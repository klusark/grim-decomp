"""Sensitivity check of the differential test: each mutation changes one detail of build/overrides_asm_q5.c (a control
word load, a rounding point, an operand order, a compare, a constant, a left-over value); the test must report
differences for every one.
usage: python -I mutate.py [cases per mutation] [mutation numbers...]   (run run_all.sh first: it makes out/base_asm_funcs.s)"""
import os, re, subprocess, sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", ".."))
D = "build/difftest/asm_q5"
N = sys.argv[1] if len(sys.argv) > 1 else "20000"
# (function filter, regex, replacement): the first match is replaced
MUT = [
    # the peephole's behaviour: no default control word after the first conversion (the filler stays truncating, 24 bits)
    ("=rdZRaster_DrawScanLineNGonLIT_8", r"(z = q5_floor_i\(zf\);\s*\\\n\s*\}\s*\\\n)\s*q5_fldcw\(&DAT_00900524\);", r"\1"),
    ("=rdRaster_Span16_TexZw_9", r"(UINT_007f4cfc = q5_floor_i\(q5_f\(\(long double\)oz \* 65536\.0f\)\);\s*\\\n\s*\}\s*\\\n)\s*q5_fldcw\(&DAT_00900524\);", r"\1"),
    # no truncating control word at the start
    ("=rdZRaster_DrawScanLineNGonFIT_16", r"q5_fldcw\(&DAT_00900528\);", ""),
    # the first part's divide by the unrounded 1/z at its end
    ("=rdZRaster_DrawScanLineNGonTFIT_8", r"w = 1\.0f / \(long double\)oz1;", "w = 1.0f / (k * g_dwRdZRaster_dOneOverZdX + oz);"),
    # the last part's operand order
    ("=rdZRaster_DrawScanLineNGonGIT_8", r"w = 1\.0f / \(\(k \* g_dwRdZRaster_dOneOverZdX - g_dwRdZRaster_oneOverZStep\) \+ oz\);", "w = 1.0f / (k * g_dwRdZRaster_dOneOverZdX + (oz - g_dwRdZRaster_oneOverZStep));"),
    # the left-over u / v of a span without a first part
    ("=rdZRaster_DrawScanLineNGonLIT_16", r"(Q5_PSPAN16\(rdZRaster_DrawScanLineNGonLIT_16, 0, 0, )Q5_GPIX", r"\1Q5_GZ"),
    ("=rdZRaster_DrawScanLineNGonMTGIT_16", r"(Q5_PSPAN16\(rdZRaster_DrawScanLineNGonMTGIT_16, 1, 1, )Q5_GZF", r"\1Q5_GL"),
    # the first part's 1/k from the table
    ("=rdZRaster_DrawScanLineNGonMFIT_8", r"float rk = g_dwRdRaster_aOneOverNFlex\[first\];", "float rk = 1.0f / first;"),
    # Span16_TexZ_5's misplaced << 8 (the intended lookup)
    ("=rdZRaster_DrawScanLineNGonTFIT_16", r"g_dwRdZRaster_aRGBToPalette\[g_dwRdZRaster_aRGBMap\[tx\] << 8\] \+ g_dwRdZRaster_aRGBToPalette\[\*pix\]", "(g_dwRdZRaster_aRGBToPalette[g_dwRdZRaster_aRGBMap[tx]] << 8) + g_dwRdZRaster_aRGBToPalette[*pix]"),
    # key ignored
    ("=rdZRaster_DrawScanLineNGonMGIT_16", r"Q5_PSPAN16\(rdZRaster_DrawScanLineNGonMGIT_16, 1, 1,", "Q5_PSPAN16(rdZRaster_DrawScanLineNGonMGIT_16, 1, 0,"),
    # edge: v/z operand order, and the direct divide replaced by the reciprocal
    ("=rdZRaster_SetupLeftEdgeNGonLIT", r"e->vz = q5_f\(\(dxs \* g_dwRdZRaster_dVOverZdX \+ Q5_VZI\(i\)\) \+ \(long double\)sub \* g_dwRdZRaster_dVOverZdY\);", "e->vz = q5_f(((long double)sub * g_dwRdZRaster_dVOverZdY + Q5_VZI(i)) + dxs * g_dwRdZRaster_dVOverZdX);"),
    ("=rdZRaster_SetupRightEdgeNGonLIT", r"t = \(\(long double\)Q5_VX\(n\) - Q5_VX\(i\)\) / \(\(long double\)Q5_VY\(n\) - Q5_VY\(i\)\);", "t = ((long double)Q5_VX(n) - Q5_VX(i)) * q5_f(1.0f / ((long double)Q5_VY(n) - Q5_VY(i)));"),
    ("=rdZRaster_SetupLeftEdgeNGonGIT", r"if \(h < 2\) \{", "if (h < 1) {"),
    # Grad_Flat_4: v/z from the unrounded 1/z, the z step from the rounded d/dx, the bias compare
    ("=rdZRaster_CalcPerspGradients", r"Q5_VZI\(i\) = q5_f\(\(long double\)T\[i \* 2 \+ 1\] \* Q5_ZI\(i\)\);", "Q5_VZI(i) = q5_f(T[i * 2 + 1] * zi);"),
    ("=rdZRaster_CalcPerspGradients", r"g_dwRdZRaster_dOneOverZdXFixed = q5_ftol\(e \* 65536\.0f\);", "g_dwRdZRaster_dOneOverZdXFixed = q5_ftol((long double)g_dwRdZRaster_dOneOverZdX * 65536.0f);"),
    ("=rdZRaster_CalcPerspGradients", r"if \(e > 0\.0L\)\n            g_dwRdZRaster_dUdXModifier = 0x8000;", "if (e >= 0.0L)\n            g_dwRdZRaster_dUdXModifier = 0x8000;"),
    # fillers without z shift: the light mask, the count written only for a span, the z compare
    ("=rdRaster_Span16_TexLitZw_12", r"#define Q5_ZPALL g_dwRdZRaster_aRGBMap\[tx \+ \(\(l & 0x3f0000\) >> 8\)\]", "#define Q5_ZPALL g_dwRdZRaster_aRGBMap[tx + ((l & 0x1f0000) >> 8)]"),
    ("=rdRaster_Span16_TexZw_2", r"UINT_007f4cac = n;\s*\\\n(\s*)if \(n <= 0\)\s*\\\n\s*return;", r"if (n <= 0) return; \\\n\1UINT_007f4cac = n;"),
    ("=rdRaster_Span16_TexZw_13", r"if \(\(unsigned short\)z > zb\[i_\]\)", "if ((unsigned short)z >= zb[i_])"),
    # drivers: the blend table of the gouraud translucent drivers, the 16-pixel step, the left edge's v/z step
    ("=rdZRaster_DrawNGonTGIT", r"Q5_TDRAW\(rdZRaster_DrawNGonTGIT, 2, 1,", "Q5_TDRAW(rdZRaster_DrawNGonTGIT, 2, 0,"),
    ("=rdZRaster_DrawNGonFIT", r"g_dwRdZRaster_uOverZStep = q5_f\(\(long double\)g_dwRdZRaster_dUOverZdX \* 16\.0f\);", "g_dwRdZRaster_uOverZStep = q5_f((long double)g_dwRdZRaster_dUOverZdX * 15.0f);"),
    ("=rdZRaster_DrawNGonMTLIT", r"L\.vz = q5_f\(\(long double\)L\.vz \+ L\.dvz\);", "L.vz = L.vz;"),
    # the renderer without z-buffer: v0 from the rounded w, the control word switch at the first conversion, the chunk
    # counter's end value, the light mask, the global count of the shifted z pass, the u bias
    ("=rdRaster_SpanP16_Tex_2", r"Q5_GF\(DAT_007f4b5c\) = q5_f\(\(long double\)Q5_GF\(DAT_007f4b60\) \* Q5_GF\(DAT_007f4af0\)\);", "Q5_GF(DAT_007f4b5c) = q5_f(w_ * Q5_GF(DAT_007f4af0));"),
    ("=rdRaster_SpanP16_TexLit_5", r"    if \(\*tr\) \{", "    if (0) {"),
    ("=rdRaster_SpanP16_Tex", r"k = UINT_007f4b2c--;", "k = UINT_007f4b2c; if (k > 0) UINT_007f4b2c--;"),
    ("=rdRaster_SpanR16_TexLit_3", r"#define Q5_NPALL g_dwRdAFRaster_aRGBMap\[tx \+ \(\(l & 0x3f0000\) >> 8\)\]", "#define Q5_NPALL g_dwRdAFRaster_aRGBMap[tx + ((l & 0x1f0000) >> 8)]"),
    ("=rdRaster_SpanR_FlatZw_2", r"UINT_007f4ad0 = c;", "(void)c;"),
    ("=rdRaster_SpanR16_Tex_4", r"UINT_007f4b6c \+= g_dwRdAFRaster_dUdXModifier;", "UINT_007f4b6c += g_dwRdAFRaster_dVdXModifier;"),
]
src = open(os.path.join(ROOT, "build", "overrides_asm_q5.c")).read()
names = re.findall(r"^FN\(\w+, *(\w+)\)", open(os.path.join(ROOT, D, "q5_funcs.h")).read(), re.M)
caught = 0
only = [int(x) for x in sys.argv[2:]]
for k, (filt, old, new) in enumerate(MUT):
    if only and k not in only:
        continue
    t, cnt = re.subn(old, new, src, count=1)
    if not cnt:
        print("mutation %d: text not found" % k)
        continue
    mut = os.path.join(ROOT, D, "out", "mut.c")
    open(mut, "w", newline="\n").write(t)
    env = dict(os.environ, OVR=mut.replace("\\", "/"), EXTRA_OBJS="")
    b = subprocess.run(["bash", D + "/build.sh", D + "/raster_test.c", D + "/out/mut.exe"] + ["rdRaster_" + n for n in names],
                       cwd=ROOT, env=env, capture_output=True, text=True)
    if b.returncode:
        print("mutation %d: build failed: %s" % (k, (b.stdout + b.stderr)[-500:]))
        continue
    r = subprocess.run([os.path.join(ROOT, D, "out", "mut.exe"), N, filt], cwd=ROOT, capture_output=True, text=True)
    hit = r.returncode != 0
    caught += hit
    last = [l for l in r.stdout.strip().splitlines() if " cases " in l and not l.startswith("DIFF")]
    print("mutation %2d %-20s %s  (%s)" % (k, filt[1:], "CAUGHT" if hit else "NOT CAUGHT", (last or ["exit %d" % r.returncode])[-1].strip()))
print("%d of %d mutations caught" % (caught, len(MUT) if not only else len(only)))
