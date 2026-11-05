/* Differential test: rdPrimit3_CopyFaceVerts (0x0040e500).  Random vertex pool records (index lists, positions,
 * uvs, intensities with values around [0, 1], NaN, infinities, denormals), every geometry mode -1..5 and lighting mode
 * -1..4, with and without the extra-intensity array. */
#include "harness.h"
#define SRC  0x30000100u
#define DST  0x30000200u
#define UVO  0x30000300u
#define IDX1 0x30001000u
#define IDX2 0x30002000u
#define POS  0x30010000u
#define UV   0x30020000u
#define INT  0x30030000u
#define EXT  0x30040000u
#define DPOS 0x30050000u
#define DUV  0x30060000u
#define DINT 0x30070000u
static float rf(void)
{
    switch (rnd() & 15) {
    case 0: { uint32_t u = 0x7fc00000u | (rnd() & 0x3fffff) | (rnd() & 0x80000000u); return *(float *)&u; }
    case 1: { uint32_t u = rnd() & 0x807fffffu; return *(float *)&u; }    /* denormal */
    case 2: { uint32_t u = 0x7f800000u | (rnd() & 0x80000000u); return *(float *)&u; }
    case 3: return 0.0f;
    case 4: return 1.0f;
    case 5: { uint32_t u = rnd(); return *(float *)&u; }
    default: return ((int)rndn(4000000) - 1000000) / 2000000.0f;
    }
}
static void setup(int *a)
{
    int n = rndn(24);
    uint32_t u;
    G(SRC) = n; G(SRC + 4) = IDX1; G(SRC + 8) = IDX2; G(SRC + 0xc) = POS; G(SRC + 0x10) = UV; G(SRC + 0x14) = INT;
    G(SRC + 0x18) = (rnd() & 1) ? EXT : 0;
    G(DST) = rnd(); G(DST + 0xc) = DPOS; G(DST + 0x10) = DUV; G(DST + 0x14) = DINT;
    for (int i = 0; i < 32; i++) { G(IDX1 + 4 * i) = rndn(64); G(IDX2 + 4 * i) = rndn(64); }
    for (int i = 0; i < 64 * 3; i++) G(POS + 4 * i) = rnd();
    for (int i = 0; i < 128; i++) { float f = rf(); GF(UV + 4 * i) = f; }
    for (int i = 0; i < 64; i++) { float f = rf(); GF(INT + 4 * i) = f; f = rf(); GF(EXT + 4 * i) = f; }
    for (int i = 0; i < 2; i++) { float f = rf(); GF(UVO + 4 * i) = f; }
    fill_rand(DPOS, 32 * 12); fill_rand(DUV, 32 * 8); fill_rand(DINT, 32 * 4);
    a[0] = (int)rndn(7) - 1; a[1] = (int)rndn(6) - 1; a[2] = rnd(); a[3] = SRC; a[4] = DST; a[5] = UVO;
    (void)u;
}
extern void rdPrimit3_CopyFaceVerts(void);
static const Fn fns[] = {
    {"rdPrimit3_CopyFaceVerts", 0x40e500, (void *)rdPrimit3_CopyFaceVerts, setup, 0},
};
int main(int argc, char **argv)
{
    rt_init();
    fill_rand(0x30000000, ARENA_SZ);
    return run_all(fns, 1, argc > 1 ? atol(argv[1]) : 1000, 0);
}
