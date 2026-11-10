/* Collision_TestActorAgainstOthers (GRIMFANDANGO.EXE 1.01, 0x004939f0), written by hand from the original machine code
 * (agent big_collision_others; notes: docs/notes/big_collision_others.md, differential test:
 * build/difftest/big_collision_others/).
 *
 * Why the decompiled text could not be compiled: the loop index and the actor-list cursor live in stack slots that Ghidra
 * typed float (`local_74[1] = (float)&g_pDrawableActors`, `local_5c[2] = (float)((int)local_5c[2] + 1)`: a value
 * conversion of an address, the cursor becomes garbage), and the float vectors 0x008ca320 / 338 / 348 are reached through
 * `_DAT_... (*(undefined4 *)&DAT_...)`, so `_DAT_008ca320 = _DAT_008ca320 - local_98[0]` converts the float BITS as an
 * integer value, subtracts and converts back.  Here every slot has its real type.
 *
 * x87: every temporary the original keeps on the FPU stack is a long double here, every value it stores to a float slot
 * goes through cto_st() (a volatile float: rounds at any optimisation level), and the comparisons keep the original
 * NaN behaviour (FCOM + TEST AH). */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

typedef long double ld_t;

/* A store of an x87 value to a float slot of the original: rounds to float at any optimisation level (with gcc's
 * default -fexcess-precision=fast neither an assignment nor a (float) cast is guaranteed to round once optimised). */
static inline float cto_st(ld_t x)
{
    volatile float f = x;
    return f;
}

static inline ld_t cto_fsqrt(ld_t x)
{
    __asm__("fsqrt" : "+t"(x));
    return x;
}

#define CTO_F(p, off) (*(float *)((char *)(p) + (off)))
#define CTO_I(p, off) (*(int *)((char *)(p) + (off)))
#define CTO_P(p, off) (*(char **)((char *)(p) + (off)))
/* actor: +0x08 flags (bit 0: walking), +0x0c position, +0x18 previous position, +0x34 frame valid, +0x38 frame,
 * +0xa0 costume, +0xa4 walker record (+0x38 path, +0x3c path points (12 bytes), +0x44 current point,
 * +0x3f0 collision mode (0 off, 1 box, 2 sphere), +0x3f4 collision scale, +0x3f8 collided this frame).
 * model (costume +4 -> +4): +0x5c radius, +0x60..+0x74 bounding box (min xyz, max xyz), +0x78 centre. */
#define CTO_MODEL(a) CTO_P(CTO_P(CTO_P((a), 0xa0), 4), 4)

/* Copies three dwords (bit copy, as the original's MOVs). */
static inline void cto_copy3(void *dst, const void *src)
{
    ((uint *)dst)[0] = ((const uint *)src)[0];
    ((uint *)dst)[1] = ((const uint *)src)[1];
    ((uint *)dst)[2] = ((const uint *)src)[2];
}

/* OVERRIDES: Collision_TestActorAgainstOthers */
/* ==== Collision_TestActorAgainstOthers (0x004939f0) ====
 * Tests actor `self` against every other drawable actor with collisions on.  Both sphere radii (model radius * collision
 * scale) around the world-space model centres are compared first.  Mode 2 of the other actor: both are marked collided
 * and self is pushed back along the centre line to the touching distance.  Other modes: self's centre is taken into the
 * other's model space and tested against the other's bounding box grown by self's radius; when inside, the move from
 * the previous position is slid along the box (Collision_BoxSlide; when that fails, pushed out of it), self is moved, a
 * walking actor replans its path.  Every hit ends with Sector_IntersectSegment(self, other, start, hit point, end) on the
 * vectors 0x008ca348 (position before), 0x008ca320 (hit point), 0x008ca338 (position after).  Always returns 1. */
