/* Readable C for assembled functions of GRIMFANDANGO.EXE, round 6, lower half of the remaining list (agent asm_p1).
 *
 * Each function below replaces the assembled original at the address given in its comment.  The C was written
 * against the 1.01 machine code (src/GRIMFANDANGO.EXE/asm_funcs.s, raw/GRIMFANDANGO.EXE/sections/text.bin) and checked
 * with a differential test that runs the original bytes next to this C on the same memory
 * (build/difftest/asm_p1/, docs/notes/asm_p1.md).
 */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

#define P1_I32(a)  (*(int *)(a))
#define P1_U32(a)  (*(uint *)(a))
#define P1_U8(a)   (*(uint8_t *)(a))
#define P1_U16(a)  (*(uint16_t *)(a))
#define P1_F(a)    (*(float *)(a))

/* frame buffer descriptor of the current camera: g_pRdCurrentCamera->+4->+4 (+0x18 pitch, +0x24 bpp, +0x5c pixels) */
#define P1_CANVAS()   P1_I32(P1_I32((int)g_pRdCurrentCamera + 4) + 4)
#define P1_BPP()      P1_I32(P1_CANVAS() + 0x24)
/* g_pRdCurrentCamera->+4->+0x14: non-zero selects the second z-write span */
#define P1_ZMODE()    P1_I32(P1_I32((int)g_pRdCurrentCamera + 4) + 0x14)

/* ------------------------------------------------------------------------------------------------------------------
 * Polygon span drivers of the software rasteriser (the +0x1b4 callback that the rdRaster_Select_* functions store).
 * param_1 is the polygon record built by the selector; +0x1b8 is the list of span records (linked by +0x28).  Each
 * driver copies the per-polygon interpolants of the record into the rasteriser globals, picks the span routine for
 * the canvas depth and the texture size (+0x1cc: 8, 0x10, 0x20, 0x40, 0x80, 0x100 or anything else), runs it on
 * every span, and then runs the z-write span on every span.  At 8 bpp the textured span routine is Mem_DumpLog (an
 * empty function in 1.01: the 8 bit textured rasteriser is not implemented). */

/* the z-write pass that ends every driver */
static void p1_span_zwrite(int span)
{
    if (P1_ZMODE() == 0) {
        for (; span != 0; span = P1_I32(span + 0x28))
            rdRaster_SpanR_FlatZw((int *)span);
    }
    else {
        for (; span != 0; span = P1_I32(span + 0x28))
            rdRaster_SpanR_FlatZw_2((int *)span);
    }
}

/* run the selected span routine (UINT_007f3214) on every span, then the z-write pass */
static void p1_span_run(int param_1)
{
    int span;

    for (span = P1_I32(param_1 + 0x1b8); span != 0; span = P1_I32(span + 0x28))
        ((void (*)(int))UINT_007f3214)(span);
    p1_span_zwrite(P1_I32(param_1 + 0x1b8));
}

/* the span routine for a texture size: tab[0] for 8, [1] 0x10, [2] 0x20, [3] 0x40, [4] 0x80, [5] 0x100,
 * [6] anything else */
static void p1_span_pick(int bpp, int size, void *const *tab16)
{
    void *fn;

    if (bpp == 8) {
        UINT_007f3214 = (int)Mem_DumpLog;
        return;
    }
    if (bpp != 0x10)
        return;
    switch (size) {
    case 0x8:   fn = tab16[0]; break;
    case 0x10:  fn = tab16[1]; break;
    case 0x20:  fn = tab16[2]; break;
    case 0x40:  fn = tab16[3]; break;
    case 0x80:  fn = tab16[4]; break;
    case 0x100: fn = tab16[5]; break;
    default:    fn = tab16[6]; break;
    }
    UINT_007f3214 = (int)fn;
}

/* the interpolants that every textured driver copies */
static void p1_copy_tex(int param_1)
{
    UINT_008ddf04 = P1_U32(param_1 + 0x1c0);
    UINT_008ddf3c = P1_U32(param_1 + 0x1c4);
    UINT_008ddf10 = P1_U32(param_1 + 0x1c8);
    _DAT_008ddf34 = P1_U32(param_1 + 0x1cc);
    UINT_008ddf4c = P1_U32(param_1 + 0x1d4);
    UINT_008ddf14 = P1_U32(param_1 + 0x1d8);
    UINT_008ddf24 = P1_U32(param_1 + 0x19c);
    UINT_008ddf44 = P1_U32(param_1 + 0x1a0);
    UINT_008ddf18 = P1_U32(param_1 + 0x1a4);
}

/* the perspective terms of the P16 drivers */
static void p1_copy_persp(int param_1)
{
    _DAT_008ddf28 = P1_U32(param_1 + 0x1a8);
    _DAT_008ddf2c = P1_U32(param_1 + 0x1ac);
    _DAT_008ddf48 = P1_U32(param_1 + 0x1b0);
    _DAT_008ddf1c = P1_U32(param_1 + 0x184);
    _DAT_008ddf20 = P1_U32(param_1 + 0x18c);
    _DAT_008ddf38 = P1_U32(param_1 + 0x194);
}

/* the light-table pointer: +0x1dc at 8 bpp (UINT_008ddf0c), +0x1e0 at 16 bpp (UINT_008ddf30) */
static void p1_copy_light(int param_1, int bpp, int with8)
{
    if (with8 && bpp == 8)
        UINT_008ddf0c = P1_U32(param_1 + 0x1dc);
    else if (bpp == 0x10)
        UINT_008ddf30 = P1_U32(param_1 + 0x1e0);
}

/* OVERRIDES: FUN_00410330 */
/* ==== FUN_00410330 (0x00410330) ====
 * Span driver of rdRaster_Select_FlatLit: Gouraud-lit flat colour.  The colour index (+0x1d0, a byte) goes to
 * DAT_008ddf40; every span writes its +0x04 pixels from x +0x00, row +0x08, the light value (+0x20, step +0x24) picking
 * the level of the light table: at 8 bpp the byte table +0x1dc[((l >> 8) & 0x3f00) + colour], at 16 bpp the word
 * table +0x1e0[((l >> 16) & 0x3f) * 0x100 + colour]. */
void FUN_00410330(int param_1)
{
    int bpp = P1_BPP();
    int span, n, l, dl, cv;

    DAT_008ddf40 = P1_U8(param_1 + 0x1d0);
    p1_copy_light(param_1, bpp, 1);
    UINT_008ddf24 = P1_U32(param_1 + 0x19c);
    if (bpp == 8) {
        for (span = P1_I32(param_1 + 0x1b8); span != 0; span = P1_I32(span + 0x28)) {
            uint8_t *dst;
            dl = P1_I32(span + 0x24);
            l = P1_I32(span + 0x20);
            cv = P1_CANVAS();
            dst = (uint8_t *)(P1_I32(span + 8) * P1_I32(cv + 0x18) + P1_I32(cv + 0x5c) + P1_I32(span));
            for (n = P1_I32(span + 4); n != 0; n--) {
                uint idx = ((uint)(l >> 8) & 0x3f00) + UINT_008ddf0c;
                l += dl;
                *dst++ = P1_U8(idx + (uint)DAT_008ddf40);
            }
        }
    }
    else if (bpp == 0x10) {
        for (span = P1_I32(param_1 + 0x1b8); span != 0; span = P1_I32(span + 0x28)) {
            uint16_t *dst;
            dl = P1_I32(span + 0x24);
            l = P1_I32(span + 0x20);
            cv = P1_CANVAS();
            dst = (uint16_t *)(P1_I32(cv + 0x5c) +
                               (P1_I32(span + 8) * (int)(P1_U32(cv + 0x18) >> 1) + P1_I32(span)) * 2);
            for (n = P1_I32(span + 4); n != 0; n--) {
                uint idx = (((uint)(l >> 16) & 0x3f) << 8) + (uint)DAT_008ddf40;
                l += dl;
                *dst++ = P1_U16(UINT_008ddf30 + idx * 2);
            }
        }
    }
    p1_span_zwrite(P1_I32(param_1 + 0x1b8));
}

