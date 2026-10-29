/* GRIMFANDANGO.EXE :: std.c
 * functions 0x0047c920 .. 0x0047fd00 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047c920  Std_ParseCommandLine ---- */
/* Splits the module command line into argv-style tokens */

undefined4 Std_ParseCommandLine(void)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  undefined1 *puVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  
  bVar2 = false;
  iVar6 = 0x3ff;
  pcVar7 = DAT_00900520;
  do {
    if (iVar6 == 0) {
      return 1;
    }
    iVar3 = (*g_pSvcMain->pFgets)(DAT_0080cbd0,pcVar7,iVar6);
    if (iVar3 == 0) {
      return 0;
    }
    DAT_0080cbc8 = DAT_0080cbc8 + 1;
    cVar1 = *pcVar7;
    if ((((cVar1 != ';') && (cVar1 != '#')) && (cVar1 != '\n')) && (cVar1 != '\r')) {
      puVar4 = (undefined1 *)strchr(pcVar7,0x23);
      if (puVar4 != (undefined1 *)0x0) {
        *puVar4 = 0;
      }
      _strlwr(pcVar7);
      uVar5 = 0xffffffff;
      pcVar8 = DAT_00900520;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      if (DAT_00900520[uVar5 - 3] == '\\') {
        iVar6 = 0x400 - (uVar5 - 1);
        pcVar7 = DAT_00900520 + (uVar5 - 3);
      }
      else {
        bVar2 = true;
        if ((DAT_00900520[uVar5 - 2] == '\r') || (DAT_00900520[uVar5 - 2] == '\n')) {
          DAT_00900520[uVar5 - 2] = '\0';
        }
      }
    }
    if (bVar2) {
      return 1;
    }
  } while( true );
}

/* ---- 0x0047ca00  FUN_0047ca00 ---- */
void FUN_0047ca00(void)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  undefined4 *puVar7;
  char *pcVar8;
  undefined4 *puVar9;
  
  uVar3 = 0xffffffff;
  pcVar6 = &DAT_009004a0;
  do {
    pcVar8 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar6 = pcVar8 + -uVar3;
  pcVar8 = &DAT_00806c88 + DAT_0080cbd8 * 0x80;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar2 = DAT_0080cbc8, uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  DAT_0080cbc8 = 0;
  *(undefined4 *)(&DAT_008076d8 + DAT_0080cbd8 * 4) = uVar2;
  *(undefined4 *)(&DAT_0080c778 + DAT_0080cbd8 * 4) = DAT_0080cbd0;
  uVar2 = DAT_00900520;
  DAT_0080cbd0 = 0;
  puVar7 = &DAT_00900080;
  puVar9 = (undefined4 *)(&DAT_00807728 + DAT_0080cbd8 * 0x404);
  for (iVar5 = 0x101; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar9 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar9 = puVar9 + 1;
  }
  *(undefined4 *)(&DAT_00807688 + DAT_0080cbd8 * 4) = uVar2;
  DAT_0080cbd8 = DAT_0080cbd8 + 1;
  return;
}

/* ---- 0x0047ca90  FUN_0047ca90 ---- */
void FUN_0047ca90(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  undefined4 *puVar7;
  char *pcVar8;
  undefined4 *puVar9;
  
  if (DAT_0080cbd8 != 0) {
    iVar5 = DAT_0080cbd8 + -1;
    uVar2 = 0xffffffff;
    pcVar6 = &DAT_00806c88 + iVar5 * 0x80;
    do {
      pcVar8 = pcVar6;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar8 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar8;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    pcVar6 = pcVar8 + -uVar2;
    pcVar8 = &DAT_009004a0;
    DAT_0080cbd8 = iVar5;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    DAT_0080cbd0 = *(undefined4 *)(&DAT_0080c778 + iVar5 * 4);
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
    DAT_0080cbc8 = *(undefined4 *)(&DAT_008076d8 + iVar5 * 4);
    DAT_00900520 = *(undefined4 *)(&DAT_00807688 + iVar5 * 4);
    puVar7 = (undefined4 *)(&DAT_00807728 + iVar5 * 0x404);
    puVar9 = &DAT_00900080;
    for (iVar4 = 0x101; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar9 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar9 = puVar9 + 1;
    }
  }
  return;
}

/* ---- 0x0047fc50  Std_Swap32 ---- */
uint Std_Swap32(uint param_1)

{
  return (param_1 << 0x10 | param_1 & 0xff00) << 8 | (param_1 >> 0x10 | param_1 & 0xff0000) >> 8;
}

/* ---- 0x0047fd00  Std_Swap16 ---- */
uint Std_Swap16(uint param_1)

{
  return (param_1 & 0xffff) >> 8 | (param_1 & 0xff) << 8;
}
