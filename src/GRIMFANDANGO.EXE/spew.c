/* GRIMFANDANGO.EXE :: spew.c
 * functions 0x00488840 .. 0x00488890 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00488840  Spew_Startup ---- */
/* Loads spew.dll on first use and calls its Spew_Startup export (debug output DLL) */

void __cdecl Spew_Startup(void)

{
  if (g_hSpewDll == (void *)0x0) {
    Spew_LoadDll();
    if (g_hSpewDll == (void *)0x0) {
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x00488857. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)g_pfnSpewStartup)();
  return;
}

/* ---- 0x00488860  grimDebug_Shutdown ---- */
/* Original name grimDebug_Shutdown (the remaster's GrimFandango (Linux): the call before
   grimlib_Close in Main_Shutdown in both builds: the debug module's shutdown (here it unloads the
   spew DLL; the remaster's is empty)); was Spew_Shutdown. */

void __cdecl grimDebug_Shutdown(void)

{
  if (g_hSpewDll != (void *)0x0) {
    (*(code *)g_pfnSpewShutdown)();
    FreeLibrary((int)g_hSpewDll);
    g_hSpewDll = (void *)0x0;
  }
  return;
}

/* ---- 0x00488890  Spew_LoadDll ---- */
void __cdecl Spew_LoadDll(void)

{
  g_hSpewDll = (void *)LoadLibraryA(((unsigned)(uintptr_t)&DAT_004e8238));
  if (g_hSpewDll != (void *)0x0) {
    g_pfnSpewStartup = (void *)GetProcAddress((int)g_hSpewDll,((unsigned)(uintptr_t)&s_Spew_Startup_004e8228));
    g_pfnSpewShutdown = (void *)GetProcAddress((int)g_hSpewDll,((unsigned)(uintptr_t)&s_Spew_Shutdown_004e8218));
  }
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_004e8238[16] __asm__("_DAT_004e8238");
extern unsigned char grim_def_g_hSpewDll[4] __asm__("_g_hSpewDll");
extern unsigned char grim_def_g_pfnSpewShutdown[4] __asm__("_g_pfnSpewShutdown");
extern unsigned char grim_def_g_pfnSpewStartup[4] __asm__("_g_pfnSpewStartup");
extern char grim_def_s_Spew_Shutdown_004e8218[16] __asm__("_s_Spew_Shutdown_004e8218");
extern char grim_def_s_Spew_Startup_004e8228[16] __asm__("_s_Spew_Startup_004e8228");
/* 0x004e8218, 16 bytes */ /* loose */ char grim_def_s_Spew_Shutdown_004e8218[16] __asm__("_s_Spew_Shutdown_004e8218") = "Spew_Shutdown";
/* 0x004e8228, 16 bytes */ /* loose */ char grim_def_s_Spew_Startup_004e8228[16] __asm__("_s_Spew_Startup_004e8228") = "Spew_Startup";
/* 0x004e8238, 16 bytes */ /* loose */ unsigned char grim_def_DAT_004e8238[16] __asm__("_DAT_004e8238") = { 0x73, 0x70, 0x65, 0x77, 0x2e, 0x64, 0x6c, 0x6c };
/* 0x008c9a64, 4 bytes */ /* loose */ unsigned char grim_def_g_pfnSpewStartup[4] __asm__("_g_pfnSpewStartup") = {0};
/* 0x008c9a68, 4 bytes */ /* loose */ unsigned char grim_def_g_pfnSpewShutdown[4] __asm__("_g_pfnSpewShutdown") = {0};
/* 0x008c9a6c, 4 bytes */ /* loose */ unsigned char grim_def_g_hSpewDll[4] __asm__("_g_hSpewDll") = {0};
