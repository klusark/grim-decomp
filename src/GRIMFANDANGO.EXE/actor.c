/* GRIMFANDANGO.EXE :: actor.c
 * functions 0x00485290 .. 0x004a8500 (57 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00485290  Actor_ComputeScreenBox ---- */
/* Projects the actor's model through its frame and stores the covering screen rectangle at
   actor+0x6c (valid flag at +0x68) */

void __cdecl Actor_ComputeScreenBox(Actor *actor)

{
  int iVar1;
  float *frame;
  int iVar2;
  
  g_nRdCache_ulcExtent = UINT_009055ec;
  g_nDrawBoxMinY = *(int *)(UINT_008c97a0 + 0x10);
  g_nRdCache_lrcExtent = 0;
  g_nDrawBoxMaxY = 0;
  actor->aScreenBox[0] = 0;
  actor->aScreenBox[1] = 0;
  actor->aScreenBox[2] = 0;
  actor->aScreenBox[3] = 0;
  frame = sputActor_GetOrientMatrix(actor);
  iVar2 = rdThing_Draw(actor->pCostumes->pMainModel,frame);
  if (iVar2 != 0) {
    actor->nScreenBoxValid = 1;
    iVar2 = g_nRdCache_ulcExtent;
    actor->aScreenBox[0] = g_nRdCache_ulcExtent;
    iVar1 = g_nDrawBoxMinY;
    actor->aScreenBox[1] = g_nDrawBoxMinY;
    actor->aScreenBox[2] = g_nRdCache_lrcExtent - iVar2;
    actor->aScreenBox[3] = g_nDrawBoxMaxY - iVar1;
  }
  return;
}

/* ---- 0x00485320  Actor_DrawDebugWalker ---- */
/* WARNING: Variable defined which should be unmapped: local_28 */
/* Debug overlay: the walker's path segments, its sector outline and the look-at circle */

void __cdecl Actor_DrawDebugWalker(Actor *actor)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Puck *this;
  ActorExtra *pAVar1;
  float *b;
  int iVar2;
  int iVar3;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  if (actor->pExtra != (ActorExtra *)0x0) {
    this = actor->pExtra->pPuck;
    if (this != (Puck *)0x0) {
      Puck_Draw(this,UINT_008c97e0 & 0xffff);
    }
    if ((actor->dwMoveFlags & 1) != 0) {
      pAVar1 = actor->pExtra;
      iVar3 = 0;
      if (pAVar1->nPathNodes != 1 && -1 < pAVar1->nPathNodes + -1) {
        iVar2 = 0x48;
        do {
          rdPrimit3_DrawLine((float *)((int)pAVar1->aLookAt + iVar2),
                             (float *)((int)pAVar1->aLookAt + iVar2 + 0xc),(int *)0x0,(int *)0x0,
                             (int *)0x0,(int *)0x0,UINT_008c97d4 & 0xffff,0xffffffff);
          pAVar1 = actor->pExtra;
          iVar3 = iVar3 + 1;
          iVar2 = iVar2 + 0xc;
        } while (iVar3 < pAVar1->nPathNodes + -1);
      }
    }
    if (actor->pExtra->nCollided != 0) {
      iVar3 = *(int *)((int)actor->pCostumes->pMainModel + 4);
      b = sputActor_GetOrientMatrix(actor);
      rdMatrix_TransformPoint34(local_c,(float *)(iVar3 + 0x78),b);
      rdPrimit3_DrawPoint(local_c,*(float *)(iVar3 + 0x5c) * actor->pExtra->flCollisionScale,
                          0x41200000,0xffff,0xffffffff);
    }
  }
  return;
}
#undef local_28
#undef local_c


/* ---- 0x0048b2e0  sputText_CreateActorText ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Creates the speech text object above the actor (projected head position when on screen), clamped
   to the screen edges Original name sputText_CreateActorText (the remaster's GrimFandango (Linux):
   aligned call in sputActor_SayLine); was Actor_CreateSubtitle. */

TextObject * __cdecl sputText_CreateActorText(Actor *actor,char *text,int x,int y)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Actor *pAVar1;
  Actor *pAVar2;
  char *pcVar3;
  TextObject *pTVar4;
  int iVar5;
  int unaff_ESI;
  TextContext *pTVar6;
  int unaff_EDI;
  undefined4 *puVar7;
  #define local_5c (*(float (*)[2])(_frame + (0x70 - 0x5c)))
  #define local_50 (*(float (*)[3])(_frame + (0x70 - 0x50)))
  #define local_44 (*(uint *)(_frame + (0x70 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x70 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x70 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x70 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x70 - 0x34)))
  #define local_2c (*(uint *)(_frame + (0x70 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x70 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x70 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x70 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x70 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x70 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x70 - 0x14)))
  
  pAVar1 = actor;
  local_38 = UINT_008a94bc;
  local_50[0] = PUN(float,g_nSubtitleDefaultX);
  local_50[2] = (float)UINT_004e8490;
  local_34 = UINT_008a94c0;
  pTVar6 = &g_SubtitleTextCtx;
  puVar7 = (undefined4 *)(_frame + (0x70 - 0x30));
  for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = pTVar6->pUnused;
    pTVar6 = (TextContext *)&pTVar6->pClipRect;
    puVar7 = puVar7 + 1;
  }
  local_50[1] = PUN(float,g_nSubtitleDefaultY);
  local_2c = (uint)&local_40;
  local_40 = 0;
  local_3c = 0;
  local_1c = actor->pExtra->dwTalkColor;
  local_18 = 0;
  local_14 = 0;
  if ((actor->nScreenBoxValid == 0) || (g_dwGrimlib_mode == 3)) {
    pAVar2 = (Actor *)local_50;
    if ((actor->pCostumes == (CostumeNode *)0x0) || ((actor->dwFlags & 2) != 0)) {
      pcVar3 = sputRoom_GetCurrentRoomName();
      iVar5 = _stricmp(actor->aSetName,pcVar3);
      if (iVar5 == 0) {
        iVar5 = rdPrimit3_GetScreenCoord(actor->aPos,local_5c);
        if (iVar5 != 0) {
          local_50[0] = local_5c[0];
          local_50[1] = local_5c[1];
        }
      }
    }
  }
  else {
    pAVar2 = (Actor *)actor->aScreenBox;
  }
  actor = pAVar2;
  iVar5 = Text_GetStringWidth((TextContext *)(_frame + (0x70 - 0x30)),text);
  iVar5 = iVar5 / 2;
  if (x == -1) {
    x = (int)actor->dwMoveFlags / 2 + (int)actor->pColormapRef;
  }
  if (x - iVar5 < 0x28) {
    x = iVar5 + 0x28;
  }
  if ((int)(UINT_008a94bc - 0x28) < iVar5 + x) {
    x = (UINT_008a94bc - iVar5) - 0x28;
  }
  local_20 = *(uint *)(*(int *)local_28 + 8);
  local_24 = x;
  iVar5 = Text_GetStringHeight((TextContext *)(_frame + (0x70 - 0x30)),text);
  if (y == -1) {
    y = actor->dwFlags - iVar5;
  }
  if (y < 10) {
    y = 10;
  }
  if ((int)(UINT_008a94c0 - 10) < y + iVar5) {
    y = (UINT_008a94c0 - iVar5) + -10;
  }
  local_20 = *(int *)(*(int *)local_28 + 8) + y;
  local_24 = x;
  pTVar4 = TextObject_New((TextContext *)(_frame + (0x70 - 0x30)),text,unaff_EDI,unaff_ESI);
  pTVar4->pActor = pAVar1;
  pAVar1->dwFlags = pAVar1->dwFlags | 4;
  return pTVar4;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
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

int __cdecl sputActor_SetCostume(Actor *actor,char *name,int param_3)

{
  void *costumeRes;
  CostumeNode *pCVar1;
  
  if ((name == (char *)0x0) || (param_3 != 0)) {
    costumeRes = (void *)0x0;
    pCVar1 = actor->pCostumes;
  }
  else {
    costumeRes = sputResource_Alloc(0x54534f43,name);
    if (costumeRes == (void *)0x0) {
      return 0;
    }
    param_3 = 0;
    pCVar1 = actor->pCostumes;
  }
  pCVar1 = sputCostume_SetCostume(pCVar1,costumeRes,param_3);
  actor->pCostumes = pCVar1;
  Cos_InstSetUserData(actor->pCostumes->dwInstance,((int)actor - (int)g_pActors) / 0xa8);
  sputActor_SetFrustrumCull(actor,~actor->dwFlags >> 2 & 1);
  return 1;
}

/* ---- 0x0048f9d0  sputActor_SetActorHead ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua SetActorHead: head-tracking joints and limits Original name sputActor_SetActorHead (the
   remaster's GrimFandango (Linux): aligned call in sputLua_SetActorHeadL); was Actor_SetHead. */

void __cdecl
sputActor_SetActorHead
          (void *actor,int joint1,int joint2,int joint3,float maxRoll,float maxPitch,float maxYaw)

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
      stdMath_SinCos(fVar3 * 0.5,(float *)&actor,(float *)(iVar1 + 0x24));
    }
  }
  return;
}
#undef local_14


/* ---- 0x0048fa60  sputActor_CanActorSeePoint ---- */
/* True when the point lies within the head joint's view cone (cosine threshold at costume+0x24 set
   by Actor_SetHead) Original name sputActor_CanActorSeePoint (the remaster's GrimFandango (Linux):
   same body (actor +0xa0 joint, normalised direction, the distance out-parameter), called from
   sputActor_CanActorSeeActor and sputLua_CanActorSeeL on both sides); was Actor_CanSeePoint. */

int __cdecl sputActor_CanActorSeePoint(Actor *actor,float *point,float *outDistance)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  CostumeNode *pCVar1;
  float fVar2;
  float *frame;
  float *pfVar3;
  float fVar4;
  uint index;
  #define local_48 (*(float (*)[3])(_frame + (0x60 - 0x48)))
  #define local_3c (*(float (*)[3])(_frame + (0x60 - 0x3c)))
  #define local_30 (*(float (*)[9])(_frame + (0x60 - 0x30)))
  #define local_c (*(float (*)[3])(_frame + (0x60 - 0xc)))
  
  pCVar1 = actor->pCostumes;
  if (((pCVar1 != (CostumeNode *)0x0) && (index = pCVar1->aHeadJoints[0], -1 < (int)index)) &&
     (pCVar1->pMainModel != (void *)0x0)) {
    pfVar3 = local_30;
    frame = sputActor_GetOrientMatrix(actor);
    rdPuppet_BuildJointMatrices(pCVar1->pMainModel,frame,index,pfVar3);
    local_3c[0] = *point - local_c[0];
    local_3c[1] = point[1] - local_c[1];
    local_3c[2] = point[2] - local_c[2];
    fVar4 = rdVector_Normalize3Acc(local_3c);
    local_48[0] = local_3c[0];
    *outDistance = fVar4;
    local_48[1] = local_3c[1];
    local_48[2] = 0.0;
    rdVector_Normalize3Acc(local_48);
    pfVar3 = sputActor_GetOrientMatrix(actor);
    fVar4 = pfVar3[3] * local_48[0];
    pfVar3 = sputActor_GetOrientMatrix(actor);
    fVar2 = pfVar3[4] * local_48[1];
    pfVar3 = sputActor_GetOrientMatrix(actor);
    if (pCVar1->flViewCos <= pfVar3[5] * local_48[2] + fVar2 + fVar4) {
      return 1;
    }
  }
  return 0;
}
#undef local_30
#undef local_3c
#undef local_48
#undef local_c


/* ---- 0x0048fb80  sputActor_CanActorSeeActor ---- */
/* Lua CanActorSee / GetVisibleThings line-of-sight test Original name sputActor_CanActorSeeActor
   (the remaster's GrimFandango (Linux): aligned call in sputLua_CanActorSeeL,
   sputLua_GetVisibleThingsL); was Actor_CanSee. */

int __cdecl sputActor_CanActorSeeActor(Actor *viewer,Actor *target,float *outDistance)

