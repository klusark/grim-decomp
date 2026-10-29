/* GRIMFANDANGO.EXE :: timer.c
 * functions 0x004a3be0 .. 0x004a3ce0 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a3be0  Timer_GetTotalMs ---- */
uint Timer_GetTotalMs(void)

{
  return g_dwTimerTotalMs;
}

/* ---- 0x004a3bf0  Timer_GetFrameMs ---- */
uint Timer_GetFrameMs(void)

{
  return g_dwTimerFrameMs;
}

/* ---- 0x004a3c00  Timer_GetFrameSeconds ---- */
float __cdecl Timer_GetFrameSeconds(void)

{
  return g_flTimerFrameSeconds;
}

/* ---- 0x004a3c10  Timer_UpdateFromWallClock ---- */
/* Frame time from the wall clock: DAT_008caba8 = timeGetTime() - last, capped at 300 ms;
   DAT_008caba4 += it (total ms); DAT_008cabac = ms * 0.001 (frame seconds, read by
   Timer_GetFrameSeconds). The real-time path; jitters with the machine. */

void Timer_UpdateFromWallClock(void)

{
  uint uVar1;
  
  uVar1 = timeGetTime();
  if (uVar1 < g_dwTimerLastTick) {
    g_dwTimerFrameMs = (uVar1 - g_dwTimerLastTick) - 1;
  }
  else {
    g_dwTimerFrameMs = uVar1 - g_dwTimerLastTick;
  }
  g_dwTimerLastTick = uVar1;
  if (299 < g_dwTimerFrameMs) {
    g_dwTimerFrameMs = 300;
  }
  g_dwTimerTotalMs = g_dwTimerTotalMs + g_dwTimerFrameMs;
  g_flTimerFrameSeconds = (float)g_dwTimerFrameMs * 0.001;
  return;
}

/* ---- 0x004a3c80  Timer_UpdateFixedStep ---- */
/* Frame time given by the caller (ms, capped at 300): same globals as Timer_UpdateFromWallClock,
   but the length of the frame is the argument, not the clock. Used with a fixed frame time (see
   Game_FrameUpdate). */

void Timer_UpdateFixedStep(uint param_1)

{
  g_dwTimerFrameMs = param_1;
  if (299 < param_1) {
    g_dwTimerFrameMs = 300;
  }
  g_dwTimerTotalMs = g_dwTimerTotalMs + g_dwTimerFrameMs;
  g_flTimerFrameSeconds = (float)g_dwTimerFrameMs * 0.001;
  g_dwTimerLastTick = timeGetTime();
  return;
}

/* ---- 0x004a3ce0  Timer_Reset ---- */
void Timer_Reset(void)

{
  g_dwTimerTotalMs = 0;
  g_dwTimerFrameMs = 0;
  g_flTimerFrameSeconds = 0.0;
  g_dwTimerLastTick = timeGetTime();
  return;
}
