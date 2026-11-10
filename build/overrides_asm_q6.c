/* Readable C for the non-z-buffered half of the RDroid software rasteriser (agent q6; see docs/notes/asm_q6.md).
 *
 * Every function here replaces original 1.01 machine code (src/GRIMFANDANGO.EXE/asm_funcs.s as of 2df265d) and is
 * checked against it by the differential test in build/difftest/asm_q6/ (original bytes and this C on the same random
 * polygons, edges, spans and span lists, under the x87 precision controls 24, 53 and 64 bits; frame buffer, edge and
 * polygon records, rasteriser globals, call logs, x87 control word and stack compared).  None of these functions runs
 * in the game or in the clean-room tests (the display always has a z-buffer, docs/notes/asm_q4.md), so the file is
 * compiled the way build/link.py compiles every override file, at -O0, without q4's speed pragmas: at -O0 gcc emits
 * the statements in source order, which the perspective spans rely on (they switch the x87 control word, below).
 *
 * Two families:
 *   - the edge walker (0x00418fe0 - 0x0042d190, the siblings of build/overrides_asm_o1.c): Draw* drivers walk two edge
 *     records (Edge_Flat*) down a polygon and call a span function per scan line; the spans draw from the left edge
 *     to the right edge, affine (Span16_Tex) or perspective-correct in runs of 16 pixels (Span*_Tex*_n, below).
 *   - the span-list renderer (0x0040ea50 - 0x00418fe0, the siblings of build/overrides_asm_s1.c): a selector
 *     (Select_*) fills a polygon record with 1/z per vertex, the gradients (SetupPoly*) and the callbacks of an edge
 *     set-up (EdgeSetup_Flat*, which fills span nodes) and of a span list drawer, whose per-span functions
 *     (SpanR*, SpanP*) draw one node each.
 *
 * x87 conventions (as in build/overrides_asm_o1.c / q4):
 *   - `long double` holds a value the original keeps on the x87 stack; q6_f() is a store of it to a float slot (FSTP
 *     m32) through a volatile, so it is rounded at that point.
 *   - q6_floor_i / q6_ceil are the original's instruction sequences (`fldcw [round down]; fld m32; fistp m32;
 *     fldcw [default]` and `fldcw [round up]; fld m32; frndint; fstp m32; fldcw [default]`) in inline assembly, so they
 *     also leave the default control word loaded, as the original does.
 *   - A float the original copies with MOV is copied as a dword, so a NaN keeps its bits. */
#include "ghidra_types.h"

#ifdef GRIM_EXE

/* ---- globals (names as in globals.h; not included, the types here are the ones the code needs) ---- */
extern char *g_pRdCamera_CurCamera;     /* 0x007f0fc8; +4: the canvas (+4 colour buffer: +0x18 pitch, +0x24 bpp, +0x5c pixels) */
extern int g_nRdNRaster_numVertices;     /* 0x007f424c */
extern int g_dwRdNRaster_maxMipMap;            /* mip count - 1 (Grad_*: the mip mode) */
extern int g_nRdNRaster_yMinVert;   /* 0x007f42e8 top vertex */
extern int g_nRdNRaster_leftVertexStep;         /* 0x007f42ec left edge direction */
extern int g_nRdNRaster_yMaxVert;     /* 0x007f42fc bottom vertex */
extern float *g_pRdNRaster_aVertices;      /* 0x007f4308 screen vertices x, y, z (12 bytes each) */
extern int g_nRdNRaster_rightVertexStep;         /* 0x007f4394 right edge direction */
extern unsigned char *g_pDest;  /* 8 bpp destination / the texel of the 16 bpp blended spans */
extern float *g_dwRdNRaster_aIntensities;         /* per-vertex light */
extern float *g_dwRdNRaster_aTexVertices;         /* per-vertex u, v */
extern char *g_pWDest;           /* 16 bpp destination (advanced by the spans) */
extern unsigned char *g_dwRdNRaster_aAlphaMap; /* light / translucency table */
extern unsigned char *g_dwRdNRaster_aMonoMap; /* 8 bpp shade table */
extern unsigned short g_wRdNRaster_RGBcolor;  /* 16 bpp colour */
extern unsigned short *g_dwRdNRaster_aRGBMap;/* 16 bpp palette (64 rows of 256) */
extern unsigned char g_bRdNRaster_color;   /* colour / light level byte */
extern unsigned char *g_dwRdNRaster_aRGBToPalette; /* 16 bpp colour -> palette index */
extern char *g_dwRdColormap_pCurMap;          /* the colormap; +0x338: the translucency table */
extern int g_dwRdZRaster_numVertices;            /* the z-buffered rasteriser's vertex count (DrawWireframeZ) */
extern float *g_pRdZRaster_aVertices;         /* the z-buffered rasteriser's vertices (DrawWireframeZ) */
extern unsigned short g_wRdZRaster_RGBcolor;  /* 16 bpp colour (z-buffered half) */
extern unsigned char g_bRdZRaster_color;   /* 8 bpp colour (z-buffered half) */
extern unsigned short DAT_00900524, DAT_00900526, DAT_00900528, DAT_0090052a;  /* control words (stdStartup) */

#define Q6_I(p, off) (*(int *)((char *)(p) + (off)))
#define Q6_U8(p, off) (*(unsigned char *)((char *)(p) + (off)))
#define q6_u32(f) (*(int *)&(f))

/* the canvas of the current camera, its colour buffer and bits per pixel */
#define Q6_C4() (*(char **)(g_pRdCamera_CurCamera + 4))
#define Q6_CBUF() (*(char **)(Q6_C4() + 4))
#define Q6_BPP() Q6_I(Q6_CBUF(), 0x24)

static float q6_f(long double x)
{
    volatile float f = (float)x;
    return f;
}

/* fldcw [round down]; fld m32; fistp m32; fldcw [default] */
static int q6_floor_i(float x)
{
    int r;
    __asm__ volatile("fldcw %2\n\tflds %1\n\tfistpl %0\n\tfldcw %3"
                     : "=m"(r) : "m"(x), "m"(DAT_00900526), "m"(DAT_00900524) : "memory");
    return r;
}

/* fldcw [round up]; fld m32; frndint; fstp m32; fldcw [default] */
static float q6_ceil(float x)
{
    float r;
    __asm__ volatile("fldcw %2\n\tflds %1\n\tfrndint\n\tfstps %0\n\tfldcw %3"
                     : "=m"(r) : "m"(x), "m"(DAT_0090052a), "m"(DAT_00900524) : "memory");
    return r;
}

/* the FLD / FSTP copy of a float the original makes before rounding it (quiets a signalling NaN) */
static float q6_copy(float x)
{
    return q6_f((long double)x);
}

/* next vertex of an edge: i + dir, wrapping to 0 past the last vertex and to n - 1 below 0 */
static int q6_next(int i, int dir, int count)
{
    int n = i + dir;
    if (n < 0)
        return count - 1;
    return n > count - 1 ? 0 : n;
}

/* ========================================================================================================
 * The edge walker: points, wireframe, and the flat / affine drivers of the non-z-buffered display.
 * ======================================================================================================== */

/* ==== DrawPoints: one pixel per vertex (floor of x, y), the material's colour ====
 * 8 bpp: the colour byte of the material (+4); 16 bpp: row 63 of the 16 bpp palette at that index. */
/* OVERRIDES: rdNRaster_DrawNGonLV */
void rdNRaster_DrawNGonLV(int p, int mat)
{
    int bpp = Q6_BPP(), i, x, y;
    g_pRdNRaster_aVertices = *(float **)(p + 0x20);
    g_nRdNRaster_numVertices = Q6_I(p, 0x1c);
    if (bpp == 8) {
        g_bRdNRaster_color = Q6_U8(mat, 4);
        for (i = 0; i < g_nRdNRaster_numVertices; i++) {
            y = q6_floor_i(q6_copy(g_pRdNRaster_aVertices[i * 3 + 1]));
            x = q6_floor_i(q6_copy(g_pRdNRaster_aVertices[i * 3]));
            *(unsigned char *)(Q6_I(Q6_CBUF(), 0x18) * y + Q6_I(Q6_CBUF(), 0x5c) + x) = g_bRdNRaster_color;
        }
    } else if (bpp == 16) {
        g_wRdNRaster_RGBcolor = (*(unsigned short **)(*(char **)(p + 0x4c) + 0x348))[Q6_U8(mat, 4) + 0x3f00];
        for (i = 0; i < g_nRdNRaster_numVertices; i++) {
            y = q6_floor_i(q6_copy(g_pRdNRaster_aVertices[i * 3 + 1]));
            x = q6_floor_i(q6_copy(g_pRdNRaster_aVertices[i * 3]));
            ((unsigned short *)Q6_I(Q6_CBUF(), 0x5c))[((unsigned)Q6_I(Q6_CBUF(), 0x18) >> 1) * y + x] = g_wRdNRaster_RGBcolor;
        }
    }
}

/* ==== DrawWireframe, DrawWireframeZ: the polygon's outline with rdCanvas_DrawLine ====
 * A line from each vertex to the next and one from the last (vertex max(count - 1, 0)) back to vertex 0, with the
 * vertex coordinates rounded down (copied as dwords before the conversion); colour as DrawPoints, pattern -1.  Nothing
 * for another colour depth.  The Z variant keeps its state in the z-buffered rasteriser's globals. */
extern void rdCanvas_DrawLine(void *canvas, int x0, int y0, int x1, int y1, unsigned short color, unsigned pattern);

static void q6_wireframe(float *v, int count, unsigned colour)
{
    int i = 0;
    float f;
    for (; i < count - 1; i++) {
        int y1, x1, y0, x0;
        q6_u32(f) = q6_u32(v[i * 3 + 4]);
        y1 = q6_floor_i(f);
        q6_u32(f) = q6_u32(v[i * 3 + 3]);
        x1 = q6_floor_i(f);
        q6_u32(f) = q6_u32(v[i * 3 + 1]);
        y0 = q6_floor_i(f);
        q6_u32(f) = q6_u32(v[i * 3]);
        x0 = q6_floor_i(f);
        rdCanvas_DrawLine(Q6_C4(), x0, y0, x1, y1, (unsigned short)colour, 0xffffffff);
    }
    {
        int y1, x1, y0, x0;
        q6_u32(f) = q6_u32(v[1]);
        y1 = q6_floor_i(f);
        q6_u32(f) = q6_u32(v[0]);
        x1 = q6_floor_i(f);
        q6_u32(f) = q6_u32(v[i * 3 + 1]);
        y0 = q6_floor_i(f);
        q6_u32(f) = q6_u32(v[i * 3]);
        x0 = q6_floor_i(f);
        rdCanvas_DrawLine(Q6_C4(), x0, y0, x1, y1, (unsigned short)colour, 0xffffffff);
    }
}

/* OVERRIDES: rdNRaster_DrawNGonLW */
void rdNRaster_DrawNGonLW(int p, int mat)
{
    int bpp = Q6_BPP();
    g_pRdNRaster_aVertices = *(float **)(p + 0x20);
    g_nRdNRaster_numVertices = Q6_I(p, 0x1c);
    if (bpp == 8) {
        g_bRdNRaster_color = Q6_U8(mat, 4);
        q6_wireframe(g_pRdNRaster_aVertices, g_nRdNRaster_numVertices, g_bRdNRaster_color);
    } else if (bpp == 16) {
        g_wRdNRaster_RGBcolor = (*(unsigned short **)(*(char **)(p + 0x4c) + 0x348))[Q6_U8(mat, 4) + 0x3f00];
        q6_wireframe(g_pRdNRaster_aVertices, g_nRdNRaster_numVertices, g_wRdNRaster_RGBcolor);
    }
}

/* OVERRIDES: rdZRaster_DrawNGonLW */
void rdZRaster_DrawNGonLW(int p, int mat)
{
    int bpp = Q6_BPP();
    g_pRdZRaster_aVertices = *(float **)(p + 0x20);
    g_dwRdZRaster_numVertices = Q6_I(p, 0x1c);
    if (bpp == 8) {
        g_bRdZRaster_color = Q6_U8(mat, 4);
        q6_wireframe(g_pRdZRaster_aVertices, g_dwRdZRaster_numVertices, g_bRdZRaster_color);
    } else if (bpp == 16) {
        g_wRdZRaster_RGBcolor = (*(unsigned short **)(*(char **)(p + 0x4c) + 0x348))[Q6_U8(mat, 4) + 0x3f00];
        q6_wireframe(g_pRdZRaster_aVertices, g_dwRdZRaster_numVertices, g_wRdZRaster_RGBcolor);
    }
}

/* ==== Edge_Flat, _2, _3: the edge set-up of the flat drivers (x only; the template of build/overrides_asm_o1.c's
 * rd_edge with EDGE_DIV) ====
 * Edge record (0x44 bytes): +0 x, +4 dx (16.16), +8 h (scan lines left), +0xc vertex, +0x40 y.  Returns 1 when the
 * edge reached the end vertex, else 0 with the record set up for the next vertex pair that covers at least one scan
 * line: y = floor(ceil(vertex y)), h = floor(ceil(next y)) - y; one line: x = floor(float(x * 65536)); more:
 * d = (x1 - x0) / (y1 - y0) extended, dx = floor(float(d * 65536)), x = floor(float((float(d) * dy + x0) * 65536)) with
 * dy = float(ceil(y0) - y0).  dir: the direction global (Edge_Flat / _3 the left edge, _2 the right one). */
