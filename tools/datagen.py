"""The original's initialised data as C: src/<prog>/data.c, written by tools/build_src.py.

Each program's .rdata and .data (raw/<prog>/sections/*.bin, dumped from Ghidra by tools/export_data.py) are split into
spans. A span starts at:
* the section start;
* every global the decompiled code declares (globals.h / functions.h), and every array of scalars Ghidra types
  (raw/<prog>/globals.json), named by the code or not;
* every address the code used as a number (`IMG_ADDR(0x...)`, which build_src rewrites into the span's name);
* every address a pointer in the data points at.
A point inside a declared array of N scalars that names no typed global of its own (a biased base the code indexes
from, a pointer into the table) starts no span: its names become aliases at their offset.

Each span becomes one C definition with its bytes as the initialiser, in the original order. A span declared as a
scalar or an array of scalars gets values (floats as the shortest decimal that reads back as the same bits); when the
span is longer than the type, the rest follows as a static `<name>__tail` byte array in the same section run. The
layout is pinned:
* every span is placed in a section `.data$grim_<key>`, and the i686 ld script sorts `*(SORT(.data$*))` by name, so
  the spans keep the original order whatever file they are in;
* a key is the address of the 4-aligned span that opens a run, because an input section is at least 4-aligned and
  would pad an odd-sized span;
* within a run, `no_reorder` keeps the definitions in order, and `aligned(1)` stops gcc from padding large arrays.

The code still reads across globals (tables indexed past their end, the sine/cosine quadrant tables that run from
.rdata into .data), so the layout stays the original's until the data is typed (docs/notes/raw_free_build.md).

Pointers in the data use the same rules as the old build/gendata.py (data.s): a dword that holds a function start is
the function, an address inside a section is that span plus an offset, and text (raw/<prog>/strings.txt) and
names/data_relocs.json decide the doubtful cases. A data item that lives in the code section (DirectInput's data
formats) becomes a span of its own, with whatever it points at; the code bytes themselves are not copied.

`sect_rdata` / `sect_data` (ghidra_types.h) remain as labels on the first span of each section, for the hand-written
overrides that compute data addresses from the original's (IMG_ADDR in build/overrides*.c).

usage: python -I tools/datagen.py report [PROG...]     the data report (spans, typed and untyped bytes)
       (build_src.py calls generate())"""
import bisect
import json
import math
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "build"))
import dllnames  # noqa: E402  decorated names of the DLLs' callee-pop exports (raw/<DLL>/stdcall_funcs.json)

ADDR_SUFFIX = re.compile(r"_([0-9a-f]{8})$")
IDENT = re.compile(r"[A-Za-z_]\w*")
IMG_ADDR_RE = re.compile(r"IMG_ADDR\(0x([0-9a-f]{8})\)")
PROGS = ["GRIMFANDANGO.EXE", "LUA.DLL", "IMUSE.DLL", "CHORE.DLL"]
_DLL_STD = None


def dll_std():
    global _DLL_STD
    if _DLL_STD is None:
        _DLL_STD = dllnames.load()
    return _DLL_STD


# C type of a declared scalar -> (C type, size, format)
SCALARS = {
    "int": ("int", 4, "d"), "long": ("int", 4, "d"), "uint": ("unsigned int", 4, "x"), "ulong": ("unsigned int", 4, "x"),
    "undefined4": ("unsigned int", 4, "x"), "dword": ("unsigned int", 4, "x"), "DWORD": ("unsigned int", 4, "x"),
    "UINT": ("unsigned int", 4, "x"), "float": ("float", 4, "f"), "double": ("double", 8, "f"),
    "short": ("short", 2, "d"), "ushort": ("unsigned short", 2, "x"), "word": ("unsigned short", 2, "x"),
    "undefined2": ("unsigned short", 2, "x"), "char": ("char", 1, "d"), "byte": ("unsigned char", 1, "x"),
    "uchar": ("unsigned char", 1, "x"), "undefined": ("unsigned char", 1, "x"), "undefined1": ("unsigned char", 1, "x"),
    "bool": ("unsigned char", 1, "x"), "sbyte": ("signed char", 1, "d"), "schar": ("signed char", 1, "d"),
}


class Span:
    __slots__ = ("start", "end", "name", "aliases", "inner", "sec", "island", "relocs", "decl")

    def __init__(self, start, end, name, sec, island=False):
        self.start, self.end, self.name, self.sec, self.island = start, end, name, sec, island
        self.aliases = []
        self.inner = []  # (name, offset): labels inside a declared array (build_model)
        self.relocs = {}  # offset in span -> ("data", address) | ("func", asm name)
        self.decl = None  # declared C type in globals.h: (base, is_array)


