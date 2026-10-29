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

unsigned long __attribute__((stdcall)) GRIM_GetEnv(const char *, char *, unsigned long) __asm__("_GetEnvironmentVariableA@12");

/* Display_InitFromConfig (0x402930): the game normally restores the last display from the registry
 * or picks the closest fullscreen DirectDraw device. This build runs in the software renderer: device
 * 0 is "Window Display Device" (a DIB section in the game window), which works on any machine.
 * GRIM_DISPLAY_DEVICE=<n> selects another enumerated device (1 is the DirectDraw display). */
undefined *Display_InitFromConfig(void)
{
    char e[8] = "";
    int dev;
    GRIM_GetEnv("GRIM_DISPLAY_DEVICE", e, sizeof e);
    dev = (e[0] >= '0' && e[0] <= '9') ? e[0] - '0' : 0;
    unsigned mode;
    if ((unsigned)dev >= (unsigned)g_dwDisplayDeviceCount)
        dev = 0;
    mode = Display_FindClosestMode(&UINT_004f4d38,
                                   (void *)((unsigned *)g_pDisplayModes)[dev * 4 + 1],
                                   ((unsigned *)g_pDisplayModes)[dev * 4]);
    return (undefined *)(unsigned)Display_Select(dev, (int)mode, -1);
}


/* FUN_00489130 (0x489130), the movie subsystem start-up: reads StartSmush from the registry and, unless it
 * is FALSE, brings up the Smush/LecShare module chain (zfilio, bitmap, animplay, ...). That chain is not
 * yet reproduced faithfully, so movies are switched off the way the game itself does it for
 * StartSmush=FALSE: report success and leave g_nMovieAvailable at 0, which makes every Movie_* call a no-op. */
undefined4 FUN_00489130(void)
{
    return 0;
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

#if defined(GRIM_CHORE) || defined(GRIM_EXE) || defined(GRIM_LUA)
#include "functions.h"
/* FUN_10006b30 (0x10006b30) is MSVC's _input(FILE *, format, va_list), the scanf engine. Ghidra
 * splits its jump-table cases into pieces, so it can neither be decompiled nor assembled from its
 * listing. sscanf calls it on a FILE that wraps a string (_ptr = current position, MSVC layout
 * {_ptr, _cnt, _base, _flag}), so the host's vsscanf on that string does the same job. */
/* (mingw's vsscanf is no help: it rebuilds the call from the format and crashes on these.) Every
 * scanf output is a pointer, so the va_list words are forwarded to msvcrt's sscanf as 32 extra
 * arguments; the callee reads as many as the format needs and the caller pops them all. */
typedef int (*scanf_fn)(const char *, const char *,
                        unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned,
                        unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned,
                        unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned,
                        unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
/* libmsvcrt.a has no import entry for sscanf (mingw has its own), so ask msvcrt.dll for it */
extern void *__attribute__((stdcall)) GRIM_LoadLibraryA(const char *) __asm__("_LoadLibraryA@4");
extern void *__attribute__((stdcall)) GRIM_GetProcAddress(void *, const char *) __asm__("_GetProcAddress@8");
/* OVERRIDES: _input FUN_10006b30 */
#if defined(GRIM_CHORE)
int FUN_10006b30(undefined4 stream, byte *format, undefined4 *a)
#elif defined(GRIM_LUA)
int __cdecl _input(int *stream, byte *format, undefined4 *a)
#else
/* the EXE's own copy of the same function (0x004b3620) */
uint _input(undefined4 stream, byte *format, uint *a)
#endif
{
    static scanf_fn host_sscanf;
    const char *s = *(const char **)(unsigned)stream;
    if (!host_sscanf)
        host_sscanf = (scanf_fn)GRIM_GetProcAddress(GRIM_LoadLibraryA("msvcrt.dll"), "sscanf");
    return host_sscanf(s, (const char *)format,
                         a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7],
                         a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15],
                         a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23],
                         a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
}
#endif /* GRIM_CHORE || GRIM_EXE || GRIM_LUA */

/* MSVC 6 pow family (_CIpow takes its operands on the x87 stack, _pow on the C stack). The CRT's own
 * versions branch through special-case helpers that live in pieces Ghidra cannot stitch together, so
 * both go to the host msvcrt's pow instead. */
/* OVERRIDES: _pow _CIpow */
__asm__(".text\n"
        ".globl __pow\n"
        "__pow:\n"
        "    jmp *__imp__pow\n"
        ".globl __CIpow\n"
        "__CIpow:\n"
        "    subl $16, %esp\n"
        "    fstpl 8(%esp)\n"      /* exponent: ST(0) */
        "    fstpl (%esp)\n"       /* base: ST(1) */
        "    call *__imp__pow\n"
        "    addl $16, %esp\n"
        "    ret\n");
