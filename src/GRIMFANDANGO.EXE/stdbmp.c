/* GRIMFANDANGO.EXE :: stdbmp.c
 * functions 0x0047cb20 .. 0x0047d050 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047cb20  stdBmp_Load ---- */
/* Stdbmp.c: allocates a bitmap record and reads a Windows .bmp */

uint __cdecl stdBmp_Load(uint param_1,uint param_2,uint param_3)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = (uint *)(*g_pStd_HS->pAlloc)
                             (0x7c,s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e7638 + 4);
  if (puVar1 == (uint *)0x0) {
    return 0;
  }
  uVar2 = stdBmp_LoadEntry((char *)param_1,puVar1,param_2,param_3);
  return -(uint)(uVar2 != 0) & (uint)puVar1;
}

/* ---- 0x0047cb70  stdBmp_LoadEntry ---- */
/* Reads BITMAPFILEHEADER/BITMAPINFOHEADER; 8-bit paletted or 24-bit sources Original name
   stdBmp_LoadEntry (the remaster's GrimFandango (Linux): strings: '16 bit-per-pixel BMP not yet
   supported.' | 'Unable to read all the data from your BMP file.  It may be  | 'This BMP file uses
   a bit-depth which I do not support yet.' | 'Unable to read the palette.  Your file is
   corrupted.'); was stdBmp_LoadInto. */

uint __cdecl stdBmp_LoadEntry(char *param_1,uint *param_2,int param_3,int param_4)

