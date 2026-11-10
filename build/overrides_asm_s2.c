/* Readable C for software-rasteriser span functions of GRIMFANDANGO.EXE (slice 2, 0x0041a130 - 0x0042b1f0).
 *
 * Each function below replaces the assembled original at the address given in its comment.  The C was written
 * against the 1.01 machine code (src/GRIMFANDANGO.EXE/asm_funcs.s); the decompiled text is kept under `#if 0` by
 * tools/build_src.py.  Names and types are Ghidra's; struct offsets are the raw byte offsets used by the code
 * (param[0xe] = +0x38, param[0x10] = +0x40).  The 64-bit fixed point products of the original (imul to EDX:EAX,
 * shrd by 16) are written as long long >> 16.  Notes: docs/notes/asm_s2.md.
 */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

/* ==== rdRaster_Span8_Flat (0x0041a810) ====
 * Fills one horizontal span of an 8 bit paletted target.  param_1 / param_2 are the left and right edge records
 * (16.16 x at +0x00, a 16.16 per-scanline value at +0x38, another at +0x40 for the target row).  The start and end
 * columns are rounded up to whole pixels; the span is `count` pixels long; each pixel gets a value from the 64 level
 * table (DAT_008fbfc0, 1/n in 16.16) and a shade byte through UINT_008ddeb0 + ((x >> 8) & 0x3f00) + DAT_008ddec0. */
void rdRaster_Span8_Flat(uint *param_1, uint *param_2)
{
    uint xl_raw = *param_1;                 /* left x, 16.16 */
    uint xl = xl_raw;                       /* ceiling to whole pixel */
    uint xr;
    int count, step, x;
    long long prod;
    int dx;
    int *cam;
    uint8_t *dst;
    unsigned int idx;
    int cur, camInfo;

    if (xl_raw & 0xffff)
        xl = (xl_raw + 0x10000) & 0xffff0000u;

    xr = *param_2;
    if (xr & 0xffff)
        xr = (xr + 0x10000) & 0xffff0000u;

    count = ((int)xr >> 16) - ((int)xl >> 16);
    if (count <= 0)
        return;

    /* per-pixel step: (dz) * reciprocal(count), as 16.16 */
    prod = (long long)(int)(param_2[0xe] - param_1[0xe]) * (long long)((int *)&DAT_008fbfc0)[count];
    step = (int)(prod >> 16);
    if (step < 0 && step > -0x51e)
        step = 0;

    /* start value: (xl - xl_raw) * step + param_1[0xe] */
    dx = (int)(xl - xl_raw);
    prod = (long long)dx * (long long)step;
    cur = (int)(prod >> 16) + (int)param_1[0xe];

    camInfo = *(int *)((int)g_pRdCamera_CurCamera + 4);
    camInfo = *(int *)(camInfo + 4);
    dst = (uint8_t *)((int)param_1[0x10] * *(int *)(camInfo + 0x18) + *(int *)(camInfo + 0x5c) + ((int)xl >> 16));

    do {
        idx = (unsigned int)cur >> 8;
        cur += step;
        count--;
        *dst = *(uint8_t *)((uintptr_t)UINT_008ddeb0 + (idx & 0x3f00) + (uintptr_t)DAT_008ddec0);
        dst++;
    } while (count != 0);
}

/* ==== rdRaster_Span16_Flat_3 (0x0041a900) ====
 * The 16 bit version of rdRaster_Span8_Flat: the same span set-up, but each pixel is a word read from the table at
 * UINT_008ddebc with index ((x >> 16) & 0x3f) * 0x100 + DAT_008ddec0, and written through PTR_007f43a8, which the
 * original keeps in a global and advances by 2 bytes per pixel (the global is left at the end of the span). */
void rdRaster_Span16_Flat_3(uint *param_1, uint *param_2)
{
    uint xl_raw = *param_1;
    uint xl = xl_raw;
    uint xr;
    int count, step, cur, dx;
    long long prod;
    int camInfo;
    uint pitch_half;
    uint xl_int;

    if (xl_raw & 0xffff)
        xl = (xl_raw + 0x10000) & 0xffff0000u;

    xr = *param_2;
    if (xr & 0xffff)
        xr = (xr + 0x10000) & 0xffff0000u;

    count = ((int)xr >> 16) - ((int)xl >> 16);
    if (count <= 0)
        return;

    prod = (long long)(int)(param_2[0xe] - param_1[0xe]) * (long long)((int *)&DAT_008fbfc0)[count];
    step = (int)(prod >> 16);
    if (step < 0 && step > -0x51e)
        step = 0;

    dx = (int)(xl - xl_raw);
    prod = (long long)dx * (long long)step;
    cur = (int)(prod >> 16) + (int)param_1[0xe];

    camInfo = *(int *)((int)g_pRdCamera_CurCamera + 4);
    camInfo = *(int *)(camInfo + 4);
    pitch_half = *(uint *)(camInfo + 0x18) >> 1;
    xl_int = (uint)((int)xl >> 16);
    PTR_007f43a8 = (int *)(*(int *)(camInfo + 0x5c) +
                           ((int)param_1[0x10] * (int)pitch_half + (int)xl_int) * 2);

    do {
        uint u = (uint)cur >> 16;
        cur += step;
        *(uint16_t *)PTR_007f43a8 = *(uint16_t *)(UINT_008ddebc + ((u & 0x3f) * 0x100 + (uintptr_t)DAT_008ddec0) * 2);
        PTR_007f43a8 = (int *)((char *)PTR_007f43a8 + 2);
        count--;
    } while (count != 0);
}

#endif /* GRIM_EXE */
