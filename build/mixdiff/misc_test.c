/* Differential test of the glue code of build/overrides_mixer_misc.c against the original machine code: Smush_GetLengthMs, the
 * light editor (text field reader, keyboard hook), LecShare_Resolve, AnimPlay (create, destroy, update, reset, open file),
 * the zlib glue (gz_open, gz_putLong, Zfile_Close) and the StdFile helpers.  Everything the functions call (services of the
 * module manager, imports, zlib, the CRT) is a recorder that logs its arguments and returns scripted values.
 * Build: ORIG_SED='s/_strncpy/_test_strncpy/g; s/_malloc/_test_malloc/g; s/__errno/__test_errno/g' EXTRA_CFLAGS="-Dstrncpy=test_strncpy -Dmalloc=test_malloc -D_errno=test_errno" OVERRIDES=build/overrides_mixer_misc.c build/mixdiff/build.sh ...
 * ONLY=<n> selects a group: 0 length, 1 ReadControl, 2 keyboard hook, 3 LecShare, 4 AnimPlay, 5 gz_open, 6 small zlib/StdFile. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

/* the original code (orig_<name>) and the C version */
extern int orig_Smush_SetFile(char *), Smush_GetLengthMs(char *);
extern void orig_LightEd_ReadControl(int, int), LightEd_ReadControl(int, int);
extern int __stdcall orig_kb(int, unsigned, unsigned) __asm__("_orig_FUN_004bffb0@12");
extern int __stdcall new_kb(int, unsigned, unsigned) __asm__("_LightEd_KeyboardProc@12");
extern void *orig_LecShare_Resolve(char *, char *), *LecShare_Resolve(char *, char *);
extern int orig_FUN_004c23c0(void **, char *, int, int, int, unsigned), AnimPlay_Create(void **, char *, int, int, int, unsigned);
extern void orig_FUN_004c2690(void **), AnimPlay_Destroy(void **);
extern int orig_FUN_004c27a0(void *, int, int, int, int, int, int, int, int, int), AnimPlay_Update(void *, int, int, int, int, int, int, int, int, int);
extern int orig_FUN_004c36b0(void *), AnimPlay_ResetState(void *);
extern int orig_FUN_004c3d30(void *, char *, unsigned, int, int, int), AnimPlay_OpenFile(void *, char *, unsigned, int, int, int);
extern void *orig_gz_open(char *, char *, int), *gz_open(char *, char *, int);
extern void orig_gz_putLong(void *, unsigned), gz_putLong(void *, unsigned);
extern void orig_FUN_004c5ab0(int *), Zfile_Close(int *);
extern int orig_FUN_004c5e30(void *), StdFile_Tell(void *);
extern int orig_FUN_004c5f50(void *), StdFile_IsEof(void *);

enum {
    T_OPEN = 1, T_CLOSE, T_RFH, T_GETTEXT, T_SENDMSG, T_POSCOMP, T_ANGLE, T_SETANGLES, T_MOVEMARKER, T_FOCUS, T_SETFLOAT, T_NEXTHOOK,
    T_WILD, T_MODLEN, T_STRNCPY, T_COUNT, T_SUBSCRIBE, T_FIND,
    T_AMEM_ALLOC, T_AMEM_FREE, T_DBG0, T_DBG3, T_DBG5, T_DBG7, T_STR_OPEN, T_STR_CLOSE, T_STR_FILE, T_STR_RESET, T_STR_BUF,
    T_TMR_ADD, T_TMR_REMOVE, T_TMR_PERIOD, T_LIP, T_FRAME, T_36F0, T_VOICE, T_3D90, T_DUMP,
    T_ZMALLOC, T_ZCRC, T_ZDEFL, T_ZINFL, T_ZDESTROY, T_ZHEADER, T_ZFDOPEN, T_ZOPEN, T_ZWRITE, T_ZTELL, T_ZFREE, T_GZCLOSE, T_ZPUT, T_SSIZE, T_STELL, T_SSEEK, T_LAST
};
static void *th[T_LAST + 1];
static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }

#define CALLN(t, T, ...) ((int (*)T)th[t])(__VA_ARGS__)

