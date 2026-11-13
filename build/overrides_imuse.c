/* Readable C for functions of IMUSE.DLL whose raw Ghidra decompilation cannot be compiled as it stands (agent N).
 * Each function was checked against the original instructions; tools/build_src.py puts the decompiled version of every
 * function defined here under `#if 0`.  Names, types and offsets are Ghidra's.  The reasons why some other functions stay
 * assembled are in docs/notes/imuse.md and docs/ASM_REMAINING_imuse.md.
 * Compiled by build/link.py for every program; everything is guarded with GRIM_IMUSE. */
#include "ghidra_types.h"

#ifdef GRIM_IMUSE
#include "globals.h"
#include "functions.h"

/* DirectSound COM call: `obj->vtable[off / 4](obj, ...)`.  COM methods are __stdcall (the callee pops its arguments), which
 * the decompiler's unprototyped `(**(code **)(*obj + off))(obj, ...)` does not say: compiled as cdecl the caller would pop
 * them a second time and the stack pointer would run away by 4 * (argument count) per call. */
#define COM(obj, off, ...) ((int (__stdcall *)())(*(void ***)(obj))[(off) / 4])((obj), ##__VA_ARGS__)

/* IDirectSoundBuffer vtable offsets used below */
#define DSB_RELEASE 0x08
#define DSB_LOCK    0x2c
#define DSB_UNLOCK  0x4c

/* ==== DwQuery (0x10003730) ====
 * Called twice per 20 ms heartbeat step by TrIntHandler, alternating between two phases (DAT_1002d848 toggles):
 *   odd:  lock the next 0x1800-byte block of the DirectSound ring (the one after DAT_100170ec, the block last written, unless
 *         the play cursor is already in it) and tell the mixer where to write: *buf_out / *count_out (dwords) / *rate_out.
 *         When the lock wrapped around the end of the ring (second part DAT_1002d854 / DAT_1002d820) the mixer writes into
 *         the scratch block DAT_1002d818 instead (0x600 dwords) and the next phase copies it into the two parts;
 *   even: copy the scratch block (if it was used) and unlock.
 * DAT_1002d840 (buffer being re-created) and DAT_1002d844 (shut down) turn the whole step off.
 * The decompiler had lost the third parameter (*rate_out, 0x5622 = 22050 Hz) and the stdcall convention of the COM calls. */
int DwQuery(int **buf_out, uint *count_out, int *rate_out)
{
    int cur, next;
    uint i;

    *count_out = 0;
    if (DAT_1002d840 != 0 || DAT_1002d844 != 0)
        return 0;
    DAT_1002d848 = DAT_1002d848 ^ 1;
    if (DAT_1002d848 == 0) {                                   /* phase 2: hand the block back to DirectSound */
        if (g_dwCurrentWriteIndex == 0)
            return 0;
        if (DAT_1002d854 != 0 && DAT_1002d820 != 0) {          /* the mixer wrote into the scratch block */
            for (i = 0; i < DAT_1002d82c; i++)
                ((char *)DAT_1002d850)[i] = ((char *)DAT_1002d818)[i];
            for (i = 0; i < DAT_1002d820; i++)
                ((char *)DAT_1002d854)[i] = ((char *)DAT_1002d818)[DAT_1002d82c + i];
        }
        COM(PTR_1002d83c, DSB_UNLOCK, DAT_1002d850, DAT_1002d82c, DAT_1002d854, DAT_1002d820);
        g_dwCurrentWriteIndex = 0;
        return 0;
    }
    cur = iMUSE_dsound__3a80();                                /* block of the ring the play cursor is in */
    if (cur == -1)
        return 0;
    next = (int)PTR_100170ec;                                  /* block written last (negative: none yet) */
    if (cur == (next + 1) % DAT_1002d824)
        return 0;                                              /* the cursor is about to enter the next block: wait */
    if (next < 0)
        next = cur;
    next = (next + 1) % DAT_1002d824;
    PTR_100170ec = (int *)next;
    if (COM(PTR_1002d83c, DSB_LOCK, next * 0x1800, 0x1800, &DAT_1002d850, &DAT_1002d82c, &DAT_1002d854, &DAT_1002d820, 0) != 0)
        return 0;
    if (DAT_1002d854 != 0 && DAT_1002d820 != 0) {
        *buf_out = DAT_1002d818;
        *count_out = 0x600;
    } else {
        *buf_out = DAT_1002d850;
        *count_out = DAT_1002d82c >> 2;
    }
    *rate_out = 0x5622;
    g_dwCurrentWriteIndex = 1;
    return 0;
}

