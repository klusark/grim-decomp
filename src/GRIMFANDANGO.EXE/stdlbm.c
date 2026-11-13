/* GRIMFANDANGO.EXE :: stdlbm.c
 * functions 0x0047f120 .. 0x0047fc80 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047f120  stdLbm_Load ---- */
/* stdLoadImageData loader for '.lbm' (IFF PBM: FORM, BMHD, BODY chunks; allocation string
   Stdlbm.c). */

void * __cdecl stdLbm_Load(char *param_1,int param_2,int param_3)

{
  unsigned char _frame[0xb0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void **ppvVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  undefined1 uVar5;
  uint uVar6;
  uint *bitmap;
  uint uVar7;
  int iVar8;
  uint *puVar9;
  void *pvVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  undefined4 *puVar14;
  #define iStack_94 (*(int *)(_frame + (0xb0 - 0x94)))
  #define iStack_90 (*(int *)(_frame + (0xb0 - 0x90)))
  #define iStack_8c (*(int *)(_frame + (0xb0 - 0x8c)))
  #define auStack_88 (*(undefined1 (*)[4])(_frame + (0xb0 - 0x88)))
  #define uStack_84 (*(uint *)(_frame + (0xb0 - 0x84)))
  #define auStack_80 (*(undefined1 (*)[4])(_frame + (0xb0 - 0x80)))
  #define uStack_7c (*(uint *)(_frame + (0xb0 - 0x7c)))
  #define iStack_78 (*(int *)(_frame + (0xb0 - 0x78)))
  #define uStack_74 (*(ushort *)(_frame + (0xb0 - 0x74)))
  #define uStack_72 (*(ushort *)(_frame + (0xb0 - 0x72)))
  #define uStack_6a (*(uint *)(_frame + (0xb0 - 0x6a)))
  #define auStack_60 (*(undefined1 (*)[4])(_frame + (0xb0 - 0x60)))
  #define uStack_5c (*(uint *)(_frame + (0xb0 - 0x5c)))
  #define acStack_58 (*(char (*)[4])(_frame + (0xb0 - 0x58)))
  #define uStack_54 (*(uint *)(_frame + (0xb0 - 0x54)))
  #define uStack_4c (*(uint *)(_frame + (0xb0 - 0x4c)))
  #define uStack_48 (*(uint *)(_frame + (0xb0 - 0x48)))
  #define uStack_38 (*(undefined4 *)(_frame + (0xb0 - 0x38)))
  #define uStack_34 (*(undefined4 *)(_frame + (0xb0 - 0x34)))
  
  uVar6 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddb18);
  if (uVar6 == 0) {
    return (void *)0x0;
  }
  bitmap = (uint *)(*g_pStd_HS->pAlloc)
                             (0x7c,s_C__grimjedi_Libs_Std_General_Std_004e78ec,DAT_004e78e0 + 0x11);
  if (bitmap != (uint *)0x0) {
    (*g_pStd_HS->pFread)(uVar6,acStack_58,0xc);
    uVar7 = strncmp(acStack_58,&DAT_004e78e4,4);
    if (uVar7 == 0) {
      uStack_54 = Std_Swap32(uStack_54);
      (*g_pStd_HS->pFseek)(uVar6,0,0);
      uVar7 = stdFGetc(uVar6);
      bVar2 = false;
      cVar3 = (char)uVar7;
      do {
        iVar8 = (*g_pStd_HS->pFeof)(uVar6);
        if (iVar8 != 0) break;
        if (cVar3 == 'B') {
          uVar7 = stdFGetc(uVar6);
          cVar3 = (char)uVar7;
          if (cVar3 == 'M') {
            uVar7 = stdFGetc(uVar6);
            cVar3 = (char)uVar7;
            if (cVar3 == 'H') {
              uVar7 = stdFGetc(uVar6);
              cVar3 = (char)uVar7;
              if (cVar3 == 'D') {
                ppvVar1 = &g_pStd_HS->pFseek;
                iVar8 = (*g_pStd_HS->pFtell)(uVar6,0);
                (*(code *)*ppvVar1)(uVar6,iVar8 + -4);
                (*g_pStd_HS->pFread)(uVar6,auStack_88,8);
                bVar2 = true;
              }
            }
          }
        }
        else {
          uVar7 = stdFGetc(uVar6);
          cVar3 = (char)uVar7;
        }
      } while (!bVar2);
      if (!bVar2) {
        return (void *)0x0;
      }
      uStack_84 = Std_Swap32(uStack_84);
      (*g_pStd_HS->pFread)(uVar6,&uStack_74,0x14);
      stdLbm_SwapHeader(&uStack_74);
      uVar7 = (int)uStack_84 >> 0x1f;
      if (((uStack_84 ^ uVar7) - uVar7 & 1 ^ uVar7) != uVar7) {
        stdFGetc(uVar6);
      }
      uVar7 = (int)uStack_84 >> 0x1f;
      if (((uStack_84 ^ uVar7) - uVar7 & 1 ^ uVar7) != uVar7) {
        stdFGetc(uVar6);
      }
      bVar2 = false;
      do {
        iVar8 = (*g_pStd_HS->pFeof)(uVar6);
        if (iVar8 != 0) break;
        uVar7 = stdFGetc(uVar6);
        if (((((char)uVar7 == 'B') && (uVar7 = stdFGetc(uVar6), (char)uVar7 == 'O')) &&
            (uVar7 = stdFGetc(uVar6), (char)uVar7 == 'D')) &&
           (uVar7 = stdFGetc(uVar6), (char)uVar7 == 'Y')) {
          ppvVar1 = &g_pStd_HS->pFseek;
          iVar8 = (*g_pStd_HS->pFtell)(uVar6,0);
          (*(code *)*ppvVar1)(uVar6,iVar8 + -4);
          (*g_pStd_HS->pFread)(uVar6,auStack_80,8);
          bVar2 = true;
        }
      } while (!bVar2);
      if (!bVar2) {
        return (void *)0x0;
      }
      uStack_7c = Std_Swap32(uStack_7c);
      uVar7 = 0x1f;
      puVar9 = (uint *)stdFileFromPath(param_1);
      strncpy(bitmap,puVar9,uVar7);
      *(undefined1 *)((int)bitmap + 0x1f) = 0;
      bitmap[8] = 0;
      bitmap[9] = 2;
      bitmap[0x19] = 1;
      bitmap[0x1a] = 0;
      bitmap[10] = 0;
      bitmap[0xb] = 8;
      uVar7 = (*g_pStd_HS->pAlloc)
                        (4,s_C__grimjedi_Libs_Std_General_Std_004e78ec,DAT_004e78e0 + 0x72);
      bitmap[0x1e] = uVar7;
      if (uVar7 != 0) {
        if ((uStack_74 & 1) == 0) {
          uStack_4c = (uint)uStack_74;
        }
        else {
          uStack_4c = uStack_74 + 1;
        }
        uStack_48 = (uint)uStack_72;
        uStack_38 = 0;
        uStack_34 = 8;
        pvVar10 = stdDisplay_VBufferNew(&uStack_4c,param_2,param_3,0);
        *(void **)bitmap[0x1e] = pvVar10;
        if (*(void **)bitmap[0x1e] != (void *)0x0) {
          stdDisplay_VBufferLock(*(void **)bitmap[0x1e]);
          iVar13 = 0;
          iVar8 = *(int *)(*(int *)bitmap[0x1e] + 0x5c);
          iStack_78 = iVar8;
          if ((uStack_6a & 0xff) == 0) {
            if (0 < (int)uStack_7c) {
              do {
                uVar7 = stdFGetc(uVar6);
                *(char *)(iVar13 + iVar8) = (char)uVar7;
                iVar13 = iVar13 + 1;
              } while (iVar13 < (int)uStack_7c);
            }
          }
          else if ((uStack_6a & 0xff) == 1) {
            iStack_8c = 0;
            iStack_90 = 0;
            if (uStack_72 != 0) {
              do {
                iStack_94 = 0;
                do {
                  uVar7 = stdFGetc(uVar6);
                  bVar4 = (byte)uVar7;
                  uVar7 = (uint)(char)bVar4;
                  if (((bVar4 & 0x80) == 0x80) && (((int)(char)bVar4 | 0x80U) != 0x80)) {
                    uVar12 = 1 - (uVar7 | 0xffffff00);
                    uVar7 = stdFGetc(uVar6);
                    uVar5 = (undefined1)uVar7;
                    if (uVar12 != 0) {
                      puVar14 = (undefined4 *)(iVar13 + iVar8);
                      for (uVar7 = uVar12 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                        *puVar14 = CONCAT22(CONCAT11(uVar5,uVar5),CONCAT11(uVar5,uVar5));
                        puVar14 = puVar14 + 1;
                      }
                      for (uVar7 = uVar12 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                        *(undefined1 *)puVar14 = uVar5;
                        puVar14 = (undefined4 *)((int)puVar14 + 1);
                      }
                      iVar13 = iStack_90 + uVar12;
                      iStack_94 = iStack_94 + uVar12;
                      iVar8 = iStack_78;
                      iStack_90 = iVar13;
                    }
                  }
                  else if ((uVar7 != 0x80) && (iVar11 = uVar7 + 1, 0 < iVar11)) {
                    iStack_94 = iStack_94 + iVar11;
                    do {
                      uVar7 = stdFGetc(uVar6);
                      *(char *)(iVar13 + iVar8) = (char)uVar7;
                      iVar13 = iVar13 + 1;
                      iVar11 = iVar11 + -1;
                      iStack_90 = iVar13;
                    } while (iVar11 != 0);
                  }
                } while (iStack_94 < (int)(uint)uStack_74);
                iStack_8c = iStack_8c + 1;
              } while (iStack_8c < (int)(uint)uStack_72);
            }
          }
          stdDisplay_VBufferUnlock(*(void **)bitmap[0x1e]);
          uVar7 = (*g_pStd_HS->pAlloc)
                            (0x300,s_C__grimjedi_Libs_Std_General_Std_004e78ec,DAT_004e78e0 + 0xc2);
          bitmap[0x18] = uVar7;
          if (uVar7 != 0) {
            (*g_pStd_HS->pFseek)(uVar6,0,0);
            bVar2 = false;
            do {
              iVar8 = (*g_pStd_HS->pFeof)(uVar6);
              if (iVar8 != 0) break;
              uVar7 = stdFGetc(uVar6);
              if ((((char)uVar7 == 'C') && (uVar7 = stdFGetc(uVar6), (char)uVar7 == 'M')) &&
                 ((uVar7 = stdFGetc(uVar6), (char)uVar7 == 'A' &&
                  (uVar7 = stdFGetc(uVar6), (char)uVar7 == 'P')))) {
                ppvVar1 = &g_pStd_HS->pFseek;
                iVar8 = (*g_pStd_HS->pFtell)(uVar6,0);
                (*(code *)*ppvVar1)(uVar6,iVar8 + -4);
                (*g_pStd_HS->pFread)(uVar6,auStack_60,8);
                bVar2 = true;
              }
            } while (!bVar2);
            if (bVar2) {
              uStack_5c = Std_Swap32(uStack_5c);
              (*g_pStd_HS->pFread)(uVar6,bitmap[0x18],uStack_5c);
              (*g_pStd_HS->pFclose)(uVar6);
              return bitmap;
            }
            return (void *)0x0;
          }
        }
      }
    }
  }
  (*g_pStd_HS->pFclose)(uVar6);
  stdBitmap_Free(bitmap);
  return (void *)0x0;
}
#undef acStack_58
#undef auStack_60
#undef auStack_80
#undef auStack_88
#undef iStack_78
#undef iStack_8c
#undef iStack_90
#undef iStack_94
#undef uStack_34
#undef uStack_38
#undef uStack_48
#undef uStack_4c
#undef uStack_54
#undef uStack_5c
#undef uStack_6a
#undef uStack_72
#undef uStack_74
#undef uStack_7c
#undef uStack_84


