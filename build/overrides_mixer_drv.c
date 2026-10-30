/* Readable C for the Smush timer module, the DirectSound stream driver and its helpers (GRIMFANDANGO.EXE
 * 0x004c0ed0 - 0x004d2fb0): the two LEC modules "insane_timer" and "insane_dsnd" of the Smush movie player.
 *
 *   InsaneTimer_*   a thread that wakes every 16 ms and runs up to 19 periodic callbacks ("TIMER insane")
 *   DsndDriver_*    DirectSound output: a looping stream buffer of 0x1800 byte blocks that DSound_FillStreamBuffer
 *                   (a timer callback) refills from the software mixer behind the play cursor ("SNDDRIVER insane_dsnd")
 *   Mixer_*         the software mixer itself is in overrides_mixer.c
 *
 * Every function is a transcription of the original instructions; build/mixdiff/ holds the differential tests that run
 * the original machine code and this code against the same state and compare the results, the memory and the sequence
 * of calls into DirectSound / the module manager / Win32 (docs/notes/mixer.md).
 * tools/build_src.py puts the decompiled text of every function defined here under `#if 0`. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

/* COM method call through the vtable at byte offset `off` */
#define COMX(obj, off, ...) ((int (__stdcall *)())(*(void ***)(obj))[(off) / 4])((obj), ##__VA_ARGS__)

/* IDirectSound vtable offsets */
#define DS_RELEASE            0x08
#define DS_CREATESOUNDBUFFER  0x0c
#define DS_SETCOOPERATIVELEVEL 0x18
/* IDirectSoundBuffer vtable offsets */
#define DSB_RELEASE           0x08
#define DSB_GETCURRENTPOSITION 0x10
#define DSB_GETVOLUME         0x18
#define DSB_LOCK              0x2c
#define DSB_PLAY              0x30
#define DSB_SETFORMAT         0x38
#define DSB_SETVOLUME         0x3c
#define DSB_UNLOCK            0x4c

/* the module manager's service table (g_pDsndServices / g_pTimerServices): cdecl function pointers */
typedef void *(*SvcGetModule)(const char *name, uint arg);
typedef void (*SvcName)(const char *name);
typedef void (*SvcLog)(const char *fmt, ...);

/* ===================================================================================================================
 *  Insane timer module
 * =================================================================================================================== */

/* one timer; the table has 20 entries, entry 0 is never used (ids start at 1) */
typedef struct TimerSlot {
    void (*callback)(int slot, int user);   /* 0 = free */
    int period;                             /* ticks between calls (0 = stopped) */
    uint flags;                             /* 1: run first, in the order of the table; 2: one shot (period is zeroed before the call);
                                               4: run by InsaneTimer_RunDeferred; none: run after the flag-1 timers */
    int user;                               /* second argument of the callback */
    int busy;                               /* callback of a flag-0 timer is running */
    int elapsed;                            /* ticks since the last call */
    int busyDeferred;                       /* callback of a flag-4 timer is running */
    int total;                              /* ticks since the slot was set up */
} TimerSlot;

extern TimerSlot g_aTimerSlots[20] __asm__("_DAT_008da5d8");

extern int g_nTimerLastTime __asm__("_UINT_008da864");     /* timeGetTime() of the last tick (advanced by 16 per tick) */
extern int g_nTimerSavedBusy __asm__("_UINT_008da868");
extern int g_nTimerInTick __asm__("_DAT_008da86c");
extern int g_nTimerSavedBusy2 __asm__("_UINT_008da870");
extern int g_nTimerThread __asm__("_UINT_008da858");
extern uint g_dwTimerWorkspaceSize __asm__("_UINT_008da85c");
extern int g_nMixerRunning __asm__("_UINT_008da874");
extern int g_nTimerHold __asm__("_UINT_008da878");        /* InsaneTimer_Hold counter: nothing runs while nonzero */
extern int g_nTimerBusyA __asm__("_UINT_008da87c");
extern int g_nTimerBusyB __asm__("_UINT_008da880");
extern int g_nTimerDeferredFlag __asm__("_UINT_008da884");
extern int g_nTimerRunningDeferred __asm__("_DAT_008da888");
extern int g_nTimerSkip __asm__("_UINT_008da88c");
extern int g_nTimerRate __asm__("_UINT_008da544");       /* ticks per second the workspace was started with (300) */
extern void *g_pTimerWorkspace __asm__("_UINT_008da540");
extern int g_nTimerState __asm__("_DAT_008da5d0");
extern int g_nTimerStateSrc __asm__("_UINT_008da5d4");

