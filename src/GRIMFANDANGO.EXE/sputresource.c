/* GRIMFANDANGO.EXE :: sputresource.c
 * functions 0x0048d4e0 .. 0x0048d4e0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048d4e0  sputResource_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

int __cdecl sputResource_Initialize(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  
  DAT_008ca1d0 = param_1;
  *param_2 = sputResource_Initialize;
  param_2[1] = FUN_0048d770;
  param_2[2] = FUN_0048d790;
  param_2[3] = FUN_0048d830;
  iVar1 = Resource_RegisterFilioModule(param_1,&DAT_008ca1d8);
  if (iVar1 == 0) {
    _DAT_008ca1f8 = 1;
    param_2[4] = DAT_008ca1e8;
    param_2[5] = DAT_008ca1ec;
    param_2[6] = DAT_008ca1f0;
    param_2[7] = DAT_008ca1f4;
  }
  return iVar1;
}
