/* Differential test of Collision_TestActorAgainstOthers (build/overrides_big_collision_others.c) against the original
 * machine code (orig_Collision_TestActorAgainstOthers, sliced from src/GRIMFANDANGO.EXE/asm_funcs.s).
 *
 * World built per case: 1..7 actors in the drawable list (0x008ca358, count 0x008ca330), each with a costume chain
 * (+0xa0 -> +4 -> +4 = model: radius +0x5c, box +0x60..+0x74, centre +0x78), a walker record (+0xa4: collision mode
 * +0x3f0, scale +0x3f4, collided flag +0x3f8, path +0x38, points +0x3c, index +0x44) or none, a frame at +0x38
 * (rotation about a random axis + translation, as sputActor_GetOrientMatrix builds it), position, previous position, flags.
 * The tested actor is in the list or not; actors are placed so that sphere and box overlaps are frequent; special
 * values (0, -0, NaN, inf, exact boundary values) are mixed in.
 *
 * The callees are models defined here (both implementations call the same ones): the Vec3 helpers compute what the
 * originals compute (decompiled formulas), rdVector_Normalize3Acc returns the length in ST0, sputActor_SetActorPosition moves the
 * actor (sometimes clamped, sometimes flips actor flags: the order of the flag reads is observable), Collision_BoxSlide
 * returns 0/1 and writes its output and the hit point 0x008ca320, Collision_PushOutOfBox moves its point, the others
 * only record.  Every call is logged with the CONTENTS of its pointer arguments (stack addresses differ) and global
 * pointers by value.  Compared after each run: return value, call log, all actor / walker / model / costume memory and
 * the data block 0x008ca300..0x008ca3a0.  Precision control 24, 53 and 64 bits in turn.
 * usage: coll_test.exe [cases] [seed] */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdint.h>

extern unsigned char fx_data[] __asm__("_sect_data");
#define FXDATA(va) (fx_data + ((va) - 0x4dd000))

extern int orig_Collision_TestActorAgainstOthers(void *), Collision_TestActorAgainstOthers(void *);

/* ---- deterministic randomness ---- */
static uint64_t seed = 88172645463325252ull, cseed;
static uint64_t rnd(void) { seed ^= seed << 13; seed ^= seed >> 7; seed ^= seed << 17; return seed; }
static unsigned R(unsigned n) { return (unsigned)(rnd() % n); }
static float rf(float s) { return (float)((double)(int)(rnd() % 2000001 - 1000000) / 1000000.0 * s); }
static uint64_t cs; /* callee randomness, reset before each run */
static unsigned CR(unsigned n) { cs ^= cs << 13; cs ^= cs >> 7; cs ^= cs << 17; return (unsigned)(cs % n); }
static float fbits(unsigned u) { float f; memcpy(&f, &u, 4); return f; }
static float special(float x)
{
    switch (R(60)) {
    case 0: return 0.0f; case 1: return -0.0f; case 2: return fbits(0x7fc00000); case 3: return fbits(0xffc00000);
    case 4: return fbits(0x7f800000); case 5: return fbits(0xff800000); case 6: return 1e-30f; case 7: return 3e38f;
    }
    return x;
}

/* ---- the world ---- */
#define NA 8
typedef struct World {
    unsigned char actor[NA][0x100];
    unsigned char walker[NA][0x400];
    unsigned char model[NA][0x90];
    unsigned char cos[NA][2][0x10];
    unsigned char data[0xa0];      /* 0x008ca300.. */
} World;
static World W, W0, Wa;
#define AF(a, o) (*(float *)(W.actor[a] + (o)))
#define AI(a, o) (*(int *)(W.actor[a] + (o)))

/* ---- call log ---- */
#define MAXLOG 512
typedef struct Ev { unsigned v[24]; } Ev;
static Ev logc[MAXLOG], loga[MAXLOG];
static int nlog, nloga, overflow;
static Ev *ev(int tag)
{
    static Ev dummy;
    if (nlog >= MAXLOG) { overflow = 1; return &dummy; }
    Ev *e = &logc[nlog++];
    memset(e, 0, sizeof *e);
    e->v[0] = tag;
    return e;
}
static void put3(Ev *e, int at, const float *p) { memcpy(&e->v[at], p, 12); }
static unsigned fb(float f) { unsigned u; memcpy(&u, &f, 4); return u; }

