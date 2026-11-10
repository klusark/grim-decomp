/* IMUSE.DLL :: imuse_dispatch.c
 * functions 0x10001fd0 .. 0x10003640 (19 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10001fd0  DpTerminate ---- */
/* Original name DpTerminate (the remaster's GrimFandango (Linux): aligned call in TrTerminate); was
   iMUSE_Dispatch__1fd0. */

undefined4 DpTerminate(void)

{
  (**(code **)(g_dwSounds_pHS + 0x24))(g_dwMemAddr);
  return 0;
}

/* ---- 0x10001ff0  DpGetDp ---- */
/* Original name DpGetDp (the remaster's GrimFandango (Linux): aligned call in TrInitialize,
   TrRestore); was iMUSE_Dispatch__1ff0. */

undefined4 * __cdecl DpGetDp(int param_1)

{
  return &g_dwDispatches + param_1 * 0x215;
}

/* ---- 0x10002010  DpSave ---- */
/* Original name DpSave (the remaster's GrimFandango (Linux): aligned call in TrSave); was
   iMUSE_Dispatch__2010. */

undefined4 __cdecl DpSave(undefined4 *param_1,uint param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_2 < 0x8540) {
    return 0xfffffffb;
  }
  puVar2 = &g_dwDispatches;
  for (iVar1 = 0x2150; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return 0x8540;
}

/* ---- 0x10002040  DpBeginRestore ---- */
/* Original name DpBeginRestore (the remaster's GrimFandango (Linux): aligned call in TrRestore);
   was iMUSE_Dispatch__2040. */

