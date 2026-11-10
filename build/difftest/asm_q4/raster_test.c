/* Differential test of build/overrides_asm_q4.c (the z-buffered software rasteriser) against the original machine code.
 *
 * Each case builds a random rasteriser state (canvas with an 8 or 16 bpp colour buffer and a z-buffer with random
 * contents, light / translucency tables, vertex / uv / light / 1/(z+1) arrays, edge records, a polygon record), runs the
 * original function (orig_<name>, sliced from the assembly; it calls the original edge / span functions) on one copy
 * and the C (which calls the C ones) on another, and compares: the return value, the edge records, the whole colour
 * and z-buffer allocations (with margins), the rasteriser globals 0x007f4440..0x007f4700 and 0x008dde40..0x008ddec0
 * (the span pointer 0x007f44f0 with orig_X mapped to X), the x87 control word and the x87 stack top.
 * The x87 precision control rotates through 24, 53 and 64 bits; the control words the original loads
 * (0x00900524 default, 0x00900526 floor, 0x0090052a ceil) are set from it as stdStartup does.
 *
 * usage: raster_test.exe [cases per function] [function name filter: a substring, or =name]
 * Q4_TIME=1: also time original vs C (cycles per call); Q4_SEED=n: another random sequence;
 * Q4_NOSPECIAL=1: no NaN / inf / huge attribute values. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <windows.h>

extern char sect_data[] __asm__("_sect_data");
#define G(a) ((void *)(sect_data + ((a) - 0x4dd000)))
#define GI(a) (*(int *)G(a))
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
static uint32_t ubits(float f) { uint32_t b; memcpy(&b, &f, 4); return b; }

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

/* an attribute value (z, u, v, light): usually in range, sometimes special */
static int specials = 1;
static float rattr(float lo, float hi)
{
    if (specials && rn(64) == 0) {
        static const uint32_t sp[] = {0x00000000, 0x80000000, 0x7f800000, 0xff800000, 0x7fc00000, 0xffc00000,
                                      0x7fc12345, 0x00000001, 0x80000001, 0x007fffff, 0x7f7fffff, 0xff7fffff,
                                      0x4f000000, 0xcf000000, 0x3f800000, 0xbf800000};
        return fbits(sp[rn(sizeof sp / 4)]);
    }
    if (rn(16) == 0)
        return rcoord(-1e6f, 1e6f);
    return rcoord(lo, hi);
}

/* stand-ins: the empty Mem_DumpLog (the 8 bpp "span" of the FlatLit drivers) and an empty span for the stale pointer
 * a driver calls when the colour depth is neither 8 nor 16 */
void Mem_DumpLog(void) {}
static void null_span(void *a, void *b) { (void)a; (void)b; }

/* ---- the state ---- */
#define MAXW 96
#define MAXH 48
#define MARGIN 2048
#define CBYTES (MARGIN * 2 + (MAXH + 4) * (MAXW * 2 + 16))
#define ZBYTES CBYTES
static unsigned char cbuf_a[CBYTES], zbuf_a[ZBYTES];
static unsigned char cam[64], c4[64], cdesc[0x80], zdesc[0x80];
static unsigned char tbl8[64 * 256 + 512], lut44[65536 + 64], blend[65536 + 512], colormap[0x400];
static unsigned short tbl16_store[512 + 64 * 256 + 1024];
#define tbl16 (tbl16_store + 512)
/* the texture record (material +0x1c): +0xc log2 width, +0x10 width mask, +0x14 height mask, +0x18 mip count,
 * +0x1c.. level records (+0x18 width, +0x5c texels) */
static unsigned char texrec[0x40], levrec[4][0x60], texels[4][65536 + 256];
static int small_light;
static unsigned char tables[0x400];      /* the polygon's +0x4c record */
static unsigned char poly[0x100], mat[0x40];
#define MAXV 12
static float verts[MAXV * 3], uvs[MAXV * 2], lights[MAXV];
static int W, H, BPP;
static int recip_i[1024];
static float recip_f[1024];

