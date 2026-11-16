/* GRIMFANDANGO.EXE :: stdpcx.c
 * functions 0x0047b710 .. 0x0047ef10 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047b710  stdPcx_DecodeRun16 ---- */
/* PCX RLE run decode into 16-bit pixels via a 256-entry lookup */

uint __cdecl stdPcx_DecodeRun16(byte *palette,ushort *dst,int count)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar4 = palette;
  palette = (byte *)0x100;
  do {
    bVar1 = *pbVar4;
    pbVar2 = pbVar4 + 1;
    pbVar3 = pbVar4 + 2;
    pbVar4 = pbVar4 + 3;
    *dst = (ushort)(bVar1 >> (*(byte *)(count + 0x20) & 0x1f)) <<
           ((byte)*(undefined4 *)(count + 0x14) & 0x1f) |
           (ushort)(*pbVar2 >> (*(byte *)(count + 0x24) & 0x1f)) <<
           ((byte)*(undefined4 *)(count + 0x18) & 0x1f) |
           (ushort)(*pbVar3 >> (*(byte *)(count + 0x28) & 0x1f)) <<
           ((byte)*(undefined4 *)(count + 0x1c) & 0x1f);
    palette = palette + -1;
    dst = dst + 1;
  } while (palette != (byte *)0x0);
  return 1;
}

/* ---- 0x0047b780  stdPcx_DecodeRun8 ---- */
uint __cdecl stdPcx_DecodeRun8(byte *palette,int dst,int count)

{
  byte *pbVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar4 = palette;
  palette = (byte *)0x0;
  do {
    bVar2 = *pbVar4;
    pbVar1 = pbVar4 + 1;
    pbVar3 = pbVar4 + 2;
    pbVar4 = pbVar4 + 3;
    *(ushort *)(dst + (int)palette * 2) =
         (ushort)(((-(uint)(palette != (byte *)0x0) & 0xff) >>
                  ((byte)*(undefined4 *)(count + 0x34) & 0x1f)) <<
                 ((byte)*(undefined4 *)(count + 0x30) & 0x1f)) |
         (ushort)(bVar2 >> (*(byte *)(count + 0x20) & 0x1f)) <<
         ((byte)*(undefined4 *)(count + 0x14) & 0x1f) |
         (ushort)(*pbVar1 >> (*(byte *)(count + 0x24) & 0x1f)) <<
         ((byte)*(undefined4 *)(count + 0x18) & 0x1f) |
         (ushort)(*pbVar3 >> (*(byte *)(count + 0x28) & 0x1f)) <<
         ((byte)*(undefined4 *)(count + 0x1c) & 0x1f);
    palette = palette + 1;
  } while (palette < (byte *)0x100);
  return 1;
}

/* ---- 0x0047b810  stdPcx_DecodeRunMasked ---- */
uint __cdecl stdPcx_DecodeRunMasked(byte *palette,int dst,int count,uint flags)

{
  byte *pbVar1;
  byte bVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  pbVar5 = palette;
  palette = (byte *)0x0;
  do {
    bVar2 = *pbVar5;
    pbVar4 = pbVar5 + 1;
    pbVar1 = pbVar5 + 2;
    pbVar5 = pbVar5 + 3;
    if (palette == (byte *)0x0) {
      uVar3 = 0;
    }
    else {
      uVar3 = flags & 0xff;
    }
    *(ushort *)(dst + (int)palette * 2) =
         (ushort)((uVar3 >> ((byte)*(undefined4 *)(count + 0x34) & 0x1f)) <<
                 ((byte)*(undefined4 *)(count + 0x30) & 0x1f)) |
         (ushort)(bVar2 >> (*(byte *)(count + 0x20) & 0x1f)) <<
         ((byte)*(undefined4 *)(count + 0x14) & 0x1f) |
         (ushort)(*pbVar4 >> (*(byte *)(count + 0x24) & 0x1f)) <<
         ((byte)*(undefined4 *)(count + 0x18) & 0x1f) |
         (ushort)(*pbVar1 >> (*(byte *)(count + 0x28) & 0x1f)) <<
         ((byte)*(undefined4 *)(count + 0x1c) & 0x1f);
    palette = palette + 1;
  } while (palette < (byte *)0x100);
  return 1;
}

