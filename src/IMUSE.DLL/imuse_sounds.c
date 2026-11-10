/* IMUSE.DLL :: imuse_sounds.c
 * functions 0x10009e10 .. 0x1000a030 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10009e10  iMUSE_sounds__9e10 ---- */
/* Unidentified function of iMUSE_sounds.c (sound resource slots) */

undefined4 __cdecl iMUSE_sounds__9e10(undefined *param_1)

{
  undefined4 uVar1;
  
  if (((undefined *)IMG_ADDR(0x1003039f) < param_1) && (param_1 < &DAT_10031520)) {
    return *(undefined4 *)(param_1 + 8);
  }
  uVar1 = (**(code **)(g_dwSounds_pHS + 0x48))(param_1);
  return uVar1;
}

/* ---- 0x10009e40  iMUSE_sounds__9e40 ---- */
/* Unidentified function of iMUSE_sounds.c (sound resource slots) */

undefined4 __cdecl iMUSE_sounds__9e40(undefined *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((param_1 < &DAT_100303a0) || ((undefined *)IMG_ADDR(0x1003151f) < param_1)) {
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

/* ---- 0x10009f10  FUN_10009f10 ---- */
undefined4 FUN_10009f10(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(g_dwSounds_pHS + 0x20))
                    (param_1,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0xad5);
  FUN_10009f40(uVar1);
  return uVar1;
}

/* ---- 0x10009f40  FUN_10009f40 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10009f40(int param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  if (_DAT_10031d38 != (int *)0x0) {
    if (_DAT_1002ebd8 < _DAT_1002ec10) {
      _DAT_10031d38[_DAT_1002ebd8] = param_1;
      _DAT_1002ebd8 = _DAT_1002ebd8 + 1;
      return;
    }
    iVar1 = 0;
    piVar3 = _DAT_10031d38;
    if (0 < _DAT_1002ec10) {
      do {
        if (*piVar3 == 0) break;
        piVar3 = piVar3 + 1;
        iVar1 = iVar1 + 1;
      } while (iVar1 < _DAT_1002ec10);
    }
    if (iVar1 < _DAT_1002ec10) {
      iVar1 = _DAT_1002ec10 * 8;
      _DAT_1002ec10 = _DAT_1002ec10 * 2;
      _DAT_10031d38 =
           (int *)(**(code **)(g_dwSounds_pHS + 0x28))
                            (_DAT_10031d38,iVar1,s_C__grimsrc_libs_iMUSE_sounds_c_1001e8e0,0x9e);
      if (_DAT_10031d38 != (int *)0x0) {
        piVar3 = _DAT_10031d38 + _DAT_1002ec10 / 2;
        for (uVar2 = _DAT_1002ec10 / 2 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
          *piVar3 = 0;
          piVar3 = piVar3 + 1;
        }
        for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
          *(undefined1 *)piVar3 = 0;
          piVar3 = (int *)((int)piVar3 + 1);
        }
        _DAT_10031d38[_DAT_1002ebd8] = param_1;
        _DAT_1002ebd8 = _DAT_1002ebd8 + 1;
        return;
      }
    }
    else {
      *piVar3 = param_1;
    }
  }
  return;
}

/* ---- 0x1000a010  FUN_1000a010 ---- */
void FUN_1000a010(undefined4 param_1)

{
  FUN_1000a030(param_1);
  (**(code **)(g_dwSounds_pHS + 0x24))(param_1);
  return;
}

/* ---- 0x1000a030  FUN_1000a030 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000a030(int param_1)

{
  int iVar1;
  int *piVar2;
  
  if (_DAT_10031d38 != (int *)0x0) {
    iVar1 = 0;
    piVar2 = _DAT_10031d38;
    if (0 < _DAT_1002ebd8) {
      do {
        if (*piVar2 == param_1) break;
        piVar2 = piVar2 + 1;
        iVar1 = iVar1 + 1;
      } while (iVar1 < _DAT_1002ebd8);
    }
    if (iVar1 < _DAT_1002ebd8) {
      *piVar2 = 0;
    }
  }
  return;
}
