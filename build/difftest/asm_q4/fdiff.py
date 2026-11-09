"""Diff two assembled functions of src/GRIMFANDANGO.EXE/asm_funcs.s with the address labels normalised.
usage: python -I fdiff.py <name1> <name2>   (or one name: print it normalised)"""
import difflib, os, re, sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..")


def body(name, src=os.path.join(ROOT, "src", "GRIMFANDANGO.EXE", "asm_funcs.s")):
    out = []; on = False; base = None
    for line in open(src):
        if re.match(r"^_%s:\s+#" % re.escape(name), line):
            on = True
            continue
        if on:
            if line.startswith("\t.def") or line.startswith("\t.section"):
                break
            m = re.match(r"^\.L([0-9a-f]+)_([0-9a-f]+):\t(.*)", line)
            if m:
                if base is None:
                    base = int(m.group(1), 16)
                ins = re.sub(r"\.L[0-9a-f]+_([0-9a-f]+)", lambda k: "L%x" % (int(k.group(1), 16) - base), m.group(3))
                ins = re.sub(r"\.Ljt_[0-9a-f]+_([0-9a-f]+)", lambda k: "JT%x" % (int(k.group(1), 16) - base), ins)
                out.append("%4x: %s" % (int(m.group(2), 16) - base, ins))
            elif line.strip():
                out.append(line.rstrip())
    return out


if __name__ == "__main__":
    a = body(sys.argv[1])
    if len(sys.argv) == 2:
        print("\n".join(a))
        sys.exit()
    b = body(sys.argv[2])
    strip = lambda L: [re.sub(r"^\s*[0-9a-f]+: ", "", x) for x in L]
    for d in difflib.unified_diff(strip(a), strip(b), lineterm="", n=1):
        print(d)