undefined4 __cdecl DpBeginRestore(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar2 = &g_dwDispatches;
  for (iVar3 = 0x2150; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  iVar3 = 0;
  if (0 < g_dwImLargeFadeCount) {
    do {
      iVar1 = iVar3 + 1;
      PTR_10024dc8[iVar3] = 0;
      iVar3 = iVar1;
    } while (iVar1 < g_dwImLargeFadeCount);
  }
  iVar3 = 0;
  if (0 < g_dwImSmallFadeCount) {
    do {
      iVar1 = iVar3 + 1;
      g_pSmallFadeFlags[iVar3] = 0;
      iVar3 = iVar1;
    } while (iVar1 < g_dwImSmallFadeCount);
  }
  puVar2 = &DAT_10024df0;
  iVar3 = 0x32;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 6;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return 0x8540;
}

/* ---- 0x100020c0  DpConcludeRestore ---- */
/* Original name DpConcludeRestore (the remaster's GrimFandango (Linux): aligned call in TrRestore);
   was iMUSE_Dispatch__20c0. */

undefined4 DpConcludeRestore(void)

{
  uint *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  
  iVar3 = 0;
  if (0 < g_dwTrackCount) {
    piVar4 = &DAT_10025abc;
    do {
      piVar4[4] = 0;
      if ((*(int *)(piVar4[-0x207] + 0xc) != 0) && (*piVar4 != 0)) {
        puVar1 = StStartStream(*(uint *)(piVar4[-0x207] + 0xc),piVar4[1],0x4000);
        *piVar4 = (int)puVar1;
        if ((puVar1 != (uint *)0x0) &&
           (StSpliceStream((undefined4 *)*piVar4,*(undefined4 *)(piVar4[-0x207] + 0xc),
                           piVar4[-0x202]), piVar4[-0x201] != 0)) {
          puVar2 = iMUSE_Dispatch__3570();
          piVar4[2] = (int)puVar2;
          if (puVar2 != (undefined4 *)0x0) {
            puVar2[3] = piVar4[-0x202];
            *(undefined4 *)(piVar4[2] + 0x10) = 0;
            *(undefined4 *)(piVar4[2] + 0x14) = 0;
          }
        }
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 0x215;
    } while (iVar3 < g_dwTrackCount);
  }
  return 0;
}

/* ---- 0x10002170  DpStartSound ---- */
/* Original name DpStartSound (the remaster's GrimFandango (Linux): aligned call in TrStartSound);
   was iMUSE_Dispatch__2170. */

undefined4 __cdecl DpStartSound(int param_1,uint param_2)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  
  piVar1 = *(int **)(param_1 + 8);
  piVar1[0x20b] = 0;
  *(undefined1 *)(piVar1 + 7) = 0;
  piVar1[6] = 0;
  piVar1[5] = 0;
  if (param_2 == 0) {
    piVar1[0x207] = 0;
  }
  else {
    puVar2 = StStartStream(*(uint *)(param_1 + 0xc),param_2,0x4000);
    piVar1[0x207] = (int)puVar2;
    if (puVar2 == (uint *)0x0) {
      return 0xffffffff;
    }
    piVar1[0x208] = param_2;
    piVar1[0x209] = 0;
    piVar1[0x20a] = 0;
  }
  iVar3 = GoToNextRegion(piVar1);
  if ((iVar3 != 0) && (iVar3 != -3)) {
    DpStopTrack(*piVar1);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x10002200  DpStopTrack ---- */
/* Original name DpStopTrack (the remaster's GrimFandango (Linux): aligned call in DpStartSound,
   TrStopTrack); was iMUSE_Dispatch__2200. */

undefined4 __cdecl DpStopTrack(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(param_1 + 8);
  if (*(undefined4 **)(iVar2 + 0x81c) != (undefined4 *)0x0) {
    StStopStream(*(undefined4 **)(iVar2 + 0x81c));
    piVar1 = (int *)(iVar2 + 0x824);
    iVar3 = *(int *)(iVar2 + 0x824);
    while (iVar3 != 0) {
      *(undefined4 *)(iVar3 + 8) = 0;
      UtRemoveFromList(piVar1,(int *)*piVar1);
      iVar3 = *piVar1;
    }
  }
  if (*(int *)(iVar2 + 0x82c) != 0) {
    iMUSE_Dispatch__3640(*(int *)(iVar2 + 0x82c));
  }
  return 0;
}

/* ---- 0x10002a00  DpPredictStreams ---- */
/* Original name DpPredictStreams (the remaster's GrimFandango (Linux): aligned call in
   StProcessStreams, StQueryStream, TrIntHandler); was iMUSE_Dispatch__2a00. */

void DpPredictStreams(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = &g_dwDispatches;
  ImWaveHalt();
  iVar2 = 0;
  if (0 < g_dwTrackCount) {
    do {
      if (((*(int *)(*piVar1 + 0xc) != 0) && (piVar1[0x207] != 0)) && (piVar1[0x209] != 0)) {
        PredictStream(piVar1);
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 0x215;
    } while (iVar2 < g_dwTrackCount);
  }
  ImWaveProceed();
  return;
}

/* ---- 0x10002fe0  iMUSE_Dispatch__2fe0 ---- */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

int __cdecl iMUSE_Dispatch__2fe0(undefined4 *param_1,undefined4 *param_2)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  int *piVar8;
  undefined4 *puVar9;
  
  iVar3 = iMUSE_stream__b810((undefined1 *)param_1);
  if (iVar3 != 0x4d415020) {
    return -1;
  }
  iVar3 = iMUSE_stream__b810((undefined1 *)(param_1 + 1));
  uVar6 = iVar3 + 8;
  if (uVar6 < 0x801) {
    puVar9 = param_2;
    for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar9 = *param_1;
      param_1 = param_1 + 1;
      puVar9 = puVar9 + 1;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined1 *)puVar9 = *(undefined1 *)param_1;
      param_1 = (undefined4 *)((int)param_1 + 1);
      puVar9 = (undefined4 *)((int)puVar9 + 1);
    }
    uVar4 = iMUSE_stream__b810((undefined1 *)param_2);
    *param_2 = uVar4;
    uVar4 = iMUSE_stream__b810((undefined1 *)(param_2 + 1));
    param_2[1] = uVar4;
    piVar8 = param_2 + 2;
    piVar1 = (int *)(iVar3 + 8 + (int)param_2);
    while (piVar8 < piVar1) {
      iVar3 = iMUSE_stream__b810((undefined1 *)piVar8);
      *piVar8 = iVar3;
      uVar6 = iMUSE_stream__b810((undefined1 *)(piVar8 + 1));
      piVar8[1] = uVar6;
      piVar7 = piVar8 + 2;
      if (iVar3 == 0x54455854) {
        iVar3 = iMUSE_stream__b810((undefined1 *)piVar7);
        *piVar7 = iVar3;
        piVar7 = piVar8 + 3;
        piVar8 = (int *)((int)piVar8 + 0xd);
        cVar2 = (char)*piVar7;
        while (cVar2 != '\0') {
          iVar3 = *piVar8;
          piVar8 = (int *)((int)piVar8 + 1);
          cVar2 = (char)iVar3;
        }
      }
      else {
        piVar8 = piVar7;
        for (uVar6 = uVar6 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          iVar3 = iMUSE_stream__b810((undefined1 *)piVar8);
          *piVar8 = iVar3;
          piVar8 = piVar8 + 1;
        }
      }
    }
    return -(uint)(piVar8 != piVar1);
  }
  return -1;
}

/* ---- 0x100030d0  iMUSE_Dispatch__30d0 ---- */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

uint __cdecl iMUSE_Dispatch__30d0(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  if (param_3 == 0) {
    uVar1 = param_1 + 8;
    do {
      if (*(int *)(uVar1 + 8) == param_2) {
        return uVar1;
      }
      uVar1 = uVar1 + 8 + *(int *)(uVar1 + 4);
    } while (uVar1 < (uint)(*(int *)(param_1 + 4) + 8 + param_1));
  }
  else {
    uVar1 = *(int *)(param_3 + 4) + 8 + param_3;
    if (uVar1 < (uint)(*(int *)(param_1 + 4) + 8 + param_1)) {
      return uVar1 & (*(int *)(uVar1 + 8) != param_2) - 1;
    }
  }
  return 0;
}

/* ---- 0x10003130  PredictStream ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name PredictStream (the remaster's GrimFandango (Linux): aligned call in
   DpPredictStreams, DpProcessTrack); was iMUSE_Dispatch__3130. */

void __cdecl PredictStream(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  if ((param_1[0x207] != 0) && (param_1[0x209] != 0)) {
    iVar5 = 0;
    iVar2 = 0;
    for (iVar3 = param_1[0x209]; iVar3 != 0; iVar3 = *(int *)(iVar3 + 4)) {
      iVar5 = iVar5 + *(int *)(iVar3 + 0x10);
      iVar2 = iVar3;
    }
    iVar3 = StGetValidSize(param_1[0x207]);
    *(int *)(iVar2 + 0x10) = *(int *)(iVar2 + 0x10) + (iVar3 - iVar5);
    _g_dwPredictStream_jumpHook = *(undefined4 *)(*param_1 + 0x38);
    for (puVar1 = (undefined4 *)param_1[0x209]; puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)puVar1[1]) {
      if (puVar1[5] == 0) {
        piVar4 = iMUSE_Dispatch__31d0(param_1 + 7,(int)puVar1,(int *)&g_dwPredictStream_jumpHook);
        if (piVar4 == (int *)0x0) {
          iMUSE_Dispatch__3430(param_1,(int)puVar1);
        }
        else {
          PrepareToJump(param_1,puVar1,(int)piVar4,0);
        }
      }
    }
  }
  return;
}

