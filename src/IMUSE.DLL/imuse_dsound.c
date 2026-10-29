/* IMUSE.DLL :: imuse_dsound.c
 * functions 0x10003a80 .. 0x10004750 (9 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10003a80  iMUSE_dsound__3a80 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

int iMUSE_dsound__3a80(void)

{
  int iVar1;
  
  iVar1 = (**(code_std **)(*PTR_1002d83c + 0x10))(PTR_1002d83c,&DAT_1002d828,&DAT_1002d81c);
  if (iVar1 == 0) {
    return (DAT_1002d828 / 0x1800) % DAT_1002d824;
  }
  return -1;
}
#endif


/* ---- 0x10004540  iMUSE_dsound__4540 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 __cdecl iMUSE_dsound__4540(uint param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  pcVar1 = DAT_100336a4;
  iVar2 = iMUSE_dsound__45a0(param_1);
  if ((iVar2 != 0) && (pcVar1 != (code *)0x0)) {
    uVar3 = (*pcVar1)(param_1);
    return uVar3;
  }
  return 0;
}
#endif


/* ---- 0x10004570  iMUSE_dsound__4570 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 __cdecl iMUSE_dsound__4570(uint param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  pcVar1 = DAT_100336a0;
  iVar2 = iMUSE_dsound__45a0(param_1);
  if ((iVar2 != 0) && (pcVar1 != (code *)0x0)) {
    uVar3 = (*pcVar1)(param_1);
    return uVar3;
  }
  return 0;
}
#endif


/* ---- 0x100045a0  iMUSE_dsound__45a0 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 __cdecl iMUSE_dsound__45a0(uint param_1)

{
  if ((param_1 != 0) && (param_1 < 0xfffffff0)) {
    return 1;
  }
  return 0;
}
#endif


/* ---- 0x100045c0  iMUSE_dsound__45c0 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 __cdecl iMUSE_dsound__45c0(uint param_1,undefined4 param_2,undefined4 param_3)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  pcVar1 = DAT_100336ac;
  iVar2 = iMUSE_dsound__45a0(param_1);
  if ((iVar2 != 0) && (pcVar1 != (code *)0x0)) {
    uVar3 = (*pcVar1)(param_1,param_2,param_3);
    return uVar3;
  }
  return 0;
}
#endif


/* ---- 0x10004600  iMUSE_dsound__4600 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 __cdecl iMUSE_dsound__4600(uint param_1,undefined4 param_2,undefined4 param_3)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  pcVar1 = DAT_100336b0;
  iVar2 = iMUSE_dsound__45a0(param_1);
  if ((iVar2 != 0) && (pcVar1 != (code *)0x0)) {
    uVar3 = (*pcVar1)(param_1,param_2,param_3);
    return uVar3;
  }
  return 0;
}
#endif


/* ---- 0x10004640  iMUSE_dsound__4640 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of iMUSE_dsound.c (DirectSound output) */

undefined4 __cdecl iMUSE_dsound__4640(int param_1)

{
  undefined4 uVar1;
  
  if ((param_1 != 0) && (DAT_100336b4 != (code *)0x0)) {
    uVar1 = (*DAT_100336b4)(param_1);
    return uVar1;
  }
  return 0;
}
#endif


/* ---- 0x10004660  FUN_10004660 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10004660(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (_DAT_1002dd78 != 0) {
    return 1;
  }
  puVar2 = (undefined4 *)IMG_ADDR(0x1002dd48);
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  _DAT_1002dd58 = FUN_10009f10;
  _DAT_1002dd50 = param_1;
  _DAT_1002dd5c = FUN_1000a010;
  iVar1 = hmiFXInitSystem(IMG_ADDR(0x1002dd48));
  if (iVar1 != 0) {
    return 0;
  }
  iVar1 = hmiFXPresetLoadLibrary(&DAT_1002dd2c,IMG_ADDR(0x100172b0));
  if (iVar1 != 0) {
    return 0;
  }
  _DAT_1002dd30 = 1;
  _DAT_1002dd32 = 1;
  _DAT_1002dd34 = 0x5622;
  _DAT_1002dd3e = 0x10;
  _DAT_1002dd3c = 2;
  _DAT_1002dd38 = 0xac44;
  _DAT_1002dd40 = 0;
  _DAT_1002dd60 = 1;
  DAT_1002dd62 = 1;
  _DAT_1002dd64 = 0x5622;
  _DAT_1002dd6e = 0x10;
  _DAT_1002dd6c = 2;
  _DAT_1002dd68 = 0xac44;
  _DAT_1002dd70 = 0;
  _DAT_1002dd78 = 0;
  return 1;
}
#endif


/* ---- 0x10004750  FUN_10004750 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl FUN_10004750(uint param_1)

{
  int iVar1;
  uint uVar2;
  
  if (DAT_1002dd74 != 0) {
    hmiFXPresetRelease(DAT_1002dd74);
  }
  _DAT_1002dd08 = 0x20;
  _DAT_1002dd10 = param_1;
  iVar1 = hmiFXPresetProcess(DAT_1002dd2c,&DAT_1002dd08);
  if (iVar1 != 0) {
    DAT_1002dd74 = 0;
    DAT_1002dd7c = (uint)DAT_1002dd62;
    return 0;
  }
  DAT_1002dd74 = _DAT_1002dd0c;
  iVar1 = *(int *)(_DAT_1002dd0c + 0x450);
  if (iVar1 == 0) {
    uVar2 = param_1 & 0xff;
  }
  else {
    do {
      uVar2 = *(uint *)(iVar1 + 0xc);
      iVar1 = *(int *)(iVar1 + 0x18);
    } while (iVar1 != 0);
  }
  DAT_1002dd7c = 1;
  if ((uVar2 & 10) != 0) {
    DAT_1002dd7c = 2;
  }
  DAT_1002dd62 = (ushort)DAT_1002dd7c;
  _DAT_1002dd6c = DAT_1002dd62 * 2;
  _DAT_1002dd68 = DAT_1002dd7c * 0xac44;
  hmiFXPresetLock(_DAT_1002dd0c);
  return DAT_1002dd7c;
}
#endif

