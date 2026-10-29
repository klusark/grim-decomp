/* GRIMFANDANGO.EXE :: platmodule.c
 * functions 0x004abe90 .. 0x004abf30 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004abe90  PlatModule_Init ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlatModule_Init(GrimServices *svc,void *iface)

{
  int iVar1;
  
  _DAT_008d098c = svc;
  iVar1 = 1;
  if (UINT_008d0990 == 0) {
    UINT_008d0990 = 1;
    if (iface != (void *)0x0) {
      *(code **)iface = PlatModule_Init;
      *(code **)((int)iface + 4) = FUN_004abef0;
      *(code **)((int)iface + 8) = FUN_004abf00;
      *(code **)((int)iface + 0xc) = FUN_004abf30;
      *(undefined4 *)((int)iface + 0x10) = 0;
      *(undefined4 *)((int)iface + 0x14) = 0;
      *(undefined4 *)((int)iface + 0x18) = 0;
      *(undefined4 *)((int)iface + 0x1c) = 0;
    }
    iVar1 = 0;
  }
  return iVar1;
}

/* ---- 0x004abef0  FUN_004abef0 ---- */
void FUN_004abef0(void)

{
  UINT_008d0990 = 0;
  return;
}

/* ---- 0x004abf00  FUN_004abf00 ---- */
undefined4 FUN_004abf00(void)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if ((UINT_008d0990 != 0) && (UINT_008d0994 == 0)) {
    UINT_008d0994 = 1;
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x004abf30  FUN_004abf30 ---- */
void FUN_004abf30(void)

{
  UINT_008d0994 = 0;
  return;
}
