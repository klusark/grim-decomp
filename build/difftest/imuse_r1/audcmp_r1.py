"""audcmp_r1.py base1 base2 [...] -- c1 c2 [...]: compares PCM traces of build/perf/imuse/audtrace.py (one line per 0x1800-byte
block: index, length, CRC, peak).  The blocks where the baseline runs disagree among themselves are the run-to-run jitter
(an ambient sound or a music switch lands one heartbeat earlier or later) and are masked; reported: for each run of the
converted build, the blocks that differ from the first baseline run outside the mask, and the same count for every pair
of baseline runs (what the jitter alone gives)."""
import sys, itertools

args = sys.argv[1:]
k = args.index("--")
base, conv = args[:k], args[k + 1:]


def load(f):
    return [l.split()[1:] for l in open(f) if l[:1].isdigit()]


B = [load(f) for f in base]
C = [load(f) for f in conv]
n = min(len(x) for x in B + C)
mask = {i for i in range(n) if len({tuple(b[i]) for b in B}) > 1}


def diff(x, y, m=frozenset()):
    return [i for i in range(n) if i not in m and x[i] != y[i]]


print("blocks compared %d, masked (baseline runs disagree) %d" % (n, len(mask)))
for (i, x), (j, y) in itertools.combinations(enumerate(B), 2):
    d = diff(x, y)
    print("baseline %d vs baseline %d: %d blocks differ %s" % (i, j, len(d), d[:6]))
for j, c in enumerate(C):
    d = diff(B[0], c)
    dm = diff(B[0], c, mask)
    print("converted %d vs baseline 0: %d blocks differ, %d outside the mask %s" % (j, len(d), len(dm), dm[:6]))
