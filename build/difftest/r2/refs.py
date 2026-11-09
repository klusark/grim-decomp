"""Find every reference to the given addresses in the ORIGINAL program image (raw/<prog>/sections): absolute 32-bit
values in .text/.rdata/.data and rel32 call/jmp targets in .text, with the function that contains a .text reference.
usage: python -I refs.py <repo root> <PROG> <hex address>..."""
import bisect
import json
import os
import struct
import sys

root, prog, targets = sys.argv[1], sys.argv[2], [int(x, 16) for x in sys.argv[3:]]
raw = os.path.join(root, "raw", prog)
segs = {}
for line in open(os.path.join(raw, "segments.txt")):
    n, r = line.split(":", 1)
    lo, hi = r.strip().split(" - ")
    segs[n] = int(lo, 16)
secs = {n: open(os.path.join(raw, "sections", n[1:] + ".bin"), "rb").read() for n in (".text", ".rdata", ".data")}
funcs = sorted((int(f["address"], 16), f["name"]) for f in json.load(open(os.path.join(raw, "functions.json"))))
fa = [a for a, _ in funcs]


def owner(a):
    i = bisect.bisect_right(fa, a) - 1
    return "%s+%#x" % (funcs[i][1], a - funcs[i][0]) if i >= 0 else "?"


tb, tbase = secs[".text"], segs[".text"]
rel = {}
for i in range(len(tb) - 5):
    if tb[i] in (0xe8, 0xe9):
        d = struct.unpack_from("<i", tb, i + 1)[0]
        rel.setdefault((tbase + i + 5 + d) & 0xffffffff, []).append((tbase + i, "call" if tb[i] == 0xe8 else "jmp"))
for t in targets:
    pat = struct.pack("<I", t)
    print("target %08x:" % t)
    for n, b in secs.items():
        base = segs[n]
        i = b.find(pat)
        while i >= 0:
            a = base + i
            print("   abs %-6s %08x  %-28s %s" % (n, a, owner(a) if n == ".text" else "", b[max(0, i - 6):i + 10].hex()))
            i = b.find(pat, i + 1)
    for a, k in rel.get(t, []):
        print("   rel %-4s %08x  %s" % (k, a, owner(a)))
