"""Carry function renames from names/ batches into the hand-written code, the other batches, tools and docs.

Usage: python -I rename_refs.py [--dry] names/orig_lua.json [more batches...]      (run from tools/)

Each batch entry with "old" and "name" (tools/orig_batch.py writes them) is a rename old -> new in its program; a
names-only global entry ("old" and "global", tools/orig_gbatch.py) is one too, and is also carried into Ghidra's
other-width view `_OLD` and its pieces `OLD_2` (a DAT_1000xxxx name of one DLL can be a global of another: the owners
are read from raw/<prog>/data_items.txt, globals.json and the decompiled code).
All renames are applied in one pass per file (so swaps and chains such as luaH_free -> luaH_hashnodecreate,
ltable__c190 -> luaH_free work), whole words only:
  * build/*.c, build/*.h, build/cleanroom/*.[ch]: only where the #ifdef GRIM_<PROG> guards put the text in the renamed function's program,
    or, outside such guards, when no other program has a function of the old name (the three DLLs share the image
    base, so FUN_1000xxxx names repeat);
  * names/*.json: in place (the files keep their formatting), when no other program has a function of the old name,
    or when every entry of the file that has the name is the renamed function's (same "addr" and program);
  * tools/*.py, build/*.py, docs/*.md, build/cleanroom/*.md (not docs/notes or build/BUILD_NOTES.md, which are history,
    nor build/difftest): when no other program has a function of that name.
With --difftest only build/difftest is processed (*.c, *.h, *.s, *.S, *.sh, *.py, *.ld, *.sed, *.lua, not out/), and
also `orig_<old>` (the original machine code build/mixdiff/slice_orig.py cuts out of a baseline assembly; slice_orig.py
finds a current name under its old label). The harnesses predate the renames, so the batch given is one that maps the
earliest old name of each address to its current name (tools/orig_history.py writes it).
Prints every file it changes and the occurrences it left alone (shared names in unguarded text) for review.
Run it once per batch, on files that still have the old names: it is not idempotent for chains and swaps (a second
run would carry luaH_free on to luaH_hashnodecreate)."""
import glob, json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROGS = ["GRIMFANDANGO.EXE", "LUA.DLL", "IMUSE.DLL", "CHORE.DLL"]
PATH_PROG = {"/v101/GRIMFANDANGO.EXE": "GRIMFANDANGO.EXE", "/LUA.DLL": "LUA.DLL", "/v101/IMUSE.DLL": "IMUSE.DLL",
             "/CHORE.DLL": "CHORE.DLL"}
GUARD_PROG = {"GRIM_EXE": "GRIMFANDANGO.EXE", "GRIM_LUA": "LUA.DLL", "GRIM_IMUSE": "IMUSE.DLL",
              "GRIM_CHORE": "CHORE.DLL"}
ALL = frozenset(PROGS)
_GUARD = r"\bGRIM_(?:EXE|LUA|IMUSE|CHORE)\b"


def guard_set(cond, parent):   # as tools/build_src.py _guard_set
    cond = cond.strip()
    if re.fullmatch(r"0\b.*", cond):
        return frozenset()
    names = re.findall(_GUARD, cond)
    rest = re.sub(r"defined\s*\(\s*GRIM_(?:EXE|LUA|IMUSE|CHORE)\s*\)|" + _GUARD + r"|\|\||[\s()]", "", cond)
    if not names or rest:
        return None
    return frozenset(GUARD_PROG[n] for n in names) & parent


