/* GRIMFANDANGO.EXE :: walker.c
 * functions 0x00491230 .. 0x004a9ca0 (25 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00491230  Walker_UpdateYaw ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Walker_UpdateYaw(actor, pos): eases the visible yaw (actor+0x28) toward the walker heading. Done
   (returns 1) when under 0.5 deg. step = rate*frameSec*timescale; if remaining > step, step =
   (remaining - step)*0.1 + step. Rate <= 0 (snap) jumps the whole way and re-negates the rate. */

undefined4 Walker_UpdateYaw(void *param_1,float *param_2)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *pvVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  undefined4 uVar6;
  #define local_48 (*(float (*)[3])(_frame + (0x60 - 0x48)))
  #define local_38 (*(uint *)(_frame + (0x60 - 0x38)))
  #define local_30 (*(float (*)[12])(_frame + (0x60 - 0x30)))
  
  pvVar2 = param_1;
  pfVar3 = Actor_GetFrame(param_1);
  local_48[0] = pfVar3[3];
  local_48[1] = pfVar3[4];
  local_48[2] = pfVar3[5];
  if (*(float *)(*(int *)((int)param_1 + 0xa4) + 0x24) != 0.0) {
    uVar6 = *(undefined4 *)(*(int *)((int)param_1 + 0xa4) + 0x24);
    pfVar3 = Actor_GetFrame(param_1);
    Matrix_AxisAngle(local_30,pfVar3 + 6,uVar6);
    Vec3_Transform(local_48,local_30);
  }
  local_48[0] = local_48[0] + *param_2;
  local_48[1] = param_2[1] + local_48[1];
  local_48[2] = param_2[2] + local_48[2];
  Walker_ToLocalSpace(param_2,local_48);
  local_48[2] = 0.0;
  Vec3_Normalize(local_48);
  fVar4 = Math_AsinDegreesSeries(local_48[1]);
  fVar4 = 90.0 - fVar4;
  if (fVar4 < 0.5) {
    *(undefined4 *)(*(int *)((int)param_1 + 0xa4) + 0x28) = 0;
    return 1;
  }
  *(float *)(*(int *)((int)param_1 + 0xa4) + 0x28) = fVar4;
  iVar1 = *(int *)((int)param_1 + 0xa4);
  if (*(float *)(iVar1 + 0x1c) <= 0.0) {
    fVar5 = 3.4028235e+38;
    *(float *)(iVar1 + 0x1c) = *(float *)(iVar1 + 0x1c) * -1.0;
  }
  else {
    fVar5 = Timer_GetFrameSeconds();
    fVar5 = fVar5 * *(float *)(iVar1 + 0x41c) * *(float *)(iVar1 + 0x1c);
  }
  param_1 = PUN(void *,(float)fVar4);
  if (fVar5 < fVar4) {
    param_1 = PUN(void *,(float)((fVar4 - fVar5) * 0.1 + fVar5));
  }
  if (local_48[0] <= 0.0) {
    fVar4 = *(float *)((int)pvVar2 + 0x28) - PUN(float,param_1);
  }
  else {
    fVar4 = *(float *)((int)pvVar2 + 0x28) + PUN(float,param_1);
  }
  *(undefined4 *)((int)pvVar2 + 0x24) = *(undefined4 *)((int)pvVar2 + 0x24);
  *(float *)((int)pvVar2 + 0x28) = fVar4;
  *(undefined4 *)((int)pvVar2 + 0x2c) = *(undefined4 *)((int)pvVar2 + 0x2c);
  *(undefined4 *)((int)pvVar2 + 0x34) = 0;
  return 0;
}
#undef local_30
#undef local_38
#undef local_48

#endif


/* ---- 0x00491650  Walker_ReplanPath ---- */
void Walker_ReplanPath(int param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  unsigned char _frame[0x2f0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  void *this;
  int iVar2;
  uint *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  #define local_2d8 (*(uint *)(_frame + (0x2f0 - 0x2d8)))
  #define local_2d4 (*(uint *)(_frame + (0x2f0 - 0x2d4)))
  #define local_2d0 (*(uint *)(_frame + (0x2f0 - 0x2d0)))
  #define local_2cc (*(uint *)(_frame + (0x2f0 - 0x2cc)))
  #define local_2c8 (*(uint *)(_frame + (0x2f0 - 0x2c8)))
  #define auStack_1b0 (*(undefined4 (*)[18])(_frame + (0x2f0 - 0x1b0)))
  #define local_168 (*(uint *)(_frame + (0x2f0 - 0x168)))
  #define local_164 (*(uint *)(_frame + (0x2f0 - 0x164)))
  #define local_160 (*(uint *)(_frame + (0x2f0 - 0x160)))
  
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xfffffffe;
  iVar2 = *(int *)(*(int *)(param_1 + 0xa4) + 0x1b4);
  if ((iVar2 != 0) && (g_pSectorList != (void *)0x0)) {
    this = (void *)SectorList_FindNearestPoint(param_2,0x1000);
    if (this != (void *)0x0) {
      Sector_ClampPoint(this,param_2);
    }
    iVar2 = Planner_PlanPath(iVar2,param_2,1);
    if (iVar2 != 0) {
      iVar2 = Planner_GetPath(&local_2d4);
      if (0 < iVar2) {
        puVar3 = &local_2d0;
        iVar5 = iVar2;
        do {
          puVar1 = (uint *)((local_2d4 - (int)&local_2d0) + (int)puVar3);
          iVar5 = iVar5 + -1;
          *puVar3 = *puVar1;
          puVar3[1] = puVar1[1];
          puVar3[2] = puVar1[2];
          puVar3 = puVar3 + 3;
        } while (iVar5 != 0);
      }
      iVar2 = Walker_AvoidActorPath(param_1,param_4,&local_2d0,iVar2,&local_168);
      *(int *)(*(int *)(param_1 + 0xa4) + 0x44) = iVar2;
      *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x1b0) = 1;
      if (0 < iVar2) {
        iVar5 = 0x48;
        iVar6 = iVar2;
        do {
          puVar4 = (undefined4 *)(*(int *)(param_1 + 0xa4) + iVar5);
          iVar6 = iVar6 + -1;
          *puVar4 = *(undefined4 *)((int)auStack_1b0 + iVar5);
          puVar4[1] = *(undefined4 *)((int)auStack_1b0 + iVar5 + 4);
          puVar4[2] = *(undefined4 *)((int)auStack_1b0 + iVar5 + 8);
          iVar5 = iVar5 + 0xc;
        } while (iVar6 != 0);
      }
      iVar5 = *(int *)(param_1 + 0xa4);
      puVar4 = (undefined4 *)(iVar5 + (*(int *)(iVar5 + 0x1b0) + 6) * 0xc);
      *(undefined4 *)(iVar5 + 0x2c) = *puVar4;
      *(undefined4 *)(iVar5 + 0x30) = puVar4[1];
      *(undefined4 *)(iVar5 + 0x34) = puVar4[2];
      if (1 < iVar2) {
        *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 1;
      }
    }
    iVar2 = *(int *)(param_1 + 0xa4);
    *(undefined4 *)(iVar2 + 0x38) = *param_3;
    *(undefined4 *)(iVar2 + 0x3c) = param_3[1];
    *(undefined4 *)(iVar2 + 0x40) = param_3[2];
  }
  return;
}
#undef auStack_1b0
#undef local_160
#undef local_164
#undef local_168
#undef local_2c8
#undef local_2cc
#undef local_2d0
#undef local_2d4
#undef local_2d8


/* ---- 0x004917e0  Walker_AvoidActorPath ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_124 */

uint Walker_AvoidActorPath
               (void *param_1,void *param_2,undefined4 *param_3,uint param_4,float *param_5)

