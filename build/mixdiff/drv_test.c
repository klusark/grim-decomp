/* Differential test of the DirectSound stream driver (DsndDriver_*, DSound_*) and the memory helpers: original machine
 * code against build/overrides_mixer_drv.c.  DirectSound is replaced by fake COM objects whose methods record their
 * arguments; the module manager, the clock and the mixer are recorder thunks as well. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

/* ---- functions under test ---- */
extern void orig_DSound_Shutdown(void), DSound_Shutdown(void);
extern void orig_DSound_SetPrimaryVolume(int), DSound_SetPrimaryVolume(int);
extern void orig_DSound_FillStreamBuffer(void), DSound_FillStreamBuffer(void);
extern int orig_DSound_GetPlayBlock(void), DSound_GetPlayBlock(void);
extern int orig_FUN_004d2420(int *, unsigned), sou_dsnd_module(int *, unsigned);
extern void orig_FUN_004d2480(void), DsndDriver_module_terminate(void);
extern int orig_FUN_004d24b0(void), DsndDriver_Init(void);
extern void orig_FUN_004d2520(void), DsndDriver_module_shutdown(void);
extern int orig_FUN_004d2550(int, int, void *), dsn_initialize(int, int, void *);
extern void orig_FUN_004d25f0(void), dsn_terminate(void);
extern void orig_FUN_004d2630(unsigned), dsn_setvol(unsigned);
extern unsigned orig_FUN_004d27b0(void), dsn_getvol(void);
extern int orig_FUN_004d27c0(void), dsn_getrate(void);
extern int orig_FUN_004d2940(void), DsndDriver_InitDirectSound(void);
extern void orig_FUN_004d2aa0(int), DsndDriver_CreateStreamBuffer(int);
extern void orig_FUN_004d2bf0(void), DsndDriver_ReleaseDirectSound(void);
extern void orig_FUN_004d2cb0(void *, void *, unsigned), Dsnd_MemCopy(void *, void *, unsigned);
extern void orig_FUN_004d2ce0(void *, int, unsigned), Dsnd_MemFill(void *, int, unsigned);
extern void orig_FUN_004d23e0(void *, void *, unsigned), Dsnd_MemCopyCdecl(void *, void *, unsigned);
extern void orig_FUN_004d2400(void *, int, unsigned), Dsnd_MemFillCdecl(void *, int, unsigned);
extern void orig_FUN_004c3df0(void *, void *, unsigned), Insane_MemCopyCdecl(void *, void *, unsigned);
extern void orig_FUN_004c3e10(void *, void *, unsigned), Insane_MemCopy(void *, void *, unsigned);

enum { T_LUASTUB = 1, T_HWND, T_DSCREATE, T_MIXINIT, T_MIXFREE, T_CLEAR, T_OUTPUT, T_MIXFMT, T_MIXCB,
       T_ADDTIMER = 20, T_REMOVETIMER, T_SETPERIOD,
       T_SVC_REG = 900, T_SVC_UNREG, T_SVC_GET, T_SVC_FREE, T_SVC_ERR = 908,
       OBJ_DS = 1, OBJ_BUF1, OBJ_3D, OBJ_DS2, OBJ_BUF2, OBJ_BUF3 };

static void *th_lua, *th_hwnd, *th_mixinit, *th_mixfree, *th_clear, *th_output, *th_mixfmt;
void Lua_Stub(const char *fmt, int a) { ((void (*)(const char *, int))th_lua)(fmt, a); }
void *Win_GetMainHwnd(void) { return ((void *(*)(void))th_hwnd)(); }
int FUN_004d2d40(int *svc, unsigned units, int frames) { return ((int (*)(int *, unsigned, int))th_mixinit)(svc, units, frames); }
int Mixer_Init(int *svc, unsigned units, int frames) { return ((int (*)(int *, unsigned, int))th_mixinit)(svc, units, frames); }
int sou_mixer_terminate(int *svc) { return ((int (*)(int *))th_mixfree)(svc); }
int Mixer_Free(int *svc) { return ((int (*)(int *))th_mixfree)(svc); }
int Mixer_ClearAccumulator(void) { return ((int (*)(void))th_clear)(); }
void Mixer_Output(void *dst, int frames) { ((void (*)(void *, int))th_output)(dst, frames); }
void FUN_004d2d90(void) {}                       /* address only (callback argument) */
void Mixer_MixVoiceByFormat(void) {}