def line_progs(text):
    """programs in force on each line (the #if stack walk of build_src.load_overrides)"""
    out = []
    stack = [(ALL, ALL, frozenset())]
    for line in text.split("\n"):
        m = re.match(r"\s*#\s*(ifdef|ifndef|if|elif|else|endif)\b(.*)", line)
        if m:
            kind, cond = m.group(1), m.group(2)
            cur, parent, taken = stack[-1]
            if kind in ("ifdef", "ifndef", "if"):
                gs = (guard_set("defined(%s)" % cond.strip(), cur) if kind == "ifdef" else
                      guard_set(cond, cur) if kind == "if" else None)
                stack.append((cur if gs is None else gs, cur, frozenset() if gs is None else gs))
            elif len(stack) > 1 and kind == "elif":
                gs = guard_set(cond, parent)
                stack[-1] = (parent if gs is None else gs - taken, parent, taken | (gs or frozenset()))
            elif len(stack) > 1 and kind == "else":
                stack[-1] = (parent - taken if taken else parent, parent, taken)
            elif len(stack) > 1 and kind == "endif":
                stack.pop()
        out.append(stack[-1][0])
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    dry = "--dry" in sys.argv
    owners = {}   # name -> programs that have a function or global of that name (before the renames)
    for p in PROGS:
        for f in json.load(open(os.path.join(ROOT, "raw", p, "functions.json"))):
            owners.setdefault(f["name"], set()).add(p)
    ren = {p: {} for p in PROGS}
    by_addr = {}
    gold = set()   # old names of renamed globals
    for b in args:
        for e in json.load(open(b)):
            new = e.get("name") or (e.get("global") if e.get("names_only") else None)
            if "old" in e and new and e["old"] != new:
                p = PATH_PROG[e.get("program", "/v101/GRIMFANDANGO.EXE")]
                ren[p][e["old"]] = new
                by_addr[(p, e["addr"])] = (e["old"], new)
                owners.setdefault(e["old"], set()).add(p)
                if "global" in e:
                    gold.add(e["old"])
    if gold:
        # a global name (DAT_1000xxxx) can be another DLL's global too: every data symbol and every address-named
        # symbol the decompiled code of a program uses counts
        sym = re.compile(r"\b_?([A-Za-z]\w*?_[0-9a-f]{8})\b")
        for p in PROGS:
            names = set()
            for fn in ("data_items.txt", "globals.json"):
                fp = os.path.join(ROOT, "raw", p, fn)
                if os.path.exists(fp):
                    for line in open(fp, encoding="utf-8", errors="replace"):
                        m = re.match(r"^(\S+) @ ", line)
                        if m:
                            names.add(m.group(1))
            for fp in glob.glob(os.path.join(ROOT, "raw", p, "functions", "*.c")):
                names.update(sym.findall(open(fp, encoding="utf-8", errors="replace").read()))
            for n in names & gold:
                owners.setdefault(n, set()).add(p)
    word = {p: re.compile(r"\b(" + "|".join(map(re.escape, sorted(m, key=len, reverse=True))) + r")\b") if m else None
            for p, m in ren.items()}
    # whole words, the assembler names "_Name" of __asm__("_Name") declarations and of `.def _Name` / `.globl _Name`
    # lines in __asm__ blocks, and the ld --wrap symbols
    # __wrap_Name / __real_Name of build/cleanroom/*.c (their WRAPS lines name the function itself)
    # globals also as Ghidra's other-width view `_DAT_x` and its piece `DAT_x_2`
    falt = "|".join(re.escape(o) for m in ren.values() for o in m if o not in gold)
    galt = "|".join(re.escape(o) for o in sorted(gold, key=len, reverse=True))
    # (build/difftest also: orig_Name, the original machine code that build/mixdiff/slice_orig.py cuts out of a
    # baseline assembly; slice_orig.py maps a current name to the old label of its baseline)
    pre = r"|(?<=orig_)" if "--difftest" in sys.argv else ""
    allold = re.compile("|".join(([r"(?:\b|(?<=\"_)|(?<=[ \t,]_)|(?<=__wrap_)|(?<=__real_)" + pre + r")(" + falt + r")\b"] if falt
                                  else [r"(?!x)x()"]) +
                                 ([r"\b(_?)(" + galt + r")(_\d+)?\b"] if galt else [])))
    skipped = []

    def unique_owner(old):
        """the one program a whole-word occurrence of `old` can mean outside guards (None: ambiguous)"""
        ps = [p for p in PROGS if old in ren[p]]
        if len(ps) == 1 and owners.get(old, set()) <= {ps[0]}:
            return ps[0]
        return None

    def sub_free(text, fname, progs_of_line=None, extra=()):
        lines_progs = line_progs(text) if progs_of_line else None
        starts = [0]
        if lines_progs:
            for line in text.split("\n"):
                starts.append(starts[-1] + len(line) + 1)
        import bisect

        def rep(m):
            if m.group(1) is not None:
                old, pre, suf = m.group(1), "", ""
            else:
                old, pre, suf = m.group(3), m.group(2), m.group(4) or ""
            p = unique_owner(old)
            if p is None and old in extra:
                ps = [q for q in PROGS if old in ren[q]]
                p = ps[0] if len(ps) == 1 else None
            if lines_progs is not None:
                at = lines_progs[bisect.bisect_right(starts, m.start()) - 1]
                cand = [q for q in at if old in ren[q] and q in owners.get(old, set())]
                have = [q for q in at if q in owners.get(old, set())]
                if len(have) == 1 and cand:
                    p = cand[0]
            if p is None:
                line = text.count("\n", 0, m.start()) + 1
                skipped.append(f"{fname}:{line}: {old}")
                return m.group(0)
            return pre + ren[p][old] + suf
        return allold.sub(rep, text)

    changed = []
    if "--difftest" in sys.argv:
        # only the differential-test harnesses of build/difftest (sources, scripts, linker scripts; not the
        # generated out/ trees, logs or binaries); C and assembler text follows the #ifdef GRIM_* guards
        for path in sorted(glob.glob(os.path.join(ROOT, "build", "difftest", "**", "*"), recursive=True)):
            rel = os.path.relpath(path, ROOT)
            ext = os.path.splitext(path)[1]
            if (not os.path.isfile(path) or ext not in (".c", ".h", ".s", ".S", ".sh", ".py", ".ld", ".sed", ".lua")
                    or "/out/" in rel.replace("\\", "/") + "/"):
                continue
            text = open(path, encoding="utf-8", errors="surrogateescape").read()
            new = sub_free(text, rel, progs_of_line=ext in (".c", ".h", ".s", ".S"))
            if new != text:
                changed.append(path)
                if not dry:
                    open(path, "w", encoding="utf-8", errors="surrogateescape", newline="").write(new)
        for c in changed:
            print("changed", os.path.relpath(c, ROOT))
        for s in skipped:
            print("LEFT (shared name, check by hand)", s)
        return
    # hand-written C
    for path in sorted(glob.glob(os.path.join(ROOT, "build", "*.c")) + glob.glob(os.path.join(ROOT, "build", "*.h")) +
                       glob.glob(os.path.join(ROOT, "build", "cleanroom", "*.[ch]"))):
        text = open(path, encoding="utf-8").read()
        new = sub_free(text, os.path.relpath(path, ROOT), progs_of_line=True)
        if new != text:
            changed.append(path)
            if not dry:
                open(path, "w", encoding="utf-8", newline="").write(new)
    # batches
    for path in sorted(glob.glob(os.path.join(ROOT, "names", "*.json"))):
        if os.path.abspath(path) in {os.path.abspath(a) for a in args} or path.endswith("orig_modules.json"):
            continue
        text = open(path, encoding="utf-8").read()
        try:
            data = json.loads(text)
        except ValueError:
            continue
        # names shared with another program (FUN_1000xxxx) are replaced when every entry of this file that has
        # the name is an entry of the renamed function (same addr and program); the text is replaced in place, so
        # the file keeps its formatting
        safe = set()
        bad = set()

        def walk(x):
            if isinstance(x, list):
                for y in x:
                    walk(y)
            elif isinstance(x, dict):
                if "addr" in x:
                    p = PATH_PROG.get(x.get("program", "/v101/GRIMFANDANGO.EXE"))
                    k = by_addr.get((p, x["addr"]))
                    for key in ("name", "old", "global"):
                        v = x.get(key)
                        if isinstance(v, str) and allold.fullmatch(v):
                            (safe if k and k[0] == v else bad).add(v)
                for y in x.values():
                    walk(y)
        walk(data)
        safe -= bad
        new = sub_free(text, os.path.relpath(path, ROOT), extra=safe)
        if new != text:
            changed.append(path)
            if not dry:
                open(path, "w", encoding="utf-8", newline="").write(new)
    # tools and docs
    for path in sorted(glob.glob(os.path.join(ROOT, "tools", "*.py")) + glob.glob(os.path.join(ROOT, "docs", "*.md")) +
                       glob.glob(os.path.join(ROOT, "build", "*.py")) + glob.glob(os.path.join(ROOT, "build", "cleanroom", "*.md"))):
        if os.path.basename(path) in ("rename_refs.py", "orig_match.py", "orig_batch.py", "orig_dump.py", "orig_gbatch.py"):
            continue
        text = open(path, encoding="utf-8").read()
        new = sub_free(text, os.path.relpath(path, ROOT))
        if new != text:
            changed.append(path)
            if not dry:
                open(path, "w", encoding="utf-8", newline="").write(new)
    for c in changed:
        print("changed", os.path.relpath(c, ROOT))
    for s in skipped:
        print("LEFT (shared name, check by hand)", s)


if __name__ == "__main__":
    main()
