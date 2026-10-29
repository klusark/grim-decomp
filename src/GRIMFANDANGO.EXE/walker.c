/* GRIMFANDANGO.EXE :: walker.c
 * functions 0x00491230 .. 0x004a9ca0 (25 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00491230  Walker_UpdateYaw ---- */
/* Walker_UpdateYaw(actor, pos): eases the visible yaw (actor+0x28) toward the walker heading. Done
   (returns 1) when under 0.5 deg. step = rate*frameSec*timescale; if remaining > step, step =
   (remaining - step)*0.1 + step. Rate <= 0 (snap) jumps the whole way and re-negates the rate. */

undefined4 Walker_UpdateYaw(void *param_1,float *param_2)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  void *pvVar3;
  float *pfVar4;
  float10 fVar5;
  undefined4 uVar6;
  #define local_48 (*(float *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(float *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(float *)(_frame + (0x60 - 0x40)))
  #define local_30 (*(float (*)[12])(_frame + (0x60 - 0x30)))
  
  pvVar3 = param_1;
  pfVar4 = Actor_GetFrame(param_1);
  local_48 = pfVar4[3];
  local_44 = pfVar4[4];
  local_40 = pfVar4[5];
  if (*(float *)(*(int *)((int)param_1 + 0xa4) + 0x24) != 0.0) {
    uVar6 = *(undefined4 *)(*(int *)((int)param_1 + 0xa4) + 0x24);
    pfVar4 = Actor_GetFrame(param_1);
    Matrix_AxisAngle(local_30,pfVar4 + 6,uVar6);
    Vec3_Transform(&local_48,local_30);
  }
  local_48 = local_48 + *param_2;
  local_44 = param_2[1] + local_44;
  local_40 = param_2[2] + local_40;
  Walker_ToLocalSpace(param_2,(int)&local_48);
  local_40 = 0.0;
  Vec3_Normalize(&local_48);
  fVar5 = (float10)Math_AsinDegreesSeries(local_44);
  fVar1 = (float)((float10)90.0 - fVar5);
  if ((float10)90.0 - fVar5 < (float10)0.5) {
    *(undefined4 *)(*(int *)((int)param_1 + 0xa4) + 0x28) = 0;
    return 1;
  }
  *(float *)(*(int *)((int)param_1 + 0xa4) + 0x28) = fVar1;
  iVar2 = *(int *)((int)param_1 + 0xa4);
  if (*(float *)(iVar2 + 0x1c) <= 0.0) {
    fVar5 = (float10)3.4028235e+38;
    *(float *)(iVar2 + 0x1c) = *(float *)(iVar2 + 0x1c) * -1.0;
  }
  else {
    fVar5 = (float10)Timer_GetFrameSeconds();
    fVar5 = fVar5 * (float10)*(float *)(iVar2 + 0x41c) * (float10)*(float *)(iVar2 + 0x1c);
  }
  param_1 = PUN(void *,(float)fVar1);
  if (fVar5 < (float10)fVar1) {
    param_1 = PUN(void *,(float)(float)(((float10)fVar1 - fVar5) * (float10)0.1 + fVar5));
  }
  if (local_48 <= 0.0) {
    fVar1 = *(float *)((int)pvVar3 + 0x28) - PUN(float,param_1);
  }
  else {
    fVar1 = *(float *)((int)pvVar3 + 0x28) + PUN(float,param_1);
  }
  *(undefined4 *)((int)pvVar3 + 0x24) = *(undefined4 *)((int)pvVar3 + 0x24);
  *(float *)((int)pvVar3 + 0x28) = fVar1;
  *(undefined4 *)((int)pvVar3 + 0x2c) = *(undefined4 *)((int)pvVar3 + 0x2c);
  *(undefined4 *)((int)pvVar3 + 0x34) = 0;
  return 0;
}
#undef local_30
#undef local_40
#undef local_44
#undef local_48


/* ---- 0x00491650  Walker_ReplanPath ---- */
void Walker_ReplanPath(int param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  unsigned char _frame[0x2f0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  void *this;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  #define local_2d4 (*(int *)(_frame + (0x2f0 - 0x2d4)))
  #define local_2d0 (*(undefined4 (*)[72])(_frame + (0x2f0 - 0x2d0)))
  #define auStack_1b0 (*(undefined4 (*)[18])(_frame + (0x2f0 - 0x1b0)))
  #define local_168 (*(undefined1 (*)[360])(_frame + (0x2f0 - 0x168)))
  
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
        puVar3 = local_2d0;
        iVar4 = iVar2;
        do {
          puVar1 = (undefined4 *)((local_2d4 - (int)local_2d0) + (int)puVar3);
          iVar4 = iVar4 + -1;
          *puVar3 = *puVar1;
          puVar3[1] = puVar1[1];
          puVar3[2] = puVar1[2];
          puVar3 = puVar3 + 3;
        } while (iVar4 != 0);
      }
      iVar2 = Walker_AvoidActorPath(param_1,param_4,local_2d0,iVar2,local_168);
      *(int *)(*(int *)(param_1 + 0xa4) + 0x44) = iVar2;
      *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x1b0) = 1;
      if (0 < iVar2) {
        iVar4 = 0x48;
        iVar5 = iVar2;
        do {
          puVar3 = (undefined4 *)(*(int *)(param_1 + 0xa4) + iVar4);
          iVar5 = iVar5 + -1;
          *puVar3 = *(undefined4 *)((int)auStack_1b0 + iVar4);
          puVar3[1] = *(undefined4 *)((int)auStack_1b0 + iVar4 + 4);
          puVar3[2] = *(undefined4 *)((int)auStack_1b0 + iVar4 + 8);
          iVar4 = iVar4 + 0xc;
        } while (iVar5 != 0);
      }
      iVar4 = *(int *)(param_1 + 0xa4);
      puVar3 = (undefined4 *)(iVar4 + (*(int *)(iVar4 + 0x1b0) + 6) * 0xc);
      *(undefined4 *)(iVar4 + 0x2c) = *puVar3;
      *(undefined4 *)(iVar4 + 0x30) = puVar3[1];
      *(undefined4 *)(iVar4 + 0x34) = puVar3[2];
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
#undef local_168
#undef local_2d0
#undef local_2d4


/* ---- 0x004917e0  Walker_AvoidActorPath ---- */
/* WARNING: Type propagation algorithm not settling */

int Walker_AvoidActorPath
              (void *param_1,void *param_2,undefined4 *param_3,int param_4,float *param_5)

