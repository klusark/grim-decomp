/* Differential test of build/overrides_asm_q1.c against the original 1.01 machine code (sliced from the assembly of
 * 2df265d): rdClip_Line2, rdClip_Face3W, rdClip_Face3WOrtho, rdClip_Face3S, rdClip_Face3SOrtho,
 * rdClip_Face3GSOrtho.  Build: build/difftest/asm_q1/build.sh <exe>; run: <exe> [cases per function] [function index].
 *
 * Each case runs the original and the C on the same addresses and the same start state (the state is restored between
 * the two runs) under the x87 precision control 24, 53 or 64 bits (rotating) and compares:
 *   - the return value (EAX),
 *   - the caller's arrays (positions / intensities, including the slots past the polygon; the Line2D end points),
 *   - the data image from 0x7f4600 to 0x7f5400: the static clip buffers 0x7f47c0 (intensities) and 0x7f48c0
 *     (positions), the pointer globals 0x7f4618 / 0x7f46ac / 0x7f46b0 / 0x7f47b8 and the clip flags 0x7f4ac4, and what
 *     follows (an overflowing polygon writes past the position buffer in both versions),
 *   - the call log of the rdClip_CalcOutcode2 stand-in (canvas, x, y),
 *   - the x87 control word and the x87 stack top.
 * Inputs: Face3 polygons of 0..16 vertices (and negative counts), convex fans or random points around the frustum,
 * vertices snapped onto planes (x = float(slope * y), y = near / far, x = bound), duplicated vertices, special values
 * (0, -0, +-inf, quiet and signalling NaN, denormals); perspective slopes and orthographic bounds of both signs, far plane
 * on / off.  Line2D: canvas rectangles (also empty / inverted), end points inside, outside, on the edges, vertical /
 * horizontal, large values up to +-2^31 (float rounding, _ftol of values beyond the int range).
 * Known difference: with a signalling NaN input the NaN bits of a result may differ (the original subtracts / adds a
 * memory operand, the C loads it first, which quietens it); such a case is counted as "NaN-payload-only" when both
 * values are quiet NaNs and an input holds a signalling NaN, and as a difference otherwise.  Q1_NAN=1 makes every
 * input NaN quiet (then there must be no such case). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef unsigned uint;
extern uint orig_rdClip_Line2(int, int *, int *, int *, int *), rdClip_Line2(int, int *, int *, int *, int *);
extern uint orig_rdClip_Face3W(uint *, float *, int), rdClip_Face3W(uint *, float *, int);
extern uint orig_rdClip_Face3WOrtho(uint *, float *, int), rdClip_Face3WOrtho(uint *, float *, int);
extern uint orig_rdClip_Face3S(uint *, float *, int), rdClip_Face3S(uint *, float *, int);
extern uint orig_rdClip_Face3SOrtho(uint *, float *, int), rdClip_Face3SOrtho(uint *, float *, int);
extern uint orig_rdClip_Face3GSOrtho(uint *, float *, float *, int), rdClip_Face3GSOrtho(uint *, float *, float *, int);

extern unsigned char sect_data[] __asm__("_sect_data");
#define DATA(va) (sect_data + ((va) - 0x4dd000))
#define REG_LO 0x7f4600
#define REG_HI 0x7f5400

static uint64_t seed = 0x9E3779B97F4A7C15ull;
static uint rnd(void) { seed ^= seed << 13; seed ^= seed >> 7; seed ^= seed << 17; return (uint)(seed >> 17); }
static uint R(uint n) { return n ? rnd() % n : 0; }
static uint fbits(float f) { uint u; memcpy(&u, &f, 4); return u; }
/* NB: values are passed around as bits (setf), never as a float return value: returning a float goes through st0,
 * which would quieten a signalling NaN */
static void setf(float *dst, uint u) { memcpy(dst, &u, 4); }
static uint special(void)
{
    static const uint t[] = {0x00000000, 0x80000000, 0x7f800000, 0xff800000, 0x7fc00000, 0x7f800001, 0xffc00000,
                             0x7fa00000, 0x00000001, 0x807fffff, 0x3f800000, 0xbf800000, 0x7f7fffff, 0x00800000};
    return t[R(sizeof t / sizeof t[0])];
}
static float U(float lo, float hi) { return lo + (hi - lo) * (float)(rnd() & 0xffffff) / 16777216.0f; }

