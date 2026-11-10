/* GRIMFANDANGO.EXE :: smush.c
 * functions 0x004bd500 .. 0x004bdf00 (9 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004bd500  SmushPlay_Pause ---- */
/* Original name SmushPlay_Pause (the remaster's GrimFandango (Linux): aligned call in
   sputSmush_Pause); was Smush_Pause. */

undefined4 SmushPlay_Pause(void)

{
  if (g_dwMovieIsPlaying != 0) {
    (**(code **)(g_dwAnimplay_services + 0x24))(g_dwAh,1);
  }
  return 0;
}

/* ---- 0x004bd520  SmushPlay_Resume ---- */
/* Original name SmushPlay_Resume (the remaster's GrimFandango (Linux): aligned call in
   sputSmush_Pause); was Smush_Resume. */

undefined4 SmushPlay_Resume(void)

{
  if (g_dwMovieIsPlaying != 0) {
    (**(code **)(g_dwAnimplay_services + 0x24))(g_dwAh,0);
  }
  return 0;
}

/* ---- 0x004bd560  SmushPlay_SysConfigureColorLookup ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name SmushPlay_SysConfigureColorLookup (the remaster's GrimFandango (Linux): aligned
   call in sputSmush_Periodic); was Smush_Idle. */

void SmushPlay_SysConfigureColorLookup(undefined4 param_1)

{
  _g_pSmushplay_UserLookup = param_1;
  return;
}

/* ---- 0x004bd570  Smush_Open ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl
Smush_Open(char *name,int flags,int bufferSize,int x,int y,int w,int h,int a,int sixteenBit)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  undefined4 *puVar8;
  char *pcVar9;
  char *pcVar10;
  uint *puVar11;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(undefined4 (*)[6])(_frame + (0x30 - 0x18)))
  
  bVar2 = false;
  if (UINT_008d1098 == 0) {
    return 1;
  }
  puVar8 = local_18;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  iVar4 = (*(code *)*g_pSmushPlay_file_services)(name,&DAT_004ddb18);
  if (iVar4 != 0) {
    uVar5 = 0xffffffff;
    pcVar9 = name;
    do {
      pcVar10 = pcVar9;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar10 = pcVar9 + 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar10;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    puVar7 = (uint *)(pcVar10 + -uVar5);
    puVar11 = &g_dwCurFileName;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar11 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar11 = puVar11 + 1;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(char *)puVar11 = (char)*puVar7;
      puVar7 = (uint *)((int)puVar7 + 1);
      puVar11 = (uint *)((int)puVar11 + 1);
    }
    (*(code *)g_pSmushPlay_file_services[5])(iVar4,a,1);
    iVar3 = smushplay_GetInfo(iVar4,&DAT_008d1208);
    if (iVar3 == 0) {
      (*(code *)g_pSmushPlay_file_services[1])(iVar4);
      _DAT_008d166c = 5;
      _DAT_008d1670 = 6 - (uint)(sixteenBit != 0);
      _DAT_008d1674 = 5;
      _DAT_008d167c = 5;
      _DAT_008d1678 = 0xb - (uint)(sixteenBit != 0);
      _DAT_008d1684 = 3;
      _DAT_008d168c = 3;
      _DAT_008d1688 = (sixteenBit != 0) + 2;
      _g_aFakeBM = 0;
      _DAT_008d164c = 0x280;
      _DAT_008d1650 = 0x1e0;
      _DAT_008d1654 = 2;
      _DAT_008d1658 = 0x10;
      _DAT_008d165c = 0x500;
      _DAT_008d1660 = 0;
      _DAT_008d1664 = 0;
      _DAT_008d1668 = 1;
      _DAT_008d1680 = 0;
      iVar4 = (*(code *)UINT_008d1098)(w,h,0x10,sixteenBit);
      if (iVar4 == 0) {
        _DAT_008d1090 = flags & 0xfffffff;
        bVar2 = true;
        iVar4 = (**(code **)(g_dwAnimplay_services + 4))
                          (&g_dwAh,name,0xf,UINT_008d121a + 500000,UINT_008d121a + 10000,0x600d);
        if (iVar4 == 0) {
          if (x < 0) {
            UINT_008d11e0 = (uint)DAT_008d120c;
          }
          else {
            UINT_008d11e0 = x;
          }
          if (y < 0) {
            UINT_008d11e4 = (uint)DAT_008d120e;
          }
          else {
            UINT_008d11e4 = y;
          }
          UINT_008d11e8 = (uint)DAT_008d1210;
          UINT_008d11ec = (uint)DAT_008d1212;
          if (UINT_008d10a8 != 0) {
            (*(code *)UINT_008d10a8)();
          }
          g_dwMovieIsPlaying = 1;
          return 0;
        }
      }
    }
    else {
      (*(code *)g_pSmushPlay_file_services[1])();
    }
  }
  if (bVar2) {
    (*(code *)UINT_008d109c)();
  }
  return 1;
}
#undef local_18
#undef local_1c


/* ---- 0x004bd930  SmushPlay_StopMovie ---- */
/* Original name SmushPlay_StopMovie (the remaster's GrimFandango (Linux): aligned call in
   sputSmush_Periodic, sputSmush_StartMovie); was Smush_Close. */

undefined4 SmushPlay_StopMovie(void)

