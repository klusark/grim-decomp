/* GRIMFANDANGO.EXE :: lab.c
 * functions 0x00480120 .. 0x00482020 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00480120  Res_FileCloseAll ---- */
/* Original name Res_FileCloseAll (the remaster's GrimFandango (Linux): aligned call in
   Res_SysShutdown, sputResource_CloseResources); was Lab_CloseAll. */

void __cdecl Res_FileCloseAll(void)

{
  while (g_pResFileList != (int *)0x0) {
    Res_FileClose((char *)(g_pResFileList + 2));
  }
  return;
}

/* ---- 0x00480360  Res_FileOpen ---- */
/* Original name Res_FileOpen (the remaster's GrimFandango (Linux): AddResourcePath's open call (the
   remaster inlined the LAB / directory variants)); was Lab_OpenByName. */

int __cdecl Res_FileOpen(char *path)

{
  char cVar1;
  Lab *pLVar2;
  void *pvVar3;
  uint uVar4;
  char *pcVar5;
  
  if (*path != '\0') {
    uVar4 = 0xffffffff;
    pcVar5 = path;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    if (path[~uVar4 - 2] != '\\') {
      pLVar2 = Lab_Open(path);
      return (int)pLVar2;
    }
  }
  pvVar3 = LabDir_Open(path);
  return (int)pvVar3;
}

/* ---- 0x004803a0  Res_FileClose ---- */
/* Closes an archive: unreferenced resources from it are freed, referenced ones get a private copy
   of their name and are detached Original name Res_FileClose (the remaster's GrimFandango (Linux):
   aligned call in Res_FileCloseAll); was Lab_Close. */

int __cdecl Res_FileClose(char *name)

{
  char cVar1;
  Resource *pRVar2;
  Resource *res;
  int *item;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  item = Lab_Find(name);
  pRVar2 = g_pNewestResNode;
  if (item != (int *)0x0) {
    while (res = pRVar2, res != (Resource *)0x0) {
      pRVar2 = res->pNext;
      if (res->pLab == item) {
        if ((res->pRefs == (ResRef *)0x0) && ((res->bFlags & 8) == 0)) {
          Res_CallUnload(res);
          Res_Unlink(res);
        }
        else if ((res->bFlags & 4) == 0) {
          uVar4 = 0xffffffff;
          pcVar6 = res->pName;
          do {
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar6 + 1;
          } while (cVar1 != '\0');
          pcVar3 = (char *)(**(code **)(g_dwResHS + 0x20))
                                     (~uVar4,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0x2fe);
          uVar4 = 0xffffffff;
          pcVar6 = res->pName;
          do {
            pcVar7 = pcVar6;
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            pcVar7 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar7;
          } while (cVar1 != '\0');
          uVar4 = ~uVar4;
          pcVar6 = pcVar7 + -uVar4;
          pcVar7 = pcVar3;
          for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
            pcVar6 = pcVar6 + 4;
            pcVar7 = pcVar7 + 4;
          }
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *pcVar7 = *pcVar6;
            pcVar6 = pcVar6 + 1;
            pcVar7 = pcVar7 + 1;
          }
          res->bFlags = res->bFlags | 4;
          res->pName = pcVar3;
          res->pLab = (void *)0x0;
        }
      }
    }
    if ((*(byte *)(item + 0x45) & 2) != 0) {
      Res_FClose(item[0x43]);
    }
    if (item[0x46] != 0) {
      (**(code **)(g_dwResHS + 0x24))(item[0x46]);
    }
    if (item[0x47] != 0) {
      (**(code **)(g_dwResHS + 0x24))(item[0x47]);
    }
    Lab_Unlink(item);
  }
  return 1;
}

/* ---- 0x004804c0  Res_FileMoveToFront ---- */
/* Makes the named archive the first one searched Original name Res_FileMoveToFront (the remaster's
   GrimFandango (Linux): AddResourcePath's call after each successful open); was Lab_MoveToFront. */

