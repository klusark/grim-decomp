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

/* (DAT_00900524 / DAT_00900526, globals.h: the x87 control words default and round down, Services_SetCurrent) */
static int s3_floor_i(float x)
{
    int r;
    __asm__ volatile("fldcw %2\n\tflds %1\n\tfistpl %0\n\tfldcw %3"
                     : "=m"(r) : "m"(x), "m"(DAT_00900526), "m"(DAT_00900524) : "memory");
    return r;
}

/* ==== rdZRaster_DrawNGonLV (0x0042dba0) ====
 * Draws a list of points into the current camera's target (no depth test).  param_1 is the point list record:
 * the pointer to the points at +0x20 (12 bytes each: x float, y float, z float) and the count at +0x1c.  param_2 + 4
 * holds the colour: a byte for an 8 bit target (g_bRdZRaster_color) or a 16 bit pixel from the palette table of the
 * material at param_1 + 0x4c (`*(...+0x348) + 0x7e00 + index * 2`, g_wRdZRaster_RGBcolor).  The target is the camera's
 * surface at +0x5c with a row pitch at +0x18 (bytes for 8 bit, pixels for 16 bit: `pitch >> 1` there, unsigned).
 * Each point is rounded down (y, then x: `fldcw [round down]; fld m32; fistp m32; fldcw [default]`, as its no-z twin
 * rdNRaster_DrawNGonLV, build/overrides_asm_q6.c) and written if the target depth is 8 or 16 bpp (camera surface +0x24
 * of the surface at camera + 4 + 4).  The colour is written for each point in the order of the list; other depths
 * write nothing.  (Ghidra prints the FISTP as ROUND() and drops the FLDCW around it: this port first rounded to the
 * nearest integer, and a point at x.5 or more landed one pixel right or down of the original's, clean room render_g1.) */
void rdZRaster_DrawNGonLV(int param_1, int param_2)
{
    int *cam;          /* *(g_pRdCamera_CurCamera + 4) + 4 : the surface record */
    int bpp;           /* surface depth at +0x24 */
    int i;
    float *pt;

    g_pRdZRaster_aVertices = *(int **)(param_1 + 0x20);
    cam = *(int **)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 4);
    bpp = *(int *)((int)cam + 0x24);
    g_dwRdZRaster_numVertices = *(uint *)(param_1 + 0x1c);

    if (bpp == 8) {
        g_bRdZRaster_color = *(uint8_t *)(param_2 + 4);
        for (i = 0; i < (int)g_dwRdZRaster_numVertices; i++) {
            pt = (float *)((char *)g_pRdZRaster_aVertices + i * 12);
            int y = s3_floor_i(pt[1]), x = s3_floor_i(pt[0]);
            *(uint8_t *)((uintptr_t)(*(int *)((int)cam + 0x18) * y + *(int *)((int)cam + 0x5c) + x)) = g_bRdZRaster_color;
        }
    }
    else if (bpp == 16) {
        g_wRdZRaster_RGBcolor = *(uint16_t *)(uintptr_t)(*(int *)(*(int *)(param_1 + 0x4c) + 0x348) + 0x7e00 +
                                                (uint)*(uint8_t *)(param_2 + 4) * 2);
        for (i = 0; i < (int)g_dwRdZRaster_numVertices; i++) {
            pt = (float *)((char *)g_pRdZRaster_aVertices + i * 12);
            int y = s3_floor_i(pt[1]), x = s3_floor_i(pt[0]);
            *(uint16_t *)(uintptr_t)(*(int *)((int)cam + 0x5c) +
                                     ((*(uint *)((int)cam + 0x18) >> 1) * y + x) * 2) = g_wRdZRaster_RGBcolor;
        }
    }
}

#endif /* GRIM_EXE */