/* ---- callee models ---- */
float *sputActor_GetOrientMatrix(void *actor)
{
    Ev *e = ev(1); e->v[1] = (unsigned)(uintptr_t)actor;
    if (*(int *)((char *)actor + 0x34) == 0) *(int *)((char *)actor + 0x34) = 1;   /* frame kept as built */
    return (float *)((char *)actor + 0x38);
}
void rdMatrix_TransformVector34(float *out, float *v, float *m)
{
    Ev *e = ev(2); put3(e, 1, v); e->v[4] = (unsigned)(uintptr_t)v; e->v[5] = (unsigned)(uintptr_t)m;
    float x = v[0], y = v[1], z = v[2];
    out[0] = x * m[0] + y * m[3] + z * m[6];
    out[1] = m[1] * x + m[4] * y + z * m[7];
    out[2] = m[2] * x + m[8] * z + y * m[5];
}
void Vec3_Sub(float *out, float *a, float *b)
{
    Ev *e = ev(3); put3(e, 1, a); e->v[4] = (unsigned)(uintptr_t)a; e->v[5] = (unsigned)(uintptr_t)b;
    float x = a[0], y = a[1], z = a[2];
    out[0] = x * b[0] + y * b[3] + z * b[6] + b[9];
    out[1] = b[1] * x + b[4] * y + z * b[7] + b[10];
    out[2] = b[2] * x + b[8] * z + y * b[5] + b[11];
}
void Vec3_TransformTo(float *out, float *v, float *m)
{
    Ev *e = ev(4); put3(e, 1, v); e->v[5] = (unsigned)(uintptr_t)m;
    float x = v[0], y = v[1], z = v[2];
    out[0] = x * m[0] + y * m[1] + z * m[2];
    out[1] = m[3] * x + m[4] * y + z * m[5];
    out[2] = m[6] * x + m[8] * z + y * m[7];
}
void Vec3_Rotate3x3(float *vec, float *m)
{
    Ev *e = ev(5); put3(e, 1, vec); e->v[5] = (unsigned)(uintptr_t)m;
    unsigned va = (unsigned)(uintptr_t)vec;
    if (va >= (unsigned)(uintptr_t)FXDATA(0x8ca300) && va < (unsigned)(uintptr_t)FXDATA(0x8ca400)) e->v[6] = va;  /* global: by address */
    float x = vec[0], y = vec[1], z = vec[2];
    vec[0] = x * m[0] + y * m[3] + z * m[6] + m[9];
    vec[1] = m[1] * x + y * m[4] + z * m[7] + m[10];
    vec[2] = m[2] * x + z * m[8] + m[5] * y + m[11];
}
float rdVector_Normalize3Acc(float *v)
{
    Ev *e = ev(6); put3(e, 1, v);
    float l = sqrtf(v[0] * v[0] + v[2] * v[2] + v[1] * v[1]);
    if (l != 0.0f) { float k = 1.0f / l; v[0] *= k; v[1] *= k; v[2] *= k; }
    return l;
}
void sputActor_SetActorPosition(int actor, float *p)
{
    Ev *e = ev(7); e->v[1] = actor; put3(e, 2, p);
    float *pos = (float *)((char *)actor + 0xc);
    pos[0] = p[0]; pos[1] = p[1]; pos[2] = p[2];
    switch (CR(6)) {
    case 0: pos[1] = 0.5f; break;                                   /* clamped to a sector */
    case 1: *(int *)((char *)actor + 8) ^= 1; break;                 /* flags change inside the callee */
    case 2: *(int *)((char *)actor + 8) ^= 0x10; pos[0] += 0.25f; break;
    }
    *(int *)((char *)actor + 0x34) = 0;
}
int Collision_BoxSlide(float *a, float *b, float x0, float y0, float z0, float x1, float y1, float z1, float *out)
{
    Ev *e = ev(8); put3(e, 1, a); put3(e, 4, b);
    e->v[7] = fb(x0); e->v[8] = fb(y0); e->v[9] = fb(z0); e->v[10] = fb(x1); e->v[11] = fb(y1); e->v[12] = fb(z1);
    float *hit = (float *)FXDATA(0x8ca320);
    if (CR(3) == 0) return 0;
    out[0] = a[0] * 0.5f + b[0] * 0.5f; out[1] = a[1] - 0.125f; out[2] = b[2] + x0;
    hit[0] = a[0] + y1; hit[1] = b[1]; hit[2] = z0 * a[2];
    return 1;
}
void Collision_PushOutOfBox(float *p, float x0, float y0, float z0, float x1, float y1, float z1, float *frame, float *pos)
{
    Ev *e = ev(9); put3(e, 1, p);
    e->v[4] = fb(x0); e->v[5] = fb(y0); e->v[6] = fb(z0); e->v[7] = fb(x1); e->v[8] = fb(y1); e->v[9] = fb(z1);
    e->v[10] = (unsigned)(uintptr_t)frame; e->v[11] = (unsigned)(uintptr_t)pos;
    p[0] = x0 - 0.01f; p[1] = p[1] + pos[1]; p[2] = frame[9] + z1;
}
void sputActor_ActorWalkTo(int self, int goal, unsigned *path, unsigned other)
{
    Ev *e = ev(10); e->v[1] = self; put3(e, 2, (float *)goal); e->v[5] = (unsigned)(uintptr_t)path; e->v[6] = other;
    if (CR(2)) *(int *)((char *)self + 8) |= 0x20;
}
void sputLua_CollisionHandler(int self, int other, float *a, float *b, float *c)
{
    Ev *e = ev(11); e->v[1] = self; e->v[2] = other;
    e->v[3] = (unsigned)(uintptr_t)a; e->v[4] = (unsigned)(uintptr_t)b; e->v[5] = (unsigned)(uintptr_t)c;
    put3(e, 6, a); put3(e, 9, b); put3(e, 12, c);
}

