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
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  
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
      uVar4 = _ftol();
      uVar4 = ((code *)_ftol)(uVar4);
      uVar1 = ((code *)rdClip_Outcode2D)(param_1,uVar4);
    }
    else {
      uVar4 = _ftol();
      uVar4 = ((code *)_ftol)(uVar4);
      uVar2 = ((code *)rdClip_Outcode2D)(param_1,uVar4);
    }
    if ((uVar1 == 0) && (uVar2 == 0)) break;
    uVar3 = uVar1 & uVar2;
  }
  uVar4 = _ftol();
  *param_2 = uVar4;
  uVar4 = _ftol();
  *param_3 = uVar4;
  uVar4 = _ftol();
  *param_4 = uVar4;
  uVar4 = _ftol();
  *param_5 = uVar4;
  return 1;
}

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

int rdClip_Face3_Pos(int *param_1,float *param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  uint uVar8;
  float *pfVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  float *pfVar13;
  float *pfVar14;
  float *pfVar15;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar12 = 0;
  pfVar13 = (float *)&DAT_007f48c0;
  DAT_007f4ac4 = 0;
  DAT_007f47b8 = param_2;
  DAT_007f46ac = (float *)&DAT_007f48c0;
  if (0 < param_3) {
    iVar10 = 0;
    local_4 = param_3;
    pfVar14 = param_2 + param_3 * 3 + -3;
    pfVar15 = param_2;
    do {
      fVar2 = pfVar14[1] * (float)param_1[9];
      fVar3 = pfVar15[1] * (float)param_1[9];
      if ((fVar2 <= *pfVar14) || (fVar3 <= *pfVar15)) {
        iVar11 = iVar10;
        if (((*pfVar14 != fVar2) && (fVar3 != *pfVar15)) &&
           ((*pfVar14 < fVar2 || (*pfVar15 < fVar3)))) {
          fVar2 = pfVar15[1] - pfVar14[1];
          fVar4 = *pfVar15 - *pfVar14;
          fVar1 = (float)param_1[9] * fVar2 - fVar4;
          fVar5 = pfVar15[1] * *pfVar14 - pfVar14[1] * *pfVar15;
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
            fVar2 = ((float)param_1[9] * fVar5 - *pfVar14) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar14[1]) / fVar2;
          }
          *(float *)((int)pfVar13 + iVar10) = (float)param_1[9] * fVar5;
          iVar12 = iVar12 + 1;
          *(float *)((int)DAT_007f46ac + iVar10 + 4) = fVar5;
          iVar11 = iVar10 + 0xc;
          *(float *)((int)DAT_007f46ac + iVar10 + 8) =
               (pfVar15[2] - pfVar14[2]) * fVar2 + pfVar14[2];
          DAT_007f4ac4 = DAT_007f4ac4 | 0x10;
          pfVar13 = DAT_007f46ac;
        }
        iVar10 = iVar11;
        if (fVar3 <= *pfVar15) {
          pfVar13 = (float *)((int)pfVar13 + iVar11);
          iVar12 = iVar12 + 1;
          iVar10 = iVar11 + 0xc;
          *pfVar13 = *pfVar15;
          pfVar13[1] = pfVar15[1];
          pfVar13[2] = pfVar15[2];
          pfVar13 = DAT_007f46ac;
        }
      }
      local_4 = local_4 + -1;
      pfVar14 = pfVar15;
      pfVar15 = pfVar15 + 3;
    } while (local_4 != 0);
  }
  if (2 < iVar12) {
    iVar10 = 0;
    pfVar14 = DAT_007f47b8;
    DAT_007f46ac = DAT_007f47b8;
    if (0 < iVar12) {
      iVar11 = 0;
      pfVar15 = pfVar13 + iVar12 * 3 + -3;
      pfVar9 = pfVar13;
      DAT_007f47b8 = pfVar13;
      local_4 = iVar12;
      do {
        fVar2 = (float)param_1[10] * pfVar15[1];
        fVar3 = (float)param_1[10] * pfVar9[1];
        if ((*pfVar15 <= fVar2) || (*pfVar9 <= fVar3)) {
          iVar12 = iVar11;
          if (((*pfVar15 != fVar2) && (fVar3 != *pfVar9)) &&
             ((fVar2 < *pfVar15 || (fVar3 < *pfVar9)))) {
            fVar2 = pfVar9[1] - pfVar15[1];
            fVar4 = *pfVar9 - *pfVar15;
            fVar1 = (float)param_1[10] * fVar2 - fVar4;
            fVar5 = pfVar9[1] * *pfVar15 - pfVar15[1] * *pfVar9;
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
              fVar2 = ((float)param_1[10] * fVar5 - *pfVar15) / fVar4;
            }
            else {
              fVar2 = (fVar5 - pfVar15[1]) / fVar2;
            }
            *(float *)((int)pfVar14 + iVar11) = (float)param_1[10] * fVar5;
            iVar10 = iVar10 + 1;
            *(float *)((int)DAT_007f46ac + iVar11 + 4) = fVar5;
            iVar12 = iVar11 + 0xc;
            *(float *)((int)DAT_007f46ac + iVar11 + 8) =
                 (pfVar9[2] - pfVar15[2]) * fVar2 + pfVar15[2];
            DAT_007f4ac4 = DAT_007f4ac4 | 0x20;
            pfVar14 = DAT_007f46ac;
          }
          iVar11 = iVar12;
          if (*pfVar9 <= fVar3) {
            pfVar14 = (float *)((int)pfVar14 + iVar12);
            iVar10 = iVar10 + 1;
            iVar11 = iVar12 + 0xc;
            *pfVar14 = *pfVar9;
            pfVar14[1] = pfVar9[1];
            pfVar14[2] = pfVar9[2];
            pfVar14 = DAT_007f46ac;
          }
        }
        local_4 = local_4 + -1;
        pfVar15 = pfVar9;
        pfVar9 = pfVar9 + 3;
        pfVar13 = DAT_007f47b8;
      } while (local_4 != 0);
    }
    DAT_007f47b8 = pfVar13;
    iVar12 = iVar10;
    if (2 < iVar12) {
      iVar10 = 0;
      DAT_007f46ac = DAT_007f47b8;
      pfVar13 = pfVar14 + iVar12 * 3 + -3;
      pfVar15 = DAT_007f47b8;
      if (0 < iVar12) {
        iVar11 = 0;
        pfVar9 = pfVar14 + 2;
        DAT_007f47b8 = pfVar14;
        local_4 = iVar12;
        do {
          fVar2 = (float)param_1[7] * pfVar13[1];
          fVar3 = pfVar9[-1] * (float)param_1[7];
          if ((pfVar13[2] <= fVar2) || (*pfVar9 <= fVar3)) {
            iVar12 = iVar11;
            if (((pfVar13[2] != fVar2) && (fVar3 != *pfVar9)) &&
               ((fVar2 < pfVar13[2] || (fVar3 < *pfVar9)))) {
              fVar2 = pfVar9[-1] - pfVar13[1];
              fVar4 = *pfVar9 - pfVar13[2];
              fVar1 = (float)param_1[7] * fVar2 - fVar4;
              fVar5 = pfVar13[2] * pfVar9[-1] - pfVar13[1] * *pfVar9;
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
                fVar2 = (fVar1 * fVar5 - pfVar13[2]) / fVar4;
              }
              else {
                fVar2 = (fVar5 - pfVar13[1]) / fVar2;
              }
              iVar10 = iVar10 + 1;
              iVar12 = iVar11 + 0xc;
              *(float *)((int)pfVar15 + iVar11) = (pfVar9[-2] - *pfVar13) * fVar2 + *pfVar13;
              *(float *)((int)DAT_007f46ac + iVar11 + 4) = fVar5;
              *(float *)((int)DAT_007f46ac + iVar11 + 8) = fVar1 * fVar5;
              DAT_007f4ac4 = DAT_007f4ac4 | 4;
              pfVar15 = DAT_007f46ac;
            }
            iVar11 = iVar12;
            if (*pfVar9 <= fVar3) {
              pfVar15 = (float *)((int)pfVar15 + iVar12);
              iVar10 = iVar10 + 1;
              iVar11 = iVar12 + 0xc;
              *pfVar15 = pfVar9[-2];
              pfVar15[1] = pfVar9[-1];
              pfVar15[2] = *pfVar9;
              pfVar15 = DAT_007f46ac;
            }
          }
          pfVar13 = pfVar9 + -2;
          pfVar9 = pfVar9 + 3;
          local_4 = local_4 + -1;
          pfVar14 = DAT_007f47b8;
        } while (local_4 != 0);
      }
      DAT_007f47b8 = pfVar14;
      iVar12 = iVar10;
      if (2 < iVar12) {
        iVar10 = 0;
        DAT_007f46ac = DAT_007f47b8;
        pfVar13 = pfVar15 + iVar12 * 3 + -3;
        pfVar14 = DAT_007f47b8;
        if (0 < iVar12) {
          iVar11 = 0;
          pfVar9 = pfVar15 + 2;
          DAT_007f47b8 = pfVar15;
          local_4 = iVar12;
          do {
            fVar2 = (float)param_1[8] * pfVar13[1];
            fVar3 = pfVar9[-1] * (float)param_1[8];
            if ((fVar2 <= pfVar13[2]) || (fVar3 <= *pfVar9)) {
              iVar12 = iVar11;
              if (((pfVar13[2] != fVar2) && (fVar3 != *pfVar9)) &&
                 ((pfVar13[2] < fVar2 || (*pfVar9 < fVar3)))) {
                fVar2 = pfVar9[-1] - pfVar13[1];
                fVar4 = *pfVar9 - pfVar13[2];
                fVar1 = (float)param_1[8] * fVar2 - fVar4;
                fVar5 = pfVar13[2] * pfVar9[-1] - pfVar13[1] * *pfVar9;
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
                  fVar2 = (fVar1 * fVar5 - pfVar13[2]) / fVar4;
                }
                else {
                  fVar2 = (fVar5 - pfVar13[1]) / fVar2;
                }
                iVar10 = iVar10 + 1;
                iVar12 = iVar11 + 0xc;
                *(float *)((int)pfVar14 + iVar11) = (pfVar9[-2] - *pfVar13) * fVar2 + *pfVar13;
                *(float *)((int)DAT_007f46ac + iVar11 + 4) = fVar5;
                *(float *)((int)DAT_007f46ac + iVar11 + 8) = fVar1 * fVar5;
                DAT_007f4ac4 = DAT_007f4ac4 | 8;
                pfVar14 = DAT_007f46ac;
              }
              iVar11 = iVar12;
              if (fVar3 <= *pfVar9) {
                pfVar14 = (float *)((int)pfVar14 + iVar12);
                iVar10 = iVar10 + 1;
                iVar11 = iVar12 + 0xc;
                *pfVar14 = pfVar9[-2];
                pfVar14[1] = pfVar9[-1];
                pfVar14[2] = *pfVar9;
                pfVar14 = DAT_007f46ac;
              }
            }
            pfVar13 = pfVar9 + -2;
            pfVar9 = pfVar9 + 3;
            local_4 = local_4 + -1;
            pfVar15 = DAT_007f47b8;
          } while (local_4 != 0);
        }
        DAT_007f47b8 = pfVar15;
        iVar12 = iVar10;
        if (2 < iVar12) {
          iVar10 = 0;
          DAT_007f46ac = DAT_007f47b8;
          pfVar13 = pfVar14 + iVar12 * 3 + -3;
          pfVar15 = DAT_007f47b8;
          if (0 < iVar12) {
            pfVar9 = pfVar14 + 1;
            iVar11 = 0;
            DAT_007f47b8 = pfVar14;
            param_3 = iVar12;
            do {
              iVar12 = iVar11;
              if (((float)param_1[1] <= pfVar13[1]) || ((float)param_1[1] <= *pfVar9)) {
                if (((pfVar13[1] != (float)param_1[1]) && (*pfVar9 != (float)param_1[1])) &&
                   ((pfVar13[1] < (float)param_1[1] || (*pfVar9 < (float)param_1[1])))) {
                  iVar10 = iVar10 + 1;
                  fVar2 = ((float)param_1[1] - pfVar13[1]) / (*pfVar9 - pfVar13[1]);
                  *(int *)((int)pfVar15 + iVar11 + 4) = param_1[1];
                  iVar12 = iVar11 + 0xc;
                  *(float *)((int)DAT_007f46ac + iVar11 + 8) =
                       (pfVar9[1] - pfVar13[2]) * fVar2 + pfVar13[2];
                  *(float *)((int)DAT_007f46ac + iVar11) =
                       (pfVar9[-1] - *pfVar13) * fVar2 + *pfVar13;
                  DAT_007f4ac4 = DAT_007f4ac4 | 1;
                  pfVar15 = DAT_007f46ac;
                }
                if ((float)param_1[1] <= *pfVar9) {
                  pfVar15 = (float *)((int)pfVar15 + iVar12);
                  iVar10 = iVar10 + 1;
                  iVar12 = iVar12 + 0xc;
                  *pfVar15 = pfVar9[-1];
                  pfVar15[1] = *pfVar9;
                  pfVar15[2] = pfVar9[1];
                  pfVar15 = DAT_007f46ac;
                }
              }
              pfVar13 = pfVar9 + -1;
              pfVar9 = pfVar9 + 3;
              param_3 = param_3 + -1;
              iVar11 = iVar12;
              pfVar14 = DAT_007f47b8;
            } while (param_3 != 0);
          }
          DAT_007f47b8 = pfVar14;
          if (iVar10 < 3) {
            DAT_007f4ac4 = DAT_007f4ac4 | 0x40;
            return iVar10;
          }
          iVar12 = iVar10;
          pfVar13 = pfVar15;
          if (*param_1 != 0) {
            iVar12 = 0;
            pfVar14 = pfVar15 + iVar10 * 3 + -3;
            pfVar13 = DAT_007f47b8;
            DAT_007f46ac = DAT_007f47b8;
            if (0 < iVar10) {
              pfVar9 = pfVar15 + 1;
              iVar11 = 0;
              DAT_007f47b8 = pfVar15;
              param_3 = iVar10;
              do {
                iVar10 = iVar11;
                if ((pfVar14[1] <= (float)param_1[2]) || (*pfVar9 <= (float)param_1[2])) {
                  if (((pfVar14[1] != (float)param_1[2]) && (*pfVar9 != (float)param_1[2])) &&
                     (((float)param_1[2] < pfVar14[1] || ((float)param_1[2] < *pfVar9)))) {
                    iVar12 = iVar12 + 1;
                    fVar2 = ((float)param_1[2] - pfVar14[1]) / (*pfVar9 - pfVar14[1]);
                    *(int *)((int)pfVar13 + iVar11 + 4) = param_1[2];
                    iVar10 = iVar11 + 0xc;
                    *(float *)((int)DAT_007f46ac + iVar11 + 8) =
                         (pfVar9[1] - pfVar14[2]) * fVar2 + pfVar14[2];
                    *(float *)((int)DAT_007f46ac + iVar11) =
                         (pfVar9[-1] - *pfVar14) * fVar2 + *pfVar14;
                    DAT_007f4ac4 = DAT_007f4ac4 | 2;
                    pfVar13 = DAT_007f46ac;
                  }
                  if (*pfVar9 <= (float)param_1[2]) {
                    pfVar13 = (float *)((int)pfVar13 + iVar10);
                    iVar12 = iVar12 + 1;
                    iVar10 = iVar10 + 0xc;
                    *pfVar13 = pfVar9[-1];
                    pfVar13[1] = *pfVar9;
                    pfVar13[2] = pfVar9[1];
                    pfVar13 = DAT_007f46ac;
                  }
                }
                pfVar14 = pfVar9 + -1;
                pfVar9 = pfVar9 + 3;
                param_3 = param_3 + -1;
                iVar11 = iVar10;
                pfVar15 = DAT_007f47b8;
              } while (param_3 != 0);
            }
            DAT_007f47b8 = pfVar15;
            if (iVar12 < 3) {
              return iVar12;
            }
          }
          if (pfVar13 != param_2) {
            for (uVar8 = iVar12 * 3 & 0x3fffffff; uVar8 != 0; uVar8 = uVar8 - 1) {
              *param_2 = *pfVar13;
              pfVar13 = pfVar13 + 1;
              param_2 = param_2 + 1;
            }
            for (iVar10 = 0; iVar10 != 0; iVar10 = iVar10 + -1) {
              *(undefined1 *)param_2 = *(undefined1 *)pfVar13;
              pfVar13 = (float *)((int)pfVar13 + 1);
              param_2 = (float *)((int)param_2 + 1);
            }
          }
        }
      }
    }
  }
  return iVar12;
}
#undef local_4


/* ---- 0x00448260  rdClip_Face3_PosB ---- */
/* Second position-only face clipper (likely the orthographic variant) */