/* ---- rdClip_CalcOutcode2 stand-in: the real outcode, logged; after 64 calls it returns 0 (ends any loop) ---- */
static uint lg[2][256]; static int nlg[2], side;
uint rdClip_CalcOutcode2(int c, int x, int y)
{
    uint r = 0;
    int *cv = (int *)c;
    if (nlg[side] < 250) { lg[side][nlg[side]++] = (uint)c; lg[side][nlg[side]++] = (uint)x; lg[side][nlg[side]++] = (uint)y; }
    if (nlg[side] > 64 * 3) return 0;
    if (x < cv[6]) r = 1; else if (cv[8] < x) r = 0x10;
    if (y < cv[7]) return r | 0x1000;
    if (cv[9] < y) r |= 0x100;
    return r;
}

static uint16_t get_cw(void) { uint16_t cw; __asm__ volatile("fnstcw %0" : "=m"(cw)); return cw; }
static uint16_t get_sw(void) { uint16_t sw; __asm__ volatile("fnstsw %0" : "=m"(sw)); return sw; }
static void set_cw(uint16_t cw) { __asm__ volatile("fninit; fldcw %0" : : "m"(cw)); }

/* ---- state ---- */
#define NP 4096
static struct st {
    float pos[NP];
    float in[NP];
    uint fr[16];
    int canvas[12];
    int pt[4];
    unsigned char reg[REG_HI - REG_LO];
} s0, s;
static struct res { uint ret; uint16_t cw, sw; struct st st; int nlg; } r[2];

static const char *fname[6] = {"rdClip_Line2", "rdClip_Face3W", "rdClip_Face3WOrtho", "rdClip_Face3S",
                               "rdClip_Face3SOrtho", "rdClip_Face3GSOrtho"};

static void run(int f, int n, uint16_t cw, int sd)
{
    uint ret = 0;
    s = s0;
    memcpy(DATA(REG_LO), s0.reg, sizeof s0.reg);
    side = sd; nlg[sd] = 0;
    set_cw(cw);
    switch (f) {
    case 0: ret = (sd ? rdClip_Line2 : orig_rdClip_Line2)((int)s.canvas, &s.pt[0], &s.pt[1], &s.pt[2], &s.pt[3]); break;
    case 1: ret = (sd ? rdClip_Face3W : orig_rdClip_Face3W)(s.fr, s.pos, n); break;
    case 2: ret = (sd ? rdClip_Face3WOrtho : orig_rdClip_Face3WOrtho)(s.fr, s.pos, n); break;
    case 3: ret = (sd ? rdClip_Face3S : orig_rdClip_Face3S)(s.fr, s.pos, n); break;
    case 4: ret = (sd ? rdClip_Face3SOrtho : orig_rdClip_Face3SOrtho)(s.fr, s.pos, n); break;
    case 5: ret = (sd ? rdClip_Face3GSOrtho : orig_rdClip_Face3GSOrtho)(s.fr, s.pos, s.in, n); break;
    }
    r[sd].cw = get_cw();
    r[sd].sw = get_sw();
    set_cw(0x037f);
    r[sd].ret = ret;
    memcpy(s.reg, DATA(REG_LO), sizeof s.reg);
    r[sd].st = s;
    r[sd].nlg = nlg[sd];
}

/* ---- inputs ---- */
static float slope(int sign)
{
    uint k = R(16);
    if (k == 0) return 0.0f * (float)R(2);   /* special values of the bounds: see gen_frustum */
    if (k == 1) return 0.0f;
    if (k == 2) return (float)((int)R(9) - 4) * 0.5f;
    return sign * U(0.1f, 2.5f);
}

static void gen_frustum(int persp)
{
    int i;
    float *fr = (float *)s0.fr;
    s0.fr[0] = R(3) ? 1 : 0;
    fr[1] = R(4) ? U(0.05f, 2.0f) : (float)R(3);
    fr[2] = R(4) ? U(5.0f, 40.0f) : (float)(4 + R(8));
    if (R(10) == 0) setf(&fr[1], special());
    if (R(10) == 0) setf(&fr[2], special());
    if (R(30) == 0) { float t = fr[1]; fr[1] = fr[2]; fr[2] = t; }
    fr[3] = slope(-1) * 4; fr[5] = slope(1) * 4; fr[4] = slope(1) * 4; fr[6] = slope(-1) * 4;
    fr[7] = slope(1); fr[8] = slope(-1); fr[9] = slope(-1); fr[10] = slope(1); fr[11] = slope(1); fr[12] = slope(-1);
    for (i = 3; i < 13; i++) if (R(16) == 0) setf(&fr[i], special());
    for (i = 13; i < 16; i++) s0.fr[i] = rnd();
    if (R(20) == 0) {                      /* anything */
        for (i = 1; i < 13; i++) { fr[i] = U(-5, 5); if (R(4) == 0) setf(&fr[i], special()); }
    }
    (void)persp;
}

