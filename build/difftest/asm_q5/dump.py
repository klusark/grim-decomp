"""Dump each q5 function of src/GRIMFANDANGO.EXE/asm_funcs.s normalised (labels relative, globals by address) into
out/fn/<name>.s (a reading aid).  usage: python -I dump.py [names...]  (default: out/mine_names.txt)"""
import os, re, sys
D = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(D, "..", "asm_q4"))
from fdiff import body
names = sys.argv[1:] or open(os.path.join(D, "out", "mine_names.txt")).read().split()
for n in names:
    out = []
    for l in body("rdRaster_" + n):
        l = re.sub(r"_sect_data\+0x([0-9a-f]+)", lambda m: "G%x" % (0x4dd000 + int(m.group(1), 16)), l)
        l = l.replace("dword ptr ", "").replace("word ptr ", "w")
        out.append(l)
    open(os.path.join(D, "out", "fn", n + ".s"), "w").write("\n".join(out) + "\n")
