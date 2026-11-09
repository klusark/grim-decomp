"""Print the per-pixel core of span fillers: from the z-buffer compare to the z-buffer store (a reading aid).
usage: python -I core.py <name> ..."""
import os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fdiff import body

for n in sys.argv[1:]:
    b = [re.sub(r"^\s*[0-9a-f]+: ", "", l) for l in body(n)]
    i = next((k for k, l in enumerate(b) if re.match(r"cmp [A-Z]{2},word ptr", l)), None)
    if i is None:
        print("==", n, "(no z compare)")
        continue
    j = i + 1
    while j < len(b) and not re.match(r"mov word ptr \[E[A-Z]+\],[A-Z]{2}$", b[j]):
        j += 1
    core = [l.replace("dword ptr ", "").replace("byte ptr ", "b").replace("word ptr ", "w") for l in b[i:j + 1]]
    print("== %s: %s" % (n, " ; ".join(core)))
