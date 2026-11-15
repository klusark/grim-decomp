"""Turns a hand-written table of parameter names into a types batch for tools/apply_types.py.

  python -I tools/names_batch.py <prog> <names.py> <out.json> [comment]

names.py defines N = {function: [name or None, ...]} with one entry per parameter of the function's prototype in
src/<prog>/functions.h (None: keep it). Only `param_N` parameters are renamed, the types stay; a function whose
prototype has another parameter count, or no calling convention (custom storage: Ghidra would commit a changed
parameter with __cdecl's storage), is skipped and reported."""
import json
import os
import re
import runpy
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from propagate_params import load_protos, PROGRAMS   # noqa: E402


def main():
    prog, names_py, out = sys.argv[1:4]
    comment = sys.argv[4] if len(sys.argv) > 4 else "Parameter names (tools/names_batch.py)."
    table = runpy.run_path(names_py)["N"]
    protos = load_protos(prog)
    params, skipped = [], []
    for fn, names in table.items():
        p = protos.get(fn)
        if not p or not p.get("cc"):
            skipped.append(fn + (" (custom storage)" if p else " (no prototype)"))
            continue
        ps = p["params"]
        if len(names) != len(ps):
            skipped.append("%s (%d names, %d parameters)" % (fn, len(names), len(ps)))
            continue
        used = {n for _, n in ps}
        for i, ((t, n), nn) in enumerate(zip(ps, names)):
            if nn and re.fullmatch(r"param_\d+", n) and nn not in used:
                used.add(nn)
                params.append({"addr": p["addr"], "index": i, "type": t, "name": nn, "_fn": fn, "_names_only": True})
    json.dump({"_comment": comment, "program": PROGRAMS[prog], "params": params},
              open(out, "w", encoding="utf-8", newline="\n"), indent=1)
    print("%d parameters; skipped: %s" % (len(params), ", ".join(skipped) or "none"))


if __name__ == "__main__":
    main()
