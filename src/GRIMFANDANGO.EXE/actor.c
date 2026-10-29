/* GRIMFANDANGO.EXE :: actor.c
 * functions 0x00485290 .. 0x004a8500 (58 functions)
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
  int iVar1;
  float *b;
  int iVar2;
  int iVar3;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  if (*(int *)((int)param_1 + 0xa4) != 0) {
    if (*(int *)(*(int *)((int)param_1 + 0xa4) + 0x1b4) != 0) {
      Walker_DrawDebugAxes(UINT_008c97e0 & 0xffff);
    }
    if ((*(byte *)((int)param_1 + 8) & 1) != 0) {
      iVar1 = *(int *)((int)param_1 + 0xa4);
      iVar3 = 0;
      if (*(int *)(iVar1 + 0x44) != 1 && -1 < *(int *)(iVar1 + 0x44) + -1) {
        iVar2 = 0x48;
        do {
          rdPrimit3_DrawLine(iVar2 + iVar1,iVar2 + 0xc + iVar1,0,0,0,0,UINT_008c97d4 & 0xffff,
                             0xffffffff);
          iVar1 = *(int *)((int)param_1 + 0xa4);
          iVar3 = iVar3 + 1;
          iVar2 = iVar2 + 0xc;
        } while (iVar3 < *(int *)(iVar1 + 0x44) + -1);
      }
    }
    if (*(int *)(*(int *)((int)param_1 + 0xa4) + 0x3f8) != 0) {
      iVar1 = *(int *)(*(int *)(*(int *)((int)param_1 + 0xa0) + 4) + 4);
      b = Actor_GetFrame(param_1);
      Vec3_Sub(local_c,(float *)(iVar1 + 0x78),b);
      ((void (*)(float *, float, undefined4, int, int))rdPrimit3_DrawPoint)(local_c,*(float *)(iVar1 + 0x5c) *
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
  char *pcVar2;
  void *pvVar3;
  int iVar4;
  int unaff_ESI;
  uint *puVar5;
  int unaff_EDI;
  uint *puVar6;
  #define local_5c (*(uint *)(_frame + (0x70 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define local_50 (*(uint *)(_frame + (0x70 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0x70 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x70 - 0x48)))
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
  local_50 = g_nSubtitleDefaultX;
  local_48 = UINT_004e8490;
  local_34 = UINT_008a94c0;
  puVar5 = &g_SubtitleTextCtx;
  puVar6 = &local_30;
  for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  local_4c = g_nSubtitleDefaultY;
  local_44 = UINT_004e8494;
  local_2c = (uint)&local_40;
  local_40 = 0;
  local_3c = 0;
  local_1c = *(uint *)(*(int *)((int)actor + 0xa4) + 0x418);
  local_18 = 0;
  local_14 = 0;
  if ((*(int *)((int)actor + 0x68) == 0) || (UINT_008a8c40 == 3)) {
    puVar5 = &local_50;
    if ((*(int *)((int)actor + 0xa0) == 0) || ((*(byte *)((int)actor + 4) & 2) != 0)) {
      pcVar2 = Set_GetCurrentName();
      iVar4 = _stricmp((int)actor + 0x7c,pcVar2);
      if (iVar4 == 0) {
        iVar4 = rdCamera_ProjectPoint((float *)((int)actor + 0xc),(float *)&local_5c);
        if (iVar4 != 0) {
          local_50 = local_5c;
          local_4c = local_58;
        }
      }
    }
  }
  else {
    puVar5 = (void *)((int)actor + 0x6c);
  }
  actor = puVar5;
  iVar4 = Text_MeasureWidth(&local_30,text);
  iVar4 = iVar4 / 2;
  if (x == -1) {
    x = *(int *)((int)actor + 8) / 2 + *(int *)actor;
  }
  if (x - iVar4 < 0x28) {
    x = iVar4 + 0x28;
  }
  if ((int)(UINT_008a94bc - 0x28) < iVar4 + x) {
    x = (UINT_008a94bc - iVar4) - 0x28;
  }
  local_20 = *(uint *)(*(int *)local_28 + 8);
  local_24 = x;
  iVar4 = Text_MeasureHeight(&local_30,text);
  if (y == -1) {
    y = *(int *)((int)actor + 4) - iVar4;
  }
  if (y < 10) {
    y = 10;
  }
  if ((int)(UINT_008a94c0 - 10) < y + iVar4) {
    y = (UINT_008a94c0 - iVar4) + -10;
  }
  local_20 = *(int *)(*(int *)local_28 + 8) + y;
  local_24 = x;
  pvVar3 = TextObject_New(&local_30,text,unaff_EDI,unaff_ESI);
  *(void **)((int)pvVar3 + 0x254) = pvVar1;
  *(uint *)((int)pvVar1 + 4) = *(uint *)((int)pvVar1 + 4) | 4;
  return pvVar3;
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
#undef local_48
#undef local_4c
#undef local_50
#undef local_58
#undef local_5c

#endif


/* ---- 0x0048f930  Actor_SetCostume ---- */
/* Lua SetActorCostume: replaces the whole costume stack with one costume */

int __cdecl Actor_SetCostume(void *actor,char *name,int param_3)

{
  void *costumeRes;
  void *pvVar1;
  
  if ((name == (char *)0x0) || (param_3 != 0)) {
    costumeRes = (void *)0x0;
    pvVar1 = *(void **)((int)actor + 0xa0);
  }
  else {
    costumeRes = Resource_Load(0x54534f43,name);
    if (costumeRes == (void *)0x0) {
      return 0;
    }
    param_3 = 0;
    pvVar1 = *(void **)((int)actor + 0xa0);
  }
  pvVar1 = Costume_ReplaceTop(pvVar1,costumeRes,param_3);
  *(void **)((int)actor + 0xa0) = pvVar1;
  Cos_InstSetUserData(**(undefined4 **)((int)actor + 0xa0),((int)actor - (int)g_pActorTable) / 0xa8)
  ;
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
      Math_SinCosTable(fVar3 * 0.5,&actor,iVar1 + 0x24);
    }
  }
  return;
}
#undef local_14


/* ---- 0x0048fa60  Actor_CanSeePoint ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* True when the point lies within the head joint's view cone (cosine threshold at costume+0x24 set
   by Actor_SetHead) */

int __cdecl Actor_CanSeePoint(void *actor,float *point,float *outDistance)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float *pfVar3;
  float fVar4;
  uint uVar5;
  undefined1 *puVar6;
  #define local_48 (*(uint *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x60 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x60 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x60 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x60 - 0x34)))
  #define local_30 (*(undefined1 (*)[36])(_frame + (0x60 - 0x30)))
  #define local_c (*(uint *)(_frame + (0x60 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x60 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x60 - 0x4)))
  
  iVar1 = *(int *)((int)actor + 0xa0);
  if (((iVar1 != 0) && (uVar5 = *(uint *)(iVar1 + 0xc), -1 < (int)uVar5)) &&
     (*(int *)(iVar1 + 4) != 0)) {
    puVar6 = local_30;
    pfVar3 = Actor_GetFrame(actor);
    rdPuppet_BuildJointMatrices(*(void **)(iVar1 + 4),pfVar3,uVar5,(uint)puVar6);
    local_3c = (uint)(*point - (float)local_c);
    local_38 = (uint)(point[1] - (float)local_8);
    local_34 = (uint)(point[2] - (float)local_4);
    fVar4 = Vec3_Normalize((float *)&local_3c);
    local_48 = local_3c;
    *outDistance = fVar4;
    local_44 = local_38;
    local_40 = 0;
    Vec3_Normalize((float *)&local_48);
    pfVar3 = Actor_GetFrame(actor);
    fVar4 = pfVar3[3] * (float)local_48;
    pfVar3 = Actor_GetFrame(actor);
    fVar2 = pfVar3[4] * (float)local_44;
    pfVar3 = Actor_GetFrame(actor);
    if (*(float *)(iVar1 + 0x24) <= pfVar3[5] * (float)local_40 + fVar2 + fVar4) {
      return 1;
    }
  }
  return 0;
}
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_4
#undef local_40
#undef local_44
#undef local_48
#undef local_8
#undef local_c

#endif


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

/* ---- 0x0048fbd0  Actor_TurnKey ---- */
/* Actor_TurnKey(actor, dir): the TurnActor builtin. Walker extra struct at actor+0xa4: +0x1c turn
   rate (deg/s, default 135, set by SetActorTurnRate), +0x41c time scale, +0x28 angle still to turn.
   Turn per press = rate * frameSeconds * timescale * dir; the key is accepted (+0x10 = +-1) only
   when |+0x28| <= 2 * that amount, i.e. the visible heading has caught up. Creates the walker
   (Actor_CreateWalker) if it does not exist. */

void Actor_TurnKey(int param_1,float param_2)

