"""Cut single functions out of the generated assembly of the BASELINE build (src/<PROG>/asm_funcs.s as it was before the
functions were converted) and rename them orig_<name>, so that a test program can link the original machine code next to the
hand-written C of the same function and compare them.

usage: python -I slice_orig.py <baseline asm_funcs.s> <out.s> <name> [<name> ...]
Names are given without decoration; _name (cdecl), _name@N (stdcall) and @name@N (fastcall) are found.  Every symbol defined
by the selected functions is renamed orig_<name> (same decoration) everywhere in the slice, so calls between the selected
functions stay inside the slice; symbols the slice only references (other game functions, imports, _sect_data) are left
alone and must be provided by the test."""
import re, sys

src, out = sys.argv[1], sys.argv[2]
names = sys.argv[3:]
text = open(src).read()
# one block per function: from its ".def <sym>;" line to the next ".def" or the first section switch
blocks = {}
for m in re.finditer(r"(?ms)^\t\.def ([_@][\w@]+);.*?(?=^\t\.def |^\t\.section|^\t\.data)", text):
    blocks[m.group(1)] = m.group(0)
sel = []
for n in names:
    cand = [s for s in blocks if s == "_" + n or re.fullmatch(r"[_@]" + re.escape(n) + r"(@\d+)?", s)]
    if len(cand) != 1:
        sys.exit("function %s not found (or ambiguous %s) in %s" % (n, cand, src))
    sel.append(cand[0])
body = "".join(blocks[s] for s in sel)
# jump tables of the selected functions (".Ljt_<addr>_<n>:" in the trailing .rdata block)
addrs = set(re.findall(r"\.L([0-9a-f]+)_[0-9a-f]+:", body))
jt = []
for m in re.finditer(r"(?ms)^(\.Ljt_([0-9a-f]+)_[0-9a-f]+:\n(?:\t\.long [^\n]*\n)+)", text):
    if m.group(2) in addrs:
        jt.append(m.group(1))
for s in sel:
    new = s[0] + "orig_" + s[1:]
    body = re.sub(r"(?<![\w.@])" + re.escape(s) + r"(?![\w@])", new, body) if "@" not in s[1:] else body.replace(s, new)
hdr = "\t.intel_syntax noprefix\n\t.intel_mnemonic\n\t.text\n"
res = hdr + body
if jt:
    res += '\t.section .rdata,"dr"\n' + "".join(jt)
open(out, "w", newline="\n").write(res)
print("sliced %d functions (%d jump tables) -> %s" % (len(sel), len(jt), out))
