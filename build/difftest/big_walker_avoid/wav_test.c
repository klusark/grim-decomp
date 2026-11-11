/* Differential test of Walker_AvoidActorPath (build/overrides_big_walker_avoid.c) against the original machine code
 * (orig_Walker_AvoidActorPath, sliced from src/GRIMFANDANGO.EXE/asm_funcs.s).
 *
 * Every callee (sputActor_GetOrientMatrix, rdMatrix_TransformVector34, Vec3_Sub, GetOuttaTheBox, WalkPlane_PlaneAt,
 * TestCollision, WalkPlane_PlaneClosest, WalkPlane_SnapTo, FindObjectCorners, BuildPath,
 * Collision_PickDetour, GetPath, Collision_PointInBox) is a recorder defined here.  Each call logs:
 *   - every argument: pointers into the test's own buffers absolutely, pointers into (or computed from) the caller's
 *     frame relative to the frame base, plus the dwords they point to (3, 6 or 16);
 *   - the whole 0x104-byte frame of the function under test (original ESP+0x10 .. +0x113) at the moment of the call;
 *   - its return value.
 * The recorders take their decisions (return values, output points, path lengths and contents, pushed-out points) from a
 * random stream that is reset to the same state for both runs.  Both versions run on a private stack that is filled with
 * the same byte pattern first, so stale frame slots compare equal too.  After the run the return value, the output buffer
 * (with guard space), the input points (written by the push-out recorder) and DAT_008ca320 are compared.
 * The frame base is taken from the first rdMatrix_TransformVector34 (its output is the frame slot 0x108).
 * Cases cycle through the x87 precision controls 24, 53 and 64 bits.
 * usage: wav_test.exe [cases] */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <stdint.h>
#include "fx.h"

extern unsigned char g_dat8ca320[12] __asm__("_DAT_008ca320");

/* ---- run on a private, pattern-filled stack ---- */
static uint32_t stk[1 << 15] __attribute__((aligned(16)));
unsigned call_on_stack(void *fn, unsigned *args, void *top);
__asm__(".text\n.globl _call_on_stack\n_call_on_stack:\n"
        "\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edi\n"
        "\tmovl 8(%ebp),%eax\n\tmovl 12(%ebp),%edx\n\tmovl 16(%ebp),%esp\n"
        "\tpushl 16(%edx)\n\tpushl 12(%edx)\n\tpushl 8(%edx)\n\tpushl 4(%edx)\n\tpushl (%edx)\n"
        "\tcall *%eax\n\tleal -12(%ebp),%esp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tpopl %ebp\n\tret\n");

extern unsigned orig_Walker_AvoidActorPath(void *, void *, void *, unsigned, float *);
extern unsigned Walker_AvoidActorPath(void *, void *, void *, unsigned, float *);

/* ---- the recorders' random stream ---- */
static uint64_t rs;
static unsigned R(void) { rs ^= rs << 13; rs ^= rs >> 7; rs ^= rs << 17; return (unsigned)(rs >> 11); }
static unsigned pct_hit, pct_plan, pct_inbox, pct_found, pct_push, pct_nan, pct_fine;
static float rfl(void)
{
    unsigned u;
    float f;
    if (R() % 100 < pct_fine)          /* full 24-bit mantissas */
        return (float)((int)(R() % 2000001) - 1000000) * 1.37e-5f + (float)((int)(R() % 7) - 3);
    switch (R() % 64) {
    case 0: return 0.0f;
    case 1: return -0.0f;
    case 2: if (R() % 100 < pct_nan) { u = 0x7fc00000 | (R() & 0x3fffff); memcpy(&f, &u, 4); return f; } return 1.0f;
    case 3: if (R() % 100 < pct_nan) { u = 0xff800000; memcpy(&f, &u, 4); return f; } return -1.0f;
    case 4: u = 0x7fa00000; if (R() % 100 < pct_nan) { memcpy(&f, &u, 4); return f; } return 2.0f;   /* signalling NaN */
    case 5: return 1e-30f * (float)((int)(R() % 2001) - 1000);
    case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13:
        return (float)((int)(R() % 2000001) - 1000000) * 1e-5f;
    }
    return (float)((int)(R() % 33) - 16) * 0.25f;          /* a coarse grid: equal distances happen */
}

