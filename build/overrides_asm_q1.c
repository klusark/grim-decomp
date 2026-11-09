/* Readable C for assembled GRIMFANDANGO.EXE functions, assembly-to-C round "q" (agent q1; see docs/notes/asm_q1.md):
 * rdClip_Line2D and five of the rdClip_Face3_* frustum clippers (Pos, PosB, Pos_2, PosB_2, PosUv).
 *
 * Every function here was written by hand from the original 1.01 machine code (src/GRIMFANDANGO.EXE/asm_funcs.s as of
 * 2df265d) and checked against it with a differential test in build/difftest/asm_q1/ (original bytes and this C on the
 * same inputs under the x87 precision controls 24, 53 and 64 bits; return value, every buffer, the static clip buffers
 * and pointer / flag globals, the call log, the x87 control word and stack top compared).
 *
 * x87 conventions used below (as in overrides_asm_p2.c):
 *   - `long double` holds a value that the original keeps on the x87 stack (extended precision, rounded only by the
 *     precision control); q1_st_f() is a store of such a value to a float slot (FSTP m32), through a volatile so the
 *     rounding happens at that point at every optimisation level.
 *   - Q1_LT_U(a, b): `fcom; test ah,1` taken = a < b or unordered.  Q1_LE_U(a, b): `test ah,0x41` = a <= b or
 *     unordered.  Q1_EQ_U(a, b): `test ah,0x40` = a == b or unordered.  The first operand is the one on the x87 stack.
 *   - A float that the original copies with MOV (no FLD/FSTP) is copied as a dword (Q1_U32), so a signalling NaN keeps
 *     its bits; a float that goes through FLD/FSTP is stored with q1_st_f (a signalling NaN becomes quiet).
 *
 * Not reproduced (no effect on callers): the originals use their own parameter slots as scratch (rdClip_Line2D keeps x0
 * in the canvas slot, the Face3 clippers keep plane bounds / loop counters / DY in the frustum, count or position
 * slots).  The C uses locals. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

#define Q1_U32(lv) (*(uint *)&(lv))
#define Q1_LT_U(a, b) (!((long double)(a) >= (long double)(b)))
#define Q1_LE_U(a, b) (!((long double)(a) > (long double)(b)))
#define Q1_EQ_U(a, b) (!((long double)(a) < (long double)(b) || (long double)(a) > (long double)(b)))

static inline float q1_st_f(long double x)
{
    volatile float f = (float)x;
    return f;
}

/* FCHS as a separate step (gcc -O2 could otherwise fold it into a neighbouring operation) */
static inline long double q1_neg(long double x)
{
    volatile long double v = -x;
    return v;
}

/* _ftol: truncation of the x87 value to a 64-bit integer, low dword */
static inline int q1_ftol(long double x)
{
    return (int)(long long)x;
}

/* ==== rdClip_Line2D (0x00446c10) ====
 * Cohen-Sutherland clip of the integer line (*x0, *y0) - (*x1, *y1) against the canvas rectangle (canvas+0x18 left,
 * +0x1c top, +0x20 right, +0x24 bottom, ints; outcodes from rdClip_Outcode2D: 1 left, 0x10 right, 0x1000 top,
 * 0x100 bottom).  Returns 1 with the clipped end points written back (each truncated from its float), 0 when the line is
 * outside.  Both end points inside: returns 1 without writing anything.
 * x87 details kept:
 *   - the end points become floats (FILD/FST); "vertical" compares the exact integer x0 with float(x1), "horizontal"
 *     compares float(y0) with float(y1); both are decided once, before the loop.
 *   - the end point with a non-zero outcode (the first one if both) is moved: for top / bottom the new x is
 *     x0 + (edge - y0) * ((x1 - x0) / (y1 - y0)) kept in extended precision (x0 itself for a vertical line), the new y is
 *     the integer edge; for left / right the new y is the same formula stored as a float first (y0 for a horizontal
 *     line), the new x the integer edge.  The outcode of the new point is taken from _ftol of these unrounded values,
 *     while the stored end point is their float.
 *   - the final write-back truncates the floats with _ftol (64-bit conversion, low dword). */
