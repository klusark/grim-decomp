/* GRIMFANDANGO.EXE :: collision.c
 * functions 0x004922d0 .. 0x00494100 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004922d0  Collision_PushOutOfBox ---- */
void Collision_PushOutOfBox
               (float *param_1,float param_2,float param_3,float param_4,float param_5,float param_6
               ,float param_7,float *param_8,float *param_9)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  local_c = *param_1 - *param_9;
  local_8 = param_1[1] - param_9[1];
  local_4 = param_1[2] - param_9[2];
  Vec3_TransformTo(&local_18,&local_c,param_8);
  if ((((param_4 < local_10) && (param_3 < local_14)) && (local_14 < param_6)) &&
     (((param_2 < local_18 && (local_18 < param_5)) && (local_10 < param_7)))) {
    fVar1 = 3.4028235e+38;
    if (local_14 < param_6) {
      fVar2 = param_6 - local_14;
      if (fVar2 < 0.0) {
        fVar2 = -fVar2;
      }
      fVar1 = 3.4028235e+38;
      if (fVar2 < 3.4028235e+38) {
        local_8 = param_6 - -0.01;
        local_c = local_18;
        local_4 = local_10;
        fVar1 = fVar2;
      }
    }
    if (param_3 < local_14) {
      fVar2 = param_3 - local_14;
      if (fVar2 < 0.0) {
        fVar2 = -fVar2;
      }
      if (fVar2 < fVar1) {
        local_8 = param_3 - 0.01;
        local_c = local_18;
        local_4 = local_10;
        fVar1 = fVar2;
      }
    }
    if (local_18 < param_5) {
      fVar2 = param_5 - local_18;
      if (fVar2 < 0.0) {
        fVar2 = -fVar2;
      }
      if (fVar2 < fVar1) {
        local_c = param_5 - -0.01;
        local_8 = local_14;
        local_4 = local_10;
        fVar1 = fVar2;
      }
    }
    if (param_2 < local_18) {
      local_18 = param_2 - local_18;
      if (local_18 < 0.0) {
        local_18 = -local_18;
      }
      if (local_18 < fVar1) {
        local_c = param_2 - 0.01;
        local_8 = local_14;
        local_4 = local_10;
      }
    }
    Vec3_Sub(param_1,&local_c,param_8);
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00492510  Collision_PointInBox ---- */
undefined4 Collision_PointInBox(float *param_1,float *param_2,undefined4 param_3)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  float **ppfVar4;
  float fStack00000010;
  float fStack00000014;
  float fStack00000018;
  undefined4 in_stack_00000028;
  float *in_stack_0000002c;
  #define apfStack_38 (*(float *(*)[5])(_frame + (0x50 - 0x38)))
  #define pfStack_24 (*(float **)(_frame + (0x50 - 0x24)))
  #define iStack_20 (*(int *)(_frame + (0x50 - 0x20)))
  #define local_c (*(float *)(_frame + (0x50 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x50 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x50 - 0x4)))
  
  local_c = *in_stack_0000002c + *param_1;
  iStack_20 = in_stack_00000028;
  fStack00000010 = *in_stack_0000002c + *param_2;
  local_8 = param_1[1] + in_stack_0000002c[1];
  fStack00000014 = param_2[1] + in_stack_0000002c[1];
  local_4 = param_1[2] + in_stack_0000002c[2];
  fStack00000018 = param_2[2] + in_stack_0000002c[2];
  puVar3 = &STACK0X(0x00000010);
  ppfVar4 = apfStack_38;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *ppfVar4 = (float *)*puVar3;
    puVar3 = puVar3 + 1;
    ppfVar4 = ppfVar4 + 1;
  }
  iStack_20 = ((code *)Collision_SegmentHitsBox)(&local_c,&STACK0X(0x00000010),param_3);
  if (iStack_20 == 0) {
    pfStack_24 = param_2;
    apfStack_38[4] = param_1;
    apfStack_38[3] = (float *)0x4925a6;
    uVar1 = ((code *)Planner_PlanPath)();
    return uVar1;
  }
  return 0;
}
#undef apfStack_38
#undef iStack_20
#undef local_4
#undef local_8
#undef local_c
#undef pfStack_24


