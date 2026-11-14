/* Readable C for the software sound mixer and the DirectSound / Smush audio glue of GRIMFANDANGO.EXE
 * (0x004bdf00 - 0x004d4100).  Written from the original instructions (the decompiler printed several of these
 * wrongly: lost COM arguments, x87 results, register-passed helpers) and checked against the machine code with
 * the differential tests in build/mixdiff/ (random inputs, original code and this code side by side, zero differences).
 * tools/build_src.py puts the decompiled text of every function defined here under `#if 0`.
 * Notes: docs/notes/mixer.md.  Compiled by build/link.py for every program; only the GRIMFANDANGO.EXE part exists. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

/* =====================================================================================================
 * The mixing loops.  The mixer adds every voice into a 32-bit accumulator (g_pMixer_mixBuf, interleaved left/right
 * pairs).  A voice block is resampled on the fly:
 *      ratio = (srcCount << 16) / outCount            (16.16 fixed point, source frames per output frame)
 *   ratio 0x8000   source is played at half speed: two output frames per source frame (second one interpolated)
 *   ratio 0x10000  one to one
 *   ratio 0x20000  every second source frame
 *   otherwise      nearest neighbour with a 16-bit phase accumulator
 * The sample formats differ in how a source value becomes a signed amount:
 *   8 bit      unsigned bytes, `(b ^ 0x80) << 8`   (zero-extended in the original: 0x80 -> 0, 0x00 -> +0x8000)
 *   16 bit     signed shorts (Mix16*)
 *   "A"        16 bit with the sign bit flipped (`s ^ 0x8000`, offset binary)
 *   "B"        16 bit byte-swapped, zero-extended (`bswap16(s)`, 0..65535)
 * "...LR" functions take a mono source and separate left/right volumes; the others take interleaved stereo and one volume.
 * The odd details (the 2x case of the 8-bit mono mixers reads src[2] while it advances by one sample, odd source
 * advances in the generic stereo loop, the tail frame, count == 0 running 2^32 times) are the original's behaviour.
 * ===================================================================================================== */
#pragma GCC push_options
#pragma GCC optimize ("O2")

#define MIX_RATIO(count, outFrames)  ((uint)((count) << 16) / (uint)(outFrames))
#define U8(b)       ((((uint)(b)) ^ 0x80) << 8)                    /* 8-bit sample -> 0..0xff00 */
#define U8AVG(a, b) (((((uint)(a)) + (uint)(b)) << 7) ^ 0x8000)    /* (a + b) / 2 in the same scale */
#define SWAP16(w)   ((uint)(((ushort)(w) >> 8) | (((ushort)(w) & 0xff) << 8)))   /* byte-swapped, zero-extended */
#define OFFS16(w)   ((int)(short)((ushort)(w) ^ 0x8000))           /* offset binary -> signed */

#pragma GCC pop_options

/* =====================================================================================================
 * Mixer entry points
 * ===================================================================================================== */

/* x87 FSIN on the register stack, exactly as the original computes the volume table */
static inline long double x87_sin(long double x)
{
    long double r;
    __asm__("fsin" : "=t"(r) : "0"(x));
    return r;
}

/* The 17x17 byte table built by Mixer_InitTables: row = volume step (0..16), column = pan step (-8..8, stored +8) */
extern byte g_MixVolPanTable[17 * 17] __asm__("_DAT_008dcc70");

/* Builds the volume/pan table and the compander table, allocates the accumulator and the table through the module
 * manager's allocator (services[0](size, file, line)).  Returns 0 or -1. */
int Mixer_InitTables(int *services, uint channels, int frames4, int unused)
{
    int r, c, i;
    short *comp;
    byte *tab = g_MixVolPanTable;

    for (r = 0; r < 17; r++) {
        for (c = 0; c < 17; c++) {
            /* (sin(c * 3.1415 * 1/32) * r + 0.5) * 8 */
            long double v = x87_sin((long double)c * 3.1415 * 0.03125) * (long double)r - -0.5;
            *tab++ = (byte)(int)(v * 8.0);
        }
    }
    g_dwMixer_outChannelCount = channels;
    g_dwMixer_mixBufSize = frames4 * 4;
    g_pMixer_mixBuf = (int *)((int (*)(int, const char *, int))services[0])(g_dwMixer_mixBufSize,
                                                                        s_C__grimsrc_libs_lecsmush_insane__004f4158, 0x356);
    if (g_pMixer_mixBuf == 0)
        return 0xffffffff;
    _DAT_008dcda0 = unused;
    comp = (short *)((int (*)(int, const char *, int))services[0])(g_dwWaveMixCount << 16,
                                                                  s_C__grimsrc_libs_lecsmush_insane__004f4158, 0x35c);
    g_pMixer_softLTable = comp;
    if (comp == 0)
        return 0xffffffff;
    /* companding curve: ((524272 i) / (262136 + 7 i) + 1) / 2 */
    for (i = 0; i < (int)(g_dwWaveMixCount << 15); i++) {
        long double x = (long double)i;
        long double num = x * 524272.0;
        long double den = 262136.0 - x * -7.0;
        *comp++ = (short)(int)((num / den - -1.0) * 0.5);
    }
    return 0;
}

#endif /* GRIM_EXE */
