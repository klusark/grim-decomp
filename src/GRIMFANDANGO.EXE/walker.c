/* GRIMFANDANGO.EXE :: walker.c
 * functions 0x00491230 .. 0x004a9ca0 (25 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00491230  Walker_UpdateYaw ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
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
  #define local_48 (*(uint *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x60 - 0x40)))
  #define local_38 (*(uint *)(_frame + (0x60 - 0x38)))
  #define local_30 (*(float (*)[12])(_frame + (0x60 - 0x30)))
  
  pvVar2 = param_1;
  pfVar3 = Actor_GetFrame(param_1);
  local_48 = PUN(uint,(float)pfVar3[3]);
  local_44 = PUN(uint,(float)pfVar3[4]);
  local_40 = PUN(uint,(float)pfVar3[5]);
  if (*(float *)(*(int *)((int)param_1 + 0xa4) + 0x24) != 0.0) {
    uVar6 = *(undefined4 *)(*(int *)((int)param_1 + 0xa4) + 0x24);
    pfVar3 = Actor_GetFrame(param_1);
    Matrix_AxisAngle(local_30,pfVar3 + 6,uVar6);
    Vec3_Transform((float *)&local_48,local_30);
  }
  local_48 = PUN(uint,(float)(PUN(float,local_48) + *param_2));
  local_44 = PUN(uint,(float)(param_2[1] + PUN(float,local_44)));
  local_40 = PUN(uint,(float)(param_2[2] + PUN(float,local_40)));
  Walker_ToLocalSpace(param_2,(float *)&local_48);
  local_40 = 0;
  Vec3_Normalize((float *)&local_48);
  fVar4 = Math_AsinDegreesSeries(PUN(float,local_44));
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
  if (PUN(float,local_48) <= 0.0) {
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
#undef local_40
#undef local_44
#undef local_48

#endif


/* ---- 0x00491650  Walker_ReplanPath ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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

#endif


/* ---- 0x004917e0  Walker_AvoidActorPath ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_124 */

uint Walker_AvoidActorPath
               (void *param_1,void *param_2,undefined4 *param_3,uint param_4,float *param_5)