int __cdecl Res_FileMoveToFront(char *name)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = Lab_Find(name);
  if (piVar1 != (int *)0x0) {
    if ((int *)piVar1[1] != (int *)0x0) {
      *(int *)piVar1[1] = *piVar1;
    }
    if (*piVar1 != 0) {
      *(int *)(*piVar1 + 4) = piVar1[1];
    }
    if (g_pResFileList == piVar1) {
      g_pResFileList = (int *)*piVar1;
    }
    *piVar1 = (int)g_pResFileList;
    if (g_pResFileList != (int *)0x0) {
      g_pResFileList[1] = (int)piVar1;
    }
    piVar1[1] = 0;
    iVar2 = 1;
    g_pResFileList = piVar1;
  }
  return iVar2;
}

/* ---- 0x00481070  Lab_Find ---- */
void * __cdecl Lab_Find(char *name)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  int *piVar5;
  bool bVar6;
  
  piVar5 = g_pResFileList;
  if (g_pResFileList == (int *)0x0) {
    return (void *)0x0;
  }
  do {
    pbVar2 = (byte *)(piVar5 + 2);
    pbVar4 = (byte *)name;
    do {
      bVar1 = *pbVar2;
      bVar6 = bVar1 < *pbVar4;
      if (bVar1 != *pbVar4) {
LAB_004810b0:
        iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_004810b5;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar6 = bVar1 < pbVar4[1];
      if (bVar1 != pbVar4[1]) goto LAB_004810b0;
      pbVar2 = pbVar2 + 2;
      pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_004810b5:
    if (iVar3 == 0) {
      return piVar5;
    }
    piVar5 = (int *)*piVar5;
    if (piVar5 == (int *)0x0) {
      return (void *)0x0;
    }
  } while( true );
}

/* ---- 0x004813c0  Lab_Unlink ---- */
void __cdecl Lab_Unlink(int *item)

{
  if ((int *)item[1] != (int *)0x0) {
    *(int *)item[1] = *item;
  }
  if (*item != 0) {
    *(int *)(*item + 4) = item[1];
  }
  if (g_pResFileList == item) {
    g_pResFileList = (int *)*item;
  }
  Pool_Free(item);
  return;
}

/* ---- 0x00481630  res_FindInternalFile ---- */
/* Searches every open archive (or dev directory) for the file; fills a 0x210-byte entry {type,
   archiveFh, offset, size, inArchive, name} Original name res_FindInternalFile (the remaster's
   GrimFandango (Linux): aligned call in Res_FOpen, Res_FSize); was Lab_FindFile. */

int __cdecl res_FindInternalFile(char *name,LabFile *outEntry)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Lab *lab;
  uint hash;
  int iVar1;
  #define local_104 (*(byte (*)[260])(_frame + (0x120 - 0x104)))
  
  iVar1 = 0;
  hash = Res_HashName(name,(char *)local_104);
  lab = (Lab *)g_pResFileList;
  while ((lab != (Lab *)0x0 && (iVar1 == 0))) {
    if ((lab->field_0x114 & 2) == 0) {
      iVar1 = res_FindDirectoryEntry((int)lab,0,local_104,hash,outEntry);
    }
    else {
      iVar1 = Lab_FindEntry(lab,0,(char *)local_104,hash,outEntry);
    }
    lab = *(Lab **)lab;
  }
  return iVar1;
}
#undef local_104


/* ---- 0x004816b0  Lab_Open ---- */
/* Opens a .LAB archive, reads its directory with Lab_ReadDirectory */

Lab * __cdecl Lab_Open(char *name)

