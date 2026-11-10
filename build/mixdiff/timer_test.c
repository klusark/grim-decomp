/* Differential test of the Smush timer module (InsaneTimer_*): original machine code against build/overrides_mixer_drv.c.
 * Slots, counters and callbacks are randomised; callbacks are recorder thunks that sometimes change their own slot. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fx.h"

typedef struct { void *cb; int period; unsigned flags; int user, busy, elapsed, busyDeferred, total; } Slot;
#define SLOTS ((Slot *)FXDATA(0x8da5d8))

/* ---- functions under test ---- */
extern void orig_Mixer_Update(void), InsaneTimer_Tick(void);
extern void orig_Mixer_ServiceVoices(void), InsaneTimer_ServiceDeferred(void);
extern void orig_Mixer_ScheduleVoices(void), InsaneTimer_RunDeferred(void);
extern int orig_FUN_004cdf10(void *, int, unsigned, int), sys_Alloc(void *, int, unsigned, int);
extern void orig_FUN_004cdf80(int), sys_Free(int);
extern void orig_FUN_004cdfa0(int, int), sys_Reset(int, int);
extern void orig_FUN_004cdfd0(int), sys_Delay(int);
extern void orig_FUN_004cdef0(void), sys_Disable(void), orig_FUN_004cdf00(void), sys_Enable(void);
extern int orig_FUN_004cdd80(void), InsaneTimer_StartThread(void);
extern void orig_FUN_004cde80(void), InsaneTimer_StopThread(void);
extern int __stdcall orig_Mixer_TimerThread(int), InsaneTimer_ThreadProc(int);
extern int orig_FUN_004cdc90(int *, unsigned), sys_timer_module(int *, unsigned);
extern void orig_FUN_004cdce0(void), InsaneTimer_module_terminate(void);
extern int orig_FUN_004cdd10(void), InsaneTimer_Init(void);
extern void orig_FUN_004cdd60(void), InsaneTimer_module_shutdown(void);

/* ---- what they call ---- */
enum { T_CB = 5000, T_GETCLOCK = 1, T_TIMEGET, T_CREATEEVENT, T_WAIT, T_CLOSE, T_CREATETHREAD, T_SETPRIO, T_EXITCODE, T_DEBUGSTR,
       T_SVC_REG = 100, T_SVC_UNREG, T_SVC_GET, T_SVC_FREE, T_SVC_ERR = 108 };
static void *th_getclock;
unsigned FUN_004ce000(void) { return ((unsigned (*)(void))th_getclock)(); }
unsigned sys_GetTime(void) { return ((unsigned (*)(void))th_getclock)(); }

#define IMP(name, tag, nargs) \
    void *imp_##name __asm__("__imp__" #name "@" #nargs "0");
void *imp_timeGetTime __asm__("__imp__timeGetTime@0");
void *imp_CreateEventA __asm__("__imp__CreateEventA@16");
void *imp_WaitForSingleObject __asm__("__imp__WaitForSingleObject@8");
void *imp_CloseHandle __asm__("__imp__CloseHandle@4");
void *imp_CreateThread __asm__("__imp__CreateThread@24");
void *imp_SetThreadPriority __asm__("__imp__SetThreadPriority@8");
void *imp_GetExitCodeThread __asm__("__imp__GetExitCodeThread@8");
void *imp_OutputDebugStringA __asm__("__imp__OutputDebugStringA@4");
__asm__(".globl _timeGetTime@0\n_timeGetTime@0: jmp *__imp__timeGetTime@0\n"
        ".globl _CreateEventA@16\n_CreateEventA@16: jmp *__imp__CreateEventA@16\n"
        ".globl _WaitForSingleObject@8\n_WaitForSingleObject@8: jmp *__imp__WaitForSingleObject@8\n"
        ".globl _CloseHandle@4\n_CloseHandle@4: jmp *__imp__CloseHandle@4\n"
        ".globl _CreateThread@24\n_CreateThread@24: jmp *__imp__CreateThread@24\n"
        ".globl _SetThreadPriority@8\n_SetThreadPriority@8: jmp *__imp__SetThreadPriority@8\n"
        ".globl _GetExitCodeThread@8\n_GetExitCodeThread@8: jmp *__imp__GetExitCodeThread@8\n"
        ".globl _OutputDebugStringA@4\n_OutputDebugStringA@4: jmp *__imp__OutputDebugStringA@4\n");

static void *th_cbs[20];

static uint64_t effseed;
static unsigned effrnd(void) { effseed ^= effseed << 13; effseed ^= effseed >> 7; effseed ^= effseed << 17; return (unsigned)(effseed >> 20); }
static int cb_mode;     /* 0: callbacks only record, 1: they also change their own slot */

