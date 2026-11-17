"""Which spans of the original data can leave the original layout (tools/datagen.py).

A span is reached by the original's code (raw/<prog>/disasm.json), by the data's own pointers, and by the addresses the
code uses as numbers (IMG_ADDR, in the generated code and in build/overrides*.c). Each reference is one of:

* direct: `[0xADDR]` with a known width. It reaches ADDR .. ADDR + width and nothing else.
* indexed: `[REG*s + 0xADDR]`, `[REG + 0xADDR]`. A table: how far it goes depends on the index.
* address: `PUSH 0xADDR`, `MOV ECX,0xADDR`, `LEA EAX,[0xADDR]`, a pointer in the data, an IMG_ADDR. Whatever receives it
  can walk on from there.
* end: `CMP reg,0xADDR`, a loop's end pointer. It reaches nothing itself; the nearest table before it (reached by
  address or index) reaches up to and including it.
* an address pushed for an Interlocked* import (`PUSH 0xADDR` / `CALL [slot]` or `CALL EDI` loaded from the slot) is
  a direct access of 4 bytes.
The overrides' macros that read one value at a literal address (RG32(0x...), Q3G(0x...): OVERRIDE_READS) are direct
reads; their other literals are addresses.

A span is *loose* when every reference to it is direct and ends inside it, or when it is a pure string (no pointer, only
zeros after its NUL; named s_ / typed char, or printable text by its bytes whatever its name) whose address is taken at
its start: then nothing reaches its neighbours through it. A GUID in .rdata taken by its address (a REFIID for
QueryInterface, recognised by its version and variant bits) reaches 16 bytes. Every other
span (a table, an object passed by address, a string indexed or entered in the middle, a value read wider than its
span) may be read on into what follows: it is *glued* to its neighbours. How far depends on what bounds it:
* a value read wider than its span reaches exactly that far;
* a span whose every `&name` in the generated code is a call given its byte count (`(*writeFn)(&g_dwMovieJustFinished,
  4)`, sized_uses) reaches that many bytes;
* a span whose Ghidra type is a structure or an array (names/types_data_extents_*.json) reaches as far as its type,
  plus a known extent for stdMath_SinCos's tables (KNOWN_EXTENT); a scalar type does not bound it (it says how the
  code reads the global: Res_SetReference((ResRef *)&g_dwSputRoom_pCurrentRoom, ..) fills g_pCurrentSet after the
  `uint`);
* a global the remaster's symbols named (names/orig_sizes.json, tools/orig_sizes.py: the remaster's i386 ELF has the
  same objects, aLookup 0x100, polyglotServices 0x20) reaches as far as that symbol's size, but no further than the next
  such global (the remaster grew some buffers: aHWVertices 8 MB against 1 MB); and such a global, an object of its
  own, ends the chain of an unbounded one before it, unless that one is a biased table base (biased(): Res_F*'s
  `&DAT_00824f14 + fh * 0x102c` with handles from 1 reaches over stdMemory's counters to the files);
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

    # `PUSH 0xADDR` / `CALL dword ptr [slot]` with an Interlocked* import: the call reads and writes the one dword
    # (the C runtime's InterlockedIncrement(&__unguarded_readlc_active))
    interlocked = set()
    for line in open(os.path.join(ROOT, "raw", prog, "data_items.txt"), encoding="utf-8", errors="replace"):
        mm = re.match(r"^PTR_Interlocked\w*_([0-9a-f]{8}) @ ", line)
        if mm:
            interlocked.add(int(mm.group(1), 16))
    gone = dropped_functions(prog) | replaced_functions(prog)
    for fa, body in json.load(open(os.path.join(ROOT, "raw", prog, "disasm.json"))).items():
        if fa.lower().rjust(8, "0") in gone:
            continue   # not in the rebuilt program (names/lib_replace.json): what it reached, nothing reaches now
        pushed = None   # the address the previous instruction pushed
        regs = set()    # registers holding an Interlocked* import
        for line in body.split("\n"):
            m = INSN.match(line)
            if not m:
                continue
            mn, ops = m.group(2).upper(), m.group(3)
            load = re.match(r"(E[A-Z]{2}),dword ptr \[0x([0-9a-f]+)\]$", ops.strip()) if mn == "MOV" else None
            if load:   # `MOV EDI,dword ptr [slot]` ... `CALL EDI`
                if int(load.group(2), 16) in interlocked:
                    regs.add(load.group(1))
                else:
                    regs.discard(load.group(1))
            call = re.match(r"dword ptr \[0x([0-9a-f]+)\]", ops) if mn == "CALL" else None
            hit = (call and int(call.group(1), 16) in interlocked) or (mn == "CALL" and ops.strip() in regs)
            if hit and pushed is not None and out and out[-1][:2] == (pushed, "address"):
                out[-1] = (pushed, "direct", 4)
            pushed = int(ops.strip()[2:], 16) if mn == "PUSH" and HEX.fullmatch(ops.strip()) else None
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
# Q3P / Q3I / Q3U / Q3F(IMG_ADDR(0x...), off): one dword read at the address plus off (overrides_asm_q3.c's
# `Q3P(IMG_ADDR(0x0080692c), 0)` reads g_pStd3D_CurDevice)
Q3_FIELD_RE = re.compile(r"Q3[PIUF]\(\s*IMG_ADDR\(0x([0-9a-fA-F]{8})\)\s*,\s*(0x[0-9a-fA-F]+|\d+)\s*\)")
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
        for m in Q3_FIELD_RE.finditer(t):
            reads.append((int(m.group(1), 16) + int(m.group(2), 0), "direct", 4))
            spans.append(m.span(1))
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
    unused = unused_spans(prog)
    starts0 = sorted(unused)
    import bisect

    def in_unused(a):
        i = bisect.bisect_right(starts0, a) - 1
        return i >= 0 and a < starts0[i] + unused[starts0[i]]

    for a, (kind, v) in model.relocs.items():
        if kind == "data" and not in_unused(a):   # (a pointer in data only dead code reads reaches nothing)
            refs.append((v, "address", 0))
    for a in img_targets:
        refs.append((a, "address", 0))
    refs += override_refs(prog, ranges)
    refs += override_name_refs(model)
    spans = model.data_spans
    seen, bad, far, strings = set(), set(), {}, set()
    unbounded = set()   # glued spans whose reach no type bounds: the chain runs on after them (see below)
    ends = set()        # span starts a loop compares against: the span before reaches up to there
    indexed = set()     # spans read through an index register: a biased base may reach back into the span before
    walked = set()      # spans reached through their address or an index (a table a loop may walk)
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
            elif not (aggregate(prog, sp) and declared_size(prog, sp) and a <= sp.start + declared_size(prog, sp)):
                # (inside an array or a structure Ghidra types, a loop's bound is one within the object: VbrAdpcm's
                # init loop stops at 0x8d78e8, a row into g_wDWave_aDeltaTable)
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
        if kind == "address" and is_guid(model, sp, a):
            # a COM interface or class id, handed to QueryInterface / CoCreateInstance as a REFIID: 16 bytes
            far[sp.start] = max(far.get(sp.start, 0), a + 16, sp.end)
            bad.add(sp.start)
            continue
        bad.add(sp.start)
        walked.add(sp.start)
        if kind == "indexed":
            indexed.add(sp.start)
        osz = orig_sizes(prog).get(sp.start)
        if osz and osz[1]:
            # the remaster's symbol of the same global has this size (tools/orig_sizes.py); the remaster grew some
            # buffers, so it goes no further than the next global that is an object of its own (named likewise)
            far[sp.start] = max(far.get(sp.start, 0), sp.end,
                                min(sp.start + osz[1], next_named(prog, sp.start)))
        elif sp.name in sized_uses(prog):
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
    # A loop's end pointer belongs to the table it walks: the nearest table or object before it reaches up to and
    # including it, over any global in between (InsaneTimer_Tick walks the timers from 0x8da60c `while (p <
    # &DAT_008da86c)`, past share_config and timer_thread.lastTime: a named global must not end that chain)
    starts = [sp.start for sp in spans]
    import bisect
    for e in ends:
        i = bisect.bisect_left(starts, e) - 1
        while i >= 0 and spans[i].start not in walked:
            i -= 1
        if i >= 0:
            far[spans[i].start] = max(far.get(spans[i].start, 0), e + 1)
    LAST.update(unbounded=unbounded, strings=strings, indexed=indexed, ends=ends)
    chains, cur = [], []
    glue, reach = False, 0
    glue_indexed = False   # the glue comes from a table read through an index
    holder, cuts = None, []   # the unbounded span whose chain runs on; where a named global ended one (for reports)
    prev = None
    for sp in spans:
        if glue and sp.start >= reach and sp.start in orig_sizes(prog) and not glue_indexed \
                and os.environ.get("GRIM_ORIG_BOUNDARY", "1") == "1" and boundary_allowed(sp.start):
            # (GRIM_ORIG_BOUNDARY=0 turns it off; GRIM_BOUNDARY_RANGES=lo-hi limits it, to bisect)
            # a global the remaster has a symbol of is an object of its own: the untyped object before it ends here.
            # Not for a table read through an index: a biased base reaches over other globals (Res_F*'s
            # `fh * 0x102c + 0x824f14` skips stdMemory's counters to the files at 0x825f40)
            glue = False
            cuts.append((holder, sp.start))
        inside = not glue and sp.start < reach   # within the known extent of an object before it
        back = prev is not None and prev.start not in strings and prev.start not in unused and sp.start not in unused and (
            sp.start in unbounded or sp.start in indexed or sp.start not in seen or sp.start in ends)
        if glue or sp.start < reach or back:
            cur.append(sp)
        else:
            if cur:
                chains.append(cur)
            cur = [sp]
        if sp.start in bad:
            if sp.start in unbounded and not (inside and sp.start in indexed and sp.start not in ends):
                holder = sp.start
                # (inside the extent of a table with a known size, an index at a field offset stays in that table:
                # aHWVertices's `[EAX*0x20 + 0x6f0fd4]` is its +0x1c field; not an object passed by its address there,
                # nor a loop's end pointer: the dirty rect at 0x8a92a8, right after the draw-item pool, is both)
                glue = True
                # (a table with an original name is an object that starts there; a nameless base may be biased)
                glue_indexed = glue_indexed or (sp.start in indexed and biased(prog, sp))
            reach = max(reach, sp.start + declared_size(prog, sp), far.get(sp.start, 0))
        elif sp.start in unused and sp.start not in seen:
            # data only the code the rebuild leaves out read (names/data_unused.json, zeroed by datagen): nothing live
            # reaches it, nor the span before it (tools/data_unused.py), so it holds nothing together
            glue = glue_indexed = False
        elif sp.start not in seen:
            glue = True     # nothing names it: only a neighbour's reach gets there, so it stays with both
        elif sp.start in strings:
            glue = glue_indexed = False
        prev = sp
        # A span read only directly keeps the glue of the chain it follows: it may be a field of the object before it,
        # filled through that object's address (PolyglotInitialize writes g_aPolyglotServices[2], which the code then
        # calls as UINT_008ddd88). A string taken by its address is an object of its own: the chain ends with it.
        # Backwards, a table or object holds on to the span before it unless that is a string (luaX_init walks its
        # reserved-word table from the address one entry in, reading ppuVar3[-1]), and so does a span nothing names.
    if cur:
        chains.append(cur)
    LAST["cuts"] = cuts
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
# (The original stdMath_SinCos and stdMath_Tan read their 4096-float tables through biased bases, 0x4d7600 and 0x4db600
# + index * 4 landing in g_aSinTable at 0x4df600: it looked like tables reaching from .rdata into .data. Both are
# replaced by hand-written versions that index g_aSinTable and aTanTable themselves, so nothing reads that way now.)
KNOWN_EXTENT = {"GRIMFANDANGO.EXE": {
    # Res_F*: `fh * 0x102c + 0x824f14`, handles 1..128, Res_FOpen's end pointer
    0x00824f14: 0x8a7540 - 0x824f14}}


_ORIG = {}


def orig_sizes(prog):
    """{address: (original name, size or None)} of the globals the remaster's symbols named (names/orig_sizes.json,
    tools/orig_sizes.py)."""
    if prog not in _ORIG:
        p = os.path.join(ROOT, "names", "orig_sizes.json")
        d = json.load(open(p)).get(prog, {}) if os.path.exists(p) else {}
        if os.environ.get("GRIM_NO_ORIG") == "1":   # (to bisect: the classification without the remaster's symbols)
            d = {}
        _ORIG[prog] = {int(a, 16): tuple(v) for a, v in d.items()}
    return _ORIG[prog]


_STRIDES = {}
STRIDE_RE = re.compile(r"&(\w+) \+ \w+ \* (0x[0-9a-f]+|\d+)\b")


def biased(prog, sp):
    """True when the table indexed at sp's start cannot start there: the code steps it by a stride
    (`&DAT_00824f14 + fh * 0x102c`) and a global the remaster names (an object of its own) lies within the first
    stride, so the index starts above 0 (Res_F*'s handles 1..128 over stdMemory's counters)."""
    if prog not in _STRIDES:
        d = os.path.join(ROOT, "src", prog)
        st = {}
        for f in sorted(os.listdir(d)):
            if f.endswith(".c") and f != "data.c":
                for m in STRIDE_RE.finditer(open(os.path.join(d, f), encoding="utf-8").read()):
                    st[m.group(1)] = max(st.get(m.group(1), 0), int(m.group(2), 0))
        _STRIDES[prog] = st
    s = _STRIDES[prog].get(sp.name, 0)
    return s > 0 and next_named(prog, sp.start) < sp.start + s


def boundary_allowed(a):
    """GRIM_BOUNDARY_RANGES=lo-hi,.. (hex): the named-global boundary only there (to bisect a wrong one)."""
    r = os.environ.get("GRIM_BOUNDARY_RANGES")
    if not r:
        return True
    return any(int(x.split("-")[0], 16) <= a < int(x.split("-")[1], 16) for x in r.split(","))


def next_named(prog, a):
    """The address of the next global after a that has an original name (an object of its own), or no bound."""
    import bisect
    names = sorted(orig_sizes(prog))
    i = bisect.bisect_right(names, a)
    return names[i] if i < len(names) else 1 << 40


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
    if not sp.decl:
        return False
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


_REPLACED = {}
REPLACED_RE = re.compile(r"/\* ---- 0x([0-9a-f]{8})  \S+ ---- \*/\n(?:/\*[^\n]*\*/\n)*?/\* replaced by the hand-written version")


def replaced_functions(prog):
    """The addresses of the functions the rebuild takes from build/overrides*.c (the generated source marks each one
    `replaced by the hand-written version` and leaves it out): their original code is not in the program, the
    override's own uses of the data count instead (override_name_refs)."""
    if prog not in _REPLACED:
        d = os.path.join(ROOT, "src", prog)
        out = set()
        if os.path.isdir(d):
            for f in os.listdir(d):
                if f.endswith(".c"):
                    out |= set(REPLACED_RE.findall(open(os.path.join(d, f), encoding="utf-8").read()))
        _REPLACED[prog] = out
    return _REPLACED[prog]


