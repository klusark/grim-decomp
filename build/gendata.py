"""Generate obj/<prog>/data.s: the program's initialised data sections.

raw/<prog>/sections/*.bin (dumped from Ghidra by tools/export_data.py) are
emitted as real .rdata/.data contents with labels for every global the
decompiled code references, so `extern int DAT_004f5a2c;` in C resolves to the
original bytes at the original offset.  Dword slots whose value points into
the image become link-time relocations:

  * a function start        -> .long _FunctionName
  * inside .rdata/.data     -> .long _sect_<name> + offset
  * elsewhere (code labels, thunks) -> the original value, with a comment

Anything the code references that has no address inside a dumped section
(LAB_ labels, import address table slots) stays with link.py's data.c.

usage: python -I gendata.py <prog> <srcdir> <objdir>
Prints the JSON list of symbol names it defined."""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dllnames
DLL_STD = dllnames.load()
ADDR_SUFFIX = re.compile(r"_([0-9a-f]{8})$")


def load_sections(prog):
    raw = os.path.join(ROOT, "raw", prog)
    secs = json.load(open(os.path.join(raw, "sections.json")))
    for s in secs:
        s["start"] = int(s["start"], 16)
        s["bytes"] = open(os.path.join(raw, "sections", s["file"]), "rb").read()
        s["sym"] = "_sect_" + s["name"].strip(".")
    return secs


def load_text_range(prog):
    for line in open(os.path.join(ROOT, "raw", prog, "segments.txt")):
        if line.startswith(".text:"):
            lo, hi = line.split(":", 1)[1].strip().split(" - ")
            return int(lo, 16), int(hi, 16)
    return 0, 0


def load_functions(prog):
    fs = json.load(open(os.path.join(ROOT, "raw", prog, "functions.json")))
    return {int(f["address"], 16): f for f in fs}


def load_named_globals(prog):
    out = {}
    path = os.path.join(ROOT, "raw", prog, "globals.json")
    if not os.path.exists(path):
        return out
    for line in open(path, encoding="utf-8", errors="replace"):
        m = re.match(r"^(\S+) @ ([0-9a-f]{8}) ", line)
        if m:
            out[m.group(1)] = int(m.group(2), 16)
    return out


def referenced_symbols(src, prog):
    """Names declared extern in globals.h/functions.h -> C symbol names."""
    names = []
    for hdr in ("globals.h", "functions.h"):
        for line in open(os.path.join(src, prog, hdr), encoding="utf-8"):
            m = re.match(r"^extern (.*?);", line)
            if not m or m.group(1).startswith("code ") and "*" not in m.group(1):
                continue
            d = m.group(1)
            if "(" in d:  # function pointer declarator: name inside the parens
                mm = re.search(r"\(\s*(?:STDCALL\s*)?\*\s*([A-Za-z_]\w*)\s*\)", d)
            else:
                mm = re.search(r"([A-Za-z_]\w*)\s*(\[[^\]]*\])?$", d)
            if mm:
                names.append(mm.group(1))
    return names


