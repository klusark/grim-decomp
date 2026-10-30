/* Differential test of the Smush sound module (SoundModule_*): original machine code against build/overrides_mixer_snd.c.
 * Everything the module calls (module manager services, the sound driver, the sync clock, the allocator, the memory
 * helpers) is a recorder thunk; voices, tracks and the command streams of the mixer callback are randomised.
 * ONLY=<n> selects one function (see the switch).  */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "fx.h"

#define VOICES 16
#define VBUF 0x6000            /* ring buffer of a voice in the test */

/* ---- under test ---- */
extern int orig_FUN_004d0300(int *, unsigned), SoundModule_Register(int *, unsigned);
extern void orig_FUN_004d03a0(void), SoundModule_Unregister(void);
extern int orig_FUN_004d03d0(void), SoundModule_Init(void);
extern void orig_FUN_004d0510(void), SoundModule_Shutdown(void);
extern int orig_FUN_004d0550(int, int, unsigned, ...), SoundModule_Open(int, int, unsigned, ...);
extern int orig_FUN_004d0610(void), SoundModule_Close(void);
extern int orig_FUN_004d06a0(unsigned, int), SoundModule_AddTrackBuffer(unsigned, int);
extern void orig_FUN_004d0860(unsigned char *, int, int, int, unsigned), SoundModule_PlayChunk(unsigned char *, int, int, int, unsigned);
extern void orig_FUN_004d0a50(unsigned), SoundModule_StopSound(unsigned);
extern void orig_FUN_004d0a80(void), SoundModule_Pause(void);
extern void orig_FUN_004d0a90(void), SoundModule_Resume(void);
extern void orig_FUN_004d0aa0(void), SoundModule_StopAll(void);
extern void orig_FUN_004d0ad0(int, unsigned), SoundModule_SetVolume(int, unsigned);
extern unsigned orig_FUN_004d0b10(unsigned), SoundModule_GetVolume(unsigned);
extern void orig_FUN_004d0b60(int, unsigned char), SoundModule_SetPan(int, unsigned char);
extern int orig_FUN_004d0b90(unsigned), SoundModule_GetPan(unsigned);
extern void orig_FUN_004d0bd0(int), SoundModule_DriverCommand2(int);
extern int orig_FUN_004d0bf0(void), SoundModule_DriverCommand3(void);
extern void orig_FUN_004d0c00(unsigned), SoundModule_SetDriverRate(unsigned);
extern int orig_FUN_004d0c30(unsigned), SoundModule_GetPosition(unsigned);
extern int orig_Sound_VoiceSampleCount(int), Sound_VoiceSampleCount(int);
extern int orig_FUN_004d0d70(int, int, unsigned, unsigned), SoundModule_SetParam(int, int, unsigned, unsigned);
extern int orig_FUN_004d0e00(int, int, unsigned *, unsigned *), SoundModule_GetParam(int, int, unsigned *, unsigned *);
extern unsigned orig_FUN_004d0eb0(unsigned char), SoundModule_GetChannelVolume(unsigned char);
extern void orig_FUN_004d0ed0(unsigned char, unsigned char), SoundModule_SetChannelVolume(unsigned char, unsigned char);
extern void orig_FUN_004d0f00(unsigned char *, unsigned, int, int, int, unsigned), SoundModule_PlayVoc(unsigned char *, unsigned, int, int, int, unsigned);
extern void orig_FUN_004d1180(unsigned char *, int, int, int, int, unsigned, int, int, int, int), SoundModule_PlaySaud(unsigned char *, int, int, int, int, unsigned, int, int, int, int);
extern void orig_FUN_004d1690(void), SoundModule_SyncClock(void);
extern void orig_FUN_004d16a0(int, void *), SoundModule_MixCallback(int, void *);
extern void orig_FUN_004d2340(double), SoundModule_AdvanceClock(double);

enum { T_ALLOC = 1, T_FREE, T_MEMCPY, T_MEMFILL, T_FILL7F, T_MIX, T_PRINT,
       T_SVC_REG = 900, T_SVC_UNREG, T_SVC_GET, T_SVC_FREE, T_SVC_ERR = 908,
       T_DRV = 950,    /* 950 + slot */
       T_CLK = 970 };  /* 970 + slot */

