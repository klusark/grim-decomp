/* Differential test (agent s2): the iMUSE fade engine of the rebuilt IMUSE.DLL against the original machine code.
 * FdFadeParam (0x10003b40, the body of ImFadeParam), FdStopFade (0x10003c70) and FdIntHandler
 * (0x10003cb0, one step per heartbeat) as compiled in build/obj/IMUSE.DLL/imuse.o (the object linked into imuse.dll),
 * against orig_* sliced from the all-assembly IMUSE.DLL (git show 68b8b5b^:src/IMUSE.DLL/asm_funcs.s).  Both work on
 * the same fade table (16 slots of 10 words at 0x1002d860, flag 0x1002d858) in the original data image (data_s.o).
 * Each case: a random fade table and parameter model, then a random sequence of ImFadeParam / clear / heartbeat steps
 * (durations 0..300 and odd values, targets around the current value and extremes, the four fade parameters and invalid
 * ones), run once with each version from the same state; compared: every return value, every ImGetParam / ImSetParam /
 * ImStopSound call (in order, with the heartbeat number) and the fade table + flag after each step.
 * usage: fade_test.exe [cases] [seed] */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned g_dwFadesOn;
extern unsigned g_dwFades[160];
int FdFadeParam(int, int, unsigned, int);
void FdStopFade(int, int);
unsigned FdIntHandler(void);
int orig_FdFadeParam(int, int, unsigned, int);
void orig_FdStopFade(int, int);
unsigned orig_FdIntHandler(void);

static unsigned long long rs;
static unsigned rnd(void) { rs ^= rs << 13; rs ^= rs >> 7; rs ^= rs << 17; return (unsigned)(rs >> 11); }

#define NLOG 8192
typedef struct { int kind, a, b, c, step; } Ev;
static Ev logb[NLOG];
static int nlog, step_no;
static unsigned model[8][16];   /* parameter values per sound (low 3 bits) and param (>> 8) */

static void ev(int k, int a, int b, int c) { if (nlog < NLOG) { Ev e = {k, a, b, c, step_no}; logb[nlog++] = e; } }
unsigned ImGetParam(int s, int p) { unsigned v = model[s & 7][(p >> 8) & 15]; ev(1, s, p, (int)v); return v; }
int ImSetParam(int s, int p, unsigned v) { model[s & 7][(p >> 8) & 15] = v; ev(2, s, p, (int)v); return 0; }
int ImStopSound(int s) { ev(3, s, 0, 0); return 0; }

typedef struct { unsigned tab[160], flag; unsigned model[8][16]; } State;
static void save(State *s) { memcpy(s->tab, g_dwFades, sizeof s->tab); s->flag = g_dwFadesOn; memcpy(s->model, model, sizeof model); }
static void load(const State *s) { memcpy(g_dwFades, s->tab, sizeof s->tab); g_dwFadesOn = s->flag; memcpy(model, s->model, sizeof model); }

static const int params[] = {0x500, 0x600, 0x700, 0x800, 0x600, 0x600, 0x400, 0x100, 0, -1};
static unsigned rval(void)
{
    switch (rnd() % 8) {
    case 0: return 0;
    case 1: return 0x7f;
    case 2: return rnd() % 128;
    case 3: return rnd() % 300;
    case 4: return 0x80000000u + rnd() % 3 - 1;
    case 5: return (unsigned)-(int)(rnd() % 200);
    default: return rnd();
    }
}
static int rdur(void)
{
    switch (rnd() % 8) {
    case 0: return 0;
    case 1: return (int)(rnd() % 3);          /* 5/6 rounds to 0 */
    case 2: return (int)(rnd() % 7);
    case 3: return 0x78;
    case 4: return 0x3c;
    case 5: return -(int)(rnd() % 5) - 1;     /* rejected */
    case 6: return (int)(rnd() % 0x10000000); /* long; also beyond 0x19999999 * 5 wrap below */
    default: return (int)(rnd() % 301);
    }
}

typedef struct { int op, a, b, c, d; } Op;
#define NOPS 64
static Op ops[NOPS];
static int nops;
static unsigned res[NOPS], tabs[NOPS][161];

static void run(int orig)
{
    int i;
    nlog = 0;
    for (i = 0; i < nops; i++) {
        Op *o = &ops[i];
        step_no = i;
        if (o->op == 0)
            res[i] = (unsigned)(orig ? orig_FdFadeParam(o->a, o->b, (unsigned)o->c, o->d) : FdFadeParam(o->a, o->b, (unsigned)o->c, o->d));
        else if (o->op == 1) {
            if (orig) orig_FdStopFade(o->a, o->b); else FdStopFade(o->a, o->b);
            res[i] = 0;
        } else
            res[i] = orig ? orig_FdIntHandler() : FdIntHandler();
        memcpy(tabs[i], g_dwFades, 640);
        tabs[i][160] = g_dwFadesOn;
    }
}

