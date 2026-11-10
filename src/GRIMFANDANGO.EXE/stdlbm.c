/* GRIMFANDANGO.EXE :: stdlbm.c
 * functions 0x0047f120 .. 0x0047fc80 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047f120  stdLbm_Load ---- */
/* stdBitmap_LoadFile loader for '.lbm' (IFF PBM: FORM, BMHD, BODY chunks; allocation string
   Stdlbm.c). */

void * stdLbm_Load(char *param_1,int param_2,int param_3)

{
  unsigned char _frame[0xb0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void **ppvVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  undefined1 uVar5;
  int iVar6;
  void *bitmap;
  int iVar7;
  char *pcVar8;
  void *pvVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  undefined4 *puVar14;
  undefined4 uVar15;
  #define iStack_94 (*(int *)(_frame + (0xb0 - 0x94)))
  #define iStack_90 (*(int *)(_frame + (0xb0 - 0x90)))
  #define iStack_8c (*(int *)(_frame + (0xb0 - 0x8c)))
  #define auStack_88 (*(undefined1 (*)[4])(_frame + (0xb0 - 0x88)))
  #define uStack_84 (*(uint *)(_frame + (0xb0 - 0x84)))
  #define auStack_80 (*(undefined1 (*)[4])(_frame + (0xb0 - 0x80)))
  #define iStack_7c (*(int *)(_frame + (0xb0 - 0x7c)))
  #define iStack_78 (*(int *)(_frame + (0xb0 - 0x78)))
  #define uStack_74 (*(ushort *)(_frame + (0xb0 - 0x74)))
  #define uStack_72 (*(ushort *)(_frame + (0xb0 - 0x72)))
  #define uStack_6a (*(uint *)(_frame + (0xb0 - 0x6a)))
  #define auStack_60 (*(undefined1 (*)[4])(_frame + (0xb0 - 0x60)))
  #define uStack_5c (*(undefined4 *)(_frame + (0xb0 - 0x5c)))
  #define auStack_58 (*(undefined1 (*)[4])(_frame + (0xb0 - 0x58)))
  #define uStack_54 (*(undefined4 *)(_frame + (0xb0 - 0x54)))
  #define uStack_4c (*(uint *)(_frame + (0xb0 - 0x4c)))
  #define uStack_48 (*(uint *)(_frame + (0xb0 - 0x48)))
  #define uStack_38 (*(undefined4 *)(_frame + (0xb0 - 0x38)))
  #define uStack_34 (*(undefined4 *)(_frame + (0xb0 - 0x34)))
  
  iVar6 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddb18);
  if (iVar6 == 0) {
    return (void *)0x0;
  }
  bitmap = (void *)(*g_pStd_HS->pAlloc)
                             (0x7c,s_C__grimjedi_Libs_Std_General_Std_004e78ec,DAT_004e78e0 + 0x11);
  if (bitmap != (void *)0x0) {
    (*g_pStd_HS->pFread)(iVar6,auStack_58,0xc);
    iVar7 = strncmp(auStack_58,&DAT_004e78e4,4);
    if (iVar7 == 0) {
      uStack_54 = Std_Swap32(uStack_54);
      (*g_pStd_HS->pFseek)(iVar6,0,0);
      cVar3 = stdFile_ReadByte(iVar6);
      bVar2 = false;
      do {
        iVar7 = (*g_pStd_HS->pFeof)(iVar6);
        if (iVar7 != 0) break;
        if (cVar3 == 'B') {
          cVar3 = stdFile_ReadByte(iVar6);
          if (((cVar3 == 'M') && (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'H')) &&
             (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'D')) {
            ppvVar1 = &g_pStd_HS->pFseek;
            iVar7 = (*g_pStd_HS->pFtell)(iVar6,0);
            (*(code *)*ppvVar1)(iVar6,iVar7 + -4);
            (*g_pStd_HS->pFread)(iVar6,auStack_88,8);
            bVar2 = true;
          }
        }
        else {
          cVar3 = stdFile_ReadByte(iVar6);
        }
      } while (!bVar2);
      if (!bVar2) {
        return (void *)0x0;
      }
      uStack_84 = Std_Swap32(uStack_84);
      (*g_pStd_HS->pFread)(iVar6,&uStack_74,0x14);
      stdLbm_SwapHeader(&uStack_74);
      uVar12 = (int)uStack_84 >> 0x1f;
      if (((uStack_84 ^ uVar12) - uVar12 & 1 ^ uVar12) != uVar12) {
        stdFile_ReadByte(iVar6);
      }
      uVar12 = (int)uStack_84 >> 0x1f;
      if (((uStack_84 ^ uVar12) - uVar12 & 1 ^ uVar12) != uVar12) {
        stdFile_ReadByte(iVar6);
      }
      bVar2 = false;
      do {
        iVar7 = (*g_pStd_HS->pFeof)(iVar6);
        if (iVar7 != 0) break;
        cVar3 = stdFile_ReadByte(iVar6);
        if (((cVar3 == 'B') && (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'O')) &&
           ((cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'D' &&
            (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'Y')))) {
          ppvVar1 = &g_pStd_HS->pFseek;
          iVar7 = (*g_pStd_HS->pFtell)(iVar6,0);
          (*(code *)*ppvVar1)(iVar6,iVar7 + -4);
          (*g_pStd_HS->pFread)(iVar6,auStack_80,8);
          bVar2 = true;
        }
      } while (!bVar2);
      if (!bVar2) {
        return (void *)0x0;
      }
      iStack_7c = Std_Swap32(iStack_7c);
      uVar15 = 0x1f;
      pcVar8 = Str_FileNameFromPath(param_1);
      strncpy(bitmap,pcVar8,uVar15);
      *(undefined1 *)((int)bitmap + 0x1f) = 0;
      *(undefined4 *)((int)bitmap + 0x20) = 0;
      *(undefined4 *)((int)bitmap + 0x24) = 2;
      *(undefined4 *)((int)bitmap + 100) = 1;
      *(undefined4 *)((int)bitmap + 0x68) = 0;
      *(undefined4 *)((int)bitmap + 0x28) = 0;
      *(undefined4 *)((int)bitmap + 0x2c) = 8;
      iVar7 = (*g_pStd_HS->pAlloc)
                        (4,s_C__grimjedi_Libs_Std_General_Std_004e78ec,DAT_004e78e0 + 0x72);
      *(int *)((int)bitmap + 0x78) = iVar7;
      if (iVar7 != 0) {
        if ((uStack_74 & 1) == 0) {
          uStack_4c = (uint)uStack_74;
        }
        else {
          uStack_4c = uStack_74 + 1;
        }
        uStack_48 = (uint)uStack_72;
        uStack_38 = 0;
        uStack_34 = 8;
        pvVar9 = Surface_Create(&uStack_4c,param_2,param_3,0);
        **(undefined4 **)((int)bitmap + 0x78) = pvVar9;
        if ((void *)**(undefined4 **)((int)bitmap + 0x78) != (void *)0x0) {
          Surface_Lock((void *)**(undefined4 **)((int)bitmap + 0x78));
          iVar13 = 0;
          iVar7 = *(int *)(**(int **)((int)bitmap + 0x78) + 0x5c);
          iStack_78 = iVar7;
          if ((uStack_6a & 0xff) == 0) {
            if (0 < iStack_7c) {
              do {
                uVar5 = stdFile_ReadByte(iVar6);
                *(undefined1 *)(iVar13 + iVar7) = uVar5;
                iVar13 = iVar13 + 1;
              } while (iVar13 < iStack_7c);
            }
          }
          else if ((uStack_6a & 0xff) == 1) {
            iStack_8c = 0;
            iStack_90 = 0;
            if (uStack_72 != 0) {
              do {
                iStack_94 = 0;
                do {
                  bVar4 = stdFile_ReadByte(iVar6);
                  uVar12 = (uint)(char)bVar4;
                  if (((bVar4 & 0x80) == 0x80) && (((int)(char)bVar4 | 0x80U) != 0x80)) {
                    uVar12 = 1 - (uVar12 | 0xffffff00);
                    uVar5 = stdFile_ReadByte(iVar6);
                    if (uVar12 != 0) {
                      puVar14 = (undefined4 *)(iVar13 + iVar7);
                      for (uVar11 = uVar12 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
                        *puVar14 = CONCAT22(CONCAT11(uVar5,uVar5),CONCAT11(uVar5,uVar5));
                        puVar14 = puVar14 + 1;
                      }
                      for (uVar11 = uVar12 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
                        *(undefined1 *)puVar14 = uVar5;
                        puVar14 = (undefined4 *)((int)puVar14 + 1);
                      }
                      iVar13 = iStack_90 + uVar12;
                      iStack_94 = iStack_94 + uVar12;
                      iVar7 = iStack_78;
                      iStack_90 = iVar13;
                    }
                  }
                  else if ((uVar12 != 0x80) && (iVar10 = uVar12 + 1, 0 < iVar10)) {
                    iStack_94 = iStack_94 + iVar10;
                    do {
                      uVar5 = stdFile_ReadByte(iVar6);
                      *(undefined1 *)(iVar13 + iVar7) = uVar5;
                      iVar13 = iVar13 + 1;
                      iVar10 = iVar10 + -1;
                      iStack_90 = iVar13;
                    } while (iVar10 != 0);
                  }
                } while (iStack_94 < (int)(uint)uStack_74);
                iStack_8c = iStack_8c + 1;
              } while (iStack_8c < (int)(uint)uStack_72);
            }
          }
          Surface_Unlock((void *)**(undefined4 **)((int)bitmap + 0x78));
          iVar7 = (*g_pStd_HS->pAlloc)
                            (0x300,s_C__grimjedi_Libs_Std_General_Std_004e78ec,DAT_004e78e0 + 0xc2);
          *(int *)((int)bitmap + 0x60) = iVar7;
          if (iVar7 != 0) {
            (*g_pStd_HS->pFseek)(iVar6,0,0);
            bVar2 = false;
            do {
              iVar7 = (*g_pStd_HS->pFeof)(iVar6);
              if (iVar7 != 0) break;
              cVar3 = stdFile_ReadByte(iVar6);
              if ((((cVar3 == 'C') && (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'M')) &&
                  (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'A')) &&
                 (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'P')) {
                ppvVar1 = &g_pStd_HS->pFseek;
                iVar7 = (*g_pStd_HS->pFtell)(iVar6,0);
                (*(code *)*ppvVar1)(iVar6,iVar7 + -4);
                (*g_pStd_HS->pFread)(iVar6,auStack_60,8);
                bVar2 = true;
              }
            } while (!bVar2);
            if (bVar2) {
              uStack_5c = Std_Swap32(uStack_5c);
              (*g_pStd_HS->pFread)(iVar6,*(undefined4 *)((int)bitmap + 0x60),uStack_5c);
              (*g_pStd_HS->pFclose)(iVar6);
              return bitmap;
            }
            return (void *)0x0;
          }
        }
      }
    }
  }
  (*g_pStd_HS->pFclose)(iVar6);
  stdBitmap_Free(bitmap);
  return (void *)0x0;
}
#undef auStack_58
#undef auStack_60
#undef auStack_80
#undef auStack_88
#undef iStack_78
#undef iStack_7c
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
#undef uStack_84


