"""mut.py <mutations.txt> <index> <src.c> <out.c>: sensitivity check helper.  Writes src.c with mutation number
<index> (a line "old ||| new" of mutations.txt, literal text, must occur in src.c) applied to out.c; prints the
number of mutations when index is -1."""
import sys
muts = [l.rstrip("\n").split(" ||| ") for l in open(sys.argv[1]) if " ||| " in l]
i = int(sys.argv[2])
if i < 0:
    print(len(muts))
    sys.exit(0)
old, new = muts[i]
t = open(sys.argv[3]).read()
if old not in t:
    print("MUTATION NOT FOUND:", old)
    sys.exit(1)
open(sys.argv[4], "w", newline="\n").write(t.replace(old, new, 1))
print("mutation %d: %s -> %s" % (i, old, new))
