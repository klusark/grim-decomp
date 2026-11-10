/* GRIMFANDANGO.EXE :: actor.c
 * functions 0x00485290 .. 0x004a8500 (57 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00485290  Actor_ComputeScreenBox ---- */
/* Projects the actor's model through its frame and stores the covering screen rectangle at
   actor+0x6c (valid flag at +0x68) */

void __cdecl Actor_ComputeScreenBox(void *actor)

{
  int iVar1;
  float *frame;
  int iVar2;
  
  g_nDrawBoxMinX = UINT_009055ec;
  g_nDrawBoxMinY = *(int *)(UINT_008c97a0 + 0x10);
  g_nDrawBoxMaxX = 0;
  g_nDrawBoxMaxY = 0;
  *(undefined4 *)((int)actor + 0x6c) = 0;
  *(undefined4 *)((int)actor + 0x70) = 0;
  *(undefined4 *)((int)actor + 0x74) = 0;
  *(undefined4 *)((int)actor + 0x78) = 0;
  frame = Actor_GetFrame(actor);
  iVar2 = rdThing_DrawAlt(*(void **)(*(int *)((int)actor + 0xa0) + 4),frame);
  if (iVar2 != 0) {
    *(undefined4 *)((int)actor + 0x68) = 1;
    iVar2 = g_nDrawBoxMinX;
    *(int *)((int)actor + 0x6c) = g_nDrawBoxMinX;
    iVar1 = g_nDrawBoxMinY;
    *(int *)((int)actor + 0x70) = g_nDrawBoxMinY;
    *(int *)((int)actor + 0x74) = g_nDrawBoxMaxX - iVar2;
    *(int *)((int)actor + 0x78) = g_nDrawBoxMaxY - iVar1;
  }
  return;
}

/* ---- 0x00485320  Actor_DrawDebugWalker ---- */
/* WARNING: Variable defined which should be unmapped: local_28 */
/* Debug overlay: the walker's path segments, its sector outline and the look-at circle */

void Actor_DrawDebugWalker(void *param_1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *this;
  int iVar1;
  float *b;
  int iVar2;
  int iVar3;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  if (*(int *)((int)param_1 + 0xa4) != 0) {
    this = *(void **)(*(int *)((int)param_1 + 0xa4) + 0x1b4);
    if (this != (void *)0x0) {
      Walker_DrawDebugAxes(this,UINT_008c97e0 & 0xffff);
    }
    if ((*(byte *)((int)param_1 + 8) & 1) != 0) {
      iVar1 = *(int *)((int)param_1 + 0xa4);
      iVar3 = 0;
      if (*(int *)(iVar1 + 0x44) != 1 && -1 < *(int *)(iVar1 + 0x44) + -1) {
        iVar2 = 0x48;
        do {
          rdPrimit3_DrawLine((float *)(iVar2 + iVar1),(float *)(iVar2 + 0xc + iVar1),(int *)0x0,
                             (int *)0x0,(int *)0x0,(int *)0x0,UINT_008c97d4 & 0xffff,0xffffffff);
          iVar1 = *(int *)((int)param_1 + 0xa4);
          iVar3 = iVar3 + 1;
          iVar2 = iVar2 + 0xc;
        } while (iVar3 < *(int *)(iVar1 + 0x44) + -1);
      }
    }
    if (*(int *)(*(int *)((int)param_1 + 0xa4) + 0x3f8) != 0) {
      iVar1 = *(int *)(*(int *)(*(int *)((int)param_1 + 0xa0) + 4) + 4);
      b = Actor_GetFrame(param_1);
      Matrix34_TransformPoint(local_c,(float *)(iVar1 + 0x78),b);
      rdPrimit3_DrawPoint(local_c,*(float *)(iVar1 + 0x5c) *
                                  *(float *)(*(int *)((int)param_1 + 0xa4) + 0x3f4),0x41200000,
                          0xffff,0xffffffff);
    }
  }
  return;
}
#undef local_28
#undef local_c


/* ---- 0x0048b2e0  Actor_CreateSubtitle ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Creates the speech text object above the actor (projected head position when on screen), clamped
   to the screen edges */

void * __cdecl Actor_CreateSubtitle(void *actor,char *text,int x,int y)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  float *pfVar2;
  char *pcVar3;
  void *pvVar4;
  int iVar5;
  int unaff_ESI;
  uint *puVar6;
  int unaff_EDI;
  uint *puVar7;
  #define local_5c (*(float (*)[2])(_frame + (0x70 - 0x5c)))
  #define local_50 (*(float (*)[3])(_frame + (0x70 - 0x50)))
  #define local_44 (*(uint *)(_frame + (0x70 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x70 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x70 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x70 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x70 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x70 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x70 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x70 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x70 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x70 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x70 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x70 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x70 - 0x14)))
  
  pvVar1 = actor;
  local_38 = UINT_008a94bc;
  local_50[0] = PUN(float,g_nSubtitleDefaultX);
  local_50[2] = (float)UINT_004e8490;
  local_34 = UINT_008a94c0;
  puVar6 = &g_SubtitleTextCtx;
  puVar7 = &local_30;
  for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
  }
  local_50[1] = PUN(float,g_nSubtitleDefaultY);
  local_2c = (uint)&local_40;
  local_40 = 0;
  local_3c = 0;
  local_1c = *(uint *)(*(int *)((int)actor + 0xa4) + 0x418);
  local_18 = 0;
  local_14 = 0;
  if ((*(int *)((int)actor + 0x68) == 0) || (g_dwGrimlib_mode == 3)) {
    pfVar2 = local_50;
    if ((*(int *)((int)actor + 0xa0) == 0) || ((*(byte *)((int)actor + 4) & 2) != 0)) {
      pcVar3 = Set_GetCurrentName();
      iVar5 = _stricmp((int)actor + 0x7c,pcVar3);
      if (iVar5 == 0) {
        iVar5 = rdPrimit3_GetScreenCoord((float *)((int)actor + 0xc),local_5c);
        if (iVar5 != 0) {
          local_50[0] = local_5c[0];
          local_50[1] = local_5c[1];
        }
      }
    }
  }
  else {
    pfVar2 = (void *)((int)actor + 0x6c);
  }
  actor = pfVar2;
  iVar5 = Text_MeasureWidth(&local_30,text);
  iVar5 = iVar5 / 2;
  if (x == -1) {
    x = *(int *)((int)actor + 8) / 2 + *(int *)actor;
  }
  if (x - iVar5 < 0x28) {
    x = iVar5 + 0x28;
  }
  if ((int)(UINT_008a94bc - 0x28) < iVar5 + x) {
    x = (UINT_008a94bc - iVar5) - 0x28;
  }
  local_20 = *(uint *)(*(int *)local_28 + 8);
  local_24 = x;
  iVar5 = Text_MeasureHeight(&local_30,text);
  if (y == -1) {
    y = *(int *)((int)actor + 4) - iVar5;
  }
  if (y < 10) {
    y = 10;
  }
  if ((int)(UINT_008a94c0 - 10) < y + iVar5) {
    y = (UINT_008a94c0 - iVar5) + -10;
  }
  local_20 = *(int *)(*(int *)local_28 + 8) + y;
  local_24 = x;
  pvVar4 = TextObject_New(&local_30,text,unaff_EDI,unaff_ESI);
  *(void **)((int)pvVar4 + 0x254) = pvVar1;
  *(uint *)((int)pvVar1 + 4) = *(uint *)((int)pvVar1 + 4) | 4;
  return pvVar4;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_44
#undef local_50
#undef local_5c

#endif


/* ---- 0x0048f930  sputActor_SetCostume ---- */
/* Lua SetActorCostume: replaces the whole costume stack with one costume Original name
   sputActor_SetCostume (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_SetActorCostume; 3 matched neighbours agree, 0 disagree); was Actor_SetCostume. */

int __cdecl sputActor_SetCostume(void *actor,char *name,int param_3)

{
  void *costumeRes;
  void *pvVar1;
  
  if ((name == (char *)0x0) || (param_3 != 0)) {
    costumeRes = (void *)0x0;
    pvVar1 = *(void **)((int)actor + 0xa0);
  }
  else {
    costumeRes = sputResource_Alloc(0x54534f43,name);
    if (costumeRes == (void *)0x0) {
      return 0;
    }
    param_3 = 0;
    pvVar1 = *(void **)((int)actor + 0xa0);
  }
  pvVar1 = Costume_ReplaceTop(pvVar1,costumeRes,param_3);
  *(void **)((int)actor + 0xa0) = pvVar1;
  Cos_InstSetUserData(**(int **)((int)actor + 0xa0),((int)actor - (int)g_pActors) / 0xa8);
  Actor_SetFrustumCull(actor,~*(uint *)((int)actor + 4) >> 2 & 1);
  return 1;
}

/* ---- 0x0048f9d0  Actor_SetHead ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua SetActorHead: head-tracking joints and limits */

void __cdecl
Actor_SetHead(void *actor,int joint1,int joint2,int joint3,float maxRoll,float maxPitch,float maxYaw
             )

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  float fVar3;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  iVar1 = *(int *)((int)actor + 0xa0);
  if ((iVar1 != 0) && (*(int *)(iVar1 + 4) != 0)) {
    uVar2 = *(uint *)(*(int *)(*(int *)(iVar1 + 4) + 4) + 0x54);
    if (((uint)joint1 <= uVar2) && (((uint)joint2 <= uVar2 && ((uint)joint3 <= uVar2)))) {
      *(int *)(iVar1 + 0xc) = joint1;
      *(int *)(iVar1 + 0x10) = joint2;
      *(float *)(iVar1 + 0x1c) = maxPitch;
      *(int *)(iVar1 + 0x14) = joint3;
      *(float *)(iVar1 + 0x20) = maxYaw;
      fVar3 = maxRoll;
      if (maxRoll < 0.0) {
        fVar3 = -maxRoll;
      }
      stdMath_SinCos(fVar3 * 0.5,&actor,iVar1 + 0x24);
    }
  }
  return;
}
#undef local_14


/* ---- 0x0048fa60  Actor_CanSeePoint ---- */
/* True when the point lies within the head joint's view cone (cosine threshold at costume+0x24 set
   by Actor_SetHead) */

int __cdecl Actor_CanSeePoint(void *actor,float *point,float *outDistance)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float *frame;
  float *pfVar3;
  float fVar4;
  uint index;
  #define local_48 (*(float (*)[3])(_frame + (0x60 - 0x48)))
  #define local_3c (*(float (*)[3])(_frame + (0x60 - 0x3c)))
  #define local_30 (*(float (*)[9])(_frame + (0x60 - 0x30)))
  #define local_c (*(float (*)[3])(_frame + (0x60 - 0xc)))
  
  iVar1 = *(int *)((int)actor + 0xa0);
  if (((iVar1 != 0) && (index = *(uint *)(iVar1 + 0xc), -1 < (int)index)) &&
     (*(int *)(iVar1 + 4) != 0)) {
    pfVar3 = local_30;
    frame = Actor_GetFrame(actor);
    rdPuppet_BuildJointMatrices(*(void **)(iVar1 + 4),frame,index,pfVar3);
    local_3c[0] = *point - local_c[0];
    local_3c[1] = point[1] - local_c[1];
    local_3c[2] = point[2] - local_c[2];
    fVar4 = rdVector_Normalize3Acc(local_3c);
    local_48[0] = local_3c[0];
    *outDistance = fVar4;
    local_48[1] = local_3c[1];
    local_48[2] = 0.0;
    rdVector_Normalize3Acc(local_48);
    pfVar3 = Actor_GetFrame(actor);
    fVar4 = pfVar3[3] * local_48[0];
    pfVar3 = Actor_GetFrame(actor);
    fVar2 = pfVar3[4] * local_48[1];
    pfVar3 = Actor_GetFrame(actor);
    if (*(float *)(iVar1 + 0x24) <= pfVar3[5] * local_48[2] + fVar2 + fVar4) {
      return 1;
    }
  }
  return 0;
}
#undef local_30
#undef local_3c
#undef local_48
#undef local_c


/* ---- 0x0048fb80  Actor_CanSee ---- */
/* Lua CanActorSee / GetVisibleThings line-of-sight test */

int __cdecl Actor_CanSee(void *viewer,void *target,float *outDistance)

{
  int iVar1;
  float *pfVar2;
  
  if (*(char *)((int)target + 0x7c) != '\0') {
    if (*(char *)((int)viewer + 0x7c) != '\0') {
      iVar1 = _stricmp((int)target + 0x7c,(int)viewer + 0x7c);
      if (iVar1 == 0) {
        pfVar2 = Actor_GetFrame(target);
        iVar1 = Actor_CanSeePoint(viewer,pfVar2 + 9,outDistance);
        return iVar1;
      }
    }
  }
  return 0;
}

/* ---- 0x0048fbd0  sputActor_Turn ---- */
/* Actor_TurnKey(actor, dir): the TurnActor builtin. Walker extra struct at actor+0xa4: +0x1c turn
   rate (deg/s, default 135, set by SetActorTurnRate), +0x41c time scale, +0x28 angle still to turn.
   Turn per press = rate * frameSeconds * timescale * dir; the key is accepted (+0x10 = +-1) only
   when |+0x28| <= 2 * that amount, i.e. the visible heading has caught up. Creates the walker
   (Actor_CreateWalker) if it does not exist. Original name sputActor_Turn (the remaster's
   GrimFandango (Linux): the only unmatched callee of Lua_TurnActor; 2 matched neighbours agree, 0
   disagree); was Actor_TurnKey. */

void sputActor_Turn(int param_1,float param_2)

{
  float fVar1;
  int iVar2;
  float fVar3;
  
  iVar2 = *(int *)(param_1 + 0xa4);
  fVar3 = sputTime_GetFrameTimeFlex();
  fVar3 = *(float *)(iVar2 + 0x1c) * fVar3 * *(float *)(iVar2 + 0x41c) * param_2;
  if (*(int *)(iVar2 + 0x1b4) == 0) {
    sputActor_EnablePuck(param_1,1);
  }
  iVar2 = *(int *)(param_1 + 0xa4);
  fVar1 = *(float *)(iVar2 + 0x28);
  if (*(float *)(iVar2 + 0x28) < 0.0) {
    fVar1 = -fVar1;
  }
  fVar3 = fVar3 + fVar3;
  if (fVar3 < 0.0) {
    fVar3 = -fVar3;
  }
  if (fVar1 <= fVar3) {
    if (0.0 < param_2) {
      *(undefined4 *)(iVar2 + 0x10) = 1;
      return;
    }
    *(undefined4 *)(iVar2 + 0x10) = 0xffffffff;
  }
  return;
}

