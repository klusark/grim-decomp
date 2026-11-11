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
  
  g_dwSputResHS = param_1;
  *param_2 = sputResource_Initialize;
  param_2[1] = sputResource_Terminate;
  param_2[2] = sputResource_Startup;
  param_2[3] = sputResource_Shutdown;
  puVar1 = (undefined *)Res_SysInitialize(param_1,&g_aResModServices);
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
  g_dwSputResHS = 0;
  _DAT_008ca1f8 = 0;
  return;
}

/* ---- 0x0048d790  sputResource_Startup ---- */
/* Module interface slot 2 (sputResource): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start installs the ResFile services and registers
   the resource types. Original name sputResource_Startup (the remaster's GrimFandango (Linux):
   aligned call in sputResource_Initialize); was sputResource_Start. */

int sputResource_Startup(void)

{
  int iVar1;
  
  if (g_dwSputResStartup != 0) {
    return true;
  }
  iVar1 = (*(code *)UINT_008ca1e0)();
  if (iVar1 == 0) {
    g_dwSputResStartup = Resource_RegisterTypes();
  }
  Res_OverrideFileCalls((GrimServices *)g_dwSputResHS);
  g_dwPrdMatLoader = rdMaterial_RegisterLoader(sputResource_MatLoader);
  g_dwPrdMatUnloader = rdMaterial_RegisterUnloader(sputResource_MatUnloader);
  g_dwRes_pPeriodicCallback = (uint)SoundsPeriodic;
  Cos_RegisterSaveVerify(((unsigned)(uintptr_t)Resource_CountCostumeRefs));
  return g_dwSputResStartup == 0;
}

/* ---- 0x0048d830  sputResource_Shutdown ---- */
/* Module interface slot 3 (sputResource): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputResource_Shutdown (the remaster's GrimFandango
   (Linux): aligned call in sputResource_Initialize); was sputResource_Stop. */

void sputResource_Shutdown(void)

{
  (*(code *)UINT_008ca1e4)();
  rdMaterial_RegisterLoader(g_dwPrdMatLoader);
  rdMaterial_RegisterUnloader(g_dwPrdMatUnloader);
  Res_RestoreFileCalls((GrimServices *)g_dwSputResHS);
  g_dwSputResStartup = 0;
  return;
}