{
  char cVar1;
  int iVar2;
  Lab *lab;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  iVar2 = Res_FOpen(name,s_rb_004ddb18);
  lab = (Lab *)Lab_AllocRecord();
  if (iVar2 != 0) {
    uVar4 = 0xffffffff;
    pcVar6 = name;
    do {
      pcVar7 = pcVar6;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar7 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar6 = pcVar7 + -uVar4;
    pcVar7 = &lab->field_0x8;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
    lab->nFile = iVar2;
    uVar3 = (**(code **)(g_dwResHS + 0x50))(name);
    *(undefined4 *)&lab->field_0x110 = uVar3;
    *(undefined4 *)&lab->field_0x114 = 2;
    lab->pEntries = (LabEntry *)0x0;
    lab->pNames = (char *)0x0;
    iVar2 = Lab_ReadDirectory(lab);
    if (iVar2 != 1) {
      Lab_Unlink((int *)lab);
      lab = (Lab *)0x0;
    }
  }
  return lab;
}

/* ---- 0x00481750  Lab_AllocRecord ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Takes a 0x120-byte archive record from g_pLabPool and links it at the head of g_pLabList */

int * Lab_AllocRecord(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  piVar1 = Memory_AllocFixed((int *)g_dwResFilePool);
  if (piVar1 == (int *)0x0) {
    return (int *)0x0;
  }
  piVar3 = piVar1;
  for (iVar2 = 0x48; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar3 = 0;
    piVar3 = piVar3 + 1;
  }
  *piVar1 = (int)g_pResFileList;
  if (g_pResFileList != (int *)0x0) {
    g_pResFileList[1] = (int)piVar1;
  }
  piVar1[1] = 0;
  g_pResFileList = piVar1;
  return piVar1;
}

/* ---- 0x004817a0  Lab_ReadDirectory ---- */
/* Parses the LABN header (version, entry count, name table size) and the 16-byte entries into
   0x1c-byte records {nameHash, name, ?, fourcc, a, b, 0}; names are hashed with Res_HashName */

int __cdecl Lab_ReadDirectory(Lab *lab)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Lab *pLVar1;
  Lab *n;
  uint uVar2;
  LabEntry *pLVar3;
  char *pcVar4;
  uint uVar5;
  Lab *pLVar6;
  int iVar7;
  Lab *pLVar8;
  uint local_c;
  #define local_8 (*(char (*)[8])(_frame + (0x20 - 0x8)))
  
  pLVar1 = lab;
  uVar2 = Res_FRead(lab->nFile,local_8,4);
  if ((((uVar2 == 4) && (uVar2 = strncmp(local_8,s_LABN_004e7af0,4), uVar2 == 0)) &&
      (uVar2 = Res_FRead(pLVar1->nFile,&lab,4), uVar2 == 4)) &&
     (((lab < (Lab *)0x10001 && (uVar2 = Res_FRead(pLVar1->nFile,&lab,4), pLVar8 = lab, uVar2 == 4))
      && (uVar2 = Res_FRead(pLVar1->nFile,&lab,4), n = lab, uVar2 == 4)))) {
    pLVar3 = (LabEntry *)
             (**(code **)(g_dwResHS + 0x20))
                       ((int)&pLVar8->field_0x1 * 0x1c,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,
                        0xbdc);
    pLVar1->pEntries = pLVar3;
    if (pLVar3 != (LabEntry *)0x0) {
      pcVar4 = (char *)(**(code **)(g_dwResHS + 0x20))
                                 (n,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xbdf);
      pLVar1->pNames = pcVar4;
      if (pcVar4 != (char *)0x0) {
        pLVar3 = pLVar1->pEntries;
        uVar2 = 0;
        if (pLVar8 != (Lab *)0x0) {
          do {
            uVar5 = Res_FRead(pLVar1->nFile,&lab,4);
            if (uVar5 != 4) goto LAB_00481994;
            pLVar3->pName = pLVar1->pNames + (int)&lab->field_0x0;
            uVar5 = Res_FRead(pLVar1->nFile,&lab,4);
            if (uVar5 != 4) goto LAB_00481994;
            pLVar3->nOffset = (int)lab;
            uVar5 = Res_FRead(pLVar1->nFile,&lab,4);
            if (uVar5 != 4) goto LAB_00481994;
            pLVar3->nSize = (int)lab;
            uVar5 = Res_FRead(pLVar1->nFile,&lab,4);
            if (uVar5 != 4) goto LAB_00481994;
            *(undefined4 *)&pLVar3->field_0x18 = 0;
            pLVar3->dwFourcc = (uint)lab;
            uVar2 = uVar2 + 1;
            pLVar3 = pLVar3 + 1;
          } while (uVar2 < pLVar8);
        }
        for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1) {
          pLVar3->dwHash = 0;
          pLVar3 = (LabEntry *)&pLVar3->pName;
        }
        pLVar6 = (Lab *)Res_FRead(pLVar1->nFile,pLVar1->pNames,(uint)n);
        if (pLVar6 == n) {
          pLVar3 = pLVar1->pEntries;
          for (; pLVar8 != (Lab *)0x0; pLVar8 = (Lab *)((int)&pLVar8[-1].pNames + 3)) {
            uVar2 = Res_HashName(pLVar3->pName,pLVar3->pName);
            pLVar3->dwHash = uVar2;
            pLVar3 = pLVar3 + 1;
          }
          return 1;
        }
      }
    }
  }