int rdClip_Face3_PosB(int *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  
  iVar6 = 0;
  pfVar9 = (float *)&DAT_007f48c0;
  iVar8 = 0;
  DAT_007f4ac4 = 0;
  DAT_007f47b8 = param_2;
  DAT_007f46ac = (float *)&DAT_007f48c0;
  pfVar10 = param_2 + param_3 * 3 + -3;
  pfVar11 = param_2;
  if (0 < param_3) {
    do {
      fVar2 = (float)param_1[3];
      fVar1 = (float)param_1[3];
      if ((fVar2 <= *pfVar10) || (fVar1 <= *pfVar11)) {
        iVar7 = iVar6;
        if (((*pfVar10 != fVar2) && (fVar1 != *pfVar11)) &&
           ((*pfVar10 < fVar2 || (*pfVar11 < fVar1)))) {
          fVar3 = (fVar2 - *pfVar10) / (*pfVar11 - *pfVar10);
          iVar8 = iVar8 + 1;
          iVar7 = iVar6 + 0xc;
          *(float *)((int)pfVar9 + iVar6) = fVar2;
          *(float *)((int)DAT_007f46ac + iVar6 + 4) = (pfVar11[1] - pfVar10[1]) * fVar3 + pfVar10[1]
          ;
          *(float *)((int)DAT_007f46ac + iVar6 + 8) = (pfVar11[2] - pfVar10[2]) * fVar3 + pfVar10[2]
          ;
          DAT_007f4ac4 = DAT_007f4ac4 | 0x10;
          pfVar9 = DAT_007f46ac;
        }
        iVar6 = iVar7;
        if (fVar1 <= *pfVar11) {
          pfVar9 = (float *)((int)pfVar9 + iVar7);
          iVar8 = iVar8 + 1;
          iVar6 = iVar7 + 0xc;
          *pfVar9 = *pfVar11;
          pfVar9[1] = pfVar11[1];
          pfVar9[2] = pfVar11[2];
          pfVar9 = DAT_007f46ac;
        }
      }
      param_3 = param_3 + -1;
      pfVar10 = pfVar11;
      pfVar11 = pfVar11 + 3;
    } while (param_3 != 0);
  }
  if (2 < iVar8) {
    iVar6 = 0;
    pfVar10 = DAT_007f47b8;
    DAT_007f46ac = DAT_007f47b8;
    if (0 < iVar8) {
      iVar7 = 0;
      pfVar11 = pfVar9 + iVar8 * 3 + -3;
      pfVar5 = pfVar9;
      DAT_007f47b8 = pfVar9;
      param_3 = iVar8;
      do {
        fVar2 = (float)param_1[5];
        fVar1 = (float)param_1[5];
        if ((*pfVar11 <= fVar2) || (*pfVar5 <= fVar1)) {
          iVar8 = iVar7;
          if (((*pfVar11 != fVar2) && (fVar1 != *pfVar5)) &&
             ((fVar2 < *pfVar11 || (fVar1 < *pfVar5)))) {
            fVar3 = (fVar2 - *pfVar11) / (*pfVar5 - *pfVar11);
            iVar6 = iVar6 + 1;
            iVar8 = iVar7 + 0xc;
            *(float *)((int)pfVar10 + iVar7) = fVar2;
            *(float *)((int)DAT_007f46ac + iVar7 + 4) =
                 (pfVar5[1] - pfVar11[1]) * fVar3 + pfVar11[1];
            *(float *)((int)DAT_007f46ac + iVar7 + 8) =
                 (pfVar5[2] - pfVar11[2]) * fVar3 + pfVar11[2];
            DAT_007f4ac4 = DAT_007f4ac4 | 0x20;
            pfVar10 = DAT_007f46ac;
          }
          iVar7 = iVar8;
          if (*pfVar5 <= fVar1) {
            pfVar10 = (float *)((int)pfVar10 + iVar8);
            iVar6 = iVar6 + 1;
            iVar7 = iVar8 + 0xc;
            *pfVar10 = *pfVar5;
            pfVar10[1] = pfVar5[1];
            pfVar10[2] = pfVar5[2];
            pfVar10 = DAT_007f46ac;
          }
        }
        param_3 = param_3 + -1;
        pfVar11 = pfVar5;
        pfVar5 = pfVar5 + 3;
        pfVar9 = DAT_007f47b8;
      } while (param_3 != 0);
    }
    DAT_007f47b8 = pfVar9;
    iVar8 = iVar6;
    if (2 < iVar8) {
      iVar6 = 0;
      pfVar11 = pfVar10 + iVar8 * 3 + -3;
      pfVar9 = DAT_007f47b8;
      DAT_007f46ac = DAT_007f47b8;
      if (0 < iVar8) {
        pfVar5 = pfVar10 + 2;
        iVar7 = 0;
        DAT_007f47b8 = pfVar10;
        param_3 = iVar8;
        do {
          fVar2 = (float)param_1[4];
          fVar1 = (float)param_1[4];
          if ((pfVar11[2] <= fVar2) || (*pfVar5 <= fVar1)) {
            iVar8 = iVar7;
            if (((pfVar11[2] != fVar2) && (fVar1 != *pfVar5)) &&
               ((fVar2 < pfVar11[2] || (fVar1 < *pfVar5)))) {
              fVar3 = (fVar2 - pfVar11[2]) / (*pfVar5 - pfVar11[2]);
              iVar6 = iVar6 + 1;
              iVar8 = iVar7 + 0xc;
              *(float *)((int)pfVar9 + iVar7) = (pfVar5[-2] - *pfVar11) * fVar3 + *pfVar11;
              *(float *)((int)DAT_007f46ac + iVar7 + 4) =
                   (pfVar5[-1] - pfVar11[1]) * fVar3 + pfVar11[1];
              *(float *)((int)DAT_007f46ac + iVar7 + 8) = fVar2;
              DAT_007f4ac4 = DAT_007f4ac4 | 4;
              pfVar9 = DAT_007f46ac;
            }
            iVar7 = iVar8;
            if (*pfVar5 <= fVar1) {
              pfVar9 = (float *)((int)pfVar9 + iVar8);
              iVar6 = iVar6 + 1;
              iVar7 = iVar8 + 0xc;
              *pfVar9 = pfVar5[-2];
              pfVar9[1] = pfVar5[-1];
              pfVar9[2] = *pfVar5;
              pfVar9 = DAT_007f46ac;
            }
          }
          pfVar11 = pfVar5 + -2;
          pfVar5 = pfVar5 + 3;
          param_3 = param_3 + -1;
          pfVar10 = DAT_007f47b8;
        } while (param_3 != 0);
      }
      DAT_007f47b8 = pfVar10;
      iVar8 = iVar6;
      if (2 < iVar8) {
        iVar6 = 0;
        pfVar10 = pfVar9 + iVar8 * 3 + -3;
        pfVar11 = DAT_007f47b8;
        DAT_007f46ac = DAT_007f47b8;
        if (0 < iVar8) {
          pfVar5 = pfVar9 + 2;
          iVar7 = 0;
          DAT_007f47b8 = pfVar9;
          param_3 = iVar8;
          do {
            fVar2 = (float)param_1[6];
            fVar1 = (float)param_1[6];
            if ((fVar2 <= pfVar10[2]) || (fVar1 <= *pfVar5)) {
              iVar8 = iVar7;
              if (((pfVar10[2] != fVar2) && (fVar1 != *pfVar5)) &&
                 ((pfVar10[2] < fVar2 || (*pfVar5 < fVar1)))) {
                fVar3 = (fVar2 - pfVar10[2]) / (*pfVar5 - pfVar10[2]);
                iVar6 = iVar6 + 1;
                iVar8 = iVar7 + 0xc;
                *(float *)((int)pfVar11 + iVar7) = (pfVar5[-2] - *pfVar10) * fVar3 + *pfVar10;
                *(float *)((int)DAT_007f46ac + iVar7 + 4) =
                     (pfVar5[-1] - pfVar10[1]) * fVar3 + pfVar10[1];
                *(float *)((int)DAT_007f46ac + iVar7 + 8) = fVar2;
                DAT_007f4ac4 = DAT_007f4ac4 | 8;
                pfVar11 = DAT_007f46ac;
              }
              iVar7 = iVar8;
              if (fVar1 <= *pfVar5) {
                pfVar11 = (float *)((int)pfVar11 + iVar8);
                iVar6 = iVar6 + 1;
                iVar7 = iVar8 + 0xc;
                *pfVar11 = pfVar5[-2];
                pfVar11[1] = pfVar5[-1];
                pfVar11[2] = *pfVar5;
                pfVar11 = DAT_007f46ac;
              }
            }
            pfVar10 = pfVar5 + -2;
            pfVar5 = pfVar5 + 3;
            param_3 = param_3 + -1;
            pfVar9 = DAT_007f47b8;
          } while (param_3 != 0);
        }
        DAT_007f47b8 = pfVar9;
        iVar8 = iVar6;
        if (2 < iVar8) {
          iVar6 = 0;
          pfVar10 = pfVar11 + iVar8 * 3 + -3;
          pfVar9 = DAT_007f47b8;
          DAT_007f46ac = DAT_007f47b8;
          if (0 < iVar8) {
            pfVar5 = pfVar11 + 1;
            iVar7 = 0;
            DAT_007f47b8 = pfVar11;
            param_3 = iVar8;
            do {
              iVar8 = iVar7;
              if (((float)param_1[1] <= pfVar10[1]) || ((float)param_1[1] <= *pfVar5)) {
                if (((pfVar10[1] != (float)param_1[1]) && (*pfVar5 != (float)param_1[1])) &&
                   ((pfVar10[1] < (float)param_1[1] || (*pfVar5 < (float)param_1[1])))) {
                  iVar6 = iVar6 + 1;
                  fVar1 = ((float)param_1[1] - pfVar10[1]) / (*pfVar5 - pfVar10[1]);
                  *(int *)((int)pfVar9 + iVar7 + 4) = param_1[1];
                  iVar8 = iVar7 + 0xc;
                  *(float *)((int)DAT_007f46ac + iVar7 + 8) =
                       (pfVar5[1] - pfVar10[2]) * fVar1 + pfVar10[2];
                  *(float *)((int)DAT_007f46ac + iVar7) = (pfVar5[-1] - *pfVar10) * fVar1 + *pfVar10
                  ;
                  DAT_007f4ac4 = DAT_007f4ac4 | 1;
                  pfVar9 = DAT_007f46ac;
                }
                if ((float)param_1[1] <= *pfVar5) {
                  pfVar9 = (float *)((int)pfVar9 + iVar8);
                  iVar6 = iVar6 + 1;
                  iVar8 = iVar8 + 0xc;
                  *pfVar9 = pfVar5[-1];
                  pfVar9[1] = *pfVar5;
                  pfVar9[2] = pfVar5[1];
                  pfVar9 = DAT_007f46ac;
                }
              }
              pfVar10 = pfVar5 + -1;
              pfVar5 = pfVar5 + 3;
              param_3 = param_3 + -1;
              iVar7 = iVar8;
              pfVar11 = DAT_007f47b8;
            } while (param_3 != 0);
          }
          DAT_007f47b8 = pfVar11;
          if (iVar6 < 3) {
            DAT_007f4ac4 = DAT_007f4ac4 | 0x40;
            return iVar6;
          }
          iVar8 = iVar6;
          pfVar10 = pfVar9;
          if (*param_1 != 0) {
            iVar8 = 0;
            pfVar11 = pfVar9 + iVar6 * 3 + -3;
            pfVar10 = DAT_007f47b8;
            DAT_007f46ac = DAT_007f47b8;
            if (0 < iVar6) {
              pfVar5 = pfVar9 + 1;
              iVar7 = 0;
              DAT_007f47b8 = pfVar9;
              param_3 = iVar6;
              do {
                iVar6 = iVar7;
                if ((pfVar11[1] <= (float)param_1[2]) || (*pfVar5 <= (float)param_1[2])) {
                  if (((pfVar11[1] != (float)param_1[2]) && (*pfVar5 != (float)param_1[2])) &&
                     (((float)param_1[2] < pfVar11[1] || ((float)param_1[2] < *pfVar5)))) {
                    iVar8 = iVar8 + 1;
                    fVar1 = ((float)param_1[2] - pfVar11[1]) / (*pfVar5 - pfVar11[1]);
                    *(int *)((int)pfVar10 + iVar7 + 4) = param_1[2];
                    iVar6 = iVar7 + 0xc;
                    *(float *)((int)DAT_007f46ac + iVar7 + 8) =
                         (pfVar5[1] - pfVar11[2]) * fVar1 + pfVar11[2];
                    *(float *)((int)DAT_007f46ac + iVar7) =
                         (pfVar5[-1] - *pfVar11) * fVar1 + *pfVar11;
                    DAT_007f4ac4 = DAT_007f4ac4 | 2;
                    pfVar10 = DAT_007f46ac;
                  }
                  if (*pfVar5 <= (float)param_1[2]) {
                    pfVar10 = (float *)((int)pfVar10 + iVar6);
                    iVar8 = iVar8 + 1;
                    iVar6 = iVar6 + 0xc;
                    *pfVar10 = pfVar5[-1];
                    pfVar10[1] = *pfVar5;
                    pfVar10[2] = pfVar5[1];
                    pfVar10 = DAT_007f46ac;
                  }
                }
                pfVar11 = pfVar5 + -1;
                pfVar5 = pfVar5 + 3;
                param_3 = param_3 + -1;
                iVar7 = iVar6;
                pfVar9 = DAT_007f47b8;
              } while (param_3 != 0);
            }
            DAT_007f47b8 = pfVar9;
            if (iVar8 < 3) {
              return iVar8;
            }
          }
          if (pfVar10 != param_2) {
            for (uVar4 = iVar8 * 3 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
              *param_2 = *pfVar10;
              pfVar10 = pfVar10 + 1;
              param_2 = param_2 + 1;
            }
            for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
              *(undefined1 *)param_2 = *(undefined1 *)pfVar10;
              pfVar10 = (float *)((int)pfVar10 + 1);
              param_2 = (float *)((int)param_2 + 1);
            }
          }
        }
      }
    }
  }
  return iVar8;
}

/* ---- 0x004489b0  rdClip_Face3_Pos_2 ---- */
int rdClip_Face3_Pos_2(int *param_1,float *param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  uint uVar8;
  float *pfVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  float *pfVar13;
  float *pfVar14;
  float *pfVar15;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar12 = 0;
  pfVar13 = (float *)&DAT_007f48c0;
  DAT_007f4ac4 = 0;
  DAT_007f47b8 = param_2;
  DAT_007f46ac = (float *)&DAT_007f48c0;
  if (0 < param_3) {
    iVar10 = 0;
    local_4 = param_3;
    pfVar14 = param_2 + param_3 * 3 + -3;
    pfVar15 = param_2;
    do {
      fVar2 = pfVar14[1] * (float)param_1[0xc];
      fVar3 = pfVar15[1] * (float)param_1[0xc];
      if ((fVar2 <= *pfVar14) || (fVar3 <= *pfVar15)) {
        iVar11 = iVar10;
        if (((*pfVar14 != fVar2) && (fVar3 != *pfVar15)) &&
           ((*pfVar14 < fVar2 || (*pfVar15 < fVar3)))) {
          fVar2 = pfVar15[1] - pfVar14[1];
          fVar4 = *pfVar15 - *pfVar14;
          fVar1 = (float)param_1[0xc] * fVar2 - fVar4;
          fVar5 = pfVar15[1] * *pfVar14 - pfVar14[1] * *pfVar15;
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
            fVar2 = ((float)param_1[0xc] * fVar5 - *pfVar14) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar14[1]) / fVar2;
          }
          *(float *)((int)pfVar13 + iVar10) = (float)param_1[0xc] * fVar5;
          iVar12 = iVar12 + 1;
          *(float *)((int)DAT_007f46ac + iVar10 + 4) = fVar5;
          iVar11 = iVar10 + 0xc;
          *(float *)((int)DAT_007f46ac + iVar10 + 8) =
               (pfVar15[2] - pfVar14[2]) * fVar2 + pfVar14[2];
          DAT_007f4ac4 = DAT_007f4ac4 | 0x10;
          pfVar13 = DAT_007f46ac;
        }
        iVar10 = iVar11;
        if (fVar3 <= *pfVar15) {
          pfVar13 = (float *)((int)pfVar13 + iVar11);
          iVar12 = iVar12 + 1;
          iVar10 = iVar11 + 0xc;
          *pfVar13 = *pfVar15;
          pfVar13[1] = pfVar15[1];
          pfVar13[2] = pfVar15[2];
          pfVar13 = DAT_007f46ac;
        }
      }
      local_4 = local_4 + -1;
      pfVar14 = pfVar15;
      pfVar15 = pfVar15 + 3;
    } while (local_4 != 0);
  }
  if (2 < iVar12) {
    iVar10 = 0;
    pfVar14 = DAT_007f47b8;
    DAT_007f46ac = DAT_007f47b8;
    if (0 < iVar12) {
      iVar11 = 0;
      pfVar15 = pfVar13 + iVar12 * 3 + -3;
      pfVar9 = pfVar13;
      DAT_007f47b8 = pfVar13;
      local_4 = iVar12;
      do {
        fVar2 = (float)param_1[10] * pfVar15[1];
        fVar3 = (float)param_1[10] * pfVar9[1];
        if ((*pfVar15 <= fVar2) || (*pfVar9 <= fVar3)) {
          iVar12 = iVar11;
          if (((*pfVar15 != fVar2) && (fVar3 != *pfVar9)) &&
             ((fVar2 < *pfVar15 || (fVar3 < *pfVar9)))) {
            fVar2 = pfVar9[1] - pfVar15[1];
            fVar4 = *pfVar9 - *pfVar15;
            fVar1 = (float)param_1[10] * fVar2 - fVar4;
            fVar5 = pfVar9[1] * *pfVar15 - pfVar15[1] * *pfVar9;
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
              fVar2 = ((float)param_1[10] * fVar5 - *pfVar15) / fVar4;
            }
            else {
              fVar2 = (fVar5 - pfVar15[1]) / fVar2;
            }
            *(float *)((int)pfVar14 + iVar11) = (float)param_1[10] * fVar5;
            iVar10 = iVar10 + 1;
            *(float *)((int)DAT_007f46ac + iVar11 + 4) = fVar5;
            iVar12 = iVar11 + 0xc;
            *(float *)((int)DAT_007f46ac + iVar11 + 8) =
                 (pfVar9[2] - pfVar15[2]) * fVar2 + pfVar15[2];
            DAT_007f4ac4 = DAT_007f4ac4 | 0x20;
            pfVar14 = DAT_007f46ac;
          }
          iVar11 = iVar12;
          if (*pfVar9 <= fVar3) {
            pfVar14 = (float *)((int)pfVar14 + iVar12);
            iVar10 = iVar10 + 1;
            iVar11 = iVar12 + 0xc;
            *pfVar14 = *pfVar9;
            pfVar14[1] = pfVar9[1];
            pfVar14[2] = pfVar9[2];
            pfVar14 = DAT_007f46ac;
          }
        }
        local_4 = local_4 + -1;
        pfVar15 = pfVar9;
        pfVar9 = pfVar9 + 3;
        pfVar13 = DAT_007f47b8;
      } while (local_4 != 0);
    }
    DAT_007f47b8 = pfVar13;
    iVar12 = iVar10;
    if (2 < iVar12) {
      iVar10 = 0;
      DAT_007f46ac = DAT_007f47b8;
      pfVar13 = pfVar14 + iVar12 * 3 + -3;
      pfVar15 = DAT_007f47b8;
      if (0 < iVar12) {
        iVar11 = 0;
        pfVar9 = pfVar14 + 2;
        DAT_007f47b8 = pfVar14;
        local_4 = iVar12;
        do {
          fVar2 = (float)param_1[0xb] * pfVar13[1];
          fVar3 = pfVar9[-1] * (float)param_1[0xb];
          if ((pfVar13[2] <= fVar2) || (*pfVar9 <= fVar3)) {
            iVar12 = iVar11;
            if (((pfVar13[2] != fVar2) && (fVar3 != *pfVar9)) &&
               ((fVar2 < pfVar13[2] || (fVar3 < *pfVar9)))) {
              fVar2 = pfVar9[-1] - pfVar13[1];
              fVar4 = *pfVar9 - pfVar13[2];
              fVar1 = (float)param_1[0xb] * fVar2 - fVar4;
              fVar5 = pfVar13[2] * pfVar9[-1] - pfVar13[1] * *pfVar9;
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
                fVar2 = (fVar1 * fVar5 - pfVar13[2]) / fVar4;
              }
              else {
                fVar2 = (fVar5 - pfVar13[1]) / fVar2;
              }
              iVar10 = iVar10 + 1;
              iVar12 = iVar11 + 0xc;
              *(float *)((int)pfVar15 + iVar11) = (pfVar9[-2] - *pfVar13) * fVar2 + *pfVar13;
              *(float *)((int)DAT_007f46ac + iVar11 + 4) = fVar5;
              *(float *)((int)DAT_007f46ac + iVar11 + 8) = fVar1 * fVar5;
              DAT_007f4ac4 = DAT_007f4ac4 | 4;
              pfVar15 = DAT_007f46ac;
            }
            iVar11 = iVar12;
            if (*pfVar9 <= fVar3) {
              pfVar15 = (float *)((int)pfVar15 + iVar12);
              iVar10 = iVar10 + 1;
              iVar11 = iVar12 + 0xc;
              *pfVar15 = pfVar9[-2];
              pfVar15[1] = pfVar9[-1];
              pfVar15[2] = *pfVar9;
              pfVar15 = DAT_007f46ac;
            }
          }
          pfVar13 = pfVar9 + -2;
          pfVar9 = pfVar9 + 3;
          local_4 = local_4 + -1;
          pfVar14 = DAT_007f47b8;
        } while (local_4 != 0);
      }
      DAT_007f47b8 = pfVar14;
      iVar12 = iVar10;
      if (2 < iVar12) {
        iVar10 = 0;
        DAT_007f46ac = DAT_007f47b8;
        pfVar13 = pfVar15 + iVar12 * 3 + -3;
        pfVar14 = DAT_007f47b8;
        if (0 < iVar12) {
          iVar11 = 0;
          pfVar9 = pfVar15 + 2;
          DAT_007f47b8 = pfVar15;
          local_4 = iVar12;
          do {
            fVar2 = (float)param_1[8] * pfVar13[1];
            fVar3 = pfVar9[-1] * (float)param_1[8];
            if ((fVar2 <= pfVar13[2]) || (fVar3 <= *pfVar9)) {
              iVar12 = iVar11;
              if (((pfVar13[2] != fVar2) && (fVar3 != *pfVar9)) &&
                 ((pfVar13[2] < fVar2 || (*pfVar9 < fVar3)))) {
                fVar2 = pfVar9[-1] - pfVar13[1];
                fVar4 = *pfVar9 - pfVar13[2];
                fVar1 = (float)param_1[8] * fVar2 - fVar4;
                fVar5 = pfVar13[2] * pfVar9[-1] - pfVar13[1] * *pfVar9;
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
                  fVar2 = (fVar1 * fVar5 - pfVar13[2]) / fVar4;
                }
                else {
                  fVar2 = (fVar5 - pfVar13[1]) / fVar2;
                }
                iVar10 = iVar10 + 1;
                iVar12 = iVar11 + 0xc;
                *(float *)((int)pfVar14 + iVar11) = (pfVar9[-2] - *pfVar13) * fVar2 + *pfVar13;
                *(float *)((int)DAT_007f46ac + iVar11 + 4) = fVar5;
                *(float *)((int)DAT_007f46ac + iVar11 + 8) = fVar1 * fVar5;
                DAT_007f4ac4 = DAT_007f4ac4 | 8;
                pfVar14 = DAT_007f46ac;
              }
              iVar11 = iVar12;
              if (fVar3 <= *pfVar9) {
                pfVar14 = (float *)((int)pfVar14 + iVar12);
                iVar10 = iVar10 + 1;
                iVar11 = iVar12 + 0xc;
                *pfVar14 = pfVar9[-2];
                pfVar14[1] = pfVar9[-1];
                pfVar14[2] = *pfVar9;
                pfVar14 = DAT_007f46ac;
              }
            }
            pfVar13 = pfVar9 + -2;
            pfVar9 = pfVar9 + 3;
            local_4 = local_4 + -1;
            pfVar15 = DAT_007f47b8;
          } while (local_4 != 0);
        }
        DAT_007f47b8 = pfVar15;
        iVar12 = iVar10;
        if (2 < iVar12) {
          iVar10 = 0;
          DAT_007f46ac = DAT_007f47b8;
          pfVar13 = pfVar14 + iVar12 * 3 + -3;
          pfVar15 = DAT_007f47b8;
          if (0 < iVar12) {
            pfVar9 = pfVar14 + 1;
            iVar11 = 0;
            DAT_007f47b8 = pfVar14;
            param_3 = iVar12;
            do {
              iVar12 = iVar11;
              if (((float)param_1[1] <= pfVar13[1]) || ((float)param_1[1] <= *pfVar9)) {
                if (((pfVar13[1] != (float)param_1[1]) && (*pfVar9 != (float)param_1[1])) &&
                   ((pfVar13[1] < (float)param_1[1] || (*pfVar9 < (float)param_1[1])))) {
                  iVar10 = iVar10 + 1;
                  fVar2 = ((float)param_1[1] - pfVar13[1]) / (*pfVar9 - pfVar13[1]);
                  *(int *)((int)pfVar15 + iVar11 + 4) = param_1[1];
                  iVar12 = iVar11 + 0xc;
                  *(float *)((int)DAT_007f46ac + iVar11 + 8) =
                       (pfVar9[1] - pfVar13[2]) * fVar2 + pfVar13[2];
                  *(float *)((int)DAT_007f46ac + iVar11) =
                       (pfVar9[-1] - *pfVar13) * fVar2 + *pfVar13;
                  DAT_007f4ac4 = DAT_007f4ac4 | 1;
                  pfVar15 = DAT_007f46ac;
                }
                if ((float)param_1[1] <= *pfVar9) {
                  pfVar15 = (float *)((int)pfVar15 + iVar12);
                  iVar10 = iVar10 + 1;
                  iVar12 = iVar12 + 0xc;
                  *pfVar15 = pfVar9[-1];
                  pfVar15[1] = *pfVar9;
                  pfVar15[2] = pfVar9[1];
                  pfVar15 = DAT_007f46ac;
                }
              }
              pfVar13 = pfVar9 + -1;
              pfVar9 = pfVar9 + 3;
              param_3 = param_3 + -1;
              iVar11 = iVar12;
              pfVar14 = DAT_007f47b8;
            } while (param_3 != 0);
          }
          DAT_007f47b8 = pfVar14;
          if (iVar10 < 3) {
            DAT_007f4ac4 = DAT_007f4ac4 | 0x40;
            return iVar10;
          }
          iVar12 = iVar10;
          pfVar13 = pfVar15;
          if (*param_1 != 0) {
            iVar12 = 0;
            pfVar14 = pfVar15 + iVar10 * 3 + -3;
            pfVar13 = DAT_007f47b8;
            DAT_007f46ac = DAT_007f47b8;
            if (0 < iVar10) {
              pfVar9 = pfVar15 + 1;
              iVar11 = 0;
              DAT_007f47b8 = pfVar15;
              param_3 = iVar10;
              do {
                iVar10 = iVar11;
                if ((pfVar14[1] <= (float)param_1[2]) || (*pfVar9 <= (float)param_1[2])) {
                  if (((pfVar14[1] != (float)param_1[2]) && (*pfVar9 != (float)param_1[2])) &&
                     (((float)param_1[2] < pfVar14[1] || ((float)param_1[2] < *pfVar9)))) {
                    iVar12 = iVar12 + 1;
                    fVar2 = ((float)param_1[2] - pfVar14[1]) / (*pfVar9 - pfVar14[1]);
                    *(int *)((int)pfVar13 + iVar11 + 4) = param_1[2];
                    iVar10 = iVar11 + 0xc;
                    *(float *)((int)DAT_007f46ac + iVar11 + 8) =
                         (pfVar9[1] - pfVar14[2]) * fVar2 + pfVar14[2];
                    *(float *)((int)DAT_007f46ac + iVar11) =
                         (pfVar9[-1] - *pfVar14) * fVar2 + *pfVar14;
                    DAT_007f4ac4 = DAT_007f4ac4 | 2;
                    pfVar13 = DAT_007f46ac;
                  }
                  if (*pfVar9 <= (float)param_1[2]) {
                    pfVar13 = (float *)((int)pfVar13 + iVar10);
                    iVar12 = iVar12 + 1;
                    iVar10 = iVar10 + 0xc;
                    *pfVar13 = pfVar9[-1];
                    pfVar13[1] = *pfVar9;
                    pfVar13[2] = pfVar9[1];
                    pfVar13 = DAT_007f46ac;
                  }
                }
                pfVar14 = pfVar9 + -1;
                pfVar9 = pfVar9 + 3;
                param_3 = param_3 + -1;
                iVar11 = iVar10;
                pfVar15 = DAT_007f47b8;
              } while (param_3 != 0);
            }
            DAT_007f47b8 = pfVar15;
            if (iVar12 < 3) {
              return iVar12;
            }
          }
          if (pfVar13 != param_2) {
            for (uVar8 = iVar12 * 3 & 0x3fffffff; uVar8 != 0; uVar8 = uVar8 - 1) {
              *param_2 = *pfVar13;
              pfVar13 = pfVar13 + 1;
              param_2 = param_2 + 1;
            }
            for (iVar10 = 0; iVar10 != 0; iVar10 = iVar10 + -1) {
              *(undefined1 *)param_2 = *(undefined1 *)pfVar13;
              pfVar13 = (float *)((int)pfVar13 + 1);
              param_2 = (float *)((int)param_2 + 1);
            }
          }
        }
      }
    }
  }
  return iVar12;
}
#undef local_4


