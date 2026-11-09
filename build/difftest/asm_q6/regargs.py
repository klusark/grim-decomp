"""Reading aid (agent q6): per q6 function, the registers read before they are written on the straight line from the
entry (a rough register-argument check; EBP / ESP excluded) and whether the x87 stack is read before anything is
loaded.  usage: regargs.py <base asm_funcs.s>"""
import os
import re
import sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from funcs import load, q6_names

R = ['EAX', 'EBX', 'ECX', 'EDX', 'ESI', 'EDI']
SUB = {'AL': 'EAX', 'AH': 'EAX', 'AX': 'EAX', 'BL': 'EBX', 'BH': 'EBX', 'BX': 'EBX', 'CL': 'ECX', 'CH': 'ECX',
       'CX': 'ECX', 'DL': 'EDX', 'DH': 'EDX', 'DX': 'EDX', 'SI': 'ESI', 'DI': 'EDI'}


def regs(s):
    out = set()
    for t in re.findall(r'\b[A-Z]{2,3}\b', s):
        if t in R:
            out.add(t)
        elif t in SUB:
            out.add(SUB[t])
    return out


F = load(sys.argv[1])
for n in q6_names(sys.argv[1], F):
    written, live, fpu = set(), set(), 0
    fpu_live = False
    for lab, ins in F[n]:
        op = ins.split()[0]
        args = ins[len(op):].strip()
        if op.startswith('f'):
            if op in ('fld', 'fild', 'fld1', 'fldz', 'fldpi'):
                fpu += 1
            elif op.startswith('fst') and op.endswith('p') or op.startswith('fistp') or op.endswith('pp'):
                if fpu == 0:
                    fpu_live = True
                fpu -= 1
            elif op not in ('fldcw', 'fnstcw', 'fnstsw') and fpu == 0:
                fpu_live = True
        if op == 'ret' or op.startswith('j'):
            break
        parts = [p.strip() for p in args.split(',', 1)]
        if op in ('xor', 'sub') and len(parts) == 2 and parts[0] == parts[1]:
            written |= regs(parts[0])
            continue
        if op in ('push', 'cmp', 'test', 'call'):
            live |= regs(args) - written
            if op == 'call':
                written |= {'EAX', 'ECX', 'EDX'}
            continue
        if op == 'pop':
            written |= regs(args)
            continue
        if op in ('mov', 'lea', 'movzx', 'movsx') and len(parts) == 2:
            live |= regs(parts[1]) - written
            if '[' in parts[0]:
                live |= regs(parts[0]) - written
            else:
                written |= regs(parts[0])
            continue
        live |= regs(args) - written
        if parts and '[' not in parts[0]:
            written |= regs(parts[0])
    print('%-32s %-20s %s' % (n, ' '.join(sorted(live)), 'x87 stack read at entry' if fpu_live else ''))
