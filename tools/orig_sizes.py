"""names/orig_sizes.json: the size of every global whose original name the remaster's symbols gave (names/orig*_globals*.json,
docs/notes/orig_globals.md), from the remaster's own ELF symbol table.

The remaster's Linux build (`GrimFandango` with iMUSE linked in, `libLua.so`) is i386 like the originals, built from
the same sources: its data symbols carry their sizes (`nm -S`), so a global matched to one of them by name has a known
extent (aLookup 0x100, polyglotServices 0x20, aTanTable 0x4000, as in v1.01). tools/data_reach.py uses them: a global
with an original name is an object of its own (the chain of an untyped object before it ends there), and one whose
size is known reaches that far.

The file records {program: {address: [name, size]}}; a name the ELF holds twice with different sizes (a static of the
same name in two modules) gets no size.

usage: python -I tools/orig_sizes.py [REMASTER_DIR]     (default: C:/GOG Games/Grim Fandango Remastered)
"""
import glob
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF_OF = {"/v101/GRIMFANDANGO.EXE": "GrimFandango", "/v101/IMUSE.DLL": "GrimFandango", "/LUA.DLL": "libLua.so"}
PROG_OF = {"/v101/GRIMFANDANGO.EXE": "GRIMFANDANGO.EXE", "/v101/IMUSE.DLL": "IMUSE.DLL", "/LUA.DLL": "LUA.DLL"}


def elf_sizes(path):
    """{demangled name: size} of the ELF's data symbols; a name with two sizes maps to None."""
    out = {}
    p = subprocess.run(["nm", "-S", "-C", "--defined-only", path], capture_output=True, text=True)
    for line in p.stdout.splitlines():
        m = re.match(r"^[0-9a-f]+ ([0-9a-f]+) [bBdDrRgGsS] (.+)$", line)
        if not m:
            continue
        name, size = m.group(2).strip(), int(m.group(1), 16)
        if name in out and out[name] != size:
            out[name] = None
        else:
            out.setdefault(name, size)
    return out


def main(argv):
    rdir = argv[0] if argv else "C:/GOG Games/Grim Fandango Remastered"
    sizes = {f: elf_sizes(os.path.join(rdir, f)) for f in set(ELF_OF.values())}
    out = {}
    for f in sorted(glob.glob(os.path.join(ROOT, "names", "*globals*.json"))):
        try:
            d = json.load(open(f, encoding="utf-8"))
        except ValueError:
            continue
        for e in d if isinstance(d, list) else d.get("globals", []):
            m = re.match(r"Original name (\S+?)[,;]? \(", e.get("comment", "")) if isinstance(e, dict) else None
            if not m or e.get("program") not in ELF_OF:
                continue
            name = m.group(1)
            # C statics are written `fn.var` in the comments, `fn::var` by nm -C
            size = sizes[ELF_OF[e["program"]]].get(name)
            if size is None:
                size = sizes[ELF_OF[e["program"]]].get(name.replace(".", "::"))
            out.setdefault(PROG_OF[e["program"]], {})[e["addr"].lower()] = [name, size]
    with open(os.path.join(ROOT, "names", "orig_sizes.json"), "w", newline="\n") as w:
        json.dump(out, w, indent=1, sort_keys=True)
    for p, d in sorted(out.items()):
        print("%s: %d globals with an original name, %d with a size" % (p, len(d), sum(1 for v in d.values() if v[1])))


if __name__ == "__main__":
    main(sys.argv[1:])
