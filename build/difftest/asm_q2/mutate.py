"""mutate.py: sensitivity check of clip_test.c.  Builds the test with deliberately wrong versions of
build/overrides_asm_q2.c (one textual change each) and reports whether the test finds a difference.
usage: python -I build/difftest/asm_q2/mutate.py [cases per function]"""
import os, subprocess, sys
root = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..")
os.chdir(root)
cases = sys.argv[1] if len(sys.argv) > 1 else "20000"
src = open("build/overrides_asm_q2.c").read()
FUNCS = ["rdClip_Face3_" + n for n in "PosUvLit PosUvLit_2 PosUvFlags PosUvLitColor PosUvLitFlags".split()]
MUT = [
    ("persp: prev bound not rounded", "A = q2_st_f((long double)prev[1] * k);", "A = (long double)prev[1] * k;"),
    ("persp: cur bound rounded", "B = (long double)k * cur[1];", "B = q2_st_f((long double)k * cur[1]);"),
    ("persp: divide by the unrounded den", "? N / denF : N;", "? N / den : N;"),
    ("persp: t branch >=", "if (ady > ada)", "if (ady >= ada)"),
    ("persp: kY unrounded in t", "t = ((long double)kY - prev[a]) / daF;", "t = ((long double)k * Y - prev[a]) / daF;"),
    ("persp: Y rounded in t", "t = (Y - prev[1]) / dyF;", "t = ((long double)q2_st_f(Y) - prev[1]) / dyF;"),
    ("persp: dy not rounded in den", "long double den = (long double)k * dyF - daF;", "long double den = (long double)k * dy - daF;"),
    ("persp: N first product rounded", "N = (long double)cur[1] * prev[a] -", "N = (long double)q2_st_f((long double)cur[1] * prev[a]) -"),
    ("GE: keep test ordered", "keep = !(B > cur[a]);", "keep = B <= cur[a];"),
    ("GE: crossing ignores cur on the plane", "cross = !Q2_EQU(prev[a], A) && !Q2_EQU(B, cur[a]) && (prev[a] < A",
     "cross = !Q2_EQU(prev[a], A) && (prev[a] < A"),
    ("LE: keep test unordered", "keep = B >= cur[a];", "keep = !(B < cur[a]);"),
    ("near: keep unordered", "keep = cur[1] >= c;", "keep = !(cur[1] < c);"),
    ("far: keep ordered", "keep = !(cur[1] > c);", "keep = cur[1] <= c;"),
    ("ortho: t rounded", "t = (c - prev[a]) / ((long double)cur[a] - prev[a]);",
     "t = q2_st_f((c - prev[a]) / ((long double)cur[a] - prev[a]));"),
    ("uv: second coordinate from the first", "ou[1] = q2_st_f(((long double)cu[1] - pu[1]) * t + pu[1]);",
     "ou[1] = q2_st_f(((long double)cu[1] - pu[0]) * t + pu[1]);"),
    ("intensity: rounded t", "out->li[cnt] = q2_st_f(((long double)*ci - *pi) * t + *pi);",
     "out->li[cnt] = q2_st_f(((long double)*ci - *pi) * q2_st_f(t) + *pi);"),
    ("0x40 also after the far plane", "if (p == 4)\n", "if (p >= 4)\n"),
    ("no intensity copy-back", "            q2_copy((uint *)li, (const uint *)UINT_007f46b0, n);", "            ;"),
    ("uv buffers not swapped", "                UINT_007f46a8 = s;", "                UINT_007f46a8 = UINT_007f461c;"),
    ("far plane runs without f[0]", "if (p == 5 && frustum[0] == 0)", "if (p == 5 && 0)"),
]
# Mutations not run.  Equivalent (they cannot change any output):
#  - the unordered part of the "both outside" tests (GE / LE / near): when a compare is unordered, the crossing test
#    (which needs both compares ordered) and the keep test (the complement of the cur part) give the same result
#    whether or not the vertex pair is skipped;
#  - near / far y through FLD/FSTP instead of MOV: a NaN near / far value (the only case where the bits differ) makes
#    every crossing test unordered, so no intersection is ever written;
# Not seen by the test (the C follows the original here; only the test cannot show it):
#  - "den != 0" tested on the float denF instead of the extended den: it differs only for 0 < |den| <= 2^-150 on an
#    edge that crosses the plane; the previous vertex is then at least half a denormal ulp (2^-150) on one side of
#    float(k*prev.y), so the current one must be beyond k*cur.y by the rounding errors of dyF / daF alone.  The
#    denormal mode of clip_test.c (coordinates of a few 2^-149, slopes 0.25 .. 1.5) never produced such an edge.
os.makedirs("build/difftest/asm_q2/out", exist_ok=True)
missed = 0
for name, a, b in MUT:
    if a not in src:
        print("MUTATION NOT APPLICABLE:", name); missed += 1; continue
    p = "build/difftest/asm_q2/out/mut.c"
    open(p, "w", newline="\n").write(src.replace(a, b, 1))
    env = dict(os.environ, OVR=p)
    r = subprocess.run(["bash", "build/difftest/asm_q2/build.sh", "build/difftest/asm_q2/clip_test.c",
                        "build/difftest/asm_q2/out/mut_test.exe"] + FUNCS, env=env, capture_output=True, text=True)
    if r.returncode:
        print("BUILD FAILED:", name, r.stdout[-300:], r.stderr[-300:]); missed += 1; continue
    t = subprocess.run([os.path.abspath("build/difftest/asm_q2/out/mut_test.exe"), cases], capture_output=True, text=True)
    found = t.returncode != 0
    print("%-8s %s" % ("caught" if found else "MISSED", name))
    missed += not found
print("%d of %d mutations missed" % (missed, len(MUT)))
sys.exit(missed != 0)
