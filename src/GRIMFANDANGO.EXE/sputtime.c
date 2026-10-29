/* GRIMFANDANGO.EXE :: sputtime.c
 * functions 0x004a3d00 .. 0x004a3da0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a3d00  sputTime_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputTime_Initialize(undefined4 param_1,undefined4 *param_2)

{
  _DAT_008cab94 = param_1;
  *param_2 = sputTime_Initialize;
  param_2[1] = FUN_004a3d50;
  param_2[2] = FUN_004a3d70;
  param_2[3] = FUN_004a3da0;
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  DAT_008cab98 = 1;
  return 0;
}

/* ---- 0x004a3d50  FUN_004a3d50 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004a3d50(void)

{
  _DAT_008cab94 = 0;
  if (DAT_008cab98 != 0) {
    DAT_008cab98 = 0;
  }
  return;
}

/* ---- 0x004a3d70  FUN_004a3d70 ---- */
undefined4 FUN_004a3d70(void)

{
  if (DAT_008cab9c != 0) {
    return 1;
  }
  DAT_008cab9c = 1;
  Timer_Reset();
  return 0;
}

/* ---- 0x004a3da0  FUN_004a3da0 ---- */
void FUN_004a3da0(void)

{
  DAT_008cab9c = 0;
  return;
}
