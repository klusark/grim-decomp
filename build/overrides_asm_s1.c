/* Readable C for the software rasteriser functions of GRIMFANDANGO.EXE, slice 1 (agent asm_s1).
 *
 * Each function below replaces an assembled function at the address given in its comment.  Every C version was written
 * against the original instructions (src/GRIMFANDANGO.EXE/asm_funcs.s), not only against Ghidra's decompilation; the
 * decompilation was used for names and for the structure of the code.  Offsets are the byte offsets of the 1.01 records:
 * a span / edge record is an array of dwords (`int *`), the offsets are written as `[index]` where the original uses
 * `+0x..`.  Calling convention: cdecl (every function ends in a plain `ret`).
 * docs/notes/asm_s1.md lists how each one was checked. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

/* ==== rdAFRaster_SetupNGonLW (0x0040f5f0) ====
 * Builds the 1/w table of a polygon (the record in param_1[0] holds a count at +0x1c and an array of 12 byte vertices
 * at +0x20, the w value at +8 of each), stores the flat span callback, the colour (dword of param_2 + 4) and the edge
 * callback into the polygon record. */
void rdAFRaster_SetupNGonLW(float *param_1,int param_2)
{
    int rec = ((int *)param_1)[0];
    unsigned int count = *(unsigned int *)(rec + 0x1c);
    int base = *(int *)(rec + 0x20);
    unsigned int k;

    if (count != 0) {
        for (k = 0; k < count; k++) {
            param_1[k + 1] = 1.0f / *(float *)(base + 12 * k + 8);
        }
    }
    ((int *)param_1)[0x6d] = (int)rdAFRaster_DrawNGonLW;       /* +0x1b4 */
    ((int *)param_1)[0x74] = *(int *)(param_2 + 4);             /* +0x1d0 colour (copied as bits) */
    ((int *)param_1)[0x7a] = (int)rdAFRaster_SetupEdgeNGonLW;      /* +0x1e8 */
}

/* ==== rdAFRaster_DrawNGonLW (0x0040f650) ====
 * Span callback of the flat selector: picks the colour byte (8 bpp, +0x1d0) or the 16 bit colour from the palette table
 * (16 bpp, index = byte at +0x1d0) and draws each span of the list at +0x1b8 (linked by +0x28). */
void rdAFRaster_DrawNGonLW(int *param_1)
{
    int node = param_1[0x6e];
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4) + 0x24);

    if (bpp == 8) {
        g_bRdAFRaster_color = ((unsigned char *)param_1)[0x1d0];
        if (node != 0) {
            do {
                rdAFRaster_DrawSpanNGonLW_8((int *)node);
                node = *(int *)(node + 0x28);
            } while (node != 0);
        }
    }
    else if (bpp == 0x10) {
        g_wRdAFRaster_RGBcolor = *(unsigned short *)(*(int *)(*(int *)(*param_1 + 0x4c) + 0x348) + 0x7e00 +
                                           (unsigned int)((unsigned char *)param_1)[0x1d0] * 2);
        for (; node != 0; node = *(int *)(node + 0x28)) {
            rdAFRaster_DrawSpanNGonLW_16((int *)node);
        }
    }
}

/* ==== rdAFRaster_DrawSpanNGonLW_8 (0x0040f6d0) ====
 * Wireframe span at 8 bpp: writes the colour g_bRdAFRaster_color at the first and the last pixel of the span.
 * Span record: [0] x, [1] length, [2] y.  Pixel = base + y * pitch + x (camera record +4 +4, pitch +0x18, base +0x5c). */
void rdAFRaster_DrawSpanNGonLW_8(int *param_1)
{
    int iVar1 = *(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4);
    unsigned char *puVar2 = (unsigned char *)(param_1[2] * *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x5c) + param_1[0]);

    *puVar2 = g_bRdAFRaster_color;
    puVar2[param_1[1] - 1] = g_bRdAFRaster_color;
}

/* ==== rdAFRaster_DrawSpanNGonLW_16 (0x0040f710) ====
 * The same at 16 bpp: pitch is halved (unsigned), the colour is g_wRdAFRaster_RGBcolor. */
void rdAFRaster_DrawSpanNGonLW_16(int *param_1)
{
    int iVar2 = *(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4);
    unsigned short *puVar1 = (unsigned short *)
        (*(int *)(iVar2 + 0x5c) + (param_1[2] * (int)(*(unsigned int *)(iVar2 + 0x18) >> 1) + param_1[0]) * 2);

    *puVar1 = g_wRdAFRaster_RGBcolor;
    puVar1[param_1[1] - 1] = g_wRdAFRaster_RGBcolor;
}

/* ==== rdRaster_EdgeStepFlat (0x0040f750) ====
 * Advances an edge record one scanline: integer x (+0x28) += dx (+0x2c); float attribute +0x10 += +0x14. */
