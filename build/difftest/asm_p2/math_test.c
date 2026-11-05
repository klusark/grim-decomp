/* Differential test of build/overrides_asm_p2.c against the original 1.01 machine code (sliced from the assembly of
 * bb04517): Frustum_TestSphere, Polygon_ClipToPlane, Angles_ToMatrix, Angles_ToMatrixNoPos, Matrix_AxisAngle,
 * rdLight_CalcVertexIntensities, rdCanvas_DrawPoint.
 *
 * Each case builds random inputs (small integers and halves that make ties, random floats, and the special values
 * 0, -0, +-inf, quiet and signalling NaN, denormals, 1e-5 neighbours), runs the original and the C on copies of the
 * same state under the x87 precision control 24, 53 or 64 bits (rotating), and compares: the return value (the x87
 * long double bits for rdLight_CalcVertexIntensities), every output buffer and the static clip buffers of the data
 * image, the call log of the stand-in callees (arguments as dwords), the x87 control word and the x87 stack top.
 * The callees are stand-ins: Math_SinCosTable and Vec3_Normalize write values from a per-case stream (so both runs
 * see the same values when they call in the same order), rdPrimit2_DrawLine records its arguments.
 * usage: math_test.exe [cases per function] */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <stdint.h>
#include <math.h>
#include "fx.h"

typedef unsigned uint;
/* float-by-value parameters are declared uint so the exact bits are pushed (no FLD/FSTP in the test) */
extern uint orig_Frustum_TestSphere(int *, float *, uint), Frustum_TestSphere(int *, float *, uint);
extern uint orig_Polygon_ClipToPlane(float *, float *, float *, float *, float *, int),
    Polygon_ClipToPlane(float *, float *, float *, float *, float *, int);
extern void orig_Angles_ToMatrix(float *, uint *, float *), Angles_ToMatrix(float *, uint *, float *);
extern void orig_Angles_ToMatrixNoPos(float *, uint *), Angles_ToMatrixNoPos(float *, uint *);
extern void orig_Matrix_AxisAngle(float *, float *, uint), Matrix_AxisAngle(float *, float *, uint);
extern long double orig_rdLight_CalcVertexIntensities(int **, float *, float *, uint, float *, float *, float *, float *, uint, uint),
    rdLight_CalcVertexIntensities(int **, float *, float *, uint, float *, float *, float *, float *, uint, uint);
extern void orig_rdCanvas_DrawPoint(void *, int, int, uint, uint, int, int), rdCanvas_DrawPoint(void *, int, int, uint, uint, int, int);