/* ---- symbols the code under test references ---- */
static unsigned char heap[0x8000];
static unsigned heap_used, heap_limit = sizeof heap;
static unsigned rfh_seed;
int Insane_ReadFrameHeader(int f, int buf)
{
    int i;
    for (i = 0; i < 0x420; i++) { rfh_seed = rfh_seed * 1664525u + 1013904223u; ((unsigned char *)buf)[i] = (unsigned char)(rfh_seed >> 24); }
    return CALLN(T_RFH, (int, int), f, 0);
}
float my_atof(unsigned char *s) __asm__("_atof");
float my_atof(unsigned char *s) { return (float)strtod((char *)s, 0); }
int Str_WildcardMatchX(char *a, char *b) __asm__("_Str_WildcardMatch");
int Str_WildcardMatchX(char *a, char *b) { return CALLN(T_WILD, (char *, char *), a, b); }
int Str_ModuleNameLengthX(char *a) __asm__("_Str_ModuleNameLength");
int Str_ModuleNameLengthX(char *a) { return CALLN(T_MODLEN, (char *), a); }
int strncpyX(char *d, char *s, int n) __asm__("_test_strncpy");
int strncpyX(char *d, char *s, int n)
{
    int i;
    CALLN(T_STRNCPY, (char *, char *, int), d, s, n);
    for (i = 0; i < n && s[i]; i++) d[i] = s[i];
    for (; i < n; i++) d[i] = 0;
    return (int)(intptr_t)d;
}
int LecShare_CountMatchingX(char *a) __asm__("_LecShare_CountMatching");
int LecShare_CountMatchingX(char *a) { return CALLN(T_COUNT, (char *), a); }
int LecShare_SubscribeX(char *a, int b) __asm__("_LecShare_Subscribe");
int LecShare_SubscribeX(char *a, int b) { return CALLN(T_SUBSCRIBE, (char *, int), a, b); }
int LecShare_FindEntryX(char *a) __asm__("_LecShare_FindEntry");
int LecShare_FindEntryX(char *a) { return CALLN(T_FIND, (char *), a); }
int LightEd_SetLightPosComponent(int a, short b, unsigned c) { return CALLN(T_POSCOMP, (int, int, unsigned), a, (int)b, c); }
int LightEd_SetLightAngle(int a, short b, unsigned c) { return CALLN(T_ANGLE, (int, int, unsigned), a, (int)b, c); }
int rdLight_SetAngles(void *a, float b, float c) { unsigned x, y; memcpy(&x, &b, 4); memcpy(&y, &c, 4); return CALLN(T_SETANGLES, (void *, unsigned, unsigned), a, x, y); }
int LightEd_MoveMarkerActor(void) { return CALLN(T_MOVEMARKER, (void)); }
int Win_IsFocusWithin(void *h) { return CALLN(T_FOCUS, (void *), h); }
int LightEd_SetDlgFloat(int a, int b, float c, int d) { unsigned x; memcpy(&x, &c, 4); return CALLN(T_SETFLOAT, (int, int, unsigned, int), a, b, x, d); }
void *imp_GetDlgItemTextA __asm__("__imp__GetDlgItemTextA@16");
void *imp_SendDlgItemMessageA __asm__("__imp__SendDlgItemMessageA@20");
void *imp_CallNextHookEx __asm__("__imp__CallNextHookEx@16");
__asm__(".text\n.globl _GetDlgItemTextA@16\n_GetDlgItemTextA@16:\n\tjmp *__imp__GetDlgItemTextA@16\n"
        ".globl _SendDlgItemMessageA@20\n_SendDlgItemMessageA@20:\n\tjmp *__imp__SendDlgItemMessageA@20\n"
        ".globl _CallNextHookEx@16\n_CallNextHookEx@16:\n\tjmp *__imp__CallNextHookEx@16\n");
