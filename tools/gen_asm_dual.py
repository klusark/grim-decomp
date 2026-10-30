"""Extracts assembled functions from a generated asm_funcs.s and writes them under the symbol <name>__orig (local labels
renamed), so that a test build can call the original machine code next to its C replacement (differential tests of numeric
functions, see docs/notes/logic.md).
  python -I tools/gen_asm_dual.py <asm_funcs.s of an all-assembly build> <out.s> Name [Name ...]
The output is meant to be pulled into an object with `__asm__(".include \"out.s\"")` (build/overrides_logic_dt.c)."""
import re, sys

src, out, names = sys.argv[1], sys.argv[2], sys.argv[3:]
text = open(src, encoding="utf-8").read().split("\n")
res = ["\t.intel_syntax noprefix", "\t.intel_mnemonic", "\t.text"]
for n in names:
    start = next((i for i, l in enumerate(text) if l == "_%s:  # %s" % (n, n)), None)
    if start is None:
        sys.exit("function %s is not assembled in %s" % (n, src))
    end = start + 1
    while end < len(text) and not text[end].startswith("\t.def ") and not text[end].startswith("\t.section") and text[end] != "\t.data":
        end += 1
    body = text[start:end]
    m = re.match(r"\.L([0-9a-f]+)_", body[1])
    fstart = m.group(1)
    res.append("\t.globl _%s__orig" % n)
    for l in body:
        l = l.replace(".L%s_" % fstart, ".Lo%s_" % fstart).replace(".Ljt_%s_" % fstart, ".Lojt_%s_" % fstart)
        if l.startswith("_%s:" % n):
            l = "_%s__orig:" % n
        res.append(l)
    # jump tables of the function (in the .rdata part of the file): copied with the same renaming
    tables = sorted(set(re.findall(r"\.Ljt_%s_[0-9a-f]+" % fstart, "\n".join(body))))
    for t in tables:
        i = text.index(t + ":")
        j = i + 1
        while j < len(text) and text[j].startswith("\t.long"):
            j += 1
        res.append('\t.section .rdata,"dr"')
        res += [l.replace(".L%s_" % fstart, ".Lo%s_" % fstart).replace(t, t.replace(".Ljt_", ".Lojt_")) for l in text[i:j]]
        res.append("\t.text")
open(out, "w", newline="\n").write("\n".join(res) + "\n")
print("%d functions -> %s" % (len(names), out))
