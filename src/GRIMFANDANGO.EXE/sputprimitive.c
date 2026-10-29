/* GRIMFANDANGO.EXE :: sputprimitive.c
 * functions 0x00489580 .. 0x00489580 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00489580  sputPrimitive_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputPrimitive_Initialize(undefined4 param_1,undefined4 *param_2)

{
  _DAT_008ca0b0 = param_1;
  *param_2 = sputPrimitive_Initialize;
  param_2[1] = FUN_004897d0;
  param_2[2] = FUN_004897f0;
  param_2[3] = FUN_00489820;
  param_2[4] = FUN_00489600;
  param_2[5] = FUN_004896b0;
  param_2[6] = 0;
  param_2[7] = 0;
  UINT_008ca0a8 = 1;
  return 0;
}
