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

undefined4 * __cdecl DpGetDp(int index)

{
  return &g_dwDispatches + index * 0x215;
}

/* ---- 0x10002010  DpSave ---- */
/* Original name DpSave (the remaster's GrimFandango (Linux): aligned call in TrSave); was
   iMUSE_Dispatch__2010. */

undefined4 __cdecl DpSave(undefined4 *buf,uint size)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (size < 0x8540) {
    return 0xfffffffb;
  }
  puVar2 = &g_dwDispatches;
  for (iVar1 = 0x2150; iVar1 != 0; iVar1 = iVar1 + -1) {
    *buf = *puVar2;
    puVar2 = puVar2 + 1;
    buf = buf + 1;
  }
  return 0x8540;
}

/* ---- 0x10002040  DpBeginRestore ---- */
/* Original name DpBeginRestore (the remaster's GrimFandango (Linux): aligned call in TrRestore);
   was iMUSE_Dispatch__2040. */

undefined4 __cdecl DpBeginRestore(undefined4 *buf)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar2 = &g_dwDispatches;
  for (iVar3 = 0x2150; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = *buf;
    buf = buf + 1;
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

undefined4 __cdecl DpStartSound(int track,uint group)

{
  int *dp;
  uint *puVar1;
  int iVar2;
  
  dp = *(int **)(track + 8);
  dp[0x20b] = 0;
  *(undefined1 *)(dp + 7) = 0;
  dp[6] = 0;
  dp[5] = 0;
  if (group == 0) {
    dp[0x207] = 0;
  }
  else {
    puVar1 = StStartStream(*(uint *)(track + 0xc),group,0x4000);
    dp[0x207] = (int)puVar1;
    if (puVar1 == (uint *)0x0) {
      return 0xffffffff;
    }
    dp[0x208] = group;
    dp[0x209] = 0;
    dp[0x20a] = 0;
  }
  iVar2 = GoToNextRegion(dp);
  if ((iVar2 != 0) && (iVar2 != -3)) {
    DpStopTrack(*dp);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x10002200  DpStopTrack ---- */
/* Original name DpStopTrack (the remaster's GrimFandango (Linux): aligned call in DpStartSound,
   TrStopTrack); was iMUSE_Dispatch__2200. */

undefined4 __cdecl DpStopTrack(int track)

{
  int *head;
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(track + 8);
  if (*(undefined4 **)(iVar1 + 0x81c) != (undefined4 *)0x0) {
    StStopStream(*(undefined4 **)(iVar1 + 0x81c));
    head = (int *)(iVar1 + 0x824);
    iVar2 = *(int *)(iVar1 + 0x824);
    while (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 8) = 0;
      UtRemoveFromList(head,(int *)*head);
      iVar2 = *head;
    }
  }
  if (*(int *)(iVar1 + 0x82c) != 0) {
    iMUSE_Dispatch__3640(*(int *)(iVar1 + 0x82c));
  }
  return 0;
}

/* ---- 0x10002a00  DpPredictStreams ---- */
/* Original name DpPredictStreams (the remaster's GrimFandango (Linux): aligned call in
   StProcessStreams, StQueryStream, TrIntHandler); was iMUSE_Dispatch__2a00. */

void DpPredictStreams(void)

{
  int *dp;
  int iVar1;
  
  dp = &g_dwDispatches;
  ImWaveHalt();
  iVar1 = 0;
  if (0 < g_dwTrackCount) {
    do {
      if (((*(int *)(*dp + 0xc) != 0) && (dp[0x207] != 0)) && (dp[0x209] != 0)) {
        PredictStream(dp);
      }
      iVar1 = iVar1 + 1;
      dp = dp + 0x215;
    } while (iVar1 < g_dwTrackCount);
  }
  ImWaveProceed();
  return;
}

/* ---- 0x10002fe0  ConvertMap ---- */
/* Original name ConvertMap (the remaster's GrimFandango (Linux): same body ('MAP ' tag 0x4d415020
   checked, size + 8 at most 0x800 copied, every record converted with UtReadLongHilo, 'TEXT'
   records skipped as strings); called by the region fetch (GoToNextRegion in the remaster, which
   inlined v1.01's Im_DispatchFetchNext)); was iMUSE_Dispatch__2fe0. */

int __cdecl ConvertMap(undefined4 *src,undefined4 *dst)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  int *p;
  undefined4 *puVar8;
  
  iVar3 = UtReadLongHilo((undefined1 *)src);
  if (iVar3 != 0x4d415020) {
    return -1;
  }
  iVar3 = UtReadLongHilo((undefined1 *)(src + 1));
  uVar6 = iVar3 + 8;
  if (uVar6 < 0x801) {
    puVar8 = dst;
    for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar8 = *src;
      src = src + 1;
      puVar8 = puVar8 + 1;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined1 *)puVar8 = *(undefined1 *)src;
      src = (undefined4 *)((int)src + 1);
      puVar8 = (undefined4 *)((int)puVar8 + 1);
    }
    uVar4 = UtReadLongHilo((undefined1 *)dst);
    *dst = uVar4;
    uVar4 = UtReadLongHilo((undefined1 *)(dst + 1));
    dst[1] = uVar4;
    p = dst + 2;
    piVar1 = (int *)(iVar3 + 8 + (int)dst);
    while (p < piVar1) {
      iVar3 = UtReadLongHilo((undefined1 *)p);
      *p = iVar3;
      uVar6 = UtReadLongHilo((undefined1 *)(p + 1));
      p[1] = uVar6;
      piVar7 = p + 2;
      if (iVar3 == 0x54455854) {
        iVar3 = UtReadLongHilo((undefined1 *)piVar7);
        *piVar7 = iVar3;
        piVar7 = p + 3;
        p = (int *)((int)p + 0xd);
        cVar2 = (char)*piVar7;
        while (cVar2 != '\0') {
          iVar3 = *p;
          p = (int *)((int)p + 1);
          cVar2 = (char)iVar3;
        }
      }
      else {
        p = piVar7;
        for (uVar6 = uVar6 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          iVar3 = UtReadLongHilo((undefined1 *)p);
          *p = iVar3;
          p = p + 1;
        }
      }
    }
    return -(uint)(p != piVar1);
  }
  return -1;
}

