"""The original's data that nothing in the rebuilt programs reads: names/data_unused.json, which tools/datagen.py
emits as zero-filled spans of the same size (the content goes, the layout stays pinned; docs/notes/data_unused.md).

A span is unused when all of these hold:
* the linked program does not reach it: no base relocation of the code (generated or hand-written), of the import
  tables or of the overrides' own data points into it, no hex literal of build/*.c (IMG_ADDR, SPAN_DATA, Q3G, ...)
  lies in it, and no reached span holds a pointer to it;
* every original function whose decompiled text names it is one names/lib_replace.json takes out of the build (the
  dead C runtime, the runtime functions msvcrt.dll replaces, the zlib functions the system zlib replaces), and every
  pointer to it sits in a span that is itself unused; or, named by nothing, it follows an unused span (the rest of
  that object);
* the span before it is not reached either, so that no live code indexing a neighbour can run into it.
The last rule is what keeps the tables that live code reads through a label in front of them (iMUSE's state table is
read as `DAT_1001730c[state * 0x15]`; `DAT_10017328`, a column of its first record, is named only by a dead
function). It also keeps some dead data next to live data; the spans themselves do not say where an object ends.

Run it on a build: `python -I tools/data_unused.py [BINDIR]` (default build/obj/<prog>/, needs raw/ and nm). The
list only grows: a span already in it is kept (its bytes are zero in the build, so it is never reached again).

usage: python -I tools/data_unused.py [--check] [BINDIR]     --check: report, write nothing"""
import bisect
import glob
import json
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "build"))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import datacmp  # noqa: E402
import datagen  # noqa: E402

OUT = os.path.join(ROOT, "names", "data_unused.json")
HDR = re.compile(r"^/\* ---- 0x([0-9a-f]{8})  (\S+) ---- \*/", re.M)


def base_relocs(img):
    """(site, value) of every HIGHLOW base relocation of the image."""
    d = img.data
    pe = struct.unpack_from("<I", d, 0x3c)[0]
    opt = pe + 24
    ddir = opt + (96 if struct.unpack_from("<H", d, opt)[0] == 0x10b else 112)
    rva, size = struct.unpack_from("<II", d, ddir + 5 * 8)
    out, pos = [], rva
    while pos < rva + size:
        page, bsz = struct.unpack("<II", img.read(img.base + pos, 8))
        if bsz < 8:
            break
        ent = img.read(img.base + pos + 8, bsz - 8)
        for i in range(0, len(ent), 2):
            e = struct.unpack_from("<H", ent, i)[0]
            if e >> 12 == 3:
                site = img.base + page + (e & 0xfff)
                out.append((site, struct.unpack("<I", img.read(site, 4))[0]))
        pos += bsz
    return out


def literals():
    out = set()
    for p in glob.glob(os.path.join(ROOT, "build", "*.c")):
        for m in re.finditer(r"\b0x([0-9a-fA-F]{6,8})u?\b", open(p, encoding="utf-8", errors="replace").read()):
            out.add(int(m.group(1), 16))
    return out


def reached_spans(model, img, lits):
    spans = sorted((img.by_name["_" + sp.name], sp) for sp in model.spans if "_" + sp.name in img.by_name)
    starts = [a for a, _ in spans]

    def at(v):
        i = bisect.bisect_right(starts, v) - 1
        return spans[i][1] if i >= 0 and v < starts[i] + spans[i][1].end - spans[i][1].start else None

    reached, edges = set(), {}
    for site, val in base_relocs(img):
        t = at(val)
        if t is not None:
            s = at(site)
            if s is None:
                reached.add(t.name)
            else:
                edges.setdefault(s.name, set()).add(t.name)
    for a in lits:
        sp = datagen.span_containing(model, a)
        if sp is not None:
            reached.add(sp.name)
    todo = list(reached)
    while todo:
        for t in edges.get(todo.pop(), ()):
            if t not in reached:
                reached.add(t)
                todo.append(t)
    return reached


