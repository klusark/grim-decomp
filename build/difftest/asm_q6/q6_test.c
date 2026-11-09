/* Differential test of build/overrides_asm_q6.c (the non-z-buffered software rasteriser) against the original machine
 * code (agent q6; modelled on build/difftest/asm_q4/raster_test.c).
 *
 * Each case builds a random rasteriser state (canvas with an 8 or 16 bpp colour buffer with random contents, light /
 * palette / translucency tables, textures, vertex / uv / light arrays, edge records, a polygon record, span nodes of
 * the span-list renderer, the rasteriser globals), runs the original function (orig_<name>, sliced from the assembly
 * of 2df265d; it calls the original versions of the other q6 functions) on one copy and the C (which calls the C
 * ones) on another, and compares: the return value, the arena (colour buffer with margins, edge records, polygon
 * records, span nodes), the rasteriser globals 0x007f4200..0x007f4600 and 0x008dde40..0x008ddf60 (function pointers
 * orig_X mapped to X), the calls of rdCanvas_DrawLine (stand-in that logs), the x87 control word and stack top.
 * The x87 precision control rotates through 24, 53 and 64 bits; the control words the original loads
 * (0x00900524 default, 0x00900526 floor, 0x00900528 truncate / 24 bits, 0x0090052a ceil) are set from it as
 * Services_SetCurrent does.
 *
 * usage: q6_test.exe [cases per function] [function name filter: a substring, or =name]
 * Q6_SEED=n: another random sequence; Q6_NOSPECIAL=1: no NaN / inf / huge attribute values. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stddef.h>
#include <windows.h>

extern char sect_data[] __asm__("_sect_data");
#define G(a) ((void *)(sect_data + ((a) - 0x4dd000)))
#define GI(a) (*(int *)G(a))
#define GF(a) (*(float *)G(a))
#define GP(a) (*(void **)G(a))

/* ---- random numbers ---- */
static uint64_t seed = 0x9e3779b97f4a7c15ull;
static uint32_t rnd(void)
{
    seed ^= seed << 13; seed ^= seed >> 7; seed ^= seed << 17;
    return (uint32_t)(seed >> 11);
}
static int rn(int n) { return n > 0 ? (int)(rnd() % (unsigned)n) : 0; }
static float rf(float lo, float hi) { float f = lo + (hi - lo) * (float)(rnd() / 4294967296.0); return f < hi ? f : lo; }
static float fbits(uint32_t b) { float f; memcpy(&f, &b, 4); return f; }

/* a coordinate in [lo, hi): uniform, an integer, a half, or a neighbour of an integer */
static float rcoord(float lo, float hi)
{
    float f = rf(lo, hi);
    switch (rn(8)) {
    case 0: return floorf(f);
    case 1: return floorf(f) + 0.5f;
    case 2: return nextafterf(floorf(f), 1e9f);
    case 3: return nextafterf(floorf(f), -1e9f);
    default: return f;
    }
}

static int specials = 1;
static float rspecial(void)
{
    static const uint32_t sp[] = {0x00000000, 0x80000000, 0x7f800000, 0xff800000, 0x7fc00000, 0xffc00000,
                                  0x7fc12345, 0x7f812345, 0x00000001, 0x80000001, 0x007fffff, 0x7f7fffff, 0xff7fffff,
                                  0x4f000000, 0xcf000000, 0x3f800000, 0xbf800000, 0x47000000, 0xc7000000};
    return fbits(sp[rn(sizeof sp / 4)]);
}
/* an attribute value: usually in range, sometimes special */
static float rattr(float lo, float hi)
{
    if (specials && rn(64) == 0)
        return rspecial();
    if (rn(16) == 0)
        return rcoord(-1e6f, 1e6f);
    return rcoord(lo, hi);
}

/* ---- stand-ins ---- */
#define MAXLOG 64
static uint32_t dl_log[MAXLOG][7];
static int dl_n;
void rdCanvas_DrawLine(void *c, int x0, int y0, int x1, int y1, uint32_t colour, uint32_t pat)
{
    if (dl_n < MAXLOG) {
        uint32_t *l = dl_log[dl_n];
        l[0] = (uint32_t)c; l[1] = x0; l[2] = y0; l[3] = x1; l[4] = y1; l[5] = colour; l[6] = pat;
    }
    dl_n++;
}
void Mem_DumpLog(void) {}

