import sys, struct
t = open('raw/GRIMFANDANGO.EXE/sections/text.bin', 'rb').read()
B = 0x401000
def rd(a, n): return t[a - B:a - B + n]
# usage: jt.py jtaddr idxaddr nidx bias
jt, idx, n, bias = [int(x, 16) for x in sys.argv[1:5]]
ib = rd(idx, n)
groups = {}
for i, b in enumerate(ib):
    tgt = struct.unpack('<I', rd(jt + 4 * b, 4))[0]
    groups.setdefault(tgt, []).append(hex(i + bias))
for tgt, vals in groups.items():
    print(hex(tgt), vals if len(vals) < 10 else '%d values (default?)' % len(vals))