/* OVERRIDES: FUN_00410970 */
/* ==== FUN_00410970 (0x00410970) ==== span driver of rdRaster_Select_FlatLit_2 (affine textured, rdRaster_SpanR16_Tex*) */
void FUN_00410970(int param_1)
{
    static void *const tab[7] = {
        (void *)rdRaster_SpanR16_Tex_2, (void *)rdRaster_SpanR16_Tex_3, (void *)rdRaster_SpanR16_Tex_4,
        (void *)rdRaster_SpanR16_TexLit, (void *)rdRaster_SpanR16_Tex_5, (void *)rdRaster_SpanR16_Tex_6,
        (void *)rdRaster_SpanR16_Tex};
    int bpp = P1_BPP();

    p1_copy_light(param_1, bpp, 0);
    p1_copy_tex(param_1);
    p1_span_pick(bpp, _DAT_008ddf34, tab);
    p1_span_run(param_1);
}

/* OVERRIDES: FUN_00411740 */
/* ==== FUN_00411740 (0x00411740) ==== span driver (affine textured and lit, rdRaster_SpanR16_Tex_7 .. _12) */
void FUN_00411740(int param_1)
{
    static void *const tab[7] = {
        (void *)rdRaster_SpanR16_Tex_8, (void *)rdRaster_SpanR16_Tex_9, (void *)rdRaster_SpanR16_Tex_10,
        (void *)rdRaster_SpanR16_TexLit_2, (void *)rdRaster_SpanR16_Tex_11, (void *)rdRaster_SpanR16_Tex_12,
        (void *)rdRaster_SpanR16_Tex_7};
    int bpp = P1_BPP();

    p1_copy_light(param_1, bpp, 1);
    p1_copy_tex(param_1);
    p1_span_pick(bpp, _DAT_008ddf34, tab);
    p1_span_run(param_1);
}

/* OVERRIDES: FUN_004125c0 */
/* ==== FUN_004125c0 (0x004125c0) ==== span driver of rdRaster_Select_FlatLit_6 (rdRaster_SpanR16_TexLit_3 .. _9) */
void FUN_004125c0(int param_1)
{
    static void *const tab[7] = {
        (void *)rdRaster_SpanR16_TexLit_4, (void *)rdRaster_SpanR16_TexLit_5, (void *)rdRaster_SpanR16_TexLit_6,
        (void *)rdRaster_SpanR16_TexLit_7, (void *)rdRaster_SpanR16_TexLit_8, (void *)rdRaster_SpanR16_TexLit_9,
        (void *)rdRaster_SpanR16_TexLit_3};
    int bpp = P1_BPP();

    p1_copy_light(param_1, bpp, 1);
    p1_copy_tex(param_1);
    p1_span_pick(bpp, _DAT_008ddf34, tab);
    p1_span_run(param_1);
}

/* OVERRIDES: FUN_00413590 */
/* ==== FUN_00413590 (0x00413590) ==== perspective span driver (rdRaster_SpanP16_Tex .. _6) */
void FUN_00413590(int param_1)
{
    static void *const tab[7] = {
        (void *)rdRaster_SpanP16_Tex_2, (void *)rdRaster_SpanP16_Tex_3, (void *)rdRaster_SpanP16_Tex_4,
        (void *)rdRaster_SpanP16_TexLit, (void *)rdRaster_SpanP16_Tex_5, (void *)rdRaster_SpanP16_Tex_6,
        (void *)rdRaster_SpanP16_Tex};
    int bpp = P1_BPP();

    p1_copy_light(param_1, bpp, 0);
    p1_copy_tex(param_1);
    p1_copy_persp(param_1);
    p1_span_pick(bpp, _DAT_008ddf34, tab);
    p1_span_run(param_1);
}

/* OVERRIDES: FUN_00414d20 */
/* ==== FUN_00414d20 (0x00414d20) ==== perspective span driver (rdRaster_SpanP16_Tex_7 .. _12) */
void FUN_00414d20(int param_1)
{
    static void *const tab[7] = {
        (void *)rdRaster_SpanP16_Tex_8, (void *)rdRaster_SpanP16_Tex_9, (void *)rdRaster_SpanP16_Tex_10,
        (void *)rdRaster_SpanP16_TexLit_2, (void *)rdRaster_SpanP16_Tex_11, (void *)rdRaster_SpanP16_Tex_12,
        (void *)rdRaster_SpanP16_Tex_7};
    int bpp = P1_BPP();

    p1_copy_light(param_1, bpp, 1);
    p1_copy_tex(param_1);
    p1_copy_persp(param_1);
    p1_span_pick(bpp, _DAT_008ddf34, tab);
    p1_span_run(param_1);
}

/* OVERRIDES: FUN_00416580 */
/* ==== FUN_00416580 (0x00416580) ==== perspective lit span driver (rdRaster_SpanP16_TexLit_3 .. _9) */
void FUN_00416580(int param_1)
{
    static void *const tab[7] = {
        (void *)rdRaster_SpanP16_TexLit_4, (void *)rdRaster_SpanP16_TexLit_5, (void *)rdRaster_SpanP16_TexLit_6,
        (void *)rdRaster_SpanP16_TexLit_7, (void *)rdRaster_SpanP16_TexLit_8, (void *)rdRaster_SpanP16_TexLit_9,
        (void *)rdRaster_SpanP16_TexLit_3};
    int bpp = P1_BPP();

    p1_copy_light(param_1, bpp, 1);
    p1_copy_tex(param_1);
    p1_copy_persp(param_1);
    p1_span_pick(bpp, _DAT_008ddf34, tab);
    p1_span_run(param_1);
}

/* ------------------------------------------------------------------------------------------------------------------
 * rdCanvas: the scanline span builder of the software canvas.
 *
 * Edge-list records (linked by +0x50, from UINT_004f6f20 to the sentinel DAT_005e6f40): +0x00 non-zero for a leading
 * edge, +0x04 the polygon record, +0x10 z at the crossing (float), +0x28 x (16.16).  Polygon records: +0x000 the
 * material / mode record (+0x08 geometry mode, +0x0c light mode, +0x10 texture mode, +0x74 sort key: low half must
 * match, high half orders), +0x184 dz/dx (float), +0x18c / +0x194 du/dx, dv/dx (float), +0x19c dz/dx * 65536 (int),
 * +0x1b8 / +0x1bc span list head / tail, +0x1c0 texture shift, +0x1d0 flat colour, +0x1ec / +0x1f0 left / right edge
 * (+0x10 z, +0x18 u, +0x20 v (floats), +0x28 x, +0x30 u, +0x38 v, +0x40 light (16.16)), +0x1f4 x where the polygon
 * became the front one, +0x1f8 crossing count, +0x1fc / +0x200 previous / next in the active list.
 * Span records (0x2c bytes, DAT_004f6f30[UINT_004f6f2c], flushed by rdCanvas_FlushSpans at 0x800): +0x00 x, +0x04
 * count, +0x08 row (UINT_0050cf30), +0x0c / +0x10 u, du (or the colour, or float u / v), +0x14 / +0x18 v, dv,
 * +0x1c z (float), +0x20 / +0x24 light, dlight, +0x28 next. */

