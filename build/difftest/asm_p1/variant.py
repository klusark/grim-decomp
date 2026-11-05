"""variant.py <overrides.c> <name>...: renames the named override functions (a #define after functions.h)"""
import sys
p = sys.argv[1]
t = open(p).read()
defs = "".join("#define %s p1_off_%s\n" % (n, n) for n in sys.argv[2:])
key = '#include "functions.h"\n'
assert key in t
t = t.replace(key, key + defs, 1)
open(p, "w", newline="\n").write(t)
