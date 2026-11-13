/* GRIMFANDANGO.EXE :: video.c
 * functions 0x004cea30 .. 0x004d0260 (14 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004cea30  gra_BlitRectLookup ---- */
/* Copies or converts a clipped rectangle from one bitmap to another through
   VideoBitmap_ConvertPixels Original name gra_BlitRectLookup (the remaster's GrimFandango (Linux):
   same body: clips the source rectangle, gra_CopyRect when the formats agree, else
   gra_ConvertMakeLookup for 8-bit sources and gra_ConvertCopy row by row); was Video_BlitConvert.
    */

void gra_BlitRectLookup(int *param_1,uint *param_2,int param_3,int param_4,int *param_5,
                       byte *param_6,byte *param_7)

{
  unsigned char _frame[0x430] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *dst;
  int iVar1;
  byte *src;
  uint uVar2;
  int iVar3;
  #define local_420 (*(uint *)(_frame + (0x430 - 0x420)))
  #define local_41c (*(uint *)(_frame + (0x430 - 0x41c)))
  #define local_418 (*(uint *)(_frame + (0x430 - 0x418)))
  #define local_414 (*(uint *)(_frame + (0x430 - 0x414)))
  #define local_410 (*(uint *)(_frame + (0x430 - 0x410)))
  #define local_40c (*(uint *)(_frame + (0x430 - 0x40c)))
  #define local_408 (*(uint *)(_frame + (0x430 - 0x408)))
  #define local_404 (*(uint *)(_frame + (0x430 - 0x404)))
  #define local_400 (*(byte (*)[1024])(_frame + (0x430 - 0x400)))
  
  if (param_2 == (uint *)0x0) {
    param_2 = &local_410;
    local_410 = 0;
    local_40c = 0;
    local_408 = param_1[1];
    local_404 = param_1[2];
  }
  local_420 = 0;
  local_41c = param_5[1];
  local_418 = param_5[2];
  uVar2 = *param_2 - param_3;
  if (0 < (int)uVar2) {
    local_41c = local_41c - uVar2;
    param_3 = param_3 + uVar2;
    local_420 = uVar2;
  }
  iVar3 = param_2[1] - param_4;
  iVar1 = 0;
  if (0 < iVar3) {
    local_418 = local_418 - iVar3;
    param_4 = param_4 + iVar3;
    iVar1 = iVar3;
  }
  if ((int)(param_2[2] + *param_2) < (int)(local_41c + param_3)) {
    local_41c = (param_2[2] + *param_2) - param_3;
  }
  iVar3 = param_2[3] + param_2[1];
  if (iVar3 < (int)(local_418 + param_4)) {
    local_418 = iVar3 - param_4;
  }
  if ((0 < (int)local_41c) && (0 < (int)local_418)) {
    dst = (byte *)(param_3 * param_1[3] + param_4 * param_1[5] + *param_1);
    src = (byte *)(iVar1 * param_5[5] + local_420 * param_5[3] + *param_5);
    if (((param_5[4] == param_1[4]) && (iVar1 = param_5[8], iVar1 == param_1[8])) &&
       (((iVar1 != 1 && (iVar1 != 2)) ||
        ((param_5[0xc] == param_1[0xc] &&
         ((param_5[0xd] == param_1[0xd] && (param_5[0xe] == param_1[0xe])))))))) {
      ((code *)Video_CopyRectDstFirst)(dst,src,0,0,0,0,local_41c * param_1[3],local_418,param_1[5],param_5[5])
      ;
      return;
    }
    local_420 = local_418;
    if ((param_7 == (byte *)0x0) && (param_5[3] == 1)) {
      gra_ConvertMakeLookup(param_5,param_1,local_400,param_6);
      param_7 = local_400;
    }
    do {
      local_420 = local_420 - 1;
      iVar1 = gra_ConvertCopy(src,param_5,local_41c,param_6,dst,param_1,param_7);
      if (iVar1 != 0) {
        return;
      }
      src = src + param_5[5];
      dst = dst + param_1[5];
    } while (local_420 != 0);
  }
  return;
}
#undef local_400
#undef local_404
#undef local_408
#undef local_40c
#undef local_410
#undef local_414
#undef local_418
#undef local_41c
#undef local_420


/* ---- 0x004cec40  gra_SetBuffer ---- */
/* Fills a number of pixels of 1 to 4 bytes with one pixel value Original name gra_SetBuffer (the
   remaster's GrimFandango (Linux): gra_SetBitmap's call (buffer, bitmap, w*h, colour)); was
   Video_FillPixels. */

void __cdecl gra_SetBuffer(char *param_1,int param_2,int param_3,char *param_4)

