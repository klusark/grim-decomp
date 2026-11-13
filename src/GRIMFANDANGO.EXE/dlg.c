/* GRIMFANDANGO.EXE :: dlg.c
 * functions 0x00488010 .. 0x004881a0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00488010  Dlg_MakeItemTemplate ---- */
/* Builds a DLGITEMTEMPLATE (style, x, y, w, h, id, text, class) in a malloc'd block, size returned
   through the last argument */

undefined4 * __cdecl
Dlg_MakeItemTemplate
          (uint param_1,ushort param_2,ushort param_3,ushort param_4,ushort param_5,ushort param_6,
          int param_7,int param_8,uint *param_9)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *a5;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint *puVar6;
  undefined4 *puVar7;
  #define local_c (*(undefined4 *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  
  local_c = CONCAT22(param_3,param_2);
  local_8 = CONCAT22(param_5,param_4);
  if (param_8 == 0) {
    PIECE(param_2,0,4) = 2;
    PIECE(param_4,0,4) = (undefined4 *)malloc(2);
    *(undefined2 *)PIECE(param_4,0,4) = 0;
  }
  else {
    iVar1 = MultiByteToWideChar(0,1,param_8,-1,0,0);
    PIECE(param_2,0,4) = iVar1 * 2;
    PIECE(param_4,0,4) = (undefined4 *)malloc(PIECE(param_2,0,4));
    MultiByteToWideChar(0,1,param_8,-1,(int)PIECE(param_4,0,4),iVar1);
  }
  if (param_7 == 0) {
    PIECE(param_3,0,4) = 2;
    a5 = (undefined4 *)malloc(2);
    *(undefined2 *)a5 = 0;
  }
  else {
    iVar1 = MultiByteToWideChar(0,1,param_7,-1,0,0);
    PIECE(param_3,0,4) = iVar1 * 2;
    a5 = (undefined4 *)malloc(PIECE(param_3,0,4));
    MultiByteToWideChar(0,1,param_7,-1,(int)a5,iVar1);
  }
  uVar4 = PIECE(param_2,0,4) + 0x13 + PIECE(param_3,0,4);
  *param_9 = uVar4;
  if ((uVar4 & 3) != 0) {
    do {
      *param_9 = *param_9 + 1;
    } while ((*param_9 & 3) != 0);
  }
  puVar2 = (uint *)malloc(*param_9);
  uVar4 = *param_9;
  puVar6 = puVar2;
  for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined1 *)puVar6 = 0;
    puVar6 = (uint *)((int)puVar6 + 1);
  }
  *puVar2 = param_1;
  puVar2[1] = 0;
  puVar2[2] = local_c;
  puVar2[3] = local_8;
  *(ushort *)(puVar2 + 4) = param_6;
  puVar5 = PIECE(param_4,0,4);
  puVar7 = (undefined4 *)((int)puVar2 + 0x12);
  for (uVar4 = PIECE(param_2,0,4) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar7 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar7 = puVar7 + 1;
  }
  for (uVar4 = PIECE(param_2,0,4) & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined1 *)puVar7 = *(undefined1 *)puVar5;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  puVar5 = a5;
  puVar7 = (undefined4 *)(PIECE(param_2,0,4) + (int)puVar2 + 0x12);
  for (uVar4 = PIECE(param_3,0,4) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar7 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar7 = puVar7 + 1;
  }
  for (PIECE(param_3,0,4) = PIECE(param_3,0,4) & 3; PIECE(param_3,0,4) != 0; PIECE(param_3,0,4) = PIECE(param_3,0,4) - 1) {
    *(undefined1 *)puVar7 = *(undefined1 *)puVar5;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  free((int)a5);
  free((int)PIECE(param_4,0,4));
  return puVar2;
}
#undef local_8
#undef local_c


/* ---- 0x004881a0  Dlg_MakeDialogTemplate ---- */
/* Builds a DLGTEMPLATE header (style, item count, x, y, w, h, title, font, point size) */

