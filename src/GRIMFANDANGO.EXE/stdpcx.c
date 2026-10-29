/* GRIMFANDANGO.EXE :: stdpcx.c
 * functions 0x0047b710 .. 0x0047f120 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047b710  stdPcx_DecodeRun16 ---- */
/* PCX RLE run decode into 16-bit pixels via a 256-entry lookup */

undefined4 stdPcx_DecodeRun16(byte *param_1,ushort *param_2,int param_3)

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
    param_1 = (byte *)((int)param_1 + -1);
    param_2 = param_2 + 1;
  } while (param_1 != (byte *)0x0);
  return 1;
}

/* ---- 0x0047b780  stdPcx_DecodeRun8 ---- */
undefined4 stdPcx_DecodeRun8(byte *param_1,int param_2,int param_3)

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
    param_1 = (byte *)((int)param_1 + 1);
  } while (param_1 < 0x100);
  return 1;
}

/* ---- 0x0047b810  stdPcx_DecodeRunMasked ---- */
undefined4 stdPcx_DecodeRunMasked(byte *param_1,int param_2,int param_3,uint param_4)

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
    param_1 = (byte *)((int)param_1 + 1);
  } while (param_1 < 0x100);
  return 1;
}

/* ---- 0x0047db00  stdPcx_Load ---- */
/* Stdpcx.c: reads a PCX file into a new bitmap */

