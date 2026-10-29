"""Undo __thiscall on functions that verify_ecx.py found do not read ECX at entry.

Callee-pop functions (RET imm) go back to `__stdcall` with N int arguments.
Plain-RET (cdecl) functions are deleted and re-created so Ghidra re-infers the
parameters from the stack accesses; the name and plate comment are restored.

Usage: python -I revert_ecx.py [--dry]
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    dry = "--dry" in sys.argv
    for prog, path in export_raw.PROGRAMS.items():
        raw = os.path.join(ROOT, "raw", prog)
        vp = os.path.join(raw, "ecx_verdict.json")
        if not os.path.exists(vp):
            continue
        verdict = json.load(open(vp))
        sc_path = os.path.join(raw, "stdcall_funcs.json")
        sc = json.load(open(sc_path)) if os.path.exists(sc_path) else {}
        bad = {a: v for a, v in verdict.items() if v["thiscall"] and not v["entry_read"]}
        if not bad:
            continue
        g.ensure_current(path)
        for a, v in bad.items():
            nbytes = int(sc.get(a, {}).get("bytes", 0))
            name = v["name"]
            print(f"{prog} {a} {name}: {'stdcall %d args' % (nbytes // 4) if nbytes else 're-derive'}")
            if dry:
                continue
            if nbytes:
                proto = "undefined4 __stdcall %s(%s)" % (name, ", ".join("int a%d" % (i + 1) for i in range(nbytes // 4)))
                print("   ", str(g.post("set_function_prototype", program=path, function_address=a, prototype=proto))[:100])
            else:
                plate = g.get("get_plate_comment", program=path, address=a)
                g.post("delete_function", program=path, address=a)
                r = g.post("create_function", program=path, address=a)
                print("    create:", str(r)[:100])
                g.rename_function(path, a, name)
                text = plate if isinstance(plate, str) else (plate or {}).get("comment", "")
                if text and not text.startswith("{") and "No plate" not in text:
                    g.post("set_plate_comment", program=path, address=a, comment=text.strip())
    if not dry:
        g.ensure_current(g.EXE)
        print(str(g.post("save_all_programs"))[:60])


if __name__ == "__main__":
    main()