/* OVERRIDES: rdClip_Line2D */
undefined4 rdClip_Line2D(undefined4 param_1, undefined4 *param_2, undefined4 *param_3, undefined4 *param_4,
                         undefined4 *param_5)
{
    int canvas = (int)param_1;
    uint o0, o1;
    float x0, y0, x1, y1, tmp;
    int vert, horz, ix0;

    o0 = rdClip_Outcode2D(canvas, *param_2, *param_3);
    o1 = rdClip_Outcode2D(canvas, *param_4, *param_5);
    if (o0 == 0 && o1 == 0)
        return 1;
    if ((o0 & o1) != 0)
        return 0;
    ix0 = (int)*param_2;
    x0 = q1_st_f((long double)ix0);
    x1 = q1_st_f((long double)(int)*param_4);
    vert = Q1_EQ_U((long double)ix0, x1);
    y0 = q1_st_f((long double)(int)*param_3);
    y1 = q1_st_f((long double)(int)*param_5);
    horz = Q1_EQ_U(y0, y1);
    for (;;) {
        uint o = o0 != 0 ? o0 : o1;
        long double nx, ny;
        if ((o & 0x1000) != 0 || (o & 0x100) != 0) {
            int edge = *(int *)(canvas + ((o & 0x1000) != 0 ? 0x1c : 0x24));
            if (vert)
                nx = x0;
            else
                nx = ((long double)edge - y0) * (((long double)x1 - x0) / ((long double)y1 - y0)) + x0;
            ny = (long double)edge;
        } else {
            int edge = *(int *)(canvas + ((o & 0x10) != 0 ? 0x20 : 0x18));
            if (horz)
                Q1_U32(tmp) = Q1_U32(y0);
            else
                tmp = q1_st_f(((long double)edge - x0) * (((long double)y1 - y0) / ((long double)x1 - x0)) + y0);
            nx = (long double)edge;
            ny = tmp;
        }
        if (o == o0) {
            x0 = q1_st_f(nx);
            y0 = q1_st_f(ny);
            o0 = rdClip_Outcode2D(canvas, q1_ftol(nx), q1_ftol(ny));
        } else {
            x1 = q1_st_f(nx);
            y1 = q1_st_f(ny);
            o1 = rdClip_Outcode2D(canvas, q1_ftol(nx), q1_ftol(ny));
        }
        if (o0 == 0 && o1 == 0)
            break;
        if ((o0 & o1) != 0)
            return 0;
    }
    *param_2 = q1_ftol(x0);
    *param_3 = q1_ftol(y0);
    *param_4 = q1_ftol(x1);
    *param_5 = q1_ftol(y1);
    return 1;
}

/* ==== rdClip_Face3_* frustum clippers: one Sutherland-Hodgman pass ====
 * The frustum record fr (the clippers' param_1): int fr[0] != 0 enables the far plane, fr[1] near y, fr[2] far y,
 * fr[3] / fr[5] the x bounds and fr[4] / fr[6] the z bounds of an orthographic view, fr[7..12] the slopes of the
 * perspective side planes (bound = slope * y).  Depth is y.
 *
 * Each pass reads n vertices (3 floats; plus one intensity for PosUv) from `in` and writes the clipped polygon to `out`;
 * the edge runs from the previous vertex P (the last one for the first edge) to the current vertex C.  The original
 * repeats the pass inline for each plane with small differences, all kept here:
 *
 *   pattern GE (x / z planes 1 and 4): P is in when !LT_U(P, a), C is in when LE_U(b, C)
 *   pattern LE (x / z planes 2 and 3): P is in when LE_U(P, a),  C is in when !LT_U(b, C)
 *   near:  in when !LT_U(v, near) (both ends);  far: in when LE_U(v, far) (both ends)
 *   (a = b = the bound for the orthographic planes; for the perspective planes a = float(slope * P.y) and
 *   b = slope * C.y unrounded.)  An edge with an end in is handled: the intersection is added when neither end is
 *   exactly on the plane (EQ_U, unordered counts as on it) and one end is out; then C is added (dword copy) when it is in.
 *
 * Intersections (all stores FSTP to float unless noted):
 *   perspective x plane (slope k): DY = float(C.y - P.y), DX = float(C.x - P.x), den = k*DY - DX (extended),
 *     s = C.y*P.x - P.y*C.x, divided by float(den) unless den (extended) == 0 or unordered; X = float(k*s);
 *     u = (X - P.x) / DX when LE_U(|DY|, |DX|), else (s - P.y) / DY; out = (X, s, (C.z - P.z)*u + P.z).
 *   perspective z plane: the same with z for x, but Z = k*s stays extended (for u and the stored z):
 *     out = ((C.x - P.x)*u + P.x, s, Z).
 *   orthographic plane (bound k): t = (k - P.c) / (C.c - P.c); the clipped coordinate is FLD/FSTP of k, the others
 *     (C - P)*t + P.  Intensity (PosUv): (C.i - P.i)*t + P.i.
 *   near / far: t = (k - P.y) / (C.y - P.y); y is a dword copy of fr[1] / fr[2]; z, then x as above; then intensity.
 * Every intersection ORs the plane's bit into the clip flags UINT_007f4ac4. */
