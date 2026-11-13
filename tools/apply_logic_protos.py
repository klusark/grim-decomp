"""Applies names/logic_protos.json to the live Ghidra project (agent P): function prototypes whose arguments the decompiler
had wrong, so that the callers' decompilation (and tools/export_changed.py) sees the right argument lists.
  python -I tools/apply_logic_protos.py [--dry] [names/<file>.json]   (default names/logic_protos.json)"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
files = [a for a in sys.argv[1:] if not a.startswith("--")]
data = json.load(open(files[0] if files else os.path.join(ROOT, "names", "logic_protos.json")))
for prog, items in data.items():
    if prog.startswith("_"):
        continue
    path = export_raw.PROGRAMS[prog]
    if "--dry" not in sys.argv:
        g.ensure_current(path)
    for addr, spec in items.items():
        if "--dry" in sys.argv:
            print(prog, addr, spec["proto"])
            continue
        g.ensure_current(path)   # (the bridge's write endpoints act on its current program; other sessions may switch it)
        r = g.set_prototype(path, addr, spec["proto"], spec.get("cc", ""))
        now = g.get("get_function_by_address", program=path, address=addr)
        m = re.search(r"^Signature: (.*)$", now, re.M)
        print(addr, "->", m.group(1) if m else now[:80], "|", str(r)[:60])
