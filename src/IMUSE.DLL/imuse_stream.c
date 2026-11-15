/* IMUSE.DLL :: imuse_stream.c
 * functions 0x1000a210 .. 0x1000b8d0 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000a210  StStartStream ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name StStartStream (the remaster's GrimFandango (Linux): aligned call in
   DpConcludeRestore, DpStartSound); was iMUSE_stream__a210. */

uint * __cdecl StStartStream(uint sound,uint slot,uint offset)

{
  uint *puVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  
  puVar1 = (uint *)FmGetBufInfo(slot);
  if ((puVar1 != (uint *)0x0) && (offset < (uint)((int)puVar1[1] >> 2))) {
    piVar2 = &g_dwStreams;
    iVar4 = 0;
    while ((*piVar2 == 0 || (piVar2[3] != slot))) {
      piVar2 = piVar2 + 0xc;
      iVar4 = iVar4 + 1;
      if (2 < iVar4) {
        puVar5 = &g_dwStreams;
        iVar4 = 0;
        do {
          if (*puVar5 == 0) {
            *puVar5 = sound;
            puVar5[1] = 0;
            uVar3 = FmSeek(sound,0,2);
            puVar5[2] = uVar3;
            puVar5[3] = slot;
            puVar5[4] = *puVar1;
            puVar5[5] = (puVar1[1] - offset) - 4;
            puVar5[6] = puVar1[2];
            uVar3 = puVar1[3];
            puVar5[8] = offset;
            puVar5[7] = uVar3;
            puVar5[9] = 0;
            puVar5[10] = 0;
            puVar5[0xb] = 0;
            return puVar5;
          }
          puVar5 = puVar5 + 0xc;
          iVar4 = iVar4 + 1;
        } while (iVar4 < 3);
        return (uint *)0x0;
      }
    }
  }
  return (uint *)0x0;
}

/* ---- 0x1000a2d0  StStopStream ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name StStopStream (the remaster's GrimFandango (Linux): aligned call in DpStopTrack);
   was iMUSE_stream__a2d0. */

undefined4 __cdecl StStopStream(undefined4 *stream)

{
  *stream = 0;
  if (g_dwLastStreamLoaded == stream) {
    g_dwLastStreamLoaded = (undefined4 *)0x0;
  }
  return 0;
}

/* ---- 0x1000a420  StReadData ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name StReadData (the remaster's GrimFandango (Linux): aligned call in DpProcessTrack,
   DpSwitchStream, GoToNextRegion); was iMUSE_stream__a420. */

int __cdecl StReadData(int stream,uint size)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  uVar1 = StGetValidSize(stream);
  if ((uVar1 < size) || (*(uint *)(stream + 0x20) < size)) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(stream + 0x14);
    if ((uint)(iVar2 - *(int *)(stream + 0x28)) < size) {
      uVar3 = (size - iVar2) + *(int *)(stream + 0x28);
      puVar4 = *(undefined4 **)(stream + 0x10);
      puVar5 = (undefined4 *)((int)*(undefined4 **)(stream + 0x10) + iVar2);
      for (uVar1 = uVar3 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
    }
    iVar2 = *(int *)(stream + 0x10) + *(int *)(stream + 0x28);
    uVar1 = *(int *)(stream + 0x28) + size;
    *(uint *)(stream + 0x28) = uVar1;
    if (*(uint *)(stream + 0x14) <= uVar1) {
      *(uint *)(stream + 0x28) = uVar1 - *(uint *)(stream + 0x14);
      return iVar2;
    }
  }
  return iVar2;
}

/* ---- 0x1000a490  StViewData ---- */
/* Original name StViewData (the remaster's GrimFandango (Linux): same body (offset + size within
   StGetValidSize and the view size +0x20, the ring-buffer wrap copied to the end of the buffer,
   returns buffer + offset); called by the region fetch as in the remaster's GoToNextRegion); was
   iMUSE_stream__a490. */

int __cdecl StViewData(int stream,int offset,uint size)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  uVar2 = StGetValidSize(stream);
  if ((size + offset <= uVar2) && (size <= *(uint *)(stream + 0x20))) {
    iVar1 = *(int *)(stream + 0x14);
    iVar4 = *(int *)(stream + 0x28) + offset;
    if (iVar1 <= iVar4) {
      iVar4 = iVar4 - iVar1;
    }
    if ((uint)(iVar1 - iVar4) < size) {
      uVar3 = (size + iVar4) - iVar1;
      puVar5 = *(undefined4 **)(stream + 0x10);
      puVar6 = (undefined4 *)((int)*(undefined4 **)(stream + 0x10) + iVar1);
      for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
        puVar6 = (undefined4 *)((int)puVar6 + 1);
      }
    }
    return *(int *)(stream + 0x10) + iVar4;
  }
  return 0;
}

/* ---- 0x1000a500  StEraseFromFront ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name StEraseFromFront (the remaster's GrimFandango (Linux): aligned call in
   DpSwitchStream, StFeedStream); was iMUSE_stream__a500. */