int InsaneTimer_Register(int *services, uint workspaceSize)
{
    g_pTimerServices = services;
    g_dwTimerWorkspaceSize = workspaceSize;
    ((void (*)(const char *, void *))services[0])(s_LECMODULE_insane_timer_004f3c40, &g_apfnInsaneTimerModule);
    ((void (*)(const char *, void *))g_pTimerServices[0])(s_TIMER_insane_004f3c30, &g_apfnInsaneTimerInterface);
    g_nTimerRate = 300;
    return 0;
}

void InsaneTimer_Unregister(void)
{
    ((void (*)(const char *))g_pTimerServices[1])(s_TIMER_insane_004f3c30);
    ((void (*)(const char *))g_pTimerServices[1])(s_LECMODULE_insane_timer_004f3c40);
}

/* The thread: ticks every 16 ms of timeGetTime, sleeps (an event that is never set) for the time to the next tick,
 * at most 10 ms at a time. */
undefined * __stdcall InsaneTimer_ThreadProc(int unused)
{
    int event = CreateEventA(0, 1, 0, 0);
    int wait;

    g_nTimerLastTime = timeGetTime();
    while (g_nMixerRunning != 0) {
        int now = timeGetTime();
        if ((int)(now - g_nTimerLastTime) < 0x11) {
            wait = 0x10 - (now - g_nTimerLastTime);
        } else {
            g_nTimerLastTime += 0x10;
            InsaneTimer_Tick();
            wait = 10;
        }
        if (wait == 0)
            wait = 1;
        if (10 < wait)
            wait = 10;
        WaitForSingleObject(event, wait);
    }
    CloseHandle(event);
    return (undefined *)0;
}

/* Reference counted: the first caller clears the timers and starts the thread. */
int InsaneTimer_StartThread(void)
{
    int first = g_nMixerRunning++ == 0;
    if (first) {
        int i;
        int id;
        for (i = 1; i < 20; i++)
            g_aTimerSlots[i].callback = 0;
        g_dwTimerStep = 0x4dae;
        g_nTimerThread = CreateThread(0, 0, InsaneTimer_ThreadProc, 0, 0, &id);
        SetThreadPriority(g_nTimerThread, 2);
        _DAT_004f3c2c = 0xffffffff;
    }
    return 0;
}

/* The last caller waits for the thread to end (it leaves its loop when the counter reaches 0). */
void InsaneTimer_StopThread(void)
{
    if (--g_nMixerRunning == 0) {
        uint code;
        int ok = GetExitCodeThread(g_nTimerThread, &code);
        while (ok != 0 && code == 0x103) {      /* STILL_ACTIVE */
            OutputDebugStringA("Waiting for timer thread to exit!\n");
            ok = GetExitCodeThread(g_nTimerThread, &code);
        }
        CloseHandle(g_nTimerThread);
    }
}

int InsaneTimer_Init(void)
{
    g_pTimerWorkspace = ((void *(*)(const char *, uint))g_pTimerServices[2])(s_MEMORY_workspace_004f14ec, g_dwTimerWorkspaceSize);
    if (g_pTimerWorkspace == 0) {
        ((void (*)(const char *))g_pTimerServices[8])(s_Timer_Module__Cannot_allocate_me_004f3c58);
        return 0xffffffff;
    }
    return InsaneTimer_StartThread();
}

void InsaneTimer_Shutdown(void)
{
    ((void (*)(void *))g_pTimerServices[3])(g_pTimerWorkspace);
    InsaneTimer_StopThread();
}

void InsaneTimer_Hold(void)
{
    g_nTimerHold++;
}

void InsaneTimer_Release(void)
{
    g_nTimerHold--;
}

