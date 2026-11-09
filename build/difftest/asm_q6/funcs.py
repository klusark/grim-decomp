"""Reading aid (agent q6): the functions of a base assembly file (name -> list of (address, instruction)) and the q6 list
(the non-z-buffered half of the software rasteriser, 0x0040ea50 - 0x0042d190, plus rdRaster_DrawWireframeZ)."""
import re


def load(path):
    funcs, cur = {}, None
    for l in open(path):
        l = l.rstrip('\n')
        m = re.match(r'^_(\w+):\s+#', l)
        if m:
            cur = funcs.setdefault(m.group(1), [])
            continue
        m = re.match(r'^\.L(\w+)_(\w+):\t(.*)$', l)
        if m and cur is not None:
            cur.append((m.group(2), m.group(3)))
        elif l.startswith('\t.def'):
            cur = None
    return funcs


def q6_names(path, F=None):
    F = F or load(path)
    out = []
    for n, ins in F.items():
        a = int(ins[0][0], 16)
        if 0x0040ea50 <= a < 0x0042d190 or a == 0x42dd10:
            out.append(n)
    return out
