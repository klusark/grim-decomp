/* Differential test: integer span functions (one scanline between two edge records). */
#include "harness.h"
#define CAM   0x30000100u
#define CAM4  0x30000200u
#define CANV  0x30000300u
#define E1    0x30001000u
#define E2    0x30001100u
#define FB    0x30010000u
#define TAB   0x30110000u
#define TEX   0x30210000u
static void fill_rand(uint32_t a, uint32_t n) { for (uint32_t i = 0; i < n; i += 4) G(a + i) = rnd(); }
/* globals of the rasteriser state block: random, small ones for shifts and masks; pointers into the arena */
static void common_setup(int *args, int bpp)
{
    G(0x7f0fc8) = CAM; G(CAM + 4) = CAM4; G(CAM4 + 4) = CANV;
    int pitch = 0x800;
    G(CANV + 0x18) = pitch; G(CANV + 0x24) = bpp; G(CANV + 0x5c) = FB;
    for (uint32_t a = 0x7f4200; a < 0x7f4500; a += 4) G(a) = rnd_edge();
    for (uint32_t a = 0x8ddea0; a < 0x8ddf10; a += 4) G(a) = rnd();
    for (int i = 0; i < 0x800; i++) G(0x8fbfc0 + 4 * i) = (rnd() & 3) ? (int)(0x10000 / (i ? i : 1)) : (int)rnd();
    /* pointer globals */
    G(0x8ddea8) = TAB + rndn(0x1000); G(0x8ddebc) = TAB + 0x20000 + rndn(0x1000); G(0x8dded4) = TAB + 0x50000 + rndn(0x1000);
    G(0x8ddeb0) = TAB + 0x60000 + rndn(0x1000);
    G(0x8ddee8) = TEX + rndn(0x1000); G(0x8ddeec) = TEX + rndn(0x1000);
    G(0x7f4300) = TEX + 0x80000 + rndn(0x10000); G(0x7f43a8) = FB + rndn(0x1000);
    /* shifts and masks */
    G(0x8ddee4) = rnd() & 7; G(0x8dded8) = rnd() & 15; G(0x8ddefc) = (rnd() & 1) ? 0x3f00 : rnd() & 0xff00;
    G(0x8ddecc) = (rnd() & 1) ? 0x00ff0000 : (int)(rnd() & 0x00ff0000);
    /* edge records */
    fill_rand(E1, 0x44); fill_rand(E2, 0x44);
    int xl = rndn(600) << 16 | (rnd() & 1 ? rnd() & 0xffff : 0);
    int w = (int)rndn(420) - 20;
    G(E1) = xl; G(E2) = xl + (w << 16) + (int)(rnd() & 0xffff) * (rnd() & 1);
    G(E1 + 0x40) = rndn(0x1e0); G(E2 + 0x40) = rndn(0x1e0);
    args[0] = E1; args[1] = E2;
}
static void s8(int *a) { common_setup(a, 8); }
static void s16(int *a) { common_setup(a, 16); }
#define F(n, addr, s) extern void n(void); 
#include "span_list.h"
#undef F
#define F(n, addr, s) {#n, addr, (void *)n, s, 0},
static const Fn fns[] = {
#include "span_list.h"
};
int main(int argc, char **argv)
{
    rt_init();
    fill_rand(0x30000000, ARENA_SZ);
    return run_all(fns, sizeof fns / sizeof fns[0], argc > 1 ? atol(argv[1]) : 1000, argc > 2 ? argv[2] : 0);
}
