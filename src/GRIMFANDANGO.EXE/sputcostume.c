/* GRIMFANDANGO.EXE :: sputcostume.c
 * functions 0x004957f0 .. 0x004957f0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004957f0  sputCostume_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

bool sputCostume_Initialize(GrimServices *param_1,undefined4 *param_2)

{
  int iVar1;
  
  g_pSvcCostume = param_1;
  *param_2 = sputCostume_Initialize;
  param_2[1] = FUN_00495960;
  param_2[2] = FUN_004959a0;
  param_2[3] = FUN_004988a0;
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  iVar1 = Cos_Initialize(param_1,&DAT_008ca770);
  DAT_008ca798 = (uint)(iVar1 == 0);
  return iVar1 != 0;
}
