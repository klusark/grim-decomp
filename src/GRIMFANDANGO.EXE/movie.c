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

uint __cdecl sputSmush_Restore(code *read)

{
  sputSmush_SetTarget(&g_dwStdDisplay_frontBuffer);
  (*read)(&g_nSmushPlaying,4);
  (*read)(&g_nSmushPaused,4);
  (*read)(&g_nSmushAbort,4);
  (*read)(g_szCurMovieFile,0x80);
  (*read)(&g_nSmushLooping,4);
  (*read)(&g_dwSmushX,4);
  (*read)(&g_dwSmushY,4);
  if (g_nSmushPlaying != 0) {
    sputSmush_StartMovie(g_szCurMovieFile,g_nSmushLooping,g_dwSmushX,g_dwSmushY);
  }
  return 0;
}

/* ---- 0x004891b0  sputSmush_Periodic ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name sputSmush_Periodic (the remaster's GrimFandango (Linux): aligned call in
   sputRender_Update); was Movie_PollPlayback. */

uint __cdecl sputSmush_Periodic(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define auStack_10 (*(uint (*)[4])(_frame + (0x30 - 0x10)))
  
  local_14 = 0;
  uVar2 = 1;
  if ((g_nSputSmushStarted == 0) || (g_nSmushPlaying == 0)) {
    return 1;
  }
  if (g_nSmushPaused != 0) {
    return 0;
  }
  SmushPlay_SetTranslationTable(((unsigned)(uintptr_t)&g_wSputRender_ColorLookup));
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
    SmushPlay_GetFrameRect(auStack_10,(uint *)0x0);
    MarkDirtyRect((int *)auStack_10,0);
  }
LAB_00489259:
  SmushPlay_SysConfigureColorLookup(0);
  _DAT_008ca098 = timeGetTime();
  return uVar2;
}
#undef auStack_10
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

uint __cdecl sputSmush_StartMovie(char *name,int loop,uint x,uint y)

{
  int iVar1;
  
  if (g_nSputSmushStarted != 0) {
    if (g_nSmushPlaying != 0) {
      SmushPlay_StopMovie();
      g_nSmushPlaying = 0;
    }
    SmushPlay_SetTranslationTable(((unsigned)(uintptr_t)&g_wSputRender_ColorLookup));
    g_nSmushLooping = loop;
    g_dwSmushX = x;
    g_dwSmushY = y;
    iVar1 = SmushPlay_StartMovie
                      (name,-(uint)(loop != 0) & 0x10,100000,x,y,(g_pPresentBuf->format).nWidth,
                       (g_pPresentBuf->format).nHeight,0,(uint)(UINT_009016ac != 6));
    if (iVar1 == 0) {
      g_nSmushPlaying = 1;
      g_nSmushPaused = iVar1;
      g_nSmushAbort = iVar1;
      strncpy((uint *)g_szCurMovieFile,(uint *)name,0x80);
      _g_dwSmushStartTime = timeGetTime();
      return 0;
    }
  }
  return 1;
}

/* ---- 0x00489370  sputSmush_StopMovie ---- */
/* Original name sputSmush_StopMovie (the remaster's GrimFandango (Linux): aligned call in
   sputLua_DetachFromResourcesL); was Movie_Stop. */

void __cdecl sputSmush_StopMovie(void)

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

int __cdecl sputSmush_GetMovieLength(char *name)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_80 (*(char (*)[128])(_frame + (0x90 - 0x80)))
  
  iVar1 = Res_FindExternalFile(name,local_80,0x80);
  if (iVar1 != 1) {
    return 0;
  }
  iVar1 = SmushPlay_GetMovieLength(local_80);
  return iVar1;
}
#undef local_80


/* ---- 0x004893d0  sputSmush_StartVideo ---- */
/* Smush surface callback: 0 when the movie surface has exactly the requested width, height and bits
   per pixel. Original name sputSmush_StartVideo (the remaster's GrimFandango (Linux): slot 0 of
   sputVideoCallBacks (g_pSputVideoCallBacks)); was Movie_CheckSurfaceFormat. */

uint __cdecl sputSmush_StartVideo(int width,int height,int bpp)

{
  if ((((g_nSputSmushStarted != 0) && ((g_pPresentBuf->format).nWidth == width)) &&
      ((g_pPresentBuf->format).nHeight == height)) &&
     ((g_pPresentBuf->format).colorFormat.nBpp == bpp)) {
    return 0;
  }
  return 1;
}

/* ---- 0x00489410  sputSmush_StopVideo ---- */
/* Original name sputSmush_StopVideo (the remaster's GrimFandango (Linux): slot 1 of
   sputVideoCallBacks (g_pSputVideoCallBacks)); was FUN_00489410. */

int __cdecl sputSmush_StopVideo(void)

{
  return (uint)(g_nSputSmushStarted == 0);
}

/* ---- 0x00489420  sputSmush_LockMovieBuffer ---- */
/* Smush surface callback: locks the movie surface and returns its description (pixels, pitch, size,
   bytes per pixel) and the full-frame rectangle. Original name sputSmush_LockMovieBuffer (the
   remaster's GrimFandango (Linux): slot 2 of sputVideoCallBacks (g_pSputVideoCallBacks)); was
   Movie_LockSurface. */

