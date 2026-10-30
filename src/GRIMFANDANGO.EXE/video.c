/* GRIMFANDANGO.EXE :: video.c
 * functions 0x004cf010 .. 0x004d0260 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004cf010  Video_PixelsToRgba ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl Video_PixelsToRgba(void *src,void *fmt,int count,byte *palette,byte *dst)

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
    bVar1 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x28) * 4];
    bVar2 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x24) * 4];
    bVar3 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x2c) * 4];
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
    bVar1 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x28) * 4];
    bVar2 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x24) * 4];
    bVar3 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x2c) * 4];
    bVar4 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x48) * 4];
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


/* ---- 0x004cf520  Video_PixelsFromRgba ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl Video_PixelsFromRgba(void *dst,void *fmt,int count,int unused,byte *src)

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
    bVar2 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x24) * 4];
    bVar3 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x28) * 4];
    bVar4 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x2c) * 4];
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
    bVar2 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x24) * 4];
    bVar3 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x28) * 4];
    bVar4 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x2c) * 4];
    bVar5 = (&DAT_004f3da0)[*(int *)((int)fmt + 0x48) * 4];
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

