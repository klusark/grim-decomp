/* Differential test of rdPrimit3_ClipFace (0x0040deb0, the C block in build/overrides_logic.c) against the original machine
 * code (orig_rdPrimit3_ClipFace, sliced from the baseline asm_funcs.s of commit 1b0b2d2^).
 * Build and run: build/difftest/clipface/run.sh [cases]
 *
 * Each case picks the geometry mode (param_2 0..4 plus out-of-range values), the lighting mode (param_3 -1..4), the camera
 * projection type (0, 1, 2), a vertex count 0..24, random index arrays and random position / uv / intensity pools, with and
 * without the per-vertex extra intensity array (src[6]).  Both versions run on the same start state.  The ten rdClip_Face3_*
 * clippers are stand-ins that log their name and arguments and return a random count in EAX (like the real ones, which leave
 * the x87 stack empty).  Compared: the call log, the output count (dst[0]) and all of dst / src headers, the whole position /
 * uv / intensity output buffers, the x87 control word, the x87 stack depth (TOP) and the invalid / stack fault flags. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern void *g_pRdCurrentCamera;

typedef void clipface_fn(void *, int, int, int, uint32_t *, uint32_t *, float *);
extern clipface_fn orig_rdPrimit3_ClipFace, rdPrimit3_ClipFace;

static uint64_t seed = 0x2545F4914F6CDD1Dull;
static uint32_t rnd(void) { seed ^= seed << 13; seed ^= seed >> 7; seed ^= seed << 17; return (uint32_t)(seed >> 11); }
static uint32_t R(uint32_t n) { return n ? rnd() % n : 0; }
static float F(float lo, float hi)
{
    union { uint32_t u; float f; } v;
    switch (R(24)) {        /* edge values of the clamps */
    case 0: return 0.0f;
    case 1: return 1.0f;
    case 2: return -0.0f;
    case 3: v.u = 0x7fc00000u | R(0x400000); return v.f;            /* quiet NaN */
    case 4: v.u = 0x7f800000u; return v.f;                          /* +inf */
    case 5: v.u = 0xff800000u; return v.f;                          /* -inf */
    case 6: v.u = 0x3f800000u + R(3) - 1; return v.f;               /* just around 1 */
    case 7: v.u = R(2) ? 0x00000001u + R(8) : 0x80000001u + R(8); return v.f;   /* denormals */
    default: return lo + (hi - lo) * (float)(rnd() & 0xffffff) / 16777216.0f;
    }
}

/* ---- the call log ---- */
struct call { int id, n; uint32_t a[5]; uint32_t ret; };
static struct call logbuf[2][8];
static int nlog[2], side;
static uint32_t retval;
static void rec(int id, int n, uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4)
{
    struct call *c;
    if (nlog[side] >= 8) return;
    c = &logbuf[side][nlog[side]++];
    c->id = id; c->n = n; c->a[0] = a0; c->a[1] = a1; c->a[2] = a2; c->a[3] = a3; c->a[4] = a4; c->ret = retval;
}
static const char *names[] = {"?", "Pos", "PosB", "Pos_2", "PosB_2", "PosUvLit", "PosUv", "PosUvLit_2", "PosUvFlags",
                              "PosUvLitColor", "PosUvLitFlags"};
#define C3(nm, id) uint32_t rdClip_Face3_##nm(uint32_t a, uint32_t b, uint32_t c) { rec(id, 3, a, b, c, 0, 0); return retval; }
#define C4(nm, id) uint32_t rdClip_Face3_##nm(uint32_t a, uint32_t b, uint32_t c, uint32_t d) { rec(id, 4, a, b, c, d, 0); return retval; }
#define C5(nm, id) uint32_t rdClip_Face3_##nm(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e) { rec(id, 5, a, b, c, d, e); return retval; }
C3(Pos, 1) C3(PosB, 2) C3(Pos_2, 3) C3(PosB_2, 4)
C4(PosUvLit, 5) C4(PosUv, 6) C4(PosUvLit_2, 7) C4(PosUvFlags, 8)
C5(PosUvLitColor, 9) C5(PosUvLitFlags, 10)

/* ---- the memory both versions work on ---- */
#define NV 64
static struct mem {
    uint32_t src[8], dst[8];
    int vidx[NV], uvidx[NV];
    float pos[NV * 3], uv[NV * 2], light[NV], extra[NV];
    float opos[NV * 3], ouv[NV * 2], olight[NV];
    float off[2];
    int cam[4];
    uint32_t frustum[4];
} m0, m[2];

static void setup(struct mem *s, int extra_on)
{
    s->src[0] = 0;           /* filled by the caller */
    s->src[1] = (uint32_t)s->vidx;
    s->src[2] = (uint32_t)s->uvidx;
    s->src[3] = (uint32_t)s->pos;
    s->src[4] = (uint32_t)s->uv;
    s->src[5] = (uint32_t)s->light;
    s->src[6] = extra_on ? (uint32_t)s->extra : 0;
    s->src[7] = 0xa5a5a5a5;
    s->dst[0] = 0xdeadbeef;
    s->dst[1] = 0x11111111;
    s->dst[2] = 0x22222222;
    s->dst[3] = (uint32_t)s->opos;
    s->dst[4] = (uint32_t)s->ouv;
    s->dst[5] = (uint32_t)s->olight;
    s->dst[6] = 0x66666666;
    s->dst[7] = 0x77777777;
}

/* x87 state after a call: control word, status word */
static void fpu_state(uint16_t *cw, uint16_t *sw)
{
    __asm__ volatile("fnstcw %0" : "=m"(*cw));
    __asm__ volatile("fnstsw %0" : "=m"(*sw));
}
static void fpu_reset(uint16_t cw)
{
    __asm__ volatile("fninit");
    __asm__ volatile("fldcw %0" : : "m"(cw));
}

