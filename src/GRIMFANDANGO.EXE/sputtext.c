/* GRIMFANDANGO.EXE :: sputtext.c
 * functions 0x0048acc0 .. 0x0048acc0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048acc0  sputText_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputText_Initialize(GrimServices *param_1,undefined4 *param_2)

{
  int iVar1;
  
  _DAT_008ca144 = param_1;
  *param_2 = sputText_Initialize;
  param_2[1] = FUN_0048c4d0;
  param_2[2] = FUN_0048c500;
  param_2[3] = FUN_0048c6f0;
  param_2[4] = FUN_0048cbc0;
  param_2[5] = FUN_0048cd80;
  param_2[6] = 0;
  param_2[7] = 0;
  iVar1 = PlatModule_Init(param_1,&DAT_008ca118);
  if (iVar1 == 0) {
    iVar1 = TextModule_Init(param_1,&DAT_008ca0b8);
    if (iVar1 == 0) {
      DAT_008ca138 = 1;
      return 0;
    }
  }
  return 1;
}
