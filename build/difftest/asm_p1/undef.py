"""undef.py <nm.txt> <out>: the symbols the C under test uses and does not define (input from build.sh's nm | awk)"""
import sys
u = set(); d = set()
for l in open(sys.argv[1]):
    p = l.split()
    if not p:
        continue
    if p[0] == "DEF":
        d.add(p[1])
    else:
        u.add(p[0])
open(sys.argv[2], "w").write("\n".join(sorted(u - d)) + "\n")
