/* GRIMFANDANGO.EXE :: collision.c
 * functions 0x004922d0 .. 0x00494100 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004922d0  GetOuttaTheBox ---- */
/* Original name GetOuttaTheBox (the remaster's GrimFandango (Linux): same body (the point into box
   space; if inside, move it out through the nearest face from FLT_MAX)); was
   Collision_PushOutOfBox. */

void __cdecl
GetOuttaTheBox(float *pos,float xmin,float ymin,float zmin,float xmax,float ymax,float zmax,
              float *frame,float *out)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float (*)[2])(_frame + (0x30 - 0x14)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  local_c = *pos - *out;
  local_8 = pos[1] - out[1];
  local_4 = pos[2] - out[2];
  rdMatrix_TransformVectorOrtho34(&local_18,&local_c,frame);
  if ((((zmin < local_14[1]) && (ymin < local_14[0])) && (local_14[0] < ymax)) &&
     (((xmin < local_18 && (local_18 < xmax)) && (local_14[1] < zmax)))) {
    fVar1 = 3.4028235e+38;
    if (local_14[0] < ymax) {
      fVar2 = ymax - local_14[0];
      if (fVar2 < 0.0f) {
        fVar2 = -fVar2;
      }
      fVar1 = 3.4028235e+38;
      if (fVar2 < 3.4028235e+38) {
        local_8 = ymax - -0.01f;
        local_c = local_18;
        local_4 = local_14[1];
        fVar1 = fVar2;
      }
    }
    if (ymin < local_14[0]) {
      fVar2 = ymin - local_14[0];
      if (fVar2 < 0.0f) {
        fVar2 = -fVar2;
      }
      if (fVar2 < fVar1) {
        local_8 = ymin - 0.01f;
        local_c = local_18;
        local_4 = local_14[1];
        fVar1 = fVar2;
      }
    }
    if (local_18 < xmax) {
      fVar2 = xmax - local_18;
      if (fVar2 < 0.0f) {
        fVar2 = -fVar2;
      }
      if (fVar2 < fVar1) {
        local_c = xmax - -0.01f;
        local_8 = local_14[0];
        local_4 = local_14[1];
        fVar1 = fVar2;
      }
    }
    if (xmin < local_18) {
      fVar2 = xmin - local_18;
      if (fVar2 < 0.0f) {
        fVar2 = -fVar2;
      }
      if (fVar2 < fVar1) {
        local_c = xmin - 0.01f;
        local_8 = local_14[0];
        local_4 = local_14[1];
      }
    }
    rdMatrix_TransformPoint34(pos,&local_c,frame);
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
int __cdecl
Collision_PointInBox
          (float *a,float *b,float *p3,float bx0,float by0,float bz0,float bx1,float by1,float bz1,
          float *p10,float *offset)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[80] __attribute__((aligned(16)));  /* the original frame below the return address */
  int iVar1;
  float *pfVar2;
  float *pfVar3;
  float in_stack_ffffffc8;
  float in_stack_ffffffcc;
  float in_stack_ffffffd0;
  float in_stack_ffffffd4;
  float in_stack_ffffffd8;
  float in_stack_ffffffdc;
  float *frame;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
  local_c[0] = *offset + *a;
  bx0 = *offset + *b;
  local_c[1] = a[1] + offset[1];
  by0 = b[1] + offset[1];
  local_c[2] = a[2] + offset[2];
  bz0 = b[2] + offset[2];
  pfVar2 = &bx0;
  pfVar3 = (float *)(_stkneg + 24);
  frame = p10;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar3 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar3 = pfVar3 + 1;
  }
  iVar1 = TestCollision(local_c,&bx0,p3,in_stack_ffffffc8,in_stack_ffffffcc,in_stack_ffffffd0,
                        in_stack_ffffffd4,in_stack_ffffffd8,in_stack_ffffffdc,frame);
  if (iVar1 == 0) {
    iVar1 = BuildPath(a,b,0);
    return iVar1;
  }
  return 0;
}
#undef local_c

#endif


/* ---- 0x004925c0  FindObjectCorners ---- */
/* Computes the four detour points around an actor's collision box Original name FindObjectCorners
   (the remaster's GrimFandango (Linux): same body (with an upright actor (m[8] >= 0.999) the four
   corners of the box +0x60 .. +0x70 grown by the radius, transformed by the matrix)); was
   Collision_BoxCorners. */

