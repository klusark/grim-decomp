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
          (uint style,ushort x,ushort y,ushort cx,ushort cy,ushort id,int className,int text,
          uint *outSize)

{
  int iVar1;
  undefined4 *a5;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint *puVar6;
  undefined4 *puVar7;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = CONCAT22(y,x);
  local_8 = CONCAT22(cy,cx);
  if (text == 0) {
    PIECE(x,0,4) = 2;
    PIECE(cx,0,4) = (undefined4 *)malloc(2);
    *(undefined2 *)PIECE(cx,0,4) = 0;
  }
  else {
    iVar1 = MultiByteToWideChar(0,1,text,-1,0,0);
    PIECE(x,0,4) = iVar1 * 2;
    PIECE(cx,0,4) = (undefined4 *)malloc(PIECE(x,0,4));
    MultiByteToWideChar(0,1,text,-1,(int)PIECE(cx,0,4),iVar1);
  }
  if (className == 0) {
    PIECE(y,0,4) = 2;
    a5 = (undefined4 *)malloc(2);
    *(undefined2 *)a5 = 0;
  }
  else {
    iVar1 = MultiByteToWideChar(0,1,className,-1,0,0);
    PIECE(y,0,4) = iVar1 * 2;
    a5 = (undefined4 *)malloc(PIECE(y,0,4));
    MultiByteToWideChar(0,1,className,-1,(int)a5,iVar1);
  }
  uVar4 = PIECE(x,0,4) + 0x13 + PIECE(y,0,4);
  *outSize = uVar4;
  if ((uVar4 & 3) != 0) {
    do {
      *outSize = *outSize + 1;
    } while ((*outSize & 3) != 0);
  }
  puVar2 = (uint *)malloc(*outSize);
  uVar4 = *outSize;
  puVar6 = puVar2;
  for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined1 *)puVar6 = 0;
    puVar6 = (uint *)((int)puVar6 + 1);
  }
  *puVar2 = style;
  puVar2[1] = 0;
  puVar2[2] = local_c;
  puVar2[3] = local_8;
  *(ushort *)(puVar2 + 4) = id;
  puVar5 = PIECE(cx,0,4);
  puVar7 = (undefined4 *)((int)puVar2 + 0x12);
  for (uVar4 = PIECE(x,0,4) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar7 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar7 = puVar7 + 1;
  }
  for (uVar4 = PIECE(x,0,4) & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined1 *)puVar7 = *(undefined1 *)puVar5;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  puVar5 = a5;
  puVar7 = (undefined4 *)(PIECE(x,0,4) + (int)puVar2 + 0x12);
  for (uVar4 = PIECE(y,0,4) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar7 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar7 = puVar7 + 1;
  }
  for (PIECE(y,0,4) = PIECE(y,0,4) & 3; PIECE(y,0,4) != 0; PIECE(y,0,4) = PIECE(y,0,4) - 1) {
    *(undefined1 *)puVar7 = *(undefined1 *)puVar5;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  free((int)a5);
  free((int)PIECE(cx,0,4));
  return puVar2;
}

/* ---- 0x004881a0  Dlg_MakeDialogTemplate ---- */
/* Builds a DLGTEMPLATE header (style, item count, x, y, w, h, title, font, point size) */

uint * __cdecl
Dlg_MakeDialogTemplate
          (undefined4 *style,ushort items,ushort x,ushort y,ushort cx,ushort cy,int title,int font,
          ushort pointSize,uint *outSize)

{
  byte bVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  ushort *puVar6;
  undefined4 *puVar7;
  uint *puVar8;
  undefined4 *puVar9;
  uint local_14;
  undefined4 local_c;
  undefined4 local_8;
  
  local_14 = (uint)style;
  if (font != 0) {
    local_14 = (uint)style | 0x40;
  }
  local_c = CONCAT22(x,items);
  local_8 = CONCAT22(cx,y);
  if (title == 0) {
    PIECE(items,0,4) = 2;
    PIECE(y,0,4) = (undefined4 *)malloc(2);
    *(undefined2 *)PIECE(y,0,4) = 0;
  }
  else {
    iVar2 = MultiByteToWideChar(0,1,title,-1,0,0);
    PIECE(items,0,4) = iVar2 * 2;
    PIECE(y,0,4) = (undefined4 *)malloc(PIECE(items,0,4));
    MultiByteToWideChar(0,1,title,-1,(int)PIECE(y,0,4),iVar2);
  }
  if (font == 0) {
    PIECE(x,0,4) = 0;
    style = (undefined4 *)0x0;
    cx = 0;
  }
  else {
    iVar2 = MultiByteToWideChar(0,1,font,-1,0,0);
    PIECE(x,0,4) = iVar2 * 2;
    style = (undefined4 *)malloc(PIECE(x,0,4));
    MultiByteToWideChar(0,1,font,-1,(int)style,iVar2);
    cx = pointSize;
  }
  *outSize = PIECE(items,0,4) + 0x16;
  if (font != 0) {
    *outSize = PIECE(x,0,4) + 2 + PIECE(items,0,4) + 0x16;
  }
  bVar1 = (byte)*outSize;
  while ((bVar1 & 3) != 0) {
    *outSize = *outSize + 1;
    bVar1 = (byte)*outSize;
  }
  puVar3 = (uint *)malloc(*outSize);
  uVar5 = *outSize;
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
  *(ushort *)(puVar3 + 4) = cy;
  *(undefined2 *)((int)puVar3 + 0x12) = 0;
  *(undefined2 *)(puVar3 + 5) = 0;
  puVar7 = PIECE(y,0,4);
  puVar9 = (undefined4 *)((int)puVar3 + 0x16);
  for (uVar5 = PIECE(items,0,4) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar9 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar9 = puVar9 + 1;
  }
  for (uVar5 = PIECE(items,0,4) & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined1 *)puVar9 = *(undefined1 *)puVar7;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
    puVar9 = (undefined4 *)((int)puVar9 + 1);
  }
  free((int)PIECE(y,0,4));
  if (font != 0) {
    puVar6 = (ushort *)((int)puVar3 + 0x16 + PIECE(items,0,4));
    *puVar6 = cx;
    puVar7 = style;
    puVar6 = puVar6 + 1;
    for (uVar5 = PIECE(x,0,4) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)puVar6 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar6 = puVar6 + 2;
    }
    for (PIECE(x,0,4) = PIECE(x,0,4) & 3; PIECE(x,0,4) != 0; PIECE(x,0,4) = PIECE(x,0,4) - 1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar7;
      puVar7 = (undefined4 *)((int)puVar7 + 1);
      puVar6 = (ushort *)((int)puVar6 + 1);
    }
    free((int)style);
  }
  return puVar3;
}
