"""Keep Ghidra's stack layout for the locals it names by frame offset.

Ghidra calls a stack slot at offset -0x30 `local_30` (or `auStack_30`,
`uStack_30`, `pcStack_30` ... when the type came from an access pattern).  The
original code often builds a structure out of adjacent slots and passes
`&local_30` to a Win32 call (WNDCLASSEXA, STARTUPINFOA, DDSURFACEDESC, SEH
frames ...), which only works if the slots really are adjacent and in that
order.  gcc lays out independent locals however it likes, so this rewrite
declares one byte array per function and turns every offset-named local into
a view into it at its Ghidra offset:

    undefined4 local_30;            ->   #define local_30 (*(undefined4 *)(_frame + (0x40 - 0x30)))
    undefined1 auStack_60 [44];     ->   #define auStack_60 (*(undefined1 (*)[44])(_frame + (0x40 - 0x60)))

`&local_30`, `local_30 = x`, `auStack_60[i]` all keep working, and the slots
end up at the same relative addresses as in the shipped binary.  The macros
are #undef'd after the function so names can be reused in the next one.
"""
import re

DECL_RE = re.compile(
    r"^(?P<ind>[ \t]+)(?P<type>[A-Za-z_][\w]*(?:[ \t]+[A-Za-z_]\w*)*)[ \t]+(?P<stars>\**)"
    r"(?P<name>(?:local|[a-zA-Z]+Stack)_(?P<off>[0-9a-f]+))(?P<dims>(?:[ \t]*\[\d+\])*)[ \t]*;[ \t]*$",
    re.M)
NAME_RE = re.compile(r"\b(?:local|[a-zA-Z]+Stack)_[0-9a-f]+\b")


def rewrite(body):
    """body: text from the function's opening '{' to its closing '}'.
    Returns (new_body, trailer) where trailer holds the #undef lines."""
    decls = list(DECL_RE.finditer(body))
    if not decls:
        return body, ""
    # only declarations in the leading block count: a declaration after the first
    # statement would be a parse error anyway, but be safe with Ghidra's `local_x = ...`
    first_stmt = len(body)
    for line in body.split("\n"):
        pass
    frame = 0
    items = []
    for m in decls:
        if m.group("type").split()[0] in ("return", "goto", "else", "case", "sizeof"):
            continue  # `return local_8;` is a statement, not a declaration
        name = m.group("name")
        off = int(m.group("off"), 16)
        if off > 0x40000 or off == 0:
            return body, ""  # not a plausible stack frame: leave the function alone
        dims = re.sub(r"\s+", "", m.group("dims") or "")
        items.append((m, name, off, m.group("type"), m.group("stars"), dims))
    # Only a function whose locals depend on the layout gets the frame: a local whose address is taken (`&local_30`
    # passed as a structure), an array (indexed past its end into its neighbours), a piece of a local
    # (`local_10._4_4_`), a structure held by value or two locals that overlap. Locals used only by name are plain C
    # locals then (gcc may place them anywhere: nothing can see where).
    decl_spans = [(m.start(), m.end()) for m, *_ in items]
    code = "".join(body[a:b] for a, b in zip([0] + [e for _, e in decl_spans], [s for s, _ in decl_spans] + [len(body)]))
    used = [it for it in items if re.search(r"\b%s\b" % it[1], code)]
    if not needs_layout(used, code):
        return body, ""
    if not ("_stkneg" in code or "STACK0X" in code):
        # Only the locals the layout can reach stay in the frame: those that need it themselves, and every local at
        # or above the deepest of them (a structure passed by address runs up from its first slot into the slots
        # Ghidra split it into). The locals below that and the unused ones are plain C locals. (A frame left with
        # one local stays a frame: the code reaches past Ghidra's extent of the local, into the frame's slack.)
        deepest = max(it[2] for it in observed(used, code))
        items = [it for it in used if it[2] <= deepest]
    # (with addresses below the frame mapped onto it, a function keeps all its locals there, the unused ones too:
    # the deepest one decides which of those addresses negative_stack_into_frame maps onto the locals, Res_FOpen's
    # LabFile)
    for it in items:
        frame = max(frame, it[2])
    frame = (frame + 15) & ~15
    frame += 16  # slack for a last slot wider than its offset suggests
    out = body
    names = []
    # replace from the end so the match spans stay valid
    for m, name, off, typ, stars, dims in reversed(items):
        if dims:
            cast = f"{typ} {stars}(*){dims}"
        else:
            cast = f"{typ} {stars}*"
        macro = f"{m.group('ind')}#define {name} (*({cast})(_frame + (0x{frame:x} - 0x{off:x})))"
        out = out[:m.start()] + macro + out[m.end():]
        names.append(name)
    # the frame itself goes right after the opening brace
    brace = out.find("{")
    decl = f"\n  unsigned char _frame[0x{frame:x}] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */"
    out = out[:brace + 1] + decl + out[brace + 1:]
    trailer = "\n" + "\n".join(f"#undef {n}" for n in sorted(set(names))) + "\n"
    return out, trailer


