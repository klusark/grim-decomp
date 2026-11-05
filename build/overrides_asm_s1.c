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

/* ==== rdRaster_Select_Flat (0x0040f5f0) ====
 * Builds the 1/w table of a polygon (the record in param_1[0] holds a count at +0x1c and an array of 12 byte vertices
 * at +0x20, the w value at +8 of each), stores the flat span callback, the colour (dword of param_2 + 4) and the edge
 * callback into the polygon record. */
void rdRaster_Select_Flat(float *param_1,int param_2)
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
    ((int *)param_1)[0x6d] = (int)rdRaster_SpanFlatSetup;       /* +0x1b4 */
    ((int *)param_1)[0x74] = *(int *)(param_2 + 4);             /* +0x1d0 colour (copied as bits) */
    ((int *)param_1)[0x7a] = (int)rdRaster_EdgeSetup_Flat;      /* +0x1e8 */
}

/* ==== rdRaster_SpanFlatSetup (0x0040f650) ====
 * Span callback of the flat selector: picks the colour byte (8 bpp, +0x1d0) or the 16 bit colour from the palette table
 * (16 bpp, index = byte at +0x1d0) and draws each span of the list at +0x1b8 (linked by +0x28). */
void rdRaster_SpanFlatSetup(int *param_1)
{
    int node = param_1[0x6e];
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4) + 0x24);

    if (bpp == 8) {
        DAT_008ddf40 = ((unsigned char *)param_1)[0x1d0];
        if (node != 0) {
            do {
                rdRaster_SpanOutline8((int *)node);
                node = *(int *)(node + 0x28);
            } while (node != 0);
        }
    }
    else if (bpp == 0x10) {
        DAT_008ddf08 = *(unsigned short *)(*(int *)(*(int *)(*param_1 + 0x4c) + 0x348) + 0x7e00 +
                                           (unsigned int)((unsigned char *)param_1)[0x1d0] * 2);
        for (; node != 0; node = *(int *)(node + 0x28)) {
            rdRaster_SpanOutline16((int *)node);
        }
    }
}

/* ==== rdRaster_SpanOutline8 (0x0040f6d0) ====
 * Wireframe span at 8 bpp: writes the colour DAT_008ddf40 at the first and the last pixel of the span.
 * Span record: [0] x, [1] length, [2] y.  Pixel = base + y * pitch + x (camera record +4 +4, pitch +0x18, base +0x5c). */
void rdRaster_SpanOutline8(int *param_1)
{
    int iVar1 = *(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4);
    unsigned char *puVar2 = (unsigned char *)(param_1[2] * *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x5c) + param_1[0]);

    *puVar2 = DAT_008ddf40;
    puVar2[param_1[1] - 1] = DAT_008ddf40;
}

/* ==== rdRaster_SpanOutline16 (0x0040f710) ====
 * The same at 16 bpp: pitch is halved (unsigned), the colour is DAT_008ddf08. */
void rdRaster_SpanOutline16(int *param_1)
{
    int iVar2 = *(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4);
    unsigned short *puVar1 = (unsigned short *)
        (*(int *)(iVar2 + 0x5c) + (param_1[2] * (int)(*(unsigned int *)(iVar2 + 0x18) >> 1) + param_1[0]) * 2);

    *puVar1 = DAT_008ddf08;
    puVar1[param_1[1] - 1] = DAT_008ddf08;
}

/* ==== rdRaster_EdgeStepFlat (0x0040f750) ====
 * Advances an edge record one scanline: integer x (+0x28) += dx (+0x2c); float attribute +0x10 += +0x14. */
void rdRaster_EdgeStepFlat(int param_1)
{
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2c);
    *(float *)(param_1 + 0x10) = *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x10);
}

/* ==== rdRaster_Select_Flat_2 (0x0040fa20) ====
 * The same as rdRaster_Select_Flat with the texture span callback (rdRaster_SpanTexSetup) and the second edge
 * setup.  Constant of the division: 1.0 (Ghidra's read of the constant at rdata+0x738). */
void rdRaster_Select_Flat_2(float *param_1,int param_2)
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
    ((int *)param_1)[0x6d] = (int)rdRaster_SpanTexSetup;        /* +0x1b4 */
    ((int *)param_1)[0x74] = *(int *)(param_2 + 4);             /* +0x1d0 */
    ((int *)param_1)[0x7a] = (int)rdRaster_EdgeSetup_Flat_2;    /* +0x1e8 */
}

