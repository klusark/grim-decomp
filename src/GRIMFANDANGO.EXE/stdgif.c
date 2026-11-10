/* GRIMFANDANGO.EXE :: stdgif.c
 * functions 0x0047db00 .. 0x0047ec40 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047db00  stdGif_Load ---- */
/* stdBitmap_LoadFile loader for '.gif' (LZW through stdGif_LzwInitDecoder/DecodeNext, allocation
   string Stdgif.c) */

void * stdGif_Load(char *param_1,int param_2,int param_3)

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
  
  iVar3 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddb18);
  if (iVar3 == 0) {
    return (void *)0x0;
  }
  iStack_6c = iVar3;
  bitmap = (void *)(*g_pStd_HS->pAlloc)
                             (0x7c,s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x13);
  if (bitmap != (void *)0x0) {
    *(undefined4 *)((int)bitmap + 0x60) = 0;
    *(undefined4 *)((int)bitmap + 0x78) = 0;
    (*g_pStd_HS->pFread)(iVar3,&cStack_5c,3);
    iVar4 = toupper((int)cStack_5c);
    if (((iVar4 == 0x47) && (iVar4 = toupper((int)cStack_5b), iVar4 == 0x49)) &&
       (iVar4 = toupper((int)cStack_5a), iVar4 == 0x46)) {
      (*g_pStd_HS->pFread)(iVar3,&cStack_59,3);
      (*g_pStd_HS->pFread)(iVar3,auStack_56,2);
      (*g_pStd_HS->pFread)(iVar3,auStack_54,2);
      (*g_pStd_HS->pFread)(iVar3,&bStack_52,1);
      (*g_pStd_HS->pFread)(iVar3,&uStack_51,1);
      (*g_pStd_HS->pFread)(iVar3,auStack_50,1);
      if ((bStack_52 & 0x80) != 0) {
        iVar4 = (*g_pStd_HS->pAlloc)
                          (0x300,s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x3b);
        *(int *)((int)bitmap + 0x60) = iVar4;
        if (iVar4 == 0) goto LAB_0047e02f;
        (*g_pStd_HS->pFread)(iVar3,iVar4,(short)(1 << (bStack_52 & 7) + 1) * 3);
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
        (*g_pStd_HS->pFread)(iVar3,&sStack_66,2);
        (*g_pStd_HS->pFread)(iVar3,auStack_64,2);
        (*g_pStd_HS->pFread)(iVar3,&sStack_62,2);
        (*g_pStd_HS->pFread)(iVar3,&sStack_60,2);
        (*g_pStd_HS->pFread)(iVar3,abStack_5e,1);
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
        iVar4 = (*g_pStd_HS->pAlloc)
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
                iVar4 = (*g_pStd_HS->pAlloc)
                                  (0x300,s_C__grimjedi_Libs_Std_General_Std_004e7884,
                                   DAT_004e787c + 0x8a);
                *(int *)((int)bitmap + 0x60) = iVar4;
                if (iVar4 == 0) goto LAB_0047e02f;
              }
              (*g_pStd_HS->pFread)
                        (iVar3,*(undefined4 *)((int)bitmap + 0x60),(short)(1 << bVar2 + 1) * 3);
            }
            iVar4 = (*g_pStd_HS->pAlloc)
                              (*(int *)(**(int **)((int)bitmap + 0x78) + 0xc) + (int)sStack_66,
                               s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x95);
            iStack_7c = iVar4;
            if (iVar4 != 0) {
              (*g_pStd_HS->pFread)(iVar3,&cStack_81,1);
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
                        (*g_pStd_HS->pFree)(iStack_7c);
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
              (*g_pStd_HS->pFree)(iVar4);
              (*g_pStd_HS->pFread)(iVar3,&cStack_81,1);
              (*g_pStd_HS->pFclose)(iVar3);
              return bitmap;
            }
          }
        }
      }
    }
  }
LAB_0047e02f:
  (*g_pStd_HS->pFclose)(iVar3);
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