{
  float fVar1;
  int iVar2;
  float fVar3;
  
  iVar2 = *(int *)(param_1 + 0xa4);
  fVar3 = Timer_GetFrameSeconds();
  fVar3 = *(float *)(iVar2 + 0x1c) * fVar3 * *(float *)(iVar2 + 0x41c) * param_2;
  if (*(int *)(iVar2 + 0x1b4) == 0) {
    Actor_CreateWalker(param_1,1);
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

/* ---- 0x0048fc80  Actor_WalkForward ---- */
/* Actor_WalkForward(actor): creates the walker if missing and sets extra+0xc (walk forward this
   frame), consumed by Actor_UpdateWalker. */

void Actor_WalkForward(int param_1)

{
  Timer_GetFrameSeconds();
  if (*(int *)(*(int *)(param_1 + 0xa4) + 0x1b4) == 0) {
    Actor_CreateWalker(param_1,1);
  }
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0xc) = 1;
  return;
}

/* ---- 0x0048fd90  Actor_UpdateMovement ---- */
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
      (*g_pSvcMain->pAssertFail)
                (s_Bad_costume_Reference_004e9e90,s_main_sputResource_h_004e80a8,0xb8);
    }
    Cos_InstRescue(**(undefined4 **)((int)param_1 + 0xa0),*(undefined4 *)(iVar1 + 0x80));
  }
  if ((*(byte *)((int)param_1 + 8) & 1) != 0) {
    Actor_FollowPath(param_1);
  }
  if ((*(int *)((int)param_1 + 0xa4) != 0) && (*(int *)(*(int *)((int)param_1 + 0xa4) + 0x1b4) != 0)
     ) {
    Actor_UpdateWalker(param_1);
  }
  Actor_UpdateMoveChores(param_1);
  Costume_UpdateAll(*(void **)((int)param_1 + 0xa0),param_2);
  if ((*(byte *)((int)param_1 + 8) & 2) != 0) {
    Actor_UpdateLookAt(param_1,param_2);
  }
  if ((*(byte *)((int)param_1 + 4) & 0x10) != 0) {
    Actor_PuckOrient(PUN(float,param_1));
  }
  return;
}

/* ---- 0x0048fe80  Actor_UpdateLookAt ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
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
  uint uVar11;
  #define fStack_c8 (*(float *)(_frame + (0xe0 - 0xc8)))
  #define local_c4 (*(uint *)(_frame + (0xe0 - 0xc4)))
  #define local_c0 (*(uint *)(_frame + (0xe0 - 0xc0)))
  #define local_bc (*(uint *)(_frame + (0xe0 - 0xbc)))
  #define local_b8 (*(uint *)(_frame + (0xe0 - 0xb8)))
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
    (**(code **)(UINT_008ca32c + 0x18))
              (s_pActor__pExtra_004e9ea8,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x47a);
  }
  if (((iVar1 != 0) && (piVar8 = (int *)(iVar1 + 0xc), -1 < *(int *)(iVar1 + 0xc))) &&
     (*(int *)(iVar1 + 4) != 0)) {
    local_c0 = 0;
    local_bc = 0x3f800000;
    local_b8 = 0;
    if (*(int *)((int)actor + 0x68) == 0) {
      pfVar6 = Actor_GetFrame(actor);
      rdPuppet_UpdateFrame(*(void **)(iVar1 + 4),pfVar6);
    }
    uVar11 = *(uint *)(iVar1 + 0x14);
    pfVar6 = afStack_60;
    pfVar7 = Actor_GetFrame(actor);
    rdPuppet_BuildJointMatrices(*(void **)(iVar1 + 4),pfVar7,uVar11,(uint)pfVar6);
    Matrix_Transpose(afStack_90,afStack_60);
    pfVar6 = *(float **)((int)actor + 0xa4);
    if (((*pfVar6 == 0.0) && (pfVar6[1] == 0.0)) && (pfVar6[2] == 0.0)) {
      pfVar6 = afStack_90;
      bVar5 = true;
      pfVar7 = Actor_GetFrame(actor);
      Vec3_Copy(afStack_a8,pfVar7 + 3,pfVar6);
    }
    else {
      Vec3_Sub(afStack_a8,pfVar6,afStack_90);
      Vec3_Normalize(afStack_a8);
    }
    Vec3_Cross(afStack_9c,(float *)&local_c0,afStack_a8);
    Vec3_Normalize(afStack_9c);
    fStack_c8 = *(float *)(iVar1 + 0x18) * dt;
    fVar10 = Vec3_Dot((float *)&local_c0,afStack_a8);
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
    Vec3_Rotate3x3((float *)&local_c0,afStack_30);
    Matrix_GetAngles((float *)&local_c0,&fStack_b4);
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
#undef local_b8
#undef local_bc
#undef local_c0
#undef local_c4

#endif


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
  undefined4 *puVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  
  iVar3 = *(int *)((int)actor + 0xa4);
  if (*(int *)(iVar3 + 0x1c4) == 0) {
    return;
  }
  if (((*(char *)(iVar3 + 0x1dc) != '\0') && (*(int *)(iVar3 + 0x1f0) != 0)) &&
     (*(int *)((int)actor + 0xa0) != 0)) {
    iVar3 = iMUSE_GetPhoneme(*(undefined4 *)(iVar3 + 0x1c8),0);
    if (iVar3 == 0) {
      Actor_ShutUp(actor);
    }
    else {
      uVar2 = Phoneme_ToTalkChore(actor,iVar3);
      puVar4 = *(undefined4 **)((int)actor + 0xa0);
      piVar1 = puVar4 + 1;
      if (puVar4 != (undefined4 *)0x0) {
        do {
          if ((puVar4[1] != *piVar1) || (-1 < (int)puVar4[CONCAT22(extraout_var,uVar2) + 0xe]))
          break;
          puVar4 = (undefined4 *)puVar4[0x2c];
        } while (puVar4 != (undefined4 *)0x0);
        if ((puVar4 != (undefined4 *)0x0) && (puVar4[1] == *piVar1)) {
          Cos_InstCompleteChore(*puVar4,puVar4[CONCAT22(extraout_var,uVar2) + 0xe]);
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
  Actor_ShutUp(actor);
  return;
}
#endif


/* ---- 0x00490320  Actor_SetSelected ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua SetSelectedActor; returns the handle or -1 */

int __cdecl Actor_SetSelected(int handle)

{
  int iVar1;
  int unaff_retaddr;
  
  iVar1 = -1;
  if (g_pSelectedActor != (void *)0x0) {
    iVar1 = Actor_GetHandle(g_pSelectedActor,unaff_retaddr);
  }
  if ((-1 < handle) && (handle < g_nActorCapacity)) {
    g_pSelectedActor = (void *)((int)g_pActorTable + handle * 0xa8);
  }
  return iVar1;
}
#endif


/* ---- 0x00490360  Actor_FromHandle ---- */
void * Actor_FromHandle(int param_1)

{
  return (void *)((int)g_pActorTable + param_1 * 0xa8);
}

/* ---- 0x00490380  Actor_GetHandle ---- */
int __cdecl Actor_GetHandle(void *actor,int tag)

{
  return ((int)actor - (int)g_pActorTable) / 0xa8;
}

/* ---- 0x004903a0  Actor_Create ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Lua LoadActor: allocates an actor record and returns its handle (-1 when full) */

int Actor_Create(void)

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
  if (0 < g_nActorCapacity) {
    piVar4 = (int *)((int)g_pActorTable + 0x9c);
    do {
      if (*piVar4 == 0) {
        puVar5 = (undefined4 *)((int)g_pActorTable + iVar2 * 0xa8);
        break;
      }
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 0x2a;
    } while (iVar2 < g_nActorCapacity);
  }
  if (puVar5 == (undefined4 *)0x0) {
    iVar2 = 0;
    do {
      if (*(int *)((int)&g_pTalkingActors + iVar2) != 0) {
        *(int *)((int)aiStack_10 + iVar2) =
             (*(int *)((int)&g_pTalkingActors + iVar2) - (int)g_pActorTable) / 0xa8;
      }
      iVar2 = iVar2 + 4;
    } while (iVar2 < 0x10);
    if (g_pSelectedActor != (void *)0x0) {
      local_14 = ((int)g_pSelectedActor - (int)g_pActorTable) / 0xa8;
    }
    g_pActorTable =
         (void *)(**(code **)(UINT_008ca32c + 0x28))
                           (g_pActorTable,(g_nActorCapacity + 0x20) * 0xa8,
                            s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x5f6);
    puVar5 = (undefined4 *)((int)g_pActorTable + g_nActorCapacity * 0xa8);
    for (iVar2 = 0x540; pvVar1 = g_pActorTable, iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    iVar2 = 0;
    puVar5 = (undefined4 *)((int)g_pActorTable + g_nActorCapacity * 0xa8);
    g_nActorCapacity = g_nActorCapacity + 0x20;
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
  g_nActorCount = g_nActorCount + 1;
  puVar3 = puVar5;
  for (iVar2 = 0x2a; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar5[0xd] = 1;
  Matrix_Identity((float *)(puVar5 + 0xe));
  puVar5[0xc] = 0x3f800000;
  puVar5[0x28] = 0;
  puVar3 = (undefined4 *)
           (**(code **)(UINT_008ca32c + 0x20))
                     (0x34,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x60e);
  *puVar5 = puVar3;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar5[0x27] = 1;
  return ((int)puVar5 - (int)g_pActorTable) / 0xa8;
}
#undef aiStack_10
#undef local_14


/* ---- 0x00490580  Actor_CreateExtra ---- */
/* Source: Engine/sputActor.cpp (lines 1561-1564, from __FILE__/__LINE__ passed to the allocator) */

void Actor_CreateExtra(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 0xa4) != 0)) {
    (**(code **)(UINT_008ca32c + 0x18))
              (s_pActor_____pActor__pExtra_004e9eb8,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,
               0x619);
  }
  iVar1 = (**(code **)(UINT_008ca32c + 0x20))
                    (0x4a0,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x61b);
  *(int *)(param_1 + 0xa4) = iVar1;
  if (iVar1 == 0) {
    (**(code **)(UINT_008ca32c + 0x18))
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

/* ---- 0x004906b0  Actor_SetFollowBoxes ---- */
/* Actor_SetFollowBoxes(actor, follow): sets extra+0x1b8. Following creates the walker and
   reattaches it to the set; not following clears the walker's sector (+0x5c) but keeps the walker.
    */

void Actor_SetFollowBoxes(int param_1,int param_2)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xa4) == 0) {
    Actor_CreateExtra(param_1);
  }
  if (param_2 != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x1b8) = 1;
    Actor_CreateWalker(param_1,1);
    Walker_ReattachToSet(*(void **)(*(int *)(param_1 + 0xa4) + 0x1b4));
    return;
  }
  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x1b8) = 0;
  iVar1 = *(int *)(*(int *)(param_1 + 0xa4) + 0x1b4);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x5c) = 0;
  }
  return;
}

