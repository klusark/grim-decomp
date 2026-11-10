/* GRIMFANDANGO.EXE :: renderer.c
 * functions 0x0040a870 .. 0x0040a880 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0040a870  rdModel3_ActivateClipPlane ---- */
/* Original name rdModel3_ActivateClipPlane (the remaster's GrimFandango (Linux): aligned call in
   sputCostume_InternalDraw3D); was Renderer_EnableClipPlane. */

void rdModel3_ActivateClipPlane(uint param_1)

{
  g_dwClipPlaneActive = param_1;
  return;
}

/* ---- 0x0040a880  rdModel3_SetClipPlane ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name rdModel3_SetClipPlane (the remaster's GrimFandango (Linux): aligned call in
   sputCostume_InternalDraw3D); was Renderer_SetClipPlane. */

void rdModel3_SetClipPlane(undefined4 *param_1,undefined4 *param_2)

{
  _DAT_004ddb70 = *param_1;
  _DAT_004ddb74 = param_1[1];
  _DAT_004ddb78 = param_1[2];
  _DAT_007f3208 = *param_2;
  _DAT_007f320c = param_2[1];
  _DAT_007f3210 = param_2[2];
  return;
}
