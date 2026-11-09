/* GRIMFANDANGO.EXE :: stdfileutil.c
 * functions 0x00473430 .. 0x004c12d0 (18 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00473430  stdFile_Open ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined * __cdecl stdFile_Open(uint param_1,uint param_2)

{
  undefined *puVar1;
  
  puVar1 = fopen(param_1,param_2);
  return puVar1;
}
#endif


/* ---- 0x00473450  stdFile_Close ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void stdFile_Close(undefined4 param_1)

{
  fclose(param_1);
  return;
}
#endif


/* ---- 0x00473460  stdFile_Read ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* GrimServices.pFread of the platform table: fread(buf, 1, n, file). */

void stdFile_Read(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  fread(param_2,1,param_3,param_1);
  return;
}
#endif


/* ---- 0x00473480  stdFile_Write ---- */
void stdFile_Write(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  fwrite(param_2,1,param_3,param_1);
  return;
}

/* ---- 0x004734a0  stdFile_Gets ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* GrimServices.pFgets of the platform table: fgets. */

void stdFile_Gets(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  fgets(param_2,param_3,param_1);
  return;
}
#endif


/* ---- 0x004734c0  FUN_004734c0 ---- */
void FUN_004734c0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_004adef0(param_2,param_3,param_1);
  return;
}

/* ---- 0x004734e0  stdFile_Eof ---- */
/* GrimServices.pFeof of the platform table: feof. */

uint stdFile_Eof(int param_1)

{
  return *(uint *)(param_1 + 0xc) & 0x10;
}

/* ---- 0x004734f0  stdFile_Tell ---- */
undefined * __cdecl stdFile_Tell(uint param_1)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)ftell(param_1);
  return puVar1;
}

/* ---- 0x00473500  stdFile_Seek ---- */
void stdFile_Seek(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  fseek(param_1,param_2,param_3);
  return;
}

/* ---- 0x00473520  stdFile_Size ---- */
/* GrimServices.pFileSize of the platform table: opens the file, seeks to the end and returns ftell.
    */

undefined * stdFile_Size(uint param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = stdFile_Open(param_1,IMG_ADDR(0x004ddb18));
  if (puVar1 == (undefined *)0x0) {
    return (undefined *)0x0;
  }
  stdFile_Seek(puVar1,0,2);
  puVar2 = stdFile_Tell((uint)puVar1);
  stdFile_Close(puVar1);
  return puVar2;
}

/* ---- 0x00473570  stdFile_Printf ---- */
/* GrimServices.pFprintf of the platform table: formats into a 0x400-byte buffer and writes it. */

undefined4 stdFile_Printf(undefined4 param_1,char *param_2)

{
  int iVar1;
  
  iVar1 = _snprintf(&DAT_007f6090,0x400,param_2,&STACK0X(0x0000000c));
  stdFile_Write(param_1,&DAT_007f6090,iVar1);
  return 0;
}

/* ---- 0x004735f0  stdFile_ReadByte ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
uint stdFile_ReadByte(uint param_1)

{
  (*g_pSvcMain->pFread)(param_1,&param_1,1);
  return param_1 & 0xff;
}
#endif


/* ---- 0x00473610  stdFile_WriteByte ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void stdFile_WriteByte(undefined4 param_1,undefined4 param_2)

{
  (*g_pSvcMain->pFwrite)(param_2,&param_1,1);
  return;
}
#endif


/* ---- 0x00473a00  stdCompress_Decompress ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* LZSS decompressor used for compressed (type 2) surfaces; returns the decompressed size */

int __cdecl stdCompress_Decompress(void *dst,void *src,int srcSize)

{
  PTR_007fead8 = src;
  _DAT_007feb58 = 0;
  UINT_007fa7ac = 0;
  _DAT_007feb54 = srcSize;
  UINT_007feae4 = (uint)dst;
  stdCompress_DecompressLoop();
  return UINT_007fa7ac;
}

