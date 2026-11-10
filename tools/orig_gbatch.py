"""Write a names/orig_<prog>_globals*.json batch from a reviewed list of global renames (round orig-globals).

Usage: python -I orig_gbatch.py <PROG> <spec.txt> <names/out.json>      (run from tools/, needs the bridge)

spec.txt, one global per line (blank lines and # comments ignored):
    <addr> <original name> <evidence ...>
The original name is the remaster's (demangled: `LState::refArray`, `grimlib_SetPause::oldmode`, `pLuaHS`).
The new name is `g_` + a Hungarian prefix the bridge accepts for the global's *current* Ghidra type + the original
name (its own prefix kept when the bridge takes it: pLuaHS -> g_pLuaHS on a pointer, g_dwLuaHS on an undefined4;
`::` -> `_`): the type is not changed, so the decompilation only changes in the name. A name can be forced with
`<addr> <original name> =<new name> <evidence>`, the part after the prefix with `<addr> <original name> @<body> <evidence>`
(statics that several modules have: `memory_services @Zfile_memory_services`).

Each entry: {"program", "addr", "old", "global", "oldtype", "names_only": true, "comment"}; "oldtype" is the Ghidra
type at the rename (tools/build_src.py treats the global as its old name while the type is unchanged, so the
generated C is the same), the comment is the existing plate comment followed by
"Original name X (source: evidence); was OLD." apply_names.py applies a names_only entry with rename_or_label and a
plate comment, never a type."""
import json, os, re, sys, urllib.parse, urllib.request
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROG_PATH = {"GRIMFANDANGO.EXE": g.EXE, "LUA.DLL": g.LUA, "IMUSE.DLL": g.IMUSE, "CHORE.DLL": g.CHORE}
SOURCE = {"LUA.DLL": "the remaster's libLua.so", "GRIMFANDANGO.EXE": "the remaster's GrimFandango (Linux)",
          "IMUSE.DLL": "the remaster's GrimFandango (Linux)"}
OWN = ["pfn", "pp", "ap", "sz", "dw", "fl", "lp", "by", "ch", "ul", "ui", "p", "b", "n", "a", "f", "h", "i", "w", "c",
       "l", "u", "e"]


ELF = {"LUA.DLL": "C:/GOG Games/Grim Fandango Remastered/libLua.so",
       "GRIMFANDANGO.EXE": "C:/GOG Games/Grim Fandango Remastered/GrimFandango",
       "IMUSE.DLL": "C:/GOG Games/Grim Fandango Remastered/GrimFandango"}