static int cb_effect(int tag, unsigned *args)
{
    int slot = (int)args[0];
    if (cb_mode && slot > 0 && slot < 20) {
        Slot *s = &SLOTS[slot];
        switch (effrnd() % 8) {
        case 0: s->period = 1 + effrnd() % 30; break;
        case 1: s->elapsed -= effrnd() % 40; break;
        case 2: s->flags ^= 2; break;
        case 3: s->elapsed = -1000000; break;
        case 4: SLOTS[1 + effrnd() % 19].elapsed += effrnd() % 10; break;
        case 5: FXI32(0x8da878) = effrnd() % 2; break;    /* hold */
        default: break;
        }
    }
    return 0;
}
static int clock_effect(int tag, unsigned *args) { FXU32(0x8da5c8) += 1 + effrnd() % 20; return (int)FXU32(0x8da5c8); }

/* thread test: timeGetTime ticks forward, the 20th wait stops the loop */
static unsigned fake_time;
static int waits;
static int time_effect(int tag, unsigned *args) { fake_time += effrnd() % 25; return (int)fake_time; }
static int wait_effect(int tag, unsigned *args) { if (++waits >= 12 + (int)(effseed & 7)) FXI32(0x8da874) = 0; return 0; }

static void setup_state(void)
{
    int i;
    memset(FXDATA(0x8da540), 0, 0x8da898 - 0x8da540);
    for (i = 1; i < 20; i++) {
        Slot *s = &SLOTS[i];
        if (fx_rnd() % 4) {
            s->cb = th_cbs[i];
            s->period = fx_rnd() % 40;
            s->flags = fx_rnd() % 8;
            s->user = (int)fx_rnd();
            s->busy = (fx_rnd() % 8) == 0;
            s->elapsed = (int)(fx_rnd() % 60) - 5;
            s->busyDeferred = (fx_rnd() % 8) == 0;
            s->total = (int)fx_rnd();
        }
    }
    FXU32(0x8da5c8) = (unsigned)fx_rnd();
    FXU32(0x8da860) = 1 + fx_rnd() % 30;
    FXI32(0x8da878) = (fx_rnd() % 5) == 0;
    FXI32(0x8da87c) = (fx_rnd() % 6) == 0;
    FXI32(0x8da880) = (fx_rnd() % 6) == 0;
    FXI32(0x8da884) = 0;
    FXI32(0x8da88c) = fx_rnd() % 3;
    FXI32(0x8da868) = fx_rnd() % 3;
    FXI32(0x8da870) = fx_rnd() % 3;
    FXI32(0x8da5d0) = (int)fx_rnd();
    FXI32(0x8da5d4) = (int)fx_rnd();
    FXI32(0x8da888) = (int)(fx_rnd() % 2);
    FXI32(0x8da544) = 1 + (int)(fx_rnd() % 500);
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000;
    setvbuf(stdout, 0, _IONBF, 0);
    int neg = argc > 2;
    int i;
    static const int svc_args[16] = {2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int svc[16];

    th_getclock = fx_thunk(T_GETCLOCK, 0, 0);
    fx_effect(T_GETCLOCK, clock_effect);
    imp_timeGetTime = fx_thunk(T_TIMEGET, 0, 1); fx_effect(T_TIMEGET, time_effect);
    imp_CreateEventA = fx_thunk(T_CREATEEVENT, 4, 1); fx_ret(T_CREATEEVENT, 0x1234);
    imp_WaitForSingleObject = fx_thunk(T_WAIT, 2, 1); fx_effect(T_WAIT, wait_effect);
    imp_CloseHandle = fx_thunk(T_CLOSE, 1, 1);
    imp_CreateThread = fx_thunk(T_CREATETHREAD, 6, 1); fx_ret(T_CREATETHREAD, 0x4321); fx_ignmask(T_CREATETHREAD, 0x24);
    imp_SetThreadPriority = fx_thunk(T_SETPRIO, 2, 1);
    imp_GetExitCodeThread = fx_thunk(T_EXITCODE, 2, 1); fx_ignmask(T_EXITCODE, 2);
    imp_OutputDebugStringA = fx_thunk(T_DEBUGSTR, 1, 1); fx_strmask(T_DEBUGSTR, 1);
    for (i = 1; i < 20; i++) { th_cbs[i] = fx_thunk(T_CB + i, 2, 0); fx_effect(T_CB + i, cb_effect); }
    (void)th_cbs;
    /* module manager services (cdecl): [0] register(name, table) [1] unregister(name) [2] get(name, size) [3] free(p) [8] error(msg) */
    svc[0] = (int)(intptr_t)fx_thunk(T_SVC_REG, 2, 0); svc[1] = (int)(intptr_t)fx_thunk(T_SVC_UNREG, 1, 0);
    svc[2] = (int)(intptr_t)fx_thunk(T_SVC_GET, 2, 0); svc[3] = (int)(intptr_t)fx_thunk(T_SVC_FREE, 1, 0);
    svc[8] = (int)(intptr_t)fx_thunk(T_SVC_ERR, 1, 0);
    fx_strmask(T_SVC_REG, 1); fx_strmask(T_SVC_UNREG, 1); fx_strmask(T_SVC_GET, 1); fx_strmask(T_SVC_ERR, 1);
    (void)svc_args;

    fx_region(FXDATA(0x8da540), 8);                  /* workspace pointer, rate */
    fx_region(FXDATA(0x8da5c8), 0x8da8a0 - 0x8da5c8);  /* clock ... slots ... counters (the two jmp_bufs 0x8da548.. are not compared) */
    fx_region(FXDATA(0x4f3c2c), 4);

    for (long it = 0; it < n; it++) {
        int f = getenv("ONLY") ? atoi(getenv("ONLY")) : (int)(it % 14);
        unsigned long long cseed = fx_rnd();
        int ra = 0, rb = 0;
        int a1 = (int)fx_rnd(), a2 = (int)fx_rnd();

        setup_state();
        cb_mode = (fx_rnd() & 1);
        FXU32(0x4f3c2c) = 0;
        FXU32(0x8da5cc) = (unsigned)(uintptr_t)svc;
        /* per function setup */
        if (f == 12) { FXI32(0x8da874) = 1 + (int)(fx_rnd() % 2); FXI32(0x8da858) = 0x4321; }       /* StopThread */
        if (f == 11) { FXI32(0x8da874) = (fx_rnd() % 2); }                                         /* StartThread */
        if (f == 13) { FXI32(0x8da874) = 1; fake_time = (unsigned)fx_rnd(); waits = 0; }           /* ThreadProc */
        fx_clear_queues();
        fx_ret(T_EXITCODE, 1); fx_queue(T_EXITCODE, 1); fx_queue(T_EXITCODE, 0x103); fx_queue(T_EXITCODE, 0x103); fx_queue(T_EXITCODE, 5);
        fx_queue(T_SVC_GET, 1 + (int)(fx_rnd() % 2) * 0x1000); fx_queue(T_SVC_GET, (int)(fx_rnd() % 2) * 0x2000);
        if (f == 13) { fx_queue(T_TIMEGET, 0); }
        fx_save();

#define RUN(CALL_O, CALL_M) do { \
            fx_reset(); effseed = cseed | 1; waits = 0; fake_time = (unsigned)cseed; ra = (CALL_O); fx_snap_a(); \
            fx_restore(); fx_reset(); effseed = cseed | 1; waits = 0; fake_time = (unsigned)cseed; rb = (CALL_M) + neg; } while (0)
        switch (f) {
        case 0: case 1: RUN((orig_Mixer_Update(), 0), (InsaneTimer_Tick(), 0)); break;
        case 2: RUN((orig_Mixer_ServiceVoices(), 0), (InsaneTimer_ServiceDeferred(), 0)); break;
        case 3: RUN((orig_Mixer_ScheduleVoices(), 0), (InsaneTimer_RunDeferred(), 0)); break;
        case 4: RUN(orig_FUN_004cdf10(th_cbs[1], a1, (unsigned)a2, a1 ^ a2), sys_Alloc(th_cbs[1], a1, (unsigned)a2, a1 ^ a2)); break;
        case 5: RUN((orig_FUN_004cdf80(a1 % 24 - 2), 0), (sys_Free(a1 % 24 - 2), 0)); break;
        case 6: RUN((orig_FUN_004cdfa0(a1 % 24 - 2, a2), 0), (sys_Reset(a1 % 24 - 2, a2), 0)); break;
        case 7: RUN((orig_FUN_004cdfd0(a1 & 63), 0), (sys_Delay(a1 & 63), 0)); break;
        case 8: RUN((orig_FUN_004cdef0(), orig_FUN_004cdf00(), orig_FUN_004cdef0(), 0), (sys_Disable(), sys_Enable(), sys_Disable(), 0)); break;
        case 9: RUN(orig_FUN_004cdc90(svc, a1), sys_timer_module(svc, a1)); break;
        case 10: RUN((orig_FUN_004cdce0(), orig_FUN_004cdd10(), orig_FUN_004cdd60(), 0), (InsaneTimer_module_terminate(), InsaneTimer_Init(), InsaneTimer_module_shutdown(), 0)); break;
        case 11: RUN(orig_FUN_004cdd80(), InsaneTimer_StartThread()); break;
        case 12: RUN((orig_FUN_004cde80(), 0), (InsaneTimer_StopThread(), 0)); break;
        case 13: RUN(orig_Mixer_TimerThread(0), InsaneTimer_ThreadProc(0)); break;
        }
        fx_cases++;
        if (ra != rb) fx_fail("return value", it * 100 + f);
        else if (fx_cmp_a() || fx_cmp_log()) fx_fail("state/calls", it * 100 + f);
        if (f == 9 || f == 10) {   /* the service table pointer is set up by Register: Init/Shutdown above use it */
            ;
        }
    }
    printf("timer cases %ld  differences %ld\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