/* ---- 0x0047f720  stdLbm_Write ---- */
undefined4 stdLbm_Write(undefined4 param_1,int param_2)

{
  unsigned char _frame[0x800] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  #define iStack_7ec (*(int *)(_frame + (0x800 - 0x7ec)))
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
  #define auStack_7d0 (*(undefined1 (*)[2000])(_frame + (0x800 - 0x7d0)))
  
  iVar2 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddd78);
  if (iVar2 == 0) {
    return 0;
  }
  (*g_pStd_HS->pFwrite)(iVar2,s_FORMxxxxPBM_BMHD_004e7928,0x10);
  iStack_7ec = Std_Swap32(0x14);
  (*g_pStd_HS->pFwrite)(iVar2,&iStack_7ec,4);
  stdLbm_SwapHeader(&uStack_7e8);
  (*g_pStd_HS->pFwrite)(iVar2,&uStack_7e8,0x14);
  (*g_pStd_HS->pFwrite)(iVar2,&DAT_004e7920,4);
  iStack_7ec = Std_Swap32(0x300);
  (*g_pStd_HS->pFwrite)(iVar2,&iStack_7ec,4);
  (*g_pStd_HS->pFwrite)(iVar2,*(undefined4 *)(param_2 + 0x60),0x300);
  iStack_7d4 = (*g_pStd_HS->pFtell)(iVar2);
  (*g_pStd_HS->pFwrite)(iVar2,s_BODYxxxx_004e7914,8);
  Surface_Lock((void *)**(undefined4 **)(param_2 + 0x78));
  uVar4 = 0;
  iVar3 = **(int **)(param_2 + 0x78);
  iVar5 = *(int *)(iVar3 + 0x5c);
  if (*(int *)(iVar3 + 0x10) != 0) {
    iVar3 = *(int *)(iVar3 + 0xc);
    do {
      stdLbm_PackBits(iVar2,iVar5,iVar3,auStack_7d0);
      iVar3 = *(int *)(**(int **)(param_2 + 0x78) + 0xc);
      iVar5 = iVar5 + iVar3;
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(**(int **)(param_2 + 0x78) + 0x10));
  }
  Surface_Unlock((void *)**(undefined4 **)(param_2 + 0x78));
  iStack_7ec = (*g_pStd_HS->pFtell)(iVar2);
  iVar3 = iStack_7d4;
  iStack_7ec = iStack_7ec + (-8 - iStack_7d4);
  iStack_7ec = Std_Swap32(iStack_7ec);
  (*g_pStd_HS->pFseek)(iVar2,iVar3 + 4,0);
  (*g_pStd_HS->pFwrite)(iVar2,&iStack_7ec,4);
  (*g_pStd_HS->pFseek)(iVar2,0,2);
  iStack_7ec = (*g_pStd_HS->pFtell)(iVar2);
  iStack_7ec = iStack_7ec + -8;
  iStack_7ec = Std_Swap32(iStack_7ec);
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
  (*g_pStd_HS->pFseek)(iVar2,4,0);
  (*g_pStd_HS->pFwrite)(iVar2,&iStack_7ec,4);
  (*g_pStd_HS->pFseek)(iVar2,0x14,0);
  stdLbm_SwapHeader(&uStack_7e8);
  (*g_pStd_HS->pFwrite)(iVar2,&uStack_7e8,0x14);
  (*g_pStd_HS->pFseek)(iVar2,0,2);
  (*g_pStd_HS->pFclose)(iVar2);
  return 1;
}
#undef auStack_7d0
#undef iStack_7d4
#undef iStack_7ec
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


