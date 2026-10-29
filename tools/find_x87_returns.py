"""Find functions that return their value in the x87 register (float / double results).

MSVC returns float and double in ST(0). Ghidra only models that when the prototype says so, so
`real luaL_check_number(int)` decompiles as `void f(int)` and every caller loses the value.
A callee returns in ST(0) when the instruction after a call to it consumes ST(0) (FSTP, FADD,
FMUL, FCOMP ...); a dword operand means float, a qword operand double.

Pass 1 (scan):  raw/<prog>/x87_returns.json  {key: {"type": "float"|"double", "votes": n}}
                key = a direct callee address ("10002aa0") or an import name ("lua_getnumber").
Pass 2 (--apply): rewrites the return type in Ghidra, keeping name, convention and parameters.

Usage: python -I find_x87_returns.py [--apply] [prog...]
"""
import json, os, re, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INSN = re.compile(r"^([0-9a-f]+):\s+(\w+)\s*(.*?)\s*$")
CONSUME = re.compile(r"^(FSTP|FST|FISTP|FIST|FADD|FADDP|FSUB|FSUBP|FSUBR|FSUBRP|FMUL|FMULP|FDIV|FDIVP|FDIVR|FDIVRP|"
                     r"FCOM|FCOMP|FCOMPP|FUCOM|FUCOMP|FUCOMPP|FCOMI|FCOMIP|FCHS|FABS|FSQRT|FXCH|FRNDINT|FSIN|FCOS|FPATAN|"
                     r"FIADD|FISUB|FIMUL|FIDIV)$")
SKIP = {"ADD", "POP", "NOP", "MOV", "LEA", "PUSH"}  # cleanup between the call and its consumer
DIRECT = re.compile(r"^0x([0-9a-f]+)$")
SLOT = re.compile(r"^dword ptr \[0x([0-9a-f]{8})\]$")


def slot_names(prog):
    out = {}
    path = os.path.join(ROOT, "raw", prog, "data_items.txt")
    for line in open(path, encoding="utf-8", errors="replace"):
        m = re.match(r"^PTR_(\w+)_([0-9a-f]{8}) @ ([0-9a-f]{8}) ", line)
        if m:
            out[m.group(3)] = m.group(1)
    return out


def scan(prog, path):
    funcs = json.load(open(os.path.join(ROOT, "raw", prog, "functions.json")))
    slots = slot_names(prog)
    votes = collections.defaultdict(collections.Counter)
    for i, f in enumerate(funcs):
        if f.get("isThunk") or f.get("isExternal"):
            continue
        lines = g.get("disassemble_function", program=path, address=f["address"]).splitlines()
        insns = [m.groups() for m in (INSN.match(l) for l in lines) if m]
        for k, (addr, mn, ops) in enumerate(insns):
            if mn != "CALL":
                continue
            m = DIRECT.match(ops)
            s = SLOT.match(ops)
            key = ("%08x" % int(m.group(1), 16)) if m else (slots.get(s.group(1)) if s else None)
            if not key:
                continue
            for mn2, ops2 in [(b, c) for _, b, c in insns[k + 1:k + 5]]:
                if mn2 in SKIP and not (mn2 == "MOV" and "ST" in ops2):
                    continue
                if CONSUME.match(mn2):
                    kind = "double" if "qword" in ops2 else "float"
                    votes[key][kind] += 1
                break
        if i % 300 == 0:
            print(f"  {prog}: {i}/{len(funcs)}", flush=True)
    out = {}
    for k, c in votes.items():
        t = "double" if c["double"] > c["float"] else "float"
        out[k] = {"type": t, "votes": sum(c.values())}
    json.dump(out, open(os.path.join(ROOT, "raw", prog, "x87_returns.json"), "w"), indent=1)
    print(f"{prog}: {len(out)} functions return in ST(0)", flush=True)
    return out


HDR = re.compile(r"^([A-Za-z_][^(\n]*?)\s+(?:(__\w+)\s+)?(\*?[A-Za-z_]\w*)\((.*)\)\s*$", re.M)


def apply(prog, path):
    raw = os.path.join(ROOT, "raw", prog)
    found = json.load(open(os.path.join(raw, "x87_returns.json")))
    funcs = {f["address"]: f for f in json.load(open(os.path.join(raw, "functions.json")))}
    byname = {f["name"]: f for f in funcs.values()}
    g.ensure_current(path)
    ok = bad = 0
    for key, info in sorted(found.items()):
        f = funcs.get(key) or byname.get(key)
        if not f:
            continue
        src = os.path.join(raw, "functions", f["address"] + ".c")
        sig = None
        if os.path.exists(src):
            m = HDR.search(open(src, encoding="utf-8", errors="replace").read())
            if m and m.group(3).lstrip("*") == f["name"]:
                sig = (m.group(2) or "", m.group(4))
        if sig is None:
            try:
                cur = json.loads(g.get("get_function_signature", program=path, address=f["address"])).get("signature", "")
            except Exception:
                cur = ""
            m = re.match(r"^.*?\s+(?:(__\w+)\s+)?\*?" + re.escape(f["name"]) + r"\((.*)\)\s*$", cur)
            sig = (m.group(1) or "", m.group(2)) if m else ("", "")
        cc, params = sig
        proto = "%s %s %s(%s)" % (info["type"], cc or "__cdecl", f["name"], params or "void")
        r = g.post("set_function_prototype", program=path, function_address=f["address"], prototype=proto)
        if "Success" in str(r):
            ok += 1
        else:
            bad += 1
            if bad <= 10:
                print("  failed", f["name"], proto[:80], str(r)[:100])
    print(f"{prog}: x87 return types set {ok}, failed {bad}")


if __name__ == "__main__":
    do_apply = "--apply" in sys.argv
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or list(export_raw.PROGRAMS)
    for n in names:
        path = export_raw.PROGRAMS[n]
        if do_apply and os.path.exists(os.path.join(ROOT, "raw", n, "x87_returns.json")):
            apply(n, path)
        else:
            scan(n, path)
    if do_apply:
        g.ensure_current(g.EXE)
        print(str(g.post("save_all_programs"))[:40])
