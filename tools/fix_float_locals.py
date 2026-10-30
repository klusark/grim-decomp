"""Retype stack locals that hold floats but were typed uint/int/undefined4 by the decompiler.

Ghidra types a 4-byte stack slot by its first use; when the code first copies the slot as a dword, the decompiled C
then converts instead of copying bits: `local_18 = (uint)lua_getnumber(n)` stores 4.0 as the integer 4.  The cure is
the variable type, so the decompiler prints `float local_18[3]` and plain assignments.

For every function given (or --range lo hi) the tool decompiles, finds the integer locals that are used as floats

  * assigned from a float expression: `local_X = (uint)lua_getnumber(...)`, `= (uint)(float)...`, `= (uint)fVarN`
  * passed by address as a float vector: `(float *)&local_X`, `(float *)&local_X`
  * read back as a float: `(float)local_X`

and retypes the lowest-addressed slot of each run of three consecutive 4-byte slots (a vector) to float[3]
(--scalar keeps single floats as `float`), then decompiles again until nothing changes.  The result is printed;
review it before relying on it.   Usage: python fix_float_locals.py [--dry] [--scalar] addr [addr ...]
"""
import re, sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

PATH = "/v101/GRIMFANDANGO.EXE"
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FRET = {"lua_getnumber"}   # functions that return float/double (names from the generated functions.h)
try:
    for _l in open(os.path.join(ROOT, "src", "GRIMFANDANGO.EXE", "functions.h"), encoding="utf-8"):
        _m = re.match(r"^(?:float|double)\s+(?:__\w+\s+)?\*?(\w+)\s*\(", _l)
        if _m:
            FRET.add(_m.group(1))
except OSError:
    pass
INTTYPES = ("uint", "int", "undefined4", "dword", "long", "ulong")
DECL = re.compile(r"^\s+(\w[\w ]*?)\s+(local_[0-9a-f]+)\s*(\[\d+\])?;", re.M)


def decompile(addr):
    return g.get("decompile_function", program=PATH, address=addr).replace("\r\n", "\n")


def analyse(text):
    """-> (declared {name: (type, isarray)}, flagged set of names)"""
    decl = {}
    for m in DECL.finditer(text):
        decl[m.group(2)] = (m.group(1).strip(), bool(m.group(3)))
    flagged = set()
    for name, (ty, arr) in decl.items():
        if arr or ty not in INTTYPES:
            continue
        n = re.escape(name)
        fnames = set(re.findall(r"\b(?:float|double)\s+\*?(\w+)\s*[;,)\[]", text))
        pats = ([r"\b%s\s*=\s*\(u?int\)\s*\(?[^;\n]*\b(?:%s)\b" % (n, "|".join(map(re.escape, fnames)))] if fnames else []) + [
            r"\b%s\s*=\s*\(u?int\)\s*lua_getnumber" % n,
            r"\b%s\s*=\s*\(u?int\)\s*\(float\)" % n,
            r"\b%s\s*=\s*\(u?int\)\s*[fd]Var\d+" % n,
            r"\b%s\s*=\s*\(u?int\)\s*(?:%s)\(" % (n, "|".join(sorted(FRET))),
            r"\b%s\s*=\s*\(u?int\)\s*\(?[^;\n]*(?:\b\d+\.\d+|\b[fd]Var\d+|\*\(float \*\))" % n,
            r"\(float \*\)\s*&\s*%s\b" % n,
            r"(?s)(?=.*&\s*%s\b).*\(float\)\s*%s\b" % (n, n),   # read back as a float, address passed on
        ]
        if any(re.search(p, text) for p in pats):
            flagged.add(name)
        elif re.search(r"\(float\)\s*%s\b" % n, text) and not re.search(r"\b%s\s*=\s*[^;\n]*(?:&|<<|>>|\|)" % n, text):
            # element of a vector whose first slot has its address taken (a float * argument)
            off = int(name[len("local_"):], 16)
            for y in re.findall(r"&\s*local_([0-9a-f]+)\b", text):
                if 0 <= int(y, 16) - off <= 8:
                    flagged.add(name)
                    break
            # the slots right after a float array (a 3x3 matrix local_30[9] followed by its translation local_c, local_8, local_4)
            for yname, (ty2, arr2) in decl.items():
                if arr2 and ty2 == "float":
                    ym = re.search(r"float\s+%s\s*\[(\d+)\]" % re.escape(yname), text)
                    if ym:
                        end = int(yname[len("local_"):], 16) - 4 * int(ym.group(1))
                        if 0 <= end - off <= 8 or end == off:
                            flagged.add(name)
    return decl, flagged


def plain_move_only(text, name):
    """True when every use of the slot besides its declaration is a plain copy / store of a dword."""
    n = re.escape(name)
    for line in text.split("\n"):
        if not re.search(r"\b%s\b" % n, line) or re.match(r"\s+\w[\w ]*\s+%s\s*(\[\d+\])?;" % n, line):
            continue
        if re.match(r"\s*%s\s*=\s*(\*\(u?int \*\)\(.*\)|\w+|0|0x[0-9a-f]+);\s*$" % n, line):
            continue
        if re.match(r"\s*[\w\[\]\*\(\) +]+\s*=\s*%s;\s*$" % n, line):
            continue
        return False
    return True


def groups(decl, flagged, scalar, text=""):
    def off(n):
        return int(n[len("local_"):], 16)
    ints = {off(n): n for n, (t, a) in decl.items() if t in INTTYPES and not a}
    todo = []
    used = set()
    for o in sorted((off(n) for n in flagged), reverse=True):
        if o in used:
            continue
        if scalar and (o - 4) not in ints and (o + 4) not in ints:
            todo.append((ints[o], "float"))
            used.add(o)
            continue
        run = [o]
        while len(run) < 3 and (run[-1] - 4) in ints and (run[-1] - 4) not in used and                 ((run[-1] - 4) in [int(f[len("local_"):], 16) for f in flagged] or plain_move_only(text, ints[run[-1] - 4])):
            run.append(run[-1] - 4)
        if len(run) == 3:
            todo.append((ints[o], "float[3]"))
        else:
            todo.append((ints[o], "float" if len(run) == 1 else "float[%d]" % len(run)))
        used.update(run)
    return todo


def main():
    dry = "--dry" in sys.argv
    scalar = "--scalar" in sys.argv
    addrs = [a for a in sys.argv[1:] if not a.startswith("--")]
    g.ensure_current(PATH)
    for a in addrs:
        for _ in range(6):
            text = decompile(a)
            decl, flagged = analyse(text)
            todo = groups(decl, flagged, scalar, text)
            if not todo:
                break
            for name, ty in todo:
                print("%s: %s -> %s" % (a, name, ty))
                if not dry:
                    r = g.post("set_local_variable_type", program=PATH, function_address=a, variable_name=name, new_type=ty)
                    if not g.ok(r):
                        print("   failed", str(r)[:200])
            if dry:
                break
        else:
            print(a, "did not settle")


if __name__ == "__main__":
    main()
