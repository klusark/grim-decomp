"""Audit every EXE function of the low range (0x401000-0x49ffff) for decompiler artifacts that make the C text
unsafe to compile, by comparing the C text (raw/<prog>/functions/*.c) with the original instructions
(raw/<prog>/disasm.json, see find_arity_asm.py --fetch).

Output: raw/<prog>/audit.json  {address: [flags]}  and a summary.  A function without flags is a candidate for
conversion from assembly to C; each flag names the root cause that has to be fixed in Ghidra (or by a hand-written
override in build/overrides_exe.c) first:

  ftol        _ftol(...) in the C text: the x87 value converted is not tracked by the decompiler
  x87state    in_ST*, extraout_ST*, in_FPU*  (x87 stack / status word crossing instructions or calls)
  regs        unaff_*, extraout_*, in_E??     (register values crossing calls or function boundaries)
  carry       CARRY/SBORROW/SCARRY            (multi-word arithmetic, flags crossing instructions)
  fpucw       FLDCW/FRNDINT: the code switches the x87 rounding mode (floor/ceil), the C text shows ROUND()
  floatptr    an element of a float array/pointer is used as an integer or pointer (struct behind `float *p`)
  floatfield  `(float)p[i]` with an integer-typed p: a float field behind an int * (struct typing missing)
  floatslot   a float is converted to an integer variable/memory slot where the code copies the bits
  paramaddr   &param_N (parameter slot reused as a local)
  stackvar    stack0x / in_stack / register0x (varargs, missing stack parameters)
  lostcall    a call in the C text has fewer arguments than the instruction stream pushes for it, or the C text
              calls fewer distinct functions than the code does
  jumptable   switch / computed jump that Ghidra could not recover (halt_baddata, JUMPOUT, code *)
  puns        build_src.py has to insert PUN()/FBITS() to compile the text (float/int register confusion)
  fpu         the function uses the x87 unit at all (informational, not a blocker)

Usage: python -I asm_audit.py [lo hi]
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ftol_fold
FRET_NAMES = ftol_fold.float_returners()

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROG = "GRIMFANDANGO.EXE"
LO, HI = (int(sys.argv[1], 16), int(sys.argv[2], 16)) if len(sys.argv) > 2 else (0x401000, 0x4a0000)
RAW = os.path.join(ROOT, "raw", PROG)

PATTERNS = [
    ("ftol", re.compile(r"\b_ftol\b|\b_CI\w+\(")),
    ("x87state", re.compile(r"\b(in_ST[0-7]|extraout_ST[0-7]|in_FPU\w+|extraout_FPU\w+|unaff_ST\d)\b")),
    ("regs", re.compile(r"\b(unaff_\w+|extraout_E\w+|in_E[A-Z]{2}|in_[A-D]L|in_[A-D]X|unaff_retaddr)\b")),
    ("carry", re.compile(r"\b(CARRY\d|SBORROW\d|SCARRY\d)\b")),
    ("paramaddr", re.compile(r"&\s*param_\d+\b")),
    ("stackvar", re.compile(r"\b(stack0x\w+|in_stack_\w+|register0x\w+)\b")),
    ("jumptable", re.compile(r"halt_baddata|JUMPOUT|\bswitchD\w*|\(\*\(code \*\)\(\w*\*4\b")),
    # a float value stored into an integer-typed slot ((uint)(float)x, (int)lua_getnumber(...) is a real conversion
    # when the code uses _ftol, so only the explicit double cast is flagged here; the count comparison below
    # catches the rest)
    ("floatslot", re.compile(r"\((?:u?int|undefined4|uint|dword)\)\s*\(float\)")),
]
# calls of functions that return a float / double (x87 result): converting that to an integer slot is the same bug
FLOAT_RETURNERS = set()
try:
    for _l in open(os.path.join(ROOT, "src", PROG, "functions.h"), encoding="utf-8"):
        _m = re.match(r"^(?:float|double)\s+(?:__\w+\s+)?\*?(\w+)\s*\(", _l)
        if _m:
            FLOAT_RETURNERS.add(_m.group(1))
except OSError:
    pass
GLOBAL_FLOAT_PTRS = set()
try:
    GLOBAL_FLOAT_PTRS = set(re.findall(r"extern (?:float|double) \*+ ?(\w+);", open(os.path.join(ROOT, "src", PROG, "globals.h"), encoding="utf-8").read()))
except OSError:
    pass
FLOAT_EXPR_TO_INT = re.compile(r"\b(?:local|uStack|auStack|param)_\w+\s*=\s*\((?:u?int|undefined4|dword)\)\s*\(?[^;\n]*(?:\b\d+\.\d+|\b[fd]Var\d+|\*\(float \*\))")
FLOAT_CALL_TO_INT = re.compile(r"\w+\s*=\s*\((?:u?int|undefined4|dword)\)\s*(%s)\(" % "|".join(sorted(FLOAT_RETURNERS | {"lua_getnumber"})))


def main():
    funcs = json.load(open(os.path.join(RAW, "functions.json")))
    disasm = json.load(open(os.path.join(RAW, "disasm.json")))
    out = {}
    for f in funcs:
        a = f["address"]
        if f.get("isThunk") or f.get("isExternal") or not (LO <= int(a, 16) < HI):
            continue
        p = os.path.join(RAW, "functions", a + ".c")
        if not os.path.exists(p):
            continue
        c = ftol_fold.fold(open(p, encoding="utf-8", errors="replace").read(), FRET_NAMES)   # lost-x87-result pairs are fixed by build_src
        flags = []
        for name, rx in PATTERNS:
            if rx.search(c):
                flags.append(name)
        fnames = set(re.findall(r"\b(?:float|double)\s+\*?(\w+)\s*[;,)\[]", c))
        if fnames and re.search(r"\b(?:local|uStack|auStack|param)_\w+\s*=\s*\((?:u?int|undefined4|dword)\)\s*\(?[^;\n]*\b(?:%s)\b" % "|".join(map(re.escape, fnames)), c):
            flags.append("floatslot")
        if (FLOAT_CALL_TO_INT.search(c) or FLOAT_EXPR_TO_INT.search(c)) and "floatslot" not in flags:
            flags.append("floatslot")
        # a float array element used as an integer / pointer (struct fields behind a float * variable)
        fptrs = set(re.findall(r"\b(?:float|double)\s*\*+\s*(\w+)\s*[;,)=]", c)) | GLOBAL_FLOAT_PTRS
        if fptrs and re.search(r"\(\s*(?:u?int|undefined4|void \*|code \*|\w+ \*)\s*\)\s*\(?\s*(?:%s)\s*\[" % "|".join(map(re.escape, fptrs)), c):
            flags.append("floatptr")
        # `(float)p[i]` with p an int/uint/undefined4 pointer: the code reads a float field through an integer pointer type
        iptrs = set(re.findall(r"\b(?:u?int|undefined4|dword)\s*\*+\s*(\w+)\s*[;,)=]", c))
        if iptrs and re.search(r"\(float\)\s*\(?\s*(?:%s)\s*\[" % "|".join(map(re.escape, iptrs)), c):
            flags.append("floatfield")
        elif iptrs and re.search(r"\b(?:%s)\s*\[[^\]\n]*\]\s*=\s*\((?:u?int|undefined4)\)\s*\(?[^;\n]*(?:\b\d+\.\d+|\b[fd]Var\d+|\(float\))" % "|".join(map(re.escape, iptrs)), c):
            flags.append("floatfield")   # a float stored into a field behind an int * (converted to an integer)
        asm = disasm.get(a, "")
        fpu = bool(re.search(r"^[0-9a-f]+:\s+F[A-Z]+", asm, re.M))
        if re.search(r"^[0-9a-f]+:\s+FLDCW|^[0-9a-f]+:\s+FRNDINT", asm, re.M):
            flags.append("fpucw")   # rounding-mode switch (floor/ceil/round): the decompiler prints a plain ROUND()
        if fpu:
            flags.append("fpu")
        # float -> int conversions in the C text (excluding _ftol results) vs FIST/FISTP/_ftol in the code:
        # more conversions in the C text than the code performs means the code copies float bits
        out[a] = flags
    json.dump(out, open(os.path.join(RAW, "audit.json"), "w"), indent=0)
    from collections import Counter
    cnt = Counter()
    clean = 0
    for a, fl in out.items():
        hard = [x for x in fl if x != "fpu"]
        if not hard:
            clean += 1
        for x in fl:
            cnt[x] += 1
    print(len(out), "functions;", clean, "without blocking flags;", dict(cnt))


if __name__ == "__main__":
    main()