{
  unsigned char _frame[0x150] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float *pfVar4;
  void *this;
  float fVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  float *pfVar12;
  float fVar13;
  float **ppfVar14;
  #define apfStack_134 (*(float *(*)[3])(_frame + (0x150 - 0x134)))
  #define iStack_128 (*(int *)(_frame + (0x150 - 0x128)))
  #define local_124 (*(float *)(_frame + (0x150 - 0x124)))
  #define local_104 (*(float *)(_frame + (0x150 - 0x104)))
  #define local_100 (*(int *)(_frame + (0x150 - 0x100)))
  #define local_fc (*(float **)(_frame + (0x150 - 0xfc)))
  #define local_f8 (*(float *)(_frame + (0x150 - 0xf8)))
  #define local_f4 (*(float **)(_frame + (0x150 - 0xf4)))
  #define local_f0 (*(int *)(_frame + (0x150 - 0xf0)))
  #define local_e8 (*(float *)(_frame + (0x150 - 0xe8)))
  #define local_e4 (*(float *)(_frame + (0x150 - 0xe4)))
  #define local_e0 (*(float *)(_frame + (0x150 - 0xe0)))
  #define local_dc (*(float *)(_frame + (0x150 - 0xdc)))
  #define local_d8 (*(float *)(_frame + (0x150 - 0xd8)))
  #define local_d4 (*(float *)(_frame + (0x150 - 0xd4)))
  #define local_d0 (*(float *)(_frame + (0x150 - 0xd0)))
  #define local_cc (*(float *)(_frame + (0x150 - 0xcc)))
  #define local_c8 (*(float *)(_frame + (0x150 - 0xc8)))
  #define local_c4 (*(float *)(_frame + (0x150 - 0xc4)))
  #define local_c0 (*(float *)(_frame + (0x150 - 0xc0)))
  #define local_bc (*(float *)(_frame + (0x150 - 0xbc)))
  #define local_b8 (*(float *)(_frame + (0x150 - 0xb8)))
  #define local_b4 (*(float *)(_frame + (0x150 - 0xb4)))
  #define local_b0 (*(float *)(_frame + (0x150 - 0xb0)))
  #define local_ac (*(float *)(_frame + (0x150 - 0xac)))
  #define local_a8 (*(float *)(_frame + (0x150 - 0xa8)))
  #define local_a4 (*(float *)(_frame + (0x150 - 0xa4)))
  #define local_a0 (*(float *)(_frame + (0x150 - 0xa0)))
  #define local_9c (*(float *)(_frame + (0x150 - 0x9c)))
  #define local_98 (*(float *)(_frame + (0x150 - 0x98)))
  #define local_94 (*(float *)(_frame + (0x150 - 0x94)))
  #define local_90 (*(float *)(_frame + (0x150 - 0x90)))
  #define local_8c (*(float *)(_frame + (0x150 - 0x8c)))
  #define local_88 (*(float (*)[3])(_frame + (0x150 - 0x88)))
  #define local_7c (*(float (*)[4])(_frame + (0x150 - 0x7c)))
  #define local_6c (*(float *)(_frame + (0x150 - 0x6c)))
  #define local_68 (*(float *)(_frame + (0x150 - 0x68)))
  #define local_64 (*(float *)(_frame + (0x150 - 0x64)))
  #define local_60 (*(float *)(_frame + (0x150 - 0x60)))
  #define local_5c (*(float *)(_frame + (0x150 - 0x5c)))
  #define local_58 (*(float (*)[3])(_frame + (0x150 - 0x58)))
  #define local_4c (*(float (*)[12])(_frame + (0x150 - 0x4c)))
  #define local_1c (*(undefined4 (*)[4])(_frame + (0x150 - 0x1c)))
  #define local_c (*(float (*)[3])(_frame + (0x150 - 0xc)))
  
  local_100 = 0;
  if (param_2 == (void *)0x0) {
    puVar2 = param_3;
    iVar8 = param_4;
    if (param_4 < 1) {
      return 0;
    }
    do {
      puVar3 = puVar2 + 3;
      iVar8 = iVar8 + -1;
      *(undefined4 *)((int)param_5 + (-0xc - (int)param_3) + (int)puVar3) = *puVar2;
      *(undefined4 *)((int)param_5 + (-8 - (int)param_3) + (int)puVar3) = puVar2[1];
      *(undefined4 *)((int)param_5 + (-4 - (int)param_3) + (int)puVar3) = puVar2[2];
      puVar2 = puVar3;
    } while (iVar8 != 0);
    return param_4;
  }
  iVar8 = *(int *)(*(int *)(*(int *)((int)param_1 + 0xa0) + 4) + 4);
  local_104 = *(float *)(*(int *)((int)param_1 + 0xa4) + 0x3f4) * *(float *)(iVar8 + 0x5c);
  Actor_GetFrame(param_1);
  local_124 = 6.712797e-39;
  Vec3_Copy(local_c,(float *)(iVar8 + 0x78));
  iVar8 = *(int *)(*(int *)(*(int *)((int)param_2 + 0xa0) + 4) + 4);
  pfVar4 = Actor_GetFrame(param_2);
  local_124 = 6.712856e-39;
  Vec3_Sub(local_88,(float *)(iVar8 + 0x78),pfVar4);
  Actor_GetFrame(param_2);
  local_124 = 6.71289e-39;
  Vec3_Copy(&local_e8,(float *)(iVar8 + 0x78));
  iVar6 = *(int *)((int)param_2 + 0xa4);
  local_7c[0] = *(float *)(iVar8 + 0x60) * *(float *)(iVar6 + 0x3f4) - local_104;
  pfVar4 = (float *)(param_3 + param_4 * 3 + -3);
  local_7c[1] = *(float *)(iVar8 + 100) * *(float *)(iVar6 + 0x3f4) - local_104;
  local_7c[2] = *(float *)(iVar8 + 0x68) * *(float *)(iVar6 + 0x3f4) - local_104;
  local_7c[3] = *(float *)(iVar8 + 0x6c) * *(float *)(iVar6 + 0x3f4) + local_104;
  local_6c = *(float *)(iVar8 + 0x70) * *(float *)(iVar6 + 0x3f4) + local_104;
  local_68 = *(float *)(iVar8 + 0x74) * *(float *)(iVar6 + 0x3f4) + local_104;
  Actor_GetFrame(param_2);
  pfVar7 = local_7c;
  ppfVar14 = apfStack_134;
  for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
    *ppfVar14 = PUN(float *,(float)*pfVar7);
    pfVar7 = pfVar7 + 1;
    ppfVar14 = ppfVar14 + 1;
  }
  ((code *)Collision_PushOutOfBox)(pfVar4);
  Actor_GetFrame(param_2);
  pfVar7 = local_7c;
  ppfVar14 = apfStack_134;
  for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
    *ppfVar14 = PUN(float *,(float)*pfVar7);
    pfVar7 = pfVar7 + 1;
    ppfVar14 = ppfVar14 + 1;
  }
  ((code *)Collision_PushOutOfBox)(param_3);
  local_d0 = *pfVar4;
  local_cc = pfVar4[1];
  local_c8 = pfVar4[2];
  iVar6 = ((code *)SectorList_FindByPoint)();
  if (iVar6 == 0) {
    return 0;
  }
  iVar6 = 0;
  local_f8 = (float)(param_4 + -1);
  local_f0 = 0;
  if (0 < (int)local_f8) {
    pfVar7 = (float *)(param_3 + 2);
    pfVar4 = param_5;
    do {
      local_64 = local_e8 + pfVar7[-2];
      local_fc = pfVar4 + 3;
      iVar11 = local_100 + 1;
      local_60 = pfVar7[-1] + local_e4;
      local_5c = local_e0 + *pfVar7;
      local_a0 = pfVar7[1] + local_e8;
      local_9c = pfVar7[2] + local_e4;
      local_98 = pfVar7[3] + local_e0;
      *pfVar4 = pfVar7[-2];
      pfVar4[1] = pfVar7[-1];
      pfVar4[2] = *pfVar7;
      Actor_GetFrame(param_2);
      apfStack_134[0] = local_88;
      ppfVar14 = apfStack_134;
      pfVar4 = local_7c;
      for (iVar6 = 6; ppfVar14 = (float **)((int)ppfVar14 + 4), iVar6 != 0; iVar6 = iVar6 + -1) {
        *ppfVar14 = PUN(float *,(float)*pfVar4);
        pfVar4 = pfVar4 + 1;
      }
      iVar6 = ((code *)Collision_SegmentHitsBox)(&local_64,&local_a0);
      local_100 = iVar11;
      if (iVar6 != 0) {
        pfVar4 = Actor_GetFrame(param_2);
        local_124 = 6.713799e-39;
        Vec3_Sub(local_58,(float *)&DAT_008ca320,pfVar4);
        this = (void *)((code *)SectorList_FindNearestPoint)();
        Sector_SnapToPlane(this,(int)local_58);
        local_124 = 6.71388e-39;
        Actor_GetFrame(param_2);
        local_124 = local_104 - -0.02;
        apfStack_134[2] = (float *)0x491ba9;
        iStack_128 = iVar8;
        ((code *)Collision_BoxCorners)();
        puVar2 = local_1c;
        pfVar4 = local_4c;
        local_f4 = (float *)0x4;
        do {
          *puVar2 = 0;
          local_a0 = local_e8 + *pfVar4;
          local_9c = pfVar4[1] + local_e4;
          local_98 = local_e0 + pfVar4[2];
          Actor_GetFrame(param_2);
          apfStack_134[0] = local_88;
          ppfVar14 = apfStack_134;
          pfVar7 = local_7c;
          for (iVar8 = 6; ppfVar14 = (float **)((int)ppfVar14 + 4), iVar8 != 0; iVar8 = iVar8 + -1)
          {
            *ppfVar14 = PUN(float *,(float)*pfVar7);
            pfVar7 = pfVar7 + 1;
          }
          iVar8 = ((code *)Collision_SegmentHitsBox)(&local_64,&local_a0);
          if (iVar8 == 0) {
            local_124 = 6.714142e-39;
            iVar8 = ((code *)Planner_PlanPath)();
            if (iVar8 != 0) {
              *puVar2 = 1;
            }
          }
          pfVar4 = pfVar4 + 3;
          puVar2 = puVar2 + 1;
          local_f4 = (float *)((int)local_f4 + -1);
        } while (local_f4 != (float *)0x0);
        local_124 = 6.714228e-39;
        fVar5 = (float)((code *)Collision_PickDetour)();
        if (fVar5 == -NAN) {
          return iVar11;
        }
        local_124 = 6.714319e-39;
        local_d8 = fVar5;
        ((code *)Planner_PlanPath)();
        iVar8 = ((code *)Planner_GetPath)();
        if (0 < iVar8) {
          local_100 = iVar11 + iVar8;
          pfVar4 = param_5 + iVar11 * 3;
          pfVar7 = local_fc;
          do {
            iVar8 = iVar8 + -1;
            *pfVar4 = *pfVar7;
            pfVar4[1] = pfVar7[1];
            pfVar4[2] = pfVar7[2];
            pfVar4 = pfVar4 + 3;
            pfVar7 = pfVar7 + 3;
            fVar5 = local_d8;
          } while (iVar8 != 0);
        }
        local_1c[(int)fVar5] = 0;
        local_f4 = param_5 + local_100 * 3;
        pfVar4 = local_f4 + -3;
        Actor_GetFrame(param_2);
        pfVar7 = local_7c;
        ppfVar14 = apfStack_134;
        for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
          *ppfVar14 = PUN(float *,(float)*pfVar7);
          pfVar7 = pfVar7 + 1;
          ppfVar14 = ppfVar14 + 1;
        }
        iVar8 = Collision_PointInBox(pfVar4,&local_d0,local_88);
        if (iVar8 != 0) {
          iVar8 = ((code *)Planner_GetPath)();
          if (iVar8 < 1) {
            return local_100;
          }
          local_100 = local_100 + iVar8;
          do {
            iVar8 = iVar8 + -1;
            *local_f4 = *local_fc;
            local_f4[1] = local_fc[1];
            local_f4[2] = local_fc[2];
            local_f4 = local_f4 + 3;
            local_fc = local_fc + 3;
          } while (iVar8 != 0);
          return local_100;
        }
        uVar9 = (int)((int)local_d8 + 3U) >> 0x1f;
        fVar5 = (float)((((int)local_d8 + 3U ^ uVar9) - uVar9 & 3 ^ uVar9) - uVar9);
        uVar9 = (int)((int)local_d8 + 5U) >> 0x1f;
        fVar13 = (float)((((int)local_d8 + 5U ^ uVar9) - uVar9 & 3 ^ uVar9) - uVar9);
        local_124 = 6.71479e-39;
        local_dc = fVar13;
        local_f0 = ((code *)Planner_PlanPath)();
        local_124 = 6.71483e-39;
        iVar8 = ((code *)Planner_PlanPath)();
        if (iVar8 != 0) {
          if (local_f0 == 0) goto LAB_00491fa5;
          local_104 = *pfVar4 - local_4c[(int)fVar5 * 3];
          local_bc = local_f4[-2] - local_4c[(int)fVar5 * 3 + 1];
          local_b8 = local_f4[-1] - local_4c[(int)fVar5 * 3 + 2];
          local_c0 = local_4c[(int)fVar5 * 3] - local_d0;
          local_c4 = local_4c[(int)fVar5 * 3 + 1] - local_cc;
          local_b0 = local_4c[(int)fVar5 * 3 + 2] - local_c8;
          local_b4 = *pfVar4 - local_4c[(int)fVar13 * 3];
          local_d4 = local_f4[-2] - local_4c[(int)fVar13 * 3 + 1];
          local_f8 = local_f4[-1] - local_4c[(int)fVar13 * 3 + 2];
          local_fc = PUN(float *,(float)(local_4c[(int)fVar13 * 3 + 1] - local_cc));
          fVar1 = local_4c[(int)fVar13 * 3 + 2] - local_c8;
          if (fVar1 * fVar1 +
              PUN(float,local_fc) * PUN(float,local_fc) +
              (local_4c[(int)fVar13 * 3] - local_d0) * (local_4c[(int)fVar13 * 3] - local_d0) +
              local_f8 * local_f8 + local_d4 * local_d4 + local_b4 * local_b4 <=
              local_b0 * local_b0 + local_c4 * local_c4 + local_c0 * local_c0 +
              local_b8 * local_b8 + local_bc * local_bc + local_104 * local_104) {
            local_f0 = 0;
          }
          else {
            iVar8 = 0;
          }
        }
        if (local_f0 != 0) {
          local_f8 = -NAN;
          local_104 = fVar5;
        }
LAB_00491fa5:
        if (iVar8 != 0) {
          local_f8 = 1.4013e-45;
          local_104 = local_dc;
        }
        if (local_104 == local_d8) {
          return local_100;
        }
        while( true ) {
          local_124 = 6.715423e-39;
          ((code *)Planner_PlanPath)();
          pfVar4 = (float *)((code *)Planner_GetPath)();
          local_dc = (float)((int)pfVar4 + -1);
          iVar8 = 0;
          if (0 < (int)local_dc) {
            iVar6 = 0;
            do {
              local_ac = local_e8 + *(float *)((int)local_fc + iVar6);
              local_a8 = *(float *)((int)local_fc + iVar6 + 4) + local_e4;
              local_a4 = *(float *)((int)local_fc + iVar6 + 8) + local_e0;
              local_94 = *(float *)((int)local_fc + iVar6 + 0xc) + local_e8;
              local_90 = *(float *)((int)local_fc + iVar6 + 0x10) + local_e4;
              local_8c = *(float *)((int)local_fc + iVar6 + 0x14) + local_e0;
              Actor_GetFrame(param_2);
              ppfVar14 = apfStack_134;
              pfVar7 = local_7c;
              for (iVar11 = 6; ppfVar14 = (float **)((int)ppfVar14 + 4), iVar11 != 0;
                  iVar11 = iVar11 + -1) {
                *ppfVar14 = PUN(float *,(float)*pfVar7);
                pfVar7 = pfVar7 + 1;
              }
              apfStack_134[0] = local_88;
              iVar11 = ((code *)Collision_SegmentHitsBox)(&local_ac,&local_94);
              if (iVar11 != 0) {
                return 0;
              }
              iVar8 = iVar8 + 1;
              iVar6 = iVar6 + 0xc;
            } while (iVar8 < (int)local_dc);
          }
          if (0 < (int)pfVar4) {
            local_100 = local_100 + (int)pfVar4;
            pfVar7 = local_fc;
            pfVar12 = pfVar4;
            do {
              pfVar12 = (float *)((int)pfVar12 + -1);
              *local_f4 = *pfVar7;
              local_f4[1] = pfVar7[1];
              local_f4[2] = pfVar7[2];
              local_f4 = local_f4 + 3;
              pfVar7 = pfVar7 + 3;
            } while (pfVar12 != (float *)0x0);
          }
          local_f4 = param_5 + local_100 * 3;
          Actor_GetFrame(param_2);
          pfVar7 = local_7c;
          ppfVar14 = apfStack_134;
          for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
            *ppfVar14 = PUN(float *,(float)*pfVar7);
            pfVar7 = pfVar7 + 1;
            ppfVar14 = ppfVar14 + 1;
          }
          iVar8 = Collision_PointInBox(local_f4 + -3,&local_d0,local_88);
          if (iVar8 != 0) break;
          uVar9 = (int)local_f8 + 4 + (int)local_104;
          uVar10 = (int)uVar9 >> 0x1f;
          local_104 = (float)(((uVar9 ^ uVar10) - uVar10 & 3 ^ uVar10) - uVar10);
          if (local_104 == local_d8) {
            return local_100;
          }
        }
        local_d4 = (float)((code *)Planner_GetPath)();
        iVar8 = 0;
        local_dc = (float)((int)local_d4 + -1);
        local_f8 = 0.0;
        if (0 < (int)local_dc) {
          do {
            local_94 = local_e8 + *(float *)((int)pfVar4 + iVar8);
            local_90 = *(float *)((int)pfVar4 + iVar8 + 4) + local_e4;
            local_8c = *(float *)((int)pfVar4 + iVar8 + 8) + local_e0;
            local_ac = *(float *)((int)pfVar4 + iVar8 + 0xc) + local_e8;
            local_a8 = *(float *)((int)pfVar4 + iVar8 + 0x10) + local_e4;
            local_a4 = *(float *)((int)pfVar4 + iVar8 + 0x14) + local_e0;
            Actor_GetFrame(param_2);
            apfStack_134[0] = local_88;
            ppfVar14 = apfStack_134;
            pfVar7 = local_7c;
            for (iVar6 = 6; ppfVar14 = (float **)((int)ppfVar14 + 4), iVar6 != 0; iVar6 = iVar6 + -1
                ) {
              *ppfVar14 = PUN(float *,(float)*pfVar7);
              pfVar7 = pfVar7 + 1;
            }
            iVar6 = ((code *)Collision_SegmentHitsBox)(&local_94,&local_ac);
            if (iVar6 != 0) {
              return 0;
            }
            local_f8 = (float)((int)local_f8 + 1);
            iVar8 = iVar8 + 0xc;
          } while ((int)local_f8 < (int)local_dc);
        }
        iVar8 = local_100;
        if (0 < (int)local_d4) {
          iVar8 = local_100 + (int)local_d4;
          pfVar7 = param_5 + local_100 * 3;
          do {
            local_d4 = (float)((int)local_d4 + -1);
            *pfVar7 = *pfVar4;
            pfVar7[1] = pfVar4[1];
            pfVar7[2] = pfVar4[2];
            pfVar7 = pfVar7 + 3;
            pfVar4 = pfVar4 + 3;
          } while (local_d4 != 0.0);
        }
        return iVar8;
      }
      iVar6 = local_f0 + 1;
      pfVar7 = pfVar7 + 3;
      pfVar4 = local_fc;
      local_f0 = iVar6;
    } while (iVar6 < (int)local_f8);
  }
  pfVar4 = (float *)(param_3 + iVar6 * 3);
  param_5 = param_5 + local_100 * 3;
  *param_5 = *pfVar4;
  param_5[1] = pfVar4[1];
  param_5[2] = pfVar4[2];
  return local_100 + 1;
}
#undef apfStack_134
#undef iStack_128
#undef local_100
#undef local_104
#undef local_124
#undef local_1c
#undef local_4c
#undef local_58
#undef local_5c
#undef local_60
#undef local_64
#undef local_68
#undef local_6c
#undef local_7c
#undef local_88
#undef local_8c
#undef local_90
#undef local_94
#undef local_98
#undef local_9c
#undef local_a0
#undef local_a4
#undef local_a8
#undef local_ac
#undef local_b0
#undef local_b4
#undef local_b8
#undef local_bc
#undef local_c
#undef local_c0
#undef local_c4
#undef local_c8
#undef local_cc
#undef local_d0
#undef local_d4
#undef local_d8
#undef local_dc
#undef local_e0
#undef local_e4
#undef local_e8
#undef local_f0
#undef local_f4
#undef local_f8
#undef local_fc


