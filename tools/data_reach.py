"""Which spans of the original data can leave the original layout (tools/datagen.py).

A span is reached by the original's code (raw/<prog>/disasm.json), by the data's own pointers, and by the addresses the
code uses as numbers (IMG_ADDR, in the generated code and in build/overrides*.c). Each reference is one of:

* direct: `[0xADDR]` with a known width. It reaches ADDR .. ADDR + width and nothing else.
* indexed: `[REG*s + 0xADDR]`, `[REG + 0xADDR]`. A table: how far it goes depends on the index.
* address: `PUSH 0xADDR`, `MOV ECX,0xADDR`, `LEA EAX,[0xADDR]`, a pointer in the data, an IMG_ADDR. Whatever receives it
  can walk on from there.
* end: `CMP reg,0xADDR`, a loop's end pointer. It reaches nothing itself; the span before ADDR reaches up to it.
The overrides' macros that read one value at a literal address (RG32(0x...), Q3G(0x...): OVERRIDE_READS) are direct
reads; their other literals are addresses.

A span is *loose* when every reference to it is direct and ends inside it, or when it is a pure string (no pointer, only
zeros after its NUL) whose address is taken at its start: then nothing reaches its neighbours through it. Every other
span (a table, an object passed by address, a string indexed or entered in the middle, a value read wider than its
span) may be read on into what follows: it is *glued* to its neighbours. How far depends on what bounds it:
* a value read wider than its span reaches exactly that far;
* a span whose every `&name` in the generated code is a call given its byte count (`(*writeFn)(&g_dwMovieJustFinished,
  4)`, sized_uses) reaches that many bytes;
* a span whose Ghidra type is a structure or an array (names/types_data_extents_*.json) reaches as far as its type,
  plus a known extent for stdMath_SinCos's tables (KNOWN_EXTENT); a scalar type does not bound it (it says how the
  code reads the global: Res_SetReference((ResRef *)&g_dwSputRoom_pCurrentRoom, ..) fills g_pCurrentSet after the
  `uint`);
* an untyped one is *unbounded*: its chain runs on through every span read only directly (it may be a field of the
  object, filled through the object's address: PolyglotInitialize writes g_aPolyglotServices[2], which the code then
  calls as UINT_008ddd88), up to and including the next string taken by its address, an object of its own.
Any chain also runs through spans nothing refers to (padding, unused tails, the gap between .rdata and .data that the
quadrant tables read across). Backwards, an unbounded or indexed span, a span nothing names, and a loop's end pointer
take in the span before them unless that is a string (luaX_init walks its reserved-word table from one entry in,
reading ppuVar3[-1]). A glued chain keeps the original layout among its members; the chains themselves and the loose
spans may be placed anywhere.

usage: python -I tools/data_reach.py [PROG...]                 the counts
       python -I tools/data_reach.py explain PROG ADDR...      why the spans at ADDR are glued
"""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INSN = re.compile(r"^([0-9a-f]{8}):\s+(\S+)\s*(.*?)\s*$")
MEM = re.compile(r"(?:(byte|word|dword|qword|tbyte|float|double|float10|xmmword)\s+ptr\s+)?\[([^\]]*)\]")
HEX = re.compile(r"0x([0-9a-f]+)\b")
PTR = {"byte": 1, "word": 2, "dword": 4, "float": 4, "qword": 8, "double": 8, "tbyte": 10, "float10": 10, "xmmword": 16}
REG8 = {"AL", "AH", "BL", "BH", "CL", "CH", "DL", "DH"}
REG16 = {"AX", "BX", "CX", "DX", "SI", "DI", "BP", "SP"}
BRANCH = re.compile(r"^(CALL|J\w+|LOOP\w*)$")
IMG_RE = re.compile(r"IMG_ADDR\(\s*0x([0-9a-fA-F]{8})u?\s*\)")
LIT_RE = re.compile(r"\b0x([0-9a-fA-F]{8})u?\b")


def reg_width(ops):
    for r in re.split(r"[,\s]+", re.sub(r"\[[^\]]*\]", "", ops)):
        r = r.upper()
        if r in REG8:
            return 1
        if r in REG16:
            return 2
    return 4


