/* GRIMFANDANGO.EXE :: sputrender.c
 * functions 0x00483d40 .. 0x00483d40 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00483d40  sputRender_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputRender_Initialize(GrimServices *param_1,undefined4 *param_2)

{
  g_pSvcRender = param_1;
  *param_2 = sputRender_Initialize;
  param_2[1] = FUN_00486050;
  param_2[2] = FUN_00486070;
  param_2[3] = FUN_004860d0;
  param_2[4] = Render_SaveState;
  param_2[5] = Render_RestoreState;
  param_2[6] = 0;
  param_2[7] = 0;
  Engine_RegisterShutdownHook(FUN_00484a50);
  UINT_008c9788 = 1;
  return 0;
}
