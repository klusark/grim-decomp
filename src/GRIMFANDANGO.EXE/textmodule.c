/* GRIMFANDANGO.EXE :: textmodule.c
 * functions 0x004aa7b0 .. 0x004aa8d0 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004aa7b0  Text_SysInitialize ---- */
/* Original name Text_SysInitialize (the remaster's GrimFandango (Linux): aligned call in
   sputText_Initialize); was TextModule_Init. */

int __cdecl Text_SysInitialize(GrimServices *svc,SysModuleIface *iface)

{
  int iVar1;
  
  g_pTextHS = svc;
  iVar1 = 1;
  if (g_dwTextSysInitialized == 0) {
    g_dwTextSysInitialized = 1;
    if (iface != (SysModuleIface *)0x0) {
      iface->pfnInitialize = Text_SysInitialize;
      iface->pfnTerminate = Text_SysTerminate;
      iface->pfnStartup = Text_SysStartup;
      iface->pfnShutdown = Text_SysShutdown;
      iface->pfnSave = Text_SysSave;
      iface->pfnRestore = Text_SysRestore;
      iface->pfnReserved1 = (code *)0x0;
      iface->pfnReserved2 = (code *)0x0;
    }
    iVar1 = 0;
  }
  return iVar1;
}

/* ---- 0x004aa810  Text_SysTerminate ---- */
/* Module interface slot 1 (TextModule): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. Original name Text_SysTerminate
   (the remaster's GrimFandango (Linux): aligned call in Text_SysInitialize); was
   TextModule_Terminate. */

void __cdecl Text_SysTerminate(void)

{
  g_dwTextSysInitialized = 0;
  return;
}

/* ---- 0x004aa820  Text_SysStartup ---- */
/* Module interface slot 2 (TextModule): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start fills the identity translation table and wraps
   the default font. Original name Text_SysStartup (the remaster's GrimFandango (Linux): aligned
   call in Text_SysInitialize); was TextModule_Start. */

void __cdecl Text_SysStartup(void)

{
  int iVar1;
  
  if ((g_dwTextSysInitialized != 0) && (g_dwTextSysStarted == 0)) {
    g_dwTextSysStarted = 1;
    iVar1 = 0;
    do {
      (&g_bLookup)[iVar1] = (char)iVar1;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0xff);
    Text_WrapLines((uint *)&g_pDefaultFont);
  }
  return;
}

/* ---- 0x004aa860  Text_SysShutdown ---- */
/* Module interface slot 3 (TextModule): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name Text_SysShutdown (the remaster's GrimFandango
   (Linux): aligned call in Text_SysInitialize); was TextModule_Stop. */

void __cdecl Text_SysShutdown(void)

{
  (*g_pTextHS->pHFree)(g_pDefaultFont);
  g_dwTextSysStarted = 0;
  return;
}

/* ---- 0x004aa880  Text_SysSave ---- */
/* Module interface slot 4 (TextModule): save-game writer, calls the SaveGame_Write callback it is
   handed for every field. Original name Text_SysSave (the remaster's GrimFandango (Linux): aligned
   call in Text_SysInitialize); was TextModule_SaveState. */

uint __cdecl Text_SysSave(code *write)

{
  uint local_4;
  
  local_4 = 0x42747854;
  (*write)(&local_4,4);
  local_4 = 1;
  (*write)(&local_4,4);
  local_4 = 0;
  (*write)(&local_4,4);
  return 0;
}

/* ---- 0x004aa8d0  Text_SysRestore ---- */
/* Expects 'TxtB', 1, 0 from the read function Original name Text_SysRestore (the remaster's
   GrimFandango (Linux): aligned call in Text_SysInitialize); was TextModule_CheckHeader. */

uint __cdecl Text_SysRestore(code *read)

{
  code *pcVar1;
  uint uVar2;
  
  pcVar1 = read;
  uVar2 = 1;
  (*read)(&read,4);
  if (read == (code *)0x42747854) {
    (*pcVar1)(&read,4);
    if (read == (code *)0x1) {
      (*pcVar1)(&read,4);
      if (read == (code *)0x0) {
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned int grim_def_g_dwTextSysInitialized __asm__("_g_dwTextSysInitialized");
extern unsigned int grim_def_g_dwTextSysStarted __asm__("_g_dwTextSysStarted");
/* 0x008d0980, 4 bytes */ GRIM_DATA("008d0980") unsigned int grim_def_g_dwTextSysInitialized __asm__("_g_dwTextSysInitialized") = 0x0;
/* 0x008d0984, 4 bytes */ GRIM_DATA("008d0984") unsigned int grim_def_g_dwTextSysStarted __asm__("_g_dwTextSysStarted") = 0x0;