int main(int argc, char **argv)
{
    int cases = argc > 1 ? atoi(argv[1]) : 200000, diffs = 0, k, i, shown = 0;
    int hist[6][6] = {{0}};
    void *savedcam = g_pRdCurrentCamera;

    for (k = 0; k < cases; k++) {
        int p2, p3, n, extra_on = R(2);
        uint16_t cw0 = R(2) ? 0x027f : 0x037f, cw[2], sw[2];
        uint32_t dst_sum = 0;

        p2 = R(12) == 0 ? (int)R(8) - 2 : (int)R(5);     /* mostly 0..4, sometimes -2..5 */
        p3 = R(12) == 0 ? (int)R(6) - 1 : (int)R(4);     /* mostly 0..3, sometimes -1..4 */
        n = R(8) == 0 ? 0 : 1 + R(24);
        memset(&m0, 0, sizeof m0);
        for (i = 0; i < NV; i++) {
            m0.vidx[i] = R(NV);
            m0.uvidx[i] = R(NV);
            m0.light[i] = F(-0.6f, 1.6f);
            m0.extra[i] = F(-0.8f, 0.8f);
            m0.uv[2 * i] = F(-4, 4); m0.uv[2 * i + 1] = F(-4, 4);
            m0.pos[3 * i] = F(-10, 10); m0.pos[3 * i + 1] = F(-10, 10); m0.pos[3 * i + 2] = F(-10, 10);
            m0.ouv[2 * i] = m0.ouv[2 * i + 1] = m0.olight[i] = -123.0f - (float)i;
            m0.opos[3 * i] = m0.opos[3 * i + 1] = m0.opos[3 * i + 2] = 777.0f + (float)i;
        }
        m0.off[0] = F(-1, 1); m0.off[1] = F(-1, 1);
        m0.cam[0] = R(3);                                   /* 0 orthographic, 1 perspective, 2 other */
        retval = rnd();

        for (side = 0; side < 2; side++) {
            m[side] = m0;
            setup(&m[side], extra_on);
            m[side].src[0] = n;
            nlog[side] = 0;
            g_pRdCurrentCamera = m[side].cam;
            fpu_reset(cw0);
            (side ? rdPrimit3_ClipFace : orig_rdPrimit3_ClipFace)(m[side].frustum, p2, p3, 0x4444, m[side].src,
                                                                    m[side].dst, m[side].off);
            fpu_state(&cw[side], &sw[side]);
            fpu_reset(0x037f);
        }
        g_pRdCurrentCamera = savedcam;

        /* compare: pointers inside m[1] are shifted by the distance between the two copies */
        {
            int bad = 0;
            const char *why = "";
            uint32_t delta = (uint32_t)((char *)&m[1] - (char *)&m[0]);
            if (nlog[0] != nlog[1]) { bad = 1; why = "call count"; }
            for (i = 0; !bad && i < nlog[0]; i++) {
                struct call *a = &logbuf[0][i], *b = &logbuf[1][i];
                int j;
                if (a->id != b->id || a->n != b->n) { bad = 1; why = "callee"; break; }
                for (j = 0; j < a->n; j++) {
                    uint32_t x = a->a[j], y = b->a[j];
                    int inmem = x >= (uint32_t)&m[0] && x < (uint32_t)(&m[0] + 1);
                    if (inmem ? y - x != delta : x != y) { bad = 1; why = "callee argument"; break; }
                }
            }
            if (!bad && m[0].dst[0] != m[1].dst[0]) { bad = 1; why = "output count dst[0]"; }
            if (!bad && (memcmp(m[0].opos, m[1].opos, sizeof m0.opos) || memcmp(m[0].ouv, m[1].ouv, sizeof m0.ouv) ||
                         memcmp(m[0].olight, m[1].olight, sizeof m0.olight))) { bad = 1; why = "output buffers"; }
            for (i = 1; !bad && i < 8; i++)
                if ((i >= 3 && i <= 5) ? m[1].dst[i] - m[0].dst[i] != delta : m[1].dst[i] != m[0].dst[i]) { bad = 1; why = "dst header"; }
            if (!bad && (cw[0] != cw[1])) { bad = 1; why = "x87 control word"; }
            if (!bad && ((sw[0] ^ sw[1]) & 0x3841)) { bad = 1; why = "x87 stack depth / invalid / stack fault"; }
            if (bad) {
                diffs++;
                if (shown++ < 12) {
                    printf("case %d: p2=%d p3=%d cam=%d n=%d extra=%d: %s\n", k, p2, p3, m0.cam[0], n, extra_on, why);
                    for (side = 0; side < 2; side++) {
                        printf("  %s: dst[0]=%08x sw=%04x cw=%04x calls:", side ? "C   " : "orig", m[side].dst[0], sw[side], cw[side]);
                        for (i = 0; i < nlog[side]; i++) printf(" %s/%d", names[logbuf[side][i].id], logbuf[side][i].n);
                        printf("\n");
                    }
                }
            }
            if (p2 >= 0 && p2 <= 4 && p3 >= 0 && p3 <= 3) hist[p2][p3]++;
            (void)dst_sum;
        }
    }
    printf("cases per (param_2, param_3):\n");
    for (i = 0; i < 5; i++) printf("  p2=%d: %6d %6d %6d %6d\n", i, hist[i][0], hist[i][1], hist[i][2], hist[i][3]);
    printf("%d cases, %d differences\n", cases, diffs);
    return diffs != 0;
}
