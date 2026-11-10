/* Differential test: rdActive_BuildSpans (0x00404e00).  Random scanlines: a sorted list of edge crossings over a
 * few polygons (random crossing counts, sort keys with equal and different halves, z values on a coarse grid so that
 * ties occur, all material modes), a random fill level of the span table (rdCanvas_FlushSpans is a recorder that
 * empties it), and random control words in DAT_00900524 / 00900526. */
#include "harness.h"
#define CROSS  0x30000000u   /* crossing records, 0x60 apart */
#define POLY   0x30010000u   /* polygon records, 0x400 apart */
#define MODE   0x30020000u   /* mode records, 0x100 apart */
#define EDGE   0x30030000u   /* edge records, 0x60 apart */
#define LIST   0x30040000u   /* dummy span list tails */
#define SENT   0x5e6f40u
static float rq(void)
{
    if (rnd() & 1) return ((int)rndn(9) - 4) / 4.0f;
    switch (rnd() & 15) {
    case 0: { uint32_t u = 0x7fc00000u; return *(float *)&u; }
    case 1: return 0.0f;
    default: return ((int)rndn(2000001) - 1000000) / 100000.0f;
    }
}
#define SF(a) do { float f_ = rq(); GF(a) = f_; } while (0)
static uint32_t h_flush(uint32_t *a) { (void)a; G(0x4f6f2c) = 0; return 0; }
static void setup(int *args)
{
    int np = 1 + rndn(6), nc = rndn(14);
    G(0x5e6f38) = (rnd() & 15) != 0;
    G(0x4f6f2c) = (rnd() & 3) ? (int)rndn(40) : 0x7f8 + (int)rndn(9);
    G(0x50cf30) = rnd();
    static const uint16_t cws[4] = {0x027f, 0x067f, 0x0e7f, 0x047f};
    *(volatile uint16_t *)0x900524 = cws[rnd() & 3]; *(volatile uint16_t *)0x900526 = cws[rnd() & 3];
    for (int i = 0; i < np; i++) {
        uint32_t p = POLY + i * 0x400, m = MODE + i * 0x100;
        fill_rand(p, 0x204);
        fill_rand(m, 0x80);
        G(p) = m;
        static const int geo[4] = {4, 4, 3, 2};
        G(m + 8) = geo[rnd() & 3]; G(m + 0xc) = (rnd() & 1) ? 3 : (int)rndn(3); G(m + 0x10) = rndn(3);
        G(m + 0x74) = (rndn(4) << 16) | ((rnd() & 3) == 0);
        SF(p + 0x184); SF(p + 0x18c); SF(p + 0x194);
        G(p + 0x1b8) = (rnd() & 1) ? (int)(LIST + i * 0x40) : 0; G(p + 0x1bc) = LIST + i * 0x40;
        G(p + 0x1c0) = rndn(12);
        G(p + 0x1f4) = rndn(640) << 16;
        G(p + 0x1f8) = (rnd() & 3) ? 0 : (int)rndn(3) - 1;
        /* not linked at the start (random links can make the active list a cycle: both sides would hang) */
        G(p + 0x1fc) = 0;
        G(p + 0x200) = 0;
        for (int s = 0; s < 2; s++) {
            uint32_t e = EDGE + (i * 2 + s) * 0x60;
            fill_rand(e, 0x60);
            G(p + 0x1ec + 4 * s) = e;
            SF(e + 0x10); SF(e + 0x18); SF(e + 0x20);
            G(e + 0x28) = (rndn(640) << 16) | ((rnd() & 1) ? rnd() & 0xffff : 0);
            G(e + 0x30) = rnd() >> (rnd() & 15); G(e + 0x38) = rnd() >> (rnd() & 15); G(e + 0x40) = rnd() >> (rnd() & 15);
        }
    }
    uint32_t x = rndn(64) << 16;
    G(0x4f6f20) = nc ? CROSS : SENT;
    for (int c = 0; c < nc; c++) {
        uint32_t r = CROSS + c * 0x60;
        fill_rand(r, 0x60);
        G(r) = (rnd() & 1) ? (int)rnd() : 0;
        G(r + 4) = POLY + rndn(np) * 0x400;
        SF(r + 0x10);
        x += (rnd() & 3) ? (rndn(64) << 16) | ((rnd() & 1) ? rnd() & 0xffff : 0) : 0;
        if ((rnd() & 15) == 0) x -= rndn(64) << 16;   /* out of order: negative span widths */
        G(r + 0x28) = x;
        G(r + 0x50) = c + 1 < nc ? r + 0x60 : SENT;
    }
}
extern void rdActive_BuildSpans(void);
static const Fn fns[] = {{"rdActive_BuildSpans", 0x404e00, (void *)rdActive_BuildSpans, setup, 0}};
int main(int argc, char **argv)
{
    rt_init();
    rt_patch(0x4055d0, 1, 0); rec_handler[1] = h_flush;
    /* the 1/w tables */
    for (int i = 0; i < 0x800; i++) {
        float f = i ? 1.0f / i : 0.0f;
        GF(0x8fe000 + 4 * i) = f;
        G(0x8fbfc0 + 4 * i) = i ? 0x10000 / i : 0;
    }
    fill_rand(0x30000000, ARENA_SZ);
    return run_all(fns, 1, argc > 1 ? atol(argv[1]) : 1000, 0);
}