LAB_00481994:
  if (pLVar1->pEntries != (LabEntry *)0x0) {
    (**(code **)(g_dwResHS + 0x24))(pLVar1->pEntries);
  }
  if (pLVar1->pNames != (char *)0x0) {
    (**(code **)(g_dwResHS + 0x24))(pLVar1->pNames);
  }
  return 0;
}
#undef local_8


/* ---- 0x00481a00  Lab_FindEntry ---- */
/* Hash + name match inside one archive; remembers the hit in the 16-slot recent-lookup ring */

int __cdecl Lab_FindEntry(Lab *lab,int fourcc,char *lowerName,uint hash,LabFile *outEntry)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  LabEntry *pLVar7;
  byte *pbVar8;
  char *pcVar9;
  char *pcVar10;
  bool bVar11;
  
  pLVar7 = lab->pEntries;
  pbVar3 = (byte *)pLVar7->pName;
  if (pbVar3 == (byte *)0x0) {
    return 0;
  }
  do {
    if ((((fourcc == 0) || (pLVar7->dwFourcc == 0)) || (pLVar7->dwFourcc == fourcc)) &&
       (pbVar8 = (byte *)lowerName, pLVar7->dwHash == hash)) {
      do {
        bVar2 = *pbVar3;
        bVar11 = bVar2 < *pbVar8;
        if (bVar2 != *pbVar8) {
LAB_00481a61:
          iVar4 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
          goto LAB_00481a66;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar3[1];
        bVar11 = bVar2 < pbVar8[1];
        if (bVar2 != pbVar8[1]) goto LAB_00481a61;
        pbVar3 = pbVar3 + 2;
        pbVar8 = pbVar8 + 2;
      } while (bVar2 != 0);
      iVar4 = 0;
LAB_00481a66:
      if (iVar4 == 0) {
        *(LabEntry **)(&g_aFoundFiles + g_dwLastFound * 4) = pLVar7;
        *(Lab **)(&g_aFoundFileNodes + g_dwLastFound * 4) = lab;
        uVar5 = 0xffffffff;
        g_dwLastFound = g_dwLastFound + 1 & 0xf;
        pcVar9 = pLVar7->pName;
        break;
      }
    }
    pbVar3 = (byte *)pLVar7[1].pName;
    pLVar7 = pLVar7 + 1;
    if (pbVar3 == (byte *)0x0) {
      return 0;
    }
  } while( true );
  while( true ) {
    uVar5 = uVar5 - 1;
    pcVar10 = pcVar9 + 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar10;
    if (cVar1 == '\0') break;
    pcVar10 = pcVar9;
    if (uVar5 == 0) break;
  }
  uVar5 = ~uVar5;
  pcVar9 = pcVar10 + -uVar5;
  pcVar10 = outEntry->aName;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
    pcVar10 = pcVar10 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar10 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    pcVar10 = pcVar10 + 1;
  }
  outEntry->dwFourcc = fourcc;
  outEntry->nFile = lab->nFile;
  outEntry->nSize = pLVar7->nSize;
  outEntry->nOffset = pLVar7->nOffset;
  outEntry->nInLab = 1;
  return 1;
}

/* ---- 0x00482020  Lab_ReadRaw ---- */
/* Reads n bytes at offset inside an archive-backed file entry, clamped to the entry size */

int __cdecl Lab_ReadRaw(ResFile *file,void *buf,int offset,int n)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = file->nLength;
  if (iVar1 <= offset) {
    return 0;
  }
  if (iVar1 < n + offset) {
    n = iVar1 - offset;
  }
  Res_FSeek(file->dwHandle,file->nBase + offset,0);
  uVar2 = Res_FRead(file->dwHandle,buf,n);
  return uVar2;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char grim_def_s_LABN_004e7af0[8] __asm__("_s_LABN_004e7af0");
/* 0x004e7af0, 8 bytes */ /* loose */ char grim_def_s_LABN_004e7af0[8] __asm__("_s_LABN_004e7af0") = "LABN";
