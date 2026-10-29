"""Repair the pointer32 retyping of 4-byte unknown values in the executable.

Something replaced `undefined4` by `pointer32` for locals, parameters and data items in
GRIMFANDANGO.EXE. The bridge refuses `undefined4` (too undefined), so each one becomes
`uint`, which decompiles as plain integer arithmetic with explicit float casts.

Usage: python -I fix_pointer32.py [--dry] [--data]   (locals/params; --data = data items)
Progress goes to stdout; it is safe to rerun (only pointer32 entries are touched).
"""
import json, os, re, sys, time
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NEW = "uint"


def sweep_variables(prog, dry):
    path = export_raw.PROGRAMS[prog]
    funcs = [f for f in json.load(open(os.path.join(ROOT, "raw", prog, "functions.json")))
             if not f.get("isThunk") and not f.get("isExternal")]
    g.ensure_current(path)
    fixed = failed = 0
    t0 = time.time()
    for i, f in enumerate(funcs):
        try:
            r = json.loads(g.get("get_function_variables", program=path, address=f["address"]))
        except Exception:
            continue
        for kind, key, tool in (("param", "parameters", "set_parameter_type"), ("local", "locals", "set_local_variable_type")):
            for v in r.get(key, []):
                if v.get("type") != "pointer32" or v.get("is_phantom"):
                    continue
                if dry:
                    fixed += 1
                    continue
                args = dict(program=path, function_address=f["address"], new_type=NEW)
                args["parameter_name" if kind == "param" else "variable_name"] = v["name"]
                res = g.post(tool, **args)
                if "Success" in str(res):
                    fixed += 1
                else:
                    failed += 1
                    if failed <= 10:
                        print("  failed", f["name"], v["name"], str(res)[:100])
        if i % 200 == 0:
            print(f"  {i}/{len(funcs)} functions, {fixed} retyped, {failed} failed, {time.time()-t0:.0f}s", flush=True)
    print(f"{prog}: retyped {fixed}, failed {failed}")


def sweep_data(prog, dry):
    path = export_raw.PROGRAMS[prog]
    g.ensure_current(path)
    items = []
    for line in open(os.path.join(ROOT, "raw", prog, "data_items.txt"), encoding="utf-8", errors="replace"):
        m = re.match(r"^\S+ @ ([0-9a-f]{8}) \[pointer32\] \(4 bytes?\)", line)
        if m:
            items.append(m.group(1))
    print(f"{prog}: {len(items)} pointer32 data items")
    ok = bad = 0
    for i, a in enumerate(items):
        if dry:
            continue
        r = g.post("apply_data_type", program=path, address=a, type_name=NEW)
        if "Successfully" in str(r) or (isinstance(r, dict) and r.get("success")):
            ok += 1
        else:
            bad += 1
            if bad <= 10:
                print("  failed", a, str(r)[:100])
        if i % 300 == 0:
            print(f"  {i}/{len(items)}", flush=True)
    print(f"{prog}: data items retyped {ok}, failed {bad}")


if __name__ == "__main__":
    dry = "--dry" in sys.argv
    if "--data" in sys.argv:
        sweep_data("GRIMFANDANGO.EXE", dry)
    else:
        sweep_variables("GRIMFANDANGO.EXE", dry)
    if not dry:
        g.ensure_current(g.EXE)
        print(str(g.post("save_all_programs"))[:40])
