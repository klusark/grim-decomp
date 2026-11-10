"""Carry function renames from names/ batches into the hand-written code, the other batches, tools and docs.

Usage: python -I rename_refs.py [--dry] names/orig_lua.json [more batches...]      (run from tools/)

Each batch entry with "old" and "name" (tools/orig_batch.py writes them) is a rename old -> new in its program.
All renames are applied in one pass per file (so swaps and chains such as luaH_free -> luaH_hashnodecreate,
ltable__c190 -> luaH_free work), whole words only:
  * build/*.c, build/*.h: only where the #ifdef GRIM_<PROG> guards put the text in the renamed function's program,
    or, outside such guards, when no other program has a function of the old name (the three DLLs share the image
    base, so FUN_1000xxxx names repeat);
  * names/*.json: in place (the files keep their formatting), when no other program has a function of the old name,
    or when every entry of the file that has the name is the renamed function's (same "addr" and program);
  * tools/*.py, docs/*.md (not docs/notes, which is history): when no other program has a function of that name.
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
    owners = {}   # name -> programs that have a function of that name (before the renames)
    for p in PROGS:
        for f in json.load(open(os.path.join(ROOT, "raw", p, "functions.json"))):
            owners.setdefault(f["name"], set()).add(p)
    ren = {p: {} for p in PROGS}
    by_addr = {}
    for b in args:
        for e in json.load(open(b)):
            if "old" in e and "name" in e and e["old"] != e["name"]:
                p = PATH_PROG[e.get("program", "/v101/GRIMFANDANGO.EXE")]
                ren[p][e["old"]] = e["name"]
                by_addr[(p, e["addr"])] = (e["old"], e["name"])
                owners.setdefault(e["old"], set()).add(p)
    word = {p: re.compile(r"\b(" + "|".join(map(re.escape, sorted(m, key=len, reverse=True))) + r")\b") if m else None
            for p, m in ren.items()}
    allold = re.compile(r"\b(" + "|".join(re.escape(o) for m in ren.values() for o in m) + r")\b")
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
            old = m.group(1)
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
                return old
            return ren[p][old]
        return allold.sub(rep, text)

    changed = []
    # hand-written C
    for path in sorted(glob.glob(os.path.join(ROOT, "build", "*.c")) + glob.glob(os.path.join(ROOT, "build", "*.h"))):
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
                    for key in ("name", "old"):
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
    for path in sorted(glob.glob(os.path.join(ROOT, "tools", "*.py")) + glob.glob(os.path.join(ROOT, "docs", "*.md"))):
        if os.path.basename(path) in ("rename_refs.py", "orig_match.py", "orig_batch.py", "orig_dump.py"):
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