/* ---- 0x00490730  Actor_CreateWalker ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Source: Engine/sputActor.cpp (line 1637, from __FILE__/__LINE__ passed to the allocator) */

void Actor_CreateWalker(void *param_1,int param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  float *pfVar2;
  void *p;
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define pcStack_8 (*(code **)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  pcStack_8 = FUN_004d605b;
  *unaff_FS_OFFSET = (uint)&local_c;
  p = (void *)0x0;
  if ((param_2 == 0) &&
     (pvVar1 = *(void **)(*(int *)((int)param_1 + 0xa4) + 0x1b4), pvVar1 != (void *)0x0)) {
    Walker_Destroy((int)pvVar1);
    Plat_Free(pvVar1);
    *(undefined4 *)(*(int *)((int)param_1 + 0xa4) + 0x1b4) = 0;
    *unaff_FS_OFFSET = local_c;
    return;
  }
  if (*(int *)(*(int *)((int)param_1 + 0xa4) + 0x1b4) == 0) {
    pvVar1 = Plat_Alloc(0x60);
    local_4 = 0;
    if (pvVar1 != (void *)0x0) {
      p = Walker_Create(pvVar1,*(float *)(*(int *)((int)param_1 + 0xa4) + 0x1c0));
    }
    local_4 = 0xffffffff;
    Mem_CheckAlloc(p,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x665);
    Walker_SetPosition(p,(float *)((int)param_1 + 0xc));
    pfVar2 = Actor_GetFrame(param_1);
    local_18 = (uint)(pfVar2[3] + *(float *)((int)param_1 + 0xc));
    local_14 = (uint)(*(float *)((int)param_1 + 0x10) + pfVar2[4]);
    local_10 = (uint)(*(float *)((int)param_1 + 0x14) + pfVar2[5]);
    Walker_TurnToPoint(p,(int)&local_18,0x7f7fffff);
    *(void **)(*(int *)((int)param_1 + 0xa4) + 0x1b4) = p;
  }
  *unaff_FS_OFFSET = local_c;
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_c
#undef pcStack_8

#endif


/* ---- 0x00490870  Actor_SetPositionClamped ---- */
void Actor_SetPositionClamped(int param_1,float *param_2)

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
    Walker_SetPosition(this,param_2);
    if (*(int *)(*(int *)(param_1 + 0xa4) + 0x1b8) != 0) {
      Walker_ReattachToSet(this);
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

/* ---- 0x00490900  Actor_SetRot ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_40 */
/* Actor_SetRot(actor, angles, snap): clears actor+8 bit 0 first, which ends a WalkActorTo path walk
   (Actor_UpdateMovement only calls Actor_FollowPath while it is set). Pitch (+0x24) and roll
   (+0x2c) are always set at once. With a walker, the walker heading is turned to the yaw
   immediately, +0x28 (angle left) is set, and the visible yaw eases there in Walker_UpdateYaw; snap
   (5th Lua arg nil) negates the turn rate so that update jumps in one frame. Without a walker all
   three angles are set at once. Does not create a walker. */

void Actor_SetRot(int param_1,undefined4 *param_2,int param_3)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *this;
  int iVar1;
  undefined4 uVar2;
  float fVar3;
  #define local_40 (*(uint *)(_frame + (0x50 - 0x40)))
  #define local_30 (*(undefined1 (*)[12])(_frame + (0x50 - 0x30)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xfffffffe;
  if ((*(int *)(param_1 + 0xa4) != 0) &&
     (this = *(float **)(*(int *)(param_1 + 0xa4) + 0x1b4), this != (float *)0x0)) {
    Angles_ToMatrixNoPos(local_30,param_2);
    local_24 = (uint)((float)local_24 + *this);
    local_20 = (uint)(this[1] + (float)local_20);
    local_1c = (uint)(this[2] + (float)local_1c);
    Walker_ToLocalSpace(this,(float *)&local_24);
    local_1c = 0;
    Vec3_Normalize((float *)&local_24);
    fVar3 = Math_AsinDegreesSeries((float)local_20);
    fVar3 = 90.0 - fVar3;
    local_40 = (uint)fVar3;
    if (0.0 < (float)local_24) {
      local_40 = (uint)-fVar3;
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
#undef local_1c
#undef local_20
#undef local_24
#undef local_30
#undef local_40

#endif


/* ---- 0x00490a40  Actor_SetReflection ---- */
void __cdecl Actor_SetReflection(void *actor,float angle)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)((int)actor + 0xa4) + 0x1b4);
  if (iVar1 != 0) {
    *(float *)(iVar1 + 0x3c) = angle;
  }
  return;
}

/* ---- 0x00490a60  Actor_SetWalkChore ---- */
void __cdecl Actor_SetWalkChore(void *actor,int chore,void *costume)

{
  int *piVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  puVar3 = *(undefined4 **)((int)actor + 0xa0);
  if (puVar3 != (undefined4 *)0x0) {
    if (costume == (void *)0x0) {
      costume = puVar3;
    }
    piVar1 = puVar3 + 1;
    if (puVar3 != (undefined4 *)0x0) {
      do {
        if ((puVar3[1] != *piVar1) || (-1 < (int)puVar3[10])) break;
        puVar3 = (undefined4 *)puVar3[0x2c];
      } while (puVar3 != (undefined4 *)0x0);
      if ((puVar3 != (undefined4 *)0x0) && (puVar3[1] == *piVar1)) {
        if (chore == puVar3[10]) {
          return;
        }
        uVar2 = Cos_InstChoreStatus(*puVar3,puVar3[10]);
        if ((uVar2 != 0) &&
           (Cos_StopChoreFaded((void *)*puVar3,puVar3[10],g_nChoreFadeMs), chore != -1)) {
          Cos_InstPlayChore(*puVar3,chore,uVar2 & 2,~uVar2 >> 2 & 1);
          Cos_InstUpdateChore(*puVar3,chore,100);
          Chore_FadeIn((void *)*puVar3,chore,g_nChoreFadeMs);
        }
        puVar3[10] = 0xffffffff;
        *(int *)((int)costume + 0x28) = chore;
        return;
      }
    }
    *(int *)((int)costume + 0x28) = chore;
  }
  return;
}

/* ---- 0x00490b50  Actor_SetTurnChores ---- */
void __cdecl Actor_SetTurnChores(void *actor,int leftChore,int rightChore,void *costume)

{
  int *piVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  puVar3 = *(undefined4 **)((int)actor + 0xa0);
  if (puVar3 != (undefined4 *)0x0) {
    if (costume == (void *)0x0) {
      costume = puVar3;
    }
    piVar1 = puVar3 + 1;
    if (puVar3 != (undefined4 *)0x0) {
      do {
        if ((puVar3[1] != *piVar1) || (-1 < (int)puVar3[0xb])) break;
        puVar3 = (undefined4 *)puVar3[0x2c];
      } while (puVar3 != (undefined4 *)0x0);
      if ((puVar3 != (undefined4 *)0x0) && (puVar3[1] == *piVar1)) {
        if (leftChore != puVar3[0xb]) {
          uVar2 = Cos_InstChoreStatus(*puVar3,puVar3[0xb]);
          if ((uVar2 != 0) && (Cos_InstStopChore(*puVar3,puVar3[0xb]), leftChore != -1)) {
            Cos_InstPlayChore(*puVar3,leftChore,uVar2 & 2,~uVar2 >> 2 & 1);
          }
          puVar3[0xb] = 0xffffffff;
          *(int *)((int)costume + 0x2c) = leftChore;
        }
        if (rightChore == puVar3[0xc]) {
          return;
        }
        uVar2 = Cos_InstChoreStatus(*puVar3,puVar3[0xc]);
        if ((uVar2 != 0) && (Cos_InstStopChore(*puVar3,puVar3[0xc]), leftChore != -1)) {
          Cos_InstPlayChore(*puVar3,rightChore,uVar2 & 2,~uVar2 >> 2 & 1);
        }
        puVar3[0xc] = 0xffffffff;
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
  undefined4 *puVar3;
  
  puVar3 = *(undefined4 **)((int)actor + 0xa0);
  if (puVar3 != (undefined4 *)0x0) {
    if (costume == (void *)0x0) {
      costume = puVar3;
    }
    piVar1 = puVar3 + 1;
    if (puVar3 != (undefined4 *)0x0) {
      do {
        if ((puVar3[1] != *piVar1) || (-1 < (int)puVar3[0xd])) break;
        puVar3 = (undefined4 *)puVar3[0x2c];
      } while (puVar3 != (undefined4 *)0x0);
      if ((puVar3 != (undefined4 *)0x0) && (puVar3[1] == *piVar1)) {
        if (chore == puVar3[0xd]) {
          return;
        }
        uVar2 = Cos_InstChoreStatus(*puVar3,puVar3[0xd]);
        if ((uVar2 != 0) && (Cos_InstStopChore(*puVar3,puVar3[0xd]), chore != -1)) {
          Cos_InstPlayChore(*puVar3,chore,uVar2 & 2,~uVar2 >> 2 & 1);
        }
        puVar3[0xd] = 0xffffffff;
        *(int *)((int)costume + 0x34) = chore;
        return;
      }
    }
    *(int *)((int)costume + 0x34) = chore;
  }
  return;
}

/* ---- 0x00490d30  Actor_PushCostume ---- */
int __cdecl Actor_PushCostume(void *actor,char *name,int param_3)

{
  void *costumeRes;
  void *pvVar1;
  
  if ((name == (char *)0x0) || (param_3 != 0)) {
    costumeRes = (void *)0x0;
    pvVar1 = *(void **)((int)actor + 0xa0);
  }
  else {
    costumeRes = Resource_Load(0x54534f43,name);
    if (costumeRes == (void *)0x0) {
      return 0;
    }
    param_3 = 0;
    pvVar1 = *(void **)((int)actor + 0xa0);
  }
  pvVar1 = Costume_Push(pvVar1,costumeRes,param_3);
  *(void **)((int)actor + 0xa0) = pvVar1;
  Cos_InstSetUserData(**(undefined4 **)((int)actor + 0xa0),((int)actor - (int)g_pActorTable) / 0xa8)
  ;
  Actor_SetFrustumCull(actor,~*(uint *)((int)actor + 4) >> 2 & 1);
  return 1;
}

/* ---- 0x00490dd0  Actor_PopCostume ---- */
void __cdecl Actor_PopCostume(void *actor,int free)

{
  void *pvVar1;
  
  pvVar1 = Costume_Pop(*(void **)((int)actor + 0xa0),free);
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

void Actor_PuckOrient(float param_1)

{
  unsigned char _frame[0x80] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  #define local_68 (*(uint *)(_frame + (0x80 - 0x68)))
  #define local_54 (*(uint *)(_frame + (0x80 - 0x54)))
  #define local_50 (*(uint *)(_frame + (0x80 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0x80 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x80 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x80 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x80 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x80 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x80 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x80 - 0x34)))
  #define local_30 (*(undefined1 (*)[48])(_frame + (0x80 - 0x30)))
  
  if (((param_1 != 0.0) && (*(int *)((int)param_1 + 0xa4) != 0)) &&
     (iVar4 = *(int *)(*(int *)((int)param_1 + 0xa4) + 0x1b4), iVar4 != 0)) {
    iVar1 = (int)param_1 + 0xc;
    iVar2 = (int)param_1 + 0x24;
    iVar3 = (int)param_1 + 0x38;
    Angles_ToMatrix(iVar3,iVar2,iVar1);
    local_48 = *(uint *)((int)param_1 + 0x50);
    local_44 = *(uint *)((int)param_1 + 0x54);
    local_40 = *(uint *)((int)param_1 + 0x58);
    local_54 = *(uint *)(iVar4 + 0x24);
    local_50 = *(uint *)(iVar4 + 0x28);
    local_4c = *(uint *)(iVar4 + 0x2c);
    fVar5 = Vec3_Dot2((float *)&local_48,(float *)&local_54);
    fVar5 = Math_AsinDegreesSeries(fVar5);
    fVar5 = 90.0 - fVar5;
    fVar6 = fVar5;
    if (fVar5 < 0.0) {
      fVar6 = -fVar5;
    }
    if (2.0 < fVar6) {
      fVar6 = Timer_GetFrameSeconds();
      fVar6 = fVar6 * *(float *)(*(int *)((int)param_1 + 0xa4) + 0x1c);
      param_1 = fVar5;
      if ((0.0 < fVar5) && (fVar6 < fVar5)) {
        param_1 = fVar6;
      }
      if ((param_1 < 0.0) && (param_1 < -fVar6)) {
        param_1 = -fVar6;
      }
      local_3c = (uint)((float)local_4c * (float)local_44 - (float)local_50 * (float)local_40);
      local_38 = (uint)((float)local_54 * (float)local_40 - (float)local_4c * (float)local_48);
      local_34 = (uint)((float)local_50 * (float)local_48 - (float)local_54 * (float)local_44);
      Vec3_Normalize((float *)&local_3c);
      Matrix_AxisAngle(local_30,&local_3c,param_1);
      Matrix_Multiply(iVar3,local_30);
      Matrix_ToAngles(iVar3,iVar2);
      Angles_ToMatrix(iVar3,iVar2,iVar1);
    }
  }
  return;
}
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_44
#undef local_48
#undef local_4c
#undef local_50
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
  uint a2;
  uint a3;
  
  puVar1 = *(undefined4 **)(*(int *)(param_1 + 0xa4) + 0x1b4);
  if ((*(int *)(*(int *)(param_1 + 0xa4) + 0x10) != 0) && ((*(byte *)(param_1 + 8) & 1) == 0)) {
    iVar2 = *(int *)(param_1 + 0xa4);
    fVar5 = Timer_GetFrameSeconds();
    Walker_TurnHeading(*(void **)(iVar2 + 0x1b4),
                       (int)((float)*(int *)(iVar2 + 0x10) *
                            *(float *)(iVar2 + 0x1c) * fVar5 * *(float *)(iVar2 + 0x41c)));
  }
  iVar2 = *(int *)(param_1 + 0xa4);
  if (*(int *)(iVar2 + 0xc) != 0) {
    fVar5 = Timer_GetFrameSeconds();
    if (*(int *)(iVar2 + 0x1bc) == 0) {
      a3 = (uint)(*(int *)(iVar2 + 0x10) != 1);
      a2 = (uint)(*(int *)(iVar2 + 0x10) != -1);
    }
    else {
      a3 = 1;
      a2 = 1;
    }
    puVar3 = Walker_WalkSectors(*(void **)(iVar2 + 0x1b4),
                                (int)(fVar5 * *(float *)(iVar2 + 0x41c) * *(float *)(iVar2 + 0x18)),
                                a2,a3);
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
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  if (*(int *)(param_1 + 0xa4) == 0) {
    return;
  }
  puVar5 = *(undefined4 **)(param_1 + 0xa0);
  if (puVar5 == (undefined4 *)0x0) {
    return;
  }
  piVar1 = puVar5 + 1;
  if (puVar5 != (undefined4 *)0x0) {
    do {
      if ((puVar5[1] != *piVar1) || (-1 < (int)puVar5[10])) break;
      puVar5 = (undefined4 *)puVar5[0x2c];
    } while (puVar5 != (undefined4 *)0x0);
    if ((puVar5 != (undefined4 *)0x0) && (puVar5[1] == *piVar1)) {
      uVar3 = Cos_InstChoreStatus(*puVar5,puVar5[10]);
      iVar2 = *(int *)(*(int *)(param_1 + 0xa4) + 0xc);
      if (iVar2 == 0) {
LAB_00491477:
        if (((uVar3 & 1) != 0) && ((*(byte *)(param_1 + 8) & 1) == 0)) {
          Cos_StopChoreFaded((void *)*puVar5,puVar5[10],g_nChoreFadeMs);
        }
      }
      else if (uVar3 == 0) {
        *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x14) = 0;
        Cos_StartChoreFaded(*puVar5,puVar5[10],g_nChoreFadeMs);
      }
      else if (iVar2 == 0) goto LAB_00491477;
    }
  }
  if (*(int *)(*(int *)(param_1 + 0xa4) + 0xc) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x10) = 0;
  }
  puVar5 = *(undefined4 **)(param_1 + 0xa0);
  iVar2 = puVar5[1];
  if (puVar5 != (undefined4 *)0x0) {
    do {
      if ((puVar5[1] != iVar2) || (-1 < (int)puVar5[0xb])) break;
      puVar5 = (undefined4 *)puVar5[0x2c];
    } while (puVar5 != (undefined4 *)0x0);
    if (puVar5 != (undefined4 *)0x0) {
      if ((puVar5[1] == iVar2) && (-1 < (int)puVar5[0xb])) {
        uVar3 = Cos_InstChoreStatus(*puVar5,puVar5[0xb]);
        iVar4 = *(int *)(*(int *)(param_1 + 0xa4) + 0x10);
        if (iVar4 < 1) {
LAB_00491517:
          if ((uVar3 & 1) != 0) {
            Cos_StopChoreFaded((void *)*puVar5,puVar5[0xb],g_nChoreFadeMs);
          }
        }
        else if (uVar3 == 0) {
          *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x14) = 0;
          Cos_StartChoreFaded(*puVar5,puVar5[0xb],g_nChoreFadeMs);
        }
        else if (iVar4 < 1) goto LAB_00491517;
      }
      if (((puVar5 != (undefined4 *)0x0) && (puVar5[1] == iVar2)) && (-1 < (int)puVar5[0xc])) {
        uVar3 = Cos_InstChoreStatus(*puVar5,puVar5[0xc]);
        iVar2 = *(int *)(*(int *)(param_1 + 0xa4) + 0x10);
        if (iVar2 < 0) {
          if (uVar3 == 0) {
            *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x14) = 0;
            Cos_StartChoreFaded(*puVar5,puVar5[0xc],g_nChoreFadeMs);
          }
          else if (-1 < iVar2) goto LAB_0049157a;
        }
        else {
LAB_0049157a:
          if ((uVar3 & 1) != 0) {
            Cos_StopChoreFaded((void *)*puVar5,puVar5[0xc],g_nChoreFadeMs);
          }
        }
      }
    }
  }
  iVar2 = *(int *)(param_1 + 0xa4);
  if ((*(int *)(iVar2 + 0xc) == 0) && (*(int *)(iVar2 + 0x10) == 0)) {
    *(undefined4 *)(iVar2 + 0x14) = 1;
  }
  puVar5 = *(undefined4 **)(param_1 + 0xa0);
  piVar1 = puVar5 + 1;
  if (puVar5 != (undefined4 *)0x0) {
    do {
      if ((puVar5[1] != *piVar1) || (-1 < (int)puVar5[0xd])) break;
      puVar5 = (undefined4 *)puVar5[0x2c];
    } while (puVar5 != (undefined4 *)0x0);
    if (((puVar5 != (undefined4 *)0x0) && (puVar5[1] == *piVar1)) && (-1 < (int)puVar5[0xd])) {
      iVar4 = Cos_InstChoreStatus(*puVar5,puVar5[0xd]);
      iVar2 = *(int *)(*(int *)(param_1 + 0xa4) + 0x14);
      if (iVar2 != 0) {
        if (iVar4 == 0) {
          Cos_StartChoreFaded(*puVar5,puVar5[0xd],g_nChoreFadeMs);
          goto LAB_0049162b;
        }
        if (iVar2 != 0) goto LAB_0049162b;
      }
      if (iVar4 != 0) {
        Cos_StopChoreFaded((void *)*puVar5,puVar5[0xd],g_nChoreFadeMs);
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
  int *piVar1;
  uint *puVar2;
  char cVar3;
  byte bVar4;
  uint uVar5;
  char *text_00;
  int iVar6;
  byte *pbVar7;
  void **ppvVar8;
  void *pvVar9;
  int iVar10;
  undefined4 *puVar11;
  uint uVar12;
  int *piVar13;
  int iVar14;
  byte *pbVar15;
  char *pcVar16;
  uint uVar17;
  char *pcVar18;
  bool bVar19;
  undefined4 uVar20;
  #define local_44 (*(byte (*)[32])(_frame + (0x60 - 0x44)))
  #define local_24 (*(char (*)[36])(_frame + (0x60 - 0x24)))
  
  if (*(int *)((int)actor + 0xa4) == 0) {
    Actor_CreateExtra(actor);
  }
  uVar5 = g_dwSpeechMode & 1;
  uVar17 = g_dwSpeechMode & 2;
  text_00 = Text_ParseLineId(text,(char *)local_44);
  local_24[0] = '\0';
  if (local_44[0] != 0) {
    sprintf(local_24,s__s_wvc_004e9eec,local_44);
    iVar6 = (**(code **)(UINT_008ca32c + 0x30))(local_24,&DAT_004ddb18);
    if (iVar6 == 0) {
      sprintf(local_24,s__s_wav_004e9ee4,local_44);
      iVar6 = (**(code **)(UINT_008ca32c + 0x30))(local_24,&DAT_004ddb18);
      if (iVar6 == 0) {
        sprintf(local_24,s__s_imc_004e9edc,local_44);
        iVar6 = (**(code **)(UINT_008ca32c + 0x30))(local_24,&DAT_004ddb18);
        if (iVar6 == 0) {
          sprintf(local_24,s__s_imu_004e9ed4,local_44);
          iVar6 = (**(code **)(UINT_008ca32c + 0x30))(local_24,&DAT_004ddb18);
          if (iVar6 == 0) {
            local_24[0] = '\0';
            goto LAB_00492c61;
          }
        }
      }
    }
    (**(code **)(UINT_008ca32c + 0x34))(iVar6);
  }
LAB_00492c61:
  if (*(int *)(*(int *)((int)actor + 0xa4) + 0x1c4) != 0) {
    if (local_44[0] != 0) {
      pbVar15 = local_44;
      pbVar7 = (byte *)(*(int *)((int)actor + 0xa4) + 0x1d0);
      do {
        bVar4 = *pbVar7;
        bVar19 = bVar4 < *pbVar15;
        if (bVar4 != *pbVar15) {
LAB_00492ca6:
          iVar6 = (1 - (uint)bVar19) - (uint)(bVar19 != 0);
          goto LAB_00492cab;
        }
        if (bVar4 == 0) break;
        bVar4 = pbVar7[1];
        bVar19 = bVar4 < pbVar15[1];
        if (bVar4 != pbVar15[1]) goto LAB_00492ca6;
        pbVar7 = pbVar7 + 2;
        pbVar15 = pbVar15 + 2;
      } while (bVar4 != 0);
      iVar6 = 0;
LAB_00492cab:
      if (iVar6 == 0) {
        return;
      }
    }
    Actor_ShutUp(actor);
  }
  *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1cc) = 0;
  *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1c4) = 1;
  strncpy(*(int *)((int)actor + 0xa4) + 0x1d0,local_44,0xc);
  g_nTalkingActorCount = g_nTalkingActorCount + 1;
  iVar6 = 0;
  ppvVar8 = &g_pTalkingActors;
  do {
    if (*ppvVar8 == (void *)0x0) {
      (&g_pTalkingActors)[iVar6] = actor;
      break;
    }
    ppvVar8 = ppvVar8 + 1;
    iVar6 = iVar6 + 1;
  } while ((int)ppvVar8 < IMG_ADDR(0x008ca320));
  if (uVar17 != 0) {
    if (local_24[0] == '\0') {
LAB_00492e5e:
      *(undefined1 *)(*(int *)((int)actor + 0xa4) + 0x1dc) = 0;
    }
    else {
      if (background == 0) {
        uVar20 = SoundsLoadProcessStartSound(local_24,0x7f,2);
        *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1c8) = uVar20;
        iVar6 = *(int *)(*(int *)((int)actor + 0xa4) + 0x1c8);
        if (iVar6 == 0) {
          *(undefined1 *)(*(int *)((int)actor + 0xa4) + 0x1dc) = 0;
          goto LAB_00492e6b;
        }
        SoundsSetParam(iVar6,0x600,volume);
        if ((*(byte *)((int)actor + 4) & 8) != 0) {
          uVar20 = *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1c8);
          goto LAB_00492dfb;
        }
      }
      else {
        iVar6 = SoundStartVoiceStream(local_24,volume,pan);
        if (iVar6 != 0) goto LAB_00492e5e;
        *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1c8) = 10000;
        if ((*(byte *)((int)actor + 4) & 8) != 0) {
          uVar20 = 10000;
LAB_00492dfb:
          Sound_SetPosition(uVar20,(int)actor + 0xc,0x14,0x7f,0x41000000,0x3f4ccccd);
        }
      }
      uVar17 = 0xffffffff;
      pcVar16 = local_24;
      do {
        pcVar18 = pcVar16;
        if (uVar17 == 0) break;
        uVar17 = uVar17 - 1;
        pcVar18 = pcVar16 + 1;
        cVar3 = *pcVar16;
        pcVar16 = pcVar18;
      } while (cVar3 != '\0');
      uVar17 = ~uVar17;
      pcVar16 = pcVar18 + -uVar17;
      pcVar18 = (char *)(*(int *)((int)actor + 0xa4) + 0x1dc);
      for (uVar12 = uVar17 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pcVar18 = *(undefined4 *)pcVar16;
        pcVar16 = pcVar16 + 4;
        pcVar18 = pcVar18 + 4;
      }
      for (uVar17 = uVar17 & 3; uVar17 != 0; uVar17 = uVar17 - 1) {
        *pcVar18 = *pcVar16;
        pcVar16 = pcVar16 + 1;
        pcVar18 = pcVar18 + 1;
      }
      uVar20 = iMUSE_GetPhoneme(*(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1c8),0);
      *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1f0) = uVar20;
    }
LAB_00492e6b:
    *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1cc) = 0xffffffff;
  }
  if ((uVar5 != 0) || (*(char *)(*(int *)((int)actor + 0xa4) + 0x1dc) == '\0')) {
    pvVar9 = Actor_CreateSubtitle(actor,text_00,x,y);
    *(void **)(*(int *)((int)actor + 0xa4) + 0x1ec) = pvVar9;
    if (*(char *)(*(int *)((int)actor + 0xa4) + 0x1dc) == '\0') {
      uVar5 = 0xffffffff;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar3 = *text_00;
        text_00 = text_00 + 1;
      } while (cVar3 != '\0');
      *(uint *)(*(int *)((int)actor + 0xa4) + 0x1cc) =
           (~uVar5 - 1) * (0xb - g_nTextSpeed) * 0xf + 0x280;
    }
    TextObject_Activate(pvVar9,-1,0xd);
    ppvVar8 = &g_pTalkingActors;
    if (background == 0) {
      do {
        pvVar9 = *ppvVar8;
        if ((((pvVar9 != (void *)0x0) && (pvVar9 != actor)) &&
            (*(int *)(*(int *)((int)pvVar9 + 0xa4) + 0x1ec) != 0)) &&
           (*(int *)(*(int *)((int)pvVar9 + 0xa4) + 0x1c8) == 10000)) {
          puVar2 = (uint *)(*(int *)(*(int *)((int)actor + 0xa4) + 0x1ec) + 600);
          *puVar2 = *puVar2 | 2;
          break;
        }
        ppvVar8 = ppvVar8 + 1;
      } while ((int)ppvVar8 < IMG_ADDR(0x008ca320));
    }
    else {
      do {
        pvVar9 = *ppvVar8;
        if (((pvVar9 != (void *)0x0) && (pvVar9 != actor)) &&
           (iVar6 = *(int *)(*(int *)((int)pvVar9 + 0xa4) + 0x1ec), iVar6 != 0)) {
          puVar2 = (uint *)(iVar6 + 600);
          *puVar2 = *puVar2 | 2;
        }
        ppvVar8 = ppvVar8 + 1;
      } while ((int)ppvVar8 < IMG_ADDR(0x008ca320));
    }
  }
  if (((actor != (void *)0x0) && (iVar6 = *(int *)((int)actor + 0xa4), iVar6 != 0)) &&
     ((iVar14 = *(int *)((int)actor + 0xa0), iVar14 != 0 && (*(int *)(iVar6 + 0x1f0) != 0)))) {
    piVar1 = (int *)(iVar14 + 4);
    if (iVar14 != 0) {
      while (*(int *)(iVar14 + 4) == *piVar1) {
        iVar10 = 1;
        piVar13 = (int *)(iVar14 + 0x3c);
        do {
          if (-1 < *piVar13) break;
          iVar10 = iVar10 + 1;
          piVar13 = piVar13 + 1;
        } while (iVar10 < 10);
        if ((iVar10 < 10) || (iVar14 = *(int *)(iVar14 + 0xb0), iVar14 == 0)) break;
      }
      if ((iVar14 != 0) && (*(int *)(iVar14 + 4) == *piVar1)) goto LAB_00492fe7;
    }
    *(undefined4 *)(iVar6 + 0x1f0) = 0;
  }