/* ==== rdRaster_SpanTexSetup (0x0040fa80) ====
 * Span callback of the texture selector: fills the spans with the flat colour (8 bpp: bytes, 16 bpp: words from
 * DAT_008ddf08), then sets UINT_008ddf24 and calls the per-span textured drawer of the camera's flag at +0x14. */
void rdRaster_SpanTexSetup(int *param_1)
{
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4) + 0x24);
    int node;
    int iVar1;
    unsigned int cnt;
    unsigned int i;

    if (bpp == 8) {
        DAT_008ddf40 = ((unsigned char *)param_1)[0x1d0];
    }
    else if (bpp == 0x10) {
        DAT_008ddf08 = *(unsigned short *)(*(int *)(*(int *)(*param_1 + 0x4c) + 0x348) + 0x7e00 +
                                           (unsigned int)((unsigned char *)param_1)[0x1d0] * 2);
    }
    UINT_008ddf24 = param_1[0x67];                              /* +0x19c */

    if (bpp == 8) {
        for (node = param_1[0x6e]; node != 0; node = *(int *)(node + 0x28)) {
            unsigned char *dst;
            iVar1 = *(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4);
            dst = (unsigned char *)(*(int *)(node + 8) * *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x5c) + *(int *)node);
            cnt = *(unsigned int *)(node + 4);
            for (i = 0; i < cnt; i++) {
                dst[i] = DAT_008ddf40;
            }
        }
    }
    else if (bpp == 0x10) {
        for (node = param_1[0x6e]; node != 0; node = *(int *)(node + 0x28)) {
            unsigned short *dst;
            iVar1 = *(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4);
            dst = (unsigned short *)(*(int *)(iVar1 + 0x5c) +
                                     (*(int *)(node + 8) * (int)(*(unsigned int *)(iVar1 + 0x18) >> 1) + *(int *)node) * 2);
            for (cnt = *(unsigned int *)(node + 4); cnt != 0; cnt--) {
                *dst = DAT_008ddf08;
                dst++;
            }
        }
    }

    node = param_1[0x6e];
    if (*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 0x14) == 0) {
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

/* ==== FUN_004169f0 (0x004169f0) ====
 * Edge step: x (+0x28) += dx (+0x2c), float +0x10 += +0x14, int +0x40 += +0x44, float +0x18 += +0x1c,
 * float +0x20 += +0x24. */
void FUN_004169f0(int param_1)
{
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2c);
    *(float *)(param_1 + 0x10) = *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x10);
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + *(int *)(param_1 + 0x44);
    *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x1c) + *(float *)(param_1 + 0x18);
    *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x20);
}

/* ==== FUN_00416a30 (0x00416a30) ====
 * Edge step: x (+0x28) += dx (+0x2c), int +0x40 += +0x44. */
void FUN_00416a30(int param_1)
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

/* ==== FUN_00411330 (0x00411330) ====
 * Copies the polygon's state (+0x1c0 .. +0x1d8, +0x19c, +0x1e0 for 16 bpp) into the rasteriser globals, then draws
 * every span of the list at +0x1b8 with the 8 / 16 bit "TexKey" span routine of the camera's bpp (+0x24). */
void FUN_00411330(int param_1)
{
    int iVar1;
    int iVar2;

    iVar1 = *(int *)(*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4) + 0x24);
    if (iVar1 == 0x10) {
        UINT_008ddf30 = *(unsigned int *)(param_1 + 0x1e0);
    }
    UINT_008ddf04 = *(unsigned int *)(param_1 + 0x1c0);
    UINT_008ddf3c = *(unsigned int *)(param_1 + 0x1c4);
    UINT_008ddf10 = *(unsigned int *)(param_1 + 0x1c8);
    _DAT_008ddf34 = *(undefined4 *)(param_1 + 0x1cc);
    UINT_008ddf4c = *(unsigned int *)(param_1 + 0x1d4);
    UINT_008ddf14 = *(unsigned int *)(param_1 + 0x1d8);
    UINT_008ddf24 = *(unsigned int *)(param_1 + 0x19c);
    for (iVar2 = *(int *)(param_1 + 0x1b8); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x28)) {
        if (iVar1 == 8) {
            rdRaster_SpanR8_TexKey((int *)iVar2);
        }
        else if (iVar1 == 0x10) {
            rdRaster_SpanR16_TexKey((int *)iVar2);
        }
    }
}