static int q6_edge_x(int *e, int dir)
{
    int cur = e[3], next, n;
    float yc, dy, s;
    float *v;
    long double d;
    if (cur == g_nRdNRaster_yMaxVert)
        return 1;
    for (;;) {
        next = q6_next(cur, dir, g_nRdNRaster_numVertices);
        yc = q6_ceil(q6_copy(g_pRdNRaster_aVertices[cur * 3 + 1]));
        e[0x10] = q6_floor_i(q6_copy(yc));
        n = q6_floor_i(q6_copy(q6_ceil(q6_copy(g_pRdNRaster_aVertices[next * 3 + 1])))) - e[0x10];
        e[2] = n;
        if (n > 0)
            break;
        cur = next;
        if (next == g_nRdNRaster_yMaxVert)
            return 1;
    }
    v = g_pRdNRaster_aVertices;
    if (n < 2) {
        e[0] = q6_floor_i(q6_f(v[cur * 3] * 65536.0L));
        e[3] = next;
        return 0;
    }
    dy = q6_f((long double)yc - v[cur * 3 + 1]);
    d = ((long double)v[next * 3] - v[cur * 3]) / ((long double)v[next * 3 + 1] - v[cur * 3 + 1]);
    s = q6_f(d);
    e[1] = q6_floor_i(q6_f(d * 65536.0L));
    e[0] = q6_floor_i(q6_f(((long double)s * dy + v[cur * 3]) * 65536.0L));
    e[3] = next;
    return 0;
}

/* OVERRIDES: rdNRaster_SetupLeftEdgeNGonLS */
int rdNRaster_SetupLeftEdgeNGonLS(int *e)
{
    return q6_edge_x(e, g_nRdNRaster_leftVertexStep);
}
/* OVERRIDES: rdNRaster_SetupRightEdgeNGonLS */
int rdNRaster_SetupRightEdgeNGonLS(int *e)
{
    return q6_edge_x(e, g_nRdNRaster_rightVertexStep);
}
/* OVERRIDES: rdNRaster_SetupLeftEdgeNGonFS */
int rdNRaster_SetupLeftEdgeNGonFS(int *e)
{
    return q6_edge_x(e, g_nRdNRaster_leftVertexStep);
}

/* ==== the flat drivers (Draw16_FlatLit, Draw16_TexLit, Draw16_FlatLit_2) ====
 * Walk a left (A) and a right (B) edge from the top vertex: per scan line one span (8 or 16 bpp; nothing for another
 * depth), then each edge is set up for its next vertex pair when its line count runs out, else stepped (x += dx,
 * y++).  The polygon record: +0x1c vertex count, +0x20 vertices, +0x4c tables (+0x330 8 bpp shade, +0x348 16 bpp
 * palette, +0x34c 16 bpp -> index), +0x50 winding, +0x6c top, +0x70 bottom. */
typedef int (*q6_edge_fn)(int *);
typedef void (*q6_span_fn)(void *, void *);
extern void rdRaster_Span_Flat(void *, void *), rdNRaster_DrawScanLineNGonLS_16(void *, void *), rdNRaster_DrawScanLineNGonFS_16(void *, void *);
extern void rdRaster_Span_Tex(void *, void *);
extern int rdNRaster_SetupRightEdgeNGonFS(int *);

static void q6_poly_globals(int p)
{
    g_pRdNRaster_aVertices = *(float **)(p + 0x20);
    g_nRdNRaster_numVertices = Q6_I(p, 0x1c);
    g_nRdNRaster_yMinVert = Q6_I(p, 0x6c);
    g_nRdNRaster_yMaxVert = Q6_I(p, 0x70);
    if (Q6_I(p, 0x50)) {
        g_nRdNRaster_leftVertexStep = -1;
        g_nRdNRaster_rightVertexStep = 1;
    } else {
        g_nRdNRaster_leftVertexStep = 1;
        g_nRdNRaster_rightVertexStep = -1;
    }
}

static void q6_walk_x(int bpp, q6_edge_fn ea, q6_edge_fn eb, q6_span_fn s8, q6_span_fn s16)
{
    int a[0x11], b[0x11];
    a[3] = g_nRdNRaster_yMinVert;
    if (ea(a))
        return;
    b[3] = g_nRdNRaster_yMinVert;
    if (eb(b))
        return;
    for (;;) {
        if (bpp == 8)
            s8(a, b);
        else if (bpp == 16)
            s16(a, b);
        if (--a[2] == 0) {
            if (ea(a))
                return;
        } else {
            a[0] += a[1];
            a[0x10]++;
        }
        if (--b[2] == 0) {
            if (eb(b))
                return;
        } else {
            b[0] += b[1];
            b[0x10]++;
        }
    }
}

/* ==== Draw16_FlatLit: flat colour (8 bpp: the material's index; 16 bpp: palette row 63) ==== */
/* OVERRIDES: rdNRaster_DrawNGonLS */
void rdNRaster_DrawNGonLS(int p, int mat)
{
    int bpp = Q6_BPP();
    if (bpp == 8)
        g_bRdNRaster_color = Q6_U8(mat, 4);
    else if (bpp == 16)
        g_wRdNRaster_RGBcolor = (*(unsigned short **)(*(char **)(p + 0x4c) + 0x348))[Q6_U8(mat, 4) + 0x3f00];
    q6_poly_globals(p);
    q6_walk_x(bpp, rdNRaster_SetupLeftEdgeNGonLS, rdNRaster_SetupRightEdgeNGonLS, rdRaster_Span_Flat, rdNRaster_DrawScanLineNGonLS_16);
}

/* ==== Draw16_TexLit: translucent flat colour (the spans remap the frame buffer through the light table) ====
 * 16 bpp: palette row 63, the colour at the material's (dword) index, its palette index as the level. */
extern void rdNRaster_DrawScanLineNGonTLS_16(void *, void *);
/* OVERRIDES: rdNRaster_DrawNGonTLS */
void rdNRaster_DrawNGonTLS(int p, int mat)
{
    int bpp = Q6_BPP();
    if (bpp == 8)
        g_bRdNRaster_color = Q6_U8(mat, 4);
    else if (bpp == 16) {
        g_dwRdNRaster_aRGBMap = (unsigned short *)(*(char **)(*(char **)(p + 0x4c) + 0x348) + 0x7e00);
        g_wRdNRaster_RGBcolor = (*(unsigned short **)(*(char **)(p + 0x4c) + 0x348))[Q6_I(mat, 4) + 0x3f00];
        g_dwRdNRaster_aRGBToPalette = *(unsigned char **)(*(char **)(p + 0x4c) + 0x34c);
        g_bRdNRaster_color = g_dwRdNRaster_aRGBToPalette[g_wRdNRaster_RGBcolor];
    }
    q6_poly_globals(p);
    g_dwRdNRaster_aAlphaMap = *(unsigned char **)(g_dwRdColormap_pCurMap + 0x338);
    q6_walk_x(bpp, rdNRaster_SetupLeftEdgeNGonLS, rdNRaster_SetupRightEdgeNGonLS, rdRaster_Span_Tex, rdNRaster_DrawScanLineNGonTLS_16);
}

/* ==== Draw16_FlatLit_2: flat colour at the light level floor(light) ==== */
/* OVERRIDES: rdNRaster_DrawNGonFS */
void rdNRaster_DrawNGonFS(int p, int mat, float light)
{
    int bpp = Q6_BPP();
    if (bpp == 8)
        g_bRdNRaster_color = (*(unsigned char **)(*(char **)(p + 0x4c) + 0x330))[Q6_I(mat, 4) + q6_floor_i(light) * 256];
    else if (bpp == 16)
        g_wRdNRaster_RGBcolor = (*(unsigned short **)(*(char **)(p + 0x4c) + 0x348))[Q6_I(mat, 4) + q6_floor_i(light) * 256];
    q6_poly_globals(p);
    q6_walk_x(bpp, rdNRaster_SetupLeftEdgeNGonFS, rdNRaster_SetupRightEdgeNGonFS, rdRaster_Span_Flat, rdNRaster_DrawScanLineNGonFS_16);
}

/* ==== Span16_Tex: 16 bpp translucent flat span ====
 * Pixels ceil(L.x) .. ceil(R.x) - 1 (16.16, unsigned >> 16) of row L.y: the colour is the palette entry of
 * light[level * 256 + index[*g_pDest]] (the 8 bpp destination pointer is read, not advanced: the original's
 * stale pointer); the 16 bpp destination is the global g_pWDest, left after the span. */
/* OVERRIDES: rdNRaster_DrawScanLineNGonTLS_16 */
void rdNRaster_DrawScanLineNGonTLS_16(void *pl, void *pr)
{
    unsigned *L = pl, *R = pr, xl = L[0], xr = R[0];
    int n;
    if (xl & 0xffff)
        xl = (xl + 0x10000) & 0xffff0000;
    if (xr & 0xffff)
        xr = (xr + 0x10000) & 0xffff0000;
    xl >>= 16;
    n = (int)((xr >> 16) - xl);
    if (n <= 0)
        return;
    g_pWDest = Q6_I(Q6_CBUF(), 0x5c) + (L[0x10] * ((unsigned)Q6_I(Q6_CBUF(), 0x18) >> 1) + xl) * 2;
    do {
        *(unsigned short *)g_pWDest =
            g_dwRdNRaster_aRGBMap[g_dwRdNRaster_aAlphaMap[g_bRdNRaster_color * 256 + g_dwRdNRaster_aRGBToPalette[*g_pDest]]];
        g_pWDest += 2;
    } while (--n);
}

/* ==== Grad_Flat, Grad_Flat_2: texture gradient set-up of the affine / perspective edge-walker drivers ====
 * Pick three vertices a, b, c: for a triangle 0, 1, 2; otherwise a = top, b = bottom and c the vertex farthest in x
 * from the midpoint float((xa + xb) * 0.5) (|x - mid| > the largest so far, strictly; NaN is not), searched from the
 * top in direction dir up to the bottom.  dir: when the vertex after the top (+1) is the bottom, -1 and when the one
 * before it (-1) is the bottom, +1, and c starts as Grad_Flat's argument's bits (an index the original would use if no
 * vertex beats 0; Grad_Flat_2 starts it from an uninitialised stack slot instead, see q6_grad_pick); otherwise c starts
 * as the vertex after the top and dir is -1 unless |_ftol(xc - xb)| > 1 or |_ftol(xc - xa)| > 1 (32-bit abs, compared as
 * a float), in which case it is +1 when c is at least 1 away in y from the line a -> b (d = yc - ((yb - ya) / (xb - xa)
 * * (xc - xa) + ya), negated unless d >= 0, then d >= 1), else -1. */
extern int g_dwRdNRaster_mipMapNum;            /* mip level */
extern int g_dwRdNRaster_dUdXModifier, g_dwRdNRaster_dVdXModifier; /* u / v rounding bias (0x8000 / 0x7fff) */
extern float g_dwRdNRaster_dOneOverZdX, g_dwRdNRaster_dOneOverZdY, g_dwRdNRaster_dUOverZdX, g_dwRdNRaster_dUOverZdY, g_dwRdNRaster_dVOverZdX, g_dwRdNRaster_dVOverZdY;  /* plane gradients */
extern float g_dwRdNRaster_aOneOverZ[], g_dwRdNRaster_aUOverZ[], g_dwRdNRaster_aVOverZ[];  /* per vertex 1/z, u/z, v/z (Grad_Flat_2) */
extern float DAT_004dda90, g_aRdroid_MipDistances, DAT_004dda98;  /* mip distance thresholds (10, 20, 40) */

/* _ftol: truncation of the x87 value to a 64-bit integer, low dword */
static int q6_ftol(long double x)
{
    return (int)(long long)x;
}

/* |_ftol(x)| > 1: the 32-bit absolute value (neg of 0x80000000 stays negative) loaded as an integer, compared as "greater" */
static int q6_far(long double x)
{
    int i = q6_ftol(x);
    if (i < 0)
        i = -(unsigned)i;
    return (long double)i > 1.0L;
}

static void q6_pick(float *V, int cnt, int start, int end, int cbits, int *pa, int *pb, int *pc)
{
    int c, dir, k;
    float mid, mx;
    if (cnt == 3) {
        *pa = 0;
        *pb = 1;
        *pc = 2;
        return;
    }
    if (q6_next(start, 1, cnt) == end) {
        c = cbits;
        dir = -1;
    } else if (q6_next(start, -1, cnt) == end) {
        c = cbits;
        dir = 1;
    } else {
        c = q6_next(start, 1, cnt);
        dir = -1;
        if (q6_far((long double)V[c * 3] - V[end * 3]) || q6_far((long double)V[c * 3] - V[start * 3])) {
            long double r, d;
            r = ((long double)V[end * 3 + 1] - V[start * 3 + 1]) / ((long double)V[end * 3] - V[start * 3]);
            d = V[c * 3 + 1] - (r * ((long double)V[c * 3] - V[start * 3]) + V[start * 3 + 1]);
            if (!(d >= 0.0L))
                d = -d;
            dir = d >= 1.0L ? 1 : -1;
        }
    }
    mx = 0.0f;
    mid = q6_f(((long double)V[start * 3] + V[end * 3]) * 0.5f);
    for (k = q6_next(start, dir, cnt); k != end; k = q6_next(k, dir, cnt)) {
        long double d = (long double)V[k * 3] - mid;
        if (!(d >= 0.0L))
            d = -d;
        if (d > mx) {
            mx = q6_f(d);
            c = k;
        }
    }
    *pa = start;
    *pb = end;
    *pc = c;
}

/* the edge walker's pick: the rasteriser globals */
static void q6_grad_pick(int cbits, int *pa, int *pb, int *pc)
{
    q6_pick(g_pRdNRaster_aVertices, g_nRdNRaster_numVertices, g_nRdNRaster_yMinVert, g_nRdNRaster_yMaxVert, cbits, pa, pb, pc);
}

/* the mip level from the distance and the mode g_dwRdNRaster_maxMipMap (mip count - 1): 0 -> 0; 1 -> 1 if d > 20; 2 -> 0 / 1 / 2
 * by d > 10, d > 20; 3 -> 0..3 by d > 10, 20, 40 (a NaN compares "not greater"); another mode leaves it as it was */
static void q6_mip_level(float dist, int mode, int *level)
{
    switch (mode) {
    case 0:
        *level = 0;
        break;
    case 1:
        *level = dist > g_aRdroid_MipDistances ? 1 : 0;
        break;
    case 2:
        *level = !(dist > DAT_004dda90) ? 0 : !(dist > g_aRdroid_MipDistances) ? 1 : 2;
        break;
    case 3:
        *level = !(dist > DAT_004dda90) ? 0 : !(dist > g_aRdroid_MipDistances) ? 1 : !(dist > DAT_004dda98) ? 2 : 3;
        break;
    }
}