def elf_data_sizes(path):
    """demangled data symbol name (also its last :: part and the C static `f.x` as f_x) -> sizes, from the .symtab"""
    import struct, subprocess
    d = open(path, "rb").read()
    shoff, = struct.unpack_from("<I", d, 0x20)
    shentsize, shnum = struct.unpack_from("<HH", d, 0x2e)
    sh = [struct.unpack_from("<IIIIIIIIII", d, shoff + i * shentsize) for i in range(shnum)]
    syms = []
    for s in sh:
        if s[1] == 2:
            strtab = sh[s[6]]
            for i in range(s[5] // 16):
                nm, val, size, info, _, _ = struct.unpack_from("<IIIBBH", d, s[4] + i * 16)
                if info & 15 == 1 and val:
                    syms.append((d[strtab[4] + nm:d.index(b"\0", strtab[4] + nm)].decode(), size))
    dem = subprocess.run(["c++filt"], input="\n".join(n for n, _ in syms), capture_output=True,
                         text=True).stdout.split("\n")
    out = {}
    for (n, size), dn in zip(syms, dem):
        dn = re.sub(r"\(.*?\)", "", dn.strip() or n)
        for k in {dn, dn.split("::")[-1], re.sub(r"\.\d+$", "", dn)}:
            out.setdefault(k, set()).add(size)
    return out


def type_prefixes(t, size):
    t = (t or "").strip()
    if "[" in t:   # arrays: the bridge takes no plain `a`
        base = t.split("[")[0].strip()
        return {"char": ["sz"], "float": ["fl"], "byte": ["ab"], "undefined1": ["ab"]}.get(base, ["ab", "dw"])
    if t in ("undefined4", "dword"):
        return ["dw", "n"]
    if t in ("int", "long"):
        return ["n"]
    if t in ("uint", "ulong"):
        return ["dw"]
    if t == "float":
        return ["fl"]
    if t in ("undefined2", "word", "short", "ushort"):
        return ["w", "n"]
    if t in ("undefined1", "byte", "bool", "char", "uchar"):
        return ["b"]
    if t.startswith("char *"):
        return ["sz", "p"]
    if "*" in t or t == "pointer":
        return ["p", "pfn"]
    if not t or t == "undefined":   # no data item: by the remaster's size, a scalar or a table / structure
        return ["dw", "n"] if 0 < size <= 4 else ["a"]
    return ["a", "dw", "n", "p"]


def dry(prog, addr, name, strict=""):
    q = {"program": prog, "dry_run": "true"}
    body = dict(program=prog, address=addr, name=name, dry_run=True)
    if strict:
        q["strict_mode"] = strict
        body["strict_mode"] = strict
    url = f"{g.BASE}/rename_or_label?" + urllib.parse.urlencode(q)
    req = urllib.request.Request(url, data=json.dumps(body).encode(), headers={"Content-Type": "application/json"})
    r = json.loads(urllib.request.urlopen(req, timeout=60).read().decode("utf-8", "replace"))
    return r.get("status") == "success"


def split_own(body):
    """-> (own Hungarian prefix, rest, body without the global marker)"""
    m = re.match(r"^g([A-Z].*)$", body)          # gNumPages: the 'g' is the global marker
    if m:
        body = m.group(1)
    for p in OWN:
        if body.startswith(p) and len(body) > len(p) and body[len(p)].isupper():
            return p, body[len(p):], body
    m = re.match(r"^([pbf])(sput\w+)$", body)    # psputRendHS, bsputRendInitialize: prefix + the sput module name
    if m:
        return m.group(1), cap(m.group(2)), body
    return "", body, body


def cap(s):
    return s[:1].upper() + s[1:]


def new_name(prog, addr, orig, cur_type, size, cur=""):
    body = re.sub(r"\.\d+$", "", orig).replace("::", "_").replace(".", "_")
    body = re.sub(r"\(.*?\)", "", body)
    own, stem, body = split_own(body)
    rest = stem if own else cap(body)    # after another prefix than the original's
    m = re.match(r"^([A-Za-z][A-Za-z0-9]*)_([a-z]+)([A-Z]\w*)$", body)
    if not own and m and m.group(2) in OWN:
        # module_pName (rdroid_pHS, stdConffile_aLine): the prefix goes in front, g_pRdroid_HS
        own, stem = m.group(2), cap(m.group(1)) + "_" + m.group(3)
    cands = []
    if own:
        cands.append(("g_" + own + stem, ""))
    tps = type_prefixes(cur_type, size)
    if own in ("b", "n", "i") and "n" in tps:   # flags and counts: n rather than dw on an undefined4
        tps = ["n"] + [t for t in tps if t != "n"]
    for t in tps:
        cands.append(("g_" + t + rest, ""))
    for c, s in cands:
        if c == cur or dry(prog, addr, c, s):   # (the bridge refuses a dry run of the current name)
            return c, s
    # the bridge takes no prefix for Ghidra's generic `pointer` type: keep the pointer prefix, warn mode
    t = type_prefixes(cur_type, size)[0]
    return ("g_" + own + stem if own else "g_" + t + rest), "warn"


def main():
    prog, spec, out = sys.argv[1:4]
    path = PROG_PATH[prog]
    global ELF_SIZES
    ELF_SIZES = elf_data_sizes(ELF[prog])
    taken = set()
    for f in json.load(open(os.path.join(ROOT, "raw", prog, "functions.json"))):
        taken.add(f["name"])
    entries = []
    for line in open(spec, encoding="utf-8"):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        addr, orig, ev = (line.split(None, 2) + [""])[:3]
        force = body = ""
        if ev.startswith("="):
            force, ev = (ev[1:].split(None, 1) + [""])[:2]
        elif ev.startswith("@"):   # name body other than the original (a module static: @Zfile_memory_services)
            body, ev = (ev[1:].split(None, 1) + [""])[:2]
        a = g.get_json("audit_global", program=path, address=addr)
        old, cur_type, plate = a.get("name"), a.get("type") or "undefined", (a.get("plate_comment") or "").strip()
        if not old:
            print("NO SYMBOL", addr, orig, a)
            continue
        size = int(a.get("length") or 0)
        if cur_type == "undefined":
            sz = ELF_SIZES.get(orig.split("(")[0] if "::" not in orig else re.sub(r"\(.*?\)", "", orig)) or set()
            size = max(sz) if len(sz) == 1 else 0
        if force:
            name, strict = force, ("" if dry(path, addr, force) else "warn")
        else:
            name, strict = new_name(path, addr, body or orig, cur_type, size, old)
        if name in taken and name != old:
            print("NAME TAKEN", addr, name)
            continue
        taken.add(name)
        note = f"Original name {orig} ({SOURCE[prog]}: {ev})" if ev else f"Original name {orig} ({SOURCE[prog]})"
        note += f"; was {old}." if old != name else "."
        plate = re.sub(r"\s*Original name .*?; was \S+\.$", "", plate)
        e = {"program": path, "addr": addr, "old": old, "global": name, "oldtype": cur_type, "names_only": True,
             "comment": (plate + " " + note).strip() if plate else note}
        if strict:
            e["strict_mode"] = strict
        entries.append(e)
        print(f"{addr} {old} -> {name} ({cur_type or 'no data'}{', ' + strict if strict else ''})")
    json.dump(entries, open(out, "w", newline="\n"), indent=1)
    print(f"{out}: {len(entries)} entries")


if __name__ == "__main__":
    main()
