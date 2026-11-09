"""Reading aid (agent q6): print the pixel loops of the perspective spans (from each read of the texture shift
0x008dded8 to the loop's jnz), to compare the per-pixel code of the variants.
usage: pbody.py [-all] <name...>   (default: the first loop only)"""
import os
import re
import sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', 'asm_q4'))
from fdiff import body

for n in [a for a in sys.argv[1:] if not a.startswith('-')]:
    nn = 'rdRaster_' + n if not n.startswith('rdRaster') else n
    b = body(nn)
    print('==== %s' % nn)
    on = False
    loops = 0
    for x in b:
        m = re.match(r'\s*([0-9a-f]+): (.*)', x)
        if not m:
            continue
        ins = m.group(2)
        mark = '0x400f10' if 'SpanP' in nn else '0x400ed8'   # the texture shift global of the span-list / edge spans
        if not on and mark in ins and ('mov' in ins) and 'sub' not in ins:
            on = True
            print('  --')
        if on:
            print('   ' + x.strip())
            if ins.startswith('jnz'):
                on = False
                loops += 1
                if '-all' not in sys.argv:
                    break