static void q6_mip(float dist)
{
    q6_mip_level(dist, g_dwRdNRaster_maxMipMap, &g_dwRdNRaster_mipMapNum);
}

/* Grad_Flat: the u / v rounding biases from the signs of the plane gradients through a, b, c (only their signs are
 * used: 0x8000 for a positive x gradient, 0x7fff for a negative or NaN one, for 0 by the y gradient: 0x7fff when it
 * is negative or NaN).  x87 as Grad_Flat_3 (build/overrides_asm_q4.c): A = xa - xc, B = xb - xc, C = ya - yc,
 * D = yb - yc extended, A and B also as floats; R = 1 / (C * float(B) - D * float(A)); E, F (u) extended and as
 * floats, G, H (v) as floats; du/dx = float((E * C - F * D) * float(R)) with E, F extended, the other three use the
 * floats and float(-R). */
/* the affine gradient signs through a, b, c (vertices V, texture coordinates T) -> the u / v rounding biases */
static void q6_affine_bias(float *V, float *T, int a, int b, int c, int *ubias, int *vbias)
{
    float *va = V + a * 3, *vb = V + b * 3, *vc = V + c * 3, *ta = T + a * 2, *tb = T + b * 2, *tc = T + c * 2;
    long double A, B, C, D, R, E, F, G, H;
    float fA, fB, fR, fnR, fE, fF, fG, fH, dudx, dudy, dvdx, dvdy;
    A = (long double)va[0] - vc[0];
    B = (long double)vb[0] - vc[0];
    C = (long double)va[1] - vc[1];
    D = (long double)vb[1] - vc[1];
    fA = q6_f(A);
    fB = q6_f(B);
    R = 1.0L / (C * fB - D * fA);
    fR = q6_f(R);
    fnR = q6_f(-R);
    E = (long double)tb[0] - tc[0];
    F = (long double)ta[0] - tc[0];
    fE = q6_f(E);
    fF = q6_f(F);
    G = (long double)tb[1] - tc[1];
    H = (long double)ta[1] - tc[1];
    fG = q6_f(G);
    fH = q6_f(H);
    dudx = q6_f((E * C - F * D) * fR);
    dudy = q6_f(((long double)fE * fA - (long double)fF * fB) * fnR);
    dvdx = q6_f(((long double)fG * C - (long double)fH * D) * fR);
    dvdy = q6_f(((long double)fG * fA - (long double)fH * fB) * fnR);
    if (dudx > 0.0f)
        *ubias = 0x8000;
    else if (!(dudx >= 0.0f) || !(dudy >= 0.0f))
        *ubias = 0x7fff;
    else
        *ubias = 0x8000;
    if (dvdx > 0.0f)
        *vbias = 0x8000;
    else if (!(dvdx >= 0.0f) || !(dvdy >= 0.0f))
        *vbias = 0x7fff;
    else
        *vbias = 0x8000;
}

/* OVERRIDES: rdNRaster_CalcAffineGradients */
void rdNRaster_CalcAffineGradients(int dbits)
{
    int a, b, c;
    q6_grad_pick(dbits, &a, &b, &c);
    q6_affine_bias(g_pRdNRaster_aVertices, g_dwRdNRaster_aTexVertices, a, b, c, &g_dwRdNRaster_dUdXModifier, &g_dwRdNRaster_dVdXModifier);
    q6_mip(*(float *)&dbits);
}

/* Grad_Flat_2: perspective.  Per vertex W = 1 / z (float, 0x007f43c8), U = float(u * W extended) (0x007f4260),
 * V = float(v * float(W)) (0x007f4310); then the screen gradients of the three planes through a, b, c:
 * dYa = ya - yc, dYb = yb - yc (extended and as floats), dXa = xa - xc, dXb = xb - xc (floats),
 * R = float(1 / (dYa * dXb - dYb * dXa)) with the extended dY, nR = -R; per plane P (dPb = Pb - Pc, dPa = Pa - Pc as
 * floats; for W dPb stays extended): d/dx = float((dPb * dYa - dPa * dYb) * R) (0x008ddef4, 0x008ddec8, 0x008ddedc),
 * d/dy = float((dPb * dXa - dPa * dXb) * nR) (0x008ddef0, 0x008ddec4, 0x008ddee0).  The rounding biases from the
 * signs of Wa * dU/dx - Ua * dW/dx (u; for 0 Wa * dU/dy - Ua * dW/dy) and Wa * dV/dx - Va * dW/dx (v), extended:
 * 0x8000 when positive, 0x7fff when negative or NaN, for 0 by the y term as Grad_Flat.
 * When the vertex next to the top is the bottom (and the polygon is not a triangle), c starts from a stack slot the
 * original never writes (garbage of the caller's frame) and stays so unless a vertex's x differs from the midpoint;
 * the C starts it at 0. */
/* OVERRIDES: rdNRaster_CalcPerspGradients */
void rdNRaster_CalcPerspGradients(int dbits)
{
    float dist = *(float *)&dbits;
    int a, b, c, i;
    float *va, *vb, *vc;
    float *W = g_dwRdNRaster_aOneOverZ, *U = g_dwRdNRaster_aUOverZ, *V = g_dwRdNRaster_aVOverZ;
    long double R, dWb, w;
    float fdYa, fdYb, fdXa, fdXb, fR, fnR, fdWa, fdUb, fdUa, fdVb, fdVa;
    q6_grad_pick(0, &a, &b, &c);
    for (i = 0; i < g_nRdNRaster_numVertices; i++) {
        w = 1.0L / g_pRdNRaster_aVertices[i * 3 + 2];
        W[i] = q6_f(w);
        U[i] = q6_f(g_dwRdNRaster_aTexVertices[i * 2] * w);
        V[i] = q6_f((long double)g_dwRdNRaster_aTexVertices[i * 2 + 1] * W[i]);
    }
    va = g_pRdNRaster_aVertices + a * 3;
    vb = g_pRdNRaster_aVertices + b * 3;
    vc = g_pRdNRaster_aVertices + c * 3;
    fdYa = q6_f((long double)va[1] - vc[1]);
    fdYb = q6_f((long double)vb[1] - vc[1]);
    fdXa = q6_f((long double)va[0] - vc[0]);
    fdXb = q6_f((long double)vb[0] - vc[0]);
    R = 1.0L / (((long double)va[1] - vc[1]) * fdXb - ((long double)vb[1] - vc[1]) * fdXa);
    dWb = (long double)W[b] - W[c];
    fdWa = q6_f((long double)W[a] - W[c]);
    fdUb = q6_f((long double)U[b] - U[c]);
    fdUa = q6_f((long double)U[a] - U[c]);
    fdVb = q6_f((long double)V[b] - V[c]);
    fdVa = q6_f((long double)V[a] - V[c]);
    fR = q6_f(R);
    fnR = q6_f(-(long double)fR);
    g_dwRdNRaster_dOneOverZdX = q6_f((dWb * fdYa - (long double)fdWa * fdYb) * fR);
    g_dwRdNRaster_dOneOverZdY = q6_f((dWb * fdXa - (long double)fdWa * fdXb) * fnR);
    g_dwRdNRaster_dUOverZdX = q6_f(((long double)fdUb * fdYa - (long double)fdUa * fdYb) * fR);
    g_dwRdNRaster_dUOverZdY = q6_f(((long double)fdUb * fdXa - (long double)fdUa * fdXb) * fnR);
    g_dwRdNRaster_dVOverZdX = q6_f(((long double)fdVb * fdYa - (long double)fdVa * fdYb) * fR);
    g_dwRdNRaster_dVOverZdY = q6_f(((long double)fdVb * fdXa - (long double)fdVa * fdXb) * fnR);
    q6_mip(dist);
    {
        long double t = (long double)W[a] * g_dwRdNRaster_dUOverZdX - (long double)U[a] * g_dwRdNRaster_dOneOverZdX;
        if (t > 0.0L)
            g_dwRdNRaster_dUdXModifier = 0x8000;
        else if (!(t >= 0.0L) || !((long double)W[a] * g_dwRdNRaster_dUOverZdY - (long double)U[a] * g_dwRdNRaster_dOneOverZdY >= 0.0L))
            g_dwRdNRaster_dUdXModifier = 0x7fff;
        else
            g_dwRdNRaster_dUdXModifier = 0x8000;
        t = (long double)W[a] * g_dwRdNRaster_dVOverZdX - (long double)V[a] * g_dwRdNRaster_dOneOverZdX;
        if (t > 0.0L)
            g_dwRdNRaster_dVdXModifier = 0x8000;
        else if (!(t >= 0.0L) || !((long double)W[a] * g_dwRdNRaster_dVOverZdY - (long double)V[a] * g_dwRdNRaster_dOneOverZdY >= 0.0L))
            g_dwRdNRaster_dVdXModifier = 0x7fff;
        else
            g_dwRdNRaster_dVdXModifier = 0x8000;
    }
}

/* ========================================================================================================
 * The perspective-correct spans of the edge walker (Span16_Tex_10 .. 15, Span_Tex_6 .. 8, Span*_TexKey_3 .. 11,
 * Span_FlatKey_2).  The edges carry three plane values per scan line (e[4] 1/z, e[6] u/z, e[8] v/z, floats; their
 * per-pixel gradients g_dwRdNRaster_dOneOverZdX / ec8 / edc and their 16-pixel steps g_dwRdNRaster_oneOverZStep / ed0 / f00 are set by the
 * drivers after Grad_Flat_2).  The span is drawn in runs: a head of 16 - (xl % 16) pixels (C remainder, so 17 .. 31
 * for a negative xl; at most n), runs of 16, and a tail (rest % 16, or 16); for each run u and v are computed exactly
 * at its two ends (u = U / W, v = V / W) and stepped linearly in 16.16 inside it.
 *
 * x87 control word: the original loads DAT_00900528 (truncate, 24-bit precision) after the empty-span test, so all
 * the arithmetic up to the first float -> int conversion runs in that mode; that conversion (fldcw floor ... fldcw
 * default, q6_floor_i) leaves the default word loaded, and everything after it runs at the default precision; the
 * end loads the default word again.  The C does the same: q6_fldcw at the same two points, the conversions with the
 * original's instruction sequence, at -O0 (statement order kept), with every value the original keeps on the x87
 * stack in a long double and every FSTP m32 a volatile float store.  Which arithmetic runs in the 24-bit mode
 * therefore depends on the path, as in the original: with a head, its set-up; without, the 16-pixel steps of the start
 * values and the first run's (or the tail's) divisions.
 *
 * Variants (the template's parameters):
 *   kind 10 (Span16_Tex_10, Span_Tex_6, Span16_Tex_11, Span_FlatKey_2, Span16_TexKey_6, Span_TexKey_5, Span16_TexKey_7:
 *        the unlit drivers): the tail step divides by float(t);
 *   kind 12 (Span16_Tex_12, Span_Tex_7, Span16_Tex_13, Span8_TexKey_3, Span16_TexKey_8, Span_TexKey_6,
 *        Span16_TexKey_9: the drivers at a light level): the tail step multiplies by the 1/n table (0x008fe000);
 *   kind 15 (Span_Tex_8, Span16_Tex_15, Span8_TexKey_4, Span16_TexKey_10, Span_TexKey_7, Span16_TexKey_11: gouraud):
 *        as 12, the third plane value rounded to a float at the start, and a light value l (16.16, stepped by
 *        (R.l - L.l) * (65536/n) >> 16, 0 when in -1309 .. -1, starting at frac * dl >> 16 + L.l; row (l >> 8) & 0x3f00).
 *   8 / 16 bpp: 8 bpp writes through a local pointer, 16 bpp through g_pWDest (left after the span).
 *   KEY: texel 0 is not drawn.  The pixel (q6_ppix): see the enum.
 * A span that starts on a multiple of 16 has no head; when it is then a single pixel (no run, tail 1), the original
 * draws it with u and v registers it never set in that path: they hold the bits of the first plane value after its
 * 16-pixel step (or, in the 8 bpp gouraud spans, the light value), and the C uses the same bits. */
extern unsigned char *g_dwRdNRaster_pPixels;  /* texels of the mip level */
extern int g_dwRdNRaster_texRowShift;             /* log2 width of the mip level */
extern int g_dwRdNRaster_uWrap;             /* u mask << 16 */
extern int g_dwRdNRaster_vWrap;             /* v mask << log2 width */
extern float g_dwRdNRaster_oneOverZStep, g_dwRdNRaster_uOverZStep, g_dwRdNRaster_vOverZStep;  /* the plane gradients times 16 */
extern int g_aRdRaster_OneOverNFixed[];            /* 65536 / n */
extern float g_dwRdRaster_aOneOverNFlex[];         /* 1.0f / n */

static void q6_fldcw(unsigned short *cw)
{
    __asm__ volatile("fldcw %0" : : "m"(*cw) : "memory");
}

/* imul; shrd EAX,EDX,0x10: bits 16..47 of the 64-bit product */
static int q6_mul16(int a, int b)
{
    return (int)((long long)a * b >> 16);
}

/* the pixel of the perspective spans: tx the texel, lrow the light row (0 without light), d the destination */
enum {
    Q6P_TEX,          /* 8 bpp: tx */
    Q6P_PAL,          /* 16 bpp: palette[lrow + tx] */
    Q6P_SHADE,        /* 8 bpp: shade[lrow + tx] */
    Q6P_BLEND8,       /* 8 bpp: blend[tx * 256 + d] */
    Q6P_SHADE_BLEND,  /* 8 bpp: blend[shade[lrow + tx] * 256 + d] */
    Q6P_BLEND_SHADE,  /* 8 bpp: shade[lrow + blend[tx * 256 + d]] */
    Q6P_BLEND16,      /* 16 bpp: palette[lrow + blend[tx * 256 + index[*g_pDest]]] (the stale 8 bpp pointer) */
    Q6P_ODD16         /* 16 bpp: palette[blend[index[palette[lrow + tx] << 8] + index[*g_pDest]]]: the original
                       * indexes the 16 bpp -> index table with the colour times 256 (far past the table) */
};