{
  char cVar1;
  int iVar2;
  undefined3 uVar3;
  undefined4 in_EDX;
  undefined3 uVar4;
  
  iVar2 = *(int *)(param_2 + 0xc) + -1;
  uVar3 = (undefined3)((uint)iVar2 >> 8);
  uVar4 = (undefined3)((uint)in_EDX >> 8);
  switch(iVar2) {
  case 0:
    msc_MemSet((uint)param_1,CONCAT31(uVar3,*param_4),param_3);
    return;
  case 1:
    if (*param_4 == param_4[1]) {
      msc_MemSet((uint)param_1,CONCAT31(uVar3,*param_4),param_3 * 2);
      return;
    }
    if (param_3 != 0) {
      do {
        *(undefined2 *)param_1 = *(undefined2 *)param_4;
        param_1 = param_1 + 2;
        param_3 = param_3 + -1;
      } while (param_3 != 0);
      return;
    }
    break;
  case 2:
    if ((*param_4 == param_4[1]) && (param_4[2] == param_4[1])) {
      msc_MemSet((uint)param_1,CONCAT31(uVar4,*param_4),param_3 * 3);
      return;
    }
    if (param_3 != 0) {
      do {
        *param_1 = *param_4;
        param_1[1] = param_4[1];
        param_1[2] = param_4[2];
        param_1 = param_1 + 3;
        param_3 = param_3 + -1;
      } while (param_3 != 0);
      return;
    }
    break;
  case 3:
    cVar1 = param_4[1];
    if (((*param_4 == cVar1) && (param_4[2] == cVar1)) && (param_4[3] == cVar1)) {
      msc_MemSet((uint)param_1,CONCAT31(uVar4,*param_4),param_3 * 4);
      return;
    }
    for (; param_3 != 0; param_3 = param_3 + -1) {
      *(undefined4 *)param_1 = *(undefined4 *)param_4;
      param_1 = param_1 + 4;
    }
  }
  return;
}

/* ---- 0x004cf010  gra_ConvertToLecColor ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name gra_ConvertToLecColor (the remaster's GrimFandango (Linux): the counterpart of
   gra_ConvertFromLecColor: unpacks 16 / 32-bit pixels by the format's shifts and the
   convert_bitmask table into 4-byte colours; called from gra_ConvertCopy in both builds); was
   Video_PixelsToRgba. */