void rdRaster_EdgeStepFlat(int param_1)
{
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2c);
    *(float *)(param_1 + 0x10) = *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x10);
}

/* ==== rdAFRaster_SetupNGonLS (0x0040fa20) ====
 * The same as rdAFRaster_SetupNGonLW with the texture span callback (rdAFRaster_DrawNGonLS) and the second edge
 * setup.  Constant of the division: 1.0 (Ghidra's read of the constant at rdata+0x738). */
void rdAFRaster_SetupNGonLS(float *param_1,int param_2)
{
    int rec = ((int *)param_1)[0];
    unsigned int count = *(unsigned int *)(rec + 0x1c);
    int base = *(int *)(rec + 0x20);
    unsigned int k;

    if (count != 0) {
        for (k = 0; k < count; k++) {
            param_1[k + 1] = 1.0f / *(float *)(base + 12 * k + 8);
        }
    }
    ((int *)param_1)[0x6d] = (int)rdAFRaster_DrawNGonLS;        /* +0x1b4 */
    ((int *)param_1)[0x74] = *(int *)(param_2 + 4);             /* +0x1d0 */
    ((int *)param_1)[0x7a] = (int)rdAFRaster_SetupEdgeNGonLS;    /* +0x1e8 */
}

/* ==== rdAFRaster_DrawNGonLS (0x0040fa80) ====
 * Span callback of the texture selector: fills the spans with the flat colour (8 bpp: bytes, 16 bpp: words from
 * g_wRdAFRaster_RGBcolor), then sets g_dwRdAFRaster_dOneOverZdXFixed and calls the per-span textured drawer of the camera's flag at +0x14. */
void rdAFRaster_DrawNGonLS(int *param_1)
{
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4) + 0x24);
    int node;
    int iVar1;
    unsigned int cnt;
    unsigned int i;

    if (bpp == 8) {
        g_bRdAFRaster_color = ((unsigned char *)param_1)[0x1d0];
    }
    else if (bpp == 0x10) {
        g_wRdAFRaster_RGBcolor = *(unsigned short *)(*(int *)(*(int *)(*param_1 + 0x4c) + 0x348) + 0x7e00 +
                                           (unsigned int)((unsigned char *)param_1)[0x1d0] * 2);
    }
    g_dwRdAFRaster_dOneOverZdXFixed = param_1[0x67];                              /* +0x19c */

    if (bpp == 8) {
        for (node = param_1[0x6e]; node != 0; node = *(int *)(node + 0x28)) {
            unsigned char *dst;
            iVar1 = *(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4);
            dst = (unsigned char *)(*(int *)(node + 8) * *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x5c) + *(int *)node);
            cnt = *(unsigned int *)(node + 4);
            for (i = 0; i < cnt; i++) {
                dst[i] = g_bRdAFRaster_color;
            }
        }
    }
    else if (bpp == 0x10) {
        for (node = param_1[0x6e]; node != 0; node = *(int *)(node + 0x28)) {
            unsigned short *dst;
            iVar1 = *(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4);
            dst = (unsigned short *)(*(int *)(iVar1 + 0x5c) +
                                     (*(int *)(node + 8) * (int)(*(unsigned int *)(iVar1 + 0x18) >> 1) + *(int *)node) * 2);
            for (cnt = *(unsigned int *)(node + 4); cnt != 0; cnt--) {
                *dst = g_wRdAFRaster_RGBcolor;
                dst++;
            }
        }
    }

    node = param_1[0x6e];
    if (*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 0x14) == 0) {
        for (; node != 0; node = *(int *)(node + 0x28)) {
            rdRaster_SpanR_FlatZw((int *)node);
        }
    }
    else {
        for (; node != 0; node = *(int *)(node + 0x28)) {
            rdRaster_SpanR_FlatZw_2((int *)node);
        }
    }
}

/* ==== FUN_004104b0 (0x004104b0) ====
 * Edge step: x (+0x28) += dx (+0x2c), float +0x10 += +0x14, int +0x40 += +0x44. */
void FUN_004104b0(int param_1)
{
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2c);
    *(float *)(param_1 + 0x10) = *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x10);
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + *(int *)(param_1 + 0x44);
}

/* ==== FUN_00411b70 (0x00411b70) ====
 * Edge step: x (+0x28) += dx (+0x2c), float +0x10 += +0x14, int +0x30 += +0x34, int +0x38 += +0x3c. */
void FUN_00411b70(int param_1)
{
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2c);
    *(float *)(param_1 + 0x10) = *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x10);
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x34);
    *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x3c);
}

/* ==== FUN_00415180 (0x00415180) ====
 * Edge step: three float attributes += their deltas (+0x10 += +0x14, +0x18 += +0x1c, +0x20 += +0x24), x (+0x28) += dx.
 * The original keeps the three sums on the x87 stack and stores them at the end: the same values as these statements. */