/* ---- 0x00449350  rdClip_Face3_PosB_2 ---- */
int rdClip_Face3_PosB_2(int *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  
  iVar6 = 0;
  pfVar9 = (float *)&DAT_007f48c0;
  iVar8 = 0;
  DAT_007f4ac4 = 0;
  DAT_007f47b8 = param_2;
  DAT_007f46ac = (float *)&DAT_007f48c0;
  pfVar10 = param_2 + param_3 * 3 + -3;
  pfVar11 = param_2;
  if (0 < param_3) {
    do {
      fVar2 = (float)param_1[3];
      fVar1 = (float)param_1[3];
      if ((fVar2 <= *pfVar10) || (fVar1 <= *pfVar11)) {
        iVar7 = iVar6;
        if (((*pfVar10 != fVar2) && (fVar1 != *pfVar11)) &&
           ((*pfVar10 < fVar2 || (*pfVar11 < fVar1)))) {
          fVar3 = (fVar2 - *pfVar10) / (*pfVar11 - *pfVar10);
          iVar8 = iVar8 + 1;
          iVar7 = iVar6 + 0xc;
          *(float *)((int)pfVar9 + iVar6) = fVar2;
          *(float *)((int)DAT_007f46ac + iVar6 + 4) = (pfVar11[1] - pfVar10[1]) * fVar3 + pfVar10[1]
          ;
          *(float *)((int)DAT_007f46ac + iVar6 + 8) = (pfVar11[2] - pfVar10[2]) * fVar3 + pfVar10[2]
          ;
          DAT_007f4ac4 = DAT_007f4ac4 | 0x10;
          pfVar9 = DAT_007f46ac;
        }
        iVar6 = iVar7;
        if (fVar1 <= *pfVar11) {
          pfVar9 = (float *)((int)pfVar9 + iVar7);
          iVar8 = iVar8 + 1;
          iVar6 = iVar7 + 0xc;
          *pfVar9 = *pfVar11;
          pfVar9[1] = pfVar11[1];
          pfVar9[2] = pfVar11[2];
          pfVar9 = DAT_007f46ac;
        }
      }
      param_3 = param_3 + -1;
      pfVar10 = pfVar11;
      pfVar11 = pfVar11 + 3;
    } while (param_3 != 0);
  }
  if (2 < iVar8) {
    iVar6 = 0;
    pfVar10 = DAT_007f47b8;
    DAT_007f46ac = DAT_007f47b8;
    if (0 < iVar8) {
      iVar7 = 0;
      pfVar11 = pfVar9 + iVar8 * 3 + -3;
      pfVar5 = pfVar9;
      DAT_007f47b8 = pfVar9;
      param_3 = iVar8;
      do {
        fVar2 = (float)param_1[5];
        fVar1 = (float)param_1[5];
        if ((*pfVar11 <= fVar2) || (*pfVar5 <= fVar1)) {
          iVar8 = iVar7;
          if (((*pfVar11 != fVar2) && (fVar1 != *pfVar5)) &&
             ((fVar2 < *pfVar11 || (fVar1 < *pfVar5)))) {
            fVar3 = (fVar2 - *pfVar11) / (*pfVar5 - *pfVar11);
            iVar6 = iVar6 + 1;
            iVar8 = iVar7 + 0xc;
            *(float *)((int)pfVar10 + iVar7) = fVar2;
            *(float *)((int)DAT_007f46ac + iVar7 + 4) =
                 (pfVar5[1] - pfVar11[1]) * fVar3 + pfVar11[1];
            *(float *)((int)DAT_007f46ac + iVar7 + 8) =
                 (pfVar5[2] - pfVar11[2]) * fVar3 + pfVar11[2];
            DAT_007f4ac4 = DAT_007f4ac4 | 0x20;
            pfVar10 = DAT_007f46ac;
          }
          iVar7 = iVar8;
          if (*pfVar5 <= fVar1) {
            pfVar10 = (float *)((int)pfVar10 + iVar8);
            iVar6 = iVar6 + 1;
            iVar7 = iVar8 + 0xc;
            *pfVar10 = *pfVar5;
            pfVar10[1] = pfVar5[1];
            pfVar10[2] = pfVar5[2];
            pfVar10 = DAT_007f46ac;
          }
        }
        param_3 = param_3 + -1;
        pfVar11 = pfVar5;
        pfVar5 = pfVar5 + 3;
        pfVar9 = DAT_007f47b8;
      } while (param_3 != 0);
    }
    DAT_007f47b8 = pfVar9;
    iVar8 = iVar6;
    if (2 < iVar8) {
      iVar6 = 0;
      pfVar11 = pfVar10 + iVar8 * 3 + -3;
      pfVar9 = DAT_007f47b8;
      DAT_007f46ac = DAT_007f47b8;
      if (0 < iVar8) {
        pfVar5 = pfVar10 + 2;
        iVar7 = 0;
        DAT_007f47b8 = pfVar10;
        param_3 = iVar8;
        do {
          fVar2 = (float)param_1[4];
          fVar1 = (float)param_1[4];
          if ((pfVar11[2] <= fVar2) || (*pfVar5 <= fVar1)) {
            iVar8 = iVar7;
            if (((pfVar11[2] != fVar2) && (fVar1 != *pfVar5)) &&
               ((fVar2 < pfVar11[2] || (fVar1 < *pfVar5)))) {
              fVar3 = (fVar2 - pfVar11[2]) / (*pfVar5 - pfVar11[2]);
              iVar6 = iVar6 + 1;
              iVar8 = iVar7 + 0xc;
              *(float *)((int)pfVar9 + iVar7) = (pfVar5[-2] - *pfVar11) * fVar3 + *pfVar11;
              *(float *)((int)DAT_007f46ac + iVar7 + 4) =
                   (pfVar5[-1] - pfVar11[1]) * fVar3 + pfVar11[1];
              *(float *)((int)DAT_007f46ac + iVar7 + 8) = fVar2;
              DAT_007f4ac4 = DAT_007f4ac4 | 4;
              pfVar9 = DAT_007f46ac;
            }
            iVar7 = iVar8;
            if (*pfVar5 <= fVar1) {
              pfVar9 = (float *)((int)pfVar9 + iVar8);
              iVar6 = iVar6 + 1;
              iVar7 = iVar8 + 0xc;
              *pfVar9 = pfVar5[-2];
              pfVar9[1] = pfVar5[-1];
              pfVar9[2] = *pfVar5;
              pfVar9 = DAT_007f46ac;
            }
          }
          pfVar11 = pfVar5 + -2;
          pfVar5 = pfVar5 + 3;
          param_3 = param_3 + -1;
          pfVar10 = DAT_007f47b8;
        } while (param_3 != 0);
      }
      DAT_007f47b8 = pfVar10;
      iVar8 = iVar6;
      if (2 < iVar8) {
        iVar6 = 0;
        pfVar10 = pfVar9 + iVar8 * 3 + -3;
        pfVar11 = DAT_007f47b8;
        DAT_007f46ac = DAT_007f47b8;
        if (0 < iVar8) {
          pfVar5 = pfVar9 + 2;
          iVar7 = 0;
          DAT_007f47b8 = pfVar9;
          param_3 = iVar8;
          do {
            fVar2 = (float)param_1[6];
            fVar1 = (float)param_1[6];
            if ((fVar2 <= pfVar10[2]) || (fVar1 <= *pfVar5)) {
              iVar8 = iVar7;
              if (((pfVar10[2] != fVar2) && (fVar1 != *pfVar5)) &&
                 ((pfVar10[2] < fVar2 || (*pfVar5 < fVar1)))) {
                fVar3 = (fVar2 - pfVar10[2]) / (*pfVar5 - pfVar10[2]);
                iVar6 = iVar6 + 1;
                iVar8 = iVar7 + 0xc;
                *(float *)((int)pfVar11 + iVar7) = (pfVar5[-2] - *pfVar10) * fVar3 + *pfVar10;
                *(float *)((int)DAT_007f46ac + iVar7 + 4) =
                     (pfVar5[-1] - pfVar10[1]) * fVar3 + pfVar10[1];
                *(float *)((int)DAT_007f46ac + iVar7 + 8) = fVar2;
                DAT_007f4ac4 = DAT_007f4ac4 | 8;
                pfVar11 = DAT_007f46ac;
              }
              iVar7 = iVar8;
              if (fVar1 <= *pfVar5) {
                pfVar11 = (float *)((int)pfVar11 + iVar8);
                iVar6 = iVar6 + 1;
                iVar7 = iVar8 + 0xc;
                *pfVar11 = pfVar5[-2];
                pfVar11[1] = pfVar5[-1];
                pfVar11[2] = *pfVar5;
                pfVar11 = DAT_007f46ac;
              }
            }
            pfVar10 = pfVar5 + -2;
            pfVar5 = pfVar5 + 3;
            param_3 = param_3 + -1;
            pfVar9 = DAT_007f47b8;
          } while (param_3 != 0);
        }
        DAT_007f47b8 = pfVar9;
        iVar8 = iVar6;
        if (2 < iVar8) {
          iVar6 = 0;
          pfVar10 = pfVar11 + iVar8 * 3 + -3;
          pfVar9 = DAT_007f47b8;
          DAT_007f46ac = DAT_007f47b8;
          if (0 < iVar8) {
            pfVar5 = pfVar11 + 1;
            iVar7 = 0;
            DAT_007f47b8 = pfVar11;
            param_3 = iVar8;
            do {
              iVar8 = iVar7;
              if (((float)param_1[1] <= pfVar10[1]) || ((float)param_1[1] <= *pfVar5)) {
                if (((pfVar10[1] != (float)param_1[1]) && (*pfVar5 != (float)param_1[1])) &&
                   ((pfVar10[1] < (float)param_1[1] || (*pfVar5 < (float)param_1[1])))) {
                  iVar6 = iVar6 + 1;
                  fVar1 = ((float)param_1[1] - pfVar10[1]) / (*pfVar5 - pfVar10[1]);
                  *(int *)((int)pfVar9 + iVar7 + 4) = param_1[1];
                  iVar8 = iVar7 + 0xc;
                  *(float *)((int)DAT_007f46ac + iVar7 + 8) =
                       (pfVar5[1] - pfVar10[2]) * fVar1 + pfVar10[2];
                  *(float *)((int)DAT_007f46ac + iVar7) = (pfVar5[-1] - *pfVar10) * fVar1 + *pfVar10
                  ;
                  DAT_007f4ac4 = DAT_007f4ac4 | 1;
                  pfVar9 = DAT_007f46ac;
                }
                if ((float)param_1[1] <= *pfVar5) {
                  pfVar9 = (float *)((int)pfVar9 + iVar8);
                  iVar6 = iVar6 + 1;
                  iVar8 = iVar8 + 0xc;
                  *pfVar9 = pfVar5[-1];
                  pfVar9[1] = *pfVar5;
                  pfVar9[2] = pfVar5[1];
                  pfVar9 = DAT_007f46ac;
                }
              }
              pfVar10 = pfVar5 + -1;
              pfVar5 = pfVar5 + 3;
              param_3 = param_3 + -1;
              iVar7 = iVar8;
              pfVar11 = DAT_007f47b8;
            } while (param_3 != 0);
          }
          DAT_007f47b8 = pfVar11;
          if (iVar6 < 3) {
            DAT_007f4ac4 = DAT_007f4ac4 | 0x40;
            return iVar6;
          }
          iVar8 = iVar6;
          pfVar10 = pfVar9;
          if (*param_1 != 0) {
            iVar8 = 0;
            pfVar11 = pfVar9 + iVar6 * 3 + -3;
            pfVar10 = DAT_007f47b8;
            DAT_007f46ac = DAT_007f47b8;
            if (0 < iVar6) {
              pfVar5 = pfVar9 + 1;
              iVar7 = 0;
              DAT_007f47b8 = pfVar9;
              param_3 = iVar6;
              do {
                iVar6 = iVar7;
                if ((pfVar11[1] <= (float)param_1[2]) || (*pfVar5 <= (float)param_1[2])) {
                  if (((pfVar11[1] != (float)param_1[2]) && (*pfVar5 != (float)param_1[2])) &&
                     (((float)param_1[2] < pfVar11[1] || ((float)param_1[2] < *pfVar5)))) {
                    iVar8 = iVar8 + 1;
                    fVar1 = ((float)param_1[2] - pfVar11[1]) / (*pfVar5 - pfVar11[1]);
                    *(int *)((int)pfVar10 + iVar7 + 4) = param_1[2];
                    iVar6 = iVar7 + 0xc;
                    *(float *)((int)DAT_007f46ac + iVar7 + 8) =
                         (pfVar5[1] - pfVar11[2]) * fVar1 + pfVar11[2];
                    *(float *)((int)DAT_007f46ac + iVar7) =
                         (pfVar5[-1] - *pfVar11) * fVar1 + *pfVar11;
                    DAT_007f4ac4 = DAT_007f4ac4 | 2;
                    pfVar10 = DAT_007f46ac;
                  }
                  if (*pfVar5 <= (float)param_1[2]) {
                    pfVar10 = (float *)((int)pfVar10 + iVar6);
                    iVar8 = iVar8 + 1;
                    iVar6 = iVar6 + 0xc;
                    *pfVar10 = pfVar5[-1];
                    pfVar10[1] = *pfVar5;
                    pfVar10[2] = pfVar5[1];
                    pfVar10 = DAT_007f46ac;
                  }
                }
                pfVar11 = pfVar5 + -1;
                pfVar5 = pfVar5 + 3;
                param_3 = param_3 + -1;
                iVar7 = iVar6;
                pfVar9 = DAT_007f47b8;
              } while (param_3 != 0);
            }
            DAT_007f47b8 = pfVar9;
            if (iVar8 < 3) {
              return iVar8;
            }
          }
          if (pfVar10 != param_2) {
            for (uVar4 = iVar8 * 3 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
              *param_2 = *pfVar10;
              pfVar10 = pfVar10 + 1;
              param_2 = param_2 + 1;
            }
            for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
              *(undefined1 *)param_2 = *(undefined1 *)pfVar10;
              pfVar10 = (float *)((int)pfVar10 + 1);
              param_2 = (float *)((int)param_2 + 1);
            }
          }
        }
      }
    }
  }
  return iVar8;
}

/* ---- 0x00449aa0  rdClip_Face3_PosUvLit ---- */
/* Face clipper interpolating position, texture coordinate and intensity */

