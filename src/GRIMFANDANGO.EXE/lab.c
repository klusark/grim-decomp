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
  void *pvVar2;
  uint uVar3;
  char *pcVar4;
  
  if (*path != '\0') {
    uVar3 = 0xffffffff;
    pcVar4 = path;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    if (path[~uVar3 - 2] != '\\') {
      pvVar2 = Lab_Open(path);
      return (int)pvVar2;
    }
  }
  pvVar2 = LabDir_Open(path);
  return (int)pvVar2;
}

/* ---- 0x004803a0  Res_FileClose ---- */
/* Closes an archive: unreferenced resources from it are freed, referenced ones get a private copy
   of their name and are detached Original name Res_FileClose (the remaster's GrimFandango (Linux):
   aligned call in Res_FileCloseAll); was Lab_Close. */

int __cdecl Res_FileClose(char *name)

{
  char cVar1;
  int *piVar2;
  int *res;
  int *piVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  
  piVar3 = Lab_Find(name);
  piVar2 = g_pNewestResNode;
  if (piVar3 != (int *)0x0) {
    while (res = piVar2, res != (int *)0x0) {
      piVar2 = (int *)*res;
      if ((int *)res[8] == piVar3) {
        if ((res[9] == 0) && ((*(byte *)(res + 7) & 8) == 0)) {
          Res_CallUnload(res);
          Res_Unlink(res);
        }
        else if ((*(byte *)(res + 7) & 4) == 0) {
          uVar5 = 0xffffffff;
          pcVar7 = (char *)res[2];
          do {
            if (uVar5 == 0) break;
            uVar5 = uVar5 - 1;
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          pcVar4 = (char *)(**(code **)(g_dwResHS + 0x20))
                                     (~uVar5,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0x2fe);
          uVar5 = 0xffffffff;
          pcVar7 = (char *)res[2];
          do {
            pcVar8 = pcVar7;
            if (uVar5 == 0) break;
            uVar5 = uVar5 - 1;
            pcVar8 = pcVar7 + 1;
            cVar1 = *pcVar7;
            pcVar7 = pcVar8;
          } while (cVar1 != '\0');
          uVar5 = ~uVar5;
          pcVar7 = pcVar8 + -uVar5;
          pcVar8 = pcVar4;
          for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
            pcVar7 = pcVar7 + 4;
            pcVar8 = pcVar8 + 4;
          }
          for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
            *pcVar8 = *pcVar7;
            pcVar7 = pcVar7 + 1;
            pcVar8 = pcVar8 + 1;
          }
          *(byte *)(res + 7) = *(byte *)(res + 7) | 4;
          res[2] = (int)pcVar4;
          res[8] = 0;
        }
      }
    }
    if ((*(byte *)(piVar3 + 0x45) & 2) != 0) {
      Res_FClose(piVar3[0x43]);
    }
    if (piVar3[0x46] != 0) {
      (**(code **)(g_dwResHS + 0x24))(piVar3[0x46]);
    }
    if (piVar3[0x47] != 0) {
      (**(code **)(g_dwResHS + 0x24))(piVar3[0x47]);
    }
    Lab_Unlink(piVar3);
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
void __cdecl Lab_Unlink(int *param_1)

{
  if ((int *)param_1[1] != (int *)0x0) {
    *(int *)param_1[1] = *param_1;
  }
  if (*param_1 != 0) {
    *(int *)(*param_1 + 4) = param_1[1];
  }
  if (g_pResFileList == param_1) {
    g_pResFileList = (int *)*param_1;
  }
  Pool_Free(param_1);
  return;
}

/* ---- 0x00481630  res_FindInternalFile ---- */
/* Searches every open archive (or dev directory) for the file; fills a 0x210-byte entry {type,
   archiveFh, offset, size, inArchive, name} Original name res_FindInternalFile (the remaster's
   GrimFandango (Linux): aligned call in Res_FOpen, Res_FSize); was Lab_FindFile. */

int __cdecl res_FindInternalFile(char *name,void *outEntry)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *lab;
  uint hash;
  int iVar1;
  #define local_104 (*(byte (*)[260])(_frame + (0x120 - 0x104)))
  
  iVar1 = 0;
  hash = Res_HashName(name,(char *)local_104);
  lab = g_pResFileList;
  while ((lab != (int *)0x0 && (iVar1 == 0))) {
    if ((*(byte *)(lab + 0x45) & 2) == 0) {
      iVar1 = res_FindDirectoryEntry((int)lab,0,local_104,hash,outEntry);
    }
    else {
      iVar1 = Lab_FindEntry(lab,0,(char *)local_104,hash,outEntry);
    }
    lab = (int *)*lab;
  }
  return iVar1;
}
#undef local_104


