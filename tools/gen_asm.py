"""Translate selected functions from Ghidra's disassembly into assembly source.

Some functions cannot be decompiled faithfully: x87 helper calls (`_ftol`, `_CIpow`) lose their
ST(0) operand, setjmp frames, register-passed values. For those the original instructions are
reassembled with symbolic references instead:

  * absolute data/code references become `_sect_<name> + offset` (the rebuilt sections) or the
    symbol of the function they point at
  * calls go to the C function's real symbol (stdcall/fastcall decoration taken from the
    generated prototypes), or through `__imp_` for imports
  * switch tables inside .text are re-emitted with local labels

The selection lives in names/asm_funcs.json ({prog: [addresses]}); output is
src/<prog>/asm_funcs.s, assembled by build/link.py. build_src.py puts the C bodies of these
functions under `#if 0`.

Usage: python -I gen_asm.py [prog...] [--select]   (--select re-derives the list)
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INSN = re.compile(r"^([0-9a-f]+):\s+(\S+)\s*(.*?)\s*$")
HEX = re.compile(r"(?<![\w.])(-?)0x([0-9a-f]+)\b")
SELECT_RE = re.compile(r"\b(_ftol|_CI[A-Za-z0-9]+|_frnd|floor|ceil)\(\)")
PTR = {"float": "dword", "double": "qword", "float10": "tbyte"}


class Ctx:
    def __init__(self, prog):
        self.prog = prog
        raw = os.path.join(ROOT, "raw", prog)
        self.funcs = {int(f["address"], 16): f for f in json.load(open(os.path.join(raw, "functions.json")))}
        self.secs = [(s["name"].strip("."), int(s["start"], 16), s["size"]) for s in json.load(open(os.path.join(raw, "sections.json")))]
        for line in open(os.path.join(raw, "segments.txt")):
            if line.startswith(".text:"):
                lo, hi = line.split(":", 1)[1].strip().split(" - ")
                self.text = (int(lo, 16), int(hi, 16))
        self.slots = {}
        for line in open(os.path.join(raw, "data_items.txt"), encoding="utf-8", errors="replace"):
            m = re.match(r"^PTR_(\w+)_([0-9a-f]{8}) @ ([0-9a-f]{8}) ", line)
            if m:
                self.slots[int(m.group(3), 16)] = m.group(1)
        try:
            self.dec = json.load(open(os.path.join(ROOT, "build", "stdcall_names.json")))
        except OSError:
            self.dec = {}
        self.protos = {}
        for line in open(os.path.join(ROOT, "src", prog, "functions.h"), encoding="utf-8"):
            m = re.match(r"^(.*?)\b([A-Za-z_]\w*)\s*\((.*)\);\s*/\* 0x([0-9a-f]+)", line)
            if m:
                head, name, params, addr = m.groups()
                cc = re.search(r"__(stdcall|fastcall|thiscall)", head)
                n = 0 if params.strip() in ("", "void") else params.count(",") + 1
                self.protos[int(addr, 16)] = (name, cc.group(1) if cc else "cdecl", n)

    def section_of(self, v):
        for name, start, size in self.secs:
            if start <= v <= start + size:
                return name, v - start
        return None

    def symbol_of(self, addr):
        """C symbol of the function at addr, or None."""
        if addr in self.protos:
            name, cc, n = self.protos[addr]
            if cc == "stdcall":
                return "_%s@%d" % (name, 4 * n)
            if cc == "fastcall":
                return "@%s@%d" % (name, 4 * n)
            return "_" + name
        f = self.funcs.get(addr)
        return ("_" + f["name"]) if f else None


def convert_operand_text(ctx, text, fstart, fend, labels, tables):
    """Rewrite one operand string; returns (text, consumed_label_targets)."""
    t = text
    for a, b in PTR.items():
        t = t.replace(a + " ptr", b + " ptr")
    t = re.sub(r"\bST(\d)\b", r"st(\1)", t)
    t = re.sub(r"\[([^\]]*)\]", lambda m: "[" + m.group(1).replace(" ", "") + "]", t)  # [EAX + 0x4] -> [EAX+0x4]
    return t


def addr_expr(ctx, v, fstart, fend, tables, in_mem, size_hint=4):
    """Symbolic form of an absolute address, or None when it is a plain number."""
    if fstart <= v < fend:
        return ".L%x" % v
    sec = ctx.section_of(v)
    if sec:
        return "_sect_%s+0x%x" % sec
    if ctx.text[0] <= v <= ctx.text[1]:
        sym = ctx.symbol_of(v)
        if sym:
            return sym
        tables.setdefault(v, size_hint)
        return ".Lc_%x" % v
    return None


def convert(ctx, addr, lines):
    fstart = int(addr, 16)
    insns = [m.groups() for m in (INSN.match(l) for l in lines) if m]
    fend = int(insns[-1][0], 16) + 1  # branches past the last instruction leave the function
    targets = set()
    for a, mn, ops in insns:
        if mn.upper().startswith("J") or mn.upper() in ("LOOP", "CALL"):
            m = re.fullmatch(r"0x([0-9a-f]+)", ops)
            if m and fstart <= int(m.group(1), 16) < fend:
                targets.add(int(m.group(1), 16))
    tables = {}
    jt = {}
    out = []
    for a, mn, ops in insns:
        ia = int(a, 16)
        up = mn.upper()
        lab = ".L%x:" % ia if ia in targets or True else ""
        text = None
        m = re.fullmatch(r"(\w+)\.(REP|REPE|REPNE)\s*.*", mn, re.I)
        if m:
            pre = {"REP": "rep", "REPE": "repe", "REPNE": "repne"}[m.group(2).upper()]
            text = "%s %s" % (pre, m.group(1).lower())
        elif re.fullmatch(r"(MOVS|STOS|LODS|SCAS|CMPS)[BWD]", up):
            text = up.lower()
        elif up == "CALL" or up.startswith("J") or up == "LOOP":
            m1 = re.fullmatch(r"0x([0-9a-f]+)", ops)
            ms = re.fullmatch(r"dword ptr \[0x([0-9a-f]{8})\]", ops)
            if m1:
                tgt = int(m1.group(1), 16)
                if fstart <= tgt < fend:
                    text = "%s .L%x" % (mn.lower(), tgt)
                else:
                    sym = ctx.symbol_of(tgt)
                    f = ctx.funcs.get(tgt)
                    if f is not None and f.get("isThunk") and f["name"] in ctx.dec:
                        text = "%s dword ptr [__imp_%s]" % (mn.lower(), ctx.dec[f["name"]])
                    elif sym:
                        text = "%s %s" % (mn.lower(), sym)
                    else:
                        text = "ud2  # %s %s: target is not a known function" % (mn, ops)
            elif ms and int(ms.group(1), 16) in ctx.slots:
                name = ctx.slots[int(ms.group(1), 16)]
                text = "%s dword ptr [__imp_%s]" % (mn.lower(), ctx.dec.get(name, "_" + name))
            elif re.search(r"\*0x4\s*\+\s*0x([0-9a-f]+)\]", ops) and up == "JMP":
                mt = re.search(r"\[(\w+)\*0x4\s*\+\s*0x([0-9a-f]+)\]", ops)
                taddr = int(mt.group(2), 16)
                jt[taddr] = None
                text = "jmp dword ptr [%s*4+.Ljt_%x]" % (mt.group(1).lower(), taddr)
        if text is None:
            # generic: rewrite hex literals that are addresses
            def rep(mm):
                neg, h = mm.group(1), int(mm.group(2), 16)
                if neg:
                    return mm.group(0)
                lo = ctx.secs[0][1] if ctx.secs else 0
                if h < min(lo, ctx.text[0]) or h > max(s[1] + s[2] for s in ctx.secs):
                    return mm.group(0)
                e = addr_expr(ctx, h, fstart, fend, tables, True)
                if e is None:
                    return mm.group(0)
                return "offset " + e if mm.string[:mm.start()].count("[") <= mm.string[:mm.start()].count("]") else e
            t = ops
            t = HEX.sub(rep, t)
            t = convert_operand_text(ctx, t, fstart, fend, targets, tables)
            text = ("%s %s" % (mn.lower(), t)).strip()
            text = text.replace("fs:[0x0]", "fs:[0]").replace("FS:[0x0]", "fs:[0]")
        out.append((ia, text))
    return out, tables, jt, fend


def read_text(path, a, n):
    r = g.get("read_memory", program=path, address="%08x" % a, length=n)
    try:
        d = json.loads(r)
        return bytes(d["data"])
    except Exception:
        return None


def select(prog):
    raw = os.path.join(ROOT, "raw", prog)
    out = []
    for f in json.load(open(os.path.join(raw, "functions.json"))):
        if f.get("isThunk") or f.get("isExternal"):
            continue
        p = os.path.join(raw, "functions", f["address"] + ".c")
        if os.path.exists(p) and SELECT_RE.search(open(p, encoding="utf-8", errors="replace").read()):
            out.append(f["address"])
    return sorted(out)


def main():
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or ["LUA.DLL"]
    sel_path = os.path.join(ROOT, "names", "asm_funcs.json")
    sel = json.load(open(sel_path)) if os.path.exists(sel_path) else {}
    for prog in names:
        path = export_raw.PROGRAMS[prog]
        if "--select" in sys.argv or prog not in sel:
            sel[prog] = select(prog)
            json.dump(sel, open(sel_path, "w"), indent=1)
        ctx = Ctx(prog)
        body = ["# GENERATED by tools/gen_asm.py from Ghidra's disassembly (%s)" % prog,
                "\t.intel_syntax noprefix", "\t.intel_mnemonic", "\t.text"]
        rodata = ["\t.section .rdata,\"dr\"", "\t.p2align 2"]
        done = 0
        for addr in sel[prog]:
            lines = g.get("disassemble_function", program=path, address=addr).splitlines()
            insns, tables, jt, fend = convert(ctx, addr, lines)
            fstart = int(addr, 16)
            sym = ctx.symbol_of(fstart)
            if not sym:
                print("  no symbol for", addr)
                continue
            body += ["", "\t.globl %s" % sym, "%s:  # %s" % (sym, ctx.funcs[fstart]["name"])]
            for ia, text in insns:
                body.append(".L%x:\t%s" % (ia, text))
            for taddr in jt:
                raw = read_text(path, taddr, 4 * 128)
                ents = []
                if raw:
                    for k in range(128):
                        v = int.from_bytes(raw[4 * k:4 * k + 4], "little")
                        if fstart <= v < fend:
                            ents.append(v)
                        else:
                            break
                rodata.append(".Ljt_%x:" % taddr)
                rodata += ["\t.long .L%x" % v for v in ents] or ["\t.long 0"]
            for caddr, size in tables.items():
                raw = read_text(path, caddr, 64)
                rodata.append(".Lc_%x:" % caddr)
                rodata.append("\t.byte " + ",".join(str(b) for b in (raw or bytes(64))))
            done += 1
        open(os.path.join(ROOT, "src", prog, "asm_funcs.s"), "w", newline="\n").write("\n".join(body + [""] + rodata) + "\n")
        print(f"{prog}: {done} functions written to src/{prog}/asm_funcs.s")


if __name__ == "__main__":
    main()
