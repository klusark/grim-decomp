"""Cross-check every function's declared C prototype against its machine code.

find_arity_mismatch.py only compares C text with C text.  This tool reads the original code (Ghidra
disassembly) and reports, per program,

  * stdcall/cdecl disagreement:  `RET n` in the binary vs the calling convention the C prototype declares
    (a C function declared with the wrong convention unbalances the stack of every caller);
  * phantom parameters:  the prototype declares more stack parameters than the code ever reads
    (the C body reads stack garbage, e.g. lua_setfallback's third parameter);
  * lost parameters:  the code reads more stack parameters than are declared (the decompiler dropped
    arguments, the C body sees uninitialised variables instead);
  * call sites that push fewer arguments than the callee's prototype declares (cdecl callees whose
    cleanup `ADD ESP,n` follows the call directly), and the same for callees that the code reads more
    parameters from than any call site pushes.

Functions that are assembled (names/asm_funcs.json) execute the original code, so for them only the
decorated symbol name matters; the interesting rows are the C-compiled ones ("C"), and assembled callers
of C callees.

Usage: python -I find_arity_asm.py [--fetch] [prog...]     (--fetch re-reads the disassembly from Ghidra into
                                                              raw/<prog>/disasm.json, otherwise that cache is used)
"""
import json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INSN = re.compile(r"^([0-9a-f]+):\s+(\S+)\s*(.*?)\s*$")
ESPMEM = re.compile(r"\[ESP\s*\+\s*0x([0-9a-f]+)\]")
EBPMEM = re.compile(r"\[EBP\s*\+\s*0x([0-9a-f]+)\]")
DEC = json.load(open(os.path.join(ROOT, "build", "stdcall_names.json")))
PROGS = ["GRIMFANDANGO.EXE", "LUA.DLL", "IMUSE.DLL", "CHORE.DLL"]


def fetch(prog):
    import ghidra_api as g
    import export_raw
    path = export_raw.PROGRAMS[prog]
    fs = json.load(open(os.path.join(ROOT, "raw", prog, "functions.json")))
    out = {}
    for f in fs:
        if not f.get("isExternal"):
            out[f["address"]] = g.get("disassemble_function", program=path, address=f["address"])
    json.dump(out, open(os.path.join(ROOT, "raw", prog, "disasm.json"), "w"))
    return out


def parse(text):
    return [(int(m.group(1), 16), m.group(2).upper(), m.group(3)) for m in (INSN.match(l) for l in text.splitlines()) if m]


