"""strip_asm.py <asm_funcs.s> <out.s> <name>...: copy of the generated assembly without the named functions (and their
jump tables), so that a local build links every caller, assembled ones included, to the C of build/overrides_asm_p2.c.
For a smoke test before the integrator regenerates names/asm_funcs.json and src/ (calls inside asm_funcs.s to a
function defined in the same file are resolved by the assembler and would keep using the assembled copy)."""
import re, sys

src, out = sys.argv[1], sys.argv[2]
names = sys.argv[3:]
text = open(src).read()
removed = []
for n in names:
    m = re.search(r"(?ms)^\t\.def (_%s(?:@\d+)?);.*?(?=^\t\.def |^\t\.section|^\t\.data)" % re.escape(n), text)
    if not m:
        sys.exit("function %s not found" % n)
    body = m.group(0)
    addrs = set(re.findall(r"^\.L([0-9a-f]+)_[0-9a-f]+:", body, re.M))
    text = text[:m.start()] + text[m.end():]
    for a in addrs:
        text = re.sub(r"(?m)^\.Ljt_%s_[0-9a-f]+:\n(?:\t\.long [^\n]*\n)+" % a, "", text)
    removed.append(m.group(1))
open(out, "w", newline="\n").write(text)
print("removed", " ".join(removed))
