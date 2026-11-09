"""Symbolic trace of a straight-line x87 block of an assembled function (a reading aid for writing the C).
Prints every store to memory as `slot = expr`, where f(...) marks a value rounded to float by an FSTP / FST m32 and
loads of an earlier stored slot read that rounded value back.
usage: python -I x87sym.py <function> <first offset hex> <last offset hex>   (offsets as fdiff.py prints them)"""
import os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fdiff import body

name, lo, hi = sys.argv[1], int(sys.argv[2], 16), int(sys.argv[3], 16)
st = []
mem = {}
regs = {}


def m(op):
    op = op.replace("dword ptr ", "").strip()
    return op


def load(op):
    k = m(op)
    if k in mem:
        return mem[k]
    return k


def sti(op):
    mm = re.match(r"st\((\d)\)", op.strip())
    return int(mm.group(1)) if mm else (0 if op.strip() == "st" else None)


for line in body(name):
    mm = re.match(r"\s*([0-9a-f]+): (\S+)\s*(.*)", line)
    if not mm:
        continue
    off, ins, ops = int(mm.group(1), 16), mm.group(2), mm.group(3)
    if off < lo or off > hi:
        continue
    args = [a.strip() for a in ops.split(",")] if ops else []
    if ins in ("mov", "lea", "shl", "add", "sub", "xor", "cmp", "test", "dec", "inc", "jnz", "jz", "jmp", "jl", "jle",
               "jg", "jge", "fnstsw", "push", "pop", "or", "and", "setg"):
        if ins in ("mov", "lea") and len(args) == 2 and not args[0].startswith("dword"):
            regs[args[0]] = args[1]
        print("    ; %x %s %s" % (off, ins, ops))
        continue
    if ins == "fld":
        i = sti(args[0])
        st.insert(0, st[i] if i is not None else load(args[0]))
    elif ins in ("fst", "fstp"):
        i = sti(args[0])
        if i is not None:
            st[i] = st[0]
        else:
            k = m(args[0])
            v = "f(%s)" % st[0]
            print("%x: %s = %s" % (off, k, v))
            mem[k] = "[%s]" % k if False else v
        if ins == "fstp":
            st.pop(0)
    elif ins == "fxch":
        i = sti(args[0]) if args else 1
        st[0], st[i] = st[i], st[0]
    elif ins in ("fadd", "fsub", "fsubr", "fmul", "fdiv", "fdivr"):
        sym = {"fadd": "+", "fsub": "-", "fsubr": "-", "fmul": "*", "fdiv": "/", "fdivr": "/"}[ins]
        rev = ins.endswith("r")
        if len(args) == 2:  # fop st, st(i)  or fop st(i), st
            d, s = sti(args[0]), sti(args[1])
            a, b = st[d], st[s]
        else:
            d = 0
            a, b = st[0], (load(args[0]) if sti(args[0]) is None else st[sti(args[0])])
        st[d] = "(%s %s %s)" % ((b, sym, a) if rev else (a, sym, b))
    elif ins in ("faddp", "fsubp", "fsubrp", "fmulp", "fdivp", "fdivrp"):
        sym = {"faddp": "+", "fsubp": "-", "fsubrp": "-", "fmulp": "*", "fdivp": "/", "fdivrp": "/"}[ins]
        i = sti(args[0]) if args else 1
        a, b = st[i], st[0]
        st[i] = "(%s %s %s)" % ((b, sym, a) if ins.endswith("rp") else (a, sym, b))
        st.pop(0)
    elif ins == "fchs":
        st[0] = "-%s" % st[0]
    elif ins in ("fcom", "fcomp"):
        print("%x: compare %s with %s" % (off, st[0], args[0] if args else "st1"))
        if ins == "fcomp":
            st.pop(0)
    else:
        print("?? %x %s %s" % (off, ins, ops))
print("stack at end:", st)