/* ---- 0x00494880  Walker_SetFadeTime ---- */
/* Lua SetWalkSystemFadeTime */

void __cdecl Walker_SetFadeTime(int ms)

{
  g_nChoreFadeMs = ms;
  return;
}

/* ---- 0x004a8200  Walker_Create ---- */
/* Allocates the 0x60-byte walker record */

undefined4 * __thiscall Walker_Create(void *this,int a1)

{
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  Angles_ToMatrix((int)this + 0xc,this,this);
  *(undefined4 *)((int)this + 0x48) = 0x3f800000;
  *(int *)((int)this + 0x3c) = a1;
  *(undefined4 *)((int)this + 0x5c) = 0;
  *(undefined4 *)((int)this + 0x40) = 0;
  *(undefined4 *)((int)this + 0x50) = 0;
  *(undefined4 *)((int)this + 0x44) = 0;
  *(undefined4 *)((int)this + 0x4c) = 0;
  *(undefined4 *)((int)this + 0x58) = 0;
  *(undefined4 *)((int)this + 0x54) = 0;
  *(void **)((int)this + 0x58) = DAT_008d086c;
  if (DAT_008d086c != (void *)0x0) {
    *(void **)((int)DAT_008d086c + 0x54) = this;
  }
  DAT_008d086c = this;
  return this;
}

