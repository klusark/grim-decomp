/* Readable C for assembled GRIMFANDANGO.EXE functions, upper half by address (agent asm_p2; see docs/notes/asm_p2.md).
 *
 * Every function here was written by hand from the original 1.01 machine code (src/GRIMFANDANGO.EXE/asm_funcs.s as of
 * bb04517) and checked against it with a differential test in build/difftest/asm_p2/ (original bytes and this C on the
 * same inputs, under the x87 precision controls 24, 53 and 64 bits; return value, memory, call log and control word
 * compared).
 *
 * x87 conventions used below:
 *   - `long double` holds a value that the original keeps on the x87 stack (extended precision, rounded only by the
 *     precision control); st_f() is a store of such a value to a float slot (FSTP m32), through a volatile so the
 *     rounding happens at that point at every optimisation level.
 *   - LT_U(a, b): `fcomp; test ah,1` taken = a < b or unordered.  LE_U(a, b): `test ah,0x41` = a <= b or unordered.
 *   - A float that the original copies with MOV (no FLD/FSTP) is copied as a dword here (U32), so a signalling NaN
 *     keeps its bits; a float that goes through FLD/FSTP is copied with st_f (a signalling NaN becomes quiet).
 *   - stdMath_SinCos gets the angle as the dword the original pushes (MOV/PUSH), not as a float argument. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#define rdLight_CalcVertexIntensities rdLight_CalcVertexIntensities__ghidra
#define Matrix_AxisAngle Matrix_AxisAngle__ghidra
#include "functions.h"
#undef Matrix_AxisAngle
#undef rdLight_CalcVertexIntensities

#define U32(lv) (*(uint *)&(lv))
#define LT_U(a, b) (!((long double)(a) >= (long double)(b)))
#define LE_U(a, b) (!((long double)(a) > (long double)(b)))

static inline float p2_st_f(long double x)
{
    volatile float f = (float)x;
    return f;
}
#define st_f p2_st_f

/* FCHS of an x87 value as a separate step: gcc -O2 otherwise moves the negation past a multiplication
 * ((-a)*b -> -(a*b)), which only changes the sign of a NaN result, but does change it. */
static inline long double p2_neg(long double x)
{
    volatile long double v = -x;
    return v;
}

/* stdMath_SinCos(angle, out1, out2) with the angle passed as the raw dword */
typedef void (*p2_sincos_fn)(uint, float *, float *);
#define SINCOS(bits, a, b) (((p2_sincos_fn)stdMath_SinCos)((bits), (a), (b)))

/* _ftol: truncation of the x87 value to a 64-bit integer, low dword */
static inline int p2_ftol(long double x)
{
    return (int)(long long)x;
}

/* ==== Frustum_TestSphere (0x0044e7d0) ====
 * Tests a sphere (centre c, radius r) against the view frustum record f: returns 2 when it is fully outside one plane,
 * 1 when it crosses a plane, 0 when it is fully inside.  f[0] != 0 enables the far plane f[2]; f[1] is the near plane.
 * The depth axis is y.  With the camera's projection type 1 (perspective) the side planes scale with depth: the bound
 * of each side is k * (y - r) (kept in extended precision) and k * (y + r) (stored as a float); otherwise the side
 * planes are the constants f[3] .. f[6] (left / top / right / bottom; the asm compares x against f[3], f[5] and z
 * against f[4], f[6]).  The "x - r" style values are stored as floats, the first "y + r" is compared unrounded.
 * The asm stores y - r into its first parameter slot and k*(y+r) into the second / third (no effect on the caller). */
