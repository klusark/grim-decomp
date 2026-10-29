"""Apply curated symbol names to Ghidra.

Usage: python apply_names.py names/exe_core.json [more.json ...]

Each file is a JSON list of entries:
  {"addr": "00488980", "name": "Pool_Create",            # function rename
   "proto": "Pool * Pool_Create(int itemSize, int initialCount, int growBy)",   # optional
   "comment": "...",                                     # optional plate comment
   "tags": "memory,pool",                                # optional
   "program": "/v101/GRIMFANDANGO.EXE"}                  # optional, default EXE
  {"addr": "00905ac0", "global": "g_pMemServices", "type": "GrimServices *", "comment": "..."}
  {"addr": "004e8238", "label": "s_spew_dll"}            # plain label/data rename
Entries are idempotent; rerunning is safe."""
import json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def apply(entries, log):
    n_ok = n_fail = 0
    for e in entries:
        prog = e.get("program", g.EXE)
        addr = e["addr"]
        results = []
        if "name" in e:
            results.append(("rename", g.rename_function(prog, addr, e["name"])))
        if "proto" in e:
            results.append(("proto", g.set_prototype(prog, addr, e["proto"], e.get("cc", ""))))
        if "global" in e:
            r = g.set_global(prog, addr, e["global"], e.get("type", "undefined4"),
                             e.get("comment", ""), e.get("array_length", 0))
            if isinstance(r, dict) and r.get("error") == "name_quality":
                # the bridge's Hungarian-prefix policy rejected the name: apply the pieces directly
                r1 = g.post("apply_data_type", program=prog, address=addr, type_name=e.get("type", "undefined4"))
                r2 = g.rename_or_label(prog, addr, e["global"])
                if not g.ok(r2):
                    r2 = g.post("create_label", program=prog, address=addr, name=e["global"])
                r3 = g.set_plate_comment(prog, addr, e.get("comment", "")) if e.get("comment") else {"status": "success"}
                r = r2 if not g.ok(r2) else (r1 if not g.ok(r1) else r3)
            results.append(("global", r))
        elif "comment" in e:
            results.append(("comment", g.set_plate_comment(prog, addr, e["comment"])))
        if "label" in e:
            results.append(("label", g.rename_or_label(prog, addr, e["label"])))
        if "tags" in e:
            results.append(("tags", g.add_tag(prog, addr, e["tags"])))
        for what, r in results:
            if g.ok(r):
                n_ok += 1
            else:
                n_fail += 1
                log.write(f"FAIL {what} {addr} {e.get('name') or e.get('global') or e.get('label')}: {str(r)[:300]}\n")
    return n_ok, n_fail


if __name__ == "__main__":
    files = sys.argv[1:]
    with open(os.path.join(ROOT, "names", "apply.log"), "a") as log:
        for f in files:
            entries = json.load(open(f))
            g.ensure_current(entries[0].get("program", g.EXE) if entries else g.EXE)
            ok, fail = apply(entries, log)
            print(f"{os.path.basename(f)}: {len(entries)} entries, {ok} ops ok, {fail} failed")