/* helpers the sound module calls: the lecsmush memcpy / the dsnd fill (as real memory operations, logged) */
static void *th_copy, *th_fill, *th_fill7f;
void FUN_004c3df0(void *d, void *s, unsigned n) { ((void (*)(void *, void *, unsigned))th_copy)(d, s, n); memcpy(d, s, n); }
void Insane_MemCopyCdecl(void *d, void *s, unsigned n) { ((void (*)(void *, void *, unsigned))th_copy)(d, s, n); memcpy(d, s, n); }
void FUN_004d23e0(void *d, void *s, unsigned n) { ((void (*)(void *, void *, unsigned))th_copy)(d, s, n); memcpy(d, s, n); }
void Dsnd_MemCopyCdecl(void *d, void *s, unsigned n) { ((void (*)(void *, void *, unsigned))th_copy)(d, s, n); memcpy(d, s, n); }
void FUN_004d2400(void *d, int v, unsigned n) { ((void (*)(void *, int, unsigned))th_fill)(d, v, n); memset(d, (unsigned char)v, n); }
void Dsnd_MemFillCdecl(void *d, int v, unsigned n) { ((void (*)(void *, int, unsigned))th_fill)(d, v, n); memset(d, (unsigned char)v, n); }
void FUN_004d5e50(void *d, int v, int n) { ((void (*)(void *, int, int))th_fill7f)(d, v, n); memset(d, v, n); }

static int dbg_w;
static volatile int g_phase;
static volatile long g_last;
static DWORD WINAPI watchdog(LPVOID p) { long seen = -1; int stale = 0; (void)p; for (;;) { Sleep(1000); if (g_last == seen) { if (++stale >= 4) { printf("WATCHDOG: stuck in case %ld phase %d (1 = original, 2 = mine)\n", seen, g_phase); fflush(stdout); printf("STUCK %ld cases %ld differences %ld\n", seen, fx_cases, fx_fails); ExitProcess(3); } } else { stale = 0; seen = g_last; } } return 0; }
static uint64_t effseed;
static unsigned effrnd(void) { effseed ^= effseed << 13; effseed ^= effseed >> 7; effseed ^= effseed << 17; return (unsigned)(effseed >> 20); }

/* bump allocator with failures */
static unsigned char pool[1 << 22];
static unsigned pool_used;
static int alloc_calls, alloc_fail_at, alloc_big_fail;
static int alloc_effect(int tag, unsigned *args)
{
    unsigned n = (args[0] + 15) & ~15u;
    alloc_calls++;
    if (alloc_calls == alloc_fail_at) return 0;
    if (alloc_big_fail && args[0] > 100000 && (alloc_calls & 1)) return 0;     /* big requests fail now and then (the size is reduced and retried) */
    if (pool_used + n > sizeof pool) return 0;
    pool_used += n;
    return (int)(intptr_t)(pool + pool_used - n);
}

static unsigned char vbuf[VOICES][VBUF + 64], vblock[VOICES][0x1800 + 64];
static unsigned char chunkdata[8192];

#define VOICE(i) ((unsigned char *)FXDATA(0x8dad58) + (i) * 0x34)
#define TRACK(i) ((unsigned char *)FXDATA(0x8da8f0) + (i) * 0x3c)
#define U32AT(p, o) (*(unsigned *)((p) + (o)))
#define I32AT(p, o) (*(int *)((p) + (o)))

static void be32(unsigned char *p, unsigned v) { p[0] = v >> 24; p[1] = v >> 16; p[2] = v >> 8; p[3] = v; }
static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }

static int mix_effect(int tag, unsigned *args) { return 0; }

static int memtab[4], clktab[12], drvtab[8], svc[16];
static void *drvtab_ptr(int i) { return (void *)(intptr_t)drvtab[i]; }
static void *th_mix;

