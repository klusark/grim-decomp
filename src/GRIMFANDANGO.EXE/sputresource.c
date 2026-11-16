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

undefined * __cdecl sputResource_Initialize(uint services,undefined **iface)

{
  undefined *puVar1;
  
  g_dwSputResHS = services;
  *iface = sputResource_Initialize;
  iface[1] = sputResource_Terminate;
  iface[2] = sputResource_Startup;
  iface[3] = sputResource_Shutdown;
  puVar1 = (undefined *)Res_SysInitialize(services,(undefined4 *)&g_aResModServices);
  if (puVar1 == (undefined *)0x0) {
    _DAT_008ca1f8 = 1;
    iface[4] = (undefined *)UINT_008ca1e8;
    iface[5] = (undefined *)UINT_008ca1ec;
    iface[6] = (undefined *)UINT_008ca1f0;
    iface[7] = (undefined *)UINT_008ca1f4;
  }
  return puVar1;
}

/* ---- 0x0048d770  sputResource_Terminate ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Module interface slot 1 (sputResource): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. */

void __cdecl sputResource_Terminate(void)

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

int __cdecl sputResource_Startup(void)

{
  int iVar1;
  
  if (g_dwSputResStartup != 0) {
    return 1;
  }
  iVar1 = (*(code *)UINT_008ca1e0)();
  if (iVar1 == 0) {
    g_dwSputResStartup = Resource_RegisterTypes();
  }
  Res_OverrideFileCalls((GrimServices *)g_dwSputResHS);
  g_dwPrdMatLoader = rdMaterial_RegisterLoader(((unsigned)(uintptr_t)sputResource_MatLoader));
  g_dwPrdMatUnloader = rdMaterial_RegisterUnloader(((unsigned)(uintptr_t)sputResource_MatUnloader));
  g_dwRes_pPeriodicCallback = (uint)SoundsPeriodic;
  Cos_RegisterSaveVerify(((unsigned)(uintptr_t)Resource_CountCostumeRefs));
  return (uint)(g_dwSputResStartup == 0);
}

/* ---- 0x0048d830  sputResource_Shutdown ---- */
/* Module interface slot 3 (sputResource): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputResource_Shutdown (the remaster's GrimFandango
   (Linux): aligned call in sputResource_Initialize); was sputResource_Stop. */

void __cdecl sputResource_Shutdown(void)

{
  (*(code *)UINT_008ca1e4)();
  rdMaterial_RegisterLoader(g_dwPrdMatLoader);
  rdMaterial_RegisterUnloader(g_dwPrdMatUnloader);
  Res_RestoreFileCalls((GrimServices *)g_dwSputResHS);
  g_dwSputResStartup = 0;
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_008ca1f8[4] __asm__("_DAT_008ca1f8");
extern unsigned int grim_def_UINT_008ca1dc __asm__("_UINT_008ca1dc");
extern unsigned int grim_def_UINT_008ca1e0 __asm__("_UINT_008ca1e0");
extern unsigned int grim_def_UINT_008ca1e4 __asm__("_UINT_008ca1e4");
extern unsigned int grim_def_UINT_008ca1e8 __asm__("_UINT_008ca1e8");
extern unsigned int grim_def_UINT_008ca1ec __asm__("_UINT_008ca1ec");
extern unsigned int grim_def_UINT_008ca1f0 __asm__("_UINT_008ca1f0");
extern unsigned int grim_def_UINT_008ca1f4 __asm__("_UINT_008ca1f4");
extern unsigned char grim_def_g_aResModServices[4] __asm__("_g_aResModServices");
extern unsigned int grim_def_g_dwPrdMatLoader __asm__("_g_dwPrdMatLoader");
extern unsigned int grim_def_g_dwPrdMatUnloader __asm__("_g_dwPrdMatUnloader");
extern unsigned int grim_def_g_dwSputResStartup __asm__("_g_dwSputResStartup");
/* 0x008ca1d8, 4 bytes */ GRIM_DATA("008ca1d8") unsigned char grim_def_g_aResModServices[4] __asm__("_g_aResModServices") = {0};
/* 0x008ca1dc, 4 bytes */ GRIM_DATA("008ca1dc") unsigned int grim_def_UINT_008ca1dc __asm__("_UINT_008ca1dc") = 0x0;
/* 0x008ca1e0, 4 bytes */ GRIM_DATA("008ca1e0") unsigned int grim_def_UINT_008ca1e0 __asm__("_UINT_008ca1e0") = 0x0;
/* 0x008ca1e4, 4 bytes */ GRIM_DATA("008ca1e4") unsigned int grim_def_UINT_008ca1e4 __asm__("_UINT_008ca1e4") = 0x0;
/* 0x008ca1e8, 4 bytes */ GRIM_DATA("008ca1e8") unsigned int grim_def_UINT_008ca1e8 __asm__("_UINT_008ca1e8") = 0x0;
/* 0x008ca1ec, 4 bytes */ GRIM_DATA("008ca1ec") unsigned int grim_def_UINT_008ca1ec __asm__("_UINT_008ca1ec") = 0x0;
/* 0x008ca1f0, 4 bytes */ GRIM_DATA("008ca1f0") unsigned int grim_def_UINT_008ca1f0 __asm__("_UINT_008ca1f0") = 0x0;
/* 0x008ca1f4, 4 bytes */ GRIM_DATA("008ca1f4") unsigned int grim_def_UINT_008ca1f4 __asm__("_UINT_008ca1f4") = 0x0;
/* 0x008ca1f8, 4 bytes */ GRIM_DATA("008ca1f8") unsigned char grim_def_DAT_008ca1f8[4] __asm__("_DAT_008ca1f8") = {0};
/* 0x008ca1fc, 4 bytes */ GRIM_DATA("008ca1fc") unsigned int grim_def_g_dwSputResStartup __asm__("_g_dwSputResStartup") = 0x0;
/* 0x008ca200, 4 bytes */ GRIM_DATA("008ca200") unsigned int grim_def_g_dwPrdMatLoader __asm__("_g_dwPrdMatLoader") = 0x0;
/* 0x008ca204, 4 bytes */ GRIM_DATA("008ca204") unsigned int grim_def_g_dwPrdMatUnloader __asm__("_g_dwPrdMatUnloader") = 0x0;
