/* GRIMFANDANGO.EXE :: sputrender.c
 * functions 0x00483d40 .. 0x004860d0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00483d40  sputRender_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

uint __cdecl sputRender_Initialize(GrimServices *services,undefined4 *iface)

{
  g_pSputRendHS = services;
  *iface = sputRender_Initialize;
  iface[1] = sputRender_Terminate;
  iface[2] = sputRender_Startup;
  iface[3] = sputRender_Shutdown;
  iface[4] = sputRender_Save;
  iface[5] = sputRender_Restore;
  iface[6] = 0;
  iface[7] = 0;
  sputControl_AddCallback(sputRender_ControlHandler);
  g_dwSputRendInitialize = 1;
  return 0;
}

/* ---- 0x00486050  sputRender_Terminate ---- */
/* Module interface slot 1 (sputRender): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. */

void __cdecl sputRender_Terminate(void)

{
  g_pSputRendHS = (GrimServices *)0x0;
  if (g_dwSputRendInitialize != 0) {
    g_dwSputRendInitialize = 0;
  }
  return;
}

/* ---- 0x00486070  sputRender_Startup ---- */
/* Module interface slot 2 (sputRender): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start creates the dirty-rectangle pool, _Stop frees
   the cache rects and the pool. Original name sputRender_Startup (the remaster's GrimFandango
   (Linux): aligned call in sputRender_Initialize); was sputRender_Start. */

int __cdecl sputRender_Startup(void)

{
  bool bVar1;
  
  bVar1 = g_dwSputRendStartup != 0;
  if (!bVar1) {
    g_dwSputRendStartup = 1;
    g_dwRenderVars[0] = 4;
    g_dwRenderVars[1] = 3;
    g_dwRenderVars[2] = 1;
    g_dwRenderVars[3] = 1;
    g_dwRenderVars[4] = 0;
    g_dwRenderVars[5] = 0;
    g_dwRenderVars[6] = 2;
    g_pDirtyRectPool = Memory_AllocatePool(0x24,(void *)0x20,(void *)0x8);
  }
  return (uint)bVar1;
}

/* ---- 0x004860d0  sputRender_Shutdown ---- */
/* Module interface slot 3 (sputRender): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputRender_Shutdown (the remaster's GrimFandango
   (Linux): aligned call in sputRender_Initialize); was sputRender_Stop. */

void __cdecl sputRender_Shutdown(void)

{
  CacheRect_FreeAll();
  if (g_pDirtyRectPool != (void **)0x0) {
    Memory_FreePool(g_pDirtyRectPool);
    g_pDirtyRectPool = (void **)0x0;
  }
  g_dwSputRendStartup = 0;
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned int grim_def_g_dwSputRendInitialize __asm__("_g_dwSputRendInitialize");
extern unsigned int grim_def_g_dwSputRendStartup __asm__("_g_dwSputRendStartup");
/* 0x008c9788, 4 bytes */ GRIM_DATA("008c9788") unsigned int grim_def_g_dwSputRendInitialize __asm__("_g_dwSputRendInitialize") = 0x0;
/* 0x008c978c, 4 bytes */ GRIM_DATA("008c978c") unsigned int grim_def_g_dwSputRendStartup __asm__("_g_dwSputRendStartup") = 0x0;