int rdClip_Face3_PosUvLit(int *param_1,float *param_2,float *param_3,float *param_4)

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
  uint uVar10;
  int iVar11;
  int iVar12;
  float *pfVar13;
  float *pfVar14;
  float *pfVar15;
  float *pfVar16;
  float *pfVar17;
  float *pfVar18;
  float *pfVar19;
  #define local_10 (*(float **)(_frame + (0x20 - 0x10)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar11 = 0;
  pfVar14 = (float *)&DAT_007f48c0;
  DAT_007f4ac4 = 0;
  DAT_007f47b8 = param_2;
  DAT_007f4618 = param_3;
  DAT_007f46ac = (float *)&DAT_007f48c0;
  DAT_007f46b0 = (float *)&DAT_007f47c0;
  if (0 < (int)param_4) {
    iVar8 = 0;
    local_4 = (int)param_4;
    pfVar17 = param_2;
    pfVar15 = param_3;
    pfVar16 = param_2 + (int)param_4 * 3 + -3;
    local_10 = param_3 + (int)param_4 + -1;
    do {
      pfVar18 = pfVar15;
      pfVar19 = pfVar17;
      fVar2 = pfVar16[1] * (float)param_1[0xc];
      fVar3 = (float)param_1[0xc] * pfVar19[1];
      if ((fVar2 <= *pfVar16) || (fVar3 <= *pfVar19)) {
        iVar9 = iVar8;
        iVar12 = iVar11;
        if (((*pfVar16 != fVar2) && (fVar3 != *pfVar19)) &&
           ((*pfVar16 < fVar2 || (*pfVar19 < fVar3)))) {
          fVar2 = pfVar19[1] - pfVar16[1];
          fVar4 = *pfVar19 - *pfVar16;
          fVar1 = (float)param_1[0xc] * fVar2 - fVar4;
          fVar5 = pfVar19[1] * *pfVar16 - pfVar16[1] * *pfVar19;
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
            fVar2 = ((float)param_1[0xc] * fVar5 - *pfVar16) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar16[1]) / fVar2;
          }
          *(float *)((int)pfVar14 + iVar8) = (float)param_1[0xc] * fVar5;
          iVar9 = iVar8 + 0xc;
          *(float *)((int)DAT_007f46ac + iVar8 + 4) = fVar5;
          iVar12 = iVar11 + 1;
          *(float *)((int)DAT_007f46ac + iVar8 + 8) = (pfVar19[2] - pfVar16[2]) * fVar2 + pfVar16[2]
          ;
          DAT_007f46b0[iVar11] = (*pfVar18 - *local_10) * fVar2 + *local_10;
          DAT_007f4ac4 = DAT_007f4ac4 | 0x10;
          pfVar14 = DAT_007f46ac;
        }
        iVar8 = iVar9;
        iVar11 = iVar12;
        if (fVar3 <= *pfVar19) {
          pfVar14 = (float *)((int)pfVar14 + iVar9);
          iVar11 = iVar12 + 1;
          iVar8 = iVar9 + 0xc;
          *pfVar14 = *pfVar19;
          pfVar14[1] = pfVar19[1];
          pfVar14[2] = pfVar19[2];
          DAT_007f46b0[iVar12] = *pfVar18;
          pfVar14 = DAT_007f46ac;
        }
      }
      local_4 = local_4 + -1;
      pfVar17 = pfVar19 + 3;
      pfVar15 = pfVar18 + 1;
      pfVar16 = pfVar19;
      local_10 = pfVar18;
    } while (local_4 != 0);
  }
  pfVar17 = DAT_007f4618;
  if (2 < iVar11) {
    DAT_007f4618 = DAT_007f46b0;
    local_10 = DAT_007f46b0 + iVar11 + -1;
    iVar8 = 0;
    pfVar15 = DAT_007f47b8;
    DAT_007f46ac = DAT_007f47b8;
    if (0 < iVar11) {
      iVar9 = 0;
      pfVar16 = pfVar14;
      pfVar19 = DAT_007f46b0;
      pfVar18 = pfVar14 + iVar11 * 3 + -3;
      DAT_007f46b0 = pfVar17;
      DAT_007f47b8 = pfVar14;
      local_4 = iVar11;
      do {
        pfVar13 = pfVar19;
        pfVar14 = pfVar16;
        fVar2 = (float)param_1[10] * pfVar18[1];
        fVar3 = (float)param_1[10] * pfVar14[1];
        if ((*pfVar18 <= fVar2) || (*pfVar14 <= fVar3)) {
          iVar11 = iVar9;
          iVar12 = iVar8;
          if (((*pfVar18 != fVar2) && (fVar3 != *pfVar14)) &&
             ((fVar2 < *pfVar18 || (fVar3 < *pfVar14)))) {
            fVar2 = pfVar14[1] - pfVar18[1];
            fVar4 = *pfVar14 - *pfVar18;
            fVar1 = (float)param_1[10] * fVar2 - fVar4;
            fVar5 = pfVar14[1] * *pfVar18 - pfVar18[1] * *pfVar14;
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
              fVar2 = ((float)param_1[10] * fVar5 - *pfVar18) / fVar4;
            }
            else {
              fVar2 = (fVar5 - pfVar18[1]) / fVar2;
            }
            *(float *)((int)pfVar15 + iVar9) = (float)param_1[10] * fVar5;
            iVar11 = iVar9 + 0xc;
            *(float *)((int)DAT_007f46ac + iVar9 + 4) = fVar5;
            iVar12 = iVar8 + 1;
            *(float *)((int)DAT_007f46ac + iVar9 + 8) =
                 (pfVar14[2] - pfVar18[2]) * fVar2 + pfVar18[2];
            DAT_007f46b0[iVar8] = (*pfVar13 - *local_10) * fVar2 + *local_10;
            DAT_007f4ac4 = DAT_007f4ac4 | 0x20;
            pfVar15 = DAT_007f46ac;
          }
          iVar9 = iVar11;
          iVar8 = iVar12;
          if (*pfVar14 <= fVar3) {
            pfVar15 = (float *)((int)pfVar15 + iVar11);
            iVar8 = iVar12 + 1;
            iVar9 = iVar11 + 0xc;
            *pfVar15 = *pfVar14;
            pfVar15[1] = pfVar14[1];
            pfVar15[2] = pfVar14[2];
            DAT_007f46b0[iVar12] = *pfVar13;
            pfVar15 = DAT_007f46ac;
          }
        }
        local_4 = local_4 + -1;
        pfVar16 = pfVar14 + 3;
        pfVar19 = pfVar13 + 1;
        pfVar18 = pfVar14;
        pfVar17 = DAT_007f46b0;
        pfVar14 = DAT_007f47b8;
        local_10 = pfVar13;
      } while (local_4 != 0);
    }
    DAT_007f47b8 = pfVar14;
    DAT_007f46b0 = pfVar17;
    iVar11 = iVar8;
    pfVar14 = DAT_007f46b0;
    if (2 < iVar11) {
      DAT_007f46b0 = DAT_007f4618;
      iVar8 = 0;
      DAT_007f46ac = DAT_007f47b8;
      pfVar17 = pfVar15 + iVar11 * 3 + -3;
      DAT_007f4618 = pfVar14;
      pfVar16 = DAT_007f47b8;
      if (0 < iVar11) {
        iVar9 = 0;
        pfVar19 = pfVar15 + 2;
        DAT_007f47b8 = pfVar15;
        local_10 = pfVar14 + iVar11 + -1;
        local_4 = iVar11;
        do {
          pfVar18 = pfVar14;
          fVar2 = (float)param_1[0xb] * pfVar17[1];
          fVar3 = pfVar19[-1] * (float)param_1[0xb];
          if ((pfVar17[2] <= fVar2) || (*pfVar19 <= fVar3)) {
            iVar11 = iVar9;
            iVar12 = iVar8;
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
              iVar11 = iVar9 + 0xc;
              iVar12 = iVar8 + 1;
              *(float *)((int)pfVar16 + iVar9) = (pfVar19[-2] - *pfVar17) * fVar2 + *pfVar17;
              *(float *)((int)DAT_007f46ac + iVar9 + 4) = fVar5;
              *(float *)((int)DAT_007f46ac + iVar9 + 8) = fVar1 * fVar5;
              DAT_007f46b0[iVar8] = (*pfVar18 - *local_10) * fVar2 + *local_10;
              DAT_007f4ac4 = DAT_007f4ac4 | 4;
              pfVar16 = DAT_007f46ac;
            }
            iVar9 = iVar11;
            iVar8 = iVar12;
            if (*pfVar19 <= fVar3) {
              pfVar16 = (float *)((int)pfVar16 + iVar11);
              iVar8 = iVar12 + 1;
              iVar9 = iVar11 + 0xc;
              *pfVar16 = pfVar19[-2];
              pfVar16[1] = pfVar19[-1];
              pfVar16[2] = *pfVar19;
              DAT_007f46b0[iVar12] = *pfVar18;
              pfVar16 = DAT_007f46ac;
            }
          }
          pfVar17 = pfVar19 + -2;
          pfVar19 = pfVar19 + 3;
          local_4 = local_4 + -1;
          pfVar14 = pfVar18 + 1;
          pfVar15 = DAT_007f47b8;
          local_10 = pfVar18;
        } while (local_4 != 0);
      }
      DAT_007f47b8 = pfVar15;
      iVar11 = iVar8;
      pfVar14 = DAT_007f46b0;
      if (2 < iVar11) {
        DAT_007f46b0 = DAT_007f4618;
        iVar8 = 0;
        DAT_007f46ac = DAT_007f47b8;
        pfVar17 = pfVar16 + iVar11 * 3 + -3;
        DAT_007f4618 = pfVar14;
        pfVar15 = DAT_007f47b8;
        if (0 < iVar11) {
          iVar9 = 0;
          pfVar19 = pfVar16 + 2;
          DAT_007f47b8 = pfVar16;
          local_10 = pfVar14 + iVar11 + -1;
          local_4 = iVar11;
          do {
            pfVar18 = pfVar14;
            fVar2 = (float)param_1[8] * pfVar17[1];
            fVar3 = pfVar19[-1] * (float)param_1[8];
            if ((fVar2 <= pfVar17[2]) || (fVar3 <= *pfVar19)) {
              iVar11 = iVar9;
              iVar12 = iVar8;
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
                iVar11 = iVar9 + 0xc;
                iVar12 = iVar8 + 1;
                *(float *)((int)pfVar15 + iVar9) = (pfVar19[-2] - *pfVar17) * fVar2 + *pfVar17;
                *(float *)((int)DAT_007f46ac + iVar9 + 4) = fVar5;
                *(float *)((int)DAT_007f46ac + iVar9 + 8) = fVar1 * fVar5;
                DAT_007f46b0[iVar8] = (*pfVar18 - *local_10) * fVar2 + *local_10;
                DAT_007f4ac4 = DAT_007f4ac4 | 8;
                pfVar15 = DAT_007f46ac;
              }
              iVar9 = iVar11;
              iVar8 = iVar12;
              if (fVar3 <= *pfVar19) {
                pfVar15 = (float *)((int)pfVar15 + iVar11);
                iVar8 = iVar12 + 1;
                iVar9 = iVar11 + 0xc;
                *pfVar15 = pfVar19[-2];
                pfVar15[1] = pfVar19[-1];
                pfVar15[2] = *pfVar19;
                DAT_007f46b0[iVar12] = *pfVar18;
                pfVar15 = DAT_007f46ac;
              }
            }
            pfVar17 = pfVar19 + -2;
            pfVar19 = pfVar19 + 3;
            local_4 = local_4 + -1;
            pfVar14 = pfVar18 + 1;
            pfVar16 = DAT_007f47b8;
            local_10 = pfVar18;
          } while (local_4 != 0);
        }
        DAT_007f47b8 = pfVar16;
        iVar11 = iVar8;
        param_4 = DAT_007f46b0;
        if (2 < iVar11) {
          DAT_007f46b0 = DAT_007f4618;
          iVar8 = 0;
          local_10 = param_4 + iVar11 + -1;
          DAT_007f46ac = DAT_007f47b8;
          DAT_007f4618 = param_4;
          pfVar14 = pfVar15 + iVar11 * 3 + -3;
          pfVar17 = DAT_007f47b8;
          if (0 < iVar11) {
            pfVar16 = pfVar15 + 1;
            iVar9 = 0;
            DAT_007f47b8 = pfVar15;
            local_4 = iVar11;
            do {
              iVar11 = iVar9;
              if (((float)param_1[1] <= pfVar14[1]) || ((float)param_1[1] <= *pfVar16)) {
                iVar12 = iVar8;
                if (((pfVar14[1] != (float)param_1[1]) && (*pfVar16 != (float)param_1[1])) &&
                   ((pfVar14[1] < (float)param_1[1] || (*pfVar16 < (float)param_1[1])))) {
                  fVar2 = ((float)param_1[1] - pfVar14[1]) / (*pfVar16 - pfVar14[1]);
                  *(int *)((int)pfVar17 + iVar9 + 4) = param_1[1];
                  iVar11 = iVar9 + 0xc;
                  iVar12 = iVar8 + 1;
                  *(float *)((int)DAT_007f46ac + iVar9 + 8) =
                       (pfVar16[1] - pfVar14[2]) * fVar2 + pfVar14[2];
                  *(float *)((int)DAT_007f46ac + iVar9) =
                       (pfVar16[-1] - *pfVar14) * fVar2 + *pfVar14;
                  DAT_007f46b0[iVar8] = (*param_4 - *local_10) * fVar2 + *local_10;
                  DAT_007f4ac4 = DAT_007f4ac4 | 1;
                  pfVar17 = DAT_007f46ac;
                }
                iVar8 = iVar12;
                if ((float)param_1[1] <= *pfVar16) {
                  pfVar17 = (float *)((int)pfVar17 + iVar11);
                  iVar8 = iVar12 + 1;
                  iVar11 = iVar11 + 0xc;
                  *pfVar17 = pfVar16[-1];
                  pfVar17[1] = *pfVar16;
                  pfVar17[2] = pfVar16[1];
                  DAT_007f46b0[iVar12] = *param_4;
                  pfVar17 = DAT_007f46ac;
                }
              }
              pfVar14 = pfVar16 + -1;
              local_10 = param_4;
              param_4 = param_4 + 1;
              pfVar16 = pfVar16 + 3;
              local_4 = local_4 + -1;
              iVar9 = iVar11;
              pfVar15 = DAT_007f47b8;
            } while (local_4 != 0);
          }
          DAT_007f47b8 = pfVar15;
          param_4 = DAT_007f46b0;
          if (iVar8 < 3) {
            DAT_007f4ac4 = DAT_007f4ac4 | 0x40;
            return iVar8;
          }
          iVar11 = iVar8;
          pfVar14 = pfVar17;
          if (*param_1 != 0) {
            DAT_007f46b0 = DAT_007f4618;
            iVar11 = 0;
            local_10 = param_4 + iVar8 + -1;
            DAT_007f46ac = DAT_007f47b8;
            DAT_007f4618 = param_4;
            pfVar15 = pfVar17 + iVar8 * 3 + -3;
            pfVar14 = DAT_007f47b8;
            if (0 < iVar8) {
              pfVar16 = pfVar17 + 1;
              iVar9 = 0;
              DAT_007f47b8 = pfVar17;
              local_4 = iVar8;
              do {
                iVar8 = iVar9;
                if ((pfVar15[1] <= (float)param_1[2]) || (*pfVar16 <= (float)param_1[2])) {
                  iVar12 = iVar11;
                  if (((pfVar15[1] != (float)param_1[2]) && (*pfVar16 != (float)param_1[2])) &&
                     (((float)param_1[2] < pfVar15[1] || ((float)param_1[2] < *pfVar16)))) {
                    fVar2 = ((float)param_1[2] - pfVar15[1]) / (*pfVar16 - pfVar15[1]);
                    *(int *)((int)pfVar14 + iVar9 + 4) = param_1[2];
                    iVar8 = iVar9 + 0xc;
                    iVar12 = iVar11 + 1;
                    *(float *)((int)DAT_007f46ac + iVar9 + 8) =
                         (pfVar16[1] - pfVar15[2]) * fVar2 + pfVar15[2];
                    *(float *)((int)DAT_007f46ac + iVar9) =
                         (pfVar16[-1] - *pfVar15) * fVar2 + *pfVar15;
                    DAT_007f46b0[iVar11] = (*param_4 - *local_10) * fVar2 + *local_10;
                    DAT_007f4ac4 = DAT_007f4ac4 | 2;
                    pfVar14 = DAT_007f46ac;
                  }
                  iVar11 = iVar12;
                  if (*pfVar16 <= (float)param_1[2]) {
                    pfVar14 = (float *)((int)pfVar14 + iVar8);
                    iVar11 = iVar12 + 1;
                    iVar8 = iVar8 + 0xc;
                    *pfVar14 = pfVar16[-1];
                    pfVar14[1] = *pfVar16;
                    pfVar14[2] = pfVar16[1];
                    DAT_007f46b0[iVar12] = *param_4;
                    pfVar14 = DAT_007f46ac;
                  }
                }
                pfVar15 = pfVar16 + -1;
                local_10 = param_4;
                param_4 = param_4 + 1;
                pfVar16 = pfVar16 + 3;
                local_4 = local_4 + -1;
                iVar9 = iVar8;
                pfVar17 = DAT_007f47b8;
              } while (local_4 != 0);
            }
            DAT_007f47b8 = pfVar17;
            if (iVar11 < 3) {
              return iVar11;
            }
          }
          if (pfVar14 != param_2) {
            for (uVar10 = iVar11 * 3 & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
              *param_2 = *pfVar14;
              pfVar14 = pfVar14 + 1;
              param_2 = param_2 + 1;
            }
            for (iVar8 = 0; iVar9 = iVar11, pfVar17 = DAT_007f46b0, iVar8 != 0; iVar8 = iVar8 + -1)
            {
              *(undefined1 *)param_2 = *(undefined1 *)pfVar14;
              pfVar14 = (float *)((int)pfVar14 + 1);
              param_2 = (float *)((int)param_2 + 1);
            }
            for (; iVar9 != 0; iVar9 = iVar9 + -1) {
              *param_3 = *pfVar17;
              pfVar17 = pfVar17 + 1;
              param_3 = param_3 + 1;
            }
          }
        }
      }
    }
  }
  return iVar11;
}
#undef local_10
#undef local_4