void * stdPcx_Load(char *param_1,int param_2,int param_3)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  byte bVar2;
  int iVar3;
  void *bitmap;
  int iVar4;
  char *pcVar5;
  void *pvVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  #define cStack_81 (*(char *)(_frame + (0xa0 - 0x81)))
  #define iStack_80 (*(int *)(_frame + (0xa0 - 0x80)))
  #define iStack_7c (*(int *)(_frame + (0xa0 - 0x7c)))
  #define piStack_78 (*(int **)(_frame + (0xa0 - 0x78)))
  #define iStack_74 (*(int *)(_frame + (0xa0 - 0x74)))
  #define iStack_70 (*(int *)(_frame + (0xa0 - 0x70)))
  #define iStack_6c (*(int *)(_frame + (0xa0 - 0x6c)))
  #define sStack_66 (*(short *)(_frame + (0xa0 - 0x66)))
  #define auStack_64 (*(undefined1 (*)[2])(_frame + (0xa0 - 0x64)))
  #define sStack_62 (*(short *)(_frame + (0xa0 - 0x62)))
  #define sStack_60 (*(short *)(_frame + (0xa0 - 0x60)))
  #define abStack_5e (*(byte (*)[2])(_frame + (0xa0 - 0x5e)))
  #define cStack_5c (*(char *)(_frame + (0xa0 - 0x5c)))
  #define cStack_5b (*(char *)(_frame + (0xa0 - 0x5b)))
  #define cStack_5a (*(char *)(_frame + (0xa0 - 0x5a)))
  #define cStack_59 (*(char *)(_frame + (0xa0 - 0x59)))
  #define cStack_58 (*(char *)(_frame + (0xa0 - 0x58)))
  #define cStack_57 (*(char *)(_frame + (0xa0 - 0x57)))
  #define auStack_56 (*(undefined1 (*)[2])(_frame + (0xa0 - 0x56)))
  #define auStack_54 (*(undefined1 (*)[2])(_frame + (0xa0 - 0x54)))
  #define bStack_52 (*(byte *)(_frame + (0xa0 - 0x52)))
  #define uStack_51 (*(undefined1 *)(_frame + (0xa0 - 0x51)))
  #define auStack_50 (*(undefined1 (*)[4])(_frame + (0xa0 - 0x50)))
  #define iStack_4c (*(int *)(_frame + (0xa0 - 0x4c)))
  #define iStack_48 (*(int *)(_frame + (0xa0 - 0x48)))
  #define uStack_38 (*(undefined4 *)(_frame + (0xa0 - 0x38)))
  #define uStack_34 (*(undefined4 *)(_frame + (0xa0 - 0x34)))
  
  iVar3 = (*g_pSvcMain->pFopen)(param_1,&DAT_004ddb18);
  if (iVar3 == 0) {
    return (void *)0x0;
  }
  iStack_6c = iVar3;
  bitmap = (void *)(*g_pSvcMain->pAlloc)
                             (0x7c,s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x13);
  if (bitmap != (void *)0x0) {
    *(undefined4 *)((int)bitmap + 0x60) = 0;
    *(undefined4 *)((int)bitmap + 0x78) = 0;
    (*g_pSvcMain->pFread)(iVar3,&cStack_5c,3);
    iVar4 = toupper((int)cStack_5c);
    if (((iVar4 == 0x47) && (iVar4 = toupper((int)cStack_5b), iVar4 == 0x49)) &&
       (iVar4 = toupper((int)cStack_5a), iVar4 == 0x46)) {
      (*g_pSvcMain->pFread)(iVar3,&cStack_59,3);
      (*g_pSvcMain->pFread)(iVar3,auStack_56,2);
      (*g_pSvcMain->pFread)(iVar3,auStack_54,2);
      (*g_pSvcMain->pFread)(iVar3,&bStack_52,1);
      (*g_pSvcMain->pFread)(iVar3,&uStack_51,1);
      (*g_pSvcMain->pFread)(iVar3,auStack_50,1);
      if ((bStack_52 & 0x80) != 0) {
        iVar4 = (*g_pSvcMain->pAlloc)
                          (0x300,s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x3b);
        *(int *)((int)bitmap + 0x60) = iVar4;
        if (iVar4 == 0) goto LAB_0047e02f;
        (*g_pSvcMain->pFread)(iVar3,iVar4,(short)(1 << (bStack_52 & 7) + 1) * 3);
      }
      if (((cStack_59 == '8') && (cStack_58 == '9')) &&
         (iVar4 = toupper((int)cStack_57), iVar4 == 0x41)) {
        cVar1 = stdFile_ReadByte(iVar3);
        while (cVar1 == '!') {
          cVar1 = stdFile_ReadByte(iVar3);
          while (cVar1 != '\0') {
            cVar1 = stdFile_ReadByte(iVar3);
          }
          cVar1 = stdFile_ReadByte(iVar3);
        }
      }
      else {
        cVar1 = stdFile_ReadByte(iVar3);
      }
      if (cVar1 == ',') {
        (*g_pSvcMain->pFread)(iVar3,&sStack_66,2);
        (*g_pSvcMain->pFread)(iVar3,auStack_64,2);
        (*g_pSvcMain->pFread)(iVar3,&sStack_62,2);
        (*g_pSvcMain->pFread)(iVar3,&sStack_60,2);
        (*g_pSvcMain->pFread)(iVar3,abStack_5e,1);
        uVar10 = 0x1f;
        pcVar5 = Str_FileNameFromPath(param_1);
        strncpy(bitmap,pcVar5,uVar10);
        *(undefined1 *)((int)bitmap + 0x1f) = 0;
        *(undefined4 *)((int)bitmap + 0x20) = 0;
        *(undefined4 *)((int)bitmap + 0x24) = 2;
        *(undefined4 *)((int)bitmap + 100) = 1;
        *(undefined4 *)((int)bitmap + 0x68) = 0;
        *(undefined4 *)((int)bitmap + 0x28) = 0;
        *(undefined4 *)((int)bitmap + 0x2c) = 8;
        iVar4 = (*g_pSvcMain->pAlloc)
                          (4,s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x73);
        *(int *)((int)bitmap + 0x78) = iVar4;
        if (iVar4 != 0) {
          iStack_4c = (int)sStack_62;
          iStack_48 = (int)sStack_60;
          uStack_38 = 0;
          uStack_34 = 8;
          pvVar6 = Surface_Create(&iStack_4c,param_2,param_3,0);
          **(undefined4 **)((int)bitmap + 0x78) = pvVar6;
          if (**(int **)((int)bitmap + 0x78) != 0) {
            if ((abStack_5e[0] & 0x80) != 0) {
              bVar2 = abStack_5e[0] & 7;
              if (*(int *)((int)bitmap + 0x60) == 0) {
                iVar4 = (*g_pSvcMain->pAlloc)
                                  (0x300,s_C__grimjedi_Libs_Std_General_Std_004e7884,
                                   DAT_004e787c + 0x8a);
                *(int *)((int)bitmap + 0x60) = iVar4;
                if (iVar4 == 0) goto LAB_0047e02f;
              }
              (*g_pSvcMain->pFread)
                        (iVar3,*(undefined4 *)((int)bitmap + 0x60),(short)(1 << bVar2 + 1) * 3);
            }
            iVar4 = (*g_pSvcMain->pAlloc)
                              (*(int *)(**(int **)((int)bitmap + 0x78) + 0xc) + (int)sStack_66,
                               s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x95);
            iStack_7c = iVar4;
            if (iVar4 != 0) {
              (*g_pSvcMain->pFread)(iVar3,&cStack_81,1);
              stdGif_LzwInitDecoder((short)cStack_81);
              iVar9 = 0;
              iStack_74 = (-(uint)((abStack_5e[0] & 2) != 0) & 7) + 1;
              iStack_80 = 0;
              Surface_Lock((void *)**(undefined4 **)((int)bitmap + 0x78));
              iStack_70 = 0;
              iVar7 = **(int **)((int)bitmap + 0x78);
              if (0 < *(int *)(iVar7 + 0x10)) {
                piStack_78 = (int *)&DAT_004e780c;
                do {
                  iVar4 = 0;
                  if (0 < *(int *)(iVar7 + 0xc) + (int)sStack_66) {
                    do {
                      bVar2 = stdGif_LzwDecodeNext(iVar3);
                      *(byte *)(iVar4 + iStack_7c) = bVar2;
                      if (bVar2 == 0xffffffff) {
                        (*g_pSvcMain->pFree)(iStack_7c);
                        goto LAB_0047e02f;
                      }
                      iVar4 = iVar4 + 1;
                    } while (iVar4 < *(int *)(**(int **)((int)bitmap + 0x78) + 0xc) + (int)sStack_66
                            );
                  }
                  iVar4 = **(int **)((int)bitmap + 0x78);
                  if (iVar9 <= *(int *)(iVar4 + 0x10)) {
                    iVar7 = *(int *)(iVar4 + 0xc);
                    iVar8 = 0;
                    if (0 < iVar7) {
                      do {
                        iVar3 = iStack_7c + iVar8;
                        iVar8 = iVar8 + 1;
                        *(undefined1 *)(iVar9 * iVar7 + *(int *)(iVar4 + 0x5c) + -1 + iVar8) =
                             *(undefined1 *)(iVar3 + sStack_66);
                        iVar4 = **(int **)((int)bitmap + 0x78);
                        iVar7 = *(int *)(iVar4 + 0xc);
                        iVar9 = iStack_80;
                        iVar3 = iStack_6c;
                      } while (iVar8 < iVar7);
                    }
                  }
                  iVar9 = iVar9 + iStack_74;
                  iVar7 = **(int **)((int)bitmap + 0x78);
                  if (*(int *)(iVar7 + 0x10) <= iVar9) {
                    iVar9 = piStack_78[1];
                    iStack_74 = piStack_78[2];
                    piStack_78 = piStack_78 + 2;
                  }
                  iStack_70 = iStack_70 + 1;
                  iVar4 = iStack_7c;
                  iStack_80 = iVar9;
                } while (iStack_70 < *(int *)(iVar7 + 0x10));
              }
              Surface_Unlock((void *)**(undefined4 **)((int)bitmap + 0x78));
              (*g_pSvcMain->pFree)(iVar4);
              (*g_pSvcMain->pFread)(iVar3,&cStack_81,1);
              (*g_pSvcMain->pFclose)(iVar3);
              return bitmap;
            }
          }
        }
      }
    }
  }