static int q6_ppix(int mode, unsigned tx, int lrow, unsigned d)
{
    switch (mode) {
    case Q6P_TEX:
        return tx;
    case Q6P_PAL:
        return g_dwRdNRaster_aRGBMap[lrow + tx];
    case Q6P_SHADE:
        return g_dwRdNRaster_aMonoMap[lrow + tx];
    case Q6P_BLEND8:
        return g_dwRdNRaster_aAlphaMap[tx * 256 + d];
    case Q6P_SHADE_BLEND:
        return g_dwRdNRaster_aAlphaMap[g_dwRdNRaster_aMonoMap[lrow + tx] * 256 + d];
    case Q6P_BLEND_SHADE:
        return g_dwRdNRaster_aMonoMap[lrow + g_dwRdNRaster_aAlphaMap[tx * 256 + d]];
    case Q6P_BLEND16:
        return g_dwRdNRaster_aRGBMap[lrow + g_dwRdNRaster_aAlphaMap[tx * 256 + g_dwRdNRaster_aRGBToPalette[*g_pDest]]];
    default:
        return g_dwRdNRaster_aRGBMap[g_dwRdNRaster_aAlphaMap[g_dwRdNRaster_aRGBToPalette[(unsigned)g_dwRdNRaster_aRGBMap[lrow + tx] << 8] +
                                            g_dwRdNRaster_aRGBToPalette[*g_pDest]]];
    }
}

/* the texel at (u, v): texels[(u >> 16 & umask) + (v >> (16 - log2 w) & vmask)] (arithmetic shifts, count mod 32) */
static unsigned q6_texel(int u, int v)
{
    return g_dwRdNRaster_pPixels[((u >> 16) & (g_dwRdNRaster_uWrap >> 16)) + ((v >> ((16 - g_dwRdNRaster_texRowShift) & 31)) & g_dwRdNRaster_vWrap)];
}

typedef struct {
    int bpp16, key, mode, lit;
    unsigned char *d8;
    int u, du, v, dv, l, dl;
} q6_pstate;

/* count pixels from (u, v) stepping (du, dv) (and l by dl) */
static void q6_ppixels(q6_pstate *s, int count)
{
    do {
        unsigned tx = q6_texel(s->u, s->v);
        int lrow = s->lit ? (s->l >> 8) & 0x3f00 : 0;
        if (!s->key || tx) {
            if (s->bpp16)
                *(unsigned short *)g_pWDest = (unsigned short)q6_ppix(s->mode, tx, lrow, 0);
            else
                *s->d8 = (unsigned char)q6_ppix(s->mode, tx, lrow, *s->d8);
        }
        if (s->bpp16)
            g_pWDest += 2;
        else
            s->d8++;
        s->u += s->du;
        s->v += s->dv;
        if (s->lit)
            s->l += s->dl;
    } while (--count);
}

/* the 16.16 start of u or v of a run: floor(float(x * 65536)) >> mip, plus the rounding bias */
static int q6_pstart(float x, int bias)
{
    return (q6_floor_i(q6_f(x * 65536.0L)) >> (g_dwRdNRaster_mipMapNum & 31)) + bias;
}

/* the per-pixel step: floor(float(d)) >> mip */
static int q6_pstep(long double d)
{
    return q6_floor_i(q6_f(d)) >> (g_dwRdNRaster_mipMapNum & 31);
}

static void q6_pspan(int *L, int *R, int kind, int bpp16, int key, int mode)
{
    int xs = L[0], xr = R[0], xl, n, m, head, rest, runs, tail, t, frac;
    long double sub, p2x, r, h;
    float p0, p1, p2, u0, v0, u1, v1, inv, tf;
    q6_pstate s;
    if (xs & 0xffff)
        xs = (xs + 0x10000) & 0xffff0000;
    if (xr & 0xffff)
        xr = (xr + 0x10000) & 0xffff0000;
    xl = xs >> 16;
    n = (xr >> 16) - xl;
    if (n <= 0)
        return;
    q6_fldcw(&DAT_00900528);
    s.bpp16 = bpp16;
    s.key = key;
    s.mode = mode;
    s.lit = kind == 15;
    m = xl % 16;
    if (m) {
        head = 16 - m;
        if (n < head)
            head = n;
    } else
        head = 0;
    rest = n - head;
    if (rest) {
        runs = rest / 16;
        tail = rest % 16;
        if (!tail) {
            runs--;
            tail = 16;
        }
    } else
        runs = tail = 0;
    frac = xs - L[0];
    if (s.lit) {
        s.dl = q6_mul16(R[14] - L[14], g_aRdRaster_OneOverNFixed[n]);
        if (s.dl < 0 && s.dl > -0x51e)
            s.dl = 0;
        s.l = q6_mul16(frac, s.dl) + L[14];
    }
    /* the plane values at the first pixel centre column and u, v there */
    sub = (long double)frac * (1.0f / 65536.0f);
    p0 = q6_f(sub * g_dwRdNRaster_dOneOverZdX + ((float *)L)[4]);
    p1 = q6_f(sub * g_dwRdNRaster_dUOverZdX + ((float *)L)[6]);
    p2x = sub * g_dwRdNRaster_dVOverZdX + ((float *)L)[8];
    if (kind == 15) {
        p2 = q6_f(p2x);
        p2x = p2;
    }
    r = 1.0L / p0;
    u0 = q6_f(r * p1);
    v0 = q6_f(r * p2x);
    if (bpp16)
        g_pWDest = Q6_I(Q6_CBUF(), 0x5c) + (L[0x10] * ((unsigned)Q6_I(Q6_CBUF(), 0x18) >> 1) + xl) * 2;
    else
        s.d8 = (unsigned char *)(L[0x10] * Q6_I(Q6_CBUF(), 0x18) + Q6_I(Q6_CBUF(), 0x5c) + xl);
    if (head) {
        h = head;
        inv = q6_copy(g_dwRdRaster_aOneOverNFlex[head]);
        p0 = q6_f(h * g_dwRdNRaster_dOneOverZdX + p0);
        p1 = q6_f(h * g_dwRdNRaster_dUOverZdX + p1);
        p2 = q6_f(h * g_dwRdNRaster_dVOverZdX + p2x);
        r = 1.0L / p0;
        u1 = q6_f(r * p1);
        v1 = q6_f(r * p2);
        s.du = q6_pstep(((long double)u1 - u0) * inv * 65536.0f);
        s.dv = q6_pstep(((long double)v1 - v0) * inv * 65536.0f);
        s.u = q6_pstart(u0, g_dwRdNRaster_dUdXModifier);
        s.v = q6_pstart(v0, g_dwRdNRaster_dVdXModifier);
        q6_ppixels(&s, head);
        p0 = q6_f((long double)p0 + g_dwRdNRaster_oneOverZStep);
        u0 = u1;
        v0 = v1;
        p1 = q6_f((long double)p1 + g_dwRdNRaster_uOverZStep);
        p2 = q6_f((long double)p2 + g_dwRdNRaster_vOverZStep);
    } else {
        p0 = q6_f((long double)p0 + g_dwRdNRaster_oneOverZStep);
        p1 = q6_f((long double)p1 + g_dwRdNRaster_uOverZStep);
        p2 = q6_f(p2x + g_dwRdNRaster_vOverZStep);
        /* registers the original leaves as they are in this path (used if the span is a single tail pixel) */
        s.u = s.v = (kind == 15 && !bpp16) ? s.l : q6_u32(p0);
        s.du = s.dv = 0;
    }
    for (; runs > 0; runs--) {
        r = 1.0L / p0;
        u1 = q6_f(r * p1);
        v1 = q6_f(r * p2);
        s.du = q6_pstep(((long double)u1 - u0) * 0.0625f * 65536.0f);
        s.dv = q6_pstep(((long double)v1 - v0) * 0.0625f * 65536.0f);
        s.u = q6_pstart(u0, g_dwRdNRaster_dUdXModifier);
        s.v = q6_pstart(v0, g_dwRdNRaster_dVdXModifier);
        q6_ppixels(&s, 16);
        p0 = q6_f((long double)p0 + g_dwRdNRaster_oneOverZStep);
        u0 = u1;
        v0 = v1;
        p1 = q6_f((long double)p1 + g_dwRdNRaster_uOverZStep);
        p2 = q6_f((long double)p2 + g_dwRdNRaster_vOverZStep);
    }
    if (tail) {
        t = tail - 1;
        if (t) {
            if (kind == 10) {
                tf = q6_f((long double)t);
                r = 1.0L / ((long double)tf * g_dwRdNRaster_dOneOverZdX - g_dwRdNRaster_oneOverZStep + p0);
                u1 = q6_f(((long double)tf * g_dwRdNRaster_dUOverZdX - g_dwRdNRaster_uOverZStep + p1) * r);
                v1 = q6_f(((long double)tf * g_dwRdNRaster_dVOverZdX - g_dwRdNRaster_vOverZStep + p2) * r);
                s.du = q6_pstep(((long double)u1 - u0) / tf * 65536.0f);
                s.dv = q6_pstep(((long double)v1 - v0) / tf * 65536.0f);
            } else {
                h = t;
                inv = q6_copy(g_dwRdRaster_aOneOverNFlex[t]);
                r = 1.0L / (h * g_dwRdNRaster_dOneOverZdX - g_dwRdNRaster_oneOverZStep + p0);
                u1 = q6_f((h * g_dwRdNRaster_dUOverZdX - g_dwRdNRaster_uOverZStep + p1) * r);
                v1 = q6_f((h * g_dwRdNRaster_dVOverZdX - g_dwRdNRaster_vOverZStep + p2) * r);
                s.du = q6_pstep(((long double)u1 - u0) * inv * 65536.0f);
                s.dv = q6_pstep(((long double)v1 - v0) * inv * 65536.0f);
            }
            s.u = q6_pstart(u0, g_dwRdNRaster_dUdXModifier);
            s.v = q6_pstart(v0, g_dwRdNRaster_dVdXModifier);
        }
        q6_ppixels(&s, t + 1);
    }
    q6_fldcw(&DAT_00900524);
}

