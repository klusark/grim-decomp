/* Differential test of the five face clippers of build/overrides_asm_q2.c against the original machine code
 * (orig_rdClip_Face3_*, sliced from the asm_funcs.s of 2df265d).
 * Build and run: build/difftest/asm_q2/run_all.sh [cases per function]
 *
 * Each case builds a frustum record (perspective slopes f[8], f[10..12], orthographic constants f[3..6], near f[1], far
 * f[2], far enable f[0]), a polygon of -1..10 vertices (positions, uv, intensities) and a start state of the static work
 * area 0x007f4600..0x007f4ad0 (the uv / intensity / position buffers, the buffer pointer globals and the clip flags at
 * 0x007f4ac4), then runs the original and the C on the same state, under the x87 precision control 24, 53 or 64 bits.
 * Compared: the return value (EAX), the caller's arrays, the whole work area, the x87 control word and stack top.
 * Values: random floats, small integers and halves (exact ties), vertices placed exactly on a plane (x = float(k*y),
 * x = c, y = near ...), 0, -0, +-inf, quiet and signalling NaN, denormals; slopes include 0, +-1, 0.5, 2 and NaN.
 * A difference where every differing dword is a NaN on both sides is counted separately as "NaN-payload-only"
 * (Q2_NOSNAN=1: no signalling NaN inputs). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

typedef uint32_t fn4(int *, float *, float *, int);
typedef uint32_t fn5(int *, float *, float *, float *, int);
extern fn4 orig_rdClip_Face3GS, rdClip_Face3GS;
extern fn4 orig_rdClip_Face3T, rdClip_Face3T;
extern fn4 orig_rdClip_Face3TOrtho, rdClip_Face3TOrtho;
extern fn5 orig_rdClip_Face3GT, rdClip_Face3GT;
extern fn5 orig_rdClip_Face3GTOrtho, rdClip_Face3GTOrtho;
extern uint32_t g_dwDestVert;

static uint64_t seed = 0x9E3779B97F4A7C15ull;
static uint32_t rnd(void) { seed ^= seed << 13; seed ^= seed >> 7; seed ^= seed << 17; return (uint32_t)(seed >> 11); }
static uint32_t R(uint32_t n) { return n ? rnd() % n : 0; }
static int nosnan;

static float bits(uint32_t u) { union { uint32_t u; float f; } v; v.u = u; return v.f; }
static uint32_t ubits(float f) { union { uint32_t u; float f; } v; v.f = f; return v.u; }

static float special(void)
{
    switch (R(9)) {
    case 0: return 0.0f;
    case 1: return -0.0f;
    case 2: return bits(0x7f800000u);
    case 3: return bits(0xff800000u);
    case 4: return bits((R(2) ? 0x7fc00000u : 0xffc00000u) | R(0x400000));          /* quiet NaN */
    case 5: if (!nosnan) return bits((R(2) ? 0x7f800001u : 0xff800001u) + R(0x3fffff)); /* signalling NaN */
            return bits(0x7fc00000u);
    case 6: return bits((R(2) ? 0x00000001u : 0x80000001u) + R(0x7fffff));          /* denormal */
    case 7: return bits(0x00800000u | (R(2) << 31));                                  /* smallest normal */
    default: return bits(0x7f7fffffu | (R(2) << 31));                                 /* largest finite */
    }
}
static float rf(float lo, float hi) { return lo + (hi - lo) * (float)(rnd() & 0xffffff) / 16777216.0f; }
/* a coordinate: mostly random, often a small integer / half (ties), sometimes special */
static float coord(float range, int specials)
{
    uint32_t r = R(100);
    if (r < (uint32_t)specials) return special();
    if (r < 40) return (float)((int)R(41) - 20) * 0.5f;
    if (r < 45) return (float)((int)R(9) - 4);
    return rf(-range, range);
}
static float slope(int specials)
{
    static const float simple[] = {1.0f, -1.0f, 0.5f, -0.5f, 2.0f, -2.0f, 0.75f, -0.75f, 0.0f, -0.0f, 1.25f};
    uint32_t r = R(100);
    if (r < (uint32_t)specials) return special();
    if (r < 40) return simple[R(11)];
    return rf(-3.0f, 3.0f);
}

