/* GRIMFANDANGO.EXE :: stdpcx.c
 * functions 0x0047b710 .. 0x0047ef10 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047b710  stdPcx_DecodeRun16 ---- */
/* PCX RLE run decode into 16-bit pixels via a 256-entry lookup */

uint __cdecl stdPcx_DecodeRun16(byte *param_1,ushort *param_2,int param_3)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar4 = param_1;
  param_1 = (byte *)0x100;
  do {
    bVar1 = *pbVar4;
    pbVar2 = pbVar4 + 1;
    pbVar3 = pbVar4 + 2;
    pbVar4 = pbVar4 + 3;
    *param_2 = (ushort)(bVar1 >> (*(byte *)(param_3 + 0x20) & 0x1f)) <<
               ((byte)*(undefined4 *)(param_3 + 0x14) & 0x1f) |
               (ushort)(*pbVar2 >> (*(byte *)(param_3 + 0x24) & 0x1f)) <<
               ((byte)*(undefined4 *)(param_3 + 0x18) & 0x1f) |
               (ushort)(*pbVar3 >> (*(byte *)(param_3 + 0x28) & 0x1f)) <<
               ((byte)*(undefined4 *)(param_3 + 0x1c) & 0x1f);
    param_1 = param_1 + -1;
    param_2 = param_2 + 1;
  } while (param_1 != (byte *)0x0);
  return 1;
}

/* ---- 0x0047b780  stdPcx_DecodeRun8 ---- */
uint __cdecl stdPcx_DecodeRun8(byte *param_1,int param_2,int param_3)

{
  byte *pbVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar4 = param_1;
  param_1 = (byte *)0x0;
  do {
    bVar2 = *pbVar4;
    pbVar1 = pbVar4 + 1;
    pbVar3 = pbVar4 + 2;
    pbVar4 = pbVar4 + 3;
    *(ushort *)(param_2 + (int)param_1 * 2) =
         (ushort)(((-(uint)(param_1 != (byte *)0x0) & 0xff) >>
                  ((byte)*(undefined4 *)(param_3 + 0x34) & 0x1f)) <<
                 ((byte)*(undefined4 *)(param_3 + 0x30) & 0x1f)) |
         (ushort)(bVar2 >> (*(byte *)(param_3 + 0x20) & 0x1f)) <<
         ((byte)*(undefined4 *)(param_3 + 0x14) & 0x1f) |
         (ushort)(*pbVar1 >> (*(byte *)(param_3 + 0x24) & 0x1f)) <<
         ((byte)*(undefined4 *)(param_3 + 0x18) & 0x1f) |
         (ushort)(*pbVar3 >> (*(byte *)(param_3 + 0x28) & 0x1f)) <<
         ((byte)*(undefined4 *)(param_3 + 0x1c) & 0x1f);
    param_1 = param_1 + 1;
  } while (param_1 < (byte *)0x100);
  return 1;
}

/* ---- 0x0047b810  stdPcx_DecodeRunMasked ---- */
uint __cdecl stdPcx_DecodeRunMasked(byte *param_1,int param_2,int param_3,uint param_4)

{
  byte *pbVar1;
  byte bVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  pbVar5 = param_1;
  param_1 = (byte *)0x0;
  do {
    bVar2 = *pbVar5;
    pbVar4 = pbVar5 + 1;
    pbVar1 = pbVar5 + 2;
    pbVar5 = pbVar5 + 3;
    if (param_1 == (byte *)0x0) {
      uVar3 = 0;
    }
    else {
      uVar3 = param_4 & 0xff;
    }
    *(ushort *)(param_2 + (int)param_1 * 2) =
         (ushort)((uVar3 >> ((byte)*(undefined4 *)(param_3 + 0x34) & 0x1f)) <<
                 ((byte)*(undefined4 *)(param_3 + 0x30) & 0x1f)) |
         (ushort)(bVar2 >> (*(byte *)(param_3 + 0x20) & 0x1f)) <<
         ((byte)*(undefined4 *)(param_3 + 0x14) & 0x1f) |
         (ushort)(*pbVar4 >> (*(byte *)(param_3 + 0x24) & 0x1f)) <<
         ((byte)*(undefined4 *)(param_3 + 0x18) & 0x1f) |
         (ushort)(*pbVar1 >> (*(byte *)(param_3 + 0x28) & 0x1f)) <<
         ((byte)*(undefined4 *)(param_3 + 0x1c) & 0x1f);
    param_1 = param_1 + 1;
  } while (param_1 < (byte *)0x100);
  return 1;
}

/* ---- 0x0047ec80  stdPcx_Load ---- */
/* stdLoadImageData loader for '.pcx' (allocation string Stdpcx.c); was named stdLbm_Load. */

undefined4 * __cdecl stdPcx_Load(uint param_1,int param_2,int param_3)

