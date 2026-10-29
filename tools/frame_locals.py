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
        frame = max(frame, off)
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
