/* Readable C for the perspective-correct half of the RDroid software rasteriser (agent q5; see docs/notes/asm_q5.md).
 *
 * Every function here replaces original 1.01 machine code (src/GRIMFANDANGO.EXE/asm_funcs.s as of 2df265d) and is
 * checked against it by the differential test in build/difftest/asm_q5/ (original bytes and this C on the same random
 * polygons, edges and spans, under the x87 precision controls 24, 53 and 64 bits; frame buffer, z-buffer, edge records,
 * rasteriser globals, x87 control word and stack compared).  It continues build/overrides_asm_q4.c (the affine half)
 * and uses the same conventions.
 *
 * The perspective pipeline (z-buffered, one polygon, called through rdCache's per-mode driver):
 *   Draw_*        the driver: copies the polygon's arrays and the mode tables into the rasteriser globals, calls
 *                 Grad_Flat_4, sets the mip level's texture globals and the 16-pixel steps of the plane equations,
 *                 then walks a left and a right edge down the polygon and calls the span filler per scan line.
 *   Grad_Flat_4   per vertex 1/(z+1), u/(z+1), v/(z+1); the screen-space plane gradients of the three (d/dx, d/dy), the
 *                 integer z step, the mip level and the u / v rounding biases.
 *   SpanR_Flat_13 .. 18   the edge set-up: x (16.16) on both edges, and on the left edge the three plane values at the
 *                 first pixel centre's row (1/z, u/z, v/z as floats) with their per-row steps; _17 / _18 also light.
 *   Span*         the span filler: one scan line; u and v are computed exactly (u/z divided by 1/z) every 16 pixels
 *                 (aligned to screen x multiples of 16) and stepped linearly in between.
 *
 * x87 conventions (as in build/overrides_asm_q4.c / _p2.c):
 *   - `long double` holds a value the original keeps on the x87 stack; q5_f() is a store of it to a float slot (FSTP
 *     m32) through a volatile, so it is rounded at that point at every optimisation level.
 *   - The original's `fldcw floor; fld m32; fistp; fldcw default` is q5_floor_i (SSE4.1 ROUNDSS + CVTTSS2SI: exact for a
 *     float operand; NaN and out of range give 0x80000000 in both).
 *   - The perspective span fillers start with `fldcw [0x00900528]` (round toward zero, 24-bit precision) and their
 *     first float -> int conversion ends with `fldcw [0x00900524]` (the default control word), so only the few
 *     operations before that conversion run truncated at 24 bits; everything after (the divides included) runs at the
 *     default precision.  The C loads the same control words at the same points (q5_fldcw); the values computed in
 *     between are stored through volatiles, which keeps the compiler from moving them across the control word loads.
 *     (build/peephole.py removed those `fldcw default` loads from the assembled build, which therefore ran whole
 *     fillers truncated at 24 bits; see the notes.)
 *
 * Speed: as build/overrides_asm_q4.c, compiled at -O2 with SSE4.1 and always-inlined helpers (build/link.py compiles
 * override files without -O). */
#pragma GCC optimize("O2", "no-strict-aliasing", "no-omit-frame-pointer")
#pragma GCC target("sse4.1")
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include <smmintrin.h>

/* ---- the rasteriser globals (names as in globals.h; not included, the types here are the ones the code needs) ---- */
extern int g_dwRdZRaster_numVertices;            /* vertex count of the polygon */
extern int g_dwRdZRaster_maxMipMap;            /* mip mode: the texture's mip count - 1 */
extern float g_dwRdZRaster_aUOverZ[];        /* per-vertex u / (z + 1) (Grad_Flat_4) */
extern int g_dwRdZRaster_yMinVert;            /* start vertex (top) */
extern int g_dwRdZRaster_leftVertexStep;            /* left edge direction (+1 / -1) */
extern void *UINT_007f44f0;          /* span filler chosen by the opaque drivers */
extern int g_dwRdZRaster_yMaxVert;            /* end vertex (bottom) */
extern float *g_dwRdZRaster_aIntensities;         /* per-vertex light */
extern float *g_pRdZRaster_aVertices;          /* screen vertices x, y, z (12 bytes each) */
extern float g_dwRdZRaster_aVOverZ[];        /* per-vertex v / (z + 1) */
extern int g_dwRdZRaster_rightVertexStep;            /* right edge direction */
extern float *g_dwRdZRaster_aTexVertices;         /* per-vertex u, v */
extern float g_dwRdZRaster_aOneOverZ[];        /* per-vertex 1 / (z + 1) */
extern unsigned char *g_dwRdZRaster_aRGBToPalette; /* 16 bpp colour -> palette index */
extern int g_dwRdZRaster_uWrap;            /* texture u mask << 16 */
extern float g_dwRdZRaster_oneOverZStep;           /* 16 * d(1/z)/dx */
extern int g_dwRdZRaster_dVdXModifier;            /* v rounding bias (0x8000 / 0x7fff) */
extern int g_dwRdZRaster_mipMapNum;            /* mip level */
extern int g_dwRdZRaster_vWrap;            /* texture v mask << log2 width */
extern unsigned short *g_dwRdZRaster_aRGBMap;/* light table, 16 bpp (64 rows of 256) */
extern float g_dwRdZRaster_dUOverZdX;           /* d(u/z)/dx */
extern float g_dwRdZRaster_dUOverZdY;           /* d(u/z)/dy */
extern int g_dwRdZRaster_texPitch;            /* width of the mip level (selects the 16 bpp filler without z shift) */
extern unsigned char *g_dwRdZRaster_aMonoMap; /* light table, 8 bpp */
extern float g_dwRdZRaster_vOverZStep;           /* 16 * d(v/z)/dx */
extern int g_dwRdZRaster_dUdXModifier;            /* u rounding bias */
extern unsigned char *g_dwRdZRaster_pPixels; /* texels of the mip level */
extern float g_dwRdZRaster_dVOverZdX;           /* d(v/z)/dx */
extern float g_dwRdZRaster_dVOverZdY;           /* d(v/z)/dy */
extern int g_dwRdZRaster_dOneOverZdXFixed;            /* z step per pixel (16.16) */
extern int g_dwRdZRaster_texRowShift;            /* log2 width of the mip level */
extern unsigned char *g_dwRdZRaster_aAlphaMap; /* translucency table (256 x 256) */
extern float g_dwRdZRaster_uOverZStep;           /* 16 * d(u/z)/dx */
extern float g_dwRdZRaster_dOneOverZdY;           /* d(1/z)/dy */
extern float g_dwRdZRaster_dOneOverZdX;           /* d(1/z)/dx */
extern int g_dwRdZRaster_zScaleShift;            /* z-buffer shift */
extern int g_aRdRaster_OneOverNFixed[];           /* 65536 / n (span length) */
extern float g_dwRdRaster_aOneOverNFlex[];        /* 1.0f / n */
extern unsigned short DAT_00900524;  /* x87 control word: default */
extern unsigned short DAT_00900528;  /* x87 control word: round toward zero, 24-bit precision */
extern char *g_dwRdColormap_pCurMap;          /* the colormap; +0x338: the translucency table */
extern char *g_pRdCamera_CurCamera;     /* 0x007f0fc8; +4: the canvas (+4 colour buffer, +0x10 z-buffer, +0x14 z shift) */
extern float DAT_004dda90, g_aRdroid_MipDistances, DAT_004dda98;  /* mip distance thresholds (10, 20, 40) */
extern void Mem_DumpLog(void);       /* an empty function: the 8 bpp "span filler" of the opaque drivers */

/* the edge record (0x44 bytes, on the driver's stack): x, dx (16.16), h (scan lines left), idx (current vertex); the
 * left edge's 1/z, u/z, v/z at the row (float) and their steps per row; light and its step (16.16); y (scan line) */
typedef struct q5_edge {
    int x, dx, h, idx;
    float z, dz, uz, duz, vz, dvz;
    int p28, p2c, p30, p34;
    int l, dl, y;
} q5_edge;

typedef int (*q5_edge_fn)(q5_edge *);
typedef void (*q5_span_fn)(q5_edge *, q5_edge *);

#define Q5_I(p, off) (*(int *)((char *)(p) + (off)))
#define Q5_VX(i) (g_pRdZRaster_aVertices[(i) * 3])
#define Q5_VY(i) (g_pRdZRaster_aVertices[(i) * 3 + 1])
#define Q5_VZ(i) (g_pRdZRaster_aVertices[(i) * 3 + 2])
#define Q5_LT(i) (g_dwRdZRaster_aIntensities[i])
#define Q5_ZI(i) (g_dwRdZRaster_aOneOverZ[i])
#define Q5_UZ(i) (g_dwRdZRaster_aUOverZ[i])
#define Q5_VZI(i) (g_dwRdZRaster_aVOverZ[i])
#define q5_u32(f) (*(int *)&(f))
#define Q5_INLINE static inline __attribute__((always_inline))

Q5_INLINE float q5_f(long double x)
{
    volatile float f = (float)x;
    return f;
}

/* fldcw floor; fld m32; fistp m32 */
Q5_INLINE int q5_floor_i(float f)
{
    __m128 v = _mm_set_ss(f);
    return _mm_cvttss_si32(_mm_round_ss(v, v, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC));
}

/* fldcw ceil; fld m32; frndint; fstp m32 */
Q5_INLINE float q5_ceil(float f)
{
    __m128 v = _mm_set_ss(f);
    return _mm_cvtss_f32(_mm_round_ss(v, v, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC));
}

/* the FLD / FSTP copy of a float (quiets a signalling NaN) */
Q5_INLINE float q5_copy(float f)
{
    return q5_f((long double)f);
}

/* fldcw m16 (the memory clobber keeps the volatile stores / loads around it in place) */
Q5_INLINE void q5_fldcw(unsigned short *cw)
{
    __asm__ volatile("fldcw %0" : : "m"(*cw) : "memory");
}

/* _ftol: truncation of the x87 value to a 64-bit integer, low dword */
Q5_INLINE int q5_ftol(long double x)
{
    return (int)(long long)x;
}

/* imul; shrd EAX,EDX,0x10: bits 16..47 of the 64-bit product */
Q5_INLINE int q5_mul16(int a, int b)
{
    return (int)((long long)a * b >> 16);
}

/* next vertex of an edge: i + dir, wrapping to 0 past the last vertex and to n - 1 below 0 */
Q5_INLINE int q5_next(int i, int dir)
{
    int n = i + dir;
    if (n < 0)
        return g_dwRdZRaster_numVertices - 1;
    return n > g_dwRdZRaster_numVertices - 1 ? 0 : n;
}

/* ==== Grad_Flat_4: the plane equations of the perspective drivers ====
 * Picks three vertices a, b, c exactly as Grad_Flat_3 (build/overrides_asm_q4.c): a triangle's 0, 1, 2; otherwise
 * a = top, b = bottom and c the vertex farthest in x from their midpoint, searched from the top on the side that is
 * not the straight continuation (c starts as the argument's bits when the vertex next to the top is the bottom).
 * Per vertex: zi = 1 / (z - -1) (float), u/z = float(u * zi unrounded), v/z = float(v * float(zi)).
 * Plane gradients through a, b, c: A = float(xa - xc), B = float(xb - xc), C = ya - yc, D = yb - yc (extended),
 * R = float(1 / (C * B - D * A)); for each of the three (dZ = float(Zb - Zc), ... with Zb from b, Za from a):
 * d/dx = float((Zb * C - Za * D) * R), d/dy = float((Zb * A - Za * B) * -R); the integer z step is
 * _ftol((Zb * C - Za * D) * R * 65536) (the unrounded d/dx).  The mip level as Grad_Flat_3.  The u rounding bias:
 * 0x8000 when e = zi(a) * du/dx - u/z(a) * dz/dx > 0, 0x7fff when e < 0 or NaN, else by the same test on the d/dy
 * gradients (0x7fff when < 0 or NaN); v the same. */
