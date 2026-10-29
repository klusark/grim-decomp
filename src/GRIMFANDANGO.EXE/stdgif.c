/* GRIMFANDANGO.EXE :: stdgif.c
 * functions 0x0047d280 .. 0x0047ec40 (13 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047d280  stdGif_Load ---- */
uint stdGif_Load(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (*g_pSvcMain->pAlloc)(0x7c,s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77cc + 4);
  if (uVar1 == 0) {
    return 0;
  }
  iVar2 = stdGif_LoadInto(param_1,uVar1,param_2,param_3);
  return -(uint)(iVar2 != 0) & uVar1;
}

/* ---- 0x0047d2d0  stdGif_LoadInto ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Stdgif.c: GIF87/89 decoder (LZW via the stdGif_Lzw* helpers) */

undefined4 stdGif_LoadInto(char *param_1,undefined4 *param_2,int param_3,int param_4)

{
  unsigned char _frame[0x160] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  short sVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  void *pvVar9;
  int iVar10;
  undefined1 *puVar11;
  undefined4 unaff_ESI;
  uint uVar12;
  int iVar13;
  uint *puVar14;
  undefined4 *puVar15;
  undefined4 unaff_EDI;
  uint uVar16;
  uint *puVar17;
  bool bVar18;
  longlong lVar19;
  undefined4 uVar20;
  #define bStack_14b (*(byte *)(_frame + (0x160 - 0x14b)))
  #define bStack_14a (*(byte *)(_frame + (0x160 - 0x14a)))
  #define bStack_149 (*(byte *)(_frame + (0x160 - 0x149)))
  #define puStack_148 (*(undefined4 **)(_frame + (0x160 - 0x148)))
  #define uStack_141 (*(undefined1 *)(_frame + (0x160 - 0x141)))
  #define iStack_140 (*(int *)(_frame + (0x160 - 0x140)))
  #define iStack_13c (*(int *)(_frame + (0x160 - 0x13c)))
  #define iStack_138 (*(int *)(_frame + (0x160 - 0x138)))
  #define iStack_134 (*(int *)(_frame + (0x160 - 0x134)))
  #define iStack_130 (*(int *)(_frame + (0x160 - 0x130)))
  #define iStack_12c (*(int *)(_frame + (0x160 - 0x12c)))
  #define uStack_128 (*(uint *)(_frame + (0x160 - 0x128)))
  #define uStack_124 (*(uint *)(_frame + (0x160 - 0x124)))
  #define puStack_120 (*(uint **)(_frame + (0x160 - 0x120)))
  #define uStack_11c (*(uint *)(_frame + (0x160 - 0x11c)))
  #define uStack_118 (*(uint *)(_frame + (0x160 - 0x118)))
  #define uStack_114 (*(uint *)(_frame + (0x160 - 0x114)))
  #define uStack_110 (*(undefined4 *)(_frame + (0x160 - 0x110)))
  #define cStack_10c (*(char *)(_frame + (0x160 - 0x10c)))
  #define cStack_10b (*(char *)(_frame + (0x160 - 0x10b)))
  #define uStack_10a (*(ushort *)(_frame + (0x160 - 0x10a)))
  #define iStack_104 (*(int *)(_frame + (0x160 - 0x104)))
  #define auStack_100 (*(undefined1 (*)[4])(_frame + (0x160 - 0x100)))
  #define local_fc (*(uint *)(_frame + (0x160 - 0xfc)))
  #define local_f8 (*(uint *)(_frame + (0x160 - 0xf8)))
  #define local_f4 (*(uint *)(_frame + (0x160 - 0xf4)))
  #define local_f0 (*(uint *)(_frame + (0x160 - 0xf0)))
  #define uStack_ec (*(uint *)(_frame + (0x160 - 0xec)))
  #define fStack_e8 (*(float *)(_frame + (0x160 - 0xe8)))
  #define uStack_94 (*(uint *)(_frame + (0x160 - 0x94)))
  #define uStack_90 (*(undefined1 *)(_frame + (0x160 - 0x90)))
  #define uStack_8f (*(undefined1 *)(_frame + (0x160 - 0x8f)))
  #define uStack_8e (*(undefined1 *)(_frame + (0x160 - 0x8e)))
  #define uStack_8d (*(undefined1 *)(_frame + (0x160 - 0x8d)))
  #define fStack_8c (*(float *)(_frame + (0x160 - 0x8c)))
  #define uStack_88 (*(undefined2 *)(_frame + (0x160 - 0x88)))
  #define uStack_86 (*(undefined2 *)(_frame + (0x160 - 0x86)))
  #define local_84 (*(uint *)(_frame + (0x160 - 0x84)))
  #define local_80 (*(uint *)(_frame + (0x160 - 0x80)))
  #define local_7c (*(uint *)(_frame + (0x160 - 0x7c)))
  #define local_78 (*(uint *)(_frame + (0x160 - 0x78)))
  #define local_74 (*(uint *)(_frame + (0x160 - 0x74)))
  #define local_70 (*(uint *)(_frame + (0x160 - 0x70)))
  #define local_6c (*(uint *)(_frame + (0x160 - 0x6c)))
  #define local_68 (*(uint *)(_frame + (0x160 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0x160 - 0x64)))
  #define local_60 (*(uint *)(_frame + (0x160 - 0x60)))
  #define local_5c (*(uint *)(_frame + (0x160 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x160 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x160 - 0x54)))
  #define local_50 (*(uint *)(_frame + (0x160 - 0x50)))
  #define uStack_4c (*(uint *)(_frame + (0x160 - 0x4c)))
  #define uStack_48 (*(uint *)(_frame + (0x160 - 0x48)))
  #define auStack_38 (*(uint (*)[14])(_frame + (0x160 - 0x38)))
  
  local_7c = 8;
  local_78 = 8;
  local_74 = 8;
  local_6c = 8;
  local_fc = 0;
  local_f8 = 0;
  local_f4 = 0;
  local_f0 = 0;
  local_84 = 1;
  local_80 = 0x18;
  local_70 = 0x10;
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  iVar5 = (*g_pSvcMain->pFopen)(param_1,&DAT_004ddb18);
  if (iVar5 == 0) {
    return 0;
  }
  iVar6 = (*g_pSvcMain->pFread)(iVar5,&uStack_ec,0x68);
  if (iVar6 != 0x68) {
    return 0;
  }
  uVar12 = (uStack_ec << 0x10 | uStack_ec & 0xff00) << 8 |
           (uStack_ec >> 0x10 | uStack_ec & 0xff0000) >> 8;
  uStack_ec = uVar12;
  lVar19 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  uVar3 = uStack_8e;
  uVar2 = uStack_90;
  uVar7 = (uint)lVar19;
  uStack_110 = 0;
  uStack_114 = (uVar7 & 0xff00 | uVar7 << 0x10) << 8 | (uVar7 >> 0x10 | uVar7 & 0xff0000) >> 8;
  fStack_e8 = (float)uStack_114;
  uStack_90 = uStack_8f;
  uStack_8f = uVar2;
  uVar16 = (uStack_94 << 0x10 | uStack_94 & 0xff00) << 8 |
           (uStack_94 >> 0x10 | uStack_94 & 0xff0000) >> 8;
  uStack_8e = uStack_8d;
  uStack_8d = uVar3;
  uStack_94 = uVar16;
  lVar19 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  uVar7 = (uint)lVar19;
  uStack_110 = 0;
  uStack_114 = (uVar7 & 0xff00 | uVar7 << 0x10) << 8 | (uVar7 >> 0x10 | uVar7 & 0xff0000) >> 8;
  fStack_8c = (float)uStack_114;
  uStack_88 = CONCAT11((undefined1)uStack_88,PIECE(uStack_88,1,1));
  uStack_86 = CONCAT11((undefined1)uStack_86,PIECE(uStack_86,1,1));
  if (uVar12 != 0x5380f634) {
    return 0;
  }
  if (uVar16 == 0x50494354) {
    iStack_140 = -1;
    iStack_138 = -1;
    iStack_134 = -1;
    iStack_130 = -1;
    iVar13 = 0;
    iVar6 = (*g_pSvcMain->pFread)(iVar5,&cStack_10c,4);
    if (iVar6 == 4) {
      puVar14 = &local_fc;
      while( true ) {
        bStack_14a = (byte)(uStack_10a >> 8);
        if ((uStack_10a & 0x8000) != 0) {
          iStack_140 = iVar13;
        }
        bStack_149 = bStack_14a & 0x40;
        if ((uStack_10a & 0x4000) != 0) {
          iStack_138 = iVar13;
        }
        bStack_14a = bStack_14a & 0x20;
        if ((uStack_10a & 0x2000) != 0) {
          iStack_134 = iVar13;
        }
        if ((uStack_10a & 0x1000) != 0) {
          iStack_130 = iVar13;
        }
        uVar7 = (uint)CONCAT21(uStack_10a,cStack_10b);
        if ((uStack_10a & 0x8000) != 0) {
          uStack_128 = (uVar7 & 0xff) >> 3;
        }
        if ((uStack_10a & 0x4000) != 0) {
          uStack_118 = (uVar7 & 0xff) >> 3;
        }
        if ((uStack_10a & 0x2000) != 0) {
          uStack_11c = (uVar7 & 0xff) >> 3;
        }
        if ((uStack_10a & 0x1000) != 0) {
          uStack_124 = (uVar7 & 0xff) >> 3;
        }
        *puVar14 = uStack_10a & 0xff;
        if (cStack_10b != '\b') break;
        iVar13 = iVar13 + 1;
        puVar14 = puVar14 + 1;
        if (cStack_10c == '\0') {
          uVar20 = 0x1f;
          puVar15 = param_2;
          for (iVar6 = 0x1f; iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar15 = 0;
            puVar15 = puVar15 + 1;
          }
          iStack_12c = iVar13;
          pcVar8 = Str_FileNameFromPath(param_1);
          strncpy(param_2,pcVar8,uVar20);
          *(undefined1 *)((int)param_2 + 0x1f) = 0;
          param_2[8] = 0;
          param_2[9] = 0;
          param_2[0x18] = 0;
          param_2[0x19] = 1;
          param_2[0x1a] = 0;
          puVar14 = &local_84;
          puVar17 = param_2 + 10;
          for (iVar6 = 0xe; iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar17 = *puVar14;
            puVar14 = puVar14 + 1;
            puVar17 = puVar17 + 1;
          }
          iVar6 = (*g_pSvcMain->pAlloc)
                            (4,s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77d0 + 0x6d);
          param_2[0x1e] = iVar6;
          if (iVar6 == 0) {
            (*g_pSvcMain->pAssertFail)
                      (s_Unable_to_allocate_memory__004e76d4,
                       s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77d0 + 0x6e);
          }
          uStack_4c = CONCAT12(uStack_8e,CONCAT11(uStack_8f,uStack_90)) & 0xffff;
          puVar14 = param_2 + 10;
          puVar17 = auStack_38;
          for (iVar6 = 0xe; iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar17 = *puVar14;
            puVar14 = puVar14 + 1;
            puVar17 = puVar17 + 1;
          }
          uStack_48 = (uint)CONCAT11(uStack_8d,uStack_8e);
          pvVar9 = Surface_Create(&uStack_4c,param_3,param_4,0);
          *(void **)param_2[0x1e] = pvVar9;
          if (*(int *)param_2[0x1e] == 0) {
            (*g_pSvcMain->pAssertFail)
                      (s_Unable_to_allocate_memory__004e76d4,
                       s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77d0 + 0x76);
          }
          iVar6 = Surface_Lock(*(void **)param_2[0x1e]);
          if (iVar6 == 0) {
            (*g_pSvcMain->pAssertFail)
                      (s_Unable_to_lock_VBuffer_memory__004e76b4,
                       s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77d0 + 0x7c);
          }
          iStack_104 = 0;
          uStack_114 = *(int *)(*(int *)param_2[0x1e] + 0x18);
          puVar15 = param_2;
          iVar6 = *(int *)(*(int *)param_2[0x1e] + 0x5c);
          if (CONCAT11(uStack_8d,uStack_8e) != 0) {
            do {
              iStack_13c = iVar6;
              iVar6 = 0;
              if (0 < iStack_12c) {
                puStack_120 = &local_fc;
                do {
                  if (*puStack_120 == 0) {
                    iVar13 = 0;
                    if (CONCAT11(uStack_8f,uStack_90) != 0) {
                      puVar15 = (undefined4 *)(iStack_13c + 2);
                      do {
                        if (iStack_140 == iVar6) {
                          (*g_pSvcMain->pFread)(iVar5,(int)puVar15 + -2,uStack_128);
                        }
                        if (iStack_138 == iVar6) {
                          (*g_pSvcMain->pFread)(iVar5,(int)puVar15 + -1,uStack_118);
                        }
                        if (iStack_134 == iVar6) {
                          (*g_pSvcMain->pFread)(iVar5,puVar15,uStack_11c);
                        }
                        if (iStack_130 == iVar6) {
                          (*g_pSvcMain->pFread)(iVar5,auStack_100,uStack_124);
                        }
                        iVar13 = iVar13 + 1;
                        puVar15 = (undefined4 *)((int)puVar15 + 3);
                      } while (iVar13 < (int)(CONCAT12(uStack_8e,CONCAT11(uStack_8f,uStack_90)) &
                                             0xffff));
                    }
                  }
                  else {
                    iVar13 = 0;
                    if (CONCAT11(uStack_8f,uStack_90) != 0) {
                      do {
                        (*g_pSvcMain->pFread)(iVar5,&bStack_14b,1);
                        if (bStack_14b < 0x80) {
                          if (bStack_14b != 0xff) {
                            puVar15 = (undefined4 *)(iVar13 * 3 + 2 + iStack_13c);
                            do {
                              if (iStack_140 == iVar6) {
                                (*g_pSvcMain->pFread)(iVar5,(int)puVar15 + -2,uStack_128);
                              }
                              if (iStack_138 == iVar6) {
                                (*g_pSvcMain->pFread)(iVar5,(int)puVar15 + -1,uStack_118);
                              }
                              if (iStack_134 == iVar6) {
                                (*g_pSvcMain->pFread)(iVar5,puVar15,uStack_11c);
                              }
                              if (iStack_130 == iVar6) {
                                (*g_pSvcMain->pFread)(iVar5,auStack_100,uStack_124);
                              }
                              iVar13 = iVar13 + 1;
                              puVar15 = (undefined4 *)((int)puVar15 + 3);
                              bVar4 = bStack_14b - 1;
                              bVar18 = bStack_14b != 0;
                              bStack_14b = bVar4;
                            } while (bVar18);
                          }
                        }
                        else {
                          if (bStack_14b == 0x80) {
                            (*g_pSvcMain->pFread)(iVar5,&puStack_148,2);
                            puStack_148 = (undefined4 *)
                                          (uint)CONCAT11((char)puStack_148,
                                                         (char)((uint)puStack_148 >> 8));
                          }
                          else {
                            puStack_148 = (undefined4 *)
                                          (CONCAT22((short)((uint)puVar15 >> 0x10),
                                                    (ushort)bStack_14b) - 0x7f);
                          }
                          if (iStack_140 == iVar6) {
                            (*g_pSvcMain->pFread)(iVar5,&bStack_14a,uStack_128);
                          }
                          if (iStack_138 == iVar6) {
                            (*g_pSvcMain->pFread)(iVar5,&bStack_149,uStack_118);
                          }
                          if (iStack_134 == iVar6) {
                            (*g_pSvcMain->pFread)(iVar5,&uStack_141,uStack_11c);
                          }
                          if (iStack_130 == iVar6) {
                            (*g_pSvcMain->pFread)(iVar5,auStack_100,uStack_124);
                          }
                          sVar1 = (short)puStack_148;
                          puVar15 = (undefined4 *)((int)puStack_148 + 0xffff);
                          puStack_148 = puVar15;
                          if (sVar1 != 0) {
                            iVar10 = ((uint)puVar15 & 0xffff) + 1;
                            puVar11 = (undefined1 *)(iVar13 * 3 + 2 + iStack_13c);
                            iVar13 = iVar13 + iVar10;
                            do {
                              if (iStack_140 == iVar6) {
                                puVar11[-2] = bStack_14a;
                              }
                              if (iStack_138 == iVar6) {
                                puVar11[-1] = bStack_149;
                              }
                              if (iStack_134 == iVar6) {
                                *puVar11 = uStack_141;
                              }
                              puVar11 = puVar11 + 3;
                              iVar10 = iVar10 + -1;
                              puVar15 = (undefined4 *)((int)puVar15 + 0xffff);
                              puStack_148 = puVar15;
                            } while (iVar10 != 0);
                          }
                        }
                      } while (iVar13 < (int)(CONCAT12(uStack_8e,CONCAT11(uStack_8f,uStack_90)) &
                                             0xffff));
                    }
                  }
                  iVar6 = iVar6 + 1;
                  puStack_120 = puStack_120 + 1;
                } while (iVar6 < iStack_12c);
              }
              iStack_104 = iStack_104 + 1;
              iStack_13c = iStack_13c + uStack_114;
              iVar6 = iStack_13c;
            } while (iStack_104 < (int)(uint)CONCAT11(uStack_8d,uStack_8e));
          }
          Surface_Unlock(*(void **)param_2[0x1e]);
          (*g_pSvcMain->pFclose)(iVar5);
          return 1;
        }
        iVar6 = (*g_pSvcMain->pFread)(iVar5,&cStack_10c,4);
        if (iVar6 != 4) {
          return 0;
        }
      }
    }
    return 0;
  }
  return 0;
}
#undef auStack_100
#undef auStack_38
#undef bStack_149
#undef bStack_14a
#undef bStack_14b
#undef cStack_10b
#undef cStack_10c
#undef fStack_8c
#undef fStack_e8
#undef iStack_104
#undef iStack_12c
#undef iStack_130
#undef iStack_134
#undef iStack_138
#undef iStack_13c
#undef iStack_140
#undef local_50
#undef local_54
#undef local_58
#undef local_5c
#undef local_60
#undef local_64
#undef local_68
#undef local_6c
#undef local_70
#undef local_74
#undef local_78
#undef local_7c
#undef local_80
#undef local_84
#undef local_f0
#undef local_f4
#undef local_f8
#undef local_fc
#undef puStack_120
#undef puStack_148
#undef uStack_10a
#undef uStack_110
#undef uStack_114
#undef uStack_118
#undef uStack_11c
#undef uStack_124
#undef uStack_128
#undef uStack_141
#undef uStack_48
#undef uStack_4c
#undef uStack_86
#undef uStack_88
#undef uStack_8d
#undef uStack_8e
#undef uStack_8f
#undef uStack_90
#undef uStack_94
#undef uStack_ec