/* ---- 0x100031d0  iMUSE_Dispatch__31d0 ---- */
/* WARNING: Removing unreachable block (ram,0x10003234) */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

int * __cdecl iMUSE_Dispatch__31d0(int *param_1,int param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  uVar1 = *(uint *)(param_2 + 0xc);
  iVar2 = param_1[1];
  iVar3 = *(int *)(param_2 + 0x10);
  piVar5 = param_1 + 2;
  while( true ) {
    if ((int *)(iVar2 + 8 + (int)param_1) <= piVar5) {
      return (int *)0x0;
    }
    if ((((*piVar5 == 0x4a554d50) && (uVar1 < (uint)piVar5[2])) &&
        ((uint)piVar5[2] <= iVar3 + uVar1)) &&
       (iVar4 = iMUSE_stream__b840(param_3,piVar5[4]), iVar4 == 0)) break;
    piVar5 = (int *)((int)piVar5 + piVar5[1] + 8);
  }
  return piVar5;
}

/* ---- 0x10003250  PrepareToJump ---- */
/* Original name PrepareToJump (the remaster's GrimFandango (Linux): aligned call in GoToNextRegion,
   PredictStream); was iMUSE_Dispatch__3250. */

void __cdecl PrepareToJump(int *param_1,undefined4 *param_2,int param_3,int param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  #define local_4 (*(undefined4 **)(_frame + (0x20 - 0x4)))
  
  local_4 = (undefined4 *)0x0;
  if ((param_2[3] + param_2[4] == *(int *)(param_3 + 8)) && (iVar5 = param_2[1], iVar5 != 0)) {
    if (*(int *)(iVar5 + 0x14) == 0) {
      if (*(int *)(iVar5 + 0xc) == *(int *)(param_3 + 0xc)) {
        return;
      }
    }
    else if (((*(int *)(iVar5 + 0xc) == *(int *)(param_3 + 8)) && (*(int *)(iVar5 + 4) != 0)) &&
            (*(int *)(*(int *)(iVar5 + 4) + 0xc) == *(int *)(param_3 + 0xc))) {
      return;
    }
  }
  g_dwPrepareToJump_fadeSize =
       ((uint)(*(int *)(param_3 + 0x14) * param_1[2]) / 1000) * param_1[1] * param_1[3] >> 3;
  if ((param_4 != 0) ||
     ((g_dwPrepareToJump_fadeSize - param_2[3]) + *(int *)(param_3 + 8) <= (uint)param_2[4])) {
    uVar6 = (param_2[3] - *(int *)(param_3 + 8)) + param_2[4];
    if (uVar6 <= g_dwPrepareToJump_fadeSize) {
      g_dwPrepareToJump_fadeSize = uVar6;
    }
    g_dwPrepareToJump_fadeSize =
         g_dwPrepareToJump_fadeSize -
         ((param_1[1] >> 3) * param_1[3] - 1U & g_dwPrepareToJump_fadeSize);
    if ((*(uint *)(param_3 + 8) < 2000) && (*(uint *)(param_3 + 8) < *(uint *)(param_3 + 0xc))) {
      g_dwPrepareToJump_fadeSize = 0;
    }
    if (param_1[0x20d] != 0) {
      g_dwPrepareToJump_fadeSize = 0;
    }
    if (((g_dwPrepareToJump_fadeSize == 0) ||
        (local_4 = iMUSE_Dispatch__3570(), local_4 != (undefined4 *)0x0)) &&
       (puVar4 = iMUSE_Dispatch__3570(), puVar4 != (undefined4 *)0x0)) {
      iVar5 = *(int *)(param_3 + 8) - param_2[3];
      param_2[4] = iVar5;
      uVar6 = g_dwPrepareToJump_fadeSize + iVar5;
      for (puVar2 = (undefined4 *)param_1[0x209]; puVar2 != param_2;
          puVar2 = (undefined4 *)puVar2[1]) {
        uVar6 = uVar6 + puVar2[4];
      }
      StEraseFromMid(param_1[0x207],uVar6);
      piVar1 = param_2 + 1;
      iVar5 = param_2[1];
      while (iVar5 != 0) {
        *(undefined4 *)(iVar5 + 8) = 0;
        UtRemoveFromList(piVar1,(int *)*piVar1);
        iVar5 = *piVar1;
      }
      StSpliceStream((undefined4 *)param_1[0x207],*(undefined4 *)(*param_1 + 0xc),
                     *(undefined4 *)(param_3 + 0xc));
      if (g_dwPrepareToJump_fadeSize != 0) {
        *piVar1 = (int)local_4;
        *local_4 = param_2;
        local_4[1] = 0;
        local_4[3] = *(undefined4 *)(param_3 + 8);
        local_4[4] = g_dwPrepareToJump_fadeSize;
        local_4[5] = 1;
        param_2 = local_4;
      }
      param_2[1] = puVar4;
      *puVar4 = param_2;
      puVar4[1] = 0;
      uVar3 = *(undefined4 *)(param_3 + 0xc);
      puVar4[4] = 0;
      puVar4[3] = uVar3;
      puVar4[5] = 0;
    }
  }
  return;
}
#undef local_4