/* ==== DwTerminate (0x100038d0) ====
 * Releases the two DirectSound objects (COM Release, vtable slot 2, __stdcall) and frees the scratch block. */
undefined4 DwTerminate(void)
{
    DAT_1002d844 = 1;
    if (PTR_1002d838 != 0)
        COM(PTR_1002d838, DSB_RELEASE);
    PTR_1002d838 = 0;
    if (PTR_1002d83c != 0)
        COM(PTR_1002d83c, DSB_RELEASE);
    PTR_1002d83c = 0;
    (**(code **)(g_dwSounds_pHS + 0x24))(PTR_1002d830);          /* services->free */
    return 0;
}

/* ==== ihost_get_buffer_info (0x10007a80) ====
 * &sound_slots[i] of the 16-byte slot table at DAT_1002ebe0.  Ghidra prints the table's address as a plain number inside
 * an arithmetic expression, which tools/build_src.py cannot tell from a constant; the DLL is loaded away from 0x10000000 and
 * the table lives in the rebuilt .data section, so the address has to be relocated (IMG_ADDR). */
int ihost_get_buffer_info(int param_1)
{
    return param_1 * 0x10 + IMG_ADDR(0x1002ebe0);
}

/* ==== MxInitialize (0x10005360) ====
 * Builds the two lookup tables of the software mixer and allocates its accumulator.  The decompiler lost the arithmetic that
 * is done in x87 registers between the calls of the _ftol helper (hmi__bae0), so it is written from the disassembly:
 *   pan weights  g_bPanTable[i][j] (17 x 17 bytes) = (int)((sin(j * 3.1415 * 0.03125) * i + 0.5) * 8.0)
 *   volume curve g_dwSoftLTable[k]    (g_dwImWaveMixCount * 0x8000 shorts) = (int)((524272 k / (262136 + 7 k) + 1) * 0.5)
 * The intermediate values stay in extended precision (long double) like the original x87 code. */
static long double x87_fsin(long double x)
{
    __asm__("fsin" : "+t"(x));
    return x;
}
undefined4 MxInitialize(undefined4 *param_1)
{
    int i, j, k, n;
    unsigned char *pan = (unsigned char *)&g_bPanTable;
    short *curve;

    for (i = 0; i < 17; i++)
        for (j = 0; j < 17; j++)
            *pan++ = (unsigned char)(long long)((x87_fsin((long double)j * 3.1415 * 0.03125) * (long double)i - -0.5) * 8.0);
    g_dwOutChannelCount = *param_1;
    g_dwMixBufSize = param_1[2] << 1;
    g_pMixBuf = (int *)(**(code **)(g_dwSounds_pHS + 0x20))(param_1[2] << 1, s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8, 0x7a);
    _DAT_1002df28 = param_1[3];
    curve = (short *)(**(code **)(g_dwSounds_pHS + 0x20))(g_dwImWaveMixCount << 16, s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8, 0x7f);
    g_dwSoftLTable = (undefined4)curve;
    if (curve == 0)
        return 0xffffffff;
    n = g_dwImWaveMixCount << 15;
    for (k = 0; k < n; k++) {
        long double x = (long double)k;
        *curve++ = (short)(long long)((x * 524272.0 / (262136.0 - x * -7.0) - -1.0) * 0.5);
    }
    return 0;
}

