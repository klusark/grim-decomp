"""Dump every data item Ghidra has defined, with its type and size.

raw/<prog>/data_items.txt, one `NAME @ addr [type] (N bytes)` line per item
(list_data_items). build_src.py uses the element size of an item to type a global
that the code only touches by address: Ghidra prints `(&DAT_x)[i]` with the
item's own element size, so the C declaration has to have the same size.

Usage: python -I export_data_items.py [prog...]
"""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PAGE = 5000


def main():
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or list(export_raw.PROGRAMS)
    for prog in names:
        path = export_raw.PROGRAMS[prog]
        lines, off = [], 0
        while True:
            r = g.get("list_data_items", program=path, offset=off, limit=PAGE)
            batch = [l for l in str(r).splitlines() if " @ " in l]
            lines += batch
            if len(batch) < PAGE:
                break
            off += PAGE
        out = os.path.join(ROOT, "raw", prog, "data_items.txt")
        open(out, "w", encoding="utf-8", newline="\n").write("\n".join(lines) + "\n")
        print(f"{prog}: {len(lines)} data items")


if __name__ == "__main__":
    main()
