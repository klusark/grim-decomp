/* Differential test of rdCache_SendFaceListToHardware (build/overrides_asm_q3.c) against the original 1.01 machine code (sliced
 * from the assembly of 2df265d, with the original _ftol).
 *
 * Each case fills the mesh cache (up to 8 entries of 0x78 bytes at 0x008ddfc0) with random meshes: geometry / lighting
 * modes around the limits, materials with cels (-1 = the material's own), textures with and without flag 0x8, texture
 * types 0-5 and distances on the 10 / 20 / 40 thresholds, palettes (the default one or another with factors that
 * overflow 255), vertex arrays with z = 0 / -0 / -+1 / NaN, x / y on halves (the FRNDINT with DAT_0090052a), light
 * levels on 0 / 1 / the floor, tiny negatives, NaN; and the globals: the tints, the channel masks, the global scale
 * (1, below 1, NaN), the lighting flag 0x0090004c, the batch capacity (flushes in the middle), the device caps (forced
 * alpha).  It runs the original and the C on the same state under the x87 precision control 24, 53 or 64 bits and
 * compares: the return value, the cache entries, the mesh data (light arrays written back, z written back), the D3D
 * vertex buffer, both triangle lists and their counts, the call log of the stand-ins (std3D_ResetRenderList /
 * Flush3DBatch, std3D_SetCurrentPalette, rdMaterial_AddToTextureCache (sometimes failing), std3D_PurgeTextureCache,
 * std3D_GetValidDimensions), the x87 control word and stack top.
 * The original keeps the mip level and the last vertex colour in stack slots it never initialises; the generator
 * avoids the two cases that read them before a write (see the C's comment).
 * usage: cache_test.exe [cases]   (P3_NAN=1: no signalling NaN inputs) */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <stdint.h>
#include "fx.h"

typedef unsigned uint;
extern uint orig_rdCache_SendFaceListToHardware(void), rdCache_SendFaceListToHardware(void);

#define ARSZ (1 << 20)
static unsigned char ar[ARSZ] __attribute__((aligned(16))), ar0[ARSZ], arA[ARSZ];
static uint used;
static void *A(uint n) { void *p = ar + used; used = (used + n + 15) & ~15u; if (used > ARSZ) abort(); return p; }
#define U(p, o) (*(uint *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(void **)((char *)(p) + (o)))

static uint64_t ss;
static uint snext(void) { ss ^= ss << 13; ss ^= ss >> 7; ss ^= ss << 17; return (uint)(ss >> 17); }
static uint lg[1 << 16]; static int nlg;
static void L(uint v) { if (nlg < (1 << 16)) lg[nlg++] = v; }
static uint fbits(float f) { uint u; memcpy(&u, &f, 4); return u; }
static float bitsf(uint u) { float f; memcpy(&f, &u, 4); return f; }
static uint R(uint n) { return (uint)(fx_rnd() % n); }
static int nan_mode;
static uint special_bits(uint k)
{
    static const uint t[] = {0x00000000, 0x80000000, 0x7f800000, 0xff800000, 0x7fc00000, 0x7f800001, 0xffc00000,
                             0x00000001, 0x807fffff, 0x3f800000, 0x3f7fffff, 0x3f800001, 0xbf800000, 0x7f7fffff,
                             0x80000001, 0x33800000, 0xb3800000};
    uint v = t[k % (sizeof t / sizeof t[0])];
    if (nan_mode >= 1 && (v & 0x7fc00000) == 0x7f800000 && (v & 0x7fffff)) v = 0x7fc00000;
    return v;
}
static float rf(float scale)
{
    uint k = R(40);
    if (k < 3) return bitsf(special_bits(R(64)));
    if (k < 16) return (float)((int)R(17) - 8) * 0.5f;
    return (float)(((double)(int)(fx_rnd() % 2000001) - 1000000.0) / 1000000.0 * scale);
}
/* a light level: 0..1 mostly, the edges, a little outside */
static float rlevel(void)
{
    switch (R(12)) {
    case 0: return bitsf(special_bits(R(64)));
    case 1: return 0.0f;
    case 2: return 1.0f;
    case 3: return -1e-30f;
    case 4: return (float)R(5) * 0.25f;
    case 5: return 1.0f + (float)R(3) * 0.5f;
    case 6: return -(float)R(3) * 0.25f;
    default: return (float)(fx_rnd() % 100001) / 100000.0f;
    }
}

