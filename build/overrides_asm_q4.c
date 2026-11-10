/* Readable C for the z-buffered RDroid software rasteriser (agent q4; see docs/notes/asm_q4.md).
 *
 * Every function here replaces original 1.01 machine code (src/GRIMFANDANGO.EXE/asm_funcs.s as of 2df265d) and is
 * checked against it by the differential test in build/difftest/asm_q4/ (original bytes and this C on the same random
 * polygons, edges and spans, under the x87 precision controls 24, 53 and 64 bits; frame buffer, z-buffer, edge records,
 * rasteriser globals, x87 control word and stack compared).
 *
 * The pipeline (one polygon, called from rdCache through the per-mode driver):
 *   Draw_*      the driver: copies the polygon's arrays and the mode tables into the rasteriser globals, computes
 *               1/(z+1) per vertex (g_dwRdZRaster_aOneOverZ), optionally Grad_* (texture mip level and gradient direction
 *               flags), then walks a left and a right edge record down the polygon and calls the span filler per row.
 *   SpanR_*     the edge set-up: advance an edge record to the next vertex pair that spans at least one scan line,
 *               and compute the 16.16 start / step of x, u, v, light and the float start / step of 1/(z+1).
 *   Span8/16_*  the span filler: one scan line from the left to the right edge, z-buffered (unsigned 16-bit compare,
 *               the nearer pixel has the larger value), 8 bpp (palette index) or 16 bpp.
 *
 * The edge record (q4_edge, 0x44 bytes, on the driver's stack): x, dx (16.16), h (scan lines left), idx (current
 * vertex), z, dz (float 1/(z+1)), 4 dwords the perspective variants use, u, du, v, dv, l, dl (16.16), y (scan line).
 *
 * x87 conventions (as in build/overrides_asm_p2.c):
 *   - `long double` holds a value the original keeps on the x87 stack; q4_f() is a store of it to a float slot (FSTP
 *     m32) through a volatile, so it is rounded at that point at every optimisation level.
 *   - The original converts with `fldcw floor; fld m32; fistp m32; fldcw default` and rounds up with
 *     `fldcw ceil; fld m32; frndint; fstp m32; fldcw default`.  q4_floor_i / q4_ceil do the same with SSE4.1 ROUNDSS
 *     (+ CVTTSS2SI), exactly what build/peephole.py turns those sequences into in the assembled build: the operand is
 *     a float, floor/ceil of a float is exact, and an out-of-range or NaN value gives 0x80000000 in both.
 *   - A float the original copies with MOV is copied as a dword (q4_u32), so a NaN keeps its bits.
 *
 * Speed: this is the hot loop of a frame, so the file is compiled at -O2 (the pragma below; build/link.py compiles
 * override files without -O).  -fno-strict-aliasing because the records are read as int and float. */
#pragma GCC optimize("O2", "no-strict-aliasing", "no-omit-frame-pointer")
#pragma GCC target("sse4.1")
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include <smmintrin.h>

/* ---- the rasteriser globals (names as in globals.h; not included, the types here are the ones the code needs) ---- */
extern int g_dwRdZRaster_numVertices;            /* vertex count of the polygon */
extern int g_dwRdZRaster_maxMipMap;            /* geometry / texture mode (Grad_*: mip selection) */
extern int g_dwRdZRaster_yMinVert;            /* start vertex (top) */
extern int g_dwRdZRaster_leftVertexStep;            /* left edge direction (+1 / -1) */
extern void *UINT_007f44f0;          /* span filler chosen by the textured drivers */
extern int g_dwRdZRaster_yMaxVert;            /* end vertex (bottom) */
extern float *g_dwRdZRaster_aIntensities;         /* per-vertex light */
extern float *g_pRdZRaster_aVertices;          /* screen vertices x, y, z (12 bytes each) */
extern int g_dwRdZRaster_rightVertexStep;            /* right edge direction */
extern float *g_dwRdZRaster_aTexVertices;         /* per-vertex u, v */
extern float g_dwRdZRaster_aOneOverZ[];        /* per-vertex 1 / (z + 1) */
extern unsigned char *g_dwRdZRaster_aRGBToPalette; /* 16 bpp colour -> palette index */
extern unsigned short *g_dwRdZRaster_aRGBMap;/* light table, 16 bpp (64 rows of 256) */
extern unsigned char *g_dwRdZRaster_aMonoMap; /* light table, 8 bpp */
extern unsigned short g_wRdZRaster_RGBcolor;  /* flat colour, 16 bpp */
extern unsigned char *g_dwRdZRaster_aAlphaMap; /* translucency table (256 x 256) */
extern unsigned char g_bRdZRaster_color;   /* flat colour, 8 bpp (palette index) */
extern int g_dwRdZRaster_zScaleShift;            /* z-buffer shift */
extern int g_aRdRaster_OneOverNFixed[];           /* 65536 / n (span length) */
extern float g_dwRdRaster_aOneOverNFlex[];        /* 1.0f / n */
extern char *g_dwRdColormap_pCurMap;          /* the colormap; +0x338: the translucency table */
extern char *g_pRdCamera_CurCamera;     /* 0x007f0fc8; +4: the canvas (+4 colour buffer, +0x10 z-buffer, +0x14 z shift) */
extern int g_dwRdZRaster_uWrap;            /* texture u mask << 16 */
extern int g_dwRdZRaster_dVdXModifier;            /* v rounding bias (0x8000 / 0x7fff, Grad_*) */
extern int g_dwRdZRaster_mipMapNum;            /* mip level (Grad_*) */
extern int g_dwRdZRaster_vWrap;            /* texture v mask << log2 width */
extern int g_dwRdZRaster_texPitch;            /* width of the mip level (selects the C span filler) */
extern int g_dwRdZRaster_dUdXModifier;            /* u rounding bias */
extern unsigned char *g_dwRdZRaster_pPixels; /* texels of the mip level */
extern int g_dwRdZRaster_texRowShift;            /* log2 width of the mip level */
extern float DAT_004dda90, g_aRdroid_MipDistances, DAT_004dda98;  /* mip distance thresholds (10, 20, 40) */
extern void Mem_DumpLog(void);       /* an empty function: the 8 bpp "span filler" of the FlatLit drivers */

typedef struct q4_edge {
    int x, dx, h, idx;
    float z, dz;
    int p18, p1c, p20, p24;
    int u, du, v, dv, l, dl, y;
} q4_edge;

typedef int (*q4_edge_fn)(q4_edge *);
typedef void (*q4_span_fn)(q4_edge *, q4_edge *);

#define Q4_I(p, off) (*(int *)((char *)(p) + (off)))
#define Q4_VX(i) (g_pRdZRaster_aVertices[(i) * 3])
#define Q4_VY(i) (g_pRdZRaster_aVertices[(i) * 3 + 1])
#define Q4_VZ(i) (g_pRdZRaster_aVertices[(i) * 3 + 2])
#define Q4_U(i) (g_dwRdZRaster_aTexVertices[(i) * 2])
#define Q4_V(i) (g_dwRdZRaster_aTexVertices[(i) * 2 + 1])
#define Q4_LT(i) (g_dwRdZRaster_aIntensities[i])
#define Q4_ZI(i) (g_dwRdZRaster_aOneOverZ[i])
#define q4_u32(f) (*(int *)&(f))
/* the helpers below are always inlined: the pragma's -O2 alone does not inline them into the macro-made functions */
#define Q4_INLINE static inline __attribute__((always_inline))

Q4_INLINE float q4_f(long double x)
{
    volatile float f = (float)x;
    return f;
}

/* fldcw floor; fld m32; fistp m32 */
Q4_INLINE int q4_floor_i(float f)
{
    __m128 v = _mm_set_ss(f);
    return _mm_cvttss_si32(_mm_round_ss(v, v, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC));
}

/* fldcw ceil; fld m32; frndint; fstp m32 */
Q4_INLINE float q4_ceil(float f)
{
    __m128 v = _mm_set_ss(f);
    return _mm_cvtss_f32(_mm_round_ss(v, v, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC));
}

/* the float FLD / FSTP copy of a vertex y the edge set-up makes before rounding it (quiets a signalling NaN) */
Q4_INLINE float q4_copy(float f)
{
    return q4_f((long double)f);
}

/* imul; shrd EAX,EDX,0x10: bits 16..47 of the 64-bit product */
Q4_INLINE int q4_mul16(int a, int b)
{
    return (int)((long long)a * b >> 16);
}

/* next vertex of an edge: i + dir, wrapping to 0 past the last vertex and to n - 1 below 0 */
Q4_INLINE int q4_next(int i, int dir)
{
    int n = i + dir;
    if (n < 0)
        return g_dwRdZRaster_numVertices - 1;
    return n > g_dwRdZRaster_numVertices - 1 ? 0 : n;
}