int FUN_004c36f0(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k) { return CALLN(T_36F0, (int, int, int, int, int, int, int, int, int, int, int), a, b, c, d, e, f, g, h, i, j, k); }
int Sound_VoiceSampleCount(int v) { return CALLN(T_VOICE, (int), v); }
int FUN_004c3d90(int a, int b, int c) { return CALLN(T_3D90, (int, int, int), a, b, c); }
int Mem_DumpLog(void) { return CALLN(T_DUMP, (void)); }
int zlibVersion(int x) { return 0; }
void FUN_004c2a70(int a, int b) { }
void FUN_004c2a80(int a, int b) { }
int zmalloc(int n) __asm__("_test_malloc");
int zmalloc(int n) { return CALLN(T_ZMALLOC, (int), n); }
int zcrc(unsigned a, void *b, unsigned c) __asm__("_crc32");
int zcrc(unsigned a, void *b, unsigned c) { return CALLN(T_ZCRC, (unsigned, void *, unsigned), a, b, c); }
int zdefl(int a, int b, int c, int d, int e, int f, char *g, int h) __asm__("_deflateInit2_");
int zdefl(int a, int b, int c, int d, int e, int f, char *g, int h) { return CALLN(T_ZDEFL, (int, int, int, int, int, int, char *, int), a, b, c, d, e, f, g, h); }
int zinfl(int a, int b, char *c, int d) __asm__("_inflateInit2_");
int zinfl(int a, int b, char *c, int d) { return CALLN(T_ZINFL, (int, int, char *, int), a, b, c, d); }
int zdestroy(int a) __asm__("_gz_destroy");
int zdestroy(int a) { return CALLN(T_ZDESTROY, (int), a); }
void zheader(int *a) __asm__("_gz_check_header");
void zheader(int *a) { CALLN(T_ZHEADER, (int *), a); }
int zfdopen(unsigned a, char *b) __asm__("__fdopen");
int zfdopen(unsigned a, char *b) { return CALLN(T_ZFDOPEN, (unsigned, char *), a, b); }
static int errno_cell;
int *zerrno(void) __asm__("__test_errno");
int *zerrno(void) { return &errno_cell; }
int *zerrno2(void) __asm__("_test_errno");
int *zerrno2(void) { return &errno_cell; }
int gzclose_x(int a) __asm__("_gzclose");
int gzclose_x(int a) { return CALLN(T_GZCLOSE, (int), a); }
int FUN_004c5e90(void *f) { return CALLN(T_SSIZE, (void *), f); }
int StdFile_Size(void *f) { return CALLN(T_SSIZE, (void *), f); }

/* ---- shared state ---- */
static unsigned char wlog[64];
static unsigned wlog_n;
static unsigned char lightbuf[3][0x80];
static unsigned char animobj[0x80];
static void *animptr;
static unsigned char bufB[0x4000];
static unsigned char entryarea[64];
static const char *texts[] = { "12.5", "-3", "abc", "1e5", "", "999999999", "0.001", "360", "-180.5", "7", "  42", "3.99" };
static const char *names[] = { "gamma", "gamma.dll", "lua", "audio.vox", "x", "a=b", "" };
static const char *pats[] = { "gamma=gamma2", "lua=lua5", "x=y", "*", "=" };
static const char *repl[] = { "beta", "", "z", "newname.dll" };
static int svc_a[16], svc_b[16], svc_c[16], svc_d[16], svc_e[16], svc_f[16], svc_g[16];


static int gettext_effect(int tag, unsigned *a)
{
    const char *t = texts[(a[1] + (unsigned)strlen("x")) % (sizeof texts / sizeof *texts)];
    strcpy((char *)a[2], t);
    return (int)strlen(t);
}
static int dbg3_effect(int tag, unsigned *a)
{
    const char *f = (const char *)a[0];
    int cnt = 0, k;
    for (; *f; f++) if (*f == '%') { if (f[1] == '%') f++; else cnt++; }
    for (k = 1 + cnt; k < 10; k++) fx_log[fx_nlog].a[k] = 0;
    return -12345678;
}
static int write_effect(int tag, unsigned *a)
{
    unsigned n = a[2], i;
    for (i = 0; i < n && wlog_n < sizeof wlog; i++) wlog[wlog_n++] = ((unsigned char *)a[1])[i];
    return (int)n;
}
static int ref_effect(int tag, unsigned *a)
{
    /* open handle returns the scripted value; the handle is also stored through the first argument (stream open) */
    if (a[0] >= 0x1000 && (unsigned char *)a[0] >= animobj && (unsigned char *)a[0] < animobj + 0x80) *(unsigned *)a[0] = 0x7000 + (unsigned)tag;
    return -12345678;
}
static int zalloc_effect(int tag, unsigned *a)
{
    unsigned n = (a[0] + 15) & ~15u;
    if (heap_used + n > heap_limit) return 0;
    heap_used += n;
    return (int)(uintptr_t)(heap + heap_used - n);
}
static int transparent_next;
static int zheader_effect2(int tag, unsigned *a) { ((int *)a[0])[0x58 / 4] = transparent_next; return 0; }


