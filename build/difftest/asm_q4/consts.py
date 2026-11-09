"""Print the float constants (and other dwords) the rasteriser functions read from .rdata / .data.
usage: python -I consts.py [function names...]   (default: every rdRaster function of src/GRIMFANDANGO.EXE/asm_funcs.s)"""
import os, re, struct, sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..")
raw = os.path.join(ROOT, "raw", "GRIMFANDANGO.EXE", "sections")
sec = {"rdata": (0x4d7000, open(os.path.join(raw, "rdata.bin"), "rb").read()),
       "data": (0x4dd000, open(os.path.join(raw, "data.bin"), "rb").read())}
want = set(sys.argv[1:])
cur = None
seen = {}
for line in open(os.path.join(ROOT, "src", "GRIMFANDANGO.EXE", "asm_funcs.s")):
    m = re.match(r"^_(\w+):\s+#", line)
    if m:
        cur = m.group(1)
        continue
    if not cur or (want and cur not in want) or (not want and not cur.startswith("rdRaster")):
        continue
    for m in re.finditer(r"(dword|qword|word) ptr \[(?:[A-Z]+\*0x\d\+)?_sect_(rdata|data)\+0x([0-9a-f]+)\]", line):
        size, s, off = m.group(1), m.group(2), int(m.group(3), 16)
        base, b = sec[s]
        if off + 8 > len(b):
            continue
        key = (s, off, size)
        if key in seen:
            seen[key].add(cur)
            continue
        seen[key] = {cur}
for (s, off, size), fs in sorted(seen.items()):
    base, b = sec[s]
    if size == "dword":
        v = "%r (0x%08x)" % (struct.unpack_from("<f", b, off)[0], struct.unpack_from("<I", b, off)[0])
    elif size == "qword":
        v = "%r" % struct.unpack_from("<d", b, off)[0]
    else:
        v = "0x%04x" % struct.unpack_from("<H", b, off)[0]
    print("%s+0x%x = 0x%08x %-5s %s   %s" % (s, off, base + off, size, v, " ".join(sorted(fs))[:100]))
