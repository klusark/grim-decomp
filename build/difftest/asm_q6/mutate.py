"""Sensitivity check of the q6 differential test: apply one small change to build/overrides_asm_q6.c at a time (a
rounding point, a compare, a mode switch, an index), rebuild the test against it and check that the test reports
differences for the function(s) the change affects.
usage: python -I mutate.py [cases per function] [mutation name filter]"""
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.join(HERE, '..', '..', '..')
SRC = os.path.join(ROOT, 'build', 'overrides_asm_q6.c')
N = sys.argv[1] if len(sys.argv) > 1 else '20000'
FILT = sys.argv[2] if len(sys.argv) > 2 else ''

# (name, function filter for the test, old text, new text)
MUT = [
    ('pspan: no 24-bit mode', 'Span16_Tex_10', 'q6_fldcw(&DAT_00900528);', ';'),
    ('pspan: no-head u, v = 0', 'Span_Tex_6', 's.u = s.v = (kind == 15 && !bpp16) ? s.l : q6_u32(p0);', 's.u = s.v = 0;'),
    ('pspan: no-head u, v of the 8 bpp gouraud spans = p0', 'Span_Tex_8', 's.u = s.v = (kind == 15 && !bpp16) ? s.l : q6_u32(p0);', 's.u = s.v = q6_u32(p0);'),
    ('pspan: kind 10 tail by the table', 'Span16_TexKey_6', 'if (kind == 10) {', 'if (0) {'),
    ('pspan: run u1 from the float 1/p0', 'Span16_Tex_10',
     'u1 = q6_f(r * p1);\n        v1 = q6_f(r * p2);\n        s.du = q6_pstep(((long double)u1 - u0) * 0.0625f',
     'u1 = q6_f(q6_f(r) * p1);\n        v1 = q6_f(r * p2);\n        s.du = q6_pstep(((long double)u1 - u0) * 0.0625f'),
    ('pspan: tail one pixel short', 'Span16_Tex_11', '        q6_ppixels(&s, t + 1);', '        if (t) q6_ppixels(&s, t);'),
    ('pspan: no light clamp', 'Span_TexKey_7', 'if (s.dl < 0 && s.dl > -0x51e)', 'if (0)'),
    ('pspan: head 1/n from the run', 'Span16_TexKey_9', 'inv = q6_copy(g_dwRdRaster_aOneOverNFlex[head]);', 'inv = q6_copy(g_dwRdRaster_aOneOverNFlex[head + 1]);'),
    ('edge: x start from the unrounded slope', 'Edge_Flat_2', 'e[0] = q6_floor_i(q6_f(((long double)s * dy + v[cur * 3]) * 65536.0L));', 'e[0] = q6_floor_i(q6_f((d * dy + v[cur * 3]) * 65536.0L));'),
    ('edge: one line rounds x up', 'Edge_Flat', 'e[0] = q6_floor_i(q6_f(v[cur * 3] * 65536.0L));\n        e[3] = next;',
     'e[0] = q6_floor_i(q6_ceil(q6_f(v[cur * 3] * 65536.0L)) + 1.0f);\n        e[3] = next;'),
    ('pspan: odd index without << 8', 'Span16_Tex_13', 'UINT_008ddebc[lrow + tx] << 8]', 'UINT_008ddebc[lrow + tx]]'),
    ('grad: dudx with float E', 'Grad_Flat', 'dudx = q6_f((E * C - F * D) * fR);', 'dudx = q6_f(((long double)fE * C - F * D) * fR);'),
    ('grad2: V from the extended 1/z', 'Grad_Flat_2', 'V[i] = q6_f((long double)UINT_007f4398[i * 2 + 1] * W[i]);', 'V[i] = q6_f((long double)UINT_007f4398[i * 2 + 1] * w);'),
    ('grad: mip threshold tie', 'Grad_Flat_2', '*level = dist > g_aRdroid_MipDistances ? 1 : 0;', '*level = dist >= g_aRdroid_MipDistances ? 1 : 0;'),
    ('grad: far test >= 1', 'Grad_Flat', 'return (long double)i > 1.0L;', 'return (long double)i >= 1.0L;'),
    ('points: floor of the unrounded y', 'DrawPoints', 'y = q6_floor_i(q6_copy(g_pRdRasterVerts[i * 3 + 1]));\n            x = q6_floor_i(q6_copy(g_pRdRasterVerts[i * 3]));\n            *(unsigned char', 'y = q6_floor_i(q6_copy(g_pRdRasterVerts[i * 3 + 1])) + 0;\n            x = q6_floor_i(q6_copy(g_pRdRasterVerts[i * 3 + 1]));\n            *(unsigned char'),
    ('wireframe: closing line from the first vertex', 'DrawWireframe', 'q6_u32(f) = q6_u32(v[i * 3 + 1]);\n        y0 = q6_floor_i(f);\n        q6_u32(f) = q6_u32(v[i * 3]);\n        x0 = q6_floor_i(f);\n        rdCanvas_DrawLine(Q6_C4(), x0, y0, x1, y1, (unsigned short)colour, 0xffffffff);\n    }\n}', 'q6_u32(f) = q6_u32(v[1]);\n        y0 = q6_floor_i(f);\n        q6_u32(f) = q6_u32(v[i * 3]);\n        x0 = q6_floor_i(f);\n        rdCanvas_DrawLine(Q6_C4(), x0, y0, x1, y1, (unsigned short)colour, 0xffffffff);\n    }\n}'),
    ('span16tex: level row', 'Span16_Tex', 'UINT_008ddea8[DAT_008ddec0 * 256 + UINT_008dded4[*PTR_007f4300]]', 'UINT_008ddea8[DAT_008ddec0 * 255 + UINT_008dded4[*PTR_007f4300]]'),
    ('tex14: v from the extended 1/p', 'Span16_Tex_14', 'UINT_007f43b4 = q6_f((long double)UINT_007f43b8 * DAT_007f4248);', 'UINT_007f43b4 = q6_f(r * DAT_007f4248);'),
    ('tex14: run counter ends at 0', 'Span16_Tex_14', 'while (UINT_007f4390-- > 0) {', 'for (; UINT_007f4390 > 0; UINT_007f4390--) {'),
    ('setuptex: dWa rounded', 'SetupPolyTex', 'dWa = (long double)W[a] - W[c];', 'dWa = q6_f((long double)W[a] - W[c]);'),
    ('setuptex: u bias NaN taken as 0', 'SetupPolyTex', '    else if (!(t >= 0.0L) || !((long double)W[a] * fdUdy', '    else if (t < 0.0L || !((long double)W[a] * fdUdy'),
    ('setuptex: dW/dx * 65536 rounded down', 'SetupPolyTex', 'rec[0x67] = q6_ftol(dWdx * 65536.0f);', 'rec[0x67] = q6_floor_i(q6_f(dWdx * 65536.0f));'),
    ('setuppoly: mip mode', 'SetupPoly', 'q6_mip_level(*(float *)(P + 0x64), mode, &rec[0x70]);\n}', 'q6_mip_level(*(float *)(P + 0x64), mode + 1, &rec[0x70]);\n}'),
    ('select: texlit level row', 'Select_TexLit', '[Q6_I(mat, 4) + level * 256];', '[Q6_I(mat, 4) + level * 255];'),
    ('select8: palette row 63 missing', 'Select_FlatLit_8', 'rec[0x78] = Q6_I(*(char **)(*(char **)rec + 0x4c), 0x348) + 0x7e00;', 'rec[0x78] = Q6_I(*(char **)(*(char **)rec + 0x4c), 0x348);'),
    ('esetup: W from the rounded dW', 'EdgeSetup_Flat', 'Q6_RF(node, 4) = q6_f(dy * dw + Q6_RF(rec, 1 + a));', 'Q6_RF(node, 4) = q6_f(dy * (long double)q6_f(dw) + Q6_RF(rec, 1 + a));'),
    ('esetup: V plane association', 'EdgeSetup_Flat_8', 'Q6_RF(node, 8) = q6_f((Q6_RF(rec, 0x65) * dxs + Q6_RF(rec, 0x41 + a)) + (long double)Q6_RF(rec, 0x66) * dy);', 'Q6_RF(node, 8) = q6_f(((long double)Q6_RF(rec, 0x66) * dy + Q6_RF(rec, 0x41 + a)) + Q6_RF(rec, 0x65) * dxs);'),
    ('esetup: _10 x slope by division', 'EdgeSetup_Flat_10', 'Q6E_PERSP | Q6E_LIGHT, FUN_004169f0', 'Q6E_PERSP | Q6E_LIGHT | Q6E_DIV, FUN_004169f0'),
    ('esetup: up edge from the lower vertex y', 'EdgeSetup_Flat_5', '        yc = y1c;\n', '        yc = y0c;\n'),
    ('spanr: z not stepped', 'SpanR16_TexKey_3', '        z += dz;\n        u += node[4];', '        u += node[4];'),
    ('spanp: no-head u, v from the colour pointer (8 bpp)', 'SpanP8_TexKeyZw', 'u = v = nohead_colour ? (int)d16 : (int)zp;', 'u = v = nohead_colour ? (int)d16 : (int)d8;'),
    ('spanp: no-head u, v of SpanP16_TexKeyZw_3 from the colour pointer', 'SpanP16_TexKeyZw_3', 'void rdRaster_SpanP16_TexKeyZw_3(int *node) { q6_spanp(node, 1, Q6R_PAL_L, 0); }', 'void rdRaster_SpanP16_TexKeyZw_3(int *node) { q6_spanp(node, 1, Q6R_PAL_L, 1); }'),
    ('spanp: z of transparent texels written', 'SpanP16_TexKeyZw_3', '            *zp = (unsigned short)(z >> (sh & 31));                                                         \\\n        }', '        }                                                                                                   \\\n            *zp = (unsigned short)(z >> (sh & 31));'),
]

fails = 0
for name, fn, old, new in MUT:
    if FILT and FILT not in name:
        continue
    src = open(SRC).read()
    if src.count(old) < 1:
        print('MUTATION NOT APPLICABLE: %s' % name)
        fails += 1
        continue
    mut = os.path.join(HERE, 'out', 'mut.c')
    open(mut, 'w', newline='\n').write(src.replace(old, new, 1))
    env = dict(os.environ, OVR='build/difftest/asm_q6/out/mut.c', OUTEXE='q6_mut')
    r = subprocess.run(['bash', os.path.join(HERE, 'run_all.sh'), N, '=' + fn], env=env, capture_output=True, text=True)
    caught = 'DIFFERENCES' in r.stdout
    print('%-55s %-20s %s' % (name, fn, 'caught' if caught else 'NOT CAUGHT'))
    if not caught:
        fails += 1
        print(r.stdout[-500:], r.stderr[-500:])
print('%d not caught' % fails)
sys.exit(1 if fails else 0)
