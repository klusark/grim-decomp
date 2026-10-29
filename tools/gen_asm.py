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
import glob, json, os, re, sys
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
        try:
            imported = {i["name"] for i in json.load(open(os.path.join(raw, "imports.json")))}
        except OSError:
            imported = None
        for line in open(os.path.join(raw, "data_items.txt"), encoding="utf-8", errors="replace"):
            m = re.match(r"^PTR_(\w+)_([0-9a-f]{8}) @ ([0-9a-f]{8}) ", line)
            # Ghidra also names plain data pointers PTR_DAT_/PTR_FUN_/PTR_s_...; only imports are slots
            if m and (imported is None or m.group(1) in imported):
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
        if f and f.get("isThunk") and f["name"] in self.dec:
            return self.dec[f["name"]]  # a Win32 import thunk: the import library's decorated label
        return ("_" + f["name"]) if f else None

# imports that build/win32_shims.c replaces (the C code binds to the decorated symbol, which the shim
# defines); assembled code reads the import slot, so it gets a pointer cell that holds the shim
SHIMMED = {"InterlockedIncrement": "_InterlockedIncrement@4", "InterlockedDecrement": "_InterlockedDecrement@4",
           "InterlockedExchange": "_InterlockedExchange@8", "RegOpenKeyExA": "_RegOpenKeyExA@20",
           "RegCreateKeyExA": "_RegCreateKeyExA@36"}
SHIM_USED = set()


def imp_ref(ctx, name):
    if name in SHIMMED:
        SHIM_USED.add(name)
        return "__shimimp_" + name
    return "__imp_" + ctx.dec.get(name, "_" + name)


def convert_operand_text(ctx, text, fstart, fend, labels, tables):
    """Rewrite one operand string; returns (text, consumed_label_targets)."""
    t = text.replace("extended double ptr", "tbyte ptr")  # Ghidra's spelling of the 80-bit operand
    for a, b in PTR.items():
        t = t.replace(a + " ptr", b + " ptr")
    t = re.sub(r"\bST(\d)\b", r"st(\1)", t)
    t = re.sub(r"\[([^\]]*)\]", lambda m: "[" + m.group(1).replace(" ", "") + "]", t)  # [EAX + 0x4] -> [EAX+0x4]
    return t


