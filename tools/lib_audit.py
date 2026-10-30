"""Static reachability audit of a LINKED program (build/obj/<PROG>/<prog>.exe|dll).

Which functions of the rebuilt binary can run at all?  The decompiled source still contains the
original MSVC C runtime and zlib; most of the runtime start-up/locale/stdio code is only reached
from the original `entry`, which the rebuilt programs never run (the host CRT start-up calls
WinMain).  This tool answers "is function F referenced from anything live?" on the final PE image:

  * functions = symbols of `nm -n` inside .text (the next symbol ends a function)
  * edges     = every address-sized hex operand in the disassembly of a function that falls
                inside .text (direct call/jmp, `push $addr`, `mov $addr`, `call *addr`, ...)
  * data      = every aligned dword of .data/.rdata/.text-islands that is a function start
                (vtables, callback tables); `--ignore-data-in SYM,SYM` skips tables that are
                themselves dead (e.g. the CRT's own exit tables)
  * roots     = entry point, DLL exports, `--root SYM`

usage: python -I lib_audit.py <pe-file> [--root SYM]... [--json out.json]
prints the number of live / dead functions, writes {symbol: [addr, reachable]} to --json.
"""
import json, re, struct, subprocess, sys, os

NM = "C:/msys64/mingw32/bin/nm.exe"
OBJDUMP = "C:/msys64/mingw32/bin/objdump.exe"


def pe_sections(data):
    pe = struct.unpack_from("<I", data, 0x3c)[0]
    nsec = struct.unpack_from("<H", data, pe + 6)[0]
    opt = struct.unpack_from("<H", data, pe + 20)[0]
    base = struct.unpack_from("<I", data, pe + 24 + 28)[0]
    entry = struct.unpack_from("<I", data, pe + 24 + 16)[0] + base
    exp_rva, exp_size = struct.unpack_from("<II", data, pe + 24 + 96)
    secs = []
    off = pe + 24 + opt
    for i in range(nsec):
        name = data[off:off + 8].rstrip(b"\0").decode()
        vsize, va, rsize, raw = struct.unpack_from("<IIII", data, off + 8)
        secs.append((name, base + va, vsize, raw, rsize))
        off += 40
    return base, entry, secs, (exp_rva, exp_size)


def exports(data, base, secs, exp):
    rva, size = exp
    if not rva:
        return []

    def r(v):
        for n, va, vs, raw, rs in secs:
            if va - base <= v < va - base + max(vs, rs):
                return raw + v - (va - base)
    o = r(rva)
    nfun, nnames, afun, anames, aord = struct.unpack_from("<IIIII", data, o + 20)
    out = []
    for i in range(nfun):
        out.append(base + struct.unpack_from("<I", data, r(afun) + 4 * i)[0])
    return out


