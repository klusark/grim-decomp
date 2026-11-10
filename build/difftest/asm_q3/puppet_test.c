/* Differential test of rdPuppet_AdvanceTrack and rdPuppet_UpdateFrame (build/overrides_asm_q3.c) against the original
 * 1.01 machine code (sliced from the assembly of 2df265d).
 *
 * Each case builds a random puppet / model / animation graph in an arena (track records, animations with nodes, keys
 * and markers, joints, the thing's matrix and scale arrays), runs the original and the C on the same arena contents
 * (restored between the runs, so every pointer is the same) under the x87 precision control 24, 53 or 64 bits
 * (rotating), and compares: the whole arena afterwards, the call log of the stand-in callees (arguments as dwords),
 * the x87 control word and the x87 stack top.
 * Inputs: small integers and halves (ties with key / marker times and frame counts), random floats, and 0, -0,
 * +-inf, quiet and signalling NaN, denormals; frame counts 0, small, and above 2^31 (the FILD of a uint); dt values
 * that land exactly on the frame count; the control word of DAT_00900526 with each rounding mode.
 * The stand-ins: rdPuppet_FadeOutTrack / rdPuppet_RemoveTrack change the track flags as the real ones do; the marker
 * callback sometimes changes the track's times, the marker count, the animation or the callback itself (the original
 * reads them again after each call); Math_NormalizeAngle180 returns an extended value (not a float) from a per-case
 * stream; rdMatrix_Build34 logs the angles and position it gets and writes the matrix.
 * usage: puppet_test.exe [cases per function]   (P3_NAN=1: no signalling NaN inputs) */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <stdint.h>
#include "fx.h"

typedef unsigned uint;
extern void orig_rdPuppet_AdvanceTrack(void *, int, uint), rdPuppet_AdvanceTrack(void *, int, uint);
extern void orig_rdPuppet_UpdateFrame(void *, float *), rdPuppet_UpdateFrame(void *, float *);

/* ---- arena: everything the functions can reach ---- */
#define ARSZ (1 << 18)
static unsigned char ar[ARSZ] __attribute__((aligned(16))), ar0[ARSZ], arA[ARSZ];
static uint used;
static void *A(uint n) { void *p = ar + used; used = (used + n + 15) & ~15u; if (used > ARSZ) abort(); return p; }
#define U(p, o) (*(uint *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(void **)((char *)(p) + (o)))

/* ---- per-case stream and call log ---- */
static uint64_t ss;
static uint snext(void) { ss ^= ss << 13; ss ^= ss >> 7; ss ^= ss << 17; return (uint)(ss >> 17); }
static uint lg[16384]; static int nlg;
static void L(uint v) { if (nlg < 16384) lg[nlg++] = v; }
static uint fbits(float f) { uint u; memcpy(&u, &f, 4); return u; }
static float bitsf(uint u) { float f; memcpy(&f, &u, 4); return f; }
static uint R(uint n) { return (uint)(fx_rnd() % n); }
static int nan_mode = -1;
static uint special_bits(uint k)
{
    static const uint t[] = {0x00000000, 0x80000000, 0x7f800000, 0xff800000, 0x7fc00000, 0x7f800001, 0xffc00000,
                             0x00000001, 0x807fffff, 0x3f800000, 0x3f7fffff, 0x3f800001, 0xbf800000, 0x7f7fffff,
                             0x7fa00000, 0xff800005};
    uint v = t[k % (sizeof t / sizeof t[0])];
    if (nan_mode >= 1 && (v & 0x7fc00000) == 0x7f800000 && (v & 0x7fffff)) v = 0x7fc00000;
    return v;
}
static float rf(float scale)
{
    uint k = R(40);
    if (k < 2) return bitsf(special_bits(R(64)));
    if (k < 14) return (float)((int)R(17) - 8) * 0.5f;
    return (float)(((double)(int)(fx_rnd() % 2000001) - 1000000.0) / 1000000.0 * scale);
}
static uint stream_f(void)
{
    uint k = snext() % 24;
    if (k == 0) return special_bits(snext());
    if (k < 8) return fbits((float)((int)(snext() % 9) - 4) * 0.25f);
    return fbits((float)(((double)(snext() % 2000001) - 1000000.0) / 1000.0));
}