/* ---- stand-in callees with a per-case value stream and a call log ---- */
static uint64_t ss;
static uint snext(void) { ss ^= ss << 13; ss ^= ss >> 7; ss ^= ss << 17; return (uint)(ss >> 17); }
static uint lg[8192]; static int nlg;
static void L(uint v) { if (nlg < 8192) lg[nlg++] = v; }
static uint fbits(float f) { uint u; memcpy(&u, &f, 4); return u; }
static float bitsf(uint u) { float f; memcpy(&f, &u, 4); return f; }
static uint R(uint n) { return (uint)(fx_rnd() % n); }
static uint special_bits(uint k)
{
    static const uint t[] = {0x00000000, 0x80000000, 0x7f800000, 0xff800000, 0x7fc00000, 0x7f800001, 0xffc00000,
                             0x00000001, 0x807fffff, 0x3727c5ac, 0x3727c5ab, 0x3727c5ad, 0x3f800000, 0x3f7fffff,
                             0x3f800001, 0xbf800000, 0x7f7fffff};
    static int mode = -1;   /* P2_NAN=1: no signalling NaN; P2_NAN=2: no NaN of either sign other than 0x7fc00000 */
    uint v = t[k % (sizeof t / sizeof t[0])];
    if (mode < 0) mode = getenv("P2_NAN") ? atoi(getenv("P2_NAN")) : 0;
    if (mode >= 1 && v == 0x7f800001) v = 0x7fc00000;
    if (mode >= 2 && v == 0xffc00000) v = 0x7fc00000;
    return v;
}
/* a float: small integers / halves (ties), random, or a special value */
static float rf(float scale)
{
    uint k = R(24);
    if (k < 2) return bitsf(special_bits(R(64)));
    if (k < 10) return (float)((int)R(17) - 8) * 0.5f;
    return (float)(((double)(int)(fx_rnd() % 2000001) - 1000000.0) / 1000000.0 * scale);
}
static float rf_nospecial(float scale)
{
    if (R(3) == 0) return (float)((int)R(17) - 8) * 0.5f;
    return (float)(((double)(int)(fx_rnd() % 2000001) - 1000000.0) / 1000000.0 * scale);
}
static uint stream_f(void)
{
    uint k = snext() % 20;
    if (k == 0) return special_bits(snext());
    if (k < 6) return fbits((float)((int)(snext() % 9) - 4) * 0.25f);
    return fbits((float)(((double)(snext() % 2000001) - 1000000.0) / 1000000.0));
}
void __cdecl Math_SinCosTable(uint ang, float *a, float *b)
{
    uint u = stream_f(), v = stream_f();
    L(0x5c5c0000); L(ang);
    memcpy(a, &u, 4); memcpy(b, &v, 4);
}
static int (*cur_lrec)[16];
static float *cur_dir;
long double __cdecl Vec3_Normalize(float *p)
{
    uint i, u;
    long double r;
    L(0x7ec30000);
    for (i = 0; i < 3; i++) { memcpy(&u, &p[i], 4); L(u); }
    for (i = 0; i < 3; i++) { u = stream_f(); memcpy(&p[i], &u, 4); }
    /* spot-light ties: when every light has the same direction (cur_dir), sometimes set the outer cone cosine (+0x2c)
     * of every light record of the running implementation to the float rounding of the extended dot(dir, L), the
     * value the function compares next (in the same x87 precision) */
    if (cur_lrec && snext() % 2) {
        long double cs = ((long double)cur_dir[0] * p[0] + (long double)cur_dir[1] * p[1]) + (long double)cur_dir[2] * p[2];
        float cf = (float)cs;
        for (i = 0; i < 6; i++) memcpy(&cur_lrec[i][11], &cf, 4);
    }
    /* a length that is not a float (extended value) most of the time */
    r = (long double)(snext() % 100000) / 7777.0L;
    if (snext() % 10 == 0) r = 0.0L;
    return r;
}
void __cdecl rdPrimit2_DrawLine(void *c, int x1, int y1, int x2, int y2, int col, int mask)
{
    L(0xd1a40000); L((uint)c); L(x1); L(y1); L(x2); L(y2); L(col); L(mask);
}

static uint get_sw(void) { unsigned short sw; __asm__ volatile("fnstsw %0" : "=m"(sw)); return sw; }
static uint get_cw(void) { unsigned short cw; __asm__ volatile("fnstcw %0" : "=m"(cw)); return cw; }

/* ---- comparison bookkeeping: state A = after the original, B = after the C ---- */
#define MAXS 8192
static unsigned char stA[MAXS], stB[MAXS];
static uint lgA[8192]; static int nlgA;
static uint cwA, swA;
static long nf[8], nc[8];
static const char *fname[8] = {"Frustum_TestSphere", "Polygon_ClipToPlane", "Angles_ToMatrix", "Angles_ToMatrixNoPos",
                               "Matrix_AxisAngle", "rdLight_CalcVertexIntensities", "rdCanvas_DrawPoint", ""};