def readers(prog, model):
    """span name -> addresses of the functions whose decompiled text names it (or an alias of it)."""
    names = {}
    for sp in model.spans:
        for n in [sp.name] + list(sp.aliases) + [al for al, _ in sp.inner]:
            names[n] = sp.name
    out = {}
    d = os.path.join(ROOT, "src", prog)
    for f in os.listdir(d):
        if not f.endswith(".c") or f == "data.c":
            continue
        t = open(os.path.join(d, f), encoding="utf-8", errors="replace").read()
        hs = list(HDR.finditer(t))
        for i, m in enumerate(hs):
            body = t[m.end():hs[i + 1].start() if i + 1 < len(hs) else len(t)]
            for w in set(re.findall(r"\b[A-Za-z_]\w*\b", body)):
                if w in names:
                    out.setdefault(names[w], set()).add(m.group(1))
    return out


def unused(prog, bindir, lits, before):
    model = datagen.build_model(prog, os.path.join(ROOT, "src"))
    img = datacmp.Image(os.path.join(bindir, datacmp.FILES[prog]))
    reached = reached_spans(model, img, lits)
    cats = json.load(open(os.path.join(ROOT, "names", "lib_replace.json"))).get(prog, {})
    out_fns = {a: c for c, lst in cats.items() for a in lst}
    reads = readers(prog, model)
    pointed = {}  # span -> spans holding a pointer to it
    for sp in model.spans:
        for r in sp.relocs.values():
            if r[0] == "data":
                t, _ = datagen.resolve(model, r[1])
                if t is not None:
                    pointed.setdefault(t.name, set()).add(sp.name)
    order = [sp for sp in model.spans if not sp.island]
    found = {n: r for n, r in before.items() if n in {sp.name for sp in order} and n not in reached}
    for n in sorted(set(before) & reached):
        print("  %s: %s is in the list but reached now: taken out" % (prog, n))
    while True:
        new, prev = dict(found), None
        for sp in order:
            if sp.name in new or sp.sec is None or sp.name in reached:
                prev = sp
                continue
            r = reads.get(sp.name, set())
            ptr_ok = pointed.get(sp.name, set()) <= set(new)
            prev_ok = prev is None or prev.name not in reached
            if r and r <= set(out_fns) and ptr_ok and prev_ok:
                new[sp.name] = "+".join(sorted({out_fns[a] for a in r}))
            elif not r and pointed.get(sp.name) and ptr_ok and prev_ok:
                new[sp.name] = "pointed at by unused data"
            elif not r and not pointed.get(sp.name) and prev is not None and prev.name in new:
                new[sp.name] = "rest of " + prev.name
            prev = sp
        if new == found:
            break
        found = new
    rows = []
    for sp in order:
        if sp.name in found:
            rows.append({"addr": "%08x" % sp.start, "size": sp.end - sp.start, "name": sp.name, "reader": found[sp.name]})
    return rows, model


def main(argv):
    check = "--check" in argv
    args = [a for a in argv if not a.startswith("--")]
    lits = literals()
    old = json.load(open(OUT)) if os.path.exists(OUT) else {}
    res = {"_comment": "Written by tools/data_unused.py: spans of the original's data that nothing in the rebuilt "
                       "programs reads; tools/datagen.py emits them zero-filled (docs/notes/data_unused.md)."}
    for prog in datagen.PROGS:
        bindir = args[0] if args else os.path.join(ROOT, "build", "obj", prog)
        rows, model = unused(prog, bindir, lits, {r["name"]: r["reader"] for r in old.get(prog, [])})
        withdata = [r for r in rows if any(datagen.section_bytes(model, next(sp for sp in model.spans if sp.name == r["name"])))]
        print("%s: %d unused spans, %d bytes (%d of them with data, %d bytes)" % (
            prog, len(rows), sum(r["size"] for r in rows), len(withdata), sum(r["size"] for r in withdata)))
        res[prog] = rows
    if not check:
        with open(OUT, "w", newline="\n") as w:
            w.write("{\n \"_comment\": %s" % json.dumps(res["_comment"]))
            for prog in datagen.PROGS:
                w.write(",\n %s: [\n" % json.dumps(prog))
                w.write(",\n".join("  " + json.dumps(r) for r in res[prog]))
                w.write("\n ]")
            w.write("\n}\n")


if __name__ == "__main__":
    main(sys.argv[1:])