{
  unsigned char _frame[0x140] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[336] __attribute__((aligned(16)));  /* the original frame below the return address */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  float *pfVar9;
  void *this;
  float fVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  float *pfVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  uint *puVar18;
  float *pfVar19;
  float *pfVar20;
  float fVar21;
  float *pfVar22;
  float in_stack_fffffed0;
  float bz0;
  float bx1;
  #define local_124 (*(uint *)(_frame + (0x140 - 0x124)))
  float fVar23;
  #define local_104 (*(float *)(_frame + (0x140 - 0x104)))
  #define local_100 (*(uint *)(_frame + (0x140 - 0x100)))
  #define local_fc (*(float *)(_frame + (0x140 - 0xfc)))
  #define local_f8 (*(float *)(_frame + (0x140 - 0xf8)))
  #define local_f4 (*(float *)(_frame + (0x140 - 0xf4)))
  #define local_f0 (*(uint *)(_frame + (0x140 - 0xf0)))
  #define local_ec (*(uint *)(_frame + (0x140 - 0xec)))
  #define local_e8 (*(float *)(_frame + (0x140 - 0xe8)))
  #define local_e4 (*(float (*)[2])(_frame + (0x140 - 0xe4)))
  #define local_dc (*(float *)(_frame + (0x140 - 0xdc)))
  #define local_d8 (*(uint *)(_frame + (0x140 - 0xd8)))
  #define local_d4 (*(float *)(_frame + (0x140 - 0xd4)))
  #define local_d0 (*(float *)(_frame + (0x140 - 0xd0)))
  #define local_cc (*(float (*)[2])(_frame + (0x140 - 0xcc)))
  #define local_c4 (*(uint *)(_frame + (0x140 - 0xc4)))
  #define local_c0 (*(float *)(_frame + (0x140 - 0xc0)))
  #define local_bc (*(uint *)(_frame + (0x140 - 0xbc)))
  #define local_b8 (*(uint *)(_frame + (0x140 - 0xb8)))
  #define local_b4 (*(float *)(_frame + (0x140 - 0xb4)))
  #define local_b0 (*(uint *)(_frame + (0x140 - 0xb0)))
  #define local_ac (*(float (*)[3])(_frame + (0x140 - 0xac)))
  #define local_a0 (*(float (*)[3])(_frame + (0x140 - 0xa0)))
  #define local_94 (*(float (*)[3])(_frame + (0x140 - 0x94)))
  #define local_88 (*(float (*)[3])(_frame + (0x140 - 0x88)))
  #define local_7c (*(float (*)[3])(_frame + (0x140 - 0x7c)))
  #define local_70 (*(float (*)[3])(_frame + (0x140 - 0x70)))
  #define local_64 (*(float (*)[3])(_frame + (0x140 - 0x64)))
  #define local_58 (*(float (*)[2])(_frame + (0x140 - 0x58)))
  #define local_50 (*(uint *)(_frame + (0x140 - 0x50)))
  #define local_4c (*(float *)(_frame + (0x140 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x140 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x140 - 0x44)))
  #define local_1c (*(uint *)(_frame + (0x140 - 0x1c)))
  #define local_c (*(float (*)[3])(_frame + (0x140 - 0xc)))
  
  local_100 = 0;
  if (param_2 == (void *)0x0) {
    puVar7 = param_3;
    uVar15 = param_4;
    if ((int)param_4 < 1) {
      return 0;
    }
    do {
      puVar8 = puVar7 + 3;
      uVar15 = uVar15 - 1;
      *(undefined4 *)((int)param_5 + (-0xc - (int)param_3) + (int)puVar8) = *puVar7;
      *(undefined4 *)((int)param_5 + (-8 - (int)param_3) + (int)puVar8) = puVar7[1];
      *(undefined4 *)((int)param_5 + (-4 - (int)param_3) + (int)puVar8) = puVar7[2];
      puVar7 = puVar8;
    } while (uVar15 != 0);
    return param_4;
  }
  iVar12 = *(int *)(*(int *)(*(int *)((int)param_1 + 0xa0) + 4) + 4);
  local_104 = *(float *)(*(int *)((int)param_1 + 0xa4) + 0x3f4) * *(float *)(iVar12 + 0x5c);
  pfVar9 = Actor_GetFrame(param_1);
  Vec3_Copy(local_c,(float *)(iVar12 + 0x78),pfVar9);
  bx1 = *(float *)(*(int *)(*(int *)((int)param_2 + 0xa0) + 4) + 4);
  pfVar9 = Actor_GetFrame(param_2);
  Vec3_Sub(local_88,(float *)(PUN(int,(float)bx1) + 0x78),pfVar9);
  pfVar9 = Actor_GetFrame(param_2);
  Vec3_Copy(&local_e8,(float *)(PUN(int,(float)bx1) + 0x78),pfVar9);
  iVar12 = *(int *)((int)param_2 + 0xa4);
  local_7c[0] = *(float *)(PUN(int,(float)bx1) + 0x60) * *(float *)(iVar12 + 0x3f4) - local_104;
  pfVar9 = (float *)(param_3 + param_4 * 3 + -3);
  local_7c[1] = *(float *)(PUN(int,(float)bx1) + 100) * *(float *)(iVar12 + 0x3f4) - local_104;
  local_7c[2] = *(float *)(PUN(int,(float)bx1) + 0x68) * *(float *)(iVar12 + 0x3f4) - local_104;
  Actor_GetFrame(param_2);
  pfVar14 = local_7c;
  pfVar19 = (float *)(_stkneg + 28);
  for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
    *pfVar19 = *pfVar14;
    pfVar14 = pfVar14 + 1;
    pfVar19 = pfVar19 + 1;
  }
  ((code *)Collision_PushOutOfBox)(pfVar9);
  Actor_GetFrame(param_2);
  pfVar14 = local_7c;
  pfVar19 = (float *)(_stkneg + 28);
  for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
    *pfVar19 = *pfVar14;
    pfVar14 = pfVar14 + 1;
    pfVar19 = pfVar19 + 1;
  }
  ((code *)Collision_PushOutOfBox)(param_3);
  local_d0 = *pfVar9;
  local_cc[0] = pfVar9[1];
  local_cc[1] = pfVar9[2];
  iVar12 = ((code *)SectorList_FindByPoint)();
  if (iVar12 == 0) {
    return 0;
  }
  uVar15 = 0;
  local_f8 = PUN(float,(param_4 - 1));
  local_f0 = 0;
  if (0 < PUN(int,(float)local_f8)) {
    pfVar14 = (float *)(param_3 + 2);
    pfVar9 = param_5;
    do {
      local_64[0] = local_e8 + pfVar14[-2];
      local_fc = PUN(float,(pfVar9 + 3));
      uVar15 = local_100 + 1;
      local_64[1] = pfVar14[-1] + local_e4[0];
      local_64[2] = local_e4[1] + *pfVar14;
      local_a0[0] = pfVar14[1] + local_e8;
      local_a0[1] = pfVar14[2] + local_e4[0];
      local_a0[2] = pfVar14[3] + local_e4[1];
      *pfVar9 = pfVar14[-2];
      pfVar9[1] = pfVar14[-1];
      pfVar9[2] = *pfVar14;
      Actor_GetFrame(param_2);
      pfVar9 = local_7c;
      pfVar19 = (float *)(_stkneg + 32);
      for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
        *pfVar19 = *pfVar9;
        pfVar9 = pfVar9 + 1;
        pfVar19 = pfVar19 + 1;
      }
      iVar12 = ((code *)Collision_SegmentHitsBox)(local_64,local_a0);
      local_100 = uVar15;
      if (iVar12 != 0) {
        pfVar9 = Actor_GetFrame(param_2);
        Vec3_Sub(local_58,(float *)&DAT_008ca320,pfVar9);
        this = (void *)((code *)SectorList_FindNearestPoint)();
        Sector_SnapToPlane(this,local_58);
        Actor_GetFrame(param_2);
        bz0 = 6.713914e-39;
        ((code *)Collision_BoxCorners)();
        puVar18 = &local_1c;
        pfVar9 = &local_4c;
        local_f4 = 5.60519e-45;
        do {
          *puVar18 = 0;
          local_a0[0] = local_e8 + *pfVar9;
          local_a0[1] = pfVar9[1] + local_e4[0];
          local_a0[2] = local_e4[1] + pfVar9[2];
          Actor_GetFrame(param_2);
          pfVar14 = local_88;
          pfVar19 = local_7c;
          pfVar20 = (float *)(_stkneg + 32);
          for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
            *pfVar20 = *pfVar19;
            pfVar19 = pfVar19 + 1;
            pfVar20 = pfVar20 + 1;
          }
          iVar12 = ((code *)Collision_SegmentHitsBox)(local_64,local_a0);
          if ((iVar12 == 0) && (iVar12 = ((code *)Planner_PlanPath)(), iVar12 != 0)) {
            *puVar18 = 1;
          }
          pfVar9 = pfVar9 + 3;
          puVar18 = puVar18 + 1;
          local_f4 = PUN(float,(PUN(int,(float)local_f4) + -1));
        } while (local_f4 != 0.0);
        fVar10 = (float)((code *)Collision_PickDetour)();
        if (fVar10 == -NAN) {
          return uVar15;
        }
        ((code *)Planner_PlanPath)();
        iVar12 = ((code *)Planner_GetPath)();
        if (0 < iVar12) {
          local_100 = uVar15 + iVar12;
          pfVar9 = param_5 + uVar15 * 3;
          pfVar19 = PUN(float *,(float)local_fc);
          do {
            iVar12 = iVar12 + -1;
            *pfVar9 = *pfVar19;
            pfVar9[1] = pfVar19[1];
            pfVar9[2] = pfVar19[2];
            pfVar9 = pfVar9 + 3;
            pfVar19 = pfVar19 + 3;
          } while (iVar12 != 0);
        }
        pfVar19 = &local_e8;
        (&local_1c)[PUN(int,(float)fVar10)] = 0;
        local_f4 = PUN(float,(param_5 + local_100 * 3));
        pfVar9 = (float *)(PUN(int,(float)local_f4) + -0xc);
        fVar23 = 6.714508e-39;
        pfVar11 = Actor_GetFrame(param_2);
        pfVar20 = local_7c;
        pfVar22 = (float *)(_stkneg + 28);
        for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
          *pfVar22 = *pfVar20;
          pfVar20 = pfVar20 + 1;
          pfVar22 = pfVar22 + 1;
        }
        iVar12 = Collision_PointInBox
                           (pfVar9,&local_d0,local_88,PUN(float,pfVar14),in_stack_fffffed0,bz0,bx1,
                            6.714319e-39,fVar23,pfVar11,pfVar19);
        if (iVar12 != 0) {
          iVar12 = ((code *)Planner_GetPath)();
          if (iVar12 < 1) {
            return local_100;
          }
          uVar15 = local_100 + iVar12;
          do {
            iVar12 = iVar12 + -1;
            *PUN(float *,(float)local_f4) = *PUN(float *,(float)local_fc);
            *(float *)(PUN(int,(float)local_f4) + 4) = *(float *)(PUN(int,(float)local_fc) + 4);
            *(float *)(PUN(int,(float)local_f4) + 8) = *(float *)(PUN(int,(float)local_fc) + 8);
            local_f4 = PUN(float,(PUN(int,(float)local_f4) + 0xc));
            local_fc = PUN(float,(PUN(int,(float)local_fc) + 0xc));
          } while (iVar12 != 0);
          return uVar15;
        }
        uVar15 = (int)(PUN(int,(float)fVar10) + 3U) >> 0x1f;
        fVar23 = PUN(float,(((PUN(int,(float)fVar10) + 3U ^ uVar15) - uVar15 & 3 ^ uVar15) - uVar15));
        uVar15 = (int)(PUN(int,(float)fVar10) + 5U) >> 0x1f;
        fVar21 = PUN(float,(((PUN(int,(float)fVar10) + 5U ^ uVar15) - uVar15 & 3 ^ uVar15) - uVar15));
        local_f0 = ((code *)Planner_PlanPath)();
        iVar12 = ((code *)Planner_PlanPath)();
        if (iVar12 != 0) {
          if (local_f0 == 0) goto LAB_00491fa5;
          local_104 = *pfVar9 - (&local_4c)[PUN(int,(float)fVar23) * 3];
          fVar2 = *(float *)(PUN(int,(float)local_f4) + -8) - PUN(float,(&local_48)[PUN(int,(float)fVar23) * 3]);
          fVar3 = *(float *)(PUN(int,(float)local_f4) + -4) - PUN(float,(&local_44)[PUN(int,(float)fVar23) * 3]);
          fVar4 = PUN(float,(&local_48)[PUN(int,(float)fVar23) * 3]) - local_cc[0];
          fVar5 = PUN(float,(&local_44)[PUN(int,(float)fVar23) * 3]) - local_cc[1];
          fVar6 = *(float *)(PUN(int,(float)local_f4) + -8) - PUN(float,(&local_48)[PUN(int,(float)fVar21) * 3]);
          local_f8 = *(float *)(PUN(int,(float)local_f4) + -4) - PUN(float,(&local_44)[PUN(int,(float)fVar21) * 3]);
          local_fc = PUN(float,(&local_48)[PUN(int,(float)fVar21) * 3]) - local_cc[0];
          fVar1 = PUN(float,(&local_44)[PUN(int,(float)fVar21) * 3]) - local_cc[1];
          if (fVar1 * fVar1 +
              local_fc * local_fc +
              ((&local_4c)[PUN(int,(float)fVar21) * 3] - local_d0) * ((&local_4c)[PUN(int,(float)fVar21) * 3] - local_d0)
              + local_f8 * local_f8 +
                fVar6 * fVar6 +
                (*pfVar9 - (&local_4c)[PUN(int,(float)fVar21) * 3]) * (*pfVar9 - (&local_4c)[PUN(int,(float)fVar21) * 3])
              <= fVar5 * fVar5 +
                 fVar4 * fVar4 +
                 ((&local_4c)[PUN(int,(float)fVar23) * 3] - local_d0) *
                 ((&local_4c)[PUN(int,(float)fVar23) * 3] - local_d0) +
                 fVar3 * fVar3 + fVar2 * fVar2 + local_104 * local_104) {
            local_f0 = 0;
          }
          else {
            iVar12 = 0;
          }
        }
        if (local_f0 != 0) {
          local_f8 = -NAN;
          local_104 = fVar23;
        }
