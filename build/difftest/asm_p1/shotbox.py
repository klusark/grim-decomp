"""shotbox.py <a.raw> <b.raw> [width]: bounding box and count of the pixels that differ between two raw BGRA shots"""
import sys
a = open(sys.argv[1], "rb").read(); b = open(sys.argv[2], "rb").read()
w = int(sys.argv[3]) if len(sys.argv) > 3 else 640
x0 = y0 = 1 << 30; x1 = y1 = -1; n = 0
for i in range(0, min(len(a), len(b)), 4):
    if a[i:i + 3] != b[i:i + 3]:
        p = i // 4; x, y = p % w, p // w
        n += 1; x0 = min(x0, x); x1 = max(x1, x); y0 = min(y0, y); y1 = max(y1, y)
print(n, "pixels differ, box x %d..%d y %d..%d" % (x0, x1, y0, y1))