/* ---- 0x004925c0  Collision_BoxCorners ---- */
/* Computes the four detour points around an actor's collision box */

void Collision_BoxCorners(int param_1,float param_2,float *param_3,float param_4,float *param_5)

{
  int iVar1;
  float *pfVar2;
  
  if (0.999 <= param_3[8]) {
    *param_5 = *(float *)(param_1 + 0x60) - param_2;
    param_5[1] = *(float *)(param_1 + 100) - param_2;
    param_5[2] = *(float *)(param_1 + 0x68);
    pfVar2 = param_5 + 0xc;
    iVar1 = 4;
    param_5[3] = param_2 + *(float *)(param_1 + 0x6c);
    param_5[4] = *(float *)(param_1 + 100) - param_2;
    param_5[5] = *(float *)(param_1 + 0x68);
    param_5[6] = param_2 + *(float *)(param_1 + 0x6c);
    param_5[7] = param_2 + *(float *)(param_1 + 0x70);
    param_5[8] = *(float *)(param_1 + 0x68);
    param_5[9] = *(float *)(param_1 + 0x60) - param_2;
    param_5[10] = param_2 + *(float *)(param_1 + 0x70);
    param_5[0xb] = *(float *)(param_1 + 0x68);
    do {
      Vec3_Rotate3x3(param_5,param_3);
      param_5[2] = param_4;
      *pfVar2 = 1.4013e-45;
      pfVar2 = pfVar2 + 1;
      param_5 = param_5 + 3;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}

/* ---- 0x00492680  Collision_SegmentHitsBox ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Walker_AvoidActorPath: does the path segment pass through the other actor's collision box */

undefined4
Collision_SegmentHitsBox
          (float *param_1,float *param_2,float *param_3,float param_4,float param_5,
          undefined4 param_6,float param_7,float param_8,undefined4 param_9,float *param_10)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  #define local_24 (*(float *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(float *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(float *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x40 - 0x4)))
  
  local_18 = *param_1 - *param_3;
  local_14 = param_1[1] - param_3[1];
  local_10 = param_1[2] - param_3[2];
  Vec3_TransformTo(&local_24,&local_18,param_10);
  local_18 = *param_2 - *param_3;
  local_14 = param_2[1] - param_3[1];
  local_10 = param_2[2] - param_3[2];
  Vec3_TransformTo(&local_c,&local_18,param_10);
  fVar2 = local_c - local_24;
  fVar3 = local_8 - local_20;
  local_4 = local_4 - local_1c;
  if (((param_8 < local_20) && (local_8 < param_8)) &&
     (fVar1 = (param_8 - local_20) / fVar3, fVar1 < 1.0)) {
    fVar4 = fVar1 * fVar2 + local_24;
    if ((param_4 < fVar4) &&
       (fVar5 = fVar1 * fVar3 + local_20, fVar6 = fVar1 * local_4 + local_1c, fVar4 < param_7))
    goto LAB_00492801;
  }
  fVar1 = 1.0;
  fVar4 = _DAT_008ca320;
  fVar5 = _DAT_008ca324;
  fVar6 = _DAT_008ca328;
LAB_00492801:
  _DAT_008ca328 = fVar6;
  _DAT_008ca324 = fVar5;
  _DAT_008ca320 = fVar4;
  if (((local_20 < param_5) && (param_5 < local_8)) &&
     (fVar4 = (param_5 - local_20) / fVar3, fVar4 < fVar1)) {
    fVar5 = fVar4 * fVar2 + local_24;
    if ((param_4 < fVar5) && (fVar5 < param_7)) {
      fVar1 = fVar4;
      _DAT_008ca320 = fVar5;
      _DAT_008ca324 = fVar4 * fVar3 + local_20;
      _DAT_008ca328 = fVar4 * local_4 + local_1c;
    }
  }
  if (((param_7 < local_24) && (local_c < param_7)) &&
     (fVar4 = (param_7 - local_24) / fVar2, fVar4 < fVar1)) {
    fVar5 = fVar4 * fVar3 + local_20;
    if ((param_5 < fVar5) && (fVar5 < param_8)) {
      fVar1 = fVar4;
      _DAT_008ca320 = fVar4 * fVar2 + local_24;
      _DAT_008ca324 = fVar5;
      _DAT_008ca328 = fVar4 * local_4 + local_1c;
    }
  }
  if (((local_24 < param_4) && (param_4 < local_c)) &&
     (fVar4 = (param_4 - local_24) / fVar2, fVar4 < fVar1)) {
    local_20 = fVar4 * fVar3 + local_20;
    if ((param_5 < local_20) && (local_20 < param_8)) {
      fVar1 = fVar4;
      _DAT_008ca320 = fVar4 * fVar2 + local_24;
      _DAT_008ca324 = local_20;
      _DAT_008ca328 = fVar4 * local_4 + local_1c;
    }
  }
  if (fVar1 == 1.0) {
    return 0;
  }
  return 1;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00492a50  Collision_PickDetour ---- */
/* Chooses the detour corner that keeps the path shortest */

int Collision_PickDetour(float *param_1,float *param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  iVar4 = -1;
  local_4 = 3.4028235e+38;
  iVar3 = 0;
  pfVar2 = (float *)(param_3 + 8);
  piVar5 = (int *)(param_3 + 0x30);
  do {
    if ((*piVar5 != 0) &&
       (fVar1 = (pfVar2[-2] - *param_2) * (pfVar2[-2] - *param_2) +
                (*pfVar2 - param_2[2]) * (*pfVar2 - param_2[2]) +
                (pfVar2[-1] - param_2[1]) * (pfVar2[-1] - param_2[1]) +
                (param_1[2] - *pfVar2) * (param_1[2] - *pfVar2) +
                (param_1[1] - pfVar2[-1]) * (param_1[1] - pfVar2[-1]) +
                (*param_1 - pfVar2[-2]) * (*param_1 - pfVar2[-2]), fVar1 < local_4)) {
      iVar4 = iVar3;
      local_4 = fVar1;
    }
    iVar3 = iVar3 + 1;
    piVar5 = piVar5 + 1;
    pfVar2 = pfVar2 + 3;
  } while (iVar3 < 4);
  return iVar4;
}
#undef local_4


/* ---- 0x004939a0  Collision_UpdateMovedActors ---- */
undefined4 Collision_UpdateMovedActors(void)

{
  void *pvVar1;
  int iVar2;
  void **ppvVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  
  iVar4 = 0;
  if (0 < g_nDrawableActorCount) {
    ppvVar3 = &g_pDrawableActors;
    do {
      pvVar1 = *ppvVar3;
      iVar2 = 0xc;
      bVar7 = true;
      pcVar5 = (char *)((int)pvVar1 + 0xc);
      pcVar6 = (char *)((int)pvVar1 + 0x18);
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar7 = *pcVar5 == *pcVar6;
        pcVar5 = pcVar5 + 1;
        pcVar6 = pcVar6 + 1;
      } while (bVar7);
      if (!bVar7) {
        Collision_TestActorAgainstOthers(pvVar1);
      }
      iVar4 = iVar4 + 1;
      ppvVar3 = ppvVar3 + 1;
    } while (iVar4 < g_nDrawableActorCount);
  }
  return 1;
}

/* ---- 0x004939f0  Collision_TestActorAgainstOthers ---- */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Collision_TestActorAgainstOthers(void *param_1)

{
  unsigned char _frame[0xf0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  byte bVar2;
  void *actor;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  float *pfVar8;
  int iVar9;
  float **ppfVar10;
  #define apfStack_e0 (*(float *(*)[3])(_frame + (0xf0 - 0xe0)))
  #define pvStack_d4 (*(void **)(_frame + (0xf0 - 0xd4)))
  #define pvStack_d0 (*(void **)(_frame + (0xf0 - 0xd0)))
  #define local_a4 (*(float *)(_frame + (0xf0 - 0xa4)))
  #define local_a0 (*(float *)(_frame + (0xf0 - 0xa0)))
  #define local_9c (*(float *)(_frame + (0xf0 - 0x9c)))
  #define local_98 (*(float *)(_frame + (0xf0 - 0x98)))
  #define local_94 (*(float *)(_frame + (0xf0 - 0x94)))
  #define local_90 (*(float *)(_frame + (0xf0 - 0x90)))
  #define local_8c (*(float *)(_frame + (0xf0 - 0x8c)))
  #define local_88 (*(float *)(_frame + (0xf0 - 0x88)))
  #define local_84 (*(float *)(_frame + (0xf0 - 0x84)))
  #define local_80 (*(float *)(_frame + (0xf0 - 0x80)))
  #define local_7c (*(float *)(_frame + (0xf0 - 0x7c)))
  #define local_78 (*(float *)(_frame + (0xf0 - 0x78)))
  #define local_74 (*(float *)(_frame + (0xf0 - 0x74)))
  #define local_70 (*(void ***)(_frame + (0xf0 - 0x70)))
  #define local_6c (*(float *)(_frame + (0xf0 - 0x6c)))
  #define local_68 (*(float *)(_frame + (0xf0 - 0x68)))
  #define local_64 (*(float *)(_frame + (0xf0 - 0x64)))
  #define local_60 (*(float *)(_frame + (0xf0 - 0x60)))
  #define local_5c (*(float *)(_frame + (0xf0 - 0x5c)))
  #define local_58 (*(float *)(_frame + (0xf0 - 0x58)))
  #define local_54 (*(int *)(_frame + (0xf0 - 0x54)))
  #define local_50 (*(float *)(_frame + (0xf0 - 0x50)))
  #define local_4c (*(float *)(_frame + (0xf0 - 0x4c)))
  #define local_48 (*(float *)(_frame + (0xf0 - 0x48)))
  #define local_44 (*(float *)(_frame + (0xf0 - 0x44)))
  #define local_40 (*(float *)(_frame + (0xf0 - 0x40)))
  #define local_3c (*(float (*)[4])(_frame + (0xf0 - 0x3c)))
  #define local_2c (*(float *)(_frame + (0xf0 - 0x2c)))
  #define local_28 (*(float *)(_frame + (0xf0 - 0x28)))
  #define local_24 (*(float *)(_frame + (0xf0 - 0x24)))
  #define local_20 (*(float *)(_frame + (0xf0 - 0x20)))
  #define local_1c (*(float *)(_frame + (0xf0 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0xf0 - 0x18)))
  #define local_14 (*(float *)(_frame + (0xf0 - 0x14)))
  #define local_10 (*(float *)(_frame + (0xf0 - 0x10)))
  #define local_c (*(undefined4 *)(_frame + (0xf0 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0xf0 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0xf0 - 0x4)))
  
  iVar9 = *(int *)(*(int *)(*(int *)((int)param_1 + 0xa0) + 4) + 4);
  Actor_GetFrame(param_1);
  Vec3_Copy(&local_98,(float *)(iVar9 + 0x78));
  local_6c = local_98 + *(float *)((int)param_1 + 0xc);
  local_54 = 0;
  local_68 = *(float *)((int)param_1 + 0x10) + local_94;
  local_64 = *(float *)((int)param_1 + 0x14) + local_90;
  fVar4 = *(float *)(iVar9 + 0x5c) * *(float *)(*(int *)((int)param_1 + 0xa4) + 0x3f4);
  if (0 < g_nDrawableActorCount) {
    local_70 = &g_pDrawableActors;
    do {
      actor = *local_70;
      if (((actor != param_1) && (*(int *)((int)actor + 0xa4) != 0)) &&
         (*(int *)(*(int *)((int)actor + 0xa4) + 0x3f0) != 0)) {
        iVar9 = *(int *)(*(int *)(*(int *)((int)actor + 0xa0) + 4) + 4);
        pfVar8 = (float *)(iVar9 + 0x78);
        pfVar7 = Actor_GetFrame(actor);
        pvStack_d0 = (void *)0x493ac7;
        Vec3_Sub(&local_60,pfVar8,pfVar7);
        local_4c = local_6c - local_60;
        local_50 = local_68 - local_5c;
        fVar6 = local_64 - local_58;
        fVar5 = SQRT(fVar6 * fVar6 + local_50 * local_50 + local_4c * local_4c);
        local_8c = *(float *)(iVar9 + 0x5c) * *(float *)(*(int *)((int)actor + 0xa4) + 0x3f4);
        if (fVar5 < local_8c + fVar4) {
          if (*(int *)(*(int *)((int)actor + 0xa4) + 0x3f0) == 2) {
            *(undefined4 *)(*(int *)((int)param_1 + 0xa4) + 0x3f8) = 1;
            pfVar8 = (float *)((int)param_1 + 0xc);
            *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x3f8) = 1;
            local_24 = local_6c - local_60;
            local_20 = local_68 - local_5c;
            local_1c = local_64 - local_58;
            _DAT_008ca348 = *pfVar8;
            _DAT_008ca34c = *(undefined4 *)((int)param_1 + 0x10);
            _DAT_008ca350 = *(undefined4 *)((int)param_1 + 0x14);
            ((code *)Vec3_Normalize)();
            bVar2 = *(byte *)((int)param_1 + 8);
            fVar5 = (1.0 - (fVar5 - local_8c) / fVar4) * fVar4;
            local_18 = (local_24 * fVar5 + local_6c) - local_98;
            local_14 = (local_20 * fVar5 + local_68) - local_94;
            local_10 = (local_1c * fVar5 + local_64) - local_90;
            ((code *)Actor_SetPositionClamped)();
            _DAT_008ca338 = *pfVar8;
            _DAT_008ca33c = *(undefined4 *)((int)param_1 + 0x10);
            _DAT_008ca340 = *(undefined4 *)((int)param_1 + 0x14);
            _DAT_008ca320 = *pfVar8;
            _DAT_008ca324 = *(float *)((int)param_1 + 0x10);
            _DAT_008ca328 = *(float *)((int)param_1 + 0x14);
            if ((bVar2 & 1) != 0) {
              *(uint *)((int)param_1 + 8) = *(uint *)((int)param_1 + 8) | 1;
            }
          }
          else {
            local_88 = local_4c;
            local_84 = local_50;
            local_80 = fVar6;
            pfVar7 = Actor_GetFrame(actor);
            pvStack_d0 = (void *)0x493d0d;
            Vec3_TransformTo(&local_a4,&local_88,pfVar7);
            local_a4 = local_a4 + *pfVar8;
            local_a0 = local_a0 + *(float *)(iVar9 + 0x7c);
            local_9c = local_9c + *(float *)(iVar9 + 0x80);
            iVar3 = *(int *)((int)actor + 0xa4);
            local_3c[2] = *(float *)(iVar9 + 0x68) * *(float *)(iVar3 + 0x3f4) - fVar4;
            local_3c[0] = *(float *)(iVar9 + 0x60) * *(float *)(iVar3 + 0x3f4) - fVar4;
            local_3c[1] = *(float *)(iVar9 + 100) * *(float *)(iVar3 + 0x3f4) - fVar4;
            local_3c[3] = *(float *)(iVar9 + 0x6c) * *(float *)(iVar3 + 0x3f4) + fVar4;
            local_2c = *(float *)(iVar9 + 0x70) * *(float *)(iVar3 + 0x3f4) + fVar4;
            local_28 = *(float *)(iVar9 + 0x74) * *(float *)(iVar3 + 0x3f4) + fVar4;
            if ((((local_9c <= local_3c[2]) || (local_a0 <= local_3c[1])) ||
                ((local_2c <= local_a0 || ((local_a4 <= local_3c[0] || (local_3c[3] <= local_a4)))))
                ) || (local_28 <= local_9c)) goto LAB_004940c6;
            *(undefined4 *)(*(int *)((int)param_1 + 0xa4) + 0x3f8) = 1;
            _DAT_008ca348 = *(float *)((int)param_1 + 0xc);
            _DAT_008ca34c = *(undefined4 *)((int)param_1 + 0x10);
            _DAT_008ca350 = *(undefined4 *)((int)param_1 + 0x14);
            local_88 = (local_98 + *(float *)((int)param_1 + 0x18)) - local_60;
            local_84 = (*(float *)((int)param_1 + 0x1c) + local_94) - local_5c;
            local_80 = (*(float *)((int)param_1 + 0x20) + local_90) - local_58;
            pfVar7 = Actor_GetFrame(actor);
            pvStack_d0 = (void *)0x493ee1;
            Vec3_TransformTo(&local_48,&local_88,pfVar7);
            local_48 = local_48 + *pfVar8;
            local_44 = local_44 + *(float *)(iVar9 + 0x7c);
            ppfVar10 = apfStack_e0;
            local_40 = local_40 + *(float *)(iVar9 + 0x80);
            pfVar8 = local_3c;
            for (iVar9 = 6; ppfVar10 = (float **)((int)ppfVar10 + 4), iVar9 != 0; iVar9 = iVar9 + -1
                ) {
              *ppfVar10 = PUN(float *,(float)*pfVar8);
              pfVar8 = pfVar8 + 1;
            }
            apfStack_e0[0] = &local_48;
            iVar9 = ((code *)Collision_BoxSlide)(&local_a4);
            if (iVar9 == 0) {
              Actor_GetFrame(actor);
              pfVar8 = local_3c;
              ppfVar10 = apfStack_e0;
              for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
                *ppfVar10 = PUN(float *,(float)*pfVar8);
                pfVar8 = pfVar8 + 1;
                ppfVar10 = ppfVar10 + 1;
              }
              ((code *)Collision_PushOutOfBox)(&local_a4);
              local_7c = local_a4;
              local_78 = local_a0;
              local_74 = local_9c;
            }
            pfVar8 = Actor_GetFrame(actor);
            Vec3_Rotate3x3(&local_7c,pfVar8);
            local_7c = local_7c - local_98;
            local_78 = local_78 - local_94;
            *(float *)((int)param_1 + 0x18) = *(float *)((int)param_1 + 0xc);
            local_74 = local_74 - local_90;
            *(undefined4 *)((int)param_1 + 0x1c) = *(undefined4 *)((int)param_1 + 0x10);
            *(undefined4 *)((int)param_1 + 0x20) = *(undefined4 *)((int)param_1 + 0x14);
            pfVar8 = Actor_GetFrame(actor);
            Vec3_Rotate3x3((float *)&DAT_008ca320,pfVar8);
            _DAT_008ca320 = _DAT_008ca320 - local_98;
            _DAT_008ca324 = _DAT_008ca324 - local_94;
            _DAT_008ca328 = _DAT_008ca328 - local_90;
            bVar2 = *(byte *)((int)param_1 + 8);
            ((code *)Actor_SetPositionClamped)();
            _DAT_008ca338 = *(float *)((int)param_1 + 0xc);
            _DAT_008ca33c = *(undefined4 *)((int)param_1 + 0x10);
            _DAT_008ca340 = *(undefined4 *)((int)param_1 + 0x14);
            if ((bVar2 & 1) != 0) {
              *(uint *)((int)param_1 + 8) = *(uint *)((int)param_1 + 8) | 1;
              puVar1 = (undefined4 *)
                       (*(int *)((int)param_1 + 0xa4) +
                       (*(int *)(*(int *)((int)param_1 + 0xa4) + 0x44) + 5) * 0xc);
              local_c = *puVar1;
              pvStack_d0 = param_1;
              local_8 = puVar1[1];
              local_4 = puVar1[2];
              pvStack_d4 = (void *)0x4940aa;
              ((code *)Walker_ReplanPath)();
            }
          }
          pvStack_d4 = param_1;
          apfStack_e0[2] = (float *)0x4940c3;
          pvStack_d0 = actor;
          ((code *)Sector_IntersectSegment)();
        }
      }
LAB_004940c6:
      local_54 = local_54 + 1;
      local_70 = local_70 + 1;
    } while (local_54 < g_nDrawableActorCount);
  }
  return 1;
}
#undef apfStack_e0
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_3c
#undef local_4
#undef local_40
#undef local_44
#undef local_48
#undef local_4c
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
#undef local_8
#undef local_80
#undef local_84
#undef local_88
#undef local_8c
#undef local_90
#undef local_94
#undef local_98
#undef local_9c
#undef local_a0
#undef local_a4
#undef local_c
#undef pvStack_d0
#undef pvStack_d4


