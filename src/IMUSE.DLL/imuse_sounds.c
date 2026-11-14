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

undefined4 __cdecl iRes_FTELL(undefined *param_1)

{
  undefined4 uVar1;
  
  if (((undefined *)((unsigned)(uintptr_t)&DAT_1003039f) < param_1) && (param_1 < &DAT_10031520)) {
    return *(undefined4 *)(param_1 + 8);
  }
  uVar1 = (**(code **)(g_dwSounds_pHS + 0x48))(param_1);
  return uVar1;
}

/* ---- 0x10009e40  iRes_FSEEK ---- */
/* Original name iRes_FSEEK (the remaster's GrimFandango (Linux): same body (for a handle outside
   the MCMP handle array the host fseek service +0x4c, else the position at +8 by whence 0 / 1 / 2
   with the size at +4)); was iMUSE_sounds__9e40. */

undefined4 __cdecl iRes_FSEEK(undefined *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((param_1 < &g_aMcmpFileHandles) || ((undefined *)((unsigned)(uintptr_t)&DAT_1003151f) < param_1)) {
    uVar1 = (**(code **)(g_dwSounds_pHS + 0x4c))(param_1,param_2,param_3);
    return uVar1;
  }
  if (param_3 == 0) {
    *(int *)(param_1 + 8) = param_2;
    return 0;
  }
  if (param_3 != 1) {
    if (param_3 != 2) {
      return 1;
    }
    *(int *)(param_1 + 8) = *(int *)(param_1 + 4) + param_2;
    return 0;
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + param_2;
  return 0;
}

/* ---- 0x10009eb0  iMUSE_sounds__9eb0 ---- */
/* Unidentified function of iMUSE_sounds.c (sound resource slots) */

int __cdecl iMUSE_sounds__9eb0(int param_1,uint param_2)

{
  uint uVar1;
  
  if (param_2 < *(uint *)(param_1 + 4)) {
    uVar1 = bsearch(param_2,*(uint *)(param_1 + 0x1c),*(uint *)(param_1 + 0xc),4,FUN_10009ef0);
    if (uVar1 != 0) {
      return (int)(uVar1 - *(int *)(param_1 + 0x1c)) >> 2;
    }
  }
  return -1;
}

/* ---- 0x10009ef0  FUN_10009ef0 ---- */
int __cdecl FUN_10009ef0(uint param_1,uint *param_2)

{
  if ((*param_2 <= param_1) && (param_1 < param_2[1])) {
    return 0;
  }
  return (-(uint)(param_1 < *param_2) & 0xfffffffe) + 1;
}

/* ---- 0x10009f10  iMUSE_Malloc ---- */
/* Original name iMUSE_Malloc (the remaster's GrimFandango (Linux): same body (the host alloc
   service in sounds.c, then the pointer into the memory list mlEntries, which doubles when full);
   the remaster inlined FUN_10009f40 into it); was FUN_10009f10. */

uint __cdecl iMUSE_Malloc(uint param_1)

{
  uint uVar1;
  
  uVar1 = (**(code **)(g_dwSounds_pHS + 0x20))
                    (param_1,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0xad5);
  FUN_10009f40(uVar1);
  return uVar1;
}

/* ---- 0x10009f40  FUN_10009f40 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_10009f40(int param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  if (_g_dwMlEntries != (int *)0x0) {
    if (_g_dwMlListSize < _g_dwMlEntryCount) {
      _g_dwMlEntries[_g_dwMlListSize] = param_1;
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
        _g_dwMlEntries[_g_dwMlListSize] = param_1;
        _g_dwMlListSize = _g_dwMlListSize + 1;
        return;
      }
    }
    else {
      *piVar3 = param_1;
    }
  }
  return;
}

/* ---- 0x1000a010  iMUSE_Free ---- */
/* Original name iMUSE_Free (the remaster's GrimFandango (Linux): same body (clear the pointer's
   slot in the memory list mlEntries, then the host free service); the remaster inlined FUN_1000a030
   into it); was FUN_1000a010. */

uint __cdecl iMUSE_Free(uint param_1)

{
  uint uRet;
  
  FUN_1000a030(param_1);
  uRet = (uint)(**(code **)(g_dwSounds_pHS + 0x24))(param_1);
  return uRet;
}

/* ---- 0x1000a030  FUN_1000a030 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_1000a030(int param_1)

{
  int iVar1;
  int *piVar2;
  
  if (_g_dwMlEntries != (int *)0x0) {
    iVar1 = 0;
    piVar2 = _g_dwMlEntries;
    if (0 < _g_dwMlListSize) {
      do {
        if (*piVar2 == param_1) break;
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
