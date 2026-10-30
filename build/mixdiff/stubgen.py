"""read an ld log, write int3 stubs (asm) for every undefined reference.  usage: stubgen.py link.log stubs.s
(ld prints the symbols without the i386 leading underscore)"""
import re, sys
syms = sorted(set("_" + s for s in re.findall(r"undefined reference to `([^']+)'", open(sys.argv[1], errors="replace").read())))
try:
    have = set(re.findall(r"^\t\.globl (\S+)", open(sys.argv[2]).read(), re.M))
except OSError:
    have = set()
open(sys.argv[2], "a", newline="\n").write("".join("\t.globl %s\n%s:\n\tint3\n" % (s, s) for s in syms if s not in have))
print(len(syms), "stubs")