/* OVERRIDES: rdZRaster_CalcPerspGradients */
void rdZRaster_CalcPerspGradients(int dbits)
{
    float dist = *(float *)&dbits;
    int cnt = g_dwRdZRaster_numVertices, a, b, c, dir, k, i;
    float *V = g_pRdZRaster_aVertices;
    if (cnt == 3) {
        a = 0;
        b = 1;
        c = 2;
    } else {
        int start = g_dwRdZRaster_yMinVert, end = g_dwRdZRaster_yMaxVert;
        float mid, mx = 0.0f;
        a = start;
        b = end;
        if (q5_next(start, 1) == end) {
            c = dbits;
            dir = -1;
        } else if (q5_next(start, -1) == end) {
            c = dbits;
            dir = 1;
        } else {
            long double r, d;
            c = q5_next(start, 1);
            r = ((long double)V[end * 3 + 1] - V[start * 3 + 1]) / ((long double)V[end * 3] - V[start * 3]);
            d = V[c * 3 + 1] - (r * ((long double)V[c * 3] - V[start * 3]) + V[start * 3 + 1]);
            if (!(d >= 0.0L))
                d = -d;
            dir = d >= 1.0L ? 1 : -1;
        }
        mid = q5_f(((long double)V[start * 3] + V[end * 3]) * 0.5f);
        for (k = q5_next(start, dir); k != end; k = q5_next(k, dir)) {
            long double d = (long double)V[k * 3] - mid;
            if (!(d >= 0.0L))
                d = -d;
            if (d > mx) {
                mx = q5_f(d);
                c = k;
            }
        }
        cnt = g_dwRdZRaster_numVertices;
    }
    {
        float *T = g_dwRdZRaster_aTexVertices;
        for (i = 0; i < cnt; i++) {
            long double zi = 1.0f / ((long double)V[i * 3 + 2] - -1.0f);
            Q5_ZI(i) = q5_f(zi);
            Q5_UZ(i) = q5_f(T[i * 2] * zi);
            Q5_VZI(i) = q5_f((long double)T[i * 2 + 1] * Q5_ZI(i));
        }
    }
    {
        float *va = V + a * 3, *vb = V + b * 3, *vc = V + c * 3;
        long double C, D, e;
        float A, B, R, nR, Za, Zb, Ua, Ub, Va, Vb;
        C = (long double)va[1] - vc[1];
        D = (long double)vb[1] - vc[1];
        A = q5_f((long double)va[0] - vc[0]);
        B = q5_f((long double)vb[0] - vc[0]);
        R = q5_f(1.0f / (C * B - D * A));
        nR = -R;
        Zb = q5_f((long double)Q5_ZI(b) - Q5_ZI(c));
        Za = q5_f((long double)Q5_ZI(a) - Q5_ZI(c));
        Ub = q5_f((long double)Q5_UZ(b) - Q5_UZ(c));
        Ua = q5_f((long double)Q5_UZ(a) - Q5_UZ(c));
        Vb = q5_f((long double)Q5_VZI(b) - Q5_VZI(c));
        Va = q5_f((long double)Q5_VZI(a) - Q5_VZI(c));
        e = ((long double)Zb * C - (long double)Za * D) * R;
        g_dwRdZRaster_dOneOverZdX = q5_f(e);
        g_dwRdZRaster_dOneOverZdY = q5_f(((long double)Zb * A - (long double)Za * B) * nR);
        g_dwRdZRaster_dOneOverZdXFixed = q5_ftol(e * 65536.0f);
        g_dwRdZRaster_dUOverZdX = q5_f(((long double)Ub * C - (long double)Ua * D) * R);
        g_dwRdZRaster_dUOverZdY = q5_f(((long double)Ub * A - (long double)Ua * B) * nR);
        g_dwRdZRaster_dVOverZdX = q5_f(((long double)Vb * C - (long double)Va * D) * R);
        g_dwRdZRaster_dVOverZdY = q5_f(((long double)Vb * A - (long double)Va * B) * nR);
    }
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
    {
        long double e = (long double)Q5_ZI(a) * g_dwRdZRaster_dUOverZdX - (long double)Q5_UZ(a) * g_dwRdZRaster_dOneOverZdX;
        if (e > 0.0L)
            g_dwRdZRaster_dUdXModifier = 0x8000;
        else if (!(e >= 0.0L) ||
                 !((long double)Q5_ZI(a) * g_dwRdZRaster_dUOverZdY - (long double)Q5_UZ(a) * g_dwRdZRaster_dOneOverZdY >= 0.0L))
            g_dwRdZRaster_dUdXModifier = 0x7fff;
        else
            g_dwRdZRaster_dUdXModifier = 0x8000;
        e = (long double)Q5_ZI(a) * g_dwRdZRaster_dVOverZdX - (long double)Q5_VZI(a) * g_dwRdZRaster_dOneOverZdX;
        if (e > 0.0L)
            g_dwRdZRaster_dVdXModifier = 0x8000;
        else if (!(e >= 0.0L) ||
                 !((long double)Q5_ZI(a) * g_dwRdZRaster_dVOverZdY - (long double)Q5_VZI(a) * g_dwRdZRaster_dOneOverZdY >= 0.0L))
            g_dwRdZRaster_dVdXModifier = 0x7fff;
        else
            g_dwRdZRaster_dVdXModifier = 0x8000;
    }
}

/* ==== SpanR_Flat_13 .. _18: the perspective edge set-up ====
 * Returns 1 when the edge reached the end vertex, else 0 with the record set up for the next vertex pair that covers
 * at least one scan line (y = ceil(y0), h = ceil(y1) - y as q4's affine edges).  sub = float(ceil(y0) - y0).
 * One scan line: x = floor(float(x0 * 65536)) (LIT: l the same from the vertex light), xs = float(x0), steps unchanged.
 * More: the x slope t is (x1 - x0) / (y1 - y0) (_13 .. _16) or (x1 - x0) * float(1 / (y1 - y0)) (_17, _18);
 * dx = floor(float(t * 65536)), xs = float(float(t) * sub + x0) and x = floor(float(that, unrounded, * 65536)); LIT:
 * light as q4 (inv), dl = floor(float(t * 65536)), l = floor(float((float(t) * sub + l0) * 65536)).
 * PERSP (the left edge): the per-row steps dz = float(float(t) * d/dx + d/dy) of the three planes; and with
 * dxs = xs - x0 (extended) the values at the row: z = float((sub * dZ/dy + zi0) + dxs * dZ/dx), u/z likewise, v/z =
 * float((dxs * dV/dx + vz0) + sub * dV/dy) (the operand order of the original). */
#define Q5_EDGE_FN(NAME, DIR, PERSP, LIT)                                                                   \
int NAME(q5_edge *e)                                                                                        \
{                                                                                                           \
    int i = e->idx, n, h;                                                                                   \
    float cy, sub, xs, tf;                                                                                  \
    if (i == g_dwRdZRaster_yMaxVert)                                                                                 \
        return 1;                                                                                           \
    for (;;) {                                                                                              \
        n = q5_next(i, DIR);                                                                                \
        cy = q5_ceil(q5_copy(Q5_VY(i)));                                                                    \
        e->y = q5_floor_i(cy);                                                                              \
        h = q5_floor_i(q5_ceil(q5_copy(Q5_VY(n)))) - e->y;                                                  \
        e->h = h;                                                                                           \
        if (h > 0)                                                                                          \
            break;                                                                                          \
        i = n;                                                                                              \
        if (n == g_dwRdZRaster_yMaxVert)                                                                             \
            return 1;                                                                                       \
    }                                                                                                       \
    sub = q5_f((long double)cy - Q5_VY(i));                                                                 \
    if (h < 2) {                                                                                            \
        xs = q5_copy(Q5_VX(i));                                                                             \
        e->x = q5_floor_i(q5_f(Q5_VX(i) * 65536.0f));                                                      \
        if (LIT)                                                                                            \
            e->l = q5_floor_i(q5_f(Q5_LT(i) * 65536.0f));                                                   \
    } else {                                                                                                \
        long double t, xe;                                                                                  \
        float inv = 0.0f;                                                                                   \
        if (LIT) {                                                                                          \
            inv = q5_f(1.0f / ((long double)Q5_VY(n) - Q5_VY(i)));                                          \
            t = ((long double)Q5_VX(n) - Q5_VX(i)) * inv;                                                   \
        } else                                                                                              \
            t = ((long double)Q5_VX(n) - Q5_VX(i)) / ((long double)Q5_VY(n) - Q5_VY(i));                    \
        tf = q5_f(t);                                                                                       \
        e->dx = q5_floor_i(q5_f(t * 65536.0f));                                                             \
        xe = (long double)tf * sub + Q5_VX(i);                                                              \
        xs = q5_f(xe);                                                                                      \
        e->x = q5_floor_i(q5_f(xe * 65536.0f));                                                             \
        if (PERSP) {                                                                                        \
            e->dz = q5_f((long double)tf * g_dwRdZRaster_dOneOverZdX + g_dwRdZRaster_dOneOverZdY);                                    \
            e->duz = q5_f((long double)tf * g_dwRdZRaster_dUOverZdX + g_dwRdZRaster_dUOverZdY);                                   \
            e->dvz = q5_f((long double)tf * g_dwRdZRaster_dVOverZdX + g_dwRdZRaster_dVOverZdY);                                   \
        }                                                                                                   \
        if (LIT) {                                                                                          \
            float lf;                                                                                       \
            t = ((long double)Q5_LT(n) - Q5_LT(i)) * inv;                                                   \
            lf = q5_f(t);                                                                                   \
            e->dl = q5_floor_i(q5_f(t * 65536.0f));                                                         \
            e->l = q5_floor_i(q5_f(((long double)lf * sub + Q5_LT(i)) * 65536.0f));                        \
        }                                                                                                   \
    }                                                                                                       \
    if (PERSP) {                                                                                            \
        long double dxs = (long double)xs - Q5_VX(i);                                                       \
        e->z = q5_f(((long double)sub * g_dwRdZRaster_dOneOverZdY + Q5_ZI(i)) + dxs * g_dwRdZRaster_dOneOverZdX);                     \
        e->uz = q5_f(((long double)sub * g_dwRdZRaster_dUOverZdY + Q5_UZ(i)) + dxs * g_dwRdZRaster_dUOverZdX);                    \
        e->vz = q5_f((dxs * g_dwRdZRaster_dVOverZdX + Q5_VZI(i)) + (long double)sub * g_dwRdZRaster_dVOverZdY);                   \
    }                                                                                                       \
    e->idx = n;                                                                                             \
    return 0;                                                                                               \
}

/* OVERRIDES: rdZRaster_SetupLeftEdgeNGonLIT */
Q5_EDGE_FN(rdZRaster_SetupLeftEdgeNGonLIT, g_dwRdZRaster_leftVertexStep, 1, 0)
/* OVERRIDES: rdZRaster_SetupRightEdgeNGonLIT */
Q5_EDGE_FN(rdZRaster_SetupRightEdgeNGonLIT, g_dwRdZRaster_rightVertexStep, 0, 0)
/* OVERRIDES: rdZRaster_SetupLeftEdgeNGonFIT */
Q5_EDGE_FN(rdZRaster_SetupLeftEdgeNGonFIT, g_dwRdZRaster_leftVertexStep, 1, 0)
/* OVERRIDES: rdZRaster_SetupRightEdgeNGonFIT */
Q5_EDGE_FN(rdZRaster_SetupRightEdgeNGonFIT, g_dwRdZRaster_rightVertexStep, 0, 0)
/* OVERRIDES: rdZRaster_SetupLeftEdgeNGonGIT */
Q5_EDGE_FN(rdZRaster_SetupLeftEdgeNGonGIT, g_dwRdZRaster_leftVertexStep, 1, 1)
/* OVERRIDES: rdZRaster_SetupRightEdgeNGonGIT */
Q5_EDGE_FN(rdZRaster_SetupRightEdgeNGonGIT, g_dwRdZRaster_rightVertexStep, 0, 1)

/* ==== the perspective span fillers (z-buffered, 8 / 16 bpp) ====
 * The span covers the pixel columns xl .. xr - 1 (xl = ceil(L.x), xr = ceil(R.x), 16.16, both >> 16 signed); nothing
 * when xr - xl <= 0.  It is cut into a first part up to the next screen column that is a multiple of 16 (none when xl
 * is one; xl % 16 is a C remainder), whole 16-pixel chunks, and a last part of 1..16 pixels.  At the start (with the
 * control word truncating at 24 bits): f = (xl_fixed - L.x) / 65536, the plane values at the first pixel
 * oz = float(f * d(1/z)/dx + L.z), ouz, ovz the same, z = floor(float(oz * 65536)); from there on the default control
 * word: u0 = float(1/oz * ouz), v0 = float(1/oz * ovz).  Per part of k pixels the plane values at its end (first part:
 * float(k * d/dx + start), chunks: + 16 * d/dx, last part: 1 / ((k - 1) * d/dx - 16 d/dx + oz) with k - 1 in place
 * of k) give u1, v1, and du = floor(float((u1 - u0) * (1/k as a float: the table at 0x008fe000; chunks 0.0625) *
 * 65536)) >> mip, u = floor(float(u0 * 65536)) >> mip + the bias (dv, v the same); a 1-pixel last part keeps u, v and
 * their steps from the part before.  When there is no first part, u and v hold a register's left-over value (G: the
 * z value, the light or a destination pointer, as in each original) until the first chunk; a 1-pixel span that starts
 * on a multiple of 16 is drawn with it.  The pixels as q4's fillers: z >> shift compared (unsigned 16 bits, greater
 * draws) with the z-buffer, the texel texels[(u >> 16 & umask) + (v >> (16 - log2 w) & vmask)], KEY: texel 0 is
 * transparent; z += dz (the integer step 0x008dde88), LIT: the light as q4's gouraud fillers. */