{
  unsigned char _frame[0xe0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint uVar2;
  stdBitmap *bitmap;
  VBuffer **ppVVar3;
  VBuffer *pVVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  void *pvVar8;
  int iVar9;
  byte *pbVar10;
  stdBitmap *psVar11;
  VBufferFormat *pVVar12;
  byte *pbVar13;
  #define VStack_cc (*(VBufferFormat *)(_frame + (0xe0 - 0xcc)))
  #define acStack_80 (*(char (*)[3])(_frame + (0xe0 - 0x80)))
  #define uStack_7d (*(uint *)(_frame + (0xe0 - 0x7d)))
  #define sStack_78 (*(short *)(_frame + (0xe0 - 0x78)))
  #define sStack_76 (*(short *)(_frame + (0xe0 - 0x76)))
  #define sStack_3e (*(short *)(_frame + (0xe0 - 0x3e)))
  
  uVar2 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddb18);
  if (uVar2 == 0) {
    return (undefined4 *)0x0;
  }
  bitmap = (stdBitmap *)
           (*g_pStd_HS->pAlloc)(0x7c,s_C__grimjedi_Libs_Std_General_Std_004e78b8,DAT_004e78b4 + 0xe)
  ;
  if (bitmap != (stdBitmap *)0x0) {
    psVar11 = bitmap;
    for (iVar9 = 0x1f; iVar9 != 0; iVar9 = iVar9 + -1) {
      psVar11->aName[0] = '\0';
      psVar11->aName[1] = '\0';
      psVar11->aName[2] = '\0';
      psVar11->aName[3] = '\0';
      psVar11 = (stdBitmap *)(psVar11->aName + 4);
    }
    (*g_pStd_HS->pFread)(uVar2,acStack_80,0x80);
    if (acStack_80[0] == '\n') {
      bitmap->nType = 0;
      bitmap->dwPalFlags = 2;
      bitmap->nFrames = 1;
      bitmap->nCurFrame = 0;
      (bitmap->colorFormat).nColorMode = 0;
      (bitmap->colorFormat).nBpp = uStack_7d & 0xff;
      ppVVar3 = (VBuffer **)
                (*g_pStd_HS->pAlloc)
                          (4,s_C__grimjedi_Libs_Std_General_Std_004e78b8,DAT_004e78b4 + 0x33);
      bitmap->ppFrames = ppVVar3;
      if (ppVVar3 != (VBuffer **)0x0) {
        pVVar12 = &VStack_cc;
        for (iVar9 = 0x13; iVar9 != 0; iVar9 = iVar9 + -1) {
          pVVar12->nWidth = 0;
          pVVar12 = (VBufferFormat *)&pVVar12->nHeight;
        }
        VStack_cc.colorFormat.nColorMode = 0;
        VStack_cc.colorFormat.nBpp = uStack_7d & 0xff;
        VStack_cc.nWidth = (int)sStack_3e / (int)((uint)VStack_cc.colorFormat.nBpp >> 3);
        VStack_cc.nHeight = sStack_76 + 1;
        pVVar4 = stdDisplay_VBufferNew(&VStack_cc,param_2,param_3,0);
        *bitmap->ppFrames = pVVar4;
        if (*bitmap->ppFrames != (VBuffer *)0x0) {
          ((*bitmap->ppFrames)->format).nWidth = sStack_78 + 1;
          stdDisplay_VBufferLock(*bitmap->ppFrames);
          pbVar10 = (*bitmap->ppFrames)->pPixels;
          if (((*bitmap->ppFrames)->format).dwSize != 0) {
            do {
              uVar5 = stdFGetc(uVar2);
              if (((byte)uVar5 & 0xc0) == 0xc0) {
                uVar6 = uVar5 & 0x3f;
                uVar7 = stdFGetc(uVar2);
                bVar1 = (byte)uVar7;
                if (uVar6 != 0) {
                  pbVar13 = pbVar10;
                  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                    *(uint *)pbVar13 = CONCAT22(CONCAT11(bVar1,bVar1),CONCAT11(bVar1,bVar1));
                    pbVar13 = pbVar13 + 4;
                  }
                  pbVar10 = pbVar10 + uVar6;
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pbVar13 = bVar1;
                    pbVar13 = pbVar13 + 1;
                  }
                }
              }
              else {
                *pbVar10 = (byte)uVar5;
                pbVar10 = pbVar10 + 1;
              }
            } while ((uint)((int)pbVar10 - (int)(*bitmap->ppFrames)->pPixels) <
                     ((*bitmap->ppFrames)->format).dwSize);
          }
          stdDisplay_VBufferUnlock(*bitmap->ppFrames);
          pvVar8 = (void *)(*g_pStd_HS->pAlloc)
                                     (0x300,s_C__grimjedi_Libs_Std_General_Std_004e78b8,
                                      DAT_004e78b4 + 0x6c);
          bitmap->pPalette = pvVar8;
          if (pvVar8 != (void *)0x0) {
            stdFGetc(uVar2);
            (*g_pStd_HS->pFread)(uVar2,bitmap->pPalette,0x300);
            (*g_pStd_HS->pFclose)(uVar2);
            return (undefined4 *)bitmap;
          }
        }
      }
    }
  }
  (*g_pStd_HS->pFclose)(uVar2);
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

