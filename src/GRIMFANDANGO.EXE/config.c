/* GRIMFANDANGO.EXE :: config.c
 * functions 0x00498bf0 .. 0x00498cf0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00498bf0  Config_GetPath ---- */
/* Reads a path setting from the registry (prefix g_szConfigKeyPrefix + name); falls back to
   GrimDataDir plus the default sub directory */

void __cdecl Config_GetPath(char *name,char *buf,char *defaultSubdir)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  #define local_80 (*(char (*)[128])(_frame + (0x90 - 0x80)))
  
  uVar2 = 0xffffffff;
  pcVar5 = g_szConfigKeyPrefix;
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
  pcVar7 = local_80;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar7 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar2 = 0xffffffff;
  do {
    pcVar5 = name;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar5 = name + 1;
    cVar1 = *name;
    name = pcVar5;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  iVar4 = -1;
  pcVar7 = local_80;
  do {
    pcVar6 = pcVar7;
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    pcVar6 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar6;
  } while (cVar1 != '\0');
  pcVar5 = pcVar5 + -uVar2;
  pcVar7 = pcVar6 + -1;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar7 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar7 = pcVar7 + 1;
  }
  wuRegistry_GetStr(local_80,buf,0x80,&DAT_004f5a98);
  if (*buf == '\0') {
    iVar4 = wuRegistry_GetStr(s_GrimDataDir_004dd94c,buf,0x80,&DAT_004f5a98);
    if (iVar4 != 0) {
      uVar2 = 0xffffffff;
      pcVar5 = &DAT_004e9c60;
      do {
        pcVar7 = pcVar5;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar7 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar7;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      iVar4 = -1;
      pcVar5 = buf;
      do {
        pcVar6 = pcVar5;
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        pcVar6 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar6;
      } while (cVar1 != '\0');
      pcVar5 = pcVar7 + -uVar2;
      pcVar7 = pcVar6 + -1;
      for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar7 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar7 = pcVar7 + 1;
      }
      uVar2 = 0xffffffff;
      do {
        pcVar5 = defaultSubdir;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar5 = defaultSubdir + 1;
        cVar1 = *defaultSubdir;
        defaultSubdir = pcVar5;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      iVar4 = -1;
      do {
        pcVar7 = buf;
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        pcVar7 = buf + 1;
        cVar1 = *buf;
        buf = pcVar7;
      } while (cVar1 != '\0');
      pcVar5 = pcVar5 + -uVar2;
      pcVar7 = pcVar7 + -1;
      for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar7 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar7 = pcVar7 + 1;
      }
    }
  }
  return;
}
#undef local_80


/* ---- 0x00498cf0  Config_SetPath ---- */
void __cdecl Config_SetPath(char *name,char *value)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  #define local_80 (*(char (*)[128])(_frame + (0x90 - 0x80)))
  
  if (*value != '\0') {
    uVar2 = 0xffffffff;
    pcVar5 = g_szConfigKeyPrefix;
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
    pcVar7 = local_80;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *pcVar7 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar7 = pcVar7 + 1;
    }
    uVar2 = 0xffffffff;
    do {
      pcVar5 = name;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar5 = name + 1;
      cVar1 = *name;
      name = pcVar5;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    iVar4 = -1;
    pcVar7 = local_80;
    do {
      pcVar6 = pcVar7;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar6 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar6;
    } while (cVar1 != '\0');
    pcVar5 = pcVar5 + -uVar2;
    pcVar7 = pcVar6 + -1;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *pcVar7 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar7 = pcVar7 + 1;
    }
    wuRegistry_SaveStr(local_80,value);
  }
  return;
}
#undef local_80