/* ---- 0x0048fc80  sputActor_Forward ---- */
/* Actor_WalkForward(actor): creates the walker if missing and sets extra+0xc (walk forward this
   frame), consumed by Actor_UpdateWalker. Original name sputActor_Forward (the remaster's
   GrimFandango (Linux): the only unmatched callee of Lua_WalkActorForward; 3 matched neighbours
   agree, 0 disagree); was Actor_WalkForward. */

void sputActor_Forward(int param_1)

{
  sputTime_GetFrameTimeFlex();
  if (*(int *)(*(int *)(param_1 + 0xa4) + 0x1b4) == 0) {
    sputActor_EnablePuck(param_1,1);
  }
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0xc) = 1;
  return;
}

/* ---- 0x0048fd90  Actor_UpdateMovement ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Actor_UpdateMovement(actor, dt): per frame; path following when actor+8 bit 0 (Actor_FollowPath),
   Actor_UpdateWalker, Actor_UpdateMoveChores, costume update with dt * time scale, Actor_PuckOrient
   when actor+4 & 0x10. */

void Actor_UpdateMovement(void *param_1,float param_2)

{
  int iVar1;
  
  if (*(int *)((int)param_1 + 0xa4) != 0) {
    param_2 = *(float *)(*(int *)((int)param_1 + 0xa4) + 0x41c) * param_2;
  }
  iVar1 = *(int *)((int)param_1 + 0xa0);
  *(undefined4 *)((int)param_1 + 0x18) = *(undefined4 *)((int)param_1 + 0xc);
  *(undefined4 *)((int)param_1 + 0x1c) = *(undefined4 *)((int)param_1 + 0x10);
  *(undefined4 *)((int)param_1 + 0x20) = *(undefined4 *)((int)param_1 + 0x14);
  if ((iVar1 != 0) && (*(int *)(iVar1 + 0x7c) != 0)) {
    if (*(int *)(iVar1 + 0x7c) == 0) {
      (*g_pStd_HS->pAssertFail)
                (s_Bad_costume_Reference_004e9e90,s_main_sputResource_h_004e80a8,0xb8);
    }
    Cos_InstRescue(**(int **)((int)param_1 + 0xa0),*(int *)(iVar1 + 0x80));
  }
  if ((*(byte *)((int)param_1 + 8) & 1) != 0) {
    Actor_FollowPath(param_1);
  }
  if ((*(int *)((int)param_1 + 0xa4) != 0) && (*(int *)(*(int *)((int)param_1 + 0xa4) + 0x1b4) != 0)
     ) {
    Actor_UpdateWalker(param_1);
  }
  Actor_UpdateMoveChores(param_1);
  sputCostume_Update(*(void **)((int)param_1 + 0xa0),param_2);
  if ((*(byte *)((int)param_1 + 8) & 2) != 0) {
    Actor_UpdateLookAt(param_1,param_2);
  }
  if ((*(byte *)((int)param_1 + 4) & 0x10) != 0) {
    Actor_PuckOrient(param_1);
  }
  return;
}
#endif


/* ---- 0x0048fe80  Actor_UpdateLookAt ---- */
/* Head tracking: turns the three head joints toward the look-at point (extra+0) limited by the look
   rate and the yaw/pitch limits */

void __cdecl Actor_UpdateLookAt(void *actor,float dt)

{
  unsigned char _frame[0xe0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  float *pfVar6;
  float *pfVar7;
  int *piVar8;
  int iVar9;
  float fVar10;
  uint index;
  #define fStack_c8 (*(float *)(_frame + (0xe0 - 0xc8)))
  #define local_c4 (*(uint *)(_frame + (0xe0 - 0xc4)))
  #define local_c0 (*(float (*)[3])(_frame + (0xe0 - 0xc0)))
  #define fStack_b4 (*(float *)(_frame + (0xe0 - 0xb4)))
  #define fStack_b0 (*(float *)(_frame + (0xe0 - 0xb0)))
  #define afStack_a8 (*(float (*)[3])(_frame + (0xe0 - 0xa8)))
  #define afStack_9c (*(float (*)[3])(_frame + (0xe0 - 0x9c)))
  #define afStack_90 (*(float (*)[12])(_frame + (0xe0 - 0x90)))
  #define afStack_60 (*(float (*)[12])(_frame + (0xe0 - 0x60)))
  #define afStack_30 (*(float (*)[12])(_frame + (0xe0 - 0x30)))
  
  bVar5 = false;
  iVar1 = *(int *)((int)actor + 0xa0);
  if (*(int *)((int)actor + 0xa4) == 0) {
    (**(code **)(g_dwSputActHS + 0x18))
              (s_pActor__pExtra_004e9ea8,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x47a);
  }
  if (((iVar1 != 0) && (piVar8 = (int *)(iVar1 + 0xc), -1 < *(int *)(iVar1 + 0xc))) &&
     (*(int *)(iVar1 + 4) != 0)) {
    local_c0[0] = 0.0;
    local_c0[1] = 1.0;
    local_c0[2] = 0.0;
    if (*(int *)((int)actor + 0x68) == 0) {
      pfVar6 = Actor_GetFrame(actor);
      rdPuppet_UpdateFrame(*(void **)(iVar1 + 4),pfVar6);
    }
    index = *(uint *)(iVar1 + 0x14);
    pfVar6 = afStack_60;
    pfVar7 = Actor_GetFrame(actor);
    rdPuppet_BuildJointMatrices(*(void **)(iVar1 + 4),pfVar7,index,pfVar6);
    Matrix34_InvertRigid(afStack_90,afStack_60);
    pfVar6 = *(float **)((int)actor + 0xa4);
    if (((*pfVar6 == 0.0) && (pfVar6[1] == 0.0)) && (pfVar6[2] == 0.0)) {
      pfVar6 = afStack_90;
      bVar5 = true;
      pfVar7 = Actor_GetFrame(actor);
      Vec3_Copy(afStack_a8,pfVar7 + 3,pfVar6);
    }
    else {
      Matrix34_TransformPoint(afStack_a8,pfVar6,afStack_90);
      rdVector_Normalize3Acc(afStack_a8);
    }
    Vec3_Cross(afStack_9c,local_c0,afStack_a8);
    rdVector_Normalize3Acc(afStack_9c);
    fStack_c8 = *(float *)(iVar1 + 0x18) * dt;
    fVar10 = Vec3_Dot(local_c0,afStack_a8);
    fVar10 = Math_AsinDegrees(fVar10);
    fVar10 = 90.0 - fVar10;
    fVar3 = fVar10;
    if (fVar10 < 0.0) {
      fVar3 = -fVar10;
    }
    if (fVar3 < fStack_c8) {
      if (bVar5) {
        *(uint *)((int)actor + 8) = *(uint *)((int)actor + 8) & 0xfffffffd;
      }
      fStack_c8 = fVar10;
      if (fVar10 <= 0.0) {
        fStack_c8 = -fVar10;
      }
    }
    Matrix_AxisAngle(afStack_30,afStack_9c,fStack_c8);
    Vec3_Rotate3x3(local_c0,afStack_30);
    Matrix_GetAngles(local_c0,&fStack_b4);
    if ((*(byte *)((int)actor + 8) & 2) == 0) {
      iVar9 = 3;
      do {
        iVar9 = iVar9 + -1;
        *(undefined4 *)(*(int *)(*(int *)(iVar1 + 4) + 0x24) + 4 + *piVar8 * 0xc) = 0;
        *(undefined4 *)(*(int *)(*(int *)(iVar1 + 4) + 0x24) + *piVar8 * 0xc) = 0;
        *(undefined4 *)(*(int *)(*(int *)(iVar1 + 4) + 0x24) + 8 + *piVar8 * 0xc) = 0;
        piVar8 = piVar8 + 1;
      } while (iVar9 != 0);
      *(undefined4 *)(*(int *)(iVar1 + 4) + 0x1c) = 0;
      return;
    }
    iVar9 = 3;
    fVar3 = *(float *)(iVar1 + 0x20) * 0.33333334;
    fVar10 = *(float *)(iVar1 + 0x1c) * 0.33333334;
    do {
      iVar2 = *(int *)(*(int *)(iVar1 + 4) + 0x24);
      *(float *)(iVar2 + 4 + *piVar8 * 0xc) =
           fStack_b0 * 0.33333334 + *(float *)(iVar2 + 4 + *piVar8 * 0xc);
      iVar2 = *(int *)(*(int *)(iVar1 + 4) + 0x24);
      *(float *)(iVar2 + *piVar8 * 0xc) = fStack_b4 * 0.33333334 + *(float *)(iVar2 + *piVar8 * 0xc)
      ;
      *(undefined4 *)(*(int *)(*(int *)(iVar1 + 4) + 0x24) + 8 + *piVar8 * 0xc) = 0;
      iVar2 = *(int *)(*(int *)(iVar1 + 4) + 0x24);
      pfVar6 = (float *)(iVar2 + 4 + *piVar8 * 0xc);
      fVar4 = -fVar3;
      if ((-fVar3 <= *(float *)(iVar2 + 4 + *piVar8 * 0xc)) && (fVar4 = fVar3, *pfVar6 <= fVar3)) {
        fVar4 = *pfVar6;
      }
      *pfVar6 = fVar4;
      iVar2 = *(int *)(*(int *)(iVar1 + 4) + 0x24);
      pfVar6 = (float *)(iVar2 + *piVar8 * 0xc);
      fVar4 = -fVar10;
      if ((-fVar10 <= *(float *)(iVar2 + *piVar8 * 0xc)) && (fVar4 = fVar10, *pfVar6 <= fVar10)) {
        fVar4 = *pfVar6;
      }
      *pfVar6 = fVar4;
      piVar8 = piVar8 + 1;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    *(undefined4 *)(*(int *)(iVar1 + 4) + 0x1c) = 0;
  }
  return;
}
#undef afStack_30
#undef afStack_60
#undef afStack_90
#undef afStack_9c
#undef afStack_a8
#undef fStack_b0
#undef fStack_b4
#undef fStack_c8
#undef local_c0
#undef local_c4


/* ---- 0x00490210  Actor_UpdateTalk ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lip sync: reads the current phoneme from iMUSE, plays the matching talk chore, ends speech when
   the voice or the text timer runs out */

void __cdecl Actor_UpdateTalk(void *actor,float dt)

{
  int *piVar1;
  ushort uVar2;
  int iVar3;
  undefined2 extraout_var;
  int *piVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  
  iVar3 = *(int *)((int)actor + 0xa4);
  if (*(int *)(iVar3 + 0x1c4) == 0) {
    return;
  }
  if (((*(char *)(iVar3 + 0x1dc) != '\0') && (*(int *)(iVar3 + 0x1f0) != 0)) &&
     (*(int *)((int)actor + 0xa0) != 0)) {
    iVar3 = iMUSE_GetPhoneme(*(int *)(iVar3 + 0x1c8),0);
    if (iVar3 == 0) {
      sputActor_ShutUp(actor);
    }
    else {
      uVar2 = Phoneme_ToTalkChore(actor,iVar3);
      piVar4 = *(int **)((int)actor + 0xa0);
      piVar1 = piVar4 + 1;
      if (piVar4 != (int *)0x0) {
        do {
          if ((piVar4[1] != *piVar1) || (-1 < piVar4[CONCAT22(extraout_var,uVar2) + 0xe])) break;
          piVar4 = (int *)piVar4[0x2c];
        } while (piVar4 != (int *)0x0);
        if ((piVar4 != (int *)0x0) && (piVar4[1] == *piVar1)) {
          Cos_InstCompleteChore(*piVar4,piVar4[CONCAT22(extraout_var,uVar2) + 0xe]);
        }
      }
    }
  }
  iVar3 = *(int *)((int)actor + 0xa4);
  lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  *(int *)(iVar3 + 0x1cc) = *(int *)(iVar3 + 0x1cc) + (int)lVar5;
  if ((*(char *)(*(int *)((int)actor + 0xa4) + 0x1dc) == '\0') ||
     (iVar3 = Actor_IsVoicePlaying(actor), iVar3 != 0)) {
    if (*(char *)(*(int *)((int)actor + 0xa4) + 0x1dc) != '\0') {
      return;
    }
    if (-1 < *(int *)(*(int *)((int)actor + 0xa4) + 0x1cc)) {
      return;
    }
  }
  sputActor_ShutUp(actor);
  return;
}
#endif


/* ---- 0x00490320  sputActor_SetSelectedActor ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua SetSelectedActor; returns the handle or -1 Original name sputActor_SetSelectedActor (the
   remaster's GrimFandango (Linux): the only unmatched callee of Lua_SetSelectedActor; 1 matched
   neighbours agree, 0 disagree); was Actor_SetSelected. */

int __cdecl sputActor_SetSelectedActor(int handle)

{
  int iVar1;
  int unaff_retaddr;
  
  iVar1 = -1;
  if (g_pSelectedActor != (void *)0x0) {
    iVar1 = sputActor_GetActorHandle(g_pSelectedActor,unaff_retaddr);
  }
  if ((-1 < handle) && (handle < g_nMaxActors)) {
    g_pSelectedActor = (void *)((int)g_pActors + handle * 0xa8);
  }
  return iVar1;
}
#endif


/* ---- 0x00490360  sputActor_ActorDeref ---- */
/* Original name sputActor_ActorDeref (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_ActorVoiceIs3D; the only unmatched callee of Lua_GetActorCostumeDepth; the only
   unmatched callee of Lua_GetActorLookRate; the only unmatched callee of Lua_GetActorPos; the only
   unmatched callee of Lua_GetActorRect; the only unmatched callee of Lua_GetActorRot; the only
   unmatched callee of Lua_GetActorScale; the only unmatched callee of Lua_GetActorTalkColor; the
   only unmatched callee of Lua_IsActorLooking; the only unmatched callee of Lua_IsActorMoving; the
   only unmatched callee of Lua_SetActorLookRate; the only unmatched callee of Lua_SetActorPitch;
   the only unmatched callee of Lua_SetActorRoll; the only unmatched callee of Lua_SetActorScale;
   the only unmatched callee of Lua_SetActorVisibility; 97 matched neighbours agree, 0 disagree);
   was Actor_FromHandle. */

void * sputActor_ActorDeref(int param_1)

{
  return (void *)((int)g_pActors + param_1 * 0xa8);
}

/* ---- 0x00490380  sputActor_GetActorHandle ---- */
/* Original name sputActor_GetActorHandle (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_CallCostumeMarkerHandler; the only unmatched callee of
   Lua_CallCostumeOverrideHandler; 3 matched neighbours agree, 1 disagree); was Actor_GetHandle. */

int __cdecl sputActor_GetActorHandle(void *actor,int tag)

{
  return ((int)actor - (int)g_pActors) / 0xa8;
}

/* ---- 0x004903a0  sputActor_AllocateActor ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Lua LoadActor: allocates an actor record and returns its handle (-1 when full) Original name
   sputActor_AllocateActor (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_LoadActor; 1 matched neighbours agree, 0 disagree); was Actor_Create. */

int sputActor_AllocateActor(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined4 *puVar5;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define aiStack_10 (*(int (*)[4])(_frame + (0x30 - 0x10)))
  
  iVar2 = 0;
  puVar5 = (undefined4 *)0x0;
  if (0 < g_nMaxActors) {
    piVar4 = (int *)((int)g_pActors + 0x9c);
    do {
      if (*piVar4 == 0) {
        puVar5 = (undefined4 *)((int)g_pActors + iVar2 * 0xa8);
        break;
      }
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 0x2a;
    } while (iVar2 < g_nMaxActors);
  }
  if (puVar5 == (undefined4 *)0x0) {
    iVar2 = 0;
    do {
      if (*(int *)((int)&g_pTalkingActors + iVar2) != 0) {
        *(int *)((int)aiStack_10 + iVar2) =
             (*(int *)((int)&g_pTalkingActors + iVar2) - (int)g_pActors) / 0xa8;
      }
      iVar2 = iVar2 + 4;
    } while (iVar2 < 0x10);
    if (g_pSelectedActor != (void *)0x0) {
      local_14 = ((int)g_pSelectedActor - (int)g_pActors) / 0xa8;
    }
    g_pActors = (void *)(**(code **)(g_dwSputActHS + 0x28))
                                  (g_pActors,(g_nMaxActors + 0x20) * 0xa8,
                                   s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x5f6);
    puVar5 = (undefined4 *)((int)g_pActors + g_nMaxActors * 0xa8);
    for (iVar2 = 0x540; pvVar1 = g_pActors, iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    iVar2 = 0;
    puVar5 = (undefined4 *)((int)g_pActors + g_nMaxActors * 0xa8);
    g_nMaxActors = g_nMaxActors + 0x20;
    do {
      if (*(int *)((int)&g_pTalkingActors + iVar2) != 0) {
        *(void **)((int)&g_pTalkingActors + iVar2) =
             (void *)((int)pvVar1 + *(int *)((int)aiStack_10 + iVar2) * 0xa8);
      }
      iVar2 = iVar2 + 4;
    } while (iVar2 < 0x10);
    if (g_pSelectedActor != (void *)0x0) {
      g_pSelectedActor = (void *)((int)pvVar1 + local_14 * 0xa8);
    }
  }
  g_nNumActors = g_nNumActors + 1;
  puVar3 = puVar5;
  for (iVar2 = 0x2a; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar5[0xd] = 1;
  rdMatrix_Identity34((float *)(puVar5 + 0xe));
  puVar5[0xc] = 0x3f800000;
  puVar5[0x28] = 0;
  puVar3 = (undefined4 *)
           (**(code **)(g_dwSputActHS + 0x20))
                     (0x34,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x60e);
  *puVar5 = puVar3;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar5[0x27] = 1;
  return ((int)puVar5 - (int)g_pActors) / 0xa8;
}
#undef aiStack_10
#undef local_14


/* ---- 0x00490580  sputActor_AllocateActorExtra ---- */
/* Source: Engine/sputActor.cpp (lines 1561-1564, from __FILE__/__LINE__ passed to the allocator)
   Original name sputActor_AllocateActorExtra (the remaster's GrimFandango (Linux): the only
   unmatched callee of Lua_ActorLookAt; the only unmatched callee of Lua_GetActorPuckVector; the
   only unmatched callee of Lua_GetActorTimeScale; the only unmatched callee of
   Lua_GetActorTurnRate; the only unmatched callee of Lua_GetActorWalkRate; the only unmatched
   callee of Lua_IsActorResting; the only unmatched callee of Lua_IsActorTurning; the only unmatched
   callee of Lua_SetActorCollisionScale; the only unmatched callee of Lua_SetActorOffsetYaw; the
   only unmatched callee of Lua_SetActorTalkColor; the only unmatched callee of
   Lua_SetActorTimeScale; the only unmatched callee of Lua_SetActorTurnRate; the only unmatched
   callee of Lua_SetActorWalkRate; 20 matched neighbours agree, 1 disagree); was Actor_CreateExtra.
    */

void sputActor_AllocateActorExtra(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 0xa4) != 0)) {
    (**(code **)(g_dwSputActHS + 0x18))
              (s_pActor_____pActor__pExtra_004e9eb8,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,
               0x619);
  }
  iVar1 = (**(code **)(g_dwSputActHS + 0x20))
                    (0x4a0,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x61b);
  *(int *)(param_1 + 0xa4) = iVar1;
  if (iVar1 == 0) {
    (**(code **)(g_dwSputActHS + 0x18))
              (s_pActor__pExtra_004e9ea8,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x61c);
  }
  puVar2 = *(undefined4 **)(param_1 + 0xa4);
  for (iVar1 = 0x128; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x18) = 0x3ecccccd;
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x1c) = 0x43070000;
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x1bc) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x1c0) = 0x42700000;
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x3f4) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x41c) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x418) = 0xffffff;
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x420) = 0xffffffff;
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x400) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x404) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x408) = 0x3f800000;
  return;
}

