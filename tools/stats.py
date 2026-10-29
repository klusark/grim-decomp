"""Print a markdown table of naming coverage per program from raw/<prog>/functions.json."""
import json, os, re, collections
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
rows = []
for prog in ["GRIMFANDANGO.EXE", "LUA.DLL", "IMUSE.DLL", "CHORE.DLL"]:
    p = os.path.join(ROOT, "raw", prog, "functions.json")
    if not os.path.exists(p):
        continue
    fs = json.load(open(p))
    total = len(fs)
    unnamed = sum(1 for f in fs if f["name"].startswith("FUN_"))
    auto = sum(1 for f in fs if "__" in f["name"] or f["name"].startswith("rdRaster_"))
    rows.append((prog, total, total - unnamed, auto, unnamed))
print("| Program | Functions | Named | of which auto/module-level | Unnamed (FUN_) |")
print("|---|---|---|---|---|")
for r in rows:
    print("| %s | %d | %d | %d | %d |" % r)
src = os.path.join(ROOT, "src")
if os.path.isdir(src):
    n = 0
    for d, _, files in os.walk(src):
        n += sum(1 for f in files if f.endswith((".c", ".h")))
    print("\nFiles in src/: %d" % n)
