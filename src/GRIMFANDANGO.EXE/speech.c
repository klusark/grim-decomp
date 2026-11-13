/* GRIMFANDANGO.EXE :: speech.c
 * functions 0x004931c0 .. 0x004931e0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004931c0  sputActor_SetSpeechMode ---- */
/* Lua SetSpeechMode: 1 text only, 2 voice only, 3 both Original name sputActor_SetSpeechMode (the
   remaster's GrimFandango (Linux): the only unpaired user of smSpeechMode, same body, called from
   sputLua_SetSpeechMode on both sides); was Speech_SetMode. */

void __cdecl sputActor_SetSpeechMode(int mode)

{
  if ((mode != g_dwSmSpeechMode) && ((mode & 3U) != 0)) {
    g_dwSmSpeechMode = mode;
  }
  return;
}

/* ---- 0x004931e0  sputActor_GetSpeechMode ---- */
/* Returns bits: 1 text, 2 voice Original name sputActor_GetSpeechMode (the remaster's GrimFandango
   (Linux): the only unmatched callee of Lua_GetSpeechMode; 1 matched neighbours agree, 0 disagree);
   was Speech_GetMode. */

uint __cdecl sputActor_GetSpeechMode(void)

{
  return g_dwSmSpeechMode;
}
