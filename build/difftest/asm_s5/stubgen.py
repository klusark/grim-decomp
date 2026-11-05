"""stubgen.py link.log stubs.s: int3 stubs for every undefined reference (copy of build/mixdiff/stubgen.py that keeps
fastcall names, which ld prints with their own '@' decoration)"""
import re, sys
syms = sorted(set((s if s.startswith("@") else "_" + s) for s in re.findall(r"undefined reference to `([^']+)'", open(sys.argv[1], errors="replace").read())))
try:
    have = set(re.findall(r"^\t\.globl (\S+)", open(sys.argv[2]).read(), re.M))
except OSError:
    have = set()
open(sys.argv[2], "a", newline="\n").write("".join("\t.globl %s\n%s:\n\tint3\n" % (s, s) for s in syms if s not in have))
print(len(syms), "stubs")