/* ---- 0x0044a6d0  rdClip_Face3_PosUv ---- */
int rdClip_Face3_PosUv(int *param_1,float *param_2,float *param_3,int param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  uint uVar5;
  float *pfVar6;
  int iVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  float *pfVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  #define local_c (*(float **)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  pfVar9 = (float *)&DAT_007f48c0;
  DAT_007f4ac4 = 0;
  DAT_007f47b8 = param_2;
  DAT_007f4618 = param_3;
  DAT_007f46ac = (float *)&DAT_007f48c0;
  DAT_007f46b0 = (float *)&DAT_007f47c0;
  if (0 < param_4) {
    iVar13 = 0;
    pfVar12 = param_2 + param_4 * 3 + -3;
    pfVar10 = param_2;
    pfVar11 = param_3;
    local_8 = param_3 + param_4 + -1;
    do {
      pfVar6 = pfVar11;
      fVar2 = (float)param_1[3];
      fVar1 = (float)param_1[3];
      if ((fVar2 <= *pfVar12) || (fVar1 <= *pfVar10)) {
        iVar7 = local_4;
        iVar14 = iVar13;
        if (((*pfVar12 != fVar2) && (fVar1 != *pfVar10)) &&
           ((*pfVar12 < fVar2 || (*pfVar10 < fVar1)))) {
          fVar3 = (fVar2 - *pfVar12) / (*pfVar10 - *pfVar12);
          iVar14 = iVar13 + 0xc;
          iVar7 = local_4 + 1;
          *(float *)((int)pfVar9 + iVar13) = fVar2;
          *(float *)((int)DAT_007f46ac + iVar13 + 4) =
               (pfVar10[1] - pfVar12[1]) * fVar3 + pfVar12[1];
          *(float *)((int)DAT_007f46ac + iVar13 + 8) =
               (pfVar10[2] - pfVar12[2]) * fVar3 + pfVar12[2];
          DAT_007f46b0[local_4] = (*pfVar6 - *local_8) * fVar3 + *local_8;
          DAT_007f4ac4 = DAT_007f4ac4 | 0x10;
          pfVar9 = DAT_007f46ac;
        }
        local_4 = iVar7;
        iVar13 = iVar14;
        if (fVar1 <= *pfVar10) {
          pfVar9 = (float *)((int)pfVar9 + iVar14);
          local_4 = iVar7 + 1;
          iVar13 = iVar14 + 0xc;
          *pfVar9 = *pfVar10;
          pfVar9[1] = pfVar10[1];
          pfVar9[2] = pfVar10[2];
          DAT_007f46b0[iVar7] = *pfVar6;
          pfVar9 = DAT_007f46ac;
        }
      }
      param_4 = param_4 + -1;
      pfVar12 = pfVar10;
      pfVar10 = pfVar10 + 3;
      pfVar11 = pfVar6 + 1;
      local_8 = pfVar6;
    } while (param_4 != 0);
  }
  pfVar12 = DAT_007f4618;
  if (2 < local_4) {
    local_8 = DAT_007f46b0 + local_4 + -1;
    iVar13 = 0;
    DAT_007f4618 = DAT_007f46b0;
    pfVar10 = DAT_007f47b8;
    DAT_007f46ac = DAT_007f47b8;
    if (0 < local_4) {
      iVar7 = 0;
      pfVar11 = pfVar9 + local_4 * 3 + -3;
      pfVar6 = pfVar9;
      pfVar4 = DAT_007f46b0;
      DAT_007f46b0 = pfVar12;
      DAT_007f47b8 = pfVar9;
      param_4 = local_4;
      do {
        pfVar8 = pfVar4;
        fVar2 = (float)param_1[5];
        fVar1 = (float)param_1[5];
        if ((*pfVar11 <= fVar2) || (*pfVar6 <= fVar1)) {
          iVar14 = iVar13;
          iVar15 = iVar7;
          if (((*pfVar11 != fVar2) && (fVar1 != *pfVar6)) &&
             ((fVar2 < *pfVar11 || (fVar1 < *pfVar6)))) {
            fVar3 = (fVar2 - *pfVar11) / (*pfVar6 - *pfVar11);
            iVar15 = iVar7 + 0xc;
            iVar14 = iVar13 + 1;
            *(float *)((int)pfVar10 + iVar7) = fVar2;
            *(float *)((int)DAT_007f46ac + iVar7 + 4) =
                 (pfVar6[1] - pfVar11[1]) * fVar3 + pfVar11[1];
            *(float *)((int)DAT_007f46ac + iVar7 + 8) =
                 (pfVar6[2] - pfVar11[2]) * fVar3 + pfVar11[2];
            DAT_007f46b0[iVar13] = (*pfVar8 - *local_8) * fVar3 + *local_8;
            DAT_007f4ac4 = DAT_007f4ac4 | 0x20;
            pfVar10 = DAT_007f46ac;
          }
          iVar13 = iVar14;
          iVar7 = iVar15;
          if (*pfVar6 <= fVar1) {
            pfVar10 = (float *)((int)pfVar10 + iVar15);
            iVar13 = iVar14 + 1;
            iVar7 = iVar15 + 0xc;
            *pfVar10 = *pfVar6;
            pfVar10[1] = pfVar6[1];
            pfVar10[2] = pfVar6[2];
            DAT_007f46b0[iVar14] = *pfVar8;
            pfVar10 = DAT_007f46ac;
          }
        }
        param_4 = param_4 + -1;
        pfVar11 = pfVar6;
        pfVar6 = pfVar6 + 3;
        pfVar4 = pfVar8 + 1;
        pfVar12 = DAT_007f46b0;
        pfVar9 = DAT_007f47b8;
        local_8 = pfVar8;
      } while (param_4 != 0);
    }
    DAT_007f47b8 = pfVar9;
    DAT_007f46b0 = pfVar12;
    local_4 = iVar13;
    pfVar9 = DAT_007f4618;
    if (2 < local_4) {
      local_8 = DAT_007f46b0 + local_4 + -1;
      iVar13 = 0;
      DAT_007f4618 = DAT_007f46b0;
      pfVar12 = pfVar10 + local_4 * 3 + -3;
      pfVar11 = DAT_007f47b8;
      DAT_007f46ac = DAT_007f47b8;
      if (0 < local_4) {
        pfVar6 = pfVar10 + 2;
        iVar7 = 0;
        pfVar4 = DAT_007f46b0;
        DAT_007f46b0 = pfVar9;
        DAT_007f47b8 = pfVar10;
        do {
          pfVar8 = pfVar4;
          fVar2 = (float)param_1[4];
          fVar1 = (float)param_1[4];
          if ((pfVar12[2] <= fVar2) || (*pfVar6 <= fVar1)) {
            iVar14 = iVar13;
            iVar15 = iVar7;
            if (((pfVar12[2] != fVar2) && (fVar1 != *pfVar6)) &&
               ((fVar2 < pfVar12[2] || (fVar1 < *pfVar6)))) {
              fVar3 = (fVar2 - pfVar12[2]) / (*pfVar6 - pfVar12[2]);
              iVar15 = iVar7 + 0xc;
              iVar14 = iVar13 + 1;
              *(float *)((int)pfVar11 + iVar7) = (pfVar6[-2] - *pfVar12) * fVar3 + *pfVar12;
              *(float *)((int)DAT_007f46ac + iVar7 + 4) =
                   (pfVar6[-1] - pfVar12[1]) * fVar3 + pfVar12[1];
              *(float *)((int)DAT_007f46ac + iVar7 + 8) = fVar2;
              DAT_007f46b0[iVar13] = (*pfVar8 - *local_8) * fVar3 + *local_8;
              DAT_007f4ac4 = DAT_007f4ac4 | 4;
              pfVar11 = DAT_007f46ac;
            }
            iVar13 = iVar14;
            iVar7 = iVar15;
            if (*pfVar6 <= fVar1) {
              pfVar11 = (float *)((int)pfVar11 + iVar15);
              iVar13 = iVar14 + 1;
              iVar7 = iVar15 + 0xc;
              *pfVar11 = pfVar6[-2];
              pfVar11[1] = pfVar6[-1];
              pfVar11[2] = *pfVar6;
              DAT_007f46b0[iVar14] = *pfVar8;
              pfVar11 = DAT_007f46ac;
            }
          }
          pfVar12 = pfVar6 + -2;
          pfVar6 = pfVar6 + 3;
          local_4 = local_4 + -1;
          pfVar4 = pfVar8 + 1;
          pfVar9 = DAT_007f46b0;
          pfVar10 = DAT_007f47b8;
          local_8 = pfVar8;
        } while (local_4 != 0);
      }
      DAT_007f47b8 = pfVar10;
      DAT_007f46b0 = pfVar9;
      local_4 = iVar13;
      pfVar9 = DAT_007f4618;
      if (2 < local_4) {
        iVar13 = 0;
        local_8 = DAT_007f46b0 + local_4 + -1;
        DAT_007f4618 = DAT_007f46b0;
        pfVar12 = pfVar11 + local_4 * 3 + -3;
        local_c = DAT_007f46b0;
        pfVar10 = DAT_007f47b8;
        DAT_007f46ac = DAT_007f47b8;
        DAT_007f46b0 = pfVar9;
        if (0 < local_4) {
          iVar7 = 0;
          pfVar9 = pfVar11 + 2;
          DAT_007f47b8 = pfVar11;
          do {
            fVar2 = (float)param_1[6];
            fVar1 = (float)param_1[6];
            if ((fVar2 <= pfVar12[2]) || (fVar1 <= *pfVar9)) {
              iVar14 = iVar13;
              iVar15 = iVar7;
              if (((pfVar12[2] != fVar2) && (fVar1 != *pfVar9)) &&
                 ((pfVar12[2] < fVar2 || (*pfVar9 < fVar1)))) {
                fVar3 = (fVar2 - pfVar12[2]) / (*pfVar9 - pfVar12[2]);
                iVar15 = iVar7 + 0xc;
                iVar14 = iVar13 + 1;
                *(float *)((int)pfVar10 + iVar7) = (pfVar9[-2] - *pfVar12) * fVar3 + *pfVar12;
                *(float *)((int)DAT_007f46ac + iVar7 + 4) =
                     (pfVar9[-1] - pfVar12[1]) * fVar3 + pfVar12[1];
                *(float *)((int)DAT_007f46ac + iVar7 + 8) = fVar2;
                DAT_007f46b0[iVar13] = (*local_c - *local_8) * fVar3 + *local_8;
                DAT_007f4ac4 = DAT_007f4ac4 | 8;
                pfVar10 = DAT_007f46ac;
              }
              iVar13 = iVar14;
              iVar7 = iVar15;
              if (fVar1 <= *pfVar9) {
                pfVar10 = (float *)((int)pfVar10 + iVar15);
                iVar13 = iVar14 + 1;
                iVar7 = iVar15 + 0xc;
                *pfVar10 = pfVar9[-2];
                pfVar10[1] = pfVar9[-1];
                pfVar10[2] = *pfVar9;
                DAT_007f46b0[iVar14] = *local_c;
                pfVar10 = DAT_007f46ac;
              }
            }
            pfVar12 = pfVar9 + -2;
            local_8 = local_c;
            local_c = local_c + 1;
            pfVar9 = pfVar9 + 3;
            local_4 = local_4 + -1;
            pfVar11 = DAT_007f47b8;
          } while (local_4 != 0);
        }
        DAT_007f47b8 = pfVar11;
        local_4 = iVar13;
        pfVar9 = DAT_007f4618;
        if (2 < local_4) {
          local_8 = DAT_007f46b0 + local_4 + -1;
          iVar13 = 0;
          DAT_007f4618 = DAT_007f46b0;
          pfVar12 = pfVar10 + local_4 * 3 + -3;
          local_c = DAT_007f46b0;
          pfVar11 = DAT_007f47b8;
          DAT_007f46ac = DAT_007f47b8;
          DAT_007f46b0 = pfVar9;
          if (0 < local_4) {
            pfVar9 = pfVar10 + 1;
            iVar7 = 0;
            DAT_007f47b8 = pfVar10;
            param_4 = local_4;
            do {
              iVar14 = iVar7;
              if (((float)param_1[1] <= pfVar12[1]) || ((float)param_1[1] <= *pfVar9)) {
                iVar15 = iVar13;
                if (((pfVar12[1] != (float)param_1[1]) && (*pfVar9 != (float)param_1[1])) &&
                   ((pfVar12[1] < (float)param_1[1] || (*pfVar9 < (float)param_1[1])))) {
                  fVar1 = ((float)param_1[1] - pfVar12[1]) / (*pfVar9 - pfVar12[1]);
                  *(int *)((int)pfVar11 + iVar7 + 4) = param_1[1];
                  iVar14 = iVar7 + 0xc;
                  iVar15 = iVar13 + 1;
                  *(float *)((int)DAT_007f46ac + iVar7 + 8) =
                       (pfVar9[1] - pfVar12[2]) * fVar1 + pfVar12[2];
                  *(float *)((int)DAT_007f46ac + iVar7) = (pfVar9[-1] - *pfVar12) * fVar1 + *pfVar12
                  ;
                  DAT_007f46b0[iVar13] = (*local_c - *local_8) * fVar1 + *local_8;
                  DAT_007f4ac4 = DAT_007f4ac4 | 1;
                  pfVar11 = DAT_007f46ac;
                }
                iVar13 = iVar15;
                if ((float)param_1[1] <= *pfVar9) {
                  pfVar11 = (float *)((int)pfVar11 + iVar14);
                  iVar13 = iVar15 + 1;
                  iVar14 = iVar14 + 0xc;
                  *pfVar11 = pfVar9[-1];
                  pfVar11[1] = *pfVar9;
                  pfVar11[2] = pfVar9[1];
                  DAT_007f46b0[iVar15] = *local_c;
                  pfVar11 = DAT_007f46ac;
                }
              }
              pfVar12 = pfVar9 + -1;
              local_8 = local_c;
              local_c = local_c + 1;
              pfVar9 = pfVar9 + 3;
              param_4 = param_4 + -1;
              iVar7 = iVar14;
              pfVar10 = DAT_007f47b8;
            } while (param_4 != 0);
          }
          DAT_007f47b8 = pfVar10;
          pfVar9 = DAT_007f4618;
          if (iVar13 < 3) {
            DAT_007f4ac4 = DAT_007f4ac4 | 0x40;
            return iVar13;
          }
          local_4 = iVar13;
          pfVar12 = pfVar11;
          if (*param_1 != 0) {
            local_8 = DAT_007f46b0 + iVar13 + -1;
            local_4 = 0;
            DAT_007f4618 = DAT_007f46b0;
            pfVar10 = pfVar11 + iVar13 * 3 + -3;
            local_c = DAT_007f46b0;
            pfVar12 = DAT_007f47b8;
            DAT_007f46ac = DAT_007f47b8;
            DAT_007f46b0 = pfVar9;
            if (0 < iVar13) {
              pfVar9 = pfVar11 + 1;
              iVar7 = 0;
              DAT_007f47b8 = pfVar11;
              param_4 = iVar13;
              do {
                iVar13 = iVar7;
                if ((pfVar10[1] <= (float)param_1[2]) || (*pfVar9 <= (float)param_1[2])) {
                  iVar14 = local_4;
                  if (((pfVar10[1] != (float)param_1[2]) && (*pfVar9 != (float)param_1[2])) &&
                     (((float)param_1[2] < pfVar10[1] || ((float)param_1[2] < *pfVar9)))) {
                    fVar1 = ((float)param_1[2] - pfVar10[1]) / (*pfVar9 - pfVar10[1]);
                    *(int *)((int)pfVar12 + iVar7 + 4) = param_1[2];
                    iVar13 = iVar7 + 0xc;
                    iVar14 = local_4 + 1;
                    *(float *)((int)DAT_007f46ac + iVar7 + 8) =
                         (pfVar9[1] - pfVar10[2]) * fVar1 + pfVar10[2];
                    *(float *)((int)DAT_007f46ac + iVar7) =
                         (pfVar9[-1] - *pfVar10) * fVar1 + *pfVar10;
                    DAT_007f46b0[local_4] = (*local_c - *local_8) * fVar1 + *local_8;
                    DAT_007f4ac4 = DAT_007f4ac4 | 2;
                    pfVar12 = DAT_007f46ac;
                  }
                  local_4 = iVar14;
                  if (*pfVar9 <= (float)param_1[2]) {
                    pfVar12 = (float *)((int)pfVar12 + iVar13);
                    local_4 = iVar14 + 1;
                    iVar13 = iVar13 + 0xc;
                    *pfVar12 = pfVar9[-1];
                    pfVar12[1] = *pfVar9;
                    pfVar12[2] = pfVar9[1];
                    DAT_007f46b0[iVar14] = *local_c;
                    pfVar12 = DAT_007f46ac;
                  }
                }
                pfVar10 = pfVar9 + -1;
                local_8 = local_c;
                local_c = local_c + 1;
                pfVar9 = pfVar9 + 3;
                param_4 = param_4 + -1;
                iVar7 = iVar13;
                pfVar11 = DAT_007f47b8;
              } while (param_4 != 0);
            }
            DAT_007f47b8 = pfVar11;
            if (local_4 < 3) {
              return local_4;
            }
          }
          if (pfVar12 != param_2) {
            for (uVar5 = local_4 * 3 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
              *param_2 = *pfVar12;
              pfVar12 = pfVar12 + 1;
              param_2 = param_2 + 1;
            }
            for (iVar13 = 0; iVar7 = local_4, pfVar9 = DAT_007f46b0, iVar13 != 0;
                iVar13 = iVar13 + -1) {
              *(undefined1 *)param_2 = *(undefined1 *)pfVar12;
              pfVar12 = (float *)((int)pfVar12 + 1);
              param_2 = (float *)((int)param_2 + 1);
            }
            for (; iVar7 != 0; iVar7 = iVar7 + -1) {
              *param_3 = *pfVar9;
              pfVar9 = pfVar9 + 1;
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
  uint uVar13;
  float *pfVar14;
  float *pfVar15;
  float *pfVar16;
  float *pfVar17;
  float *pfVar18;
  float *pfVar19;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  DAT_007f4ac4 = 0;
  local_10 = 0;
  pfVar15 = (float *)&DAT_007f48c0;
  DAT_007f47b8 = param_2;
  DAT_007f46ac = (float *)&DAT_007f48c0;
  DAT_007f461c = param_3;
  DAT_007f46a8 = (float *)&DAT_007f46b8;
  if (0 < (int)param_4) {
    iVar8 = 0;
    local_4 = (uint)param_4;
    pfVar18 = param_3 + (int)param_4 * 2 + -2;
    pfVar16 = param_3;
    pfVar17 = param_2 + (int)param_4 * 3 + -3;
    pfVar10 = param_2;
    do {
      fVar2 = pfVar17[1] * (float)param_1[0xc];
      fVar3 = (float)param_1[0xc] * pfVar10[1];
      if ((fVar2 <= *pfVar17) || (fVar3 <= *pfVar10)) {
        iVar9 = iVar8;
        if (((*pfVar17 != fVar2) && (fVar3 != *pfVar10)) &&
           ((*pfVar17 < fVar2 || (*pfVar10 < fVar3)))) {
          fVar2 = pfVar10[1] - pfVar17[1];
          fVar4 = *pfVar10 - *pfVar17;
          fVar1 = (float)param_1[0xc] * fVar2 - fVar4;
          fVar5 = pfVar10[1] * *pfVar17 - pfVar17[1] * *pfVar10;
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
            fVar2 = ((float)param_1[0xc] * fVar5 - *pfVar17) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar17[1]) / fVar2;
          }
          *(float *)((int)pfVar15 + iVar8) = (float)param_1[0xc] * fVar5;
          *(float *)((int)DAT_007f46ac + iVar8 + 4) = fVar5;
          iVar9 = iVar8 + 0xc;
          *(float *)((int)DAT_007f46ac + iVar8 + 8) = (pfVar10[2] - pfVar17[2]) * fVar2 + pfVar17[2]
          ;
          DAT_007f46a8[local_10 * 2] = (*pfVar16 - *pfVar18) * fVar2 + *pfVar18;
          DAT_007f46a8[local_10 * 2 + 1] = (pfVar16[1] - pfVar18[1]) * fVar2 + pfVar18[1];
          DAT_007f4ac4 = DAT_007f4ac4 | 0x10;
          pfVar15 = DAT_007f46ac;
          local_10 = local_10 + 1;
        }
        iVar8 = iVar9;
        if (fVar3 <= *pfVar10) {
          pfVar15 = (float *)((int)pfVar15 + iVar9);
          *pfVar15 = *pfVar10;
          pfVar15[1] = pfVar10[1];
          pfVar15[2] = pfVar10[2];
          DAT_007f46a8[local_10 * 2] = *pfVar16;
          DAT_007f46a8[local_10 * 2 + 1] = pfVar16[1];
          local_10 = local_10 + 1;
          iVar8 = iVar9 + 0xc;
          pfVar15 = DAT_007f46ac;
        }
      }
      local_4 = local_4 + -1;
      pfVar18 = pfVar16;
      pfVar16 = pfVar16 + 2;
      pfVar17 = pfVar10;
      pfVar10 = pfVar10 + 3;
    } while (local_4 != 0);
  }
  local_4 = local_10;
  pfVar18 = DAT_007f461c;
  if ((int)local_10 < 3) {
    return local_10;
  }
  DAT_007f461c = DAT_007f46a8;
  iVar8 = local_10 * 2;
  local_10 = 0;
  pfVar16 = DAT_007f47b8;
  DAT_007f46ac = DAT_007f47b8;
  if (0 < (int)local_4) {
    iVar9 = 0;
    pfVar17 = DAT_007f46a8 + iVar8 + -2;
    pfVar10 = pfVar15;
    pfVar14 = DAT_007f46a8;
    pfVar19 = pfVar15 + local_4 * 3 + -3;
    DAT_007f46a8 = pfVar18;
    DAT_007f47b8 = pfVar15;
    do {
      pfVar15 = pfVar10;
      fVar2 = (float)param_1[10] * pfVar19[1];
      fVar3 = (float)param_1[10] * pfVar15[1];
      if ((*pfVar19 <= fVar2) || (*pfVar15 <= fVar3)) {
        iVar8 = iVar9;
        if (((*pfVar19 != fVar2) && (fVar3 != *pfVar15)) &&
           ((fVar2 < *pfVar19 || (fVar3 < *pfVar15)))) {
          fVar2 = pfVar15[1] - pfVar19[1];
          fVar4 = *pfVar15 - *pfVar19;
          fVar1 = (float)param_1[10] * fVar2 - fVar4;
          fVar5 = pfVar15[1] * *pfVar19 - pfVar19[1] * *pfVar15;
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
          *(float *)((int)pfVar16 + iVar9) = (float)param_1[10] * fVar5;
          *(float *)((int)DAT_007f46ac + iVar9 + 4) = fVar5;
          iVar8 = iVar9 + 0xc;
          *(float *)((int)DAT_007f46ac + iVar9 + 8) = (pfVar15[2] - pfVar19[2]) * fVar2 + pfVar19[2]
          ;
          DAT_007f46a8[local_10 * 2] = (*pfVar14 - *pfVar17) * fVar2 + *pfVar17;
          DAT_007f46a8[local_10 * 2 + 1] = (pfVar14[1] - pfVar17[1]) * fVar2 + pfVar17[1];
          DAT_007f4ac4 = DAT_007f4ac4 | 0x20;
          pfVar16 = DAT_007f46ac;
          local_10 = local_10 + 1;
        }
        iVar9 = iVar8;
        if (*pfVar15 <= fVar3) {
          pfVar16 = (float *)((int)pfVar16 + iVar8);
          *pfVar16 = *pfVar15;
          pfVar16[1] = pfVar15[1];
          pfVar16[2] = pfVar15[2];
          DAT_007f46a8[local_10 * 2] = *pfVar14;
          DAT_007f46a8[local_10 * 2 + 1] = pfVar14[1];
          local_10 = local_10 + 1;
          iVar9 = iVar8 + 0xc;
          pfVar16 = DAT_007f46ac;
        }
      }
      local_4 = local_4 - 1;
      pfVar17 = pfVar14;
      pfVar10 = pfVar15 + 3;
      pfVar14 = pfVar14 + 2;
      pfVar19 = pfVar15;
      pfVar18 = DAT_007f46a8;
      pfVar15 = DAT_007f47b8;
    } while (local_4 != 0);
  }
  DAT_007f47b8 = pfVar15;
  DAT_007f46a8 = pfVar18;
  local_4 = local_10;
  pfVar15 = DAT_007f46a8;
  if ((int)local_10 < 3) {
    return local_10;
  }
  DAT_007f46a8 = DAT_007f461c;
  iVar8 = 0;
  DAT_007f46ac = DAT_007f47b8;
  pfVar18 = pfVar16 + local_10 * 3 + -3;
  DAT_007f461c = pfVar15;
  local_10 = 0;
  pfVar17 = DAT_007f47b8;
  if (0 < (int)local_4) {
    pfVar14 = pfVar16 + 2;
    pfVar10 = pfVar15 + local_4 * 2 + -2;
    DAT_007f47b8 = pfVar16;
    do {
      fVar2 = (float)param_1[0xb] * pfVar18[1];
      fVar3 = pfVar14[-1] * (float)param_1[0xb];
      if ((pfVar18[2] <= fVar2) || (*pfVar14 <= fVar3)) {
        iVar9 = iVar8;
        if (((pfVar18[2] != fVar2) && (fVar3 != *pfVar14)) &&
           ((fVar2 < pfVar18[2] || (fVar3 < *pfVar14)))) {
          fVar2 = pfVar14[-1] - pfVar18[1];
          fVar4 = *pfVar14 - pfVar18[2];
          fVar1 = (float)param_1[0xb] * fVar2 - fVar4;
          fVar5 = pfVar18[2] * pfVar14[-1] - pfVar18[1] * *pfVar14;
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
            fVar2 = (fVar1 * fVar5 - pfVar18[2]) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar18[1]) / fVar2;
          }
          iVar9 = iVar8 + 0xc;
          *(float *)((int)pfVar17 + iVar8) = (pfVar14[-2] - *pfVar18) * fVar2 + *pfVar18;
          *(float *)((int)DAT_007f46ac + iVar8 + 4) = fVar5;
          *(float *)((int)DAT_007f46ac + iVar8 + 8) = fVar1 * fVar5;
          DAT_007f46a8[local_10 * 2] = (*pfVar15 - *pfVar10) * fVar2 + *pfVar10;
          DAT_007f46a8[local_10 * 2 + 1] = (pfVar15[1] - pfVar10[1]) * fVar2 + pfVar10[1];
          DAT_007f4ac4 = DAT_007f4ac4 | 4;
          pfVar17 = DAT_007f46ac;
          local_10 = local_10 + 1;
        }
        iVar8 = iVar9;
        if (*pfVar14 <= fVar3) {
          pfVar17 = (float *)((int)pfVar17 + iVar9);
          *pfVar17 = pfVar14[-2];
          pfVar17[1] = pfVar14[-1];
          pfVar17[2] = *pfVar14;
          DAT_007f46a8[local_10 * 2] = *pfVar15;
          DAT_007f46a8[local_10 * 2 + 1] = pfVar15[1];
          local_10 = local_10 + 1;
          iVar8 = iVar9 + 0xc;
          pfVar17 = DAT_007f46ac;
        }
      }
      pfVar18 = pfVar14 + -2;
      pfVar14 = pfVar14 + 3;
      local_4 = local_4 - 1;
      pfVar10 = pfVar15;
      pfVar15 = pfVar15 + 2;
      pfVar16 = DAT_007f47b8;
    } while (local_4 != 0);
  }
  DAT_007f47b8 = pfVar16;
  local_4 = local_10;
  pfVar15 = DAT_007f46a8;
  if ((int)local_10 < 3) {
    return local_10;
  }
  DAT_007f46a8 = DAT_007f461c;
  iVar8 = 0;
  DAT_007f46ac = DAT_007f47b8;
  pfVar18 = pfVar17 + local_10 * 3 + -3;
  DAT_007f461c = pfVar15;
  local_10 = 0;
  pfVar16 = DAT_007f47b8;
  if (0 < (int)local_4) {
    pfVar14 = pfVar17 + 2;
    pfVar10 = pfVar15 + local_4 * 2 + -2;
    DAT_007f47b8 = pfVar17;
    do {
      fVar2 = (float)param_1[8] * pfVar18[1];
      fVar3 = pfVar14[-1] * (float)param_1[8];
      if ((fVar2 <= pfVar18[2]) || (fVar3 <= *pfVar14)) {
        iVar9 = iVar8;
        if (((pfVar18[2] != fVar2) && (fVar3 != *pfVar14)) &&
           ((pfVar18[2] < fVar2 || (*pfVar14 < fVar3)))) {
          fVar2 = pfVar14[-1] - pfVar18[1];
          fVar4 = *pfVar14 - pfVar18[2];
          fVar1 = (float)param_1[8] * fVar2 - fVar4;
          fVar5 = pfVar18[2] * pfVar14[-1] - pfVar18[1] * *pfVar14;
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
            fVar2 = (fVar1 * fVar5 - pfVar18[2]) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar18[1]) / fVar2;
          }
          iVar9 = iVar8 + 0xc;
          *(float *)((int)pfVar16 + iVar8) = (pfVar14[-2] - *pfVar18) * fVar2 + *pfVar18;
          *(float *)((int)DAT_007f46ac + iVar8 + 4) = fVar5;
          *(float *)((int)DAT_007f46ac + iVar8 + 8) = fVar1 * fVar5;
          DAT_007f46a8[local_10 * 2] = (*pfVar15 - *pfVar10) * fVar2 + *pfVar10;
          DAT_007f46a8[local_10 * 2 + 1] = (pfVar15[1] - pfVar10[1]) * fVar2 + pfVar10[1];
          DAT_007f4ac4 = DAT_007f4ac4 | 8;
          pfVar16 = DAT_007f46ac;
          local_10 = local_10 + 1;
        }
        iVar8 = iVar9;
        if (fVar3 <= *pfVar14) {
          pfVar16 = (float *)((int)pfVar16 + iVar9);
          *pfVar16 = pfVar14[-2];
          pfVar16[1] = pfVar14[-1];
          pfVar16[2] = *pfVar14;
          DAT_007f46a8[local_10 * 2] = *pfVar15;
          DAT_007f46a8[local_10 * 2 + 1] = pfVar15[1];
          local_10 = local_10 + 1;
          iVar8 = iVar9 + 0xc;
          pfVar16 = DAT_007f46ac;
        }
      }
      pfVar18 = pfVar14 + -2;
      pfVar14 = pfVar14 + 3;
      local_4 = local_4 - 1;
      pfVar10 = pfVar15;
      pfVar15 = pfVar15 + 2;
      pfVar17 = DAT_007f47b8;
    } while (local_4 != 0);
  }
  DAT_007f47b8 = pfVar17;
  param_4 = DAT_007f46a8;
  if (2 < (int)local_10) {
    DAT_007f46a8 = DAT_007f461c;
    uVar11 = 0;
    DAT_007f46ac = DAT_007f47b8;
    DAT_007f461c = param_4;
    pfVar15 = pfVar16 + local_10 * 3 + -3;
    pfVar18 = DAT_007f47b8;
    if (0 < (int)local_10) {
      pfVar10 = pfVar16 + 1;
      uVar12 = uVar11;
      pfVar17 = param_4 + local_10 * 2 + -2;
      iVar8 = 0;
      DAT_007f47b8 = pfVar16;
      local_4 = local_10;
      do {
        uVar11 = uVar12;
        iVar9 = iVar8;
        if (((float)param_1[1] <= pfVar15[1]) || ((float)param_1[1] <= *pfVar10)) {
          if (((pfVar15[1] != (float)param_1[1]) && (*pfVar10 != (float)param_1[1])) &&
             ((pfVar15[1] < (float)param_1[1] || (*pfVar10 < (float)param_1[1])))) {
            iVar9 = iVar8 + 0xc;
            fVar2 = ((float)param_1[1] - pfVar15[1]) / (*pfVar10 - pfVar15[1]);
            *(int *)((int)pfVar18 + iVar8 + 4) = param_1[1];
            uVar11 = uVar12 + 1;
            *(float *)((int)DAT_007f46ac + iVar8 + 8) =
                 (pfVar10[1] - pfVar15[2]) * fVar2 + pfVar15[2];
            *(float *)((int)DAT_007f46ac + iVar8) = (pfVar10[-1] - *pfVar15) * fVar2 + *pfVar15;
            DAT_007f46a8[uVar12 * 2] = (*param_4 - *pfVar17) * fVar2 + *pfVar17;
            DAT_007f46a8[uVar12 * 2 + 1] = (param_4[1] - pfVar17[1]) * fVar2 + pfVar17[1];
            DAT_007f4ac4 = DAT_007f4ac4 | 1;
            pfVar18 = DAT_007f46ac;
          }
          if ((float)param_1[1] <= *pfVar10) {
            pfVar18 = (float *)((int)pfVar18 + iVar9);
            uVar11 = uVar11 + 1;
            iVar9 = iVar9 + 0xc;
            *pfVar18 = pfVar10[-1];
            pfVar18[1] = *pfVar10;
            pfVar18[2] = pfVar10[1];
            DAT_007f46a8[uVar11 * 2 + -2] = *param_4;
            DAT_007f46a8[uVar11 * 2 + -1] = param_4[1];
            pfVar18 = DAT_007f46ac;
          }
        }
        pfVar15 = pfVar10 + -1;
        pfVar10 = pfVar10 + 3;
        local_4 = local_4 - 1;
        uVar12 = uVar11;
        pfVar17 = param_4;
        iVar8 = iVar9;
        pfVar16 = DAT_007f47b8;
        param_4 = param_4 + 2;
      } while (local_4 != 0);
    }
    DAT_007f47b8 = pfVar16;
    pfVar15 = DAT_007f461c;
    if ((int)uVar11 < 3) {
      DAT_007f4ac4 = DAT_007f4ac4 | 0x40;
      return uVar11;
    }
    uVar12 = uVar11;
    pfVar16 = pfVar18;
    if (*param_1 != 0) {
      uVar12 = 0;
      DAT_007f461c = DAT_007f46a8;
      pfVar17 = pfVar18 + uVar11 * 3 + -3;
      pfVar10 = DAT_007f46a8 + uVar11 * 2 + -2;
      param_4 = DAT_007f46a8;
      pfVar16 = DAT_007f47b8;
      DAT_007f46a8 = pfVar15;
      DAT_007f46ac = DAT_007f47b8;
      if (0 < (int)uVar11) {
        pfVar15 = pfVar18 + 1;
        uVar13 = uVar12;
        iVar8 = 0;
        DAT_007f47b8 = pfVar18;
        local_4 = uVar11;
        do {
          uVar12 = uVar13;
          iVar9 = iVar8;
          if ((pfVar17[1] <= (float)param_1[2]) || (*pfVar15 <= (float)param_1[2])) {
            if (((pfVar17[1] != (float)param_1[2]) && (*pfVar15 != (float)param_1[2])) &&
               (((float)param_1[2] < pfVar17[1] || ((float)param_1[2] < *pfVar15)))) {
              iVar9 = iVar8 + 0xc;
              fVar2 = ((float)param_1[2] - pfVar17[1]) / (*pfVar15 - pfVar17[1]);
              *(int *)((int)pfVar16 + iVar8 + 4) = param_1[2];
              uVar12 = uVar13 + 1;
              *(float *)((int)DAT_007f46ac + iVar8 + 8) =
                   (pfVar15[1] - pfVar17[2]) * fVar2 + pfVar17[2];
              *(float *)((int)DAT_007f46ac + iVar8) = (pfVar15[-1] - *pfVar17) * fVar2 + *pfVar17;
              DAT_007f46a8[uVar13 * 2] = (*param_4 - *pfVar10) * fVar2 + *pfVar10;
              DAT_007f46a8[uVar13 * 2 + 1] = (param_4[1] - pfVar10[1]) * fVar2 + pfVar10[1];
              DAT_007f4ac4 = DAT_007f4ac4 | 2;
              pfVar16 = DAT_007f46ac;
            }
            if (*pfVar15 <= (float)param_1[2]) {
              pfVar16 = (float *)((int)pfVar16 + iVar9);
              uVar12 = uVar12 + 1;
              iVar9 = iVar9 + 0xc;
              *pfVar16 = pfVar15[-1];
              pfVar16[1] = *pfVar15;
              pfVar16[2] = pfVar15[1];
              DAT_007f46a8[uVar12 * 2 + -2] = *param_4;
              DAT_007f46a8[uVar12 * 2 + -1] = param_4[1];
              pfVar16 = DAT_007f46ac;
            }
          }
          pfVar17 = pfVar15 + -1;
          pfVar15 = pfVar15 + 3;
          local_4 = local_4 - 1;
          uVar13 = uVar12;
          pfVar10 = param_4;
          iVar8 = iVar9;
          pfVar18 = DAT_007f47b8;
          param_4 = param_4 + 2;
        } while (local_4 != 0);
      }
      DAT_007f47b8 = pfVar18;
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
      pfVar15 = DAT_007f46a8;
      for (iVar8 = (uVar12 & 0x1fffffff) << 1; iVar8 != 0; iVar8 = iVar8 + -1) {
        *param_3 = *pfVar15;
        pfVar15 = pfVar15 + 1;
        param_3 = param_3 + 1;
      }
      for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
        *(undefined1 *)param_3 = *(undefined1 *)pfVar15;
        pfVar15 = (float *)((int)pfVar15 + 1);
        param_3 = (float *)((int)param_3 + 1);
      }
    }
    return uVar12;
  }
  return local_10;
}
#undef local_10
#undef local_4


