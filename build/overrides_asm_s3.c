/* Readable C for software-rasteriser functions of GRIMFANDANGO.EXE (slice 3, 0x0042b8e0 - 0x0043c130).
 *
 * Each function below replaces the assembled original at the address given in its comment.  The C was written
 * against the 1.01 machine code (src/GRIMFANDANGO.EXE/asm_funcs.s); the decompiled text is kept under `#if 0` by
 * tools/build_src.py.  Names and types are Ghidra's; struct offsets are the raw byte offsets used by the code.
 * Notes and the list of functions still assembled: docs/notes/asm_s3.md.
 */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

/* ==== rdRaster_DrawPointsZ (0x0042dba0) ====
 * Draws a list of points into the current camera's target (no depth test).  param_1 is the point list record:
 * the pointer to the points at +0x20 (12 bytes each: x float, y float, z float) and the count at +0x1c.  param_2 + 4
 * holds the colour: a byte for an 8 bit target (DAT_008dde98) or a 16 bit pixel from the palette table of the
 * material at param_1 + 0x4c (`*(...+0x348) + 0x7e00 + index * 2`, DAT_008dde70).  The target is the camera's
 * surface at +0x5c with a row pitch at +0x18 (bytes for 8 bit, pixels for 16 bit: `pitch >> 1` there, unsigned).
 * Each point is rounded to the nearest integer (ROUND = FRNDINT, round half to even) and written if the target depth
 * is 8 or 16 bpp (camera surface +0x24 of the surface at camera + 4 + 4).  The colour is written for each point
 * in the order of the list; other depths write nothing. */
void rdRaster_DrawPointsZ(int param_1, int param_2)
{
    int *cam;          /* *(g_pRdCamera_CurCamera + 4) + 4 : the surface record */
    int bpp;           /* surface depth at +0x24 */
    int i;
    float *pt;

    PTR_007f44fc = *(int **)(param_1 + 0x20);
    cam = *(int **)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 4);
    bpp = *(int *)((int)cam + 0x24);
    UINT_007f4460 = *(uint *)(param_1 + 0x1c);

    if (bpp == 8) {
        DAT_008dde98 = *(uint8_t *)(param_2 + 4);
        for (i = 0; i < (int)UINT_007f4460; i++) {
            pt = (float *)((char *)PTR_007f44fc + i * 12);
            *(uint8_t *)((uintptr_t)(*(int *)((int)cam + 0x18) * (int)ROUND(pt[1]) +
                                     *(int *)((int)cam + 0x5c) + (int)ROUND(pt[0]))) = DAT_008dde98;
        }
    }
    else if (bpp == 16) {
        DAT_008dde70 = *(uint16_t *)(uintptr_t)(*(int *)(*(int *)(param_1 + 0x4c) + 0x348) + 0x7e00 +
                                                (uint)*(uint8_t *)(param_2 + 4) * 2);
        for (i = 0; i < (int)UINT_007f4460; i++) {
            pt = (float *)((char *)PTR_007f44fc + i * 12);
            *(uint16_t *)(uintptr_t)(*(int *)((int)cam + 0x5c) +
                                     ((*(uint *)((int)cam + 0x18) >> 1) * (int)ROUND(pt[1]) +
                                      (int)ROUND(pt[0])) * 2) = DAT_008dde70;
        }
    }
}

#endif /* GRIM_EXE */