static long nnan[8];
/* 0: equal; 1: differ only in entries that are NaN in both (the NaN payload / sign the x87 picks); 2: real difference */
static int fkind(const void *a, const void *b, int n)
{
    const uint *x = a, *y = b;
    int i, k = 0;
    for (i = 0; i < n; i++)
        if (x[i] != y[i]) {
            if ((x[i] & 0x7fffffff) > 0x7f800000 && (y[i] & 0x7fffffff) > 0x7f800000) k = 1;
            else return 2;
        }
    return k;
}
static void fail(int f, long i, const char *what)
{
    if (nf[f]++ < 5) printf("DIFF %s case %ld: %s\n", fname[f], i, what);
}
static const unsigned pcs[3] = {_PC_24, _PC_53, _PC_64};
static void begin(uint64_t seed, int pc) { ss = seed | 1; nlg = 0; _controlfp(pcs[pc], _MCW_PC); }
static void endA(void) { cwA = get_cw(); swA = get_sw(); _controlfp(_PC_64, _MCW_PC); memcpy(lgA, lg, nlg * 4); nlgA = nlg; }
static void endB(int f, long i)
{
    uint cw = get_cw(), sw = get_sw();
    _controlfp(_PC_64, _MCW_PC);
    if (cw != cwA) fail(f, i, "control word");
    if (((sw >> 11) & 7) != ((swA >> 11) & 7)) fail(f, i, "x87 stack top");
    if (nlg != nlgA || memcmp(lg, lgA, nlg * 4)) fail(f, i, "call log");
}

/* ---- Frustum_TestSphere ---- */
static int cam[4];
static void t_frustum(long i)
{
    static int fr[11], frB[11];
    static float c[3], cB[3];
    uint r, ra, rb;
    int pc = i % 3, k;
    uint64_t seed = fx_rnd();
    float base;
    fr[0] = R(3) == 0 ? 0 : (R(4) ? 1 : (int)fx_rnd());
    for (k = 0; k < 3; k++) c[k] = rf(10);
    r = R(10) ? fbits(rf_nospecial(4)) : fbits(rf(4));
    base = R(2) ? c[1] : rf(10);
    for (k = 1; k < 11; k++) {
        float v;
        switch (R(6)) {
        case 0: v = c[R(3)] + bitsf(r); break;
        case 1: v = c[R(3)] - bitsf(r); break;
        case 2: v = base; break;
        default: v = rf(10); break;
        }
        memcpy(&fr[k], &v, 4);
    }
    if (R(3) == 0) {   /* ties of the depth-scaled side bounds: r = 0, a centre coordinate = float(k * y) */
        float ff[11], y;
        memcpy(ff, fr, sizeof ff);
        if (R(2)) r = 0;
        y = c[1] - bitsf(r);
        k = 7 + R(4);
        c[k == 7 || k == 8 ? 2 : 0] = (float)((double)ff[k] * y);
    }
    cam[0] = R(3) ? 1 : (int)R(3);
    FXU32(0x7f0fc8) = (uint)(uintptr_t)cam;
    memcpy(frB, fr, sizeof fr); memcpy(cB, c, sizeof c);
    begin(seed, pc); ra = orig_Frustum_TestSphere(fr, c, r); endA();
    begin(seed, pc); rb = Frustum_TestSphere(frB, cB, r); endB(0, i);
    if (ra != rb) fail(0, i, "return");
    if (memcmp(fr, frB, sizeof fr) || memcmp(c, cB, sizeof c)) fail(0, i, "inputs changed");
    nc[0]++;
}

