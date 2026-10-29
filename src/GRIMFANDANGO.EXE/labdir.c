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
  void *pvVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  char *pcVar10;
  char *pcVar11;
  #define local_114 (*(uint *)(_frame + (0x130 - 0x114)))
  #define local_110 (*(uint *)(_frame + (0x130 - 0x110)))
  #define local_10c (*(char (*)[260])(_frame + (0x130 - 0x10c)))
  #define local_8 (*(uint *)(_frame + (0x130 - 0x8)))
  
  iVar9 = 0;
  pvVar6 = (void *)0x0;
  iVar7 = 0;
  uVar2 = DirScan_Create(dir,1,&DAT_004f5a98);
  iVar3 = DirScan_Next(uVar2,local_10c);
  while (iVar3 != 0) {
    if (local_8 == 0) {
      uVar4 = 0xffffffff;
      iVar9 = iVar9 + 1;
      pcVar10 = local_10c;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      iVar7 = iVar7 + ~uVar4;
    }
    iVar3 = DirScan_Next(uVar2,local_10c);
  }
  if (iVar9 != 0) {
    if (iVar7 < 1) {
      iVar7 = 1;
    }
    pvVar6 = (void *)Lab_AllocRecord();
    uVar4 = 0xffffffff;
    do {
      pcVar10 = dir;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar10 = dir + 1;
      cVar1 = *dir;
      dir = pcVar10;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar10 = pcVar10 + -uVar4;
    pcVar11 = (char *)((int)pvVar6 + 8);
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar11 = pcVar11 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar11 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar11 = pcVar11 + 1;
    }
    *(undefined4 *)((int)pvVar6 + 0x114) = 1;
    iVar9 = (**(code **)(UINT_008a856c + 0x20))
                      ((iVar9 + 1) * 0xc,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xc63);
    *(int *)((int)pvVar6 + 0x118) = iVar9;
    if (iVar9 != 0) {
      iVar7 = (**(code **)(UINT_008a856c + 0x20))
                        (iVar7,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xc67);
      *(int *)((int)pvVar6 + 0x11c) = iVar7;
      if (iVar7 == 0) {
        (**(code **)(UINT_008a856c + 0x24))(*(undefined4 *)((int)pvVar6 + 0x118));
        *(undefined4 *)((int)pvVar6 + 0x118) = 0;
      }
      else {
        puVar8 = *(uint **)((int)pvVar6 + 0x118);
        iVar7 = 0;
        DirScan_Reset(uVar2);
        iVar9 = DirScan_Next(uVar2,local_10c);
        while (iVar9 != 0) {
          if (local_8 == 0) {
            puVar8[1] = iVar7 + *(int *)((int)pvVar6 + 0x11c);
            uVar4 = Res_HashName(local_10c,(char *)(iVar7 + *(int *)((int)pvVar6 + 0x11c)));
            *puVar8 = uVar4;
            uVar4 = 0xffffffff;
            puVar8 = puVar8 + 3;
            pcVar10 = local_10c;
            do {
              if (uVar4 == 0) break;
              uVar4 = uVar4 - 1;
              cVar1 = *pcVar10;
              pcVar10 = pcVar10 + 1;
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
  return pvVar6;
}
#undef local_10c
#undef local_110
#undef local_114
#undef local_8


/* ---- 0x00481cf0  LabDir_FindEntry ---- */
/* Directory-backed archive lookup; fills the entry with the full path and the file size */

undefined4
LabDir_FindEntry(int param_1,undefined4 param_2,byte *param_3,int param_4,undefined4 *param_5)

{
  int *piVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  int *piVar9;
  bool bVar10;
  
  piVar9 = *(int **)(param_1 + 0x118);
  if (piVar9 == (int *)0x0) {
    return 0;
  }
  pbVar8 = (byte *)piVar9[1];
  while (pbVar8 != (byte *)0x0) {
    pbVar3 = param_3;
    if (*piVar9 == param_4) {
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
        *(int **)(&DAT_00825f00 + UINT_008a85e0 * 4) = piVar9;
        *(int *)(&DAT_008a8578 + UINT_008a85e0 * 4) = param_1;
        UINT_008a85e0 = UINT_008a85e0 + 1 & 0xf;
        break;
      }
    }
    piVar1 = piVar9 + 4;
    piVar9 = piVar9 + 3;
    pbVar8 = (byte *)*piVar1;
  }
  if (piVar9[1] == 0) {
    return 0;
  }
  uVar6 = 0xffffffff;
  pbVar8 = param_3;
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
  pbVar3 = (byte *)(param_5 + 5);
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
  *param_5 = param_2;
  ((code *)sprintf)((int)param_5 + 0x115,&DAT_004e7af8,param_1 + 8,param_3);
  param_5[1] = 0;
  uVar5 = (**(code **)(UINT_008a8570 + 0x50))((int)param_5 + 0x115);
  param_5[2] = uVar5;
  param_5[3] = 0;
  param_5[4] = 0;
  return 1;
}