/* ---- 0x0044be80  rdClip_Face3_PosUvFlags ---- */
uint rdClip_Face3_PosUvFlags(int *param_1,float *param_2,float *param_3,uint param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float **)(_frame + (0x20 - 0x8)))
  
  DAT_007f4ac4 = 0;
  local_c = 0;
  pfVar7 = (float *)&DAT_007f48c0;
  DAT_007f47b8 = param_2;
  DAT_007f46ac = (float *)&DAT_007f48c0;
  DAT_007f461c = param_3;
  DAT_007f46a8 = (float *)&DAT_007f46b8;
  if (0 < (int)param_4) {
    iVar12 = 0;
    local_8 = (float *)param_4;
    pfVar11 = param_2 + param_4 * 3 + -3;
    pfVar8 = param_2;
    pfVar9 = param_3 + param_4 * 2 + -2;
    pfVar10 = param_3;
    do {
      fVar2 = (float)param_1[3];
      fVar1 = (float)param_1[3];
      if ((fVar2 <= *pfVar11) || (fVar1 <= *pfVar8)) {
        iVar13 = iVar12;
        if (((*pfVar11 != fVar2) && (fVar1 != *pfVar8)) && ((*pfVar11 < fVar2 || (*pfVar8 < fVar1)))
           ) {
          fVar3 = (fVar2 - *pfVar11) / (*pfVar8 - *pfVar11);
          iVar13 = iVar12 + 0xc;
          *(float *)((int)pfVar7 + iVar12) = fVar2;
          *(float *)((int)DAT_007f46ac + iVar12 + 4) = (pfVar8[1] - pfVar11[1]) * fVar3 + pfVar11[1]
          ;
          *(float *)((int)DAT_007f46ac + iVar12 + 8) = (pfVar8[2] - pfVar11[2]) * fVar3 + pfVar11[2]
          ;
          DAT_007f46a8[local_c * 2] = (*pfVar10 - *pfVar9) * fVar3 + *pfVar9;
          DAT_007f46a8[local_c * 2 + 1] = (pfVar10[1] - pfVar9[1]) * fVar3 + pfVar9[1];
          DAT_007f4ac4 = DAT_007f4ac4 | 0x10;
          pfVar7 = DAT_007f46ac;
          local_c = local_c + 1;
        }
        iVar12 = iVar13;
        if (fVar1 <= *pfVar8) {
          pfVar7 = (float *)((int)pfVar7 + iVar13);
          *pfVar7 = *pfVar8;
          pfVar7[1] = pfVar8[1];
          pfVar7[2] = pfVar8[2];
          DAT_007f46a8[local_c * 2] = *pfVar10;
          DAT_007f46a8[local_c * 2 + 1] = pfVar10[1];
          local_c = local_c + 1;
          iVar12 = iVar13 + 0xc;
          pfVar7 = DAT_007f46ac;
        }
      }
      local_8 = (float *)((int)local_8 + -1);
      pfVar11 = pfVar8;
      pfVar8 = pfVar8 + 3;
      pfVar9 = pfVar10;
      pfVar10 = pfVar10 + 2;
    } while (local_8 != (float *)0x0);
  }
  local_8 = (float *)local_c;
  pfVar11 = DAT_007f461c;
  if (2 < (int)local_c) {
    DAT_007f46ac = DAT_007f47b8;
    DAT_007f461c = DAT_007f46a8;
    local_c = 0;
    pfVar8 = DAT_007f47b8;
    if (0 < (int)local_8) {
      iVar12 = 0;
      pfVar9 = pfVar7 + (int)local_8 * 3 + -3;
      pfVar10 = pfVar7;
      pfVar5 = DAT_007f46a8 + (int)local_8 * 2 + -2;
      pfVar6 = DAT_007f46a8;
      DAT_007f46a8 = pfVar11;
      DAT_007f47b8 = pfVar7;
      do {
        fVar2 = (float)param_1[5];
        fVar1 = (float)param_1[5];
        if ((*pfVar9 <= fVar2) || (*pfVar10 <= fVar1)) {
          iVar13 = iVar12;
          if (((*pfVar9 != fVar2) && (fVar1 != *pfVar10)) &&
             ((fVar2 < *pfVar9 || (fVar1 < *pfVar10)))) {
            fVar3 = (fVar2 - *pfVar9) / (*pfVar10 - *pfVar9);
            iVar13 = iVar12 + 0xc;
            *(float *)((int)pfVar8 + iVar12) = fVar2;
            *(float *)((int)DAT_007f46ac + iVar12 + 4) =
                 (pfVar10[1] - pfVar9[1]) * fVar3 + pfVar9[1];
            *(float *)((int)DAT_007f46ac + iVar12 + 8) =
                 (pfVar10[2] - pfVar9[2]) * fVar3 + pfVar9[2];
            DAT_007f46a8[local_c * 2] = (*pfVar6 - *pfVar5) * fVar3 + *pfVar5;
            DAT_007f46a8[local_c * 2 + 1] = (pfVar6[1] - pfVar5[1]) * fVar3 + pfVar5[1];
            DAT_007f4ac4 = DAT_007f4ac4 | 0x20;
            pfVar8 = DAT_007f46ac;
            local_c = local_c + 1;
          }
          iVar12 = iVar13;
          if (*pfVar10 <= fVar1) {
            pfVar8 = (float *)((int)pfVar8 + iVar13);
            *pfVar8 = *pfVar10;
            pfVar8[1] = pfVar10[1];
            pfVar8[2] = pfVar10[2];
            DAT_007f46a8[local_c * 2] = *pfVar6;
            DAT_007f46a8[local_c * 2 + 1] = pfVar6[1];
            local_c = local_c + 1;
            iVar12 = iVar13 + 0xc;
            pfVar8 = DAT_007f46ac;
          }
        }
        local_8 = (float *)((int)local_8 - 1);
        pfVar9 = pfVar10;
        pfVar10 = pfVar10 + 3;
        pfVar5 = pfVar6;
        pfVar6 = pfVar6 + 2;
        pfVar11 = DAT_007f46a8;
        pfVar7 = DAT_007f47b8;
      } while (local_8 != (float *)0x0);
    }
    DAT_007f47b8 = pfVar7;
    DAT_007f46a8 = pfVar11;
    param_4 = local_c;
    pfVar7 = DAT_007f461c;
    if (2 < (int)local_c) {
      DAT_007f46ac = DAT_007f47b8;
      DAT_007f461c = DAT_007f46a8;
      local_c = 0;
      pfVar11 = pfVar8 + param_4 * 3 + -3;
      pfVar9 = DAT_007f47b8;
      if (0 < (int)param_4) {
        pfVar10 = pfVar8 + 2;
        iVar12 = 0;
        pfVar5 = DAT_007f46a8 + param_4 * 2 + -2;
        pfVar6 = DAT_007f46a8;
        DAT_007f46a8 = pfVar7;
        DAT_007f47b8 = pfVar8;
        do {
          fVar2 = (float)param_1[4];
          fVar1 = (float)param_1[4];
          if ((pfVar11[2] <= fVar2) || (*pfVar10 <= fVar1)) {
            iVar13 = iVar12;
            if (((pfVar11[2] != fVar2) && (fVar1 != *pfVar10)) &&
               ((fVar2 < pfVar11[2] || (fVar1 < *pfVar10)))) {
              fVar3 = (fVar2 - pfVar11[2]) / (*pfVar10 - pfVar11[2]);
              iVar13 = iVar12 + 0xc;
              *(float *)((int)pfVar9 + iVar12) = (pfVar10[-2] - *pfVar11) * fVar3 + *pfVar11;
              *(float *)((int)DAT_007f46ac + iVar12 + 4) =
                   (pfVar10[-1] - pfVar11[1]) * fVar3 + pfVar11[1];
              *(float *)((int)DAT_007f46ac + iVar12 + 8) = fVar2;
              DAT_007f46a8[local_c * 2] = (*pfVar6 - *pfVar5) * fVar3 + *pfVar5;
              DAT_007f46a8[local_c * 2 + 1] = (pfVar6[1] - pfVar5[1]) * fVar3 + pfVar5[1];
              DAT_007f4ac4 = DAT_007f4ac4 | 4;
              pfVar9 = DAT_007f46ac;
              local_c = local_c + 1;
            }
            iVar12 = iVar13;
            if (*pfVar10 <= fVar1) {
              pfVar9 = (float *)((int)pfVar9 + iVar13);
              *pfVar9 = pfVar10[-2];
              pfVar9[1] = pfVar10[-1];
              pfVar9[2] = *pfVar10;
              DAT_007f46a8[local_c * 2] = *pfVar6;
              DAT_007f46a8[local_c * 2 + 1] = pfVar6[1];
              local_c = local_c + 1;
              iVar12 = iVar13 + 0xc;
              pfVar9 = DAT_007f46ac;
            }
          }
          pfVar11 = pfVar10 + -2;
          pfVar10 = pfVar10 + 3;
          param_4 = param_4 - 1;
          pfVar5 = pfVar6;
          pfVar6 = pfVar6 + 2;
          pfVar7 = DAT_007f46a8;
          pfVar8 = DAT_007f47b8;
        } while (param_4 != 0);
      }
      DAT_007f47b8 = pfVar8;
      DAT_007f46a8 = pfVar7;
      param_4 = local_c;
      pfVar7 = DAT_007f461c;
      if (2 < (int)local_c) {
        DAT_007f461c = DAT_007f46a8;
        local_c = 0;
        pfVar11 = pfVar9 + param_4 * 3 + -3;
        pfVar8 = DAT_007f47b8;
        DAT_007f46ac = DAT_007f47b8;
        if (0 < (int)param_4) {
          pfVar10 = pfVar9 + 2;
          iVar12 = 0;
          pfVar5 = DAT_007f46a8 + param_4 * 2 + -2;
          pfVar6 = DAT_007f46a8;
          DAT_007f46a8 = pfVar7;
          DAT_007f47b8 = pfVar9;
          do {
            fVar2 = (float)param_1[6];
            fVar1 = (float)param_1[6];
            if ((fVar2 <= pfVar11[2]) || (fVar1 <= *pfVar10)) {
              iVar13 = iVar12;
              if (((pfVar11[2] != fVar2) && (fVar1 != *pfVar10)) &&
                 ((pfVar11[2] < fVar2 || (*pfVar10 < fVar1)))) {
                fVar3 = (fVar2 - pfVar11[2]) / (*pfVar10 - pfVar11[2]);
                iVar13 = iVar12 + 0xc;
                *(float *)((int)pfVar8 + iVar12) = (pfVar10[-2] - *pfVar11) * fVar3 + *pfVar11;
                *(float *)((int)DAT_007f46ac + iVar12 + 4) =
                     (pfVar10[-1] - pfVar11[1]) * fVar3 + pfVar11[1];
                *(float *)((int)DAT_007f46ac + iVar12 + 8) = fVar2;
                DAT_007f46a8[local_c * 2] = (*pfVar6 - *pfVar5) * fVar3 + *pfVar5;
                DAT_007f46a8[local_c * 2 + 1] = (pfVar6[1] - pfVar5[1]) * fVar3 + pfVar5[1];
                DAT_007f4ac4 = DAT_007f4ac4 | 8;
                pfVar8 = DAT_007f46ac;
                local_c = local_c + 1;
              }
              iVar12 = iVar13;
              if (fVar1 <= *pfVar10) {
                pfVar8 = (float *)((int)pfVar8 + iVar13);
                *pfVar8 = pfVar10[-2];
                pfVar8[1] = pfVar10[-1];
                pfVar8[2] = *pfVar10;
                DAT_007f46a8[local_c * 2] = *pfVar6;
                DAT_007f46a8[local_c * 2 + 1] = pfVar6[1];
                local_c = local_c + 1;
                iVar12 = iVar13 + 0xc;
                pfVar8 = DAT_007f46ac;
              }
            }
            pfVar11 = pfVar10 + -2;
            pfVar10 = pfVar10 + 3;
            param_4 = param_4 - 1;
            pfVar5 = pfVar6;
            pfVar6 = pfVar6 + 2;
            pfVar7 = DAT_007f46a8;
            pfVar9 = DAT_007f47b8;
          } while (param_4 != 0);
        }
        DAT_007f47b8 = pfVar9;
        DAT_007f46a8 = pfVar7;
        pfVar7 = DAT_007f461c;
        if ((int)local_c < 3) {
          return local_c;
        }
        uVar4 = 0;
        DAT_007f461c = DAT_007f46a8;
        pfVar11 = pfVar8 + local_c * 3 + -3;
        pfVar9 = DAT_007f46a8 + local_c * 2 + -2;
        local_8 = DAT_007f46a8;
        pfVar10 = DAT_007f47b8;
        DAT_007f46a8 = pfVar7;
        DAT_007f46ac = DAT_007f47b8;
        if (0 < (int)local_c) {
          pfVar7 = pfVar8 + 1;
          iVar12 = 0;
          param_4 = local_c;
          DAT_007f47b8 = pfVar8;
          do {
            if (((float)param_1[1] <= pfVar11[1]) || ((float)param_1[1] <= *pfVar7)) {
              if (((pfVar11[1] != (float)param_1[1]) && (*pfVar7 != (float)param_1[1])) &&
                 ((pfVar11[1] < (float)param_1[1] || (*pfVar7 < (float)param_1[1])))) {
                fVar1 = ((float)param_1[1] - pfVar11[1]) / (*pfVar7 - pfVar11[1]);
                *(int *)((int)pfVar10 + iVar12 + 4) = param_1[1];
                *(float *)((int)DAT_007f46ac + iVar12 + 8) =
                     (pfVar7[1] - pfVar11[2]) * fVar1 + pfVar11[2];
                *(float *)((int)DAT_007f46ac + iVar12) = (pfVar7[-1] - *pfVar11) * fVar1 + *pfVar11;
                DAT_007f46a8[uVar4 * 2] = (*local_8 - *pfVar9) * fVar1 + *pfVar9;
                DAT_007f46a8[uVar4 * 2 + 1] = (local_8[1] - pfVar9[1]) * fVar1 + pfVar9[1];
                DAT_007f4ac4 = DAT_007f4ac4 | 1;
                uVar4 = uVar4 + 1;
                pfVar10 = DAT_007f46ac;
                iVar12 = iVar12 + 0xc;
              }
              if ((float)param_1[1] <= *pfVar7) {
                pfVar10 = (float *)((int)pfVar10 + iVar12);
                uVar4 = uVar4 + 1;
                iVar12 = iVar12 + 0xc;
                *pfVar10 = pfVar7[-1];
                pfVar10[1] = *pfVar7;
                pfVar10[2] = pfVar7[1];
                DAT_007f46a8[uVar4 * 2 + -2] = *local_8;
                DAT_007f46a8[uVar4 * 2 + -1] = local_8[1];
                pfVar10 = DAT_007f46ac;
              }
            }
            pfVar11 = pfVar7 + -1;
            pfVar7 = pfVar7 + 3;
            param_4 = param_4 - 1;
            pfVar9 = local_8;
            pfVar8 = DAT_007f47b8;
            local_8 = local_8 + 2;
          } while (param_4 != 0);
        }
        DAT_007f47b8 = pfVar8;
        pfVar7 = DAT_007f461c;
        if ((int)uVar4 < 3) {
          DAT_007f4ac4 = DAT_007f4ac4 | 0x40;
          return uVar4;
        }
        local_c = uVar4;
        pfVar11 = pfVar10;
        if (*param_1 != 0) {
          local_c = 0;
          DAT_007f46ac = DAT_007f47b8;
          DAT_007f461c = DAT_007f46a8;
          pfVar8 = pfVar10 + uVar4 * 3 + -3;
          pfVar9 = DAT_007f46a8 + uVar4 * 2 + -2;
          local_8 = DAT_007f46a8;
          pfVar11 = DAT_007f47b8;
          DAT_007f46a8 = pfVar7;
          if (0 < (int)uVar4) {
            iVar12 = 0;
            pfVar7 = pfVar10 + 1;
            DAT_007f47b8 = pfVar10;
            param_4 = uVar4;
            do {
              if ((pfVar8[1] <= (float)param_1[2]) || (*pfVar7 <= (float)param_1[2])) {
                if (((pfVar8[1] != (float)param_1[2]) && (*pfVar7 != (float)param_1[2])) &&
                   (((float)param_1[2] < pfVar8[1] || ((float)param_1[2] < *pfVar7)))) {
                  fVar1 = ((float)param_1[2] - pfVar8[1]) / (*pfVar7 - pfVar8[1]);
                  *(int *)((int)pfVar11 + iVar12 + 4) = param_1[2];
                  *(float *)((int)DAT_007f46ac + iVar12 + 8) =
                       (pfVar7[1] - pfVar8[2]) * fVar1 + pfVar8[2];
                  *(float *)((int)DAT_007f46ac + iVar12) = (pfVar7[-1] - *pfVar8) * fVar1 + *pfVar8;
                  DAT_007f46a8[local_c * 2] = (*local_8 - *pfVar9) * fVar1 + *pfVar9;
                  DAT_007f46a8[local_c * 2 + 1] = (local_8[1] - pfVar9[1]) * fVar1 + pfVar9[1];
                  DAT_007f4ac4 = DAT_007f4ac4 | 2;
                  local_c = local_c + 1;
                  iVar12 = iVar12 + 0xc;
                  pfVar11 = DAT_007f46ac;
                }
                if (*pfVar7 <= (float)param_1[2]) {
                  pfVar11 = (float *)((int)pfVar11 + iVar12);
                  local_c = local_c + 1;
                  iVar12 = iVar12 + 0xc;
                  *pfVar11 = pfVar7[-1];
                  pfVar11[1] = *pfVar7;
                  pfVar11[2] = pfVar7[1];
                  DAT_007f46a8[local_c * 2 + -2] = *local_8;
                  DAT_007f46a8[local_c * 2 + -1] = local_8[1];
                  pfVar11 = DAT_007f46ac;
                }
              }
              pfVar8 = pfVar7 + -1;
              pfVar7 = pfVar7 + 3;
              param_4 = param_4 - 1;
              pfVar9 = local_8;
              pfVar10 = DAT_007f47b8;
              local_8 = local_8 + 2;
            } while (param_4 != 0);
          }
          DAT_007f47b8 = pfVar10;
          if ((int)local_c < 3) {
            return local_c;
          }
        }
        if (pfVar11 != param_2) {
          for (uVar4 = local_c * 3 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
            *param_2 = *pfVar11;
            pfVar11 = pfVar11 + 1;
            param_2 = param_2 + 1;
          }
          for (iVar12 = 0; iVar12 != 0; iVar12 = iVar12 + -1) {
            *(undefined1 *)param_2 = *(undefined1 *)pfVar11;
            pfVar11 = (float *)((int)pfVar11 + 1);
            param_2 = (float *)((int)param_2 + 1);
          }
          pfVar7 = DAT_007f46a8;
          for (iVar12 = (local_c & 0x1fffffff) << 1; iVar12 != 0; iVar12 = iVar12 + -1) {
            *param_3 = *pfVar7;
            pfVar7 = pfVar7 + 1;
            param_3 = param_3 + 1;
          }
          for (iVar12 = 0; iVar12 != 0; iVar12 = iVar12 + -1) {
            *(undefined1 *)param_3 = *(undefined1 *)pfVar7;
            pfVar7 = (float *)((int)pfVar7 + 1);
            param_3 = (float *)((int)param_3 + 1);
          }
        }
      }
    }
  }
  return local_c;
}
#undef local_8
#undef local_c