def addr_expr(ctx, v, fstart, fend, tables, in_mem, size_hint=4):
    """Symbolic form of an absolute address, or None when it is a plain number."""
    if fstart <= v < fend:
        return ".L%x_%x" % (fstart, v)
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
        lock = ""
        if mn.upper().endswith(".LOCK"):  # Ghidra prints `DEC.LOCK [..]`; gas wants `lock dec [..]`
            mn, lock = mn[:-5], "lock "
        up = mn.upper()
        text = None
        m = re.fullmatch(r"(\w+)\.(REP|REPE|REPNE)\s*.*", mn, re.I)
        if m:
            pre = {"REP": "rep", "REPE": "repe", "REPNE": "repne"}[m.group(2).upper()]
            text = "%s %s" % (pre, m.group(1).lower())
        elif re.fullmatch(r"(MOVS|STOS|LODS|SCAS|CMPS)[BWD]", up):
            text = up.lower()
        elif up == "XLAT":
            text = "xlatb"
        elif up == "CALL" or up.startswith("J") or up == "LOOP":
            m1 = re.fullmatch(r"0x([0-9a-f]+)", ops)
            ms = re.fullmatch(r"dword ptr \[0x([0-9a-f]{8})\]", ops)
            if m1:
                tgt = int(m1.group(1), 16)
                if fstart <= tgt < fend:
                    text = "%s .L%x_%x" % (mn.lower(), fstart, tgt)
                else:
                    sym = ctx.symbol_of(tgt)
                    f = ctx.funcs.get(tgt)
                    if f is not None and f.get("isThunk") and f["name"] in ctx.dec:
                        text = "%s dword ptr [%s]" % (mn.lower(), imp_ref(ctx, f["name"]))
                    elif sym:
                        text = "%s %s" % (mn.lower(), sym)
                    else:
                        text = "ud2  # %s %s: target is not a known function" % (mn, ops)
            elif ms and int(ms.group(1), 16) in ctx.slots:
                name = ctx.slots[int(ms.group(1), 16)]
                text = "%s dword ptr [%s]" % (mn.lower(), imp_ref(ctx, name))
            elif re.search(r"\*0x4\s*\+\s*0x([0-9a-f]+)\]", ops) and up == "JMP":
                mt = re.search(r"\[(\w+)\*0x4\s*\+\s*0x([0-9a-f]+)\]", ops)
                taddr = int(mt.group(2), 16)
                jt[taddr] = None
                text = "jmp dword ptr [%s*4+.Ljt_%x_%x]" % (mt.group(1).lower(), fstart, taddr)
        if text is None:
            # generic: rewrite hex literals that are addresses
            def rep(mm):
                neg, h = mm.group(1), int(mm.group(2), 16)
                if neg:
                    return mm.group(0)
                lo = ctx.secs[0][1] if ctx.secs else 0
                if h < min(lo, ctx.text[0]) or h > max(s[1] + s[2] for s in ctx.secs):
                    return mm.group(0)
                if h in ctx.slots and mm.string[:mm.start()].count("[") > mm.string[:mm.start()].count("]"):
                    # an import address table slot read as data (`MOV ESI,[slot]` ... `CALL ESI`): the
                    # dumped IAT holds import-name entries, the linker's import symbol holds the address
                    name = ctx.slots[h]
                    return imp_ref(ctx, name)
                # `[idx*4+0x4d3600]` with the base inside .text (or anywhere outside the dumped sections) is
                # a biased table base: the index brings it back into .data (Math_SinCosTable's quadrant
                # tables). Express it relative to the .data blob so the relocation keeps the distance.
                before = mm.string[:mm.start()]
                if before.count("[") > before.count("]") and "*" in before[before.rfind("["):] \
                        and ctx.text[0] <= h <= ctx.text[1] and not ctx.symbol_of(h) and not ctx.section_of(h) \
                        and not (fstart <= h < fend):
                    dsec = next((s for s in ctx.secs if s[0] == "data"), None)
                    if dsec:
                        return "_sect_data%+d" % (h - dsec[1])
                e = addr_expr(ctx, h, fstart, fend, tables, True)
                if e is None:
                    return mm.group(0)
                return "offset " + e if mm.string[:mm.start()].count("[") <= mm.string[:mm.start()].count("]") else e
            t = ops
            t = HEX.sub(rep, t)
            t = convert_operand_text(ctx, t, fstart, fend, targets, tables)
            text = lock + ("%s %s" % (mn.lower(), t)).strip()
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
    # COM calls through a vtable (`code_std` in the generated C): Ghidra drops the pushed arguments
    # when it cannot type the interface, so only the disassembly has the real call
    # (decided from the original decompile in raw/, restricted to the DirectX modules, so the choice
    # does not depend on what the previous generator run did to src/)
    banner = re.compile(r"(?m)^/\* ---- 0x([0-9a-f]+)  (\S+) ---- \*/")
    com_call = re.compile(r"\(\*\*?\(code \*\*?\)")
    com_modules = {"std3d.c", "stddisplay.c", "stdinput.c", "mixer.c", "rdmaterial.c"}
    import build_src  # OVERRIDES: functions hand-written in build/overrides.c stay C
    for sp in sorted(glob.glob(os.path.join(ROOT, "src", prog, "*.c"))):
        if os.path.basename(sp) not in com_modules:
            continue
        for a in banner.findall(open(sp, encoding="utf-8", errors="replace").read()):
            rp = os.path.join(raw, "functions", a[0] + ".c")
            if a[1] not in build_src.OVERRIDES and os.path.exists(rp) \
                    and com_call.search(open(rp, encoding="utf-8", errors="replace").read()):
                out.append(a[0])
    # decompiler artifacts that only exist because a register or flag value crosses a call or an
    # instruction boundary (multi-word arithmetic, x87 state, return values read from EAX/EDX/ST0)
    arti = re.compile(r"\b(CARRY[124]|SBORROW[124]|SCARRY[124]|in_FPUStatusWord|in_ST[0-7]|extraout_ST[0-7]|extraout_E[ABCD]X|unaff_E[A-Z]+|unaff_retaddr)\b")
    import build_src  # OVERRIDES: functions hand-written in build/overrides.c stay C
    for f in json.load(open(os.path.join(raw, "functions.json"))):
        if f.get("isThunk") or f.get("isExternal") or f["name"] in build_src.OVERRIDES:
            continue
        p = os.path.join(raw, "functions", f["address"] + ".c")
        if os.path.exists(p) and arti.search(open(p, encoding="utf-8", errors="replace").read()):
            out.append(f["address"])
    # hand-picked: the decompiler mishandles them for other reasons (stack objects, register
    # values); names/asm_extra.json {prog: [addresses]}
    xp = os.path.join(ROOT, "names", "asm_extra.json")
    if os.path.exists(xp):
        out += json.load(open(xp)).get(prog, [])
    # --all: assemble every function (the decompiled C stays in src/ under #if 0 for reading);
    # names/asm_exclude.json {prog: [addresses]} keeps individual functions as C
    if "--all" in sys.argv:
        # the MSVC runtime (heap, locks, stdio) expects its own start-up; the host runtime provides
        # those, so the CRT modules stay C (only the artifact-driven picks above are assembled)
        crt_addrs = set()
        for sp in glob.glob(os.path.join(ROOT, "src", prog, "*.c")):
            if re.match(r"(crt|tmpnam|getlcid|translatename|parse|getsystemcp|setsbcs|setsbuplow)", os.path.basename(sp)):
                crt_addrs |= set(re.findall(r"(?m)^/\* ---- 0x([0-9a-f]+)  ", open(sp, encoding="utf-8", errors="replace").read()))
        keep = set(out)
        out += [f["address"] for f in json.load(open(os.path.join(raw, "functions.json")))
                if not (f.get("isThunk") or f.get("isExternal") or f["name"] in build_src.OVERRIDES)
                and f["address"] not in crt_addrs]
        out = [a for a in out if a not in crt_addrs or a in keep]
    ep = os.path.join(ROOT, "names", "asm_exclude.json")  # applies to every selection mode
    if os.path.exists(ep):
        skip = set(json.load(open(ep)).get(prog, []))
        out = [a for a in out if a not in skip]
    # a function written by hand in build/overrides.c must not also be assembled (duplicate symbol)
    hand = {f["address"] for f in json.load(open(os.path.join(raw, "functions.json"))) if f["name"] in build_src.OVERRIDES}
    out = [a for a in out if a not in hand]
    return sorted(set(out))