/* ---- 0x0047e060  stdGif_Save ---- */
undefined4 stdGif_Save(undefined4 param_1,int param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined4 *puVar11;
  #define auStack_1c (*(undefined1 (*)[2])(_frame + (0x30 - 0x1c)))
  #define uStack_1a (*(undefined2 *)(_frame + (0x30 - 0x1a)))
  #define uStack_18 (*(undefined2 *)(_frame + (0x30 - 0x18)))
  #define uStack_16 (*(undefined2 *)(_frame + (0x30 - 0x16)))
  #define uStack_14 (*(undefined2 *)(_frame + (0x30 - 0x14)))
  #define abStack_12 (*(byte (*)[2])(_frame + (0x30 - 0x12)))
  #define auStack_10 (*(undefined1 (*)[3])(_frame + (0x30 - 0x10)))
  #define auStack_d (*(undefined1 (*)[3])(_frame + (0x30 - 0xd)))
  #define uStack_a (*(undefined2 *)(_frame + (0x30 - 0xa)))
  #define uStack_8 (*(undefined2 *)(_frame + (0x30 - 0x8)))
  #define uStack_6 (*(undefined1 *)(_frame + (0x30 - 0x6)))
  #define uStack_5 (*(undefined1 *)(_frame + (0x30 - 0x5)))
  #define auStack_4 (*(undefined1 (*)[4])(_frame + (0x30 - 0x4)))
  
  iVar5 = param_2;
  iVar2 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddd78);
  if (iVar2 != 0) {
    strncpy(auStack_10,&DAT_004e78b0,3);
    (*g_pStd_HS->pFwrite)(iVar2,auStack_10,3);
    strncpy(auStack_d,&DAT_004e78ac,3);
    (*g_pStd_HS->pFwrite)(iVar2,auStack_d,3);
    uStack_a = *(undefined2 *)(**(int **)(param_2 + 0x78) + 0xc);
    uStack_8 = *(undefined2 *)(**(int **)(param_2 + 0x78) + 0x10);
    uStack_6 = 0xf7;
    uStack_5 = 0;
    auStack_4[0] = 0;
    (*g_pStd_HS->pFwrite)(iVar2,&uStack_a,2);
    (*g_pStd_HS->pFwrite)(iVar2,&uStack_8,2);
    (*g_pStd_HS->pFwrite)(iVar2,&uStack_6,1);
    (*g_pStd_HS->pFwrite)(iVar2,&uStack_5,1);
    (*g_pStd_HS->pFwrite)(iVar2,auStack_4,1);
    (*g_pStd_HS->pFwrite)(iVar2,*(undefined4 *)(param_2 + 0x60),0x300);
    auStack_1c[0] = 0x2c;
    uStack_1a = 0;
    uStack_18 = 0;
    uStack_16 = *(undefined2 *)(**(int **)(param_2 + 0x78) + 0xc);
    uStack_14 = *(undefined2 *)(**(int **)(param_2 + 0x78) + 0x10);
    abStack_12[0] = 0;
    (*g_pStd_HS->pFwrite)(iVar2,auStack_1c,1);
    (*g_pStd_HS->pFwrite)(iVar2,&uStack_1a,2);
    (*g_pStd_HS->pFwrite)(iVar2,&uStack_18,2);
    (*g_pStd_HS->pFwrite)(iVar2,&uStack_16,2);
    (*g_pStd_HS->pFwrite)(iVar2,&uStack_14,2);
    (*g_pStd_HS->pFwrite)(iVar2,abStack_12,1);
    iVar8 = 1;
    iVar10 = 0;
    iVar3 = 1 << (abStack_12[0] & 7) + 1;
    if (1 < iVar3) {
      do {
        iVar8 = iVar8 * 2;
        iVar10 = iVar10 + 1;
      } while (iVar8 < iVar3);
    }
    if (iVar10 == 1) {
      iVar10 = 2;
    }
    sVar1 = stdGif_LzwInitEncoder(iVar2,iVar10);
    if ((sVar1 == 0) &&
       (puVar4 = (undefined4 *)
                 (*g_pStd_HS->pAlloc)
                           (*(undefined4 *)(**(int **)(param_2 + 0x78) + 0xc),
                            s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e7880 + 0x55),
       puVar4 != (undefined4 *)0x0)) {
      Surface_Lock((void *)**(undefined4 **)(param_2 + 0x78));
      iVar3 = **(int **)(param_2 + 0x78);
      param_2 = 0;
      if (0 < *(int *)(iVar3 + 0x10)) {
        do {
          uVar7 = *(uint *)(iVar3 + 0xc);
          puVar9 = (undefined4 *)(param_2 * uVar7 + *(int *)(iVar3 + 0x5c));
          puVar11 = puVar4;
          for (uVar6 = uVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
            *puVar11 = *puVar9;
            puVar9 = puVar9 + 1;
            puVar11 = puVar11 + 1;
          }
          for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
            puVar9 = (undefined4 *)((int)puVar9 + 1);
            puVar11 = (undefined4 *)((int)puVar11 + 1);
          }
          iVar3 = 0;
          if (0 < *(int *)(**(int **)(iVar5 + 0x78) + 0xc)) {
            do {
              sVar1 = stdGif_LzwEncodePixel(iVar2,*(undefined1 *)((int)puVar4 + iVar3));
              if (sVar1 != 0) {
                (*g_pStd_HS->pFree)(puVar4);
                (*g_pStd_HS->pFclose)(iVar2);
                return 0;
              }
              iVar3 = iVar3 + 1;
            } while (iVar3 < *(int *)(**(int **)(iVar5 + 0x78) + 0xc));
          }
          param_2 = param_2 + 1;
          iVar3 = **(int **)(iVar5 + 0x78);
        } while (param_2 < *(int *)(iVar3 + 0x10));
      }
      Surface_Unlock((void *)**(undefined4 **)(iVar5 + 0x78));
      stdGif_LzwFinishEncode(iVar2);
      *(undefined1 *)puVar4 = 0;
      iVar5 = (*g_pStd_HS->pFwrite)(iVar2,puVar4,1);
      if (iVar5 == 1) {
        *(undefined1 *)puVar4 = 0x3b;
        iVar5 = (*g_pStd_HS->pFwrite)(iVar2,puVar4,1);
        if (iVar5 == 1) {
          (*g_pStd_HS->pFree)(puVar4);
          (*g_pStd_HS->pFclose)(iVar2);
          return 1;
        }
      }
    }
  }
  (*g_pStd_HS->pFclose)(iVar2);
  return 0;
}
#undef abStack_12
#undef auStack_10
#undef auStack_1c
#undef auStack_4
#undef auStack_d
#undef uStack_14
#undef uStack_16
#undef uStack_18
#undef uStack_1a
#undef uStack_5
#undef uStack_6
#undef uStack_8
#undef uStack_a


