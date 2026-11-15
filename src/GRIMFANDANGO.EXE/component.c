/* GRIMFANDANGO.EXE :: component.c
 * functions 0x00496060 .. 0x00496060 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00496060  BitmapChanger ---- */
/* Original name BitmapChanger (the remaster's GrimFandango (Linux): the same handler slot (changer)
   of the same costume tag registration in sputCostume_Startup); was Component_SetBitmapFrame. */

void __cdecl BitmapChanger(uint cosInst,int *inst,uint tag,int frame)

{
  if (*inst == 0) {
    (*g_pStd_HS->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
  }
  *(int *)(inst[1] + 0x68) = frame + -1;
  return;
}