undefined4 __cdecl StEraseFromFront(int stream,uint size)

{
  uint uVar1;
  
  g_dwBailFlag = 1;
  uVar1 = StGetValidSize(stream);
  if (uVar1 < size) {
    return 0xffffffff;
  }
  uVar1 = *(int *)(stream + 0x28) + size;
  *(uint *)(stream + 0x28) = uVar1;
  if (*(uint *)(stream + 0x14) <= uVar1) {
    *(uint *)(stream + 0x28) = uVar1 - *(uint *)(stream + 0x14);
  }
  return 0;
}

/* ---- 0x1000a540  StEraseFromMid ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name StEraseFromMid (the remaster's GrimFandango (Linux): aligned call in
   PrepareToJump); was iMUSE_stream__a540. */

undefined4 __cdecl StEraseFromMid(int stream,uint offset)

{
  uint uVar1;
  
  g_dwBailFlag = 1;
  uVar1 = StGetValidSize(stream);
  if (uVar1 < offset) {
    return 0xffffffff;
  }
  uVar1 = *(int *)(stream + 0x28) + offset;
  *(uint *)(stream + 0x24) = uVar1;
  if (*(uint *)(stream + 0x14) <= uVar1) {
    *(uint *)(stream + 0x24) = uVar1 - *(uint *)(stream + 0x14);
  }
  return 0;
}

/* ---- 0x1000a5a0  StSpliceStream ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name StSpliceStream (the remaster's GrimFandango (Linux): aligned call in
   DpConcludeRestore, DpSwitchStream, PrepareToJump); was iMUSE_stream__a5a0. */

undefined4 __cdecl StSpliceStream(undefined4 *stream,undefined4 offset,undefined4 sound)

{
  g_dwBailFlag = 1;
  *stream = offset;
  stream[1] = sound;
  stream[2] = 0;
  stream[0xb] = 0;
  if (g_dwLastStreamLoaded == stream) {
    g_dwLastStreamLoaded = (undefined4 *)0x0;
  }
  return 0;
}

/* ---- 0x1000b760  UtAddToList ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name UtAddToList (the remaster's GrimFandango (Linux): aligned call in TrRestore,
   TrStartSound); was iMUSE_stream__b760. */

undefined4 __cdecl UtAddToList(int *trackList,int *node)

{
  if (((node != (int *)0x0) && (*node == 0)) && (node[1] == 0)) {
    node[1] = *trackList;
    if ((undefined4 *)*trackList != (undefined4 *)0x0) {
      *(undefined4 *)*trackList = node;
    }
    *node = 0;
    *trackList = (int)node;
    return 0;
  }
  return 0xfffffffb;
}

/* ---- 0x1000b7a0  UtRemoveFromList ---- */
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
   Original name UtRemoveFromList (the remaster's GrimFandango (Linux): aligned call in DpStopTrack,
   GoToNextRegion, TrStopTrack); was iMUSE_stream__b7a0. */

undefined4 __cdecl UtRemoveFromList(int *head,int *node)

{
  int *piVar1;
  
  piVar1 = (int *)*head;
  if ((node == (int *)0x0) || (piVar1 == (int *)0x0)) {
    return 0xfffffffb;
  }
  do {
    if (piVar1 == node) break;
    piVar1 = (int *)piVar1[1];
  } while (piVar1 != (int *)0x0);
  if (piVar1 == (int *)0x0) {
    return 0xfffffffd;
  }
  if ((int *)node[1] != (int *)0x0) {
    *(int *)node[1] = *node;
  }
  if (*node != 0) {
    *(int *)(*node + 4) = node[1];
    node[1] = 0;
    *node = 0;
    return 0;
  }
  *head = node[1];
  node[1] = 0;
  *node = 0;
  return 0;
}

/* ---- 0x1000b810  UtReadLongHilo ---- */
/* Original name UtReadLongHilo (the remaster's GrimFandango (Linux): same body (the big-endian
   32-bit read *p << 24 | p[1] << 16 | p[2] << 8 | p[3]); called by the MAP converter (ConvertMap)
   and the region code in both builds); was iMUSE_stream__b810. */

undefined4 __cdecl UtReadLongHilo(undefined1 *p)

{
  return CONCAT31(CONCAT21(CONCAT11(*p,p[1]),p[2]),p[3]);
}

/* ---- 0x1000b840  UtCheckHook ---- */
/* Original name UtCheckHook (the remaster's GrimFandango (Linux): same body (hook 0 matches 0x80
   and clears it, else a hook equal to *p clears it); called by the JUMP search under the jump hook
   (PredictStream in the remaster, inlined there) and GoToNextRegion in both builds); was
   iMUSE_stream__b840. */

undefined4 __cdecl UtCheckHook(int *hook,int value)

{
  if (value == 0) {
    if (*hook != 0x80) {
      return 0;
    }
    *hook = 0;
  }
  else if (value == *hook) {
    *hook = 0;
    return 0;
  }
  return 0xffffffff;
}

/* ---- 0x1000b8d0  FUN_1000b8d0 ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */

