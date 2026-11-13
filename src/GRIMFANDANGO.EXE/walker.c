/* GRIMFANDANGO.EXE :: walker.c
 * functions 0x00491230 .. 0x004a9ca0 (25 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00491230  sputActor_AlignToPuck ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Walker_UpdateYaw(actor, pos): eases the visible yaw (actor+0x28) toward the walker heading. Done
   (returns 1) when under 0.5 deg. step = rate*frameSec*timescale; if remaining > step, step =
   (remaining - step)*0.1 + step. Rate <= 0 (snap) jumps the whole way and re-negates the rate.
   Original name sputActor_AlignToPuck (the remaster's GrimFandango (Linux): same body (the actor's
   orientation vector, rotated by the costume's +0x24 angle with rdMatrix_BuildFromVectorAngle34,
   offset by the puck position, into the puck's space with Puck_InvXform)); was Walker_UpdateYaw. */

undefined4 __cdecl sputActor_AlignToPuck(Actor *actor,float *param_2)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ActorExtra *pAVar1;
  Actor *pAVar2;
  float fVar3;
  Actor *pAVar4;
  float *pfVar5;
  float fVar6;
  #define local_48 (*(float (*)[3])(_frame + (0x60 - 0x48)))
  #define local_38 (*(uint *)(_frame + (0x60 - 0x38)))
  #define local_30 (*(float (*)[12])(_frame + (0x60 - 0x30)))
  
  pAVar4 = actor;
  pfVar5 = sputActor_GetOrientMatrix(actor);
  local_48[0] = pfVar5[3];
  local_48[1] = pfVar5[4];
  local_48[2] = pfVar5[5];
  if (actor->pExtra->flOffsetYaw != 0.0) {
    fVar6 = actor->pExtra->flOffsetYaw;
    pfVar5 = sputActor_GetOrientMatrix(actor);
    rdMatrix_BuildFromVectorAngle34(local_30,pfVar5 + 6,fVar6);
    rdMatrix_TransformVector34Acc(local_48,local_30);
  }
  local_48[0] = local_48[0] + *param_2;
  local_48[1] = param_2[1] + local_48[1];
  local_48[2] = param_2[2] + local_48[2];
  Puck_InvXform((Puck *)param_2,local_48);
  local_48[2] = 0.0;
  rdVector_Normalize3Acc(local_48);
  fVar6 = stdMath_ArcSin3(local_48[1]);
  pAVar2 = PUN(Actor *,(float)(90.0 - fVar6));
  if (PUN(float,pAVar2) < 0.5) {
    actor->pExtra->flYawLeft = 0.0;
    return 1;
  }
  actor->pExtra->flYawLeft = PUN(float,pAVar2);
  pAVar1 = actor->pExtra;
  if (pAVar1->flTurnRate <= 0.0) {
    fVar6 = 3.4028235e+38;
    pAVar1->flTurnRate = pAVar1->flTurnRate * -1.0;
  }
  else {
    fVar6 = sputTime_GetFrameTimeFlex();
    fVar6 = fVar6 * pAVar1->flTimeScale * pAVar1->flTurnRate;
  }
  actor = pAVar2;
  if (fVar6 < PUN(float,pAVar2)) {
    actor = PUN(Actor *,(float)((PUN(float,pAVar2) - fVar6) * 0.1 + fVar6));
  }
  fVar6 = pAVar4->aRot[2];
  if (local_48[0] <= 0.0) {
    fVar3 = pAVar4->aRot[1] - PUN(float,actor);
  }
  else {
    fVar3 = pAVar4->aRot[1] + PUN(float,actor);
  }
  pAVar4->aRot[0] = pAVar4->aRot[0];
  pAVar4->aRot[1] = fVar3;
  pAVar4->aRot[2] = fVar6;
  pAVar4->nMatrixDirty = 0;
  return 0;
}
#undef local_30
#undef local_38
#undef local_48

#endif


/* ---- 0x00491650  sputActor_ActorWalkTo ---- */
/* Original name sputActor_ActorWalkTo (the remaster's GrimFandango (Linux): aligned call in
   sputLua_WalkActorToAvoidingL, sputLua_WalkActorToL); was Walker_ReplanPath. */

void __cdecl sputActor_ActorWalkTo(Actor *actor,int param_2,undefined4 *param_3,undefined4 param_4)

