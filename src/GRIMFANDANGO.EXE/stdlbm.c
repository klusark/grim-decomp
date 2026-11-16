/* GRIMFANDANGO.EXE :: stdlbm.c
 * functions 0x0047f120 .. 0x0047fc80 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047f120  stdLbm_Load ---- */
/* stdLoadImageData loader for '.lbm' (IFF PBM: FORM, BMHD, BODY chunks; allocation string
   Stdlbm.c). */

stdBitmap * __cdecl stdLbm_Load(char *path,int videoMem,int b)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void **ppvVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  undefined1 uVar5;
  uint f;
  stdBitmap *bitmap;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  VBuffer **ppVVar9;
  VBuffer *pVVar10;
  int iVar11;
  void *pvVar12;
  uint uVar13;
  undefined4 *puVar14;
  int iStack_94;
  int iStack_90;
  int iStack_8c;
  #define auStack_88 (*(undefined1 (*)[4])(_frame + (0xa0 - 0x88)))
  #define uStack_84 (*(uint *)(_frame + (0xa0 - 0x84)))
  #define auStack_80 (*(undefined1 (*)[4])(_frame + (0xa0 - 0x80)))
  #define uStack_7c (*(uint *)(_frame + (0xa0 - 0x7c)))
  #define pvStack_78 (*(void **)(_frame + (0xa0 - 0x78)))
  #define uStack_74 (*(ushort *)(_frame + (0xa0 - 0x74)))
  #define uStack_72 (*(ushort *)(_frame + (0xa0 - 0x72)))
  #define uStack_6a (*(uint *)(_frame + (0xa0 - 0x6a)))
  #define auStack_60 (*(undefined1 (*)[4])(_frame + (0xa0 - 0x60)))
  #define uStack_5c (*(uint *)(_frame + (0xa0 - 0x5c)))
  #define acStack_58 (*(char (*)[4])(_frame + (0xa0 - 0x58)))
  #define uStack_54 (*(uint *)(_frame + (0xa0 - 0x54)))
  #define VStack_4c (*(VBufferFormat *)(_frame + (0xa0 - 0x4c)))
  
  f = (*g_pStd_HS->pFopen)(path,&DAT_004ddb18);
  if (f == 0) {
    return (stdBitmap *)0x0;
  }
  bitmap = (stdBitmap *)
           (*g_pStd_HS->pAlloc)
                     (0x7c,s_C__grimjedi_Libs_Std_General_Std_004e78ec,DAT_004e78e0 + 0x11);
  if (bitmap != (stdBitmap *)0x0) {
    (*g_pStd_HS->pFread)(f,acStack_58,0xc);
    uVar6 = strncmp(acStack_58,&DAT_004e78e4,4);
    if (uVar6 == 0) {
      uStack_54 = Std_Swap32(uStack_54);
      (*g_pStd_HS->pFseek)(f,0,0);
      uVar6 = stdFGetc(f);
      bVar2 = false;
      cVar3 = (char)uVar6;
      do {
        iVar7 = (*g_pStd_HS->pFeof)(f);
        if (iVar7 != 0) break;
        if (cVar3 == 'B') {
          uVar6 = stdFGetc(f);
          cVar3 = (char)uVar6;
          if (cVar3 == 'M') {
            uVar6 = stdFGetc(f);
            cVar3 = (char)uVar6;
            if (cVar3 == 'H') {
              uVar6 = stdFGetc(f);
              cVar3 = (char)uVar6;
              if (cVar3 == 'D') {
                ppvVar1 = &g_pStd_HS->pFseek;
                iVar7 = (*g_pStd_HS->pFtell)(f,0);
                (*(code *)*ppvVar1)(f,iVar7 + -4);
                (*g_pStd_HS->pFread)(f,auStack_88,8);
                bVar2 = true;
              }
            }
          }
        }
        else {
          uVar6 = stdFGetc(f);
          cVar3 = (char)uVar6;
        }
      } while (!bVar2);
      if (!bVar2) {
        return (stdBitmap *)0x0;
      }
      uStack_84 = Std_Swap32(uStack_84);
      (*g_pStd_HS->pFread)(f,&uStack_74,0x14);
      stdLbm_SwapHeader(&uStack_74);
      uVar6 = (int)uStack_84 >> 0x1f;
      if (((uStack_84 ^ uVar6) - uVar6 & 1 ^ uVar6) != uVar6) {
        stdFGetc(f);
      }
      uVar6 = (int)uStack_84 >> 0x1f;
      if (((uStack_84 ^ uVar6) - uVar6 & 1 ^ uVar6) != uVar6) {
        stdFGetc(f);
      }
      bVar2 = false;
      do {
        iVar7 = (*g_pStd_HS->pFeof)(f);
        if (iVar7 != 0) break;
        uVar6 = stdFGetc(f);
        if (((((char)uVar6 == 'B') && (uVar6 = stdFGetc(f), (char)uVar6 == 'O')) &&
            (uVar6 = stdFGetc(f), (char)uVar6 == 'D')) && (uVar6 = stdFGetc(f), (char)uVar6 == 'Y'))
        {
          ppvVar1 = &g_pStd_HS->pFseek;
          iVar7 = (*g_pStd_HS->pFtell)(f,0);
          (*(code *)*ppvVar1)(f,iVar7 + -4);
          (*g_pStd_HS->pFread)(f,auStack_80,8);
          bVar2 = true;
        }
      } while (!bVar2);
      if (!bVar2) {
        return (stdBitmap *)0x0;
      }
      uStack_7c = Std_Swap32(uStack_7c);
      uVar6 = 0x1f;
      puVar8 = (uint *)stdFileFromPath(path);
      strncpy((uint *)bitmap,puVar8,uVar6);
      bitmap->aName[0x1f] = '\0';
      bitmap->nType = 0;
      bitmap->dwPalFlags = 2;
      bitmap->nFrames = 1;
      bitmap->nCurFrame = 0;
      (bitmap->colorFormat).nColorMode = 0;
      (bitmap->colorFormat).nBpp = 8;
      ppVVar9 = (VBuffer **)
                (*g_pStd_HS->pAlloc)
                          (4,s_C__grimjedi_Libs_Std_General_Std_004e78ec,DAT_004e78e0 + 0x72);
      bitmap->ppFrames = ppVVar9;
      if (ppVVar9 != (VBuffer **)0x0) {
        if ((uStack_74 & 1) == 0) {
          VStack_4c.nWidth = (int)uStack_74;
        }
        else {
          VStack_4c.nWidth = uStack_74 + 1;
        }
        VStack_4c.nHeight = (int)uStack_72;
        VStack_4c.colorFormat.nColorMode = 0;
        VStack_4c.colorFormat.nBpp = 8;
        pVVar10 = stdDisplay_VBufferNew(&VStack_4c,videoMem,b,0);
        *bitmap->ppFrames = pVVar10;
        if (*bitmap->ppFrames != (VBuffer *)0x0) {
          stdDisplay_VBufferLock(*bitmap->ppFrames);
          iVar7 = 0;
          pvVar12 = (*bitmap->ppFrames)->pPixels;
          pvStack_78 = pvVar12;
          if ((uStack_6a & 0xff) == 0) {
            if (0 < (int)uStack_7c) {
              do {
                uVar6 = stdFGetc(f);
                *(char *)(iVar7 + (int)pvVar12) = (char)uVar6;
                iVar7 = iVar7 + 1;
              } while (iVar7 < (int)uStack_7c);
            }
          }
          else if ((uStack_6a & 0xff) == 1) {
            iStack_8c = 0;
            iStack_90 = 0;
            if (uStack_72 != 0) {
              do {
                iStack_94 = 0;
                do {
                  uVar6 = stdFGetc(f);
                  bVar4 = (byte)uVar6;
                  uVar6 = (uint)(char)bVar4;
                  if (((bVar4 & 0x80) == 0x80) && (((int)(char)bVar4 | 0x80U) != 0x80)) {
                    uVar13 = 1 - (uVar6 | 0xffffff00);
                    uVar6 = stdFGetc(f);
                    uVar5 = (undefined1)uVar6;
                    if (uVar13 != 0) {
                      puVar14 = (undefined4 *)(iVar7 + (int)pvVar12);
                      for (uVar6 = uVar13 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                        *puVar14 = CONCAT22(CONCAT11(uVar5,uVar5),CONCAT11(uVar5,uVar5));
                        puVar14 = puVar14 + 1;
                      }
                      for (uVar6 = uVar13 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
                        *(undefined1 *)puVar14 = uVar5;
                        puVar14 = (undefined4 *)((int)puVar14 + 1);
                      }
                      iVar7 = iStack_90 + uVar13;
                      iStack_94 = iStack_94 + uVar13;
                      pvVar12 = pvStack_78;
                      iStack_90 = iVar7;
                    }
                  }
                  else if ((uVar6 != 0x80) && (iVar11 = uVar6 + 1, 0 < iVar11)) {
                    iStack_94 = iStack_94 + iVar11;
                    do {
                      uVar6 = stdFGetc(f);
                      *(char *)(iVar7 + (int)pvVar12) = (char)uVar6;
                      iVar7 = iVar7 + 1;
                      iVar11 = iVar11 + -1;
                      iStack_90 = iVar7;
                    } while (iVar11 != 0);
                  }
                } while (iStack_94 < (int)(uint)uStack_74);
                iStack_8c = iStack_8c + 1;
              } while (iStack_8c < (int)(uint)uStack_72);
            }
          }
          stdDisplay_VBufferUnlock(*bitmap->ppFrames);
          pvVar12 = (void *)(*g_pStd_HS->pAlloc)
                                      (0x300,s_C__grimjedi_Libs_Std_General_Std_004e78ec,
                                       DAT_004e78e0 + 0xc2);
          bitmap->pPalette = pvVar12;
          if (pvVar12 != (void *)0x0) {
            (*g_pStd_HS->pFseek)(f,0,0);
            bVar2 = false;
            do {
              iVar7 = (*g_pStd_HS->pFeof)(f);
              if (iVar7 != 0) break;
              uVar6 = stdFGetc(f);
              if ((((char)uVar6 == 'C') && (uVar6 = stdFGetc(f), (char)uVar6 == 'M')) &&
                 ((uVar6 = stdFGetc(f), (char)uVar6 == 'A' &&
                  (uVar6 = stdFGetc(f), (char)uVar6 == 'P')))) {
                ppvVar1 = &g_pStd_HS->pFseek;
                iVar7 = (*g_pStd_HS->pFtell)(f,0);
                (*(code *)*ppvVar1)(f,iVar7 + -4);
                (*g_pStd_HS->pFread)(f,auStack_60,8);
                bVar2 = true;
              }
            } while (!bVar2);
            if (bVar2) {
              uStack_5c = Std_Swap32(uStack_5c);
              (*g_pStd_HS->pFread)(f,bitmap->pPalette,uStack_5c);
              (*g_pStd_HS->pFclose)(f);
              return bitmap;
            }
            return (stdBitmap *)0x0;
          }
        }
      }
    }
  }
  (*g_pStd_HS->pFclose)(f);
  stdBitmap_Free(bitmap);
  return (stdBitmap *)0x0;
}
#undef VStack_4c
#undef acStack_58
#undef auStack_60
#undef auStack_80
#undef auStack_88
#undef pvStack_78
#undef uStack_54
#undef uStack_5c
#undef uStack_6a
#undef uStack_72
#undef uStack_74
#undef uStack_7c
#undef uStack_84