/* ---- the state ---- */
#define MAXW 96
#define MAXH 48
#define MARGIN 4096
#define CBYTES (MARGIN * 2 + (MAXH + 4) * (MAXW * 2 + 16))
#define MAXV 12
typedef struct {
    unsigned char cbuf[CBYTES];
    unsigned char gap[0x12345];     /* (not saved) keeps the z-buffer far from the colour buffer: pointer bits used as u / v differ */
    unsigned char zbuf[CBYTES];
    int e1[0x11], e2[0x11];
    unsigned char poly[0x100];
    unsigned char rec[0x400];       /* the span-list renderer's polygon record */
    unsigned char nodes[16][0x40];  /* span nodes */
} arena_t;
static arena_t A;
static unsigned char cam[64], c4[64], cdesc[0x80], zdesc[0x80];
/* lut44: the 16 bpp -> index table; 16 MB because Span16_Tex_13 / _15 index it with a colour times 256 */
static unsigned char tbl8[64 * 256 + 512], lut44[0x1000000 + 0x10000], blend[65536 + 512], colormap[0x400];
static unsigned short pal16_store[512 + 0x8000 + 1024];
#define pal16 (pal16_store + 512)
static unsigned char texrec[0x40], levrec[4][0x60], texels[4][65536 + 256];
static unsigned char tables[0x400];
static unsigned char mat[0x40];
static float verts[MAXV * 3], uvs[MAXV * 2], lights[MAXV];
static unsigned char texel_cell[16];
static int W, H, BPP, NV, convex, top, bot, sel_mode, es_i0, es_i1;

static void setup_canvas(void)
{
    W = 1 + rn(MAXW);
    H = 1 + rn(MAXH);
    BPP = rn(16) == 0 ? 24 : (rn(2) ? 8 : 16);
    int pitch = W * (BPP == 8 ? 1 : 2) + rn(9);
    for (int i = 0; i < CBYTES / 4; i++) ((uint32_t *)A.cbuf)[i] = rnd();
    memset(cam, 0, sizeof cam); memset(c4, 0, sizeof c4);
    *(void **)(cam + 4) = c4;
    *(void **)(c4 + 4) = cdesc;
    *(int *)(cdesc + 0x18) = pitch;
    *(int *)(cdesc + 0x24) = BPP;
    *(void **)(cdesc + 0x5c) = A.cbuf + MARGIN;
    for (int i = 0; i < CBYTES / 4; i++) ((uint32_t *)A.zbuf)[i] = rnd();
    *(void **)(c4 + 0x10) = zdesc;
    *(int *)(c4 + 0x14) = rn(3) == 0 ? 0 : rn(4) == 0 ? rn(33) : (rn(2) ? 16 : 8);
    *(int *)(zdesc + 0x18) = W * 2 + rn(5) * 2;
    *(void **)(zdesc + 0x5c) = A.zbuf + MARGIN;
    *(void **)G(0x7f0fc8) = cam;
}

static void setup_big_tables(void)
{
    for (unsigned i = 0; i < sizeof tbl8; i++) tbl8[i] = rnd();
    for (unsigned i = 0; i < sizeof pal16_store / 2; i++) pal16_store[i] = rnd();
    for (int k = 0; k < 4; k++)
        for (unsigned i = 0; i < sizeof texels[k]; i++) texels[k][i] = rn(4) ? rnd() : 0;
    static int lut_done;
    for (unsigned i = 0; i < (lut_done ? 65536u : sizeof lut44); i++) lut44[i] = rnd();
    lut_done = 1;
    for (unsigned i = 0; i < sizeof blend; i++) blend[i] = rnd();
    *(void **)(tables + 0x330) = tbl8;
    *(void **)(tables + 0x348) = pal16;
    *(void **)(tables + 0x34c) = lut44;
    *(void **)(colormap + 0x338) = blend;
    GP(0x4f5ec4) = colormap;
    /* the span length tables (filled at run time by the game: 65536 / n and 1.0f / n); sometimes perturbed */
    for (int n = 0; n < 1024; n++) {
        int ri = n ? 65536 / n : 0;
        float rfv = n ? 1.0f / n : 0.0f;
        if (rn(32) == 0) { ri += rn(5) - 2; rfv = nextafterf(rfv, rn(2) ? 1 : -1); }
        if (rn(64) == 0) rfv = rf(0.0f, 2.0f);
        ((int *)G(0x8fbfc0))[n] = ri;
        ((float *)G(0x8fe000))[n] = rfv;
    }
}

static long ncase;
/* texture record (material +0x1c): +0xc log2 width, +0x10 width mask, +0x14 height mask, +0x18 mip count,
 * +0x1c.. level records (+0x18 width, +0x5c texels) */