static void setup_canvas(void)
{
    W = 1 + rn(MAXW);
    H = 1 + rn(MAXH);
    BPP = rn(16) == 0 ? 24 : (rn(2) ? 8 : 16);
    int pitch = W * (BPP == 8 ? 1 : 2) + rn(9);
    int zpitch = W * 2 + rn(5) * 2;
    for (int i = 0; i < CBYTES / 8; i++) ((uint64_t *)cbuf_a)[i] = (seed ^= seed << 13, seed ^= seed >> 7, seed ^= seed << 17);
    for (int i = 0; i < ZBYTES / 8; i++) ((uint64_t *)zbuf_a)[i] = (seed ^= seed << 13, seed ^= seed >> 7, seed ^= seed << 17);
    memset(cam, 0, sizeof cam); memset(c4, 0, sizeof c4);
    *(void **)(cam + 4) = c4;
    *(void **)(c4 + 4) = cdesc;
    *(void **)(c4 + 0x10) = zdesc;
    *(int *)(c4 + 0x14) = rn(3) == 0 ? 0 : rn(4) == 0 ? rn(17) : (rn(2) ? 16 : 8);   /* 0 in the game (the FlatLit drivers then pick the C fillers) */
    *(int *)(cdesc + 0x18) = pitch;
    *(int *)(cdesc + 0x24) = BPP;
    *(void **)(cdesc + 0x5c) = cbuf_a + MARGIN;
    *(int *)(zdesc + 0x18) = zpitch;
    *(void **)(zdesc + 0x5c) = zbuf_a + MARGIN;
    *(void **)G(0x7f0fc8) = cam;
}

static void setup_big_tables(void)
{
    for (unsigned i = 0; i < sizeof tbl8; i++) tbl8[i] = rnd();
    for (unsigned i = 0; i < sizeof tbl16_store / 2; i++) tbl16_store[i] = rnd();
    for (int k = 0; k < 4; k++)
        for (unsigned i = 0; i < sizeof texels[k]; i++) texels[k][i] = rn(4) ? rnd() : 0;
    for (unsigned i = 0; i < sizeof lut44; i++) lut44[i] = rnd();
    for (unsigned i = 0; i < sizeof blend; i++) blend[i] = rnd();
    *(void **)(tables + 0x330) = tbl8;
    *(void **)(tables + 0x348) = tbl16;
    *(void **)(tables + 0x34c) = lut44;
    *(void **)(colormap + 0x338) = blend;
    GP(0x4f5ec4) = colormap;
    /* the span length tables (filled at run time by the game: 65536 / n and 1.0f / n); sometimes perturbed */
    for (int n = 0; n < 1024; n++) {
        recip_i[n] = n ? 65536 / n : 0;
        recip_f[n] = n ? 1.0f / n : 0.0f;
        if (rn(32) == 0) { recip_i[n] += rn(5) - 2; recip_f[n] = nextafterf(recip_f[n], rn(2) ? 1 : -1); }
    }
    memcpy(G(0x8fbfc0), recip_i, sizeof recip_i);
    memcpy(G(0x8fe000), recip_f, sizeof recip_f);
}

/* the tables are refreshed every 128 cases (they are inputs to both sides alike), the per-mode globals every case */
static long ncase;
static void setup_tables(void)
{
    if (ncase++ % 128 == 0)
        setup_big_tables();
    GP(0x8dde44) = lut44;
    GP(0x8dde5c) = tbl16 + (rn(2) ? 0x3f00 : 0);
    GP(0x8dde6c) = tbl8;
    GP(0x8dde90) = blend;
    *(unsigned short *)G(0x8dde70) = rnd();
    *(unsigned char *)G(0x8dde98) = rnd();
    GI(0x8ddea4) = *(int *)(c4 + 0x14);
    /* texture: log2 width k, height 2^m (k + m <= 16), up to 4 mip levels */
    static const int widths[] = {4, 8, 16, 32, 64, 128, 256, 1, 2, 3, 100, 512};
    int k = 3 + rn(6), m = rn(9);   /* log2 width >= 3: the mip level (0..3) never exceeds it in the game */
    if (k + m > 16) m = 16 - k;
    memset(texrec, 0, sizeof texrec);
    *(int *)(texrec + 0xc) = k;
    *(int *)(texrec + 0x10) = (1 << k) - 1;
    *(int *)(texrec + 0x14) = (1 << m) - 1;
    *(int *)(texrec + 0x18) = rn(8) ? 1 + rn(4) : rn(7) - 1;      /* mip count; the mode is count - 1 */
    for (int i = 0; i < 4; i++) {
        *(void **)(texrec + 0x1c + 4 * i) = levrec[i];
        *(int *)(levrec[i] + 0x18) = rn(4) ? widths[rn(7)] : widths[rn(12)];
        *(void **)(levrec[i] + 0x5c) = texels[i];
    }
    /* the per-span texture globals (as the drivers set them) */
    int mip = rn(4);
    GI(0x8dde54) = mip;
    GI(0x8dde8c) = k - mip;
    GI(0x8dde48) = (((1 << k) - 1) >> mip) << 16;
    GI(0x8dde58) = ((((1 << m) - 1) >> mip) << ((k - mip) & 31));
    GP(0x8dde7c) = texels[mip];
    GI(0x8dde50) = rn(2) ? 0x8000 : 0x7fff;
    GI(0x8dde78) = rn(2) ? 0x8000 : 0x7fff;
    GI(0x8dde68) = widths[rn(12)];
    GI(0x7f4464) = rn(6) - 1;
    GP(0x7f44f0) = null_span;
}

