/* Differential test of build/overrides_asm_o2_chore.c (CHORE.DLL costume loader: Cos_LoadEntry, FUN_100041e0,
 * FUN_10004390, FUN_100047f0, FUN_10004970) against the original machine code.  Each case generates a random text
 * costume (valid, or with a damaged line, missing lines, unknown types, comments, duplicate tracks) and loads it with
 * the original Cos_LoadEntry (which calls the original section readers) and with the C version, from the same start
 * state.  The compiled helpers of the build (line reader FUN_10004bb0, sscanf FUN_10005810, string functions) come from
 * costume.o; the service table (fopen / fgets / fclose / alloc / realloc / free / assert), CosUtil_* and the costume
 * helpers FUN_10004320 / 10004140 / 10004770 / 10004170 / 100010d0 are recorders with scripted results.  Compared: the
 * return value, the whole .data section, the costume, the allocation arena and the call log.
 * Build: PROG=CHORE.DLL DEF=GRIM_CHORE OVERRIDES=build/overrides_asm_o2_chore.c \
 *   EXTRA_OBJ="build/obj/CHORE.DLL/costume.o build/obj/CHORE.DLL/crt.o" build/difftest/asm_s5/build.sh \
 *   build/difftest/asm_s5/chore_test.c build/difftest/asm_s5/out/chore_test.exe Cos_LoadEntry FUN_100041e0 FUN_10004390 FUN_100047f0 FUN_10004970 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "fx.h"

extern int orig_Cos_LoadEntry(char *, int), Cos_LoadEntry(char *, int);
extern unsigned char sect_data_[] __asm__("_sect_data");
#define CD(va) (sect_data_ + ((va) - 0x10010000))
#define CU32(va) (*(unsigned *)CD(va))
static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }

enum { T_FOPEN = 1, T_FGETS, T_FCLOSE, T_ALLOC, T_REALLOC, T_FREE, T_ASSERT, T_PTR, T_ADDCOMP, T_SETLEN, T_4320, T_4140, T_4770, T_4170, T_10D0, T_LAST };
static void *th[T_LAST];
#define CALLN(t, T, ...) ((int (*)T)th[t])(__VA_ARGS__)

static struct {
    unsigned char arena[0x20000];
    unsigned used;
    unsigned char costume[0x40];
    unsigned char comps[16][0x40];      /* costume +0x2c */
    int tagtypes[4][0x17];              /* PTR_100143c0 */
    int map[64];                        /* DAT_100143d0 */
    int line;
} st;
static char text[64][160];
static int nlines;
static unsigned script;

static int eff(int tag, unsigned *a)
{
    unsigned h;
    switch (tag) {
    case T_FGETS:
        if (st.line >= nlines) return 0;
        { unsigned n = a[2]; char *d = (char *)a[1]; strncpy(d, text[st.line], n); d[n] = 0; st.line++; return (int)a[1]; }
    case T_ALLOC: case T_REALLOC: {
        unsigned n = tag == T_ALLOC ? a[0] : a[1], p;
        if (tag == T_ALLOC && (a[2] == 0xbdf || a[2] == 0xc7e) && (script + a[2]) % 9 == 0) return 0;    /* the component or chore array allocation fails now and then (a failure of the others crashes the original) */
        p = (st.used + 15) & ~15u;
        if (p + n > sizeof st.arena) return 0;
        st.used = p + n;
        if (tag == T_REALLOC && a[0]) memcpy(st.arena + p, (void *)a[0], n < 64 * 4 ? n : 64 * 4);
        return (int)(uintptr_t)(st.arena + p);
    }
    case T_PTR: return (int)(uintptr_t)st.costume;
    case T_4320: return (int)((a[0] * 7 + a[2] + script) % 4);
    case T_4770: h = a[3] ? *(unsigned *)(a[3] + 0x28) : 0; return ((h + script) % 5 == 0) ? (int)(h % 4) : -1;
    case T_4170: h = a[3] ? *(unsigned *)(a[3] + 0x28) : 0; return ((h + script) % 23 == 0) ? -1 : (int)((h + a[1]) % 4);
    case T_ADDCOMP: return ((a[1] + script) % 31) != 0;
    }
    return -12345678;
}