/* OVERRIDES: Frustum_TestSphere */
uint Frustum_TestSphere(int *param_1, float *param_2, float param_3)
{
    float *ff = (float *)param_1;
    float *c = param_2;
    float r = param_3;
    long double hi = (long double)r + c[1];
    float hiF, loF, hi2, lo2, hi3, lo3, B;
    long double A;
    int inside = 1;
    int cam;

    hiF = st_f(hi);
    loF = st_f((long double)c[1] - r);
    if (LT_U(hi, ff[1]))
        return 2;
    if (LT_U(loF, ff[1]))
        inside = 0;
    if (param_1[0] != 0) {
        if (!LE_U(loF, ff[2]))
            return 2;
        if (!LE_U(hiF, ff[2]))
            inside = 0;
    }

    hi2 = st_f((long double)r + c[2]);
    lo2 = st_f((long double)c[2] - r);
    cam = *(int *)g_pRdCamera_CurCamera;
    if (cam == 1) {
        A = (long double)ff[7] * loF;
        B = st_f((long double)ff[7] * hiF);
    } else {
        A = ff[4];
        U32(B) = (uint)param_1[4];
    }
    if (!LE_U(lo2, A) && !LE_U(lo2, B))
        return 2;
    if (!LE_U(hi2, A) || !LE_U(hi2, B))
        inside = 0;

    if (cam == 1) {
        A = (long double)ff[8] * loF;
        B = st_f((long double)ff[8] * hiF);
    } else {
        A = ff[6];
        U32(B) = (uint)param_1[6];
    }
    if (LT_U(hi2, A) && LT_U(hi2, B))
        return 2;
    if (LT_U(lo2, A) || LT_U(lo2, B))
        inside = 0;

    hi3 = st_f((long double)r + c[0]);
    lo3 = st_f((long double)c[0] - r);
    if (cam == 1) {
        A = (long double)ff[9] * loF;
        B = st_f((long double)ff[9] * hiF);
    } else {
        A = ff[3];
        U32(B) = (uint)param_1[3];
    }
    if (LT_U(hi3, A) && LT_U(hi3, B))
        return 2;
    if (LT_U(lo3, A) || LT_U(lo3, B))
        inside = 0;

    if (cam == 1) {
        A = (long double)ff[10] * loF;
        B = st_f((long double)ff[10] * hiF);
    } else {
        A = ff[5];
        U32(B) = (uint)param_1[5];
    }
    if (!LE_U(lo3, A) && !LE_U(lo3, B))
        return 2;
    if (!LE_U(hi3, A) || !LE_U(hi3, B))
        inside = 0;
    return inside == 0;
}

/* ==== Polygon_ClipToPlane (0x0044ea50) ====
 * Clips a polygon of `n` vertices (12-byte positions `v`, optional 8-byte texture coordinates `uv`, optional float
 * intensities `in`) against the plane through `pt` with normal `nrm` (keeps the side where dot(p - pt, nrm) >= 0),
 * Sutherland-Hodgman style, into the static buffers 0x007f48c0 (positions), 0x007f46b8 (uv), 0x007f47c0 (intensities),
 * then copies the result back over the input arrays.  Returns the new vertex count.  `n` is passed in the last
 * parameter (Ghidra typed it as a pointer).
 * Details kept from the original:
 *   - the plane distance of the current vertex stays in extended precision for the tests and the interpolation factor;
 *     the previous one is the stored float.  t = -(dprev / (d - dprev)).
 *   - a vertex that is kept copies THREE dwords of uv (the third is the next vertex's u; it is overwritten by the next
 *     output vertex or stays behind the last one), and its intensity goes through FLD/FSTP.
 *   - the last vertex (index n - 1) and its intensity are read even when n <= 0. */