/* a polygon: n vertices, screen x in [-2, W + 2), y in [0, H), attributes random */
static int NV;
static void setup_verts(void)
{
    NV = 1 + rn(MAXV);
    if (rn(4)) NV = 3 + rn(6);
    for (int i = 0; i < NV; i++) {
        verts[i * 3] = rcoord(1.0f, W + 1.0f);   /* >= 1: a negative right edge x gives a 65535-pixel span (unsigned >> 16), in the original too */
        verts[i * 3 + 1] = rcoord(0.0f, (float)H);
        verts[i * 3 + 2] = rattr(0.0f, 20.0f);
        uvs[i * 2] = rattr(-4.0f, 300.0f);
        uvs[i * 2 + 1] = rattr(-4.0f, 300.0f);
        lights[i] = small_light ? rf(0.0f, 63.0f) : rattr(0.0f, 63.99f);
        if (i && rn(6) == 0) verts[i * 3 + 1] = verts[(i - 1) * 3 + 1];   /* horizontal edge */
        if (i && rn(10) == 0) verts[i * 3] = verts[(i - 1) * 3];         /* vertical edge */
    }
    GP(0x7f44fc) = verts;
    GP(0x7f4584) = uvs;
    GP(0x7f44f8) = lights;
    GI(0x7f4460) = NV;
    GI(0x7f44e8) = rn(NV);
    GI(0x7f44f4) = rn(NV);
    int d = rn(2) ? 1 : -1;
    GI(0x7f44ec) = d;
    GI(0x7f4580) = -d;
    float *zi = G(0x7f4588);
    for (int i = 0; i < MAXV; i++) zi[i] = rattr(0.0f, 1.0f);
}

static void setup_poly(void)
{
    memset(poly, 0, sizeof poly);
    *(int *)(poly + 0x1c) = NV;
    *(void **)(poly + 0x20) = verts;
    *(void **)(poly + 0x24) = uvs;
    *(void **)(poly + 0x28) = lights;
    *(void **)(poly + 0x4c) = tables;
    *(int *)(poly + 0x50) = rn(2);
    *(int *)(poly + 0x6c) = rn(NV);
    *(int *)(poly + 0x70) = rn(NV);
    for (unsigned i = 0; i < sizeof mat; i++) mat[i] = rnd();
    *(int *)(mat + 4) = rn(256);
    *(void **)(mat + 0x1c) = texrec;
    *(float *)(poly + 0x64) = rn(16) ? rf(0.0f, 60.0f) : rattr(0.0f, 60.0f);
    if (rn(8) == 0) *(float *)(poly + 0x64) = (float)(rn(5) * 10);
}

/* an edge record: random contents, a vertex index */
typedef struct { int x, dx, h, idx; float z, dz; int p[4]; int u, du, v, dv, l, dl, y; } edge;
static void rand_edge(edge *e)
{
    uint32_t *w = (uint32_t *)e;
    for (int i = 0; i < 17; i++) w[i] = rnd();
    e->idx = rn(NV);
}
/* an edge record as a span filler sees it: x in [-2, W + 2) pixels (16.16), y in [0, H), z, l */
static void rand_span_edge(edge *e)
{
    rand_edge(e);
    e->x = (int)(rf(0.0f, W + 1.0f) * 65536.0f);
    if (rn(6) == 0) e->x &= ~0xffff;
    e->y = rn(H);
    e->z = rattr(0.0f, 1.0f);
    e->l = (int)(rf(-2.0f, 66.0f) * 65536.0f);
    if (rn(8) == 0) e->l = rnd();
    if (small_light) e->l = (int)(rf(0.0f, 63.0f) * 65536.0f);
    e->u = rnd(); e->v = rnd();
}

