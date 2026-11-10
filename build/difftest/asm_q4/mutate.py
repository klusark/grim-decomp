"""Sensitivity check of the differential test: each mutation changes one detail of build/overrides_asm_q4.c (a rounding
point, a compare, a constant, a table offset); the test must report differences for every one.
usage: python -I mutate.py [cases per mutation] [mutation numbers...]   (run run_all.sh first: it makes out/base_asm_funcs.s)"""
import os, subprocess, sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", ".."))
D = "build/difftest/asm_q4"
N = sys.argv[1] if len(sys.argv) > 1 else "20000"
# (function filter, old text, new text)
MUT = [
    ("=rdZRaster_SetupLeftEdgeNGonGAT", "e->z = q4_f(sub * dz + Q4_ZI(i));", "e->z = q4_f(sub * e->dz + Q4_ZI(i));"),
    ("=rdZRaster_SetupLeftEdgeNGonFS", "(start) = q4_floor_i(q4_f(((long double)tf_ * sub", "(start) = q4_floor_i(q4_f(((long double)t * sub"),
    ("=rdZRaster_SetupLeftEdgeNGonGS", "    float cy, sub, inv; ", "    float cy, sub; long double inv; ", ("inv = q4_f(1.0L /", "inv = (1.0L /")),
    ("=rdZRaster_SetupLeftEdgeNGonLAT", "    if (h < 2) {", "    if (h < 1) {"),
    ("=rdZRaster_SetupRightEdgeNGonGAT", "h = q4_floor_i(q4_ceil(q4_copy(Q4_VY(n)))) - e->y;", "h = q4_floor_i(q4_copy(Q4_VY(n))) - e->y;"),
    ("=rdZRaster_DrawScanLineNGonFS_16", "z = q4_floor_i(q4_f(((long double)tf_ * sub + L->z) * 65536.0L));                                   \\\n    }                                                                                                       \\\n    c4 = *(char **)(g_pRdCamera_CurCamera + 4)\n\n/* colour",
     "z = q4_floor_i(q4_f(((long double)t * sub + L->z) * 65536.0L));                                   \\\n    }                                                                                                       \\\n    c4 = *(char **)(g_pRdCamera_CurCamera + 4)\n\n/* colour"),
    ("=rdZRaster_DrawScanLineNGonGS_16", "if (dl < 0 && dl > -0x51e)                                                                          \\\n            dl = 0;                                                                                         \\\n        l = q4_mul16(frac, dl) + L->l;                                                                      \\\n    }                                                                                                       \\\n    {                                                                                                       \\\n        float tf_;                                                                                          \\\n        t = ((long double)R->z - L->z) * g_dwRdRaster_aOneOverNFlex[n];                                                  \\\n        tf_ = q4_f(t);                                                                                      \\\n        dz = q4_floor_i(q4_f(t * 65536.0L));                                                                \\\n        z = q4_floor_i(q4_f(((long double)tf_ * sub + L->z) * 65536.0L));                                   \\\n    }                                                                                                       \\\n    c4",
     "if (dl < 0 && dl > -0x400)                                                                          \\\n            dl = 0;                                                                                         \\\n        l = q4_mul16(frac, dl) + L->l;                                                                      \\\n    }                                                                                                       \\\n    {                                                                                                       \\\n        float tf_;                                                                                          \\\n        t = ((long double)R->z - L->z) * g_dwRdRaster_aOneOverNFlex[n];                                                  \\\n        tf_ = q4_f(t);                                                                                      \\\n        dz = q4_floor_i(q4_f(t * 65536.0L));                                                                \\\n        z = q4_floor_i(q4_f(((long double)tf_ * sub + L->z) * 65536.0L));                                   \\\n    }                                                                                                       \\\n    c4"),
    ("=rdZRaster_DrawScanLineNGonLS_16", "            if ((unsigned short)zs > *zp) {                                                                 \\\n                PIXEL;", "            if ((unsigned short)zs >= *zp) {                                                                 \\\n                PIXEL;"),
    ("=rdZRaster_DrawScanLineNGonMGAT_16", "(((v) >> ((16 - g_dwRdZRaster_texRowShift) & 31))", "(((v) >> ((15 - g_dwRdZRaster_texRowShift) & 31))"),
    ("=rdZRaster_DrawScanLineNGonMFAT_16", "Q4_TSPAN16(rdZRaster_DrawScanLineNGonMFAT_16, 0, 1,", "Q4_TSPAN16(rdZRaster_DrawScanLineNGonMFAT_16, 0, 0,"),
    ("=rdZRaster_DrawScanLineNGonGAT_16", "{0, 0xc000, 0x8000, 0x4000}", "{0, 0xb000, 0x8000, 0x4000}"),
    ("=rdZRaster_DrawScanLineNGonMTFAT_8", "*pix = g_dwRdZRaster_aMonoMap[Q4_BLEND(tx, *pix)])", "*pix = Q4_BLEND(g_dwRdZRaster_aMonoMap[tx], *pix))"),
    ("=rdZRaster_CalcAffineGradients", "dir = d >= 1.0L ? 1 : -1;", "dir = d > 1.0L ? 1 : -1;"),
    ("=rdZRaster_CalcAffineGradients", "g_dwRdZRaster_mipMapNum = dist > g_aRdroid_MipDistances ? 1 : 0;", "g_dwRdZRaster_mipMapNum = dist >= g_aRdroid_MipDistances ? 1 : 0;"),
    ("=rdZRaster_CalcAffineGradients", "            if (d > mx) {", "            if (d >= mx) {"),
    ("=rdZRaster_DrawNGonTGS", "        g_dwRdZRaster_aRGBMap = t16;\n", "        g_dwRdZRaster_aRGBMap = t16 + 0x3f00;\n"),
    ("=rdZRaster_DrawNGonGAT", "        case 128: UINT_007f44f0 = (void *)W128; break;", "        case 129: UINT_007f44f0 = (void *)W128; break;"),
    ("=rdZRaster_DrawNGonFAT", "t16 + (int)((unsigned)li << 9)", "t16 + (int)((unsigned)li << 8)"),
    ("=rdZRaster_DrawNGonLS", "        E.z = q4_f((long double)E.z + E.dz);", "        E.z = E.z;"),
    ("=rdZRaster_DrawNGonFS", "        Q4_ZI(i) = q4_f(1.0L / ((long double)Q4_VZ(i) - -1.0f));", "        Q4_ZI(i) = q4_f(1.0L / ((long double)Q4_VZ(i) - -1.0f)) + 0.0f * i;"),
]
src = open(os.path.join(ROOT, "build", "overrides_asm_q4.c")).read()
names = __import__("re").findall(r"^FN\(\w+, *(\w+)\)", open(os.path.join(ROOT, D, "q4_funcs.h")).read(), __import__("re").M)
caught = 0
only = [int(x) for x in sys.argv[2:]]
for k, m in enumerate(MUT):
    filt, old, new = m[:3]
    if only and k not in only:
        continue
    if src.count(old) < 1:
        print("mutation %d: text not found" % k)
        continue
    mut = os.path.join(ROOT, D, "out", "mut.c")
    t = src.replace(old, new, 1)
    for o, n2 in m[3:]:
        t = t.replace(o, n2)
    open(mut, "w", newline="\n").write(t)
    env = dict(os.environ, OVR=mut.replace("\\", "/"))
    b = subprocess.run(["bash", D + "/build.sh", D + "/raster_test.c", D + "/out/mut.exe"] + ["rdRaster_" + n for n in names],
                       cwd=ROOT, env=dict(env, EXTRA_OBJS="build/obj/GRIMFANDANGO.EXE/overrides_asm_o2.o"),
                       capture_output=True, text=True)
    if b.returncode:
        print("mutation %d: build failed: %s" % (k, (b.stdout + b.stderr)[-500:]))
        continue
    r = subprocess.run([os.path.join(ROOT, D, "out", "mut.exe"), N, filt], cwd=ROOT, capture_output=True, text=True)
    hit = r.returncode != 0
    caught += hit
    last = (r.stdout.strip().splitlines() or ["(no output, exit %d)" % r.returncode])[-1]
    print("mutation %2d %-22s %s  (%s)" % (k, filt[1:], "CAUGHT" if hit else "NOT CAUGHT", last))
print("%d of %d mutations caught" % (caught, len(MUT)))