/* ---- 0x004816b0  Lab_Open ---- */
/* Opens a .LAB archive, reads its directory with Lab_ReadDirectory */

void * __cdecl Lab_Open(char *name)

{
  char cVar1;
  int iVar2;
  int *lab;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  char *pcVar6;
  char *pcVar7;
  int *piVar8;
  
  iVar2 = Res_FOpen(name,&DAT_004ddb18);
  lab = Lab_AllocRecord();
  if (iVar2 != 0) {
    uVar3 = 0xffffffff;
    pcVar6 = name;
    do {
      pcVar7 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar7 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    piVar5 = (int *)(pcVar7 + -uVar3);
    piVar8 = lab + 2;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *piVar8 = *piVar5;
      piVar5 = piVar5 + 1;
      piVar8 = piVar8 + 1;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(char *)piVar8 = (char)*piVar5;
      piVar5 = (int *)((int)piVar5 + 1);
      piVar8 = (int *)((int)piVar8 + 1);
    }
    lab[0x43] = iVar2;
    iVar2 = (**(code **)(g_dwResHS + 0x50))(name);
    lab[0x44] = iVar2;
    lab[0x45] = 2;
    lab[0x46] = 0;
    lab[0x47] = 0;
    iVar2 = Lab_ReadDirectory(lab);
    if (iVar2 != 1) {
      Lab_Unlink(lab);
      lab = (int *)0x0;
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

int __cdecl Lab_ReadDirectory(void *lab)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  void *n;
  uint uVar2;
  int iVar3;
  void *pvVar4;
  uint *puVar5;
  undefined4 *puVar6;
  void *pvVar7;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(char (*)[8])(_frame + (0x20 - 0x8)))
  
  pvVar1 = lab;
  uVar2 = Res_FRead(*(int *)((int)lab + 0x10c),local_8,4);
  if ((((uVar2 == 4) && (uVar2 = strncmp(local_8,&DAT_004e7af0,4), uVar2 == 0)) &&
      (uVar2 = Res_FRead(*(int *)((int)pvVar1 + 0x10c),&lab,4), uVar2 == 4)) &&
     (((lab < (void *)0x10001 &&
       (uVar2 = Res_FRead(*(int *)((int)pvVar1 + 0x10c),&lab,4), pvVar7 = lab, uVar2 == 4)) &&
      (uVar2 = Res_FRead(*(int *)((int)pvVar1 + 0x10c),&lab,4), n = lab, uVar2 == 4)))) {
    iVar3 = (**(code **)(g_dwResHS + 0x20))
                      (((int)pvVar7 + 1) * 0x1c,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xbdc);
    *(int *)((int)pvVar1 + 0x118) = iVar3;
    if (iVar3 != 0) {
      iVar3 = (**(code **)(g_dwResHS + 0x20))(n,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xbdf);
      *(int *)((int)pvVar1 + 0x11c) = iVar3;
      if (iVar3 != 0) {
        puVar6 = *(undefined4 **)((int)pvVar1 + 0x118);
        pvVar4 = (void *)0x0;
        if (pvVar7 != (void *)0x0) {
          do {
            uVar2 = Res_FRead(*(int *)((int)pvVar1 + 0x10c),&lab,4);
            if (uVar2 != 4) goto LAB_00481994;
            puVar6[1] = (int)lab + *(int *)((int)pvVar1 + 0x11c);
            uVar2 = Res_FRead(*(int *)((int)pvVar1 + 0x10c),&lab,4);
            if (uVar2 != 4) goto LAB_00481994;
            puVar6[4] = lab;
            uVar2 = Res_FRead(*(int *)((int)pvVar1 + 0x10c),&lab,4);
            if (uVar2 != 4) goto LAB_00481994;
            puVar6[5] = lab;
            uVar2 = Res_FRead(*(int *)((int)pvVar1 + 0x10c),&lab,4);
            if (uVar2 != 4) goto LAB_00481994;
            puVar6[6] = 0;
            puVar6[3] = lab;
            pvVar4 = (void *)((int)pvVar4 + 1);
            puVar6 = puVar6 + 7;
          } while (pvVar4 < pvVar7);
        }
        for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
        pvVar4 = (void *)Res_FRead(*(int *)((int)pvVar1 + 0x10c),*(void **)((int)pvVar1 + 0x11c),
                                   (uint)n);
        if (pvVar4 == n) {
          puVar5 = *(uint **)((int)pvVar1 + 0x118);
          for (; pvVar7 != (void *)0x0; pvVar7 = (void *)((int)pvVar7 + -1)) {
            uVar2 = Res_HashName((char *)puVar5[1],(char *)puVar5[1]);
            *puVar5 = uVar2;
            puVar5 = puVar5 + 7;
          }
          return 1;
        }
      }
    }
  }
LAB_00481994:
  if (*(int *)((int)pvVar1 + 0x118) != 0) {
    (**(code **)(g_dwResHS + 0x24))(*(int *)((int)pvVar1 + 0x118));
  }
  if (*(int *)((int)pvVar1 + 0x11c) != 0) {
    (**(code **)(g_dwResHS + 0x24))(*(int *)((int)pvVar1 + 0x11c));
  }
  return 0;
}
#undef local_8
#undef local_c


/* ---- 0x00481a00  Lab_FindEntry ---- */
/* Hash + name match inside one archive; remembers the hit in the 16-slot recent-lookup ring */

int __cdecl Lab_FindEntry(void *lab,int fourcc,char *lowerName,uint hash,void *outEntry)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  byte *pbVar8;
  char *pcVar9;
  char *pcVar10;
  bool bVar11;
  
  puVar7 = *(uint **)((int)lab + 0x118);
  pbVar3 = (byte *)puVar7[1];
  if (pbVar3 == (byte *)0x0) {
    return 0;
  }
  do {
    if ((((fourcc == 0) || (puVar7[3] == 0)) || (puVar7[3] == fourcc)) &&
       (pbVar8 = (byte *)lowerName, *puVar7 == hash)) {
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
        *(uint **)(&g_aFoundFiles + g_dwLastFound * 4) = puVar7;
        *(void **)(&g_aFoundFileNodes + g_dwLastFound * 4) = lab;
        uVar5 = 0xffffffff;
        g_dwLastFound = g_dwLastFound + 1 & 0xf;
        pcVar9 = (char *)puVar7[1];
        break;
      }
    }
    pbVar3 = (byte *)puVar7[8];
    puVar7 = puVar7 + 7;
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
  pcVar10 = (char *)((int)outEntry + 0x14);
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
  *(int *)outEntry = fourcc;
  *(undefined4 *)((int)outEntry + 4) = *(undefined4 *)((int)lab + 0x10c);
  *(uint *)((int)outEntry + 8) = puVar7[5];
  *(uint *)((int)outEntry + 0xc) = puVar7[4];
  *(undefined4 *)((int)outEntry + 0x10) = 1;
  return 1;
}

/* ---- 0x00482020  Lab_ReadRaw ---- */
/* Reads n bytes at offset inside an archive-backed file entry, clamped to the entry size */

int __cdecl Lab_ReadRaw(void *entry,void *buf,int offset,int n)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)((int)entry + 0x10);
  if (iVar1 <= offset) {
    return 0;
  }
  if (iVar1 < n + offset) {
    n = iVar1 - offset;
  }
  Res_FSeek(*(int *)entry,*(int *)((int)entry + 0x14) + offset,0);
  uVar2 = Res_FRead(*(int *)entry,buf,n);
  return uVar2;
}
