"""Match the functions of a v1.01 program against the remaster's unstripped Linux build (original names).

Usage: python -I orig_match.py <source dump> <source elf> <target prog> <target dump> <out.json>   (from tools/)
  source dump: orig_dump.py output of /linux/libLua.so or /linux/GrimFandango (with code)
  source elf:  the ELF file (string contents of DAT_ / 0x addresses)
  target prog: LUA.DLL / GRIMFANDANGO.EXE / IMUSE.DLL (code from raw/<prog>/functions, strings from raw/<prog>/sections)
  target dump: orig_dump.py --no-code output of the v1.01 program (call graph)

Evidence, all of it recorded per candidate in the output:
  * anchors: functions (and imports) that have the same name on both sides;
  * strings: a string literal referenced by exactly one function on each side votes for that pair (the target's
    s_*_ADDR / DAT_ / 0x tokens are read from the section dumps);
  * call graph: for a matched pair, its only unmatched callee (caller) on each side is paired; a candidate is kept
    when the callees / callers it shares with already matched pairs agree (no contradiction) and no other candidate
    claims either side.
The output lists candidates with their evidence; nothing is renamed here (names/orig_*.json batches are written from
it after review)."""
import json, os, re, struct, sys
from collections import defaultdict, Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


# ---- string contents ------------------------------------------------------
class Image:
    def __init__(self, blocks):
        self.blocks = blocks  # [(start, bytes)]

    def cstr(self, addr):
        for start, data in self.blocks:
            if start <= addr < start + len(data):
                off = addr - start
                end = data.find(b"\0", off)
                if end < 0 or end - off < 3 or end - off > 400:
                    return None
                s = data[off:end]
                if all(32 <= c < 127 or c in (9, 10, 13) for c in s):
                    return s.decode("latin-1")
                return None
        return None


def pe_image(prog):
    d = os.path.join(ROOT, "raw", prog)
    blocks = []
    for sec in json.load(open(os.path.join(d, "sections.json"))):
        blocks.append((int(sec["start"], 16), open(os.path.join(d, "sections", sec["file"]), "rb").read()))
    return Image(blocks)


def elf_image(path, base_shift=0):
    data = open(path, "rb").read()
    phoff, = struct.unpack_from("<I", data, 0x1c)
    phentsize, phnum = struct.unpack_from("<HH", data, 0x2a)
    blocks = []
    for i in range(phnum):
        p_type, p_off, p_vaddr, _, p_filesz = struct.unpack_from("<IIIII", data, phoff + i * phentsize)
        if p_type == 1:
            blocks.append((p_vaddr + base_shift, data[p_off:p_off + p_filesz]))
    return Image(blocks)


LIT_RE = re.compile(r'"((?:[^"\\]|\\.)*)"')
ADDR_RE = re.compile(r"\b(?:s_\w*?_|DAT_|PTR_s_\w*?_|0x)([0-9a-f]{8})\b")


def unescape(s):
    return s.replace("\\'", "'").replace('\\"', '"').replace("\\n", "\n").replace("\\t", "\t").replace("\\\\", "\\")


def strings_of(code, img):
    out = set()
    for m in LIT_RE.finditer(code):
        s = unescape(m.group(1))
        if len(s) >= 3:
            out.add(s)
    for m in ADDR_RE.finditer(code):
        s = img.cstr(int(m.group(1), 16))
        if s and len(s) >= 3:
            out.add(s)
    return out