static void setup_texture(void)
{
    static const int widths[] = {4, 8, 16, 32, 64, 128, 256, 1, 2, 3, 100, 512};
    int k = 3 + rn(6), m = rn(9);
    if (k + m > 16) m = 16 - k;
    memset(texrec, 0, sizeof texrec);
    *(int *)(texrec + 0xc) = k;
    *(int *)(texrec + 0x10) = (1 << k) - 1;
    *(int *)(texrec + 0x14) = (1 << m) - 1;
    *(int *)(texrec + 0x18) = rn(8) ? 1 + rn(4) : rn(7) - 1;
    for (int i = 0; i < 4; i++) {
        *(void **)(texrec + 0x1c + 4 * i) = levrec[i];
        *(int *)(levrec[i] + 0x18) = rn(4) ? widths[rn(7)] : widths[rn(12)];
        *(void **)(levrec[i] + 0x5c) = texels[i];
    }
}

/* the edge walker's globals (0x007f42xx .. 0x007f44xx, 0x008ddeax .. 0x008ddf0x): random, pointers valid */
static void setup_globals_b(void)
{
    for (int a = 0x7f4200; a < 0x7f4600; a += 4) GI(a) = rnd();
    for (int a = 0x8dde40; a < 0x8ddf60; a += 4) GI(a) = rnd();
    GP(0x7f4308) = verts;
    GP(0x7f4398) = uvs;
    GP(0x7f4304) = lights;
    GI(0x7f424c) = NV;
    GI(0x7f42e8) = rn(NV);
    GI(0x7f42fc) = rn(NV);
    int d = rn(2) ? 1 : -1;
    GI(0x7f42ec) = d;
    GI(0x7f4394) = -d;
    for (int i = 0; i < 16; i++) texel_cell[i] = rnd();
    GP(0x7f4300) = texel_cell + rn(16);
    GP(0x7f43a8) = A.cbuf + rn(CBYTES);
    GP(0x8ddea8) = blend;
    GP(0x8ddeb0) = tbl8;
    GP(0x8ddebc) = pal16 + (rn(2) ? 0x3f00 : 0);
    GP(0x8dded4) = lut44;
    GI(0x8ddec0) = rnd();
    /* texture state of the perspective spans (as the drivers set it after Grad_*) */
    int k = *(int *)(texrec + 0xc), mip = rn(4);
    int m = 0;
    while ((1 << m) - 1 < *(int *)(texrec + 0x14)) m++;
    GI(0x8ddee4) = mip;
    GI(0x8dded8) = k - mip;
    GI(0x8ddecc) = (((1 << k) - 1) >> mip) << 16;
    GI(0x8ddefc) = ((((1 << m) - 1) >> mip) << ((k - mip) & 31));
    GP(0x8ddee8) = texels[mip];
    GI(0x8ddeac) = rn(2) ? 0x8000 : 0x7fff;
    GI(0x8ddef8) = rn(2) ? 0x8000 : 0x7fff;
    GI(0x7f4250) = rn(6) - 1;
}

/* a polygon: n vertices, screen x in [1, W + 1), y in [0, H) (finite: the drivers draw them); edge tests also get
 * special values */
static void setup_verts(int special_xy)
{
    NV = 1 + rn(MAXV);
    if (rn(4)) NV = 3 + rn(6);
    for (int i = 0; i < NV; i++) {
        verts[i * 3] = rcoord(1.0f, W + 1.0f);
        verts[i * 3 + 1] = rcoord(0.0f, (float)H);
        verts[i * 3 + 2] = rattr(0.0f, 20.0f);
        if (special_xy && rn(32) == 0) verts[i * 3 + rn(2)] = rattr(-100.0f, 100.0f);
        uvs[i * 2] = rattr(-4.0f, 300.0f);
        uvs[i * 2 + 1] = rattr(-4.0f, 300.0f);
        lights[i] = rattr(0.0f, 63.99f);
        if (i && rn(6) == 0) verts[i * 3 + 1] = verts[(i - 1) * 3 + 1];   /* horizontal edge */
        if (i && rn(10) == 0) verts[i * 3] = verts[(i - 1) * 3];         /* vertical edge */
    }
    /* half of the polygons convex (angles sorted around a centre inside the canvas), with their real top / bottom */
    convex = !special_xy && NV >= 3 && rn(2);
    if (convex) {
        float cx = rf(1.0f, W + 1.0f), cy = rf(0.0f, (float)H), ang[MAXV];
        for (int i = 0; i < NV; i++) ang[i] = rf(0.0f, 6.2831853f);
        for (int i = 1; i < NV; i++)
            for (int j = i; j > 0 && ang[j] < ang[j - 1]; j--) { float t = ang[j]; ang[j] = ang[j - 1]; ang[j - 1] = t; }
        if (rn(2)) for (int i = 0; i < NV / 2; i++) { float t = ang[i]; ang[i] = ang[NV - 1 - i]; ang[NV - 1 - i] = t; }
        for (int i = 0; i < NV; i++) {
            float x = cx + cosf(ang[i]) * cx, y = cy + sinf(ang[i]) * cy;
            if (rn(3) == 0) { x = floorf(x) + (rn(2) ? 0.5f : 0.0f); y = floorf(y); }
            verts[i * 3] = fminf(fmaxf(x, 1.0f), (float)W);
            verts[i * 3 + 1] = fminf(fmaxf(y, 0.0f), (float)H - 0.01f);
        }
        top = bot = 0;
        for (int i = 1; i < NV; i++) {
            if (verts[i * 3 + 1] < verts[top * 3 + 1]) top = i;
            if (verts[i * 3 + 1] > verts[bot * 3 + 1]) bot = i;
        }
    }
}