{
  unsigned char _frame[0x140] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[336] __attribute__((aligned(16)));  /* the original frame below the return address */
  float fVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float *pfVar4;
  void *this;
  uint uVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  uint *puVar13;
  uint *puVar14;
  float *pfVar15;
  uint *puVar16;
  uint in_stack_fffffed0;
  uint uVar17;
  #define local_124 (*(uint *)(_frame + (0x140 - 0x124)))
  #define local_104 (*(uint *)(_frame + (0x140 - 0x104)))
  #define local_100 (*(uint *)(_frame + (0x140 - 0x100)))
  #define local_fc (*(uint *)(_frame + (0x140 - 0xfc)))
  #define local_f8 (*(uint *)(_frame + (0x140 - 0xf8)))
  #define local_f4 (*(uint *)(_frame + (0x140 - 0xf4)))
  #define local_f0 (*(uint *)(_frame + (0x140 - 0xf0)))
  #define local_ec (*(uint *)(_frame + (0x140 - 0xec)))
  #define local_e8 (*(uint *)(_frame + (0x140 - 0xe8)))
  #define local_e4 (*(uint *)(_frame + (0x140 - 0xe4)))
  #define local_e0 (*(uint *)(_frame + (0x140 - 0xe0)))
  #define local_dc (*(uint *)(_frame + (0x140 - 0xdc)))
  #define local_d8 (*(uint *)(_frame + (0x140 - 0xd8)))
  #define local_d4 (*(uint *)(_frame + (0x140 - 0xd4)))
  #define local_d0 (*(uint *)(_frame + (0x140 - 0xd0)))
  #define local_cc (*(uint *)(_frame + (0x140 - 0xcc)))
  #define local_c8 (*(uint *)(_frame + (0x140 - 0xc8)))
  #define local_c4 (*(uint *)(_frame + (0x140 - 0xc4)))
  #define local_c0 (*(uint *)(_frame + (0x140 - 0xc0)))
  #define local_bc (*(uint *)(_frame + (0x140 - 0xbc)))
  #define local_b8 (*(uint *)(_frame + (0x140 - 0xb8)))
  #define local_b4 (*(uint *)(_frame + (0x140 - 0xb4)))
  #define local_b0 (*(uint *)(_frame + (0x140 - 0xb0)))
  #define local_ac (*(uint *)(_frame + (0x140 - 0xac)))
  #define local_a8 (*(uint *)(_frame + (0x140 - 0xa8)))
  #define local_a4 (*(uint *)(_frame + (0x140 - 0xa4)))
  #define local_a0 (*(uint *)(_frame + (0x140 - 0xa0)))
  #define local_9c (*(uint *)(_frame + (0x140 - 0x9c)))
  #define local_98 (*(uint *)(_frame + (0x140 - 0x98)))
  #define local_94 (*(uint *)(_frame + (0x140 - 0x94)))
  #define local_90 (*(uint *)(_frame + (0x140 - 0x90)))
  #define local_8c (*(uint *)(_frame + (0x140 - 0x8c)))
  #define local_88 (*(float (*)[3])(_frame + (0x140 - 0x88)))
  #define local_7c (*(uint *)(_frame + (0x140 - 0x7c)))
  #define local_78 (*(uint *)(_frame + (0x140 - 0x78)))
  #define local_74 (*(uint *)(_frame + (0x140 - 0x74)))
  #define local_70 (*(uint *)(_frame + (0x140 - 0x70)))
  #define local_6c (*(uint *)(_frame + (0x140 - 0x6c)))
  #define local_68 (*(uint *)(_frame + (0x140 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0x140 - 0x64)))
  #define local_60 (*(uint *)(_frame + (0x140 - 0x60)))
  #define local_5c (*(uint *)(_frame + (0x140 - 0x5c)))
  #define local_58 (*(float (*)[2])(_frame + (0x140 - 0x58)))
  #define local_50 (*(uint *)(_frame + (0x140 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0x140 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x140 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x140 - 0x44)))
  #define local_1c (*(uint *)(_frame + (0x140 - 0x1c)))
  #define local_c (*(float (*)[3])(_frame + (0x140 - 0xc)))
  
  local_100 = 0;
  if (param_2 == (void *)0x0) {
    puVar2 = param_3;
    uVar10 = param_4;
    if ((int)param_4 < 1) {
      return 0;
    }
    do {
      puVar3 = puVar2 + 3;
      uVar10 = uVar10 - 1;
      *(undefined4 *)((int)param_5 + (-0xc - (int)param_3) + (int)puVar3) = *puVar2;
      *(undefined4 *)((int)param_5 + (-8 - (int)param_3) + (int)puVar3) = puVar2[1];
      *(undefined4 *)((int)param_5 + (-4 - (int)param_3) + (int)puVar3) = puVar2[2];
      puVar2 = puVar3;
    } while (uVar10 != 0);
    return param_4;
  }
  iVar7 = *(int *)(*(int *)(*(int *)((int)param_1 + 0xa0) + 4) + 4);
  local_104 = PUN(uint,(float)(*(float *)(*(int *)((int)param_1 + 0xa4) + 0x3f4) * *(float *)(iVar7 + 0x5c)));
  pfVar4 = Actor_GetFrame(param_1);
  Vec3_Copy(local_c,(float *)(iVar7 + 0x78),pfVar4);
  uVar10 = *(uint *)(*(int *)(*(int *)((int)param_2 + 0xa0) + 4) + 4);
  pfVar4 = Actor_GetFrame(param_2);
  Vec3_Sub(local_88,(float *)(uVar10 + 0x78),pfVar4);
  pfVar4 = Actor_GetFrame(param_2);
  Vec3_Copy((float *)&local_e8,(float *)(uVar10 + 0x78),pfVar4);
  iVar7 = *(int *)((int)param_2 + 0xa4);
  local_7c = PUN(uint,(float)(*(float *)(uVar10 + 0x60) * *(float *)(iVar7 + 0x3f4) - PUN(float,local_104)));
  puVar13 = param_3 + param_4 * 3 + -3;
  local_78 = PUN(uint,(float)(*(float *)(uVar10 + 100) * *(float *)(iVar7 + 0x3f4) - PUN(float,local_104)));
  local_74 = PUN(uint,(float)(*(float *)(uVar10 + 0x68) * *(float *)(iVar7 + 0x3f4) - PUN(float,local_104)));
  local_70 = PUN(uint,(float)(*(float *)(uVar10 + 0x6c) * *(float *)(iVar7 + 0x3f4) + PUN(float,local_104)));
  local_6c = PUN(uint,(float)(*(float *)(uVar10 + 0x70) * *(float *)(iVar7 + 0x3f4) + PUN(float,local_104)));
  local_68 = PUN(uint,(float)(*(float *)(uVar10 + 0x74) * *(float *)(iVar7 + 0x3f4) + PUN(float,local_104)));
  Actor_GetFrame(param_2);
  puVar14 = &local_7c;
  puVar16 = (uint *)(_stkneg + 28);
  for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar16 = *puVar14;
    puVar14 = puVar14 + 1;
    puVar16 = puVar16 + 1;
  }
  ((code *)Collision_PushOutOfBox)(puVar13);
  Actor_GetFrame(param_2);
  puVar14 = &local_7c;
  puVar16 = (uint *)(_stkneg + 28);
  for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar16 = *puVar14;
    puVar14 = puVar14 + 1;
    puVar16 = puVar16 + 1;
  }
  ((code *)Collision_PushOutOfBox)(param_3);
  local_d0 = *puVar13;
  local_cc = puVar13[1];
  local_c8 = puVar13[2];
  iVar7 = ((code *)SectorList_FindByPoint)();
  if (iVar7 == 0) {
    return 0;
  }
  uVar11 = 0;
  local_f8 = param_4 - 1;
  local_f0 = 0;
  if (0 < (int)local_f8) {
    pfVar9 = (float *)(param_3 + 2);
    pfVar4 = param_5;
    do {
      local_64 = PUN(uint,(float)(PUN(float,local_e8) + pfVar9[-2]));
      local_fc = (uint)(pfVar4 + 3);
      uVar11 = local_100 + 1;
      local_60 = PUN(uint,(float)(pfVar9[-1] + PUN(float,local_e4)));
      local_5c = PUN(uint,(float)(PUN(float,local_e0) + *pfVar9));
      local_a0 = PUN(uint,(float)(pfVar9[1] + PUN(float,local_e8)));
      local_9c = PUN(uint,(float)(pfVar9[2] + PUN(float,local_e4)));
      local_98 = PUN(uint,(float)(pfVar9[3] + PUN(float,local_e0)));
      *pfVar4 = pfVar9[-2];
      pfVar4[1] = pfVar9[-1];
      pfVar4[2] = *pfVar9;
      Actor_GetFrame(param_2);
      puVar13 = &local_7c;
      puVar14 = (uint *)(_stkneg + 32);
      for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar14 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar14 = puVar14 + 1;
      }
      iVar7 = ((code *)Collision_SegmentHitsBox)(&local_64,&local_a0);
      local_100 = uVar11;
      if (iVar7 != 0) {
        pfVar4 = Actor_GetFrame(param_2);
        Vec3_Sub(local_58,(float *)&DAT_008ca320,pfVar4);
        this = (void *)((code *)SectorList_FindNearestPoint)();
        Sector_SnapToPlane(this,local_58);
        Actor_GetFrame(param_2);
        uVar17 = 0x491ba9;
        ((code *)Collision_BoxCorners)();
        puVar13 = &local_1c;
        pfVar4 = (float *)&local_4c;
        local_f4 = 4;
        do {
          *puVar13 = 0;
          local_a0 = PUN(uint,(float)(PUN(float,local_e8) + *pfVar4));
          local_9c = PUN(uint,(float)(pfVar4[1] + PUN(float,local_e4)));
          local_98 = PUN(uint,(float)(PUN(float,local_e0) + pfVar4[2]));
          Actor_GetFrame(param_2);
          pfVar9 = local_88;
          puVar14 = &local_7c;
          puVar16 = (uint *)(_stkneg + 32);
          for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
            *puVar16 = *puVar14;
            puVar14 = puVar14 + 1;
            puVar16 = puVar16 + 1;
          }
          iVar7 = ((code *)Collision_SegmentHitsBox)(&local_64,&local_a0);
          if ((iVar7 == 0) && (iVar7 = ((code *)Planner_PlanPath)(), iVar7 != 0)) {
            *puVar13 = 1;
          }
          pfVar4 = pfVar4 + 3;
          puVar13 = puVar13 + 1;
          local_f4 = local_f4 - 1;
        } while (local_f4 != 0);
        uVar5 = ((code *)Collision_PickDetour)();
        if (uVar5 == 0xffffffff) {
          return uVar11;
        }
        local_d8 = uVar5;
        ((code *)Planner_PlanPath)();
        iVar7 = ((code *)Planner_GetPath)();
        if (0 < iVar7) {
          local_100 = uVar11 + iVar7;
          pfVar4 = param_5 + uVar11 * 3;
          pfVar15 = (float *)local_fc;
          do {
            iVar7 = iVar7 + -1;
            *pfVar4 = *pfVar15;
            pfVar4[1] = pfVar15[1];
            pfVar4[2] = pfVar15[2];
            pfVar4 = pfVar4 + 3;
            pfVar15 = pfVar15 + 3;
            uVar5 = local_d8;
          } while (iVar7 != 0);
        }
        pfVar15 = (float *)&local_e8;
        (&local_1c)[uVar5] = 0;
        local_f4 = (uint)(param_5 + local_100 * 3);
        pfVar4 = (float *)(local_f4 + -0xc);
        uVar11 = 0x491d51;
        pfVar6 = Actor_GetFrame(param_2);
        puVar13 = &local_7c;
        puVar14 = (uint *)(_stkneg + 28);
        for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar14 = *puVar13;
          puVar13 = puVar13 + 1;
          puVar14 = puVar14 + 1;
        }
        iVar7 = Collision_PointInBox
                          (pfVar4,(float *)&local_d0,local_88,(uint)pfVar9,in_stack_fffffed0,uVar17,
                           uVar10,0x491cca,uVar11,(uint)pfVar6,pfVar15);
        if (iVar7 != 0) {
          iVar7 = ((code *)Planner_GetPath)();
          if (iVar7 < 1) {
            return local_100;
          }
          uVar10 = local_100 + iVar7;
          do {
            iVar7 = iVar7 + -1;
            *(float *)local_f4 = *(float *)local_fc;
            *(float *)(local_f4 + 4) = *(float *)(local_fc + 4);
            *(float *)(local_f4 + 8) = *(float *)(local_fc + 8);
            local_f4 = (uint)(local_f4 + 0xc);
            local_fc = (uint)(local_fc + 0xc);
          } while (iVar7 != 0);
          return uVar10;
        }
        uVar11 = (int)(local_d8 + 3) >> 0x1f;
        uVar11 = ((local_d8 + 3 ^ uVar11) - uVar11 & 3 ^ uVar11) - uVar11;
        uVar5 = (int)(local_d8 + 5) >> 0x1f;
        uVar5 = ((local_d8 + 5 ^ uVar5) - uVar5 & 3 ^ uVar5) - uVar5;
        local_dc = uVar5;
        local_f0 = ((code *)Planner_PlanPath)();
        iVar7 = ((code *)Planner_PlanPath)();
        if (iVar7 != 0) {
          if (local_f0 == 0) goto LAB_00491fa5;
          local_104 = PUN(uint,(float)(*pfVar4 - (float)(&local_4c)[uVar11 * 3]));
          local_bc = PUN(uint,(float)(*(float *)(local_f4 + -8) - (float)(&local_48)[uVar11 * 3]));
          local_b8 = PUN(uint,(float)(*(float *)(local_f4 + -4) - (float)(&local_44)[uVar11 * 3]));
          local_c0 = PUN(uint,(float)((float)(&local_4c)[uVar11 * 3] - PUN(float,local_d0)));
          local_c4 = PUN(uint,(float)((float)(&local_48)[uVar11 * 3] - PUN(float,local_cc)));
          local_b0 = PUN(uint,(float)((float)(&local_44)[uVar11 * 3] - PUN(float,local_c8)));
          local_b4 = PUN(uint,(float)(*pfVar4 - (float)(&local_4c)[uVar5 * 3]));
          local_d4 = PUN(uint,(float)(*(float *)(local_f4 + -8) - (float)(&local_48)[uVar5 * 3]));
          local_f8 = PUN(uint,(float)(*(float *)(local_f4 + -4) - (float)(&local_44)[uVar5 * 3]));
          local_fc = PUN(uint,(float)((float)(&local_48)[uVar5 * 3] - PUN(float,local_cc)));
          fVar1 = (float)(&local_44)[uVar5 * 3] - PUN(float,local_c8);
          if (fVar1 * fVar1 +
              PUN(float,local_fc) * PUN(float,local_fc) +
              ((float)(&local_4c)[uVar5 * 3] - PUN(float,local_d0)) *
              ((float)(&local_4c)[uVar5 * 3] - PUN(float,local_d0)) +
              PUN(float,local_f8) * PUN(float,local_f8) +
              PUN(float,local_d4) * PUN(float,local_d4) + PUN(float,local_b4) * PUN(float,local_b4) <=
              PUN(float,local_b0) * PUN(float,local_b0) +
              PUN(float,local_c4) * PUN(float,local_c4) + PUN(float,local_c0) * PUN(float,local_c0) +
              PUN(float,local_b8) * PUN(float,local_b8) +
              PUN(float,local_bc) * PUN(float,local_bc) + PUN(float,local_104) * PUN(float,local_104)) {
            local_f0 = 0;
          }
          else {
            iVar7 = 0;
          }
        }
        if (local_f0 != 0) {
          local_f8 = 0xffffffff;
          local_104 = uVar11;
        }