PRIM_SIZE = {"char": 1, "uchar": 1, "byte": 1, "bool": 1, "undefined": 1, "undefined1": 1, "short": 2, "ushort": 2,
             "word": 2, "undefined2": 2, "int": 4, "uint": 4, "long": 4, "ulong": 4, "dword": 4, "float": 4,
             "undefined4": 4, "undefined3": 3, "double": 8, "longlong": 8, "ulonglong": 8, "qword": 8, "undefined8": 8,
             "float10": 10, "undefined5": 5, "undefined6": 6, "undefined7": 7}


def needs_layout(items, code):
    """True when the frame's layout can be observed: see rewrite. items: the used (m, name, off, type, stars, dims)."""
    if "_stkneg" in code or "STACK0X" in code:
        return True     # addresses below or around the frame are mapped onto it (negative_stack_into_frame)
    return bool(observed(items, code))


def observed(items, code):
    """The locals whose place in the frame the code can see: address taken, an array, a piece of one, a structure
    held by value (its extent is not known here), or two that overlap."""
    out, spans = [], []
    for it in items:
        m, name, off, typ, stars, dims = it
        size = 4 if stars else PRIM_SIZE.get(typ.split()[-1])
        if dims or size is None or re.search(r"\b%s\._|PIECE\(\s*%s\b" % (name, name), code) or \
                address_seen(name, typ, stars, code):
            out.append(it)
        else:
            spans.append((off - size, off, it))
    spans.sort(key=lambda t: t[:2])
    for a, b in zip(spans, spans[1:]):
        if a[1] > b[0]:
            out += [a[2], b[2]]
    return out


SCAN_FUNCS = ("sscanf",)


def address_seen(name, typ, stars, code):
    """True when `&name` is used where the layout around the local can matter. Two uses cannot reach the neighbours:
    an int, uint or float whose address goes to sscanf as one argument (written as one %d / %f), and a call that is
    given the address and right after it the local's own size, `(*read)(&local_15c,4)`, `gzread(f,(int)&local_88,4)`
    (a save-game reader or writer moving exactly that local)."""
    refs = list(re.finditer(r"(?<!&)&\s*%s\b" % name, code))
    if not refs:
        return False
    size = 4 if stars else PRIM_SIZE.get(typ)
    for r in refs:
        before, after = code[:r.start()], code[r.end():]
        if not re.search(r"[,(]\s*(?:\([\w\s*]+\)\s*)?$", before):
            return True
        sized = re.match(r"\s*,\s*(0x[0-9a-fA-F]+|\d+)\s*\)", after)
        if size and sized and int(sized.group(1), 0) == size:
            continue
        if stars or typ not in ("int", "uint", "float") or not re.match(r"\s*[,)]", after) or                 not re.search(r",\s*$", before):
            return True
        i, depth = r.start(), 0
        while i > 0:
            i -= 1
            if code[i] == ")":
                depth += 1
            elif code[i] == "(":
                if depth == 0:
                    break
                depth -= 1
            elif code[i] in ";{}":
                return True
        callee = re.search(r"(\w+)\s*$", code[:i])
        if not callee or callee.group(1) not in SCAN_FUNCS:
            return True
    return False