/* ---- 0x0047f720  stdLbm_Write ---- */
uint __cdecl stdLbm_Write(uint param_1,int param_2)

{
  unsigned char _frame[0x800] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
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
  
  uVar2 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddd78);
  if (uVar2 == 0) {
    return 0;
  }
  (*g_pStd_HS->pFwrite)(uVar2,s_FORMxxxxPBM_BMHD_004e7928,0x10);
  uStack_7ec = Std_Swap32(0x14);
  (*g_pStd_HS->pFwrite)(uVar2,&uStack_7ec,4);
  stdLbm_SwapHeader(&uStack_7e8);
  (*g_pStd_HS->pFwrite)(uVar2,&uStack_7e8,0x14);
  (*g_pStd_HS->pFwrite)(uVar2,&DAT_004e7920,4);
  uStack_7ec = Std_Swap32(0x300);
  (*g_pStd_HS->pFwrite)(uVar2,&uStack_7ec,4);
  (*g_pStd_HS->pFwrite)(uVar2,*(undefined4 *)(param_2 + 0x60),0x300);
  iStack_7d4 = (*g_pStd_HS->pFtell)(uVar2);
  (*g_pStd_HS->pFwrite)(uVar2,s_BODYxxxx_004e7914,8);
  stdDisplay_VBufferLock((void *)**(undefined4 **)(param_2 + 0x78));
  uVar5 = 0;
  iVar4 = **(int **)(param_2 + 0x78);
  puVar6 = *(undefined1 **)(iVar4 + 0x5c);
  if (*(int *)(iVar4 + 0x10) != 0) {
    iVar4 = *(int *)(iVar4 + 0xc);
    do {
      stdLbm_PackBits(uVar2,puVar6,iVar4,acStack_7d0);
      iVar4 = *(int *)(**(int **)(param_2 + 0x78) + 0xc);
      puVar6 = puVar6 + iVar4;
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(**(int **)(param_2 + 0x78) + 0x10));
  }
  stdDisplay_VBufferUnlock((void *)**(undefined4 **)(param_2 + 0x78));
  iVar3 = (*g_pStd_HS->pFtell)(uVar2);
  iVar4 = iStack_7d4;
  uStack_7ec = iVar3 + (-8 - iStack_7d4);
  uStack_7ec = Std_Swap32(uStack_7ec);
  (*g_pStd_HS->pFseek)(uVar2,iVar4 + 4,0);
  (*g_pStd_HS->pFwrite)(uVar2,&uStack_7ec,4);
  (*g_pStd_HS->pFseek)(uVar2,0,2);
  iVar4 = (*g_pStd_HS->pFtell)(uVar2);
  uStack_7ec = iVar4 - 8;
  uStack_7ec = Std_Swap32(uStack_7ec);
  piVar1 = *(int **)(param_2 + 0x78);
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
  (*g_pStd_HS->pFseek)(uVar2,4,0);
  (*g_pStd_HS->pFwrite)(uVar2,&uStack_7ec,4);
  (*g_pStd_HS->pFseek)(uVar2,0x14,0);
  stdLbm_SwapHeader(&uStack_7e8);
  (*g_pStd_HS->pFwrite)(uVar2,&uStack_7e8,0x14);
  (*g_pStd_HS->pFseek)(uVar2,0,2);
  (*g_pStd_HS->pFclose)(uVar2);
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