/* callback(slot, user): returns the slot (1..19) or 0 when the table is full */
int InsaneTimer_AddTimer(void *callback, int period, uint flags, int user)
{
    int i;

    for (i = 1; i < 20; i++) {
        TimerSlot *t = &g_aTimerSlots[i];
        if (t->callback == 0) {
            t->busyDeferred = 0;
            t->elapsed = 0;
            t->user = user;
            t->flags = flags;
            t->period = period;
            t->callback = callback;
            t->busy = 0;
            t->total = 0;
            return i;
        }
    }
    return 0;
}

void InsaneTimer_RemoveTimer(int slot)
{
    if (0 < slot && slot < 0x14)
        g_aTimerSlots[slot].callback = 0;
}

void InsaneTimer_SetPeriod(int slot, int period)
{
    if (0 < slot && slot < 0x14) {
        g_aTimerSlots[slot].period = period;
        g_aTimerSlots[slot].elapsed = 0;
    }
}

/* Runs the clock for `ticks` ticks of InsaneTimer_GetClock, one step at a time. */
void InsaneTimer_Run(int ticks)
{
    int start = g_nTimerClock;
    int end = ticks + g_nTimerClock;

    while (g_nTimerClock < end) {
        InsaneTimer_GetClock();
        if (g_nTimerClock < start)
            break;
    }
}

/* Runs the callbacks of timer `i` while it is due: `elapsed >= period`.  A one-shot timer is stopped first. */
static void timer_run_due(TimerSlot *t, int i)
{
    do {
        t->elapsed -= t->period;
        if (t->flags & 2) {
            t->period = 0;
            t->callback(i, t->user);
            break;
        }
        t->callback(i, t->user);
    } while (t->period <= t->elapsed);
}

/* One step of the clock (g_dwTimerStep ticks): first the flag-1 timers, then the plain ones, then the deferred ones are
 * scheduled (InsaneTimer_ServiceDeferred).  Does nothing while InsaneTimer_Hold is active. */
void InsaneTimer_Tick(void)
{
    int i;
    TimerSlot *t;

    g_nTimerClock += g_dwTimerStep;
    if (g_nTimerHold != 0)
        return;

    g_nTimerInTick = 1;
    g_nTimerSavedBusy2 = g_nTimerSavedBusy;
    g_nTimerSavedBusy = 0;
    for (i = 1, t = &g_aTimerSlots[1]; i < 20; i++, t++) {
        if (t->callback != 0) {
            t->elapsed += g_dwTimerStep;
            t->total += g_dwTimerStep;
            if ((t->flags & 5) == 1 && t->period != 0 && t->elapsed >= t->period)
                timer_run_due(t, i);
        }
    }
    for (i = 1, t = &g_aTimerSlots[1]; i < 20; i++, t++) {
        if (t->callback != 0 && (t->flags & 5) == 0 && t->period != 0 && t->busy == 0) {
            t->busy = 1;
            if (t->elapsed >= t->period)
                timer_run_due(t, i);
            t->busy = 0;
        }
    }
    g_nTimerSavedBusy = g_nTimerSavedBusy2;
    g_nTimerInTick = 0;
    if (g_nTimerBusyB == 0 && g_nTimerBusyA == 0) {
        g_nTimerBusyB = 1;
        InsaneTimer_ServiceDeferred();
        g_nTimerBusyB = 0;
    }
}

/* Runs the deferred (flag 4) timers once.  The original brackets this with a setjmp / longjmp pair on two jmp_bufs of
 * its own (DAT_008da548 and DAT_008da588); nothing else ever jumps to them, so the only effect is the final
 * `g_nTimerSavedBusy = 0`; the longjmp to the second buffer is only reached when g_nTimerDeferredFlag is set, which
 * nothing does. */
void InsaneTimer_ServiceDeferred(void)
{
    if (g_nTimerSkip == 0 || --g_nTimerSkip == 0) {
        g_nTimerDeferredFlag = 0;
        g_nTimerRunningDeferred = 1;
        InsaneTimer_RunDeferred();
        g_nTimerRunningDeferred = 0;
        g_nTimerState = g_nTimerStateSrc;
        g_nTimerSavedBusy = 0;
    }
}

