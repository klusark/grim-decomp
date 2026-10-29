/* GRIMFANDANGO.EXE :: stdlbm.c
 * functions 0x0047ec80 .. 0x0047fc80 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047ec80  stdLbm_Load ---- */
/* Stdlbm.c: IFF ILBM/PBM reader (FORM/BMHD/CMAP/BODY) */

undefined4 * stdLbm_Load(undefined4 param_1,int param_2,int param_3)

{
  unsigned char _frame[0xe0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined4 *bitmap;
  void *pvVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  byte *pbVar8;
  undefined4 *puVar9;
  int *piVar10;
  byte *pbVar11;
  #define aiStack_cc (*(int (*)[5])(_frame + (0xe0 - 0xcc)))
  #define uStack_b8 (*(undefined4 *)(_frame + (0xe0 - 0xb8)))
  #define uStack_b4 (*(uint *)(_frame + (0xe0 - 0xb4)))
  #define acStack_80 (*(char (*)[3])(_frame + (0xe0 - 0x80)))
  #define uStack_7d (*(uint *)(_frame + (0xe0 - 0x7d)))
  #define sStack_78 (*(short *)(_frame + (0xe0 - 0x78)))
  #define sStack_76 (*(short *)(_frame + (0xe0 - 0x76)))
  #define sStack_3e (*(short *)(_frame + (0xe0 - 0x3e)))
  
  iVar3 = (*g_pSvcMain->pFopen)(param_1,&DAT_004ddb18);
  if (iVar3 == 0) {
    return (undefined4 *)0x0;
  }
  bitmap = (undefined4 *)
           (*g_pSvcMain->pAlloc)
                     (0x7c,s_C__grimjedi_Libs_Std_General_Std_004e78b8,DAT_004e78b4 + 0xe);
  if (bitmap != (undefined4 *)0x0) {
    puVar9 = bitmap;
    for (iVar6 = 0x1f; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
    }
    (*g_pSvcMain->pFread)(iVar3,acStack_80,0x80);
    if (acStack_80[0] == '\n') {
      bitmap[8] = 0;
      bitmap[9] = 2;
      bitmap[0x19] = 1;
      bitmap[0x1a] = 0;
      bitmap[10] = 0;
      bitmap[0xb] = uStack_7d & 0xff;
      iVar6 = (*g_pSvcMain->pAlloc)
                        (4,s_C__grimjedi_Libs_Std_General_Std_004e78b8,DAT_004e78b4 + 0x33);
      bitmap[0x1e] = iVar6;
      if (iVar6 != 0) {
        piVar10 = aiStack_cc;
        for (iVar6 = 0x13; iVar6 != 0; iVar6 = iVar6 + -1) {
          *piVar10 = 0;
          piVar10 = piVar10 + 1;
        }
        uStack_b8 = 0;
        uStack_b4 = uStack_7d & 0xff;
        aiStack_cc[0] = (int)sStack_3e / (int)(uStack_b4 >> 3);
        aiStack_cc[1] = sStack_76 + 1;
        pvVar4 = Surface_Create(aiStack_cc,param_2,param_3,0);
        *(void **)bitmap[0x1e] = pvVar4;
        if (*(int *)bitmap[0x1e] != 0) {
          *(int *)(*(int *)bitmap[0x1e] + 0xc) = sStack_78 + 1;
          Surface_Lock(*(void **)bitmap[0x1e]);
          pbVar8 = *(byte **)(*(int *)bitmap[0x1e] + 0x5c);
          if (*(int *)(*(int *)bitmap[0x1e] + 0x14) != 0) {
            do {
              bVar1 = stdFile_ReadByte(iVar3);
              if ((bVar1 & 0xc0) == 0xc0) {
                uVar5 = bVar1 & 0x3f;
                bVar2 = stdFile_ReadByte(iVar3);
                if ((bVar1 & 0x3f) != 0) {
                  pbVar11 = pbVar8;
                  for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                    *(uint *)pbVar11 = CONCAT22(CONCAT11(bVar2,bVar2),CONCAT11(bVar2,bVar2));
                    pbVar11 = pbVar11 + 4;
                  }
                  pbVar8 = pbVar8 + uVar5;
                  for (uVar5 = bVar1 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pbVar11 = bVar2;
                    pbVar11 = pbVar11 + 1;
                  }
                }
              }
              else {
                *pbVar8 = bVar1;
                pbVar8 = pbVar8 + 1;
              }
            } while ((uint)((int)pbVar8 - *(int *)(*(int *)bitmap[0x1e] + 0x5c)) <
                     *(uint *)(*(int *)bitmap[0x1e] + 0x14));
          }
          Surface_Unlock(*(void **)bitmap[0x1e]);
          iVar6 = (*g_pSvcMain->pAlloc)
                            (0x300,s_C__grimjedi_Libs_Std_General_Std_004e78b8,DAT_004e78b4 + 0x6c);
          bitmap[0x18] = iVar6;
          if (iVar6 != 0) {
            stdFile_ReadByte(iVar3);
            (*g_pSvcMain->pFread)(iVar3,bitmap[0x18],0x300);
            (*g_pSvcMain->pFclose)(iVar3);
            return bitmap;
          }
        }
      }
    }
  }
  (*g_pSvcMain->pFclose)(iVar3);
  stdBitmap_Free(bitmap);
  return (undefined4 *)0x0;
}
#undef acStack_80
#undef aiStack_cc
#undef sStack_3e
#undef sStack_76
#undef sStack_78
#undef uStack_7d
#undef uStack_b4
#undef uStack_b8