uint * __cdecl
Dlg_MakeDialogTemplate
          (undefined4 *param_1,ushort param_2,ushort param_3,ushort param_4,ushort param_5,
          ushort param_6,int param_7,int param_8,ushort param_9,uint *param_10)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  ushort *puVar6;
  undefined4 *puVar7;
  uint *puVar8;
  undefined4 *puVar9;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_c (*(undefined4 *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  
  local_14 = (uint)param_1;
  if (param_8 != 0) {
    local_14 = (uint)param_1 | 0x40;
  }
  local_c = CONCAT22(param_3,param_2);
  local_8 = CONCAT22(param_5,param_4);
  if (param_7 == 0) {
    PIECE(param_2,0,4) = 2;
    PIECE(param_4,0,4) = (undefined4 *)malloc(2);
    *(undefined2 *)PIECE(param_4,0,4) = 0;
  }
  else {
    iVar2 = MultiByteToWideChar(0,1,param_7,-1,0,0);
    PIECE(param_2,0,4) = iVar2 * 2;
    PIECE(param_4,0,4) = (undefined4 *)malloc(PIECE(param_2,0,4));
    MultiByteToWideChar(0,1,param_7,-1,(int)PIECE(param_4,0,4),iVar2);
  }
  if (param_8 == 0) {
    PIECE(param_3,0,4) = 0;
    param_1 = (undefined4 *)0x0;
    param_5 = 0;
  }
  else {
    iVar2 = MultiByteToWideChar(0,1,param_8,-1,0,0);
    PIECE(param_3,0,4) = iVar2 * 2;
    param_1 = (undefined4 *)malloc(PIECE(param_3,0,4));
    MultiByteToWideChar(0,1,param_8,-1,(int)param_1,iVar2);
    param_5 = param_9;
  }
  *param_10 = PIECE(param_2,0,4) + 0x16;
  if (param_8 != 0) {
    *param_10 = PIECE(param_3,0,4) + 2 + PIECE(param_2,0,4) + 0x16;
  }
  bVar1 = (byte)*param_10;
  while ((bVar1 & 3) != 0) {
    *param_10 = *param_10 + 1;
    bVar1 = (byte)*param_10;
  }
  puVar3 = (uint *)malloc(*param_10);
  uVar5 = *param_10;
  puVar8 = puVar3;
  for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined1 *)puVar8 = 0;
    puVar8 = (uint *)((int)puVar8 + 1);
  }
  *puVar3 = local_14;
  puVar3[1] = 0;
  puVar3[2] = local_c;
  puVar3[3] = local_8;
  *(ushort *)(puVar3 + 4) = param_6;
  *(undefined2 *)((int)puVar3 + 0x12) = 0;
  *(undefined2 *)(puVar3 + 5) = 0;
  puVar7 = PIECE(param_4,0,4);
  puVar9 = (undefined4 *)((int)puVar3 + 0x16);
  for (uVar5 = PIECE(param_2,0,4) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar9 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar9 = puVar9 + 1;
  }
  for (uVar5 = PIECE(param_2,0,4) & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined1 *)puVar9 = *(undefined1 *)puVar7;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
    puVar9 = (undefined4 *)((int)puVar9 + 1);
  }
  free((int)PIECE(param_4,0,4));
  if (param_8 != 0) {
    puVar6 = (ushort *)((int)puVar3 + 0x16 + PIECE(param_2,0,4));
    *puVar6 = param_5;
    puVar7 = param_1;
    puVar6 = puVar6 + 1;
    for (uVar5 = PIECE(param_3,0,4) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)puVar6 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar6 = puVar6 + 2;
    }
    for (PIECE(param_3,0,4) = PIECE(param_3,0,4) & 3; PIECE(param_3,0,4) != 0; PIECE(param_3,0,4) = PIECE(param_3,0,4) - 1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar7;
      puVar7 = (undefined4 *)((int)puVar7 + 1);
      puVar6 = (ushort *)((int)puVar6 + 1);
    }
    free((int)param_1);
  }
  return puVar3;
}
#undef local_14
#undef local_8
#undef local_c

