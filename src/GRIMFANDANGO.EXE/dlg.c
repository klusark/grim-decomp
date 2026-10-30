/* GRIMFANDANGO.EXE :: dlg.c
 * functions 0x00488010 .. 0x004881a0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00488010  Dlg_MakeItemTemplate ---- */
/* Builds a DLGITEMTEMPLATE (style, x, y, w, h, id, text, class) in a malloc'd block, size returned
   through the last argument */

undefined4 *
Dlg_MakeItemTemplate
          (undefined4 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
          undefined2 param_5,undefined2 param_6,int param_7,int param_8,uint *param_9)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *a5;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  uVar1 = CONCAT22(param_3,param_2);
  uVar2 = CONCAT22(param_5,param_4);
  if (param_8 == 0) {
    PIECE(param_2,0,4) = 2;
    PIECE(param_4,0,4) = (undefined4 *)malloc(2);
    *(undefined2 *)PIECE(param_4,0,4) = 0;
  }
  else {
    iVar3 = MultiByteToWideChar(0,1,param_8,-1,0,0);
    PIECE(param_2,0,4) = iVar3 * 2;
    PIECE(param_4,0,4) = (undefined4 *)malloc(PIECE(param_2,0,4));
    MultiByteToWideChar(0,1,param_8,-1,(int)PIECE(param_4,0,4),iVar3);
  }
  if (param_7 == 0) {
    PIECE(param_3,0,4) = 2;
    a5 = (undefined4 *)malloc(2);
    *(undefined2 *)a5 = 0;
  }
  else {
    iVar3 = MultiByteToWideChar(0,1,param_7,-1,0,0);
    PIECE(param_3,0,4) = iVar3 * 2;
    a5 = (undefined4 *)malloc(PIECE(param_3,0,4));
    MultiByteToWideChar(0,1,param_7,-1,(int)a5,iVar3);
  }
  uVar6 = PIECE(param_2,0,4) + 0x13 + PIECE(param_3,0,4);
  *param_9 = uVar6;
  if ((uVar6 & 3) != 0) {
    do {
      *param_9 = *param_9 + 1;
    } while ((*param_9 & 3) != 0);
  }
  puVar4 = (undefined4 *)malloc(*param_9);
  uVar6 = *param_9;
  puVar7 = puVar4;
  for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined1 *)puVar7 = 0;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  *puVar4 = param_1;
  puVar4[1] = 0;
  puVar4[2] = uVar1;
  puVar4[3] = uVar2;
  *(undefined2 *)(puVar4 + 4) = param_6;
  puVar7 = PIECE(param_4,0,4);
  puVar8 = (undefined4 *)((int)puVar4 + 0x12);
  for (uVar6 = PIECE(param_2,0,4) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  for (uVar6 = PIECE(param_2,0,4) & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  }
  puVar7 = a5;
  puVar8 = (undefined4 *)(PIECE(param_2,0,4) + (int)puVar4 + 0x12);
  for (uVar6 = PIECE(param_3,0,4) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  for (PIECE(param_3,0,4) = PIECE(param_3,0,4) & 3; PIECE(param_3,0,4) != 0; PIECE(param_3,0,4) = PIECE(param_3,0,4) - 1) {
    *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  }
  free(a5);
  free(PIECE(param_4,0,4));
  return puVar4;
}

/* ---- 0x004881a0  Dlg_MakeDialogTemplate ---- */
/* Builds a DLGTEMPLATE header (style, item count, x, y, w, h, title, font, point size) */

uint * Dlg_MakeDialogTemplate
                 (undefined4 *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
                 undefined2 param_5,undefined2 param_6,int param_7,int param_8,undefined2 param_9,
                 uint *param_10)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined2 *puVar8;
  undefined4 *puVar9;
  uint *puVar10;
  undefined4 *puVar11;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  local_14 = (uint)param_1;
  if (param_8 != 0) {
    local_14 = (uint)param_1 | 0x40;
  }
  uVar7 = CONCAT22(param_3,param_2);
  uVar2 = CONCAT22(param_5,param_4);
  if (param_7 == 0) {
    PIECE(param_2,0,4) = 2;
    PIECE(param_4,0,4) = (undefined4 *)malloc(2);
    *(undefined2 *)PIECE(param_4,0,4) = 0;
  }
  else {
    iVar3 = MultiByteToWideChar(0,1,param_7,-1,0,0);
    PIECE(param_2,0,4) = iVar3 * 2;
    PIECE(param_4,0,4) = (undefined4 *)malloc(PIECE(param_2,0,4));
    MultiByteToWideChar(0,1,param_7,-1,(int)PIECE(param_4,0,4),iVar3);
  }
  if (param_8 == 0) {
    PIECE(param_3,0,4) = 0;
    param_1 = (undefined4 *)0x0;
    param_5 = 0;
  }
  else {
    iVar3 = MultiByteToWideChar(0,1,param_8,-1,0,0);
    PIECE(param_3,0,4) = iVar3 * 2;
    param_1 = (undefined4 *)malloc(PIECE(param_3,0,4));
    MultiByteToWideChar(0,1,param_8,-1,(int)param_1,iVar3);
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
  puVar4 = (uint *)malloc(*param_10);
  uVar6 = *param_10;
  puVar10 = puVar4;
  for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined1 *)puVar10 = 0;
    puVar10 = (uint *)((int)puVar10 + 1);
  }
  *puVar4 = local_14;
  puVar4[1] = 0;
  puVar4[2] = uVar7;
  puVar4[3] = uVar2;
  *(undefined2 *)(puVar4 + 4) = param_6;
  *(undefined2 *)((int)puVar4 + 0x12) = 0;
  *(undefined2 *)(puVar4 + 5) = 0;
  puVar9 = PIECE(param_4,0,4);
  puVar11 = (undefined4 *)((int)puVar4 + 0x16);
  for (uVar7 = PIECE(param_2,0,4) >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *puVar11 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar11 = puVar11 + 1;
  }
  for (uVar7 = PIECE(param_2,0,4) & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
    puVar9 = (undefined4 *)((int)puVar9 + 1);
    puVar11 = (undefined4 *)((int)puVar11 + 1);
  }
  free(PIECE(param_4,0,4));
  if (param_8 != 0) {
    puVar8 = (undefined2 *)((int)puVar4 + 0x16 + PIECE(param_2,0,4));
    *puVar8 = param_5;
    puVar9 = param_1;
    puVar11 = (undefined4 *)(puVar8 + 1);
    for (uVar7 = PIECE(param_3,0,4) >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar11 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar11 = puVar11 + 1;
    }
    for (PIECE(param_3,0,4) = PIECE(param_3,0,4) & 3; PIECE(param_3,0,4) != 0; PIECE(param_3,0,4) = PIECE(param_3,0,4) - 1) {
      *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
      puVar9 = (undefined4 *)((int)puVar9 + 1);
      puVar11 = (undefined4 *)((int)puVar11 + 1);
    }
    free(param_1);
  }
  return puVar4;
}
#undef local_14