void __cdecl stdLbm_PackBits(uint param_1,undefined1 *param_2,int param_3,char *param_4)

{
  char cVar1;
  
  UINT_00815614 = 0;
  DAT_00815620 = 3;
  PTR_0081561c = param_4;
  for (; param_3 != 0; param_3 = param_3 + -1) {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
    stdLbm_PackByte(cVar1);
  }
  if (DAT_00815620 == 2) {
    *PTR_0081561c = '\0';
    PTR_0081561c = PTR_0081561c + 1;
    *PTR_0081561c = DAT_00815610;
    UINT_00815614 = UINT_00815614 + 2;
  }
  (*g_pStd_HS->pFwrite)(param_1,param_4,UINT_00815614);
  return;
}

/* ---- 0x0047fa70  stdLbm_PackByte ---- */
void __cdecl stdLbm_PackByte(char param_1)

{
  char *pcVar1;
  
  switch(DAT_00815620) {
  case 0:
    if (param_1 == DAT_00815610) {
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
      *PTR_0081561c = param_1;
      DAT_00815610 = param_1;
      PTR_0081561c = PTR_0081561c + 1;
      return;
    }
    *(char *)UINT_00815618 = *(char *)UINT_00815618 + '\x01';
    *PTR_0081561c = param_1;
    PTR_0081561c = PTR_0081561c + 1;
    if (*(char *)UINT_00815618 == '\x7f') {
      DAT_00815620 = 3;
    }
    DAT_00815610 = param_1;
    UINT_00815614 = UINT_00815614 + 1;
    return;
  case 1:
    break;
  case 2:
    UINT_00815618 = (uint)PTR_0081561c;
    if (param_1 != DAT_00815610) {
      pcVar1 = PTR_0081561c + 1;
      *PTR_0081561c = '\x01';
      PTR_0081561c = pcVar1;
      DAT_00815620 = 0;
      *PTR_0081561c = DAT_00815610;
      PTR_0081561c = PTR_0081561c + 1;
      *PTR_0081561c = param_1;
      PTR_0081561c = PTR_0081561c + 1;
      UINT_00815614 = UINT_00815614 + 3;
      DAT_00815624 = 0;
      DAT_00815610 = param_1;
      return;
    }
    pcVar1 = PTR_0081561c + 1;
    *PTR_0081561c = -1;
    PTR_0081561c = pcVar1;
    DAT_00815620 = 1;
    *PTR_0081561c = param_1;
    PTR_0081561c = PTR_0081561c + 1;
    UINT_00815614 = UINT_00815614 + 2;
    DAT_00815610 = param_1;
    return;
  case 3:
    DAT_00815610 = param_1;
    DAT_00815620 = 2;
    return;
  default:
    DAT_00815610 = param_1;
    return;
  }
  if (param_1 != DAT_00815610) {
    DAT_00815610 = param_1;
    DAT_00815620 = 2;
    return;
  }
  *(char *)UINT_00815618 = *(char *)UINT_00815618 + -1;
  if (*(char *)UINT_00815618 == -0x7f) {
    DAT_00815620 = 3;
    DAT_00815610 = param_1;
    return;
  }
  DAT_00815610 = param_1;
  return;
}

