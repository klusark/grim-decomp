/* Hand-written replacements for functions whose decompilation cannot be
 * compiled faithfully. tools/build_src.py puts the decompiled version of every
 * function defined here under `#if 0` and link.py links this file instead.
 * Keep each entry short and say why it is here. */
#include "ghidra_types.h"

/* stdMemory_CheckMagic (0x47fe20): asserts the 0x12345678 guard word in front
 * of an allocation. MSVC called it without pushing an argument because the
 * pointer already sat in the right stack slot; the C call site therefore
 * passes nothing and the decompiled body reads garbage. The guard is only an
 * assertion, so skip it. */
void stdMemory_CheckMagic(int p)
{
    (void)p;
}

/* COM calls through a vtable. Ghidra loses the arguments of `CALL [reg+off]` when it cannot type
 * the interface: the pushes show up as stack variables (including the return address) and the
 * call itself passes nothing. The functions below are rewritten from the disassembly. */
#define COM(obj, off, ...) ((int (__stdcall *)())(*(void ***)(obj))[(off) / 4])((obj), ##__VA_ARGS__)

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"


/* Input_CreateKeyboard (0x477530): system keyboard, c_dfDIKeyboard format,
 * buffered input of 32 events (DIPROP_BUFFERSIZE). */
void Input_CreateKeyboard(void)
{
    unsigned prop[5] = { 0x14, 0x10, 0, 0, 0x20 };
    if (g_pDirectInput == 0)
        return;
    if (COM(g_pDirectInput, 0xc, &DAT_004d8350, &g_pDInputKeyboard, 0) == 0) {
        COM(g_pDInputKeyboard, 0x2c, &DAT_004d5370);
        COM(g_pDInputKeyboard, 0x18, 1, prop);
    }
}

/* Input_CreateMouse (0x4775a0): system mouse, c_dfDIMouse format, exclusive
 * foreground access, buffered input; axes 12/13/14 are x, y, wheel. */
void Input_CreateMouse(void)
{
    unsigned prop[5] = { 0x14, 0x10, 0, 0, 0x20 };
    if (g_pDirectInput == 0)
        return;
    GetSystemMetrics(0x2b);
    if (COM(g_pDirectInput, 0xc, &DAT_004d8340, &g_pDInputMouse, 0) != 0)
        return;
    if (COM(g_pDInputMouse, 0x2c, &DAT_004d5400) != 0)
        return;
    if (COM(g_pDInputMouse, 0x34, Win_GetMainHwnd(), 5) != 0)
        return;
    COM(g_pDInputMouse, 0x18, 1, prop);
    Input_SetAxisRange(0xc, -0xfa, 0xfa, 0.0);
    Input_SetAxisRange(0xd, -200, 200, 0.0);
    Input_SetAxisRange(0xe, -0x14, 0x14, 0.0);
}

/* DSound_Init (0x4c0ed0): DirectSound object, priority cooperative level,
 * primary buffer (22050 or 11025 Hz 16-bit stereo), optional 3D listener. */
undefined4 DSound_Init(void)
{
    struct { unsigned size, flags, bytes, reserved, format; } desc;
    struct { unsigned short tag, channels; unsigned rate, avg; unsigned short align, bits, cb; } wfx;
    unsigned hwnd;
    int rate;

    if (g_pDirectSound != 0)
        return 0;
    UINT_008d3664 = 0;
    if (DirectSoundCreate(0, &g_pDirectSound, 0) < 0) {
        g_pDirectSound = 0;
        return 0;
    }
    hwnd = (unsigned)Win_GetMainHwnd();
    if (COM(g_pDirectSound, 0x18, hwnd, 2) < 0)
        return 1;
    desc.size = 0x14;
    desc.flags = UINT_008d3664 ? 0x91 : 0x81;   /* PRIMARYBUFFER | CTRLVOLUME [| CTRL3D] */
    desc.bytes = 0;
    desc.reserved = 0;
    desc.format = 0;
    UINT_008d3654 = hwnd;
    if (COM(g_pDirectSound, 0xc, &desc, &g_pDSoundPrimary, 0) < 0) {
        g_pDSoundPrimary = 0;
        return 1;
    }
    COM(g_pDSoundPrimary, 0x18, &UINT_008d3658);          /* GetVolume */
    rate = UINT_008d3660 ? 0x2b11 : 0x5622;
    wfx.tag = 1;
    wfx.channels = 2;
    wfx.rate = rate;
    wfx.avg = rate << 2;
    wfx.align = 4;
    wfx.bits = 0x10;
    wfx.cb = 0;
    COM(g_pDSoundPrimary, 0x38, &wfx);                   /* SetFormat */
    DSound_SetPrimaryVolume(UINT_004f1000);
    if (UINT_008d3664 != 0) {
        if (COM(g_pDSoundPrimary, 0, &DAT_004d8510, &PTR_008d3674) < 0) {
            UINT_008d3664 = 0;
            PTR_008d3674 = 0;
        } else {
            COM(PTR_008d3674, 0x2c, 0x3f000000, 1);
            COM(PTR_008d3674, 0x3c, 0, 1);
        }
    }
    COM(g_pDSoundPrimary, 0x30, 0, 0, 0);                /* Play */
    COM(g_pDirectSound, 0x18, hwnd, 3);                  /* SetCooperativeLevel: exclusive */
    return 1;
}
#endif /* GRIM_EXE */

