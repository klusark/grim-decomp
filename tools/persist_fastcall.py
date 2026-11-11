"""Store Ghidra's inferred __fastcall signatures so callers pass the register arguments.

Inside a function Ghidra infers `__fastcall(int *param_1)` from the code, but the
stored signature keeps zero parameters, so every caller decompiles as `F()` and the
ECX (EDX) value is lost (FUN_00489820 -> PrimitiveQueue_purge()). Setting the printed
header as the real prototype fixes the call sites. Only functions whose disassembly
reads ECX at entry (verify_ecx.entry_reads_ecx) are touched.

Usage: python -I persist_fastcall.py [--dry] [prog...]
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw
from verify_ecx import entry_reads_ecx

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HDR = re.compile(r"^([A-Za-z_][^(\n]*?)\s+__fastcall\s+(\*?[A-Za-z_]\w*)\((.*)\)\s*$", re.M)


def main():
    dry = "--dry" in sys.argv
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or list(export_raw.PROGRAMS)
    for prog in names:
        path = export_raw.PROGRAMS[prog]
        raw = os.path.join(ROOT, "raw", prog)
        funcs = {f["address"]: f for f in json.load(open(os.path.join(raw, "functions.json")))}
        todo = []
        for addr, f in funcs.items():
            src = os.path.join(raw, "functions", addr + ".c")
            if not os.path.exists(src):
                continue
            m = HDR.search(open(src, encoding="utf-8", errors="replace").read())
            if not m or m.group(2).lstrip("*") != f["name"]:
                continue
            d = g.get("disassemble_function", program=path, address=addr)
            if entry_reads_ecx(d):
                ret = "undefined4" if m.group(1).strip() in ("longlong", "ulonglong") else m.group(1)  # 64-bit returns are decompiler noise
                todo.append((addr, f["name"], "%s __fastcall %s(%s)" % (ret, m.group(2), m.group(3))))
        print(f"{prog}: {len(todo)} fastcall functions read ECX at entry")
        for a, n, p in todo[:5]:
            print("  ", a, p)
        if dry:
            continue
        g.ensure_current(path)
        ok = 0
        for a, n, p in todo:
            r = g.post("set_function_prototype", program=path, function_address=a, prototype=p)
            if "Success" in str(r):
                ok += 1
            else:
                print("  failed", n, str(r)[:100])
        print(f"{prog}: set {ok}")
    if not dry:
        g.ensure_current(g.EXE)
        print(str(g.post("save_all_programs"))[:40])


if __name__ == "__main__":
    main()
