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
  #define local_14 (*(float (*)[2])(_frame + (0x30 - 0x14)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  local_c = *param_1 - *param_9;
  local_8 = param_1[1] - param_9[1];
  local_4 = param_1[2] - param_9[2];
  Vec3_TransformTo(&local_18,&local_c,param_8);
  if ((((param_4 < local_14[1]) && (param_3 < local_14[0])) && (local_14[0] < param_6)) &&
     (((param_2 < local_18 && (local_18 < param_5)) && (local_14[1] < param_7)))) {
    fVar1 = 3.4028235e+38;
    if (local_14[0] < param_6) {
      fVar2 = param_6 - local_14[0];
      if (fVar2 < 0.0) {
        fVar2 = -fVar2;
      }
      fVar1 = 3.4028235e+38;
      if (fVar2 < 3.4028235e+38) {
        local_8 = param_6 - -0.01;
        local_c = local_18;
        local_4 = local_14[1];
        fVar1 = fVar2;
      }
    }
    if (param_3 < local_14[0]) {
      fVar2 = param_3 - local_14[0];
      if (fVar2 < 0.0) {
        fVar2 = -fVar2;
      }
      if (fVar2 < fVar1) {
        local_8 = param_3 - 0.01;
        local_c = local_18;
        local_4 = local_14[1];
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
        local_8 = local_14[0];
        local_4 = local_14[1];
        fVar1 = fVar2;
      }
    }
    if (param_2 < local_18) {
      fVar2 = param_2 - local_18;
      if (fVar2 < 0.0) {
        fVar2 = -fVar2;
      }
      if (fVar2 < fVar1) {
        local_c = param_2 - 0.01;
        local_8 = local_14[0];
        local_4 = local_14[1];
      }
    }
    Vec3_Sub(param_1,&local_c,param_8);
  }
  return;
}
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00492510  Collision_PointInBox ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 __cdecl
Collision_PointInBox
          (float *a,float *b,float *p3,float bx0,float by0,float bz0,float bx1,float by1,float bz1,
          float *p10,float *offset)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  #define afStack_38 (*(float (*)[4])(_frame + (0x50 - 0x38)))
  #define pfStack_28 (*(float **)(_frame + (0x50 - 0x28)))
  #define pfStack_24 (*(float **)(_frame + (0x50 - 0x24)))
  #define pfStack_20 (*(float **)(_frame + (0x50 - 0x20)))
  #define local_c (*(float (*)[3])(_frame + (0x50 - 0xc)))
  
  local_c[0] = *offset + *a;
  pfStack_20 = p10;
  bx0 = *offset + *b;
  local_c[1] = a[1] + offset[1];
  by0 = b[1] + offset[1];
  local_c[2] = a[2] + offset[2];
  bz0 = b[2] + offset[2];
  pfVar3 = &bx0;
  pfVar4 = afStack_38;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar4 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar4 = pfVar4 + 1;
  }
  pfStack_20 = (float *)((code *)Collision_SegmentHitsBox)(local_c,&bx0,p3);
  if (pfStack_20 == (float *)0x0) {
    pfStack_24 = b;
    pfStack_28 = a;
    afStack_38[3] = 6.717497e-39;
    uVar1 = ((code *)Planner_PlanPath)();
    return uVar1;
  }
  return 0;
}
#undef afStack_38
#undef local_c
#undef pfStack_20
#undef pfStack_24
#undef pfStack_28