/* ---- stand-in callees ---- */
static void *cur_pup, *alt_anim;
static void __cdecl marker_cb2(uint a, int track, uint v);
static void marker_effect(int track)
{
    char *rec = (char *)cur_pup + 8 + track * 0x134;
    switch (snext() % 24) {
    case 0: U(rec, 0x120) = stream_f(); break;
    case 6: U(rec, 0x120) = special_bits(snext()); break;
    case 1: U(rec, 0x124) = stream_f(); break;
    case 2: U(P(rec, 0x128), 0x40) = snext() % 9; break;
    case 3: if (alt_anim) P(rec, 0x128) = alt_anim; break;
    case 4: P(rec, 0x12c) = (void *)marker_cb2; break;
    case 5: U(P(rec, 0x128), 0x44 + 4 * (snext() % 8)) = stream_f(); break;
    }
}
static void __cdecl marker_cb(uint a, int track, uint v) { L(0xcb000001); L(a); L(track); L(v); marker_effect(track); }
static void __cdecl marker_cb2(uint a, int track, uint v) { L(0xcb000002); L(a); L(track); L(v); marker_effect(track); }
int __cdecl rdPuppet_FadeOutTrack(void *p, int track, uint secbits)
{
    char *rec = (char *)p + 8 + track * 0x134;
    L(0xfade0000); L((uint)p); L(track); L(secbits);
    U(rec, 0) = (U(rec, 0) & ~4u) | 8;
    U(rec, 0x1c) = 0x40800000;
    return 1;
}
void __cdecl rdPuppet_RemoveTrack(void *p, int track)
{
    char *rec = (char *)p + 8 + track * 0x134;
    L(0x5709000); L((uint)p); L(track);
    U(rec, 0) = 0;
    U(rec, 0x120) = snext();
}
long double __cdecl Math_NormalizeAngle180(uint bits)
{
    long double r;
    uint k = snext() % 8;
    L(0xa1800000); L(bits);
    if (k == 0) return (long double)bitsf(stream_f());
    if (k == 1) return (long double)bitsf(bits);
    r = (long double)bitsf(bits) / 3.0L + (long double)(snext() % 1000) / 7.0L;
    return r;
}
void __cdecl rdMatrix_Build34(uint *m, uint *ang, uint *pos)
{
    int k;
    L(0xa0700000); L((uint)m);
    for (k = 0; k < 3; k++) L(ang[k]);
    for (k = 0; k < 3; k++) L(pos[k]);
    for (k = 0; k < 12; k++) m[k] = snext();
}
void __cdecl Matrix_BuildTransform(uint *m, uint *v)
{
    L(0xb7000000); L((uint)m); L((uint)v); L(v[0]); L(v[1]); L(v[2]);
    m[0] ^= snext();
}
void __cdecl rdThing_BuildNodeMatrix(uint a, uint b, uint c) { L(0xb0de0000); L(a); L(b); L(c); }

static uint get_sw(void) { unsigned short sw; __asm__ volatile("fnstsw %0" : "=m"(sw)); return sw; }
static uint get_cw(void) { unsigned short cw; __asm__ volatile("fnstcw %0" : "=m"(cw)); return cw; }

