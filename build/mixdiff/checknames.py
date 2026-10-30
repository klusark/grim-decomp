"""check that every name of a names/*.json file is present in the exported raw/ tree (functions.json, globals.json)
usage: python -I checknames.py names/mixer_names.json [...]"""
import json, re, sys, os
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
raw = os.path.join(ROOT, "raw", "GRIMFANDANGO.EXE")
funcs = {f["address"]: f["name"] for f in json.load(open(os.path.join(raw, "functions.json")))}
glob = {}
for line in open(os.path.join(raw, "globals.json"), encoding="utf-8", errors="replace"):
    m = re.match(r"^(\S+) @ ([0-9a-f]{8}) ", line)
    if m:
        glob[m.group(2)] = m.group(1)
bad = 0
for p in sys.argv[1:]:
    for e in json.load(open(p)):
        a = e["addr"]
        for key, tab in (("name", funcs), ("global", glob), ("label", glob)):
            if key in e and tab.get(a) != e[key]:
                bad += 1
                print("MISSING %s %s: want %s have %s" % (key, a, e[key], tab.get(a)))
print("checked, %d problems" % bad)