def code_refs(prog, ranges):
    """[(address, kind, width)] from the original's code. kind: direct / indexed / address."""
    out = []

    def inside(a):
        return any(lo <= a < hi for lo, hi in ranges)

    for body in json.load(open(os.path.join(ROOT, "raw", prog, "disasm.json"))).values():
        for line in body.split("\n"):
            m = INSN.match(line)
            if not m:
                continue
            mn, ops = m.group(2).upper(), m.group(3)
            if BRANCH.match(mn):
                continue
            spans = []
            for mm in MEM.finditer(ops):
                spans.append((mm.start(), mm.end()))
                inner = mm.group(2)
                hs = [int(h.group(1), 16) for h in HEX.finditer(inner)]
                hs = [a for a in hs if inside(a)]   # (not the scale of `[EDX*0x4 + 0x4df600]`)
                if not hs:
                    continue
                a = hs[-1]
                if re.search(r"[A-Z]{2}", inner):
                    out.append((a, "indexed", 0))
                elif mn == "LEA":
                    out.append((a, "address", 0))
                else:
                    if mn in ("MOVZX", "MOVSX"):
                        w = PTR.get(mm.group(1) or "", 1)
                    elif mm.group(1):
                        w = PTR[mm.group(1)]
                    else:
                        w = reg_width(ops)
                    out.append((a, "direct", w))
            rest = ops
            for s, e in reversed(spans):
                rest = rest[:s] + rest[e:]
            for h in HEX.finditer(rest):
                a = int(h.group(1), 16)
                if inside(a):
                    # `CMP reg,0xADDR`: a loop's end pointer, the end of the span before (Win_AddMessageHook's
                    # `CMP EAX,0x8d0a6c`); it reaches nothing itself
                    out.append((a, "end" if mn == "CMP" else "address", 0))
    return out


def override_targets(prog, ranges):
    """Addresses the hand-written overrides compute from the original's (IMG_ADDR and the macros over it): every
    8-digit literal inside a data section of a file that uses IMG_ADDR for this program's addresses."""
    out = set()
    bd = os.path.join(ROOT, "build")
    for f in sorted(os.listdir(bd)):
        if not (f.startswith("overrides") and f.endswith(".c")):
            continue
        t = open(os.path.join(bd, f), encoding="utf-8", errors="replace").read()
        if "IMG_ADDR" not in t and "sect_data" not in t:
            continue
        for h in LIT_RE.finditer(t):
            a = int(h.group(1), 16)
            if any(lo <= a <= hi for lo, hi in ranges):
                out.add(a)
    return out


# the overrides' macros that read one value at a literal address (RG32(0x008dde8c) is `*(int *)` there): a direct
# access of that width, not an address that goes elsewhere
COMMENT_RE = re.compile(r"/[*].*?[*]/|//[^\n]*", re.S)
OVERRIDE_READS = {"RG32": 4, "RGU32": 4, "RG16": 2, "Q3G": 4, "Q3GI": 4, "Q3GF": 4, "CR_FLT": 4, "IMW": 4}
READ_RE = re.compile(r"\b(%s)\(\s*0x([0-9a-fA-F]{8})u?\s*\)" % "|".join(OVERRIDE_READS))


def override_refs(prog, ranges):
    """[(address, kind, width)] for the overrides' literal addresses (override_targets): a direct read through one of
    OVERRIDE_READS, else an address."""
    bd = os.path.join(ROOT, "build")
    reads, addrs = [], set()
    for f in sorted(os.listdir(bd)):
        if not (f.startswith("overrides") and f.endswith(".c")):
            continue
        t = open(os.path.join(bd, f), encoding="utf-8", errors="replace").read()
        if "IMG_ADDR" not in t and "sect_data" not in t:
            continue
        t = COMMENT_RE.sub(lambda m: " " * len(m.group(0)), t)   # (addresses named in comments are not uses)
        spans = []
        for m in READ_RE.finditer(t):
            reads.append((int(m.group(2), 16), "direct", OVERRIDE_READS[m.group(1)]))
            spans.append(m.span(2))
        for h in LIT_RE.finditer(t):
            if any(s <= h.start(1) < e for s, e in spans):
                continue
            addrs.add(int(h.group(1), 16))
    return [r for r in reads if any(lo <= r[0] <= hi for lo, hi in ranges)] +         [(a, "address", 0) for a in sorted(addrs) if any(lo <= a <= hi for lo, hi in ranges)]


LAST = {}   # the sets of the last classify (for the reports)


