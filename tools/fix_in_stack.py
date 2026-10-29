"""Add stack parameters Ghidra missed to function prototypes.

When a function reads `[ESP+0xc]` but its prototype only has two parameters, the decompiler
declares an uninitialised local `in_stack_0000000c` and the C code reads garbage. The offset
(relative to the return address at 0) says which parameter it really is: 4 -> 1st, 8 -> 2nd, ...

Scan (default) lists the candidates; --apply sets the extended prototype in Ghidra (cdecl and
stdcall functions only; thiscall/fastcall numbering differs and is reported, not changed).

Usage: python -I fix_in_stack.py [--apply] [prog...]
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HDR = re.compile(r"^([A-Za-z_][^(\n]*?)\s+(?:(__\w+)\s+)?(\*?[A-Za-z_]\w*)\((.*)\)\s*$", re.M)
DECL = re.compile(r"^\s+([A-Za-z_][\w ]*?\s*\**)\s*in_stack_([0-9a-f]{8});", re.M)
MAX_OFFSET = 0x40


def candidates(prog):
    raw = os.path.join(ROOT, "raw", prog)
    funcs = {f["address"]: f for f in json.load(open(os.path.join(raw, "functions.json")))}
    out = []
    for addr, f in funcs.items():
        p = os.path.join(raw, "functions", addr + ".c")
        if not os.path.exists(p) or f.get("isThunk") or f.get("isExternal"):
            continue
        txt = open(p, encoding="utf-8", errors="replace").read()
        decls = {int(m.group(2), 16): m.group(1).strip() for m in DECL.finditer(txt)}
        decls = {k: v for k, v in decls.items() if 4 <= k <= MAX_OFFSET and k % 4 == 0}
        if not decls:
            continue
        m = HDR.search(txt)
        if not m or m.group(3).lstrip("*") != f["name"]:
            continue
        ret, cc, name, params = m.group(1), m.group(2) or "__cdecl", m.group(3).lstrip("*"), m.group(4).strip()
        plist = [] if params in ("", "void") else [x.strip() for x in params.split(",")]
        out.append(dict(addr=addr, name=name, ret=ret + ("*" if m.group(3).startswith("*") else ""), cc=cc,
                        params=plist, extra=decls))
    return out


def new_prototype(c):
    n = len(c["params"])
    top = max(c["extra"]) // 4
    if top <= n:
        return None  # the "missing" offset is inside the declared parameters: a different problem
    plist = list(c["params"])
    for i in range(n + 1, top + 1):
        t = c["extra"].get(4 * i, "uint")
        if t.startswith("undefined"):
            t = "uint"
        plist.append("%s param_%d" % (t, i))
    return "%s %s %s(%s)" % (c["ret"], c["cc"], c["name"], ", ".join(plist))


if __name__ == "__main__":
    apply = "--apply" in sys.argv
    for prog in [a for a in sys.argv[1:] if not a.startswith("--")] or list(export_raw.PROGRAMS):
        cands = candidates(prog)
        path = export_raw.PROGRAMS[prog]
        if apply:
            g.ensure_current(path)
        done = 0
        for c in cands:
            proto = new_prototype(c)
            if proto is None or c["cc"] in ("__thiscall", "__fastcall"):
                print("  skip", prog, c["addr"], c["name"], c["cc"], sorted(c["extra"]))
                continue
            print("  ", prog, c["addr"], proto)
            if apply:
                r = g.post("set_function_prototype", program=path, function_address=c["addr"], prototype=proto)
                if "Success" in str(r):
                    done += 1
                else:
                    print("    failed:", str(r)[:120])
        print(f"{prog}: {len(cands)} candidates, {done} changed")
    if apply:
        g.ensure_current(g.EXE)
        print(str(g.post("save_all_programs"))[:40])