/* ==== SpanR_Flat .. SpanR_Flat_12: the affine edge set-up ====
 * Returns 1 when the edge reached the end vertex (the polygon is done), else 0 with the record set up for the next
 * vertex pair that covers at least one scan line.  Per tried pair the record's y (first scan line, ceil of the vertex
 * y) and h (scan lines) are written.  One scan line: x (and u, v, l) are the vertex values * 65536 floored, z is the
 * vertex 1/(z+1) copied as a dword, the steps are left as they were.  More: inv = 1 / (y1 - y0) and
 * sub = ceil(y0) - y0 as floats; per attribute a: t = (a1 - a0) * inv (extended), step = floor(float(t * 65536)),
 * start = floor(float((float(t) * sub + a0) * 65536)); dz = float((z1 - z0) * inv) and z = float(sub * dz' + z0) with the
 * unrounded dz'.  UV / LIT select the attributes; DIR the direction global (left / right edge). */
#define Q4_EDGE_FN(NAME, DIR, UV, LIT)                                                                      \
int NAME(q4_edge *e)                                                                                        \
{                                                                                                           \
    int i = e->idx, n, h;                                                                                   \
    float cy, sub, inv;                                                                                     \
    long double t, dz;                                                                                      \
    if (i == g_dwRdZRaster_yMaxVert)                                                                                 \
        return 1;                                                                                           \
    for (;;) {                                                                                              \
        n = q4_next(i, DIR);                                                                                \
        cy = q4_ceil(q4_copy(Q4_VY(i)));                                                                    \
        e->y = q4_floor_i(cy);                                                                              \
        h = q4_floor_i(q4_ceil(q4_copy(Q4_VY(n)))) - e->y;                                                  \
        e->h = h;                                                                                           \
        if (h > 0)                                                                                          \
            break;                                                                                          \
        i = n;                                                                                              \
        if (n == g_dwRdZRaster_yMaxVert)                                                                             \
            return 1;                                                                                       \
    }                                                                                                       \
    if (h < 2) {                                                                                            \
        e->x = q4_floor_i(q4_f(Q4_VX(i) * 65536.0f));                                                       \
        if (UV) {                                                                                           \
            e->u = q4_floor_i(q4_f(Q4_U(i) * 65536.0f));                                                    \
            e->v = q4_floor_i(q4_f(Q4_V(i) * 65536.0f));                                                    \
        }                                                                                                   \
        if (LIT)                                                                                            \
            e->l = q4_floor_i(q4_f(Q4_LT(i) * 65536.0f));                                                   \
        q4_u32(e->z) = q4_u32(Q4_ZI(i));                                                                    \
        e->idx = n;                                                                                         \
        return 0;                                                                                           \
    }                                                                                                       \
    sub = q4_f((long double)cy - Q4_VY(i));                                                                 \
    inv = q4_f(1.0L / ((long double)Q4_VY(n) - Q4_VY(i)));                                                  \
    Q4_ATTR(e->x, e->dx, Q4_VX(n), Q4_VX(i));                                                               \
    if (UV) {                                                                                               \
        Q4_ATTR(e->u, e->du, Q4_U(n), Q4_U(i));                                                             \
        Q4_ATTR(e->v, e->dv, Q4_V(n), Q4_V(i));                                                             \
    }                                                                                                       \
    if (LIT)                                                                                                \
        Q4_ATTR(e->l, e->dl, Q4_LT(n), Q4_LT(i));                                                           \
    dz = ((long double)Q4_ZI(n) - Q4_ZI(i)) * inv;                                                          \
    e->dz = q4_f(dz);                                                                                       \
    e->z = q4_f(sub * dz + Q4_ZI(i));                                                                       \
    e->idx = n;                                                                                             \
    return 0;                                                                                               \
}
#define Q4_ATTR(start, step, a1, a0)                                                                        \
    do {                                                                                                    \
        float tf_;                                                                                          \
        t = ((long double)(a1) - (a0)) * inv;                                                               \
        tf_ = q4_f(t);                                                                                      \
        (step) = q4_floor_i(q4_f(t * 65536.0f));                                                            \
        (start) = q4_floor_i(q4_f(((long double)tf_ * sub + (a0)) * 65536.0f));                            \
    } while (0)

/* OVERRIDES: rdZRaster_SetupLeftEdgeNGonLS */
Q4_EDGE_FN(rdZRaster_SetupLeftEdgeNGonLS, g_dwRdZRaster_leftVertexStep, 0, 0)
/* OVERRIDES: rdZRaster_SetupRightEdgeNGonLS */
Q4_EDGE_FN(rdZRaster_SetupRightEdgeNGonLS, g_dwRdZRaster_rightVertexStep, 0, 0)
/* OVERRIDES: rdZRaster_SetupLeftEdgeNGonFS */
Q4_EDGE_FN(rdZRaster_SetupLeftEdgeNGonFS, g_dwRdZRaster_leftVertexStep, 0, 0)
/* OVERRIDES: rdZRaster_SetupRightEdgeNGonFS */
Q4_EDGE_FN(rdZRaster_SetupRightEdgeNGonFS, g_dwRdZRaster_rightVertexStep, 0, 0)
/* OVERRIDES: rdZRaster_SetupLeftEdgeNGonGS */
Q4_EDGE_FN(rdZRaster_SetupLeftEdgeNGonGS, g_dwRdZRaster_leftVertexStep, 0, 1)
/* OVERRIDES: rdZRaster_SetupRightEdgeNGonGS */
Q4_EDGE_FN(rdZRaster_SetupRightEdgeNGonGS, g_dwRdZRaster_rightVertexStep, 0, 1)
/* OVERRIDES: rdZRaster_SetupLeftEdgeNGonLAT */
Q4_EDGE_FN(rdZRaster_SetupLeftEdgeNGonLAT, g_dwRdZRaster_leftVertexStep, 1, 0)
/* OVERRIDES: rdZRaster_SetupRightEdgeNGonLAT */
Q4_EDGE_FN(rdZRaster_SetupRightEdgeNGonLAT, g_dwRdZRaster_rightVertexStep, 1, 0)
/* OVERRIDES: rdZRaster_SetupLeftEdgeNGonFAT */
Q4_EDGE_FN(rdZRaster_SetupLeftEdgeNGonFAT, g_dwRdZRaster_leftVertexStep, 1, 0)
/* OVERRIDES: rdZRaster_SetupRightEdgeNGonFAT */
Q4_EDGE_FN(rdZRaster_SetupRightEdgeNGonFAT, g_dwRdZRaster_rightVertexStep, 1, 0)
/* OVERRIDES: rdZRaster_SetupLeftEdgeNGonGAT */
Q4_EDGE_FN(rdZRaster_SetupLeftEdgeNGonGAT, g_dwRdZRaster_leftVertexStep, 1, 1)
/* OVERRIDES: rdZRaster_SetupRightEdgeNGonGAT */
Q4_EDGE_FN(rdZRaster_SetupRightEdgeNGonGAT, g_dwRdZRaster_rightVertexStep, 1, 1)

/* ==== the span prologue shared by the fillers ====
 * The span covers the pixel columns xl .. xr - 1 with xl = ceil(L.x), xr = ceil(R.x) (16.16; xr as unsigned >> 16);
 * nothing when xr - xl <= 0.  sub = float((xl_fixed - L.x) * 2^-16) is the distance from the edge to the first pixel
 * centre column.  z: t = (R.z - L.z) * (1/n from the table at 0x008fe000), dz = floor(float(t * 65536)),
 * z = floor(float((float(t) * sub + L.z) * 65536)).  Light (LIT): dl = (R.l - L.l) * (65536/n) >> 16, set to 0 when it
 * is in -1309 .. -1, l = (xl_fixed - L.x) * dl >> 16 + L.l.  The pixel row is L.y; the colour buffer is the canvas'
 * +4 (pitch +0x18, pixels +0x5c), the z-buffer its +0x10; a pixel is drawn when (z >> shift) as an unsigned short is
 * greater than the z-buffer value, which it then replaces. */
#define Q4_SPAN_PROLOGUE(LIT)                                                                               \
    int x0 = L->x, xs = (x0 & 0xffff) ? (x0 + 0x10000) & 0xffff0000 : x0;                                   \
    int xl = xs >> 16, xr = R->x, n, z, dz, frac, l = 0, dl = 0;                                            \
    float sub;                                                                                              \
    long double t;                                                                                          \
    char *c4;                                                                                               \
    if (xr & 0xffff)                                                                                        \
        xr = (xr + 0x10000) & 0xffff0000;                                                                   \
    n = (int)((unsigned)xr >> 16) - xl;                                                                     \
    if (n <= 0)                                                                                             \
        return;                                                                                             \
    frac = xs - x0;                                                                                         \
    sub = q4_f((long double)frac * (1.0f / 65536.0f));                                                      \
    if (LIT) {                                                                                              \
        dl = q4_mul16(R->l - L->l, g_aRdRaster_OneOverNFixed[n]);                                                        \
        if (dl < 0 && dl > -0x51e)                                                                          \
            dl = 0;                                                                                         \
        l = q4_mul16(frac, dl) + L->l;                                                                      \
    }                                                                                                       \
    {                                                                                                       \
        float tf_;                                                                                          \
        t = ((long double)R->z - L->z) * g_dwRdRaster_aOneOverNFlex[n];                                                  \
        tf_ = q4_f(t);                                                                                      \
        dz = q4_floor_i(q4_f(t * 65536.0f));                                                                \
        z = q4_floor_i(q4_f(((long double)tf_ * sub + L->z) * 65536.0f));                                   \
    }                                                                                                       \
    c4 = *(char **)(g_pRdCamera_CurCamera + 4)

