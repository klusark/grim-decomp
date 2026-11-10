/* GRIMFANDANGO.EXE :: stdpic.c
 * functions 0x0047d280 .. 0x0047d2d0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047d280  stdPic_Load ---- */
/* stdBitmap_LoadFile loader for '.pic' (wrapper of stdPic_LoadInto, allocation string stdPic.c) */

uint stdPic_Load(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (*g_pStd_HS->pAlloc)(0x7c,s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77cc + 4);
  if (uVar1 == 0) {
    return 0;
  }
  iVar2 = stdPic_LoadEntry(param_1,uVar1,param_2,param_3);
  return -(uint)(iVar2 != 0) & uVar1;
}

/* ---- 0x0047d2d0  stdPic_LoadEntry ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Decoder of '.pic' files (allocation string stdPic.c)
   Ported to C (build/overrides_big_stdpic_loadinto.c): differential test on generated inputs, 0
   differences (docs/notes/big_stdpic_loadinto.md). Original name stdPic_LoadEntry (the remaster's
   GrimFandango (Linux): the only unmatched callee of stdPic_Load; 1 matched neighbours agree, 0
   disagree); was stdPic_LoadInto. */

undefined4 stdPic_LoadEntry(char *param_1,undefined4 *param_2,int param_3,int param_4)

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
  iVar5 = (*g_pStd_HS->pFopen)(param_1,&DAT_004ddb18);
  if (iVar5 == 0) {
    return 0;
  }
  iVar6 = (*g_pStd_HS->pFread)(iVar5,&uStack_ec,0x68);
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
    iVar6 = (*g_pStd_HS->pFread)(iVar5,&cStack_10c,4);
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
          pcVar8 = stdFileFromPath(param_1);
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
          iVar6 = (*g_pStd_HS->pAlloc)
                            (4,s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77d0 + 0x6d);
          param_2[0x1e] = iVar6;
          if (iVar6 == 0) {
            (*g_pStd_HS->pAssertFail)
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
          pvVar9 = stdDisplay_VBufferNew(&uStack_4c,param_3,param_4,0);
          *(void **)param_2[0x1e] = pvVar9;
          if (*(int *)param_2[0x1e] == 0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Unable_to_allocate_memory__004e76d4,
                       s_C__grimjedi_Libs_Std_General_std_004e77d8,DAT_004e77d0 + 0x76);
          }
          iVar6 = stdDisplay_VBufferLock(*(void **)param_2[0x1e]);
          if (iVar6 == 0) {
            (*g_pStd_HS->pAssertFail)
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
                          (*g_pStd_HS->pFread)(iVar5,(int)puVar15 + -2,uStack_128);
                        }
                        if (iStack_138 == iVar6) {
                          (*g_pStd_HS->pFread)(iVar5,(int)puVar15 + -1,uStack_118);
                        }
                        if (iStack_134 == iVar6) {
                          (*g_pStd_HS->pFread)(iVar5,puVar15,uStack_11c);
                        }
                        if (iStack_130 == iVar6) {
                          (*g_pStd_HS->pFread)(iVar5,auStack_100,uStack_124);
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
                        (*g_pStd_HS->pFread)(iVar5,&bStack_14b,1);
                        if (bStack_14b < 0x80) {
                          if (bStack_14b != 0xff) {
                            puVar15 = (undefined4 *)(iVar13 * 3 + 2 + iStack_13c);
                            do {
                              if (iStack_140 == iVar6) {
                                (*g_pStd_HS->pFread)(iVar5,(int)puVar15 + -2,uStack_128);
                              }
                              if (iStack_138 == iVar6) {
                                (*g_pStd_HS->pFread)(iVar5,(int)puVar15 + -1,uStack_118);
                              }
                              if (iStack_134 == iVar6) {
                                (*g_pStd_HS->pFread)(iVar5,puVar15,uStack_11c);
                              }
                              if (iStack_130 == iVar6) {
                                (*g_pStd_HS->pFread)(iVar5,auStack_100,uStack_124);
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
                            (*g_pStd_HS->pFread)(iVar5,&puStack_148,2);
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
                            (*g_pStd_HS->pFread)(iVar5,&bStack_14a,uStack_128);
                          }
                          if (iStack_138 == iVar6) {
                            (*g_pStd_HS->pFread)(iVar5,&bStack_149,uStack_118);
                          }
                          if (iStack_134 == iVar6) {
                            (*g_pStd_HS->pFread)(iVar5,&uStack_141,uStack_11c);
                          }
                          if (iStack_130 == iVar6) {
                            (*g_pStd_HS->pFread)(iVar5,auStack_100,uStack_124);
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
          stdDisplay_VBufferUnlock(*(void **)param_2[0x1e]);
          (*g_pStd_HS->pFclose)(iVar5);
          return 1;
        }
        iVar6 = (*g_pStd_HS->pFread)(iVar5,&cStack_10c,4);
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

