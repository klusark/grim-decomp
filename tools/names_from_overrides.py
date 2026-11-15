"""Names the `param_N` parameters of hand-written functions after the hand-written definition (build/overrides*.c).

  python -I tools/names_from_overrides.py <prog> [out.json]

For a function build/overrides*.c defines by hand (the generated twin is under `#if 0`), the prototype in
src/<prog>/functions.h keeps Ghidra's parameters; where the hand-written definition has as many parameters, each
`param_N` takes the hand-written name (types unchanged: the C that is built is the hand-written one). Generic names
(a1, p, x2, param_3, arg0 ...) are not taken, nor a name the prototype already has. Macro-built definitions (the
rasteriser templates: `FN(...)` lines) count only when their parameter list is written out. Writes a types batch for
tools/apply_types.py. Functions without a calling convention in functions.h (custom storage: ST0 results, register
parameters) are left alone: Ghidra commits a changed parameter with __cdecl's storage."""
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from propagate_params import load_protos, PROGRAMS, split_params   # noqa: E402

GUARD = {"GRIMFANDANGO.EXE": "GRIM_EXE", "LUA.DLL": "GRIM_LUA", "IMUSE.DLL": "GRIM_IMUSE", "CHORE.DLL": "GRIM_CHORE"}
GENERIC = re.compile(r"(param|arg|a|p|x|v|n|i|unused|dummy|unk|reg)_?\d*$|.*_$")


def hand_defs():
    defs = {}
    files = sorted(glob.glob(os.path.join(ROOT, "build", "overrides*.c"))) + [os.path.join(ROOT, "build", "fastpaths.c")]
    for path in files:
        if not os.path.exists(path):
            continue
        t = open(path, encoding="utf-8", errors="replace").read()
        t = re.sub(r"/\*.*?\*/", lambda m: " " * len(m.group(0)), t, flags=re.S)
        for m in re.finditer(r"(?m)^[A-Za-z_][\w \*]*?\b(\w+)\s*\(([^;{)]*(?:\([^)]*\)[^;{)]*)*)\)\s*(?:__asm__\([^)]*\)\s*)?\{",
                             t):
            defs.setdefault(m.group(1), []).append((os.path.basename(path), split_params(m.group(2))))
    return defs


def main():
    prog = sys.argv[1]
    out_path = sys.argv[2] if len(sys.argv) > 2 else None
    protos = load_protos(prog)
    hand = hand_defs()
    overridden = set()
    for f in glob.glob(os.path.join(ROOT, "src", prog, "*.c")):
        t = open(f, encoding="utf-8", errors="replace").read()
        for m in re.finditer(r"(?m)^/\* ---- 0x[0-9a-f]+  (\S+) ---- \*/\n/\* replaced by the hand-written", t):
            overridden.add(m.group(1))
    tag = {"LUA.DLL": "lua", "IMUSE.DLL": "imuse", "CHORE.DLL": "chore"}.get(prog)
    params = []
    for fn in sorted(overridden):
        pr = protos.get(fn)
        cands = hand.get(fn, [])
        if len(cands) > 1:
            cands = [c for c in cands if tag and tag in c[0]] or [c for c in cands if not any(
                x in c[0] for x in ("lua", "imuse", "chore"))] or cands
        if not pr or not cands or not pr.get("cc"):
            continue    # (no calling convention: custom storage, which setting a parameter would replace by __cdecl's)
        hp = cands[0][1]
        gp = pr["params"]
        if len(hp) != len(gp) or any(t == "..." for t, _ in gp):
            continue
        used = {n for _, n in gp}
        for idx, ((gt, gn), (ht, hn)) in enumerate(zip(gp, hp)):
            if not re.fullmatch(r"param_\d+", gn) or not hn or GENERIC.fullmatch(hn) or hn in used or hn == "this":
                continue
            used.add(hn)
            params.append({"addr": pr["addr"], "index": idx, "type": gt, "name": hn, "_fn": fn, "_names_only": True})
    print("%s: %d parameters of %d hand-written functions" % (prog, len(params), len({p["_fn"] for p in params})))
    if out_path:
        json.dump({"_comment": "Parameter names of hand-written functions taken from their definitions in "
                               "build/overrides*.c (tools/names_from_overrides.py, 2026-11-15).",
                   "program": PROGRAMS[prog], "params": params}, open(out_path, "w", encoding="utf-8", newline="\n"),
                  indent=1)


if __name__ == "__main__":
    main()