/* ---- 0x0047ec80  stdPcx_Load ---- */
/* stdLoadImageData loader for '.pcx' (allocation string Stdpcx.c); was named stdLbm_Load. */

undefined4 * __cdecl stdPcx_Load(uint name,int videoMem,int b)

{
  unsigned char _frame[0xe0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint f;
  stdBitmap *bitmap;
  VBuffer **ppVVar2;
  VBuffer *pVVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  void *pvVar7;
  int iVar8;
  byte *pbVar9;
  stdBitmap *psVar10;
  VBufferFormat *pVVar11;
  byte *pbVar12;
  #define VStack_cc (*(VBufferFormat *)(_frame + (0xe0 - 0xcc)))
  #define acStack_80 (*(char (*)[3])(_frame + (0xe0 - 0x80)))
  #define uStack_7d (*(uint *)(_frame + (0xe0 - 0x7d)))
  #define sStack_78 (*(short *)(_frame + (0xe0 - 0x78)))
  #define sStack_76 (*(short *)(_frame + (0xe0 - 0x76)))
  #define sStack_3e (*(short *)(_frame + (0xe0 - 0x3e)))
  
  f = (*g_pStd_HS->pFopen)(name,&DAT_004ddb18);
  if (f == 0) {
    return (undefined4 *)0x0;
  }
  bitmap = (stdBitmap *)
           (*g_pStd_HS->pAlloc)(0x7c,s_C__grimjedi_Libs_Std_General_Std_004e78b8,DAT_004e78b4 + 0xe)
  ;
  if (bitmap != (stdBitmap *)0x0) {
    psVar10 = bitmap;
    for (iVar8 = 0x1f; iVar8 != 0; iVar8 = iVar8 + -1) {
      psVar10->aName[0] = '\0';
      psVar10->aName[1] = '\0';
      psVar10->aName[2] = '\0';
      psVar10->aName[3] = '\0';
      psVar10 = (stdBitmap *)(psVar10->aName + 4);
    }
    (*g_pStd_HS->pFread)(f,acStack_80,0x80);
    if (acStack_80[0] == '\n') {
      bitmap->nType = 0;
      bitmap->dwPalFlags = 2;
      bitmap->nFrames = 1;
      bitmap->nCurFrame = 0;
      (bitmap->colorFormat).nColorMode = 0;
      (bitmap->colorFormat).nBpp = uStack_7d & 0xff;
      ppVVar2 = (VBuffer **)
                (*g_pStd_HS->pAlloc)
                          (4,s_C__grimjedi_Libs_Std_General_Std_004e78b8,DAT_004e78b4 + 0x33);
      bitmap->ppFrames = ppVVar2;
      if (ppVVar2 != (VBuffer **)0x0) {
        pVVar11 = &VStack_cc;
        for (iVar8 = 0x13; iVar8 != 0; iVar8 = iVar8 + -1) {
          pVVar11->nWidth = 0;
          pVVar11 = (VBufferFormat *)&pVVar11->nHeight;
        }
        VStack_cc.colorFormat.nColorMode = 0;
        VStack_cc.colorFormat.nBpp = uStack_7d & 0xff;
        VStack_cc.nWidth = (int)sStack_3e / (int)((uint)VStack_cc.colorFormat.nBpp >> 3);
        VStack_cc.nHeight = sStack_76 + 1;
        pVVar3 = stdDisplay_VBufferNew(&VStack_cc,videoMem,b,0);
        *bitmap->ppFrames = pVVar3;
        if (*bitmap->ppFrames != (VBuffer *)0x0) {
          ((*bitmap->ppFrames)->format).nWidth = sStack_78 + 1;
          stdDisplay_VBufferLock(*bitmap->ppFrames);
          pbVar9 = (*bitmap->ppFrames)->pPixels;
          if (((*bitmap->ppFrames)->format).dwSize != 0) {
            do {
              uVar4 = stdFGetc(f);
              if (((byte)uVar4 & 0xc0) == 0xc0) {
                uVar5 = uVar4 & 0x3f;
                uVar6 = stdFGetc(f);
                bVar1 = (byte)uVar6;
                if (uVar5 != 0) {
                  pbVar12 = pbVar9;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(uint *)pbVar12 = CONCAT22(CONCAT11(bVar1,bVar1),CONCAT11(bVar1,bVar1));
                    pbVar12 = pbVar12 + 4;
                  }
                  pbVar9 = pbVar9 + uVar5;
                  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
                    *pbVar12 = bVar1;
                    pbVar12 = pbVar12 + 1;
                  }
                }
              }
              else {
                *pbVar9 = (byte)uVar4;
                pbVar9 = pbVar9 + 1;
              }
            } while ((uint)((int)pbVar9 - (int)(*bitmap->ppFrames)->pPixels) <
                     ((*bitmap->ppFrames)->format).dwSize);
          }
          stdDisplay_VBufferUnlock(*bitmap->ppFrames);
          pvVar7 = (void *)(*g_pStd_HS->pAlloc)
                                     (0x300,s_C__grimjedi_Libs_Std_General_Std_004e78b8,
                                      DAT_004e78b4 + 0x6c);
          bitmap->pPalette = pvVar7;
          if (pvVar7 != (void *)0x0) {
            stdFGetc(f);
            (*g_pStd_HS->pFread)(f,bitmap->pPalette,0x300);
            (*g_pStd_HS->pFclose)(f);
            return (undefined4 *)bitmap;
          }
        }
      }
    }
  }
  (*g_pStd_HS->pFclose)(f);
  stdBitmap_Free(bitmap);
  return (undefined4 *)0x0;
}
#undef VStack_cc
#undef acStack_80
#undef sStack_3e
#undef sStack_76
#undef sStack_78
#undef uStack_7d