/* ==== Trigger and deferred-command layer (0x1000b220 0x1000b570 0x1000b6a0 0x1000b710 0x10004f70) ====
 * iMUSE can attach a command to a marker of a sound (ImSetTrigger: when the marker passes, "run command <cmd> with these ten
 * parameter words") and queue one for later (ImDeferCommand).  Commands 0..0x1d are the numbers of the Im* API calls handled
 * by ImSoundCall; a larger value is a callback address.
 *
 * What the shipped code really does (the disassembly is the reference; the original C source must have used va_arg):
 *  - ImSetTrigger / ImDeferCommand pass their LAST parameter p9 for every one of the ten stored words (see their decompiled
 *    text), and Im_Run*Command pass the last stored word for all ten again, so a command runs with the same word in every
 *    argument: ImSetHook(w, w), ImFadeParam(w, w, w, w).  Dispatch uses a different one of those equal arguments per call,
 *    which is the same.  The commands therefore only do something useful when the word happens to be meaningful; the script
 *    layer (Script_Trans) sets such triggers with garbage in the unused words.  Kept as it is: the behaviour of the game
 *    depends on it.
 *  - ImSoundCall reads the word at [esp+0x3c] (argument 15, four words beyond what the callers push) for commands
 *    0x11 (set trigger) and 0x14 (defer): garbage in the original.  Here: the last argument, a11 (identical to every other
 *    argument as passed by the two callers).
 * Trigger slots: 8 of 0x4d dwords at g_dwTrigs {0 owner sound, 1..0x40 marker string (256 bytes), 0x41 command,
 * 0x42..0x4b parameters, 0x4c kept-after-fire flag}.  Deferred slots: 8 of 12 dwords at DAT_10032cc0 {0 time, 1 command,
 * 2..11 parameters}. */
undefined4 TgSetTrigger(int sound, char *marker, int cmd, int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9)
{
    int *slot = (int *)&g_dwTrigs;
    int n, len;
    char *dst;

    if (sound == 0)
        return 0xfffffffb;
    if (marker == 0)
        marker = (char *)&DAT_10032f48;           /* "" */
    for (len = 0; marker[len] != 0; len++)
        ;
    if (len > 0xff)
        return 0xfffffffb;
    for (n = 0; slot[0] != 0; ) {                  /* first free slot */
        n++;
        slot += 0x4d;
        if (n > 7)
            return 0xfffffffa;
    }
    slot[0x41] = cmd;
    slot[0] = sound;
    slot[0x4c] = 0;
    dst = (char *)(slot + 1);
    for (n = 0; n <= len; n++)
        dst[n] = marker[n];
    slot[0x42] = p0; slot[0x43] = p1; slot[0x44] = p2; slot[0x45] = p3; slot[0x46] = p4;
    slot[0x47] = p5; slot[0x48] = p6; slot[0x49] = p7; slot[0x4a] = p8; slot[0x4b] = p9;
    return 0;
}

undefined4 TgDeferCommand(int time, int cmd, int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9)
{
    int *e = (int *)&DAT_10032cc0;
    int i;

    if (time == 0)
        return 0xfffffffb;
    for (i = 0; i < 8; i++, e += 0xc) {
        if (e[0] == 0) {
            e[1] = cmd;
            e[2] = p0; e[3] = p1; e[4] = p2; e[5] = p3; e[6] = p4;
            e[7] = p5; e[8] = p6; e[9] = p7; e[10] = p8; e[11] = p9;
            e[0] = time;
            g_dwDefersOn = 1;                      /* something to look at in TgIntHandler */
            return 0;
        }
    }
    return 0xfffffffa;
}

/* A fired trigger: free its slot, then run the command with marker name `marker` (callbacks get it first).  The decompiler
 * showed the callback call with one argument; the code pushes eleven (marker + ten words) and pops 0x2c bytes. */
void Im_RunTriggerCommand(undefined4 *slot, undefined4 marker)
{
    int cmd = (int)slot[0x41];
    int w = (int)slot[0x4b];

    slot[0] = 0;
    if (cmd == 0) {
        if (DAT_100336a8 != 0)
            ((int (*)(int, int, int, int, int, int, int, int, int, int, int))DAT_100336a8)(marker, w, w, w, w, w, w, w, w, w, w);
        return;
    }
    if ((unsigned)cmd < 0x1e) {
        ImSoundCall(cmd, w, w, w, w, w, w, w, w, w, w);
        return;
    }
    ((int (*)(int, int, int, int, int, int, int, int, int, int, int))cmd)(marker, w, w, w, w, w, w, w, w, w, w);
}