/* ---- 0x0047f720  stdLbm_Write ---- */
uint __cdecl stdLbm_Write(uint filename,int bitmap)

{
  unsigned char _frame[0x800] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  uint f;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined1 *src;
  #define uStack_7ec (*(uint *)(_frame + (0x800 - 0x7ec)))
  #define uStack_7e8 (*(undefined2 *)(_frame + (0x800 - 0x7e8)))
  #define uStack_7e6 (*(undefined2 *)(_frame + (0x800 - 0x7e6)))
  #define uStack_7e4 (*(undefined2 *)(_frame + (0x800 - 0x7e4)))
  #define uStack_7e2 (*(undefined2 *)(_frame + (0x800 - 0x7e2)))
  #define uStack_7e0 (*(undefined1 *)(_frame + (0x800 - 0x7e0)))
  #define uStack_7df (*(undefined1 *)(_frame + (0x800 - 0x7df)))
  #define uStack_7de (*(undefined1 *)(_frame + (0x800 - 0x7de)))
  #define uStack_7dc (*(undefined2 *)(_frame + (0x800 - 0x7dc)))
  #define uStack_7da (*(undefined1 *)(_frame + (0x800 - 0x7da)))
  #define uStack_7d9 (*(undefined1 *)(_frame + (0x800 - 0x7d9)))
  #define uStack_7d8 (*(undefined2 *)(_frame + (0x800 - 0x7d8)))
  #define uStack_7d6 (*(undefined2 *)(_frame + (0x800 - 0x7d6)))
  #define iStack_7d4 (*(int *)(_frame + (0x800 - 0x7d4)))
  #define acStack_7d0 (*(char (*)[2000])(_frame + (0x800 - 0x7d0)))
  
  f = (*g_pStd_HS->pFopen)(filename,&DAT_004ddd78);
  if (f == 0) {
    return 0;
  }
  (*g_pStd_HS->pFwrite)(f,s_FORMxxxxPBM_BMHD_004e7928,0x10);
  uStack_7ec = Std_Swap32(0x14);
  (*g_pStd_HS->pFwrite)(f,&uStack_7ec,4);
  stdLbm_SwapHeader(&uStack_7e8);
  (*g_pStd_HS->pFwrite)(f,&uStack_7e8,0x14);
  (*g_pStd_HS->pFwrite)(f,&DAT_004e7920,4);
  uStack_7ec = Std_Swap32(0x300);
  (*g_pStd_HS->pFwrite)(f,&uStack_7ec,4);
  (*g_pStd_HS->pFwrite)(f,*(undefined4 *)(bitmap + 0x60),0x300);
  iStack_7d4 = (*g_pStd_HS->pFtell)(f);
  (*g_pStd_HS->pFwrite)(f,s_BODYxxxx_004e7914,8);
  stdDisplay_VBufferLock((VBuffer *)**(undefined4 **)(bitmap + 0x78));
  uVar4 = 0;
  iVar3 = **(int **)(bitmap + 0x78);
  src = *(undefined1 **)(iVar3 + 0x5c);
  if (*(int *)(iVar3 + 0x10) != 0) {
    iVar3 = *(int *)(iVar3 + 0xc);
    do {
      stdLbm_PackBits(f,src,iVar3,acStack_7d0);
      iVar3 = *(int *)(**(int **)(bitmap + 0x78) + 0xc);
      src = src + iVar3;
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(**(int **)(bitmap + 0x78) + 0x10));
  }
  stdDisplay_VBufferUnlock((VBuffer *)**(undefined4 **)(bitmap + 0x78));
  iVar2 = (*g_pStd_HS->pFtell)(f);
  iVar3 = iStack_7d4;
  uStack_7ec = iVar2 + (-8 - iStack_7d4);
  uStack_7ec = Std_Swap32(uStack_7ec);
  (*g_pStd_HS->pFseek)(f,iVar3 + 4,0);
  (*g_pStd_HS->pFwrite)(f,&uStack_7ec,4);
  (*g_pStd_HS->pFseek)(f,0,2);
  iVar3 = (*g_pStd_HS->pFtell)(f);
  uStack_7ec = iVar3 - 8;
  uStack_7ec = Std_Swap32(uStack_7ec);
  piVar1 = *(int **)(bitmap + 0x78);
  uStack_7e8 = *(undefined2 *)(*piVar1 + 0xc);
  uStack_7e6 = *(undefined2 *)(*piVar1 + 0x10);
  uStack_7e4 = 0;
  uStack_7e2 = 0;
  uStack_7e0 = 8;
  uStack_7df = 0;
  uStack_7de = 1;
  uStack_7dc = 0;
  uStack_7da = 6;
  uStack_7d9 = 5;
  uStack_7d8 = *(undefined2 *)(*piVar1 + 0xc);
  uStack_7d6 = *(undefined2 *)(*piVar1 + 0x10);
  (*g_pStd_HS->pFseek)(f,4,0);
  (*g_pStd_HS->pFwrite)(f,&uStack_7ec,4);
  (*g_pStd_HS->pFseek)(f,0x14,0);
  stdLbm_SwapHeader(&uStack_7e8);
  (*g_pStd_HS->pFwrite)(f,&uStack_7e8,0x14);
  (*g_pStd_HS->pFseek)(f,0,2);
  (*g_pStd_HS->pFclose)(f);
  return 1;
}
#undef acStack_7d0
#undef iStack_7d4
#undef uStack_7d6
#undef uStack_7d8
#undef uStack_7d9
#undef uStack_7da
#undef uStack_7dc
#undef uStack_7de
#undef uStack_7df
#undef uStack_7e0
#undef uStack_7e2
#undef uStack_7e4
#undef uStack_7e6
#undef uStack_7e8
#undef uStack_7ec


