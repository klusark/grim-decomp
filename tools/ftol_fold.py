"""Fold the decompiler's lost x87 result into the conversion that consumes it.

MSVC converts a float to an integer with `CALL _ftol` right after the call that produced the float in ST(0):

    CALL lua_getnumber ; ADD ESP,4 ; CALL _ftol ; (result in EAX/EDX)

Ghidra loses the link and prints

    lua_getnumber(iVar2);
    lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));

where the CONCAT44 operand is two uninitialised register values.  This module rewrites the pair to the intended
`lVar4 = (longlong)lua_getnumber(iVar2);` (a C float -> integer cast truncates exactly like `_ftol`).  It is applied
by tools/build_src.py to the raw text before anything else, and by tools/asm_audit.py so that a function whose only
x87 problem is this pair is no longer a blocker.

Only call statements of functions that return a float are folded (the names come from the generated functions.h).
"""
import os, re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def float_returners(prog="GRIMFANDANGO.EXE"):
    names = {"lua_getnumber"}
    try:
        for line in open(os.path.join(ROOT, "src", prog, "functions.h"), encoding="utf-8"):
            m = re.match(r"^(?:float|double)\s+(?:__\w+\s+)?\*?(\w+)\s*\(", line)
            if m:
                names.add(m.group(1))
    except OSError:
        pass
    return names


def fold(text, names=None):
    """-> text with every `F(args);  X = _ftol((double)CONCAT44(..));` pair replaced by `X = (longlong)F(args);`"""
    names = names or float_returners()
    rx = re.compile(r"^([ \t]*)(%s)\(([^;\n]*)\);[ \t]*\n[ \t]*(\w+) = _ftol\(\(double\)CONCAT44\([^;\n]*\)\);" %
                    "|".join(sorted(map(re.escape, names))), re.M)
    out = rx.sub(lambda m: "%s%s = (longlong)%s(%s);" % (m.group(1), m.group(4), m.group(2), m.group(3)), text)
    # the uninitialised register stand-ins are no longer used
    for var in set(re.findall(r"^\s+undefined4 (unaff_\w+);", out, re.M)):
        if len(re.findall(r"\b%s\b" % var, out)) == 1:
            out = re.sub(r"^\s+undefined4 %s;\n" % var, "", out, flags=re.M)
    return out