/* ---- comparison bookkeeping ---- */
static uint lgA[16384]; static int nlgA;
static uint cwA, swA;
static long nf[4], nc[4], nnan[4];
static const char *fname[4] = {"rdPuppet_AdvanceTrack", "rdPuppet_UpdateFrame", "", ""};
/* 0 equal, 1 only NaN-vs-NaN dwords differ, 2 real difference */
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
static int dbg;
static void fail(int f, long i, const char *what)
{
    if (nf[f]++ < 5) printf("DIFF %s case %ld: %s\n", fname[f], i, what);
}
static const unsigned pcs[3] = {_PC_24, _PC_53, _PC_64};
static uint64_t cseed;
static int cpc;
static void begin(void)
{
    ss = cseed | 1; nlg = 0;
    memcpy(ar, ar0, used);
    _controlfp(pcs[cpc] | _RC_NEAR, _MCW_PC | _MCW_RC);
}
static void endA(void)
{
    cwA = get_cw(); swA = get_sw(); _controlfp(_PC_64 | _RC_NEAR, _MCW_PC | _MCW_RC);
    memcpy(lgA, lg, nlg * 4); nlgA = nlg; memcpy(arA, ar, used);
}
static void endB(int f, long i)
{
    uint cw = get_cw(), sw = get_sw();
    int k1, k2 = 0;
    _controlfp(_PC_64 | _RC_NEAR, _MCW_PC | _MCW_RC);
    if (cw != cwA) fail(f, i, "control word");
    if (((sw >> 11) & 7) != ((swA >> 11) & 7)) fail(f, i, "x87 stack top");
    if (nlg != nlgA) { fail(f, i, "call log length"); k2 = 2; }
    else k2 = fkind(lg, lgA, nlg);
    k1 = fkind(ar, arA, used / 4);
    if (k1 == 2 || k2 == 2) {
        fail(f, i, k1 == 2 ? "memory" : "call log");
        if (dbg) {
            int k;
            for (k = 0; k < (int)used / 4; k++)
                if (((uint *)ar)[k] != ((uint *)arA)[k]) printf("  ar+%05x orig %08x C %08x\n", k * 4, ((uint *)arA)[k], ((uint *)ar)[k]);
            for (k = 0; k < nlg && k < nlgA; k++)
                if (lg[k] != lgA[k]) printf("  log[%d] orig %08x C %08x\n", k, lgA[k], lg[k]);
        }
    } else if (k1 || k2)
        nnan[f]++;
    nc[f]++;
}
/* the control words of the frndint (DAT_00900526) and the default (DAT_00900524) */
static void set_cws(void)
{
    static const uint pcb[3] = {0x000, 0x200, 0x300};
    uint def = 0x007f | pcb[R(3)] | (R(6) == 0 ? R(4) << 10 : 0);
    uint rnd = 0x007f | pcb[R(3)] | (R(4) << 10);
    FXU32(0x900524) = def | (rnd << 16);
}

