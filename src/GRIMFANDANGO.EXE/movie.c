/* GRIMFANDANGO.EXE :: movie.c
 * functions 0x00489030 .. 0x004894f0 (14 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00489030  sputSmush_Save ---- */
/* Original name sputSmush_Save (the remaster's GrimFandango (Linux): aligned call in
   sputSmush_Initialize); was Movie_SaveState. */

int __cdecl sputSmush_Save(void *fn)

{
  (*(code *)fn)(&g_nSmushPlaying,4);
  (*(code *)fn)(&g_nSmushPaused,4);
  (*(code *)fn)(&g_nSmushAbort,4);
  (*(code *)fn)(g_szCurMovieFile,0x80);
  (*(code *)fn)(&g_nSmushLooping,4);
  (*(code *)fn)(&g_dwSmushX,4);
  (*(code *)fn)(&g_dwSmushY,4);
  return 0;
}

/* ---- 0x00489090  sputSmush_Restore ---- */
/* Module slot 5 of sputSmush: reads the movie state saved by Movie_SaveState (playing/paused/stop
   flag, file name, fullscreen, position) and restarts the movie with Movie_Start if one was
   playing. Original name sputSmush_Restore (the remaster's GrimFandango (Linux): aligned call in
   sputSmush_Initialize); was Movie_RestoreState. */

undefined4 sputSmush_Restore(code *param_1)

{
  sputSmush_SetTarget(&g_dwStdDisplay_frontBuffer);
  (*param_1)(&g_nSmushPlaying,4);
  (*param_1)(&g_nSmushPaused,4);
  (*param_1)(&g_nSmushAbort,4);
  (*param_1)(g_szCurMovieFile,0x80);
  (*param_1)(&g_nSmushLooping,4);
  (*param_1)(&g_dwSmushX,4);
  (*param_1)(&g_dwSmushY,4);
  if (g_nSmushPlaying != 0) {
    sputSmush_StartMovie(g_szCurMovieFile,g_nSmushLooping,g_dwSmushX,g_dwSmushY);
  }
  return 0;
}

/* ---- 0x004891b0  sputSmush_Periodic ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name sputSmush_Periodic (the remaster's GrimFandango (Linux): aligned call in
   sputRender_Update); was Movie_PollPlayback. */

undefined4 sputSmush_Periodic(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define aiStack_10 (*(int (*)[4])(_frame + (0x30 - 0x10)))
  
  local_14 = 0;
  uVar2 = 1;
  if ((g_nSputSmushStarted == 0) || (g_nSmushPlaying == 0)) {
    return 1;
  }
  if (g_nSmushPaused != 0) {
    return 0;
  }
  SmushPlay_SetTranslationTable(&g_wSputRender_ColorLookup);
  timeGetTime();
  if (g_nSmushAbort == 0) {
    iVar1 = SmushPlay_UpdateMovie((int *)&local_14);
    if (iVar1 != 0) goto LAB_00489259;
  }
  if ((local_14 == 0) && (g_nSmushAbort == 0)) {
    uVar2 = 0;
  }
  else {
    g_nSmushPlaying = 0;
    SmushPlay_StopMovie();
    SmushPlay_GetFrameRect(aiStack_10,0);
    MarkDirtyRect(aiStack_10,0);
  }
LAB_00489259:
  SmushPlay_SysConfigureColorLookup(0);
  _DAT_008ca098 = timeGetTime();
  return uVar2;
}
#undef aiStack_10
#undef local_14


/* ---- 0x00489280  sputSmush_SetTarget ---- */
/* Original name sputSmush_SetTarget (the remaster's GrimFandango (Linux): aligned call in
   grimlib_PlayMovie, sputRender_Dim, sputRender_Update); was Movie_SetTarget. */

int __cdecl sputSmush_SetTarget(void *surface)

{
  if (g_nSputSmushStarted == 0) {
    return 1;
  }
  g_pPresentBuf = surface;
  return 0;
}

/* ---- 0x004892a0  sputSmush_StartMovie ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name sputSmush_StartMovie (the remaster's GrimFandango (Linux): aligned call in
   grimlib_PlayMovie, sputSmush_Restore); was Movie_Start. */

undefined4 sputSmush_StartMovie(char *param_1,int param_2,uint param_3,uint param_4)

{
  int iVar1;
  
  if (g_nSputSmushStarted != 0) {
    if (g_nSmushPlaying != 0) {
      SmushPlay_StopMovie();
      g_nSmushPlaying = 0;
    }
    SmushPlay_SetTranslationTable(&g_wSputRender_ColorLookup);
    g_nSmushLooping = param_2;
    g_dwSmushX = param_3;
    g_dwSmushY = param_4;
    iVar1 = SmushPlay_StartMovie
                      (param_1,-(uint)(param_2 != 0) & 0x10,100000,param_3,param_4,
                       *(int *)((int)g_pPresentBuf + 0xc),*(int *)((int)g_pPresentBuf + 0x10),0,
                       (uint)(UINT_009016ac != 6));
    if (iVar1 == 0) {
      g_nSmushPlaying = 1;
      g_nSmushPaused = iVar1;
      g_nSmushAbort = iVar1;
      strncpy(g_szCurMovieFile,param_1,0x80);
      _g_dwSmushStartTime = timeGetTime();
      return 0;
    }
  }
  return 1;
}