# ---- ELF symbols ------------------------------------------------------------
def elf_symbols(path, base_shift=0):
    """[(value, size, 'F'|'O', bind 'G'|'L'|'W', raw name)] from .symtab"""
    d = open(path, "rb").read()
    shoff, = struct.unpack_from("<I", d, 0x20)
    shentsize, shnum = struct.unpack_from("<HH", d, 0x2e)
    sh = [struct.unpack_from("<IIIIIIIIII", d, shoff + i * shentsize) for i in range(shnum)]
    out = []
    for s in sh:
        if s[1] != 2:  # SHT_SYMTAB
            continue
        stroff = sh[s[6]][4]
        for i in range(s[5] // 16):
            nm, val, size, info, _, shn = struct.unpack_from("<IIIBBH", d, s[4] + i * 16)
            name = d[stroff + nm:d.index(b"\0", stroff + nm)].decode("latin-1")
            typ, bind = info & 15, info >> 4
            if name and typ in (1, 2) and shn != 0:
                out.append((val + base_shift, size, "F" if typ == 2 else "O", "GLW"[bind] if bind < 3 else "?", name))
    return sorted(out)


def _src_name(s, i):
    j = i
    while j < len(s) and s[j].isdigit():
        j += 1
    if j == i:
        return None, i
    n = int(s[i:j])
    return s[j:j + n], j + n


def demangle(raw):
    """Just the qualified name of an Itanium-mangled symbol: _ZL4nextv -> next, _ZN6LState4SaveEPFlPvjE ->
    LState::Save; anything else (templates, operators) comes back unchanged."""
    n = raw.split("@@")[0]
    if not n.startswith("_Z"):
        return n
    i = 2
    if n.startswith("L", i):
        i += 1
    if n.startswith("N", i):
        i += 1
        parts = []
        while i < len(n) and n[i] != "E":
            if n[i:i + 2] in ("C1", "C2"):
                parts.append(parts[-1] if parts else "?")
                i += 2
            elif n[i:i + 2] in ("D0", "D1", "D2"):
                parts.append("~" + (parts[-1] if parts else "?"))
                i += 2
            else:
                part, i2 = _src_name(n, i)
                if part is None:
                    return n
                parts.append(part)
                i = i2
        return "::".join(parts)
    part, _ = _src_name(n, i)
    return part or n


# ---- programs ---------------------------------------------------------------
class Prog:
    def __init__(self, dump, img, code_dir=None, symbols=None):
        d = json.load(open(dump))
        self.name = {}
        self.thunk = {}
        self.sym = {}   # canonical address -> raw symbol (source side)
        canon = {}
        if symbols:
            fs = [x for x in symbols if x[2] == "F" and x[1] > 0]
            starts = [x[0] for x in fs]
            import bisect
            for f in d["funcs"]:
                a = int(f["address"], 16)
                k = bisect.bisect_right(starts, a) - 1
                if k >= 0 and fs[k][0] <= a < fs[k][0] + fs[k][1] and not f["isExternal"]:
                    # (inside a sized symbol it is real code, even where Ghidra took the PIC prologue for a thunk)
                    c = "%08x" % fs[k][0]
                    canon[f["address"]] = c
                    if c not in self.sym or fs[k][3] == "G":
                        self.sym[c] = fs[k][4]
        for f in d["funcs"]:
            a = canon.get(f["address"], f["address"])
            if a in self.name and a != f["address"]:
                continue
            self.name[a] = demangle(self.sym[a]) if a in self.sym else f["name"]
            self.thunk[a] = (f["isThunk"] or f["isExternal"]) and a not in self.sym
        if canon:
            edges = [[canon.get(s, s), canon.get(t, t)] for s, t in d["edges"]]
            code = defaultdict(str)
            for a, c in d["code"].items():
                code[canon.get(a, a)] += c
            d = dict(d, edges=edges, code=code)
        local = defaultdict(list)
        for a, n in self.name.items():
            if not self.thunk[a]:
                local[n].append(a)
        self.by_name = local

        def node(a):
            if a not in self.name:
                return None
            if self.thunk[a]:
                n = self.name[a]
                if len(local.get(n, [])) == 1:
                    return local[n][0]
                return "ext:" + n
            return a

        self.callees = defaultdict(set)
        self.callers = defaultdict(set)
        for s, t in d["edges"]:
            s2, t2 = node(s), node(t)
            if s2 is None or t2 is None or s2.startswith("ext:") or s2 == t2:
                continue
            self.callees[s2].add(t2)
            self.callers[t2].add(s2)
        self.code = {}
        if code_dir:
            for a in self.name:
                p = os.path.join(code_dir, a + ".c")
                if not self.thunk[a] and os.path.exists(p):
                    self.code[a] = open(p, encoding="utf-8", errors="replace").read()
        else:
            self.code = {a: c.replace("\r\n", "\n") for a, c in d["code"].items()}
        self.strings = {a: strings_of(c, img) for a, c in self.code.items()}
        self.funcs = [a for a in self.name if not self.thunk[a]]


def name_tables(img, funcs, shift=0):
    """{string: set(function)} from tables of {char *name, function} or {function, char *name} pairs in the data
    (Lua registration tables, the module tables).  The words are classified as string pointers (S) and function
    pointers (F, any function or thunk); a run of alternating S / F words with stride 4 is a table, and its first word
    tells the order of each pair (a run starting with S pairs each S with the F after it, one starting with F each F
    with the S after it).  Runs shorter than two pairs or of odd length are ignored."""
    out = defaultdict(set)
    fset = set(funcs)
    for start, data in img.blocks:
        kinds = []
        for off in range(0, len(data) - 3, 4):
            w, = struct.unpack_from("<I", data, off)
            a = "%08x" % ((w + shift) & 0xffffffff)
            if a in fset:
                kinds.append(("F", a))
            else:
                st = img.cstr(w + shift)
                kinds.append(("S", st) if st else (None, None))
        i = 0
        while i < len(kinds):
            k0 = kinds[i][0]
            if k0 is None:
                i += 1
                continue
            j = i + 1
            while j < len(kinds) and kinds[j][0] is not None and kinds[j][0] != kinds[j - 1][0]:
                j += 1
            run = kinds[i:j]
            if len(run) >= 4 and len(run) % 2 == 0:   # an odd run has an unknown orientation: skip it
                for x in range(0, len(run) - 1, 2):
                    a, b = run[x], run[x + 1]
                    st, fn = (a[1], b[1]) if a[0] == "S" else (b[1], a[1])
                    out[st].add(fn)
            i = j if j > i + 1 else i + 1
    return out


AUTO_RE = re.compile(r"^(FUN_|thunk_|[a-z0-9]+__[0-9a-f]+$)")


def is_auto(n):
    return bool(AUTO_RE.match(n))


def match(S, T, fixed=None, s_tables=None, t_tables=None):
    """Returns (pairs, evidence): pairs target addr -> source addr."""
    pairs, ev = {}, defaultdict(list)
    rev = {}

    def add(t, s, why):
        pairs[t] = s
        rev[s] = t
        ev[t].append(why)

    # {name, function} tables: the same string names one function on each side
    if s_tables and t_tables:
        tv = defaultdict(set)
        for st, ts in t_tables.items():
            ss = s_tables.get(st)
            if ss and len(ss) == 1 and len(ts) == 1:
                tv[next(iter(ts))].add((next(iter(ss)), st))
        sv = Counter(s for v in tv.values() for s in {x[0] for x in v})
        for t, v in tv.items():
            srcs = {x[0] for x in v}
            if len(srcs) == 1:
                s = next(iter(srcs))
                if sv[s] == 1:
                    add(t, s, "table entry " + " | ".join(repr(x[1]) for x in sorted(v)))

    # anchors: same (non-auto) name, unique on both sides
    for n, sa in S.by_name.items():
        ta = T.by_name.get(n)
        if len(sa) == 1 and ta and len(ta) == 1 and not is_auto(n) and ta[0] not in pairs and sa[0] not in rev:
            add(ta[0], sa[0], "same name")
    for t, s in (fixed or {}).items():
        if t not in pairs and s not in rev:
            add(t, s, "fixed")

    # strings unique to one function on each side
    s_users, t_users = defaultdict(set), defaultdict(set)
    for a, ss in S.strings.items():
        for x in ss:
            s_users[x].add(a)
    for a, ss in T.strings.items():
        for x in ss:
            t_users[x].add(a)
    votes = defaultdict(Counter)
    vote_strs = defaultdict(list)
    for x, ts in t_users.items():
        ss = s_users.get(x)
        if ss and len(ss) == 1 and len(ts) == 1:
            t, s = next(iter(ts)), next(iter(ss))
            votes[t][s] += 1
            vote_strs[(t, s)].append(x)
    sbest = defaultdict(Counter)
    for t, c in votes.items():
        for s, n in c.items():
            sbest[s][t] += n
    for t, c in votes.items():
        if t in pairs:
            continue
        (s, n), = c.most_common(1)
        if len(c) > 1 and c.most_common(2)[1][1] == n:
            continue
        if sbest[s].most_common(1)[0][0] != t or s in rev:
            continue
        add(t, s, "strings: " + " | ".join(repr(x)[:60] for x in vote_strs[(t, s)][:4]))

    # call graph propagation
    def mapped(t):  # target node -> source node, ext nodes map by name
        if t.startswith("ext:"):
            return t
        return pairs.get(t)

    changed = True
    while changed:
        changed = False
        cand = defaultdict(set)
        for t, s in list(pairs.items()):
            for rel, (tt, st) in (("callee", (T.callees, S.callees)), ("caller", (T.callers, S.callers))):
                ut = [x for x in tt.get(t, ()) if not x.startswith("ext:") and x not in pairs]
                us = [x for x in st.get(s, ()) if not x.startswith("ext:") and x not in rev]
                if len(ut) == 1 and len(us) == 1:
                    cand[(ut[0], us[0])].add(f"only unmatched {rel} of {T.name[t]}")
        tcount = Counter(t for t, s in cand)
        scount = Counter(s for t, s in cand)
        for (t, s), why in cand.items():
            if tcount[t] != 1 or scount[s] != 1:
                continue
            # consistency: matched callees / callers must correspond
            bad = 0
            good = 0
            for tt, st in ((T.callees, S.callees), (T.callers, S.callers)):
                tm = {mapped(x) for x in tt.get(t, ()) if mapped(x)}
                sm = {x for x in st.get(s, ()) if x in rev or x.startswith("ext:")}
                good += len(tm & sm)
                bad += len(tm - sm - {x for x in tm if x.startswith("ext:")})
            if bad > max(1, good // 2):
                continue
            add(t, s, "; ".join(sorted(why)) + f" (agree {good}, disagree {bad})")
            changed = True
    return pairs, ev


def main():
    sdump, selfpath, tprog, tdump, out = sys.argv[1:6]
    # Ghidra loads a shared object at 0x10000
    shift = 0x10000 if selfpath.endswith(".so") else 0
    S = Prog(sdump, elf_image(selfpath, shift), symbols=elf_symbols(selfpath, shift))
    T = Prog(tdump, pe_image(tprog), os.path.join(ROOT, "raw", tprog, "functions"))
    s_img, t_img = elf_image(selfpath, shift), pe_image(tprog)
    pairs, ev = match(S, T, s_tables=name_tables(s_img, S.name, shift), t_tables=name_tables(t_img, T.name))
    res = []
    for t in sorted(pairs):
        s = pairs[t]
        res.append({"addr": t, "old": T.name[t], "orig": S.name[s], "src": s, "evidence": ev[t]})
    json.dump(res, open(out, "w"), indent=1)
    diff = [r for r in res if r["old"] != r["orig"]]
    print(f"{len(res)} pairs, {len(diff)} with a different name, "
          f"{sum(1 for r in diff if T.name[r['addr']].startswith('FUN_'))} FUN_, "
          f"{sum(1 for r in diff if is_auto(r['old']) and not r['old'].startswith('FUN_'))} module names")


if __name__ == "__main__":
    main()
