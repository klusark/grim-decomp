/* Differential test: rdCache_DrawFaceUser (0x00409580).  Random face records (all mode combinations, the
 * renderer limits, materials with cel lists, intensities around [0, 1] with NaN / infinities / denormals / -0, per-
 * vertex arrays); the face's draw callback (+0x14) is a recorder (it is the patched entry of an unrelated function,
 * 0x0040aa20, which this test does not run). */
#include "harness.h"
#define FACE  0x30000100u
#define MAT   0x30000200u
#define CELS  0x30000400u
#define VERTS 0x30001000u
#define CB    0x40aa20u
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
    fill_rand(FACE, 0x50);
    G(FACE + 8) = (int)rndn(7) - 1; G(FACE + 0xc) = (int)rndn(7) - 1; G(FACE + 0x10) = (int)rndn(4) - 1;
    G(0x900008) = (int)rndn(6); G(0x900000) = (int)rndn(6); G(0x900060) = (int)rndn(4);
    G(FACE + 0x14) = CB;
    G(FACE + 0x38) = (rnd() & 3) ? (int)MAT : 0;
    G(FACE + 0x3c) = (rnd() & 1) ? -1 : (int)rndn(8) - 2;
    fill_rand(MAT, 0x80);
    for (int i = 0; i < 8; i++) { G(MAT + 0x68 + 4 * i) = CELS + 0x10 * i; G(CELS + 0x10 * i) = rnd(); }
    G(MAT + 0x60) = 1 + rndn(5); G(MAT + 0x64) = (int)rndn(8) - 2;
    G(0x900064) = rnd();
    SF(FACE + 0x40); SF(FACE + 0x44); SF(FACE + 0x48);
    int n = rndn(10);
    G(FACE + 0x1c) = n; G(FACE + 0x28) = VERTS;
    for (int i = 0; i < 10; i++) SF(VERTS + 4 * i);
    args[0] = FACE;
}
extern void rdCache_DrawFaceUser(void);
static const Fn fns[] = {{"rdCache_DrawFaceUser", 0x409580, (void *)rdCache_DrawFaceUser, setup, 1}};
int main(int argc, char **argv)
{
    rt_init();
    rt_patch(CB, 1, 0); rec_nargs[1] = 3;
    fill_rand(0x30000000, ARENA_SZ);
    return run_all(fns, 1, argc > 1 ? atol(argv[1]) : 1000, 0);
}
