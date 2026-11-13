/* GRIMFANDANGO.EXE :: stdgif.c
 * functions 0x0047db00 .. 0x0047ec40 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047db00  stdGif_Load ---- */
/* stdLoadImageData loader for '.gif' (LZW through stdGif_LzwInitDecoder/DecodeNext, allocation
   string Stdgif.c); was named stdPcx_Load. */

void * __cdecl stdGif_Load(char *param_1,int param_2,int param_3)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  void *bitmap;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  void *pvVar6;
  int iVar7;
  int iVar8;
  byte bVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  #define cStack_81 (*(char *)(_frame + (0xa0 - 0x81)))
  #define iStack_80 (*(int *)(_frame + (0xa0 - 0x80)))
  #define iStack_7c (*(int *)(_frame + (0xa0 - 0x7c)))
  #define piStack_78 (*(int **)(_frame + (0xa0 - 0x78)))
  #define iStack_74 (*(int *)(_frame + (0xa0 - 0x74)))
  #define iStack_70 (*(int *)(_frame + (0xa0 - 0x70)))
  #define uStack_6c (*(uint *)(_frame + (0xa0 - 0x6c)))
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
  
  uVar2 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddb18);
  if (uVar2 == 0) {
    return (void *)0x0;
  }
  uStack_6c = uVar2;
  bitmap = (void *)(*g_pStd_HS->pAlloc)
                             (0x7c,s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x13);
  if (bitmap != (void *)0x0) {
    *(undefined4 *)((int)bitmap + 0x60) = 0;
    *(undefined4 *)((int)bitmap + 0x78) = 0;
    (*g_pStd_HS->pFread)(uVar2,&cStack_5c,3);
    iVar3 = toupper((int)cStack_5c);
    if (((iVar3 == 0x47) && (iVar3 = toupper((int)cStack_5b), iVar3 == 0x49)) &&
       (iVar3 = toupper((int)cStack_5a), iVar3 == 0x46)) {
      (*g_pStd_HS->pFread)(uVar2,&cStack_59,3);
      (*g_pStd_HS->pFread)(uVar2,auStack_56,2);
      (*g_pStd_HS->pFread)(uVar2,auStack_54,2);
      (*g_pStd_HS->pFread)(uVar2,&bStack_52,1);
      (*g_pStd_HS->pFread)(uVar2,&uStack_51,1);
      (*g_pStd_HS->pFread)(uVar2,auStack_50,1);
      if ((bStack_52 & 0x80) != 0) {
        iVar3 = (*g_pStd_HS->pAlloc)
                          (0x300,s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x3b);
        *(int *)((int)bitmap + 0x60) = iVar3;
        if (iVar3 == 0) goto LAB_0047e02f;
        (*g_pStd_HS->pFread)(uVar2,iVar3,(short)(1 << (bStack_52 & 7) + 1) * 3);
      }
      if (((cStack_59 == '8') && (cStack_58 == '9')) &&
         (iVar3 = toupper((int)cStack_57), iVar3 == 0x41)) {
        uVar4 = stdFGetc(uVar2);
        cVar1 = (char)uVar4;
        while (cVar1 == '!') {
          uVar4 = stdFGetc(uVar2);
          cVar1 = (char)uVar4;
          while (cVar1 != '\0') {
            uVar4 = stdFGetc(uVar2);
            cVar1 = (char)uVar4;
          }
          uVar4 = stdFGetc(uVar2);
          cVar1 = (char)uVar4;
        }
      }
      else {
        uVar4 = stdFGetc(uVar2);
        cVar1 = (char)uVar4;
      }
      if (cVar1 == ',') {
        (*g_pStd_HS->pFread)(uVar2,&sStack_66,2);
        (*g_pStd_HS->pFread)(uVar2,auStack_64,2);
        (*g_pStd_HS->pFread)(uVar2,&sStack_62,2);
        (*g_pStd_HS->pFread)(uVar2,&sStack_60,2);
        (*g_pStd_HS->pFread)(uVar2,abStack_5e,1);
        uVar12 = 0x1f;
        pcVar5 = stdFileFromPath(param_1);
        strncpy(bitmap,pcVar5,uVar12);
        *(undefined1 *)((int)bitmap + 0x1f) = 0;
        *(undefined4 *)((int)bitmap + 0x20) = 0;
        *(undefined4 *)((int)bitmap + 0x24) = 2;
        *(undefined4 *)((int)bitmap + 100) = 1;
        *(undefined4 *)((int)bitmap + 0x68) = 0;
        *(undefined4 *)((int)bitmap + 0x28) = 0;
        *(undefined4 *)((int)bitmap + 0x2c) = 8;
        iVar3 = (*g_pStd_HS->pAlloc)
                          (4,s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x73);
        *(int *)((int)bitmap + 0x78) = iVar3;
        if (iVar3 != 0) {
          iStack_4c = (int)sStack_62;
          iStack_48 = (int)sStack_60;
          uStack_38 = 0;
          uStack_34 = 8;
          pvVar6 = stdDisplay_VBufferNew(&iStack_4c,param_2,param_3,0);
          **(undefined4 **)((int)bitmap + 0x78) = pvVar6;
          if (**(int **)((int)bitmap + 0x78) != 0) {
            if ((abStack_5e[0] & 0x80) != 0) {
              bVar9 = abStack_5e[0] & 7;
              if (*(int *)((int)bitmap + 0x60) == 0) {
                iVar3 = (*g_pStd_HS->pAlloc)
                                  (0x300,s_C__grimjedi_Libs_Std_General_Std_004e7884,
                                   DAT_004e787c + 0x8a);
                *(int *)((int)bitmap + 0x60) = iVar3;
                if (iVar3 == 0) goto LAB_0047e02f;
              }
              (*g_pStd_HS->pFread)
                        (uVar2,*(undefined4 *)((int)bitmap + 0x60),(short)(1 << bVar9 + 1) * 3);
            }
            iVar3 = (*g_pStd_HS->pAlloc)
                              (*(int *)(**(int **)((int)bitmap + 0x78) + 0xc) + (int)sStack_66,
                               s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e787c + 0x95);
            iStack_7c = iVar3;
            if (iVar3 != 0) {
              (*g_pStd_HS->pFread)(uVar2,&cStack_81,1);
              stdGif_LzwInitDecoder((short)cStack_81);
              iVar10 = 0;
              iStack_74 = (-(uint)((abStack_5e[0] & 2) != 0) & 7) + 1;
              iStack_80 = 0;
              stdDisplay_VBufferLock((void *)**(undefined4 **)((int)bitmap + 0x78));
              iStack_70 = 0;
              iVar7 = **(int **)((int)bitmap + 0x78);
              if (0 < *(int *)(iVar7 + 0x10)) {
                piStack_78 = (int *)&DAT_004e780c;
                do {
                  iVar3 = 0;
                  if (0 < *(int *)(iVar7 + 0xc) + (int)sStack_66) {
                    do {
                      uVar4 = stdGif_LzwDecodeNext(uVar2);
                      *(char *)(iVar3 + iStack_7c) = (char)uVar4;
                      if ((uVar4 & 0xff) == 0xffffffff) {
                        (*g_pStd_HS->pFree)(iStack_7c);
                        goto LAB_0047e02f;
                      }
                      iVar3 = iVar3 + 1;
                    } while (iVar3 < *(int *)(**(int **)((int)bitmap + 0x78) + 0xc) + (int)sStack_66
                            );
                  }
                  iVar3 = **(int **)((int)bitmap + 0x78);
                  if (iVar10 <= *(int *)(iVar3 + 0x10)) {
                    iVar7 = *(int *)(iVar3 + 0xc);
                    iVar8 = 0;
                    if (0 < iVar7) {
                      do {
                        iVar11 = iStack_7c + iVar8;
                        iVar8 = iVar8 + 1;
                        *(undefined1 *)(iVar10 * iVar7 + *(int *)(iVar3 + 0x5c) + -1 + iVar8) =
                             *(undefined1 *)(iVar11 + sStack_66);
                        iVar3 = **(int **)((int)bitmap + 0x78);
                        iVar7 = *(int *)(iVar3 + 0xc);
                        iVar10 = iStack_80;
                        uVar2 = uStack_6c;
                      } while (iVar8 < iVar7);
                    }
                  }
                  iVar10 = iVar10 + iStack_74;
                  iVar7 = **(int **)((int)bitmap + 0x78);
                  if (*(int *)(iVar7 + 0x10) <= iVar10) {
                    iVar10 = piStack_78[1];
                    iStack_74 = piStack_78[2];
                    piStack_78 = piStack_78 + 2;
                  }
                  iStack_70 = iStack_70 + 1;
                  iVar3 = iStack_7c;
                  iStack_80 = iVar10;
                } while (iStack_70 < *(int *)(iVar7 + 0x10));
              }
              stdDisplay_VBufferUnlock((void *)**(undefined4 **)((int)bitmap + 0x78));
              (*g_pStd_HS->pFree)(iVar3);
              (*g_pStd_HS->pFread)(uVar2,&cStack_81,1);
              (*g_pStd_HS->pFclose)(uVar2);
              return bitmap;
            }
          }
        }
      }
    }
  }
