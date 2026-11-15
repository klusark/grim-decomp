/* IMUSE.DLL :: imuse_sounds.c
 * functions 0x10009e10 .. 0x1000a030 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10009e10  iRes_FTELL ---- */
/* Original name iRes_FTELL (the remaster's GrimFandango (Linux): same body (for a handle inside the
   MCMP handle array the position at +8, else the host ftell service +0x48); the counterpart of
   iRes_FSEEK; called by ihost_fseek / ihost_read here (the remaster inlined it)); was
   iMUSE_sounds__9e10. */

undefined4 __cdecl iRes_FTELL(undefined *f)

{
  undefined4 uVar1;
  
  if ((&DAT_1003039f < f) && (f < &DAT_10031520)) {
    return *(undefined4 *)(f + 8);
  }
  uVar1 = (**(code **)(g_dwSounds_pHS + 0x48))(f);
  return uVar1;
}

/* ---- 0x10009e40  iRes_FSEEK ---- */
/* Original name iRes_FSEEK (the remaster's GrimFandango (Linux): same body (for a handle outside
   the MCMP handle array the host fseek service +0x4c, else the position at +8 by whence 0 / 1 / 2
   with the size at +4)); was iMUSE_sounds__9e40. */

undefined4 __cdecl iRes_FSEEK(undefined *f,int offset,int whence)

{
  undefined4 uVar1;
  
  if ((f < &g_aMcmpFileHandles) || (&DAT_1003151f < f)) {
    uVar1 = (**(code **)(g_dwSounds_pHS + 0x4c))(f,offset,whence);
    return uVar1;
  }
  if (whence == 0) {
    *(int *)(f + 8) = offset;
    return 0;
  }
  if (whence != 1) {
    if (whence != 2) {
      return 1;
    }
    *(int *)(f + 8) = *(int *)(f + 4) + offset;
    return 0;
  }
  *(int *)(f + 8) = *(int *)(f + 8) + offset;
  return 0;
}

/* ---- 0x10009eb0  iMUSE_sounds__9eb0 ---- */
/* Unidentified function of iMUSE_sounds.c (sound resource slots) */

int __cdecl iMUSE_sounds__9eb0(int res,uint offset)

{
  uint uVar1;
  
  if (offset < *(uint *)(res + 4)) {
    uVar1 = bsearch(offset,*(uint *)(res + 0x1c),*(uint *)(res + 0xc),4,Sounds_CompareRange);
    if (uVar1 != 0) {
      return (int)(uVar1 - *(int *)(res + 0x1c)) >> 2;
    }
  }
  return -1;
}

/* ---- 0x10009ef0  Sounds_CompareRange ---- */
/* Search comparator: 0 when value lies in [range[0], range[1]), -1 below it, 1 above it; was
   FUN_10009ef0. */

int __cdecl Sounds_CompareRange(uint value,uint *range)

{
  if ((*range <= value) && (value < range[1])) {
    return 0;
  }
  return (-(uint)(value < *range) & 0xfffffffe) + 1;
}

/* ---- 0x10009f10  iMUSE_Malloc ---- */
/* Original name iMUSE_Malloc (the remaster's GrimFandango (Linux): same body (the host alloc
   service in sounds.c, then the pointer into the memory list mlEntries, which doubles when full);
   the remaster inlined FUN_10009f40 into it); was FUN_10009f10. */

uint __cdecl iMUSE_Malloc(uint size)

{
  uint block;
  
  block = (**(code **)(g_dwSounds_pHS + 0x20))(size,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0xad5)
  ;
  Sounds_MlAdd(block);
  return block;
}

/* ---- 0x10009f40  Sounds_MlAdd ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Adds a block to the loaded-memory list: appends while there is room, else reuses a free slot or
   doubles the list; was FUN_10009f40. */

void __cdecl Sounds_MlAdd(int block)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  if (_g_dwMlEntries != (int *)0x0) {
    if (_g_dwMlListSize < _g_dwMlEntryCount) {
      _g_dwMlEntries[_g_dwMlListSize] = block;
      _g_dwMlListSize = _g_dwMlListSize + 1;
      return;
    }
    iVar1 = 0;
    piVar3 = _g_dwMlEntries;
    if (0 < _g_dwMlEntryCount) {
      do {
        if (*piVar3 == 0) break;
        piVar3 = piVar3 + 1;
        iVar1 = iVar1 + 1;
      } while (iVar1 < _g_dwMlEntryCount);
    }
    if (iVar1 < _g_dwMlEntryCount) {
      iVar1 = _g_dwMlEntryCount * 8;
      _g_dwMlEntryCount = _g_dwMlEntryCount * 2;
      _g_dwMlEntries =
           (int *)(**(code **)(g_dwSounds_pHS + 0x28))
                            (_g_dwMlEntries,iVar1,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x9e);
      if (_g_dwMlEntries != (int *)0x0) {
        piVar3 = _g_dwMlEntries + _g_dwMlEntryCount / 2;
        for (uVar2 = _g_dwMlEntryCount / 2 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
          *piVar3 = 0;
          piVar3 = piVar3 + 1;
        }
        for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
          *(undefined1 *)piVar3 = 0;
          piVar3 = (int *)((int)piVar3 + 1);
        }
        _g_dwMlEntries[_g_dwMlListSize] = block;
        _g_dwMlListSize = _g_dwMlListSize + 1;
        return;
      }
    }
    else {
      *piVar3 = block;
    }
  }
  return;
}

/* ---- 0x1000a010  iMUSE_Free ---- */
/* Original name iMUSE_Free (the remaster's GrimFandango (Linux): same body (clear the pointer's
   slot in the memory list mlEntries, then the host free service); the remaster inlined FUN_1000a030
   into it); was FUN_1000a010. */

uint __cdecl iMUSE_Free(uint block)

{
  uint uVar1;
  
  Sounds_MlRemove(block);
  uVar1 = (**(code **)(g_dwSounds_pHS + 0x24))(block);
  return uVar1;
}

/* ---- 0x1000a030  Sounds_MlRemove ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Clears the loaded-memory list's slot that holds `block`; was FUN_1000a030. */

void __cdecl Sounds_MlRemove(int block)

{
  int iVar1;
  int *piVar2;
  
  if (_g_dwMlEntries != (int *)0x0) {
    iVar1 = 0;
    piVar2 = _g_dwMlEntries;
    if (0 < _g_dwMlListSize) {
      do {
        if (*piVar2 == block) break;
        piVar2 = piVar2 + 1;
        iVar1 = iVar1 + 1;
      } while (iVar1 < _g_dwMlListSize);
    }
    if (iVar1 < _g_dwMlListSize) {
      *piVar2 = 0;
    }
  }
  return;
}