enum { Q1_GE, Q1_LE, Q1_NEAR, Q1_FAR };

static int q1_pass(float *fr, int kidx, int c, int pat, int persp, uint flag, int n, float *in, float *out,
                   float *iin, float *iout)
{
    float k = fr[kidx];
    float *P = in + n * 3 - 3, *C = in;
    float *IP = iin != 0 ? iin + n - 1 : 0, *IC = iin;
    int cnt = 0, left;

    for (left = n; left > 0; left--) {
        long double a, b;
        int inP, inC, eq, outP, outC;

        if (persp) {
            a = q1_st_f((long double)P[1] * k);
            b = (long double)C[1] * k;
        } else {
            a = k;
            b = k;
        }
        switch (pat) {
        case Q1_GE:
            inP = !Q1_LT_U(P[c], a);
            inC = Q1_LE_U(b, C[c]);
            eq = Q1_EQ_U(P[c], a) || Q1_EQ_U(b, C[c]);
            outP = Q1_LT_U(P[c], a);
            outC = !Q1_LE_U(b, C[c]);
            break;
        case Q1_LE:
            inP = Q1_LE_U(P[c], a);
            inC = !Q1_LT_U(b, C[c]);
            eq = Q1_EQ_U(P[c], a) || Q1_EQ_U(b, C[c]);
            outP = !Q1_LE_U(P[c], a);
            outC = Q1_LT_U(b, C[c]);
            break;
        case Q1_NEAR:
            inP = !Q1_LT_U(P[1], k);
            inC = !Q1_LT_U(C[1], k);
            eq = Q1_EQ_U(P[1], k) || Q1_EQ_U(C[1], k);
            outP = Q1_LT_U(P[1], k);
            outC = Q1_LT_U(C[1], k);
            break;
        default:   /* Q1_FAR */
            inP = Q1_LE_U(P[1], k);
            inC = Q1_LE_U(C[1], k);
            eq = Q1_EQ_U(P[1], k) || Q1_EQ_U(C[1], k);
            outP = !Q1_LE_U(P[1], k);
            outC = !Q1_LE_U(C[1], k);
            break;
        }
        if (inP || inC) {
            if (!eq && (outP || outC)) {
                float *o = out + cnt * 3;
                long double t = 0.0L;
                cnt++;
                if (pat == Q1_NEAR || pat == Q1_FAR) {
                    t = ((long double)k - P[1]) / ((long double)C[1] - P[1]);
                    Q1_U32(o[1]) = Q1_U32(fr[kidx]);
                    o[2] = q1_st_f(((long double)C[2] - P[2]) * t + P[2]);
                    o[0] = q1_st_f(((long double)C[0] - P[0]) * t + P[0]);
                } else if (!persp) {
                    t = ((long double)k - P[c]) / ((long double)C[c] - P[c]);
                    if (c == 0) {
                        o[0] = q1_st_f(k);
                        o[1] = q1_st_f(((long double)C[1] - P[1]) * t + P[1]);
                        o[2] = q1_st_f(((long double)C[2] - P[2]) * t + P[2]);
                    } else {
                        o[0] = q1_st_f(((long double)C[0] - P[0]) * t + P[0]);
                        o[1] = q1_st_f(((long double)C[1] - P[1]) * t + P[1]);
                        o[2] = q1_st_f(k);
                    }
                } else {
                    float DY, DC, DEN, X;
                    long double den, s, aDY, aDC, u, Z;
                    DY = q1_st_f((long double)C[1] - P[1]);
                    DC = q1_st_f((long double)C[c] - P[c]);
                    den = (long double)k * DY - DC;
                    s = (long double)C[1] * P[c] - (long double)P[1] * C[c];
                    DEN = q1_st_f(den);
                    if (!Q1_EQ_U(den, 0.0f))
                        s = s / DEN;
                    Z = (long double)k * s;
                    aDY = DY;
                    if (Q1_LT_U(DY, 0.0f))
                        aDY = q1_neg(aDY);
                    aDC = DC;
                    if (Q1_LT_U(DC, 0.0f))
                        aDC = q1_neg(aDC);
                    if (c == 0) {
                        X = q1_st_f(Z);
                        if (Q1_LE_U(aDY, aDC))
                            u = ((long double)X - P[0]) / DC;
                        else
                            u = (s - P[1]) / DY;
                        Q1_U32(o[0]) = Q1_U32(X);
                        o[1] = q1_st_f(s);
                        o[2] = q1_st_f(((long double)C[2] - P[2]) * u + P[2]);
                    } else {
                        if (Q1_LE_U(aDY, aDC))
                            u = (Z - P[2]) / DC;
                        else
                            u = (s - P[1]) / DY;
                        o[0] = q1_st_f(((long double)C[0] - P[0]) * u + P[0]);
                        o[1] = q1_st_f(s);
                        o[2] = q1_st_f(Z);
                    }
                }
                if (iin != 0)
                    iout[cnt - 1] = q1_st_f(((long double)*IC - *IP) * t + *IP);
                UINT_007f4ac4 |= flag;
            }
            if (inC) {
                float *o = out + cnt * 3;
                Q1_U32(o[0]) = Q1_U32(C[0]);
                Q1_U32(o[1]) = Q1_U32(C[1]);
                Q1_U32(o[2]) = Q1_U32(C[2]);
                if (iin != 0)
                    Q1_U32(iout[cnt]) = Q1_U32(*IC);
                cnt++;
            }
        }
        P = C;
        C += 3;
        if (iin != 0) {
            IP = IC;
            IC++;
        }
    }
    return cnt;
}