/* OVERRIDES: Polygon_ClipToPlane */
uint Polygon_ClipToPlane(float *param_1, float *param_2, float *param_3, undefined4 *param_4, float *param_5,
                         uint *param_6)
{
    float *nrm = param_1, *pt = param_2, *v = param_3, *uv = (float *)param_4, *in = param_5;
    int n = (int)param_6;
    float *prev = v + n * 3 - 3;
    float *prevuv;
    float dprev, iprev;
    long double icur = 0.0L;
    int cnt = 0;

    dprev = st_f((((long double)prev[0] - pt[0]) * nrm[0] + ((long double)prev[2] - pt[2]) * nrm[2]) +
                 ((long double)prev[1] - pt[1]) * nrm[1]);
    prevuv = uv != 0 ? uv + n * 2 - 2 : in;
    if (in != 0)
        iprev = st_f(in[n - 1]);
    if (n > 0) {
        float *ov = (float *)&UINT_007f48c0, *ouv = (float *)&UINT_007f46b8, *oi = (float *)&UINT_007f47c0;
        float *cur = v, *curuv = uv, *curi = in, *uvp = 0;
        int left = n;
        do {
            long double d;
            if (uv != 0)
                uvp = curuv;
            if (in != 0)
                icur = *curi;
            d = (((long double)cur[0] - pt[0]) * nrm[0] + ((long double)cur[2] - pt[2]) * nrm[2]) +
                ((long double)cur[1] - pt[1]) * nrm[1];
            if (!LT_U(dprev, 0.0f) && !LT_U(d, 0.0f)) {
                /* both inside: keep the current vertex */
                U32(ov[0]) = U32(cur[0]);
                U32(ov[1]) = U32(cur[1]);
                U32(ov[2]) = U32(cur[2]);
                if (uv != 0) {
                    U32(ouv[0]) = U32(uvp[0]);
                    U32(ouv[1]) = U32(uvp[1]);
                    U32(ouv[2]) = U32(uvp[2]);
                }
                if (in != 0)
                    *oi = st_f(icur);
                cnt++; ov += 3; ouv += 2; oi++;
            } else if (!LT_U(dprev, 0.0f) || !LT_U(d, 0.0f)) {
                /* the edge crosses the plane: the intersection */
                int entering = LT_U(dprev, 0.0f);
                long double t = p2_neg((long double)dprev / (d - dprev));
                ov[0] = st_f(((long double)cur[0] - prev[0]) * t + prev[0]);
                ov[1] = st_f(((long double)cur[1] - prev[1]) * t + prev[1]);
                ov[2] = st_f(((long double)cur[2] - prev[2]) * t + prev[2]);
                if (uv != 0) {
                    ouv[0] = st_f(((long double)uvp[0] - prevuv[0]) * t + prevuv[0]);
                    ouv[1] = st_f(((long double)uvp[1] - prevuv[1]) * t + prevuv[1]);
                }
                if (in != 0)
                    *oi = st_f((icur - iprev) * t + iprev);
                if (entering) {
                    /* coming back inside: then the current vertex */
                    cnt++; ov += 3; ouv += 2; oi++;
                    U32(ov[0]) = U32(cur[0]);
                    U32(ov[1]) = U32(cur[1]);
                    U32(ov[2]) = U32(cur[2]);
                    if (uv != 0) {
                        U32(ouv[0]) = U32(uvp[0]);
                        U32(ouv[1]) = U32(uvp[1]);
                        U32(ouv[2]) = U32(uvp[2]);
                    }
                    if (in != 0)
                        *oi = st_f(icur);
                }
                cnt++; ov += 3; ouv += 2; oi++;
            }
            prevuv = uvp;
            prev = cur;
            curuv += 2;
            curi++;
            cur += 3;
            iprev = st_f(icur);
            dprev = st_f(d);
        } while (--left != 0);
    }
    if (cnt > 0) {
        float *ov = (float *)&UINT_007f48c0, *ouv = (float *)&UINT_007f46b8, *oi = (float *)&UINT_007f47c0;
        int i;
        for (i = 0; i < cnt; i++) {
            U32(v[i * 3]) = U32(ov[i * 3]);
            U32(v[i * 3 + 1]) = U32(ov[i * 3 + 1]);
            U32(v[i * 3 + 2]) = U32(ov[i * 3 + 2]);
            if (uv != 0) {
                U32(uv[i * 2]) = U32(ouv[i * 2]);
                U32(uv[i * 2 + 1]) = U32(ouv[i * 2 + 1]);
            }
            if (in != 0)
                U32(in[i]) = U32(oi[i]);
        }
    }
    return (uint)cnt;
}

/* ==== Angles_ToMatrix (0x0044eeb0), Angles_ToMatrixNoPos (0x0044f080) ====
 * Builds the 3x4 matrix (rows of 3 floats; translation in m[9..11]) of the Euler angles ang[0..2] (pitch, yaw, roll)
 * from stdMath_SinCos(angle, &a, &b) of each angle.  With a1, b1 / a2, b2 / a3, b3 the outputs for ang[0] / [1] / [2]:
 *   P1 = a3*a2, P2 = a3*b2, P3 = b3*a2, P4 = b3*b2 (extended), S2 / S3 = P2 / P3 stored as floats;
 *   m0 = -P1*a1 + P4   m1 = P2*a1 + S3   m2 = -a3*b1
 *   m3 = -a2*b1        m4 = b2*b1        m5 = a1
 *   m6 = P3*a1 + S2    m7 = -a1*P4 + P1  m8 = b3*b1
 * Angles_ToMatrix copies pos[0..2] (dwords) to m[9..11]; Angles_ToMatrixNoPos stores 0 there. */