/* ---- Polygon_ClipToPlane ---- */
#define CLIP_LO 0x7f4600
#define CLIP_HI 0x7f4c00
static void t_clip(long i)
{
    static float vb[3 * 48], uvb[2 * 48], ib[48];
    static float vB[3 * 48], uvB[2 * 48], iB[48];
    static unsigned char clipA[CLIP_HI - CLIP_LO];
    float nrm[3], pt[3];
    int n = R(17), k, has_uv = R(3) != 0, has_i = R(3) != 0;
    int pc = i % 3, mode = R(4);
    uint ra, rb;
    uint64_t seed = fx_rnd();
    for (k = 0; k < 3 * 48; k++) vb[k] = mode == 0 ? rf(10) : rf_nospecial(10);
    for (k = 0; k < 2 * 48; k++) uvb[k] = mode == 0 ? rf(1) : rf_nospecial(1);
    for (k = 0; k < 48; k++) ib[k] = R(16) == 0 ? bitsf(0x7f800001 + R(4)) : mode == 0 ? rf(1) : rf_nospecial(1);
    for (k = 0; k < 3; k++) { nrm[k] = mode == 0 ? rf(1) : rf_nospecial(1); pt[k] = mode == 0 ? rf(5) : rf_nospecial(5); }
    if (R(3) == 0) { nrm[0] = nrm[2] = 0; nrm[1] = 1; pt[1] = 0; }
    if (R(4) == 0) for (k = 0; k < 3; k++) pt[k] = vb[3 + 3 * R(n + 1) + k];   /* a vertex on the plane */
    for (k = 0; k < CLIP_HI - CLIP_LO; k++) FXDATA(CLIP_LO)[k] = (unsigned char)fx_rnd();
    memcpy(vB, vb, sizeof vb); memcpy(uvB, uvb, sizeof uvb); memcpy(iB, ib, sizeof ib);
    memcpy(clipA, FXDATA(CLIP_LO), sizeof clipA);
    /* vertex 0 is at index 1 of the buffers (n = 0 reads index -1) */
    begin(seed, pc);
    ra = orig_Polygon_ClipToPlane(nrm, pt, vb + 3, has_uv ? uvb + 2 : 0, has_i ? ib + 1 : 0, n);
    endA();
    memcpy(stA, FXDATA(CLIP_LO), CLIP_HI - CLIP_LO);
    memcpy(FXDATA(CLIP_LO), clipA, sizeof clipA);
    begin(seed, pc);
    rb = Polygon_ClipToPlane(nrm, pt, vB + 3, has_uv ? uvB + 2 : 0, has_i ? iB + 1 : 0, n);
    endB(1, i);
    if (ra != rb) fail(1, i, "return");
    if (memcmp(vb, vB, sizeof vb)) fail(1, i, "vertices");
    if (memcmp(uvb, uvB, sizeof uvb)) fail(1, i, "uv");
    if (memcmp(ib, iB, sizeof ib)) {
        fail(1, i, "intensities");
        if (getenv("P2DBG"))
            for (k = 0; k < 48; k++)
                if (fbits(ib[k]) != fbits(iB[k])) printf("  i[%d] orig %08x C %08x (n %d)\n", k - 1, fbits(ib[k]), fbits(iB[k]), n);
    }
    if (memcmp(stA, FXDATA(CLIP_LO), CLIP_HI - CLIP_LO)) fail(1, i, "static clip buffers");
    nc[1]++;
}

/* ---- Angles_ToMatrix / NoPos ---- */
static void t_angles(long i, int nopos)
{
    float m[16], mB[16], pos[3];
    uint ang[3];
    int k, pc = i % 3;
    uint64_t seed = fx_rnd();
    for (k = 0; k < 16; k++) m[k] = bitsf((uint)fx_rnd());
    for (k = 0; k < 3; k++) { ang[k] = fbits(rf(360)); pos[k] = R(8) ? rf(100) : bitsf(special_bits(R(64))); }
    memcpy(mB, m, sizeof m);
    begin(seed, pc);
    if (nopos) orig_Angles_ToMatrixNoPos(m, ang); else orig_Angles_ToMatrix(m, ang, pos);
    endA();
    begin(seed, pc);
    if (nopos) Angles_ToMatrixNoPos(mB, ang); else Angles_ToMatrix(mB, ang, pos);
    endB(2 + nopos, i);
    if ((k = fkind(m, mB, 16)) == 1) nnan[2 + nopos]++;
    else if (k) {
        fail(2 + nopos, i, "matrix");
        if (getenv("P2DBG"))
            for (k = 0; k < 12; k++)
                if (fbits(m[k]) != fbits(mB[k])) printf("  m[%d] orig %08x C %08x\n", k, fbits(m[k]), fbits(mB[k]));
    }
    nc[2 + nopos]++;
}

