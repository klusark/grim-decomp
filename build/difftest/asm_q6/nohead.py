"""Reading aid (agent q6): print the no-head block of each perspective span (the target of the first `jz` after the
head-count test, up to the run loop), with the x87 stores symbolised, to see which values the u / v / du / dv
registers and slots get when the span starts on a multiple of 16.
usage: nohead.py <name...>"""
import os
import re
import sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', 'asm_q4'))
from fdiff import body

for n in sys.argv[1:]:
    nn = 'rdRaster_' + n if not n.startswith('rdRaster') else n
    b = body(nn)
    lines = [(int(m.group(1), 16), m.group(2)) for m in (re.match(r'\s*([0-9a-f]+): (.*)', x) for x in b) if m]
    # the head test: the first "jz L.." after the first fdiv (1 / p0)
    tgt = None
    fdiv = min(o for o, ins in lines if ins.startswith('fdiv'))
    for o, ins in lines:
        if o > fdiv and ins.startswith('jz'):
            tgt = int(ins.split('L')[1], 16)
            break
    print('==== %s: no-head block at %x' % (nn, tgt if tgt else -1))
    if tgt is None:
        continue
    on = False
    cnt = 0
    for o, ins in lines:
        if o == tgt:
            on = True
        if on:
            print('   %4x: %s' % (o, ins))
            cnt += 1
            if cnt > 16 or ins.startswith('jle') or ins.startswith('jl '):
                break