#define Q5_TEXEL(u, v)                                                                                      \
    g_dwRdZRaster_pPixels[(((u) >> 16) & (g_dwRdZRaster_uWrap >> 16)) + (((v) >> ((16 - g_dwRdZRaster_texRowShift) & 31)) & g_dwRdZRaster_vWrap)]
#define Q5_BUF8(c4, y, x) ((unsigned char *)(Q5_I(Q5_I(c4, 4), 0x5c) + Q5_I(Q5_I(c4, 4), 0x18) * (y) + (x)))
#define Q5_BUF16(c4, y, x)                                                                                  \
    ((unsigned short *)(Q5_I(Q5_I(c4, 4), 0x5c) + (((unsigned)Q5_I(Q5_I(c4, 4), 0x18) >> 1) * (y) + (x)) * 2))
#define Q5_ZBUF(c4, y, x) ((unsigned short *)(Q5_I(Q5_I(c4, 0x10), 0x5c) + Q5_I(Q5_I(c4, 0x10), 0x18) * (y) + (x) * 2))
#define Q5_LROW(l) ((((l) >> 16) & 0x3f) << 8)
#define Q5_BLEND(c, d) g_dwRdZRaster_aAlphaMap[(c) * 256 + (d)]

/* the pixels of one part: k pixels from pix / zp on */
#define Q5_PIXELS(k, KEY, PIXEL, LIT)                                                                       \
    {                                                                                                       \
        int k_ = (k);                                                                                       \
        do {                                                                                                \
            int zs = z >> sh;                                                                               \
            if ((unsigned short)zs > *zp) {                                                                 \
                unsigned tx = Q5_TEXEL(u, v);                                                               \
                if (!(KEY) || tx) {                                                                         \
                    PIXEL;                                                                                  \
                    *zp = (unsigned short)zs;                                                               \
                }                                                                                           \
            }                                                                                               \
            u += du;                                                                                        \
            v += dv;                                                                                        \
            z += dz;                                                                                        \
            if (LIT)                                                                                        \
                l += dl;                                                                                    \
            pix++;                                                                                          \
            zp++;                                                                                           \
        } while (--k_);                                                                                     \
    }

/* u, v and their steps for a part from (u0, v0) to (u1, v1) over 1/k = rk */
#define Q5_UV(rk)                                                                                           \
    {                                                                                                       \
        int mip = g_dwRdZRaster_mipMapNum & 31;                                                                       \
        du = q5_floor_i(q5_f(((long double)u1 - u0) * (rk) * 65536.0f)) >> mip;                             \
        dv = q5_floor_i(q5_f(((long double)v1 - v0) * (rk) * 65536.0f)) >> mip;                             \
        u = (q5_floor_i(q5_f((long double)u0 * 65536.0f)) >> mip) + g_dwRdZRaster_dUdXModifier;                          \
        v = (q5_floor_i(q5_f((long double)v0 * 65536.0f)) >> mip) + g_dwRdZRaster_dVdXModifier;                          \
    }

#define Q5_PSPAN(NAME, PIXT, BUF, LIT, KEY, G, PIXEL)                                                       \
void NAME(q5_edge *L, q5_edge *R)                                                                           \
{                                                                                                           \
    int x0 = L->x, xs = (x0 & 0xffff) ? (x0 + 0x10000) & 0xffff0000 : x0;                                   \
    int xr = R->x, xl, n, r, first, chunks, rem, frac, z, dz, u, v, du = 0, dv = 0, l = 0, dl = 0, sh;      \
    float oz, ouz, ovz, u0, v0, u1, v1, zf;                                                                 \
    long double w;                                                                                          \
    char *c4;                                                                                               \
    PIXT *pix;                                                                                              \
    unsigned short *zp;                                                                                     \
    if (xr & 0xffff)                                                                                        \
        xr = (xr + 0x10000) & 0xffff0000;                                                                   \
    xl = xs >> 16;                                                                                          \
    n = (xr >> 16) - xl;                                                                                    \
    if (n <= 0)                                                                                             \
        return;                                                                                             \
    q5_fldcw(&DAT_00900528);                                                                                \
    r = xl % 16;                                                                                            \
    first = r ? (n < 16 - r ? n : 16 - r) : 0;                                                              \
    rem = n - first;                                                                                        \
    if (rem) {                                                                                              \
        chunks = rem / 16;                                                                                  \
        rem %= 16;                                                                                          \
        if (!rem) {                                                                                         \
            rem = 16;                                                                                       \
            chunks--;                                                                                       \
        }                                                                                                   \
    } else                                                                                                  \
        chunks = 0;                                                                                         \
    frac = xs - x0;                                                                                         \
    if (LIT) {                                                                                              \
        dl = q5_mul16(R->l - L->l, g_aRdRaster_OneOverNFixed[n]);                                                        \
        if (dl < 0 && dl > -0x51e)                                                                          \
            dl = 0;                                                                                         \
        l = q5_mul16(frac, dl) + L->l;                                                                      \
    }                                                                                                       \
    {                                                                                                       \
        long double f = (long double)frac * (1.0f / 65536.0f);                                              \
        oz = q5_f(f * g_dwRdZRaster_dOneOverZdX + L->z);                                                                 \
        ouz = q5_f(f * g_dwRdZRaster_dUOverZdX + L->uz);                                                               \
        ovz = q5_f(f * g_dwRdZRaster_dVOverZdX + L->vz);                                                               \
        zf = q5_f((long double)oz * 65536.0f);                                                              \
        z = q5_floor_i(zf);                                                                                 \
    }                                                                                                       \
    q5_fldcw(&DAT_00900524);                                                                                \
    dz = g_dwRdZRaster_dOneOverZdXFixed;                                                                                     \
    sh = g_dwRdZRaster_zScaleShift;                                                                                     \
    w = 1.0f / (long double)oz;                                                                             \
    c4 = *(char **)(g_pRdCamera_CurCamera + 4);                                                                \
    pix = BUF(c4, L->y, xl);                                                                                \
    zp = Q5_ZBUF(c4, L->y, xl);                                                                             \
    u0 = q5_f(w * ouz);                                                                                     \
    v0 = q5_f(w * ovz);                                                                                     \
    if (first) {                                                                                            \
        long double k = first;                                                                              \
        float rk = g_dwRdRaster_aOneOverNFlex[first];                                                                    \
        float oz1 = q5_f(k * g_dwRdZRaster_dOneOverZdX + oz), uz1 = q5_f(k * g_dwRdZRaster_dUOverZdX + ouz),                         \
              vz1 = q5_f(k * g_dwRdZRaster_dVOverZdX + ovz);                                                           \
        w = 1.0f / (long double)oz1;                                                                        \
        u1 = q5_f(w * uz1);                                                                                 \
        v1 = q5_f(w * vz1);                                                                                 \
        Q5_UV(rk)                                                                                           \
        Q5_PIXELS(first, KEY, PIXEL, LIT)                                                                   \
        oz = q5_f((long double)oz1 + g_dwRdZRaster_oneOverZStep);                                                         \
        u0 = u1;                                                                                            \
        v0 = v1;                                                                                            \
        ouz = q5_f((long double)uz1 + g_dwRdZRaster_uOverZStep);                                                        \
        ovz = q5_f((long double)vz1 + g_dwRdZRaster_vOverZStep);                                                        \
    } else {                                                                                                \
        u = v = (G);                                                                                        \
        oz = q5_f((long double)oz + g_dwRdZRaster_oneOverZStep);                                                          \
        ouz = q5_f((long double)ouz + g_dwRdZRaster_uOverZStep);                                                        \
        ovz = q5_f((long double)ovz + g_dwRdZRaster_vOverZStep);                                                        \
    }                                                                                                       \
    for (; chunks > 0; chunks--) {                                                                          \
        w = 1.0f / (long double)oz;                                                                         \
        u1 = q5_f(w * ouz);                                                                                 \
        v1 = q5_f(w * ovz);                                                                                 \
        Q5_UV(0.0625f)                                                                                      \
        Q5_PIXELS(16, KEY, PIXEL, LIT)                                                                      \
        oz = q5_f((long double)oz + g_dwRdZRaster_oneOverZStep);                                                          \
        u0 = u1;                                                                                            \
        v0 = v1;                                                                                            \
        ouz = q5_f((long double)ouz + g_dwRdZRaster_uOverZStep);                                                        \
        ovz = q5_f((long double)ovz + g_dwRdZRaster_vOverZStep);                                                        \
    }                                                                                                       \
    if (rem) {                                                                                              \
        if (--rem) {                                                                                        \
            long double k = rem;                                                                            \
            float rk = g_dwRdRaster_aOneOverNFlex[rem];                                                                  \
            w = 1.0f / ((k * g_dwRdZRaster_dOneOverZdX - g_dwRdZRaster_oneOverZStep) + oz);                                            \
            u1 = q5_f(((k * g_dwRdZRaster_dUOverZdX - g_dwRdZRaster_uOverZStep) + ouz) * w);                                       \
            v1 = q5_f(((k * g_dwRdZRaster_dVOverZdX - g_dwRdZRaster_vOverZStep) + ovz) * w);                                       \
            Q5_UV(rk)                                                                                       \
        }                                                                                                   \
        Q5_PIXELS(rem + 1, KEY, PIXEL, LIT)                                                                 \
    }                                                                                                       \
    q5_fldcw(&DAT_00900524);                                                                                \
}
#define Q5_PSPAN8(NAME, LIT, KEY, G, PIXEL) Q5_PSPAN(NAME, unsigned char, Q5_BUF8, LIT, KEY, G, PIXEL)
#define Q5_PSPAN16(NAME, LIT, KEY, G, PIXEL) Q5_PSPAN(NAME, unsigned short, Q5_BUF16, LIT, KEY, G, PIXEL)
/* the left-over register values (G) */
#define Q5_GZ z
#define Q5_GL l
#define Q5_GPIX ((int)pix)
#define Q5_GZP ((int)zp)
#define Q5_GZF q5_u32(zf)