def classify(model, img_targets=()):
    """{span start: "loose" | "glued"} for the data spans of datagen's model, and the chains: a list of lists of spans
    that must stay together in this order (a loose span is a chain of one)."""
    import datagen
    prog = model.prog
    secs = json.load(open(os.path.join(ROOT, "raw", prog, "sections.json")))
    ranges = [(int(s["start"], 16), int(s["start"], 16) + s["size"]) for s in secs]
    refs = code_refs(prog, ranges)
    for a, (kind, v) in model.relocs.items():
        if kind == "data":
            refs.append((v, "address", 0))
    for a in img_targets:
        refs.append((a, "address", 0))
    refs += override_refs(prog, ranges)
    spans = model.data_spans
    seen, bad, far, strings = set(), set(), {}, set()
    unbounded = set()   # glued spans whose reach no type bounds: the chain runs on after them (see below)
    ends = set()        # span starts a loop compares against: the span before reaches up to there
    indexed = set()     # spans read through an index register: a biased base may reach back into the span before
    known = KNOWN_EXTENT.get(prog, {})
    for a, kind, w in refs:
        sp = datagen.span_containing(model, a)
        if sp is None or sp.island:
            continue
        seen.add(sp.start)
        if a in known:
            far[sp.start] = max(far.get(sp.start, 0), a + known[a])
        if kind == "end":
            if a == sp.start:
                ends.add(sp.start)
            else:
                bad.add(sp.start)
                unbounded.add(sp.start)
            continue
        if kind == "direct":
            if a + w > sp.end:
                bad.add(sp.start)   # read wider than the span: reaches exactly that far
                far[sp.start] = max(far.get(sp.start, 0), a + w)
            continue
        if kind == "address" and a == sp.start and is_string(model, sp):
            strings.add(sp.start)
            continue
        bad.add(sp.start)
        if kind == "indexed":
            indexed.add(sp.start)
        if sp.name in sized_uses(prog):
            # every use of its address is a call given its byte count (a save-game write of the global)
            far[sp.start] = max(far.get(sp.start, 0), sp.start + sized_uses(prog)[sp.name], sp.end)
        elif datagen.placeholder_decl(sp.decl) or declared_size(prog, sp) == 0 or not aggregate(prog, sp):
            # (a scalar type says how the code reads the global, not how far an object passed by its address goes:
            # Res_SetReference((ResRef *)&g_dwSputRoom_pCurrentRoom, ..) fills g_pCurrentSet after the `uint`)
            unbounded.add(sp.start)
        else:
            # a table or object Ghidra types: it reaches as far as its type
            far[sp.start] = max(far.get(sp.start, 0), sp.start + declared_size(prog, sp), sp.end)
    exported = exported_addrs(prog)
    for sp in spans:
        if sp.start in exported or sp.sec is None:
            bad.add(sp.start)   # a DLL's exported variable (the EXE reaches it by its own code), the .rdata/.data gap
            unbounded.add(sp.start)
            seen.add(sp.start)
    strings -= bad
    LAST.update(unbounded=unbounded, strings=strings, indexed=indexed, ends=ends)
    chains, cur = [], []
    glue, reach = False, 0
    prev = None
    for sp in spans:
        back = prev is not None and prev.start not in strings and (
            sp.start in unbounded or sp.start in indexed or sp.start not in seen or sp.start in ends)
        if glue or sp.start < reach or back:
            cur.append(sp)
        else:
            if cur:
                chains.append(cur)
            cur = [sp]
        if sp.start in bad:
            if sp.start in unbounded:
                glue = True
            reach = max(reach, sp.start + declared_size(prog, sp), far.get(sp.start, 0))
        elif sp.start not in seen:
            glue = True     # nothing names it: only a neighbour's reach gets there, so it stays with both
        elif sp.start in strings:
            glue = False
        prev = sp
        # A span read only directly keeps the glue of the chain it follows: it may be a field of the object before it,
        # filled through that object's address (PolyglotInitialize writes g_aPolyglotServices[2], which the code then
        # calls as UINT_008ddd88). A string taken by its address is an object of its own: the chain ends with it.
        # Backwards, a table or object holds on to the span before it unless that is a string (luaX_init walks its
        # reserved-word table from the address one entry in, reading ppuVar3[-1]), and so does a span nothing names.
    if cur:
        chains.append(cur)
    # A chain keeps its inner layout only from a 4-aligned start: datagen opens a new input section (4-aligned) at
    # every 4-aligned span, so a chain that started at 4k+2 would get padding inside it. Such a chain joins the one
    # before it (which then stays pinned with it, harmless).
    merged = []
    for c in chains:
        if merged and c[0].start % 4:
            merged[-1].extend(c)
        else:
            merged.append(c)
    return merged, seen, bad