#ifdef GRIM_IMUSE
#include "globals.h"
#include "functions.h"

/* FUN_10008ce0 (iMUSE heartbeat timer start-up): the decompiler lost the TIMECAPS
 * structure it reads back from the stack (wPeriodMin/wPeriodMax became unaff_ESI /
 * unaff_EDI, which made the period 0). Rewritten from the disassembly:
 * period = min(max(wPeriodMin, 50), wPeriodMax). The heartbeat callback
 * (FUN_10008e00, __stdcall with five arguments) must fire within 4 s, retried
 * twice, or the function reports failure. */
int FUN_10008ce0(void)
{
    unsigned caps[2];
    unsigned period, lo;
    int start, tries;

    if (timeGetDevCaps(caps, 8) != 0)
        return 0;
    lo = caps[0] > 0x32 ? caps[0] : 0x32;
    period = (lo >= caps[1]) ? caps[1] : lo;
    _DAT_1002e338 = 1000 / period;
    _DAT_10031520 = period;
    timeBeginPeriod(period);
    _DAT_10031d28 = timeSetEvent(_DAT_1002e338, 0, (void *)FUN_10008e00, 0xf, 1);
    start = timeGetTime();
    _DAT_10031e84 = 0;
    for (tries = 3; tries > 0; tries--) {
        if (_DAT_10031e84 != 0)
            return _DAT_10031e84;
        while ((unsigned)(timeGetTime() - start) < 4000) {
            if (_DAT_10031e84 != 0)
                return _DAT_10031e84;
        }
        if (_DAT_10031e84 == 0) {
            timeKillEvent(_DAT_10031d28);
            timeEndPeriod(_DAT_10031520);
            timeBeginPeriod(_DAT_10031520);
            _DAT_10031d28 = timeSetEvent(_DAT_1002e338, 0, (void *)FUN_10008e00, 0xf, 1);
            start = timeGetTime();
        }
    }
    return _DAT_10031e84;
}

/* Im_DSoundCreateBuffer (0x10003930): secondary streaming buffer of n * 0x1800
 * bytes (n clamped to 3..16), zero-filled and played in a loop. The decompiler lost
 * every COM argument and turned the lock/clear/unlock into stack writes, so it is
 * rewritten from the disassembly. IDirectSoundBuffer slots: 8 Release, 0x2c Lock,
 * 0x30 Play, 0x3c SetVolume, 0x4c Unlock; IDirectSound 0xc CreateSoundBuffer. */
void Im_DSoundCreateBuffer(int n)
{
    struct { unsigned size, flags, bytes, reserved; void *format; } desc;
    void *p1 = 0, *p2 = 0;
    unsigned b1 = 0, b2 = 0;

    DAT_1002d840 = 1;
    if (PTR_1002d83c != 0)
        COM(PTR_1002d83c, 8);
    PTR_1002d83c = 0;
    if (n < 3)
        n = 3;
    if (n > 0x10)
        n = 0x10;
    DAT_1002d824 = n;
    desc.size = 0x14;
    desc.flags = 0x18080;           /* GETCURRENTPOSITION2 | GLOBALFOCUS | CTRLVOLUME */
    desc.bytes = n * 0x1800;
    desc.reserved = 0;
    desc.format = &DAT_100170f0;
    if (COM(PTR_1002d834, 0xc, &desc, &PTR_1002d83c, 0) == 0) {
        COM(PTR_1002d83c, 0x3c, 0);
        if (COM(PTR_1002d83c, 0x2c, 0, n * 0x1800, &p1, &b1, &p2, &b2, 0) == 0) {
            unsigned i;
            for (i = 0; i < b1; i++)
                ((unsigned char *)p1)[i] = 0;
            if (p2 != 0)
                for (i = 0; i < b2; i++)
                    ((unsigned char *)p2)[i] = 0;
            COM(PTR_1002d83c, 0x4c, p1, b1, p2, b2);
        }
        COM(PTR_1002d83c, 0x30, 0, 0, 1);   /* Play, looping */
    }
    DAT_1002d840 = 0;
}
#endif /* GRIM_IMUSE */