/* ---- 0x00494100  Collision_BoxSlide ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Collision_BoxSlide: box collision response (entry face from the move, slide along the face).
   Head-on slides depend on float noise of a zero rotation axis, either side. Ported bit-exact as
   origBoxSlide in engines/grim/actor.cpp. */

undefined4
Collision_BoxSlide(float *param_1,float *param_2,float param_3,float param_4,float param_5,
                  float param_6,float param_7,float param_8,float *param_9)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float *pfVar6;
  int iVar7;
  float10 fVar8;
  float fVar9;
  #define local_48 (*(float *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(float *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(float *)(_frame + (0x60 - 0x40)))
  #define local_3c (*(float *)(_frame + (0x60 - 0x3c)))
  #define local_38 (*(float *)(_frame + (0x60 - 0x38)))
  #define local_34 (*(float *)(_frame + (0x60 - 0x34)))
  #define local_30 (*(float (*)[12])(_frame + (0x60 - 0x30)))
  
  pfVar6 = param_9;
  iVar7 = 0;
  local_48 = *param_1 - *param_2;
  local_44 = param_1[1] - param_2[1];
  local_40 = param_1[2] - param_2[2];
  fVar1 = local_48 * -10.0 + *param_2;
  fVar9 = local_44 * -10.0 + param_2[1];
  fVar4 = local_40 * -10.0 + param_2[2];
  *param_2 = fVar1;
  fVar3 = 3.4028235e+38;
  param_2[1] = fVar9;
  param_2[2] = fVar4;
  if (param_6 - 0.002 < fVar1) {
    fVar2 = local_48;
    if (local_48 < 0.0) {
      fVar2 = -local_48;
    }
    fVar2 = (param_6 - *param_1) / fVar2;
    fVar5 = fVar2;
    if (fVar2 < 0.0) {
      fVar5 = -fVar2;
    }
    fVar3 = 3.4028235e+38;
    if (fVar5 < 3.4028235e+38) {
      fVar3 = -fVar2;
      iVar7 = 1;
      local_3c = 1.0;
      local_38 = 0.0;
      local_34 = 0.0;
    }
  }
  if (fVar1 < param_3 - -0.002) {
    fVar1 = local_48;
    if (local_48 < 0.0) {
      fVar1 = -local_48;
    }
    fVar1 = (param_3 - *param_1) / fVar1;
    fVar2 = fVar1;
    if (fVar1 < 0.0) {
      fVar2 = -fVar1;
    }
    fVar5 = fVar3;
    if (fVar3 < 0.0) {
      fVar5 = -fVar3;
    }
    if (fVar2 < fVar5) {
      iVar7 = 2;
      local_3c = -1.0;
      local_38 = 0.0;
      local_34 = 0.0;
      fVar3 = fVar1;
    }
  }
  if (param_7 - 0.002 < fVar9) {
    fVar1 = local_44;
    if (local_44 < 0.0) {
      fVar1 = -local_44;
    }
    fVar1 = (param_7 - param_1[1]) / fVar1;
    fVar2 = fVar1;
    if (fVar1 < 0.0) {
      fVar2 = -fVar1;
    }
    fVar5 = fVar3;
    if (fVar3 < 0.0) {
      fVar5 = -fVar3;
    }
    if (fVar2 < fVar5) {
      fVar3 = -fVar1;
      iVar7 = 3;
      local_3c = 0.0;
      local_38 = 1.0;
      local_34 = 0.0;
    }
  }
  if (fVar9 < param_4 - -0.002) {
    fVar1 = local_44;
    if (local_44 < 0.0) {
      fVar1 = -local_44;
    }
    fVar1 = (param_4 - param_1[1]) / fVar1;
    fVar9 = fVar1;
    if (fVar1 < 0.0) {
      fVar9 = -fVar1;
    }
    fVar2 = fVar3;
    if (fVar3 < 0.0) {
      fVar2 = -fVar3;
    }
    if (fVar9 < fVar2) {
      iVar7 = 4;
      local_3c = 0.0;
      local_38 = -1.0;
      local_34 = 0.0;
      fVar3 = fVar1;
    }
  }
  if (param_8 - 0.002 < fVar4) {
    fVar1 = local_40;
    if (local_40 < 0.0) {
      fVar1 = -local_40;
    }
    fVar1 = (param_8 - param_1[2]) / fVar1;
    fVar9 = fVar1;
    if (fVar1 < 0.0) {
      fVar9 = -fVar1;
    }
    fVar2 = fVar3;
    if (fVar3 < 0.0) {
      fVar2 = -fVar3;
    }
    if (fVar9 < fVar2) {
      fVar3 = -fVar1;
      iVar7 = 5;
      local_3c = 0.0;
      local_38 = 0.0;
      local_34 = 1.0;
    }
  }
  if (fVar4 < param_5 - -0.002) {
    fVar1 = local_40;
    if (local_40 < 0.0) {
      fVar1 = -local_40;
    }
    fVar1 = (param_5 - param_1[2]) / fVar1;
    fVar9 = fVar1;
    if (fVar1 < 0.0) {
      fVar9 = -fVar1;
    }
    fVar4 = fVar3;
    if (fVar3 < 0.0) {
      fVar4 = -fVar3;
    }
    if (fVar9 < fVar4) {
      iVar7 = 6;
      local_3c = 0.0;
      local_38 = 0.0;
      local_34 = -1.0;
      fVar3 = fVar1;
    }
  }
  if (iVar7 == 0) {
    return 0;
  }
  *param_9 = fVar3 * local_48 + *param_1;
  param_9[1] = fVar3 * local_44 + param_1[1];
  param_9[2] = fVar3 * local_40 + param_1[2];
  _DAT_008ca320 = *param_9;
  _DAT_008ca324 = param_9[1];
  _DAT_008ca328 = param_9[2];
  fVar1 = fVar3;
  if (fVar3 < 0.0) {
    fVar1 = -fVar3;
  }
  local_48 = local_48 * fVar1;
  fVar1 = fVar3;
  if (fVar3 < 0.0) {
    fVar1 = -fVar3;
  }
  local_44 = local_44 * fVar1;
  if (fVar3 < 0.0) {
    fVar3 = -fVar3;
  }
  local_40 = local_40 * fVar3;
  fVar8 = (float10)((code *)Vec3_Normalize)(&local_48);
  fVar1 = (float)fVar8;
  fVar9 = Vec3_Dot2(&local_48,&local_3c);
  fVar8 = (float10)Math_AsinDegreesSeries(fVar9);
  if ((float10)90.0 - fVar8 < (float10)90.0) {
    return 0;
  }
  param_3 = local_34 * local_44 - local_38 * local_40;
  param_4 = local_3c * local_40 - local_34 * local_48;
  param_5 = local_38 * local_48 - local_3c * local_44;
  Vec3_Normalize(&param_3);
  Matrix_AxisAngle(local_30,&param_3,(float)((float10)90.0 - fVar8) - 90.0);
  Vec3_Transform(&local_48,local_30);
  *pfVar6 = fVar1 * local_48 + *pfVar6;
  pfVar6[1] = fVar1 * local_44 + pfVar6[1];
  pfVar6[2] = fVar1 * local_40 + pfVar6[2];
  return 1;
}
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_44
#undef local_48