LAB_0047e02f:
  (*g_pStd_HS->pFclose)(uVar2);
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
#undef uStack_6c


/* ---- 0x0047e060  stdGif_Write ---- */
/* Original name stdGif_Write (the remaster's GrimFandango (Linux): same body (open, "GIF" "89a",
   the screen descriptor from the first frame, the LZW image data); stdWriteImage's "gif" case in
   both builds); was stdGif_Save. */

uint __cdecl stdGif_Write(uint param_1,int param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  undefined4 *puVar9;
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
  
  iVar4 = param_2;
  uVar1 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddd78);
  if (uVar1 != 0) {
    strncpy(auStack_10,&DAT_004e78b0,3);
    (*g_pStd_HS->pFwrite)(uVar1,auStack_10,3);
    strncpy(auStack_d,&DAT_004e78ac,3);
    (*g_pStd_HS->pFwrite)(uVar1,auStack_d,3);
    uStack_a = *(undefined2 *)(**(int **)(param_2 + 0x78) + 0xc);
    uStack_8 = *(undefined2 *)(**(int **)(param_2 + 0x78) + 0x10);
    uStack_6 = 0xf7;
    uStack_5 = 0;
    auStack_4[0] = 0;
    (*g_pStd_HS->pFwrite)(uVar1,&uStack_a,2);
    (*g_pStd_HS->pFwrite)(uVar1,&uStack_8,2);
    (*g_pStd_HS->pFwrite)(uVar1,&uStack_6,1);
    (*g_pStd_HS->pFwrite)(uVar1,&uStack_5,1);
    (*g_pStd_HS->pFwrite)(uVar1,auStack_4,1);
    (*g_pStd_HS->pFwrite)(uVar1,*(undefined4 *)(param_2 + 0x60),0x300);
    auStack_1c[0] = 0x2c;
    uStack_1a = 0;
    uStack_18 = 0;
    uStack_16 = *(undefined2 *)(**(int **)(param_2 + 0x78) + 0xc);
    uStack_14 = *(undefined2 *)(**(int **)(param_2 + 0x78) + 0x10);
    abStack_12[0] = 0;
    (*g_pStd_HS->pFwrite)(uVar1,auStack_1c,1);
    (*g_pStd_HS->pFwrite)(uVar1,&uStack_1a,2);
    (*g_pStd_HS->pFwrite)(uVar1,&uStack_18,2);
    (*g_pStd_HS->pFwrite)(uVar1,&uStack_16,2);
    (*g_pStd_HS->pFwrite)(uVar1,&uStack_14,2);
    (*g_pStd_HS->pFwrite)(uVar1,abStack_12,1);
    iVar6 = 1;
    uVar8 = 0;
    iVar2 = 1 << (abStack_12[0] & 7) + 1;
    if (1 < iVar2) {
      do {
        iVar6 = iVar6 * 2;
        uVar8 = uVar8 + 1;
      } while (iVar6 < iVar2);
    }
    if (uVar8 == 1) {
      uVar8 = 2;
    }
    uVar8 = stdGif_LzwInitEncoder(uVar1,uVar8);
    if (((short)uVar8 == 0) &&
       (puVar3 = (undefined4 *)
                 (*g_pStd_HS->pAlloc)
                           (*(undefined4 *)(**(int **)(param_2 + 0x78) + 0xc),
                            s_C__grimjedi_Libs_Std_General_Std_004e7884,DAT_004e7880 + 0x55),
       puVar3 != (undefined4 *)0x0)) {
      stdDisplay_VBufferLock((void *)**(undefined4 **)(param_2 + 0x78));
      iVar2 = **(int **)(param_2 + 0x78);
      param_2 = 0;
      if (0 < *(int *)(iVar2 + 0x10)) {
        do {
          uVar8 = *(uint *)(iVar2 + 0xc);
          puVar7 = (undefined4 *)(param_2 * uVar8 + *(int *)(iVar2 + 0x5c));
          puVar9 = puVar3;
          for (uVar5 = uVar8 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *puVar9 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar9 = puVar9 + 1;
          }
          for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
            *(undefined1 *)puVar9 = *(undefined1 *)puVar7;
            puVar7 = (undefined4 *)((int)puVar7 + 1);
            puVar9 = (undefined4 *)((int)puVar9 + 1);
          }
          iVar2 = 0;
          if (0 < *(int *)(**(int **)(iVar4 + 0x78) + 0xc)) {
            do {
              uVar8 = stdGif_LzwEncodePixel(uVar1,*(byte *)((int)puVar3 + iVar2));
              if ((short)uVar8 != 0) {
                (*g_pStd_HS->pFree)(puVar3);
                (*g_pStd_HS->pFclose)(uVar1);
                return 0;
              }
              iVar2 = iVar2 + 1;
            } while (iVar2 < *(int *)(**(int **)(iVar4 + 0x78) + 0xc));
          }
          param_2 = param_2 + 1;
          iVar2 = **(int **)(iVar4 + 0x78);
        } while (param_2 < *(int *)(iVar2 + 0x10));
      }
      stdDisplay_VBufferUnlock((void *)**(undefined4 **)(iVar4 + 0x78));
      stdGif_LzwFinishEncode(uVar1);
      *(undefined1 *)puVar3 = 0;
      iVar4 = (*g_pStd_HS->pFwrite)(uVar1,puVar3,1);
      if (iVar4 == 1) {
        *(undefined1 *)puVar3 = 0x3b;
        iVar4 = (*g_pStd_HS->pFwrite)(uVar1,puVar3,1);
        if (iVar4 == 1) {
          (*g_pStd_HS->pFree)(puVar3);
          (*g_pStd_HS->pFclose)(uVar1);
          return 1;
        }
      }
    }
  }
  (*g_pStd_HS->pFclose)(uVar1);
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