def main(argv):
    pe = argv[0]
    roots_extra = []
    ignore_data = []
    out_json = None
    orig_exports = None
    i = 1
    while i < len(argv):
        if argv[i] == "--root":
            roots_extra.append(argv[i + 1]); i += 2
        elif argv[i] == "--json":
            out_json = argv[i + 1]; i += 2
        elif argv[i] == "--orig-exports":
            orig_exports = argv[i + 1]; i += 2
        elif argv[i] == "--ignore-data-in":
            ignore_data = argv[i + 1].split(","); i += 2
        else:
            i += 1
    data = open(pe, "rb").read()
    base, entry, secs, exp = pe_sections(data)
    text = [s for s in secs if s[0] == ".text"][0]
    tlo, thi = text[1], text[1] + text[2]
    syms = []
    for line in subprocess.run([NM, "-n", pe], capture_output=True, text=True).stdout.splitlines():
        p = line.split()
        if len(p) == 3 and p[1] in "Tt" and tlo <= int(p[0], 16) < thi:
            syms.append((int(p[0], 16), p[2]))
    # keep the first symbol at an address
    seen = {}
    for a, n in syms:
        seen.setdefault(a, n)
    starts = sorted(seen)
    import bisect

    def fn_of(addr):
        k = bisect.bisect_right(starts, addr) - 1
        return starts[k] if k >= 0 else None
    dis = subprocess.run([OBJDUMP, "-d", "--no-show-raw-insn", pe], capture_output=True, text=True).stdout
    edges = {a: set() for a in starts}
    cur = None
    FD = []
    hexre = re.compile(r"(?<![\w.])(?:0x)?([0-9a-f]{6,8})\b")
    for line in dis.splitlines():
        m = re.match(r"^\s*([0-9a-f]+):\t(.*)$", line)
        if not m:
            continue
        a = int(m.group(1), 16)
        f = fn_of(a)
        if f is None:
            continue
        ops = m.group(2)
        ops = re.sub(r"<[^>]*>", "", ops)
        for h in re.finditer(r"\$?0x([0-9a-f]+)|\b([0-9a-f]{6,8})\b", ops):
            v = int(h.group(1) or h.group(2), 16)
            if tlo <= v < thi:
                t = fn_of(v)
                if t is not None and t != f:
                    edges[f].add(t)
            else:
                FD.append((f, v))
    # data objects: intervals between consecutive data symbols; a data object is live when something
    # live references an address inside it, and then every function / data address stored in it is
    # referenced as well (dead tables, e.g. the CRT's own exit tables, stay dead)
    dsyms = {}
    for line in subprocess.run([NM, "-n", pe], capture_output=True, text=True).stdout.splitlines():
        p = line.split()
        if len(p) == 3 and p[1] in "DdRrBbCGgSs" and not (tlo <= int(p[0], 16) < thi):
            dsyms.setdefault(int(p[0], 16), p[2])
    dsec = [(n, va, min(vs, rs) if rs else vs, raw, rs) for n, va, vs, raw, rs in secs
            if n not in (".text", ".idata", ".rsrc", ".reloc", ".eh_fram")]
    dstarts = sorted(set(dsyms) | {va for n, va, vs, raw, rs in dsec})
    dend = {}
    for k, st_ in enumerate(dstarts):
        nxt = dstarts[k + 1] if k + 1 < len(dstarts) else st_ + 4
        dend[st_] = nxt

    def dn_of(addr):
        k = bisect.bisect_right(dstarts, addr) - 1
        if k >= 0 and addr < dend[dstarts[k]]:
            return dstarts[k]

    sec_of = {}
    for n, va, vs, raw, rs in dsec:
        sec_of[n] = (va, vs, raw, rs)
    dedges = {a: set() for a in dstarts}
    for n, (va, vs, raw, rs) in sec_of.items():
        if not rs:
            continue
        blob = data[raw:raw + min(vs, rs)]
        for k in range(0, len(blob) - 3, 4):
            v = struct.unpack_from("<I", blob, k)[0]
            if v < 0x1000:
                continue
            here = dn_of(va + k)
            if here is None or dsyms.get(here) == "_sect_text":
                continue   # the original code bytes linked as data (islands): their pointers are stale originals
            if tlo <= v < thi:
                if v in seen:   # only function starts: other code addresses are switch-table entries of their own function
                    dedges[here].add(("f", v))
            else:
                t = dn_of(v)
                if t is not None and t != here:
                    dedges[here].add(("d", t))
    fdata = {a: set() for a in starts}   # function -> data objects it references
    dataroots = set()
    for f, v in FD:
        t = dn_of(v)
        if t is not None:
            fdata[f].add(t)
    roots = set()
    if tlo <= entry < thi:
        roots.add(fn_of(entry))
    if orig_exports:   # the rebuilt DLLs export everything (--export-all-symbols); only the original API is a root
        names = set()
        fj = os.path.join(os.path.dirname(orig_exports), "functions.json")
        byaddr = {f["address"]: f["name"] for f in json.load(open(fj))} if os.path.exists(fj) else {}
        for l in open(orig_exports):
            n, _, ad = l.strip().partition(" -> ")
            ad = ad.split()[0] if ad else ""
            if not n.startswith("Ordinal_"):
                names.add(n.strip())
            if ad in byaddr:
                names.add(byaddr[ad])
        for a, n in seen.items():
            if n.lstrip("_").split("@")[0] in names:
                roots.add(a)
    else:
        for e in exports(data, base, secs, exp):
            if tlo <= e < thi:
                roots.add(fn_of(e))
    byname = {n: a for a, n in seen.items()}
    for r in roots_extra:
        if r in byname:
            roots.add(byname[r])
    live = set(roots)
    dlive = set()
    st = [("f", r) for r in roots]
    par = {}
    while st:
        kind, a = st.pop()
        if kind == "f":
            for b in sorted(edges.get(a, ())):
                if b not in live:
                    live.add(b); st.append(("f", b)); par[("f", b)] = (kind, a)
            for d in sorted(fdata.get(a, ())):
                if d not in dlive:
                    dlive.add(d); st.append(("d", d)); par[("d", d)] = (kind, a)
        else:
            for k2, t in sorted(dedges.get(a, ())):
                if k2 == "f" and t not in live:
                    live.add(t); st.append(("f", t)); par[("f", t)] = (kind, a)
                elif k2 == "d" and t not in dlive:
                    dlive.add(t); st.append(("d", t)); par[("d", t)] = (kind, a)
    dataroots = {t for (k, t), p in par.items() if k == "f" and p[0] == "d"}
    seen_d = dsyms
    print(f"{os.path.basename(pe)}: {len(starts)} functions, {len(live)} reachable, {len(starts) - len(live)} dead; "
          f"{len(dataroots)} of them reached through live data")
    for q in os.environ.get("WHY", "").split(","):
        if q and q in byname:
            c = [("f", byname[q])]
            while c[-1] in par:
                c.append(par[c[-1]])
            print(q, "<-", " <- ".join((seen.get(x[1]) if x[0] == "f" else "DATA:" + hex(x[1]) + ":" + dsyms.get(x[1], "?")) for x in c[1:10]))
    if os.environ.get("DNODE"):
        d0 = int(os.environ["DNODE"], 16)
        print("dnode", hex(d0), dend[d0] - d0, [(k, seen.get(t) if k == "f" else hex(t)) for k, t in sorted(dedges[d0])][:40])
    if os.environ.get("WHYSTUB"):
        rev = {}
        for a_, bs in edges.items():
            for b_ in bs:
                rev.setdefault(b_, set()).add(a_)
        for q in os.environ["WHYSTUB"].split(","):
            if q in byname:
                print(q, "referenced by", [seen[x] + ("(live)" if x in live else "(dead)") for x in sorted(rev.get(byname[q], ()))][:8],
                      "data" if byname[q] in dataroots else "")
    if out_json:
        json.dump({seen[a]: [hex(a), a in live, a in dataroots] for a in starts}, open(out_json, "w"))


if __name__ == "__main__":
    main(sys.argv[1:])
