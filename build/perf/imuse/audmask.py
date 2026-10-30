import sys, glob
base = [open(f).read().split('\n')[:3000] for f in sorted(glob.glob('aud_lb3k*.txt') + glob.glob('aud_bq*.txt'))]
n = min(len(b) for b in base)
mask = [i for i in range(n) if len(set(b[i] for b in base)) > 1]
ref = base[0]
print("baseline runs", len(base), "blocks", n, "nondeterministic blocks", len(mask), "ranges", end=" ")
r = []; s = None
for i in mask:
    if s is None: s = p = i
    elif i == p + 1: p = i
    else: r.append((s, p)); s = p = i
if s is not None: r.append((s, p))
print(r)
ms = set(mask)
for f in sys.argv[1:]:
    c = open(f).read().split('\n')[:n]
    bad = [i for i in range(min(n, len(c))) if i not in ms and c[i] != ref[i]]
    print(f, "outside-mask diffs:", len(bad), bad[:5])