/* ---- world generation ---- */
static void mkframe(int a)
{
    float *m = (float *)(W.actor[a] + 0x38);
    double ang = rf(3.14159f), c = cos(ang), s = sin(ang);
    int axis = R(4);
    memset(m, 0, 48);
    if (axis == 3) { for (int k = 0; k < 9; k++) m[k] = rf(1.2f); }      /* not orthonormal */
    else {
        int i = axis, j = (axis + 1) % 3, k = (axis + 2) % 3;
        m[i * 3 + i] = 1; m[j * 3 + j] = (float)c; m[j * 3 + k] = (float)s; m[k * 3 + j] = (float)-s; m[k * 3 + k] = (float)c;
    }
    m[9] = AF(a, 0xc); m[10] = AF(a, 0x10); m[11] = AF(a, 0x14);
    if (R(30) == 0) m[R(12)] = special(m[0]);
}
static void gen(int *pself, int *pn)
{
    int n = 1 + R(7), self = R(n), inlist = R(12) != 0;
    float spread = R(3) ? 1.5f : 0.3f;
    memset(&W, 0, sizeof W);
    for (int a = 0; a < NA; a++) {
        unsigned char *md = W.model[a];
        AF(a, 0xc) = rf(spread); AF(a, 0x10) = rf(spread); AF(a, 0x14) = R(3) ? rf(0.2f) : 0;
        AF(a, 0x18) = AF(a, 0xc) + rf(0.3f); AF(a, 0x1c) = AF(a, 0x10) + rf(0.3f); AF(a, 0x20) = AF(a, 0x14) + rf(0.05f);
        for (int k = 0xc; k <= 0x20; k += 4) if (R(25) == 0) AF(a, k) = special(AF(a, k));
        AI(a, 8) = R(4) | (R(2) << 8);
        AI(a, 0x34) = R(2);
        mkframe(a);
        *(void **)(W.actor[a] + 0xa0) = W.cos[a][0];
        *(void **)(W.cos[a][0] + 4) = W.cos[a][1];
        *(void **)(W.cos[a][1] + 4) = md;
        *(float *)(md + 0x5c) = R(10) ? 0.05f + fabsf(rf(1.4f)) : special(0.3f);
        for (int k = 0; k < 3; k++) {
            *(float *)(md + 0x60 + 4 * k) = R(4) ? -fabsf(rf(1.1f)) : -(float)R(1000) / 900.0f;
            *(float *)(md + 0x6c + 4 * k) = R(4) ? fabsf(rf(1.1f)) : (float)R(1000) / 900.0f;
            *(float *)(md + 0x78 + 4 * k) = R(3) ? rf(0.2f) : 0;
        }
        for (int k = 0x5c; k <= 0x80; k += 4) if (R(40) == 0) *(float *)(md + k) = special(*(float *)(md + k));
        if (R(8) || a == self) {   /* the tested actor always has one (the original reads its scale first) */
            unsigned char *wk = W.walker[a];
            *(void **)(W.actor[a] + 0xa4) = wk;
            int mode = R(10); *(int *)(wk + 0x3f0) = mode < 2 ? 0 : mode < 6 ? 1 : mode < 9 ? 2 : 3 + R(3);
            *(float *)(wk + 0x3f4) = R(6) ? 0.5f + fabsf(rf(1.0f)) : special(1.0f);
            *(int *)(wk + 0x3f8) = R(4) == 0;
            for (int k = 0x38; k < 0x100; k += 4) *(float *)(wk + k) = rf(3);
            *(int *)(wk + 0x44) = R(5);
        }
    }
    unsigned char *d = FXDATA(0x8ca300);
    memset(d, 0, 0xa0);
    for (int k = 0; k < 0xa0; k += 4) if (R(2)) *(float *)(d + k) = rf(2);
    int cnt = inlist ? n : (n > 1 ? n - 1 : (R(2) ? 0 : 1));
    if (R(20) == 0) cnt = 0;
    *(int *)FXDATA(0x8ca330) = cnt;
    for (int k = 0; k < cnt; k++) {
        int a = k;
        if (!inlist && k >= self) a = k + 1;
        ((void **)FXDATA(0x8ca358))[k] = W.actor[a];
    }
    if (R(10) == 0 && cnt > 1) ((void **)FXDATA(0x8ca358))[R(cnt)] = W.actor[self];  /* self twice */
    *pself = self; *pn = n;
    /* spheres exactly touching (to a few ulps): the other's centre is put at distance r0 + r1 from self's */
    if (R(3) == 0 && n > 1) {
        int o = (self + 1 + R(n - 1)) % n;
        unsigned char *ow = *(unsigned char **)(W.actor[o] + 0xa4);
        if (ow && *(int *)(ow + 0x3f0)) {
            float *fs = (float *)(W.actor[self] + 0x38), *fo = (float *)(W.actor[o] + 0x38);
            float *cs_ = (float *)(W.model[self] + 0x78), *co = (float *)(W.model[o] + 0x78);
            double r0 = (double)*(float *)(W.model[self] + 0x5c) * *(float *)(*(unsigned char **)(W.actor[self] + 0xa4) + 0x3f4);
            double r1 = (double)*(float *)(W.model[o] + 0x5c) * *(float *)(ow + 0x3f4);
            double A[3], Bc[3], dir[3], l;
            for (int k = 0; k < 3; k++) A[k] = (double)(cs_[0] * fs[k] + cs_[1] * fs[3 + k] + cs_[2] * fs[6 + k]) + *(float *)(W.actor[self] + 0xc + 4 * k);
            for (int k = 0; k < 3; k++) dir[k] = rf(1); dir[2] *= 0.1; l = sqrt(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]);
            if (l == 0) l = 1, dir[0] = 1;
            double d = (r0 + r1) * (1 + (double)(int)(R(9) - 4) * 3e-8);
            for (int k = 0; k < 3; k++) Bc[k] = A[k] + dir[k] / l * d;
            /* B = rot * co + t: choose t */
            for (int k = 0; k < 3; k++) fo[9 + k] = (float)(Bc[k] - (co[0] * fo[k] + co[1] * fo[3 + k] + co[2] * fo[6 + k]));
        }
    }
    /* place some actors exactly touching / on box faces */
    if (R(4) == 0 && n > 1) {
        int o = (self + 1) % n;
        AF(o, 0xc) = AF(self, 0xc) + (R(2) ? 0.5f : 0.0f); AF(o, 0x10) = AF(self, 0x10); AF(o, 0x14) = AF(self, 0x14);
        mkframe(o);
    }
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000, i, fails = 0, hits[4] = {0};
    unsigned pcs[3] = {_PC_24, _PC_53, _PC_64};
    if (argc > 2) seed = strtoull(argv[2], 0, 0);
    for (i = 0; i < n; i++) {
        int self, na, ra, rb;
        unsigned pc = pcs[i % 3];
        gen(&self, &na);
        memcpy(W.data, FXDATA(0x8ca300), 0xa0);
        W0 = W;
        cseed = rnd() | 1;
        /* original */
        cs = cseed; nlog = 0; overflow = 0;
        _controlfp(pc, _MCW_PC);
        ra = orig_Collision_TestActorAgainstOthers(W.actor[self]);
        _controlfp(_PC_64, _MCW_PC);
        memcpy(W.data, FXDATA(0x8ca300), 0xa0);
        Wa = W; memcpy(loga, logc, sizeof(Ev) * nlog); nloga = nlog;
        /* C */
        W = W0; memcpy(FXDATA(0x8ca300), W0.data, 0xa0);
        cs = cseed; nlog = 0;
        _controlfp(pc, _MCW_PC);
        rb = Collision_TestActorAgainstOthers(W.actor[self]);
        _controlfp(_PC_64, _MCW_PC);
        memcpy(W.data, FXDATA(0x8ca300), 0xa0);
        int bad = 0;
        if (ra != rb) { bad = 1; if (fails < 20) printf("DIFF ret %d %d (case %ld)\n", ra, rb, i); }
        if (nloga != nlog || memcmp(loga, logc, sizeof(Ev) * nlog)) {
            bad = 1;
            if (fails < 20) {
                printf("DIFF log (case %ld, pc %x): %d vs %d events\n", i, pc, nloga, nlog);
                for (int k = 0; k < nlog && k < nloga; k++)
                    if (memcmp(&loga[k], &logc[k], sizeof(Ev))) {
                        printf("  event %d tag %u:", k, loga[k].v[0]);
                        for (int j = 1; j < 16; j++) if (loga[k].v[j] != logc[k].v[j]) printf(" [%d] %08x/%08x", j, loga[k].v[j], logc[k].v[j]);
                        printf("\n"); break;
                    }
            }
        }
        if (memcmp(&Wa, &W, sizeof W)) {
            bad = 1;
            if (fails < 20) {
                unsigned char *x = (unsigned char *)&Wa, *y = (unsigned char *)&W;
                for (size_t k = 0; k < sizeof W; k++) if (x[k] != y[k]) { printf("DIFF mem (case %ld, pc %x) at world+0x%x\n", i, pc, (unsigned)k); break; }
            }
        }
        if (overflow) printf("log overflow (case %ld)\n", i);
        fails += bad;
        for (int k = 0; k < nloga; k++) {
            if (loga[k].v[0] == 6) hits[0]++;        /* sphere push (mode 2) */
            if (loga[k].v[0] == 8) hits[1]++;        /* inside the box */
            if (loga[k].v[0] == 9) hits[2]++;        /* pushed out */
            if (loga[k].v[0] == 10) hits[3]++;       /* replan */
        }
    }
    printf("coll_test: sphere pushes %ld, box hits %ld, push-outs %ld, replans %ld\n", hits[0], hits[1], hits[2], hits[3]);
    printf("coll_test: %ld cases, %ld differences\n", n, fails);
    return fails != 0;
}