/* 16.16 x rounded up to a whole pixel */
static inline uint p1_ceil16(uint x)
{
    if (x & 0xffff)
        x = (x + 0x10000) & 0xffff0000u;
    return x;
}

/* 16.16 product: imul to EDX:EAX, shrd by 16 */
#define P1_FMUL(a, b)  ((int)(((long long)(int)(a) * (long long)(int)(b)) >> 16))

/* fldcw [DAT_00900526]; fld x; fistp; fldcw [DAT_00900524] */
static inline int p1_fistp_cw(float x)
{
    int r;
    __asm__ volatile("fldcw %2\n\tflds %1\n\tfistpl %0\n\tfldcw %3"
                     : "=m"(r) : "m"(x), "m"(DAT_00900526), "m"(DAT_00900524));
    return r;
}

/* does polygon e (sort key key) go in front of polygon p at the crossing cur?  Keys with the same low half compare
 * their high halves; otherwise (or when equal) the z of p's left edge at the crossing is compared with the crossing's
 * z in extended precision, and a tie (or NaN) goes to the larger dz/dx. */
static int p1_canvas_before(int cur, int e, int p, uint key)
{
    uint pk = P1_U32(P1_I32(p) + 0x74);
    long double x, z;
    int l;

    if (((pk ^ key) & 0xffff) == 0) {
        if ((key >> 16) > (pk >> 16))
            return 1;
        if ((key >> 16) < (pk >> 16))
            return 0;
    }
    l = P1_I32(p + 0x1ec);
    z = P1_F(cur + 0x10);
    x = (long double)(P1_I32(cur + 0x28) - P1_I32(l + 0x28)) * (long double)1.5258789e-05f * P1_F(p + 0x184) +
        P1_F(l + 0x10);
    if (z > x)
        return 1;
    if (z < x)
        return 0;
    return P1_F(e + 0x184) > P1_F(p + 0x184);
}

/* closes the span of polygon p that ends at x (the original has this code twice, inline) */
static void p1_canvas_emit(int p, uint x)
{
    int count = (int)(x - P1_U32(p + 0x1f4)) >> 16;
    int rec, l, r, w, d, poly, sh;
    uint n;
    volatile float t;

    if (count <= 0)
        return;
    n = UINT_004f6f2c;
    if (n >= 0x800) {
        rdCanvas_FlushSpans();
        n = UINT_004f6f2c;
    }
    UINT_004f6f2c = n + 1;
    rec = (int)&DAT_004f6f30 + n * 0x2c;
    P1_I32(rec) = P1_I32(p + 0x1f4) >> 16;
    P1_I32(rec + 4) = count;
    P1_U32(rec + 8) = UINT_0050cf30;
    P1_I32(rec + 0x28) = 0;
    l = P1_I32(p + 0x1ec);
    r = P1_I32(p + 0x1f0);
    w = (int)((p1_ceil16(P1_U32(r + 0x28)) - p1_ceil16(P1_U32(l + 0x28))) >> 16);
    d = P1_I32(p + 0x1f4) - P1_I32(l + 0x28);
    t = (float)((long double)d * (long double)1.5258789e-05f);
    P1_F(rec + 0x1c) = (float)((long double)P1_F(p + 0x184) * t + P1_F(l + 0x10));
    poly = P1_I32(p);
    if (P1_I32(poly + 8) != 4) {
        P1_U32(rec + 0xc) = P1_U32(p + 0x1d0);
    }
    else if (P1_I32(poly + 0x10) == 0) {
        int inv = (&_DAT_008fbfc0)[w];
        int s;
        sh = P1_I32(p + 0x1c0) & 31;
        s = P1_FMUL(P1_I32(r + 0x30) - P1_I32(l + 0x30), inv);
        P1_I32(rec + 0x10) = s >> sh;
        P1_I32(rec + 0xc) = (P1_I32(l + 0x30) + P1_FMUL(d, s)) >> sh;
        sh = P1_I32(p + 0x1c0) & 31;
        s = P1_FMUL(P1_I32(r + 0x38) - P1_I32(l + 0x38), inv);
        P1_I32(rec + 0x18) = s >> sh;
        P1_I32(rec + 0x14) = (P1_I32(l + 0x38) + P1_FMUL(d, s)) >> sh;
    }
    else if (P1_I32(poly + 0x10) == 1) {
        P1_F(rec + 0xc) = (float)((long double)P1_F(p + 0x18c) * t + P1_F(l + 0x18));
        P1_F(rec + 0x10) = (float)((long double)P1_F(p + 0x194) * t + P1_F(l + 0x20));
    }
    if (P1_I32(P1_I32(p) + 0xc) == 3) {
        int s = P1_FMUL(P1_I32(r + 0x40) - P1_I32(l + 0x40), (&_DAT_008fbfc0)[w]);
        P1_I32(rec + 0x24) = s;
        if (s < 0 && s > -0x51e)
            P1_I32(rec + 0x24) = 0;
        P1_I32(rec + 0x20) = P1_I32(l + 0x40) + P1_FMUL(d, P1_I32(rec + 0x24));
    }
    if (P1_I32(p + 0x1b8) != 0)
        P1_I32(P1_I32(p + 0x1bc) + 0x28) = rec;
    else
        P1_I32(p + 0x1b8) = rec;
    P1_I32(p + 0x1bc) = rec;
}

/* OVERRIDES: rdCanvas_EmitSpans */
/* ==== rdCanvas_EmitSpans (0x00404e00) ====
 * Walks the edge crossings of one scanline from left to right and keeps the list of polygons covering the current
 * x, front polygon first.  A leading edge whose polygon becomes covered computes the polygon's dz/dx (float +0x184
 * and, rounded through the DAT_00900526 control word, +0x19c) unless it is a perspective-textured polygon, then is
 * sorted into the list; becoming the front polygon closes the previous front polygon's span.  A trailing edge whose
 * polygon is no longer covered closes its span if it was the front one (the next one becomes the front from here),
 * or unlinks it. */
