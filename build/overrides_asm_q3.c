/* Readable C for assembled GRIMFANDANGO.EXE functions, agent asm_q3 (see docs/notes/asm_q3.md).
 *
 * Every function here was written by hand from the original 1.01 machine code (src/GRIMFANDANGO.EXE/asm_funcs.s as of
 * 2df265d) and checked against it with a differential test in build/difftest/asm_q3/ (original bytes and this C on the
 * same inputs, under the x87 precision controls 24, 53 and 64 bits; memory, call log, control word and x87 stack top
 * compared).
 *
 * x87 conventions used below (as in build/overrides_asm_p2.c):
 *   - `long double` holds a value that the original keeps on the x87 stack (extended precision, rounded only by the
 *     precision control); q3_f() is a store of such a value to a float slot (FSTP m32), through a volatile so the
 *     rounding happens at that point at every optimisation level.
 *   - A float that the original copies with MOV (no FLD/FSTP) is copied as a dword here (Q3U), so a signalling NaN
 *     keeps its bits.
 *   - The compares say which way an unordered (NaN) compare goes: FCOMP + `test ah,1` is "less or unordered",
 *     `test ah,0x41` "less, equal or unordered", `test ah,0x40` "equal or unordered".
 *
 * The puppet track records (rdPuppet_*) are 0x134 bytes each, six per puppet, starting at puppet+8:
 *   +0x00 flags, +0x08 / +0x0c int priorities (the second one for the joints whose mask matches the animation's
 *   mask at anim+0x2c), +0x18 float weight, +0x20 uint[0x40] current key per animation node, +0x120 float time,
 *   +0x124 float previous time, +0x128 animation (+0x24 flags, +0x2c joint mask, +0x34 uint frame count,
 *   +0x38 node count, +0x3c nodes of 0x2c bytes, +0x40 marker count, +0x44 float marker times, +0x64 marker values),
 *   +0x12c marker callback. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#define rdModel3_LoadText rdModel3_LoadText__ghidra
#include "functions.h"
#undef rdModel3_LoadText

#define Q3U(p, off) (*(uint *)((char *)(p) + (off)))
#define Q3I(p, off) (*(int *)((char *)(p) + (off)))
#define Q3P(p, off) (*(char **)((char *)(p) + (off)))
#define Q3F(p, off) (*(float *)((char *)(p) + (off)))

static inline float q3_f(long double x)
{
    volatile float f = (float)x;
    return f;
}

/* FCOMP + `test ah,0x40` not taken: ordered and not equal */
#define Q3_NE_ORD(a, b) __builtin_islessgreater((long double)(a), (long double)(b))

/* uint frame / marker count as FILD QWORD of the zero-extended dword */
#define Q3_FILD_U(u) ((long double)(long long)(uint)(u))

/* fldcw [DAT_00900526]; fld x; frndint; fstp float; fldcw [DAT_00900524] (the rounding mode Services_SetCurrent
 * stored in DAT_00900526, round down in the game) */
static inline float q3_frndint_cw(float x)
{
    float r;
    __asm__ volatile("fldcw %2\n\tflds %1\n\tfrndint\n\tfstps %0\n\tfldcw %3"
                     : "=m"(r) : "m"(x), "m"(DAT_00900526), "m"(DAT_00900524));
    return r;
}

typedef void (*q3_marker_fn)(uint, int, uint);

/* ==== rdPuppet_AdvanceTrack (0x004507e0) ====
 * Advances the time of one track by dt (nothing when the track has no animation, or dt is 0 or NaN: FCOMP with 0.0,
 * `test ah,0x40`).  time = float(dt + previous time).  When time >= the frame count (FILD of the uint count; a NaN
 * time does not wrap): flag 0x20 holds the last frame and stops the track at the end, 0x40 holds it and sets 0x10,
 * 0x80 holds it, fades out over 0.25 s and sets 0x10; otherwise the time wraps: loops = float(time / count) rounded
 * with the control word DAT_00900526 (FRNDINT, stored as a float), time = float(time - count * loops) (the product
 * extended), and the current keys at +0x20 are cleared for min(model node count, 0x40) nodes.
 * Then the markers whose times were passed call the callback (model+0x48 value, track, marker value):
 *   loops 0 (or NaN): markers in order while time >= marker (stops at the first later one), each called when
 *     marker > previous time or previous time is 0 (or NaN);
 *   loops > 1: every marker;
 *   otherwise (one wrap): markers with marker > previous time or !(marker > time).
 * The animation pointer and the marker count are read again after each marker (the callback may change them).
 * Finally the track is stopped (flag 0x20 case) or previous time = time (dword copy).
 * The original returns garbage in EAX (void in functions.h, no caller reads it). */