void *imp_DirectSoundCreate __asm__("__imp__DirectSoundCreate@12");
__asm__(".globl _DirectSoundCreate@12\n_DirectSoundCreate@12: jmp *__imp__DirectSoundCreate@12\n");

static uint64_t effseed;
static unsigned effrnd(void) { effseed ^= effseed << 13; effseed ^= effseed >> 7; effseed ^= effseed << 17; return (unsigned)(effseed >> 20); }

#define BUFSZ 0x18100
static unsigned char bufA[BUFSZ + 64], bufB[BUFSZ + 64];
static void *fake_ds_new, *fake_ds_primary_new, *fake_buf_new;

static unsigned *dbg_pn1;
static int lock_effect(int tag, unsigned *args)
{
    dbg_pn1 = (unsigned *)args[4];
    unsigned bytes = args[2];
    unsigned **pp1 = (unsigned **)args[3], *pn1 = (unsigned *)args[4], **pp2 = (unsigned **)args[5], *pn2 = (unsigned *)args[6];
    unsigned mode = effrnd() % 4;
    if (getenv("LOCKDBG")) printf("lock tag %d bytes %x pp1 %p pn1 %p pp2 %p pn2 %p\n", tag, bytes, pp1, pn1, pp2, pn2);
    unsigned k = 4 * (1 + effrnd() % 1000);
    if (mode == 0 || k >= bytes) { *pp1 = (unsigned *)bufA; *pn1 = bytes; *pp2 = 0; *pn2 = 0; }
    else if (mode == 1) { *pp1 = (unsigned *)bufA; *pn1 = bytes - k; *pp2 = (unsigned *)bufB; *pn2 = k; }
    else if (mode == 2) { *pp1 = (unsigned *)bufA; *pn1 = bytes; *pp2 = (unsigned *)bufB; *pn2 = 0; }
    else { *pp1 = (unsigned *)bufA; *pn1 = bytes - (k & ~3u); *pp2 = (unsigned *)bufB; *pn2 = (k & ~3u); }
    return -12345678;       /* the queued / constant HRESULT */
}
static int getpos_effect(int tag, unsigned *args)
{
    unsigned *pplay = (unsigned *)args[1], *pwrite = (unsigned *)args[2];
    *pplay = effrnd() % 0x18000; *pwrite = effrnd() % 0x18000;
    return -12345678;
}
static int dscreate_effect(int tag, unsigned *args)
{
    *(void **)args[1] = fake_ds_new;
    return -12345678;
}
static int createbuf_effect(int tag, unsigned *args)
{
    *(void **)args[2] = ((unsigned *)args[1])[1] == 0x81 ? fake_ds_primary_new : fake_buf_new;
    return -12345678;
}
static int output_effect(int tag, unsigned *args)
{
    unsigned char *dst = (unsigned char *)args[0];
    int frames = (int)args[1], i;
    if (getenv("LOCKDBG")) printf("output dst %p frames %x n1 %x (at %p)\n", dst, frames, dbg_pn1 ? *dbg_pn1 : 0, dbg_pn1);
    for (i = 0; i < frames * 4 && i < BUFSZ; i++) dst[i] = (unsigned char)(frames * 7 + i);
    if (getenv("LOCKDBG")) printf("after: n1 %x\n", dbg_pn1 ? *dbg_pn1 : 0);
    return 0;
}