/* ==== rdRaster_SpanLitSetup (0x0040ff20) ====
 * Span callback of the lit selector: DAT_008ddf40 = colour byte (+0x1d0), UINT_008ddf24 = light step (+0x19c).  Every
 * span of the list at +0x1b8 is filled with the colour byte (whatever the bpp: bytes at the pixel address), then the
 * spans are drawn with the FlatZw routine chosen by the camera's flag at +0x14 (as rdRaster_SpanTexSetup). */
void rdRaster_SpanLitSetup(int param_1)
{
    int node;
    int iVar5;
    unsigned int cnt;
    unsigned int i;
    unsigned char *dst;

    DAT_008ddf40 = ((unsigned char *)param_1)[0x1d0];
    UINT_008ddf24 = *(unsigned int *)(param_1 + 0x19c);
    for (node = *(int *)(param_1 + 0x1b8); node != 0; node = *(int *)(node + 0x28)) {
        iVar5 = *(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4);
        cnt = *(unsigned int *)(node + 4);
        dst = (unsigned char *)(*(int *)(node + 8) * *(int *)(iVar5 + 0x18) + *(int *)(iVar5 + 0x5c) + *(int *)node);
        for (i = 0; i < cnt; i++) {
            dst[i] = DAT_008ddf40;
        }
    }

    node = *(int *)(param_1 + 0x1b8);
    if (*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 0x14) == 0) {
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

/* ==== rdRaster_Select_FlatLit (0x00410290) ====
 * Selector for flat lit polygons: builds the 1/w table as rdRaster_Select_Flat, copies the colour (+0x1d0), stores the
 * light / palette pointer for the camera's bpp (+0x1dc for 8 bpp from the record's +0x4c table +0x330, +0x1e0 for 16 bpp
 * from +0x348), then the span callback FUN_00410330 and the edge setup.  The raw dwords are copied as ints (they are
 * pointers or colour bits, not floats). */
void rdRaster_Select_FlatLit(float *param_1,int param_2)
{
    int rec = ((int *)param_1)[0];
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4) + 0x24);
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
    ((int *)param_1)[0x6d] = (int)FUN_00410330;                 /* +0x1b4 */
    ((int *)param_1)[0x7a] = (int)rdRaster_EdgeSetup_Flat_4;    /* +0x1e8 */
}

/* ==== rdRaster_Select_FlatLit_2 (0x004108b0) ====
 * Selector for the lit polygon with a 16 bit texture / palette: calls rdRaster_SetupPoly(param_1, count - 1), then
 * takes the table entry for the index in param_1[0x70] (the source's +0x1c table: +0x5c -> param_1[0x71], +0x18 ->
 * param_1[0x73]), the shifts and masks of the colour fields (+0x0c, +0x10, +0x14; shift counts masked to 5 bits as the
 * x86 shifts do) into param_1[0x72], [0x75], [0x76], and for 16 bpp the table address (+0x7e00) into param_1[0x78]. */
void rdRaster_Select_FlatLit_2(int *param_1,int param_2)
{
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4) + 0x24);
    int iVar2;

    rdRaster_SetupPoly((float *)param_1, *(int *)(*(int *)(param_2 + 0x1c) + 0x18) - 1);
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
    param_1[0x6d] = (int)FUN_00410970;
    param_1[0x7a] = (int)rdRaster_EdgeSetup_Flat_5;
}

/* ==== rdRaster_Select_FlatLit_3 (0x00411270) ====
 * The same selector as rdRaster_Select_FlatLit_2 with the span callback FUN_00411330 and the edge setup _5; 16 bpp
 * palette table at +0x7e00 into param_1[0x78]. */
void rdRaster_Select_FlatLit_3(int *param_1,int param_2)
{
    int iVar1 = *(int *)(*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4) + 0x24);
    int iVar2;

    rdRaster_SetupPoly((float *)param_1, *(int *)(*(int *)(param_2 + 0x1c) + 0x18) - 1);
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
    param_1[0x6d] = (int)FUN_00411330;
    param_1[0x7a] = (int)rdRaster_EdgeSetup_Flat_5;
}

