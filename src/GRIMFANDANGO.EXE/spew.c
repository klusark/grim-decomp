/* GRIMFANDANGO.EXE :: spew.c
 * functions 0x00488840 .. 0x00488890 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00488840  Spew_Startup ---- */
/* Loads spew.dll on first use and calls its Spew_Startup export (debug output DLL) */

void Spew_Startup(void)

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

/* ---- 0x00488860  Spew_Shutdown ---- */
void Spew_Shutdown(void)

{
  if (g_hSpewDll != (void *)0x0) {
    (*(code *)g_pfnSpewShutdown)();
    FreeLibrary((int)g_hSpewDll);
    g_hSpewDll = (void *)0x0;
  }
  return;
}

/* ---- 0x00488890  Spew_LoadDll ---- */
void Spew_LoadDll(void)

{
  g_hSpewDll = (void *)LoadLibraryA(IMG_ADDR(0x004e8238));
  if (g_hSpewDll != (void *)0x0) {
    g_pfnSpewStartup = (void *)GetProcAddress((int)g_hSpewDll,IMG_ADDR(0x004e8228));
    g_pfnSpewShutdown = (void *)GetProcAddress((int)g_hSpewDll,IMG_ADDR(0x004e8218));
  }
  return;
}
