"""Sensitivity check of the asm_q1 differential test: builds deliberately wrong versions of build/overrides_asm_q1.c (one
change each: a rounding point, a compare kind, an operand, a copy kind) and runs the test on each; every mutation must
be reported.  usage (from the repository root, MSYS2 bash): python -I build/difftest/asm_q1/mutate.py [cases]"""
import subprocess, sys, os

CASES = sys.argv[1] if len(sys.argv) > 1 else "30000"
SRC = "build/overrides_asm_q1.c"
OUT = "build/difftest/asm_q1/out"
# Dropped as equivalent (no input can tell them apart): "P in when < far" for the far plane (a P exactly on the plane
# is never interpolated and its C decides alone), and Line2D's vertical test on float(x0) instead of the integer (with
# x1 - x0 == 0 the general formula gives x0 too), and FLD/FSTP against a dword copy of a plane bound in an intersection
# (near / far y, the orthographic x / z): only a NaN bound would show it, and a NaN bound never produces an
# intersection (the "on the plane" test is true for unordered compares).  Not dropped as equivalent but not reachable
# by random inputs: testing float(den) instead of the extended den against 0 differs only when 0 < |den| < 2^-149 with
# an edge that crosses the plane, which (worked out in docs/notes/asm_q1.md) needs den == +-2^-150 exactly.
M = [
    ("persp bound a not rounded", "a = q1_st_f((long double)P[1] * k);", "a = (long double)P[1] * k;"),
    ("persp bound b rounded", "b = (long double)C[1] * k;", "b = q1_st_f((long double)C[1] * k);"),
    ("GE: C in as C >= b (NaN)", "inC = Q1_LE_U(b, C[c]);", "inC = !Q1_LT_U(C[c], b);"),
    ("LE: C in as C <= b or unordered (NaN)", "inC = !Q1_LT_U(b, C[c]);", "inC = Q1_LE_U(C[c], b);"),
    ("x plane: u from the unrounded k*s", "u = ((long double)X - P[0]) / DC;", "u = (Z - P[0]) / DC;"),
    ("z plane: u from float(k*s)", "u = (Z - P[2]) / DC;", "u = ((long double)q1_st_f(Z) - P[2]) / DC;"),
    ("divide by the unrounded den", "s = s / DEN;", "s = s / den;"),
    ("|DY| <= |DX| as <", "if (Q1_LE_U(aDY, aDC))\n                            u = ((long double)X",
     "if (Q1_LT_U(aDY, aDC))\n                            u = ((long double)X"),
    ("den from the unrounded C.c - P.c", "den = (long double)k * DY - DC;", "den = (long double)k * DY - ((long double)C[c] - P[c]);"),
    ("far: C in when < far", "inC = Q1_LE_U(C[1], k);", "inC = Q1_LT_U(C[1], k);"),
    ("near: equality not excluded", "eq = Q1_EQ_U(P[1], k) || Q1_EQ_U(C[1], k);\n            outP = Q1_LT_U(P[1], k);",
     "eq = 0;\n            outP = Q1_LT_U(P[1], k);"),
    ("flag 0x40 after any pass", "if (i == 4)\n                g_dwRdClip_faceStatus |= 0x40;", "g_dwRdClip_faceStatus |= 0x40;"),
    ("intensity difference rounded", "iout[cnt - 1] = q1_st_f(((long double)*IC - *IP) * t + *IP);",
     "iout[cnt - 1] = q1_st_f((long double)q1_st_f((long double)*IC - *IP) * t + *IP);"),
    ("kept intensity via FLD/FSTP", "Q1_U32(iout[cnt]) = Q1_U32(*IC);", "iout[cnt] = q1_st_f(*IC);"),
    ("Pos_2 slope order", "static const int side[4] = {12, 10, 11, 8};", "static const int side[4] = {12, 10, 7, 8};"),
    ("Line2D: outcode of the rounded point", "o0 = rdClip_CalcOutcode2(canvas, q1_ftol(nx), q1_ftol(ny));",
     "o0 = rdClip_CalcOutcode2(canvas, q1_ftol(q1_st_f(nx)), q1_ftol(q1_st_f(ny)));"),
    ("Line2D: left/right y kept unrounded", "            nx = (long double)edge;\n            ny = tmp;",
     "            nx = (long double)edge;\n            ny = horz ? (long double)y0 : ((long double)edge - x0) * (((long double)y1 - y0) / ((long double)x1 - x0)) + y0;"),
    ("Line2D: 32-bit conversion", "return (int)(long long)x;", "return (int)x;"),
]

src = open(SRC).read()
missed = 0
for i, (name, old, new) in enumerate(M):
    if src.count(old) < 1:
        print("MUTATION %d (%s): text not found" % (i, name)); missed += 1; continue
    p = "%s/mut%d.c" % (OUT, i)
    open(p, "w", newline="\n").write(src.replace(old, new, 1))
    env = dict(os.environ, OVR=p, LINKPY="1")
    exe = "%s/mut.exe" % OUT
    b = subprocess.run(["bash", "build/difftest/asm_q1/build.sh", exe], env=env, capture_output=True, text=True)
    if b.returncode:
        print("MUTATION %d (%s): build failed\n%s" % (i, name, b.stdout + b.stderr)); missed += 1; continue
    r = subprocess.run([os.path.abspath(exe), CASES], capture_output=True, text=True)
    tot = [l for l in r.stdout.splitlines() if l.startswith("total differences")]
    n = int(tot[0].split()[-1]) if tot else -1
    print("%-45s %s (%s)" % (name, "caught" if n > 0 else "NOT CAUGHT", tot[0] if tot else r.stdout[-200:]))
    if n <= 0:
        missed += 1
print("%d of %d mutations caught" % (len(M) - missed, len(M)))
sys.exit(1 if missed else 0)
