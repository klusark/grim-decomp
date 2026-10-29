/* CHORE.DLL :: crt.c
 * functions 0x10006070 .. 0x10006070 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10006070  entry ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __stdcall entry(int a1,int a2,int a3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 1;
  if ((a2 == 0) && (_DAT_100143fc == 0)) {
    return 0;
  }
  if ((a2 != 1) && (a2 != 2)) {
LAB_100060ce:
    iVar1 = FUN_10008990(a1,a2,a3);
    if ((a2 == 1) && (iVar1 == 0)) {
      FUN_10005f50(a1,0,a3);
    }
    if ((a2 == 0) || (a2 == 3)) {
      iVar2 = FUN_10005f50(a1,a2,a3);
      if (iVar2 == 0) {
        iVar1 = 0;
      }
      if ((iVar1 != 0) && (_DAT_10015af8 != (code *)0x0)) {
        iVar1 = (*_DAT_10015af8)(a1,a2,a3);
      }
    }
    return iVar1;
  }
  if (_DAT_10015af8 != (code *)0x0) {
    iVar1 = (*_DAT_10015af8)(a1,a2,a3);
  }
  if (iVar1 != 0) {
    iVar1 = FUN_10005f50(a1,a2,a3);
    if (iVar1 != 0) goto LAB_100060ce;
  }
  return 0;
}