static void p2_angles_rot(float *m, undefined4 *ang)
{
    float a1, b1, a2, b2, a3, b3;
    long double P1, P2, P3, P4;
    float S2, S3;

    SINCOS(ang[0], &a1, &b1);
    SINCOS(ang[1], &a2, &b2);
    SINCOS(ang[2], &a3, &b3);
    P1 = (long double)a3 * a2;
    P2 = (long double)a3 * b2;
    P3 = (long double)b3 * a2;
    P4 = (long double)b3 * b2;
    S2 = st_f(P2);
    S3 = st_f(P3);
    m[0] = st_f(p2_neg(P1) * a1 + P4);
    m[1] = st_f(P2 * a1 + S3);
    m[2] = st_f(p2_neg(a3) * b1);
    m[3] = st_f(p2_neg(a2) * b1);
    m[4] = st_f((long double)b2 * b1);
    m[5] = st_f(a1);
    m[6] = st_f(P3 * a1 + S2);
    m[7] = st_f(p2_neg(a1) * P4 + P1);
    m[8] = st_f((long double)b3 * b1);
}

/* OVERRIDES: Angles_ToMatrix */
void Angles_ToMatrix(float *param_1, undefined4 *param_2, float *param_3)
{
    p2_angles_rot(param_1, param_2);
    U32(param_1[9]) = U32(param_3[0]);
    U32(param_1[10]) = U32(param_3[1]);
    U32(param_1[11]) = U32(param_3[2]);
}

/* OVERRIDES: Angles_ToMatrixNoPos */
void Angles_ToMatrixNoPos(float *param_1, undefined4 *param_2)
{
    p2_angles_rot(param_1, param_2);
    U32(param_1[9]) = 0;
    U32(param_1[10]) = 0;
    U32(param_1[11]) = 0;
}

/* ==== Matrix_AxisAngle (0x0044f210) ====
 * Rotation matrix (3x4, translation 0) of `angle` around the unit axis `ax`, with s, c from stdMath_SinCos(angle).
 * Axis (almost) +z (|1 - z| <= 1e-5f or NaN) and (almost) -z (|z + 1| <= 1e-5f) are special cases (a plain rotation in
 * the x-y plane, m[0] / m[3] via FLD/FSTP, m[4] / m[1] as dword copies).  Otherwise, with xx = x*x, yy = y*y stored as
 * floats, z' = 1 - xx - yy (float), xc = xx*c, yc = yy*c:
 *   m0 = (xc*z' + yc) / (1 - z') + xx    m4 = (yc*z' + xc) / (1 - z') + yy    m8 = yc + xc + z'
 * and the off-diagonal terms from (1 - c) products: m1 = x*y*(1-c) + z*s, m3 = x*y*(1-c) - z*s (x*y*(1-c) unrounded),
 * m2 = z*x*(1-c) - y*s, m6 = z*x*(1-c) + y*s, m5 = y*z*(1-c) + x*s, m7 = y*z*(1-c) - x*s.
 * Which value is stored as a float before use follows the asm exactly (see the test).
 * The angle is declared as its dword (the original only passes it on): with a float parameter gcc -O2 copies it with
 * FLD/FSTP, which changes a signalling NaN. */