void rdCanvas_EmitSpans(void)
{
    int act = 0;
    int cur;

    if (UINT_005e6f38 == 0)
        return;
    for (cur = (int)UINT_004f6f20; cur != (int)&DAT_005e6f40; cur = P1_I32(cur + 0x50)) {
        int e = P1_I32(cur + 4);

        if (P1_I32(cur) != 0) {
            int poly;
            uint key, x;

            P1_I32(e + 0x1f8) = P1_I32(e + 0x1f8) + 1;
            if (P1_I32(e + 0x1f8) != 1)
                continue;
            poly = P1_I32(e);
            if (P1_I32(poly + 8) != 4 || P1_I32(poly + 0x10) != 1) {
                uint xr = p1_ceil16(P1_U32(P1_I32(e + 0x1f0) + 0x28));
                uint xl = p1_ceil16(P1_U32(P1_I32(e + 0x1ec) + 0x28));
                long double s = ((long double)P1_F(P1_I32(e + 0x1f0) + 0x10) - P1_F(P1_I32(e + 0x1ec) + 0x10)) *
                                ((float *)&UINT_008fe000)[(xr - xl) >> 16];   /* 1 / width table */
                volatile float s16;
                P1_F(e + 0x184) = (float)s;
                s16 = (float)(s * 65536.0L);
                P1_I32(e + 0x19c) = p1_fistp_cw(s16);
            }
            if (act == 0) {
                P1_I32(e + 0x1fc) = 0;
                P1_I32(e + 0x200) = 0;
                act = e;
                P1_U32(e + 0x1f4) = p1_ceil16(P1_U32(cur + 0x28));
                continue;
            }
            key = P1_U32(P1_I32(e) + 0x74);
            if (p1_canvas_before(cur, e, act, key)) {
                x = p1_ceil16(P1_U32(cur + 0x28));
                p1_canvas_emit(act, x);
                P1_I32(e + 0x200) = act;
                P1_I32(act + 0x1fc) = e;
                P1_I32(e + 0x1fc) = 0;
                act = e;
                P1_U32(e + 0x1f4) = x;
            }
            else {
                int prev = act, cand = P1_I32(act + 0x200);

                while (cand != 0 && !p1_canvas_before(cur, e, cand, key)) {
                    prev = cand;
                    cand = P1_I32(cand + 0x200);
                }
                if (cand != 0) {
                    P1_I32(e + 0x1fc) = prev;
                    P1_I32(prev + 0x200) = e;
                    P1_I32(cand + 0x1fc) = e;
                    P1_I32(e + 0x200) = cand;
                }
                else {
                    P1_I32(prev + 0x200) = e;
                    P1_I32(e + 0x1fc) = prev;
                    P1_I32(e + 0x200) = 0;
                }
            }
        }
        else {
            P1_I32(e + 0x1f8) = P1_I32(e + 0x1f8) - 1;
            if (P1_I32(e + 0x1f8) != 0)
                continue;
            if (e == act) {
                uint x = p1_ceil16(P1_U32(cur + 0x28));
                p1_canvas_emit(act, x);
                act = P1_I32(act + 0x200);
                if (act != 0) {
                    P1_U32(act + 0x1f4) = x;
                    P1_I32(act + 0x1fc) = 0;
                }
            }
            else {
                if (P1_I32(e + 0x200) != 0)
                    P1_I32(P1_I32(e + 0x200) + 0x1fc) = P1_I32(e + 0x1fc);
                if (P1_I32(e + 0x1fc) != 0)
                    P1_I32(P1_I32(e + 0x1fc) + 0x200) = P1_I32(e + 0x200);
            }
        }
    }
}

static float p1_light_level(long double s, float sf, float amb);

/* hands a prepared polygon to its renderer: the face's own callback (+0x18) when face bit 0 is set, else (only with
 * the z-buffer mode 1) the rasteriser selector; level is passed as its raw dword when lit */
static void p1_prep_draw(int face, int poly, int cel, void *sel, int lit, uint level)
{
    if (P1_U8(face) & 1)
        ((void (*)(int, int, uint))P1_I32(face + 0x18))(poly, cel, lit ? level : 0);
    else if (g_nRdroidZBufferMode == 1) {
        if (lit)
            ((void (*)(int, int, uint))sel)(poly, cel, level);
        else
            ((void (*)(int, int))sel)(poly, cel);
    }
}

/* OVERRIDES: rdCanvas_PreparePolygon */
/* ==== rdCanvas_PreparePolygon (0x00405770) ====
 * Takes the next polygon record of the canvas (UINT_00565f38 + UINT_005e6f3c * 0x204, at most 0x400; returns 0 when
 * full or when the geometry mode is 0), clears its span list and edges, and picks the rasteriser selector by the
 * clamped modes of the face (geometry +0x08, lighting +0x0c, texture +0x10; the cel and the ambient floor as in
 * rdModel_ComputeMeshLighting).  Geometry 2 is flat (lighting 0..4); 3 is untextured; 4 is textured, with the
 * selector set by the cel's colour-key flag (cel +0x1c -> bit 0) and the texture mode (0, or 1..2).  For each of these
 * the lighting mode picks: 0 the unlit selector, 1 / 2 the lit selector with the level of +0x48 (+ +0x44), stored in
 * +0x44, 3 the per-vertex levels of +0x28 and the per-vertex selector.  Counts the polygon (UINT_005e6f3c,
 * UINT_005e6f98) and returns 1 also when no selector applies. */
undefined4 rdCanvas_PreparePolygon(byte *param_1)
{
    /* per group: lit (lighting 1 and 2), unlit (0), per-vertex (3) */
    static void *const sel[5][3] = {
        {(void *)rdRaster_Select_FlatLit_11, (void *)rdRaster_Select_FlatLit_9, (void *)rdRaster_Select_FlatLit_13},
        {(void *)rdRaster_Select_FlatLit_5, (void *)rdRaster_Select_FlatLit_3, (void *)rdRaster_Select_FlatLit_7},
        {(void *)rdRaster_Select_FlatLit_10, (void *)rdRaster_Select_FlatLit_8, (void *)rdRaster_Select_FlatLit_12},
        {(void *)rdRaster_Select_FlatLit_4, (void *)rdRaster_Select_FlatLit_2, (void *)rdRaster_Select_FlatLit_6},
        {(void *)rdRaster_Select_TexLit, (void *)rdRaster_Select_Flat_2, (void *)rdRaster_Select_FlatLit},
    };
    int face = (int)param_1;
    uint idx = UINT_005e6f3c;
    int geo, light, tex, poly, cel, c, grp, n;
    float amb;

    if (idx >= 0x400)
        return 0;
    geo = P1_I32(face + 8);
    if (geo >= g_nRdroidGeometryMode)
        geo = g_nRdroidGeometryMode;
    light = P1_I32(face + 0xc);
    if (light >= g_nRdroidLightingMode)
        light = g_nRdroidLightingMode;
    tex = P1_I32(face + 0x10);
    if (tex >= g_nRdroidTextureMode)
        tex = g_nRdroidTextureMode;
    if (geo == 0)
        return 0;
    poly = (int)&UINT_00565f38 + idx * 0x204;
    P1_I32(poly) = face;
    P1_I32(poly + 0x1b8) = 0;
    P1_I32(poly + 0x1bc) = 0;
    P1_I32(poly + 0x1ec) = 0;
    P1_I32(poly + 0x1f0) = 0;
    P1_I32(poly + 0x1f8) = 0;
    cel = 0;
    if (P1_I32(face + 0x38) != 0) {
        int mat = P1_I32(face + 0x38);
        c = P1_I32(face + 0x3c);
        if (c == -1)
            c = P1_I32(mat + 0x64);
        if (c < 0)
            c = 0;
        else if (c > P1_I32(mat + 0x60) - 1)
            c = P1_I32(mat + 0x60) - 1;
        cel = P1_I32(mat + 0x68 + c * 4);
        if (geo == 4 && (P1_U8(cel) & 8) == 0)
            geo = 3;
    }
    if ((P1_U8(&g_dwRdroidFlags) & 2) == 0)
        amb = 0.0f;
    else
        P1_U32(&amb) = P1_U32(face + 0x40);
    grp = -1;
    if (geo == 2) {
        if (light >= 0 && light <= 4)
            p1_prep_draw(face, poly, cel, (void *)rdRaster_Select_Flat, 0, 0);
    }
    else if (geo == 3)
        grp = 4;
    else if (geo == 4) {
        int keyed = P1_U8(P1_I32(cel + 0x1c)) & 1;
        if (tex == 0)
            grp = keyed ? 1 : 3;
        else if (tex > 0 && tex <= 2)
            grp = keyed ? 0 : 2;
    }
    if (grp >= 0) {
        switch (light) {
        case 0:
            p1_prep_draw(face, poly, cel, sel[grp][1], 0, 0);
            break;
        case 1: {
            volatile float lv = p1_light_level(P1_F(face + 0x48), P1_F(face + 0x48), amb);
            P1_F(face + 0x44) = lv;
            p1_prep_draw(face, poly, cel, sel[grp][0], 1, P1_U32(&lv));
            break;
        }
        case 2: {
            long double s = (long double)P1_F(face + 0x48) + P1_F(face + 0x44);
            volatile float sf = (float)s;
            volatile float lv = p1_light_level(s, sf, amb);
            P1_F(face + 0x44) = lv;
            p1_prep_draw(face, poly, cel, sel[grp][0], 1, P1_U32(&lv));
            break;
        }
        case 3:
            for (n = 0; (uint)n < P1_U32(face + 0x1c); n++) {
                float *v = (float *)(P1_I32(face + 0x28) + n * 4);
                long double s = (long double)*v + P1_F(face + 0x48);
                volatile float sf = (float)s;
                *v = p1_light_level(s, sf, amb);
            }
            p1_prep_draw(face, poly, cel, sel[grp][2], 0, 0);
            break;
        default:
            break;
        }
    }
    UINT_005e6f3c = UINT_005e6f3c + 1;
    UINT_005e6f98 = UINT_005e6f98 + 1;
    return 1;
}

