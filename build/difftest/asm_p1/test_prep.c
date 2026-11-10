/* Differential test: rdActive_AddActiveFace (0x00405770).  Random face records as in test_light.c plus the
 * colour-key flag of the cel, the z-buffer mode and the polygon count; the 15 rdRaster_Select_* selectors and the
 * face callback (+0x18, the patched entry of an unrelated function, 0x0040aa20) are recorders (3 argument words
 * logged: the level is the third). */
#include "harness.h"
#define FACE  0x30000100u
#define MAT   0x30000200u
#define CELS  0x30000400u
#define KEYS  0x30000800u
#define VERTS 0x30001000u
#define CB    0x40aa20u
static const uint32_t sels[] = {0x0040f5f0, 0x0040fa20, 0x0040fe90, 0x00410290, 0x004108b0, 0x00411270, 0x00411630,
    0x00412090, 0x004124f0, 0x00413040, 0x004134a0, 0x00413ce0, 0x00414be0, 0x004154c0, 0x00416470, 0x00416e70};
static int quant;
static float rf(void)
{
    if (quant && (rnd() & 3)) return ((int)rndn(13) - 4) / 4.0f;
    switch (rnd() & 15) {
    case 0: { uint32_t u = 0x7fc00000u | (rnd() & 0x80000000u); return *(float *)&u; }
    case 1: { uint32_t u = rnd() & 0x807fffffu; return *(float *)&u; }
    case 2: { uint32_t u = 0x7f800000u | (rnd() & 0x80000000u); return *(float *)&u; }
    case 3: { uint32_t u = 0x80000000u; return *(float *)&u; }
    case 4: return 1.0f;
    case 5: return 0.0f;
    default: return ((int)rndn(3000001) - 1000000) / 1500000.0f;
    }
}
#define SF(a) do { float f_ = rf(); GF(a) = f_; } while (0)
static void setup(int *args)
{
    quant = rnd() & 1;
    G(0x5e6f3c) = (rnd() & 15) ? (int)rndn(0x400) : 0x3fe + (int)rndn(4);
    G(0x5e6f98) = rnd();
    fill_rand(FACE, 0x50);
    G(FACE + 8) = (int)rndn(7) - 1; G(FACE + 0xc) = (int)rndn(7) - 1; G(FACE + 0x10) = (int)rndn(5) - 1;
    G(0x900008) = (int)rndn(6); G(0x900000) = (int)rndn(6); G(0x900060) = (int)rndn(4);
    if (rnd() & 1) { G(FACE + 8) = 4; G(0x900008) = 5; G(0x900060) = 3; }   /* textured: the four selector groups */
    if (G(0x5e6f3c) < 0x400) fill_rand(0x565f38 + G(0x5e6f3c) * 0x204, 0x204);
    G(0x900050) = (rnd() & 3) ? 1 : (int)rndn(3);
    G(FACE + 0x18) = CB;
    G(FACE + 0x38) = (rnd() & 7) ? (int)MAT : 0;
    G(FACE + 0x3c) = (rnd() & 1) ? -1 : (int)rndn(8) - 2;
    fill_rand(MAT, 0x80);
    for (int i = 0; i < 8; i++) {
        uint32_t c = CELS + 0x40 * i;
        G(MAT + 0x68 + 4 * i) = c; fill_rand(c, 0x40); G(c + 0x1c) = KEYS + 4 * i; G(KEYS + 4 * i) = rnd();
    }
    G(MAT + 0x60) = 1 + rndn(5); G(MAT + 0x64) = (int)rndn(8) - 2;
    G(0x900064) = rnd();
    SF(FACE + 0x40); SF(FACE + 0x44); SF(FACE + 0x48);
    int n = rndn(10);
    G(FACE + 0x1c) = n; G(FACE + 0x28) = VERTS;
    for (int i = 0; i < 10; i++) SF(VERTS + 4 * i);
    args[0] = FACE;
}
extern void rdActive_AddActiveFace(void);
static const Fn fns[] = {{"rdActive_AddActiveFace", 0x405770, (void *)rdActive_AddActiveFace, setup, 1}};
int main(int argc, char **argv)
{
    rt_init();
    rt_patch(CB, 1, 0); rec_nargs[1] = 3;
    for (int i = 0; i < 16; i++) {
        uint32_t s = sels[i];
        rt_patch(s, 2 + i, 0);
        /* the lit selectors take the level as a third argument */
        rec_nargs[2 + i] = (s == 0x40fe90 || s == 0x411630 || s == 0x412090 || s == 0x414be0 || s == 0x4154c0) ? 3 : 2;
    }
    fill_rand(0x30000000, ARENA_SZ);
    return run_all(fns, 1, argc > 1 ? atol(argv[1]) : 1000, 0);
}
