/* Readable C for the Smush timer module, the DirectSound stream driver and its helpers (GRIMFANDANGO.EXE
 * 0x004c0ed0 - 0x004d2fb0): the two LEC modules "insane_timer" and "insane_dsnd" of the Smush movie player.
 *
 *   InsaneTimer_*   a thread that wakes every 16 ms and runs up to 19 periodic callbacks ("TIMER insane")
 *   DsndDriver_*    DirectSound output: a looping stream buffer of 0x1800 byte blocks that dsn_fill_thread
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

/* the module manager's service table (g_pDsndDriver_share_services / g_pInsaneTimer_share_services): cdecl function pointers */
typedef void *(*SvcGetModule)(const char *name, uint arg);
typedef void (*SvcName)(const char *name);
typedef void (*SvcLog)(const char *fmt, ...);

/* ==== GRIM_SIMTIME: movies (SMUSH) in game time =======================================================================
 * The scripted runs give every frame a fixed game time (GRIM_SIMTIME ms) and run many times faster than real time, but SMUSH
 * paces itself with the insane timer: a thread that runs InsaneTimer_Tick (the movie's frame and sound callbacks) every 16 ms
 * of timeGetTime. A movie of 5 s therefore lasted 5 s of real time, hundreds of frames of game time. With GRIM_SIMTIME set:
 *   - the timer thread no longer ticks; GRIM_SmushSimFrame(ms), called by Main_Service once per frame before the frame runs,
 *     ticks once per 16 ms of game time on the main thread;
 *   - sys_Delay (waits for the clock to move by n ticks) ticks itself, or it would wait forever;
 *   - the movie's sound is mixed into a DirectSound ring (dsn_fill_thread) when the play cursor has left a block, and the
 *     player keeps the picture in step with the sound: the play cursor (DSound_GetPlayBlock) moves with game time too
 *     (22050 Hz, 16 bit, stereo), and the ring is muted (it is filled faster than it plays).
 * The same as grim_tools' grimlaunch smushtime patch (launcher/grimlaunch.cpp), which the clean room's reference was
 * recorded with. Off without GRIM_SIMTIME and with GRIM_SMUSH_REALTIME=1. */
extern int GRIM_SimTime(void);
extern char *GRIM_mixdrv_getenv(const char *) __asm__("_getenv");

static unsigned g_smushSimPos;   /* the simulated play cursor of the stream, in thousandths of a byte (within the ring) */
static int g_smushSimAcc;        /* game ms not yet turned into 16 ms ticks */

int GRIM_SmushSimOn(void)
{
    static int on = -1;
    if (on < 0) {
        const char *rt = GRIM_mixdrv_getenv("GRIM_SMUSH_REALTIME");
        on = GRIM_SimTime() > 0 && !(rt != 0 && rt[0] == '1');
    }
    return on;
}

void GRIM_SmushSimFrame(int ms)
{
    unsigned ring;

    if (!GRIM_SmushSimOn())
        return;
    ring = (unsigned)g_nStreamBlocks * (0x1800u * 1000u);
    if (ring != 0) {
        g_smushSimPos = (g_smushSimPos + (unsigned)ms * (22050u * 4u)) % ring;
        if (g_pStreamDSBuffer != 0)
            ((int (__stdcall *)(void *, int))(*(void ***)g_pStreamDSBuffer)[0x3c / 4])(g_pStreamDSBuffer, -10000);   /* SetVolume */
    }
    g_smushSimAcc += ms;
    while (g_smushSimAcc >= 16) {
        g_smushSimAcc -= 16;
        InsaneTimer_Tick();
    }
}
/* ==== end GRIM_SIMTIME ================================================================================================ */

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

extern int g_nTimerLastTime __asm__("_g_dwTimer_thread_lastTime");     /* timeGetTime() of the last tick (advanced by 16 per tick) */
extern int g_nTimerSavedBusy __asm__("_UINT_008da868");
extern int g_nTimerInTick __asm__("_DAT_008da86c");
extern int g_nTimerSavedBusy2 __asm__("_UINT_008da870");
extern int g_nTimerThread __asm__("_UINT_008da858");
extern uint g_dwTimerWorkspaceSize __asm__("_g_dwInsaneTimer_share_config");
extern int g_nMixerRunning __asm__("_UINT_008da874");
extern int g_nTimerHold __asm__("_g_dwSys_disable_flag");        /* sys_Disable counter: nothing runs while nonzero */
extern int g_nTimerBusyA __asm__("_UINT_008da87c");
extern int g_nTimerBusyB __asm__("_UINT_008da880");
extern int g_nTimerDeferredFlag __asm__("_UINT_008da884");
extern int g_nTimerRunningDeferred __asm__("_DAT_008da888");
extern int g_nTimerSkip __asm__("_UINT_008da88c");
extern int g_nTimerRate __asm__("_g_dwTimer_rate");       /* ticks per second the workspace was started with (300) */
extern void *g_pTimerWorkspace __asm__("_g_dwInsaneTimer_memory_services");
extern int g_nTimerState __asm__("_DAT_008da5d0");
extern int g_nTimerStateSrc __asm__("_UINT_008da5d4");

/* The thread: ticks every 16 ms of timeGetTime, sleeps (an event that is never set) for the time to the next tick,
 * at most 10 ms at a time. */
undefined * __stdcall timer_thread(int unused)
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
            if (!GRIM_SmushSimOn())             /* GRIM_SIMTIME: Main_Service ticks it by game time */
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
        g_dwSys_timer_count = 0x4dae;
        g_nTimerThread = CreateThread(0, 0, timer_thread, 0, 0, &id);
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