/* ------------------------------------------------------------------------------------------------------------------
 * rdPrimit3 */

/* the x87 clamp of an intensity to [0, 1]: a value below 0 or a NaN gives 0, above 1 gives 1 */
static float p1_clamp01(long double v)
{
    if (!(v >= 0.0L))
        return 0.0f;
    if (v > 1.0L)
        return 1.0f;
    return (float)v;
}

/* OVERRIDES: rdPrimit3_CopyFaceVerts */
/* ==== rdPrimit3_CopyFaceVerts (0x0040e500) ====
 * Copies a face that needs no clipping into the output vertex pools.  src (param_4) and dst (param_5) are vertex
 * pool records: +0x00 count, +0x04 position index list, +0x08 uv index list, +0x0c positions (12 bytes each),
 * +0x10 uvs (8 bytes), +0x14 intensities, +0x18 per-vertex extra intensity (src only, may be 0).  The geometry mode
 * (param_1: 0..2 positions only; 3 untextured; 4 textured) and the lighting mode (param_2, 3 = per-vertex intensity)
 * select what is copied; param_6 is the uv offset added to every uv; param_3 is unused.  The intensity is clamped to
 * [0, 1] on the x87 (with the extra term, the sum is clamped before rounding to float).  Unknown modes copy nothing
 * and leave dst->count alone.  The loops re-read src->count every pass, as the original does. */
void rdPrimit3_CopyFaceVerts(undefined4 param_1,int param_2,undefined4 param_3,uint *param_4,uint *param_5,
                             float *param_6)
{
    uint *src = param_4, *dst = param_5;
    uint i;
    int light, uv;

    (void)param_3;
    switch (param_1) {
    case 0: case 1: case 2:
        light = 0; uv = 0;
        break;
    case 3:
        if ((uint)param_2 > 3)
            return;
        light = param_2 == 3; uv = 0;
        break;
    case 4:
        if (param_2 < 0 || param_2 > 3)
            return;
        light = param_2 == 3; uv = 1;
        break;
    default:
        return;
    }
    for (i = 0; i < src[0]; i++) {
        uint *ps = (uint *)(src[3] + P1_I32(src[1] + i * 4) * 12);
        uint *pd = (uint *)(dst[3] + i * 12);
        pd[0] = ps[0];
        pd[1] = ps[1];
        pd[2] = ps[2];
        if (uv) {
            int k = P1_I32(src[2] + i * 4);
            float *td = (float *)(dst[4] + i * 8);
            ((uint *)td)[0] = P1_U32(src[4] + k * 8);
            ((uint *)td)[1] = P1_U32(src[4] + 4 + k * 8);
            td = (float *)(dst[4] + i * 8);
            td[0] = (float)((long double)param_6[0] + (long double)td[0]);
            td = (float *)(dst[4] + i * 8);
            td[1] = (float)((long double)td[1] + (long double)param_6[1]);
        }
        if (light) {
            float *pi = (float *)(src[5] + P1_I32(src[1] + i * 4) * 4);
            if (src[6] != 0) {
                long double s = (long double)*pi + (long double)((float *)src[6])[i];
                ((float *)dst[5])[i] = p1_clamp01(s);
            }
            else {
                /* the in-range value is reloaded from memory: an exact copy */
                if (!(*pi >= 0.0f))
                    ((float *)dst[5])[i] = 0.0f;
                else if (*pi > 1.0f)
                    ((float *)dst[5])[i] = 1.0f;
                else
                    ((uint *)dst[5])[i] = *(uint *)pi;
            }
        }
    }
    dst[0] = src[0];
}

/* ------------------------------------------------------------------------------------------------------------------
 * rdModel */

/* the stdio / heap services of g_pSvcRdroid with their real argument lists */
#define P1_FREAD(fp, buf, n) \
    ((int (*)(int, void *, int))g_pSvcRdroid->pFread)((fp), (void *)(buf), (int)(n))
/* pAlloc(size, source file, line): the line is DAT_004ddb84 (a short, the line of the first call) + k */
#define P1_ALLOC(n, k) \
    ((int (*)(int, const char *, int))g_pSvcRdroid->pAlloc)((int)(n), s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94, \
                                                             (int)*(short *)&DAT_004ddb84 + (k))
#define P1_FREE(p)  ((void (*)(int))g_pSvcRdroid->pFree)((int)(p))

/* OVERRIDES: rdModel3_LoadBinary */
/* ==== rdModel3_LoadBinary (0x0040b8e0) ====
 * Reads a binary model (param_1: the open file, param_2: the model record, reset by rdModel3_NewEntry) through the
 * g_pSvcRdroid file services: the material names (0x20 bytes each, +0x4c of them), the name (0x20) and +0x20, the
 * geometry sets (+0x44 of them at +0x24, 8 bytes each: mesh count and a zeroed 0x7c-byte mesh array), each mesh with
 * its vertices (+0x48: positions +0x30, +0x38 and +0x3c per vertex, normals +0x44), uvs (+0x4c: +0x34) and faces
 * (+0x50: 0x4c bytes each at +0x40, with vertex (+0x18) and uv (+0x1c) index lists of +0x14 entries and a material
 * index at +0x20, -1 when absent), then the hierarchy nodes (+0x54 of them, 0xb8 bytes at +0x58, the parent / child /
 * sibling indexes at +0x54 / +0x5c / +0x60 turned into pointers), the tail fields, and loads the materials
 * (rdMaterial_Load) into the +0x48 table; the face material indexes become material pointers (negative: 0).
 * Every count and pointer is re-read from the record where the original re-reads it.  Returns 1. */