LAB_00491fa5:
        if (iVar12 != 0) {
          local_f8 = 1.4013e-45;
          local_104 = fVar21;
        }
        if (local_104 == fVar10) {
          return local_100;
        }
        while( true ) {
          ((code *)Planner_PlanPath)();
          pfVar9 = (float *)((code *)Planner_GetPath)();
          iVar12 = 0;
          if (0 < (int)pfVar9 + -1) {
            iVar17 = 0;
            do {
              local_ac[0] = local_e8 + *(float *)(PUN(int,(float)local_fc) + iVar17);
              local_ac[1] = *(float *)(PUN(int,(float)local_fc) + 4 + iVar17) + local_e4[0];
              local_ac[2] = *(float *)(PUN(int,(float)local_fc) + 8 + iVar17) + local_e4[1];
              local_94[0] = *(float *)(PUN(int,(float)local_fc) + 0xc + iVar17) + local_e8;
              local_94[1] = *(float *)(PUN(int,(float)local_fc) + 0x10 + iVar17) + local_e4[0];
              local_94[2] = *(float *)(PUN(int,(float)local_fc) + 0x14 + iVar17) + local_e4[1];
              Actor_GetFrame(param_2);
              pfVar14 = local_7c;
              pfVar19 = (float *)(_stkneg + 32);
              for (iVar13 = 6; iVar13 != 0; iVar13 = iVar13 + -1) {
                *pfVar19 = *pfVar14;
                pfVar14 = pfVar14 + 1;
                pfVar19 = pfVar19 + 1;
              }
              pfVar14 = local_88;
              iVar13 = ((code *)Collision_SegmentHitsBox)(local_ac,local_94);
              if (iVar13 != 0) {
                return 0;
              }
              iVar12 = iVar12 + 1;
              iVar17 = iVar17 + 0xc;
            } while (iVar12 < (int)pfVar9 + -1);
          }
          if (0 < (int)pfVar9) {
            local_100 = local_100 + (int)pfVar9;
            puVar7 = PUN(undefined4 *,(float)local_fc);
            pfVar19 = pfVar9;
            do {
              pfVar19 = (float *)((int)pfVar19 + -1);
              *PUN(undefined4 *,(float)local_f4) = *puVar7;
              *(undefined4 *)(PUN(int,(float)local_f4) + 4) = puVar7[1];
              *(undefined4 *)(PUN(int,(float)local_f4) + 8) = puVar7[2];
              local_f4 = PUN(float,(PUN(int,(float)local_f4) + 0xc));
              puVar7 = puVar7 + 3;
            } while (pfVar19 != (float *)0x0);
          }
          pfVar19 = &local_e8;
          local_f4 = PUN(float,(param_5 + local_100 * 3));
          fVar23 = 6.715863e-39;
          pfVar11 = Actor_GetFrame(param_2);
          pfVar20 = local_7c;
          pfVar22 = (float *)(_stkneg + 28);
          for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
            *pfVar22 = *pfVar20;
            pfVar20 = pfVar20 + 1;
            pfVar22 = pfVar22 + 1;
          }
          iVar12 = Collision_PointInBox
                             ((float *)(PUN(int,(float)local_f4) + -0xc),&local_d0,local_88,PUN(float,pfVar14),
                              in_stack_fffffed0,bz0,bx1,6.715423e-39,fVar23,pfVar11,pfVar19);
          if (iVar12 != 0) break;
          uVar15 = PUN(int,(float)local_f8) + 4 + PUN(int,(float)local_104);
          uVar16 = (int)uVar15 >> 0x1f;
          local_104 = PUN(float,(((uVar15 ^ uVar16) - uVar16 & 3 ^ uVar16) - uVar16));
          if (local_104 == fVar10) {
            return local_100;
          }
        }
        iVar12 = ((code *)Planner_GetPath)();
        iVar17 = 0;
        local_f8 = 0.0;
        if (0 < iVar12 + -1) {
          do {
            local_94[0] = local_e8 + *(float *)((int)pfVar9 + iVar17);
            local_94[1] = *(float *)((int)pfVar9 + iVar17 + 4) + local_e4[0];
            local_94[2] = *(float *)((int)pfVar9 + iVar17 + 8) + local_e4[1];
            local_ac[0] = *(float *)((int)pfVar9 + iVar17 + 0xc) + local_e8;
            local_ac[1] = *(float *)((int)pfVar9 + iVar17 + 0x10) + local_e4[0];
            local_ac[2] = *(float *)((int)pfVar9 + iVar17 + 0x14) + local_e4[1];
            Actor_GetFrame(param_2);
            pfVar14 = local_7c;
            pfVar19 = (float *)(_stkneg + 32);
            for (iVar13 = 6; iVar13 != 0; iVar13 = iVar13 + -1) {
              *pfVar19 = *pfVar14;
              pfVar14 = pfVar14 + 1;
              pfVar19 = pfVar19 + 1;
            }
            iVar13 = ((code *)Collision_SegmentHitsBox)(local_94,local_ac);
            if (iVar13 != 0) {
              return 0;
            }
            local_f8 = PUN(float,(PUN(int,(float)local_f8) + 1));
            iVar17 = iVar17 + 0xc;
          } while (PUN(int,(float)local_f8) < iVar12 + -1);
        }
        uVar15 = local_100;
        if (0 < iVar12) {
          uVar15 = local_100 + iVar12;
          pfVar14 = param_5 + local_100 * 3;
          do {
            iVar12 = iVar12 + -1;
            *pfVar14 = *pfVar9;
            pfVar14[1] = pfVar9[1];
            pfVar14[2] = pfVar9[2];
            pfVar14 = pfVar14 + 3;
            pfVar9 = pfVar9 + 3;
          } while (iVar12 != 0);
        }
        return uVar15;
      }
      uVar15 = local_f0 + 1;
      pfVar14 = pfVar14 + 3;
      pfVar9 = PUN(float *,(float)local_fc);
      local_f0 = uVar15;
    } while ((int)uVar15 < PUN(int,(float)local_f8));
  }
  pfVar9 = (float *)(param_3 + uVar15 * 3);
  param_5 = param_5 + local_100 * 3;
  *param_5 = *pfVar9;
  param_5[1] = pfVar9[1];
  param_5[2] = pfVar9[2];
  return local_100 + 1;
}
#undef local_100
#undef local_104
#undef local_124
#undef local_1c
#undef local_44
#undef local_48
#undef local_4c
#undef local_50
#undef local_58
#undef local_64
#undef local_70
#undef local_7c
#undef local_88
#undef local_94
#undef local_a0
#undef local_ac
#undef local_b0
#undef local_b4
#undef local_b8
#undef local_bc
#undef local_c
#undef local_c0
#undef local_c4
#undef local_cc
#undef local_d0
#undef local_d4
#undef local_d8
#undef local_dc
#undef local_e4
#undef local_e8
#undef local_ec
#undef local_f0
#undef local_f4
#undef local_f8
#undef local_fc

