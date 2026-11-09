"""Who uses the data around a slot that build/difftest/r2/relocheck.py reports (a false or a missed pointer)?
usage: python -I relocwho.py <original PE> <PROG> <lo> <hi> [<address> ...]
  <lo>..<hi>: the table that holds the slots (hex). Prints every instruction of the ORIGINAL program whose base
  relocation points into [lo - 0x40, hi) (MSVC indexes tables from a biased base, so a little room below), the function
  that contains it (raw/<PROG>/functions.json) and what the rebuild does with that function (names/lib_replace.json
  category, or a hand-written override), and for every <address> the original value and the function it points into
  (a code address) with the same information.  Run from the repository root."""
import bisect
import json
import re
import struct
import sys
import glob

pe = open(sys.argv[1], "rb").read()
prog = sys.argv[2]
lo, hi = int(sys.argv[3], 16), int(sys.argv[4], 16)
po = struct.unpack_from("<I", pe, 0x3c)[0]
opt = po + 24
base = struct.unpack_from("<I", pe, opt + 28)[0]
rr, rs = struct.unpack_from("<II", pe, opt + 96 + 5 * 8)
n = struct.unpack_from("<H", pe, po + 6)[0]
so = opt + struct.unpack_from("<H", pe, po + 20)[0]
secs = [struct.unpack_from("<IIII", pe, so + 40 * i + 8) for i in range(n)]


def off(rva):
    for vs, va, rsz, rp in secs:
        if va <= rva < va + max(vs, rsz):
            return rp + rva - va
    raise ValueError(hex(rva))


rel = []
p = off(rr)
e = p + rs
while p < e:
    pg, sz = struct.unpack_from("<II", pe, p)
    if not sz:
        break
    for k in range((sz - 8) // 2):
        x = struct.unpack_from("<H", pe, p + 8 + 2 * k)[0]
        if x >> 12 == 3:
            rel.append(base + pg + (x & 0xfff))
    p += sz

fs = json.load(open("raw/%s/functions.json" % prog))
addrs = sorted((int(x["address"], 16), x["name"]) for x in fs)
ks = [a for a, _ in addrs]
lr = json.load(open("names/lib_replace.json")).get(prog, {})
over = set()
for f in glob.glob("build/overrides*.c"):
    for m in re.finditer(r"OVERRIDES:([^\n*]*)|^[A-Za-z_][\w \*]*?\b(\w+)\s*\([^;{]*\)\s*\{", open(f).read(), re.M):
        if m.group(1):
            over.update(m.group(1).split())
        elif m.group(2):
            over.add(m.group(2))
text_end = base + secs[0][1] + secs[0][0]


def func(a):
    i = bisect.bisect_right(ks, a) - 1
    a0, nm = addrs[i]
    cat = [k for k, v in lr.items() if isinstance(v, (list, dict)) and "%08x" % a0 in v]
    how = [("lib_replace " + "/".join(cat))] if cat else []
    if nm in over:
        how.append("hand-written override (build/overrides*.c)")
    how = ", ".join(how) or "compiled from the decompiled C"
    return "%s (%08x, +%x): %s" % (nm, a0, a - a0, how)


print("original instructions referring to %08x..%08x:" % (lo - 0x40, hi))
for r in rel:
    if r >= text_end:
        continue
    v = struct.unpack_from("<I", pe, off(r - base))[0]
    if lo - 0x40 <= v < hi:
        print("   %08x -> %08x  in %s" % (r, v, func(r)))
for a in sys.argv[5:]:
    a = int(a, 16)
    v = struct.unpack_from("<I", pe, off(a - base))[0]
    print("slot %08x = %08x%s" % (a, v, ("  -> code: " + func(v)) if base + 0x1000 <= v < text_end else ""))
