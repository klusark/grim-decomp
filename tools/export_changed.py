"""Incremental export: re-decompile only what the last Ghidra edits invalidated.

tools/ghidra_api.py records every write (rename, prototype, comment, label,
create_function ...) in raw/touched.json.  For each touched address this
script re-exports

  * the function itself (if it is one),
  * every function that references it (callers, users of a global, functions
    holding its address) via get_xrefs_to, following one extra hop for
    non-function addresses such as import-table slots and EXTERNAL imports,
  * functions that are new since the last functions.json,

then refreshes functions.json and the auxiliary dumps and clears the journal.
A "*struct*" entry (struct layout changed) falls back to a full export of that
program, as does `--full`.

Usage: python -I export_changed.py [--dry] [prog...]      (run from tools/)
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROGRAMS = export_raw.PROGRAMS
XREF_RE = re.compile(r"From ([0-9a-f]{8}) in (\S+)")


def function_map(prog_name, prog_path):
    funcs = g.get_json("list_functions_enhanced", program=prog_path, limit=20000)
    funcs = funcs.get("functions", funcs)
    return funcs, {f["address"]: f for f in funcs}, {f["name"]: f["address"] for f in funcs}


def referrers(prog_path, addr, by_name, by_addr, depth=2):
    """Functions that reference `addr`; non-function sources are followed `depth` hops."""
    out = set()
    text = g.xrefs_to(prog_path, addr)
    for m in XREF_RE.finditer(text):
        src, holder = m.group(1), m.group(2)
        if holder in by_name:
            out.add(by_name[holder])
        elif src in by_addr:
            out.add(src)
        elif depth > 0:
            out |= referrers(prog_path, src, by_name, by_addr, depth - 1)
    # "From 004e8238 [DATA]" without a holder: a data slot (e.g. an IAT entry)
    for m in re.finditer(r"From ([0-9a-f]{8}) \[", text):
        src = m.group(1)
        if src not in by_addr and depth > 0 and not any(src == x for x in out):
            out |= referrers(prog_path, src, by_name, by_addr, depth - 1)
    return out


def export_changed(prog_name, prog_path, touched, dry=False):
    out = os.path.join(ROOT, "raw", prog_name)
    fdir = os.path.join(out, "functions")
    os.makedirs(fdir, exist_ok=True)
    old_path = os.path.join(out, "functions.json")
    old = {f["address"] for f in json.load(open(old_path))} if os.path.exists(old_path) else set()
    funcs, by_addr, by_name = function_map(prog_name, prog_path)
    if "*struct*" in touched:
        print(f"{prog_name}: struct layout changed -> full export")
        if not dry:
            for f in os.listdir(fdir):
                os.remove(os.path.join(fdir, f))
            export_raw.dump(prog_name, prog_path)
        return
    todo = set()
    for a in touched:
        if a in by_addr:
            todo.add(a)
        todo |= referrers(prog_path, a, by_name, by_addr)
    new = set(by_addr) - old
    for a in new:
        todo.add(a)
        todo |= referrers(prog_path, a, by_name, by_addr)
    gone = old - set(by_addr)
    print(f"{prog_name}: {len(touched)} touched, {len(new)} new functions, {len(gone)} removed -> {len(todo)} to re-export")
    if dry:
        return
    for a in gone:
        p = os.path.join(fdir, a + ".c")
        if os.path.exists(p):
            os.remove(p)
    with open(old_path, "w") as f:
        json.dump(funcs, f, indent=1)
    for i, a in enumerate(sorted(todo)):
        fn = by_addr[a]
        if fn.get("isThunk") or fn.get("isExternal"):
            code = export_raw.thunk_code(prog_path, fn)
        else:
            code = g.get("decompile_function", program=prog_path, address=a)
        with open(os.path.join(fdir, a + ".c"), "w", newline="\n") as f:
            f.write(code.replace("\r\n", "\n"))
        if i and i % 50 == 0:
            print(f"  {prog_name}: {i}/{len(todo)}", flush=True)
    # names/strings/globals may have changed too
    for name, fn in {
        "imports.json": lambda: g.get("list_imports", program=prog_path, limit=5000),
        "exports.json": lambda: g.get("list_exports", program=prog_path, limit=5000),
        "strings.txt": lambda: g.get("list_strings", program=prog_path, limit=100000),
        "globals.json": lambda: g.get("list_globals", program=prog_path, limit=100000),
    }.items():
        try:
            with open(os.path.join(out, name), "w", newline="\n") as f:
                f.write(fn().replace("\r\n", "\n"))
        except Exception as e:
            print("  aux failed", name, e)
    export_raw.dump_structs(prog_name, prog_path)
    print(prog_name + ": done (" + str(len(todo)) + " functions)")


def main(argv):
    dry = "--dry" in argv
    full = "--full" in argv
    names = [a for a in argv if not a.startswith("--")] or list(PROGRAMS)
    touched = json.load(open(g.TOUCHED_PATH)) if os.path.exists(g.TOUCHED_PATH) else {}
    for n in names:
        path = PROGRAMS[n]
        t = set(touched.get(path, []))
        if full:
            t.add("*struct*")
        if not t:
            # still pick up functions created outside the journal
            t = set()
        export_changed(n, path, t, dry)
        if not dry:
            touched.pop(path, None)
    if not dry:
        json.dump(touched, open(g.TOUCHED_PATH, "w"), indent=1)


if __name__ == "__main__":
    main(sys.argv[1:])