#endif


/* ---- 0x00494880  Walker_SetFadeTime ---- */
/* Lua SetWalkSystemFadeTime */

void __cdecl Walker_SetFadeTime(int ms)

{
  g_nChoreFadeMs = ms;
  return;
}

/* ---- 0x004a8200  Walker_Create ---- */
/* Allocates the 0x60-byte walker record */

void * __thiscall Walker_Create(void *this,float radius)

{
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  Angles_ToMatrix((int)this + 0xc,this,this);
  *(undefined4 *)((int)this + 0x48) = 0x3f800000;
  *(float *)((int)this + 0x3c) = radius;
  *(undefined4 *)((int)this + 0x5c) = 0;
  *(undefined4 *)((int)this + 0x40) = 0;
  *(undefined4 *)((int)this + 0x50) = 0;
  *(undefined4 *)((int)this + 0x44) = 0;
  *(undefined4 *)((int)this + 0x4c) = 0;
  *(undefined4 *)((int)this + 0x58) = 0;
  *(undefined4 *)((int)this + 0x54) = 0;
  *(uint *)((int)this + 0x58) = UINT_008d086c;
  if (UINT_008d086c != 0) {
    *(void **)(UINT_008d086c + 0x54) = this;
  }
  UINT_008d086c = (uint)this;
  return this;
}

/* ---- 0x004a8270  Walker_Destroy ---- */
void __fastcall Walker_Destroy(int param_1)

{
  if (param_1 == UINT_008d086c) {
    UINT_008d086c = *(uint *)(param_1 + 0x58);
  }
  if (*(int *)(param_1 + 0x54) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x58) = *(undefined4 *)(param_1 + 0x58);
  }
  if (*(int *)(param_1 + 0x58) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x54) = *(undefined4 *)(param_1 + 0x54);
  }
  return;
}

/* ---- 0x004a82a0  Walker_GetAngles ---- */
/* Converts the walker's 3x3 frame to pitch/yaw/roll in g_vWalkerAngles */

undefined * __fastcall Walker_GetAngles(int param_1)

{
  Matrix_ToAngles(param_1 + 0xc,&DAT_008cf250);
  return &DAT_008cf250;
}

/* ---- 0x004a82c0  Walker_ReattachToSet ---- */
/* Called after Actor_PutInSet when the actor has a walker so it picks up the new set's sectors */

void __fastcall Walker_ReattachToSet(void *param_1)

{
  void *this;
  int iVar1;
  
  this = (void *)SectorList_FindNearestPoint(param_1,0x1000);
  *(void **)((int)param_1 + 0x5c) = this;
  if (this != (void *)0x0) {
    iVar1 = Sector_ContainsPoint(this,param_1,1);
    if (iVar1 == 0) {
      Sector_ClampPoint(*(void **)((int)param_1 + 0x5c),(int)param_1);
      Walker_SetPosition(param_1,param_1);
    }
    Walker_SetSectorFrame(param_1,*(int *)((int)param_1 + 0x5c));
  }
  return;
}

/* ---- 0x004a8310  Walker_SetPosition ---- */
void __thiscall Walker_SetPosition(void *this,float *pos)

