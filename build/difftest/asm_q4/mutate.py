"""Sensitivity check of the differential test: each mutation changes one detail of build/overrides_asm_q4.c (a rounding
point, a compare, a constant, a table offset); the test must report differences for every one.
usage: python -I mutate.py [cases per mutation] [mutation numbers...]   (run run_all.sh first: it makes out/base_asm_funcs.s)"""
import os, subprocess, sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", ".."))
D = "build/difftest/asm_q4"
N = sys.argv[1] if len(sys.argv) > 1 else "20000"
# (function filter, old text, new text)
MUT = [
    ("=SpanR_Flat_11", "e->z = q4_f(sub * dz + Q4_ZI(i));", "e->z = q4_f(sub * e->dz + Q4_ZI(i));"),
    ("=SpanR_Flat_3", "(start) = q4_floor_i(q4_f(((long double)tf_ * sub", "(start) = q4_floor_i(q4_f(((long double)t * sub"),
    ("=SpanR_Flat_5", "    float cy, sub, inv; ", "    float cy, sub; long double inv; ", ("inv = q4_f(1.0L /", "inv = (1.0L /")),
    ("=SpanR_Flat_7", "    if (h < 2) {", "    if (h < 1) {"),
    ("=SpanR_Flat_12", "h = q4_floor_i(q4_ceil(q4_copy(Q4_VY(n)))) - e->y;", "h = q4_floor_i(q4_copy(Q4_VY(n))) - e->y;"),
    ("=Span16_FlatZ_2", "z = q4_floor_i(q4_f(((long double)tf_ * sub + L->z) * 65536.0L));                                   \\\n    }                                                                                                       \\\n    c4 = *(char **)(g_pRdCurrentCamera + 4)\n\n/* colour",
     "z = q4_floor_i(q4_f(((long double)t * sub + L->z) * 65536.0L));                                   \\\n    }                                                                                                       \\\n    c4 = *(char **)(g_pRdCurrentCamera + 4)\n\n/* colour"),
    ("=Span16_FlatZ_3", "if (dl < 0 && dl > -0x51e)                                                                          \\\n            dl = 0;                                                                                         \\\n        l = q4_mul16(frac, dl) + L->l;                                                                      \\\n    }                                                                                                       \\\n    {                                                                                                       \\\n        float tf_;                                                                                          \\\n        t = ((long double)R->z - L->z) * UINT_008fe000[n];                                                  \\\n        tf_ = q4_f(t);                                                                                      \\\n        dz = q4_floor_i(q4_f(t * 65536.0L));                                                                \\\n        z = q4_floor_i(q4_f(((long double)tf_ * sub + L->z) * 65536.0L));                                   \\\n    }                                                                                                       \\\n    c4",
     "if (dl < 0 && dl > -0x400)                                                                          \\\n            dl = 0;                                                                                         \\\n        l = q4_mul16(frac, dl) + L->l;                                                                      \\\n    }                                                                                                       \\\n    {                                                                                                       \\\n        float tf_;                                                                                          \\\n        t = ((long double)R->z - L->z) * UINT_008fe000[n];                                                  \\\n        tf_ = q4_f(t);                                                                                      \\\n        dz = q4_floor_i(q4_f(t * 65536.0L));                                                                \\\n        z = q4_floor_i(q4_f(((long double)tf_ * sub + L->z) * 65536.0L));                                   \\\n    }                                                                                                       \\\n    c4"),
    ("=Span16_FlatZ", "            if ((unsigned short)zs > *zp) {                                                                 \\\n                PIXEL;", "            if ((unsigned short)zs >= *zp) {                                                                 \\\n                PIXEL;"),
    ("=Span16_TexLitKeyZw", "(((v) >> ((16 - UINT_008dde8c) & 31))", "(((v) >> ((15 - UINT_008dde8c) & 31))"),
    ("=Span16_TexLitKey_3", "Q4_TSPAN16(rdRaster_Span16_TexLitKey_3, 0, 1,", "Q4_TSPAN16(rdRaster_Span16_TexLitKey_3, 0, 0,"),
    ("=Span16_TexLitZ_4", "{0, 0xc000, 0x8000, 0x4000}", "{0, 0xb000, 0x8000, 0x4000}"),
    ("=Span8_TexLitKeyZw_3", "*pix = UINT_008dde6c[Q4_BLEND(tx, *pix)])", "*pix = Q4_BLEND(UINT_008dde6c[tx], *pix))"),
    ("=Grad_Flat_3", "dir = d >= 1.0L ? 1 : -1;", "dir = d > 1.0L ? 1 : -1;"),
    ("=Grad_Flat_3", "UINT_008dde54 = dist > DAT_004dda94 ? 1 : 0;", "UINT_008dde54 = dist >= DAT_004dda94 ? 1 : 0;"),
    ("=Grad_Flat_3", "            if (d > mx) {", "            if (d >= mx) {"),
    ("=Draw_TexLitZ_3", "        UINT_008dde5c = t16;\n", "        UINT_008dde5c = t16 + 0x3f00;\n"),
    ("=Draw_FlatLit_9", "        case 128: UINT_007f44f0 = (void *)W128; break;", "        case 129: UINT_007f44f0 = (void *)W128; break;"),
    ("=Draw_FlatLit_8", "t16 + (int)((unsigned)li << 9)", "t16 + (int)((unsigned)li << 8)"),
    ("=Draw_FlatLitZ", "        E.z = q4_f((long double)E.z + E.dz);", "        E.z = E.z;"),
    ("=Draw_FlatLitZ_2", "        Q4_ZI(i) = q4_f(1.0L / ((long double)Q4_VZ(i) - -1.0f));", "        Q4_ZI(i) = q4_f(1.0L / ((long double)Q4_VZ(i) - -1.0f)) + 0.0f * i;"),
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