void InsaneTimer_RunDeferred(void)
{
    int i;
    TimerSlot *t;

    for (i = 1, t = &g_aTimerSlots[1]; i < 20; i++, t++) {
        t->busyDeferred = 1;
        if (t->callback != 0 && (t->flags & 5) == 4 && t->period != 0 && t->elapsed >= t->period)
            timer_run_due(t, i);
        t->busyDeferred = 0;
    }
}


/* ===================================================================================================================
 *  DirectSound stream driver
 * =================================================================================================================== */

extern int *g_pDsndMemSvc __asm__("_UINT_008db208");              /* "MEMORY mixertable": allocator for Mixer_Init */
extern uint g_dwDsndModuleSize __asm__("_UINT_008db430");
extern int g_aiStreamVolumeTable[128] __asm__("_UINT_008db210");  /* DirectSound volume (1/100 dB) for 0..127 */
extern byte g_abStreamScratch[0x1800] __asm__("_UINT_008db438");  /* mixes a block that wraps around the buffer end */
extern int g_nStreamPlayPos __asm__("_UINT_008db428");
extern int g_nStreamWritePos __asm__("_DAT_008db418");
extern int g_bStreamBufferBusy __asm__("_DAT_008dcc4c");
extern int g_bStreamPrimaryOwned __asm__("_UINT_008dcc50");
extern int g_bStreamVolumeTableBuilt __asm__("_UINT_008dcc58");
extern byte g_StreamFormat[0x18] __asm__("_DAT_004f3fa8");        /* WAVEFORMATEX set on the primary buffer */
extern byte g_StreamBufferFormat[0x18] __asm__("_DAT_004f3fc0");  /* WAVEFORMATEX of the stream buffer */

typedef struct DsndClock {      /* TIMER clock interface (cdecl) */
    int (*addTimer)(void *callback, int period, uint flags, int user);
    void (*removeTimer)(int id);
    void *unused[2];
    void (*setPeriod)(int id, int period);
} DsndClock;

int DsndDriver_Register(int *services, uint moduleSize)
{
    g_pDsndServices = services;
    g_dwDsndModuleSize = moduleSize;
    ((void (*)(const char *, void *))services[0])(s_LECMODULE_insane_dsnd_004f3fec, &g_apfnDsndDriverModule);
    ((void (*)(const char *, void *))g_pDsndServices[0])(s_SNDDRIVER_insane_dsnd_004f3fd4, &g_apfnDsndDriverInterface);
    _DAT_008db414 = 0xffffffff;
    _DAT_008db20c = 0xffffffff;
    _DAT_008dcc38 = 0xffffffff;
    _DAT_008db42c = 0xffffffff;
    return 0;
}

void DsndDriver_Unregister(void)
{
    ((void (*)(const char *))g_pDsndServices[1])(s_SNDDRIVER_insane_dsnd_004f3fd4);
    ((void (*)(const char *))g_pDsndServices[1])(s_LECMODULE_insane_dsnd_004f3fec);
}

int DsndDriver_Init(void)
{
    g_pDsndClock = ((int *(*)(const char *, uint))g_pDsndServices[2])(s_TIMER_clock_004f4054, g_dwDsndModuleSize);
    if (g_pDsndClock == 0) {
        ((void (*)(const char *))g_pDsndServices[8])(s_DirectSoundDriver_Module__Cannot_004f4018);
        return 0xffffffff;
    }
    g_pDsndMemSvc = ((int *(*)(const char *, uint))g_pDsndServices[2])(s_MEMORY_mixertable_004f4004, g_dwDsndModuleSize);
    if (g_pDsndMemSvc == 0) {
        ((void (*)(const char *))g_pDsndServices[8])(s_DirectSoundDriver_Module__Cannot_004f4018);
        return 0xffffffff;
    }
    return 0;
}

void DsndDriver_Shutdown(void)
{
    ((void (*)(void *))g_pDsndServices[3])(g_pDsndClock);
    ((void (*)(void *))g_pDsndServices[3])(g_pDsndMemSvc);
}

/* rate: sample rate (at least 22050); mix: callback (frames, Mixer_MixVoiceByFormat) that mixes into the accumulator.
 * Returns 0 or -1. */
