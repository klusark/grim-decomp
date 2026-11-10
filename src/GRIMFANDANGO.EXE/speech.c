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
  if ((mode != g_dwSpeechMode) && ((mode & 3U) != 0)) {
    g_dwSpeechMode = mode;
  }
  return;
}

/* ---- 0x004931e0  sputActor_GetSpeechMode ---- */
/* Returns bits: 1 text, 2 voice Original name sputActor_GetSpeechMode (the remaster's GrimFandango
   (Linux): the only unmatched callee of Lua_GetSpeechMode; 1 matched neighbours agree, 0 disagree);
   was Speech_GetMode. */

uint sputActor_GetSpeechMode(void)

{
  return g_dwSpeechMode;
}
