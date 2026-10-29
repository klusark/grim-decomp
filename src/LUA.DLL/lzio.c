/* LUA.DLL :: lzio.c
 * functions 0x1000edc0 .. 0x1000ef40 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000edc0  luaZ_mopen ---- */
/* Unidentified function of lvm.c (virtual machine) */

undefined4 * __cdecl
luaZ_mopen(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_2 == 0) {
    return (undefined4 *)0x0;
  }
  param_1[1] = param_2;
  *param_1 = param_3;
  param_1[2] = FUN_1000edf0;
  param_1[3] = 0;
  param_1[4] = param_4;
  return param_1;
}

/* ---- 0x1000edf0  FUN_1000edf0 ---- */
undefined4 FUN_1000edf0(void)

{
  return 0xffffffff;
}

/* ---- 0x1000ee00  luaZ_sopen ---- */
/* Unidentified function of lvm.c (virtual machine) */

undefined4 * __cdecl luaZ_sopen(undefined4 *param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  char *pcVar4;
  
  if (param_2 == (char *)0x0) {
    return (undefined4 *)0x0;
  }
  uVar3 = 0xffffffff;
  pcVar4 = param_2;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  puVar2 = luaZ_mopen(param_1,(int)param_2,~uVar3 - 1,param_3);
  return puVar2;
}

/* ---- 0x1000ee30  luaZ_Fopen ---- */
undefined4 * __cdecl luaZ_Fopen(undefined4 *param_1,int param_2,undefined4 param_3)

{
                    /* 0xee30  5  luaZ_Fopen */
  if (param_2 == 0) {
    return (undefined4 *)0x0;
  }
  param_1[3] = param_2;
  *param_1 = 0;
  param_1[1] = param_1 + 5;
  param_1[2] = FUN_1000ee60;
  param_1[4] = param_3;
  return param_1;
}

/* ---- 0x1000ee60  FUN_1000ee60 ---- */
uint __cdecl FUN_1000ee60(int *param_1)

{
  byte *pbVar1;
  int iVar2;
  
  pbVar1 = (byte *)(param_1 + 5);
  iVar2 = (**(code **)(DAT_1002beb8 + 0x38))(param_1[3],pbVar1,0x100);
  if (iVar2 == 0) {
    return 0xffffffff;
  }
  param_1[1] = (int)pbVar1;
  *param_1 = iVar2 + -1;
  param_1[1] = (int)param_1 + 0x15;
  return (uint)*pbVar1;
}

/* ---- 0x1000eea0  luaZ_read ---- */
/* Unidentified function of lzio.c (input streams) */

uint __cdecl luaZ_read(uint *param_1,undefined4 *param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if (param_3 == 0) {
    return 0;
  }
  do {
    if (*param_1 == 0) {
      iVar1 = (*(code *)param_1[2])(param_1);
      if (iVar1 == -1) {
        return param_3;
      }
      *param_1 = *param_1 + 1;
      param_1[1] = param_1[1] - 1;
    }
    uVar2 = *param_1;
    if ((int)param_3 <= (int)*param_1) {
      uVar2 = param_3;
    }
    puVar4 = (undefined4 *)param_1[1];
    puVar5 = param_2;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    param_2 = (undefined4 *)((int)param_2 + uVar2);
    for (uVar3 = uVar2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    param_3 = param_3 - uVar2;
    *param_1 = *param_1 - uVar2;
    param_1[1] = param_1[1] + uVar2;
  } while (param_3 != 0);
  return 0;
}

/* ---- 0x1000ef20  lzio__ef20 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Unidentified function of lzio.c (input streams) */

void lzio__ef20(void)

{
  lzio__ef40();
  _DAT_1002bf8c = FUN_10012f30();
  FUN_10012ec0();
  return;
}

/* ---- 0x1000ef40  lzio__ef40 ---- */
/* Unidentified function of lzio.c (input streams) */

void lzio__ef40(void)

{
  PTR_FUN_10028b7c = FUN_10012fc0;
  PTR_FUN_10028b78 = FUN_10013420;
  PTR_FUN_10028b80 = FUN_10013050;
  PTR_FUN_10028b84 = FUN_10012f60;
  PTR_FUN_10028b88 = FUN_10013030;
  PTR_FUN_10028b8c = FUN_10013420;
  return;
}
