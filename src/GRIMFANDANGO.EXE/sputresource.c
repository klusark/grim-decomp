/* GRIMFANDANGO.EXE :: sputresource.c
 * functions 0x0048d4e0 .. 0x0048d830 (4 functions)
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
  param_2[1] = sputResource_Terminate;
  param_2[2] = sputResource_Start;
  param_2[3] = sputResource_Stop;
  puVar1 = (undefined *)Res_SysInitialize(param_1,&DAT_008ca1d8);
  if (puVar1 == (undefined *)0x0) {
    _DAT_008ca1f8 = 1;
    param_2[4] = (undefined *)UINT_008ca1e8;
    param_2[5] = (undefined *)UINT_008ca1ec;
    param_2[6] = (undefined *)UINT_008ca1f0;
    param_2[7] = (undefined *)UINT_008ca1f4;
  }
  return puVar1;
}

/* ---- 0x0048d770  sputResource_Terminate ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Module interface slot 1 (sputResource): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. */

void sputResource_Terminate(void)

{
  (*(code *)UINT_008ca1dc)();
  UINT_008ca1d0 = 0;
  _DAT_008ca1f8 = 0;
  return;
}

/* ---- 0x0048d790  sputResource_Start ---- */
/* Module interface slot 2 (sputResource): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start installs the ResFile services and registers
   the resource types. */

int sputResource_Start(void)

{
  int iVar1;
  
  if (UINT_008ca1fc != 0) {
    return true;
  }
  iVar1 = (*(code *)UINT_008ca1e0)();
  if (iVar1 == 0) {
    UINT_008ca1fc = Resource_RegisterTypes();
  }
  Res_InstallFileServices((GrimServices *)UINT_008ca1d0);
  UINT_008ca200 = rdMaterial_SetLoadHook(Resource_MaterialLoadHook);
  UINT_008ca204 = rdMaterial_SetFreeHook(Resource_MaterialFreeHook);
  UINT_008a85e8 = (uint)SoundsPeriodic;
  Cos_RegisterSaveVerify(((unsigned)(uintptr_t)Resource_CountCostumeRefs));
  return UINT_008ca1fc == 0;
}

/* ---- 0x0048d830  sputResource_Stop ---- */
/* Module interface slot 3 (sputResource): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. */

void sputResource_Stop(void)

{
  (*(code *)UINT_008ca1e4)();
  rdMaterial_SetLoadHook(UINT_008ca200);
  rdMaterial_SetFreeHook(UINT_008ca204);
  Res_RestoreFileServices((GrimServices *)UINT_008ca1d0);
  UINT_008ca1fc = 0;
  return;
}