void FUN_00415180(int param_1)
{
    *(float *)(param_1 + 0x10) = *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x10);
    *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x1c) + *(float *)(param_1 + 0x18);
    *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x20);
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2c);
}

/* ==== FUN_004151c0 (0x004151c0) ====
 * Edge step: x (+0x28) += dx (+0x2c) only. */
void FUN_004151c0(int param_1)
{
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2c);
}

/* ==== rdAFRaster_AdvanceLeftEdgeNGonGIT (0x004169f0) ====
 * Edge step: x (+0x28) += dx (+0x2c), float +0x10 += +0x14, int +0x40 += +0x44, float +0x18 += +0x1c,
 * float +0x20 += +0x24. */
void rdAFRaster_AdvanceLeftEdgeNGonGIT(int param_1)
{
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2c);
    *(float *)(param_1 + 0x10) = *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x10);
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + *(int *)(param_1 + 0x44);
    *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x1c) + *(float *)(param_1 + 0x18);
    *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x20);
}

/* ==== rdAFRaster_AdvanceRightEdgeNGonGIT (0x00416a30) ====
 * Edge step: x (+0x28) += dx (+0x2c), int +0x40 += +0x44. */
void rdAFRaster_AdvanceRightEdgeNGonGIT(int param_1)
{
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2c);
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + *(int *)(param_1 + 0x44);
}

/* ==== FUN_004129f0 (0x004129f0) ====
 * Edge step: x (+0x28) += dx (+0x2c), int +0x30 += +0x34, float +0x10 += +0x14, int +0x38 += +0x3c, int +0x40 += +0x44. */
void FUN_004129f0(int param_1)
{
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2c);
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x34);
    *(float *)(param_1 + 0x10) = *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x10);
    *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x3c);
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + *(int *)(param_1 + 0x44);
}

/* ==== rdAFRaster_DrawNGonMLAT (0x00411330) ====
 * Copies the polygon's state (+0x1c0 .. +0x1d8, +0x19c, +0x1e0 for 16 bpp) into the rasteriser globals, then draws
 * every span of the list at +0x1b8 with the 8 / 16 bit "TexKey" span routine of the camera's bpp (+0x24). */
void rdAFRaster_DrawNGonMLAT(int param_1)
{
    int iVar1;
    int iVar2;

    iVar1 = *(int *)(*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4) + 0x24);
    if (iVar1 == 0x10) {
        g_dwRdAFRaster_aRGBMap = *(unsigned int *)(param_1 + 0x1e0);
    }
    g_dwRdAFRaster_mipMapNum = *(unsigned int *)(param_1 + 0x1c0);
    g_dwRdAFRaster_pPixels = *(unsigned int *)(param_1 + 0x1c4);
    g_dwRdAFRaster_texRowShift = *(unsigned int *)(param_1 + 0x1c8);
    _g_dwRdAFRaster_texPitch = *(undefined4 *)(param_1 + 0x1cc);
    g_dwRdAFRaster_uWrap = *(unsigned int *)(param_1 + 0x1d4);
    g_dwRdAFRaster_vWrap = *(unsigned int *)(param_1 + 0x1d8);
    g_dwRdAFRaster_dOneOverZdXFixed = *(unsigned int *)(param_1 + 0x19c);
    for (iVar2 = *(int *)(param_1 + 0x1b8); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x28)) {
        if (iVar1 == 8) {
            rdAFRaster_DrawSpanNGonMLAT_8((int *)iVar2);
        }
        else if (iVar1 == 0x10) {
            rdAFRaster_DrawSpanNGonMLAT_16((int *)iVar2);
        }
    }
}

/* ==== rdAFRaster_DrawNGonFS (0x0040ff20) ====
 * Span callback of the lit selector: g_bRdAFRaster_color = colour byte (+0x1d0), g_dwRdAFRaster_dOneOverZdXFixed = light step (+0x19c).  Every
 * span of the list at +0x1b8 is filled with the colour byte (whatever the bpp: bytes at the pixel address), then the
 * spans are drawn with the FlatZw routine chosen by the camera's flag at +0x14 (as rdAFRaster_DrawNGonLS). */
void rdAFRaster_DrawNGonFS(int param_1)
{
    int node;
    int iVar5;
    unsigned int cnt;
    unsigned int i;
    unsigned char *dst;

    g_bRdAFRaster_color = ((unsigned char *)param_1)[0x1d0];
    g_dwRdAFRaster_dOneOverZdXFixed = *(unsigned int *)(param_1 + 0x19c);
    for (node = *(int *)(param_1 + 0x1b8); node != 0; node = *(int *)(node + 0x28)) {
        iVar5 = *(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4);
        cnt = *(unsigned int *)(node + 4);
        dst = (unsigned char *)(*(int *)(node + 8) * *(int *)(iVar5 + 0x18) + *(int *)(iVar5 + 0x5c) + *(int *)node);
        for (i = 0; i < cnt; i++) {
            dst[i] = g_bRdAFRaster_color;
        }
    }

    node = *(int *)(param_1 + 0x1b8);
    if (*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 0x14) == 0) {
        for (; node != 0; node = *(int *)(node + 0x28)) {
            rdRaster_SpanR_FlatZw((int *)node);
        }
    }
    else {
        for (; node != 0; node = *(int *)(node + 0x28)) {
            rdRaster_SpanR_FlatZw_2((int *)node);
        }
    }
}

