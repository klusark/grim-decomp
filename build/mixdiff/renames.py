"""renames.py <prog> <test.c> <out.c> [baseline.s]: the test with the old names of renamed functions written as the
current ones.  The old names come from the plate comments of src/<prog>/*.c ("... was <old name>.", the function of each
section from its `/* ---- 0x<addr>  <name> ---- */` marker) and from the labels of the baseline assembly (the address of
`_<old name>:` is the address of its first instruction label `.L<addr>_<addr>`).  A name that is still the current name
of some function is left alone."""
import glob
import re
import sys

prog, src, out = sys.argv[1:4]
base = sys.argv[4] if len(sys.argv) > 4 else None
current, old, by_addr = set(), {}, {}
for f in glob.glob('src/%s/*.c' % prog):
    t = open(f, encoding='utf-8', errors='replace').read()
    for m in re.finditer(r'(?ms)^/\* ---- 0x([0-9a-f]+)  (\S+) ---- \*/\n(.*?)(?=^/\* ---- 0x|\Z)', t):
        addr, name, body = int(m.group(1), 16), m.group(2), m.group(3)
        current.add(name)
        by_addr[addr] = name
        head = body.split('\n{', 1)[0]
        # "...; was Old_Name." at the end of a plate comment (the name may wrap onto the next line)
        for o in re.findall(r'\bwas\s+([A-Za-z_]\w*(?:_|[A-Z])\w*)\.(?:\s|\*/)', head):
            old.setdefault(o, name)
if base:
    text = open(base, errors='replace').read()
    for m in re.finditer(r'(?m)^[_@]([A-Za-z_]\w*?)(?:@\d+)?:[^\n]*\n\.L([0-9a-f]+)_', text):
        n = by_addr.get(int(m.group(2), 16))
        if n:
            old.setdefault(m.group(1), n)
mp = {o: n for o, n in old.items() if o not in current and o != n}
t = open(src, encoding='utf-8', errors='replace').read()
def has(name):
    return re.search(r'\b%s\b' % re.escape(name), t)


# (a test that already names the current function too, e.g. a recorder defined under both names, keeps the old one)
used, targets = [], set()
for o in sorted(mp, key=lambda o: (o.startswith('FUN_'), o)):     # (two old names of one function: rename one)
    if has(o) and not has(mp[o]) and mp[o] not in targets:
        used.append(o)
        targets.add(mp[o])
for o in used:
    t = re.sub(r'\b%s\b' % re.escape(o), mp[o], t)
open(out, 'w', encoding='utf-8', newline='\n').write(t)
if used:
    print('renamed in the test:', ', '.join('%s -> %s' % (o, mp[o]) for o in used))
