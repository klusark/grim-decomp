"""mutate.py: sensitivity check of math_test.c.  Builds the test with deliberately wrong versions of
build/overrides_asm_p2.c (one textual change each) and reports whether the test finds a difference.
usage: python -I build/difftest/asm_p2/mutate.py [cases]"""
import os, subprocess, sys
root = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..")
os.chdir(root)
cases = sys.argv[1] if len(sys.argv) > 1 else "20000"
src = open("build/overrides_asm_p2.c").read()
FUNCS = "rdClip_SphereInFrustrum rdClip_FaceToPlane rdMatrix_Build34 rdMatrix_BuildRotate34 rdMatrix_BuildFromVectorAngle34 " \
        "rdLight_CalcVertexIntensities rdCanvas_DrawPoint _ftol".split()
MUT = [
    ("Frustum: first far test <= instead of < unordered", "if (!LE_U(loF, ff[2]))", "if (!LT_U(loF, ff[2]))"),
    ("Frustum: near bound rounded", "if (LT_U(hi, ff[1]))", "if (LT_U(hiF, ff[1]))"),
    ("Frustum: extended A rounded", "A = (long double)ff[7] * loF;", "A = st_f((long double)ff[7] * loF);"),
    ("Frustum: inside result inverted", "return inside == 0;", "return inside != 0;"),
    ("Clip: t sign", "long double t = p2_neg(", "long double t = ("),
    ("Clip: d rounded", "            if (!LT_U(dprev, 0.0f) && !LT_U(d, 0.0f)) {", "            d = st_f(d);\n            if (!LT_U(dprev, 0.0f) && !LT_U(d, 0.0f)) {"),
    ("Clip: third uv dword not copied", "                    U32(ouv[2]) = U32(uvp[2]);\n                }\n                if (in != 0)\n                    *oi = st_f(icur);\n                cnt++;", "                }\n                if (in != 0)\n                    *oi = st_f(icur);\n                cnt++;"),
    ("Clip: intensity copied as bits", "                if (in != 0)\n                    *oi = st_f(icur);\n                cnt++; ov += 3;", "                if (in != 0)\n                    U32(*oi) = U32(*curi);\n                cnt++; ov += 3;"),
    ("Angles: S3 unrounded", "m[1] = st_f(P2 * a1 + S3);", "m[1] = st_f(P2 * a1 + P3);"),
    ("Angles: m7 operands", "m[7] = st_f(p2_neg(a1) * P4 + P1);", "m[7] = st_f(p2_neg(a1) * P1 + P4);"),
    # (< instead of <= against 1e-5f cannot be seen: |1 - z| of a float z near 1 is never exactly 1e-5f)
    ("Axis: +z tolerance 1e-4", "    if (LE_U(Dabs, 1e-05f))\n        D = 0.0f;\n    if (!(D < 0.0L", "    if (LE_U(Dabs, 1e-04f))\n        D = 0.0f;\n    if (!(D < 0.0L"),
    ("Axis: yx*omc rounded", "yxoE = (long double)yx * omc;", "yxoE = st_f((long double)yx * omc);"),
    ("Axis: m8 association", "m[8] = st_f(((long double)yc + xc) + z);", "m[8] = st_f((long double)yc + ((long double)xc + z));"),
    ("Light: squared distance from floats", "qx = dx * L[0];", "qx = (long double)L[0] * L[0];"),
    # (< instead of <= in the clamp is equivalent: both store 1.0f at 1.0f)
    ("Light: no clamp", "if (!LE_U(*o, 1.0f))", "if (0)"),
    ("Light: spot cone uses cf", "if (LE_U(cs, lf[11]))", "if (LE_U(cf, lf[11]))"),
    ("Light: return rounded", "return (long double)sum / (long double)(long long)(unsigned long long)nverts;", "return st_f((long double)sum / (long double)(long long)(unsigned long long)nverts);"),
    ("Point: loop test on rounded angle", "    } while (LE_U(t, 360.0f));", "    } while (LE_U(ang, 360.0f));"),
    ("Point: radius rounding", "R = p2_ftol((long double)r - -0.5L);", "R = p2_ftol((long double)r);"),
]
os.makedirs("build/difftest/asm_p2/out", exist_ok=True)
missed = 0
for name, a, b in MUT:
    if a not in src:
        print("MUTATION NOT APPLICABLE:", name); missed += 1; continue
    p = "build/difftest/asm_p2/out/mut.c"
    open(p, "w", newline="\n").write(src.replace(a, b, 1))
    env = dict(os.environ, OVR=p)
    r = subprocess.run(["bash", "build/difftest/asm_p2/build.sh", "build/difftest/asm_p2/math_test.c",
                        "build/difftest/asm_p2/out/mut_test.exe"] + FUNCS, env=env, capture_output=True, text=True)
    if r.returncode:
        print("BUILD FAILED:", name, r.stdout[-300:], r.stderr[-300:]); missed += 1; continue
    t = subprocess.run([os.path.abspath("build/difftest/asm_p2/out/mut_test.exe"), cases], capture_output=True, text=True)
    found = t.returncode != 0
    print("%-8s %s" % ("caught" if found else "MISSED", name))
    missed += not found
print("%d of %d mutations missed" % (missed, len(MUT)))
sys.exit(missed != 0)
