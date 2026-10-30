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

/* ==== Im_DSoundHeartbeat (0x10003730) ====
 * Called twice per 20 ms heartbeat step by Im_HeartbeatBody, alternating between two phases (DAT_1002d848 toggles):
 *   odd:  lock the next 0x1800-byte block of the DirectSound ring (the one after DAT_100170ec, the block last written, unless
 *         the play cursor is already in it) and tell the mixer where to write: *buf_out / *count_out (dwords) / *rate_out.
 *         When the lock wrapped around the end of the ring (second part DAT_1002d854 / DAT_1002d820) the mixer writes into
 *         the scratch block DAT_1002d818 instead (0x600 dwords) and the next phase copies it into the two parts;
 *   even: copy the scratch block (if it was used) and unlock.
 * DAT_1002d840 (buffer being re-created) and DAT_1002d844 (shut down) turn the whole step off.
 * The decompiler had lost the third parameter (*rate_out, 0x5622 = 22050 Hz) and the stdcall convention of the COM calls. */
int Im_DSoundHeartbeat(int **buf_out, uint *count_out, int *rate_out)
{
    int cur, next;
    uint i;

    *count_out = 0;
    if (DAT_1002d840 != 0 || DAT_1002d844 != 0)
        return 0;
    DAT_1002d848 = DAT_1002d848 ^ 1;
    if (DAT_1002d848 == 0) {                                   /* phase 2: hand the block back to DirectSound */
        if (DAT_1002d84c == 0)
            return 0;
        if (DAT_1002d854 != 0 && DAT_1002d820 != 0) {          /* the mixer wrote into the scratch block */
            for (i = 0; i < DAT_1002d82c; i++)
                ((char *)DAT_1002d850)[i] = ((char *)DAT_1002d818)[i];
            for (i = 0; i < DAT_1002d820; i++)
                ((char *)DAT_1002d854)[i] = ((char *)DAT_1002d818)[DAT_1002d82c + i];
        }
        COM(PTR_1002d83c, DSB_UNLOCK, DAT_1002d850, DAT_1002d82c, DAT_1002d854, DAT_1002d820);
        DAT_1002d84c = 0;
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
    DAT_1002d84c = 1;
    return 0;
}

/* ==== Im_DSoundShutdown (0x100038d0) ====
 * Releases the two DirectSound objects (COM Release, vtable slot 2, __stdcall) and frees the scratch block. */
undefined4 Im_DSoundShutdown(void)
{
    DAT_1002d844 = 1;
    if (PTR_1002d838 != 0)
        COM(PTR_1002d838, DSB_RELEASE);
    PTR_1002d838 = 0;
    if (PTR_1002d83c != 0)
        COM(PTR_1002d83c, DSB_RELEASE);
    PTR_1002d83c = 0;
    (**(code **)(DAT_10033510 + 0x24))(PTR_1002d830);          /* services->free */
    return 0;
}

/* ==== FUN_10007a80 (0x10007a80) ====
 * &sound_slots[i] of the 16-byte slot table at DAT_1002ebe0.  Ghidra prints the table's address as a plain number inside
 * an arithmetic expression, which tools/build_src.py cannot tell from a constant; the DLL is loaded away from 0x10000000 and
 * the table lives in the rebuilt .data section, so the address has to be relocated (IMG_ADDR). */
int FUN_10007a80(int param_1)
{
    return param_1 * 0x10 + IMG_ADDR(0x1002ebe0);
}

/* ==== Im_MixerInit (0x10005360) ====
 * Builds the two lookup tables of the software mixer and allocates its accumulator.  The decompiler lost the arithmetic that
 * is done in x87 registers between the calls of the _ftol helper (hmi__bae0), so it is written from the disassembly:
 *   pan weights  DAT_10033560[i][j] (17 x 17 bytes) = (int)((sin(j * 3.1415 * 0.03125) * i + 0.5) * 8.0)
 *   volume curve DAT_1002df20[k]    (DAT_1001e8d4 * 0x8000 shorts) = (int)((524272 k / (262136 + 7 k) + 1) * 0.5)
 * The intermediate values stay in extended precision (long double) like the original x87 code. */
static long double x87_fsin(long double x)
{
    __asm__("fsin" : "+t"(x));
    return x;
}
undefined4 Im_MixerInit(undefined4 *param_1)
{
    int i, j, k, n;
    unsigned char *pan = (unsigned char *)&DAT_10033560;
    short *curve;

    for (i = 0; i < 17; i++)
        for (j = 0; j < 17; j++)
            *pan++ = (unsigned char)(long long)((x87_fsin((long double)j * 3.1415 * 0.03125) * (long double)i - -0.5) * 8.0);
    DAT_1002df18 = *param_1;
    DAT_1002df24 = param_1[2] << 1;
    PTR_1002df5c = (int *)(**(code **)(DAT_10033510 + 0x20))(param_1[2] << 1, s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8, 0x7a);
    _DAT_1002df28 = param_1[3];
    curve = (short *)(**(code **)(DAT_10033510 + 0x20))(DAT_1001e8d4 << 16, s_C__grimsrc_libs_iMUSE_Mixer_c_100172c8, 0x7f);
    DAT_1002df20 = (undefined4)curve;
    if (curve == 0)
        return 0xffffffff;
    n = DAT_1001e8d4 << 15;
    for (k = 0; k < n; k++) {
        long double x = (long double)k;
        *curve++ = (short)(long long)((x * 524272.0 / (262136.0 - x * -7.0) - -1.0) * 0.5);
    }
    return 0;
}
#endif /* GRIM_IMUSE */
