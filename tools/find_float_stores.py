"""List decompiled functions that store a float/double variable (or the result of a float-returning
function) into a non-float lvalue, e.g. `puVar1[1] = fVar6;` with puVar1 an undefined4 *.

The C compiler converts the value (4.0 -> 4) where the original copied the bits. Such functions
are candidates for assembly mode (names/asm_extra.json).

Usage: python -I find_float_stores.py [prog]        (default LUA.DLL)
"""
import re, glob, json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
prog = sys.argv[1] if len(sys.argv) > 1 else "LUA.DLL"
asm = set(json.load(open(os.path.join(ROOT, "names", "asm_funcs.json"))).get(prog, []))
funcs = json.load(open(os.path.join(ROOT, "raw", prog, "functions.json")))
FRET = set()
for fn in funcs:
    pass
hdr = open(os.path.join(ROOT, "src", prog, "functions.h"), encoding="utf-8").read()
for m in re.finditer(r"^(?:float|double)\s+(?:__\w+\s+)?\*?(\w+)\(", hdr, re.M):
    FRET.add(m.group(1))
total = 0
for f in sorted(glob.glob(os.path.join(ROOT, "src", prog, "*.c"))):
    base = os.path.basename(f)
    s = open(f, encoding="utf-8").read()
    parts = re.split(r"(?m)^/\* ---- 0x([0-9a-f]+)  (\S+) ---- \*/", s)
    for i in range(1, len(parts), 3):
        addr, name, body = parts[i], parts[i + 1], parts[i + 2]
        if addr in asm:
            continue
        fl = set(re.findall(r"\b(?:float|double)\s+(\w+);", body))
        hits = []
        for line in body.splitlines():
            m = re.match(r"\s*(.+?)\s=\s(\w+)(\(.*)?;\s*$", line)
            if not m:
                continue
            lhs, rhs, call = m.group(1), m.group(2), m.group(3)
            isf = (call is None and rhs in fl) or (call is not None and rhs in FRET)
            if not isf:
                continue
            if lhs in fl or re.search(r"\((?:float|double) ?\*\)", lhs):
                continue
            hits.append(line.strip())
        if hits:
            total += 1
            print("%s %s %s: %s" % (base, addr, name, hits[0]))
print(total, "functions")
