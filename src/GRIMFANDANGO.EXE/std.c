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
  pcVar7 = (char *)UINT_00900520;
  do {
    if (iVar6 == 0) {
      return 1;
    }
    iVar3 = (*g_pSvcMain->pFgets)(UINT_0080cbd0,pcVar7,iVar6);
    if (iVar3 == 0) {
      return 0;
    }
    UINT_0080cbc8 = UINT_0080cbc8 + 1;
    cVar1 = *pcVar7;
    if ((((cVar1 != ';') && (cVar1 != '#')) && (cVar1 != '\n')) && (cVar1 != '\r')) {
      puVar4 = (undefined1 *)strchr(pcVar7,0x23);
      if (puVar4 != (undefined1 *)0x0) {
        *puVar4 = 0;
      }
      _strlwr(pcVar7);
      uVar5 = 0xffffffff;
      pcVar8 = (char *)UINT_00900520;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      if (*(char *)((uVar5 - 3) + UINT_00900520) == '\\') {
        iVar6 = 0x400 - (uVar5 - 1);
        pcVar7 = (char *)((uVar5 - 3) + UINT_00900520);
      }
      else {
        cVar1 = *(char *)((uVar5 - 2) + UINT_00900520);
        bVar2 = true;
        if ((cVar1 == '\r') || (cVar1 == '\n')) {
          *(undefined1 *)((uVar5 - 2) + UINT_00900520) = 0;
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
  uint uVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  uint *puVar6;
  char *pcVar7;
  uint *puVar8;
  
  uVar2 = 0xffffffff;
  pcVar5 = &DAT_009004a0;
  do {
    pcVar7 = pcVar5;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar7 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar7;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar5 = pcVar7 + -uVar2;
  pcVar7 = &DAT_00806c88 + UINT_0080cbd8 * 0x80;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar3 = UINT_0080cbc8, uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar7 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar7 = pcVar7 + 1;
  }
  UINT_0080cbc8 = 0;
  *(uint *)(&DAT_008076d8 + UINT_0080cbd8 * 4) = uVar3;
  *(uint *)(&DAT_0080c778 + UINT_0080cbd8 * 4) = UINT_0080cbd0;
  uVar2 = UINT_00900520;
  UINT_0080cbd0 = 0;
  puVar6 = &UINT_00900080;
  puVar8 = (uint *)(&DAT_00807728 + UINT_0080cbd8 * 0x404);
  for (iVar4 = 0x101; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  *(uint *)(&DAT_00807688 + UINT_0080cbd8 * 4) = uVar2;
  UINT_0080cbd8 = UINT_0080cbd8 + 1;
  return;
}

/* ---- 0x0047ca90  FUN_0047ca90 ---- */
void FUN_0047ca90(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  uint *puVar7;
  char *pcVar8;
  uint *puVar9;
  
  if (UINT_0080cbd8 != 0) {
    uVar5 = UINT_0080cbd8 - 1;
    uVar2 = 0xffffffff;
    pcVar6 = &DAT_00806c88 + uVar5 * 0x80;
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
    UINT_0080cbd8 = uVar5;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    UINT_0080cbd0 = *(uint *)(&DAT_0080c778 + uVar5 * 4);
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
    UINT_0080cbc8 = *(uint *)(&DAT_008076d8 + uVar5 * 4);
    UINT_00900520 = *(uint *)(&DAT_00807688 + uVar5 * 4);
    puVar7 = (uint *)(&DAT_00807728 + uVar5 * 0x404);
    puVar9 = &UINT_00900080;
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