static void setup_poly(void)
{
    unsigned char *poly = A.poly;
    memset(poly, 0, sizeof A.poly);
    *(int *)(poly + 0x1c) = NV;
    *(void **)(poly + 0x20) = verts;
    *(void **)(poly + 0x24) = uvs;
    *(void **)(poly + 0x28) = lights;
    *(void **)(poly + 0x4c) = tables;
    *(int *)(poly + 0x50) = rn(2);
    if (convex && rn(4)) {   /* the winding that puts edge A (step +1 when 0) on the left */
        int nx = (top + 1) % NV, px = (top + NV - 1) % NV;
        *(int *)(poly + 0x50) = verts[nx * 3] < verts[px * 3] ? 0 : 1;
    }
    *(int *)(poly + 0x6c) = convex ? top : rn(NV);
    *(int *)(poly + 0x70) = convex ? bot : rn(NV);
    for (unsigned i = 0; i < sizeof mat; i++) mat[i] = rnd();
    *(int *)(mat + 4) = rn(256);
    *(void **)(mat + 0x1c) = texrec;
    *(float *)(poly + 0x64) = rn(16) ? rf(0.0f, 60.0f) : rattr(0.0f, 60.0f);
    if (rn(8) == 0) *(float *)(poly + 0x64) = (float)(rn(5) * 10);
}

static void rand_edge(int *e)
{
    for (int i = 0; i < 0x11; i++) e[i] = rnd();
    e[3] = rn(NV);
}
/* an edge record as a span sees it: x in [0, W + 1) pixels (16.16), y in [0, H) */
static void rand_span_edge(int *e)
{
    rand_edge(e);
    e[0] = (int)(rf(0.0f, W + 1.0f) * 65536.0f);
    if (rn(6) == 0) e[0] &= ~0xffff;
    e[0x10] = rn(H);
}

/* ---- snapshot / compare ---- */
#define R1 0x7f4200
#define R1N 0x400
#define R2 0x8dde40
#define R2N 0x120
typedef struct {
    unsigned char g1[R1N], g2[R2N];
    arena_t a;
    uint32_t dl[MAXLOG][7];
    int dln;
    int ret;
    unsigned cw, sw;
} snap;
static snap s_in, s_orig, s_c;

static void save(snap *s)
{
    memcpy(s->g1, G(R1), R1N); memcpy(s->g2, G(R2), R2N);
    memcpy(&s->a, &A, offsetof(arena_t, gap)); memcpy(s->a.zbuf, A.zbuf, sizeof A - offsetof(arena_t, zbuf));
    memcpy(s->dl, dl_log, sizeof dl_log); s->dln = dl_n;
}
static void restore(const snap *s)
{
    memcpy(G(R1), s->g1, R1N); memcpy(G(R2), s->g2, R2N);
    memcpy(&A, &s->a, offsetof(arena_t, gap)); memcpy(A.zbuf, s->a.zbuf, sizeof A - offsetof(arena_t, zbuf));
    dl_n = 0;
    memset(dl_log, 0, sizeof dl_log);
}

/* ---- the functions ---- */
enum { K_DRAW, K_DRAWL, K_EDGE, K_SPAN, K_GRAD, K_PSPAN, K_PDRAW, K_SETUP, K_SEL, K_SELL, K_SELR, K_ESETUP, K_SPANR, K_SPANP };
typedef struct { const char *name; int kind; void *orig, *c; } fn;
#define FN(kind, n) extern void orig_rdRaster_##n(void), rdRaster_##n(void);
#include "q6_funcs.h"
#undef FN
static const fn fns[] = {
#define FN(kind, n) {#n, kind, (void *)orig_rdRaster_##n, (void *)rdRaster_##n},
#include "q6_funcs.h"
#undef FN
};
#define NFN (sizeof fns / sizeof fns[0])

static void *map_orig(void *p)
{
    for (unsigned i = 0; i < NFN; i++)
        if (p == fns[i].orig) return fns[i].c;
    return p;
}

static unsigned short cws[3] = {0x007f, 0x027f, 0x037f};

