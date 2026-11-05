"""show.py <PROG> <hexaddr|name> [asm]: print the decompiled text (from src/<PROG>/*.c) and optionally the assembly of a function"""
import re, sys, glob, os
root = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..")
prog, key = sys.argv[1], sys.argv[2]
for f in sorted(glob.glob(os.path.join(root, "src", prog, "*.c"))):
    t = open(f, encoding="utf-8", errors="replace").read()
    for m in re.finditer(r"(?ms)^/\* ---- 0x(\w+)  (\S+) ---- \*/.*?(?=^/\* ---- 0x|\Z)", t):
        if m.group(1).lstrip("0") == key.lower().lstrip("0x").lstrip("0") or m.group(2) == key:
            print("//", os.path.basename(f)); print(m.group(0))
if len(sys.argv) > 3:
    t = open(os.path.join(root, "src", prog, "asm_funcs.s")).read()
    for m in re.finditer(r"(?ms)^(\S+):  # (\S+)\n.*?(?=^\t\.def |^\t\.section|^\t\.data)", t):
        if m.group(2) == key or re.search(r"^\.L%s_" % key.lower().lstrip("0x").lstrip("0"), m.group(0), re.M):
            print(re.sub(r"^\.L\w+_(\w+):", r"\1:", m.group(0), flags=re.M))