/* ---- 0x0044c9d0  rdClip_Face3_PosUvLitColor ---- */
uint rdClip_Face3_PosUvLitColor
               (int *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

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
  float *pfVar10;
  int iVar11;
  int iVar12;
  float *pfVar13;
  float *pfVar14;
  float *pfVar15;
  float *pfVar16;
  float *pfVar17;
  float *pfVar18;
  #define local_18 (*(float **)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float **)(_frame + (0x30 - 0x14)))
  #define local_c (*(float **)(_frame + (0x30 - 0xc)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  DAT_007f4618 = param_4;
  local_14 = param_4 + (int)param_5 + -1;
  uVar8 = 0;
  pfVar15 = (float *)&DAT_007f48c0;
  DAT_007f4ac4 = 0;
  DAT_007f47b8 = param_2;
  DAT_007f46ac = (float *)&DAT_007f48c0;
  DAT_007f461c = param_3;
  DAT_007f46a8 = (float *)&DAT_007f46b8;
  DAT_007f46b0 = (float *)&DAT_007f47c0;
  local_18 = param_4;
  if (0 < (int)param_5) {
    iVar11 = 0;
    local_4 = (uint)param_5;
    pfVar18 = param_2;
    pfVar16 = param_3;
    pfVar17 = param_3 + (int)param_5 * 2 + -2;
    param_5 = param_2 + (int)param_5 * 3 + -3;
    do {
      pfVar14 = pfVar16;
      pfVar10 = pfVar18;
      fVar2 = (float)param_1[0xc] * param_5[1];
      fVar3 = (float)param_1[0xc] * pfVar10[1];
      if ((fVar2 <= *param_5) || (fVar3 <= *pfVar10)) {
        uVar9 = uVar8;
        iVar12 = iVar11;
        if (((*param_5 != fVar2) && (fVar3 != *pfVar10)) &&
           ((*param_5 < fVar2 || (*pfVar10 < fVar3)))) {
          fVar2 = pfVar10[1] - param_5[1];
          fVar4 = *pfVar10 - *param_5;
          fVar1 = (float)param_1[0xc] * fVar2 - fVar4;
          fVar5 = pfVar10[1] * *param_5 - param_5[1] * *pfVar10;
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
          *(float *)((int)pfVar15 + iVar11) = (float)param_1[0xc] * fVar5;
          iVar12 = iVar11 + 0xc;
          *(float *)((int)DAT_007f46ac + iVar11 + 4) = fVar5;
          uVar9 = uVar8 + 1;
          *(float *)((int)DAT_007f46ac + iVar11 + 8) =
               (pfVar10[2] - param_5[2]) * fVar2 + param_5[2];
          DAT_007f46a8[uVar9 * 2 + -2] = (*pfVar14 - *pfVar17) * fVar2 + *pfVar17;
          DAT_007f46a8[uVar9 * 2 + -1] = (pfVar14[1] - pfVar17[1]) * fVar2 + pfVar17[1];
          DAT_007f46b0[uVar8] = (*local_18 - *local_14) * fVar2 + *local_14;
          DAT_007f4ac4 = DAT_007f4ac4 | 0x10;
          pfVar15 = DAT_007f46ac;
        }
        uVar8 = uVar9;
        iVar11 = iVar12;
        if (fVar3 <= *pfVar10) {
          pfVar15 = (float *)((int)pfVar15 + iVar12);
          uVar8 = uVar9 + 1;
          iVar11 = iVar12 + 0xc;
          *pfVar15 = *pfVar10;
          pfVar15[1] = pfVar10[1];
          pfVar15[2] = pfVar10[2];
          DAT_007f46a8[uVar8 * 2 + -2] = *pfVar14;
          DAT_007f46a8[uVar8 * 2 + -1] = pfVar14[1];
          DAT_007f46b0[uVar9] = *local_18;
          pfVar15 = DAT_007f46ac;
        }
      }
      local_14 = local_18;
      local_18 = local_18 + 1;
      local_4 = local_4 + -1;
      pfVar18 = pfVar10 + 3;
      pfVar16 = pfVar14 + 2;
      pfVar17 = pfVar14;
      param_5 = pfVar10;
    } while (local_4 != 0);
  }
  local_18 = DAT_007f46b0;
  pfVar18 = DAT_007f461c;
  if ((int)uVar8 < 3) {
    return uVar8;
  }
  DAT_007f461c = DAT_007f46a8;
  DAT_007f46b0 = DAT_007f4618;
  DAT_007f4618 = local_18;
  uVar9 = 0;
  local_14 = local_18 + (uVar8 - 1);
  pfVar16 = DAT_007f47b8;
  DAT_007f46ac = DAT_007f47b8;
  if (0 < (int)uVar8) {
    iVar11 = 0;
    pfVar17 = DAT_007f46a8;
    pfVar10 = pfVar15;
    pfVar14 = DAT_007f46a8 + uVar8 * 2 + -2;
    DAT_007f46a8 = pfVar18;
    DAT_007f47b8 = pfVar15;
    param_5 = pfVar15 + uVar8 * 3 + -3;
    local_4 = uVar8;
    do {
      pfVar13 = pfVar10;
      pfVar15 = pfVar17;
      fVar2 = (float)param_1[10] * param_5[1];
      fVar3 = (float)param_1[10] * pfVar13[1];
      if ((*param_5 <= fVar2) || (*pfVar13 <= fVar3)) {
        uVar8 = uVar9;
        iVar12 = iVar11;
        if (((*param_5 != fVar2) && (fVar3 != *pfVar13)) &&
           ((fVar2 < *param_5 || (fVar3 < *pfVar13)))) {
          fVar2 = pfVar13[1] - param_5[1];
          fVar4 = *pfVar13 - *param_5;
          fVar1 = (float)param_1[10] * fVar2 - fVar4;
          fVar5 = pfVar13[1] * *param_5 - param_5[1] * *pfVar13;
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
          *(float *)((int)pfVar16 + iVar11) = (float)param_1[10] * fVar5;
          iVar12 = iVar11 + 0xc;
          *(float *)((int)DAT_007f46ac + iVar11 + 4) = fVar5;
          uVar8 = uVar9 + 1;
          *(float *)((int)DAT_007f46ac + iVar11 + 8) =
               (pfVar13[2] - param_5[2]) * fVar2 + param_5[2];
          DAT_007f46a8[uVar8 * 2 + -2] = (*pfVar15 - *pfVar14) * fVar2 + *pfVar14;
          DAT_007f46a8[uVar8 * 2 + -1] = (pfVar15[1] - pfVar14[1]) * fVar2 + pfVar14[1];
          DAT_007f46b0[uVar9] = (*local_18 - *local_14) * fVar2 + *local_14;
          DAT_007f4ac4 = DAT_007f4ac4 | 0x20;
          pfVar16 = DAT_007f46ac;
        }
        uVar9 = uVar8;
        iVar11 = iVar12;
        if (*pfVar13 <= fVar3) {
          pfVar16 = (float *)((int)pfVar16 + iVar12);
          uVar9 = uVar8 + 1;
          iVar11 = iVar12 + 0xc;
          *pfVar16 = *pfVar13;
          pfVar16[1] = pfVar13[1];
          pfVar16[2] = pfVar13[2];
          DAT_007f46a8[uVar9 * 2 + -2] = *pfVar15;
          DAT_007f46a8[uVar9 * 2 + -1] = pfVar15[1];
          DAT_007f46b0[uVar8] = *local_18;
          pfVar16 = DAT_007f46ac;
        }
      }
      local_14 = local_18;
      local_18 = local_18 + 1;
      local_4 = local_4 - 1;
      pfVar17 = pfVar15 + 2;
      pfVar10 = pfVar13 + 3;
      pfVar14 = pfVar15;
      pfVar18 = DAT_007f46a8;
      pfVar15 = DAT_007f47b8;
      param_5 = pfVar13;
    } while (local_4 != 0);
  }
  DAT_007f47b8 = pfVar15;
  DAT_007f46a8 = pfVar18;
  local_18 = DAT_007f46b0;
  pfVar18 = DAT_007f46a8;
  pfVar15 = DAT_007f4618;
  if (2 < (int)uVar9) {
    DAT_007f46a8 = DAT_007f461c;
    DAT_007f4618 = DAT_007f46b0;
    DAT_007f461c = pfVar18;
    DAT_007f46b0 = pfVar15;
    uVar8 = 0;
    DAT_007f46ac = DAT_007f47b8;
    pfVar15 = pfVar16 + uVar9 * 3 + -3;
    local_14 = local_18 + (uVar9 - 1);
    pfVar17 = DAT_007f47b8;
    if (0 < (int)uVar9) {
      iVar11 = 0;
      local_c = pfVar16 + 2;
      pfVar10 = pfVar18 + uVar9 * 2 + -2;
      DAT_007f47b8 = pfVar16;
      local_4 = uVar9;
      do {
        pfVar16 = pfVar18;
        fVar2 = (float)param_1[0xb] * pfVar15[1];
        fVar3 = (float)param_1[0xb] * local_c[-1];
        if ((pfVar15[2] <= fVar2) || (*local_c <= fVar3)) {
          uVar9 = uVar8;
          iVar12 = iVar11;
          if (((pfVar15[2] != fVar2) && (fVar3 != *local_c)) &&
             ((fVar2 < pfVar15[2] || (fVar3 < *local_c)))) {
            fVar2 = local_c[-1] - pfVar15[1];
            fVar4 = *local_c - pfVar15[2];
            fVar1 = (float)param_1[0xb] * fVar2 - fVar4;
            fVar5 = pfVar15[2] * local_c[-1] - pfVar15[1] * *local_c;
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
            iVar12 = iVar11 + 0xc;
            uVar9 = uVar8 + 1;
            *(float *)((int)pfVar17 + iVar11) = (local_c[-2] - *pfVar15) * fVar2 + *pfVar15;
            *(float *)((int)DAT_007f46ac + iVar11 + 4) = fVar5;
            *(float *)((int)DAT_007f46ac + iVar11 + 8) = fVar1 * fVar5;
            DAT_007f46a8[uVar9 * 2 + -2] = (*pfVar16 - *pfVar10) * fVar2 + *pfVar10;
            DAT_007f46a8[uVar9 * 2 + -1] = (pfVar16[1] - pfVar10[1]) * fVar2 + pfVar10[1];
            DAT_007f46b0[uVar8] = (*local_18 - *local_14) * fVar2 + *local_14;
            DAT_007f4ac4 = DAT_007f4ac4 | 4;
            pfVar17 = DAT_007f46ac;
          }
          uVar8 = uVar9;
          iVar11 = iVar12;
          if (*local_c <= fVar3) {
            pfVar17 = (float *)((int)pfVar17 + iVar12);
            uVar8 = uVar9 + 1;
            iVar11 = iVar12 + 0xc;
            *pfVar17 = local_c[-2];
            pfVar17[1] = local_c[-1];
            pfVar17[2] = *local_c;
            DAT_007f46a8[uVar8 * 2 + -2] = *pfVar16;
            DAT_007f46a8[uVar8 * 2 + -1] = pfVar16[1];
            DAT_007f46b0[uVar9] = *local_18;
            pfVar17 = DAT_007f46ac;
          }
        }
        pfVar15 = local_c + -2;
        local_c = local_c + 3;
        local_14 = local_18;
        local_18 = local_18 + 1;
        local_4 = local_4 - 1;
        pfVar18 = pfVar16 + 2;
        pfVar10 = pfVar16;
        pfVar16 = DAT_007f47b8;
      } while (local_4 != 0);
    }
    DAT_007f47b8 = pfVar16;
    local_18 = DAT_007f46b0;
    pfVar15 = DAT_007f46a8;
    if ((int)uVar8 < 3) {
      return uVar8;
    }
    DAT_007f46a8 = DAT_007f461c;
    DAT_007f46b0 = DAT_007f4618;
    DAT_007f4618 = local_18;
    uVar9 = 0;
    local_14 = local_18 + (uVar8 - 1);
    pfVar18 = pfVar17 + uVar8 * 3 + -3;
    DAT_007f46ac = DAT_007f47b8;
    DAT_007f461c = pfVar15;
    pfVar16 = DAT_007f47b8;
    if (0 < (int)uVar8) {
      iVar11 = 0;
      local_c = pfVar17 + 2;
      pfVar10 = pfVar15 + uVar8 * 2 + -2;
      DAT_007f47b8 = pfVar17;
      local_4 = uVar8;
      do {
        pfVar17 = pfVar15;
        fVar2 = (float)param_1[8] * pfVar18[1];
        fVar3 = (float)param_1[8] * local_c[-1];
        if ((fVar2 <= pfVar18[2]) || (fVar3 <= *local_c)) {
          uVar8 = uVar9;
          iVar12 = iVar11;
          if (((pfVar18[2] != fVar2) && (fVar3 != *local_c)) &&
             ((pfVar18[2] < fVar2 || (*local_c < fVar3)))) {
            fVar2 = local_c[-1] - pfVar18[1];
            fVar4 = *local_c - pfVar18[2];
            fVar1 = (float)param_1[8] * fVar2 - fVar4;
            fVar5 = pfVar18[2] * local_c[-1] - pfVar18[1] * *local_c;
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
              fVar2 = (fVar1 * fVar5 - pfVar18[2]) / fVar4;
            }
            else {
              fVar2 = (fVar5 - pfVar18[1]) / fVar2;
            }
            iVar12 = iVar11 + 0xc;
            uVar8 = uVar9 + 1;
            *(float *)((int)pfVar16 + iVar11) = (local_c[-2] - *pfVar18) * fVar2 + *pfVar18;
            *(float *)((int)DAT_007f46ac + iVar11 + 4) = fVar5;
            *(float *)((int)DAT_007f46ac + iVar11 + 8) = fVar1 * fVar5;
            DAT_007f46a8[uVar8 * 2 + -2] = (*pfVar17 - *pfVar10) * fVar2 + *pfVar10;
            DAT_007f46a8[uVar8 * 2 + -1] = (pfVar17[1] - pfVar10[1]) * fVar2 + pfVar10[1];
            DAT_007f46b0[uVar9] = (*local_18 - *local_14) * fVar2 + *local_14;
            DAT_007f4ac4 = DAT_007f4ac4 | 8;
            pfVar16 = DAT_007f46ac;
          }
          uVar9 = uVar8;
          iVar11 = iVar12;
          if (fVar3 <= *local_c) {
            pfVar16 = (float *)((int)pfVar16 + iVar12);
            uVar9 = uVar8 + 1;
            iVar11 = iVar12 + 0xc;
            *pfVar16 = local_c[-2];
            pfVar16[1] = local_c[-1];
            pfVar16[2] = *local_c;
            DAT_007f46a8[uVar9 * 2 + -2] = *pfVar17;
            DAT_007f46a8[uVar9 * 2 + -1] = pfVar17[1];
            DAT_007f46b0[uVar8] = *local_18;
            pfVar16 = DAT_007f46ac;
          }
        }
        pfVar18 = local_c + -2;
        local_c = local_c + 3;
        local_14 = local_18;
        local_18 = local_18 + 1;
        local_4 = local_4 - 1;
        pfVar15 = pfVar17 + 2;
        pfVar10 = pfVar17;
        pfVar17 = DAT_007f47b8;
      } while (local_4 != 0);
    }
    DAT_007f47b8 = pfVar17;
    local_18 = DAT_007f46b0;
    param_5 = DAT_007f46a8;
    if ((int)uVar9 < 3) {
      return uVar9;
    }
    DAT_007f46a8 = DAT_007f461c;
    DAT_007f46b0 = DAT_007f4618;
    DAT_007f461c = param_5;
    DAT_007f4618 = local_18;
    uVar8 = 0;
    local_14 = local_18 + (uVar9 - 1);
    pfVar15 = pfVar16 + uVar9 * 3 + -3;
    DAT_007f46ac = DAT_007f47b8;
    pfVar18 = DAT_007f47b8;
    if (0 < (int)uVar9) {
      pfVar10 = pfVar16 + 1;
      pfVar17 = param_5 + uVar9 * 2 + -2;
      iVar11 = 0;
      DAT_007f47b8 = pfVar16;
      local_4 = uVar9;
      do {
        iVar12 = iVar11;
        if (((float)param_1[1] <= pfVar15[1]) || ((float)param_1[1] <= *pfVar10)) {
          uVar9 = uVar8;
          if (((pfVar15[1] != (float)param_1[1]) && (*pfVar10 != (float)param_1[1])) &&
             ((pfVar15[1] < (float)param_1[1] || (*pfVar10 < (float)param_1[1])))) {
            iVar12 = iVar11 + 0xc;
            uVar9 = uVar8 + 1;
            fVar2 = ((float)param_1[1] - pfVar15[1]) / (*pfVar10 - pfVar15[1]);
            *(int *)((int)pfVar18 + iVar11 + 4) = param_1[1];
            *(float *)((int)DAT_007f46ac + iVar11 + 8) =
                 (pfVar10[1] - pfVar15[2]) * fVar2 + pfVar15[2];
            *(float *)((int)DAT_007f46ac + iVar11) = (pfVar10[-1] - *pfVar15) * fVar2 + *pfVar15;
            DAT_007f46a8[uVar9 * 2 + -2] = (*param_5 - *pfVar17) * fVar2 + *pfVar17;
            DAT_007f46a8[uVar9 * 2 + -1] = (param_5[1] - pfVar17[1]) * fVar2 + pfVar17[1];
            DAT_007f46b0[uVar8] = (*local_18 - *local_14) * fVar2 + *local_14;
            DAT_007f4ac4 = DAT_007f4ac4 | 1;
            pfVar18 = DAT_007f46ac;
          }
          uVar8 = uVar9;
          if ((float)param_1[1] <= *pfVar10) {
            pfVar18 = (float *)((int)pfVar18 + iVar12);
            uVar8 = uVar9 + 1;
            iVar12 = iVar12 + 0xc;
            *pfVar18 = pfVar10[-1];
            pfVar18[1] = *pfVar10;
            pfVar18[2] = pfVar10[1];
            DAT_007f46a8[uVar8 * 2 + -2] = *param_5;
            DAT_007f46a8[uVar8 * 2 + -1] = param_5[1];
            DAT_007f46b0[uVar9] = *local_18;
            pfVar18 = DAT_007f46ac;
          }
        }
        pfVar15 = pfVar10 + -1;
        local_14 = local_18;
        local_18 = local_18 + 1;
        pfVar10 = pfVar10 + 3;
        local_4 = local_4 - 1;
        pfVar17 = param_5;
        iVar11 = iVar12;
        pfVar16 = DAT_007f47b8;
        param_5 = param_5 + 2;
      } while (local_4 != 0);
    }
    DAT_007f47b8 = pfVar16;
    pfVar16 = DAT_007f461c;
    pfVar15 = DAT_007f4618;
    if ((int)uVar8 < 3) {
      DAT_007f4ac4 = DAT_007f4ac4 | 0x40;
      return uVar8;
    }
    uVar9 = uVar8;
    pfVar17 = pfVar18;
    if (*param_1 != 0) {
      DAT_007f461c = DAT_007f46a8;
      DAT_007f4618 = DAT_007f46b0;
      uVar9 = 0;
      param_5 = DAT_007f46a8;
      local_14 = DAT_007f46b0 + (uVar8 - 1);
      pfVar10 = pfVar18 + uVar8 * 3 + -3;
      pfVar14 = DAT_007f46a8 + uVar8 * 2 + -2;
      local_18 = DAT_007f46b0;
      pfVar17 = DAT_007f47b8;
      DAT_007f46a8 = pfVar16;
      DAT_007f46ac = DAT_007f47b8;
      DAT_007f46b0 = pfVar15;
      if (0 < (int)uVar8) {
        pfVar15 = pfVar18 + 1;
        iVar11 = 0;
        DAT_007f47b8 = pfVar18;
        local_4 = uVar8;
        do {
          iVar12 = iVar11;
          if ((pfVar10[1] <= (float)param_1[2]) || (*pfVar15 <= (float)param_1[2])) {
            uVar8 = uVar9;
            if (((pfVar10[1] != (float)param_1[2]) && (*pfVar15 != (float)param_1[2])) &&
               (((float)param_1[2] < pfVar10[1] || ((float)param_1[2] < *pfVar15)))) {
              iVar12 = iVar11 + 0xc;
              uVar8 = uVar9 + 1;
              fVar2 = ((float)param_1[2] - pfVar10[1]) / (*pfVar15 - pfVar10[1]);
              *(int *)((int)pfVar17 + iVar11 + 4) = param_1[2];
              *(float *)((int)DAT_007f46ac + iVar11 + 8) =
                   (pfVar15[1] - pfVar10[2]) * fVar2 + pfVar10[2];
              *(float *)((int)DAT_007f46ac + iVar11) = (pfVar15[-1] - *pfVar10) * fVar2 + *pfVar10;
              DAT_007f46a8[uVar8 * 2 + -2] = (*param_5 - *pfVar14) * fVar2 + *pfVar14;
              DAT_007f46a8[uVar8 * 2 + -1] = (param_5[1] - pfVar14[1]) * fVar2 + pfVar14[1];
              DAT_007f46b0[uVar9] = (*local_18 - *local_14) * fVar2 + *local_14;
              DAT_007f4ac4 = DAT_007f4ac4 | 2;
              pfVar17 = DAT_007f46ac;
            }
            uVar9 = uVar8;
            if (*pfVar15 <= (float)param_1[2]) {
              pfVar17 = (float *)((int)pfVar17 + iVar12);
              uVar9 = uVar8 + 1;
              iVar12 = iVar12 + 0xc;
              *pfVar17 = pfVar15[-1];
              pfVar17[1] = *pfVar15;
              pfVar17[2] = pfVar15[1];
              DAT_007f46a8[uVar9 * 2 + -2] = *param_5;
              DAT_007f46a8[uVar9 * 2 + -1] = param_5[1];
              DAT_007f46b0[uVar8] = *local_18;
              pfVar17 = DAT_007f46ac;
            }
          }
          pfVar10 = pfVar15 + -1;
          local_14 = local_18;
          local_18 = local_18 + 1;
          pfVar15 = pfVar15 + 3;
          local_4 = local_4 - 1;
          pfVar14 = param_5;
          iVar11 = iVar12;
          pfVar18 = DAT_007f47b8;
          param_5 = param_5 + 2;
        } while (local_4 != 0);
      }
      DAT_007f47b8 = pfVar18;
      if ((int)uVar9 < 3) {
        return uVar9;
      }
    }
    if (pfVar17 != param_2) {
      for (uVar8 = uVar9 * 3 & 0x3fffffff; uVar8 != 0; uVar8 = uVar8 - 1) {
        *param_2 = *pfVar17;
        pfVar17 = pfVar17 + 1;
        param_2 = param_2 + 1;
      }
      for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)param_2 = *(undefined1 *)pfVar17;
        pfVar17 = (float *)((int)pfVar17 + 1);
        param_2 = (float *)((int)param_2 + 1);
      }
      pfVar15 = DAT_007f46a8;
      for (iVar11 = (uVar9 & 0x1fffffff) << 1; iVar11 != 0; iVar11 = iVar11 + -1) {
        *param_3 = *pfVar15;
        pfVar15 = pfVar15 + 1;
        param_3 = param_3 + 1;
      }
      for (iVar11 = 0; uVar8 = uVar9, pfVar18 = DAT_007f46b0, iVar11 != 0; iVar11 = iVar11 + -1) {
        *(undefined1 *)param_3 = *(undefined1 *)pfVar15;
        pfVar15 = (float *)((int)pfVar15 + 1);
        param_3 = (float *)((int)param_3 + 1);
      }
      for (; uVar8 != 0; uVar8 = uVar8 - 1) {
        *param_4 = *pfVar18;
        pfVar18 = pfVar18 + 1;
        param_4 = param_4 + 1;
      }
    }
  }
  return uVar9;
}
#undef local_14
#undef local_18
#undef local_4
#undef local_c


