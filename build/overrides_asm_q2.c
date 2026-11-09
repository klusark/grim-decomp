/* Readable C for five assembled GRIMFANDANGO.EXE face clippers (agent q2; see docs/notes/asm_q2.md).
 *
 * rdClip_Face3_PosUvLit (0x00449aa0), rdClip_Face3_PosUvLit_2 (0x0044b0a0), rdClip_Face3_PosUvFlags (0x0044be80),
 * rdClip_Face3_PosUvLitColor (0x0044c9d0), rdClip_Face3_PosUvLitFlags (0x0044da40).
 *
 * Every function here was written by hand from the original 1.01 machine code (src/GRIMFANDANGO.EXE/asm_funcs.s as of
 * 2df265d) and checked against it with a differential test in build/difftest/asm_q2/ (original bytes and this C on the
 * same inputs, under the x87 precision controls 24, 53 and 64 bits; return value, every output array, the static work
 * buffers, the pointer / flag globals, the x87 control word and stack top compared).
 *
 * What they do.  Each one is a Sutherland-Hodgman clip of a polygon of `n` vertices against the six planes of the view
 * frustum record `f` (int / float array; f[0] != 0 enables the far plane):
 *   perspective (PosUvLit, PosUvLit_2, PosUvLitColor):  x >= f[12]*y (flag 0x10), x <= f[10]*y (0x20),
 *                                                        z <= f[11]*y (0x04), z >= f[8]*y (0x08)
 *   orthographic (PosUvFlags, PosUvLitFlags):            x >= f[3] (0x10), x <= f[5] (0x20), z <= f[4] (0x04), z >= f[6] (0x08)
 *   then y >= f[1] (near, 0x01) and, when f[0] != 0, y <= f[2] (far, 0x02).
 * A plane that clips something ORs its flag into the global UINT_007f4ac4 (cleared at the start); a polygon that the
 * near plane reduces below 3 vertices also sets 0x40.  The vertex attributes (12-byte positions, optional 8-byte uv,
 * optional float intensity) ping-pong between the caller's arrays and the static buffers 0x007f48c0 (positions),
 * 0x007f46b8 (uv), 0x007f47c0 (intensity): plane 1 writes the static buffers, plane 2 the caller's arrays, and so on.
 * The current input / output buffers are kept in the globals 0x007f47b8 / 0x007f46ac (positions), 0x007f461c /
 * 0x007f46a8 (uv) and 0x007f4618 / 0x007f46b0 (intensity), swapped before each plane.  After a plane that leaves fewer
 * than 3 vertices the function returns that count at once (the arrays then hold whatever the last planes wrote).
 * When the result ends in the static buffers (far plane disabled), it is copied back to the caller's arrays.
 * All five are cdecl and return the vertex count in EAX (Ghidra typed three of them as float), with the x87 stack empty.
 * (The names are Ghidra's guesses: "PosUvLit" clips positions + intensity, "PosUvLit_2" / "PosUvFlags" positions + uv,
 * "PosUvLitColor" / "PosUvLitFlags" positions + uv + intensity; see rdPrimit3_ClipFace in overrides_logic.c.)
 *
 * x87 details kept (the same in every plane of every function; one shared plane routine below):
 *   - side planes, perspective: the bound of the previous vertex k*prev.y is stored as a float before it is compared,
 *     the bound of the current vertex k*cur.y is compared unrounded.  The intersection: dy, da (a = x or z) stored as
 *     floats, den = k*dyF - daF compared with 0 unrounded but divided by as the float, N = cur.y*prev.a - prev.y*cur.a
 *     (extended), Y = N / denF (N when den is 0 or NaN), kY = float(k*Y); t = (Y - prev.y)/dyF when |dyF| > |daF|,
 *     else (kY - prev.a)/daF; the new vertex is a = kY, y = float(Y), the rest (c - p)*t + p rounded at the store.
 *   - side planes, orthographic: t = (c - prev.a)/(cur.a - prev.a), a = c (through FLD/FSTP).
 *   - near / far: t = (c - prev.y)/(cur.y - prev.y), y = the dword of f[1] / f[2] (MOV).
 *   - the unordered (NaN) results of the compares differ between the planes and between the "both outside", the
 *     "edge crosses" and the "keep the current vertex" tests; each is written out per plane kind below.
 *   - kept vertices are copied as dwords (MOV), so NaN bits survive.
 * Not reproduced (no effect on the caller): the original writes temporaries into its own parameter slots. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#define rdClip_Face3_PosUvLit rdClip_Face3_PosUvLit__ghidra
#define rdClip_Face3_PosUvLit_2 rdClip_Face3_PosUvLit_2__ghidra
#define rdClip_Face3_PosUvFlags rdClip_Face3_PosUvFlags__ghidra
#define rdClip_Face3_PosUvLitColor rdClip_Face3_PosUvLitColor__ghidra
#define rdClip_Face3_PosUvLitFlags rdClip_Face3_PosUvLitFlags__ghidra
#include "functions.h"
#undef rdClip_Face3_PosUvLit
#undef rdClip_Face3_PosUvLit_2
#undef rdClip_Face3_PosUvFlags
#undef rdClip_Face3_PosUvLitColor
#undef rdClip_Face3_PosUvLitFlags

#define Q2_U32(lv) (*(uint *)&(lv))
/* C3 of an x87 compare: equal or unordered */
#define Q2_EQU(a, b) (!((a) < (b)) && !((a) > (b)))

