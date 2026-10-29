"""Give untyped globals that the C tree treats as pointers the same type in Ghidra.

build_src.py infers `extern int *DAT_1002bf6c;` from copies such as
`DAT_1002bf6c = piVar3;`, but Ghidra decompiles arithmetic on an untyped global in
bytes (`DAT_1002bf6c + 0x1c`), which C then scales by the element size. Setting the
pointer type in Ghidra makes the decompiler print `DAT_1002bf6c + 7`, consistent
with the C declaration. The change is journaled, so tools/export_changed.py
re-exports every function that uses the global.

Usage: python -I type_pointer_globals.py [--dry] [prog...]
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DECL_RE = re.compile(r"^extern (.+?)\s*\*\s*(DAT_([0-9a-f]{8}));")
ARITH_RE = re.compile(r"\b(DAT_[0-9a-f]{8})\s*[-+]\s*(?!=)")  # any + / - after the symbol


def candidates(prog):
    src = os.path.join(ROOT, "src", prog)
    ptrs = {}
    for line in open(os.path.join(src, "globals.h"), encoding="utf-8"):
        m = DECL_RE.match(line)
        if m:
            ptrs[m.group(2)] = m.group(1).strip() + " *"
    arith = set()
    for f in os.listdir(src):
        if f.endswith(".c"):
            arith |= set(ARITH_RE.findall(open(os.path.join(src, f), encoding="utf-8", errors="replace").read()))
    return {n: t for n, t in ptrs.items() if n in arith}


def main():
    dry = "--dry" in sys.argv
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or list(export_raw.PROGRAMS)
    for prog in names:
        path = export_raw.PROGRAMS[prog]
        cands = candidates(prog)
        print(f"{prog}: {len(cands)} pointer globals used with byte offsets")
        for n, t in sorted(cands.items()):
            print(f"  {n}: {t}")
        if dry:
            continue
        g.ensure_current(path)
        ok = 0
        applied = {}
        for n, t in sorted(cands.items()):
            if t.startswith(("undefined4", "undefined ", "code", "undefined1")):
                t = "void *" if t.startswith("undefined ") else t.replace("undefined4", "int").replace("undefined1", "char")
            r = g.post("apply_data_type", program=path, address=n[4:], type_name=t)
            if "Successfully" in str(r) or (isinstance(r, dict) and r.get("success")):
                ok += 1
                applied[n[4:]] = t
            else:
                print("  failed", n, t, str(r)[:150])
        print(f"{prog}: typed {ok}")
        # build_src.py declares PTR_<addr> with the pointee type applied here
        side = os.path.join(ROOT, "raw", prog, "ptr_types.json")
        known = json.load(open(side)) if os.path.exists(side) else {}
        known.update(applied)
        json.dump(known, open(side, "w"), indent=1)
    if not dry:
        g.ensure_current(g.EXE)
        print(str(g.post("save_all_programs"))[:60])


if __name__ == "__main__":
    main()
