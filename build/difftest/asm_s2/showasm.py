"""usage: python -I showasm.py [-c] <name> [...]: prints the 1.01 assembly of the functions (src/GRIMFANDANGO.EXE/asm_funcs.s)
with _sect_data+X shown as the 1.01 address.  -c: one line per function, instructions separated by '; ', jump targets
labelled L<addr>:."""
import re, sys
t = open("src/GRIMFANDANGO.EXE/asm_funcs.s").read()
compact = sys.argv[1] == "-c"
names = sys.argv[2:] if compact else sys.argv[1:]
for n in names:
    m = re.search(r"(?ms)^\t\.def [_@]%s(@\d+)?;.*?(?=^\t\.def |^\t\.section|^\t\.data)" % re.escape(n), t)
    if not m:
        print("not found", n)
        continue
    targets = set(re.findall(r"\s(?:j\w+|call)\s+\.L[0-9a-f]+_([0-9a-f]+)", m.group(0)))
    out = []
    for line in m.group(0).splitlines():
        mm = re.match(r"\.L[0-9a-f]+_([0-9a-f]+):\s*(.*)", line)
        if not mm:
            continue
        ins = re.sub(r"_sect_data\+0x([0-9a-f]+)", lambda x: "%x" % (0x4dd000 + int(x.group(1), 16)), mm.group(2))
        ins = re.sub(r"\.L[0-9a-f]+_([0-9a-f]+)", r"L\1", ins)
        ins = ins.replace("dword ptr ", "").replace("word ptr ", "w ").replace("byte ptr ", "b ").replace("*0x1]", "]")
        if compact:
            out.append(("L%s: " % mm.group(1) if mm.group(1) in targets else "") + ins)
        else:
            print(mm.group(1), ins)
    if compact:
        print("== " + n + "\n" + "; ".join(out))
    print()