static unsigned char fmtbuf[0x40];
#define DS_BYTES 0x8d3650
int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000;
    setvbuf(stdout, 0, _IONBF, 0);
    int neg = argc > 2;
    int i;
    /* IDirectSound: QI(3) AddRef(1) Release(1) CreateSoundBuffer(4) GetCaps(2) Duplicate(3) SetCoopLevel(3) Compact(1) ... */
    static const int dsargs[16] = {3, 1, 1, 4, 2, 3, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2};
    /* IDirectSoundBuffer: QI AddRef Release GetCaps GetCurrentPosition(3) GetFormat(4) GetVolume(2) GetPan GetFreq GetStatus Init Lock(9) Play(4)
       SetCurrentPosition(2) SetFormat(2) SetVolume(2) SetPan SetFreq Stop Unlock(5) Restore */
    static const int bufargs[24] = {3, 1, 1, 2, 3, 4, 2, 2, 2, 2, 3, 8, 4, 2, 2, 2, 2, 2, 1, 5, 1, 2, 2, 2};
    void *ds, *buf1, *d3, *ds2, *buf2, *buf3;
    int svc[16] = {0};
    void *th_hmix, *th_add, *th_rem, *th_set;
    int clk[8];

    th_lua = fx_thunk(T_LUASTUB, 2, 0); fx_strmask(T_LUASTUB, 1);
    th_hwnd = fx_thunk(T_HWND, 0, 0); fx_ret(T_HWND, 0x77);
    th_mixinit = fx_thunk(T_MIXINIT, 3, 0);
    th_mixfree = fx_thunk(T_MIXFREE, 1, 0);
    th_clear = fx_thunk(T_CLEAR, 0, 0);
    th_output = fx_thunk(T_OUTPUT, 2, 0); fx_effect(T_OUTPUT, output_effect);
    th_mixfmt = fx_thunk(T_MIXFMT, 0, 0);
    imp_DirectSoundCreate = fx_thunk(T_DSCREATE, 3, 1); fx_effect(T_DSCREATE, dscreate_effect);
    th_hmix = fx_thunk(T_MIXCB, 2, 0); fx_ignmask(T_MIXCB, 2);
    th_add = fx_thunk(T_ADDTIMER, 4, 0); fx_ignmask(T_ADDTIMER, 1); fx_ret(T_ADDTIMER, 7);
    th_rem = fx_thunk(T_REMOVETIMER, 1, 0);
    th_set = fx_thunk(T_SETPERIOD, 2, 0);
    clk[0] = (int)(intptr_t)th_add; clk[1] = (int)(intptr_t)th_rem; clk[4] = (int)(intptr_t)th_set;
    svc[0] = (int)(intptr_t)fx_thunk(T_SVC_REG, 2, 0); svc[1] = (int)(intptr_t)fx_thunk(T_SVC_UNREG, 1, 0);
    svc[2] = (int)(intptr_t)fx_thunk(T_SVC_GET, 2, 0); svc[3] = (int)(intptr_t)fx_thunk(T_SVC_FREE, 1, 0);
    svc[8] = (int)(intptr_t)fx_thunk(T_SVC_ERR, 1, 0);
    fx_strmask(T_SVC_REG, 1); fx_strmask(T_SVC_UNREG, 1); fx_strmask(T_SVC_GET, 1); fx_strmask(T_SVC_ERR, 1);
    ds = fx_com(OBJ_DS, 16, dsargs); buf1 = fx_com(OBJ_BUF1, 24, bufargs); d3 = fx_com(OBJ_3D, 24, bufargs);
    ds2 = fx_com(OBJ_DS2, 16, dsargs); buf2 = fx_com(OBJ_BUF2, 24, bufargs); buf3 = fx_com(OBJ_BUF3, 24, bufargs);
    fake_ds_new = ds2; fake_ds_primary_new = buf2; fake_buf_new = buf3;
    for (i = OBJ_DS2; i <= OBJ_DS2; i++) fx_effect(i * 100 + 3, createbuf_effect);
    fx_effect(OBJ_DS * 100 + 3, createbuf_effect);
    fx_effect(OBJ_BUF3 * 100 + 11, lock_effect); fx_ignmask(OBJ_BUF3 * 100 + 11, 0x78); fx_ignmask(OBJ_BUF2 * 100 + 11, 0x78);
    fx_derefmask(OBJ_DS2 * 100 + 3, 2); fx_derefmask(OBJ_DS * 100 + 3, 2);
    fx_effect(OBJ_BUF3 * 100 + 4, getpos_effect);
    fx_effect(OBJ_BUF2 * 100 + 11, lock_effect);
    memset(fmtbuf, 0, sizeof fmtbuf);

    fx_region(FXDATA(0x8d3650), 0x30);
    fx_region(FXDATA(0x8db200), 0x8dcc90 - 0x8db200);
    fx_region(FXDATA(0x4f3f94), 0x18);
    fx_region(bufA, BUFSZ); fx_region(bufB, BUFSZ);

    for (long it = 0; it < n; it++) {
        int f = getenv("ONLY") ? atoi(getenv("ONLY")) : (int)(it % 26);
        unsigned long long cseed = fx_rnd();
        int ra = 0, rb = 0;
        int a1 = (int)fx_rnd(), a2 = (int)fx_rnd();
        unsigned char src1[300], src2[300], dstA[300], dstB[300];

        memset(FXDATA(0x8d3650), 0, 0x30);
        memset(FXDATA(0x8db200), 0, 0x8dcc90 - 0x8db200);
        memset(FXDATA(0x4f3f94), 0, 0x18);
        for (i = 0; i < BUFSZ; i++) { bufA[i] = (unsigned char)fx_rnd(); bufB[i] = (unsigned char)fx_rnd(); }
        /* the main sound system's objects */
        FXU32(0x8d365c) = (fx_rnd() % 6) ? (unsigned)(uintptr_t)ds : 0;
        FXU32(0x8d3670) = (fx_rnd() % 6) ? (unsigned)(uintptr_t)buf1 : 0;
        FXU32(0x8d3674) = (fx_rnd() % 3) ? (unsigned)(uintptr_t)d3 : 0;
        FXU32(0x8d3654) = (unsigned)fx_rnd(); FXU32(0x8d3658) = (unsigned)fx_rnd();
        /* the stream driver's */
        FXU32(0x8dcc40) = (fx_rnd() % 5) ? (unsigned)(uintptr_t)ds2 : 0;
        FXU32(0x8dcc44) = (fx_rnd() % 5) ? (unsigned)(uintptr_t)buf2 : 0;
        FXU32(0x8dcc48) = (fx_rnd() % 6) ? (unsigned)(uintptr_t)buf3 : 0;
        FXI32(0x8dcc50) = (int)(fx_rnd() % 2);
        FXI32(0x8dcc54) = (int)(fx_rnd() % 3);        /* timer id */
        FXI32(0x8dcc58) = (int)(fx_rnd() % 2);        /* volume table built */
        FXI32(0x8db420) = 3 + (int)(fx_rnd() % 14);   /* blocks */
        FXI32(0x4f3f94) = (int)(fx_rnd() % 20) - 3;   /* last block */
        FXU32(0x4f3f98) = 5000 + (unsigned)(fx_rnd() % 60000);   /* rate */
        FXU32(0x4f3f9c) = (unsigned)fx_rnd() & 0xff;
        FXI32(0x4f3fa0) = (int)fx_rnd();
        FXU32(0x8db410) = (unsigned)(uintptr_t)th_hmix;
        FXU32(0x8db41c) = (unsigned)(uintptr_t)svc;
        FXU32(0x8db424) = (unsigned)(uintptr_t)clk;
        FXU32(0x8db208) = (unsigned)(uintptr_t)0x12340000 + (unsigned)(fx_rnd() % 2) * 4;
        FXU32(0x8db430) = (unsigned)fx_rnd();
        FXU32(0x4f1000) = 0;
        {   /* the primary volume as a float in 0..1.2 */
            float v = (float)(fx_rnd() % 1300) / 1000.0f;
            memcpy(&a1, &v, 4);
            if ((fx_rnd() & 15) == 0) a1 = (int)fx_rnd();       /* any bit pattern */
        }
        if (FXU32(0x8d365c) == 0) FXU32(0x8d3670) = 0;          /* preconditions of the original (it dereferences without testing) */
        if (f == 16) FXU32(0x8dcc40) = (unsigned)(uintptr_t)ds2;
        if (f == 12) FXU32(0x8dcc48) = (unsigned)(uintptr_t)buf3;
        for (i = 0; i < 300; i++) { src1[i] = src2[i] = (unsigned char)fx_rnd(); dstA[i] = dstB[i] = (unsigned char)fx_rnd(); }

        fx_clear_queues();
        /* HRESULTs: mostly success, now and then a failure */
        {
            int k;
            for (k = 0; k < 24; k++) {
                int t;
                for (t = 1; t <= 6; t++) {
                    fx_ret(t * 100 + k, 0);
                    if (fx_rnd() % 12 == 0) fx_queue(t * 100 + k, (int)(0x88780000 | (fx_rnd() & 0xff)));
                }
            }
            fx_ret(T_DSCREATE, 0); if (fx_rnd() % 10 == 0) fx_queue(T_DSCREATE, (int)0x88780078);
            fx_ret(T_ADDTIMER, 7);
            fx_queue(T_SVC_GET, ((fx_rnd() % 4) ? 0x2200 : 0)); fx_queue(T_SVC_GET, (fx_rnd() % 4) ? 0x2400 : 0);
            fx_ret(T_MIXINIT, 0); if (fx_rnd() % 6 == 0) fx_queue(T_MIXINIT, -1);
        }
        fx_region_reset();
        fx_region(FXDATA(0x8d3650), 0x30);
        fx_region(FXDATA(0x8db200), 0x8dcc90 - 0x8db200);
        fx_region(FXDATA(0x4f3f94), 0x18);
        fx_region(bufA, BUFSZ); fx_region(bufB, BUFSZ);
        fx_region(dstA, 300);
        fx_save();

#define RUN(CALL_O, CALL_M) do { \
            fx_reset(); effseed = cseed | 1; ra = (CALL_O); fx_snap_a(); \
            fx_restore(); fx_reset(); effseed = cseed | 1; rb = (CALL_M) + neg; } while (0)
        switch (f) {
        case 0: RUN((orig_DSound_Shutdown(), 0), (DSound_Shutdown(), 0)); break;
        case 1: RUN((orig_DSound_SetPrimaryVolume(a1), 0), (DSound_SetPrimaryVolume(a1), 0)); break;
        case 2: case 3: case 4: RUN((orig_DSound_FillStreamBuffer(), 0), (DSound_FillStreamBuffer(), 0)); break;
        case 5: RUN(orig_DSound_GetPlayBlock(), DSound_GetPlayBlock()); break;
        case 6: RUN(orig_FUN_004d2420(svc, a2), sou_dsnd_module(svc, a2)); break;
        case 7: RUN((orig_FUN_004d2480(), 0), (DsndDriver_module_terminate(), 0)); break;
        case 8: RUN(orig_FUN_004d24b0(), DsndDriver_Init()); break;
        case 9: RUN((orig_FUN_004d2520(), 0), (DsndDriver_module_shutdown(), 0)); break;
        case 10: RUN(orig_FUN_004d2550(a2 % 80000, 5, th_hmix), dsn_initialize(a2 % 80000, 5, th_hmix)); break;
        case 11: RUN((orig_FUN_004d25f0(), 0), (dsn_terminate(), 0)); break;
        case 12: RUN((orig_FUN_004d2630(a2), 0), (dsn_setvol(a2), 0)); break;
        case 13: RUN((int)orig_FUN_004d27b0(), (int)dsn_getvol()); break;
        case 14: RUN(orig_FUN_004d27c0(), dsn_getrate()); break;
        case 15: RUN(orig_FUN_004d2940(), DsndDriver_InitDirectSound()); break;
        case 16: RUN((orig_FUN_004d2aa0(a2 % 24 - 3), 0), (DsndDriver_CreateStreamBuffer(a2 % 24 - 3), 0)); break;
        case 17: RUN((orig_FUN_004d2bf0(), 0), (DsndDriver_ReleaseDirectSound(), 0)); break;
        case 18: { unsigned c = (unsigned)a2 % 260; RUN((orig_FUN_004d2cb0(dstA + 3, src1 + 1, c), 0), (Dsnd_MemCopy(dstA + 3, src1 + 1, c), 0)); break; }
        case 19: { unsigned c = ((unsigned)a2 % 260) & ~3u; RUN((orig_FUN_004d2ce0(dstA + 1, a2 >> 8, c), 0), (Dsnd_MemFill(dstA + 1, a2 >> 8, c), 0)); break; }
        case 20: { unsigned c = (unsigned)a2 % 260; RUN((orig_FUN_004d23e0(dstA + 2, src1, c), 0), (Dsnd_MemCopyCdecl(dstA + 2, src1, c), 0)); break; }
        case 21: { unsigned c = ((unsigned)a2 % 260) & ~3u; RUN((orig_FUN_004d2400(dstA + 2, a2 >> 8, c), 0), (Dsnd_MemFillCdecl(dstA + 2, a2 >> 8, c), 0)); break; }
        case 22: { unsigned c = (unsigned)a2 % 260; RUN((orig_FUN_004c3df0(dstA + 1, src1 + 2, c), 0), (Insane_MemCopyCdecl(dstA + 1, src1 + 2, c), 0)); break; }
        case 23: { unsigned c = (unsigned)a2 % 260; RUN((orig_FUN_004c3e10(dstA + 3, src1 + 3, c), 0), (Insane_MemCopy(dstA + 3, src1 + 3, c), 0)); break; }
        default: RUN((orig_DSound_FillStreamBuffer(), 0), (DSound_FillStreamBuffer(), 0)); break;
        }
        fx_cases++;
        if (ra != rb) fx_fail("return value", it * 100 + f);
        else if (fx_cmp_a() || fx_cmp_log()) fx_fail("state/calls", it * 100 + f);
    }
    printf("drv cases %ld  differences %ld\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