int main(int argc, char **argv)
{
    long cases = argc > 1 ? atol(argv[1]) : 100000, c, diffs = 0, nfade = 0, nstop = 0, nset = 0, nhb = 0;
    static Ev lo[NLOG];
    static unsigned ro[NOPS], to[NOPS][161];
    int nlo, i, j;
    State st;
    rs = 0x9e3779b97f4a7c15ull * (unsigned)(argc > 2 ? atoi(argv[2]) : 1) + 1;
    for (c = 0; c < cases; c++) {
        /* random start: a few active slots with random fields, the rest free or stale */
        for (i = 0; i < 16; i++) {
            unsigned *s = &g_dwFades[i * 10];
            for (j = 0; j < 10; j++)
                s[j] = rnd() % 4 == 0 ? rnd() : rnd() % 200;
            s[0] = rnd() % 3 == 0;
            s[1] = 1 + rnd() % 4;
            s[2] = params[rnd() % 4];
            s[4] = rnd() % 4 == 0 ? rnd() : rnd() % 120;
            s[5] = rnd() % 4 == 0 ? rnd() : 1 + rnd() % 120;
            s[9] = rnd() % 2 ? 1 : (unsigned)-1;
        }
        g_dwFadesOn = rnd() % 4 != 0;
        for (i = 0; i < 8; i++)
            for (j = 0; j < 16; j++)
                model[i][j] = rval();
        nops = 1 + rnd() % NOPS;
        for (i = 0; i < nops; i++) {
            Op *o = &ops[i];
            unsigned r = rnd() % 10;
            o->op = r < 3 ? 0 : r < 4 ? 1 : 2;
            o->a = rnd() % 16 == 0 ? 0 : (int)(1 + rnd() % 4);
            o->b = rnd() % 8 == 0 ? params[rnd() % 10] : params[rnd() % 4];
            if (o->op == 1 && rnd() % 3 == 0)
                o->b = -1;
            o->c = (int)rval();
            o->d = rdur();
            /* idiv traps alike in both for INT_MIN / -1 (duration 858993458: 5 * d wraps to -6, / 6 = -1); not generated */
            if (o->op == 0 && (int)((unsigned)o->d * 5u) / 6 == -1)
                o->d = 0x78;
        }
        save(&st);
        run(1);
        nlo = nlog;
        memcpy(lo, logb, sizeof(Ev) * nlog);
        memcpy(ro, res, sizeof ro);
        memcpy(to, tabs, sizeof to);
        load(&st);
        run(0);
        for (i = 0; i < nops; i++) {
            if (ops[i].op == 0) nfade++;
            if (ops[i].op == 2) nhb++;
        }
        for (i = 0; i < nlo; i++) {
            if (lo[i].kind == 3) nstop++;
            if (lo[i].kind == 2) nset++;
        }
        if (nlo != nlog || memcmp(lo, logb, sizeof(Ev) * nlog) || memcmp(ro, res, sizeof(unsigned) * nops) ||
            memcmp(to, tabs, sizeof(to[0]) * nops)) {
            if (diffs++ < 5) {
                printf("case %ld differs: log %d / %d\n", c, nlo, nlog);
                for (i = 0; i < nops; i++)
                    if (ro[i] != res[i] || memcmp(to[i], tabs[i], sizeof to[i]))
                        { printf("  first step %d: op %d (%x %x %x %d) ret %x / %x\n", i, ops[i].op, ops[i].a, ops[i].b, ops[i].c, ops[i].d, ro[i], res[i]); break; }
                for (i = 0; i < nlo && i < nlog; i++)
                    if (memcmp(&lo[i], &logb[i], sizeof(Ev)))
                        { printf("  first call %d: %d(%x,%x,%x)@%d / %d(%x,%x,%x)@%d\n", i, lo[i].kind, lo[i].a, lo[i].b, lo[i].c, lo[i].step,
                                 logb[i].kind, logb[i].a, logb[i].b, logb[i].c, logb[i].step); break; }
            }
        }
    }
    printf("cases %ld: %ld ImFadeParam, %ld heartbeats, %ld ImSetParam and %ld ImStopSound calls from the fades (original)\n",
           cases, nfade, nhb, nset, nstop);
    printf("%ld differences\n", diffs);
    return diffs != 0;
}