int DsndDriver_Open(int rate, int unused, void *mix)
{
    DsndClock *clock;

    _DAT_008dcc3c = 0;
    if (rate < 0x5622)
        rate = 0x5622;
    if (DsndDriver_InitDirectSound() != 0)
        return 0xffffffff;
    if (Mixer_Init(g_pDsndMemSvc, 4, 0x400) != 0)
        return 0xffffffff;
    g_pfnStreamMix = mix;
    g_dwStreamRate = rate;
    clock = (DsndClock *)g_pDsndClock;
    g_nStreamTimerId = clock->addTimer(DSound_FillStreamBuffer, 0x1234dc / ((rate + ((rate >> 31) & 0x3ff)) >> 10), 2, 0);
    return 0;
}

void DsndDriver_Close(void)
{
    if (g_nStreamTimerId != 0)
        ((DsndClock *)g_pDsndClock)->removeTimer(g_nStreamTimerId);
    g_nStreamTimerId = 0;
    Mixer_Free(g_pDsndMemSvc);
    DsndDriver_ReleaseDirectSound();
}

/* volume 0..127 */
void DsndDriver_SetVolume(uint volume)
{
    if (g_bStreamVolumeTableBuilt == 0) {
        /* 1/100 dB: a coarse curve for the lowest steps, then three linear ramps */
        static const int head[9] = {-10000, -7000, -6000, -5200, -5000, -4500, -4200, -4100, -4000};
        int i;
        for (i = 0; i < 9; i++)
            g_aiStreamVolumeTable[i] = head[i];
        for (i = 0; i < 24; i++)
            g_aiStreamVolumeTable[8 + i] = (i * 2000) / 0x17 - 4000;
        for (i = 0; i < 32; i++)
            g_aiStreamVolumeTable[32 + i] = (i * 1000) / 0x1f - 2000;
        for (i = 0; i < 64; i++)
            g_aiStreamVolumeTable[64 + i] = (i * 1000) / 0x3f - 1000;
        g_bStreamVolumeTableBuilt = 1;
    }
    g_dwStreamVolume = volume & 0x7f;
    /* (the original also tests for < 0 and > 0x7f, which cannot happen after the mask) */
    COMX(g_pStreamDSBuffer, DSB_SETVOLUME, g_aiStreamVolumeTable[g_dwStreamVolume]);
}

uint DsndDriver_GetVolume(void)
{
    return g_dwStreamVolume;
}

int DsndDriver_GetSampleRate(void)
{
    return 0x5622;
}

/* Creates the DirectSound object, takes the primary buffer (22050 Hz 16 bit stereo), saves its volume and makes the
 * stream buffer.  Returns 0 or -1. */
int DsndDriver_InitDirectSound(void)
{
    int hr;
    struct { uint size, flags, bytes, reserved, format; } desc;

    if (g_pStreamDS != 0)
        return 0;
    hr = DirectSoundCreate(0, &g_pStreamDS, 0);
    if (hr != 0) {
        g_pStreamDS = 0;
        ((void (*)(const char *, ...))Lua_Stub)(s_Cannot_create_DirectSound_object_004f40d0, hr);
        return 0xffffffff;
    }
    hr = COMX(g_pStreamDS, DS_SETCOOPERATIVELEVEL, Win_GetMainHwnd(), 3);
    if (hr != 0) {
        ((void (*)(const char *, ...))Lua_Stub)(s_DirectSound__Error__08X_while_se_004f4098, hr);
        return 0xffffffff;
    }
    desc.size = 0x14;
    desc.flags = 0x81;                  /* DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME */
    desc.bytes = 0;
    desc.reserved = 0;
    desc.format = 0;
    hr = COMX(g_pStreamDS, DS_CREATESOUNDBUFFER, &desc, &g_pStreamDSPrimary, 0);
    if (hr != 0) {
        ((void (*)(const char *, ...))Lua_Stub)(s_DirectSound__Error__08X_while_cr_004f4060, hr);
        return 0xffffffff;
    }
    if (COMX(g_pStreamDSPrimary, DSB_SETFORMAT, g_StreamFormat) != 0)
        return 0xffffffff;
    if (COMX(g_pStreamDSPrimary, DSB_GETVOLUME, &g_nStreamSavedVolume) != 0)
        return 0xffffffff;
    if (COMX(g_pStreamDSPrimary, DSB_SETVOLUME, 0) != 0)
        return 0xffffffff;
    DsndDriver_CreateStreamBuffer(3);
    g_bStreamPrimaryOwned = 1;
    return 0;
}

