"""Compare the data of two builds span by span (docs/notes/raw_free_build.md).

For every span of tools/datagen.py's model:
* the bytes of the span in the new build equal those at the same original address in the old build;
* a dword that is a pointer in either build points at the same original address (data) or at the same function;
* the span sits at its original distance from the start of its section (`sect_<name>`): the layout is pinned.

The old build may be one with the data.s blob (`_sect_rdata` / `_sect_data` / `_sect_text`) or one with data.c.
Needs raw/ (the model) and nm; it is a check for the export machine, not part of the build.

usage: python -I build/datacmp.py OLD_DIR NEW_DIR [PROG...]
       (each DIR holds grimfandango.exe, lua.dll, imuse.dll, chore.dll)"""
import bisect
import os
import shutil
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import datagen  # noqa: E402

FILES = {"GRIMFANDANGO.EXE": "grimfandango.exe", "LUA.DLL": "lua.dll", "IMUSE.DLL": "imuse.dll", "CHORE.DLL": "chore.dll"}
NM = shutil.which("nm") or "C:/msys64/mingw32/bin/nm.exe"


class Image:
    def __init__(self, path):
        self.data = open(path, "rb").read()
        d = self.data
        pe = struct.unpack_from("<I", d, 0x3c)[0]
        nsec = struct.unpack_from("<H", d, pe + 6)[0]
        optsz = struct.unpack_from("<H", d, pe + 20)[0]
        self.base = struct.unpack_from("<I", d, pe + 24 + 28)[0]
        self.secs = []
        for i in range(nsec):
            o = pe + 24 + optsz + 40 * i
            vsize, va, rawsz, rawptr = struct.unpack_from("<IIII", d, o + 8)
            self.secs.append((self.base + va, vsize, rawptr, rawsz))
        self.by_name, self.by_addr = {}, {}
        out = subprocess.run([NM, path], capture_output=True, text=True).stdout
        for line in out.splitlines():
            f = line.split()
            if len(f) == 3:
                a = int(f[0], 16)
                self.by_name.setdefault(f[2], a)
                self.by_addr.setdefault(a, set()).add(f[2])

    def read(self, va, n):
        for start, vsize, rawptr, rawsz in self.secs:
            if start <= va < start + max(vsize, rawsz):
                off = va - start
                b = self.data[rawptr + off:rawptr + min(off + n, rawsz)] if off < rawsz else b""
                return b + bytes(n - len(b))
        raise ValueError("%#x not in the image" % va)


def compare(prog, old, new):
    model = datagen.build_model(prog, os.path.join(ROOT, "src"))
    secs = {s["key"]: s for s in model.secs}
    text_start = model.tb["start"] if model.tb else None
    # old: where an original address lives
    old_ranges = []  # (va, size, original start)
    for k, s in secs.items():
        if "_sect_" + k in old.by_name:
            old_ranges.append((old.by_name["_sect_" + k], s["size"] + 0x10000, s["start"]))
    if "_sect_text" in old.by_name and model.tb:
        old_ranges.append((old.by_name["_sect_text"], model.tb["size"], text_start))
    # new: every span by its symbol
    new_spans = sorted((new.by_name["_" + sp.name], sp) for sp in model.spans if "_" + sp.name in new.by_name)
    new_starts = [a for a, _ in new_spans]

    def old_va(sp):
        if "_" + sp.name in old.by_name and not old_ranges:
            return old.by_name["_" + sp.name]
        if sp.island:
            for va, size, ostart in old_ranges:
                if ostart == text_start:
                    return va + sp.start - text_start
            return old.by_name.get("_" + sp.name)
        key = sp.sec["key"] if sp.sec is not None else "rdata"
        s = secs[key]
        for va, size, ostart in old_ranges:
            if ostart == s["start"]:
                return va + sp.start - s["start"]
        return old.by_name.get("_" + sp.name)

    def orig_old(v):
        for va, size, ostart in old_ranges:
            if va <= v < va + size:
                return ("d", ostart + v - va)
        return ("f", frozenset(old.by_addr.get(v, ())) or v)

    def orig_new(v):
        i = bisect.bisect_right(new_starts, v) - 1
        if i >= 0:
            a, sp = new_spans[i]
            if v < a + (sp.end - sp.start) or (v == a + (sp.end - sp.start) and i + 1 == len(new_spans)):
                return ("d", sp.start + v - a)
        return ("f", frozenset(new.by_addr.get(v, ())) or v)

    def same(x, y):
        if x[0] != y[0]:
            return False
        if x[0] == "f" and isinstance(x[1], frozenset) and isinstance(y[1], frozenset):
            return bool(x[1] & y[1])
        return x[1] == y[1]

    bad, missing, moved, ptrs, nbytes = [], [], [], 0, 0
    first = {}
    for a, sp in new_spans:
        if sp.sec is not None and sp.sec["key"] not in first:
            first[sp.sec["key"]] = (a, sp)
    for sp in model.spans:
        n = sp.end - sp.start
        if "_" + sp.name not in new.by_name:
            missing.append(sp.name)
            continue
        nv = new.by_name["_" + sp.name]
        if sp.sec is not None:
            fa, fsp = first[sp.sec["key"]]
            if nv - fa != sp.start - fsp.start:
                moved.append(sp.name)
        ov = old_va(sp)
        if ov is None:
            missing.append("old:" + sp.name)
            continue
        ob, nb = old.read(ov, n), new.read(nv, n)
        nbytes += n
        if ob == nb:
            continue
        off = 0
        while off < n:
            if ob[off] == nb[off]:
                off += 1
                continue
            o4 = off & ~3 if (sp.start + off) % 4 == 0 or True else off
            o4 = off - ((sp.start + off) % 4)
            if o4 >= 0 and o4 + 4 <= n:
                x = orig_old(int.from_bytes(ob[o4:o4 + 4], "little"))
                y = orig_new(int.from_bytes(nb[o4:o4 + 4], "little"))
                if same(x, y):
                    ptrs += 1
                    off = o4 + 4
                    continue
            bad.append((sp.name, sp.start + off, ob[o4:o4 + 4].hex() if o4 >= 0 else "", nb[o4:o4 + 4].hex() if o4 >= 0 else ""))
            off = (o4 + 4) if o4 >= 0 else off + 1
    print("%s: %d spans, %d bytes compared; %d pointers equal by target; %d differences, %d moved, %d missing"
          % (prog, len(model.spans), nbytes, ptrs, len(bad), len(moved), len(missing)))
    for b in bad[:20]:
        print("  DIFF %s at 0x%08x: old %s new %s" % b)
    for m in moved[:10]:
        print("  MOVED", m)
    for m in missing[:10]:
        print("  MISSING", m)
    return not bad and not moved and not missing


def main(argv):
    if len(argv) < 2:
        print(__doc__)
        return 2
    progs = argv[2:] or list(FILES)
    ok = True
    for p in progs:
        ok &= compare(p, Image(os.path.join(argv[0], FILES[p])), Image(os.path.join(argv[1], FILES[p])))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
