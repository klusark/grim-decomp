/* GRIMFANDANGO.EXE :: rdclip.c
 * functions 0x00446c10 .. 0x0044da40 (14 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00446c10  rdClip_Line2D ---- */
/* Cohen-Sutherland line clip against a rectangle using rdClip_Outcode2D */

undefined4
rdClip_Line2D(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
             undefined4 *param_5)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = rdClip_Outcode2D(param_1,*param_2,*param_3);
  uVar2 = rdClip_Outcode2D(param_1,*param_4,*param_5);
  if ((uVar1 == 0) && (uVar2 == 0)) {
    return 1;
  }
  uVar3 = uVar1 & uVar2;
  while( true ) {
    if (uVar3 != 0) {
      return 0;
    }
    uVar3 = uVar1;
    if (uVar1 == 0) {
      uVar3 = uVar2;
    }
    if (uVar3 == uVar1) {
      lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      lVar4 = _ftol((double)CONCAT44(unaff_EDI,(int)lVar4));
      uVar1 = ((code *)rdClip_Outcode2D)(param_1,(int)lVar4);
    }
    else {
      lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      lVar4 = _ftol((double)CONCAT44(unaff_EDI,(int)lVar4));
      uVar2 = ((code *)rdClip_Outcode2D)(param_1,(int)lVar4);
    }
    if ((uVar1 == 0) && (uVar2 == 0)) break;
    uVar3 = uVar1 & uVar2;
  }
  lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  *param_2 = (int)lVar4;
  lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  *param_3 = (int)lVar4;
  lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  *param_4 = (int)lVar4;
  lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  *param_5 = (int)lVar4;
  return 1;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00446e80  rdClip_Outcode2D ---- */
uint rdClip_Outcode2D(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = 0;
  if (param_2 < *(int *)(param_1 + 0x18)) {
    uVar1 = 1;
  }
  else if (*(int *)(param_1 + 0x20) < param_2) {
    uVar1 = 0x10;
  }
  if (param_3 < *(int *)(param_1 + 0x1c)) {
    return uVar1 | 0x1000;
  }
  if (*(int *)(param_1 + 0x24) < param_3) {
    uVar1 = uVar1 | 0x100;
  }
  return uVar1;
}

/* ---- 0x00446ec0  rdClip_PointInFrustum ---- */
/* Near/far, then left/right/top/bottom; perspective frustums scale the side planes by depth */

int __cdecl rdClip_PointInFrustum(void *frustum,float *point)

{
  float fVar1;
  int iVar2;
  
  if (point[1] < *(float *)((int)frustum + 4)) {
    return 0;
  }
  if ((*(int *)frustum != 0) && (*(float *)((int)frustum + 8) < point[1])) {
    return 0;
  }
  iVar2 = *(int *)g_pRdCurrentCamera;
  if (iVar2 == 1) {
    fVar1 = *(float *)((int)frustum + 0x24) * point[1];
  }
  else {
    fVar1 = *(float *)((int)frustum + 0xc);
  }
  if (*point < fVar1) {
    return 0;
  }
  if (iVar2 == 1) {
    fVar1 = *(float *)((int)frustum + 0x28) * point[1];
  }
  else {
    fVar1 = *(float *)((int)frustum + 0x14);
  }
  if (fVar1 < *point) {
    return 0;
  }
  if (iVar2 == 1) {
    fVar1 = *(float *)((int)frustum + 0x1c) * point[1];
  }
  else {
    fVar1 = *(float *)((int)frustum + 0x10);
  }
  if (fVar1 < point[2]) {
    return 0;
  }
  if (iVar2 == 1) {
    fVar1 = *(float *)((int)frustum + 0x20) * point[1];
  }
  else {
    fVar1 = *(float *)((int)frustum + 0x18);
  }
  if (point[2] < fVar1) {
    return 0;
  }
  return 1;
}

/* ---- 0x00446f80  rdClip_Line3 ---- */
int __cdecl rdClip_Line3(void *frustum,float *p0,float *p1,int *clipped0,int *clipped1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  if ((p0[1] < *(float *)((int)frustum + 4)) && (p1[1] < *(float *)((int)frustum + 4))) {
    return 0;
  }
  if (*(float *)((int)frustum + 4) <= p0[1]) {
    if (p1[1] < *(float *)((int)frustum + 4)) {
      fVar3 = (*(float *)((int)frustum + 4) - p0[1]) / (p1[1] - p0[1]);
      p1[1] = *(float *)((int)frustum + 4);
      p1[2] = (p1[2] - p0[2]) * fVar3 + p0[2];
      *p1 = (*p1 - *p0) * fVar3 + *p0;
      if (clipped1 != (int *)0x0) {
        *clipped1 = 1;
      }
    }
  }
  else {
    fVar3 = (*(float *)((int)frustum + 4) - p0[1]) / (p1[1] - p0[1]);
    p0[1] = *(float *)((int)frustum + 4);
    p0[2] = (p1[2] - p0[2]) * fVar3 + p0[2];
    *p0 = (*p1 - *p0) * fVar3 + *p0;
    if (clipped0 != (int *)0x0) {
      *clipped0 = 1;
    }
  }
  if (*(int *)frustum != 0) {
    if ((*(float *)((int)frustum + 8) < p0[1]) && (*(float *)((int)frustum + 8) < p1[1])) {
      return 0;
    }
    if (p0[1] <= *(float *)((int)frustum + 8)) {
      if (*(float *)((int)frustum + 8) < p1[1]) {
        fVar3 = (*(float *)((int)frustum + 8) - p0[1]) / (p1[1] - p0[1]);
        p1[1] = *(float *)((int)frustum + 8);
        p1[2] = (p1[2] - p0[2]) * fVar3 + p0[2];
        *p1 = (*p1 - *p0) * fVar3 + *p0;
        if (clipped1 != (int *)0x0) {
          *clipped1 = 1;
        }
      }
    }
    else {
      fVar3 = (*(float *)((int)frustum + 8) - p0[1]) / (p1[1] - p0[1]);
      p0[1] = *(float *)((int)frustum + 8);
      p0[2] = (p1[2] - p0[2]) * fVar3 + p0[2];
      *p0 = (*p1 - *p0) * fVar3 + *p0;
      if (clipped0 != (int *)0x0) {
        *clipped0 = 1;
      }
    }
  }
  fVar3 = *(float *)((int)frustum + 0x24) * p0[1];
  fVar4 = *(float *)((int)frustum + 0x24) * p1[1];
  if ((*p0 < fVar3) && (*p1 < fVar4)) {
    return 0;
  }
  if (fVar3 <= *p0) {
    if (*p1 < fVar4) {
      fVar3 = p1[1] - p0[1];
      fVar1 = *p1 - *p0;
      fVar4 = *(float *)((int)frustum + 0x24) * fVar3 - fVar1;
      fVar5 = p1[1] * *p0 - p0[1] * *p1;
      if (fVar4 != 0.0) {
        fVar5 = fVar5 / fVar4;
      }
      fVar4 = *(float *)((int)frustum + 0x24) * fVar5;
      fVar2 = fVar3;
      if (fVar3 < 0.0) {
        fVar2 = -fVar3;
      }
      fVar6 = fVar1;
      if (fVar1 < 0.0) {
        fVar6 = -fVar1;
      }
      if (fVar2 <= fVar6) {
        fVar3 = (fVar4 - *p0) / fVar1;
      }
      else {
        fVar3 = (fVar5 - p0[1]) / fVar3;
      }
      *p1 = fVar4;
      p1[1] = fVar5;
      p1[2] = (p1[2] - p0[2]) * fVar3 + p0[2];
      if (clipped1 != (int *)0x0) {
        *clipped1 = 1;
      }
    }
  }
  else {
    fVar3 = p1[1] - p0[1];
    fVar1 = *p1 - *p0;
    fVar4 = *(float *)((int)frustum + 0x24) * fVar3 - fVar1;
    fVar5 = p1[1] * *p0 - p0[1] * *p1;
    if (fVar4 != 0.0) {
      fVar5 = fVar5 / fVar4;
    }
    fVar4 = *(float *)((int)frustum + 0x24) * fVar5;
    fVar2 = fVar3;
    if (fVar3 < 0.0) {
      fVar2 = -fVar3;
    }
    fVar6 = fVar1;
    if (fVar1 < 0.0) {
      fVar6 = -fVar1;
    }
    if (fVar2 <= fVar6) {
      fVar3 = (fVar4 - *p0) / fVar1;
    }
    else {
      fVar3 = (fVar5 - p0[1]) / fVar3;
    }
    *p0 = fVar4;
    p0[1] = fVar5;
    p0[2] = (p1[2] - p0[2]) * fVar3 + p0[2];
    if (clipped0 != (int *)0x0) {
      *clipped0 = 1;
    }
  }
  fVar3 = *(float *)((int)frustum + 0x28) * p0[1];
  fVar4 = *(float *)((int)frustum + 0x28) * p1[1];
  if ((fVar3 < *p0) && (fVar4 < *p1)) {
    return 0;
  }
  if (*p0 <= fVar3) {
    if (fVar4 < *p1) {
      fVar3 = p1[1] - p0[1];
      fVar1 = *p1 - *p0;
      fVar4 = *(float *)((int)frustum + 0x28) * fVar3 - fVar1;
      fVar5 = p1[1] * *p0 - p0[1] * *p1;
      if (fVar4 != 0.0) {
        fVar5 = fVar5 / fVar4;
      }
      fVar4 = *(float *)((int)frustum + 0x28) * fVar5;
      fVar2 = fVar3;
      if (fVar3 < 0.0) {
        fVar2 = -fVar3;
      }
      fVar6 = fVar1;
      if (fVar1 < 0.0) {
        fVar6 = -fVar1;
      }
      if (fVar2 <= fVar6) {
        fVar3 = (fVar4 - *p0) / fVar1;
      }
      else {
        fVar3 = (fVar5 - p0[1]) / fVar3;
      }
      *p1 = fVar4;
      p1[1] = fVar5;
      p1[2] = (p1[2] - p0[2]) * fVar3 + p0[2];
      if (clipped1 != (int *)0x0) {
        *clipped1 = 1;
      }
    }
  }
  else {
    fVar3 = p1[1] - p0[1];
    fVar1 = *p1 - *p0;
    fVar4 = *(float *)((int)frustum + 0x28) * fVar3 - fVar1;
    fVar5 = p1[1] * *p0 - p0[1] * *p1;
    if (fVar4 != 0.0) {
      fVar5 = fVar5 / fVar4;
    }
    fVar4 = *(float *)((int)frustum + 0x28) * fVar5;
    fVar2 = fVar3;
    if (fVar3 < 0.0) {
      fVar2 = -fVar3;
    }
    fVar6 = fVar1;
    if (fVar1 < 0.0) {
      fVar6 = -fVar1;
    }
    if (fVar2 <= fVar6) {
      fVar3 = (fVar4 - *p0) / fVar1;
    }
    else {
      fVar3 = (fVar5 - p0[1]) / fVar3;
    }
    *p0 = fVar4;
    p0[1] = fVar5;
    p0[2] = (p1[2] - p0[2]) * fVar3 + p0[2];
    if (clipped0 != (int *)0x0) {
      *clipped0 = 1;
    }
  }
  fVar3 = *(float *)((int)frustum + 0x1c) * p0[1];
  fVar4 = *(float *)((int)frustum + 0x1c) * p1[1];
  if ((fVar3 < p0[2]) && (fVar4 < p1[2])) {
    return 0;
  }
  if (p0[2] <= fVar3) {
    if (fVar4 < p1[2]) {
      fVar3 = p1[1] - p0[1];
      fVar1 = p1[2] - p0[2];
      fVar4 = *(float *)((int)frustum + 0x1c) * fVar3 - fVar1;
      fVar5 = p0[2] * p1[1] - p1[2] * p0[1];
      if (fVar4 != 0.0) {
        fVar5 = fVar5 / fVar4;
      }
      fVar4 = *(float *)((int)frustum + 0x1c) * fVar5;
      fVar2 = fVar3;
      if (fVar3 < 0.0) {
        fVar2 = -fVar3;
      }
      fVar6 = fVar1;
      if (fVar1 < 0.0) {
        fVar6 = -fVar1;
      }
      if (fVar2 <= fVar6) {
        fVar3 = (fVar4 - p0[2]) / fVar1;
      }
      else {
        fVar3 = (fVar5 - p0[1]) / fVar3;
      }
      fVar1 = *p0;
      fVar2 = *p0;
      p1[1] = fVar5;
      p1[2] = fVar4;
      *p1 = (*p1 - fVar1) * fVar3 + fVar2;
      if (clipped1 != (int *)0x0) {
        *clipped1 = 1;
      }
    }
  }
  else {
    fVar3 = p1[1] - p0[1];
    fVar1 = p1[2] - p0[2];
    fVar4 = *(float *)((int)frustum + 0x1c) * fVar3 - fVar1;
    fVar5 = p0[2] * p1[1] - p1[2] * p0[1];
    if (fVar4 != 0.0) {
      fVar5 = fVar5 / fVar4;
    }
    fVar4 = *(float *)((int)frustum + 0x1c) * fVar5;
    fVar2 = fVar3;
    if (fVar3 < 0.0) {
      fVar2 = -fVar3;
    }
    fVar6 = fVar1;
    if (fVar1 < 0.0) {
      fVar6 = -fVar1;
    }
    if (fVar2 <= fVar6) {
      fVar3 = (fVar4 - p0[2]) / fVar1;
    }
    else {
      fVar3 = (fVar5 - p0[1]) / fVar3;
    }
    fVar1 = *p1;
    p0[1] = fVar5;
    p0[2] = fVar4;
    *p0 = (fVar1 - *p0) * fVar3 + *p0;
    if (clipped0 != (int *)0x0) {
      *clipped0 = 1;
    }
  }
  fVar3 = *(float *)((int)frustum + 0x20) * p0[1];
  fVar4 = *(float *)((int)frustum + 0x20) * p1[1];
  if ((p0[2] < fVar3) && (p1[2] < fVar4)) {
    return 0;
  }
  if (fVar3 <= p0[2]) {
    if (p1[2] < fVar4) {
      fVar3 = p1[1] - p0[1];
      fVar1 = p1[2] - p0[2];
      fVar4 = *(float *)((int)frustum + 0x20) * fVar3 - fVar1;
      fVar5 = p0[2] * p1[1] - p1[2] * p0[1];
      if (fVar4 != 0.0) {
        fVar5 = fVar5 / fVar4;
      }
      fVar4 = *(float *)((int)frustum + 0x20) * fVar5;
      fVar2 = fVar3;
      if (fVar3 < 0.0) {
        fVar2 = -fVar3;
      }
      fVar6 = fVar1;
      if (fVar1 < 0.0) {
        fVar6 = -fVar1;
      }
      if (fVar2 <= fVar6) {
        fVar3 = (fVar4 - p0[2]) / fVar1;
      }
      else {
        fVar3 = (fVar5 - p0[1]) / fVar3;
      }
      fVar1 = *p0;
      fVar2 = *p0;
      p1[1] = fVar5;
      p1[2] = fVar4;
      *p1 = (*p1 - fVar1) * fVar3 + fVar2;
      if (clipped1 != (int *)0x0) {
        *clipped1 = 1;
      }
    }
  }
  else {
    fVar3 = p1[1] - p0[1];
    fVar1 = p1[2] - p0[2];
    fVar4 = *(float *)((int)frustum + 0x20) * fVar3 - fVar1;
    fVar5 = p0[2] * p1[1] - p1[2] * p0[1];
    if (fVar4 != 0.0) {
      fVar5 = fVar5 / fVar4;
    }
    fVar4 = *(float *)((int)frustum + 0x20) * fVar5;
    fVar2 = fVar3;
    if (fVar3 < 0.0) {
      fVar2 = -fVar3;
    }
    fVar6 = fVar1;
    if (fVar1 < 0.0) {
      fVar6 = -fVar1;
    }
    if (fVar2 <= fVar6) {
      fVar3 = (fVar4 - p0[2]) / fVar1;
    }
    else {
      fVar3 = (fVar5 - p0[1]) / fVar3;
    }
    fVar1 = *p1;
    p0[1] = fVar5;
    p0[2] = fVar4;
    *p0 = (fVar1 - *p0) * fVar3 + *p0;
    if (clipped0 != (int *)0x0) {
      *clipped0 = 1;
      return 1;
    }
  }
  return 1;
}

/* ---- 0x004478c0  rdClip_Face3_Pos ---- */
/* Frustum clip of a face with position-only vertices (output into the rdClip work buffers at
   g_RdClipVerts). Attribute set inferred from the parameter list */

uint rdClip_Face3_Pos(int *param_1,float *param_2,uint param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint *puVar14;
  float *pfVar15;
  uint uVar16;
  uint uVar17;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar12 = 0;
  puVar14 = &UINT_007f48c0;
  UINT_007f4ac4 = 0;
  UINT_007f47b8 = (uint)param_2;
  UINT_007f46ac = (uint)&UINT_007f48c0;
  if (0 < (int)param_3) {
    iVar11 = 0;
    local_4 = param_3;
    pfVar15 = param_2 + param_3 * 3 + -3;
    pfVar8 = param_2;
    do {
      fVar2 = pfVar15[1] * (float)param_1[9];
      fVar3 = pfVar8[1] * (float)param_1[9];
      if ((fVar2 <= *pfVar15) || (fVar3 <= *pfVar8)) {
        if (((*pfVar15 != fVar2) && (fVar3 != *pfVar8)) && ((*pfVar15 < fVar2 || (*pfVar8 < fVar3)))
           ) {
          fVar2 = pfVar8[1] - pfVar15[1];
          fVar4 = *pfVar8 - *pfVar15;
          fVar1 = (float)param_1[9] * fVar2 - fVar4;
          fVar5 = pfVar8[1] * *pfVar15 - pfVar15[1] * *pfVar8;
          if (fVar1 != 0.0) {
            fVar5 = fVar5 / fVar1;
          }
          fVar1 = fVar2;
          if (fVar2 < 0.0) {
            fVar1 = -fVar2;
          }
          fVar6 = fVar4;
          if (fVar4 < 0.0) {
            fVar6 = -fVar4;
          }
          if (fVar1 <= fVar6) {
            fVar2 = ((float)param_1[9] * fVar5 - *pfVar15) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar15[1]) / fVar2;
          }
          *(float *)((int)puVar14 + iVar11) = (float)param_1[9] * fVar5;
          uVar12 = uVar12 + 1;
          *(float *)(UINT_007f46ac + 4 + iVar11) = fVar5;
          iVar11 = iVar11 + 0xc;
          *(float *)((UINT_007f46ac - 4) + iVar11) = (pfVar8[2] - pfVar15[2]) * fVar2 + pfVar15[2];
          UINT_007f4ac4 = UINT_007f4ac4 | 0x10;
          puVar14 = (uint *)UINT_007f46ac;
        }
        if (fVar3 <= *pfVar8) {
          pfVar15 = (float *)((int)puVar14 + iVar11);
          uVar12 = uVar12 + 1;
          iVar11 = iVar11 + 0xc;
          *pfVar15 = *pfVar8;
          pfVar15[1] = pfVar8[1];
          pfVar15[2] = pfVar8[2];
          puVar14 = (uint *)UINT_007f46ac;
        }
      }
      local_4 = local_4 - 1;
      pfVar15 = pfVar8;
      pfVar8 = pfVar8 + 3;
    } while (local_4 != 0);
  }
  if (2 < (int)uVar12) {
    uVar13 = 0;
    uVar17 = UINT_007f47b8;
    UINT_007f46ac = UINT_007f47b8;
    pfVar15 = (float *)puVar14;
    if (0 < (int)uVar12) {
      iVar11 = 0;
      pfVar8 = (float *)(puVar14 + uVar12 * 3 + -3);
      UINT_007f47b8 = (uint)puVar14;
      local_4 = uVar12;
      do {
        fVar2 = (float)param_1[10] * pfVar8[1];
        fVar3 = (float)param_1[10] * (float)puVar14[1];
        if ((*pfVar8 <= fVar2) || ((float)*puVar14 <= fVar3)) {
          if (((*pfVar8 != fVar2) && (fVar3 != (float)*puVar14)) &&
             ((fVar2 < *pfVar8 || (fVar3 < (float)*puVar14)))) {
            fVar2 = (float)puVar14[1] - pfVar8[1];
            fVar4 = (float)*puVar14 - *pfVar8;
            fVar1 = (float)param_1[10] * fVar2 - fVar4;
            fVar5 = (float)puVar14[1] * *pfVar8 - pfVar8[1] * (float)*puVar14;
            if (fVar1 != 0.0) {
              fVar5 = fVar5 / fVar1;
            }
            fVar1 = fVar2;
            if (fVar2 < 0.0) {
              fVar1 = -fVar2;
            }
            fVar6 = fVar4;
            if (fVar4 < 0.0) {
              fVar6 = -fVar4;
            }
            if (fVar1 <= fVar6) {
              fVar2 = ((float)param_1[10] * fVar5 - *pfVar8) / fVar4;
            }
            else {
              fVar2 = (fVar5 - pfVar8[1]) / fVar2;
            }
            *(float *)(uVar17 + iVar11) = (float)param_1[10] * fVar5;
            uVar13 = uVar13 + 1;
            *(float *)(UINT_007f46ac + 4 + iVar11) = fVar5;
            iVar11 = iVar11 + 0xc;
            *(float *)((UINT_007f46ac - 4) + iVar11) =
                 ((float)puVar14[2] - pfVar8[2]) * fVar2 + pfVar8[2];
            UINT_007f4ac4 = UINT_007f4ac4 | 0x20;
            uVar17 = UINT_007f46ac;
          }
          if ((float)*puVar14 <= fVar3) {
            pfVar15 = (float *)(uVar17 + iVar11);
            uVar13 = uVar13 + 1;
            iVar11 = iVar11 + 0xc;
            *pfVar15 = (float)*puVar14;
            pfVar15[1] = (float)puVar14[1];
            pfVar15[2] = (float)puVar14[2];
            uVar17 = UINT_007f46ac;
          }
        }
        local_4 = local_4 - 1;
        pfVar8 = (float *)puVar14;
        puVar14 = puVar14 + 3;
        pfVar15 = (float *)UINT_007f47b8;
      } while (local_4 != 0);
    }
    UINT_007f47b8 = (uint)pfVar15;
    uVar12 = uVar13;
    if (2 < (int)uVar12) {
      uVar13 = 0;
      UINT_007f46ac = UINT_007f47b8;
      pfVar15 = (float *)((uVar17 - 0xc) + uVar12 * 0xc);
      uVar16 = UINT_007f47b8;
      if (0 < (int)uVar12) {
        iVar11 = 0;
        pfVar8 = (float *)(uVar17 + 8);
        UINT_007f47b8 = uVar17;
        local_4 = uVar12;
        do {
          fVar2 = (float)param_1[7] * pfVar15[1];
          fVar3 = pfVar8[-1] * (float)param_1[7];
          if ((pfVar15[2] <= fVar2) || (*pfVar8 <= fVar3)) {
            if (((pfVar15[2] != fVar2) && (fVar3 != *pfVar8)) &&
               ((fVar2 < pfVar15[2] || (fVar3 < *pfVar8)))) {
              fVar2 = pfVar8[-1] - pfVar15[1];
              fVar4 = *pfVar8 - pfVar15[2];
              fVar1 = (float)param_1[7] * fVar2 - fVar4;
              fVar5 = pfVar15[2] * pfVar8[-1] - pfVar15[1] * *pfVar8;
              if (fVar1 != 0.0) {
                fVar5 = fVar5 / fVar1;
              }
              fVar1 = (float)param_1[7];
              fVar6 = fVar2;
              if (fVar2 < 0.0) {
                fVar6 = -fVar2;
              }
              fVar7 = fVar4;
              if (fVar4 < 0.0) {
                fVar7 = -fVar4;
              }
              if (fVar6 <= fVar7) {
                fVar2 = (fVar1 * fVar5 - pfVar15[2]) / fVar4;
              }
              else {
                fVar2 = (fVar5 - pfVar15[1]) / fVar2;
              }
              uVar13 = uVar13 + 1;
              iVar11 = iVar11 + 0xc;
              *(float *)((uVar16 - 0xc) + iVar11) = (pfVar8[-2] - *pfVar15) * fVar2 + *pfVar15;
              *(float *)((UINT_007f46ac - 8) + iVar11) = fVar5;
              *(float *)((UINT_007f46ac - 4) + iVar11) = fVar1 * fVar5;
              UINT_007f4ac4 = UINT_007f4ac4 | 4;
              uVar16 = UINT_007f46ac;
            }
            if (*pfVar8 <= fVar3) {
              pfVar15 = (float *)(uVar16 + iVar11);
              uVar13 = uVar13 + 1;
              iVar11 = iVar11 + 0xc;
              *pfVar15 = pfVar8[-2];
              pfVar15[1] = pfVar8[-1];
              pfVar15[2] = *pfVar8;
              uVar16 = UINT_007f46ac;
            }
          }
          pfVar15 = pfVar8 + -2;
          pfVar8 = pfVar8 + 3;
          local_4 = local_4 - 1;
          uVar17 = UINT_007f47b8;
        } while (local_4 != 0);
      }
      UINT_007f47b8 = uVar17;
      uVar12 = uVar13;
      if (2 < (int)uVar12) {
        uVar13 = 0;
        UINT_007f46ac = UINT_007f47b8;
        pfVar15 = (float *)((uVar16 - 0xc) + uVar12 * 0xc);
        uVar17 = UINT_007f47b8;
        if (0 < (int)uVar12) {
          iVar11 = 0;
          pfVar8 = (float *)(uVar16 + 8);
          UINT_007f47b8 = uVar16;
          local_4 = uVar12;
          do {
            fVar2 = (float)param_1[8] * pfVar15[1];
            fVar3 = pfVar8[-1] * (float)param_1[8];
            if ((fVar2 <= pfVar15[2]) || (fVar3 <= *pfVar8)) {
              if (((pfVar15[2] != fVar2) && (fVar3 != *pfVar8)) &&
                 ((pfVar15[2] < fVar2 || (*pfVar8 < fVar3)))) {
                fVar2 = pfVar8[-1] - pfVar15[1];
                fVar4 = *pfVar8 - pfVar15[2];
                fVar1 = (float)param_1[8] * fVar2 - fVar4;
                fVar5 = pfVar15[2] * pfVar8[-1] - pfVar15[1] * *pfVar8;
                if (fVar1 != 0.0) {
                  fVar5 = fVar5 / fVar1;
                }
                fVar1 = (float)param_1[8];
                fVar6 = fVar2;
                if (fVar2 < 0.0) {
                  fVar6 = -fVar2;
                }
                fVar7 = fVar4;
                if (fVar4 < 0.0) {
                  fVar7 = -fVar4;
                }
                if (fVar6 <= fVar7) {
                  fVar2 = (fVar1 * fVar5 - pfVar15[2]) / fVar4;
                }
                else {
                  fVar2 = (fVar5 - pfVar15[1]) / fVar2;
                }
                uVar13 = uVar13 + 1;
                iVar11 = iVar11 + 0xc;
                *(float *)((uVar17 - 0xc) + iVar11) = (pfVar8[-2] - *pfVar15) * fVar2 + *pfVar15;
                *(float *)((UINT_007f46ac - 8) + iVar11) = fVar5;
                *(float *)((UINT_007f46ac - 4) + iVar11) = fVar1 * fVar5;
                UINT_007f4ac4 = UINT_007f4ac4 | 8;
                uVar17 = UINT_007f46ac;
              }
              if (fVar3 <= *pfVar8) {
                pfVar15 = (float *)(uVar17 + iVar11);
                uVar13 = uVar13 + 1;
                iVar11 = iVar11 + 0xc;
                *pfVar15 = pfVar8[-2];
                pfVar15[1] = pfVar8[-1];
                pfVar15[2] = *pfVar8;
                uVar17 = UINT_007f46ac;
              }
            }
            pfVar15 = pfVar8 + -2;
            pfVar8 = pfVar8 + 3;
            local_4 = local_4 - 1;
            uVar16 = UINT_007f47b8;
          } while (local_4 != 0);
        }
        UINT_007f47b8 = uVar16;
        uVar12 = uVar13;
        if (2 < (int)uVar12) {
          uVar13 = 0;
          UINT_007f46ac = UINT_007f47b8;
          pfVar15 = (float *)((uVar17 - 0xc) + uVar12 * 0xc);
          pfVar8 = (float *)UINT_007f47b8;
          if (0 < (int)uVar12) {
            iVar11 = 0;
            pfVar9 = (float *)(uVar17 + 4);
            UINT_007f47b8 = uVar17;
            param_3 = uVar12;
            do {
              if (((float)param_1[1] <= pfVar15[1]) || ((float)param_1[1] <= *pfVar9)) {
                if (((pfVar15[1] != (float)param_1[1]) && (*pfVar9 != (float)param_1[1])) &&
                   ((pfVar15[1] < (float)param_1[1] || (*pfVar9 < (float)param_1[1])))) {
                  uVar13 = uVar13 + 1;
                  fVar2 = ((float)param_1[1] - pfVar15[1]) / (*pfVar9 - pfVar15[1]);
                  *(int *)((int)pfVar8 + iVar11 + 4) = param_1[1];
                  iVar11 = iVar11 + 0xc;
                  *(float *)((UINT_007f46ac - 4) + iVar11) =
                       (pfVar9[1] - pfVar15[2]) * fVar2 + pfVar15[2];
                  *(float *)((UINT_007f46ac - 0xc) + iVar11) =
                       (pfVar9[-1] - *pfVar15) * fVar2 + *pfVar15;
                  UINT_007f4ac4 = UINT_007f4ac4 | 1;
                  pfVar8 = (float *)UINT_007f46ac;
                }
                if ((float)param_1[1] <= *pfVar9) {
                  pfVar8 = (float *)((int)pfVar8 + iVar11);
                  uVar13 = uVar13 + 1;
                  iVar11 = iVar11 + 0xc;
                  *pfVar8 = pfVar9[-1];
                  pfVar8[1] = *pfVar9;
                  pfVar8[2] = pfVar9[1];
                  pfVar8 = (float *)UINT_007f46ac;
                }
              }
              pfVar15 = pfVar9 + -1;
              pfVar9 = pfVar9 + 3;
              param_3 = param_3 - 1;
              uVar17 = UINT_007f47b8;
            } while (param_3 != 0);
          }
          UINT_007f47b8 = uVar17;
          if ((int)uVar13 < 3) {
            UINT_007f4ac4 = UINT_007f4ac4 | 0x40;
            return uVar13;
          }
          uVar12 = uVar13;
          pfVar15 = pfVar8;
          if (*param_1 != 0) {
            uVar12 = 0;
            pfVar9 = pfVar8 + uVar13 * 3 + -3;
            pfVar15 = (float *)UINT_007f47b8;
            UINT_007f46ac = UINT_007f47b8;
            if (0 < (int)uVar13) {
              iVar11 = 0;
              pfVar10 = pfVar8 + 1;
              UINT_007f47b8 = (uint)pfVar8;
              param_3 = uVar13;
              do {
                if ((pfVar9[1] <= (float)param_1[2]) || (*pfVar10 <= (float)param_1[2])) {
                  if (((pfVar9[1] != (float)param_1[2]) && (*pfVar10 != (float)param_1[2])) &&
                     (((float)param_1[2] < pfVar9[1] || ((float)param_1[2] < *pfVar10)))) {
                    uVar12 = uVar12 + 1;
                    fVar2 = ((float)param_1[2] - pfVar9[1]) / (*pfVar10 - pfVar9[1]);
                    *(int *)((int)pfVar15 + iVar11 + 4) = param_1[2];
                    iVar11 = iVar11 + 0xc;
                    *(float *)((UINT_007f46ac - 4) + iVar11) =
                         (pfVar10[1] - pfVar9[2]) * fVar2 + pfVar9[2];
                    *(float *)((UINT_007f46ac - 0xc) + iVar11) =
                         (pfVar10[-1] - *pfVar9) * fVar2 + *pfVar9;
                    UINT_007f4ac4 = UINT_007f4ac4 | 2;
                    pfVar15 = (float *)UINT_007f46ac;
                  }
                  if (*pfVar10 <= (float)param_1[2]) {
                    pfVar15 = (float *)((int)pfVar15 + iVar11);
                    uVar12 = uVar12 + 1;
                    iVar11 = iVar11 + 0xc;
                    *pfVar15 = pfVar10[-1];
                    pfVar15[1] = *pfVar10;
                    pfVar15[2] = pfVar10[1];
                    pfVar15 = (float *)UINT_007f46ac;
                  }
                }
                pfVar9 = pfVar10 + -1;
                pfVar10 = pfVar10 + 3;
                param_3 = param_3 - 1;
                pfVar8 = (float *)UINT_007f47b8;
              } while (param_3 != 0);
            }
            UINT_007f47b8 = (uint)pfVar8;
            if ((int)uVar12 < 3) {
              return uVar12;
            }
          }
          if (pfVar15 != param_2) {
            for (uVar13 = uVar12 * 3 & 0x3fffffff; uVar13 != 0; uVar13 = uVar13 - 1) {
              *param_2 = *pfVar15;
              pfVar15 = pfVar15 + 1;
              param_2 = param_2 + 1;
            }
            for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
              *(undefined1 *)param_2 = *(undefined1 *)pfVar15;
              pfVar15 = (float *)((int)pfVar15 + 1);
              param_2 = (float *)((int)param_2 + 1);
            }
          }
        }
      }
    }
  }
  return uVar12;
}
#undef local_4
#undef local_8


