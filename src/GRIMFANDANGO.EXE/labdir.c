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
  unsigned char _frame[0x130] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  int *piVar10;
  int *piVar11;
  char *pcVar12;
  #define local_114 (*(uint *)(_frame + (0x130 - 0x114)))
  #define local_110 (*(uint *)(_frame + (0x130 - 0x110)))
  #define local_10c (*(char (*)[260])(_frame + (0x130 - 0x10c)))
  #define local_8 (*(uint *)(_frame + (0x130 - 0x8)))
  
  iVar9 = 0;
  piVar6 = (int *)0x0;
  iVar7 = 0;
  uVar2 = DirScan_Create(dir,1,&DAT_004f5a98);
  iVar3 = DirScan_Next(uVar2,local_10c);
  while (iVar3 != 0) {
    if (local_8 == 0) {
      uVar4 = 0xffffffff;
      iVar9 = iVar9 + 1;
      pcVar12 = local_10c;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar12;
        pcVar12 = pcVar12 + 1;
      } while (cVar1 != '\0');
      iVar7 = iVar7 + ~uVar4;
    }
    iVar3 = DirScan_Next(uVar2,local_10c);
  }
  if (iVar9 != 0) {
    if (iVar7 < 1) {
      iVar7 = 1;
    }
    piVar6 = Lab_AllocRecord();
    uVar4 = 0xffffffff;
    do {
      pcVar12 = dir;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar12 = dir + 1;
      cVar1 = *dir;
      dir = pcVar12;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    piVar10 = (int *)(pcVar12 + -uVar4);
    piVar11 = piVar6 + 2;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *piVar11 = *piVar10;
      piVar10 = piVar10 + 1;
      piVar11 = piVar11 + 1;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(char *)piVar11 = (char)*piVar10;
      piVar10 = (int *)((int)piVar10 + 1);
      piVar11 = (int *)((int)piVar11 + 1);
    }
    piVar6[0x45] = 1;
    iVar9 = (**(code **)(g_dwResHS + 0x20))
                      ((iVar9 + 1) * 0xc,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xc63);
    piVar6[0x46] = iVar9;
    if (iVar9 != 0) {
      iVar7 = (**(code **)(g_dwResHS + 0x20))
                        (iVar7,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xc67);
      piVar6[0x47] = iVar7;
      if (iVar7 == 0) {
        (**(code **)(g_dwResHS + 0x24))(piVar6[0x46]);
        piVar6[0x46] = 0;
      }
      else {
        puVar8 = (uint *)piVar6[0x46];
        iVar7 = 0;
        DirScan_Reset(uVar2);
        iVar9 = DirScan_Next(uVar2,local_10c);
        while (iVar9 != 0) {
          if (local_8 == 0) {
            puVar8[1] = iVar7 + piVar6[0x47];
            uVar4 = Res_HashName(local_10c,(char *)(iVar7 + piVar6[0x47]));
            *puVar8 = uVar4;
            uVar4 = 0xffffffff;
            puVar8 = puVar8 + 3;
            pcVar12 = local_10c;
            do {
              if (uVar4 == 0) break;
              uVar4 = uVar4 - 1;
              cVar1 = *pcVar12;
              pcVar12 = pcVar12 + 1;
            } while (cVar1 != '\0');
            iVar7 = iVar7 + ~uVar4;
          }
          iVar9 = DirScan_Next(uVar2,local_10c);
        }
        puVar8[1] = 0;
        *puVar8 = 0;
      }
    }
  }
  DirScan_Destroy(uVar2);
  return piVar6;
}
#undef local_10c
#undef local_110
#undef local_114
#undef local_8


/* ---- 0x00481cf0  res_FindDirectoryEntry ---- */
/* Directory-backed archive lookup; fills the entry with the full path and the file size Original
   name res_FindDirectoryEntry (the remaster's GrimFandango (Linux): aligned call in
   Res_FindExternalFile, res_FindInternalFile); was LabDir_FindEntry. */

int __cdecl res_FindDirectoryEntry(int archive,int type,byte *name,uint hash,undefined4 *entry)

{
  uint *puVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  uint *puVar9;
  bool bVar10;
  
  puVar9 = *(uint **)(archive + 0x118);
  if (puVar9 == (uint *)0x0) {
    return 0;
  }
  pbVar8 = (byte *)puVar9[1];
  while (pbVar8 != (byte *)0x0) {
    pbVar3 = name;
    if (*puVar9 == hash) {
      do {
        bVar2 = *pbVar3;
        bVar10 = bVar2 < *pbVar8;
        if (bVar2 != *pbVar8) {
LAB_00481d3e:
          iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
          goto LAB_00481d43;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar3[1];
        bVar10 = bVar2 < pbVar8[1];
        if (bVar2 != pbVar8[1]) goto LAB_00481d3e;
        pbVar8 = pbVar8 + 2;
        pbVar3 = pbVar3 + 2;
      } while (bVar2 != 0);
      iVar4 = 0;
LAB_00481d43:
      if (iVar4 == 0) {
        *(uint **)(&g_aFoundFiles + g_dwLastFound * 4) = puVar9;
        *(int *)(&g_aFoundFileNodes + g_dwLastFound * 4) = archive;
        g_dwLastFound = g_dwLastFound + 1 & 0xf;
        break;
      }
    }
    puVar1 = puVar9 + 4;
    puVar9 = puVar9 + 3;
    pbVar8 = (byte *)*puVar1;
  }
  if (puVar9[1] == 0) {
    return 0;
  }
  uVar6 = 0xffffffff;
  pbVar8 = name;
  do {
    pbVar3 = pbVar8;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pbVar3 = pbVar8 + 1;
    bVar2 = *pbVar8;
    pbVar8 = pbVar3;
  } while (bVar2 != 0);
  uVar6 = ~uVar6;
  pbVar8 = pbVar3 + -uVar6;
  pbVar3 = (byte *)(entry + 5);
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pbVar3 = *(undefined4 *)pbVar8;
    pbVar8 = pbVar8 + 4;
    pbVar3 = pbVar3 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pbVar3 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar3 = pbVar3 + 1;
  }
  *entry = type;
  sprintf((char *)((int)entry + 0x115),&DAT_004e7af8,archive + 8,name);
  entry[1] = 0;
  uVar5 = (**(code **)(g_dwLowLevelHS + 0x50))((char *)((int)entry + 0x115));
  entry[2] = uVar5;
  entry[3] = 0;
  entry[4] = 0;
  return 1;
}