PATCHES = json.load(open(os.path.join(ROOT, "names", "asm_patches.json"))) if os.path.exists(os.path.join(ROOT, "names", "asm_patches.json")) else {}


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
        emitted_consts = set()
        for addr in sel[prog]:
            lines = g.get("disassemble_function", program=path, address=addr).splitlines()
            insns, tables, jt, fend = convert(ctx, addr, lines)
            fstart = int(addr, 16)
            sym = ctx.symbol_of(fstart)
            if not sym:
                print("  no symbol for", addr)
                continue
            # every local label the code refers to must be an instruction of this listing; Ghidra
            # splits functions with computed-jump bodies, and those cannot be assembled from the listing
            defined = {ia for ia, _ in insns}
            refs = set()
            for _, text in insns:
                refs |= {int(x, 16) for x in re.findall(r"\.L[0-9a-f]{6,8}_([0-9a-f]{6,8})\b", text)}
            ents_ok = True
            for taddr in jt:
                raw = read_text(path, taddr, 4 * 128)
                for k in range(128 if raw else 0):
                    v = int.from_bytes(raw[4 * k:4 * k + 4], "little")
                    if not (fstart <= v < fend):
                        break
                    if v not in defined:
                        ents_ok = False
            if (refs - defined) or not ents_ok:
                print("  skipped %s %s: refers to code outside its listing" % (addr, ctx.funcs[fstart]["name"]))
                sel[prog] = [a for a in sel[prog] if a != addr]
                json.dump(sel, open(sel_path, "w"), indent=1)
                continue
            # COFF function type, so `ld --export-all-symbols` exports a code symbol (import libraries
            # get a call thunk) instead of treating the label as data
            body += ["", "\t.def %s; .scl 2; .type 32; .endef" % sym, "\t.globl %s" % sym,
                     "%s:  # %s" % (sym, ctx.funcs[fstart]["name"])]
            patches = PATCHES.get(prog, {}).get(addr, {})
            for ia, text in insns:
                body.append(".L%x_%x:\t%s" % (fstart, ia, text))
                for extra in patches.get("%08x" % ia, patches.get("%x" % ia, [])):
                    body.append("\t" + extra)
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
                rodata.append(".Ljt_%x_%x:" % (fstart, taddr))
                rodata += ["\t.long .L%x_%x" % (fstart, v) for v in ents] or ["\t.long 0"]
            for caddr, size in tables.items():
                if caddr in emitted_consts:
                    continue
                emitted_consts.add(caddr)
                raw = read_text(path, caddr, 64)
                rodata.append(".Lc_%x:" % caddr)
                rodata.append("\t.byte " + ",".join(str(b) for b in (raw or bytes(64))))
            done += 1
        cells = ["\t.data", "\t.p2align 2"] + ["__shimimp_%s:\t.long %s" % (n, SHIMMED[n]) for n in sorted(SHIM_USED)]
        SHIM_USED.clear()
        open(os.path.join(ROOT, "src", prog, "asm_funcs.s"), "w", newline="\n").write("\n".join(body + [""] + rodata + cells) + "\n")
        print(f"{prog}: {done} functions written to src/{prog}/asm_funcs.s")


if __name__ == "__main__":
    main()