{
  *(float *)this = *pos;
  *(float *)((int)this + 4) = pos[1];
  *(float *)((int)this + 8) = pos[2];
  *(float *)((int)this + 0x30) = *pos;
  *(float *)((int)this + 0x34) = pos[1];
  *(float *)((int)this + 0x38) = pos[2];
  return;
}

/* ---- 0x004a8350  Walker_RotateVector ---- */
void __thiscall Walker_RotateVector(void *this,float *vec)

{
  Vec3_Rotate3x3(vec,(float *)((int)this + 0xc));
  return;
}

/* ---- 0x004a8370  Walker_ToLocalSpace ---- */
/* Rotates a world vector into the current walker's frame */

void __thiscall Walker_ToLocalSpace(void *this,float *vec)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  *vec = *vec - *(float *)this;
  vec[1] = vec[1] - *(float *)((int)this + 4);
  vec[2] = vec[2] - *(float *)((int)this + 8);
  Vec3_TransformTo(&local_c,vec,(float *)((int)this + 0xc));
  *vec = local_c;
  vec[1] = local_8;
  vec[2] = local_4;
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a83c0  Walker_TurnHeading ---- */
void __thiscall Walker_TurnHeading(void *this,float angle)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *vec;
  #define local_30 (*(float (*)[12])(_frame + (0x40 - 0x30)))
  
  Matrix_AxisAngle(local_30,(int)this + 0x24,angle);
  vec = (float *)((int)this + 0x18);
  Vec3_Transform(vec,local_30);
  *vec = *vec + *(float *)((int)this + 0x30);
  *(float *)((int)this + 0x1c) = *(float *)((int)this + 0x34) + *(float *)((int)this + 0x1c);
  *(float *)((int)this + 0x20) = *(float *)((int)this + 0x38) + *(float *)((int)this + 0x20);
  if (*(void **)((int)this + 0x5c) != (void *)0x0) {
    Sector_SnapToPlane(*(void **)((int)this + 0x5c),vec);
  }
  *vec = *vec - *(float *)((int)this + 0x30);
  *(float *)((int)this + 0x1c) = *(float *)((int)this + 0x1c) - *(float *)((int)this + 0x34);
  *(float *)((int)this + 0x20) = *(float *)((int)this + 0x20) - *(float *)((int)this + 0x38);
  Walker_RebuildRightVector((int)this);
  return;
}
#undef local_30


/* ---- 0x004a8450  Walker_TurnToPoint ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
float __thiscall Walker_TurnToPoint(void *this,float *point,float maxTurn)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_c = *point;
  local_8 = point[1];
  local_4 = PUN(uint,(float)point[2]);
  if (*(void **)((int)this + 0x5c) != (void *)0x0) {
    Sector_FixPlaneCoordinate(*(void **)((int)this + 0x5c),(int)&local_c);
  }
  Walker_ToLocalSpace(this,&local_c);
  Vec3_Normalize(&local_c);
  fVar1 = Math_AsinDegreesSeries(local_8);
  point = PUN(float *,(float)(90.0 - fVar1));
  if (maxTurn < PUN(float,point)) {
    point = PUN(float *,(float)maxTurn);
  }
  if (0.0 < local_c) {
    point = PUN(float *,(float)(PUN(float,point) * -1.0));
  }
  Walker_TurnHeading(this,PUN(float,point));
  return PUN(float,point);
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a85b0  Walker_SetConstraint ---- */
void __thiscall Walker_SetConstraint(void *this,int a1)

{
  float *pfVar1;
  
  *(undefined4 *)((int)this + 0x50) = 0;
  if ((*(void **)((int)this + 0x5c) != (void *)0x0) && (a1 != 0)) {
    pfVar1 = Sector_EdgeFollowDirection(*(void **)((int)this + 0x5c),this);
    if (pfVar1 != (float *)0x0) {
      *(float *)((int)this + 0x44) = *pfVar1;
      *(float *)((int)this + 0x48) = pfVar1[1];
      *(float *)((int)this + 0x4c) = pfVar1[2];
      *(float *)((int)this + 0x18) = *pfVar1;
      *(float *)((int)this + 0x1c) = pfVar1[1];
      *(float *)((int)this + 0x20) = pfVar1[2];
      Walker_RebuildRightVector((int)this);
      *(undefined4 *)((int)this + 0x50) = 1;
    }
  }
  return;
}

/* ---- 0x004a8610  Walker_WalkSectors ---- */
/* WARNING: Variable defined which should be unmapped: local_48 */
/* Walker_WalkSectors: the per-frame walk of an actor over the walk sectors (target-inside test with
   tolerance, exit point of the edge, neighbour lookup with the current sector deactivated, 0.02 cap
   into the new sector, reflection turn only when |angle| < reflect and not against a held turn
   key). See autorun/NAV_PLAN.md and COLLISION_FIX_PLAN.md. */

undefined * __thiscall Walker_WalkSectors(void *this,float step,int turnLeftOk,int turnRightOk)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *this_00;
  int iVar1;
  undefined *puVar2;
  float fVar3;
  #define local_48 (*(float *)(_frame + (0x60 - 0x48)))
  #define local_34 (*(float *)(_frame + (0x60 - 0x34)))
  #define local_30 (*(float *)(_frame + (0x60 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x60 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x60 - 0x28)))
  #define local_24 (*(float *)(_frame + (0x60 - 0x24)))
  #define local_20 (*(float *)(_frame + (0x60 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x60 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x60 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x60 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x60 - 0x10)))
  #define local_c (*(float *)(_frame + (0x60 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x60 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x60 - 0x4)))
  
  puVar2 = (undefined *)0x0;
  if (UINT_008d0870 == 0) {
    *(float *)((int)this + 0x40) = step;
  }
  UINT_008d0870 = UINT_008d0870 + 1;
  if (*(int *)((int)this + 0x50) != 0) {
    fVar3 = Vec3_Dot2((float *)((int)this + 0xc),(float *)((int)this + 0x44));
    fVar3 = Math_AsinDegreesSeries(fVar3);
    local_48 = (90.0 - fVar3) - 90.0;
    fVar3 = local_48;
    if (local_48 < 0.0) {
      fVar3 = -local_48;
    }
    if (*(float *)((int)this + 0x3c) < fVar3) {
      return (undefined *)0x0;
    }
    fVar3 = Vec3_Dot2((float *)((int)this + 0x18),(float *)((int)this + 0x44));
    if (fVar3 <= 0.0) {
      local_48 = -local_48;
    }
    Walker_TurnHeading(this,local_48);
  }
  local_30 = 0.0;
  local_2c = PUN(uint,(float)step);
  local_28 = 0;
  Walker_RotateVector(this,&local_30);
  if ((*(void **)((int)this + 0x5c) == (void *)0x0) ||
     (iVar1 = Sector_ContainsPoint(*(void **)((int)this + 0x5c),&local_30,1), iVar1 != 0)) {
    local_48 = PUN(float,&local_30);
    Walker_SetPosition(this,PUN(float *,(float)local_48));
    UINT_008d0870 = 0;
    return (undefined *)0x1;
  }
  if (8 < (int)UINT_008d0870) {
    UINT_008d0870 = 0;
    return (undefined *)0x0;
  }
  this_00 = *(void **)((int)this + 0x5c);
  local_34 = Sector_FindExitPoint(this_00,(int)this,(int)&local_30,(int)&local_24);
  *(undefined4 *)(*(int *)((int)this + 0x5c) + 0x2c) = 0;
  local_18 = local_24;
  local_14 = local_20;
  local_10 = local_1c;
  Walker_ToLocalSpace(this,&local_18);
  step = step - local_14;
  iVar1 = SectorList_FindByPoint(&local_24,0x1000);
  if (iVar1 == 0) {
    Walker_SetPosition(this,&local_24);
    iVar1 = *(int *)((int)this + 0x5c);
    if ((*(uint *)(iVar1 + 0x24) & 0x100) == 0) {
      fVar3 = local_34;
      if (local_34 < 0.0) {
        fVar3 = -local_34;
      }
      if ((*(float *)((int)this + 0x3c) <= fVar3) || (*(int *)((int)this + 0x50) != 0)) {
        *(float *)((int)this + 0x40) = *(float *)((int)this + 0x40) - step;
      }
      else if (((0.0 < local_34) && (turnLeftOk != 0)) || ((local_34 < 0.0 && (turnRightOk != 0))))
      {
        Walker_TurnHeading(this,local_34);
        *(undefined4 *)((int)this_00 + 0x2c) = 1;
        puVar2 = Walker_WalkSectors(this,step,1,1);
      }
      if (*(int *)((int)this + 0x50) != 0) {
        Walker_TurnHeading(this,local_34);
        *(undefined4 *)((int)this + 0x50) = 1;
        *(undefined4 *)((int)this + 0x44) = *(undefined4 *)((int)this + 0x18);
        *(undefined4 *)((int)this + 0x48) = *(undefined4 *)((int)this + 0x1c);
        *(undefined4 *)((int)this + 0x4c) = *(undefined4 *)((int)this + 0x20);
      }
      *(undefined4 *)((int)this_00 + 0x2c) = 1;
      return puVar2;
    }
    if ((*(int *)(iVar1 + 0x78) + 1) % *(int *)(iVar1 + 0x34) != *(int *)(iVar1 + 0x74)) {
      iVar1 = *(int *)(iVar1 + 0x38 + *(int *)(iVar1 + 0x78) * 4);
      local_c = *(float *)(iVar1 + 4);
      local_8 = *(uint *)(iVar1 + 8);
      local_4 = *(uint *)(iVar1 + 0xc);
      Walker_ToLocalSpace(this,&local_c);
      if (local_c <= 0.0) {
        if (local_34 < 3.0) {
          local_34 = (local_34 - -90.0) - -90.2;
        }
      }
      else if (3.0 < local_34) {
        local_34 = -90.2 - (90.0 - local_34);
      }
      Walker_TurnHeading(this,local_34);
      puVar2 = Walker_WalkSectors(this,step,1,1);
      *(undefined4 *)((int)this_00 + 0x2c) = 1;
      return puVar2;
    }
    return (undefined *)0x0;
  }
  Walker_SetPosition(this,&local_24);
  *(int *)((int)this + 0x5c) = iVar1;
  Walker_SetSectorFrame(this,iVar1);
  if (0.02 <= step) {
    step = 0.02;
  }
  puVar2 = Walker_WalkSectors(this,step,1,1);
  *(undefined4 *)((int)this_00 + 0x2c) = 1;
  return puVar2;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_4