static inline float q2_st_f(long double x)
{
    volatile float f = (float)x;
    return f;
}

/* the caller's arrays or the static buffers of one plane pass */
typedef struct {
    float *pos;  /* 3 floats per vertex */
    float *uv;   /* 2 floats per vertex, or 0 */
    float *li;   /* 1 float per vertex, or 0 */
} q2_bufs;

enum { Q2_GE, Q2_LE, Q2_NEAR, Q2_FAR };

typedef struct {
    int kind;    /* Q2_GE: a >= bound, Q2_LE: a <= bound, Q2_NEAR: y >= f[1], Q2_FAR: y <= f[2] */
    int axis;    /* a: 0 = x, 2 = z (side planes) */
    int fidx;    /* f[fidx]: the slope (perspective) or the constant (orthographic, near, far) */
    uint flag;
} q2_plane;

static const q2_plane q2_persp[6] = {
    {Q2_GE, 0, 12, 0x10}, {Q2_LE, 0, 10, 0x20}, {Q2_LE, 2, 11, 0x04}, {Q2_GE, 2, 8, 0x08},
    {Q2_NEAR, 1, 1, 0x01}, {Q2_FAR, 1, 2, 0x02}};
static const q2_plane q2_ortho[6] = {
    {Q2_GE, 0, 3, 0x10}, {Q2_LE, 0, 5, 0x20}, {Q2_LE, 2, 4, 0x04}, {Q2_GE, 2, 6, 0x08},
    {Q2_NEAR, 1, 1, 0x01}, {Q2_FAR, 1, 2, 0x02}};

