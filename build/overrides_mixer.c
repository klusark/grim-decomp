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
 * The mixing loops.  The mixer adds every voice into a 32-bit accumulator (g_pMixAccum, interleaved left/right
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

/* 8-bit unsigned MONO source, left/right volume */
void Mixer_Mix8MonoLR(byte *src, int count, uint rateFrac, int accumOffset, int volL, int volR)
{
    int *out = g_pMixAccum + accumOffset * 2;
    uint ratio = MIX_RATIO(count, rateFrac);

    if (ratio == 0x8000) {
        while (--count != 0) {
            uint v = U8(src[0]);
            out[0] += v * volL;
            out[1] += v * volR;
            v = U8AVG(src[0], src[2]);          /* (sic) src[2], not src[1] */
            out[2] += v * volL;
            out[3] += v * volR;
            src += 1;
            out += 4;
        }
        out[0] += U8(src[0]) * volL;
        out[1] += U8(src[0]) * volR;
        out[2] += U8(src[0]) * volL;
        out[3] += U8(src[0]) * volR;
    } else if (ratio == 0x10000) {
        while (rateFrac != 0) {
            out[0] += U8(*src) * volL;
            out[1] += U8(*src) * volR;
            src += 1;
            out += 2;
            rateFrac--;
        }
    } else if (ratio == 0x20000) {
        while (rateFrac != 0) {
            out[0] += U8(*src) * volL;
            out[1] += U8(*src) * volR;
            src += 2;
            out += 2;
            rateFrac--;
        }
    } else {
        uint phase = 0;
        while (rateFrac != 0) {
            uint sum;
            out[0] += U8(*src) * volL;
            out[1] += U8(*src) * volR;
            sum = phase + ratio;
            src += (int)sum >> 16;
            phase = sum & 0xffff;
            out += 2;
            rateFrac--;
        }
    }
}

/* 8-bit unsigned STEREO source (interleaved), one volume */
void Mixer_Mix8Mono(byte *src, int count, uint rateFrac, int accumOffset, int vol)
{
    int *out = g_pMixAccum + accumOffset * 2;
    uint ratio = MIX_RATIO(count, rateFrac);

    if (ratio == 0x8000) {
        while (--count != 0) {
            out[0] += U8(src[0]) * vol;
            out[1] += U8(src[1]) * vol;
            out[2] += U8AVG(src[2], src[0]) * vol;
            out[3] += U8AVG(src[3], src[1]) * vol;
            src += 2;
            out += 4;
        }
        out[0] += U8(src[0]) * vol;
        out[1] += U8(src[1]) * vol;
        out[2] += U8(src[0]) * vol;
        out[3] += U8(src[1]) * vol;
    } else if (ratio == 0x10000) {
        uint n = rateFrac * 2;
        while (n != 0) {
            *out++ += U8(*src) * vol;
            src++;
            n--;
        }
    } else if (ratio == 0x20000) {
        while (rateFrac != 0) {
            out[0] += U8(src[0]) * vol;
            out[1] += U8(src[1]) * vol;
            src += 4;
            out += 2;
            rateFrac--;
        }
    } else {
        uint phase = 0;
        while (rateFrac != 0) {
            uint sum = phase + ratio * 2;       /* two bytes per frame: the step is in bytes */
            out[0] += U8(src[0]) * vol;
            out[1] += U8(src[1]) * vol;
            src += (int)sum >> 16;
            phase = sum & 0xffff;
            out += 2;
            rateFrac--;
        }
    }
}

/* 16-bit signed MONO source, left/right volume */
void Mixer_Mix16MonoLR(short *src, int count, uint rateFrac, int accumOffset, int volL, int volR)
{
    int *out = g_pMixAccum + accumOffset * 2;
    uint ratio = MIX_RATIO(count, rateFrac);

    if (ratio == 0x8000) {
        while (--count != 0) {
            int avg = ((int)src[0] + (int)src[2]) >> 1;
            out[0] += src[0] * volL;
            out[1] += src[0] * volR;
            out[2] += avg * volL;
            out[3] += avg * volR;
            out += 4;
            src += 1;
        }
        out[0] += src[0] * volL;
        out[1] += src[0] * volR;
        out[2] += src[0] * volL;
        out[3] += src[0] * volR;
    } else if (ratio == 0x10000) {
        while (rateFrac != 0) {
            out[0] += src[0] * volL;
            out[1] += src[0] * volR;
            out += 2;
            rateFrac--;
            src += 1;
        }
    } else if (ratio == 0x20000) {
        while (rateFrac != 0) {
            out[0] += src[0] * volL;
            out[1] += src[0] * volR;
            out += 2;
            rateFrac--;
            src += 2;
        }
    } else {
        uint phase = 0;
        while (rateFrac != 0) {
            uint sum;
            out[0] += src[0] * volL;
            out[1] += src[0] * volR;
            sum = phase + ratio;
            out += 2;
            phase = sum & 0xffff;
            rateFrac--;
            src += (int)sum >> 16;
        }
    }
}

/* 16-bit signed STEREO source, one volume */
void Mixer_Mix16Mono(short *src, int count, uint rateFrac, int accumOffset, int vol)
{
    int *out = g_pMixAccum + accumOffset * 2;
    uint ratio = MIX_RATIO(count, rateFrac);

    if (ratio == 0x8000) {
        while (--count != 0) {
            out[0] += src[0] * vol;
            out[1] += vol * src[1];
            out[2] += (((int)src[2] + (int)src[0]) >> 1) * vol;
            out[3] += (((int)src[3] + (int)src[1]) >> 1) * vol;
            out += 4;
            src += 2;
        }
        out[0] += src[0] * vol;
        out[1] += vol * src[1];
        out[2] += src[0] * vol;
        out[3] += vol * src[1];
    } else if (ratio == 0x10000) {
        uint n = rateFrac * 2;
        while (n != 0) {
            *out++ += *src * vol;
            src++;
            n--;
        }
    } else if (ratio == 0x20000) {
        while (rateFrac != 0) {
            out[0] += src[0] * vol;
            out[1] += src[1] * vol;
            out += 2;
            rateFrac--;
            src += 4;
        }
    } else {
        uint phase = 0;
        while (rateFrac != 0) {
            uint sum;
            out[0] += src[0] * vol;
            out[1] += src[1] * vol;
            sum = phase + ratio * 2;            /* two shorts per frame */
            out += 2;
            phase = sum & 0xffff;
            rateFrac--;
            src += (int)sum >> 16;
        }
    }
}

/* "A" format (offset binary 16 bit) MONO source, left/right volume */
void Mixer_MixStereoLR_A(ushort *src, int count, uint rateFrac, uint accumOffset, int volL, int volR)
{
    int *out = g_pMixAccum + accumOffset * 2;
    uint ratio = MIX_RATIO(count, rateFrac);

    if (ratio == 0x8000) {
        while (--count != 0) {
            int s0 = OFFS16(src[0]);
            int avg;
            out[0] += volL * s0;
            out[1] += volR * s0;
            avg = (OFFS16(src[2]) + s0) >> 1;
            out[2] += volL * avg;
            src += 1;
            out[3] += volR * avg;
            out += 4;
        }
        volL = volL * OFFS16(src[0]);
        volR = volR * OFFS16(src[0]);
        out[0] += volL;
        out[1] += volR;
        out[2] += volL;
        out[3] += volR;
    } else if (ratio == 0x10000) {
        while (rateFrac != 0) {
            ushort w = *src;
            out[0] += volL * OFFS16(w);
            src += 1;
            out[1] += volR * OFFS16(w);
            out += 2;
            rateFrac--;
        }
    } else if (ratio == 0x20000) {
        while (rateFrac != 0) {
            ushort w = *src;
            out[0] += volL * OFFS16(w);
            src += 2;
            out[1] += volR * OFFS16(w);
            rateFrac--;
            out += 2;
        }
    } else {
        uint phase = 0;
        while (rateFrac != 0) {
            ushort w = *src;
            uint sum;
            out[0] += volL * OFFS16(w);
            sum = phase + ratio;
            out[1] += volR * OFFS16(w);
            out += 2;
            phase = sum & 0xffff;
            src += (int)sum >> 16;
            rateFrac--;
        }
    }
}

/* "A" format STEREO source, one volume */
void Mixer_MixStereo_A(ushort *src, int count, uint rateFrac, uint accumOffset, int vol)
{
    int *out = g_pMixAccum + accumOffset * 2;
    uint ratio = MIX_RATIO(count, rateFrac);

    if (ratio == 0x8000) {
        while (--count != 0) {
            int l0 = OFFS16(src[0]), r0 = OFFS16(src[1]);
            int l1 = OFFS16(src[2]), r1 = OFFS16(src[3]);
            out[0] += vol * l0;
            out[1] += vol * r0;
            src += 2;
            out[2] += ((l1 + l0) >> 1) * vol;
            out[3] += ((r1 + r0) >> 1) * vol;
            out += 4;
        }
        {
            int l = vol * OFFS16(src[0]);
            int r = vol * OFFS16(src[1]);
            out[0] += l;
            out[1] += r;
            out[2] += l;
            out[3] += r;
        }
    } else if (ratio == 0x10000) {
        uint n = rateFrac * 2;
        while (n != 0) {
            ushort w = *src++;
            *out++ += OFFS16(w) * vol;
            n--;
        }
    } else if (ratio == 0x20000) {
        while (rateFrac != 0) {
            ushort r = src[1];
            out[0] += OFFS16(src[0]) * vol;
            src += 4;
            out[1] += OFFS16(r) * vol;
            out += 2;
            rateFrac--;
        }
    } else {
        uint phase = 0;
        while (rateFrac != 0) {
            ushort r = src[1];
            uint sum;
            out[0] += OFFS16(src[0]) * vol;
            sum = phase + ratio * 2;
            out[1] += OFFS16(r) * vol;
            out += 2;
            phase = sum & 0xffff;
            src += (int)sum >> 16;
            rateFrac--;
        }
    }
}

/* "B" format (byte-swapped 16 bit, zero-extended) MONO source, left/right volume */
void Mixer_MixStereoLR_B(ushort *src, int count, uint rateFrac, uint accumOffset, int volL, int volR)
{
    int *out = g_pMixAccum + accumOffset * 2;
    uint ratio = MIX_RATIO(count, rateFrac);

    if (ratio == 0x8000) {
        while (--count != 0) {
            int avg;
            out[0] += SWAP16(src[0]) * volL;
            out[1] += SWAP16(src[0]) * volR;
            avg = ((int)(short)src[2] + (int)(short)src[0]) >> 1;
            avg = (int)(short)SWAP16(avg);     /* the interpolated value is swapped back AND sign-extended */
            out[2] += volL * avg;
            out[3] += volR * avg;
            out += 4;
            src += 1;
        }
        {
            int v = (int)(short)SWAP16(src[0]);     /* the tail frame is sign-extended too */
            volL = volL * v;
            volR = volR * v;
            out[0] += volL;
            out[1] += volR;
            out[2] += volL;
            out[3] += volR;
        }
    } else if (ratio == 0x10000) {
        while (rateFrac != 0) {
            out[0] += SWAP16(*src) * volL;
            out[1] += SWAP16(*src) * volR;
            src += 1;
            rateFrac--;
            out += 2;
        }
    } else if (ratio == 0x20000) {
        while (rateFrac != 0) {
            out[0] += SWAP16(*src) * volL;
            out[1] += SWAP16(*src) * volR;
            src += 2;
            rateFrac--;
            out += 2;
        }
    } else {
        uint phase = 0;
        while (rateFrac != 0) {
            uint sum;
            out[0] += SWAP16(*src) * volL;
            sum = phase + ratio;
            out[1] += SWAP16(*src) * volR;
            out += 2;
            phase = sum & 0xffff;
            rateFrac--;
            src += (int)sum >> 16;
        }
    }
}

/* "B" format STEREO source, one volume */
void Mixer_MixStereo_B(ushort *src, int count, uint rateFrac, uint accumOffset, int vol)
{
    int *out = g_pMixAccum + accumOffset * 2;
    uint ratio = MIX_RATIO(count, rateFrac);

    if (ratio == 0x8000) {
        while (--count != 0) {
            uint avg;
            out[0] += SWAP16(src[0]) * vol;
            out[1] += SWAP16(src[1]) * vol;
            avg = ((int)(short)src[2] + (int)(short)src[0]) >> 1;
            out[2] += SWAP16(avg) * vol;
            avg = ((int)(short)src[3] + (int)(short)src[1]) >> 1;
            out[3] += SWAP16(avg) * vol;
            out += 4;
            src += 2;
        }
        out[0] += SWAP16(src[0]) * vol;
        out[1] += SWAP16(src[1]) * vol;
        out[2] += SWAP16(src[0]) * vol;
        out[3] += SWAP16(src[1]) * vol;
    } else if (ratio == 0x10000) {
        uint n = rateFrac * 2;
        while (n != 0) {
            n--;
            *out++ += SWAP16(*src) * vol;
        }
    } else if (ratio == 0x20000) {
        while (rateFrac != 0) {
            out[0] += SWAP16(src[0]) * vol;
            out[1] += SWAP16(src[1]) * vol;
            src += 4;
            out += 2;
            rateFrac--;
        }
    } else {
        uint phase = 0;
        while (rateFrac != 0) {
            uint sum;
            out[0] += SWAP16(src[0]) * vol;
            sum = phase + ratio * 2;
            out[1] += SWAP16(src[1]) * vol;
            phase = sum & 0xffff;
            rateFrac--;
            src += (int)sum >> 16;
            out += 2;
        }
    }
}

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

/* Zeroes the accumulator. */
int Mixer_ClearAccumulator(void)
{
    memset(g_pMixAccum, 0, g_dwMixAccumBytes);
    return 0;
}

/* Adds one block of a voice to the accumulator.  data/count: source bytes of the block (count in source frames),
 * bits 8 or 16, channels 1 or 2, outFrames: frames of output the block is stretched/squeezed to, accumOffset: first
 * output frame, volume 0..127, pan 0..128 (64 = centre), offsetBinary / byteSwapped: format of the 16-bit data. */
void Mixer_MixVoice(byte *data, int count, int bits, int channels, uint outFrames, int accumOffset,
                    int volume, int pan, int offsetBinary, int byteSwapped)
{
    if (g_pMixAccum == 0 || data == 0 || count == 0)
        return;
    if (channels == 1) {
        /* mono source: left/right volumes from the volume/pan table */
        uint vstep = volume >> 3;
        int pstep;
        uint volL, volR;
        if (volume != 0)
            vstep++;
        if (vstep > 16)
            vstep = 16;
        pstep = (pan >> 3) - 8;
        if (pan > 0x40)
            pstep++;
        volL = (g_MixVolPanTable + 8)[vstep * 17 - pstep];
        volR = (g_MixVolPanTable + 8)[vstep * 17 + pstep];
        if (bits == 8)
            Mixer_Mix8MonoLR(data, count, outFrames, accumOffset, volL, volR);
        else if (offsetBinary == 0)
            Mixer_MixStereoLR_A((ushort *)data, count, outFrames, accumOffset, volL, volR);
        else if (byteSwapped != 0)
            Mixer_MixStereoLR_B((ushort *)data, count, outFrames, accumOffset, volL, volR);
        else
            Mixer_Mix16MonoLR((short *)data, count, outFrames, accumOffset, volL, volR);
    } else {
        /* interleaved stereo: one volume */
        if (bits == 8)
            Mixer_Mix8Mono(data, count, outFrames, accumOffset, volume + 1);
        else if (offsetBinary == 0)
            Mixer_MixStereo_A((ushort *)data, count, outFrames, accumOffset, volume + 1);
        else if (byteSwapped != 0)
            Mixer_MixStereo_B((ushort *)data, count, outFrames, accumOffset, volume + 1);
        else
            Mixer_Mix16Mono((short *)data, count, outFrames, accumOffset, volume + 1);
    }
}

/* Accumulator >> 7, clamped to 16 bits, into the output block (twice the frame count in stereo).
 * Returns 0, or -1 when there is no accumulator, no buffer or no frames. */
int Mixer_ConvertTo16(short *dst, int frames)
{
    int *src = g_pMixAccum;
    int n;

    if (src == 0 || dst == 0 || frames == 0)
        return 0xffffffff;
    n = (g_dwMixChannels == 2) ? frames * 2 : frames;
    for (; n != 0; n--) {
        int v = *src++ >> 7;
        if (v < -0x8000)
            v = -0x8000;
        if (v > 0x7fff)
            v = 0x7fff;
        *dst++ = (short)v;
    }
    return 0;
}

void Mixer_Output(short *dst, int frames)
{
    Mixer_ConvertTo16(dst, frames);
}

/* Callback the sound module hands to the driver: translates a format code to MixVoice arguments.
 * format: 0 = 8 bit mono, 1 = 8 bit stereo, 2 = 16 bit mono, 3 = 16 bit stereo (both signed, "offset binary"
 * flag clear), 4 / 5 = 16 bit mono / stereo with the flag set; anything else passes the code itself for bits,
 * channels and flag (an error the original does not catch). */
void Mixer_MixVoiceByFormat(byte *data, int accumOffset, uint outFrames, int srcBytes,
                            int unused, int volume, int pan, int format)
{
    int bits = format, channels = format, flag = format;

    switch (format) {
    case 0: flag = 1; bits = 8;  channels = 1; break;
    case 1: flag = 1; bits = 8;  channels = 2; break;
    case 2: flag = 0; bits = 16; channels = 1; break;
    case 3: flag = 0; bits = 16; channels = 2; break;
    case 4: flag = 1; bits = 16; channels = 1; break;
    case 5: flag = 1; bits = 16; channels = 2; break;
    }
    Mixer_MixVoice(data, srcBytes / ((bits >> 3) * channels), bits, channels, outFrames, accumOffset,
                   volume, (pan + 0x7f) / 2, flag, 0);
}

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
    g_dwMixChannels = channels;
    g_dwMixAccumBytes = frames4 * 4;
    g_pMixAccum = (int *)((int (*)(int, const char *, int))services[0])(g_dwMixAccumBytes,
                                                                        s_C__grimsrc_libs_lecsmush_insane__004f4158, 0x356);
    if (g_pMixAccum == 0)
        return 0xffffffff;
    _DAT_008dcda0 = unused;
    comp = (short *)((int (*)(int, const char *, int))services[0])(g_dwMixTableUnits << 16,
                                                                  s_C__grimsrc_libs_lecsmush_insane__004f4158, 0x35c);
    g_pMixCompanderTable = comp;
    if (comp == 0)
        return 0xffffffff;
    /* companding curve: ((524272 i) / (262136 + 7 i) + 1) / 2 */
    for (i = 0; i < (int)(g_dwMixTableUnits << 15); i++) {
        long double x = (long double)i;
        long double num = x * 524272.0;
        long double den = 262136.0 - x * -7.0;
        *comp++ = (short)(int)((num / den - -1.0) * 0.5);
    }
    return 0;
}

int Mixer_Init(int *services, uint tableUnits, int frames)
{
    g_dwMixTableUnits = tableUnits;
    return Mixer_InitTables(services, 2, frames * 4, 0);
}

/* Frees the compander table and the accumulator through services[1](ptr, file, line). */
int Mixer_Free(int *services)
{
    if (g_pMixCompanderTable != 0)
        ((void (*)(void *, const char *, int))services[1])(g_pMixCompanderTable, s_C__grimsrc_libs_lecsmush_insane__004f4158, 0x379);
    g_pMixCompanderTable = 0;
    if (g_pMixAccum != 0)
        ((void (*)(void *, const char *, int))services[1])(g_pMixAccum, s_C__grimsrc_libs_lecsmush_insane__004f4158, 0x37a);
    g_pMixAccum = 0;
    return 0;
}

#endif /* GRIM_EXE */