/* ---- Matrix_AxisAngle ---- */
static void t_axis(long i)
{
    float m[16], mB[16], ax[3];
    uint ang;
    int k, pc = i % 3;
    uint64_t seed = fx_rnd();
    static const uint zs[] = {0x3f800000, 0xbf800000, 0x3f7fff58, 0x3f7fff57, 0x3f7fff59, 0x3f800054, 0x3f800053,
                              0xbf7fff58, 0xbf7fff57, 0xbf7fff59, 0xbf800054, 0xbf800053, 0x7fc00000, 0x7f800001,
                              0x3f7fffff, 0xbf7fffff, 0x00000000};
    for (k = 0; k < 16; k++) m[k] = bitsf((uint)fx_rnd());
    for (k = 0; k < 3; k++) ax[k] = R(4) ? rf_nospecial(1) : rf(1);
    switch (R(4)) {
    case 0: ax[2] = bitsf(zs[R(sizeof zs / 4)]); break;
    case 1: ax[2] = 1.0f - (float)R(30) * 1e-6f; break;
    case 2: ax[2] = -1.0f + (float)R(30) * 1e-6f; break;
    }
    ang = R(10) ? fbits(rf(360)) : special_bits(R(64));
    memcpy(mB, m, sizeof m);
    begin(seed, pc); orig_Matrix_AxisAngle(m, ax, ang); endA();
    begin(seed, pc); Matrix_AxisAngle(mB, ax, ang); endB(4, i);
    if ((k = fkind(m, mB, 16)) == 1) nnan[4]++;
    else if (k) {
        fail(4, i, "matrix");
        if (getenv("P2DBG"))
            for (k = 0; k < 12; k++)
                if (fbits(m[k]) != fbits(mB[k])) printf("  m[%d] orig %08x C %08x\n", k, fbits(m[k]), fbits(mB[k]));
    }
    nc[4]++;
}

/* ---- rdLight_CalcVertexIntensities ---- */
static void t_light(long i)
{
    static int lrec[6][16], lrecB[6][16];
    static int *lp[6], *lpB[6];
    float lpos[18], ldir[18], nrm[24], vtx[24], base[8], out[10], outB[10];
    uint nl = R(6), nv = R(8), k, j, kbits;
    int pc = i % 3, sp = R(5) == 0, shared;
    long double ra, rb;
    uint64_t seed = fx_rnd();
    for (k = 0; k < 6; k++) {
        float *f = (float *)lrec[k];
        for (j = 0; j < 16; j++) f[j] = sp ? rf(2) : rf_nospecial(2);
        lrec[k][1] = R(8) ? (int)R(4) : (int)R(7) - 2;
        f[6] = R(3) ? rf_nospecial(1.5f) : rf(3);
        f[9] = rf_nospecial(1);  f[11] = R(2) ? f[9] - 0.25f : rf_nospecial(1);
        f[12] = rf_nospecial(4);
        f[13] = R(4) ? (float)R(20) : rf(20);
        lp[k] = lrec[k]; lpB[k] = lrecB[k];
    }
    memcpy(lrecB, lrec, sizeof lrec);
    for (k = 0; k < 18; k++) { lpos[k] = sp ? rf(10) : rf_nospecial(10); ldir[k] = sp ? rf(1) : rf_nospecial(1); }
    for (k = 0; k < 24; k++) { nrm[k] = sp ? rf(1) : rf_nospecial(1); vtx[k] = sp ? rf(10) : rf_nospecial(10); }
    for (k = 0; k < 8; k++) base[k] = R(4) == 0 ? 1.0f : (sp ? rf(1) : rf_nospecial(1));
    for (k = 0; k < 10; k++) out[k] = bitsf((uint)fx_rnd());
    memcpy(outB, out, sizeof out);
    kbits = R(4) ? 0x3e4ccccd : fbits(rf(1));
    if (R(3) == 0) {   /* range ties: range = float(sqrt(squared distance to vertex 0)) */
        for (k = 0; k < 6; k++) {
            double dx = (double)lpos[3 * k] - vtx[0], dy = (double)lpos[3 * k + 1] - vtx[1], dz = (double)lpos[3 * k + 2] - vtx[2];
            ((float *)lrec[k])[13] = (float)sqrt(dx * dx + dy * dy + dz * dz);
        }
        memcpy(lrecB, lrec, sizeof lrec);
    }
    shared = R(3) == 0;   /* one direction for every light: Vec3_Normalize may set cone ties (see there) */
    if (shared) for (k = 3; k < 18; k++) ldir[k] = ldir[k % 3];
    begin(seed, pc);
    if (shared) { cur_lrec = lrec; cur_dir = ldir; }
    ra = orig_rdLight_CalcVertexIntensities(lp, lpos, ldir, nl, nrm, vtx, base, out, nv, kbits);
    endA();
    begin(seed, pc);
    if (shared) { cur_lrec = lrecB; cur_dir = ldir; }
    rb = rdLight_CalcVertexIntensities(lpB, lpos, ldir, nl, nrm, vtx, base, outB, nv, kbits);
    cur_lrec = 0;
    endB(5, i);
    if (memcmp(&ra, &rb, 10)) fail(5, i, "return (x87 bits)");
    if (memcmp(out, outB, sizeof out)) fail(5, i, "out");
    if (memcmp(lrec, lrecB, sizeof lrec)) fail(5, i, "light records changed");
    nc[5]++;
}