/* ==== rdAFRaster_SetupNGonGS (0x00410290) ====
 * Selector for flat lit polygons: builds the 1/w table as rdAFRaster_SetupNGonLW, copies the colour (+0x1d0), stores the
 * light / palette pointer for the camera's bpp (+0x1dc for 8 bpp from the record's +0x4c table +0x330, +0x1e0 for 16 bpp
 * from +0x348), then the span callback rdAFRaster_DrawNGonGS and the edge setup.  The raw dwords are copied as ints (they are
 * pointers or colour bits, not floats). */
void rdAFRaster_SetupNGonGS(float *param_1,int param_2)
{
    int rec = ((int *)param_1)[0];
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4) + 0x24);
    unsigned int count = *(unsigned int *)(rec + 0x1c);
    int base = *(int *)(rec + 0x20);
    unsigned int k;

    if (count != 0) {
        for (k = 0; k < count; k++) {
            param_1[k + 1] = 1.0f / *(float *)(base + 12 * k + 8);
        }
    }
    ((int *)param_1)[0x74] = *(int *)(param_2 + 4);             /* +0x1d0 */
    if (bpp == 8) {
        ((int *)param_1)[0x77] = *(int *)(*(int *)(rec + 0x4c) + 0x330);   /* +0x1dc */
    }
    else if (bpp == 0x10) {
        ((int *)param_1)[0x78] = *(int *)(*(int *)(rec + 0x4c) + 0x348);   /* +0x1e0 */
    }
    ((int *)param_1)[0x6d] = (int)rdAFRaster_DrawNGonGS;                 /* +0x1b4 */
    ((int *)param_1)[0x7a] = (int)rdAFRaster_SetupEdgeNGonGS;    /* +0x1e8 */
}

/* ==== rdAFRaster_SetupNGonLAT (0x004108b0) ====
 * Selector for the lit polygon with a 16 bit texture / palette: calls rdAFRaster_CalcAffineGradients(param_1, count - 1), then
 * takes the table entry for the index in param_1[0x70] (the source's +0x1c table: +0x5c -> param_1[0x71], +0x18 ->
 * param_1[0x73]), the shifts and masks of the colour fields (+0x0c, +0x10, +0x14; shift counts masked to 5 bits as the
 * x86 shifts do) into param_1[0x72], [0x75], [0x76], and for 16 bpp the table address (+0x7e00) into param_1[0x78]. */
void rdAFRaster_SetupNGonLAT(int *param_1,int param_2)
{
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4) + 0x24);
    int iVar2;

    rdAFRaster_CalcAffineGradients((float *)param_1, *(int *)(*(int *)(param_2 + 0x1c) + 0x18) - 1);
    iVar2 = param_1[0x70];
    param_1[0x71] = *(int *)(*(int *)(*(int *)(param_2 + 0x1c) + 0x1c + iVar2 * 4) + 0x5c);
    param_1[0x73] = *(int *)(*(int *)(*(int *)(param_2 + 0x1c) + 0x1c + iVar2 * 4) + 0x18);
    param_1[0x72] = *(int *)(*(int *)(param_2 + 0x1c) + 0xc) - iVar2;
    param_1[0x75] = (int)((*(unsigned int *)(*(int *)(param_2 + 0x1c) + 0x10) >> ((unsigned char)iVar2 & 0x1f)) << 0x10);
    param_1[0x76] = (int)((*(unsigned int *)(*(int *)(param_2 + 0x1c) + 0x14) >> ((unsigned char)iVar2 & 0x1f))
                          << ((unsigned char)param_1[0x72] & 0x1f));
    if (bpp == 0x10) {
        param_1[0x78] = *(int *)(*(int *)(*param_1 + 0x4c) + 0x348) + 0x7e00;
    }
    param_1[0x6d] = (int)rdAFRaster_DrawNGonLAT;
    param_1[0x7a] = (int)rdAFRaster_SetupEdgeNGonLAT;
}

/* ==== rdAFRaster_SetupNGonMLAT (0x00411270) ====
 * The same selector as rdAFRaster_SetupNGonLAT with the span callback rdAFRaster_DrawNGonMLAT and the edge setup _5; 16 bpp
 * palette table at +0x7e00 into param_1[0x78]. */