/* OVERRIDES: rdPuppet_AdvanceTrack */
void __cdecl rdPuppet_AdvanceTrack(void *puppet, int track, float dt)
{
    char *rec = (char *)puppet + track * 0x134 + 8;
    char *anim = Q3P(rec, 0x128);
    float loops = 0.0f;
    int stop = 0;
    float t;
    long double cnt;
    uint i;

    if (anim == 0)
        return;
    if (!Q3_NE_ORD(dt, 0.0f))
        return;
    t = q3_f((long double)dt + (long double)Q3F(rec, 0x124));
    Q3F(rec, 0x120) = t;
    cnt = Q3_FILD_U(Q3U(anim, 0x34));
    if ((long double)t >= cnt) {
        uint fl = Q3U(rec, 0);
        if (fl & 0x20) {
            Q3F(rec, 0x120) = q3_f(cnt);
            stop = 1;
        } else if (fl & 0x40) {
            Q3F(rec, 0x120) = q3_f(cnt);
            Q3U(rec, 0) = fl | 0x10;
        } else if (fl & 0x80) {
            Q3F(rec, 0x120) = q3_f(cnt);
            rdPuppet_FadeOutTrack(puppet, track, 0.25f);
            Q3U(rec, 0) |= 0x10;
        } else {
            uint n;
            float q = q3_f((long double)t / cnt);
            loops = q3_frndint_cw(q);
            cnt = Q3_FILD_U(Q3U(Q3P(rec, 0x128), 0x34));
            Q3F(rec, 0x120) = q3_f((long double)Q3F(rec, 0x120) - cnt * (long double)loops);
            n = Q3U(Q3P(Q3P(puppet, 4), 4), 0x54);
            if (n >= 0x40)
                n = 0x40;
            for (i = 0; i < n; i++)
                Q3U(rec, 0x20 + i * 4) = 0;
        }
    }

    if (Q3P(rec, 0x12c) != 0 && Q3U(Q3P(rec, 0x128), 0x40) != 0) {
        anim = Q3P(rec, 0x128);
        i = 0;
        if (!Q3_NE_ORD(loops, 0.0f)) {
            do {
                float mt = Q3F(anim, 0x44 + i * 4);
                if ((long double)mt > (long double)Q3F(rec, 0x120))
                    break;
                if ((long double)mt > (long double)Q3F(rec, 0x124) || !Q3_NE_ORD(Q3F(rec, 0x124), 0.0f))
                    ((q3_marker_fn)Q3P(rec, 0x12c))(Q3U(Q3P(puppet, 4), 0x48), track, Q3U(anim, 0x64 + i * 4));
                anim = Q3P(rec, 0x128);
                i++;
            } while (i < Q3U(anim, 0x40));
        } else if ((long double)loops > 1.0L) {
            do {
                ((q3_marker_fn)Q3P(rec, 0x12c))(Q3U(Q3P(puppet, 4), 0x48), track, Q3U(anim, 0x64 + i * 4));
                anim = Q3P(rec, 0x128);
                i++;
            } while (i < Q3U(anim, 0x40));
        } else {
            do {
                float mt = Q3F(anim, 0x44 + i * 4);
                if ((long double)mt > (long double)Q3F(rec, 0x124) || !((long double)mt > (long double)Q3F(rec, 0x120)))
                    ((q3_marker_fn)Q3P(rec, 0x12c))(Q3U(Q3P(puppet, 4), 0x48), track, Q3U(anim, 0x64 + i * 4));
                anim = Q3P(rec, 0x128);
                i++;
            } while (i < Q3U(anim, 0x40));
        }
    }

    if (stop) {
        rdPuppet_StopTrack(puppet, track);
        return;
    }
    Q3U(rec, 0x124) = Q3U(rec, 0x120);
}

/* ==== rdPuppet_UpdateFrame (0x00450ba0) ====
 * Poses the joints of a model instance (thing) from its puppet and builds the node matrices.  Nothing when thing+0x18
 * is set.  Without a puppet, or with the puppet's first dword set, each joint's matrix (thing+0x20, 0x30 bytes per
 * node) is copied from the model's rest matrix (joint+0x88, joints of 0xb8 bytes at model+0x58).  Otherwise:
 *  1. for each track with flags, each animation node advances its current key (track+0x20+4*node, only for node
 *     < 0x40) while time >= the next key's time (keys of 0x38 bytes; a NaN time stops), from the key at the slot the
 *     node names (node+0x20, 0 when >= 0x40);
 *  2. for each joint, every track that plays (flag 0x2) an animation node for it (joint+0x44 < node count, node keys
 *     non-zero) gives a position and rotation: the key's value, plus velocity * (time - key time) when key flag 1 / 2
 *     (dt extended, 0.0 when anim flag 0x100); minus the joint's rest position / rotation (joint+0x70 / +0x7c), the
 *     rotations through Math_NormalizeAngle180, scaled by the track weight when the weight is < 1 (or NaN).
 *     The two highest priorities are blended: equal priority adds (position, rotation, weight), a higher priority
 *     moves the best one to the second; a track below the best is only taken while the best weight is < 1 (or NaN).
 *     Then: best weight < 1 (or NaN) and second weight > 0: second scaled by 1/weight when its weight > 1, and best +=
 *     second * (1 - best weight) (product and 1-w extended); otherwise the best is scaled by 1/weight when > 1.
 *     Rotations through Math_NormalizeAngle180, rest position / rotation added back, Angles_ToMatrix, then
 *     Matrix_BuildTransform with the joint's scale (thing+0x24, 12 bytes per node) when one component is ordered
 *     non-zero.
 * Then rdThing_BuildNodeMatrix(thing, joints, frame) and thing+0x1c = UINT_004f5eb4.
 * x87: the rotation y / z of a key with velocity stay extended until the rest rotation is subtracted (the position and
 * the rotation x are stored as floats first), every other step is stored as a float as in the original. */