/* A deferred command whose time has come (TgIntHandler): the slot is {time, command, ten words}. */
void Im_RunDeferredCommand(int e)
{
    int cmd = ((int *)e)[1];
    int w = ((int *)e)[0xb];

    if (cmd == 0) {
        if (DAT_100336a8 == 0)
            return;
        cmd = (int)DAT_100336a8;
    } else if ((unsigned)cmd < 0x1e) {
        ImSoundCall(cmd, w, w, w, w, w, w, w, w, w, w);
        return;
    }
    ((int (*)(int, int, int, int, int, int, int, int, int, int))cmd)(w, w, w, w, w, w, w, w, w, w);
}

/* Command dispatcher: cmd = number of the Im* call, a2..a11 = ten argument words.  Every call takes ITS arguments from the
 * LAST of the argument words it needs (the same word for all of them: compiled from va_arg expressions evaluated in the
 * wrong order).  Commands 0x15..0x18 do not exist. */
uint ImSoundCall(uint cmd, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11)
{
    if (g_dwIm_initialized == 0 || cmd > 0x1d)
        return 0xffffffff;
    switch (cmd) {
    case 0x00: return ImInitialize();
    case 0x01: return ImTerminate();
    case 0x02: return cmd;
    case 0x03: return ImPause();
    case 0x04: return ImResume();
    case 0x05: return ImSave((undefined4 *)a3, a3);
    case 0x06: return ImRestore((int *)a2);
    case 0x07: return ImSetGroupVol(a3, a3);
    case 0x08: return ImStartSound(a3, a3);
    case 0x09: return ImStopSound(a2);
    case 0x0a: return ImStopAllSounds();
    case 0x0b: return ImGetNextSound(a2);
    case 0x0c: return ImSetParam(a4, a4, a4);
    case 0x0d: return ImGetParam(a3, a3);
    case 0x0e: return ImFadeParam(a5, a5, a5, a5);
    case 0x0f: return ImSetHook(a3, a3);
    case 0x10: return ImGetHook(a2);
    case 0x11: return ImSetTrigger(a11, (char *)a11, a11, a11, a11, a11, a11, a11, a11, a11, a11, a11, a11);
    case 0x12: return ImCheckTrigger(a4, (byte *)a4, a4);
    case 0x13: return ImClearTrigger(a4, (byte *)a4, a4);
    case 0x14: return ImDeferCommand(a11, a11, a11, a11, a11, a11, a11, a11, a11, a11, a11, a11);
    case 0x19: return ImStartStream(a4, a4, a4);
    case 0x1a: return ImSwitchStream(a6, a6, a6, a6, a6);
    case 0x1b: return ImProcessStreams();
    case 0x1c: return ImQueryStream(a6, (undefined4 *)a6, (undefined4 *)a6, (int *)a6, (undefined4 *)a6);
    case 0x1d: return ImFeedStream(a5, (undefined4 *)a5, a5, a5);
    }
    return 0xffffffff;
}

/* ==== SoundStartVoiceStream (0x100088d0) ====
 * Starts the voice stream (sound id 10000): SoundStartVoiceStream(name, volume, pan).  The decompiler mixed up the arguments
 * (it read the pan from a fourth, non-existent parameter): the code reads [esp+0x14] and [esp+0x18] while the 3 pushes of
 * the calls before it are still on the stack (the pops are deferred), which are arguments 2 and 3. */
int SoundStartVoiceStream(char *name, uint volume, uint pan)
{
    ImStopSound(10000);
    SoundsCloseVoiceFile();
    if (SoundsRegisterVoice(name) == 0)
        return 1;
    SoundsFillStreamsWhileMusicCritical(5);
    ImStartStream(10000, 0x7f, 1);
    ImSetParam(10000, 0x400, 2);            /* group 2: voice */
    ImSetParam(10000, 0x600, volume);
    ImSetParam(10000, 0x700, pan);
    ImProcessStreams();
    ImProcessStreams();
    return 0;
}

/* ==== Script_Callback (0x100070e0) ====
 * Trigger callback (stored by FUN_10006360, run by Im_RunTriggerCommand with the marker name as its first argument): when the
 * marker is "_..." the script layer's end-of-sequence flag DAT_1002e304 is set.  The decompiler read the marker from the
 * second argument (the code reads [esp+8] while the pop of the ImPrintf argument is still pending, that is argument 1). */
