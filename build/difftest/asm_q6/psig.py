"""Reading aid (agent q6): compare the perspective spans by their x87 instruction sequence (stack slots, registers and
constant addresses normalised: [EBP+..] -> S, rdata constants -> their value) and print, per function, how its x87
sequence and its integer instructions differ from a reference function.
usage: psig.py <reference> <name...>   (-x87: only the x87 diff, -int: only the integer diff)"""
import difflib
import os
import re
import struct
import sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', 'asm_q4'))
from fdiff import body

ROOT = os.path.join(HERE, '..', '..', '..')
raw = os.path.join(ROOT, 'raw', 'GRIMFANDANGO.EXE', 'sections')
RD = open(os.path.join(raw, 'rdata.bin'), 'rb').read()


def norm(ins):
    ins = re.sub(r'^\s*[0-9a-f]+: ', '', ins)
    ins = re.sub(r'_sect_rdata\+0x([0-9a-f]+)', lambda m: 'K%g' % struct.unpack_from('<f', RD, int(m.group(1), 16))[0], ins)
    ins = re.sub(r'\[EBP\+-?0x[0-9a-f]+\]', 'S', ins)
    ins = re.sub(r'\[EBP\+0xffffff[0-9a-f]+\]', 'S', ins)
    ins = re.sub(r'\b(EAX|EBX|ECX|EDX|ESI|EDI)\b', 'R', ins)
    ins = re.sub(r'\b(AL|BL|CL|DL|AX|BX|CX|DX|SI|DI)\b', 'r', ins)
    ins = re.sub(r'L[0-9a-f]+\b', 'L', ins)
    return ins


def split(name):
    b = body(name)
    x = [norm(i) for i in b if re.match(r'\s*[0-9a-f]+: f', i)]
    n = [norm(i) for i in b if re.match(r'\s*[0-9a-f]+: [^f]', i)]
    return x, n


args = [a for a in sys.argv[1:] if not a.startswith('-')]
ref = split('rdRaster_' + args[0] if not args[0].startswith('rdRaster') else args[0])
for n in args[1:]:
    nn = 'rdRaster_' + n if not n.startswith('rdRaster') else n
    x, i = split(nn)
    print('==== %s vs %s' % (nn, args[0]))
    if '-int' not in sys.argv:
        print('-- x87:')
        for d in difflib.unified_diff(ref[0], x, lineterm='', n=0):
            if not d.startswith(('---', '+++')):
                print(d)
    if '-x87' not in sys.argv:
        print('-- int:')
        for d in difflib.unified_diff(ref[1], i, lineterm='', n=0):
            if not d.startswith(('---', '+++')):
                print(d)