LAB_00492fe7:
  if (((*(char *)(*(int *)((int)actor + 0xa4) + 0x1dc) == '\0') ||
      (*(int *)(*(int *)((int)actor + 0xa4) + 0x1f0) == 0)) &&
     (puVar11 = *(undefined4 **)((int)actor + 0xa0), puVar11 != (undefined4 *)0x0)) {
    piVar1 = puVar11 + 1;
    do {
      if ((puVar11[1] != *piVar1) || (-1 < (int)puVar11[0x1e])) break;
      puVar11 = (undefined4 *)puVar11[0x2c];
    } while (puVar11 != (undefined4 *)0x0);
    if (((puVar11 != (undefined4 *)0x0) && (puVar11[1] == *piVar1)) && (-1 < (int)puVar11[0x1e])) {
      Cos_InstPlayChore(*puVar11,puVar11[0x1e],1,0);
    }
  }
  return;
}
#undef local_24
#undef local_44


/* ---- 0x00493060  Actor_ShutUp ---- */
/* Lua ShutUpActor: stops the actor's speech and talk chores */

void __cdecl Actor_ShutUp(void *actor)

{
  int *piVar1;
  void *obj;
  int iVar2;
  undefined4 *puVar3;
  void **ppvVar4;
  
  if ((actor != (void *)0x0) && (iVar2 = *(int *)((int)actor + 0xa4), iVar2 != 0)) {
    if (*(char *)(iVar2 + 0x1dc) != '\0') {
      if (*(int *)(iVar2 + 0x1c8) == 10000) {
        SoundStopVoiceStream();
      }
      else {
        SoundsStopSound(*(int *)(iVar2 + 0x1c8));
      }
    }
    obj = *(void **)(*(int *)((int)actor + 0xa4) + 0x1ec);
    if (obj != (void *)0x0) {
      List_Unlink(obj);
    }
    puVar3 = *(undefined4 **)((int)actor + 0xa0);
    if (puVar3 != (undefined4 *)0x0) {
      piVar1 = puVar3 + 1;
      if (puVar3 != (undefined4 *)0x0) {
        do {
          if ((puVar3[1] != *piVar1) || (-1 < (int)puVar3[0x1e])) break;
          puVar3 = (undefined4 *)puVar3[0x2c];
        } while (puVar3 != (undefined4 *)0x0);
        if (((puVar3 != (undefined4 *)0x0) && (puVar3[1] == *piVar1)) && (-1 < (int)puVar3[0x1e])) {
          iVar2 = Cos_InstChoreStatus(*puVar3,puVar3[0x1e]);
          if (iVar2 != 0) {
            Cos_InstStopChore(*puVar3,puVar3[0x1e]);
          }
        }
      }
      puVar3 = *(undefined4 **)((int)actor + 0xa0);
      piVar1 = puVar3 + 1;
      if (puVar3 != (undefined4 *)0x0) {
        do {
          if ((puVar3[1] != *piVar1) || (-1 < (int)puVar3[0xe])) break;
          puVar3 = (undefined4 *)puVar3[0x2c];
        } while (puVar3 != (undefined4 *)0x0);
        if (((puVar3 != (undefined4 *)0x0) && (puVar3[1] == *piVar1)) && (-1 < (int)puVar3[0xe])) {
          Cos_InstCompleteChore(*puVar3,puVar3[0xe]);
        }
      }
    }
    ppvVar4 = &g_pTalkingActors;
    do {
      if (*ppvVar4 == actor) {
        *ppvVar4 = (void *)0x0;
      }
      ppvVar4 = ppvVar4 + 1;
    } while ((int)ppvVar4 < IMG_ADDR(0x008ca320));
    *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1f0) = 0;
    *(undefined1 *)(*(int *)((int)actor + 0xa4) + 0x1dc) = 0;
    *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1ec) = 0;
    *(undefined1 *)(*(int *)((int)actor + 0xa4) + 0x1d0) = 0;
    *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1c4) = 0;
    if (0 < g_nTalkingActorCount) {
      g_nTalkingActorCount = g_nTalkingActorCount + -1;
    }
  }
  return;
}