#endif


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
  float fVar7;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(float (*)[3])(_frame + (0x40 - 0x24)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  local_18[0] = *param_1 - *param_3;
  local_18[1] = param_1[1] - param_3[1];
  local_18[2] = param_1[2] - param_3[2];
  Vec3_TransformTo(local_24,local_18,param_10);
  local_18[0] = *param_2 - *param_3;
  local_18[1] = param_2[1] - param_3[1];
  local_18[2] = param_2[2] - param_3[2];
  Vec3_TransformTo(local_c,local_18,param_10);
  fVar2 = local_c[0] - local_24[0];
  fVar3 = local_c[1] - local_24[1];
  fVar4 = local_c[2] - local_24[2];
  if (((param_8 < local_24[1]) && (local_c[1] < param_8)) &&
     (fVar1 = (param_8 - local_24[1]) / fVar3, fVar1 < 1.0)) {
    fVar5 = fVar1 * fVar2 + local_24[0];
    if ((param_4 < fVar5) &&
       (fVar6 = fVar1 * fVar3 + local_24[1], fVar7 = fVar1 * fVar4 + local_24[2], fVar5 < param_7))
    goto LAB_00492801;
  }
  fVar1 = 1.0;
  fVar5 = *(float *)&DAT_008ca320;
  fVar6 = *(float *)&DAT_008ca324;
  fVar7 = *(float *)&DAT_008ca328;
LAB_00492801:
  *(float *)&DAT_008ca328 = fVar7;
  *(float *)&DAT_008ca324 = fVar6;
  *(float *)&DAT_008ca320 = fVar5;
  if (((local_24[1] < param_5) && (param_5 < local_c[1])) &&
     (fVar5 = (param_5 - local_24[1]) / fVar3, fVar5 < fVar1)) {
    fVar6 = fVar5 * fVar2 + local_24[0];
    if ((param_4 < fVar6) && (fVar6 < param_7)) {
      fVar1 = fVar5;
      *(float *)&DAT_008ca320 = fVar6;
      *(float *)&DAT_008ca324 = fVar5 * fVar3 + local_24[1];
      *(float *)&DAT_008ca328 = fVar5 * fVar4 + local_24[2];
    }
  }
  if (((param_7 < local_24[0]) && (local_c[0] < param_7)) &&
     (fVar5 = (param_7 - local_24[0]) / fVar2, fVar5 < fVar1)) {
    fVar6 = fVar5 * fVar3 + local_24[1];
    if ((param_5 < fVar6) && (fVar6 < param_8)) {
      fVar1 = fVar5;
      *(float *)&DAT_008ca320 = fVar5 * fVar2 + local_24[0];
      *(float *)&DAT_008ca324 = fVar6;
      *(float *)&DAT_008ca328 = fVar5 * fVar4 + local_24[2];
    }
  }
  if (((local_24[0] < param_4) && (param_4 < local_c[0])) &&
     (fVar5 = (param_4 - local_24[0]) / fVar2, fVar5 < fVar1)) {
    fVar3 = fVar5 * fVar3 + local_24[1];
    if ((param_5 < fVar3) && (fVar3 < param_8)) {
      fVar1 = fVar5;
      *(float *)&DAT_008ca320 = fVar5 * fVar2 + local_24[0];
      *(float *)&DAT_008ca324 = fVar3;
      *(float *)&DAT_008ca328 = fVar5 * fVar4 + local_24[2];
    }
  }
  if (fVar1 == 1.0) {
    return 0;
  }
  return 1;
}
#undef local_18
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
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
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar4 = -1;
  local_4 = 0x7f7fffff;
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
                (*param_1 - pfVar2[-2]) * (*param_1 - pfVar2[-2]), fVar1 < PUN(float,local_4))) {
      iVar4 = iVar3;
      local_4 = PUN(uint,(float)fVar1);
    }
    iVar3 = iVar3 + 1;
    piVar5 = piVar5 + 1;
    pfVar2 = pfVar2 + 3;
  } while (iVar3 < 4);
  return iVar4;
}
#undef local_4
#undef local_8
#undef local_c


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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Collision_TestActorAgainstOthers(void *param_1)