/* ---- 0x00473b60  stdCompress_DecompressLoop ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void stdCompress_DecompressLoop(void)

{
  ushort *puVar1;
  ushort *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  
  uVar3 = (uint)(ushort)*PTR_007fead8;
  puVar1 = (ushort *)((int)PTR_007fead8 + 2);
  iVar7 = 0x10;
  pbVar6 = (byte *)UINT_007feae4;
  do {
    while( true ) {
      uVar4 = uVar3 & 1;
      uVar3 = (int)uVar3 >> 1;
      iVar7 = iVar7 + -1;
      puVar2 = puVar1;
      if (iVar7 == 0) {
        iVar7 = 0x10;
        uVar3 = (uint)*puVar1;
        puVar2 = puVar1 + 1;
      }
      if (uVar4 != 1) break;
      *pbVar6 = (byte)*puVar2;
      pbVar6 = pbVar6 + 1;
      puVar1 = (ushort *)((int)puVar2 + 1);
    }
    uVar4 = uVar3 & 1;
    uVar3 = (int)uVar3 >> 1;
    iVar7 = iVar7 + -1;
    if (iVar7 == 0) {
      iVar7 = 0x10;
      uVar3 = (uint)*puVar2;
      puVar2 = puVar2 + 1;
    }
    if (uVar4 == 0) {
      uVar5 = uVar3 & 1;
      uVar4 = (int)uVar3 >> 1;
      iVar7 = iVar7 + -1;
      if (iVar7 == 0) {
        iVar7 = 0x10;
        uVar4 = (uint)*puVar2;
        puVar2 = puVar2 + 1;
      }
      uVar3 = (int)uVar4 >> 1;
      iVar7 = iVar7 + -1;
      if (iVar7 == 0) {
        iVar7 = 0x10;
        uVar3 = (uint)*puVar2;
        puVar2 = puVar2 + 1;
      }
      iVar8 = (uVar5 * 2 | uVar4 & 1) + 3;
      uVar4 = (byte)*puVar2 | 0xffffff00;
      puVar1 = (ushort *)((int)puVar2 + 1);
    }
    else {
      puVar1 = puVar2 + 1;
      iVar8 = (*(byte *)((int)puVar2 + 1) & 0xf) + 3;
      uVar4 = (uint)(byte)*puVar2 | ((*(byte *)((int)puVar2 + 1) & 0xf0) - 0x100) * 0x10;
      if (iVar8 == 3) {
        iVar8 = (byte)*puVar1 + 1;
        puVar1 = (ushort *)((int)puVar2 + 3);
        if (iVar8 == 1) {
          UINT_007fa7ac = (int)pbVar6 - UINT_007feae4;
          _DAT_007feb58 = (int)puVar1 - (int)PTR_007fead8;
          return;
        }
      }
    }
    pbVar9 = pbVar6 + uVar4;
    for (; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pbVar6 = *pbVar9;
      pbVar6 = pbVar6 + 1;
      pbVar9 = pbVar9 + 1;
    }
  } while( true );
}

/* ---- 0x004c1170  stdFileUtil_NewFind ---- */
/* Std/General/Stdfileutil.c directory search (same shape as DirScan_Create) */