/* ---- stand-ins ---- */
static int ens_fail;   /* bit i: the i-th rdMaterial_AddToTextureCache call fails */
static int nens;
void __cdecl std3D_ResetRenderList(void)
{
    L(0xbe900000);
    if (snext() % 3 == 0) FXU32(0x68bfa8) = 0;
}
void __cdecl rdCache_DrawRenderList(void)
{
    L(0xf1500000); L(FXU32(0x68bfa8)); L(FXU32(0x60bfa0)); L(FXU32(0x6f0fb0));
}
void __cdecl std3D_SetCurrentPalette(void *p, int f) { L(0xd5e70000); L((uint)p); L(f); }
int __cdecl rdMaterial_AddToTextureCache(void *a, uint *info, int mip, int alt)
{
    int r = !((ens_fail >> (nens++ & 31)) & 1);
    L(0xe7500000); L((uint)a); L((uint)info); L(mip); L(alt); L(r);
    return r;
}
void __cdecl std3D_PurgeTextureCache(void) { L(0xd3e50000); }
void __cdecl std3D_GetValidDimensions(uint w, uint h, uint *ow, uint *oh)
{
    L(0xc1a70000); L(w); L(h);
    *ow = w > 256 ? 256 : w;
    *oh = snext() % 4 == 0 ? h / 2 : h;
}

static uint get_sw(void) { unsigned short sw; __asm__ volatile("fnstsw %0" : "=m"(sw)); return sw; }
static uint get_cw(void) { unsigned short cw; __asm__ volatile("fnstcw %0" : "=m"(cw)); return cw; }

/* ---- the compared global regions (virtual addresses) ---- */
static const uint regs[][2] = {
    {0x00606fa0, 0x0060bfa4},   /* untextured triangle list, textured count */
    {0x0068bfa8, 0x0068bfac},   /* vertex count */
    {0x006cbfb0, 0x006d0fb0},   /* textured triangle list (0x400 triangles) */
    {0x006f0fb0, 0x006f0fb4},   /* untextured count */
    {0x006f0fb8, 0x006f4fb8},   /* vertex buffer (0x200 vertices) */
    {0x008ddfa0, 0x008de3c0},   /* cache count and entries */
    {0x00900000, 0x00900070},   /* the settings the function reads */
};
#define NREG (sizeof regs / sizeof regs[0])
static unsigned char g0[NREG][0x6000], gA[NREG][0x6000];
static void gsave(unsigned char (*d)[0x6000]) { uint k; for (k = 0; k < NREG; k++) memcpy(d[k], FXDATA(regs[k][0]), regs[k][1] - regs[k][0]); }
static void gload(unsigned char (*d)[0x6000]) { uint k; for (k = 0; k < NREG; k++) memcpy(FXDATA(regs[k][0]), d[k], regs[k][1] - regs[k][0]); }

static long nf, nc, nnan, nret0;
static int dbg;
static int fkind(const void *a, const void *b, int n)
{
    const uint *x = a, *y = b;
    int i, k = 0;
    for (i = 0; i < n; i++)
        if (x[i] != y[i]) {
            if ((x[i] & 0x7fffffff) > 0x7f800000 && (y[i] & 0x7fffffff) > 0x7f800000) k = 1;
            else {
                if (dbg) {
                    int c = 0;
                    for (; i < n && c < 12; i++)
                        if (x[i] != y[i]) { printf("  dword %d: orig %08x C %08x\n", i, y[i], x[i]); c++; }
                }
                return 2;
            }
        }
    return k;
}

