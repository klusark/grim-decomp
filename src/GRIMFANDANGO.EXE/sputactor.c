/* GRIMFANDANGO.EXE :: sputactor.c
 * functions 0x0048e2c0 .. 0x0048ecd0 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048e2c0  sputActor_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputActor_Initialize(uint param_1,undefined4 *param_2)

{
  UINT_008ca32c = param_1;
  *param_2 = sputActor_Initialize;
  param_2[1] = FUN_00490e60;
  param_2[2] = FUN_00490e80;
  param_2[3] = FUN_00490ef0;
  param_2[4] = FUN_0048e330;
  param_2[5] = FUN_0048ecd0;
  param_2[6] = 0;
  param_2[7] = 0;
  g_pTalkingActors = (void *)0x0;
  UINT_008ca768 = 1;
  UINT_008ca314 = 0;
  _DAT_008ca318 = 0;
  _DAT_008ca31c = 0;
  return 0;
}

/* ---- 0x0048e330  FUN_0048e330 ---- */
undefined4 FUN_0048e330(code *param_1)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *actor;
  undefined4 *puVar1;
  int *piVar2;
  void *pvVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  #define iStack_a8 (*(int *)(_frame + (0xc0 - 0xa8)))
  #define iStack_a4 (*(int *)(_frame + (0xc0 - 0xa4)))
  #define iStack_a0 (*(int *)(_frame + (0xc0 - 0xa0)))
  #define iStack_9c (*(int *)(_frame + (0xc0 - 0x9c)))
  #define iStack_98 (*(int *)(_frame + (0xc0 - 0x98)))
  #define iStack_94 (*(int *)(_frame + (0xc0 - 0x94)))
  #define iStack_90 (*(int *)(_frame + (0xc0 - 0x90)))
  #define iStack_8c (*(int *)(_frame + (0xc0 - 0x8c)))
  #define uStack_88 (*(uint *)(_frame + (0xc0 - 0x88)))
  #define local_84 (*(uint *)(_frame + (0xc0 - 0x84)))
  #define aiStack_80 (*(int (*)[32])(_frame + (0xc0 - 0x80)))
  
  local_84 = g_nActorCount;
  (*param_1)(&g_nActorCapacity,4);
  (*param_1)(&local_84,4);
  iStack_94 = 0;
  pvVar3 = g_pActorTable;
  if (0 < g_nActorCapacity) {
    iStack_98 = 0;
    do {
      actor = (int *)((int)pvVar3 + iStack_98);
      if (*(int *)((int)pvVar3 + iStack_98 + 0x9c) != 0) {
        iStack_8c = ((int)actor - (int)pvVar3) / 0xa8;
        (*param_1)(&iStack_8c,4);
        (*param_1)(*actor + 4,4);
        (*param_1)(actor + 1,4);
        (*param_1)(actor + 2,4);
        (*param_1)(actor + 3,4);
        (*param_1)(actor + 4,4);
        (*param_1)(actor + 5,4);
        (*param_1)(actor + 6,4);
        (*param_1)(actor + 7,4);
        (*param_1)(actor + 8,4);
        (*param_1)(actor + 9,4);
        (*param_1)(actor + 10,4);
        (*param_1)(actor + 0xb,4);
        (*param_1)(actor + 0xc,4);
        (*param_1)(actor + 0xd,4);
        (*param_1)(actor + 0xe,4);
        (*param_1)(actor + 0xf,4);
        (*param_1)(actor + 0x10,4);
        (*param_1)(actor + 0x11,4);
        (*param_1)(actor + 0x12,4);
        (*param_1)(actor + 0x13,4);
        (*param_1)(actor + 0x14,4);
        (*param_1)(actor + 0x15,4);
        (*param_1)(actor + 0x16,4);
        (*param_1)(actor + 0x17,4);
        (*param_1)(actor + 0x18,4);
        (*param_1)(actor + 0x19,4);
        (*param_1)(actor + 0x1a,4);
        (*param_1)(actor + 0x1b,4);
        (*param_1)(actor + 0x1c,4);
        (*param_1)(actor + 0x1d,4);
        (*param_1)(actor + 0x1e,4);
        (*param_1)(actor + 0x1f,0x20);
        uStack_88 = (uint)(actor[0x29] != 0);
        (*param_1)(&uStack_88,4);
        iStack_9c = Actor_CountCostumes(actor);
        (*param_1)(&iStack_9c,4);
        iVar6 = actor[0x28];
        if (-1 < iStack_9c + -1) {
          piVar4 = aiStack_80 + iStack_9c + -1;
          iVar5 = iStack_9c;
          do {
            *piVar4 = iVar6;
            iVar6 = *(int *)(iVar6 + 0xb0);
            piVar4 = piVar4 + -1;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
        }
        iStack_a8 = 0;
        if (0 < iStack_9c) {
          piVar4 = aiStack_80;
          do {
            puVar1 = (undefined4 *)*piVar4;
            (*param_1)(puVar1,4);
            (*param_1)(puVar1 + 3,0xc);
            (*param_1)(puVar1 + 6,4);
            (*param_1)(puVar1 + 7,4);
            (*param_1)(puVar1 + 8,4);
            (*param_1)(puVar1 + 9,4);
            (*param_1)(puVar1 + 10,4);
            (*param_1)(puVar1 + 0xb,4);
            (*param_1)(puVar1 + 0xc,4);
            (*param_1)(puVar1 + 0xd,4);
            (*param_1)(puVar1 + 0xe,0x40);
            (*param_1)(puVar1 + 0x1e,4);
            if (puVar1[0x1f] == 0) {
              (**(code **)(UINT_008ca32c + 0x18))
                        (s_Valid_Ref___pCosNode__rCostume___004e9e1c,
                         s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x1c1);
            }
            (*param_1)(puVar1 + 0x20,4);
            Cos_SaveInstance(*puVar1,param_1);
            iStack_a8 = iStack_a8 + 1;
            piVar4 = piVar4 + 1;
          } while (iStack_a8 < iStack_9c);
        }
        if (actor[0x28] != 0) {
          iStack_a4 = 0;
          for (iVar6 = *(int *)(actor[0x28] + 8); iVar6 != 0; iVar6 = *(int *)(iVar6 + 400)) {
            iStack_a4 = iStack_a4 + 1;
          }
          (*param_1)(&iStack_a4,4);
          for (piVar4 = *(int **)(actor[0x28] + 8); piVar4 != (int *)0x0;
              piVar4 = (int *)piVar4[100]) {
            (*param_1)(piVar4 + 0xe,4);
            (*param_1)(piVar4 + 0xf,4);
            (*param_1)(piVar4 + 0x12,4);
            if (*(int *)piVar4[0x10] == 1) {
              if (*piVar4 == 0) {
                (*g_pSvcMain->pAssertFail)
                          (s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
              }
              (*param_1)(*(undefined4 *)(piVar4[0x10] + 0x2c),*(int *)(piVar4[1] + 0x54) << 2);
            }
            iStack_a0 = 0;
            if ((piVar4[0x10] == 0) || (iVar6 = *(int *)(piVar4[0x10] + 0x14), iVar6 == 0)) {
              (*param_1)(&iStack_a0,4);
            }
            else {
              piVar7 = (int *)(iVar6 + 0x130);
              iVar6 = 6;
              piVar2 = piVar7;
              do {
                if (*piVar2 != 0) {
                  iStack_a0 = iStack_a0 + 1;
                }
                piVar2 = piVar2 + 0x4d;
                iVar6 = iVar6 + -1;
              } while (iVar6 != 0);
              (*param_1)(&iStack_a0,4);
              iStack_a8 = 6;
              do {
                if (*piVar7 != 0) {
                  (*param_1)(*piVar7,0x20);
                  (*param_1)(piVar7 + -0x48,4);
                  (*param_1)(piVar7 + -0x47,4);
                  (*param_1)(piVar7 + -0x4a,4);
                  (*param_1)(piVar7 + -2,4);
                  (*param_1)(piVar7 + -1,4);
                  (*param_1)(piVar7 + -0x44,4);
                  (*param_1)(piVar7 + -0x43,4);
                }
                piVar7 = piVar7 + 0x4d;
                iStack_a8 = iStack_a8 + -1;
              } while (iStack_a8 != 0);
            }
          }
        }
        pvVar3 = g_pActorTable;
        if (actor[0x29] != 0) {
          (*param_1)(actor[0x29],4);
          (*param_1)(actor[0x29] + 4,4);
          (*param_1)(actor[0x29] + 8,4);
          (*param_1)(actor[0x29] + 0xc,4);
          (*param_1)(actor[0x29] + 0x10,4);
          (*param_1)(actor[0x29] + 0x14,4);
          (*param_1)(actor[0x29] + 0x18,4);
          (*param_1)(actor[0x29] + 0x1c,4);
          (*param_1)(actor[0x29] + 0x20,4);
          (*param_1)(actor[0x29] + 0x24,4);
          (*param_1)(actor[0x29] + 0x28,4);
          (*param_1)(actor[0x29] + 0x2c,4);
          (*param_1)(actor[0x29] + 0x30,4);
          (*param_1)(actor[0x29] + 0x34,4);
          (*param_1)(actor[0x29] + 0x38,4);
          (*param_1)(actor[0x29] + 0x3c,4);
          (*param_1)(actor[0x29] + 0x40,4);
          (*param_1)(actor[0x29] + 0x44,4);
          iVar6 = 0;
          do {
            (*param_1)(iVar6 + 0x48 + actor[0x29],4);
            (*param_1)(iVar6 + 0x4c + actor[0x29],4);
            (*param_1)(iVar6 + 0x50 + actor[0x29],4);
            iVar6 = iVar6 + 0xc;
          } while (iVar6 < 0x168);
          (*param_1)(actor[0x29] + 0x1b0,4);
          (*param_1)(actor[0x29] + 0x1b4,4);
          (*param_1)(actor[0x29] + 0x1b8,4);
          (*param_1)(actor[0x29] + 0x1bc,4);
          (*param_1)(actor[0x29] + 0x1c0,4);
          (*param_1)(actor[0x29] + 0x1c4,4);
          (*param_1)(actor[0x29] + 0x1c8,4);
          (*param_1)(actor[0x29] + 0x1cc,4);
          (*param_1)(actor[0x29] + 0x1d0,0xc);
          (*param_1)(actor[0x29] + 0x1dc,0xf);
          (*param_1)(actor[0x29] + 0x1ec,4);
          (*param_1)(actor[0x29] + 0x1f0,4);
          (*param_1)(actor[0x29] + 500,4);
          (*param_1)(actor[0x29] + 0x3f0,4);
          (*param_1)(actor[0x29] + 0x3f4,4);
          (*param_1)(actor[0x29] + 0x3f8,4);
          (*param_1)(actor[0x29] + 0x3fc,4);
          (*param_1)(actor[0x29] + 0x400,4);
          (*param_1)(actor[0x29] + 0x404,4);
          (*param_1)(actor[0x29] + 0x408,4);
          (*param_1)(actor[0x29] + 0x40c,4);
          (*param_1)(actor[0x29] + 0x410,4);
          (*param_1)(actor[0x29] + 0x414,4);
          (*param_1)(actor[0x29] + 0x418,4);
          (*param_1)(actor[0x29] + 0x41c,4);
          (*param_1)(actor[0x29] + 0x420,4);
          pvVar3 = Set_GetCurrent();
          if (pvVar3 == (void *)0x0) {
            Actor_KillShadows(actor);
          }
          iStack_a8 = 0x1f8;
          do {
            iVar6 = iStack_a8 + actor[0x29];
            iStack_a4 = 0;
            (*param_1)(iVar6,4);
            (*param_1)(iVar6 + 4,4);
            (*param_1)(iVar6 + 8,4);
            (*param_1)(iVar6 + 0xc,4);
            (*param_1)(iVar6 + 0x10,4);
            (*param_1)(iVar6 + 0x14,4);
            (*param_1)(iVar6 + 0x18,4);
            (*param_1)(iVar6 + 0x1c,4);
            (*param_1)(iVar6 + 0x20,4);
            piVar7 = (int *)(iVar6 + 0x24);
            iVar6 = 0xc;
            piVar4 = piVar7;
            do {
              if (*piVar4 != 0) {
                iStack_a4 = iStack_a4 + 1;
              }
              piVar4 = piVar4 + 1;
              iVar6 = iVar6 + -1;
            } while (iVar6 != 0);
            (*param_1)(&iStack_a4,4);
            iVar6 = 0xc;
            do {
              if (*piVar7 != 0) {
                (*param_1)(*piVar7,0x20);
              }
              piVar7 = piVar7 + 1;
              iVar6 = iVar6 + -1;
            } while (iVar6 != 0);
            iStack_a8 = iStack_a8 + 0x54;
            pvVar3 = g_pActorTable;
          } while (iStack_a8 < 0x3f0);
        }
      }
      iStack_94 = iStack_94 + 1;
      iStack_98 = iStack_98 + 0xa8;
    } while (iStack_94 < g_nActorCapacity);
  }
  iStack_90 = -1;
  if (g_pSelectedActor != (void *)0x0) {
    iStack_90 = ((int)g_pSelectedActor - (int)pvVar3) / 0xa8;
  }
  (*param_1)(&iStack_90,4);
  return 0;
}
#undef aiStack_80
#undef iStack_8c
#undef iStack_90
#undef iStack_94
#undef iStack_98
#undef iStack_9c
#undef iStack_a0
#undef iStack_a4
#undef iStack_a8
#undef local_84
#undef uStack_88


/* ---- 0x0048ecd0  FUN_0048ecd0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0048ecd0(code *param_1)

{
  unsigned char _frame[0x180] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *setName;
  void *pvVar1;
  undefined4 *puVar2;
  char *name;
  void *pvVar3;
  void **ppvVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int *piVar11;
  undefined4 *puVar12;
  #define iStack_164 (*(int *)(_frame + (0x180 - 0x164)))
  #define pvStack_160 (*(void **)(_frame + (0x180 - 0x160)))
  #define local_15c (*(int *)(_frame + (0x180 - 0x15c)))
  #define iStack_158 (*(int *)(_frame + (0x180 - 0x158)))
  #define iStack_154 (*(int *)(_frame + (0x180 - 0x154)))
  #define iStack_150 (*(int *)(_frame + (0x180 - 0x150)))
  #define iStack_14c (*(int *)(_frame + (0x180 - 0x14c)))
  #define iStack_148 (*(int *)(_frame + (0x180 - 0x148)))
  #define uStack_144 (*(uint *)(_frame + (0x180 - 0x144)))
  #define iStack_140 (*(int *)(_frame + (0x180 - 0x140)))
  #define iStack_13c (*(int *)(_frame + (0x180 - 0x13c)))
  #define uStack_138 (*(uint *)(_frame + (0x180 - 0x138)))
  #define auStack_134 (*(undefined1 (*)[12])(_frame + (0x180 - 0x134)))
  #define uStack_128 (*(undefined4 *)(_frame + (0x180 - 0x128)))
  #define uStack_124 (*(undefined4 *)(_frame + (0x180 - 0x124)))
  #define uStack_120 (*(undefined4 *)(_frame + (0x180 - 0x120)))
  #define uStack_11c (*(undefined4 *)(_frame + (0x180 - 0x11c)))
  #define uStack_118 (*(undefined4 *)(_frame + (0x180 - 0x118)))
  #define uStack_114 (*(undefined4 *)(_frame + (0x180 - 0x114)))
  #define uStack_110 (*(undefined4 *)(_frame + (0x180 - 0x110)))
  #define uStack_10c (*(undefined4 *)(_frame + (0x180 - 0x10c)))
  #define uStack_108 (*(undefined4 *)(_frame + (0x180 - 0x108)))
  #define uStack_104 (*(undefined4 *)(_frame + (0x180 - 0x104)))
  #define uStack_100 (*(undefined4 *)(_frame + (0x180 - 0x100)))
  #define auStack_fc (*(undefined4 (*)[16])(_frame + (0x180 - 0xfc)))
  #define uStack_bc (*(undefined4 *)(_frame + (0x180 - 0xbc)))
  #define iStack_b8 (*(int *)(_frame + (0x180 - 0xb8)))
  #define auStack_b4 (*(undefined4 (*)[13])(_frame + (0x180 - 0xb4)))
  #define acStack_80 (*(char (*)[32])(_frame + (0x180 - 0x80)))
  #define acStack_60 (*(char (*)[32])(_frame + (0x180 - 0x60)))
  #define auStack_40 (*(undefined4 (*)[16])(_frame + (0x180 - 0x40)))
  
  g_pTalkingActors = (void *)0x0;
  UINT_008ca314 = 0;
  _DAT_008ca318 = 0;
  _DAT_008ca31c = 0;
  iVar9 = 0;
  g_nTalkingActorCount = 0;
  if (0 < g_nActorCapacity) {
    iVar8 = 0;
    do {
      Actor_Destroy((void *)((int)g_pActorTable + iVar8));
      iVar9 = iVar9 + 1;
      iVar8 = iVar8 + 0xa8;
    } while (iVar9 < g_nActorCapacity);
  }
  (*param_1)(&local_15c,4);
  if (g_nActorCapacity < local_15c) {
    g_pActorTable =
         (void *)(**(code **)(UINT_008ca32c + 0x28))
                           (g_pActorTable,local_15c * 0xa8,
                            s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x28a);
    puVar2 = (undefined4 *)((int)g_pActorTable + g_nActorCapacity * 0xa8);
    for (iVar9 = ((local_15c - g_nActorCapacity) * 0x15 & 0x1fffffffU) << 1; iVar9 != 0;
        iVar9 = iVar9 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
      *(undefined1 *)puVar2 = 0;
      puVar2 = (undefined4 *)((int)puVar2 + 1);
    }
    g_nActorCapacity = local_15c;
  }
  (*param_1)(&g_nActorCount,4);
  iStack_150 = 0;
  if (0 < g_nActorCount) {
    do {
      (*param_1)(&iStack_140,4);
      setName = (int *)((int)g_pActorTable + iStack_140 * 0xa8);
      iVar9 = *(int *)((int)g_pActorTable + iStack_140 * 0xa8);
      setName[0x27] = 1;
      if (iVar9 == 0) {
        puVar2 = (undefined4 *)
                 (**(code **)(UINT_008ca32c + 0x20))
                           (0x34,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x29f);
        *setName = (int)puVar2;
        for (iVar9 = 0xd; iVar9 != 0; iVar9 = iVar9 + -1) {
          *puVar2 = 0;
          puVar2 = puVar2 + 1;
        }
      }
      (*param_1)(*setName + 4,4);
      (*param_1)(setName + 1,4);
      (*param_1)(setName + 2,4);
      (*param_1)(setName + 3,4);
      (*param_1)(setName + 4,4);
      (*param_1)(setName + 5,4);
      (*param_1)(setName + 6,4);
      (*param_1)(setName + 7,4);
      (*param_1)(setName + 8,4);
      (*param_1)(setName + 9,4);
      (*param_1)(setName + 10,4);
      (*param_1)(setName + 0xb,4);
      (*param_1)(setName + 0xc,4);
      (*param_1)(setName + 0xd,4);
      setName[0xd] = 0;
      (*param_1)(setName + 0xe,4);
      (*param_1)(setName + 0xf,4);
      (*param_1)(setName + 0x10,4);
      (*param_1)(setName + 0x11,4);
      (*param_1)(setName + 0x12,4);
      (*param_1)(setName + 0x13,4);
      (*param_1)(setName + 0x14,4);
      (*param_1)(setName + 0x15,4);
      (*param_1)(setName + 0x16,4);
      (*param_1)(setName + 0x17,4);
      (*param_1)(setName + 0x18,4);
      (*param_1)(setName + 0x19,4);
      (*param_1)(setName + 0x1a,4);
      (*param_1)(setName + 0x1b,4);
      (*param_1)(setName + 0x1c,4);
      (*param_1)(setName + 0x1d,4);
      (*param_1)(setName + 0x1e,4);
      piVar10 = setName + 0x1f;
      (*param_1)(piVar10,0x20);
      (*param_1)(&iStack_13c,4);
      ResRef_Release(*setName);
      if ((char)*piVar10 != '\0') {
        uVar6 = 0xffffffff;
        do {
          piVar11 = piVar10;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          piVar11 = (int *)((int)piVar10 + 1);
          iVar9 = *piVar10;
          piVar10 = piVar11;
        } while ((char)iVar9 != '\0');
        uVar6 = ~uVar6;
        puVar2 = (undefined4 *)((int)piVar11 - uVar6);
        puVar12 = auStack_40;
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *puVar12 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar12 = puVar12 + 1;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined1 *)puVar12 = *(undefined1 *)puVar2;
          puVar2 = (undefined4 *)((int)puVar2 + 1);
          puVar12 = (undefined4 *)((int)puVar12 + 1);
        }
        *(char *)(setName + 0x1f) = '\0';
        Actor_PutInSet(auStack_40,(char *)setName);
      }
      setName[0x28] = 0;
      (*param_1)(&iStack_148,4);
      iStack_164 = 0;
      if (0 < iStack_148) {
        do {
          (*param_1)(auStack_134,4);
          (*param_1)(&uStack_128,0xc);
          (*param_1)(&uStack_11c,4);
          (*param_1)(&uStack_118,4);
          (*param_1)(&uStack_114,4);
          (*param_1)(&uStack_110,4);
          (*param_1)(&uStack_10c,4);
          (*param_1)(&uStack_108,4);
          (*param_1)(&uStack_104,4);
          (*param_1)(&uStack_100,4);
          (*param_1)(auStack_fc,0x40);
          (*param_1)(&uStack_bc,4);
          (*param_1)(auStack_b4,4);
          ResRef_Release(&iStack_b8);
          if (iStack_b8 == 0) {
            (*g_pSvcMain->pAssertFail)
                      (s_Bad_costume_Reference_004e9e90,s_main_sputResource_h_004e80a8,0xb8);
          }
          name = (char *)CosUtil_PtrFromHandle(auStack_b4[0]);
          if (iStack_164 == 0) {
            Actor_SetCostume(setName,name);
          }
          else {
            Actor_PushCostume(setName,name);
          }
          Cos_RestoreInstance(*(undefined4 *)setName[0x28],param_1);
          *(undefined4 *)(setName[0x28] + 0xc) = uStack_128;
          *(undefined4 *)(setName[0x28] + 0x10) = uStack_124;
          *(undefined4 *)(setName[0x28] + 0x14) = uStack_120;
          *(undefined4 *)(setName[0x28] + 0x18) = uStack_11c;
          *(undefined4 *)(setName[0x28] + 0x1c) = uStack_118;
          *(undefined4 *)(setName[0x28] + 0x20) = uStack_114;
          *(undefined4 *)(setName[0x28] + 0x24) = uStack_110;
          *(undefined4 *)(setName[0x28] + 0x28) = uStack_10c;
          *(undefined4 *)(setName[0x28] + 0x2c) = uStack_108;
          *(undefined4 *)(setName[0x28] + 0x30) = uStack_104;
          *(undefined4 *)(setName[0x28] + 0x34) = uStack_100;
          puVar2 = auStack_fc;
          puVar12 = (undefined4 *)(setName[0x28] + 0x38);
          for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
            *puVar12 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar12 = puVar12 + 1;
          }
          *(undefined4 *)(setName[0x28] + 0x78) = uStack_bc;
          ResRef_Remove(&iStack_b8);
          iStack_164 = iStack_164 + 1;
        } while (iStack_164 < iStack_148);
      }
      if (setName[0x28] != 0) {
        piVar10 = *(int **)(setName[0x28] + 8);
        (*param_1)(&iStack_158,4);
        if (0 < iStack_158) {
          for (; piVar10 != (int *)0x0; piVar10 = (int *)piVar10[100]) {
            (*param_1)(piVar10 + 0xe,4);
            (*param_1)(piVar10 + 0xf,4);
            (*param_1)(piVar10 + 0x12,4);
            if (*(int *)piVar10[0x10] == 1) {
              if (*piVar10 == 0) {
                (*g_pSvcMain->pAssertFail)
                          (s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
              }
              (*param_1)(*(undefined4 *)(piVar10[0x10] + 0x2c),*(int *)(piVar10[1] + 0x54) << 2);
            }
            (*param_1)(&iStack_14c,4);
            iStack_164 = 0;
            if (0 < iStack_14c) {
              do {
                pvStack_160 = *(void **)(piVar10[0x10] + 0x14);
                (*param_1)(acStack_60,0x20);
                pvVar3 = Resource_Load(0x4659454b,acStack_60);
                if (pvVar3 != (void *)0x0) {
                  (*param_1)(&uStack_144,4);
                  (*param_1)(&uStack_138,4);
                  pvVar1 = pvStack_160;
                  uVar6 = rdPuppet_AddTrack(pvStack_160,(uint)pvVar3,uStack_144,uStack_138);
                  (*param_1)((int)pvVar1 + uVar6 * 0x134 + 8,4);
                  (*param_1)((int)pvVar1 + uVar6 * 0x134 + 0x128,4);
                  (*param_1)((int)pvVar1 + uVar6 * 0x134 + 300,4);
                  (*param_1)((int)pvVar1 + uVar6 * 0x134 + 0x20,4);
                  (*param_1)((int)pvVar1 + uVar6 * 0x134 + 0x24,4);
                }
                iStack_164 = iStack_164 + 1;
              } while (iStack_164 < iStack_14c);
            }
            iStack_158 = iStack_158 + -1;
          }
        }
      }
      if (iStack_13c != 0) {
        setName[0x29] = 0;
        Actor_CreateExtra(setName);
        (*param_1)(setName[0x29],4);
        (*param_1)(setName[0x29] + 4,4);
        (*param_1)(setName[0x29] + 8,4);
        (*param_1)(setName[0x29] + 0xc,4);
        (*param_1)(setName[0x29] + 0x10,4);
        (*param_1)(setName[0x29] + 0x14,4);
        (*param_1)(setName[0x29] + 0x18,4);
        (*param_1)(setName[0x29] + 0x1c,4);
        (*param_1)(setName[0x29] + 0x20,4);
        (*param_1)(setName[0x29] + 0x24,4);
        (*param_1)(setName[0x29] + 0x28,4);
        (*param_1)(setName[0x29] + 0x2c,4);
        (*param_1)(setName[0x29] + 0x30,4);
        (*param_1)(setName[0x29] + 0x34,4);
        (*param_1)(setName[0x29] + 0x38,4);
        (*param_1)(setName[0x29] + 0x3c,4);
        (*param_1)(setName[0x29] + 0x40,4);
        (*param_1)(setName[0x29] + 0x44,4);
        iVar9 = 0;
        do {
          (*param_1)(iVar9 + 0x48 + setName[0x29],4);
          (*param_1)(iVar9 + 0x4c + setName[0x29],4);
          (*param_1)(iVar9 + 0x50 + setName[0x29],4);
          iVar9 = iVar9 + 0xc;
        } while (iVar9 < 0x168);
        (*param_1)(setName[0x29] + 0x1b0,4);
        (*param_1)(setName[0x29] + 0x1b4,4);
        (*param_1)(setName[0x29] + 0x1b8,4);
        (*param_1)(setName[0x29] + 0x1bc,4);
        (*param_1)(setName[0x29] + 0x1c0,4);
        (*param_1)(setName[0x29] + 0x1c4,4);
        (*param_1)(setName[0x29] + 0x1c8,4);
        (*param_1)(setName[0x29] + 0x1cc,4);
        (*param_1)(setName[0x29] + 0x1d0,0xc);
        (*param_1)(setName[0x29] + 0x1dc,0xf);
        (*param_1)(setName[0x29] + 0x1ec,4);
        (*param_1)(setName[0x29] + 0x1f0,4);
        (*param_1)(setName[0x29] + 500,4);
        (*param_1)(setName[0x29] + 0x3f0,4);
        (*param_1)(setName[0x29] + 0x3f4,4);
        (*param_1)(setName[0x29] + 0x3f8,4);
        (*param_1)(setName[0x29] + 0x3fc,4);
        (*param_1)(setName[0x29] + 0x400,4);
        (*param_1)(setName[0x29] + 0x404,4);
        (*param_1)(setName[0x29] + 0x408,4);
        (*param_1)(setName[0x29] + 0x40c,4);
        (*param_1)(setName[0x29] + 0x410,4);
        (*param_1)(setName[0x29] + 0x414,4);
        (*param_1)(setName[0x29] + 0x418,4);
        (*param_1)(setName[0x29] + 0x41c,4);
        (*param_1)(setName[0x29] + 0x420,4);
        if (*(int *)(setName[0x29] + 0x1b4) != 0) {
          *(undefined4 *)(setName[0x29] + 0x1b4) = 0;
          Actor_CreateWalker(setName,1);
          if (*(int *)(setName[0x29] + 0x1b8) != 0) {
            Walker_ReattachToSet(*(void **)(setName[0x29] + 0x1b4));
          }
        }
        if (*(int *)(setName[0x29] + 0x1c4) != 0) {
          iVar9 = 0;
          ppvVar4 = &g_pTalkingActors;
          do {
            if (*ppvVar4 == (void *)0x0) {
              (&g_pTalkingActors)[iVar9] = setName;
              g_nTalkingActorCount = g_nTalkingActorCount + 1;
              break;
            }
            ppvVar4 = ppvVar4 + 1;
            iVar9 = iVar9 + 1;
          } while ((int)ppvVar4 < IMG_ADDR(0x008ca320));
        }
        if (*(int *)(setName[0x29] + 0x1ec) != 0) {
          uVar5 = TextObject_FindBySelf(*(int *)(setName[0x29] + 0x1ec));
          *(undefined4 *)(setName[0x29] + 0x1ec) = uVar5;
        }
        Actor_KillShadows(setName);
        pvStack_160 = (void *)0x1f8;
        do {
          iVar8 = (int)pvStack_160 + setName[0x29];
          iVar9 = 0;
          iStack_164 = 0;
          (*param_1)(iVar8,4);
          (*param_1)(iVar8 + 4,4);
          (*param_1)(iVar8 + 8,4);
          (*param_1)(iVar8 + 0xc,4);
          (*param_1)(iVar8 + 0x10,4);
          (*param_1)(iVar8 + 0x14,4);
          (*param_1)(iVar8 + 0x18,4);
          (*param_1)(iVar8 + 0x1c,4);
          (*param_1)(iVar8 + 0x20,4);
          (*param_1)(&iStack_164,4);
          if (0xb < iStack_164) {
            (**(code **)(UINT_008ca32c + 0x18))
                      (s_tot_clips___MAX_SHADOW_CLIPS_004e9e70,
                       s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x3a5);
          }
          if (0 < iStack_164) {
            puVar2 = (undefined4 *)(iVar8 + 0x24);
            do {
              acStack_80[0] = '\0';
              (*param_1)(acStack_80,0x20);
              pvVar3 = Sector_FindByName(acStack_80);
              *puVar2 = pvVar3;
              iVar9 = iVar9 + 1;
              puVar2 = puVar2 + 1;
            } while (iVar9 < iStack_164);
          }
          pvStack_160 = (void *)((int)pvStack_160 + 0x54);
        } while ((int)pvStack_160 < 0x3f0);
      }
      iStack_150 = iStack_150 + 1;
    } while (iStack_150 < g_nActorCount);
  }
  iStack_154 = -1;
  g_pSelectedActor = (void *)0x0;
  (*param_1)(&iStack_154,4);
  if (iStack_154 != -1) {
    g_pSelectedActor = (void *)((int)g_pActorTable + iStack_154 * 0xa8);
  }
  return 0;
}
#undef acStack_60
#undef acStack_80
#undef auStack_134
#undef auStack_40
#undef auStack_b4
#undef auStack_fc
#undef iStack_13c
#undef iStack_140
#undef iStack_148
#undef iStack_14c
#undef iStack_150
#undef iStack_154
#undef iStack_158
#undef iStack_164
#undef iStack_b8
#undef local_15c
#undef pvStack_160
#undef uStack_100
#undef uStack_104
#undef uStack_108
#undef uStack_10c
#undef uStack_110
#undef uStack_114
#undef uStack_118
#undef uStack_11c
#undef uStack_120
#undef uStack_124
#undef uStack_128
#undef uStack_138
#undef uStack_144
#undef uStack_bc