int __cdecl gra_ConvertToLecColor(void *src,void *fmt,int count,byte *palette,byte *dst)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  ushort uVar13;
  int iVar14;
  int iVar15;
  byte *table;
  uint uVar16;
  
  iVar14 = *(int *)((int)fmt + 0x20);
  if ((iVar14 == 1) && (*(int *)((int)fmt + 0xc) == 2)) {
    iVar15 = *(int *)((int)fmt + 0x30);
    if ((iVar15 == 10) && ((*(int *)((int)fmt + 0x34) == 5 && (*(int *)((int)fmt + 0x38) == 0)))) {
      Video_555ToRgba32((uint *)dst,src,count);
      return 0;
    }
    if (((iVar15 == 0) && (*(int *)((int)fmt + 0x34) == 5)) && (*(int *)((int)fmt + 0x38) == 0xb)) {
      Video_565AltToRgba32((uint *)dst,src,count);
      return 0;
    }
    if (((iVar15 == 0xb) && (*(int *)((int)fmt + 0x34) == 5)) && (*(int *)((int)fmt + 0x38) == 0)) {
      Video_565ToRgba32((uint *)dst,src,count);
      return 0;
    }
  }
  if (iVar14 == 0) {
    table = *(byte **)((int)fmt + 0x24);
    if ((*(byte **)((int)fmt + 0x24) == (byte *)0x0) && (table = palette, palette == (byte *)0x0)) {
      return -1;
    }
    Video_ExpandIndexed8(dst,src,count,4,table);
    return 0;
  }
  if (iVar14 == 1) {
    bVar1 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x28) * 4];
    bVar2 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x24) * 4];
    bVar3 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x2c) * 4];
    bVar4 = *(byte *)((int)fmt + 0x30);
    bVar5 = *(byte *)((int)fmt + 0x34);
    bVar6 = *(byte *)((int)fmt + 0x38);
    bVar7 = *(byte *)((int)fmt + 0x3c);
    bVar8 = *(byte *)((int)fmt + 0x40);
    bVar9 = *(byte *)((int)fmt + 0x44);
    iVar14 = *(int *)((int)fmt + 0xc);
    if (iVar14 == 2) {
      if (count != 0) {
        do {
          uVar13 = *(ushort *)src;
          src = (void *)((int)src + 2);
          *dst = (char)(uVar13 >> (bVar4 & 0x1f)) << (bVar7 & 0x1f) & bVar2;
          dst[1] = (char)(uVar13 >> (bVar5 & 0x1f)) << (bVar8 & 0x1f) & bVar1;
          dst[2] = (char)(uVar13 >> (bVar6 & 0x1f)) << (bVar9 & 0x1f) & bVar3;
          dst[3] = 0xff;
          dst = dst + 4;
          count = count + -1;
        } while (count != 0);
        return 0;
      }
    }
    else if (iVar14 == 3) {
      if (count != 0) {
        do {
          uVar16 = *(uint *)src;
          src = (void *)((int)src + 3);
          uVar16 = uVar16 & 0xffffff;
          *dst = (char)(uVar16 >> (bVar4 & 0x1f)) << (bVar7 & 0x1f) & bVar2;
          dst[1] = (char)(uVar16 >> (bVar5 & 0x1f)) << (bVar8 & 0x1f) & bVar1;
          dst[2] = (char)(uVar16 >> (bVar6 & 0x1f)) << (bVar9 & 0x1f) & bVar3;
          dst[3] = 0xff;
          dst = dst + 4;
          count = count + -1;
        } while (count != 0);
        return 0;
      }
    }
    else {
      if (iVar14 != 4) {
        return -1;
      }
      if (count != 0) {
        do {
          uVar16 = *(uint *)src;
          src = (void *)((int)src + 4);
          *dst = (char)(uVar16 >> (bVar4 & 0x1f)) << (bVar7 & 0x1f) & bVar2;
          dst[1] = (char)(uVar16 >> (bVar5 & 0x1f)) << (bVar8 & 0x1f) & bVar1;
          dst[2] = (char)(uVar16 >> (bVar6 & 0x1f)) << (bVar9 & 0x1f) & bVar3;
          dst[3] = 0xff;
          dst = dst + 4;
          count = count + -1;
        } while (count != 0);
        return 0;
      }
    }
  }
  else {
    if (iVar14 != 2) {
      return -1;
    }
    bVar1 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x28) * 4];
    bVar2 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x24) * 4];
    bVar3 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x2c) * 4];
    bVar4 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x48) * 4];
    bVar5 = *(byte *)((int)fmt + 0x30);
    bVar6 = *(byte *)((int)fmt + 0x34);
    bVar7 = *(byte *)((int)fmt + 0x38);
    bVar8 = *(byte *)((int)fmt + 0x4c);
    bVar9 = *(byte *)((int)fmt + 0x3c);
    bVar10 = *(byte *)((int)fmt + 0x40);
    bVar11 = *(byte *)((int)fmt + 0x44);
    bVar12 = *(byte *)((int)fmt + 0x50);
    iVar14 = *(int *)((int)fmt + 0xc);
    if (iVar14 == 2) {
      if (count != 0) {
        do {
          uVar13 = *(ushort *)src;
          src = (void *)((int)src + 2);
          *dst = (char)(uVar13 >> (bVar5 & 0x1f)) << (bVar9 & 0x1f) & bVar2;
          dst[1] = (char)(uVar13 >> (bVar6 & 0x1f)) << (bVar10 & 0x1f) & bVar1;
          dst[2] = (char)(uVar13 >> (bVar7 & 0x1f)) << (bVar11 & 0x1f) & bVar3;
          dst[3] = (char)(uVar13 >> (bVar8 & 0x1f)) << (bVar12 & 0x1f) & bVar4;
          dst = dst + 4;
          count = count + -1;
        } while (count != 0);
        return 0;
      }
    }
    else if (iVar14 == 3) {
      if (count != 0) {
        do {
          uVar16 = *(uint *)src;
          src = (void *)((int)src + 3);
          uVar16 = uVar16 & 0xffffff;
          *dst = (char)(uVar16 >> (bVar5 & 0x1f)) << (bVar9 & 0x1f) & bVar2;
          dst[1] = (char)(uVar16 >> (bVar6 & 0x1f)) << (bVar10 & 0x1f) & bVar1;
          dst[2] = (char)(uVar16 >> (bVar7 & 0x1f)) << (bVar11 & 0x1f) & bVar3;
          dst[3] = (char)(uVar16 >> (bVar8 & 0x1f)) << (bVar12 & 0x1f) & bVar4;
          dst = dst + 4;
          count = count + -1;
        } while (count != 0);
        return 0;
      }
    }
    else {
      if (iVar14 != 4) {
        return -1;
      }
      for (; count != 0; count = count + -1) {
        uVar16 = *(uint *)src;
        src = (void *)((int)src + 4);
        *dst = (char)(uVar16 >> (bVar5 & 0x1f)) << (bVar9 & 0x1f) & bVar2;
        dst[1] = (char)(uVar16 >> (bVar6 & 0x1f)) << (bVar10 & 0x1f) & bVar1;
        dst[2] = (char)(uVar16 >> (bVar7 & 0x1f)) << (bVar11 & 0x1f) & bVar3;
        dst[3] = (char)(uVar16 >> (bVar8 & 0x1f)) << (bVar12 & 0x1f) & bVar4;
        dst = dst + 4;
      }
    }
  }
  return 0;
}
#endif


/* ---- 0x004cf520  gra_ConvertFromLecColor ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name gra_ConvertFromLecColor (the remaster's GrimFandango (Linux): gra_SetBitmap's call
   (dst, bitmap, 1, 0, &colour)); was Video_PixelsFromRgba. */

