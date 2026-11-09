"""Compare the pointers build/gendata.py writes into the data image (obj/<PROG>/data.s: `.long <symbol>` lines) with
the base relocations of the ORIGINAL program (its .reloc section lists every absolute address the linker emitted).
A `.long` that the original does not relocate is a value that only looks like an address (false pointer: the rebuilt
image changes the value); an original relocation that data.s writes as bytes is a missed pointer.
usage: python -I relocheck.py <original PE> <obj/<PROG>/data.s> <raw/<PROG>/sections.json>"""
import json
import re
import struct
import sys

pe = open(sys.argv[1], "rb").read()
pe_off = struct.unpack_from("<I", pe, 0x3c)[0]
nsec = struct.unpack_from("<H", pe, pe_off + 6)[0]
opt = pe_off + 24
magic = struct.unpack_from("<H", pe, opt)[0]
base = struct.unpack_from("<I", pe, opt + 28)[0]
dd = opt + 96
reloc_rva, reloc_size = struct.unpack_from("<II", pe, dd + 5 * 8)
sects = []
so = opt + struct.unpack_from("<H", pe, pe_off + 20)[0]
for i in range(nsec):
    name = pe[so + 40 * i: so + 40 * i + 8].rstrip(b"\0").decode()
    vsize, va, rsize, rptr = struct.unpack_from("<IIII", pe, so + 40 * i + 8)
    sects.append((name, va, vsize, rptr, rsize))


def rva2off(rva):
    for n, va, vs, rp, rs in sects:
        if va <= rva < va + max(vs, rs):
            return rp + rva - va
    raise ValueError(hex(rva))


relocs = set()
p, end = rva2off(reloc_rva), rva2off(reloc_rva) + reloc_size
while p < end:
    page, size = struct.unpack_from("<II", pe, p)
    if size == 0:
        break
    for k in range((size - 8) // 2):
        e = struct.unpack_from("<H", pe, p + 8 + 2 * k)[0]
        if e >> 12 == 3:
            relocs.add(base + page + (e & 0xfff))
    p += size

# walk data.s: track the address of every emitted item inside the dumped sections
secinfo = {s["name"]: s for s in json.load(open(sys.argv[3]))}
sym_base = {"_sect_rdata": int(secinfo[".rdata"]["start"], 16), "_sect_data": int(secinfo[".data"]["start"], 16)}
addr = None
ptrs = {}
for line in open(sys.argv[2]):
    line = line.split("#")[0].strip() if not line.strip().startswith(".byte") else line.strip()
    if line.startswith("_sect_rdata:") or line.startswith("_sect_data:"):
        addr = sym_base[line[:-1]]
    elif line == ".text" or line.startswith("_sect_text:"):
        addr = None
    elif addr is None:
        continue
    elif line.startswith(".byte"):
        addr += len(line[5:].split(","))
    elif line.startswith(".zero"):
        addr += int(line.split()[1])
    elif line.startswith(".long"):
        v = line[5:].strip()
        if not re.fullmatch(r"0x[0-9a-f]+|\d+", v):
            ptrs[addr] = v
        addr += 4
lo = min(sym_base.values())
in_img = {r for r in relocs if lo <= r < int(secinfo[".data"]["start"], 16) + secinfo[".data"]["size"]}
false_ptr = sorted(a for a in ptrs if a not in relocs)
missed = sorted(a for a in in_img if a not in ptrs)
print("original relocations in .rdata/.data: %d, pointers in data.s: %d" % (len(in_img), len(ptrs)))
print("false pointers (relocated by data.s, not by the original): %d" % len(false_ptr))
for a in false_ptr:
    print("   %08x  %s" % (a, ptrs[a]))
print("missed pointers (relocated by the original, bytes in data.s): %d" % len(missed))
raw = {}
for n, s in secinfo.items():
    raw[n] = (int(s["start"], 16), open(sys.argv[3].replace("sections.json", "sections/" + s["file"]), "rb").read())
lo_d, hi_d = lo, int(secinfo[".data"]["start"], 16) + secinfo[".data"]["size"]
fixable = []
for a in missed:
    st, b = raw[".rdata"] if a < raw[".data"][0] else raw[".data"]
    v = struct.unpack_from("<I", b + b"\0" * 8, a - st)[0]
    kind = "data pointer" if lo_d <= v < hi_d else "code address"
    if kind == "data pointer" and a % 4 == 0:
        fixable.append(a)
    print("   %08x -> %08x  %s%s" % (a, v, kind, "" if a % 4 == 0 else " (unaligned)"))
if len(sys.argv) > 4:   # --json <prog>: the names/data_relocs.json entry
    print(json.dumps({sys.argv[5]: {"not_pointers": ["%08x" % a for a in false_ptr],
                                    "pointers": ["%08x" % a for a in fixable]}}, indent=1))
