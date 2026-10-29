"""Stack-argument analysis for functions that are reassembled (see gen_asm.py).

Walks the instructions tracking the stack pointer delta (push/pop/sub/add esp, call cleanup
is explicit in cdecl code) and records every [ESP+x] access that lands in the argument area.
Result: {argument index (1-based): 'int' | 'float' | 'double'}.
Usage: python -I asm_args.py [--apply] [prog...]   -> compares with the prototype in Ghidra
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw
from gen_asm import INSN, Ctx

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REG = r"(?:E[A-D]X|E[SD]I|EBP)"


def analyze(lines):
    insns = [m.groups() for m in (INSN.match(l) for l in lines) if m]
    delta = 0
    at = {}
    args = {}
    for a, mn, ops in insns:
        up = mn.upper()
        ia = int(a, 16)
        if ia in at:
            delta = at[ia]
        # accesses first (uses the delta before this instruction's own push/pop)
        for m in re.finditer(r"(dword|qword|word|byte|float|double) ptr \[ESP\s*\+\s*0x([0-9a-f]+)\]|\[ESP\s*\+\s*0x([0-9a-f]+)\]", ops):
            x = int(m.group(2) or m.group(3), 16)
            rel = x - delta
            if rel >= 4 and rel % 4 == 0:
                idx = rel // 4
                size = (m.group(1) or "dword")
                kind = "double" if (size in ("qword", "double")) and up.startswith("F") and not up.startswith("FI") else (
                    "float" if size in ("dword", "float") and up.startswith("F") and not up.startswith("FI") else "int")
                if kind == "double":
                    args[idx] = "double"
                    args.setdefault(idx + 1, "double-high")
                elif idx not in args or args[idx] == "int":
                    args[idx] = kind
        if up == "PUSH":
            delta += 4
        elif up == "POP":
            delta -= 4
        elif up == "SUB" and re.fullmatch(r"ESP,0x[0-9a-f]+", ops):
            delta += int(ops.split("0x")[1], 16)
        elif up == "ADD" and re.fullmatch(r"ESP,0x[0-9a-f]+", ops):
            delta -= int(ops.split("0x")[1], 16)
        elif up == "ADD" and re.fullmatch(r"ESP,-0x[0-9a-f]+", ops):
            delta += int(ops.split("-0x")[1], 16)
        elif up == "LEAVE":
            delta = 0
        m = re.fullmatch(r"0x([0-9a-f]+)", ops)
        if m and (up.startswith("J")) and up != "JMP":
            at.setdefault(int(m.group(1), 16), delta)
        if up == "JMP" and m:
            at.setdefault(int(m.group(1), 16), delta)
        if up in ("RET", "JMP"):
            pass
    return {k: v for k, v in args.items() if v != "double-high"}


def main():
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or ["LUA.DLL"]
    sel = json.load(open(os.path.join(ROOT, "names", "asm_funcs.json")))
    for prog in names:
        path = export_raw.PROGRAMS[prog]
        ctx = Ctx(prog)
        for addr in sel.get(prog, []):
            lines = g.get("disassemble_function", program=path, address=addr).splitlines()
            args = analyze(lines)
            n = max(args) if args else 0
            cur = ctx.protos.get(int(addr, 16))
            have = cur[2] if cur else 0
            if have < n <= 8:  # larger counts are frame-layout artefacts
                print(f"{prog} {addr} {cur[0] if cur else '?'}: stack args used {n} > prototype {have}: {args}")
                if "--apply" in sys.argv and cur:
                    name = cur[0]
                    params = ", ".join("%s a%d" % (args.get(i, "int"), i) for i in range(1, n + 1))
                    ccs = {"stdcall": "__stdcall", "fastcall": "__fastcall", "thiscall": "__thiscall"}.get(cur[1], "__cdecl")
                    hdr = None
                    src = os.path.join(ROOT, "raw", prog, "functions", addr + ".c")
                    rt = "undefined4"
                    if os.path.exists(src):
                        m = re.search(r"^([A-Za-z_][^(\n]*?)\s+(?:__\w+\s+)?\*?" + re.escape(name) + r"\(", open(src, encoding="utf-8", errors="replace").read(), re.M)
                        if m:
                            rt = re.sub(r"__\w+", "", m.group(1)).strip() or "undefined4"
                    r = g.post("set_function_prototype", program=path, function_address=addr, prototype="%s %s %s(%s)" % (rt, ccs, name, params))
                    print("   ->", "ok" if "Success" in str(r) else str(r)[:100])
    if "--apply" in sys.argv:
        g.ensure_current(g.EXE)
        g.post("save_all_programs")


if __name__ == "__main__":
    main()