/* ---- test memory ---- */
static float ptsbuf[64 * 3], outbuf[4096 * 3], pathbuf[2][16 * 3], mats[2][12];
static unsigned char actor[2][0x100], cosbuf[2][0x100], lnk[4][8], scl[2][0x400];
static unsigned char sector_dummy[16];
typedef struct { uint32_t lo, hi; } Rg;
static Rg regs[16];
static int nregs;
static void reg(void *p, unsigned len) { regs[nregs].lo = (uint32_t)(uintptr_t)p; regs[nregs].hi = regs[nregs].lo + len; nregs++; }

/* ---- the log ---- */
typedef struct {
    int tag, ret;
    uint32_t a[12];
    uint32_t d[12][16];
    uint32_t frame[0x41];
    int hasframe;
} Ev;
#define MAXEV 600
static Ev lg[2][MAXEV];
static int nlg[2], cur_run, nev, budget_over;
static uint32_t fbase;            /* the caller's ESP after its prologue (frame slot 0 at fbase) */

static int in_regions(uint32_t p, unsigned len)
{
    for (int i = 0; i < nregs; i++)
        if (p >= regs[i].lo && p + len <= regs[i].hi) return 1;
    return 0;
}
static int in_frame(uint32_t p, unsigned len) { return fbase && p >= fbase + 0x10 && p + len <= fbase + 0x114; }

/* kind: 0 plain value, else number of dwords to dump behind the pointer; negative: a pointer the caller computes from
 * its frame (a corner, possibly with a wild index), always logged frame-relative even when it lands in a test buffer */
static Ev *ev_begin(int tag, int nargs, const uint32_t *args, const int *kind)
{
    Ev *e = &lg[cur_run][nev < MAXEV ? nev : MAXEV - 1];
    memset(e, 0, sizeof *e);
    e->tag = tag;
    for (int i = 0; i < nargs; i++) {
        uint32_t v = args[i];
        if (!kind[i]) { e->a[i] = v; continue; }
        unsigned len = (kind[i] < 0 ? -kind[i] : kind[i]) * 4;
        if (kind[i] > 0 && in_regions(v, len)) { e->a[i] = v; memcpy(e->d[i], (void *)(uintptr_t)v, len); }
        else if (fbase) {
            e->a[i] = (v - fbase) ^ 0x5a000000u;    /* frame-relative (also for out-of-frame addresses computed from it) */
            if (in_frame(v, len)) memcpy(e->d[i], (void *)(uintptr_t)v, len);
            else e->d[i][15] = 0xdeadbeef;
        } else e->a[i] = v;
    }
    if (fbase) { memcpy(e->frame, (void *)(uintptr_t)(fbase + 0x10), 0x104); e->hasframe = 1; }
    nev++;
    if (nev > 400) budget_over = 1;
    return e;
}
static int ev_end(Ev *e, int r) { e->ret = r; return r; }

static void rand_pt(float *p) { p[0] = rfl(); p[1] = rfl(); p[2] = rfl(); }