/* blocks: 3..16 blocks of 0x1800 bytes; the buffer is cleared and played in a loop */
void DsndDriver_CreateStreamBuffer(int blocks)
{
    struct { uint size, flags, bytes, reserved; void *format; } desc;
    void *p1, *p2;
    uint n1, n2;

    g_bStreamBufferBusy = 1;
    if (g_pStreamDSBuffer != 0)
        COMX(g_pStreamDSBuffer, DSB_RELEASE);
    g_pStreamDSBuffer = 0;
    if (blocks < 3)
        blocks = 3;
    if (blocks > 0x10)
        blocks = 0x10;
    g_nStreamBlocks = blocks;
    desc.size = 0x14;
    desc.flags = 0x10080;               /* DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 */
    desc.bytes = blocks * 0x1800;
    desc.reserved = 0;
    desc.format = g_StreamBufferFormat;
    if (COMX(g_pStreamDS, DS_CREATESOUNDBUFFER, &desc, &g_pStreamDSBuffer, 0) == 0) {
        COMX(g_pStreamDSBuffer, DSB_SETVOLUME, 0);
        if (COMX(g_pStreamDSBuffer, DSB_LOCK, 0, g_nStreamBlocks * 0x1800, &p1, &n1, &p2, &n2, 0) == 0) {
            memset(p1, 0, n1);
            if (p2 != 0)
                memset(p2, 0, n2);
            COMX(g_pStreamDSBuffer, DSB_UNLOCK, p1, n1, p2, n2);
        }
        COMX(g_pStreamDSBuffer, DSB_PLAY, 0, 0, 1);     /* DSBPLAY_LOOPING */
    }
    g_bStreamBufferBusy = 0;
}

void DsndDriver_ReleaseDirectSound(void)
{
    if (g_pStreamDSBuffer != 0)
        COMX(g_pStreamDSBuffer, DSB_RELEASE);
    g_pStreamDSBuffer = 0;
    if (g_pStreamDSPrimary != 0 && g_bStreamPrimaryOwned != 0) {
        COMX(g_pStreamDSPrimary, DSB_SETVOLUME, g_nStreamSavedVolume);
        COMX(g_pStreamDSPrimary, DSB_RELEASE);
        g_pStreamDSPrimary = 0;
        g_bStreamPrimaryOwned = 0;
    }
    if (g_pStreamDS != 0)
        COMX(g_pStreamDS, DS_RELEASE);
    g_pStreamDS = 0;
}

/* Index of the block the play cursor is in, or -1 */
int DSound_GetPlayBlock(void)
{
    if (g_pStreamDSBuffer != 0 && COMX(g_pStreamDSBuffer, DSB_GETCURRENTPOSITION, &g_nStreamPlayPos, &g_nStreamWritePos) == 0)
        return (g_nStreamPlayPos / 0x1800) % g_nStreamBlocks;
    return -1;
}

/* The timer callback that keeps the stream buffer filled: if the play cursor has left the block behind the one written
 * last, locks the next block, mixes into it (through the scratch buffer when the lock wraps around the end of the
 * buffer) and unlocks it.  Finally re-arms the timer. */
