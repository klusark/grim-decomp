"""Smallest access width the code uses for each absolute data address.

Ghidra labels bytes that code reaches (`DAT_0090051f`) without defining a data item of the right
size, so the generated C declares them as 4-byte `undefined4`. A one-byte store such as
`MOV byte ptr [0x0090051f],0x0` then clobbers the three bytes after it (here the low bytes of the
pointer stored at 0x00900520). The disassembly tells the real width of every direct access.

Writes raw/<prog>/access_sizes.json {"0090051f": 1, ...} (minimum width seen, 1/2/4/8/10).
Only displacement-only operands `[0xADDR]` are considered; indexed forms are arrays and keep
the width of their Ghidra data item.

Usage: python -I export_access_sizes.py [prog...]
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INSN = re.compile(r"^([0-9a-f]+):\s+(\w+)\s*(.*?)\s*$")
MEM = re.compile(r"(?:(byte|word|dword|qword|tbyte|float|double|float10)\s+ptr\s+)?\[0x([0-9a-f]{6,8})\]")
PTR = {"byte": 1, "word": 2, "dword": 4, "float": 4, "qword": 8, "double": 8, "tbyte": 10, "float10": 10}
REG8 = {"AL", "AH", "BL", "BH", "CL", "CH", "DL", "DH"}
REG16 = {"AX", "BX", "CX", "DX", "SI", "DI", "BP", "SP"}
REG32 = {"EAX", "EBX", "ECX", "EDX", "ESI", "EDI", "EBP", "ESP"}
SKIP = {"LEA", "CALL", "JMP", "NOP"}


def reg_width(ops):
    for r in re.split(r"[,\s]+", ops):
        r = r.upper()
        if r in REG8: return 1
        if r in REG16: return 2
        if r in REG32: return 4
    return 4  # no register or size prefix: PUSH/CMP with an immediate default to the operand size 4


def scan(prog):
    path = export_raw.PROGRAMS[prog]
    funcs = json.load(open(os.path.join(ROOT, "raw", prog, "functions.json")))
    best = {}
    for i, f in enumerate(funcs):
        if f.get("isThunk") or f.get("isExternal"):
            continue
        for line in g.get("disassemble_function", program=path, address=f["address"]).splitlines():
            m = INSN.match(line)
            if not m or m.group(2).upper() in SKIP:
                continue
            ops = m.group(3)
            if m.group(2).upper().startswith(("MOVZX", "MOVSX")):
                mm = MEM.search(ops)
                if mm:
                    w = PTR.get(mm.group(1) or "", 1 if mm.group(1) is None else 4)
                    best[mm.group(2).rjust(8, "0")] = min(best.get(mm.group(2).rjust(8, "0"), 99), w)
                continue
            for mm in MEM.finditer(ops):
                w = PTR[mm.group(1)] if mm.group(1) else reg_width(ops)
                a = mm.group(2).rjust(8, "0")
                best[a] = min(best.get(a, 99), w)
        if i % 300 == 0:
            print(f"  {prog}: {i}/{len(funcs)}", flush=True)
    json.dump(best, open(os.path.join(ROOT, "raw", prog, "access_sizes.json"), "w"), indent=0, sort_keys=True)
    print(f"{prog}: {len(best)} addresses; {sum(1 for v in best.values() if v < 4)} narrower than 4 bytes", flush=True)


if __name__ == "__main__":
    for n in [a for a in sys.argv[1:] if not a.startswith("--")] or list(export_raw.PROGRAMS):
        scan(n)