/* colour buffer row pointers; 16 bpp uses (pitch >> 1) * y + x pixels */
#define Q4_BUF8(c4, y, x) ((unsigned char *)(Q4_I(Q4_I(c4, 4), 0x5c) + Q4_I(Q4_I(c4, 4), 0x18) * (y) + (x)))
#define Q4_BUF16(c4, y, x)                                                                                  \
    ((unsigned short *)(Q4_I(Q4_I(c4, 4), 0x5c) + (((unsigned)Q4_I(Q4_I(c4, 4), 0x18) >> 1) * (y) + (x)) * 2))
#define Q4_ZBUF(c4, y, x) ((unsigned short *)(Q4_I(Q4_I(c4, 0x10), 0x5c) + Q4_I(Q4_I(c4, 0x10), 0x18) * (y) + (x) * 2))

/* the per-pixel loop: PIXEL writes *pix from the destination (and l), with zv the 16-bit depth */
#define Q4_SPAN_LOOP(PIXT, BUF, PIXEL, LIT)                                                                 \
    {                                                                                                       \
        PIXT *pix = BUF(c4, L->y, xl);                                                                      \
        unsigned short *zp = Q4_ZBUF(c4, L->y, xl);                                                         \
        int sh = g_dwRdZRaster_zScaleShift;                                                                             \
        do {                                                                                                \
            int zs = z >> sh;                                                                               \
            if ((unsigned short)zs > *zp) {                                                                 \
                PIXEL;                                                                                      \
                *zp = (unsigned short)zs;                                                                   \
            }                                                                                               \
            if (LIT)                                                                                        \
                l += dl;                                                                                    \
            pix++;                                                                                          \
            zp++;                                                                                           \
            z += dz;                                                                                        \
        } while (--n);                                                                                      \
    }

/* light row of a 16.16 light value: bits 16..21, times 256 */
#define Q4_LROW(l) ((((l) >> 16) & 0x3f) << 8)

/* ==== flat colour (Span8/16_FlatZ, _2) ==== */
#define Q4_SPAN_FLAT8(NAME)                                                                                 \
void NAME(q4_edge *L, q4_edge *R)                                                                           \
{                                                                                                           \
    Q4_SPAN_PROLOGUE(0);                                                                                    \
    Q4_SPAN_LOOP(unsigned char, Q4_BUF8, *pix = g_bRdZRaster_color, 0)                                            \
}
#define Q4_SPAN_FLAT16(NAME)                                                                                \
void NAME(q4_edge *L, q4_edge *R)                                                                           \
{                                                                                                           \
    Q4_SPAN_PROLOGUE(0);                                                                                    \
    Q4_SPAN_LOOP(unsigned short, Q4_BUF16, *pix = g_wRdZRaster_RGBcolor, 0)                                          \
}
/* OVERRIDES: rdZRaster_DrawScanLineNGonLS_8 */
Q4_SPAN_FLAT8(rdZRaster_DrawScanLineNGonLS_8)
/* OVERRIDES: rdZRaster_DrawScanLineNGonLS_16 */
Q4_SPAN_FLAT16(rdZRaster_DrawScanLineNGonLS_16)
/* OVERRIDES: rdZRaster_DrawScanLineNGonFS_8 */
Q4_SPAN_FLAT8(rdZRaster_DrawScanLineNGonFS_8)
/* OVERRIDES: rdZRaster_DrawScanLineNGonFS_16 */
Q4_SPAN_FLAT16(rdZRaster_DrawScanLineNGonFS_16)

/* ==== translucent flat colour (Span8/16_TexLitZ, _2): blend table [colour * 256 + destination index] ==== */
#define Q4_SPAN_TRANS8(NAME)                                                                                \
void NAME(q4_edge *L, q4_edge *R)                                                                           \
{                                                                                                           \
    Q4_SPAN_PROLOGUE(0);                                                                                    \
    Q4_SPAN_LOOP(unsigned char, Q4_BUF8, *pix = g_dwRdZRaster_aAlphaMap[g_bRdZRaster_color * 256 + *pix], 0)                \
}
#define Q4_SPAN_TRANS16(NAME)                                                                               \
void NAME(q4_edge *L, q4_edge *R)                                                                           \
{                                                                                                           \
    Q4_SPAN_PROLOGUE(0);                                                                                    \
    Q4_SPAN_LOOP(unsigned short, Q4_BUF16,                                                                  \
                 *pix = g_dwRdZRaster_aRGBMap[g_dwRdZRaster_aAlphaMap[g_bRdZRaster_color * 256 + g_dwRdZRaster_aRGBToPalette[*pix]]], 0)          \
}
/* OVERRIDES: rdZRaster_DrawScanLineNGonTLS_8 */
Q4_SPAN_TRANS8(rdZRaster_DrawScanLineNGonTLS_8)
/* OVERRIDES: rdZRaster_DrawScanLineNGonTLS_16 */
Q4_SPAN_TRANS16(rdZRaster_DrawScanLineNGonTLS_16)
/* OVERRIDES: rdZRaster_DrawScanLineNGonTFS_8 */
Q4_SPAN_TRANS8(rdZRaster_DrawScanLineNGonTFS_8)
/* OVERRIDES: rdZRaster_DrawScanLineNGonTFS_16 */
Q4_SPAN_TRANS16(rdZRaster_DrawScanLineNGonTFS_16)

/* ==== lit flat colour (Span8/16_FlatZ_3): light table [light row + colour] ==== */
/* OVERRIDES: rdZRaster_DrawScanLineNGonGS_8 */
void rdZRaster_DrawScanLineNGonGS_8(q4_edge *L, q4_edge *R)
{
    Q4_SPAN_PROLOGUE(1);
    Q4_SPAN_LOOP(unsigned char, Q4_BUF8, *pix = g_dwRdZRaster_aMonoMap[Q4_LROW(l) + g_bRdZRaster_color], 1)
}
/* OVERRIDES: rdZRaster_DrawScanLineNGonGS_16 */
void rdZRaster_DrawScanLineNGonGS_16(q4_edge *L, q4_edge *R)
{
    Q4_SPAN_PROLOGUE(1);
    Q4_SPAN_LOOP(unsigned short, Q4_BUF16, *pix = g_dwRdZRaster_aRGBMap[Q4_LROW(l) + g_bRdZRaster_color], 1)
}

/* ==== lit translucent flat colour (Span8/16_TexZ) ====
 * 8 bpp: blend[lit colour * 256 + destination]; 16 bpp: light table16[light row + blend[colour * 256 + index of the
 * destination]] (the light is applied after the blend). */
/* OVERRIDES: rdZRaster_DrawScanLineNGonTGS_8 */
void rdZRaster_DrawScanLineNGonTGS_8(q4_edge *L, q4_edge *R)
{
    Q4_SPAN_PROLOGUE(1);
    Q4_SPAN_LOOP(unsigned char, Q4_BUF8,
                 *pix = g_dwRdZRaster_aAlphaMap[g_dwRdZRaster_aMonoMap[Q4_LROW(l) + g_bRdZRaster_color] * 256 + *pix], 1)
}
/* OVERRIDES: rdZRaster_DrawScanLineNGonTGS_16 */
void rdZRaster_DrawScanLineNGonTGS_16(q4_edge *L, q4_edge *R)
{
    Q4_SPAN_PROLOGUE(1);
    Q4_SPAN_LOOP(unsigned short, Q4_BUF16,
                 *pix = g_dwRdZRaster_aRGBMap[Q4_LROW(l) + g_dwRdZRaster_aAlphaMap[g_bRdZRaster_color * 256 + g_dwRdZRaster_aRGBToPalette[*pix]]], 1)
}

/* ==== the drivers ==== */

/* the polygon record (Draw_* first argument) */
#define Q4_P_COUNT 0x1c
#define Q4_P_VERTS 0x20
#define Q4_P_UV 0x24
#define Q4_P_LIGHT 0x28
#define Q4_P_TABLES 0x4c  /* -> +0x330 light table 8 bpp, +0x348 light table 16 bpp, +0x34c 16 bpp -> index */
#define Q4_P_FLIP 0x50
#define Q4_P_TOP 0x6c
#define Q4_P_BOTTOM 0x70

