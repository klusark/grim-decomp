"""Write a names/orig_<prog>_<topic>.json batch from a reviewed rename list (round orig-names).

Usage: python -I orig_batch.py <PROG> <spec.txt> <names/out.json>      (run from tools/, needs the bridge)

spec.txt, one rename per line (blank lines and # comments ignored):
    <addr> <new name> <evidence ...>
The batch entry gets the old name ("old", for tools/rename_refs.py; apply_names.py ignores it) and a plate comment:
the existing plate comment (without the generated "Unidentified function of ..." text) followed by
"Original name <new> (<source>: <evidence>); was <old>."  An evidence starting with "(not in the remaster" marks a
correction that has no remaster symbol (the name then comes from Lua 3.1 or the code itself).  The C++ names of the remaster are written Class_Method
(Class_Construct / Class_Destruct for constructors and destructors) and the evidence says so.

It also records, in names/orig_modules.json, the module (src/<prog>/<module>.c) each renamed function is in now
when tools/build_src.py would put the new name elsewhere, so a rename does not move code between files."""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROG_PATH = {"GRIMFANDANGO.EXE": g.EXE, "LUA.DLL": g.LUA, "IMUSE.DLL": g.IMUSE, "CHORE.DLL": g.CHORE}
SOURCE = {"LUA.DLL": "the remaster's libLua.so", "GRIMFANDANGO.EXE": "the remaster's GrimFandango (Linux)",
          "IMUSE.DLL": "the remaster's GrimFandango (Linux)"}
GENERATED = re.compile(r"^Unidentified function of [^()]*(\([^)]*\))?\s*$")


def current_modules(prog):
    mods = {}
    for line in open(os.path.join(ROOT, "src", prog, "FUNCTIONS.md"), encoding="utf-8"):
        m = re.match(r"^\| ([0-9a-f]{8}) \| (\S+) \| (\S+)\.c \|", line)
        if m:
            mods[m.group(1)] = m.group(3)
    return mods


def main():
    prog, spec, out = sys.argv[1:4]
    path = PROG_PATH[prog]
    funcs = {f["address"]: f["name"] for f in json.load(open(os.path.join(ROOT, "raw", prog, "functions.json")))}
    mods = current_modules(prog)
    import build_src
    mod_path = os.path.join(ROOT, "names", "orig_modules.json")
    modmap = json.load(open(mod_path)) if os.path.exists(mod_path) else {}
    entries = []
    for line in open(spec, encoding="utf-8"):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        addr, new, ev = (line.split(None, 2) + [""])[:3]
        old = funcs[addr]
        r = g.get_json("get_plate_comment", program=path, address=addr)
        plate = (r.get("comment") or "").strip()
        if GENERATED.match(plate):
            plate = ""
        if ev.startswith("(not in the remaster"):
            # a correction of a guessed name without a remaster symbol: the evidence says where the name comes from
            note = f"Named {new} {ev}"
        else:
            note = f"Original name {new} ({SOURCE[prog]}: {ev})" if ev else f"Original name {new} ({SOURCE[prog]})"
        if old != new:
            note += f"; was {old}."
        else:
            note += "."
        comment = (plate + " " + note).strip() if plate else note
        entries.append({"program": path, "addr": addr, "old": old, "name": new, "comment": comment})
        cur = mods.get(addr)
        build_src.CUR_PROG = prog
        if cur and build_src.module_for(new) != cur:
            modmap.setdefault(prog, {})[new] = cur
    json.dump(entries, open(out, "w"), indent=1)
    json.dump(modmap, open(mod_path, "w"), indent=1, sort_keys=True)
    print(f"{out}: {len(entries)} entries; {len(modmap.get(prog, {}))} module pins for {prog}")


if __name__ == "__main__":
    main()