/* ---- 0x00448260  rdClip_Face3_PosB ---- */
/* Second position-only face clipper (likely the orthographic variant) */

int rdClip_Face3_PosB(int *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  uint uVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint *puVar10;
  float *pfVar11;
  uint uVar12;
  float *pfVar13;
  
  iVar7 = 0;
  puVar10 = &UINT_007f48c0;
  iVar9 = 0;
  UINT_007f4ac4 = 0;
  UINT_007f47b8 = (uint)param_2;
  UINT_007f46ac = (uint)&UINT_007f48c0;
  pfVar11 = param_2 + param_3 * 3 + -3;
  pfVar13 = param_2;
  if (0 < param_3) {
    do {
      fVar2 = (float)param_1[3];
      fVar1 = (float)param_1[3];
      if ((fVar2 <= *pfVar11) || (fVar1 <= *pfVar13)) {
        iVar8 = iVar7;
        if (((*pfVar11 != fVar2) && (fVar1 != *pfVar13)) &&
           ((*pfVar11 < fVar2 || (*pfVar13 < fVar1)))) {
          fVar3 = (fVar2 - *pfVar11) / (*pfVar13 - *pfVar11);
          iVar9 = iVar9 + 1;
          iVar8 = iVar7 + 0xc;
          *(float *)((int)puVar10 + iVar7) = fVar2;
          *(float *)((UINT_007f46ac - 8) + iVar8) = (pfVar13[1] - pfVar11[1]) * fVar3 + pfVar11[1];
          *(float *)((UINT_007f46ac - 4) + iVar8) = (pfVar13[2] - pfVar11[2]) * fVar3 + pfVar11[2];
          UINT_007f4ac4 = UINT_007f4ac4 | 0x10;
          puVar10 = (uint *)UINT_007f46ac;
        }
        iVar7 = iVar8;
        if (fVar1 <= *pfVar13) {
          pfVar11 = (float *)((int)puVar10 + iVar8);
          iVar9 = iVar9 + 1;
          iVar7 = iVar8 + 0xc;
          *pfVar11 = *pfVar13;
          pfVar11[1] = pfVar13[1];
          pfVar11[2] = pfVar13[2];
          puVar10 = (uint *)UINT_007f46ac;
        }
      }
      param_3 = param_3 + -1;
      pfVar11 = pfVar13;
      pfVar13 = pfVar13 + 3;
    } while (param_3 != 0);
  }
  if (2 < iVar9) {
    iVar7 = 0;
    uVar5 = UINT_007f47b8;
    UINT_007f46ac = UINT_007f47b8;
    pfVar11 = (float *)puVar10;
    if (0 < iVar9) {
      iVar8 = 0;
      pfVar13 = (float *)(puVar10 + iVar9 * 3 + -3);
      UINT_007f47b8 = (uint)puVar10;
      param_3 = iVar9;
      do {
        fVar2 = (float)param_1[5];
        fVar1 = (float)param_1[5];
        if ((*pfVar13 <= fVar2) || ((float)*puVar10 <= fVar1)) {
          if (((*pfVar13 != fVar2) && (fVar1 != (float)*puVar10)) &&
             ((fVar2 < *pfVar13 || (fVar1 < (float)*puVar10)))) {
            fVar3 = (fVar2 - *pfVar13) / ((float)*puVar10 - *pfVar13);
            iVar7 = iVar7 + 1;
            iVar8 = iVar8 + 0xc;
            *(float *)((uVar5 - 0xc) + iVar8) = fVar2;
            *(float *)((UINT_007f46ac - 8) + iVar8) =
                 ((float)puVar10[1] - pfVar13[1]) * fVar3 + pfVar13[1];
            *(float *)((UINT_007f46ac - 4) + iVar8) =
                 ((float)puVar10[2] - pfVar13[2]) * fVar3 + pfVar13[2];
            UINT_007f4ac4 = UINT_007f4ac4 | 0x20;
            uVar5 = UINT_007f46ac;
          }
          if ((float)*puVar10 <= fVar1) {
            pfVar11 = (float *)(uVar5 + iVar8);
            iVar7 = iVar7 + 1;
            iVar8 = iVar8 + 0xc;
            *pfVar11 = (float)*puVar10;
            pfVar11[1] = (float)puVar10[1];
            pfVar11[2] = (float)puVar10[2];
            uVar5 = UINT_007f46ac;
          }
        }
        param_3 = param_3 + -1;
        pfVar13 = (float *)puVar10;
        puVar10 = puVar10 + 3;
        pfVar11 = (float *)UINT_007f47b8;
      } while (param_3 != 0);
    }
    UINT_007f47b8 = (uint)pfVar11;
    iVar9 = iVar7;
    if (2 < iVar9) {
      iVar7 = 0;
      pfVar11 = (float *)((uVar5 - 0xc) + iVar9 * 0xc);
      uVar12 = UINT_007f47b8;
      UINT_007f46ac = UINT_007f47b8;
      if (0 < iVar9) {
        pfVar13 = (float *)(uVar5 + 8);
        iVar8 = 0;
        UINT_007f47b8 = uVar5;
        param_3 = iVar9;
        do {
          fVar2 = (float)param_1[4];
          fVar1 = (float)param_1[4];
          if ((pfVar11[2] <= fVar2) || (*pfVar13 <= fVar1)) {
            if (((pfVar11[2] != fVar2) && (fVar1 != *pfVar13)) &&
               ((fVar2 < pfVar11[2] || (fVar1 < *pfVar13)))) {
              fVar3 = (fVar2 - pfVar11[2]) / (*pfVar13 - pfVar11[2]);
              iVar7 = iVar7 + 1;
              iVar8 = iVar8 + 0xc;
              *(float *)((uVar12 - 0xc) + iVar8) = (pfVar13[-2] - *pfVar11) * fVar3 + *pfVar11;
              *(float *)((UINT_007f46ac - 8) + iVar8) =
                   (pfVar13[-1] - pfVar11[1]) * fVar3 + pfVar11[1];
              *(float *)((UINT_007f46ac - 4) + iVar8) = fVar2;
              UINT_007f4ac4 = UINT_007f4ac4 | 4;
              uVar12 = UINT_007f46ac;
            }
            if (*pfVar13 <= fVar1) {
              pfVar11 = (float *)(uVar12 + iVar8);
              iVar7 = iVar7 + 1;
              iVar8 = iVar8 + 0xc;
              *pfVar11 = pfVar13[-2];
              pfVar11[1] = pfVar13[-1];
              pfVar11[2] = *pfVar13;
              uVar12 = UINT_007f46ac;
            }
          }
          pfVar11 = pfVar13 + -2;
          pfVar13 = pfVar13 + 3;
          param_3 = param_3 + -1;
          uVar5 = UINT_007f47b8;
        } while (param_3 != 0);
      }
      UINT_007f47b8 = uVar5;
      iVar9 = iVar7;
      if (2 < iVar9) {
        iVar7 = 0;
        pfVar11 = (float *)((uVar12 - 0xc) + iVar9 * 0xc);
        uVar5 = UINT_007f47b8;
        UINT_007f46ac = UINT_007f47b8;
        if (0 < iVar9) {
          pfVar13 = (float *)(uVar12 + 8);
          iVar8 = 0;
          UINT_007f47b8 = uVar12;
          param_3 = iVar9;
          do {
            fVar2 = (float)param_1[6];
            fVar1 = (float)param_1[6];
            if ((fVar2 <= pfVar11[2]) || (fVar1 <= *pfVar13)) {
              if (((pfVar11[2] != fVar2) && (fVar1 != *pfVar13)) &&
                 ((pfVar11[2] < fVar2 || (*pfVar13 < fVar1)))) {
                fVar3 = (fVar2 - pfVar11[2]) / (*pfVar13 - pfVar11[2]);
                iVar7 = iVar7 + 1;
                iVar8 = iVar8 + 0xc;
                *(float *)((uVar5 - 0xc) + iVar8) = (pfVar13[-2] - *pfVar11) * fVar3 + *pfVar11;
                *(float *)((UINT_007f46ac - 8) + iVar8) =
                     (pfVar13[-1] - pfVar11[1]) * fVar3 + pfVar11[1];
                *(float *)((UINT_007f46ac - 4) + iVar8) = fVar2;
                UINT_007f4ac4 = UINT_007f4ac4 | 8;
                uVar5 = UINT_007f46ac;
              }
              if (fVar1 <= *pfVar13) {
                pfVar11 = (float *)(uVar5 + iVar8);
                iVar7 = iVar7 + 1;
                iVar8 = iVar8 + 0xc;
                *pfVar11 = pfVar13[-2];
                pfVar11[1] = pfVar13[-1];
                pfVar11[2] = *pfVar13;
                uVar5 = UINT_007f46ac;
              }
            }
            pfVar11 = pfVar13 + -2;
            pfVar13 = pfVar13 + 3;
            param_3 = param_3 + -1;
            uVar12 = UINT_007f47b8;
          } while (param_3 != 0);
        }
        UINT_007f47b8 = uVar12;
        iVar9 = iVar7;
        if (2 < iVar9) {
          iVar7 = 0;
          pfVar11 = (float *)((uVar5 - 0xc) + iVar9 * 0xc);
          pfVar13 = (float *)UINT_007f47b8;
          UINT_007f46ac = UINT_007f47b8;
          if (0 < iVar9) {
            pfVar4 = (float *)(uVar5 + 4);
            iVar8 = 0;
            UINT_007f47b8 = uVar5;
            param_3 = iVar9;
            do {
              if (((float)param_1[1] <= pfVar11[1]) || ((float)param_1[1] <= *pfVar4)) {
                if (((pfVar11[1] != (float)param_1[1]) && (*pfVar4 != (float)param_1[1])) &&
                   ((pfVar11[1] < (float)param_1[1] || (*pfVar4 < (float)param_1[1])))) {
                  iVar7 = iVar7 + 1;
                  fVar1 = ((float)param_1[1] - pfVar11[1]) / (*pfVar4 - pfVar11[1]);
                  *(int *)((int)pfVar13 + iVar8 + 4) = param_1[1];
                  iVar8 = iVar8 + 0xc;
                  *(float *)((UINT_007f46ac - 4) + iVar8) =
                       (pfVar4[1] - pfVar11[2]) * fVar1 + pfVar11[2];
                  *(float *)((UINT_007f46ac - 0xc) + iVar8) =
                       (pfVar4[-1] - *pfVar11) * fVar1 + *pfVar11;
                  UINT_007f4ac4 = UINT_007f4ac4 | 1;
                  pfVar13 = (float *)UINT_007f46ac;
                }
                if ((float)param_1[1] <= *pfVar4) {
                  pfVar13 = (float *)((int)pfVar13 + iVar8);
                  iVar7 = iVar7 + 1;
                  iVar8 = iVar8 + 0xc;
                  *pfVar13 = pfVar4[-1];
                  pfVar13[1] = *pfVar4;
                  pfVar13[2] = pfVar4[1];
                  pfVar13 = (float *)UINT_007f46ac;
                }
              }
              pfVar11 = pfVar4 + -1;
              pfVar4 = pfVar4 + 3;
              param_3 = param_3 + -1;
              uVar5 = UINT_007f47b8;
            } while (param_3 != 0);
          }
          UINT_007f47b8 = uVar5;
          if (iVar7 < 3) {
            UINT_007f4ac4 = UINT_007f4ac4 | 0x40;
            return iVar7;
          }
          iVar9 = iVar7;
          pfVar11 = pfVar13;
          if (*param_1 != 0) {
            iVar9 = 0;
            pfVar4 = pfVar13 + iVar7 * 3 + -3;
            pfVar11 = (float *)UINT_007f47b8;
            UINT_007f46ac = UINT_007f47b8;
            if (0 < iVar7) {
              pfVar6 = pfVar13 + 1;
              iVar8 = 0;
              UINT_007f47b8 = (uint)pfVar13;
              param_3 = iVar7;
              do {
                if ((pfVar4[1] <= (float)param_1[2]) || (*pfVar6 <= (float)param_1[2])) {
                  if (((pfVar4[1] != (float)param_1[2]) && (*pfVar6 != (float)param_1[2])) &&
                     (((float)param_1[2] < pfVar4[1] || ((float)param_1[2] < *pfVar6)))) {
                    iVar9 = iVar9 + 1;
                    fVar1 = ((float)param_1[2] - pfVar4[1]) / (*pfVar6 - pfVar4[1]);
                    *(int *)((int)pfVar11 + iVar8 + 4) = param_1[2];
                    iVar8 = iVar8 + 0xc;
                    *(float *)((UINT_007f46ac - 4) + iVar8) =
                         (pfVar6[1] - pfVar4[2]) * fVar1 + pfVar4[2];
                    *(float *)((UINT_007f46ac - 0xc) + iVar8) =
                         (pfVar6[-1] - *pfVar4) * fVar1 + *pfVar4;
                    UINT_007f4ac4 = UINT_007f4ac4 | 2;
                    pfVar11 = (float *)UINT_007f46ac;
                  }
                  if (*pfVar6 <= (float)param_1[2]) {
                    pfVar11 = (float *)((int)pfVar11 + iVar8);
                    iVar9 = iVar9 + 1;
                    iVar8 = iVar8 + 0xc;
                    *pfVar11 = pfVar6[-1];
                    pfVar11[1] = *pfVar6;
                    pfVar11[2] = pfVar6[1];
                    pfVar11 = (float *)UINT_007f46ac;
                  }
                }
                pfVar4 = pfVar6 + -1;
                pfVar6 = pfVar6 + 3;
                param_3 = param_3 + -1;
                pfVar13 = (float *)UINT_007f47b8;
              } while (param_3 != 0);
            }
            UINT_007f47b8 = (uint)pfVar13;
            if (iVar9 < 3) {
              return iVar9;
            }
          }
          if (pfVar11 != param_2) {
            for (uVar5 = iVar9 * 3 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
              *param_2 = *pfVar11;
              pfVar11 = pfVar11 + 1;
              param_2 = param_2 + 1;
            }
            for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
              *(undefined1 *)param_2 = *(undefined1 *)pfVar11;
              pfVar11 = (float *)((int)pfVar11 + 1);
              param_2 = (float *)((int)param_2 + 1);
            }
          }
        }
      }
    }
  }
  return iVar9;
}