uint __cdecl stdGif_LzwInitDecoder(short param_1)

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

uint __cdecl stdGif_LzwDecodeNext(uint param_1)

{
  short sVar1;
  uint uVar2;
  short sVar3;
  int iVar4;
  undefined4 *puVar5;
  
  if (PTR_00812ec0 != (int *)&DAT_00811b30) {
    PTR_00812ec0 = (int *)((int)PTR_00812ec0 + -1);
    return CONCAT22((short)((uint)PTR_00812ec0 >> 0x10),(ushort)*(byte *)PTR_00812ec0);
  }
  uVar2 = getcode(param_1);
  if (-1 < (short)uVar2) {
    if ((short)uVar2 == _DAT_00811b2c) {
      puVar5 = (undefined4 *)PTR_UINT_004e7874;
      for (iVar4 = 0x100; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      UINT_00812ecc = 1;
      _DAT_0080cbec = CONCAT22(DAT_0080cbec_2,(short)_DAT_0080cbe8 + -1);
      uVar2 = getcode(param_1);
      if ((short)uVar2 == -1) {
        return uVar2;
      }
    }
    sVar1 = (short)uVar2;
    if (sVar1 == _DAT_00812ebc) {
      return CONCAT22((short)(uVar2 >> 0x10),0xffff);
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
    return CONCAT22((short)((uint)PTR_00812ec0 >> 0x10),(ushort)*(byte *)PTR_00812ec0);
  }
  return CONCAT22((short)(uVar2 >> 0x10),0xffff);
}

/* ---- 0x0047e600  getcode ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name getcode (the remaster's GrimFandango (Linux): same body (code width grows with
   maxcode up to 12 bits, the clear flag resets it, data sub-blocks read through the std file
   service); the LZW code reader of stdGif_Load in both builds); was stdGif_LzwReadCode. */

uint __cdecl getcode(uint param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  sbyte sVar4;
  undefined4 extraout_EDX;
  byte bVar5;
  byte bVar6;
  undefined4 unaff_EDI;
  uint uVar7;
  
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
    uVar3 = stdGif_ReadByte(param_1);
    if ((short)uVar3 == 0xffff) goto LAB_0047e760;
    DAT_00815600 = (byte)uVar3;
  }
  sVar4 = (sbyte)(DAT_00812ed0 & 7);
  cVar1 = -sVar4;
  bVar5 = cVar1 + 8;
  uVar7 = CONCAT22((short)((uint)unaff_EDI >> 0x10),(ushort)(DAT_00815600 >> sVar4));
  sVar2 = ((DAT_00812ed0 & 7) - 8) + (short)_DAT_00812ec4;
  bVar6 = bVar5;
  if (7 < sVar2) {
    uVar3 = stdGif_ReadByte(param_1);
    if ((short)uVar3 == 0xffff) goto LAB_0047e760;
    DAT_00815600 = (byte)uVar3;
    bVar6 = cVar1 + 0x10;
    uVar7 = uVar7 | (CONCAT31((int3)((uint)extraout_EDX >> 8),DAT_00815600) & 0xffff00ff) <<
                    (bVar5 & 0x1f);
    sVar2 = sVar2 + -8;
  }
  if (0 < sVar2) {
    uVar3 = stdGif_ReadByte(param_1);
    if ((short)uVar3 == 0xffff) {
LAB_0047e760:
      return CONCAT22((short)(uVar3 >> 0x10),0xffff);
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

uint __cdecl stdGif_ReadByte(uint param_1)

{
  int in_EAX;
  int iVar1;
  
  if (DAT_00811b28 == DAT_008155f0) {
    DAT_008155f0 = 0;
    iVar1 = (*g_pStd_HS->pFread)(param_1,&DAT_008155f0,1);
    if (iVar1 != 1) {
      return CONCAT22((short)((uint)iVar1 >> 0x10),0xffff);
    }
    in_EAX = (*g_pStd_HS->pFread)(param_1,&DAT_0080cbf8,(int)DAT_008155f0);
    if (in_EAX != DAT_008155f0) {
      return CONCAT22((short)((uint)in_EAX >> 0x10),0xffff);
    }
    DAT_00811b28 = 0;
  }
  iVar1 = (int)DAT_00811b28;
  DAT_00811b28 = DAT_00811b28 + 1;
  return CONCAT22((short)((uint)in_EAX >> 0x10),(ushort)(byte)(&DAT_0080cbf8)[iVar1]);
}

/* ---- 0x0047e7f0  stdGif_LzwInitEncoder ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
    */

uint __cdecl stdGif_LzwInitEncoder(uint param_1,uint param_2)

{
  undefined2 extraout_var;
  uint uVar1;
  int iVar2;
  uint *puVar3;
  
  _DAT_008155f8 = 0;
  DAT_00812ed0 = 0;
  UINT_00812ecc = 0;
  PIECE(UINT_0080cbe4,0,2) = (short)param_2 + 1;
  _DAT_00811b2c = 1 << ((byte)param_2 & 0x1f);
  _DAT_00812ebc = _DAT_00811b2c + 1;
  _DAT_0080cbe8 = _DAT_00811b2c + 2;
  DAT_008155f4 = (short)(1 << ((byte)UINT_0080cbe4 & 0x1f)) + -1;
  DAT_0080cbec = (undefined2)_DAT_0080cbe8;
  puVar3 = &UINT_0080ccf8;
  _DAT_00812ec4 = (short)UINT_0080cbe4;
  for (iVar2 = 0x138b; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0xffffffff;
    puVar3 = puVar3 + 1;
  }
  DAT_0080cbf0 = 1;
  iVar2 = (*g_pStd_HS->pFwrite)(param_1,&param_2,1);
  if (iVar2 != 1) {
    return CONCAT22((short)((uint)iVar2 >> 0x10),1);
  }
  putcode(param_1,DAT_00811b2c);
  uVar1 = CONCAT22(extraout_var,DAT_008155f8);
  return uVar1;
}
#endif


/* ---- 0x0047e8b0  putcode ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name putcode (the remaster's GrimFandango (Linux): same body (packs the code into the
   output buffer at the bit offset with the lmask / rmask tables); the LZW code writer of
   stdGif_Write in both builds); was stdGif_LzwWriteCode. */

void __cdecl putcode(uint param_1,short param_2)

{
  undefined4 uVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  ushort uVar5;
  short sVar6;
  short sVar7;
  
  uVar5 = DAT_00812ed0 & 7;
  sVar2 = (short)DAT_00812ed0 >> 3;
  DAT_00812ed0 = DAT_00812ed0 + _DAT_00812ec4;
  (&DAT_0080cbf8)[(short)(sVar2 + 1)] =
       (char)param_2 << (sbyte)uVar5 & (&DAT_004e7858)[(short)uVar5] |
       (&DAT_004e7868)[(short)uVar5] & (&DAT_0080cbf8)[(short)(sVar2 + 1)];
  sVar3 = sVar2 + 2;
  sVar7 = (uVar5 - 8) + (short)_DAT_00812ec4;
  sVar6 = param_2 >> (8U - (sbyte)uVar5 & 0x1f);
  if (7 < sVar7) {
    iVar4 = (int)sVar3;
    sVar3 = sVar2 + 3;
    (&DAT_0080cbf8)[iVar4] = (char)sVar6;
    sVar6 = sVar6 >> 8;
    sVar7 = sVar7 + -8;
  }
  if (sVar3 == 0x100) {
    stdGif_WriteSubBlock(param_1,0xff);
    DAT_00812ed0 = DAT_00812ed0 + -0x7f8;
    sVar3 = 1;
  }
  if (0 < sVar7) {
    if (sVar3 == 0xff) {
      stdGif_WriteSubBlock(param_1,0xfe);
      DAT_00812ed0 = DAT_00812ed0 + -0x7f0;
      sVar3 = 1;
    }
    (&DAT_0080cbf8)[sVar3] = (char)sVar6;
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

uint __cdecl stdGif_LzwEncodePixel(uint param_1,byte param_2)

{
  ushort uVar2;
  uint uVar1;
  undefined2 extraout_var;
  short sVar3;
  int iVar4;
  undefined4 unaff_EBX;
  uint uVar5;
  
  _DAT_008155f8 = 0;
  if (DAT_0080cbf0 != 0) {
    _DAT_00811b24 = CONCAT22(DAT_00811b24_2,(ushort)param_2);
    sVar3 = 0;
    UINT_0081560c = 0x138b;
    do {
      UINT_0081560c = UINT_0081560c * 2;
      sVar3 = sVar3 + 1;
    } while ((int)UINT_0081560c < 0x10000);
    DAT_0080cbf0 = 0;
    _DAT_00815608 = CONCAT22(DAT_00815608_2,8 - sVar3);
    return (uint)DAT_00815608_2 << 0x10;
  }
  uVar1 = CONCAT31((int3)((uint)unaff_EBX >> 8),param_2) & 0xffff00ff;
  UINT_0081560c = (uint)param_2 * 0x1000 + (_DAT_00811b24 & 0xffff);
  uVar5 = uVar1 << (DAT_00815608 & 0x1f) ^ _DAT_00811b24;
  sVar3 = (short)uVar5;
  uVar2 = (ushort)(UINT_0081560c >> 0x10);
  if ((&UINT_0080ccf8)[sVar3] != UINT_0081560c) {
    if (-1 < (int)(&UINT_0080ccf8)[sVar3]) {
      iVar4 = 0x138b - uVar5;
      if (sVar3 == 0) {
        iVar4 = 1;
      }
      do {
        uVar5 = uVar5 - iVar4;
        if ((short)uVar5 < 0) {
          uVar5 = uVar5 + 0x138b;
        }
        sVar3 = (short)uVar5;
        if ((&UINT_0080ccf8)[sVar3] == UINT_0081560c) {
          _DAT_00811b24 = CONCAT22(DAT_00811b24_2,*(undefined2 *)((int)&UINT_00812ed8 + sVar3 * 2));
          return (uint)uVar2 << 0x10;
        }
      } while (0 < (int)(&UINT_0080ccf8)[sVar3]);
    }
    putcode(param_1,DAT_00811b24);
    uVar5 = UINT_0081560c;
    _DAT_00811b24 = CONCAT22(DAT_00811b24_2,(short)uVar1);
    if (DAT_004e7800 <= DAT_0080cbec) {
      stdGif_LzwClearTable(param_1);
      uVar1 = CONCAT22(extraout_var,DAT_008155f8);
      return uVar1;
    }
    *(short *)((int)&UINT_00812ed8 + sVar3 * 2) = DAT_0080cbec;
    (&UINT_0080ccf8)[sVar3] = uVar5;
    uVar1 = CONCAT22(sVar3 >> 0xf,DAT_008155f8);
    DAT_0080cbec = DAT_0080cbec + 1;
    return uVar1;
  }
  _DAT_00811b24 = CONCAT22(DAT_00811b24_2,*(undefined2 *)((int)&UINT_00812ed8 + sVar3 * 2));
  return (uint)uVar2 << 0x10;
}
#endif


/* ---- 0x0047eba0  stdGif_LzwClearTable ---- */
void __cdecl stdGif_LzwClearTable(uint param_1)

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
  putcode(param_1,DAT_00811b2c);
  return;
}

/* ---- 0x0047ebe0  stdGif_LzwFinishEncode ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl stdGif_LzwFinishEncode(uint param_1)

{
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  uint uVar1;
  undefined2 uVar2;
  
  _DAT_008155f8 = 0;
  putcode(param_1,DAT_00811b24);
  putcode(param_1,DAT_00812ebc);
  uVar2 = extraout_var;
  if (DAT_00812ed0 != 1) {
    stdGif_WriteSubBlock(param_1,(short)(DAT_00812ed0 + 7 >> 3));
    uVar2 = extraout_var_00;
  }
  uVar1 = CONCAT22(uVar2,DAT_008155f8);
  return uVar1;
}

/* ---- 0x0047ec40  stdGif_WriteSubBlock ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl stdGif_WriteSubBlock(uint param_1,short param_2)

{
  int iVar1;
  
  DAT_0080cbf8 = (undefined1)param_2;
  iVar1 = (*g_pStd_HS->pFwrite)(param_1,&DAT_0080cbf8,param_2 + 1);
  if (iVar1 != param_2 + 1) {
    _DAT_008155f8 = _DAT_008155f8 + 1;
  }
  return;
}
