"""Find callee-pop (stdcall) functions: those whose disassembly ends in `RET imm`.

Ghidra left every function on the default cdecl model, so Win32 callbacks
(window procedures, DirectDraw/DirectInput enumeration callbacks, dialog
procedures) were compiled without the callee stack clean-up and corrupted the
caller's stack when Windows called them.  Writes raw/<prog>/stdcall_funcs.json:
{address: {"name":..., "bytes": N}} for every function with a non-zero RET imm,
then (with --apply) sets `undefined4 name(int a1..aN)` __stdcall on each.
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RET_RE = re.compile(r"RET 0x([0-9a-f]+)", re.I)


def scan(prog_name, prog_path):
    funcs = json.load(open(os.path.join(ROOT, "raw", prog_name, "functions.json")))
    found = {}
    for i, f in enumerate(funcs):
        if f.get("isThunk") or f.get("isExternal"):
            continue
        d = g.get("disassemble_function", program=prog_path, address=f["address"])
        imms = {int(m.group(1), 16) for m in RET_RE.finditer(d)}
        imms.discard(0)
        skip = json.load(open(os.path.join(ROOT, "names", "not_stdcall.json"))).get(prog_name, [])
        if imms and f["address"] not in skip:
            found[f["address"]] = {"name": f["name"], "bytes": max(imms)}
        if i % 200 == 0:
            print(f"  {prog_name}: {i}/{len(funcs)}", flush=True)
    json.dump(found, open(os.path.join(ROOT, "raw", prog_name, "stdcall_funcs.json"), "w"), indent=1)
    print(prog_name, len(found), "callee-pop functions", flush=True)
    return found


def apply(prog_name, prog_path, found):
    g.ensure_current(prog_path)
    ok = 0
    # functions verify_ecx.py found to read ECX at entry are __thiscall (fix_ecx_args.py)
    verdict = {}
    vp = os.path.join(ROOT, "raw", prog_name, "ecx_verdict.json")
    if os.path.exists(vp):
        verdict = json.load(open(vp))
    for addr, info in found.items():
        if verdict.get(addr, {}).get("entry_read"):
            continue
        n = info["bytes"] // 4
        params = ", ".join("int a%d" % k for k in range(1, n + 1)) or "void"
        r = g.set_prototype(prog_path, addr, "undefined4 %s(%s)" % (info["name"], params), "__stdcall")
        if g.ok(r):
            ok += 1
        else:
            print("  failed", addr, info["name"], str(r)[:100])
    print(prog_name, "stdcall prototypes set:", ok, flush=True)


if __name__ == "__main__":
    do_apply = "--apply" in sys.argv
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or list(export_raw.PROGRAMS)
    for n in names:
        path = export_raw.PROGRAMS[n]
        found = scan(n, path)
        if do_apply:
            apply(n, path, found)
    g.ensure_current(g.EXE)
    print(str(g.post("save_all_programs"))[:40])