static int __attribute__((noinline)) call(const fn *f, int which, unsigned cw, unsigned *cw_out, unsigned *sw_out)
{
    void *p = which ? f->c : f->orig;
    unsigned short c = cw, co, so;
    int r = 0;
    *(unsigned short *)G(0x900524) = c;
    *(unsigned short *)G(0x900526) = (c & 0xff) | 0x0700;
    *(unsigned short *)G(0x900528) = (c & 0xff) | 0x0c00;
    *(unsigned short *)G(0x90052a) = (c & 0xff) | 0x0b00;
    __asm__ volatile("fninit; fldcw %0" : : "m"(c));
    switch (f->kind) {
    case K_DRAW: case K_PDRAW: ((void (*)(void *, void *))p)(A.poly, mat); break;
    case K_DRAWL: ((void (*)(void *, void *, float))p)(A.poly, mat, *(float *)(A.poly + 0xf0)); break;
    case K_EDGE: r = ((int (*)(int *))p)(A.e1); break;
    case K_SPAN: case K_PSPAN: ((void (*)(int *, int *))p)(A.e1, A.e2); break;
    case K_GRAD: ((void (*)(int))p)(*(int *)(A.poly + 0x64)); break;
    case K_SETUP: ((void (*)(void *, int))p)(A.rec, sel_mode); break;
    case K_SEL: ((void (*)(void *, void *))p)(A.rec, mat); break;
    case K_SELR: r = ((int (*)(void *, void *))p)(A.rec, mat); break;
    case K_SELL: ((void (*)(void *, void *, float))p)(A.rec, mat, *(float *)(A.poly + 0xf0)); break;
    case K_ESETUP: r = ((int (*)(void *, void *, int, int))p)(A.nodes[0], A.rec, es_i0, es_i1); break;
    case K_SPANR: case K_SPANP: ((void (*)(void *))p)(A.nodes[0]); break;
    }
    __asm__ volatile("fnstcw %0; fnstsw %1" : "=m"(co), "=m"(so));
    *cw_out = co; *sw_out = (so >> 11) & 7;
    return r;
}

static long fails;
static void diff(const fn *f, long i, const char *what, long off)
{
    if (fails++ < 30)
        printf("DIFF %s case %ld: %s at +0x%lx\n", f->name, i, what, off);
}

static void cmpbytes(const fn *f, long i, const char *what, const void *a, const void *b, int n, long base)
{
    if (memcmp(a, b, n))
        for (int k = 0; k < n; k++)
            if (((const unsigned char *)a)[k] != ((const unsigned char *)b)[k]) { diff(f, i, what, base + k); break; }
}

static void compare(const fn *f, long i)
{
    if (s_orig.ret != s_c.ret) diff(f, i, "return", 0);
    if (s_orig.cw != s_c.cw) diff(f, i, "control word", s_orig.cw);
    if (s_orig.sw != s_c.sw) diff(f, i, "x87 stack top", s_orig.sw);
    if (s_orig.dln != s_c.dln) diff(f, i, "DrawLine call count", s_orig.dln);
    cmpbytes(f, i, "DrawLine log", s_orig.dl, s_c.dl, sizeof s_orig.dl, 0);
    /* function pointers stored by the originals: orig_X -> X */
    /* (a word is taken as equal when the original stored orig_X where the C stored X) */
#define MAPW(sn, fld, k) if (*(void **)(sn.fld + k) != *(void **)(s_c.fld + k) && map_orig(*(void **)(sn.fld + k)) == *(void **)(s_c.fld + k)) *(void **)(sn.fld + k) = *(void **)(s_c.fld + k)
    for (int k = 0; k + 4 <= R1N; k += 4) MAPW(s_orig, g1, k);
    for (int k = 0; k + 4 <= R2N; k += 4) MAPW(s_orig, g2, k);
    for (int k = 0; k + 4 <= (int)sizeof s_orig.a.rec; k += 4) MAPW(s_orig, a.rec, k);
    cmpbytes(f, i, "globals 0x7f42xx", s_orig.g1, s_c.g1, R1N, R1);
    if (getenv("Q6_CASE"))
        for (int k = 0; k < R1N; k += 4)
            if (*(int *)(s_orig.g1 + k) != *(int *)(s_c.g1 + k))
                printf("  %x: orig %08x C %08x (in %08x)\n", R1 + k, *(int *)(s_orig.g1 + k), *(int *)(s_c.g1 + k),
                       *(int *)(s_in.g1 + k));
    cmpbytes(f, i, "globals 0x8ddexx", s_orig.g2, s_c.g2, R2N, R2);
    cmpbytes(f, i, "colour buffer", s_orig.a.cbuf, s_c.a.cbuf, CBYTES, -MARGIN);
    cmpbytes(f, i, "z-buffer", s_orig.a.zbuf, s_c.a.zbuf, CBYTES, -MARGIN);
    cmpbytes(f, i, "edge 1", s_orig.a.e1, s_c.a.e1, sizeof A.e1, 0);
    cmpbytes(f, i, "edge 2", s_orig.a.e2, s_c.a.e2, sizeof A.e2, 0);
    cmpbytes(f, i, "polygon", s_orig.a.poly, s_c.a.poly, sizeof A.poly, 0);
    cmpbytes(f, i, "record", s_orig.a.rec, s_c.a.rec, sizeof A.rec, 0);
    cmpbytes(f, i, "nodes", s_orig.a.nodes, s_c.a.nodes, sizeof A.nodes, 0);
}

