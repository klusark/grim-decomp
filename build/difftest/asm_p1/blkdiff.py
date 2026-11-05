"""blkdiff.py <file.s> a0 a1 b0 b1: compares two address ranges of a dumped function (lines "addr:\tinsn"), with
label and address operands normalised to offsets from the block start; prints the differing lines."""
import re, sys
lines = []
for l in open(sys.argv[1]):
    m = re.match(r"([0-9a-f]+):\t(.*)", l.rstrip("\n"))
    if m:
        lines.append((int(m.group(1), 16), m.group(2)))
def blk(a0, a1):
    out = []
    for a, t in lines:
        if a0 <= a < a1:
            t = re.sub(r"\.L[0-9a-f]+_([0-9a-f]+)", lambda m: "L%+d" % (int(m.group(1), 16) - a0), t)
            t = re.sub(r"\.Ljt_[0-9a-f]+_[0-9a-f]+", "JT", t)
            out.append(t)
    return out
x = blk(int(sys.argv[2], 16), int(sys.argv[3], 16))
y = blk(int(sys.argv[4], 16), int(sys.argv[5], 16))
print(len(x), len(y))
for i, (p, q) in enumerate(zip(x, y)):
    if p != q:
        print(i, p, "|", q)
