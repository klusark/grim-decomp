"""List C functions that take the address of one of their own parameters (`&param_2`, `(int)&param_1`).

Ghidra reuses a parameter's stack slot as a local (scanf output, loop counter, ...) and often
splits the uses over differently named variables, so the compiled C reads the wrong slot.
Such functions are candidates for assembly mode (names/asm_extra.json).

Usage: python -I find_param_addr.py [prog]        (default LUA.DLL)
"""
import re, glob, json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
prog = sys.argv[1] if len(sys.argv) > 1 else "LUA.DLL"
asm = set(json.load(open(os.path.join(ROOT, "names", "asm_funcs.json"))).get(prog, []))
total = 0
for f in sorted(glob.glob(os.path.join(ROOT, "src", prog, "*.c"))):
    base = os.path.basename(f)
    s = open(f, encoding="utf-8").read()
    parts = re.split(r"(?m)^/\* ---- 0x([0-9a-f]+)  (\S+) ---- \*/", s)
    for i in range(1, len(parts), 3):
        addr, name, body = parts[i], parts[i + 1], parts[i + 2]
        if addr in asm or "#if 0" in body.split("\n", 6)[0:6].__str__():
            continue
        m = re.search(r"&\s*param_\d+\b", body)
        if m:
            total += 1
            print("%s %s %s: %s" % (base, addr, name, m.group(0)))
print(total, "functions")