/* ---- 0x100030d0  iMUSE_Dispatch__30d0 ---- */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

uint __cdecl iMUSE_Dispatch__30d0(int map,int id,int prev)

{
  uint uVar1;
  
  if (prev == 0) {
    uVar1 = map + 8;
    do {
      if (*(int *)(uVar1 + 8) == id) {
        return uVar1;
      }
      uVar1 = uVar1 + 8 + *(int *)(uVar1 + 4);
    } while (uVar1 < (uint)(*(int *)(map + 4) + 8 + map));
  }
  else {
    uVar1 = *(int *)(prev + 4) + 8 + prev;
    if (uVar1 < (uint)(*(int *)(map + 4) + 8 + map)) {
      return uVar1 & (*(int *)(uVar1 + 8) != id) - 1;
    }
  }
  return 0;
}

/* ---- 0x10003130  PredictStream ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name PredictStream (the remaster's GrimFandango (Linux): aligned call in
   DpPredictStreams, DpProcessTrack); was iMUSE_Dispatch__3130. */

void __cdecl PredictStream(int *dp)

{
  undefined4 *region;
  int iVar1;
  int iVar2;
  int *jump;
  int iVar3;
  
  if ((dp[0x207] != 0) && (dp[0x209] != 0)) {
    iVar3 = 0;
    iVar1 = 0;
    for (iVar2 = dp[0x209]; iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
      iVar3 = iVar3 + *(int *)(iVar2 + 0x10);
      iVar1 = iVar2;
    }
    iVar2 = StGetValidSize(dp[0x207]);
    *(int *)(iVar1 + 0x10) = *(int *)(iVar1 + 0x10) + (iVar2 - iVar3);
    _g_dwPredictStream_jumpHook = *(undefined4 *)(*dp + 0x38);
    for (region = (undefined4 *)dp[0x209]; region != (undefined4 *)0x0;
        region = (undefined4 *)region[1]) {
      if (region[5] == 0) {
        jump = iMUSE_Dispatch__31d0(dp + 7,(int)region,(int *)&g_dwPredictStream_jumpHook);
        if (jump == (int *)0x0) {
          iMUSE_Dispatch__3430(dp,(int)region);
        }
        else {
          PrepareToJump(dp,region,(int)jump,0);
        }
      }
    }
  }
  return;
}

/* ---- 0x100031d0  iMUSE_Dispatch__31d0 ---- */
/* WARNING: Removing unreachable block (ram,0x10003234) */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