/* ---- 0x004906b0  sputActor_EnableWalkSystem ---- */
/* Actor_SetFollowBoxes(actor, follow): sets extra+0x1b8. Following creates the walker and
   reattaches it to the set; not following clears the walker's sector (+0x5c) but keeps the walker.
   Original name sputActor_EnableWalkSystem (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetActorFollowBoxes; 1 matched neighbours agree, 1 disagree); was
   Actor_SetFollowBoxes. */

void sputActor_EnableWalkSystem(int param_1,int param_2)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xa4) == 0) {
    sputActor_AllocateActorExtra(param_1);
  }
  if (param_2 != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x1b8) = 1;
    sputActor_EnablePuck(param_1,1);
    Puck_Validate(*(void **)(*(int *)(param_1 + 0xa4) + 0x1b4));
    return;
  }
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x1b8) = 0;
  iVar1 = *(int *)(*(int *)(param_1 + 0xa4) + 0x1b4);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x5c) = 0;
  }
  return;
}

/* ---- 0x00490730  sputActor_EnablePuck ---- */
/* Source: Engine/sputActor.cpp (line 1637, from __FILE__/__LINE__ passed to the allocator) Original
   name sputActor_EnablePuck (the remaster's GrimFandango (Linux): the only unmatched callee of
   Actor_TurnKey; the only unmatched callee of Actor_WalkForward; 7 matched neighbours agree, 0
   disagree); was Actor_CreateWalker. */

void sputActor_EnablePuck(void *param_1,int param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  float *pfVar2;
  void *p;
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  
  p = (void *)0x0;
  if ((param_2 == 0) &&
     (pvVar1 = *(void **)(*(int *)((int)param_1 + 0xa4) + 0x1b4), pvVar1 != (void *)0x0)) {
    Walker_Destroy((int)pvVar1);
    Plat_Free(pvVar1);
    *(undefined4 *)(*(int *)((int)param_1 + 0xa4) + 0x1b4) = 0;
    return;
  }
  if (*(int *)(*(int *)((int)param_1 + 0xa4) + 0x1b4) == 0) {
    pvVar1 = Plat_Alloc(0x60);
    if (pvVar1 != (void *)0x0) {
      p = Walker_Create(pvVar1,*(float *)(*(int *)((int)param_1 + 0xa4) + 0x1c0));
    }
    Mem_CheckAlloc(p,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x665);
    Puck_SetPos(p,(float *)((int)param_1 + 0xc));
    pfVar2 = Actor_GetFrame(param_1);
    local_18[0] = pfVar2[3] + *(float *)((int)param_1 + 0xc);
    local_18[1] = *(float *)((int)param_1 + 0x10) + pfVar2[4];
    local_18[2] = *(float *)((int)param_1 + 0x14) + pfVar2[5];
    Puck_PointAt(p,local_18,3.4028235e+38);
    *(void **)(*(int *)((int)param_1 + 0xa4) + 0x1b4) = p;
  }
  return;
}
#undef local_18


/* ---- 0x00490870  sputActor_SetActorPosition ---- */
/* Original name sputActor_SetActorPosition (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_PutActorAt; the only unmatched callee of Lua_PutActorAtInterest; 2 matched
   neighbours agree, 1 disagree); was Actor_SetPositionClamped. */

void sputActor_SetActorPosition(int param_1,float *param_2)

{
  undefined4 uVar1;
  float fVar2;
  undefined4 *this;
  
  this = (undefined4 *)0x0;
  if (*(int *)(param_1 + 0xa4) != 0) {
    this = *(undefined4 **)(*(int *)(param_1 + 0xa4) + 0x1b4);
  }
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xfffffffe;
  if (this != (undefined4 *)0x0) {
    Puck_SetPos(this,param_2);
    if (*(int *)(*(int *)(param_1 + 0xa4) + 0x1b8) != 0) {
      Puck_Validate(this);
    }
    *(undefined4 *)(param_1 + 0xc) = *this;
    *(undefined4 *)(param_1 + 0x10) = this[1];
    uVar1 = this[2];
    *(undefined4 *)(param_1 + 0x34) = 0;
    *(undefined4 *)(param_1 + 0x14) = uVar1;
    return;
  }
  *(float *)(param_1 + 0xc) = *param_2;
  *(float *)(param_1 + 0x10) = param_2[1];
  fVar2 = param_2[2];
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(float *)(param_1 + 0x14) = fVar2;
  return;
}

/* ---- 0x00490900  sputActor_SetActorRotation ---- */
/* WARNING: Variable defined which should be unmapped: local_40 */
/* Actor_SetRot(actor, angles, snap): clears actor+8 bit 0 first, which ends a WalkActorTo path walk
   (Actor_UpdateMovement only calls Actor_FollowPath while it is set). Pitch (+0x24) and roll
   (+0x2c) are always set at once. With a walker, the walker heading is turned to the yaw
   immediately, +0x28 (angle left) is set, and the visible yaw eases there in Walker_UpdateYaw; snap
   (5th Lua arg nil) negates the turn rate so that update jumps in one frame. Without a walker all
   three angles are set at once. Does not create a walker. Original name sputActor_SetActorRotation
   (the remaster's GrimFandango (Linux): the only unmatched callee of Lua_SetActorRot; 2 matched
   neighbours agree, 0 disagree); was Actor_SetRot. */

void sputActor_SetActorRotation(int param_1,undefined4 *param_2,int param_3)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *this;
  int iVar1;
  undefined4 uVar2;
  float fVar3;
  #define local_40 (*(float *)(_frame + (0x50 - 0x40)))
  #define local_30 (*(undefined1 (*)[12])(_frame + (0x50 - 0x30)))
  #define local_24 (*(float (*)[3])(_frame + (0x50 - 0x24)))
  
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xfffffffe;
  if ((*(int *)(param_1 + 0xa4) != 0) &&
     (this = *(float **)(*(int *)(param_1 + 0xa4) + 0x1b4), this != (float *)0x0)) {
    Angles_ToMatrixNoPos(local_30,param_2);
    local_24[0] = local_24[0] + *this;
    local_24[1] = this[1] + local_24[1];
    local_24[2] = this[2] + local_24[2];
    Walker_ToLocalSpace(this,local_24);
    local_24[2] = 0.0;
    rdVector_Normalize3Acc(local_24);
    fVar3 = stdMath_ArcSin3(local_24[1]);
    fVar3 = 90.0 - fVar3;
    local_40 = fVar3;
    if (0.0 < local_24[0]) {
      local_40 = -fVar3;
    }
    Walker_TurnHeading(this,local_40);
    iVar1 = *(int *)(param_1 + 0xa4);
    if ((0.0 < *(float *)(iVar1 + 0x1c)) && (param_3 != 0)) {
      *(float *)(iVar1 + 0x1c) = *(float *)(iVar1 + 0x1c) * -1.0;
    }
    *(float *)(*(int *)(param_1 + 0xa4) + 0x28) = fVar3;
    *(undefined4 *)(param_1 + 0x2c) = param_2[2];
    *(undefined4 *)(param_1 + 0x24) = *param_2;
    *(undefined4 *)(param_1 + 0x34) = 0;
    return;
  }
  *(undefined4 *)(param_1 + 0x24) = *param_2;
  *(undefined4 *)(param_1 + 0x28) = param_2[1];
  uVar2 = param_2[2];
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x2c) = uVar2;
  return;
}
#undef local_24
#undef local_30
#undef local_40


/* ---- 0x00490a40  sputActor_SetReflection ---- */
/* Original name sputActor_SetReflection (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetActorReflection; 1 matched neighbours agree, 0 disagree); was
   Actor_SetReflection. */

void __cdecl sputActor_SetReflection(void *actor,float angle)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)((int)actor + 0xa4) + 0x1b4);
  if (iVar1 != 0) {
    *(float *)(iVar1 + 0x3c) = angle;
  }
  return;
}

/* ---- 0x00490b50  Actor_SetTurnChores ---- */
void __cdecl Actor_SetTurnChores(void *actor,int leftChore,int rightChore,void *costume)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  
  piVar3 = *(int **)((int)actor + 0xa0);
  if (piVar3 != (int *)0x0) {
    if (costume == (void *)0x0) {
      costume = piVar3;
    }
    piVar1 = piVar3 + 1;
    if (piVar3 != (int *)0x0) {
      do {
        if ((piVar3[1] != *piVar1) || (-1 < piVar3[0xb])) break;
        piVar3 = (int *)piVar3[0x2c];
      } while (piVar3 != (int *)0x0);
      if ((piVar3 != (int *)0x0) && (piVar3[1] == *piVar1)) {
        if (leftChore != piVar3[0xb]) {
          uVar2 = Cos_InstChoreStatus(*piVar3,piVar3[0xb]);
          if ((uVar2 != 0) && (Cos_InstStopChore(*piVar3,piVar3[0xb]), leftChore != -1)) {
            Cos_InstPlayChore(*piVar3,leftChore,uVar2 & 2,~uVar2 >> 2 & 1);
          }
          piVar3[0xb] = -1;
          *(int *)((int)costume + 0x2c) = leftChore;
        }
        if (rightChore == piVar3[0xc]) {
          return;
        }
        uVar2 = Cos_InstChoreStatus(*piVar3,piVar3[0xc]);
        if ((uVar2 != 0) && (Cos_InstStopChore(*piVar3,piVar3[0xc]), leftChore != -1)) {
          Cos_InstPlayChore(*piVar3,rightChore,uVar2 & 2,~uVar2 >> 2 & 1);
        }
        piVar3[0xc] = -1;
        *(int *)((int)costume + 0x30) = rightChore;
        return;
      }
    }
    *(int *)((int)costume + 0x2c) = leftChore;
    *(int *)((int)costume + 0x30) = rightChore;
  }
  return;
}

/* ---- 0x00490c80  Actor_SetRestChore ---- */
void __cdecl Actor_SetRestChore(void *actor,int chore,void *costume)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  
  piVar3 = *(int **)((int)actor + 0xa0);
  if (piVar3 != (int *)0x0) {
    if (costume == (void *)0x0) {
      costume = piVar3;
    }
    piVar1 = piVar3 + 1;
    if (piVar3 != (int *)0x0) {
      do {
        if ((piVar3[1] != *piVar1) || (-1 < piVar3[0xd])) break;
        piVar3 = (int *)piVar3[0x2c];
      } while (piVar3 != (int *)0x0);
      if ((piVar3 != (int *)0x0) && (piVar3[1] == *piVar1)) {
        if (chore == piVar3[0xd]) {
          return;
        }
        uVar2 = Cos_InstChoreStatus(*piVar3,piVar3[0xd]);
        if ((uVar2 != 0) && (Cos_InstStopChore(*piVar3,piVar3[0xd]), chore != -1)) {
          Cos_InstPlayChore(*piVar3,chore,uVar2 & 2,~uVar2 >> 2 & 1);
        }
        piVar3[0xd] = -1;
        *(int *)((int)costume + 0x34) = chore;
        return;
      }
    }
    *(int *)((int)costume + 0x34) = chore;
  }
  return;
}

/* ---- 0x00490d30  sputActor_PushCostume ---- */
/* Original name sputActor_PushCostume (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_PushActorCostume; 2 matched neighbours agree, 0 disagree); was Actor_PushCostume.
    */

int __cdecl sputActor_PushCostume(void *actor,char *name,int param_3)

{
  void *costumeRes;
  void *pvVar1;
  
  if ((name == (char *)0x0) || (param_3 != 0)) {
    costumeRes = (void *)0x0;
    pvVar1 = *(void **)((int)actor + 0xa0);
  }
  else {
    costumeRes = sputResource_Alloc(0x54534f43,name);
    if (costumeRes == (void *)0x0) {
      return 0;
    }
    param_3 = 0;
    pvVar1 = *(void **)((int)actor + 0xa0);
  }
  pvVar1 = Costume_Push(pvVar1,costumeRes,param_3);
  *(void **)((int)actor + 0xa0) = pvVar1;
  Cos_InstSetUserData(**(int **)((int)actor + 0xa0),((int)actor - (int)g_pActors) / 0xa8);
  Actor_SetFrustumCull(actor,~*(uint *)((int)actor + 4) >> 2 & 1);
  return 1;
}

/* ---- 0x00490dd0  sputActor_PopCostume ---- */
/* Original name sputActor_PopCostume (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_PopActorCostume; 2 matched neighbours agree, 0 disagree); was Actor_PopCostume. */

void __cdecl sputActor_PopCostume(void *actor,int free)

{
  void *pvVar1;
  
  pvVar1 = sputCostume_PopCostume(*(void **)((int)actor + 0xa0),free);
  *(void **)((int)actor + 0xa0) = pvVar1;
  return;
}

/* ---- 0x00490f50  Actor_PuckOrient ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_68 */
/* Actor_PuckOrient: at the end of the actor update when actor+4 & 0x10 (ActorPuckOrient). Rebuilds
   the actor matrix, takes the angle between its up row and the up vector of the walker frame; over
   2 degrees it turns about up x normal by min(angle, frame seconds * turn rate), multiplies
   (Matrix_Multiply) and sets the three angles from the matrix (Matrix_ToAngles). */

void __cdecl Actor_PuckOrient(void *actor)

{
  unsigned char _frame[0x80] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  void *pvVar6;
  float fVar7;
  #define local_68 (*(uint *)(_frame + (0x80 - 0x68)))
  #define local_54 (*(float (*)[3])(_frame + (0x80 - 0x54)))
  #define local_48 (*(float (*)[3])(_frame + (0x80 - 0x48)))
  #define local_3c (*(float (*)[3])(_frame + (0x80 - 0x3c)))
  #define local_30 (*(undefined1 (*)[48])(_frame + (0x80 - 0x30)))
  
  if (((actor != (void *)0x0) && (*(int *)((int)actor + 0xa4) != 0)) &&
     (iVar4 = *(int *)(*(int *)((int)actor + 0xa4) + 0x1b4), iVar4 != 0)) {
    iVar1 = (int)actor + 0xc;
    iVar2 = (int)actor + 0x24;
    iVar3 = (int)actor + 0x38;
    Angles_ToMatrix(iVar3,iVar2,iVar1);
    local_48[0] = *(float *)((int)actor + 0x50);
    local_48[1] = *(float *)((int)actor + 0x54);
    local_48[2] = *(float *)((int)actor + 0x58);
    local_54[0] = *(float *)(iVar4 + 0x24);
    local_54[1] = *(float *)(iVar4 + 0x28);
    local_54[2] = *(float *)(iVar4 + 0x2c);
    fVar7 = Vec3_Dot2(local_48,local_54);
    fVar7 = stdMath_ArcSin3(fVar7);
    pvVar5 = PUN(void *,(float)(90.0 - fVar7));
    pvVar6 = pvVar5;
    if (PUN(float,pvVar5) < 0.0) {
      pvVar6 = PUN(void *,(float)-PUN(float,pvVar5));
    }
    if (2.0 < PUN(float,pvVar6)) {
      fVar7 = sputTime_GetFrameTimeFlex();
      pvVar6 = PUN(void *,(float)(fVar7 * *(float *)(*(int *)((int)actor + 0xa4) + 0x1c)));
      actor = pvVar5;
      if ((0.0 < PUN(float,pvVar5)) && (PUN(float,pvVar6) < PUN(float,pvVar5))) {
        actor = pvVar6;
      }
      if ((PUN(float,actor) < 0.0) && (PUN(float,actor) < -PUN(float,pvVar6))) {
        actor = PUN(void *,(float)-PUN(float,pvVar6));
      }
      local_3c[0] = local_54[2] * local_48[1] - local_54[1] * local_48[2];
      local_3c[1] = local_54[0] * local_48[2] - local_54[2] * local_48[0];
      local_3c[2] = local_54[1] * local_48[0] - local_54[0] * local_48[1];
      rdVector_Normalize3Acc(local_3c);
      Matrix_AxisAngle(local_30,local_3c,PUN(float,actor));
      Matrix_Multiply(iVar3,local_30);
      Matrix_ToAngles(iVar3,iVar2);
      Angles_ToMatrix(iVar3,iVar2,iVar1);
    }
  }
  return;
}
#undef local_30
#undef local_3c
#undef local_48
#undef local_54
#undef local_68

#endif


/* ---- 0x00491110  Actor_UpdateWalker ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void Actor_UpdateWalker(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 uVar4;
  float fVar5;
  uint turnLeftOk;
  uint turnRightOk;
  
  puVar1 = *(undefined4 **)(*(int *)(param_1 + 0xa4) + 0x1b4);
  if ((*(int *)(*(int *)(param_1 + 0xa4) + 0x10) != 0) && ((*(byte *)(param_1 + 8) & 1) == 0)) {
    iVar2 = *(int *)(param_1 + 0xa4);
    fVar5 = sputTime_GetFrameTimeFlex();
    Walker_TurnHeading(*(void **)(iVar2 + 0x1b4),
                       (float)*(int *)(iVar2 + 0x10) *
                       *(float *)(iVar2 + 0x1c) * fVar5 * *(float *)(iVar2 + 0x41c));
  }
  iVar2 = *(int *)(param_1 + 0xa4);
  if (*(int *)(iVar2 + 0xc) != 0) {
    fVar5 = sputTime_GetFrameTimeFlex();
    if (*(int *)(iVar2 + 0x1bc) == 0) {
      turnRightOk = (uint)(*(int *)(iVar2 + 0x10) != 1);
      turnLeftOk = (uint)(*(int *)(iVar2 + 0x10) != -1);
    }
    else {
      turnRightOk = 1;
      turnLeftOk = 1;
    }
    puVar3 = Walker_WalkSectors(*(void **)(iVar2 + 0x1b4),
                                fVar5 * *(float *)(iVar2 + 0x41c) * *(float *)(iVar2 + 0x18),
                                turnLeftOk,turnRightOk);
    *(undefined **)(*(int *)(param_1 + 0xa4) + 0xc) = puVar3;
  }
  uVar4 = Walker_UpdateYaw(param_1,puVar1);
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x20) = uVar4;
  iVar2 = *(int *)(param_1 + 0xa4);
  if ((*(int *)(iVar2 + 0x10) == 0) && (*(int *)(iVar2 + 0x20) == 0)) {
    if (*(float *)(iVar2 + 0x28) <= 0.0) {
      uVar4 = 1;
    }
    else {
      uVar4 = 0xffffffff;
    }
    *(undefined4 *)(iVar2 + 0x10) = uVar4;
  }
  *(undefined4 *)(param_1 + 0xc) = *puVar1;
  *(undefined4 *)(param_1 + 0x10) = puVar1[1];
  uVar4 = puVar1[2];
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x14) = uVar4;
  return;
}
#endif


/* ---- 0x004913f0  Actor_UpdateMoveChores ---- */
/* Actor_UpdateMoveChores (after Actor_UpdateWalker): costume record [10] walk, [0xb] left turn,
   [0xc] right turn, [0xd] rest. Walking (walker+0xc): start walk chore (rest flag +0x14 = 0) else
   stop it; walking clears +0x10. +0x10 >= 1 plays left, < 0 plays right (eased turns set -1 always:
   right chore); starting one clears +0x14. Not walking and +0x10 == 0 sets +0x14 = 1; rest plays
   while +0x14 else stops. Clears +0xc and +0x10. Start/stop fade 130 ms (DAT_004e9e04). */

void Actor_UpdateMoveChores(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  
  if (*(int *)(param_1 + 0xa4) == 0) {
    return;
  }
  piVar4 = *(int **)(param_1 + 0xa0);
  if (piVar4 == (int *)0x0) {
    return;
  }
  piVar5 = piVar4 + 1;
  if (piVar4 != (int *)0x0) {
    do {
      if ((piVar4[1] != *piVar5) || (-1 < piVar4[10])) break;
      piVar4 = (int *)piVar4[0x2c];
    } while (piVar4 != (int *)0x0);
    if ((piVar4 != (int *)0x0) && (piVar4[1] == *piVar5)) {
      uVar2 = Cos_InstChoreStatus(*piVar4,piVar4[10]);
      iVar1 = *(int *)(*(int *)(param_1 + 0xa4) + 0xc);
      if (iVar1 == 0) {
LAB_00491477:
        if (((uVar2 & 1) != 0) && ((*(byte *)(param_1 + 8) & 1) == 0)) {
          FadeOutChore((void *)*piVar4,piVar4[10],g_nWALKSYSTEM_FADE_TIME);
        }
      }
      else if (uVar2 == 0) {
        *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x14) = 0;
        FadeInChore(*piVar4,piVar4[10],g_nWALKSYSTEM_FADE_TIME);
      }
      else if (iVar1 == 0) goto LAB_00491477;
    }
  }
  if (*(int *)(*(int *)(param_1 + 0xa4) + 0xc) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x10) = 0;
  }
  piVar4 = *(int **)(param_1 + 0xa0);
  iVar1 = piVar4[1];
  if (piVar4 != (int *)0x0) {
    do {
      if ((piVar4[1] != iVar1) || (-1 < piVar4[0xb])) break;
      piVar4 = (int *)piVar4[0x2c];
    } while (piVar4 != (int *)0x0);
    if (piVar4 != (int *)0x0) {
      if ((piVar4[1] == iVar1) && (-1 < piVar4[0xb])) {
        uVar2 = Cos_InstChoreStatus(*piVar4,piVar4[0xb]);
        iVar3 = *(int *)(*(int *)(param_1 + 0xa4) + 0x10);
        if (iVar3 < 1) {
LAB_00491517:
          if ((uVar2 & 1) != 0) {
            FadeOutChore((void *)*piVar4,piVar4[0xb],g_nWALKSYSTEM_FADE_TIME);
          }
        }
        else if (uVar2 == 0) {
          *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x14) = 0;
          FadeInChore(*piVar4,piVar4[0xb],g_nWALKSYSTEM_FADE_TIME);
        }
        else if (iVar3 < 1) goto LAB_00491517;
      }
      if (((piVar4 != (int *)0x0) && (piVar4[1] == iVar1)) && (-1 < piVar4[0xc])) {
        uVar2 = Cos_InstChoreStatus(*piVar4,piVar4[0xc]);
        iVar1 = *(int *)(*(int *)(param_1 + 0xa4) + 0x10);
        if (iVar1 < 0) {
          if (uVar2 == 0) {
            *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x14) = 0;
            FadeInChore(*piVar4,piVar4[0xc],g_nWALKSYSTEM_FADE_TIME);
          }
          else if (-1 < iVar1) goto LAB_0049157a;
        }
        else {
LAB_0049157a:
          if ((uVar2 & 1) != 0) {
            FadeOutChore((void *)*piVar4,piVar4[0xc],g_nWALKSYSTEM_FADE_TIME);
          }
        }
      }
    }
  }
  iVar1 = *(int *)(param_1 + 0xa4);
  if ((*(int *)(iVar1 + 0xc) == 0) && (*(int *)(iVar1 + 0x10) == 0)) {
    *(undefined4 *)(iVar1 + 0x14) = 1;
  }
  piVar5 = *(int **)(param_1 + 0xa0);
  piVar4 = piVar5 + 1;
  if (piVar5 != (int *)0x0) {
    do {
      if ((piVar5[1] != *piVar4) || (-1 < piVar5[0xd])) break;
      piVar5 = (int *)piVar5[0x2c];
    } while (piVar5 != (int *)0x0);
    if (((piVar5 != (int *)0x0) && (piVar5[1] == *piVar4)) && (-1 < piVar5[0xd])) {
      iVar3 = Cos_InstChoreStatus(*piVar5,piVar5[0xd]);
      iVar1 = *(int *)(*(int *)(param_1 + 0xa4) + 0x14);
      if (iVar1 != 0) {
        if (iVar3 == 0) {
          FadeInChore(*piVar5,piVar5[0xd],g_nWALKSYSTEM_FADE_TIME);
          goto LAB_0049162b;
        }
        if (iVar1 != 0) goto LAB_0049162b;
      }
      if (iVar3 != 0) {
        FadeOutChore((void *)*piVar5,piVar5[0xd],g_nWALKSYSTEM_FADE_TIME);
      }
    }
  }
