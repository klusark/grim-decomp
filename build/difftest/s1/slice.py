"""Slices FUN_10004e50 and FUN_10005090 out of the original CHORE.DLL (machine code bytes) into orig.s (agent s1): each
absolute reference to CHORE.DLL data (0x1001xxxx) becomes a .long of the test's symbol of that address; the count of
them is checked against the disassembly (15 each).
usage: python -I slice.py <CHORE.DLL> <out.s>"""
import struct
import sys

FUNCS = {"orig_FUN_10004e50": (0x10004e50, 0x10004f27), "orig_FUN_10005090": (0x10005090, 0x1000515b)}
SYMS = {0x100143a8: "_DAT_100143a8", 0x100143ac: "_DAT_100143ac", 0x100143b0: "_DAT_100143b0", 0x100143b4: "_DAT_100143b4",
        0x100143c4: "_DAT_100143c4", 0x100143c8: "_DAT_100143c8", 0x100143cc: "_DAT_100143cc",
        0x1001020c: "_s_C__grimsrc_libs_chore_Costume_c_1001020c"}
EXPECT = {"orig_FUN_10004e50": 15, "orig_FUN_10005090": 15}
data = open(sys.argv[1], "rb").read()
out = [".text"]
for name, (lo, hi) in FUNCS.items():
    code = data[lo - 0x10001000 + 0x400: hi - 0x10001000 + 0x400]   # (.text: VA 0x10001000 at file offset 0x400)
    out += [".globl _" + name, "_" + name + ":"]
    i, n = 0, 0
    while i < len(code):
        if i + 4 <= len(code):
            v = struct.unpack_from("<I", code, i)[0]
            if 0x10010000 <= v < 0x10020000:
                if v not in SYMS:
                    sys.exit("%s: unknown reference %08x at %x" % (name, v, lo + i))
                out.append("\t.long %s" % SYMS[v])
                i += 4
                n += 1
                continue
        out.append("\t.byte 0x%02x" % code[i])
        i += 1
    if n != EXPECT[name]:
        sys.exit("%s: %d references, expected %d" % (name, n, EXPECT[name]))
open(sys.argv[2], "w").write("\n".join(out) + "\n")