/* ---- 0x10003430  iMUSE_Dispatch__3430 ---- */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

void __cdecl iMUSE_Dispatch__3430(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  
  piVar1 = (int *)(param_2 + 4);
  if (*(int *)(param_2 + 4) != 0) {
    uVar3 = *(uint *)(param_2 + 0x10);
    for (iVar2 = param_1[0x209]; iVar2 != param_2; iVar2 = *(int *)(iVar2 + 4)) {
      uVar3 = uVar3 + *(int *)(iVar2 + 0x10);
    }
    StEraseFromMid(param_1[0x207],uVar3);
    iVar2 = *piVar1;
    while (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 8) = 0;
      UtRemoveFromList(piVar1,(int *)*piVar1);
      iVar2 = *piVar1;
    }
    StSpliceStream((undefined4 *)param_1[0x207],*(undefined4 *)(*param_1 + 0xc),
                   *(int *)(param_2 + 0xc) + *(int *)(param_2 + 0x10));
  }
  return;
}

/* ---- 0x100034b0  iMUSE_Dispatch__34b0 ---- */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

int __cdecl iMUSE_Dispatch__34b0(int *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(*param_1 + 0x20);
  if (param_1[0x214] == 0) {
    uVar2 = param_1[0x20d];
    if (uVar2 < 2) {
      uVar2 = 2;
    }
    param_1[0x214] = -(int)(0x7f0000 / (ulonglong)uVar2);
  }
  return (0x80 - (param_1[0x213] >> 0x10)) * iVar1 >> 7;
}