/* ---- 0x0044da40  rdClip_Face3_PosUvLitFlags ---- */
uint rdClip_Face3_PosUvLitFlags
               (int *param_1,float *param_2,float *param_3,float *param_4,uint param_5)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  float *pfVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  float *pfVar12;
  int iVar13;
  #define local_14 (*(float **)(_frame + (0x30 - 0x14)))
  #define local_10 (*(float **)(_frame + (0x30 - 0x10)))
  #define local_c (*(float **)(_frame + (0x30 - 0xc)))
  
  DAT_007f4618 = param_4;
  DAT_007f47b8 = param_2;
  uVar6 = 0;
  pfVar9 = (float *)&DAT_007f48c0;
  local_c = param_4 + param_5 + -1;
  local_10 = param_3;
  local_14 = param_4;
  DAT_007f4ac4 = 0;
  DAT_007f46ac = (float *)&DAT_007f48c0;
  DAT_007f461c = param_3;
  DAT_007f46a8 = (float *)&DAT_007f46b8;
  DAT_007f46b0 = (float *)&DAT_007f47c0;
  if (0 < (int)param_5) {
    iVar13 = 0;
    pfVar4 = param_2 + param_5 * 3 + -3;
    pfVar12 = param_2;
    pfVar5 = param_3 + param_5 * 2 + -2;
    do {
      fVar2 = (float)param_1[3];
      fVar1 = (float)param_1[3];
      if ((fVar2 <= *pfVar4) || (fVar1 <= *pfVar12)) {
        if (((*pfVar4 != fVar2) && (fVar1 != *pfVar12)) && ((*pfVar4 < fVar2 || (*pfVar12 < fVar1)))
           ) {
          fVar3 = (fVar2 - *pfVar4) / (*pfVar12 - *pfVar4);
          uVar7 = uVar6 + 1;
          *(float *)((int)pfVar9 + iVar13) = fVar2;
          *(float *)((int)DAT_007f46ac + iVar13 + 4) = (pfVar12[1] - pfVar4[1]) * fVar3 + pfVar4[1];
          *(float *)((int)DAT_007f46ac + iVar13 + 8) = (pfVar12[2] - pfVar4[2]) * fVar3 + pfVar4[2];
          DAT_007f46a8[uVar7 * 2 + -2] = (*local_10 - *pfVar5) * fVar3 + *pfVar5;
          DAT_007f46a8[uVar7 * 2 + -1] = (local_10[1] - pfVar5[1]) * fVar3 + pfVar5[1];
          DAT_007f46b0[uVar6] = (*local_14 - *local_c) * fVar3 + *local_c;
          DAT_007f4ac4 = DAT_007f4ac4 | 0x10;
          uVar6 = uVar7;
          pfVar9 = DAT_007f46ac;
          iVar13 = iVar13 + 0xc;
        }
        if (fVar1 <= *pfVar12) {
          pfVar9 = (float *)((int)pfVar9 + iVar13);
          uVar7 = uVar6 + 1;
          iVar13 = iVar13 + 0xc;
          *pfVar9 = *pfVar12;
          pfVar9[1] = pfVar12[1];
          pfVar9[2] = pfVar12[2];
          DAT_007f46a8[uVar7 * 2 + -2] = *local_10;
          DAT_007f46a8[uVar7 * 2 + -1] = local_10[1];
          DAT_007f46b0[uVar6] = *local_14;
          uVar6 = uVar7;
          pfVar9 = DAT_007f46ac;
        }
      }
      local_c = local_14;
      local_14 = local_14 + 1;
      param_5 = param_5 + -1;
      pfVar4 = pfVar12;
      pfVar12 = pfVar12 + 3;
      pfVar5 = local_10;
      local_10 = local_10 + 2;
    } while (param_5 != 0);
  }
  pfVar12 = DAT_007f461c;
  pfVar4 = DAT_007f4618;
  if (2 < (int)uVar6) {
    pfVar5 = DAT_007f46a8 + uVar6 * 2 + -2;
    local_c = DAT_007f46b0 + (uVar6 - 1);
    uVar7 = 0;
    DAT_007f461c = DAT_007f46a8;
    DAT_007f4618 = DAT_007f46b0;
    local_10 = DAT_007f46a8;
    local_14 = DAT_007f46b0;
    pfVar10 = DAT_007f47b8;
    DAT_007f46a8 = pfVar12;
    DAT_007f46ac = DAT_007f47b8;
    DAT_007f46b0 = pfVar4;
    if (0 < (int)uVar6) {
      iVar13 = 0;
      pfVar4 = pfVar9 + uVar6 * 3 + -3;
      pfVar12 = pfVar9;
      DAT_007f47b8 = pfVar9;
      param_5 = uVar6;
      do {
        fVar2 = (float)param_1[5];
        fVar1 = (float)param_1[5];
        if ((*pfVar4 <= fVar2) || (*pfVar12 <= fVar1)) {
          if (((*pfVar4 != fVar2) && (fVar1 != *pfVar12)) &&
             ((fVar2 < *pfVar4 || (fVar1 < *pfVar12)))) {
            fVar3 = (fVar2 - *pfVar4) / (*pfVar12 - *pfVar4);
            uVar6 = uVar7 + 1;
            *(float *)((int)pfVar10 + iVar13) = fVar2;
            *(float *)((int)DAT_007f46ac + iVar13 + 4) =
                 (pfVar12[1] - pfVar4[1]) * fVar3 + pfVar4[1];
            *(float *)((int)DAT_007f46ac + iVar13 + 8) =
                 (pfVar12[2] - pfVar4[2]) * fVar3 + pfVar4[2];
            DAT_007f46a8[uVar6 * 2 + -2] = (*local_10 - *pfVar5) * fVar3 + *pfVar5;
            DAT_007f46a8[uVar6 * 2 + -1] = (local_10[1] - pfVar5[1]) * fVar3 + pfVar5[1];
            DAT_007f46b0[uVar7] = (*local_14 - *local_c) * fVar3 + *local_c;
            DAT_007f4ac4 = DAT_007f4ac4 | 0x20;
            uVar7 = uVar6;
            pfVar10 = DAT_007f46ac;
            iVar13 = iVar13 + 0xc;
          }
          if (*pfVar12 <= fVar1) {
            pfVar10 = (float *)((int)pfVar10 + iVar13);
            uVar6 = uVar7 + 1;
            iVar13 = iVar13 + 0xc;
            *pfVar10 = *pfVar12;
            pfVar10[1] = pfVar12[1];
            pfVar10[2] = pfVar12[2];
            DAT_007f46a8[uVar6 * 2 + -2] = *local_10;
            DAT_007f46a8[uVar6 * 2 + -1] = local_10[1];
            DAT_007f46b0[uVar7] = *local_14;
            uVar7 = uVar6;
            pfVar10 = DAT_007f46ac;
          }
        }
        local_c = local_14;
        local_14 = local_14 + 1;
        param_5 = param_5 - 1;
        pfVar4 = pfVar12;
        pfVar12 = pfVar12 + 3;
        pfVar5 = local_10;
        pfVar9 = DAT_007f47b8;
        local_10 = local_10 + 2;
      } while (param_5 != 0);
    }
    DAT_007f47b8 = pfVar9;
    pfVar4 = DAT_007f461c;
    pfVar9 = DAT_007f4618;
    if ((int)uVar7 < 3) {
      return uVar7;
    }
    pfVar12 = pfVar10 + uVar7 * 3 + -3;
    pfVar5 = DAT_007f46a8 + uVar7 * 2 + -2;
    local_c = DAT_007f46b0 + (uVar7 - 1);
    uVar6 = 0;
    DAT_007f46ac = DAT_007f47b8;
    DAT_007f461c = DAT_007f46a8;
    DAT_007f4618 = DAT_007f46b0;
    local_10 = DAT_007f46a8;
    local_14 = DAT_007f46b0;
    pfVar11 = DAT_007f47b8;
    DAT_007f46a8 = pfVar4;
    DAT_007f46b0 = pfVar9;
    if (0 < (int)uVar7) {
      iVar13 = 0;
      pfVar9 = pfVar10 + 2;
      DAT_007f47b8 = pfVar10;
      param_5 = uVar7;
      do {
        fVar2 = (float)param_1[4];
        fVar1 = (float)param_1[4];
        if ((pfVar12[2] <= fVar2) || (*pfVar9 <= fVar1)) {
          if (((pfVar12[2] != fVar2) && (fVar1 != *pfVar9)) &&
             ((fVar2 < pfVar12[2] || (fVar1 < *pfVar9)))) {
            fVar3 = (fVar2 - pfVar12[2]) / (*pfVar9 - pfVar12[2]);
            uVar7 = uVar6 + 1;
            *(float *)((int)pfVar11 + iVar13) = (pfVar9[-2] - *pfVar12) * fVar3 + *pfVar12;
            *(float *)((int)DAT_007f46ac + iVar13 + 4) =
                 (pfVar9[-1] - pfVar12[1]) * fVar3 + pfVar12[1];
            *(float *)((int)DAT_007f46ac + iVar13 + 8) = fVar2;
            DAT_007f46a8[uVar7 * 2 + -2] = (*local_10 - *pfVar5) * fVar3 + *pfVar5;
            DAT_007f46a8[uVar7 * 2 + -1] = (local_10[1] - pfVar5[1]) * fVar3 + pfVar5[1];
            DAT_007f46b0[uVar6] = (*local_14 - *local_c) * fVar3 + *local_c;
            DAT_007f4ac4 = DAT_007f4ac4 | 4;
            uVar6 = uVar7;
            iVar13 = iVar13 + 0xc;
            pfVar11 = DAT_007f46ac;
          }
          if (*pfVar9 <= fVar1) {
            pfVar11 = (float *)((int)pfVar11 + iVar13);
            uVar7 = uVar6 + 1;
            iVar13 = iVar13 + 0xc;
            *pfVar11 = pfVar9[-2];
            pfVar11[1] = pfVar9[-1];
            pfVar11[2] = *pfVar9;
            DAT_007f46a8[uVar7 * 2 + -2] = *local_10;
            DAT_007f46a8[uVar7 * 2 + -1] = local_10[1];
            DAT_007f46b0[uVar6] = *local_14;
            uVar6 = uVar7;
            pfVar11 = DAT_007f46ac;
          }
        }
        pfVar12 = pfVar9 + -2;
        local_c = local_14;
        local_14 = local_14 + 1;
        pfVar9 = pfVar9 + 3;
        param_5 = param_5 - 1;
        pfVar5 = local_10;
        pfVar10 = DAT_007f47b8;
        local_10 = local_10 + 2;
      } while (param_5 != 0);
    }
    DAT_007f47b8 = pfVar10;
    pfVar4 = DAT_007f461c;
    pfVar9 = DAT_007f4618;
    if (2 < (int)uVar6) {
      DAT_007f46ac = DAT_007f47b8;
      uVar7 = 0;
      DAT_007f461c = DAT_007f46a8;
      DAT_007f4618 = DAT_007f46b0;
      local_10 = DAT_007f46a8;
      local_14 = DAT_007f46b0;
      pfVar12 = pfVar11 + uVar6 * 3 + -3;
      pfVar5 = DAT_007f46a8 + uVar6 * 2 + -2;
      local_c = DAT_007f46b0 + (uVar6 - 1);
      pfVar10 = DAT_007f47b8;
      DAT_007f46a8 = pfVar4;
      DAT_007f46b0 = pfVar9;
      if (0 < (int)uVar6) {
        iVar13 = 0;
        pfVar9 = pfVar11 + 2;
        DAT_007f47b8 = pfVar11;
        param_5 = uVar6;
        do {
          fVar2 = (float)param_1[6];
          fVar1 = (float)param_1[6];
          if ((fVar2 <= pfVar12[2]) || (fVar1 <= *pfVar9)) {
            if (((pfVar12[2] != fVar2) && (fVar1 != *pfVar9)) &&
               ((pfVar12[2] < fVar2 || (*pfVar9 < fVar1)))) {
              fVar3 = (fVar2 - pfVar12[2]) / (*pfVar9 - pfVar12[2]);
              uVar6 = uVar7 + 1;
              *(float *)((int)pfVar10 + iVar13) = (pfVar9[-2] - *pfVar12) * fVar3 + *pfVar12;
              *(float *)((int)DAT_007f46ac + iVar13 + 4) =
                   (pfVar9[-1] - pfVar12[1]) * fVar3 + pfVar12[1];
              *(float *)((int)DAT_007f46ac + iVar13 + 8) = fVar2;
              DAT_007f46a8[uVar6 * 2 + -2] = (*local_10 - *pfVar5) * fVar3 + *pfVar5;
              DAT_007f46a8[uVar6 * 2 + -1] = (local_10[1] - pfVar5[1]) * fVar3 + pfVar5[1];
              DAT_007f46b0[uVar7] = (*local_14 - *local_c) * fVar3 + *local_c;
              DAT_007f4ac4 = DAT_007f4ac4 | 8;
              uVar7 = uVar6;
              iVar13 = iVar13 + 0xc;
              pfVar10 = DAT_007f46ac;
            }
            if (fVar1 <= *pfVar9) {
              pfVar10 = (float *)((int)pfVar10 + iVar13);
              uVar6 = uVar7 + 1;
              iVar13 = iVar13 + 0xc;
              *pfVar10 = pfVar9[-2];
              pfVar10[1] = pfVar9[-1];
              pfVar10[2] = *pfVar9;
              DAT_007f46a8[uVar6 * 2 + -2] = *local_10;
              DAT_007f46a8[uVar6 * 2 + -1] = local_10[1];
              DAT_007f46b0[uVar7] = *local_14;
              uVar7 = uVar6;
              pfVar10 = DAT_007f46ac;
            }
          }
          pfVar12 = pfVar9 + -2;
          local_c = local_14;
          local_14 = local_14 + 1;
          pfVar9 = pfVar9 + 3;
          param_5 = param_5 - 1;
          pfVar5 = local_10;
          pfVar11 = DAT_007f47b8;
          local_10 = local_10 + 2;
        } while (param_5 != 0);
      }
      DAT_007f47b8 = pfVar11;
      uVar6 = uVar7;
      pfVar4 = DAT_007f461c;
      pfVar9 = DAT_007f4618;
      if (2 < (int)uVar6) {
        DAT_007f46ac = DAT_007f47b8;
        uVar7 = 0;
        DAT_007f461c = DAT_007f46a8;
        DAT_007f4618 = DAT_007f46b0;
        local_10 = DAT_007f46a8;
        local_14 = DAT_007f46b0;
        pfVar12 = pfVar10 + uVar6 * 3 + -3;
        pfVar5 = DAT_007f46a8 + uVar6 * 2 + -2;
        local_c = DAT_007f46b0 + (uVar6 - 1);
        pfVar11 = DAT_007f47b8;
        DAT_007f46a8 = pfVar4;
        DAT_007f46b0 = pfVar9;
        if (0 < (int)uVar6) {
          iVar13 = 0;
          pfVar9 = pfVar10 + 1;
          uVar8 = uVar7;
          DAT_007f47b8 = pfVar10;
          param_5 = uVar6;
          do {
            if (((float)param_1[1] <= pfVar12[1]) || (uVar7 = uVar8, (float)param_1[1] <= *pfVar9))
            {
              if (((pfVar12[1] != (float)param_1[1]) && (*pfVar9 != (float)param_1[1])) &&
                 ((pfVar12[1] < (float)param_1[1] || (*pfVar9 < (float)param_1[1])))) {
                uVar6 = uVar8 + 1;
                fVar1 = ((float)param_1[1] - pfVar12[1]) / (*pfVar9 - pfVar12[1]);
                *(int *)((int)pfVar11 + iVar13 + 4) = param_1[1];
                *(float *)((int)DAT_007f46ac + iVar13 + 8) =
                     (pfVar9[1] - pfVar12[2]) * fVar1 + pfVar12[2];
                *(float *)((int)DAT_007f46ac + iVar13) = (pfVar9[-1] - *pfVar12) * fVar1 + *pfVar12;
                DAT_007f46a8[uVar6 * 2 + -2] = (*local_10 - *pfVar5) * fVar1 + *pfVar5;
                DAT_007f46a8[uVar6 * 2 + -1] = (local_10[1] - pfVar5[1]) * fVar1 + pfVar5[1];
                DAT_007f46b0[uVar8] = (*local_14 - *local_c) * fVar1 + *local_c;
                DAT_007f4ac4 = DAT_007f4ac4 | 1;
                uVar8 = uVar6;
                pfVar11 = DAT_007f46ac;
                iVar13 = iVar13 + 0xc;
              }
              uVar7 = uVar8;
              if ((float)param_1[1] <= *pfVar9) {
                pfVar11 = (float *)((int)pfVar11 + iVar13);
                uVar7 = uVar8 + 1;
                iVar13 = iVar13 + 0xc;
                *pfVar11 = pfVar9[-1];
                pfVar11[1] = *pfVar9;
                pfVar11[2] = pfVar9[1];
                DAT_007f46a8[uVar7 * 2 + -2] = *local_10;
                DAT_007f46a8[uVar7 * 2 + -1] = local_10[1];
                DAT_007f46b0[uVar8] = *local_14;
                pfVar11 = DAT_007f46ac;
              }
            }
            pfVar12 = pfVar9 + -1;
            local_c = local_14;
            local_14 = local_14 + 1;
            pfVar9 = pfVar9 + 3;
            param_5 = param_5 - 1;
            uVar8 = uVar7;
            pfVar5 = local_10;
            pfVar10 = DAT_007f47b8;
            local_10 = local_10 + 2;
          } while (param_5 != 0);
        }
        DAT_007f47b8 = pfVar10;
        pfVar4 = DAT_007f461c;
        pfVar9 = DAT_007f4618;
        if ((int)uVar7 < 3) {
          DAT_007f4ac4 = DAT_007f4ac4 | 0x40;
          return uVar7;
        }
        uVar6 = uVar7;
        pfVar12 = pfVar11;
        if (*param_1 != 0) {
          DAT_007f46ac = DAT_007f47b8;
          DAT_007f4618 = DAT_007f46b0;
          local_14 = DAT_007f46b0;
          uVar6 = 0;
          DAT_007f461c = DAT_007f46a8;
          local_10 = DAT_007f46a8;
          pfVar5 = pfVar11 + uVar7 * 3 + -3;
          pfVar10 = DAT_007f46a8 + uVar7 * 2 + -2;
          local_c = DAT_007f46b0 + (uVar7 - 1);
          pfVar12 = DAT_007f47b8;
          DAT_007f46a8 = pfVar4;
          DAT_007f46b0 = pfVar9;
          if (0 < (int)uVar7) {
            iVar13 = 0;
            pfVar9 = pfVar11 + 1;
            uVar8 = uVar6;
            DAT_007f47b8 = pfVar11;
            param_5 = uVar7;
            do {
              if ((pfVar5[1] <= (float)param_1[2]) || (uVar6 = uVar8, *pfVar9 <= (float)param_1[2]))
              {
                if (((pfVar5[1] != (float)param_1[2]) && (*pfVar9 != (float)param_1[2])) &&
                   (((float)param_1[2] < pfVar5[1] || ((float)param_1[2] < *pfVar9)))) {
                  uVar6 = uVar8 + 1;
                  fVar1 = ((float)param_1[2] - pfVar5[1]) / (*pfVar9 - pfVar5[1]);
                  *(int *)((int)pfVar12 + iVar13 + 4) = param_1[2];
                  *(float *)((int)DAT_007f46ac + iVar13 + 8) =
                       (pfVar9[1] - pfVar5[2]) * fVar1 + pfVar5[2];
                  *(float *)((int)DAT_007f46ac + iVar13) = (pfVar9[-1] - *pfVar5) * fVar1 + *pfVar5;
                  DAT_007f46a8[uVar6 * 2 + -2] = (*local_10 - *pfVar10) * fVar1 + *pfVar10;
                  DAT_007f46a8[uVar6 * 2 + -1] = (local_10[1] - pfVar10[1]) * fVar1 + pfVar10[1];
                  DAT_007f46b0[uVar8] = (*local_14 - *local_c) * fVar1 + *local_c;
                  DAT_007f4ac4 = DAT_007f4ac4 | 2;
                  uVar8 = uVar6;
                  pfVar12 = DAT_007f46ac;
                  iVar13 = iVar13 + 0xc;
                }
                uVar6 = uVar8;
                if (*pfVar9 <= (float)param_1[2]) {
                  pfVar12 = (float *)((int)pfVar12 + iVar13);
                  uVar6 = uVar8 + 1;
                  iVar13 = iVar13 + 0xc;
                  *pfVar12 = pfVar9[-1];
                  pfVar12[1] = *pfVar9;
                  pfVar12[2] = pfVar9[1];
                  DAT_007f46a8[uVar6 * 2 + -2] = *local_10;
                  DAT_007f46a8[uVar6 * 2 + -1] = local_10[1];
                  DAT_007f46b0[uVar8] = *local_14;
                  pfVar12 = DAT_007f46ac;
                }
              }
              pfVar5 = pfVar9 + -1;
              local_c = local_14;
              local_14 = local_14 + 1;
              pfVar9 = pfVar9 + 3;
              param_5 = param_5 - 1;
              uVar8 = uVar6;
              pfVar10 = local_10;
              pfVar11 = DAT_007f47b8;
              local_10 = local_10 + 2;
            } while (param_5 != 0);
          }
          DAT_007f47b8 = pfVar11;
          if ((int)uVar6 < 3) {
            return uVar6;
          }
        }
        if (pfVar12 != param_2) {
          for (uVar7 = uVar6 * 3 & 0x3fffffff; uVar7 != 0; uVar7 = uVar7 - 1) {
            *param_2 = *pfVar12;
            pfVar12 = pfVar12 + 1;
            param_2 = param_2 + 1;
          }
          for (iVar13 = 0; iVar13 != 0; iVar13 = iVar13 + -1) {
            *(undefined1 *)param_2 = *(undefined1 *)pfVar12;
            pfVar12 = (float *)((int)pfVar12 + 1);
            param_2 = (float *)((int)param_2 + 1);
          }
          pfVar9 = DAT_007f46a8;
          for (iVar13 = (uVar6 & 0x1fffffff) << 1; iVar13 != 0; iVar13 = iVar13 + -1) {
            *param_3 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            param_3 = param_3 + 1;
          }
          for (iVar13 = 0; uVar7 = uVar6, pfVar4 = DAT_007f46b0, iVar13 != 0; iVar13 = iVar13 + -1)
          {
            *(undefined1 *)param_3 = *(undefined1 *)pfVar9;
            pfVar9 = (float *)((int)pfVar9 + 1);
            param_3 = (float *)((int)param_3 + 1);
          }
          for (; uVar7 != 0; uVar7 = uVar7 - 1) {
            *param_4 = *pfVar4;
            pfVar4 = pfVar4 + 1;
            param_4 = param_4 + 1;
          }
        }
      }
    }
  }
  return uVar6;
}
#undef local_10
#undef local_14
#undef local_c