LAB_0047e02f:
  (*g_pSvcMain->pFclose)(iVar3);
  if (bitmap != (void *)0x0) {
    stdBitmap_Free(bitmap);
  }
  return (void *)0x0;
}
#undef abStack_5e
#undef auStack_50
#undef auStack_54
#undef auStack_56
#undef auStack_64
#undef bStack_52
#undef cStack_57
#undef cStack_58
#undef cStack_59
#undef cStack_5a
#undef cStack_5b
#undef cStack_5c
#undef cStack_81
#undef iStack_48
#undef iStack_4c
#undef iStack_6c
#undef iStack_70
#undef iStack_74
#undef iStack_7c
#undef iStack_80
#undef piStack_78
#undef sStack_60
#undef sStack_62
#undef sStack_66
#undef uStack_34
#undef uStack_38
#undef uStack_51


/* ---- 0x0047ef10  stdPcx_Save ---- */
undefined4 stdPcx_Save(undefined4 param_1,int param_2)

{
  unsigned char _frame[0xb0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
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
  iVar7 = (*g_pSvcMain->pFopen)(param_1,&DAT_004ddd78);
  if (iVar7 == 0) {
    return 0;
  }
  (*g_pSvcMain->pFwrite)(iVar7,&local_80,0x80);
  iVar4 = **(int **)(param_2 + 0x78);
  iVar3 = *(int *)(iVar4 + 0x5c);
  uStack_8c = 0;
  if (*(int *)(iVar4 + 0x10) != 0) {
    do {
      uVar9 = *(uint *)(iVar4 + 0xc);
      iVar4 = uStack_8c * uVar9 + iVar3;
      uVar11 = 0;
      uVar5 = uStack_8c;
      if (uVar9 != 0) {
        do {
          bVar1 = *(byte *)(uVar11 + iVar4);
          uVar8 = (undefined3)(uVar5 >> 8);
          bVar6 = 1;
          uStack_94 = 1;
          if (bVar1 == *(byte *)(uVar11 + 1 + iVar4)) {
            uVar5 = 1;
            do {
              if ((uVar9 <= uVar5 + uVar11) || (0x3e < bVar6)) break;
              bVar6 = bVar6 + 1;
              uStack_94 = (uint)bVar6;
              uVar5 = (uint)bVar6;
            } while (bVar1 == ((undefined1 *)(uVar11 + iVar4))[uVar5]);
          }
          if ((1 < bVar6) || (0xbf < bVar1)) {
            stdFile_WriteByte(CONCAT31(uVar8,bVar6) | 0xc0,iVar7);
            uVar8 = extraout_var;
          }
          stdFile_WriteByte(CONCAT31(uVar8,*(undefined1 *)(uVar11 + iVar4)),iVar7);
          uVar11 = uVar11 + uStack_94;
          uVar5 = **(uint **)(param_2 + 0x78);
          uVar9 = *(uint *)(uVar5 + 0xc);
        } while (uVar11 < uVar9);
      }
      uStack_8c = uStack_8c + 1;
      iVar4 = **(int **)(param_2 + 0x78);
    } while (uStack_8c < *(uint *)(iVar4 + 0x10));
  }
  stdFile_WriteByte(0xc,iVar7);
  (*g_pSvcMain->pFwrite)(iVar7,*(undefined4 *)(param_2 + 0x60),0x300);
  (*g_pSvcMain->pFclose)(iVar7);
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


/* ---- 0x0047f120  FUN_0047f120 ---- */
void * FUN_0047f120(char *param_1,int param_2,int param_3)

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
  
  iVar6 = (*g_pSvcMain->pFopen)(param_1,&DAT_004ddb18);
  if (iVar6 == 0) {
    return (void *)0x0;
  }
  bitmap = (void *)(*g_pSvcMain->pAlloc)
                             (0x7c,s_C__grimjedi_Libs_Std_General_Std_004e78ec,DAT_004e78e0 + 0x11);
  if (bitmap != (void *)0x0) {
    (*g_pSvcMain->pFread)(iVar6,auStack_58,0xc);
    iVar7 = memcmp(auStack_58,&DAT_004e78e4,4);
    if (iVar7 == 0) {
      uStack_54 = Std_Swap32(uStack_54);
      (*g_pSvcMain->pFseek)(iVar6,0,0);
      cVar3 = stdFile_ReadByte(iVar6);
      bVar2 = false;
      do {
        iVar7 = (*g_pSvcMain->pFeof)(iVar6);
        if (iVar7 != 0) break;
        if (cVar3 == 'B') {
          cVar3 = stdFile_ReadByte(iVar6);
          if (((cVar3 == 'M') && (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'H')) &&
             (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'D')) {
            ppvVar1 = &g_pSvcMain->pFseek;
            iVar7 = (*g_pSvcMain->pFtell)(iVar6,0);
            (*(code *)*ppvVar1)(iVar6,iVar7 + -4);
            (*g_pSvcMain->pFread)(iVar6,auStack_88,8);
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
      (*g_pSvcMain->pFread)(iVar6,&uStack_74,0x14);
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
        iVar7 = (*g_pSvcMain->pFeof)(iVar6);
        if (iVar7 != 0) break;
        cVar3 = stdFile_ReadByte(iVar6);
        if (((cVar3 == 'B') && (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'O')) &&
           ((cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'D' &&
            (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'Y')))) {
          ppvVar1 = &g_pSvcMain->pFseek;
          iVar7 = (*g_pSvcMain->pFtell)(iVar6,0);
          (*(code *)*ppvVar1)(iVar6,iVar7 + -4);
          (*g_pSvcMain->pFread)(iVar6,auStack_80,8);
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
      iVar7 = (*g_pSvcMain->pAlloc)
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
          iVar7 = (*g_pSvcMain->pAlloc)
                            (0x300,s_C__grimjedi_Libs_Std_General_Std_004e78ec,DAT_004e78e0 + 0xc2);
          *(int *)((int)bitmap + 0x60) = iVar7;
          if (iVar7 != 0) {
            (*g_pSvcMain->pFseek)(iVar6,0,0);
            bVar2 = false;
            do {
              iVar7 = (*g_pSvcMain->pFeof)(iVar6);
              if (iVar7 != 0) break;
              cVar3 = stdFile_ReadByte(iVar6);
              if ((((cVar3 == 'C') && (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'M')) &&
                  (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'A')) &&
                 (cVar3 = stdFile_ReadByte(iVar6), cVar3 == 'P')) {
                ppvVar1 = &g_pSvcMain->pFseek;
                iVar7 = (*g_pSvcMain->pFtell)(iVar6,0);
                (*(code *)*ppvVar1)(iVar6,iVar7 + -4);
                (*g_pSvcMain->pFread)(iVar6,auStack_60,8);
                bVar2 = true;
              }
            } while (!bVar2);
            if (bVar2) {
              uStack_5c = Std_Swap32(uStack_5c);
              (*g_pSvcMain->pFread)(iVar6,*(undefined4 *)((int)bitmap + 0x60),uStack_5c);
              (*g_pSvcMain->pFclose)(iVar6);
              return bitmap;
            }
            return (void *)0x0;
          }
        }
      }
    }
  }
  (*g_pSvcMain->pFclose)(iVar6);
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

