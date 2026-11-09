"""Reading aid (agent q6): group the q6 functions by similarity of their normalised bodies (q4's fdiff.body), printing
for each function its closest other function, the similarity ratio and the number of differing lines.
usage: groups.py [base asm]"""
import difflib
import os
import re
import sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(HERE, '..', 'asm_q4'))
from funcs import q6_names
from fdiff import body

src = sys.argv[1] if len(sys.argv) > 1 else os.path.join(HERE, '..', '..', '..', 'src', 'GRIMFANDANGO.EXE', 'asm_funcs.s')
names = q6_names(src)
B = {n: [re.sub(r'^\s*[0-9a-f]+: ', '', x) for x in body(n, src)] for n in names}
for n in names:
    best = None
    for m in names:
        if m == n:
            continue
        sm = difflib.SequenceMatcher(None, B[n], B[m], autojunk=False)
        if abs(len(B[n]) - len(B[m])) > max(len(B[n]), len(B[m])) * 0.3:
            continue
        r = sm.ratio()
        if best is None or r > best[0]:
            nd = sum(max(i2 - i1, j2 - j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
            best = (r, m, nd)
    print('%-30s %4d  %s' % (n, len(B[n]), '%-30s %.3f %d' % (best[1], best[0], best[2]) if best else '-'))