/* ---- 0x0047f9d0  stdLbm_PackBits ---- */
/* ByteRun1 (PackBits) RLE encoder feeding stdLbm_PackByte */

void stdLbm_PackBits(undefined4 param_1,undefined1 *param_2,int param_3,char *param_4)

{
  undefined1 uVar1;
  
  UINT_00815614 = 0;
  DAT_00815620 = 3;
  PTR_0081561c = param_4;
  for (; param_3 != 0; param_3 = param_3 + -1) {
    uVar1 = *param_2;
    param_2 = param_2 + 1;
    stdLbm_PackByte(uVar1);
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
void stdLbm_PackByte(char param_1)

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

void stdLbm_SwapHeader(undefined2 *param_1)

{
  undefined2 uVar1;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  
  uVar1 = Std_Swap16(*param_1);
  *param_1 = uVar1;
  uVar1 = Std_Swap16(CONCAT22(extraout_var,param_1[1]));
  param_1[1] = uVar1;
  uVar1 = Std_Swap16(CONCAT22(extraout_var_01,param_1[2]));
  param_1[2] = uVar1;
  uVar1 = Std_Swap16(param_1[3]);
  param_1[3] = uVar1;
  uVar1 = Std_Swap16(CONCAT22(extraout_var_00,param_1[6]));
  param_1[6] = uVar1;
  uVar1 = Std_Swap16(CONCAT22(extraout_var_02,param_1[8]));
  param_1[8] = uVar1;
  uVar1 = Std_Swap16(param_1[9]);
  param_1[9] = uVar1;
  return;
}