/* the perspective spans: plane values 1/z, u/z, v/z at the left edge (e[4], e[6], e[8]), their x gradients and
 * 16-pixel steps (usually 16 * gradient), light e[14] on both edges; sometimes special values, a span start on a
 * multiple of 16, a negative start (heads of 17 .. 31 pixels) */
static float pspecial(float f) { return (specials && rn(48) == 0) ? rspecial() : f; }
static void setup_pspan(void)
{
    int *L = A.e1, *R = A.e2;
    float w = rf(0.05f, 2.0f), u = rf(-50.0f, 300.0f), v = rf(-50.0f, 300.0f);
    float gw = rf(-1.0f, 1.0f) * w / (rn(2) ? 100.0f : 1000.0f);
    float gu = rf(-8.0f, 8.0f) * w, gv = rf(-8.0f, 8.0f) * w;
    if (rn(3) == 0) {   /* large texture coordinates: a 1-ulp difference of u or v moves the texel */
        float k = rf(100.0f, 30000.0f);
        u *= k; v *= k; gu *= k; gv *= k;
    }
    if (rn(8) == 0) gw = 0.0f;
    ((float *)L)[4] = pspecial(w);
    ((float *)L)[6] = pspecial(u * w);
    ((float *)L)[8] = pspecial(v * w);
    GF(0x8ddef4) = pspecial(gw);
    GF(0x8ddec8) = pspecial(gu);
    GF(0x8ddedc) = pspecial(gv);
    GF(0x8ddeec) = rn(8) ? GF(0x8ddef4) * 16.0f : pspecial(rf(-0.1f, 0.1f));
    GF(0x8dded0) = rn(8) ? GF(0x8ddec8) * 16.0f : pspecial(rf(-100.0f, 100.0f));
    GF(0x8ddf00) = rn(8) ? GF(0x8ddedc) * 16.0f : pspecial(rf(-100.0f, 100.0f));
    if (rn(4) == 0) L[0] = (L[0] & 0xffff) | ((rn(7) * 16) << 16);          /* xl on a multiple of 16 */
    if (rn(4) == 0) L[0] &= ~0xffff;
    if (rn(16) == 0) L[0] = -(int)(rf(0.0f, 3.0f) * 65536.0f);            /* negative start */
    if (rn(3) == 0) R[0] = L[0] + (int)(rf(0.0f, 40.0f) * 65536.0f);
    if (rn(8) == 0) R[0] = (L[0] & ~0xffff) + (rn(3) << 16) + rn(2);       /* 0 .. 3 pixels */
    L[14] = (int)(rf(0.0f, 63.99f) * 65536.0f);
    R[14] = (int)(rf(0.0f, 63.99f) * 65536.0f);
    if (rn(16) == 0) R[14] = rnd();
    if (rn(4) == 0) {   /* a small negative light step (the clamp range -1309 .. -1 and around it) */
        int n = ((R[0] + 0xffff) >> 16) - ((L[0] + 0xffff) >> 16);
        R[14] = L[14] + (rn(1600) - 1450) * (n > 0 ? n : 1);
    }
}

/* Grad_*: when the vertex next to the top is the bottom, the third vertex starts as the argument's bits (Grad_Flat) or
 * an uninitialised stack slot (Grad_Flat_2) and only a vertex whose x differs from the top / bottom midpoint replaces
 * it; the original would index with those bits otherwise (the game's polygons never get there), so such polygons are
 * not generated.  Conservative: some vertex between must be clearly away from the midpoint. */
static int wrapi(int n) { if (n < 0) return NV - 1; return n > NV - 1 ? 0 : n; }
static int grad_safe(int start, int end)
{
    int dir;
    if (NV == 3) return 1;
    if (NV < 3) return 0;
    if (wrapi(start + 1) == end) dir = -1;
    else if (wrapi(start - 1) == end) dir = 1;
    else return 1;
    long double mid = ((long double)verts[start * 3] + verts[end * 3]) * 0.5L;
    for (int k = wrapi(start + dir); k != end; k = wrapi(k + dir)) {
        long double d = fabsl((long double)verts[k * 3] - mid);
        if (d > 1e-5L * (fabsl(mid) + 1.0L)) return 1;
    }
    return 0;
}

