/* GRIMFANDANGO.EXE :: sputcontrol.c
 * functions 0x0048d100 .. 0x0048d100 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048d100  sputControl_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputControl_Initialize(undefined4 param_1,undefined4 *param_2)

{
  if (DAT_008ca1bc == 0) {
    _DAT_008ca1b8 = param_1;
    *param_2 = sputControl_Initialize;
    param_2[1] = FUN_0048d2c0;
    param_2[2] = FUN_0048d2e0;
    param_2[3] = FUN_0048d330;
    param_2[4] = 0;
    param_2[5] = 0;
    param_2[6] = 0;
    param_2[7] = 0;
    DAT_008ca1bc = 1;
  }
  return 0;
}