uint __cdecl stdPcx_Write(uint param_1,int param_2)

{
  unsigned char _frame[0xb0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  byte bVar6;
  int iVar7;
  undefined3 uVar8;
  undefined3 extraout_var;
  uint uVar9;
  undefined4 *puVar10;
  uint uVar11;
  #define uStack_94 (*(uint *)(_frame + (0xb0 - 0x94)))
  #define uStack_8c (*(uint *)(_frame + (0xb0 - 0x8c)))
  #define local_80 (*(undefined1 *)(_frame + (0xb0 - 0x80)))
  #define local_7f (*(undefined1 *)(_frame + (0xb0 - 0x7f)))
  #define local_7e (*(undefined1 *)(_frame + (0xb0 - 0x7e)))
  #define local_7d (*(undefined1 *)(_frame + (0xb0 - 0x7d)))
  #define local_7c (*(undefined2 *)(_frame + (0xb0 - 0x7c)))
  #define local_7a (*(undefined2 *)(_frame + (0xb0 - 0x7a)))
  #define local_78 (*(short *)(_frame + (0xb0 - 0x78)))
  #define local_76 (*(short *)(_frame + (0xb0 - 0x76)))
  #define local_74 (*(undefined2 *)(_frame + (0xb0 - 0x74)))
  #define local_72 (*(undefined2 *)(_frame + (0xb0 - 0x72)))
  #define local_70 (*(undefined4 (*)[12])(_frame + (0xb0 - 0x70)))
  #define local_40 (*(undefined1 *)(_frame + (0xb0 - 0x40)))
  #define local_3f (*(undefined1 *)(_frame + (0xb0 - 0x3f)))
  #define local_3e (*(undefined2 *)(_frame + (0xb0 - 0x3e)))
  #define local_3c (*(undefined2 *)(_frame + (0xb0 - 0x3c)))
  #define local_3a (*(undefined4 (*)[14])(_frame + (0xb0 - 0x3a)))
  
  local_80 = 10;
  piVar2 = *(int **)(param_2 + 0x78);
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
  puVar10 = local_70;
  for (iVar7 = 0xc; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  puVar10 = local_3a;
  for (iVar7 = 0xe; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  *(undefined2 *)puVar10 = 0;
  uVar4 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddd78);
  if (uVar4 == 0) {
    return 0;
  }
  (*g_pStd_HS->pFwrite)(uVar4,&local_80,0x80);
  iVar7 = **(int **)(param_2 + 0x78);
  iVar3 = *(int *)(iVar7 + 0x5c);
  uStack_8c = 0;
  if (*(int *)(iVar7 + 0x10) != 0) {
    do {
      uVar9 = *(uint *)(iVar7 + 0xc);
      iVar7 = uStack_8c * uVar9 + iVar3;
      uVar11 = 0;
      uVar5 = uStack_8c;
      if (uVar9 != 0) {
        do {
          bVar1 = *(byte *)(uVar11 + iVar7);
          uVar8 = (undefined3)(uVar5 >> 8);
          bVar6 = 1;
          uStack_94 = 1;
          if (bVar1 == *(byte *)(uVar11 + 1 + iVar7)) {
            uVar5 = 1;
            do {
              if ((uVar9 <= uVar5 + uVar11) || (0x3e < bVar6)) break;
              bVar6 = bVar6 + 1;
              uStack_94 = (uint)bVar6;
              uVar5 = (uint)bVar6;
            } while (bVar1 == ((undefined1 *)(uVar11 + iVar7))[uVar5]);
          }
          if ((1 < bVar6) || (0xbf < bVar1)) {
            stdFPutc(CONCAT31(uVar8,bVar6) | 0xc0,uVar4);
            uVar8 = extraout_var;
          }
          stdFPutc(CONCAT31(uVar8,*(undefined1 *)(uVar11 + iVar7)),uVar4);
          uVar11 = uVar11 + uStack_94;
          uVar5 = **(uint **)(param_2 + 0x78);
          uVar9 = *(uint *)(uVar5 + 0xc);
        } while (uVar11 < uVar9);
      }
      uStack_8c = uStack_8c + 1;
      iVar7 = **(int **)(param_2 + 0x78);
    } while (uStack_8c < *(uint *)(iVar7 + 0x10));
  }
  stdFPutc(0xc,uVar4);
  (*g_pStd_HS->pFwrite)(uVar4,*(undefined4 *)(param_2 + 0x60),0x300);
  (*g_pStd_HS->pFclose)(uVar4);
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
#undef uStack_8c
#undef uStack_94