LAB_00491fa5:
        if (iVar7 != 0) {
          local_f8 = 1;
          local_104 = local_dc;
        }
        if (local_104 == local_d8) {
          return local_100;
        }
        while( true ) {
          ((code *)Planner_PlanPath)();
          pfVar4 = (float *)((code *)Planner_GetPath)();
          local_dc = (int)pfVar4 - 1;
          iVar7 = 0;
          if (0 < (int)local_dc) {
            iVar12 = 0;
            do {
              local_ac = PUN(uint,(float)(PUN(float,local_e8) + *(float *)(local_fc + iVar12)));
              local_a8 = PUN(uint,(float)(*(float *)(local_fc + 4 + iVar12) + PUN(float,local_e4)));
              local_a4 = PUN(uint,(float)(*(float *)(local_fc + 8 + iVar12) + PUN(float,local_e0)));
              local_94 = PUN(uint,(float)(*(float *)(local_fc + 0xc + iVar12) + PUN(float,local_e8)));
              local_90 = PUN(uint,(float)(*(float *)(local_fc + 0x10 + iVar12) + PUN(float,local_e4)));
              local_8c = PUN(uint,(float)(*(float *)(local_fc + 0x14 + iVar12) + PUN(float,local_e0)));
              Actor_GetFrame(param_2);
              puVar13 = &local_7c;
              puVar14 = (uint *)(_stkneg + 32);
              for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
                *puVar14 = *puVar13;
                puVar13 = puVar13 + 1;
                puVar14 = puVar14 + 1;
              }
              pfVar9 = local_88;
              iVar8 = ((code *)Collision_SegmentHitsBox)(&local_ac,&local_94);
              if (iVar8 != 0) {
                return 0;
              }
              iVar7 = iVar7 + 1;
              iVar12 = iVar12 + 0xc;
            } while (iVar7 < (int)local_dc);
          }
          if (0 < (int)pfVar4) {
            local_100 = local_100 + (int)pfVar4;
            puVar2 = (undefined4 *)local_fc;
            pfVar15 = pfVar4;
            do {
              pfVar15 = (float *)((int)pfVar15 + -1);
              *(undefined4 *)local_f4 = *puVar2;
              *(undefined4 *)(local_f4 + 4) = puVar2[1];
              *(undefined4 *)(local_f4 + 8) = puVar2[2];
              local_f4 = (uint)(local_f4 + 0xc);
              puVar2 = puVar2 + 3;
            } while (pfVar15 != (float *)0x0);
          }
          pfVar15 = (float *)&local_e8;
          local_f4 = (uint)(param_5 + local_100 * 3);
          uVar11 = 0x492118;
          pfVar6 = Actor_GetFrame(param_2);
          puVar13 = &local_7c;
          puVar14 = (uint *)(_stkneg + 28);
          for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
            *puVar14 = *puVar13;
            puVar13 = puVar13 + 1;
            puVar14 = puVar14 + 1;
          }
          iVar7 = Collision_PointInBox
                            ((float *)(local_f4 + -0xc),(float *)&local_d0,local_88,(uint)pfVar9,
                             in_stack_fffffed0,uVar17,uVar10,0x491fde,uVar11,(uint)pfVar6,pfVar15);
          if (iVar7 != 0) break;
          uVar11 = local_f8 + 4 + local_104;
          uVar5 = (int)uVar11 >> 0x1f;
          local_104 = ((uVar11 ^ uVar5) - uVar5 & 3 ^ uVar5) - uVar5;
          if (local_104 == local_d8) {
            return local_100;
          }
        }
        local_d4 = ((code *)Planner_GetPath)();
        iVar7 = 0;
        local_dc = local_d4 - 1;
        local_f8 = 0;
        if (0 < (int)local_dc) {
          do {
            local_94 = PUN(uint,(float)(PUN(float,local_e8) + *(float *)((int)pfVar4 + iVar7)));
            local_90 = PUN(uint,(float)(*(float *)((int)pfVar4 + iVar7 + 4) + PUN(float,local_e4)));
            local_8c = PUN(uint,(float)(*(float *)((int)pfVar4 + iVar7 + 8) + PUN(float,local_e0)));
            local_ac = PUN(uint,(float)(*(float *)((int)pfVar4 + iVar7 + 0xc) + PUN(float,local_e8)));
            local_a8 = PUN(uint,(float)(*(float *)((int)pfVar4 + iVar7 + 0x10) + PUN(float,local_e4)));
            local_a4 = PUN(uint,(float)(*(float *)((int)pfVar4 + iVar7 + 0x14) + PUN(float,local_e0)));
            Actor_GetFrame(param_2);
            puVar13 = &local_7c;
            puVar14 = (uint *)(_stkneg + 32);
            for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
              *puVar14 = *puVar13;
              puVar13 = puVar13 + 1;
              puVar14 = puVar14 + 1;
            }
            iVar12 = ((code *)Collision_SegmentHitsBox)(&local_94,&local_ac);
            if (iVar12 != 0) {
              return 0;
            }
            local_f8 = local_f8 + 1;
            iVar7 = iVar7 + 0xc;
          } while ((int)local_f8 < (int)local_dc);
        }
        uVar10 = local_100;
        if (0 < (int)local_d4) {
          uVar10 = local_100 + local_d4;
          pfVar9 = param_5 + local_100 * 3;
          do {
            local_d4 = local_d4 - 1;
            *pfVar9 = *pfVar4;
            pfVar9[1] = pfVar4[1];
            pfVar9[2] = pfVar4[2];
            pfVar9 = pfVar9 + 3;
            pfVar4 = pfVar4 + 3;
          } while (local_d4 != 0);
        }
        return uVar10;
      }
      uVar11 = local_f0 + 1;
      pfVar9 = pfVar9 + 3;
      pfVar4 = (float *)local_fc;
      local_f0 = uVar11;
    } while ((int)uVar11 < (int)local_f8);
  }
  pfVar4 = (float *)(param_3 + uVar11 * 3);
  param_5 = param_5 + local_100 * 3;
  *param_5 = *pfVar4;
  param_5[1] = pfVar4[1];
  param_5[2] = pfVar4[2];
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
#undef local_5c
#undef local_60
#undef local_64
#undef local_68
#undef local_6c
#undef local_70
#undef local_74
#undef local_78
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
#undef local_ec
#undef local_f0
#undef local_f4
#undef local_f8
#undef local_fc

