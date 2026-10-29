"""List decompiled functions whose float/double-typed variables are used as integers or pointers.

Ghidra sometimes types a 4-byte local as float although the code treats it as an int or pointer
(or the reverse); the C compiler then converts values where the original just copied bits.
Such functions are candidates for assembly mode (names/asm_extra.json).

Usage: python -I find_float_misuse.py [prog]        (default LUA.DLL)
"""
import re, glob, json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
prog = sys.argv[1] if len(sys.argv) > 1 else "LUA.DLL"
asm = set(json.load(open(os.path.join(ROOT, "names", "asm_funcs.json"))).get(prog, []))
INT_CAST = r"\((?:u?int|byte \*|u?int \*|undefined\d? \*|char \*|void \*|code \*|short|ushort)\)\s*%s\b"
INT_OPS = r"[\[\+\-\*]\s*%s\s*[\]\+\-\)]|\b%s\s*(?:<<|>>|%%|&|\|)"
total = 0
for f in sorted(glob.glob(os.path.join(ROOT, "src", prog, "*.c"))):
    base = os.path.basename(f)
    if base.startswith("crt") or base in ("tmpnam.c",):
        continue
    s = open(f, encoding="utf-8").read()
    parts = re.split(r"(?m)^/\* ---- 0x([0-9a-f]+)  (\S+) ---- \*/", s)
    for i in range(1, len(parts), 3):
        addr, name, body = parts[i], parts[i + 1], parts[i + 2]
        if addr in asm:
            continue
        fl = set(re.findall(r"\b(?:float|double)\s+(\w+);", body)) | set(re.findall(r"#define (\w+) \(\*\((?:float|double) \*\)", body))
        bad = sorted({v for v in fl if re.search(INT_CAST % v, body) or re.search(INT_OPS % (v, v), body)})
        if bad:
            total += 1
            print(base, addr, name, bad)
print(total, "functions")
