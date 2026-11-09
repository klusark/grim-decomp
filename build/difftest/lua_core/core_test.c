/* Differential test of build/overrides_lua_core.c against the original LUA.DLL machine code (orig_*, sliced by build.sh).
 * Build and run: build/difftest/lua_core/build.sh [cases]
 *
 * Each case builds a random set of lua_State-like records in a fixed pool (a task list linked through the stand-in
 * lstate__8bf0 = "next task", call chains linked through +0x0c, paused / marked flags, stack fields, task hook on or
 * off), saves a snapshot, runs the original, saves the result, restores the snapshot, runs the C, and compares: the
 * return value, the call log of every stand-in callee (name and arguments as dwords, in order), the global L, the
 * services table, and the whole pool.  The stand-ins take their decisions from a per-case stream consumed in call order,
 * so both versions see the same answers as long as they call the same things in the same order.  Errors are raised
 * like lua_error does: msvcrt longjmp(*(jmp_buf *)L->errorJmp, 1), also from nested protected calls. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern int *PTR_1002bf6c;           /* the global L (data image) */
extern void *lua_taskhook;
extern int *DAT_1002beb8;            /* the services table pointer; +0x18 is the assert function */
extern void __cdecl longjmp(void *, int) __attribute__((noreturn));

typedef int updatetasks_fn(int);
typedef int protectedrun_fn(void *);
typedef int protectedparser_fn(int *, int);
extern updatetasks_fn orig_lua_updatetasks, lua_updatetasks;
extern protectedrun_fn orig_luaD_protectedrun, luaD_protectedrun;
extern protectedparser_fn orig_luaD_protectedparser, luaD_protectedparser;
static protectedrun_fn *cur_prun;
static protectedparser_fn *cur_ppar;

/* ---- the pool: states (0x40 dwords, next task at [0x3c]) and call entries (8 dwords) ---- */
#define NSTATE 8
#define NENT 64
static struct pool { int st[NSTATE][0x40]; int ent[NENT][8]; int services[16]; int stackmem[64]; } P, snap, res_orig;
static int nent_used;

/* ---- per-case decision stream and call log ---- */
static uint64_t seed, sstream;
static uint32_t rnd(void) { seed ^= seed << 13; seed ^= seed >> 7; seed ^= seed << 17; return (uint32_t)(seed >> 11); }
static uint32_t R(uint32_t n) { return n ? rnd() % n : 0; }
static uint32_t snext(void) { sstream ^= sstream << 13; sstream ^= sstream >> 7; sstream ^= sstream << 17; return (uint32_t)(sstream >> 11); }
static uint32_t S(uint32_t n) { return n ? snext() % n : 0; }
static uint32_t lg[4096], lg_orig[4096]; static int nlg, nlg_orig, overflow;
static void L(uint32_t v) { if (nlg < 4096) lg[nlg++] = v; else overflow = 1; }
static int ncalls, depth, entcur;

static int *new_entry(void)
{
    int *e;
    if (entcur >= NENT) entcur = nent_used;    /* reuse the scratch entries (contents compared anyway) */
    e = P.ent[entcur++];
    e[0] = (int)snext(); e[4] = (int)S(1000); e[5] = (int)S(1000);
    return e;
}
static void raise_error(void) { L(0xEEEE); longjmp((void *)PTR_1002bf6c[0xd], 1); }