LAB_0049162b:
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0xc) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x10) = 0;
  return;
}

/* ---- 0x00492b30  Actor_SayLine ---- */
/* Starts speech: resolves the /id/ to a voice file (.wvc/.wav/.imc/.imu), plays it (3D positioned
   when flag 8), creates the subtitle text object, times text-only speech from its length, and plays
   the talk chore */

void __cdecl Actor_SayLine(void *actor,char *text,int background,int volume,int pan,int x,int y)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  char cVar2;
  byte bVar3;
  uint uVar4;
  char *text_00;
  int iVar5;
  byte *pbVar6;
  void **ppvVar7;
  void *pvVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  int *piVar12;
  int iVar13;
  byte *pbVar14;
  char *pcVar15;
  uint uVar16;
  char *pcVar17;
  bool bVar18;
  undefined4 uVar19;
  #define local_44 (*(byte (*)[32])(_frame + (0x60 - 0x44)))
  #define local_24 (*(char (*)[36])(_frame + (0x60 - 0x24)))
  
  if (*(int *)((int)actor + 0xa4) == 0) {
    sputActor_AllocateActorExtra(actor);
  }
  uVar4 = g_dwSmSpeechMode & 1;
  uVar16 = g_dwSmSpeechMode & 2;
  text_00 = sputText_ExtractSayLineData(text,(char *)local_44);
  local_24[0] = '\0';
  if (local_44[0] != 0) {
    sprintf(local_24,s__s_wvc_004e9eec,local_44);
    iVar5 = (**(code **)(g_dwSputActHS + 0x30))(local_24,&DAT_004ddb18);
    if (iVar5 == 0) {
      sprintf(local_24,s__s_wav_004e9ee4,local_44);
      iVar5 = (**(code **)(g_dwSputActHS + 0x30))(local_24,&DAT_004ddb18);
      if (iVar5 == 0) {
        sprintf(local_24,s__s_imc_004e9edc,local_44);
        iVar5 = (**(code **)(g_dwSputActHS + 0x30))(local_24,&DAT_004ddb18);
        if (iVar5 == 0) {
          sprintf(local_24,s__s_imu_004e9ed4,local_44);
          iVar5 = (**(code **)(g_dwSputActHS + 0x30))(local_24,&DAT_004ddb18);
          if (iVar5 == 0) {
            local_24[0] = '\0';
            goto LAB_00492c61;
          }
        }
      }
    }
    (**(code **)(g_dwSputActHS + 0x34))(iVar5);
  }
LAB_00492c61:
  if (*(int *)(*(int *)((int)actor + 0xa4) + 0x1c4) != 0) {
    if (local_44[0] != 0) {
      pbVar14 = local_44;
      pbVar6 = (byte *)(*(int *)((int)actor + 0xa4) + 0x1d0);
      do {
        bVar3 = *pbVar6;
        bVar18 = bVar3 < *pbVar14;
        if (bVar3 != *pbVar14) {
LAB_00492ca6:
          iVar5 = (1 - (uint)bVar18) - (uint)(bVar18 != 0);
          goto LAB_00492cab;
        }
        if (bVar3 == 0) break;
        bVar3 = pbVar6[1];
        bVar18 = bVar3 < pbVar14[1];
        if (bVar3 != pbVar14[1]) goto LAB_00492ca6;
        pbVar6 = pbVar6 + 2;
        pbVar14 = pbVar14 + 2;
      } while (bVar3 != 0);
      iVar5 = 0;
LAB_00492cab:
      if (iVar5 == 0) {
        return;
      }
    }
    sputActor_ShutUp(actor);
  }
  *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1cc) = 0;
  *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1c4) = 1;
  strncpy(*(int *)((int)actor + 0xa4) + 0x1d0,local_44,0xc);
  g_nNumActorsTalking = g_nNumActorsTalking + 1;
  iVar5 = 0;
  ppvVar7 = &g_pTalkingActors;
  do {
    if (*ppvVar7 == (void *)0x0) {
      (&g_pTalkingActors)[iVar5] = actor;
      break;
    }
    ppvVar7 = ppvVar7 + 1;
    iVar5 = iVar5 + 1;
  } while ((int)ppvVar7 < IMG_ADDR(0x008ca320));
  if (uVar16 != 0) {
    if (local_24[0] == '\0') {
LAB_00492e5e:
      *(undefined1 *)(*(int *)((int)actor + 0xa4) + 0x1dc) = 0;
    }
    else {
      if (background == 0) {
        iVar5 = SoundsLoadProcessStartSound((int)local_24,0x7f,2);
        *(int *)(*(int *)((int)actor + 0xa4) + 0x1c8) = iVar5;
        iVar5 = *(int *)(*(int *)((int)actor + 0xa4) + 0x1c8);
        if (iVar5 == 0) {
          *(undefined1 *)(*(int *)((int)actor + 0xa4) + 0x1dc) = 0;
          goto LAB_00492e6b;
        }
        SoundsSetParam(iVar5,0x600,volume);
        if ((*(byte *)((int)actor + 4) & 8) != 0) {
          uVar19 = *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1c8);
          goto LAB_00492dfb;
        }
      }
      else {
        iVar5 = SoundStartVoiceStream((int)local_24,volume,pan);
        if (iVar5 != 0) goto LAB_00492e5e;
        *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1c8) = 10000;
        if ((*(byte *)((int)actor + 4) & 8) != 0) {
          uVar19 = 10000;
LAB_00492dfb:
          Sound_SetPosition(uVar19,(int)actor + 0xc,0x14,0x7f,0x41000000,0x3f4ccccd);
        }
      }
      uVar16 = 0xffffffff;
      pcVar15 = local_24;
      do {
        pcVar17 = pcVar15;
        if (uVar16 == 0) break;
        uVar16 = uVar16 - 1;
        pcVar17 = pcVar15 + 1;
        cVar2 = *pcVar15;
        pcVar15 = pcVar17;
      } while (cVar2 != '\0');
      uVar16 = ~uVar16;
      pcVar15 = pcVar17 + -uVar16;
      pcVar17 = (char *)(*(int *)((int)actor + 0xa4) + 0x1dc);
      for (uVar11 = uVar16 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
        *(undefined4 *)pcVar17 = *(undefined4 *)pcVar15;
        pcVar15 = pcVar15 + 4;
        pcVar17 = pcVar17 + 4;
      }
      for (uVar16 = uVar16 & 3; uVar16 != 0; uVar16 = uVar16 - 1) {
        *pcVar17 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        pcVar17 = pcVar17 + 1;
      }
      iVar5 = iMUSE_GetPhoneme(*(int *)(*(int *)((int)actor + 0xa4) + 0x1c8),0);
      *(int *)(*(int *)((int)actor + 0xa4) + 0x1f0) = iVar5;
    }
LAB_00492e6b:
    *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1cc) = 0xffffffff;
  }
  if ((uVar4 != 0) || (*(char *)(*(int *)((int)actor + 0xa4) + 0x1dc) == '\0')) {
    pvVar8 = Actor_CreateSubtitle(actor,text_00,x,y);
    *(void **)(*(int *)((int)actor + 0xa4) + 0x1ec) = pvVar8;
    if (*(char *)(*(int *)((int)actor + 0xa4) + 0x1dc) == '\0') {
      uVar4 = 0xffffffff;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar2 = *text_00;
        text_00 = text_00 + 1;
      } while (cVar2 != '\0');
      *(uint *)(*(int *)((int)actor + 0xa4) + 0x1cc) =
           (~uVar4 - 1) * (0xb - g_nTextRate) * 0xf + 0x280;
    }
    TextObject_Activate(pvVar8,-1,0xd);
    ppvVar7 = &g_pTalkingActors;
    if (background == 0) {
      do {
        pvVar8 = *ppvVar7;
        if ((((pvVar8 != (void *)0x0) && (pvVar8 != actor)) &&
            (*(int *)(*(int *)((int)pvVar8 + 0xa4) + 0x1ec) != 0)) &&
           (*(int *)(*(int *)((int)pvVar8 + 0xa4) + 0x1c8) == 10000)) {
          puVar1 = (uint *)(*(int *)(*(int *)((int)actor + 0xa4) + 0x1ec) + 600);
          *puVar1 = *puVar1 | 2;
          break;
        }
        ppvVar7 = ppvVar7 + 1;
      } while ((int)ppvVar7 < IMG_ADDR(0x008ca320));
    }
    else {
      do {
        pvVar8 = *ppvVar7;
        if (((pvVar8 != (void *)0x0) && (pvVar8 != actor)) &&
           (iVar5 = *(int *)(*(int *)((int)pvVar8 + 0xa4) + 0x1ec), iVar5 != 0)) {
          puVar1 = (uint *)(iVar5 + 600);
          *puVar1 = *puVar1 | 2;
        }
        ppvVar7 = ppvVar7 + 1;
      } while ((int)ppvVar7 < IMG_ADDR(0x008ca320));
    }
  }
  if (((actor != (void *)0x0) && (iVar5 = *(int *)((int)actor + 0xa4), iVar5 != 0)) &&
     ((iVar13 = *(int *)((int)actor + 0xa0), iVar13 != 0 && (*(int *)(iVar5 + 0x1f0) != 0)))) {
    piVar10 = (int *)(iVar13 + 4);
    if (iVar13 != 0) {
      while (*(int *)(iVar13 + 4) == *piVar10) {
        iVar9 = 1;
        piVar12 = (int *)(iVar13 + 0x3c);
        do {
          if (-1 < *piVar12) break;
          iVar9 = iVar9 + 1;
          piVar12 = piVar12 + 1;
        } while (iVar9 < 10);
        if ((iVar9 < 10) || (iVar13 = *(int *)(iVar13 + 0xb0), iVar13 == 0)) break;
      }
      if ((iVar13 != 0) && (*(int *)(iVar13 + 4) == *piVar10)) goto LAB_00492fe7;
    }
    *(undefined4 *)(iVar5 + 0x1f0) = 0;
  }
LAB_00492fe7:
  if (((*(char *)(*(int *)((int)actor + 0xa4) + 0x1dc) == '\0') ||
      (*(int *)(*(int *)((int)actor + 0xa4) + 0x1f0) == 0)) &&
     (piVar10 = *(int **)((int)actor + 0xa0), piVar10 != (int *)0x0)) {
    piVar12 = piVar10 + 1;
    do {
      if ((piVar10[1] != *piVar12) || (-1 < piVar10[0x1e])) break;
      piVar10 = (int *)piVar10[0x2c];
    } while (piVar10 != (int *)0x0);
    if (((piVar10 != (int *)0x0) && (piVar10[1] == *piVar12)) && (-1 < piVar10[0x1e])) {
      Cos_InstPlayChore(*piVar10,piVar10[0x1e],1,0);
    }
  }
  return;
}
#undef local_24
#undef local_44


/* ---- 0x00493060  sputActor_ShutUp ---- */
/* Lua ShutUpActor: stops the actor's speech and talk chores Original name sputActor_ShutUp (the
   remaster's GrimFandango (Linux): the only unmatched callee of Lua_ShutUpActor; 1 matched
   neighbours agree, 1 disagree); was Actor_ShutUp. */

void __cdecl sputActor_ShutUp(void *actor)

