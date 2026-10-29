"""Which functions really take `this` in ECX?

A function takes ECX as an input only if its first instruction that mentions
ECX/CX/CL reads it, before any CALL, jump or write to the register.  A
decompiler `in_ECX` that shows up later is just a value a callee left in ECX.

Usage: python -I verify_ecx.py [prog...]    -> prints verdicts and writes
raw/<prog>/ecx_verdict.json {address: {name, entry_read, thiscall}}
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INSN = re.compile(r"^[0-9a-f]+:\s+(\w+)\s*(.*?)\s*$")
ECX_WORDS = re.compile(r"\b(ECX|CX|CL|CH)\b")


def entry_reads_ecx(disasm):
    """True / False / None (never mentions ECX before the first call or jump)."""
    for line in disasm.strip().splitlines():
        m = INSN.match(line)
        if not m:
            continue
        mn, ops = m.group(1).upper(), m.group(2)
        if mn.startswith(("CALL", "J", "RET", "LOOP")):
            return None
        if not ECX_WORDS.search(ops):
            continue
        dst, _, src = ops.partition(",")
        dst_is_ecx = bool(re.fullmatch(r"\s*(ECX|CX|CL|CH)\s*", dst))
        if mn == "XOR" and dst_is_ecx and re.fullmatch(r"\s*(ECX|CX|CL|CH)\s*", src):
            return False  # zeroing idiom: a write
        if mn in ("MOV", "LEA", "MOVZX", "MOVSX", "POP", "SETZ", "SETNZ", "SETL", "SETGE", "SETLE", "SETG") and dst_is_ecx:
            # a write; but `MOV ECX,[ECX+4]` reads it first
            return bool(ECX_WORDS.search(src))
        return True  # any other mention reads it (PUSH ECX, MOV [x],ECX, CMP, ADD ...)
    return None


def main():
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or list(export_raw.PROGRAMS)
    for prog in names:
        path = export_raw.PROGRAMS[prog]
        raw = os.path.join(ROOT, "raw", prog)
        funcs = json.load(open(os.path.join(raw, "functions.json")))
        out = {}
        for f in funcs:
            if f.get("isThunk") or f.get("isExternal"):
                continue
            src = os.path.join(raw, "functions", f["address"] + ".c")
            if not os.path.exists(src):
                continue
            code = open(src, encoding="utf-8", errors="replace").read()
            if "in_ECX" not in code and "__thiscall" not in code:
                continue
            d = g.get("disassemble_function", program=path, address=f["address"])
            out[f["address"]] = {"name": f["name"], "entry_read": entry_reads_ecx(d), "thiscall": "__thiscall" in code}
        json.dump(out, open(os.path.join(raw, "ecx_verdict.json"), "w"), indent=1)
        yes = [a for a, v in out.items() if v["entry_read"]]
        no = [a for a, v in out.items() if not v["entry_read"]]
        print(f"{prog}: {len(out)} candidates, {len(yes)} read ECX at entry, {len(no)} do not")
        for a in no:
            v = out[a]
            print("   NOT:", a, v["name"], "(typed thiscall)" if v["thiscall"] else "", v["entry_read"])


if __name__ == "__main__":
    main()