undefined4 rdModel3_LoadBinary(int param_1,int param_2)
{
    int fp = param_1, m = param_2;
    int names = 0, tmp, g, i, k, f;
    uint u;

    rdModel3_NewEntry((undefined4 *)m);
    P1_FREAD(fp, &tmp, 4);
    P1_I32(m + 0x4c) = tmp;
    P1_I32(m + 0x48) = 0;
    if ((uint)tmp != 0)
        names = P1_ALLOC((uint)tmp << 5, 0x10);
    for (u = 0, k = names; u < P1_U32(m + 0x4c); u++, k += 0x20)
        P1_FREAD(fp, k, 0x20);
    P1_FREAD(fp, m, 0x20);
    P1_FREAD(fp, m + 0x20, 4);
    P1_FREAD(fp, m + 0x44, 4);
    for (g = 0; g < P1_I32(m + 0x44); g++) {
        int gs = m + 0x24 + g * 8;
        int arr;

        P1_FREAD(fp, gs, 4);
        arr = P1_ALLOC(P1_I32(gs) * 0x7c, 0x20);
        P1_I32(gs + 4) = arr;
        memset((void *)arr, 0, (uint)(P1_I32(gs) * 0x7c));
        for (i = 0; i < P1_I32(gs); i++) {
            int me = P1_I32(gs + 4) + i * 0x7c;

            P1_FREAD(fp, me, 0x20);
            P1_FREAD(fp, me + 0x20, 4);
            P1_FREAD(fp, me + 0x24, 4);
            P1_FREAD(fp, me + 0x28, 4);
            P1_FREAD(fp, me + 0x2c, 4);
            P1_FREAD(fp, me + 0x48, 4);
            P1_FREAD(fp, me + 0x4c, 4);
            P1_FREAD(fp, me + 0x50, 4);
            if (P1_U32(me + 0x48) != 0) {
                P1_I32(me + 0x30) = P1_ALLOC(P1_I32(me + 0x48) * 12, 0x30);
                P1_I32(me + 0x38) = P1_ALLOC(P1_I32(me + 0x48) << 2, 0x31);
                P1_I32(me + 0x3c) = P1_ALLOC(P1_I32(me + 0x48) << 2, 0x32);
            }
            if (P1_U32(me + 0x4c) != 0)
                P1_I32(me + 0x34) = P1_ALLOC(P1_I32(me + 0x4c) * 8, 0x36);
            P1_FREAD(fp, P1_I32(me + 0x30), P1_I32(me + 0x48) * 12);
            P1_FREAD(fp, P1_I32(me + 0x34), P1_I32(me + 0x4c) << 3);
            P1_FREAD(fp, P1_I32(me + 0x38), P1_I32(me + 0x48) << 2);
            P1_FREAD(fp, P1_I32(me + 0x3c), P1_I32(me + 0x48) << 2);
            if (P1_U32(me + 0x50) != 0) {
                int fa = P1_ALLOC(P1_I32(me + 0x50) * 0x4c, 0x40);
                P1_I32(me + 0x40) = fa;
                memset((void *)fa, 0, (uint)(P1_I32(me + 0x50) * 0x4c));
            }
            for (f = 0; f < P1_I32(me + 0x50); f++) {
                int fc = P1_I32(me + 0x40) + f * 0x4c;
                int p;

                P1_FREAD(fp, fc, 0x4c);
                if (P1_U32(fc + 0x14) != 0) {
                    p = P1_ALLOC(P1_I32(fc + 0x14) * 4, 0x49);
                    P1_I32(fc + 0x18) = p;
                    P1_FREAD(fp, p, P1_I32(fc + 0x14) << 2);
                }
                if (P1_I32(fc + 0x1c) != 0) {
                    p = P1_ALLOC(P1_I32(fc + 0x14) << 2, 0x4e);
                    P1_I32(fc + 0x1c) = p;
                    P1_FREAD(fp, p, P1_I32(fc + 0x14) << 2);
                }
                if (P1_I32(fc + 0x20) != 0) {
                    P1_FREAD(fp, &tmp, 4);
                    P1_I32(fc + 0x20) = tmp;
                }
                else
                    P1_I32(fc + 0x20) = -1;
            }
            P1_I32(me + 0x44) = 0;
            if (P1_U32(me + 0x48) != 0)
                P1_I32(me + 0x44) = P1_ALLOC(P1_I32(me + 0x48) * 12, 0x5f);
            {
                int nv = P1_I32(me + 0x48);
                P1_FREAD(fp, P1_I32(me + 0x44), nv * 12);
            }
            P1_FREAD(fp, me + 0x54, 4);
            P1_FREAD(fp, me + 0x5c, 4);
            P1_FREAD(fp, me + 0x60, 4);
            P1_FREAD(fp, me + 0x64, 0x18);
        }
    }
    P1_FREAD(fp, m + 0x50, 4);
    P1_FREAD(fp, m + 0x54, 4);
    P1_I32(m + 0x58) = P1_ALLOC(P1_I32(m + 0x54) * 0xb8, 0x6c);
    for (i = 0; i < P1_I32(m + 0x54); i++) {
        int nd = P1_I32(m + 0x58) + i * 0xb8;

        P1_FREAD(fp, nd, 0xb8);
        for (k = 0x54; k <= 0x60; k += 4) {
            if (k == 0x58)
                continue;
            if (P1_I32(nd + k) != 0) {
                P1_FREAD(fp, &tmp, 4);
                P1_I32(nd + k) = P1_I32(m + 0x58) + tmp * 0xb8;
            }
        }
    }
    P1_FREAD(fp, m + 0x5c, 4);
    P1_FREAD(fp, m + 0x60, 0x18);
    P1_FREAD(fp, m + 0x78, 0xc);
    P1_FREAD(fp, m + 0x84, 0xc);
    if (P1_U32(m + 0x4c) != 0)
        P1_I32(m + 0x48) = P1_ALLOC(P1_I32(m + 0x4c) * 4, 0x8e);
    for (u = 0, k = names; u < P1_U32(m + 0x4c); u++, k += 0x20)
        ((int *)P1_I32(m + 0x48))[u] = (int)rdMaterial_Load((char *)k, 0, 0);
    for (g = 0; g < P1_I32(m + 0x44); g++) {
        int gs = m + 0x24 + g * 8;

        for (i = 0; i < P1_I32(gs); i++) {
            int me = P1_I32(gs + 4) + i * 0x7c;

            for (f = 0; f < P1_I32(me + 0x50); f++) {
                int fc = P1_I32(me + 0x40) + f * 0x4c;

                if (P1_I32(fc + 0x20) < 0)
                    P1_I32(fc + 0x20) = 0;
                else
                    P1_I32(fc + 0x20) = ((int *)P1_I32(m + 0x48))[P1_I32(fc + 0x20)];
            }
        }
    }
    if (names != 0)
        P1_FREE(names);
    return 1;
}