/* ---- 0x004489b0  rdClip_Face3_Pos_2 ---- */
uint rdClip_Face3_Pos_2(int *param_1,float *param_2,uint param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint *puVar14;
  float *pfVar15;
  uint uVar16;
  uint uVar17;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar12 = 0;
  puVar14 = &UINT_007f48c0;
  UINT_007f4ac4 = 0;
  UINT_007f47b8 = (uint)param_2;
  UINT_007f46ac = (uint)&UINT_007f48c0;
  if (0 < (int)param_3) {
    iVar11 = 0;
    local_4 = param_3;
    pfVar15 = param_2 + param_3 * 3 + -3;
    pfVar8 = param_2;
    do {
      fVar2 = pfVar15[1] * (float)param_1[0xc];
      fVar3 = pfVar8[1] * (float)param_1[0xc];
      if ((fVar2 <= *pfVar15) || (fVar3 <= *pfVar8)) {
        if (((*pfVar15 != fVar2) && (fVar3 != *pfVar8)) && ((*pfVar15 < fVar2 || (*pfVar8 < fVar3)))
           ) {
          fVar2 = pfVar8[1] - pfVar15[1];
          fVar4 = *pfVar8 - *pfVar15;
          fVar1 = (float)param_1[0xc] * fVar2 - fVar4;
          fVar5 = pfVar8[1] * *pfVar15 - pfVar15[1] * *pfVar8;
          if (fVar1 != 0.0) {
            fVar5 = fVar5 / fVar1;
          }
          fVar1 = fVar2;
          if (fVar2 < 0.0) {
            fVar1 = -fVar2;
          }
          fVar6 = fVar4;
          if (fVar4 < 0.0) {
            fVar6 = -fVar4;
          }
          if (fVar1 <= fVar6) {
            fVar2 = ((float)param_1[0xc] * fVar5 - *pfVar15) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar15[1]) / fVar2;
          }
          *(float *)((int)puVar14 + iVar11) = (float)param_1[0xc] * fVar5;
          uVar12 = uVar12 + 1;
          *(float *)(UINT_007f46ac + 4 + iVar11) = fVar5;
          iVar11 = iVar11 + 0xc;
          *(float *)((UINT_007f46ac - 4) + iVar11) = (pfVar8[2] - pfVar15[2]) * fVar2 + pfVar15[2];
          UINT_007f4ac4 = UINT_007f4ac4 | 0x10;
          puVar14 = (uint *)UINT_007f46ac;
        }
        if (fVar3 <= *pfVar8) {
          pfVar15 = (float *)((int)puVar14 + iVar11);
          uVar12 = uVar12 + 1;
          iVar11 = iVar11 + 0xc;
          *pfVar15 = *pfVar8;
          pfVar15[1] = pfVar8[1];
          pfVar15[2] = pfVar8[2];
          puVar14 = (uint *)UINT_007f46ac;
        }
      }
      local_4 = local_4 - 1;
      pfVar15 = pfVar8;
      pfVar8 = pfVar8 + 3;
    } while (local_4 != 0);
  }
  if (2 < (int)uVar12) {
    uVar13 = 0;
    uVar17 = UINT_007f47b8;
    UINT_007f46ac = UINT_007f47b8;
    pfVar15 = (float *)puVar14;
    if (0 < (int)uVar12) {
      iVar11 = 0;
      pfVar8 = (float *)(puVar14 + uVar12 * 3 + -3);
      UINT_007f47b8 = (uint)puVar14;
      local_4 = uVar12;
      do {
        fVar2 = (float)param_1[10] * pfVar8[1];
        fVar3 = (float)param_1[10] * (float)puVar14[1];
        if ((*pfVar8 <= fVar2) || ((float)*puVar14 <= fVar3)) {
          if (((*pfVar8 != fVar2) && (fVar3 != (float)*puVar14)) &&
             ((fVar2 < *pfVar8 || (fVar3 < (float)*puVar14)))) {
            fVar2 = (float)puVar14[1] - pfVar8[1];
            fVar4 = (float)*puVar14 - *pfVar8;
            fVar1 = (float)param_1[10] * fVar2 - fVar4;
            fVar5 = (float)puVar14[1] * *pfVar8 - pfVar8[1] * (float)*puVar14;
            if (fVar1 != 0.0) {
              fVar5 = fVar5 / fVar1;
            }
            fVar1 = fVar2;
            if (fVar2 < 0.0) {
              fVar1 = -fVar2;
            }
            fVar6 = fVar4;
            if (fVar4 < 0.0) {
              fVar6 = -fVar4;
            }
            if (fVar1 <= fVar6) {
              fVar2 = ((float)param_1[10] * fVar5 - *pfVar8) / fVar4;
            }
            else {
              fVar2 = (fVar5 - pfVar8[1]) / fVar2;
            }
            *(float *)(uVar17 + iVar11) = (float)param_1[10] * fVar5;
            uVar13 = uVar13 + 1;
            *(float *)(UINT_007f46ac + 4 + iVar11) = fVar5;
            iVar11 = iVar11 + 0xc;
            *(float *)((UINT_007f46ac - 4) + iVar11) =
                 ((float)puVar14[2] - pfVar8[2]) * fVar2 + pfVar8[2];
            UINT_007f4ac4 = UINT_007f4ac4 | 0x20;
            uVar17 = UINT_007f46ac;
          }
          if ((float)*puVar14 <= fVar3) {
            pfVar15 = (float *)(uVar17 + iVar11);
            uVar13 = uVar13 + 1;
            iVar11 = iVar11 + 0xc;
            *pfVar15 = (float)*puVar14;
            pfVar15[1] = (float)puVar14[1];
            pfVar15[2] = (float)puVar14[2];
            uVar17 = UINT_007f46ac;
          }
        }
        local_4 = local_4 - 1;
        pfVar8 = (float *)puVar14;
        puVar14 = puVar14 + 3;
        pfVar15 = (float *)UINT_007f47b8;
      } while (local_4 != 0);
    }
    UINT_007f47b8 = (uint)pfVar15;
    uVar12 = uVar13;
    if (2 < (int)uVar12) {
      uVar13 = 0;
      UINT_007f46ac = UINT_007f47b8;
      pfVar15 = (float *)((uVar17 - 0xc) + uVar12 * 0xc);
      uVar16 = UINT_007f47b8;
      if (0 < (int)uVar12) {
        iVar11 = 0;
        pfVar8 = (float *)(uVar17 + 8);
        UINT_007f47b8 = uVar17;
        local_4 = uVar12;
        do {
          fVar2 = (float)param_1[0xb] * pfVar15[1];
          fVar3 = pfVar8[-1] * (float)param_1[0xb];
          if ((pfVar15[2] <= fVar2) || (*pfVar8 <= fVar3)) {
            if (((pfVar15[2] != fVar2) && (fVar3 != *pfVar8)) &&
               ((fVar2 < pfVar15[2] || (fVar3 < *pfVar8)))) {
              fVar2 = pfVar8[-1] - pfVar15[1];
              fVar4 = *pfVar8 - pfVar15[2];
              fVar1 = (float)param_1[0xb] * fVar2 - fVar4;
              fVar5 = pfVar15[2] * pfVar8[-1] - pfVar15[1] * *pfVar8;
              if (fVar1 != 0.0) {
                fVar5 = fVar5 / fVar1;
              }
              fVar1 = (float)param_1[0xb];
              fVar6 = fVar2;
              if (fVar2 < 0.0) {
                fVar6 = -fVar2;
              }
              fVar7 = fVar4;
              if (fVar4 < 0.0) {
                fVar7 = -fVar4;
              }
              if (fVar6 <= fVar7) {
                fVar2 = (fVar1 * fVar5 - pfVar15[2]) / fVar4;
              }
              else {
                fVar2 = (fVar5 - pfVar15[1]) / fVar2;
              }
              uVar13 = uVar13 + 1;
              iVar11 = iVar11 + 0xc;
              *(float *)((uVar16 - 0xc) + iVar11) = (pfVar8[-2] - *pfVar15) * fVar2 + *pfVar15;
              *(float *)((UINT_007f46ac - 8) + iVar11) = fVar5;
              *(float *)((UINT_007f46ac - 4) + iVar11) = fVar1 * fVar5;
              UINT_007f4ac4 = UINT_007f4ac4 | 4;
              uVar16 = UINT_007f46ac;
            }
            if (*pfVar8 <= fVar3) {
              pfVar15 = (float *)(uVar16 + iVar11);
              uVar13 = uVar13 + 1;
              iVar11 = iVar11 + 0xc;
              *pfVar15 = pfVar8[-2];
              pfVar15[1] = pfVar8[-1];
              pfVar15[2] = *pfVar8;
              uVar16 = UINT_007f46ac;
            }
          }
          pfVar15 = pfVar8 + -2;
          pfVar8 = pfVar8 + 3;
          local_4 = local_4 - 1;
          uVar17 = UINT_007f47b8;
        } while (local_4 != 0);
      }
      UINT_007f47b8 = uVar17;
      uVar12 = uVar13;
      if (2 < (int)uVar12) {
        uVar13 = 0;
        UINT_007f46ac = UINT_007f47b8;
        pfVar15 = (float *)((uVar16 - 0xc) + uVar12 * 0xc);
        uVar17 = UINT_007f47b8;
        if (0 < (int)uVar12) {
          iVar11 = 0;
          pfVar8 = (float *)(uVar16 + 8);
          UINT_007f47b8 = uVar16;
          local_4 = uVar12;
          do {
            fVar2 = (float)param_1[8] * pfVar15[1];
            fVar3 = pfVar8[-1] * (float)param_1[8];
            if ((fVar2 <= pfVar15[2]) || (fVar3 <= *pfVar8)) {
              if (((pfVar15[2] != fVar2) && (fVar3 != *pfVar8)) &&
                 ((pfVar15[2] < fVar2 || (*pfVar8 < fVar3)))) {
                fVar2 = pfVar8[-1] - pfVar15[1];
                fVar4 = *pfVar8 - pfVar15[2];
                fVar1 = (float)param_1[8] * fVar2 - fVar4;
                fVar5 = pfVar15[2] * pfVar8[-1] - pfVar15[1] * *pfVar8;
                if (fVar1 != 0.0) {
                  fVar5 = fVar5 / fVar1;
                }
                fVar1 = (float)param_1[8];
                fVar6 = fVar2;
                if (fVar2 < 0.0) {
                  fVar6 = -fVar2;
                }
                fVar7 = fVar4;
                if (fVar4 < 0.0) {
                  fVar7 = -fVar4;
                }
                if (fVar6 <= fVar7) {
                  fVar2 = (fVar1 * fVar5 - pfVar15[2]) / fVar4;
                }
                else {
                  fVar2 = (fVar5 - pfVar15[1]) / fVar2;
                }
                uVar13 = uVar13 + 1;
                iVar11 = iVar11 + 0xc;
                *(float *)((uVar17 - 0xc) + iVar11) = (pfVar8[-2] - *pfVar15) * fVar2 + *pfVar15;
                *(float *)((UINT_007f46ac - 8) + iVar11) = fVar5;
                *(float *)((UINT_007f46ac - 4) + iVar11) = fVar1 * fVar5;
                UINT_007f4ac4 = UINT_007f4ac4 | 8;
                uVar17 = UINT_007f46ac;
              }
              if (fVar3 <= *pfVar8) {
                pfVar15 = (float *)(uVar17 + iVar11);
                uVar13 = uVar13 + 1;
                iVar11 = iVar11 + 0xc;
                *pfVar15 = pfVar8[-2];
                pfVar15[1] = pfVar8[-1];
                pfVar15[2] = *pfVar8;
                uVar17 = UINT_007f46ac;
              }
            }
            pfVar15 = pfVar8 + -2;
            pfVar8 = pfVar8 + 3;
            local_4 = local_4 - 1;
            uVar16 = UINT_007f47b8;
          } while (local_4 != 0);
        }
        UINT_007f47b8 = uVar16;
        uVar12 = uVar13;
        if (2 < (int)uVar12) {
          uVar13 = 0;
          UINT_007f46ac = UINT_007f47b8;
          pfVar15 = (float *)((uVar17 - 0xc) + uVar12 * 0xc);
          pfVar8 = (float *)UINT_007f47b8;
          if (0 < (int)uVar12) {
            iVar11 = 0;
            pfVar9 = (float *)(uVar17 + 4);
            UINT_007f47b8 = uVar17;
            param_3 = uVar12;
            do {
              if (((float)param_1[1] <= pfVar15[1]) || ((float)param_1[1] <= *pfVar9)) {
                if (((pfVar15[1] != (float)param_1[1]) && (*pfVar9 != (float)param_1[1])) &&
                   ((pfVar15[1] < (float)param_1[1] || (*pfVar9 < (float)param_1[1])))) {
                  uVar13 = uVar13 + 1;
                  fVar2 = ((float)param_1[1] - pfVar15[1]) / (*pfVar9 - pfVar15[1]);
                  *(int *)((int)pfVar8 + iVar11 + 4) = param_1[1];
                  iVar11 = iVar11 + 0xc;
                  *(float *)((UINT_007f46ac - 4) + iVar11) =
                       (pfVar9[1] - pfVar15[2]) * fVar2 + pfVar15[2];
                  *(float *)((UINT_007f46ac - 0xc) + iVar11) =
                       (pfVar9[-1] - *pfVar15) * fVar2 + *pfVar15;
                  UINT_007f4ac4 = UINT_007f4ac4 | 1;
                  pfVar8 = (float *)UINT_007f46ac;
                }
                if ((float)param_1[1] <= *pfVar9) {
                  pfVar8 = (float *)((int)pfVar8 + iVar11);
                  uVar13 = uVar13 + 1;
                  iVar11 = iVar11 + 0xc;
                  *pfVar8 = pfVar9[-1];
                  pfVar8[1] = *pfVar9;
                  pfVar8[2] = pfVar9[1];
                  pfVar8 = (float *)UINT_007f46ac;
                }
              }
              pfVar15 = pfVar9 + -1;
              pfVar9 = pfVar9 + 3;
              param_3 = param_3 - 1;
              uVar17 = UINT_007f47b8;
            } while (param_3 != 0);
          }
          UINT_007f47b8 = uVar17;
          if ((int)uVar13 < 3) {
            UINT_007f4ac4 = UINT_007f4ac4 | 0x40;
            return uVar13;
          }
          uVar12 = uVar13;
          pfVar15 = pfVar8;
          if (*param_1 != 0) {
            uVar12 = 0;
            pfVar9 = pfVar8 + uVar13 * 3 + -3;
            pfVar15 = (float *)UINT_007f47b8;
            UINT_007f46ac = UINT_007f47b8;
            if (0 < (int)uVar13) {
              iVar11 = 0;
              pfVar10 = pfVar8 + 1;
              UINT_007f47b8 = (uint)pfVar8;
              param_3 = uVar13;
              do {
                if ((pfVar9[1] <= (float)param_1[2]) || (*pfVar10 <= (float)param_1[2])) {
                  if (((pfVar9[1] != (float)param_1[2]) && (*pfVar10 != (float)param_1[2])) &&
                     (((float)param_1[2] < pfVar9[1] || ((float)param_1[2] < *pfVar10)))) {
                    uVar12 = uVar12 + 1;
                    fVar2 = ((float)param_1[2] - pfVar9[1]) / (*pfVar10 - pfVar9[1]);
                    *(int *)((int)pfVar15 + iVar11 + 4) = param_1[2];
                    iVar11 = iVar11 + 0xc;
                    *(float *)((UINT_007f46ac - 4) + iVar11) =
                         (pfVar10[1] - pfVar9[2]) * fVar2 + pfVar9[2];
                    *(float *)((UINT_007f46ac - 0xc) + iVar11) =
                         (pfVar10[-1] - *pfVar9) * fVar2 + *pfVar9;
                    UINT_007f4ac4 = UINT_007f4ac4 | 2;
                    pfVar15 = (float *)UINT_007f46ac;
                  }
                  if (*pfVar10 <= (float)param_1[2]) {
                    pfVar15 = (float *)((int)pfVar15 + iVar11);
                    uVar12 = uVar12 + 1;
                    iVar11 = iVar11 + 0xc;
                    *pfVar15 = pfVar10[-1];
                    pfVar15[1] = *pfVar10;
                    pfVar15[2] = pfVar10[1];
                    pfVar15 = (float *)UINT_007f46ac;
                  }
                }
                pfVar9 = pfVar10 + -1;
                pfVar10 = pfVar10 + 3;
                param_3 = param_3 - 1;
                pfVar8 = (float *)UINT_007f47b8;
              } while (param_3 != 0);
            }
            UINT_007f47b8 = (uint)pfVar8;
            if ((int)uVar12 < 3) {
              return uVar12;
            }
          }
          if (pfVar15 != param_2) {
            for (uVar13 = uVar12 * 3 & 0x3fffffff; uVar13 != 0; uVar13 = uVar13 - 1) {
              *param_2 = *pfVar15;
              pfVar15 = pfVar15 + 1;
              param_2 = param_2 + 1;
            }
            for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
              *(undefined1 *)param_2 = *(undefined1 *)pfVar15;
              pfVar15 = (float *)((int)pfVar15 + 1);
              param_2 = (float *)((int)param_2 + 1);
            }
          }
        }
      }
    }
  }
  return uVar12;
}
#undef local_4
#undef local_8


/* ---- 0x00449350  rdClip_Face3_PosB_2 ---- */
int rdClip_Face3_PosB_2(int *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  uint uVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint *puVar10;
  float *pfVar11;
  uint uVar12;
  float *pfVar13;
  
  iVar7 = 0;
  puVar10 = &UINT_007f48c0;
  iVar9 = 0;
  UINT_007f4ac4 = 0;
  UINT_007f47b8 = (uint)param_2;
  UINT_007f46ac = (uint)&UINT_007f48c0;
  pfVar11 = param_2 + param_3 * 3 + -3;
  pfVar13 = param_2;
  if (0 < param_3) {
    do {
      fVar2 = (float)param_1[3];
      fVar1 = (float)param_1[3];
      if ((fVar2 <= *pfVar11) || (fVar1 <= *pfVar13)) {
        iVar8 = iVar7;
        if (((*pfVar11 != fVar2) && (fVar1 != *pfVar13)) &&
           ((*pfVar11 < fVar2 || (*pfVar13 < fVar1)))) {
          fVar3 = (fVar2 - *pfVar11) / (*pfVar13 - *pfVar11);
          iVar9 = iVar9 + 1;
          iVar8 = iVar7 + 0xc;
          *(float *)((int)puVar10 + iVar7) = fVar2;
          *(float *)((UINT_007f46ac - 8) + iVar8) = (pfVar13[1] - pfVar11[1]) * fVar3 + pfVar11[1];
          *(float *)((UINT_007f46ac - 4) + iVar8) = (pfVar13[2] - pfVar11[2]) * fVar3 + pfVar11[2];
          UINT_007f4ac4 = UINT_007f4ac4 | 0x10;
          puVar10 = (uint *)UINT_007f46ac;
        }
        iVar7 = iVar8;
        if (fVar1 <= *pfVar13) {
          pfVar11 = (float *)((int)puVar10 + iVar8);
          iVar9 = iVar9 + 1;
          iVar7 = iVar8 + 0xc;
          *pfVar11 = *pfVar13;
          pfVar11[1] = pfVar13[1];
          pfVar11[2] = pfVar13[2];
          puVar10 = (uint *)UINT_007f46ac;
        }
      }
      param_3 = param_3 + -1;
      pfVar11 = pfVar13;
      pfVar13 = pfVar13 + 3;
    } while (param_3 != 0);
  }
  if (2 < iVar9) {
    iVar7 = 0;
    uVar5 = UINT_007f47b8;
    UINT_007f46ac = UINT_007f47b8;
    pfVar11 = (float *)puVar10;
    if (0 < iVar9) {
      iVar8 = 0;
      pfVar13 = (float *)(puVar10 + iVar9 * 3 + -3);
      UINT_007f47b8 = (uint)puVar10;
      param_3 = iVar9;
      do {
        fVar2 = (float)param_1[5];
        fVar1 = (float)param_1[5];
        if ((*pfVar13 <= fVar2) || ((float)*puVar10 <= fVar1)) {
          if (((*pfVar13 != fVar2) && (fVar1 != (float)*puVar10)) &&
             ((fVar2 < *pfVar13 || (fVar1 < (float)*puVar10)))) {
            fVar3 = (fVar2 - *pfVar13) / ((float)*puVar10 - *pfVar13);
            iVar7 = iVar7 + 1;
            iVar8 = iVar8 + 0xc;
            *(float *)((uVar5 - 0xc) + iVar8) = fVar2;
            *(float *)((UINT_007f46ac - 8) + iVar8) =
                 ((float)puVar10[1] - pfVar13[1]) * fVar3 + pfVar13[1];
            *(float *)((UINT_007f46ac - 4) + iVar8) =
                 ((float)puVar10[2] - pfVar13[2]) * fVar3 + pfVar13[2];
            UINT_007f4ac4 = UINT_007f4ac4 | 0x20;
            uVar5 = UINT_007f46ac;
          }
          if ((float)*puVar10 <= fVar1) {
            pfVar11 = (float *)(uVar5 + iVar8);
            iVar7 = iVar7 + 1;
            iVar8 = iVar8 + 0xc;
            *pfVar11 = (float)*puVar10;
            pfVar11[1] = (float)puVar10[1];
            pfVar11[2] = (float)puVar10[2];
            uVar5 = UINT_007f46ac;
          }
        }
        param_3 = param_3 + -1;
        pfVar13 = (float *)puVar10;
        puVar10 = puVar10 + 3;
        pfVar11 = (float *)UINT_007f47b8;
      } while (param_3 != 0);
    }
    UINT_007f47b8 = (uint)pfVar11;
    iVar9 = iVar7;
    if (2 < iVar9) {
      iVar7 = 0;
      pfVar11 = (float *)((uVar5 - 0xc) + iVar9 * 0xc);
      uVar12 = UINT_007f47b8;
      UINT_007f46ac = UINT_007f47b8;
      if (0 < iVar9) {
        pfVar13 = (float *)(uVar5 + 8);
        iVar8 = 0;
        UINT_007f47b8 = uVar5;
        param_3 = iVar9;
        do {
          fVar2 = (float)param_1[4];
          fVar1 = (float)param_1[4];
          if ((pfVar11[2] <= fVar2) || (*pfVar13 <= fVar1)) {
            if (((pfVar11[2] != fVar2) && (fVar1 != *pfVar13)) &&
               ((fVar2 < pfVar11[2] || (fVar1 < *pfVar13)))) {
              fVar3 = (fVar2 - pfVar11[2]) / (*pfVar13 - pfVar11[2]);
              iVar7 = iVar7 + 1;
              iVar8 = iVar8 + 0xc;
              *(float *)((uVar12 - 0xc) + iVar8) = (pfVar13[-2] - *pfVar11) * fVar3 + *pfVar11;
              *(float *)((UINT_007f46ac - 8) + iVar8) =
                   (pfVar13[-1] - pfVar11[1]) * fVar3 + pfVar11[1];
              *(float *)((UINT_007f46ac - 4) + iVar8) = fVar2;
              UINT_007f4ac4 = UINT_007f4ac4 | 4;
              uVar12 = UINT_007f46ac;
            }
            if (*pfVar13 <= fVar1) {
              pfVar11 = (float *)(uVar12 + iVar8);
              iVar7 = iVar7 + 1;
              iVar8 = iVar8 + 0xc;
              *pfVar11 = pfVar13[-2];
              pfVar11[1] = pfVar13[-1];
              pfVar11[2] = *pfVar13;
              uVar12 = UINT_007f46ac;
            }
          }
          pfVar11 = pfVar13 + -2;
          pfVar13 = pfVar13 + 3;
          param_3 = param_3 + -1;
          uVar5 = UINT_007f47b8;
        } while (param_3 != 0);
      }
      UINT_007f47b8 = uVar5;
      iVar9 = iVar7;
      if (2 < iVar9) {
        iVar7 = 0;
        pfVar11 = (float *)((uVar12 - 0xc) + iVar9 * 0xc);
        uVar5 = UINT_007f47b8;
        UINT_007f46ac = UINT_007f47b8;
        if (0 < iVar9) {
          pfVar13 = (float *)(uVar12 + 8);
          iVar8 = 0;
          UINT_007f47b8 = uVar12;
          param_3 = iVar9;
          do {
            fVar2 = (float)param_1[6];
            fVar1 = (float)param_1[6];
            if ((fVar2 <= pfVar11[2]) || (fVar1 <= *pfVar13)) {
              if (((pfVar11[2] != fVar2) && (fVar1 != *pfVar13)) &&
                 ((pfVar11[2] < fVar2 || (*pfVar13 < fVar1)))) {
                fVar3 = (fVar2 - pfVar11[2]) / (*pfVar13 - pfVar11[2]);
                iVar7 = iVar7 + 1;
                iVar8 = iVar8 + 0xc;
                *(float *)((uVar5 - 0xc) + iVar8) = (pfVar13[-2] - *pfVar11) * fVar3 + *pfVar11;
                *(float *)((UINT_007f46ac - 8) + iVar8) =
                     (pfVar13[-1] - pfVar11[1]) * fVar3 + pfVar11[1];
                *(float *)((UINT_007f46ac - 4) + iVar8) = fVar2;
                UINT_007f4ac4 = UINT_007f4ac4 | 8;
                uVar5 = UINT_007f46ac;
              }
              if (fVar1 <= *pfVar13) {
                pfVar11 = (float *)(uVar5 + iVar8);
                iVar7 = iVar7 + 1;
                iVar8 = iVar8 + 0xc;
                *pfVar11 = pfVar13[-2];
                pfVar11[1] = pfVar13[-1];
                pfVar11[2] = *pfVar13;
                uVar5 = UINT_007f46ac;
              }
            }
            pfVar11 = pfVar13 + -2;
            pfVar13 = pfVar13 + 3;
            param_3 = param_3 + -1;
            uVar12 = UINT_007f47b8;
          } while (param_3 != 0);
        }
        UINT_007f47b8 = uVar12;
        iVar9 = iVar7;
        if (2 < iVar9) {
          iVar7 = 0;
          pfVar11 = (float *)((uVar5 - 0xc) + iVar9 * 0xc);
          pfVar13 = (float *)UINT_007f47b8;
          UINT_007f46ac = UINT_007f47b8;
          if (0 < iVar9) {
            pfVar4 = (float *)(uVar5 + 4);
            iVar8 = 0;
            UINT_007f47b8 = uVar5;
            param_3 = iVar9;
            do {
              if (((float)param_1[1] <= pfVar11[1]) || ((float)param_1[1] <= *pfVar4)) {
                if (((pfVar11[1] != (float)param_1[1]) && (*pfVar4 != (float)param_1[1])) &&
                   ((pfVar11[1] < (float)param_1[1] || (*pfVar4 < (float)param_1[1])))) {
                  iVar7 = iVar7 + 1;
                  fVar1 = ((float)param_1[1] - pfVar11[1]) / (*pfVar4 - pfVar11[1]);
                  *(int *)((int)pfVar13 + iVar8 + 4) = param_1[1];
                  iVar8 = iVar8 + 0xc;
                  *(float *)((UINT_007f46ac - 4) + iVar8) =
                       (pfVar4[1] - pfVar11[2]) * fVar1 + pfVar11[2];
                  *(float *)((UINT_007f46ac - 0xc) + iVar8) =
                       (pfVar4[-1] - *pfVar11) * fVar1 + *pfVar11;
                  UINT_007f4ac4 = UINT_007f4ac4 | 1;
                  pfVar13 = (float *)UINT_007f46ac;
                }
                if ((float)param_1[1] <= *pfVar4) {
                  pfVar13 = (float *)((int)pfVar13 + iVar8);
                  iVar7 = iVar7 + 1;
                  iVar8 = iVar8 + 0xc;
                  *pfVar13 = pfVar4[-1];
                  pfVar13[1] = *pfVar4;
                  pfVar13[2] = pfVar4[1];
                  pfVar13 = (float *)UINT_007f46ac;
                }
              }
              pfVar11 = pfVar4 + -1;
              pfVar4 = pfVar4 + 3;
              param_3 = param_3 + -1;
              uVar5 = UINT_007f47b8;
            } while (param_3 != 0);
          }
          UINT_007f47b8 = uVar5;
          if (iVar7 < 3) {
            UINT_007f4ac4 = UINT_007f4ac4 | 0x40;
            return iVar7;
          }
          iVar9 = iVar7;
          pfVar11 = pfVar13;
          if (*param_1 != 0) {
            iVar9 = 0;
            pfVar4 = pfVar13 + iVar7 * 3 + -3;
            pfVar11 = (float *)UINT_007f47b8;
            UINT_007f46ac = UINT_007f47b8;
            if (0 < iVar7) {
              pfVar6 = pfVar13 + 1;
              iVar8 = 0;
              UINT_007f47b8 = (uint)pfVar13;
              param_3 = iVar7;
              do {
                if ((pfVar4[1] <= (float)param_1[2]) || (*pfVar6 <= (float)param_1[2])) {
                  if (((pfVar4[1] != (float)param_1[2]) && (*pfVar6 != (float)param_1[2])) &&
                     (((float)param_1[2] < pfVar4[1] || ((float)param_1[2] < *pfVar6)))) {
                    iVar9 = iVar9 + 1;
                    fVar1 = ((float)param_1[2] - pfVar4[1]) / (*pfVar6 - pfVar4[1]);
                    *(int *)((int)pfVar11 + iVar8 + 4) = param_1[2];
                    iVar8 = iVar8 + 0xc;
                    *(float *)((UINT_007f46ac - 4) + iVar8) =
                         (pfVar6[1] - pfVar4[2]) * fVar1 + pfVar4[2];
                    *(float *)((UINT_007f46ac - 0xc) + iVar8) =
                         (pfVar6[-1] - *pfVar4) * fVar1 + *pfVar4;
                    UINT_007f4ac4 = UINT_007f4ac4 | 2;
                    pfVar11 = (float *)UINT_007f46ac;
                  }
                  if (*pfVar6 <= (float)param_1[2]) {
                    pfVar11 = (float *)((int)pfVar11 + iVar8);
                    iVar9 = iVar9 + 1;
                    iVar8 = iVar8 + 0xc;
                    *pfVar11 = pfVar6[-1];
                    pfVar11[1] = *pfVar6;
                    pfVar11[2] = pfVar6[1];
                    pfVar11 = (float *)UINT_007f46ac;
                  }
                }
                pfVar4 = pfVar6 + -1;
                pfVar6 = pfVar6 + 3;
                param_3 = param_3 + -1;
                pfVar13 = (float *)UINT_007f47b8;
              } while (param_3 != 0);
            }
            UINT_007f47b8 = (uint)pfVar13;
            if (iVar9 < 3) {
              return iVar9;
            }
          }
          if (pfVar11 != param_2) {
            for (uVar5 = iVar9 * 3 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
              *param_2 = *pfVar11;
              pfVar11 = pfVar11 + 1;
              param_2 = param_2 + 1;
            }
            for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
              *(undefined1 *)param_2 = *(undefined1 *)pfVar11;
              pfVar11 = (float *)((int)pfVar11 + 1);
              param_2 = (float *)((int)param_2 + 1);
            }
          }
        }
      }
    }
  }
  return iVar9;
}

/* ---- 0x00449aa0  rdClip_Face3_PosUvLit ---- */
/* Face clipper interpolating position, texture coordinate and intensity */