{
  void *obj;
  int iVar1;
  int *piVar2;
  void **ppvVar3;
  int *piVar4;
  
  if ((actor != (void *)0x0) && (iVar1 = *(int *)((int)actor + 0xa4), iVar1 != 0)) {
    if (*(char *)(iVar1 + 0x1dc) != '\0') {
      if (*(int *)(iVar1 + 0x1c8) == 10000) {
        SoundStopVoiceStream();
      }
      else {
        SoundsStopSound(*(int *)(iVar1 + 0x1c8));
      }
    }
    obj = *(void **)(*(int *)((int)actor + 0xa4) + 0x1ec);
    if (obj != (void *)0x0) {
      List_Unlink(obj);
    }
    piVar4 = *(int **)((int)actor + 0xa0);
    if (piVar4 != (int *)0x0) {
      piVar2 = piVar4 + 1;
      if (piVar4 != (int *)0x0) {
        do {
          if ((piVar4[1] != *piVar2) || (-1 < piVar4[0x1e])) break;
          piVar4 = (int *)piVar4[0x2c];
        } while (piVar4 != (int *)0x0);
        if (((piVar4 != (int *)0x0) && (piVar4[1] == *piVar2)) && (-1 < piVar4[0x1e])) {
          iVar1 = Cos_InstChoreStatus(*piVar4,piVar4[0x1e]);
          if (iVar1 != 0) {
            Cos_InstStopChore(*piVar4,piVar4[0x1e]);
          }
        }
      }
      piVar2 = *(int **)((int)actor + 0xa0);
      piVar4 = piVar2 + 1;
      if (piVar2 != (int *)0x0) {
        do {
          if ((piVar2[1] != *piVar4) || (-1 < piVar2[0xe])) break;
          piVar2 = (int *)piVar2[0x2c];
        } while (piVar2 != (int *)0x0);
        if (((piVar2 != (int *)0x0) && (piVar2[1] == *piVar4)) && (-1 < piVar2[0xe])) {
          Cos_InstCompleteChore(*piVar2,piVar2[0xe]);
        }
      }
    }
    ppvVar3 = &g_pTalkingActors;
    do {
      if (*ppvVar3 == actor) {
        *ppvVar3 = (void *)0x0;
      }
      ppvVar3 = ppvVar3 + 1;
    } while ((int)ppvVar3 < IMG_ADDR(0x008ca320));
    *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1f0) = 0;
    *(undefined1 *)(*(int *)((int)actor + 0xa4) + 0x1dc) = 0;
    *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1ec) = 0;
    *(undefined1 *)(*(int *)((int)actor + 0xa4) + 0x1d0) = 0;
    *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1c4) = 0;
    if (0 < g_nNumActorsTalking) {
      g_nNumActorsTalking = g_nNumActorsTalking + -1;
    }
  }
  return;
}

/* ---- 0x004931f0  sputActor_LeaveSector ---- */
/* Lua GetSectorOppositeEdge: pushes the point on the far edge of the sector from the actor Original
   name sputActor_LeaveSector (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_GetSectorOppositeEdge; 1 matched neighbours agree, 1 disagree); was
   Actor_PushSectorOppositeEdge. */

void __cdecl sputActor_LeaveSector(int a1,int a2)

{
  float *walker;
  
  if (((a2 != 0) && (a1 != 0)) &&
     (walker = *(float **)(*(int *)(a1 + 0xa4) + 0x1b4), walker != (float *)0x0)) {
    WalkPlane_JumpOut((void *)a2,walker);
    sputActor_SetActorPosition(a1,walker);
  }
  return;
}

/* ---- 0x00493230  Actor_FollowPath ---- */
/* Actor_FollowPath(actor): walk to a point along the planned path (walker+0x2c next node); sets
   actor+8 bit 0 while the path lasts, clears it at the end. TurnActor and SetActorRot clear bit 0,
   ending the walk. */

void Actor_FollowPath(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  float fVar7;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  iVar6 = *(int *)(param_1 + 0xa4);
  fVar5 = *(float *)(param_1 + 0xc) - *(float *)(iVar6 + 0x2c);
  fVar3 = *(float *)(param_1 + 0x10) - *(float *)(iVar6 + 0x30);
  fVar4 = *(float *)(param_1 + 0x14) - *(float *)(iVar6 + 0x34);
  fVar2 = *(float *)(iVar6 + 0x18);
  if (*(float *)(iVar6 + 0x18) < 0.0) {
    fVar2 = -fVar2;
  }
  iVar6 = *(int *)(param_1 + 0xa4);
  fVar7 = sputTime_GetFrameTimeFlex();
  fVar2 = fVar7 * *(float *)(iVar6 + 0x41c) * fVar2 * 1.25;
  if (SQRT(fVar4 * fVar4 + fVar3 * fVar3 + fVar5 * fVar5) < fVar2) {
    do {
      if (*(int *)(iVar6 + 0x44) <= *(int *)(iVar6 + 0x1b0)) break;
      *(int *)(iVar6 + 0x1b0) = *(int *)(iVar6 + 0x1b0) + 1;
      sputActor_SetActorPosition(param_1,*(int *)(param_1 + 0xa4) + 0x2c);
      iVar6 = *(int *)(param_1 + 0xa4);
      puVar1 = (undefined4 *)(iVar6 + (*(int *)(iVar6 + 0x1b0) + 6) * 0xc);
      *(undefined4 *)(iVar6 + 0x2c) = *puVar1;
      *(undefined4 *)(iVar6 + 0x30) = puVar1[1];
      *(undefined4 *)(iVar6 + 0x34) = puVar1[2];
      iVar6 = *(int *)(param_1 + 0xa4);
      fVar5 = *(float *)(param_1 + 0xc) - *(float *)(iVar6 + 0x2c);
      fVar3 = *(float *)(param_1 + 0x10) - *(float *)(iVar6 + 0x30);
      fVar4 = *(float *)(param_1 + 0x14) - *(float *)(iVar6 + 0x34);
    } while (SQRT(fVar4 * fVar4 + fVar3 * fVar3 + fVar5 * fVar5) < fVar2);
    iVar6 = *(int *)(param_1 + 0xa4);
    if (*(int *)(iVar6 + 0x1b0) == *(int *)(iVar6 + 0x44)) {
      *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xfffffffe;
      return;
    }
  }
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 1;
  Puck_PointAt(*(void **)(iVar6 + 0x1b4),(float *)(iVar6 + 0x2c),3.4028235e+38);
  sputActor_Forward(param_1);
  return;
}
#undef local_10
#undef local_8
#undef local_c


/* ---- 0x004933c0  sputActor_SetWalkDominate ---- */
/* Original name sputActor_SetWalkDominate (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetActorWalkDominate; 1 matched neighbours agree, 0 disagree); was
   Actor_SetWalkDominate. */

void __cdecl sputActor_SetWalkDominate(void *actor,int dominate)

{
  *(int *)(*(int *)((int)actor + 0xa4) + 0x1bc) = dominate;
  return;
}

/* ---- 0x004933e0  sputActor_SetActorConstrain ---- */
/* Original name sputActor_SetActorConstrain (the remaster's GrimFandango (Linux): the only
   unmatched callee of Lua_SetActorConstrain; 1 matched neighbours agree, 0 disagree); was
   Actor_SetConstrain. */

void sputActor_SetActorConstrain(int param_1,int param_2)

{
  void *this;
  
  if ((((*(byte *)(param_1 + 8) & 1) == 0) || (param_2 == 0)) &&
     (this = *(void **)(*(int *)(param_1 + 0xa4) + 0x1b4), this != (void *)0x0)) {
    Puck_Constrain(this,param_2);
  }
  return;
}

/* ---- 0x004934b0  Actor_IsVoicePlaying ---- */
int __cdecl Actor_IsVoicePlaying(void *actor)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)((int)actor + 0xa4);
  if (*(char *)(iVar2 + 0x1dc) == '\0') {
    return 0;
  }
  if (*(int *)(iVar2 + 0x1c8) == 10000) {
    uVar1 = ImGetParam(10000,0x100);
    return (uint)(0 < (int)uVar1);
  }
  iVar2 = SoundsIsSoundPlaying(iVar2 + 0x1dc);
  return (uint)(0 < iVar2);
}

/* ---- 0x00493510  sputActor_ActorHasShadow ---- */
/* Original name sputActor_ActorHasShadow (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_ActorShadow; 1 matched neighbours agree, 0 disagree); was Actor_HasShadow. */

int __cdecl sputActor_ActorHasShadow(void *actor)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = (int *)(*(int *)((int)actor + 0xa4) + 0x1f8);
  do {
    if (*piVar1 != 0) {
      return 1;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 0x15;
  } while (iVar2 < 6);
  return 0;
}

/* ---- 0x00493540  Actor_ActivateShadow ---- */
void __cdecl Actor_ActivateShadow(void *actor,int shadowIdx,int active)

{
  *(int *)(*(int *)((int)actor + 0xa4) + (shadowIdx + 6) * 0x54) = active;
  return;
}

/* ---- 0x00493570  sputActor_SetShadowPlane ---- */
/* Original name sputActor_SetShadowPlane (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetActorShadowPlane; 1 matched neighbours agree, 0 disagree); was
   Actor_SetShadowPlane. */

void sputActor_SetShadowPlane(int param_1,char *param_2)

{
  undefined4 *puVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  void *pvVar7;
  
  puVar1 = (undefined4 *)
           (*(int *)(param_1 + 0xa4) + (*(int *)(*(int *)(param_1 + 0xa4) + 500) + 6) * 0x54);
  pvVar7 = WalkPlane_PlaneNamed(param_2);
  if (pvVar7 != (void *)0x0) {
    puVar1[2] = *(undefined4 *)((int)pvVar7 + 0x60);
    puVar1[3] = *(undefined4 *)((int)pvVar7 + 100);
    fVar2 = *(float *)((int)pvVar7 + 0x68);
    puVar1[4] = PUN(undefined4,(float)(fVar2));
    iVar6 = *(int *)((int)pvVar7 + 0x38);
    fVar3 = *(float *)(iVar6 + 8);
    fVar4 = *(float *)(iVar6 + 0xc);
    fVar5 = *(float *)(iVar6 + 4);
    *puVar1 = 1;
    puVar1[1] = 0;
    puVar1[5] = PUN(undefined4,(float)(-(fVar5 * PUN(float,puVar1[2]) + fVar3 * PUN(float,puVar1[3]) + fVar4 * fVar2)));
  }
  return;
}

/* ---- 0x004935f0  sputActor_SetShadowPoint ---- */
/* Original name sputActor_SetShadowPoint (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetActorShadowPoint; 1 matched neighbours agree, 0 disagree); was
   Actor_SetShadowPoint. */

void __cdecl sputActor_SetShadowPoint(void *actor,float x,float y,float z)

{
  int iVar1;
  
  iVar1 = *(int *)((int)actor + 0xa4) + (*(int *)(*(int *)((int)actor + 0xa4) + 500) + 6) * 0x54;
  *(float *)(iVar1 + 0x18) = x;
  *(float *)(iVar1 + 0x1c) = y;
  *(float *)(iVar1 + 0x20) = z;
  return;
}

/* ---- 0x00493630  Actor_SetShadowValid ---- */
void __cdecl Actor_SetShadowValid(void *actor,int shadowIdx,int valid)

{
  *(int *)(*(int *)((int)actor + 0xa4) + 0x1fc + shadowIdx * 0x54) = valid;
  return;
}

/* ---- 0x00493660  sputActor_AddShadowClipPlane ---- */
/* Shadow records are 0x54 bytes at extra+(idx+6)*0x54 with the plane equation at +8 Original name
   sputActor_AddShadowClipPlane (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_AddShadowPlane; 1 matched neighbours agree, 0 disagree); was Actor_AddShadowPlane. */

void __cdecl sputActor_AddShadowClipPlane(void *actor,int shadowIdx,char *sectorName)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  
  pvVar2 = WalkPlane_PlaneNamed(sectorName);
  if (pvVar2 != (void *)0x0) {
    iVar1 = *(int *)((int)actor + 0xa4) + (shadowIdx + 6) * 0x54;
    iVar3 = 0;
    piVar4 = (int *)(iVar1 + 0x24);
    while (*piVar4 != 0) {
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
      if (0xb < iVar3) {
        return;
      }
    }
    *(void **)(iVar1 + 0x24 + iVar3 * 4) = pvVar2;
  }
  return;
}

/* ---- 0x004936b0  sputActor_ResetShadows ---- */
/* Original name sputActor_ResetShadows (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_KillActorShadows; 1 matched neighbours agree, 0 disagree); was Actor_KillShadows.
    */

void __cdecl sputActor_ResetShadows(void *actor)