int * __cdecl iMUSE_Dispatch__31d0(int *map,int region,int *predictStream_jumpHook)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  uVar1 = *(uint *)(region + 0xc);
  iVar2 = map[1];
  iVar3 = *(int *)(region + 0x10);
  piVar5 = map + 2;
  while( true ) {
    if ((int *)(iVar2 + 8 + (int)map) <= piVar5) {
      return (int *)0x0;
    }
    if ((((*piVar5 == 0x4a554d50) && (uVar1 < (uint)piVar5[2])) &&
        ((uint)piVar5[2] <= iVar3 + uVar1)) &&
       (iVar4 = UtCheckHook(predictStream_jumpHook,piVar5[4]), iVar4 == 0)) break;
    piVar5 = (int *)((int)piVar5 + piVar5[1] + 8);
  }
  return piVar5;
}

/* ---- 0x10003250  PrepareToJump ---- */
/* Original name PrepareToJump (the remaster's GrimFandango (Linux): aligned call in GoToNextRegion,
   PredictStream); was iMUSE_Dispatch__3250. */

void __cdecl PrepareToJump(int *format,undefined4 *region,int jump,int now)

{
  int *head;
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined4 *local_4;
  
  local_4 = (undefined4 *)0x0;
  if ((region[3] + region[4] == *(int *)(jump + 8)) && (iVar4 = region[1], iVar4 != 0)) {
    if (*(int *)(iVar4 + 0x14) == 0) {
      if (*(int *)(iVar4 + 0xc) == *(int *)(jump + 0xc)) {
        return;
      }
    }
    else if (((*(int *)(iVar4 + 0xc) == *(int *)(jump + 8)) && (*(int *)(iVar4 + 4) != 0)) &&
            (*(int *)(*(int *)(iVar4 + 4) + 0xc) == *(int *)(jump + 0xc))) {
      return;
    }
  }
  g_dwPrepareToJump_fadeSize =
       ((uint)(*(int *)(jump + 0x14) * format[2]) / 1000) * format[1] * format[3] >> 3;
  if ((now != 0) ||
     ((g_dwPrepareToJump_fadeSize - region[3]) + *(int *)(jump + 8) <= (uint)region[4])) {
    uVar5 = (region[3] - *(int *)(jump + 8)) + region[4];
    if (uVar5 <= g_dwPrepareToJump_fadeSize) {
      g_dwPrepareToJump_fadeSize = uVar5;
    }
    g_dwPrepareToJump_fadeSize =
         g_dwPrepareToJump_fadeSize -
         ((format[1] >> 3) * format[3] - 1U & g_dwPrepareToJump_fadeSize);
    if ((*(uint *)(jump + 8) < 2000) && (*(uint *)(jump + 8) < *(uint *)(jump + 0xc))) {
      g_dwPrepareToJump_fadeSize = 0;
    }
    if (format[0x20d] != 0) {
      g_dwPrepareToJump_fadeSize = 0;
    }
    if (((g_dwPrepareToJump_fadeSize == 0) ||
        (local_4 = iMUSE_Dispatch__3570(), local_4 != (undefined4 *)0x0)) &&
       (puVar3 = iMUSE_Dispatch__3570(), puVar3 != (undefined4 *)0x0)) {
      iVar4 = *(int *)(jump + 8) - region[3];
      region[4] = iVar4;
      uVar5 = g_dwPrepareToJump_fadeSize + iVar4;
      for (puVar1 = (undefined4 *)format[0x209]; puVar1 != region; puVar1 = (undefined4 *)puVar1[1])
      {
        uVar5 = uVar5 + puVar1[4];
      }
      StEraseFromMid(format[0x207],uVar5);
      head = region + 1;
      iVar4 = region[1];
      while (iVar4 != 0) {
        *(undefined4 *)(iVar4 + 8) = 0;
        UtRemoveFromList(head,(int *)*head);
        iVar4 = *head;
      }
      StSpliceStream((undefined4 *)format[0x207],*(undefined4 *)(*format + 0xc),
                     *(undefined4 *)(jump + 0xc));
      if (g_dwPrepareToJump_fadeSize != 0) {
        *head = (int)local_4;
        *local_4 = region;
        local_4[1] = 0;
        local_4[3] = *(undefined4 *)(jump + 8);
        local_4[4] = g_dwPrepareToJump_fadeSize;
        local_4[5] = 1;
        region = local_4;
      }
      region[1] = puVar3;
      *puVar3 = region;
      puVar3[1] = 0;
      uVar2 = *(undefined4 *)(jump + 0xc);
      puVar3[4] = 0;
      puVar3[3] = uVar2;
      puVar3[5] = 0;
    }
  }
  return;
}

