/* GRIMFANDANGO.EXE :: movie.c
 * functions 0x00489030 .. 0x00489530 (19 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00489030  Movie_SaveState ---- */
int __cdecl Movie_SaveState(void *fn)

{
  (*(code *)fn)(&g_nMoviePlaying,4);
  (*(code *)fn)(&g_nMoviePaused,4);
  (*(code *)fn)(&g_nMovieStopRequested,4);
  (*(code *)fn)(g_szMovieName,0x80);
  (*(code *)fn)(&g_nMovieFullscreen,4);
  (*(code *)fn)(&UINT_008c9fb0,4);
  (*(code *)fn)(&UINT_008c9fb4,4);
  return 0;
}

/* ---- 0x00489090  FUN_00489090 ---- */
undefined4 FUN_00489090(code *param_1)

{
  Movie_SetTarget(&g_PrimarySurface);
  (*param_1)(&g_nMoviePlaying,4);
  (*param_1)(&g_nMoviePaused,4);
  (*param_1)(&g_nMovieStopRequested,4);
  (*param_1)(g_szMovieName,0x80);
  (*param_1)(&g_nMovieFullscreen,4);
  (*param_1)(&UINT_008c9fb0,4);
  (*param_1)(&UINT_008c9fb4,4);
  if (g_nMoviePlaying != 0) {
    Movie_Start(g_szMovieName,g_nMovieFullscreen,UINT_008c9fb0,UINT_008c9fb4);
  }
  return 0;
}

/* ---- 0x00489130  FUN_00489130 ---- */
undefined4 FUN_00489130(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_c (*(char (*)[12])(_frame + (0x20 - 0xc)))
  
  iVar1 = Reg_GetString(s_StartSmush_004e8358,local_c,10,&DAT_004f5a98);
  if ((iVar1 != 0) && (iVar1 = _stricmp(local_c,s_FALSE_004e8350), iVar1 == 0)) {
    return 0;
  }
  iVar1 = (*(code *)UINT_008c9fc0)();
  if (iVar1 == 0) {
    g_nMovieAvailable = 1;
    return 0;
  }
  return 1;
}
#undef local_c


/* ---- 0x00489190  FUN_00489190 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00489190(void)

{
  if (g_nMovieAvailable != 0) {
                    /* WARNING: Could not recover jumptable at 0x00489199. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*_DAT_008c9fc4)();
    return;
  }
  return;
}

/* ---- 0x004891b0  Movie_PollPlayback ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Movie_PollPlayback(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define aiStack_10 (*(int (*)[4])(_frame + (0x30 - 0x10)))
  
  local_14 = 0;
  uVar2 = 1;
  if ((g_nMovieAvailable == 0) || (g_nMoviePlaying == 0)) {
    return 1;
  }
  if (g_nMoviePaused != 0) {
    return 0;
  }
  Smush_SetColorTable(&g_wColorTable);
  timeGetTime();
  if (g_nMovieStopRequested == 0) {
    iVar1 = Smush_Advance((int *)&local_14);
    if (iVar1 != 0) goto LAB_00489259;
  }
  if ((local_14 == 0) && (g_nMovieStopRequested == 0)) {
    uVar2 = 0;
  }
  else {
    g_nMoviePlaying = 0;
    Smush_Close();
    Smush_GetFrameRect(aiStack_10,0);
    Render_InvalidateRect(aiStack_10,0);
  }
LAB_00489259:
  Smush_Idle(0);
  _DAT_008ca098 = timeGetTime();
  return uVar2;
}
#undef aiStack_10
#undef local_14


/* ---- 0x00489280  Movie_SetTarget ---- */
int __cdecl Movie_SetTarget(void *surface)

{
  if (g_nMovieAvailable == 0) {
    return 1;
  }
  g_pMovieSurface = surface;
  return 0;
}

