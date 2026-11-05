/* Differential test: edge stepping functions (x87, rounding with the control words of Services_SetCurrent). */
#include "harness.h"
#define VERTS 0x30002000u
#define UVS   0x30003000u
#define LVS   0x30004000u
#define PVS   0x30005000u
#define EDGE  0x30001000u
static float rf(float lo, float hi)
{
    float f = lo + (hi - lo) * (float)(rnd() & 0xffffff) / 16777216.0f;
    switch (rnd() & 7) {
    case 0: return (float)(int)f;               /* integral */
    case 1: return (float)(int)f + 0.5f;
    default: return f;
    }
}
static void setup(int *a)
{
    int n = 3 + rndn(6);
    unsigned short base = (rnd() & 1) ? 0x027f : ((rnd() & 1) ? 0x007f : 0x037f);
    *(unsigned short *)0x900524 = base;
    *(unsigned short *)0x90052a = (unsigned short)(0x0b00 | (base & 0xff));
    *(unsigned short *)0x900526 = (unsigned short)(0x0700 | (base & 0xff));
    *(unsigned short *)0x900528 = (unsigned short)(0x0c00 | (base & 0xff));
    G(0x7f424c) = n; G(0x7f4308) = VERTS; G(0x7f4398) = UVS; G(0x7f4304) = LVS;
    G(0x7f42ec) = (rnd() & 1) ? 1 : -1; G(0x7f4394) = -G(0x7f42ec);
    G(0x7f42fc) = rndn(n);
    float ybase = rf(-20, 480);
    for (int i = 0; i < 16; i++) {
        GF(VERTS + 12 * i) = rf(-50, 700);
        GF(VERTS + 12 * i + 4) = (rnd() & 3) ? rf(-20, 500) : ybase + rf(0, 3);
        GF(VERTS + 12 * i + 8) = rf(0.1f, 100);
        GF(UVS + 8 * i) = rf(-10, 300); GF(UVS + 8 * i + 4) = rf(-10, 300);
        GF(LVS + 4 * i) = rf(0, 64);
        GF(0x7f43c8 + 4 * i) = rf(0, 2); GF(0x7f4260 + 4 * i) = rf(-100, 100); GF(0x7f4310 + 4 * i) = rf(-100, 100);
    }
    for (uint32_t g = 0x8ddec4; g <= 0x8ddef4; g += 4)
        if (g == 0x8ddec4 || g == 0x8ddec8 || g == 0x8ddedc || g == 0x8ddee0 || g == 0x8ddef0 || g == 0x8ddef4)
            GF(g) = rf(-3, 3);
    for (int i = 0; i < 0x44; i += 4) G(EDGE + i) = rnd();
    G(EDGE + 0xc) = rndn(n);
    a[0] = EDGE;
}
#define F(n, addr) extern void n(void);
#include "edge_list.h"
#undef F
#define F(n, addr) {#n, addr, (void *)n, setup, 1},
static const Fn fns[] = {
#include "edge_list.h"
};
int main(int argc, char **argv)
{
    rt_init();
    for (uint32_t i = 0; i < ARENA_SZ; i += 4) G(0x30000000 + i) = rnd();
    return run_all(fns, sizeof fns / sizeof fns[0], argc > 1 ? atol(argv[1]) : 1000, argc > 2 ? argv[2] : 0);
}
