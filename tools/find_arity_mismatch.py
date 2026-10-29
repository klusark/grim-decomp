"""List C functions that call a known function with a different number of arguments than its prototype.

A call like `lua_getstring(uVar2,&DAT_004dda54)` (one parameter) next to `(*(code *)*ppvVar1)(uVar2)`
means the decompiler gave the pushed arguments to the wrong call; the function is a candidate for
assembly mode (names/asm_extra.json).

Usage: python -I find_arity_mismatch.py [prog]        (default GRIMFANDANGO.EXE)
"""
import re, glob, json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
prog = sys.argv[1] if len(sys.argv) > 1 else "GRIMFANDANGO.EXE"
asm = set(json.load(open(os.path.join(ROOT, "names", "asm_funcs.json"))).get(prog, []))
protos = {}
# the other programs' exports are imports here (`int lua_getstring();`): take their parameter counts
for other in ("LUA.DLL", "CHORE.DLL", "IMUSE.DLL", prog):
    path = os.path.join(ROOT, "src", other, "functions.h")
    if not os.path.exists(path):
        continue
    for line in open(path, encoding="utf-8"):
        m = re.match(r"^[^(]*?\b([A-Za-z_]\w*)\s*\((.*)\);\s*/\*", line)
        if not m or "..." in m.group(2):
            continue
        params = m.group(2).strip()
        if "import" in line:
            continue  # `int f();` import declarations have no parameter list
        protos[m.group(1)] = 0 if params in ("", "void") else params.count(",") + 1


def split_args(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur); cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


CALL = re.compile(r"\b([A-Za-z_]\w*)\(")
total = 0
for f in sorted(glob.glob(os.path.join(ROOT, "src", prog, "*.c"))):
    base = os.path.basename(f)
    if base.startswith("crt") or base == "tmpnam.c":
        continue
    s = open(f, encoding="utf-8").read()
    parts = re.split(r"(?m)^/\* ---- 0x([0-9a-f]+)  (\S+) ---- \*/", s)
    for i in range(1, len(parts), 3):
        addr, name, body = parts[i], parts[i + 1], parts[i + 2]
        if addr in asm or body.lstrip().startswith("/* replaced"):
            continue
        bad = []
        for m in CALL.finditer(body):
            fn = m.group(1)
            if fn not in protos or fn == name:
                continue
            j, depth = m.end(), 1
            while j < len(body) and depth:
                depth += (body[j] == "(") - (body[j] == ")")
                j += 1
            args = split_args(body[m.end():j - 1])
            if len(args) != protos[fn]:
                bad.append("%s/%d (declared %d)" % (fn, len(args), protos[fn]))
        if bad:
            total += 1
            print("%s %s %s: %s" % (base, addr, name, ", ".join(bad[:3])))
print(total, "functions")