/* The whole clip: the four side planes, near, far (when fr[0] != 0).  Positions ping-pong between the caller's array
 * and the static buffer UINT_007f48c0 (UINT_007f46ac = output, UINT_007f47b8 = input of the current pass); with
 * intensities (PosUv) they ping-pong between the caller's array and UINT_007f47c0 (UINT_007f46b0 = output,
 * UINT_007f4618 = input).  A pass that leaves fewer than 3 vertices ends the clip and returns that count (the near
 * pass also sets flag 0x40 then); otherwise the result is copied back (dwords) when it ended in the static buffer.
 * side[] = slope / bound indices of the x GE, x LE, z LE and z GE planes. */
static uint q1_clip(int *param_1, float *pos, float *inten, int n, const int *side, int persp)
{
    float *fr = (float *)param_1;
    float *src = pos, *dst = (float *)&UINT_007f48c0, *isrc = inten, *idst = (float *)&UINT_007f47c0, *tmp;
    static const int coord[4] = {0, 0, 2, 2}, pat[4] = {Q1_GE, Q1_LE, Q1_LE, Q1_GE};
    static const uint bit[4] = {0x10, 0x20, 4, 8};
    int cnt = n, i;

    UINT_007f4ac4 = 0;
    for (i = 0; i < 6; i++) {
        if (i > 0) {
            if (i == 5 && param_1[0] == 0)
                break;
            tmp = src; src = dst; dst = tmp;
            tmp = isrc; isrc = idst; idst = tmp;
        }
        UINT_007f47b8 = (uint)src;
        UINT_007f46ac = (uint)dst;
        if (inten != 0) {
            UINT_007f4618 = (uint)isrc;
            UINT_007f46b0 = (uint)idst;
        }
        if (i < 4)
            cnt = q1_pass(fr, side[i], coord[i], pat[i], persp, bit[i], cnt, src, dst, inten ? isrc : 0, idst);
        else if (i == 4)
            cnt = q1_pass(fr, 1, 1, Q1_NEAR, 0, 1, cnt, src, dst, inten ? isrc : 0, idst);
        else
            cnt = q1_pass(fr, 2, 1, Q1_FAR, 0, 2, cnt, src, dst, inten ? isrc : 0, idst);
        if (cnt < 3) {
            if (i == 4)
                UINT_007f4ac4 |= 0x40;
            return (uint)cnt;
        }
    }
    if (dst != pos) {
        for (i = 0; i < cnt * 3; i++)
            Q1_U32(pos[i]) = Q1_U32(dst[i]);
        if (inten != 0)
            for (i = 0; i < cnt; i++)
                Q1_U32(inten[i]) = Q1_U32(idst[i]);
    }
    return (uint)cnt;
}

