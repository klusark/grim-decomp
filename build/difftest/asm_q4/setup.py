"""Print the set-up part of rasteriser drivers compactly (to the first edge call), with the globals named by address.
usage: python -I setup.py <name> ..."""
import os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fdiff import body


def g(m):
    return "G%x" % (0x4dd000 + int(m.group(1), 16))


for n in sys.argv[1:]:
    out = []
    for l in body(n):
        l = re.sub(r"^\s*[0-9a-f]+: ", "", l)
        if "call _rdRaster_SpanR" in l:
            out.append(l.replace("call _rdRaster_", "CALL "))
            break
        l = re.sub(r"_sect_data\+0x([0-9a-f]+)", g, l).replace("dword ptr ", "").replace("word ptr ", "w")
        out.append(l)
    print("== %s:\n  %s" % (n, " ; ".join(out)))