/* ---- rdPuppet_AdvanceTrack ---- */
static void t_advance(long i)
{
    char *pup, *thing, *mdl, *rec, *anim;
    int track = R(6), k, nm;
    uint dtb, cnt;
    used = 0;
    pup = A(8 + 6 * 0x134);
    for (k = 0; k < (8 + 6 * 0x134) / 4; k++) U(pup, k * 4) = (uint)fx_rnd();
    thing = A(0x60); mdl = A(0x60);
    for (k = 0; k < 0x18; k++) { U(thing, k * 4) = (uint)fx_rnd(); U(mdl, k * 4) = (uint)fx_rnd(); }
    P(pup, 4) = thing; P(thing, 4) = mdl;
    U(mdl, 0x54) = R(4) ? R(0x50) : (uint)fx_rnd();
    if (U(mdl, 0x54) > 0x40 && R(2)) U(mdl, 0x54) = 0x40;
    cur_pup = pup;
    rec = pup + 8 + track * 0x134;
    {
        static const uint fl[] = {0, 0x20, 0x40, 0x80, 0x60, 0xa0, 0xc0, 0xe0, 0x2, 0x6, 0x10, 0x200};
        U(rec, 0) = fl[R(12)] | (R(4) == 0 ? (uint)fx_rnd() & 0x31f : 0);
    }
    /* animation (and a second one the marker callback may switch to) */
    anim = 0; alt_anim = 0;
    for (k = 0; k < 2; k++) {
        char *a = A(0x90);
        int m;
        for (m = 0; m < 0x24; m++) U(a, m * 4) = (uint)fx_rnd();
        switch (R(8)) {
        case 0: cnt = 0; break;
        case 1: cnt = 0x80000000u + R(1000); break;
        case 3: cnt = (1u << (24 + R(8))) + R(300) - 150; break;   /* not a float: t / cnt near an integer */
        case 2: cnt = (uint)fx_rnd(); break;
        default: cnt = 1 + R(100); break;
        }
        U(a, 0x34) = cnt;
        nm = R(5) == 0 ? 0 : 1 + R(8);
        U(a, 0x40) = nm;
        {
            float mt = R(3) ? 0.0f : rf(10);
            for (m = 0; m < 8; m++) {
                F(a, 0x44 + m * 4) = mt;
                switch (R(5)) {
                case 0: mt = rf(cnt > 1000 ? 1000 : (float)cnt); break;
                case 1: break;
                default: mt += (float)R(5) * 0.5f; break;
                }
            }
        }
        if (k == 0) anim = a; else alt_anim = a;
    }
    P(rec, 0x128) = R(25) ? anim : 0;
    P(rec, 0x12c) = R(10) ? (void *)marker_cb : 0;
    F(rec, 0x124) = R(6) == 0 ? 0.0f : rf(cnt > 200 ? 200 : (float)(cnt + 1));
    {
        float c = (float)U(anim, 0x34), prev = F(rec, 0x124);
        switch (R(10)) {
        case 0: dtb = special_bits(R(64)); break;
        case 1: dtb = fbits(c - prev); break;                     /* lands on the frame count */
        case 6: dtb = fbits((float)((double)U(anim, 0x34) * (1 + R(4))) - prev); break;
        case 2: dtb = fbits(c * (float)(1 + R(4)) - prev); break;  /* on a multiple */
        case 3: dtb = 0; break;
        case 4: dtb = fbits(rf(1)); break;
        default: dtb = fbits(rf(c * 3.0f + 1.0f)); break;
        }
    }
    /* marker ties with the new time and with the previous time */
    if (R(3) == 0) F(anim, 0x44 + 4 * R(8)) = F(rec, 0x124);
    if (R(3) == 0) F(anim, 0x44 + 4 * R(8)) = (float)((long double)bitsf(dtb) + F(rec, 0x124));
    for (k = 0; k < 0x40; k++) U(rec, 0x20 + k * 4) = R(4) ? R(8) : (uint)fx_rnd();
    set_cws();
    memcpy(ar0, ar, used);
    cseed = fx_rnd(); cpc = i % 3;
    if (dbg) printf("case %ld: flags %x dt %08x prev %08x cnt %u cws %08x pc %d n %u\n", i, U(rec, 0), dtb, U(rec, 0x124),
                    P(rec, 0x128) ? U(P(rec, 0x128), 0x34) : 0, FXU32(0x900524), cpc, U(mdl, 0x54));
    begin(); orig_rdPuppet_AdvanceTrack(pup, track, dtb); endA();
    begin(); rdPuppet_AdvanceTrack(pup, track, dtb); endB(0, i);
}

