/* GRIMFANDANGO.EXE :: renderer.c
 * functions 0x0040a870 .. 0x0040a880 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0040a870  rdModel3_ActivateClipPlane ---- */
/* Original name rdModel3_ActivateClipPlane (the remaster's GrimFandango (Linux): aligned call in
   sputCostume_InternalDraw3D); was Renderer_EnableClipPlane. */

void __cdecl rdModel3_ActivateClipPlane(uint active)

{
  g_dwClipPlaneActive = active;
  return;
}

/* ---- 0x0040a880  rdModel3_SetClipPlane ---- */
/* Original name rdModel3_SetClipPlane (the remaster's GrimFandango (Linux): aligned call in
   sputCostume_InternalDraw3D); was Renderer_SetClipPlane. */

void __cdecl rdModel3_SetClipPlane(undefined4 *normal,undefined4 *point)

{
  FLOAT_004ddb70 = PUN(float,*normal);
  FLOAT_004ddb74 = PUN(float,normal[1]);
  FLOAT_004ddb78 = PUN(float,normal[2]);
  FLOAT_007f3208 = PUN(float,*point);
  FLOAT_007f320c = PUN(float,point[1]);
  FLOAT_007f3210 = PUN(float,point[2]);
  return;
}
