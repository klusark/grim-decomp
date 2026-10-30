"""print the generated assembly of functions (by name) with the .L<func>_ prefix of the labels stripped.
usage: python -I showasm.py <asm_funcs.s> name [name...]"""
import re, sys
t = open(sys.argv[1]).read()
for n in sys.argv[2:]:
    m = re.search(r"(?ms)^\t\.def _%s;.*?(?=^\t\.def |^\t\.section|^\t\.data)" % re.escape(n), t)
    if not m:
        print("; not found", n); continue
    s = m.group(0)
    s = re.sub(r"\.L[0-9a-f]+_([0-9a-f]+)", r"L\1", s)
    s = re.sub(r"^\t\.(def|globl)[^\n]*\n", "", s, flags=re.M)
    s = re.sub(r"^(L[0-9a-f]+):\t", r"\1:  ", s, flags=re.M)
    print(s)