{
  unsigned char _frame[0x2f0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  float (*pafVar2) [3];
  Puck *pPVar3;
  ActorExtra *pAVar4;
  WalkPlane *this;
  int iVar5;
  uint *puVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  #define local_2d8 (*(uint *)(_frame + (0x2f0 - 0x2d8)))
  #define local_2d4 (*(uint *)(_frame + (0x2f0 - 0x2d4)))
  #define local_2d0 (*(uint *)(_frame + (0x2f0 - 0x2d0)))
  #define local_2cc (*(uint *)(_frame + (0x2f0 - 0x2cc)))
  #define local_2c8 (*(uint *)(_frame + (0x2f0 - 0x2c8)))
  #define auStack_1b0 (*(undefined4 (*)[18])(_frame + (0x2f0 - 0x1b0)))
  #define local_168 (*(uint *)(_frame + (0x2f0 - 0x168)))
  #define local_164 (*(uint *)(_frame + (0x2f0 - 0x164)))
  #define local_160 (*(uint *)(_frame + (0x2f0 - 0x160)))
  
  actor->dwMoveFlags = actor->dwMoveFlags & 0xfffffffe;
  pPVar3 = actor->pExtra->pPuck;
  if ((pPVar3 != (Puck *)0x0) && (g_pWalkPlane_wp_head != (WalkPlane *)0x0)) {
    this = WalkPlane_PlaneClosest((float *)param_2,0x1000);
    if (this != (WalkPlane *)0x0) {
      WalkPlane_ClosestPoint(this,param_2);
    }
    iVar5 = BuildPath(pPVar3,param_2,1);
    if (iVar5 != 0) {
      iVar5 = GetPath(&local_2d4);
      if (0 < iVar5) {
        puVar6 = &local_2d0;
        iVar8 = iVar5;
        do {
          puVar1 = (uint *)((local_2d4 - (int)&local_2d0) + (int)puVar6);
          iVar8 = iVar8 + -1;
          *puVar6 = *puVar1;
          puVar6[1] = puVar1[1];
          puVar6[2] = puVar1[2];
          puVar6 = puVar6 + 3;
        } while (iVar8 != 0);
      }
      iVar5 = Walker_AvoidActorPath(actor,param_4,&local_2d0,iVar5,&local_168);
      actor->pExtra->nPathNodes = iVar5;
      actor->pExtra->nPathIndex = 1;
      if (0 < iVar5) {
        iVar8 = 0x48;
        iVar9 = iVar5;
        do {
          puVar7 = (undefined4 *)((int)actor->pExtra->aLookAt + iVar8);
          iVar9 = iVar9 + -1;
          *puVar7 = *(undefined4 *)((int)auStack_1b0 + iVar8);
          puVar7[1] = *(undefined4 *)((int)auStack_1b0 + iVar8 + 4);
          puVar7[2] = *(undefined4 *)((int)auStack_1b0 + iVar8 + 8);
          iVar8 = iVar8 + 0xc;
        } while (iVar9 != 0);
      }
      pAVar4 = actor->pExtra;
      pafVar2 = pAVar4->aPath + pAVar4->nPathIndex;
      pAVar4->aWaypoint[0] = (*pafVar2)[0];
      pAVar4->aWaypoint[1] = (*pafVar2)[1];
      pAVar4->aWaypoint[2] = (*pafVar2)[2];
      if (1 < iVar5) {
        actor->dwMoveFlags = actor->dwMoveFlags | 1;
      }
    }
    pAVar4 = actor->pExtra;
    pAVar4->aDest[0] = PUN(float,*param_3);
    pAVar4->aDest[1] = PUN(float,param_3[1]);
    pAVar4->aDest[2] = PUN(float,param_3[2]);
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
/* Ported to C (build/overrides_big_walker_avoid.c): differential test vs stand-ins, 0 differences
   at -O0 (docs/notes/big_walker_avoid.md). */

uint Walker_AvoidActorPath
               (Actor *param_1,Actor *param_2,undefined4 *param_3,uint param_4,float *param_5)

{
  unsigned char _frame[0x140] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[336] __attribute__((aligned(16)));  /* the original frame below the return address */
  ActorExtra *pAVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  float *pfVar10;
  WalkPlane *pWVar11;
  float fVar12;
  float *pfVar13;
  int iVar14;
  int iVar15;
  float *pfVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  uint *puVar20;
  float *pfVar21;
  float *pfVar22;
  float fVar23;
  float *pfVar24;
  float in_stack_fffffed0;
  float bz0;
  float bx1;
  #define local_124 (*(uint *)(_frame + (0x140 - 0x124)))
  float fVar25;
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
  if (param_2 == (Actor *)0x0) {
    puVar8 = param_3;
    uVar17 = param_4;
    if ((int)param_4 < 1) {
      return 0;
    }
    do {
      puVar9 = puVar8 + 3;
      uVar17 = uVar17 - 1;
      *(undefined4 *)((int)param_5 + (-0xc - (int)param_3) + (int)puVar9) = *puVar8;
      *(undefined4 *)((int)param_5 + (-8 - (int)param_3) + (int)puVar9) = puVar8[1];
      *(undefined4 *)((int)param_5 + (-4 - (int)param_3) + (int)puVar9) = puVar8[2];
      puVar8 = puVar9;
    } while (uVar17 != 0);
    return param_4;
  }
  iVar14 = *(int *)((int)param_1->pCostumes->pMainModel + 4);
  local_104 = param_1->pExtra->flCollisionScale * *(float *)(iVar14 + 0x5c);
  pfVar10 = sputActor_GetOrientMatrix(param_1);
  rdMatrix_TransformVector34(local_c,(float *)(iVar14 + 0x78),pfVar10);
  bx1 = *(float *)((int)param_2->pCostumes->pMainModel + 4);
  pfVar10 = sputActor_GetOrientMatrix(param_2);
  rdMatrix_TransformPoint34(local_88,(float *)(PUN(int,(float)bx1) + 0x78),pfVar10);
  pfVar10 = sputActor_GetOrientMatrix(param_2);
  rdMatrix_TransformVector34(&local_e8,(float *)(PUN(int,(float)bx1) + 0x78),pfVar10);
  pAVar1 = param_2->pExtra;
  local_7c[0] = *(float *)(PUN(int,(float)bx1) + 0x60) * pAVar1->flCollisionScale - local_104;
  pfVar10 = (float *)(param_3 + param_4 * 3 + -3);
  local_7c[1] = *(float *)(PUN(int,(float)bx1) + 100) * pAVar1->flCollisionScale - local_104;
  local_7c[2] = *(float *)(PUN(int,(float)bx1) + 0x68) * pAVar1->flCollisionScale - local_104;
  sputActor_GetOrientMatrix(param_2);
  pfVar16 = local_7c;
  pfVar21 = (float *)(_stkneg + 28);
  for (iVar14 = 6; iVar14 != 0; iVar14 = iVar14 + -1) {
    *pfVar21 = *pfVar16;
    pfVar16 = pfVar16 + 1;
    pfVar21 = pfVar21 + 1;
  }
  ((code *)GetOuttaTheBox)(pfVar10);
  sputActor_GetOrientMatrix(param_2);
  pfVar16 = local_7c;
  pfVar21 = (float *)(_stkneg + 28);
  for (iVar14 = 6; iVar14 != 0; iVar14 = iVar14 + -1) {
    *pfVar21 = *pfVar16;
    pfVar16 = pfVar16 + 1;
    pfVar21 = pfVar21 + 1;
  }
  ((code *)GetOuttaTheBox)(param_3);
  local_d0 = *pfVar10;
  local_cc[0] = pfVar10[1];
  local_cc[1] = pfVar10[2];
  pWVar11 = WalkPlane_PlaneAt(&local_d0,0xffffffff);
  if (pWVar11 == (WalkPlane *)0x0) {
    return 0;
  }
  uVar17 = 0;
  local_f8 = PUN(float,(param_4 - 1));
  local_f0 = 0;
  if (0 < PUN(int,(float)local_f8)) {
    pfVar16 = (float *)(param_3 + 2);
    pfVar10 = param_5;
    do {
      local_64[0] = local_e8 + pfVar16[-2];
      local_fc = PUN(float,(pfVar10 + 3));
      uVar17 = local_100 + 1;
      local_64[1] = pfVar16[-1] + local_e4[0];
      local_64[2] = local_e4[1] + *pfVar16;
      local_a0[0] = pfVar16[1] + local_e8;
      local_a0[1] = pfVar16[2] + local_e4[0];
      local_a0[2] = pfVar16[3] + local_e4[1];
      *pfVar10 = pfVar16[-2];
      pfVar10[1] = pfVar16[-1];
      pfVar10[2] = *pfVar16;
      sputActor_GetOrientMatrix(param_2);
      pfVar10 = local_7c;
      pfVar21 = (float *)(_stkneg + 32);
      for (iVar14 = 6; iVar14 != 0; iVar14 = iVar14 + -1) {
        *pfVar21 = *pfVar10;
        pfVar10 = pfVar10 + 1;
        pfVar21 = pfVar21 + 1;
      }
      iVar14 = ((code *)TestCollision)(local_64,local_a0);
      local_100 = uVar17;
      if (iVar14 != 0) {
        pfVar10 = sputActor_GetOrientMatrix(param_2);
        rdMatrix_TransformPoint34(local_58,(float *)&DAT_008ca320,pfVar10);
        pWVar11 = WalkPlane_PlaneClosest(local_58,0xffffffff);
        WalkPlane_SnapTo(pWVar11,local_58);
        sputActor_GetOrientMatrix(param_2);
        bz0 = 6.713914e-39;
        ((code *)FindObjectCorners)();
        puVar20 = &local_1c;
        pfVar10 = &local_4c;
        local_f4 = 5.60519e-45;
        do {
          *puVar20 = 0;
          local_a0[0] = local_e8 + *pfVar10;
          local_a0[1] = pfVar10[1] + local_e4[0];
          local_a0[2] = local_e4[1] + pfVar10[2];
          sputActor_GetOrientMatrix(param_2);
          pfVar16 = local_88;
          pfVar21 = local_7c;
          pfVar22 = (float *)(_stkneg + 32);
          for (iVar14 = 6; iVar14 != 0; iVar14 = iVar14 + -1) {
            *pfVar22 = *pfVar21;
            pfVar21 = pfVar21 + 1;
            pfVar22 = pfVar22 + 1;
          }
          iVar14 = ((code *)TestCollision)(local_64,local_a0);
          if ((iVar14 == 0) && (iVar14 = ((code *)BuildPath)(), iVar14 != 0)) {
            *puVar20 = 1;
          }
          pfVar10 = pfVar10 + 3;
          puVar20 = puVar20 + 1;
          local_f4 = PUN(float,(PUN(int,(float)local_f4) + -1));
        } while (local_f4 != 0.0);
        fVar12 = (float)((code *)Collision_PickDetour)();
        if (fVar12 == -NAN) {
          return uVar17;
        }
        ((code *)BuildPath)();
        iVar14 = ((code *)GetPath)();
        if (0 < iVar14) {
          local_100 = uVar17 + iVar14;
          pfVar10 = param_5 + uVar17 * 3;
          pfVar21 = PUN(float *,(float)local_fc);
          do {
            iVar14 = iVar14 + -1;
            *pfVar10 = *pfVar21;
            pfVar10[1] = pfVar21[1];
            pfVar10[2] = pfVar21[2];
            pfVar10 = pfVar10 + 3;
            pfVar21 = pfVar21 + 3;
          } while (iVar14 != 0);
        }
        pfVar21 = &local_e8;
        (&local_1c)[PUN(int,(float)fVar12)] = 0;
        local_f4 = PUN(float,(param_5 + local_100 * 3));
        pfVar10 = (float *)(PUN(int,(float)local_f4) + -0xc);
        fVar25 = 6.714508e-39;
        pfVar13 = sputActor_GetOrientMatrix(param_2);
        pfVar22 = local_7c;
        pfVar24 = (float *)(_stkneg + 28);
        for (iVar14 = 6; iVar14 != 0; iVar14 = iVar14 + -1) {
          *pfVar24 = *pfVar22;
          pfVar22 = pfVar22 + 1;
          pfVar24 = pfVar24 + 1;
        }
        iVar14 = Collision_PointInBox
                           (pfVar10,&local_d0,local_88,PUN(float,pfVar16),in_stack_fffffed0,bz0,bx1,
                            6.714319e-39,fVar25,pfVar13,pfVar21);
        if (iVar14 != 0) {
          iVar14 = ((code *)GetPath)();
          if (iVar14 < 1) {
            return local_100;
          }
          uVar17 = local_100 + iVar14;
          do {
            iVar14 = iVar14 + -1;
            *PUN(float *,(float)local_f4) = *PUN(float *,(float)local_fc);
            *(float *)(PUN(int,(float)local_f4) + 4) = *(float *)(PUN(int,(float)local_fc) + 4);
            *(float *)(PUN(int,(float)local_f4) + 8) = *(float *)(PUN(int,(float)local_fc) + 8);
            local_f4 = PUN(float,(PUN(int,(float)local_f4) + 0xc));
            local_fc = PUN(float,(PUN(int,(float)local_fc) + 0xc));
          } while (iVar14 != 0);
          return uVar17;
        }
        uVar17 = (int)(PUN(int,(float)fVar12) + 3U) >> 0x1f;
        fVar25 = PUN(float,(((PUN(int,(float)fVar12) + 3U ^ uVar17) - uVar17 & 3 ^ uVar17) - uVar17));
        uVar17 = (int)(PUN(int,(float)fVar12) + 5U) >> 0x1f;
        fVar23 = PUN(float,(((PUN(int,(float)fVar12) + 5U ^ uVar17) - uVar17 & 3 ^ uVar17) - uVar17));
        local_f0 = ((code *)BuildPath)();
        iVar14 = ((code *)BuildPath)();
        if (iVar14 != 0) {
          if (local_f0 == 0) goto LAB_00491fa5;
          local_104 = *pfVar10 - (&local_4c)[PUN(int,(float)fVar25) * 3];
          fVar3 = *(float *)(PUN(int,(float)local_f4) + -8) - PUN(float,(&local_48)[PUN(int,(float)fVar25) * 3]);
          fVar4 = *(float *)(PUN(int,(float)local_f4) + -4) - PUN(float,(&local_44)[PUN(int,(float)fVar25) * 3]);
          fVar5 = PUN(float,(&local_48)[PUN(int,(float)fVar25) * 3]) - local_cc[0];
          fVar6 = PUN(float,(&local_44)[PUN(int,(float)fVar25) * 3]) - local_cc[1];
          fVar7 = *(float *)(PUN(int,(float)local_f4) + -8) - PUN(float,(&local_48)[PUN(int,(float)fVar23) * 3]);
          local_f8 = *(float *)(PUN(int,(float)local_f4) + -4) - PUN(float,(&local_44)[PUN(int,(float)fVar23) * 3]);
          local_fc = PUN(float,(&local_48)[PUN(int,(float)fVar23) * 3]) - local_cc[0];
          fVar2 = PUN(float,(&local_44)[PUN(int,(float)fVar23) * 3]) - local_cc[1];
          if (fVar2 * fVar2 +
              local_fc * local_fc +
              ((&local_4c)[PUN(int,(float)fVar23) * 3] - local_d0) * ((&local_4c)[PUN(int,(float)fVar23) * 3] - local_d0)
              + local_f8 * local_f8 +
                fVar7 * fVar7 +
                (*pfVar10 - (&local_4c)[PUN(int,(float)fVar23) * 3]) *
                (*pfVar10 - (&local_4c)[PUN(int,(float)fVar23) * 3]) <=
              fVar6 * fVar6 +
              fVar5 * fVar5 +
              ((&local_4c)[PUN(int,(float)fVar25) * 3] - local_d0) * ((&local_4c)[PUN(int,(float)fVar25) * 3] - local_d0)
              + fVar4 * fVar4 + fVar3 * fVar3 + local_104 * local_104) {
            local_f0 = 0;
          }
          else {
            iVar14 = 0;
          }
        }
        if (local_f0 != 0) {
          local_f8 = -NAN;
          local_104 = fVar25;
        }
LAB_00491fa5:
        if (iVar14 != 0) {
          local_f8 = 1.4013e-45;
          local_104 = fVar23;
        }
        if (local_104 == fVar12) {
          return local_100;
        }
        while( true ) {
          ((code *)BuildPath)();
          pfVar10 = (float *)((code *)GetPath)();
          iVar14 = 0;
          if (0 < (int)pfVar10 + -1) {
            iVar19 = 0;
            do {
              local_ac[0] = local_e8 + *(float *)(PUN(int,(float)local_fc) + iVar19);
              local_ac[1] = *(float *)(PUN(int,(float)local_fc) + 4 + iVar19) + local_e4[0];
              local_ac[2] = *(float *)(PUN(int,(float)local_fc) + 8 + iVar19) + local_e4[1];
              local_94[0] = *(float *)(PUN(int,(float)local_fc) + 0xc + iVar19) + local_e8;
              local_94[1] = *(float *)(PUN(int,(float)local_fc) + 0x10 + iVar19) + local_e4[0];
              local_94[2] = *(float *)(PUN(int,(float)local_fc) + 0x14 + iVar19) + local_e4[1];
              sputActor_GetOrientMatrix(param_2);
              pfVar16 = local_7c;
              pfVar21 = (float *)(_stkneg + 32);
              for (iVar15 = 6; iVar15 != 0; iVar15 = iVar15 + -1) {
                *pfVar21 = *pfVar16;
                pfVar16 = pfVar16 + 1;
                pfVar21 = pfVar21 + 1;
              }
              pfVar16 = local_88;
              iVar15 = ((code *)TestCollision)(local_ac,local_94);
              if (iVar15 != 0) {
                return 0;
              }
              iVar14 = iVar14 + 1;
              iVar19 = iVar19 + 0xc;
            } while (iVar14 < (int)pfVar10 + -1);
          }
          if (0 < (int)pfVar10) {
            local_100 = local_100 + (int)pfVar10;
            puVar8 = PUN(undefined4 *,(float)local_fc);
            pfVar21 = pfVar10;
            do {
              pfVar21 = (float *)((int)pfVar21 + -1);
              *PUN(undefined4 *,(float)local_f4) = *puVar8;
              *(undefined4 *)(PUN(int,(float)local_f4) + 4) = puVar8[1];
              *(undefined4 *)(PUN(int,(float)local_f4) + 8) = puVar8[2];
              local_f4 = PUN(float,(PUN(int,(float)local_f4) + 0xc));
              puVar8 = puVar8 + 3;
            } while (pfVar21 != (float *)0x0);
          }
          pfVar21 = &local_e8;
          local_f4 = PUN(float,(param_5 + local_100 * 3));
          fVar25 = 6.715863e-39;
          pfVar13 = sputActor_GetOrientMatrix(param_2);
          pfVar22 = local_7c;
          pfVar24 = (float *)(_stkneg + 28);
          for (iVar14 = 6; iVar14 != 0; iVar14 = iVar14 + -1) {
            *pfVar24 = *pfVar22;
            pfVar22 = pfVar22 + 1;
            pfVar24 = pfVar24 + 1;
          }
          iVar14 = Collision_PointInBox
                             ((float *)(PUN(int,(float)local_f4) + -0xc),&local_d0,local_88,PUN(float,pfVar16),
                              in_stack_fffffed0,bz0,bx1,6.715423e-39,fVar25,pfVar13,pfVar21);
          if (iVar14 != 0) break;
          uVar17 = PUN(int,(float)local_f8) + 4 + PUN(int,(float)local_104);
          uVar18 = (int)uVar17 >> 0x1f;
          local_104 = PUN(float,(((uVar17 ^ uVar18) - uVar18 & 3 ^ uVar18) - uVar18));
          if (local_104 == fVar12) {
            return local_100;
          }
        }
        iVar14 = ((code *)GetPath)();
        iVar19 = 0;
        local_f8 = 0.0;
        if (0 < iVar14 + -1) {
          do {
            local_94[0] = local_e8 + *(float *)((int)pfVar10 + iVar19);
            local_94[1] = *(float *)((int)pfVar10 + iVar19 + 4) + local_e4[0];
            local_94[2] = *(float *)((int)pfVar10 + iVar19 + 8) + local_e4[1];
            local_ac[0] = *(float *)((int)pfVar10 + iVar19 + 0xc) + local_e8;
            local_ac[1] = *(float *)((int)pfVar10 + iVar19 + 0x10) + local_e4[0];
            local_ac[2] = *(float *)((int)pfVar10 + iVar19 + 0x14) + local_e4[1];
            sputActor_GetOrientMatrix(param_2);
            pfVar16 = local_7c;
            pfVar21 = (float *)(_stkneg + 32);
            for (iVar15 = 6; iVar15 != 0; iVar15 = iVar15 + -1) {
              *pfVar21 = *pfVar16;
              pfVar16 = pfVar16 + 1;
              pfVar21 = pfVar21 + 1;
            }
            iVar15 = ((code *)TestCollision)(local_94,local_ac);
            if (iVar15 != 0) {
              return 0;
            }
            local_f8 = PUN(float,(PUN(int,(float)local_f8) + 1));
            iVar19 = iVar19 + 0xc;
          } while (PUN(int,(float)local_f8) < iVar14 + -1);
        }
        uVar17 = local_100;
        if (0 < iVar14) {
          uVar17 = local_100 + iVar14;
          pfVar16 = param_5 + local_100 * 3;
          do {
            iVar14 = iVar14 + -1;
            *pfVar16 = *pfVar10;
            pfVar16[1] = pfVar10[1];
            pfVar16[2] = pfVar10[2];
            pfVar16 = pfVar16 + 3;
            pfVar10 = pfVar10 + 3;
          } while (iVar14 != 0);
        }
        return uVar17;
      }
      uVar17 = local_f0 + 1;
      pfVar16 = pfVar16 + 3;
      pfVar10 = PUN(float *,(float)local_fc);
      local_f0 = uVar17;
    } while ((int)uVar17 < PUN(int,(float)local_f8));
  }
  pfVar10 = (float *)(param_3 + uVar17 * 3);
  param_5 = param_5 + local_100 * 3;
  *param_5 = *pfVar10;
  param_5[1] = pfVar10[1];
  param_5[2] = pfVar10[2];
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


/* ---- 0x00494880  sputActor_SetWalkSystemFadeTime ---- */
/* Lua SetWalkSystemFadeTime Original name sputActor_SetWalkSystemFadeTime (the remaster's
   GrimFandango (Linux): aligned call in sputLua_SetWalkSystemFadeTime); was Walker_SetFadeTime. */

void __cdecl sputActor_SetWalkSystemFadeTime(int ms)

{
  g_nWALKSYSTEM_FADE_TIME = ms;
  return;
}

/* ---- 0x004a8200  Puck_Construct ---- */
/* Allocates the 0x60-byte walker record Original name Puck_Construct (the remaster's GrimFandango
   (Linux): same body (position 0, rdMatrix_Build34, the radius at +0x3c, +0x48 = 1.0f, the rest
   cleared)); was Walker_Create. */

Puck * __thiscall Puck_Construct(Puck *this,float radius)

{
  this->aPos[0] = 0.0;
  this->aPos[1] = 0.0;
  this->aPos[2] = 0.0;
  rdMatrix_Build34(this->aFrame,this,this);
  this->aConstraint[1] = 1.0;
  this->flRadius = radius;
  this->pSector = (WalkPlane *)0x0;
  this->flStep = 0.0;
  this->nConstrained = 0;
  this->aConstraint[0] = 0.0;
  this->aConstraint[2] = 0.0;
  this->pNext = (Puck *)0x0;
  this->pPrev = (Puck *)0x0;
  this->pNext = g_dwPuck_p_head;
  if (g_dwPuck_p_head != (Puck *)0x0) {
    g_dwPuck_p_head->pPrev = this;
  }
  g_dwPuck_p_head = this;
  return this;
}

/* ---- 0x004a8270  Puck_Destruct ---- */
/* Original name Puck_Destruct (the remaster's GrimFandango (Linux): same body (unlink from p_head
   and the neighbours +0x54 / +0x58)); was Walker_Destroy. */

void __fastcall Puck_Destruct(Puck *puck)

{
  if (puck == g_dwPuck_p_head) {
    g_dwPuck_p_head = puck->pNext;
  }
  if (puck->pPrev != (Puck *)0x0) {
    puck->pPrev->pNext = puck->pNext;
  }
  if (puck->pNext != (Puck *)0x0) {
    puck->pNext->pPrev = puck->pPrev;
  }
  return;
}

/* ---- 0x004a82a0  Puck_Rot ---- */
/* Converts the walker's 3x3 frame to pitch/yaw/roll in g_vWalkerAngles Original name Puck_Rot (the
   remaster's GrimFandango (Linux): same body (rdMatrix_ExtractAngles34 of the orientation into the
   static Rot()::ret, returned)); was Walker_GetAngles. */

undefined * __fastcall Puck_Rot(Puck *puck)

{
  rdMatrix_ExtractAngles34(puck->aFrame,&g_aPuck_Rot_ret);
  return &g_aPuck_Rot_ret;
}

/* ---- 0x004a82c0  Puck_Validate ---- */
/* Called after Actor_PutInSet when the actor has a walker so it picks up the new set's sectors
   Original name Puck_Validate (the remaster's GrimFandango (Linux): Puck::Validate in the remaster
   (a C++ method there); the only unmatched callee of Actor_SetFollowBoxes; 4 matched neighbours
   agree, 1 disagree); was Walker_ReattachToSet. */

void __fastcall Puck_Validate(Puck *puck)

{
  WalkPlane *this;
  int iVar1;
  
  this = WalkPlane_PlaneClosest(puck->aPos,0x1000);
  puck->pSector = this;
  if (this != (WalkPlane *)0x0) {
    iVar1 = WalkPlane_Within(this,puck->aPos,1);
    if (iVar1 == 0) {
      WalkPlane_ClosestPoint(puck->pSector,(int)puck);
      Puck_SetPos(puck,puck->aPos);
    }
    Puck_OrientToPlane(puck,(int)puck->pSector);
  }
  return;
}

/* ---- 0x004a8310  Puck_SetPos ---- */
/* Original name Puck_SetPos (the remaster's GrimFandango (Linux): Puck::SetPos in the remaster (a
   C++ method there); the only unmatched callee of Actor_SetPositionClamped; 2 matched neighbours
   agree, 1 disagree); was Walker_SetPosition. */

void __thiscall Puck_SetPos(Puck *this,float *pos)

{
  this->aPos[0] = *pos;
  this->aPos[1] = pos[1];
  this->aPos[2] = pos[2];
  this->aFrame[9] = *pos;
  this->aFrame[10] = pos[1];
  this->aFrame[0xb] = pos[2];
  return;
}

/* ---- 0x004a8350  Puck_Xform ---- */
/* Original name Puck_Xform (the remaster's GrimFandango (Linux): same body
   (rdMatrix_TransformPoint34Acc of the vector by the orientation at +0xc)); was
   Walker_RotateVector. */

void __thiscall Puck_Xform(Puck *this,float *vec)

{
  rdMatrix_TransformPoint34Acc(vec,this->aFrame);
  return;
}

/* ---- 0x004a8370  Puck_InvXform ---- */
/* Rotates a world vector into the current walker's frame Original name Puck_InvXform (the
   remaster's GrimFandango (Linux): same body (subtract the position, rotate by the transposed
   orientation)); was Walker_ToLocalSpace. */

void __thiscall Puck_InvXform(Puck *this,float *vec)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  *vec = *vec - this->aPos[0];
  vec[1] = vec[1] - this->aPos[1];
  vec[2] = vec[2] - this->aPos[2];
  rdMatrix_TransformVectorOrtho34(&local_c,vec,this->aFrame);
  *vec = local_c;
  vec[1] = local_8;
  vec[2] = local_4;
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a83c0  Puck_Rotate ---- */
/* Original name Puck_Rotate (the remaster's GrimFandango (Linux): Puck::Rotate; aligned call in
   PointAt, sputActor_SetActorRotation); was Walker_TurnHeading. */

void __thiscall Puck_Rotate(Puck *this,float angle)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *vec;
  WalkPlane *this_00;
  #define local_30 (*(float (*)[12])(_frame + (0x40 - 0x30)))
  
  rdMatrix_BuildFromVectorAngle34(local_30,this->aFrame + 6,angle);
  vec = this->aFrame + 3;
  rdMatrix_TransformVector34Acc(vec,local_30);
  this_00 = this->pSector;
  *vec = *vec + this->aFrame[9];
  this->aFrame[4] = this->aFrame[10] + this->aFrame[4];
  this->aFrame[5] = this->aFrame[0xb] + this->aFrame[5];
  if (this_00 != (WalkPlane *)0x0) {
    WalkPlane_SnapTo(this_00,vec);
  }
  *vec = *vec - this->aFrame[9];
  this->aFrame[4] = this->aFrame[4] - this->aFrame[10];
  this->aFrame[5] = this->aFrame[5] - this->aFrame[0xb];
  Puck_Normalize(this);
  return;
}
#undef local_30


/* ---- 0x004a8450  Puck_PointAt ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name Puck_PointAt (the remaster's GrimFandango (Linux): Puck::PointAt in the remaster (a
   C++ method there); the only unmatched callee of Lua_PointActorAt; the only unmatched callee of
   Lua_TurnActorTo; 6 matched neighbours agree, 0 disagree); was Walker_TurnToPoint. */

float __thiscall Puck_PointAt(Puck *this,float *point,float maxTurn)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_c = *point;
  local_8 = point[1];
  local_4 = PUN(uint,(float)point[2]);
  if (this->pSector != (WalkPlane *)0x0) {
    WalkPlane_Project(this->pSector,(int)&local_c);
  }
  Puck_InvXform(this,&local_c);
  rdVector_Normalize3Acc(&local_c);
  fVar1 = stdMath_ArcSin3(local_8);
  point = PUN(float *,(float)(90.0 - fVar1));
  if (maxTurn < PUN(float,point)) {
    point = PUN(float *,(float)maxTurn);
  }
  if (0.0 < local_c) {
    point = PUN(float *,(float)(PUN(float,point) * -1.0));
  }
  Puck_Rotate(this,PUN(float,point));
  return PUN(float,point);
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a85b0  Puck_Constrain ---- */
/* Original name Puck_Constrain (the remaster's GrimFandango (Linux): Puck::Constrain in the
   remaster (a C++ method there); the only unmatched callee of Actor_SetConstrain; 1 matched
   neighbours agree, 0 disagree); was Walker_SetConstraint. */

void __thiscall Puck_Constrain(Puck *this,int a1)

{
  float *pfVar1;
  
  this->nConstrained = 0;
  if ((this->pSector != (WalkPlane *)0x0) && (a1 != 0)) {
    pfVar1 = WalkPlane_GetConstraintVector(this->pSector,this->aPos);
    if (pfVar1 != (float *)0x0) {
      this->aConstraint[0] = *pfVar1;
      this->aConstraint[1] = pfVar1[1];
      this->aConstraint[2] = pfVar1[2];
      this->aFrame[3] = *pfVar1;
      this->aFrame[4] = pfVar1[1];
      this->aFrame[5] = pfVar1[2];
      Puck_Normalize(this);
      this->nConstrained = 1;
    }
  }
  return;
}

/* ---- 0x004a8610  Puck_Forward ---- */
/* WARNING: Variable defined which should be unmapped: local_48 */
/* Walker_WalkSectors: the per-frame walk of an actor over the walk sectors (target-inside test with
   tolerance, exit point of the edge, neighbour lookup with the current sector deactivated, 0.02 cap
   into the new sector, reflection turn only when |angle| < reflect and not against a held turn
   key). See autorun/NAV_PLAN.md and COLLISION_FIX_PLAN.md. Original name Puck_Forward (the
   remaster's GrimFandango (Linux): same body (the recursion counter static, the step at +0x40, the
   plane slope by stdMath_ArcSin3 of the dot product, the plane walk)); was Walker_WalkSectors. */

undefined * __thiscall Puck_Forward(Puck *this,float step,int turnLeftOk,int turnRightOk)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  WalkPlane *this_00;
  WalkVertex *pWVar1;
  int iVar2;
  WalkPlane *pWVar3;
  undefined *puVar4;
  float fVar5;
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
  
  puVar4 = (undefined *)0x0;
  if (g_dwPuck_Forward_recursion_level == 0) {
    this->flStep = step;
  }
  g_dwPuck_Forward_recursion_level = g_dwPuck_Forward_recursion_level + 1;
  if (this->nConstrained != 0) {
    fVar5 = rdVector_Dot3(this->aFrame,this->aConstraint);
    fVar5 = stdMath_ArcSin3(fVar5);
    local_48 = (90.0 - fVar5) - 90.0;
    fVar5 = local_48;
    if (local_48 < 0.0) {
      fVar5 = -local_48;
    }
    if (this->flRadius < fVar5) {
      return (undefined *)0x0;
    }
    fVar5 = rdVector_Dot3(this->aFrame + 3,this->aConstraint);
    if (fVar5 <= 0.0) {
      local_48 = -local_48;
    }
    Puck_Rotate(this,local_48);
  }
  local_30 = 0.0;
  local_2c = PUN(uint,(float)step);
  local_28 = 0;
  Puck_Xform(this,&local_30);
  if ((this->pSector == (WalkPlane *)0x0) ||
     (iVar2 = WalkPlane_Within(this->pSector,&local_30,1), iVar2 != 0)) {
    local_48 = PUN(float,&local_30);
    Puck_SetPos(this,PUN(float *,(float)local_48));
    g_dwPuck_Forward_recursion_level = 0;
    return (undefined *)0x1;
  }
  if (8 < (int)g_dwPuck_Forward_recursion_level) {
    g_dwPuck_Forward_recursion_level = 0;
    return (undefined *)0x0;
  }
  this_00 = this->pSector;
  local_34 = WalkPlane_Intersection(this_00,(int)this,(int)&local_30,(int)&local_24);
  this->pSector->nActive = 0;
  local_18 = local_24;
  local_14 = local_20;
  local_10 = local_1c;
  Puck_InvXform(this,&local_18);
  step = step - local_14;
  pWVar3 = WalkPlane_PlaneAt(&local_24,0x1000);
  if (pWVar3 == (WalkPlane *)0x0) {
    Puck_SetPos(this,&local_24);
    pWVar3 = this->pSector;
    if ((pWVar3->dwType & 0x100) == 0) {
      fVar5 = local_34;
      if (local_34 < 0.0) {
        fVar5 = -local_34;
      }
      if ((this->flRadius <= fVar5) || (this->nConstrained != 0)) {
        this->flStep = this->flStep - step;
      }
      else if (((0.0 < local_34) && (turnLeftOk != 0)) || ((local_34 < 0.0 && (turnRightOk != 0))))
      {
        Puck_Rotate(this,local_34);
        this_00->nActive = 1;
        puVar4 = Puck_Forward(this,step,1,1);
      }
      if (this->nConstrained != 0) {
        Puck_Rotate(this,local_34);
        this->nConstrained = 1;
        this->aConstraint[0] = this->aFrame[3];
        this->aConstraint[1] = this->aFrame[4];
        this->aConstraint[2] = this->aFrame[5];
      }
      this_00->nActive = 1;
      return puVar4;
    }
    if ((pWVar3->nLongEdge + 1) % pWVar3->nNumVerts != pWVar3->nHitEdge) {
      pWVar1 = pWVar3->aVerts[pWVar3->nLongEdge];
      local_c = pWVar1->aPos[0];
      local_8 = PUN(uint,(float)pWVar1->aPos[1]);
      local_4 = PUN(uint,(float)pWVar1->aPos[2]);
      Puck_InvXform(this,&local_c);
      if (local_c <= 0.0) {
        if (local_34 < 3.0) {
          local_34 = (local_34 - -90.0) - -90.2;
        }
      }
      else if (3.0 < local_34) {
        local_34 = -90.2 - (90.0 - local_34);
      }
      Puck_Rotate(this,local_34);
      puVar4 = Puck_Forward(this,step,1,1);
      this_00->nActive = 1;
      return puVar4;
    }
    return (undefined *)0x0;
  }
  Puck_SetPos(this,&local_24);
  this->pSector = pWVar3;
  Puck_OrientToPlane(this,(int)pWVar3);
  if (0.02 <= step) {
    step = 0.02;
  }
  puVar4 = Puck_Forward(this,step,1,1);
  this_00->nActive = 1;
  return puVar4;
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


/* ---- 0x004a89b0  Puck_OrientToPlane ---- */
/* Original name Puck_OrientToPlane (the remaster's GrimFandango (Linux): same body (the up vector
   from the plane normal +0x60, then the right / forward vectors by cross products)); was
   Walker_SetSectorFrame. */

void __thiscall Puck_OrientToPlane(Puck *this,int a1)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  
  pfVar1 = this->aFrame + 6;
  fVar4 = this->aFrame[5];
  pfVar2 = this->aFrame + 3;
  pfVar3 = this->aFrame;
  *pfVar1 = *(float *)(a1 + 0x60);
  this->aFrame[7] = *(float *)(a1 + 100);
  this->aFrame[8] = *(float *)(a1 + 0x68);
  fVar5 = *pfVar1;
  *pfVar3 = this->aFrame[8] * this->aFrame[4] - this->aFrame[7] * this->aFrame[5];
  this->aFrame[1] = fVar4 * fVar5 - this->aFrame[8] * this->aFrame[3];
  this->aFrame[2] = this->aFrame[7] * *pfVar2 - *pfVar1 * this->aFrame[4];
  rdVector_Normalize3Acc(pfVar3);
  *pfVar2 = this->aFrame[7] * this->aFrame[2] - this->aFrame[8] * this->aFrame[1];
  this->aFrame[4] = *pfVar3 * this->aFrame[8] - *pfVar1 * this->aFrame[2];
  this->aFrame[5] = this->aFrame[1] * *pfVar1 - this->aFrame[7] * *pfVar3;
  rdVector_Normalize3Acc(pfVar2);
  return;
}

/* ---- 0x004a8a90  Puck_Normalize ---- */
/* Original name Puck_Normalize (the remaster's GrimFandango (Linux): same body (normalise the
   forward vector, the right vector as its cross product with up, normalised)); was
   Walker_RebuildRightVector. */

void __fastcall Puck_Normalize(Puck *puck)

{
  float *pfVar1;
  float fVar2;
  
  pfVar1 = puck->aFrame + 3;
  rdVector_Normalize3Acc(pfVar1);
  fVar2 = puck->aFrame[8];
  puck->aFrame[0] = puck->aFrame[4] * puck->aFrame[8] - puck->aFrame[7] * puck->aFrame[5];
  puck->aFrame[1] = puck->aFrame[5] * puck->aFrame[6] - *pfVar1 * fVar2;
  puck->aFrame[2] = *pfVar1 * puck->aFrame[7] - puck->aFrame[4] * puck->aFrame[6];
  rdVector_Normalize3Acc(puck->aFrame);
  return;
}

/* ---- 0x004a8b00  Puck_Draw ---- */
/* Original name Puck_Draw (the remaster's GrimFandango (Linux): same body (three short axis lines
   (0.1 / 0.05) transformed by the orientation, rdPrimit3_DrawLine in the colour)); was
   Walker_DrawDebugAxes. */

void __thiscall Puck_Draw(Puck *this,int color)

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
  Puck_Xform(this,&local_c);
  Puck_Xform(this,&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,color,0xffffffff
                    );
  local_c = 0.05;
  local_8 = 0x3d4ccccd;
  local_4 = 0;
  local_18 = 0.0;
  local_14 = 0x3dcccccd;
  local_10 = 0;
  Puck_Xform(this,&local_c);
  Puck_Xform(this,&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,color,0xffffffff
                    );
  local_c = -0.05;
  local_8 = 0x3d4ccccd;
  local_4 = 0;
  local_18 = 0.0;
  local_14 = 0x3dcccccd;
  local_10 = 0;
  Puck_Xform(this,&local_c);
  Puck_Xform(this,&local_18);
  rdPrimit3_DrawLine(&local_c,&local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,color,0xffffffff
                    );
  local_c = 0.0;
  local_8 = 0;
  local_4 = 0x3d4ccccd;
  local_18 = 0.0;
  local_14 = 0;
  local_10 = 0;
  Puck_Xform(this,&local_c);
  Puck_Xform(this,&local_18);
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


/* ---- 0x004a9420  GetPath ---- */
/* Original name GetPath (the remaster's GrimFandango (Linux): aligned call in
   sputActor_ActorWalkTo); was Planner_GetPath. */

uint GetPath(undefined4 *param_1)

{
  *param_1 = &g_dwWorkingPath;
  return g_dwTotWorkingPathPoints;
}

/* ---- 0x004a9430  BuildPath ---- */
/* Original name BuildPath (the remaster's GrimFandango (Linux): the walk path planner of
   sputActor_ActorWalkTo in both builds; the remaster's first tries its new PathFinder, its fallback
   is this body (all planes active, find the start and end planes, FindPath, append the end point,
   TightenPath)); was Planner_PlanPath. */

undefined4 BuildPath(float *param_1,float *param_2,int param_3)

{
  uint uVar1;
  WalkPlane *pWVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  WalkPlane_AllActive();
  g_dwTotWorkingPathPoints = 0;
  pWVar2 = WalkPlane_PlaneAt(param_1,0x1000);
  if (pWVar2 == (WalkPlane *)0x0) {
    return 0;
  }
  pWVar2 = WalkPlane_PlaneAt(param_2,0x1000);
  if (pWVar2 == (WalkPlane *)0x0) {
    return 0;
  }
  iVar3 = Planner_FindPath(param_1,param_2,(WalkPlane *)0x0);
  uVar1 = g_dwTotWorkingPathPoints;
  if (iVar3 != 0) {
    iVar3 = g_dwTotWorkingPathPoints * 3;
    g_dwTotWorkingPathPoints = g_dwTotWorkingPathPoints + 1;
    (&g_dwWorkingPath)[iVar3] = PUN(uint,(float)*param_2);
    (&UINT_008cf0b4)[uVar1 * 3] = PUN(uint,(float)param_2[1]);
    (&UINT_008cf0b8)[uVar1 * 3] = PUN(uint,(float)param_2[2]);
    if (param_3 != 0) {
      TightenPath();
    }
    uVar4 = 1;
  }
  WalkPlane_AllActive();
  return uVar4;
}

/* ---- 0x004a94d0  Planner_FindPath ---- */
/* Original name Planner_FindPath (the remaster's GrimFandango (Linux): the recursive plane search
   in both builds (Within, WalkPlane::Intersection, the exit points, recursion into the next plane);
   FindPath is a static two remaster files have, so it keeps the module prefix); was
   Planner_SearchSectors. */

undefined4 __cdecl Planner_FindPath(float *param_1,float *param_2,WalkPlane *plane)

{
  unsigned char _frame[0x210] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  WalkPlane *planeB;
  float *point;
  #define local_1fc (*(uint *)(_frame + (0x210 - 0x1fc)))
  #define local_1f8 (*(uint *)(_frame + (0x210 - 0x1f8)))
  #define local_1f4 (*(float *)(_frame + (0x210 - 0x1f4)))
  #define local_1f0 (*(float *)(_frame + (0x210 - 0x1f0)))
  #define local_1ec (*(float *)(_frame + (0x210 - 0x1ec)))
  #define local_1e8 (*(uint *)(_frame + (0x210 - 0x1e8)))
  #define local_1e4 (*(uint *)(_frame + (0x210 - 0x1e4)))
  #define local_1e0 (*(float (*)[120])(_frame + (0x210 - 0x1e0)))
  
  if (0x1d < (int)(g_dwTotWorkingPathPoints + 1)) {
    plane->nActive = 0;
    return 1;
  }
  if (plane == (WalkPlane *)0x0) {
    plane = WalkPlane_PlaneAt(param_1,0x1000);
  }
  uVar1 = g_dwTotWorkingPathPoints;
  if (plane != (WalkPlane *)0x0) {
    iVar2 = g_dwTotWorkingPathPoints * 3;
    g_dwTotWorkingPathPoints = g_dwTotWorkingPathPoints + 1;
    (&g_dwWorkingPath)[iVar2] = PUN(uint,(float)*param_1);
    (&UINT_008cf0b4)[uVar1 * 3] = PUN(uint,(float)param_1[1]);
    (&UINT_008cf0b8)[uVar1 * 3] = PUN(uint,(float)param_1[2]);
    iVar2 = WalkPlane_Within(plane,param_2,1);
    if (iVar2 != 0) {
      return 1;
    }
    local_1e8 = g_dwTotWorkingPathPoints;
    WalkPlane_Intersection(plane,(int)param_1,(int)param_2,(int)&local_1f4);
    plane->nActive = 0;
    if ((local_1f4 - *param_1) * (local_1f4 - *param_1) +
        (local_1ec - param_1[2]) * (local_1ec - param_1[2]) +
        (local_1f0 - param_1[1]) * (local_1f0 - param_1[1]) <= 0.0001) {
      local_1f8 = 0;
    }
    else {
      local_1f8 = (uint)WalkPlane_PlaneAt(&local_1f4,0x1000);
    }
    if (local_1f8 != 0) {
      iVar2 = Planner_FindPath(&local_1f4,param_2,(WalkPlane *)local_1f8);
      if (iVar2 != 0) {
        return 1;
      }
      if (local_1f8 != 0) {
        *(undefined4 *)(local_1f8 + 0x2c) = 0;
      }
    }
    local_1e4 = FindExitPoints(plane,param_2,(uint *)local_1e0);
    local_1fc = 0;
    if (0 < (int)local_1e4) {
      point = local_1e0;
      do {
        planeB = WalkPlane_PlaneAt(point,0x1000);
        if (planeB != (WalkPlane *)0x0) {
          g_dwTotWorkingPathPoints = local_1e8;
          iVar2 = Planner_PortalPoint(plane,planeB,param_2,&local_1f4);
          if ((iVar2 != 0) && (iVar2 = Planner_FindPath(&local_1f4,param_2,planeB), iVar2 != 0)) {
            return 1;
          }
        }
        local_1fc = local_1fc + 1;
        point = point + 4;
      } while ((int)local_1fc < (int)local_1e4);
    }
    plane->nActive = 1;
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


/* ---- 0x004a96f0  FindExitPoints ---- */
/* Original name FindExitPoints (the remaster's GrimFandango (Linux): same body (for every other
   active walkable plane the vertices inside the current plane, without duplicates); called by
   FindPath in both builds); was Planner_CollectSharedCorners. */

uint __cdecl FindExitPoints(WalkPlane *plane,float *param_2,uint *param_3)

{
  unsigned char _frame[0x200] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  WalkVertex *pWVar4;
  WalkPlane *pWVar5;
  int iVar6;
  uint uVar7;
  uint *puVar8;
  uint *puVar9;
  WalkVertex **ppWVar10;
  uint uVar11;
  float *pfVar12;
  bool bVar13;
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
  
  uVar11 = 0;
  local_1e8 = 0;
  for (pWVar5 = g_pWalkPlane_wp_head; pWVar5 != (WalkPlane *)0x0; pWVar5 = pWVar5->pNext) {
    if ((((pWVar5 != plane) && (pWVar5->nActive != 0)) && ((pWVar5->dwType & 0x1000) != 0)) &&
       (local_1ec = 0, 0 < pWVar5->nNumVerts)) {
      ppWVar10 = pWVar5->aVerts;
      do {
        iVar6 = WalkPlane_Within(plane,(*ppWVar10)->aPos,0);
        if (iVar6 != 0) {
          uVar7 = 0;
          if (0 < (int)uVar11) {
            puVar8 = &local_1e0;
            do {
              iVar6 = 0xc;
              bVar13 = true;
              puVar9 = puVar8;
              pfVar12 = (*ppWVar10)->aPos;
              do {
                if (iVar6 == 0) break;
                iVar6 = iVar6 + -1;
                bVar13 = (char)*puVar9 == *(char *)pfVar12;
                puVar9 = (uint *)((int)puVar9 + 1);
                pfVar12 = (float *)((int)pfVar12 + 1);
              } while (bVar13);
              uVar11 = local_1e8;
              if (bVar13) break;
              uVar7 = uVar7 + 1;
              puVar8 = puVar8 + 4;
            } while ((int)uVar7 < (int)local_1e8);
          }
          if (uVar7 == uVar11) {
            pWVar4 = *ppWVar10;
            fVar1 = *param_2;
            fVar2 = param_2[1];
            uVar11 = uVar11 + 1;
            fVar3 = param_2[2];
            (&local_1e0)[uVar7 * 4] = PUN(uint,(float)pWVar4->aPos[0]);
            (&local_1dc)[uVar7 * 4] = PUN(uint,(float)pWVar4->aPos[1]);
            (&local_1d8)[uVar7 * 4] = PUN(uint,(float)pWVar4->aPos[2]);
            fVar1 = fVar1 - PUN(float,(&local_1e0)[uVar7 * 4]);
            (&local_1d4)[uVar7 * 4] =
                 PUN(uint,(float)((fVar3 - PUN(float,(&local_1d8)[uVar7 * 4])) *
                        (fVar3 - PUN(float,(&local_1d8)[uVar7 * 4])) +
                       (fVar2 - PUN(float,(&local_1dc)[uVar7 * 4])) *
                       (fVar2 - PUN(float,(&local_1dc)[uVar7 * 4])) + fVar1 * fVar1));
            local_1e8 = uVar11;
          }
        }
        local_1ec = local_1ec + 1;
        ppWVar10 = ppWVar10 + 1;
      } while ((int)local_1ec < pWVar5->nNumVerts);
    }
  }
  iVar6 = 1;
  *param_3 = local_1e0;
  param_3[1] = local_1dc;
  param_3[2] = local_1d8;
  param_3[3] = local_1d4;
  if (1 < (int)uVar11) {
    puVar8 = &local_1d0;
    do {
      fVar1 = PUN(float,puVar8[3]);
      uVar7 = iVar6 - 1;
      if (-1 < (int)uVar7) {
        puVar9 = param_3 + iVar6 * 4;
        do {
          if (PUN(float,puVar9[-1]) <= fVar1) break;
          uVar7 = uVar7 - 1;
          *puVar9 = puVar9[-4];
          puVar9[1] = puVar9[-3];
          puVar9[2] = puVar9[-2];
          puVar9[3] = puVar9[-1];
          puVar9 = puVar9 + -4;
        } while (uVar7 < 0x80000000);
      }
      puVar9 = param_3 + (uVar7 + 1) * 4;
      iVar6 = iVar6 + 1;
      *puVar9 = *puVar8;
      puVar9[1] = puVar8[1];
      uVar7 = puVar8[3];
      puVar9[2] = puVar8[2];
      puVar9[3] = uVar7;
      puVar8 = puVar8 + 4;
    } while (iVar6 < (int)uVar11);
  }
  return uVar11;
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
undefined4 __cdecl Planner_PortalPoint(WalkPlane *planeA,WalkPlane *planeB,float *point,float *out)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  WalkVertex *pWVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  WalkVertex **ppWVar7;
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  iVar6 = 0;
  local_4 = 3.4028235e+38;
  if (0 < planeA->nNumVerts) {
    ppWVar7 = planeA->aVerts;
    do {
      iVar5 = WalkPlane_Within(planeB,(*ppWVar7)->aPos,0);
      if (iVar5 != 0) {
        pWVar1 = *ppWVar7;
        fVar4 = pWVar1->aPos[1] - point[1];
        fVar2 = pWVar1->aPos[2] - point[2];
        fVar3 = pWVar1->aPos[0] - *point;
        fVar2 = fVar3 * fVar3 + fVar2 * fVar2 + fVar4 * fVar4;
        if (fVar2 < local_4) {
          *out = pWVar1->aPos[0];
          out[1] = pWVar1->aPos[1];
          out[2] = pWVar1->aPos[2];
          local_4 = fVar2;
        }
      }
      iVar6 = iVar6 + 1;
      ppWVar7 = ppWVar7 + 1;
    } while (iVar6 < planeA->nNumVerts);
  }
  iVar6 = 0;
  if (0 < planeB->nNumVerts) {
    ppWVar7 = planeB->aVerts;
    do {
      iVar5 = WalkPlane_Within(planeA,(*ppWVar7)->aPos,0);
      if (iVar5 != 0) {
        pWVar1 = *ppWVar7;
        fVar4 = pWVar1->aPos[1] - point[1];
        fVar2 = pWVar1->aPos[2] - point[2];
        fVar3 = pWVar1->aPos[0] - *point;
        fVar2 = fVar3 * fVar3 + fVar2 * fVar2 + fVar4 * fVar4;
        if (fVar2 < local_4) {
          *out = pWVar1->aPos[0];
          out[1] = pWVar1->aPos[1];
          out[2] = pWVar1->aPos[2];
          local_4 = fVar2;
        }
      }
      iVar6 = iVar6 + 1;
      ppWVar7 = ppWVar7 + 1;
    } while (iVar6 < planeB->nNumVerts);
  }
  if (local_4 == 3.4028235e+38) {
    return 0;
  }
  return 1;
}
#undef local_4


/* ---- 0x004a9aa0  TightenPath ---- */
/* Original name TightenPath (the remaster's GrimFandango (Linux): same body (for more than 3
   working-path points drop the middle point where the direct segment stays on the planes); called
   by BuildPath in both builds); was Planner_SmoothPath. */

undefined4 TightenPath(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *from;
  bool bVar1;
  bool bVar2;
  WalkPlane *pWVar3;
  WalkPlane *pWVar4;
  float *pfVar5;
  int iVar6;
  uint *puVar7;
  uint uVar8;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  bVar2 = false;
  local_10 = 0;
  if (g_dwTotWorkingPathPoints != 3 && -1 < (int)(g_dwTotWorkingPathPoints - 3)) {
    puVar7 = &UINT_008cf0c8;
    do {
      pfVar5 = (float *)(puVar7 + -3);
      from = (float *)(puVar7 + -6);
      pWVar3 = Planner_SharedSector(from,pfVar5);
      pWVar4 = Planner_SharedSector(pfVar5,(float *)puVar7);
      if (pWVar3 == (WalkPlane *)0x0) {
        return 1;
      }
      if (pWVar4 == (WalkPlane *)0x0) {
        return 1;
      }
      WalkPlane_Intersection(pWVar3,(int)from,(int)puVar7,(int)&local_c);
      pWVar3 = Planner_SharedSector(&local_c,from);
      pWVar4 = Planner_SharedSector(&local_c,(float *)puVar7);
      if (((pWVar4 != (WalkPlane *)0x0) && (pWVar3 != (WalkPlane *)0x0)) &&
         (0.0025000002 <
          (local_4 - PUN(float,puVar7[-1])) * (local_4 - PUN(float,puVar7[-1])) +
          (local_8 - PUN(float,puVar7[-2])) * (local_8 - PUN(float,puVar7[-2])) +
          (local_c - *pfVar5) * (local_c - *pfVar5))) {
        *pfVar5 = local_c;
        puVar7[-2] = PUN(uint,(float)local_8);
        puVar7[-1] = PUN(uint,(float)local_4);
        bVar2 = true;
      }
      local_10 = local_10 + 1;
      puVar7 = puVar7 + 3;
    } while ((int)local_10 < (int)(g_dwTotWorkingPathPoints - 3));
  }
  if (g_dwTotWorkingPathPoints != 2 && -1 < (int)(g_dwTotWorkingPathPoints - 2)) {
    puVar7 = &UINT_008cf0b4;
    local_14 = 1;
    uVar8 = g_dwTotWorkingPathPoints;
    do {
      if (((PUN(float,puVar7[1]) - PUN(float,puVar7[4])) * (PUN(float,puVar7[1]) - PUN(float,puVar7[4])) +
           (PUN(float,*puVar7) - PUN(float,puVar7[3])) * (PUN(float,*puVar7) - PUN(float,puVar7[3])) +
           (PUN(float,puVar7[-1]) - PUN(float,puVar7[2])) * (PUN(float,puVar7[-1]) - PUN(float,puVar7[2])) < 0.0001)
         && (pWVar3 = Planner_SharedSector((float *)(puVar7 + -1),(float *)(puVar7 + 2)),
            uVar8 = g_dwTotWorkingPathPoints, pWVar3 != (WalkPlane *)0x0)) {
        bVar2 = true;
        uVar8 = g_dwTotWorkingPathPoints - 1;
        g_dwTotWorkingPathPoints = uVar8;
        if ((int)local_14 < (int)uVar8) {
          iVar6 = uVar8 - local_14;
          pfVar5 = (float *)(puVar7 + 2);
          do {
            iVar6 = iVar6 + -1;
            *pfVar5 = pfVar5[3];
            pfVar5[1] = pfVar5[4];
            pfVar5[2] = pfVar5[5];
            pfVar5 = pfVar5 + 3;
          } while (iVar6 != 0);
        }
      }
      puVar7 = puVar7 + 3;
      bVar1 = (int)local_14 < (int)(uVar8 - 2);
      local_14 = local_14 + 1;
    } while (bVar1);
  }
  if (bVar2) {
    TightenPath();
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
WalkPlane * __cdecl Planner_SharedSector(float *from,float *to)

{
  WalkPlane *this;
  int iVar1;
  
  this = WalkPlane_PlaneAt(from,0x1000);
  while ((this != (WalkPlane *)0x0 && (iVar1 = WalkPlane_Within(this,to,1), iVar1 == 0)))
  {
    this->nActive = 0;
    this = WalkPlane_PlaneAt(from,0x1000);
  }
  WalkPlane_AllActive();
  return this;
}
