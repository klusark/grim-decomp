/* GRIMFANDANGO.EXE :: stdconffile.c
 * functions 0x0047c7c0 .. 0x0047ca90 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047c7c0  stdConffile_Open ---- */
/* Opens a text configuration file for reading (stdConffile_OpenMode with mode "r"). Source file
   Stdconffile.c (C:\grimjedi\Libs\Std\General\Stdconffile.c). Original name stdConffile_Open (the
   remaster's GrimFandango (Linux): the only unmatched caller of stdConffile_OpenMode; 4 matched
   neighbours agree, 0 disagree); was stdConffile_OpenRead. */

uint __cdecl stdConffile_Open(uint param_1)

{
  uint uVar1;
  
  uVar1 = stdConffile_OpenMode((byte *)param_1,((unsigned)(uintptr_t)&DAT_004dda54));
  return uVar1;
}

/* ---- 0x0047c7e0  stdConffile_OpenMode ---- */
/* Opens a configuration file through the file services (pFopen); pushes the currently open file
   first (stdConffile_Push) and allocates the 0x400-byte line buffer. The name 'none' means no file.
   Source file Stdconffile.c (C:\grimjedi\Libs\Std\General\Stdconffile.c). */

uint __cdecl stdConffile_OpenMode(byte *param_1,uint param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  bool bVar5;
  
  if (g_dwStdConffile_bOpen != 0) {
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
    UINT_0080cbd0 = (*g_pStd_HS->pFopen)(param_1,param_2);
    if ((int)UINT_0080cbd0 < 1) {
      UINT_0080cbd0 = 0;
      if (g_dwStdConffile_bOpen != 0) {
        stdConffile_Pop();
      }
      return 0;
    }
  }
  g_dwStdConffile_aLine =
       (*g_pStd_HS->pAlloc)(0x400,s_C__grimjedi_Libs_Std_General_Std_004e7604,DAT_004e7600 + 0x1d);
  strncpy((uint *)&g_bStdConffile_pFilename,(uint *)param_1,0x7f);
  DAT_0090051f = 0;
  g_dwStdConffile_linenum = 0;
  g_dwStdConffile_bOpen = 1;
  return 1;
}

/* ---- 0x0047c8c0  stdConffile_Close ---- */
/* Closes the current configuration file, frees the line buffer and pops the previous file if one
   was pushed. Source file Stdconffile.c (C:\grimjedi\Libs\Std\General\Stdconffile.c). */

void __cdecl stdConffile_Close(void)

{
  if (g_dwStdConffile_bOpen != 0) {
    if (UINT_0080cbd0 != 0) {
      (*g_pStd_HS->pFclose)(UINT_0080cbd0);
    }
    UINT_0080cbd0 = 0;
    (*g_pStd_HS->pFree)(g_dwStdConffile_aLine);
    if (g_dwStackLevel != 0) {
      stdConffile_Pop();
      return;
    }
    g_dwStdConffile_bOpen = 0;
  }
  return;
}

/* ---- 0x0047c920  stdConffile_ReadLine ---- */
/* Renamed from Std_ParseCommandLine: it does not tokenise a command line, it reads the next line of
   the open stdConffile into the line buffer g_dwStdConffile_aLine (skips ';' '#' and blank lines,
   strips '#' comments, lower-cases, joins lines that end in a backslash). Source file Stdconffile.c
   (C:\grimjedi\Libs\Std\General\Stdconffile.c). */

uint __cdecl stdConffile_ReadLine(void)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  char *pcVar8;
  
  bVar2 = false;
  iVar6 = 0x3ff;
  puVar7 = (uint *)g_dwStdConffile_aLine;
  do {
    if (iVar6 == 0) {
      return 1;
    }
    iVar3 = (*g_pStd_HS->pFgets)(UINT_0080cbd0,puVar7,iVar6);
    if (iVar3 == 0) {
      return 0;
    }
    g_dwStdConffile_linenum = g_dwStdConffile_linenum + 1;
    cVar1 = (char)*puVar7;
    if ((((cVar1 != ';') && (cVar1 != '#')) && (cVar1 != '\n')) && (cVar1 != '\r')) {
      puVar4 = strchr(puVar7,'#');
      if (puVar4 != (uint *)0x0) {
        *(undefined1 *)puVar4 = 0;
      }
      _strlwr((char *)puVar7);
      uVar5 = 0xffffffff;
      pcVar8 = (char *)g_dwStdConffile_aLine;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      if (*(char *)((uVar5 - 3) + g_dwStdConffile_aLine) == '\\') {
        iVar6 = 0x400 - (uVar5 - 1);
        puVar7 = (uint *)((uVar5 - 3) + g_dwStdConffile_aLine);
      }
      else {
        cVar1 = *(char *)((uVar5 - 2) + g_dwStdConffile_aLine);
        bVar2 = true;
        if ((cVar1 == '\r') || (cVar1 == '\n')) {
          *(undefined1 *)((uVar5 - 2) + g_dwStdConffile_aLine) = 0;
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

void __cdecl stdConffile_Push(void)

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
  pcVar5 = &g_bStdConffile_pFilename;
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
  pcVar7 = &DAT_00806c88 + g_dwStackLevel * 0x80;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar3 = g_dwStdConffile_linenum, uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar7 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar7 = pcVar7 + 1;
  }
  g_dwStdConffile_linenum = 0;
  *(uint *)(&DAT_008076d8 + g_dwStackLevel * 4) = uVar3;
  *(uint *)(&DAT_0080c778 + g_dwStackLevel * 4) = UINT_0080cbd0;
  uVar2 = g_dwStdConffile_aLine;
  UINT_0080cbd0 = 0;
  puVar6 = &UINT_00900080;
  puVar8 = (uint *)(&DAT_00807728 + g_dwStackLevel * 0x404);
  for (iVar4 = 0x101; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  *(uint *)(&DAT_00807688 + g_dwStackLevel * 4) = uVar2;
  g_dwStackLevel = g_dwStackLevel + 1;
  return;
}

/* ---- 0x0047ca90  stdConffile_Pop ---- */
/* Restores the configuration file state saved by stdConffile_Push. Source file Stdconffile.c
   (C:\grimjedi\Libs\Std\General\Stdconffile.c). */

void __cdecl stdConffile_Pop(void)

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
  
  if (g_dwStackLevel != 0) {
    uVar5 = g_dwStackLevel - 1;
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
    pcVar8 = &g_bStdConffile_pFilename;
    g_dwStackLevel = uVar5;
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
    g_dwStdConffile_linenum = *(uint *)(&DAT_008076d8 + uVar5 * 4);
    g_dwStdConffile_aLine = *(uint *)(&DAT_00807688 + uVar5 * 4);
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