{
  int iVar1;
  undefined4 *puVar2;
  
  if ((actor != (void *)0x0) && (*(int *)((int)actor + 0xa4) != 0)) {
    puVar2 = (undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1f8);
    for (iVar1 = 0x7e; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
  }
  return;
}

/* ---- 0x004936e0  sputCostume_DrawActorShadow ---- */
/* Draws the shadows of an actor: slots at extra+0x1f8, 0x54 bytes each (+0 active, +4 valid,
   +8..+0x14 plane normal and d, +0x18..0x20 shadow point). valid 0: always; -1: only when pos.n+d
   <= 0; 1: only when >= 0 (pos = actor+0xc). Set by SetActorShadowPlane (Actor_SetShadowPlane
   0x493570, which resets valid to 0) and SetActorShadowValid (Lua_SetActorShadowValid 0x4a1fd0 ->
   0x493630). Original name sputCostume_DrawActorShadow (the remaster's GrimFandango (Linux): the
   only unmatched caller of Actor_DrawShadowPlane; 1 matched neighbours agree, 0 disagree); was
   Actor_DrawShadows. */

void sputCostume_DrawActorShadow(int param_1)

{
  int iVar1;
  float fVar2;
  int *shadow;
  int iVar3;
  
  if (*(int *)(param_1 + 0xa4) != 0) {
    Profile_Begin(0xb);
    iVar3 = 0x1f8;
    do {
      shadow = (int *)(*(int *)(param_1 + 0xa4) + iVar3);
      if ((*shadow != 0) &&
         ((iVar1 = shadow[1], iVar1 == 0 ||
          (((fVar2 = *(float *)(param_1 + 0x10) * PUN(float,shadow[3]) +
                     *(float *)(param_1 + 0x14) * PUN(float,shadow[4]) +
                     *(float *)(param_1 + 0xc) * PUN(float,shadow[2]) + PUN(float,shadow[5]), iVar1 != -1 ||
            (fVar2 <= 0.0)) && ((iVar1 != 1 || (0.0 <= fVar2)))))))) {
        Actor_DrawShadowPlane(*(void **)(param_1 + 0xa0),shadow);
      }
      iVar3 = iVar3 + 0x54;
    } while (iVar3 < 0x3f0);
    Profile_End(0xb);
  }
  return;
}

/* ---- 0x00493790  Actor_GetFrame ---- */
/* Returns the actor's 12-float frame (position + 3x3 rotation), rebuilding it from pos/rot when
   dirty */

float * __cdecl Actor_GetFrame(void *actor)

{
  if (*(int *)((int)actor + 0x34) == 0) {
    Angles_ToMatrix((int)actor + 0x38,(int)actor + 0x24,(int)actor + 0xc);
    *(undefined4 *)((int)actor + 0x34) = 1;
  }
  return (float *)((int)actor + 0x38);
}

/* ---- 0x004937c0  sputActor_DrawToClean ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua ActorToClean: marks the actor's rectangle to be restored from the clean background Original
   name sputActor_DrawToClean (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_ActorToClean; 3 matched neighbours agree, 0 disagree); was Actor_ToClean. */

void __cdecl sputActor_DrawToClean(void *actor)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  void *pvVar6;
  undefined4 uVar7;
  code *pcVar8;
  float *pfVar9;
  int *piVar10;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x20 - 0xc)))
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  pvVar6 = sputRoom_GetCurrentRoom();
  iVar2 = *(int *)((int)pvVar6 + 0xb4);
  pvVar6 = sputRoom_GetCurrentRoom();
  iVar1 = *(int *)((int)pvVar6 + 0xac) + iVar2 * 300;
  iVar2 = *(int *)(*(int *)(*(int *)((int)pvVar6 + 0xac) + 0x48 + iVar2 * 300) + 4);
  if (iVar2 != 0) {
    uVar3 = *(undefined4 *)(iVar2 + 0x10);
    uVar4 = *(undefined4 *)(iVar2 + 4);
    uVar7 = Render_GetBackgroundSurface();
    *(undefined4 *)(*(int *)(*(int *)(iVar1 + 0x48) + 4) + 4) = uVar7;
    uVar7 = Render_GetZBufferSurface();
    *(undefined4 *)(*(int *)(*(int *)(iVar1 + 0x48) + 4) + 0x10) = uVar7;
    piVar10 = *(int **)actor;
    iVar2 = *piVar10;
    if (iVar2 == 0) {
      pvVar6 = sputRoom_GetCurrentRoom();
      iVar2 = *(int *)((int)pvVar6 + 0x88);
      pvVar6 = sputRoom_GetCurrentRoom();
      iVar5 = *(int *)((int)pvVar6 + 0x80);
      if (*(int *)(iVar5 + iVar2 * 0x34) == 0) {
        (*g_pStd_HS->pAssertFail)
                  (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
      }
      rdroid_SetColormap(*(undefined4 *)(iVar5 + iVar2 * 0x34 + 4));
      pvVar6 = sputRoom_GetCurrentRoom();
      iVar2 = *(int *)((int)pvVar6 + 0x88);
      pvVar6 = sputRoom_GetCurrentRoom();
      piVar10 = (int *)(*(int *)((int)pvVar6 + 0x80) + iVar2 * 0x34);
      if (*piVar10 == 0) {
        (*g_pStd_HS->pAssertFail)
                  (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
      }
      iVar2 = piVar10[1];
    }
    else {
      if (iVar2 == 0) {
        (*g_pStd_HS->pAssertFail)
                  (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
      }
      rdroid_SetColormap(piVar10[1]);
      piVar10 = *(int **)actor;
      if (*piVar10 == 0) {
        (*g_pStd_HS->pAssertFail)
                  (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
      }
      iVar2 = piVar10[1];
    }
    pcVar8 = (code *)((code *)Render_GetUserCallback)(iVar2 + 0x30,0);
    (*pcVar8)();
    iVar2 = *(int *)((int)actor + 0x30);
    if (iVar2 != 0x3f800000) {
      piVar10 = &iStack_c;
      iStack_c = iVar2;
      iStack_8 = iVar2;
      iStack_4 = iVar2;
      pfVar9 = Actor_GetFrame(actor);
      Matrix_BuildTransform2(pfVar9,piVar10);
    }
    pfVar9 = Actor_GetFrame(actor);
    Actor_DrawCostumes(*(undefined4 *)((int)actor + 0xa0),pfVar9);
    *(undefined4 *)((int)actor + 0x34) = 0;
    rdCache_Flush();
    *(undefined4 *)(*(int *)(*(int *)(iVar1 + 0x48) + 4) + 4) = uVar4;
    *(undefined4 *)(*(int *)(*(int *)(iVar1 + 0x48) + 4) + 0x10) = uVar3;
  }
  return;
}
#undef iStack_4
#undef iStack_8
#undef iStack_c
#undef local_10

#endif


/* ---- 0x00494690  Actor_CountCostumes ---- */
int Actor_CountCostumes(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  for (iVar1 = *(int *)(param_1 + 0xa0); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xb0)) {
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}

/* ---- 0x004946b0  sputActor_SetClipPlane ---- */
/* Original name sputActor_SetClipPlane (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetActorClipPlane; 1 matched neighbours agree, 1 disagree); was Actor_SetClipPlane.
    */

void sputActor_SetClipPlane(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xa4) == 0) {
    sputActor_AllocateActorExtra(param_1);
  }
  iVar1 = *(int *)(param_1 + 0xa4);
  *(undefined4 *)(iVar1 + 0x400) = *param_2;
  *(undefined4 *)(iVar1 + 0x404) = param_2[1];
  *(undefined4 *)(iVar1 + 0x408) = param_2[2];
  iVar1 = *(int *)(param_1 + 0xa4);
  *(undefined4 *)(iVar1 + 0x40c) = *param_3;
  *(undefined4 *)(iVar1 + 0x410) = param_3[1];
  *(undefined4 *)(iVar1 + 0x414) = param_3[2];
  return;
}

/* ---- 0x00494710  Actor_SetClipActive ---- */
void Actor_SetClipActive(int param_1,undefined4 param_2)

{
  if (*(int *)(param_1 + 0xa4) == 0) {
    sputActor_AllocateActorExtra(param_1);
  }
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x3fc) = param_2;
  return;
}

/* ---- 0x00494780  Actor_SetFrustumCull ---- */
void Actor_SetFrustumCull(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  if (param_1 != 0) {
    if (param_2 == 0) {
      uVar2 = *(uint *)(param_1 + 4) & 0xfffffffb;
    }
    else {
      uVar2 = *(uint *)(param_1 + 4) | 4;
    }
    *(uint *)(param_1 + 4) = uVar2;
    if (*(int *)(param_1 + 0xa0) != 0) {
      for (iVar1 = *(int *)(*(int *)(param_1 + 0xa0) + 8); iVar1 != 0; iVar1 = *(int *)(iVar1 + 400)
          ) {
        *(int *)(*(int *)(iVar1 + 0x40) + 0x44) = param_2;
      }
    }
  }
  return;
}

/* ---- 0x004947c0  Actor_Destroy ---- */
/* Removes the actor from its set, kills shadows, frees costumes, walker, extra and colormap
   reference */

void __cdecl Actor_Destroy(void *actor)

{
  void *p;
  
  if (*(char *)((int)actor + 0x7c) != '\0') {
    Actor_RemoveFromSet((char *)((int)actor + 0x7c),actor);
  }
  sputActor_ResetShadows(actor);
  Costume_FreeList(*(void **)((int)actor + 0xa0),0);
  *(undefined4 *)((int)actor + 0xa0) = 0;
  if (*(int *)((int)actor + 0xa4) != 0) {
    p = *(void **)(*(int *)((int)actor + 0xa4) + 0x1b4);
    if (p != (void *)0x0) {
      Walker_Destroy((int)p);
      Plat_Free(p);
      *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1b4) = 0;
    }
    (**(code **)(g_dwSputActHS + 0x24))(*(undefined4 *)((int)actor + 0xa4));
    *(undefined4 *)((int)actor + 0xa4) = 0;
  }
  if (*(void **)actor != (void *)0x0) {
    Res_RemoveReference(*(void **)actor);
    (**(code **)(g_dwSputActHS + 0x24))(*(undefined4 *)actor);
    *(undefined4 *)actor = 0;
  }
  *(undefined4 *)((int)actor + 0x9c) = 0;
  g_nNumActors = g_nNumActors + -1;
  return;
}

/* ---- 0x00494940  Actor_DrawShadowPlane ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Draws the actor's shadow onto one shadow plane: every mesh face of each model is projected
   through the plane, clipped to each of the plane's sectors and drawn with shadow.mat / shadow.cmp
    */

void Actor_DrawShadowPlane(void *costumeList,void *shadow)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *out;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar8;
  #define local_fc (*(float (*)[2])(_frame + (0x110 - 0xfc)))
  #define local_f4 (*(uint *)(_frame + (0x110 - 0xf4)))
  #define local_f0 (*(uint *)(_frame + (0x110 - 0xf0)))
  #define local_ec (*(uint *)(_frame + (0x110 - 0xec)))
  #define local_e8 (*(uint *)(_frame + (0x110 - 0xe8)))
  #define local_e4 (*(float (*)[3])(_frame + (0x110 - 0xe4)))
  #define local_d8 (*(uint *)(_frame + (0x110 - 0xd8)))
  #define local_d4 (*(uint *)(_frame + (0x110 - 0xd4)))
  #define local_d0 (*(uint *)(_frame + (0x110 - 0xd0)))
  #define local_cc (*(uint *)(_frame + (0x110 - 0xcc)))
  #define local_c8 (*(uint *)(_frame + (0x110 - 0xc8)))
  #define local_c4 (*(uint *)(_frame + (0x110 - 0xc4)))
  #define local_c0 (*(float (*)[12])(_frame + (0x110 - 0xc0)))
  #define local_90 (*(float (*)[12])(_frame + (0x110 - 0x90)))
  #define local_60 (*(float (*)[12])(_frame + (0x110 - 0x60)))
  #define local_30 (*(float (*)[12])(_frame + (0x110 - 0x30)))
  
  if (costumeList != (void *)0x0) {
    iVar1 = *(int *)((int)costumeList + 8);
    local_fc[0] = 640.0;
    local_fc[1] = 480.0;
    local_e4[0] = 0.0;
    local_e4[2] = 0.0;
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 400)) {
      iVar2 = *(int *)(iVar1 + 0x40);
      iVar3 = *(int *)(iVar2 + 4);
      if (((*(int *)(iVar1 + 0x38) != 0) && (*(int *)(iVar1 + 0x34) == 0)) &&
         (local_d8 = 0, 0 < *(int *)(iVar3 + 0x54))) {
        local_f4 = 0;
        local_ec = 0;
        do {
          iVar4 = *(int *)(local_ec + 0x4c + *(int *)(iVar3 + 0x58));
          if (((iVar4 != -1) &&
              (iVar5 = *(int *)(iVar3 + 0x28), *(int *)(iVar5 + 0x54 + iVar4 * 0x7c) != 0)) &&
             (*(int *)(*(int *)(iVar2 + 0x2c) + iVar4 * 4) != 0)) {
            iVar7 = 0;
            do {
              out = (float *)((int)local_c0 + iVar7);
              Matrix34_TransformPoint
                        (out,(float *)(iVar7 + *(int *)(iVar5 + iVar4 * 0x7c + 0x58)),
                         (float *)(local_f4 + *(int *)(iVar2 + 0x20)));
              iVar6 = Plane_IntersectSegment
                                (out,(float *)((int)shadow + 0x18),out,*(float *)((int)shadow + 8),
                                 *(float *)((int)shadow + 0xc),*(float *)((int)shadow + 0x10),
                                 *(float *)((int)shadow + 0x14));
              if (iVar6 == 0) {
                return;
              }
              iVar7 = iVar7 + 0xc;
            } while (iVar7 < 0xc0);
            if (g_pShadowMaterial == (void *)0x0) {
              g_pShadowMaterial = rdMaterial_Load(s_shadow_mat_004ea19c,0,0);
            }
            if (g_pShadowColormap == (void *)0x0) {
              g_pShadowColormap = rdColormap_Load(s_shadow_cmp_004ea190);
            }
            if (g_pShadowMaterial != (void *)0x0) {
              rdroid_SetColormap(g_pShadowColormap);
              if (g_nSputRender_b3DAcceleration != 0) {
                std3D_SetCurrentPalette((void *)((int)g_pShadowColormap + 0x30),0);
              }
              Shadow_DrawClippedPoly(local_c0,4,local_fc,local_e4,shadow);
              Shadow_DrawClippedPoly(local_90,4,local_fc,local_e4,shadow);
              Shadow_DrawClippedPoly(local_60,4,local_fc,local_e4,shadow);
              Shadow_DrawClippedPoly(local_30,4,local_fc,local_e4,shadow);
            }
          }
          local_d8 = local_d8 + 1;
          local_ec = local_ec + 0xb8;
          local_f4 = local_f4 + 0x30;
        } while ((int)local_d8 < *(int *)(iVar3 + 0x54));
      }
    }
    if (local_fc[0] <= local_e4[0]) {
      lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      local_d0 = (uint)lVar8;
      lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      local_cc = (uint)lVar8;
      lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      local_c8 = (uint)lVar8;
      lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      local_c4 = (uint)lVar8;
      Render_InvalidateRectLastBuffer((int *)&local_d0,1);
    }
  }
  return;
}
#undef local_30
#undef local_60
#undef local_90
#undef local_c0
#undef local_c4
#undef local_c8
#undef local_cc
#undef local_d0
#undef local_d4
#undef local_d8
#undef local_e4
#undef local_e8
#undef local_ec
#undef local_f0
#undef local_f4
#undef local_fc

#endif


/* ---- 0x00495080  Actor_DrawCostumes ---- */
void Actor_DrawCostumes(undefined4 param_1,undefined4 param_2)

{
  ((code *)Actor_DrawCostumeMeshes)(param_1,param_2,0,0);
  return;
}

/* ---- 0x004950a0  Actor_DrawCostumeMeshes ---- */
/* Draws the meshes of an actor's costume. Enables the user clip plane when extra+0x3fc != 0 (normal
   extra+0x400, point extra+0x40c). For a model hung on a node (component+0x44 != 0) whose node
   index (+0x48) equals extra+0x420 (SetActorInvClipNode) the plane through the actor position
   (actor+0xc) with the second row of the actor matrix (actor+0x44..0x4c, the facing) as normal is
   used for that mesh only, then the clip is switched off. Meshes are clipped per polygon in eye
   space (MeshFace_Draw 0x40d880 -> Polygon_ClipToPlane 0x44ea50: keep dist >= 0); Mesh_Draw
   0x40d230 skips a mesh whose centre is more than its radius behind the plane. */

