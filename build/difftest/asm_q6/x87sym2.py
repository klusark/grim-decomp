"""Reading aid (agent q6): symbolic trace of a straight-line x87 block, like asm_q4/x87sym.py, but integer registers are
tracked too (mov / lea / shl / add / sub / inc / dec of registers and stack slots), so memory operands print in terms of
the starting values.  Every store to memory prints as `slot = expr`; f(...) marks a value rounded to float by an
FSTP / FST m32, and a later load of that slot reads the rounded value back.
usage: x87sym2.py <function> <first offset hex> <last offset hex> [REG=value ...] [[ESP+0x14]=value ...]"""
import os
import re
import sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', 'asm_q4'))
from fdiff import body

name, lo, hi = sys.argv[1], int(sys.argv[2], 16), int(sys.argv[3], 16)
regs = {r: r for r in ('EAX', 'EBX', 'ECX', 'EDX', 'ESI', 'EDI', 'EBP')}
mem = {}
for a in sys.argv[4:]:
    k, v = a.split('=', 1)
    if k.startswith('['):
        mem[k] = v
    else:
        regs[k] = v
st = []


def simp(e):
    e = re.sub(r'\+-', '-', e)
    return e


def addr(op):
    """the symbolic address of a memory operand [..]"""
    inner = re.search(r'\[(.*)\]', op).group(1)
    if 'ESP' in inner:
        return '[%s]' % inner
    out = re.sub(r'\b(EAX|EBX|ECX|EDX|ESI|EDI|EBP)\b', lambda m: '(%s)' % regs[m.group(1)], inner)
    out = out.replace('_sect_data+', 'D+').replace('_sect_rdata+', 'R+')
    return '[%s]' % simp(out)


def val(op):
    op = op.strip()
    if '[' in op:
        k = addr(op)
        return mem.get(k, k)
    if op in regs:
        return regs[op]
    return op


def sti(op):
    m = re.match(r'st\((\d)\)', op.strip())
    return int(m.group(1)) if m else (0 if op.strip() == 'st' else None)


for line in body(name):
    m = re.match(r'\s*([0-9a-f]+): (\S+)\s*(.*)', line)
    if not m:
        continue
    off, ins, ops = int(m.group(1), 16), m.group(2), m.group(3)
    if off < lo or off > hi:
        continue
    ops = ops.replace('dword ptr ', '').replace('word ptr ', '').replace('qword ptr ', '')
    args = [a.strip() for a in ops.split(',')] if ops else []
    if ins in ('mov', 'lea', 'shl', 'add', 'sub', 'inc', 'dec', 'neg', 'imul', 'sar', 'shr', 'and', 'or', 'xor'):
        d = args[0]
        if ins == 'mov':
            v = val(args[1])
        elif ins == 'lea':
            v = addr(args[1])[1:-1]
        elif ins in ('inc', 'dec', 'neg'):
            v = '(%s%s)' % (val(d), {'inc': '+1', 'dec': '-1', 'neg': '*-1'}[ins])
        elif ins == 'xor' and args[0] == args[1]:
            v = '0'
        else:
            v = '(%s %s %s)' % (val(d), {'shl': '<<', 'add': '+', 'sub': '-', 'imul': '*', 'sar': '>>', 'shr': '>>>',
                                         'and': '&', 'or': '|', 'xor': '^'}[ins], val(args[1]))
        if '[' in d:
            k = addr(d)
            mem[k] = v
            print('%x: %s = %s' % (off, k, v))
        else:
            regs[d] = v
        continue
    if not ins.startswith('f'):
        print('    ; %x %s %s' % (off, ins, ops))
        continue
    if ins in ('fld', 'fild'):
        i = sti(args[0])
        st.insert(0, st[i] if i is not None else (('int(%s)' % val(args[0])) if ins == 'fild' else val(args[0])))
    elif ins in ('fld1', 'fldz'):
        st.insert(0, '1' if ins == 'fld1' else '0')
    elif ins in ('fst', 'fstp', 'fistp'):
        i = sti(args[0])
        if i is not None:
            st[i] = st[0]
        else:
            k = addr(args[0])
            v = ('floor_or_cw(%s)' if ins == 'fistp' else 'f(%s)') % st[0]
            print('%x: %s = %s' % (off, k, v))
            mem[k] = v
        if ins != 'fst':
            st.pop(0)
    elif ins == 'fxch':
        i = sti(args[0]) if args else 1
        st[0], st[i] = st[i], st[0]
    elif ins in ('fadd', 'fsub', 'fsubr', 'fmul', 'fdiv', 'fdivr'):
        sym = {'fadd': '+', 'fsub': '-', 'fsubr': '-', 'fmul': '*', 'fdiv': '/', 'fdivr': '/'}[ins]
        rev = ins.endswith('r')
        if len(args) == 2:
            d, s = sti(args[0]), sti(args[1])
            a, b = st[d], st[s]
        else:
            d = 0
            a, b = st[0], (val(args[0]) if sti(args[0]) is None else st[sti(args[0])])
        st[d] = '(%s %s %s)' % ((b, sym, a) if rev else (a, sym, b))
    elif ins in ('faddp', 'fsubp', 'fsubrp', 'fmulp', 'fdivp', 'fdivrp'):
        sym = {'faddp': '+', 'fsubp': '-', 'fsubrp': '-', 'fmulp': '*', 'fdivp': '/', 'fdivrp': '/'}[ins]
        i = sti(args[0]) if args else 1
        a, b = st[i], st[0]
        st[i] = '(%s %s %s)' % ((b, sym, a) if ins.endswith('rp') else (a, sym, b))
        st.pop(0)
    elif ins == 'fchs':
        st[0] = '-%s' % st[0]
    elif ins in ('fcom', 'fcomp', 'fcompp'):
        print('%x: compare %s with %s' % (off, st[0], val(args[0]) if args else st[1]))
        if ins == 'fcomp':
            st.pop(0)
        if ins == 'fcompp':
            st.pop(0); st.pop(0)
    elif ins in ('fldcw', 'fnstsw', 'fnstcw'):
        print('    ; %x %s %s' % (off, ins, ops))
    else:
        print('?? %x %s %s' % (off, ins, ops))
print('stack at end:', st)