void Script_Callback(char *marker)
{
    ImPrintf(s_CALLBACK__1001e898);
    if (*marker == '_') {
        DAT_1002e304 = 1;
        return;
    }
    ImPrintf(s_ERR_callback_got_marker______end_1001e870);
}

/* ==== Im_MixLoopC (0x10005b80) and Im_MixLoopD (0x10005db0) ====
 * The mixer's inner loops for 16-bit samples stored BIG-endian (the source is the sound data as it comes from the file): C takes
 * mono data into the two accumulators of a stereo pair with the weights wl / wr, D takes stereo data with one weight.
 * The decompiler lost the sign extension (`movsx eax, ax` after the byte swap) and printed (int)CONCAT11(lo, hi), which is
 * unsigned: every negative sample came out as +65536 - |x| (twice as loud, from the first blocks of any stereo/big-endian sound).
 * `rate` = (count << 16) / length is the resampling step in 16.16: exactly 0x8000 (interpolating doubling: odd output frames
 * are the mean of two input frames), 0x10000 and 0x20000 (plain copy / every second frame), anything else steps by `rate`.
 * acc = the accumulators g_pMixBuf + 2 * out (two ints per output frame; the accumulator of a stereo pair is [left, right]). */
static int bswap_s16(unsigned short v)
{
    return (short)((v >> 8) | (v << 8));
}

void Im_MixLoopC(undefined2 *src, int n, uint count, int out, int wl, int wr)
{
    int *acc = g_pMixBuf + out * 2;
    uint rate = (uint)(n << 16) / count;
    unsigned short *p = (unsigned short *)src;
    uint frac;

    if (rate == 0x8000) {
        while (--n != 0) {
            int a = bswap_s16(p[0]);
            int avg = (short)((bswap_s16(p[2]) + a) >> 1);
            p++;
            acc[0] += wl * a;
            acc[1] += wr * a;
            acc[2] += wl * avg;
            acc[3] += wr * avg;
            acc += 4;
        }
        {
            int a = bswap_s16(p[0]);
            acc[0] += wl * a;
            acc[1] += wr * a;
            acc[2] += wl * a;
            acc[3] += wr * a;
        }
    } else if (rate == 0x10000) {
        for (; count != 0; count--) {
            int a = bswap_s16(*p++);
            acc[0] += wl * a;
            acc[1] += wr * a;
            acc += 2;
        }
    } else if (rate == 0x20000) {
        for (; count != 0; count--) {
            int a = bswap_s16(p[0]);
            p += 2;
            acc[0] += wl * a;
            acc[1] += wr * a;
            acc += 2;
        }
    } else {
        for (frac = 0; count != 0; count--) {
            int a = bswap_s16(p[0]);
            uint f = frac + rate;
            acc[0] += wl * a;
            acc[1] += wr * a;
            acc += 2;
            frac = f & 0xffff;
            p += (int)f >> 16;
        }
    }
}

void Im_MixLoopD(undefined2 *src, int n, uint count, uint out, int vol)
{
    int *acc = g_pMixBuf + out * 2;
    uint rate = (uint)(n << 16) / count;
    unsigned short *p = (unsigned short *)src;
    uint frac;
    int k;

    if (rate == 0x8000) {
        while (--n != 0) {
            int l = bswap_s16(p[0]), r = bswap_s16(p[1]);
            int nl = bswap_s16(p[2]), nr = bswap_s16(p[3]);
            p += 2;
            acc[0] += vol * l;
            acc[1] += vol * r;
            acc[2] += (short)((nl + l) >> 1) * vol;
            acc[3] += (short)((nr + r) >> 1) * vol;
            acc += 4;
        }
        {
            int a = bswap_s16(p[0]) * vol, b = bswap_s16(p[1]) * vol;
            acc[0] += a;
            acc[1] += b;
            acc[2] += a;
            acc[3] += b;
        }
    } else if (rate == 0x10000) {
        for (k = count * 2; k != 0; k--)
            *acc++ += bswap_s16(*p++) * vol;
    } else if (rate == 0x20000) {
        for (; count != 0; count--) {
            acc[0] += bswap_s16(p[0]) * vol;
            acc[1] += bswap_s16(p[1]) * vol;
            p += 4;
            acc += 2;
        }
    } else {
        for (frac = 0; count != 0; count--) {
            uint f = frac + rate * 2;
            acc[0] += vol * bswap_s16(p[0]);
            acc[1] += vol * bswap_s16(p[1]);
            frac = f & 0xffff;
            p += (int)f >> 16;
            acc += 2;
        }
    }
}
/* ==== sounds_restore (0x10008580) ====
 * The sounds module's restore callback (SoundsInitialize registers it): reads the voice effect, iMUSE's own state (ImRestore)
 * and its script state (ImRestoreScript), stops the sounds below 10001 and starts the saved ones again with their volume, pan
 * and hook.  `read(buf, n)` returns 0 when it read n bytes.  The decompiler lost the arguments of the read of the pan (the
 * original reuses its first argument's stack slot for the value) and wrote `SoundsSetParam((uint *)0x4, 0x700, ...)`: the pan
 * was never restored (grim_tools/cleanroom ims_save: the pan of 30 came back as 64). */