void rdAFRaster_SetupNGonMLAT(int *param_1,int param_2)
{
    int iVar1 = *(int *)(*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4) + 0x24);
    int iVar2;

    rdAFRaster_CalcAffineGradients((float *)param_1, *(int *)(*(int *)(param_2 + 0x1c) + 0x18) - 1);
    iVar2 = param_1[0x70];
    param_1[0x71] = *(int *)(*(int *)(*(int *)(param_2 + 0x1c) + 0x1c + iVar2 * 4) + 0x5c);
    param_1[0x73] = *(int *)(*(int *)(*(int *)(param_2 + 0x1c) + 0x1c + iVar2 * 4) + 0x18);
    param_1[0x72] = *(int *)(*(int *)(param_2 + 0x1c) + 0xc) - iVar2;
    param_1[0x75] = (int)((*(unsigned int *)(*(int *)(param_2 + 0x1c) + 0x10) >> ((unsigned char)iVar2 & 0x1f)) << 0x10);
    param_1[0x76] = (int)((*(unsigned int *)(*(int *)(param_2 + 0x1c) + 0x14) >> ((unsigned char)iVar2 & 0x1f))
                          << ((unsigned char)param_1[0x72] & 0x1f));
    if (iVar1 == 0x10) {
        param_1[0x78] = *(int *)(*(int *)(*param_1 + 0x4c) + 0x348) + 0x7e00;
    }
    param_1[0x6d] = (int)rdAFRaster_DrawNGonMLAT;
    param_1[0x7a] = (int)rdAFRaster_SetupEdgeNGonLAT;
}

/* Shared body of rdAFRaster_SetupNGonGAT and _7 (asm 0x004124f0 and 0x00413040, identical except for the span callback
 * and the edge setup): the 8 bpp palette word is at +0x330 of the material table, the 16 bpp one at +0x348 WITHOUT the
 * +0x7e00 offset that _2 / _3 add. */
static inline void select_flatlit_nooffset(int *param_1, int param_2, int span_fn_is_6)
{
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4) + 0x24);
    int iVar2;
    int rec;

    rdAFRaster_CalcAffineGradients((float *)param_1, *(int *)(*(int *)(param_2 + 0x1c) + 0x18) - 1);
    iVar2 = param_1[0x70];
    param_1[0x71] = *(int *)(*(int *)(*(int *)(param_2 + 0x1c) + 0x1c + iVar2 * 4) + 0x5c);
    if (bpp == 8) {
        rec = *param_1;
        param_1[0x77] = *(int *)(*(int *)(rec + 0x4c) + 0x330);
    }
    else if (bpp == 0x10) {
        rec = *param_1;
        param_1[0x78] = *(int *)(*(int *)(rec + 0x4c) + 0x348);
    }
    param_1[0x73] = *(int *)(*(int *)(*(int *)(param_2 + 0x1c) + 0x1c + iVar2 * 4) + 0x18);
    param_1[0x72] = *(int *)(*(int *)(param_2 + 0x1c) + 0xc) - iVar2;
    param_1[0x75] = (int)((*(unsigned int *)(*(int *)(param_2 + 0x1c) + 0x10) >> ((unsigned char)iVar2 & 0x1f)) << 0x10);
    param_1[0x76] = (int)((*(unsigned int *)(*(int *)(param_2 + 0x1c) + 0x14) >> ((unsigned char)iVar2 & 0x1f))
                          << ((unsigned char)param_1[0x72] & 0x1f));
    if (span_fn_is_6) {
        param_1[0x6d] = (int)rdAFRaster_DrawNGonGAT;
        param_1[0x7a] = (int)rdAFRaster_SetupEdgeNGonGAT;
    }
    else {
        param_1[0x6d] = (int)rdAFRaster_DrawNGonMGAT;
        param_1[0x7a] = (int)rdAFRaster_SetupEdgeNGonGAT;
    }
}

/* ==== rdAFRaster_SetupNGonGAT (0x004124f0) ==== see select_flatlit_nooffset: span callback rdAFRaster_DrawNGonGAT. */
void rdAFRaster_SetupNGonGAT(int *param_1,int param_2)
{
    select_flatlit_nooffset(param_1, param_2, 1);
}

/* ==== rdAFRaster_SetupNGonMGAT (0x00413040) ==== see select_flatlit_nooffset: span callback rdAFRaster_DrawNGonMGAT. */
void rdAFRaster_SetupNGonMGAT(int *param_1,int param_2)
{
    select_flatlit_nooffset(param_1, param_2, 0);
}

/* ==== rdNRaster_DrawScanLineNGonLS_16 (0x004195f0) ====
 * 16 bit flat span: x range from the 16.16 fixed-point ends (*param_1 and *param_2, each rounded up to a whole pixel),
 * a write cursor g_pWDest at (row param_1[0x10]) of the camera's buffer (+0x5c, pitch halved), and the colour word
 * g_wRdNRaster_RGBcolor written for each pixel of the span.  Nothing is written for an empty span (the cursor is left alone). */