static void t_case(long i)
{
    static const unsigned pcs[3] = {_PC_24, _PC_53, _PC_64};
    char *pals[3], *mats[4], *texs[6], *infos[3], *caps;
    int nmesh = R(9), k, j, seen_type = 0, seen_vertex = 0;
    void *locked = 0;
    uint ra, rb, cwA, swA, cw, sw, lgA[1 << 16];
    int nlgA, kind = 0;
    uint64_t seed;
    used = 0;
    /* palettes: [0] the default one */
    for (k = 0; k < 3; k++) {
        pals[k] = A(0x30 + 0x300);
        for (j = 0; j < 0x330; j++) ((unsigned char *)pals[k])[j] = (unsigned char)fx_rnd();
        F(pals[k], 0x24) = R(3) ? (float)R(9) * 0.25f : rf(300);
        F(pals[k], 0x28) = R(3) ? (float)R(9) * 0.25f : rf(300);
        F(pals[k], 0x2c) = R(3) ? (float)R(9) * 0.25f : rf(300);
    }
    FXU32(0x4f5ec4) = (uint)pals[0];
    /* texture infos with four mip levels */
    for (k = 0; k < 3; k++) {
        infos[k] = A(0xa4 + 4 * 0x98 + 0x40);
        for (j = 0; j < (0xa4 + 4 * 0x98 + 0x40) / 4; j++) U(infos[k], j * 4) = (uint)fx_rnd();
        U(infos[k], 0) = R(4);
        U(infos[k], 0x18) = 1 + R(4);
        for (j = 0; j < 4; j++) {
            char *mi = A(0x20);
            U(mi, 0xc) = 1u << R(10); U(mi, 0x10) = 1u << R(10);
            if (R(10) == 0) U(mi, 0xc) = 0;
            P(infos[k], 0x1c + j * 4) = mi;
            U(infos[k], j * 0x98 + 0xa4) = R(3) ? 1 : 0;
        }
    }
    for (k = 0; k < 6; k++) {
        texs[k] = A(0x20);
        for (j = 0; j < 8; j++) U(texs[k], j * 4) = (uint)fx_rnd();
        U(texs[k], 0) = (R(3) ? 8 : 0) | R(8);
        U(texs[k], 4) = R(256);
        P(texs[k], 0x1c) = infos[R(3)];
    }
    for (k = 0; k < 4; k++) {
        mats[k] = A(0x68 + 4 * 4);
        for (j = 0; j < 0x1a; j++) U(mats[k], j * 4) = (uint)fx_rnd();
        U(mats[k], 0x60) = 1 + R(4);
        U(mats[k], 0x64) = (int)R(7) - 2;
        for (j = 0; j < 4; j++) P(mats[k], 0x68 + j * 4) = texs[R(6)];
    }
    caps = A(0x20);
    U(caps, 0x10) = R(2); U(caps, 0x14) = R(3) == 0; U(caps, 0x18) = R(3) == 0;
    FXU32(0x80692c) = (uint)caps;
    /* settings */
    FXU32(0x900000) = R(5);                 /* lighting limit */
    FXU32(0x900008) = 2 + R(4);             /* geometry limit */
    for (k = 0; k < 3; k++) FXU32(0x900020 + 4 * k) = R(3) ? 0 : R(2);
    for (k = 0; k < 3; k++) *(float *)FXDATA(0x90002c + 4 * k) = R(3) ? 0.0f : rf(1);
    *(float *)FXDATA(0x900044) = R(3) ? 1.0f : R(3) ? (float)R(8) * 0.125f : rf(2);
    FXU32(0x90004c) = R(3) == 0;
    FXU32(0x900050) = R(5);
    FXU32(0x900064) = R(2) ? 2 : R(4);
    FXU32(0x900534) = R(2) ? 0x10 : 0x18;
    {
        static const uint pcb[3] = {0x000, 0x200, 0x300};
        uint def = 0x007f | pcb[R(3)];
        uint up = 0x007f | pcb[R(3)] | (R(4) << 10);
        *(unsigned short *)FXDATA(0x900524) = def;
        *(unsigned short *)FXDATA(0x90052a) = up;
    }
    *(float *)FXDATA(0x4dda90) = 10.0f; *(float *)FXDATA(0x4dda94) = 20.0f; *(float *)FXDATA(0x4dda98) = 40.0f;
    FXU32(0x806940) = R(4) ? 0x100 : 8 + R(40);   /* batch capacity */
    FXU32(0x68bfa8) = R(4) ? 0 : R(20);
    FXU32(0x60bfa0) = R(4) ? 0 : R(20);
    FXU32(0x6f0fb0) = R(4) ? 0 : R(20);
    for (k = 0x606fa0; k < 0x60bfa0; k += 4) FXU32(k) = (uint)fx_rnd();
    for (k = 0x6cbfb0; k < 0x6d0fb0; k += 4) FXU32(k) = (uint)fx_rnd();
    for (k = 0x6f0fb8; k < 0x6f4fb8; k += 4) FXU32(k) = (uint)fx_rnd();
    /* meshes */
    FXU32(0x8ddfa0) = nmesh;
    for (k = 0; k < nmesh; k++) {
        char *e = (char *)FXDATA(0x8ddfc0 + k * 0x78);
        int nv = R(8) == 0 ? R(3) : 1 + R(14), geo, light, cel, typ;
        char *mat, *tex;
        for (j = 0; j < 0x78 / 4; j++) U(e, j * 4) = (uint)fx_rnd();
        U(e, 4) = R(4);
        U(e, 8) = R(6) == 0 ? (int)R(8) - 1 : 3 + R(2);
        U(e, 0xc) = (int)R(6) - 1;
        U(e, 0x1c) = nv;
        P(e, 0x20) = A(nv * 12 + 4);
        P(e, 0x24) = A(nv * 8 + 4);
        for (j = 0; j < 4; j++) P(e, 0x28 + 4 * j) = A(nv * 4 + 4);
        for (j = 0; j < nv; j++) {
            float *v = (float *)P(e, 0x20) + j * 3;
            v[0] = rf(640); v[1] = rf(480);
            switch (R(8)) {
            case 0: v[2] = 0.0f; break;
            case 1: v[2] = R(2) ? 1.0f : -1.0f; break;
            case 2: v[2] = bitsf(special_bits(R(64))); break;
            default: v[2] = rf(100); break;
            }
            ((float *)P(e, 0x24))[2 * j] = rf(256);
            ((float *)P(e, 0x24))[2 * j + 1] = rf(256);
            for (int a = 0; a < 4; a++) ((float *)P(e, 0x28 + 4 * a))[j] = rlevel();
        }
        mat = R(10) ? mats[R(4)] : 0;
        P(e, 0x38) = mat;
        U(e, 0x3c) = R(3) ? (uint)-1 : (int)R(7) - 2;
        F(e, 0x40) = R(3) ? 0.0f : rlevel();
        F(e, 0x44) = rlevel();
        F(e, 0x48) = R(2) ? 0.0f : rlevel() - 0.5f;
        P(e, 0x4c) = pals[R(3) ? 0 : 1 + R(2)];
        switch (R(6)) {
        case 0: F(e, 0x64) = 10.0f; break;
        case 1: F(e, 0x64) = 20.0f; break;
        case 2: F(e, 0x64) = 40.0f; break;
        case 3: F(e, 0x64) = bitsf(special_bits(R(64))); break;
        default: F(e, 0x64) = (float)R(60); break;
        }
        /* the original's uninitialised stack slots: the first textured mesh gets a type in 1..4, the first mesh that
         * makes vertices does not use geometry 3 + lighting 3 + 0x0090004c */
        if (!mat) continue;
        cel = (int)U(e, 0x3c);
        if (cel == -1) cel = (int)U(mat, 0x64);
        if (cel < 0) cel = 0; else if (cel > (int)U(mat, 0x60) - 1) cel = U(mat, 0x60) - 1;
        tex = P(mat, 0x68 + cel * 4);
        typ = R(8) == 0 ? (R(2) ? 0 : 5) : 1 + R(4);
        if (U(tex, 0) & 8) {
            if (!seen_type && (typ < 1 || typ > 4)) typ = 1 + R(4);
            /* the info is shared: set the type only where it does not undo an earlier choice */
            if (!seen_type) { U(P(tex, 0x1c), 0x18) = typ; locked = P(tex, 0x1c); }
            else if (P(tex, 0x1c) != locked) U(P(tex, 0x1c), 0x18) = typ;
            seen_type = 1;
        }
        geo = (int)U(e, 8); if (geo >= (int)FXU32(0x900008)) geo = FXU32(0x900008);
        light = (int)U(e, 0xc); if (light >= (int)FXU32(0x900000)) light = FXU32(0x900000);
        if (geo == 4 && !(U(tex, 0) & 8)) geo = 3;
        if ((geo == 3 || geo == 4) && nv > 0) {
            if (!seen_vertex && geo == 3 && light == 3 && FXU32(0x90004c) == 1) U(e, 0xc) = 0;
            seen_vertex = 1;
        }
    }
    ens_fail = R(6) == 0 ? (int)fx_rnd() : 0;
    memcpy(ar0, ar, used);
    gsave(g0);
    seed = fx_rnd();
    /* original */
    ss = seed | 1; nlg = 0; nens = 0;
    _controlfp(pcs[i % 3] | _RC_NEAR, _MCW_PC | _MCW_RC);
    ra = orig_rdCache_SendFaceListToHardware();
    cwA = get_cw(); swA = get_sw(); _controlfp(_PC_64 | _RC_NEAR, _MCW_PC | _MCW_RC);
    memcpy(arA, ar, used); gsave(gA); memcpy(lgA, lg, nlg * 4); nlgA = nlg;
    /* C */
    memcpy(ar, ar0, used); gload(g0);
    ss = seed | 1; nlg = 0; nens = 0;
    _controlfp(pcs[i % 3] | _RC_NEAR, _MCW_PC | _MCW_RC);
    rb = rdCache_SendFaceListToHardware();
    cw = get_cw(); sw = get_sw(); _controlfp(_PC_64 | _RC_NEAR, _MCW_PC | _MCW_RC);
    {
        const char *what = 0;
        int kk;
        if (ra != rb) what = "return";
        else if (cw != cwA) what = "control word";
        else if (((sw >> 11) & 7) != ((swA >> 11) & 7)) what = "x87 stack top";
        else if (nlg != nlgA || memcmp(lg, lgA, nlg * 4)) {
            what = "call log";
            if (dbg) {
                printf("  log length orig %d C %d\n", nlgA, nlg);
                for (kk = 0; kk < nlg && kk < nlgA; kk++)
                    if (lg[kk] != lgA[kk]) { printf("  log[%d] orig %08x C %08x (prev %08x)\n", kk, lgA[kk], lg[kk], kk ? lg[kk - 1] : 0); break; }
            }
        }
        if (!what) {
            kk = fkind(ar, arA, used / 4);
            if (kk == 2) what = "mesh data";
            else kind |= kk;
        }
        for (k = 0; (dbg || !what) && k < (int)NREG; k++) {
            kk = fkind(FXDATA(regs[k][0]), gA[k], (regs[k][1] - regs[k][0]) / 4);
            if (kk == 2) { what = "globals"; if (dbg) printf("  region %08x\n", regs[k][0]); }
            else kind |= kk;
        }
        if (what) {
            if (nf++ < 5) printf("DIFF rdCache_SendFaceListToHardware case %ld: %s\n", i, what);
        } else if (kind)
            nnan++;
        if (!ra) nret0++;
        nc++;
    }
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000, i;
    nan_mode = getenv("P3_NAN") ? atoi(getenv("P3_NAN")) : 0;
    dbg = getenv("P3DBG") != 0;
    for (i = 0; i < n; i++) t_case(i);
    printf("%-32s %8ld cases (%ld returned 0), %ld differences, %ld NaN-payload-only\n", "rdCache_SendFaceListToHardware", nc,
           nret0, nf, nnan);
    return nf != 0 || nnan != 0;
}