static int heavy;   /* every fourth case: more special values */

/* a vertex near the frustum, possibly snapped onto one of the planes of clipper f */
static void gen_vertex(int f, float *v, float cx, float cy, float cz, float rad)
{
    float *fr = (float *)s0.fr;
    uint k = R(40);
    v[0] = cx + U(-rad, rad);
    v[1] = cy + U(-rad, rad);
    v[2] = cz + U(-rad, rad);
    if (R(6) == 0) { v[0] = (float)((int)R(17) - 8) * 0.5f; v[1] = (float)((int)R(17) - 2) * 0.5f; v[2] = (float)((int)R(17) - 8) * 0.5f; }
    if (k < 12) {
        int persp = (f == 1 || f == 3);
        int side[4];
        int j = R(4);
        if (f == 1) { side[0] = 9; side[1] = 10; side[2] = 7; side[3] = 8; }
        else if (f == 3) { side[0] = 12; side[1] = 10; side[2] = 11; side[3] = 8; }
        else { side[0] = 3; side[1] = 5; side[2] = 4; side[3] = 6; }
        if (k < 4) v[1] = fr[1 + R(2)];                                       /* on near / far */
        else {
            float val = persp ? (float)((long double)v[1] * fr[side[j]]) : fr[side[j]];
            if (R(4) == 0) val = (float)((double)fr[side[j]] * v[1]);        /* double-rounded variant */
            v[j < 2 ? 0 : 2] = val;
            if (R(5) == 0) setf(&v[j < 2 ? 0 : 2], fbits(val) + (R(2) ? 1 : -1));   /* one ulp off */
        }
    }
    if (R(heavy ? 6 : 60) == 0) setf(&v[R(3)], special());
}

static int gen_face(int f)
{
    int n, i;
    float cx, cy, cz, rad;
    float *fr = (float *)s0.fr;
    uint k = R(20);
    n = k == 0 ? (int)R(3) : (k == 1 ? -(int)R(3) - 1 : (k < 10 ? 3 + (int)R(2) : 3 + (int)R(14)));
    cy = U(-2, 25);
    cx = U(-2, 2) * (cy > 1 ? cy : 1);
    cz = U(-2, 2) * (cy > 1 ? cy : 1);
    rad = R(3) ? U(0.1f, 8) : U(0.001f, 0.1f);
    if (f == 2 || f == 4 || f == 5) { cx = U(-12, 12); cz = U(-12, 12); }
    for (i = 0; i < NP; i++) { setf(&s0.pos[i], 0x55500000 + i); setf(&s0.in[i], 0x66600000 + i); }
    if (R(3) == 0) {                         /* convex fan */
        float a0 = U(0, 6.28f), ry = R(3) ? rad : 0;
        for (i = 0; i < (n > 0 ? n : 0); i++) {
            float a = a0 + 6.2831853f * i / n;
            float ca, sa;   /* Taylor series: rough, fine for a shape */
            while (a > 3.14159f) a -= 6.2831853f;
            ca = 1 - a * a / 2 + a * a * a * a / 24 - a * a * a * a * a * a / 720;
            sa = a - a * a * a / 6 + a * a * a * a * a / 120;
            s0.pos[i * 3] = cx + rad * ca;
            s0.pos[i * 3 + 1] = cy + ry * sa * 0.3f;
            s0.pos[i * 3 + 2] = cz + rad * sa;
            if (R(8) == 0) gen_vertex(f, &s0.pos[i * 3], cx, cy, cz, rad);
        }
    } else {
        for (i = 0; i < (n > 0 ? n : 0); i++) gen_vertex(f, &s0.pos[i * 3], cx, cy, cz, rad);
    }
    for (i = 0; i < (n > 0 ? n : 0); i++) {
        if (i > 0 && R(15) == 0) memcpy(&s0.pos[i * 3], &s0.pos[(i - 1) * 3], 12);   /* duplicate vertex */
        s0.in[i] = U(-0.5f, 1.5f);
        if (R(12) == 0) setf(&s0.in[i], special());
    }
    if (R(25) == 0) {   /* tiny polygon: differences and products leave the float range (extended den != 0, float 0) */
        int sc = 100 + R(40);
        long double m = 1.0L;
        while (sc-- > 0) m *= 0.5L;
        for (i = 0; i < 3 * (n > 0 ? n : 0); i++) s0.pos[i] = (float)((long double)s0.pos[i] * m);
        for (i = 1; i < (n > 0 ? n : 0); i++)     /* edges with DX == 0 or DZ == 0 and a DY of a few denormal steps */
            if (R(2)) {
                int c = 2 * R(2);
                memcpy(&s0.pos[3 * i + c], &s0.pos[3 * (i - 1) + c], 4);
                if (R(2)) setf(&s0.pos[3 * i + 1], fbits(s0.pos[3 * (i - 1) + 1]) + 1 + R(3));
            }
    }
    (void)fr;
    return n;
}