def override_name_refs(model):
    """[(address, kind, width)] for the data the overrides name. The original code of a replaced function no longer
    counts, so the override's own text does: a name taken with `&`, indexed with `[`, or that of an array is an
    address (whatever receives it may walk on); a name read or written as it is, a direct access inside the span."""
    import datagen
    names = {}
    for sp in model.data_spans:
        names[sp.name] = sp
        for al in sp.aliases:
            names[al] = sp
    bd = os.path.join(ROOT, "build")
    out = []
    for f in sorted(os.listdir(bd)):
        if not (f.startswith("overrides") and f.endswith(".c")):
            continue
        t = COMMENT_RE.sub(" ", open(os.path.join(bd, f), encoding="utf-8", errors="replace").read())
        for m in re.finditer(r"(&\s*)?\b_?([A-Za-z_]\w*)\b(\s*\[)?", t):
            sp = names.get(m.group(2))
            if sp is None or sp.island:
                continue
            is_arr = sp.decl and sp.decl[1]
            if m.group(1) or m.group(3) or is_arr:
                out.append((sp.start, "address", 0))
            else:
                out.append((sp.start, "direct", sp.end - sp.start))
    # (an asm label `__asm__("_name")` binds a C name of the override to the global: the C name's uses are the
    # global's, which the scan above misses when the C name differs; count the global as taken by address)
    for f in sorted(os.listdir(bd)):
        if f.startswith("overrides") and f.endswith(".c"):
            for m in re.finditer(r'__asm__\("_(\w+)"\)', open(os.path.join(bd, f), encoding="utf-8", errors="replace").read()):
                sp = names.get(m.group(1))
                if sp is not None and not sp.island:
                    out.append((sp.start, "address", 0))
    return out


