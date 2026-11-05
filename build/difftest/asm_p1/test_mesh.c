/* Differential test: rdModel_DrawMesh (0x0040d230).  Random camera, model matrix, mesh, faces and lights; every
 * callee (Vec3_Sub, Matrix_Mul34, Matrix_TransformPoints, Matrix_Transpose, Frustum_TestSphere,
 * rdLight_CalcVertexIntensities, rdModel_AddMeshToCache) is a recorder.  Arguments that point to the caller's stack
 * are logged by content (their addresses differ between the two sides).  The recorders' results depend only on
 * their inputs. */
#include "harness.h"
#include <math.h>
#define CAM    0x30000000u
#define FRUST  0x30001000u
#define MESH   0x30002000u
#define MAT    0x30002100u
#define VERTS  0x30003000u
#define FACES  0x30004000u
#define IDX    0x30008000u
#define LIGHTS 0x30009000u
static uint32_t hsh(const uint32_t *w, int n) { uint32_t h = 2166136261u; for (int i = 0; i < n; i++) h = (h ^ w[i]) * 16777619u; return h; }
static void logp(uint32_t tag, uint32_t p, int n)
{
    uint32_t w[16];
    w[0] = is_stack(p) ? 0x5ac0000u : p;
    memcpy(w + 1, (void *)(uintptr_t)p, n * 4);
    rec_append(tag, w, n + 1);
}
static uint32_t h_vsub(uint32_t *a)
{
    logp(0x101, a[0], 0); logp(0x102, a[1], 3); logp(0x103, a[2], 12);
    volatile float *o = (float *)a[0], *x = (float *)a[1], *y = (float *)a[2];
    for (int i = 0; i < 3; i++) o[i] = x[i] - y[i];
    return 0;
}
static uint32_t h_mul34(uint32_t *a)
{
    logp(0x201, a[0], 0); logp(0x202, a[1], 12); logp(0x203, a[2], 12);
    uint32_t *o = (uint32_t *)a[0], *x = (uint32_t *)a[1], *y = (uint32_t *)a[2];
    for (int i = 0; i < 12; i++) o[i] = (x[i] & 0xffff0000u) | (y[(i + 3) % 12] & 0xffff);
    return 0;
}
static uint32_t h_xform(uint32_t *a)
{
    logp(0x301, a[0], 12); rec_append(0x302, a + 1, 3);
    return 0;
}
static uint32_t h_transpose(uint32_t *a)
{
    logp(0x401, a[0], 0); logp(0x402, a[1], 12);
    uint32_t *o = (uint32_t *)a[0], *m = (uint32_t *)a[1];
    for (int i = 0; i < 12; i++) o[i] = m[(i * 7) % 12];
    return 0;
}
static uint32_t h_frust(uint32_t *a)
{
    rec_append(0x501, a, 1); logp(0x502, a[1], 3); rec_append(0x503, a + 2, 1);
    uint32_t w[4] = {a[0], a[2]}; memcpy(w + 2, (void *)(uintptr_t)a[1], 8);
    return hsh(w, 4) % 3;
}
static uint32_t h_light(uint32_t *a)
{
    rec_append(0x601, a, 10);
    return hsh(a, 10) & 0x3f8fffffu;
}
static uint32_t h_add(uint32_t *a)
{
    rec_append(0x701, a, 2);
    return 0;
}
static int quant;   /* per case: values on a 1/8 grid, so that exact ties occur */
static float rf(float s)
{
    if (quant && (rnd() & 7)) return ((int)rndn(17) - 8) / 8.0f * s;
    switch (rnd() & 31) {
    case 0: { uint32_t u = 0x7fc00000u | (rnd() & 0x80000000u); return *(float *)&u; }
    case 1: { uint32_t u = rnd() & 0x807fffffu; return *(float *)&u; }
    case 2: return 0.0f;
    case 3: { uint32_t u = 0x7f800000u | (rnd() & 0x80000000u); return *(float *)&u; }
    default: return ((int)rndn(2000001) - 1000000) / 1000000.0f * s;
    }
}
#define SF(a, s) do { float f_ = rf(s); GF(a) = f_; } while (0)
/* a float near v: v itself or a few ulps off */
static float near(double v)
{
    float f = (float)v;
    int k = (int)rndn(7) - 3;
    uint32_t u = *(uint32_t *)&f;
    u += k;
    return *(float *)&u;
}
static void setup(int *args)
{
    quant = rnd() & 1;
    G(0x7f0fc8) = CAM;
    for (int i = 0; i < 12; i++) SF(CAM + 8 + 4 * i, 4);
    G(CAM + 0x48) = FRUST;
    for (int i = 0; i < 8 * 3; i++) SF(CAM + 0x15c + 4 * i, 6);
    SF(CAM + 0x45c, 1);
    /* mesh */
    fill_rand(MESH, 0x64);
    G(MESH + 0x24) = (rnd() & 15) ? (int)rndn(5) + 1 : 0;
    G(MESH + 0x28) = (rnd() & 7) == 0 ? (int)rnd() : (int)rndn(8);
    G(MESH + 0x2c) = rndn(6);
    G(MESH + 0x30) = VERTS; G(MESH + 0x48) = rndn(30);
    int nf = rndn(12);
    G(MESH + 0x40) = FACES; G(MESH + 0x50) = nf;
    SF(MESH + 0x5c, 1); SF(MESH + 0x60, 3);
    for (int i = 0; i < 64 * 3; i++) SF(VERTS + 4 * i, 5);
    for (int f = 0; f < nf; f++) {
        uint32_t fa = FACES + f * 0x4c;
        fill_rand(fa, 0x4c);
        G(fa + 0x18) = IDX + f * 16; G(IDX + f * 16) = rndn(64);
        SF(fa + 0x40, 1); SF(fa + 0x44, 1); SF(fa + 0x48, 1);
    }
    for (int i = 0; i < 12; i++) SF(MAT + 4 * i, 5);
    /* lights */
    int nl = rndn(9);
    G(0x7f31f8) = nl;
    for (int l = 0; l < nl; l++) {
        uint32_t la = LIGHTS + l * 0x40;
        fill_rand(la, 0x40);
        G(0x7f1498 + 4 * l) = la;
        G(la) = rndn(8); G(la + 4) = rndn(4); G(la + 8) = rnd() & 1;
        SF(la + 0xc, 1); SF(la + 0x10, 1); SF(la + 0x14, 1); SF(la + 0x34, 8);
        if (rnd() & 1) {
            /* range just at the distance: the precision of the test decides */
            uint32_t p = CAM + 0x15c + G(la) * 12;
            double dx = (double)GF(p) - GF(MAT + 36), dy = (double)GF(p + 4) - GF(MAT + 40), dz = (double)GF(p + 8) - GF(MAT + 44);
            float r = near(sqrt(dx * dx + dy * dy + dz * dz) - GF(MESH + 0x60));
            GF(la + 0x34) = r;
        }
    }
    /* globals */
    G(0x7f30a4) = rnd() & 1; GB(0x900068) = rnd(); G(0x7f3204) = rnd() & 1;
    SF(0x7f3208, 5); SF(0x7f320c, 5); SF(0x7f3210, 5); SF(0x4ddb70, 1); SF(0x4ddb74, 1); SF(0x4ddb78, 1);
    if (rnd() & 1) {
        /* clip plane through the mesh's bounding sphere */
        double d1 = ((double)GF(MAT + 40) - GF(0x7f320c)) * GF(0x4ddb74), d2 = ((double)GF(MAT + 44) - GF(0x7f3210)) * GF(0x4ddb78);
        float p0 = near(GF(MAT + 36) - (-(double)GF(MESH + 0x60) - d1 - d2) / GF(0x4ddb70));
        GF(0x7f3208) = p0;
    }
    G(0x7f1494) = rndn(6); G(0x7f189c) = rndn(6); G(0x7f30dc) = (rnd() & 3) ? 7 : (int)rndn(7);
    SF(0x8ddf84, 6); SF(0x8ddf88, 6); SF(0x8ddf8c, 6);
    G(0x900064) = rnd();
    args[0] = MESH; args[1] = MAT;
}
extern void rdModel_DrawMesh(void);
static const Fn fns[] = {{"rdModel_DrawMesh", 0x40d230, (void *)rdModel_DrawMesh, setup, 0}};
int main(int argc, char **argv)
{
    rt_init();
    rt_patch(0x450060, 1, 0); rec_handler[1] = h_vsub;
    rt_patch(0x44f8a0, 2, 0); rec_handler[2] = h_mul34;
    rt_patch(0x450170, 3, 0); rec_handler[3] = h_xform;
    rt_patch(0x44efd0, 4, 0); rec_handler[4] = h_transpose;
    rt_patch(0x44e7d0, 5, 0); rec_handler[5] = h_frust;
    rt_patch(0x451510, 6, -1); rec_handler[6] = h_light;
    rt_patch(0x40d880, 7, 0); rec_handler[7] = h_add;
    fill_rand(0x30000000, ARENA_SZ);
    return run_all(fns, 1, argc > 1 ? atol(argv[1]) : 1000, 0);
}