/* ---- 0x0047f9d0  stdLbm_PackBits ---- */
/* ByteRun1 (PackBits) RLE encoder feeding stdLbm_PackByte */

void __cdecl stdLbm_PackBits(uint f,undefined1 *src,int count,char *buf)

{
  char c;
  
  UINT_00815614 = 0;
  DAT_00815620 = 3;
  PTR_0081561c = buf;
  for (; count != 0; count = count + -1) {
    c = *src;
    src = src + 1;
    stdLbm_PackByte(c);
  }
  if (DAT_00815620 == 2) {
    *PTR_0081561c = '\0';
    PTR_0081561c = PTR_0081561c + 1;
    *PTR_0081561c = DAT_00815610;
    UINT_00815614 = UINT_00815614 + 2;
  }
  (*g_pStd_HS->pFwrite)(f,buf,UINT_00815614);
  return;
}

/* ---- 0x0047fa70  stdLbm_PackByte ---- */
void __cdecl stdLbm_PackByte(char c)

{
  char *pcVar1;
  
  switch(DAT_00815620) {
  case 0:
    if (c == DAT_00815610) {
      DAT_00815624 = DAT_00815624 + 1;
    }
    else {
      DAT_00815624 = 0;
    }
    if (2 < DAT_00815624) {
      *(char *)UINT_00815618 = *(char *)UINT_00815618 + -2;
      UINT_00815618 = (uint)(PTR_0081561c + -2);
      PTR_0081561c = PTR_0081561c + -1;
      *(char *)UINT_00815618 = -2;
      DAT_00815620 = 1;
      *PTR_0081561c = c;
      DAT_00815610 = c;
      PTR_0081561c = PTR_0081561c + 1;
      return;
    }
    *(char *)UINT_00815618 = *(char *)UINT_00815618 + '\x01';
    *PTR_0081561c = c;
    PTR_0081561c = PTR_0081561c + 1;
    if (*(char *)UINT_00815618 == '\x7f') {
      DAT_00815620 = 3;
    }
    DAT_00815610 = c;
    UINT_00815614 = UINT_00815614 + 1;
    return;
  case 1:
    break;
  case 2:
    UINT_00815618 = (uint)PTR_0081561c;
    if (c != DAT_00815610) {
      pcVar1 = PTR_0081561c + 1;
      *PTR_0081561c = '\x01';
      PTR_0081561c = pcVar1;
      DAT_00815620 = 0;
      *PTR_0081561c = DAT_00815610;
      PTR_0081561c = PTR_0081561c + 1;
      *PTR_0081561c = c;
      PTR_0081561c = PTR_0081561c + 1;
      UINT_00815614 = UINT_00815614 + 3;
      DAT_00815624 = 0;
      DAT_00815610 = c;
      return;
    }
    pcVar1 = PTR_0081561c + 1;
    *PTR_0081561c = -1;
    PTR_0081561c = pcVar1;
    DAT_00815620 = 1;
    *PTR_0081561c = c;
    PTR_0081561c = PTR_0081561c + 1;
    UINT_00815614 = UINT_00815614 + 2;
    DAT_00815610 = c;
    return;
  case 3:
    DAT_00815610 = c;
    DAT_00815620 = 2;
    return;
  default:
    DAT_00815610 = c;
    return;
  }
  if (c != DAT_00815610) {
    DAT_00815610 = c;
    DAT_00815620 = 2;
    return;
  }
  *(char *)UINT_00815618 = *(char *)UINT_00815618 + -1;
  if (*(char *)UINT_00815618 == -0x7f) {
    DAT_00815620 = 3;
    DAT_00815610 = c;
    return;
  }
  DAT_00815610 = c;
  return;
}

/* ---- 0x0047fc80  stdLbm_SwapHeader ---- */
/* Byte-swaps the big-endian BMHD fields */

void __cdecl stdLbm_SwapHeader(undefined2 *header)

{
  undefined4 in_EAX;
  uint uVar1;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  
  uVar1 = Std_Swap16(CONCAT22((short)((uint)in_EAX >> 0x10),*header));
  *header = (short)uVar1;
  uVar1 = Std_Swap16(CONCAT22(extraout_var,header[1]));
  header[1] = (short)uVar1;
  uVar1 = Std_Swap16(CONCAT22(extraout_var_01,header[2]));
  header[2] = (short)uVar1;
  uVar1 = Std_Swap16(CONCAT22((short)(uVar1 >> 0x10),header[3]));
  header[3] = (short)uVar1;
  uVar1 = Std_Swap16(CONCAT22(extraout_var_00,header[6]));
  header[6] = (short)uVar1;
  uVar1 = Std_Swap16(CONCAT22(extraout_var_02,header[8]));
  header[8] = (short)uVar1;
  uVar1 = Std_Swap16(CONCAT22((short)(uVar1 >> 0x10),header[9]));
  header[9] = (short)uVar1;
  return;
}