/* Shared body of rdRaster_Select_FlatLit_6 and _7 (asm 0x004124f0 and 0x00413040, identical except for the span callback
 * and the edge setup): the 8 bpp palette word is at +0x330 of the material table, the 16 bpp one at +0x348 WITHOUT the
 * +0x7e00 offset that _2 / _3 add. */
static inline void select_flatlit_nooffset(int *param_1, int param_2, int span_fn_is_6)
{
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4) + 0x24);
    int iVar2;
    int rec;

    rdRaster_SetupPoly((float *)param_1, *(int *)(*(int *)(param_2 + 0x1c) + 0x18) - 1);
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
        param_1[0x6d] = (int)FUN_004125c0;
        param_1[0x7a] = (int)rdRaster_EdgeSetup_Flat_7;
    }
    else {
        param_1[0x6d] = (int)FUN_00413110;
        param_1[0x7a] = (int)rdRaster_EdgeSetup_Flat_7;
    }
}

/* ==== rdRaster_Select_FlatLit_6 (0x004124f0) ==== see select_flatlit_nooffset: span callback FUN_004125c0. */
void rdRaster_Select_FlatLit_6(int *param_1,int param_2)
{
    select_flatlit_nooffset(param_1, param_2, 1);
}

/* ==== rdRaster_Select_FlatLit_7 (0x00413040) ==== see select_flatlit_nooffset: span callback FUN_00413110. */
void rdRaster_Select_FlatLit_7(int *param_1,int param_2)
{
    select_flatlit_nooffset(param_1, param_2, 0);
}

/* ==== rdRaster_Span16_Flat (0x004195f0) ====
 * 16 bit flat span: x range from the 16.16 fixed-point ends (*param_1 and *param_2, each rounded up to a whole pixel),
 * a write cursor PTR_007f43a8 at (row param_1[0x10]) of the camera's buffer (+0x5c, pitch halved), and the colour word
 * DAT_008ddeb8 written for each pixel of the span.  Nothing is written for an empty span (the cursor is left alone). */
void rdRaster_Span16_Flat(uint *param_1,uint *param_2)
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
        iVar1 = *(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4);
        PTR_007f43a8 = (int *)(*(int *)(iVar1 + 0x5c) +
                              ((int)param_1[0x10] * (int)(*(unsigned int *)(iVar1 + 0x18) >> 1) + (int)(uVar2 >> 0x10)) * 2);
        do {
            *(unsigned short *)PTR_007f43a8 = DAT_008ddeb8;
            PTR_007f43a8 = (int *)((char *)PTR_007f43a8 + 2);
            iVar4 = iVar4 - 1;
        } while (iVar4 != 0);
    }
}

/* ==== rdRaster_Span16_Flat_2 (0x00419ee0) ====
 * Same body as rdRaster_Span16_Flat (the asm of both is the same instruction sequence). */
void rdRaster_Span16_Flat_2(uint *param_1,uint *param_2)
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
        iVar1 = *(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4);
        PTR_007f43a8 = (int *)(*(int *)(iVar1 + 0x5c) +
                              ((int)param_1[0x10] * (int)(*(unsigned int *)(iVar1 + 0x18) >> 1) + (int)(uVar2 >> 0x10)) * 2);
        do {
            *(unsigned short *)PTR_007f43a8 = DAT_008ddeb8;
            PTR_007f43a8 = (int *)((char *)PTR_007f43a8 + 2);
            iVar4 = iVar4 - 1;
        } while (iVar4 != 0);
    }
}

/* ==== rdRaster_Span_Flat (0x00419e60) ====
 * 8 bit flat span: the same x range as rdRaster_Span16_Flat; the pixels at row param_1[0x10] of the camera's buffer
 * (pitch not halved) are set to the colour byte DAT_008ddec0 (the original's rep stosd / rep stosb is a byte fill). */
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
        iVar1 = *(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4);
        dst = (unsigned char *)((int)param_1[0x10] * *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x5c) + (int)(uVar3 >> 0x10));
        for (i = 0; i < uVar4; i++) {
            dst[i] = DAT_008ddec0;
        }
    }
}

/* ==== FUN_004121a0 (0x004121a0) ====  span dispatcher of rdRaster_Select_FlatLit_5 ====
 * Copies the polygon record's fields (record offsets in the comments; p[n] is the dword at +4n) into the rasteriser globals:
 * +0x1c0 and +0x1c4 always; the 8 bpp path copies +0x1dc only, the 16 bpp path copies +0x1e0, +0x1c8, +0x1cc, +0x1d4,
 * +0x1d8, +0x1a0, +0x1a4 and +0x19c.  Then rdRaster_SpanR8_TexKey_2 / rdRaster_SpanR16_TexKey_2 is called for each span of the
 * list at +0x1b8 (linked by +0x28).  The copies are dword bit copies. */