void * __cdecl stdFileUtil_NewFind(char *dir,int mode,char *ext)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  
  puVar2 = (undefined4 *)
           (*g_pSvcMain->pAlloc)(0x150,s_C__grimjedi_Libs_Std_General_Std_004f11d0,DAT_004f11c0 + 3)
  ;
  if (puVar2 == (undefined4 *)0x0) {
    return (void *)0x0;
  }
  puVar6 = puVar2;
  for (iVar3 = 0x54; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  uVar4 = 0xffffffff;
  puVar2[2] = 0;
  puVar2[0x53] = mode;
  do {
    pcVar7 = dir;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = dir + 1;
    cVar1 = *dir;
    dir = pcVar7;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar10 = (char *)(puVar2 + 0xe);
  pcVar7 = pcVar7 + -uVar4;
  pcVar9 = pcVar10;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  switch(mode) {
  case 0:
  case 1:
  case 2:
    ext = &DAT_004f11c8;
    break;
  case 3:
    iVar3 = strchr(ext,0x2e);
    pcVar7 = &DAT_004f11c4;
    if (iVar3 != 0) {
      pcVar7 = &DAT_004e9c60;
    }
    uVar4 = 0xffffffff;
    do {
      pcVar9 = pcVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar3 = -1;
    pcVar7 = pcVar10;
    do {
      pcVar8 = pcVar7;
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    pcVar7 = pcVar9 + -uVar4;
    pcVar9 = pcVar8 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
    break;
  case 4:
    uVar4 = 0xffffffff;
    do {
      pcVar7 = ext;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar7 = ext + 1;
      cVar1 = *ext;
      ext = pcVar7;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar7 = pcVar7 + -uVar4;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar10 = pcVar10 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar10 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar10 = pcVar10 + 1;
    }
    return puVar2;
  default:
    goto switchD_004c11e0_default;
  }
  uVar4 = 0xffffffff;
  do {
    pcVar7 = ext;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = ext + 1;
    cVar1 = *ext;
    ext = pcVar7;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar3 = -1;
  do {
    pcVar9 = pcVar10;
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar9 = pcVar10 + 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar9;
  } while (cVar1 != '\0');
  pcVar7 = pcVar7 + -uVar4;
  pcVar10 = pcVar9 + -1;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar10 = pcVar10 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar10 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar10 = pcVar10 + 1;
  }
switchD_004c11e0_default:
  return puVar2;
}

/* ---- 0x004c12a0  stdFileUtil_DisposeFind ---- */
void stdFileUtil_DisposeFind(int param_1)

{
  if (param_1 != 0) {
    if (*(int *)(param_1 + 8) != 0) {
      FindClose(*(int *)(param_1 + 8));
      *(undefined4 *)(param_1 + 8) = 0;
    }
    if (param_1 != 0) {
      (*g_pSvcMain->pFree)(param_1);
    }
  }
  return;
}

/* ---- 0x004c12d0  stdFileUtil_FindNext ---- */
int __cdecl stdFileUtil_FindNext(void *find,void *outEntry)

{
  uint *a2;
  char cVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  
  if (find == (void *)0x0) {
    return 0;
  }
  do {
    a2 = (uint *)((int)find + 0xc);
    if (*(int *)((int)find + 8) == 0) {
      iVar3 = FindFirstFileA((int)find + 0x38,(int)a2);
      *(int *)((int)find + 8) = iVar3;
      uVar6 = (uint)(iVar3 != -1);
    }
    else {
      uVar6 = FindNextFileA(*(int *)((int)find + 8),(int)a2);
    }
    if (uVar6 == 0) {
LAB_004c1378:
      bVar2 = false;
    }
    else {
      *(uint *)((int)outEntry + 0x104) = *a2 & 0x10;
      *(undefined4 *)((int)outEntry + 0x108) = *(undefined4 *)((int)find + 0x20);
      uVar4 = 0xffffffff;
      pcVar7 = (char *)((int)find + 0x38);
      do {
        pcVar8 = pcVar7;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar8 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar8;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      pcVar7 = pcVar8 + -uVar4;
      pcVar8 = outEntry;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar8 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar8 = pcVar8 + 1;
      }
      if ((*(int *)((int)find + 0x14c) == 1) && (*(int *)((int)outEntry + 0x104) != 0)) {
        uVar6 = 0;
        bVar2 = true;
      }
      else {
        if ((*(int *)((int)find + 0x14c) != 2) || (*(int *)((int)outEntry + 0x104) != 0))
        goto LAB_004c1378;
        uVar6 = 0;
        bVar2 = true;
      }
    }
    if (!bVar2) {
      return uVar6;
    }
  } while( true );
}