/* ---- 0x004a8270  Walker_Destroy ---- */
void __fastcall Walker_Destroy(int param_1)

{
  if (param_1 == DAT_008d086c) {
    DAT_008d086c = *(int *)(param_1 + 0x58);
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
  int iVar1;
  
  iVar1 = SectorList_FindNearestPoint(param_1,0x1000);
  *(int *)((int)param_1 + 0x5c) = iVar1;
  if (iVar1 != 0) {
    iVar1 = Sector_ContainsPoint((int)param_1,1);
    if (iVar1 == 0) {
      Sector_ClampPoint(*(void **)((int)param_1 + 0x5c),(int)param_1);
      Walker_SetPosition(param_1,(int)param_1);
    }
    Walker_SetSectorFrame(param_1,*(int *)((int)param_1 + 0x5c));
  }
  return;
}

/* ---- 0x004a8310  Walker_SetPosition ---- */
undefined4 __thiscall Walker_SetPosition(void *this,int a1)

{
  undefined4 uVar1;
  
  *(undefined4 *)this = *(undefined4 *)a1;
  *(undefined4 *)((int)this + 4) = *(undefined4 *)(a1 + 4);
  *(undefined4 *)((int)this + 8) = *(undefined4 *)(a1 + 8);
  *(undefined4 *)((int)this + 0x30) = *(undefined4 *)a1;
  *(undefined4 *)((int)this + 0x34) = *(undefined4 *)(a1 + 4);
  uVar1 = *(undefined4 *)(a1 + 8);
  *(undefined4 *)((int)this + 0x38) = uVar1;
  return uVar1;
}

/* ---- 0x004a8350  Walker_RotateVector ---- */
undefined4 __thiscall Walker_RotateVector(void *this,int a1)

{
  undefined4 extraout_EAX;
  
  Vec3_Rotate3x3((float *)a1,(float *)((int)this + 0xc));
  return extraout_EAX;
}

/* ---- 0x004a8370  Walker_ToLocalSpace ---- */
/* Rotates a world vector into the current walker's frame */

undefined4 __thiscall Walker_ToLocalSpace(void *this,int a1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  *(float *)a1 = *(float *)a1 - *(float *)this;
  *(float *)(a1 + 4) = *(float *)(a1 + 4) - *(float *)((int)this + 4);
  *(float *)(a1 + 8) = *(float *)(a1 + 8) - *(float *)((int)this + 8);
  Vec3_TransformTo(&local_c,(float *)a1,(float *)((int)this + 0xc));
  *(float *)a1 = local_c;
  *(undefined4 *)(a1 + 4) = local_8;
  *(undefined4 *)(a1 + 8) = local_4;
  return local_4;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a83c0  Walker_TurnHeading ---- */
undefined4 __thiscall Walker_TurnHeading(void *this,int a1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *vec;
  undefined4 uVar1;
  #define local_30 (*(float (*)[12])(_frame + (0x40 - 0x30)))
  
  Matrix_AxisAngle(local_30,(int)this + 0x24,a1);
  vec = (float *)((int)this + 0x18);
  Vec3_Transform(vec,local_30);
  *vec = *vec + *(float *)((int)this + 0x30);
  *(float *)((int)this + 0x1c) = *(float *)((int)this + 0x34) + *(float *)((int)this + 0x1c);
  *(float *)((int)this + 0x20) = *(float *)((int)this + 0x38) + *(float *)((int)this + 0x20);
  if (*(void **)((int)this + 0x5c) != (void *)0x0) {
    Sector_SnapToPlane(*(void **)((int)this + 0x5c),(int)vec);
  }
  *vec = *vec - *(float *)((int)this + 0x30);
  *(float *)((int)this + 0x1c) = *(float *)((int)this + 0x1c) - *(float *)((int)this + 0x34);
  *(float *)((int)this + 0x20) = *(float *)((int)this + 0x20) - *(float *)((int)this + 0x38);
  uVar1 = ((code *)Walker_RebuildRightVector)();
  return uVar1;
}
#undef local_30


/* ---- 0x004a8450  Walker_TurnToPoint ---- */
undefined4 __thiscall Walker_TurnToPoint(void *this,int a1,int a2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  float10 fVar2;
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  local_c = *(float *)a1;
  local_8 = *(undefined4 *)(a1 + 4);
  local_4 = *(undefined4 *)(a1 + 8);
  if (*(void **)((int)this + 0x5c) != (void *)0x0) {
    Sector_FixPlaneCoordinate(*(void **)((int)this + 0x5c),(int)&local_c);
  }
  Walker_ToLocalSpace(this,(int)&local_c);
  Vec3_Normalize(&local_c);
  fVar2 = (float10)Math_AsinDegreesSeries(local_8);
  a1 = (int)(float)((float10)90.0 - fVar2);
  if ((float)a2 < (float)a1) {
    a1 = a2;
  }
  if (0.0 < local_c) {
    a1 = (int)((float)a1 * -1.0);
  }
  uVar1 = Walker_TurnHeading(this,a1);
  return uVar1;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a85b0  Walker_SetConstraint ---- */
undefined4 __thiscall Walker_SetConstraint(void *this,int a1)

{
  undefined4 in_EAX;
  undefined4 *puVar1;
  
  *(undefined4 *)((int)this + 0x50) = 0;
  if ((*(void **)((int)this + 0x5c) != (void *)0x0) && (in_EAX = 0, a1 != 0)) {
    puVar1 = (undefined4 *)Sector_EdgeFollowDirection(*(void **)((int)this + 0x5c),(int)this);
    in_EAX = 0;
    if (puVar1 != (undefined4 *)0x0) {
      *(undefined4 *)((int)this + 0x44) = *puVar1;
      *(undefined4 *)((int)this + 0x48) = puVar1[1];
      *(undefined4 *)((int)this + 0x4c) = puVar1[2];
      *(undefined4 *)((int)this + 0x18) = *puVar1;
      *(undefined4 *)((int)this + 0x1c) = puVar1[1];
      *(undefined4 *)((int)this + 0x20) = puVar1[2];
      in_EAX = ((code *)Walker_RebuildRightVector)();
      *(undefined4 *)((int)this + 0x50) = 1;
    }
  }
  return in_EAX;
}

/* ---- 0x004a8610  Walker_WalkSectors ---- */
/* Walker_WalkSectors: the per-frame walk of an actor over the walk sectors (target-inside test with
   tolerance, exit point of the edge, neighbour lookup with the current sector deactivated, 0.02 cap
   into the new sector, reflection turn only when |angle| < reflect and not against a held turn
   key). See autorun/NAV_PLAN.md and COLLISION_FIX_PLAN.md. */

undefined4 __thiscall Walker_WalkSectors(void *this,int a1,int a2,int a3)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *this_00;
  int iVar1;
  undefined4 uVar2;
  float10 fVar3;
  float10 extraout_ST0;
  float fVar4;
  float fVar5;
  #define local_34 (*(float *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(undefined4 *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(int *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(undefined4 *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(undefined4 *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(float *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(undefined4 *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(undefined4 *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(undefined4 *)(_frame + (0x50 - 0x10)))
  #define local_c (*(float *)(_frame + (0x50 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x50 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x50 - 0x4)))
  
  uVar2 = 0;
  if (DAT_008d0870 == 0) {
    *(int *)((int)this + 0x40) = a1;
  }
  DAT_008d0870 = DAT_008d0870 + 1;
  if (*(int *)((int)this + 0x50) != 0) {
    fVar4 = Vec3_Dot2((float *)((int)this + 0xc),(float *)((int)this + 0x44));
    fVar3 = (float10)Math_AsinDegreesSeries(fVar4);
    fVar3 = ((float10)90.0 - fVar3) - (float10)90.0;
    fVar4 = (float)fVar3;
    if (fVar3 < (float10)0.0) {
      fVar3 = -fVar3;
    }
    if ((float10)*(float *)((int)this + 0x3c) < fVar3) {
      return 0;
    }
    fVar5 = Vec3_Dot2((float *)((int)this + 0x18),(float *)((int)this + 0x44));
    if (fVar5 <= 0.0) {
      fVar4 = -fVar4;
    }
    Walker_TurnHeading(this,(int)fVar4);
  }
  local_30 = 0;
  local_2c = a1;
  local_28 = 0;
  Walker_RotateVector(this,(int)&local_30);
  if ((*(int *)((int)this + 0x5c) == 0) ||
     (iVar1 = Sector_ContainsPoint((int)&local_30,1), iVar1 != 0)) {
    Walker_SetPosition(this,(int)&local_30);
    DAT_008d0870 = 0;
    return 1;
  }
  if (8 < DAT_008d0870) {
    DAT_008d0870 = 0;
    return 0;
  }
  this_00 = *(void **)((int)this + 0x5c);
  Sector_FindExitPoint(this_00,(int)this,(int)&local_30,(int)&local_24);
  local_34 = (float)extraout_ST0;
  *(undefined4 *)(*(int *)((int)this + 0x5c) + 0x2c) = 0;
  local_18 = local_24;
  local_14 = local_20;
  local_10 = local_1c;
  Walker_ToLocalSpace(this,(int)&local_18);
  a1 = (int)((float)a1 - local_14);
  iVar1 = SectorList_FindByPoint(&local_24,0x1000);
  if (iVar1 == 0) {
    Walker_SetPosition(this,(int)&local_24);
    iVar1 = *(int *)((int)this + 0x5c);
    if ((*(uint *)(iVar1 + 0x24) & 0x100) == 0) {
      fVar4 = local_34;
      if (local_34 < 0.0) {
        fVar4 = -local_34;
      }
      if ((*(float *)((int)this + 0x3c) <= fVar4) || (*(int *)((int)this + 0x50) != 0)) {
        *(float *)((int)this + 0x40) = *(float *)((int)this + 0x40) - (float)a1;
      }
      else if (((0.0 < local_34) && (a2 != 0)) || ((local_34 < 0.0 && (a3 != 0)))) {
        Walker_TurnHeading(this,(int)local_34);
        *(undefined4 *)((int)this_00 + 0x2c) = 1;
        uVar2 = Walker_WalkSectors(this,a1,1,1);
      }
      if (*(int *)((int)this + 0x50) != 0) {
        Walker_TurnHeading(this,(int)local_34);
        *(undefined4 *)((int)this + 0x50) = 1;
        *(undefined4 *)((int)this + 0x44) = *(undefined4 *)((int)this + 0x18);
        *(undefined4 *)((int)this + 0x48) = *(undefined4 *)((int)this + 0x1c);
        *(undefined4 *)((int)this + 0x4c) = *(undefined4 *)((int)this + 0x20);
      }
      *(undefined4 *)((int)this_00 + 0x2c) = 1;
      return uVar2;
    }
    if ((*(int *)(iVar1 + 0x78) + 1) % *(int *)(iVar1 + 0x34) != *(int *)(iVar1 + 0x74)) {
      iVar1 = *(int *)(iVar1 + 0x38 + *(int *)(iVar1 + 0x78) * 4);
      local_c = *(float *)(iVar1 + 4);
      local_8 = *(undefined4 *)(iVar1 + 8);
      local_4 = *(undefined4 *)(iVar1 + 0xc);
      Walker_ToLocalSpace(this,(int)&local_c);
      if (local_c <= 0.0) {
        if (local_34 < 3.0) {
          local_34 = (local_34 - -90.0) - -90.2;
        }
      }
      else if (3.0 < local_34) {
        local_34 = -90.2 - (90.0 - local_34);
      }
      Walker_TurnHeading(this,(int)local_34);
      uVar2 = Walker_WalkSectors(this,a1,1,1);
      *(undefined4 *)((int)this_00 + 0x2c) = 1;
      return uVar2;
    }
    return 0;
  }
  Walker_SetPosition(this,(int)&local_24);
  *(int *)((int)this + 0x5c) = iVar1;
  Walker_SetSectorFrame(this,iVar1);
  if (0.02 <= (float)a1) {
    a1 = 0x3ca3d70a;
  }
  uVar2 = Walker_WalkSectors(this,a1,1,1);
  *(undefined4 *)((int)this_00 + 0x2c) = 1;
  return uVar2;
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
#undef local_8
#undef local_c


/* ---- 0x004a89b0  Walker_SetSectorFrame ---- */
undefined4 __thiscall Walker_SetSectorFrame(void *this,int a1)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  undefined4 uVar4;
  
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
  uVar4 = ((code *)Vec3_Normalize)(pfVar2);
  return uVar4;
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
undefined4 __stdcall Walker_DrawDebugAxes(int a1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  void *in_ECX;
  #define local_18 (*(undefined4 *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(undefined4 *)(_frame + (0x30 - 0x10)))
  #define local_c (*(undefined4 *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x30 - 0x4)))
  
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  local_18 = 0;
  local_14 = 0x3dcccccd;
  local_10 = 0;
  Walker_RotateVector(in_ECX,(int)&local_c);
  Walker_RotateVector(in_ECX,(int)&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,a1,0xffffffff);
  local_c = 0x3d4ccccd;
  local_8 = 0x3d4ccccd;
  local_4 = 0;
  local_18 = 0;
  local_14 = 0x3dcccccd;
  local_10 = 0;
  Walker_RotateVector(in_ECX,(int)&local_c);
  Walker_RotateVector(in_ECX,(int)&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,a1,0xffffffff);
  local_c = 0xbd4ccccd;
  local_8 = 0x3d4ccccd;
  local_4 = 0;
  local_18 = 0;
  local_14 = 0x3dcccccd;
  local_10 = 0;
  Walker_RotateVector(in_ECX,(int)&local_c);
  Walker_RotateVector(in_ECX,(int)&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,a1,0xffffffff);
  local_c = 0;
  local_8 = 0;
  local_4 = 0x3d4ccccd;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  Walker_RotateVector(in_ECX,(int)&local_c);
  Walker_RotateVector(in_ECX,(int)&local_18);
  uVar1 = rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,a1,0xffffffff);
  return uVar1;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a9420  Planner_GetPath ---- */
undefined4 Planner_GetPath(undefined4 *param_1)

{
  *param_1 = &DAT_008cf0b0;
  return DAT_008cf248;
}

/* ---- 0x004a9430  Planner_PlanPath ---- */
undefined4 Planner_PlanPath(undefined4 param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  SectorList_ResetFree();
  DAT_008cf248 = 0;
  iVar1 = SectorList_FindByPoint(param_1,0x1000);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = SectorList_FindByPoint(param_2,0x1000);
  if (iVar1 == 0) {
    return 0;
  }
  iVar2 = Planner_SearchSectors(param_1,param_2,0);
  iVar1 = DAT_008cf248;
  if (iVar2 != 0) {
    iVar2 = DAT_008cf248 * 3;
    DAT_008cf248 = DAT_008cf248 + 1;
    (&DAT_008cf0b0)[iVar2] = *param_2;
    (&DAT_008cf0b4)[iVar1 * 3] = param_2[1];
    (&DAT_008cf0b8)[iVar1 * 3] = param_2[2];
    if (param_3 != 0) {
      Planner_SmoothPath();
    }
    uVar3 = 1;
  }
  SectorList_ResetFree();
  return uVar3;
}

/* ---- 0x004a94d0  Planner_SearchSectors ---- */
undefined4 Planner_SearchSectors(float *param_1,int param_2,void *param_3)

{
  unsigned char _frame[0x210] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  #define local_1fc (*(int *)(_frame + (0x210 - 0x1fc)))
  #define local_1f8 (*(int *)(_frame + (0x210 - 0x1f8)))
  #define local_1f4 (*(float *)(_frame + (0x210 - 0x1f4)))
  #define local_1f0 (*(float *)(_frame + (0x210 - 0x1f0)))
  #define local_1ec (*(float *)(_frame + (0x210 - 0x1ec)))
  #define local_1e8 (*(int *)(_frame + (0x210 - 0x1e8)))
  #define local_1e4 (*(int *)(_frame + (0x210 - 0x1e4)))
  #define local_1e0 (*(undefined1 (*)[480])(_frame + (0x210 - 0x1e0)))
  
  if (0x1d < DAT_008cf248 + 1) {
    *(undefined4 *)((int)param_3 + 0x2c) = 0;
    return 1;
  }
  if (param_3 == (void *)0x0) {
    param_3 = (void *)SectorList_FindByPoint(param_1,0x1000);
  }
  iVar1 = DAT_008cf248;
  if (param_3 != (void *)0x0) {
    iVar2 = DAT_008cf248 * 3;
    DAT_008cf248 = DAT_008cf248 + 1;
    (&DAT_008cf0b0)[iVar2] = *param_1;
    (&DAT_008cf0b4)[iVar1 * 3] = param_1[1];
    (&DAT_008cf0b8)[iVar1 * 3] = param_1[2];
    iVar1 = Sector_ContainsPoint(param_2,1);
    if (iVar1 != 0) {
      return 1;
    }
    local_1e8 = DAT_008cf248;
    Sector_FindExitPoint(param_3,(int)param_1,param_2,(int)&local_1f4);
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
      iVar1 = Planner_SearchSectors(&local_1f4,param_2,local_1f8);
      if (iVar1 != 0) {
        return 1;
      }
      if (local_1f8 != 0) {
        *(undefined4 *)(local_1f8 + 0x2c) = 0;
      }
    }
    local_1e4 = Planner_CollectSharedCorners(param_3,param_2,local_1e0);
    local_1fc = 0;
    if (0 < local_1e4) {
      puVar3 = local_1e0;
      do {
        iVar1 = SectorList_FindByPoint(puVar3,0x1000);
        if (iVar1 != 0) {
          DAT_008cf248 = local_1e8;
          iVar2 = Planner_PortalPoint(param_3,iVar1,param_2,&local_1f4);
          if ((iVar2 != 0) && (iVar1 = Planner_SearchSectors(&local_1f4,param_2,iVar1), iVar1 != 0))
          {
            return 1;
          }
        }
        local_1fc = local_1fc + 1;
        puVar3 = puVar3 + 0x10;
      } while (local_1fc < local_1e4);
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
int Planner_CollectSharedCorners(void *param_1,float *param_2,float *param_3)

{
  unsigned char _frame[0x200] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  void *pvVar5;
  int iVar6;
  float *pfVar7;
  float *pfVar8;
  uint uVar9;
  int *piVar10;
  int iVar11;
  char *pcVar12;
  bool bVar13;
  #define local_1ec (*(int *)(_frame + (0x200 - 0x1ec)))
  #define local_1e8 (*(int *)(_frame + (0x200 - 0x1e8)))
  #define local_1e0 (*(float (*)[4])(_frame + (0x200 - 0x1e0)))
  #define local_1d0 (*(float (*)[116])(_frame + (0x200 - 0x1d0)))
  
  iVar11 = 0;
  local_1e8 = 0;
  for (pvVar5 = g_pSectorList; pvVar5 != (void *)0x0; pvVar5 = *(void **)((int)pvVar5 + 0x70)) {
    if ((((pvVar5 != param_1) && (*(int *)((int)pvVar5 + 0x2c) != 0)) &&
        ((*(uint *)((int)pvVar5 + 0x24) & 0x1000) != 0)) &&
       (local_1ec = 0, 0 < *(int *)((int)pvVar5 + 0x34))) {
      piVar10 = (int *)((int)pvVar5 + 0x38);
      do {
        iVar6 = Sector_ContainsPoint(*piVar10 + 4,0);
        if (iVar6 != 0) {
          iVar6 = 0;
          if (0 < iVar11) {
            pfVar8 = local_1e0;
            do {
              iVar11 = 0xc;
              bVar13 = true;
              pfVar7 = pfVar8;
              pcVar12 = (char *)(*piVar10 + 4);
              do {
                if (iVar11 == 0) break;
                iVar11 = iVar11 + -1;
                bVar13 = *(char *)pfVar7 == *pcVar12;
                pfVar7 = (float *)((int)pfVar7 + 1);
                pcVar12 = pcVar12 + 1;
              } while (bVar13);
              iVar11 = local_1e8;
              if (bVar13) break;
              iVar6 = iVar6 + 1;
              pfVar8 = pfVar8 + 4;
            } while (iVar6 < local_1e8);
          }
          if (iVar6 == iVar11) {
            iVar4 = *piVar10;
            fVar1 = *param_2;
            fVar2 = param_2[1];
            iVar11 = iVar11 + 1;
            fVar3 = param_2[2];
            local_1e0[iVar6 * 4] = *(float *)(iVar4 + 4);
            local_1e0[iVar6 * 4 + 1] = *(float *)(iVar4 + 8);
            local_1e0[iVar6 * 4 + 2] = *(float *)(iVar4 + 0xc);
            fVar1 = fVar1 - local_1e0[iVar6 * 4];
            local_1e0[iVar6 * 4 + 3] =
                 (fVar3 - local_1e0[iVar6 * 4 + 2]) * (fVar3 - local_1e0[iVar6 * 4 + 2]) +
                 (fVar2 - local_1e0[iVar6 * 4 + 1]) * (fVar2 - local_1e0[iVar6 * 4 + 1]) +
                 fVar1 * fVar1;
            local_1e8 = iVar11;
          }
        }
        local_1ec = local_1ec + 1;
        piVar10 = piVar10 + 1;
      } while (local_1ec < *(int *)((int)pvVar5 + 0x34));
    }
  }
  iVar6 = 1;
  *param_3 = local_1e0[0];
  param_3[1] = local_1e0[1];
  param_3[2] = local_1e0[2];
  param_3[3] = local_1e0[3];
  if (1 < iVar11) {
    pfVar8 = local_1e0;
    do {
      pfVar8 = pfVar8 + 4;
      fVar1 = pfVar8[3];
      uVar9 = iVar6 - 1;
      if (-1 < (int)uVar9) {
        pfVar7 = param_3 + iVar6 * 4;
        do {
          if (pfVar7[-1] <= fVar1) break;
          uVar9 = uVar9 - 1;
          *pfVar7 = pfVar7[-4];
          pfVar7[1] = pfVar7[-3];
          pfVar7[2] = pfVar7[-2];
          pfVar7[3] = pfVar7[-1];
          pfVar7 = pfVar7 + -4;
        } while (uVar9 < 0x80000000);
      }
      pfVar7 = param_3 + (uVar9 + 1) * 4;
      iVar6 = iVar6 + 1;
      *pfVar7 = *pfVar8;
      pfVar7[1] = pfVar8[1];
      fVar1 = pfVar8[3];
      pfVar7[2] = pfVar8[2];
      pfVar7[3] = fVar1;
    } while (iVar6 < iVar11);
  }
  return iVar11;
}
#undef local_1d0
#undef local_1e0
#undef local_1e8
#undef local_1ec


/* ---- 0x004a9920  Planner_PortalPoint ---- */
undefined4 Planner_PortalPoint(int param_1,int param_2,float *param_3,undefined4 *param_4)

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
  if (0 < *(int *)(param_1 + 0x34)) {
    piVar6 = (int *)(param_1 + 0x38);
    do {
      iVar4 = Sector_ContainsPoint(*piVar6 + 4,0);
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
    } while (iVar5 < *(int *)(param_1 + 0x34));
  }
  iVar5 = 0;
  if (0 < *(int *)(param_2 + 0x34)) {
    piVar6 = (int *)(param_2 + 0x38);
    do {
      iVar4 = Sector_ContainsPoint(*piVar6 + 4,0);
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
    } while (iVar5 < *(int *)(param_2 + 0x34));
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
  undefined4 *a1;
  bool bVar1;
  bool bVar2;
  void *this;
  int iVar3;
  int iVar4;
  float *pfVar5;
  undefined4 *a2;
  float *pfVar6;
  #define local_14 (*(int *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(int *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  bVar2 = false;
  local_10 = 0;
  if (DAT_008cf248 != 3 && -1 < DAT_008cf248 + -3) {
    a2 = &DAT_008cf0c8;
    do {
      pfVar6 = (float *)(a2 + -3);
      a1 = a2 + -6;
      this = (void *)Planner_SharedSector(a1,pfVar6);
      iVar3 = Planner_SharedSector(pfVar6,a2);
      if (this == (void *)0x0) {
        return 1;
      }
      if (iVar3 == 0) {
        return 1;
      }
      Sector_FindExitPoint(this,(int)a1,(int)a2,(int)&local_c);
      iVar3 = Planner_SharedSector(&local_c,a1);
      iVar4 = Planner_SharedSector(&local_c,a2);
      if (((iVar4 != 0) && (iVar3 != 0)) &&
         (0.0025000002 <
          (local_4 - (float)a2[-1]) * (local_4 - (float)a2[-1]) +
          (local_8 - (float)a2[-2]) * (local_8 - (float)a2[-2]) +
          (local_c - *pfVar6) * (local_c - *pfVar6))) {
        *pfVar6 = local_c;
        a2[-2] = local_8;
        a2[-1] = local_4;
        bVar2 = true;
      }
      local_10 = local_10 + 1;
      a2 = a2 + 3;
    } while (local_10 < DAT_008cf248 + -3);
  }
  if (DAT_008cf248 != 2 && -1 < DAT_008cf248 + -2) {
    pfVar6 = (float *)&DAT_008cf0b4;
    local_14 = 1;
    iVar3 = DAT_008cf248;
    do {
      if (((pfVar6[1] - pfVar6[4]) * (pfVar6[1] - pfVar6[4]) +
           (*pfVar6 - pfVar6[3]) * (*pfVar6 - pfVar6[3]) +
           (pfVar6[-1] - pfVar6[2]) * (pfVar6[-1] - pfVar6[2]) < 0.0001) &&
         (iVar4 = Planner_SharedSector(pfVar6 + -1,pfVar6 + 2), iVar3 = DAT_008cf248, iVar4 != 0)) {
        bVar2 = true;
        iVar3 = DAT_008cf248 + -1;
        DAT_008cf248 = iVar3;
        if (local_14 < iVar3) {
          iVar4 = iVar3 - local_14;
          pfVar5 = pfVar6 + 2;
          do {
            iVar4 = iVar4 + -1;
            *pfVar5 = pfVar5[3];
            pfVar5[1] = pfVar5[4];
            pfVar5[2] = pfVar5[5];
            pfVar5 = pfVar5 + 3;
          } while (iVar4 != 0);
        }
      }
      pfVar6 = pfVar6 + 3;
      bVar1 = local_14 < iVar3 + -2;
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
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a9ca0  Planner_SharedSector ---- */
int Planner_SharedSector(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = SectorList_FindByPoint(param_1,0x1000);
  while ((iVar1 != 0 && (iVar2 = Sector_ContainsPoint(param_2,1), iVar2 == 0))) {
    *(undefined4 *)(iVar1 + 0x2c) = 0;
    iVar1 = SectorList_FindByPoint(param_1,0x1000);
  }
  SectorList_ResetFree();
  return iVar1;
}