/* x87 square root of an extended value (the original's fsqrt; no errno path) */
static inline long double p1_fsqrt(long double x)
{
    __asm__("fsqrt" : "+t"(x));
    return x;
}

/* the light level of rdModel_ComputeMeshLighting: the intensity clamped to [0, 1] (the first test against 0 is made
 * on s, the x87 value, the others on its float copy sf), raised to the ambient floor amb, times 63, rounded to
 * float.  The original clamps a second time, on sf only, when the clamped value is above the floor. */
static float p1_light_level(long double s, float sf, float amb)
{
    float c, r;

    if (!(s >= 0.0L))
        c = 0.0f;
    else
        c = sf > 1.0f ? 1.0f : sf;
    if (c > amb) {
        if (!(sf >= 0.0f))
            r = 0.0f;
        else
            r = sf > 1.0f ? 1.0f : sf;
    }
    else
        r = amb;
    return (float)((long double)r * 63.0f);
}

/* OVERRIDES: rdModel_ComputeMeshLighting */
/* ==== rdModel_ComputeMeshLighting (0x00409580) ====
 * Light level of a mesh face before it is drawn.  The face's geometry / lighting / texture modes (+0x08, +0x0c,
 * +0x10) are clamped to the renderer's (g_nRdroid*Mode); geometry 0 returns 0.  The material (+0x38) gives the
 * texture cel (+0x3c, -1 = the material's current cel +0x64, clamped to its +0x60 cels); a textured face whose cel
 * has no bit 3 in its flags draws untextured.  The ambient floor is +0x40 when g_dwRdroidFlags bit 1 is set, else 0.
 * Lighting 1 uses the face intensity +0x48, 2 the sum +0x48 + +0x44, 3 the per-vertex sums +0x48 + +0x28[i]
 * (stored back in +0x28[i]); the level of 1 and 2 is stored in +0x44 and passed (as its raw dword) to the face's draw
 * callback +0x14 (face, cel, level); lighting 0 and 3 pass 0.  Geometry 1 and 2 only call the callback (level 0) for
 * lighting 0..4.  Unknown modes skip the callback.  Returns 1. */
undefined4 rdModel_ComputeMeshLighting(byte *param_1)
{
    int p = (int)param_1;
    int geo, light, tex, mat, cel, n;
    float amb;
    void (*draw)(int, int, uint);

    geo = P1_I32(p + 8);
    if (geo >= g_nRdroidGeometryMode)
        geo = g_nRdroidGeometryMode;
    light = P1_I32(p + 0xc);
    if (light >= g_nRdroidLightingMode)
        light = g_nRdroidLightingMode;
    tex = P1_I32(p + 0x10);
    if (tex >= g_nRdroidTextureMode)
        tex = g_nRdroidTextureMode;
    if (geo == 0)
        return 0;
    mat = P1_I32(p + 0x38);
    if (mat != 0) {
        cel = P1_I32(p + 0x3c);
        if (cel == -1)
            cel = P1_I32(mat + 0x64);
        if (cel < 0)
            cel = 0;
        else if (cel > P1_I32(mat + 0x60) - 1)
            cel = P1_I32(mat + 0x60) - 1;
        mat = P1_I32(mat + 0x68 + cel * 4);
        if (geo == 4 && (P1_U8(mat) & 8) == 0)
            geo = 3;
    }
    if ((P1_U8(&g_dwRdroidFlags) & 2) == 0)
        amb = 0.0f;
    else
        P1_U32(&amb) = P1_U32(p + 0x40);
    draw = (void (*)(int, int, uint))P1_I32(p + 0x14);
    switch (geo) {
    case 1: case 2:
        if (light >= 0 && light <= 4)
            draw(p, mat, 0);
        return 1;
    case 3:
        break;
    case 4:
        if (tex != 0 && tex != 1)
            return 1;
        break;
    default:
        return 1;
    }
    switch (light) {
    case 0:
        draw(p, mat, 0);
        break;
    case 1: {
        volatile float lv = p1_light_level(P1_F(p + 0x48), P1_F(p + 0x48), amb);
        P1_F(p + 0x44) = lv;
        draw(p, mat, P1_U32(&lv));
        break;
    }
    case 2: {
        long double s = (long double)P1_F(p + 0x48) + P1_F(p + 0x44);
        volatile float sf = (float)s;
        volatile float lv = p1_light_level(s, sf, amb);
        P1_F(p + 0x44) = lv;
        draw(p, mat, P1_U32(&lv));
        break;
    }
    case 3:
        for (n = 0; (uint)n < P1_U32(p + 0x1c); n++) {
            float *v = (float *)(P1_I32(p + 0x28) + n * 4);
            long double s = (long double)P1_F(p + 0x48) + *v;
            volatile float sf = (float)s;
            *v = p1_light_level(s, sf, amb);
        }
        draw(p, mat, 0);
        break;
    default:
        break;
    }
    return 1;
}

/* the light records of the current scene (UINT_007f1498[UINT_007f31f8]): +0x00 index of the light position in the
 * camera (camera + 0x15c + index * 12), +0x04 type (2 = point light without a direction), +0x08 enabled,
 * +0x0c direction, +0x34 range (float) */
#define P1_LIGHTPOS(cam, l)  ((cam) + (P1_I32(l) + 0x1d) * 12)

/* the direction of a light into the model frame: the transposed model matrix with its translation cleared for the
 * call (the original saves and restores the three words around it) */
static void p1_light_dir(int light, float *mt, int slot)
{
    float dir[3];
    uint t0 = ((uint *)mt)[9], t1 = ((uint *)mt)[10], t2 = ((uint *)mt)[11];

    ((uint *)mt)[9] = 0;
    ((uint *)mt)[10] = 0;
    ((uint *)mt)[11] = 0;
    dir[0] = -P1_F(light + 0xc);
    dir[1] = -P1_F(light + 0x10);
    dir[2] = -P1_F(light + 0x14);
    Vec3_Sub((float *)((int)&DAT_007f1168 + slot * 12), dir, mt);
    ((uint *)mt)[9] = t0;
    ((uint *)mt)[10] = t1;
    ((uint *)mt)[11] = t2;
}

/* OVERRIDES: rdModel_DrawMesh */
/* ==== rdModel_DrawMesh (0x0040d230) ====
 * Draws one mesh of a model with the model matrix (12 floats, translation at +9).  The mesh (PTR_007f30a0) is
 * frustum tested (UINT_007f1898: 0 inside, 1 crossing, 2 outside, which returns), culled against the clip plane of
 * UINT_007f3204, its vertices are transformed into the camera frame (DAT_007f18a0), the geometry / texture / light
 * modes are clamped to the renderer limits, and by the light mode: 2 or 3 collect the lights that reach the mesh
 * (UINT_007f30e0 list, positions DAT_007f1598 and directions DAT_007f1168 in the model frame); 3 also computes the
 * vertex intensities; 6 copies the mesh intensity into every face.  Last, every face whose plane faces the eye (the
 * eye in the model frame at DAT_007f0fd8) goes to rdModel_AddMeshToCache with flag 0; back faces go with flag 1 if
 * the face is two-sided (+0x04 bit 0) or culling is off (g_dwRdroidFlags bit 0).
 * The distance tests are x87 expressions with the original's precision: mode 2 compares sqrt(dx*dx + dy*(float)dy +
 * (float)dz*(float)dz) against range + mesh radius (the original spills dy and dz to float slots); mode 3 compares
 * the squared distance in extended precision (NaN counts as "inside"). */