static int big(void)
{
    switch (R(8)) {
    case 0: return (int)rnd() * 2 + (int)R(2);
    case 1: return R(2) ? 0x7fffffff - (int)R(200) : (int)0x80000000 + (int)R(200);
    case 2: return ((int)R(2) ? 1 : -1) * (int)((1u << (24 + R(7))) + R(1000) - 500);
    default: return (int)R(4001) - 2000;
    }
}

static void gen_line(void)
{
    int *c = s0.canvas, i;
    for (i = 0; i < 12; i++) c[i] = (int)rnd();
    c[6] = (int)R(200) - 50; c[8] = c[6] + (int)R(700);
    c[7] = (int)R(200) - 50; c[9] = c[7] + (int)R(500);
    if (R(20) == 0) { c[6] = big(); c[7] = big(); c[8] = big(); c[9] = big(); }
    for (i = 0; i < 4; i++) {
        uint k = R(10);
        int lo = (i & 1) ? c[7] : c[6], hi = (i & 1) ? c[9] : c[8];
        if (k < 3) s0.pt[i] = lo + (int)R((uint)(hi - lo) + 1);
        else if (k < 5) s0.pt[i] = R(2) ? lo : hi;
        else if (k < 6) s0.pt[i] = big();
        else s0.pt[i] = lo - 400 + (int)R((uint)(hi - lo) + 800);
    }
    if (R(6) == 0) {                           /* vertical, also at x beyond 2^24 (float(x1) != x0) */
        if (R(3) == 0) s0.pt[0] = big();
        s0.pt[2] = s0.pt[0];
    }
    if (R(6) == 0) s0.pt[3] = s0.pt[1];        /* horizontal */
}

static long fails;
static void fail(int f, long i, const char *what, int n)
{
    fails++;
    if (fails <= 20)
        printf("%s case %ld (n=%d, cw=%04x): %s (ret %u / %u)\n", fname[f], i, n, r[0].cw, what, r[0].ret, r[1].ret);
}

static int isnan_u(uint u) { return (u & 0x7f800000) == 0x7f800000 && (u & 0x7fffff) != 0; }
static int issnan_u(uint u) { return isnan_u(u) && !(u & 0x400000); }
/* 0 equal, 1 only NaN bits differ (both NaN), 2 other difference */
static int cmpf(const uint *a, const uint *b, int n)
{
    int i, k = 0;
    for (i = 0; i < n; i++)
        if (a[i] != b[i]) {
            if (isnan_u(a[i]) && isnan_u(b[i]) && !issnan_u(a[i]) && !issnan_u(b[i])) k |= 1; else return 2;
        }
    return k;
}
static int has_snan(int f, int n)
{
    int i;
    for (i = 1; i < 13; i++) if (issnan_u(s0.fr[i])) return 1;
    for (i = 0; i < 3 * n; i++) if (issnan_u(((uint *)s0.pos)[i])) return 1;
    for (i = 0; f == 5 && i < n; i++) if (issnan_u(((uint *)s0.in)[i])) return 1;
    return 0;
}
static void dump(int f, int n)
{
    int j;
    const uint *a = (const uint *)r[0].st.pos, *b = (const uint *)r[1].st.pos, *p = (const uint *)s0.pos;
    if (fails > 5) return;
    for (j = 0; j < NP; j++)
        if (a[j] != b[j]) printf("   pos[%d]: orig %08x  C %08x  (input %08x)\n", j, a[j], b[j], p[j]);
    a = (const uint *)r[0].st.in; b = (const uint *)r[1].st.in;
    for (j = 0; j < NP; j++)
        if (a[j] != b[j]) printf("   in[%d]: orig %08x  C %08x\n", j, a[j], b[j]);
    for (j = 0; j < 13; j++) printf("   fr[%d] = %08x\n", j, s0.fr[j]);
    for (j = 0; j < n; j++) printf("   v%d: %08x %08x %08x  i %08x\n", j, p[3 * j], p[3 * j + 1], p[3 * j + 2], ((uint *)s0.in)[j]);
    (void)f;
}