class Model:
    pass


# ---------------------------------------------------------------------------------------------- inputs

def load_raw(prog):
    raw = os.path.join(ROOT, "raw", prog)
    secs = json.load(open(os.path.join(raw, "sections.json")))
    for s in secs:
        s["start"] = int(s["start"], 16)
        s["bytes"] = open(os.path.join(raw, "sections", s["file"]), "rb").read()
        s["key"] = s["name"].strip(".")
    text = (0, 0)
    for line in open(os.path.join(raw, "segments.txt")):
        if line.startswith(".text:"):
            lo, hi = line.split(":", 1)[1].strip().split(" - ")
            text = (int(lo, 16), int(hi, 16))
    funcs = {int(f["address"], 16): f for f in json.load(open(os.path.join(raw, "functions.json")))}
    named, typed_arrays = {}, {}
    for line in open(os.path.join(raw, "globals.json"), encoding="utf-8", errors="replace"):
        m = re.match(r"^(\S+) @ ([0-9a-f]{8}) ", line)
        if m:
            named[m.group(1)] = int(m.group(2), 16)
            t = re.match(r"^\S+ @ [0-9a-f]{8} \[Label\] \((\w+)\[(\d+)\]\)", line)
            if t and IDENT.fullmatch(m.group(1)):
                typed_arrays[m.group(1)] = (t.group(1), True, int(t.group(2)))
    tb = None
    tbp = os.path.join(raw, "textblob.json")
    if os.path.exists(tbp):
        tb = json.load(open(tbp))
        tb["start"] = int(tb["start"], 16)
        tb["bytes"] = open(os.path.join(raw, "sections", tb["file"]), "rb").read()
    item_names = {}
    for line in open(os.path.join(raw, "data_items.txt"), encoding="utf-8", errors="replace"):
        m = re.match(r"^(\S+) @ ([0-9a-f]{8}) ", line)
        if m and IDENT.fullmatch(m.group(1)) and ADDR_SUFFIX.search(m.group(1)) \
                and ADDR_SUFFIX.search(m.group(1)).group(1) == m.group(2):
            item_names.setdefault(int(m.group(2), 16), m.group(1))
    strings = []
    for line in open(os.path.join(raw, "strings.txt"), encoding="utf-8", errors="replace"):
        m = re.match(r"^([0-9a-f]{8}): \"(.*)\"\s*$", line)
        if m and not re.fullmatch(r"[0-9a-f]{8}", m.group(2)):
            strings.append(int(m.group(1), 16))
    try:
        dr = json.load(open(os.path.join(ROOT, "names", "data_relocs.json"))).get(prog, {})
    except (OSError, ValueError):
        dr = {}
    return secs, text, funcs, named, tb, item_names, strings, dr, typed_arrays


def placeholder_decl(d):
    """A declaration that says nothing about the bytes: none, or Ghidra's `undefined*` (a label the code only addresses)."""
    return d is None or d[0].replace("const ", "").strip().startswith("undefined")


def array_extent(d):
    """Bytes a declared array of N scalars covers (0 for anything else)."""
    if d is None or not d[1] or not d[2]:
        return 0
    sc = SCALARS.get(d[0].replace("const ", "").strip())
    return d[2] * sc[1] if sc and not placeholder_decl(d) else 0


def declared(srcdir, prog):
    """name -> (base type, is array, element count or None) for every `extern T name;` of globals.h / functions.h."""
    out = {}
    for hdr in ("globals.h", "functions.h"):
        p = os.path.join(srcdir, prog, hdr)
        if not os.path.exists(p):
            continue
        for line in open(p, encoding="utf-8"):
            m = re.match(r"^extern (.*?);", line)
            if not m or m.group(1).startswith("code ") and "*" not in m.group(1):
                continue
            d = m.group(1)
            if "(" in d:  # function pointer declarator: name inside the parens
                mm = re.search(r"\(\s*(?:STDCALL\s*)?\*\s*([A-Za-z_]\w*)\s*\)", d)
                if mm:
                    out[mm.group(1)] = ("code *", False, None)
                continue
            mm = re.search(r"([A-Za-z_]\w*)\s*(\[\s*(\d*)\s*\])?$", d)
            if mm:
                count = int(mm.group(3)) if mm.group(3) else None
                out[mm.group(1)] = (d[:mm.start()].strip(), bool(mm.group(2)), count)
    return out


# ---------------------------------------------------------------------------------------------- the model