/* ---- 0x0047fc80  stdLbm_SwapHeader ---- */
/* Byte-swaps the big-endian BMHD fields */

void __cdecl stdLbm_SwapHeader(undefined2 *param_1)

{
  undefined4 in_EAX;
  uint uVar1;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  
  uVar1 = Std_Swap16(CONCAT22((short)((uint)in_EAX >> 0x10),*param_1));
  *param_1 = (short)uVar1;
  uVar1 = Std_Swap16(CONCAT22(extraout_var,param_1[1]));
  param_1[1] = (short)uVar1;
  uVar1 = Std_Swap16(CONCAT22(extraout_var_01,param_1[2]));
  param_1[2] = (short)uVar1;
  uVar1 = Std_Swap16(CONCAT22((short)(uVar1 >> 0x10),param_1[3]));
  param_1[3] = (short)uVar1;
  uVar1 = Std_Swap16(CONCAT22(extraout_var_00,param_1[6]));
  param_1[6] = (short)uVar1;
  uVar1 = Std_Swap16(CONCAT22(extraout_var_02,param_1[8]));
  param_1[8] = (short)uVar1;
  uVar1 = Std_Swap16(CONCAT22((short)(uVar1 >> 0x10),param_1[9]));
  param_1[9] = (short)uVar1;
  return;
}
