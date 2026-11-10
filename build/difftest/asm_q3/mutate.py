"""mutate.py: sensitivity check of the asm_q3 differential tests.  Builds a test with deliberately wrong versions of
build/overrides_asm_q3.c (one textual change each) and reports whether the test finds a difference.
usage: python -I build/difftest/asm_q3/mutate.py [cases] [group]   (group: puppet, model, cache; default all)"""
import os, subprocess, sys
root = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..")
os.chdir(root)
cases = sys.argv[1] if len(sys.argv) > 1 else "20000"
only = sys.argv[2] if len(sys.argv) > 2 else None
src = open("build/overrides_asm_q3.c").read()

GROUPS = {
    "puppet": ("build/difftest/asm_q3/puppet_test.c", ["rdPuppet_AdvanceTrack", "rdPuppet_UpdateFrame"], [
        ("Advance: dt == 0 instead of equal-or-unordered", "if (!Q3_NE_ORD(dt, 0.0f))", "if (dt == 0.0f)"),
        ("Advance: wrap test > instead of >=", "if ((long double)t >= cnt) {", "if ((long double)t > cnt) {"),
        ("Advance: loops not rounded (no FRNDINT)", "loops = q3_frndint_cw(q);", "loops = q;"),
        ("Advance: quotient not stored as float", "float q = q3_f((long double)t / cnt);\n            loops = q3_frndint_cw(q);",
         "long double q = (long double)t / cnt;\n            loops = q3_f(__builtin_floorl(q));"),
        ("Advance: product rounded", "- cnt * (long double)loops);", "- q3_f(cnt * (long double)loops));"),
        ("Advance: key clear cap 0x3f", "            if (n >= 0x40)\n                n = 0x40;", "            if (n >= 0x3f)\n                n = 0x3f;"),
        ("Advance: previous time == 0 ordered", "|| !Q3_NE_ORD(Q3F(rec, 0x124), 0.0f))", "|| Q3F(rec, 0x124) == 0.0f)"),
        ("Advance: one-wrap test <= ordered", "|| !((long double)mt > (long double)Q3F(rec, 0x120)))", "|| (long double)mt <= (long double)Q3F(rec, 0x120))"),
        ("Advance: loops > 1 as >=", "} else if ((long double)loops > 1.0L) {", "} else if ((long double)loops >= 1.0L) {"),
        ("Advance: animation not read again after a marker", "                ((q3_marker_fn)Q3P(rec, 0x12c))(Q3U(Q3P(puppet, 4), 0x48), track, Q3U(anim, 0x64 + i * 4));\n                anim = Q3P(rec, 0x128);\n                i++;\n            } while (i < Q3U(anim, 0x40));\n        } else {",
         "                ((q3_marker_fn)Q3P(rec, 0x12c))(Q3U(Q3P(puppet, 4), 0x48), track, Q3U(anim, 0x64 + i * 4));\n                i++;\n            } while (i < Q3U(anim, 0x40));\n        } else {"),
        ("Advance: previous time copied through the FPU", "    Q3U(rec, 0x124) = Q3U(rec, 0x120);", "    Q3F(rec, 0x124) = q3_f(Q3F(rec, 0x120));"),
        ("Advance: stop flag ignored", "    if (stop) {", "    if (0) {"),
        ("Update: key advance > instead of >=", "if ((long double)Q3F(rec, 0x120) >= (long double)Q3F(keys, k * 0x38)) {", "if ((long double)Q3F(rec, 0x120) > (long double)Q3F(keys, k * 0x38)) {"),
        ("Update: key slot cap 3", "                            if (i < 0x40)", "                            if (i < 3)"),
        ("Update: dt rounded", "dt = (long double)Q3F(rec, 0x120) - (long double)Q3F(kf, 0);", "dt = q3_f((long double)Q3F(rec, 0x120) - (long double)Q3F(kf, 0));"),
        ("Update: rotation y rounded early", "ry = (long double)Q3F(kf, 0x30) * dt + (long double)Q3F(kf, 0x18);", "ry = q3_f((long double)Q3F(kf, 0x30) * dt + (long double)Q3F(kf, 0x18));"),
        ("Update: weight < 1 ordered", "if (!((long double)Q3F(rec, 0x18) >= 1.0L)) {", "if ((long double)Q3F(rec, 0x18) < 1.0L) {"),
        ("Update: best weight >= 1 as > 1", "if (pri < pri0 && (long double)W0 >= 1.0L)", "if (pri < pri0 && (long double)W0 > 1.0L)"),
        ("Update: 1 - w rounded", "k = 1.0L - (long double)W0;", "k = q3_f(1.0L - (long double)W0);"),
        ("Update: blend test W1 >= 0", "if (!((long double)W0 >= 1.0L) && (long double)W1 > 0.0L) {", "if (!((long double)W0 >= 1.0L) && (long double)W1 >= 0.0L) {"),
        ("Update: 1/W0 rounded", "long double inv = 1.0L / (long double)W0;", "long double inv = q3_f(1.0L / (long double)W0);"),
        ("Update: rest rotation z from y", "R0[2] = q3_f((long double)Q3F(j, 0x40) + (long double)nz);", "R0[2] = q3_f((long double)Q3F(j, 0x3c) + (long double)nz);"),
        ("Update: scale test != (NaN calls)", "if (Q3_NE_ORD(v[0], 0.0f) ||", "if (v[0] != 0.0f ||"),
        ("Update: second priority after demotion", "                    pri1 = pri0;\n                    pri0 = pri;", "                    pri1 = pri;\n                    pri0 = pri;"),
        ("Update: lower priority test <=", "                if (pri < pri1)\n", "                if (pri <= pri1)\n"),
        ("Update: Normalize result not rounded", "r[1] = q3_f(Math_NormalizeAngle180(r[1]));", "r[1] = q3_f((long double)Math_NormalizeAngle180(r[1]) + 0.0L);"),
    ]),
    "model": ("build/difftest/asm_q3/model_test.c", ["rdModel3_LoadText", "FUN_004addf0"], [
        ("Load: +0x3c cleared for 4 bytes per vertex", "for (i = 0; i < nv; i++)    /* nv bytes", "for (i = 0; i < nv * 4; i++)    /* nv bytes"),
        ("Load: face normal y / z swapped", "                Q3U(fp, 0x44) = y;\n                Q3U(fp, 0x48) = z;", "                Q3U(fp, 0x44) = z;\n                Q3U(fp, 0x48) = y;"),
        ("Load: parent index < 0 as none", "Q3P(node, 0x54) = (int)hp == -1 ? 0", "Q3P(node, 0x54) = (int)hp < 0 ? 0"),
        ("Load: normals allocation line", "Q3_ALLOC(nv * 12, 0x148)", "Q3_ALLOC(nv * 12, 0x149)"),
        ("Load: no line skipped after the uvs", "            Q3U(mesh, 0x4c) = ntv;\n            if (!Q3_READ())\n                goto fail;", "            Q3U(mesh, 0x4c) = ntv;"),
        ("Load: no new line after shadow", "                Q3I(mesh, 0x54) = shadow;\n                if (!Q3_READ())\n                    goto fail;", "                Q3I(mesh, 0x54) = shadow;"),
        ("Load: vertex limit 0x1ff", "if (nv > 0x200)", "if (nv > 0x1ff)"),
        ("Load: face index not stored", "                Q3U(fp, 0) = f;\n", ""),
        ("Load: material slots in reading order", "d = names[idx];", "d = names[i];"),
        ("Load: vertex lists split without commas", "Q3I(Q3P(fp, 0x18), k * 4) = Q3_ATOI(Q3_TOK(0, Q3_WSC));\n                        Q3_TOK(0, Q3_WSC);", "Q3I(Q3P(fp, 0x18), k * 4) = Q3_ATOI(Q3_TOK(0, Q3_WS));\n                        Q3_TOK(0, Q3_WS);"),
        ("Load: no node allocation for 0 nodes", "if ((Q3P(m, 0x58) = (char *)Q3_ALLOC(nn * 0xb8, 0x1ef)) == 0)", "if (nn && (Q3P(m, 0x58) = (char *)Q3_ALLOC(nn * 0xb8, 0x1ef)) == 0)"),
        ("Load: no CountNodeChildren", "    rdModel3_CountNodeChildren((int)m);\n", ""),
        ("Load: 0x18 vertices rejected", "if (n == 0 || (uint)n > 0x18)", "if (n == 0 || (uint)n >= 0x18)"),
        ("Load: face count re-read from the mesh", "            for (f = 0; f < nf; f++, fp += 0x4c) {\n                int mi", "            for (f = 0; f < Q3U(mesh, 0x50) - (nf > 3); f++, fp += 0x4c) {\n                int mi"),
        ("Load: no assertion", "        if (nmats >= 0x80)\n", "        if (0)\n"),
        ("Load: geoset mesh count not stored", "        Q3U(gp, -4) = nmesh;\n", ""),
        ("Load: intensity from x", "q3_f(*(float *)&w);", "q3_f(*(float *)&x);"),
    ]),
    "cache": ("build/difftest/asm_q3/cache_test.c", ["rdCache_SendFaceListToHardware", "_ftol"], [
        ("Cache: NaN level not clamped to 0", "    if (!(s >= 0.0L))\n        c = 0.0L;", "    if (s < 0.0L)\n        c = 0.0L;"),
        # (the association of the tint sums, r - (b/2 + g/2) against (r - b/2) - g/2, changes a tint by one ulp; the
        #  truncated colour products almost never show it: not a useful mutation)
        ("Cache: tint without the halves of r", "long double r5 = (long double)Q3GF(0x0090002c) * 0.5L;", "long double r5 = (long double)Q3GF(0x0090002c);"),
        ("Cache: one triangle up to 4 vertices", "    if (n <= 3) {", "    if (n <= 4) {"),
        ("Cache: light multiplier 255 in geometry 3", "q3_mesh_light(e, light, fl, 63.0L, 0x28);", "q3_mesh_light(e, light, fl, 255.0L, 0x28);"),
        ("Cache: floor test ordered", "    if (!(c > (long double)fl))", "    if (c <= (long double)fl)"),
        ("Cache: tint test >= 0", "if ((long double)Q3GF(0x0090002c) > 0.0L ||", "if ((long double)Q3GF(0x0090002c) >= 0.0L ||"),
        ("Cache: mip thresholds >=", "mip = !(z > Q3GF(0x004dda90)) ? 0 : !(z > Q3GF(0x004dda94)) ? 1 : !(z > Q3GF(0x004dda98)) ? 2 : 3;", "mip = !(z >= Q3GF(0x004dda90)) ? 0 : !(z > Q3GF(0x004dda94)) ? 1 : !(z > Q3GF(0x004dda98)) ? 2 : 3;"),
        ("Cache: force flag reset per mesh", "        mat = Q3P(e, 0x38);\n        if (mat == 0)", "        mat = Q3P(e, 0x38);\n        if (alpha == 0xff && !(*(unsigned char *)(e + 4) & 2)) force = 0;\n        if (mat == 0)"),
        ("Cache: texture size from h", "texw = q3_f(Q3_FILD_U(w << (mip & 31)));", "texw = q3_f(Q3_FILD_U(h << (mip & 31)));"),
        ("Cache: z not written back (geometry 4)", "                    Q3F(v, 8) = q3_f((long double)d + (long double)Q3F(v, 8));\n                    q = 1.0L / (long double)Q3F(v, 8);", "                    q = 1.0L / q3_f((long double)d + (long double)Q3F(v, 8));"),
        ("Cache: rhw not scaled (geometry 3)", "Q3_VBF(n, 0xc) = q3_f(q * 0.03125L);", "Q3_VBF(n, 0xc) = q3_f(q);"),
        ("Cache: z test == 0 ordered", "                if (!Q3_NE_ORD(Q3F(v, 8), 0.0f)) {\n                    q = 0.0L;", "                if (Q3F(v, 8) == 0.0f) {\n                    q = 0.0L;"),
        ("Cache: x rounded to nearest", "Q3_VBF(n, 0) = q3_frndint_52a(Q3F(v, 0));\n                Q3_VBF(n, 4) = q3_frndint_52a(Q3F(v, 4));\n                if (!Q3_NE_ORD(Q3F(v, 8), 0.0f)) {", "Q3_VBF(n, 0) = q3_f(__builtin_rintl(Q3F(v, 0)));\n                Q3_VBF(n, 4) = q3_frndint_52a(Q3F(v, 4));\n                if (!Q3_NE_ORD(Q3F(v, 8), 0.0f)) {"),
        ("Cache: palette factor not masked", "cR = q3_ftol((long double)Q3F(pal, 0x24) * (long double)cR) & 0xff;", "cR = q3_ftol((long double)Q3F(pal, 0x24) * (long double)cR);"),
        ("Cache: scale test ordered", "                if (!((long double)Q3GF(0x00900044) >= 1.0L)) {\n                    R = q3_ftol((long double)cR * (long double)Q3GF(0x00900044));\n                    G = q3_ftol((long double)cG * (long double)Q3GF(0x00900044));\n                    B = q3_ftol((long double)cB * (long double)Q3GF(0x00900044));\n                }\n                cR = q3_clamp255(R);\n                cG = q3_clamp255(G);\n                cB = q3_clamp255(B);\n                col = ((((uint)cR | ((uint)alpha << 8)) << 8 | (uint)cG) << 8) | (uint)cB;\n                Q3_VB(n, 0x10) = col;\n                Q3_VBF",
         "                if ((long double)Q3GF(0x00900044) < 1.0L) {\n                    R = q3_ftol((long double)cR * (long double)Q3GF(0x00900044));\n                    G = q3_ftol((long double)cG * (long double)Q3GF(0x00900044));\n                    B = q3_ftol((long double)cB * (long double)Q3GF(0x00900044));\n                }\n                cR = q3_clamp255(R);\n                cG = q3_clamp255(G);\n                cB = q3_clamp255(B);\n                col = ((((uint)cR | ((uint)alpha << 8)) << 8 | (uint)cG) << 8) | (uint)cB;\n                Q3_VB(n, 0x10) = col;\n                Q3_VBF"),
        ("Cache: geometry 3 colour of lighting 3 + 0x4c recomputed", "                    if (Q3GI(0x0090004c) != 1) {\n                        long double k", "                    if (1) {\n                        long double k"),
        ("Cache: geometry 3 palette flag only with a palette", "                }\n                flags |= 0x8000;\n                if (mask) {", "                    flags |= 0x8000;\n                }\n                if (mask) {"),
        ("Cache: tint G from tR", "cG += q3_ftol((long double)cG * (long double)tG);\n                    cB += q3_ftol((long double)cB * (long double)tB);\n                }\n                R = cR; G = cG; B = cB;\n                if (!((long double)Q3GF(0x00900044) >= 1.0L)) {\n                    R = q3_ftol((long double)cR * (long double)Q3GF(0x00900044));\n                    G = q3_ftol((long double)cG * (long double)Q3GF(0x00900044));\n                    B = q3_ftol((long double)cB * (long double)Q3GF(0x00900044));\n                }\n                cR = q3_clamp255(R);\n                cG = q3_clamp255(G);\n                cB = q3_clamp255(B);\n                col = ((((uint)cR | ((uint)alpha << 8)) << 8 | (uint)cG) << 8) | (uint)cB;\n                Q3_VB(n, 0x10) = col;\n                Q3_VB(n, 0x18) = 0;",
         "cG += q3_ftol((long double)cG * (long double)tR);\n                    cB += q3_ftol((long double)cB * (long double)tB);\n                }\n                R = cR; G = cG; B = cB;\n                if (!((long double)Q3GF(0x00900044) >= 1.0L)) {\n                    R = q3_ftol((long double)cR * (long double)Q3GF(0x00900044));\n                    G = q3_ftol((long double)cG * (long double)Q3GF(0x00900044));\n                    B = q3_ftol((long double)cB * (long double)Q3GF(0x00900044));\n                }\n                cR = q3_clamp255(R);\n                cG = q3_clamp255(G);\n                cB = q3_clamp255(B);\n                col = ((((uint)cR | ((uint)alpha << 8)) << 8 | (uint)cG) << 8) | (uint)cB;\n                Q3_VB(n, 0x10) = col;\n                Q3_VB(n, 0x18) = 0;"),
        ("Cache: fan order", "            if ((k & 1) == 0)\n                prev = lo++;", "            if ((k & 1) != 0)\n                prev = lo++;"),
        ("Cache: triangle base after the retry flush", "            if (rdMaterial_AddToTextureCache(mat, (uint *)info, mip, force) == 0) {\n                rdCache_DrawRenderList();\n                std3D_ResetRenderList();", "            if (rdMaterial_AddToTextureCache(mat, (uint *)info, mip, force) == 0) {\n                rdCache_DrawRenderList();\n                std3D_ResetRenderList();\n                base = Q3GI(0x0068bfa8);"),
        ("Cache: flush test >", "if (Q3G(0x0068bfa8) + Q3U(e, 0x1c) >= Q3G(0x00806940)) {", "if (Q3G(0x0068bfa8) + Q3U(e, 0x1c) > Q3G(0x00806940)) {"),
        ("Cache: lighting 3 arrays from 0x2c in geometry 3", "q3_mesh_light(e, light, fl, 63.0L, 0x28);", "q3_mesh_light(e, light, fl, 63.0L, 0x2c);"),
        ("Cache: no 0x400 flag", "                flags |= 0x400;\n", ""),
        ("Cache: uv v divided by the width", "[i * 2 + 1] / (long double)texh);", "[i * 2 + 1] / (long double)texw);"),
        ("Cache: mip kept when the type is unknown -> 0", "            case 1:\n                mip = 0;\n                break;", "            default:\n                mip = 0;\n                break;"),
    ]),
}

missed = total = 0
for g, (test, funcs, muts) in GROUPS.items():
    if only and g != only:
        continue
    for name, a, b in muts:
        total += 1
        if a not in src:
            print("MUTATION NOT APPLICABLE:", name); missed += 1; continue
        p = "build/difftest/asm_q3/out/mut.c"
        open(p, "w", newline="\n").write(src.replace(a, b, 1))
        env = dict(os.environ, OVR=p)
        exe = "build/difftest/asm_q3/out/mut_%s.exe" % g
        r = subprocess.run(["bash", "build/difftest/asm_q3/build.sh", test, exe] + funcs, env=env, capture_output=True, text=True)
        if r.returncode:
            print("BUILD FAILED:", name, r.stdout[-300:], r.stderr[-300:]); missed += 1; continue
        t = subprocess.run([os.path.abspath(exe), cases], capture_output=True, text=True)
        found = t.returncode != 0
        print("%-8s %s" % ("caught" if found else "MISSED", name))
        missed += not found
print("%d of %d mutations missed" % (missed, total))
sys.exit(missed != 0)