{
  unsigned char _frame[0xf0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  void *actor;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  float **ppfVar9;
  #define pfStack_e0 (*(float **)(_frame + (0xf0 - 0xe0)))
  #define afStack_dc (*(float (*)[2])(_frame + (0xf0 - 0xdc)))
  #define pvStack_d4 (*(void **)(_frame + (0xf0 - 0xd4)))
  #define pvStack_d0 (*(void **)(_frame + (0xf0 - 0xd0)))
  #define local_b0 (*(uint *)(_frame + (0xf0 - 0xb0)))
  #define local_ac (*(uint *)(_frame + (0xf0 - 0xac)))
  #define local_a8 (*(uint *)(_frame + (0xf0 - 0xa8)))
  #define local_a4 (*(float (*)[3])(_frame + (0xf0 - 0xa4)))
  #define local_98 (*(float (*)[3])(_frame + (0xf0 - 0x98)))
  #define local_8c (*(float (*)[3])(_frame + (0xf0 - 0x8c)))
  #define local_80 (*(float (*)[3])(_frame + (0xf0 - 0x80)))
  #define local_74 (*(float (*)[3])(_frame + (0xf0 - 0x74)))
  #define local_68 (*(float (*)[3])(_frame + (0xf0 - 0x68)))
  #define local_5c (*(float (*)[3])(_frame + (0xf0 - 0x5c)))
  #define local_50 (*(float (*)[3])(_frame + (0xf0 - 0x50)))
  #define local_44 (*(float (*)[3])(_frame + (0xf0 - 0x44)))
  #define local_38 (*(float (*)[3])(_frame + (0xf0 - 0x38)))
  #define local_2c (*(float (*)[3])(_frame + (0xf0 - 0x2c)))
  #define local_20 (*(float (*)[3])(_frame + (0xf0 - 0x20)))
  #define local_14 (*(uint *)(_frame + (0xf0 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0xf0 - 0x10)))
  #define local_c (*(uint *)(_frame + (0xf0 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0xf0 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0xf0 - 0x4)))
  
  iVar8 = *(int *)(*(int *)(*(int *)((int)param_1 + 0xa0) + 4) + 4);
  pfVar6 = Actor_GetFrame(param_1);
  Vec3_Copy(local_98,(float *)(iVar8 + 0x78),pfVar6);
  fVar3 = local_98[0] + *(float *)((int)param_1 + 0xc);
  local_5c[2] = 0.0;
  local_68[0] = *(float *)((int)param_1 + 0x10) + local_98[1];
  local_68[1] = *(float *)((int)param_1 + 0x14) + local_98[2];
  fVar4 = *(float *)(iVar8 + 0x5c) * *(float *)(*(int *)((int)param_1 + 0xa4) + 0x3f4);
  if (0 < g_nDrawableActorCount) {
    local_74[1] = PUN(float,&g_pDrawableActors);
    do {
      actor = *PUN(void **,(float)local_74[1]);
      if (((actor != param_1) && (*(int *)((int)actor + 0xa4) != 0)) &&
         (*(int *)(*(int *)((int)actor + 0xa4) + 0x3f0) != 0)) {
        iVar8 = *(int *)(*(int *)(*(int *)((int)actor + 0xa0) + 4) + 4);
        pfVar6 = (float *)(iVar8 + 0x78);
        pfVar7 = Actor_GetFrame(actor);
        pvStack_d0 = (void *)0x493ac7;
        Vec3_Sub(local_68 + 2,pfVar6,pfVar7);
        local_50[1] = fVar3 - local_68[2];
        local_50[0] = local_68[0] - local_5c[0];
        fVar5 = local_68[1] - local_5c[1];
        local_8c[0] = *(float *)(iVar8 + 0x5c) * *(float *)(*(int *)((int)actor + 0xa4) + 0x3f4);
        if (SQRT(fVar5 * fVar5 + local_50[0] * local_50[0] + local_50[1] * local_50[1]) <
            local_8c[0] + fVar4) {
          if (*(int *)(*(int *)((int)actor + 0xa4) + 0x3f0) == 2) {
            *(undefined4 *)(*(int *)((int)param_1 + 0xa4) + 0x3f8) = 1;
            pfVar6 = (float *)((int)param_1 + 0xc);
            *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x3f8) = 1;
            local_2c[2] = fVar3 - local_68[2];
            *(float *)&DAT_008ca348 = *pfVar6;
            _DAT_008ca34c = *(undefined4 *)((int)param_1 + 0x10);
            _DAT_008ca350 = *(undefined4 *)((int)param_1 + 0x14);
            Vec3_Normalize(local_2c + 2);
            bVar1 = *(byte *)((int)param_1 + 8);
            ((code *)Actor_SetPositionClamped)();
            *(float *)&DAT_008ca338 = *pfVar6;
            _DAT_008ca33c = *(undefined4 *)((int)param_1 + 0x10);
            _DAT_008ca340 = *(undefined4 *)((int)param_1 + 0x14);
            *(float *)&DAT_008ca320 = *pfVar6;
            *(float *)&DAT_008ca324 = *(float *)((int)param_1 + 0x10);
            *(float *)&DAT_008ca328 = *(float *)((int)param_1 + 0x14);
            if ((bVar1 & 1) != 0) {
              *(uint *)((int)param_1 + 8) = *(uint *)((int)param_1 + 8) | 1;
            }
          }
          else {
            local_8c[1] = local_50[1];
            local_8c[2] = local_50[0];
            local_80[0] = fVar5;
            pfVar7 = Actor_GetFrame(actor);
            pvStack_d0 = (void *)0x493d0d;
            Vec3_TransformTo(local_a4,local_8c + 1,pfVar7);
            local_a4[0] = local_a4[0] + *pfVar6;
            local_a4[1] = local_a4[1] + *(float *)(iVar8 + 0x7c);
            local_a4[2] = local_a4[2] + *(float *)(iVar8 + 0x80);
            iVar2 = *(int *)((int)actor + 0xa4);
            local_44[2] = *(float *)(iVar8 + 0x60) * *(float *)(iVar2 + 0x3f4) - fVar4;
            local_2c[0] = *(float *)(iVar8 + 0x70) * *(float *)(iVar2 + 0x3f4) + fVar4;
            local_2c[1] = *(float *)(iVar8 + 0x74) * *(float *)(iVar2 + 0x3f4) + fVar4;
            if ((((local_a4[2] <= *(float *)(iVar8 + 0x68) * *(float *)(iVar2 + 0x3f4) - fVar4) ||
                 (local_a4[1] <= *(float *)(iVar8 + 100) * *(float *)(iVar2 + 0x3f4) - fVar4)) ||
                ((local_2c[0] <= local_a4[1] ||
                 ((local_a4[0] <= local_44[2] ||
                  (*(float *)(iVar8 + 0x6c) * *(float *)(iVar2 + 0x3f4) + fVar4 <= local_a4[0]))))))
               || (local_2c[1] <= local_a4[2])) goto LAB_004940c6;
            *(undefined4 *)(*(int *)((int)param_1 + 0xa4) + 0x3f8) = 1;
            *(float *)&DAT_008ca348 = *(float *)((int)param_1 + 0xc);
            _DAT_008ca34c = *(undefined4 *)((int)param_1 + 0x10);
            _DAT_008ca350 = *(undefined4 *)((int)param_1 + 0x14);
            local_8c[1] = (local_98[0] + *(float *)((int)param_1 + 0x18)) - local_68[2];
            local_8c[2] = (*(float *)((int)param_1 + 0x1c) + local_98[1]) - local_5c[0];
            local_80[0] = (*(float *)((int)param_1 + 0x20) + local_98[2]) - local_5c[1];
            pfVar7 = Actor_GetFrame(actor);
            pvStack_d0 = (void *)0x493ee1;
            Vec3_TransformTo(local_50 + 2,local_8c + 1,pfVar7);
            local_50[2] = local_50[2] + *pfVar6;
            local_44[0] = local_44[0] + *(float *)(iVar8 + 0x7c);
            local_44[1] = local_44[1] + *(float *)(iVar8 + 0x80);
            pfVar6 = local_44 + 2;
            pfVar7 = afStack_dc;
            for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
              *pfVar7 = *pfVar6;
              pfVar6 = pfVar6 + 1;
              pfVar7 = pfVar7 + 1;
            }
            pfStack_e0 = local_50 + 2;
            iVar8 = ((code *)Collision_BoxSlide)(local_a4);
            if (iVar8 == 0) {
              Actor_GetFrame(actor);
              pfVar6 = local_44 + 2;
              ppfVar9 = &pfStack_e0;
              for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
                *ppfVar9 = PUN(float *,(float)*pfVar6);
                pfVar6 = pfVar6 + 1;
                ppfVar9 = ppfVar9 + 1;
              }
              ((code *)Collision_PushOutOfBox)(local_a4);
              local_80[1] = local_a4[0];
              local_80[2] = local_a4[1];
            }
            pfVar6 = Actor_GetFrame(actor);
            Vec3_Rotate3x3(local_80 + 1,pfVar6);
            local_80[1] = local_80[1] - local_98[0];
            local_80[2] = local_80[2] - local_98[1];
            *(float *)((int)param_1 + 0x18) = *(float *)((int)param_1 + 0xc);
            *(undefined4 *)((int)param_1 + 0x1c) = *(undefined4 *)((int)param_1 + 0x10);
            *(undefined4 *)((int)param_1 + 0x20) = *(undefined4 *)((int)param_1 + 0x14);
            pfVar6 = Actor_GetFrame(actor);
            Vec3_Rotate3x3((float *)&DAT_008ca320,pfVar6);
            *(float *)&DAT_008ca320 = *(float *)&DAT_008ca320 - local_98[0];
            *(float *)&DAT_008ca324 = *(float *)&DAT_008ca324 - local_98[1];
            *(float *)&DAT_008ca328 = *(float *)&DAT_008ca328 - local_98[2];
            bVar1 = *(byte *)((int)param_1 + 8);
            ((code *)Actor_SetPositionClamped)();
            *(float *)&DAT_008ca338 = *(float *)((int)param_1 + 0xc);
            _DAT_008ca33c = *(undefined4 *)((int)param_1 + 0x10);
            _DAT_008ca340 = *(undefined4 *)((int)param_1 + 0x14);
            if ((bVar1 & 1) != 0) {
              *(uint *)((int)param_1 + 8) = *(uint *)((int)param_1 + 8) | 1;
              pvStack_d0 = param_1;
              pvStack_d4 = (void *)0x4940aa;
              ((code *)Walker_ReplanPath)();
            }
          }
          pvStack_d4 = param_1;
          afStack_dc[1] = 6.727223e-39;
          pvStack_d0 = actor;
          ((code *)Sector_IntersectSegment)();
        }
      }
LAB_004940c6:
      local_5c[2] = PUN(float,(PUN(int,(float)local_5c[2]) + 1));
      local_74[1] = PUN(float,(PUN(int,(float)local_74[1]) + 4));
    } while (PUN(int,(float)local_5c[2]) < g_nDrawableActorCount);
  }
  return 1;
}
#undef afStack_dc
#undef local_10
#undef local_14
#undef local_20
#undef local_2c
#undef local_38
#undef local_4
#undef local_44
#undef local_50
#undef local_5c
#undef local_68
#undef local_74
#undef local_8
#undef local_80
#undef local_8c
#undef local_98
#undef local_a4
#undef local_a8
#undef local_ac
#undef local_b0
#undef local_c
#undef pfStack_e0
#undef pvStack_d0
#undef pvStack_d4