/* ---- memory both versions work on ---- */
#define NV 512
#define WA_LO 0x007f4600u
#define WA_HI 0x007f4ad0u
static struct mem {
    int frustum[16];
    float pos[NV * 3], uv[NV * 2], li[NV];
    uint8_t wa[WA_HI - WA_LO];
} m0, mo;
static uint8_t *wa_ptr(void) { return (uint8_t *)&g_dwDestVert - (0x007f46acu - WA_LO); }

static uint16_t get_sw(void) { uint16_t sw; __asm__ volatile("fnstsw %0" : "=m"(sw)); return sw; }
static uint16_t get_cw(void) { uint16_t cw; __asm__ volatile("fnstcw %0" : "=m"(cw)); return cw; }
static void fpu_reset(uint16_t cw) { __asm__ volatile("fninit"); __asm__ volatile("fldcw %0" : : "m"(cw)); }

static struct mem cur;
static uint32_t call(int fi, int side, int n)
{
    static fn4 *o4[] = {orig_rdClip_Face3GS, orig_rdClip_Face3T, orig_rdClip_Face3TOrtho};
    static fn4 *c4[] = {rdClip_Face3GS, rdClip_Face3T, rdClip_Face3TOrtho};
    switch (fi) {
    case 0: return (side ? c4[0] : o4[0])(cur.frustum, cur.pos, cur.li, n);
    case 1: case 2: return (side ? c4[fi] : o4[fi])(cur.frustum, cur.pos, cur.uv, n);
    case 3: return (side ? rdClip_Face3GT : orig_rdClip_Face3GT)(cur.frustum, cur.pos, cur.uv, cur.li, n);
    default: return (side ? rdClip_Face3GTOrtho : orig_rdClip_Face3GTOrtho)(cur.frustum, cur.pos, cur.uv, cur.li, n);
    }
}
static const char *fname[] = {"PosUvLit", "PosUvLit_2", "PosUvFlags", "PosUvLitColor", "PosUvLitFlags"};
static const int is_persp[] = {1, 1, 0, 1, 0};

static int isnan_u(uint32_t u) { return (u & 0x7f800000u) == 0x7f800000u && (u & 0x7fffffu); }

