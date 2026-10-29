"""Give every void exported function of the DLLs an undefined4 return value.

The EXE calls the DLL exports through import prototypes that return int, and
Ghidra's void guess for an export (lua_ref, lua_createtable ...) makes the
rebuilt body drop the value it computed in EAX. A spurious return on a truly
void export is harmless, so every void export is retyped.

Usage: python -I fix_void_exports.py [--dry] [prog...]
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SIG_RE = re.compile(r"^void\s+(?:(__cdecl|__stdcall|__fastcall|__thiscall)\s+)?(\w+)\s*\((.*)\)\s*$", re.M)


def main():
    dry = "--dry" in sys.argv
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or ["LUA.DLL", "IMUSE.DLL", "CHORE.DLL"]
    for prog in names:
        path = export_raw.PROGRAMS[prog]
        raw = os.path.join(ROOT, "raw", prog)
        funcs = {f["address"]: f for f in json.load(open(os.path.join(raw, "functions.json")))}
        # exports.json is the bridge's text listing: `name -> address`, one per line
        exported = set()
        for line in open(os.path.join(raw, "exports.json"), encoding="utf-8", errors="replace"):
            m = re.match(r"^(\S+) -> ([0-9a-f]{8})", line.strip())
            if m and not m.group(1).startswith("Ordinal_"):
                exported.add(m.group(2))
        todo = []
        for a in sorted(exported):
            f = funcs.get(a)
            if not f or f.get("isThunk") or f.get("isExternal"):
                continue
            src = os.path.join(raw, "functions", f["address"] + ".c")
            if not os.path.exists(src):
                continue
            m = SIG_RE.search(open(src, encoding="utf-8", errors="replace").read())
            if not m:
                continue
            cc = m.group(1) or "__cdecl"
            todo.append((f["address"], f["name"], f"undefined4 {cc} {m.group(2)}({m.group(3)})"))
        print(f"{prog}: {len(todo)} void exports" + ("" if todo else ""))
        for a, n, proto in todo[:8]:
            print("  ", a, proto)
        if dry:
            continue
        g.ensure_current(path)
        ok = 0
        for a, n, proto in todo:
            r = g.post("set_function_prototype", program=path, function_address=a, prototype=proto)
            if "Success" in str(r):
                ok += 1
            else:
                print("  failed", n, str(r)[:120])
        print(f"{prog}: retyped {ok}")
    if not dry:
        g.ensure_current(g.EXE)
        print(str(g.post("save_all_programs"))[:60])


if __name__ == "__main__":
    main()