void rdNRaster_DrawScanLineNGonLS_16(uint *param_1,uint *param_2)
{
    unsigned int uVar2 = *param_1;
    unsigned int uVar3;
    int iVar4;
    int iVar1;

    if ((uVar2 & 0xffff) != 0) {
        uVar2 = (uVar2 + 0x10000) & 0xffff0000;
    }
    uVar3 = *param_2;
    if ((uVar3 & 0xffff) != 0) {
        uVar3 = (uVar3 + 0x10000) & 0xffff0000;
    }
    iVar4 = (int)((uVar3 >> 0x10) - (uVar2 >> 0x10));
    if (0 < iVar4) {
        iVar1 = *(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4);
        g_pWDest = (int *)(*(int *)(iVar1 + 0x5c) +
                              ((int)param_1[0x10] * (int)(*(unsigned int *)(iVar1 + 0x18) >> 1) + (int)(uVar2 >> 0x10)) * 2);
        do {
            *(unsigned short *)g_pWDest = g_wRdNRaster_RGBcolor;
            g_pWDest = (int *)((char *)g_pWDest + 2);
            iVar4 = iVar4 - 1;
        } while (iVar4 != 0);
    }
}

/* ==== rdNRaster_DrawScanLineNGonFS_16 (0x00419ee0) ====
 * Same body as rdNRaster_DrawScanLineNGonLS_16 (the asm of both is the same instruction sequence). */
void rdNRaster_DrawScanLineNGonFS_16(uint *param_1,uint *param_2)
{
    unsigned int uVar2 = *param_1;
    unsigned int uVar3;
    int iVar4;
    int iVar1;

    if ((uVar2 & 0xffff) != 0) {
        uVar2 = (uVar2 + 0x10000) & 0xffff0000;
    }
    uVar3 = *param_2;
    if ((uVar3 & 0xffff) != 0) {
        uVar3 = (uVar3 + 0x10000) & 0xffff0000;
    }
    iVar4 = (int)((uVar3 >> 0x10) - (uVar2 >> 0x10));
    if (0 < iVar4) {
        iVar1 = *(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4);
        g_pWDest = (int *)(*(int *)(iVar1 + 0x5c) +
                              ((int)param_1[0x10] * (int)(*(unsigned int *)(iVar1 + 0x18) >> 1) + (int)(uVar2 >> 0x10)) * 2);
        do {
            *(unsigned short *)g_pWDest = g_wRdNRaster_RGBcolor;
            g_pWDest = (int *)((char *)g_pWDest + 2);
            iVar4 = iVar4 - 1;
        } while (iVar4 != 0);
    }
}

/* ==== rdRaster_Span_Flat (0x00419e60) ====
 * 8 bit flat span: the same x range as rdNRaster_DrawScanLineNGonLS_16; the pixels at row param_1[0x10] of the camera's buffer
 * (pitch not halved) are set to the colour byte g_bRdNRaster_color (the original's rep stosd / rep stosb is a byte fill). */
void rdRaster_Span_Flat(uint *param_1,uint *param_2)
{
    unsigned int uVar3 = *param_1;
    unsigned int uVar4;
    unsigned int i;
    int iVar1;
    unsigned char *dst;

    if ((uVar3 & 0xffff) != 0) {
        uVar3 = (uVar3 + 0x10000) & 0xffff0000;
    }
    uVar4 = *param_2;
    if ((uVar4 & 0xffff) != 0) {
        uVar4 = (uVar4 + 0x10000) & 0xffff0000;
    }
    uVar4 = (uVar4 >> 0x10) - (uVar3 >> 0x10);
    if (0 < (int)uVar4) {
        iVar1 = *(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4);
        dst = (unsigned char *)((int)param_1[0x10] * *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x5c) + (int)(uVar3 >> 0x10));
        for (i = 0; i < uVar4; i++) {
            dst[i] = g_bRdNRaster_color;
        }
    }
}

/* ==== rdAFRaster_DrawNGonMFAT (0x004121a0) ====  span dispatcher of rdAFRaster_SetupNGonMFAT ====
 * Copies the polygon record's fields (record offsets in the comments; p[n] is the dword at +4n) into the rasteriser globals:
 * +0x1c0 and +0x1c4 always; the 8 bpp path copies +0x1dc only, the 16 bpp path copies +0x1e0, +0x1c8, +0x1cc, +0x1d4,
 * +0x1d8, +0x1a0, +0x1a4 and +0x19c.  Then rdAFRaster_DrawSpanNGonMFAT_8 / rdAFRaster_DrawSpanNGonMFAT_16 is called for each span of the
 * list at +0x1b8 (linked by +0x28).  The copies are dword bit copies. */
