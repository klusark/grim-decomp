/* GRIMFANDANGO.EXE :: videobitmap.c
 * functions 0x004ce3e0 .. 0x004cedc0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004ce3e0  bmp_bitmap_Alloc ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name bmp_bitmap_Alloc (the remaster's GrimFandango (Linux): slot 0 of the
   "BITMAP=insane" service table); was VideoBitmap_Create. */

int __cdecl bmp_bitmap_Alloc(void *out,int width,int height,int format)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  switch(format) {
  case 1:
    local_4 = 0x100;
  case 0:
    iVar2 = 1;
    break;
  case 2:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
    iVar2 = 2;
    break;
  case 4:
  case 9:
    iVar2 = 3;
    break;
  case 6:
  case 0xb:
  case 0xc:
    iVar2 = 4;
    break;
  case -1:
    if (g_dwVideo_video_services == 0) {
      uVar3 = 0xbe;
      goto LAB_004ce7b5;
    }
    iVar2 = (**(code **)(g_dwVideo_video_services + 4))();
    iVar2 = *(int *)(iVar2 + 0xc);
    break;
  default:
    uVar3 = 0xc4;
LAB_004ce7b5:
    msc_error_SaveString
              (s__s__line__s__Type__d_not_support_004f3d40,
               s_C__grimsrc_libs_lecsmush_insane__004f3d64,uVar3,format);
    return -1;
  }
  iVar1 = (*(code *)*g_pVideo_memory_services)
                    (iVar2 * height * width + 0x5c + local_4 * 4,
                     s_C__grimsrc_libs_lecsmush_insane__004f3d64,200);
  if (iVar1 == 0) {
    return -0x65;
  }
  *(int **)out = (int *)(iVar1 + 8);
  *(int *)(iVar1 + 8) = iVar1 + 0x5c;
  *(int *)(*(int *)out + 4) = width;
  *(int *)(*(int *)out + 0x14) = iVar2 * width;
  *(int *)(*(int *)out + 8) = height;
  *(int *)(*(int *)out + 0xc) = iVar2;
  *(undefined4 *)(*(int *)out + 0x1c) = 0;
  *(undefined4 *)(*(int *)out + 0x18) = 0;
                    /* WARNING: Could not recover jumptable at 0x004ce4a6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar2 = (**(code **)(&DAT_004ce808 + (format + 1) * 4))();
  return iVar2;
}
#undef local_4

#endif


/* ---- 0x004cedc0  gra_ConvertCopy ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name gra_ConvertCopy (the remaster's GrimFandango (Linux): same parameters (src, srcFmt,
   count, palette, dst, dstFmt, lookup) and body (memcpy when the formats agree, the lookup
   expansion, then gra_ConvertToLecColor / gra_ConvertFromLecColor in chunks); called after the
   0..0xffff translation table fill in both blocky16 decoders); was VideoBitmap_ConvertPixels. */

int __cdecl
gra_ConvertCopy(byte *src,void *srcFmt,int count,byte *palette,byte *dst,void *dstFmt,
               byte *expandTable)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (((*(int *)((int)srcFmt + 0x10) == *(int *)((int)dstFmt + 0x10)) &&
      (iVar5 = *(int *)((int)srcFmt + 0x20), iVar5 == *(int *)((int)dstFmt + 0x20))) &&
     (((iVar5 != 1 && (iVar5 != 2)) ||
      (((*(int *)((int)srcFmt + 0x30) == *(int *)((int)dstFmt + 0x30) &&
        (*(int *)((int)srcFmt + 0x34) == *(int *)((int)dstFmt + 0x34))) &&
       (*(int *)((int)srcFmt + 0x38) == *(int *)((int)dstFmt + 0x38))))))) {
    msc_MemCopy(dst,src,*(int *)((int)dstFmt + 0xc) * count);
    return 0;
  }
  if (expandTable != (byte *)0x0) {
    if ((*(int *)((int)srcFmt + 0x20) == 0) && (*(int *)((int)srcFmt + 0xc) == 1)) {
      Video_ExpandIndexed8(dst,src,count,*(int *)((int)dstFmt + 0xc),expandTable);
      return 0;
    }
    if (((expandTable != (byte *)0x0) && (*(int *)((int)srcFmt + 0xc) == 2)) &&
       (*(int *)((int)dstFmt + 0x20) != 0)) {
      Video_ExpandIndexed16(dst,(ushort *)src,count,*(int *)((int)dstFmt + 0xc),expandTable);
      return 0;
    }
  }
  if ((((*(int *)((int)srcFmt + 0x20) != 2) || (*(int *)((int)srcFmt + 0xc) != 4)) ||
      (*(int *)((int)srcFmt + 0x30) != 0)) ||
     ((*(int *)((int)srcFmt + 0x34) != 8 || (bVar1 = true, *(int *)((int)srcFmt + 0x38) != 0x10))))
  {
    bVar1 = false;
  }
  if (((*(int *)((int)dstFmt + 0x20) != 2) || (*(int *)((int)dstFmt + 0xc) != 4)) ||
     ((*(int *)((int)dstFmt + 0x30) != 0 ||
      ((*(int *)((int)dstFmt + 0x34) != 8 || (bVar2 = true, *(int *)((int)dstFmt + 0x38) != 0x10))))
     )) {
    bVar2 = false;
  }
  iVar5 = count;
  if (0x4ff < count) {
    iVar5 = 0x500;
  }
  if (iVar5 < 1) {
    return 0;
  }
  while( true ) {
    if (bVar1) {
      iVar3 = gra_ConvertFromLecColor(dst,dstFmt,iVar5,(int)palette,src);
    }
    else if (bVar2) {
      iVar3 = gra_ConvertToLecColor(src,srcFmt,iVar5,palette,dst);
    }
    else {
      UINT_008da8a0 = UINT_008da8a0 + 1;
      uVar4 = UINT_008da8a0 & 1;
      iVar3 = gra_ConvertToLecColor(src,srcFmt,iVar5,palette,&DAT_009272a0 + uVar4 * 0x1400);
      if (iVar3 != 0) {
        return -1;
      }
      iVar3 = gra_ConvertFromLecColor(dst,dstFmt,iVar5,(int)palette,&DAT_009272a0 + uVar4 * 0x1400);
    }
    if (iVar3 != 0) break;
    count = count - iVar5;
    src = src + *(int *)((int)srcFmt + 0xc) * iVar5;
    dst = dst + *(int *)((int)dstFmt + 0xc) * iVar5;
    iVar5 = count;
    if (0x4ff < count) {
      iVar5 = 0x500;
    }
    if (iVar5 < 1) {
      return 0;
    }
  }
  return -1;
}
#undef local_4

#endif