/* ---- 0x0047ef10  stdPcx_Write ---- */
/* Original name stdPcx_Write (the remaster's GrimFandango (Linux): aligned call in stdWriteImage);
   was stdPcx_Save. */

uint __cdecl stdPcx_Write(uint filename,int bitmap)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int *piVar2;
  int iVar3;
  uint f;
  uint uVar4;
  byte bVar5;
  int iVar6;
  undefined3 uVar7;
  undefined3 extraout_var;
  uint uVar8;
  undefined4 *puVar9;
  uint uVar10;
  uint uStack_94;
  uint uStack_8c;
  #define local_80 (*(undefined1 *)(_frame + (0x90 - 0x80)))
  #define local_7f (*(undefined1 *)(_frame + (0x90 - 0x7f)))
  #define local_7e (*(undefined1 *)(_frame + (0x90 - 0x7e)))
  #define local_7d (*(undefined1 *)(_frame + (0x90 - 0x7d)))
  #define local_7c (*(undefined2 *)(_frame + (0x90 - 0x7c)))
  #define local_7a (*(undefined2 *)(_frame + (0x90 - 0x7a)))
  #define local_78 (*(short *)(_frame + (0x90 - 0x78)))
  #define local_76 (*(short *)(_frame + (0x90 - 0x76)))
  #define local_74 (*(undefined2 *)(_frame + (0x90 - 0x74)))
  #define local_72 (*(undefined2 *)(_frame + (0x90 - 0x72)))
  #define local_70 (*(undefined4 (*)[12])(_frame + (0x90 - 0x70)))
  #define local_40 (*(undefined1 *)(_frame + (0x90 - 0x40)))
  #define local_3f (*(undefined1 *)(_frame + (0x90 - 0x3f)))
  #define local_3e (*(undefined2 *)(_frame + (0x90 - 0x3e)))
  #define local_3c (*(undefined2 *)(_frame + (0x90 - 0x3c)))
  #define local_3a (*(undefined4 (*)[14])(_frame + (0x90 - 0x3a)))
  
  local_80 = 10;
  piVar2 = *(int **)(bitmap + 0x78);
  local_7f = 5;
  local_7e = 1;
  local_7d = 8;
  local_7c = 0;
  local_7a = 0;
  local_78 = *(short *)(*piVar2 + 0xc) + -1;
  local_76 = *(short *)(*piVar2 + 0x10) + -1;
  local_74 = *(undefined2 *)(*piVar2 + 0xc);
  local_72 = *(undefined2 *)(*piVar2 + 0x10);
  local_40 = 0;
  local_3f = 1;
  local_3e = *(undefined2 *)(*piVar2 + 0xc);
  local_3c = 0;
  puVar9 = local_70;
  for (iVar6 = 0xc; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  puVar9 = local_3a;
  for (iVar6 = 0xe; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  *(undefined2 *)puVar9 = 0;
  f = (*g_pStd_HS->pFopen)(filename,&DAT_004ddd78);
  if (f == 0) {
    return 0;
  }
  (*g_pStd_HS->pFwrite)(f,&local_80,0x80);
  iVar6 = **(int **)(bitmap + 0x78);
  iVar3 = *(int *)(iVar6 + 0x5c);
  uStack_8c = 0;
  if (*(int *)(iVar6 + 0x10) != 0) {
    do {
      uVar8 = *(uint *)(iVar6 + 0xc);
      iVar6 = uStack_8c * uVar8 + iVar3;
      uVar10 = 0;
      uVar4 = uStack_8c;
      if (uVar8 != 0) {
        do {
          bVar1 = *(byte *)(uVar10 + iVar6);
          uVar7 = (undefined3)(uVar4 >> 8);
          bVar5 = 1;
          uStack_94 = 1;
          if (bVar1 == *(byte *)(uVar10 + 1 + iVar6)) {
            uVar4 = 1;
            do {
              if ((uVar8 <= uVar4 + uVar10) || (0x3e < bVar5)) break;
              bVar5 = bVar5 + 1;
              uStack_94 = (uint)bVar5;
              uVar4 = (uint)bVar5;
            } while (bVar1 == ((undefined1 *)(uVar10 + iVar6))[uVar4]);
          }
          if ((1 < bVar5) || (0xbf < bVar1)) {
            stdFPutc(CONCAT31(uVar7,bVar5) | 0xc0,f);
            uVar7 = extraout_var;
          }
          stdFPutc(CONCAT31(uVar7,*(undefined1 *)(uVar10 + iVar6)),f);
          uVar10 = uVar10 + uStack_94;
          uVar4 = **(uint **)(bitmap + 0x78);
          uVar8 = *(uint *)(uVar4 + 0xc);
        } while (uVar10 < uVar8);
      }
      uStack_8c = uStack_8c + 1;
      iVar6 = **(int **)(bitmap + 0x78);
    } while (uStack_8c < *(uint *)(iVar6 + 0x10));
  }
  stdFPutc(0xc,f);
  (*g_pStd_HS->pFwrite)(f,*(undefined4 *)(bitmap + 0x60),0x300);
  (*g_pStd_HS->pFclose)(f);
  return 1;
}
#undef local_3a
#undef local_3c
#undef local_3e
#undef local_3f
#undef local_40
#undef local_70
#undef local_72
#undef local_74
#undef local_76
#undef local_78
#undef local_7a
#undef local_7c
#undef local_7d
#undef local_7e
#undef local_7f
#undef local_80

