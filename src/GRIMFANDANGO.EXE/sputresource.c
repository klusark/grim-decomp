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

undefined * __cdecl sputResource_Initialize(uint param_1,undefined **param_2)

{
  undefined *puVar1;
  
  UINT_008ca1d0 = param_1;
  *param_2 = sputResource_Initialize;
  param_2[1] = FUN_0048d770;
  param_2[2] = FUN_0048d790;
  param_2[3] = FUN_0048d830;
  puVar1 = (undefined *)Resource_RegisterFilioModule(param_1,&DAT_008ca1d8);
  if (puVar1 == (undefined *)0x0) {
    _DAT_008ca1f8 = 1;
    param_2[4] = (undefined *)UINT_008ca1e8;
    param_2[5] = (undefined *)UINT_008ca1ec;
    param_2[6] = (undefined *)UINT_008ca1f0;
    param_2[7] = (undefined *)UINT_008ca1f4;
  }
  return puVar1;
}