void Matrix_AxisAngle(float *param_1, float *param_2, uint param_3) __asm__("_Matrix_AxisAngle");
/* OVERRIDES: Matrix_AxisAngle */
void Matrix_AxisAngle(float *param_1, float *param_2, uint param_3)
{
    float *m = param_1, *ax = param_2;
    float s, c;
    long double D, Dabs;

    SINCOS(param_3, &s, &c);
    D = 1.0L - ax[2];
    Dabs = LT_U(D, 0.0f) ? -D : D;
    if (LE_U(Dabs, 1e-05f))
        D = 0.0f;
    if (!(D < 0.0L || D > 0.0L)) {
        m[0] = st_f(c);
        U32(m[4]) = U32(c);
        m[3] = st_f(-(long double)s);
        U32(m[1]) = U32(s);
    } else {
        D = (long double)ax[2] - -1.0L;
        Dabs = LT_U(D, 0.0f) ? -D : D;
        if (LE_U(Dabs, 1e-05f))
            D = 0.0f;
        if (!(D < 0.0L || D > 0.0L)) {
            m[0] = st_f(c);
            U32(m[4]) = U32(c);
            m[1] = st_f(-(long double)s);
            U32(m[3]) = U32(s);
        } else {
            long double XX, YY, xcE, Z, A, M0, M4, yxoE, zxoE, yzoE, t;
            float ayf, xx, yy, xc, z, yc, omz, omc, yx, sx, sy, sz, zxo, yzo;

            XX = (long double)ax[0] * ax[0];
            ayf = st_f(ax[1]);
            YY = (long double)ax[1] * ayf;
            xx = st_f(XX);
            t = 1.0L - xx;
            xcE = XX * c;
            yy = st_f(YY);
            Z = t - yy;
            xc = st_f(xcE);
            z = st_f(Z);
            A = xcE * z;
            yc = st_f((long double)yy * c);
            A = A + yc;
            omz = st_f(1.0L - z);
            M0 = A / omz;
            omc = st_f(1.0L - c);
            yx = st_f((long double)ax[1] * ax[0]);
            sx = st_f((long double)s * ax[0]);
            sy = st_f((long double)ax[1] * s);
            zxoE = (long double)ax[2] * ax[0] * omc;
            yzoE = (long double)ax[1] * ax[2] * omc;
            sz = st_f((long double)ax[2] * s);
            zxo = st_f(zxoE);
            yzo = st_f(yzoE);
            m[0] = st_f(M0 + xx);
            yxoE = (long double)yx * omc;
            M4 = ((long double)yc * z + xc) / omz;
            U32(m[9]) = 0;
            U32(m[10]) = 0;
            m[4] = st_f(M4 + yy);
            m[8] = st_f(((long double)yc + xc) + z);
            m[1] = st_f((long double)sz + yxoE);
            m[3] = st_f(yxoE - sz);
            m[2] = st_f((long double)zxo - sy);
            m[5] = st_f((long double)yzo + sx);
            m[6] = st_f((long double)zxo + sy);
            m[7] = st_f((long double)yzo - sx);
            U32(m[11]) = 0;
            return;
        }
    }
    U32(m[2]) = 0;
    U32(m[5]) = 0;
    U32(m[6]) = 0;
    U32(m[7]) = 0;
    U32(m[8]) = 0x3f800000;
    U32(m[9]) = 0;
    U32(m[10]) = 0;
    U32(m[11]) = 0;
}

/* ==== rdLight_CalcVertexIntensities (0x00451510) ====
 * Per-vertex light level (monochrome).  out[v] = base[v] (dword copy), then for each light while out[v] is not exactly
 * 1.0f: lights of type >= 2 are culled when |lpos - vertex|^2 >= range^2 (light +0x34; the squared distance sums the
 * extended differences times their float roundings), types < 2 compare 0 < range^2.  Then
 *   type 0/1: dot(n, dir) > 0 adds intensity(+0x18) * dot,
 *   type 2:   L = normalised (lpos - vertex) (rdVector_Normalize3Acc, length stored as a float), dot(n, L) > 0 adds
 *             (I - len * k) * dot,
 *   type 3:   cs = dot(dir, L); if cs > cosOuter(+0x2c): I' = I, or I * (1 - (cosInner(+0x24) - cs) * invRange(+0x30))
 *             when cs < cosInner; adds (I' - len * k) * dot(n, dir), unclamped,
 * then clamps out[v] to 1.0f.  Returns sum(out) / nverts in extended precision (st0; Ghidra declares float, the
 * definition returns long double so the value is the original's unrounded quotient; the symbol is unchanged).
 * BUILD_NOTES: an earlier generated C of this function lit characters wrong (int/float slot confusion of the light
 * counter); here the counter is a plain uint. */
long double rdLight_CalcVertexIntensities(int **lights, float *lpos, float *ldir, uint nlights, float *normals,
                                          float *verts, float *base, float *out, uint nverts, float k)
    __asm__("_rdLight_CalcVertexIntensities");