/* ---- rdCanvas_DrawPoint ---- */
/* steps whose angle sum ends just above 360 in extended precision but at 360 or below when rounded to a float (the
 * loop test uses the unrounded sum); found by search at start-up (precision control 64 bits) */
static float tie_steps[32];
static int ntie;
static void find_tie_steps(void)
{
    uint64_t keep = fx_seed;
    int tries;
    /* candidates: float neighbours (up to +-64 ulps) of 360 / k for k = 3 .. 720 */
    for (tries = 0; tries < 718 * 129 && ntie < 32; tries++) {
        float s0 = (float)(360.0 / (3 + tries / 129));
        uint u;
        volatile float step, a;
        memcpy(&u, &s0, 4);
        u += tries % 129 - 64;
        memcpy((float *)&step, &u, 4);
        a = step;
        long double t;
        do { t = (long double)a + step; a = (float)t; } while (!(t > 360.0L));
        if ((long double)a <= 360.0L) tie_steps[ntie++] = step;
    }
    if (getenv("P2DBG")) printf("tie steps: %d (first %.9g)\n", ntie, ntie ? tie_steps[0] : 0.0);
    if (ntie == 0) tie_steps[ntie++] = 30.0f;
    fx_seed = keep;
}
static void t_point(long i)
{
    static int cv[16];
    static const float steps[] = {30, 45, 90, 7.5f, 120, 360, 400, 359.5f, 360.00003f, 180, 72, 10, 12.5f,
                                  180.00001f, 90.000002f, 179.99998f, 120.00001f, 119.99999f};
    int x = (int)R(800) - 80, y = (int)R(600) - 60, pc = i % 3, k, mask = (int)R(3) - 1;
    uint r, step;
    uint64_t seed = fx_rnd();
    for (k = 0; k < 16; k++) cv[k] = (int)fx_rnd();
    cv[6] = R(100); cv[7] = R(100); cv[8] = 300 + R(400); cv[9] = 200 + R(300);
    if (R(8) == 0) { cv[6] = x + 3; }
    r = R(6) ? fbits((float)R(40) * 0.25f + (R(2) ? 0.5f : 0)) : fbits(rf(50));
    if (R(10) == 0) r = special_bits(R(64));
    step = fbits(steps[R(sizeof steps / 4)]);
    if (R(3) == 0) step = fbits(tie_steps[R(ntie)]);
    begin(seed, pc); orig_rdCanvas_DrawPoint(cv, x, y, r, step, 0x1234, mask); endA();
    begin(seed, pc); rdCanvas_DrawPoint(cv, x, y, r, step, 0x1234, mask); endB(6, i);
    nc[6]++;
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000, i;
    int f, bad = 0;
    for (i = 0; i < n; i++) t_frustum(i);
    for (i = 0; i < n; i++) t_clip(i);
    for (i = 0; i < n; i++) t_angles(i, 0);
    for (i = 0; i < n; i++) t_angles(i, 1);
    for (i = 0; i < n; i++) t_axis(i);
    for (i = 0; i < n; i++) t_light(i);
    find_tie_steps();
    for (i = 0; i < n / 4; i++) t_point(i);
    for (f = 0; f < 7; f++) {
        printf("%-32s %8ld cases, %ld differences, %ld NaN-payload-only\n", fname[f], nc[f], nf[f], nnan[f]);
        bad |= nf[f] != 0;
    }
    return bad;
}