/* ---- 0x0047e3c0  stdGif_LzwInitDecoder ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Sets the clear/end codes and code size from the root code size */

uint stdGif_LzwInitDecoder(short param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  _DAT_00811b2c = 1 << ((byte)param_1 & 0x1f);
  PIECE(UINT_0080cbe4,0,2) = param_1 + 1;
  UINT_00812ecc = 0;
  _DAT_00812ebc = _DAT_00811b2c + 1;
  _DAT_0080cbe8 = _DAT_00811b2c + 2;
  DAT_008155f4 = (short)(1 << ((byte)UINT_0080cbe4 & 0x1f)) + -1;
  puVar3 = (undefined4 *)PTR_UINT_004e7874;
  _DAT_00812ec4 = (short)UINT_0080cbe4;
  for (iVar2 = 0x100; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  uVar1 = 0xff;
  iVar2 = 0xff;
  do {
    PTR_UINT_004e7878[iVar2] = (char)uVar1;
    uVar1 = uVar1 - 1;
    iVar2 = iVar2 + -1;
  } while (-1 < (short)uVar1);
  DAT_0080cbec = DAT_0080cbe8;
  PTR_00812ec0 = (int *)&DAT_00811b30;
  DAT_00811b28 = DAT_008155f0;
  DAT_00812ed0 = 0;
  return uVar1 & 0xffff0000;
}

/* ---- 0x0047e470  stdGif_LzwDecodeNext ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Returns the next decoded pixel, walking the prefix/suffix tables */

uint stdGif_LzwDecodeNext(undefined4 param_1)

{
  short sVar1;
  uint uVar2;
  short sVar3;
  int iVar4;
  undefined4 *puVar5;
  
  if (PTR_00812ec0 != (int *)&DAT_00811b30) {
    PTR_00812ec0 = (int *)((int)PTR_00812ec0 + -1);
    return (uint)*(byte *)PTR_00812ec0;
  }
  uVar2 = stdGif_LzwReadCode(param_1);
  if (-1 < (short)uVar2) {
    if ((short)uVar2 == _DAT_00811b2c) {
      puVar5 = (undefined4 *)PTR_UINT_004e7874;
      for (iVar4 = 0x100; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      UINT_00812ecc = 1;
      _DAT_0080cbec = CONCAT22(DAT_0080cbec_2,(short)_DAT_0080cbe8 + -1);
      uVar2 = stdGif_LzwReadCode(param_1);
      if ((short)uVar2 == -1) {
        return uVar2;
      }
    }
    sVar1 = (short)uVar2;
    if (sVar1 == _DAT_00812ebc) {
      return 0xffff;
    }
    if (DAT_0080cbec <= sVar1) {
      *(undefined1 *)PTR_00812ec0 = DAT_00812ec8;
      PTR_00812ec0 = (int *)((int)PTR_00812ec0 + 1);
      uVar2 = _DAT_0080cbe0;
    }
    sVar3 = (short)uVar2;
    iVar4 = (int)sVar3;
    if (_DAT_00812ebc <= iVar4) {
      do {
        *(undefined *)PTR_00812ec0 = PTR_UINT_004e7878[iVar4];
        PTR_00812ec0 = (int *)((int)PTR_00812ec0 + 1);
        sVar3 = *(short *)(PTR_UINT_004e7874 + iVar4 * 2);
        iVar4 = (int)sVar3;
      } while (_DAT_00812ebc <= iVar4);
    }
    _DAT_00812ec8 = (ushort)(byte)PTR_UINT_004e7878[sVar3];
    *(undefined *)PTR_00812ec0 = PTR_UINT_004e7878[sVar3];
    PTR_00812ec0 = (int *)((int)PTR_00812ec0 + 1);
    if (DAT_0080cbec < DAT_004e7800) {
      iVar4 = (int)DAT_0080cbec;
      sVar3 = DAT_0080cbec + 1;
      *(undefined2 *)(PTR_UINT_004e7874 + iVar4 * 2) = DAT_0080cbe0;
      PTR_UINT_004e7878[iVar4] = DAT_00812ec8;
      _DAT_0080cbec = CONCAT22(DAT_0080cbec_2,sVar3);
    }
    _DAT_0080cbe0 = CONCAT22(DAT_0080cbe0_2,sVar1);
    PTR_00812ec0 = (int *)((int)PTR_00812ec0 + -1);
    return (uint)*(byte *)PTR_00812ec0;
  }
  return 0xffff;
}

/* ---- 0x0047e600  stdGif_LzwReadCode ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint stdGif_LzwReadCode(undefined4 param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  sbyte sVar4;
  byte bVar5;
  byte bVar6;
  uint uVar7;
  undefined8 uVar8;
  
  if (DAT_008155f4 < DAT_0080cbec) {
    sVar2 = _DAT_00812ec4 + 1;
    _DAT_00812ec4 = CONCAT22(DAT_00812ec4_2,sVar2);
    if (sVar2 == 0xc) {
      DAT_008155f4 = DAT_004e7800;
    }
    else {
      DAT_00812ec4 = (byte)sVar2;
      DAT_008155f4 = (short)(1 << (DAT_00812ec4 & 0x1f)) + -1;
    }
  }
  if (0 < (int)UINT_00812ecc) {
    _DAT_00812ec4 = CONCAT22(DAT_00812ec4_2,(short)UINT_0080cbe4);
    UINT_00812ecc = 0;
    DAT_008155f4 = (short)(1 << ((byte)UINT_0080cbe4 & 0x1f)) + -1;
  }
  if (DAT_00812ed0 == 0) {
    sVar2 = stdGif_ReadByte(param_1);
    if (sVar2 == 0xffff) {
      return 0xffff;
    }
    DAT_00815600 = (byte)sVar2;
  }
  sVar4 = (sbyte)(DAT_00812ed0 & 7);
  cVar1 = -sVar4;
  bVar5 = cVar1 + 8;
  uVar7 = (uint)(DAT_00815600 >> sVar4);
  sVar2 = ((DAT_00812ed0 & 7) - 8) + (short)_DAT_00812ec4;
  bVar6 = bVar5;
  if (7 < sVar2) {
    uVar8 = stdGif_ReadByte(param_1);
    if ((short)uVar8 == 0xffff) {
      return 0xffff;
    }
    DAT_00815600 = (byte)uVar8;
    bVar6 = cVar1 + 0x10;
    uVar7 = uVar7 | (CONCAT31((int3)((ulonglong)uVar8 >> 0x28),DAT_00815600) & 0xffff00ff) <<
                    (bVar5 & 0x1f);
    sVar2 = sVar2 + -8;
  }
  if (0 < sVar2) {
    uVar3 = stdGif_ReadByte(param_1);
    if ((short)uVar3 == 0xffff) {
      return 0xffff;
    }
    DAT_00815600 = (byte)uVar3;
    uVar7 = uVar7 | (CONCAT22(sVar2 >> 0xf,(ushort)(byte)(&DAT_004e7868)[sVar2]) & uVar3) <<
                    (bVar6 & 0x1f);
  }
  DAT_00812ed0 = (byte)((char)DAT_00812ed0 + DAT_00812ec4) & 7;
  bVar6 = DAT_00812ec4 & 0x1f;
  return (1 << bVar6) - 1U & uVar7;
}

/* ---- 0x0047e770  stdGif_ReadByte ---- */
/* Reads the next byte from the GIF sub-block stream */

uint stdGif_ReadByte(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_00811b28 == DAT_008155f0) {
    DAT_008155f0 = 0;
    iVar1 = (*g_pStd_HS->pFread)(param_1,&DAT_008155f0,1);
    if (iVar1 != 1) {
      return 0xffff;
    }
    iVar1 = (*g_pStd_HS->pFread)(param_1,&DAT_0080cbf8,(int)DAT_008155f0);
    if (iVar1 != DAT_008155f0) {
      return 0xffff;
    }
    DAT_00811b28 = 0;
  }
  iVar1 = (int)DAT_00811b28;
  DAT_00811b28 = DAT_00811b28 + 1;
  return (uint)(byte)(&DAT_0080cbf8)[iVar1];
}

/* ---- 0x0047e7f0  stdGif_LzwInitEncoder ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
    */

uint stdGif_LzwInitEncoder(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined2 extraout_var;
  uint *puVar2;
  
  _DAT_008155f8 = 0;
  DAT_00812ed0 = 0;
  UINT_00812ecc = 0;
  PIECE(UINT_0080cbe4,0,2) = (short)param_2 + 1;
  _DAT_00811b2c = 1 << ((byte)param_2 & 0x1f);
  _DAT_00812ebc = _DAT_00811b2c + 1;
  _DAT_0080cbe8 = _DAT_00811b2c + 2;
  DAT_008155f4 = (short)(1 << ((byte)UINT_0080cbe4 & 0x1f)) + -1;
  DAT_0080cbec = (undefined2)_DAT_0080cbe8;
  puVar2 = &UINT_0080ccf8;
  _DAT_00812ec4 = (short)UINT_0080cbe4;
  for (iVar1 = 0x138b; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0xffffffff;
    puVar2 = puVar2 + 1;
  }
  DAT_0080cbf0 = 1;
  iVar1 = (*g_pStd_HS->pFwrite)(param_1,&param_2,1);
  if (iVar1 != 1) {
    return 1;
  }
  stdGif_LzwWriteCode(param_1,CONCAT22(extraout_var,DAT_00811b2c));
  return _DAT_008155f8 & 0xffff;
}
#endif


/* ---- 0x0047e8b0  stdGif_LzwWriteCode ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void stdGif_LzwWriteCode(undefined4 param_1,short param_2)

{
  undefined4 uVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  ushort uVar5;
  short sVar6;
  
  uVar5 = DAT_00812ed0 & 7;
  sVar2 = (short)DAT_00812ed0 >> 3;
  DAT_00812ed0 = DAT_00812ed0 + _DAT_00812ec4;
  (&DAT_0080cbf8)[(short)(sVar2 + 1)] =
       (char)param_2 << (sbyte)uVar5 & (&DAT_004e7858)[(short)uVar5] |
       (&DAT_004e7868)[(short)uVar5] & (&DAT_0080cbf8)[(short)(sVar2 + 1)];
  sVar3 = sVar2 + 2;
  sVar6 = (uVar5 - 8) + (short)_DAT_00812ec4;
  param_2 = param_2 >> (8U - (sbyte)uVar5 & 0x1f);
  if (7 < sVar6) {
    iVar4 = (int)sVar3;
    sVar3 = sVar2 + 3;
    (&DAT_0080cbf8)[iVar4] = (char)param_2;
    param_2 = param_2 >> 8;
    sVar6 = sVar6 + -8;
  }
  if (sVar3 == 0x100) {
    stdGif_WriteSubBlock(param_1,0xff);
    DAT_00812ed0 = DAT_00812ed0 + -0x7f8;
    sVar3 = 1;
  }
  if (0 < sVar6) {
    if (sVar3 == 0xff) {
      stdGif_WriteSubBlock(param_1,0xfe);
      DAT_00812ed0 = DAT_00812ed0 + -0x7f0;
      sVar3 = 1;
    }
    (&DAT_0080cbf8)[sVar3] = (char)param_2;
  }
  if (DAT_00812ed0 == 0x7f0) {
    stdGif_WriteSubBlock(param_1,0xfe);
    DAT_00812ed0 = 0;
  }
  if ((DAT_008155f4 < DAT_0080cbec) || (0 < (int)UINT_00812ecc)) {
    if (UINT_00812ecc != 0) {
      _DAT_00812ec4 = CONCAT22(DAT_00812ec4_2,(short)UINT_0080cbe4);
      UINT_00812ecc = 0;
      DAT_008155f4 = (short)(1 << ((byte)UINT_0080cbe4 & 0x1f)) + -1;
      return;
    }
    _DAT_00812ec4 = _DAT_00812ec4 + 1;
    uVar1 = _DAT_00812ec4;
    if (_DAT_00812ec4 == 0xc) {
      DAT_008155f4 = DAT_004e7800;
      return;
    }
    DAT_008155f4 = (short)(1 << (DAT_00812ec4 & 0x1f)) + -1;
    _DAT_00812ec4 = uVar1;
  }
  return;
}

/* ---- 0x0047ea30  stdGif_LzwEncodePixel ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
    */

uint stdGif_LzwEncodePixel(undefined4 param_1,byte param_2)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  undefined4 unaff_EBX;
  uint uVar4;
  uint uVar5;
  
  _DAT_008155f8 = 0;
  if (DAT_0080cbf0 != 0) {
    _DAT_00811b24 = CONCAT22(DAT_00811b24_2,(ushort)param_2);
    sVar1 = 0;
    UINT_0081560c = 0x138b;
    do {
      UINT_0081560c = UINT_0081560c * 2;
      sVar1 = sVar1 + 1;
    } while ((int)UINT_0081560c < 0x10000);
    DAT_0080cbf0 = 0;
    _DAT_00815608 = CONCAT22(DAT_00815608_2,8 - sVar1);
    return 0;
  }
  uVar4 = CONCAT31((int3)((uint)unaff_EBX >> 8),param_2) & 0xffff00ff;
  UINT_0081560c = (uint)param_2 * 0x1000 + (_DAT_00811b24 & 0xffff);
  uVar5 = uVar4 << (DAT_00815608 & 0x1f) ^ _DAT_00811b24;
  sVar1 = (short)uVar5;
  uVar2 = (&UINT_0080ccf8)[sVar1];
  if (uVar2 != UINT_0081560c) {
    if (-1 < (int)uVar2) {
      iVar3 = 0x138b - uVar5;
      if (sVar1 == 0) {
        iVar3 = 1;
      }
      do {
        uVar5 = uVar5 - iVar3;
        if ((short)uVar5 < 0) {
          uVar5 = uVar5 + 0x138b;
        }
        sVar1 = (short)uVar5;
        uVar2 = (&UINT_0080ccf8)[sVar1];
        if (uVar2 == UINT_0081560c) {
          _DAT_00811b24 = CONCAT22(DAT_00811b24_2,*(undefined2 *)((int)&UINT_00812ed8 + sVar1 * 2));
          return 0;
        }
      } while (0 < (int)uVar2);
    }
    stdGif_LzwWriteCode(param_1,CONCAT22((short)(uVar2 >> 0x10),DAT_00811b24));
    uVar2 = UINT_0081560c;
    _DAT_00811b24 = CONCAT22(DAT_00811b24_2,(short)uVar4);
    if (DAT_004e7800 <= DAT_0080cbec) {
      stdGif_LzwClearTable(param_1);
      return _DAT_008155f8 & 0xffff;
    }
    *(short *)((int)&UINT_00812ed8 + sVar1 * 2) = DAT_0080cbec;
    (&UINT_0080ccf8)[sVar1] = uVar2;
    DAT_0080cbec = DAT_0080cbec + 1;
    return _DAT_008155f8 & 0xffff;
  }
  _DAT_00811b24 = CONCAT22(DAT_00811b24_2,*(undefined2 *)((int)&UINT_00812ed8 + sVar1 * 2));
  return 0;
}
#endif