/* ---- 0x004931f0  Actor_PushSectorOppositeEdge ---- */
/* Lua GetSectorOppositeEdge: pushes the point on the far edge of the sector from the actor */

void __cdecl Actor_PushSectorOppositeEdge(int a1,int a2)

{
  float *walker;
  
  if (((a2 != 0) && (a1 != 0)) &&
     (walker = *(float **)(*(int *)(a1 + 0xa4) + 0x1b4), walker != (float *)0x0)) {
    Sector_MoveWalkerToOppositeEdge((void *)a2,walker);
    Actor_SetPositionClamped(a1,walker);
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
  fVar7 = Timer_GetFrameSeconds();
  fVar2 = fVar7 * *(float *)(iVar6 + 0x41c) * fVar2 * 1.25;
  if (SQRT(fVar4 * fVar4 + fVar3 * fVar3 + fVar5 * fVar5) < fVar2) {
    do {
      if (*(int *)(iVar6 + 0x44) <= *(int *)(iVar6 + 0x1b0)) break;
      *(int *)(iVar6 + 0x1b0) = *(int *)(iVar6 + 0x1b0) + 1;
      Actor_SetPositionClamped(param_1,*(int *)(param_1 + 0xa4) + 0x2c);
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
  Walker_TurnToPoint(*(void **)(iVar6 + 0x1b4),iVar6 + 0x2c,0x7f7fffff);
  Actor_WalkForward(param_1);
  return;
}
#undef local_10
#undef local_8
#undef local_c


/* ---- 0x004933c0  Actor_SetWalkDominate ---- */
void __cdecl Actor_SetWalkDominate(void *actor,int dominate)

{
  *(int *)(*(int *)((int)actor + 0xa4) + 0x1bc) = dominate;
  return;
}

/* ---- 0x004933e0  Actor_SetConstrain ---- */
void Actor_SetConstrain(int param_1,int param_2)

{
  void *this;
  
  if ((((*(byte *)(param_1 + 8) & 1) == 0) || (param_2 == 0)) &&
     (this = *(void **)(*(int *)(param_1 + 0xa4) + 0x1b4), this != (void *)0x0)) {
    Walker_SetConstraint(this,param_2);
  }
  return;
}

/* ---- 0x004934b0  Actor_IsVoicePlaying ---- */
int __cdecl Actor_IsVoicePlaying(void *actor)

{
  int iVar1;
  
  iVar1 = *(int *)((int)actor + 0xa4);
  if (*(char *)(iVar1 + 0x1dc) == '\0') {
    return 0;
  }
  if (*(int *)(iVar1 + 0x1c8) == 10000) {
    iVar1 = ImGetParam(10000,0x100);
    return (uint)(0 < iVar1);
  }
  iVar1 = SoundsIsSoundPlaying(iVar1 + 0x1dc);
  return (uint)(0 < iVar1);
}

/* ---- 0x00493510  Actor_HasShadow ---- */
int __cdecl Actor_HasShadow(void *actor)

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

/* ---- 0x00493570  Actor_SetShadowPlane ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void Actor_SetShadowPlane(int param_1,char *param_2)

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
  pvVar7 = Sector_FindByName(param_2);
  if (pvVar7 != (void *)0x0) {
    puVar1[2] = *(undefined4 *)((int)pvVar7 + 0x60);
    puVar1[3] = *(undefined4 *)((int)pvVar7 + 100);
    fVar2 = *(float *)((int)pvVar7 + 0x68);
    puVar1[4] = fVar2;
    iVar6 = *(int *)((int)pvVar7 + 0x38);
    fVar3 = *(float *)(iVar6 + 8);
    fVar4 = *(float *)(iVar6 + 0xc);
    fVar5 = *(float *)(iVar6 + 4);
    *puVar1 = 1;
    puVar1[1] = 0;
    puVar1[5] = -(fVar5 * (float)puVar1[2] + fVar3 * (float)puVar1[3] + fVar4 * fVar2);
  }
  return;
}
#endif


/* ---- 0x004935f0  Actor_SetShadowPoint ---- */
void __cdecl Actor_SetShadowPoint(void *actor,float x,float y,float z)

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

/* ---- 0x00493660  Actor_AddShadowPlane ---- */
/* Shadow records are 0x54 bytes at extra+(idx+6)*0x54 with the plane equation at +8 */

void __cdecl Actor_AddShadowPlane(void *actor,int shadowIdx,char *sectorName)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  
  pvVar2 = Sector_FindByName(sectorName);
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

/* ---- 0x004936b0  Actor_KillShadows ---- */
void __cdecl Actor_KillShadows(void *actor)

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

/* ---- 0x004936e0  Actor_DrawShadows ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Draws the shadows of an actor: slots at extra+0x1f8, 0x54 bytes each (+0 active, +4 valid,
   +8..+0x14 plane normal and d, +0x18..0x20 shadow point). valid 0: always; -1: only when pos.n+d
   <= 0; 1: only when >= 0 (pos = actor+0xc). Set by SetActorShadowPlane (Actor_SetShadowPlane
   0x493570, which resets valid to 0) and SetActorShadowValid (Lua_SetActorShadowValid 0x4a1fd0 ->
   0x493630). */

void Actor_DrawShadows(int param_1)

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
          (((fVar2 = *(float *)(param_1 + 0x10) * (float)shadow[3] +
                     *(float *)(param_1 + 0x14) * (float)shadow[4] +
                     *(float *)(param_1 + 0xc) * (float)shadow[2] + (float)shadow[5], iVar1 != -1 ||
            (fVar2 <= 0.0)) && ((iVar1 != 1 || (0.0 <= fVar2)))))))) {
        Actor_DrawShadowPlane(*(void **)(param_1 + 0xa0),shadow);
      }
      iVar3 = iVar3 + 0x54;
    } while (iVar3 < 0x3f0);
    Profile_End(0xb);
  }
  return;
}
#endif


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

