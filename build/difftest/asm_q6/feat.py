"""Reading aid (agent q6): globals (1.01 addresses; w = written), calls and x87 counts of each q6 function.
usage: feat.py [name regex]"""
import os
import re
import sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from funcs import load, q6_names

src = os.path.join(HERE, '..', '..', '..', 'src', 'GRIMFANDANGO.EXE', 'asm_funcs.s')
F = load(src)
pat = re.compile(sys.argv[1] if len(sys.argv) > 1 else '.*')
allg = {}
for n in q6_names(src, F):
    if not pat.search(n):
        continue
    g, w, calls, offs = set(), set(), set(), set()
    for a, ins in F[n]:
        for x in re.findall(r'_sect_(data|rdata)\+0x([0-9a-f]+)', ins):
            addr = (0x4dd000 if x[0] == 'data' else 0x4d0000) + int(x[1], 16)
            g.add(addr)
            op = ins.split()[0]
            dst = ins[len(op):].split(',')[0]
            if '_sect_' in dst and not op.startswith(('cmp', 'test', 'fld', 'fild', 'fcom', 'fadd', 'fsub', 'fmul', 'fdiv', 'push')):
                w.add(addr)
        m = re.match(r'call (\S+)', ins)
        if m:
            calls.add(m.group(1))
        for x in re.findall(r'offset (_\w+)', ins):
            calls.add('&' + x)
    for a in g:
        allg.setdefault(a, set()).add(n)
    fp = sum(1 for a, i in F[n] if i.startswith('f'))
    print('%-28s %4d fpu %3d fldcw %2d | %s | calls %s' % (n, len(F[n]), fp, sum(1 for a, i in F[n] if i.startswith('fldcw')),
          ' '.join('%x%s' % (a, 'w' if a in w else '') for a in sorted(g)), ' '.join(sorted(calls))))
if len(sys.argv) > 2:
    for a in sorted(allg):
        print('%x %d' % (a, len(allg[a])))
