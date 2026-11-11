"""Write one rename batch from the earliest old name of every address the original-names rounds renamed to its current
name (for text older than all the rounds, such as build/difftest: python -I rename_refs.py --difftest <out.json>).

Usage: python -I orig_history.py <out.json>      (run from tools/; current names from raw/<prog>/functions.json and
globals.json)
The rounds in the order they were applied: orig-names, orig-globals, orig-3, orig-4, orig-5, orig-6 (names/orig*.json)."""
import json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ORDER = ["orig_lua", "orig_exe_lua", "orig_exe_engine", "orig_imuse", "orig_lua_globals", "orig_exe_globals",
         "orig_exe_globals2", "orig_imuse_globals", "orig_imuse_globals2", "orig_exe_leftovers",
         "orig_imuse_leftovers", "orig3_exe_funcs", "orig3_exe_globals", "orig3_imuse_funcs", "orig3_imuse_globals",
         "orig3_lua_funcs", "orig4_exe_funcs", "orig4_exe_globals", "orig4_exe_funcs2", "orig4_exe_funcs3",
         "orig4_exe_funcs4", "orig4_exe_funcs5", "orig4_exe_globals2", "orig4_exe_globals3", "orig4_exe_globals4",
         "orig4_imuse_funcs", "orig4_imuse_globals", "orig5_exe_funcs", "orig5_exe_globals", "orig5_imuse_funcs",
         "orig6_exe_funcs", "orig6_exe_globals", "orig6_imuse_funcs", "orig6_imuse_globals", "orig6_lua_funcs"]
PATH_PROG = {"/v101/GRIMFANDANGO.EXE": "GRIMFANDANGO.EXE", "/LUA.DLL": "LUA.DLL", "/v101/IMUSE.DLL": "IMUSE.DLL",
             "/CHORE.DLL": "CHORE.DLL"}


def main():
    first, glob_ = {}, set()
    for b in ORDER:
        for e in json.load(open(os.path.join(ROOT, "names", b + ".json"))):
            k = (e.get("program", "/v101/GRIMFANDANGO.EXE"), e["addr"])
            if "old" in e and k not in first:
                first[k] = e["old"]
                if e.get("names_only"):
                    glob_.add(k)
    cur = {}
    for path, prog in PATH_PROG.items():
        for f in json.load(open(os.path.join(ROOT, "raw", prog, "functions.json"))):
            cur[(path, f["address"])] = f["name"]
        for line in open(os.path.join(ROOT, "raw", prog, "globals.json")):
            m = re.match(r"^(\S+) @ ([0-9a-f]+) ", line)
            if m:
                cur.setdefault((path, m.group(2)), m.group(1))
    out = []
    for k, old in first.items():
        c = cur.get(k)
        if c is None or c == old:
            continue
        e = {"program": k[0], "addr": k[1], "old": old}
        if k in glob_:
            e.update({"global": c, "names_only": True})
        else:
            e["name"] = c
        out.append(e)
    json.dump(out, open(sys.argv[1], "w", newline="\n"), indent=0)
    print(f"{sys.argv[1]}: {len(out)} renames")


if __name__ == "__main__":
    main()