/* ---- 0x10003430  iMUSE_Dispatch__3430 ---- */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

void __cdecl iMUSE_Dispatch__3430(int *dispatch,int region)

{
  int *head;
  int iVar1;
  uint offset;
  
  head = (int *)(region + 4);
  if (*(int *)(region + 4) != 0) {
    offset = *(uint *)(region + 0x10);
    for (iVar1 = dispatch[0x209]; iVar1 != region; iVar1 = *(int *)(iVar1 + 4)) {
      offset = offset + *(int *)(iVar1 + 0x10);
    }
    StEraseFromMid(dispatch[0x207],offset);
    iVar1 = *head;
    while (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 8) = 0;
      UtRemoveFromList(head,(int *)*head);
      iVar1 = *head;
    }
    StSpliceStream((undefined4 *)dispatch[0x207],*(undefined4 *)(*dispatch + 0xc),
                   *(int *)(region + 0xc) + *(int *)(region + 0x10));
  }
  return;
}

/* ---- 0x100034b0  iMUSE_Dispatch__34b0 ---- */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

int __cdecl iMUSE_Dispatch__34b0(int *dispatch)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(*dispatch + 0x20);
  if (dispatch[0x214] == 0) {
    uVar2 = dispatch[0x20d];
    if (uVar2 < 2) {
      uVar2 = 2;
    }
    dispatch[0x214] = -(int)(0x7f0000 / (ulonglong)uVar2);
  }
  return (0x80 - (dispatch[0x213] >> 0x10)) * iVar1 >> 7;
}

/* ---- 0x10003510  iMUSE_Dispatch__3510 ---- */
/* Unidentified function of iMUSE_Dispatch.c (command dispatch, fades, triggers) */

int __cdecl iMUSE_Dispatch__3510(int *dispatch,int count)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = dispatch[0x213];
  iVar2 = *(int *)(*dispatch + 0x20);
  iVar3 = iVar1 + dispatch[0x214] * count;
  dispatch[0x213] = iVar3;
  if (iVar3 < 0) {
    dispatch[0x213] = 0;
  }
  if (0x7f0000 < dispatch[0x213]) {
    dispatch[0x213] = 0x7f0000;
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

int __cdecl iMUSE_Dispatch__35a0(uint *size)

{
  int iVar1;
  int *piVar2;
  
  if (g_dwImLargeFadeSize < *size) {
    *size = g_dwImLargeFadeSize;
  }
  if (g_dwImSmallFadeSize < *size) {
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
    *size = g_dwImSmallFadeSize;
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

void __cdecl iMUSE_Dispatch__3640(int buf)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = g_dwLargeFadeBufs;
  if (0 < g_dwImLargeFadeCount) {
    do {
      if (buf == iVar2) {
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
    while (buf != iVar2) {
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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_10024df0[1192] __asm__("_DAT_10024df0");
extern unsigned char grim_def_DAT_10025abc[32036] __asm__("_DAT_10025abc");
extern unsigned char grim_def_g_dwPredictStream_jumpHook[4] __asm__("_g_dwPredictStream_jumpHook");
extern unsigned int grim_def_g_dwPrepareToJump_fadeSize __asm__("_g_dwPrepareToJump_fadeSize");
/* 0x10024dd8, 4 bytes */ GRIM_DATA("10024dd8") unsigned char grim_def_g_dwPredictStream_jumpHook[4] __asm__("_g_dwPredictStream_jumpHook") = {0};
/* 0x10024df0, 1192 bytes */ GRIM_DATA("10024df0") unsigned char grim_def_DAT_10024df0[1192] __asm__("_DAT_10024df0") = {0};
/* 0x10025abc, 32036 bytes */ GRIM_DATA("10025abc") unsigned char grim_def_DAT_10025abc[32036] __asm__("_DAT_10025abc") = {0};
/* 0x1002d80c, 4 bytes */ GRIM_DATA("1002d80c") unsigned int grim_def_g_dwPrepareToJump_fadeSize __asm__("_g_dwPrepareToJump_fadeSize") = 0x0;