#endif


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
  iVar2 = (*g_pSvcMain->pFopen)(param_1,&DAT_004ddd78);
  if (iVar2 != 0) {
    strncpy(auStack_10,&DAT_004e78b0,3);
    (*g_pSvcMain->pFwrite)(iVar2,auStack_10,3);
    strncpy(auStack_d,&DAT_004e78ac,3);
    (*g_pSvcMain->pFwrite)(iVar2,auStack_d,3);
    uStack_a = *(undefined2 *)(**(int **)(param_2 + 0x78) + 0xc);
    uStack_8 = *(undefined2 *)(**(int **)(param_2 + 0x78) + 0x10);
    uStack_6 = 0xf7;
    uStack_5 = 0;
    auStack_4[0] = 0;
    (*g_pSvcMain->pFwrite)(iVar2,&uStack_a,2);
    (*g_pSvcMain->pFwrite)(iVar2,&uStack_8,2);
    (*g_pSvcMain->pFwrite)(iVar2,&uStack_6,1);
    (*g_pSvcMain->pFwrite)(iVar2,&uStack_5,1);
    (*g_pSvcMain->pFwrite)(iVar2,auStack_4,1);
    (*g_pSvcMain->pFwrite)(iVar2,*(undefined4 *)(param_2 + 0x60),0x300);
    auStack_1c[0] = 0x2c;
    uStack_1a = 0;
    uStack_18 = 0;
    uStack_16 = *(undefined2 *)(**(int **)(param_2 + 0x78) + 0xc);
    uStack_14 = *(undefined2 *)(**(int **)(param_2 + 0x78) + 0x10);
    abStack_12[0] = 0;
    (*g_pSvcMain->pFwrite)(iVar2,auStack_1c,1);
    (*g_pSvcMain->pFwrite)(iVar2,&uStack_1a,2);
    (*g_pSvcMain->pFwrite)(iVar2,&uStack_18,2);
    (*g_pSvcMain->pFwrite)(iVar2,&uStack_16,2);
    (*g_pSvcMain->pFwrite)(iVar2,&uStack_14,2);
    (*g_pSvcMain->pFwrite)(iVar2,abStack_12,1);
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
                 (*g_pSvcMain->pAlloc)
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
                (*g_pSvcMain->pFree)(puVar4);
                (*g_pSvcMain->pFclose)(iVar2);
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
      iVar5 = (*g_pSvcMain->pFwrite)(iVar2,puVar4,1);
      if (iVar5 == 1) {
        *(undefined1 *)puVar4 = 0x3b;
        iVar5 = (*g_pSvcMain->pFwrite)(iVar2,puVar4,1);
        if (iVar5 == 1) {
          (*g_pSvcMain->pFree)(puVar4);
          (*g_pSvcMain->pFclose)(iVar2);
          return 1;
        }
      }
    }
  }
  (*g_pSvcMain->pFclose)(iVar2);
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
    iVar1 = (*g_pSvcMain->pFread)(param_1,&DAT_008155f0,1);
    if (iVar1 != 1) {
      return 0xffff;
    }
    iVar1 = (*g_pSvcMain->pFread)(param_1,&DAT_0080cbf8,(int)DAT_008155f0);
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
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

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
  iVar1 = (*g_pSvcMain->pFwrite)(param_1,&param_2,1);
  if (iVar1 != 1) {
    return 1;
  }
  stdGif_LzwWriteCode(param_1,CONCAT22(extraout_var,DAT_00811b2c));
  return _DAT_008155f8 & 0xffff;
}

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
  iVar1 = (*g_pSvcMain->pFwrite)(param_1,&DAT_0080cbf8,param_2 + 1);
  if (iVar1 != param_2 + 1) {
    _DAT_008155f8 = _DAT_008155f8 + 1;
  }
  return;
}