int FUN_10004320X(int a, int b, int c) __asm__("_FUN_10004320");
int FUN_10004320X(int a, int b, int c) { return CALLN(T_4320, (int, int, int), a, b, c); }
void FUN_10004140X(int a) __asm__("_FUN_10004140");
void FUN_10004140X(int a) { CALLN(T_4140, (int), a); }
int FUN_10004770X(int a, int b, int c, int d, int e) __asm__("_FUN_10004770");
int FUN_10004770X(int a, int b, int c, int d, int e) { return CALLN(T_4770, (int, int, int, int, int), a, b, c, d, e); }
int FUN_10004170X(int a, int b, int c, int d) __asm__("_FUN_10004170");
int FUN_10004170X(int a, int b, int c, int d) { return CALLN(T_4170, (int, int, int, int), a, b, c, d); }
void FUN_100010d0X(int a) __asm__("_FUN_100010d0");
void FUN_100010d0X(int a) { CALLN(T_10D0, (int), a); }
int PtrX(int a) __asm__("_CosUtil_PtrFromHandle");
int PtrX(int a) { return CALLN(T_PTR, (int), a); }
int AddCompX(int a, int b, int c, int d, int e) __asm__("_CosUtil_AddComponent");
int AddCompX(int a, int b, int c, int d, int e) { return CALLN(T_ADDCOMP, (int, int, int, int, int), a, b, c, d, e); }
int SetLenX(int a, int b, int c) __asm__("_CosUtil_SetChoreLength");
int SetLenX(int a, int b, int c) { return CALLN(T_SETLEN, (int, int, int), a, b, c); }

static void add(const char *fmt, ...)
{
    va_list ap;
    if (nlines >= 64) return;
    va_start(ap, fmt); _vsnprintf(text[nlines], 159, fmt, ap); va_end(ap);
    text[nlines][159] = 0;
    nlines++;
    if (R(12) == 0 && nlines < 64) strcpy(text[nlines++], R(2) ? "# comment\n" : "\n");
}

