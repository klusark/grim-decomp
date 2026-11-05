/* Readable C for software-rasteriser functions of GRIMFANDANGO.EXE (0x0041a130 - 0x0042b1f0, follow-up of
 * build/overrides_asm_s2.c).
 *
 * Each function below replaces the assembled original at the address given in its comment.  The C was written
 * against the 1.01 machine code (src/GRIMFANDANGO.EXE/asm_funcs.s) and checked with a differential test that runs the
 * original bytes of the function next to this C on the same memory (build/difftest/asm_s2/, docs/notes/asm_o1.md).
 *
 * Conventions.  An edge record (`RdEdge` below, 0x44 bytes) is what the edge stepping functions fill and the span
 * functions read: +0x00 x (16.16), +0x04 dx per scanline, +0x08 scanlines left, +0x0c current vertex index,
 * +0x28 / +0x30 / +0x38 interpolants (16.16), +0x40 screen row.  Only the raw byte offsets are used, as in the
 * original.  The 64-bit fixed point products (imul to EDX:EAX, shrd by 16) are written as long long >> 16.
 * Globals are Ghidra's names; R32 / R8 / R16 read them at their real width.
 */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

#define R32(g) (*(int *)&(g))
#define U32(g) (*(uint *)&(g))
#define R8(g) (*(uint8_t *)&(g))
#define R16(g) (*(uint16_t *)&(g))

/* frame buffer descriptor of the current camera: g_pRdCurrentCamera->+4->+4 (+0x18 pitch, +0x24 bpp, +0x5c pixels) */
#define RD_CANVAS() (*(int *)(*(int *)((int)g_pRdCurrentCamera + 4) + 4))

/* Rasteriser state globals used by the span loops (Ghidra names, read at their real width) */
#define RD_RECIP(n)  (((int *)&DAT_008fbfc0)[n])   /* 0x10000 / n, filled at start-up */
#define rd_u         R32(UINT_007f4454)            /* texture u (16.16, after the shift) */
#define rd_uStep     R32(UINT_007f43bc)
#define rd_v         R32(UINT_007f4458)            /* texture v */
#define rd_vStep     R32(UINT_007f4254)
#define rd_l         R32(UINT_007f4450)            /* light / shade value */
#define rd_lStep     R32(UINT_007f439c)
#define rd_texShift  R32(UINT_008ddee4)            /* u, v are shifted right by this */
#define rd_uOffset   R32(UINT_008ddef8)
#define rd_vOffset   R32(UINT_008ddeac)
#define rd_vShift    R32(UINT_008dded8)            /* row index = (v >> (16 - rd_vShift)) & rd_vMask */
#define rd_vMask     R32(UINT_008ddefc)
#define rd_uMask     R32(UINT_008ddecc)            /* column index = (u >> 16) & (rd_uMask >> 16) */
#define rd_pTex      U32(UINT_008ddee8)            /* texels */
#define rd_pLight    U32(UINT_008ddea8)            /* light table, 256 bytes per level */
#define rd_pShade    U32(UINT_008ddeb0)            /* shade table, 256 bytes per level */
#define rd_pPal16    U32(UINT_008ddebc)            /* 16 bit palette, 256 words per level */
#define rd_pTexPal   U32(UINT_008dded4)            /* texel to palette index */
#define rd_level     R8(DAT_008ddec0)              /* light level of the face */
#define rd_ptr8      PTR_007f4300                  /* 8 bit destination (or the texel of the 16 bit flat spans) */
#define rd_ptr16     PTR_007f43a8                  /* 16 bit destination */

/* arithmetic shift by a count taken mod 32, as SAR with CL does */
#define SAR(x, n)    ((int)(x) >> ((n) & 31))
/* 16.16 product, imul to EDX:EAX then shrd 16 */
#define FMUL(a, b)   ((int)(((long long)(int)(a) * (long long)(int)(b)) >> 16))

/* x of an edge rounded up to a whole pixel (16.16), as the span functions do */
static inline uint rd_ceil16(uint x)
{
    if (x & 0xffff)
        x = (x + 0x10000) & 0xffff0000u;
    return x;
}

/* ==== rdRaster_Span_Tex (0x0041a4f0) ====
 * 8 bit span, flat lit: every pixel already in the frame buffer is remapped through the 256 byte light table
 * UINT_008ddea8 + DAT_008ddec0 * 0x100 (in place). */
void rdRaster_Span_Tex(uint *param_1, uint *param_2)
{
    uint xl = rd_ceil16(*param_1) >> 16;
    uint xr = rd_ceil16(*param_2) >> 16;
    int count = (int)(xr - xl);
    int cv;
    uint8_t *dst;

    if (count <= 0)
        return;
    cv = RD_CANVAS();
    dst = (uint8_t *)(param_1[0x10] * *(int *)(cv + 0x18) + *(int *)(cv + 0x5c) + xl);
    do {
        *dst = *(uint8_t *)(U32(UINT_008ddea8) + (uint)R8(DAT_008ddec0) * 0x100 + *dst);
        dst++;
    } while (--count != 0);
}

/* ==== rdRaster_Span16_Tex_2 (0x0041a580) ====
 * 16 bit span, one colour: the texel *PTR_007f4300 (not advanced) goes through the byte table UINT_008dded4, the
 * light table UINT_008ddea8 + DAT_008ddec0 * 0x100 and the word palette UINT_008ddebc.  The destination pointer is
 * the global PTR_007f43a8, advanced by 2 per pixel and left after the span. */
void rdRaster_Span16_Tex_2(uint *param_1, uint *param_2)
{
    uint xl = rd_ceil16(*param_1) >> 16;
    uint xr = rd_ceil16(*param_2) >> 16;
    int count = (int)(xr - xl);
    int cv;
    uint c;

    if (count <= 0)
        return;
    cv = RD_CANVAS();
    PTR_007f43a8 = (int *)(*(int *)(cv + 0x5c) + (param_1[0x10] * (*(uint *)(cv + 0x18) >> 1) + xl) * 2);
    do {
        c = *(uint8_t *)(U32(UINT_008dded4) + *PTR_007f4300);
        c = *(uint8_t *)((uint)R8(DAT_008ddec0) * 0x100 + U32(UINT_008ddea8) + c);
        *(uint16_t *)PTR_007f43a8 = *(uint16_t *)(U32(UINT_008ddebc) + c * 2);
        PTR_007f43a8 = (int *)((char *)PTR_007f43a8 + 2);
    } while (--count != 0);
}

/* the per-pixel step of the light value that most lit spans use: a small negative step is set to 0 */
static inline int rd_clamp_step(int step)
{
    if (step < 0 && step > -0x51e)
        step = 0;
    return step;
}

/* ==== rdRaster_Span_Tex_2 (0x0041b0d0) ====
 * 8 bit span, Gouraud lit remap of the frame buffer: the light value (edge +0x38) is interpolated; each pixel is
 * remapped in place through light[shade[level + (l >> 8 & 0x3f00)] * 0x100 + pixel]. */
void rdRaster_Span_Tex_2(uint *param_1, uint *param_2)
{
    uint xl = rd_ceil16(*param_1);
    int xli = (int)xl >> 16;
    int count = ((int)rd_ceil16(*param_2) >> 16) - xli;
    int r, step, l, cv;
    uint8_t *dst;

    if (count <= 0)
        return;
    r = RD_RECIP(count);
    step = rd_clamp_step(FMUL(param_2[0xe] - param_1[0xe], r));
    l = FMUL(xl - *param_1, step) + (int)param_1[0xe];
    cv = RD_CANVAS();
    dst = (uint8_t *)(param_1[0x10] * *(int *)(cv + 0x18) + *(int *)(cv + 0x5c) + xli);
    do {
        uint s = *(uint8_t *)(rd_pShade + (SAR(l, 8) & 0x3f00) + rd_level);
        l += step;
        *dst = *(uint8_t *)(*dst + rd_pLight + (s << 8));
        dst++;
    } while (--count != 0);
}