void Actor_DrawCostumeMeshes(int *param_1,float *param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  void *pvVar6;
  int iVar7;
  int iVar8;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define uStack_1c (*(undefined4 *)(_frame + (0x30 - 0x1c)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define iStack_10 (*(int *)(_frame + (0x30 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x30 - 0xc)))
  #define iStack_8 (*(int *)(_frame + (0x30 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x30 - 0x4)))
  
  iVar5 = param_1[1];
  for (piVar1 = param_1; (piVar1 != (int *)0x0 && (piVar1[1] == iVar5));
      piVar1 = (int *)piVar1[0x2c]) {
    Costume_ApplyComponentState((void *)*piVar1);
  }
  iVar5 = Cos_InstGetUserData(*param_1);
  piVar1 = (int *)((int)g_pActors + iVar5 * 0xa8);
  if ((piVar1[0x29] == 0) || (*(int *)(piVar1[0x29] + 0x3fc) == 0)) {
    Renderer_EnableClipPlane(0);
  }
  else {
    Renderer_EnableClipPlane(1);
    Renderer_SetClipPlane(piVar1[0x29] + 0x400,piVar1[0x29] + 0x40c);
  }
  Costume_ApplyScale(piVar1,(void *)param_1[2]);
  iVar5 = param_1[2];
  do {
    if (iVar5 == 0) {
      sputCostume_DrawActorShadow(piVar1);
      iVar5 = param_1[1];
      for (piVar4 = param_1; (piVar4 != (int *)0x0 && (piVar4[1] == iVar5));
          piVar4 = (int *)piVar4[0x2c]) {
        Costume_ApplyComponentState((void *)*piVar4);
      }
      Costume_ApplyScale(piVar1,(void *)param_1[2]);
      return;
    }
    if (*(int *)(iVar5 + 0x38) != 0) {
      g_nDrawBoxMinX = 0x280;
      g_nDrawBoxMinY = 0x1e0;
      g_nDrawBoxMaxX = 0;
      g_nDrawBoxMaxY = 0;
      iVar7 = iVar5;
      if (*(int *)(iVar5 + 0x44) == 0) {
        if (*(int *)(iVar5 + 0x4c) == 0) {
LAB_004951ab:
          if (g_nSputRender_b3DAcceleration == 0) goto LAB_004951b3;
        }
        else {
          rdroid_SetColormap(*(int *)(iVar5 + 0x4c));
          if (g_nSputRender_b3DAcceleration != 0) {
            std3D_SetCurrentPalette((void *)(*(int *)(iVar5 + 0x4c) + 0x30),0);
            goto LAB_004951ab;
          }
LAB_004951b3:
          pvVar6 = (void *)Render_GetBackBuffer();
          Surface_Lock(pvVar6);
        }
        iVar7 = rdThing_DrawAlt(*(void **)(iVar5 + 0x40),param_2);
        if ((iVar7 == 0) || (piVar1 == (int *)0x0)) {
          piVar1[0x1a] = 0;
        }
        else {
          piVar1[0x1a] = 1;
        }
        if (g_nSputRender_b3DAcceleration == 0) {
          pvVar6 = (void *)Render_GetBackBuffer();
          Surface_Unlock(pvVar6);
        }
      }
      else {
        for (; (iVar7 != 0 && (*(int *)(iVar7 + 0x4c) == 0)); iVar7 = *(int *)(iVar7 + 0x44)) {
        }
        if (((iVar7 != 0) && (*(int *)(iVar7 + 0x4c) != 0)) &&
           (rdroid_SetColormap(*(int *)(iVar7 + 0x4c)), g_nSputRender_b3DAcceleration != 0)) {
          std3D_SetCurrentPalette((void *)(*(int *)(iVar7 + 0x4c) + 0x30),0);
        }
        Costume_UpdateAttachedFrame(*(void **)(iVar5 + 0x44),param_2);
        iVar8 = *(int *)(*(int *)(iVar5 + 0x44) + 0x40);
        iVar7 = *(int *)(*(int *)(iVar8 + 4) + 0x58) + *(int *)(iVar5 + 0x48) * 0xb8;
        iVar2 = *(int *)(*(int *)(*(int *)(iVar5 + 0x40) + 4) + 0x58);
        if (g_nSputRender_b3DAcceleration == 0) {
          pvVar6 = (void *)Render_GetBackBuffer();
          Surface_Lock(pvVar6);
        }
        if ((*(int *)(iVar5 + 0x3c) != 0) && (**(int **)(iVar5 + 0x40) != 4)) {
          iVar3 = (*(int **)(iVar5 + 0x40))[1];
          uStack_1c = *(undefined4 *)(iVar3 + 0x84);
          uStack_18 = *(undefined4 *)(iVar3 + 0x88);
          uStack_14 = *(undefined4 *)(iVar3 + 0x8c);
          *(undefined4 *)(iVar3 + 0x84) = 0;
          *(undefined4 *)(iVar3 + 0x88) = 0;
          *(undefined4 *)(iVar3 + 0x8c) = 0;
          *(float *)(iVar2 + 100) = *(float *)(iVar2 + 100) - *(float *)(iVar7 + 100);
          *(float *)(iVar2 + 0x68) = *(float *)(iVar2 + 0x68) - *(float *)(iVar7 + 0x68);
          *(float *)(iVar2 + 0x6c) = *(float *)(iVar2 + 0x6c) - *(float *)(iVar7 + 0x6c);
        }
        piVar1[0x1a] = 0;
        if ((piVar1[0x29] != 0) && (*(int *)(piVar1[0x29] + 0x420) == *(int *)(iVar5 + 0x48))) {
          Renderer_EnableClipPlane(1);
          Renderer_SetClipPlane(piVar1 + 0x11,piVar1 + 3);
        }
        iVar8 = rdThing_DrawAlt(*(void **)(iVar5 + 0x40),
                                (float *)(*(int *)(iVar8 + 0x20) + *(int *)(iVar5 + 0x48) * 0x30));
        if ((iVar8 != 0) && (piVar1 != (int *)0x0)) {
          piVar1[0x1a] = 1;
        }
        if ((piVar1[0x29] != 0) && (*(int *)(piVar1[0x29] + 0x420) == *(int *)(iVar5 + 0x48))) {
          Renderer_EnableClipPlane(0);
        }
        if ((*(int *)(iVar5 + 0x3c) != 0) && (**(int **)(iVar5 + 0x40) != 4)) {
          *(float *)(iVar2 + 100) = *(float *)(iVar7 + 100) + *(float *)(iVar2 + 100);
          *(float *)(iVar2 + 0x68) = *(float *)(iVar7 + 0x68) + *(float *)(iVar2 + 0x68);
          *(float *)(iVar2 + 0x6c) = *(float *)(iVar7 + 0x6c) + *(float *)(iVar2 + 0x6c);
          iVar7 = *(int *)(*(int *)(iVar5 + 0x40) + 4);
          *(undefined4 *)(iVar7 + 0x84) = uStack_1c;
          *(undefined4 *)(iVar7 + 0x88) = uStack_18;
          *(undefined4 *)(iVar7 + 0x8c) = uStack_14;
        }
        if (g_nSputRender_b3DAcceleration == 0) {
          pvVar6 = (void *)Render_GetBackBuffer();
          Surface_Unlock(pvVar6);
        }
      }
      piVar4 = (int *)*piVar1;
      iVar7 = *piVar4;
      if (iVar7 != 0) {
        if (iVar7 == 0) {
          (*g_pStd_HS->pAssertFail)
                    (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
        }
        rdroid_SetColormap(piVar4[1]);
        if (g_nSputRender_b3DAcceleration != 0) {
          piVar4 = (int *)*piVar1;
          if (*piVar4 == 0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
          }
          std3D_SetCurrentPalette((void *)(piVar4[1] + 0x30),0);
        }
      }
      iStack_10 = g_nDrawBoxMinX;
      iStack_8 = g_nDrawBoxMaxX - g_nDrawBoxMinX;
      iStack_c = g_nDrawBoxMinY;
      iStack_4 = g_nDrawBoxMaxY - g_nDrawBoxMinY;
      Render_InvalidateRectLastBuffer(&iStack_10,1);
      if ((*(int *)(iVar5 + 0x40) == param_1[1]) && (piVar1 != (int *)0x0)) {
        piVar1[0x1b] = iStack_10;
        piVar1[0x1c] = iStack_c;
        piVar1[0x1d] = iStack_8;
        piVar1[0x1e] = iStack_4;
      }
    }
    iVar5 = *(int *)(iVar5 + 400);
  } while( true );
}
#undef iStack_10
#undef iStack_4
#undef iStack_8
#undef iStack_c
#undef local_20
#undef uStack_14
#undef uStack_18
#undef uStack_1c


/* ---- 0x004a5eb0  Actor_RemoveFromSet ---- */
void __cdecl Actor_RemoveFromSet(char *setName,void *actor)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = Set_FindNameInList(setName);
  if (iVar2 != 0) {
    *(undefined4 *)((int)actor + 0x68) = 0;
    piVar3 = *(int **)(iVar2 + 0x80);
    if (piVar3 != (int *)0x0) {
      do {
        if ((void *)((int)g_pActors + *piVar3 * 0xa8) == actor) break;
        piVar3 = (int *)piVar3[2];
      } while (piVar3 != (int *)0x0);
      if (piVar3 != (int *)0x0) {
        if ((*(int *)((int)actor + 0xa4) != 0) &&
           (iVar1 = *(int *)(*(int *)((int)actor + 0xa4) + 0x1b4), iVar1 != 0)) {
          *(undefined4 *)(iVar1 + 0x5c) = 0;
        }
        if (piVar3[2] != 0) {
          *(int *)(piVar3[2] + 4) = piVar3[1];
        }
        if (piVar3[1] != 0) {
          *(int *)(piVar3[1] + 8) = piVar3[2];
        }
        if (*(int **)(iVar2 + 0x80) == piVar3) {
          *(int *)(iVar2 + 0x80) = piVar3[2];
        }
        (*g_pSputRoomHS->pFree)(piVar3);
        *(undefined1 *)((int)actor + 0x7c) = 0;
      }
    }
  }
  return;
}

/* ---- 0x004a5f60  Actor_PutInSet ---- */
/* sputRoom.cpp: moves the actor into the named set's actor list (actor+0x7c holds the set name) */

void __cdecl Actor_PutInSet(void *actor,char *setName)

{
  char *setName_00;
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  void *pvVar4;
  int *piVar5;
  byte *pbVar6;
  bool bVar7;
  
  if ((actor != (void *)0x0) &&
     (pbVar6 = (byte *)(setName + 0x7c), pbVar2 = actor, pbVar6 != (byte *)0x0)) {
    do {
      bVar1 = *pbVar2;
      bVar7 = bVar1 < *pbVar6;
      if (bVar1 != *pbVar6) {
LAB_004a5fa1:
        iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_004a5fa6;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar7 = bVar1 < pbVar6[1];
      if (bVar1 != pbVar6[1]) goto LAB_004a5fa1;
      pbVar6 = pbVar6 + 2;
      pbVar2 = pbVar2 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_004a5fa6:
    if (iVar3 == 0) {
      return;
    }
  }
  setName_00 = setName + 0x7c;
  if ((setName_00 != (char *)0x0) || (actor != (void *)0x0)) {
    if ((setName != (char *)0x0) && (setName_00 != (char *)0x0)) {
      Actor_RemoveFromSet(setName_00,setName);
    }
    if (actor == (void *)0x0) {
      setName[0x68] = '\0';
      setName[0x69] = '\0';
      setName[0x6a] = '\0';
      setName[0x6b] = '\0';
      return;
    }
    pvVar4 = (void *)Set_FindNameInList(actor);
    if (pvVar4 == (void *)0x0) {
      pvVar4 = Set_NormalizeName(actor);
    }
    for (piVar5 = *(int **)((int)pvVar4 + 0x80); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[2]) {
      if ((char *)((int)g_pActors + *piVar5 * 0xa8) == setName) {
        return;
      }
    }
    piVar5 = (int *)(*g_pSputRoomHS->pAlloc)(0xc,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0xa09);
    *piVar5 = 0;
    piVar5[1] = 0;
    piVar5[2] = 0;
    *piVar5 = ((int)setName - (int)g_pActors) / 0xa8;
    iVar3 = *(int *)((int)pvVar4 + 0x80);
    piVar5[2] = iVar3;
    if (iVar3 != 0) {
      *(int **)(iVar3 + 4) = piVar5;
    }
    *(int **)((int)pvVar4 + 0x80) = piVar5;
    if (setName != (char *)0x0) {
      strncpy(setName_00,actor,0x20);
    }
  }
  return;
}

/* ---- 0x004a8500  Puck_GetYawToPoint ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name Puck_GetYawToPoint (the remaster's GrimFandango (Linux): Puck::GetYawToPoint in the
   remaster (a C++ method there); the only unmatched callee of Lua_GetActorYawToPoint; 3 matched
   neighbours agree, 0 disagree); was Actor_GetYawToPoint. */

float __thiscall Puck_GetYawToPoint(void *this,float *point)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined *puVar1;
  float fVar2;
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  local_18 = *point;
  local_14 = point[1];
  local_10 = PUN(uint,(float)point[2]);
  if (*(void **)((int)this + 0x5c) != (void *)0x0) {
    Sector_FixPlaneCoordinate(*(void **)((int)this + 0x5c),(int)&local_18);
  }
  Walker_ToLocalSpace(this,&local_18);
  rdVector_Normalize3Acc(&local_18);
  fVar2 = stdMath_ArcSin3(local_14);
  point = PUN(float *,(float)(90.0 - fVar2));
  if (0.0 < local_18) {
    point = PUN(float *,(float)(PUN(float,point) * -1.0));
  }
  puVar1 = Walker_GetAngles((int)this);
  return *(float *)(puVar1 + 4) + PUN(float,point);
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c

#endif