void rdAFRaster_DrawNGonMFAT(int param_1)
{
    int *p = (int *)param_1;
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4) + 0x24);
    int node;

    g_dwRdAFRaster_mipMapNum = p[0x70];
    g_dwRdAFRaster_pPixels = p[0x71];
    if (bpp == 8) {
        g_dwRdAFRaster_aMonoMap = p[0x77];
    }
    else if (bpp == 0x10) {
        g_dwRdAFRaster_aRGBMap = p[0x78];
        g_dwRdAFRaster_texRowShift = p[0x72];
        _g_dwRdAFRaster_texPitch = p[0x73];
        g_dwRdAFRaster_uWrap = p[0x75];
        g_dwRdAFRaster_vWrap = p[0x76];
        g_dwRdAFRaster_dUdXModifier = p[0x68];
        g_dwRdAFRaster_dVdXModifier = p[0x69];
        g_dwRdAFRaster_dOneOverZdXFixed = p[0x67];
    }
    node = p[0x6e];
    if (node != 0) {
        do {
            if (bpp == 8) {
                rdAFRaster_DrawSpanNGonMFAT_8((int *)node);
            }
            else if (bpp == 0x10) {
                rdAFRaster_DrawSpanNGonMFAT_16((int *)node);
            }
            node = *(int *)(node + 0x28);
        } while (node != 0);
    }
}

/* ==== rdAFRaster_DrawNGonMGAT (0x00413110) ====  span dispatcher of rdAFRaster_SetupNGonMGAT ====
 * Identical to rdAFRaster_DrawNGonMFAT except for the span routines: rdAFRaster_DrawSpanNGonMGAT_8 / rdAFRaster_DrawSpanNGonMGAT_16. */
void rdAFRaster_DrawNGonMGAT(int param_1)
{
    int *p = (int *)param_1;
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4) + 0x24);
    int node;

    g_dwRdAFRaster_mipMapNum = p[0x70];
    g_dwRdAFRaster_pPixels = p[0x71];
    if (bpp == 8) {
        g_dwRdAFRaster_aMonoMap = p[0x77];
    }
    else if (bpp == 0x10) {
        g_dwRdAFRaster_aRGBMap = p[0x78];
        g_dwRdAFRaster_texRowShift = p[0x72];
        _g_dwRdAFRaster_texPitch = p[0x73];
        g_dwRdAFRaster_uWrap = p[0x75];
        g_dwRdAFRaster_vWrap = p[0x76];
        g_dwRdAFRaster_dUdXModifier = p[0x68];
        g_dwRdAFRaster_dVdXModifier = p[0x69];
        g_dwRdAFRaster_dOneOverZdXFixed = p[0x67];
    }
    node = p[0x6e];
    if (node != 0) {
        do {
            if (bpp == 8) {
                rdAFRaster_DrawSpanNGonMGAT_8((int *)node);
            }
            else if (bpp == 0x10) {
                rdAFRaster_DrawSpanNGonMGAT_16((int *)node);
            }
            node = *(int *)(node + 0x28);
        } while (node != 0);
    }
}

/* ==== rdAFRaster_DrawNGonMFIT (0x00415600) ====  span dispatcher (its selector was not checked) ====
 * Copies +0x1c0 always; the 8 bpp path copies +0x1dc; the 16 bpp path copies +0x1e0, +0x1c4, +0x1c8, +0x1cc, +0x1d4,
 * +0x1d8, +0x1a8, +0x1ac, +0x1b0, +0x19c, +0x184, +0x18c, +0x194, +0x1a0, +0x1a4.  Calls rdAFRaster_DrawSpanNGonMFIT_8 /
 * rdAFRaster_DrawSpanNGonMFIT_16 for each span of the list at +0x1b8. */
void rdAFRaster_DrawNGonMFIT(int param_1)
{
    int *p = (int *)param_1;
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4) + 0x24);
    int node;

    g_dwRdAFRaster_mipMapNum = p[0x70];
    if (bpp == 8) {
        g_dwRdAFRaster_aMonoMap = p[0x77];
    }
    else if (bpp == 0x10) {
        g_dwRdAFRaster_aRGBMap = p[0x78];
        g_dwRdAFRaster_pPixels = p[0x71];
        g_dwRdAFRaster_texRowShift = p[0x72];
        _g_dwRdAFRaster_texPitch = p[0x73];
        g_dwRdAFRaster_uWrap = p[0x75];
        g_dwRdAFRaster_vWrap = p[0x76];
        _g_dwRdAFRaster_oneOverZStep = p[0x6a];
        _g_dwRdAFRaster_uOverZStep = p[0x6b];
        _g_dwRdAFRaster_vOverZStep = p[0x6c];
        g_dwRdAFRaster_dOneOverZdXFixed = p[0x67];
        _g_dwRdAFRaster_dOneOverZdX = p[0x61];
        _g_dwRdAFRaster_dUOverZdX = p[0x63];
        _g_dwRdAFRaster_dVOverZdX = p[0x65];
        g_dwRdAFRaster_dUdXModifier = p[0x68];
        g_dwRdAFRaster_dVdXModifier = p[0x69];
    }
    node = p[0x6e];
    if (node != 0) {
        do {
            if (bpp == 8) {
                rdAFRaster_DrawSpanNGonMFIT_8((unsigned int *)node);
            }
            else if (bpp == 0x10) {
                rdAFRaster_DrawSpanNGonMFIT_16((unsigned int *)node);
            }
            node = *(int *)(node + 0x28);
        } while (node != 0);
    }
}