/* bits per pixel of the colour buffer */
#define Q4_BPP() Q4_I(Q4_I(Q4_I(g_pRdCamera_CurCamera, 4), 4), 0x24)

/* 1/(z+1) per vertex: float(1 / (z - -1)) */
Q4_INLINE void q4_zinv(int cnt)
{
    int i;
    for (i = 0; i < cnt; i++)
        Q4_ZI(i) = q4_f(1.0L / ((long double)Q4_VZ(i) - -1.0f));
}

/* the common part of every driver's set-up: vertex arrays, top / bottom vertex, z shift, edge directions and the
 * 1/(z+1) array (float(1 / (z - -1)) per vertex) */
Q4_INLINE void q4_setup_common(char *p, int zinv)
{
    int i, cnt;
    g_pRdZRaster_aVertices = *(float **)(p + Q4_P_VERTS);
    g_dwRdZRaster_numVertices = cnt = Q4_I(p, Q4_P_COUNT);
    g_dwRdZRaster_yMinVert = Q4_I(p, Q4_P_TOP);
    g_dwRdZRaster_yMaxVert = Q4_I(p, Q4_P_BOTTOM);
    g_dwRdZRaster_zScaleShift = Q4_I(Q4_I(g_pRdCamera_CurCamera, 4), 0x14);
    if (Q4_I(p, Q4_P_FLIP)) {
        g_dwRdZRaster_leftVertexStep = -1;
        g_dwRdZRaster_rightVertexStep = 1;
    } else {
        g_dwRdZRaster_leftVertexStep = 1;
        g_dwRdZRaster_rightVertexStep = -1;
    }
    if (zinv)
        q4_zinv(cnt);
}

/* walk the two edges: one span per scan line, then step each edge (or set up its next vertex pair) */
#define Q4_WALK(EL, ER, SPAN, UV, LIT)                                                                      \
    do {                                                                                                    \
        q4_edge L, R;                                                                                       \
        L.idx = g_dwRdZRaster_yMinVert;                                                                              \
        if (EL(&L))                                                                                         \
            return;                                                                                         \
        R.idx = g_dwRdZRaster_yMinVert;                                                                              \
        if (ER(&R))                                                                                         \
            return;                                                                                         \
        for (;;) {                                                                                          \
            SPAN;                                                                                           \
            Q4_STEP(L, EL, UV, LIT);                                                                        \
            Q4_STEP(R, ER, UV, LIT);                                                                        \
        }                                                                                                   \
    } while (0)
#define Q4_STEP(E, EFN, UV, LIT)                                                                            \
    if (--E.h == 0) {                                                                                       \
        if (EFN(&E))                                                                                        \
            return;                                                                                         \
    } else {                                                                                                \
        E.x += E.dx;                                                                                        \
        E.z = q4_f((long double)E.z + E.dz);                                                                \
        if (UV) {                                                                                           \
            E.u += E.du;                                                                                    \
            E.v += E.dv;                                                                                    \
        }                                                                                                   \
        if (LIT)                                                                                            \
            E.l += E.dl;                                                                                    \
        E.y++;                                                                                              \
    }
/* the 8 / 16 bpp span call of the untextured drivers (nothing for another depth) */
#define Q4_SPAN_BPP(bpp, S8, S16)                                                                           \
    if ((bpp) == 8)                                                                                         \
        S8(&L, &R);                                                                                         \
    else if ((bpp) == 16)                                                                                   \
        S16(&L, &R)

/* ==== Draw_FlatLitZ: flat colour (the material's colour index; 16 bpp: light row 63 of the 16 bpp table) ==== */
/* OVERRIDES: rdZRaster_DrawNGonLS */
void rdZRaster_DrawNGonLS(char *p, char *mat)
{
    int bpp = Q4_BPP();
    if (bpp == 8)
        g_bRdZRaster_color = (unsigned char)Q4_I(mat, 4);
    else if (bpp == 16)
        g_wRdZRaster_RGBcolor = (*(unsigned short **)(*(char **)(p + Q4_P_TABLES) + 0x348))[*(unsigned char *)(mat + 4) + 0x3f00];
    q4_setup_common(p, 1);
    Q4_WALK(rdZRaster_SetupLeftEdgeNGonLS, rdZRaster_SetupRightEdgeNGonLS, Q4_SPAN_BPP(bpp, rdZRaster_DrawScanLineNGonLS_8, rdZRaster_DrawScanLineNGonLS_16),
            0, 0);
}

/* ==== Draw_FlatLitZ_2: flat colour at the polygon's light level (floor of the float argument) ==== */
/* OVERRIDES: rdZRaster_DrawNGonFS */
void rdZRaster_DrawNGonFS(char *p, char *mat, float light)
{
    int bpp = Q4_BPP();
    if (bpp == 8)
        g_bRdZRaster_color = (*(unsigned char **)(*(char **)(p + Q4_P_TABLES) + 0x330))[Q4_I(mat, 4) + q4_floor_i(light) * 256];
    else if (bpp == 16)
        g_wRdZRaster_RGBcolor = (*(unsigned short **)(*(char **)(p + Q4_P_TABLES) + 0x348))[Q4_I(mat, 4) + q4_floor_i(light) * 256];
    q4_setup_common(p, 1);
    Q4_WALK(rdZRaster_SetupLeftEdgeNGonFS, rdZRaster_SetupRightEdgeNGonFS,
            Q4_SPAN_BPP(bpp, rdZRaster_DrawScanLineNGonFS_8, rdZRaster_DrawScanLineNGonFS_16), 0, 0);
}

/* ==== Draw_FlatLitZ_3: flat colour, per-vertex light (gouraud) ==== */
/* OVERRIDES: rdZRaster_DrawNGonGS */
void rdZRaster_DrawNGonGS(char *p, char *mat)
{
    int bpp = Q4_BPP();
    g_bRdZRaster_color = *(unsigned char *)(mat + 4);
    g_dwRdZRaster_aIntensities = *(float **)(p + Q4_P_LIGHT);
    if (bpp == 8)
        g_dwRdZRaster_aMonoMap = *(unsigned char **)(*(char **)(p + Q4_P_TABLES) + 0x330);
    else if (bpp == 16)
        g_dwRdZRaster_aRGBMap = *(unsigned short **)(*(char **)(p + Q4_P_TABLES) + 0x348);
    q4_setup_common(p, 1);
    Q4_WALK(rdZRaster_SetupLeftEdgeNGonGS, rdZRaster_SetupRightEdgeNGonGS,
            Q4_SPAN_BPP(bpp, rdZRaster_DrawScanLineNGonGS_8, rdZRaster_DrawScanLineNGonGS_16), 0, 1);
}

/* translucency set-up of the Draw_TexLitZ drivers: 16 bpp -> 8 bpp index table and the colour's palette index */
Q4_INLINE void q4_trans16(char *p, unsigned short c16)
{
    g_dwRdZRaster_aRGBToPalette = *(unsigned char **)(*(char **)(p + Q4_P_TABLES) + 0x34c);
    g_bRdZRaster_color = g_dwRdZRaster_aRGBToPalette[c16];
}

/* ==== Draw_TexLitZ: translucent flat colour ==== */
/* OVERRIDES: rdZRaster_DrawNGonTLS */
void rdZRaster_DrawNGonTLS(char *p, char *mat)
{
    int bpp = Q4_BPP();
    if (bpp == 8)
        g_bRdZRaster_color = *(unsigned char *)(mat + 4);
    else if (bpp == 16) {
        unsigned short *t16 = *(unsigned short **)(*(char **)(p + Q4_P_TABLES) + 0x348);
        g_dwRdZRaster_aRGBMap = t16 + 0x3f00;
        g_wRdZRaster_RGBcolor = t16[Q4_I(mat, 4) + 0x3f00];
        q4_trans16(p, g_wRdZRaster_RGBcolor);
    }
    q4_setup_common(p, 1);
    g_dwRdZRaster_aAlphaMap = *(unsigned char **)(g_dwRdColormap_pCurMap + 0x338);
    Q4_WALK(rdZRaster_SetupLeftEdgeNGonLS, rdZRaster_SetupRightEdgeNGonLS,
            Q4_SPAN_BPP(bpp, rdZRaster_DrawScanLineNGonTLS_8, rdZRaster_DrawScanLineNGonTLS_16), 0, 0);
}