/* ---- 0x0047f720  stdLbm_Save ---- */
undefined4 stdLbm_Save(undefined4 param_1,int param_2)

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
  
  iVar2 = (*g_pSvcMain->pFopen)(param_1,&DAT_004ddd78);
  if (iVar2 == 0) {
    return 0;
  }
  (*g_pSvcMain->pFwrite)(iVar2,s_FORMxxxxPBM_BMHD_004e7928,0x10);
  iStack_7ec = Std_Swap32(0x14);
  (*g_pSvcMain->pFwrite)(iVar2,&iStack_7ec,4);
  stdLbm_SwapHeader(&uStack_7e8);
  (*g_pSvcMain->pFwrite)(iVar2,&uStack_7e8,0x14);
  (*g_pSvcMain->pFwrite)(iVar2,&DAT_004e7920,4);
  iStack_7ec = Std_Swap32(0x300);
  (*g_pSvcMain->pFwrite)(iVar2,&iStack_7ec,4);
  (*g_pSvcMain->pFwrite)(iVar2,*(undefined4 *)(param_2 + 0x60),0x300);
  iStack_7d4 = (*g_pSvcMain->pFtell)(iVar2);
  (*g_pSvcMain->pFwrite)(iVar2,s_BODYxxxx_004e7914,8);
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
  iStack_7ec = (*g_pSvcMain->pFtell)(iVar2);
  iVar3 = iStack_7d4;
  iStack_7ec = iStack_7ec + (-8 - iStack_7d4);
  iStack_7ec = Std_Swap32(iStack_7ec);
  (*g_pSvcMain->pFseek)(iVar2,iVar3 + 4,0);
  (*g_pSvcMain->pFwrite)(iVar2,&iStack_7ec,4);
  (*g_pSvcMain->pFseek)(iVar2,0,2);
  iStack_7ec = (*g_pSvcMain->pFtell)(iVar2);
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
  (*g_pSvcMain->pFseek)(iVar2,4,0);
  (*g_pSvcMain->pFwrite)(iVar2,&iStack_7ec,4);
  (*g_pSvcMain->pFseek)(iVar2,0x14,0);
  stdLbm_SwapHeader(&uStack_7e8);
  (*g_pSvcMain->pFwrite)(iVar2,&uStack_7e8,0x14);
  (*g_pSvcMain->pFseek)(iVar2,0,2);
  (*g_pSvcMain->pFclose)(iVar2);
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
  (*g_pSvcMain->pFwrite)(param_1,param_4,UINT_00815614);
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