/* ==== rdAFRaster_DrawNGonMGIT (0x00416f80) ====  span dispatcher of rdAFRaster_SetupNGonMGIT ====
 * The same copies as rdAFRaster_DrawNGonMFIT; calls rdAFRaster_DrawSpanNGonMGIT_8 / rdAFRaster_DrawSpanNGonMGIT_16. */
void rdAFRaster_DrawNGonMGIT(int param_1)
{
    int *p = (int *)param_1;
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4) + 0x24);
    int node;

    g_dwRdAFRaster_mipMapNum = p[0x70];
    if (bpp == 8) {
        g_dwRdAFRaster_aMonoMap = p[0x77];
    }
    else if (bpp == 0x10) {
        g_dwRdAFRaster_aRGBMap = p[0x78];
        g_dwRdAFRaster_pPixels = p[0x71];
        g_dwRdAFRaster_texRowShift = p[0x72];
        _g_dwRdAFRaster_texPitch = p[0x73];
        g_dwRdAFRaster_uWrap = p[0x75];
        g_dwRdAFRaster_vWrap = p[0x76];
        _g_dwRdAFRaster_oneOverZStep = p[0x6a];
        _g_dwRdAFRaster_uOverZStep = p[0x6b];
        _g_dwRdAFRaster_vOverZStep = p[0x6c];
        g_dwRdAFRaster_dOneOverZdXFixed = p[0x67];
        _g_dwRdAFRaster_dOneOverZdX = p[0x61];
        _g_dwRdAFRaster_dUOverZdX = p[0x63];
        _g_dwRdAFRaster_dVOverZdX = p[0x65];
        g_dwRdAFRaster_dUdXModifier = p[0x68];
        g_dwRdAFRaster_dVdXModifier = p[0x69];
    }
    node = p[0x6e];
    if (node != 0) {
        do {
            if (bpp == 8) {
                rdAFRaster_DrawSpanNGonMGIT_8((unsigned int *)node);
            }
            else if (bpp == 0x10) {
                rdAFRaster_DrawSpanNGonMGIT_16((unsigned int *)node);
            }
            node = *(int *)(node + 0x28);
        } while (node != 0);
    }
}

/* ==== rdAFRaster_DrawNGonMLIT (0x00413dd0) ====  span dispatcher of rdAFRaster_SetupNGonMLIT ====
 * Copies only for 16 bpp (the 8 bpp path copies nothing): +0x1e0, +0x1c0, +0x1c4, +0x1c8, +0x1cc, +0x1d4, +0x1d8, +0x1a8,
 * +0x1ac, +0x1b0, +0x19c, +0x184, +0x18c, +0x194, +0x1a0, +0x1a4.  Calls rdAFRaster_DrawSpanNGonMLIT_8 / rdAFRaster_DrawSpanNGonMLIT_16
 * for each span of the list at +0x1b8. */
void rdAFRaster_DrawNGonMLIT(int param_1)
{
    int *p = (int *)param_1;
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCamera_CurCamera + 4) + 4) + 0x24);
    int node;

    if (bpp == 0x10) {
        g_dwRdAFRaster_aRGBMap = p[0x78];
        g_dwRdAFRaster_mipMapNum = p[0x70];
        g_dwRdAFRaster_pPixels = p[0x71];
        g_dwRdAFRaster_texRowShift = p[0x72];
        _g_dwRdAFRaster_texPitch = p[0x73];
        g_dwRdAFRaster_uWrap = p[0x75];
        g_dwRdAFRaster_vWrap = p[0x76];
        _g_dwRdAFRaster_oneOverZStep = p[0x6a];
        _g_dwRdAFRaster_uOverZStep = p[0x6b];
        _g_dwRdAFRaster_vOverZStep = p[0x6c];
        g_dwRdAFRaster_dOneOverZdXFixed = p[0x67];
        _g_dwRdAFRaster_dOneOverZdX = p[0x61];
        _g_dwRdAFRaster_dUOverZdX = p[0x63];
        _g_dwRdAFRaster_dVOverZdX = p[0x65];
        g_dwRdAFRaster_dUdXModifier = p[0x68];
        g_dwRdAFRaster_dVdXModifier = p[0x69];
    }
    node = p[0x6e];
    if (node != 0) {
        do {
            if (bpp == 8) {
                rdAFRaster_DrawSpanNGonMLIT_8((unsigned int *)node);
            }
            else if (bpp == 0x10) {
                rdAFRaster_DrawSpanNGonMLIT_16((unsigned int *)node);
            }
            node = *(int *)(node + 0x28);
        } while (node != 0);
    }
}

#endif /* GRIM_EXE */
