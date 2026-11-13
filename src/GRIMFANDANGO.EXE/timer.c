/* GRIMFANDANGO.EXE :: timer.c
 * functions 0x004a3be0 .. 0x004a3ce0 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a3be0  sputTime_GetGameTime ---- */
/* Original name sputTime_GetGameTime (the remaster's GrimFandango (Linux): aligned call in
   sputRender_IrisDown, sputRender_IrisUp, sputRender_Update); was Timer_GetTotalMs. */

uint __cdecl sputTime_GetGameTime(void)

{
  return g_dwSputTime_gameTime_ms;
}

/* ---- 0x004a3bf0  sputTime_GetFrameTime ---- */
/* Original name sputTime_GetFrameTime (the remaster's GrimFandango (Linux): aligned call in
   grimlib_UpdateManual, sputLua_Update, sputText_Update); was Timer_GetFrameMs. */

uint __cdecl sputTime_GetFrameTime(void)

{
  return g_dwSputTime_frameTime_ms;
}

/* ---- 0x004a3c00  sputTime_GetFrameTimeFlex ---- */
/* Original name sputTime_GetFrameTimeFlex (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_PerSecond; 3 matched neighbours agree, 0 disagree); was Timer_GetFrameSeconds. */

float __cdecl sputTime_GetFrameTimeFlex(void)

{
  return g_flSputTime_frameTimeSeconds;
}

/* ---- 0x004a3c10  sputTime_Advance ---- */
/* Frame time from the wall clock: DAT_008caba8 = timeGetTime() - last, capped at 300 ms;
   DAT_008caba4 += it (total ms); DAT_008cabac = ms * 0.001 (frame seconds, read by
   Timer_GetFrameSeconds). The real-time path; jitters with the machine. Original name
   sputTime_Advance (the remaster's GrimFandango (Linux): aligned call in grimlib_UpdateManual); was
   Timer_UpdateFromWallClock. */

void __cdecl sputTime_Advance(void)

{
  uint uVar1;
  
  uVar1 = timeGetTime();
  if (uVar1 < g_dwLastClockTime) {
    g_dwSputTime_frameTime_ms = (uVar1 - g_dwLastClockTime) - 1;
  }
  else {
    g_dwSputTime_frameTime_ms = uVar1 - g_dwLastClockTime;
  }
  g_dwLastClockTime = uVar1;
  if (299 < g_dwSputTime_frameTime_ms) {
    g_dwSputTime_frameTime_ms = 300;
  }
  g_dwSputTime_gameTime_ms = g_dwSputTime_gameTime_ms + g_dwSputTime_frameTime_ms;
  g_flSputTime_frameTimeSeconds = (float)g_dwSputTime_frameTime_ms * 0.001;
  return;
}

/* ---- 0x004a3c80  sputTime_AdvanceManual ---- */
/* Frame time given by the caller (ms, capped at 300): same globals as Timer_UpdateFromWallClock,
   but the length of the frame is the argument, not the clock. Used with a fixed frame time (see
   Game_FrameUpdate). Original name sputTime_AdvanceManual (the remaster's GrimFandango (Linux):
   aligned call in grimlib_UpdateManual, sputRender_Dim); was Timer_UpdateFixedStep. */

void __cdecl sputTime_AdvanceManual(uint param_1)

{
  g_dwSputTime_frameTime_ms = param_1;
  if (299 < param_1) {
    g_dwSputTime_frameTime_ms = 300;
  }
  g_dwSputTime_gameTime_ms = g_dwSputTime_gameTime_ms + g_dwSputTime_frameTime_ms;
  g_flSputTime_frameTimeSeconds = (float)g_dwSputTime_frameTime_ms * 0.001;
  g_dwLastClockTime = timeGetTime();
  return;
}

/* ---- 0x004a3ce0  Timer_Reset ---- */
void __cdecl Timer_Reset(void)

{
  g_dwSputTime_gameTime_ms = 0;
  g_dwSputTime_frameTime_ms = 0;
  g_flSputTime_frameTimeSeconds = 0.0;
  g_dwLastClockTime = timeGetTime();
  return;
}