{
  if (g_dwMovieIsPlaying != 0) {
    (**(code **)(g_dwAnimplay_services + 0x14))(&g_dwAh);
    (**(code **)(g_dwSmushPlay_sound_services + 0x10))();
    g_dwSmush_pInternalBitmap = 0;
  }
  g_dwMovieIsPlaying = 0;
  (*(code *)UINT_008d109c)();
  return 0;
}

/* ---- 0x004bd970  SmushPlay_UpdateMovie ---- */
/* Original name SmushPlay_UpdateMovie (the remaster's GrimFandango (Linux): aligned call in
   sputSmush_Periodic); was Smush_Advance. */

int __cdecl SmushPlay_UpdateMovie(int *outDone)

{
  unsigned char _frame[0x480] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_46c (*(uint *)(_frame + (0x480 - 0x46c)))
  #define local_468 (*(uint *)(_frame + (0x480 - 0x468)))
  #define auStack_464 (*(undefined1 (*)[16])(_frame + (0x480 - 0x464)))
  #define auStack_454 (*(undefined1 (*)[84])(_frame + (0x480 - 0x454)))
  #define local_400 (*(undefined1 (*)[1024])(_frame + (0x480 - 0x400)))
  
  local_46c = 0;
  local_468 = 0;
  fob_flobdec_blocky16_config(1,FUN_004bdad0,0);
  iVar1 = (**(code **)(g_dwAnimplay_services + 0xc))
                    (g_dwAh,&g_aFakeBM,0,0,0,local_400,&local_468,&local_46c,1,0);
  (*(code *)UINT_008d10a0)(auStack_454,auStack_464);
  Insane_PrepareFrame(auStack_454,g_dwSmush_pInternalBitmap,auStack_464);
  (*(code *)UINT_008d10a4)(auStack_454,auStack_464);
  if ((iVar1 < 0) || (iVar1 == 4)) {
    (**(code **)(g_dwAnimplay_services + 0x14))(&g_dwAh);
    g_dwSmush_pInternalBitmap = 0;
    if ((DAT_008d1090 & 0x10) == 0) {
      *outDone = 1;
      g_dwMovieIsPlaying = 0;
    }
    else {
      *outDone = 0;
      if (UINT_008d1216 == 0) {
        iVar1 = 0xf;
      }
      else {
        iVar1 = ((int)UINT_008d1216 / 2 + 1000000) / (int)UINT_008d1216;
      }
      (**(code **)(g_dwAnimplay_services + 4))
                (&g_dwAh,&g_dwCurFileName,iVar1,UINT_008d121a + 500000,UINT_008d121a + 10000,0x600d)
      ;
      g_dwMovieIsPlaying = 1;
    }
  }
  else {
    *outDone = 0;
    g_dwMovieIsPlaying = 1;
  }
  fob_flobdec_blocky16_config(1,0,0);
  return 0;
}
#undef auStack_454
#undef auStack_464
#undef local_400
#undef local_468
#undef local_46c


/* ---- 0x004bde90  SmushPlay_SetTranslationTable ---- */
/* Original name SmushPlay_SetTranslationTable (the remaster's GrimFandango (Linux): aligned call in
   sputSmush_Periodic, sputSmush_StartMovie); was Smush_SetColorTable. */

void SmushPlay_SetTranslationTable(uint param_1)

{
  g_dwSmushPlay_TranslationTable = param_1;
  return;
}

/* ---- 0x004bdea0  SmushPlay_GetFrameRect ---- */
/* Original name SmushPlay_GetFrameRect (the remaster's GrimFandango (Linux): aligned call in
   sputSmush_Periodic); was Smush_GetFrameRect. */

undefined4 SmushPlay_GetFrameRect(uint *param_1,uint *param_2)

{
  if (param_1 != (uint *)0x0) {
    *param_1 = UINT_008d11e0;
    param_1[1] = UINT_008d11e4;
    param_1[2] = UINT_008d11e8;
    param_1[3] = UINT_008d11ec;
  }
  if (param_2 != (uint *)0x0) {
    *param_2 = UINT_008d1638;
    param_2[1] = UINT_008d163c;
    param_2[2] = UINT_008d1640;
    param_2[3] = UINT_008d1644;
  }
  return 0;
}

/* ---- 0x004bdf00  SmushPlay_GetMovieLength ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Opens a movie file, reads its header and returns the movie length in milliseconds (16 bit header
   field times 66.67); 0 if it cannot be opened Original name SmushPlay_GetMovieLength (the
   remaster's GrimFandango (Linux): aligned call in sputSmush_GetMovieLength); was
   Smush_GetLengthMs. */

int __cdecl SmushPlay_GetMovieLength(char *path)

{
  unsigned char _frame[0x440] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 unaff_ESI;
  longlong lVar2;
  #define auStack_428 (*(undefined1 (*)[2])(_frame + (0x440 - 0x428)))
  #define sStack_426 (*(short *)(_frame + (0x440 - 0x426)))
  
  iVar1 = (*(code *)*g_pSmushPlay_file_services)(path,&DAT_004dda54);
  if (iVar1 == 0) {
    return 0;
  }
  smushplay_GetInfo(iVar1,auStack_428);
  (*(code *)g_pSmushPlay_file_services[1])(iVar1);
  lVar2 = _ftol((double)CONCAT44((int)sStack_426,unaff_ESI));
  return (int)lVar2;
}
#undef auStack_428
#undef sStack_426

#endif

