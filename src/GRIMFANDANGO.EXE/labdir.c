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
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  uint *puVar7;
  int iVar8;
  int *piVar9;
  int *piVar10;
  char *pcVar11;
  #define local_114 (*(uint *)(_frame + (0x130 - 0x114)))
  #define local_110 (*(uint *)(_frame + (0x130 - 0x110)))
  #define local_10c (*(char (*)[260])(_frame + (0x130 - 0x10c)))
  #define local_8 (*(uint *)(_frame + (0x130 - 0x8)))
  
  iVar8 = 0;
  piVar5 = (int *)0x0;
  iVar6 = 0;
  puVar2 = DirScan_Create((uint)dir,1,&DAT_004f5a98);
  uVar3 = DirScan_Next((int)puVar2,local_10c);
  while (uVar3 != 0) {
    if (local_8 == 0) {
      uVar3 = 0xffffffff;
      iVar8 = iVar8 + 1;
      pcVar11 = local_10c;
      do {
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        cVar1 = *pcVar11;
        pcVar11 = pcVar11 + 1;
      } while (cVar1 != '\0');
      iVar6 = iVar6 + ~uVar3;
    }
    uVar3 = DirScan_Next((int)puVar2,local_10c);
  }
  if (iVar8 != 0) {
    if (iVar6 < 1) {
      iVar6 = 1;
    }
    piVar5 = Lab_AllocRecord();
    uVar3 = 0xffffffff;
    do {
      pcVar11 = dir;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar11 = dir + 1;
      cVar1 = *dir;
      dir = pcVar11;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    piVar9 = (int *)(pcVar11 + -uVar3);
    piVar10 = piVar5 + 2;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *piVar10 = *piVar9;
      piVar9 = piVar9 + 1;
      piVar10 = piVar10 + 1;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(char *)piVar10 = (char)*piVar9;
      piVar9 = (int *)((int)piVar9 + 1);
      piVar10 = (int *)((int)piVar10 + 1);
    }
    piVar5[0x45] = 1;
    iVar8 = (**(code **)(g_dwResHS + 0x20))
                      ((iVar8 + 1) * 0xc,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xc63);
    piVar5[0x46] = iVar8;
    if (iVar8 != 0) {
      iVar6 = (**(code **)(g_dwResHS + 0x20))
                        (iVar6,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xc67);
      piVar5[0x47] = iVar6;
      if (iVar6 == 0) {
        (**(code **)(g_dwResHS + 0x24))(piVar5[0x46]);
        piVar5[0x46] = 0;
      }
      else {
        puVar7 = (uint *)piVar5[0x46];
        iVar6 = 0;
        DirScan_Reset((int)puVar2);
        uVar3 = DirScan_Next((int)puVar2,local_10c);
        while (uVar3 != 0) {
          if (local_8 == 0) {
            puVar7[1] = iVar6 + piVar5[0x47];
            uVar3 = Res_HashName(local_10c,(char *)(iVar6 + piVar5[0x47]));
            *puVar7 = uVar3;
            uVar3 = 0xffffffff;
            puVar7 = puVar7 + 3;
            pcVar11 = local_10c;
            do {
              if (uVar3 == 0) break;
              uVar3 = uVar3 - 1;
              cVar1 = *pcVar11;
              pcVar11 = pcVar11 + 1;
            } while (cVar1 != '\0');
            iVar6 = iVar6 + ~uVar3;
          }
          uVar3 = DirScan_Next((int)puVar2,local_10c);
        }
        puVar7[1] = 0;
        *puVar7 = 0;
      }
    }
  }
  DirScan_Destroy((int)puVar2);
  return piVar5;
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
