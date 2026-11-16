/* GRIMFANDANGO.EXE :: labdir.c
 * functions 0x00481b00 .. 0x00481cf0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00481b00  LabDir_Open ---- */
/* Developer mode: a plain directory presented as an archive (12-byte entries {hash, name, 0}) */

void * __cdecl LabDir_Open(char *dir)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined4 *scan;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  uint *puVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  char *pcVar10;
  uint local_114;
  uint local_110;
  #define local_10c (*(char (*)[260])(_frame + (0x120 - 0x10c)))
  #define local_8 (*(uint *)(_frame + (0x120 - 0x8)))
  
  iVar7 = 0;
  piVar4 = (int *)0x0;
  iVar5 = 0;
  scan = DirScan_Create((uint)dir,1,&DAT_004f5a98);
  uVar2 = DirScan_Next((int)scan,local_10c);
  while (uVar2 != 0) {
    if (local_8 == 0) {
      uVar2 = 0xffffffff;
      iVar7 = iVar7 + 1;
      pcVar10 = local_10c;
      do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      iVar5 = iVar5 + ~uVar2;
    }
    uVar2 = DirScan_Next((int)scan,local_10c);
  }
  if (iVar7 != 0) {
    if (iVar5 < 1) {
      iVar5 = 1;
    }
    piVar4 = Lab_AllocRecord();
    uVar2 = 0xffffffff;
    do {
      pcVar10 = dir;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar10 = dir + 1;
      cVar1 = *dir;
      dir = pcVar10;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    piVar8 = (int *)(pcVar10 + -uVar2);
    piVar9 = piVar4 + 2;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *piVar9 = *piVar8;
      piVar8 = piVar8 + 1;
      piVar9 = piVar9 + 1;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(char *)piVar9 = (char)*piVar8;
      piVar8 = (int *)((int)piVar8 + 1);
      piVar9 = (int *)((int)piVar9 + 1);
    }
    piVar4[0x45] = 1;
    iVar7 = (**(code **)(g_dwResHS + 0x20))
                      ((iVar7 + 1) * 0xc,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xc63);
    piVar4[0x46] = iVar7;
    if (iVar7 != 0) {
      iVar5 = (**(code **)(g_dwResHS + 0x20))
                        (iVar5,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xc67);
      piVar4[0x47] = iVar5;
      if (iVar5 == 0) {
        (**(code **)(g_dwResHS + 0x24))(piVar4[0x46]);
        piVar4[0x46] = 0;
      }
      else {
        puVar6 = (uint *)piVar4[0x46];
        iVar5 = 0;
        DirScan_Reset((int)scan);
        uVar2 = DirScan_Next((int)scan,local_10c);
        while (uVar2 != 0) {
          if (local_8 == 0) {
            puVar6[1] = iVar5 + piVar4[0x47];
            uVar2 = Res_HashName(local_10c,(char *)(iVar5 + piVar4[0x47]));
            *puVar6 = uVar2;
            uVar2 = 0xffffffff;
            puVar6 = puVar6 + 3;
            pcVar10 = local_10c;
            do {
              if (uVar2 == 0) break;
              uVar2 = uVar2 - 1;
              cVar1 = *pcVar10;
              pcVar10 = pcVar10 + 1;
            } while (cVar1 != '\0');
            iVar5 = iVar5 + ~uVar2;
          }
          uVar2 = DirScan_Next((int)scan,local_10c);
        }
        puVar6[1] = 0;
        *puVar6 = 0;
      }
    }
  }
  DirScan_Destroy((int)scan);
  return piVar4;
}
#undef local_10c
#undef local_8


/* ---- 0x00481cf0  res_FindDirectoryEntry ---- */
/* Directory-backed archive lookup; fills the entry with the full path and the file size Original
   name res_FindDirectoryEntry (the remaster's GrimFandango (Linux): aligned call in
   Res_FindExternalFile, res_FindInternalFile); was LabDir_FindEntry. */

int __cdecl res_FindDirectoryEntry(int archive,int type,byte *name,uint hash,LabFile *entry)

{
  uint *puVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  uint *puVar8;
  char *pcVar9;
  bool bVar10;
  
  puVar8 = *(uint **)(archive + 0x118);
  if (puVar8 == (uint *)0x0) {
    return 0;
  }
  pbVar7 = (byte *)puVar8[1];
  while (pbVar7 != (byte *)0x0) {
    pbVar3 = name;
    if (*puVar8 == hash) {
      do {
        bVar2 = *pbVar3;
        bVar10 = bVar2 < *pbVar7;
        if (bVar2 != *pbVar7) {
LAB_00481d3e:
          iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
          goto LAB_00481d43;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar3[1];
        bVar10 = bVar2 < pbVar7[1];
        if (bVar2 != pbVar7[1]) goto LAB_00481d3e;
        pbVar7 = pbVar7 + 2;
        pbVar3 = pbVar3 + 2;
      } while (bVar2 != 0);
      iVar4 = 0;
LAB_00481d43:
      if (iVar4 == 0) {
        *(uint **)(&g_aFoundFiles + g_dwLastFound * 4) = puVar8;
        g_aFoundFileNodes[g_dwLastFound] = (void *)archive;
        g_dwLastFound = g_dwLastFound + 1 & 0xf;
        break;
      }
    }
    puVar1 = puVar8 + 4;
    puVar8 = puVar8 + 3;
    pbVar7 = (byte *)*puVar1;
  }
  if (puVar8[1] == 0) {
    return 0;
  }
  uVar5 = 0xffffffff;
  pbVar7 = name;
  do {
    pbVar3 = pbVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pbVar3 = pbVar7 + 1;
    bVar2 = *pbVar7;
    pbVar7 = pbVar3;
  } while (bVar2 != 0);
  uVar5 = ~uVar5;
  pbVar7 = pbVar3 + -uVar5;
  pcVar9 = entry->aName;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pbVar7;
    pbVar7 = pbVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar9 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  entry->dwFourcc = type;
  sprintf(entry->aPath,s__s_s_004e7af8,archive + 8,name);
  entry->nFile = 0;
  iVar4 = (**(code **)(g_dwLowLevelHS + 0x50))(entry->aPath);
  entry->nSize = iVar4;
  entry->nOffset = 0;
  entry->nInLab = 0;
  return 1;
}