def dropped_functions(prog):
    """The addresses of the original's functions the rebuild leaves out (names/lib_replace.json: the dead C runtime,
    the runtime msvcrt.dll replaces, and zlib, which the system zlib replaces unless GRIM_BUNDLED_ZLIB is set, as in
    tools/build_src.py)."""
    p = os.path.join(ROOT, "names", "lib_replace.json")
    out = set()
    if os.path.exists(p):
        for cat, addrs in json.load(open(p)).get(prog, {}).items():
            if cat == "zlib" and os.environ.get("GRIM_BUNDLED_ZLIB"):
                continue
            out |= {a.lower().rjust(8, "0") for a in addrs}
    return out


def unused_spans(prog):
    """{start: size} of names/data_unused.json: data nothing in the rebuilt program reads (tools/data_unused.py)."""
    p = os.path.join(ROOT, "names", "data_unused.json")
    if not os.path.exists(p):
        return {}
    return {int(r["addr"], 16): r["size"] for r in json.load(open(p)).get(prog, [])}


def is_guid(model, sp, a):
    """True when the 16 bytes at a, in the read-only data, are a GUID: the version nibble of Data3 1..5 and the variant
    bits of Data4[0] 10 (the DirectX interface ids, `IID_IDirectDraw` .. `...-11cf-bfc7-444553540000`)."""
    import datagen
    if sp.sec is None or sp.sec["name"] != ".rdata" or a + 16 > sp.end:
        return False
    b = datagen.section_bytes(model, sp)[a - sp.start:a - sp.start + 16]
    return len(b) == 16 and 1 <= (b[7] >> 4) <= 5 and (b[8] & 0xc0) == 0x80 and b.strip(b"\0") != b""


def is_string(model, sp):
    import datagen
    b = datagen.section_bytes(model, sp)
    # a string and nothing else: no pointer in it, only zeros after its NUL (s__STDIN_10026d04's span also holds the
    # first entry of luaX_init's reserved-word table)
    if b"\0" not in b or sp.relocs or b[b.index(b"\0"):].strip(b"\0"):
        return False
    if sp.name.startswith(("s_", "u_")) or (sp.decl and sp.decl[1] and sp.decl[0].replace("const ", "").strip() == "char"):
        return True
    # by its bytes too, whatever Ghidra named it: printable text of two characters or more, then the NUL (the C
    # runtime's locale names in CHORE.DLL, `DAT_1000e118` = "LC_TIME", held a chain of 237 spans open)
    text = b[:b.index(b"\0")]
    return len(text) >= 2 and all(32 <= c < 127 or c in (9, 10, 13) for c in text)


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