{
  unsigned char _frame[0xb0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  void *pvVar7;
  byte *pbVar8;
  byte *pbVar9;
  int iVar10;
  uint *puVar11;
  uint *puVar12;
  byte *pbVar13;
  bool bVar14;
  undefined4 uVar15;
  #define local_98 (*(uint *)(_frame + (0xb0 - 0x98)))
  #define auStack_84 (*(uint (*)[19])(_frame + (0xb0 - 0x84)))
  #define iStack_38 (*(int *)(_frame + (0xb0 - 0x38)))
  #define uStack_34 (*(uint *)(_frame + (0xb0 - 0x34)))
  #define iStack_30 (*(int *)(_frame + (0xb0 - 0x30)))
  #define uStack_2a (*(uint *)(_frame + (0xb0 - 0x2a)))
  #define asStack_10 (*(short (*)[8])(_frame + (0xb0 - 0x10)))
  
  local_98 = 0;
  iVar2 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddb18);
  if (iVar2 == 0) {
    return 0;
  }
  iVar3 = (*g_pStd_HS->pFread)(iVar2,asStack_10,0xe);
  iVar4 = (*g_pStd_HS->pFread)(iVar2,&iStack_38,0x28);
  if (iVar3 + iVar4 != 0x36) {
    return 0;
  }
  if (asStack_10[0] != 0x4d42) {
    return 0;
  }
  if (iStack_38 == 0x28) {
    if ((ushort)uStack_2a < 8) {
      iVar4 = (1 << ((byte)uStack_2a & 0x1f)) * 4;
      local_98 = (*g_pStd_HS->pAlloc)
                           (iVar4 + 0x2c,s_C__grimjedi_Libs_Std_General_Std_004e7644,
                            DAT_004e763c + 0x43);
      iVar3 = (*g_pStd_HS->pFread)(iVar2,local_98,iVar4);
      if (iVar3 != iVar4) {
        (*g_pStd_HS->pAssertFail)
                  (s_Unable_to_read_the_palette__Your_004e777c,
                   s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e763c + 0x46);
      }
    }
    puVar11 = param_2;
    for (iVar3 = 0x1f; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar11 = 0;
      puVar11 = puVar11 + 1;
    }
    uVar15 = 0x1f;
    pcVar5 = stdFileFromPath(param_1);
    strncpy(param_2,pcVar5,uVar15);
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
      (*g_pStd_HS->pAssertFail)
                (s_This_BMP_file_uses_a_bit_depth_w_004e76f0,
                 s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e763c + 0x72);
      break;
    case 0x10:
      (*g_pStd_HS->pAssertFail)
                (s_16_bit_per_pixel_BMP_not_yet_sup_004e7754,
                 s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e763c + 0x62);
      break;
    case 0x18:
      auStack_84[0] = 1;
      auStack_84[1] = 0x18;
      auStack_84[2] = 8;
      auStack_84[3] = 8;
      auStack_84[4] = 8;
      auStack_84[5] = 0x10;
      auStack_84[6] = 8;
      auStack_84[7] = 0;
      auStack_84[8] = 0;
      auStack_84[9] = 0;
      auStack_84[10] = 0;
      auStack_84[0xb] = 0;
      auStack_84[0xc] = 0;
      auStack_84[0xd] = 0;
      puVar11 = auStack_84;
      puVar12 = param_2 + 10;
      for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar12 = *puVar11;
        puVar11 = puVar11 + 1;
        puVar12 = puVar12 + 1;
      }
      break;
    case 0x20:
      (*g_pStd_HS->pAssertFail)
                (s_32bit_per_pixel_BMP_not_yet_supp_004e772c,
                 s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e763c + 0x66);
    }
    uVar6 = (*g_pStd_HS->pAlloc)
                      (param_2[0x19] << 2,s_C__grimjedi_Libs_Std_General_Std_004e7644,
                       DAT_004e763c + 0x76);
    param_2[0x1e] = uVar6;
    if (uVar6 == 0) {
      (*g_pStd_HS->pAssertFail)
                (s_Unable_to_allocate_memory__004e76d4,s_C__grimjedi_Libs_Std_General_Std_004e7644,
                 DAT_004e763c + 0x77);
    }
    auStack_84[1] = iStack_30;
    bVar14 = iStack_30 < 0;
    puVar11 = param_2 + 10;
    puVar12 = auStack_84 + 5;
    for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + 1;
      puVar12 = puVar12 + 1;
    }
    auStack_84[0] = uStack_34;
    if (bVar14) {
      auStack_84[1] = -auStack_84[1];
    }
    pvVar7 = stdDisplay_VBufferNew(auStack_84,param_3,param_4,local_98);
    *(void **)param_2[0x1e] = pvVar7;
    if (*(int *)param_2[0x1e] == 0) {
      (*g_pStd_HS->pAssertFail)
                (s_Unable_to_allocate_memory__004e76d4,s_C__grimjedi_Libs_Std_General_Std_004e7644,
                 DAT_004e763c + 0x81);
    }
    iVar3 = stdDisplay_VBufferLock(*(void **)param_2[0x1e]);
    if (iVar3 == 0) {
      (*g_pStd_HS->pAssertFail)
                (s_Unable_to_lock_VBuffer_memory__004e76b4,
                 s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e763c + 0x8d);
    }
    iVar3 = *(int *)param_2[0x1e];
    uVar6 = *(uint *)(iVar3 + 0x10);
    pbVar1 = *(byte **)(iVar3 + 0x5c);
    iVar4 = *(int *)(iVar3 + 0x18);
    if (0 < (int)uVar6) {
      pbVar13 = pbVar1;
      local_98 = uVar6;
      do {
        iVar3 = (*g_pStd_HS->pFread)(iVar2,pbVar13,*(undefined4 *)(iVar3 + 0x18));
        if (iVar3 != *(int *)(*(int *)param_2[0x1e] + 0x18)) {
          (*g_pStd_HS->pAssertFail)
                    (s_Unable_to_read_all_the_data_from_004e766c,
                     s_C__grimjedi_Libs_Std_General_Std_004e7644,DAT_004e763c + 0xa2);
        }
        (*g_pStd_HS->pFseek)(iVar2,(iVar4 + 3U & 0xfffffffc) - iVar4,1);
        iVar3 = *(int *)param_2[0x1e];
        if ((*(int *)(iVar3 + 0x24) == 0x18) &&
           (iVar10 = 0, pbVar8 = pbVar13, 0 < *(int *)(iVar3 + 0xc))) {
          do {
            *pbVar8 = *pbVar8 ^ pbVar8[2];
            pbVar8[2] = pbVar8[2] ^ *pbVar8;
            *pbVar8 = *pbVar8 ^ pbVar8[2];
            pbVar8 = pbVar8 + 3;
            iVar10 = iVar10 + 1;
            iVar3 = *(int *)param_2[0x1e];
          } while (iVar10 < *(int *)(iVar3 + 0xc));
        }
        pbVar13 = pbVar13 + iVar4;
        local_98 = local_98 - 1;
      } while (local_98 != 0);
    }
    if ((0 < iStack_30) && (local_98 = (int)uVar6 / 2, 0 < (int)local_98)) {
      iVar3 = iVar4 * uVar6;
      pbVar13 = pbVar1;
      do {
        if (0 < iVar4) {
          pbVar9 = pbVar1 + ((iVar3 - iVar4) - (int)pbVar13);
          pbVar8 = pbVar13;
          iVar10 = iVar4;
          do {
            *pbVar8 = *pbVar8 ^ pbVar8[(int)pbVar9];
            pbVar8[(int)pbVar9] = pbVar8[(int)pbVar9] ^ *pbVar8;
            *pbVar8 = *pbVar8 ^ pbVar8[(int)pbVar9];
            pbVar8 = pbVar8 + 1;
            iVar10 = iVar10 + -1;
          } while (iVar10 != 0);
        }
        iVar3 = iVar3 - iVar4;
        pbVar13 = pbVar13 + iVar4;
        local_98 = local_98 - 1;
      } while (local_98 != 0);
    }
    stdDisplay_VBufferUnlock(*(void **)param_2[0x1e]);
    (*g_pStd_HS->pFclose)(iVar2);
    return 1;
  }
  return 0;
}
#undef asStack_10
#undef auStack_84
#undef iStack_30
#undef iStack_38
#undef local_98
#undef uStack_2a
#undef uStack_34