uint rdClip_Face3_PosUvLit(int *param_1,float *param_2,float *param_3,float *param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  float *pfVar14;
  uint *puVar15;
  float *pfVar16;
  float *pfVar17;
  uint uVar18;
  float *pfVar19;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar11 = 0;
  puVar15 = &UINT_007f48c0;
  UINT_007f4ac4 = 0;
  UINT_007f47b8 = (uint)param_2;
  UINT_007f4618 = (uint)param_3;
  UINT_007f46ac = (uint)&UINT_007f48c0;
  UINT_007f46b0 = (uint)&UINT_007f47c0;
  if (0 < (int)param_4) {
    iVar8 = 0;
    local_4 = (uint)param_4;
    pfVar16 = param_2;
    pfVar17 = param_3;
    pfVar19 = param_2 + (int)param_4 * 3 + -3;
    local_10 = (uint)(param_3 + ((int)param_4 - 1));
    do {
      pfVar14 = pfVar17;
      pfVar10 = pfVar16;
      fVar2 = pfVar19[1] * (float)param_1[0xc];
      fVar3 = (float)param_1[0xc] * pfVar10[1];
      if ((fVar2 <= *pfVar19) || (fVar3 <= *pfVar10)) {
        if (((*pfVar19 != fVar2) && (fVar3 != *pfVar10)) &&
           ((*pfVar19 < fVar2 || (*pfVar10 < fVar3)))) {
          fVar2 = pfVar10[1] - pfVar19[1];
          fVar4 = *pfVar10 - *pfVar19;
          fVar1 = (float)param_1[0xc] * fVar2 - fVar4;
          fVar5 = pfVar10[1] * *pfVar19 - pfVar19[1] * *pfVar10;
          if (fVar1 != 0.0) {
            fVar5 = fVar5 / fVar1;
          }
          fVar1 = fVar2;
          if (fVar2 < 0.0) {
            fVar1 = -fVar2;
          }
          fVar6 = fVar4;
          if (fVar4 < 0.0) {
            fVar6 = -fVar4;
          }
          if (fVar1 <= fVar6) {
            fVar2 = ((float)param_1[0xc] * fVar5 - *pfVar19) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar19[1]) / fVar2;
          }
          *(float *)((int)puVar15 + iVar8) = (float)param_1[0xc] * fVar5;
          iVar8 = iVar8 + 0xc;
          *(float *)((UINT_007f46ac - 8) + iVar8) = fVar5;
          uVar11 = uVar11 + 1;
          *(float *)((UINT_007f46ac - 4) + iVar8) = (pfVar10[2] - pfVar19[2]) * fVar2 + pfVar19[2];
          *(float *)((UINT_007f46b0 - 4) + uVar11 * 4) =
               (*pfVar14 - *(float *)local_10) * fVar2 + *(float *)local_10;
          UINT_007f4ac4 = UINT_007f4ac4 | 0x10;
          puVar15 = (uint *)UINT_007f46ac;
        }
        if (fVar3 <= *pfVar10) {
          pfVar16 = (float *)((int)puVar15 + iVar8);
          uVar11 = uVar11 + 1;
          iVar8 = iVar8 + 0xc;
          *pfVar16 = *pfVar10;
          pfVar16[1] = pfVar10[1];
          pfVar16[2] = pfVar10[2];
          *(float *)((UINT_007f46b0 - 4) + uVar11 * 4) = *pfVar14;
          puVar15 = (uint *)UINT_007f46ac;
        }
      }
      local_4 = local_4 - 1;
      pfVar16 = pfVar10 + 3;
      pfVar17 = pfVar14 + 1;
      pfVar19 = pfVar10;
      local_10 = (uint)pfVar14;
    } while (local_4 != 0);
  }
  uVar13 = UINT_007f4618;
  if (2 < (int)uVar11) {
    UINT_007f4618 = UINT_007f46b0;
    iVar8 = UINT_007f46b0 - 4;
    uVar12 = 0;
    uVar18 = UINT_007f47b8;
    UINT_007f46ac = UINT_007f47b8;
    pfVar16 = (float *)puVar15;
    if (0 < (int)uVar11) {
      iVar9 = 0;
      pfVar17 = (float *)UINT_007f46b0;
      pfVar19 = (float *)(puVar15 + uVar11 * 3 + -3);
      UINT_007f46b0 = uVar13;
      UINT_007f47b8 = (uint)puVar15;
      local_10 = iVar8 + uVar11 * 4;
      local_4 = uVar11;
      do {
        pfVar10 = pfVar17;
        pfVar16 = (float *)puVar15;
        fVar2 = (float)param_1[10] * pfVar19[1];
        fVar3 = (float)param_1[10] * pfVar16[1];
        if ((*pfVar19 <= fVar2) || (*pfVar16 <= fVar3)) {
          if (((*pfVar19 != fVar2) && (fVar3 != *pfVar16)) &&
             ((fVar2 < *pfVar19 || (fVar3 < *pfVar16)))) {
            fVar2 = pfVar16[1] - pfVar19[1];
            fVar4 = *pfVar16 - *pfVar19;
            fVar1 = (float)param_1[10] * fVar2 - fVar4;
            fVar5 = pfVar16[1] * *pfVar19 - pfVar19[1] * *pfVar16;
            if (fVar1 != 0.0) {
              fVar5 = fVar5 / fVar1;
            }
            fVar1 = fVar2;
            if (fVar2 < 0.0) {
              fVar1 = -fVar2;
            }
            fVar6 = fVar4;
            if (fVar4 < 0.0) {
              fVar6 = -fVar4;
            }
            if (fVar1 <= fVar6) {
              fVar2 = ((float)param_1[10] * fVar5 - *pfVar19) / fVar4;
            }
            else {
              fVar2 = (fVar5 - pfVar19[1]) / fVar2;
            }
            *(float *)(uVar18 + iVar9) = (float)param_1[10] * fVar5;
            iVar9 = iVar9 + 0xc;
            *(float *)((UINT_007f46ac - 8) + iVar9) = fVar5;
            uVar12 = uVar12 + 1;
            *(float *)((UINT_007f46ac - 4) + iVar9) = (pfVar16[2] - pfVar19[2]) * fVar2 + pfVar19[2]
            ;
            *(float *)((UINT_007f46b0 - 4) + uVar12 * 4) =
                 (*pfVar10 - *(float *)local_10) * fVar2 + *(float *)local_10;
            UINT_007f4ac4 = UINT_007f4ac4 | 0x20;
            uVar18 = UINT_007f46ac;
          }
          if (*pfVar16 <= fVar3) {
            pfVar17 = (float *)(uVar18 + iVar9);
            uVar12 = uVar12 + 1;
            iVar9 = iVar9 + 0xc;
            *pfVar17 = *pfVar16;
            pfVar17[1] = pfVar16[1];
            pfVar17[2] = pfVar16[2];
            *(float *)((UINT_007f46b0 - 4) + uVar12 * 4) = *pfVar10;
            uVar18 = UINT_007f46ac;
          }
        }
        local_4 = local_4 - 1;
        puVar15 = (uint *)(pfVar16 + 3);
        pfVar17 = pfVar10 + 1;
        pfVar19 = pfVar16;
        uVar13 = UINT_007f46b0;
        pfVar16 = (float *)UINT_007f47b8;
        local_10 = (uint)pfVar10;
      } while (local_4 != 0);
    }
    UINT_007f47b8 = (uint)pfVar16;
    UINT_007f46b0 = uVar13;
    uVar11 = uVar12;
    pfVar16 = (float *)UINT_007f46b0;
    if (2 < (int)uVar11) {
      UINT_007f46b0 = UINT_007f4618;
      uVar13 = 0;
      UINT_007f46ac = UINT_007f47b8;
      pfVar17 = (float *)((uVar18 - 0xc) + uVar11 * 0xc);
      UINT_007f4618 = (uint)pfVar16;
      uVar12 = UINT_007f47b8;
      if (0 < (int)uVar11) {
        iVar8 = 0;
        pfVar19 = (float *)(uVar18 + 8);
        UINT_007f47b8 = uVar18;
        local_10 = ((int)pfVar16 - 4U) + uVar11 * 4;
        local_4 = uVar11;
        do {
          pfVar10 = pfVar16;
          fVar2 = (float)param_1[0xb] * pfVar17[1];
          fVar3 = pfVar19[-1] * (float)param_1[0xb];
          if ((pfVar17[2] <= fVar2) || (*pfVar19 <= fVar3)) {
            if (((pfVar17[2] != fVar2) && (fVar3 != *pfVar19)) &&
               ((fVar2 < pfVar17[2] || (fVar3 < *pfVar19)))) {
              fVar2 = pfVar19[-1] - pfVar17[1];
              fVar4 = *pfVar19 - pfVar17[2];
              fVar1 = (float)param_1[0xb] * fVar2 - fVar4;
              fVar5 = pfVar17[2] * pfVar19[-1] - pfVar17[1] * *pfVar19;
              if (fVar1 != 0.0) {
                fVar5 = fVar5 / fVar1;
              }
              fVar1 = (float)param_1[0xb];
              fVar6 = fVar2;
              if (fVar2 < 0.0) {
                fVar6 = -fVar2;
              }
              fVar7 = fVar4;
              if (fVar4 < 0.0) {
                fVar7 = -fVar4;
              }
              if (fVar6 <= fVar7) {
                fVar2 = (fVar1 * fVar5 - pfVar17[2]) / fVar4;
              }
              else {
                fVar2 = (fVar5 - pfVar17[1]) / fVar2;
              }
              iVar8 = iVar8 + 0xc;
              uVar13 = uVar13 + 1;
              *(float *)((uVar12 - 0xc) + iVar8) = (pfVar19[-2] - *pfVar17) * fVar2 + *pfVar17;
              *(float *)((UINT_007f46ac - 8) + iVar8) = fVar5;
              *(float *)((UINT_007f46ac - 4) + iVar8) = fVar1 * fVar5;
              *(float *)((UINT_007f46b0 - 4) + uVar13 * 4) =
                   (*pfVar10 - *(float *)local_10) * fVar2 + *(float *)local_10;
              UINT_007f4ac4 = UINT_007f4ac4 | 4;
              uVar12 = UINT_007f46ac;
            }
            if (*pfVar19 <= fVar3) {
              pfVar16 = (float *)(uVar12 + iVar8);
              uVar13 = uVar13 + 1;
              iVar8 = iVar8 + 0xc;
              *pfVar16 = pfVar19[-2];
              pfVar16[1] = pfVar19[-1];
              pfVar16[2] = *pfVar19;
              *(float *)((UINT_007f46b0 - 4) + uVar13 * 4) = *pfVar10;
              uVar12 = UINT_007f46ac;
            }
          }
          pfVar17 = pfVar19 + -2;
          pfVar19 = pfVar19 + 3;
          local_4 = local_4 - 1;
          pfVar16 = pfVar10 + 1;
          uVar18 = UINT_007f47b8;
          local_10 = (uint)pfVar10;
        } while (local_4 != 0);
      }
      UINT_007f47b8 = uVar18;
      uVar11 = uVar13;
      pfVar16 = (float *)UINT_007f46b0;
      if (2 < (int)uVar11) {
        UINT_007f46b0 = UINT_007f4618;
        uVar13 = 0;
        UINT_007f46ac = UINT_007f47b8;
        pfVar17 = (float *)((uVar12 - 0xc) + uVar11 * 0xc);
        UINT_007f4618 = (uint)pfVar16;
        uVar18 = UINT_007f47b8;
        if (0 < (int)uVar11) {
          iVar8 = 0;
          pfVar19 = (float *)(uVar12 + 8);
          UINT_007f47b8 = uVar12;
          local_10 = ((int)pfVar16 - 4U) + uVar11 * 4;
          local_4 = uVar11;
          do {
            pfVar10 = pfVar16;
            fVar2 = (float)param_1[8] * pfVar17[1];
            fVar3 = pfVar19[-1] * (float)param_1[8];
            if ((fVar2 <= pfVar17[2]) || (fVar3 <= *pfVar19)) {
              if (((pfVar17[2] != fVar2) && (fVar3 != *pfVar19)) &&
                 ((pfVar17[2] < fVar2 || (*pfVar19 < fVar3)))) {
                fVar2 = pfVar19[-1] - pfVar17[1];
                fVar4 = *pfVar19 - pfVar17[2];
                fVar1 = (float)param_1[8] * fVar2 - fVar4;
                fVar5 = pfVar17[2] * pfVar19[-1] - pfVar17[1] * *pfVar19;
                if (fVar1 != 0.0) {
                  fVar5 = fVar5 / fVar1;
                }
                fVar1 = (float)param_1[8];
                fVar6 = fVar2;
                if (fVar2 < 0.0) {
                  fVar6 = -fVar2;
                }
                fVar7 = fVar4;
                if (fVar4 < 0.0) {
                  fVar7 = -fVar4;
                }
                if (fVar6 <= fVar7) {
                  fVar2 = (fVar1 * fVar5 - pfVar17[2]) / fVar4;
                }
                else {
                  fVar2 = (fVar5 - pfVar17[1]) / fVar2;
                }
                iVar8 = iVar8 + 0xc;
                uVar13 = uVar13 + 1;
                *(float *)((uVar18 - 0xc) + iVar8) = (pfVar19[-2] - *pfVar17) * fVar2 + *pfVar17;
                *(float *)((UINT_007f46ac - 8) + iVar8) = fVar5;
                *(float *)((UINT_007f46ac - 4) + iVar8) = fVar1 * fVar5;
                *(float *)((UINT_007f46b0 - 4) + uVar13 * 4) =
                     (*pfVar10 - *(float *)local_10) * fVar2 + *(float *)local_10;
                UINT_007f4ac4 = UINT_007f4ac4 | 8;
                uVar18 = UINT_007f46ac;
              }
              if (fVar3 <= *pfVar19) {
                pfVar16 = (float *)(uVar18 + iVar8);
                uVar13 = uVar13 + 1;
                iVar8 = iVar8 + 0xc;
                *pfVar16 = pfVar19[-2];
                pfVar16[1] = pfVar19[-1];
                pfVar16[2] = *pfVar19;
                *(float *)((UINT_007f46b0 - 4) + uVar13 * 4) = *pfVar10;
                uVar18 = UINT_007f46ac;
              }
            }
            pfVar17 = pfVar19 + -2;
            pfVar19 = pfVar19 + 3;
            local_4 = local_4 - 1;
            pfVar16 = pfVar10 + 1;
            uVar12 = UINT_007f47b8;
            local_10 = (uint)pfVar10;
          } while (local_4 != 0);
        }
        UINT_007f47b8 = uVar12;
        uVar11 = uVar13;
        param_4 = (float *)UINT_007f46b0;
        if (2 < (int)uVar11) {
          UINT_007f46b0 = UINT_007f4618;
          uVar13 = 0;
          local_10 = ((int)param_4 - 4U) + uVar11 * 4;
          UINT_007f46ac = UINT_007f47b8;
          UINT_007f4618 = (uint)param_4;
          pfVar16 = (float *)((uVar18 - 0xc) + uVar11 * 0xc);
          pfVar17 = (float *)UINT_007f47b8;
          if (0 < (int)uVar11) {
            iVar8 = 0;
            pfVar19 = (float *)(uVar18 + 4);
            UINT_007f47b8 = uVar18;
            local_4 = uVar11;
            do {
              if (((float)param_1[1] <= pfVar16[1]) || ((float)param_1[1] <= *pfVar19)) {
                if (((pfVar16[1] != (float)param_1[1]) && (*pfVar19 != (float)param_1[1])) &&
                   ((pfVar16[1] < (float)param_1[1] || (*pfVar19 < (float)param_1[1])))) {
                  fVar2 = ((float)param_1[1] - pfVar16[1]) / (*pfVar19 - pfVar16[1]);
                  *(int *)((int)pfVar17 + iVar8 + 4) = param_1[1];
                  iVar8 = iVar8 + 0xc;
                  uVar13 = uVar13 + 1;
                  *(float *)((UINT_007f46ac - 4) + iVar8) =
                       (pfVar19[1] - pfVar16[2]) * fVar2 + pfVar16[2];
                  *(float *)((UINT_007f46ac - 0xc) + iVar8) =
                       (pfVar19[-1] - *pfVar16) * fVar2 + *pfVar16;
                  *(float *)((UINT_007f46b0 - 4) + uVar13 * 4) =
                       (*param_4 - *(float *)local_10) * fVar2 + *(float *)local_10;
                  UINT_007f4ac4 = UINT_007f4ac4 | 1;
                  pfVar17 = (float *)UINT_007f46ac;
                }
                if ((float)param_1[1] <= *pfVar19) {
                  pfVar17 = (float *)((int)pfVar17 + iVar8);
                  uVar13 = uVar13 + 1;
                  iVar8 = iVar8 + 0xc;
                  *pfVar17 = pfVar19[-1];
                  pfVar17[1] = *pfVar19;
                  pfVar17[2] = pfVar19[1];
                  *(float *)((UINT_007f46b0 - 4) + uVar13 * 4) = *param_4;
                  pfVar17 = (float *)UINT_007f46ac;
                }
              }
              pfVar16 = pfVar19 + -1;
              local_10 = (uint)param_4;
              param_4 = param_4 + 1;
              pfVar19 = pfVar19 + 3;
              local_4 = local_4 - 1;
              uVar18 = UINT_007f47b8;
            } while (local_4 != 0);
          }
          UINT_007f47b8 = uVar18;
          param_4 = (float *)UINT_007f46b0;
          if ((int)uVar13 < 3) {
            UINT_007f4ac4 = UINT_007f4ac4 | 0x40;
            return uVar13;
          }
          uVar11 = uVar13;
          pfVar16 = pfVar17;
          if (*param_1 != 0) {
            UINT_007f46b0 = UINT_007f4618;
            uVar11 = 0;
            local_10 = ((int)param_4 - 4U) + uVar13 * 4;
            UINT_007f46ac = UINT_007f47b8;
            UINT_007f4618 = (uint)param_4;
            pfVar19 = pfVar17 + uVar13 * 3 + -3;
            pfVar16 = (float *)UINT_007f47b8;
            if (0 < (int)uVar13) {
              iVar8 = 0;
              pfVar10 = pfVar17 + 1;
              UINT_007f47b8 = (uint)pfVar17;
              local_4 = uVar13;
              do {
                if ((pfVar19[1] <= (float)param_1[2]) || (*pfVar10 <= (float)param_1[2])) {
                  if (((pfVar19[1] != (float)param_1[2]) && (*pfVar10 != (float)param_1[2])) &&
                     (((float)param_1[2] < pfVar19[1] || ((float)param_1[2] < *pfVar10)))) {
                    fVar2 = ((float)param_1[2] - pfVar19[1]) / (*pfVar10 - pfVar19[1]);
                    *(int *)((int)pfVar16 + iVar8 + 4) = param_1[2];
                    iVar8 = iVar8 + 0xc;
                    uVar11 = uVar11 + 1;
                    *(float *)((UINT_007f46ac - 4) + iVar8) =
                         (pfVar10[1] - pfVar19[2]) * fVar2 + pfVar19[2];
                    *(float *)((UINT_007f46ac - 0xc) + iVar8) =
                         (pfVar10[-1] - *pfVar19) * fVar2 + *pfVar19;
                    *(float *)((UINT_007f46b0 - 4) + uVar11 * 4) =
                         (*param_4 - *(float *)local_10) * fVar2 + *(float *)local_10;
                    UINT_007f4ac4 = UINT_007f4ac4 | 2;
                    pfVar16 = (float *)UINT_007f46ac;
                  }
                  if (*pfVar10 <= (float)param_1[2]) {
                    pfVar16 = (float *)((int)pfVar16 + iVar8);
                    uVar11 = uVar11 + 1;
                    iVar8 = iVar8 + 0xc;
                    *pfVar16 = pfVar10[-1];
                    pfVar16[1] = *pfVar10;
                    pfVar16[2] = pfVar10[1];
                    *(float *)((UINT_007f46b0 - 4) + uVar11 * 4) = *param_4;
                    pfVar16 = (float *)UINT_007f46ac;
                  }
                }
                pfVar19 = pfVar10 + -1;
                local_10 = (uint)param_4;
                param_4 = param_4 + 1;
                pfVar10 = pfVar10 + 3;
                local_4 = local_4 - 1;
                pfVar17 = (float *)UINT_007f47b8;
              } while (local_4 != 0);
            }
            UINT_007f47b8 = (uint)pfVar17;
            if ((int)uVar11 < 3) {
              return uVar11;
            }
          }
          if (pfVar16 != param_2) {
            for (uVar13 = uVar11 * 3 & 0x3fffffff; uVar13 != 0; uVar13 = uVar13 - 1) {
              *param_2 = *pfVar16;
              pfVar16 = pfVar16 + 1;
              param_2 = param_2 + 1;
            }
            for (iVar8 = 0; uVar13 = uVar11, pfVar17 = (float *)UINT_007f46b0, iVar8 != 0;
                iVar8 = iVar8 + -1) {
              *(undefined1 *)param_2 = *(undefined1 *)pfVar16;
              pfVar16 = (float *)((int)pfVar16 + 1);
              param_2 = (float *)((int)param_2 + 1);
            }
            for (; uVar13 != 0; uVar13 = uVar13 - 1) {
              *param_3 = *pfVar17;
              pfVar17 = pfVar17 + 1;
              param_3 = param_3 + 1;
            }
          }
        }
      }
    }
  }
  return uVar11;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0044a6d0  rdClip_Face3_PosUv ---- */