/* one Sutherland-Hodgman pass; returns the new count (0 when n <= 0) */
static int q2_clip_plane(const float *f, int persp, const q2_plane *pl, const q2_bufs *in, const q2_bufs *out, int n)
{
    const float *prev, *cur, *pu = 0, *cu = 0, *pi = 0, *ci = 0;
    int a = pl->axis, o = 2 - pl->axis;   /* o: the other horizontal axis (side planes) */
    int cnt = 0, left;

    if (n <= 0)
        return 0;
    prev = in->pos + (n - 1) * 3;
    cur = in->pos;
    if (in->uv) {
        pu = in->uv + (n - 1) * 2;
        cu = in->uv;
    }
    if (in->li) {
        pi = in->li + (n - 1);
        ci = in->li;
    }
    for (left = n; left != 0; left--) {
        int skip, cross, keep;
        long double t, A, B;
        float k = 0.0f;

        /* the three tests */
        if (pl->kind == Q2_GE || pl->kind == Q2_LE) {
            if (persp) {
                k = f[pl->fidx];
                A = q2_st_f((long double)prev[1] * k);   /* stored as a float before the compare */
                B = (long double)k * cur[1];               /* compared unrounded */
            } else {
                A = f[pl->fidx];
                B = f[pl->fidx];
            }
            if (pl->kind == Q2_GE) {
                skip = !(prev[a] >= A) && B > cur[a];
                cross = !Q2_EQU(prev[a], A) && !Q2_EQU(B, cur[a]) && (prev[a] < A || B > cur[a]);
                keep = !(B > cur[a]);
            } else {
                skip = prev[a] > A && !(B >= cur[a]);
                cross = !Q2_EQU(prev[a], A) && !Q2_EQU(B, cur[a]) && (prev[a] > A || B < cur[a]);
                keep = B >= cur[a];
            }
        } else {
            float c = f[pl->fidx];
            if (pl->kind == Q2_NEAR) {
                skip = !(prev[1] >= c) && !(cur[1] >= c);
                cross = !Q2_EQU(prev[1], c) && !Q2_EQU(cur[1], c) && (prev[1] < c || cur[1] < c);
                keep = cur[1] >= c;
            } else {
                skip = prev[1] > c && cur[1] > c;
                cross = !Q2_EQU(prev[1], c) && !Q2_EQU(cur[1], c) && (prev[1] > c || cur[1] > c);
                keep = !(cur[1] > c);
            }
        }

        if (!skip) {
            if (cross) {
                float *op = out->pos + cnt * 3;
                if (pl->kind == Q2_NEAR || pl->kind == Q2_FAR) {
                    t = ((long double)f[pl->fidx] - prev[1]) / ((long double)cur[1] - prev[1]);
                    Q2_U32(op[1]) = ((const uint *)f)[pl->fidx];
                    op[2] = q2_st_f(((long double)cur[2] - prev[2]) * t + prev[2]);
                    op[0] = q2_st_f(((long double)cur[0] - prev[0]) * t + prev[0]);
                } else if (persp) {
                    long double dy = (long double)cur[1] - prev[1];
                    long double da = (long double)cur[a] - prev[a];
                    float dyF = q2_st_f(dy), daF = q2_st_f(da), denF, kY;
                    long double den = (long double)k * dyF - daF;
                    long double N, Y, ady, ada;
                    denF = q2_st_f(den);
                    N = (long double)cur[1] * prev[a] - (long double)prev[1] * cur[a];
                    Y = (den < 0.0L || den > 0.0L) ? N / denF : N;
                    kY = q2_st_f((long double)k * Y);
                    ady = dyF < 0.0f ? -(long double)dyF : (long double)dyF;
                    ada = daF < 0.0f ? -(long double)daF : (long double)daF;
                    if (ady > ada)
                        t = (Y - prev[1]) / dyF;
                    else
                        t = ((long double)kY - prev[a]) / daF;
                    op[o] = q2_st_f(((long double)cur[o] - prev[o]) * t + prev[o]);
                    op[a] = kY;
                    op[1] = q2_st_f(Y);
                } else {
                    long double c = f[pl->fidx];
                    t = (c - prev[a]) / ((long double)cur[a] - prev[a]);
                    op[a] = q2_st_f(c);
                    op[1] = q2_st_f(((long double)cur[1] - prev[1]) * t + prev[1]);
                    op[o] = q2_st_f(((long double)cur[o] - prev[o]) * t + prev[o]);
                }
                if (in->uv) {
                    float *ou = out->uv + cnt * 2;
                    ou[0] = q2_st_f(((long double)cu[0] - pu[0]) * t + pu[0]);
                    ou[1] = q2_st_f(((long double)cu[1] - pu[1]) * t + pu[1]);
                }
                if (in->li)
                    out->li[cnt] = q2_st_f(((long double)*ci - *pi) * t + *pi);
                UINT_007f4ac4 |= pl->flag;
                cnt++;
            }
            if (keep) {
                float *op = out->pos + cnt * 3;
                Q2_U32(op[0]) = Q2_U32(cur[0]);
                Q2_U32(op[1]) = Q2_U32(cur[1]);
                Q2_U32(op[2]) = Q2_U32(cur[2]);
                if (in->uv) {
                    Q2_U32(out->uv[cnt * 2]) = Q2_U32(cu[0]);
                    Q2_U32(out->uv[cnt * 2 + 1]) = Q2_U32(cu[1]);
                }
                if (in->li)
                    Q2_U32(out->li[cnt]) = Q2_U32(*ci);
                cnt++;
            }
        }
        prev = cur;
        cur += 3;
        if (in->uv) {
            pu = cu;
            cu += 2;
        }
        if (in->li) {
            pi = ci;
            ci++;
        }
    }
    return cnt;
}

static void q2_copy(uint *dst, const uint *src, int dwords)
{
    while (dwords-- > 0)
        *dst++ = *src++;
}