/* ---- snapshot / compare ---- */
#define R1 0x7f4440
#define R1N 0x2c0
#define R2 0x8dde40
#define R2N 0x80
typedef struct {
    unsigned char g1[R1N], g2[R2N], cb[CBYTES], zb[ZBYTES];
    edge e1, e2;
    int ret;
    unsigned cw, sw;
} snap;
static snap s_in, s_orig, s_c;
static edge E1, E2;

static void save(snap *s)
{
    memcpy(s->g1, G(R1), R1N); memcpy(s->g2, G(R2), R2N);
    memcpy(s->cb, cbuf_a, CBYTES); memcpy(s->zb, zbuf_a, ZBYTES);
    s->e1 = E1; s->e2 = E2;
}
static void restore(const snap *s)
{
    memcpy(G(R1), s->g1, R1N); memcpy(G(R2), s->g2, R2N);
    memcpy(cbuf_a, s->cb, CBYTES); memcpy(zbuf_a, s->zb, ZBYTES);
    E1 = s->e1; E2 = s->e2;
}

/* ---- the functions ---- */
enum { K_EDGE, K_SPAN, K_DRAW, K_DRAWL, K_GRAD };
typedef struct { const char *name; int kind; void *orig, *c; } fn;
#define FN(kind, n) extern void orig_##n(void), n(void);
#include "q4_funcs.h"
#undef FN
static const fn fns[] = {
#define FN(kind, n) {#n, kind, (void *)orig_##n, (void *)n},
#include "q4_funcs.h"
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
    case K_EDGE: r = ((int (*)(edge *))p)(&E1); break;
    case K_SPAN: ((void (*)(edge *, edge *))p)(&E1, &E2); break;
    case K_DRAW: ((void (*)(void *, void *))p)(poly, mat); break;
    case K_DRAWL: ((void (*)(void *, void *, float))p)(poly, mat, *(float *)(poly + 0xf0)); break;
    case K_GRAD: ((void (*)(int))p)(*(int *)(poly + 0x64)); break;
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

static void compare(const fn *f, long i)
{
    if (s_orig.ret != s_c.ret) diff(f, i, "return", 0);
    if (s_orig.cw != s_c.cw) diff(f, i, "control word", s_orig.cw);
    if (s_orig.sw != s_c.sw) diff(f, i, "x87 stack top", s_orig.sw);
    if (memcmp(&s_orig.e1, &s_c.e1, sizeof(edge))) {
        for (int k = 0; k < 17; k++)
            if (((int *)&s_orig.e1)[k] != ((int *)&s_c.e1)[k]) { diff(f, i, "edge record 1", k * 4); break; }
    }
    if (memcmp(&s_orig.e2, &s_c.e2, sizeof(edge))) diff(f, i, "edge record 2", 0);
    /* the span pointer: orig_X -> X */
    *(void **)(s_orig.g1 + (0x7f44f0 - R1)) = map_orig(*(void **)(s_orig.g1 + (0x7f44f0 - R1)));
    for (int k = 0; k < R1N; k++) if (s_orig.g1[k] != s_c.g1[k]) { diff(f, i, "globals 0x7f44xx", R1 + k); break; }
    for (int k = 0; k < R2N; k++) if (s_orig.g2[k] != s_c.g2[k]) { diff(f, i, "globals 0x8ddexx", R2 + k); break; }
    if (memcmp(s_orig.cb, s_c.cb, CBYTES))
        for (int k = 0; k < CBYTES; k++) if (s_orig.cb[k] != s_c.cb[k]) { diff(f, i, "colour buffer", k - MARGIN); break; }
    if (memcmp(s_orig.zb, s_c.zb, ZBYTES))
        for (int k = 0; k < ZBYTES; k++) if (s_orig.zb[k] != s_c.zb[k]) { diff(f, i, "z-buffer", k - MARGIN); break; }
}

/* Grad_*: when the vertex next to the top is the bottom, the third vertex starts as the argument's bits and only a
 * vertex whose x differs from the top / bottom midpoint replaces it; the original would index with those bits
 * otherwise (the game's polygons never get there), so such polygons are not generated */
static int wrapi(int n) { if (n < 0) return NV - 1; return n > NV - 1 ? 0 : n; }
static int grad_safe(int start, int end)
{
    int dir;
    if (NV == 3) return 1;
    if (NV < 3) return 0;
    if (wrapi(start + 1) == end) dir = -1;
    else if (wrapi(start - 1) == end) dir = 1;
    else return 1;
    float mid = (float)(((double)verts[start * 3] + verts[end * 3]) * 0.5);
    for (int k = wrapi(start + dir); k != end; k = wrapi(k + dir))
        if (verts[k * 3] != mid) return 1;
    return 0;
}

static void make_case(const fn *f)
{
    setup_canvas();
    setup_tables();
    do {
        setup_verts();
        setup_poly();
    } while ((f->kind == K_GRAD && !grad_safe(GI(0x7f44e8), GI(0x7f44f4))) ||
             ((f->kind == K_DRAW || f->kind == K_DRAWL) && !grad_safe(*(int *)(poly + 0x6c), *(int *)(poly + 0x70))));
    *(float *)(poly + 0xf0) = rn(16) ? rcoord(0.0f, 63.99f) : rattr(0.0f, 63.99f);
    if (f->kind == K_EDGE) {
        rand_edge(&E1);
        if (rn(8) == 0) E1.idx = GI(0x7f44f4);
    } else {
        rand_span_edge(&E1);
        rand_span_edge(&E2);
        if (rn(4) == 0) { E2.y = E1.y; }
        if (rn(8) == 0 && E1.x >= 65536) { E2.x = E1.x + rn(3) * 65536 - 65536; }
    }
    /* driver light argument: a polygon light level that indexes the 64 table rows */
    if (f->kind == K_DRAWL && !isfinite(*(float *)(poly + 0xf0))) *(float *)(poly + 0xf0) = 0.0f;
    if (f->kind == K_DRAWL && (*(float *)(poly + 0xf0) < 0 || *(float *)(poly + 0xf0) >= 64.0f)) *(float *)(poly + 0xf0) = 1.0f;
}

static inline uint64_t rdtsc(void) { uint32_t lo, hi; __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi)); return ((uint64_t)hi << 32) | lo; }

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000;
    const char *filt = argc > 2 ? argv[2] : 0;
    if (getenv("Q4_NOSPECIAL")) specials = 0;
    if (getenv("Q4_SEED")) seed ^= strtoull(getenv("Q4_SEED"), 0, 0) * 0x9e3779b97f4a7c15ull;
    long total = 0;
    for (unsigned k = 0; k < NFN; k++) {
        const fn *f = &fns[k];
        if (filt && (filt[0] == '=' ? strcmp(f->name, filt + 1) != 0 : !strstr(f->name, filt))) continue;
        /* the dithered filler indexes the light table without the 0..63 mask: keep the light in range */
        small_light = !strcmp(f->name, "rdZRaster_DrawScanLineNGonGAT_16") || !strcmp(f->name, "rdZRaster_DrawNGonGAT");
        long f0 = fails;
        uint64_t t_orig = 0, t_c = 0;
        for (long i = 0; i < n; i++) {
            make_case(f);
            unsigned cw = cws[i % 3];
            save(&s_in);
            if (getenv("Q4_DEBUG"))
                printf("case %ld: W %d H %d bpp %d L.x %08x L.y %d R.x %08x idx %d nv %d\n", i, W, H, BPP, E1.x, E1.y,
                       E2.x, E1.idx, NV), fflush(stdout);
            if (getenv("Q4_DEBUG") && f->kind >= K_DRAW) {
                for (int v = 0; v < NV; v++) printf("  v%d %.9g %.9g %.9g\n", v, verts[v * 3], verts[v * 3 + 1], verts[v * 3 + 2]);
                printf("  top %d bottom %d flip %d\n", *(int *)(poly + 0x6c), *(int *)(poly + 0x70), *(int *)(poly + 0x50));
                fflush(stdout);
            }
            uint64_t t0 = rdtsc();
            s_orig.ret = call(f, 0, cw, &s_orig.cw, &s_orig.sw);
            uint64_t t1 = rdtsc();
            save(&s_orig);
            restore(&s_in);
            uint64_t t2 = rdtsc();
            s_c.ret = call(f, 1, cw, &s_c.cw, &s_c.sw);
            uint64_t t3 = rdtsc();
            save(&s_c);
            t_orig += t1 - t0; t_c += t3 - t2;
            compare(f, i);
            total++;
        }
        printf("%-34s %8ld cases  %s", f->name, n, fails == f0 ? "0 differences" : "DIFFERENCES");
        if (getenv("Q4_TIME")) printf("   cycles/call orig %.0f  C %.0f", (double)t_orig / n, (double)t_c / n);
        printf("\n");
        fflush(stdout);
    }
    printf("%ld cases, %ld differences\n", total, fails);
    return fails != 0;
}