void FUN_004121a0(int param_1)
{
    int *p = (int *)param_1;
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4) + 0x24);
    int node;

    UINT_008ddf04 = p[0x70];
    UINT_008ddf3c = p[0x71];
    if (bpp == 8) {
        UINT_008ddf0c = p[0x77];
    }
    else if (bpp == 0x10) {
        UINT_008ddf30 = p[0x78];
        UINT_008ddf10 = p[0x72];
        _DAT_008ddf34 = p[0x73];
        UINT_008ddf4c = p[0x75];
        UINT_008ddf14 = p[0x76];
        UINT_008ddf44 = p[0x68];
        UINT_008ddf18 = p[0x69];
        UINT_008ddf24 = p[0x67];
    }
    node = p[0x6e];
    if (node != 0) {
        do {
            if (bpp == 8) {
                rdRaster_SpanR8_TexKey_2((int *)node);
            }
            else if (bpp == 0x10) {
                rdRaster_SpanR16_TexKey_2((int *)node);
            }
            node = *(int *)(node + 0x28);
        } while (node != 0);
    }
}

/* ==== FUN_00413110 (0x00413110) ====  span dispatcher of rdRaster_Select_FlatLit_7 ====
 * Identical to FUN_004121a0 except for the span routines: rdRaster_SpanR8_TexKey_3 / rdRaster_SpanR16_TexKey_3. */
void FUN_00413110(int param_1)
{
    int *p = (int *)param_1;
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4) + 0x24);
    int node;

    UINT_008ddf04 = p[0x70];
    UINT_008ddf3c = p[0x71];
    if (bpp == 8) {
        UINT_008ddf0c = p[0x77];
    }
    else if (bpp == 0x10) {
        UINT_008ddf30 = p[0x78];
        UINT_008ddf10 = p[0x72];
        _DAT_008ddf34 = p[0x73];
        UINT_008ddf4c = p[0x75];
        UINT_008ddf14 = p[0x76];
        UINT_008ddf44 = p[0x68];
        UINT_008ddf18 = p[0x69];
        UINT_008ddf24 = p[0x67];
    }
    node = p[0x6e];
    if (node != 0) {
        do {
            if (bpp == 8) {
                rdRaster_SpanR8_TexKey_3((int *)node);
            }
            else if (bpp == 0x10) {
                rdRaster_SpanR16_TexKey_3((int *)node);
            }
            node = *(int *)(node + 0x28);
        } while (node != 0);
    }
}

/* ==== FUN_00415600 (0x00415600) ====  span dispatcher (its selector was not checked) ====
 * Copies +0x1c0 always; the 8 bpp path copies +0x1dc; the 16 bpp path copies +0x1e0, +0x1c4, +0x1c8, +0x1cc, +0x1d4,
 * +0x1d8, +0x1a8, +0x1ac, +0x1b0, +0x19c, +0x184, +0x18c, +0x194, +0x1a0, +0x1a4.  Calls rdRaster_SpanP8_TexKeyZw_2 /
 * rdRaster_SpanP16_TexKeyZw_2 for each span of the list at +0x1b8. */
void FUN_00415600(int param_1)
{
    int *p = (int *)param_1;
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4) + 0x24);
    int node;

    UINT_008ddf04 = p[0x70];
    if (bpp == 8) {
        UINT_008ddf0c = p[0x77];
    }
    else if (bpp == 0x10) {
        UINT_008ddf30 = p[0x78];
        UINT_008ddf3c = p[0x71];
        UINT_008ddf10 = p[0x72];
        _DAT_008ddf34 = p[0x73];
        UINT_008ddf4c = p[0x75];
        UINT_008ddf14 = p[0x76];
        _DAT_008ddf28 = p[0x6a];
        _DAT_008ddf2c = p[0x6b];
        _DAT_008ddf48 = p[0x6c];
        UINT_008ddf24 = p[0x67];
        _DAT_008ddf1c = p[0x61];
        _DAT_008ddf20 = p[0x63];
        _DAT_008ddf38 = p[0x65];
        UINT_008ddf44 = p[0x68];
        UINT_008ddf18 = p[0x69];
    }
    node = p[0x6e];
    if (node != 0) {
        do {
            if (bpp == 8) {
                rdRaster_SpanP8_TexKeyZw_2((unsigned int *)node);
            }
            else if (bpp == 0x10) {
                rdRaster_SpanP16_TexKeyZw_2((unsigned int *)node);
            }
            node = *(int *)(node + 0x28);
        } while (node != 0);
    }
}

