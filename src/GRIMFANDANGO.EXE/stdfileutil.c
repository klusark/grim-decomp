/* GRIMFANDANGO.EXE :: stdfileutil.c
 * functions 0x00473430 .. 0x004c12d0 (18 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00473430  stdFileOpen ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name stdFileOpen (the remaster's GrimFandango (Linux): the std.c host file service in
   the same table order (stdFileOpen .. stdFilePrintf); fopen wrapper in both builds); was
   stdFile_Open. */

undefined * __cdecl stdFileOpen(uint param_1,uint param_2)

{
  undefined *puVar1;
  
  puVar1 = fopen(param_1,param_2);
  return puVar1;
}
#endif


/* ---- 0x00473450  stdFileClose ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name stdFileClose (the remaster's GrimFandango (Linux): the std.c host file service
   after stdFileOpen; fclose wrapper in both builds); was stdFile_Close. */

void stdFileClose(undefined4 param_1)

{
  fclose(param_1);
  return;
}
#endif


/* ---- 0x00473460  stdFileRead ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* GrimServices.pFread of the platform table: fread(buf, 1, n, file). Original name stdFileRead (the
   remaster's GrimFandango (Linux): same body (fread(buf, 1, n, fh))); was stdFile_Read. */

void stdFileRead(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  fread(param_2,1,param_3,param_1);
  return;
}
#endif


/* ---- 0x00473480  stdFileWrite ---- */
/* Original name stdFileWrite (the remaster's GrimFandango (Linux): the std.c host file service
   after stdFileRead; fwrite wrapper in both builds); was stdFile_Write. */

void stdFileWrite(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  fwrite(param_2,1,param_3,param_1);
  return;
}

/* ---- 0x004734a0  stdFileGets ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* GrimServices.pFgets of the platform table: fgets. Original name stdFileGets (the remaster's
   GrimFandango (Linux): same body (fgets(buf, n, fh))); was stdFile_Gets. */

void stdFileGets(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  fgets(param_2,param_3,param_1);
  return;
}
#endif


/* ---- 0x004734c0  stdFileGetws ---- */
/* Original name stdFileGetws (the remaster's GrimFandango (Linux): same body (fgetws(buf, n, fh));
   between stdFileGets and stdFeof in both builds); was FUN_004734c0. */

void stdFileGetws(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_004adef0(param_2,param_3,param_1);
  return;
}

/* ---- 0x004734e0  stdFeof ---- */
/* GrimServices.pFeof of the platform table: feof. Original name stdFeof (the remaster's
   GrimFandango (Linux): the std.c end-of-file service after stdFileGetws in both builds); was
   stdFile_Eof. */

uint stdFeof(int param_1)

{
  return *(uint *)(param_1 + 0xc) & 0x10;
}

/* ---- 0x004734f0  stdFtell ---- */
/* Original name stdFtell (the remaster's GrimFandango (Linux): the std.c tell service after stdFeof
   in both builds); was stdFile_Tell. */

undefined * __cdecl stdFtell(uint param_1)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)ftell(param_1);
  return puVar1;
}

/* ---- 0x00473500  stdFseek ---- */
/* Original name stdFseek (the remaster's GrimFandango (Linux): the std.c seek service after
   stdFtell in both builds); was stdFile_Seek. */

void stdFseek(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  fseek(param_1,param_2,param_3);
  return;
}

/* ---- 0x00473520  stdFileSize ---- */
/* GrimServices.pFileSize of the platform table: opens the file, seeks to the end and returns ftell.
   Original name stdFileSize (the remaster's GrimFandango (Linux): same body (open "rb", seek to the
   end, tell, close)); was stdFile_Size. */

undefined * stdFileSize(uint param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = stdFileOpen(param_1,IMG_ADDR(0x004ddb18));
  if (puVar1 == (undefined *)0x0) {
    return (undefined *)0x0;
  }
  stdFseek(puVar1,0,2);
  puVar2 = stdFtell((uint)puVar1);
  stdFileClose(puVar1);
  return puVar2;
}

/* ---- 0x00473570  stdFilePrintf ---- */
/* GrimServices.pFprintf of the platform table: formats into a 0x400-byte buffer and writes it.
   Original name stdFilePrintf (the remaster's GrimFandango (Linux): same body (format into the
   static printBuffer of 0x400 bytes, write it to the file)); was stdFile_Printf. */

undefined4 stdFilePrintf(undefined4 param_1,char *param_2)

{
  int iVar1;
  
  iVar1 = _snprintf(&DAT_007f6090,0x400,param_2,&STACK0X(0x0000000c));
  stdFileWrite(param_1,&DAT_007f6090,iVar1);
  return 0;
}

/* ---- 0x004735f0  stdFGetc ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name stdFGetc (the remaster's GrimFandango (Linux): aligned call in stdGif_Load,
   stdLbm_Load, stdPcx_Load); was stdFile_ReadByte. */

uint stdFGetc(uint param_1)

{
  (*g_pStd_HS->pFread)(param_1,&param_1,1);
  return param_1 & 0xff;
}
#endif


/* ---- 0x00473610  stdFPutc ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name stdFPutc (the remaster's GrimFandango (Linux): aligned call in stdPcx_Write); was
   stdFile_WriteByte. */

void stdFPutc(undefined4 param_1,undefined4 param_2)

{
  (*g_pStd_HS->pFwrite)(param_2,&param_1,1);
  return;
}
#endif


/* ---- 0x00473a00  LzssDecompress ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* LZSS decompressor used for compressed (type 2) surfaces; returns the decompressed size Original
   name LzssDecompress (the remaster's GrimFandango (Linux): the decompressor (dst, src, size) of
   stdDisplay_VBufferDeCompress and _DeCompressTo in both builds; here the loop is a separate helper
   (stdCompress_DecompressLoop), the remaster adds a cache); was stdCompress_Decompress. */

int __cdecl LzssDecompress(void *dst,void *src,int srcSize)

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
           (*g_pStd_HS->pAlloc)(0x150,s_C__grimjedi_Libs_Std_General_Std_004f11d0,DAT_004f11c0 + 3);
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
      (*g_pStd_HS->pFree)(param_1);
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
