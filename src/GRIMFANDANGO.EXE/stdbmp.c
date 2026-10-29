/* GRIMFANDANGO.EXE :: stdbmp.c
 * functions 0x0047cb20 .. 0x0047d050 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047cb20  stdBmp_Load ---- */
/* Stdbmp.c: allocates a bitmap record and reads a Windows .bmp */

uint stdBmp_Load(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (*g_pSvcMain->pAlloc)(0x7c,s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e7638 + 4);
  if (uVar1 == 0) {
    return 0;
  }
  iVar2 = stdBmp_LoadInto(param_1,uVar1,param_2,param_3);
  return -(uint)(iVar2 != 0) & uVar1;
}

/* ---- 0x0047cb70  stdBmp_LoadInto ---- */
/* Reads BITMAPFILEHEADER/BITMAPINFOHEADER; 8-bit paletted or 24-bit sources */

undefined4 stdBmp_LoadInto(char *param_1,undefined4 *param_2,int param_3,int param_4)

{
  unsigned char _frame[0xb0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  void *pvVar7;
  byte *pbVar8;
  byte *pbVar9;
  int iVar10;
  int *piVar11;
  undefined4 *puVar12;
  int *piVar13;
  byte *pbVar14;
  bool bVar15;
  undefined4 uVar16;
  #define local_98 (*(int *)(_frame + (0xb0 - 0x98)))
  #define aiStack_84 (*(int (*)[19])(_frame + (0xb0 - 0x84)))
  #define iStack_38 (*(int *)(_frame + (0xb0 - 0x38)))
  #define iStack_34 (*(int *)(_frame + (0xb0 - 0x34)))
  #define iStack_30 (*(int *)(_frame + (0xb0 - 0x30)))
  #define uStack_2a (*(uint *)(_frame + (0xb0 - 0x2a)))
  #define asStack_10 (*(short (*)[8])(_frame + (0xb0 - 0x10)))
  
  local_98 = 0;
  iVar3 = (*g_pSvcMain->pFopen)(param_1,&DAT_004ddb18);
  if (iVar3 == 0) {
    return 0;
  }
  iVar4 = (*g_pSvcMain->pFread)(iVar3,asStack_10,0xe);
  iVar5 = (*g_pSvcMain->pFread)(iVar3,&iStack_38,0x28);
  if (iVar4 + iVar5 != 0x36) {
    return 0;
  }
  if (asStack_10[0] != 0x4d42) {
    return 0;
  }
  if (iStack_38 == 0x28) {
    if ((ushort)uStack_2a < 8) {
      iVar5 = (1 << ((byte)uStack_2a & 0x1f)) * 4;
      local_98 = (*g_pSvcMain->pAlloc)
                           (iVar5 + 0x2c,s_C__grimjedi_Libs_Std_General_Std_004e7644,
                            DAT_004e763c + 0x43);
      iVar4 = (*g_pSvcMain->pFread)(iVar3,local_98,iVar5);
      if (iVar4 != iVar5) {
        (*g_pSvcMain->pAssertFail)
                  (s_Unable_to_read_the_palette__Your_004e777c,
                   s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e763c + 0x46);
      }
    }
    puVar12 = param_2;
    for (iVar4 = 0x1f; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar12 = 0;
      puVar12 = puVar12 + 1;
    }
    uVar16 = 0x1f;
    pcVar6 = Str_FileNameFromPath(param_1);
    strncpy(param_2,pcVar6,uVar16);
    *(undefined1 *)((int)param_2 + 0x1f) = 0;
    param_2[8] = 0;
    param_2[9] = 0;
    param_2[0x18] = local_98;
    param_2[0x19] = 1;
    param_2[0x1a] = 0;
    switch(uStack_2a & 0xffff) {
    case 8:
      param_2[9] = 2;
      param_2[0xb] = uStack_2a & 0xffff;
      param_2[10] = 0;
      break;
    default:
      (*g_pSvcMain->pAssertFail)
                (s_This_BMP_file_uses_a_bit_depth_w_004e76f0,
                 s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e763c + 0x72);
      break;
    case 0x10:
      (*g_pSvcMain->pAssertFail)
                (s_16_bit_per_pixel_BMP_not_yet_sup_004e7754,
                 s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e763c + 0x62);
      break;
    case 0x18:
      aiStack_84[0] = 1;
      aiStack_84[1] = 0x18;
      aiStack_84[2] = 8;
      aiStack_84[3] = 8;
      aiStack_84[4] = 8;
      aiStack_84[5] = 0x10;
      aiStack_84[6] = 8;
      aiStack_84[7] = 0;
      aiStack_84[8] = 0;
      aiStack_84[9] = 0;
      aiStack_84[10] = 0;
      aiStack_84[0xb] = 0;
      aiStack_84[0xc] = 0;
      aiStack_84[0xd] = 0;
      piVar11 = aiStack_84;
      piVar13 = param_2 + 10;
      for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1) {
        *piVar13 = *piVar11;
        piVar11 = piVar11 + 1;
        piVar13 = piVar13 + 1;
      }
      break;
    case 0x20:
      (*g_pSvcMain->pAssertFail)
                (s_32bit_per_pixel_BMP_not_yet_supp_004e772c,
                 s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e763c + 0x66);
    }
    iVar4 = (*g_pSvcMain->pAlloc)
                      (param_2[0x19] << 2,s_C__grimjedi_Libs_Std_General_Std_004e7644,
                       DAT_004e763c + 0x76);
    param_2[0x1e] = iVar4;
    if (iVar4 == 0) {
      (*g_pSvcMain->pAssertFail)
                (s_Unable_to_allocate_memory__004e76d4,s_C__grimjedi_Libs_Std_General_Std_004e7644,
                 DAT_004e763c + 0x77);
    }
    aiStack_84[1] = iStack_30;
    bVar15 = iStack_30 < 0;
    piVar11 = param_2 + 10;
    piVar13 = aiStack_84 + 5;
    for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1) {
      *piVar13 = *piVar11;
      piVar11 = piVar11 + 1;
      piVar13 = piVar13 + 1;
    }
    aiStack_84[0] = iStack_34;
    if (bVar15) {
      aiStack_84[1] = -aiStack_84[1];
    }
    pvVar7 = Surface_Create(aiStack_84,param_3,param_4,local_98);
    *(void **)param_2[0x1e] = pvVar7;
    if (*(int *)param_2[0x1e] == 0) {
      (*g_pSvcMain->pAssertFail)
                (s_Unable_to_allocate_memory__004e76d4,s_C__grimjedi_Libs_Std_General_Std_004e7644,
                 DAT_004e763c + 0x81);
    }
    iVar4 = Surface_Lock(*(void **)param_2[0x1e]);
    if (iVar4 == 0) {
      (*g_pSvcMain->pAssertFail)
                (s_Unable_to_lock_VBuffer_memory__004e76b4,
                 s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e763c + 0x8d);
    }
    iVar4 = *(int *)param_2[0x1e];
    iVar5 = *(int *)(iVar4 + 0x10);
    pbVar1 = *(byte **)(iVar4 + 0x5c);
    iVar2 = *(int *)(iVar4 + 0x18);
    if (0 < iVar5) {
      pbVar14 = pbVar1;
      local_98 = iVar5;
      do {
        iVar4 = (*g_pSvcMain->pFread)(iVar3,pbVar14,*(undefined4 *)(iVar4 + 0x18));
        if (iVar4 != *(int *)(*(int *)param_2[0x1e] + 0x18)) {
          (*g_pSvcMain->pAssertFail)
                    (s_Unable_to_read_all_the_data_from_004e766c,
                     s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e763c + 0xa2);
        }
        (*g_pSvcMain->pFseek)(iVar3,(iVar2 + 3U & 0xfffffffc) - iVar2,1);
        iVar4 = *(int *)param_2[0x1e];
        if ((*(int *)(iVar4 + 0x24) == 0x18) &&
           (iVar10 = 0, pbVar8 = pbVar14, 0 < *(int *)(iVar4 + 0xc))) {
          do {
            *pbVar8 = *pbVar8 ^ pbVar8[2];
            pbVar8[2] = pbVar8[2] ^ *pbVar8;
            *pbVar8 = *pbVar8 ^ pbVar8[2];
            pbVar8 = pbVar8 + 3;
            iVar10 = iVar10 + 1;
            iVar4 = *(int *)param_2[0x1e];
          } while (iVar10 < *(int *)(iVar4 + 0xc));
        }
        pbVar14 = pbVar14 + iVar2;
        local_98 = local_98 + -1;
      } while (local_98 != 0);
    }
    if ((0 < iStack_30) && (local_98 = iVar5 / 2, 0 < local_98)) {
      iVar5 = iVar2 * iVar5;
      pbVar14 = pbVar1;
      do {
        if (0 < iVar2) {
          pbVar9 = pbVar1 + ((iVar5 - iVar2) - (int)pbVar14);
          pbVar8 = pbVar14;
          iVar4 = iVar2;
          do {
            *pbVar8 = *pbVar8 ^ pbVar8[(int)pbVar9];
            pbVar8[(int)pbVar9] = pbVar8[(int)pbVar9] ^ *pbVar8;
            *pbVar8 = *pbVar8 ^ pbVar8[(int)pbVar9];
            pbVar8 = pbVar8 + 1;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
        }
        iVar5 = iVar5 - iVar2;
        pbVar14 = pbVar14 + iVar2;
        local_98 = local_98 + -1;
      } while (local_98 != 0);
    }
    Surface_Unlock(*(void **)param_2[0x1e]);
    (*g_pSvcMain->pFclose)(iVar3);
    return 1;
  }
  return 0;
}
#undef aiStack_84
#undef asStack_10
#undef iStack_30
#undef iStack_34
#undef iStack_38
#undef local_98
#undef uStack_2a


