/* GRIMFANDANGO.EXE :: sputsmush.c
 * functions 0x00488fb0 .. 0x00488fb0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00488fb0  sputSmush_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputSmush_Initialize(undefined4 param_1,undefined4 *param_2)

{
  _DAT_008c9ca8 = param_1;
  *param_2 = sputSmush_Initialize;
  param_2[1] = &DAT_004891a0;
  param_2[2] = FUN_00489130;
  param_2[3] = FUN_00489190;
  param_2[4] = Movie_SaveState;
  param_2[5] = FUN_00489090;
  param_2[6] = 0;
  param_2[7] = 0;
  Insane_RegisterFilio(param_1,&DAT_008c9fb8);
  Insane_SetOutputParams(&PTR_FUN_004e8338);
  g_pMovieSurface = (void *)0x0;
  _DAT_008ca080 = 1;
  return 0;
}