#endif


/* ---- 0x00494100  Collision_BoxSlide ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_58 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Collision_BoxSlide: box collision response (entry face from the move, slide along the face).
   Head-on slides depend on float noise of a zero rotation axis, either side. Ported bit-exact as
   origBoxSlide in engines/grim/actor.cpp. */

undefined4
Collision_BoxSlide(float *param_1,float *param_2,float param_3,float param_4,float param_5,
                  float param_6,float param_7,float param_8,float *param_9)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  int iVar9;
  float fVar10;
  float fVar11;
  #define local_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define local_50 (*(uint *)(_frame + (0x70 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0x70 - 0x4c)))
  #define local_48 (*(float *)(_frame + (0x70 - 0x48)))
  #define local_44 (*(float (*)[2])(_frame + (0x70 - 0x44)))
  #define local_3c (*(float *)(_frame + (0x70 - 0x3c)))
  #define local_38 (*(float (*)[2])(_frame + (0x70 - 0x38)))
  #define local_30 (*(float (*)[12])(_frame + (0x70 - 0x30)))
  
  pfVar8 = param_9;
  iVar9 = 0;
  fVar10 = *param_1 - *param_2;
  fVar1 = param_1[1] - param_2[1];
  fVar3 = param_1[2] - param_2[2];
  fVar11 = fVar10 * -10.0 + *param_2;
  fVar2 = fVar1 * -10.0 + param_2[1];
  fVar6 = fVar3 * -10.0 + param_2[2];
  *param_2 = fVar11;
  fVar5 = 3.4028235e+38;
  param_2[1] = fVar2;
  param_2[2] = fVar6;
  if (param_6 - 0.002 < fVar11) {
    fVar4 = fVar10;
    if (fVar10 < 0.0) {
      fVar4 = -fVar10;
    }
    fVar4 = (param_6 - *param_1) / fVar4;
    fVar7 = fVar4;
    if (fVar4 < 0.0) {
      fVar7 = -fVar4;
    }
    fVar5 = 3.4028235e+38;
    if (fVar7 < 3.4028235e+38) {
      fVar5 = -fVar4;
      iVar9 = 1;
      local_3c = 1.0;
      local_38[0] = 0.0;
      local_38[1] = 0.0;
    }
  }
  if (fVar11 < param_3 - -0.002) {
    fVar11 = fVar10;
    if (fVar10 < 0.0) {
      fVar11 = -fVar10;
    }
    fVar11 = (param_3 - *param_1) / fVar11;
    fVar4 = fVar11;
    if (fVar11 < 0.0) {
      fVar4 = -fVar11;
    }
    fVar7 = fVar5;
    if (fVar5 < 0.0) {
      fVar7 = -fVar5;
    }
    if (fVar4 < fVar7) {
      iVar9 = 2;
      local_3c = -1.0;
      local_38[0] = 0.0;
      local_38[1] = 0.0;
      fVar5 = fVar11;
    }
  }
  if (param_7 - 0.002 < fVar2) {
    fVar11 = fVar1;
    if (fVar1 < 0.0) {
      fVar11 = -fVar1;
    }
    fVar11 = (param_7 - param_1[1]) / fVar11;
    fVar4 = fVar11;
    if (fVar11 < 0.0) {
      fVar4 = -fVar11;
    }
    fVar7 = fVar5;
    if (fVar5 < 0.0) {
      fVar7 = -fVar5;
    }
    if (fVar4 < fVar7) {
      fVar5 = -fVar11;
      iVar9 = 3;
      local_3c = 0.0;
      local_38[0] = 1.0;
      local_38[1] = 0.0;
    }
  }
  if (fVar2 < param_4 - -0.002) {
    fVar11 = fVar1;
    if (fVar1 < 0.0) {
      fVar11 = -fVar1;
    }
    fVar11 = (param_4 - param_1[1]) / fVar11;
    fVar2 = fVar11;
    if (fVar11 < 0.0) {
      fVar2 = -fVar11;
    }
    fVar4 = fVar5;
    if (fVar5 < 0.0) {
      fVar4 = -fVar5;
    }
    if (fVar2 < fVar4) {
      iVar9 = 4;
      local_3c = 0.0;
      local_38[0] = -1.0;
      local_38[1] = 0.0;
      fVar5 = fVar11;
    }
  }
  if (param_8 - 0.002 < fVar6) {
    fVar11 = fVar3;
    if (fVar3 < 0.0) {
      fVar11 = -fVar3;
    }
    fVar11 = (param_8 - param_1[2]) / fVar11;
    fVar2 = fVar11;
    if (fVar11 < 0.0) {
      fVar2 = -fVar11;
    }
    fVar4 = fVar5;
    if (fVar5 < 0.0) {
      fVar4 = -fVar5;
    }
    if (fVar2 < fVar4) {
      fVar5 = -fVar11;
      iVar9 = 5;
      local_3c = 0.0;
      local_38[0] = 0.0;
      local_38[1] = 1.0;
    }
  }
  if (fVar6 < param_5 - -0.002) {
    fVar11 = fVar3;
    if (fVar3 < 0.0) {
      fVar11 = -fVar3;
    }
    fVar11 = (param_5 - param_1[2]) / fVar11;
    fVar2 = fVar11;
    if (fVar11 < 0.0) {
      fVar2 = -fVar11;
    }
    fVar6 = fVar5;
    if (fVar5 < 0.0) {
      fVar6 = -fVar5;
    }
    if (fVar2 < fVar6) {
      iVar9 = 6;
      local_3c = 0.0;
      local_38[0] = 0.0;
      local_38[1] = -1.0;
      fVar5 = fVar11;
    }
  }
  if (iVar9 == 0) {
    return 0;
  }
  *param_9 = fVar5 * fVar10 + *param_1;
  param_9[1] = fVar5 * fVar1 + param_1[1];
  param_9[2] = fVar5 * fVar3 + param_1[2];
  *(float *)&DAT_008ca320 = *param_9;
  *(float *)&DAT_008ca324 = param_9[1];
  *(float *)&DAT_008ca328 = param_9[2];
  fVar11 = fVar5;
  if (fVar5 < 0.0) {
    fVar11 = -fVar5;
  }
  local_48 = fVar10 * fVar11;
  fVar10 = fVar5;
  if (fVar5 < 0.0) {
    fVar10 = -fVar5;
  }
  local_44[0] = fVar1 * fVar10;
  if (fVar5 < 0.0) {
    fVar5 = -fVar5;
  }
  local_44[1] = fVar3 * fVar5;
  fVar10 = Vec3_Normalize(&local_48);
  fVar11 = Vec3_Dot2(&local_48,&local_3c);
  fVar11 = Math_AsinDegreesSeries(fVar11);
  if (90.0 - fVar11 < 90.0) {
    return 0;
  }
  param_3 = local_38[1] * local_44[0] - local_38[0] * local_44[1];
  param_4 = local_3c * local_44[1] - local_38[1] * local_48;
  param_5 = local_38[0] * local_48 - local_3c * local_44[0];
  Vec3_Normalize(&param_3);
  Matrix_AxisAngle(local_30,&param_3,(90.0 - fVar11) - 90.0);
  Vec3_Transform(&local_48,local_30);
  *pfVar8 = fVar10 * local_48 + *pfVar8;
  pfVar8[1] = fVar10 * local_44[0] + pfVar8[1];
  pfVar8[2] = fVar10 * local_44[1] + pfVar8[2];
  return 1;
}
#undef local_30
#undef local_38
#undef local_3c
#undef local_44
#undef local_48
#undef local_4c
#undef local_50
#undef local_58

#endif