/* the span-list renderer: the polygon record (rec[0] the polygon, per-vertex W / U / V, gradients), a span node */

static void setup_rec(void)
{
    int *rec = (int *)A.rec;
    for (int i = 0; i < 0x100; i++) rec[i] = rnd();
    rec[0] = (int)A.poly;
    for (int i = 0; i < 0x60; i++) ((float *)rec)[1 + i] = rattr(-2.0f, 2.0f);
    for (int i = 0; i < NV; i++) {
        float w = rf(0.05f, 2.0f);
        ((float *)rec)[1 + i] = rn(32) ? w : rattr(0.0f, 1.0f);
        ((float *)rec)[0x21 + i] = rattr(-50.0f, 300.0f) * w;
        ((float *)rec)[0x41 + i] = rattr(-50.0f, 300.0f) * w;
    }
    for (int i = 0x61; i <= 0x66; i++) ((float *)rec)[i] = rattr(-8.0f, 8.0f);
    rec[0x70] = rn(4);
    sel_mode = rn(6) - 1;
}
static void setup_spanlist_globals(void)
{
    int k = *(int *)(texrec + 0xc), mip = rn(4), m = 0;
    while ((1 << m) - 1 < *(int *)(texrec + 0x14)) m++;
    GP(0x8ddf0c) = tbl8;
    GP(0x8ddf30) = pal16 + (rn(2) ? 0x3f00 : 0);
    GP(0x8ddf3c) = texels[mip];
    GI(0x8ddf04) = mip;
    GI(0x8ddf10) = k - mip;
    GI(0x8ddf4c) = (((1 << k) - 1) >> mip) << 16;
    GI(0x8ddf14) = ((((1 << m) - 1) >> mip) << ((k - mip) & 31));
    GI(0x8ddf44) = rn(2) ? 0x8000 : 0x7fff;
    GI(0x8ddf18) = rn(2) ? 0x8000 : 0x7fff;
    GI(0x8ddf24) = rn(4) ? (int)rnd() >> rn(16) : 0;
}
/* a span node: x in [0, W], count 0 .. W - x (+ 2), row; affine u, v (16.16); plane values; light */
static void setup_node(int persp)
{
    int *nd = (int *)A.nodes[0];
    for (int i = 0; i < 16; i++) nd[i] = rnd();
    nd[0] = rn(W + 1);
    if (rn(4) == 0) nd[0] &= ~15;
    nd[1] = rn(W - nd[0] + 3);
    if (rn(8) == 0) nd[1] = rn(3);
    nd[2] = rn(H);
    if (persp) {
        float w = rf(0.05f, 2.0f), u = rf(-50.0f, 300.0f), v = rf(-50.0f, 300.0f);
        if (rn(3) == 0) { float k = rf(100.0f, 30000.0f); u *= k; v *= k; }
        ((float *)nd)[7] = pspecial(w);
        ((float *)nd)[3] = pspecial(u * w);
        ((float *)nd)[4] = pspecial(v * w);
        GF(0x8ddf1c) = pspecial(rf(-1.0f, 1.0f) * w / (rn(2) ? 100.0f : 1000.0f));
        GF(0x8ddf20) = pspecial(rf(-8.0f, 8.0f) * w * (rn(3) ? 1.0f : 1000.0f));
        GF(0x8ddf38) = pspecial(rf(-8.0f, 8.0f) * w * (rn(3) ? 1.0f : 1000.0f));
        GF(0x8ddf28) = rn(8) ? GF(0x8ddf1c) * 16.0f : pspecial(rf(-0.1f, 0.1f));
        GF(0x8ddf2c) = rn(8) ? GF(0x8ddf20) * 16.0f : pspecial(rf(-100.0f, 100.0f));
        GF(0x8ddf48) = rn(8) ? GF(0x8ddf38) * 16.0f : pspecial(rf(-100.0f, 100.0f));
    } else {
        ((float *)nd)[7] = rattr(0.0f, 2.0f);
    }
    nd[8] = (int)(rf(0.0f, 63.99f) * 65536.0f);
    nd[9] = rn(4) ? (int)(rf(-2.0f, 2.0f) * 65536.0f) : (int)rnd();
}