undefined4 sounds_restore(code *param_1, uint param_2)
{
    int (*read)(void *, int) = (int (*)(void *, int))param_1;
    int *buf;
    int size, count, i;
    uint sound, value;
    uint name[8];
    (void)param_2;

    buf = (int *)((void *(*)(int, void *, int))*(void **)(g_dwSounds_pHS + 0x20))(0x20000, s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0, 0x46a);
    if (buf == 0)
        return 1;
    if (read(&g_aVoxFxName, 0x28) != 0)
        return 1;
    ((void (*)(void *))FUN_10009700)(&DAT_1001e98c);
    ImStopAllSounds();
    ((void (*)(void *))FUN_10009700)(&DAT_1001e97c);
    ImFlushSounds();
    ((void (*)(void *))FUN_10009700)(&DAT_1001e970);
    SoundsCloseVoiceFile();
    ((void (*)(void *))FUN_10009700)(&DAT_1001e958);
    FUN_10008e60();
    ((void (*)(void *))FUN_10009700)(&DAT_1001e944);
    iMUSE_SetVoiceEffect((uint *)&g_aVoxFxName);
    g_aLastVoiceFilename = 0;
    read(&size, 4);
    read(buf, size);
    if (ImRestore(buf) != 0) {
        ((void (*)(void *))FUN_10009700)(&DAT_1001e930);
        read(&size, 4);
        read(buf, size);
        if (ImRestoreScript((int)buf) != 0) {
            ((void (*)(void *))FUN_10009700)(&DAT_1001e910);
            for (sound = ImGetNextSound(0); sound != 0; sound = ImGetNextSound(sound))
                if ((int)sound < 0x2711)
                    ImStopSound(sound);
            SoundsCloseVoiceFile();
            ((void (*)(void *))FUN_10009700)(&DAT_1001e958);
            if (read(&count, 4) == 0 && count != 0) {
                for (i = 0; i < count; i++) {                  /* name, handle, priority: start them again */
                    if (read(name, 0x20) != 0 || read(&value, 4) != 0)
                        goto done;
                    g_dwNextHandle = value - 0x457;
                    if (read(&value, 4) != 0)
                        goto done;
                    SoundsLoadStartSound(name, value, 1);
                }
                for (i = 0; i < count; i++) {                  /* sound, volume, pan */
                    if (read(&sound, 4) != 0 || read(&value, 4) != 0)
                        goto done;
                    SoundsSetParam((uint *)sound, 0x600, value);
                    if (read(&value, 4) != 0)
                        goto done;
                    SoundsSetParam((uint *)sound, 0x700, value);
                }
                for (i = 0; i < count; i++) {                  /* sound, hook */
                    if (read(&sound, 4) != 0 || read(&value, 4) != 0)
                        break;
                    iMUSE_SetHook((uint *)sound, value);
                }
            }
        done:
            ((void (*)(void *))*(void **)(g_dwSounds_pHS + 0x24))(buf);
            return 0;
        }
    }
    ((void (*)(void *))*(void **)(g_dwSounds_pHS + 0x24))(buf);
    return 1;
}

#endif /* GRIM_IMUSE */