def loose_starts(model, img_targets=()):
    """The starts of the spans datagen may define without a pinned section."""
    chains, seen, bad = classify(model, img_targets)
    return {c[0].start for c in chains if len(c) == 1 and c[0].start not in bad}


# Tables whose reads go further than any type says: stdMath_SinCos indexes three 4096-float tables from .rdata
# on through the gap into .data (docs/notes/raw_free_build.md).
KNOWN_EXTENT = {"GRIMFANDANGO.EXE": {0x004d7600: 0x4000, 0x004db600: 0x4000, 0x004df600: 0x4000}}


_SIZED = {}
SIZED_RE = re.compile(r"&\s*(\w+)\s*,\s*(0x[0-9a-fA-F]+|\d+)\s*\)")
ADDR_OF_RE = re.compile(r"&\s*(\w+)\b(?!\s*\[)")


def sized_uses(prog):
    """{name: bytes} for the globals whose every `&name` in the generated code is a call that is also given a byte
    count right after it, `(*writeFn)(&g_dwMovieJustFinished,4)`, `Mem_Copy(&DAT_00806618,palette,0x300)` excepted
    (the count must follow the address): the call reaches that many bytes and no further. The module data blocks
    (tools/datagen.py: place_in_modules) are not code and are left out."""
    if prog not in _SIZED:
        d = os.path.join(ROOT, "src", prog)
        sized, other = {}, set()
        for f in sorted(os.listdir(d)):
            if not f.endswith(".c") or f == "data.c":
                continue
            t = open(os.path.join(d, f), encoding="utf-8").read().split("/* ---- data only this file names")[0]
            for m in SIZED_RE.finditer(t):
                sized[m.group(1)] = max(sized.get(m.group(1), 0), int(m.group(2), 0))
            n_all = {}
            for m in ADDR_OF_RE.finditer(t):
                n_all[m.group(1)] = n_all.get(m.group(1), 0) + 1
            n_sized = {}
            for m in SIZED_RE.finditer(t):
                n_sized[m.group(1)] = n_sized.get(m.group(1), 0) + 1
            other |= {k for k, v in n_all.items() if v > n_sized.get(k, 0)}
        # (`_DAT_x` is a view of DAT_x: an unsized use of either counts for both)
        other |= {k.lstrip("_") for k in other} | {"_" + k for k in other}
        _SIZED[prog] = {k: v for k, v in sized.items() if k not in other and k.lstrip("_") not in other}
    return _SIZED[prog]


_STRUCT_SIZES = {}


def struct_sizes(prog):
    """{structure name: size} of every structure of the program (raw/<prog>/structs.json; datagen's STRUCTS holds only
    those the data uses)."""
    if prog not in _STRUCT_SIZES:
        s = json.load(open(os.path.join(ROOT, "raw", prog, "structs.json")))
        _STRUCT_SIZES[prog] = {k: v.get("size", 0) for k, v in s.items() if isinstance(v, dict)}
    return _STRUCT_SIZES[prog]


_GHIDRA_TYPES = {}


def ghidra_type(prog, addr):
    """Ghidra's type of the global at addr (raw/<prog>/globals.json), when the code declares it only as an address
    (`unsigned char NAME[]`, from an IMG_ADDR): `uint[12]` for g_aBaseModuleServices."""
    if prog not in _GHIDRA_TYPES:
        out = {}
        for line in open(os.path.join(ROOT, "raw", prog, "globals.json"), encoding="utf-8", errors="replace"):
            m = re.match(r"^\S+ @ ([0-9a-f]{8}) \[Label\] \((.+)\) xrefs=", line)
            if m:
                out[int(m.group(1), 16)] = m.group(2)
        _GHIDRA_TYPES[prog] = out
    return _GHIDRA_TYPES[prog].get(addr)


def declared_size(prog, sp):
    """The bytes Ghidra's type gives the span (0 when unknown): a table read by index goes at least that far."""
    import datagen
    if not sp.decl:
        return 0
    base, is_arr, count = sp.decl
    base = base.replace("const ", "").strip()
    if is_arr and not count:
        # declared only as an address (`unsigned char NAME[]`): Ghidra's own type, if it has one
        t = ghidra_type(prog, sp.start)
        return type_size(prog, t) if t and not t.startswith("undefined") else 0
    size = type_size(prog, base)
    return size * (count or 1) if is_arr else size


