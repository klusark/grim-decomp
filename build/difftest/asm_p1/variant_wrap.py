"""variant_wrap.py <overrides.c> <slice.s> <name>: experiment variant: the C override <name> is renamed away and replaced by
a C function of the same name that calls the sliced original assembly (orig_<name>, embedded as a top-level asm block),
so the game links the machine code of the function under the address of a C definition."""
import sys
p, s, n = sys.argv[1], sys.argv[2], sys.argv[3]
t = open(p).read()
key = '#include "functions.h"\n'
t = t.replace(key, key + "#define %s p1_off_%s\n" % (n, n), 1)
asm = open(s).read()
lines = "".join('"%s\\n"\n' % l.replace("\\", "\\\\").replace('"', '\\"') for l in asm.split("\n"))
# optional 4th argument: a busy loop of that many iterations before the call (timing experiment)
slow = "{ volatile int k; for (k = 0; k < %s; k++); }" % (sys.argv[4] if len(sys.argv) > 4 else "0")
tail = "\n#undef %s\n__asm__(\n%s\".att_syntax prefix\\n\");\nextern void orig_%s(int);\nvoid %s(int p) { %s orig_%s(p); }\n" % (
    n, lines, n, n, slow, n)
i = t.rindex("#endif /* GRIM_EXE */")
t = t[:i] + tail + t[i:]
open(p, "w", newline="\n").write(t)
