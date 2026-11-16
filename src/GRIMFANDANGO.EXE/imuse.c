/* GRIMFANDANGO.EXE :: imuse.c
 * functions 0x00483610 .. 0x00483650 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00483610  IMuse_SaveToTemp ---- */
/* Lua SaveIMuse: writes the sound module's save hook output to grim.tmp */

void __cdecl IMuse_SaveToTemp(void)

{
  UINT_008a8770 = (uint)SaveFile_Open(s_grim_tmp_004e8018,s_wb_004ddd78);
  if ((void *)UINT_008a8770 != (void *)0x0) {
    if (g_pfnIMuseSaveHook != (void *)0x0) {
      (*(code *)g_pfnIMuseSaveHook)(SaveGame_Write);
    }
    gzclose(UINT_008a8770);
  }
  return;
}

/* ---- 0x00483650  IMuse_RestoreFromTemp ---- */
/* Lua RestoreIMuse: stops all sounds, feeds grim.tmp to the sound module's restore hook, deletes
   the file */

void __cdecl IMuse_RestoreFromTemp(void)

{
  UINT_008a8770 = (uint)SaveFile_Open(s_grim_tmp_004e8018,s_rb_004ddb18);
  if ((void *)UINT_008a8770 != (void *)0x0) {
    if (g_pfnIMuseRestoreHook != (void *)0x0) {
      ImStopAllSounds();
      (*(code *)g_pfnIMuseRestoreHook)(SaveGame_Read);
    }
    gzclose(UINT_008a8770);
    DeleteFileA(((unsigned)(uintptr_t)&s_grim_tmp_004e8018));
  }
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char grim_def_s_grim_tmp_004e8018[12] __asm__("_s_grim_tmp_004e8018");
/* 0x004e8018, 12 bytes */ /* loose */ char grim_def_s_grim_tmp_004e8018[12] __asm__("_s_grim_tmp_004e8018") = "grim.tmp";
