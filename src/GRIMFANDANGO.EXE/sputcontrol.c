/* GRIMFANDANGO.EXE :: sputcontrol.c
 * functions 0x0048d100 .. 0x0048d330 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048d100  sputControl_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

uint __cdecl sputControl_Initialize(uint services,undefined4 *iface)

{
  if (g_dwSputConInitialize == 0) {
    _g_pSputConHS = services;
    *iface = sputControl_Initialize;
    iface[1] = sputControl_Terminate;
    iface[2] = sputControl_Startup;
    iface[3] = sputControl_Shutdown;
    iface[4] = 0;
    iface[5] = 0;
    iface[6] = 0;
    iface[7] = 0;
    g_dwSputConInitialize = 1;
  }
  return 0;
}

/* ---- 0x0048d2c0  sputControl_Terminate ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Module interface slot 1 (sputControl): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. */

void __cdecl sputControl_Terminate(void)

{
  _g_pSputConHS = 0;
  if (g_dwSputConInitialize != 0) {
    g_dwSputConInitialize = 0;
  }
  return;
}

/* ---- 0x0048d2e0  sputControl_Startup ---- */
/* Module interface slot 2 (sputControl): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start initialises input and resets all controls.
   Original name sputControl_Startup (the remaster's GrimFandango (Linux): aligned call in
   sputControl_Initialize); was sputControl_Start. */

uint __cdecl sputControl_Startup(void)

{
  undefined *puVar1;
  
  if (g_dwSputConStartup != 0) {
    return 1;
  }
  if (g_dwStdControl_bStartup == 0) {
    puVar1 = stdControl_Startup();
    if (puVar1 == (undefined *)0x0) {
      return 1;
    }
  }
  sputControl_Reset();
  sputControl_AddCallback(Controls_DebugKeysHook);
  g_dwSputConStartup = 1;
  return 0;
}

/* ---- 0x0048d330  sputControl_Shutdown ---- */
/* Module interface slot 3 (sputControl): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputControl_Shutdown (the remaster's GrimFandango
   (Linux): aligned call in sputControl_Initialize); was sputControl_Stop. */

void __cdecl sputControl_Shutdown(void)

{
  stdControl_Shutdown();
  g_dwSputConStartup = 0;
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned int grim_def_g_dwSputConInitialize __asm__("_g_dwSputConInitialize");
extern unsigned int grim_def_g_dwSputConStartup __asm__("_g_dwSputConStartup");
extern unsigned char grim_def_g_pSputConHS[4] __asm__("_g_pSputConHS");
/* 0x008ca1b8, 4 bytes */ /* loose */ unsigned char grim_def_g_pSputConHS[4] __asm__("_g_pSputConHS") = {0};
/* 0x008ca1bc, 4 bytes */ /* loose */ unsigned int grim_def_g_dwSputConInitialize __asm__("_g_dwSputConInitialize") = 0x0;
/* 0x008ca1c0, 4 bytes */ /* loose */ unsigned int grim_def_g_dwSputConStartup __asm__("_g_dwSputConStartup") = 0x0;