/* OVERRIDES: rdNRaster_DrawScanLineNGonLIT_16 */
void rdNRaster_DrawScanLineNGonLIT_16(int *L, int *R) { q6_pspan(L, R, 10, 1, 0, Q6P_PAL); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonTLIT_8 */
void rdNRaster_DrawScanLineNGonTLIT_8(int *L, int *R) { q6_pspan(L, R, 10, 0, 0, Q6P_BLEND8); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonTLIT_16 */
void rdNRaster_DrawScanLineNGonTLIT_16(int *L, int *R) { q6_pspan(L, R, 10, 1, 0, Q6P_BLEND16); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonMLIT_8 */
void rdNRaster_DrawScanLineNGonMLIT_8(int *L, int *R) { q6_pspan(L, R, 10, 0, 1, Q6P_TEX); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonMLIT_16 */
void rdNRaster_DrawScanLineNGonMLIT_16(int *L, int *R) { q6_pspan(L, R, 10, 1, 1, Q6P_PAL); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonMTLIT_8 */
void rdNRaster_DrawScanLineNGonMTLIT_8(int *L, int *R) { q6_pspan(L, R, 10, 0, 1, Q6P_BLEND8); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonMTLIT_16 */
void rdNRaster_DrawScanLineNGonMTLIT_16(int *L, int *R) { q6_pspan(L, R, 10, 1, 1, Q6P_BLEND16); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonFIT_16 */
void rdNRaster_DrawScanLineNGonFIT_16(int *L, int *R) { q6_pspan(L, R, 12, 1, 0, Q6P_PAL); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonTFIT_8 */
void rdNRaster_DrawScanLineNGonTFIT_8(int *L, int *R) { q6_pspan(L, R, 12, 0, 0, Q6P_SHADE_BLEND); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonTFIT_16 */
void rdNRaster_DrawScanLineNGonTFIT_16(int *L, int *R) { q6_pspan(L, R, 12, 1, 0, Q6P_ODD16); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonMFIT_8 */
void rdNRaster_DrawScanLineNGonMFIT_8(int *L, int *R) { q6_pspan(L, R, 12, 0, 1, Q6P_SHADE); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonMFIT_16 */
void rdNRaster_DrawScanLineNGonMFIT_16(int *L, int *R) { q6_pspan(L, R, 12, 1, 1, Q6P_PAL); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonMTFIT_8 */
void rdNRaster_DrawScanLineNGonMTFIT_8(int *L, int *R) { q6_pspan(L, R, 12, 0, 1, Q6P_BLEND_SHADE); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonMTFIT_16 */
void rdNRaster_DrawScanLineNGonMTFIT_16(int *L, int *R) { q6_pspan(L, R, 12, 1, 1, Q6P_BLEND16); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonTGIT_8 */
void rdNRaster_DrawScanLineNGonTGIT_8(int *L, int *R) { q6_pspan(L, R, 15, 0, 0, Q6P_SHADE_BLEND); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonTGIT_16 */
void rdNRaster_DrawScanLineNGonTGIT_16(int *L, int *R) { q6_pspan(L, R, 15, 1, 0, Q6P_ODD16); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonMGIT_8 */
void rdNRaster_DrawScanLineNGonMGIT_8(int *L, int *R) { q6_pspan(L, R, 15, 0, 1, Q6P_SHADE); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonMGIT_16 */
void rdNRaster_DrawScanLineNGonMGIT_16(int *L, int *R) { q6_pspan(L, R, 15, 1, 1, Q6P_PAL); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonMTGIT_8 */
void rdNRaster_DrawScanLineNGonMTGIT_8(int *L, int *R) { q6_pspan(L, R, 15, 0, 1, Q6P_BLEND_SHADE); }
/* OVERRIDES: rdNRaster_DrawScanLineNGonMTGIT_16 */
void rdNRaster_DrawScanLineNGonMTGIT_16(int *L, int *R) { q6_pspan(L, R, 15, 1, 1, Q6P_BLEND16); }

/* ==== Span16_Tex_14: the gouraud 16 bpp perspective span of Draw_FlatLit_6 (through its span pointer) ====
 * The same algorithm as the kind-15 spans (pixel palette[lrow + texel], no key), but written (or compiled) with
 * globals for every intermediate value, which therefore keep the last values when it returns; its x87 also differs:
 * the head / tail counts are converted to floats and stored, 1/p is stored as a float and v = float(1/p) * V uses that
 * float (u = 1/p * U uses the extended value), the tail moves the plane values back by one 16-pixel step and
 * forward by t pixels in place.  The run counter ends at -1.  Without a head the u, v of a single tail pixel are the
 * globals' old values (as in the original, whose registers hold them).  Globals (0x007f4xxx): */
extern float g_dwOneOverZ, g_dwUOverZ, g_dwVOverZ;      /* plane values at the first pixel centre */
extern float g_dwEndOneOverZ, g_dwEndUOverZ, g_dwEndVOverZ;      /* plane values at the current run start */
extern float g_dwCurZ, g_dwEndZ;                   /* 1 / p0 there and at the run end (floats) */
extern float g_dwCurU, g_dwCurV, g_dwEndU, g_dwEndV;  /* u, v at the run start and end */
extern float g_dwFlexStartScrap, g_dwOneOverStartScrap, g_dwFlexEndScrap, g_dwOneOverEndScrap;    /* head / tail count and 1/n (floats) */
extern int g_dwStartScrap, g_dwNumSubdivisions, g_dwEndScrap;     /* head, runs, tail */
extern int g_dwIStep, g_dwFixI;                    /* light step, light */
extern int g_dwUStep, g_dwVStep, g_dwFixU, g_dwFixV;  /* du, dv, u, v */

/* one run or head or tail of Span16_Tex_14: count pixels; the loop works on the globals */
static void q6_tex14_pixels(int count)
{
    do {
        unsigned tx = q6_texel(g_dwFixU, g_dwFixV);
        *(unsigned short *)g_pWDest = g_dwRdNRaster_aRGBMap[(((g_dwFixI >> 16) & 0x3f) << 8) + tx];
        g_pWDest += 2;
        g_dwFixU += g_dwUStep;
        g_dwFixV += g_dwVStep;
        g_dwFixI += g_dwIStep;
    } while (--count);
}

/* u, v at the run end from the plane values at it; then the steps over the run (times inv) and the start values */
static void q6_tex14_run(long double inv)
{
    long double r = 1.0L / g_dwEndOneOverZ;
    g_dwEndZ = q6_f(r);
    g_dwEndU = q6_f(r * g_dwEndUOverZ);
    g_dwEndV = q6_f((long double)g_dwEndZ * g_dwEndVOverZ);
    g_dwUStep = q6_pstep(((long double)g_dwEndU - g_dwCurU) * inv * 65536.0f);
    g_dwVStep = q6_pstep(((long double)g_dwEndV - g_dwCurV) * inv * 65536.0f);
    g_dwFixU = q6_pstart(g_dwCurU, g_dwRdNRaster_dUdXModifier);
    g_dwFixV = q6_pstart(g_dwCurV, g_dwRdNRaster_dVdXModifier);
}

/* the 16-pixel step of the plane values; the run end becomes the run start */
static void q6_tex14_next(void)
{
    g_dwEndOneOverZ = q6_f((long double)g_dwRdNRaster_oneOverZStep + g_dwEndOneOverZ);
    q6_u32(g_dwCurU) = q6_u32(g_dwEndU);
    q6_u32(g_dwCurV) = q6_u32(g_dwEndV);
    q6_u32(g_dwCurZ) = q6_u32(g_dwEndZ);
    g_dwEndUOverZ = q6_f((long double)g_dwRdNRaster_uOverZStep + g_dwEndUOverZ);
    g_dwEndVOverZ = q6_f((long double)g_dwRdNRaster_vOverZStep + g_dwEndVOverZ);
}

/* OVERRIDES: rdNRaster_DrawScanLineNGonGIT_16 */
void rdNRaster_DrawScanLineNGonGIT_16(int *L, int *R)
{
    int xs = L[0], xr = R[0], xl, n, m, rest, frac;
    long double sub, r;
    if (xs & 0xffff)
        xs = (xs + 0x10000) & 0xffff0000;
    if (xr & 0xffff)
        xr = (xr + 0x10000) & 0xffff0000;
    xl = xs >> 16;
    n = (xr >> 16) - xl;
    if (n <= 0)
        return;
    q6_fldcw(&DAT_00900528);
    m = xl % 16;
    if (m) {
        g_dwStartScrap = 16 - m;
        if (n < g_dwStartScrap)
            g_dwStartScrap = n;
    } else
        g_dwStartScrap = 0;
    rest = n - g_dwStartScrap;
    if (rest) {
        g_dwNumSubdivisions = rest / 16;
        g_dwEndScrap = rest % 16;
        if (!g_dwEndScrap) {
            g_dwEndScrap = 16;
            g_dwNumSubdivisions--;
        }
    } else
        g_dwNumSubdivisions = g_dwEndScrap = 0;
    frac = xs - L[0];
    sub = (long double)frac * (1.0f / 65536.0f);
    g_dwOneOverZ = q6_f(sub * g_dwRdNRaster_dOneOverZdX + ((float *)L)[4]);
    g_dwUOverZ = q6_f(sub * g_dwRdNRaster_dUOverZdX + ((float *)L)[6]);
    g_dwVOverZ = q6_f(sub * g_dwRdNRaster_dVOverZdX + ((float *)L)[8]);
    g_dwIStep = q6_mul16(R[14] - L[14], g_aRdRaster_OneOverNFixed[n]);
    if (g_dwIStep < 0 && g_dwIStep > -0x51e)
        g_dwIStep = 0;
    g_dwFixI = q6_mul16(frac, g_dwIStep) + L[14];
    r = 1.0L / g_dwOneOverZ;
    g_dwCurZ = q6_f(r);
    g_dwCurU = q6_f(r * g_dwUOverZ);
    g_dwCurV = q6_f((long double)g_dwCurZ * g_dwVOverZ);
    g_pWDest = Q6_I(Q6_CBUF(), 0x5c) + (L[0x10] * ((unsigned)Q6_I(Q6_CBUF(), 0x18) >> 1) + xl) * 2;
    if (g_dwStartScrap) {
        g_dwFlexStartScrap = q6_f((long double)g_dwStartScrap);
        g_dwOneOverStartScrap = q6_copy(g_dwRdRaster_aOneOverNFlex[g_dwStartScrap]);
        g_dwEndOneOverZ = q6_f((long double)g_dwRdNRaster_dOneOverZdX * g_dwFlexStartScrap + g_dwOneOverZ);
        g_dwEndUOverZ = q6_f((long double)g_dwRdNRaster_dUOverZdX * g_dwFlexStartScrap + g_dwUOverZ);
        g_dwEndVOverZ = q6_f((long double)g_dwRdNRaster_dVOverZdX * g_dwFlexStartScrap + g_dwVOverZ);
        q6_tex14_run(g_dwOneOverStartScrap);
        if (g_dwStartScrap > 0)
            q6_tex14_pixels(g_dwStartScrap);
        q6_tex14_next();
    } else {
        g_dwEndOneOverZ = q6_f((long double)g_dwRdNRaster_oneOverZStep + g_dwOneOverZ);
        g_dwEndUOverZ = q6_f((long double)g_dwRdNRaster_uOverZStep + g_dwUOverZ);
        g_dwEndVOverZ = q6_f((long double)g_dwRdNRaster_vOverZStep + g_dwVOverZ);
    }
    while (g_dwNumSubdivisions-- > 0) {
        q6_tex14_run(0.0625f);
        q6_tex14_pixels(16);
        q6_tex14_next();
    }
    if (g_dwEndScrap) {
        if (--g_dwEndScrap) {
            g_dwFlexEndScrap = q6_f((long double)g_dwEndScrap);
            g_dwOneOverEndScrap = q6_copy(g_dwRdRaster_aOneOverNFlex[g_dwEndScrap]);
            g_dwEndOneOverZ = q6_f((long double)g_dwRdNRaster_dOneOverZdX * g_dwFlexEndScrap - g_dwRdNRaster_oneOverZStep + g_dwEndOneOverZ);
            g_dwEndUOverZ = q6_f((long double)g_dwRdNRaster_dUOverZdX * g_dwFlexEndScrap - g_dwRdNRaster_uOverZStep + g_dwEndUOverZ);
            g_dwEndVOverZ = q6_f((long double)g_dwRdNRaster_dVOverZdX * g_dwFlexEndScrap - g_dwRdNRaster_vOverZStep + g_dwEndVOverZ);
            q6_tex14_run(g_dwOneOverEndScrap);
        }
        if (g_dwEndScrap >= 0)
            q6_tex14_pixels(g_dwEndScrap + 1);
    }
    q6_fldcw(&DAT_00900524);
}

/* ==== Draw16_TexLitKey_7: the gouraud perspective keyed driver (as build/overrides_asm_o1.c's Draw16_TexLit_10 with
 * the keyed spans) ====
 * Set-up: mip mode (texture +0x18 - 1), vertices, uv, per-vertex light, the 8 bpp shade table / the 16 bpp palette and
 * 16 bpp -> index table, the translucency table, the polygon globals, Grad_Flat_2, then the mip level's texels, log2
 * width, masks and the plane gradients times 16 (floats).  Walk: edges Edge_Flat_17 (left, with the plane values) and
 * _18; per scan line Span_TexKey_7 (8 bpp) / Span16_TexKey_11 (16 bpp); the left edge steps its three plane values
 * (float adds), both step x and light. */
extern int rdNRaster_SetupLeftEdgeNGonGIT(int *), rdNRaster_SetupRightEdgeNGonGIT(int *);
/* OVERRIDES: rdNRaster_DrawNGonMTGIT */
void rdNRaster_DrawNGonMTGIT(int p, int mat)
{
    int bpp = Q6_BPP(), mip, a[0x11], b[0x11];
    char *tex = *(char **)(mat + 0x1c), *tb = *(char **)(p + 0x4c);
    g_dwRdNRaster_maxMipMap = Q6_I(tex, 0x18) - 1;
    g_pRdNRaster_aVertices = *(float **)(p + 0x20);
    g_dwRdNRaster_aTexVertices = *(float **)(p + 0x24);
    g_dwRdNRaster_aIntensities = *(float **)(p + 0x28);
    if (bpp == 8)
        g_dwRdNRaster_aMonoMap = *(unsigned char **)(tb + 0x330);
    else if (bpp == 16) {
        g_dwRdNRaster_aRGBMap = *(unsigned short **)(tb + 0x348);
        g_dwRdNRaster_aRGBToPalette = *(unsigned char **)(tb + 0x34c);
    }
    g_dwRdNRaster_aAlphaMap = *(unsigned char **)(g_dwRdColormap_pCurMap + 0x338);
    q6_poly_globals(p);
    rdNRaster_CalcPerspGradients(Q6_I(p, 0x64));
    mip = g_dwRdNRaster_mipMapNum;
    g_dwRdNRaster_pPixels = *(unsigned char **)(*(char **)(tex + 0x1c + mip * 4) + 0x5c);
    g_dwRdNRaster_texRowShift = Q6_I(tex, 0xc) - mip;
    g_dwRdNRaster_uWrap = (int)(((unsigned)Q6_I(tex, 0x10) >> (mip & 31)) << 16);
    g_dwRdNRaster_oneOverZStep = q6_f((long double)g_dwRdNRaster_dOneOverZdX * 16.0f);
    g_dwRdNRaster_uOverZStep = q6_f((long double)g_dwRdNRaster_dUOverZdX * 16.0f);
    g_dwRdNRaster_vOverZStep = q6_f((long double)g_dwRdNRaster_dVOverZdX * 16.0f);
    g_dwRdNRaster_vWrap = (int)(((unsigned)Q6_I(tex, 0x14) >> (mip & 31)) << (g_dwRdNRaster_texRowShift & 31));
    a[3] = g_nRdNRaster_yMinVert;
    if (rdNRaster_SetupLeftEdgeNGonGIT(a))
        return;
    b[3] = g_nRdNRaster_yMinVert;
    if (rdNRaster_SetupRightEdgeNGonGIT(b))
        return;
    for (;;) {
        if (bpp == 8)
            rdNRaster_DrawScanLineNGonMTGIT_8(a, b);
        else if (bpp == 16)
            rdNRaster_DrawScanLineNGonMTGIT_16(a, b);
        if (--a[2] == 0) {
            if (rdNRaster_SetupLeftEdgeNGonGIT(a))
                return;
        } else {
            ((float *)a)[4] = q6_f((long double)((float *)a)[4] + ((float *)a)[5]);
            ((float *)a)[6] = q6_f((long double)((float *)a)[6] + ((float *)a)[7]);
            ((float *)a)[8] = q6_f((long double)((float *)a)[8] + ((float *)a)[9]);
            a[0] += a[1];
            a[14] += a[15];
            a[0x10]++;
        }
        if (--b[2] == 0) {
            if (rdNRaster_SetupRightEdgeNGonGIT(b))
                return;
        } else {
            b[0] += b[1];
            b[14] += b[15];
            b[0x10]++;
        }
    }
}

/* ========================================================================================================
 * The span-list renderer (the siblings of build/overrides_asm_s1.c).  rec is the polygon record of the selectors:
 * rec[0] the polygon (+0x1c vertex count, +0x20 vertices, +0x24 u, v, +0x28 light, +0x4c tables, +0x64 distance,
 * +0x6c top, +0x70 bottom), rec[1 + i] 1/z of vertex i (W), rec[0x21 + i] u/z (U), rec[0x41 + i] v/z (V) (the
 * perspective set-up), +0x184 .. +0x198 the plane gradients (W, U, V by x and y), +0x19c dW/dx * 65536 (int),
 * +0x1a0 / +0x1a4 the u / v rounding biases, +0x1a8 .. +0x1b0 the gradients times 16, +0x1b4 the span list drawer,
 * +0x1c0 the mip level, +0x1c4 its texels, +0x1c8 its log2 width, +0x1cc its width, +0x1d0 a colour, +0x1d4 / +0x1d8
 * the u / v masks, +0x1dc / +0x1e0 the 8 / 16 bpp colour tables, +0x1e8 the edge set-up.
 * ======================================================================================================== */
#define Q6_RF(rec, i) (((float *)(rec))[i])

/* ==== SetupPoly: the affine set-up of a polygon record ====
 * As Grad_Flat on the polygon's arrays (vertices a, b, c; the third vertex starts as the bits of the record pointer
 * when the vertex next to the top is the bottom, an index the original would use as is), plus W = float(1 / z) per
 * vertex into rec[1 + i]; mip level from the mode argument and the polygon's distance into +0x1c0, biases into +0x1a0,
 * +0x1a4. */
/* OVERRIDES: rdAFRaster_CalcAffineGradients */
void rdAFRaster_CalcAffineGradients(int *rec, int mode)
{
    char *P = *(char **)rec;
    float *V = *(float **)(P + 0x20);
    int a, b, c, i;
    q6_pick(V, Q6_I(P, 0x1c), Q6_I(P, 0x6c), Q6_I(P, 0x70), (int)rec, &a, &b, &c);
    for (i = 0; i < Q6_I(P, 0x1c); i++)
        Q6_RF(rec, 1 + i) = q6_f(1.0L / (*(float **)(P + 0x20))[i * 3 + 2]);
    q6_affine_bias(*(float **)(P + 0x20), *(float **)(P + 0x24), a, b, c, &rec[0x68], &rec[0x69]);
    q6_mip_level(*(float *)(P + 0x64), mode, &rec[0x70]);
}

/* ==== SetupPolyTex: the perspective set-up of a polygon record ====
 * Vertices a, b, c as SetupPoly (the third vertex starts from a stack slot the original never writes when the vertex
 * next to the top is the bottom: the C starts it at 0).  Per vertex w = 1 / z: W = float(w), U = float(u * w) (w
 * extended), V = float(v * W).  The gradients through a, b, c: dYa = ya - yc, dYb = yb - yc extended (and as floats),
 * dXa, dXb floats; R = float(1 / (dYa * dXb - dYb * dXa)), nR = -R; dW/dx = (dWb * dYa - dWa * dYb) * R and
 * dW/dy = (dWb * dXa - dWa * dXb) * nR with dWa, dWb extended, the U and V gradients from the float differences;
 * all stored as floats, and _ftol(dW/dx * 65536) (extended) into +0x19c.  The biases use the extended dU/dx and dW/dx:
 * u: Wa * dU/dx - Ua * dW/dx (> 0: 0x8000; < 0 or NaN: 0x7fff; 0: by Wa * dU/dy - Ua * dW/dy (floats)); v: Wa *
 * float(dV/dx) - Va * dW/dx, for 0 Wa * dV/dy - Va * dW/dy. */
/* OVERRIDES: rdAFRaster_CalcPerspGradients */
void rdAFRaster_CalcPerspGradients(int *rec, int mode)
{
    char *P = *(char **)rec;
    float *V = *(float **)(P + 0x20), *T, *va, *vb, *vc;
    float *W = &Q6_RF(rec, 1), *U = &Q6_RF(rec, 0x21), *VV = &Q6_RF(rec, 0x41);
    int a, b, c, i, cnt = Q6_I(P, 0x1c);
    long double w, R, dWb, dWa, dWdx, dWdy, dUdx, t;
    float fdYa, fdYb, fdXa, fdXb, fR, fnR, fdUb, fdUa, fdVb, fdVa, fdWdy, fdUdy, fdVdx, fdVdy;
    q6_pick(V, cnt, Q6_I(P, 0x6c), Q6_I(P, 0x70), 0, &a, &b, &c);
    for (i = 0; i < Q6_I(P, 0x1c); i++) {
        w = 1.0L / (*(float **)(P + 0x20))[i * 3 + 2];
        W[i] = q6_f(w);
        U[i] = q6_f((*(float **)(P + 0x24))[i * 2] * w);
        VV[i] = q6_f((long double)(*(float **)(P + 0x24))[i * 2 + 1] * W[i]);
    }
    V = *(float **)(P + 0x20);
    va = V + a * 3;
    vb = V + b * 3;
    vc = V + c * 3;
    fdYa = q6_f((long double)va[1] - vc[1]);
    fdYb = q6_f((long double)vb[1] - vc[1]);
    fdXa = q6_f((long double)va[0] - vc[0]);
    fdXb = q6_f((long double)vb[0] - vc[0]);
    R = 1.0L / (((long double)va[1] - vc[1]) * fdXb - ((long double)vb[1] - vc[1]) * fdXa);
    dWb = (long double)W[b] - W[c];
    dWa = (long double)W[a] - W[c];
    fdUb = q6_f((long double)U[b] - U[c]);
    fdUa = q6_f((long double)U[a] - U[c]);
    fdVb = q6_f((long double)VV[b] - VV[c]);
    fdVa = q6_f((long double)VV[a] - VV[c]);
    fR = q6_f(R);
    fnR = q6_f(-(long double)fR);
    dWdx = (dWb * fdYa - dWa * fdYb) * fR;
    dWdy = (dWb * fdXa - dWa * fdXb) * fnR;
    fdWdy = q6_f(dWdy);
    Q6_RF(rec, 0x61) = q6_f(dWdx);
    Q6_RF(rec, 0x62) = fdWdy;
    rec[0x67] = q6_ftol(dWdx * 65536.0f);
    dUdx = ((long double)fdUb * fdYa - (long double)fdUa * fdYb) * fR;
    Q6_RF(rec, 0x63) = q6_f(dUdx);
    fdUdy = q6_f(((long double)fdUb * fdXa - (long double)fdUa * fdXb) * fnR);
    Q6_RF(rec, 0x64) = fdUdy;
    fdVdx = q6_f(((long double)fdVb * fdYa - (long double)fdVa * fdYb) * fR);
    Q6_RF(rec, 0x65) = fdVdx;
    fdVdy = q6_f(((long double)fdVb * fdXa - (long double)fdVa * fdXb) * fnR);
    Q6_RF(rec, 0x66) = fdVdy;
    q6_mip_level(*(float *)(P + 0x64), mode, &rec[0x70]);
    t = (long double)W[a] * dUdx - U[a] * dWdx;
    if (t > 0.0L)
        rec[0x68] = 0x8000;
    else if (!(t >= 0.0L) || !((long double)W[a] * fdUdy - (long double)U[a] * fdWdy >= 0.0L))
        rec[0x68] = 0x7fff;
    else
        rec[0x68] = 0x8000;
    t = (long double)W[a] * fdVdx - VV[a] * dWdx;
    if (t > 0.0L)
        rec[0x69] = 0x8000;
    else if (!(t >= 0.0L) || !((long double)W[a] * fdVdy - (long double)VV[a] * fdWdy >= 0.0L))
        rec[0x69] = 0x7fff;
    else
        rec[0x69] = 0x8000;
}

/* ==== the selectors (Select_TexLit, Select_FlatLit_4 / 5 / 8 .. 13): fill the polygon record and its callbacks ==== */
extern void rdRaster_EdgeStepFlat(int), FUN_004104b0(int), FUN_00411b70(int), FUN_004129f0(int);
extern void FUN_00415180(int), FUN_004151c0(int), rdAFRaster_AdvanceLeftEdgeNGonGIT(int), rdAFRaster_AdvanceRightEdgeNGonGIT(int);
extern void rdAFRaster_DrawNGonFS(int), rdAFRaster_DrawNGonFAT(int), rdAFRaster_DrawNGonMFAT(int), rdAFRaster_DrawNGonLIT(int), rdAFRaster_DrawNGonMLIT(int);
extern void rdAFRaster_DrawNGonFIT(int), rdAFRaster_DrawNGonMFIT(int), rdAFRaster_DrawNGonGIT(int), rdAFRaster_DrawNGonMGIT(int);
int rdAFRaster_SetupEdgeNGonFS(int *, int *, int, int), rdAFRaster_SetupEdgeNGonFAT(int *, int *, int, int);
int rdAFRaster_SetupEdgeNGonLIT(int *, int *, int, int), rdAFRaster_SetupEdgeNGonFIT(int *, int *, int, int);
int rdAFRaster_SetupEdgeNGonGIT(int *, int *, int, int);

/* ==== Select_TexLit: flat colour at the light level floor(light) ====
 * W = float(1 / z) per vertex into rec[1 + i] (unsigned count), the colour byte of the 8 bpp table at the material's
 * index and the level's row into +0x1d0, the span drawer SpanLitSetup and the edge set-up EdgeSetup_Flat_3. */
/* OVERRIDES: rdAFRaster_SetupNGonFS */
void rdAFRaster_SetupNGonFS(int *rec, int mat, float light)
{
    char *P = *(char **)rec;
    unsigned i;
    int level;
    for (i = 0; i < (unsigned)Q6_I(P, 0x1c); i++)
        Q6_RF(rec, 1 + i) = q6_f(1.0L / (*(float **)(P + 0x20))[i * 3 + 2]);
    level = q6_floor_i(light);
    P = *(char **)rec;
    rec[0x74] = (*(unsigned char **)(*(char **)(P + 0x4c) + 0x330))[Q6_I(mat, 4) + level * 256];
    rec[0x6d] = (int)rdAFRaster_DrawNGonFS;
    rec[0x7a] = (int)rdAFRaster_SetupEdgeNGonFS;
}

/* the texture fields of the record for its mip level (+0x1c0): texels, log2 width, width, masks (texture record:
 * material +0x1c: +0xc log2 width, +0x10 / +0x14 the masks, +0x1c + 4 * level the level records: +0x18 width,
 * +0x5c texels) */
static void q6_rec_tex(int *rec, int mat)
{
    char *tex = *(char **)(mat + 0x1c);
    int mip = rec[0x70];
    rec[0x71] = Q6_I(*(char **)(tex + 0x1c + mip * 4), 0x5c);
    rec[0x72] = Q6_I(tex, 0xc) - mip;
    rec[0x73] = Q6_I(*(char **)(tex + 0x1c + mip * 4), 0x18);
    rec[0x75] = (int)(((unsigned)Q6_I(tex, 0x10) >> (mip & 31)) << 16);
    rec[0x76] = (int)(((unsigned)Q6_I(tex, 0x14) >> (mip & 31)) << (rec[0x72] & 31));
}

/* the colour tables at the light level floor(light): 8 bpp shade + level * 256, 16 bpp palette + level * 512 */
static void q6_rec_level(int *rec, int bpp, float light)
{
    char *tb = *(char **)(*(char **)rec + 0x4c);
    if (bpp == 8)
        rec[0x77] = Q6_I(tb, 0x330) + q6_floor_i(light) * 256;
    else if (bpp == 16)
        rec[0x78] = Q6_I(tb, 0x348) + q6_floor_i(light) * 512;
}

/* ==== Select_FlatLit_4 / _5: affine textured at the light level; span drawers rdAFRaster_DrawNGonFAT / rdAFRaster_DrawNGonMFAT ==== */
static void q6_select_lit_affine(int *rec, int mat, float light, void (*span)(int))
{
    int bpp = Q6_BPP();
    rdAFRaster_CalcAffineGradients(rec, Q6_I(*(char **)(mat + 0x1c), 0x18) - 1);
    rec[0x71] = Q6_I(*(char **)(*(char **)(mat + 0x1c) + 0x1c + rec[0x70] * 4), 0x5c);
    q6_rec_level(rec, bpp, light);
    q6_rec_tex(rec, mat);
    rec[0x6d] = (int)span;
    rec[0x7a] = (int)rdAFRaster_SetupEdgeNGonFAT;
}
/* OVERRIDES: rdAFRaster_SetupNGonFAT */
void rdAFRaster_SetupNGonFAT(int *rec, int mat, float light) { q6_select_lit_affine(rec, mat, light, rdAFRaster_DrawNGonFAT); }
/* OVERRIDES: rdAFRaster_SetupNGonMFAT */
void rdAFRaster_SetupNGonMFAT(int *rec, int mat, float light) { q6_select_lit_affine(rec, mat, light, rdAFRaster_DrawNGonMFAT); }

/* the perspective selectors: SetupPolyTex, the gradients times 16 (float(g * 16)) */
static int q6_select_persp(int *rec, int mat)
{
    int bpp = Q6_BPP();
    rdAFRaster_CalcPerspGradients(rec, Q6_I(*(char **)(mat + 0x1c), 0x18) - 1);
    Q6_RF(rec, 0x6a) = q6_f((long double)Q6_RF(rec, 0x61) * 16.0f);
    Q6_RF(rec, 0x6b) = q6_f((long double)Q6_RF(rec, 0x63) * 16.0f);
    Q6_RF(rec, 0x6c) = q6_f((long double)Q6_RF(rec, 0x65) * 16.0f);
    return bpp;
}

/* ==== Select_FlatLit_8 / _9: perspective unlit (16 bpp: palette row 63); rdAFRaster_DrawNGonLIT / rdAFRaster_DrawNGonMLIT, EdgeSetup_8 ==== */
static void q6_select_persp_unlit(int *rec, int mat, void (*span)(int))
{
    int bpp = q6_select_persp(rec, mat);
    q6_rec_tex(rec, mat);
    if (bpp == 16)
        rec[0x78] = Q6_I(*(char **)(*(char **)rec + 0x4c), 0x348) + 0x7e00;
    rec[0x6d] = (int)span;
    rec[0x7a] = (int)rdAFRaster_SetupEdgeNGonLIT;
}
/* OVERRIDES: rdAFRaster_SetupNGonLIT */
void rdAFRaster_SetupNGonLIT(int *rec, int mat) { q6_select_persp_unlit(rec, mat, rdAFRaster_DrawNGonLIT); }
/* OVERRIDES: rdAFRaster_SetupNGonMLIT */
void rdAFRaster_SetupNGonMLIT(int *rec, int mat) { q6_select_persp_unlit(rec, mat, rdAFRaster_DrawNGonMLIT); }

/* ==== Select_FlatLit_10 / _11: perspective at the light level; rdAFRaster_DrawNGonFIT / rdAFRaster_DrawNGonMFIT, EdgeSetup_9 ==== */
static void q6_select_persp_level(int *rec, int mat, float light, void (*span)(int))
{
    int bpp = q6_select_persp(rec, mat);
    q6_rec_level(rec, bpp, light);
    q6_rec_tex(rec, mat);
    rec[0x6d] = (int)span;
    rec[0x7a] = (int)rdAFRaster_SetupEdgeNGonFIT;
}
/* OVERRIDES: rdAFRaster_SetupNGonFIT */
void rdAFRaster_SetupNGonFIT(int *rec, int mat, float light) { q6_select_persp_level(rec, mat, light, rdAFRaster_DrawNGonFIT); }
/* OVERRIDES: rdAFRaster_SetupNGonMFIT */
void rdAFRaster_SetupNGonMFIT(int *rec, int mat, float light) { q6_select_persp_level(rec, mat, light, rdAFRaster_DrawNGonMFIT); }

/* ==== Select_FlatLit_12 / _13: perspective gouraud (the whole colour tables); rdAFRaster_DrawNGonGIT / rdAFRaster_DrawNGonMGIT,
 * EdgeSetup_10.  _13 returns 1 (the other selectors return nothing). ==== */
static void q6_select_persp_gouraud(int *rec, int mat, void (*span)(int))
{
    int bpp = q6_select_persp(rec, mat);
    char *tb = *(char **)(*(char **)rec + 0x4c);
    if (bpp == 8)
        rec[0x77] = Q6_I(tb, 0x330);
    else if (bpp == 16)
        rec[0x78] = Q6_I(tb, 0x348);
    q6_rec_tex(rec, mat);
    rec[0x6d] = (int)span;
    rec[0x7a] = (int)rdAFRaster_SetupEdgeNGonGIT;
}
/* OVERRIDES: rdAFRaster_SetupNGonGIT */
void rdAFRaster_SetupNGonGIT(int *rec, int mat) { q6_select_persp_gouraud(rec, mat, rdAFRaster_DrawNGonGIT); }
/* OVERRIDES: rdAFRaster_SetupNGonMGIT */
int rdAFRaster_SetupNGonMGIT(int *rec, int mat)
{
    q6_select_persp_gouraud(rec, mat, rdAFRaster_DrawNGonMGIT);
    return 1;
}

/* ==== EdgeSetup_Flat .. _10: the edge set-up of the span-list renderer ====
 * EdgeSetup(node, rec, i0, i1): the edge from vertex i0 to i1.  y0 = ceil(y[i0]), y1 = ceil(y[i1]) (floats),
 * h = floor(y1) - floor(y0) into +0xc; returns 0 when h is 0.  Otherwise the edge is set up from its upper vertex a
 * (i0 when h > 0: +0 = 1, +8 = floor(y0); else i1: +0 = 0, +8 = floor(y1), +0xc = -h) to the other one b, the step
 * function into +0x48, and it returns 1.  One scan line: x (+0x28) and u (+0x30), v (+0x38), light (+0x40) =
 * floor(float(a * 65536)) of vertex a, W (+0x10) copied from rec[1 + a].  More: dy = float(ceil(ya) - ya),
 * inv = float(1 / (yb - ya)), per attribute d = (b - a) * inv extended, step = floor(float(d * 65536)),
 * start = floor(float((float(d) * dy + a) * 65536)); W: dW = float((Wb - Wa) * inv) (+0x14), W = float(dy * dW' + Wa)
 * with the unrounded dW'.
 * The perspective ones (_8, _9: x only; _10: x and light) keep the three plane values: for an edge going down
 * (h > 0) dy is taken first; x: d = (xb - xa) / (yb - ya) (a division in _8 / _9, times inv in _10), xs = float(float(d)
 * * dy + xa) (xa itself for one line); the per-line steps of the planes (only for more than one line) +0x14 / +0x1c /
 * +0x24 = float(g_x * float(d) + g_y), and their values at the start +0x10 = float((gW_y * dy + Wa) + gW_x * dxs),
 * +0x18 = float((gU_y * dy + Ua) + gU_x * dxs), +0x20 = float((gV_x * dxs + Va) + gV_y * dy), dxs = xs - xa extended
 * (g_x, g_y: rec +0x184 .. +0x198).  An edge going up gets no plane values. */
#define Q6E_LIGHT 1   /* light (polygon +0x28) into +0x40 / +0x44 */
#define Q6E_UV 2      /* u, v (polygon +0x24) into +0x30 / +0x34, +0x38 / +0x3c */
#define Q6E_PERSP 4   /* perspective: the plane values instead of W */
#define Q6E_DIV 8     /* perspective x slope by a division (_8, _9) */

/* one attribute: start / step (16.16) from a, b, the float inv and dy; returns float(d) */
static float q6_eattr(float a, float b, float inv, float dy, int *start, int *step)
{
    long double d = ((long double)b - a) * inv;
    float s = q6_f(d);
    *step = q6_floor_i(q6_f(d * 65536.0f));
    *start = q6_floor_i(q6_f(((long double)s * dy + a) * 65536.0f));
    return s;
}

static int q6_esetup(int *node, int *rec, int i0, int i1, int flags, void (*down)(int), void (*up)(int))
{
    char *P = *(char **)rec;
    float *V, *T, *Lt, y0c, y1c, yc, dy, inv, s, xs;
    int y0, y1, h, a, b, down_edge;
    V = *(float **)(P + 0x20);
    y0c = q6_ceil(q6_copy(V[i0 * 3 + 1]));
    y1c = q6_ceil(q6_copy((*(float **)(P + 0x20))[i1 * 3 + 1]));
    y0 = q6_floor_i(y0c);
    y1 = q6_floor_i(y1c);
    h = y1 - y0;
    node[3] = h;
    if (h == 0)
        return 0;
    down_edge = h > 0;
    if (down_edge) {
        node[0] = 1;
        node[2] = y0;
        a = i0;
        b = i1;
        yc = y0c;
    } else {
        node[0] = 0;
        h = -h;
        node[2] = y1;
        node[3] = h;
        a = i1;
        b = i0;
        yc = y1c;
    }
    node[0x12] = (int)(down_edge ? down : up);
    V = *(float **)(P + 0x20);
    T = *(float **)(P + 0x24);
    Lt = *(float **)(P + 0x28);
    if (!(flags & Q6E_PERSP)) {
        if (h < 2) {
            node[10] = q6_floor_i(q6_f(V[a * 3] * 65536.0L));
            if (flags & Q6E_UV) {
                node[12] = q6_floor_i(q6_f(T[a * 2] * 65536.0L));
                node[14] = q6_floor_i(q6_f(T[a * 2 + 1] * 65536.0L));
            }
            if (flags & Q6E_LIGHT)
                node[16] = q6_floor_i(q6_f(Lt[a] * 65536.0L));
            node[4] = rec[1 + a];
            return 1;
        }
        {
            long double dw;
            dy = q6_f((long double)yc - V[a * 3 + 1]);
            inv = q6_f(1.0L / ((long double)V[b * 3 + 1] - V[a * 3 + 1]));
            q6_eattr(V[a * 3], V[b * 3], inv, dy, &node[10], &node[11]);
            if (flags & Q6E_UV) {
                q6_eattr(T[a * 2], T[b * 2], inv, dy, &node[12], &node[13]);
                q6_eattr(T[a * 2 + 1], T[b * 2 + 1], inv, dy, &node[14], &node[15]);
            }
            if (flags & Q6E_LIGHT)
                q6_eattr(Lt[a], Lt[b], inv, dy, &node[16], &node[17]);
            dw = ((long double)Q6_RF(rec, 1 + b) - Q6_RF(rec, 1 + a)) * inv;
            Q6_RF(node, 5) = q6_f(dw);
            Q6_RF(node, 4) = q6_f(dy * dw + Q6_RF(rec, 1 + a));
        }
        return 1;
    }
    /* perspective */
    if (down_edge)
        dy = q6_f((long double)yc - V[a * 3 + 1]);
    if (h < 2) {
        if (down_edge)
            xs = q6_copy(V[a * 3]);
        node[10] = q6_floor_i(q6_f((long double)(down_edge ? xs : V[a * 3]) * 65536.0f));
        if (flags & Q6E_LIGHT)
            node[16] = q6_floor_i(q6_f(Lt[a] * 65536.0L));
        if (!down_edge)
            return 1;
    } else {
        long double d, t;
        if (!down_edge)
            dy = q6_f((long double)yc - V[a * 3 + 1]);
        if (flags & Q6E_DIV)
            d = ((long double)V[b * 3] - V[a * 3]) / ((long double)V[b * 3 + 1] - V[a * 3 + 1]);
        else {
            inv = q6_f(1.0L / ((long double)V[b * 3 + 1] - V[a * 3 + 1]));
            d = ((long double)V[b * 3] - V[a * 3]) * inv;
        }
        s = q6_f(d);
        node[11] = q6_floor_i(q6_f(d * 65536.0f));
        t = (long double)s * dy + V[a * 3];
        if (down_edge)
            xs = q6_f(t);
        node[10] = q6_floor_i(q6_f(t * 65536.0f));
        if (down_edge) {
            Q6_RF(node, 5) = q6_f((long double)Q6_RF(rec, 0x61) * s + Q6_RF(rec, 0x62));
            Q6_RF(node, 7) = q6_f((long double)Q6_RF(rec, 0x63) * s + Q6_RF(rec, 0x64));
            Q6_RF(node, 9) = q6_f((long double)Q6_RF(rec, 0x65) * s + Q6_RF(rec, 0x66));
        }
        if (flags & Q6E_LIGHT)
            q6_eattr(Lt[a], Lt[b], inv, dy, &node[16], &node[17]);
        if (!down_edge)
            return 1;
    }
    {
        long double dxs = (long double)xs - V[a * 3];
        Q6_RF(node, 4) = q6_f(((long double)Q6_RF(rec, 0x62) * dy + Q6_RF(rec, 1 + a)) + Q6_RF(rec, 0x61) * dxs);
        Q6_RF(node, 6) = q6_f(((long double)Q6_RF(rec, 0x64) * dy + Q6_RF(rec, 0x21 + a)) + Q6_RF(rec, 0x63) * dxs);
        Q6_RF(node, 8) = q6_f((Q6_RF(rec, 0x65) * dxs + Q6_RF(rec, 0x41 + a)) + (long double)Q6_RF(rec, 0x66) * dy);
    }
    return 1;
}

/* OVERRIDES: rdAFRaster_SetupEdgeNGonLW */
int rdAFRaster_SetupEdgeNGonLW(int *n, int *r, int i0, int i1) { return q6_esetup(n, r, i0, i1, 0, rdRaster_EdgeStepFlat, rdRaster_EdgeStepFlat); }
/* OVERRIDES: rdAFRaster_SetupEdgeNGonLS */
int rdAFRaster_SetupEdgeNGonLS(int *n, int *r, int i0, int i1) { return q6_esetup(n, r, i0, i1, 0, rdRaster_EdgeStepFlat, rdRaster_EdgeStepFlat); }
/* OVERRIDES: rdAFRaster_SetupEdgeNGonFS */
int rdAFRaster_SetupEdgeNGonFS(int *n, int *r, int i0, int i1) { return q6_esetup(n, r, i0, i1, 0, rdRaster_EdgeStepFlat, rdRaster_EdgeStepFlat); }
/* OVERRIDES: rdAFRaster_SetupEdgeNGonGS */
int rdAFRaster_SetupEdgeNGonGS(int *n, int *r, int i0, int i1) { return q6_esetup(n, r, i0, i1, Q6E_LIGHT, FUN_004104b0, FUN_004104b0); }
/* OVERRIDES: rdAFRaster_SetupEdgeNGonLAT */
int rdAFRaster_SetupEdgeNGonLAT(int *n, int *r, int i0, int i1) { return q6_esetup(n, r, i0, i1, Q6E_UV, FUN_00411b70, FUN_00411b70); }
/* OVERRIDES: rdAFRaster_SetupEdgeNGonFAT */
int rdAFRaster_SetupEdgeNGonFAT(int *n, int *r, int i0, int i1) { return q6_esetup(n, r, i0, i1, Q6E_UV, FUN_00411b70, FUN_00411b70); }
/* OVERRIDES: rdAFRaster_SetupEdgeNGonGAT */
int rdAFRaster_SetupEdgeNGonGAT(int *n, int *r, int i0, int i1) { return q6_esetup(n, r, i0, i1, Q6E_UV | Q6E_LIGHT, FUN_004129f0, FUN_004129f0); }
/* OVERRIDES: rdAFRaster_SetupEdgeNGonLIT */
int rdAFRaster_SetupEdgeNGonLIT(int *n, int *r, int i0, int i1) { return q6_esetup(n, r, i0, i1, Q6E_PERSP | Q6E_DIV, FUN_00415180, FUN_004151c0); }
/* OVERRIDES: rdAFRaster_SetupEdgeNGonFIT */
int rdAFRaster_SetupEdgeNGonFIT(int *n, int *r, int i0, int i1) { return q6_esetup(n, r, i0, i1, Q6E_PERSP | Q6E_DIV, FUN_00415180, FUN_004151c0); }
/* OVERRIDES: rdAFRaster_SetupEdgeNGonGIT */
int rdAFRaster_SetupEdgeNGonGIT(int *n, int *r, int i0, int i1) { return q6_esetup(n, r, i0, i1, Q6E_PERSP | Q6E_LIGHT, rdAFRaster_AdvanceLeftEdgeNGonGIT, rdAFRaster_AdvanceRightEdgeNGonGIT); }

/* ==== SpanR8/16_TexKey, _2, _3: one affine keyed span node of the span-list renderer ====
 * Node: +0 x, +4 pixel count, +8 row, +0xc u, +0x10 du, +0x14 v, +0x18 dv (16.16), +0x1c z (the plane value 1/z),
 * +0x20 / +0x24 light and its step (_3).  z = floor(float(z * 65536)), stepped by g_dwRdAFRaster_dOneOverZdXFixed; a non-zero texel
 * (texels g_dwRdAFRaster_pPixels, u mask g_dwRdAFRaster_uWrap, v shift g_dwRdAFRaster_texRowShift and mask g_dwRdAFRaster_vWrap) is drawn and its
 * z >> (canvas +0x14) written to the z-buffer (no depth test).  A count of 0 draws nothing. */
extern unsigned char *g_dwRdAFRaster_aMonoMap, *g_dwRdAFRaster_pPixels;
extern unsigned short *g_dwRdAFRaster_aRGBMap;
extern int g_dwRdAFRaster_mipMapNum, g_dwRdAFRaster_texRowShift, g_dwRdAFRaster_vWrap, g_dwRdAFRaster_dVdXModifier, g_dwRdAFRaster_dOneOverZdXFixed, g_dwRdAFRaster_dUdXModifier, g_dwRdAFRaster_uWrap;
extern float g_dwRdAFRaster_dOneOverZdX, g_dwRdAFRaster_dUOverZdX, g_dwRdAFRaster_dVOverZdX, g_dwRdAFRaster_oneOverZStep, g_dwRdAFRaster_uOverZStep, g_dwRdAFRaster_vOverZStep;

enum { Q6R_TEX, Q6R_SHADE, Q6R_SHADE_L, Q6R_PAL, Q6R_PAL_L };   /* tx, shade[tx], shade[lrow + tx], pal[...] */

static unsigned q6_rtexel(int u, int v)
{
    return g_dwRdAFRaster_pPixels[((u >> 16) & (g_dwRdAFRaster_uWrap >> 16)) + ((v >> ((16 - g_dwRdAFRaster_texRowShift) & 31)) & g_dwRdAFRaster_vWrap)];
}

static int q6_rpix(int mode, unsigned tx, int l)
{
    switch (mode) {
    case Q6R_TEX:
        return tx;
    case Q6R_SHADE:
        return g_dwRdAFRaster_aMonoMap[tx];
    case Q6R_SHADE_L:
        return g_dwRdAFRaster_aMonoMap[((l >> 8) & 0x3f00) + tx];
    case Q6R_PAL:
        return g_dwRdAFRaster_aRGBMap[tx];
    default:
        return g_dwRdAFRaster_aRGBMap[(((l >> 16) & 0x3f) << 8) + tx];
    }
}

static void q6_spanr(int *node, int bpp16, int mode)
{
    char *c4 = Q6_C4();
    int sh = Q6_I(c4, 0x14), dz = g_dwRdAFRaster_dOneOverZdXFixed, u = node[3], v = node[5], l = node[8], n;
    int z = q6_floor_i(q6_f(Q6_RF(node, 7) * 65536.0L));
    unsigned char *d8 = 0;
    unsigned short *d16 = 0, *zp;
    if (bpp16)
        d16 = (unsigned short *)(Q6_I(Q6_CBUF(), 0x5c) + (((unsigned)Q6_I(Q6_CBUF(), 0x18) >> 1) * node[2] + node[0]) * 2);
    else
        d8 = (unsigned char *)(Q6_I(Q6_CBUF(), 0x18) * node[2] + Q6_I(Q6_CBUF(), 0x5c) + node[0]);
    zp = (unsigned short *)(Q6_I(Q6_I(c4, 0x10), 0x18) * node[2] + Q6_I(Q6_I(c4, 0x10), 0x5c) + node[0] * 2);
    for (n = node[1]; n != 0; n--) {
        unsigned tx = q6_rtexel(u, v);
        if (tx) {
            if (bpp16)
                *d16 = (unsigned short)q6_rpix(mode, tx, l);
            else
                *d8 = (unsigned char)q6_rpix(mode, tx, l);
            *zp = (unsigned short)(z >> (sh & 31));
        }
        z += dz;
        u += node[4];
        v += node[6];
        l += node[9];
        if (bpp16)
            d16++;
        else
            d8++;
        zp++;
    }
}

/* OVERRIDES: rdAFRaster_DrawSpanNGonMLAT_8 */
void rdAFRaster_DrawSpanNGonMLAT_8(int *node) { q6_spanr(node, 0, Q6R_TEX); }
/* OVERRIDES: rdAFRaster_DrawSpanNGonMLAT_16 */
void rdAFRaster_DrawSpanNGonMLAT_16(int *node) { q6_spanr(node, 1, Q6R_PAL); }
/* OVERRIDES: rdAFRaster_DrawSpanNGonMFAT_8 */
void rdAFRaster_DrawSpanNGonMFAT_8(int *node) { q6_spanr(node, 0, Q6R_SHADE); }
/* OVERRIDES: rdAFRaster_DrawSpanNGonMFAT_16 */
void rdAFRaster_DrawSpanNGonMFAT_16(int *node) { q6_spanr(node, 1, Q6R_PAL); }
/* OVERRIDES: rdAFRaster_DrawSpanNGonMGAT_8 */
void rdAFRaster_DrawSpanNGonMGAT_8(int *node) { q6_spanr(node, 0, Q6R_SHADE_L); }
/* OVERRIDES: rdAFRaster_DrawSpanNGonMGAT_16 */
void rdAFRaster_DrawSpanNGonMGAT_16(int *node) { q6_spanr(node, 1, Q6R_PAL_L); }

/* ==== SpanP8/16_TexKeyZw, _2, _3: one perspective keyed span node of the span-list renderer ====
 * Node: +0 x, +4 count, +8 row, +0xc U, +0x10 V, +0x1c W (the plane values at the first pixel), +0x20 / +0x24 light
 * and step (_3).  The runs as the edge walker's spans (head 16 - (x & 15), at most count; runs of 16; tail; 1/n
 * table for the head and tail steps), with the gradients UINT_008ddf1c / f20 / f38, the 16-pixel steps f28 / f2c / f48,
 * the mip shift f04 and the u / v biases f44 / f18.  The control word: DAT_00900528 (truncate, 24 bits) is loaded
 * first, so only z = floor(float(W * 65536)) is computed in that mode; its conversion loads the default word.  z is
 * stepped by f24; a non-zero texel is drawn with its z >> (canvas +0x14) (no depth test).  Without a head a single
 * tail pixel uses the bits of the z-buffer pointer (or, in SpanP16_TexKeyZw and _2, of the colour pointer) as u and v
 * (the registers the original leaves holding them). */
static void q6_spanp(int *node, int bpp16, int mode, int nohead_colour)
{
    char *c4 = Q6_C4();
    int sh = Q6_I(c4, 0x14), m, head, rest, runs, tail, t, n = node[1], z, dz, l = node[8], dl = node[9];
    int u = 0, du = 0, v = 0, dv = 0, k;
    long double r, h;
    float p0, p1, p2, u0, v0, u1, v1, inv;
    unsigned char *d8 = 0;
    unsigned short *d16 = 0, *zp;
    q6_fldcw(&DAT_00900528);
    m = node[0] & 0xf;
    if (m) {
        head = 16 - m;
        if (n < head)
            head = n;
    } else
        head = 0;
    rest = n - head;
    if (rest) {
        runs = rest / 16;
        tail = rest % 16;
        if (!tail) {
            runs--;
            tail = 16;
        }
    } else
        runs = tail = 0;
    q6_u32(p0) = node[7];
    q6_u32(p1) = node[3];
    q6_u32(p2) = node[4];
    z = q6_floor_i(q6_f(p0 * 65536.0L));
    r = 1.0L / p0;
    dz = g_dwRdAFRaster_dOneOverZdXFixed;
    if (bpp16)
        d16 = (unsigned short *)(Q6_I(Q6_CBUF(), 0x5c) + (((unsigned)Q6_I(Q6_CBUF(), 0x18) >> 1) * node[2] + node[0]) * 2);
    else
        d8 = (unsigned char *)(Q6_I(Q6_CBUF(), 0x18) * node[2] + Q6_I(Q6_CBUF(), 0x5c) + node[0]);
    zp = (unsigned short *)(Q6_I(Q6_I(c4, 0x10), 0x18) * node[2] + Q6_I(Q6_I(c4, 0x10), 0x5c) + node[0] * 2);
    u0 = q6_f(r * p1);
    v0 = q6_f(r * p2);
#define Q6_SPANP_PIXELS(count)                                                                                \
    for (k = (count); k > 0; k--) {                                                                         \
        unsigned tx = q6_rtexel(u, v);                                                                      \
        if (tx) {                                                                                           \
            if (bpp16)                                                                                      \
                *d16 = (unsigned short)q6_rpix(mode, tx, l);                                                \
            else                                                                                            \
                *d8 = (unsigned char)q6_rpix(mode, tx, l);                                                  \
            *zp = (unsigned short)(z >> (sh & 31));                                                         \
        }                                                                                                   \
        zp++;                                                                                               \
        if (bpp16)                                                                                          \
            d16++;                                                                                          \
        else                                                                                                \
            d8++;                                                                                           \
        u += du;                                                                                            \
        z += dz;                                                                                            \
        v += dv;                                                                                            \
        l += dl;                                                                                            \
    }
#define Q6_SPANP_START()                                                                                      \
    u = (q6_floor_i(q6_f(u0 * 65536.0L)) >> (g_dwRdAFRaster_mipMapNum & 31)) + g_dwRdAFRaster_dUdXModifier;                          \
    v = (q6_floor_i(q6_f(v0 * 65536.0L)) >> (g_dwRdAFRaster_mipMapNum & 31)) + g_dwRdAFRaster_dVdXModifier
    if (head) {
        h = head;
        inv = q6_copy(g_dwRdRaster_aOneOverNFlex[head]);
        p0 = q6_f(h * g_dwRdAFRaster_dOneOverZdX + p0);
        p1 = q6_f(h * g_dwRdAFRaster_dUOverZdX + p1);
        p2 = q6_f(h * g_dwRdAFRaster_dVOverZdX + p2);
        r = 1.0L / p0;
        u1 = q6_f(r * p1);
        v1 = q6_f(r * p2);
        du = q6_floor_i(q6_f(((long double)u1 - u0) * inv * 65536.0f)) >> (g_dwRdAFRaster_mipMapNum & 31);
        dv = q6_floor_i(q6_f(((long double)v1 - v0) * inv * 65536.0f)) >> (g_dwRdAFRaster_mipMapNum & 31);
        Q6_SPANP_START();
        Q6_SPANP_PIXELS(head)
        p0 = q6_f((long double)p0 + g_dwRdAFRaster_oneOverZStep);
        u0 = u1;
        v0 = v1;
        p1 = q6_f((long double)p1 + g_dwRdAFRaster_uOverZStep);
        p2 = q6_f((long double)p2 + g_dwRdAFRaster_vOverZStep);
    } else {
        p0 = q6_f((long double)p0 + g_dwRdAFRaster_oneOverZStep);
        u = v = nohead_colour ? (int)d16 : (int)zp;
        p1 = q6_f((long double)p1 + g_dwRdAFRaster_uOverZStep);
        p2 = q6_f((long double)p2 + g_dwRdAFRaster_vOverZStep);
    }
    for (; runs > 0; runs--) {
        r = 1.0L / p0;
        u1 = q6_f(r * p1);
        v1 = q6_f(r * p2);
        du = q6_floor_i(q6_f(((long double)u1 - u0) * 0.0625f * 65536.0f)) >> (g_dwRdAFRaster_mipMapNum & 31);
        dv = q6_floor_i(q6_f(((long double)v1 - v0) * 0.0625f * 65536.0f)) >> (g_dwRdAFRaster_mipMapNum & 31);
        Q6_SPANP_START();
        Q6_SPANP_PIXELS(16)
        p0 = q6_f((long double)p0 + g_dwRdAFRaster_oneOverZStep);
        u0 = u1;
        v0 = v1;
        p1 = q6_f((long double)p1 + g_dwRdAFRaster_uOverZStep);
        p2 = q6_f((long double)p2 + g_dwRdAFRaster_vOverZStep);
    }
    if (tail) {
        t = tail - 1;
        if (t) {
            h = t;
            inv = q6_copy(g_dwRdRaster_aOneOverNFlex[t]);
            r = 1.0L / (h * g_dwRdAFRaster_dOneOverZdX - g_dwRdAFRaster_oneOverZStep + p0);
            u1 = q6_f((h * g_dwRdAFRaster_dUOverZdX - g_dwRdAFRaster_uOverZStep + p1) * r);
            v1 = q6_f((h * g_dwRdAFRaster_dVOverZdX - g_dwRdAFRaster_vOverZStep + p2) * r);
            du = q6_floor_i(q6_f(((long double)u1 - u0) * inv * 65536.0f)) >> (g_dwRdAFRaster_mipMapNum & 31);
            dv = q6_floor_i(q6_f(((long double)v1 - v0) * inv * 65536.0f)) >> (g_dwRdAFRaster_mipMapNum & 31);
            Q6_SPANP_START();
        }
        Q6_SPANP_PIXELS(t + 1)
    }
#undef Q6_SPANP_PIXELS
#undef Q6_SPANP_START
    q6_fldcw(&DAT_00900524);
}

/* OVERRIDES: rdAFRaster_DrawSpanNGonMLIT_8 */
void rdAFRaster_DrawSpanNGonMLIT_8(int *node) { q6_spanp(node, 0, Q6R_TEX, 0); }
/* OVERRIDES: rdAFRaster_DrawSpanNGonMLIT_16 */
void rdAFRaster_DrawSpanNGonMLIT_16(int *node) { q6_spanp(node, 1, Q6R_PAL, 1); }
/* OVERRIDES: rdAFRaster_DrawSpanNGonMFIT_8 */
void rdAFRaster_DrawSpanNGonMFIT_8(int *node) { q6_spanp(node, 0, Q6R_SHADE, 0); }
/* OVERRIDES: rdAFRaster_DrawSpanNGonMFIT_16 */
void rdAFRaster_DrawSpanNGonMFIT_16(int *node) { q6_spanp(node, 1, Q6R_PAL, 1); }
/* OVERRIDES: rdAFRaster_DrawSpanNGonMGIT_8 */
void rdAFRaster_DrawSpanNGonMGIT_8(int *node) { q6_spanp(node, 0, Q6R_SHADE_L, 0); }
/* OVERRIDES: rdAFRaster_DrawSpanNGonMGIT_16 */
void rdAFRaster_DrawSpanNGonMGIT_16(int *node) { q6_spanp(node, 1, Q6R_PAL_L, 0); }

#endif /* GRIM_EXE */
