"""Fix callee parameters that are floats but typed int/uint/undefined4.

Symptom in the decompiled C: a float variable is passed as `(int)aspectX` / `(uint)fVar1` to an integer parameter.
The C compiler then converts the value where the original code passes the bits.  The callee's parameter must be
typed float in Ghidra; this tool finds such call sites in raw/<prog>/functions/*.c (low EXE range), looks the callee
up in src/<prog>/functions.h and rewrites its prototype in Ghidra (cdecl/stdcall callees inside the range only;
others are listed).

Usage: python -I fix_float_params.py [--apply]
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROG, PATH = "GRIMFANDANGO.EXE", "/v101/GRIMFANDANGO.EXE"
LO, HI = 0x401000, 0x4a0000


def split_args(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


def main():
    apply = "--apply" in sys.argv
    protos = {}
    for line in open(os.path.join(ROOT, "src", PROG, "functions.h"), encoding="utf-8"):
        m = re.match(r"^(.*?)\b([A-Za-z_]\w*)\s*\((.*)\);\s*/\* 0x([0-9a-f]+)", line)
        if m:
            head, name, params, addr = m.groups()
            protos[name] = (head.strip(), params, addr.zfill(8))
    found = {}   # (callee, index) -> [callers]
    rawdir = os.path.join(ROOT, "raw", PROG, "functions")
    for fn in sorted(os.listdir(rawdir)):
        a = fn[:-2]
        if not LO <= int(a, 16) < HI:
            continue
        text = open(os.path.join(rawdir, fn), encoding="utf-8", errors="replace").read()
        fvars = set(re.findall(r"\b(?:float|double)\s+(\w+)\s*[;,)]", text))   # scalars only (no pointers/arrays)
        for m in re.finditer(r"\b([A-Za-z_]\w*)\(([^;]*)\)\s*;", text):
            callee = m.group(1)
            if callee not in protos or callee in ("if", "while", "for", "switch", "return", "sizeof"):
                continue
            for i, arg in enumerate(split_args(m.group(2))):
                am = re.fullmatch(r"\s*\((?:u?int|undefined4)\)\s*(\w+)\s*", arg)
                if am and am.group(1) in fvars:
                    found.setdefault((callee, i), []).append(a)
    g.ensure_current(PATH)
    bycallee = {}
    for (callee, i), callers in sorted(found.items()):
        bycallee.setdefault(callee, {})[i] = callers
    for callee, idx in sorted(bycallee.items()):
        head, params, addr = protos[callee]
        ps = [p.strip() for p in params.split(",")] if params.strip() not in ("", "void") else []
        for i, callers in sorted(idx.items()):
            print("%s %s param %d (%s): %s" % (addr, callee, i + 1, ps[i] if i < len(ps) else "?", ",".join(callers[:3])))
        if not apply:
            continue
        in_range = LO <= int(addr, 16) < HI
        cc = re.search(r"__(thiscall|fastcall|stdcall)", head)
        if not in_range or (cc and cc.group(1) != "stdcall") or any(i >= len(ps) for i in idx):
            print("   skipped (outside range / thiscall / varargs)")
            continue
        newp = list(ps)
        for i in idx:
            ptype = re.match(r"(.*?)(\**)\s*(\w+)$", ps[i])
            newp[i] = "float " + (ptype.group(3) if ptype else "p%d" % i)
        ret = re.sub(r"__\w+", "", head).strip() or "int"
        proto = "%s %s(%s)" % (ret, callee, ", ".join(newp))
        r = g.set_prototype(PATH, addr, proto, "__" + (cc.group(1) if cc else "cdecl"))
        print("   ->", proto, str(r)[:80])
    return
    for (callee, i), callers in sorted(found.items()):
        head, params, addr = protos[callee]
        ps = [p.strip() for p in params.split(",")] if params.strip() not in ("", "void") else []
        in_range = LO <= int(addr, 16) < HI
        cc = re.search(r"__(thiscall|fastcall|stdcall)", head)
        print("%s %s param %d (%s): %s  %s" % (addr, callee, i + 1, ps[i] if i < len(ps) else "?", ",".join(callers[:3]),
                                              "" if in_range else "[outside range]"))
        if not apply or not in_range or i >= len(ps) or (cc and cc.group(1) != "stdcall"):
            continue
        ptype = re.match(r"(.*?)(\**)\s*(\w+)$", ps[i])
        newp = list(ps)
        newp[i] = "float " + (ptype.group(3) if ptype else "p%d" % i)
        ret = re.sub(r"__\w+", "", head).strip() or "int"
        proto = "%s %s(%s)" % (ret, callee, ", ".join(newp))
        r = g.set_prototype(PATH, addr, proto, "__" + (cc.group(1) if cc else "cdecl"))
        print("   ->", proto, str(r)[:80])
    if apply:
        g.post("save_all_programs")


if __name__ == "__main__":
    main()