#endif


/* ---- 0x00494880  Walker_SetFadeTime ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua SetWalkSystemFadeTime */

void __cdecl Walker_SetFadeTime(int ms)

{
  g_nChoreFadeMs = ms;
  return;
}
#endif


/* ---- 0x004a8200  Walker_Create ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
#endif


/* ---- 0x004a8270  Walker_Destroy ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
#endif


/* ---- 0x004a82a0  Walker_GetAngles ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Converts the walker's 3x3 frame to pitch/yaw/roll in g_vWalkerAngles */

undefined * __fastcall Walker_GetAngles(int param_1)

{
  Matrix_ToAngles(param_1 + 0xc,&DAT_008cf250);
  return &DAT_008cf250;
}
#endif


/* ---- 0x004a82c0  Walker_ReattachToSet ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
#endif


/* ---- 0x004a8310  Walker_SetPosition ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
#endif


/* ---- 0x004a8350  Walker_RotateVector ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void __thiscall Walker_RotateVector(void *this,float *vec)

{
  Vec3_Rotate3x3(vec,(float *)((int)this + 0xc));
  return;
}
#endif


/* ---- 0x004a8370  Walker_ToLocalSpace ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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

#endif


/* ---- 0x004a83c0  Walker_TurnHeading ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
undefined * __thiscall Walker_TurnHeading(void *this,int a1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *vec;
  undefined *extraout_EAX;
  #define local_30 (*(float (*)[12])(_frame + (0x40 - 0x30)))
  
  Matrix_AxisAngle(local_30,(int)this + 0x24,a1);
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
  return extraout_EAX;
}
#undef local_30

#endif


/* ---- 0x004a8450  Walker_TurnToPoint ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
float __thiscall Walker_TurnToPoint(void *this,int a1,int a2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_c = *(float *)a1;
  local_8 = *(float *)(a1 + 4);
  local_4 = *(uint *)(a1 + 8);
  if (*(void **)((int)this + 0x5c) != (void *)0x0) {
    Sector_FixPlaneCoordinate(*(void **)((int)this + 0x5c),(int)&local_c);
  }
  Walker_ToLocalSpace(this,&local_c);
  Vec3_Normalize(&local_c);
  fVar1 = Math_AsinDegreesSeries(local_8);
  a1 = PUN(int,(float)(90.0 - fVar1));
  if (PUN(float,a2) < PUN(float,a1)) {
    a1 = a2;
  }
  if (0.0 < local_c) {
    a1 = PUN(int,(float)(PUN(float,a1) * -1.0));
  }
  Walker_TurnHeading(this,a1);
  return PUN(float,a1);
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a85b0  Walker_SetConstraint ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
undefined * __thiscall Walker_SetConstraint(void *this,int a1)

{
  undefined *in_EAX;
  float *pfVar1;
  undefined *extraout_EAX;
  
  *(undefined4 *)((int)this + 0x50) = 0;
  if ((*(void **)((int)this + 0x5c) != (void *)0x0) && (in_EAX = (undefined *)0x0, a1 != 0)) {
    pfVar1 = Sector_EdgeFollowDirection(*(void **)((int)this + 0x5c),this);
    in_EAX = (undefined *)0x0;
    if (pfVar1 != (float *)0x0) {
      *(float *)((int)this + 0x44) = *pfVar1;
      *(float *)((int)this + 0x48) = pfVar1[1];
      *(float *)((int)this + 0x4c) = pfVar1[2];
      *(float *)((int)this + 0x18) = *pfVar1;
      *(float *)((int)this + 0x1c) = pfVar1[1];
      *(float *)((int)this + 0x20) = pfVar1[2];
      Walker_RebuildRightVector((int)this);
      *(undefined4 *)((int)this + 0x50) = 1;
      in_EAX = extraout_EAX;
    }
  }
  return in_EAX;
}
#endif


/* ---- 0x004a8610  Walker_WalkSectors ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_48 */
/* Walker_WalkSectors: the per-frame walk of an actor over the walk sectors (target-inside test with
   tolerance, exit point of the edge, neighbour lookup with the current sector deactivated, 0.02 cap
   into the new sector, reflection turn only when |angle| < reflect and not against a held turn
   key). See autorun/NAV_PLAN.md and COLLISION_FIX_PLAN.md. */

