"""Retype functions that read ECX as an input as __thiscall.

MSVC passes `this` in ECX and the other arguments on the stack, and the callee
pops them.  Ghidra marks these functions with the default convention, so the
decompiler shows `in_ECX` inside the body and drops ECX at every call site
(ExecutionState_Construct(a1, a2, a3) lost the object it initialises).  Declaring
`__thiscall` with an explicit first parameter makes the callers pass it.

The number of stack arguments comes from the function's `RET imm` (see
find_stdcall.py): thiscall is callee-pop, so a plain RET means no stack args.

Usage: python -I fix_ecx_args.py [--dry] [prog...]
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ECX_RE = re.compile(r"\bin_ECX\b")


def signature(code, name):
    """-> (return type, calling convention or '') from the decompiled header."""
    m = re.search(r"^([A-Za-z_][\w \*]*?)\s*\*?\s*(__\w+\s+)?\*?" + re.escape(name) + r"\s*\(", code, re.M)
    if not m:
        return None
    text = code[m.start():m.end()]
    ret = re.sub(r"\b" + re.escape(name) + r"\s*\($", "", text).strip()
    cc = (m.group(2) or "").strip()
    ret = re.sub(r"__\w+", "", ret).strip()
    return ret or "undefined4", cc


def main():
    dry = "--dry" in sys.argv
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or list(export_raw.PROGRAMS)
    for prog in names:
        path = export_raw.PROGRAMS[prog]
        raw = os.path.join(ROOT, "raw", prog)
        funcs = json.load(open(os.path.join(raw, "functions.json")))
        sc = {}
        sc_path = os.path.join(raw, "stdcall_funcs.json")
        if os.path.exists(sc_path):
            sc = json.load(open(sc_path))
        verdict = {}
        vp = os.path.join(raw, "ecx_verdict.json")
        if os.path.exists(vp):
            verdict = json.load(open(vp))
        todo = []
        for f in funcs:
            if f.get("isThunk") or f.get("isExternal"):
                continue
            src = os.path.join(raw, "functions", f["address"] + ".c")
            if not os.path.exists(src):
                continue
            code = open(src, encoding="utf-8", errors="replace").read()
            # in_ECX: not yet typed; pThis: an earlier run of this script added a
            # second `this` (Ghidra supplies one itself for __thiscall)
            if not ECX_RE.search(code) and "pThis" not in code:
                continue
            sig = signature(code, f["name"])
            if sig is None:
                print("  no signature for", f["name"], f["address"])
                continue
            ret, cc = sig
            if cc == "__fastcall" or (cc == "__thiscall" and "pThis" not in code):
                continue
            if verdict and not verdict.get(f["address"], {}).get("entry_read"):
                continue  # verify_ecx.py: ECX is not an input here
            nbytes = int(sc.get(f["address"], {}).get("bytes", 0))
            # Ghidra adds the implicit `this` (ECX) to a __thiscall prototype itself
            params = ["int a%d" % (i + 1) for i in range(nbytes // 4)] or ["void"]
            ret = "void *" if ret in ("void", "undefined") else ret
            todo.append((f["address"], f["name"], "%s __thiscall %s(%s)" % (ret, f["name"], ", ".join(params))))
        print(f"{prog}: {len(todo)} functions read ECX")
        for a, n, proto in todo[:6]:
            print("  ", a, proto)
        if dry:
            continue
        g.ensure_current(path)
        ok = 0
        for a, n, proto in todo:
            r = g.post("set_function_prototype", program=path, function_address=a, prototype=proto)
            if "Success" in str(r):
                ok += 1
            else:
                print("  failed", n, proto, str(r)[:140])
        print(f"{prog}: retyped {ok}")
    if not dry:
        g.ensure_current(g.EXE)
        print(str(g.post("save_all_programs"))[:60])


if __name__ == "__main__":
    main()