/* callback(slot, user): returns the slot (1..19) or 0 when the table is full */
int sys_Alloc(void *callback, int period, uint flags, int user)
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

/* Runs the clock for `ticks` ticks of sys_GetTime, one step at a time. */
void sys_Delay(int ticks)
{
    int start = g_nSys_global_timer;
    int end = ticks + g_nSys_global_timer;

    if (GRIM_SmushSimOn()) {                    /* GRIM_SIMTIME: the thread does not tick, so tick here */
        while (g_nSys_global_timer < end)
            InsaneTimer_Tick();
        return;
    }
    while (g_nSys_global_timer < end) {
        sys_GetTime();
        if (g_nSys_global_timer < start)
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

/* One step of the clock (g_dwSys_timer_count ticks): first the flag-1 timers, then the plain ones, then the deferred ones are
 * scheduled (sys_timer_dispatcher).  Does nothing while sys_Disable is active. */
void InsaneTimer_Tick(void)
{
    int i;
    TimerSlot *t;

    g_nSys_global_timer += g_dwSys_timer_count;
    if (g_nTimerHold != 0)
        return;

    g_nTimerInTick = 1;
    g_nTimerSavedBusy2 = g_nTimerSavedBusy;
    g_nTimerSavedBusy = 0;
    for (i = 1, t = &g_aTimerSlots[1]; i < 20; i++, t++) {
        if (t->callback != 0) {
            t->elapsed += g_dwSys_timer_count;
            t->total += g_dwSys_timer_count;
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
        sys_timer_dispatcher();
        g_nTimerBusyB = 0;
    }
}

/* Runs the deferred (flag 4) timers once.  The original brackets this with a setjmp / longjmp pair on two jmp_bufs of
 * its own (DAT_008da548 and DAT_008da588); nothing else ever jumps to them, so the only effect is the final
 * `g_nTimerSavedBusy = 0`; the longjmp to the second buffer is only reached when g_nTimerDeferredFlag is set, which
 * nothing does. */
void sys_timer_dispatcher(void)
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

extern int *g_pDsndMemSvc __asm__("_g_dwDsndDriver_memory_services");              /* "MEMORY mixertable": allocator for sou_mixer_initialize */
extern uint g_dwDsndModuleSize __asm__("_g_dwDsndDriver_share_config");
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

/* rate: sample rate (at least 22050); mix: callback (frames, sou_mixer_mix) that mixes into the accumulator.
 * Returns 0 or -1. */
int dsn_initialize(int rate, int unused, void *mix)
{
    DsndClock *clock;

    _DAT_008dcc3c = 0;
    if (rate < 0x5622)
        rate = 0x5622;
    if (DsndDriver_InitDirectSound() != 0)
        return 0xffffffff;
    if (sou_mixer_initialize(g_pDsndMemSvc, 4, 0x400) != 0)
        return 0xffffffff;
    g_pfnStreamMix = mix;
    g_dwStreamRate = rate;
    clock = (DsndClock *)g_pDsndDriver_timer_services;
    g_nStreamTimerId = clock->addTimer(dsn_fill_thread, 0x1234dc / ((rate + ((rate >> 31) & 0x3ff)) >> 10), 2, 0);
    return 0;
}

/* volume 0..127 */
void dsn_setvol(uint volume)
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
    g_dwCurrentVol = volume & 0x7f;
    /* (the original also tests for < 0 and > 0x7f, which cannot happen after the mask) */
    COMX(g_pStreamDSBuffer, DSB_SETVOLUME, g_aiStreamVolumeTable[g_dwCurrentVol]);
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

/* Index of the block the play cursor is in, or -1 */
int DSound_GetPlayBlock(void)
{
    if (GRIM_SmushSimOn()) {                    /* GRIM_SIMTIME: the cursor GRIM_SmushSimFrame moves */
        unsigned pos;
        if (g_pStreamDSBuffer == 0)
            return -1;
        pos = g_smushSimPos / 1000;
        g_nStreamPlayPos = pos;
        return (int)((pos / 0x1800) % (unsigned)g_nStreamBlocks);
    }
    if (g_pStreamDSBuffer != 0 && COMX(g_pStreamDSBuffer, DSB_GETCURRENTPOSITION, &g_nStreamPlayPos, &g_nStreamWritePos) == 0)
        return (g_nStreamPlayPos / 0x1800) % g_nStreamBlocks;
    return -1;
}

/* The timer callback that keeps the stream buffer filled: if the play cursor has left the block behind the one written
 * last, locks the next block, mixes into it (through the scratch buffer when the lock wraps around the end of the
 * buffer) and unlocks it.  Finally re-arms the timer. */
void dsn_fill_thread(void)
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
            sou_mixer_start();
            ((void (*)(int, void *))g_pfnStreamMix)(frames, sou_mixer_mix);
            sou_mixer_end(out, frames);
            if (wraps) {
                memcpy(p1, g_abStreamScratch, n1);
                memcpy(p2, g_abStreamScratch + n1, n2);
            }
            COMX(g_pStreamDSBuffer, DSB_UNLOCK, p1, n1, p2, n2);
        }
    }
    ((DsndClock *)g_pDsndDriver_timer_services)->setPeriod(g_nStreamTimerId, 0x1234dc / (((int)g_dwStreamRate + (((int)g_dwStreamRate >> 31) & 0x3ff)) >> 10));
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

#endif /* GRIM_EXE */
