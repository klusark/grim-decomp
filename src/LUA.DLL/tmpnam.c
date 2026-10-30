/* LUA.DLL :: tmpnam.c
 * functions 0x10010220 .. 0x100102a0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10010220  tmpnam_genfname ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl tmpnam_genfname(int param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  uint uVar7;
  
  pcVar5 = &DAT_1002bfc0;
  if (param_1 != 0) {
    pcVar5 = &DAT_1002bfd0;
  }
  pcVar5[0] = '\\';
  pcVar5[1] = '\0';
  pcVar2 = pcVar5 + 1;
  if ((*pcVar5 != '\\') && (*pcVar5 != '/')) {
    *pcVar2 = '\\';
    pcVar2 = pcVar5 + 2;
  }
  if (param_1 == 0) {
    *pcVar2 = 's';
  }
  else {
    *pcVar2 = 't';
  }
  pcVar2 = pcVar2 + 1;
  uVar7 = 0x20;
  uVar3 = GetCurrentProcessId();
  FUN_10015ff0(uVar3,pcVar2,uVar7);
  uVar3 = 0xffffffff;
  pcVar2 = ".";
  do {
    pcVar6 = pcVar2;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar4 = -1;
  do {
    pcVar2 = pcVar5;
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    pcVar2 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar2;
  } while (cVar1 != '\0');
  pcVar5 = pcVar6 + -uVar3;
  pcVar2 = pcVar2 + -1;
  for (uVar7 = uVar3 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar2 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar2 = pcVar2 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar2 = pcVar2 + 1;
  }
  return;
}

/* ---- 0x100102a0  FUN_100102a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_100102a0(byte *param_1)

{
  char cVar1;
  byte *pbVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  char *pcVar8;
  
  pbVar2 = _mbschr(param_1,0x2e);
  iVar3 = strtoul(pbVar2 + 1,(undefined4 *)0x0,0x20);
  if (0x7ffe < iVar3 + 1U) {
    return 0xffffffff;
  }
  pcVar4 = FUN_10015ff0(iVar3 + 1U,(char *)&param_1,0x20);
  uVar5 = 0xffffffff;
  do {
    pcVar8 = pcVar4;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar8;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pbVar7 = (byte *)(pcVar8 + -uVar5);
  pbVar2 = pbVar2 + 1;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pbVar2 = *(undefined4 *)pbVar7;
    pbVar7 = pbVar7 + 4;
    pbVar2 = pbVar2 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar2 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    pbVar2 = pbVar2 + 1;
  }
  return 0;
}
#endif