static void gen(void)
{
    int ntags = R(6), ncomp = R(6), nch = R(4), bad = R(3) == 0 ? (int)R(40) : -1;
    static const char *types[5] = {"fs", "int", "float", "FS", "bogus"};
    int chtracks[4];
    nlines = 0;
    add(R(10) ? "costume v0.1\n" : "costume x\n");
    add(R(30) ? "section tags\n" : "section tag\n");
    add("numtags %d\n", ntags);
    for (int i = 0; i < ntags; i++) add("%d '%c%c%c%c' %s tag%d\n", i, 'A' + R(26), 'A' + R(26), 'A' + R(26), 'A' + R(26), types[R(10) ? R(3) : 3 + R(2)], i);
    add(R(30) ? "section components\n" : "section comps\n");
    add("numcomponents %d\n", ncomp);
    for (int i = 0; i < ncomp; i++) add("%d %d %d %d comp%d.3do\n", i, R(ntags + 1), (int)R(100), i == 0 || R(3) == 0 ? -1 : (int)R(i), i);
    add(R(30) ? "section chores\n" : "section chore\n");
    add("numchores %d\n", nch);
    for (int i = 0; i < nch; i++) { chtracks[i] = R(4); add("%d %d %d chore%d\n", i, (int)R(5000), chtracks[i], i); }
    add(R(30) ? "section keys\n" : "section key\n");
    for (int i = 0; i < nch; i++) {
        add("chore %d\n", R(8) ? i : (int)R(nch));
        for (int t = 0; t < chtracks[i]; t++) {
            int nk = R(4);
            add("%d %d\n", R(ncomp + 1), nk);
            for (int k = 0; k < nk; k++) add(R(2) ? "%d %d\n" : "%d %d.5\n", k * 100 + (int)R(100), (int)R(1000) - 500);
        }
    }
    if (bad >= 0 && bad < nlines) {
        if (R(2)) nlines = bad;                       /* file ends early */
        else strcpy(text[bad], "x\n");   /* damaged line (a line that still parses but shifts the rest crashes the original) */
    }
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 10000, i;
    static void *svc[0x20];
    int nargs[T_LAST] = {0, 2, 3, 1, 3, 4, 1, 3, 1, 5, 3, 3, 1, 5, 4, 1};
    unsigned datalen = 0x5afc;
    for (int t = 1; t < T_LAST; t++) { th[t] = fx_thunk(t, nargs[t], 0); fx_effect(t, eff); }
    fx_strmask(T_FOPEN, 3); fx_strmask(T_ALLOC, 2); fx_strmask(T_REALLOC, 4); fx_strmask(T_ASSERT, 3);
    fx_ignmask(T_FGETS, 2); fx_strmask(T_4320, 2);
    svc[0x18 / 4] = th[T_ASSERT]; svc[0x20 / 4] = th[T_ALLOC]; svc[0x24 / 4] = th[T_FREE]; svc[0x28 / 4] = th[T_REALLOC];
    svc[0x30 / 4] = th[T_FOPEN]; svc[0x34 / 4] = th[T_FCLOSE]; svc[0x3c / 4] = th[T_FGETS];
    fx_region(sect_data_, datalen);
    fx_region(&st, sizeof st);
    for (i = 0; i < n; i++) {
        int ret[2];
        static char name[80];
        int handle = 0x100 + R(4);
        gen();
        script = (unsigned)fx_rnd();
        memset(&st, 0, sizeof st);
        for (int k = 0; k < 16; k++) for (int j = 0; j < 16; j++) ((unsigned *)st.comps[k])[j] = R(4);
        for (int k = 0; k < 4; k++) { st.tagtypes[k][0] = (int)fx_rnd(); st.tagtypes[k][1] = R(3); }
        for (int k = 0; k < 64; k++) st.map[k] = R(4);
        *(void **)(st.costume + 0x2c) = st.comps;
        for (int k = 0; k < 64; k++) CU32(0x10014210 + k * 4) = R(4);
        CU32(0x100143a8) = (unsigned)(uintptr_t)svc;
        CU32(0x100143c0) = (unsigned)(uintptr_t)st.tagtypes;
        CU32(0x100143d0) = (unsigned)(uintptr_t)st.map;
        CU32(0x100143d4) = R(2) ? 64 : R(4);
        if (R(20) == 0) { int L = 30 + R(10); memset(name, 'c', L); name[L] = 0; }
        else sprintf(name, R(2) ? "data\\costumes\\manny_%d.cos" : "manny_%d.cos", (int)R(100));
        fx_ret(T_FOPEN, R(30) ? 0x4444 : 0);
        if (getenv("TRACE")) { printf("case %ld\n", i); for (int k = 0; k < nlines; k++) printf("  %s", text[k]); fflush(stdout); }
        fx_save();
        fx_reset();
        ret[0] = orig_Cos_LoadEntry(name, handle);
        fx_snap_a(); fx_restore(); fx_reset();
        if (getenv("TRACE")) { printf("orig done %d, name %s\n", ret[0], name); fflush(stdout); }
        ret[1] = Cos_LoadEntry(name, handle);
        if (ret[0] != ret[1]) fx_fail("ret", i);
        if (fx_cmp_a()) fx_fail("mem", i);
        if (fx_cmp_log()) fx_fail("log", i);
        if (ret[0]) fx_seed += 0;
        fx_cases++;
        if (i < 3 || ret[0]) { static int shown; if (shown++ < 3) printf("case %ld ret %d lines %d log %d\n", i, ret[0], nlines, fx_nlog); }
    }
    printf("chore_test: %ld cases, %ld differences\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
