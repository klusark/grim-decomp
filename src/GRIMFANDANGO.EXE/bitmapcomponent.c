/* GRIMFANDANGO.EXE :: bitmapcomponent.c
 * functions 0x004980b0 .. 0x004980b0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004980b0  BitmapComponent_Destroy ---- */
undefined4 BitmapComponent_Destroy(undefined4 param_1,undefined4 param_2,void *param_3)

{
  ResRef_Remove(param_3);
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}
