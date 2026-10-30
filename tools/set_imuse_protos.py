"""Apply the prototype fixes of names/imuse_protos.json to IMUSE.DLL in Ghidra (agent N).

  python -I set_imuse_protos.py        then      python -I export_changed.py IMUSE.DLL

names/imuse_protos.json: {address: [prototype, calling convention]}.  Ghidra is the system of record; the file records what was
set so that a fresh Ghidra project can be brought to the same state."""
import json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
path = export_raw.PROGRAMS["IMUSE.DLL"]
g.ensure_current(path)
for addr, spec in json.load(open(os.path.join(ROOT, "names", "imuse_protos.json"))).items():
    if addr.startswith("_"):
        continue
    proto, cc = spec
    r = g.set_prototype(path, addr, proto, cc)
    print(addr, proto, "->", str(r)[:100])