/* OVERRIDES: rdPuppet_UpdateFrame */
void __cdecl rdPuppet_UpdateFrame(void *model, float *frame)
{
    char *thing = (char *)model;
    char *mdl = Q3P(thing, 4);
    char *pup = Q3P(thing, 0x14);
    char *rec0;
    uint node;

    if (Q3I(thing, 0x18) != 0)
        return;

    if (pup == 0 || Q3I(pup, 0) != 0) {
        char *src = Q3P(mdl, 0x58) + 0x88;
        uint off = 0, k;
        for (node = 0; node < Q3U(mdl, 0x54); node++, src += 0xb8, off += 0x30)
            for (k = 0; k < 12; k++)
                Q3U(Q3P(thing, 0x20) + off, k * 4) = Q3U(src, k * 4);
        goto done;
    }

    rec0 = pup + 8;
    {
        char *rec = rec0;
        int t;
        for (t = 6; t != 0; t--, rec += 0x134) {
            char *anim, *ent;
            uint i;
            if (Q3I(rec, 0) == 0)
                continue;
            anim = Q3P(rec, 0x128);
            if (Q3U(anim, 0x38) == 0)
                continue;
            ent = Q3P(anim, 0x3c) + 0x24;
            i = 0;
            do {
                uint nk = Q3U(ent, 0);
                if (nk != 0) {
                    uint s = Q3U(ent, -4);
                    int cur = s < 0x40 ? Q3I(rec, 0x20 + s * 4) : 0;
                    int last = (int)nk - 1;
                    if (cur != last) {
                        char *keys = Q3P(ent, 4);
                        int k = cur + 1;
                        if ((long double)Q3F(rec, 0x120) >= (long double)Q3F(keys, k * 0x38)) {
                            char *p = keys + (cur + 2) * 0x38;
                            for (;;) {
                                if (k == last)
                                    break;
                                if (!((long double)Q3F(rec, 0x120) >= (long double)Q3F(p, 0)))
                                    break;
                                k++;
                                p += 0x38;
                            }
                            if (i < 0x40)
                                Q3I(rec, 0x20 + i * 4) = k;
                        }
                    }
                }
                i++;
                ent += 0x2c;
            } while (i < Q3U(anim, 0x38));
        }
    }

    if (Q3U(mdl, 0x54) != 0) {
        char *j = Q3P(mdl, 0x58) + 0x44;   /* joint + 0x44 */
        uint off12 = 0, off48 = 0;
        node = 0;
        do {
            /* best (0) and second (1) priority: position, rotation, weight, priority */
            float P0[3] = {0, 0, 0}, R0[3] = {0, 0, 0}, P1[3] = {0, 0, 0}, R1[3] = {0, 0, 0};
            float W0 = 0.0f, W1 = 0.0f, nz;
            int pri0 = 0, pri1 = 0;
            char *rec = rec0;
            int t, c;
            float *v;
            char *mat;

            for (t = 6; t != 0; t--, rec += 0x134) {
                char *anim = Q3P(rec, 0x128), *ent;
                float p[3], r[3], ra;
                long double dt, ry, rz;
                uint ti, kfl;
                char *kf;
                int pri;

                if (anim == 0)
                    continue;
                pri = (Q3U(j, 4) & Q3U(anim, 0x2c)) ? Q3I(rec, 0xc) : Q3I(rec, 8);
                if ((*(unsigned char *)rec & 2) == 0)
                    continue;
                ti = Q3U(j, 0);
                if (ti >= Q3U(anim, 0x38))
                    continue;
                ent = Q3P(anim, 0x3c) + ti * 0x2c;
                if (Q3I(ent, 0x24) == 0)
                    continue;
                if (pri < pri1)
                    continue;
                if (pri < pri0 && (long double)W0 >= 1.0L)
                    continue;
                if (Q3U(anim, 0x38) <= ti)
                    continue;
                kf = Q3P(ent, 0x28) + Q3I(rec, 0x20 + ti * 4) * 0x38;
                if (Q3U(anim, 0x24) & 0x100)
                    dt = 0.0f;
                else
                    dt = (long double)Q3F(rec, 0x120) - (long double)Q3F(kf, 0);
                kfl = Q3U(kf, 4);
                if (kfl & 1) {
                    for (c = 0; c < 3; c++)
                        p[c] = q3_f((long double)Q3F(kf, 0x20 + c * 4) * dt + (long double)Q3F(kf, 8 + c * 4));
                } else {
                    for (c = 0; c < 3; c++)
                        *(uint *)&p[c] = Q3U(kf, 8 + c * 4);
                }
                if (kfl & 2) {
                    r[0] = q3_f((long double)Q3F(kf, 0x2c) * dt + (long double)Q3F(kf, 0x14));
                    ry = (long double)Q3F(kf, 0x30) * dt + (long double)Q3F(kf, 0x18);
                    rz = (long double)Q3F(kf, 0x34) * dt + (long double)Q3F(kf, 0x1c);
                } else {
                    for (c = 0; c < 3; c++)
                        *(uint *)&r[c] = Q3U(kf, 0x14 + c * 4);
                    ry = r[1];
                    rz = r[2];
                }
                for (c = 0; c < 3; c++)
                    p[c] = q3_f((long double)p[c] - (long double)Q3F(j, 0x2c + c * 4));
                ra = q3_f((long double)r[0] - (long double)Q3F(j, 0x38));
                r[1] = q3_f(ry - (long double)Q3F(j, 0x3c));
                r[2] = q3_f(rz - (long double)Q3F(j, 0x40));
                r[0] = q3_f(Math_NormalizeAngle180(ra));
                r[1] = q3_f(Math_NormalizeAngle180(r[1]));
                r[2] = q3_f(Math_NormalizeAngle180(r[2]));
                if (!((long double)Q3F(rec, 0x18) >= 1.0L)) {
                    for (c = 0; c < 3; c++)
                        p[c] = q3_f((long double)Q3F(rec, 0x18) * (long double)p[c]);
                    for (c = 0; c < 3; c++)
                        r[c] = q3_f((long double)Q3F(rec, 0x18) * (long double)r[c]);
                }
                if (pri == pri0) {
                    for (c = 0; c < 3; c++) {
                        P0[c] = q3_f((long double)p[c] + (long double)P0[c]);
                        R0[c] = q3_f((long double)r[c] + (long double)R0[c]);
                    }
                    W0 = q3_f((long double)W0 + (long double)Q3F(rec, 0x18));
                } else if (pri > pri0) {
                    for (c = 0; c < 3; c++) {
                        *(uint *)&P1[c] = *(uint *)&P0[c];
                        *(uint *)&R1[c] = *(uint *)&R0[c];
                        *(uint *)&P0[c] = *(uint *)&p[c];
                        *(uint *)&R0[c] = *(uint *)&r[c];
                    }
                    *(uint *)&W1 = *(uint *)&W0;
                    pri1 = pri0;
                    pri0 = pri;
                    *(uint *)&W0 = Q3U(rec, 0x18);
                } else if (pri > pri1) {
                    for (c = 0; c < 3; c++) {
                        *(uint *)&P1[c] = *(uint *)&p[c];
                        *(uint *)&R1[c] = *(uint *)&r[c];
                    }
                    *(uint *)&W1 = Q3U(rec, 0x18);
                    pri1 = pri;
                } else {
                    for (c = 0; c < 3; c++) {
                        P1[c] = q3_f((long double)p[c] + (long double)P1[c]);
                        R1[c] = q3_f((long double)r[c] + (long double)R1[c]);
                    }
                    W1 = q3_f((long double)W1 + (long double)Q3F(rec, 0x18));
                }
            }

            if (!((long double)W0 >= 1.0L) && (long double)W1 > 0.0L) {
                long double k;
                if ((long double)W1 > 1.0L) {
                    long double inv = 1.0L / (long double)W1;
                    for (c = 0; c < 3; c++) {
                        P1[c] = q3_f((long double)P1[c] * inv);
                        R1[c] = q3_f((long double)R1[c] * inv);
                    }
                }
                k = 1.0L - (long double)W0;
                for (c = 0; c < 3; c++) {
                    P0[c] = q3_f((long double)P1[c] * k + (long double)P0[c]);
                    R0[c] = q3_f((long double)R1[c] * k + (long double)R0[c]);
                }
            } else if ((long double)W0 > 1.0L) {
                long double inv = 1.0L / (long double)W0;
                for (c = 0; c < 3; c++) {
                    P0[c] = q3_f((long double)P0[c] * inv);
                    R0[c] = q3_f((long double)R0[c] * inv);
                }
            }
            R0[0] = q3_f(Math_NormalizeAngle180(R0[0]));
            R0[1] = q3_f(Math_NormalizeAngle180(R0[1]));
            nz = q3_f(Math_NormalizeAngle180(R0[2]));
            for (c = 0; c < 3; c++)
                P0[c] = q3_f((long double)Q3F(j, 0x2c + c * 4) + (long double)P0[c]);
            R0[0] = q3_f((long double)Q3F(j, 0x38) + (long double)R0[0]);
            R0[1] = q3_f((long double)Q3F(j, 0x3c) + (long double)R0[1]);
            R0[2] = q3_f((long double)Q3F(j, 0x40) + (long double)nz);
            mat = Q3P(thing, 0x20) + off48;
            Angles_ToMatrix((float *)mat, (undefined4 *)R0, P0);
            v = (float *)(Q3P(thing, 0x24) + off12);
            if (Q3_NE_ORD(v[0], 0.0f) || Q3_NE_ORD(v[1], 0.0f) || Q3_NE_ORD(v[2], 0.0f))
                Matrix_BuildTransform((float *)(Q3P(thing, 0x20) + off48), (undefined4)v);
            node++;
            off12 += 0xc;
            off48 += 0x30;
            j += 0xb8;
        } while (node < Q3U(mdl, 0x54));
    }

done:
    rdThing_BuildNodeMatrix((int)thing, (int)Q3P(mdl, 0x58), frame);
    Q3U(thing, 0x1c) = UINT_004f5eb4;
}