void __cdecl FindObjectCorners(int box,float pad,float *matrix,float z,float *vec)

{
  int iVar1;
  float *pfVar2;
  
  if (0.999 <= matrix[8]) {
    *vec = *(float *)(box + 0x60) - pad;
    vec[1] = *(float *)(box + 100) - pad;
    vec[2] = *(float *)(box + 0x68);
    pfVar2 = vec + 0xc;
    iVar1 = 4;
    vec[3] = pad + *(float *)(box + 0x6c);
    vec[4] = *(float *)(box + 100) - pad;
    vec[5] = *(float *)(box + 0x68);
    vec[6] = pad + *(float *)(box + 0x6c);
    vec[7] = pad + *(float *)(box + 0x70);
    vec[8] = *(float *)(box + 0x68);
    vec[9] = *(float *)(box + 0x60) - pad;
    vec[10] = pad + *(float *)(box + 0x70);
    vec[0xb] = *(float *)(box + 0x68);
    do {
      rdMatrix_TransformPoint34Acc(vec,matrix);
      vec[2] = z;
      *pfVar2 = 1.4013e-45f;
      pfVar2 = pfVar2 + 1;
      vec = vec + 3;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}

/* ---- 0x00492680  TestCollision ---- */
/* Walker_AvoidActorPath: does the path segment pass through the other actor's collision box
   Original name TestCollision (the remaster's GrimFandango (Linux): same parameters and body (both
   segment ends into box space with rdMatrix_TransformVectorOrtho34, the slab tests against the box
   faces)); was Collision_SegmentHitsBox. */

int __cdecl
TestCollision(float *from,float *to,float *hit,float xmin,float ymin,float zmin,float xmax,
             float ymax,float zmax,float *frame)

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
  
  local_18[0] = *from - *hit;
  local_18[1] = from[1] - hit[1];
  local_18[2] = from[2] - hit[2];
  rdMatrix_TransformVectorOrtho34(local_24,local_18,frame);
  local_18[0] = *to - *hit;
  local_18[1] = to[1] - hit[1];
  local_18[2] = to[2] - hit[2];
  rdMatrix_TransformVectorOrtho34(local_c,local_18,frame);
  fVar2 = local_c[0] - local_24[0];
  fVar3 = local_c[1] - local_24[1];
  fVar4 = local_c[2] - local_24[2];
  if (((ymax < local_24[1]) && (local_c[1] < ymax)) &&
     (fVar1 = (ymax - local_24[1]) / fVar3, fVar1 < 1.0f)) {
    fVar5 = fVar1 * fVar2 + local_24[0];
    if ((xmin < fVar5) &&
       (fVar6 = fVar1 * fVar3 + local_24[1], fVar7 = fVar1 * fVar4 + local_24[2], fVar5 < xmax))
    goto LAB_00492801;
  }
  fVar1 = 1.0f;
  fVar5 = FLOAT_008ca320;
  fVar6 = FLOAT_008ca324;
  fVar7 = FLOAT_008ca328;
LAB_00492801:
  FLOAT_008ca328 = fVar7;
  FLOAT_008ca324 = fVar6;
  FLOAT_008ca320 = fVar5;
  if (((local_24[1] < ymin) && (ymin < local_c[1])) &&
     (fVar5 = (ymin - local_24[1]) / fVar3, fVar5 < fVar1)) {
    fVar6 = fVar5 * fVar2 + local_24[0];
    if ((xmin < fVar6) && (fVar6 < xmax)) {
      fVar1 = fVar5;
      FLOAT_008ca320 = fVar6;
      FLOAT_008ca324 = fVar5 * fVar3 + local_24[1];
      FLOAT_008ca328 = fVar5 * fVar4 + local_24[2];
    }
  }
  if (((xmax < local_24[0]) && (local_c[0] < xmax)) &&
     (fVar5 = (xmax - local_24[0]) / fVar2, fVar5 < fVar1)) {
    fVar6 = fVar5 * fVar3 + local_24[1];
    if ((ymin < fVar6) && (fVar6 < ymax)) {
      fVar1 = fVar5;
      FLOAT_008ca320 = fVar5 * fVar2 + local_24[0];
      FLOAT_008ca324 = fVar6;
      FLOAT_008ca328 = fVar5 * fVar4 + local_24[2];
    }
  }
  if (((local_24[0] < xmin) && (xmin < local_c[0])) &&
     (fVar5 = (xmin - local_24[0]) / fVar2, fVar5 < fVar1)) {
    fVar3 = fVar5 * fVar3 + local_24[1];
    if ((ymin < fVar3) && (fVar3 < ymax)) {
      fVar1 = fVar5;
      FLOAT_008ca320 = fVar5 * fVar2 + local_24[0];
      FLOAT_008ca324 = fVar3;
      FLOAT_008ca328 = fVar5 * fVar4 + local_24[2];
    }
  }
  if (fVar1 == 1.0f) {
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

int __cdecl Collision_PickDetour(float *from,float *to,int corners)

{
  float fVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint local_c;
  uint local_8;
  uint local_4;
  
  iVar4 = -1;
  local_4 = 0x7f7fffff;
  iVar3 = 0;
  pfVar2 = (float *)(corners + 8);
  piVar5 = (int *)(corners + 0x30);
  do {
    if ((*piVar5 != 0) &&
       (fVar1 = (pfVar2[-2] - *to) * (pfVar2[-2] - *to) +
                (*pfVar2 - to[2]) * (*pfVar2 - to[2]) + (pfVar2[-1] - to[1]) * (pfVar2[-1] - to[1])
                + (from[2] - *pfVar2) * (from[2] - *pfVar2) +
                  (from[1] - pfVar2[-1]) * (from[1] - pfVar2[-1]) +
                  (*from - pfVar2[-2]) * (*from - pfVar2[-2]), fVar1 < PUN(float,local_4))) {
      iVar4 = iVar3;
      local_4 = PUN(uint,(float)fVar1);
    }
    iVar3 = iVar3 + 1;
    piVar5 = piVar5 + 1;
    pfVar2 = pfVar2 + 3;
  } while (iVar3 < 4);
  return iVar4;
}

/* ---- 0x004939a0  Collision_UpdateMovedActors ---- */
uint __cdecl Collision_UpdateMovedActors(void)

{
  Actor *self;
  int iVar1;
  void **ppvVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  bool bVar6;
  
  iVar3 = 0;
  if (0 < g_nTotActors) {
    ppvVar2 = &g_pDrawableActors;
    do {
      self = *ppvVar2;
      iVar1 = 0xc;
      bVar6 = true;
      pfVar4 = self->aPos;
      pfVar5 = self->aPrevPos;
      do {
        if (iVar1 == 0) break;
        iVar1 = iVar1 + -1;
        bVar6 = *(char *)pfVar4 == *(char *)pfVar5;
        pfVar4 = (float *)((int)pfVar4 + 1);
        pfVar5 = (float *)((int)pfVar5 + 1);
      } while (bVar6);
      if (!bVar6) {
        Collision_TestActorAgainstOthers(self);
      }
      iVar3 = iVar3 + 1;
      ppvVar2 = ppvVar2 + 1;
    } while (iVar3 < g_nTotActors);
  }
  return 1;
}

/* ---- 0x004939f0  Collision_TestActorAgainstOthers ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Ported to C (build/overrides_big_collision_others.c): differential test vs model stand-ins, 0
   differences (docs/notes/big_collision_others.md). */

uint __cdecl Collision_TestActorAgainstOthers(Actor *self)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[240] __attribute__((aligned(16)));  /* the original frame below the return address */
  float (*pafVar1) [3];
  Actor *actor;
  ActorExtra *pAVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  int iVar10;
  float *pfVar11;
  float in_stack_ffffff24;
  float in_stack_ffffff28;
  Actor *in_stack_ffffff2c;
  float fVar12;
  float fVar13;
  #define local_b0 (*(uint *)(_frame + (0xc0 - 0xb0)))
  #define local_ac (*(uint *)(_frame + (0xc0 - 0xac)))
  #define local_a8 (*(uint *)(_frame + (0xc0 - 0xa8)))
  #define local_a4 (*(float (*)[3])(_frame + (0xc0 - 0xa4)))
  #define local_98 (*(float (*)[3])(_frame + (0xc0 - 0x98)))
  #define local_8c (*(float (*)[3])(_frame + (0xc0 - 0x8c)))
  #define local_80 (*(float (*)[3])(_frame + (0xc0 - 0x80)))
  #define local_74 (*(float (*)[3])(_frame + (0xc0 - 0x74)))
  #define local_68 (*(float (*)[3])(_frame + (0xc0 - 0x68)))
  #define local_5c (*(float (*)[3])(_frame + (0xc0 - 0x5c)))
  #define local_50 (*(float (*)[3])(_frame + (0xc0 - 0x50)))
  #define local_44 (*(float (*)[3])(_frame + (0xc0 - 0x44)))
  #define local_38 (*(float (*)[3])(_frame + (0xc0 - 0x38)))
  #define local_2c (*(float (*)[3])(_frame + (0xc0 - 0x2c)))
  #define local_20 (*(float (*)[3])(_frame + (0xc0 - 0x20)))
  #define local_14 (*(uint *)(_frame + (0xc0 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0xc0 - 0x10)))
  #define local_c (*(uint *)(_frame + (0xc0 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0xc0 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0xc0 - 0x4)))
  
  iVar10 = *(int *)((int)self->pCostumes->pMainModel + 4);
  pfVar6 = sputActor_GetOrientMatrix(self);
  rdMatrix_TransformVector34(local_98,(float *)(iVar10 + 0x78),pfVar6);
  fVar3 = local_98[0] + self->aPos[0];
  local_5c[2] = 0.0f;
  local_68[0] = self->aPos[1] + local_98[1];
  local_68[1] = self->aPos[2] + local_98[2];
  fVar4 = *(float *)(iVar10 + 0x5c) * self->pExtra->flCollisionScale;
  if (0 < g_nTotActors) {
    local_74[1] = PUN(float,&g_pDrawableActors);
    do {
      actor = *(Actor **)local_74[1];
      if (((actor != self) && (actor->pExtra != (ActorExtra *)0x0)) &&
         (actor->pExtra->nCollisionMode != 0)) {
        iVar10 = *(int *)((int)actor->pCostumes->pMainModel + 4);
        pfVar6 = (float *)(iVar10 + 0x78);
        pfVar7 = sputActor_GetOrientMatrix(actor);
        rdMatrix_TransformPoint34(local_68 + 2,pfVar6,pfVar7);
        local_50[1] = fVar3 - local_68[2];
        local_50[0] = local_68[0] - local_5c[0];
        fVar13 = local_68[1] - local_5c[1];
        fVar12 = SQRT(fVar13 * fVar13 + local_50[0] * local_50[0] + local_50[1] * local_50[1]);
        local_8c[0] = *(float *)(iVar10 + 0x5c) * actor->pExtra->flCollisionScale;
        if (fVar12 < local_8c[0] + fVar4) {
          if (actor->pExtra->nCollisionMode == 2) {
            self->pExtra->nCollided = 1;
            pfVar6 = self->aPos;
            actor->pExtra->nCollided = 1;
            local_2c[2] = fVar3 - local_68[2];
            local_20[0] = local_68[0] - local_5c[0];
            local_20[1] = local_68[1] - local_5c[1];
            _DAT_008ca348 = *pfVar6;
            _DAT_008ca34c = self->aPos[1];
            _DAT_008ca350 = self->aPos[2];
            rdVector_Normalize3Acc(local_2c + 2);
            uVar5 = self->dwMoveFlags;
            local_20[2] = (local_2c[2] * (1.0f - (fVar12 - local_8c[0]) / fVar4) * fVar4 + fVar3) -
                          local_98[0];
            sputActor_SetActorPosition(self,local_20 + 2);
            _DAT_008ca338 = *pfVar6;
            _DAT_008ca33c = self->aPos[1];
            _DAT_008ca340 = self->aPos[2];
            FLOAT_008ca320 = *pfVar6;
            FLOAT_008ca324 = self->aPos[1];
            FLOAT_008ca328 = self->aPos[2];
            if ((uVar5 & 1) != 0) {
              self->dwMoveFlags = self->dwMoveFlags | 1;
            }
          }
          else {
            local_8c[1] = local_50[1];
            local_8c[2] = local_50[0];
            local_80[0] = fVar13;
            pfVar7 = sputActor_GetOrientMatrix(actor);
            rdMatrix_TransformVectorOrtho34(local_a4,local_8c + 1,pfVar7);
            local_a4[0] = local_a4[0] + *pfVar6;
            local_a4[1] = local_a4[1] + *(float *)(iVar10 + 0x7c);
            local_a4[2] = local_a4[2] + *(float *)(iVar10 + 0x80);
            pAVar2 = actor->pExtra;
            local_44[2] = *(float *)(iVar10 + 0x60) * pAVar2->flCollisionScale - fVar4;
            local_2c[0] = *(float *)(iVar10 + 0x70) * pAVar2->flCollisionScale + fVar4;
            local_2c[1] = *(float *)(iVar10 + 0x74) * pAVar2->flCollisionScale + fVar4;
            if ((((local_a4[2] <= *(float *)(iVar10 + 0x68) * pAVar2->flCollisionScale - fVar4) ||
                 (local_a4[1] <= *(float *)(iVar10 + 100) * pAVar2->flCollisionScale - fVar4)) ||
                ((local_2c[0] <= local_a4[1] ||
                 ((local_a4[0] <= local_44[2] ||
                  (*(float *)(iVar10 + 0x6c) * pAVar2->flCollisionScale + fVar4 <= local_a4[0]))))))
               || (local_2c[1] <= local_a4[2])) goto LAB_004940c6;
            self->pExtra->nCollided = 1;
            _DAT_008ca348 = self->aPos[0];
            _DAT_008ca34c = self->aPos[1];
            _DAT_008ca350 = self->aPos[2];
            local_8c[1] = (local_98[0] + self->aPrevPos[0]) - local_68[2];
            local_8c[2] = (self->aPrevPos[1] + local_98[1]) - local_5c[0];
            local_80[0] = (self->aPrevPos[2] + local_98[2]) - local_5c[1];
            pfVar8 = sputActor_GetOrientMatrix(actor);
            pfVar7 = local_8c + 1;
            pfVar11 = local_50 + 2;
            fVar12 = 6.726548e-39f;
            rdMatrix_TransformVectorOrtho34(pfVar11,pfVar7,pfVar8);
            local_50[2] = local_50[2] + *pfVar6;
            pfVar6 = local_80 + 1;
            local_44[0] = local_44[0] + *(float *)(iVar10 + 0x7c);
            local_44[1] = local_44[1] + *(float *)(iVar10 + 0x80);
            pfVar8 = local_44 + 2;
            pfVar9 = (float *)(_stkneg + 20);
            for (iVar10 = 6; iVar10 != 0; iVar10 = iVar10 + -1) {
              *pfVar9 = *pfVar8;
              pfVar8 = pfVar8 + 1;
              pfVar9 = pfVar9 + 1;
            }
            pfVar8 = local_50 + 2;
            iVar10 = Collision_BoxSlide(local_a4,pfVar8,in_stack_ffffff24,in_stack_ffffff28,
                                        (float)in_stack_ffffff2c,fVar12,(float)pfVar11,(float)pfVar7
                                        ,pfVar6);
            if (iVar10 == 0) {
              pfVar6 = actor->aPos;
              fVar13 = 6.726705e-39f;
              pfVar9 = sputActor_GetOrientMatrix(actor);
              pfVar7 = local_44 + 2;
              pfVar11 = (float *)(_stkneg + 16);
              for (iVar10 = 6; iVar10 != 0; iVar10 = iVar10 + -1) {
                *pfVar11 = *pfVar7;
                pfVar7 = pfVar7 + 1;
                pfVar11 = pfVar11 + 1;
              }
              GetOuttaTheBox(local_a4,(float)pfVar8,in_stack_ffffff24,in_stack_ffffff28,
                             (float)in_stack_ffffff2c,fVar12,fVar13,pfVar9,pfVar6);
              local_80[1] = local_a4[0];
              local_80[2] = local_a4[1];
            }
            pfVar6 = sputActor_GetOrientMatrix(actor);
            rdMatrix_TransformPoint34Acc(local_80 + 1,pfVar6);
            local_80[1] = local_80[1] - local_98[0];
            local_80[2] = local_80[2] - local_98[1];
            self->aPrevPos[0] = self->aPos[0];
            fVar12 = self->aPos[2];
            self->aPrevPos[1] = self->aPos[1];
            self->aPrevPos[2] = fVar12;
            pfVar6 = sputActor_GetOrientMatrix(actor);
            rdMatrix_TransformPoint34Acc(&FLOAT_008ca320,pfVar6);
            FLOAT_008ca320 = FLOAT_008ca320 - local_98[0];
            FLOAT_008ca324 = FLOAT_008ca324 - local_98[1];
            FLOAT_008ca328 = FLOAT_008ca328 - local_98[2];
            uVar5 = self->dwMoveFlags;
            sputActor_SetActorPosition(self,local_80 + 1);
            _DAT_008ca338 = self->aPos[0];
            _DAT_008ca33c = self->aPos[1];
            _DAT_008ca340 = self->aPos[2];
            if ((uVar5 & 1) != 0) {
              pAVar2 = self->pExtra;
              self->dwMoveFlags = self->dwMoveFlags | 1;
              pafVar1 = pAVar2->aPath + pAVar2->nPathNodes + -1;
              local_c = (uint)(*pafVar1)[0];
              local_8 = (uint)(*pafVar1)[1];
              local_4 = (uint)(*pafVar1)[2];
              sputActor_ActorWalkTo(self,(int)&local_c,pAVar2->aDest,actor);
            }
          }
          in_stack_ffffff28 = 6.727223e-39f;
          in_stack_ffffff2c = self;
          sputLua_CollisionHandler
                    ((int)self,(int)actor,(float *)&DAT_008ca348,&FLOAT_008ca320,
                     (float *)&DAT_008ca338);
        }
      }
LAB_004940c6:
      local_5c[2] = PUN(float,((int)local_5c[2] + 1));
      local_74[1] = PUN(float,((int)local_74[1] + 4));
    } while ((int)local_5c[2] < g_nTotActors);
  }
  return 1;
}
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

#endif


/* ---- 0x00494100  Collision_BoxSlide ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_58 */
/* Collision_BoxSlide: box collision response (entry face from the move, slide along the face).
   Head-on slides depend on float noise of a zero rotation axis, either side. Ported bit-exact as
   origBoxSlide in engines/grim/actor.cpp. */

undefined4 __cdecl
Collision_BoxSlide(float *from,float *to,float xmin,float ymin,float zmin,float xmax,float ymax,
                  float zmax,float *out)

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
  
  pfVar8 = out;
  iVar9 = 0;
  fVar10 = *from - *to;
  fVar1 = from[1] - to[1];
  fVar3 = from[2] - to[2];
  fVar11 = fVar10 * -10.0f + *to;
  fVar2 = fVar1 * -10.0f + to[1];
  fVar6 = fVar3 * -10.0f + to[2];
  *to = fVar11;
  fVar5 = 3.4028235e+38;
  to[1] = fVar2;
  to[2] = fVar6;
  if (xmax - 0.002 < fVar11) {
    fVar4 = fVar10;
    if (fVar10 < 0.0f) {
      fVar4 = -fVar10;
    }
    fVar4 = (xmax - *from) / fVar4;
    fVar7 = fVar4;
    if (fVar4 < 0.0f) {
      fVar7 = -fVar4;
    }
    fVar5 = 3.4028235e+38;
    if (fVar7 < 3.4028235e+38) {
      fVar5 = -fVar4;
      iVar9 = 1;
      local_3c = 1.0f;
      local_38[0] = 0.0f;
      local_38[1] = 0.0f;
    }
  }
  if (fVar11 < xmin - -0.002) {
    fVar11 = fVar10;
    if (fVar10 < 0.0f) {
      fVar11 = -fVar10;
    }
    fVar11 = (xmin - *from) / fVar11;
    fVar4 = fVar11;
    if (fVar11 < 0.0f) {
      fVar4 = -fVar11;
    }
    fVar7 = fVar5;
    if (fVar5 < 0.0f) {
      fVar7 = -fVar5;
    }
    if (fVar4 < fVar7) {
      iVar9 = 2;
      local_3c = -1.0f;
      local_38[0] = 0.0f;
      local_38[1] = 0.0f;
      fVar5 = fVar11;
    }
  }
  if (ymax - 0.002 < fVar2) {
    fVar11 = fVar1;
    if (fVar1 < 0.0f) {
      fVar11 = -fVar1;
    }
    fVar11 = (ymax - from[1]) / fVar11;
    fVar4 = fVar11;
    if (fVar11 < 0.0f) {
      fVar4 = -fVar11;
    }
    fVar7 = fVar5;
    if (fVar5 < 0.0f) {
      fVar7 = -fVar5;
    }
    if (fVar4 < fVar7) {
      fVar5 = -fVar11;
      iVar9 = 3;
      local_3c = 0.0f;
      local_38[0] = 1.0f;
      local_38[1] = 0.0f;
    }
  }
  if (fVar2 < ymin - -0.002) {
    fVar11 = fVar1;
    if (fVar1 < 0.0f) {
      fVar11 = -fVar1;
    }
    fVar11 = (ymin - from[1]) / fVar11;
    fVar2 = fVar11;
    if (fVar11 < 0.0f) {
      fVar2 = -fVar11;
    }
    fVar4 = fVar5;
    if (fVar5 < 0.0f) {
      fVar4 = -fVar5;
    }
    if (fVar2 < fVar4) {
      iVar9 = 4;
      local_3c = 0.0f;
      local_38[0] = -1.0f;
      local_38[1] = 0.0f;
      fVar5 = fVar11;
    }
  }
  if (zmax - 0.002 < fVar6) {
    fVar11 = fVar3;
    if (fVar3 < 0.0f) {
      fVar11 = -fVar3;
    }
    fVar11 = (zmax - from[2]) / fVar11;
    fVar2 = fVar11;
    if (fVar11 < 0.0f) {
      fVar2 = -fVar11;
    }
    fVar4 = fVar5;
    if (fVar5 < 0.0f) {
      fVar4 = -fVar5;
    }
    if (fVar2 < fVar4) {
      fVar5 = -fVar11;
      iVar9 = 5;
      local_3c = 0.0f;
      local_38[0] = 0.0f;
      local_38[1] = 1.0f;
    }
  }
  if (fVar6 < zmin - -0.002) {
    fVar11 = fVar3;
    if (fVar3 < 0.0f) {
      fVar11 = -fVar3;
    }
    fVar11 = (zmin - from[2]) / fVar11;
    fVar2 = fVar11;
    if (fVar11 < 0.0f) {
      fVar2 = -fVar11;
    }
    fVar6 = fVar5;
    if (fVar5 < 0.0f) {
      fVar6 = -fVar5;
    }
    if (fVar2 < fVar6) {
      iVar9 = 6;
      local_3c = 0.0f;
      local_38[0] = 0.0f;
      local_38[1] = -1.0f;
      fVar5 = fVar11;
    }
  }
  if (iVar9 == 0) {
    return 0;
  }
  *out = fVar5 * fVar10 + *from;
  out[1] = fVar5 * fVar1 + from[1];
  out[2] = fVar5 * fVar3 + from[2];
  FLOAT_008ca320 = *out;
  FLOAT_008ca324 = out[1];
  FLOAT_008ca328 = out[2];
  fVar11 = fVar5;
  if (fVar5 < 0.0f) {
    fVar11 = -fVar5;
  }
  local_48 = fVar10 * fVar11;
  fVar10 = fVar5;
  if (fVar5 < 0.0f) {
    fVar10 = -fVar5;
  }
  local_44[0] = fVar1 * fVar10;
  if (fVar5 < 0.0f) {
    fVar5 = -fVar5;
  }
  local_44[1] = fVar3 * fVar5;
  fVar10 = rdVector_Normalize3Acc(&local_48);
  fVar11 = rdVector_Dot3(&local_48,&local_3c);
  fVar11 = stdMath_ArcSin3(fVar11);
  if (90.0f - fVar11 < 90.0f) {
    return 0;
  }
  xmin = local_38[1] * local_44[0] - local_38[0] * local_44[1];
  ymin = local_3c * local_44[1] - local_38[1] * local_48;
  zmin = local_38[0] * local_48 - local_3c * local_44[0];
  rdVector_Normalize3Acc(&xmin);
  rdMatrix_BuildFromVectorAngle34(local_30,&xmin,(90.0f - fVar11) - 90.0f);
  rdMatrix_TransformVector34Acc(&local_48,local_30);
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

