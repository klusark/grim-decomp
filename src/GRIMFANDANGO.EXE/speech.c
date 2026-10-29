/* GRIMFANDANGO.EXE :: speech.c
 * functions 0x004931c0 .. 0x004931e0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004931c0  Speech_SetMode ---- */
/* Lua SetSpeechMode: 1 text only, 2 voice only, 3 both */

void __cdecl Speech_SetMode(int mode)

{
  if ((mode != DAT_004e9dfc) && ((mode & 3U) != 0)) {
    DAT_004e9dfc = mode;
  }
  return;
}

/* ---- 0x004931e0  Speech_GetMode ---- */
/* Returns bits: 1 text, 2 voice */

undefined4 Speech_GetMode(void)

{
  return DAT_004e9dfc;
}