int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000;
    int neg = argc > 2;
    int only = getenv("ONLY") ? atoi(getenv("ONLY")) : -1;
    long it;
    int i;
    int nargs[T_LAST + 1];
    int stdc[T_LAST + 1];

    setvbuf(stdout, 0, _IONBF, 0);
    for (i = 0; i <= T_LAST; i++) { nargs[i] = 0; stdc[i] = 0; }
    nargs[T_OPEN] = 2; nargs[T_CLOSE] = 1; nargs[T_RFH] = 2;
    nargs[T_GETTEXT] = 4; stdc[T_GETTEXT] = 1; nargs[T_SENDMSG] = 5; stdc[T_SENDMSG] = 1; nargs[T_NEXTHOOK] = 4; stdc[T_NEXTHOOK] = 1;
    nargs[T_POSCOMP] = 3; nargs[T_ANGLE] = 3; nargs[T_SETANGLES] = 3; nargs[T_MOVEMARKER] = 0; nargs[T_FOCUS] = 1; nargs[T_SETFLOAT] = 4;
    nargs[T_WILD] = 2; nargs[T_MODLEN] = 1; nargs[T_STRNCPY] = 3; nargs[T_COUNT] = 1; nargs[T_SUBSCRIBE] = 2; nargs[T_FIND] = 1;
    nargs[T_AMEM_ALLOC] = 3; nargs[T_AMEM_FREE] = 3; nargs[T_DBG0] = 2; nargs[T_DBG3] = 4; nargs[T_DBG5] = 3; nargs[T_DBG7] = 2;
    nargs[T_STR_OPEN] = 3; nargs[T_STR_CLOSE] = 1; nargs[T_STR_FILE] = 3; nargs[T_STR_RESET] = 1; nargs[T_STR_BUF] = 1;
    nargs[T_TMR_ADD] = 4; nargs[T_TMR_REMOVE] = 1; nargs[T_TMR_PERIOD] = 2; nargs[T_LIP] = 0; nargs[T_FRAME] = 0;
    nargs[T_36F0] = 11; nargs[T_VOICE] = 1; nargs[T_3D90] = 3; nargs[T_DUMP] = 0;
    nargs[T_ZMALLOC] = 1; nargs[T_ZCRC] = 3; nargs[T_ZDEFL] = 8; nargs[T_ZINFL] = 4; nargs[T_ZDESTROY] = 1; nargs[T_ZHEADER] = 1; nargs[T_ZFDOPEN] = 2;
    nargs[T_ZOPEN] = 2; nargs[T_ZWRITE] = 3; nargs[T_ZTELL] = 1; nargs[T_ZFREE] = 3; nargs[T_GZCLOSE] = 1; nargs[T_ZPUT] = 3; nargs[T_SSIZE] = 1;
    nargs[T_STELL] = 1; nargs[T_SSEEK] = 3;
    for (i = 1; i < T_LAST; i++) th[i] = fx_thunk(i, nargs[i], stdc[i]);
    imp_GetDlgItemTextA = th[T_GETTEXT]; imp_SendDlgItemMessageA = th[T_SENDMSG]; imp_CallNextHookEx = th[T_NEXTHOOK];
    fx_effect(T_GETTEXT, gettext_effect); fx_ignmask(T_GETTEXT, 4);
    fx_strmask(T_OPEN, 3); fx_strmask(T_WILD, 3); fx_strmask(T_MODLEN, 1); fx_strmask(T_STRNCPY, 2); fx_ignmask(T_STRNCPY, 1);
    fx_strmask(T_COUNT, 1); fx_strmask(T_SUBSCRIBE, 1); fx_strmask(T_FIND, 1);
    fx_strmask(T_ZFDOPEN, 2); fx_strmask(T_ZOPEN, 3);
    fx_ignmask(T_ZWRITE, 2); fx_effect(T_ZWRITE, write_effect); fx_ignmask(T_ZPUT, 2); fx_effect(T_ZPUT, write_effect);
    fx_effect(T_ZMALLOC, zalloc_effect);
    fx_effect(T_STR_OPEN, ref_effect);
    fx_effect(T_ZHEADER, zheader_effect2);
    fx_strmask(T_ZDEFL, 0x40);
    fx_strmask(T_ZINFL, 0x4);
    fx_strmask(T_DBG3, 1); fx_effect(T_DBG3, dbg3_effect);

    fx_region(heap, sizeof heap); fx_region(&heap_used, 4); fx_region(wlog, sizeof wlog); fx_region(&wlog_n, 4);
    fx_region(lightbuf, sizeof lightbuf); fx_region(animobj, sizeof animobj); fx_region(&animptr, 4); fx_region(entryarea, sizeof entryarea);
    fx_region(&errno_cell, 4);
    fx_region(FXDATA(0x8d1730), 60);            /* light entries */
    fx_region(FXDATA(0x8d3630), 0x28);          /* light editor globals */
    fx_region(FXDATA(0x4f0d10), 0x14);
    fx_region(FXDATA(0x8d56e8), 0x10);
    fx_region(FXDATA(0x8d6f1c), 0x10);

    for (it = 0; it < n; it++) {
        int f = only >= 0 ? only : (int)(it % 7);
        int ra = 0, rb = 0;
        unsigned long long cs = fx_rnd();

        (void)cs;
        fx_clear_queues(); fx_reset();
        rfh_seed = (unsigned)it * 7919u; transparent_next = R(3) == 0;
        heap_used = 0; heap_limit = sizeof heap; wlog_n = 0; errno_cell = 0x55; memset(heap, 0xcd, sizeof heap); memset(wlog, 0, sizeof wlog);
        switch (f) {
        case 0: {     /* Smush_GetLengthMs */
            char path[8];
            strcpy(path, "movie");
            FXU32(0x8d10c8) = (unsigned)(uintptr_t)svc_a;
            svc_a[0] = (int)(uintptr_t)th[T_OPEN]; svc_a[1] = (int)(uintptr_t)th[T_CLOSE];
            fx_ret(T_OPEN, R(4) ? 0x1234 : 0);
            fx_save();
            fx_reset(); rfh_seed = (unsigned)it * 7919u; ra = orig_Smush_SetFile(path); fx_snap_a();
            fx_restore(); fx_reset(); rfh_seed = (unsigned)it * 7919u; rb = Smush_GetLengthMs(path) + neg;
            break; }
        case 1: {     /* LightEd_ReadControl */
            int ids[] = { 0x3ec, 0x3ed, 0x3ee, 0x3ef, 0x3f0, 0x3f1, 0x3f2, 0x3f3, 0x3f4, 0x3f5, 0x3eb, 0x3f6, 0x100 };
            int id = ids[R(13)];
            for (i = 0; i < 3; i++) {
                unsigned *e = (unsigned *)FXDATA(0x8d1730 + i * 20);
                int k;
                e[0] = (unsigned)(uintptr_t)lightbuf[i];
                for (k = 1; k < 5; k++) { float v = (float)((int)R(800) - 300) / 7.0f; memcpy(&e[k], &v, 4); }
                for (k = 0; k < 0x80; k++) lightbuf[i][k] = (unsigned char)fx_rnd();
                for (k = 8; k < 24; k++) { float v = (float)((int)R(2000) - 700) / 5.0f; memcpy(lightbuf[i] + k * 4, &v, 4); }
            }
            FXU32(0x8d3634) = R(5) ? 1 : 0;
            FXI32(0x4f0d10) = R(5) ? (int)R(3) : -1;
            FXI32(0x8d3640) = R(3) == 0;
            fx_save();
            fx_reset(); orig_LightEd_ReadControl(0x777, id); fx_snap_a();
            fx_restore(); fx_reset(); LightEd_ReadControl(0x777, id);
            break; }
        case 2: {     /* keyboard hook */
            int keys[] = { 0x12, 0x25, 0x26, 0x27, 0x28, 0x62, 0x64, 0x66, 0x68, 0x41, 0x13, 0x69, 0x11 };
            unsigned key = keys[R(13)];
            unsigned lp = (unsigned)fx_rnd();
            int code = R(8) ? 0 : (int)R(3) + 1;
            for (i = 0; i < 3; i++) {
                unsigned *e = (unsigned *)FXDATA(0x8d1730 + i * 20);
                int k;
                e[0] = (unsigned)(uintptr_t)lightbuf[i];
                for (k = 1; k < 5; k++) { float v = (float)((int)R(1400) - 500) / 3.0f; if (R(9) == 0) v = 359.9f; if (R(9) == 0) v = -179.9f; if (R(7) == 0) v = 359.0f; if (R(7) == 0) v = -179.0f; if (R(9) == 0) v = 360.0f; if (R(9) == 0) v = -180.0f; memcpy(&e[k], &v, 4); }
                for (k = 0; k < 0x80; k++) lightbuf[i][k] = (unsigned char)fx_rnd();
                for (k = 8; k < 24; k++) { float v = (float)((int)R(2000) - 700) / 5.0f; memcpy(lightbuf[i] + k * 4, &v, 4); }
            }
            FXU32(0x8d3630) = R(6) ? 0x555 : 0;
            FXI32(0x4f0d10) = R(6) ? (int)R(3) : -1;
            FXU32(0x8d3648) = R(2) ? (unsigned)fx_rnd() : (R(2) ? key : (key | 0x10000));
            { float s1 = (float)R(100) / 100.0f, s2 = (float)R(500) / 7.0f; memcpy(FXDATA(0x4f0d18), &s1, 4); memcpy(FXDATA(0x4f0d1c), &s2, 4); }
            FXU32(0x8d363c) = (unsigned)fx_rnd();
            fx_ret(T_FOCUS, R(6) ? 1 : 0);
            fx_ret(T_NEXTHOOK, (int)fx_rnd());
            fx_save();
            fx_reset(); ra = orig_kb(code, key, lp); fx_snap_a();
            fx_restore(); fx_reset(); rb = new_kb(code, key, lp) + neg;
            break; }
        case 3: {     /* LecShare_Resolve */
            char nm[24], pt[24], over[24], deflt[24], r1[24], r2[24], r3[24];
            char *patarg;
            int k;
            strcpy(nm, names[R(7)]); strcpy(pt, pats[R(5)]); strcpy(over, pats[R(5)]); strcpy(deflt, pats[R(5)]);
            strcpy(r1, repl[R(4)]); strcpy(r2, repl[R(4)]); strcpy(r3, repl[R(4)]);
            patarg = R(2) ? pt : 0;
            FXU32(0x8d56e8) = R(6) != 0;
            FXU32(0x8d56f0) = R(2) ? (unsigned)(uintptr_t)over : 0;
            FXU32(0x8d56ec) = R(2) ? (unsigned)(uintptr_t)deflt : 0;
            for (k = 0; k < 16; k++) entryarea[k] = (unsigned char)fx_rnd();
            for (k = 0; k < 3; k++) fx_queue(T_WILD, R(2) ? (int)(uintptr_t)(k == 0 ? r1 : k == 1 ? r2 : r3) : 0);
            fx_ret(T_MODLEN, (int)R((unsigned)strlen(nm) + 1));
            fx_ret(T_COUNT, (int)R(4));
            fx_ret(T_SUBSCRIBE, (int)(uintptr_t)r1);
            fx_ret(T_FIND, R(4) ? (int)(uintptr_t)entryarea : 0);
            fx_save();
            fx_reset(); ra = (int)(uintptr_t)orig_LecShare_Resolve(nm, patarg); fx_snap_a();
            fx_restore(); fx_reset(); rb = (int)(uintptr_t)LecShare_Resolve(nm, patarg) + neg;
            break; }
        case 4: {     /* AnimPlay */
            static char moviename[] = "movie.snm";
            int sub = (int)R(5), k;
            void *dbg;

            memset(svc_a, 0, sizeof svc_a); memset(svc_b, 0, sizeof svc_b); memset(svc_c, 0, sizeof svc_c); memset(svc_d, 0, sizeof svc_d);
            memset(svc_e, 0, sizeof svc_e); memset(svc_f, 0, sizeof svc_f); memset(svc_g, 0, sizeof svc_g);
            svc_a[0] = (int)(uintptr_t)th[T_AMEM_ALLOC]; svc_a[1] = (int)(uintptr_t)th[T_AMEM_FREE];
            svc_b[0] = (int)(uintptr_t)th[T_DBG0]; svc_b[3] = (int)(uintptr_t)th[T_DBG3]; svc_b[5] = (int)(uintptr_t)th[T_DBG5]; svc_b[7] = (int)(uintptr_t)th[T_DBG7];
            svc_c[0] = (int)(uintptr_t)th[T_STR_OPEN]; svc_c[1] = (int)(uintptr_t)th[T_STR_CLOSE]; svc_c[2] = (int)(uintptr_t)th[T_STR_FILE];
            svc_c[6] = (int)(uintptr_t)th[T_STR_RESET]; svc_c[7] = (int)(uintptr_t)th[T_STR_BUF];
            svc_d[0] = (int)(uintptr_t)th[T_FRAME];
            svc_e[0] = (int)(uintptr_t)th[T_TMR_ADD]; svc_e[1] = (int)(uintptr_t)th[T_TMR_REMOVE]; svc_e[4] = (int)(uintptr_t)th[T_TMR_PERIOD];
            svc_f[3] = (int)(uintptr_t)th[T_LIP];
            dbg = (sub == 0 || R(4)) ? svc_b : 0;      /* some of the failure messages are printed without a check */
            FXU32(0x906c3c) = (unsigned)(uintptr_t)svc_a; FXU32(0x906c30) = (unsigned)(uintptr_t)dbg; FXU32(0x906c38) = (unsigned)(uintptr_t)svc_c;
            FXU32(0x906c34) = (unsigned)(uintptr_t)svc_d; FXU32(0x8d6f10) = (unsigned)(uintptr_t)svc_e; FXU32(0x8d6f18) = R(4) ? (unsigned)(uintptr_t)svc_f : 0;
            FXU32(0x8d6f20) = R(2) ? 0x20000 : (R(2) ? 0xc0000000u : (unsigned)fx_rnd());
            FXU32(0x8d6f24) = R(2);
            FXU32(0x8d6f28) = (unsigned)R(100000);
            FXU32(0x8d6f1c) = R(300);
            for (k = 0; k < 0x80; k++) animobj[k] = (unsigned char)fx_rnd();
            animptr = animobj;
            fx_ret(T_AMEM_ALLOC, (int)(uintptr_t)animobj);
            if (R(8) == 0) fx_ret(T_AMEM_ALLOC, 0);
            fx_ret(T_STR_OPEN, R(6) == 0 ? -1 : 0);
            fx_ret(T_STR_FILE, R(6) == 0 ? -1 : 0);
            fx_ret(T_STR_BUF, (int)R(5000));
            fx_ret(T_TMR_ADD, R(6) == 0 ? 0 : 1 + (int)R(50));
            if (R(7) == 0) fx_queue(T_TMR_ADD, 0);
            fx_ret(T_DBG7, (int)R(1000));
            fx_ret(T_36F0, (int)R(9) - 3);
            fx_ret(T_VOICE, (int)(FXU32(0x8d6f1c) * 66.67 + (int)R(3000) - 1500));
            if (sub == 0) {   /* create */
                int fps = 1 + (int)R(60);
                unsigned flags = (unsigned)fx_rnd();
                int a4 = (int)fx_rnd(), a5 = (int)fx_rnd();
                animptr = 0;
                fx_save();
                fx_reset(); ra = orig_FUN_004c23c0(&animptr, moviename, fps, a4, a5, flags); fx_snap_a();
                fx_restore(); fx_reset(); rb = AnimPlay_Create(&animptr, moviename, fps, a4, a5, flags) + neg;
            } else if (sub == 1) {   /* destroy */
                fx_save();
                fx_reset(); orig_FUN_004c2690(&animptr); fx_snap_a();
                fx_restore(); fx_reset(); AnimPlay_Destroy(&animptr);
            } else if (sub == 2 || sub == 3) {   /* update */
                int st[] = { 5, 0, 1, 2, 3, 4, -1, 6, 7 };
                int tgt = 100 + (int)R(40000);
                int args[9];
                unsigned *o = (unsigned *)animobj;
                for (k = 0; k < 9; k++) args[k] = (int)fx_rnd();
                o[0x68 / 4] = (unsigned)st[R(9)];
                o[0x14 / 4] = R(4) != 0;
                o[0x6c / 4] = R(2);
                o[0x1c / 4] = (unsigned)tgt;
                o[0x20 / 4] = R(4) ? 1 + R(tgt * 2) : tgt;
                o[0x18 / 4] = R(20);
                o[0x08 / 4] = R(2) ? 0 : (unsigned)fx_rnd();
                o[0x64 / 4] = R(2);
                o[0x60 / 4] = 0x4321;
                fx_save();
                fx_reset(); ra = orig_FUN_004c27a0(animobj, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]); fx_snap_a();
                fx_restore(); fx_reset(); rb = AnimPlay_Update(animobj, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]) + neg;
            } else {
                unsigned flags = (unsigned)fx_rnd();
                int a4 = (int)fx_rnd(), a5 = (int)fx_rnd(), a6 = (int)fx_rnd();
                fx_save();
                fx_reset(); ra = orig_FUN_004c36b0(animobj); ra += 10 * orig_FUN_004c3d30(animobj, moviename, flags, a4, a5, a6); fx_snap_a();
                fx_restore(); fx_reset(); rb = AnimPlay_ResetState(animobj); rb += 10 * AnimPlay_OpenFile(animobj, moviename, flags, a4, a5, a6); rb += neg;
            }
            break; }
        case 5: {     /* gz_open */
            static const char *modes[] = { "rb", "wb9", "wb", "rb0", "wf6", "ab", "", "r", "w1h", "xyz", "rw", "wb9f", "r3" };
            char path[24], mode[24];
            int fd = R(3) ? -1 : 3;
            memset(svc_a, 0, sizeof svc_a);
            svc_a[0] = (int)(uintptr_t)th[T_ZOPEN]; svc_a[3] = (int)(uintptr_t)th[T_ZWRITE]; svc_a[4] = (int)(uintptr_t)th[T_ZTELL];
            FXU32(0x906c44) = (unsigned)(uintptr_t)svc_a;
            strcpy(path, R(8) ? "save/game.gsv" : "x"); strcpy(mode, modes[R(13)]);
            if (R(30) == 0) strcpy(mode, "wbbbbbbbbbbbbbbbbbbbbbb");
            fx_ret(T_ZCRC, (int)fx_rnd()); fx_ret(T_ZDEFL, R(5) == 0 ? -2 : 0); fx_ret(T_ZINFL, R(5) == 0 ? -2 : 0);
            fx_ret(T_ZFDOPEN, R(5) ? 0x6000 : 0); fx_ret(T_ZOPEN, R(5) ? 0x6100 : 0); fx_ret(T_ZTELL, (int)R(300));
            fx_ret(T_ZDESTROY, 0);
            heap_limit = R(10) == 0 ? 100 + R(300) : sizeof heap;
            fx_save();
            fx_reset(); heap_used = 0; ra = (int)(uintptr_t)orig_gz_open(path, mode, fd); fx_snap_a();
            fx_restore(); fx_reset(); heap_used = 0; rb = (int)(uintptr_t)gz_open(path, mode, fd) + neg;
            break; }
        default: {    /* gz_putLong, Zfile_Close, StdFile */
            int sub = (int)R(4);
            int z[2];
            void *file = (void *)(uintptr_t)(0x3000 + R(50));
            memset(svc_a, 0, sizeof svc_a); memset(svc_b, 0, sizeof svc_b); memset(svc_c, 0, sizeof svc_c);
            svc_a[1] = (int)(uintptr_t)th[T_CLOSE]; svc_a[3] = (int)(uintptr_t)th[T_ZPUT]; svc_a[4] = (int)(uintptr_t)th[T_ZTELL];
            svc_b[1] = (int)(uintptr_t)th[T_ZFREE];
            svc_c[4] = (int)(uintptr_t)th[T_STELL]; svc_c[5] = (int)(uintptr_t)th[T_SSEEK];
            FXU32(0x906c44) = (unsigned)(uintptr_t)svc_a; FXU32(0x8d7834) = (unsigned)(uintptr_t)svc_b; FXU32(0x8d7848) = (unsigned)(uintptr_t)svc_c;
            fx_ret(T_STELL, (int)R(100)); fx_ret(T_SSIZE, (int)R(100)); if (R(4) == 0) fx_ret(T_SSIZE, 50), fx_ret(T_STELL, 50);
            z[0] = R(3) ? 0x2222 : 0; z[1] = (int)R(2);
            if (sub == 0) {
                unsigned x = (unsigned)fx_rnd();
                fx_save();
                fx_reset(); orig_gz_putLong(file, x); fx_snap_a();
                fx_restore(); fx_reset(); gz_putLong(file, x);
            } else if (sub == 1) {
                static int zz[2];
                zz[0] = z[0]; zz[1] = z[1];
                fx_save();
                fx_reset(); orig_FUN_004c5ab0(zz); fx_snap_a();
                fx_restore(); fx_reset(); Zfile_Close(zz);
            } else if (sub == 2) {
                fx_save();
                fx_reset(); ra = orig_FUN_004c5e30(file); fx_snap_a();
                fx_restore(); fx_reset(); rb = StdFile_Tell(file) + neg;
            } else {
                fx_save();
                fx_reset(); ra = orig_FUN_004c5f50(file); fx_snap_a();
                fx_restore(); fx_reset(); rb = StdFile_IsEof(file) + neg;
            }
            break; }
        }
        fx_cases++;
        if (ra != rb) { if (fx_fails < 4) printf("  ret %d %d (%x %x)\n", ra, rb, ra, rb); fx_fail("return value", it * 100 + f); }
        else if (fx_cmp_a() || fx_cmp_log()) fx_fail("state/calls", it * 100 + f);
    }
    printf("misc cases %ld  differences %ld\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