static void setup_voices(int n)
{
    int i;
    I32AT(FXDATA(0x4f3e30), 0) = n;
    for (i = 0; i < VOICES; i++) {
        unsigned char *v = VOICE(i);
        memset(v, 0, 0x34);
        U32AT(v, 0x00) = (unsigned)(uintptr_t)vbuf[i];
        U32AT(v, 0x04) = (unsigned)(uintptr_t)vblock[i];
        I32AT(v, 0x10) = (R(3) == 0) ? 0x1000 : 0x2000 + 0x800 * R(4);
        U32AT(v, 0x08) = (unsigned)(uintptr_t)vbuf[i]; U32AT(v, 0x0c) = (unsigned)(uintptr_t)(vbuf[i] + 0x40);
        U32AT(v, 0x24) = 0x1000 + 0x100 * R(8); U32AT(v, 0x28) = R(0x3000); U32AT(v, 0x30) = R(0x3000);
        v[0x14] = (unsigned char)R(256); v[0x15] = (unsigned char)R(256);
        v[0x16] = (unsigned char)(R(5) == 0 ? 3 : R(3));      /* 0 free, 1 playing, 2 started, 3 stalled */
        v[0x17] = (unsigned char)R(6);
        U32AT(v, 0x18) = (R(3) == 0 ? 0x40 : R(3) == 0 ? 0x80 : 0) | R(4);
        U32AT(v, 0x1c) = R(4) == 0 ? 0xffffff01 : R(30);
        I32AT(v, 0x20) = R(0x100);
        memset(vbuf[i], 0x7f, VBUF);
    }
}

static void setup_sound_globals(void)
{
    int i;
    memset(FXDATA(0x4f3e34), 0, 0x18);
    FXU32(0x4f3e34) = R(3) ? 0x7f : R(256);
    FXU32(0x4f3e38) = 5000 + R(40000);
    FXI32(0x4f3e3c) = 16 + R(100);
    FXU32(0x4f3e40) = 1 + R(4000);
    FXI32(0x4f3e44) = 16 + R(241);
    FXI32(0x4f3e48) = R(2);
    FXI32(0x8dad40) = R(2); FXI32(0x8dad44) = R(2); FXI32(0x8dad4c) = R(2); FXI32(0x8dad50) = R(2);
    FXI32(0x8db1ec) = R(5) == 0;
    FXI32(0x8db1f0) = R(4) != 0;
    FXI32(0x8dacf4) = R(1000);
    FXI32(0x8db1f8) = R(3) ? 0 : (int)R(100000);
    *(double *)FXDATA(0x8db200) = (double)(int)R(100000) * 0.37;
    for (i = 0; i < 256; i++) FXDATA(0x8db0e8)[i] = (unsigned char)R(256);
    for (i = 0; i < 16; i++) {
        FXI32(0x8da8b0 + 4 * i) = (int)R(3); FXI32(0x8dad00 + 4 * i) = (int)R(3); FXI32(0x8db0a8 + 4 * i) = (int)R(3);
    }
    FXU32(0x8da8a8) = (unsigned)(uintptr_t)memtab;
    FXU32(0x8dacf0) = (unsigned)(uintptr_t)drvtab;
    FXU32(0x8dad48) = (unsigned)(uintptr_t)clktab;
    FXU32(0x8dacf8) = (unsigned)(uintptr_t)svc;
    FXU32(0x8db098) = R(0x10000); FXU32(0x8db09c) = 22050; FXU32(0x8db0a0) = R(2) ? R(0x1000) : 0;
    FXU32(0x8dacfc) = 64000;
    for (i = 0; i < 16; i++) FXU32(0x8dacb0 + 4 * i) = i < 1 + (int)R(6) ? 20000 + R(200000) : 0;
}

int Sound_DriverQuery(void) { return ((int (*)(void))drvtab_ptr(5))(); }