/* ---- 0x004937c0  Actor_ToClean ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua ActorToClean: marks the actor's rectangle to be restored from the clean background */

void __cdecl Actor_ToClean(void *actor)

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
  
  pvVar6 = Set_GetCurrent();
  iVar2 = *(int *)((int)pvVar6 + 0xb4);
  pvVar6 = Set_GetCurrent();
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
      pvVar6 = Set_GetCurrent();
      iVar2 = *(int *)((int)pvVar6 + 0x88);
      pvVar6 = Set_GetCurrent();
      iVar5 = *(int *)((int)pvVar6 + 0x80);
      if (*(int *)(iVar5 + iVar2 * 0x34) == 0) {
        (*g_pSvcMain->pAssertFail)
                  (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
      }
      rdroid_SetColormap(*(undefined4 *)(iVar5 + iVar2 * 0x34 + 4));
      pvVar6 = Set_GetCurrent();
      iVar2 = *(int *)((int)pvVar6 + 0x88);
      pvVar6 = Set_GetCurrent();
      piVar10 = (int *)(*(int *)((int)pvVar6 + 0x80) + iVar2 * 0x34);
      if (*piVar10 == 0) {
        (*g_pSvcMain->pAssertFail)
                  (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
      }
      iVar2 = piVar10[1];
    }
    else {
      if (iVar2 == 0) {
        (*g_pSvcMain->pAssertFail)
                  (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
      }
      rdroid_SetColormap(piVar10[1]);
      piVar10 = *(int **)actor;
      if (*piVar10 == 0) {
        (*g_pSvcMain->pAssertFail)
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

/* ---- 0x004946b0  Actor_SetClipPlane ---- */
void Actor_SetClipPlane(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xa4) == 0) {
    Actor_CreateExtra(param_1);
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
    Actor_CreateExtra(param_1);
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
  Actor_KillShadows(actor);
  Costume_FreeList(*(void **)((int)actor + 0xa0),0);
  *(undefined4 *)((int)actor + 0xa0) = 0;
  if (*(int *)((int)actor + 0xa4) != 0) {
    p = *(void **)(*(int *)((int)actor + 0xa4) + 0x1b4);
    if (p != (void *)0x0) {
      Walker_Destroy((int)p);
      Plat_Free(p);
      *(undefined4 *)(*(int *)((int)actor + 0xa4) + 0x1b4) = 0;
    }
    (**(code **)(UINT_008ca32c + 0x24))(*(undefined4 *)((int)actor + 0xa4));
    *(undefined4 *)((int)actor + 0xa4) = 0;
  }
  if (*(void **)actor != (void *)0x0) {
    ResRef_Remove(*(void **)actor);
    (**(code **)(UINT_008ca32c + 0x24))(*(undefined4 *)actor);
    *(undefined4 *)actor = 0;
  }
  *(undefined4 *)((int)actor + 0x9c) = 0;
  g_nActorCount = g_nActorCount + -1;
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
  uint uVar4;
  int iVar5;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar6;
  #define local_fc (*(uint *)(_frame + (0x110 - 0xfc)))
  #define local_f8 (*(uint *)(_frame + (0x110 - 0xf8)))
  #define local_f4 (*(uint *)(_frame + (0x110 - 0xf4)))
  #define local_f0 (*(uint *)(_frame + (0x110 - 0xf0)))
  #define local_ec (*(uint *)(_frame + (0x110 - 0xec)))
  #define local_e8 (*(uint *)(_frame + (0x110 - 0xe8)))
  #define local_e4 (*(uint *)(_frame + (0x110 - 0xe4)))
  #define local_e0 (*(uint *)(_frame + (0x110 - 0xe0)))
  #define local_dc (*(uint *)(_frame + (0x110 - 0xdc)))
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
    local_f0 = *(uint *)((int)costumeList + 8);
    local_fc = 0x44200000;
    local_f8 = 0x43f00000;
    local_e4 = 0;
    local_dc = 0;
    for (; local_f0 != 0; local_f0 = *(uint *)(local_f0 + 400)) {
      local_d4 = *(uint *)(local_f0 + 0x40);
      uVar4 = *(uint *)(local_d4 + 4);
      local_e8 = uVar4;
      if (((*(int *)(local_f0 + 0x38) != 0) && (*(int *)(local_f0 + 0x34) == 0)) &&
         (local_d8 = 0, 0 < *(int *)(uVar4 + 0x54))) {
        local_f4 = 0;
        local_ec = 0;
        do {
          iVar1 = *(int *)(local_ec + 0x4c + *(int *)(uVar4 + 0x58));
          if (((iVar1 != -1) &&
              (iVar2 = *(int *)(uVar4 + 0x28), *(int *)(iVar2 + 0x54 + iVar1 * 0x7c) != 0)) &&
             (*(int *)(*(int *)(local_d4 + 0x2c) + iVar1 * 4) != 0)) {
            iVar5 = 0;
            do {
              out = (float *)((int)local_c0 + iVar5);
              Vec3_Sub(out,(float *)(iVar5 + *(int *)(iVar2 + iVar1 * 0x7c + 0x58)),
                       (float *)(local_f4 + *(int *)(local_d4 + 0x20)));
              iVar3 = Plane_IntersectSegment
                                (out,(float *)((int)shadow + 0x18),out,*(float *)((int)shadow + 8),
                                 *(float *)((int)shadow + 0xc),*(float *)((int)shadow + 0x10),
                                 *(float *)((int)shadow + 0x14));
              if (iVar3 == 0) {
                return;
              }
              iVar5 = iVar5 + 0xc;
            } while (iVar5 < 0xc0);
            if (g_pShadowMaterial == (void *)0x0) {
              g_pShadowMaterial = rdMaterial_Load(s_shadow_mat_004ea19c,0,0);
            }
            if (g_pShadowColormap == (void *)0x0) {
              g_pShadowColormap = rdColormap_Load(s_shadow_cmp_004ea190);
            }
            uVar4 = local_e8;
            if (g_pShadowMaterial != (void *)0x0) {
              rdroid_SetColormap(g_pShadowColormap);
              if (g_nZBufferEnabled != 0) {
                Display_SetPalette3D((void *)((int)g_pShadowColormap + 0x30),0);
              }
              Shadow_DrawClippedPoly(local_c0,4,(float *)&local_fc,(float *)&local_e4,shadow);
              Shadow_DrawClippedPoly(local_90,4,(float *)&local_fc,(float *)&local_e4,shadow);
              Shadow_DrawClippedPoly(local_60,4,(float *)&local_fc,(float *)&local_e4,shadow);
              Shadow_DrawClippedPoly(local_30,4,(float *)&local_fc,(float *)&local_e4,shadow);
              uVar4 = local_e8;
            }
          }
          local_d8 = local_d8 + 1;
          local_ec = local_ec + 0xb8;
          local_f4 = local_f4 + 0x30;
        } while ((int)local_d8 < *(int *)(uVar4 + 0x54));
      }
    }
    if ((float)local_fc <= (float)local_e4) {
      lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      local_d0 = (uint)lVar6;
      lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      local_cc = (uint)lVar6;
      lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      local_c8 = (uint)lVar6;
      lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      local_c4 = (uint)lVar6;
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


/* ---- 0x00495080  Actor_DrawCostumes ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void Actor_DrawCostumes(undefined4 param_1,undefined4 param_2)

{
  ((code *)Actor_DrawCostumeMeshes)(param_1,param_2,0,0);
  return;
}
#endif


/* ---- 0x004950a0  Actor_DrawCostumeMeshes ---- */
/* Draws the meshes of an actor's costume. Enables the user clip plane when extra+0x3fc != 0 (normal
   extra+0x400, point extra+0x40c). For a model hung on a node (component+0x44 != 0) whose node
   index (+0x48) equals extra+0x420 (SetActorInvClipNode) the plane through the actor position
   (actor+0xc) with the second row of the actor matrix (actor+0x44..0x4c, the facing) as normal is
   used for that mesh only, then the clip is switched off. Meshes are clipped per polygon in eye
   space (MeshFace_Draw 0x40d880 -> Polygon_ClipToPlane 0x44ea50: keep dist >= 0); Mesh_Draw
   0x40d230 skips a mesh whose centre is more than its radius behind the plane. */

void Actor_DrawCostumeMeshes(undefined4 *param_1,float *param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *actor;
  undefined4 *puVar1;
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
  for (puVar1 = param_1; (puVar1 != (undefined4 *)0x0 && (puVar1[1] == iVar5));
      puVar1 = (undefined4 *)puVar1[0x2c]) {
    Costume_ApplyComponentState((void *)*puVar1);
  }
  iVar5 = Cos_InstGetUserData(*param_1);
  actor = (int *)((int)g_pActorTable + iVar5 * 0xa8);
  if ((actor[0x29] == 0) || (*(int *)(actor[0x29] + 0x3fc) == 0)) {
    Renderer_EnableClipPlane(0);
  }
  else {
    Renderer_EnableClipPlane(1);
    Renderer_SetClipPlane(actor[0x29] + 0x400,actor[0x29] + 0x40c);
  }
  Costume_ApplyScale(actor,(void *)param_1[2]);
  iVar5 = param_1[2];
  do {
    if (iVar5 == 0) {
      Actor_DrawShadows(actor);
      iVar5 = param_1[1];
      for (puVar1 = param_1; (puVar1 != (undefined4 *)0x0 && (puVar1[1] == iVar5));
          puVar1 = (undefined4 *)puVar1[0x2c]) {
        Costume_ApplyComponentState((void *)*puVar1);
      }
      Costume_ApplyScale(actor,(void *)param_1[2]);
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
          if (g_nZBufferEnabled == 0) goto LAB_004951b3;
        }
        else {
          rdroid_SetColormap(*(int *)(iVar5 + 0x4c));
          if (g_nZBufferEnabled != 0) {
            Display_SetPalette3D((void *)(*(int *)(iVar5 + 0x4c) + 0x30),0);
            goto LAB_004951ab;
          }
LAB_004951b3:
          pvVar6 = (void *)Render_GetBackBuffer();
          Surface_Lock(pvVar6);
        }
        iVar7 = rdThing_DrawAlt(*(void **)(iVar5 + 0x40),param_2);
        if ((iVar7 == 0) || (actor == (int *)0x0)) {
          actor[0x1a] = 0;
        }
        else {
          actor[0x1a] = 1;
        }
        if (g_nZBufferEnabled == 0) {
          pvVar6 = (void *)Render_GetBackBuffer();
          Surface_Unlock(pvVar6);
        }
      }
      else {
        for (; (iVar7 != 0 && (*(int *)(iVar7 + 0x4c) == 0)); iVar7 = *(int *)(iVar7 + 0x44)) {
        }
        if (((iVar7 != 0) && (*(int *)(iVar7 + 0x4c) != 0)) &&
           (rdroid_SetColormap(*(int *)(iVar7 + 0x4c)), g_nZBufferEnabled != 0)) {
          Display_SetPalette3D((void *)(*(int *)(iVar7 + 0x4c) + 0x30),0);
        }
        Costume_UpdateAttachedFrame(*(void **)(iVar5 + 0x44),param_2);
        iVar8 = *(int *)(*(int *)(iVar5 + 0x44) + 0x40);
        iVar7 = *(int *)(*(int *)(iVar8 + 4) + 0x58) + *(int *)(iVar5 + 0x48) * 0xb8;
        iVar2 = *(int *)(*(int *)(*(int *)(iVar5 + 0x40) + 4) + 0x58);
        if (g_nZBufferEnabled == 0) {
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
        actor[0x1a] = 0;
        if ((actor[0x29] != 0) && (*(int *)(actor[0x29] + 0x420) == *(int *)(iVar5 + 0x48))) {
          Renderer_EnableClipPlane(1);
          Renderer_SetClipPlane(actor + 0x11,actor + 3);
        }
        iVar8 = rdThing_DrawAlt(*(void **)(iVar5 + 0x40),
                                (float *)(*(int *)(iVar8 + 0x20) + *(int *)(iVar5 + 0x48) * 0x30));
        if ((iVar8 != 0) && (actor != (int *)0x0)) {
          actor[0x1a] = 1;
        }
        if ((actor[0x29] != 0) && (*(int *)(actor[0x29] + 0x420) == *(int *)(iVar5 + 0x48))) {
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
        if (g_nZBufferEnabled == 0) {
          pvVar6 = (void *)Render_GetBackBuffer();
          Surface_Unlock(pvVar6);
        }
      }
      piVar4 = (int *)*actor;
      iVar7 = *piVar4;
      if (iVar7 != 0) {
        if (iVar7 == 0) {
          (*g_pSvcMain->pAssertFail)
                    (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
        }
        rdroid_SetColormap(piVar4[1]);
        if (g_nZBufferEnabled != 0) {
          piVar4 = (int *)*actor;
          if (*piVar4 == 0) {
            (*g_pSvcMain->pAssertFail)
                      (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
          }
          Display_SetPalette3D((void *)(piVar4[1] + 0x30),0);
        }
      }
      iStack_10 = g_nDrawBoxMinX;
      iStack_8 = g_nDrawBoxMaxX - g_nDrawBoxMinX;
      iStack_c = g_nDrawBoxMinY;
      iStack_4 = g_nDrawBoxMaxY - g_nDrawBoxMinY;
      Render_InvalidateRectLastBuffer(&iStack_10,1);
      if ((*(int *)(iVar5 + 0x40) == param_1[1]) && (actor != (int *)0x0)) {
        actor[0x1b] = iStack_10;
        actor[0x1c] = iStack_c;
        actor[0x1d] = iStack_8;
        actor[0x1e] = iStack_4;
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
        if ((void *)((int)g_pActorTable + *piVar3 * 0xa8) == actor) break;
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
        (*g_pSvcRoom->pFree)(piVar3);
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
      if ((char *)((int)g_pActorTable + *piVar5 * 0xa8) == setName) {
        return;
      }
    }
    piVar5 = (int *)(*g_pSvcRoom->pAlloc)(0xc,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0xa09);
    *piVar5 = 0;
    piVar5[1] = 0;
    piVar5[2] = 0;
    *piVar5 = ((int)setName - (int)g_pActorTable) / 0xa8;
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

/* ---- 0x004a8500  Actor_GetYawToPoint ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
float __thiscall Actor_GetYawToPoint(void *this,int a1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined *puVar1;
  float fVar2;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  local_18 = *(uint *)a1;
  local_14 = *(uint *)(a1 + 4);
  local_10 = *(uint *)(a1 + 8);
  if (*(void **)((int)this + 0x5c) != (void *)0x0) {
    Sector_FixPlaneCoordinate(*(void **)((int)this + 0x5c),(int)&local_18);
  }
  Walker_ToLocalSpace(this,(float *)&local_18);
  Vec3_Normalize((float *)&local_18);
  fVar2 = Math_AsinDegreesSeries((float)local_14);
  a1 = (int)(90.0 - fVar2);
  if (0.0 < (float)local_18) {
    a1 = (int)((float)a1 * -1.0);
  }
  puVar1 = Walker_GetAngles((int)this);
  return *(float *)(puVar1 + 4) + (float)a1;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c

#endif