/* ---- recorders ---- */
float *sputActor_GetOrientMatrix(void *a)
{
    uint32_t ar[1] = {(uint32_t)(uintptr_t)a}; static const int k[1] = {0};
    Ev *e = ev_begin(1, 1, ar, k);
    float *m = a == (void *)actor[0] ? mats[0] : mats[1];
    ev_end(e, (int)(uintptr_t)m);
    return m;
}
void rdMatrix_TransformVector34(float *out, float *v, float *m)
{
    uint32_t ar[3] = {(uint32_t)(uintptr_t)out, (uint32_t)(uintptr_t)v, (uint32_t)(uintptr_t)m}; static const int k[3] = {3, 3, 12};
    if (!fbase) fbase = (uint32_t)(uintptr_t)out - 0x108;
    Ev *e = ev_begin(2, 3, ar, k);
    rand_pt(out);
    ev_end(e, 0);
}
void Vec3_Sub(float *out, float *a, float *b)
{
    uint32_t ar[3] = {(uint32_t)(uintptr_t)out, (uint32_t)(uintptr_t)a, (uint32_t)(uintptr_t)b}; static const int k[3] = {3, 3, 12};
    Ev *e = ev_begin(3, 3, ar, k);
    rand_pt(out);
    ev_end(e, 0);
}
void GetOuttaTheBox(uint32_t pt, uint32_t b0, uint32_t b1, uint32_t b2, uint32_t b3, uint32_t b4, uint32_t b5,
                            uint32_t frame, uint32_t pos)
{
    uint32_t ar[9] = {pt, b0, b1, b2, b3, b4, b5, frame, pos}; static const int k[9] = {3, 0, 0, 0, 0, 0, 0, 12, 3};
    Ev *e = ev_begin(4, 9, ar, k);
    if (R() % 100 < pct_push && in_regions(pt, 12)) rand_pt((float *)(uintptr_t)pt);
    ev_end(e, 0);
}
void *WalkPlane_PlaneAt(uint32_t p, uint32_t f)
{
    uint32_t ar[2] = {p, f}; static const int k[2] = {3, 0};
    Ev *e = ev_begin(5, 2, ar, k);
    return (void *)(uintptr_t)ev_end(e, R() % 100 < pct_found ? (int)(uintptr_t)sector_dummy : 0);
}
int TestCollision(uint32_t a, uint32_t b, uint32_t c, uint32_t b0, uint32_t b1, uint32_t b2, uint32_t b3,
                             uint32_t b4, uint32_t b5, uint32_t frame)
{
    uint32_t ar[10] = {a, b, c, b0, b1, b2, b3, b4, b5, frame}; static const int k[10] = {3, 3, 3, 0, 0, 0, 0, 0, 0, 12};
    Ev *e = ev_begin(6, 10, ar, k);
    return ev_end(e, budget_over ? 1 : (R() % 100 < pct_hit ? (int)(R() % 3) + 1 : 0));
}
void *WalkPlane_PlaneClosest(uint32_t p, uint32_t f)
{
    uint32_t ar[2] = {p, f}; static const int k[2] = {3, 0};
    Ev *e = ev_begin(7, 2, ar, k);
    return (void *)(uintptr_t)ev_end(e, (int)(uintptr_t)(sector_dummy + 4));
}
void __attribute__((thiscall)) WalkPlane_SnapTo(void *self, float *pos)
{
    uint32_t ar[2] = {(uint32_t)(uintptr_t)self, (uint32_t)(uintptr_t)pos}; static const int k[2] = {0, 3};
    Ev *e = ev_begin(8, 2, ar, k);
    if (R() % 2) pos[1] = rfl();
    ev_end(e, 0);
}
void FindObjectCorners(uint32_t cos, uint32_t r, uint32_t frame, uint32_t z, uint32_t corners)
{
    uint32_t ar[5] = {cos, r, frame, z, corners}; static const int k[5] = {0, 0, 12, 0, 3};
    Ev *e = ev_begin(9, 5, ar, k);
    float *c = (float *)(uintptr_t)corners;
    if (in_frame(corners, 48))
        for (int i = 0; i < 4; i++) {
            rand_pt(c + 3 * i);
            if (R() % 4 == 0 && i) memcpy(c + 3 * i, c + 3 * (i - 1), 12);   /* equal corners: equal distances */
        }
    if (in_frame(corners, 48) && R() % 3 == 0)      /* near ties: all corners within an ulp or two of the first */
        for (int i = 1; i < 4; i++)
            for (int j = 0; j < 3; j++) {
                uint32_t u;
                memcpy(&u, c + j, 4);
                u += (int)(R() % 5) - 2;
                memcpy(c + 3 * i + j, &u, 4);
            }
    ev_end(e, 0);
}
int BuildPath(uint32_t a, uint32_t b, uint32_t f)
{
    uint32_t ar[3] = {a, b, f}; static const int k[3] = {3, -3, 0};
    Ev *e = ev_begin(10, 3, ar, k);
    return ev_end(e, R() % 100 < pct_plan ? (int)(R() % 2) + 1 : 0);
}
int Collision_PickDetour(uint32_t a, uint32_t t, uint32_t corners)
{
    uint32_t ar[3] = {a, t, corners}; static const int k[3] = {3, 3, 16};
    Ev *e = ev_begin(11, 3, ar, k);
    return ev_end(e, (int)(R() % 5) - 1);
}
int GetPath(uint32_t pp)
{
    uint32_t ar[1] = {pp}; static const int k[1] = {1};
    static const int lens[8] = {-1, 0, 1, 2, 2, 3, 4, 6};
    Ev *e = ev_begin(12, 1, ar, k);
    float *pb = pathbuf[R() % 2];
    int n = lens[R() % 8];
    for (int i = 0; i < 16; i++) rand_pt(pb + 3 * i);
    if (in_frame(pp, 4)) *(float **)(uintptr_t)pp = pb;
    return ev_end(e, n);
}
int Collision_PointInBox(uint32_t a, uint32_t b, uint32_t c, uint32_t b0, uint32_t b1, uint32_t b2, uint32_t b3,
                         uint32_t b4, uint32_t b5, uint32_t frame, uint32_t off)
{
    uint32_t ar[11] = {a, b, c, b0, b1, b2, b3, b4, b5, frame, off}; static const int k[11] = {3, 3, 3, 0, 0, 0, 0, 0, 0, 12, 3};
    Ev *e = ev_begin(13, 11, ar, k);
    return ev_end(e, budget_over ? 1 : (R() % 100 < pct_inbox ? (int)(R() % 2) + 1 : 0));
}