/* ==== rdRaster_Span16_Tex_3 (0x0041b1e0) ====
 * 16 bit span, one texel (*rd_ptr8, not advanced), Gouraud lit: palette word
 * pal16[((l >> 16) & 0x3f) * 0x100 + light[level * 0x100 + texpal[texel]]].  Writes through rd_ptr16. */
void rdRaster_Span16_Tex_3(uint *param_1, uint *param_2)
{
    uint xl = rd_ceil16(*param_1);
    int xli = (int)xl >> 16;
    int count = ((int)rd_ceil16(*param_2) >> 16) - xli;
    int r, step, l, cv;

    if (count <= 0)
        return;
    r = RD_RECIP(count);
    step = rd_clamp_step(FMUL(param_2[0xe] - param_1[0xe], r));
    l = FMUL(xl - *param_1, step) + (int)param_1[0xe];
    cv = RD_CANVAS();
    rd_ptr16 = (int *)(*(int *)(cv + 0x5c) + (param_1[0x10] * (*(uint *)(cv + 0x18) >> 1) + xli) * 2);
    do {
        uint c = *(uint8_t *)(rd_pTexPal + *rd_ptr8);
        c = *(uint8_t *)((uint)rd_level * 0x100 + rd_pLight + c);
        c += (SAR(l, 16) & 0x3f) << 8;
        l += step;
        *(uint16_t *)rd_ptr16 = *(uint16_t *)(rd_pPal16 + c * 2);
        rd_ptr16 = (int *)((char *)rd_ptr16 + 2);
    } while (--count != 0);
}

/* Set-up shared by the affine textured spans: u (edge +0x28) and v (+0x30) steps and start values, shifted by
 * rd_texShift, plus the offsets rd_uOffset / rd_vOffset; returns the pixel count (<= 0: nothing to draw) and the
 * first column.  The right x is rounded up and shifted logically (shr) in these functions. */
static inline int rd_setup_uv(uint *e1, uint *e2, int *pxli)
{
    uint xl = rd_ceil16(*e1);
    int xli = (int)xl >> 16;
    int count = (int)((rd_ceil16(*e2) >> 16) - xli);
    int dx, r, t;

    *pxli = xli;
    if (count <= 0)
        return count;
    dx = (int)(xl - *e1);
    r = RD_RECIP(count);
    t = FMUL(e2[0xa] - e1[0xa], r);
    rd_uStep = SAR(t, rd_texShift);
    rd_u = SAR(FMUL(dx, t) + (int)e1[0xa], rd_texShift);
    t = FMUL(e2[0xc] - e1[0xc], r);
    rd_vStep = SAR(t, rd_texShift);
    t = SAR(FMUL(dx, t) + (int)e1[0xc], rd_texShift);
    rd_u += rd_uOffset;
    rd_v = t + rd_vOffset;
    return count;
}

/* texel at the current u, v */
static inline uint8_t rd_texel(void)
{
    return *(uint8_t *)(rd_pTex + (SAR(rd_v, 16 - rd_vShift) & rd_vMask) + (SAR(rd_uMask, 16) & SAR(rd_u, 16)));
}

/* pointer to the first pixel of an 8 bit span */
static inline uint8_t *rd_dst8(uint *e1, int xli)
{
    int cv = RD_CANVAS();
    return (uint8_t *)(e1[0x10] * *(int *)(cv + 0x18) + *(int *)(cv + 0x5c) + xli);
}

/* ==== rdRaster_Span_Flat_2 (0x0041b6f0) ====
 * 8 bit span, affine textured, unlit: dst = texel(u, v).  u, v and the destination are kept in the globals. */