int main(int argc, char **argv)
{
    int cases = argc > 1 ? atoi(argv[1]) : 100000;
    int only = argc > 2 ? atoi(argv[2]) : -1;
    int fi, total_bad = 0;
    nosnan = getenv("Q2_NOSNAN") != 0;
    if (getenv("Q2_SEED")) seed ^= strtoull(getenv("Q2_SEED"), 0, 0);

    for (fi = 0; fi < 5; fi++) {
        int k, bad = 0, nanonly = 0, shown = 0;
        long hist[8] = {0}, flagseen = 0, fbit[7] = {0};
        if (only >= 0 && fi != only) continue;
        for (k = 0; k < cases; k++) {
            static const uint16_t pcs[3] = {0x007f, 0x027f, 0x037f};
            uint16_t cw0 = pcs[R(3)], cw[2], sw[2];
            uint32_t ret[2];
            int n, i, sp = R(4) == 0 ? 8 : (R(2) ? 1 : 0), side;
            float *f = (float *)m0.frustum;
            uint8_t *wa = wa_ptr();

            /* frustum */
            for (i = 0; i < 16; i++) m0.frustum[i] = rnd();
            m0.frustum[0] = R(3) == 0 ? 0 : (R(4) ? 1 : (int)rnd());
            f[1] = R(3) == 0 ? (float)((int)R(5) - 1) : (R(20) < (uint32_t)sp ? special() : rf(-2.0f, 3.0f));
            f[2] = R(3) == 0 ? (float)((int)R(12)) : (R(20) < (uint32_t)sp ? special() : rf(1.0f, 12.0f));
            f[3] = R(20) < (uint32_t)sp ? special() : (R(2) ? (float)-(int)R(6) : rf(-6.0f, 1.0f));
            f[5] = R(20) < (uint32_t)sp ? special() : (R(2) ? (float)(int)R(6) : rf(-1.0f, 6.0f));
            f[4] = R(20) < (uint32_t)sp ? special() : (R(2) ? (float)(int)R(6) : rf(-1.0f, 6.0f));
            f[6] = R(20) < (uint32_t)sp ? special() : (R(2) ? (float)-(int)R(6) : rf(-6.0f, 1.0f));
            f[12] = R(4) ? -(float)fabsf(slope(sp)) : slope(sp);
            f[10] = R(4) ? (float)fabsf(slope(sp)) : slope(sp);
            f[11] = R(4) ? (float)fabsf(slope(sp)) : slope(sp);
            f[8] = R(4) ? -(float)fabsf(slope(sp)) : slope(sp);
            if (R(50) == 0) for (i = 1; i < 16; i++) if (i != 7 && i != 9) f[i] = special();

            /* polygon */
            n = R(30) == 0 ? (int)R(3) - 1 : 3 + (int)R(R(4) ? 3 : 8);
            for (i = 0; i < NV * 3; i++) m0.pos[i] = bits(0x4b000000u + i);
            for (i = 0; i < NV * 2; i++) m0.uv[i] = bits(0x4c000000u + i);
            for (i = 0; i < NV; i++) m0.li[i] = bits(0x4d000000u + i);
            {
                float scale = R(4) ? 10.0f : (R(2) ? 1e-3f : 1e6f);
                int vis = R(2), tiny = R(12) == 0;
                if (tiny) {             /* denormal geometry: den = k*dyF - daF can be non-zero and round to 0 */
                    static const float ks[] = {0.5f, -0.5f, 1.5f, -1.5f, 0.25f};
                    f[12] = ks[R(5)]; f[10] = ks[R(5)]; f[11] = ks[R(5)]; f[8] = ks[R(5)];
                    if (R(2)) { f[1] = bits(R(4)); m0.frustum[0] = 0; }
                }
                for (i = 0; i < (n > 0 ? n : 1); i++) {
                    float *p = &m0.pos[i * 3];
                    p[0] = coord(scale, sp);
                    p[1] = R(4) ? (coord(scale, sp) + scale * 0.5f) : coord(scale, sp);
                    p[2] = coord(scale, sp);
                    if (vis) {          /* mostly inside the view: y in front, |x|, |z| about y */
                        p[1] = rf(0.25f, 9.0f);
                        p[0] = rf(-1.6f, 1.6f) * p[1];
                        p[2] = rf(-1.6f, 1.6f) * p[1];
                        if (!is_persp[fi]) { p[0] = rf(-7.0f, 7.0f); p[2] = rf(-7.0f, 7.0f); }
                        if (R(20) < (uint32_t)sp) p[R(3)] = special();
                    }
                    switch (R(10)) {    /* exactly on a plane */
                    case 0: p[0] = (float)((long double)f[12] * p[1]); break;
                    case 1: p[0] = (float)((long double)f[10] * p[1]); break;
                    case 2: p[2] = (float)((long double)f[11] * p[1]); break;
                    case 3: p[2] = (float)((long double)f[8] * p[1]); break;
                    case 4: p[1] = R(2) ? f[1] : f[2]; break;
                    case 5: p[R(2) * 2] = f[3 + R(4)]; break;
                    default: break;
                    }
                    if (tiny) {             /* small multiples of the smallest denormal */
                        int j;
                        for (j = 0; j < 3; j++) p[j] = bits(R(6) | (R(2) << 31));
                        if (R(2)) p[1] = bits(R(6));
                    }
                    m0.uv[i * 2] = coord(4.0f, sp / 2);
                    m0.uv[i * 2 + 1] = coord(4.0f, sp / 2);
                    m0.li[i] = R(3) ? rf(0.0f, 1.0f) : coord(1.0f, sp / 2);
                }
            }
            /* work area: random garbage, so stale values show */
            for (i = 0; i < (int)sizeof m0.wa; i += 4) {
                uint32_t v = 0x3f000000u + R(0x1000000);
                memcpy(&m0.wa[i], &v, 4);
            }

            for (side = 0; side < 2; side++) {
                cur = m0;
                memcpy(wa, m0.wa, sizeof m0.wa);
                fpu_reset(cw0);
                ret[side] = call(fi, side, n);
                sw[side] = get_sw();
                cw[side] = get_cw();
                fpu_reset(0x037f);
                memcpy(cur.wa, wa, sizeof cur.wa);
                if (side == 0) mo = cur;
            }
            /* compare (cur is the C's state, mo the original's) */
            {
                const char *why = 0;
                int allnan = 1, j;
                const uint32_t *A = (const uint32_t *)&mo, *B = (const uint32_t *)&cur;
                if (ret[0] != ret[1]) why = "return value";
                else if (cw[0] != cw[1]) why = "x87 control word";
                else if ((sw[0] ^ sw[1]) & 0x3800) why = "x87 stack top";
                else if (memcmp(&mo, &cur, sizeof mo)) {
                    why = "memory";
                    for (j = 0; j < (int)(sizeof mo / 4); j++)
                        if (A[j] != B[j] && !(isnan_u(A[j]) && isnan_u(B[j]))) { allnan = 0; break; }
                }
                if (why && !strcmp(why, "memory") && allnan) {
                    nanonly++;
                } else if (why) {
                    bad++;
                    if (shown++ < 6) {
                        printf("%s case %d: n=%d far=%d cw=%04x: %s (ret %u / %u)\n", fname[fi], k, n, m0.frustum[0], cw0, why,
                               ret[0], ret[1]);
                        for (j = 0; j < (int)(sizeof mo / 4); j++)
                            if (A[j] != B[j]) {
                                uint32_t off = j * 4;
                                const char *rg = off < 64 ? "frustum" : off < 64 + NV * 12 ? "pos" : off < 64 + NV * 20 ? "uv"
                                                 : off < 64 + NV * 24 ? "li" : "workarea";
                                uint32_t rel = off < 64 + NV * 24 ? (off < 64 ? off : off < 64 + NV * 12 ? off - 64
                                               : off < 64 + NV * 20 ? off - 64 - NV * 12 : off - 64 - NV * 20)
                                               : WA_LO + off - (64 + NV * 24);
                                printf("   %s +%x: orig %08x (%g)  C %08x (%g)\n", rg, rel, A[j], bits(A[j]), B[j], bits(B[j]));
                                if (++shown > 40) break;
                            }
                        printf("   frustum:");
                        for (j = 0; j < 13; j++) printf(" %g", f[j]);
                        printf("\n   in:");
                        for (j = 0; j < (n > 0 ? n : 0); j++) printf(" (%g %g %g)", m0.pos[3 * j], m0.pos[3 * j + 1], m0.pos[3 * j + 2]);
                        printf("\n");
                    }
                }
                hist[ret[0] < 7 ? ret[0] : 7]++;
                {
                    uint32_t fl = *(uint32_t *)&mo.wa[0x7f4ac4 - WA_LO];
                    if (fl & 0x3f) flagseen++;
                    for (j = 0; j < 7; j++) if (fl & (1u << j)) fbit[j]++;
                }
            }
        }
        printf("%-14s %d cases, %d differences, %d NaN-payload-only; results 0..6+: %ld %ld %ld %ld %ld %ld %ld %ld; clipped %ld\n",
               fname[fi], cases, bad, nanonly, hist[0], hist[1], hist[2], hist[3], hist[4], hist[5], hist[6], hist[7], flagseen);
        printf("               plane flags 01 02 04 08 10 20 40: %ld %ld %ld %ld %ld %ld %ld\n", fbit[0], fbit[1], fbit[2],
               fbit[3], fbit[4], fbit[5], fbit[6]);
        total_bad += bad + nanonly;
        (void)is_persp;
    }
    return total_bad != 0;
}