#undef local_48
#undef local_8
#undef local_c


/* ---- 0x004a89b0  Walker_SetSectorFrame ---- */
void __thiscall Walker_SetSectorFrame(void *this,int a1)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  
  pfVar1 = (float *)((int)this + 0x24);
  pfVar2 = (float *)((int)this + 0x18);
  pfVar3 = (float *)((int)this + 0xc);
  *pfVar1 = *(float *)(a1 + 0x60);
  *(undefined4 *)((int)this + 0x28) = *(undefined4 *)(a1 + 100);
  *(undefined4 *)((int)this + 0x2c) = *(undefined4 *)(a1 + 0x68);
  *pfVar3 = *(float *)((int)this + 0x2c) * *(float *)((int)this + 0x1c) -
            *(float *)((int)this + 0x28) * *(float *)((int)this + 0x20);
  *(float *)((int)this + 0x10) =
       *(float *)((int)this + 0x20) * *pfVar1 -
       *(float *)((int)this + 0x2c) * *(float *)((int)this + 0x18);
  *(float *)((int)this + 0x14) =
       *(float *)((int)this + 0x28) * *pfVar2 - *pfVar1 * *(float *)((int)this + 0x1c);
  Vec3_Normalize(pfVar3);
  *pfVar2 = *(float *)((int)this + 0x28) * *(float *)((int)this + 0x14) -
            *(float *)((int)this + 0x2c) * *(float *)((int)this + 0x10);
  *(float *)((int)this + 0x1c) =
       *pfVar3 * *(float *)((int)this + 0x2c) - *pfVar1 * *(float *)((int)this + 0x14);
  *(float *)((int)this + 0x20) =
       *(float *)((int)this + 0x10) * *pfVar1 - *(float *)((int)this + 0x28) * *pfVar3;
  Vec3_Normalize(pfVar2);
  return;
}

/* ---- 0x004a8a90  Walker_RebuildRightVector ---- */
void __fastcall Walker_RebuildRightVector(int param_1)

{
  float *pfVar1;
  
  pfVar1 = (float *)(param_1 + 0x18);
  Vec3_Normalize(pfVar1);
  *(float *)(param_1 + 0xc) =
       *(float *)(param_1 + 0x1c) * *(float *)(param_1 + 0x2c) -
       *(float *)(param_1 + 0x28) * *(float *)(param_1 + 0x20);
  *(float *)(param_1 + 0x10) =
       *(float *)(param_1 + 0x20) * *(float *)(param_1 + 0x24) -
       *pfVar1 * *(float *)(param_1 + 0x2c);
  *(float *)(param_1 + 0x14) =
       *pfVar1 * *(float *)(param_1 + 0x28) -
       *(float *)(param_1 + 0x1c) * *(float *)(param_1 + 0x24);
  Vec3_Normalize((float *)(param_1 + 0xc));
  return;
}

/* ---- 0x004a8b00  Walker_DrawDebugAxes ---- */
void __thiscall Walker_DrawDebugAxes(void *this,int color)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  local_c = 0.0;
  local_8 = 0;
  local_4 = 0;
  local_18 = 0.0;
  local_14 = 0x3dcccccd;
  local_10 = 0;
  Walker_RotateVector(this,&local_c);
  Walker_RotateVector(this,&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,color,0xffffffff
                    );
  local_c = 0.05;
  local_8 = 0x3d4ccccd;
  local_4 = 0;
  local_18 = 0.0;
  local_14 = 0x3dcccccd;
  local_10 = 0;
  Walker_RotateVector(this,&local_c);
  Walker_RotateVector(this,&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,color,0xffffffff
                    );
  local_c = -0.05;
  local_8 = 0x3d4ccccd;
  local_4 = 0;
  local_18 = 0.0;
  local_14 = 0x3dcccccd;
  local_10 = 0;
  Walker_RotateVector(this,&local_c);
  Walker_RotateVector(this,&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,color,0xffffffff
                    );
  local_c = 0.0;
  local_8 = 0;
  local_4 = 0x3d4ccccd;
  local_18 = 0.0;
  local_14 = 0;
  local_10 = 0;
  Walker_RotateVector(this,&local_c);
  Walker_RotateVector(this,&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,color,0xffffffff
                    );
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a9420  Planner_GetPath ---- */
uint Planner_GetPath(undefined4 *param_1)

{
  *param_1 = &UINT_008cf0b0;
  return UINT_008cf248;
}

/* ---- 0x004a9430  Planner_PlanPath ---- */
undefined4 Planner_PlanPath(undefined4 param_1,uint *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  SectorList_ResetFree();
  UINT_008cf248 = 0;
  iVar2 = SectorList_FindByPoint(param_1,0x1000);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = SectorList_FindByPoint(param_2,0x1000);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = Planner_SearchSectors(param_1,param_2,0);
  uVar1 = UINT_008cf248;
  if (iVar2 != 0) {
    iVar2 = UINT_008cf248 * 3;
    UINT_008cf248 = UINT_008cf248 + 1;
    (&UINT_008cf0b0)[iVar2] = *param_2;
    (&UINT_008cf0b4)[uVar1 * 3] = param_2[1];
    (&UINT_008cf0b8)[uVar1 * 3] = param_2[2];
    if (param_3 != 0) {
      Planner_SmoothPath();
    }
    uVar3 = 1;
  }
  SectorList_ResetFree();
  return uVar3;
}

/* ---- 0x004a94d0  Planner_SearchSectors ---- */
undefined4 Planner_SearchSectors(float *param_1,float *param_2,void *param_3)

