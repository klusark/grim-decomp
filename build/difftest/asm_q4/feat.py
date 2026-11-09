"""Which globals / edge fields each rasteriser function touches (to group the template variants).
usage: python -I feat.py <regex of names>"""
import os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fdiff import body

pat = re.compile(sys.argv[1])
names = []
for line in open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "src", "GRIMFANDANGO.EXE", "asm_funcs.s")):
    m = re.match(r"^_(\w+):\s+#", line)
    if m and pat.fullmatch(m.group(1)):
        names.append(m.group(1))
for n in names:
    b = body(n)
    txt = "\n".join(b)
    g = sorted(set("%x" % (0x4dd000 + int(x, 16)) for x in re.findall(r"_sect_data\+0x([0-9a-f]+)", txt)))
    f = sorted(set(re.findall(r"\[EAX\+0x([0-9a-f]+)\]", txt)), key=lambda s: int(s, 16))
    fl = "fldcw" in txt
    print("%-30s %4d %s | EAX+ %s | fpu=%d fldcw=%d" % (n, len(b), " ".join(g), " ".join(f), txt.count("\tf") + txt.count(" f"), txt.count("fldcw")))