/* ---- 0x0047d050  stdBmp_Save ---- */
undefined4 stdBmp_Save(undefined4 param_1,int param_2)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  byte *pbVar9;
  #define local_38 (*(undefined2 *)(_frame + (0x50 - 0x38)))
  #define iStack_36 (*(int *)(_frame + (0x50 - 0x36)))
  #define uStack_32 (*(undefined2 *)(_frame + (0x50 - 0x32)))
  #define local_30 (*(undefined2 *)(_frame + (0x50 - 0x30)))
  #define iStack_2e (*(int *)(_frame + (0x50 - 0x2e)))
  #define local_28 (*(undefined4 (*)[3])(_frame + (0x50 - 0x28)))
  #define local_1c (*(undefined2 *)(_frame + (0x50 - 0x1c)))
  #define local_1a (*(undefined2 *)(_frame + (0x50 - 0x1a)))
  #define local_18 (*(undefined4 *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(undefined4 *)(_frame + (0x50 - 0x10)))
  #define local_c (*(undefined4 *)(_frame + (0x50 - 0xc)))
  
  iVar1 = **(int **)(param_2 + 0x78);
  if (*(int *)(iVar1 + 0x20) == 0) {
    iVar7 = (1 << ((byte)*(undefined4 *)(iVar1 + 0x24) & 0x1f)) << 2;
  }
  else {
    if (*(int *)(iVar1 + 0x24) != 0x18) {
      (*g_pSvcMain->pAssertFail)
                (s_Only_24bpp_supported_004e77b4,s_C__grimjedi_Libs_Std_General_Std_004e7644,
                 DAT_004e7640 + 0x18);
    }
    iVar7 = 0;
  }
  iStack_2e = iVar7 + 0x36;
  uStack_32 = 0;
  local_30 = 0;
  local_38 = 0x4d42;
  uVar6 = (uint)(*(int *)(iVar1 + 0xc) * *(int *)(iVar1 + 0x10) * *(int *)(iVar1 + 0x24)) >> 3;
  iStack_36 = iStack_2e + uVar6;
  puVar8 = local_28;
  for (iVar5 = 10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  local_28[0] = 0x28;
  local_28[1] = *(undefined4 *)(iVar1 + 0xc);
  local_28[2] = *(undefined4 *)(iVar1 + 0x10);
  local_1c = 1;
  local_1a = *(undefined2 *)(iVar1 + 0x24);
  local_18 = 0;
  local_10 = 0xb12;
  local_c = 0xb12;
  local_14 = uVar6;
  iVar5 = (*g_pSvcMain->pFopen)(param_1,&DAT_004ddd78);
  if (iVar5 == 0) {
    return 0;
  }
  iVar2 = (*g_pSvcMain->pFwrite)(iVar5,&local_38,0xe);
  if (iVar2 != 0xe) {
    (*g_pSvcMain->pFclose)(iVar5);
    return 0;
  }
  iVar2 = (*g_pSvcMain->pFwrite)(iVar5,local_28,0x28);
  if (iVar2 == 0x28) {
    if (0 < iVar7) {
      iVar2 = (*g_pSvcMain->pFwrite)(iVar5,*(undefined4 *)(param_2 + 0x60),iVar7);
      if (iVar2 != iVar7) {
        (*g_pSvcMain->pFclose)(iVar5);
        return 0;
      }
    }
    iVar7 = *(int *)(iVar1 + 0x10);
    uVar6 = (uint)(*(int *)(iVar1 + 0xc) * *(int *)(iVar1 + 0x24)) >> 3;
    do {
      iVar7 = iVar7 + -1;
      if (iVar7 < 0) {
        (*g_pSvcMain->pFclose)(iVar5);
        return 1;
      }
      pbVar9 = (byte *)(iVar7 * *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x5c));
      if ((*(int *)(iVar1 + 0x24) == 0x18) &&
         (iVar2 = 0, pbVar3 = pbVar9, 0 < *(int *)(iVar1 + 0xc))) {
        do {
          *pbVar3 = *pbVar3 ^ pbVar3[2];
          pbVar3[2] = pbVar3[2] ^ *pbVar3;
          *pbVar3 = *pbVar3 ^ pbVar3[2];
          pbVar3 = pbVar3 + 3;
          iVar2 = iVar2 + 1;
        } while (iVar2 < *(int *)(iVar1 + 0xc));
      }
      uVar4 = (*g_pSvcMain->pFwrite)(iVar5,pbVar9,uVar6);
    } while (uVar4 == uVar6);
    (*g_pSvcMain->pFclose)(iVar5);
    return 0;
  }
  (*g_pSvcMain->pFclose)(iVar5);
  return 0;
}
#undef iStack_2e
#undef iStack_36
#undef local_10
#undef local_14
#undef local_18
#undef local_1a
#undef local_1c
#undef local_28
#undef local_30
#undef local_38
#undef local_c
#undef uStack_32