/* ---- rdPuppet_UpdateFrame ---- */
#define KCAP 32
static char *make_anim(int nnodes, int nk, int nslots)
{
    char *a = A(0x90), *nodes = A(nnodes * 0x2c + 4);
    int n, k, m;
    for (m = 0; m < 0x24; m++) U(a, m * 4) = (uint)fx_rnd();
    U(a, 0x24) = R(4) == 0 ? 0x100 | R(0x100) : R(0x100);
    U(a, 0x2c) = R(4) ? R(8) : 0;
    U(a, 0x38) = nnodes;
    P(a, 0x3c) = nodes;
    for (n = 0; n < nnodes; n++) {
        char *nd = nodes + n * 0x2c, *keys = A(KCAP * 0x38);
        float t = R(3) ? 0.0f : rf(5);
        for (m = 0; m < 0x2c / 4; m++) U(nd, m * 4) = (uint)fx_rnd();
        U(nd, 0x20) = R(8) ? R(nslots) : 0x40 + R(4);
        U(nd, 0x24) = R(6) == 0 ? 0 : nk;
        P(nd, 0x28) = keys;
        for (k = 0; k < KCAP; k++) {
            char *kf = keys + k * 0x38;
            F(kf, 0) = t;
            t += R(3) == 0 ? 0.0f : (R(4) ? 0.5f * (1 + R(4)) : (float)(fx_rnd() % 1000) / 999.0f);
            if (R(60) == 0) t = rf(10);
            U(kf, 4) = R(4);
            for (m = 2; m < 14; m++) F(kf, m * 4) = rf(m < 8 ? 50 : 4);
        }
    }
    return a;
}
static void t_update(long i)
{
    char *thing, *mdl, *pup = 0, *joints, *anims[2];
    int nnodes = R(7), nanodes = R(6), nk = 1 + R(8), k, m;
    float frame[4];
    used = 0;
    thing = A(0x40); mdl = A(0x60);
    for (k = 0; k < 0x10; k++) U(thing, k * 4) = (uint)fx_rnd();
    for (k = 0; k < 0x18; k++) U(mdl, k * 4) = (uint)fx_rnd();
    P(thing, 4) = mdl;
    U(thing, 0x18) = R(40) == 0 ? 1 + R(5) : 0;
    U(mdl, 0x54) = nnodes;
    joints = A(nnodes * 0xb8 + 4);
    P(mdl, 0x58) = joints;
    for (k = 0; k < nnodes; k++) {
        char *j = joints + k * 0xb8;
        for (m = 0; m < 0xb8 / 4; m++) U(j, m * 4) = (uint)fx_rnd();
        U(j, 0x44) = R(10) ? R(nanodes + 1) : (uint)fx_rnd();
        U(j, 0x48) = R(8);
        for (m = 0; m < 6; m++) F(j, 0x70 + m * 4) = rf(m < 3 ? 20 : 180);
    }
    P(thing, 0x20) = A(nnodes * 0x30 + 4);
    P(thing, 0x24) = A(nnodes * 0xc + 4);
    for (k = 0; k < nnodes * 0xc; k++) U(P(thing, 0x20), k * 4) = (uint)fx_rnd();
    for (k = 0; k < nnodes * 3; k++)
        F(P(thing, 0x24), k * 4) = R(3) ? 0.0f : R(4) == 0 ? -0.0f : rf(2);
    anims[0] = make_anim(nanodes, nk, nanodes + 1);
    anims[1] = make_anim(nanodes, nk, nanodes + 1);
    if (R(12)) {
        pup = A(8 + 6 * 0x134);
        for (k = 0; k < (8 + 6 * 0x134) / 4; k++) U(pup, k * 4) = (uint)fx_rnd();
        U(pup, 0) = R(10) == 0 ? 1 + R(3) : 0;
        for (k = 0; k < 6; k++) {
            char *rec = pup + 8 + k * 0x134;
            static const float wt[] = {1.0f, 0.5f, 0.25f, 0.0f, 0.75f, 2.0f, 1.5f, 0.3f};
            P(rec, 0x128) = R(5) == 0 ? 0 : anims[R(2)];
            U(rec, 0) = R(5) == 0 ? 0 : (R(4) ? 2 : 0) | (R(3) == 0 ? R(0x400) : 0);
            if (P(rec, 0x128) == 0) U(rec, 0) = 0;   /* a track with flags has an animation (phase 1 reads it) */
            U(rec, 8) = (int)R(4) - 1;
            U(rec, 0xc) = (int)R(4) - 1;
            F(rec, 0x18) = R(8) ? wt[R(8)] : R(4) ? rf(2) : bitsf(special_bits(R(64)));
            for (m = 0; m < 0x40; m++) U(rec, 0x20 + m * 4) = R(nk);
            F(rec, 0x120) = R(12) == 0 ? rf(20) : 0.5f * R(20);
        }
    }
    P(thing, 0x14) = pup;
    FXU32(0x4f5eb4) = (uint)fx_rnd();
    for (k = 0; k < 4; k++) frame[k] = 0;
    memcpy(ar0, ar, used);
    cseed = fx_rnd(); cpc = i % 3;
    begin(); orig_rdPuppet_UpdateFrame(thing, frame); endA();
    begin(); rdPuppet_UpdateFrame(thing, frame); endB(1, i);
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000, i;
    int f, bad = 0;
    nan_mode = getenv("P3_NAN") ? atoi(getenv("P3_NAN")) : 0;
    dbg = getenv("P3DBG") != 0;
    for (i = 0; i < n; i++) t_advance(i);
    for (i = 0; i < n; i++) t_update(i);
    for (f = 0; f < 2; f++) {
        printf("%-32s %8ld cases, %ld differences, %ld NaN-payload-only\n", fname[f], nc[f], nf[f], nnan[f]);
        bad |= nf[f] != 0 || nnan[f] != 0;   /* strict: NaN payloads must match too */
    }
    return bad;
}
