"""shotpix.py <a.raw> <b.raw> [n]: the first n differing pixels (x, y, BGR of a, BGR of b)"""
import sys
a = open(sys.argv[1], "rb").read(); b = open(sys.argv[2], "rb").read()
n = int(sys.argv[3]) if len(sys.argv) > 3 else 20
w = 640
for i in range(0, min(len(a), len(b)), 4):
    if a[i:i + 3] != b[i:i + 3]:
        p = i // 4
        print(p % w, p // w, tuple(a[i:i + 3]), tuple(b[i:i + 3]))
        n -= 1
        if not n:
            break