def stack_info(insns, ret_imm_of, import_pop):
    """-> (highest stack parameter read, set of RET immediates, unsure)"""
    delta, at, reads, rets, unsure = 0, {}, 0, set(), False
    frame = False
    for i, (a, mn, ops) in enumerate(insns):
        if a in at:
            delta = at[a]
        if mn == "MOV" and ops == "EBP,ESP" and i > 0 and insns[i - 1][1] == "PUSH" and insns[i - 1][2] == "EBP":
            frame = True
        for m in ESPMEM.finditer(ops):
            rel = int(m.group(1), 16) - delta
            if rel >= 4 and rel % 4 == 0 and rel // 4 <= 24:
                reads = max(reads, rel // 4)
        if frame:
            for m in EBPMEM.finditer(ops):
                off = int(m.group(1), 16)
                if off >= 8 and (off - 8) % 4 == 0 and (off - 8) // 4 < 24:
                    reads = max(reads, (off - 8) // 4 + 1)
        if mn == "PUSH":
            delta += 4
        elif mn == "POP":
            delta -= 4
        elif mn == "SUB" and re.fullmatch(r"ESP,0x[0-9a-f]+", ops):
            delta += int(ops.split("0x")[1], 16)
        elif mn == "ADD" and re.fullmatch(r"ESP,0x[0-9a-f]+", ops):
            delta -= int(ops.split("0x")[1], 16)
        elif mn == "ADD" and re.fullmatch(r"ESP,-0x[0-9a-f]+", ops):
            delta += int(ops.split("-0x")[1], 16)
        elif mn == "MOV" and ops.startswith("ESP,"):
            unsure = True
        elif mn == "LEAVE":
            delta = 0
        elif mn == "CALL":
            m = re.fullmatch(r"0x([0-9a-f]+)", ops)
            if m:
                delta -= ret_imm_of.get(int(m.group(1), 16), 0)
            else:
                m = re.fullmatch(r"dword ptr \[0x([0-9a-f]+)\]", ops)
                if m and int(m.group(1), 16) in import_pop:
                    delta -= import_pop[int(m.group(1), 16)]
                elif m:
                    unsure = True  # import call: callee pops an unknown amount
        elif mn == "RET":
            m = re.fullmatch(r"0x([0-9a-f]+)", ops)
            rets.add(int(m.group(1), 16) if m else 0)
        m = re.fullmatch(r"0x([0-9a-f]+)", ops)
        if m and mn.startswith("J"):
            at.setdefault(int(m.group(1), 16), delta)
    return reads, rets, unsure


def protos_of(prog):
    out = {}
    for line in open(os.path.join(ROOT, "src", prog, "functions.h"), encoding="utf-8"):
        m = re.match(r"^(.*?)\b([A-Za-z_]\w*)\s*\((.*)\);\s*/\* 0x([0-9a-f]+)", line)
        if m:
            head, name, params, addr = m.groups()
            cc = re.search(r"__(stdcall|fastcall|thiscall)", head)
            n = 0 if params.strip() in ("", "void") else params.count(",") + 1
            out[int(addr, 16)] = (name, cc.group(1) if cc else "cdecl", n, "..." in params)
    return out


def import_pops(prog):
    """{import slot or thunk address: bytes the stdcall import pops}, from the decorated names in build/stdcall_names.json"""
    dec = DEC
    raw = os.path.join(ROOT, "raw", prog)
    pop = {}
    imported = {i["name"] for i in json.load(open(os.path.join(raw, "imports.json")))}
    for line in open(os.path.join(raw, "data_items.txt"), encoding="utf-8", errors="replace"):
        m = re.match(r"^PTR_(\w+)_([0-9a-f]{8}) @ ([0-9a-f]{8}) ", line)
        if m and m.group(1) in imported and m.group(1) in dec:
            pop[int(m.group(3), 16)] = int(dec[m.group(1)].rsplit("@", 1)[1])
    return pop


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")] or PROGS
    asm = json.load(open(os.path.join(ROOT, "names", "asm_funcs.json")))
    for prog in args:
        cache = os.path.join(ROOT, "raw", prog, "disasm.json")
        if "--fetch" in sys.argv or not os.path.exists(cache):
            fetch(prog)
        dis = {int(a, 16): parse(t) for a, t in json.load(open(cache)).items()}
        protos = protos_of(prog)
        funcs = {int(f["address"], 16): f["name"] for f in json.load(open(os.path.join(ROOT, "raw", prog, "functions.json")))}
        asm_set = {int(a, 16) for a in asm.get(prog, [])}
        ret_imm = {}
        for a, ins in dis.items():
            rets = [int(o, 16) for (_, mn, o) in ins if mn == "RET" and o.startswith("0x")]
            if rets:
                ret_imm[a] = max(rets)
        import_pop = import_pops(prog)
        for a, name in funcs.items():  # calls to Win32 import thunks pop the decorated size
            if name in DEC:
                ret_imm.setdefault(a, int(DEC[name].rsplit("@", 1)[1]))
        info = {a: stack_info(ins, ret_imm, import_pop) for a, ins in dis.items()}
        print("==== %s" % prog)
        for a, (reads, rets, unsure) in sorted(info.items()):
            p = protos.get(a)
            if not p:
                continue
            name, cc, n, va = p
            kind = "asm" if a in asm_set else "C"
            ret = max(rets) if rets else 0
            what = []
            if cc == "stdcall" and ret != 4 * n:
                what.append("stdcall n=%d but RET %#x" % (n, ret))
            if cc == "cdecl" and ret:
                what.append("cdecl but RET %#x" % ret)
            if cc == "cdecl" and not ret and not va and reads < n:
                what.append("phantom params: declared %d, reads %d%s" % (n, reads, " (unsure)" if unsure else ""))
            if cc == "cdecl" and not ret and not va and n < reads <= 12:
                what.append("lost params: declared %d, reads %d%s" % (n, reads, " (unsure)" if unsure else ""))
            if what:
                print("%-3s %08x %-34s %s" % (kind, a, name, "; ".join(what)))
        print("-- call sites pushing fewer arguments than the callee's prototype declares")
        for a, ins in sorted(dis.items()):
            for i, (ia, mn, ops) in enumerate(ins[:-1]):
                m = re.fullmatch(r"0x([0-9a-f]+)", ops) if mn == "CALL" else None
                if not m:
                    continue
                t = int(m.group(1), 16)
                p = protos.get(t)
                if not p or p[1] != "cdecl" or p[3]:
                    continue
                nx = ins[i + 1]
                m2 = re.fullmatch(r"ESP,0x([0-9a-f]+)", nx[2]) if nx[1] == "ADD" else None
                if not m2:
                    continue
                pushed = int(m2.group(1), 16) // 4
                if pushed < p[2]:
                    kind = "asm" if a in asm_set else "C"
                    print("%-3s %08x in %-30s -> %-28s pushes %d, declared %d (callee reads %d)"
                          % (kind, ia, funcs.get(a, "?"), p[0], pushed, p[2], info[t][0]))


if __name__ == "__main__":
    main()