/* ---- 0x00489370  sputSmush_StopMovie ---- */
/* Original name sputSmush_StopMovie (the remaster's GrimFandango (Linux): aligned call in
   sputLua_DetachFromResourcesL); was Movie_Stop. */

void sputSmush_StopMovie(void)

{
  if (g_nSputSmushStarted != 0) {
    g_nSmushAbort = 1;
    g_nSmushPaused = 0;
  }
  return;
}

/* ---- 0x00489390  sputSmush_GetMovieLength ---- */
/* Resolves the movie name through the resource system and hands the path to the SMUSH player
   Original name sputSmush_GetMovieLength (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_GetSmushLength; 1 matched neighbours agree, 0 disagree); was Movie_SetFile. */

int sputSmush_GetMovieLength(char *param_1)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_80 (*(char (*)[128])(_frame + (0x90 - 0x80)))
  
  iVar1 = Res_FindExternalFile(param_1,local_80,0x80);
  if (iVar1 != 1) {
    return 0;
  }
  iVar1 = SmushPlay_GetMovieLength(local_80);
  return iVar1;
}
#undef local_80


/* ---- 0x004893d0  Movie_CheckSurfaceFormat ---- */
/* Smush surface callback: 0 when the movie surface has exactly the requested width, height and bits
   per pixel. */

undefined4 Movie_CheckSurfaceFormat(int param_1,int param_2,int param_3)

{
  if ((((g_nSputSmushStarted != 0) && (*(int *)((int)g_pPresentBuf + 0xc) == param_1)) &&
      (*(int *)((int)g_pPresentBuf + 0x10) == param_2)) &&
     (*(int *)((int)g_pPresentBuf + 0x24) == param_3)) {
    return 0;
  }
  return 1;
}

/* ---- 0x00489410  FUN_00489410 ---- */
int FUN_00489410(void)

{
  return g_nSputSmushStarted == 0;
}

/* ---- 0x00489420  Movie_LockSurface ---- */
/* Smush surface callback: locks the movie surface and returns its description (pixels, pitch, size,
   bytes per pixel) and the full-frame rectangle. */

undefined4 Movie_LockSurface(undefined4 *param_1,undefined4 *param_2)

{
  if (g_nSputSmushStarted == 0) {
    return 1;
  }
  stdDisplay_VBufferLock(g_pPresentBuf);
  param_1[3] = *(uint *)((int)g_pPresentBuf + 0x24) >> 3;
  *param_1 = *(undefined4 *)((int)g_pPresentBuf + 0x5c);
  param_1[2] = *(undefined4 *)((int)g_pPresentBuf + 0x10);
  param_1[1] = *(undefined4 *)((int)g_pPresentBuf + 0xc);
  param_1[5] = *(undefined4 *)((int)g_pPresentBuf + 0x18);
  param_2[1] = 0;
  *param_2 = 0;
  param_2[3] = *(undefined4 *)((int)g_pPresentBuf + 0x10);
  param_2[2] = *(undefined4 *)((int)g_pPresentBuf + 0xc);
  return 0;
}

/* ---- 0x004894b0  Movie_UnlockSurface ---- */
/* Smush surface callback: unlocks the movie surface. */

undefined4 Movie_UnlockSurface(void)

{
  if (g_nSputSmushStarted == 0) {
    return 1;
  }
  stdDisplay_VBufferUnlock(g_pPresentBuf);
  return 0;
}

/* ---- 0x004894d0  FUN_004894d0 ---- */
int FUN_004894d0(void)

{
  return g_nSputSmushStarted == 0;
}

/* ---- 0x004894e0  sputSmush_MoviePlaying ---- */
/* Original name sputSmush_MoviePlaying (the remaster's GrimFandango (Linux): returns SmushPlaying,
   called by sputLua_IsMoviePlayingL); was Movie_IsPlaying. */

int sputSmush_MoviePlaying(void)

{
  return g_nSmushPlaying;
}

/* ---- 0x004894f0  sputSmush_Pause ---- */
/* Original name sputSmush_Pause (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_PauseMovie; 3 matched neighbours agree, 0 disagree); was Movie_SetPaused. */

void sputSmush_Pause(int paused)

{
  g_nSmushPaused = paused;
  if (paused != 0) {
    SmushPlay_Pause();
    return;
  }
  SmushPlay_Resume();
  return;
}