{
  unsigned char _frame[0x210] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  #define local_1fc (*(uint *)(_frame + (0x210 - 0x1fc)))
  #define local_1f8 (*(uint *)(_frame + (0x210 - 0x1f8)))
  #define local_1f4 (*(float *)(_frame + (0x210 - 0x1f4)))
  #define local_1f0 (*(float *)(_frame + (0x210 - 0x1f0)))
  #define local_1ec (*(float *)(_frame + (0x210 - 0x1ec)))
  #define local_1e8 (*(uint *)(_frame + (0x210 - 0x1e8)))
  #define local_1e4 (*(uint *)(_frame + (0x210 - 0x1e4)))
  #define local_1e0 (*(undefined1 (*)[480])(_frame + (0x210 - 0x1e0)))
  
  if (0x1d < (int)(UINT_008cf248 + 1)) {
    *(undefined4 *)((int)param_3 + 0x2c) = 0;
    return 1;
  }
  if (param_3 == (void *)0x0) {
    param_3 = (void *)SectorList_FindByPoint(param_1,0x1000);
  }
  uVar1 = UINT_008cf248;
  if (param_3 != (void *)0x0) {
    iVar2 = UINT_008cf248 * 3;
    UINT_008cf248 = UINT_008cf248 + 1;
    (&UINT_008cf0b0)[iVar2] = PUN(uint,(float)*param_1);
    (&UINT_008cf0b4)[uVar1 * 3] = PUN(uint,(float)param_1[1]);
    (&UINT_008cf0b8)[uVar1 * 3] = PUN(uint,(float)param_1[2]);
    iVar2 = Sector_ContainsPoint(param_3,param_2,1);
    if (iVar2 != 0) {
      return 1;
    }
    local_1e8 = UINT_008cf248;
    Sector_FindExitPoint(param_3,(int)param_1,(int)param_2,(int)&local_1f4);
    *(undefined4 *)((int)param_3 + 0x2c) = 0;
    if ((local_1f4 - *param_1) * (local_1f4 - *param_1) +
        (local_1ec - param_1[2]) * (local_1ec - param_1[2]) +
        (local_1f0 - param_1[1]) * (local_1f0 - param_1[1]) <= 0.0001) {
      local_1f8 = 0;
    }
    else {
      local_1f8 = SectorList_FindByPoint(&local_1f4,0x1000);
    }
    if (local_1f8 != 0) {
      iVar2 = Planner_SearchSectors(&local_1f4,param_2,local_1f8);
      if (iVar2 != 0) {
        return 1;
      }
      if (local_1f8 != 0) {
        *(undefined4 *)(local_1f8 + 0x2c) = 0;
      }
    }
    local_1e4 = Planner_CollectSharedCorners(param_3,param_2,local_1e0);
    local_1fc = 0;
    if (0 < (int)local_1e4) {
      puVar4 = local_1e0;
      do {
        iVar2 = SectorList_FindByPoint(puVar4,0x1000);
        if (iVar2 != 0) {
          UINT_008cf248 = local_1e8;
          iVar3 = Planner_PortalPoint(param_3,iVar2,param_2,&local_1f4);
          if ((iVar3 != 0) && (iVar2 = Planner_SearchSectors(&local_1f4,param_2,iVar2), iVar2 != 0))
          {
            return 1;
          }
        }
        local_1fc = local_1fc + 1;
        puVar4 = puVar4 + 0x10;
      } while ((int)local_1fc < (int)local_1e4);
    }
    *(undefined4 *)((int)param_3 + 0x2c) = 1;
    if (local_1f8 != 0) {
      *(undefined4 *)(local_1f8 + 0x2c) = 1;
    }
  }
  return 0;
}
#undef local_1e0
#undef local_1e4
#undef local_1e8
#undef local_1ec
#undef local_1f0
#undef local_1f4
#undef local_1f8
#undef local_1fc


/* ---- 0x004a96f0  Planner_CollectSharedCorners ---- */
uint Planner_CollectSharedCorners(void *param_1,float *param_2,uint *param_3)

{
  unsigned char _frame[0x200] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  void *pvVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  uint *puVar8;
  int *piVar9;
  uint uVar10;
  char *pcVar11;
  bool bVar12;
  #define local_1f0 (*(uint *)(_frame + (0x200 - 0x1f0)))
  #define local_1ec (*(uint *)(_frame + (0x200 - 0x1ec)))
  #define local_1e8 (*(uint *)(_frame + (0x200 - 0x1e8)))
  #define local_1e4 (*(uint *)(_frame + (0x200 - 0x1e4)))
  #define local_1e0 (*(uint *)(_frame + (0x200 - 0x1e0)))
  #define local_1dc (*(uint *)(_frame + (0x200 - 0x1dc)))
  #define local_1d8 (*(uint *)(_frame + (0x200 - 0x1d8)))
  #define local_1d4 (*(uint *)(_frame + (0x200 - 0x1d4)))
  #define local_1d0 (*(uint *)(_frame + (0x200 - 0x1d0)))
  #define local_1cc (*(uint *)(_frame + (0x200 - 0x1cc)))
  #define local_1c8 (*(uint *)(_frame + (0x200 - 0x1c8)))
  #define local_1c4 (*(uint *)(_frame + (0x200 - 0x1c4)))
  
  uVar10 = 0;
  local_1e8 = 0;
  for (pvVar4 = g_pSectorList; pvVar4 != (void *)0x0; pvVar4 = *(void **)((int)pvVar4 + 0x70)) {
    if ((((pvVar4 != param_1) && (*(int *)((int)pvVar4 + 0x2c) != 0)) &&
        ((*(uint *)((int)pvVar4 + 0x24) & 0x1000) != 0)) &&
       (local_1ec = 0, 0 < *(int *)((int)pvVar4 + 0x34))) {
      piVar9 = (int *)((int)pvVar4 + 0x38);
      do {
        iVar5 = Sector_ContainsPoint(param_1,(float *)(*piVar9 + 4),0);
        if (iVar5 != 0) {
          uVar6 = 0;
          if (0 < (int)uVar10) {
            puVar7 = &local_1e0;
            do {
              iVar5 = 0xc;
              bVar12 = true;
              puVar8 = puVar7;
              pcVar11 = (char *)(*piVar9 + 4);
              do {
                if (iVar5 == 0) break;
                iVar5 = iVar5 + -1;
                bVar12 = (char)*puVar8 == *pcVar11;
                puVar8 = (uint *)((int)puVar8 + 1);
                pcVar11 = pcVar11 + 1;
              } while (bVar12);
              uVar10 = local_1e8;
              if (bVar12) break;
              uVar6 = uVar6 + 1;
              puVar7 = puVar7 + 4;
            } while ((int)uVar6 < (int)local_1e8);
          }
          if (uVar6 == uVar10) {
            iVar5 = *piVar9;
            fVar1 = *param_2;
            fVar2 = param_2[1];
            uVar10 = uVar10 + 1;
            fVar3 = param_2[2];
            (&local_1e0)[uVar6 * 4] = PUN(uint,(float)*(float *)(iVar5 + 4));
            (&local_1dc)[uVar6 * 4] = *(uint *)(iVar5 + 8);
            (&local_1d8)[uVar6 * 4] = *(uint *)(iVar5 + 0xc);
            fVar1 = fVar1 - PUN(float,(&local_1e0)[uVar6 * 4]);
            (&local_1d4)[uVar6 * 4] =
                 PUN(uint,(float)((fVar3 - PUN(float,(&local_1d8)[uVar6 * 4])) *
                        (fVar3 - PUN(float,(&local_1d8)[uVar6 * 4])) +
                       (fVar2 - PUN(float,(&local_1dc)[uVar6 * 4])) *
                       (fVar2 - PUN(float,(&local_1dc)[uVar6 * 4])) + fVar1 * fVar1));
            local_1e8 = uVar10;
          }
        }
        local_1ec = local_1ec + 1;
        piVar9 = piVar9 + 1;
      } while ((int)local_1ec < *(int *)((int)pvVar4 + 0x34));
    }
  }
  iVar5 = 1;
  *param_3 = local_1e0;
  param_3[1] = local_1dc;
  param_3[2] = local_1d8;
  param_3[3] = local_1d4;
  if (1 < (int)uVar10) {
    puVar7 = &local_1d0;
    do {
      fVar1 = PUN(float,puVar7[3]);
      uVar6 = iVar5 - 1;
      if (-1 < (int)uVar6) {
        puVar8 = param_3 + iVar5 * 4;
        do {
          if (PUN(float,puVar8[-1]) <= fVar1) break;
          uVar6 = uVar6 - 1;
          *puVar8 = puVar8[-4];
          puVar8[1] = puVar8[-3];
          puVar8[2] = puVar8[-2];
          puVar8[3] = puVar8[-1];
          puVar8 = puVar8 + -4;
        } while (uVar6 < 0x80000000);
      }
      puVar8 = param_3 + (uVar6 + 1) * 4;
      iVar5 = iVar5 + 1;
      *puVar8 = *puVar7;
      puVar8[1] = puVar7[1];
      uVar6 = puVar7[3];
      puVar8[2] = puVar7[2];
      puVar8[3] = uVar6;
      puVar7 = puVar7 + 4;
    } while (iVar5 < (int)uVar10);
  }
  return uVar10;
}
#undef local_1c4
#undef local_1c8
#undef local_1cc
#undef local_1d0
#undef local_1d4
#undef local_1d8
#undef local_1dc
#undef local_1e0
#undef local_1e4
#undef local_1e8
#undef local_1ec
#undef local_1f0