int __fastcall lstate__8bf0(int p) { L(0x8bf0); L(p); return p ? ((int *)p)[0x3c] : 0; }
/* lstate__8c00 (the task's clean-up) unlinks it from the task list here, so that the scheduler terminates */
void __fastcall lstate__8c00(int *p)
{
    int i;
    L(0x8c00); L((uint32_t)p);
    for (i = 0; i < NSTATE; i++)
        if (P.st[i][0x3c] == (int)p) P.st[i][0x3c] = p[0x3c];
    p[0x3f] = 0xDEAD;
}
/* the callees change what the real ones may change, so that the order of reads around them is tested */
void __fastcall lvm__de20(int p) { L(0xde20); L(p); if (S(4) == 0) ((int *)p)[3] = 0; }
void __cdecl lvm__dd90(int p) { L(0xdd90); L(p); ((int *)p)[3] = 0x0BAD0000; }   /* freed */
void __cdecl luaM_free(void *p) { L(0x73d0); L((uint32_t)p); }
void __cdecl ldo__40c0(int a, int b) { L(0x40c0); L(a); L(b); }
void __cdecl ldo__4160(int a) { L(0x4160); L(a); }
void __cdecl luaD_openstack(int n)
{
    L(0x3f40); L(n);
    if (S(3) == 0) { PTR_1002bf6c[10] = (int)S(8); PTR_1002bf6c[7] = (int)snext(); }
}
void __cdecl luaA_setnormalized(int *a, int *b) { L(0x13c0); L((uint32_t)a); L((uint32_t)b); }
void __cdecl luaD_adjusttop(int n) { L(0x3ee0); L(n); }
void __cdecl luaV_closure(int n) { L(0xd6d0); L(n); }
static void __cdecl assert_fn(char *a, char *b, int line) { L(0xA55E); L((uint32_t)a); L((uint32_t)b); L(line); }

/* a call of Lua code: may change the state, nest a protected call, yield (non-zero), finish (0) or raise an error */
static int lua_work(void)
{
    int *gl = PTR_1002bf6c, k;
    ncalls++;
    for (k = S(3); k > 0; k--) {                  /* push call entries */
        int *e = new_entry();
        e[3] = gl[0]; gl[0] = (int)e;
    }
    if (S(4) == 0) { gl[10] = (int)S(20); gl[11] = (int)snext(); gl[12] = (int)S(9); gl[7] = (int)snext(); }
    if (depth < 3 && S(5) == 0) {                /* nested protected call / parse */
        int r;
        depth++;
        r = S(2) ? cur_prun((void *)(int)S(300)) : cur_ppar((int *)(int)snext(), (int)S(2));
        depth--;
        L(0x9e57); L(r); L(gl[2]); L(gl[0xd] != 0);
    }
    if (S(6) == 0) raise_error();
    return ncalls > 60 ? 0 : (S(3) == 0 ? 0 : (int)S(5));
}
int __cdecl luaD_call(int a, int b) { L(0x4180); L(a); L(b); return lua_work(); }
void __cdecl luaD_callinc(void *n) { L(0x47c0); L((uint32_t)n); lua_work(); }
int __cdecl luaU_undump1(int *z) { L(0xcea0); L((uint32_t)z); if (S(5) == 0) raise_error(); return S(4) ? (int)snext() : 0; }
int __cdecl luaY_parser(int z) { L(0xa900); L(z); if (S(5) == 0) raise_error(); return S(4) ? (int)snext() : 0; }

/* ---- case set-up ---- */
static void make_case(int which)
{
    int i, n = 1 + R(NSTATE - 1), k;
    memset(&P, 0, sizeof P);
    for (i = 0; i < 16; i++) P.services[i] = (int)rnd();
    P.services[6] = (int)assert_fn;
    DAT_1002beb8 = P.services;
    lua_taskhook = R(2) ? (void *)0x1234 : 0;
    nent_used = 0;
    for (i = 0; i < NSTATE; i++) {
        int *s = P.st[i];
        for (k = 0; k < 0x3c; k++) s[k] = (int)(R(4) ? R(64) : rnd());
        s[0] = 0;
        if (R(2)) {                                /* a call chain (the root) */
            int m = 1 + R(3), *prev = 0;
            for (k = 0; k < m && nent_used < NENT / 2; k++) {
                int *e = P.ent[nent_used++], j;
                for (j = 0; j < 8; j++) e[j] = (int)rnd();
                e[3] = (int)prev; prev = e;
            }
            s[0] = (int)prev;
        }
        s[4] = R(3) == 0; s[5] = R(4) == 0;        /* paused / marked */
        s[8] = (int)P.stackmem; s[10] = (int)R(8); s[7] = s[8] + 8 * (int)(s[10] + R(8)) * (R(9) ? 1 : -1);
        s[0xd] = (int)rnd();                       /* old errorJmp */
        s[2] = (int)R(5);
        s[0x30] = 0x100 + i;
        s[0x3c] = 0;
    }
    for (i = 0; i + 1 < n; i++) P.st[i][0x3c] = (int)P.st[i + 1];   /* task list: st[0] -> ... -> st[n-1] */
    PTR_1002bf6c = P.st[which == 0 ? 0 : R(n)];
}
static void no_stopped(void)   /* lua_updatetasks(1) loops until no task is left: a task flagged at +0x14 would never end */
{
    int i;
    for (i = 0; i < NSTATE; i++) P.st[i][5] = 0;
}