{
  int iVar1;
  float *pfVar2;
  
  if (target->aSetName[0] != '\0') {
    if (viewer->aSetName[0] != '\0') {
      iVar1 = _stricmp(target->aSetName,viewer->aSetName);
      if (iVar1 == 0) {
        pfVar2 = sputActor_GetOrientMatrix(target);
        iVar1 = sputActor_CanActorSeePoint(viewer,pfVar2 + 9,outDistance);
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

void __cdecl sputActor_Turn(Actor *actor,float param_2)

{
  float fVar1;
  ActorExtra *pAVar2;
  float fVar3;
  
  pAVar2 = actor->pExtra;
  fVar3 = sputTime_GetFrameTimeFlex();
  fVar3 = pAVar2->flTurnRate * fVar3 * pAVar2->flTimeScale * param_2;
  if (pAVar2->pPuck == (Puck *)0x0) {
    sputActor_EnablePuck(actor,1);
  }
  pAVar2 = actor->pExtra;
  fVar1 = pAVar2->flYawLeft;
  if (pAVar2->flYawLeft < 0.0) {
    fVar1 = -fVar1;
  }
  fVar3 = fVar3 + fVar3;
  if (fVar3 < 0.0) {
    fVar3 = -fVar3;
  }
  if (fVar1 <= fVar3) {
    if (0.0 < param_2) {
      pAVar2->nTurning = 1;
      return;
    }
    pAVar2->nTurning = -1;
  }
  return;
}

/* ---- 0x0048fc80  sputActor_Forward ---- */
/* Actor_WalkForward(actor): creates the walker if missing and sets extra+0xc (walk forward this
   frame), consumed by Actor_UpdateWalker. Original name sputActor_Forward (the remaster's
   GrimFandango (Linux): the only unmatched callee of Lua_WalkActorForward; 3 matched neighbours
   agree, 0 disagree); was Actor_WalkForward. */

void __cdecl sputActor_Forward(Actor *actor)

{
  sputTime_GetFrameTimeFlex();
  if (actor->pExtra->pPuck == (Puck *)0x0) {
    sputActor_EnablePuck(actor,1);
  }
  actor->pExtra->nWalking = 1;
  return;
}

/* ---- 0x0048fd90  Actor_UpdateMovement ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Actor_UpdateMovement(actor, dt): per frame; path following when actor+8 bit 0 (Actor_FollowPath),
   Actor_UpdateWalker, Actor_UpdateMoveChores, costume update with dt * time scale, Actor_PuckOrient
   when actor+4 & 0x10. */

void __cdecl Actor_UpdateMovement(Actor *actor,float param_2)

{
  CostumeNode *pCVar1;
  
  if (actor->pExtra != (ActorExtra *)0x0) {
    param_2 = actor->pExtra->flTimeScale * param_2;
  }
  pCVar1 = actor->pCostumes;
  actor->aPrevPos[0] = actor->aPos[0];
  actor->aPrevPos[1] = actor->aPos[1];
  actor->aPrevPos[2] = actor->aPos[2];
  if ((pCVar1 != (CostumeNode *)0x0) && (pCVar1->aCostumeRef[0] != 0)) {
    if (pCVar1->aCostumeRef[0] == 0) {
      (*g_pStd_HS->pAssertFail)
                (s_Bad_costume_Reference_004e9e90,s_main_sputResource_h_004e80a8,0xb8);
    }
    Cos_InstRescue(actor->pCostumes->dwInstance,pCVar1->aCostumeRef[1]);
  }
  if ((actor->dwMoveFlags & 1) != 0) {
    Actor_FollowPath(actor);
  }
  if ((actor->pExtra != (ActorExtra *)0x0) && (actor->pExtra->pPuck != (Puck *)0x0)) {
    Actor_UpdateWalker(actor);
  }
  Actor_UpdateMoveChores(actor);
  sputCostume_Update(actor->pCostumes,param_2);
  if ((actor->dwMoveFlags & 2) != 0) {
    Actor_UpdateLookAt(actor,param_2);
  }
  if ((actor->dwFlags & 0x10) != 0) {
    Actor_PuckOrient(actor);
  }
  return;
}
#endif


/* ---- 0x0048fe80  Actor_UpdateLookAt ---- */
/* Head tracking: turns the three head joints toward the look-at point (extra+0) limited by the look
   rate and the yaw/pitch limits */

void __cdecl Actor_UpdateLookAt(Actor *actor,float dt)

{
  unsigned char _frame[0xe0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  CostumeNode *pCVar1;
  ActorExtra *a;
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
  pCVar1 = actor->pCostumes;
  if (actor->pExtra == (ActorExtra *)0x0) {
    (**(code **)(g_dwSputActHS + 0x18))
              (s_pActor__pExtra_004e9ea8,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x47a);
  }
  if (((pCVar1 != (CostumeNode *)0x0) && (piVar8 = pCVar1->aHeadJoints, -1 < pCVar1->aHeadJoints[0])
      ) && (pCVar1->pMainModel != (void *)0x0)) {
    local_c0[0] = 0.0;
    local_c0[1] = 1.0;
    local_c0[2] = 0.0;
    if (actor->nScreenBoxValid == 0) {
      pfVar6 = sputActor_GetOrientMatrix(actor);
      rdPuppet_UpdateFrame(pCVar1->pMainModel,pfVar6);
    }
    index = pCVar1->aHeadJoints[2];
    pfVar6 = afStack_60;
    pfVar7 = sputActor_GetOrientMatrix(actor);
    rdPuppet_BuildJointMatrices(pCVar1->pMainModel,pfVar7,index,pfVar6);
    rdMatrix_InvertOrtho34(afStack_90,afStack_60);
    a = actor->pExtra;
    if (((a->aLookAt[0] == 0.0) && (a->aLookAt[1] == 0.0)) && (a->aLookAt[2] == 0.0)) {
      pfVar6 = afStack_90;
      bVar5 = true;
      pfVar7 = sputActor_GetOrientMatrix(actor);
      rdMatrix_TransformVector34(afStack_a8,pfVar7 + 3,pfVar6);
    }
    else {
      rdMatrix_TransformPoint34(afStack_a8,a->aLookAt,afStack_90);
      rdVector_Normalize3Acc(afStack_a8);
    }
    rdVector_Cross3(afStack_9c,local_c0,afStack_a8);
    rdVector_Normalize3Acc(afStack_9c);
    fStack_c8 = pCVar1->flLookRate * dt;
    fVar10 = rdVector_Dot2(local_c0,afStack_a8);
    fVar10 = stdMath_ArcSin1(fVar10);
    fVar10 = 90.0 - fVar10;
    fVar3 = fVar10;
    if (fVar10 < 0.0) {
      fVar3 = -fVar10;
    }
    if (fVar3 < fStack_c8) {
      if (bVar5) {
        actor->dwMoveFlags = actor->dwMoveFlags & 0xfffffffd;
      }
      fStack_c8 = fVar10;
      if (fVar10 <= 0.0) {
        fStack_c8 = -fVar10;
      }
    }
    rdMatrix_BuildFromVectorAngle34(afStack_30,afStack_9c,fStack_c8);
    rdMatrix_TransformPoint34Acc(local_c0,afStack_30);
    rdVector_ExtractAngles(local_c0,&fStack_b4);
    if ((actor->dwMoveFlags & 2) == 0) {
      iVar9 = 3;
      do {
        iVar9 = iVar9 + -1;
        *(undefined4 *)(*(int *)((int)pCVar1->pMainModel + 0x24) + 4 + *piVar8 * 0xc) = 0;
        *(undefined4 *)(*(int *)((int)pCVar1->pMainModel + 0x24) + *piVar8 * 0xc) = 0;
        *(undefined4 *)(*(int *)((int)pCVar1->pMainModel + 0x24) + 8 + *piVar8 * 0xc) = 0;
        piVar8 = piVar8 + 1;
      } while (iVar9 != 0);
      *(undefined4 *)((int)pCVar1->pMainModel + 0x1c) = 0;
      return;
    }
    iVar9 = 3;
    fVar3 = pCVar1->flMaxYaw * 0.33333334;
    fVar10 = pCVar1->flMaxPitch * 0.33333334;
    do {
      iVar2 = *(int *)((int)pCVar1->pMainModel + 0x24);
      *(float *)(iVar2 + 4 + *piVar8 * 0xc) =
           fStack_b0 * 0.33333334 + *(float *)(iVar2 + 4 + *piVar8 * 0xc);
      iVar2 = *(int *)((int)pCVar1->pMainModel + 0x24);
      *(float *)(iVar2 + *piVar8 * 0xc) = fStack_b4 * 0.33333334 + *(float *)(iVar2 + *piVar8 * 0xc)
      ;
      *(undefined4 *)(*(int *)((int)pCVar1->pMainModel + 0x24) + 8 + *piVar8 * 0xc) = 0;
      iVar2 = *(int *)((int)pCVar1->pMainModel + 0x24);
      pfVar6 = (float *)(iVar2 + 4 + *piVar8 * 0xc);
      fVar4 = -fVar3;
      if ((-fVar3 <= *(float *)(iVar2 + 4 + *piVar8 * 0xc)) && (fVar4 = fVar3, *pfVar6 <= fVar3)) {
        fVar4 = *pfVar6;
      }
      *pfVar6 = fVar4;
      iVar2 = *(int *)((int)pCVar1->pMainModel + 0x24);
      pfVar6 = (float *)(iVar2 + *piVar8 * 0xc);
      fVar4 = -fVar10;
      if ((-fVar10 <= *(float *)(iVar2 + *piVar8 * 0xc)) && (fVar4 = fVar10, *pfVar6 <= fVar10)) {
        fVar4 = *pfVar6;
      }
      *pfVar6 = fVar4;
      piVar8 = piVar8 + 1;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    *(undefined4 *)((int)pCVar1->pMainModel + 0x1c) = 0;
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


/* ---- 0x00490210  sputActor_UpdateActorSpeech ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lip sync: reads the current phoneme from iMUSE, plays the matching talk chore, ends speech when
   the voice or the text timer runs out Original name sputActor_UpdateActorSpeech (the remaster's
   GrimFandango (Linux): aligned call in sputActor_UpdateSpeechOnly); was Actor_UpdateTalk. */

void __cdecl sputActor_UpdateActorSpeech(Actor *actor,float dt)

{
  void **ppvVar1;
  ActorExtra *pAVar2;
  ushort uVar3;
  int iVar4;
  undefined2 extraout_var;
  CostumeNode *pCVar5;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar6;
  
  pAVar2 = actor->pExtra;
  if (pAVar2->nTalking == 0) {
    return;
  }
  if (((pAVar2->aVoiceFile[0] != '\0') && (pAVar2->nLipSync != 0)) &&
     (actor->pCostumes != (CostumeNode *)0x0)) {
    iVar4 = iMUSE_GetPhoneme(pAVar2->nVoiceSound,0);
    if (iVar4 == 0) {
      sputActor_ShutUp(actor);
    }
    else {
      uVar3 = Phoneme_ToTalkChore(actor,iVar4);
      pCVar5 = actor->pCostumes;
      ppvVar1 = &pCVar5->pMainModel;
      if (pCVar5 != (CostumeNode *)0x0) {
        do {
          if ((pCVar5->pMainModel != *ppvVar1) ||
             (-1 < pCVar5->aTalkChores[CONCAT22(extraout_var,uVar3)])) break;
          pCVar5 = pCVar5->pNext;
        } while (pCVar5 != (CostumeNode *)0x0);
        if ((pCVar5 != (CostumeNode *)0x0) && (pCVar5->pMainModel == *ppvVar1)) {
          Cos_InstCompleteChore
                    (pCVar5->dwInstance,pCVar5->aTalkChores[CONCAT22(extraout_var,uVar3)]);
        }
      }
    }
  }
  pAVar2 = actor->pExtra;
  lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  pAVar2->nTalkTime = pAVar2->nTalkTime + (int)lVar6;
  if ((actor->pExtra->aVoiceFile[0] == '\0') || (iVar4 = Actor_IsVoicePlaying(actor), iVar4 != 0)) {
    if (actor->pExtra->aVoiceFile[0] != '\0') {
      return;
    }
    if (-1 < actor->pExtra->nTalkTime) {
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
  if (g_pSelectedActor != (Actor *)0x0) {
    iVar1 = sputActor_GetActorHandle(g_pSelectedActor,unaff_retaddr);
  }
  if ((-1 < handle) && (handle < g_nMaxActors)) {
    g_pSelectedActor = g_pActors + handle;
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

Actor * __cdecl sputActor_ActorDeref(int handle)

{
  return g_pActors + handle;
}

/* ---- 0x00490380  sputActor_GetActorHandle ---- */
/* Original name sputActor_GetActorHandle (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_CallCostumeMarkerHandler; the only unmatched callee of
   Lua_CallCostumeOverrideHandler; 3 matched neighbours agree, 1 disagree); was Actor_GetHandle. */

int __cdecl sputActor_GetActorHandle(Actor *actor,int tag)

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
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  Actor *pAVar4;
  Actor *pAVar5;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define aiStack_10 (*(int (*)[4])(_frame + (0x30 - 0x10)))
  
  iVar1 = 0;
  pAVar4 = (Actor *)0x0;
  if (0 < g_nMaxActors) {
    piVar3 = &g_pActors->nInUse;
    do {
      if (*piVar3 == 0) {
        pAVar4 = g_pActors + iVar1;
        break;
      }
      iVar1 = iVar1 + 1;
      piVar3 = piVar3 + 0x2a;
    } while (iVar1 < g_nMaxActors);
  }
  if (pAVar4 == (Actor *)0x0) {
    iVar1 = 0;
    do {
      if (*(int *)((int)g_pTalkingActors + iVar1) != 0) {
        *(int *)((int)aiStack_10 + iVar1) =
             (*(int *)((int)g_pTalkingActors + iVar1) - (int)g_pActors) / 0xa8;
      }
      iVar1 = iVar1 + 4;
    } while (iVar1 < 0x10);
    if (g_pSelectedActor != (Actor *)0x0) {
      local_14 = ((int)g_pSelectedActor - (int)g_pActors) / 0xa8;
    }
    g_pActors = (Actor *)(**(code **)(g_dwSputActHS + 0x28))
                                   (g_pActors,(g_nMaxActors + 0x20) * 0xa8,
                                    s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x5f6);
    pAVar4 = g_pActors + g_nMaxActors;
    for (iVar1 = 0x540; pAVar5 = g_pActors, iVar1 != 0; iVar1 = iVar1 + -1) {
      pAVar4->pColormapRef = (void *)0x0;
      pAVar4 = (Actor *)&pAVar4->dwFlags;
    }
    iVar1 = 0;
    pAVar4 = g_pActors + g_nMaxActors;
    g_nMaxActors = g_nMaxActors + 0x20;
    do {
      if (*(int *)((int)g_pTalkingActors + iVar1) != 0) {
        *(Actor **)((int)g_pTalkingActors + iVar1) = pAVar5 + *(int *)((int)aiStack_10 + iVar1);
      }
      iVar1 = iVar1 + 4;
    } while (iVar1 < 0x10);
    if (g_pSelectedActor != (Actor *)0x0) {
      g_pSelectedActor = pAVar5 + local_14;
    }
  }
  g_nNumActors = g_nNumActors + 1;
  pAVar5 = pAVar4;
  for (iVar1 = 0x2a; iVar1 != 0; iVar1 = iVar1 + -1) {
    pAVar5->pColormapRef = (void *)0x0;
    pAVar5 = (Actor *)&pAVar5->dwFlags;
  }
  pAVar4->nMatrixDirty = 1;
  rdMatrix_Identity34(pAVar4->aOrient);
  pAVar4->flScale = 1.0;
  pAVar4->pCostumes = (CostumeNode *)0x0;
  puVar2 = (undefined4 *)
           (**(code **)(g_dwSputActHS + 0x20))
                     (0x34,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x60e);
  pAVar4->pColormapRef = puVar2;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  pAVar4->nInUse = 1;
  return ((int)pAVar4 - (int)g_pActors) / 0xa8;
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

void __cdecl sputActor_AllocateActorExtra(Actor *actor)

{
  ActorExtra *pAVar1;
  int iVar2;
  
  if ((actor == (Actor *)0x0) || (actor->pExtra != (ActorExtra *)0x0)) {
    (**(code **)(g_dwSputActHS + 0x18))
              (s_pActor_____pActor__pExtra_004e9eb8,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,
               0x619);
  }
  pAVar1 = (ActorExtra *)
           (**(code **)(g_dwSputActHS + 0x20))
                     (0x4a0,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x61b);
  actor->pExtra = pAVar1;
  if (pAVar1 == (ActorExtra *)0x0) {
    (**(code **)(g_dwSputActHS + 0x18))
              (s_pActor__pExtra_004e9ea8,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x61c);
  }
  pAVar1 = actor->pExtra;
  for (iVar2 = 0x128; iVar2 != 0; iVar2 = iVar2 + -1) {
    pAVar1->aLookAt[0] = 0.0;
    pAVar1 = (ActorExtra *)(pAVar1->aLookAt + 1);
  }
  actor->pExtra->flWalkRate = 0.4;
  actor->pExtra->flTurnRate = 135.0;
  actor->pExtra->nWalkDominate = 0;
  actor->pExtra->flPuckRadius = 60.0;
  actor->pExtra->flCollisionScale = 1.0;
  actor->pExtra->flTimeScale = 1.0;
  actor->pExtra->dwTalkColor = 0xffffff;
  actor->pExtra->nInvClipNode = -1;
  actor->pExtra->aClipNormal[0] = 0.0;
  actor->pExtra->aClipNormal[1] = 0.0;
  actor->pExtra->aClipNormal[2] = 1.0;
  return;
}

/* ---- 0x004906b0  sputActor_EnableWalkSystem ---- */
/* Actor_SetFollowBoxes(actor, follow): sets extra+0x1b8. Following creates the walker and
   reattaches it to the set; not following clears the walker's sector (+0x5c) but keeps the walker.
   Original name sputActor_EnableWalkSystem (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetActorFollowBoxes; 1 matched neighbours agree, 1 disagree); was
   Actor_SetFollowBoxes. */

void __cdecl sputActor_EnableWalkSystem(Actor *actor,int param_2)

{
  Puck *pPVar1;
  
  if (actor->pExtra == (ActorExtra *)0x0) {
    sputActor_AllocateActorExtra(actor);
  }
  if (param_2 != 0) {
    actor->pExtra->nFollowBoxes = 1;
    sputActor_EnablePuck(actor,1);
    Puck_Validate(actor->pExtra->pPuck);
    return;
  }
  actor->pExtra->nFollowBoxes = 0;
  pPVar1 = actor->pExtra->pPuck;
  if (pPVar1 != (Puck *)0x0) {
    pPVar1->pSector = (WalkPlane *)0x0;
  }
  return;
}

/* ---- 0x00490730  sputActor_EnablePuck ---- */
/* Source: Engine/sputActor.cpp (line 1637, from __FILE__/__LINE__ passed to the allocator) Original
   name sputActor_EnablePuck (the remaster's GrimFandango (Linux): the only unmatched callee of
   Actor_TurnKey; the only unmatched callee of Actor_WalkForward; 7 matched neighbours agree, 0
   disagree); was Actor_CreateWalker. */

void __cdecl sputActor_EnablePuck(Actor *actor,int param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Puck *pPVar1;
  float *pfVar2;
  Puck *this;
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  
  this = (Puck *)0x0;
  if ((param_2 == 0) && (pPVar1 = actor->pExtra->pPuck, pPVar1 != (Puck *)0x0)) {
    Puck_Destruct(pPVar1);
    Plat_Free(pPVar1);
    actor->pExtra->pPuck = (Puck *)0x0;
    return;
  }
  if (actor->pExtra->pPuck == (Puck *)0x0) {
    pPVar1 = Plat_Alloc(0x60);
    if (pPVar1 != (Puck *)0x0) {
      this = Puck_Construct(pPVar1,actor->pExtra->flPuckRadius);
    }
    Mem_CheckAlloc(this,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x665);
    Puck_SetPos(this,actor->aPos);
    pfVar2 = sputActor_GetOrientMatrix(actor);
    local_18[0] = pfVar2[3] + actor->aPos[0];
    local_18[1] = actor->aPos[1] + pfVar2[4];
    local_18[2] = actor->aPos[2] + pfVar2[5];
    Puck_PointAt(this,local_18,3.4028235e+38);
    actor->pExtra->pPuck = this;
  }
  return;
}
#undef local_18


/* ---- 0x00490870  sputActor_SetActorPosition ---- */
/* Original name sputActor_SetActorPosition (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_PutActorAt; the only unmatched callee of Lua_PutActorAtInterest; 2 matched
   neighbours agree, 1 disagree); was Actor_SetPositionClamped. */

void __cdecl sputActor_SetActorPosition(Actor *actor,float *param_2)

{
  float fVar1;
  Puck *this;
  
  this = (Puck *)0x0;
  if (actor->pExtra != (ActorExtra *)0x0) {
    this = actor->pExtra->pPuck;
  }
  actor->dwMoveFlags = actor->dwMoveFlags & 0xfffffffe;
  if (this != (Puck *)0x0) {
    Puck_SetPos(this,param_2);
    if (actor->pExtra->nFollowBoxes != 0) {
      Puck_Validate(this);
    }
    actor->aPos[0] = this->aPos[0];
    actor->aPos[1] = this->aPos[1];
    fVar1 = this->aPos[2];
    actor->nMatrixDirty = 0;
    actor->aPos[2] = fVar1;
    return;
  }
  actor->aPos[0] = *param_2;
  actor->aPos[1] = param_2[1];
  fVar1 = param_2[2];
  actor->nMatrixDirty = 0;
  actor->aPos[2] = fVar1;
  return;
}

/* ---- 0x00490900  sputActor_SetActorRotation ---- */
/* WARNING: Variable defined which should be unmapped: local_40 */
/* Actor_SetRot(actor, angles, snap): clears actor+8 bit 0 first, which ends a WalkActorTo path walk
   (Actor_UpdateMovement only calls Actor_FollowPath while it is set). Pitch (+0x24) and roll
   (+0x2c) are always set at once. With a walker, the walker heading is turned to the yaw
   immediately, +0x28 (angle left) is set, and the visible yaw eases there in sputActor_AlignToPuck;
   snap (5th Lua arg nil) negates the turn rate so that update jumps in one frame. Without a walker
   all three angles are set at once. Does not create a walker. Original name
   sputActor_SetActorRotation (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_SetActorRot; 2 matched neighbours agree, 0 disagree); was Actor_SetRot. */

void __cdecl sputActor_SetActorRotation(Actor *actor,undefined4 *param_2,int param_3)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Puck *this;
  ActorExtra *pAVar1;
  float fVar2;
  #define local_40 (*(float *)(_frame + (0x50 - 0x40)))
  #define local_30 (*(float (*)[3])(_frame + (0x50 - 0x30)))
  #define local_24 (*(float (*)[3])(_frame + (0x50 - 0x24)))
  
  actor->dwMoveFlags = actor->dwMoveFlags & 0xfffffffe;
  if ((actor->pExtra != (ActorExtra *)0x0) && (this = actor->pExtra->pPuck, this != (Puck *)0x0)) {
    rdMatrix_BuildRotate34(local_30,param_2);
    local_24[0] = local_24[0] + this->aPos[0];
    local_24[1] = this->aPos[1] + local_24[1];
    local_24[2] = this->aPos[2] + local_24[2];
    Puck_InvXform(this,local_24);
    local_24[2] = 0.0;
    rdVector_Normalize3Acc(local_24);
    fVar2 = stdMath_ArcSin3(local_24[1]);
    fVar2 = 90.0 - fVar2;
    local_40 = fVar2;
    if (0.0 < local_24[0]) {
      local_40 = -fVar2;
    }
    Puck_Rotate(this,local_40);
    pAVar1 = actor->pExtra;
    if ((0.0 < pAVar1->flTurnRate) && (param_3 != 0)) {
      pAVar1->flTurnRate = pAVar1->flTurnRate * -1.0;
    }
    actor->pExtra->flYawLeft = fVar2;
    actor->aRot[2] = PUN(float,param_2[2]);
    actor->aRot[0] = PUN(float,*param_2);
    actor->nMatrixDirty = 0;
    return;
  }
  actor->aRot[0] = PUN(float,*param_2);
  actor->aRot[1] = PUN(float,param_2[1]);
  fVar2 = PUN(float,param_2[2]);
  actor->nMatrixDirty = 0;
  actor->aRot[2] = fVar2;
  return;
}
#undef local_24
#undef local_30
#undef local_40


/* ---- 0x00490a40  sputActor_SetReflection ---- */
/* Original name sputActor_SetReflection (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetActorReflection; 1 matched neighbours agree, 0 disagree); was
   Actor_SetReflection. */

void __cdecl sputActor_SetReflection(Actor *actor,float angle)

{
  Puck *pPVar1;
  
  pPVar1 = actor->pExtra->pPuck;
  if (pPVar1 != (Puck *)0x0) {
    pPVar1->flRadius = angle;
  }
  return;
}

/* ---- 0x00490b50  sputActor_SetTurnChores ---- */
/* Original name sputActor_SetTurnChores (the remaster's GrimFandango (Linux): same body (stop the
   old left / right turn chores of the costume and keep their play state, store the new ones at
   +0x2c / +0x30); called by sputLua_SetActorTurnChoresL in both builds); was Actor_SetTurnChores.
    */

void __cdecl sputActor_SetTurnChores(Actor *actor,int leftChore,int rightChore,CostumeNode *costume)

{
  void **ppvVar1;
  uint uVar2;
  CostumeNode *pCVar3;
  
  pCVar3 = actor->pCostumes;
  if (pCVar3 != (CostumeNode *)0x0) {
    if (costume == (CostumeNode *)0x0) {
      costume = pCVar3;
    }
    ppvVar1 = &pCVar3->pMainModel;
    if (pCVar3 != (CostumeNode *)0x0) {
      do {
        if ((pCVar3->pMainModel != *ppvVar1) || (-1 < pCVar3->nTurnLeftChore)) break;
        pCVar3 = pCVar3->pNext;
      } while (pCVar3 != (CostumeNode *)0x0);
      if ((pCVar3 != (CostumeNode *)0x0) && (pCVar3->pMainModel == *ppvVar1)) {
        if (leftChore != pCVar3->nTurnLeftChore) {
          uVar2 = Cos_InstChoreStatus(pCVar3->dwInstance,pCVar3->nTurnLeftChore);
          if ((uVar2 != 0) &&
             (Cos_InstStopChore(pCVar3->dwInstance,pCVar3->nTurnLeftChore), leftChore != -1)) {
            Cos_InstPlayChore(pCVar3->dwInstance,leftChore,uVar2 & 2,~uVar2 >> 2 & 1);
          }
          pCVar3->nTurnLeftChore = -1;
          costume->nTurnLeftChore = leftChore;
        }
        if (rightChore == pCVar3->nTurnRightChore) {
          return;
        }
        uVar2 = Cos_InstChoreStatus(pCVar3->dwInstance,pCVar3->nTurnRightChore);
        if ((uVar2 != 0) &&
           (Cos_InstStopChore(pCVar3->dwInstance,pCVar3->nTurnRightChore), leftChore != -1)) {
          Cos_InstPlayChore(pCVar3->dwInstance,rightChore,uVar2 & 2,~uVar2 >> 2 & 1);
        }
        pCVar3->nTurnRightChore = -1;
        costume->nTurnRightChore = rightChore;
        return;
      }
    }
    costume->nTurnLeftChore = leftChore;
    costume->nTurnRightChore = rightChore;
  }
  return;
}

/* ---- 0x00490c80  sputActor_SetRestChore ---- */
/* Original name sputActor_SetRestChore (the remaster's GrimFandango (Linux): aligned call in
   sputLua_SetActorRestChoreL); was Actor_SetRestChore. */

void __cdecl sputActor_SetRestChore(Actor *actor,int chore,CostumeNode *costume)

{
  void **ppvVar1;
  uint uVar2;
  CostumeNode *pCVar3;
  
  pCVar3 = actor->pCostumes;
  if (pCVar3 != (CostumeNode *)0x0) {
    if (costume == (CostumeNode *)0x0) {
      costume = pCVar3;
    }
    ppvVar1 = &pCVar3->pMainModel;
    if (pCVar3 != (CostumeNode *)0x0) {
      do {
        if ((pCVar3->pMainModel != *ppvVar1) || (-1 < pCVar3->nRestChore)) break;
        pCVar3 = pCVar3->pNext;
      } while (pCVar3 != (CostumeNode *)0x0);
      if ((pCVar3 != (CostumeNode *)0x0) && (pCVar3->pMainModel == *ppvVar1)) {
        if (chore == pCVar3->nRestChore) {
          return;
        }
        uVar2 = Cos_InstChoreStatus(pCVar3->dwInstance,pCVar3->nRestChore);
        if ((uVar2 != 0) && (Cos_InstStopChore(pCVar3->dwInstance,pCVar3->nRestChore), chore != -1))
        {
          Cos_InstPlayChore(pCVar3->dwInstance,chore,uVar2 & 2,~uVar2 >> 2 & 1);
        }
        pCVar3->nRestChore = -1;
        costume->nRestChore = chore;
        return;
      }
    }
    costume->nRestChore = chore;
  }
  return;
}

/* ---- 0x00490d30  sputActor_PushCostume ---- */
/* Original name sputActor_PushCostume (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_PushActorCostume; 2 matched neighbours agree, 0 disagree); was Actor_PushCostume.
    */

int __cdecl sputActor_PushCostume(Actor *actor,char *name,int param_3)

{
  void *costumeRes;
  CostumeNode *pCVar1;
  
  if ((name == (char *)0x0) || (param_3 != 0)) {
    costumeRes = (void *)0x0;
    pCVar1 = actor->pCostumes;
  }
  else {
    costumeRes = sputResource_Alloc(0x54534f43,name);
    if (costumeRes == (void *)0x0) {
      return 0;
    }
    param_3 = 0;
    pCVar1 = actor->pCostumes;
  }
  pCVar1 = sputCostume_PushCostume(pCVar1,costumeRes,param_3);
  actor->pCostumes = pCVar1;
  Cos_InstSetUserData(actor->pCostumes->dwInstance,((int)actor - (int)g_pActors) / 0xa8);
  sputActor_SetFrustrumCull(actor,~actor->dwFlags >> 2 & 1);
  return 1;
}

/* ---- 0x00490dd0  sputActor_PopCostume ---- */
/* Original name sputActor_PopCostume (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_PopActorCostume; 2 matched neighbours agree, 0 disagree); was Actor_PopCostume. */

void __cdecl sputActor_PopCostume(Actor *actor,int free)

{
  CostumeNode *pCVar1;
  
  pCVar1 = sputCostume_PopCostume(actor->pCostumes,free);
  actor->pCostumes = pCVar1;
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

void __cdecl Actor_PuckOrient(Actor *actor)

{
  unsigned char _frame[0x80] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  Puck *pPVar4;
  Actor *pAVar5;
  Actor *pAVar6;
  float fVar7;
  #define local_68 (*(uint *)(_frame + (0x80 - 0x68)))
  #define local_54 (*(float (*)[3])(_frame + (0x80 - 0x54)))
  #define local_48 (*(float (*)[3])(_frame + (0x80 - 0x48)))
  #define local_3c (*(float (*)[3])(_frame + (0x80 - 0x3c)))
  #define local_30 (*(float (*)[12])(_frame + (0x80 - 0x30)))
  
  if (((actor != (Actor *)0x0) && (actor->pExtra != (ActorExtra *)0x0)) &&
     (pPVar4 = actor->pExtra->pPuck, pPVar4 != (Puck *)0x0)) {
    pfVar1 = actor->aPos;
    pfVar2 = actor->aRot;
    pfVar3 = actor->aOrient;
    rdMatrix_Build34(pfVar3,(uint *)pfVar2,pfVar1);
    local_48[0] = actor->aOrient[6];
    local_48[1] = actor->aOrient[7];
    local_48[2] = actor->aOrient[8];
    local_54[0] = pPVar4->aFrame[6];
    local_54[1] = pPVar4->aFrame[7];
    local_54[2] = pPVar4->aFrame[8];
    fVar7 = rdVector_Dot3(local_48,local_54);
    fVar7 = stdMath_ArcSin3(fVar7);
    pAVar5 = PUN(Actor *,(float)(90.0 - fVar7));
    pAVar6 = pAVar5;
    if (PUN(float,pAVar5) < 0.0) {
      pAVar6 = PUN(Actor *,(float)-PUN(float,pAVar5));
    }
    if (2.0 < PUN(float,pAVar6)) {
      fVar7 = sputTime_GetFrameTimeFlex();
      pAVar6 = PUN(Actor *,(float)(fVar7 * actor->pExtra->flTurnRate));
      actor = pAVar5;
      if ((0.0 < PUN(float,pAVar5)) && (PUN(float,pAVar6) < PUN(float,pAVar5))) {
        actor = pAVar6;
      }
      if ((PUN(float,actor) < 0.0) && (PUN(float,actor) < -PUN(float,pAVar6))) {
        actor = PUN(Actor *,(float)-PUN(float,pAVar6));
      }
      local_3c[0] = local_54[2] * local_48[1] - local_54[1] * local_48[2];
      local_3c[1] = local_54[0] * local_48[2] - local_54[2] * local_48[0];
      local_3c[2] = local_54[1] * local_48[0] - local_54[0] * local_48[1];
      rdVector_Normalize3Acc(local_3c);
      rdMatrix_BuildFromVectorAngle34(local_30,local_3c,PUN(float,actor));
      rdMatrix_PostMultiply34(pfVar3,local_30);
      rdMatrix_ExtractAngles34(pfVar3,pfVar2);
      rdMatrix_Build34(pfVar3,(uint *)pfVar2,pfVar1);
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
void __cdecl Actor_UpdateWalker(Actor *actor)

{
  Puck *pPVar1;
  ActorExtra *pAVar2;
  undefined *puVar3;
  int iVar4;
  float fVar5;
  uint turnLeftOk;
  uint turnRightOk;
  
  pPVar1 = actor->pExtra->pPuck;
  if ((actor->pExtra->nTurning != 0) && ((actor->dwMoveFlags & 1) == 0)) {
    pAVar2 = actor->pExtra;
    fVar5 = sputTime_GetFrameTimeFlex();
    Puck_Rotate(pAVar2->pPuck,
                      (float)pAVar2->nTurning * pAVar2->flTurnRate * fVar5 * pAVar2->flTimeScale);
  }
  pAVar2 = actor->pExtra;
  if (pAVar2->nWalking != 0) {
    fVar5 = sputTime_GetFrameTimeFlex();
    if (pAVar2->nWalkDominate == 0) {
      turnRightOk = (uint)(pAVar2->nTurning != 1);
      turnLeftOk = (uint)(pAVar2->nTurning != -1);
    }
    else {
      turnRightOk = 1;
      turnLeftOk = 1;
    }
    puVar3 = Puck_Forward(pAVar2->pPuck,fVar5 * pAVar2->flTimeScale * pAVar2->flWalkRate,
                                turnLeftOk,turnRightOk);
    actor->pExtra->nWalking = (int)puVar3;
  }
  iVar4 = sputActor_AlignToPuck(actor,pPVar1->aPos);
  actor->pExtra->nAlignTurn = iVar4;
  pAVar2 = actor->pExtra;
  if ((pAVar2->nTurning == 0) && (pAVar2->nAlignTurn == 0)) {
    if (pAVar2->flYawLeft <= 0.0) {
      iVar4 = 1;
    }
    else {
      iVar4 = -1;
    }
    pAVar2->nTurning = iVar4;
  }
  actor->aPos[0] = pPVar1->aPos[0];
  actor->aPos[1] = pPVar1->aPos[1];
  fVar5 = pPVar1->aPos[2];
  actor->nMatrixDirty = 0;
  actor->aPos[2] = fVar5;
  return;
}
#endif


/* ---- 0x004913f0  Actor_UpdateMoveChores ---- */
/* Actor_UpdateMoveChores (after Actor_UpdateWalker): costume record [10] walk, [0xb] left turn,
   [0xc] right turn, [0xd] rest. Walking (walker+0xc): start walk chore (rest flag +0x14 = 0) else
   stop it; walking clears +0x10. +0x10 >= 1 plays left, < 0 plays right (eased turns set -1 always:
   right chore); starting one clears +0x14. Not walking and +0x10 == 0 sets +0x14 = 1; rest plays
   while +0x14 else stops. Clears +0xc and +0x10. Start/stop fade 130 ms (DAT_004e9e04). */

void __cdecl Actor_UpdateMoveChores(Actor *actor)

{
  void **ppvVar1;
  int iVar2;
  void *pvVar3;
  ActorExtra *pAVar4;
  uint uVar5;
  int iVar6;
  CostumeNode *pCVar7;
  
  if (actor->pExtra == (ActorExtra *)0x0) {
    return;
  }
  pCVar7 = actor->pCostumes;
  if (pCVar7 == (CostumeNode *)0x0) {
    return;
  }
  ppvVar1 = &pCVar7->pMainModel;
  if (pCVar7 != (CostumeNode *)0x0) {
    do {
      if ((pCVar7->pMainModel != *ppvVar1) || (-1 < pCVar7->nWalkChore)) break;
      pCVar7 = pCVar7->pNext;
    } while (pCVar7 != (CostumeNode *)0x0);
    if ((pCVar7 != (CostumeNode *)0x0) && (pCVar7->pMainModel == *ppvVar1)) {
      uVar5 = Cos_InstChoreStatus(pCVar7->dwInstance,pCVar7->nWalkChore);
      iVar2 = actor->pExtra->nWalking;
      if (iVar2 == 0) {
LAB_00491477:
        if (((uVar5 & 1) != 0) && ((actor->dwMoveFlags & 1) == 0)) {
          FadeOutChore((void *)pCVar7->dwInstance,pCVar7->nWalkChore,g_nWALKSYSTEM_FADE_TIME);
        }
      }
      else if (uVar5 == 0) {
        actor->pExtra->nResting = 0;
        FadeInChore(pCVar7->dwInstance,pCVar7->nWalkChore,g_nWALKSYSTEM_FADE_TIME);
      }
      else if (iVar2 == 0) goto LAB_00491477;
    }
  }
  if (actor->pExtra->nWalking != 0) {
    actor->pExtra->nTurning = 0;
  }
  pCVar7 = actor->pCostumes;
  pvVar3 = pCVar7->pMainModel;
  if (pCVar7 != (CostumeNode *)0x0) {
    do {
      if ((pCVar7->pMainModel != pvVar3) || (-1 < pCVar7->nTurnLeftChore)) break;
      pCVar7 = pCVar7->pNext;
    } while (pCVar7 != (CostumeNode *)0x0);
    if (pCVar7 != (CostumeNode *)0x0) {
      if ((pCVar7->pMainModel == pvVar3) && (-1 < pCVar7->nTurnLeftChore)) {
        uVar5 = Cos_InstChoreStatus(pCVar7->dwInstance,pCVar7->nTurnLeftChore);
        iVar2 = actor->pExtra->nTurning;
        if (iVar2 < 1) {
LAB_00491517:
          if ((uVar5 & 1) != 0) {
            FadeOutChore((void *)pCVar7->dwInstance,pCVar7->nTurnLeftChore,g_nWALKSYSTEM_FADE_TIME);
          }
        }
        else if (uVar5 == 0) {
          actor->pExtra->nResting = 0;
          FadeInChore(pCVar7->dwInstance,pCVar7->nTurnLeftChore,g_nWALKSYSTEM_FADE_TIME);
        }
        else if (iVar2 < 1) goto LAB_00491517;
      }
      if (((pCVar7 != (CostumeNode *)0x0) && (pCVar7->pMainModel == pvVar3)) &&
         (-1 < pCVar7->nTurnRightChore)) {
        uVar5 = Cos_InstChoreStatus(pCVar7->dwInstance,pCVar7->nTurnRightChore);
        iVar2 = actor->pExtra->nTurning;
        if (iVar2 < 0) {
          if (uVar5 == 0) {
            actor->pExtra->nResting = 0;
            FadeInChore(pCVar7->dwInstance,pCVar7->nTurnRightChore,g_nWALKSYSTEM_FADE_TIME);
          }
          else if (-1 < iVar2) goto LAB_0049157a;
        }
        else {
LAB_0049157a:
          if ((uVar5 & 1) != 0) {
            FadeOutChore((void *)pCVar7->dwInstance,pCVar7->nTurnRightChore,g_nWALKSYSTEM_FADE_TIME)
            ;
          }
        }
      }
    }
  }
  pAVar4 = actor->pExtra;
  if ((pAVar4->nWalking == 0) && (pAVar4->nTurning == 0)) {
    pAVar4->nResting = 1;
  }
  pCVar7 = actor->pCostumes;
  ppvVar1 = &pCVar7->pMainModel;
  if (pCVar7 != (CostumeNode *)0x0) {
    do {
      if ((pCVar7->pMainModel != *ppvVar1) || (-1 < pCVar7->nRestChore)) break;
      pCVar7 = pCVar7->pNext;
    } while (pCVar7 != (CostumeNode *)0x0);
    if (((pCVar7 != (CostumeNode *)0x0) && (pCVar7->pMainModel == *ppvVar1)) &&
       (-1 < pCVar7->nRestChore)) {
      iVar6 = Cos_InstChoreStatus(pCVar7->dwInstance,pCVar7->nRestChore);
      iVar2 = actor->pExtra->nResting;
      if (iVar2 != 0) {
        if (iVar6 == 0) {
          FadeInChore(pCVar7->dwInstance,pCVar7->nRestChore,g_nWALKSYSTEM_FADE_TIME);
          goto LAB_0049162b;
        }
        if (iVar2 != 0) goto LAB_0049162b;
      }
      if (iVar6 != 0) {
        FadeOutChore((void *)pCVar7->dwInstance,pCVar7->nRestChore,g_nWALKSYSTEM_FADE_TIME);
      }
    }
  }
LAB_0049162b:
  actor->pExtra->nWalking = 0;
  actor->pExtra->nTurning = 0;
  return;
}

/* ---- 0x00492b30  sputActor_SayLine ---- */
/* Starts speech: resolves the /id/ to a voice file (.wvc/.wav/.imc/.imu), plays it (3D positioned
   when flag 8), creates the subtitle text object, times text-only speech from its length, and plays
   the talk chore Original name sputActor_SayLine (the remaster's GrimFandango (Linux): aligned call
   in sputText_SayLineL); was Actor_SayLine. */

void __cdecl
sputActor_SayLine(Actor *actor,char *text,int background,int volume,int pan,int x,int y)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void **ppvVar1;
  uint *puVar2;
  char cVar3;
  byte bVar4;
  Actor *pAVar5;
  ActorExtra *pAVar6;
  uint uVar7;
  char *text_00;
  int iVar8;
  char *pcVar9;
  Actor **ppAVar10;
  TextObject *pTVar11;
  CostumeNode *pCVar12;
  uint uVar13;
  int *piVar14;
  byte *pbVar15;
  uint uVar16;
  char *pcVar17;
  bool bVar18;
  #define local_44 (*(byte (*)[32])(_frame + (0x60 - 0x44)))
  #define local_24 (*(char (*)[36])(_frame + (0x60 - 0x24)))
  
  if (actor->pExtra == (ActorExtra *)0x0) {
    sputActor_AllocateActorExtra(actor);
  }
  uVar7 = g_dwSmSpeechMode & 1;
  uVar16 = g_dwSmSpeechMode & 2;
  text_00 = sputText_ExtractSayLineData(text,(char *)local_44);
  local_24[0] = '\0';
  if (local_44[0] != 0) {
    sprintf(local_24,s__s_wvc_004e9eec,local_44);
    iVar8 = (**(code **)(g_dwSputActHS + 0x30))(local_24,&DAT_004ddb18);
    if (iVar8 == 0) {
      sprintf(local_24,s__s_wav_004e9ee4,local_44);
      iVar8 = (**(code **)(g_dwSputActHS + 0x30))(local_24,&DAT_004ddb18);
      if (iVar8 == 0) {
        sprintf(local_24,s__s_imc_004e9edc,local_44);
        iVar8 = (**(code **)(g_dwSputActHS + 0x30))(local_24,&DAT_004ddb18);
        if (iVar8 == 0) {
          sprintf(local_24,s__s_imu_004e9ed4,local_44);
          iVar8 = (**(code **)(g_dwSputActHS + 0x30))(local_24,&DAT_004ddb18);
          if (iVar8 == 0) {
            local_24[0] = '\0';
            goto LAB_00492c61;
          }
        }
      }
    }
    (**(code **)(g_dwSputActHS + 0x34))(iVar8);
  }
LAB_00492c61:
  if (actor->pExtra->nTalking != 0) {
    if (local_44[0] != 0) {
      pbVar15 = local_44;
      pcVar9 = actor->pExtra->aMsgId;
      do {
        bVar4 = *pcVar9;
        bVar18 = bVar4 < *pbVar15;
        if (bVar4 != *pbVar15) {
LAB_00492ca6:
          iVar8 = (1 - (uint)bVar18) - (uint)(bVar18 != 0);
          goto LAB_00492cab;
        }
        if (bVar4 == 0) break;
        bVar4 = pcVar9[1];
        bVar18 = bVar4 < pbVar15[1];
        if (bVar4 != pbVar15[1]) goto LAB_00492ca6;
        pcVar9 = pcVar9 + 2;
        pbVar15 = pbVar15 + 2;
      } while (bVar4 != 0);
      iVar8 = 0;
LAB_00492cab:
      if (iVar8 == 0) {
        return;
      }
    }
    sputActor_ShutUp(actor);
  }
  actor->pExtra->nTalkTime = 0;
  actor->pExtra->nTalking = 1;
  strncpy(actor->pExtra->aMsgId,local_44,0xc);
  g_nNumActorsTalking = g_nNumActorsTalking + 1;
  iVar8 = 0;
  ppAVar10 = g_pTalkingActors;
  do {
    if (*ppAVar10 == (Actor *)0x0) {
      g_pTalkingActors[iVar8] = actor;
      break;
    }
    ppAVar10 = ppAVar10 + 1;
    iVar8 = iVar8 + 1;
  } while ((int)ppAVar10 < ((unsigned)(uintptr_t)&DAT_008ca320));
  if (uVar16 != 0) {
    if (local_24[0] == '\0') {
LAB_00492e5e:
      actor->pExtra->aVoiceFile[0] = '\0';
    }
    else {
      if (background == 0) {
        iVar8 = SoundsLoadProcessStartSound((int)local_24,0x7f,2);
        actor->pExtra->nVoiceSound = iVar8;
        iVar8 = actor->pExtra->nVoiceSound;
        if (iVar8 == 0) {
          actor->pExtra->aVoiceFile[0] = '\0';
          goto LAB_00492e6b;
        }
        SoundsSetParam(iVar8,0x600,volume);
        if ((actor->dwFlags & 8) != 0) {
          iVar8 = actor->pExtra->nVoiceSound;
          goto LAB_00492dfb;
        }
      }
      else {
        iVar8 = SoundStartVoiceStream((int)local_24,volume,pan);
        if (iVar8 != 0) goto LAB_00492e5e;
        actor->pExtra->nVoiceSound = 10000;
        if ((actor->dwFlags & 8) != 0) {
          iVar8 = 10000;
LAB_00492dfb:
          sputRoom_SetSoundPosition(iVar8,actor->aPos,0x14,0x7f,0x41000000,0x3f4ccccd);
        }
      }
      uVar16 = 0xffffffff;
      pcVar9 = local_24;
      do {
        pcVar17 = pcVar9;
        if (uVar16 == 0) break;
        uVar16 = uVar16 - 1;
        pcVar17 = pcVar9 + 1;
        cVar3 = *pcVar9;
        pcVar9 = pcVar17;
      } while (cVar3 != '\0');
      uVar16 = ~uVar16;
      pcVar9 = pcVar17 + -uVar16;
      pcVar17 = actor->pExtra->aVoiceFile;
      for (uVar13 = uVar16 >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
        *(undefined4 *)pcVar17 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar17 = pcVar17 + 4;
      }
      for (uVar16 = uVar16 & 3; uVar16 != 0; uVar16 = uVar16 - 1) {
        *pcVar17 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar17 = pcVar17 + 1;
      }
      iVar8 = iMUSE_GetPhoneme(actor->pExtra->nVoiceSound,0);
      actor->pExtra->nLipSync = iVar8;
    }
LAB_00492e6b:
    actor->pExtra->nTalkTime = -1;
  }
  if ((uVar7 != 0) || (actor->pExtra->aVoiceFile[0] == '\0')) {
    pTVar11 = sputText_CreateActorText(actor,text_00,x,y);
    actor->pExtra->pText = pTVar11;
    if (actor->pExtra->aVoiceFile[0] == '\0') {
      uVar7 = 0xffffffff;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar3 = *text_00;
        text_00 = text_00 + 1;
      } while (cVar3 != '\0');
      actor->pExtra->nTalkTime = (~uVar7 - 1) * (0xb - g_nTextRate) * 0xf + 0x280;
    }
    sputText_AddToQueue(pTVar11,-1,0xd);
    ppAVar10 = g_pTalkingActors;
    if (background == 0) {
      do {
        pAVar5 = *ppAVar10;
        if ((((pAVar5 != (Actor *)0x0) && (pAVar5 != actor)) &&
            (pAVar5->pExtra->pText != (TextObject *)0x0)) && (pAVar5->pExtra->nVoiceSound == 10000))
        {
          puVar2 = &actor->pExtra->pText->dwFlags;
          *puVar2 = *puVar2 | 2;
          break;
        }
        ppAVar10 = ppAVar10 + 1;
      } while ((int)ppAVar10 < ((unsigned)(uintptr_t)&DAT_008ca320));
    }
    else {
      do {
        pAVar5 = *ppAVar10;
        if (((pAVar5 != (Actor *)0x0) && (pAVar5 != actor)) &&
           (pTVar11 = pAVar5->pExtra->pText, pTVar11 != (TextObject *)0x0)) {
          puVar2 = &pTVar11->dwFlags;
          *puVar2 = *puVar2 | 2;
        }
        ppAVar10 = ppAVar10 + 1;
      } while ((int)ppAVar10 < ((unsigned)(uintptr_t)&DAT_008ca320));
    }
  }
  if (((actor != (Actor *)0x0) && (pAVar6 = actor->pExtra, pAVar6 != (ActorExtra *)0x0)) &&
     ((pCVar12 = actor->pCostumes, pCVar12 != (CostumeNode *)0x0 && (pAVar6->nLipSync != 0)))) {
    ppvVar1 = &pCVar12->pMainModel;
    if (pCVar12 != (CostumeNode *)0x0) {
      while (pCVar12->pMainModel == *ppvVar1) {
        iVar8 = 1;
        piVar14 = pCVar12->aTalkChores;
        do {
          piVar14 = piVar14 + 1;
          if (-1 < *piVar14) break;
          iVar8 = iVar8 + 1;
        } while (iVar8 < 10);
        if ((iVar8 < 10) || (pCVar12 = pCVar12->pNext, pCVar12 == (CostumeNode *)0x0)) break;
      }
      if ((pCVar12 != (CostumeNode *)0x0) && (pCVar12->pMainModel == *ppvVar1)) goto LAB_00492fe7;
    }
    pAVar6->nLipSync = 0;
  }
LAB_00492fe7:
  if (((actor->pExtra->aVoiceFile[0] == '\0') || (actor->pExtra->nLipSync == 0)) &&
     (pCVar12 = actor->pCostumes, pCVar12 != (CostumeNode *)0x0)) {
    ppvVar1 = &pCVar12->pMainModel;
    do {
      if ((pCVar12->pMainModel != *ppvVar1) || (-1 < pCVar12->nMumbleChore)) break;
      pCVar12 = pCVar12->pNext;
    } while (pCVar12 != (CostumeNode *)0x0);
    if (((pCVar12 != (CostumeNode *)0x0) && (pCVar12->pMainModel == *ppvVar1)) &&
       (-1 < pCVar12->nMumbleChore)) {
      Cos_InstPlayChore(pCVar12->dwInstance,pCVar12->nMumbleChore,1,0);
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

void __cdecl sputActor_ShutUp(Actor *actor)

{
  void **ppvVar1;
  ActorExtra *pAVar2;
  TextObject *obj;
  int iVar3;
  CostumeNode *pCVar4;
  Actor **ppAVar5;
  
  if ((actor != (Actor *)0x0) && (pAVar2 = actor->pExtra, pAVar2 != (ActorExtra *)0x0)) {
    if (pAVar2->aVoiceFile[0] != '\0') {
      if (pAVar2->nVoiceSound == 10000) {
        SoundStopVoiceStream();
      }
      else {
        SoundsStopSound(pAVar2->nVoiceSound);
      }
    }
    obj = actor->pExtra->pText;
    if (obj != (TextObject *)0x0) {
      List_Unlink(obj);
    }
    pCVar4 = actor->pCostumes;
    if (pCVar4 != (CostumeNode *)0x0) {
      ppvVar1 = &pCVar4->pMainModel;
      if (pCVar4 != (CostumeNode *)0x0) {
        do {
          if ((pCVar4->pMainModel != *ppvVar1) || (-1 < pCVar4->nMumbleChore)) break;
          pCVar4 = pCVar4->pNext;
        } while (pCVar4 != (CostumeNode *)0x0);
        if (((pCVar4 != (CostumeNode *)0x0) && (pCVar4->pMainModel == *ppvVar1)) &&
           (-1 < pCVar4->nMumbleChore)) {
          iVar3 = Cos_InstChoreStatus(pCVar4->dwInstance,pCVar4->nMumbleChore);
          if (iVar3 != 0) {
            Cos_InstStopChore(pCVar4->dwInstance,pCVar4->nMumbleChore);
          }
        }
      }
      pCVar4 = actor->pCostumes;
      ppvVar1 = &pCVar4->pMainModel;
      if (pCVar4 != (CostumeNode *)0x0) {
        do {
          if ((pCVar4->pMainModel != *ppvVar1) || (-1 < pCVar4->aTalkChores[0])) break;
          pCVar4 = pCVar4->pNext;
        } while (pCVar4 != (CostumeNode *)0x0);
        if (((pCVar4 != (CostumeNode *)0x0) && (pCVar4->pMainModel == *ppvVar1)) &&
           (-1 < pCVar4->aTalkChores[0])) {
          Cos_InstCompleteChore(pCVar4->dwInstance,pCVar4->aTalkChores[0]);
        }
      }
    }
    ppAVar5 = g_pTalkingActors;
    do {
      if (*ppAVar5 == actor) {
        *ppAVar5 = (Actor *)0x0;
      }
      ppAVar5 = ppAVar5 + 1;
    } while ((int)ppAVar5 < ((unsigned)(uintptr_t)&DAT_008ca320));
    actor->pExtra->nLipSync = 0;
    actor->pExtra->aVoiceFile[0] = '\0';
    actor->pExtra->pText = (TextObject *)0x0;
    actor->pExtra->aMsgId[0] = '\0';
    actor->pExtra->nTalking = 0;
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
    WalkPlane_JumpOut((WalkPlane *)a2,walker);
    sputActor_SetActorPosition((Actor *)a1,walker);
  }
  return;
}

/* ---- 0x00493230  Actor_FollowPath ---- */
/* Actor_FollowPath(actor): walk to a point along the planned path (walker+0x2c next node); sets
   actor+8 bit 0 while the path lasts, clears it at the end. TurnActor and SetActorRot clear bit 0,
   ending the walk. */

void __cdecl Actor_FollowPath(Actor *actor)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float (*pafVar1) [3];
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  ActorExtra *pAVar6;
  float fVar7;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  pAVar6 = actor->pExtra;
  fVar5 = actor->aPos[0] - pAVar6->aWaypoint[0];
  fVar3 = actor->aPos[1] - pAVar6->aWaypoint[1];
  fVar4 = actor->aPos[2] - pAVar6->aWaypoint[2];
  fVar2 = pAVar6->flWalkRate;
  if (pAVar6->flWalkRate < 0.0) {
    fVar2 = -fVar2;
  }
  pAVar6 = actor->pExtra;
  fVar7 = sputTime_GetFrameTimeFlex();
  fVar2 = fVar7 * pAVar6->flTimeScale * fVar2 * 1.25;
  if (SQRT(fVar4 * fVar4 + fVar3 * fVar3 + fVar5 * fVar5) < fVar2) {
    do {
      if (pAVar6->nPathNodes <= pAVar6->nPathIndex) break;
      pAVar6->nPathIndex = pAVar6->nPathIndex + 1;
      sputActor_SetActorPosition(actor,actor->pExtra->aWaypoint);
      pAVar6 = actor->pExtra;
      pafVar1 = pAVar6->aPath + pAVar6->nPathIndex;
      pAVar6->aWaypoint[0] = (*pafVar1)[0];
      pAVar6->aWaypoint[1] = (*pafVar1)[1];
      pAVar6->aWaypoint[2] = (*pafVar1)[2];
      pAVar6 = actor->pExtra;
      fVar5 = actor->aPos[0] - pAVar6->aWaypoint[0];
      fVar3 = actor->aPos[1] - pAVar6->aWaypoint[1];
      fVar4 = actor->aPos[2] - pAVar6->aWaypoint[2];
    } while (SQRT(fVar4 * fVar4 + fVar3 * fVar3 + fVar5 * fVar5) < fVar2);
    pAVar6 = actor->pExtra;
    if (pAVar6->nPathIndex == pAVar6->nPathNodes) {
      actor->dwMoveFlags = actor->dwMoveFlags & 0xfffffffe;
      return;
    }
  }
  actor->dwMoveFlags = actor->dwMoveFlags | 1;
  Puck_PointAt(pAVar6->pPuck,pAVar6->aWaypoint,3.4028235e+38);
  sputActor_Forward(actor);
  return;
}
#undef local_10
#undef local_8
#undef local_c


/* ---- 0x004933c0  sputActor_SetWalkDominate ---- */
/* Original name sputActor_SetWalkDominate (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetActorWalkDominate; 1 matched neighbours agree, 0 disagree); was
   Actor_SetWalkDominate. */

void __cdecl sputActor_SetWalkDominate(Actor *actor,int dominate)

{
  actor->pExtra->nWalkDominate = dominate;
  return;
}

/* ---- 0x004933e0  sputActor_SetActorConstrain ---- */
/* Original name sputActor_SetActorConstrain (the remaster's GrimFandango (Linux): the only
   unmatched callee of Lua_SetActorConstrain; 1 matched neighbours agree, 0 disagree); was
   Actor_SetConstrain. */

void __cdecl sputActor_SetActorConstrain(Actor *actor,int param_2)

{
  Puck *this;
  
  if ((((actor->dwMoveFlags & 1) == 0) || (param_2 == 0)) &&
     (this = actor->pExtra->pPuck, this != (Puck *)0x0)) {
    Puck_Constrain(this,param_2);
  }
  return;
}

/* ---- 0x004934b0  Actor_IsVoicePlaying ---- */
int __cdecl Actor_IsVoicePlaying(Actor *actor)

{
  ActorExtra *pAVar1;
  uint uVar2;
  int iVar3;
  
  pAVar1 = actor->pExtra;
  if (pAVar1->aVoiceFile[0] == '\0') {
    return 0;
  }
  if (pAVar1->nVoiceSound == 10000) {
    uVar2 = ImGetParam(10000,0x100);
    return (uint)(0 < (int)uVar2);
  }
  iVar3 = SoundsIsSoundPlaying((int)pAVar1->aVoiceFile);
  return (uint)(0 < iVar3);
}

/* ---- 0x00493510  sputActor_ActorHasShadow ---- */
/* Original name sputActor_ActorHasShadow (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_ActorShadow; 1 matched neighbours agree, 0 disagree); was Actor_HasShadow. */

int __cdecl sputActor_ActorHasShadow(Actor *actor)

{
  ActorShadow *pAVar1;
  int iVar2;
  
  iVar2 = 0;
  pAVar1 = actor->pExtra->aShadows;
  do {
    if (pAVar1->nActive != 0) {
      return 1;
    }
    iVar2 = iVar2 + 1;
    pAVar1 = pAVar1 + 1;
  } while (iVar2 < 6);
  return 0;
}

/* ---- 0x00493540  sputActor_ActivateActorShadow ---- */
/* Original name sputActor_ActivateActorShadow (the remaster's GrimFandango (Linux): aligned call in
   sputLua_ActivateActorShadow); was Actor_ActivateShadow. */

void __cdecl sputActor_ActivateActorShadow(Actor *actor,int shadowIdx,int active)

{
  actor->pExtra->aShadows[shadowIdx].nActive = active;
  return;
}

/* ---- 0x00493570  sputActor_SetShadowPlane ---- */
/* Original name sputActor_SetShadowPlane (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetActorShadowPlane; 1 matched neighbours agree, 0 disagree); was
   Actor_SetShadowPlane. */

void __cdecl sputActor_SetShadowPlane(Actor *actor,char *param_2)

{
  ActorShadow *pAVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  WalkVertex *pWVar7;
  WalkPlane *pWVar8;
  
  pAVar1 = actor->pExtra->aShadows + actor->pExtra->nActiveShadow;
  pWVar8 = WalkPlane_PlaneNamed(param_2);
  if (pWVar8 != (WalkPlane *)0x0) {
    pAVar1->aPlane[0] = pWVar8->aNormal[0];
    pAVar1->aPlane[1] = pWVar8->aNormal[1];
    fVar2 = pWVar8->aNormal[2];
    pAVar1->aPlane[2] = fVar2;
    pWVar7 = pWVar8->aVerts[0];
    fVar3 = pWVar7->aPos[1];
    fVar4 = pWVar7->aPos[2];
    fVar5 = pWVar7->aPos[0];
    fVar6 = pAVar1->aPlane[1];
    pAVar1->nActive = 1;
    pAVar1->nValid = 0;
    pAVar1->aPlane[3] = -(fVar5 * pAVar1->aPlane[0] + fVar3 * fVar6 + fVar4 * fVar2);
  }
  return;
}

/* ---- 0x004935f0  sputActor_SetShadowPoint ---- */
/* Original name sputActor_SetShadowPoint (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetActorShadowPoint; 1 matched neighbours agree, 0 disagree); was
   Actor_SetShadowPoint. */

void __cdecl sputActor_SetShadowPoint(Actor *actor,float x,float y,float z)

{
  ActorExtra *pAVar1;
  int iVar2;
  
  pAVar1 = actor->pExtra;
  iVar2 = pAVar1->nActiveShadow;
  pAVar1->aShadows[iVar2].aPoint[0] = x;
  pAVar1->aShadows[iVar2].aPoint[1] = y;
  pAVar1->aShadows[iVar2].aPoint[2] = z;
  return;
}

/* ---- 0x00493630  sputActor_SetShadowValid ---- */
/* Original name sputActor_SetShadowValid (the remaster's GrimFandango (Linux): same body (stores
   the flag into the actor's shadow record shadowIdx * 0x54); called by sputLua_SetActorShadowValid
   in both builds); was Actor_SetShadowValid. */

void __cdecl sputActor_SetShadowValid(Actor *actor,int shadowIdx,int valid)

{
  actor->pExtra->aShadows[shadowIdx].nValid = valid;
  return;
}

/* ---- 0x00493660  sputActor_AddShadowClipPlane ---- */
/* Shadow records are 0x54 bytes at extra+(idx+6)*0x54 with the plane equation at +8 Original name
   sputActor_AddShadowClipPlane (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_AddShadowPlane; 1 matched neighbours agree, 0 disagree); was Actor_AddShadowPlane. */

void __cdecl sputActor_AddShadowClipPlane(Actor *actor,int shadowIdx,char *sectorName)

{
  WalkPlane *pWVar1;
  int iVar2;
  void **ppvVar3;
  
  pWVar1 = WalkPlane_PlaneNamed(sectorName);
  if (pWVar1 != (WalkPlane *)0x0) {
    iVar2 = 0;
    ppvVar3 = actor->pExtra->aShadows[shadowIdx].aClipPlanes;
    while (*ppvVar3 != (void *)0x0) {
      iVar2 = iVar2 + 1;
      ppvVar3 = ppvVar3 + 1;
      if (0xb < iVar2) {
        return;
      }
    }
    actor->pExtra->aShadows[shadowIdx].aClipPlanes[iVar2] = pWVar1;
  }
  return;
}

/* ---- 0x004936b0  sputActor_ResetShadows ---- */
/* Original name sputActor_ResetShadows (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_KillActorShadows; 1 matched neighbours agree, 0 disagree); was Actor_KillShadows.
    */

void __cdecl sputActor_ResetShadows(Actor *actor)

{
  int iVar1;
  ActorShadow *pAVar2;
  
  if ((actor != (Actor *)0x0) && (actor->pExtra != (ActorExtra *)0x0)) {
    pAVar2 = actor->pExtra->aShadows;
    for (iVar1 = 0x7e; iVar1 != 0; iVar1 = iVar1 + -1) {
      pAVar2->nActive = 0;
      pAVar2 = (ActorShadow *)&pAVar2->nValid;
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
   only unmatched caller of sputCostume_DrawMeshShadow; 1 matched neighbours agree, 0 disagree); was
   Actor_DrawShadows. */

void __cdecl sputCostume_DrawActorShadow(Actor *actor)

{
  int iVar1;
  float fVar2;
  ActorShadow *shadow;
  int iVar3;
  
  if (actor->pExtra != (ActorExtra *)0x0) {
    PerfBegin(0xb);
    iVar3 = 0x1f8;
    do {
      shadow = (ActorShadow *)((int)actor->pExtra->aLookAt + iVar3);
      if ((shadow->nActive != 0) &&
         ((iVar1 = shadow->nValid, iVar1 == 0 ||
          (((fVar2 = actor->aPos[1] * shadow->aPlane[1] +
                     actor->aPos[2] * shadow->aPlane[2] + actor->aPos[0] * shadow->aPlane[0] +
                     shadow->aPlane[3], iVar1 != -1 || (fVar2 <= 0.0)) &&
           ((iVar1 != 1 || (0.0 <= fVar2)))))))) {
        sputCostume_DrawMeshShadow(actor->pCostumes,shadow);
      }
      iVar3 = iVar3 + 0x54;
    } while (iVar3 < 0x3f0);
    PerfEnd(0xb);
  }
  return;
}

/* ---- 0x00493790  sputActor_GetOrientMatrix ---- */
/* Returns the actor's 12-float frame (position + 3x3 rotation), rebuilding it from pos/rot when
   dirty Original name sputActor_GetOrientMatrix (the remaster's GrimFandango (Linux): aligned call
   in sputActor_DrawToClean, sputActor_EnablePuck, sputRender_Update); was Actor_GetFrame. */

float * __cdecl sputActor_GetOrientMatrix(Actor *actor)

{
  if (actor->nMatrixDirty == 0) {
    rdMatrix_Build34(actor->aOrient,(uint *)actor->aRot,actor->aPos);
    actor->nMatrixDirty = 1;
  }
  return actor->aOrient;
}

/* ---- 0x004937c0  sputActor_DrawToClean ---- */
/* Lua ActorToClean: marks the actor's rectangle to be restored from the clean background Original
   name sputActor_DrawToClean (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_ActorToClean; 3 matched neighbours agree, 0 disagree); was Actor_ToClean. */

void __cdecl sputActor_DrawToClean(Actor *actor)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  float fVar6;
  void *pvVar7;
  code *pcVar8;
  float *pfVar9;
  float *pfVar10;
  int iVar11;
  undefined4 uVar12;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define fStack_c (*(float *)(_frame + (0x20 - 0xc)))
  #define fStack_8 (*(float *)(_frame + (0x20 - 0x8)))
  #define fStack_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  pvVar7 = sputRoom_GetCurrentRoom();
  iVar11 = *(int *)((int)pvVar7 + 0xb4);
  pvVar7 = sputRoom_GetCurrentRoom();
  iVar1 = *(int *)((int)pvVar7 + 0xac) + iVar11 * 300;
  iVar11 = *(int *)(*(int *)(*(int *)((int)pvVar7 + 0xac) + 0x48 + iVar11 * 300) + 4);
  if (iVar11 != 0) {
    uVar2 = *(undefined4 *)(iVar11 + 0x10);
    uVar3 = *(undefined4 *)(iVar11 + 4);
    pvVar7 = sputRender_CleanArtBuffer();
    *(void **)(*(int *)(*(int *)(iVar1 + 0x48) + 4) + 4) = pvVar7;
    pvVar7 = sputRender_CleanZBuffer();
    *(void **)(*(int *)(*(int *)(iVar1 + 0x48) + 4) + 0x10) = pvVar7;
    piVar4 = actor->pColormapRef;
    iVar11 = *piVar4;
    if (iVar11 == 0) {
      pvVar7 = sputRoom_GetCurrentRoom();
      iVar11 = *(int *)((int)pvVar7 + 0x88);
      pvVar7 = sputRoom_GetCurrentRoom();
      iVar5 = *(int *)((int)pvVar7 + 0x80);
      if (*(int *)(iVar5 + iVar11 * 0x34) == 0) {
        (*g_pStd_HS->pAssertFail)
                  (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
      }
      rdroid_SetColormap(*(uint *)(iVar5 + iVar11 * 0x34 + 4));
      pvVar7 = sputRoom_GetCurrentRoom();
      iVar11 = *(int *)((int)pvVar7 + 0x88);
      pvVar7 = sputRoom_GetCurrentRoom();
      piVar4 = (int *)(*(int *)((int)pvVar7 + 0x80) + iVar11 * 0x34);
      if (*piVar4 == 0) {
        (*g_pStd_HS->pAssertFail)
                  (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
      }
      iVar11 = piVar4[1];
    }
    else {
      if (iVar11 == 0) {
        (*g_pStd_HS->pAssertFail)
                  (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
      }
      rdroid_SetColormap(piVar4[1]);
      piVar4 = actor->pColormapRef;
      if (*piVar4 == 0) {
        (*g_pStd_HS->pAssertFail)
                  (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
      }
      iVar11 = piVar4[1];
    }
    iVar11 = iVar11 + 0x30;
    uVar12 = 0;
    pcVar8 = sputRender_SetPaletteFunc();
    (*pcVar8)(iVar11,uVar12);
    fVar6 = actor->flScale;
    if (fVar6 != 1.0) {
      pfVar10 = &fStack_c;
      fStack_c = fVar6;
      fStack_8 = fVar6;
      fStack_4 = fVar6;
      pfVar9 = sputActor_GetOrientMatrix(actor);
      rdMatrix_PreScale34(pfVar9,(uint)pfVar10);
    }
    pfVar10 = sputActor_GetOrientMatrix(actor);
    sputCostume_Draw3D(actor->pCostumes,pfVar10);
    actor->nMatrixDirty = 0;
    rdCache_Flush();
    *(undefined4 *)(*(int *)(*(int *)(iVar1 + 0x48) + 4) + 4) = uVar3;
    *(undefined4 *)(*(int *)(*(int *)(iVar1 + 0x48) + 4) + 0x10) = uVar2;
  }
  return;
}
#undef fStack_4
#undef fStack_8
#undef fStack_c
#undef local_10


/* ---- 0x00494690  Actor_CountCostumes ---- */
int __cdecl Actor_CountCostumes(Actor *actor)

{
  CostumeNode *pCVar1;
  int iVar2;
  
  iVar2 = 0;
  for (pCVar1 = actor->pCostumes; pCVar1 != (CostumeNode *)0x0; pCVar1 = pCVar1->pNext) {
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}

/* ---- 0x004946b0  sputActor_SetClipPlane ---- */
/* Original name sputActor_SetClipPlane (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetActorClipPlane; 1 matched neighbours agree, 1 disagree); was Actor_SetClipPlane.
    */

void __cdecl sputActor_SetClipPlane(Actor *actor,undefined4 *param_2,undefined4 *param_3)

{
  ActorExtra *pAVar1;
  
  if (actor->pExtra == (ActorExtra *)0x0) {
    sputActor_AllocateActorExtra(actor);
  }
  pAVar1 = actor->pExtra;
  pAVar1->aClipNormal[0] = PUN(float,*param_2);
  pAVar1->aClipNormal[1] = PUN(float,param_2[1]);
  pAVar1->aClipNormal[2] = PUN(float,param_2[2]);
  pAVar1 = actor->pExtra;
  pAVar1->aClipPoint[0] = PUN(float,*param_3);
  pAVar1->aClipPoint[1] = PUN(float,param_3[1]);
  pAVar1->aClipPoint[2] = PUN(float,param_3[2]);
  return;
}

/* ---- 0x00494710  sputActor_SetClipPlaneActive ---- */
/* Original name sputActor_SetClipPlaneActive (the remaster's GrimFandango (Linux): aligned call in
   sputLua_SetActorClipActive); was Actor_SetClipActive. */

void __cdecl sputActor_SetClipPlaneActive(Actor *actor,int param_2)

{
  if (actor->pExtra == (ActorExtra *)0x0) {
    sputActor_AllocateActorExtra(actor);
  }
  actor->pExtra->nClipPlaneActive = param_2;
  return;
}

/* ---- 0x00494780  sputActor_SetFrustrumCull ---- */
/* Original name sputActor_SetFrustrumCull (the remaster's GrimFandango (Linux): aligned call in
   sputActor_PushCostume, sputActor_SetCostume, sputLua_SetActorFrustrumCull); was
   Actor_SetFrustumCull. */

void __cdecl sputActor_SetFrustrumCull(Actor *actor,int param_2)

{
  void *pvVar1;
  uint uVar2;
  
  if (actor != (Actor *)0x0) {
    if (param_2 == 0) {
      uVar2 = actor->dwFlags & 0xfffffffb;
    }
    else {
      uVar2 = actor->dwFlags | 4;
    }
    actor->dwFlags = uVar2;
    if (actor->pCostumes != (CostumeNode *)0x0) {
      for (pvVar1 = actor->pCostumes->pComponents; pvVar1 != (void *)0x0;
          pvVar1 = *(void **)((int)pvVar1 + 400)) {
        *(int *)(*(int *)((int)pvVar1 + 0x40) + 0x44) = param_2;
      }
    }
  }
  return;
}

/* ---- 0x004947c0  sputActor_FreeActor ---- */
/* Removes the actor from its set, kills shadows, frees costumes, walker, extra and colormap
   reference Original name sputActor_FreeActor (the remaster's GrimFandango (Linux): aligned call in
   sputActor_Restore, sputActor_Shutdown); was Actor_Destroy. */

void __cdecl sputActor_FreeActor(Actor *actor)

{
  Puck *puck;
  
  if (actor->aSetName[0] != '\0') {
    sputRoom_RemoveActor(actor->aSetName,actor);
  }
  sputActor_ResetShadows(actor);
  sputCostume_FreeCostumeNodes(actor->pCostumes,0);
  actor->pCostumes = (CostumeNode *)0x0;
  if (actor->pExtra != (ActorExtra *)0x0) {
    puck = actor->pExtra->pPuck;
    if (puck != (Puck *)0x0) {
      Puck_Destruct(puck);
      Plat_Free(puck);
      actor->pExtra->pPuck = (Puck *)0x0;
    }
    (**(code **)(g_dwSputActHS + 0x24))(actor->pExtra);
    actor->pExtra = (ActorExtra *)0x0;
  }
  if (actor->pColormapRef != (void *)0x0) {
    Res_RemoveReference(actor->pColormapRef);
    (**(code **)(g_dwSputActHS + 0x24))(actor->pColormapRef);
    actor->pColormapRef = (void *)0x0;
  }
  actor->nInUse = 0;
  g_nNumActors = g_nNumActors + -1;
  return;
}

/* ---- 0x00494940  sputCostume_DrawMeshShadow ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Draws the actor's shadow onto one shadow plane: every mesh face of each model is projected
   through the plane, clipped to each of the plane's sectors and drawn with shadow.mat / shadow.cmp
   Original name sputCostume_DrawMeshShadow (the remaster's GrimFandango (Linux): the only function
   loading shadow.mat / shadow.cmp; caller sputCostume_DrawActorShadow and callees
   (TransformPoint34, segment-plane intersection, four shadow polygons) agree); was
   Actor_DrawShadowPlane. */

void __cdecl sputCostume_DrawMeshShadow(CostumeNode *costumeList,ActorShadow *shadow)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *out;
  void *pvVar1;
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
  
  if (costumeList != (CostumeNode *)0x0) {
    pvVar1 = costumeList->pComponents;
    local_fc[0] = 640.0;
    local_fc[1] = 480.0;
    local_e4[0] = 0.0;
    local_e4[2] = 0.0;
    for (; pvVar1 != (void *)0x0; pvVar1 = *(void **)((int)pvVar1 + 400)) {
      iVar2 = *(int *)((int)pvVar1 + 0x40);
      iVar3 = *(int *)(iVar2 + 4);
      if (((*(int *)((int)pvVar1 + 0x38) != 0) && (*(int *)((int)pvVar1 + 0x34) == 0)) &&
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
              rdMatrix_TransformPoint34
                        (out,(float *)(iVar7 + *(int *)(iVar5 + iVar4 * 0x7c + 0x58)),
                         (float *)(local_f4 + *(int *)(iVar2 + 0x20)));
              iVar6 = sputRender_SegmentPlaneIntersect
                                (out,shadow->aPoint,out,shadow->aPlane[0],shadow->aPlane[1],
                                 shadow->aPlane[2],shadow->aPlane[3]);
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
              rdroid_SetColormap((uint)g_pShadowColormap);
              if (g_nSputRender_b3DAcceleration != 0) {
                std3D_SetCurrentPalette((void *)((int)g_pShadowColormap + 0x30),0);
              }
              sputCostume_OutputShadowPoly(local_c0,4,local_fc,local_e4,shadow);
              sputCostume_OutputShadowPoly(local_90,4,local_fc,local_e4,shadow);
              sputCostume_OutputShadowPoly(local_60,4,local_fc,local_e4,shadow);
              sputCostume_OutputShadowPoly(local_30,4,local_fc,local_e4,shadow);
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
      sputRender_MarkDirtyRect((int *)&local_d0,1);
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


/* ---- 0x00495080  sputCostume_Draw3D ---- */
/* Original name sputCostume_Draw3D (the remaster's GrimFandango (Linux): aligned call in
   sputActor_DrawToClean, sputRender_Update); was Actor_DrawCostumes. */

void sputCostume_Draw3D(undefined4 param_1,undefined4 param_2)

{
  ((code *)sputCostume_InternalDraw3D)(param_1,param_2,0,0);
  return;
}

/* ---- 0x004950a0  sputCostume_InternalDraw3D ---- */
/* Draws the meshes of an actor's costume. Enables the user clip plane when extra+0x3fc != 0 (normal
   extra+0x400, point extra+0x40c). For a model hung on a node (component+0x44 != 0) whose node
   index (+0x48) equals extra+0x420 (SetActorInvClipNode) the plane through the actor position
   (actor+0xc) with the second row of the actor matrix (actor+0x44..0x4c, the facing) as normal is
   used for that mesh only, then the clip is switched off. Meshes are clipped per polygon in eye
   space (MeshFace_Draw 0x40d880 -> Polygon_ClipToPlane 0x44ea50: keep dist >= 0); Mesh_Draw
   0x40d230 skips a mesh whose centre is more than its radius behind the plane. Original name
   sputCostume_InternalDraw3D (the remaster's GrimFandango (Linux): aligned call in
   sputCostume_Draw3D); was Actor_DrawCostumeMeshes. */

void sputCostume_InternalDraw3D(int *param_1,float *param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Actor *actor;
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define uStack_1c (*(undefined4 *)(_frame + (0x30 - 0x1c)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define iStack_10 (*(int *)(_frame + (0x30 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x30 - 0xc)))
  #define iStack_8 (*(int *)(_frame + (0x30 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x30 - 0x4)))
  
  iVar4 = param_1[1];
  for (piVar1 = param_1; (piVar1 != (int *)0x0 && (piVar1[1] == iVar4));
      piVar1 = (int *)piVar1[0x2c]) {
    Costume_ApplyComponentState((void *)*piVar1);
  }
  iVar4 = Cos_InstGetUserData(*param_1);
  actor = g_pActors + iVar4;
  if ((actor->pExtra == (ActorExtra *)0x0) || (actor->pExtra->nClipPlaneActive == 0)) {
    rdModel3_ActivateClipPlane(0);
  }
  else {
    rdModel3_ActivateClipPlane(1);
    rdModel3_SetClipPlane((uint *)actor->pExtra->aClipNormal,(uint *)actor->pExtra->aClipPoint);
  }
  Costume_ApplyScale(actor,(void *)param_1[2]);
  iVar4 = param_1[2];
  do {
    if (iVar4 == 0) {
      sputCostume_DrawActorShadow(actor);
      iVar4 = param_1[1];
      for (piVar1 = param_1; (piVar1 != (int *)0x0 && (piVar1[1] == iVar4));
          piVar1 = (int *)piVar1[0x2c]) {
        Costume_ApplyComponentState((void *)*piVar1);
      }
      Costume_ApplyScale(actor,(void *)param_1[2]);
      return;
    }
    if (*(int *)(iVar4 + 0x38) != 0) {
      g_nRdCache_ulcExtent = 0x280;
      g_nDrawBoxMinY = 0x1e0;
      g_nRdCache_lrcExtent = 0;
      g_nDrawBoxMaxY = 0;
      iVar6 = iVar4;
      if (*(int *)(iVar4 + 0x44) == 0) {
        if (*(uint *)(iVar4 + 0x4c) == 0) {
LAB_004951ab:
          if (g_nSputRender_b3DAcceleration == 0) goto LAB_004951b3;
        }
        else {
          rdroid_SetColormap(*(uint *)(iVar4 + 0x4c));
          if (g_nSputRender_b3DAcceleration != 0) {
            std3D_SetCurrentPalette((void *)(*(int *)(iVar4 + 0x4c) + 0x30),0);
            goto LAB_004951ab;
          }
LAB_004951b3:
          puVar5 = Render_GetBackBuffer();
          stdDisplay_VBufferLock(puVar5);
        }
        iVar6 = rdThing_Draw(*(void **)(iVar4 + 0x40),param_2);
        if ((iVar6 == 0) || (actor == (Actor *)0x0)) {
          actor->nScreenBoxValid = 0;
        }
        else {
          actor->nScreenBoxValid = 1;
        }
        if (g_nSputRender_b3DAcceleration == 0) {
          puVar5 = Render_GetBackBuffer();
          stdDisplay_VBufferUnlock(puVar5);
        }
      }
      else {
        for (; (iVar6 != 0 && (*(int *)(iVar6 + 0x4c) == 0)); iVar6 = *(int *)(iVar6 + 0x44)) {
        }
        if (((iVar6 != 0) && (*(uint *)(iVar6 + 0x4c) != 0)) &&
           (rdroid_SetColormap(*(uint *)(iVar6 + 0x4c)), g_nSputRender_b3DAcceleration != 0)) {
          std3D_SetCurrentPalette((void *)(*(int *)(iVar6 + 0x4c) + 0x30),0);
        }
        sputCostume_BuildThingStateMatrices(*(void **)(iVar4 + 0x44),param_2);
        iVar7 = *(int *)(*(int *)(iVar4 + 0x44) + 0x40);
        iVar6 = *(int *)(*(int *)(iVar7 + 4) + 0x58) + *(int *)(iVar4 + 0x48) * 0xb8;
        iVar2 = *(int *)(*(int *)(*(int *)(iVar4 + 0x40) + 4) + 0x58);
        if (g_nSputRender_b3DAcceleration == 0) {
          puVar5 = Render_GetBackBuffer();
          stdDisplay_VBufferLock(puVar5);
        }
        if ((*(int *)(iVar4 + 0x3c) != 0) && (**(int **)(iVar4 + 0x40) != 4)) {
          iVar3 = (*(int **)(iVar4 + 0x40))[1];
          uStack_1c = *(undefined4 *)(iVar3 + 0x84);
          uStack_18 = *(undefined4 *)(iVar3 + 0x88);
          uStack_14 = *(undefined4 *)(iVar3 + 0x8c);
          *(undefined4 *)(iVar3 + 0x84) = 0;
          *(undefined4 *)(iVar3 + 0x88) = 0;
          *(undefined4 *)(iVar3 + 0x8c) = 0;
          *(float *)(iVar2 + 100) = *(float *)(iVar2 + 100) - *(float *)(iVar6 + 100);
          *(float *)(iVar2 + 0x68) = *(float *)(iVar2 + 0x68) - *(float *)(iVar6 + 0x68);
          *(float *)(iVar2 + 0x6c) = *(float *)(iVar2 + 0x6c) - *(float *)(iVar6 + 0x6c);
        }
        actor->nScreenBoxValid = 0;
        if ((actor->pExtra != (ActorExtra *)0x0) &&
           (actor->pExtra->nInvClipNode == *(int *)(iVar4 + 0x48))) {
          rdModel3_ActivateClipPlane(1);
          rdModel3_SetClipPlane((uint *)(actor->aOrient + 3),(uint *)actor->aPos);
        }
        iVar7 = rdThing_Draw(*(void **)(iVar4 + 0x40),
                             (float *)(*(int *)(iVar7 + 0x20) + *(int *)(iVar4 + 0x48) * 0x30));
        if ((iVar7 != 0) && (actor != (Actor *)0x0)) {
          actor->nScreenBoxValid = 1;
        }
        if ((actor->pExtra != (ActorExtra *)0x0) &&
           (actor->pExtra->nInvClipNode == *(int *)(iVar4 + 0x48))) {
          rdModel3_ActivateClipPlane(0);
        }
        if ((*(int *)(iVar4 + 0x3c) != 0) && (**(int **)(iVar4 + 0x40) != 4)) {
          *(float *)(iVar2 + 100) = *(float *)(iVar6 + 100) + *(float *)(iVar2 + 100);
          *(float *)(iVar2 + 0x68) = *(float *)(iVar6 + 0x68) + *(float *)(iVar2 + 0x68);
          *(float *)(iVar2 + 0x6c) = *(float *)(iVar6 + 0x6c) + *(float *)(iVar2 + 0x6c);
          iVar6 = *(int *)(*(int *)(iVar4 + 0x40) + 4);
          *(undefined4 *)(iVar6 + 0x84) = uStack_1c;
          *(undefined4 *)(iVar6 + 0x88) = uStack_18;
          *(undefined4 *)(iVar6 + 0x8c) = uStack_14;
        }
        if (g_nSputRender_b3DAcceleration == 0) {
          puVar5 = Render_GetBackBuffer();
          stdDisplay_VBufferUnlock(puVar5);
        }
      }
      piVar1 = actor->pColormapRef;
      iVar6 = *piVar1;
      if (iVar6 != 0) {
        if (iVar6 == 0) {
          (*g_pStd_HS->pAssertFail)
                    (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
        }
        rdroid_SetColormap(piVar1[1]);
        if (g_nSputRender_b3DAcceleration != 0) {
          piVar1 = actor->pColormapRef;
          if (*piVar1 == 0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
          }
          std3D_SetCurrentPalette((void *)(piVar1[1] + 0x30),0);
        }
      }
      iStack_10 = g_nRdCache_ulcExtent;
      iStack_8 = g_nRdCache_lrcExtent - g_nRdCache_ulcExtent;
      iStack_c = g_nDrawBoxMinY;
      iStack_4 = g_nDrawBoxMaxY - g_nDrawBoxMinY;
      sputRender_MarkDirtyRect(&iStack_10,1);
      if ((*(int *)(iVar4 + 0x40) == param_1[1]) && (actor != (Actor *)0x0)) {
        actor->aScreenBox[0] = iStack_10;
        actor->aScreenBox[1] = iStack_c;
        actor->aScreenBox[2] = iStack_8;
        actor->aScreenBox[3] = iStack_4;
      }
    }
    iVar4 = *(int *)(iVar4 + 400);
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


/* ---- 0x004a5eb0  sputRoom_RemoveActor ---- */
/* Original name sputRoom_RemoveActor (the remaster's GrimFandango (Linux): aligned call in
   sputActor_FreeActor, body similarity); was Actor_RemoveFromSet. */

void __cdecl sputRoom_RemoveActor(char *setName,void *actor)

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
        if (g_pActors + *piVar3 == actor) break;
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

/* ---- 0x004a5f60  sputRoom_AddActor ---- */
/* sputRoom.cpp: moves the actor into the named set's actor list (actor+0x7c holds the set name)
   Original name sputRoom_AddActor (the remaster's GrimFandango (Linux): aligned call in
   sputActor_Restore, sputLua_PutActorInSetL); was Actor_PutInSet. */

void __cdecl sputRoom_AddActor(Actor *actor,char *setName)

{
  char *setName_00;
  byte bVar1;
  Actor *pAVar2;
  int iVar3;
  void *pvVar4;
  int *piVar5;
  byte *pbVar6;
  bool bVar7;
  
  if ((actor != (Actor *)0x0) &&
     (pbVar6 = (byte *)(setName + 0x7c), pAVar2 = actor, pbVar6 != (byte *)0x0)) {
    do {
      bVar1 = *(byte *)&pAVar2->pColormapRef;
      bVar7 = bVar1 < *pbVar6;
      if (bVar1 != *pbVar6) {
LAB_004a5fa1:
        iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_004a5fa6;
      }
      if (bVar1 == 0) break;
      bVar1 = *(byte *)((int)&pAVar2->pColormapRef + 1);
      bVar7 = bVar1 < pbVar6[1];
      if (bVar1 != pbVar6[1]) goto LAB_004a5fa1;
      pbVar6 = pbVar6 + 2;
      pAVar2 = (Actor *)((int)&pAVar2->pColormapRef + 2);
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_004a5fa6:
    if (iVar3 == 0) {
      return;
    }
  }
  setName_00 = setName + 0x7c;
  if ((setName_00 != (char *)0x0) || (actor != (Actor *)0x0)) {
    if ((setName != (char *)0x0) && (setName_00 != (char *)0x0)) {
      sputRoom_RemoveActor(setName_00,setName);
    }
    if (actor == (Actor *)0x0) {
      setName[0x68] = '\0';
      setName[0x69] = '\0';
      setName[0x6a] = '\0';
      setName[0x6b] = '\0';
      return;
    }
    pvVar4 = (void *)Set_FindNameInList(actor);
    if (pvVar4 == (void *)0x0) {
      pvVar4 = Set_NormalizeName((char *)actor);
    }
    for (piVar5 = *(int **)((int)pvVar4 + 0x80); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[2]) {
      if (g_pActors + *piVar5 == (Actor *)setName) {
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

float __thiscall Puck_GetYawToPoint(Puck *this,float *point)

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
  if (this->pSector != (WalkPlane *)0x0) {
    WalkPlane_Project(this->pSector,(int)&local_18);
  }
  Puck_InvXform(this,&local_18);
  rdVector_Normalize3Acc(&local_18);
  fVar2 = stdMath_ArcSin3(local_14);
  point = PUN(float *,(float)(90.0 - fVar2));
  if (0.0 < local_18) {
    point = PUN(float *,(float)(PUN(float,point) * -1.0));
  }
  puVar1 = Puck_Rot(this);
  return *(float *)(puVar1 + 4) + PUN(float,point);
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c

#endif