int main(int argc, char **argv)
{
    long cases = argc > 1 ? atol(argv[1]) : 100000, i;
    int only = argc > 2 ? atoi(argv[2]) : -1, f;
    static const uint16_t cws[3] = {0x007f, 0x027f, 0x037f};
    int quiet_only = getenv("Q1_NAN") != 0;
    for (f = 0; f < 6; f++) {
        long fb = fails, nonzero = 0, clipped = 0, bits[8] = {0}, loops = 0, nanonly = 0;
        if (only >= 0 && f != only) continue;
        for (i = 0; i < cases; i++) {
            int n = 0, j;
            uint16_t cw = cws[i % 3];
            for (j = 0; j < (int)sizeof s0.reg; j++) s0.reg[j] = (unsigned char)rnd();
            heavy = (i & 3) == 3;
            if (f == 0) gen_line();
            else { gen_frustum(f == 1 || f == 3); n = gen_face(f); }
            if (quiet_only) {   /* Q1_NAN=1: every signalling NaN input made quiet */
                for (j = 1; j < 13; j++) if (issnan_u(s0.fr[j])) s0.fr[j] |= 0x400000;
                for (j = 0; j < NP; j++) if (issnan_u(((uint *)s0.pos)[j])) ((uint *)s0.pos)[j] |= 0x400000;
                for (j = 0; j < NP; j++) if (issnan_u(((uint *)s0.in)[j])) ((uint *)s0.in)[j] |= 0x400000;
            }
            run(f, n, cw, 0);
            run(f, n, cw, 1);
            {
                int k1 = cmpf((uint *)r[0].st.pos, (uint *)r[1].st.pos, NP);
                int k2 = cmpf((uint *)r[0].st.in, (uint *)r[1].st.in, NP);
                int k3 = cmpf((uint *)r[0].st.reg, (uint *)r[1].st.reg, sizeof s0.reg / 4);
                int knan = k1 | k2 | k3;
                if (r[0].ret != r[1].ret) fail(f, i, "return value", n);
                else if (k1 & 2) { fail(f, i, "positions", n); dump(f, n); }
                else if (k2 & 2) { fail(f, i, "intensities", n); dump(f, n); }
                else if (memcmp(r[0].st.pt, r[1].st.pt, sizeof s0.pt)) fail(f, i, "line end points", n);
                else if (k3 & 2) {
                    for (j = 0; j < (int)sizeof s0.reg && r[0].st.reg[j] == r[1].st.reg[j]; j++) ;
                    fail(f, i, "data image 0x7f4600..0x7f5400", n);
                    if (fails <= 20) printf("   first difference at 0x%x\n", REG_LO + j);
                }
                else if (r[0].nlg != r[1].nlg || memcmp(lg[0], lg[1], r[0].nlg * 4)) fail(f, i, "rdClip_CalcOutcode2 calls", n);
                else if (r[0].cw != r[1].cw) fail(f, i, "x87 control word", n);
                else if (((r[0].sw >> 11) & 7) != ((r[1].sw >> 11) & 7)) fail(f, i, "x87 stack top", n);
                else if (knan) {
                    /* only NaN bits differ: allowed when an input is a signalling NaN (see the header) */
                    if (has_snan(f, n)) nanonly++;
                    else { fail(f, i, "NaN payload without a signalling NaN input", n); dump(f, n); }
                }
            }
            if (r[0].ret) nonzero++;
            if (f > 0 && *(uint *)DATA(0x7f4ac4) != 0) clipped++;
            for (j = 0; f > 0 && j < 8; j++) if (*(uint *)DATA(0x7f4ac4) & (1u << j)) bits[j]++;
            if (f == 0 && r[1].nlg > 6) loops++;
        }
        printf("%-20s %ld cases, %ld differences, %ld NaN-payload-only with a signalling NaN input (return != 0: %ld, flags != 0: %ld)\n",
               fname[f], cases, fails - fb, nanonly, nonzero, clipped);
        if (f == 0) printf("    cases with more than one clip step: %ld\n", loops);
        else printf("    flag bits 1/2/4/8/10/20/40: %ld %ld %ld %ld %ld %ld %ld\n", bits[0], bits[1], bits[2], bits[3], bits[4], bits[5], bits[6]);
    }
    printf("total differences: %ld\n", fails);
    return fails != 0;
}