uint rdClip_Face3_PosUv(int *param_1,float *param_2,float *param_3,uint param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  uint uVar5;
  float *pfVar6;
  uint uVar7;
  uint *puVar8;
  float *pfVar9;
  uint uVar10;
  uint uVar11;
  float *pfVar12;
  int iVar13;
  int iVar14;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  puVar8 = &UINT_007f48c0;
  UINT_007f4ac4 = 0;
  UINT_007f47b8 = (uint)param_2;
  UINT_007f4618 = (uint)param_3;
  UINT_007f46ac = (uint)&UINT_007f48c0;
  UINT_007f46b0 = (uint)&UINT_007f47c0;
  if (0 < (int)param_4) {
    iVar13 = 0;
    pfVar9 = param_2 + param_4 * 3 + -3;
    pfVar12 = param_2;
    pfVar4 = param_3;
    local_8 = (uint)(param_3 + param_4 + -1);
    do {
      pfVar6 = pfVar4;
      fVar2 = (float)param_1[3];
      fVar1 = (float)param_1[3];
      if ((fVar2 <= *pfVar9) || (fVar1 <= *pfVar12)) {
        iVar14 = iVar13;
        if (((*pfVar9 != fVar2) && (fVar1 != *pfVar12)) && ((*pfVar9 < fVar2 || (*pfVar12 < fVar1)))
           ) {
          fVar3 = (fVar2 - *pfVar9) / (*pfVar12 - *pfVar9);
          iVar14 = iVar13 + 0xc;
          local_4 = local_4 + 1;
          *(float *)((int)puVar8 + iVar13) = fVar2;
          *(float *)((UINT_007f46ac - 8) + iVar14) = (pfVar12[1] - pfVar9[1]) * fVar3 + pfVar9[1];
          *(float *)((UINT_007f46ac - 4) + iVar14) = (pfVar12[2] - pfVar9[2]) * fVar3 + pfVar9[2];
          *(float *)((UINT_007f46b0 - 4) + local_4 * 4) =
               (*pfVar6 - *(float *)local_8) * fVar3 + *(float *)local_8;
          UINT_007f4ac4 = UINT_007f4ac4 | 0x10;
          puVar8 = (uint *)UINT_007f46ac;
        }
        iVar13 = iVar14;
        if (fVar1 <= *pfVar12) {
          pfVar9 = (float *)((int)puVar8 + iVar14);
          local_4 = local_4 + 1;
          iVar13 = iVar14 + 0xc;
          *pfVar9 = *pfVar12;
          pfVar9[1] = pfVar12[1];
          pfVar9[2] = pfVar12[2];
          *(float *)((UINT_007f46b0 - 4) + local_4 * 4) = *pfVar6;
          puVar8 = (uint *)UINT_007f46ac;
        }
      }
      param_4 = param_4 + -1;
      pfVar9 = pfVar12;
      pfVar12 = pfVar12 + 3;
      pfVar4 = pfVar6 + 1;
      local_8 = (uint)pfVar6;
    } while (param_4 != 0);
  }
  uVar5 = UINT_007f4618;
  if (2 < (int)local_4) {
    iVar13 = UINT_007f46b0 - 4;
    uVar7 = 0;
    UINT_007f4618 = UINT_007f46b0;
    uVar11 = UINT_007f47b8;
    UINT_007f46ac = UINT_007f47b8;
    pfVar9 = (float *)puVar8;
    if (0 < (int)local_4) {
      iVar14 = 0;
      pfVar12 = (float *)(puVar8 + local_4 * 3 + -3);
      pfVar4 = (float *)UINT_007f46b0;
      UINT_007f46b0 = uVar5;
      UINT_007f47b8 = (uint)puVar8;
      param_4 = local_4;
      local_8 = iVar13 + local_4 * 4;
      do {
        pfVar6 = pfVar4;
        fVar2 = (float)param_1[5];
        fVar1 = (float)param_1[5];
        if ((*pfVar12 <= fVar2) || ((float)*puVar8 <= fVar1)) {
          if (((*pfVar12 != fVar2) && (fVar1 != (float)*puVar8)) &&
             ((fVar2 < *pfVar12 || (fVar1 < (float)*puVar8)))) {
            fVar3 = (fVar2 - *pfVar12) / ((float)*puVar8 - *pfVar12);
            iVar14 = iVar14 + 0xc;
            uVar7 = uVar7 + 1;
            *(float *)((uVar11 - 0xc) + iVar14) = fVar2;
            *(float *)((UINT_007f46ac - 8) + iVar14) =
                 ((float)puVar8[1] - pfVar12[1]) * fVar3 + pfVar12[1];
            *(float *)((UINT_007f46ac - 4) + iVar14) =
                 ((float)puVar8[2] - pfVar12[2]) * fVar3 + pfVar12[2];
            *(float *)((UINT_007f46b0 - 4) + uVar7 * 4) =
                 (*pfVar6 - *(float *)local_8) * fVar3 + *(float *)local_8;
            UINT_007f4ac4 = UINT_007f4ac4 | 0x20;
            uVar11 = UINT_007f46ac;
          }
          if ((float)*puVar8 <= fVar1) {
            pfVar9 = (float *)(uVar11 + iVar14);
            uVar7 = uVar7 + 1;
            iVar14 = iVar14 + 0xc;
            *pfVar9 = (float)*puVar8;
            pfVar9[1] = (float)puVar8[1];
            pfVar9[2] = (float)puVar8[2];
            *(float *)((UINT_007f46b0 - 4) + uVar7 * 4) = *pfVar6;
            uVar11 = UINT_007f46ac;
          }
        }
        param_4 = param_4 - 1;
        pfVar12 = (float *)puVar8;
        puVar8 = puVar8 + 3;
        pfVar4 = pfVar6 + 1;
        uVar5 = UINT_007f46b0;
        pfVar9 = (float *)UINT_007f47b8;
        local_8 = (uint)pfVar6;
      } while (param_4 != 0);
    }
    UINT_007f47b8 = (uint)pfVar9;
    UINT_007f46b0 = uVar5;
    local_4 = uVar7;
    uVar5 = UINT_007f4618;
    if (2 < (int)local_4) {
      iVar13 = UINT_007f46b0 - 4;
      uVar7 = 0;
      UINT_007f4618 = UINT_007f46b0;
      pfVar9 = (float *)((uVar11 - 0xc) + local_4 * 0xc);
      uVar10 = UINT_007f47b8;
      UINT_007f46ac = UINT_007f47b8;
      if (0 < (int)local_4) {
        pfVar12 = (float *)(uVar11 + 8);
        iVar14 = 0;
        pfVar4 = (float *)UINT_007f46b0;
        UINT_007f46b0 = uVar5;
        UINT_007f47b8 = uVar11;
        local_8 = iVar13 + local_4 * 4;
        do {
          pfVar6 = pfVar4;
          fVar2 = (float)param_1[4];
          fVar1 = (float)param_1[4];
          if ((pfVar9[2] <= fVar2) || (*pfVar12 <= fVar1)) {
            if (((pfVar9[2] != fVar2) && (fVar1 != *pfVar12)) &&
               ((fVar2 < pfVar9[2] || (fVar1 < *pfVar12)))) {
              fVar3 = (fVar2 - pfVar9[2]) / (*pfVar12 - pfVar9[2]);
              iVar14 = iVar14 + 0xc;
              uVar7 = uVar7 + 1;
              *(float *)((uVar10 - 0xc) + iVar14) = (pfVar12[-2] - *pfVar9) * fVar3 + *pfVar9;
              *(float *)((UINT_007f46ac - 8) + iVar14) =
                   (pfVar12[-1] - pfVar9[1]) * fVar3 + pfVar9[1];
              *(float *)((UINT_007f46ac - 4) + iVar14) = fVar2;
              *(float *)((UINT_007f46b0 - 4) + uVar7 * 4) =
                   (*pfVar6 - *(float *)local_8) * fVar3 + *(float *)local_8;
              UINT_007f4ac4 = UINT_007f4ac4 | 4;
              uVar10 = UINT_007f46ac;
            }
            if (*pfVar12 <= fVar1) {
              pfVar9 = (float *)(uVar10 + iVar14);
              uVar7 = uVar7 + 1;
              iVar14 = iVar14 + 0xc;
              *pfVar9 = pfVar12[-2];
              pfVar9[1] = pfVar12[-1];
              pfVar9[2] = *pfVar12;
              *(float *)((UINT_007f46b0 - 4) + uVar7 * 4) = *pfVar6;
              uVar10 = UINT_007f46ac;
            }
          }
          pfVar9 = pfVar12 + -2;
          pfVar12 = pfVar12 + 3;
          local_4 = local_4 - 1;
          pfVar4 = pfVar6 + 1;
          uVar5 = UINT_007f46b0;
          uVar11 = UINT_007f47b8;
          local_8 = (uint)pfVar6;
        } while (local_4 != 0);
      }
      UINT_007f47b8 = uVar11;
      UINT_007f46b0 = uVar5;
      local_4 = uVar7;
      uVar5 = UINT_007f4618;
      if (2 < (int)local_4) {
        uVar7 = 0;
        local_8 = (UINT_007f46b0 - 4) + local_4 * 4;
        UINT_007f4618 = UINT_007f46b0;
        pfVar9 = (float *)((uVar10 - 0xc) + local_4 * 0xc);
        local_c = UINT_007f46b0;
        uVar11 = UINT_007f47b8;
        UINT_007f46ac = UINT_007f47b8;
        UINT_007f46b0 = uVar5;
        if (0 < (int)local_4) {
          iVar13 = 0;
          pfVar12 = (float *)(uVar10 + 8);
          UINT_007f47b8 = uVar10;
          do {
            fVar2 = (float)param_1[6];
            fVar1 = (float)param_1[6];
            if ((fVar2 <= pfVar9[2]) || (fVar1 <= *pfVar12)) {
              if (((pfVar9[2] != fVar2) && (fVar1 != *pfVar12)) &&
                 ((pfVar9[2] < fVar2 || (*pfVar12 < fVar1)))) {
                fVar3 = (fVar2 - pfVar9[2]) / (*pfVar12 - pfVar9[2]);
                iVar13 = iVar13 + 0xc;
                uVar7 = uVar7 + 1;
                *(float *)((uVar11 - 0xc) + iVar13) = (pfVar12[-2] - *pfVar9) * fVar3 + *pfVar9;
                *(float *)((UINT_007f46ac - 8) + iVar13) =
                     (pfVar12[-1] - pfVar9[1]) * fVar3 + pfVar9[1];
                *(float *)((UINT_007f46ac - 4) + iVar13) = fVar2;
                *(float *)((UINT_007f46b0 - 4) + uVar7 * 4) =
                     (*(float *)local_c - *(float *)local_8) * fVar3 + *(float *)local_8;
                UINT_007f4ac4 = UINT_007f4ac4 | 8;
                uVar11 = UINT_007f46ac;
              }
              if (fVar1 <= *pfVar12) {
                pfVar9 = (float *)(uVar11 + iVar13);
                uVar7 = uVar7 + 1;
                iVar13 = iVar13 + 0xc;
                *pfVar9 = pfVar12[-2];
                pfVar9[1] = pfVar12[-1];
                pfVar9[2] = *pfVar12;
                *(undefined4 *)((UINT_007f46b0 - 4) + uVar7 * 4) = *(undefined4 *)local_c;
                uVar11 = UINT_007f46ac;
              }
            }
            pfVar9 = pfVar12 + -2;
            local_8 = local_c;
            local_c = local_c + 4;
            pfVar12 = pfVar12 + 3;
            local_4 = local_4 - 1;
            uVar10 = UINT_007f47b8;
          } while (local_4 != 0);
        }
        UINT_007f47b8 = uVar10;
        local_4 = uVar7;
        uVar5 = UINT_007f4618;
        if (2 < (int)local_4) {
          local_8 = (UINT_007f46b0 - 4) + local_4 * 4;
          uVar7 = 0;
          UINT_007f4618 = UINT_007f46b0;
          pfVar9 = (float *)((uVar11 - 0xc) + local_4 * 0xc);
          local_c = UINT_007f46b0;
          pfVar12 = (float *)UINT_007f47b8;
          UINT_007f46ac = UINT_007f47b8;
          UINT_007f46b0 = uVar5;
          if (0 < (int)local_4) {
            pfVar4 = (float *)(uVar11 + 4);
            iVar13 = 0;
            UINT_007f47b8 = uVar11;
            param_4 = local_4;
            do {
              if (((float)param_1[1] <= pfVar9[1]) || ((float)param_1[1] <= *pfVar4)) {
                if (((pfVar9[1] != (float)param_1[1]) && (*pfVar4 != (float)param_1[1])) &&
                   ((pfVar9[1] < (float)param_1[1] || (*pfVar4 < (float)param_1[1])))) {
                  fVar1 = ((float)param_1[1] - pfVar9[1]) / (*pfVar4 - pfVar9[1]);
                  *(int *)((int)pfVar12 + iVar13 + 4) = param_1[1];
                  iVar13 = iVar13 + 0xc;
                  uVar7 = uVar7 + 1;
                  *(float *)((UINT_007f46ac - 4) + iVar13) =
                       (pfVar4[1] - pfVar9[2]) * fVar1 + pfVar9[2];
                  *(float *)((UINT_007f46ac - 0xc) + iVar13) =
                       (pfVar4[-1] - *pfVar9) * fVar1 + *pfVar9;
                  *(float *)((UINT_007f46b0 - 4) + uVar7 * 4) =
                       (*(float *)local_c - *(float *)local_8) * fVar1 + *(float *)local_8;
                  UINT_007f4ac4 = UINT_007f4ac4 | 1;
                  pfVar12 = (float *)UINT_007f46ac;
                }
                if ((float)param_1[1] <= *pfVar4) {
                  pfVar12 = (float *)((int)pfVar12 + iVar13);
                  uVar7 = uVar7 + 1;
                  iVar13 = iVar13 + 0xc;
                  *pfVar12 = pfVar4[-1];
                  pfVar12[1] = *pfVar4;
                  pfVar12[2] = pfVar4[1];
                  *(undefined4 *)((UINT_007f46b0 - 4) + uVar7 * 4) = *(undefined4 *)local_c;
                  pfVar12 = (float *)UINT_007f46ac;
                }
              }
              pfVar9 = pfVar4 + -1;
              local_8 = local_c;
              local_c = local_c + 4;
              pfVar4 = pfVar4 + 3;
              param_4 = param_4 - 1;
              uVar11 = UINT_007f47b8;
            } while (param_4 != 0);
          }
          UINT_007f47b8 = uVar11;
          uVar5 = UINT_007f4618;
          if ((int)uVar7 < 3) {
            UINT_007f4ac4 = UINT_007f4ac4 | 0x40;
            return uVar7;
          }
          local_4 = uVar7;
          pfVar9 = pfVar12;
          if (*param_1 != 0) {
            local_8 = (UINT_007f46b0 - 4) + uVar7 * 4;
            local_4 = 0;
            UINT_007f4618 = UINT_007f46b0;
            pfVar4 = pfVar12 + uVar7 * 3 + -3;
            local_c = UINT_007f46b0;
            pfVar9 = (float *)UINT_007f47b8;
            UINT_007f46ac = UINT_007f47b8;
            UINT_007f46b0 = uVar5;
            if (0 < (int)uVar7) {
              pfVar6 = pfVar12 + 1;
              iVar13 = 0;
              UINT_007f47b8 = (uint)pfVar12;
              param_4 = uVar7;
              do {
                if ((pfVar4[1] <= (float)param_1[2]) || (*pfVar6 <= (float)param_1[2])) {
                  if (((pfVar4[1] != (float)param_1[2]) && (*pfVar6 != (float)param_1[2])) &&
                     (((float)param_1[2] < pfVar4[1] || ((float)param_1[2] < *pfVar6)))) {
                    fVar1 = ((float)param_1[2] - pfVar4[1]) / (*pfVar6 - pfVar4[1]);
                    *(int *)((int)pfVar9 + iVar13 + 4) = param_1[2];
                    iVar13 = iVar13 + 0xc;
                    local_4 = local_4 + 1;
                    *(float *)((UINT_007f46ac - 4) + iVar13) =
                         (pfVar6[1] - pfVar4[2]) * fVar1 + pfVar4[2];
                    *(float *)((UINT_007f46ac - 0xc) + iVar13) =
                         (pfVar6[-1] - *pfVar4) * fVar1 + *pfVar4;
                    *(float *)((UINT_007f46b0 - 4) + local_4 * 4) =
                         (*(float *)local_c - *(float *)local_8) * fVar1 + *(float *)local_8;
                    UINT_007f4ac4 = UINT_007f4ac4 | 2;
                    pfVar9 = (float *)UINT_007f46ac;
                  }
                  if (*pfVar6 <= (float)param_1[2]) {
                    pfVar9 = (float *)((int)pfVar9 + iVar13);
                    local_4 = local_4 + 1;
                    iVar13 = iVar13 + 0xc;
                    *pfVar9 = pfVar6[-1];
                    pfVar9[1] = *pfVar6;
                    pfVar9[2] = pfVar6[1];
                    *(undefined4 *)((UINT_007f46b0 - 4) + local_4 * 4) = *(undefined4 *)local_c;
                    pfVar9 = (float *)UINT_007f46ac;
                  }
                }
                pfVar4 = pfVar6 + -1;
                local_8 = local_c;
                local_c = local_c + 4;
                pfVar6 = pfVar6 + 3;
                param_4 = param_4 - 1;
                pfVar12 = (float *)UINT_007f47b8;
              } while (param_4 != 0);
            }
            UINT_007f47b8 = (uint)pfVar12;
            if ((int)local_4 < 3) {
              return local_4;
            }
          }
          if (pfVar9 != param_2) {
            for (uVar5 = local_4 * 3 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
              *param_2 = *pfVar9;
              pfVar9 = pfVar9 + 1;
              param_2 = param_2 + 1;
            }
            for (iVar13 = 0; uVar5 = local_4, pfVar12 = (float *)UINT_007f46b0, iVar13 != 0;
                iVar13 = iVar13 + -1) {
              *(undefined1 *)param_2 = *(undefined1 *)pfVar9;
              pfVar9 = (float *)((int)pfVar9 + 1);
              param_2 = (float *)((int)param_2 + 1);
            }
            for (; uVar5 != 0; uVar5 = uVar5 - 1) {
              *param_3 = *pfVar12;
              pfVar12 = pfVar12 + 1;
              param_3 = param_3 + 1;
            }
          }
        }
      }
    }
  }
  return local_4;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0044b0a0  rdClip_Face3_PosUvLit_2 ---- */
uint rdClip_Face3_PosUvLit_2(int *param_1,float *param_2,float *param_3,float *param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  uint uVar11;
  uint uVar12;
  float *pfVar13;
  float *pfVar14;
  uint *puVar15;
  float *pfVar16;
  float *pfVar17;
  uint uVar18;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  UINT_007f4ac4 = 0;
  local_10 = 0;
  puVar15 = &UINT_007f48c0;
  UINT_007f47b8 = (uint)param_2;
  UINT_007f46ac = (uint)&UINT_007f48c0;
  UINT_007f461c = (uint)param_3;
  UINT_007f46a8 = (uint)&UINT_007f46b8;
  if (0 < (int)param_4) {
    iVar8 = 0;
    local_4 = (uint)param_4;
    pfVar16 = param_3 + (int)param_4 * 2 + -2;
    pfVar17 = param_3;
    pfVar10 = param_2 + (int)param_4 * 3 + -3;
    pfVar13 = param_2;
    do {
      fVar2 = pfVar10[1] * (float)param_1[0xc];
      fVar3 = (float)param_1[0xc] * pfVar13[1];
      if ((fVar2 <= *pfVar10) || (fVar3 <= *pfVar13)) {
        if (((*pfVar10 != fVar2) && (fVar3 != *pfVar13)) &&
           ((*pfVar10 < fVar2 || (*pfVar13 < fVar3)))) {
          fVar2 = pfVar13[1] - pfVar10[1];
          fVar4 = *pfVar13 - *pfVar10;
          fVar1 = (float)param_1[0xc] * fVar2 - fVar4;
          fVar5 = pfVar13[1] * *pfVar10 - pfVar10[1] * *pfVar13;
          if (fVar1 != 0.0) {
            fVar5 = fVar5 / fVar1;
          }
          fVar1 = fVar2;
          if (fVar2 < 0.0) {
            fVar1 = -fVar2;
          }
          fVar6 = fVar4;
          if (fVar4 < 0.0) {
            fVar6 = -fVar4;
          }
          if (fVar1 <= fVar6) {
            fVar2 = ((float)param_1[0xc] * fVar5 - *pfVar10) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar10[1]) / fVar2;
          }
          *(float *)((int)puVar15 + iVar8) = (float)param_1[0xc] * fVar5;
          *(float *)(UINT_007f46ac + 4 + iVar8) = fVar5;
          iVar9 = local_10 * 8;
          local_10 = local_10 + 1;
          iVar8 = iVar8 + 0xc;
          *(float *)((UINT_007f46ac - 4) + iVar8) = (pfVar13[2] - pfVar10[2]) * fVar2 + pfVar10[2];
          *(float *)(UINT_007f46a8 + iVar9) = (*pfVar17 - *pfVar16) * fVar2 + *pfVar16;
          *(float *)(UINT_007f46a8 + 4 + iVar9) = (pfVar17[1] - pfVar16[1]) * fVar2 + pfVar16[1];
          UINT_007f4ac4 = UINT_007f4ac4 | 0x10;
          puVar15 = (uint *)UINT_007f46ac;
        }
        if (fVar3 <= *pfVar13) {
          pfVar16 = (float *)((int)puVar15 + iVar8);
          *pfVar16 = *pfVar13;
          pfVar16[1] = pfVar13[1];
          pfVar16[2] = pfVar13[2];
          *(float *)(UINT_007f46a8 + local_10 * 8) = *pfVar17;
          *(float *)(UINT_007f46a8 + 4 + local_10 * 8) = pfVar17[1];
          local_10 = local_10 + 1;
          iVar8 = iVar8 + 0xc;
          puVar15 = (uint *)UINT_007f46ac;
        }
      }
      local_4 = local_4 - 1;
      pfVar16 = pfVar17;
      pfVar17 = pfVar17 + 2;
      pfVar10 = pfVar13;
      pfVar13 = pfVar13 + 3;
    } while (local_4 != 0);
  }
  local_4 = local_10;
  uVar11 = UINT_007f461c;
  if ((int)local_10 < 3) {
    return local_10;
  }
  UINT_007f461c = UINT_007f46a8;
  iVar8 = local_10 * 8;
  local_10 = 0;
  uVar18 = UINT_007f47b8;
  UINT_007f46ac = UINT_007f47b8;
  pfVar16 = (float *)puVar15;
  if (0 < (int)local_4) {
    iVar9 = 0;
    pfVar17 = (float *)((UINT_007f46a8 - 8) + iVar8);
    pfVar10 = (float *)UINT_007f46a8;
    pfVar13 = (float *)(puVar15 + local_4 * 3 + -3);
    UINT_007f46a8 = uVar11;
    UINT_007f47b8 = (uint)puVar15;
    do {
      pfVar16 = (float *)puVar15;
      fVar2 = (float)param_1[10] * pfVar13[1];
      fVar3 = (float)param_1[10] * pfVar16[1];
      if ((*pfVar13 <= fVar2) || (*pfVar16 <= fVar3)) {
        if (((*pfVar13 != fVar2) && (fVar3 != *pfVar16)) &&
           ((fVar2 < *pfVar13 || (fVar3 < *pfVar16)))) {
          fVar2 = pfVar16[1] - pfVar13[1];
          fVar4 = *pfVar16 - *pfVar13;
          fVar1 = (float)param_1[10] * fVar2 - fVar4;
          fVar5 = pfVar16[1] * *pfVar13 - pfVar13[1] * *pfVar16;
          if (fVar1 != 0.0) {
            fVar5 = fVar5 / fVar1;
          }
          fVar1 = fVar2;
          if (fVar2 < 0.0) {
            fVar1 = -fVar2;
          }
          fVar6 = fVar4;
          if (fVar4 < 0.0) {
            fVar6 = -fVar4;
          }
          if (fVar1 <= fVar6) {
            fVar2 = ((float)param_1[10] * fVar5 - *pfVar13) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar13[1]) / fVar2;
          }
          *(float *)(uVar18 + iVar9) = (float)param_1[10] * fVar5;
          *(float *)(UINT_007f46ac + 4 + iVar9) = fVar5;
          iVar8 = local_10 * 8;
          local_10 = local_10 + 1;
          iVar9 = iVar9 + 0xc;
          *(float *)((UINT_007f46ac - 4) + iVar9) = (pfVar16[2] - pfVar13[2]) * fVar2 + pfVar13[2];
          *(float *)(UINT_007f46a8 + iVar8) = (*pfVar10 - *pfVar17) * fVar2 + *pfVar17;
          *(float *)(UINT_007f46a8 + 4 + iVar8) = (pfVar10[1] - pfVar17[1]) * fVar2 + pfVar17[1];
          UINT_007f4ac4 = UINT_007f4ac4 | 0x20;
          uVar18 = UINT_007f46ac;
        }
        if (*pfVar16 <= fVar3) {
          pfVar17 = (float *)(uVar18 + iVar9);
          *pfVar17 = *pfVar16;
          pfVar17[1] = pfVar16[1];
          pfVar17[2] = pfVar16[2];
          *(float *)(UINT_007f46a8 + local_10 * 8) = *pfVar10;
          *(float *)(UINT_007f46a8 + 4 + local_10 * 8) = pfVar10[1];
          local_10 = local_10 + 1;
          iVar9 = iVar9 + 0xc;
          uVar18 = UINT_007f46ac;
        }
      }
      local_4 = local_4 - 1;
      pfVar17 = pfVar10;
      puVar15 = (uint *)(pfVar16 + 3);
      pfVar10 = pfVar10 + 2;
      pfVar13 = pfVar16;
      uVar11 = UINT_007f46a8;
      pfVar16 = (float *)UINT_007f47b8;
    } while (local_4 != 0);
  }
  UINT_007f47b8 = (uint)pfVar16;
  UINT_007f46a8 = uVar11;
  local_4 = local_10;
  pfVar16 = (float *)UINT_007f46a8;
  if ((int)local_10 < 3) {
    return local_10;
  }
  UINT_007f46a8 = UINT_007f461c;
  iVar8 = 0;
  UINT_007f46ac = UINT_007f47b8;
  pfVar17 = (float *)((uVar18 - 0xc) + local_10 * 0xc);
  UINT_007f461c = (uint)pfVar16;
  local_10 = 0;
  uVar11 = UINT_007f47b8;
  if (0 < (int)local_4) {
    pfVar13 = (float *)(uVar18 + 8);
    pfVar10 = (float *)(((int)pfVar16 - 8U) + local_4 * 8);
    UINT_007f47b8 = uVar18;
    do {
      fVar2 = (float)param_1[0xb] * pfVar17[1];
      fVar3 = pfVar13[-1] * (float)param_1[0xb];
      if ((pfVar17[2] <= fVar2) || (*pfVar13 <= fVar3)) {
        if (((pfVar17[2] != fVar2) && (fVar3 != *pfVar13)) &&
           ((fVar2 < pfVar17[2] || (fVar3 < *pfVar13)))) {
          fVar2 = pfVar13[-1] - pfVar17[1];
          fVar4 = *pfVar13 - pfVar17[2];
          fVar1 = (float)param_1[0xb] * fVar2 - fVar4;
          fVar5 = pfVar17[2] * pfVar13[-1] - pfVar17[1] * *pfVar13;
          if (fVar1 != 0.0) {
            fVar5 = fVar5 / fVar1;
          }
          fVar1 = (float)param_1[0xb];
          fVar6 = fVar2;
          if (fVar2 < 0.0) {
            fVar6 = -fVar2;
          }
          fVar7 = fVar4;
          if (fVar4 < 0.0) {
            fVar7 = -fVar4;
          }
          if (fVar6 <= fVar7) {
            fVar2 = (fVar1 * fVar5 - pfVar17[2]) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar17[1]) / fVar2;
          }
          iVar8 = iVar8 + 0xc;
          iVar9 = local_10 * 8;
          local_10 = local_10 + 1;
          *(float *)((uVar11 - 0xc) + iVar8) = (pfVar13[-2] - *pfVar17) * fVar2 + *pfVar17;
          *(float *)((UINT_007f46ac - 8) + iVar8) = fVar5;
          *(float *)((UINT_007f46ac - 4) + iVar8) = fVar1 * fVar5;
          *(float *)(UINT_007f46a8 + iVar9) = (*pfVar16 - *pfVar10) * fVar2 + *pfVar10;
          *(float *)(UINT_007f46a8 + 4 + iVar9) = (pfVar16[1] - pfVar10[1]) * fVar2 + pfVar10[1];
          UINT_007f4ac4 = UINT_007f4ac4 | 4;
          uVar11 = UINT_007f46ac;
        }
        if (*pfVar13 <= fVar3) {
          pfVar17 = (float *)(uVar11 + iVar8);
          *pfVar17 = pfVar13[-2];
          pfVar17[1] = pfVar13[-1];
          pfVar17[2] = *pfVar13;
          *(float *)(UINT_007f46a8 + local_10 * 8) = *pfVar16;
          *(float *)(UINT_007f46a8 + 4 + local_10 * 8) = pfVar16[1];
          local_10 = local_10 + 1;
          iVar8 = iVar8 + 0xc;
          uVar11 = UINT_007f46ac;
        }
      }
      pfVar17 = pfVar13 + -2;
      pfVar13 = pfVar13 + 3;
      local_4 = local_4 - 1;
      pfVar10 = pfVar16;
      pfVar16 = pfVar16 + 2;
      uVar18 = UINT_007f47b8;
    } while (local_4 != 0);
  }
  UINT_007f47b8 = uVar18;
  local_4 = local_10;
  pfVar16 = (float *)UINT_007f46a8;
  if ((int)local_10 < 3) {
    return local_10;
  }
  UINT_007f46a8 = UINT_007f461c;
  iVar8 = 0;
  UINT_007f46ac = UINT_007f47b8;
  pfVar17 = (float *)((uVar11 - 0xc) + local_10 * 0xc);
  UINT_007f461c = (uint)pfVar16;
  local_10 = 0;
  uVar18 = UINT_007f47b8;
  if (0 < (int)local_4) {
    pfVar13 = (float *)(uVar11 + 8);
    pfVar10 = (float *)(((int)pfVar16 - 8U) + local_4 * 8);
    UINT_007f47b8 = uVar11;
    do {
      fVar2 = (float)param_1[8] * pfVar17[1];
      fVar3 = pfVar13[-1] * (float)param_1[8];
      if ((fVar2 <= pfVar17[2]) || (fVar3 <= *pfVar13)) {
        if (((pfVar17[2] != fVar2) && (fVar3 != *pfVar13)) &&
           ((pfVar17[2] < fVar2 || (*pfVar13 < fVar3)))) {
          fVar2 = pfVar13[-1] - pfVar17[1];
          fVar4 = *pfVar13 - pfVar17[2];
          fVar1 = (float)param_1[8] * fVar2 - fVar4;
          fVar5 = pfVar17[2] * pfVar13[-1] - pfVar17[1] * *pfVar13;
          if (fVar1 != 0.0) {
            fVar5 = fVar5 / fVar1;
          }
          fVar1 = (float)param_1[8];
          fVar6 = fVar2;
          if (fVar2 < 0.0) {
            fVar6 = -fVar2;
          }
          fVar7 = fVar4;
          if (fVar4 < 0.0) {
            fVar7 = -fVar4;
          }
          if (fVar6 <= fVar7) {
            fVar2 = (fVar1 * fVar5 - pfVar17[2]) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar17[1]) / fVar2;
          }
          iVar8 = iVar8 + 0xc;
          iVar9 = local_10 * 8;
          local_10 = local_10 + 1;
          *(float *)((uVar18 - 0xc) + iVar8) = (pfVar13[-2] - *pfVar17) * fVar2 + *pfVar17;
          *(float *)((UINT_007f46ac - 8) + iVar8) = fVar5;
          *(float *)((UINT_007f46ac - 4) + iVar8) = fVar1 * fVar5;
          *(float *)(UINT_007f46a8 + iVar9) = (*pfVar16 - *pfVar10) * fVar2 + *pfVar10;
          *(float *)(UINT_007f46a8 + 4 + iVar9) = (pfVar16[1] - pfVar10[1]) * fVar2 + pfVar10[1];
          UINT_007f4ac4 = UINT_007f4ac4 | 8;
          uVar18 = UINT_007f46ac;
        }
        if (fVar3 <= *pfVar13) {
          pfVar17 = (float *)(uVar18 + iVar8);
          *pfVar17 = pfVar13[-2];
          pfVar17[1] = pfVar13[-1];
          pfVar17[2] = *pfVar13;
          *(float *)(UINT_007f46a8 + local_10 * 8) = *pfVar16;
          *(float *)(UINT_007f46a8 + 4 + local_10 * 8) = pfVar16[1];
          local_10 = local_10 + 1;
          iVar8 = iVar8 + 0xc;
          uVar18 = UINT_007f46ac;
        }
      }
      pfVar17 = pfVar13 + -2;
      pfVar13 = pfVar13 + 3;
      local_4 = local_4 - 1;
      pfVar10 = pfVar16;
      pfVar16 = pfVar16 + 2;
      uVar11 = UINT_007f47b8;
    } while (local_4 != 0);
  }
  UINT_007f47b8 = uVar11;
  param_4 = (float *)UINT_007f46a8;
  if (2 < (int)local_10) {
    UINT_007f46a8 = UINT_007f461c;
    uVar11 = 0;
    UINT_007f46ac = UINT_007f47b8;
    UINT_007f461c = (uint)param_4;
    pfVar16 = (float *)((uVar18 - 0xc) + local_10 * 0xc);
    pfVar17 = (float *)UINT_007f47b8;
    if (0 < (int)local_10) {
      pfVar13 = (float *)(uVar18 + 4);
      pfVar10 = (float *)(((int)param_4 - 8U) + local_10 * 8);
      iVar8 = 0;
      UINT_007f47b8 = uVar18;
      local_4 = local_10;
      do {
        iVar9 = iVar8;
        if (((float)param_1[1] <= pfVar16[1]) || ((float)param_1[1] <= *pfVar13)) {
          if (((pfVar16[1] != (float)param_1[1]) && (*pfVar13 != (float)param_1[1])) &&
             ((pfVar16[1] < (float)param_1[1] || (*pfVar13 < (float)param_1[1])))) {
            iVar9 = iVar8 + 0xc;
            fVar2 = ((float)param_1[1] - pfVar16[1]) / (*pfVar13 - pfVar16[1]);
            *(int *)((int)pfVar17 + iVar8 + 4) = param_1[1];
            iVar8 = uVar11 * 8;
            uVar11 = uVar11 + 1;
            *(float *)((UINT_007f46ac - 4) + iVar9) = (pfVar13[1] - pfVar16[2]) * fVar2 + pfVar16[2]
            ;
            *(float *)((UINT_007f46ac - 0xc) + iVar9) = (pfVar13[-1] - *pfVar16) * fVar2 + *pfVar16;
            *(float *)(UINT_007f46a8 + iVar8) = (*param_4 - *pfVar10) * fVar2 + *pfVar10;
            *(float *)(UINT_007f46a8 + 4 + iVar8) = (param_4[1] - pfVar10[1]) * fVar2 + pfVar10[1];
            UINT_007f4ac4 = UINT_007f4ac4 | 1;
            pfVar17 = (float *)UINT_007f46ac;
          }
          if ((float)param_1[1] <= *pfVar13) {
            pfVar17 = (float *)((int)pfVar17 + iVar9);
            uVar11 = uVar11 + 1;
            iVar9 = iVar9 + 0xc;
            *pfVar17 = pfVar13[-1];
            pfVar17[1] = *pfVar13;
            pfVar17[2] = pfVar13[1];
            *(float *)((UINT_007f46a8 - 8) + uVar11 * 8) = *param_4;
            *(float *)((UINT_007f46a8 - 4) + uVar11 * 8) = param_4[1];
            pfVar17 = (float *)UINT_007f46ac;
          }
        }
        pfVar16 = pfVar13 + -1;
        pfVar13 = pfVar13 + 3;
        local_4 = local_4 - 1;
        pfVar10 = param_4;
        iVar8 = iVar9;
        uVar18 = UINT_007f47b8;
        param_4 = param_4 + 2;
      } while (local_4 != 0);
    }
    UINT_007f47b8 = uVar18;
    uVar18 = UINT_007f461c;
    if ((int)uVar11 < 3) {
      UINT_007f4ac4 = UINT_007f4ac4 | 0x40;
      return uVar11;
    }
    uVar12 = uVar11;
    pfVar16 = pfVar17;
    if (*param_1 != 0) {
      uVar12 = 0;
      UINT_007f461c = UINT_007f46a8;
      pfVar10 = pfVar17 + uVar11 * 3 + -3;
      iVar8 = UINT_007f46a8 - 8;
      param_4 = (float *)UINT_007f46a8;
      pfVar16 = (float *)UINT_007f47b8;
      UINT_007f46a8 = uVar18;
      UINT_007f46ac = UINT_007f47b8;
      if (0 < (int)uVar11) {
        pfVar14 = pfVar17 + 1;
        pfVar13 = (float *)(iVar8 + uVar11 * 8);
        iVar8 = 0;
        UINT_007f47b8 = (uint)pfVar17;
        local_4 = uVar11;
        do {
          iVar9 = iVar8;
          if ((pfVar10[1] <= (float)param_1[2]) || (*pfVar14 <= (float)param_1[2])) {
            if (((pfVar10[1] != (float)param_1[2]) && (*pfVar14 != (float)param_1[2])) &&
               (((float)param_1[2] < pfVar10[1] || ((float)param_1[2] < *pfVar14)))) {
              iVar9 = iVar8 + 0xc;
              fVar2 = ((float)param_1[2] - pfVar10[1]) / (*pfVar14 - pfVar10[1]);
              *(int *)((int)pfVar16 + iVar8 + 4) = param_1[2];
              iVar8 = uVar12 * 8;
              uVar12 = uVar12 + 1;
              *(float *)((UINT_007f46ac - 4) + iVar9) =
                   (pfVar14[1] - pfVar10[2]) * fVar2 + pfVar10[2];
              *(float *)((UINT_007f46ac - 0xc) + iVar9) =
                   (pfVar14[-1] - *pfVar10) * fVar2 + *pfVar10;
              *(float *)(UINT_007f46a8 + iVar8) = (*param_4 - *pfVar13) * fVar2 + *pfVar13;
              *(float *)(UINT_007f46a8 + 4 + iVar8) = (param_4[1] - pfVar13[1]) * fVar2 + pfVar13[1]
              ;
              UINT_007f4ac4 = UINT_007f4ac4 | 2;
              pfVar16 = (float *)UINT_007f46ac;
            }
            if (*pfVar14 <= (float)param_1[2]) {
              pfVar16 = (float *)((int)pfVar16 + iVar9);
              uVar12 = uVar12 + 1;
              iVar9 = iVar9 + 0xc;
              *pfVar16 = pfVar14[-1];
              pfVar16[1] = *pfVar14;
              pfVar16[2] = pfVar14[1];
              *(float *)((UINT_007f46a8 - 8) + uVar12 * 8) = *param_4;
              *(float *)((UINT_007f46a8 - 4) + uVar12 * 8) = param_4[1];
              pfVar16 = (float *)UINT_007f46ac;
            }
          }
          pfVar10 = pfVar14 + -1;
          pfVar14 = pfVar14 + 3;
          local_4 = local_4 - 1;
          pfVar13 = param_4;
          iVar8 = iVar9;
          pfVar17 = (float *)UINT_007f47b8;
          param_4 = param_4 + 2;
        } while (local_4 != 0);
      }
      UINT_007f47b8 = (uint)pfVar17;
      if ((int)uVar12 < 3) {
        return uVar12;
      }
    }
    if (pfVar16 != param_2) {
      for (uVar11 = uVar12 * 3 & 0x3fffffff; uVar11 != 0; uVar11 = uVar11 - 1) {
        *param_2 = *pfVar16;
        pfVar16 = pfVar16 + 1;
        param_2 = param_2 + 1;
      }
      for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
        *(undefined1 *)param_2 = *(undefined1 *)pfVar16;
        pfVar16 = (float *)((int)pfVar16 + 1);
        param_2 = (float *)((int)param_2 + 1);
      }
      pfVar16 = (float *)UINT_007f46a8;
      for (iVar8 = (uVar12 & 0x1fffffff) << 1; iVar8 != 0; iVar8 = iVar8 + -1) {
        *param_3 = *pfVar16;
        pfVar16 = pfVar16 + 1;
        param_3 = param_3 + 1;
      }
      for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
        *(undefined1 *)param_3 = *(undefined1 *)pfVar16;
        pfVar16 = (float *)((int)pfVar16 + 1);
        param_3 = (float *)((int)param_3 + 1);
      }
    }
    return uVar12;
  }
  return local_10;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0044be80  rdClip_Face3_PosUvFlags ---- */