/* ---- 0x0047eba0  stdGif_LzwClearTable ---- */
void stdGif_LzwClearTable(undefined4 param_1)

{
  int iVar1;
  uint *puVar2;
  
  UINT_00812ecc = 1;
  puVar2 = &UINT_0080ccf8;
  for (iVar1 = 0x138b; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0xffffffff;
    puVar2 = puVar2 + 1;
  }
  DAT_0080cbec = DAT_0080cbe8;
  stdGif_LzwWriteCode(param_1,DAT_00811b2c);
  return;
}

/* ---- 0x0047ebe0  stdGif_LzwFinishEncode ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 stdGif_LzwFinishEncode(undefined4 param_1)

{
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined4 uVar1;
  undefined2 extraout_var_01;
  undefined2 uVar2;
  
  _DAT_008155f8 = 0;
  stdGif_LzwWriteCode(param_1,DAT_00811b24);
  stdGif_LzwWriteCode(param_1,CONCAT22(extraout_var_01,DAT_00812ebc));
  uVar2 = extraout_var;
  if (DAT_00812ed0 != 1) {
    stdGif_WriteSubBlock(param_1,DAT_00812ed0 + 7 >> 3);
    uVar2 = extraout_var_00;
  }
  uVar1 = CONCAT22(uVar2,DAT_008155f8);
  return uVar1;
}

/* ---- 0x0047ec40  stdGif_WriteSubBlock ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void stdGif_WriteSubBlock(undefined4 param_1,short param_2)

{
  int iVar1;
  
  DAT_0080cbf8 = (undefined1)param_2;
  iVar1 = (*g_pStd_HS->pFwrite)(param_1,&DAT_0080cbf8,param_2 + 1);
  if (iVar1 != param_2 + 1) {
    _DAT_008155f8 = _DAT_008155f8 + 1;
  }
  return;
}