def build_model(prog, srcdir, img_targets=()):
    secs, (text_lo, text_hi), funcs, named, tb, item_names, string_addrs, dr, typed_arrays = load_raw(prog)
    std = dll_std()
    decls = declared(srcdir, prog)
    # arrays of scalars that Ghidra types but no code names (a table the code reaches only through a biased base, as
    # yacc's yypgoto): their own span all the same, so the bytes take the type
    for n, d in typed_arrays.items():
        if n not in decls and array_extent(d):
            decls[n] = d

    def section_of(addr):
        for s in secs:
            if s["start"] <= addr < s["start"] + s["size"]:
                return s
        return None

    def in_text_blob(addr):
        return tb is not None and tb["start"] <= addr < tb["start"] + tb["size"] and addr not in funcs

    def func_name(v, island=False):
        f = funcs.get(v)
        if not f or f.get("isExternal"):
            return None
        if f.get("isThunk") and f["name"].startswith(("thunk_", "FUN_") if island else ("FUN_",)):
            return None
        return std.get(f["name"], "_" + f["name"])

    # labels: the declared names, as build/gendata.py placed them
    placed, text_syms, code_stubs = {}, {}, []
    for n in decls:
        if n.endswith("_exref") or n.startswith(("LAB_", "switchD_")):
            continue
        m = ADDR_SUFFIX.search(n)
        addr = int(m.group(1), 16) if m else named.get(n)
        if addr is None:
            continue
        if section_of(addr) is None:
            if in_text_blob(addr) and not n.startswith(("FUN_", "thunk_")):
                off0 = addr - tb["start"]
                if tb["bytes"][off0:off0 + 2] == b"\xff\x25":
                    code_stubs.append((addr, n, int.from_bytes(tb["bytes"][off0 + 2:off0 + 6], "little")))
                else:
                    text_syms.setdefault(addr, []).append(n)
            continue
        placed.setdefault(addr, []).append(n)
    island = None
    if text_syms:
        island = (min(text_syms) & ~0xf, max(text_syms) + 0x400)

    # byte ranges that are text: dwords inside them are never pointers ("Dir\0" looks like an address in .data)
    text_ranges = []
    for a in string_addrs:
        s = section_of(a)
        if s is None:
            continue
        off = a - s["start"]
        end = s["bytes"].find(b"\0", off)
        if end < 0:
            end = len(s["bytes"])
        text_ranges.append((a, s["start"] + end + 1))
    text_ranges.sort()

    def in_text(addr):
        i = bisect.bisect_right(text_ranges, (addr, 1 << 40)) - 1
        return i >= 0 and text_ranges[i][0] <= addr < text_ranges[i][1]

    def looks_like_text(b4):
        return all(c == 0 or 9 <= c <= 13 or 32 <= c <= 126 for c in b4) and sum(32 <= c <= 126 for c in b4) >= 3

    not_ptr = {int(a, 16) for a in dr.get("not_pointers", [])}
    force_ptr = {int(a, 16) for a in dr.get("pointers", [])}

    # pointers in the data sections: address -> ("data", target) | ("func", asm name)
    relocs = {}
    for s in secs:
        data, base = s["bytes"], s["start"]
        labels = {a - base for a in placed if base <= a < base + s["size"]}
        for off in range(0, len(data) - 3, 4):
            a = base + off
            if any((off + k) in labels for k in (1, 2, 3)) or (in_text(a) and a not in force_ptr) or a in not_ptr:
                continue
            v = int.from_bytes(data[off:off + 4], "little")
            if looks_like_text(data[off:off + 4]) and v not in funcs and a not in force_ptr:
                continue
            if text_lo <= v <= text_hi:
                fn = func_name(v)
                if fn:
                    relocs[a] = ("func", fn)
                continue  # a code address that is no function start keeps its value
            if section_of(v) is not None and v != 0:
                relocs[a] = ("data", v)

    # the data items of the code section, and what they point at inside it
    island_spans = {}  # start -> end
    if island:
        func_starts = sorted(a for a in funcs if tb["start"] <= a < tb["start"] + tb["size"])
        todo = sorted(text_syms)
        points = set(todo)
        while todo:
            a = todo.pop()
            if a in island_spans:
                continue
            i = bisect.bisect_right(func_starts, a)
            nxt_fn = func_starts[i] if i < len(func_starts) else tb["start"] + tb["size"]
            later = [p for p in points if p > a]
            end = min([nxt_fn, island[1]] + later)
            island_spans[a] = end
            for off in range(a - tb["start"], end - tb["start"] - 3):
                if off % 4 or any(tb["start"] + off + k in text_syms for k in (1, 2, 3)):
                    continue
                v = int.from_bytes(tb["bytes"][off:off + 4], "little")
                ra = tb["start"] + off
                if section_of(v) is not None and v != 0:
                    relocs[ra] = ("data", v)
                elif func_name(v, island=True):
                    relocs[ra] = ("func", func_name(v, island=True))
                elif island[0] <= v < island[1]:
                    relocs[ra] = ("data", v)
                    if v not in points:
                        points.add(v)
                        todo.append(v)
                        # a new point inside an earlier span ends that span there
                        for st in list(island_spans):
                            if st < v < island_spans[st]:
                                del island_spans[st]
                                todo.append(st)
        for st, en in island_spans.items():
            if any(st < p < en for p in points):
                raise SystemExit("datagen: island span %#x-%#x overlaps another" % (st, en))

    # split points of the data sections
    def inside_reloc(p):
        return any((p - k) in relocs for k in (1, 2, 3))

    model = Model()
    model.prog, model.secs, model.relocs, model.std = prog, secs, relocs, std
    model.code_stubs, model.decls = code_stubs, decls
    model.img = {}
    spans = []
    used_names = set(decls)
    for s in secs:
        base, size = s["start"], s["size"]
        pts = {base}
        pts |= {a for a in placed if base <= a < base + size}
        pts |= {a for a in img_targets if base <= a < base + size}
        pts |= {v for k, v in relocs.values() if k == "data" and base <= v < base + size}
        pts |= {mem for _, _, mem in code_stubs if base <= mem < base + size}
        pts = sorted(p for p in pts if p in placed or p == base or not inside_reloc(p))
        # a declared array of N scalars covers its whole extent: a point inside it that names no typed global of its
        # own (a biased base the code indexes from, as yacc's `yypgoto - YYNTBASE`, a pointer or IMG_ADDR into it)
        # stays inside, its names aliases at their offset
        inner, kept, cover = {}, [], None
        for p in pts:
            if cover is not None and p < cover[1] and all(placeholder_decl(decls.get(n)) for n in placed.get(p, [])):
                inner.setdefault(cover[0], []).extend((n, p - cover[0]) for n in placed.get(p, []))
                continue
            kept.append(p)
            ext = max((array_extent(decls.get(n)) for n in placed.get(p, [])), default=0)
            cover = (p, p + ext) if ext else (cover if cover is not None and p < cover[1] else None)
        pts = kept
        for i, p in enumerate(pts):
            end = pts[i + 1] if i + 1 < len(pts) else base + size
            names = placed.get(p, [])
            if names:
                name, aliases = names[0], names[1:]
            else:
                name = item_names.get(p)
                if not name or name in used_names:
                    name = "DAT_%08x" % p
                aliases = []
            used_names.add(name)
            sp = Span(p, end, name, s)
            sp.aliases = aliases
            sp.inner = inner.get(p, [])
            spans.append(sp)
        # the gap from the end of .rdata up to the next section, at the original distance
        nxt = next((t for t in secs if t["start"] > base), None)
        if s["name"] == ".rdata" and nxt is not None and nxt["start"] > base + size:
            gap = Span(base + size, nxt["start"], "grim_gap_%s" % s["key"], None)
            spans.append(gap)
    for st in sorted(island_spans):
        names = text_syms.get(st, [])
        name = names[0] if names else (item_names.get(st) if item_names.get(st) not in used_names else None) or "DAT_%08x" % st
        used_names.add(name)
        sp = Span(st, island_spans[st], name, None, island=True)
        sp.aliases = names[1:]
        spans.append(sp)
    spans.sort(key=lambda sp: (sp.island, sp.start))
    model.spans = spans
    model.starts = [sp.start for sp in spans if not sp.island]
    model.data_spans = [sp for sp in spans if not sp.island]
    model.island_by_start = {sp.start: sp for sp in spans if sp.island}
    model.tb = tb
    # attach relocations to their spans
    for a in sorted(relocs):
        sp = span_containing(model, a)
        if sp is None:
            continue
        sp.relocs[a - sp.start] = relocs[a]
    for sp in spans:
        d = decls.get(sp.name)
        if d:
            sp.decl = d
    return model