/* ==== rdClip_Face3_Pos (0x004478c0) ====
 * Perspective clip of a position-only polygon: side slopes fr[9] (x, GE), fr[10] (x, LE), fr[7] (z, LE), fr[8] (z, GE).
 * Returns the new vertex count (cdecl, EAX; the x87 stack is left empty). */
/* OVERRIDES: rdClip_Face3_Pos */
uint rdClip_Face3_Pos(int *param_1, float *param_2, uint param_3)
{
    static const int side[4] = {9, 10, 7, 8};
    return q1_clip(param_1, param_2, 0, (int)param_3, side, 1);
}

/* ==== rdClip_Face3_Pos_2 (0x004489b0) ====
 * Same machine code as rdClip_Face3_Pos with the slopes fr[12] (x, GE), fr[10] (x, LE), fr[11] (z, LE), fr[8] (z, GE)
 * (the zero constant it compares with is another copy of 0.0f). */
/* OVERRIDES: rdClip_Face3_Pos_2 */
uint rdClip_Face3_Pos_2(int *param_1, float *param_2, uint param_3)
{
    static const int side[4] = {12, 10, 11, 8};
    return q1_clip(param_1, param_2, 0, (int)param_3, side, 1);
}

/* ==== rdClip_Face3_PosB (0x00448260), rdClip_Face3_PosB_2 (0x00449350) ====
 * Orthographic clip of a position-only polygon: x bounds fr[3] (GE) / fr[5] (LE), z bounds fr[4] (LE) / fr[6] (GE).
 * The two functions are identical machine code. */
/* OVERRIDES: rdClip_Face3_PosB */
int rdClip_Face3_PosB(int *param_1, float *param_2, int param_3)
{
    static const int side[4] = {3, 5, 4, 6};
    return (int)q1_clip(param_1, param_2, 0, param_3, side, 0);
}

/* OVERRIDES: rdClip_Face3_PosB_2 */
int rdClip_Face3_PosB_2(int *param_1, float *param_2, int param_3)
{
    static const int side[4] = {3, 5, 4, 6};
    return (int)q1_clip(param_1, param_2, 0, param_3, side, 0);
}

/* ==== rdClip_Face3_PosUv (0x0044a6d0) ====
 * Orthographic clip (as PosB) of a polygon with one intensity per vertex (param_3; Ghidra's name is a guess, there are
 * no uvs).  rdPrimit3_ClipFace uses it for geometry 3 / lighting 3 with a non-perspective camera. */
/* OVERRIDES: rdClip_Face3_PosUv */
uint rdClip_Face3_PosUv(int *param_1, float *param_2, float *param_3, uint param_4)
{
    static const int side[4] = {3, 5, 4, 6};
    return q1_clip(param_1, param_2, param_3, (int)param_4, side, 0);
}

#endif /* GRIM_EXE */
