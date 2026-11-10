/* Differential test: polygon drawing functions (edges + spans + set-up), on random convex polygons.  The C draw
 * functions call the C edges and spans of build/overrides_asm_o1.c, the original ones the original code; functions
 * that are not converted (rdNRaster_SetupLeftEdgeNGonFS, rdNRaster_CalcAffineGradients, the perspective spans) are the original code on
 * both sides.  The span pointer UINT_007f42f8 holds the address of a C function on the C side: it is mapped back to
 * the original address before the comparison. */
#include <math.h>
#include "harness.h"
#define CAM   0x30000100u
#define CAM4  0x30000200u
#define CANV  0x30000300u
#define POLY  0x30000400u
#define FACE  0x30000500u
#define MAT   0x30000600u
#define THDR  0x30000a00u
#define MIPS  0x30000b00u
#define LOBJ  0x30000c00u
#define VERTS 0x30002000u
#define UVS   0x30003000u
#define LVS   0x30004000u
#define FB    0x30010000u
#define TAB   0x30110000u
#define TEX   0x30210000u
static float rf(float lo, float hi) { return lo + (hi - lo) * (float)(rnd() & 0xffffff) / 16777216.0f; }
static int g_bpp;
static void setup(int *a)
{
    unsigned short base = (rnd() & 1) ? 0x027f : ((rnd() & 1) ? 0x007f : 0x037f);
    *(unsigned short *)0x900524 = base;
    *(unsigned short *)0x90052a = (unsigned short)(0x0b00 | (base & 0xff));
    *(unsigned short *)0x900526 = (unsigned short)(0x0700 | (base & 0xff));
    *(unsigned short *)0x900528 = (unsigned short)(0x0c00 | (base & 0xff));
    G(0x7f0fc8) = CAM; G(CAM + 4) = CAM4; G(CAM4 + 4) = CANV;
    G(CANV + 0x18) = 0x800; G(CANV + 0x24) = g_bpp; G(CANV + 0x5c) = FB;
    for (uint32_t x = 0x7f4200; x < 0x7f4500; x += 4) G(x) = rnd_edge();
    for (uint32_t x = 0x8ddea0; x < 0x8ddf10; x += 4) G(x) = rnd();
    for (int i = 0; i < 0x800; i++) G(0x8fbfc0 + 4 * i) = (int)(0x10000 / (i ? i : 1));
    G(0x8ddee4) = rnd() & 3; G(0x8ddea8) = TAB + rndn(0x1000); G(0x8ddebc) = TAB + 0x20000; G(0x8dded4) = TAB + 0x50000;
    G(0x8ddeb0) = TAB + 0x60000; G(0x7f4300) = TEX + 0x80000; G(0x7f43a8) = FB;
    G(0x4f5ec4) = LOBJ; G(LOBJ + 0x338) = TAB + 0x70000 + rndn(0x100);
    G(0x7f42f8) = 0x45ff00;
    /* material and texture */
    G(MAT + 0x330) = TAB + 0x60000 + rndn(0x100); G(MAT + 0x348) = TAB + 0x20000 + 2 * rndn(0x100); G(MAT + 0x34c) = TAB + 0x50000 + rndn(0x100);
    int lw = 3 + rndn(6), lh = 3 + rndn(6);
    G(THDR + 0xc) = lw; G(THDR + 0x10) = (1 << lw) - 1; G(THDR + 0x14) = (1 << lh) - 1; G(THDR + 0x18) = 1 + rndn(4);
    for (int m = 0; m < 4; m++) { G(THDR + 0x1c + 4 * m) = MIPS + 0x60 * m; G(MIPS + 0x60 * m + 0x18) = (1 << lw) >> m; G(MIPS + 0x60 * m + 0x5c) = TEX + 0x10000 * m; }
    G(FACE + 4) = rndn(256); G(FACE + 0x1c) = THDR;
    /* convex polygon, vertices in order around the centre */
    int n = 3 + rndn(5);
    float cx = rf(120, 520), cy = rf(110, 370), rx = rf(1, 110), ry = rf(1, 100), ang[8];
    for (int i = 0; i < n; i++) ang[i] = rf(0, 6.2831853f);
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (ang[j] < ang[i]) { float t = ang[i]; ang[i] = ang[j]; ang[j] = t; }
    int top = 0, bot = 0;
    for (int i = 0; i < n; i++) {
        GF(VERTS + 12 * i) = cx + rx * cosf(ang[i]); GF(VERTS + 12 * i + 4) = cy + ry * sinf(ang[i]); GF(VERTS + 12 * i + 8) = rf(1, 50);
        GF(UVS + 8 * i) = rf(0, 64); GF(UVS + 8 * i + 4) = rf(0, 64); GF(LVS + 4 * i) = rf(0, 63);
        GF(0x7f43c8 + 4 * i) = rf(0.02f, 1); GF(0x7f4260 + 4 * i) = rf(0, 3); GF(0x7f4310 + 4 * i) = rf(0, 3);
        if (GF(VERTS + 12 * i + 4) < GF(VERTS + 12 * top + 4)) top = i;
        if (GF(VERTS + 12 * i + 4) > GF(VERTS + 12 * bot + 4)) bot = i;
    }
    G(POLY + 0x1c) = n; G(POLY + 0x20) = VERTS; G(POLY + 0x24) = UVS; G(POLY + 0x28) = LVS; G(POLY + 0x4c) = MAT;
    G(POLY + 0x50) = rnd() & 1; GF(POLY + 0x64) = rf(0.5f, 4); G(POLY + 0x6c) = top; G(POLY + 0x70) = bot;
    float lvl = rf(0, 63);
    a[0] = POLY; a[1] = FACE; a[2] = *(int *)&lvl;
}
#define F(n, addr) extern void n(void);
#include "draw_list.h"
#undef F
#define F(n, addr) {#n, addr, (void *)n, setup, 0},
static const Fn fns[] = {
#include "draw_list.h"
};
/* C addresses of span functions that a draw function may store in UINT_007f42f8, and their 1.01 addresses */
extern void rdNRaster_DrawScanLineNGonLAT_16(void), rdNRaster_DrawScanLineNGonFAT_16(void), rdNRaster_DrawScanLineNGonGAT_16(void);
static const struct { void *c; uint32_t o; } ptrmap[] = {
    {rdNRaster_DrawScanLineNGonLAT_16, 0x41b880}, {rdNRaster_DrawScanLineNGonFAT_16, 0x41d560}, {rdNRaster_DrawScanLineNGonGAT_16, 0x41f2f0},
};
void harness_fixup(void)
{
    for (unsigned i = 0; i < sizeof ptrmap / sizeof ptrmap[0]; i++)
        if (G(0x7f42f8) == (int32_t)(uintptr_t)ptrmap[i].c) G(0x7f42f8) = ptrmap[i].o;
}
int main(int argc, char **argv)
{
    rt_init();
    for (uint32_t i = 0; i < ARENA_SZ; i += 4) G(0x30000000 + i) = rnd();
    long n = argc > 1 ? atol(argv[1]) : 300;
    int r = 0;
    g_bpp = 8; printf("-- 8 bit\n"); r |= run_all(fns, sizeof fns / sizeof fns[0], n, argc > 2 ? argv[2] : 0);
    g_bpp = 16; printf("-- 16 bit\n"); r |= run_all(fns, sizeof fns / sizeof fns[0], n, argc > 2 ? argv[2] : 0);
    return r;
}