/* ==== rdModel3_LoadText (0x0040aa20) ====
 * Loads a text .3do model (path, model record) through the stdConffile line reader (each line in the buffer
 * UINT_00900520 points to; the reader lower-cases and skips comments) and the game's own sscanf / strtok / atoi:
 * header and version, the material names (" %d: %s": copied into the stack slot the index names, then loaded with
 * rdMaterial_Load in slot order; an assertion when 0x80 or more), radius, insert offset, the geometry sets (+0x44 of
 * them at +0x24, 8 bytes each: mesh count and a zeroed 0x7c-byte mesh array) with their meshes (name, radius, optional
 * shadow, geometry / lighting / texture mode, up to 0x200 vertices with intensity, up to 0x300 uvs, the normals, up to
 * 0x200 faces of 0x4c bytes with up to 0x18 vertex / uv indexes and the face normals), and the hierarchy nodes (0xb8
 * bytes each at +0x58, parent / child / sibling indexes turned into node pointers, -1: 0); then
 * rdModel3_CountNodeChildren.  Returns 1, or 0 (after stdConffile_Close) at the first line that does not parse or a
 * failed allocation (whatever was allocated stays in the record).
 * Kept from the original: values copied with MOV are dword copies here (positions, uvs, face normals, node fields,
 * radius, offset, extra light); the vertex intensities and the vertex normals go through FLD / FSTP (q3_f); the third
 * allocation of a mesh (+0x3c, 4 bytes per vertex) is cleared for only `vertices` BYTES; the "mesh %d" and the
 * section names are scanned into the global buffer DAT_009056c0; every count is re-read from where the original keeps
 * it; every allocation passes the original's file name and line (the short at 0x004ddb80 + offset).
 * The original's material name slots are stack memory: an index outside 0..count-1 (a hole, or a slot past 0x80)
 * reads or writes memory that differs here (the game data has none). */