static void make_case(const fn *f)
{
    setup_canvas();
    if (ncase++ % 128 == 0)
        setup_big_tables();
    setup_texture();
    setup_verts(f->kind == K_EDGE || f->kind == K_GRAD || f->kind == K_ESETUP);
    setup_poly();
    setup_globals_b();
    if (f->kind == K_PDRAW || f->kind == K_SETUP || f->kind == K_SEL || f->kind == K_SELL || f->kind == K_SELR)
        while (!grad_safe(*(int *)(A.poly + 0x6c), *(int *)(A.poly + 0x70))) {
            setup_verts(0);
            setup_poly();
            setup_globals_b();
        }
    if (f->kind == K_GRAD)
        while (!grad_safe(GI(0x7f42e8), GI(0x7f42fc))) {
            setup_verts(1);
            setup_poly();
            setup_globals_b();
        }
    memset(A.rec, 0, sizeof A.rec);
    memset(A.nodes, 0, sizeof A.nodes);
    *(float *)(A.poly + 0xf0) = rn(16) ? rcoord(0.0f, 63.99f) : rattr(0.0f, 63.99f);
    if ((f->kind == K_DRAWL || f->kind == K_SELL) && !(*(float *)(A.poly + 0xf0) >= 0.0f && *(float *)(A.poly + 0xf0) < 64.0f))
        *(float *)(A.poly + 0xf0) = 1.0f;
    setup_rec();
    setup_spanlist_globals();
    if (f->kind == K_ESETUP) {
        es_i0 = rn(NV);
        es_i1 = rn(NV);
        if (rn(8) == 0) es_i1 = es_i0;
    }
    if (f->kind == K_SPANR || f->kind == K_SPANP)
        setup_node(f->kind == K_SPANP);
    if (f->kind == K_EDGE) {
        rand_edge(A.e1);
        if (rn(8) == 0) A.e1[3] = GI(0x7f42fc);
    } else {
        rand_span_edge(A.e1);
        rand_span_edge(A.e2);
        if (rn(4) == 0) A.e2[0x10] = A.e1[0x10];
        if (rn(8) == 0 && A.e1[0] >= 65536) A.e2[0] = A.e1[0] + rn(3) * 65536 - 65536;
        if (f->kind == K_PSPAN)
            setup_pspan();
    }
    dl_n = 0;
    memset(dl_log, 0, sizeof dl_log);
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000;
    const char *filt = argc > 2 ? argv[2] : 0;
    if (getenv("Q6_NOSPECIAL")) specials = 0;
    if (getenv("Q6_SEED")) seed ^= strtoull(getenv("Q6_SEED"), 0, 0) * 0x9e3779b97f4a7c15ull;
    long total = 0;
    for (unsigned k = 0; k < NFN; k++) {
        const fn *f = &fns[k];
        if (filt && (filt[0] == '=' ? strcmp(f->name, filt + 1) != 0 : !strstr(f->name, filt))) continue;
        long f0 = fails, drew = 0;
        for (long i = 0; i < n; i++) {
            make_case(f);
            unsigned cw = cws[i % 3];
            save(&s_in);
            if (getenv("Q6_DEBUG") || (getenv("Q6_CASE") && atol(getenv("Q6_CASE")) == i)) {
                printf("case %ld: W %d H %d bpp %d nv %d cw %x\n", i, W, H, BPP, NV, cw);
                printf("  L: x %08x y %d p %g %g %g l %08x | R: x %08x l %08x\n", A.e1[0], A.e1[0x10], ((float *)A.e1)[4],
                       ((float *)A.e1)[6], ((float *)A.e1)[8], A.e1[14], A.e2[0], A.e2[14]);
                printf("  grad %g %g %g step %g %g %g mip %d dst16 %p cbuf %p\n", GF(0x8ddef4), GF(0x8ddec8), GF(0x8ddedc),
                       GF(0x8ddeec), GF(0x8dded0), GF(0x8ddf00), GI(0x8ddee4), GP(0x7f43a8), (void *)A.cbuf);
                fflush(stdout);
            }
            s_orig.ret = call(f, 0, cw, &s_orig.cw, &s_orig.sw);
            save(&s_orig);
            restore(&s_in);
            s_c.ret = call(f, 1, cw, &s_c.cw, &s_c.sw);
            save(&s_c);
            compare(f, i);
            drew += memcmp(s_in.a.cbuf, s_orig.a.cbuf, CBYTES) != 0 || memcmp(s_in.a.zbuf, s_orig.a.zbuf, CBYTES) != 0 || s_orig.dln;
            restore(&s_in);
            total++;
        }
        printf("%-34s %8ld cases  %s  (%ld%% wrote pixels / lines)\n", f->name, n,
               fails == f0 ? "0 differences" : "DIFFERENCES", drew * 100 / (n ? n : 1));
        fflush(stdout);
    }
    printf("%ld cases, %ld differences\n", total, fails);
    return fails != 0;
}