int __cdecl gra_ConvertFromLecColor(void *dst,void *fmt,int count,int unused,byte *src)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  int iVar13;
  uint uVar14;
  byte *pbVar15;
  undefined1 *puVar16;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  if (*(int *)((int)fmt + 0x20) == 1) {
    if (*(int *)((int)fmt + 0xc) == 2) {
      iVar13 = *(int *)((int)fmt + 0x30);
      if (((iVar13 == 10) && (*(int *)((int)fmt + 0x34) == 5)) && (*(int *)((int)fmt + 0x38) == 0))
      {
        Video_Rgba32To555(dst,(uint *)src,count);
        return 0;
      }
      if (((iVar13 == 0) && (*(int *)((int)fmt + 0x34) == 5)) && (*(int *)((int)fmt + 0x38) == 0xb))
      {
        Video_Rgba32To565Alt(dst,(uint *)src,count);
        return 0;
      }
      if (((iVar13 == 0xb) && (*(int *)((int)fmt + 0x34) == 5)) && (*(int *)((int)fmt + 0x38) == 0))
      {
        Video_Rgba32To565(dst,(uint *)src,count);
        return 0;
      }
    }
    bVar1 = *(byte *)((int)fmt + 0x34);
    bVar2 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x24) * 4];
    bVar3 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x28) * 4];
    bVar4 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x2c) * 4];
    bVar5 = *(byte *)((int)fmt + 0x30);
    bVar6 = *(byte *)((int)fmt + 0x38);
    bVar7 = *(byte *)((int)fmt + 0x3c);
    bVar8 = *(byte *)((int)fmt + 0x40);
    bVar9 = *(byte *)((int)fmt + 0x44);
    iVar13 = *(int *)((int)fmt + 0xc);
    if (iVar13 == 1) {
      if (count != 0) {
        pbVar15 = src + 2;
        do {
          *(byte *)dst = (byte)((int)((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >>
                               (bVar8 & 0x1f)) |
                         (byte)((int)((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar9 & 0x1f))
                         | (byte)((int)((uint)(pbVar15[-2] & bVar2) << (bVar5 & 0x1f)) >>
                                 (bVar7 & 0x1f));
          dst = (void *)((int)dst + 1);
          count = count + -1;
          pbVar15 = pbVar15 + 4;
        } while (count != 0);
        return 0;
      }
    }
    else if (iVar13 == 2) {
      if (count != 0) {
        pbVar15 = src + 2;
        do {
          count = count + -1;
          *(ushort *)dst =
               (ushort)((int)((uint)(pbVar15[-2] & bVar2) << (bVar5 & 0x1f)) >> (bVar7 & 0x1f)) |
               (ushort)((int)((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar9 & 0x1f)) |
               (ushort)((int)((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar8 & 0x1f));
          pbVar15 = pbVar15 + 4;
          dst = (ushort *)((int)dst + 2);
        } while (count != 0);
        return 0;
      }
    }
    else if (iVar13 == 3) {
      if (count != 0) {
        puVar16 = dst;
        pbVar15 = src + 2;
        do {
          uVar14 = ((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar8 & 0x1f) |
                   ((uint)(pbVar15[-2] & bVar2) << (bVar5 & 0x1f)) >> (bVar7 & 0x1f) |
                   ((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar9 & 0x1f);
          *puVar16 = (char)uVar14;
          PIECE(dst,2,1) = (undefined1)(uVar14 >> 0x10);
          puVar16[1] = (char)(uVar14 >> 8);
          puVar16[2] = PIECE(dst,2,1);
          puVar16 = puVar16 + 3;
          count = count + -1;
          pbVar15 = pbVar15 + 4;
        } while (count != 0);
        return 0;
      }
    }
    else {
      if (iVar13 != 4) {
        return -1;
      }
      if (count != 0) {
        pbVar15 = src + 2;
        do {
          count = count + -1;
          *(uint *)dst = ((uint)(pbVar15[-2] & bVar2) << (bVar5 & 0x1f)) >> (bVar7 & 0x1f) |
                         ((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar9 & 0x1f) |
                         ((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar8 & 0x1f);
          pbVar15 = pbVar15 + 4;
          dst = (uint *)((int)dst + 4);
        } while (count != 0);
        return 0;
      }
    }
  }
  else {
    if (*(int *)((int)fmt + 0x20) != 2) {
      return -1;
    }
    bVar1 = *(byte *)((int)fmt + 0x34);
    bVar2 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x24) * 4];
    bVar3 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x28) * 4];
    bVar4 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x2c) * 4];
    bVar5 = (&g_aConvert_bitmask)[*(int *)((int)fmt + 0x48) * 4];
    bVar6 = *(byte *)((int)fmt + 0x38);
    bVar7 = *(byte *)((int)fmt + 0x4c);
    bVar8 = *(byte *)((int)fmt + 0x3c);
    bVar9 = *(byte *)((int)fmt + 0x40);
    bVar10 = *(byte *)((int)fmt + 0x44);
    bVar11 = *(byte *)((int)fmt + 0x30);
    bVar12 = *(byte *)((int)fmt + 0x50);
    iVar13 = *(int *)((int)fmt + 0xc);
    if (iVar13 == 2) {
      if (count != 0) {
        pbVar15 = src + 2;
        do {
          count = count + -1;
          *(ushort *)dst =
               (ushort)((int)((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar10 & 0x1f)) |
               (ushort)((int)((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar9 & 0x1f)) |
               (ushort)((int)((uint)(pbVar15[-2] & bVar2) << (bVar11 & 0x1f)) >> (bVar8 & 0x1f)) |
               (ushort)((int)((uint)(pbVar15[1] & bVar5) << (bVar7 & 0x1f)) >> (bVar12 & 0x1f));
          pbVar15 = pbVar15 + 4;
          dst = (ushort *)((int)dst + 2);
        } while (count != 0);
        return 0;
      }
    }
    else if (iVar13 == 3) {
      if (count != 0) {
        puVar16 = dst;
        pbVar15 = src + 2;
        do {
          uVar14 = ((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar10 & 0x1f) |
                   ((uint)(pbVar15[-2] & bVar2) << (bVar11 & 0x1f)) >> (bVar8 & 0x1f) |
                   ((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar9 & 0x1f) |
                   ((uint)(pbVar15[1] & bVar5) << (bVar7 & 0x1f)) >> (bVar12 & 0x1f);
          *puVar16 = (char)uVar14;
          PIECE(dst,2,1) = (undefined1)(uVar14 >> 0x10);
          puVar16[1] = (char)(uVar14 >> 8);
          puVar16[2] = PIECE(dst,2,1);
          puVar16 = puVar16 + 3;
          count = count + -1;
          pbVar15 = pbVar15 + 4;
        } while (count != 0);
        return 0;
      }
    }
    else {
      if (iVar13 != 4) {
        return -1;
      }
      if (count != 0) {
        pbVar15 = src + 2;
        do {
          count = count + -1;
          *(uint *)dst = ((uint)(pbVar15[1] & bVar5) << (bVar7 & 0x1f)) >> (bVar12 & 0x1f) |
                         ((uint)(pbVar15[-2] & bVar2) << (bVar11 & 0x1f)) >> (bVar8 & 0x1f) |
                         ((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar9 & 0x1f) |
                         ((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar10 & 0x1f);
          pbVar15 = pbVar15 + 4;
          dst = (uint *)((int)dst + 4);
        } while (count != 0);
      }
    }
  }
  return 0;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004cfdb0  Video_CopyRectDstFirst ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* The remaster calls this function gra_CopyRect (GrimFandango (Linux): the same-format copy of
   gra_BlitRectLookup (dst, src, 0, 0, 0, 0, width * bpp, rows, dst pitch, src pitch) in both
   builds; here it calls the assembler copy Video_CopyRect, the remaster msc_MemCopy per row). Not
   renamed: with the shorter name Ghidra wraps the call in gra_BlitRectLookup differently, build_src
   then drops its (code *) cast and the generated code changes. */

void __cdecl
Video_CopyRectDstFirst
          (byte *dst,byte *src,int dstX,uint dstY,int srcX,uint srcY,uint width,int rows,
          uint dstPitch,uint srcPitch)

{
  Video_CopyRect(src,dst,srcX,srcY,dstX,dstY,width,rows,srcPitch,dstPitch);
  return;
}
#endif


/* ---- 0x004cfdf0  Video_ExpandIndexed8 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Video_ExpandIndexed8(byte *dst,byte *src,int count,int bytesPerPixel,byte *table)

{
  byte bVar1;
  ushort uVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;
  
  cVar6 = (char)bytesPerPixel;
  if (cVar6 == '\x01') {
    do {
      bVar1 = *src;
      src = src + 1;
      *dst = table[bVar1];
      iVar5 = count + -1;
      dst = dst + 1;
      bVar3 = 0 < count;
      count = iVar5;
    } while (iVar5 != 0 && bVar3);
  }
  else if (cVar6 == '\x02') {
    uVar7 = (uint)count >> 1;
    if ((count & 1U) != 0) {
      bVar1 = *src;
      src = src + 1;
      *(undefined2 *)dst = *(undefined2 *)(table + (uint)bVar1 * 2);
      dst = dst + 2;
    }
    do {
      uVar2 = *(ushort *)src;
      src = (byte *)((int)src + 2);
      *(uint *)dst = CONCAT22(*(undefined2 *)(table + (uint)(byte)(uVar2 >> 8) * 2),
                              *(undefined2 *)(table + (uVar2 & 0xffff00ff) * 2));
      uVar8 = uVar7 - 1;
      dst = dst + 4;
      bVar3 = 0 < (int)uVar7;
      uVar7 = uVar8;
    } while (uVar8 != 0 && bVar3);
  }
  else if (cVar6 == '\x03') {
    iVar5 = 0;
    do {
      iVar5 = CONCAT31((int3)((uint)iVar5 >> 8),*src) * 3;
      src = src + 1;
      *(undefined4 *)dst = *(undefined4 *)(table + iVar5);
      iVar4 = count + -1;
      dst = dst + 3;
      bVar3 = 0 < count;
      count = iVar4;
    } while (iVar4 != 0 && bVar3);
  }
  else if (cVar6 == '\x04') {
    do {
      bVar1 = *src;
      src = src + 1;
      *(undefined4 *)dst = *(undefined4 *)(table + (uint)bVar1 * 4);
      iVar5 = count + -1;
      dst = dst + 4;
      bVar3 = 0 < count;
      count = iVar5;
    } while (iVar5 != 0 && bVar3);
  }
  return;
}
#endif


/* ---- 0x004cfea0  Video_ExpandIndexed16 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_8 */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* WARNING: Variable defined which should be unmapped: local_c */

void __cdecl Video_ExpandIndexed16(byte *dst,ushort *src,int count,int bytesPerPixel,byte *table)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  char cVar5;
  uint *unaff_EBX;
  uint unaff_EBP;
  uint uVar6;
  uint *unaff_ESI;
  uint local_res0;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  cVar5 = (char)local_res0;
  if (cVar5 == '\x01') {
    do {
      uVar4 = *unaff_EBX;
      unaff_EBX = (uint *)((int)unaff_EBX + 2);
      *(byte *)unaff_ESI = dst[(ushort)uVar4];
      uVar4 = unaff_EBP - 1;
      unaff_ESI = (uint *)((int)unaff_ESI + 1);
      bVar2 = 0 < (int)unaff_EBP;
      unaff_EBP = uVar4;
    } while (uVar4 != 0 && bVar2);
  }
  else if (cVar5 == '\x02') {
    uVar4 = unaff_EBP >> 1;
    if ((unaff_EBP & 1) != 0) {
      uVar4 = *unaff_EBX;
      unaff_EBX = (uint *)((int)unaff_EBX + 2);
      *(undefined2 *)unaff_ESI = *(undefined2 *)(dst + (uint)(ushort)uVar4 * 2);
      uVar4 = unaff_EBP >> 1;
      unaff_ESI = (uint *)((int)unaff_ESI + 2);
    }
    do {
      uVar1 = *unaff_EBX;
      unaff_EBX = unaff_EBX + 1;
      uVar6 = uVar4 - 1;
      *unaff_ESI = (uint)*(ushort *)(dst + (uVar1 & 0xffff) * 2) |
                   CONCAT22(*(ushort *)(dst + (uVar1 & 0xffff) * 2),
                            *(undefined2 *)(dst + (uVar1 >> 0x10) * 2)) << 0x10;
      bVar2 = 0 < (int)uVar4;
      uVar4 = uVar6;
      unaff_ESI = unaff_ESI + 1;
    } while (uVar6 != 0 && bVar2);
  }
  else if (cVar5 == '\x03') {
    iVar3 = 0;
    do {
      iVar3 = CONCAT22((short)((uint)iVar3 >> 0x10),(ushort)*unaff_EBX) * 3;
      unaff_EBX = (uint *)((int)unaff_EBX + 2);
      *unaff_ESI = *(uint *)(dst + iVar3);
      uVar4 = unaff_EBP - 1;
      unaff_ESI = (uint *)((int)unaff_ESI + 3);
      bVar2 = 0 < (int)unaff_EBP;
      unaff_EBP = uVar4;
    } while (uVar4 != 0 && bVar2);
  }
  else if (cVar5 == '\x04') {
    do {
      uVar4 = *unaff_EBX;
      unaff_EBX = (uint *)((int)unaff_EBX + 2);
      *unaff_ESI = *(uint *)(dst + (uint)(ushort)uVar4 * 4);
      uVar4 = unaff_EBP - 1;
      unaff_ESI = unaff_ESI + 1;
      bVar2 = 0 < (int)unaff_EBP;
      unaff_EBP = uVar4;
    } while (uVar4 != 0 && bVar2);
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004cff60  Video_Rgba32To555 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Video_Rgba32To555(ushort *dst,uint *src,uint count)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  uVar2 = count >> 1;
  if ((count & 1) != 0) {
    uVar2 = *src & 0xf8f8f8;
    iVar5 = (uint)CONCAT11((byte)uVar2 >> 3,(char)(uVar2 >> 8)) << 2;
    *dst = (ushort)CONCAT31((int3)((uint)iVar5 >> 8),(byte)iVar5 | (byte)((uVar2 >> 0xb) >> 8));
    src = src + 1;
    dst = dst + 1;
    uVar2 = count >> 1;
  }
  do {
    uVar3 = src[1] & 0xf8f8f8;
    uVar4 = *src & 0xf8f8f8;
    iVar6 = (uint)CONCAT11((byte)uVar3 >> 3,(char)(uVar3 >> 8)) << 2;
    iVar5 = (uint)CONCAT11((byte)uVar4 >> 3,(char)(uVar4 >> 8)) << 2;
    *(uint *)dst = CONCAT22((short)CONCAT31((int3)((uint)iVar6 >> 8),
                                            (byte)iVar6 | (byte)((uVar3 >> 0xb) >> 8)),
                            (short)CONCAT31((int3)((uint)iVar5 >> 8),
                                            (byte)iVar5 | (byte)((uVar4 >> 0xb) >> 8)));
    src = src + 2;
    dst = dst + 2;
    uVar3 = uVar2 - 1;
    bVar1 = 0 < (int)uVar2;
    uVar2 = uVar3;
  } while (uVar3 != 0 && bVar1);
  return;
}
#endif


/* ---- 0x004cffe0  Video_555ToRgba32 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Video_555ToRgba32(uint *dst,ushort *src,uint count)

{
  ushort uVar1;
  bool bVar2;
  uint in_EDX;
  ushort uVar3;
  uint unaff_EBX;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar6 = count >> 1;
  if ((count & 1) != 0) {
    uVar1 = *src;
    uVar4 = (ushort)(unaff_EBX >> 0x17) | (ushort)(((uint)(byte)(uVar1 >> 8) << 0x19) >> 0x10);
    unaff_EBX = CONCAT31(CONCAT21(uVar4,(char)uVar1 << 3),(char)(((uint)uVar1 << 6) >> 8)) << 8 |
                (uint)(uVar4 >> 8) | 0xff070707;
    *dst = unaff_EBX;
    src = src + 1;
    dst = dst + 1;
  }
  do {
    uVar1 = src[1];
    uVar4 = *src;
    uVar5 = (ushort)(unaff_EBX >> 0x17) | (ushort)(((uint)(byte)(uVar1 >> 8) << 0x19) >> 0x10);
    uVar3 = (ushort)(in_EDX >> 0x17) | (ushort)(((uint)(byte)(uVar4 >> 8) << 0x19) >> 0x10);
    unaff_EBX = CONCAT31(CONCAT21(uVar5,(char)uVar1 << 3),(char)(((uint)uVar1 << 6) >> 8)) << 8 |
                (uint)(uVar5 >> 8) | 0xff070707;
    in_EDX = CONCAT31(CONCAT21(uVar3,(char)uVar4 << 3),(char)(((uint)uVar4 << 6) >> 8)) << 8 |
             (uint)(uVar3 >> 8) | 0xff070707;
    dst[1] = unaff_EBX;
    *dst = in_EDX;
    src = src + 2;
    dst = dst + 2;
    uVar7 = uVar6 - 1;
    bVar2 = 0 < (int)uVar6;
    uVar6 = uVar7;
  } while (uVar7 != 0 && bVar2);
  return;
}
#endif


/* ---- 0x004d0070  Video_Rgba32To565 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Video_Rgba32To565(ushort *dst,uint *src,uint count)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  uVar2 = count >> 1;
  if ((count & 1) != 0) {
    uVar2 = *src & 0xf8fcf8;
    iVar5 = (uint)CONCAT11((byte)uVar2 >> 3,(char)(uVar2 >> 8)) << 3;
    *dst = (ushort)CONCAT31((int3)((uint)iVar5 >> 8),(byte)iVar5 | (byte)((uVar2 >> 0xb) >> 8));
    src = src + 1;
    dst = dst + 1;
    uVar2 = count >> 1;
  }
  do {
    uVar3 = src[1] & 0xf8fcf8;
    uVar4 = *src & 0xf8fcf8;
    iVar6 = (uint)CONCAT11((byte)uVar3 >> 3,(char)(uVar3 >> 8)) << 3;
    iVar5 = (uint)CONCAT11((byte)uVar4 >> 3,(char)(uVar4 >> 8)) << 3;
    *(uint *)dst = CONCAT22((short)CONCAT31((int3)((uint)iVar6 >> 8),
                                            (byte)iVar6 | (byte)((uVar3 >> 0xb) >> 8)),
                            (short)CONCAT31((int3)((uint)iVar5 >> 8),
                                            (byte)iVar5 | (byte)((uVar4 >> 0xb) >> 8)));
    src = src + 2;
    dst = dst + 2;
    uVar3 = uVar2 - 1;
    bVar1 = 0 < (int)uVar2;
    uVar2 = uVar3;
  } while (uVar3 != 0 && bVar1);
  return;
}
#endif


/* ---- 0x004d00f0  Video_565ToRgba32 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Video_565ToRgba32(uint *dst,ushort *src,uint count)

{
  ushort uVar1;
  ushort uVar2;
  bool bVar3;
  uint in_EDX;
  uint unaff_EBX;
  uint uVar4;
  uint uVar5;
  
  uVar4 = count >> 1;
  if ((count & 1) != 0) {
    uVar1 = *src;
    unaff_EBX = CONCAT31(CONCAT21(CONCAT11((char)(unaff_EBX >> 0x18),(char)uVar1 << 3),
                                  (char)(((uint)uVar1 << 5) >> 8)),(char)(uVar1 >> 8)) | 0xff070307;
    *dst = unaff_EBX;
    src = src + 1;
    dst = dst + 1;
  }
  do {
    uVar1 = src[1];
    uVar2 = *src;
    unaff_EBX = CONCAT31(CONCAT21(CONCAT11((char)(unaff_EBX >> 0x18),(char)uVar1 << 3),
                                  (char)(((uint)uVar1 << 5) >> 8)),(char)(uVar1 >> 8)) | 0xff070307;
    in_EDX = CONCAT31(CONCAT21(CONCAT11((char)(in_EDX >> 0x18),(char)uVar2 << 3),
                               (char)(((uint)uVar2 << 5) >> 8)),(char)(uVar2 >> 8)) | 0xff070307;
    dst[1] = unaff_EBX;
    *dst = in_EDX;
    src = src + 2;
    dst = dst + 2;
    uVar5 = uVar4 - 1;
    bVar3 = 0 < (int)uVar4;
    uVar4 = uVar5;
  } while (uVar5 != 0 && bVar3);
  return;
}
#endif


/* ---- 0x004d0180  Video_Rgba32To565Alt ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Video_Rgba32To565Alt(ushort *dst,uint *src,uint count)

{
  bool bVar1;
  short sVar2;
  ushort uVar3;
  short sVar4;
  ushort uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar6 = count >> 1;
  if ((count & 1) != 0) {
    uVar3 = (ushort)(*src >> 0x13);
    sVar2 = (short)(*src >> 3) << 1;
    *dst = (ushort)(CONCAT22(uVar3,(short)CONCAT31((int3)(CONCAT22(uVar3,sVar2) >> 8),
                                                   (char)sVar2 << 2) << 2) >> 5);
    src = src + 1;
    dst = dst + 1;
  }
  do {
    uVar3 = (ushort)(src[1] >> 0x13);
    sVar2 = (short)(src[1] >> 3) << 1;
    uVar5 = (ushort)(*src >> 0x13);
    sVar4 = (short)(*src >> 3) << 1;
    *(uint *)dst = CONCAT22((short)(CONCAT22(uVar3,(short)CONCAT31((int3)(CONCAT22(uVar3,sVar2) >> 8
                                                                         ),(char)sVar2 << 2) << 2)
                                   >> 5),
                            (short)(CONCAT22(uVar5,(short)CONCAT31((int3)(CONCAT22(uVar5,sVar4) >> 8
                                                                         ),(char)sVar4 << 2) << 2)
                                   >> 5));
    src = src + 2;
    dst = dst + 2;
    uVar7 = uVar6 - 1;
    bVar1 = 0 < (int)uVar6;
    uVar6 = uVar7;
  } while (uVar7 != 0 && bVar1);
  return;
}
#endif


/* ---- 0x004d01f0  Video_565AltToRgba32 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Video_565AltToRgba32(uint *dst,ushort *src,uint count)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = count >> 1;
  if ((count & 1) != 0) {
    iVar2 = CONCAT22((short)(((uint)*src << 5) >> 0x10),(ushort)((uint)*src << 5) >> 3) << 1;
    *dst = CONCAT31((int3)((uint)iVar2 >> 8),(byte)iVar2 >> 2) << 2;
    src = src + 1;
    dst = dst + 1;
  }
  do {
    iVar2 = CONCAT22((short)(((uint)src[1] << 5) >> 0x10),(ushort)((uint)src[1] << 5) >> 3) << 1;
    iVar3 = CONCAT22((short)(((uint)*src << 5) >> 0x10),(ushort)((uint)*src << 5) >> 3) << 1;
    dst[1] = CONCAT31((int3)((uint)iVar2 >> 8),(byte)iVar2 >> 2) << 2;
    *dst = CONCAT31((int3)((uint)iVar3 >> 8),(byte)iVar3 >> 2) << 2;
    src = src + 2;
    dst = dst + 2;
    uVar5 = uVar4 - 1;
    bVar1 = 0 < (int)uVar4;
    uVar4 = uVar5;
  } while (uVar5 != 0 && bVar1);
  return;
}
#endif


/* ---- 0x004d0260  Video_CopyRect ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl
Video_CopyRect(byte *src,byte *dst,int srcX,uint srcY,int dstX,uint dstY,uint width,int rows,
              uint srcPitch,uint dstPitch)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  
  uVar3 = (srcY & 0xffff) * (srcPitch & 0xffff);
  pbVar7 = src + (CONCAT22((short)(srcY >> 0x10),(short)uVar3) | uVar3 & 0xffff0000) + srcX;
  uVar3 = (dstY & 0xffff) * (dstPitch & 0xffff);
  pbVar8 = dst + (CONCAT22((short)(dstY >> 0x10),(short)uVar3) | uVar3 & 0xffff0000) + dstX;
  iVar5 = srcPitch - width;
  iVar4 = dstPitch - width;
  if ((width & 3) == 0) {
    if (iVar4 == 0) {
      uVar3 = width >> 2;
      do {
        for (; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined4 *)pbVar8 = *(undefined4 *)pbVar7;
          pbVar7 = pbVar7 + 4;
          pbVar8 = pbVar8 + 4;
        }
        pbVar7 = pbVar7 + iVar5;
        iVar4 = rows + -1;
        bVar1 = 0 < rows;
        uVar3 = width >> 2;
        rows = iVar4;
      } while (iVar4 != 0 && bVar1);
    }
    else {
      uVar3 = width >> 2;
      do {
        for (; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined4 *)pbVar8 = *(undefined4 *)pbVar7;
          pbVar7 = pbVar7 + 4;
          pbVar8 = pbVar8 + 4;
        }
        pbVar8 = pbVar8 + iVar4;
        pbVar7 = pbVar7 + iVar5;
        iVar6 = rows + -1;
        bVar1 = 0 < rows;
        uVar3 = width >> 2;
        rows = iVar6;
      } while (iVar6 != 0 && bVar1);
    }
  }
  else {
    uVar3 = width >> 2;
    do {
      for (; uVar2 = width & 3, uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pbVar8 = *(undefined4 *)pbVar7;
        pbVar7 = pbVar7 + 4;
        pbVar8 = pbVar8 + 4;
      }
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pbVar8 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        pbVar8 = pbVar8 + 1;
      }
      pbVar8 = pbVar8 + iVar4;
      pbVar7 = pbVar7 + iVar5;
      iVar6 = rows + -1;
      bVar1 = 0 < rows;
      uVar3 = width >> 2;
      rows = iVar6;
    } while (iVar6 != 0 && bVar1);
  }
  return;
}
#undef local_34
#undef local_38

#endif