/* ==== FUN_00416f80 (0x00416f80) ====  span dispatcher of rdRaster_Select_FlatLit_13 ====
 * The same copies as FUN_00415600; calls rdRaster_SpanP8_TexKeyZw_3 / rdRaster_SpanP16_TexKeyZw_3. */
void FUN_00416f80(int param_1)
{
    int *p = (int *)param_1;
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4) + 0x24);
    int node;

    UINT_008ddf04 = p[0x70];
    if (bpp == 8) {
        UINT_008ddf0c = p[0x77];
    }
    else if (bpp == 0x10) {
        UINT_008ddf30 = p[0x78];
        UINT_008ddf3c = p[0x71];
        UINT_008ddf10 = p[0x72];
        _DAT_008ddf34 = p[0x73];
        UINT_008ddf4c = p[0x75];
        UINT_008ddf14 = p[0x76];
        _DAT_008ddf28 = p[0x6a];
        _DAT_008ddf2c = p[0x6b];
        _DAT_008ddf48 = p[0x6c];
        UINT_008ddf24 = p[0x67];
        _DAT_008ddf1c = p[0x61];
        _DAT_008ddf20 = p[0x63];
        _DAT_008ddf38 = p[0x65];
        UINT_008ddf44 = p[0x68];
        UINT_008ddf18 = p[0x69];
    }
    node = p[0x6e];
    if (node != 0) {
        do {
            if (bpp == 8) {
                rdRaster_SpanP8_TexKeyZw_3((unsigned int *)node);
            }
            else if (bpp == 0x10) {
                rdRaster_SpanP16_TexKeyZw_3((unsigned int *)node);
            }
            node = *(int *)(node + 0x28);
        } while (node != 0);
    }
}

/* ==== FUN_00413dd0 (0x00413dd0) ====  span dispatcher of rdRaster_Select_FlatLit_9 ====
 * Copies only for 16 bpp (the 8 bpp path copies nothing): +0x1e0, +0x1c0, +0x1c4, +0x1c8, +0x1cc, +0x1d4, +0x1d8, +0x1a8,
 * +0x1ac, +0x1b0, +0x19c, +0x184, +0x18c, +0x194, +0x1a0, +0x1a4.  Calls rdRaster_SpanP8_TexKeyZw / rdRaster_SpanP16_TexKeyZw
 * for each span of the list at +0x1b8. */
void FUN_00413dd0(int param_1)
{
    int *p = (int *)param_1;
    int bpp = *(int *)(*(int *)(*(int *)((char *)g_pRdCurrentCamera + 4) + 4) + 0x24);
    int node;

    if (bpp == 0x10) {
        UINT_008ddf30 = p[0x78];
        UINT_008ddf04 = p[0x70];
        UINT_008ddf3c = p[0x71];
        UINT_008ddf10 = p[0x72];
        _DAT_008ddf34 = p[0x73];
        UINT_008ddf4c = p[0x75];
        UINT_008ddf14 = p[0x76];
        _DAT_008ddf28 = p[0x6a];
        _DAT_008ddf2c = p[0x6b];
        _DAT_008ddf48 = p[0x6c];
        UINT_008ddf24 = p[0x67];
        _DAT_008ddf1c = p[0x61];
        _DAT_008ddf20 = p[0x63];
        _DAT_008ddf38 = p[0x65];
        UINT_008ddf44 = p[0x68];
        UINT_008ddf18 = p[0x69];
    }
    node = p[0x6e];
    if (node != 0) {
        do {
            if (bpp == 8) {
                rdRaster_SpanP8_TexKeyZw((unsigned int *)node);
            }
            else if (bpp == 0x10) {
                rdRaster_SpanP16_TexKeyZw((unsigned int *)node);
            }
            node = *(int *)(node + 0x28);
        } while (node != 0);
    }
}

#endif /* GRIM_EXE */