/* ---- one case ---- */
static float s_pts[64 * 3], res_pts[2][64 * 3], res_out[2][4096 * 3];
static unsigned char s_dat[12], res_dat[2][12];
static unsigned rets[2];
static long nnull, nhit, ngarbage_seen, nboth, nwalk, nfinal;

static void put_f(void *p, float f) { memcpy(p, &f, 4); }

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000, i;
    unsigned pcs[3] = {_PC_24, _PC_53, _PC_64};
    long hist[64] = {0};

    reg(ptsbuf, sizeof ptsbuf); reg(outbuf, sizeof outbuf); reg(pathbuf, sizeof pathbuf); reg(mats, sizeof mats);
    reg(actor, sizeof actor); reg(cosbuf, sizeof cosbuf); reg(scl, sizeof scl); reg(g_dat8ca320, 12);
    for (i = 0; i < n; i++) {
        uint64_t seed;
        unsigned count = R() % 8, pc = pcs[i % 3];
        int nullother = R() % 12 == 0;
        float *pts = ptsbuf + 3 * 8;          /* count 0 reads pts[-1] */
        pct_hit = (unsigned[]){0, 20, 50, 80, 100}[R() % 5];
        pct_plan = (unsigned[]){0, 30, 60, 100}[R() % 4];
        pct_inbox = (unsigned[]){0, 20, 50, 90}[R() % 4];
        pct_found = R() % 10 ? 100 : 50;
        pct_push = R() % 3 ? 30 : 0;
        pct_nan = R() % 4 ? 0 : 50;
        pct_fine = (unsigned[]){0, 50, 90}[R() % 3];
        /* actors: actor+0xa0 -> +4 -> +4 = costume record; actor+0xa4 -> +0x3f4 scale */
        for (int k = 0; k < 2; k++) {
            *(void **)(actor[k] + 0xa0) = lnk[2 * k];
            *(void **)(lnk[2 * k] + 4) = lnk[2 * k + 1];
            *(void **)(lnk[2 * k + 1] + 4) = cosbuf[k];
            *(void **)(actor[k] + 0xa4) = scl[k];
            for (int j = 0; j < 0x40; j++) put_f(cosbuf[k] + 4 * j, rfl());
            for (int j = 0; j < 3; j++) put_f(actor[k] + 0xc + 4 * j, rfl());
            put_f(scl[k] + 0x3f4, R() % 4 == 0 ? 0.0f : (R() % 8 == 0 ? -0.0f : rfl()));
            for (int j = 0; j < 12; j++) mats[k][j] = rfl();
        }
        for (int j = 0; j < 64 * 3; j++) ptsbuf[j] = rfl();
        for (int j = 0; j < 3; j++) put_f(g_dat8ca320 + 4 * j, rfl());
        memcpy(s_pts, ptsbuf, sizeof s_pts); memcpy(s_dat, g_dat8ca320, 12);
        seed = ((uint64_t)R() << 32 | R()) | 1;
        for (int run = 0; run < 2; run++) {
            unsigned args[5];
            memcpy(ptsbuf, s_pts, sizeof s_pts); memcpy(g_dat8ca320, s_dat, 12);
            memset(outbuf, 0xab, sizeof outbuf);
            memset(stk, 0xcd, sizeof stk);
            rs = seed; cur_run = run; nev = 0; fbase = 0; budget_over = 0;
            args[0] = (unsigned)(uintptr_t)actor[0];
            args[1] = nullother ? 0 : (unsigned)(uintptr_t)actor[1];
            args[2] = (unsigned)(uintptr_t)pts; args[3] = count; args[4] = (unsigned)(uintptr_t)outbuf;
            _controlfp(pc, _MCW_PC);
            rets[run] = call_on_stack(run ? (void *)Walker_AvoidActorPath : (void *)orig_Walker_AvoidActorPath, args,
                                      (unsigned char *)stk + sizeof stk - 64);
            _controlfp(_PC_64, _MCW_PC);
            nlg[run] = nev;
            memcpy(res_pts[run], ptsbuf, sizeof s_pts); memcpy(res_out[run], outbuf, sizeof outbuf);
            memcpy(res_dat[run], g_dat8ca320, 12);
        }
        fx_cases++;
        if (nullother) nnull++;
        hist[nlg[0] < 63 ? nlg[0] : 63]++;
        {
            int bad = 0;
            if (rets[0] != rets[1]) { if (fx_fails < 20) printf("  ret orig %u mine %u\n", rets[0], rets[1]); bad = 1; }
            if (nlg[0] != nlg[1]) { if (fx_fails < 20) printf("  log length orig %d mine %d\n", nlg[0], nlg[1]); bad = 1; }
            for (int k = 0; k < nlg[0] && k < nlg[1] && k < MAXEV; k++)
                if (memcmp(&lg[0][k], &lg[1][k], sizeof(Ev))) {
                    if (fx_fails < 20) {
                        Ev *x = &lg[0][k], *y = &lg[1][k];
                        printf("  call %d differs: tag %d/%d ret %d/%d", k, x->tag, y->tag, x->ret, y->ret);
                        for (int q = 0; q < 12; q++) if (x->a[q] != y->a[q]) printf(" a%d %x/%x", q, x->a[q], y->a[q]);
                        for (int q = 0; q < 12; q++) if (memcmp(x->d[q], y->d[q], 64)) printf(" d%d", q);
                        for (int q = 0; q < 0x41; q++) if (x->frame[q] != y->frame[q]) { printf(" frame+0x%x %08x/%08x", 0x10 + 4 * q, x->frame[q], y->frame[q]); }
                        printf("\n");
                    }
                    bad = 1;
                    break;
                }
            if (memcmp(res_out[0], res_out[1], sizeof outbuf)) { if (fx_fails < 20) printf("  out differs\n"); bad = 1; }
            if (memcmp(res_pts[0], res_pts[1], sizeof s_pts)) { if (fx_fails < 20) printf("  pts differ\n"); bad = 1; }
            if (memcmp(res_dat[0], res_dat[1], 12)) { if (fx_fails < 20) printf("  DAT_008ca320 differs\n"); bad = 1; }
            if (bad) fx_fail("case", i);
        }
        /* coverage counters */
        for (int k = 0; k < nlg[0]; k++) if (lg[0][k].tag == 9) { nhit++; break; }
        for (int k = 0; k + 2 < nlg[0]; k++)
            if (lg[0][k].tag == 13 && !lg[0][k].ret && lg[0][k + 1].tag == 10 && lg[0][k + 1].ret && lg[0][k + 2].tag == 10 && lg[0][k + 2].ret) { nboth++; break; }
        for (int k = 0, c13 = 0; k < nlg[0]; k++)
            if (lg[0][k].tag == 13 && ++c13 == 2) { nwalk++; break; }
        for (int k = 0; k < nlg[0]; k++)
            if (lg[0][k].tag == 13 && lg[0][k].ret && k + 1 < nlg[0] && lg[0][k + 1].tag == 12) { nfinal++; break; }
        for (int k = 0; k < nlg[0]; k++)
            if (lg[0][k].tag == 10 && lg[0][k].d[1][15] == 0xdeadbeef) { ngarbage_seen++; break; }
    }
    printf("wav_test: %ld null-actor cases, %ld reached the detour, %ld used an out-of-frame corner pointer\n", nnull, nhit, ngarbage_seen);
    printf("wav_test: %ld chose between two reachable corners by distance, %ld walked around the box, %ld appended a final path\n", nboth, nwalk, nfinal);
    printf("wav_test: calls per case:");
    for (int k = 0; k < 64; k++) if (hist[k]) printf(" %d:%ld", k, hist[k]);
    printf("\nwav_test: %ld cases, %ld differences\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
