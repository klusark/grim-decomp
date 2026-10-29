"""Print how much of ../src compiles (run by `make summary`).

Per program:
  files      modules (src/<prog>/*.c)
  clean      modules that compile with no error at all (.o without .log, or .syn)
  objects    modules with an object file (clean + those rescued by stubify.py)
  functions  decompiled functions (`/* ---- 0x... name ---- */` blocks)
  fn ok      functions without a compiler error (compiled as decompiled)
  stubbed    functions whose body was replaced by a trap to get the object
Errors are attributed to the function block they fall in.

usage: python -I summary.py <srcdir> <objdir> PROG..."""
import os
import re
import sys
from collections import Counter

MARK = re.compile(r"^/\* ---- 0x([0-9a-f]+)\s+(\S+)")


def func_starts(path):
    starts = []
    with open(path, encoding="utf-8", errors="replace") as f:
        for i, line in enumerate(f, 1):
            m = MARK.match(line)
            if m:
                starts.append((i, m.group(2)))
    return starts


def broken_functions(log, cfile, starts):
    broken, outside = set(), 0
    base = os.path.basename(cfile)
    for line in open(log, encoding="utf-8", errors="replace"):
        m = re.match(r"^(.*?):(\d+):\d+: (?:fatal )?error:", line)
        n = re.match(r"^(.*?):(\d+):\d+: note: in expansion of macro", line)
        m = m or n
        if not m:
            continue
        if os.path.basename(m.group(1)) == base:
            owner = None
            for s, name in starts:
                if s > int(m.group(2)):
                    break
                owner = name
            if owner:
                broken.add(owner)
        elif not n:
            outside += 1
    return broken, outside


def main(src, obj, progs):
    tot = Counter()
    rows, notes = [], []
    for prog in progs:
        d = os.path.join(src, prog)
        if not os.path.isdir(d):
            continue
        c = Counter()
        for f in sorted(x for x in os.listdir(d) if x.endswith(".c")):
            base = os.path.join(obj, prog, f[:-2])
            starts = func_starts(os.path.join(d, f))
            c["files"] += 1
            c["functions"] += len(starts)
            has_o, has_syn = os.path.exists(base + ".o"), os.path.exists(base + ".syn")
            log = base + ".log" if os.path.exists(base + ".log") else (
                base + ".syn.log" if os.path.exists(base + ".syn.log") else None)
            if has_o:
                c["objects"] += 1
            if (has_o or has_syn) and not os.path.exists(base + ".log"):
                c["clean"] += 1
                c["fn ok"] += len(starts)
                continue
            if not log:
                continue  # not built yet
            broken, outside = broken_functions(log, f, starts)
            c["fn ok"] += len(starts) - len(broken)
            if has_o:
                c["stubbed"] += len(broken)
            what = "stubbed" if has_o else "FAILED"
            notes.append(f"  {what:7} {prog}/{f}: {len(broken)} function(s) with errors"
                         + (f" ({', '.join(sorted(broken)[:6])}{', ...' if len(broken) > 6 else ''})" if broken else "")
                         + (f"; {outside} error(s) outside functions" if outside else ""))
        rows.append((prog, c))
        tot.update(c)
    cols = ["files", "clean", "objects", "functions", "fn ok", "stubbed"]
    print(f"{'program':18}" + "".join(f"{k:>10}" for k in cols))
    for prog, c in rows + [("TOTAL", tot)]:
        print(f"{prog:18}" + "".join(f"{c[k]:10}" for k in cols))
    for n in notes:
        print(n)


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3:])
