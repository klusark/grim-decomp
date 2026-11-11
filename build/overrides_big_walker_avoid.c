/* Walker_AvoidActorPath (0x004917e0), written by hand from the original machine code (docs/notes/big_walker_avoid.md).
 *
 * Checked against the original instructions with a differential test, build/difftest/big_walker_avoid/ (the original and
 * this C run on the same inputs; every callee is a recorder that also dumps the whole stack frame at each call).
 *
 * The locals live in one byte array laid out exactly like the original frame (offsets below are the original's ESP
 * offsets after the prologue, 0x10 .. 0x113): the four detour corners are followed by their four "reachable" flags, which
 * Collision_PickDetour reads through the corner pointer (+0x30), and when both side corners are unreachable the
 * original indexes the corner array with the bits of the radius float (a stale slot; see below).  Several slots are
 * reused for different values, as in the original.
 *
 * x87: the temporaries the original keeps on the FPU stack are long double here; the ones it stores to the frame are
 * rounded to float there too.  Point copies are dword moves in the original, so they are copied as integers (a
 * signalling NaN coordinate is not quieted).  Verified at -O0 (the build's setting for overrides_*.c); at -O2 gcc keeps
 * some float frame stores unrounded and the corner choice differs in about 1 case in 1000 of the test. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

typedef struct { uint32_t d[6]; } WalkerBox6;   /* the six box floats the callees take by value (rep movsd) */

typedef void (*wav_pushout_t)(float *pt, WalkerBox6 box, float *frame, float *pos);
typedef int (*wav_seghit_t)(float *a, float *b, float *rel, WalkerBox6 box, float *frame);
typedef int (*wav_ptinbox_t)(float *a, float *b, float *rel, WalkerBox6 box, float *frame, float *offset);
typedef void (*wav_corners_t)(void *cos, float radius, float *frame, uint32_t z, float *corners);
typedef int (*wav_plan_t)(float *from, float *to, int flag);
typedef int (*wav_pick_t)(float *from, float *target, float *corners);
typedef int (*wav_getpath_t)(void *outPath);

/* the frame slots are read and written as int, uint32_t and float (link.py compiles without -fno-strict-aliasing) */
typedef int __attribute__((__may_alias__)) wav_int;
typedef uint32_t __attribute__((__may_alias__)) wav_u32;
typedef float __attribute__((__may_alias__)) wav_float;
#define WAV_FR(o) ((unsigned char *)fr + ((o) - 0x10))
#define WAV_I(o)  (*(wav_int *)WAV_FR(o))
#define WAV_U(o)  (*(wav_u32 *)WAV_FR(o))
#define WAV_F(o)  (*(wav_float *)WAV_FR(o))
#define WAV_P(o)  ((float *)WAV_FR(o))
#define WAV_BOX   (*(WalkerBox6 *)WAV_FR(0x98))
/* 32-bit address arithmetic of the original (lea): no C pointer rules, wraps */
#define WAV_AT(p, byteoff) ((float *)((uint32_t)(uintptr_t)(p) + (uint32_t)(byteoff)))
#define WAV_CORNER(k) WAV_AT(WAV_FR(0xc8), (uint32_t)(k) * 12u)

static void wav_copy3(float *dst, const float *src)
{
    ((wav_u32 *)dst)[0] = ((const wav_u32 *)src)[0];
    ((wav_u32 *)dst)[1] = ((const wav_u32 *)src)[1];
    ((wav_u32 *)dst)[2] = ((const wav_u32 *)src)[2];
}

/* Frame slots (original ESP offsets):
 *  0x10 radius of `self` (float) / current corner index    0x14 number of points written to out
 *  0x18 out cursor / path pointer of GetPath        0x1c count-1 / step (+1 or -1) / loop counter
 *  0x20 last input point / corner counter / end of out      0x24 segment index / "corner a reachable"
 *  0x28 path length / path pointer                          0x2c offset vector (3)
 *  0x38 corner b / path length - 1                          0x3c detour corner picked
 *  0x40 path length                                         0x44 target point (3)
 *  0x50 .. 0x64 distance temporaries                        0x68, 0x74, 0x80, 0xb0 segment end points (3 each)
 *  0x8c other actor's position relative to its frame (3)    0x98 box (6)
 *  0xbc snap point (3)   0xc8 corners (4 x 3)   0xf8 corner flags (4)   0x108 position of `self` (3) */