void __cdecl rdModel_DrawMesh(void *mesh,float *matrix)
{
    float rel[3];
    float mt[12];       /* transposed matrix */
    float mc[12];       /* camera * model */
    uint eye[3];
    int mode, n;
    uint i;

    PTR_007f30a0 = mesh;
    if (P1_I32((int)mesh + 0x24) == 0)
        return;
    Vec3_Sub(rel, matrix + 9, (float *)((int)g_pRdCurrentCamera + 8));
    if (UINT_007f30a4 == 0)
        n = 0;
    else if ((DAT_00900068 & 1) == 0)
        n = 1;
    else
        n = ((uint (*)(int *, float *, uint))Frustum_TestSphere)(*(int **)((int)g_pRdCurrentCamera + 0x48), rel,
                                                                   P1_U32((int)PTR_007f30a0 + 0x60));
    UINT_007f1898 = n;
    if (n == 2)
        return;
    if (UINT_007f3204 != 0) {
        long double a1 = ((long double)matrix[10] - P1_F(&DAT_007f320c)) * P1_F(&DAT_004ddb74);
        long double a2 = ((long double)matrix[11] - P1_F(&DAT_007f3210)) * P1_F(&DAT_004ddb78);
        long double a0 = ((long double)matrix[9] - P1_F(&DAT_007f3208)) * P1_F(&DAT_004ddb70);
        long double d = (a1 + a2) + a0;
        if (-(long double)P1_F((int)PTR_007f30a0 + 0x60) > d)
            return;
    }
    Matrix_Mul34(mc, (float *)((int)g_pRdCurrentCamera + 8), matrix);
    Matrix_TransformPoints(mc, *(float **)((int)PTR_007f30a0 + 0x30), (float *)&DAT_007f18a0,
                           P1_I32((int)PTR_007f30a0 + 0x48));
    Matrix_Transpose(mt, matrix);
    {
        int m = (int)PTR_007f30a0;
        int v;

        v = P1_I32(m + 0x24);
        UINT_007f31e8 = v < (int)UINT_007f1494 ? v : (int)UINT_007f1494;
        v = P1_I32(m + 0x2c);
        UINT_007f30d8 = v < (int)UINT_007f189c ? v : (int)UINT_007f189c;
        mode = P1_I32(m + 0x28);
        if (mode != 6 && mode >= (int)UINT_007f30dc)
            mode = (int)UINT_007f30dc;
        UINT_007f31e4 = mode;
        _DAT_007f30b4 = (int)&DAT_007f18a0;
        _DAT_007f30b8 = P1_I32(m + 0x34);
        _DAT_007f30bc = P1_I32(m + 0x3c);
        _DAT_007f30c0 = 0;
        UINT_007f1474 = (int)&DAT_007f0fe8;
    }
    if (mode == 2 || mode == 3) {
        UINT_007f31fc = 0;
        for (i = 0; i < UINT_007f31f8; i++) {
            int light = (&UINT_007f1498)[i];
            int cam = (int)g_pRdCurrentCamera;
            int pos, reach;

            if (P1_I32(light + 8) == 0)
                continue;
            pos = P1_LIGHTPOS(cam, light);
            if (mode == 2) {
                long double y = (long double)P1_F(pos + 4) - matrix[10];
                long double x = (long double)P1_F(pos) - matrix[9];
                long double z = (long double)P1_F(pos + 8) - matrix[11];
                volatile float yf = (float)y, zf = (float)z;
                long double s = (x * x + y * (long double)yf) + (long double)zf * (long double)zf;
                long double r = (long double)P1_F(light + 0x34) + P1_F((int)PTR_007f30a0 + 0x60);
                reach = r > p1_fsqrt(s);
            }
            else {
                long double x = (long double)P1_F(pos) - matrix[9];
                long double y = (long double)P1_F(pos + 4) - matrix[10];
                long double z = (long double)P1_F(pos + 8) - matrix[11];
                long double s = P1_I32(light + 4) < 2 ? 0.0L : (x * x + y * y) + z * z;
                long double r = (long double)P1_F(light + 0x34) + P1_F((int)PTR_007f30a0 + 0x60);
                reach = !(s >= r * r);
            }
            if (!reach)
                continue;
            (&UINT_007f30e0)[UINT_007f31fc] = light;
            Vec3_Sub((float *)((int)&DAT_007f1598 + UINT_007f31fc * 12), (float *)P1_LIGHTPOS(cam, light), mt);
            if (P1_I32(light + 4) != 2)
                p1_light_dir(light, mt, UINT_007f31fc);
            UINT_007f31fc = UINT_007f31fc + 1;
        }
        if (mode == 3) {
            int m = (int)PTR_007f30a0;
            /* the float argument is pushed as its raw dword, as the original does */
            P1_F((int)mesh + 0x5c) =
                ((float (*)(int *, float *, int, uint, int *, uint, float *, float *, uint, uint))
                     rdLight_CalcVertexIntensities)(
                    (int *)&UINT_007f30e0, (float *)&DAT_007f1598, (int)&DAT_007f1168, UINT_007f31fc,
                    *(int **)(m + 0x44), P1_U32(m + 0x30), *(float **)(m + 0x38), *(float **)(m + 0x3c),
                    P1_U32(m + 0x48), P1_U32((int)g_pRdCurrentCamera + 0x45c));
        }
    }
    else if (mode == 6) {
        for (i = 0; i < P1_U32((int)mesh + 0x50); i++)
            P1_U32(P1_I32((int)mesh + 0x40) + 0x30 + i * 0x4c) = P1_U32((int)mesh + 0x5c);
    }
    eye[0] = UINT_008ddf84;
    eye[1] = UINT_008ddf88;
    eye[2] = UINT_008ddf8c;
    Vec3_Sub((float *)&DAT_007f0fd8, (float *)eye, mt);
    {
        int face = P1_I32((int)mesh + 0x40);

        for (i = 0; i < P1_U32((int)mesh + 0x50); i++, face += 0x4c) {
            int v = P1_I32((int)PTR_007f30a0 + 0x30) + P1_I32(P1_I32(face + 0x18)) * 12;
            long double dz = (long double)P1_F(&DAT_007f0fe0) - P1_F(v + 8);
            long double dx = (long double)P1_F(&DAT_007f0fd8) - P1_F(v);
            long double dy = (long double)P1_F(&DAT_007f0fdc) - P1_F(v + 4);
            long double dot = dz * P1_F(face + 0x48) + dx * P1_F(face + 0x40);
            dot = dy * P1_F(face + 0x44) + dot;
            if (dot > 0.0L)
                rdModel_AddMeshToCache(face, 0);
            else if ((P1_U8(face + 4) & 1) != 0 || (P1_U8(&g_dwRdroidFlags) & 1) == 0)
                rdModel_AddMeshToCache(face, 1);
        }
    }
}

#endif /* GRIM_EXE */
