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
  {"addr": "<addr>", "global": "g_dwLuaHS", "names_only": true, "old": "DAT_<addr>", "oldtype": "undefined4",
   "comment": "..."}                                     # name + plate comment, type unchanged (orig_gbatch.py)
Entries are idempotent; rerunning is safe."""
import json, os, re, sys
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
        if "global" in e and e.get("names_only"):
            # name and plate comment only, the Ghidra type stays (tools/orig_gbatch.py)
            body = dict(program=prog, address=addr, name=e["global"])
            if e.get("strict_mode"):
                body["strict_mode"] = e["strict_mode"]
            cur = g.get_json("audit_global", program=prog, address=addr)
            if not cur.get("type") and cur.get("name") not in (None, e["global"])                     and not re.match(r"(?:DAT|PTR|UINT|INT|UNK|LAB|BYTE|WORD|DWORD|FLOAT|DOUBLE)_", cur["name"]):
                # a user label without data: rename it (rename_or_label would add a second label beside it)
                r = g.post("rename_label", program=prog, address=addr, old_name=cur["name"], new_name=e["global"])
            else:
                r = g.post("rename_or_label", **body)
            if not g.ok(r) and "already exists" in str(r):
                r = {"status": "success"}
            if g.ok(r) and e.get("comment"):
                r = g.post("set_comment", program=prog, address=addr, comment=e["comment"], comment_type="plate")
            results.append(("global", r))
        elif "global" in e:
            r = g.set_global(prog, addr, e["global"], e.get("type", "undefined4"),
                             e.get("comment", ""), e.get("array_length", 0))
            if isinstance(r, dict) and r.get("error") in ("name_quality", "prefix_type_mismatch"):
                # the bridge's Hungarian-prefix policy rejected the name: apply the pieces directly
                t = e.get("type", "undefined4")
                if e.get("array_length"):
                    t = f"{t}[{e['array_length']}]"
                r1 = g.post("apply_data_type", program=prog, address=addr, type_name=t)
                r2 = g.rename_or_label(prog, addr, e["global"])
                if not g.ok(r2):
                    r2 = g.post("create_label", program=prog, address=addr, name=e["global"])
                    if "already exists" in str(r2):   # re-applying a batch: the name is already there
                        r2 = {"status": "success"}
                # (set_plate_comment only takes function addresses)
                r3 = (g.post("set_comment", program=prog, address=addr, comment=e["comment"], comment_type="plate")
                      if e.get("comment") else {"status": "success"})
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