/* ---- 0x10003510  iMUSE_Dispatch__3510 ---- */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

int __cdecl iMUSE_Dispatch__3510(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = param_1[0x213];
  iVar2 = *(int *)(*param_1 + 0x20);
  iVar3 = iVar1 + param_1[0x214] * param_2;
  param_1[0x213] = iVar3;
  if (iVar3 < 0) {
    param_1[0x213] = 0;
  }
  if (0x7f0000 < param_1[0x213]) {
    param_1[0x213] = 0x7f0000;
  }
  return iVar2 * ((iVar1 >> 0x10) + 1) >> 7;
}

/* ---- 0x10003570  iMUSE_Dispatch__3570 ---- */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

undefined4 * iMUSE_Dispatch__3570(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = &g_dwStreamZones;
  iVar2 = 0;
  do {
    if (puVar1[2] == 0) {
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1[2] = 1;
      puVar1[3] = 0;
      puVar1[4] = 0;
      puVar1[5] = 0;
      return puVar1;
    }
    puVar1 = puVar1 + 6;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x32);
  return (undefined4 *)0x0;
}

/* ---- 0x100035a0  iMUSE_Dispatch__35a0 ---- */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

int __cdecl iMUSE_Dispatch__35a0(uint *param_1)

{
  int iVar1;
  int *piVar2;
  
  if (g_dwImLargeFadeSize < *param_1) {
    *param_1 = g_dwImLargeFadeSize;
  }
  if (g_dwImSmallFadeSize < *param_1) {
    iVar1 = 0;
    piVar2 = PTR_10024dc8;
    if (0 < g_dwImLargeFadeCount) {
      do {
        if (*piVar2 == 0) {
          PTR_10024dc8[iVar1] = 1;
          return iVar1 * g_dwImLargeFadeSize + g_dwLargeFadeBufs;
        }
        iVar1 = iVar1 + 1;
        piVar2 = piVar2 + 1;
      } while (iVar1 < g_dwImLargeFadeCount);
    }
    *param_1 = g_dwImSmallFadeSize;
  }
  iVar1 = 0;
  piVar2 = g_pSmallFadeFlags;
  if (g_dwImSmallFadeCount < 1) {
    return 0;
  }
  do {
    if (*piVar2 == 0) {
      g_pSmallFadeFlags[iVar1] = 1;
      return iVar1 * g_dwImSmallFadeSize + g_dwSmallFadeBufs;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < g_dwImSmallFadeCount);
  return 0;
}

/* ---- 0x10003640  iMUSE_Dispatch__3640 ---- */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

void __cdecl iMUSE_Dispatch__3640(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = g_dwLargeFadeBufs;
  if (0 < g_dwImLargeFadeCount) {
    do {
      if (param_1 == iVar2) {
        PTR_10024dc8[iVar1] = 0;
        return;
      }
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + g_dwImLargeFadeSize;
    } while (iVar1 < g_dwImLargeFadeCount);
  }
  iVar1 = 0;
  iVar2 = g_dwSmallFadeBufs;
  if (0 < g_dwImSmallFadeCount) {
    while (param_1 != iVar2) {
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + g_dwImSmallFadeSize;
      if (g_dwImSmallFadeCount <= iVar1) {
        return;
      }
    }
    g_pSmallFadeFlags[iVar1] = 0;
  }
  return;
}