typedef void *(*q3_alloc_fn)(uint, char *, int);
typedef void (*q3_assert_fn)(char *, char *, int);
#define Q3_LINE(n) ((int)*(short *)IMG_ADDR(0x004ddb80) + (n))
#define Q3_FILE s_C__grimjedi_Libs_RDroid_Primitiv_004ddb94
#define Q3_ALLOC(size, n) (((q3_alloc_fn)Q3P(g_pSvcRdroid, 0x20))((size), Q3_FILE, Q3_LINE(n)))
#define Q3_LINEBUF ((char *)UINT_00900520)
#define Q3_SBUF ((char *)&DAT_009056c0)
#define Q3_READ() (stdConffile_ReadLine() != 0)
#define Q3_TOK(s, d) ((char *)strtok((byte *)(s), (byte *)(d)))
#define Q3_ATOI(t) ((int)atoi((uint)(t)))
#define Q3_WS ((char *)&DAT_004dd918)              /* " \t" */
#define Q3_WSC ((char *)IMG_ADDR(0x004ddc10))      /* " \t," */

/* OVERRIDES: rdModel3_LoadText */
undefined4 rdModel3_LoadText(char *path, char *m)
{
    char names[0x80][0x400];    /* [ESP+0x498]: material name slots */
    char name[0x400];           /* [ESP+0x98] */
    int idx, v0, v1, shadow;
    uint nmats, ngeo, nmesh, nv, ntv, nf, nn, i, g, me, f;
    uint x, y, z, w, rad, u, v, el;
    uint hp, hc, hs, h[6];
    char *gp, *mesh, *fp;

    rdModel3_NewEntry((undefined4 *)m);
    strncpy((uint *)m, (uint *)Str_FileNameFromPath(path), 0x1f);
    m[0x1f] = 0;
    if (((int (*)(char *))stdConffile_OpenRead)(path) == 0)
        return 0;
    if (!Q3_READ() || sscanf(Q3_LINEBUF, s_section___s_004ddd64, Q3_SBUF) != 1)
        goto fail;
    if (!Q3_READ())
        goto fail;
    sscanf(Q3_LINEBUF, s_3do__d__d_004ddd58, &v1, &v0);
    if (!Q3_READ() || sscanf(Q3_LINEBUF, s_section___s_004ddd64, Q3_SBUF) != 1)
        goto fail;
    if (!Q3_READ() || sscanf(Q3_LINEBUF, s_materials__d_004ddd48, &nmats) != 1)
        goto fail;
    if (nmats != 0) {
        if (nmats >= 0x80)
            ((q3_assert_fn)Q3P(g_pSvcRdroid, 0x18))((char *)IMG_ADDR(0x004ddd30), Q3_FILE, Q3_LINE(0x46));
        Q3P(m, 0x48) = (char *)Q3_ALLOC(nmats * 4, 0x49);
        if (Q3P(m, 0x48) == 0)
            goto fail;
        for (i = 0; i < nmats; i++) {
            char *d, *s;
            if (!Q3_READ() || sscanf(Q3_LINEBUF, s__d___s_004ddd28, &idx, name) != 2)
                goto fail;
            d = names[idx];
            s = name;
            while ((*d++ = *s++) != 0)
                ;
        }
        for (i = 0; i < nmats; i++) {
            ((void **)Q3P(m, 0x48))[i] = rdMaterial_Load(names[i], 0, 0);
            if (((void **)Q3P(m, 0x48))[i] == 0)
                goto fail;
        }
    }
    Q3U(m, 0x4c) = nmats;
    if (!Q3_READ() || sscanf(Q3_LINEBUF, s_section___s_004ddd64, Q3_SBUF) != 1)
        goto fail;
    if (!Q3_READ() || sscanf(Q3_LINEBUF, s_radius__f_004ddd1c, &rad) != 1)
        goto fail;
    Q3U(m, 0x5c) = rad;
    if (!Q3_READ() || sscanf(Q3_LINEBUF, s_insert_offset__f__f__f_004ddd04, &x, &y, &z) != 3)
        goto fail;
    Q3U(m, 0x84) = x;
    Q3U(m, 0x88) = y;
    Q3U(m, 0x8c) = z;
    if (!Q3_READ() || sscanf(Q3_LINEBUF, s_geosets__d_004ddcf8, &ngeo) != 1)
        goto fail;
    Q3U(m, 0x44) = ngeo;
    for (g = 0, gp = m + 0x28; g < ngeo; g++, gp += 8) {
        if (!Q3_READ() || sscanf(Q3_LINEBUF, s_geoset__d_004ddcec, &idx) != 1)
            goto fail;
        if (!Q3_READ() || sscanf(Q3_LINEBUF, s_meshes__d_004ddce0, &nmesh) != 1)
            goto fail;
        Q3P(gp, 0) = (char *)Q3_ALLOC(nmesh * 0x7c, 0xa1);
        if (Q3P(gp, 0) == 0)
            goto fail;
        for (i = 0; i < nmesh * 0x7c; i++)
            Q3P(gp, 0)[i] = 0;
        Q3U(gp, -4) = nmesh;
        for (me = 0; me < nmesh; me++) {
            mesh = Q3P(gp, 0) + me * 0x7c;
            Q3U(mesh, 0x20) = me;
            if (!Q3_READ() || sscanf(Q3_LINEBUF, s_mesh__d_004ddcd4, Q3_SBUF) != 1)
                goto fail;
            if (!Q3_READ() || sscanf(Q3_LINEBUF, s_name__s_004ddcc8, Q3_SBUF) != 1)
                goto fail;
            strncpy((uint *)mesh, (uint *)Q3_SBUF, 0x1f);
            mesh[0x1f] = 0;
            if (!Q3_READ() || sscanf(Q3_LINEBUF, s_radius__f_004ddd1c, mesh + 0x60) != 1)
                goto fail;
            if (!Q3_READ())
                goto fail;
            if (sscanf(Q3_LINEBUF, s_shadow__d_004ddcbc, &shadow) == 1) {
                Q3I(mesh, 0x54) = shadow;
                if (!Q3_READ())
                    goto fail;
            }
            if (sscanf(Q3_LINEBUF, s_geometrymode__d_004ddca8, mesh + 0x24) != 1)
                goto fail;
            if (!Q3_READ() || sscanf(Q3_LINEBUF, s_lightingmode__d_004ddc94, mesh + 0x28) != 1)
                goto fail;
            if (!Q3_READ() || sscanf(Q3_LINEBUF, s_texturemode__d_004ddc84, mesh + 0x2c) != 1)
                goto fail;
            if (!Q3_READ() || sscanf(Q3_LINEBUF, s_vertices__d_004ddc74, &nv) != 1)
                goto fail;
            if (nv > 0x200)
                goto fail;
            Q3U(mesh, 0x30) = 0;
            Q3U(mesh, 0x38) = 0;
            Q3U(mesh, 0x3c) = 0;
            if (nv != 0) {
                if ((Q3P(mesh, 0x30) = (char *)Q3_ALLOC(nv * 12, 0xf5)) == 0)
                    goto fail;
                if ((Q3P(mesh, 0x38) = (char *)Q3_ALLOC(nv * 4, 0xfa)) == 0)
                    goto fail;
                if ((Q3P(mesh, 0x3c) = (char *)Q3_ALLOC(nv * 4, 0xfe)) == 0)
                    goto fail;
                for (i = 0; i < nv; i++)    /* nv bytes, as the original's rep stos */
                    Q3P(mesh, 0x3c)[i] = 0;
            }
            fp = Q3P(mesh, 0x30);
            for (i = 0; i < nv; i++, fp += 12) {
                if (!Q3_READ() || sscanf(Q3_LINEBUF, s__d___f__f__f__f_004ddc60, &idx, &x, &y, &z, &w) != 5)
                    goto fail;
                Q3U(fp, 0) = x;
                Q3U(fp, 4) = y;
                Q3U(fp, 8) = z;
                ((float *)Q3P(mesh, 0x38))[i] = q3_f(*(float *)&w);
            }
            Q3U(mesh, 0x48) = nv;
            if (!Q3_READ() || sscanf(Q3_LINEBUF, s_texture_vertices__d_004ddc48, &ntv) != 1)
                goto fail;
            if (ntv > 0x300)
                goto fail;
            Q3U(mesh, 0x34) = 0;
            if (ntv != 0) {
                if ((Q3P(mesh, 0x34) = (char *)Q3_ALLOC(ntv * 8, 0x128)) == 0)
                    goto fail;
                fp = Q3P(mesh, 0x34);
                for (i = 0; i < ntv; i++, fp += 8) {
                    if (!Q3_READ() || sscanf(Q3_LINEBUF, s__d___f__f_004ddc3c, &idx, &u, &v) != 3)
                        goto fail;
                    Q3U(fp, 0) = u;
                    Q3U(fp, 4) = v;
                }
            }
            Q3U(mesh, 0x4c) = ntv;
            if (!Q3_READ())
                goto fail;
            Q3U(mesh, 0x44) = 0;
            if (nv != 0 && (Q3P(mesh, 0x44) = (char *)Q3_ALLOC(nv * 12, 0x148)) == 0)
                goto fail;
            for (i = 0; i < nv; i++) {
                if (!Q3_READ() || sscanf(Q3_LINEBUF, s__d___f__f__f_004ddc2c, &idx, &x, &y, &z) != 4)
                    goto fail;
                Q3F(Q3P(mesh, 0x44), i * 12) = q3_f(*(float *)&x);
                Q3F(Q3P(mesh, 0x44), i * 12 + 4) = q3_f(*(float *)&y);
                Q3F(Q3P(mesh, 0x44), i * 12 + 8) = q3_f(*(float *)&z);
            }
            if (!Q3_READ() || sscanf(Q3_LINEBUF, s_faces__d_004ddc20, &nf) != 1)
                goto fail;
            if (nf > 0x200)
                goto fail;
            Q3U(mesh, 0x50) = nf;
            Q3U(mesh, 0x40) = 0;
            if (nf != 0 && (Q3P(mesh, 0x40) = (char *)Q3_ALLOC(nf * 0x4c, 0x16d)) == 0)
                goto fail;
            fp = Q3P(mesh, 0x40);
            for (f = 0; f < nf; f++, fp += 0x4c) {
                int mi, n, k;
                if (!Q3_READ())
                    goto fail;
                FUN_00450220((undefined4 *)fp);
                Q3_TOK(Q3_LINEBUF, Q3_WS);
                mi = Q3_ATOI(Q3_TOK(0, Q3_WS));
                Q3U(fp, 0) = f;
                Q3P(fp, 0x20) = mi == -1 ? 0 : ((char **)Q3P(m, 0x48))[mi];
                if (sscanf(Q3_TOK(0, Q3_WS), (char *)&DAT_004ddc1c, fp + 4) != 1)
                    goto fail;
                if (sscanf(Q3_TOK(0, Q3_WS), (char *)&DAT_004ddc18, fp + 8) != 1)
                    goto fail;
                if (sscanf(Q3_TOK(0, Q3_WS), (char *)&DAT_004ddc18, fp + 0xc) != 1)
                    goto fail;
                if (sscanf(Q3_TOK(0, Q3_WS), (char *)&DAT_004ddc18, fp + 0x10) != 1)
                    goto fail;
                if (sscanf(Q3_TOK(0, Q3_WS), (char *)&DAT_004ddc14, &el) != 1)
                    goto fail;
                Q3U(fp, 0x30) = el;
                n = Q3_ATOI(Q3_TOK(0, Q3_WS));
                if (n == 0 || (uint)n > 0x18)
                    goto fail;
                Q3I(fp, 0x14) = n;
                if ((Q3P(fp, 0x18) = (char *)Q3_ALLOC(n * 4, 0x1a9)) == 0)
                    goto fail;
                if (Q3P(fp, 0x20) != 0 && (*(unsigned char *)Q3P(fp, 0x20) & 2) != 0) {
                    if ((Q3P(fp, 0x1c) = (char *)Q3_ALLOC(n * 4, 0x1b0)) == 0)
                        goto fail;
                    for (k = 0; (uint)k < (uint)n; k++) {
                        Q3I(Q3P(fp, 0x18), k * 4) = Q3_ATOI(Q3_TOK(0, Q3_WSC));
                        Q3I(Q3P(fp, 0x1c), k * 4) = Q3_ATOI(Q3_TOK(0, Q3_WSC));
                    }
                } else {
                    for (k = 0; (uint)k < (uint)n; k++) {
                        Q3I(Q3P(fp, 0x18), k * 4) = Q3_ATOI(Q3_TOK(0, Q3_WSC));
                        Q3_TOK(0, Q3_WSC);
                    }
                }
            }
            if (!Q3_READ())
                goto fail;
            fp = Q3P(mesh, 0x40);
            for (f = 0; f < Q3U(mesh, 0x50); f++, fp += 0x4c) {
                if (!Q3_READ() || sscanf(Q3_LINEBUF, s__d___f__f__f_004ddc2c, &idx, &x, &y, &z) != 4)
                    goto fail;
                Q3U(fp, 0x40) = x;
                Q3U(fp, 0x44) = y;
                Q3U(fp, 0x48) = z;
            }
        }
    }
    if (!Q3_READ() || sscanf(Q3_LINEBUF, s_section___s_004ddd64, Q3_SBUF) != 1)
        goto fail;
    if (!Q3_READ() || sscanf(Q3_LINEBUF, s_hierarchy_nodes__d_004ddbfc, &nn) != 1)
        goto fail;
    if ((Q3P(m, 0x58) = (char *)Q3_ALLOC(nn * 0xb8, 0x1ef)) == 0)
        goto fail;
    Q3U(m, 0x54) = nn;
    for (i = 0; i < nn; i++) {
        char *node;
        Q3U(Q3P(m, 0x58) + i * 0xb8, 0x44) = i;
        node = Q3P(m, 0x58) + i * 0xb8;
        if (!Q3_READ())
            goto fail;
        if (sscanf(Q3_LINEBUF, s__d___x__x__d__d__d__d__d__f__f___004ddbc4, &idx, node + 0x40, node + 0x48,
                   node + 0x4c, &hp, &hc, &hs, node + 0x58, &x, &y, &z, &h[0], &h[1], &h[2], &h[3], &h[4], &h[5],
                   node) != 0x12)
            goto fail;
        Q3P(node, 0x54) = (int)hp == -1 ? 0 : Q3P(m, 0x58) + hp * 0xb8;
        Q3P(node, 0x5c) = (int)hc == -1 ? 0 : Q3P(m, 0x58) + hc * 0xb8;
        Q3P(node, 0x60) = (int)hs == -1 ? 0 : Q3P(m, 0x58) + hs * 0xb8;
        Q3U(node, 0x70) = x;
        Q3U(node, 0x74) = y;
        Q3U(node, 0x78) = z;
        Q3U(node, 0x7c) = h[0];
        Q3U(node, 0x80) = h[1];
        Q3U(node, 0x84) = h[2];
        Q3U(node, 0x64) = h[3];
        Q3U(node, 0x68) = h[4];
        Q3U(node, 0x6c) = h[5];
    }
    rdModel3_CountNodeChildren((int)m);
    stdConffile_Close();
    return 1;
fail:
    stdConffile_Close();
    return 0;
}
#endif
