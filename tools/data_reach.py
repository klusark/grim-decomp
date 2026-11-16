"""Which spans of the original data can leave the original layout (tools/datagen.py).

A span is reached by the original's code (raw/<prog>/disasm.json), by the data's own pointers, and by the addresses the
code uses as numbers (IMG_ADDR, in the generated code and in build/overrides*.c). Each reference is one of:

* direct: `[0xADDR]` with a known width. It reaches ADDR .. ADDR + width and nothing else.
* indexed: `[REG*s + 0xADDR]`, `[REG + 0xADDR]`. A table: how far it goes depends on the index.
* address: `PUSH 0xADDR`, `MOV ECX,0xADDR`, `LEA EAX,[0xADDR]`, a pointer in the data, an IMG_ADDR. Whatever receives it
  can walk on from there.

A span is *loose* when every reference to it is direct and ends inside it, or when it is a string (a NUL inside its
span) whose address is taken at its start: then nothing reaches its neighbours through it. Every other span (a table, an
object passed by address, a string indexed or entered in the middle, a value read wider than its span) may be read on
into what follows, so it starts a *glued* chain. The chain runs on through every span read only directly (it may be a
field of the object, filled through the object's address: PolyglotInitialize writes g_aPolyglotServices[2], which the
code calls as UINT_008ddd88), through spans nothing refers to (padding, unused tails, the gap between .rdata and .data
that the sine/cosine quadrant tables read across), and over the extent of the object's type, up to and including the
next string taken by its address, an object of its own. Backwards, a chain also takes in the span before it unless that
is a string (luaX_init walks its reserved-word table from one entry in, reading ppuVar3[-1]), and a span nothing names
stays with both its neighbours. A glued chain keeps the original layout among its members; the chains themselves and
the loose spans may be placed anywhere.

usage: python -I tools/data_reach.py [PROG...]      the counts
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
                    out.append((a, "address", 0))
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
    for a in override_targets(prog, ranges):
        refs.append((a, "address", 0))
    spans = model.data_spans
    seen, bad, far, strings = set(), set(), {}, set()
    known = KNOWN_EXTENT.get(prog, {})
    for a, kind, w in refs:
        sp = datagen.span_containing(model, a)
        if sp is None or sp.island:
            continue
        seen.add(sp.start)
        if a in known:
            far[sp.start] = max(far.get(sp.start, 0), a + known[a])
        if kind == "direct":
            if a + w > sp.end:
                bad.add(sp.start)
            continue
        if kind == "address" and a == sp.start and is_string(model, sp):
            strings.add(sp.start)
            continue
        bad.add(sp.start)
    exported = exported_addrs(prog)
    for sp in spans:
        if sp.start in exported or sp.sec is None:
            bad.add(sp.start)   # a DLL's exported variable (the EXE reaches it by its own code), the .rdata/.data gap
            seen.add(sp.start)
    strings -= bad
    chains, cur = [], []
    glue, reach = False, 0
    prev = None
    for sp in spans:
        back = prev is not None and prev.start not in strings and (sp.start in bad or sp.start not in seen)
        if glue or sp.start < reach or back:
            cur.append(sp)
        else:
            if cur:
                chains.append(cur)
            cur = [sp]
        if sp.start in bad:
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


def declared_size(prog, sp):
    """The bytes Ghidra's type gives the span (0 when unknown): a table read by index goes at least that far."""
    import datagen
    if not sp.decl:
        return 0
    base, is_arr, count = sp.decl
    base = base.replace("const ", "").strip()
    if base.endswith("*"):
        size = 4
    elif base in datagen.SCALARS:
        size = datagen.SCALARS[base][1]
    elif base in datagen.STRUCTS:
        size = datagen.STRUCTS[base]["size"]
    else:
        return 0
    return size * (count or 1) if is_arr else size


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


if __name__ == "__main__":
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
