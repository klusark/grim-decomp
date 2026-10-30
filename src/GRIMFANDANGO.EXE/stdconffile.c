/* GRIMFANDANGO.EXE :: stdconffile.c
 * functions 0x0047c7c0 .. 0x0047ca90 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047c7c0  stdConffile_OpenRead ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Opens a text configuration file for reading (stdConffile_OpenMode with mode "r"). Source file
   Stdconffile.c (C:\grimjedi\Libs\Std\General\Stdconffile.c). */

void stdConffile_OpenRead(undefined4 param_1)

{
  stdConffile_OpenMode(param_1,&DAT_004dda54);
  return;
}
#endif


/* ---- 0x0047c7e0  stdConffile_OpenMode ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Opens a configuration file through the file services (pFopen); pushes the currently open file
   first (stdConffile_Push) and allocates the 0x400-byte line buffer. The name 'none' means no file.
   Source file Stdconffile.c (C:\grimjedi\Libs\Std\General\Stdconffile.c). */

undefined4 stdConffile_OpenMode(byte *param_1,undefined4 param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  bool bVar5;
  
  if (UINT_0080cbcc != 0) {
    stdConffile_Push();
  }
  pbVar4 = &DAT_004e7630;
  pbVar2 = param_1;
  do {
    bVar1 = *pbVar2;
    bVar5 = bVar1 < *pbVar4;
    if (bVar1 != *pbVar4) {
LAB_0047c822:
      iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
      goto LAB_0047c827;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar2[1];
    bVar5 = bVar1 < pbVar4[1];
    if (bVar1 != pbVar4[1]) goto LAB_0047c822;
    pbVar2 = pbVar2 + 2;
    pbVar4 = pbVar4 + 2;
  } while (bVar1 != 0);
  iVar3 = 0;
LAB_0047c827:
  if (iVar3 == 0) {
    UINT_0080cbd0 = 0;
  }
  else {
    UINT_0080cbd0 = (*g_pSvcMain->pFopen)(param_1,param_2);
    if ((int)UINT_0080cbd0 < 1) {
      UINT_0080cbd0 = 0;
      if (UINT_0080cbcc != 0) {
        stdConffile_Pop();
      }
      return 0;
    }
  }
  UINT_00900520 =
       (*g_pSvcMain->pAlloc)(0x400,s_C__grimjedi_Libs_Std_General_Std_004e7604,DAT_004e7600 + 0x1d);
  strncpy(&DAT_009004a0,param_1,0x7f);
  DAT_0090051f = 0;
  UINT_0080cbc8 = 0;
  UINT_0080cbcc = 1;
  return 1;
}
#endif


/* ---- 0x0047c8c0  stdConffile_Close ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Closes the current configuration file, frees the line buffer and pops the previous file if one
   was pushed. Source file Stdconffile.c (C:\grimjedi\Libs\Std\General\Stdconffile.c). */

void stdConffile_Close(void)

{
  if (UINT_0080cbcc != 0) {
    if (UINT_0080cbd0 != 0) {
      (*g_pSvcMain->pFclose)(UINT_0080cbd0);
    }
    UINT_0080cbd0 = 0;
    (*g_pSvcMain->pFree)(UINT_00900520);
    if (UINT_0080cbd8 != 0) {
      stdConffile_Pop();
      return;
    }
    UINT_0080cbcc = 0;
  }
  return;
}
#endif


/* ---- 0x0047c920  stdConffile_ReadLine ---- */
/* Reads the next line of the open stdConffile into the line buffer UINT_00900520 (skips ';' '#' and
   blank lines, strips '#' comments, lower-cases, joins lines ending in a backslash) */

undefined4 stdConffile_ReadLine(void)

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

/* ---- 0x0047ca00  stdConffile_Push ---- */
/* Saves the state of the open configuration file (name, line number, handle, line buffer) on the
   8-deep stack so that another file can be opened. Source file Stdconffile.c
   (C:\grimjedi\Libs\Std\General\Stdconffile.c). */

void stdConffile_Push(void)

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

/* ---- 0x0047ca90  stdConffile_Pop ---- */
/* Restores the configuration file state saved by stdConffile_Push. Source file Stdconffile.c
   (C:\grimjedi\Libs\Std\General\Stdconffile.c). */

void stdConffile_Pop(void)

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