void rdRaster_Span_Flat_2(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr8 = rd_dst8(param_1, xli);
    do {
        *rd_ptr8 = rd_texel();
        rd_ptr8++;
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

/* ==== rdRaster_Span_FlatKey (0x0041c810) ====
 * As rdRaster_Span_Flat_2, texel 0 is transparent (not written). */
void rdRaster_Span_FlatKey(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr8 = rd_dst8(param_1, xli);
    do {
        uint8_t c = rd_texel();
        if (c != 0)
            *rd_ptr8 = c;
        rd_ptr8++;
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

/* texel at the current u, v, second addressing form: row = ((v >> 16) & rd_vMask) << rd_vShift */
static inline uint8_t rd_texel_b(void)
{
    return *(uint8_t *)(rd_pTex + (SAR(rd_uMask, 16) & SAR(rd_u, 16)) +
                        ((uint)(SAR(rd_v, 16) & rd_vMask) << (rd_vShift & 31)));
}

/* pointer to the first pixel of a 16 bit span */
static inline int *rd_dst16(uint *e1, int xli)
{
    int cv = RD_CANVAS();
    return (int *)(*(int *)(cv + 0x5c) + (e1[0x10] * (*(uint *)(cv + 0x18) >> 1) + xli) * 2);
}

#define RD_PUT16(c)  (*(uint16_t *)rd_ptr16 = (uint16_t)(c), rd_ptr16 = (int *)((char *)rd_ptr16 + 2))
#define LIGHT(i)     (*(uint8_t *)(rd_pLight + (i)))
#define SHADE(i)     (*(uint8_t *)(rd_pShade + (i)))
#define TEXPAL(i)    (*(uint8_t *)(rd_pTexPal + (i)))
#define PAL16(i)     (*(uint16_t *)(rd_pPal16 + (i) * 2))

/* ==== rdRaster_Span_Tex_3 (0x0041c260) ====
 * 8 bit span, affine textured, blended with the frame buffer: dst = light[texel * 0x100 + dst]. */
void rdRaster_Span_Tex_3(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr8 = rd_dst8(param_1, xli);
    do {
        *rd_ptr8 = LIGHT(((uint)rd_texel() << 8) + *rd_ptr8);
        rd_ptr8++;
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

/* ==== rdRaster_Span_Tex_4 (0x0041df60) ====
 * 8 bit span, affine textured, shaded and blended: dst = light[shade[texel] * 0x100 + dst]. */
void rdRaster_Span_Tex_4(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr8 = rd_dst8(param_1, xli);
    do {
        *rd_ptr8 = LIGHT(((uint)SHADE(rd_texel()) << 8) + *rd_ptr8);
        rd_ptr8++;
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

/* ==== rdRaster_Span8_TexKey (0x0041e550) ====
 * 8 bit span, affine textured, colour key 0, shaded: dst = shade[texel]. */
void rdRaster_Span8_TexKey(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr8 = rd_dst8(param_1, xli);
    do {
        uint8_t c = rd_texel();
        if (c != 0)
            *rd_ptr8 = SHADE(c);
        rd_ptr8++;
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

/* ==== rdRaster_Span_TexKey (0x0041cdd0) ====
 * 8 bit span, affine textured (row shifted left by rd_vShift), colour key 0, blended:
 * dst = light[texel * 0x100 + dst]. */
void rdRaster_Span_TexKey(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr8 = rd_dst8(param_1, xli);
    do {
        uint8_t c = rd_texel_b();
        if (c != 0)
            *rd_ptr8 = LIGHT(((uint)c << 8) + *rd_ptr8);
        rd_ptr8++;
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

/* ==== rdRaster_Span_TexKey_2 (0x0041eb40) ====
 * 8 bit span, affine textured, colour key 0, blended then shaded: dst = shade[light[texel * 0x100 + dst]]. */
void rdRaster_Span_TexKey_2(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr8 = rd_dst8(param_1, xli);
    do {
        uint8_t c = rd_texel();
        if (c != 0)
            *rd_ptr8 = SHADE(LIGHT(((uint)c << 8) + *rd_ptr8));
        rd_ptr8++;
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

/* 16 bit affine spans: the destination is rd_ptr16. */

/* ==== rdRaster_Span16_Tex_4 (0x0041b880), rdRaster_Span16_Tex_6 (0x0041d560) ====
 * 16 bit span, affine textured, unlit: dst = pal16[texel].  The two functions are identical. */
void rdRaster_Span16_Tex_4(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr16 = rd_dst16(param_1, xli);
    do {
        RD_PUT16(PAL16(rd_texel()));
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

void rdRaster_Span16_Tex_6(uint *param_1, uint *param_2)
{
    rdRaster_Span16_Tex_4(param_1, param_2);
}

/* ==== rdRaster_Span16_Tex_5 (0x0041c410) ====
 * 16 bit span, affine textured, blended with the 8 bit pixel at rd_ptr8 (not advanced):
 * dst = pal16[light[texel * 0x100 + texpal[*rd_ptr8]]]. */
void rdRaster_Span16_Tex_5(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr16 = rd_dst16(param_1, xli);
    do {
        uint c = rd_texel();
        RD_PUT16(PAL16(LIGHT((c << 8) + TEXPAL(*rd_ptr8))));
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

/* ==== rdRaster_Span16_TexKey (0x0041c9b0), rdRaster_Span16_TexKey_3 (0x0041e700) ====
 * 16 bit span, affine textured, colour key 0: dst = pal16[texel].  The two functions are identical. */
void rdRaster_Span16_TexKey(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr16 = rd_dst16(param_1, xli);
    do {
        uint8_t c = rd_texel();
        if (c != 0)
            *(uint16_t *)rd_ptr16 = PAL16(c);
        rd_ptr16 = (int *)((char *)rd_ptr16 + 2);
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

void rdRaster_Span16_TexKey_3(uint *param_1, uint *param_2)
{
    rdRaster_Span16_TexKey(param_1, param_2);
}

/* ==== rdRaster_Span16_TexKey_2 (0x0041cf90) ====
 * 16 bit span, affine textured (row shifted left by rd_vShift), colour key 0, blended with the 8 bit pixel at
 * rd_ptr8 (not advanced): dst = pal16[light[texel * 0x100 + texpal[*rd_ptr8]]]. */
void rdRaster_Span16_TexKey_2(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr16 = rd_dst16(param_1, xli);
    do {
        uint8_t c = rd_texel_b();
        if (c != 0)
            *(uint16_t *)rd_ptr16 = PAL16(LIGHT(((uint)c << 8) + TEXPAL(*rd_ptr8)));
        rd_ptr16 = (int *)((char *)rd_ptr16 + 2);
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

/* ==== rdRaster_Span_TexKey_3 (0x0041ed10) ====
 * Mixed span: rd_ptr8 is set to the 8 bit address of the first pixel and stays there; the pixels are written as
 * 16 bit words through rd_ptr16, which this function does not set (it continues from its current value), with
 * colour key 0: dst16 = pal16[light[texel * 0x100 + texpal[*rd_ptr8]]].  Kept as in the original. */
void rdRaster_Span_TexKey_3(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr8 = rd_dst8(param_1, xli);
    do {
        uint8_t c = rd_texel();
        if (c != 0)
            *(uint16_t *)rd_ptr16 = PAL16(LIGHT(((uint)c << 8) + TEXPAL(*rd_ptr8)));
        rd_ptr16 = (int *)((char *)rd_ptr16 + 2);
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

/* ==== rdRaster_Span16_Tex_7 (0x0041e120) ====
 * 16 bit span, affine textured, blended through the palette index of the texel's colour with the 8 bit pixel at
 * rd_ptr8 (not advanced): dst = pal16[light[texpal[pal16[texel]] * 0x100 + texpal[*rd_ptr8]]]. */
void rdRaster_Span16_Tex_7(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uv(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr16 = rd_dst16(param_1, xli);
    do {
        uint c = TEXPAL(PAL16(rd_texel()));
        RD_PUT16(PAL16(LIGHT((c << 8) + TEXPAL(*rd_ptr8))));
        rd_u += rd_uStep;
        rd_v += rd_vStep;
    } while (--count != 0);
}

/* As rd_setup_uv, plus the light value (edge +0x38): rd_lStep (small negative steps set to 0) and rd_l. */
static inline int rd_setup_uvl(uint *e1, uint *e2, int *pxli)
{
    uint xl = rd_ceil16(*e1);
    int xli = (int)xl >> 16;
    int count = (int)((rd_ceil16(*e2) >> 16) - xli);
    int dx, r, t, v;

    *pxli = xli;
    if (count <= 0)
        return count;
    dx = (int)(xl - *e1);
    r = RD_RECIP(count);
    t = FMUL(e2[0xa] - e1[0xa], r);
    rd_uStep = SAR(t, rd_texShift);
    rd_u = SAR(FMUL(dx, t) + (int)e1[0xa], rd_texShift);
    t = FMUL(e2[0xc] - e1[0xc], r);
    rd_vStep = SAR(t, rd_texShift);
    v = SAR(FMUL(dx, t) + (int)e1[0xc], rd_texShift);
    rd_lStep = rd_clamp_step(FMUL(e2[0xe] - e1[0xe], r));
    rd_l = FMUL(dx, rd_lStep) + (int)e1[0xe];
    rd_u += rd_uOffset;
    rd_v = v + rd_vOffset;
    return count;
}

#define RD_STEP_UVL() (rd_u += rd_uStep, rd_v += rd_vStep, rd_l += rd_lStep)
/* light level index of rd_l for the 8 bit shade table (0x100 bytes per level) and the 16 bit palette */
#define LVL8()  (SAR(rd_l, 8) & 0x3f00)
#define LVL16() ((SAR(rd_l, 16) & 0x3f) << 8)

/* ==== rdRaster_Span_Tex_5 (0x0041fe90, with its loop tail FUN_0042003c) ====
 * 8 bit span, affine textured, Gouraud lit, blended: dst = light[shade[lvl + texel] * 0x100 + dst].
 * Ghidra split this function at 0x0042003c (FUN_0042003c is the inner loop); in the assembled build its two
 * branches between the parts were lost (ud2), so this C is the first working version of the pair. */
void rdRaster_Span_Tex_5(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uvl(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr8 = rd_dst8(param_1, xli);
    do {
        uint s = SHADE(LVL8() + rd_texel());
        *rd_ptr8 = LIGHT((s << 8) + *rd_ptr8);
        rd_ptr8++;
        RD_STEP_UVL();
    } while (--count != 0);
}

/* ==== rdRaster_Span16_Tex_8 (0x0041f2f0) ====
 * 16 bit span, affine textured, Gouraud lit: dst = pal16[lvl + texel]. */
void rdRaster_Span16_Tex_8(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uvl(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr16 = rd_dst16(param_1, xli);
    do {
        RD_PUT16(PAL16(LVL16() + rd_texel()));
        RD_STEP_UVL();
    } while (--count != 0);
}

/* ==== rdRaster_Span16_Tex_9 (0x004200c0) ====
 * 16 bit span, affine textured, Gouraud lit, blended with the 8 bit pixel at rd_ptr8 (not advanced):
 * dst = pal16[lvl + light[texel * 0x100 + texpal[*rd_ptr8]]]. */
void rdRaster_Span16_Tex_9(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uvl(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr16 = rd_dst16(param_1, xli);
    do {
        uint c = rd_texel();
        RD_PUT16(PAL16(LVL16() + LIGHT((c << 8) + TEXPAL(*rd_ptr8))));
        RD_STEP_UVL();
    } while (--count != 0);
}

/* ==== rdRaster_Span8_TexKey_2 (0x00420580) ====
 * 8 bit span, affine textured, Gouraud lit, colour key 0: dst = shade[lvl + texel]. */
void rdRaster_Span8_TexKey_2(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uvl(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr8 = rd_dst8(param_1, xli);
    do {
        uint8_t c = rd_texel();
        if (c != 0)
            *rd_ptr8 = SHADE(LVL8() + c);
        rd_ptr8++;
        RD_STEP_UVL();
    } while (--count != 0);
}

/* ==== rdRaster_Span_TexKey_4 (0x00420c80) ====
 * 8 bit span, affine textured, colour key 0, blended then lit: dst = shade[lvl + light[texel * 0x100 + dst]]. */
void rdRaster_Span_TexKey_4(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uvl(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr8 = rd_dst8(param_1, xli);
    do {
        uint8_t c = rd_texel();
        if (c != 0)
            *rd_ptr8 = SHADE(LVL8() + LIGHT(((uint)c << 8) + *rd_ptr8));
        rd_ptr8++;
        RD_STEP_UVL();
    } while (--count != 0);
}

/* ==== rdRaster_Span16_TexKey_4 (0x004207b0) ====
 * 16 bit span, affine textured, Gouraud lit, colour key 0: dst = pal16[lvl + texel]. */
void rdRaster_Span16_TexKey_4(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uvl(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr16 = rd_dst16(param_1, xli);
    do {
        uint8_t c = rd_texel();
        if (c != 0)
            *(uint16_t *)rd_ptr16 = PAL16(LVL16() + c);
        rd_ptr16 = (int *)((char *)rd_ptr16 + 2);
        RD_STEP_UVL();
    } while (--count != 0);
}

/* ==== rdRaster_Span16_TexKey_5 (0x00420ec0) ====
 * 16 bit span, affine textured, Gouraud lit, colour key 0, blended with the 8 bit pixel at rd_ptr8 (not advanced):
 * dst = pal16[lvl + light[texel * 0x100 + texpal[*rd_ptr8]]]. */
void rdRaster_Span16_TexKey_5(uint *param_1, uint *param_2)
{
    int xli, count = rd_setup_uvl(param_1, param_2, &xli);

    if (count <= 0)
        return;
    rd_ptr16 = rd_dst16(param_1, xli);
    do {
        uint8_t c = rd_texel();
        if (c != 0)
            *(uint16_t *)rd_ptr16 = PAL16(LVL16() + LIGHT(((uint)c << 8) + TEXPAL(*rd_ptr8)));
        rd_ptr16 = (int *)((char *)rd_ptr16 + 2);
        RD_STEP_UVL();
    } while (--count != 0);
}

/* ======================================================================================================
 * Edge stepping.  The polygon's screen vertices are g_pRdRasterVerts (x, y, z floats per vertex); the texture
 * coordinates UINT_007f4398 (u, v floats per vertex) and the light values UINT_007f4304 (one float per vertex) are
 * pointers to parallel arrays.  An edge function walks from vertex e[3] in the direction g_nRdRasterStepA or
 * g_nRdRasterStepB (wrapping around the polygon) until it finds an edge that covers at least one scanline, fills the
 * edge record (start values and per-scanline steps, 16.16) and returns 0; it returns 1 when it reaches
 * g_nRdRasterEndVertex.
 *
 * x87: the original rounds with the control words that Services_SetCurrent captured: DAT_0090052a (round up) for
 * frndint, DAT_00900526 (round down) for fistp, DAT_00900524 (the default) for everything else.  The helpers below do
 * the same instruction sequences; every intermediate value the original stores to a float is stored to a float
 * here (rd_f), everything it keeps on the x87 stack is a long double.
 * ====================================================================================================== */
static inline float rd_f(long double x)
{
    volatile float f = (float)x;
    return f;
}

/* fldcw [round up]; fld x; frndint; fstp float; fldcw [default] */
static inline float rd_ceilf(float x)
{
    float r;
    __asm__ volatile("fldcw %2\n\tflds %1\n\tfrndint\n\tfstps %0\n\tfldcw %3"
                     : "=m"(r) : "m"(x), "m"(DAT_0090052a), "m"(DAT_00900524));
    return r;
}

/* fldcw [round down]; fld x; fistp int; fldcw [default] */
static inline int rd_floori(float x)
{
    int r;
    __asm__ volatile("fldcw %2\n\tflds %1\n\tfistpl %0\n\tfldcw %3"
                     : "=m"(r) : "m"(x), "m"(DAT_00900526), "m"(DAT_00900524));
    return r;
}

#define RD_UV(i)  (((float *)U32(UINT_007f4398))[i])
#define RD_LV(i)  (((float *)U32(UINT_007f4304))[i])

/* next vertex index in the given direction, wrapping around the polygon */
static inline int rd_edge_next(int cur, int dir)
{
    int n = dir + cur;
    if (n < 0)
        return g_nRdRasterVertCount - 1;
    return n > g_nRdRasterVertCount - 1 ? 0 : n;
}

/* one interpolated attribute of an edge: slope d (on the x87 stack) and d rounded to a float; the step is
 * d * 65536, the start value (float(d) * dy + a0) * 65536, both rounded down */
static inline float rd_edge_attr(long double d, float dy, float a0, int *start, int *step, float *pstart)
{
    float s = rd_f(d);
    long double t;

    *step = rd_floori(rd_f(d * 65536.0L));
    t = (long double)s * dy + a0;
    if (pstart)
        *pstart = rd_f(t);      /* the perspective edges keep the start x as a float (fst) */
    *start = rd_floori(rd_f(t * 65536.0L));
    return s;
}

#define EDGE_STEPB 1  /* walk with g_nRdRasterStepB (else g_nRdRasterStepA) */
#define EDGE_ROWDY 2  /* sub-scanline offset = integer row - y (else rounded-up y - y) */
#define EDGE_DIV   4  /* x slope by a division (else times 1 / dy) */
#define EDGE_UV    8  /* texture coordinates: e[10] / e[11] u, e[12] / e[13] v */
#define EDGE_L     16 /* light: e[14] / e[15] */
#define EDGE_XEXT  32 /* the x slope uses 1 / dy before it is rounded to a float (the others use the float) */
#define EDGE_PERSP 64 /* perspective: also the three plane values e[4], e[6], e[8] (floats) and their steps */

/* plane equations of the perspective attributes: value = vertex value + dx * gx + dy * gy */
#define RDF(g)        (*(float *)&(g))
#define RD_PL0(i)     (((float *)&UINT_007f43c8)[i])
#define RD_PL1(i)     (((float *)&UINT_007f4260)[i])
#define RD_PL2(i)     (((float *)&UINT_007f4310)[i])

static int rd_edge(int *e, int flags)
{
    int cur = e[3], next, n;
    float yc, dy, inv, *v, s, xs;
    long double dxs;

    if (cur == g_nRdRasterEndVertex)
        return 1;
    for (;;) {
        next = rd_edge_next(cur, (flags & EDGE_STEPB) ? g_nRdRasterStepB : g_nRdRasterStepA);
        yc = rd_ceilf(g_pRdRasterVerts[cur * 3 + 1]);
        e[0x10] = rd_floori(yc);
        n = rd_floori(rd_ceilf(g_pRdRasterVerts[next * 3 + 1])) - e[0x10];
        e[2] = n;
        if (n > 0)
            break;
        cur = next;
        if (next == g_nRdRasterEndVertex)
            return 1;
    }
    v = g_pRdRasterVerts;
    if (flags & EDGE_ROWDY)
        dy = rd_f((long double)e[0x10] - v[cur * 3 + 1]);
    else
        dy = rd_f((long double)yc - v[cur * 3 + 1]);
    if (n < 2) {
        /* a single scanline: start values only */
        xs = v[cur * 3];
        e[0] = rd_floori(rd_f(v[cur * 3] * 65536.0L));
        if (flags & EDGE_UV) {
            e[10] = rd_floori(rd_f(RD_UV(cur * 2) * 65536.0L));
            e[12] = rd_floori(rd_f(RD_UV(cur * 2 + 1) * 65536.0L));
        }
        if (flags & EDGE_L)
            e[14] = rd_floori(rd_f(RD_LV(cur) * 65536.0L));
    } else {
        if (flags & EDGE_DIV) {
            s = rd_edge_attr(((long double)v[next * 3] - v[cur * 3]) / ((long double)v[next * 3 + 1] - v[cur * 3 + 1]),
                             dy, v[cur * 3], &e[0], &e[1], &xs);
        } else {
            long double inv_x = 1.0L / ((long double)v[next * 3 + 1] - v[cur * 3 + 1]);
            inv = rd_f(inv_x);
            if (!(flags & EDGE_XEXT))
                inv_x = inv;
            s = rd_edge_attr(((long double)v[next * 3] - v[cur * 3]) * inv_x, dy, v[cur * 3], &e[0], &e[1], &xs);
        }
        if (flags & EDGE_PERSP) {
            /* per-scanline steps of the plane values */
            ((float *)e)[5] = rd_f((long double)s * RDF(DAT_008ddef4) + RDF(DAT_008ddef0));
            ((float *)e)[7] = rd_f((long double)s * RDF(DAT_008ddec8) + RDF(DAT_008ddec4));
            ((float *)e)[9] = rd_f((long double)s * RDF(DAT_008ddedc) + RDF(DAT_008ddee0));
        }
        if (flags & EDGE_UV) {
            rd_edge_attr(((long double)RD_UV(next * 2) - RD_UV(cur * 2)) * inv, dy, RD_UV(cur * 2), &e[10], &e[11], 0);
            rd_edge_attr(((long double)RD_UV(next * 2 + 1) - RD_UV(cur * 2 + 1)) * inv, dy, RD_UV(cur * 2 + 1),
                         &e[12], &e[13], 0);
        }
        if (flags & EDGE_L)
            rd_edge_attr(((long double)RD_LV(next) - RD_LV(cur)) * inv, dy, RD_LV(cur), &e[14], &e[15], 0);
    }
    if (flags & EDGE_PERSP) {
        /* plane values at the start of the edge: dx is the rounded start x minus the vertex x */
        dxs = (long double)xs - v[cur * 3];
        ((float *)e)[4] = rd_f((long double)dy * RDF(DAT_008ddef0) + dxs * RDF(DAT_008ddef4) + RD_PL0(cur));
        ((float *)e)[6] = rd_f((long double)dy * RDF(DAT_008ddec4) + dxs * RDF(DAT_008ddec8) + RD_PL1(cur));
        ((float *)e)[8] = rd_f((long double)dy * RDF(DAT_008ddee0) + dxs * RDF(DAT_008ddedc) + RD_PL2(cur));
    }
    e[3] = next;
    return 0;
}

/* ==== the edge functions: x only ==== */
/* rdRaster_Edge_Flat_4 (0x0041a130), _14 (0x00421dc0), _16 (0x00425a00): x, slope by division */
undefined4 rdRaster_Edge_Flat_4(int *param_1) { return rd_edge(param_1, EDGE_STEPB | EDGE_DIV); }
undefined4 rdRaster_Edge_Flat_14(int *param_1) { return rd_edge(param_1, EDGE_STEPB | EDGE_DIV); }
undefined4 rdRaster_Edge_Flat_16(int *param_1) { return rd_edge(param_1, EDGE_STEPB | EDGE_DIV); }

/* ==== x and light ==== */
/* rdRaster_Edge_Flat_5 (0x0041aa10), _18 (0x00429b70); _6 (0x0041ac60) measures the sub-scanline offset from the
 * integer row */
undefined4 rdRaster_Edge_Flat_5(int *param_1) { return rd_edge(param_1, EDGE_L); }
undefined4 rdRaster_Edge_Flat_6(int *param_1) { return rd_edge(param_1, EDGE_STEPB | EDGE_ROWDY | EDGE_L); }
undefined4 rdRaster_Edge_Flat_18(int *param_1) { return rd_edge(param_1, EDGE_STEPB | EDGE_L); }

/* ==== x and texture coordinates ==== */
/* rdRaster_Edge_Flat_7 (0x0041ba30), _8 (0x0041bd20); _9 (0x0041d710), _10 (0x0041da00) keep 1 / dy unrounded for x */
undefined4 rdRaster_Edge_Flat_7(int *param_1) { return rd_edge(param_1, EDGE_UV); }
undefined4 rdRaster_Edge_Flat_8(int *param_1) { return rd_edge(param_1, EDGE_STEPB | EDGE_UV); }
undefined4 rdRaster_Edge_Flat_9(int *param_1) { return rd_edge(param_1, EDGE_UV | EDGE_XEXT); }
undefined4 rdRaster_Edge_Flat_10(int *param_1) { return rd_edge(param_1, EDGE_STEPB | EDGE_UV | EDGE_XEXT); }

/* ==== perspective: x and the three plane values (1 / z and the texture coordinates over z) ==== */
/* rdRaster_Edge_Flat_13 (0x00421b60), _15 (0x004257a0): slope by division; _17 (0x00429870): times 1 / dy, plus light */
undefined4 rdRaster_Edge_Flat_13(int *param_1) { return rd_edge(param_1, EDGE_DIV | EDGE_PERSP); }
undefined4 rdRaster_Edge_Flat_15(int *param_1) { return rd_edge(param_1, EDGE_DIV | EDGE_PERSP); }
undefined4 rdRaster_Edge_Flat_17(int *param_1) { return rd_edge(param_1, EDGE_PERSP | EDGE_L); }

/* ==== x, texture coordinates and light ==== */
/* rdRaster_Edge_Flat_11 (0x0041f520), _12 (0x0041f890), 1 / dy unrounded for x */
undefined4 rdRaster_Edge_Flat_11(int *param_1) { return rd_edge(param_1, EDGE_UV | EDGE_L | EDGE_XEXT); }
undefined4 rdRaster_Edge_Flat_12(int *param_1) { return rd_edge(param_1, EDGE_STEPB | EDGE_UV | EDGE_L | EDGE_XEXT); }

/* ======================================================================================================
 * Polygon drawing.  param_1 is the polygon (+0x1c vertex count, +0x20 screen vertices, +0x24 texture coordinates,
 * +0x28 light values, +0x4c material with the colour tables at +0x330 (8 bit shade), +0x348 (16 bit palette),
 * +0x34c (texel to palette index), +0x50 winding, +0x64 the argument of the gradient set-up, +0x6c top vertex,
 * +0x70 bottom vertex); param_2 the face (+0x04 colour, +0x1c texture: +0x0c log2 width, +0x10 / +0x14 u / v masks,
 * +0x18 mip count, +0x1c mip levels with +0x18 width and +0x5c texels); param_3 (some variants) the light level.
 * Two edges (A: first argument of the span, B: second) are walked down from the top vertex; after each scanline the
 * edge whose scanlines are used up is refetched, the other one is stepped.
 * ====================================================================================================== */
typedef undefined4 (*rd_edge_fn)(int *);
typedef void (*rd_span_fn)(uint *, uint *);

#define DS_L      1   /* step the light value of both edges */
#define DS_UV     2   /* step the texture coordinates of both edges */
#define DS_PLANE  4   /* step the three perspective plane values (floats) of edge A */
#define DS_PTR    8   /* call the span through the pointer UINT_007f42f8 */

static void rd_draw_step(int *e, int steps, int isA)
{
    e[0] += e[1];
    if (steps & DS_UV) {
        e[10] += e[11];
        e[12] += e[13];
    }
    if (steps & DS_L)
        e[14] += e[15];
    if ((steps & DS_PLANE) && isA) {
        ((float *)e)[4] = rd_f((long double)((float *)e)[4] + ((float *)e)[5]);
        ((float *)e)[6] = rd_f((long double)((float *)e)[6] + ((float *)e)[7]);
        ((float *)e)[8] = rd_f((long double)((float *)e)[8] + ((float *)e)[9]);
    }
    e[0x10]++;
}

/* ptr16: when not 0, UINT_007f42f8 is set (after both edges were found) to Mem_DumpLog (an empty function: the
 * 8 bit variants of these spans were left out of 1.01) for 8 bit or ptr16 for 16 bit targets */
static void rd_draw(int bpp, rd_edge_fn edgeA, rd_edge_fn edgeB, rd_span_fn span8, rd_span_fn span16,
                    rd_span_fn ptr16, int steps)
{
    int a[0x11], b[0x11];

    a[3] = g_nRdRasterStartVertex;
    if (edgeA(a))
        return;
    b[3] = g_nRdRasterStartVertex;
    if (edgeB(b))
        return;
    if (ptr16) {
        if (bpp == 8)
            U32(UINT_007f42f8) = (uint)(uintptr_t)Mem_DumpLog;
        else if (bpp == 0x10)
            U32(UINT_007f42f8) = (uint)(uintptr_t)ptr16;
    }
    for (;;) {
        if (steps & DS_PTR)
            ((rd_span_fn)(uintptr_t)U32(UINT_007f42f8))((uint *)a, (uint *)b);
        else if (bpp == 8)
            span8((uint *)a, (uint *)b);
        else if (bpp == 0x10)
            span16((uint *)a, (uint *)b);
        if (--a[2] == 0) {
            if (edgeA(a))
                return;
        } else {
            rd_draw_step(a, steps, 1);
        }
        if (--b[2] == 0) {
            if (edgeB(b))
                return;
        } else {
            rd_draw_step(b, steps, 0);
        }
    }
}

#define RD_BPP()       (*(int *)(RD_CANVAS() + 0x24))
#define RD_MAT(p1)     (*(int *)((p1) + 0x4c))
#define RD_TEXHDR(p2)  (*(int *)((p2) + 0x1c))

/* polygon globals common to all variants */
static void rd_draw_poly(int p1)
{
    g_nRdRasterStartVertex = *(int *)(p1 + 0x6c);
    g_nRdRasterEndVertex = *(int *)(p1 + 0x70);
    if (*(int *)(p1 + 0x50) == 0) {
        g_nRdRasterStepA = 1;
        g_nRdRasterStepB = -1;
    } else {
        g_nRdRasterStepA = -1;
        g_nRdRasterStepB = 1;
    }
}

#define TS_WIDTH  1   /* also UINT_008ddeb4 = width of the mip level */
#define TS_PERSP  2   /* also the gradients times 16 (the perspective spans step 16 pixels at a time) */

/* texture globals after the gradient set-up (rdRaster_Grad_Flat / _2 chose the mip level UINT_008ddee4) */
static void rd_draw_tex(int p2, int flags)
{
    int hdr = RD_TEXHDR(p2);
    int mip = rd_texShift;

    rd_pTex = *(uint *)(*(int *)(hdr + 0x1c + mip * 4) + 0x5c);
    rd_vShift = *(int *)(hdr + 0xc) - mip;
    if (flags & TS_WIDTH)
        U32(UINT_008ddeb4) = *(uint *)(*(int *)(hdr + 0x1c + mip * 4) + 0x18);
    rd_uMask = (int)((*(uint *)(hdr + 0x10) >> (mip & 31)) << 16);
    rd_vMask = (int)((*(uint *)(hdr + 0x14) >> (mip & 31)) << (rd_vShift & 31));
    if (flags & TS_PERSP) {
        RDF(DAT_008ddeec) = rd_f((long double)RDF(DAT_008ddef4) * 16.0L);
        RDF(DAT_008dded0) = rd_f((long double)RDF(DAT_008ddec8) * 16.0L);
        RDF(DAT_008ddf00) = rd_f((long double)RDF(DAT_008ddedc) * 16.0L);
    }
}

/* the gradient set-up takes the raw 4 bytes at polygon +0x64 (a float) */
#define RD_GRAD(fn, p1)  (((void (*)(undefined4))(void *)(fn))(*(undefined4 *)((p1) + 100)))

/* textured set-up shared by most variants (order as in the original) */
static void rd_draw_texpoly(int p1, int p2, int uv, int light)
{
    U32(UINT_007f4250) = *(int *)(RD_TEXHDR(p2) + 0x18) - 1;
    g_pRdRasterVerts = *(float **)(p1 + 0x20);
    if (uv)
        U32(UINT_007f4398) = *(uint *)(p1 + 0x24);
    if (light)
        U32(UINT_007f4304) = *(uint *)(p1 + 0x28);
}

/* ==== rdRaster_Draw_FlatLit (0x0041a640) ==== Gouraud lit colour (8 / 16 bit) */
void rdRaster_Draw_FlatLit(int param_1, int param_2)
{
    int bpp;

    rd_level = *(uint8_t *)(param_2 + 4);
    bpp = RD_BPP();
    g_pRdRasterVerts = *(float **)(param_1 + 0x20);
    U32(UINT_007f4304) = *(uint *)(param_1 + 0x28);
    g_nRdRasterVertCount = *(int *)(param_1 + 0x1c);
    if (bpp == 8)
        rd_pShade = *(uint *)(RD_MAT(param_1) + 0x330);
    else if (bpp == 0x10)
        rd_pPal16 = *(uint *)(RD_MAT(param_1) + 0x348);
    rd_draw_poly(param_1);
    rd_draw(bpp, rdRaster_Edge_Flat_5, rdRaster_Edge_Flat_6, rdRaster_Span8_Flat, rdRaster_Span16_Flat_3, 0, DS_L);
}

/* 16 bit colour of the face: word of the palette at level 0x3f, its palette index and the level byte */
static void rd_face_colour16(int p1, int p2)
{
    rd_pPal16 = *(uint *)(RD_MAT(p1) + 0x348);
    R16(DAT_008ddeb8) = *(uint16_t *)(*(int *)(RD_MAT(p1) + 0x348) + 0x7e00 + *(int *)(p2 + 4) * 2);
    rd_pTexPal = *(uint *)(RD_MAT(p1) + 0x34c);
    rd_level = *(uint8_t *)(rd_pTexPal + R16(DAT_008ddeb8));
}

/* ==== rdRaster_Draw16_TexLit_3 (0x0041aeb0) ==== Gouraud lit, translucent colour (remaps the frame buffer) */
void rdRaster_Draw16_TexLit_3(int param_1, int param_2)
{
    int bpp = RD_BPP();

    if (bpp == 8) {
        rd_level = *(uint8_t *)(param_2 + 4);
        rd_pShade = *(uint *)(RD_MAT(param_1) + 0x330);
    } else if (bpp == 0x10) {
        rd_face_colour16(param_1, param_2);
    }
    g_pRdRasterVerts = *(float **)(param_1 + 0x20);
    U32(UINT_007f4304) = *(uint *)(param_1 + 0x28);
    g_nRdRasterVertCount = *(int *)(param_1 + 0x1c);
    rd_pLight = *(uint *)(U32(UINT_004f5ec4) + 0x338);
    rd_draw_poly(param_1);
    rd_draw(bpp, rdRaster_Edge_Flat_5, rdRaster_Edge_Flat_6, rdRaster_Span_Tex_2, rdRaster_Span16_Tex_3, 0, DS_L);
}

/* ==== rdRaster_Draw16_TexLit_2 (0x0041a2f0) ==== translucent colour at the light level param_3 (rounded down) */
void rdRaster_Draw16_TexLit_2(int param_1, int param_2, float param_3)
{
    int bpp = RD_BPP();

    if (bpp == 8) {
        rd_level = *(uint8_t *)(*(int *)(param_2 + 4) + *(int *)(RD_MAT(param_1) + 0x330) + rd_floori(param_3) * 0x100);
    } else if (bpp == 0x10) {
        rd_pPal16 = *(int *)(RD_MAT(param_1) + 0x348) + 0x7e00;
        R16(DAT_008ddeb8) = *(uint16_t *)(*(int *)(RD_MAT(param_1) + 0x348) +
                                          (*(int *)(param_2 + 4) + rd_floori(param_3) * 0x100) * 2);
        rd_pTexPal = *(uint *)(RD_MAT(param_1) + 0x34c);
        rd_level = *(uint8_t *)(rd_pTexPal + R16(DAT_008ddeb8));
    }
    g_pRdRasterVerts = *(float **)(param_1 + 0x20);
    g_nRdRasterVertCount = *(int *)(param_1 + 0x1c);
    rd_pLight = *(uint *)(U32(UINT_004f5ec4) + 0x338);
    rd_draw_poly(param_1);
    rd_draw(bpp, rdRaster_Edge_Flat_3, rdRaster_Edge_Flat_4, rdRaster_Span_Tex, rdRaster_Span16_Tex_2, 0, 0);
}

/* Affine textured variants with rdRaster_Grad_Flat.  pal7e00: 16 bit palette at level 0x3f (unlit);
 * texpal: also UINT_008dded4; light: also UINT_008ddea8. */
static void rd_draw_affine_unlit(int p1, int p2, int texpal, int light, int width)
{
    int bpp = RD_BPP();

    if (bpp == 0x10) {
        rd_pPal16 = *(int *)(RD_MAT(p1) + 0x348) + 0x7e00;
        if (texpal)
            rd_pTexPal = *(uint *)(RD_MAT(p1) + 0x34c);
    }
    rd_draw_texpoly(p1, p2, 1, 0);
    g_nRdRasterVertCount = *(int *)(p1 + 0x1c);
    rd_draw_poly(p1);
    if (light)
        rd_pLight = *(uint *)(U32(UINT_004f5ec4) + 0x338);
    RD_GRAD(rdRaster_Grad_Flat, p1);
    rd_draw_tex(p2, width ? TS_WIDTH : 0);
}

/* ==== rdRaster_Draw16_TexLitKey (0x0041c5e0) ==== affine textured, colour key, unlit */
void rdRaster_Draw16_TexLitKey(int param_1, int param_2)
{
    rd_draw_affine_unlit(param_1, param_2, 0, 0, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_7, rdRaster_Edge_Flat_8, rdRaster_Span_FlatKey, rdRaster_Span16_TexKey, 0,
            DS_UV);
}

/* ==== rdRaster_Draw16_TexLit_5 (0x0041c010) ==== affine textured, blended */
void rdRaster_Draw16_TexLit_5(int param_1, int param_2)
{
    rd_draw_affine_unlit(param_1, param_2, 1, 1, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_7, rdRaster_Edge_Flat_8, rdRaster_Span_Tex_3, rdRaster_Span16_Tex_5, 0, DS_UV);
}

/* ==== rdRaster_Draw16_TexLitKey_2 (0x0041cb80) ==== affine textured, colour key, blended */
void rdRaster_Draw16_TexLitKey_2(int param_1, int param_2)
{
    rd_draw_affine_unlit(param_1, param_2, 1, 1, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_7, rdRaster_Edge_Flat_8, rdRaster_Span_TexKey, rdRaster_Span16_TexKey_2, 0,
            DS_UV);
}

/* ==== rdRaster_Draw16_TexLit_4 (0x0041b310) ==== affine textured, unlit; sets the span pointer as well */
void rdRaster_Draw16_TexLit_4(int param_1, int param_2)
{
    rd_draw_affine_unlit(param_1, param_2, 0, 0, 1);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_7, rdRaster_Edge_Flat_8, rdRaster_Span_Flat_2, rdRaster_Span16_Tex_4,
            rdRaster_Span16_Tex_4, DS_UV);
}

/* Set-up of the other textured variants. */
#define SU_LARR   1   /* light values per vertex (UINT_007f4304) */
#define SU_LEVEL  2   /* colour tables at the light level param_3: shade + level * 0x100, palette + level * 0x200 */
#define SU_TEXPAL 4   /* also UINT_008dded4 (16 bit) */
#define SU_LIGHT  8   /* also the light table UINT_008ddea8 */
#define SU_WIDTH  16  /* also UINT_008ddeb4 */
#define SU_PERSP  32  /* rdRaster_Grad_Flat_2 and the gradients times 16 (else rdRaster_Grad_Flat) */
#define SU_PAL3F  64  /* 16 bit palette at level 0x3f (+0x7e00), no 8 bit shade table */

static void rd_draw_setup(int p1, int p2, int flags, float p3)
{
    int bpp = RD_BPP();

    rd_draw_texpoly(p1, p2, 1, flags & SU_LARR);
    if (flags & SU_PAL3F) {
        if (bpp == 0x10) {
            rd_pPal16 = *(int *)(RD_MAT(p1) + 0x348) + 0x7e00;
            if (flags & SU_TEXPAL)
                rd_pTexPal = *(uint *)(RD_MAT(p1) + 0x34c);
        }
    } else if (bpp == 8) {
        rd_pShade = *(int *)(RD_MAT(p1) + 0x330) + ((flags & SU_LEVEL) ? rd_floori(p3) * 0x100 : 0);
    } else if (bpp == 0x10) {
        rd_pPal16 = *(int *)(RD_MAT(p1) + 0x348) + ((flags & SU_LEVEL) ? rd_floori(p3) * 0x200 : 0);
        if (flags & SU_TEXPAL)
            rd_pTexPal = *(uint *)(RD_MAT(p1) + 0x34c);
    }
    if (flags & SU_LIGHT)
        rd_pLight = *(uint *)(U32(UINT_004f5ec4) + 0x338);
    g_nRdRasterVertCount = *(int *)(p1 + 0x1c);
    rd_draw_poly(p1);
    if (flags & SU_PERSP)
        RD_GRAD(rdRaster_Grad_Flat_2, p1);
    else
        RD_GRAD(rdRaster_Grad_Flat, p1);
    rd_draw_tex(p2, ((flags & SU_WIDTH) ? TS_WIDTH : 0) | ((flags & SU_PERSP) ? TS_PERSP : 0));
}

/* ---- affine textured, edges with texture coordinates (rdRaster_Edge_Flat_9 / _10), level param_3 ---- */

/* ==== rdRaster_Draw_TexLitKey (0x0041e300) ==== colour key, shaded */
void rdRaster_Draw_TexLitKey(int param_1, int param_2, float param_3)
{
    rd_draw_setup(param_1, param_2, SU_LEVEL, param_3);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_9, rdRaster_Edge_Flat_10, rdRaster_Span8_TexKey, rdRaster_Span16_TexKey_3, 0,
            DS_UV);
}

/* ==== rdRaster_Draw16_TexLit_6 (0x0041dcf0) ==== shaded, blended */
void rdRaster_Draw16_TexLit_6(int param_1, int param_2, float param_3)
{
    rd_draw_setup(param_1, param_2, SU_LEVEL | SU_TEXPAL | SU_LIGHT, param_3);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_9, rdRaster_Edge_Flat_10, rdRaster_Span_Tex_4, rdRaster_Span16_Tex_7, 0, DS_UV);
}

/* ==== rdRaster_Draw_TexLitKey_2 (0x0041e8d0) ==== colour key, blended (16 bit: rdRaster_Span_TexKey_3) */
void rdRaster_Draw_TexLitKey_2(int param_1, int param_2, float param_3)
{
    rd_draw_setup(param_1, param_2, SU_LEVEL | SU_TEXPAL | SU_LIGHT, param_3);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_9, rdRaster_Edge_Flat_10, rdRaster_Span_TexKey_2, rdRaster_Span_TexKey_3, 0,
            DS_UV);
}

/* ==== rdRaster_Draw_FlatLit_2 (0x0041d180) ==== span through the pointer: nothing (8 bit), rdRaster_Span16_Tex_6 */
void rdRaster_Draw_FlatLit_2(int param_1, int param_2, float param_3)
{
    rd_draw_setup(param_1, param_2, SU_LEVEL | SU_WIDTH, param_3);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_9, rdRaster_Edge_Flat_10, 0, 0, rdRaster_Span16_Tex_6, DS_UV | DS_PTR);
}

/* ---- affine textured and Gouraud lit (rdRaster_Edge_Flat_11 / _12) ---- */

/* ==== rdRaster_Draw_TexLitKey_3 (0x00420310) ==== colour key */
void rdRaster_Draw_TexLitKey_3(int param_1, int param_2)
{
    rd_draw_setup(param_1, param_2, SU_LARR, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_11, rdRaster_Edge_Flat_12, rdRaster_Span8_TexKey_2, rdRaster_Span16_TexKey_4,
            0, DS_UV | DS_L);
}

/* ==== rdRaster_Draw16_TexLit_7 (0x0041fc00) ==== blended */
void rdRaster_Draw16_TexLit_7(int param_1, int param_2)
{
    rd_draw_setup(param_1, param_2, SU_LARR | SU_TEXPAL | SU_LIGHT, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_11, rdRaster_Edge_Flat_12, rdRaster_Span_Tex_5, rdRaster_Span16_Tex_9, 0,
            DS_UV | DS_L);
}

/* ==== rdRaster_Draw16_TexLitKey_3 (0x004209f0) ==== colour key, blended */
void rdRaster_Draw16_TexLitKey_3(int param_1, int param_2)
{
    rd_draw_setup(param_1, param_2, SU_LARR | SU_TEXPAL | SU_LIGHT, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_11, rdRaster_Edge_Flat_12, rdRaster_Span_TexKey_4, rdRaster_Span16_TexKey_5,
            0, DS_UV | DS_L);
}

/* ==== rdRaster_Draw_FlatLit_3 (0x0041eef0) ==== span through the pointer: nothing (8 bit), rdRaster_Span16_Tex_8 */
void rdRaster_Draw_FlatLit_3(int param_1, int param_2)
{
    rd_draw_setup(param_1, param_2, SU_LARR | SU_WIDTH, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_11, rdRaster_Edge_Flat_12, 0, 0, rdRaster_Span16_Tex_8, DS_UV | DS_L | DS_PTR);
}

/* ---- perspective textured (rdRaster_Grad_Flat_2, edges with the plane values; the spans are assembled) ---- */

/* ==== rdRaster_Draw16_TexLitKey_4 (0x00422f00) ==== */
void rdRaster_Draw16_TexLitKey_4(int param_1, int param_2)
{
    rd_draw_setup(param_1, param_2, SU_PAL3F | SU_PERSP, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_13, rdRaster_Edge_Flat_14, rdRaster_Span_FlatKey_2, rdRaster_Span16_TexKey_6,
            0, DS_PLANE);
}

/* ==== rdRaster_Draw16_TexLit_8 (0x00421f80) ==== */
void rdRaster_Draw16_TexLit_8(int param_1, int param_2)
{
    rd_draw_setup(param_1, param_2, SU_PAL3F | SU_TEXPAL | SU_LIGHT | SU_PERSP, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_13, rdRaster_Edge_Flat_14, rdRaster_Span_Tex_6, rdRaster_Span16_Tex_11, 0,
            DS_PLANE);
}

/* ==== rdRaster_Draw16_TexLitKey_5 (0x00423db0) ==== */
void rdRaster_Draw16_TexLitKey_5(int param_1, int param_2)
{
    rd_draw_setup(param_1, param_2, SU_PAL3F | SU_TEXPAL | SU_LIGHT | SU_PERSP, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_13, rdRaster_Edge_Flat_14, rdRaster_Span_TexKey_5, rdRaster_Span16_TexKey_7,
            0, DS_PLANE);
}

/* ==== rdRaster_Draw_FlatLit_4 (0x00421120) ==== span through the pointer: nothing (8 bit), rdRaster_Span16_Tex_10 */
void rdRaster_Draw_FlatLit_4(int param_1, int param_2)
{
    rd_draw_setup(param_1, param_2, SU_PAL3F | SU_WIDTH | SU_PERSP, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_13, rdRaster_Edge_Flat_14, 0, 0, rdRaster_Span16_Tex_10, DS_PLANE | DS_PTR);
}

/* level param_3 (rdRaster_Edge_Flat_15 / _16) */

/* ==== rdRaster_Draw_TexLitKey_4 (0x00426bc0) ==== */
void rdRaster_Draw_TexLitKey_4(int param_1, int param_2, float param_3)
{
    rd_draw_setup(param_1, param_2, SU_LEVEL | SU_PERSP, param_3);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_15, rdRaster_Edge_Flat_16, rdRaster_Span8_TexKey_3, rdRaster_Span16_TexKey_8,
            0, DS_PLANE);
}

/* ==== rdRaster_Draw16_TexLit_9 (0x00425bc0) ==== */
void rdRaster_Draw16_TexLit_9(int param_1, int param_2, float param_3)
{
    rd_draw_setup(param_1, param_2, SU_LEVEL | SU_TEXPAL | SU_LIGHT | SU_PERSP, param_3);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_15, rdRaster_Edge_Flat_16, rdRaster_Span_Tex_7, rdRaster_Span16_Tex_13, 0,
            DS_PLANE);
}

/* ==== rdRaster_Draw16_TexLitKey_6 (0x00427ae0) ==== */
void rdRaster_Draw16_TexLitKey_6(int param_1, int param_2, float param_3)
{
    rd_draw_setup(param_1, param_2, SU_LEVEL | SU_TEXPAL | SU_LIGHT | SU_PERSP, param_3);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_15, rdRaster_Edge_Flat_16, rdRaster_Span_TexKey_6, rdRaster_Span16_TexKey_9,
            0, DS_PLANE);
}

/* ==== rdRaster_Draw_FlatLit_5 (0x00424d50) ==== span through the pointer: nothing (8 bit), rdRaster_Span16_Tex_12 */
void rdRaster_Draw_FlatLit_5(int param_1, int param_2, float param_3)
{
    rd_draw_setup(param_1, param_2, SU_LEVEL | SU_WIDTH | SU_PERSP, param_3);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_15, rdRaster_Edge_Flat_16, 0, 0, rdRaster_Span16_Tex_12, DS_PLANE | DS_PTR);
}

/* Gouraud lit (rdRaster_Edge_Flat_17 / _18) */

/* ==== rdRaster_Draw_TexLitKey_5 (0x0042af60) ==== */
void rdRaster_Draw_TexLitKey_5(int param_1, int param_2)
{
    rd_draw_setup(param_1, param_2, SU_LARR | SU_PERSP, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_17, rdRaster_Edge_Flat_18, rdRaster_Span8_TexKey_4, rdRaster_Span16_TexKey_10,
            0, DS_L | DS_PLANE);
}

/* ==== rdRaster_Draw16_TexLit_10 (0x00429dc0) ==== */
void rdRaster_Draw16_TexLit_10(int param_1, int param_2)
{
    rd_draw_setup(param_1, param_2, SU_LARR | SU_TEXPAL | SU_LIGHT | SU_PERSP, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_17, rdRaster_Edge_Flat_18, rdRaster_Span_Tex_8, rdRaster_Span16_Tex_15, 0,
            DS_L | DS_PLANE);
}

/* ==== rdRaster_Draw_FlatLit_6 (0x00428ae0) ==== span through the pointer: nothing (8 bit), rdRaster_Span16_Tex_14 */
void rdRaster_Draw_FlatLit_6(int param_1, int param_2)
{
    rd_draw_setup(param_1, param_2, SU_LARR | SU_WIDTH | SU_PERSP, 0);
    rd_draw(RD_BPP(), rdRaster_Edge_Flat_17, rdRaster_Edge_Flat_18, 0, 0, rdRaster_Span16_Tex_14, DS_L | DS_PLANE | DS_PTR);
}

#endif /* GRIM_EXE */