void DSound_FillStreamBuffer(void)
{
    int block = DSound_GetPlayBlock();

    if (block != -1 && block != (g_nStreamLastBlock + 1) % g_nStreamBlocks) {
        void *p1, *p2;
        uint n1, n2;

        if (g_nStreamLastBlock < 0)
            g_nStreamLastBlock = block;
        g_nStreamLastBlock = (g_nStreamLastBlock + 1) % g_nStreamBlocks;
        if (COMX(g_pStreamDSBuffer, DSB_LOCK, g_nStreamLastBlock * 0x1800, 0x1800, &p1, &n1, &p2, &n2, 0) == 0) {
            int frames;
            void *out;
            int wraps = p2 != 0 && n2 != 0;

            if (wraps) {
                frames = 0x600;
                out = g_abStreamScratch;
            } else {
                frames = ((int)n1 + (((int)n1 >> 31) & 3)) >> 2;
                out = p1;
            }
            Mixer_ClearAccumulator();
            ((void (*)(int, void *))g_pfnStreamMix)(frames, Mixer_MixVoiceByFormat);
            Mixer_Output(out, frames);
            if (wraps) {
                memcpy(p1, g_abStreamScratch, n1);
                memcpy(p2, g_abStreamScratch + n1, n2);
            }
            COMX(g_pStreamDSBuffer, DSB_UNLOCK, p1, n1, p2, n2);
        }
    }
    ((DsndClock *)g_pDsndClock)->setPeriod(g_nStreamTimerId, 0x1234dc / (((int)g_dwStreamRate + (((int)g_dwStreamRate >> 31) & 0x3ff)) >> 10));
}

/* Releases the DirectSound objects of the main sound system (DSound_Init) */
void DSound_Shutdown(void)
{
    if (PTR_008d3674 != 0) {
        COMX(PTR_008d3674, DS_RELEASE);
        PTR_008d3674 = 0;
    }
    if (g_pDSoundPrimary != 0) {
        COMX(g_pDirectSound, DS_SETCOOPERATIVELEVEL, UINT_008d3654, 2);
        COMX(g_pDSoundPrimary, DSB_SETVOLUME, UINT_008d3658);
        COMX(g_pDSoundPrimary, DSB_RELEASE);
        g_pDSoundPrimary = 0;
    }
    if (g_pDirectSound != 0) {
        COMX(g_pDirectSound, DS_RELEASE);
        g_pDirectSound = 0;
    }
}

/* IDirectSoundBuffer::SetVolume on the primary buffer: the attenuation in 1/100 dB is (1 - v)^2 * -5000 for a
 * volume v in 0..1; `volume` carries the bits of that float (the caller, DSound_Init, passes the global as an int). */
void DSound_SetPrimaryVolume(int volume)
{
    if (g_pDSoundPrimary != 0) {
        union { int i; float f; } v;
        long double d;
        int attenuation;
        void *hwnd;

        v.i = volume;
        d = (long double)1.0f - v.f;
        attenuation = (int)(long long)(d * d * (long double)-5000.0f);    /* _ftol: 64-bit truncation, low dword */
        hwnd = Win_GetMainHwnd();
        if (COMX(g_pDirectSound, DS_SETCOOPERATIVELEVEL, hwnd, 2) >= 0) {
            COMX(g_pDSoundPrimary, DSB_SETVOLUME, attenuation);
            COMX(g_pDirectSound, DS_SETCOOPERATIVELEVEL, hwnd, 3);
        }
    }
}

/* ===================================================================================================================
 *  memcpy / memset of the Smush code.  Hand-written assembly in the original (cdecl, dst / src / count at ebp+8..): the
 *  fill routine pops the wrong registers when the count is not a multiple of 4 and would crash there; nothing calls it
 *  (or its wrapper), the C versions simply fill / copy.
 * =================================================================================================================== */

void Dsnd_MemCopy(void *dst, void *src, uint n)
{
    memcpy(dst, src, n);
}

void Dsnd_MemFill(void *dst, int value, uint n)
{
    memset(dst, (byte)value, n);
}

void Dsnd_MemCopyCdecl(void *dst, void *src, uint n)
{
    Dsnd_MemCopy(dst, src, n);
}

void Dsnd_MemFillCdecl(void *dst, int value, uint n)
{
    Dsnd_MemFill(dst, value, n);
}

/* the lecsmush copy: unaligned head bytes first, then dwords */
void Insane_MemCopy(void *dst, void *src, uint n)
{
    memcpy(dst, src, n);
}

void Insane_MemCopyCdecl(void *dst, void *src, uint n)
{
    Insane_MemCopy(dst, src, n);
}

#endif /* GRIM_EXE */