/* ---- 0x0047d050  stdBmp_Write ---- */
/* Original name stdBmp_Write (the remaster's GrimFandango (Linux): aligned call in stdWriteImage);
   was stdBmp_Save. */

uint __cdecl stdBmp_Write(uint param_1,int param_2)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  byte *pbVar9;
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(undefined2 *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(undefined2 *)(_frame + (0x50 - 0x1c)))
  #define local_1a (*(undefined2 *)(_frame + (0x50 - 0x1a)))
  #define local_18 (*(uint *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x50 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x50 - 0xc)))
  
  iVar1 = **(int **)(param_2 + 0x78);
  if (*(int *)(iVar1 + 0x20) == 0) {
    iVar7 = (1 << ((byte)*(undefined4 *)(iVar1 + 0x24) & 0x1f)) << 2;
  }
  else {
    if (*(int *)(iVar1 + 0x24) != 0x18) {
      (*g_pStd_HS->pAssertFail)
                (s_Only_24bpp_supported_004e77b4,s_C__grimjedi_Libs_Std_General_Std_004e7644,
                 DAT_004e7640 + 0x18);
    }
    iVar7 = 0;
  }
  iVar2 = iVar7 + 0x36;
  PIECE(local_34,2,2) = 0;
  PIECE(local_30,0,2) = 0;
  PIECE(local_38,0,2) = 0x4d42;
  uVar6 = (uint)(*(int *)(iVar1 + 0xc) * *(int *)(iVar1 + 0x10) * *(int *)(iVar1 + 0x24)) >> 3;
  PIECE(local_30,2,2) = (undefined2)iVar2;
  local_2c = (undefined2)((uint)iVar2 >> 0x10);
  iVar2 = iVar2 + uVar6;
  PIECE(local_38,2,2) = (undefined2)iVar2;
  PIECE(local_34,0,2) = (undefined2)((uint)iVar2 >> 0x10);
  puVar8 = &local_28;
  for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  local_28 = 0x28;
  local_24 = *(uint *)(iVar1 + 0xc);
  local_20 = *(uint *)(iVar1 + 0x10);
  local_1c = 1;
  local_1a = *(undefined2 *)(iVar1 + 0x24);
  local_18 = 0;
  local_10 = 0xb12;
  local_c = 0xb12;
  local_14 = uVar6;
  iVar2 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddd78);
  if (iVar2 == 0) {
    return 0;
  }
  iVar3 = (*g_pStd_HS->pFwrite)(iVar2,&local_38,0xe);
  if (iVar3 != 0xe) {
    (*g_pStd_HS->pFclose)(iVar2);
    return 0;
  }
  iVar3 = (*g_pStd_HS->pFwrite)(iVar2,&local_28,0x28);
  if (iVar3 == 0x28) {
    if ((0 < iVar7) &&
       (iVar3 = (*g_pStd_HS->pFwrite)(iVar2,*(undefined4 *)(param_2 + 0x60),iVar7), iVar3 != iVar7))
    {
      (*g_pStd_HS->pFclose)(iVar2);
      return 0;
    }
    iVar7 = *(int *)(iVar1 + 0x10);
    uVar6 = (uint)(*(int *)(iVar1 + 0xc) * *(int *)(iVar1 + 0x24)) >> 3;
    do {
      iVar7 = iVar7 + -1;
      if (iVar7 < 0) {
        (*g_pStd_HS->pFclose)(iVar2);
        return 1;
      }
      pbVar9 = (byte *)(iVar7 * *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x5c));
      if ((*(int *)(iVar1 + 0x24) == 0x18) &&
         (iVar3 = 0, pbVar4 = pbVar9, 0 < *(int *)(iVar1 + 0xc))) {
        do {
          *pbVar4 = *pbVar4 ^ pbVar4[2];
          pbVar4[2] = pbVar4[2] ^ *pbVar4;
          *pbVar4 = *pbVar4 ^ pbVar4[2];
          pbVar4 = pbVar4 + 3;
          iVar3 = iVar3 + 1;
        } while (iVar3 < *(int *)(iVar1 + 0xc));
      }
      uVar5 = (*g_pStd_HS->pFwrite)(iVar2,pbVar9,uVar6);
    } while (uVar5 == uVar6);
    (*g_pStd_HS->pFclose)(iVar2);
    return 0;
  }
  (*g_pStd_HS->pFclose)(iVar2);
  return 0;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1a
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_c

