"""Cut single functions out of the generated assembly of the BASELINE build (src/<PROG>/asm_funcs.s as it was before the
functions were converted) and rename them orig_<name>, so that a test program can link the original machine code next to the
hand-written C of the same function and compare them.

usage: python -I slice_orig.py <baseline asm_funcs.s> <out.s> <name> [<name> ...]
Names are given without decoration; _name (cdecl), _name@N (stdcall) and @name@N (fastcall) are found.  Every symbol defined
by the selected functions is renamed orig_<name> (same decoration) everywhere in the slice, so calls between the selected
functions stay inside the slice; symbols the slice only references (other game functions, imports, _sect_data) are left
alone and must be provided by the test.

Renamed functions and globals (the original-names rounds, names/orig*.json): a baseline assembly is older than the
renames, so its labels carry the old names.  A name given in its current form is looked up under its old names too
(the selected function becomes orig_<current name>), and the symbols the slice references under an old name are written
with the current one, so they resolve against the objects and the data image of today's build.  The program is the one
whose old names the baseline assembly has most of."""
import glob, json, os, re, sys

src, out = sys.argv[1], sys.argv[2]
names = sys.argv[3:]
text = open(src).read()
# one block per function: from its ".def <sym>;" line to the next ".def" or the first section switch
blocks = {}
for m in re.finditer(r"(?ms)^\t\.def ([_@][\w@]+);.*?(?=^\t\.def |^\t\.section|^\t\.data)", text):
    blocks[m.group(1)] = m.group(0)

# ---- renames of the original-names rounds: per program, old name -> current name
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
PATH_PROG = {"/v101/GRIMFANDANGO.EXE": "GRIMFANDANGO.EXE", "/LUA.DLL": "LUA.DLL", "/v101/IMUSE.DLL": "IMUSE.DLL",
             "/CHORE.DLL": "CHORE.DLL"}
olds = {}   # prog -> {(addr): [old names]}
cur = {}    # prog -> {addr: current name}
for b in sorted(glob.glob(os.path.join(ROOT, "names", "orig*.json"))):
    try:
        entries = json.load(open(b))
    except ValueError:
        continue
    if not isinstance(entries, list):
        continue
    for e in entries:
        if not isinstance(e, dict) or "old" not in e or "addr" not in e:
            continue
        p = PATH_PROG.get(e.get("program", "/v101/GRIMFANDANGO.EXE"))
        new = e.get("name") or e.get("global")
        if not p or not new:
            continue
        olds.setdefault(p, {}).setdefault(e["addr"], []).append(e["old"])
        cur.setdefault(p, {}).setdefault(e["addr"], new)
for p in list(cur):   # today's names from the export of the Ghidra project, when there is one
    fj = os.path.join(ROOT, "raw", p, "functions.json")
    if os.path.exists(fj):
        for f in json.load(open(fj)):
            if f["address"] in cur[p]:
                cur[p][f["address"]] = f["name"]
labels = {re.sub(r"@\d+$", "", s[1:]) for s in blocks} | set(re.findall(r"\b_?((?:DAT|PTR|UINT|INT|FLOAT|DOUBLE)_[0-9a-f]{8})\b", text))
prog = max(cur, key=lambda p: sum(1 for a, ns in olds[p].items() for n in ns if n in labels), default=None)
old2new, new2old = {}, {}
if prog:
    for a, ns in olds[prog].items():
        for n in ns:
            if n != cur[prog][a]:
                old2new[n] = cur[prog][a]
                new2old.setdefault(cur[prog][a], []).append(n)


def find(n):
    return [s for s in blocks if s == "_" + n or re.fullmatch(r"[_@]" + re.escape(n) + r"(@\d+)?", s)]


sel = []   # (label in the baseline, name of the slice)
for n in names:
    cand = find(n)
    if not cand:
        for o in new2old.get(n, []):
            cand = cand or find(o)
    if len(cand) != 1:
        sys.exit("function %s not found (or ambiguous %s) in %s" % (n, cand, src))
    sel.append((cand[0], n))
body = "".join(blocks[s] for s, _ in sel)
# jump tables of the selected functions (".Ljt_<addr>_<n>:" in the trailing .rdata block)
addrs = set(re.findall(r"\.L([0-9a-f]+)_[0-9a-f]+:", body))
jt = []
for m in re.finditer(r"(?ms)^(\.Ljt_([0-9a-f]+)_[0-9a-f]+:\n(?:\t\.long [^\n]*\n)+)", text):
    if m.group(2) in addrs:
        jt.append(m.group(1))
defined = {s for s, _ in sel}
for s, n in sel:
    deco = re.fullmatch(r"([_@])[\w]+?((?:@\d+)?)", s)
    new = deco.group(1) + "orig_" + n + deco.group(2)
    body = re.sub(r"(?<![\w.@])" + re.escape(s) + r"(?![\w@])", new, body) if "@" not in s[1:] else body.replace(s, new)
if old2new:
    # references under an old name (functions _name / _name@N / @name@N, data _DAT_x): today's name
    rx = re.compile(r"(?<![\w.@])([_@])(" + "|".join(map(re.escape, sorted(old2new, key=len, reverse=True))) + r")(?![\w])")
    body = rx.sub(lambda m: m.group(1) + old2new[m.group(2)], body)
hdr = "\t.intel_syntax noprefix\n\t.intel_mnemonic\n\t.text\n"
res = hdr + body
if jt:
    res += '\t.section .rdata,"dr"\n' + "".join(jt)
open(out, "w", newline="\n").write(res)
print("sliced %d functions (%d jump tables) -> %s" % (len(sel), len(jt), out))