/* ---- 0x004a9920  Planner_PortalPoint ---- */
undefined4 Planner_PortalPoint(void *param_1,void *param_2,float *param_3,undefined4 *param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  iVar5 = 0;
  local_4 = 3.4028235e+38;
  if (0 < *(int *)((int)param_1 + 0x34)) {
    piVar6 = (int *)((int)param_1 + 0x38);
    do {
      iVar4 = Sector_ContainsPoint(param_2,(float *)(*piVar6 + 4),0);
      if (iVar4 != 0) {
        iVar4 = *piVar6;
        fVar3 = *(float *)(iVar4 + 8) - param_3[1];
        fVar1 = *(float *)(iVar4 + 0xc) - param_3[2];
        fVar2 = *(float *)(iVar4 + 4) - *param_3;
        fVar1 = fVar2 * fVar2 + fVar1 * fVar1 + fVar3 * fVar3;
        if (fVar1 < local_4) {
          *param_4 = *(undefined4 *)(iVar4 + 4);
          param_4[1] = *(undefined4 *)(iVar4 + 8);
          param_4[2] = *(undefined4 *)(iVar4 + 0xc);
          local_4 = fVar1;
        }
      }
      iVar5 = iVar5 + 1;
      piVar6 = piVar6 + 1;
    } while (iVar5 < *(int *)((int)param_1 + 0x34));
  }
  iVar5 = 0;
  if (0 < *(int *)((int)param_2 + 0x34)) {
    piVar6 = (int *)((int)param_2 + 0x38);
    do {
      iVar4 = Sector_ContainsPoint(param_1,(float *)(*piVar6 + 4),0);
      if (iVar4 != 0) {
        iVar4 = *piVar6;
        fVar3 = *(float *)(iVar4 + 8) - param_3[1];
        fVar1 = *(float *)(iVar4 + 0xc) - param_3[2];
        fVar2 = *(float *)(iVar4 + 4) - *param_3;
        fVar1 = fVar2 * fVar2 + fVar1 * fVar1 + fVar3 * fVar3;
        if (fVar1 < local_4) {
          *param_4 = *(undefined4 *)(iVar4 + 4);
          param_4[1] = *(undefined4 *)(iVar4 + 8);
          param_4[2] = *(undefined4 *)(iVar4 + 0xc);
          local_4 = fVar1;
        }
      }
      iVar5 = iVar5 + 1;
      piVar6 = piVar6 + 1;
    } while (iVar5 < *(int *)((int)param_2 + 0x34));
  }
  if (local_4 == 3.4028235e+38) {
    return 0;
  }
  return 1;
}
#undef local_4


/* ---- 0x004a9aa0  Planner_SmoothPath ---- */
undefined4 Planner_SmoothPath(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *a1;
  bool bVar1;
  bool bVar2;
  void *this;
  int iVar3;
  int iVar4;
  float *pfVar5;
  uint *puVar6;
  uint uVar7;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  bVar2 = false;
  local_10 = 0;
  if (UINT_008cf248 != 3 && -1 < (int)(UINT_008cf248 - 3)) {
    puVar6 = &UINT_008cf0c8;
    do {
      pfVar5 = (float *)(puVar6 + -3);
      a1 = puVar6 + -6;
      this = (void *)Planner_SharedSector(a1,pfVar5);
      iVar3 = Planner_SharedSector(pfVar5,puVar6);
      if (this == (void *)0x0) {
        return 1;
      }
      if (iVar3 == 0) {
        return 1;
      }
      Sector_FindExitPoint(this,(int)a1,(int)puVar6,(int)&local_c);
      iVar3 = Planner_SharedSector(&local_c,a1);
      iVar4 = Planner_SharedSector(&local_c,puVar6);
      if (((iVar4 != 0) && (iVar3 != 0)) &&
         (0.0025000002 <
          (local_4 - PUN(float,puVar6[-1])) * (local_4 - PUN(float,puVar6[-1])) +
          (local_8 - PUN(float,puVar6[-2])) * (local_8 - PUN(float,puVar6[-2])) +
          (local_c - *pfVar5) * (local_c - *pfVar5))) {
        *pfVar5 = local_c;
        puVar6[-2] = PUN(uint,(float)local_8);
        puVar6[-1] = PUN(uint,(float)local_4);
        bVar2 = true;
      }
      local_10 = local_10 + 1;
      puVar6 = puVar6 + 3;
    } while ((int)local_10 < (int)(UINT_008cf248 - 3));
  }
  if (UINT_008cf248 != 2 && -1 < (int)(UINT_008cf248 - 2)) {
    puVar6 = &UINT_008cf0b4;
    local_14 = 1;
    uVar7 = UINT_008cf248;
    do {
      if (((PUN(float,puVar6[1]) - PUN(float,puVar6[4])) * (PUN(float,puVar6[1]) - PUN(float,puVar6[4])) +
           (PUN(float,*puVar6) - PUN(float,puVar6[3])) * (PUN(float,*puVar6) - PUN(float,puVar6[3])) +
           (PUN(float,puVar6[-1]) - PUN(float,puVar6[2])) * (PUN(float,puVar6[-1]) - PUN(float,puVar6[2])) < 0.0001)
         && (iVar3 = Planner_SharedSector(puVar6 + -1,puVar6 + 2), uVar7 = UINT_008cf248, iVar3 != 0
            )) {
        bVar2 = true;
        uVar7 = UINT_008cf248 - 1;
        UINT_008cf248 = uVar7;
        if ((int)local_14 < (int)uVar7) {
          iVar3 = uVar7 - local_14;
          pfVar5 = (float *)(puVar6 + 2);
          do {
            iVar3 = iVar3 + -1;
            *pfVar5 = pfVar5[3];
            pfVar5[1] = pfVar5[4];
            pfVar5[2] = pfVar5[5];
            pfVar5 = pfVar5 + 3;
          } while (iVar3 != 0);
        }
      }
      puVar6 = puVar6 + 3;
      bVar1 = (int)local_14 < (int)(uVar7 - 2);
      local_14 = local_14 + 1;
    } while (bVar1);
  }
  if (bVar2) {
    Planner_SmoothPath();
  }
  return 1;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a9ca0  Planner_SharedSector ---- */
void * Planner_SharedSector(undefined4 param_1,float *param_2)

{
  void *this;
  int iVar1;
  
  this = (void *)SectorList_FindByPoint(param_1,0x1000);
  while ((this != (void *)0x0 && (iVar1 = Sector_ContainsPoint(this,param_2,1), iVar1 == 0))) {
    *(undefined4 *)((int)this + 0x2c) = 0;
    this = (void *)SectorList_FindByPoint(param_1,0x1000);
  }
  SectorList_ResetFree();
  return this;
}