uint rdClip_Face3_PosUvFlags(int *param_1,float *param_2,float *param_3,uint param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  uint uVar6;
  uint uVar7;
  float *pfVar8;
  uint *puVar9;
  float *pfVar10;
  uint uVar11;
  float *pfVar12;
  int iVar13;
  int iVar14;
  float *pfVar15;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  UINT_007f4ac4 = 0;
  local_c = 0;
  puVar9 = &UINT_007f48c0;
  UINT_007f47b8 = (uint)param_2;
  UINT_007f46ac = (uint)&UINT_007f48c0;
  UINT_007f461c = (uint)param_3;
  UINT_007f46a8 = (uint)&UINT_007f46b8;
  if (0 < (int)param_4) {
    iVar13 = 0;
    local_8 = param_4;
    pfVar10 = param_2 + param_4 * 3 + -3;
    pfVar12 = param_2;
    pfVar5 = param_3 + param_4 * 2 + -2;
    pfVar8 = param_3;
    do {
      fVar2 = (float)param_1[3];
      fVar1 = (float)param_1[3];
      if ((fVar2 <= *pfVar10) || (fVar1 <= *pfVar12)) {
        iVar14 = iVar13;
        if (((*pfVar10 != fVar2) && (fVar1 != *pfVar12)) &&
           ((*pfVar10 < fVar2 || (*pfVar12 < fVar1)))) {
          fVar3 = (fVar2 - *pfVar10) / (*pfVar12 - *pfVar10);
          iVar14 = iVar13 + 0xc;
          iVar4 = local_c * 8;
          local_c = local_c + 1;
          *(float *)((int)puVar9 + iVar13) = fVar2;
          *(float *)((UINT_007f46ac - 8) + iVar14) = (pfVar12[1] - pfVar10[1]) * fVar3 + pfVar10[1];
          *(float *)((UINT_007f46ac - 4) + iVar14) = (pfVar12[2] - pfVar10[2]) * fVar3 + pfVar10[2];
          *(float *)(UINT_007f46a8 + iVar4) = (*pfVar8 - *pfVar5) * fVar3 + *pfVar5;
          *(float *)(UINT_007f46a8 + 4 + iVar4) = (pfVar8[1] - pfVar5[1]) * fVar3 + pfVar5[1];
          UINT_007f4ac4 = UINT_007f4ac4 | 0x10;
          puVar9 = (uint *)UINT_007f46ac;
        }
        iVar13 = iVar14;
        if (fVar1 <= *pfVar12) {
          pfVar10 = (float *)((int)puVar9 + iVar14);
          *pfVar10 = *pfVar12;
          pfVar10[1] = pfVar12[1];
          pfVar10[2] = pfVar12[2];
          *(float *)(UINT_007f46a8 + local_c * 8) = *pfVar8;
          *(float *)(UINT_007f46a8 + 4 + local_c * 8) = pfVar8[1];
          local_c = local_c + 1;
          iVar13 = iVar14 + 0xc;
          puVar9 = (uint *)UINT_007f46ac;
        }
      }
      local_8 = local_8 - 1;
      pfVar10 = pfVar12;
      pfVar12 = pfVar12 + 3;
      pfVar5 = pfVar8;
      pfVar8 = pfVar8 + 2;
    } while (local_8 != 0);
  }
  local_8 = local_c;
  uVar6 = UINT_007f461c;
  if (2 < (int)local_c) {
    UINT_007f46ac = UINT_007f47b8;
    UINT_007f461c = UINT_007f46a8;
    local_c = 0;
    uVar11 = UINT_007f47b8;
    pfVar10 = (float *)puVar9;
    if (0 < (int)local_8) {
      iVar13 = 0;
      pfVar12 = (float *)(puVar9 + local_8 * 3 + -3);
      pfVar5 = (float *)((UINT_007f46a8 - 8) + local_8 * 8);
      pfVar8 = (float *)UINT_007f46a8;
      UINT_007f46a8 = uVar6;
      UINT_007f47b8 = (uint)puVar9;
      do {
        fVar2 = (float)param_1[5];
        fVar1 = (float)param_1[5];
        if ((*pfVar12 <= fVar2) || ((float)*puVar9 <= fVar1)) {
          if (((*pfVar12 != fVar2) && (fVar1 != (float)*puVar9)) &&
             ((fVar2 < *pfVar12 || (fVar1 < (float)*puVar9)))) {
            fVar3 = (fVar2 - *pfVar12) / ((float)*puVar9 - *pfVar12);
            iVar13 = iVar13 + 0xc;
            iVar14 = local_c * 8;
            local_c = local_c + 1;
            *(float *)((uVar11 - 0xc) + iVar13) = fVar2;
            *(float *)((UINT_007f46ac - 8) + iVar13) =
                 ((float)puVar9[1] - pfVar12[1]) * fVar3 + pfVar12[1];
            *(float *)((UINT_007f46ac - 4) + iVar13) =
                 ((float)puVar9[2] - pfVar12[2]) * fVar3 + pfVar12[2];
            *(float *)(UINT_007f46a8 + iVar14) = (*pfVar8 - *pfVar5) * fVar3 + *pfVar5;
            *(float *)(UINT_007f46a8 + 4 + iVar14) = (pfVar8[1] - pfVar5[1]) * fVar3 + pfVar5[1];
            UINT_007f4ac4 = UINT_007f4ac4 | 0x20;
            uVar11 = UINT_007f46ac;
          }
          if ((float)*puVar9 <= fVar1) {
            pfVar10 = (float *)(uVar11 + iVar13);
            *pfVar10 = (float)*puVar9;
            pfVar10[1] = (float)puVar9[1];
            pfVar10[2] = (float)puVar9[2];
            *(float *)(UINT_007f46a8 + local_c * 8) = *pfVar8;
            *(float *)(UINT_007f46a8 + 4 + local_c * 8) = pfVar8[1];
            local_c = local_c + 1;
            iVar13 = iVar13 + 0xc;
            uVar11 = UINT_007f46ac;
          }
        }
        local_8 = local_8 - 1;
        pfVar12 = (float *)puVar9;
        puVar9 = puVar9 + 3;
        pfVar5 = pfVar8;
        pfVar8 = pfVar8 + 2;
        uVar6 = UINT_007f46a8;
        pfVar10 = (float *)UINT_007f47b8;
      } while (local_8 != 0);
    }
    UINT_007f47b8 = (uint)pfVar10;
    UINT_007f46a8 = uVar6;
    param_4 = local_c;
    uVar6 = UINT_007f461c;
    if (2 < (int)local_c) {
      UINT_007f46ac = UINT_007f47b8;
      UINT_007f461c = UINT_007f46a8;
      local_c = 0;
      pfVar10 = (float *)((uVar11 - 0xc) + param_4 * 0xc);
      uVar7 = UINT_007f47b8;
      if (0 < (int)param_4) {
        pfVar12 = (float *)(uVar11 + 8);
        iVar13 = 0;
        pfVar5 = (float *)((UINT_007f46a8 - 8) + param_4 * 8);
        pfVar8 = (float *)UINT_007f46a8;
        UINT_007f46a8 = uVar6;
        UINT_007f47b8 = uVar11;
        do {
          fVar2 = (float)param_1[4];
          fVar1 = (float)param_1[4];
          if ((pfVar10[2] <= fVar2) || (*pfVar12 <= fVar1)) {
            if (((pfVar10[2] != fVar2) && (fVar1 != *pfVar12)) &&
               ((fVar2 < pfVar10[2] || (fVar1 < *pfVar12)))) {
              fVar3 = (fVar2 - pfVar10[2]) / (*pfVar12 - pfVar10[2]);
              iVar13 = iVar13 + 0xc;
              iVar14 = local_c * 8;
              local_c = local_c + 1;
              *(float *)((uVar7 - 0xc) + iVar13) = (pfVar12[-2] - *pfVar10) * fVar3 + *pfVar10;
              *(float *)((UINT_007f46ac - 8) + iVar13) =
                   (pfVar12[-1] - pfVar10[1]) * fVar3 + pfVar10[1];
              *(float *)((UINT_007f46ac - 4) + iVar13) = fVar2;
              *(float *)(UINT_007f46a8 + iVar14) = (*pfVar8 - *pfVar5) * fVar3 + *pfVar5;
              *(float *)(UINT_007f46a8 + 4 + iVar14) = (pfVar8[1] - pfVar5[1]) * fVar3 + pfVar5[1];
              UINT_007f4ac4 = UINT_007f4ac4 | 4;
              uVar7 = UINT_007f46ac;
            }
            if (*pfVar12 <= fVar1) {
              pfVar10 = (float *)(uVar7 + iVar13);
              *pfVar10 = pfVar12[-2];
              pfVar10[1] = pfVar12[-1];
              pfVar10[2] = *pfVar12;
              *(float *)(UINT_007f46a8 + local_c * 8) = *pfVar8;
              *(float *)(UINT_007f46a8 + 4 + local_c * 8) = pfVar8[1];
              local_c = local_c + 1;
              iVar13 = iVar13 + 0xc;
              uVar7 = UINT_007f46ac;
            }
          }
          pfVar10 = pfVar12 + -2;
          pfVar12 = pfVar12 + 3;
          param_4 = param_4 - 1;
          pfVar5 = pfVar8;
          pfVar8 = pfVar8 + 2;
          uVar6 = UINT_007f46a8;
          uVar11 = UINT_007f47b8;
        } while (param_4 != 0);
      }
      UINT_007f47b8 = uVar11;
      UINT_007f46a8 = uVar6;
      param_4 = local_c;
      uVar6 = UINT_007f461c;
      if (2 < (int)local_c) {
        UINT_007f461c = UINT_007f46a8;
        local_c = 0;
        pfVar10 = (float *)((uVar7 - 0xc) + param_4 * 0xc);
        uVar11 = UINT_007f47b8;
        UINT_007f46ac = UINT_007f47b8;
        if (0 < (int)param_4) {
          pfVar12 = (float *)(uVar7 + 8);
          iVar13 = 0;
          pfVar5 = (float *)((UINT_007f46a8 - 8) + param_4 * 8);
          pfVar8 = (float *)UINT_007f46a8;
          UINT_007f46a8 = uVar6;
          UINT_007f47b8 = uVar7;
          do {
            fVar2 = (float)param_1[6];
            fVar1 = (float)param_1[6];
            if ((fVar2 <= pfVar10[2]) || (fVar1 <= *pfVar12)) {
              if (((pfVar10[2] != fVar2) && (fVar1 != *pfVar12)) &&
                 ((pfVar10[2] < fVar2 || (*pfVar12 < fVar1)))) {
                fVar3 = (fVar2 - pfVar10[2]) / (*pfVar12 - pfVar10[2]);
                iVar13 = iVar13 + 0xc;
                iVar14 = local_c * 8;
                local_c = local_c + 1;
                *(float *)((uVar11 - 0xc) + iVar13) = (pfVar12[-2] - *pfVar10) * fVar3 + *pfVar10;
                *(float *)((UINT_007f46ac - 8) + iVar13) =
                     (pfVar12[-1] - pfVar10[1]) * fVar3 + pfVar10[1];
                *(float *)((UINT_007f46ac - 4) + iVar13) = fVar2;
                *(float *)(UINT_007f46a8 + iVar14) = (*pfVar8 - *pfVar5) * fVar3 + *pfVar5;
                *(float *)(UINT_007f46a8 + 4 + iVar14) = (pfVar8[1] - pfVar5[1]) * fVar3 + pfVar5[1]
                ;
                UINT_007f4ac4 = UINT_007f4ac4 | 8;
                uVar11 = UINT_007f46ac;
              }
              if (fVar1 <= *pfVar12) {
                pfVar10 = (float *)(uVar11 + iVar13);
                *pfVar10 = pfVar12[-2];
                pfVar10[1] = pfVar12[-1];
                pfVar10[2] = *pfVar12;
                *(float *)(UINT_007f46a8 + local_c * 8) = *pfVar8;
                *(float *)(UINT_007f46a8 + 4 + local_c * 8) = pfVar8[1];
                local_c = local_c + 1;
                iVar13 = iVar13 + 0xc;
                uVar11 = UINT_007f46ac;
              }
            }
            pfVar10 = pfVar12 + -2;
            pfVar12 = pfVar12 + 3;
            param_4 = param_4 - 1;
            pfVar5 = pfVar8;
            pfVar8 = pfVar8 + 2;
            uVar6 = UINT_007f46a8;
            uVar7 = UINT_007f47b8;
          } while (param_4 != 0);
        }
        UINT_007f47b8 = uVar7;
        UINT_007f46a8 = uVar6;
        uVar6 = UINT_007f461c;
        if ((int)local_c < 3) {
          return local_c;
        }
        uVar7 = 0;
        UINT_007f461c = UINT_007f46a8;
        pfVar10 = (float *)((uVar11 - 0xc) + local_c * 0xc);
        iVar13 = UINT_007f46a8 - 8;
        local_8 = UINT_007f46a8;
        pfVar12 = (float *)UINT_007f47b8;
        UINT_007f46a8 = uVar6;
        UINT_007f46ac = UINT_007f47b8;
        if (0 < (int)local_c) {
          pfVar5 = (float *)(uVar11 + 4);
          iVar14 = 0;
          param_4 = local_c;
          pfVar8 = (float *)(iVar13 + local_c * 8);
          UINT_007f47b8 = uVar11;
          do {
            if (((float)param_1[1] <= pfVar10[1]) || ((float)param_1[1] <= *pfVar5)) {
              if (((pfVar10[1] != (float)param_1[1]) && (*pfVar5 != (float)param_1[1])) &&
                 ((pfVar10[1] < (float)param_1[1] || (*pfVar5 < (float)param_1[1])))) {
                iVar4 = iVar14 + 0xc;
                fVar1 = ((float)param_1[1] - pfVar10[1]) / (*pfVar5 - pfVar10[1]);
                *(int *)((int)pfVar12 + iVar14 + 4) = param_1[1];
                iVar13 = uVar7 * 8;
                uVar7 = uVar7 + 1;
                *(float *)((UINT_007f46ac - 4) + iVar4) =
                     (pfVar5[1] - pfVar10[2]) * fVar1 + pfVar10[2];
                *(float *)((UINT_007f46ac - 0xc) + iVar4) =
                     (pfVar5[-1] - *pfVar10) * fVar1 + *pfVar10;
                *(float *)(UINT_007f46a8 + iVar13) = (*(float *)local_8 - *pfVar8) * fVar1 + *pfVar8
                ;
                *(float *)(UINT_007f46a8 + 4 + iVar13) =
                     (*(float *)(local_8 + 4) - pfVar8[1]) * fVar1 + pfVar8[1];
                UINT_007f4ac4 = UINT_007f4ac4 | 1;
                pfVar12 = (float *)UINT_007f46ac;
                iVar14 = iVar4;
              }
              if ((float)param_1[1] <= *pfVar5) {
                pfVar12 = (float *)((int)pfVar12 + iVar14);
                uVar7 = uVar7 + 1;
                iVar14 = iVar14 + 0xc;
                *pfVar12 = pfVar5[-1];
                pfVar12[1] = *pfVar5;
                pfVar12[2] = pfVar5[1];
                *(undefined4 *)((UINT_007f46a8 - 8) + uVar7 * 8) = *(undefined4 *)local_8;
                *(undefined4 *)((UINT_007f46a8 - 4) + uVar7 * 8) = *(undefined4 *)(local_8 + 4);
                pfVar12 = (float *)UINT_007f46ac;
              }
            }
            pfVar10 = pfVar5 + -1;
            pfVar5 = pfVar5 + 3;
            param_4 = param_4 - 1;
            pfVar8 = (float *)local_8;
            uVar11 = UINT_007f47b8;
            local_8 = local_8 + 8;
          } while (param_4 != 0);
        }
        UINT_007f47b8 = uVar11;
        uVar6 = UINT_007f461c;
        if ((int)uVar7 < 3) {
          UINT_007f4ac4 = UINT_007f4ac4 | 0x40;
          return uVar7;
        }
        local_c = uVar7;
        pfVar10 = pfVar12;
        if (*param_1 != 0) {
          local_c = 0;
          UINT_007f46ac = UINT_007f47b8;
          UINT_007f461c = UINT_007f46a8;
          pfVar5 = pfVar12 + uVar7 * 3 + -3;
          iVar13 = UINT_007f46a8 - 8;
          local_8 = UINT_007f46a8;
          pfVar10 = (float *)UINT_007f47b8;
          UINT_007f46a8 = uVar6;
          if (0 < (int)uVar7) {
            iVar14 = 0;
            pfVar15 = pfVar12 + 1;
            pfVar8 = (float *)(iVar13 + uVar7 * 8);
            UINT_007f47b8 = (uint)pfVar12;
            param_4 = uVar7;
            do {
              if ((pfVar5[1] <= (float)param_1[2]) || (*pfVar15 <= (float)param_1[2])) {
                if (((pfVar5[1] != (float)param_1[2]) && (*pfVar15 != (float)param_1[2])) &&
                   (((float)param_1[2] < pfVar5[1] || ((float)param_1[2] < *pfVar15)))) {
                  iVar4 = iVar14 + 0xc;
                  fVar1 = ((float)param_1[2] - pfVar5[1]) / (*pfVar15 - pfVar5[1]);
                  *(int *)((int)pfVar10 + iVar14 + 4) = param_1[2];
                  iVar13 = local_c * 8;
                  local_c = local_c + 1;
                  *(float *)((UINT_007f46ac - 4) + iVar4) =
                       (pfVar15[1] - pfVar5[2]) * fVar1 + pfVar5[2];
                  *(float *)((UINT_007f46ac - 0xc) + iVar4) =
                       (pfVar15[-1] - *pfVar5) * fVar1 + *pfVar5;
                  *(float *)(UINT_007f46a8 + iVar13) =
                       (*(float *)local_8 - *pfVar8) * fVar1 + *pfVar8;
                  *(float *)(UINT_007f46a8 + 4 + iVar13) =
                       (*(float *)(local_8 + 4) - pfVar8[1]) * fVar1 + pfVar8[1];
                  UINT_007f4ac4 = UINT_007f4ac4 | 2;
                  iVar14 = iVar4;
                  pfVar10 = (float *)UINT_007f46ac;
                }
                if (*pfVar15 <= (float)param_1[2]) {
                  pfVar10 = (float *)((int)pfVar10 + iVar14);
                  local_c = local_c + 1;
                  iVar14 = iVar14 + 0xc;
                  *pfVar10 = pfVar15[-1];
                  pfVar10[1] = *pfVar15;
                  pfVar10[2] = pfVar15[1];
                  *(undefined4 *)((UINT_007f46a8 - 8) + local_c * 8) = *(undefined4 *)local_8;
                  *(undefined4 *)((UINT_007f46a8 - 4) + local_c * 8) = *(undefined4 *)(local_8 + 4);
                  pfVar10 = (float *)UINT_007f46ac;
                }
              }
              pfVar5 = pfVar15 + -1;
              pfVar15 = pfVar15 + 3;
              param_4 = param_4 - 1;
              pfVar8 = (float *)local_8;
              pfVar12 = (float *)UINT_007f47b8;
              local_8 = local_8 + 8;
            } while (param_4 != 0);
          }
          UINT_007f47b8 = (uint)pfVar12;
          if ((int)local_c < 3) {
            return local_c;
          }
        }
        if (pfVar10 != param_2) {
          for (uVar6 = local_c * 3 & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1) {
            *param_2 = *pfVar10;
            pfVar10 = pfVar10 + 1;
            param_2 = param_2 + 1;
          }
          for (iVar13 = 0; iVar13 != 0; iVar13 = iVar13 + -1) {
            *(undefined1 *)param_2 = *(undefined1 *)pfVar10;
            pfVar10 = (float *)((int)pfVar10 + 1);
            param_2 = (float *)((int)param_2 + 1);
          }
          pfVar10 = (float *)UINT_007f46a8;
          for (iVar13 = (local_c & 0x1fffffff) << 1; iVar13 != 0; iVar13 = iVar13 + -1) {
            *param_3 = *pfVar10;
            pfVar10 = pfVar10 + 1;
            param_3 = param_3 + 1;
          }
          for (iVar13 = 0; iVar13 != 0; iVar13 = iVar13 + -1) {
            *(undefined1 *)param_3 = *(undefined1 *)pfVar10;
            pfVar10 = (float *)((int)pfVar10 + 1);
            param_3 = (float *)((int)param_3 + 1);
          }
        }
      }
    }
  }
  return local_c;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0044c9d0  rdClip_Face3_PosUvLitColor ---- */
uint rdClip_Face3_PosUvLitColor
               (int *param_1,float *param_2,float *param_3,undefined4 *param_4,float *param_5)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  float *pfVar11;
  int iVar12;
  uint uVar13;
  float *pfVar14;
  uint *puVar15;
  float *pfVar16;
  float *pfVar17;
  undefined4 *puVar18;
  int iVar19;
  float *pfVar20;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  UINT_007f4618 = (uint)param_4;
  local_14 = (uint)(param_4 + ((int)param_5 - 1));
  uVar8 = 0;
  puVar15 = &UINT_007f48c0;
  UINT_007f4ac4 = 0;
  UINT_007f47b8 = (uint)param_2;
  UINT_007f46ac = (uint)&UINT_007f48c0;
  UINT_007f461c = (uint)param_3;
  UINT_007f46a8 = (uint)&UINT_007f46b8;
  UINT_007f46b0 = (uint)&UINT_007f47c0;
  local_18 = (uint)param_4;
  if (0 < (int)param_5) {
    iVar12 = 0;
    local_4 = (uint)param_5;
    pfVar16 = param_2;
    pfVar17 = param_3;
    pfVar11 = param_3 + (int)param_5 * 2 + -2;
    param_5 = param_2 + (int)param_5 * 3 + -3;
    do {
      pfVar20 = pfVar17;
      pfVar14 = pfVar16;
      fVar2 = (float)param_1[0xc] * param_5[1];
      fVar3 = (float)param_1[0xc] * pfVar14[1];
      if ((fVar2 <= *param_5) || (fVar3 <= *pfVar14)) {
        if (((*param_5 != fVar2) && (fVar3 != *pfVar14)) &&
           ((*param_5 < fVar2 || (*pfVar14 < fVar3)))) {
          fVar2 = pfVar14[1] - param_5[1];
          fVar4 = *pfVar14 - *param_5;
          fVar1 = (float)param_1[0xc] * fVar2 - fVar4;
          fVar5 = pfVar14[1] * *param_5 - param_5[1] * *pfVar14;
          if (fVar1 != 0.0) {
            fVar5 = fVar5 / fVar1;
          }
          fVar1 = fVar2;
          if (fVar2 < 0.0) {
            fVar1 = -fVar2;
          }
          fVar6 = fVar4;
          if (fVar4 < 0.0) {
            fVar6 = -fVar4;
          }
          if (fVar1 <= fVar6) {
            fVar2 = ((float)param_1[0xc] * fVar5 - *param_5) / fVar4;
          }
          else {
            fVar2 = (fVar5 - param_5[1]) / fVar2;
          }
          *(float *)((int)puVar15 + iVar12) = (float)param_1[0xc] * fVar5;
          iVar12 = iVar12 + 0xc;
          *(float *)((UINT_007f46ac - 8) + iVar12) = fVar5;
          uVar8 = uVar8 + 1;
          *(float *)((UINT_007f46ac - 4) + iVar12) = (pfVar14[2] - param_5[2]) * fVar2 + param_5[2];
          *(float *)((UINT_007f46a8 - 8) + uVar8 * 8) = (*pfVar20 - *pfVar11) * fVar2 + *pfVar11;
          *(float *)((UINT_007f46a8 - 4) + uVar8 * 8) =
               (pfVar20[1] - pfVar11[1]) * fVar2 + pfVar11[1];
          *(float *)((UINT_007f46b0 - 4) + uVar8 * 4) =
               (*(float *)local_18 - *(float *)local_14) * fVar2 + *(float *)local_14;
          UINT_007f4ac4 = UINT_007f4ac4 | 0x10;
          puVar15 = (uint *)UINT_007f46ac;
        }
        if (fVar3 <= *pfVar14) {
          pfVar16 = (float *)((int)puVar15 + iVar12);
          uVar8 = uVar8 + 1;
          iVar12 = iVar12 + 0xc;
          *pfVar16 = *pfVar14;
          pfVar16[1] = pfVar14[1];
          pfVar16[2] = pfVar14[2];
          *(float *)((UINT_007f46a8 - 8) + uVar8 * 8) = *pfVar20;
          *(float *)((UINT_007f46a8 - 4) + uVar8 * 8) = pfVar20[1];
          *(undefined4 *)((UINT_007f46b0 - 4) + uVar8 * 4) = *(undefined4 *)local_18;
          puVar15 = (uint *)UINT_007f46ac;
        }
      }
      local_14 = local_18;
      local_18 = local_18 + 4;
      local_4 = local_4 - 1;
      pfVar16 = pfVar14 + 3;
      pfVar17 = pfVar20 + 2;
      pfVar11 = pfVar20;
      param_5 = pfVar14;
    } while (local_4 != 0);
  }
  local_18 = UINT_007f46b0;
  uVar9 = UINT_007f461c;
  if ((int)uVar8 < 3) {
    return uVar8;
  }
  UINT_007f461c = UINT_007f46a8;
  UINT_007f46b0 = UINT_007f4618;
  UINT_007f4618 = local_18;
  uVar13 = 0;
  local_14 = (local_18 - 4) + uVar8 * 4;
  uVar10 = UINT_007f47b8;
  UINT_007f46ac = UINT_007f47b8;
  pfVar16 = (float *)puVar15;
  if (0 < (int)uVar8) {
    iVar12 = 0;
    pfVar17 = (float *)UINT_007f46a8;
    pfVar11 = (float *)((UINT_007f46a8 - 8) + uVar8 * 8);
    UINT_007f46a8 = uVar9;
    UINT_007f47b8 = (uint)puVar15;
    param_5 = (float *)(puVar15 + uVar8 * 3 + -3);
    local_4 = uVar8;
    do {
      pfVar14 = (float *)puVar15;
      pfVar16 = pfVar17;
      fVar2 = (float)param_1[10] * param_5[1];
      fVar3 = (float)param_1[10] * pfVar14[1];
      if ((*param_5 <= fVar2) || (*pfVar14 <= fVar3)) {
        if (((*param_5 != fVar2) && (fVar3 != *pfVar14)) &&
           ((fVar2 < *param_5 || (fVar3 < *pfVar14)))) {
          fVar2 = pfVar14[1] - param_5[1];
          fVar4 = *pfVar14 - *param_5;
          fVar1 = (float)param_1[10] * fVar2 - fVar4;
          fVar5 = pfVar14[1] * *param_5 - param_5[1] * *pfVar14;
          if (fVar1 != 0.0) {
            fVar5 = fVar5 / fVar1;
          }
          fVar1 = fVar2;
          if (fVar2 < 0.0) {
            fVar1 = -fVar2;
          }
          fVar6 = fVar4;
          if (fVar4 < 0.0) {
            fVar6 = -fVar4;
          }
          if (fVar1 <= fVar6) {
            fVar2 = ((float)param_1[10] * fVar5 - *param_5) / fVar4;
          }
          else {
            fVar2 = (fVar5 - param_5[1]) / fVar2;
          }
          *(float *)(uVar10 + iVar12) = (float)param_1[10] * fVar5;
          iVar12 = iVar12 + 0xc;
          *(float *)((UINT_007f46ac - 8) + iVar12) = fVar5;
          uVar13 = uVar13 + 1;
          *(float *)((UINT_007f46ac - 4) + iVar12) = (pfVar14[2] - param_5[2]) * fVar2 + param_5[2];
          *(float *)((UINT_007f46a8 - 8) + uVar13 * 8) = (*pfVar16 - *pfVar11) * fVar2 + *pfVar11;
          *(float *)((UINT_007f46a8 - 4) + uVar13 * 8) =
               (pfVar16[1] - pfVar11[1]) * fVar2 + pfVar11[1];
          *(float *)((UINT_007f46b0 - 4) + uVar13 * 4) =
               (*(float *)local_18 - *(float *)local_14) * fVar2 + *(float *)local_14;
          UINT_007f4ac4 = UINT_007f4ac4 | 0x20;
          uVar10 = UINT_007f46ac;
        }
        if (*pfVar14 <= fVar3) {
          pfVar17 = (float *)(uVar10 + iVar12);
          uVar13 = uVar13 + 1;
          iVar12 = iVar12 + 0xc;
          *pfVar17 = *pfVar14;
          pfVar17[1] = pfVar14[1];
          pfVar17[2] = pfVar14[2];
          *(float *)((UINT_007f46a8 - 8) + uVar13 * 8) = *pfVar16;
          *(float *)((UINT_007f46a8 - 4) + uVar13 * 8) = pfVar16[1];
          *(undefined4 *)((UINT_007f46b0 - 4) + uVar13 * 4) = *(undefined4 *)local_18;
          uVar10 = UINT_007f46ac;
        }
      }
      local_14 = local_18;
      local_18 = local_18 + 4;
      local_4 = local_4 - 1;
      pfVar17 = pfVar16 + 2;
      puVar15 = (uint *)(pfVar14 + 3);
      pfVar11 = pfVar16;
      uVar9 = UINT_007f46a8;
      pfVar16 = (float *)UINT_007f47b8;
      param_5 = pfVar14;
    } while (local_4 != 0);
  }
  UINT_007f47b8 = (uint)pfVar16;
  UINT_007f46a8 = uVar9;
  local_18 = UINT_007f46b0;
  pfVar16 = (float *)UINT_007f46a8;
  uVar8 = UINT_007f4618;
  if (2 < (int)uVar13) {
    UINT_007f46a8 = UINT_007f461c;
    UINT_007f4618 = UINT_007f46b0;
    UINT_007f461c = (uint)pfVar16;
    UINT_007f46b0 = uVar8;
    uVar9 = 0;
    UINT_007f46ac = UINT_007f47b8;
    pfVar17 = (float *)((uVar10 - 0xc) + uVar13 * 0xc);
    local_14 = (local_18 - 4) + uVar13 * 4;
    uVar8 = UINT_007f47b8;
    if (0 < (int)uVar13) {
      iVar12 = 0;
      local_c = uVar10 + 8;
      pfVar11 = (float *)(((int)pfVar16 - 8U) + uVar13 * 8);
      UINT_007f47b8 = uVar10;
      local_4 = uVar13;
      do {
        pfVar14 = pfVar16;
        fVar2 = (float)param_1[0xb] * pfVar17[1];
        fVar3 = (float)param_1[0xb] * *(float *)(local_c - 4);
        if ((pfVar17[2] <= fVar2) || (*(float *)local_c <= fVar3)) {
          if (((pfVar17[2] != fVar2) && (fVar3 != *(float *)local_c)) &&
             ((fVar2 < pfVar17[2] || (fVar3 < *(float *)local_c)))) {
            fVar2 = *(float *)(local_c - 4) - pfVar17[1];
            fVar4 = *(float *)local_c - pfVar17[2];
            fVar1 = (float)param_1[0xb] * fVar2 - fVar4;
            fVar5 = pfVar17[2] * *(float *)(local_c - 4) - pfVar17[1] * *(float *)local_c;
            if (fVar1 != 0.0) {
              fVar5 = fVar5 / fVar1;
            }
            fVar1 = (float)param_1[0xb];
            fVar6 = fVar2;
            if (fVar2 < 0.0) {
              fVar6 = -fVar2;
            }
            fVar7 = fVar4;
            if (fVar4 < 0.0) {
              fVar7 = -fVar4;
            }
            if (fVar6 <= fVar7) {
              fVar2 = (fVar1 * fVar5 - pfVar17[2]) / fVar4;
            }
            else {
              fVar2 = (fVar5 - pfVar17[1]) / fVar2;
            }
            iVar12 = iVar12 + 0xc;
            uVar9 = uVar9 + 1;
            *(float *)((uVar8 - 0xc) + iVar12) =
                 (*(float *)(local_c - 8) - *pfVar17) * fVar2 + *pfVar17;
            *(float *)((UINT_007f46ac - 8) + iVar12) = fVar5;
            *(float *)((UINT_007f46ac - 4) + iVar12) = fVar1 * fVar5;
            *(float *)((UINT_007f46a8 - 8) + uVar9 * 8) = (*pfVar14 - *pfVar11) * fVar2 + *pfVar11;
            *(float *)((UINT_007f46a8 - 4) + uVar9 * 8) =
                 (pfVar14[1] - pfVar11[1]) * fVar2 + pfVar11[1];
            *(float *)((UINT_007f46b0 - 4) + uVar9 * 4) =
                 (*(float *)local_18 - *(float *)local_14) * fVar2 + *(float *)local_14;
            UINT_007f4ac4 = UINT_007f4ac4 | 4;
            uVar8 = UINT_007f46ac;
          }
          if (*(float *)local_c <= fVar3) {
            puVar18 = (undefined4 *)(uVar8 + iVar12);
            uVar9 = uVar9 + 1;
            iVar12 = iVar12 + 0xc;
            *puVar18 = *(undefined4 *)(local_c - 8);
            puVar18[1] = *(undefined4 *)(local_c - 4);
            puVar18[2] = *(undefined4 *)local_c;
            *(float *)((UINT_007f46a8 - 8) + uVar9 * 8) = *pfVar14;
            *(float *)((UINT_007f46a8 - 4) + uVar9 * 8) = pfVar14[1];
            *(undefined4 *)((UINT_007f46b0 - 4) + uVar9 * 4) = *(undefined4 *)local_18;
            uVar8 = UINT_007f46ac;
          }
        }
        pfVar17 = (float *)(local_c - 8);
        local_c = local_c + 0xc;
        local_14 = local_18;
        local_18 = local_18 + 4;
        local_4 = local_4 - 1;
        pfVar16 = pfVar14 + 2;
        pfVar11 = pfVar14;
        uVar10 = UINT_007f47b8;
      } while (local_4 != 0);
    }
    UINT_007f47b8 = uVar10;
    local_18 = UINT_007f46b0;
    pfVar16 = (float *)UINT_007f46a8;
    if ((int)uVar9 < 3) {
      return uVar9;
    }
    UINT_007f46a8 = UINT_007f461c;
    UINT_007f46b0 = UINT_007f4618;
    UINT_007f4618 = local_18;
    uVar10 = 0;
    local_14 = (local_18 - 4) + uVar9 * 4;
    pfVar17 = (float *)((uVar8 - 0xc) + uVar9 * 0xc);
    UINT_007f46ac = UINT_007f47b8;
    UINT_007f461c = (uint)pfVar16;
    uVar13 = UINT_007f47b8;
    if (0 < (int)uVar9) {
      iVar12 = 0;
      local_c = uVar8 + 8;
      pfVar11 = (float *)(((int)pfVar16 - 8U) + uVar9 * 8);
      UINT_007f47b8 = uVar8;
      local_4 = uVar9;
      do {
        pfVar14 = pfVar16;
        fVar2 = (float)param_1[8] * pfVar17[1];
        fVar3 = (float)param_1[8] * *(float *)(local_c - 4);
        if ((fVar2 <= pfVar17[2]) || (fVar3 <= *(float *)local_c)) {
          if (((pfVar17[2] != fVar2) && (fVar3 != *(float *)local_c)) &&
             ((pfVar17[2] < fVar2 || (*(float *)local_c < fVar3)))) {
            fVar2 = *(float *)(local_c - 4) - pfVar17[1];
            fVar4 = *(float *)local_c - pfVar17[2];
            fVar1 = (float)param_1[8] * fVar2 - fVar4;
            fVar5 = pfVar17[2] * *(float *)(local_c - 4) - pfVar17[1] * *(float *)local_c;
            if (fVar1 != 0.0) {
              fVar5 = fVar5 / fVar1;
            }
            fVar1 = (float)param_1[8];
            fVar6 = fVar2;
            if (fVar2 < 0.0) {
              fVar6 = -fVar2;
            }
            fVar7 = fVar4;
            if (fVar4 < 0.0) {
              fVar7 = -fVar4;
            }
            if (fVar6 <= fVar7) {
              fVar2 = (fVar1 * fVar5 - pfVar17[2]) / fVar4;
            }
            else {
              fVar2 = (fVar5 - pfVar17[1]) / fVar2;
            }
            iVar12 = iVar12 + 0xc;
            uVar10 = uVar10 + 1;
            *(float *)((uVar13 - 0xc) + iVar12) =
                 (*(float *)(local_c - 8) - *pfVar17) * fVar2 + *pfVar17;
            *(float *)((UINT_007f46ac - 8) + iVar12) = fVar5;
            *(float *)((UINT_007f46ac - 4) + iVar12) = fVar1 * fVar5;
            *(float *)((UINT_007f46a8 - 8) + uVar10 * 8) = (*pfVar14 - *pfVar11) * fVar2 + *pfVar11;
            *(float *)((UINT_007f46a8 - 4) + uVar10 * 8) =
                 (pfVar14[1] - pfVar11[1]) * fVar2 + pfVar11[1];
            *(float *)((UINT_007f46b0 - 4) + uVar10 * 4) =
                 (*(float *)local_18 - *(float *)local_14) * fVar2 + *(float *)local_14;
            UINT_007f4ac4 = UINT_007f4ac4 | 8;
            uVar13 = UINT_007f46ac;
          }
          if (fVar3 <= *(float *)local_c) {
            puVar18 = (undefined4 *)(uVar13 + iVar12);
            uVar10 = uVar10 + 1;
            iVar12 = iVar12 + 0xc;
            *puVar18 = *(undefined4 *)(local_c - 8);
            puVar18[1] = *(undefined4 *)(local_c - 4);
            puVar18[2] = *(undefined4 *)local_c;
            *(float *)((UINT_007f46a8 - 8) + uVar10 * 8) = *pfVar14;
            *(float *)((UINT_007f46a8 - 4) + uVar10 * 8) = pfVar14[1];
            *(undefined4 *)((UINT_007f46b0 - 4) + uVar10 * 4) = *(undefined4 *)local_18;
            uVar13 = UINT_007f46ac;
          }
        }
        pfVar17 = (float *)(local_c - 8);
        local_c = local_c + 0xc;
        local_14 = local_18;
        local_18 = local_18 + 4;
        local_4 = local_4 - 1;
        pfVar16 = pfVar14 + 2;
        pfVar11 = pfVar14;
        uVar8 = UINT_007f47b8;
      } while (local_4 != 0);
    }
    UINT_007f47b8 = uVar8;
    local_18 = UINT_007f46b0;
    param_5 = (float *)UINT_007f46a8;
    if ((int)uVar10 < 3) {
      return uVar10;
    }
    UINT_007f46a8 = UINT_007f461c;
    UINT_007f46b0 = UINT_007f4618;
    UINT_007f461c = (uint)param_5;
    UINT_007f4618 = local_18;
    uVar8 = 0;
    local_14 = (local_18 - 4) + uVar10 * 4;
    pfVar16 = (float *)((uVar13 - 0xc) + uVar10 * 0xc);
    UINT_007f46ac = UINT_007f47b8;
    pfVar17 = (float *)UINT_007f47b8;
    if (0 < (int)uVar10) {
      pfVar14 = (float *)(uVar13 + 4);
      pfVar11 = (float *)(((int)param_5 - 8U) + uVar10 * 8);
      iVar12 = 0;
      UINT_007f47b8 = uVar13;
      local_4 = uVar10;
      do {
        iVar19 = iVar12;
        if (((float)param_1[1] <= pfVar16[1]) || ((float)param_1[1] <= *pfVar14)) {
          if (((pfVar16[1] != (float)param_1[1]) && (*pfVar14 != (float)param_1[1])) &&
             ((pfVar16[1] < (float)param_1[1] || (*pfVar14 < (float)param_1[1])))) {
            iVar19 = iVar12 + 0xc;
            uVar8 = uVar8 + 1;
            fVar2 = ((float)param_1[1] - pfVar16[1]) / (*pfVar14 - pfVar16[1]);
            *(int *)((int)pfVar17 + iVar12 + 4) = param_1[1];
            *(float *)((UINT_007f46ac - 4) + iVar19) =
                 (pfVar14[1] - pfVar16[2]) * fVar2 + pfVar16[2];
            *(float *)((UINT_007f46ac - 0xc) + iVar19) = (pfVar14[-1] - *pfVar16) * fVar2 + *pfVar16
            ;
            *(float *)((UINT_007f46a8 - 8) + uVar8 * 8) = (*param_5 - *pfVar11) * fVar2 + *pfVar11;
            *(float *)((UINT_007f46a8 - 4) + uVar8 * 8) =
                 (param_5[1] - pfVar11[1]) * fVar2 + pfVar11[1];
            *(float *)((UINT_007f46b0 - 4) + uVar8 * 4) =
                 (*(float *)local_18 - *(float *)local_14) * fVar2 + *(float *)local_14;
            UINT_007f4ac4 = UINT_007f4ac4 | 1;
            pfVar17 = (float *)UINT_007f46ac;
          }
          if ((float)param_1[1] <= *pfVar14) {
            pfVar17 = (float *)((int)pfVar17 + iVar19);
            uVar8 = uVar8 + 1;
            iVar19 = iVar19 + 0xc;
            *pfVar17 = pfVar14[-1];
            pfVar17[1] = *pfVar14;
            pfVar17[2] = pfVar14[1];
            *(float *)((UINT_007f46a8 - 8) + uVar8 * 8) = *param_5;
            *(float *)((UINT_007f46a8 - 4) + uVar8 * 8) = param_5[1];
            *(undefined4 *)((UINT_007f46b0 - 4) + uVar8 * 4) = *(undefined4 *)local_18;
            pfVar17 = (float *)UINT_007f46ac;
          }
        }
        pfVar16 = pfVar14 + -1;
        local_14 = local_18;
        local_18 = local_18 + 4;
        pfVar14 = pfVar14 + 3;
        local_4 = local_4 - 1;
        pfVar11 = param_5;
        iVar12 = iVar19;
        uVar13 = UINT_007f47b8;
        param_5 = param_5 + 2;
      } while (local_4 != 0);
    }
    UINT_007f47b8 = uVar13;
    uVar10 = UINT_007f461c;
    uVar9 = UINT_007f4618;
    if ((int)uVar8 < 3) {
      UINT_007f4ac4 = UINT_007f4ac4 | 0x40;
      return uVar8;
    }
    uVar13 = uVar8;
    pfVar16 = pfVar17;
    if (*param_1 != 0) {
      UINT_007f461c = UINT_007f46a8;
      UINT_007f4618 = UINT_007f46b0;
      uVar13 = 0;
      param_5 = (float *)UINT_007f46a8;
      local_14 = (UINT_007f46b0 - 4) + uVar8 * 4;
      pfVar11 = pfVar17 + uVar8 * 3 + -3;
      iVar12 = UINT_007f46a8 - 8;
      local_18 = UINT_007f46b0;
      pfVar16 = (float *)UINT_007f47b8;
      UINT_007f46a8 = uVar10;
      UINT_007f46ac = UINT_007f47b8;
      UINT_007f46b0 = uVar9;
      if (0 < (int)uVar8) {
        pfVar20 = pfVar17 + 1;
        pfVar14 = (float *)(iVar12 + uVar8 * 8);
        iVar12 = 0;
        UINT_007f47b8 = (uint)pfVar17;
        local_4 = uVar8;
        do {
          iVar19 = iVar12;
          if ((pfVar11[1] <= (float)param_1[2]) || (*pfVar20 <= (float)param_1[2])) {
            if (((pfVar11[1] != (float)param_1[2]) && (*pfVar20 != (float)param_1[2])) &&
               (((float)param_1[2] < pfVar11[1] || ((float)param_1[2] < *pfVar20)))) {
              iVar19 = iVar12 + 0xc;
              uVar13 = uVar13 + 1;
              fVar2 = ((float)param_1[2] - pfVar11[1]) / (*pfVar20 - pfVar11[1]);
              *(int *)((int)pfVar16 + iVar12 + 4) = param_1[2];
              *(float *)((UINT_007f46ac - 4) + iVar19) =
                   (pfVar20[1] - pfVar11[2]) * fVar2 + pfVar11[2];
              *(float *)((UINT_007f46ac - 0xc) + iVar19) =
                   (pfVar20[-1] - *pfVar11) * fVar2 + *pfVar11;
              *(float *)((UINT_007f46a8 - 8) + uVar13 * 8) =
                   (*param_5 - *pfVar14) * fVar2 + *pfVar14;
              *(float *)((UINT_007f46a8 - 4) + uVar13 * 8) =
                   (param_5[1] - pfVar14[1]) * fVar2 + pfVar14[1];
              *(float *)((UINT_007f46b0 - 4) + uVar13 * 4) =
                   (*(float *)local_18 - *(float *)local_14) * fVar2 + *(float *)local_14;
              UINT_007f4ac4 = UINT_007f4ac4 | 2;
              pfVar16 = (float *)UINT_007f46ac;
            }
            if (*pfVar20 <= (float)param_1[2]) {
              pfVar16 = (float *)((int)pfVar16 + iVar19);
              uVar13 = uVar13 + 1;
              iVar19 = iVar19 + 0xc;
              *pfVar16 = pfVar20[-1];
              pfVar16[1] = *pfVar20;
              pfVar16[2] = pfVar20[1];
              *(float *)((UINT_007f46a8 - 8) + uVar13 * 8) = *param_5;
              *(float *)((UINT_007f46a8 - 4) + uVar13 * 8) = param_5[1];
              *(undefined4 *)((UINT_007f46b0 - 4) + uVar13 * 4) = *(undefined4 *)local_18;
              pfVar16 = (float *)UINT_007f46ac;
            }
          }
          pfVar11 = pfVar20 + -1;
          local_14 = local_18;
          local_18 = local_18 + 4;
          pfVar20 = pfVar20 + 3;
          local_4 = local_4 - 1;
          pfVar14 = param_5;
          iVar12 = iVar19;
          pfVar17 = (float *)UINT_007f47b8;
          param_5 = param_5 + 2;
        } while (local_4 != 0);
      }
      UINT_007f47b8 = (uint)pfVar17;
      if ((int)uVar13 < 3) {
        return uVar13;
      }
    }
    if (pfVar16 != param_2) {
      for (uVar8 = uVar13 * 3 & 0x3fffffff; uVar8 != 0; uVar8 = uVar8 - 1) {
        *param_2 = *pfVar16;
        pfVar16 = pfVar16 + 1;
        param_2 = param_2 + 1;
      }
      for (iVar12 = 0; iVar12 != 0; iVar12 = iVar12 + -1) {
        *(undefined1 *)param_2 = *(undefined1 *)pfVar16;
        pfVar16 = (float *)((int)pfVar16 + 1);
        param_2 = (float *)((int)param_2 + 1);
      }
      pfVar16 = (float *)UINT_007f46a8;
      for (iVar12 = (uVar13 & 0x1fffffff) << 1; iVar12 != 0; iVar12 = iVar12 + -1) {
        *param_3 = *pfVar16;
        pfVar16 = pfVar16 + 1;
        param_3 = param_3 + 1;
      }
      for (iVar12 = 0; uVar8 = uVar13, puVar18 = (undefined4 *)UINT_007f46b0, iVar12 != 0;
          iVar12 = iVar12 + -1) {
        *(undefined1 *)param_3 = *(undefined1 *)pfVar16;
        pfVar16 = (float *)((int)pfVar16 + 1);
        param_3 = (float *)((int)param_3 + 1);
      }
      for (; uVar8 != 0; uVar8 = uVar8 - 1) {
        *param_4 = *puVar18;
        puVar18 = puVar18 + 1;
        param_4 = param_4 + 1;
      }
    }
  }
  return uVar13;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0044da40  rdClip_Face3_PosUvLitFlags ---- */
uint rdClip_Face3_PosUvLitFlags
               (int *param_1,float *param_2,undefined4 *param_3,undefined4 *param_4,uint param_5)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  float *pfVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  float *pfVar10;
  float *pfVar11;
  uint *puVar12;
  float *pfVar13;
  uint uVar14;
  float *pfVar15;
  undefined4 *puVar16;
  undefined4 *puVar17;
  int iVar18;
  int iVar19;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  UINT_007f4618 = (uint)param_4;
  UINT_007f47b8 = (uint)param_2;
  uVar7 = 0;
  puVar12 = &UINT_007f48c0;
  local_c = (uint)(param_4 + param_5 + -1);
  local_10 = (uint)param_3;
  local_14 = (uint)param_4;
  UINT_007f4ac4 = 0;
  UINT_007f46ac = (uint)&UINT_007f48c0;
  UINT_007f461c = (uint)param_3;
  UINT_007f46a8 = (uint)&UINT_007f46b8;
  UINT_007f46b0 = (uint)&UINT_007f47c0;
  if (0 < (int)param_5) {
    iVar18 = 0;
    pfVar13 = param_2 + param_5 * 3 + -3;
    pfVar15 = param_2;
    pfVar5 = (float *)(param_3 + param_5 * 2 + -2);
    do {
      fVar2 = (float)param_1[3];
      fVar1 = (float)param_1[3];
      if ((fVar2 <= *pfVar13) || (fVar1 <= *pfVar15)) {
        if (((*pfVar13 != fVar2) && (fVar1 != *pfVar15)) &&
           ((*pfVar13 < fVar2 || (*pfVar15 < fVar1)))) {
          fVar3 = (fVar2 - *pfVar13) / (*pfVar15 - *pfVar13);
          iVar19 = iVar18 + 0xc;
          uVar7 = uVar7 + 1;
          *(float *)((int)puVar12 + iVar18) = fVar2;
          *(float *)((UINT_007f46ac - 8) + iVar19) = (pfVar15[1] - pfVar13[1]) * fVar3 + pfVar13[1];
          *(float *)((UINT_007f46ac - 4) + iVar19) = (pfVar15[2] - pfVar13[2]) * fVar3 + pfVar13[2];
          *(float *)((UINT_007f46a8 - 8) + uVar7 * 8) =
               (*(float *)local_10 - *pfVar5) * fVar3 + *pfVar5;
          *(float *)((UINT_007f46a8 - 4) + uVar7 * 8) =
               (*(float *)(local_10 + 4) - pfVar5[1]) * fVar3 + pfVar5[1];
          *(float *)((UINT_007f46b0 - 4) + uVar7 * 4) =
               (*(float *)local_14 - *(float *)local_c) * fVar3 + *(float *)local_c;
          UINT_007f4ac4 = UINT_007f4ac4 | 0x10;
          puVar12 = (uint *)UINT_007f46ac;
          iVar18 = iVar19;
        }
        if (fVar1 <= *pfVar15) {
          pfVar13 = (float *)((int)puVar12 + iVar18);
          uVar7 = uVar7 + 1;
          iVar18 = iVar18 + 0xc;
          *pfVar13 = *pfVar15;
          pfVar13[1] = pfVar15[1];
          pfVar13[2] = pfVar15[2];
          *(undefined4 *)((UINT_007f46a8 - 8) + uVar7 * 8) = *(undefined4 *)local_10;
          *(undefined4 *)((UINT_007f46a8 - 4) + uVar7 * 8) = *(undefined4 *)(local_10 + 4);
          *(undefined4 *)((UINT_007f46b0 - 4) + uVar7 * 4) = *(undefined4 *)local_14;
          puVar12 = (uint *)UINT_007f46ac;
        }
      }
      local_c = local_14;
      local_14 = local_14 + 4;
      param_5 = param_5 + -1;
      pfVar13 = pfVar15;
      pfVar15 = pfVar15 + 3;
      pfVar5 = (float *)local_10;
      local_10 = local_10 + 8;
    } while (param_5 != 0);
  }
  uVar4 = UINT_007f461c;
  uVar6 = UINT_007f4618;
  if (2 < (int)uVar7) {
    iVar18 = UINT_007f46a8 - 8;
    local_c = (UINT_007f46b0 - 4) + uVar7 * 4;
    uVar9 = 0;
    UINT_007f461c = UINT_007f46a8;
    UINT_007f4618 = UINT_007f46b0;
    local_10 = UINT_007f46a8;
    local_14 = UINT_007f46b0;
    uVar8 = UINT_007f47b8;
    UINT_007f46a8 = uVar4;
    UINT_007f46ac = UINT_007f47b8;
    UINT_007f46b0 = uVar6;
    pfVar13 = (float *)puVar12;
    if (0 < (int)uVar7) {
      iVar19 = 0;
      pfVar15 = (float *)(puVar12 + uVar7 * 3 + -3);
      pfVar5 = (float *)(iVar18 + uVar7 * 8);
      UINT_007f47b8 = (uint)puVar12;
      param_5 = uVar7;
      do {
        fVar2 = (float)param_1[5];
        fVar1 = (float)param_1[5];
        if ((*pfVar15 <= fVar2) || ((float)*puVar12 <= fVar1)) {
          if (((*pfVar15 != fVar2) && (fVar1 != (float)*puVar12)) &&
             ((fVar2 < *pfVar15 || (fVar1 < (float)*puVar12)))) {
            fVar3 = (fVar2 - *pfVar15) / ((float)*puVar12 - *pfVar15);
            iVar19 = iVar19 + 0xc;
            uVar9 = uVar9 + 1;
            *(float *)((uVar8 - 0xc) + iVar19) = fVar2;
            *(float *)((UINT_007f46ac - 8) + iVar19) =
                 ((float)puVar12[1] - pfVar15[1]) * fVar3 + pfVar15[1];
            *(float *)((UINT_007f46ac - 4) + iVar19) =
                 ((float)puVar12[2] - pfVar15[2]) * fVar3 + pfVar15[2];
            *(float *)((UINT_007f46a8 - 8) + uVar9 * 8) =
                 (*(float *)local_10 - *pfVar5) * fVar3 + *pfVar5;
            *(float *)((UINT_007f46a8 - 4) + uVar9 * 8) =
                 (*(float *)(local_10 + 4) - pfVar5[1]) * fVar3 + pfVar5[1];
            *(float *)((UINT_007f46b0 - 4) + uVar9 * 4) =
                 (*(float *)local_14 - *(float *)local_c) * fVar3 + *(float *)local_c;
            UINT_007f4ac4 = UINT_007f4ac4 | 0x20;
            uVar8 = UINT_007f46ac;
          }
          if ((float)*puVar12 <= fVar1) {
            pfVar13 = (float *)(uVar8 + iVar19);
            uVar9 = uVar9 + 1;
            iVar19 = iVar19 + 0xc;
            *pfVar13 = (float)*puVar12;
            pfVar13[1] = (float)puVar12[1];
            pfVar13[2] = (float)puVar12[2];
            *(undefined4 *)((UINT_007f46a8 - 8) + uVar9 * 8) = *(undefined4 *)local_10;
            *(undefined4 *)((UINT_007f46a8 - 4) + uVar9 * 8) = *(undefined4 *)(local_10 + 4);
            *(undefined4 *)((UINT_007f46b0 - 4) + uVar9 * 4) = *(undefined4 *)local_14;
            uVar8 = UINT_007f46ac;
          }
        }
        local_c = local_14;
        local_14 = local_14 + 4;
        param_5 = param_5 - 1;
        pfVar15 = (float *)puVar12;
        puVar12 = puVar12 + 3;
        pfVar5 = (float *)local_10;
        pfVar13 = (float *)UINT_007f47b8;
        local_10 = local_10 + 8;
      } while (param_5 != 0);
    }
    UINT_007f47b8 = (uint)pfVar13;
    uVar4 = UINT_007f461c;
    uVar6 = UINT_007f4618;
    if ((int)uVar9 < 3) {
      return uVar9;
    }
    pfVar13 = (float *)((uVar8 - 0xc) + uVar9 * 0xc);
    iVar18 = UINT_007f46a8 - 8;
    local_c = (UINT_007f46b0 - 4) + uVar9 * 4;
    uVar7 = 0;
    UINT_007f46ac = UINT_007f47b8;
    UINT_007f461c = UINT_007f46a8;
    UINT_007f4618 = UINT_007f46b0;
    local_10 = UINT_007f46a8;
    local_14 = UINT_007f46b0;
    uVar14 = UINT_007f47b8;
    UINT_007f46a8 = uVar4;
    UINT_007f46b0 = uVar6;
    if (0 < (int)uVar9) {
      iVar19 = 0;
      pfVar15 = (float *)(uVar8 + 8);
      pfVar5 = (float *)(iVar18 + uVar9 * 8);
      UINT_007f47b8 = uVar8;
      param_5 = uVar9;
      do {
        fVar2 = (float)param_1[4];
        fVar1 = (float)param_1[4];
        if ((pfVar13[2] <= fVar2) || (*pfVar15 <= fVar1)) {
          if (((pfVar13[2] != fVar2) && (fVar1 != *pfVar15)) &&
             ((fVar2 < pfVar13[2] || (fVar1 < *pfVar15)))) {
            fVar3 = (fVar2 - pfVar13[2]) / (*pfVar15 - pfVar13[2]);
            iVar19 = iVar19 + 0xc;
            uVar7 = uVar7 + 1;
            *(float *)((uVar14 - 0xc) + iVar19) = (pfVar15[-2] - *pfVar13) * fVar3 + *pfVar13;
            *(float *)((UINT_007f46ac - 8) + iVar19) =
                 (pfVar15[-1] - pfVar13[1]) * fVar3 + pfVar13[1];
            *(float *)((UINT_007f46ac - 4) + iVar19) = fVar2;
            *(float *)((UINT_007f46a8 - 8) + uVar7 * 8) =
                 (*(float *)local_10 - *pfVar5) * fVar3 + *pfVar5;
            *(float *)((UINT_007f46a8 - 4) + uVar7 * 8) =
                 (*(float *)(local_10 + 4) - pfVar5[1]) * fVar3 + pfVar5[1];
            *(float *)((UINT_007f46b0 - 4) + uVar7 * 4) =
                 (*(float *)local_14 - *(float *)local_c) * fVar3 + *(float *)local_c;
            UINT_007f4ac4 = UINT_007f4ac4 | 4;
            uVar14 = UINT_007f46ac;
          }
          if (*pfVar15 <= fVar1) {
            pfVar13 = (float *)(uVar14 + iVar19);
            uVar7 = uVar7 + 1;
            iVar19 = iVar19 + 0xc;
            *pfVar13 = pfVar15[-2];
            pfVar13[1] = pfVar15[-1];
            pfVar13[2] = *pfVar15;
            *(undefined4 *)((UINT_007f46a8 - 8) + uVar7 * 8) = *(undefined4 *)local_10;
            *(undefined4 *)((UINT_007f46a8 - 4) + uVar7 * 8) = *(undefined4 *)(local_10 + 4);
            *(undefined4 *)((UINT_007f46b0 - 4) + uVar7 * 4) = *(undefined4 *)local_14;
            uVar14 = UINT_007f46ac;
          }
        }
        pfVar13 = pfVar15 + -2;
        local_c = local_14;
        local_14 = local_14 + 4;
        pfVar15 = pfVar15 + 3;
        param_5 = param_5 - 1;
        pfVar5 = (float *)local_10;
        uVar8 = UINT_007f47b8;
        local_10 = local_10 + 8;
      } while (param_5 != 0);
    }
    UINT_007f47b8 = uVar8;
    uVar4 = UINT_007f461c;
    uVar6 = UINT_007f4618;
    if (2 < (int)uVar7) {
      UINT_007f46ac = UINT_007f47b8;
      uVar8 = 0;
      UINT_007f461c = UINT_007f46a8;
      UINT_007f4618 = UINT_007f46b0;
      local_10 = UINT_007f46a8;
      local_14 = UINT_007f46b0;
      pfVar13 = (float *)((uVar14 - 0xc) + uVar7 * 0xc);
      iVar18 = UINT_007f46a8 - 8;
      local_c = (UINT_007f46b0 - 4) + uVar7 * 4;
      uVar9 = UINT_007f47b8;
      UINT_007f46a8 = uVar4;
      UINT_007f46b0 = uVar6;
      if (0 < (int)uVar7) {
        iVar19 = 0;
        pfVar15 = (float *)(uVar14 + 8);
        pfVar5 = (float *)(iVar18 + uVar7 * 8);
        UINT_007f47b8 = uVar14;
        param_5 = uVar7;
        do {
          fVar2 = (float)param_1[6];
          fVar1 = (float)param_1[6];
          if ((fVar2 <= pfVar13[2]) || (fVar1 <= *pfVar15)) {
            if (((pfVar13[2] != fVar2) && (fVar1 != *pfVar15)) &&
               ((pfVar13[2] < fVar2 || (*pfVar15 < fVar1)))) {
              fVar3 = (fVar2 - pfVar13[2]) / (*pfVar15 - pfVar13[2]);
              iVar19 = iVar19 + 0xc;
              uVar8 = uVar8 + 1;
              *(float *)((uVar9 - 0xc) + iVar19) = (pfVar15[-2] - *pfVar13) * fVar3 + *pfVar13;
              *(float *)((UINT_007f46ac - 8) + iVar19) =
                   (pfVar15[-1] - pfVar13[1]) * fVar3 + pfVar13[1];
              *(float *)((UINT_007f46ac - 4) + iVar19) = fVar2;
              *(float *)((UINT_007f46a8 - 8) + uVar8 * 8) =
                   (*(float *)local_10 - *pfVar5) * fVar3 + *pfVar5;
              *(float *)((UINT_007f46a8 - 4) + uVar8 * 8) =
                   (*(float *)(local_10 + 4) - pfVar5[1]) * fVar3 + pfVar5[1];
              *(float *)((UINT_007f46b0 - 4) + uVar8 * 4) =
                   (*(float *)local_14 - *(float *)local_c) * fVar3 + *(float *)local_c;
              UINT_007f4ac4 = UINT_007f4ac4 | 8;
              uVar9 = UINT_007f46ac;
            }
            if (fVar1 <= *pfVar15) {
              pfVar13 = (float *)(uVar9 + iVar19);
              uVar8 = uVar8 + 1;
              iVar19 = iVar19 + 0xc;
              *pfVar13 = pfVar15[-2];
              pfVar13[1] = pfVar15[-1];
              pfVar13[2] = *pfVar15;
              *(undefined4 *)((UINT_007f46a8 - 8) + uVar8 * 8) = *(undefined4 *)local_10;
              *(undefined4 *)((UINT_007f46a8 - 4) + uVar8 * 8) = *(undefined4 *)(local_10 + 4);
              *(undefined4 *)((UINT_007f46b0 - 4) + uVar8 * 4) = *(undefined4 *)local_14;
              uVar9 = UINT_007f46ac;
            }
          }
          pfVar13 = pfVar15 + -2;
          local_c = local_14;
          local_14 = local_14 + 4;
          pfVar15 = pfVar15 + 3;
          param_5 = param_5 - 1;
          pfVar5 = (float *)local_10;
          uVar14 = UINT_007f47b8;
          local_10 = local_10 + 8;
        } while (param_5 != 0);
      }
      UINT_007f47b8 = uVar14;
      uVar7 = uVar8;
      uVar4 = UINT_007f461c;
      uVar6 = UINT_007f4618;
      if (2 < (int)uVar7) {
        UINT_007f46ac = UINT_007f47b8;
        uVar8 = 0;
        UINT_007f461c = UINT_007f46a8;
        UINT_007f4618 = UINT_007f46b0;
        local_10 = UINT_007f46a8;
        local_14 = UINT_007f46b0;
        pfVar13 = (float *)((uVar9 - 0xc) + uVar7 * 0xc);
        iVar18 = UINT_007f46a8 - 8;
        local_c = (UINT_007f46b0 - 4) + uVar7 * 4;
        pfVar15 = (float *)UINT_007f47b8;
        UINT_007f46a8 = uVar4;
        UINT_007f46b0 = uVar6;
        if (0 < (int)uVar7) {
          iVar19 = 0;
          pfVar5 = (float *)(uVar9 + 4);
          pfVar11 = (float *)(iVar18 + uVar7 * 8);
          UINT_007f47b8 = uVar9;
          param_5 = uVar7;
          do {
            if (((float)param_1[1] <= pfVar13[1]) || ((float)param_1[1] <= *pfVar5)) {
              if (((pfVar13[1] != (float)param_1[1]) && (*pfVar5 != (float)param_1[1])) &&
                 ((pfVar13[1] < (float)param_1[1] || (*pfVar5 < (float)param_1[1])))) {
                iVar18 = iVar19 + 0xc;
                uVar8 = uVar8 + 1;
                fVar1 = ((float)param_1[1] - pfVar13[1]) / (*pfVar5 - pfVar13[1]);
                *(int *)((int)pfVar15 + iVar19 + 4) = param_1[1];
                *(float *)((UINT_007f46ac - 4) + iVar18) =
                     (pfVar5[1] - pfVar13[2]) * fVar1 + pfVar13[2];
                *(float *)((UINT_007f46ac - 0xc) + iVar18) =
                     (pfVar5[-1] - *pfVar13) * fVar1 + *pfVar13;
                *(float *)((UINT_007f46a8 - 8) + uVar8 * 8) =
                     (*(float *)local_10 - *pfVar11) * fVar1 + *pfVar11;
                *(float *)((UINT_007f46a8 - 4) + uVar8 * 8) =
                     (*(float *)(local_10 + 4) - pfVar11[1]) * fVar1 + pfVar11[1];
                *(float *)((UINT_007f46b0 - 4) + uVar8 * 4) =
                     (*(float *)local_14 - *(float *)local_c) * fVar1 + *(float *)local_c;
                UINT_007f4ac4 = UINT_007f4ac4 | 1;
                pfVar15 = (float *)UINT_007f46ac;
                iVar19 = iVar18;
              }
              if ((float)param_1[1] <= *pfVar5) {
                pfVar15 = (float *)((int)pfVar15 + iVar19);
                uVar8 = uVar8 + 1;
                iVar19 = iVar19 + 0xc;
                *pfVar15 = pfVar5[-1];
                pfVar15[1] = *pfVar5;
                pfVar15[2] = pfVar5[1];
                *(undefined4 *)((UINT_007f46a8 - 8) + uVar8 * 8) = *(undefined4 *)local_10;
                *(undefined4 *)((UINT_007f46a8 - 4) + uVar8 * 8) = *(undefined4 *)(local_10 + 4);
                *(undefined4 *)((UINT_007f46b0 - 4) + uVar8 * 4) = *(undefined4 *)local_14;
                pfVar15 = (float *)UINT_007f46ac;
              }
            }
            pfVar13 = pfVar5 + -1;
            local_c = local_14;
            local_14 = local_14 + 4;
            pfVar5 = pfVar5 + 3;
            param_5 = param_5 - 1;
            pfVar11 = (float *)local_10;
            uVar9 = UINT_007f47b8;
            local_10 = local_10 + 8;
          } while (param_5 != 0);
        }
        UINT_007f47b8 = uVar9;
        uVar4 = UINT_007f461c;
        uVar6 = UINT_007f4618;
        if ((int)uVar8 < 3) {
          UINT_007f4ac4 = UINT_007f4ac4 | 0x40;
          return uVar8;
        }
        uVar7 = uVar8;
        pfVar13 = pfVar15;
        if (*param_1 != 0) {
          UINT_007f46ac = UINT_007f47b8;
          UINT_007f4618 = UINT_007f46b0;
          local_14 = UINT_007f46b0;
          uVar7 = 0;
          UINT_007f461c = UINT_007f46a8;
          local_10 = UINT_007f46a8;
          pfVar5 = pfVar15 + uVar8 * 3 + -3;
          iVar18 = UINT_007f46a8 - 8;
          local_c = (UINT_007f46b0 - 4) + uVar8 * 4;
          pfVar13 = (float *)UINT_007f47b8;
          UINT_007f46a8 = uVar4;
          UINT_007f46b0 = uVar6;
          if (0 < (int)uVar8) {
            iVar19 = 0;
            pfVar10 = pfVar15 + 1;
            pfVar11 = (float *)(iVar18 + uVar8 * 8);
            UINT_007f47b8 = (uint)pfVar15;
            param_5 = uVar8;
            do {
              if ((pfVar5[1] <= (float)param_1[2]) || (*pfVar10 <= (float)param_1[2])) {
                if (((pfVar5[1] != (float)param_1[2]) && (*pfVar10 != (float)param_1[2])) &&
                   (((float)param_1[2] < pfVar5[1] || ((float)param_1[2] < *pfVar10)))) {
                  iVar18 = iVar19 + 0xc;
                  uVar7 = uVar7 + 1;
                  fVar1 = ((float)param_1[2] - pfVar5[1]) / (*pfVar10 - pfVar5[1]);
                  *(int *)((int)pfVar13 + iVar19 + 4) = param_1[2];
                  *(float *)((UINT_007f46ac - 4) + iVar18) =
                       (pfVar10[1] - pfVar5[2]) * fVar1 + pfVar5[2];
                  *(float *)((UINT_007f46ac - 0xc) + iVar18) =
                       (pfVar10[-1] - *pfVar5) * fVar1 + *pfVar5;
                  *(float *)((UINT_007f46a8 - 8) + uVar7 * 8) =
                       (*(float *)local_10 - *pfVar11) * fVar1 + *pfVar11;
                  *(float *)((UINT_007f46a8 - 4) + uVar7 * 8) =
                       (*(float *)(local_10 + 4) - pfVar11[1]) * fVar1 + pfVar11[1];
                  *(float *)((UINT_007f46b0 - 4) + uVar7 * 4) =
                       (*(float *)local_14 - *(float *)local_c) * fVar1 + *(float *)local_c;
                  UINT_007f4ac4 = UINT_007f4ac4 | 2;
                  pfVar13 = (float *)UINT_007f46ac;
                  iVar19 = iVar18;
                }
                if (*pfVar10 <= (float)param_1[2]) {
                  pfVar13 = (float *)((int)pfVar13 + iVar19);
                  uVar7 = uVar7 + 1;
                  iVar19 = iVar19 + 0xc;
                  *pfVar13 = pfVar10[-1];
                  pfVar13[1] = *pfVar10;
                  pfVar13[2] = pfVar10[1];
                  *(undefined4 *)((UINT_007f46a8 - 8) + uVar7 * 8) = *(undefined4 *)local_10;
                  *(undefined4 *)((UINT_007f46a8 - 4) + uVar7 * 8) = *(undefined4 *)(local_10 + 4);
                  *(undefined4 *)((UINT_007f46b0 - 4) + uVar7 * 4) = *(undefined4 *)local_14;
                  pfVar13 = (float *)UINT_007f46ac;
                }
              }
              pfVar5 = pfVar10 + -1;
              local_c = local_14;
              local_14 = local_14 + 4;
              pfVar10 = pfVar10 + 3;
              param_5 = param_5 - 1;
              pfVar11 = (float *)local_10;
              pfVar15 = (float *)UINT_007f47b8;
              local_10 = local_10 + 8;
            } while (param_5 != 0);
          }
          UINT_007f47b8 = (uint)pfVar15;
          if ((int)uVar7 < 3) {
            return uVar7;
          }
        }
        if (pfVar13 != param_2) {
          for (uVar6 = uVar7 * 3 & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1) {
            *param_2 = *pfVar13;
            pfVar13 = pfVar13 + 1;
            param_2 = param_2 + 1;
          }
          for (iVar18 = 0; iVar18 != 0; iVar18 = iVar18 + -1) {
            *(undefined1 *)param_2 = *(undefined1 *)pfVar13;
            pfVar13 = (float *)((int)pfVar13 + 1);
            param_2 = (float *)((int)param_2 + 1);
          }
          puVar16 = (undefined4 *)UINT_007f46a8;
          for (iVar18 = (uVar7 & 0x1fffffff) << 1; iVar18 != 0; iVar18 = iVar18 + -1) {
            *param_3 = *puVar16;
            puVar16 = puVar16 + 1;
            param_3 = param_3 + 1;
          }
          for (iVar18 = 0; uVar6 = uVar7, puVar17 = (undefined4 *)UINT_007f46b0, iVar18 != 0;
              iVar18 = iVar18 + -1) {
            *(undefined1 *)param_3 = *(undefined1 *)puVar16;
            puVar16 = (undefined4 *)((int)puVar16 + 1);
            param_3 = (undefined4 *)((int)param_3 + 1);
          }
          for (; uVar6 != 0; uVar6 = uVar6 - 1) {
            *param_4 = *puVar17;
            puVar17 = puVar17 + 1;
            param_4 = param_4 + 1;
          }
        }
      }
    }
  }
  return uVar7;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c