static void setup_mix_voice(int i, int heavy)
{
    unsigned char *v = VOICE(i), *t = TRACK(i);
    unsigned char *buf = vbuf[i];
    int pos[24], ncmd, k, off = 0x40;
    int ring = 0x1000 + 0x400 * R(8);

    memset(t, 0, 0x3c);
    U32AT(v, 0x08) = (unsigned)(uintptr_t)(buf);                       /* chunk = command stream at the start of the buffer */
    U32AT(v, 0x0c) = (unsigned)(uintptr_t)(buf + 0x2000);              /* pcm */
    U32AT(v, 0x24) = ring;                                             /* ringSize */
    U32AT(v, 0x28) = R(8) == 0 ? R(ring) : ring + R(20000);             /* received */
    U32AT(v, 0x30) = (R(3) == 0) ? U32AT(v, 0x28) : U32AT(v, 0x28) + R(30000);   /* total */
    U32AT(v, 0x2c) = R(100);
    for (k = 0; k < ring && k < 0x3000; k++) buf[0x2000 + k] = (unsigned char)R(256);
    /* the track */
    U32AT(t, 0x00) = (unsigned)(uintptr_t)buf;
    U32AT(t, 0x04) = (unsigned)(uintptr_t)(buf + 0x2000);
    I32AT(t, 0x08) = ring;
    I32AT(t, 0x0c) = R(ring * 2);
    I32AT(t, 0x10) = R(4) ? (int)R(2500) : 0;
    I32AT(t, 0x14) = 5000 + R(40000);
    t[0x18] = (unsigned char)R(6);
    I32AT(t, 0x1c) = R(3) == 0 ? 1 : (int)R(4);
    I32AT(t, 0x20) = 5000 + R(40000);
    I32AT(t, 0x24) = (int)R(256) - 128;
    I32AT(t, 0x28) = R(2) ? 0 : (int)R(0x1800);
    t[0x2c] = (unsigned char)R(6);
    I32AT(t, 0x30) = R(17);
    U32AT(t, 0x34) = R(100); U32AT(t, 0x38) = R(3) ? 0 : R(5000);
    /* command stream: random commands, jumps only forward, ends with a sample run or stop */
    ncmd = 3 + R(6);
    for (k = 0; k < ncmd; k++) { pos[k] = off; off += 0x18 + R(8); }
    pos[ncmd] = off;
    for (k = 0; k < ncmd; k++) {
        unsigned char *c = buf + pos[k];
        int len = pos[k + 1] - pos[k];
        int type = (k == ncmd - 1) ? (R(2) ? 5 : 1) : (int[]){1, 1, 6, 6, 7, 2, 8, 9, 10, 11, 3, 3, 4, 4, 5}[R(15)];
        int tgt = k + 1 + R(ncmd - k);
        int offs = pos[tgt] - pos[k];
        memset(c, 0, len);
        c[0] = (unsigned char)type;
        c[1] = (unsigned char)(len - 2);
        switch (type) {
        case 1: case 6: case 7:
            be32(c + 2, R(ring));                 /* position in the ring */
            be32(c + 6, R(3) ? 100 + R(1500) : R(60));
            be32(c + 10, 5000 + R(40000));        /* rate (op 6, 7) */
            if (type == 7) {
                be32(c + 6, 200 + R(3000));       /* skipLeft total */
                be32(c + 0xe, 50 + R(1200));      /* bound */
                c[0x12] = (unsigned char)(offs >> 8); c[0x13] = (unsigned char)offs;
            }
            break;
        case 2: case 8: case 9: case 10: case 11:
            c[2] = (unsigned char)(offs >> 8); c[3] = (unsigned char)offs;
            c[4] = (R(3) == 0) ? (unsigned char)(0xfd + R(3)) : (unsigned char)R(256);
            c[5] = (unsigned char)R(256);
            break;
        case 3: case 4:
            c[2] = (R(2)) ? (unsigned char)(0xfd + R(3)) : (unsigned char)R(256);
            c[3] = (unsigned char)R(256);
            break;
        }
    }
    {   /* voice state */
        int st = R(10);
        v[0x16] = st < 5 ? 1 : st < 8 ? 2 : st < 9 ? 3 : 0;
        if (v[0x16] == 1 || v[0x16] == 3) { U32AT(t, 0x00) = (unsigned)(uintptr_t)(buf + pos[R(ncmd)]); }
        v[0x17] = (unsigned char)R(6);
        v[0x14] = (unsigned char)(R(4) ? R(128) : R(256)); v[0x15] = (unsigned char)(R(256));
        U32AT(v, 0x18) = (R(3) == 0 ? 0x40 : R(2) == 0 ? 0x80 : 0) | R(3);
        U32AT(v, 0x1c) = 100 + i;
        (void)heavy;
        /* conditional commands: often compare with exactly the current value (equal / one off) */
        for (k = 0; k < ncmd; k++) {
            unsigned char *c = buf + pos[k];
            if (c[0] == 2 || (c[0] >= 8 && c[0] <= 11)) {
                if (R(5) == 0) { c[4] = 0; FXDATA(0x8db0e8)[0] = R(2) ? 0 : 5; }
                unsigned char cur = c[4] == 0xff ? (unsigned char)FXU32(0x4f3e34) : c[4] == 0xfe ? v[0x14] : c[4] == 0xfd ? v[0x15] : FXDATA(0x8db0e8)[c[4]];
                int r = R(3);
                if (r == 0) c[5] = cur; else if (r == 1) c[5] = (unsigned char)(cur + 1); else if (r == 2 && R(2)) c[5] = (unsigned char)(cur - 1);
            }
        }
    }
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 20000;
    int neg = argc > 2;
    int i;
    int only = getenv("ONLY") ? atoi(getenv("ONLY")) : -1;

    setvbuf(stdout, 0, _IONBF, 0);
    CreateThread(0, 0, watchdog, 0, 0, 0);
    th_copy = fx_thunk(T_MEMCPY, 3, 0); th_fill = fx_thunk(T_MEMFILL, 3, 0); th_fill7f = fx_thunk(T_FILL7F, 3, 0);
    fx_ignmask(T_MEMCPY, 0);
    th_mix = fx_thunk(T_MIX, 8, 0);
    memtab[0] = (int)(intptr_t)fx_thunk(T_ALLOC, 3, 0); memtab[1] = (int)(intptr_t)fx_thunk(T_FREE, 3, 0);
    fx_effect(T_ALLOC, alloc_effect); fx_strmask(T_ALLOC, 2); fx_strmask(T_FREE, 2);
    for (i = 0; i < 12; i++) clktab[i] = (int)(intptr_t)fx_thunk(T_CLK + i, i == 8 ? 1 : 0, 0);
    for (i = 0; i < 8; i++) drvtab[i] = (int)(intptr_t)fx_thunk(T_DRV + i, i == 0 ? 3 : (i == 2 || i == 4) ? 1 : 0, 0);
    for (i = 0; i < 16; i++) svc[i] = (int)(intptr_t)fx_thunk(T_SVC_REG + i, (i == 0 || i == 2) ? 2 : 1, 0);
    fx_strmask(T_SVC_REG, 1); fx_strmask(T_SVC_UNREG, 1); fx_strmask(T_SVC_GET, 1); fx_strmask(T_SVC_ERR, 1);
    fx_ret(T_DRV + 5, 22050); fx_ignmask(T_DRV, 4);
    for (i = 0; i < 6; i++) FXI32(0x4f3e18 + 4 * i) = ((int[]){1, 2, 2, 4, 2, 4})[i];

    if (getenv("START")) { long st = atol(getenv("START")); fx_seed ^= (uint64_t)st * 0x9e3779b97f4a7c15ull; }
    for (long it = getenv("START") ? atol(getenv("START")) : 0; it < n; it++) {
        int f = only >= 0 ? only : (int)(it % 22);
        unsigned long long cseed = fx_rnd();
        int ra = 0, rb = 0;
        int a1 = (int)fx_rnd(), a2 = (int)fx_rnd();

        if (getenv("PROGRESS")) printf("case %ld\n", it);
        g_last = it; g_phase = 0;
        pool_used = 0; alloc_calls = 0; alloc_fail_at = R(6) == 0 ? 1 + R(5) : 0; alloc_big_fail = R(4) == 0;
        memset(FXDATA(0x8da8b0), 0, 0x40);
        setup_sound_globals();
        setup_voices(1 + R(VOICES));
        for (i = 0; i < 4096; i++) chunkdata[i] = (unsigned char)R(256);

        fx_region_reset();
        fx_region(FXDATA(0x4f3e30), 0x20);                  /* voice count ... */
        fx_region(FXDATA(0x8da8b0), 0x40);                  /* stream kinds */
        fx_region(FXDATA(0x8da8f0), VOICES * 0x3c);         /* tracks */
        fx_region(FXDATA(0x8dacb0), 0x8dad58 - 0x8dacb0);   /* sizes, driver, services, flags */
        fx_region(FXDATA(0x8dad58), VOICES * 0x34);         /* voices */
        fx_region(FXDATA(0x8db098), 0x20);
        fx_region(FXDATA(0x8db0a8), 0x40 + 0x100);
        fx_region(FXDATA(0x8db1e8), 0x28);
        fx_region(vbuf, sizeof vbuf);
        fx_region(vblock, sizeof vblock);
        fx_clear_queues();
        fx_effect(T_ALLOC, alloc_effect);

        switch (f) {
        case 0:  /* Register / Unregister */
            fx_save();
            fx_reset(); effseed = cseed | 1; ra = orig_FUN_004d0300(svc, a2); orig_FUN_004d03a0(); fx_snap_a();
            fx_restore(); fx_reset(); effseed = cseed | 1; rb = SoundModule_Register(svc, a2) + neg; SoundModule_Unregister();
            break;
        case 1: { /* Init: services hand out the allocator, clock and driver */
            fx_queue(T_SVC_GET, (int)(intptr_t)memtab); fx_queue(T_SVC_GET, (int)(intptr_t)clktab); fx_queue(T_SVC_GET, (int)(intptr_t)drvtab);
            if (R(5) == 0) { fx_clear_queues(); fx_queue(T_SVC_GET, R(2) ? (int)(intptr_t)memtab : 0); fx_queue(T_SVC_GET, R(2) ? (int)(intptr_t)clktab : 0); fx_queue(T_SVC_GET, R(2) ? (int)(intptr_t)drvtab : 0); }
            fx_queue(T_DRV, R(5) ? 0 : 1);
            fx_save();
            fx_reset(); effseed = cseed | 1; pool_used = 0; alloc_calls = 0; ra = orig_FUN_004d03d0(); fx_snap_a();
            fx_restore(); fx_reset(); effseed = cseed | 1; pool_used = 0; alloc_calls = 0; rb = SoundModule_Init() + neg;
            break; }
        case 2:  /* Shutdown (frees, closes) */
            fx_save();
            fx_reset(); effseed = cseed | 1; orig_FUN_004d0510(); fx_snap_a();
            fx_restore(); fx_reset(); effseed = cseed | 1; SoundModule_Shutdown();
            break;
        case 3: { /* Open with a size list */
            unsigned s1 = R(2) ? 30000 + R(100000) : 0, s2 = R(2) ? 20000 + R(50000) : 0, s3 = 40000;
            int limit = (int)(R(3) ? 64000 : 20000);
            fx_queue(T_DRV, R(4) ? 0 : 1);
            fx_save();
            fx_reset(); effseed = cseed | 1; pool_used = 0; alloc_calls = 0; ra = orig_FUN_004d0550(22050, limit, s1, s2, s3, 0); fx_snap_a();
            fx_restore(); fx_reset(); effseed = cseed | 1; pool_used = 0; alloc_calls = 0; rb = SoundModule_Open(22050, limit, s1, s2, s3, 0) + neg;
            break; }
        case 4:  /* Close */
            fx_save();
            fx_reset(); effseed = cseed | 1; ra = orig_FUN_004d0610(); fx_snap_a();
            fx_restore(); fx_reset(); effseed = cseed | 1; rb = SoundModule_Close() + neg;
            break;
        case 5: { /* AddTrackBuffer */
            unsigned sz = (R(4) == 0) ? R(300) * 4 : 20000 + R(500000);
            int lim = (int)(R(2) ? 64000 : R(100000));
            FXI32(0x4f3e30) = (int)R(VOICES - 1);
            fx_save();
            fx_reset(); effseed = cseed | 1; pool_used = 0; alloc_calls = 0; ra = orig_FUN_004d06a0(sz, lim); fx_snap_a();
            fx_restore(); fx_reset(); effseed = cseed | 1; pool_used = 0; alloc_calls = 0; rb = SoundModule_AddTrackBuffer(sz, lim) + neg;
            break; }
        case 6: { /* accessors by id */
            unsigned id = R(3) == 0 ? 0xffffff01u : (R(3) == 0 ? (unsigned)(-(int)R(20)) : 100 + R(20));
            int w = R(12); dbg_w = w;
            unsigned char ch = R(4) == 0 ? 0xff : (unsigned char)R(256);
            unsigned xa, xb, ya, yb;
            int w1 = 1 + R(5), w2 = 1 + R(5);
            fx_save();
            fx_reset(); effseed = cseed | 1;
            switch (w) {
            case 0: orig_FUN_004d0a50(id); break;
            case 1: orig_FUN_004d0a80(); orig_FUN_004d0a80(); orig_FUN_004d0a90(); break;
            case 2: orig_FUN_004d0aa0(); break;
            case 3: orig_FUN_004d0ad0((int)id, (unsigned)a2); break;
            case 4: ra = (int)orig_FUN_004d0b10(id); break;
            case 5: orig_FUN_004d0b60((int)id, (unsigned char)a2); break;
            case 6: ra = orig_FUN_004d0b90(id); break;
            case 7: orig_FUN_004d0bd0(a2); ra = orig_FUN_004d0bf0(); break;
            case 8: orig_FUN_004d0c00((unsigned)a2); break;
            case 9: ra = orig_FUN_004d0c30(id); break;
            case 10: orig_FUN_004d0ed0(ch, (unsigned char)a2); ra = (int)orig_FUN_004d0eb0(ch); break;
            case 11: xa = xb = 0x1234; ra = orig_FUN_004d0e00(0, w1, &xa, w1 == 1 ? (unsigned *)(uintptr_t)(w2 * 37 + 5) : &xb); orig_FUN_004d0d70(0, w2, (unsigned)a1, (unsigned)a2); ra += (int)(xa ^ xb); break;
            }
            fx_snap_a();
            fx_restore(); fx_reset(); effseed = cseed | 1;
            switch (w) {
            case 0: SoundModule_StopSound(id); break;
            case 1: SoundModule_Pause(); SoundModule_Pause(); SoundModule_Resume(); break;
            case 2: SoundModule_StopAll(); break;
            case 3: SoundModule_SetVolume((int)id, (unsigned)a2); break;
            case 4: rb = (int)SoundModule_GetVolume(id); break;
            case 5: SoundModule_SetPan((int)id, (unsigned char)a2); break;
            case 6: rb = SoundModule_GetPan(id); break;
            case 7: SoundModule_DriverCommand2(a2); rb = SoundModule_DriverCommand3(); break;
            case 8: SoundModule_SetDriverRate((unsigned)a2); break;
            case 9: rb = SoundModule_GetPosition(id); break;
            case 10: SoundModule_SetChannelVolume(ch, (unsigned char)a2); rb = (int)SoundModule_GetChannelVolume(ch); break;
            case 11: ya = yb = 0x1234; rb = SoundModule_GetParam(0, w1, &ya, w1 == 1 ? (unsigned *)(uintptr_t)(w2 * 37 + 5) : &yb); SoundModule_SetParam(0, w2, (unsigned)a1, (unsigned)a2); rb += (int)(ya ^ yb); break;
            }
            rb += neg;
            break; }
        case 7:  /* VoiceSampleCount */
            { int v = R(VOICES + 2); if (R(3) == 0) v = 0; fx_ret(T_DRV + 5, 1 + R(50000));
              if (R(2)) _controlfp(_PC_64, _MCW_PC); else _controlfp(_PC_53, _MCW_PC);
              fx_save();
              fx_reset(); effseed = cseed | 1; ra = orig_Sound_VoiceSampleCount(v); fx_snap_a();
              fx_restore(); fx_reset(); effseed = cseed | 1; rb = Sound_VoiceSampleCount(v) + neg; }
            break;
        case 8:  /* SyncClock + AdvanceClock */
            { double tk = (double)(int)R(2000000) * 0.731; fx_ret(T_CLK + 6, (int)R(3000000)); if (R(3)) fx_queue(T_CLK + 6, (int)R(3000000));
              if (R(2)) _controlfp(_PC_64, _MCW_PC); else _controlfp(_PC_53, _MCW_PC);
              fx_save();
              fx_reset(); effseed = cseed | 1; orig_FUN_004d1690(); orig_FUN_004d2340(tk); fx_snap_a();
              fx_restore(); fx_reset(); effseed = cseed | 1; SoundModule_SyncClock(); SoundModule_AdvanceClock(tk); }
            break;
        case 9: case 10: case 11: case 12: { /* PlayVoc / PlaySaud / PlayChunk */
            int kind = f - 9;
            int sz = 8 + R(2500);
            unsigned fl = (R(3) == 0 ? 0x40 : R(2) ? 0x80 : 0) | R(4);
            int vol = R(4) ? (int)R(140) - 5 : (int)fx_rnd(), pan = (int)R(300) - 150, id = (int)R(30) + 100;
            int st;
            (void)st;
            /* make the voices look settled: some playing, some free, buffers of the sizes the sound module allocated */
            if (kind == 0) {         /* PlayVoc */
                fx_save();
                fx_reset(); effseed = cseed | 1; orig_FUN_004d0f00(chunkdata, sz, id, vol, pan, fl); fx_snap_a();
                fx_restore(); fx_reset(); effseed = cseed | 1; SoundModule_PlayVoc(chunkdata, sz, id, vol, pan, fl);
            } else if (kind == 1 || kind == 2) {
                int key = (int)R(3), chunkNo = R(3) ? 0 : (int)R(4), knd = 1 + R(2), whole = R(2);
                unsigned hdr = R(3) ? R(8) : 0;
                int ssz = 0x30 + R(2000);
                static const unsigned magics[] = {0x5336535a, 0x53364d5a, 0x53443253, 0x5344364d, 0x53443653, 0x53443853, 0x12345678};
                be32(chunkdata + 4, ssz); be32(chunkdata + 0xc, hdr);
                be32(chunkdata + 0x10 + hdr, magics[R(7)]);
                if (R(2)) { chunkdata[8] = chunkdata[9] = chunkdata[0xc] = chunkdata[0xd] = chunkdata[0x10] = chunkdata[0x11] = 0; }
                if (kind == 1) {
                    fx_save();
                    fx_reset(); effseed = cseed | 1; orig_FUN_004d1180(chunkdata, ssz, id, vol, pan, fl, key, chunkNo, knd, whole); fx_snap_a();
                    fx_restore(); fx_reset(); effseed = cseed | 1; SoundModule_PlaySaud(chunkdata, ssz, id, vol, pan, fl, key, chunkNo, knd, whole);
                } else {
                    static const unsigned tags[] = {0x53415544, 0x50534144, 0x50564f43, 0x43726561, 0x41414141};
                    be32(chunkdata, tags[R(5)]);
                    chunkdata[0x14] = 0x1a; chunkdata[0x15] = 0; chunkdata[0x1b] = 0;     /* Crea: header size (LE16); the 24 bit sample count is 0 (b * 0x10100 + b bytes would be copied) */
                    be32(chunkdata + 4, 40 + R(1500));
                    if (R(2)) { chunkdata[8] = chunkdata[9] = chunkdata[0xc] = chunkdata[0xd] = chunkdata[0x10] = chunkdata[0x11] = 0; }
                    be32(chunkdata + 0xc, 0); be32(chunkdata + 0x10, magics[R(7)]);
                    fx_save();
                    fx_reset(); effseed = cseed | 1; orig_FUN_004d0860(chunkdata, id, vol, pan, fl); fx_snap_a();
                    fx_restore(); fx_reset(); effseed = cseed | 1; SoundModule_PlayChunk(chunkdata, id, vol, pan, fl);
                }
            }
            break; }
        default: { /* the mixer callback */
            int frames = 16 + R(1500);
            int nv = FXI32(0x4f3e30);
            for (i = 0; i < nv; i++) setup_mix_voice(i, 0);
            for (i = 0; i < 6; i++) FXI32(0x4f3e18 + 4 * i) = ((int[]){1, 2, 2, 4, 2, 4})[i];
            fx_ret(T_CLK + 6, (int)R(3000000));
            if (R(2)) _controlfp(_PC_64, _MCW_PC); else _controlfp(_PC_53, _MCW_PC);
            fx_save();
            if (getenv("DBGMIX")) printf("before: nv=%d frames=%d", FXI32(0x4f3e30), frames);
            fx_reset(); effseed = cseed | 1; g_phase = 1; orig_FUN_004d16a0(frames, th_mix); g_phase = 0; fx_snap_a();
            if (getenv("DBGMIX")) printf(" after: nv=%d nlog=%d\n", FXI32(0x4f3e30), fx_nlog);
            fx_restore(); fx_reset(); effseed = cseed | 1; g_phase = 2; SoundModule_MixCallback(frames, th_mix); g_phase = 0;
            break; }
        }
        fx_cases++;
        if (ra != rb) { if (fx_fails < 5) printf("  f=%d w=%d ra=%d rb=%d\n", f, dbg_w, ra, rb); fx_fail("return value", it * 100 + f); }
        else if (fx_cmp_a() || fx_cmp_log()) fx_fail("state/calls", it * 100 + f);
    }
    printf("snd cases %ld  differences %ld\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