def main(prog, src, obj):
    secs = load_sections(prog)
    text_lo, text_hi = load_text_range(prog)
    funcs = load_functions(prog)
    named = load_named_globals(prog)

    def section_of(addr):
        for s in secs:
            if s["start"] <= addr < s["start"] + s["size"]:
                return s
        return None

    # the code section as a data blob (data islands inside it: DirectInput's c_dfDIKeyboard, switch data)
    tbp = os.path.join(ROOT, "raw", prog, "textblob.json")
    tb = None
    if os.path.exists(tbp):
        tb = json.load(open(tbp))
        tb["start"] = int(tb["start"], 16)
        tb["bytes"] = open(os.path.join(ROOT, "raw", prog, "sections", tb["file"]), "rb").read()

    def in_text_blob(addr):
        return tb is not None and tb["start"] <= addr < tb["start"] + tb["size"] and addr not in funcs

    # symbols to place
    placed = {}  # addr -> [names]
    defined = []
    text_syms = []
    for n in referenced_symbols(src, prog):
        if n.endswith("_exref") or n.startswith(("LAB_", "switchD_")):
            continue
        m = ADDR_SUFFIX.search(n)
        addr = int(m.group(1), 16) if m else named.get(n)
        if addr is None:
            continue
        if section_of(addr) is None:
            if in_text_blob(addr) and not n.startswith(("FUN_", "thunk_")):
                text_syms.append((addr, n))
            continue
        placed.setdefault(addr, []).append(n)
        defined.append(n)
    # data islands of the code section: from the first to the last named data symbol that is no
    # function; dwords in there are relocated like those of the real data sections
    island = None
    if text_syms:
        lo = min(a for a, _ in text_syms)
        hi = max(a for a, _ in text_syms) + 0x400
        island = (lo & ~0xf, hi)

    # byte ranges that are text: every string Ghidra found (raw/<prog>/strings.txt),
    # extended to its NUL terminator in the dump. Dwords inside them are never
    # pointers ("Dir\0" looks like 0x00726944, an address inside .data).
    text_ranges = []
    spath = os.path.join(ROOT, "raw", prog, "strings.txt")
    if os.path.exists(spath):
        for line in open(spath, encoding="utf-8", errors="replace"):
            m = re.match(r"^([0-9a-f]{8}): \"(.*)\"\s*$", line)
            if not m:
                continue
            if re.fullmatch(r"[0-9a-f]{8}", m.group(2)):
                continue  # a pointer Ghidra labelled with its target address, not text
            a = int(m.group(1), 16)
            s = section_of(a)
            if s is None:
                continue
            off = a - s["start"]
            end = s["bytes"].find(b"\0", off)
            if end < 0:
                end = len(s["bytes"])
            text_ranges.append((a, s["start"] + end + 1))
    text_ranges.sort()

    def in_text(addr):
        import bisect
        i = bisect.bisect_right(text_ranges, (addr, 1 << 40)) - 1
        return i >= 0 and text_ranges[i][0] <= addr < text_ranges[i][1]

    def looks_like_text(b4):
        return all(c == 0 or 9 <= c <= 13 or 32 <= c <= 126 for c in b4) and sum(32 <= c <= 126 for c in b4) >= 3

    out = ["# GENERATED by build/gendata.py from raw/%s/sections (Ghidra memory dump)" % prog,
           "\t.text"]
    stats = {"code_ptr": 0, "data_ptr": 0, "code_other": 0}
    for s in secs:
        data = s["bytes"]
        size = s["size"]
        init = len(data)
        base = s["start"]
        # .rdata is emitted inside the .data output section, directly in front of the .data blob at the
        # original distance: code indexes tables that run from .rdata into .data (the sine/cosine
        # quadrant tables; Math_SinCosTable reads one entry past the end of the third one)
        out.append("")
        out.append("\t.section .data")
        out.append("\t.p2align 4")
        out.append("\t.globl %s" % s["sym"])
        out.append("%s:" % s["sym"])
        syms_here = sorted(a - base for a in placed if base <= a < base + size)
        sym_set = set(syms_here)
        off = 0
        run = []

        def flush():
            while run:
                chunk = run[:24]
                del run[:24]
                out.append("\t.byte " + ",".join(str(b) for b in chunk))

        while off < size:
            if off in sym_set:
                flush()
                for n in placed[base + off]:
                    out.append("\t.globl _%s" % n)
                    out.append("_%s:" % n)
            if off >= init:
                # zero-filled tail: jump to the next symbol or the end
                nxt = min([o for o in syms_here if o > off] + [size])
                flush()
                out.append("\t.zero %d" % (nxt - off))
                off = nxt
                continue
            if off % 4 == 0 and off + 4 <= init and not any((off + k) in sym_set for k in (1, 2, 3)) \
                    and not in_text(base + off):
                v = int.from_bytes(data[off:off + 4], "little")
                # an exact function start is a pointer even if its bytes look printable
                # (0x00483d40 is "@=H\0"); the text heuristic only guards data pointers
                if looks_like_text(data[off:off + 4]) and v not in funcs:
                    run.append(data[off])
                    off += 1
                    if len(run) >= 24:
                        flush()
                    continue
                target = None
                if text_lo <= v <= text_hi:
                    f = funcs.get(v)
                    # a named thunk (e.g. SoundsInitialize = jmp [IAT]) resolves to the
                    # import library's own thunk, so its symbol is a valid target too
                    if f and not f.get("isExternal") and (not f.get("isThunk") or not f["name"].startswith("FUN_")):
                        target = DLL_STD.get(f["name"], "_" + f["name"])
                        stats["code_ptr"] += 1
                    else:
                        stats["code_other"] += 1
                        flush()
                        out.append("\t.long 0x%08x\t# code address, not a function start" % v)
                        off += 4
                        continue
                else:
                    ts = section_of(v)
                    if ts is not None and v != 0:
                        target = "%s + 0x%x" % (ts["sym"], v - ts["start"])
                        stats["data_ptr"] += 1
                if target:
                    flush()
                    out.append("\t.long %s" % target)
                    off += 4
                    continue
            run.append(data[off])
            off += 1
            if len(run) >= 24:
                flush()
        flush()
        nxt = next((t for t in secs if t["start"] > base and s["name"] == ".rdata"), None)
        if nxt is not None and nxt["start"] > base + size:
            out.append("\t.zero %d\t# gap up to %s" % (nxt["start"] - base - size, nxt["name"]))
    if tb is not None:
        out.append("")
        out.append("\t.section .data")
        out.append("\t.p2align 4")
        out.append("\t.globl _sect_text")
        out.append("_sect_text:")
        tsyms = {}
        for a, n in text_syms:
            tsyms.setdefault(a - tb["start"], []).append(n)
            defined.append(n)
        data = tb["bytes"]
        base = tb["start"]
        off = 0
        run = []

        def tflush():
            if run:
                out.append("\t.byte " + ",".join(str(b) for b in run))
                del run[:]

        while off < tb["size"]:
            if off in tsyms:
                tflush()
                for n in tsyms[off]:
                    out.append("\t.globl _%s" % n)
                    out.append("_%s:" % n)
            if island and island[0] <= base + off < island[1] and off % 4 == 0 and off + 4 <= len(data) \
                    and not any((off + k) in tsyms for k in (1, 2, 3)):
                v = int.from_bytes(data[off:off + 4], "little")
                target = None
                ts = section_of(v)
                if ts is not None and v != 0:
                    target = "%s + 0x%x" % (ts["sym"], v - ts["start"])
                elif v in funcs and not funcs[v].get("isExternal") \
                        and (not funcs[v].get("isThunk") or not funcs[v]["name"].startswith(("thunk_", "FUN_"))):
                    target = DLL_STD.get(funcs[v]["name"], "_" + funcs[v]["name"])
                elif island[0] <= v < island[1]:
                    target = "_sect_text + 0x%x" % (v - base)
                if target:
                    tflush()
                    out.append("\t.long %s" % target)
                    off += 4
                    continue
            run.append(data[off] if off < len(data) else 0)
            off += 1
            if len(run) >= 24:
                tflush()
        tflush()
    with open(os.path.join(obj, prog, "data.s"), "w", newline="\n") as w:
        w.write("\n".join(out) + "\n")
    print(json.dumps({"defined": defined, "stats": stats, "sections": [(s["name"], s["size"], len(s["bytes"])) for s in secs]}))


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3])