/* unlit (Draw_FlatLit_10, Draw_TexLitZ_7, Draw_TexLitKeyZw_7 / _8; 16 bpp: light row 63) */
/* OVERRIDES: rdZRaster_DrawScanLineNGonLIT_8 */
Q5_PSPAN8(rdZRaster_DrawScanLineNGonLIT_8, 0, 0, Q5_GZ, *pix = tx)
/* OVERRIDES: rdZRaster_DrawScanLineNGonLIT_16 */
Q5_PSPAN16(rdZRaster_DrawScanLineNGonLIT_16, 0, 0, Q5_GPIX, *pix = g_dwRdZRaster_aRGBMap[tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonTLIT_8 */
Q5_PSPAN8(rdZRaster_DrawScanLineNGonTLIT_8, 0, 0, Q5_GZ, *pix = Q5_BLEND(tx, *pix))
/* OVERRIDES: rdZRaster_DrawScanLineNGonTLIT_16 */
Q5_PSPAN16(rdZRaster_DrawScanLineNGonTLIT_16, 0, 0, Q5_GZ, *pix = g_dwRdZRaster_aRGBMap[Q5_BLEND(tx, g_dwRdZRaster_aRGBToPalette[*pix])])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMLIT_8 */
Q5_PSPAN8(rdZRaster_DrawScanLineNGonMLIT_8, 0, 1, Q5_GPIX, *pix = tx)
/* OVERRIDES: rdZRaster_DrawScanLineNGonMLIT_16 */
Q5_PSPAN16(rdZRaster_DrawScanLineNGonMLIT_16, 0, 1, Q5_GPIX, *pix = g_dwRdZRaster_aRGBMap[tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMTLIT_8 */
Q5_PSPAN8(rdZRaster_DrawScanLineNGonMTLIT_8, 0, 1, Q5_GZP, *pix = Q5_BLEND(tx, *pix))
/* OVERRIDES: rdZRaster_DrawScanLineNGonMTLIT_16 */
Q5_PSPAN16(rdZRaster_DrawScanLineNGonMTLIT_16, 0, 1, Q5_GZP, *pix = g_dwRdZRaster_aRGBMap[Q5_BLEND(tx, g_dwRdZRaster_aRGBToPalette[*pix])])

/* flat lit (the light tables point at the polygon's light row).  The translucent 16 bpp filler (Span16_TexZ_5) looks
 * the lit colour up as g_dwRdZRaster_aRGBToPalette[colour * 256] and adds it to the blend row instead of multiplying (as in the
 * original: it reads up to 16 MB past the 64 KB table) */
/* OVERRIDES: rdZRaster_DrawScanLineNGonFIT_8 */
Q5_PSPAN8(rdZRaster_DrawScanLineNGonFIT_8, 0, 0, Q5_GZ, *pix = g_dwRdZRaster_aMonoMap[tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonFIT_16 */
Q5_PSPAN16(rdZRaster_DrawScanLineNGonFIT_16, 0, 0, Q5_GPIX, *pix = g_dwRdZRaster_aRGBMap[tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonTFIT_8 */
Q5_PSPAN8(rdZRaster_DrawScanLineNGonTFIT_8, 0, 0, Q5_GZ, *pix = Q5_BLEND(g_dwRdZRaster_aMonoMap[tx], *pix))
/* OVERRIDES: rdZRaster_DrawScanLineNGonTFIT_16 */
Q5_PSPAN16(rdZRaster_DrawScanLineNGonTFIT_16, 0, 0, Q5_GZ,
           *pix = g_dwRdZRaster_aRGBMap[g_dwRdZRaster_aAlphaMap[g_dwRdZRaster_aRGBToPalette[g_dwRdZRaster_aRGBMap[tx] << 8] + g_dwRdZRaster_aRGBToPalette[*pix]]])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMFIT_8 */
Q5_PSPAN8(rdZRaster_DrawScanLineNGonMFIT_8, 0, 1, Q5_GPIX, *pix = g_dwRdZRaster_aMonoMap[tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMFIT_16 */
Q5_PSPAN16(rdZRaster_DrawScanLineNGonMFIT_16, 0, 1, Q5_GPIX, *pix = g_dwRdZRaster_aRGBMap[tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMTFIT_8 */
Q5_PSPAN8(rdZRaster_DrawScanLineNGonMTFIT_8, 0, 1, Q5_GZP, *pix = g_dwRdZRaster_aMonoMap[Q5_BLEND(tx, *pix)])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMTFIT_16 */
Q5_PSPAN16(rdZRaster_DrawScanLineNGonMTFIT_16, 0, 1, Q5_GZP, *pix = g_dwRdZRaster_aRGBMap[Q5_BLEND(tx, g_dwRdZRaster_aRGBToPalette[*pix])])

/* gouraud (light row per pixel); Span16_TexZ_7 has Span16_TexZ_5's lookup */
/* OVERRIDES: rdZRaster_DrawScanLineNGonGIT_8 */
Q5_PSPAN8(rdZRaster_DrawScanLineNGonGIT_8, 1, 0, Q5_GL, *pix = g_dwRdZRaster_aMonoMap[Q5_LROW(l) + tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonGIT_16 */
Q5_PSPAN16(rdZRaster_DrawScanLineNGonGIT_16, 1, 0, Q5_GPIX, *pix = g_dwRdZRaster_aRGBMap[Q5_LROW(l) + tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonTGIT_8 */
Q5_PSPAN8(rdZRaster_DrawScanLineNGonTGIT_8, 1, 0, Q5_GL, *pix = Q5_BLEND(g_dwRdZRaster_aMonoMap[Q5_LROW(l) + tx], *pix))
/* OVERRIDES: rdZRaster_DrawScanLineNGonTGIT_16 */
Q5_PSPAN16(rdZRaster_DrawScanLineNGonTGIT_16, 1, 0, Q5_GZF,
           *pix = g_dwRdZRaster_aRGBMap[g_dwRdZRaster_aAlphaMap[g_dwRdZRaster_aRGBToPalette[g_dwRdZRaster_aRGBMap[Q5_LROW(l) + tx] << 8] +
                                              g_dwRdZRaster_aRGBToPalette[*pix]]])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMGIT_8 */
Q5_PSPAN8(rdZRaster_DrawScanLineNGonMGIT_8, 1, 1, Q5_GPIX, *pix = g_dwRdZRaster_aMonoMap[Q5_LROW(l) + tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMGIT_16 */
Q5_PSPAN16(rdZRaster_DrawScanLineNGonMGIT_16, 1, 1, Q5_GPIX, *pix = g_dwRdZRaster_aRGBMap[Q5_LROW(l) + tx])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMTGIT_8 */
Q5_PSPAN8(rdZRaster_DrawScanLineNGonMTGIT_8, 1, 1, Q5_GZF, *pix = g_dwRdZRaster_aMonoMap[Q5_LROW(l) + Q5_BLEND(tx, *pix)])
/* OVERRIDES: rdZRaster_DrawScanLineNGonMTGIT_16 */
Q5_PSPAN16(rdZRaster_DrawScanLineNGonMTGIT_16, 1, 1, Q5_GZF,
           *pix = g_dwRdZRaster_aRGBMap[Q5_LROW(l) + Q5_BLEND(tx, g_dwRdZRaster_aRGBToPalette[*pix])])

/* ==== the 16 bpp perspective fillers without z shift (Span16_TexZw*, Span16_TexLitZw_9 .. 14, _23, _31) ====
 * The opaque drivers choose them by the texture width when the canvas has no z shift.  The same parts and the same
 * arithmetic as Q5_PSPAN, but the span state lives in globals, as in the affine ones of build/overrides_asm_o2.c:
 * 0x007f4cac the pixel count (written even when it is <= 0), 0x007f4cfc z, 0x007f4cf4 u, 0x007f4cf8 v, 0x007f4cf0
 * light and their steps 0x007f4c54, 0x007f4cdc, 0x007f4c44, 0x007f4cb4, 0x007f4cc4 / 0x007f4ca4 the destination and
 * z-buffer pointers of the part, 0x007f4cb0 the part's pixel count; after a part u, v, z, light and the pointers are
 * one pixel past its end.  Without a first part, u, v and their steps keep the values of the previous span until the
 * first chunk (the original draws a 1-pixel span on a multiple of 16 with them).  A pixel is drawn when z (its low
 * 16 bits, not shifted) is greater than the z-buffer value; the z-buffer is written first.  The original draws each
 * part from right to left; the pixels of a part are independent, so the C goes left to right.
 * TEXEL: the texel index for the width (v >> (16 - log2 w) & vmask | (u & umask) >> 16); PIXEL: the 16 bpp colour.
 * The generic lit one (Span16_TexZw) adds light >> 8 (row and fraction, unmasked) to the texel; the fixed-width lit
 * ones (light & 0x3f0000) >> 8. */
extern int UINT_007f4c44, UINT_007f4c54, UINT_007f4ca4, UINT_007f4cac, UINT_007f4cb0, UINT_007f4cb4, UINT_007f4cc4,
    UINT_007f4cdc, UINT_007f4cf0, UINT_007f4cf4, UINT_007f4cf8, UINT_007f4cfc;

#define Q5_ZUV(rk)                                                                                          \
    {                                                                                                       \
        int mip = g_dwRdZRaster_mipMapNum & 31;                                                                       \
        UINT_007f4cdc = q5_floor_i(q5_f(((long double)u1 - u0) * (rk) * 65536.0f)) >> mip;                  \
        UINT_007f4c44 = q5_floor_i(q5_f(((long double)v1 - v0) * (rk) * 65536.0f)) >> mip;                  \
        UINT_007f4cf4 = (q5_floor_i(q5_f((long double)u0 * 65536.0f)) >> mip) + g_dwRdZRaster_dUdXModifier;              \
        UINT_007f4cf8 = (q5_floor_i(q5_f((long double)v0 * 65536.0f)) >> mip) + g_dwRdZRaster_dVdXModifier;              \
    }

#define Q5_ZPART(cnt, LIT, TEXEL, PIXEL)                                                                    \
    {                                                                                                       \
        int c_ = (cnt), i_;                                                                                 \
        unsigned z = UINT_007f4cfc, u = UINT_007f4cf4, v = UINT_007f4cf8, l = 0;                            \
        unsigned dz = UINT_007f4c54, du = UINT_007f4cdc, dv = UINT_007f4c44, dl = 0;                        \
        unsigned short *zb = (unsigned short *)UINT_007f4ca4, *pp = (unsigned short *)UINT_007f4cc4;        \
        if (LIT) {                                                                                          \
            l = UINT_007f4cf0;                                                                              \
            dl = UINT_007f4cb4;                                                                             \
        }                                                                                                   \
        UINT_007f4cb0 = c_;                                                                                 \
        for (i_ = 0; i_ < c_; i_++) {                                                                       \
            if ((unsigned short)z > zb[i_]) {                                                               \
                unsigned tx;                                                                                \
                zb[i_] = (unsigned short)z;                                                                 \
                tx = g_dwRdZRaster_pPixels[TEXEL];                                                                  \
                pp[i_] = PIXEL;                                                                             \
            }                                                                                               \
            z += dz;                                                                                        \
            u += du;                                                                                        \
            v += dv;                                                                                        \
            l += dl;                                                                                        \
        }                                                                                                   \
        UINT_007f4cfc = z;                                                                                  \
        UINT_007f4cf4 = u;                                                                                  \
        UINT_007f4cf8 = v;                                                                                  \
        if (LIT)                                                                                            \
            UINT_007f4cf0 = l;                                                                              \
        UINT_007f4cc4 += c_ * 2;                                                                            \
        UINT_007f4ca4 += c_ * 2;                                                                            \
    }

#define Q5_ZSPAN(NAME, LIT, TEXEL, PIXEL)                                                                   \
void NAME(q5_edge *L, q5_edge *R)                                                                           \
{                                                                                                           \
    int x0 = L->x, xs = (x0 & 0xffff) ? (x0 + 0x10000) & 0xffff0000 : x0;                                   \
    int xr = R->x, xl, n, r, first, chunks, rem, frac;                                                      \
    float oz, ouz, ovz, u0, v0, u1, v1;                                                                     \
    long double w;                                                                                          \
    char *c4;                                                                                               \
    if (xr & 0xffff)                                                                                        \
        xr = (xr + 0x10000) & 0xffff0000;                                                                   \
    xl = xs >> 16;                                                                                          \
    n = (xr >> 16) - xl;                                                                                    \
    UINT_007f4cac = n;                                                                                      \
    if (n <= 0)                                                                                             \
        return;                                                                                             \
    q5_fldcw(&DAT_00900528);                                                                                \
    r = xl % 16;                                                                                            \
    first = r ? (n < 16 - r ? n : 16 - r) : 0;                                                              \
    rem = n - first;                                                                                        \
    if (rem) {                                                                                              \
        chunks = rem / 16;                                                                                  \
        rem %= 16;                                                                                          \
        if (!rem) {                                                                                         \
            rem = 16;                                                                                       \
            chunks--;                                                                                       \
        }                                                                                                   \
    } else                                                                                                  \
        chunks = 0;                                                                                         \
    frac = xs - x0;                                                                                         \
    if (LIT) {                                                                                              \
        int dl = q5_mul16(R->l - L->l, g_aRdRaster_OneOverNFixed[n]);                                                    \
        if (dl < 0 && dl > -0x51e)                                                                          \
            dl = 0;                                                                                         \
        UINT_007f4cb4 = dl;                                                                                 \
        UINT_007f4cf0 = q5_mul16(frac, dl) + L->l;                                                          \
    }                                                                                                       \
    {                                                                                                       \
        long double f = (long double)frac * (1.0f / 65536.0f);                                              \
        oz = q5_f(f * g_dwRdZRaster_dOneOverZdX + L->z);                                                                 \
        ouz = q5_f(f * g_dwRdZRaster_dUOverZdX + L->uz);                                                               \
        ovz = q5_f(f * g_dwRdZRaster_dVOverZdX + L->vz);                                                               \
        UINT_007f4cfc = q5_floor_i(q5_f((long double)oz * 65536.0f));                                       \
    }                                                                                                       \
    q5_fldcw(&DAT_00900524);                                                                                \
    UINT_007f4c54 = g_dwRdZRaster_dOneOverZdXFixed;                                                                          \
    w = 1.0f / (long double)oz;                                                                             \
    c4 = *(char **)(g_pRdCamera_CurCamera + 4);                                                                \
    UINT_007f4cc4 = (int)Q5_BUF16(c4, L->y, xl);                                                            \
    UINT_007f4ca4 = (int)Q5_ZBUF(c4, L->y, xl);                                                             \
    u0 = q5_f(w * ouz);                                                                                     \
    v0 = q5_f(w * ovz);                                                                                     \
    if (first) {                                                                                            \
        long double k = first;                                                                              \
        float rk = g_dwRdRaster_aOneOverNFlex[first];                                                                    \
        float oz1 = q5_f(k * g_dwRdZRaster_dOneOverZdX + oz), uz1 = q5_f(k * g_dwRdZRaster_dUOverZdX + ouz),                         \
              vz1 = q5_f(k * g_dwRdZRaster_dVOverZdX + ovz);                                                           \
        w = 1.0f / (long double)oz1;                                                                        \
        u1 = q5_f(w * uz1);                                                                                 \
        v1 = q5_f(w * vz1);                                                                                 \
        Q5_ZUV(rk)                                                                                          \
        Q5_ZPART(first, LIT, TEXEL, PIXEL)                                                                  \
        oz = q5_f((long double)oz1 + g_dwRdZRaster_oneOverZStep);                                                         \
        u0 = u1;                                                                                            \
        v0 = v1;                                                                                            \
        ouz = q5_f((long double)uz1 + g_dwRdZRaster_uOverZStep);                                                        \
        ovz = q5_f((long double)vz1 + g_dwRdZRaster_vOverZStep);                                                        \
    } else {                                                                                                \
        oz = q5_f((long double)oz + g_dwRdZRaster_oneOverZStep);                                                          \
        ouz = q5_f((long double)ouz + g_dwRdZRaster_uOverZStep);                                                        \
        ovz = q5_f((long double)ovz + g_dwRdZRaster_vOverZStep);                                                        \
    }                                                                                                       \
    for (; chunks > 0; chunks--) {                                                                          \
        w = 1.0f / (long double)oz;                                                                         \
        u1 = q5_f(w * ouz);                                                                                 \
        v1 = q5_f(w * ovz);                                                                                 \
        Q5_ZUV(0.0625f)                                                                                     \
        Q5_ZPART(16, LIT, TEXEL, PIXEL)                                                                     \
        oz = q5_f((long double)oz + g_dwRdZRaster_oneOverZStep);                                                          \
        u0 = u1;                                                                                            \
        v0 = v1;                                                                                            \
        ouz = q5_f((long double)ouz + g_dwRdZRaster_uOverZStep);                                                        \
        ovz = q5_f((long double)ovz + g_dwRdZRaster_vOverZStep);                                                        \
    }                                                                                                       \
    if (rem) {                                                                                              \
        if (--rem) {                                                                                        \
            long double k = rem;                                                                            \
            float rk = g_dwRdRaster_aOneOverNFlex[rem];                                                                  \
            w = 1.0f / ((k * g_dwRdZRaster_dOneOverZdX - g_dwRdZRaster_oneOverZStep) + oz);                                            \
            u1 = q5_f(((k * g_dwRdZRaster_dUOverZdX - g_dwRdZRaster_uOverZStep) + ouz) * w);                                       \
            v1 = q5_f(((k * g_dwRdZRaster_dVOverZdX - g_dwRdZRaster_vOverZStep) + ovz) * w);                                       \
            Q5_ZUV(rk)                                                                                      \
        }                                                                                                   \
        Q5_ZPART(rem + 1, LIT, TEXEL, PIXEL)                                                                \
    }                                                                                                       \
    q5_fldcw(&DAT_00900524);                                                                                \
}
/* the texel index for a fixed width (v shift 16 - log2 w, u mask (w - 1) << 16) and for any width */
#define Q5_ZT(S, M) (((int)v >> (S)) & g_dwRdZRaster_vWrap) | (int)((u & (M)) >> 16)
#define Q5_ZTG (((int)v >> ((16 - g_dwRdZRaster_texRowShift) & 31)) & g_dwRdZRaster_vWrap) | ((int)(u & g_dwRdZRaster_uWrap) >> 16)
#define Q5_ZPAL g_dwRdZRaster_aRGBMap[tx]
#define Q5_ZPALL g_dwRdZRaster_aRGBMap[tx + ((l & 0x3f0000) >> 8)]
/* OVERRIDES: rdRaster_Span16_TexZw_8 */
Q5_ZSPAN(rdRaster_Span16_TexZw_8, 0, Q5_ZTG, Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexZw_9 */
Q5_ZSPAN(rdRaster_Span16_TexZw_9, 0, Q5_ZT(13, 0x70000), Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexZw_10 */
Q5_ZSPAN(rdRaster_Span16_TexZw_10, 0, Q5_ZT(12, 0xf0000), Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexZw_11 */
Q5_ZSPAN(rdRaster_Span16_TexZw_11, 0, Q5_ZT(11, 0x1f0000), Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexLitZw_31 */
Q5_ZSPAN(rdRaster_Span16_TexLitZw_31, 0, Q5_ZT(10, 0x3f0000), Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexZw_12 */
Q5_ZSPAN(rdRaster_Span16_TexZw_12, 0, Q5_ZT(9, 0x7f0000), Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexZw_13 */
Q5_ZSPAN(rdRaster_Span16_TexZw_13, 0, Q5_ZT(8, 0xff0000), Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexZw_2 */
Q5_ZSPAN(rdRaster_Span16_TexZw_2, 0, Q5_ZTG, Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexZw_3 */
Q5_ZSPAN(rdRaster_Span16_TexZw_3, 0, Q5_ZT(13, 0x70000), Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexZw_4 */
Q5_ZSPAN(rdRaster_Span16_TexZw_4, 0, Q5_ZT(12, 0xf0000), Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexZw_5 */
Q5_ZSPAN(rdRaster_Span16_TexZw_5, 0, Q5_ZT(11, 0x1f0000), Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexLitZw_23 */
Q5_ZSPAN(rdRaster_Span16_TexLitZw_23, 0, Q5_ZT(10, 0x3f0000), Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexZw_6 */
Q5_ZSPAN(rdRaster_Span16_TexZw_6, 0, Q5_ZT(9, 0x7f0000), Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexZw_7 */
Q5_ZSPAN(rdRaster_Span16_TexZw_7, 0, Q5_ZT(8, 0xff0000), Q5_ZPAL)
/* OVERRIDES: rdRaster_Span16_TexZw */
Q5_ZSPAN(rdRaster_Span16_TexZw, 1, Q5_ZTG, g_dwRdZRaster_aRGBMap[tx + ((int)l >> 8)])
/* OVERRIDES: rdRaster_Span16_TexLitZw_9 */
Q5_ZSPAN(rdRaster_Span16_TexLitZw_9, 1, Q5_ZT(13, 0x70000), Q5_ZPALL)
/* OVERRIDES: rdRaster_Span16_TexLitZw_10 */
Q5_ZSPAN(rdRaster_Span16_TexLitZw_10, 1, Q5_ZT(12, 0xf0000), Q5_ZPALL)
/* OVERRIDES: rdRaster_Span16_TexLitZw_11 */
Q5_ZSPAN(rdRaster_Span16_TexLitZw_11, 1, Q5_ZT(11, 0x1f0000), Q5_ZPALL)
/* OVERRIDES: rdRaster_Span16_TexLitZw_12 */
Q5_ZSPAN(rdRaster_Span16_TexLitZw_12, 1, Q5_ZT(10, 0x3f0000), Q5_ZPALL)
/* OVERRIDES: rdRaster_Span16_TexLitZw_13 */
Q5_ZSPAN(rdRaster_Span16_TexLitZw_13, 1, Q5_ZT(9, 0x7f0000), Q5_ZPALL)
/* OVERRIDES: rdRaster_Span16_TexLitZw_14 */
Q5_ZSPAN(rdRaster_Span16_TexLitZw_14, 1, Q5_ZT(8, 0xff0000), Q5_ZPALL)

/* ==== the drivers ==== */
#define Q5_P_COUNT 0x1c
#define Q5_P_VERTS 0x20
#define Q5_P_UV 0x24
#define Q5_P_LIGHT 0x28
#define Q5_P_TABLES 0x4c  /* -> +0x330 light table 8 bpp, +0x348 light table 16 bpp, +0x34c 16 bpp -> index */
#define Q5_P_FLIP 0x50
#define Q5_P_DIST 0x64
#define Q5_P_TOP 0x6c
#define Q5_P_BOTTOM 0x70
#define Q5_BPP() Q5_I(Q5_I(Q5_I(g_pRdCamera_CurCamera, 4), 4), 0x24)

/* LIGHT 0: unlit (16 bpp: row 63 of the light table), 1: the polygon's light level (floor of the float argument)
 * selects the row, 2: per-vertex light.  TRANS: the translucency tables.  OPAQUE: the mip level's width for the
 * filler choice.  Then Grad_Flat_4, the texture globals of the mip level, and the 16-pixel steps float(16 * d/dx) of
 * the three planes. */
Q5_INLINE void q5_tex_setup(char *p, char *mat, int light_mode, int trans, int opaque, int li)
{
    int bpp = Q5_BPP(), mip;
    char *tb = *(char **)(p + Q5_P_TABLES), *tex = *(char **)(mat + 0x1c), *lev;
    g_dwRdZRaster_maxMipMap = Q5_I(tex, 0x18) - 1;
    g_pRdZRaster_aVertices = *(float **)(p + Q5_P_VERTS);
    g_dwRdZRaster_aTexVertices = *(float **)(p + Q5_P_UV);
    if (light_mode == 2)
        g_dwRdZRaster_aIntensities = *(float **)(p + Q5_P_LIGHT);
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
    g_dwRdZRaster_numVertices = Q5_I(p, Q5_P_COUNT);
    g_dwRdZRaster_yMinVert = Q5_I(p, Q5_P_TOP);
    g_dwRdZRaster_yMaxVert = Q5_I(p, Q5_P_BOTTOM);
    g_dwRdZRaster_zScaleShift = Q5_I(Q5_I(g_pRdCamera_CurCamera, 4), 0x14);
    if (Q5_I(p, Q5_P_FLIP)) {
        g_dwRdZRaster_leftVertexStep = -1;
        g_dwRdZRaster_rightVertexStep = 1;
    } else {
        g_dwRdZRaster_leftVertexStep = 1;
        g_dwRdZRaster_rightVertexStep = -1;
    }
    rdZRaster_CalcPerspGradients(Q5_I(p, Q5_P_DIST));
    mip = g_dwRdZRaster_mipMapNum;
    lev = *(char **)(tex + 0x1c + mip * 4);
    g_dwRdZRaster_oneOverZStep = q5_f((long double)g_dwRdZRaster_dOneOverZdX * 16.0f);
    g_dwRdZRaster_pPixels = *(unsigned char **)(lev + 0x5c);
    g_dwRdZRaster_texRowShift = Q5_I(tex, 0xc) - mip;
    if (opaque)
        g_dwRdZRaster_texPitch = Q5_I(lev, 0x18);
    g_dwRdZRaster_uWrap = (int)(((unsigned)Q5_I(tex, 0x10) >> (mip & 31)) << 16);
    g_dwRdZRaster_uOverZStep = q5_f((long double)g_dwRdZRaster_dUOverZdX * 16.0f);
    g_dwRdZRaster_vOverZStep = q5_f((long double)g_dwRdZRaster_dVOverZdX * 16.0f);
    g_dwRdZRaster_vWrap = (int)(((unsigned)Q5_I(tex, 0x14) >> (mip & 31)) << (g_dwRdZRaster_texRowShift & 31));
}

/* walk the two edges: one span per scan line (SPAN), then step each edge (or set up its next vertex pair); the left
 * edge carries the three plane values, both carry light with LIT */
#define Q5_WALK(EL, ER, PRE, SPAN, LIT)                                                                     \
    do {                                                                                                    \
        q5_edge L, R;                                                                                       \
        L.idx = g_dwRdZRaster_yMinVert;                                                                              \
        if (EL(&L))                                                                                         \
            return;                                                                                         \
        R.idx = g_dwRdZRaster_yMinVert;                                                                              \
        if (ER(&R))                                                                                         \
            return;                                                                                         \
        PRE;                                                                                                \
        for (;;) {                                                                                          \
            SPAN;                                                                                           \
            if (--L.h == 0) {                                                                               \
                if (EL(&L))                                                                                 \
                    return;                                                                                 \
            } else {                                                                                        \
                L.z = q5_f((long double)L.z + L.dz);                                                        \
                L.uz = q5_f((long double)L.uz + L.duz);                                                     \
                L.vz = q5_f((long double)L.vz + L.dvz);                                                     \
                L.x += L.dx;                                                                                \
                if (LIT)                                                                                    \
                    L.l += L.dl;                                                                            \
                L.y++;                                                                                      \
            }                                                                                               \
            if (--R.h == 0) {                                                                               \
                if (ER(&R))                                                                                 \
                    return;                                                                                 \
            } else {                                                                                        \
                R.x += R.dx;                                                                                \
                if (LIT)                                                                                    \
                    R.l += R.dl;                                                                            \
                R.y++;                                                                                      \
            }                                                                                               \
        }                                                                                                   \
    } while (0)
#define Q5_SPAN_BPP(bpp, S8, S16)                                                                           \
    if ((bpp) == 8)                                                                                         \
        S8(&L, &R);                                                                                         \
    else if ((bpp) == 16)                                                                                   \
        S16(&L, &R)

/* span choice of the opaque drivers: with a z shift the filler of the depth; without, 8 bpp gets the empty
 * Mem_DumpLog and 16 bpp a filler specialised for the texture width (W8 .. W256: widths 8, 16, ..., 256; D any
 * other); another depth keeps the previous pointer */
#define Q5_PICK(bpp, S8, S16, W8, W16, W32, W64, W128, W256, D)                                              \
    if (g_dwRdZRaster_zScaleShift) {                                                                                    \
        if ((bpp) == 8)                                                                                     \
            UINT_007f44f0 = (void *)S8;                                                                     \
        else if ((bpp) == 16)                                                                               \
            UINT_007f44f0 = (void *)S16;                                                                    \
    } else if ((bpp) == 8)                                                                                  \
        UINT_007f44f0 = (void *)Mem_DumpLog;                                                                \
    else if ((bpp) == 16) {                                                                                 \
        switch (g_dwRdZRaster_texPitch) {                                                                            \
        case 8: UINT_007f44f0 = (void *)W8; break;                                                          \
        case 16: UINT_007f44f0 = (void *)W16; break;                                                        \
        case 32: UINT_007f44f0 = (void *)W32; break;                                                        \
        case 64: UINT_007f44f0 = (void *)W64; break;                                                        \
        case 128: UINT_007f44f0 = (void *)W128; break;                                                      \
        case 256: UINT_007f44f0 = (void *)W256; break;                                                      \
        default: UINT_007f44f0 = (void *)D; break;                                                          \
        }                                                                                                   \
    }

/* the opaque drivers: the span filler is chosen once, after the first two edge set-ups, into UINT_007f44f0 */
#define Q5_ODRAW(NAME, LIGHT, EL, ER, S8, S16, W8, W16, W32, W64, W128, W256, D)                           \
    {                                                                                                       \
        int bpp = Q5_BPP();                                                                                 \
        q5_tex_setup(p, mat, LIGHT, 0, 1, (LIGHT) == 1 && (bpp == 8 || bpp == 16) ? q5_floor_i(light) : 0); \
        Q5_WALK(EL, ER, Q5_PICK(bpp, S8, S16, W8, W16, W32, W64, W128, W256, D),                            \
                ((q5_span_fn)UINT_007f44f0)(&L, &R), (LIGHT) == 2);                                         \
    }
/* OVERRIDES: rdZRaster_DrawNGonLIT */
void rdZRaster_DrawNGonLIT(char *p, char *mat)
{
    float light = 0.0f;
    Q5_ODRAW(rdZRaster_DrawNGonLIT, 0, rdZRaster_SetupLeftEdgeNGonLIT, rdZRaster_SetupRightEdgeNGonLIT, rdZRaster_DrawScanLineNGonLIT_8,
             rdZRaster_DrawScanLineNGonLIT_16, rdRaster_Span16_TexZw_9, rdRaster_Span16_TexZw_10, rdRaster_Span16_TexZw_11,
             rdRaster_Span16_TexLitZw_31, rdRaster_Span16_TexZw_12, rdRaster_Span16_TexZw_13, rdRaster_Span16_TexZw_8)
}
/* OVERRIDES: rdZRaster_DrawNGonFIT */
void rdZRaster_DrawNGonFIT(char *p, char *mat, float light)
{
    Q5_ODRAW(rdZRaster_DrawNGonFIT, 1, rdZRaster_SetupLeftEdgeNGonFIT, rdZRaster_SetupRightEdgeNGonFIT, rdZRaster_DrawScanLineNGonFIT_8,
             rdZRaster_DrawScanLineNGonFIT_16, rdRaster_Span16_TexZw_3, rdRaster_Span16_TexZw_4, rdRaster_Span16_TexZw_5,
             rdRaster_Span16_TexLitZw_23, rdRaster_Span16_TexZw_6, rdRaster_Span16_TexZw_7, rdRaster_Span16_TexZw_2)
}
/* OVERRIDES: rdZRaster_DrawNGonGIT */
void rdZRaster_DrawNGonGIT(char *p, char *mat)
{
    float light = 0.0f;
    Q5_ODRAW(rdZRaster_DrawNGonGIT, 2, rdZRaster_SetupLeftEdgeNGonGIT, rdZRaster_SetupRightEdgeNGonGIT, rdZRaster_DrawScanLineNGonGIT_8,
             rdZRaster_DrawScanLineNGonGIT_16, rdRaster_Span16_TexLitZw_9, rdRaster_Span16_TexLitZw_10,
             rdRaster_Span16_TexLitZw_11, rdRaster_Span16_TexLitZw_12, rdRaster_Span16_TexLitZw_13,
             rdRaster_Span16_TexLitZw_14, rdRaster_Span16_TexZw)
}

/* the translucent / keyed drivers call their 8 or 16 bpp filler directly */
#define Q5_TDRAW(NAME, LIGHT, TRANS, EL, ER, S8, S16)                                                       \
void NAME(char *p, char *mat)                                                                               \
{                                                                                                           \
    int bpp = Q5_BPP();                                                                                     \
    q5_tex_setup(p, mat, LIGHT, TRANS, 0, 0);                                                               \
    Q5_WALK(EL, ER, , Q5_SPAN_BPP(bpp, S8, S16), (LIGHT) == 2);                                             \
}
#define Q5_TDRAW_L(NAME, TRANS, EL, ER, S8, S16)                                                            \
void NAME(char *p, char *mat, float light)                                                                  \
{                                                                                                           \
    int bpp = Q5_BPP();                                                                                     \
    q5_tex_setup(p, mat, 1, TRANS, 0, bpp == 8 || bpp == 16 ? q5_floor_i(light) : 0);                       \
    Q5_WALK(EL, ER, , Q5_SPAN_BPP(bpp, S8, S16), 0);                                                        \
}
/* OVERRIDES: rdZRaster_DrawNGonTLIT */
Q5_TDRAW(rdZRaster_DrawNGonTLIT, 0, 1, rdZRaster_SetupLeftEdgeNGonLIT, rdZRaster_SetupRightEdgeNGonLIT, rdZRaster_DrawScanLineNGonTLIT_8,
         rdZRaster_DrawScanLineNGonTLIT_16)
/* OVERRIDES: rdZRaster_DrawNGonTFIT */
Q5_TDRAW_L(rdZRaster_DrawNGonTFIT, 1, rdZRaster_SetupLeftEdgeNGonFIT, rdZRaster_SetupRightEdgeNGonFIT, rdZRaster_DrawScanLineNGonTFIT_8,
           rdZRaster_DrawScanLineNGonTFIT_16)
/* OVERRIDES: rdZRaster_DrawNGonTGIT */
Q5_TDRAW(rdZRaster_DrawNGonTGIT, 2, 1, rdZRaster_SetupLeftEdgeNGonGIT, rdZRaster_SetupRightEdgeNGonGIT, rdZRaster_DrawScanLineNGonTGIT_8,
         rdZRaster_DrawScanLineNGonTGIT_16)
/* OVERRIDES: rdZRaster_DrawNGonMLIT */
Q5_TDRAW(rdZRaster_DrawNGonMLIT, 0, 0, rdZRaster_SetupLeftEdgeNGonLIT, rdZRaster_SetupRightEdgeNGonLIT,
         rdZRaster_DrawScanLineNGonMLIT_8, rdZRaster_DrawScanLineNGonMLIT_16)
/* OVERRIDES: rdZRaster_DrawNGonMTLIT */
Q5_TDRAW(rdZRaster_DrawNGonMTLIT, 0, 1, rdZRaster_SetupLeftEdgeNGonLIT, rdZRaster_SetupRightEdgeNGonLIT, rdZRaster_DrawScanLineNGonMTLIT_8,
         rdZRaster_DrawScanLineNGonMTLIT_16)
/* OVERRIDES: rdZRaster_DrawNGonMFIT */
Q5_TDRAW_L(rdZRaster_DrawNGonMFIT, 0, rdZRaster_SetupLeftEdgeNGonFIT, rdZRaster_SetupRightEdgeNGonFIT, rdZRaster_DrawScanLineNGonMFIT_8,
           rdZRaster_DrawScanLineNGonMFIT_16)
/* OVERRIDES: rdZRaster_DrawNGonMTFIT */
Q5_TDRAW_L(rdZRaster_DrawNGonMTFIT, 1, rdZRaster_SetupLeftEdgeNGonFIT, rdZRaster_SetupRightEdgeNGonFIT, rdZRaster_DrawScanLineNGonMTFIT_8,
           rdZRaster_DrawScanLineNGonMTFIT_16)
/* OVERRIDES: rdZRaster_DrawNGonMGIT */
Q5_TDRAW(rdZRaster_DrawNGonMGIT, 2, 0, rdZRaster_SetupLeftEdgeNGonGIT, rdZRaster_SetupRightEdgeNGonGIT, rdZRaster_DrawScanLineNGonMGIT_8,
         rdZRaster_DrawScanLineNGonMGIT_16)
/* OVERRIDES: rdZRaster_DrawNGonMTGIT */
Q5_TDRAW(rdZRaster_DrawNGonMTGIT, 2, 1, rdZRaster_SetupLeftEdgeNGonGIT, rdZRaster_SetupRightEdgeNGonGIT, rdZRaster_DrawScanLineNGonMTGIT_8,
         rdZRaster_DrawScanLineNGonMTGIT_16)

/* ==== the span fillers of the renderer without z-buffer (0x00451fa0 .. 0x00459750) ====
 * Called per span by the span drivers of build/overrides_asm_p1.c (rdAFRaster_DrawNGonLAT .. rdAFRaster_DrawNGonGIT) with a span record:
 * +0 x (pixel), +4 count, +8 y; affine: +0xc u, +0x10 du, +0x14 v, +0x18 dv (16.16); perspective: +0xc u/z,
 * +0x10 v/z, +0x1c 1/z (floats); +0x1c the z (float) for the z-buffer writers; +0x20 light, +0x24 its step (16.16).
 * Their state lives in globals (0x007f4ac8 .. 0x007f4b74, 0x008dde40), the texture in 0x008ddf04 .. 0x008ddf4c (mip
 * shift, log2 width, masks, u / v biases, the 16 bpp palette, the texels, the perspective plane steps).  Each part of
 * a span is drawn from its last pixel to its first, as in the original. */
extern int DAT_007f4ac8, UINT_007f4acc, UINT_007f4ad0, DAT_007f4ad4, UINT_007f4adc, DAT_007f4ae4, DAT_007f4aec,
    DAT_007f4af0, DAT_007f4af4, DAT_007f4af8, UINT_007f4b28, UINT_007f4b2c, UINT_007f4b30, DAT_007f4b34, DAT_007f4b38,
    UINT_007f4b3c, UINT_007f4b40, UINT_007f4b44, UINT_007f4b48, UINT_007f4b4c, UINT_007f4b50, UINT_007f4b54,
    DAT_007f4b58, DAT_007f4b5c, DAT_007f4b60, DAT_007f4b64, UINT_007f4b68, UINT_007f4b6c, UINT_007f4b70, UINT_007f4b74;
extern int UINT_008dde40, g_dwRdAFRaster_mipMapNum, g_dwRdAFRaster_texRowShift, g_dwRdAFRaster_vWrap, g_dwRdAFRaster_dVdXModifier, g_dwRdAFRaster_dOneOverZdXFixed, g_dwRdAFRaster_dUdXModifier,
    g_dwRdAFRaster_uWrap;
extern float g_dwRdAFRaster_dOneOverZdX, g_dwRdAFRaster_dUOverZdX, g_dwRdAFRaster_oneOverZStep, g_dwRdAFRaster_uOverZStep, g_dwRdAFRaster_dVOverZdX, g_dwRdAFRaster_vOverZStep;
extern unsigned short *g_dwRdAFRaster_aRGBMap;   /* 16 bpp palette (light row) */
extern unsigned char *g_dwRdAFRaster_pPixels;    /* texels */
#define Q5_GF(sym) (*(float *)&(sym))
#define Q5_CANVAS() (*(char **)(g_pRdCamera_CurCamera + 4))

/* ---- SpanR_FlatZw, _2: the z-buffer pass ----
 * z = floor(float(z * 65536)), stepped by 0x008ddf24, written (>> the canvas' z shift in _2, logical) to x .. x + count
 * - 1 of the row: a 16-bit store up to a 4-byte boundary, then pairs (one 32-bit store), then the odd last one.  _2
 * counts the first store off the global count. */
#define Q5_ZWRITE(NAME, SHIFT)                                                                              \
void NAME(int *s)                                                                                           \
{                                                                                                           \
    char *zd = *(char **)(Q5_CANVAS() + 0x10);                                                              \
    unsigned short *p;                                                                                      \
    unsigned z, dz, c, k, sh = 0;                                                                           \
    UINT_007f4b28 = s[2] * Q5_I(zd, 0x18) + s[0] * 2 + Q5_I(zd, 0x5c);                                      \
    if (SHIFT)                                                                                              \
        UINT_007f4b40 = Q5_I(Q5_CANVAS(), 0x14);                                                            \
    UINT_007f4b74 = q5_floor_i(q5_f(*(float *)&s[7] * 65536.0f));                                           \
    UINT_007f4ad0 = s[1];                                                                                   \
    p = (unsigned short *)UINT_007f4b28;                                                                    \
    z = UINT_007f4b74;                                                                                      \
    dz = g_dwRdAFRaster_dOneOverZdXFixed;                                                                                     \
    c = UINT_007f4ad0;                                                                                      \
    if (SHIFT)                                                                                              \
        sh = UINT_007f4b40 & 31;                                                                            \
    if ((int)p & 2) {                                                                                       \
        *p++ = (unsigned short)(z >> sh);                                                                   \
        z += dz;                                                                                            \
        c--;                                                                                                \
        if (SHIFT)                                                                                          \
            UINT_007f4ad0 = c;                                                                              \
    }                                                                                                       \
    for (k = c >> 1; k; k--) {                                                                              \
        p[0] = (unsigned short)(z >> sh);                                                                   \
        z += dz;                                                                                            \
        p[1] = (unsigned short)(z >> sh);                                                                   \
        z += dz;                                                                                            \
        p += 2;                                                                                             \
    }                                                                                                       \
    if (c & 1)                                                                                              \
        *p = (unsigned short)(z >> sh);                                                                     \
}
/* OVERRIDES: rdRaster_SpanR_FlatZw */
Q5_ZWRITE(rdRaster_SpanR_FlatZw, 0)
/* OVERRIDES: rdRaster_SpanR_FlatZw_2 */
Q5_ZWRITE(rdRaster_SpanR_FlatZw_2, 1)

/* the pixels of a part: 0x008dde40 pixels from the destination 0x007f4b3c, with u, v (, light) in the globals at the
 * last pixel; afterwards they are one step past it (MEM: the original keeps them in memory during the loop and adds
 * (count + 1) steps after it, which differs only for a count <= 0, when one pixel, at index count - 1, is drawn).
 * TEXEL: the texel index; PIXEL: the colour from tx (the texel) and l */
#define Q5_NPART(LIT, MEM, TEXEL, PIXEL)                                                                    \
    {                                                                                                       \
        unsigned short *pp = (unsigned short *)UINT_007f4b3c;                                               \
        int c_ = UINT_008dde40, i_ = c_ - 1;                                                                \
        unsigned u = UINT_007f4b6c, v = UINT_007f4b70, l = 0, du = UINT_007f4b54, dv = UINT_007f4adc, dl = 0;\
        if (LIT) {                                                                                          \
            l = UINT_007f4b68;                                                                              \
            dl = UINT_007f4b30;                                                                             \
        }                                                                                                   \
        do {                                                                                                \
            unsigned tx = g_dwRdAFRaster_pPixels[TEXEL];                                                             \
            pp[i_] = PIXEL;                                                                                 \
            u -= du;                                                                                        \
            v -= dv;                                                                                        \
            l -= dl;                                                                                        \
        } while (--i_ >= 0);                                                                                \
        if (MEM) {                                                                                          \
            UINT_007f4b6c = u + du * (c_ + 1);                                                              \
            UINT_007f4b70 = v + dv * (c_ + 1);                                                              \
            if (LIT)                                                                                        \
                UINT_007f4b68 = l + dl * (c_ + 1);                                                          \
        } else {                                                                                            \
            UINT_007f4b6c += du;                                                                            \
            UINT_007f4b70 += dv;                                                                            \
            if (LIT)                                                                                        \
                UINT_007f4b68 += dl;                                                                        \
        }                                                                                                   \
        UINT_007f4b3c += c_ * 2;                                                                            \
    }
/* texel index: fixed width (v shift 16 - log2 w, u mask), any width */
#define Q5_NT(S, M) (((int)v >> (S)) & g_dwRdAFRaster_vWrap) | (int)((u & (M)) >> 16)
#define Q5_NTG (((int)v >> ((16 - g_dwRdAFRaster_texRowShift) & 31)) & g_dwRdAFRaster_vWrap) | ((int)(u & g_dwRdAFRaster_uWrap) >> 16)
#define Q5_NPAL g_dwRdAFRaster_aRGBMap[tx]
#define Q5_NPALL g_dwRdAFRaster_aRGBMap[tx + ((l & 0x3f0000) >> 8)]

/* ---- SpanR16_*: affine ----
 * u, v (+ light) and their steps from the record, u + the u bias 0x008ddf44, v + the v bias 0x008ddf18; one part. */
#define Q5_RSPAN(NAME, LIT, MEM, TEXEL, PIXEL)                                                              \
void NAME(int *s)                                                                                           \
{                                                                                                           \
    char *cd = *(char **)(Q5_CANVAS() + 4);                                                                 \
    int n1;                                                                                                 \
    UINT_007f4b54 = s[4];                                                                                   \
    UINT_007f4b6c = s[3];                                                                                   \
    UINT_007f4adc = s[6];                                                                                   \
    UINT_007f4b70 = s[5];                                                                                   \
    if (LIT) {                                                                                              \
        UINT_007f4b30 = s[9];                                                                               \
        UINT_007f4b68 = s[8];                                                                               \
    }                                                                                                       \
    UINT_007f4b3c = Q5_I(cd, 0x5c) + (((unsigned)Q5_I(cd, 0x18) >> 1) * s[2] + s[0]) * 2;                   \
    UINT_007f4b6c += g_dwRdAFRaster_dUdXModifier;                                                                         \
    UINT_007f4b70 += g_dwRdAFRaster_dVdXModifier;                                                                         \
    UINT_008dde40 = s[1];                                                                                   \
    n1 = s[1] - 1;                                                                                          \
    UINT_007f4b6c += UINT_007f4b54 * n1;                                                                    \
    UINT_007f4b70 += UINT_007f4adc * n1;                                                                    \
    if (LIT)                                                                                                \
        UINT_007f4b68 += UINT_007f4b30 * n1;                                                                \
    Q5_NPART(LIT, MEM, TEXEL, PIXEL)                                                                        \
}
/* OVERRIDES: rdRaster_SpanR16_Tex */
Q5_RSPAN(rdRaster_SpanR16_Tex, 0, 1, Q5_NTG, Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_Tex_2 */
Q5_RSPAN(rdRaster_SpanR16_Tex_2, 0, 0, Q5_NT(13, 0x70000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_Tex_3 */
Q5_RSPAN(rdRaster_SpanR16_Tex_3, 0, 0, Q5_NT(12, 0xf0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_Tex_4 */
Q5_RSPAN(rdRaster_SpanR16_Tex_4, 0, 0, Q5_NT(11, 0x1f0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_TexLit */
Q5_RSPAN(rdRaster_SpanR16_TexLit, 0, 0, Q5_NT(10, 0x3f0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_Tex_5 */
Q5_RSPAN(rdRaster_SpanR16_Tex_5, 0, 0, Q5_NT(9, 0x7f0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_Tex_6 */
Q5_RSPAN(rdRaster_SpanR16_Tex_6, 0, 0, Q5_NT(8, 0xff0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_Tex_7 */
Q5_RSPAN(rdRaster_SpanR16_Tex_7, 0, 1, Q5_NTG, Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_Tex_8 */
Q5_RSPAN(rdRaster_SpanR16_Tex_8, 0, 0, Q5_NT(13, 0x70000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_Tex_9 */
Q5_RSPAN(rdRaster_SpanR16_Tex_9, 0, 0, Q5_NT(12, 0xf0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_Tex_10 */
Q5_RSPAN(rdRaster_SpanR16_Tex_10, 0, 0, Q5_NT(11, 0x1f0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_TexLit_2 */
Q5_RSPAN(rdRaster_SpanR16_TexLit_2, 0, 0, Q5_NT(10, 0x3f0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_Tex_11 */
Q5_RSPAN(rdRaster_SpanR16_Tex_11, 0, 0, Q5_NT(9, 0x7f0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_Tex_12 */
Q5_RSPAN(rdRaster_SpanR16_Tex_12, 0, 0, Q5_NT(8, 0xff0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanR16_TexLit_3 */
Q5_RSPAN(rdRaster_SpanR16_TexLit_3, 1, 1, Q5_NTG, Q5_NPALL)
/* OVERRIDES: rdRaster_SpanR16_TexLit_4 */
Q5_RSPAN(rdRaster_SpanR16_TexLit_4, 1, 0, Q5_NT(13, 0x70000), Q5_NPALL)
/* OVERRIDES: rdRaster_SpanR16_TexLit_5 */
Q5_RSPAN(rdRaster_SpanR16_TexLit_5, 1, 0, Q5_NT(12, 0xf0000), Q5_NPALL)
/* OVERRIDES: rdRaster_SpanR16_TexLit_6 */
Q5_RSPAN(rdRaster_SpanR16_TexLit_6, 1, 0, Q5_NT(11, 0x1f0000), Q5_NPALL)
/* OVERRIDES: rdRaster_SpanR16_TexLit_7 */
Q5_RSPAN(rdRaster_SpanR16_TexLit_7, 1, 0, Q5_NT(10, 0x3f0000), Q5_NPALL)
/* OVERRIDES: rdRaster_SpanR16_TexLit_8 */
Q5_RSPAN(rdRaster_SpanR16_TexLit_8, 1, 0, Q5_NT(9, 0x7f0000), Q5_NPALL)
/* OVERRIDES: rdRaster_SpanR16_TexLit_9 */
Q5_RSPAN(rdRaster_SpanR16_TexLit_9, 1, 0, Q5_NT(8, 0xff0000), Q5_NPALL)

/* ---- SpanP16_*: perspective ----
 * The same parts as the z-buffered fillers, cut at screen x multiples of 16 (the first part up to the next one: x & 15,
 * not a remainder), with the state in globals: the start values 1/z, u/z, v/z (copied as dwords), w = 1 / (1/z),
 * u0 = float(w * u/z), v0 = float(float(w) * v/z) (v uses the rounded w); per part the plane values at its end (first
 * part: float(float(k) * d/dx + start); chunks: the advanced values; last part: float((float(k - 1) * d/dx - 16 d/dx)
 * + plane), stored), w, u1, v1 the same way, du = floor(float((u1 - u0) * 1/k * 65536)) >> mip (1/k the float of
 * 0x008fe000, chunks 0.0625), u = floor(float(u0 * 65536)) >> mip + bias.  After the first part and each chunk u0, v0,
 * w take u1, v1, w and the plane values advance by 16 d/dx; the chunk counter ends at -1.  The control word truncates
 * at 24 bits from the start up to the first float -> int conversion (q5_cvt; when the first part and the chunks are
 * empty and the last part has one pixel there is none, and it stays truncating to the end, as in the original).
 * Without a first part u, v and their steps are those of the previous span until the first chunk. */
#define Q5_CVT(x) q5_cvt(x, &tr)
Q5_INLINE int q5_cvt(float x, int *tr)
{
    int r = q5_floor_i(x);
    if (*tr) {
        q5_fldcw(&DAT_00900524);
        *tr = 0;
    }
    return r;
}
/* w = 1 / (1/z) at the part's end; u1, v1 */
#define Q5_PW()                                                                                             \
    {                                                                                                       \
        long double w_ = 1.0f / (long double)Q5_GF(DAT_007f4b38);                                           \
        Q5_GF(UINT_007f4b50) = q5_f(w_);                                                                    \
        Q5_GF(UINT_007f4b48) = q5_f(w_ * Q5_GF(DAT_007f4b64));                                              \
        Q5_GF(UINT_007f4b4c) = q5_f((long double)Q5_GF(UINT_007f4b50) * Q5_GF(DAT_007f4ad4));               \
    }
/* du, dv, u and the raw v of a part over 1/k = rk */
#define Q5_PUV(rk)                                                                                          \
    {                                                                                                       \
        UINT_007f4b54 =                                                                                     \
            Q5_CVT(q5_f(((long double)Q5_GF(UINT_007f4b48) - Q5_GF(DAT_007f4b58)) * (rk) * 65536.0f)) >>     \
            (g_dwRdAFRaster_mipMapNum & 31);                                                                           \
        UINT_007f4adc =                                                                                     \
            Q5_CVT(q5_f(((long double)Q5_GF(UINT_007f4b4c) - Q5_GF(DAT_007f4b5c)) * (rk) * 65536.0f)) >>     \
            (g_dwRdAFRaster_mipMapNum & 31);                                                                           \
        UINT_007f4b6c =                                                                                     \
            (Q5_CVT(q5_f((long double)Q5_GF(DAT_007f4b58) * 65536.0f)) >> (g_dwRdAFRaster_mipMapNum & 31)) + g_dwRdAFRaster_dUdXModifier;\
        vraw = Q5_CVT(q5_f((long double)Q5_GF(DAT_007f4b5c) * 65536.0f));                                   \
    }
/* u, v (, light) at the part's last pixel */
#define Q5_PLAST(k, LIT)                                                                                    \
    UINT_008dde40 = (k);                                                                                    \
    UINT_007f4b6c += UINT_007f4b54 * ((k) - 1);                                                             \
    UINT_007f4b70 = (vraw >> (g_dwRdAFRaster_mipMapNum & 31)) + (g_dwRdAFRaster_dVdXModifier + UINT_007f4adc * ((k) - 1));           \
    if (LIT)                                                                                                \
        UINT_007f4b68 += UINT_007f4b30 * ((k) - 1);
/* the plane values advance by 16 pixels; u0, v0, w take the part's end values */
#define Q5_PNEXT()                                                                                          \
    Q5_GF(DAT_007f4b38) = q5_f((long double)Q5_GF(DAT_007f4b38) + g_dwRdAFRaster_oneOverZStep);                            \
    Q5_GF(DAT_007f4b64) = q5_f((long double)Q5_GF(DAT_007f4b64) + g_dwRdAFRaster_uOverZStep);                            \
    Q5_GF(DAT_007f4ad4) = q5_f((long double)Q5_GF(DAT_007f4ad4) + g_dwRdAFRaster_vOverZStep);                            \
    DAT_007f4b58 = UINT_007f4b48;                                                                           \
    DAT_007f4b5c = UINT_007f4b4c;                                                                           \
    DAT_007f4b60 = UINT_007f4b50;

#define Q5_P16(NAME, LIT, TEXEL, PIXEL)                                                                     \
void NAME(int *s)                                                                                           \
{                                                                                                           \
    int tr = 1, n = s[1], r = s[0] & 15, rest, vraw, k;                                                     \
    char *cd;                                                                                               \
    q5_fldcw(&DAT_00900528);                                                                                \
    UINT_007f4b44 = r ? (n < 16 - r ? n : 16 - r) : 0;                                                      \
    rest = n - UINT_007f4b44;                                                                               \
    if (rest) {                                                                                             \
        UINT_007f4b2c = rest / 16;                                                                          \
        UINT_007f4acc = rest % 16;                                                                          \
        if (!UINT_007f4acc) {                                                                               \
            UINT_007f4b2c--;                                                                                \
            UINT_007f4acc = 16;                                                                             \
        }                                                                                                   \
    } else {                                                                                                \
        UINT_007f4b2c = 0;                                                                                  \
        UINT_007f4acc = 0;                                                                                  \
    }                                                                                                       \
    DAT_007f4af8 = s[7];                                                                                    \
    DAT_007f4ae4 = s[3];                                                                                    \
    DAT_007f4af0 = s[4];                                                                                    \
    if (LIT) {                                                                                              \
        UINT_007f4b30 = s[9];                                                                               \
        UINT_007f4b68 = s[8];                                                                               \
    }                                                                                                       \
    {                                                                                                       \
        long double w_ = 1.0f / (long double)Q5_GF(DAT_007f4af8);                                           \
        Q5_GF(DAT_007f4b60) = q5_f(w_);                                                                     \
        Q5_GF(DAT_007f4b58) = q5_f(w_ * Q5_GF(DAT_007f4ae4));                                               \
        Q5_GF(DAT_007f4b5c) = q5_f((long double)Q5_GF(DAT_007f4b60) * Q5_GF(DAT_007f4af0));                 \
    }                                                                                                       \
    cd = *(char **)(Q5_CANVAS() + 4);                                                                       \
    UINT_007f4b3c = Q5_I(cd, 0x5c) + (((unsigned)Q5_I(cd, 0x18) >> 1) * s[2] + s[0]) * 2;                   \
    if (UINT_007f4b44) {                                                                                    \
        Q5_GF(DAT_007f4af4) = q5_f((long double)UINT_007f4b44);                                             \
        Q5_GF(DAT_007f4b34) = q5_copy(g_dwRdRaster_aOneOverNFlex[UINT_007f4b44]);                                        \
        Q5_GF(DAT_007f4b38) = q5_f((long double)Q5_GF(DAT_007f4af4) * g_dwRdAFRaster_dOneOverZdX + Q5_GF(DAT_007f4af8));  \
        Q5_GF(DAT_007f4b64) = q5_f((long double)Q5_GF(DAT_007f4af4) * g_dwRdAFRaster_dUOverZdX + Q5_GF(DAT_007f4ae4));  \
        Q5_GF(DAT_007f4ad4) = q5_f((long double)Q5_GF(DAT_007f4af4) * g_dwRdAFRaster_dVOverZdX + Q5_GF(DAT_007f4af0));  \
        Q5_PW()                                                                                             \
        Q5_PUV(Q5_GF(DAT_007f4b34))                                                                         \
        Q5_PLAST(UINT_007f4b44, LIT)                                                                        \
        Q5_NPART(LIT, 0, TEXEL, PIXEL)                                                                      \
        Q5_PNEXT()                                                                                          \
    } else {                                                                                                \
        Q5_GF(DAT_007f4b38) = q5_f((long double)Q5_GF(DAT_007f4af8) + g_dwRdAFRaster_oneOverZStep);                        \
        Q5_GF(DAT_007f4b64) = q5_f((long double)Q5_GF(DAT_007f4ae4) + g_dwRdAFRaster_uOverZStep);                        \
        Q5_GF(DAT_007f4ad4) = q5_f((long double)Q5_GF(DAT_007f4af0) + g_dwRdAFRaster_vOverZStep);                        \
    }                                                                                                       \
    for (;;) {                                                                                              \
        k = UINT_007f4b2c--;                                                                                \
        if (k <= 0)                                                                                         \
            break;                                                                                          \
        Q5_PW()                                                                                             \
        Q5_PUV(0.0625f)                                                                                     \
        Q5_PLAST(16, LIT)                                                                                   \
        Q5_NPART(LIT, 0, TEXEL, PIXEL)                                                                      \
        Q5_PNEXT()                                                                                          \
    }                                                                                                       \
    if (UINT_007f4acc) {                                                                                    \
        k = --UINT_007f4acc;                                                                                \
        if (k) {                                                                                            \
            Q5_GF(DAT_007f4ac8) = q5_f((long double)k);                                                     \
            Q5_GF(DAT_007f4aec) = q5_copy(g_dwRdRaster_aOneOverNFlex[k]);                                                \
            Q5_GF(DAT_007f4b38) =                                                                           \
                q5_f(((long double)Q5_GF(DAT_007f4ac8) * g_dwRdAFRaster_dOneOverZdX - g_dwRdAFRaster_oneOverZStep) + Q5_GF(DAT_007f4b38));\
            Q5_GF(DAT_007f4b64) =                                                                           \
                q5_f(((long double)Q5_GF(DAT_007f4ac8) * g_dwRdAFRaster_dUOverZdX - g_dwRdAFRaster_uOverZStep) + Q5_GF(DAT_007f4b64));\
            Q5_GF(DAT_007f4ad4) =                                                                           \
                q5_f(((long double)Q5_GF(DAT_007f4ac8) * g_dwRdAFRaster_dVOverZdX - g_dwRdAFRaster_vOverZStep) + Q5_GF(DAT_007f4ad4));\
            Q5_PW()                                                                                         \
            Q5_PUV(Q5_GF(DAT_007f4aec))                                                                     \
            Q5_PLAST(k + 1, LIT)                                                                            \
        } else                                                                                              \
            UINT_008dde40 = 1;                                                                              \
        Q5_NPART(LIT, 0, TEXEL, PIXEL)                                                                      \
    }                                                                                                       \
    q5_fldcw(&DAT_00900524);                                                                                \
}
/* OVERRIDES: rdRaster_SpanP16_Tex */
Q5_P16(rdRaster_SpanP16_Tex, 0, Q5_NTG, Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_Tex_2 */
Q5_P16(rdRaster_SpanP16_Tex_2, 0, Q5_NT(13, 0x70000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_Tex_3 */
Q5_P16(rdRaster_SpanP16_Tex_3, 0, Q5_NT(12, 0xf0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_Tex_4 */
Q5_P16(rdRaster_SpanP16_Tex_4, 0, Q5_NT(11, 0x1f0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_TexLit */
Q5_P16(rdRaster_SpanP16_TexLit, 0, Q5_NT(10, 0x3f0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_Tex_5 */
Q5_P16(rdRaster_SpanP16_Tex_5, 0, Q5_NT(9, 0x7f0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_Tex_6 */
Q5_P16(rdRaster_SpanP16_Tex_6, 0, Q5_NT(8, 0xff0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_Tex_7 */
Q5_P16(rdRaster_SpanP16_Tex_7, 0, Q5_NTG, Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_Tex_8 */
Q5_P16(rdRaster_SpanP16_Tex_8, 0, Q5_NT(13, 0x70000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_Tex_9 */
Q5_P16(rdRaster_SpanP16_Tex_9, 0, Q5_NT(12, 0xf0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_Tex_10 */
Q5_P16(rdRaster_SpanP16_Tex_10, 0, Q5_NT(11, 0x1f0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_TexLit_2 */
Q5_P16(rdRaster_SpanP16_TexLit_2, 0, Q5_NT(10, 0x3f0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_Tex_11 */
Q5_P16(rdRaster_SpanP16_Tex_11, 0, Q5_NT(9, 0x7f0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_Tex_12 */
Q5_P16(rdRaster_SpanP16_Tex_12, 0, Q5_NT(8, 0xff0000), Q5_NPAL)
/* OVERRIDES: rdRaster_SpanP16_TexLit_3 */
Q5_P16(rdRaster_SpanP16_TexLit_3, 1, Q5_NTG, Q5_NPALL)
/* OVERRIDES: rdRaster_SpanP16_TexLit_4 */
Q5_P16(rdRaster_SpanP16_TexLit_4, 1, Q5_NT(13, 0x70000), Q5_NPALL)
/* OVERRIDES: rdRaster_SpanP16_TexLit_5 */
Q5_P16(rdRaster_SpanP16_TexLit_5, 1, Q5_NT(12, 0xf0000), Q5_NPALL)
/* OVERRIDES: rdRaster_SpanP16_TexLit_6 */
Q5_P16(rdRaster_SpanP16_TexLit_6, 1, Q5_NT(11, 0x1f0000), Q5_NPALL)
/* OVERRIDES: rdRaster_SpanP16_TexLit_7 */
Q5_P16(rdRaster_SpanP16_TexLit_7, 1, Q5_NT(10, 0x3f0000), Q5_NPALL)
/* OVERRIDES: rdRaster_SpanP16_TexLit_8 */
Q5_P16(rdRaster_SpanP16_TexLit_8, 1, Q5_NT(9, 0x7f0000), Q5_NPALL)
/* OVERRIDES: rdRaster_SpanP16_TexLit_9 */
Q5_P16(rdRaster_SpanP16_TexLit_9, 1, Q5_NT(8, 0xff0000), Q5_NPALL)

#endif /* GRIM_EXE */