def span_containing(model, a):
    isl = None
    for st, sp in model.island_by_start.items():
        if st <= a < sp.end:
            isl = sp
    if isl is not None:
        return isl
    i = bisect.bisect_right(model.starts, a) - 1
    if i < 0:
        return None
    sp = model.data_spans[i]
    return sp if sp.start <= a < sp.end else None


def resolve(model, a):
    """(span, offset) of an address of a data section, a section's end included (the last span + its length)."""
    sp = span_containing(model, a)
    if sp is not None:
        return sp, a - sp.start
    for s in model.secs:
        if a == s["start"] + s["size"]:
            last = [x for x in model.data_spans if x.sec is s][-1]
            return last, a - last.start
    return None, None


def section_bytes(model, sp):
    """The span's bytes; zero past the initialised part of its section, and for the gap."""
    if sp.island:
        tb = model.tb
        return tb["bytes"][sp.start - tb["start"]:sp.end - tb["start"]]
    if sp.sec is None:
        return bytes(sp.end - sp.start)
    s = sp.sec
    b = s["bytes"][sp.start - s["start"]:sp.end - s["start"]]
    return b + bytes(sp.end - sp.start - len(b))


# ---------------------------------------------------------------------------------------------- C text

def c_string(b):
    out = []
    for c in b:
        ch = chr(c)
        if ch == '"' or ch == "\\":
            out.append("\\" + ch)
        elif ch == "?":
            out.append("\\?")
        elif ch == "\n":
            out.append("\\n")
        elif ch == "\t":
            out.append("\\t")
        elif 32 <= c < 127:
            out.append(ch)
        else:
            out.append("\\%03o" % c)
    return '"' + "".join(out) + '"'