/* ==== Draw_TexLitZ_2: translucent flat colour at the polygon's light level ==== */
/* OVERRIDES: rdZRaster_DrawNGonTFS */
void rdZRaster_DrawNGonTFS(char *p, char *mat, float light)
{
    int bpp = Q4_BPP();
    if (bpp == 8)
        g_bRdZRaster_color = (*(unsigned char **)(*(char **)(p + Q4_P_TABLES) + 0x330))[Q4_I(mat, 4) + q4_floor_i(light) * 256];
    else if (bpp == 16) {
        unsigned short *t16 = *(unsigned short **)(*(char **)(p + Q4_P_TABLES) + 0x348);
        g_dwRdZRaster_aRGBMap = t16 + 0x3f00;
        g_wRdZRaster_RGBcolor = t16[Q4_I(mat, 4) + q4_floor_i(light) * 256];
        q4_trans16(p, g_wRdZRaster_RGBcolor);
    }
    q4_setup_common(p, 1);
    g_dwRdZRaster_aAlphaMap = *(unsigned char **)(g_dwRdColormap_pCurMap + 0x338);
    Q4_WALK(rdZRaster_SetupLeftEdgeNGonFS, rdZRaster_SetupRightEdgeNGonFS,
            Q4_SPAN_BPP(bpp, rdZRaster_DrawScanLineNGonTFS_8, rdZRaster_DrawScanLineNGonTFS_16), 0, 0);
}

/* ==== Draw_TexLitZ_3: translucent flat colour, per-vertex light ==== */
/* OVERRIDES: rdZRaster_DrawNGonTGS */
void rdZRaster_DrawNGonTGS(char *p, char *mat)
{
    int bpp = Q4_BPP();
    g_dwRdZRaster_aIntensities = *(float **)(p + Q4_P_LIGHT);
    if (bpp == 8) {
        g_bRdZRaster_color = *(unsigned char *)(mat + 4);
        g_dwRdZRaster_aMonoMap = *(unsigned char **)(*(char **)(p + Q4_P_TABLES) + 0x330);
    } else if (bpp == 16) {
        unsigned short *t16 = *(unsigned short **)(*(char **)(p + Q4_P_TABLES) + 0x348);
        g_dwRdZRaster_aRGBMap = t16;
        g_wRdZRaster_RGBcolor = t16[Q4_I(mat, 4) + 0x3f00];
        q4_trans16(p, g_wRdZRaster_RGBcolor);
    }
    g_dwRdZRaster_aAlphaMap = *(unsigned char **)(g_dwRdColormap_pCurMap + 0x338);
    q4_setup_common(p, 1);
    Q4_WALK(rdZRaster_SetupLeftEdgeNGonGS, rdZRaster_SetupRightEdgeNGonGS,
            Q4_SPAN_BPP(bpp, rdZRaster_DrawScanLineNGonTGS_8, rdZRaster_DrawScanLineNGonTGS_16), 0, 1);
}

/* ==== Grad_Flat_3: texture gradient set-up of the textured affine drivers ====
 * Picks three vertices a, b, c (for a triangle 0, 1, 2; otherwise a = top, b = bottom and c the vertex farthest in x
 * from the midpoint of a and b, searched from the top towards the side that is not the straight continuation: dir = -1
 * when the vertex after the top is less than 1 away (in y) from the line top -> bottom, else +1; when the vertex next
 * to the top in one direction is the bottom, the search goes the other way and c starts as the argument's bits (an
 * index the original would use if no vertex is farther than 0 from the midpoint)).  Fills 1/(z+1) per vertex, then
 * the u and v gradients of the plane through a, b, c (only their signs are used: the u / v rounding biases 0x8000 for
 * a positive x gradient, else 0x7fff for a negative one, and for 0 by the sign of the y gradient), and the mip level
 * from the argument (the polygon's distance) and the mode g_dwRdZRaster_maxMipMap (the texture's mip count - 1): mode 0 -> 0;
 * 1 -> 1 if d > 20; 2 -> 0 / 1 / 2 by d > 10, d > 20; 3 -> 0..3 by d > 10, 20, 40 (thresholds read from 0x004dda90..98;
 * a NaN compares as "not greater"); another mode leaves the level as it was.
 * x87: the plane gradients follow the original's operand order and store points: A = xa - xc, B = xb - xc,
 * C = ya - yc, D = yb - yc extended, A and B also as floats; R = 1 / (C * float(B) - D * float(A)); E, F (u) extended
 * and as floats, G, H (v) as floats; du/dx = float((E * C - F * D) * float(R)) with E, F extended, the other three use
 * the float E, F, G, H. */
/* OVERRIDES: rdZRaster_CalcAffineGradients */
void rdZRaster_CalcAffineGradients(int dbits)
{
    float dist = *(float *)&dbits;
    int cnt = g_dwRdZRaster_numVertices, a, b, c, dir, k;
    float *V = g_pRdZRaster_aVertices, *T;
    if (cnt == 3) {
        a = 0;
        b = 1;
        c = 2;
    } else {
        int start = g_dwRdZRaster_yMinVert, end = g_dwRdZRaster_yMaxVert;
        float mid, mx = 0.0f;
        a = start;
        b = end;
        if (q4_next(start, 1) == end) {
            c = dbits;
            dir = -1;
        } else if (q4_next(start, -1) == end) {
            c = dbits;
            dir = 1;
        } else {
            long double r, d;
            c = q4_next(start, 1);
            r = ((long double)V[end * 3 + 1] - V[start * 3 + 1]) / ((long double)V[end * 3] - V[start * 3]);
            d = V[c * 3 + 1] - (r * ((long double)V[c * 3] - V[start * 3]) + V[start * 3 + 1]);
            if (!(d >= 0.0L))
                d = -d;
            dir = d >= 1.0L ? 1 : -1;
        }
        mid = q4_f(((long double)V[start * 3] + V[end * 3]) * 0.5f);
        for (k = q4_next(start, dir); k != end; k = q4_next(k, dir)) {
            long double d = (long double)V[k * 3] - mid;
            if (!(d >= 0.0L))
                d = -d;
            if (d > mx) {
                mx = q4_f(d);
                c = k;
            }
        }
    }
    q4_zinv(cnt);
    {
        float *va = V + a * 3, *vb = V + b * 3, *vc = V + c * 3, *ta, *tb, *tc;
        long double A, B, C, D, R, E, F, G, H;
        float fA, fB, fR, fnR, fE, fF, fG, fH, dudx, dudy, dvdx, dvdy;
        T = g_dwRdZRaster_aTexVertices;
        ta = T + a * 2;
        tb = T + b * 2;
        tc = T + c * 2;
        A = (long double)va[0] - vc[0];
        B = (long double)vb[0] - vc[0];
        C = (long double)va[1] - vc[1];
        D = (long double)vb[1] - vc[1];
        fA = q4_f(A);
        fB = q4_f(B);
        R = 1.0f / (C * fB - D * fA);
        fR = q4_f(R);
        fnR = q4_f(-R);
        E = (long double)tb[0] - tc[0];
        F = (long double)ta[0] - tc[0];
        fE = q4_f(E);
        fF = q4_f(F);
        G = (long double)tb[1] - tc[1];
        H = (long double)ta[1] - tc[1];
        fG = q4_f(G);
        fH = q4_f(H);
        dudx = q4_f((E * C - F * D) * fR);
        dudy = q4_f(((long double)fE * fA - (long double)fF * fB) * fnR);
        dvdx = q4_f(((long double)fG * C - (long double)fH * D) * fR);
        dvdy = q4_f(((long double)fG * fA - (long double)fH * fB) * fnR);
        switch (g_dwRdZRaster_maxMipMap) {
        case 0:
            g_dwRdZRaster_mipMapNum = 0;
            break;
        case 1:
            g_dwRdZRaster_mipMapNum = dist > g_aRdroid_MipDistances ? 1 : 0;
            break;
        case 2:
            g_dwRdZRaster_mipMapNum = !(dist > DAT_004dda90) ? 0 : !(dist > g_aRdroid_MipDistances) ? 1 : 2;
            break;
        case 3:
            g_dwRdZRaster_mipMapNum = !(dist > DAT_004dda90) ? 0 : !(dist > g_aRdroid_MipDistances) ? 1 : !(dist > DAT_004dda98) ? 2 : 3;
            break;
        }
        if (dudx > 0.0f)
            g_dwRdZRaster_dUdXModifier = 0x8000;
        else if (!(dudx >= 0.0f) || !(dudy >= 0.0f))
            g_dwRdZRaster_dUdXModifier = 0x7fff;
        else
            g_dwRdZRaster_dUdXModifier = 0x8000;
        if (dvdx > 0.0f)
            g_dwRdZRaster_dVdXModifier = 0x8000;
        else if (!(dvdx >= 0.0f) || !(dvdy >= 0.0f))
            g_dwRdZRaster_dVdXModifier = 0x7fff;
        else
            g_dwRdZRaster_dVdXModifier = 0x8000;
    }
}

/* ==== the textured span fillers ====
 * As the flat ones, plus: u, v (16.16, from the edges) are stepped by (R - L) * (65536/n) >> 16 and start at
 * (xl_fixed - L.x) * step >> 16 + L, both shifted right by the mip level; then the rounding biases of Grad_* are added.
 * Light (LIT, gouraud) as in Q4_SPAN_PROLOGUE.  The texel is texels[(u >> 16 & umask) + (v >> (16 - log2 w) & vmask)]
 * (arithmetic shifts); KEY: texel 0 is transparent (neither pixel nor z written). */