/* the whole clip: planes in order, buffers ping-ponging through the globals */
static int q2_clip(const int *frustum, int persp, float *pos, float *uv, float *li, int n)
{
    const float *f = (const float *)frustum;
    const q2_plane *planes = persp ? q2_persp : q2_ortho;
    int p;

    UINT_007f4ac4 = 0;
    UINT_007f47b8 = (uint)pos;
    UINT_007f46ac = (uint)&UINT_007f48c0;
    if (uv) {
        UINT_007f461c = (uint)uv;
        UINT_007f46a8 = (uint)&UINT_007f46b8;
    }
    if (li) {
        UINT_007f4618 = (uint)li;
        UINT_007f46b0 = (uint)&UINT_007f47c0;
    }
    for (p = 0; p < 6; p++) {
        q2_bufs in, out;
        if (p == 5 && frustum[0] == 0)
            break;
        if (p > 0) {
            uint s = UINT_007f47b8;
            UINT_007f47b8 = UINT_007f46ac;
            UINT_007f46ac = s;
            if (uv) {
                s = UINT_007f461c;
                UINT_007f461c = UINT_007f46a8;
                UINT_007f46a8 = s;
            }
            if (li) {
                s = UINT_007f4618;
                UINT_007f4618 = UINT_007f46b0;
                UINT_007f46b0 = s;
            }
        }
        in.pos = (float *)UINT_007f47b8;
        out.pos = (float *)UINT_007f46ac;
        in.uv = uv ? (float *)UINT_007f461c : 0;
        out.uv = uv ? (float *)UINT_007f46a8 : 0;
        in.li = li ? (float *)UINT_007f4618 : 0;
        out.li = li ? (float *)UINT_007f46b0 : 0;
        n = q2_clip_plane(f, persp, &planes[p], &in, &out, n);
        if (n < 3) {
            if (p == 4)
                UINT_007f4ac4 |= 0x40;
            return n;
        }
    }
    if ((float *)UINT_007f46ac != pos) {
        q2_copy((uint *)pos, (const uint *)UINT_007f46ac, n * 3);
        if (uv)
            q2_copy((uint *)uv, (const uint *)UINT_007f46a8, n * 2);
        if (li)
            q2_copy((uint *)li, (const uint *)UINT_007f46b0, n);
    }
    return n;
}

/* ==== rdClip_Face3_PosUvLit (0x00449aa0) ====
 * Perspective clip of positions + one intensity per vertex.  Returns the count (Ghidra: float). */
/* OVERRIDES: rdClip_Face3_PosUvLit */
uint rdClip_Face3_PosUvLit(int *param_1, float *param_2, float *param_3, int param_4)
{
    return (uint)q2_clip(param_1, 1, param_2, 0, param_3, param_4);
}

/* ==== rdClip_Face3_PosUvLit_2 (0x0044b0a0) ====
 * Perspective clip of positions + uv.  Returns the count (Ghidra: float). */
/* OVERRIDES: rdClip_Face3_PosUvLit_2 */
uint rdClip_Face3_PosUvLit_2(int *param_1, float *param_2, float *param_3, int param_4)
{
    return (uint)q2_clip(param_1, 1, param_2, param_3, 0, param_4);
}

/* ==== rdClip_Face3_PosUvFlags (0x0044be80) ====
 * Orthographic clip of positions + uv. */
/* OVERRIDES: rdClip_Face3_PosUvFlags */
uint rdClip_Face3_PosUvFlags(int *param_1, float *param_2, float *param_3, int param_4)
{
    return (uint)q2_clip(param_1, 0, param_2, param_3, 0, param_4);
}

/* ==== rdClip_Face3_PosUvLitColor (0x0044c9d0) ====
 * Perspective clip of positions + uv + intensity.  Returns the count (Ghidra: float). */
/* OVERRIDES: rdClip_Face3_PosUvLitColor */
uint rdClip_Face3_PosUvLitColor(int *param_1, float *param_2, float *param_3, float *param_4, int param_5)
{
    return (uint)q2_clip(param_1, 1, param_2, param_3, param_4, param_5);
}

/* ==== rdClip_Face3_PosUvLitFlags (0x0044da40) ====
 * Orthographic clip of positions + uv + intensity. */
/* OVERRIDES: rdClip_Face3_PosUvLitFlags */
uint rdClip_Face3_PosUvLitFlags(int *param_1, float *param_2, float *param_3, float *param_4, int param_5)
{
    return (uint)q2_clip(param_1, 0, param_2, param_3, param_4, param_5);
}

#endif /* GRIM_EXE */