def byte_list(b, indent="    "):
    b = b.rstrip(b"\0")
    if not b:
        return "{0}"
    rows = [", ".join("0x%02x" % c for c in b[i:i + 16]) for i in range(0, len(b), 16)]
    if len(rows) == 1:
        return "{ " + rows[0] + " }"
    return "{\n" + ",\n".join(indent + r for r in rows) + "\n}"


def scalar_value(fmt, ctype, size, b):
    if fmt == "f":
        v = struct.unpack("<f" if size == 4 else "<d", b)[0]
        if math.isnan(v):
            return None  # (the payload and sign of a NaN have no portable literal: the caller keeps the bytes)
        if math.isinf(v):
            return ("-" if v < 0 else "") + ("__builtin_inff()" if size == 4 else "__builtin_inf()")
        if v == 0 and b != bytes(size):
            return "-0.0" + ("f" if size == 4 else "")
        if v == int(v) and abs(v) < 1e15:
            lit = "%d.0" % int(v)
        elif size == 8:
            lit = repr(v)  # (the shortest decimal that reads back as the same double)
        else:
            # the shortest decimal that reads back as the same float (gcc rounds a decimal constant correctly)
            lit = next(t for t in ("%.*g" % (p, v) for p in range(1, 10)) if struct.pack("<f", float(t)) == b)
        if not any(c in lit for c in ".en"):
            lit += ".0"
        return lit + ("f" if size == 4 else "")
    u = int.from_bytes(b, "little")
    if fmt == "d":
        s = int.from_bytes(b, "little", signed=True)
        return str(s) if s != -(1 << (8 * size - 1)) else "(%s)0x%x" % (ctype, u)
    return "0x%x" % u


def typed_value(base, is_arr, count, start, b):
    """(declarator, initialiser, bytes covered) for a span declared as a scalar or an array of scalars, or None when
    the bytes stay a byte list: no such type, misaligned, a NaN among floats, or a placeholder type (`undefined`,
    `undefined4`, ...) that only fits the span exactly. A declared array of N covers N elements, an array without a
    size as many whole elements as the span holds, a scalar one element; the caller puts the rest in a tail. A char
    array is text (the caller's string) unless it holds control bytes, as yacc's yytranslate of small numbers does."""
    sc = SCALARS.get(base)
    if sc is None:
        return None
    if is_arr and base == "char":
        body = b[:count or len(b)].rstrip(b"\0")
        if not count or all(c >= 32 or c in (9, 10, 13) for c in body):
            return None
    ctype, esz, fmt = sc
    n = len(b)
    if start % min(esz, 4):
        return None
    placeholder = base.startswith("undefined")
    if is_arr:
        if placeholder:
            return None
        k = count if count else n // esz
    else:
        k = 1
        if placeholder and n != esz:
            return None
    if k == 0 or k * esz > n:
        return None
    vals = [scalar_value(fmt, ctype, esz, b[i * esz:(i + 1) * esz]) for i in range(k)]
    if any(v is None for v in vals):
        return None
    if not is_arr:
        return "%s %%s" % ctype, vals[0], esz
    while vals and vals[-1] in ("0", "0x0", "0.0", "0.0f"):
        vals.pop()  # (C zero-fills the rest of the array)
    per = 8 if esz >= 4 else 16
    rows = [", ".join(vals[i:i + per]) for i in range(0, len(vals), per)]
    init = "{0}" if not rows else "{ %s }" % rows[0] if len(rows) == 1 else "{\n" + ",\n".join("    " + r for r in rows) + "\n}"
    return "%s %%s[%d]" % (ctype, k), init, k * esz