#define Q4_TSPAN_PROLOGUE(LIT)                                                                              \
    int x0 = L->x, xs = (x0 & 0xffff) ? (x0 + 0x10000) & 0xffff0000 : x0;                                   \
    int xl = xs >> 16, xr = R->x, n, z, dz, frac, irn, u, du, v, dv, l = 0, dl = 0, mip;                    \
    float sub;                                                                                              \
    long double t;                                                                                          \
    char *c4;                                                                                               \
    if (xr & 0xffff)                                                                                        \
        xr = (xr + 0x10000) & 0xffff0000;                                                                   \
    n = (int)((unsigned)xr >> 16) - xl;                                                                     \
    if (n <= 0)                                                                                             \
        return;                                                                                             \
    frac = xs - x0;                                                                                         \
    irn = g_aRdRaster_OneOverNFixed[n];                                                                                  \
    sub = q4_f((long double)frac * (1.0f / 65536.0f));                                                      \
    mip = g_dwRdZRaster_mipMapNum & 31;                                                                               \
    du = q4_mul16(R->u - L->u, irn);                                                                        \
    u = (q4_mul16(frac, du) + L->u) >> mip;                                                                 \
    du >>= mip;                                                                                             \
    dv = q4_mul16(R->v - L->v, irn);                                                                        \
    v = (q4_mul16(frac, dv) + L->v) >> mip;                                                                 \
    dv >>= mip;                                                                                             \
    if (LIT) {                                                                                              \
        dl = q4_mul16(R->l - L->l, irn);                                                                    \
        if (dl < 0 && dl > -0x51e)                                                                          \
            dl = 0;                                                                                         \
        l = q4_mul16(frac, dl) + L->l;                                                                      \
    }                                                                                                       \
    {                                                                                                       \
        float tf_;                                                                                          \
        t = ((long double)R->z - L->z) * g_dwRdRaster_aOneOverNFlex[n];                                                  \
        tf_ = q4_f(t);                                                                                      \
        dz = q4_floor_i(q4_f(t * 65536.0f));                                                                \
        z = q4_floor_i(q4_f(((long double)tf_ * sub + L->z) * 65536.0f));                                   \
    }                                                                                                       \
    v += g_dwRdZRaster_dVdXModifier;                                                                                     \
    u += g_dwRdZRaster_dUdXModifier;                                                                                     \
    c4 = *(char **)(g_pRdCamera_CurCamera + 4)

#define Q4_TEXEL(u, v)                                                                                      \
    g_dwRdZRaster_pPixels[(((u) >> 16) & (g_dwRdZRaster_uWrap >> 16)) + (((v) >> ((16 - g_dwRdZRaster_texRowShift) & 31)) & g_dwRdZRaster_vWrap)]

/* PIXEL writes *pix from tx (the texel), the destination and l */
#define Q4_TSPAN_LOOP(PIXT, BUF, KEY, PIXEL, LIT)                                                           \
    {                                                                                                       \
        PIXT *pix = BUF(c4, L->y, xl);                                                                      \
        unsigned short *zp = Q4_ZBUF(c4, L->y, xl);                                                         \
        int sh = g_dwRdZRaster_zScaleShift;                                                                             \
        do {                                                                                                \
            int zs = z >> sh;                                                                               \
            if ((unsigned short)zs > *zp) {                                                                 \
                unsigned tx = Q4_TEXEL(u, v);                                                               \
                if (!(KEY) || tx) {                                                                         \
                    PIXEL;                                                                                  \
                    *zp = (unsigned short)zs;                                                               \
                }                                                                                           \
            }                                                                                               \
            pix++;                                                                                          \
            zp++;                                                                                           \
            z += dz;                                                                                        \
            u += du;                                                                                        \
            v += dv;                                                                                        \
            if (LIT)                                                                                        \
                l += dl;                                                                                    \
        } while (--n);                                                                                      \
    }

#define Q4_TSPAN(NAME, PIXT, BUF, LIT, KEY, PIXEL)                                                          \
void NAME(q4_edge *L, q4_edge *R)                                                                           \
{                                                                                                           \
    Q4_TSPAN_PROLOGUE(LIT);                                                                                 \
    Q4_TSPAN_LOOP(PIXT, BUF, KEY, PIXEL, LIT)                                                               \
}
#define Q4_TSPAN8(NAME, LIT, KEY, PIXEL) Q4_TSPAN(NAME, unsigned char, Q4_BUF8, LIT, KEY, PIXEL)
#define Q4_TSPAN16(NAME, LIT, KEY, PIXEL) Q4_TSPAN(NAME, unsigned short, Q4_BUF16, LIT, KEY, PIXEL)
#define Q4_BLEND(c, d) g_dwRdZRaster_aAlphaMap[(c) * 256 + (d)]