def aggregate(prog, sp):
    """True when the span's type is an array or a structure: a type that says how far the object goes."""
    base, is_arr, count = sp.decl
    if is_arr and not count:
        t = ghidra_type(prog, sp.start) or ""
        return "[" in t or t in struct_sizes(prog)
    return is_arr or base.replace("const ", "").strip() in struct_sizes(prog)


def type_size(prog, t):
    """The size of a Ghidra type name (`uint`, `VideoMode`, `char *`, `uint[12]`, `char[20][200]`), 0 if unknown."""
    import datagen
    t = t.replace("const ", "").strip()
    m = re.match(r"^(.*?)((?:\[\d+\])+)$", t)
    if m:
        n = 1
        for d in re.findall(r"\d+", m.group(2)):
            n *= int(d)
        return type_size(prog, m.group(1)) * n
    if t.endswith("*"):
        return 4
    if t in datagen.SCALARS:
        return datagen.SCALARS[t][1]
    return struct_sizes(prog).get(t, 0)


def is_string(model, sp):
    import datagen
    b = datagen.section_bytes(model, sp)
    if not (sp.name.startswith(("s_", "u_")) or (sp.decl and sp.decl[1] and sp.decl[0].replace("const ", "").strip() == "char")):
        return False
    # a string and nothing else: no pointer in it, only zeros after its NUL (s__STDIN_10026d04's span also holds the
    # first entry of luaX_init's reserved-word table)
    return b"\0" in b and not sp.relocs and not b[b.index(b"\0"):].strip(b"\0")


def exported_addrs(prog):
    p = os.path.join(ROOT, "raw", prog, "exports.json")
    out = set()
    if prog.endswith(".DLL") and os.path.exists(p):
        for line in open(p, encoding="utf-8", errors="replace"):
            m = re.match(r"^(\S+) -> ([0-9a-f]{8})", line.strip())
            if m:
                out.add(int(m.group(2), 16))
    return out

def explain(prog, addrs):
    """The instructions that reach each span at addrs other than by a direct access inside it (why it is glued)."""
    import datagen
    model = datagen.build_model(prog, os.path.join(ROOT, "src"))
    secs = json.load(open(os.path.join(ROOT, "raw", prog, "sections.json")))
    ranges = [(int(s["start"], 16), int(s["start"], 16) + s["size"]) for s in secs]
    names = {}
    for f in json.load(open(os.path.join(ROOT, "raw", prog, "functions.json"))):
        names[f["address"].lower().rjust(8, "0")] = f.get("name", "")
    want = {datagen.span_containing(model, a).start: a for a in addrs}
    for fa, body in json.load(open(os.path.join(ROOT, "raw", prog, "disasm.json"))).items():
        for line in body.split("\n"):
            for h in HEX.finditer(line.split(":", 1)[-1]):
                a = int(h.group(1), 16)
                sp = datagen.span_containing(model, a) if any(lo <= a < hi for lo, hi in ranges) else None
                if sp is not None and sp.start in want and not re.search(r"\[0x%x\]" % a, line.replace("0x00", "0x")):
                    print("%s %s(%s): %s" % (sp.name, names.get(fa, fa), fa, line.strip()))
    for a, (kind, v) in model.relocs.items():
        sp = datagen.span_containing(model, v) if kind == "data" else None
        if sp is not None and sp.start in want:
            print("%s pointed at from data 0x%08x" % (sp.name, a))

if __name__ == "__main__" and len(sys.argv) > 2 and sys.argv[1] == "explain":
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    explain(sys.argv[2], [int(a, 16) for a in sys.argv[3:]])
elif __name__ == "__main__":
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    import datagen
    for prog in sys.argv[1:] or datagen.PROGS:
        model = datagen.build_model(prog, os.path.join(ROOT, "src"))
        chains, seen, bad = classify(model)
        loose = [c for c in chains if len(c) == 1 and c[0].start not in bad]
        glued = [c for c in chains if not (len(c) == 1 and c[0].start not in bad)]
        nb = lambda c: sum(sp.end - sp.start for sp in c)
        print("%s: %d spans; loose %d (%d bytes); %d glued chains holding %d spans (%d bytes), longest %d spans (%d bytes)"
              % (prog, len(model.data_spans), len(loose), sum(nb(c) for c in loose), len(glued),
                 sum(len(c) for c in glued), sum(nb(c) for c in glued), max((len(c) for c in glued), default=0),
                 max((nb(c) for c in glued), default=0)))