def emit(model, srcdir):
    prog = model.prog
    std = model.std
    lines_head, decls, defs, tail = [], [], [], []
    fn_ids = {}

    def fn_ref(asm):
        if asm not in fn_ids:
            fn_ids[asm] = "f_" + re.sub(r"\W", "_", asm.lstrip("_"))
        return fn_ids[asm]

    def target(r):
        kind, v = r
        if kind == "func":
            return "(void *)%s" % fn_ref(v)
        sp, off = resolve(model, v)
        if sp is None:
            raise SystemExit("datagen: %s: pointer to %#x outside the data" % (prog, v))
        return "(void *)&%s" % sp.name if off == 0 else "(void *)((unsigned char *)&%s + 0x%x)" % (sp.name, off)

    stats = {"spans": 0, "typed": 0, "string": 0, "pointer": 0, "table": 0, "bytes": 0, "struct": 0,
             "bytes_untyped": 0, "zero": 0}
    first_of_sec = {}
    run_key = None
    for sp in model.spans:
        b = section_bytes(model, sp)
        n = len(b)
        if n == 0:
            continue
        stats["spans"] += 1
        sec_key = "t" if sp.island else ""
        if sp.start % 4 == 0 or run_key is None or run_key[0] != sec_key:
            run_key = (sec_key, "%s%08x" % (sec_key, sp.start))
        attr = 'GRIM_DATA("%s")' % run_key[1]
        if sp.sec is not None and sp.sec["name"] not in first_of_sec:
            first_of_sec[sp.sec["name"]] = sp
        relocs = sp.relocs
        base, is_arr, count = sp.decl if sp.decl else ("", False, None)
        base = base.replace("const ", "").strip()
        where = "/* 0x%08x, %d bytes */" % (sp.start, n)
        typed = None if relocs else typed_value(base, is_arr, count, sp.start, b)
        if typed:
            decl, init, head = typed
            decl = decl % sp.name
            stats["typed"] += 1
            if head < n:
                # the span runs past the declared type (an undeclared neighbour, or a table read past its end): the
                # rest goes right behind it, in the same run of the section, so the layout does not move
                rest = b[head:]
                tname = "%s__tail" % sp.name
                decls.append("extern %s;" % decl)
                defs.append("%s %s %s = %s;" % (where, attr, decl, init))
                where = "/* 0x%08x, %d bytes: the rest of %s's span */" % (sp.start + head, n - head, sp.name)
                # (static: no code names it, and the DLLs export every global symbol)
                decl, init = "static unsigned char %s[%d] __attribute__((used))" % (tname, n - head), byte_list(rest)
                if rest.strip(b"\0"):
                    stats["bytes_untyped"] += n - head
        elif not relocs:
            if sp.name.startswith(("s_", "u_")) or (is_arr and base == "char"):
                decl = "char %s[%d]" % (sp.name, n)
                init = c_string(b.rstrip(b"\0"))
                stats["string"] += 1
            else:
                decl = "unsigned char %s[%d]" % (sp.name, n)
                init = byte_list(b)
                if b.strip(b"\0"):
                    stats["bytes"] += 1
                    stats["bytes_untyped"] += n
                else:
                    stats["zero"] += 1
        elif n == 4 and 0 in relocs:
            decl = "void *%s" % sp.name
            init = target(relocs[0])
            stats["pointer"] += 1
        elif sp.start % 4 == 0 and n % 4 == 0 and len(relocs) * 2 >= n // 4:
            vals = []
            for off in range(0, n, 4):
                if off in relocs:
                    vals.append(target(relocs[off]))
                else:
                    u = int.from_bytes(b[off:off + 4], "little")
                    vals.append("0" if u == 0 else "(void *)0x%x" % u)
            decl = "void *%s[%d]" % (sp.name, n // 4)
            init = "{\n" + ",\n".join("    " + ", ".join(vals[i:i + 4]) for i in range(0, len(vals), 4)) + "\n}"
            stats["table"] += 1
        else:
            tname = "grim_span_%08x" % sp.start
            fields, vals, off = [], [], 0
            for ro in sorted(relocs):
                if ro > off:
                    fields.append("unsigned char b%x[%d];" % (off, ro - off))
                    vals.append(byte_list(b[off:ro], "        "))
                fields.append("void *p%x;" % ro)
                vals.append(target(relocs[ro]))
                off = ro + 4
            if off < n:
                fields.append("unsigned char b%x[%d];" % (off, n - off))
                vals.append(byte_list(b[off:], "        "))
            decls.append("typedef struct __attribute__((packed)) { %s } %s;" % (" ".join(fields), tname))
            decl = "%s %s" % (tname, sp.name)
            init = "{\n" + ",\n".join("    " + v.replace("\n", "\n    ") for v in vals) + "\n}"
            stats["struct"] += 1
            stats["bytes_untyped"] += n - 4 * len(relocs)
        if not decl.startswith("static "):
            decls.append("extern %s;" % decl)
        defs.append("%s %s %s = %s;" % (where, attr, decl, init))
        for al in sp.aliases:
            tail.append('__asm__(".globl _%s\\n\\t.set _%s, _%s\\n");' % (al, al, sp.name))
        for al, off in sp.inner:
            tail.append('__asm__(".globl _%s\\n\\t.set _%s, _%s + %d\\n");' % (al, al, sp.name, off))
    for a, n, mem in model.code_stubs:
        sp, off = resolve(model, mem)
        tail.append('__asm__(".text\\n\\t.def _%s; .scl 2; .type 32; .endef\\n\\t.globl _%s\\n_%s:\\tjmp *_%s + 0x%x\\n");'
                    % (n, n, n, sp.name, off))
    for s in model.secs:
        sp = first_of_sec.get(s["name"])
        if sp is not None:
            tail.append('__asm__(".globl _sect_%s\\n\\t.set _sect_%s, _%s\\n");' % (s["key"], s["key"], sp.name))
    head = [
        "/* %s: the original's initialised data, one definition per span." % prog,
        " * GENERATED by tools/datagen.py (from tools/build_src.py) from the Ghidra memory dump; see the docstring there",
        " * and docs/notes/raw_free_build.md. The layout is the original's: GRIM_DATA's section keys keep the order. */",
        "",
        '#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))',
        "",
        "/* An empty anchor that sorts first and starts the data 16-aligned, as the original's sections were. It holds",
        " * no bytes: a section ends padded to its alignment, so the alignment cannot go on the first span itself. */",
        'unsigned char grim_data_anchor_%s[0] __attribute__((section(".data$grim_0"), aligned(16)));' % re.sub(r"\W", "_", prog.lower()),
        "",
        "/* functions the data points at */",
    ]
    for asm, ident in sorted(fn_ids.items(), key=lambda t: t[1]):
        head.append('extern char %s[] __asm__("%s");' % (ident, asm))
    text = "\n".join(head + ["", "/* every span, declared first: the pointers refer forward and back */"] + decls
                     + [""] + defs + [""] + tail) + "\n"
    with open(os.path.join(srcdir, prog, "data.c"), "w", newline="\n") as w:
        w.write(text)
    return stats


# ---------------------------------------------------------------------------------------------- build_src's entry point

def img_targets_of(texts):
    out = set()
    for t in texts:
        out |= {int(a, 16) for a in IMG_ADDR_RE.findall(t)}
    return out


def generate(prog, srcdir):
    """Called by tools/build_src.py once the program's files are written: rewrites IMG_ADDR(0x...) of the generated
    code into the name of the span at that address, declares the new names in globals.h and writes data.c."""
    out = os.path.join(srcdir, prog)
    files = sorted(f for f in os.listdir(out) if f.endswith(".c") and f != "data.c")
    texts = {f: open(os.path.join(out, f), encoding="utf-8", newline="").read() for f in files}
    secs = json.load(open(os.path.join(ROOT, "raw", prog, "sections.json")))
    ranges = [(int(s["start"], 16), int(s["start"], 16) + s["size"]) for s in secs]

    def mapped(a):  # what img_addr_ relocated: a section, its end included
        return any(lo <= a <= hi for lo, hi in ranges)

    targets = {a for a in img_targets_of(texts.values()) if mapped(a)}
    model = build_model(prog, srcdir, targets)
    new_names = {}

    def rep(m):
        a = int(m.group(1), 16)
        if not mapped(a):
            return "0x%s" % m.group(1)
        sp, off = resolve(model, a)
        if sp.name not in model.decls:
            new_names[sp.name] = sp
        if off == 0:
            return "((unsigned)(uintptr_t)&%s)" % sp.name
        return "((unsigned)(uintptr_t)((unsigned char *)&%s + 0x%x))" % (sp.name, off)

    n_img = 0
    for f, t in texts.items():
        t2, k = IMG_ADDR_RE.subn(rep, t)
        n_img += k
        if t2 != t:
            open(os.path.join(out, f), "w", encoding="utf-8", newline="").write(t2)
    if new_names:
        gp = os.path.join(out, "globals.h")
        g = open(gp, encoding="utf-8", newline="").read()
        add = ["", "/* ---- data the code addressed by number (IMG_ADDR): the span at that address (src/%s/data.c) ---- */" % prog]
        for name in sorted(new_names, key=lambda n: new_names[n].start):
            add.append("extern unsigned char %s[]; /* 0x%08x */" % (name, new_names[name].start))
        open(gp, "w", encoding="utf-8", newline="").write(g.rstrip("\n") + "\n" + "\n".join(add) + "\n")
        model.decls.update({n: ("unsigned char", True, None) for n in new_names})
    stats = emit(model, srcdir)
    stats["img_addr"] = n_img
    write_exports(prog, srcdir)
    return stats


def write_exports(prog, srcdir):
    """src/<DLL>/exports.json: the DLL's named exports, the decorated name of those that pop their arguments, and
    whether each is a variable (outside .text): what build/link.py needs to bind the EXE's imports."""
    if not prog.endswith(".DLL"):
        return
    raw = os.path.join(ROOT, "raw", prog)
    text = None
    for line in open(os.path.join(raw, "segments.txt")):
        if line.startswith(".text:"):
            lo, hi = line.split(":", 1)[1].strip().split(" - ")
            text = (int(lo, 16), int(hi, 16))
    std = dll_std()
    out = []
    for line in open(os.path.join(raw, "exports.json"), encoding="utf-8", errors="replace"):
        m = re.match(r"^(\S+) -> ([0-9a-f]{8})", line.strip())
        if not m or m.group(1).startswith("Ordinal_") or m.group(1) == "entry":
            continue
        a = int(m.group(2), 16)
        e = {"name": m.group(1), "address": m.group(2), "variable": not (text[0] <= a <= text[1])}
        if m.group(1) in std:
            e["decorated"] = std[m.group(1)]
        out.append(e)
    with open(os.path.join(srcdir, prog, "exports.json"), "w", newline="\n") as w:
        w.write("[\n" + ",\n".join("  " + json.dumps(e) for e in out) + "\n]\n")


# ---------------------------------------------------------------------------------------------- the report

def report(prog, srcdir):
    model = build_model(prog, srcdir)
    import tempfile
    tmp = tempfile.mkdtemp()
    os.makedirs(os.path.join(tmp, prog))
    stats = emit(model, tmp)
    total = sum(sp.end - sp.start for sp in model.spans if sp.sec is not None or sp.island)
    init = sum(len(s["bytes"]) for s in model.secs)
    big = sorted((sp for sp in model.spans if sp.decl and SCALARS.get(sp.decl[0]) and not sp.decl[1]
                  and sp.end - sp.start > SCALARS[sp.decl[0]][1] and section_bytes(model, sp).strip(b"\0")),
                 key=lambda sp: sp.start - sp.end)
    print("%s: %d spans over %d bytes (%d initialised), %d pointers in the data" %
          (prog, stats["spans"], total, init, len(model.relocs)))
    print("  scalars %(typed)d, strings %(string)d, pointers %(pointer)d, pointer tables %(table)d, "
          "mixed structs %(struct)d, byte arrays %(bytes)d, zero arrays %(zero)d" % stats)
    print("  untyped initialised bytes: %d" % stats["bytes_untyped"])
    print("  scalars longer than their declared type, with data after it: %d" % len(big))
    for sp in big[:8]:
        print("    %s (%s) 0x%08x: %d bytes" % (sp.name, sp.decl[0], sp.start, sp.end - sp.start))


if __name__ == "__main__":
    if len(sys.argv) >= 2 and sys.argv[1] == "report":
        for p in sys.argv[2:] or PROGS:
            report(p, os.path.join(ROOT, "src"))
        n = 0
        for f in os.listdir(os.path.join(ROOT, "build")):
            if f.startswith("overrides") and f.endswith(".c"):
                n += len(re.findall(r"\bIMG_ADDR\(", open(os.path.join(ROOT, "build", f), encoding="utf-8").read()))
        print("IMG_ADDR uses left in build/overrides*.c (by address, through sect_rdata / sect_data): %d" % n)
    else:
        print(__doc__)
