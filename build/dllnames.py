"""Exports of the rebuilt DLLs that pop their own arguments (RET imm): their real symbol is the
decorated `_name@N`, so the EXE has to declare, call and take the address of that name.
raw/<prog>/stdcall_funcs.json (find_stdcall.py) gives the byte count, exports.json the names."""
import json, os, re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def load():
    out = {}
    for prog in ("IMUSE.DLL", "LUA.DLL", "CHORE.DLL"):
        raw = os.path.join(ROOT, "raw", prog)
        try:
            sc = json.load(open(os.path.join(raw, "stdcall_funcs.json")))
            skip = set(json.load(open(os.path.join(ROOT, "names", "not_stdcall.json"))).get(prog, []))
            sc = {k: v for k, v in sc.items() if k not in skip}
            for line in open(os.path.join(raw, "exports.json"), encoding="utf-8", errors="replace"):
                m = re.match(r"^(\S+) -> ([0-9a-f]{8})", line.strip())
                if m and m.group(1) != "entry" and not m.group(1).startswith("Ordinal_") and m.group(2) in sc:
                    out[m.group(1)] = "_%s@%d" % (m.group(1), sc[m.group(2)]["bytes"])
        except OSError:
            pass
    return out
