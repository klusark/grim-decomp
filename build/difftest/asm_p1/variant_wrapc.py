"""variant_wrapc.py <overrides.c> <name>: experiment variant: the C override <name> is renamed p1_c_<name> and called from a
one-line C wrapper of the original name"""
import sys
p, n = sys.argv[1], sys.argv[2]
t = open(p).read()
key = '#include "functions.h"\n'
t = t.replace(key, key + "#define %s p1_c_%s\n" % (n, n), 1)
tail = "\n#undef %s\nvoid %s(int p) { p1_c_%s(p); }\n" % (n, n, n)
i = t.rindex("#endif /* GRIM_EXE */")
t = t[:i] + tail + t[i:]
open(p, "w", newline="\n").write(t)
