/* GRIMFANDANGO.EXE :: platmodule.c
 * functions 0x004abe90 .. 0x004abf30 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004abe90  Graph_SysInitialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name Graph_SysInitialize (the remaster's GrimFandango (Linux): aligned call in
   sputText_Initialize); was PlatModule_Init. */

int Graph_SysInitialize(GrimServices *svc,SysModuleIface *iface)

{
  int iVar1;
  
  _g_pGraphHS = svc;
  iVar1 = 1;
  if (g_dwGraphSysInitialized == 0) {
    g_dwGraphSysInitialized = 1;
    if (iface != (SysModuleIface *)0x0) {
      iface->pfnInitialize = Graph_SysInitialize;
      iface->pfnTerminate = Graph_SysTerminate;
      iface->pfnStartup = Graph_SysStartup;
      iface->pfnShutdown = Graph_SysShutdown;
      iface->pfnSave = (code *)0x0;
      iface->pfnRestore = (code *)0x0;
      iface->pfnReserved1 = (code *)0x0;
      iface->pfnReserved2 = (code *)0x0;
    }
    iVar1 = 0;
  }
  return iVar1;
}

/* ---- 0x004abef0  Graph_SysTerminate ---- */
/* Module interface slot 1 (PlatModule): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. Original name Graph_SysTerminate
   (the remaster's GrimFandango (Linux): aligned call in Graph_SysInitialize); was
   PlatModule_Terminate. */

void __cdecl Graph_SysTerminate(void)

{
  g_dwGraphSysInitialized = 0;
  return;
}

/* ---- 0x004abf00  Graph_SysStartup ---- */
/* Module interface slot 2 (PlatModule): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). Original name Graph_SysStartup (the remaster's
   GrimFandango (Linux): aligned call in Graph_SysInitialize); was PlatModule_Start. */

uint __cdecl Graph_SysStartup(void)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((g_dwGraphSysInitialized != 0) && (g_dwGraphSysStarted == 0)) {
    g_dwGraphSysStarted = 1;
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x004abf30  Graph_SysShutdown ---- */
/* Module interface slot 3 (PlatModule): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name Graph_SysShutdown (the remaster's GrimFandango
   (Linux): aligned call in Graph_SysInitialize); was PlatModule_Stop. */

void __cdecl Graph_SysShutdown(void)

{
  g_dwGraphSysStarted = 0;
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned int grim_def_g_dwGraphSysInitialized __asm__("_g_dwGraphSysInitialized");
extern unsigned int grim_def_g_dwGraphSysStarted __asm__("_g_dwGraphSysStarted");
extern unsigned char grim_def_g_pGraphHS[4] __asm__("_g_pGraphHS");
/* 0x008d098c, 4 bytes */ GRIM_DATA("008d098c") unsigned char grim_def_g_pGraphHS[4] __asm__("_g_pGraphHS") = {0};
/* 0x008d0990, 4 bytes */ GRIM_DATA("008d0990") unsigned int grim_def_g_dwGraphSysInitialized __asm__("_g_dwGraphSysInitialized") = 0x0;
/* 0x008d0994, 4 bytes */ GRIM_DATA("008d0994") unsigned int grim_def_g_dwGraphSysStarted __asm__("_g_dwGraphSysStarted") = 0x0;