/* unlit (Draw_FlatLit_7 and friends; 16 bpp: light row 63 of the 16 bpp table) */
/* OVERRIDES: rdZRaster_DrawScanLineNGonLAT_8 */
Q4_TSPAN8(rdZRaster_DrawScanLineNGonLAT_8, 0, 0, *pix = tx)
/* OVERRIDES: rdZRaster_DrawScanLineNGonLAT_16 */
Q4_TSPAN16(rdZRaster_DrawScanLineNGonLAT_16, 0, 0, *pix = g_dwRdZRaster_aRGBMap[tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonTLAT_8 */
Q4_TSPAN8(rdZRaster_DrawScanLineNGonTLAT_8, 0, 0, *pix = Q4_BLEND(tx, *pix))
/* OVERRIDES: rdZRaster_DrawScanLineNGonTLAT_16 */
Q4_TSPAN16(rdZRaster_DrawScanLineNGonTLAT_16, 0, 0, *pix = g_dwRdZRaster_aRGBMap[Q4_BLEND(tx, g_dwRdZRaster_aRGBToPalette[*pix])])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMLAT_8 */
Q4_TSPAN8(rdZRaster_DrawScanLineNGonMLAT_8, 0, 1, *pix = tx)
/* OVERRIDES: rdZRaster_DrawScanLineNGonMLAT_16 */
Q4_TSPAN16(rdZRaster_DrawScanLineNGonMLAT_16, 0, 1, *pix = g_dwRdZRaster_aRGBMap[tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMTLAT_8 */
Q4_TSPAN8(rdZRaster_DrawScanLineNGonMTLAT_8, 0, 1, *pix = Q4_BLEND(tx, *pix))
/* OVERRIDES: rdZRaster_DrawScanLineNGonMTLAT_16 */
Q4_TSPAN16(rdZRaster_DrawScanLineNGonMTLAT_16, 0, 1, *pix = g_dwRdZRaster_aRGBMap[Q4_BLEND(tx, g_dwRdZRaster_aRGBToPalette[*pix])])

/* flat lit (Draw_FlatLit_8 and friends: the light tables point at the polygon's light row) */
/* OVERRIDES: rdZRaster_DrawScanLineNGonFAT_8 */
Q4_TSPAN8(rdZRaster_DrawScanLineNGonFAT_8, 0, 0, *pix = g_dwRdZRaster_aMonoMap[tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonFAT_16 */
Q4_TSPAN16(rdZRaster_DrawScanLineNGonFAT_16, 0, 0, *pix = g_dwRdZRaster_aRGBMap[tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonTFAT_8 */
Q4_TSPAN8(rdZRaster_DrawScanLineNGonTFAT_8, 0, 0, *pix = Q4_BLEND(g_dwRdZRaster_aMonoMap[tx], *pix))
/* the lit texel's palette index blended with the destination's, then lit again by the same row */
/* OVERRIDES: rdZRaster_DrawScanLineNGonTFAT_16 */
Q4_TSPAN16(rdZRaster_DrawScanLineNGonTFAT_16, 0, 0,
         *pix = g_dwRdZRaster_aRGBMap[Q4_BLEND(g_dwRdZRaster_aRGBToPalette[g_dwRdZRaster_aRGBMap[tx]], g_dwRdZRaster_aRGBToPalette[*pix])])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMFAT_8 */
Q4_TSPAN8(rdZRaster_DrawScanLineNGonMFAT_8, 0, 1, *pix = g_dwRdZRaster_aMonoMap[tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMFAT_16 */
Q4_TSPAN16(rdZRaster_DrawScanLineNGonMFAT_16, 0, 1, *pix = g_dwRdZRaster_aRGBMap[tx])
/* keyed translucent: blended first, then lit (the opaque translucent one lights first) */
/* OVERRIDES: rdZRaster_DrawScanLineNGonMTFAT_8 */
Q4_TSPAN8(rdZRaster_DrawScanLineNGonMTFAT_8, 0, 1, *pix = g_dwRdZRaster_aMonoMap[Q4_BLEND(tx, *pix)])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMTFAT_16 */
Q4_TSPAN16(rdZRaster_DrawScanLineNGonMTFAT_16, 0, 1, *pix = g_dwRdZRaster_aRGBMap[Q4_BLEND(tx, g_dwRdZRaster_aRGBToPalette[*pix])])

/* gouraud (Draw_FlatLit_9 and friends: light row per pixel) */
/* OVERRIDES: rdZRaster_DrawScanLineNGonGAT_8 */
Q4_TSPAN8(rdZRaster_DrawScanLineNGonGAT_8, 1, 0, *pix = g_dwRdZRaster_aMonoMap[Q4_LROW(l) + tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonTGAT_8 */
Q4_TSPAN8(rdZRaster_DrawScanLineNGonTGAT_8, 1, 0, *pix = Q4_BLEND(g_dwRdZRaster_aMonoMap[Q4_LROW(l) + tx], *pix))
/* OVERRIDES: rdZRaster_DrawScanLineNGonTGAT_16 */
Q4_TSPAN16(rdZRaster_DrawScanLineNGonTGAT_16, 1, 0, *pix = g_dwRdZRaster_aRGBMap[Q4_LROW(l) + Q4_BLEND(tx, g_dwRdZRaster_aRGBToPalette[*pix])])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMGAT_8 */
Q4_TSPAN8(rdZRaster_DrawScanLineNGonMGAT_8, 1, 1, *pix = g_dwRdZRaster_aMonoMap[Q4_LROW(l) + tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMGAT_16 */
Q4_TSPAN16(rdZRaster_DrawScanLineNGonMGAT_16, 1, 1, *pix = g_dwRdZRaster_aRGBMap[Q4_LROW(l) + tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMTGAT_8 */
Q4_TSPAN8(rdZRaster_DrawScanLineNGonMTGAT_8, 1, 1, *pix = g_dwRdZRaster_aMonoMap[Q4_LROW(l) + Q4_BLEND(tx, *pix)])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMTGAT_16 */
Q4_TSPAN16(rdZRaster_DrawScanLineNGonMTGAT_16, 1, 1,
         *pix = g_dwRdZRaster_aRGBMap[Q4_LROW(l) + Q4_BLEND(tx, g_dwRdZRaster_aRGBToPalette[*pix])])

/* ==== Span16_TexLitZ_4: gouraud, 16 bpp, ordered dither of the light ====
 * The light row is (l + dither) >> 16 (no 0..63 mask) with dither 0, 0xc000, 0x8000, 0x4000 by (column & 1) +
 * 2 * (row & 1); the column counts down from the span's last pixel while the pixels go left to right (as in the
 * original).  Texel 0 is drawn (no key).  The original takes the parities as C remainders (-1 for a negative
 * column / row, which then index below its 4-entry table on its stack); spans are on screen, so they are >= 0. */
static const int q4_dither[4] = {0, 0xc000, 0x8000, 0x4000};
/* OVERRIDES: rdZRaster_DrawScanLineNGonGAT_16 */
void rdZRaster_DrawScanLineNGonGAT_16(q4_edge *L, q4_edge *R)
{
    Q4_TSPAN_PROLOGUE(1);
    {
        unsigned short *pix = Q4_BUF16(c4, L->y, xl);
        unsigned short *zp = Q4_ZBUF(c4, L->y, xl);
        int sh = g_dwRdZRaster_zScaleShift, col = xl + n - 1, row2 = (L->y & 1) * 2;
        do {
            int zs = z >> sh;
            if ((unsigned short)zs > *zp) {
                unsigned tx = Q4_TEXEL(u, v);
                *pix = g_dwRdZRaster_aRGBMap[(((l + q4_dither[(col & 1) + row2]) >> 8) & ~0xff) + tx];
                *zp = (unsigned short)zs;
            }
            pix++;
            zp++;
            z += dz;
            u += du;
            v += dv;
            l += dl;
            col--;
        } while (--n);
    }
}

/* ==== the textured affine drivers (Draw_FlatLit_7..9, Draw_TexLitZ_4..6, Draw_TexLitKeyZw..._6) ====
 * LIGHT 0: unlit (16 bpp: row 63 of the light table), 1: the polygon's light level (floor of the float argument)
 * selects the row, 2: per-vertex light (gouraud).  TRANS: the translucency tables.  After Grad_Flat_3 the mip level
 * selects the texel array, its log2 width, and the u / v masks (texture record = material +0x1c: +0xc log2 width,
 * +0x10 width, +0x14 height, +0x18 mip count, +0x1c + 4 * level the level records: +0x18 width, +0x5c texels). */
Q4_INLINE void q4_tex_setup(char *p, char *mat, int light_mode, int trans, int opaque, int li)
{
    int bpp = Q4_BPP(), mip;
    char *tb = *(char **)(p + Q4_P_TABLES), *tex = *(char **)(mat + 0x1c), *lev;
    g_dwRdZRaster_maxMipMap = Q4_I(tex, 0x18) - 1;
    g_dwRdZRaster_aTexVertices = *(float **)(p + Q4_P_UV);
    if (light_mode == 2)
        g_dwRdZRaster_aIntensities = *(float **)(p + Q4_P_LIGHT);
    if (bpp == 8) {
        if (light_mode == 1)
            g_dwRdZRaster_aMonoMap = *(unsigned char **)(tb + 0x330) + (int)((unsigned)li << 8);
        else if (light_mode == 2)
            g_dwRdZRaster_aMonoMap = *(unsigned char **)(tb + 0x330);
    } else if (bpp == 16) {
        char *t16 = *(char **)(tb + 0x348);
        g_dwRdZRaster_aRGBMap = (unsigned short *)(light_mode == 0 ? t16 + 0x7e00
                                           : light_mode == 1 ? t16 + (int)((unsigned)li << 9) : t16);
        if (trans)
            g_dwRdZRaster_aRGBToPalette = *(unsigned char **)(tb + 0x34c);
    }
    if (trans)
        g_dwRdZRaster_aAlphaMap = *(unsigned char **)(g_dwRdColormap_pCurMap + 0x338);
    q4_setup_common(p, 0);
    rdZRaster_CalcAffineGradients(Q4_I(p, 0x64));
    mip = g_dwRdZRaster_mipMapNum;
    lev = *(char **)(tex + 0x1c + mip * 4);
    g_dwRdZRaster_pPixels = *(unsigned char **)(lev + 0x5c);
    g_dwRdZRaster_texRowShift = Q4_I(tex, 0xc) - mip;
    if (opaque)
        g_dwRdZRaster_texPitch = Q4_I(lev, 0x18);
    g_dwRdZRaster_uWrap = (int)(((unsigned)Q4_I(tex, 0x10) >> (mip & 31)) << 16);
    g_dwRdZRaster_vWrap = (int)(((unsigned)Q4_I(tex, 0x14) >> (mip & 31)) << (g_dwRdZRaster_texRowShift & 31));
}

/* the walk with a span filler chosen once after the first two edge set-ups (PRE) and called through UINT_007f44f0 */
#define Q4_WALK_PTR(EL, ER, PRE, UV, LIT)                                                                   \
    do {                                                                                                    \
        q4_edge L, R;                                                                                       \
        L.idx = g_dwRdZRaster_yMinVert;                                                                              \
        if (EL(&L))                                                                                         \
            return;                                                                                         \
        R.idx = g_dwRdZRaster_yMinVert;                                                                              \
        if (ER(&R))                                                                                         \
            return;                                                                                         \
        PRE;                                                                                                \
        for (;;) {                                                                                          \
            ((q4_span_fn)UINT_007f44f0)(&L, &R);                                                            \
            Q4_STEP(L, EL, UV, LIT);                                                                        \
            Q4_STEP(R, ER, UV, LIT);                                                                        \
        }                                                                                                   \
    } while (0)

/* the C span fillers (rdraster.c) the opaque drivers choose by texture width when the z shift is 0 */
#define Q4_CSPAN(n) extern void rdRaster_Span16_TexLitZw##n(q4_edge *, q4_edge *);
Q4_CSPAN() Q4_CSPAN(_2) Q4_CSPAN(_3) Q4_CSPAN(_4) Q4_CSPAN(_5) Q4_CSPAN(_6) Q4_CSPAN(_7) Q4_CSPAN(_8)
Q4_CSPAN(_15) Q4_CSPAN(_16) Q4_CSPAN(_17) Q4_CSPAN(_18) Q4_CSPAN(_19) Q4_CSPAN(_20) Q4_CSPAN(_21) Q4_CSPAN(_22)
Q4_CSPAN(_24) Q4_CSPAN(_25) Q4_CSPAN(_26) Q4_CSPAN(_27) Q4_CSPAN(_28) Q4_CSPAN(_29) Q4_CSPAN(_30)

/* span choice of the opaque drivers: with a z shift the filler of the depth; without, 8 bpp gets the empty
 * Mem_DumpLog and 16 bpp a C filler specialised for the texture width (W4 .. W256: widths 4, 8, ..., 256; D any
 * other); another depth keeps the previous pointer */
#define Q4_PICK(bpp, S8, S16, W4, W8, W16, W32, W64, W128, W256, D)                                         \
    if (g_dwRdZRaster_zScaleShift) {                                                                                    \
        if ((bpp) == 8)                                                                                     \
            UINT_007f44f0 = (void *)S8;                                                                     \
        else if ((bpp) == 16)                                                                               \
            UINT_007f44f0 = (void *)S16;                                                                    \
    } else if ((bpp) == 8)                                                                                  \
        UINT_007f44f0 = (void *)Mem_DumpLog;                                                                \
    else if ((bpp) == 16) {                                                                                 \
        switch (g_dwRdZRaster_texPitch) {                                                                            \
        case 4: UINT_007f44f0 = (void *)W4; break;                                                          \
        case 8: UINT_007f44f0 = (void *)W8; break;                                                          \
        case 16: UINT_007f44f0 = (void *)W16; break;                                                        \
        case 32: UINT_007f44f0 = (void *)W32; break;                                                        \
        case 64: UINT_007f44f0 = (void *)W64; break;                                                        \
        case 128: UINT_007f44f0 = (void *)W128; break;                                                      \
        case 256: UINT_007f44f0 = (void *)W256; break;                                                      \
        default: UINT_007f44f0 = (void *)D; break;                                                          \
        }                                                                                                   \
    }

/* OVERRIDES: rdZRaster_DrawNGonLAT */
void rdZRaster_DrawNGonLAT(char *p, char *mat)
{
    int bpp = Q4_BPP();
    q4_tex_setup(p, mat, 0, 0, 1, 0);
    Q4_WALK_PTR(rdZRaster_SetupLeftEdgeNGonLAT, rdZRaster_SetupRightEdgeNGonLAT,
                Q4_PICK(bpp, rdZRaster_DrawScanLineNGonLAT_8, rdZRaster_DrawScanLineNGonLAT_16, rdRaster_Span16_TexLitZw_24,
                        rdRaster_Span16_TexLitZw_25, rdRaster_Span16_TexLitZw_26, rdRaster_Span16_TexLitZw_27,
                        rdRaster_Span16_TexLitZw_28, rdRaster_Span16_TexLitZw_29, rdRaster_Span16_TexLitZw_30,
                        rdRaster_Span16_TexLitZw_24), 1, 0);
}
/* OVERRIDES: rdZRaster_DrawNGonFAT */
void rdZRaster_DrawNGonFAT(char *p, char *mat, float light)
{
    int bpp = Q4_BPP();
    q4_tex_setup(p, mat, 1, 0, 1, bpp == 8 || bpp == 16 ? q4_floor_i(light) : 0);
    Q4_WALK_PTR(rdZRaster_SetupLeftEdgeNGonFAT, rdZRaster_SetupRightEdgeNGonFAT,
                Q4_PICK(bpp, rdZRaster_DrawScanLineNGonFAT_8, rdZRaster_DrawScanLineNGonFAT_16, rdRaster_Span16_TexLitZw_16,
                        rdRaster_Span16_TexLitZw_17, rdRaster_Span16_TexLitZw_18, rdRaster_Span16_TexLitZw_19,
                        rdRaster_Span16_TexLitZw_20, rdRaster_Span16_TexLitZw_21, rdRaster_Span16_TexLitZw_22,
                        rdRaster_Span16_TexLitZw_15), 1, 0);
}
/* OVERRIDES: rdZRaster_DrawNGonGAT */
void rdZRaster_DrawNGonGAT(char *p, char *mat)
{
    int bpp = Q4_BPP();
    q4_tex_setup(p, mat, 2, 0, 1, 0);
    Q4_WALK_PTR(rdZRaster_SetupLeftEdgeNGonGAT, rdZRaster_SetupRightEdgeNGonGAT,
                Q4_PICK(bpp, rdZRaster_DrawScanLineNGonGAT_8, rdZRaster_DrawScanLineNGonGAT_16, rdRaster_Span16_TexLitZw_2,
                        rdRaster_Span16_TexLitZw_3, rdRaster_Span16_TexLitZw_4, rdRaster_Span16_TexLitZw_5,
                        rdRaster_Span16_TexLitZw_6, rdRaster_Span16_TexLitZw_7, rdRaster_Span16_TexLitZw_8,
                        rdRaster_Span16_TexLitZw), 1, 1);
}

/* the translucent / keyed drivers call their 8 or 16 bpp filler directly */
#define Q4_TDRAW(NAME, LIGHT, TRANS, EL, ER, S8, S16)                                                       \
void NAME(char *p, char *mat)                                                                               \
{                                                                                                           \
    int bpp = Q4_BPP();                                                                                     \
    q4_tex_setup(p, mat, LIGHT, TRANS, 0, 0);                                                               \
    Q4_WALK(EL, ER, Q4_SPAN_BPP(bpp, S8, S16), 1, (LIGHT) == 2);                                            \
}
#define Q4_TDRAW_L(NAME, TRANS, EL, ER, S8, S16)                                                            \
void NAME(char *p, char *mat, float light)                                                                  \
{                                                                                                           \
    int bpp = Q4_BPP();                                                                                     \
    q4_tex_setup(p, mat, 1, TRANS, 0, bpp == 8 || bpp == 16 ? q4_floor_i(light) : 0);                       \
    Q4_WALK(EL, ER, Q4_SPAN_BPP(bpp, S8, S16), 1, 0);                                                       \
}
/* OVERRIDES: rdZRaster_DrawNGonTLAT */
Q4_TDRAW(rdZRaster_DrawNGonTLAT, 0, 1, rdZRaster_SetupLeftEdgeNGonLAT, rdZRaster_SetupRightEdgeNGonLAT, rdZRaster_DrawScanLineNGonTLAT_8,
         rdZRaster_DrawScanLineNGonTLAT_16)
/* OVERRIDES: rdZRaster_DrawNGonMLAT */
Q4_TDRAW(rdZRaster_DrawNGonMLAT, 0, 0, rdZRaster_SetupLeftEdgeNGonLAT, rdZRaster_SetupRightEdgeNGonLAT, rdZRaster_DrawScanLineNGonMLAT_8,
         rdZRaster_DrawScanLineNGonMLAT_16)
/* OVERRIDES: rdZRaster_DrawNGonMTLAT */
Q4_TDRAW(rdZRaster_DrawNGonMTLAT, 0, 1, rdZRaster_SetupLeftEdgeNGonLAT, rdZRaster_SetupRightEdgeNGonLAT, rdZRaster_DrawScanLineNGonMTLAT_8,
         rdZRaster_DrawScanLineNGonMTLAT_16)
/* OVERRIDES: rdZRaster_DrawNGonTFAT */
Q4_TDRAW_L(rdZRaster_DrawNGonTFAT, 1, rdZRaster_SetupLeftEdgeNGonFAT, rdZRaster_SetupRightEdgeNGonFAT, rdZRaster_DrawScanLineNGonTFAT_8,
           rdZRaster_DrawScanLineNGonTFAT_16)
/* OVERRIDES: rdZRaster_DrawNGonMFAT */
Q4_TDRAW_L(rdZRaster_DrawNGonMFAT, 0, rdZRaster_SetupLeftEdgeNGonFAT, rdZRaster_SetupRightEdgeNGonFAT, rdZRaster_DrawScanLineNGonMFAT_8,
           rdZRaster_DrawScanLineNGonMFAT_16)
/* OVERRIDES: rdZRaster_DrawNGonMTFAT */
Q4_TDRAW_L(rdZRaster_DrawNGonMTFAT, 1, rdZRaster_SetupLeftEdgeNGonFAT, rdZRaster_SetupRightEdgeNGonFAT, rdZRaster_DrawScanLineNGonMTFAT_8,
           rdZRaster_DrawScanLineNGonMTFAT_16)
/* OVERRIDES: rdZRaster_DrawNGonTGAT */
Q4_TDRAW(rdZRaster_DrawNGonTGAT, 2, 1, rdZRaster_SetupLeftEdgeNGonGAT, rdZRaster_SetupRightEdgeNGonGAT, rdZRaster_DrawScanLineNGonTGAT_8,
         rdZRaster_DrawScanLineNGonTGAT_16)
/* OVERRIDES: rdZRaster_DrawNGonMGAT */
Q4_TDRAW(rdZRaster_DrawNGonMGAT, 2, 0, rdZRaster_SetupLeftEdgeNGonGAT, rdZRaster_SetupRightEdgeNGonGAT, rdZRaster_DrawScanLineNGonMGAT_8,
         rdZRaster_DrawScanLineNGonMGAT_16)
/* OVERRIDES: rdZRaster_DrawNGonMTGAT */
Q4_TDRAW(rdZRaster_DrawNGonMTGAT, 2, 1, rdZRaster_SetupLeftEdgeNGonGAT, rdZRaster_SetupRightEdgeNGonGAT, rdZRaster_DrawScanLineNGonMTGAT_8,
         rdZRaster_DrawScanLineNGonMTGAT_16)

#endif /* GRIM_EXE */