uint __cdecl sputSmush_LockMovieBuffer(undefined4 *outBuffer,undefined4 *outOrigin)

{
  if (g_nSputSmushStarted == 0) {
    return 1;
  }
  stdDisplay_VBufferLock(g_pPresentBuf);
  outBuffer[3] = (uint)(g_pPresentBuf->format).colorFormat.nBpp >> 3;
  *outBuffer = g_pPresentBuf->pPixels;
  outBuffer[2] = (g_pPresentBuf->format).nHeight;
  outBuffer[1] = (g_pPresentBuf->format).nWidth;
  outBuffer[5] = (g_pPresentBuf->format).nPitch;
  outOrigin[1] = 0;
  *outOrigin = 0;
  outOrigin[3] = (g_pPresentBuf->format).nHeight;
  outOrigin[2] = (g_pPresentBuf->format).nWidth;
  return 0;
}

/* ---- 0x004894b0  sputSmush_UnLockMovieBuffer ---- */
/* Smush surface callback: unlocks the movie surface. Original name sputSmush_UnLockMovieBuffer (the
   remaster's GrimFandango (Linux): slot 3 of sputVideoCallBacks (g_pSputVideoCallBacks)); was
   Movie_UnlockSurface. */

uint __cdecl sputSmush_UnLockMovieBuffer(void)

{
  if (g_nSputSmushStarted == 0) {
    return 1;
  }
  stdDisplay_VBufferUnlock(g_pPresentBuf);
  return 0;
}

/* ---- 0x004894d0  sputSmush_SetVideoPalette ---- */
/* Original name sputSmush_SetVideoPalette (the remaster's GrimFandango (Linux): slot 5 of
   sputVideoCallBacks (g_pSputVideoCallBacks)); was FUN_004894d0. */

int __cdecl sputSmush_SetVideoPalette(void)

{
  return (uint)(g_nSputSmushStarted == 0);
}

/* ---- 0x004894e0  sputSmush_MoviePlaying ---- */
/* Original name sputSmush_MoviePlaying (the remaster's GrimFandango (Linux): returns SmushPlaying,
   called by sputLua_IsMoviePlayingL); was Movie_IsPlaying. */

int __cdecl sputSmush_MoviePlaying(void)

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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_008ca098[8] __asm__("_DAT_008ca098");
extern unsigned char grim_def_UINT_009016ac[44] __asm__("_UINT_009016ac");
extern unsigned char grim_def_g_dwSmushStartTime[8] __asm__("_g_dwSmushStartTime");
extern unsigned int grim_def_g_dwSmushX __asm__("_g_dwSmushX");
extern unsigned int grim_def_g_dwSmushY __asm__("_g_dwSmushY");
extern int grim_def_g_nSmushAbort __asm__("_g_nSmushAbort");
extern int grim_def_g_nSmushLooping __asm__("_g_nSmushLooping");
extern int grim_def_g_nSmushPaused __asm__("_g_nSmushPaused");
extern int grim_def_g_nSmushPlaying __asm__("_g_nSmushPlaying");
extern char grim_def_g_szCurMovieFile[128] __asm__("_g_szCurMovieFile");
/* 0x008c9fb0, 4 bytes */ GRIM_DATA("008c9fb0") unsigned int grim_def_g_dwSmushX __asm__("_g_dwSmushX") = 0x0;
/* 0x008c9fb4, 4 bytes */ GRIM_DATA("008c9fb4") unsigned int grim_def_g_dwSmushY __asm__("_g_dwSmushY") = 0x0;
/* 0x008c9ff8, 8 bytes */ GRIM_DATA("008c9ff8") unsigned char grim_def_g_dwSmushStartTime[8] __asm__("_g_dwSmushStartTime") = {0};
/* 0x008ca000, 128 bytes */ GRIM_DATA("008ca000") char grim_def_g_szCurMovieFile[128] __asm__("_g_szCurMovieFile") = "";
/* 0x008ca088, 4 bytes */ GRIM_DATA("008ca088") int grim_def_g_nSmushPlaying __asm__("_g_nSmushPlaying") = 0;
/* 0x008ca08c, 4 bytes */ GRIM_DATA("008ca08c") int grim_def_g_nSmushPaused __asm__("_g_nSmushPaused") = 0;
/* 0x008ca090, 4 bytes */ GRIM_DATA("008ca090") int grim_def_g_nSmushAbort __asm__("_g_nSmushAbort") = 0;
/* 0x008ca094, 4 bytes */ GRIM_DATA("008ca094") int grim_def_g_nSmushLooping __asm__("_g_nSmushLooping") = 0;
/* 0x008ca098, 8 bytes */ GRIM_DATA("008ca098") unsigned char grim_def_DAT_008ca098[8] __asm__("_DAT_008ca098") = {0};
/* 0x009016ac, 44 bytes */ GRIM_DATA("009016ac") unsigned char grim_def_UINT_009016ac[44] __asm__("_UINT_009016ac") = {0};