undefined4 Collision_TestActorAgainstOthers(void *param_1)
{
    char *self = (char *)param_1;
    float *g320 = (float *)&DAT_008ca320;   /* hit point */
    float *g338 = (float *)&DAT_008ca338;   /* position after */
    float *g348 = (float *)&DAT_008ca348;   /* position before */
    void **cursor;
    char *model, *other, *omodel;
    float *frame;
    float c0[3];      /* [esp+0x18] self's model centre, rotated by self's frame */
    float A[3];       /* [esp+0x44] self's centre in world space */
    float B[3];       /* [esp+0x50] other's centre in world space */
    float r0;         /* [esp+0x04] self's radius */
    int i;            /* [esp+0x5c] */

    model = CTO_MODEL(self);
    frame = Actor_GetFrame(self);
    Vec3_Copy(c0, (float *)(model + 0x78), frame);
    A[0] = cto_st((ld_t)c0[0] + CTO_F(self, 0xc));
    i = 0;
    A[1] = cto_st((ld_t)CTO_F(self, 0x10) + c0[1]);
    A[2] = cto_st((ld_t)CTO_F(self, 0x14) + c0[2]);
    r0 = cto_st((ld_t)CTO_F(model, 0x5c) * CTO_F(CTO_P(self, 0xa4), 0x3f4));
    if (g_nDrawableActorCount <= 0)
        return 1;
    cursor = (void **)&g_pDrawableActors;
    do {
        char *oa4;
        ld_t dx, dy, dz, sum, dist, r1, rsum;
        float dxf, dyf, dzf, distf, r1f;

        other = (char *)*cursor;
        if (other == self || (oa4 = CTO_P(other, 0xa4)) == 0 || CTO_I(oa4, 0x3f0) == 0)
            goto next;
        omodel = CTO_MODEL(other);
        frame = Actor_GetFrame(other);
        Matrix34_TransformPoint(B, (float *)(omodel + 0x78), frame);
        dx = (ld_t)A[0] - B[0];
        dy = (ld_t)A[1] - B[1];
        dz = (ld_t)A[2] - B[2];
        dxf = cto_st(dx);
        dyf = cto_st(dy);
        dzf = cto_st(dz);
        {
            float t0;          /* [esp+0x00] scratch: dx, then dz, as floats */
            ld_t sx, sz;
            t0 = cto_st(dx);
            sx = dx * (ld_t)t0;
            t0 = cto_st(dz);
            sz = dz * (ld_t)t0;
            sum = (sx + dy * dy) + sz;
        }
        oa4 = CTO_P(other, 0xa4);
        dist = cto_fsqrt(sum);
        r1 = (ld_t)CTO_F(omodel, 0x5c) * CTO_F(oa4, 0x3f4);
        r1f = cto_st(r1);
        rsum = r1 + r0;
        distf = cto_st(dist);
        /* FCOMPP, TEST AH,1: go on when dist < rsum or unordered */
        if (dist >= rsum)
            goto next;

        if (CTO_I(oa4, 0x3f0) == 2) {
            float n[3];        /* [esp+0x8c] */
            float np[3];       /* [esp+0x98] */
            float t, k;
            int walking;

            CTO_I(CTO_P(self, 0xa4), 0x3f8) = 1;
            CTO_I(CTO_P(other, 0xa4), 0x3f8) = 1;
            n[0] = cto_st((ld_t)A[0] - B[0]);
            cto_copy3(g348, self + 0xc);
            n[1] = cto_st((ld_t)A[1] - B[1]);
            n[2] = cto_st((ld_t)A[2] - B[2]);
            (void)Vec3_Normalize(n);
            t = cto_st(((ld_t)distf - r1f) / r0);
            walking = (*(byte *)(self + 8) & 1) != 0;
            k = cto_st((1.0L - t) * r0);
            np[0] = cto_st(((ld_t)n[0] * k + A[0]) - c0[0]);
            np[1] = cto_st(((ld_t)n[1] * k + A[1]) - c0[1]);
            np[2] = cto_st(((ld_t)n[2] * k + A[2]) - c0[2]);
            Actor_SetPositionClamped((int)self, np);
            cto_copy3(g338, self + 0xc);
            cto_copy3(g320, self + 0xc);
            if (walking)
                CTO_I(self, 8) = CTO_I(self, 8) | 1;
        } else {
            float D[3];        /* [esp+0x28] */
            float P[3];        /* [esp+0x0c] */
            float Q[3];        /* [esp+0x68] */
            float out[3];      /* [esp+0x34] */
            float box[6];      /* [esp+0x74] xmin ymin zmin xmax ymax zmax */
            float s;
            int walking, slid;

            D[0] = dxf;
            D[1] = dyf;
            D[2] = dzf;
            frame = Actor_GetFrame(other);
            Vec3_TransformTo(P, D, frame);
            P[0] = cto_st((ld_t)P[0] + CTO_F(omodel, 0x78));
            P[1] = cto_st((ld_t)P[1] + CTO_F(omodel, 0x7c));
            P[2] = cto_st((ld_t)P[2] + CTO_F(omodel, 0x80));
            oa4 = CTO_P(other, 0xa4);
            s = CTO_F(oa4, 0x3f4);
            box[0] = cto_st((ld_t)CTO_F(omodel, 0x60) * s - r0);
            box[1] = cto_st((ld_t)CTO_F(omodel, 0x64) * s - r0);
            box[2] = cto_st((ld_t)CTO_F(omodel, 0x68) * s - r0);
            box[3] = cto_st((ld_t)CTO_F(omodel, 0x6c) * s + r0);
            box[4] = cto_st((ld_t)CTO_F(omodel, 0x70) * s + r0);
            box[5] = cto_st((ld_t)CTO_F(omodel, 0x74) * s + r0);
            /* FCOMP + TEST AH,0x41 / JNZ: go on only when strictly greater (ordered);
               FCOMP + TEST AH,1 / JZ: go on when less or unordered */
            if (!(P[2] > box[2])) goto next;
            if (!(P[1] > box[1])) goto next;
            if (P[1] >= box[4]) goto next;
            if (!(P[0] > box[0])) goto next;
            if (P[0] >= box[3]) goto next;
            if (P[2] >= box[5]) goto next;

            walking = 0;
            CTO_I(CTO_P(self, 0xa4), 0x3f8) = 1;
            cto_copy3(g348, self + 0xc);
            {
                ld_t x = (ld_t)c0[0] + CTO_F(self, 0x18);
                D[1] = cto_st((ld_t)CTO_F(self, 0x1c) + c0[1]);
                D[2] = cto_st((ld_t)CTO_F(self, 0x20) + c0[2]);
                D[0] = cto_st(x - B[0]);
                D[1] = cto_st((ld_t)D[1] - B[1]);
                D[2] = cto_st((ld_t)D[2] - B[2]);
            }
            frame = Actor_GetFrame(other);
            Vec3_TransformTo(Q, D, frame);
            Q[0] = cto_st((ld_t)Q[0] + CTO_F(omodel, 0x78));
            Q[1] = cto_st((ld_t)Q[1] + CTO_F(omodel, 0x7c));
            Q[2] = cto_st((ld_t)Q[2] + CTO_F(omodel, 0x80));
            slid = Collision_BoxSlide(P, Q, box[0], box[1], box[2], box[3], box[4], box[5], out);
            if (slid == 0) {
                frame = Actor_GetFrame(other);
                Collision_PushOutOfBox(P, box[0], box[1], box[2], box[3], box[4], box[5], frame,
                                       (float *)(other + 0xc));
                cto_copy3(out, P);
            }
            frame = Actor_GetFrame(other);
            Vec3_Rotate3x3(out, frame);
            out[0] = cto_st((ld_t)out[0] - c0[0]);
            out[1] = cto_st((ld_t)out[1] - c0[1]);
            cto_copy3(self + 0x18, self + 0xc);
            out[2] = cto_st((ld_t)out[2] - c0[2]);
            frame = Actor_GetFrame(other);
            Vec3_Rotate3x3(g320, frame);
            g320[0] = cto_st((ld_t)g320[0] - c0[0]);
            g320[1] = cto_st((ld_t)g320[1] - c0[1]);
            g320[2] = cto_st((ld_t)g320[2] - c0[2]);
            walking = (*(byte *)(self + 8) & 1) ? 1 : walking;
            Actor_SetPositionClamped((int)self, out);
            cto_copy3(g338, self + 0xc);
            if (walking) {
                char *a4 = CTO_P(self, 0xa4);
                float goal[3];         /* [esp+0xa4] */
                CTO_I(self, 8) = CTO_I(self, 8) | 1;
                cto_copy3(goal, a4 + (CTO_I(a4, 0x44) + 5) * 12);
                Walker_ReplanPath((int)self, (int)goal, (undefined4 *)(a4 + 0x38), (undefined4)other);
            }
        }
        Sector_IntersectSegment((int)self, (int)other, g348, g320, g338);
    next:
        i++;
        cursor++;
    } while (i < g_nDrawableActorCount);
    return 1;
}
#endif /* GRIM_EXE */
