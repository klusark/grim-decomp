/* Differential test of the span routines of build/overrides_asm_o2.c (rdRaster_Span16_TexLitZw_15 .. _22, _24 .. _30)
 * against the original machine code: random spans (edges with fractional x, z, u, v, row), random z buffer contents,
 * texture, palette, reciprocal tables, scale shift and rounding control words; the color surface, the z buffer and
 * the span state globals (0x007f4c40 .. 0x007f4d00) are compared, under the x87 precision controls 24, 53 and 64 bits.
 * Build: build/difftest/asm_s5/build.sh build/difftest/asm_s5/span_test.c build/difftest/asm_s5/out/span_test.exe \
 *   rdRaster_Span16_TexLitZw_15 ... (the names in NAMES below) */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "fx.h"

typedef void (*SpanFn)(unsigned *, unsigned *);
#define DECL(n) extern void orig_rdRaster_Span16_TexLitZw##n(unsigned *, unsigned *), rdRaster_Span16_TexLitZw##n(unsigned *, unsigned *);
DECL() DECL(_2) DECL(_3) DECL(_4) DECL(_5) DECL(_6) DECL(_7) DECL(_8) DECL(_15) DECL(_16) DECL(_17) DECL(_18) DECL(_19) DECL(_20) DECL(_21) DECL(_22) DECL(_24) DECL(_25) DECL(_26) DECL(_27) DECL(_28) DECL(_29) DECL(_30)
#define P(n) {orig_rdRaster_Span16_TexLitZw##n, rdRaster_Span16_TexLitZw##n, #n}
static struct { SpanFn o, m; const char *n; } fns[] = {P(), P(_2), P(_3), P(_4), P(_5), P(_6), P(_7), P(_8), P(_15), P(_16), P(_17), P(_18), P(_19), P(_20), P(_21), P(_22), P(_24), P(_25), P(_26), P(_27), P(_28), P(_29), P(_30)};
#define NFN ((int)(sizeof fns / sizeof fns[0]))
static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }

#define W 640
#define H 8
static unsigned short color[W * H + 64], zbuf[W * H + 64];
static unsigned char tex[0x10000 + 0x100];
static unsigned short palbuf[0x4400], *pal = palbuf + 0x200;
static int surf_c[0x20], surf_z[0x20], canvas_inner[8], canvas[4];
static unsigned left[0x11], right[0x11];

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000, i;
    unsigned pcs[3] = {_PC_24, _PC_53, _PC_64};
    unsigned short cws[5] = {0x027f, 0x0e7f, 0x0f7f, 0x067f, 0x0a7f};
    for (int k = 0; k < 2064; k++) {
        ((int *)FXDATA(0x8fbfc0))[k] = k ? 0x10000 / k : 0;
        ((float *)FXDATA(0x8fe000))[k] = k ? 1.0f / k : 0;
    }
    for (int k = 0; k < (int)sizeof tex; k++) tex[k] = (unsigned char)fx_rnd();
    for (int k = 0; k < 0x4400; k++) palbuf[k] = (unsigned short)fx_rnd();
    surf_c[0x18 / 4] = W * 2; surf_c[0x5c / 4] = (int)(uintptr_t)color;
    surf_z[0x18 / 4] = W * 2; surf_z[0x5c / 4] = (int)(uintptr_t)zbuf;
    canvas_inner[1] = (int)(uintptr_t)surf_c; canvas_inner[4] = (int)(uintptr_t)surf_z;
    canvas[1] = (int)(uintptr_t)canvas_inner;
    FXU32(0x7f0fc8) = (unsigned)(uintptr_t)canvas;
    FXU32(0x8dde7c) = (unsigned)(uintptr_t)tex;
    FXU32(0x8dde5c) = (unsigned)(uintptr_t)pal;
    fx_region(color, sizeof color); fx_region(zbuf, sizeof zbuf);
    fx_region(FXDATA(0x7f4c40), 0xc0);
    for (i = 0; i < n; i++) {
        int f = i % NFN, shift = R(5), w = 1 + R(8);
        int x0 = (int)R(W << 16), len = R(4) ? (int)R(64 << 16) : (int)R(W << 16) - (int)R(0x30000);
        unsigned pc = pcs[R(3)];
        int y = R(H);
        if (x0 + len > (W << 16) - 0x20000) len = (W << 16) - 0x20000 - x0;
        if (R(10) == 0) len = -(int)R(0x30000);
        if (x0 + len < 0) len = -x0;    /* a negative right edge gives a huge count (shr) in both: not tested */
        memset(left, 0, sizeof left); memset(right, 0, sizeof right);
        left[0] = (unsigned)x0; right[0] = (unsigned)(x0 + len);
        if (R(8) == 0) { left[0] &= 0xffff0000; }
        { float z0 = (float)(fx_rnd() % 1000000) / 1000000.0f, z1 = (float)(fx_rnd() % 1000000) / 1000000.0f;
          memcpy(&left[4], &z0, 4); memcpy(&right[4], &z1, 4); }
        left[0x28 / 4] = (unsigned)((int)R(0x4000000) - 0x2000000) << shift >> 0; right[0x28 / 4] = (unsigned)((int)R(0x4000000) - 0x2000000);
        left[0x30 / 4] = (unsigned)((int)R(0x4000000) - 0x2000000); right[0x30 / 4] = (unsigned)((int)R(0x4000000) - 0x2000000);
        left[0x40 / 4] = (unsigned)y;
        left[0x38 / 4] = 0x10000 + R(0x3d0000); right[0x38 / 4] = R(3) ? 0x10000 + R(0x3d0000) : left[0x38 / 4] - R(0x600);
        FXU32(0x8dde54) = (unsigned)shift;
        FXU32(0x8dde78) = (unsigned)fx_rnd() & 0xffffff; FXU32(0x8dde50) = (unsigned)fx_rnd() & 0xffffff;
        FXU32(0x8dde58) = R(2) ? 0xff00 : (R(256) << 8) | R(4);
        FXU32(0x8dde8c) = (unsigned)w; FXU32(0x8dde48) = ((1u << w) - 1) << 16;
        *(unsigned short *)FXDATA(0x900526) = cws[R(5)]; *(unsigned short *)FXDATA(0x900524) = cws[R(5)];
        for (int k = 0; k < W * H; k++) { zbuf[k] = (unsigned short)(R(3) ? R(0x10000) : 0); color[k] = (unsigned short)k; }
        for (unsigned k = 0x7f4c40; k < 0x7f4d00; k += 4) FXU32(k) = (unsigned)fx_rnd();
        fx_save();
        _controlfp(pc, _MCW_PC);
        fns[f].o(left, right);
        _controlfp(_PC_64 | _RC_NEAR, _MCW_PC | _MCW_RC);
        fx_snap_a(); fx_restore();
        _controlfp(pc, _MCW_PC);
        fns[f].m(left, right);
        _controlfp(_PC_64 | _RC_NEAR, _MCW_PC | _MCW_RC);
        if (fx_cmp_a()) { fx_fail("span", i); if (fx_fails < 4) printf("  fn %s\n", fns[f].n); }
        fx_cases++;
    }
    printf("span_test: %ld cases, %ld differences\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