/* OVERRIDES: Walker_AvoidActorPath */
uint Walker_AvoidActorPath(void *self, void *other, undefined4 *pts, uint count, float *out)
{
    uint32_t fr[0x104 / 4];
    unsigned char *c1, *c2, *s2;
    float *frame, *lastout, *path, *dst, *cp;
    int *flagp;
    int i, n, k, idx, a, rb, cur, total;
    float scale;

    WAV_I(0x14) = 0;
    if (other == 0) {
        if ((int)count < 1)
            return 0;
        WAV_I(0x14) = count;
        k = count;
        dst = out;
        path = (float *)pts;
        do {
            wav_copy3(dst, path);
            dst += 3;
            path += 3;
        } while (--k != 0);
        return WAV_I(0x14);
    }

    c1 = *(unsigned char **)(*(unsigned char **)(*(unsigned char **)((unsigned char *)self + 0xa0) + 4) + 4);
    WAV_F(0x10) = (long double)*(float *)(*(unsigned char **)((unsigned char *)self + 0xa4) + 0x3f4) * *(float *)(c1 + 0x5c);
    rdMatrix_TransformVector34(WAV_P(0x108), (float *)(c1 + 0x78), sputActor_GetOrientMatrix(self));
    c2 = *(unsigned char **)(*(unsigned char **)(*(unsigned char **)((unsigned char *)other + 0xa0) + 4) + 4);
    rdMatrix_TransformPoint34(WAV_P(0x8c), (float *)(c2 + 0x78), sputActor_GetOrientMatrix(other));
    rdMatrix_TransformVector34(WAV_P(0x2c), (float *)(c2 + 0x78), sputActor_GetOrientMatrix(other));
    s2 = *(unsigned char **)((unsigned char *)other + 0xa4);
    WAV_U(0x20) = (uint32_t)(uintptr_t)pts + count * 12u - 12u;
    scale = *(float *)(s2 + 0x3f4);
    WAV_F(0x98) = (long double)*(float *)(c2 + 0x60) * scale - WAV_F(0x10);
    WAV_F(0x9c) = (long double)*(float *)(c2 + 0x64) * scale - WAV_F(0x10);
    WAV_F(0xa0) = (long double)*(float *)(c2 + 0x68) * scale - WAV_F(0x10);
    WAV_F(0xa4) = (long double)*(float *)(c2 + 0x6c) * scale + WAV_F(0x10);
    WAV_F(0xa8) = (long double)*(float *)(c2 + 0x70) * scale + WAV_F(0x10);
    WAV_F(0xac) = (long double)*(float *)(c2 + 0x74) * scale + WAV_F(0x10);

    /* both ends of the path are pushed out of the other actor's box */
    frame = sputActor_GetOrientMatrix(other);
    ((wav_pushout_t)GetOuttaTheBox)((float *)(uintptr_t)WAV_U(0x20), WAV_BOX, frame,
                                            (float *)((unsigned char *)other + 0xc));
    frame = sputActor_GetOrientMatrix(other);
    ((wav_pushout_t)GetOuttaTheBox)((float *)pts, WAV_BOX, frame, (float *)((unsigned char *)other + 0xc));
    wav_copy3(WAV_P(0x44), (float *)(uintptr_t)WAV_U(0x20));
    if (WalkPlane_PlaneAt(WAV_P(0x44), 0xffffffff) == 0)
        return 0;

    /* copy the segments to out until one passes through the other actor's box */
    i = 0;
    WAV_I(0x24) = 0;
    WAV_U(0x1c) = count - 1u;
    if (WAV_I(0x1c) > 0) {
        float *pt = (float *)pts;
        float *cursor = out;
        for (;;) {
            WAV_F(0xb0) = (long double)WAV_F(0x2c) + pt[0];
            WAV_U(0x18) = (uint32_t)(uintptr_t)cursor + 12u;
            WAV_U(0x14) = WAV_U(0x14) + 1u;
            WAV_F(0xb4) = (long double)pt[1] + WAV_F(0x30);
            WAV_F(0xb8) = (long double)WAV_F(0x34) + pt[2];
            WAV_F(0x74) = (long double)pt[3] + WAV_F(0x2c);
            WAV_F(0x78) = (long double)pt[4] + WAV_F(0x30);
            WAV_F(0x7c) = (long double)pt[5] + WAV_F(0x34);
            wav_copy3(cursor, pt);
            frame = sputActor_GetOrientMatrix(other);
            if (((wav_seghit_t)TestCollision)(WAV_P(0xb0), WAV_P(0x74), WAV_P(0x8c), WAV_BOX, frame) != 0)
                goto hit;
            WAV_I(0x24) = WAV_I(0x24) + 1;
            pt += 3;
            if (WAV_I(0x24) >= WAV_I(0x1c))
                break;
            cursor = (float *)(uintptr_t)WAV_U(0x18);
        }
        i = WAV_I(0x24);
    }
    wav_copy3(WAV_AT(out, (uint32_t)WAV_I(0x14) * 12u), WAV_AT(pts, (uint32_t)i * 12u));
    return WAV_U(0x14) + 1u;

hit:
    /* the four corners of the other actor's box (grown by this actor's radius + 0.02) */
    frame = sputActor_GetOrientMatrix(other);
    rdMatrix_TransformPoint34(WAV_P(0xbc), (float *)&DAT_008ca320, frame);
    WalkPlane_SnapTo(WalkPlane_PlaneClosest(WAV_P(0xbc), 0xffffffff), WAV_P(0xbc));
    {
        uint32_t z = WAV_U(0xc4);
        frame = sputActor_GetOrientMatrix(other);
        ((wav_corners_t)FindObjectCorners)(c2, (float)((long double)WAV_F(0x10) - (long double)-0.02f), frame, z,
                                              WAV_P(0xc8));
    }
    /* a corner is usable when the segment start reaches it outside the box and the planner finds a path to it */
    flagp = (int *)WAV_FR(0xf8);
    cp = WAV_P(0xc8);
    WAV_I(0x20) = 4;
    do {
        *flagp = 0;
        WAV_F(0x74) = (long double)WAV_F(0x2c) + cp[0];
        WAV_F(0x78) = (long double)cp[1] + WAV_F(0x30);
        WAV_F(0x7c) = (long double)WAV_F(0x34) + cp[2];
        frame = sputActor_GetOrientMatrix(other);
        if (((wav_seghit_t)TestCollision)(WAV_P(0xb0), WAV_P(0x74), WAV_P(0x8c), WAV_BOX, frame) == 0 &&
            ((wav_plan_t)BuildPath)(WAV_AT(pts, (uint32_t)WAV_I(0x24) * 12u), cp, 0) != 0)
            *flagp = 1;
        cp += 3;
        flagp++;
        WAV_I(0x20) = WAV_I(0x20) - 1;
    } while (WAV_I(0x20) != 0);

    idx = ((wav_pick_t)Collision_PickDetour)(WAV_P(0xb0), WAV_P(0x44), WAV_P(0xc8));
    WAV_I(0x3c) = idx;
    if (idx == -1)
        return WAV_I(0x14);
    ((wav_plan_t)BuildPath)(WAV_AT(pts, (uint32_t)WAV_I(0x24) * 12u), WAV_CORNER(idx), 0);
    n = ((wav_getpath_t)GetPath)(WAV_FR(0x18));
    total = WAV_I(0x14);
    if (n > 0) {
        dst = WAV_AT(out, (uint32_t)total * 12u);
        total = (int)((uint32_t)total + (uint32_t)n);
        WAV_I(0x14) = total;
        path = (float *)(uintptr_t)WAV_U(0x18);
        do {
            wav_copy3(dst, path);
            dst += 3;
            path += 3;
        } while (--n != 0);
    }
    *(int *)WAV_AT(WAV_FR(0xf8), (uint32_t)WAV_I(0x3c) * 4u) = 0;
    dst = WAV_AT(out, (uint32_t)total * 12u);
    WAV_U(0x20) = (uint32_t)(uintptr_t)dst;
    lastout = dst - 3;
    frame = sputActor_GetOrientMatrix(other);
    if (((wav_ptinbox_t)Collision_PointInBox)(lastout, WAV_P(0x44), WAV_P(0x8c), WAV_BOX, frame, WAV_P(0x2c)) != 0) {
        /* the target is reachable from the corner: append that path */
        n = ((wav_getpath_t)GetPath)(WAV_FR(0x18));
        if (n < 1)
            return WAV_I(0x14);
        WAV_U(0x14) = WAV_U(0x14) + (uint32_t)n;
        path = (float *)(uintptr_t)WAV_U(0x18);
        do {
            wav_copy3(dst, path);
            dst += 3;
            path += 3;
        } while (--n != 0);
        return WAV_I(0x14);
    }

    /* walk around the box: the neighbour corners a = idx - 1 and b = idx + 1 (C remainders) */
    a = (idx + 3) % 4;
    WAV_I(0x38) = (idx + 5) % 4;
    WAV_I(0x24) = ((wav_plan_t)BuildPath)(lastout, WAV_CORNER(a), 0);
    rb = ((wav_plan_t)BuildPath)(lastout, WAV_CORNER(WAV_I(0x38)), 0);
    if (rb != 0) {
        if (WAV_I(0x24) == 0)
            goto take_b;
        {
            /* both reachable: the shorter way (last point - corner - target), squared lengths; x87 order kept */
            float *L = lastout, *T = WAV_P(0x44), *Ca = WAV_CORNER(a), *Cb = WAV_CORNER(WAV_I(0x38));
            long double d1x, e1x, d2x, e2x, e2z, sa, sb;
            d1x = (long double)L[0] - Ca[0];
            WAV_F(0x10) = d1x;
            WAV_F(0x58) = (long double)L[1] - Ca[1];
            WAV_F(0x5c) = (long double)L[2] - Ca[2];
            e1x = (long double)Ca[0] - T[0];
            WAV_F(0x54) = e1x;
            WAV_F(0x50) = (long double)Ca[1] - T[1];
            WAV_F(0x64) = (long double)Ca[2] - T[2];
            d2x = (long double)L[0] - Cb[0];
            WAV_F(0x60) = d2x;
            WAV_F(0x40) = (long double)L[1] - Cb[1];
            WAV_F(0x1c) = (long double)L[2] - Cb[2];
            e2x = (long double)Cb[0] - T[0];
            WAV_F(0x28) = e2x;
            WAV_F(0x18) = (long double)Cb[1] - T[1];
            e2z = (long double)Cb[2] - T[2];
            sa = ((d1x * WAV_F(0x10) + (long double)WAV_F(0x58) * WAV_F(0x58)) + (long double)WAV_F(0x5c) * WAV_F(0x5c)) +
                 ((e1x * WAV_F(0x54) + (long double)WAV_F(0x50) * WAV_F(0x50)) + (long double)WAV_F(0x64) * WAV_F(0x64));
            sb = ((d2x * WAV_F(0x60) + (long double)WAV_F(0x40) * WAV_F(0x40)) + (long double)WAV_F(0x1c) * WAV_F(0x1c)) +
                 ((e2x * WAV_F(0x28) + (long double)WAV_F(0x18) * WAV_F(0x18)) + e2z * e2z);
            if (!(sb > sa))          /* FCOMPP + TEST AH,0x41: b also when unordered */
                WAV_I(0x24) = 0;
            else
                rb = 0;
        }
    }
    if (WAV_I(0x24) != 0) {
        WAV_I(0x1c) = -1;
        WAV_I(0x10) = a;
        cur = a;
    } else {
        /* neither reachable: the original takes the stale slot 0x10 (the radius float's bits) as the corner index and
         * slot 0x1c (count - 1) as the step */
        cur = WAV_I(0x10);
    }
take_b:
    if (rb != 0) {
        WAV_I(0x1c) = 1;
        WAV_I(0x10) = WAV_I(0x38);
        cur = WAV_I(0x38);
    }
    if (cur == WAV_I(0x3c))
        return WAV_I(0x14);

    lastout = (float *)(uintptr_t)(WAV_U(0x20) - 12u);
    for (;;) {
        ((wav_plan_t)BuildPath)(lastout, WAV_CORNER(cur), 0);
        n = ((wav_getpath_t)GetPath)(WAV_FR(0x18));
        WAV_I(0x28) = n;
        WAV_I(0x38) = n - 1;
        if (n - 1 > 0) {
            int j = 0;
            uint32_t o = 0;
            do {
                path = (float *)(uintptr_t)(WAV_U(0x18) + o);
                WAV_F(0x68) = (long double)WAV_F(0x2c) + path[0];
                WAV_F(0x6c) = (long double)path[1] + WAV_F(0x30);
                WAV_F(0x70) = (long double)path[2] + WAV_F(0x34);
                WAV_F(0x80) = (long double)path[3] + WAV_F(0x2c);
                WAV_F(0x84) = (long double)path[4] + WAV_F(0x30);
                WAV_F(0x88) = (long double)path[5] + WAV_F(0x34);
                frame = sputActor_GetOrientMatrix(other);
                if (((wav_seghit_t)TestCollision)(WAV_P(0x68), WAV_P(0x80), WAV_P(0x8c), WAV_BOX, frame) != 0)
                    return 0;
                j++;
                o += 12;
            } while (j < WAV_I(0x38));
            n = WAV_I(0x28);
        }
        total = WAV_I(0x14);
        if (n > 0) {
            dst = (float *)(uintptr_t)WAV_U(0x20);
            total = (int)((uint32_t)total + (uint32_t)n);
            WAV_I(0x14) = total;
            path = (float *)(uintptr_t)WAV_U(0x18);
            do {
                wav_copy3(dst, path);
                dst += 3;
                path += 3;
            } while (--n != 0);
        }
        dst = WAV_AT(out, (uint32_t)total * 12u);
        WAV_U(0x20) = (uint32_t)(uintptr_t)dst;
        lastout = dst - 3;
        frame = sputActor_GetOrientMatrix(other);
        if (((wav_ptinbox_t)Collision_PointInBox)(lastout, WAV_P(0x44), WAV_P(0x8c), WAV_BOX, frame, WAV_P(0x2c)) != 0)
            break;
        cur = (int)(WAV_U(0x1c) + WAV_U(0x10) + 4u) % 4;     /* lea: wraps */
        WAV_I(0x10) = cur;
        if (cur == WAV_I(0x3c))
            return WAV_I(0x14);
    }

    /* the target is reachable from this corner: check and append the final path */
    n = ((wav_getpath_t)GetPath)(WAV_FR(0x28));
    WAV_I(0x40) = n;
    WAV_I(0x1c) = 0;
    WAV_I(0x38) = n - 1;
    if (n - 1 > 0) {
        uint32_t o = 0;
        do {
            path = (float *)(uintptr_t)(WAV_U(0x28) + o);
            WAV_F(0x80) = (long double)WAV_F(0x2c) + path[0];
            WAV_F(0x84) = (long double)path[1] + WAV_F(0x30);
            WAV_F(0x88) = (long double)path[2] + WAV_F(0x34);
            WAV_F(0x68) = (long double)path[3] + WAV_F(0x2c);
            WAV_F(0x6c) = (long double)path[4] + WAV_F(0x30);
            WAV_F(0x70) = (long double)path[5] + WAV_F(0x34);
            frame = sputActor_GetOrientMatrix(other);
            if (((wav_seghit_t)TestCollision)(WAV_P(0x80), WAV_P(0x68), WAV_P(0x8c), WAV_BOX, frame) != 0)
                return 0;
            WAV_I(0x1c) = WAV_I(0x1c) + 1;
            o += 12;
        } while (WAV_I(0x1c) < WAV_I(0x38));
        n = WAV_I(0x40);
    }
    if (n > 0) {
        dst = WAV_AT(out, (uint32_t)total * 12u);
        path = (float *)(uintptr_t)WAV_U(0x28);
        total = (int)((uint32_t)total + (uint32_t)n);
        do {
            wav_copy3(dst, path);
            dst += 3;
            path += 3;
        } while (--n != 0);
    }
    return total;
}
#endif
