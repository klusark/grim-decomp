"""addchunk.py <overrides.c> <chunk.c> [renamed names...]: insert a chunk before the closing #endif, add rename defines"""
import sys
p, c = sys.argv[1], sys.argv[2]
t = open(p).read(); code = open(c).read()
for n in sys.argv[3:]:
    t = t.replace('#include "functions.h"\n', '#define %s %s__ghidra\n#include "functions.h"\n#undef %s\n' % (n, n, n), 1)
i = t.rindex("\n#endif /* GRIM_")
t = t[:i] + "\n" + code.rstrip("\n") + "\n" + t[i:]
open(p, "w", newline="\n").write(t)