/* ---- 0x004892a0  Movie_Start ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Movie_Start(char *param_1,int param_2,uint param_3,uint param_4)

{
  int iVar1;
  
  if (g_nMovieAvailable != 0) {
    if (g_nMoviePlaying != 0) {
      Smush_Close();
      g_nMoviePlaying = 0;
    }
    Smush_SetColorTable(&g_wColorTable);
    g_nMovieFullscreen = param_2;
    UINT_008c9fb0 = param_3;
    UINT_008c9fb4 = param_4;
    iVar1 = Smush_Open(param_1,-(uint)(param_2 != 0) & 0x10,100000,param_3,param_4,
                       *(int *)((int)g_pMovieSurface + 0xc),*(int *)((int)g_pMovieSurface + 0x10),0,
                       (uint)(UINT_009016ac != 6));
    if (iVar1 == 0) {
      g_nMoviePlaying = 1;
      g_nMoviePaused = iVar1;
      g_nMovieStopRequested = iVar1;
      strncpy(g_szMovieName,param_1,0x80);
      _DAT_008c9ff8 = timeGetTime();
      return 0;
    }
  }
  return 1;
}

/* ---- 0x00489370  Movie_Stop ---- */
void Movie_Stop(void)

{
  if (g_nMovieAvailable != 0) {
    g_nMovieStopRequested = 1;
    g_nMoviePaused = 0;
  }
  return;
}

/* ---- 0x00489390  Movie_SetFile ---- */
/* Resolves the movie name through the resource system and hands the path to the SMUSH player */

undefined * Movie_SetFile(char *param_1)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined *puVar2;
  #define local_80 (*(char (*)[128])(_frame + (0x90 - 0x80)))
  
  iVar1 = Res_GetFilePath(param_1,local_80,0x80);
  if (iVar1 != 1) {
    return (undefined *)0x0;
  }
  puVar2 = Smush_SetFile((uint)local_80);
  return puVar2;
}
#undef local_80


/* ---- 0x004893d0  FUN_004893d0 ---- */
undefined4 FUN_004893d0(int param_1,int param_2,int param_3)

{
  if ((((g_nMovieAvailable != 0) && (*(int *)((int)g_pMovieSurface + 0xc) == param_1)) &&
      (*(int *)((int)g_pMovieSurface + 0x10) == param_2)) &&
     (*(int *)((int)g_pMovieSurface + 0x24) == param_3)) {
    return 0;
  }
  return 1;
}

/* ---- 0x00489410  FUN_00489410 ---- */
bool FUN_00489410(void)

{
  return g_nMovieAvailable == 0;
}

/* ---- 0x00489420  FUN_00489420 ---- */
undefined4 FUN_00489420(undefined4 *param_1,undefined4 *param_2)

{
  if (g_nMovieAvailable == 0) {
    return 1;
  }
  Surface_Lock(g_pMovieSurface);
  param_1[3] = *(uint *)((int)g_pMovieSurface + 0x24) >> 3;
  *param_1 = *(undefined4 *)((int)g_pMovieSurface + 0x5c);
  param_1[2] = *(undefined4 *)((int)g_pMovieSurface + 0x10);
  param_1[1] = *(undefined4 *)((int)g_pMovieSurface + 0xc);
  param_1[5] = *(undefined4 *)((int)g_pMovieSurface + 0x18);
  param_2[1] = 0;
  *param_2 = 0;
  param_2[3] = *(undefined4 *)((int)g_pMovieSurface + 0x10);
  param_2[2] = *(undefined4 *)((int)g_pMovieSurface + 0xc);
  return 0;
}

/* ---- 0x004894b0  FUN_004894b0 ---- */
undefined4 FUN_004894b0(void)

{
  if (g_nMovieAvailable == 0) {
    return 1;
  }
  Surface_Unlock(g_pMovieSurface);
  return 0;
}

/* ---- 0x004894d0  FUN_004894d0 ---- */
bool FUN_004894d0(void)

{
  return g_nMovieAvailable == 0;
}

/* ---- 0x004894e0  Movie_IsPlaying ---- */
int Movie_IsPlaying(void)

{
  return g_nMoviePlaying;
}

/* ---- 0x004894f0  Movie_SetPaused ---- */
void Movie_SetPaused(int paused)

{
  g_nMoviePaused = paused;
  if (paused != 0) {
    Smush_Pause();
    return;
  }
  Smush_Resume();
  return;
}

/* ---- 0x00489510  FUN_00489510 ---- */
void FUN_00489510(void)

{
  FUN_00489520();
  FUN_00489530();
  return;
}

/* ---- 0x00489520  FUN_00489520 ---- */
void FUN_00489520(void)

{
  FUN_0048a500(&UINT_008ca0a0);
  return;
}

/* ---- 0x00489530  FUN_00489530 ---- */
void FUN_00489530(void)

{
  atexit(&LAB_00489540);
  return;
}