static int run(int which, int arg, int use_orig, uint64_t ss)
{
    int r;
    sstream = ss | 1; nlg = 0; overflow = 0; ncalls = 0; depth = 0; entcur = nent_used;
    cur_prun = use_orig ? orig_luaD_protectedrun : luaD_protectedrun;
    cur_ppar = use_orig ? orig_luaD_protectedparser : luaD_protectedparser;
    if (which == 0) r = (use_orig ? orig_lua_updatetasks : lua_updatetasks)(arg);
    else if (which == 1) r = cur_prun((void *)arg);
    else r = cur_ppar((int *)P.ent, arg);
    L(0xF1A1); L((uint32_t)PTR_1002bf6c); L((uint32_t)DAT_1002beb8);
    /* lua_updatetasks leaves errorJmp pointing at its own (now dead) jmp_buf, at a frame offset that differs between
     * the original and gcc's frame: a stack address is replaced by a marker before the compare */
    { char here; int i;
      for (i = 0; i < NSTATE; i++) {
          uint32_t v = (uint32_t)P.st[i][0xd];
          if (v < (uint32_t)&here && v > (uint32_t)&here - 0x10000) P.st[i][0xd] = 0x57AC0000;
      } }
    return r;
}

int main(int argc, char **argv)
{
    long cases = argc > 1 ? atol(argv[1]) : 100000, c, bad = 0, ovf = 0;
    long cnt[3] = {0}, errs = 0;
    seed = 0x9E3779B97F4A7C15ull;
    for (c = 0; c < cases; c++) {
        int which = (int)(c % 3), arg, r1, r2;
        uint64_t ss = ((uint64_t)rnd() << 32) | rnd();
        int *gl0;
        void *hook;
        make_case(which);
        arg = which == 0 ? (int)R(2) : which == 1 ? (int)R(300) : (int)R(2);
        if (which == 0 && arg) no_stopped();
        snap = P; gl0 = PTR_1002bf6c; hook = lua_taskhook;
        r1 = run(which, arg, 1, ss);
        res_orig = P; memcpy(lg_orig, lg, sizeof lg); nlg_orig = nlg;
        { int *glo = PTR_1002bf6c; int o = overflow;
          P = snap; PTR_1002bf6c = gl0; lua_taskhook = hook; DAT_1002beb8 = P.services;
          r2 = run(which, arg, 0, ss);
          ovf += o || overflow;
          if (r1 != r2 || nlg != nlg_orig || memcmp(lg, lg_orig, nlg * 4) || memcmp(&P, &res_orig, sizeof P) || glo != PTR_1002bf6c) {
              int i;
              if (bad++ < 5) {
                  printf("case %ld (%s, arg %d): ret %d vs %d, log %d vs %d entries\n", c,
                         which == 0 ? "updatetasks" : which == 1 ? "protectedrun" : "protectedparser", arg, r1, r2, nlg_orig, nlg);
                  for (i = 0; i < nlg && i < nlg_orig; i++)
                      if (lg[i] != lg_orig[i]) { printf("  first log difference at %d: %08x vs %08x\n", i, lg_orig[i], lg[i]); break; }
                  if (memcmp(&P, &res_orig, sizeof P)) printf("  pool differs\n");
              }
          }
        }
        cnt[which]++;
        { int i; for (i = 0; i < nlg; i++) if (lg[i] == 0xEEEE) { errs++; break; } }
    }
    printf("%ld cases (updatetasks %ld, protectedrun %ld, protectedparser %ld), %ld with an error raised, %ld log overflows: "
           "%ld differences\n", cases, cnt[0], cnt[1], cnt[2], errs, ovf, bad);
    return bad != 0;
}
