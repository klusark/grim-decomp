/* GRIMFANDANGO.EXE :: imuse.c
 * functions 0x00483610 .. 0x00483650 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00483610  IMuse_SaveToTemp ---- */
/* Lua SaveIMuse: writes the sound module's save hook output to grim.tmp */

void IMuse_SaveToTemp(void)

{
  UINT_008a8770 = (uint)SaveFile_Open(s_grim_tmp_004e8018,&DAT_004ddd78);
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

void IMuse_RestoreFromTemp(void)

{
  UINT_008a8770 = (uint)SaveFile_Open(s_grim_tmp_004e8018,&DAT_004ddb18);
  if ((void *)UINT_008a8770 != (void *)0x0) {
    if (g_pfnIMuseRestoreHook != (void *)0x0) {
      ImStopAllSounds();
      (*(code *)g_pfnIMuseRestoreHook)(SaveGame_Read);
    }
    gzclose(UINT_008a8770);
    DeleteFileA(IMG_ADDR(0x004e8018));
  }
  return;
}