undefined * __thiscall Walker_WalkSectors(void *this,int a1,int a2,int a3)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *this_00;
  int iVar1;
  undefined *puVar2;
  float fVar3;
  #define local_48 (*(float *)(_frame + (0x60 - 0x48)))
  #define local_34 (*(float *)(_frame + (0x60 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x60 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x60 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x60 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x60 - 0x24)))
  #define local_20 (*(float *)(_frame + (0x60 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x60 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x60 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x60 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x60 - 0x10)))
  #define local_c (*(float *)(_frame + (0x60 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x60 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x60 - 0x4)))
  
  puVar2 = (undefined *)0x0;
  if (UINT_008d0870 == 0) {
    *(int *)((int)this + 0x40) = a1;
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
    Walker_TurnHeading(this,PUN(int,(float)local_48));
  }
  local_30 = 0;
  local_2c = a1;
  local_28 = 0;
  Walker_RotateVector(this,(float *)&local_30);
  if ((*(void **)((int)this + 0x5c) == (void *)0x0) ||
     (iVar1 = Sector_ContainsPoint(*(void **)((int)this + 0x5c),(float *)&local_30,1), iVar1 != 0))
  {
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
  Walker_ToLocalSpace(this,(float *)&local_18);
  a1 = PUN(int,(float)(PUN(float,a1) - local_14));
  iVar1 = SectorList_FindByPoint(&local_24,0x1000);
  if (iVar1 == 0) {
    Walker_SetPosition(this,(float *)&local_24);
    iVar1 = *(int *)((int)this + 0x5c);
    if ((*(uint *)(iVar1 + 0x24) & 0x100) == 0) {
      fVar3 = local_34;
      if (local_34 < 0.0) {
        fVar3 = -local_34;
      }
      if ((*(float *)((int)this + 0x3c) <= fVar3) || (*(int *)((int)this + 0x50) != 0)) {
        *(float *)((int)this + 0x40) = *(float *)((int)this + 0x40) - PUN(float,a1);
      }
      else if (((0.0 < local_34) && (a2 != 0)) || ((local_34 < 0.0 && (a3 != 0)))) {
        Walker_TurnHeading(this,PUN(int,(float)local_34));
        *(undefined4 *)((int)this_00 + 0x2c) = 1;
        puVar2 = Walker_WalkSectors(this,a1,1,1);
      }
      if (*(int *)((int)this + 0x50) != 0) {
        Walker_TurnHeading(this,PUN(int,(float)local_34));
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
      Walker_TurnHeading(this,PUN(int,(float)local_34));
      puVar2 = Walker_WalkSectors(this,a1,1,1);
      *(undefined4 *)((int)this_00 + 0x2c) = 1;
      return puVar2;
    }
    return (undefined *)0x0;
  }
  Walker_SetPosition(this,(float *)&local_24);
  *(int *)((int)this + 0x5c) = iVar1;
  Walker_SetSectorFrame(this,iVar1);
  if (0.02 <= PUN(float,a1)) {
    a1 = 0x3ca3d70a;
  }
  puVar2 = Walker_WalkSectors(this,a1,1,1);
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

#endif


/* ---- 0x004a89b0  Walker_SetSectorFrame ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
undefined * __thiscall Walker_SetSectorFrame(void *this,int a1)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  undefined *extraout_EAX;
  
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
  return extraout_EAX;
}
#endif


/* ---- 0x004a8a90  Walker_RebuildRightVector ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
#endif


/* ---- 0x004a8b00  Walker_DrawDebugAxes ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void __stdcall Walker_DrawDebugAxes(int color)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *in_ECX;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  local_18 = 0;
  local_14 = 0x3dcccccd;
  local_10 = 0;
  Walker_RotateVector(in_ECX,(float *)&local_c);
  Walker_RotateVector(in_ECX,(float *)&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,color,0xffffffff);
  local_c = 0x3d4ccccd;
  local_8 = 0x3d4ccccd;
  local_4 = 0;
  local_18 = 0;
  local_14 = 0x3dcccccd;
  local_10 = 0;
  Walker_RotateVector(in_ECX,(float *)&local_c);
  Walker_RotateVector(in_ECX,(float *)&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,color,0xffffffff);
  local_c = 0xbd4ccccd;
  local_8 = 0x3d4ccccd;
  local_4 = 0;
  local_18 = 0;
  local_14 = 0x3dcccccd;
  local_10 = 0;
  Walker_RotateVector(in_ECX,(float *)&local_c);
  Walker_RotateVector(in_ECX,(float *)&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,color,0xffffffff);
  local_c = 0;
  local_8 = 0;
  local_4 = 0x3d4ccccd;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  Walker_RotateVector(in_ECX,(float *)&local_c);
  Walker_RotateVector(in_ECX,(float *)&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,color,0xffffffff);
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a9420  Planner_GetPath ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
uint Planner_GetPath(undefined4 *param_1)

{
  *param_1 = &UINT_008cf0b0;
  return UINT_008cf248;
}
#endif


/* ---- 0x004a9430  Planner_PlanPath ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
#endif


/* ---- 0x004a94d0  Planner_SearchSectors ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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

#endif


/* ---- 0x004a96f0  Planner_CollectSharedCorners ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
            fVar1 = fVar1 - (float)(&local_1e0)[uVar6 * 4];
            (&local_1d4)[uVar6 * 4] =
                 PUN(uint,(float)((fVar3 - (float)(&local_1d8)[uVar6 * 4]) *
                        (fVar3 - (float)(&local_1d8)[uVar6 * 4]) +
                       (fVar2 - (float)(&local_1dc)[uVar6 * 4]) *
                       (fVar2 - (float)(&local_1dc)[uVar6 * 4]) + fVar1 * fVar1));
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

#endif


/* ---- 0x004a9920  Planner_PortalPoint ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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

#endif


/* ---- 0x004a9aa0  Planner_SmoothPath ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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

#endif


/* ---- 0x004a9ca0  Planner_SharedSector ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
#endif

