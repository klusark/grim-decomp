"""Create Ghidra functions at call targets the linker had to stub.

build/obj/<prog>/stubs.txt lists symbols nothing defines. `func_0x<addr>` are
calls to code Ghidra never made a function of; creating the function lets the
next export decompile it. Dumps that still say `func_0x<addr>` are
re-decompiled so the call names the new function.

Usage: python -I close_stubs.py [prog...]    -> prints how many were created
(0 = fixed point reached)
"""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ghidra_api as g
import export_raw

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or list(export_raw.PROGRAMS)
    total = 0
    for prog in names:
        stubs_path = os.path.join(ROOT, "build", "obj", prog, "stubs.txt")
        if not os.path.exists(stubs_path):
            continue
        addrs = {m.group(1) for line in open(stubs_path) for m in [re.fullmatch(r"func_0x([0-9a-f]{8})", line.strip())] if m}
        # code addresses used as values (callbacks, vtables) that Ghidra left as data: UNK_<addr> in .text
        text = None
        for line in open(os.path.join(ROOT, "raw", prog, "segments.txt")):
            if line.startswith(".text:"):
                lo, hi = line.split(":", 1)[1].strip().split(" - ")
                text = (int(lo, 16), int(hi, 16))
        gh = os.path.join(ROOT, "src", prog, "globals.h")
        if text and os.path.exists(gh):
            for m in re.finditer(r"\bUNK_([0-9a-f]{8})\b", open(gh, encoding="utf-8", errors="replace").read()):
                if text[0] <= int(m.group(1), 16) <= text[1]:
                    addrs.add(m.group(1))
        addrs = sorted(addrs)
        if not addrs:
            continue
        path = export_raw.PROGRAMS[prog]
        g.ensure_current(path)
        made = []
        for a in addrs:
            r = g.post("create_function", program=path, address=a)
            if r.get("success"):
                made.append(a)
            else:
                print(f"  {prog} {a}: {str(r)[:90]}")
        if not made:
            continue
        total += len(made)
        d = os.path.join(ROOT, "raw", prog, "functions")
        pat = re.compile(r"(?:func_0x|UNK_)(%s)\b" % "|".join(made))
        stale = [f[:-2] for f in os.listdir(d) if f.endswith(".c") and pat.search(open(os.path.join(d, f), encoding="utf-8", errors="replace").read())]
        for a in stale:
            code = g.get("decompile_function", program=path, address=a)
            open(os.path.join(d, a + ".c"), "w", newline="\n").write(code.replace("\r\n", "\n"))
        print(f"{prog}: created {len(made)} functions, refreshed {len(stale)} dumps")
    if total:
        g.ensure_current(g.EXE)
        g.post("save_all_programs")
    print("CREATED", total)


if __name__ == "__main__":
    main()