/* OVERRIDES: rdLight_CalcVertexIntensities */
long double rdLight_CalcVertexIntensities(int **lights, float *lpos, float *ldir, uint nlights, float *normals,
                                          float *verts, float *base, float *out, uint nverts, float k)
{
    float sum = 0.0f;
    float L[3];
    float lenf, cf;

    U32(sum) = 0;
    if (nverts != 0) {
        float *vp = verts, *np = normals, *o = out;
        uint left = nverts;
        do {
            U32(*o) = U32(base[o - out]);
            if (nlights != 0) {
                int **lp = lights;
                float *pp = lpos, *dp = ldir;
                uint li = 0;
                do {
                    int *lt = *lp;
                    float *lf = (float *)lt;
                    long double D2;
                    if (lt[1] < 2) {
                        D2 = 0.0f;
                    } else {
                        long double dx = (long double)pp[0] - vp[0];
                        long double dy = (long double)pp[1] - vp[1];
                        long double dz = (long double)pp[2] - vp[2];
                        long double qx, qy, qz;
                        L[0] = st_f(dx);
                        qx = dx * L[0];
                        L[1] = st_f(dy);
                        qy = dy * L[1];
                        L[2] = st_f(dz);
                        qz = dz * L[2];
                        D2 = (qx + qy) + qz;
                    }
                    if (LT_U(D2, (long double)lf[13] * lf[13])) {
                        long double dot, cs, ip;
                        switch ((uint)lt[1]) {
                        case 0:
                        case 1:
                            dot = ((long double)np[0] * dp[0] + (long double)np[1] * dp[1]) + (long double)np[2] * dp[2];
                            if (!LE_U(dot, 0.0f))
                                *o = st_f((long double)lf[6] * dot + *o);
                            break;
                        case 2:
                            lenf = st_f(rdVector_Normalize3Acc(L));
                            dot = ((long double)np[0] * L[0] + (long double)np[1] * L[1]) + (long double)np[2] * L[2];
                            if (!LE_U(dot, 0.0f))
                                *o = st_f(((long double)lf[6] - (long double)lenf * k) * dot + *o);
                            break;
                        case 3:
                            lenf = st_f(rdVector_Normalize3Acc(L));
                            cs = ((long double)dp[0] * L[0] + (long double)dp[1] * L[1]) + (long double)dp[2] * L[2];
                            cf = st_f(cs);
                            if (LE_U(cs, lf[11]))
                                break;
                            ip = lf[6];
                            if (LT_U(cf, lf[9]))
                                ip = ip * (1.0L - ((long double)lf[9] - cf) * lf[12]);
                            dot = ((long double)np[1] * dp[1] + (long double)np[0] * dp[0]) + (long double)np[2] * dp[2];
                            *o = st_f((ip - (long double)lenf * k) * dot + *o);
                            break;
                        }
                    }
                    if (!LE_U(*o, 1.0f))
                        U32(*o) = 0x3f800000;
                    if (U32(*o) == 0x3f800000)
                        break;
                    lp++;
                    li++;
                    pp += 3;
                    dp += 3;
                } while (li < nlights);
            }
            vp += 3;
            np += 3;
            sum = st_f((long double)sum + *o);
            o++;
        } while (--left != 0);
    }
    return (long double)sum / (long double)(long long)(unsigned long long)nverts;
}

/* ==== rdCanvas_DrawPoint (0x00451dd0) ====
 * Draws a point of radius r (4th argument, a float in an int slot) at (x, y) as a polygon of lines: when the
 * bounding box (x +- R, y +- R with R = trunc(r + 0.5)) touches the canvas rect (+0x18 .. +0x24), the first corner
 * is (trunc(b0*r + 0.5) + x, trunc(a0*r + 0.5) + y) with a0, b0 = stdMath_SinCos(0), then for angle = step,
 * 2*step, ... while the extended sum <= 360 (or unordered) a line to the next corner (rdPrimit2_DrawLine).  The angle
 * is kept as a float, the comparison uses the unrounded sum. */
/* OVERRIDES: rdCanvas_DrawPoint */
void rdCanvas_DrawPoint(void *param_1, int param_2, int param_3, undefined4 param_4, float param_5, int param_6,
                        int param_7)
{
    int *cv = (int *)param_1;
    int x = param_2, y = param_3;
    float r = *(float *)&param_4;
    float sa, sb, ang;
    int R, x0, y0, x1, y1;
    long double t;

    R = p2_ftol((long double)r - -0.5L);
    if (R + x < cv[6] || x - R > cv[8] || R + y < cv[7] || y - R > cv[9])
        return;
    SINCOS(0, &sa, &sb);
    x0 = p2_ftol((long double)sb * r - -0.5L) + x;
    y0 = p2_ftol((long double)sa * r - -0.5L) + y;
    ang = st_f(param_5);
    if (!LE_U(param_5, 360.0f))
        return;
    do {
        SINCOS(U32(ang), &sa, &sb);
        x1 = p2_ftol((long double)sb * r - -0.5L) + x;
        y1 = p2_ftol((long double)sa * r - -0.5L) + y;
        rdPrimit2_DrawLine(param_1, x0, y0, x1, y1, param_6, param_7);
        x0 = x1;
        y0 = y1;
        t = (long double)ang + param_5;
        ang = st_f(t);
    } while (LE_U(t, 360.0f));
}

#endif /* GRIM_EXE */
