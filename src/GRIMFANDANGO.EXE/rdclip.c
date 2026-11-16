/* GRIMFANDANGO.EXE :: rdclip.c
 * functions 0x00446c10 .. 0x0044da40 (14 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00446c10  rdClip_Line2 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Cohen-Sutherland line clip against a rectangle using rdClip_Outcode2D Original name rdClip_Line2
   (the remaster's GrimFandango (Linux): the 2D line clip against the canvas rectangle (+0x18 ..
   +0x24) with the outcodes 1 / 0x10 / 0x1000 / 0x100 in both builds; the remaster inlined
   rdClip_CalcOutcode2); was rdClip_Line2D. */

undefined4 __cdecl
rdClip_Line2(int canvas,undefined4 *x0,undefined4 *y0,undefined4 *x1,undefined4 *y1)

{
  bool bVar1;
  float fVar2;
  bool bVar3;
  int canvas_00;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  float10 x;
  float10 x_00;
  float10 x_01;
  longlong lVar8;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  canvas_00 = canvas;
  uVar4 = rdClip_CalcOutcode2(canvas,*x0,*y0);
  uVar5 = rdClip_CalcOutcode2(canvas,*x1,*y1);
  if ((uVar4 == 0) && (uVar5 == 0)) {
    return 1;
  }
  if ((uVar4 & uVar5) == 0) {
    canvas = PUN(int,(float)PUN(float,(int)*x0));
    local_10 = PUN(uint,(float)PUN(float,(int)*x1));
    local_14 = PUN(uint,(float)PUN(float,(int)*y0));
    bVar1 = PUN(float,canvas) != PUN(float,local_10);
    local_c = PUN(uint,(float)PUN(float,(int)*y1));
    if (PUN(float,local_14) == PUN(float,local_c)) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    do {
      uVar6 = uVar4;
      if (uVar4 == 0) {
        uVar6 = uVar5;
      }
      fVar2 = PUN(float,canvas);
      if ((uVar6 & 0x1000) == 0) {
        if ((uVar6 & 0x100) == 0) {
          if ((uVar6 & 0x10) == 0) {
            if (bVar3) {
              local_8 = local_14;
            }
            else {
              local_8 = PUN(uint,(float)(((float)*(int *)(canvas_00 + 0x18) - PUN(float,canvas)) *
                               ((PUN(float,local_c) - PUN(float,local_14)) /
                               (PUN(float,local_10) - PUN(float,canvas))) + PUN(float,local_14)));
            }
            fVar2 = (float)*(int *)(canvas_00 + 0x18);
          }
          else if (bVar3) {
            fVar2 = (float)*(int *)(canvas_00 + 0x20);
            local_8 = local_14;
          }
          else {
            local_8 = PUN(uint,(float)(((float)*(int *)(canvas_00 + 0x20) - PUN(float,canvas)) *
                             ((PUN(float,local_c) - PUN(float,local_14)) / (PUN(float,local_10) - PUN(float,canvas))
                             ) + PUN(float,local_14)));
            fVar2 = (float)*(int *)(canvas_00 + 0x20);
          }
          x = (float10)(float)local_8;
        }
        else if (bVar1) {
          fVar2 = ((float)*(int *)(canvas_00 + 0x24) - PUN(float,local_14)) *
                  ((PUN(float,local_10) - PUN(float,canvas)) / (PUN(float,local_c) - PUN(float,local_14))) +
                  PUN(float,canvas);
          x = (float10)*(int *)(canvas_00 + 0x24);
        }
        else {
          x = (float10)*(int *)(canvas_00 + 0x24);
        }
      }
      else if (bVar1) {
        x = (float10)*(int *)(canvas_00 + 0x1c);
        fVar2 = ((float)*(int *)(canvas_00 + 0x1c) - PUN(float,local_14)) *
                ((PUN(float,local_10) - PUN(float,canvas)) / (PUN(float,local_c) - PUN(float,local_14))) +
                PUN(float,canvas);
      }
      else {
        x = (float10)*(int *)(canvas_00 + 0x1c);
      }
      if (uVar6 == uVar4) {
        local_14 = PUN(uint,(float)(float)x);
        lVar8 = FTOL(x);
        iVar7 = (int)lVar8;
        lVar8 = FTOL(x_00);
        uVar4 = rdClip_CalcOutcode2(canvas_00,(int)lVar8,iVar7);
        canvas = PUN(int,(float)fVar2);
      }
      else {
        local_c = PUN(uint,(float)(float)x);
        lVar8 = FTOL(x);
        iVar7 = (int)lVar8;
        lVar8 = FTOL(x_01);
        uVar5 = rdClip_CalcOutcode2(canvas_00,(int)lVar8,iVar7);
        local_10 = PUN(uint,(float)fVar2);
      }
      if ((uVar4 == 0) && (uVar5 == 0)) {
        lVar8 = FTOL((float10)PUN(float,canvas));
        *x0 = (int)lVar8;
        lVar8 = FTOL((float10)PUN(float,local_14));
        *y0 = (int)lVar8;
        lVar8 = FTOL((float10)PUN(float,local_10));
        *x1 = (int)lVar8;
        lVar8 = FTOL((float10)PUN(float,local_c));
        *y1 = (int)lVar8;
        return 1;
      }
    } while ((uVar4 & uVar5) == 0);
  }
  return 0;
}
#endif


/* ---- 0x00446e80  rdClip_CalcOutcode2 ---- */
/* Original name rdClip_CalcOutcode2 (the remaster's GrimFandango (Linux): same body (outcode 1 /
   0x10 for x left / right of +0x18 / +0x20, 0x1000 / 0x100 for y)); was rdClip_Outcode2D. */

uint __cdecl rdClip_CalcOutcode2(int canvas,int x,int y)

{
  uint uVar1;
  
  uVar1 = 0;
  if (x < *(int *)(canvas + 0x18)) {
    uVar1 = 1;
  }
  else if (*(int *)(canvas + 0x20) < x) {
    uVar1 = 0x10;
  }
  if (y < *(int *)(canvas + 0x1c)) {
    return uVar1 | 0x1000;
  }
  if (*(int *)(canvas + 0x24) < y) {
    uVar1 = uVar1 | 0x100;
  }
  return uVar1;
}

/* ---- 0x00446ec0  rdClip_Point3 ---- */
/* Near/far, then left/right/top/bottom; perspective frustums scale the side planes by depth
   Original name rdClip_Point3 (the remaster's GrimFandango (Linux): aligned call in
   rdPrimit3_GetScreenCoord); was rdClip_PointInFrustum. */

int __cdecl rdClip_Point3(rdClipFrustum *frustum,float *point)

{
  float fVar1;
  int iVar2;
  
  if (point[1] < frustum->flZNear) {
    return 0;
  }
  if ((frustum->nClipFar != 0) && (frustum->flZFar < point[1])) {
    return 0;
  }
  iVar2 = g_pRdCamera_CurCamera->nProjectType;
  if (iVar2 == 1) {
    fVar1 = frustum->flFarLeft * point[1];
  }
  else {
    fVar1 = frustum->flOrthoLeft;
  }
  if (*point < fVar1) {
    return 0;
  }
  if (iVar2 == 1) {
    fVar1 = frustum->flRight * point[1];
  }
  else {
    fVar1 = frustum->flOrthoRight;
  }
  if (fVar1 < *point) {
    return 0;
  }
  if (iVar2 == 1) {
    fVar1 = frustum->flFarTop * point[1];
  }
  else {
    fVar1 = frustum->flOrthoTop;
  }
  if (fVar1 < point[2]) {
    return 0;
  }
  if (iVar2 == 1) {
    fVar1 = frustum->flBottom * point[1];
  }
  else {
    fVar1 = frustum->flOrthoBottom;
  }
  if (point[2] < fVar1) {
    return 0;
  }
  return 1;
}

/* ---- 0x00446f80  rdClip_Line3 ---- */
int __cdecl rdClip_Line3(rdClipFrustum *frustum,float *p0,float *p1,int *clipped0,int *clipped1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  if ((p0[1] < frustum->flZNear) && (p1[1] < frustum->flZNear)) {
    return 0;
  }
  if (frustum->flZNear <= p0[1]) {
    if (p1[1] < frustum->flZNear) {
      fVar3 = (frustum->flZNear - p0[1]) / (p1[1] - p0[1]);
      p1[1] = frustum->flZNear;
      p1[2] = (p1[2] - p0[2]) * fVar3 + p0[2];
      *p1 = (*p1 - *p0) * fVar3 + *p0;
      if (clipped1 != (int *)0x0) {
        *clipped1 = 1;
      }
    }
  }
  else {
    fVar3 = (frustum->flZNear - p0[1]) / (p1[1] - p0[1]);
    p0[1] = frustum->flZNear;
    p0[2] = (p1[2] - p0[2]) * fVar3 + p0[2];
    *p0 = (*p1 - *p0) * fVar3 + *p0;
    if (clipped0 != (int *)0x0) {
      *clipped0 = 1;
    }
  }
  if (frustum->nClipFar != 0) {
    if ((frustum->flZFar < p0[1]) && (frustum->flZFar < p1[1])) {
      return 0;
    }
    if (p0[1] <= frustum->flZFar) {
      if (frustum->flZFar < p1[1]) {
        fVar3 = (frustum->flZFar - p0[1]) / (p1[1] - p0[1]);
        p1[1] = frustum->flZFar;
        p1[2] = (p1[2] - p0[2]) * fVar3 + p0[2];
        *p1 = (*p1 - *p0) * fVar3 + *p0;
        if (clipped1 != (int *)0x0) {
          *clipped1 = 1;
        }
      }
    }
    else {
      fVar3 = (frustum->flZFar - p0[1]) / (p1[1] - p0[1]);
      p0[1] = frustum->flZFar;
      p0[2] = (p1[2] - p0[2]) * fVar3 + p0[2];
      *p0 = (*p1 - *p0) * fVar3 + *p0;
      if (clipped0 != (int *)0x0) {
        *clipped0 = 1;
      }
    }
  }
  fVar3 = frustum->flFarLeft * p0[1];
  fVar4 = frustum->flFarLeft * p1[1];
  if ((*p0 < fVar3) && (*p1 < fVar4)) {
    return 0;
  }
  if (fVar3 <= *p0) {
    if (*p1 < fVar4) {
      fVar3 = p1[1] - p0[1];
      fVar1 = *p1 - *p0;
      fVar4 = frustum->flFarLeft * fVar3 - fVar1;
      fVar5 = p1[1] * *p0 - p0[1] * *p1;
      if (fVar4 != 0.0f) {
        fVar5 = fVar5 / fVar4;
      }
      fVar4 = frustum->flFarLeft * fVar5;
      fVar2 = fVar3;
      if (fVar3 < 0.0f) {
        fVar2 = -fVar3;
      }
      fVar6 = fVar1;
      if (fVar1 < 0.0f) {
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
    fVar4 = frustum->flFarLeft * fVar3 - fVar1;
    fVar5 = p1[1] * *p0 - p0[1] * *p1;
    if (fVar4 != 0.0f) {
      fVar5 = fVar5 / fVar4;
    }
    fVar4 = frustum->flFarLeft * fVar5;
    fVar2 = fVar3;
    if (fVar3 < 0.0f) {
      fVar2 = -fVar3;
    }
    fVar6 = fVar1;
    if (fVar1 < 0.0f) {
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
  fVar3 = frustum->flRight * p0[1];
  fVar4 = frustum->flRight * p1[1];
  if ((fVar3 < *p0) && (fVar4 < *p1)) {
    return 0;
  }
  if (*p0 <= fVar3) {
    if (fVar4 < *p1) {
      fVar3 = p1[1] - p0[1];
      fVar1 = *p1 - *p0;
      fVar4 = frustum->flRight * fVar3 - fVar1;
      fVar5 = p1[1] * *p0 - p0[1] * *p1;
      if (fVar4 != 0.0f) {
        fVar5 = fVar5 / fVar4;
      }
      fVar4 = frustum->flRight * fVar5;
      fVar2 = fVar3;
      if (fVar3 < 0.0f) {
        fVar2 = -fVar3;
      }
      fVar6 = fVar1;
      if (fVar1 < 0.0f) {
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
    fVar4 = frustum->flRight * fVar3 - fVar1;
    fVar5 = p1[1] * *p0 - p0[1] * *p1;
    if (fVar4 != 0.0f) {
      fVar5 = fVar5 / fVar4;
    }
    fVar4 = frustum->flRight * fVar5;
    fVar2 = fVar3;
    if (fVar3 < 0.0f) {
      fVar2 = -fVar3;
    }
    fVar6 = fVar1;
    if (fVar1 < 0.0f) {
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
  fVar3 = frustum->flFarTop * p0[1];
  fVar4 = frustum->flFarTop * p1[1];
  if ((fVar3 < p0[2]) && (fVar4 < p1[2])) {
    return 0;
  }
  if (p0[2] <= fVar3) {
    if (fVar4 < p1[2]) {
      fVar3 = p1[1] - p0[1];
      fVar1 = p1[2] - p0[2];
      fVar4 = frustum->flFarTop * fVar3 - fVar1;
      fVar5 = p0[2] * p1[1] - p1[2] * p0[1];
      if (fVar4 != 0.0f) {
        fVar5 = fVar5 / fVar4;
      }
      fVar4 = frustum->flFarTop * fVar5;
      fVar2 = fVar3;
      if (fVar3 < 0.0f) {
        fVar2 = -fVar3;
      }
      fVar6 = fVar1;
      if (fVar1 < 0.0f) {
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
    fVar4 = frustum->flFarTop * fVar3 - fVar1;
    fVar5 = p0[2] * p1[1] - p1[2] * p0[1];
    if (fVar4 != 0.0f) {
      fVar5 = fVar5 / fVar4;
    }
    fVar4 = frustum->flFarTop * fVar5;
    fVar2 = fVar3;
    if (fVar3 < 0.0f) {
      fVar2 = -fVar3;
    }
    fVar6 = fVar1;
    if (fVar1 < 0.0f) {
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
  fVar3 = frustum->flBottom * p0[1];
  fVar4 = frustum->flBottom * p1[1];
  if ((p0[2] < fVar3) && (p1[2] < fVar4)) {
    return 0;
  }
  if (fVar3 <= p0[2]) {
    if (p1[2] < fVar4) {
      fVar3 = p1[1] - p0[1];
      fVar1 = p1[2] - p0[2];
      fVar4 = frustum->flBottom * fVar3 - fVar1;
      fVar5 = p0[2] * p1[1] - p1[2] * p0[1];
      if (fVar4 != 0.0f) {
        fVar5 = fVar5 / fVar4;
      }
      fVar4 = frustum->flBottom * fVar5;
      fVar2 = fVar3;
      if (fVar3 < 0.0f) {
        fVar2 = -fVar3;
      }
      fVar6 = fVar1;
      if (fVar1 < 0.0f) {
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
    fVar4 = frustum->flBottom * fVar3 - fVar1;
    fVar5 = p0[2] * p1[1] - p1[2] * p0[1];
    if (fVar4 != 0.0f) {
      fVar5 = fVar5 / fVar4;
    }
    fVar4 = frustum->flBottom * fVar5;
    fVar2 = fVar3;
    if (fVar3 < 0.0f) {
      fVar2 = -fVar3;
    }
    fVar6 = fVar1;
    if (fVar1 < 0.0f) {
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

/* ---- 0x004478c0  rdClip_Face3W ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Frustum clip of a face with position-only vertices (output into the rdClip work buffers at
   g_RdClipVerts). Attribute set inferred from the parameter list Original name rdClip_Face3W (the
   remaster's GrimFandango (Linux): the matching branch of the rdPrimit3_ClipFace switch
   (geometry/lighting mode, perspective or ortho camera)); was rdClip_Face3_Pos. */

uint __cdecl rdClip_Face3W(int *frustum,float *verts,uint count)

{
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
  uint local_8;
  uint local_4;
  
  uVar12 = 0;
  puVar14 = &g_dwWorkVerts;
  g_dwRdClip_faceStatus = 0;
  g_dwSourceVert = (uint)verts;
  g_dwDestVert = (uint)&g_dwWorkVerts;
  if (0 < (int)count) {
    iVar11 = 0;
    local_4 = count;
    pfVar15 = verts + count * 3 + -3;
    pfVar8 = verts;
    do {
      fVar2 = pfVar15[1] * PUN(float,frustum[9]);
      fVar3 = pfVar8[1] * PUN(float,frustum[9]);
      if ((fVar2 <= *pfVar15) || (fVar3 <= *pfVar8)) {
        if (((*pfVar15 != fVar2) && (fVar3 != *pfVar8)) && ((*pfVar15 < fVar2 || (*pfVar8 < fVar3)))
           ) {
          fVar2 = pfVar8[1] - pfVar15[1];
          fVar4 = *pfVar8 - *pfVar15;
          fVar1 = PUN(float,frustum[9]) * fVar2 - fVar4;
          fVar5 = pfVar8[1] * *pfVar15 - pfVar15[1] * *pfVar8;
          if (fVar1 != 0.0f) {
            fVar5 = fVar5 / fVar1;
          }
          fVar1 = fVar2;
          if (fVar2 < 0.0f) {
            fVar1 = -fVar2;
          }
          fVar6 = fVar4;
          if (fVar4 < 0.0f) {
            fVar6 = -fVar4;
          }
          if (fVar1 <= fVar6) {
            fVar2 = (PUN(float,frustum[9]) * fVar5 - *pfVar15) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar15[1]) / fVar2;
          }
          *(float *)((int)puVar14 + iVar11) = PUN(float,frustum[9]) * fVar5;
          uVar12 = uVar12 + 1;
          *(float *)(g_dwDestVert + 4 + iVar11) = fVar5;
          iVar11 = iVar11 + 0xc;
          *(float *)((g_dwDestVert - 4) + iVar11) = (pfVar8[2] - pfVar15[2]) * fVar2 + pfVar15[2];
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x10;
          puVar14 = (uint *)g_dwDestVert;
        }
        if (fVar3 <= *pfVar8) {
          pfVar15 = (float *)((int)puVar14 + iVar11);
          uVar12 = uVar12 + 1;
          iVar11 = iVar11 + 0xc;
          *pfVar15 = *pfVar8;
          pfVar15[1] = pfVar8[1];
          pfVar15[2] = pfVar8[2];
          puVar14 = (uint *)g_dwDestVert;
        }
      }
      local_4 = local_4 - 1;
      pfVar15 = pfVar8;
      pfVar8 = pfVar8 + 3;
    } while (local_4 != 0);
  }
  if (2 < (int)uVar12) {
    uVar13 = 0;
    uVar17 = g_dwSourceVert;
    g_dwDestVert = g_dwSourceVert;
    pfVar15 = (float *)puVar14;
    if (0 < (int)uVar12) {
      iVar11 = 0;
      pfVar8 = (float *)(puVar14 + uVar12 * 3 + -3);
      g_dwSourceVert = (uint)puVar14;
      local_4 = uVar12;
      do {
        fVar2 = PUN(float,frustum[10]) * pfVar8[1];
        fVar3 = PUN(float,frustum[10]) * PUN(float,puVar14[1]);
        if ((*pfVar8 <= fVar2) || (PUN(float,*puVar14) <= fVar3)) {
          if (((*pfVar8 != fVar2) && (fVar3 != PUN(float,*puVar14))) &&
             ((fVar2 < *pfVar8 || (fVar3 < PUN(float,*puVar14))))) {
            fVar2 = PUN(float,puVar14[1]) - pfVar8[1];
            fVar4 = PUN(float,*puVar14) - *pfVar8;
            fVar1 = PUN(float,frustum[10]) * fVar2 - fVar4;
            fVar5 = PUN(float,puVar14[1]) * *pfVar8 - pfVar8[1] * PUN(float,*puVar14);
            if (fVar1 != 0.0f) {
              fVar5 = fVar5 / fVar1;
            }
            fVar1 = fVar2;
            if (fVar2 < 0.0f) {
              fVar1 = -fVar2;
            }
            fVar6 = fVar4;
            if (fVar4 < 0.0f) {
              fVar6 = -fVar4;
            }
            if (fVar1 <= fVar6) {
              fVar2 = (PUN(float,frustum[10]) * fVar5 - *pfVar8) / fVar4;
            }
            else {
              fVar2 = (fVar5 - pfVar8[1]) / fVar2;
            }
            *(float *)(uVar17 + iVar11) = PUN(float,frustum[10]) * fVar5;
            uVar13 = uVar13 + 1;
            *(float *)(g_dwDestVert + 4 + iVar11) = fVar5;
            iVar11 = iVar11 + 0xc;
            *(float *)((g_dwDestVert - 4) + iVar11) =
                 (PUN(float,puVar14[2]) - pfVar8[2]) * fVar2 + pfVar8[2];
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x20;
            uVar17 = g_dwDestVert;
          }
          if (PUN(float,*puVar14) <= fVar3) {
            pfVar15 = (float *)(uVar17 + iVar11);
            uVar13 = uVar13 + 1;
            iVar11 = iVar11 + 0xc;
            *pfVar15 = PUN(float,*puVar14);
            pfVar15[1] = PUN(float,puVar14[1]);
            pfVar15[2] = PUN(float,puVar14[2]);
            uVar17 = g_dwDestVert;
          }
        }
        local_4 = local_4 - 1;
        pfVar8 = (float *)puVar14;
        puVar14 = puVar14 + 3;
        pfVar15 = (float *)g_dwSourceVert;
      } while (local_4 != 0);
    }
    g_dwSourceVert = (uint)pfVar15;
    uVar12 = uVar13;
    if (2 < (int)uVar12) {
      uVar13 = 0;
      g_dwDestVert = g_dwSourceVert;
      pfVar15 = (float *)((uVar17 - 0xc) + uVar12 * 0xc);
      uVar16 = g_dwSourceVert;
      if (0 < (int)uVar12) {
        iVar11 = 0;
        pfVar8 = (float *)(uVar17 + 8);
        g_dwSourceVert = uVar17;
        local_4 = uVar12;
        do {
          fVar2 = PUN(float,frustum[7]) * pfVar15[1];
          fVar3 = pfVar8[-1] * PUN(float,frustum[7]);
          if ((pfVar15[2] <= fVar2) || (*pfVar8 <= fVar3)) {
            if (((pfVar15[2] != fVar2) && (fVar3 != *pfVar8)) &&
               ((fVar2 < pfVar15[2] || (fVar3 < *pfVar8)))) {
              fVar2 = pfVar8[-1] - pfVar15[1];
              fVar4 = *pfVar8 - pfVar15[2];
              fVar1 = PUN(float,frustum[7]) * fVar2 - fVar4;
              fVar5 = pfVar15[2] * pfVar8[-1] - pfVar15[1] * *pfVar8;
              if (fVar1 != 0.0f) {
                fVar5 = fVar5 / fVar1;
              }
              fVar1 = PUN(float,frustum[7]);
              fVar6 = fVar2;
              if (fVar2 < 0.0f) {
                fVar6 = -fVar2;
              }
              fVar7 = fVar4;
              if (fVar4 < 0.0f) {
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
              *(float *)((g_dwDestVert - 8) + iVar11) = fVar5;
              *(float *)((g_dwDestVert - 4) + iVar11) = fVar1 * fVar5;
              g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 4;
              uVar16 = g_dwDestVert;
            }
            if (*pfVar8 <= fVar3) {
              pfVar15 = (float *)(uVar16 + iVar11);
              uVar13 = uVar13 + 1;
              iVar11 = iVar11 + 0xc;
              *pfVar15 = pfVar8[-2];
              pfVar15[1] = pfVar8[-1];
              pfVar15[2] = *pfVar8;
              uVar16 = g_dwDestVert;
            }
          }
          pfVar15 = pfVar8 + -2;
          pfVar8 = pfVar8 + 3;
          local_4 = local_4 - 1;
          uVar17 = g_dwSourceVert;
        } while (local_4 != 0);
      }
      g_dwSourceVert = uVar17;
      uVar12 = uVar13;
      if (2 < (int)uVar12) {
        uVar13 = 0;
        g_dwDestVert = g_dwSourceVert;
        pfVar15 = (float *)((uVar16 - 0xc) + uVar12 * 0xc);
        uVar17 = g_dwSourceVert;
        if (0 < (int)uVar12) {
          iVar11 = 0;
          pfVar8 = (float *)(uVar16 + 8);
          g_dwSourceVert = uVar16;
          local_4 = uVar12;
          do {
            fVar2 = PUN(float,frustum[8]) * pfVar15[1];
            fVar3 = pfVar8[-1] * PUN(float,frustum[8]);
            if ((fVar2 <= pfVar15[2]) || (fVar3 <= *pfVar8)) {
              if (((pfVar15[2] != fVar2) && (fVar3 != *pfVar8)) &&
                 ((pfVar15[2] < fVar2 || (*pfVar8 < fVar3)))) {
                fVar2 = pfVar8[-1] - pfVar15[1];
                fVar4 = *pfVar8 - pfVar15[2];
                fVar1 = PUN(float,frustum[8]) * fVar2 - fVar4;
                fVar5 = pfVar15[2] * pfVar8[-1] - pfVar15[1] * *pfVar8;
                if (fVar1 != 0.0f) {
                  fVar5 = fVar5 / fVar1;
                }
                fVar1 = PUN(float,frustum[8]);
                fVar6 = fVar2;
                if (fVar2 < 0.0f) {
                  fVar6 = -fVar2;
                }
                fVar7 = fVar4;
                if (fVar4 < 0.0f) {
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
                *(float *)((g_dwDestVert - 8) + iVar11) = fVar5;
                *(float *)((g_dwDestVert - 4) + iVar11) = fVar1 * fVar5;
                g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 8;
                uVar17 = g_dwDestVert;
              }
              if (fVar3 <= *pfVar8) {
                pfVar15 = (float *)(uVar17 + iVar11);
                uVar13 = uVar13 + 1;
                iVar11 = iVar11 + 0xc;
                *pfVar15 = pfVar8[-2];
                pfVar15[1] = pfVar8[-1];
                pfVar15[2] = *pfVar8;
                uVar17 = g_dwDestVert;
              }
            }
            pfVar15 = pfVar8 + -2;
            pfVar8 = pfVar8 + 3;
            local_4 = local_4 - 1;
            uVar16 = g_dwSourceVert;
          } while (local_4 != 0);
        }
        g_dwSourceVert = uVar16;
        uVar12 = uVar13;
        if (2 < (int)uVar12) {
          uVar13 = 0;
          g_dwDestVert = g_dwSourceVert;
          pfVar15 = (float *)((uVar17 - 0xc) + uVar12 * 0xc);
          pfVar8 = (float *)g_dwSourceVert;
          if (0 < (int)uVar12) {
            iVar11 = 0;
            pfVar9 = (float *)(uVar17 + 4);
            g_dwSourceVert = uVar17;
            count = uVar12;
            do {
              if ((PUN(float,frustum[1]) <= pfVar15[1]) || (PUN(float,frustum[1]) <= *pfVar9)) {
                if (((pfVar15[1] != PUN(float,frustum[1])) && (*pfVar9 != PUN(float,frustum[1]))) &&
                   ((pfVar15[1] < PUN(float,frustum[1]) || (*pfVar9 < PUN(float,frustum[1]))))) {
                  uVar13 = uVar13 + 1;
                  fVar2 = (PUN(float,frustum[1]) - pfVar15[1]) / (*pfVar9 - pfVar15[1]);
                  *(int *)((int)pfVar8 + iVar11 + 4) = frustum[1];
                  iVar11 = iVar11 + 0xc;
                  *(float *)((g_dwDestVert - 4) + iVar11) =
                       (pfVar9[1] - pfVar15[2]) * fVar2 + pfVar15[2];
                  *(float *)((g_dwDestVert - 0xc) + iVar11) =
                       (pfVar9[-1] - *pfVar15) * fVar2 + *pfVar15;
                  g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 1;
                  pfVar8 = (float *)g_dwDestVert;
                }
                if (PUN(float,frustum[1]) <= *pfVar9) {
                  pfVar8 = (float *)((int)pfVar8 + iVar11);
                  uVar13 = uVar13 + 1;
                  iVar11 = iVar11 + 0xc;
                  *pfVar8 = pfVar9[-1];
                  pfVar8[1] = *pfVar9;
                  pfVar8[2] = pfVar9[1];
                  pfVar8 = (float *)g_dwDestVert;
                }
              }
              pfVar15 = pfVar9 + -1;
              pfVar9 = pfVar9 + 3;
              count = count - 1;
              uVar17 = g_dwSourceVert;
            } while (count != 0);
          }
          g_dwSourceVert = uVar17;
          if ((int)uVar13 < 3) {
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x40;
            return uVar13;
          }
          uVar12 = uVar13;
          pfVar15 = pfVar8;
          if (*frustum != 0) {
            uVar12 = 0;
            pfVar9 = pfVar8 + uVar13 * 3 + -3;
            pfVar15 = (float *)g_dwSourceVert;
            g_dwDestVert = g_dwSourceVert;
            if (0 < (int)uVar13) {
              iVar11 = 0;
              pfVar10 = pfVar8 + 1;
              g_dwSourceVert = (uint)pfVar8;
              count = uVar13;
              do {
                if ((pfVar9[1] <= PUN(float,frustum[2])) || (*pfVar10 <= PUN(float,frustum[2]))) {
                  if (((pfVar9[1] != PUN(float,frustum[2])) && (*pfVar10 != PUN(float,frustum[2]))) &&
                     ((PUN(float,frustum[2]) < pfVar9[1] || (PUN(float,frustum[2]) < *pfVar10)))) {
                    uVar12 = uVar12 + 1;
                    fVar2 = (PUN(float,frustum[2]) - pfVar9[1]) / (*pfVar10 - pfVar9[1]);
                    *(int *)((int)pfVar15 + iVar11 + 4) = frustum[2];
                    iVar11 = iVar11 + 0xc;
                    *(float *)((g_dwDestVert - 4) + iVar11) =
                         (pfVar10[1] - pfVar9[2]) * fVar2 + pfVar9[2];
                    *(float *)((g_dwDestVert - 0xc) + iVar11) =
                         (pfVar10[-1] - *pfVar9) * fVar2 + *pfVar9;
                    g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 2;
                    pfVar15 = (float *)g_dwDestVert;
                  }
                  if (*pfVar10 <= PUN(float,frustum[2])) {
                    pfVar15 = (float *)((int)pfVar15 + iVar11);
                    uVar12 = uVar12 + 1;
                    iVar11 = iVar11 + 0xc;
                    *pfVar15 = pfVar10[-1];
                    pfVar15[1] = *pfVar10;
                    pfVar15[2] = pfVar10[1];
                    pfVar15 = (float *)g_dwDestVert;
                  }
                }
                pfVar9 = pfVar10 + -1;
                pfVar10 = pfVar10 + 3;
                count = count - 1;
                pfVar8 = (float *)g_dwSourceVert;
              } while (count != 0);
            }
            g_dwSourceVert = (uint)pfVar8;
            if ((int)uVar12 < 3) {
              return uVar12;
            }
          }
          if (pfVar15 != verts) {
            for (uVar13 = uVar12 * 3 & 0x3fffffff; uVar13 != 0; uVar13 = uVar13 - 1) {
              *verts = *pfVar15;
              pfVar15 = pfVar15 + 1;
              verts = verts + 1;
            }
            for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
              *(undefined1 *)verts = *(undefined1 *)pfVar15;
              pfVar15 = (float *)((int)pfVar15 + 1);
              verts = (float *)((int)verts + 1);
            }
          }
        }
      }
    }
  }
  return uVar12;
}
#endif


/* ---- 0x00448260  rdClip_Face3WOrtho ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Second position-only face clipper (likely the orthographic variant) Original name
   rdClip_Face3WOrtho (the remaster's GrimFandango (Linux): the matching branch of the
   rdPrimit3_ClipFace switch (geometry/lighting mode, perspective or ortho camera)); was
   rdClip_Face3_PosB. */

int __cdecl rdClip_Face3WOrtho(int *frustum,float *verts,int count)

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
  puVar10 = &g_dwWorkVerts;
  iVar9 = 0;
  g_dwRdClip_faceStatus = 0;
  g_dwSourceVert = (uint)verts;
  g_dwDestVert = (uint)&g_dwWorkVerts;
  pfVar11 = verts + count * 3 + -3;
  pfVar13 = verts;
  if (0 < count) {
    do {
      fVar2 = PUN(float,frustum[3]);
      fVar1 = PUN(float,frustum[3]);
      if ((fVar2 <= *pfVar11) || (fVar1 <= *pfVar13)) {
        iVar8 = iVar7;
        if (((*pfVar11 != fVar2) && (fVar1 != *pfVar13)) &&
           ((*pfVar11 < fVar2 || (*pfVar13 < fVar1)))) {
          fVar3 = (fVar2 - *pfVar11) / (*pfVar13 - *pfVar11);
          iVar9 = iVar9 + 1;
          iVar8 = iVar7 + 0xc;
          *(float *)((int)puVar10 + iVar7) = fVar2;
          *(float *)((g_dwDestVert - 8) + iVar8) = (pfVar13[1] - pfVar11[1]) * fVar3 + pfVar11[1];
          *(float *)((g_dwDestVert - 4) + iVar8) = (pfVar13[2] - pfVar11[2]) * fVar3 + pfVar11[2];
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x10;
          puVar10 = (uint *)g_dwDestVert;
        }
        iVar7 = iVar8;
        if (fVar1 <= *pfVar13) {
          pfVar11 = (float *)((int)puVar10 + iVar8);
          iVar9 = iVar9 + 1;
          iVar7 = iVar8 + 0xc;
          *pfVar11 = *pfVar13;
          pfVar11[1] = pfVar13[1];
          pfVar11[2] = pfVar13[2];
          puVar10 = (uint *)g_dwDestVert;
        }
      }
      count = count + -1;
      pfVar11 = pfVar13;
      pfVar13 = pfVar13 + 3;
    } while (count != 0);
  }
  if (2 < iVar9) {
    iVar7 = 0;
    uVar5 = g_dwSourceVert;
    g_dwDestVert = g_dwSourceVert;
    pfVar11 = (float *)puVar10;
    if (0 < iVar9) {
      iVar8 = 0;
      pfVar13 = (float *)(puVar10 + iVar9 * 3 + -3);
      g_dwSourceVert = (uint)puVar10;
      count = iVar9;
      do {
        fVar2 = PUN(float,frustum[5]);
        fVar1 = PUN(float,frustum[5]);
        if ((*pfVar13 <= fVar2) || (PUN(float,*puVar10) <= fVar1)) {
          if (((*pfVar13 != fVar2) && (fVar1 != PUN(float,*puVar10))) &&
             ((fVar2 < *pfVar13 || (fVar1 < PUN(float,*puVar10))))) {
            fVar3 = (fVar2 - *pfVar13) / (PUN(float,*puVar10) - *pfVar13);
            iVar7 = iVar7 + 1;
            iVar8 = iVar8 + 0xc;
            *(float *)((uVar5 - 0xc) + iVar8) = fVar2;
            *(float *)((g_dwDestVert - 8) + iVar8) =
                 (PUN(float,puVar10[1]) - pfVar13[1]) * fVar3 + pfVar13[1];
            *(float *)((g_dwDestVert - 4) + iVar8) =
                 (PUN(float,puVar10[2]) - pfVar13[2]) * fVar3 + pfVar13[2];
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x20;
            uVar5 = g_dwDestVert;
          }
          if (PUN(float,*puVar10) <= fVar1) {
            pfVar11 = (float *)(uVar5 + iVar8);
            iVar7 = iVar7 + 1;
            iVar8 = iVar8 + 0xc;
            *pfVar11 = PUN(float,*puVar10);
            pfVar11[1] = PUN(float,puVar10[1]);
            pfVar11[2] = PUN(float,puVar10[2]);
            uVar5 = g_dwDestVert;
          }
        }
        count = count + -1;
        pfVar13 = (float *)puVar10;
        puVar10 = puVar10 + 3;
        pfVar11 = (float *)g_dwSourceVert;
      } while (count != 0);
    }
    g_dwSourceVert = (uint)pfVar11;
    iVar9 = iVar7;
    if (2 < iVar9) {
      iVar7 = 0;
      pfVar11 = (float *)((uVar5 - 0xc) + iVar9 * 0xc);
      uVar12 = g_dwSourceVert;
      g_dwDestVert = g_dwSourceVert;
      if (0 < iVar9) {
        pfVar13 = (float *)(uVar5 + 8);
        iVar8 = 0;
        g_dwSourceVert = uVar5;
        count = iVar9;
        do {
          fVar2 = PUN(float,frustum[4]);
          fVar1 = PUN(float,frustum[4]);
          if ((pfVar11[2] <= fVar2) || (*pfVar13 <= fVar1)) {
            if (((pfVar11[2] != fVar2) && (fVar1 != *pfVar13)) &&
               ((fVar2 < pfVar11[2] || (fVar1 < *pfVar13)))) {
              fVar3 = (fVar2 - pfVar11[2]) / (*pfVar13 - pfVar11[2]);
              iVar7 = iVar7 + 1;
              iVar8 = iVar8 + 0xc;
              *(float *)((uVar12 - 0xc) + iVar8) = (pfVar13[-2] - *pfVar11) * fVar3 + *pfVar11;
              *(float *)((g_dwDestVert - 8) + iVar8) =
                   (pfVar13[-1] - pfVar11[1]) * fVar3 + pfVar11[1];
              *(float *)((g_dwDestVert - 4) + iVar8) = fVar2;
              g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 4;
              uVar12 = g_dwDestVert;
            }
            if (*pfVar13 <= fVar1) {
              pfVar11 = (float *)(uVar12 + iVar8);
              iVar7 = iVar7 + 1;
              iVar8 = iVar8 + 0xc;
              *pfVar11 = pfVar13[-2];
              pfVar11[1] = pfVar13[-1];
              pfVar11[2] = *pfVar13;
              uVar12 = g_dwDestVert;
            }
          }
          pfVar11 = pfVar13 + -2;
          pfVar13 = pfVar13 + 3;
          count = count + -1;
          uVar5 = g_dwSourceVert;
        } while (count != 0);
      }
      g_dwSourceVert = uVar5;
      iVar9 = iVar7;
      if (2 < iVar9) {
        iVar7 = 0;
        pfVar11 = (float *)((uVar12 - 0xc) + iVar9 * 0xc);
        uVar5 = g_dwSourceVert;
        g_dwDestVert = g_dwSourceVert;
        if (0 < iVar9) {
          pfVar13 = (float *)(uVar12 + 8);
          iVar8 = 0;
          g_dwSourceVert = uVar12;
          count = iVar9;
          do {
            fVar2 = PUN(float,frustum[6]);
            fVar1 = PUN(float,frustum[6]);
            if ((fVar2 <= pfVar11[2]) || (fVar1 <= *pfVar13)) {
              if (((pfVar11[2] != fVar2) && (fVar1 != *pfVar13)) &&
                 ((pfVar11[2] < fVar2 || (*pfVar13 < fVar1)))) {
                fVar3 = (fVar2 - pfVar11[2]) / (*pfVar13 - pfVar11[2]);
                iVar7 = iVar7 + 1;
                iVar8 = iVar8 + 0xc;
                *(float *)((uVar5 - 0xc) + iVar8) = (pfVar13[-2] - *pfVar11) * fVar3 + *pfVar11;
                *(float *)((g_dwDestVert - 8) + iVar8) =
                     (pfVar13[-1] - pfVar11[1]) * fVar3 + pfVar11[1];
                *(float *)((g_dwDestVert - 4) + iVar8) = fVar2;
                g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 8;
                uVar5 = g_dwDestVert;
              }
              if (fVar1 <= *pfVar13) {
                pfVar11 = (float *)(uVar5 + iVar8);
                iVar7 = iVar7 + 1;
                iVar8 = iVar8 + 0xc;
                *pfVar11 = pfVar13[-2];
                pfVar11[1] = pfVar13[-1];
                pfVar11[2] = *pfVar13;
                uVar5 = g_dwDestVert;
              }
            }
            pfVar11 = pfVar13 + -2;
            pfVar13 = pfVar13 + 3;
            count = count + -1;
            uVar12 = g_dwSourceVert;
          } while (count != 0);
        }
        g_dwSourceVert = uVar12;
        iVar9 = iVar7;
        if (2 < iVar9) {
          iVar7 = 0;
          pfVar11 = (float *)((uVar5 - 0xc) + iVar9 * 0xc);
          pfVar13 = (float *)g_dwSourceVert;
          g_dwDestVert = g_dwSourceVert;
          if (0 < iVar9) {
            pfVar4 = (float *)(uVar5 + 4);
            iVar8 = 0;
            g_dwSourceVert = uVar5;
            count = iVar9;
            do {
              if ((PUN(float,frustum[1]) <= pfVar11[1]) || (PUN(float,frustum[1]) <= *pfVar4)) {
                if (((pfVar11[1] != PUN(float,frustum[1])) && (*pfVar4 != PUN(float,frustum[1]))) &&
                   ((pfVar11[1] < PUN(float,frustum[1]) || (*pfVar4 < PUN(float,frustum[1]))))) {
                  iVar7 = iVar7 + 1;
                  fVar1 = (PUN(float,frustum[1]) - pfVar11[1]) / (*pfVar4 - pfVar11[1]);
                  *(int *)((int)pfVar13 + iVar8 + 4) = frustum[1];
                  iVar8 = iVar8 + 0xc;
                  *(float *)((g_dwDestVert - 4) + iVar8) =
                       (pfVar4[1] - pfVar11[2]) * fVar1 + pfVar11[2];
                  *(float *)((g_dwDestVert - 0xc) + iVar8) =
                       (pfVar4[-1] - *pfVar11) * fVar1 + *pfVar11;
                  g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 1;
                  pfVar13 = (float *)g_dwDestVert;
                }
                if (PUN(float,frustum[1]) <= *pfVar4) {
                  pfVar13 = (float *)((int)pfVar13 + iVar8);
                  iVar7 = iVar7 + 1;
                  iVar8 = iVar8 + 0xc;
                  *pfVar13 = pfVar4[-1];
                  pfVar13[1] = *pfVar4;
                  pfVar13[2] = pfVar4[1];
                  pfVar13 = (float *)g_dwDestVert;
                }
              }
              pfVar11 = pfVar4 + -1;
              pfVar4 = pfVar4 + 3;
              count = count + -1;
              uVar5 = g_dwSourceVert;
            } while (count != 0);
          }
          g_dwSourceVert = uVar5;
          if (iVar7 < 3) {
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x40;
            return iVar7;
          }
          iVar9 = iVar7;
          pfVar11 = pfVar13;
          if (*frustum != 0) {
            iVar9 = 0;
            pfVar4 = pfVar13 + iVar7 * 3 + -3;
            pfVar11 = (float *)g_dwSourceVert;
            g_dwDestVert = g_dwSourceVert;
            if (0 < iVar7) {
              pfVar6 = pfVar13 + 1;
              iVar8 = 0;
              g_dwSourceVert = (uint)pfVar13;
              count = iVar7;
              do {
                if ((pfVar4[1] <= PUN(float,frustum[2])) || (*pfVar6 <= PUN(float,frustum[2]))) {
                  if (((pfVar4[1] != PUN(float,frustum[2])) && (*pfVar6 != PUN(float,frustum[2]))) &&
                     ((PUN(float,frustum[2]) < pfVar4[1] || (PUN(float,frustum[2]) < *pfVar6)))) {
                    iVar9 = iVar9 + 1;
                    fVar1 = (PUN(float,frustum[2]) - pfVar4[1]) / (*pfVar6 - pfVar4[1]);
                    *(int *)((int)pfVar11 + iVar8 + 4) = frustum[2];
                    iVar8 = iVar8 + 0xc;
                    *(float *)((g_dwDestVert - 4) + iVar8) =
                         (pfVar6[1] - pfVar4[2]) * fVar1 + pfVar4[2];
                    *(float *)((g_dwDestVert - 0xc) + iVar8) =
                         (pfVar6[-1] - *pfVar4) * fVar1 + *pfVar4;
                    g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 2;
                    pfVar11 = (float *)g_dwDestVert;
                  }
                  if (*pfVar6 <= PUN(float,frustum[2])) {
                    pfVar11 = (float *)((int)pfVar11 + iVar8);
                    iVar9 = iVar9 + 1;
                    iVar8 = iVar8 + 0xc;
                    *pfVar11 = pfVar6[-1];
                    pfVar11[1] = *pfVar6;
                    pfVar11[2] = pfVar6[1];
                    pfVar11 = (float *)g_dwDestVert;
                  }
                }
                pfVar4 = pfVar6 + -1;
                pfVar6 = pfVar6 + 3;
                count = count + -1;
                pfVar13 = (float *)g_dwSourceVert;
              } while (count != 0);
            }
            g_dwSourceVert = (uint)pfVar13;
            if (iVar9 < 3) {
              return iVar9;
            }
          }
          if (pfVar11 != verts) {
            for (uVar5 = iVar9 * 3 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
              *verts = *pfVar11;
              pfVar11 = pfVar11 + 1;
              verts = verts + 1;
            }
            for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
              *(undefined1 *)verts = *(undefined1 *)pfVar11;
              pfVar11 = (float *)((int)pfVar11 + 1);
              verts = (float *)((int)verts + 1);
            }
          }
        }
      }
    }
  }
  return iVar9;
}
#endif


/* ---- 0x004489b0  rdClip_Face3S ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdClip_Face3S (the remaster's GrimFandango (Linux): the matching branch of the
   rdPrimit3_ClipFace switch (geometry/lighting mode, perspective or ortho camera)); was
   rdClip_Face3_Pos_2. */

uint __cdecl rdClip_Face3S(int *frustum,float *verts,uint count)

{
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
  uint local_8;
  uint local_4;
  
  uVar12 = 0;
  puVar14 = &g_dwWorkVerts;
  g_dwRdClip_faceStatus = 0;
  g_dwSourceVert = (uint)verts;
  g_dwDestVert = (uint)&g_dwWorkVerts;
  if (0 < (int)count) {
    iVar11 = 0;
    local_4 = count;
    pfVar15 = verts + count * 3 + -3;
    pfVar8 = verts;
    do {
      fVar2 = pfVar15[1] * PUN(float,frustum[0xc]);
      fVar3 = pfVar8[1] * PUN(float,frustum[0xc]);
      if ((fVar2 <= *pfVar15) || (fVar3 <= *pfVar8)) {
        if (((*pfVar15 != fVar2) && (fVar3 != *pfVar8)) && ((*pfVar15 < fVar2 || (*pfVar8 < fVar3)))
           ) {
          fVar2 = pfVar8[1] - pfVar15[1];
          fVar4 = *pfVar8 - *pfVar15;
          fVar1 = PUN(float,frustum[0xc]) * fVar2 - fVar4;
          fVar5 = pfVar8[1] * *pfVar15 - pfVar15[1] * *pfVar8;
          if (fVar1 != 0.0f) {
            fVar5 = fVar5 / fVar1;
          }
          fVar1 = fVar2;
          if (fVar2 < 0.0f) {
            fVar1 = -fVar2;
          }
          fVar6 = fVar4;
          if (fVar4 < 0.0f) {
            fVar6 = -fVar4;
          }
          if (fVar1 <= fVar6) {
            fVar2 = (PUN(float,frustum[0xc]) * fVar5 - *pfVar15) / fVar4;
          }
          else {
            fVar2 = (fVar5 - pfVar15[1]) / fVar2;
          }
          *(float *)((int)puVar14 + iVar11) = PUN(float,frustum[0xc]) * fVar5;
          uVar12 = uVar12 + 1;
          *(float *)(g_dwDestVert + 4 + iVar11) = fVar5;
          iVar11 = iVar11 + 0xc;
          *(float *)((g_dwDestVert - 4) + iVar11) = (pfVar8[2] - pfVar15[2]) * fVar2 + pfVar15[2];
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x10;
          puVar14 = (uint *)g_dwDestVert;
        }
        if (fVar3 <= *pfVar8) {
          pfVar15 = (float *)((int)puVar14 + iVar11);
          uVar12 = uVar12 + 1;
          iVar11 = iVar11 + 0xc;
          *pfVar15 = *pfVar8;
          pfVar15[1] = pfVar8[1];
          pfVar15[2] = pfVar8[2];
          puVar14 = (uint *)g_dwDestVert;
        }
      }
      local_4 = local_4 - 1;
      pfVar15 = pfVar8;
      pfVar8 = pfVar8 + 3;
    } while (local_4 != 0);
  }
  if (2 < (int)uVar12) {
    uVar13 = 0;
    uVar17 = g_dwSourceVert;
    g_dwDestVert = g_dwSourceVert;
    pfVar15 = (float *)puVar14;
    if (0 < (int)uVar12) {
      iVar11 = 0;
      pfVar8 = (float *)(puVar14 + uVar12 * 3 + -3);
      g_dwSourceVert = (uint)puVar14;
      local_4 = uVar12;
      do {
        fVar2 = PUN(float,frustum[10]) * pfVar8[1];
        fVar3 = PUN(float,frustum[10]) * PUN(float,puVar14[1]);
        if ((*pfVar8 <= fVar2) || (PUN(float,*puVar14) <= fVar3)) {
          if (((*pfVar8 != fVar2) && (fVar3 != PUN(float,*puVar14))) &&
             ((fVar2 < *pfVar8 || (fVar3 < PUN(float,*puVar14))))) {
            fVar2 = PUN(float,puVar14[1]) - pfVar8[1];
            fVar4 = PUN(float,*puVar14) - *pfVar8;
            fVar1 = PUN(float,frustum[10]) * fVar2 - fVar4;
            fVar5 = PUN(float,puVar14[1]) * *pfVar8 - pfVar8[1] * PUN(float,*puVar14);
            if (fVar1 != 0.0f) {
              fVar5 = fVar5 / fVar1;
            }
            fVar1 = fVar2;
            if (fVar2 < 0.0f) {
              fVar1 = -fVar2;
            }
            fVar6 = fVar4;
            if (fVar4 < 0.0f) {
              fVar6 = -fVar4;
            }
            if (fVar1 <= fVar6) {
              fVar2 = (PUN(float,frustum[10]) * fVar5 - *pfVar8) / fVar4;
            }
            else {
              fVar2 = (fVar5 - pfVar8[1]) / fVar2;
            }
            *(float *)(uVar17 + iVar11) = PUN(float,frustum[10]) * fVar5;
            uVar13 = uVar13 + 1;
            *(float *)(g_dwDestVert + 4 + iVar11) = fVar5;
            iVar11 = iVar11 + 0xc;
            *(float *)((g_dwDestVert - 4) + iVar11) =
                 (PUN(float,puVar14[2]) - pfVar8[2]) * fVar2 + pfVar8[2];
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x20;
            uVar17 = g_dwDestVert;
          }
          if (PUN(float,*puVar14) <= fVar3) {
            pfVar15 = (float *)(uVar17 + iVar11);
            uVar13 = uVar13 + 1;
            iVar11 = iVar11 + 0xc;
            *pfVar15 = PUN(float,*puVar14);
            pfVar15[1] = PUN(float,puVar14[1]);
            pfVar15[2] = PUN(float,puVar14[2]);
            uVar17 = g_dwDestVert;
          }
        }
        local_4 = local_4 - 1;
        pfVar8 = (float *)puVar14;
        puVar14 = puVar14 + 3;
        pfVar15 = (float *)g_dwSourceVert;
      } while (local_4 != 0);
    }
    g_dwSourceVert = (uint)pfVar15;
    uVar12 = uVar13;
    if (2 < (int)uVar12) {
      uVar13 = 0;
      g_dwDestVert = g_dwSourceVert;
      pfVar15 = (float *)((uVar17 - 0xc) + uVar12 * 0xc);
      uVar16 = g_dwSourceVert;
      if (0 < (int)uVar12) {
        iVar11 = 0;
        pfVar8 = (float *)(uVar17 + 8);
        g_dwSourceVert = uVar17;
        local_4 = uVar12;
        do {
          fVar2 = PUN(float,frustum[0xb]) * pfVar15[1];
          fVar3 = pfVar8[-1] * PUN(float,frustum[0xb]);
          if ((pfVar15[2] <= fVar2) || (*pfVar8 <= fVar3)) {
            if (((pfVar15[2] != fVar2) && (fVar3 != *pfVar8)) &&
               ((fVar2 < pfVar15[2] || (fVar3 < *pfVar8)))) {
              fVar2 = pfVar8[-1] - pfVar15[1];
              fVar4 = *pfVar8 - pfVar15[2];
              fVar1 = PUN(float,frustum[0xb]) * fVar2 - fVar4;
              fVar5 = pfVar15[2] * pfVar8[-1] - pfVar15[1] * *pfVar8;
              if (fVar1 != 0.0f) {
                fVar5 = fVar5 / fVar1;
              }
              fVar1 = PUN(float,frustum[0xb]);
              fVar6 = fVar2;
              if (fVar2 < 0.0f) {
                fVar6 = -fVar2;
              }
              fVar7 = fVar4;
              if (fVar4 < 0.0f) {
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
              *(float *)((g_dwDestVert - 8) + iVar11) = fVar5;
              *(float *)((g_dwDestVert - 4) + iVar11) = fVar1 * fVar5;
              g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 4;
              uVar16 = g_dwDestVert;
            }
            if (*pfVar8 <= fVar3) {
              pfVar15 = (float *)(uVar16 + iVar11);
              uVar13 = uVar13 + 1;
              iVar11 = iVar11 + 0xc;
              *pfVar15 = pfVar8[-2];
              pfVar15[1] = pfVar8[-1];
              pfVar15[2] = *pfVar8;
              uVar16 = g_dwDestVert;
            }
          }
          pfVar15 = pfVar8 + -2;
          pfVar8 = pfVar8 + 3;
          local_4 = local_4 - 1;
          uVar17 = g_dwSourceVert;
        } while (local_4 != 0);
      }
      g_dwSourceVert = uVar17;
      uVar12 = uVar13;
      if (2 < (int)uVar12) {
        uVar13 = 0;
        g_dwDestVert = g_dwSourceVert;
        pfVar15 = (float *)((uVar16 - 0xc) + uVar12 * 0xc);
        uVar17 = g_dwSourceVert;
        if (0 < (int)uVar12) {
          iVar11 = 0;
          pfVar8 = (float *)(uVar16 + 8);
          g_dwSourceVert = uVar16;
          local_4 = uVar12;
          do {
            fVar2 = PUN(float,frustum[8]) * pfVar15[1];
            fVar3 = pfVar8[-1] * PUN(float,frustum[8]);
            if ((fVar2 <= pfVar15[2]) || (fVar3 <= *pfVar8)) {
              if (((pfVar15[2] != fVar2) && (fVar3 != *pfVar8)) &&
                 ((pfVar15[2] < fVar2 || (*pfVar8 < fVar3)))) {
                fVar2 = pfVar8[-1] - pfVar15[1];
                fVar4 = *pfVar8 - pfVar15[2];
                fVar1 = PUN(float,frustum[8]) * fVar2 - fVar4;
                fVar5 = pfVar15[2] * pfVar8[-1] - pfVar15[1] * *pfVar8;
                if (fVar1 != 0.0f) {
                  fVar5 = fVar5 / fVar1;
                }
                fVar1 = PUN(float,frustum[8]);
                fVar6 = fVar2;
                if (fVar2 < 0.0f) {
                  fVar6 = -fVar2;
                }
                fVar7 = fVar4;
                if (fVar4 < 0.0f) {
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
                *(float *)((g_dwDestVert - 8) + iVar11) = fVar5;
                *(float *)((g_dwDestVert - 4) + iVar11) = fVar1 * fVar5;
                g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 8;
                uVar17 = g_dwDestVert;
              }
              if (fVar3 <= *pfVar8) {
                pfVar15 = (float *)(uVar17 + iVar11);
                uVar13 = uVar13 + 1;
                iVar11 = iVar11 + 0xc;
                *pfVar15 = pfVar8[-2];
                pfVar15[1] = pfVar8[-1];
                pfVar15[2] = *pfVar8;
                uVar17 = g_dwDestVert;
              }
            }
            pfVar15 = pfVar8 + -2;
            pfVar8 = pfVar8 + 3;
            local_4 = local_4 - 1;
            uVar16 = g_dwSourceVert;
          } while (local_4 != 0);
        }
        g_dwSourceVert = uVar16;
        uVar12 = uVar13;
        if (2 < (int)uVar12) {
          uVar13 = 0;
          g_dwDestVert = g_dwSourceVert;
          pfVar15 = (float *)((uVar17 - 0xc) + uVar12 * 0xc);
          pfVar8 = (float *)g_dwSourceVert;
          if (0 < (int)uVar12) {
            iVar11 = 0;
            pfVar9 = (float *)(uVar17 + 4);
            g_dwSourceVert = uVar17;
            count = uVar12;
            do {
              if ((PUN(float,frustum[1]) <= pfVar15[1]) || (PUN(float,frustum[1]) <= *pfVar9)) {
                if (((pfVar15[1] != PUN(float,frustum[1])) && (*pfVar9 != PUN(float,frustum[1]))) &&
                   ((pfVar15[1] < PUN(float,frustum[1]) || (*pfVar9 < PUN(float,frustum[1]))))) {
                  uVar13 = uVar13 + 1;
                  fVar2 = (PUN(float,frustum[1]) - pfVar15[1]) / (*pfVar9 - pfVar15[1]);
                  *(int *)((int)pfVar8 + iVar11 + 4) = frustum[1];
                  iVar11 = iVar11 + 0xc;
                  *(float *)((g_dwDestVert - 4) + iVar11) =
                       (pfVar9[1] - pfVar15[2]) * fVar2 + pfVar15[2];
                  *(float *)((g_dwDestVert - 0xc) + iVar11) =
                       (pfVar9[-1] - *pfVar15) * fVar2 + *pfVar15;
                  g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 1;
                  pfVar8 = (float *)g_dwDestVert;
                }
                if (PUN(float,frustum[1]) <= *pfVar9) {
                  pfVar8 = (float *)((int)pfVar8 + iVar11);
                  uVar13 = uVar13 + 1;
                  iVar11 = iVar11 + 0xc;
                  *pfVar8 = pfVar9[-1];
                  pfVar8[1] = *pfVar9;
                  pfVar8[2] = pfVar9[1];
                  pfVar8 = (float *)g_dwDestVert;
                }
              }
              pfVar15 = pfVar9 + -1;
              pfVar9 = pfVar9 + 3;
              count = count - 1;
              uVar17 = g_dwSourceVert;
            } while (count != 0);
          }
          g_dwSourceVert = uVar17;
          if ((int)uVar13 < 3) {
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x40;
            return uVar13;
          }
          uVar12 = uVar13;
          pfVar15 = pfVar8;
          if (*frustum != 0) {
            uVar12 = 0;
            pfVar9 = pfVar8 + uVar13 * 3 + -3;
            pfVar15 = (float *)g_dwSourceVert;
            g_dwDestVert = g_dwSourceVert;
            if (0 < (int)uVar13) {
              iVar11 = 0;
              pfVar10 = pfVar8 + 1;
              g_dwSourceVert = (uint)pfVar8;
              count = uVar13;
              do {
                if ((pfVar9[1] <= PUN(float,frustum[2])) || (*pfVar10 <= PUN(float,frustum[2]))) {
                  if (((pfVar9[1] != PUN(float,frustum[2])) && (*pfVar10 != PUN(float,frustum[2]))) &&
                     ((PUN(float,frustum[2]) < pfVar9[1] || (PUN(float,frustum[2]) < *pfVar10)))) {
                    uVar12 = uVar12 + 1;
                    fVar2 = (PUN(float,frustum[2]) - pfVar9[1]) / (*pfVar10 - pfVar9[1]);
                    *(int *)((int)pfVar15 + iVar11 + 4) = frustum[2];
                    iVar11 = iVar11 + 0xc;
                    *(float *)((g_dwDestVert - 4) + iVar11) =
                         (pfVar10[1] - pfVar9[2]) * fVar2 + pfVar9[2];
                    *(float *)((g_dwDestVert - 0xc) + iVar11) =
                         (pfVar10[-1] - *pfVar9) * fVar2 + *pfVar9;
                    g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 2;
                    pfVar15 = (float *)g_dwDestVert;
                  }
                  if (*pfVar10 <= PUN(float,frustum[2])) {
                    pfVar15 = (float *)((int)pfVar15 + iVar11);
                    uVar12 = uVar12 + 1;
                    iVar11 = iVar11 + 0xc;
                    *pfVar15 = pfVar10[-1];
                    pfVar15[1] = *pfVar10;
                    pfVar15[2] = pfVar10[1];
                    pfVar15 = (float *)g_dwDestVert;
                  }
                }
                pfVar9 = pfVar10 + -1;
                pfVar10 = pfVar10 + 3;
                count = count - 1;
                pfVar8 = (float *)g_dwSourceVert;
              } while (count != 0);
            }
            g_dwSourceVert = (uint)pfVar8;
            if ((int)uVar12 < 3) {
              return uVar12;
            }
          }
          if (pfVar15 != verts) {
            for (uVar13 = uVar12 * 3 & 0x3fffffff; uVar13 != 0; uVar13 = uVar13 - 1) {
              *verts = *pfVar15;
              pfVar15 = pfVar15 + 1;
              verts = verts + 1;
            }
            for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
              *(undefined1 *)verts = *(undefined1 *)pfVar15;
              pfVar15 = (float *)((int)pfVar15 + 1);
              verts = (float *)((int)verts + 1);
            }
          }
        }
      }
    }
  }
  return uVar12;
}
#endif


/* ---- 0x00449350  rdClip_Face3SOrtho ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdClip_Face3SOrtho (the remaster's GrimFandango (Linux): the matching branch of the
   rdPrimit3_ClipFace switch (geometry/lighting mode, perspective or ortho camera)); was
   rdClip_Face3_PosB_2. */

int __cdecl rdClip_Face3SOrtho(int *frustum,float *verts,int count)

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
  puVar10 = &g_dwWorkVerts;
  iVar9 = 0;
  g_dwRdClip_faceStatus = 0;
  g_dwSourceVert = (uint)verts;
  g_dwDestVert = (uint)&g_dwWorkVerts;
  pfVar11 = verts + count * 3 + -3;
  pfVar13 = verts;
  if (0 < count) {
    do {
      fVar2 = PUN(float,frustum[3]);
      fVar1 = PUN(float,frustum[3]);
      if ((fVar2 <= *pfVar11) || (fVar1 <= *pfVar13)) {
        iVar8 = iVar7;
        if (((*pfVar11 != fVar2) && (fVar1 != *pfVar13)) &&
           ((*pfVar11 < fVar2 || (*pfVar13 < fVar1)))) {
          fVar3 = (fVar2 - *pfVar11) / (*pfVar13 - *pfVar11);
          iVar9 = iVar9 + 1;
          iVar8 = iVar7 + 0xc;
          *(float *)((int)puVar10 + iVar7) = fVar2;
          *(float *)((g_dwDestVert - 8) + iVar8) = (pfVar13[1] - pfVar11[1]) * fVar3 + pfVar11[1];
          *(float *)((g_dwDestVert - 4) + iVar8) = (pfVar13[2] - pfVar11[2]) * fVar3 + pfVar11[2];
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x10;
          puVar10 = (uint *)g_dwDestVert;
        }
        iVar7 = iVar8;
        if (fVar1 <= *pfVar13) {
          pfVar11 = (float *)((int)puVar10 + iVar8);
          iVar9 = iVar9 + 1;
          iVar7 = iVar8 + 0xc;
          *pfVar11 = *pfVar13;
          pfVar11[1] = pfVar13[1];
          pfVar11[2] = pfVar13[2];
          puVar10 = (uint *)g_dwDestVert;
        }
      }
      count = count + -1;
      pfVar11 = pfVar13;
      pfVar13 = pfVar13 + 3;
    } while (count != 0);
  }
  if (2 < iVar9) {
    iVar7 = 0;
    uVar5 = g_dwSourceVert;
    g_dwDestVert = g_dwSourceVert;
    pfVar11 = (float *)puVar10;
    if (0 < iVar9) {
      iVar8 = 0;
      pfVar13 = (float *)(puVar10 + iVar9 * 3 + -3);
      g_dwSourceVert = (uint)puVar10;
      count = iVar9;
      do {
        fVar2 = PUN(float,frustum[5]);
        fVar1 = PUN(float,frustum[5]);
        if ((*pfVar13 <= fVar2) || (PUN(float,*puVar10) <= fVar1)) {
          if (((*pfVar13 != fVar2) && (fVar1 != PUN(float,*puVar10))) &&
             ((fVar2 < *pfVar13 || (fVar1 < PUN(float,*puVar10))))) {
            fVar3 = (fVar2 - *pfVar13) / (PUN(float,*puVar10) - *pfVar13);
            iVar7 = iVar7 + 1;
            iVar8 = iVar8 + 0xc;
            *(float *)((uVar5 - 0xc) + iVar8) = fVar2;
            *(float *)((g_dwDestVert - 8) + iVar8) =
                 (PUN(float,puVar10[1]) - pfVar13[1]) * fVar3 + pfVar13[1];
            *(float *)((g_dwDestVert - 4) + iVar8) =
                 (PUN(float,puVar10[2]) - pfVar13[2]) * fVar3 + pfVar13[2];
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x20;
            uVar5 = g_dwDestVert;
          }
          if (PUN(float,*puVar10) <= fVar1) {
            pfVar11 = (float *)(uVar5 + iVar8);
            iVar7 = iVar7 + 1;
            iVar8 = iVar8 + 0xc;
            *pfVar11 = PUN(float,*puVar10);
            pfVar11[1] = PUN(float,puVar10[1]);
            pfVar11[2] = PUN(float,puVar10[2]);
            uVar5 = g_dwDestVert;
          }
        }
        count = count + -1;
        pfVar13 = (float *)puVar10;
        puVar10 = puVar10 + 3;
        pfVar11 = (float *)g_dwSourceVert;
      } while (count != 0);
    }
    g_dwSourceVert = (uint)pfVar11;
    iVar9 = iVar7;
    if (2 < iVar9) {
      iVar7 = 0;
      pfVar11 = (float *)((uVar5 - 0xc) + iVar9 * 0xc);
      uVar12 = g_dwSourceVert;
      g_dwDestVert = g_dwSourceVert;
      if (0 < iVar9) {
        pfVar13 = (float *)(uVar5 + 8);
        iVar8 = 0;
        g_dwSourceVert = uVar5;
        count = iVar9;
        do {
          fVar2 = PUN(float,frustum[4]);
          fVar1 = PUN(float,frustum[4]);
          if ((pfVar11[2] <= fVar2) || (*pfVar13 <= fVar1)) {
            if (((pfVar11[2] != fVar2) && (fVar1 != *pfVar13)) &&
               ((fVar2 < pfVar11[2] || (fVar1 < *pfVar13)))) {
              fVar3 = (fVar2 - pfVar11[2]) / (*pfVar13 - pfVar11[2]);
              iVar7 = iVar7 + 1;
              iVar8 = iVar8 + 0xc;
              *(float *)((uVar12 - 0xc) + iVar8) = (pfVar13[-2] - *pfVar11) * fVar3 + *pfVar11;
              *(float *)((g_dwDestVert - 8) + iVar8) =
                   (pfVar13[-1] - pfVar11[1]) * fVar3 + pfVar11[1];
              *(float *)((g_dwDestVert - 4) + iVar8) = fVar2;
              g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 4;
              uVar12 = g_dwDestVert;
            }
            if (*pfVar13 <= fVar1) {
              pfVar11 = (float *)(uVar12 + iVar8);
              iVar7 = iVar7 + 1;
              iVar8 = iVar8 + 0xc;
              *pfVar11 = pfVar13[-2];
              pfVar11[1] = pfVar13[-1];
              pfVar11[2] = *pfVar13;
              uVar12 = g_dwDestVert;
            }
          }
          pfVar11 = pfVar13 + -2;
          pfVar13 = pfVar13 + 3;
          count = count + -1;
          uVar5 = g_dwSourceVert;
        } while (count != 0);
      }
      g_dwSourceVert = uVar5;
      iVar9 = iVar7;
      if (2 < iVar9) {
        iVar7 = 0;
        pfVar11 = (float *)((uVar12 - 0xc) + iVar9 * 0xc);
        uVar5 = g_dwSourceVert;
        g_dwDestVert = g_dwSourceVert;
        if (0 < iVar9) {
          pfVar13 = (float *)(uVar12 + 8);
          iVar8 = 0;
          g_dwSourceVert = uVar12;
          count = iVar9;
          do {
            fVar2 = PUN(float,frustum[6]);
            fVar1 = PUN(float,frustum[6]);
            if ((fVar2 <= pfVar11[2]) || (fVar1 <= *pfVar13)) {
              if (((pfVar11[2] != fVar2) && (fVar1 != *pfVar13)) &&
                 ((pfVar11[2] < fVar2 || (*pfVar13 < fVar1)))) {
                fVar3 = (fVar2 - pfVar11[2]) / (*pfVar13 - pfVar11[2]);
                iVar7 = iVar7 + 1;
                iVar8 = iVar8 + 0xc;
                *(float *)((uVar5 - 0xc) + iVar8) = (pfVar13[-2] - *pfVar11) * fVar3 + *pfVar11;
                *(float *)((g_dwDestVert - 8) + iVar8) =
                     (pfVar13[-1] - pfVar11[1]) * fVar3 + pfVar11[1];
                *(float *)((g_dwDestVert - 4) + iVar8) = fVar2;
                g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 8;
                uVar5 = g_dwDestVert;
              }
              if (fVar1 <= *pfVar13) {
                pfVar11 = (float *)(uVar5 + iVar8);
                iVar7 = iVar7 + 1;
                iVar8 = iVar8 + 0xc;
                *pfVar11 = pfVar13[-2];
                pfVar11[1] = pfVar13[-1];
                pfVar11[2] = *pfVar13;
                uVar5 = g_dwDestVert;
              }
            }
            pfVar11 = pfVar13 + -2;
            pfVar13 = pfVar13 + 3;
            count = count + -1;
            uVar12 = g_dwSourceVert;
          } while (count != 0);
        }
        g_dwSourceVert = uVar12;
        iVar9 = iVar7;
        if (2 < iVar9) {
          iVar7 = 0;
          pfVar11 = (float *)((uVar5 - 0xc) + iVar9 * 0xc);
          pfVar13 = (float *)g_dwSourceVert;
          g_dwDestVert = g_dwSourceVert;
          if (0 < iVar9) {
            pfVar4 = (float *)(uVar5 + 4);
            iVar8 = 0;
            g_dwSourceVert = uVar5;
            count = iVar9;
            do {
              if ((PUN(float,frustum[1]) <= pfVar11[1]) || (PUN(float,frustum[1]) <= *pfVar4)) {
                if (((pfVar11[1] != PUN(float,frustum[1])) && (*pfVar4 != PUN(float,frustum[1]))) &&
                   ((pfVar11[1] < PUN(float,frustum[1]) || (*pfVar4 < PUN(float,frustum[1]))))) {
                  iVar7 = iVar7 + 1;
                  fVar1 = (PUN(float,frustum[1]) - pfVar11[1]) / (*pfVar4 - pfVar11[1]);
                  *(int *)((int)pfVar13 + iVar8 + 4) = frustum[1];
                  iVar8 = iVar8 + 0xc;
                  *(float *)((g_dwDestVert - 4) + iVar8) =
                       (pfVar4[1] - pfVar11[2]) * fVar1 + pfVar11[2];
                  *(float *)((g_dwDestVert - 0xc) + iVar8) =
                       (pfVar4[-1] - *pfVar11) * fVar1 + *pfVar11;
                  g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 1;
                  pfVar13 = (float *)g_dwDestVert;
                }
                if (PUN(float,frustum[1]) <= *pfVar4) {
                  pfVar13 = (float *)((int)pfVar13 + iVar8);
                  iVar7 = iVar7 + 1;
                  iVar8 = iVar8 + 0xc;
                  *pfVar13 = pfVar4[-1];
                  pfVar13[1] = *pfVar4;
                  pfVar13[2] = pfVar4[1];
                  pfVar13 = (float *)g_dwDestVert;
                }
              }
              pfVar11 = pfVar4 + -1;
              pfVar4 = pfVar4 + 3;
              count = count + -1;
              uVar5 = g_dwSourceVert;
            } while (count != 0);
          }
          g_dwSourceVert = uVar5;
          if (iVar7 < 3) {
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x40;
            return iVar7;
          }
          iVar9 = iVar7;
          pfVar11 = pfVar13;
          if (*frustum != 0) {
            iVar9 = 0;
            pfVar4 = pfVar13 + iVar7 * 3 + -3;
            pfVar11 = (float *)g_dwSourceVert;
            g_dwDestVert = g_dwSourceVert;
            if (0 < iVar7) {
              pfVar6 = pfVar13 + 1;
              iVar8 = 0;
              g_dwSourceVert = (uint)pfVar13;
              count = iVar7;
              do {
                if ((pfVar4[1] <= PUN(float,frustum[2])) || (*pfVar6 <= PUN(float,frustum[2]))) {
                  if (((pfVar4[1] != PUN(float,frustum[2])) && (*pfVar6 != PUN(float,frustum[2]))) &&
                     ((PUN(float,frustum[2]) < pfVar4[1] || (PUN(float,frustum[2]) < *pfVar6)))) {
                    iVar9 = iVar9 + 1;
                    fVar1 = (PUN(float,frustum[2]) - pfVar4[1]) / (*pfVar6 - pfVar4[1]);
                    *(int *)((int)pfVar11 + iVar8 + 4) = frustum[2];
                    iVar8 = iVar8 + 0xc;
                    *(float *)((g_dwDestVert - 4) + iVar8) =
                         (pfVar6[1] - pfVar4[2]) * fVar1 + pfVar4[2];
                    *(float *)((g_dwDestVert - 0xc) + iVar8) =
                         (pfVar6[-1] - *pfVar4) * fVar1 + *pfVar4;
                    g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 2;
                    pfVar11 = (float *)g_dwDestVert;
                  }
                  if (*pfVar6 <= PUN(float,frustum[2])) {
                    pfVar11 = (float *)((int)pfVar11 + iVar8);
                    iVar9 = iVar9 + 1;
                    iVar8 = iVar8 + 0xc;
                    *pfVar11 = pfVar6[-1];
                    pfVar11[1] = *pfVar6;
                    pfVar11[2] = pfVar6[1];
                    pfVar11 = (float *)g_dwDestVert;
                  }
                }
                pfVar4 = pfVar6 + -1;
                pfVar6 = pfVar6 + 3;
                count = count + -1;
                pfVar13 = (float *)g_dwSourceVert;
              } while (count != 0);
            }
            g_dwSourceVert = (uint)pfVar13;
            if (iVar9 < 3) {
              return iVar9;
            }
          }
          if (pfVar11 != verts) {
            for (uVar5 = iVar9 * 3 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
              *verts = *pfVar11;
              pfVar11 = pfVar11 + 1;
              verts = verts + 1;
            }
            for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
              *(undefined1 *)verts = *(undefined1 *)pfVar11;
              pfVar11 = (float *)((int)pfVar11 + 1);
              verts = (float *)((int)verts + 1);
            }
          }
        }
      }
    }
  }
  return iVar9;
}
#endif


/* ---- 0x00449aa0  rdClip_Face3GS ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Face clipper interpolating position, texture coordinate and intensity Original name
   rdClip_Face3GS (the remaster's GrimFandango (Linux): the matching branch of the
   rdPrimit3_ClipFace switch (geometry/lighting mode, perspective or ortho camera)); was
   rdClip_Face3_PosUvLit. */

uint __cdecl rdClip_Face3GS(int *frustum,float *verts,float *ivert,uint count)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  float *pfVar10;
  float fVar11;
  float fVar12;
  float *pfVar13;
  uint *puVar14;
  float *pfVar15;
  float *pfVar16;
  uint uVar17;
  float *pfVar18;
  #define local_10 (*(float (*)[3])(_frame + (0x20 - 0x10)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  fVar11 = 0.0f;
  puVar14 = &g_dwWorkVerts;
  g_dwRdClip_faceStatus = 0;
  g_dwSourceVert = (uint)verts;
  g_dwSourceIVert = (uint)ivert;
  g_dwDestVert = (uint)&g_dwWorkVerts;
  g_dwDestIVert = (uint)&g_dwWorkIVerts;
  if (0 < (int)count) {
    iVar7 = 0;
    local_4 = PUN(float,count);
    pfVar15 = verts;
    pfVar16 = ivert;
    pfVar18 = verts + count * 3 + -3;
    local_10[0] = PUN(float,(ivert + (count - 1)));
    do {
      pfVar13 = pfVar16;
      pfVar10 = pfVar15;
      fVar12 = pfVar18[1] * PUN(float,frustum[0xc]);
      fVar2 = PUN(float,frustum[0xc]) * pfVar10[1];
      if ((fVar12 <= *pfVar18) || (fVar2 <= *pfVar10)) {
        if (((*pfVar18 != fVar12) && (fVar2 != *pfVar10)) &&
           ((*pfVar18 < fVar12 || (*pfVar10 < fVar2)))) {
          fVar12 = pfVar10[1] - pfVar18[1];
          fVar3 = *pfVar10 - *pfVar18;
          fVar1 = PUN(float,frustum[0xc]) * fVar12 - fVar3;
          fVar4 = pfVar10[1] * *pfVar18 - pfVar18[1] * *pfVar10;
          if (fVar1 != 0.0f) {
            fVar4 = fVar4 / fVar1;
          }
          fVar1 = fVar12;
          if (fVar12 < 0.0f) {
            fVar1 = -fVar12;
          }
          fVar5 = fVar3;
          if (fVar3 < 0.0f) {
            fVar5 = -fVar3;
          }
          if (fVar1 <= fVar5) {
            fVar12 = (PUN(float,frustum[0xc]) * fVar4 - *pfVar18) / fVar3;
          }
          else {
            fVar12 = (fVar4 - pfVar18[1]) / fVar12;
          }
          *(float *)((int)puVar14 + iVar7) = PUN(float,frustum[0xc]) * fVar4;
          iVar7 = iVar7 + 0xc;
          *(float *)((g_dwDestVert - 8) + iVar7) = fVar4;
          fVar11 = PUN(float,(PUN(int,(float)fVar11) + 1));
          *(float *)((g_dwDestVert - 4) + iVar7) = (pfVar10[2] - pfVar18[2]) * fVar12 + pfVar18[2];
          *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar11) * 4) =
               (*pfVar13 - *PUN(float *,(float)local_10[0])) * fVar12 + *PUN(float *,(float)local_10[0]);
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x10;
          puVar14 = (uint *)g_dwDestVert;
        }
        if (fVar2 <= *pfVar10) {
          pfVar15 = (float *)((int)puVar14 + iVar7);
          fVar11 = PUN(float,(PUN(int,(float)fVar11) + 1));
          iVar7 = iVar7 + 0xc;
          *pfVar15 = *pfVar10;
          pfVar15[1] = pfVar10[1];
          pfVar15[2] = pfVar10[2];
          *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar11) * 4) = *pfVar13;
          puVar14 = (uint *)g_dwDestVert;
        }
      }
      local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
      pfVar15 = pfVar10 + 3;
      pfVar16 = pfVar13 + 1;
      pfVar18 = pfVar10;
      local_10[0] = PUN(float,pfVar13);
    } while (local_4 != 0.0f);
  }
  uVar9 = g_dwSourceIVert;
  if (2 < PUN(int,(float)fVar11)) {
    g_dwSourceIVert = g_dwDestIVert;
    iVar7 = g_dwDestIVert - 4;
    fVar12 = 0.0f;
    uVar17 = g_dwSourceVert;
    g_dwDestVert = g_dwSourceVert;
    pfVar15 = (float *)puVar14;
    if (0 < PUN(int,(float)fVar11)) {
      iVar8 = 0;
      pfVar16 = (float *)g_dwDestIVert;
      pfVar18 = (float *)(puVar14 + PUN(int,(float)fVar11) * 3 + -3);
      g_dwDestIVert = uVar9;
      g_dwSourceVert = (uint)puVar14;
      local_10[0] = PUN(float,(iVar7 + PUN(int,(float)fVar11) * 4));
      local_4 = fVar11;
      do {
        pfVar10 = pfVar16;
        pfVar15 = (float *)puVar14;
        fVar11 = PUN(float,frustum[10]) * pfVar18[1];
        fVar2 = PUN(float,frustum[10]) * pfVar15[1];
        if ((*pfVar18 <= fVar11) || (*pfVar15 <= fVar2)) {
          if (((*pfVar18 != fVar11) && (fVar2 != *pfVar15)) &&
             ((fVar11 < *pfVar18 || (fVar2 < *pfVar15)))) {
            fVar11 = pfVar15[1] - pfVar18[1];
            fVar3 = *pfVar15 - *pfVar18;
            fVar1 = PUN(float,frustum[10]) * fVar11 - fVar3;
            fVar4 = pfVar15[1] * *pfVar18 - pfVar18[1] * *pfVar15;
            if (fVar1 != 0.0f) {
              fVar4 = fVar4 / fVar1;
            }
            fVar1 = fVar11;
            if (fVar11 < 0.0f) {
              fVar1 = -fVar11;
            }
            fVar5 = fVar3;
            if (fVar3 < 0.0f) {
              fVar5 = -fVar3;
            }
            if (fVar1 <= fVar5) {
              fVar11 = (PUN(float,frustum[10]) * fVar4 - *pfVar18) / fVar3;
            }
            else {
              fVar11 = (fVar4 - pfVar18[1]) / fVar11;
            }
            *(float *)(uVar17 + iVar8) = PUN(float,frustum[10]) * fVar4;
            iVar8 = iVar8 + 0xc;
            *(float *)((g_dwDestVert - 8) + iVar8) = fVar4;
            fVar12 = PUN(float,(PUN(int,(float)fVar12) + 1));
            *(float *)((g_dwDestVert - 4) + iVar8) = (pfVar15[2] - pfVar18[2]) * fVar11 + pfVar18[2]
            ;
            *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar12) * 4) =
                 (*pfVar10 - *PUN(float *,(float)local_10[0])) * fVar11 + *PUN(float *,(float)local_10[0]);
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x20;
            uVar17 = g_dwDestVert;
          }
          if (*pfVar15 <= fVar2) {
            pfVar16 = (float *)(uVar17 + iVar8);
            fVar12 = PUN(float,(PUN(int,(float)fVar12) + 1));
            iVar8 = iVar8 + 0xc;
            *pfVar16 = *pfVar15;
            pfVar16[1] = pfVar15[1];
            pfVar16[2] = pfVar15[2];
            *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar12) * 4) = *pfVar10;
            uVar17 = g_dwDestVert;
          }
        }
        local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
        puVar14 = (uint *)(pfVar15 + 3);
        pfVar16 = pfVar10 + 1;
        pfVar18 = pfVar15;
        uVar9 = g_dwDestIVert;
        pfVar15 = (float *)g_dwSourceVert;
        local_10[0] = PUN(float,pfVar10);
      } while (local_4 != 0.0f);
    }
    g_dwSourceVert = (uint)pfVar15;
    g_dwDestIVert = uVar9;
    fVar11 = fVar12;
    pfVar15 = (float *)g_dwDestIVert;
    if (2 < PUN(int,(float)fVar11)) {
      g_dwDestIVert = g_dwSourceIVert;
      fVar12 = 0.0f;
      g_dwDestVert = g_dwSourceVert;
      pfVar16 = (float *)((uVar17 - 0xc) + PUN(int,(float)fVar11) * 0xc);
      g_dwSourceIVert = (uint)pfVar15;
      uVar9 = g_dwSourceVert;
      if (0 < PUN(int,(float)fVar11)) {
        iVar7 = 0;
        pfVar18 = (float *)(uVar17 + 8);
        g_dwSourceVert = uVar17;
        local_10[0] = PUN(float,(((int)pfVar15 - 4U) + PUN(int,(float)fVar11) * 4));
        local_4 = fVar11;
        do {
          pfVar10 = pfVar15;
          fVar11 = PUN(float,frustum[0xb]) * pfVar16[1];
          fVar2 = pfVar18[-1] * PUN(float,frustum[0xb]);
          if ((pfVar16[2] <= fVar11) || (*pfVar18 <= fVar2)) {
            if (((pfVar16[2] != fVar11) && (fVar2 != *pfVar18)) &&
               ((fVar11 < pfVar16[2] || (fVar2 < *pfVar18)))) {
              fVar11 = pfVar18[-1] - pfVar16[1];
              fVar3 = *pfVar18 - pfVar16[2];
              fVar1 = PUN(float,frustum[0xb]) * fVar11 - fVar3;
              fVar4 = pfVar16[2] * pfVar18[-1] - pfVar16[1] * *pfVar18;
              if (fVar1 != 0.0f) {
                fVar4 = fVar4 / fVar1;
              }
              fVar1 = PUN(float,frustum[0xb]);
              fVar5 = fVar11;
              if (fVar11 < 0.0f) {
                fVar5 = -fVar11;
              }
              fVar6 = fVar3;
              if (fVar3 < 0.0f) {
                fVar6 = -fVar3;
              }
              if (fVar5 <= fVar6) {
                fVar11 = (fVar1 * fVar4 - pfVar16[2]) / fVar3;
              }
              else {
                fVar11 = (fVar4 - pfVar16[1]) / fVar11;
              }
              iVar7 = iVar7 + 0xc;
              fVar12 = PUN(float,(PUN(int,(float)fVar12) + 1));
              *(float *)((uVar9 - 0xc) + iVar7) = (pfVar18[-2] - *pfVar16) * fVar11 + *pfVar16;
              *(float *)((g_dwDestVert - 8) + iVar7) = fVar4;
              *(float *)((g_dwDestVert - 4) + iVar7) = fVar1 * fVar4;
              *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar12) * 4) =
                   (*pfVar10 - *PUN(float *,(float)local_10[0])) * fVar11 + *PUN(float *,(float)local_10[0]);
              g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 4;
              uVar9 = g_dwDestVert;
            }
            if (*pfVar18 <= fVar2) {
              pfVar15 = (float *)(uVar9 + iVar7);
              fVar12 = PUN(float,(PUN(int,(float)fVar12) + 1));
              iVar7 = iVar7 + 0xc;
              *pfVar15 = pfVar18[-2];
              pfVar15[1] = pfVar18[-1];
              pfVar15[2] = *pfVar18;
              *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar12) * 4) = *pfVar10;
              uVar9 = g_dwDestVert;
            }
          }
          pfVar16 = pfVar18 + -2;
          pfVar18 = pfVar18 + 3;
          local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
          pfVar15 = pfVar10 + 1;
          uVar17 = g_dwSourceVert;
          local_10[0] = PUN(float,pfVar10);
        } while (local_4 != 0.0f);
      }
      g_dwSourceVert = uVar17;
      fVar11 = fVar12;
      pfVar15 = (float *)g_dwDestIVert;
      if (2 < PUN(int,(float)fVar11)) {
        g_dwDestIVert = g_dwSourceIVert;
        fVar12 = 0.0f;
        g_dwDestVert = g_dwSourceVert;
        pfVar16 = (float *)((uVar9 - 0xc) + PUN(int,(float)fVar11) * 0xc);
        g_dwSourceIVert = (uint)pfVar15;
        uVar17 = g_dwSourceVert;
        if (0 < PUN(int,(float)fVar11)) {
          iVar7 = 0;
          pfVar18 = (float *)(uVar9 + 8);
          g_dwSourceVert = uVar9;
          local_10[0] = PUN(float,(((int)pfVar15 - 4U) + PUN(int,(float)fVar11) * 4));
          local_4 = fVar11;
          do {
            pfVar10 = pfVar15;
            fVar11 = PUN(float,frustum[8]) * pfVar16[1];
            fVar2 = pfVar18[-1] * PUN(float,frustum[8]);
            if ((fVar11 <= pfVar16[2]) || (fVar2 <= *pfVar18)) {
              if (((pfVar16[2] != fVar11) && (fVar2 != *pfVar18)) &&
                 ((pfVar16[2] < fVar11 || (*pfVar18 < fVar2)))) {
                fVar11 = pfVar18[-1] - pfVar16[1];
                fVar3 = *pfVar18 - pfVar16[2];
                fVar1 = PUN(float,frustum[8]) * fVar11 - fVar3;
                fVar4 = pfVar16[2] * pfVar18[-1] - pfVar16[1] * *pfVar18;
                if (fVar1 != 0.0f) {
                  fVar4 = fVar4 / fVar1;
                }
                fVar1 = PUN(float,frustum[8]);
                fVar5 = fVar11;
                if (fVar11 < 0.0f) {
                  fVar5 = -fVar11;
                }
                fVar6 = fVar3;
                if (fVar3 < 0.0f) {
                  fVar6 = -fVar3;
                }
                if (fVar5 <= fVar6) {
                  fVar11 = (fVar1 * fVar4 - pfVar16[2]) / fVar3;
                }
                else {
                  fVar11 = (fVar4 - pfVar16[1]) / fVar11;
                }
                iVar7 = iVar7 + 0xc;
                fVar12 = PUN(float,(PUN(int,(float)fVar12) + 1));
                *(float *)((uVar17 - 0xc) + iVar7) = (pfVar18[-2] - *pfVar16) * fVar11 + *pfVar16;
                *(float *)((g_dwDestVert - 8) + iVar7) = fVar4;
                *(float *)((g_dwDestVert - 4) + iVar7) = fVar1 * fVar4;
                *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar12) * 4) =
                     (*pfVar10 - *PUN(float *,(float)local_10[0])) * fVar11 + *PUN(float *,(float)local_10[0]);
                g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 8;
                uVar17 = g_dwDestVert;
              }
              if (fVar2 <= *pfVar18) {
                pfVar15 = (float *)(uVar17 + iVar7);
                fVar12 = PUN(float,(PUN(int,(float)fVar12) + 1));
                iVar7 = iVar7 + 0xc;
                *pfVar15 = pfVar18[-2];
                pfVar15[1] = pfVar18[-1];
                pfVar15[2] = *pfVar18;
                *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar12) * 4) = *pfVar10;
                uVar17 = g_dwDestVert;
              }
            }
            pfVar16 = pfVar18 + -2;
            pfVar18 = pfVar18 + 3;
            local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
            pfVar15 = pfVar10 + 1;
            uVar9 = g_dwSourceVert;
            local_10[0] = PUN(float,pfVar10);
          } while (local_4 != 0.0f);
        }
        g_dwSourceVert = uVar9;
        fVar11 = fVar12;
        count = g_dwDestIVert;
        if (2 < PUN(int,(float)fVar11)) {
          g_dwDestIVert = g_dwSourceIVert;
          fVar12 = 0.0f;
          local_10[0] = PUN(float,((count - 4) + PUN(int,(float)fVar11) * 4));
          g_dwDestVert = g_dwSourceVert;
          g_dwSourceIVert = count;
          pfVar15 = (float *)((uVar17 - 0xc) + PUN(int,(float)fVar11) * 0xc);
          pfVar16 = (float *)g_dwSourceVert;
          if (0 < PUN(int,(float)fVar11)) {
            iVar7 = 0;
            pfVar18 = (float *)(uVar17 + 4);
            g_dwSourceVert = uVar17;
            local_4 = fVar11;
            do {
              if ((PUN(float,frustum[1]) <= pfVar15[1]) || (PUN(float,frustum[1]) <= *pfVar18)) {
                if (((pfVar15[1] != PUN(float,frustum[1])) && (*pfVar18 != PUN(float,frustum[1]))) &&
                   ((pfVar15[1] < PUN(float,frustum[1]) || (*pfVar18 < PUN(float,frustum[1]))))) {
                  fVar11 = (PUN(float,frustum[1]) - pfVar15[1]) / (*pfVar18 - pfVar15[1]);
                  *(int *)((int)pfVar16 + iVar7 + 4) = frustum[1];
                  iVar7 = iVar7 + 0xc;
                  fVar12 = PUN(float,(PUN(int,(float)fVar12) + 1));
                  *(float *)((g_dwDestVert - 4) + iVar7) =
                       (pfVar18[1] - pfVar15[2]) * fVar11 + pfVar15[2];
                  *(float *)((g_dwDestVert - 0xc) + iVar7) =
                       (pfVar18[-1] - *pfVar15) * fVar11 + *pfVar15;
                  *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar12) * 4) =
                       (*(float *)count - *PUN(float *,(float)local_10[0])) * fVar11 + *PUN(float *,(float)local_10[0]);
                  g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 1;
                  pfVar16 = (float *)g_dwDestVert;
                }
                if (PUN(float,frustum[1]) <= *pfVar18) {
                  pfVar16 = (float *)((int)pfVar16 + iVar7);
                  fVar12 = PUN(float,(PUN(int,(float)fVar12) + 1));
                  iVar7 = iVar7 + 0xc;
                  *pfVar16 = pfVar18[-1];
                  pfVar16[1] = *pfVar18;
                  pfVar16[2] = pfVar18[1];
                  *(undefined4 *)((g_dwDestIVert - 4) + PUN(int,(float)fVar12) * 4) = *(undefined4 *)count;
                  pfVar16 = (float *)g_dwDestVert;
                }
              }
              pfVar15 = pfVar18 + -1;
              local_10[0] = PUN(float,count);
              count = count + 4;
              pfVar18 = pfVar18 + 3;
              local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
              uVar17 = g_dwSourceVert;
            } while (local_4 != 0.0f);
          }
          g_dwSourceVert = uVar17;
          count = g_dwDestIVert;
          if (PUN(int,(float)fVar12) < 3) {
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x40;
            return PUN(uint,(float)fVar12);
          }
          fVar11 = fVar12;
          pfVar15 = pfVar16;
          if (*frustum != 0) {
            g_dwDestIVert = g_dwSourceIVert;
            fVar11 = 0.0f;
            local_10[0] = PUN(float,((count - 4) + PUN(int,(float)fVar12) * 4));
            g_dwDestVert = g_dwSourceVert;
            g_dwSourceIVert = count;
            pfVar18 = pfVar16 + PUN(int,(float)fVar12) * 3 + -3;
            pfVar15 = (float *)g_dwSourceVert;
            if (0 < PUN(int,(float)fVar12)) {
              iVar7 = 0;
              pfVar10 = pfVar16 + 1;
              g_dwSourceVert = (uint)pfVar16;
              local_4 = fVar12;
              do {
                if ((pfVar18[1] <= PUN(float,frustum[2])) || (*pfVar10 <= PUN(float,frustum[2]))) {
                  if (((pfVar18[1] != PUN(float,frustum[2])) && (*pfVar10 != PUN(float,frustum[2]))) &&
                     ((PUN(float,frustum[2]) < pfVar18[1] || (PUN(float,frustum[2]) < *pfVar10)))) {
                    fVar12 = (PUN(float,frustum[2]) - pfVar18[1]) / (*pfVar10 - pfVar18[1]);
                    *(int *)((int)pfVar15 + iVar7 + 4) = frustum[2];
                    iVar7 = iVar7 + 0xc;
                    fVar11 = PUN(float,(PUN(int,(float)fVar11) + 1));
                    *(float *)((g_dwDestVert - 4) + iVar7) =
                         (pfVar10[1] - pfVar18[2]) * fVar12 + pfVar18[2];
                    *(float *)((g_dwDestVert - 0xc) + iVar7) =
                         (pfVar10[-1] - *pfVar18) * fVar12 + *pfVar18;
                    *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar11) * 4) =
                         (*(float *)count - *PUN(float *,(float)local_10[0])) * fVar12 + *PUN(float *,(float)local_10[0]);
                    g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 2;
                    pfVar15 = (float *)g_dwDestVert;
                  }
                  if (*pfVar10 <= PUN(float,frustum[2])) {
                    pfVar15 = (float *)((int)pfVar15 + iVar7);
                    fVar11 = PUN(float,(PUN(int,(float)fVar11) + 1));
                    iVar7 = iVar7 + 0xc;
                    *pfVar15 = pfVar10[-1];
                    pfVar15[1] = *pfVar10;
                    pfVar15[2] = pfVar10[1];
                    *(undefined4 *)((g_dwDestIVert - 4) + PUN(int,(float)fVar11) * 4) = *(undefined4 *)count;
                    pfVar15 = (float *)g_dwDestVert;
                  }
                }
                pfVar18 = pfVar10 + -1;
                local_10[0] = PUN(float,count);
                count = count + 4;
                pfVar10 = pfVar10 + 3;
                local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
                pfVar16 = (float *)g_dwSourceVert;
              } while (local_4 != 0.0f);
            }
            g_dwSourceVert = (uint)pfVar16;
            if (PUN(int,(float)fVar11) < 3) {
              return PUN(uint,(float)fVar11);
            }
          }
          if (pfVar15 != verts) {
            for (uVar9 = PUN(int,(float)fVar11) * 3 & 0x3fffffff; uVar9 != 0; uVar9 = uVar9 - 1) {
              *verts = *pfVar15;
              pfVar15 = pfVar15 + 1;
              verts = verts + 1;
            }
            for (iVar7 = 0; fVar12 = fVar11, pfVar16 = (float *)g_dwDestIVert, iVar7 != 0;
                iVar7 = iVar7 + -1) {
              *(undefined1 *)verts = *(undefined1 *)pfVar15;
              pfVar15 = (float *)((int)pfVar15 + 1);
              verts = (float *)((int)verts + 1);
            }
            for (; fVar12 != 0.0f; fVar12 = PUN(float,(PUN(int,(float)fVar12) - 1))) {
              *ivert = *pfVar16;
              pfVar16 = pfVar16 + 1;
              ivert = ivert + 1;
            }
          }
        }
      }
    }
  }
  return PUN(uint,(float)fVar11);
}
#undef local_10
#undef local_4

#endif


/* ---- 0x0044a6d0  rdClip_Face3GSOrtho ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdClip_Face3GSOrtho (the remaster's GrimFandango (Linux): the matching branch of
   the rdPrimit3_ClipFace switch (geometry/lighting mode, perspective or ortho camera)); was
   rdClip_Face3_PosUv. */

uint __cdecl rdClip_Face3GSOrtho(int *frustum,float *verts,float *ivert,uint count)

{
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
  uint local_c;
  float local_8;
  uint local_4;
  
  local_4 = 0;
  puVar8 = &g_dwWorkVerts;
  g_dwRdClip_faceStatus = 0;
  g_dwSourceVert = (uint)verts;
  g_dwSourceIVert = (uint)ivert;
  g_dwDestVert = (uint)&g_dwWorkVerts;
  g_dwDestIVert = (uint)&g_dwWorkIVerts;
  if (0 < (int)count) {
    iVar13 = 0;
    pfVar9 = verts + count * 3 + -3;
    pfVar12 = verts;
    pfVar4 = ivert;
    local_8 = PUN(float,(ivert + (count - 1)));
    do {
      pfVar6 = pfVar4;
      fVar2 = PUN(float,frustum[3]);
      fVar1 = PUN(float,frustum[3]);
      if ((fVar2 <= *pfVar9) || (fVar1 <= *pfVar12)) {
        iVar14 = iVar13;
        if (((*pfVar9 != fVar2) && (fVar1 != *pfVar12)) && ((*pfVar9 < fVar2 || (*pfVar12 < fVar1)))
           ) {
          fVar3 = (fVar2 - *pfVar9) / (*pfVar12 - *pfVar9);
          iVar14 = iVar13 + 0xc;
          local_4 = local_4 + 1;
          *(float *)((int)puVar8 + iVar13) = fVar2;
          *(float *)((g_dwDestVert - 8) + iVar14) = (pfVar12[1] - pfVar9[1]) * fVar3 + pfVar9[1];
          *(float *)((g_dwDestVert - 4) + iVar14) = (pfVar12[2] - pfVar9[2]) * fVar3 + pfVar9[2];
          *(float *)((g_dwDestIVert - 4) + local_4 * 4) =
               (*pfVar6 - *PUN(float *,(float)local_8)) * fVar3 + *PUN(float *,(float)local_8);
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x10;
          puVar8 = (uint *)g_dwDestVert;
        }
        iVar13 = iVar14;
        if (fVar1 <= *pfVar12) {
          pfVar9 = (float *)((int)puVar8 + iVar14);
          local_4 = local_4 + 1;
          iVar13 = iVar14 + 0xc;
          *pfVar9 = *pfVar12;
          pfVar9[1] = pfVar12[1];
          pfVar9[2] = pfVar12[2];
          *(float *)((g_dwDestIVert - 4) + local_4 * 4) = *pfVar6;
          puVar8 = (uint *)g_dwDestVert;
        }
      }
      count = count - 1;
      pfVar9 = pfVar12;
      pfVar12 = pfVar12 + 3;
      pfVar4 = pfVar6 + 1;
      local_8 = PUN(float,pfVar6);
    } while (count != 0);
  }
  uVar5 = g_dwSourceIVert;
  if (2 < (int)local_4) {
    iVar13 = g_dwDestIVert - 4;
    uVar7 = 0;
    g_dwSourceIVert = g_dwDestIVert;
    uVar11 = g_dwSourceVert;
    g_dwDestVert = g_dwSourceVert;
    pfVar9 = (float *)puVar8;
    if (0 < (int)local_4) {
      iVar14 = 0;
      pfVar12 = (float *)(puVar8 + local_4 * 3 + -3);
      pfVar4 = (float *)g_dwDestIVert;
      g_dwDestIVert = uVar5;
      g_dwSourceVert = (uint)puVar8;
      count = local_4;
      local_8 = PUN(float,(iVar13 + local_4 * 4));
      do {
        pfVar6 = pfVar4;
        fVar2 = PUN(float,frustum[5]);
        fVar1 = PUN(float,frustum[5]);
        if ((*pfVar12 <= fVar2) || (PUN(float,*puVar8) <= fVar1)) {
          if (((*pfVar12 != fVar2) && (fVar1 != PUN(float,*puVar8))) &&
             ((fVar2 < *pfVar12 || (fVar1 < PUN(float,*puVar8))))) {
            fVar3 = (fVar2 - *pfVar12) / (PUN(float,*puVar8) - *pfVar12);
            iVar14 = iVar14 + 0xc;
            uVar7 = uVar7 + 1;
            *(float *)((uVar11 - 0xc) + iVar14) = fVar2;
            *(float *)((g_dwDestVert - 8) + iVar14) =
                 (PUN(float,puVar8[1]) - pfVar12[1]) * fVar3 + pfVar12[1];
            *(float *)((g_dwDestVert - 4) + iVar14) =
                 (PUN(float,puVar8[2]) - pfVar12[2]) * fVar3 + pfVar12[2];
            *(float *)((g_dwDestIVert - 4) + uVar7 * 4) =
                 (*pfVar6 - *PUN(float *,(float)local_8)) * fVar3 + *PUN(float *,(float)local_8);
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x20;
            uVar11 = g_dwDestVert;
          }
          if (PUN(float,*puVar8) <= fVar1) {
            pfVar9 = (float *)(uVar11 + iVar14);
            uVar7 = uVar7 + 1;
            iVar14 = iVar14 + 0xc;
            *pfVar9 = PUN(float,*puVar8);
            pfVar9[1] = PUN(float,puVar8[1]);
            pfVar9[2] = PUN(float,puVar8[2]);
            *(float *)((g_dwDestIVert - 4) + uVar7 * 4) = *pfVar6;
            uVar11 = g_dwDestVert;
          }
        }
        count = count - 1;
        pfVar12 = (float *)puVar8;
        puVar8 = puVar8 + 3;
        pfVar4 = pfVar6 + 1;
        uVar5 = g_dwDestIVert;
        pfVar9 = (float *)g_dwSourceVert;
        local_8 = PUN(float,pfVar6);
      } while (count != 0);
    }
    g_dwSourceVert = (uint)pfVar9;
    g_dwDestIVert = uVar5;
    local_4 = uVar7;
    uVar5 = g_dwSourceIVert;
    if (2 < (int)local_4) {
      iVar13 = g_dwDestIVert - 4;
      uVar7 = 0;
      g_dwSourceIVert = g_dwDestIVert;
      pfVar9 = (float *)((uVar11 - 0xc) + local_4 * 0xc);
      uVar10 = g_dwSourceVert;
      g_dwDestVert = g_dwSourceVert;
      if (0 < (int)local_4) {
        pfVar12 = (float *)(uVar11 + 8);
        iVar14 = 0;
        pfVar4 = (float *)g_dwDestIVert;
        g_dwDestIVert = uVar5;
        g_dwSourceVert = uVar11;
        local_8 = PUN(float,(iVar13 + local_4 * 4));
        do {
          pfVar6 = pfVar4;
          fVar2 = PUN(float,frustum[4]);
          fVar1 = PUN(float,frustum[4]);
          if ((pfVar9[2] <= fVar2) || (*pfVar12 <= fVar1)) {
            if (((pfVar9[2] != fVar2) && (fVar1 != *pfVar12)) &&
               ((fVar2 < pfVar9[2] || (fVar1 < *pfVar12)))) {
              fVar3 = (fVar2 - pfVar9[2]) / (*pfVar12 - pfVar9[2]);
              iVar14 = iVar14 + 0xc;
              uVar7 = uVar7 + 1;
              *(float *)((uVar10 - 0xc) + iVar14) = (pfVar12[-2] - *pfVar9) * fVar3 + *pfVar9;
              *(float *)((g_dwDestVert - 8) + iVar14) =
                   (pfVar12[-1] - pfVar9[1]) * fVar3 + pfVar9[1];
              *(float *)((g_dwDestVert - 4) + iVar14) = fVar2;
              *(float *)((g_dwDestIVert - 4) + uVar7 * 4) =
                   (*pfVar6 - *PUN(float *,(float)local_8)) * fVar3 + *PUN(float *,(float)local_8);
              g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 4;
              uVar10 = g_dwDestVert;
            }
            if (*pfVar12 <= fVar1) {
              pfVar9 = (float *)(uVar10 + iVar14);
              uVar7 = uVar7 + 1;
              iVar14 = iVar14 + 0xc;
              *pfVar9 = pfVar12[-2];
              pfVar9[1] = pfVar12[-1];
              pfVar9[2] = *pfVar12;
              *(float *)((g_dwDestIVert - 4) + uVar7 * 4) = *pfVar6;
              uVar10 = g_dwDestVert;
            }
          }
          pfVar9 = pfVar12 + -2;
          pfVar12 = pfVar12 + 3;
          local_4 = local_4 - 1;
          pfVar4 = pfVar6 + 1;
          uVar5 = g_dwDestIVert;
          uVar11 = g_dwSourceVert;
          local_8 = PUN(float,pfVar6);
        } while (local_4 != 0);
      }
      g_dwSourceVert = uVar11;
      g_dwDestIVert = uVar5;
      local_4 = uVar7;
      uVar5 = g_dwSourceIVert;
      if (2 < (int)local_4) {
        uVar7 = 0;
        local_8 = (float)((g_dwDestIVert - 4) + local_4 * 4);
        g_dwSourceIVert = g_dwDestIVert;
        pfVar9 = (float *)((uVar10 - 0xc) + local_4 * 0xc);
        local_c = g_dwDestIVert;
        uVar11 = g_dwSourceVert;
        g_dwDestVert = g_dwSourceVert;
        g_dwDestIVert = uVar5;
        if (0 < (int)local_4) {
          iVar13 = 0;
          pfVar12 = (float *)(uVar10 + 8);
          g_dwSourceVert = uVar10;
          do {
            fVar2 = PUN(float,frustum[6]);
            fVar1 = PUN(float,frustum[6]);
            if ((fVar2 <= pfVar9[2]) || (fVar1 <= *pfVar12)) {
              if (((pfVar9[2] != fVar2) && (fVar1 != *pfVar12)) &&
                 ((pfVar9[2] < fVar2 || (*pfVar12 < fVar1)))) {
                fVar3 = (fVar2 - pfVar9[2]) / (*pfVar12 - pfVar9[2]);
                iVar13 = iVar13 + 0xc;
                uVar7 = uVar7 + 1;
                *(float *)((uVar11 - 0xc) + iVar13) = (pfVar12[-2] - *pfVar9) * fVar3 + *pfVar9;
                *(float *)((g_dwDestVert - 8) + iVar13) =
                     (pfVar12[-1] - pfVar9[1]) * fVar3 + pfVar9[1];
                *(float *)((g_dwDestVert - 4) + iVar13) = fVar2;
                *(float *)((g_dwDestIVert - 4) + uVar7 * 4) =
                     (*(float *)local_c - *PUN(float *,(float)local_8)) * fVar3 + *PUN(float *,(float)local_8);
                g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 8;
                uVar11 = g_dwDestVert;
              }
              if (fVar1 <= *pfVar12) {
                pfVar9 = (float *)(uVar11 + iVar13);
                uVar7 = uVar7 + 1;
                iVar13 = iVar13 + 0xc;
                *pfVar9 = pfVar12[-2];
                pfVar9[1] = pfVar12[-1];
                pfVar9[2] = *pfVar12;
                *(undefined4 *)((g_dwDestIVert - 4) + uVar7 * 4) = *(undefined4 *)local_c;
                uVar11 = g_dwDestVert;
              }
            }
            pfVar9 = pfVar12 + -2;
            local_8 = PUN(float,local_c);
            local_c = local_c + 4;
            pfVar12 = pfVar12 + 3;
            local_4 = local_4 - 1;
            uVar10 = g_dwSourceVert;
          } while (local_4 != 0);
        }
        g_dwSourceVert = uVar10;
        local_4 = uVar7;
        uVar5 = g_dwSourceIVert;
        if (2 < (int)local_4) {
          local_8 = (float)((g_dwDestIVert - 4) + local_4 * 4);
          uVar7 = 0;
          g_dwSourceIVert = g_dwDestIVert;
          pfVar9 = (float *)((uVar11 - 0xc) + local_4 * 0xc);
          local_c = g_dwDestIVert;
          pfVar12 = (float *)g_dwSourceVert;
          g_dwDestVert = g_dwSourceVert;
          g_dwDestIVert = uVar5;
          if (0 < (int)local_4) {
            pfVar4 = (float *)(uVar11 + 4);
            iVar13 = 0;
            g_dwSourceVert = uVar11;
            count = local_4;
            do {
              if ((PUN(float,frustum[1]) <= pfVar9[1]) || (PUN(float,frustum[1]) <= *pfVar4)) {
                if (((pfVar9[1] != PUN(float,frustum[1])) && (*pfVar4 != PUN(float,frustum[1]))) &&
                   ((pfVar9[1] < PUN(float,frustum[1]) || (*pfVar4 < PUN(float,frustum[1]))))) {
                  fVar1 = (PUN(float,frustum[1]) - pfVar9[1]) / (*pfVar4 - pfVar9[1]);
                  *(int *)((int)pfVar12 + iVar13 + 4) = frustum[1];
                  iVar13 = iVar13 + 0xc;
                  uVar7 = uVar7 + 1;
                  *(float *)((g_dwDestVert - 4) + iVar13) =
                       (pfVar4[1] - pfVar9[2]) * fVar1 + pfVar9[2];
                  *(float *)((g_dwDestVert - 0xc) + iVar13) =
                       (pfVar4[-1] - *pfVar9) * fVar1 + *pfVar9;
                  *(float *)((g_dwDestIVert - 4) + uVar7 * 4) =
                       (*(float *)local_c - *PUN(float *,(float)local_8)) * fVar1 + *PUN(float *,(float)local_8);
                  g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 1;
                  pfVar12 = (float *)g_dwDestVert;
                }
                if (PUN(float,frustum[1]) <= *pfVar4) {
                  pfVar12 = (float *)((int)pfVar12 + iVar13);
                  uVar7 = uVar7 + 1;
                  iVar13 = iVar13 + 0xc;
                  *pfVar12 = pfVar4[-1];
                  pfVar12[1] = *pfVar4;
                  pfVar12[2] = pfVar4[1];
                  *(undefined4 *)((g_dwDestIVert - 4) + uVar7 * 4) = *(undefined4 *)local_c;
                  pfVar12 = (float *)g_dwDestVert;
                }
              }
              pfVar9 = pfVar4 + -1;
              local_8 = PUN(float,local_c);
              local_c = local_c + 4;
              pfVar4 = pfVar4 + 3;
              count = count - 1;
              uVar11 = g_dwSourceVert;
            } while (count != 0);
          }
          g_dwSourceVert = uVar11;
          uVar5 = g_dwSourceIVert;
          if ((int)uVar7 < 3) {
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x40;
            return uVar7;
          }
          local_4 = uVar7;
          pfVar9 = pfVar12;
          if (*frustum != 0) {
            local_8 = (float)((g_dwDestIVert - 4) + uVar7 * 4);
            local_4 = 0;
            g_dwSourceIVert = g_dwDestIVert;
            pfVar4 = pfVar12 + uVar7 * 3 + -3;
            local_c = g_dwDestIVert;
            pfVar9 = (float *)g_dwSourceVert;
            g_dwDestVert = g_dwSourceVert;
            g_dwDestIVert = uVar5;
            if (0 < (int)uVar7) {
              pfVar6 = pfVar12 + 1;
              iVar13 = 0;
              g_dwSourceVert = (uint)pfVar12;
              count = uVar7;
              do {
                if ((pfVar4[1] <= PUN(float,frustum[2])) || (*pfVar6 <= PUN(float,frustum[2]))) {
                  if (((pfVar4[1] != PUN(float,frustum[2])) && (*pfVar6 != PUN(float,frustum[2]))) &&
                     ((PUN(float,frustum[2]) < pfVar4[1] || (PUN(float,frustum[2]) < *pfVar6)))) {
                    fVar1 = (PUN(float,frustum[2]) - pfVar4[1]) / (*pfVar6 - pfVar4[1]);
                    *(int *)((int)pfVar9 + iVar13 + 4) = frustum[2];
                    iVar13 = iVar13 + 0xc;
                    local_4 = local_4 + 1;
                    *(float *)((g_dwDestVert - 4) + iVar13) =
                         (pfVar6[1] - pfVar4[2]) * fVar1 + pfVar4[2];
                    *(float *)((g_dwDestVert - 0xc) + iVar13) =
                         (pfVar6[-1] - *pfVar4) * fVar1 + *pfVar4;
                    *(float *)((g_dwDestIVert - 4) + local_4 * 4) =
                         (*(float *)local_c - *PUN(float *,(float)local_8)) * fVar1 + *PUN(float *,(float)local_8);
                    g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 2;
                    pfVar9 = (float *)g_dwDestVert;
                  }
                  if (*pfVar6 <= PUN(float,frustum[2])) {
                    pfVar9 = (float *)((int)pfVar9 + iVar13);
                    local_4 = local_4 + 1;
                    iVar13 = iVar13 + 0xc;
                    *pfVar9 = pfVar6[-1];
                    pfVar9[1] = *pfVar6;
                    pfVar9[2] = pfVar6[1];
                    *(undefined4 *)((g_dwDestIVert - 4) + local_4 * 4) = *(undefined4 *)local_c;
                    pfVar9 = (float *)g_dwDestVert;
                  }
                }
                pfVar4 = pfVar6 + -1;
                local_8 = PUN(float,local_c);
                local_c = local_c + 4;
                pfVar6 = pfVar6 + 3;
                count = count - 1;
                pfVar12 = (float *)g_dwSourceVert;
              } while (count != 0);
            }
            g_dwSourceVert = (uint)pfVar12;
            if ((int)local_4 < 3) {
              return local_4;
            }
          }
          if (pfVar9 != verts) {
            for (uVar5 = local_4 * 3 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
              *verts = *pfVar9;
              pfVar9 = pfVar9 + 1;
              verts = verts + 1;
            }
            for (iVar13 = 0; uVar5 = local_4, pfVar12 = (float *)g_dwDestIVert, iVar13 != 0;
                iVar13 = iVar13 + -1) {
              *(undefined1 *)verts = *(undefined1 *)pfVar9;
              pfVar9 = (float *)((int)pfVar9 + 1);
              verts = (float *)((int)verts + 1);
            }
            for (; uVar5 != 0; uVar5 = uVar5 - 1) {
              *ivert = *pfVar12;
              pfVar12 = pfVar12 + 1;
              ivert = ivert + 1;
            }
          }
        }
      }
    }
  }
  return local_4;
}
#endif


/* ---- 0x0044b0a0  rdClip_Face3T ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdClip_Face3T (the remaster's GrimFandango (Linux): the matching branch of the
   rdPrimit3_ClipFace switch (geometry/lighting mode, perspective or ortho camera)); was
   rdClip_Face3_PosUvLit_2. */

uint __cdecl rdClip_Face3T(int *frustum,float *verts,float *tverts,uint count)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  uint uVar9;
  float fVar10;
  float fVar11;
  float *pfVar12;
  float *pfVar13;
  uint *puVar14;
  float *pfVar15;
  float *pfVar16;
  uint uVar17;
  uint local_10;
  uint local_c;
  uint local_8;
  float local_4;
  
  g_dwRdClip_faceStatus = 0;
  local_10 = 0;
  puVar14 = &g_dwWorkVerts;
  g_dwSourceVert = (uint)verts;
  g_dwDestVert = (uint)&g_dwWorkVerts;
  g_dwSourceTVert = (uint)tverts;
  g_dwDestTVert = (uint)&g_dwWorkTVerts;
  if (0 < (int)count) {
    iVar6 = 0;
    local_4 = PUN(float,count);
    pfVar15 = tverts + count * 2 + -2;
    pfVar16 = tverts;
    pfVar8 = verts + count * 3 + -3;
    pfVar12 = verts;
    do {
      fVar10 = pfVar8[1] * PUN(float,frustum[0xc]);
      fVar11 = PUN(float,frustum[0xc]) * pfVar12[1];
      if ((fVar10 <= *pfVar8) || (fVar11 <= *pfVar12)) {
        if (((*pfVar8 != fVar10) && (fVar11 != *pfVar12)) &&
           ((*pfVar8 < fVar10 || (*pfVar12 < fVar11)))) {
          fVar10 = pfVar12[1] - pfVar8[1];
          fVar2 = *pfVar12 - *pfVar8;
          fVar1 = PUN(float,frustum[0xc]) * fVar10 - fVar2;
          fVar3 = pfVar12[1] * *pfVar8 - pfVar8[1] * *pfVar12;
          if (fVar1 != 0.0f) {
            fVar3 = fVar3 / fVar1;
          }
          fVar1 = fVar10;
          if (fVar10 < 0.0f) {
            fVar1 = -fVar10;
          }
          fVar4 = fVar2;
          if (fVar2 < 0.0f) {
            fVar4 = -fVar2;
          }
          if (fVar1 <= fVar4) {
            fVar10 = (PUN(float,frustum[0xc]) * fVar3 - *pfVar8) / fVar2;
          }
          else {
            fVar10 = (fVar3 - pfVar8[1]) / fVar10;
          }
          *(float *)((int)puVar14 + iVar6) = PUN(float,frustum[0xc]) * fVar3;
          *(float *)(g_dwDestVert + 4 + iVar6) = fVar3;
          iVar7 = local_10 * 8;
          local_10 = local_10 + 1;
          iVar6 = iVar6 + 0xc;
          *(float *)((g_dwDestVert - 4) + iVar6) = (pfVar12[2] - pfVar8[2]) * fVar10 + pfVar8[2];
          *(float *)(g_dwDestTVert + iVar7) = (*pfVar16 - *pfVar15) * fVar10 + *pfVar15;
          *(float *)(g_dwDestTVert + 4 + iVar7) = (pfVar16[1] - pfVar15[1]) * fVar10 + pfVar15[1];
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x10;
          puVar14 = (uint *)g_dwDestVert;
        }
        if (fVar11 <= *pfVar12) {
          pfVar15 = (float *)((int)puVar14 + iVar6);
          *pfVar15 = *pfVar12;
          pfVar15[1] = pfVar12[1];
          pfVar15[2] = pfVar12[2];
          *(float *)(g_dwDestTVert + local_10 * 8) = *pfVar16;
          *(float *)(g_dwDestTVert + 4 + local_10 * 8) = pfVar16[1];
          local_10 = local_10 + 1;
          iVar6 = iVar6 + 0xc;
          puVar14 = (uint *)g_dwDestVert;
        }
      }
      local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
      pfVar15 = pfVar16;
      pfVar16 = pfVar16 + 2;
      pfVar8 = pfVar12;
      pfVar12 = pfVar12 + 3;
    } while (local_4 != 0.0f);
  }
  local_4 = PUN(float,local_10);
  uVar9 = g_dwSourceTVert;
  if ((int)local_10 < 3) {
    return local_10;
  }
  g_dwSourceTVert = g_dwDestTVert;
  iVar6 = local_10 * 8;
  local_10 = 0;
  uVar17 = g_dwSourceVert;
  g_dwDestVert = g_dwSourceVert;
  pfVar15 = (float *)puVar14;
  if (0 < PUN(int,(float)local_4)) {
    iVar7 = 0;
    pfVar16 = (float *)((g_dwDestTVert - 8) + iVar6);
    pfVar8 = (float *)g_dwDestTVert;
    pfVar12 = (float *)(puVar14 + PUN(int,(float)local_4) * 3 + -3);
    g_dwDestTVert = uVar9;
    g_dwSourceVert = (uint)puVar14;
    do {
      pfVar15 = (float *)puVar14;
      fVar10 = PUN(float,frustum[10]) * pfVar12[1];
      fVar11 = PUN(float,frustum[10]) * pfVar15[1];
      if ((*pfVar12 <= fVar10) || (*pfVar15 <= fVar11)) {
        if (((*pfVar12 != fVar10) && (fVar11 != *pfVar15)) &&
           ((fVar10 < *pfVar12 || (fVar11 < *pfVar15)))) {
          fVar10 = pfVar15[1] - pfVar12[1];
          fVar2 = *pfVar15 - *pfVar12;
          fVar1 = PUN(float,frustum[10]) * fVar10 - fVar2;
          fVar3 = pfVar15[1] * *pfVar12 - pfVar12[1] * *pfVar15;
          if (fVar1 != 0.0f) {
            fVar3 = fVar3 / fVar1;
          }
          fVar1 = fVar10;
          if (fVar10 < 0.0f) {
            fVar1 = -fVar10;
          }
          fVar4 = fVar2;
          if (fVar2 < 0.0f) {
            fVar4 = -fVar2;
          }
          if (fVar1 <= fVar4) {
            fVar10 = (PUN(float,frustum[10]) * fVar3 - *pfVar12) / fVar2;
          }
          else {
            fVar10 = (fVar3 - pfVar12[1]) / fVar10;
          }
          *(float *)(uVar17 + iVar7) = PUN(float,frustum[10]) * fVar3;
          *(float *)(g_dwDestVert + 4 + iVar7) = fVar3;
          iVar6 = local_10 * 8;
          local_10 = local_10 + 1;
          iVar7 = iVar7 + 0xc;
          *(float *)((g_dwDestVert - 4) + iVar7) = (pfVar15[2] - pfVar12[2]) * fVar10 + pfVar12[2];
          *(float *)(g_dwDestTVert + iVar6) = (*pfVar8 - *pfVar16) * fVar10 + *pfVar16;
          *(float *)(g_dwDestTVert + 4 + iVar6) = (pfVar8[1] - pfVar16[1]) * fVar10 + pfVar16[1];
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x20;
          uVar17 = g_dwDestVert;
        }
        if (*pfVar15 <= fVar11) {
          pfVar16 = (float *)(uVar17 + iVar7);
          *pfVar16 = *pfVar15;
          pfVar16[1] = pfVar15[1];
          pfVar16[2] = pfVar15[2];
          *(float *)(g_dwDestTVert + local_10 * 8) = *pfVar8;
          *(float *)(g_dwDestTVert + 4 + local_10 * 8) = pfVar8[1];
          local_10 = local_10 + 1;
          iVar7 = iVar7 + 0xc;
          uVar17 = g_dwDestVert;
        }
      }
      local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
      pfVar16 = pfVar8;
      puVar14 = (uint *)(pfVar15 + 3);
      pfVar8 = pfVar8 + 2;
      pfVar12 = pfVar15;
      uVar9 = g_dwDestTVert;
      pfVar15 = (float *)g_dwSourceVert;
    } while (local_4 != 0.0f);
  }
  g_dwSourceVert = (uint)pfVar15;
  g_dwDestTVert = uVar9;
  local_4 = PUN(float,local_10);
  pfVar15 = (float *)g_dwDestTVert;
  if ((int)local_10 < 3) {
    return local_10;
  }
  g_dwDestTVert = g_dwSourceTVert;
  iVar6 = 0;
  g_dwDestVert = g_dwSourceVert;
  pfVar16 = (float *)((uVar17 - 0xc) + local_10 * 0xc);
  g_dwSourceTVert = (uint)pfVar15;
  local_10 = 0;
  uVar9 = g_dwSourceVert;
  if (0 < PUN(int,(float)local_4)) {
    pfVar12 = (float *)(uVar17 + 8);
    pfVar8 = (float *)(((int)pfVar15 - 8U) + PUN(int,(float)local_4) * 8);
    g_dwSourceVert = uVar17;
    do {
      fVar10 = PUN(float,frustum[0xb]) * pfVar16[1];
      fVar11 = pfVar12[-1] * PUN(float,frustum[0xb]);
      if ((pfVar16[2] <= fVar10) || (*pfVar12 <= fVar11)) {
        if (((pfVar16[2] != fVar10) && (fVar11 != *pfVar12)) &&
           ((fVar10 < pfVar16[2] || (fVar11 < *pfVar12)))) {
          fVar10 = pfVar12[-1] - pfVar16[1];
          fVar2 = *pfVar12 - pfVar16[2];
          fVar1 = PUN(float,frustum[0xb]) * fVar10 - fVar2;
          fVar3 = pfVar16[2] * pfVar12[-1] - pfVar16[1] * *pfVar12;
          if (fVar1 != 0.0f) {
            fVar3 = fVar3 / fVar1;
          }
          fVar1 = PUN(float,frustum[0xb]);
          fVar4 = fVar10;
          if (fVar10 < 0.0f) {
            fVar4 = -fVar10;
          }
          fVar5 = fVar2;
          if (fVar2 < 0.0f) {
            fVar5 = -fVar2;
          }
          if (fVar4 <= fVar5) {
            fVar10 = (fVar1 * fVar3 - pfVar16[2]) / fVar2;
          }
          else {
            fVar10 = (fVar3 - pfVar16[1]) / fVar10;
          }
          iVar6 = iVar6 + 0xc;
          iVar7 = local_10 * 8;
          local_10 = local_10 + 1;
          *(float *)((uVar9 - 0xc) + iVar6) = (pfVar12[-2] - *pfVar16) * fVar10 + *pfVar16;
          *(float *)((g_dwDestVert - 8) + iVar6) = fVar3;
          *(float *)((g_dwDestVert - 4) + iVar6) = fVar1 * fVar3;
          *(float *)(g_dwDestTVert + iVar7) = (*pfVar15 - *pfVar8) * fVar10 + *pfVar8;
          *(float *)(g_dwDestTVert + 4 + iVar7) = (pfVar15[1] - pfVar8[1]) * fVar10 + pfVar8[1];
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 4;
          uVar9 = g_dwDestVert;
        }
        if (*pfVar12 <= fVar11) {
          pfVar16 = (float *)(uVar9 + iVar6);
          *pfVar16 = pfVar12[-2];
          pfVar16[1] = pfVar12[-1];
          pfVar16[2] = *pfVar12;
          *(float *)(g_dwDestTVert + local_10 * 8) = *pfVar15;
          *(float *)(g_dwDestTVert + 4 + local_10 * 8) = pfVar15[1];
          local_10 = local_10 + 1;
          iVar6 = iVar6 + 0xc;
          uVar9 = g_dwDestVert;
        }
      }
      pfVar16 = pfVar12 + -2;
      pfVar12 = pfVar12 + 3;
      local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
      pfVar8 = pfVar15;
      pfVar15 = pfVar15 + 2;
      uVar17 = g_dwSourceVert;
    } while (local_4 != 0.0f);
  }
  g_dwSourceVert = uVar17;
  local_4 = PUN(float,local_10);
  pfVar15 = (float *)g_dwDestTVert;
  if ((int)local_10 < 3) {
    return local_10;
  }
  g_dwDestTVert = g_dwSourceTVert;
  iVar6 = 0;
  g_dwDestVert = g_dwSourceVert;
  pfVar16 = (float *)((uVar9 - 0xc) + local_10 * 0xc);
  g_dwSourceTVert = (uint)pfVar15;
  local_10 = 0;
  uVar17 = g_dwSourceVert;
  if (0 < PUN(int,(float)local_4)) {
    pfVar12 = (float *)(uVar9 + 8);
    pfVar8 = (float *)(((int)pfVar15 - 8U) + PUN(int,(float)local_4) * 8);
    g_dwSourceVert = uVar9;
    do {
      fVar10 = PUN(float,frustum[8]) * pfVar16[1];
      fVar11 = pfVar12[-1] * PUN(float,frustum[8]);
      if ((fVar10 <= pfVar16[2]) || (fVar11 <= *pfVar12)) {
        if (((pfVar16[2] != fVar10) && (fVar11 != *pfVar12)) &&
           ((pfVar16[2] < fVar10 || (*pfVar12 < fVar11)))) {
          fVar10 = pfVar12[-1] - pfVar16[1];
          fVar2 = *pfVar12 - pfVar16[2];
          fVar1 = PUN(float,frustum[8]) * fVar10 - fVar2;
          fVar3 = pfVar16[2] * pfVar12[-1] - pfVar16[1] * *pfVar12;
          if (fVar1 != 0.0f) {
            fVar3 = fVar3 / fVar1;
          }
          fVar1 = PUN(float,frustum[8]);
          fVar4 = fVar10;
          if (fVar10 < 0.0f) {
            fVar4 = -fVar10;
          }
          fVar5 = fVar2;
          if (fVar2 < 0.0f) {
            fVar5 = -fVar2;
          }
          if (fVar4 <= fVar5) {
            fVar10 = (fVar1 * fVar3 - pfVar16[2]) / fVar2;
          }
          else {
            fVar10 = (fVar3 - pfVar16[1]) / fVar10;
          }
          iVar6 = iVar6 + 0xc;
          iVar7 = local_10 * 8;
          local_10 = local_10 + 1;
          *(float *)((uVar17 - 0xc) + iVar6) = (pfVar12[-2] - *pfVar16) * fVar10 + *pfVar16;
          *(float *)((g_dwDestVert - 8) + iVar6) = fVar3;
          *(float *)((g_dwDestVert - 4) + iVar6) = fVar1 * fVar3;
          *(float *)(g_dwDestTVert + iVar7) = (*pfVar15 - *pfVar8) * fVar10 + *pfVar8;
          *(float *)(g_dwDestTVert + 4 + iVar7) = (pfVar15[1] - pfVar8[1]) * fVar10 + pfVar8[1];
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 8;
          uVar17 = g_dwDestVert;
        }
        if (fVar11 <= *pfVar12) {
          pfVar16 = (float *)(uVar17 + iVar6);
          *pfVar16 = pfVar12[-2];
          pfVar16[1] = pfVar12[-1];
          pfVar16[2] = *pfVar12;
          *(float *)(g_dwDestTVert + local_10 * 8) = *pfVar15;
          *(float *)(g_dwDestTVert + 4 + local_10 * 8) = pfVar15[1];
          local_10 = local_10 + 1;
          iVar6 = iVar6 + 0xc;
          uVar17 = g_dwDestVert;
        }
      }
      pfVar16 = pfVar12 + -2;
      pfVar12 = pfVar12 + 3;
      local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
      pfVar8 = pfVar15;
      pfVar15 = pfVar15 + 2;
      uVar9 = g_dwSourceVert;
    } while (local_4 != 0.0f);
  }
  g_dwSourceVert = uVar9;
  count = g_dwDestTVert;
  if (2 < (int)local_10) {
    g_dwDestTVert = g_dwSourceTVert;
    fVar10 = 0.0f;
    g_dwDestVert = g_dwSourceVert;
    g_dwSourceTVert = count;
    pfVar15 = (float *)((uVar17 - 0xc) + local_10 * 0xc);
    pfVar16 = (float *)g_dwSourceVert;
    if (0 < (int)local_10) {
      pfVar12 = (float *)(uVar17 + 4);
      pfVar8 = (float *)((count - 8) + local_10 * 8);
      iVar6 = 0;
      g_dwSourceVert = uVar17;
      local_4 = PUN(float,local_10);
      do {
        iVar7 = iVar6;
        if ((PUN(float,frustum[1]) <= pfVar15[1]) || (PUN(float,frustum[1]) <= *pfVar12)) {
          if (((pfVar15[1] != PUN(float,frustum[1])) && (*pfVar12 != PUN(float,frustum[1]))) &&
             ((pfVar15[1] < PUN(float,frustum[1]) || (*pfVar12 < PUN(float,frustum[1]))))) {
            iVar7 = iVar6 + 0xc;
            fVar11 = (PUN(float,frustum[1]) - pfVar15[1]) / (*pfVar12 - pfVar15[1]);
            *(int *)((int)pfVar16 + iVar6 + 4) = frustum[1];
            iVar6 = PUN(int,(float)fVar10) * 8;
            fVar10 = PUN(float,(PUN(int,(float)fVar10) + 1));
            *(float *)((g_dwDestVert - 4) + iVar7) = (pfVar12[1] - pfVar15[2]) * fVar11 + pfVar15[2]
            ;
            *(float *)((g_dwDestVert - 0xc) + iVar7) = (pfVar12[-1] - *pfVar15) * fVar11 + *pfVar15;
            *(float *)(g_dwDestTVert + iVar6) = (*(float *)count - *pfVar8) * fVar11 + *pfVar8;
            *(float *)(g_dwDestTVert + 4 + iVar6) =
                 (*(float *)(count + 4) - pfVar8[1]) * fVar11 + pfVar8[1];
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 1;
            pfVar16 = (float *)g_dwDestVert;
          }
          if (PUN(float,frustum[1]) <= *pfVar12) {
            pfVar16 = (float *)((int)pfVar16 + iVar7);
            fVar10 = PUN(float,(PUN(int,(float)fVar10) + 1));
            iVar7 = iVar7 + 0xc;
            *pfVar16 = pfVar12[-1];
            pfVar16[1] = *pfVar12;
            pfVar16[2] = pfVar12[1];
            *(undefined4 *)((g_dwDestTVert - 8) + PUN(int,(float)fVar10) * 8) = *(undefined4 *)count;
            *(undefined4 *)((g_dwDestTVert - 4) + PUN(int,(float)fVar10) * 8) = *(undefined4 *)(count + 4);
            pfVar16 = (float *)g_dwDestVert;
          }
        }
        pfVar15 = pfVar12 + -1;
        pfVar12 = pfVar12 + 3;
        local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
        pfVar8 = (float *)count;
        iVar6 = iVar7;
        uVar17 = g_dwSourceVert;
        count = count + 8;
      } while (local_4 != 0.0f);
    }
    g_dwSourceVert = uVar17;
    uVar9 = g_dwSourceTVert;
    if (PUN(int,(float)fVar10) < 3) {
      g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x40;
      return PUN(uint,(float)fVar10);
    }
    fVar11 = fVar10;
    pfVar15 = pfVar16;
    if (*frustum != 0) {
      fVar11 = 0.0f;
      g_dwSourceTVert = g_dwDestTVert;
      pfVar8 = pfVar16 + PUN(int,(float)fVar10) * 3 + -3;
      iVar6 = g_dwDestTVert - 8;
      count = g_dwDestTVert;
      pfVar15 = (float *)g_dwSourceVert;
      g_dwDestTVert = uVar9;
      g_dwDestVert = g_dwSourceVert;
      if (0 < PUN(int,(float)fVar10)) {
        pfVar13 = pfVar16 + 1;
        pfVar12 = (float *)(iVar6 + PUN(int,(float)fVar10) * 8);
        iVar6 = 0;
        g_dwSourceVert = (uint)pfVar16;
        local_4 = fVar10;
        do {
          iVar7 = iVar6;
          if ((pfVar8[1] <= PUN(float,frustum[2])) || (*pfVar13 <= PUN(float,frustum[2]))) {
            if (((pfVar8[1] != PUN(float,frustum[2])) && (*pfVar13 != PUN(float,frustum[2]))) &&
               ((PUN(float,frustum[2]) < pfVar8[1] || (PUN(float,frustum[2]) < *pfVar13)))) {
              iVar7 = iVar6 + 0xc;
              fVar10 = (PUN(float,frustum[2]) - pfVar8[1]) / (*pfVar13 - pfVar8[1]);
              *(int *)((int)pfVar15 + iVar6 + 4) = frustum[2];
              iVar6 = PUN(int,(float)fVar11) * 8;
              fVar11 = PUN(float,(PUN(int,(float)fVar11) + 1));
              *(float *)((g_dwDestVert - 4) + iVar7) = (pfVar13[1] - pfVar8[2]) * fVar10 + pfVar8[2]
              ;
              *(float *)((g_dwDestVert - 0xc) + iVar7) = (pfVar13[-1] - *pfVar8) * fVar10 + *pfVar8;
              *(float *)(g_dwDestTVert + iVar6) = (*(float *)count - *pfVar12) * fVar10 + *pfVar12;
              *(float *)(g_dwDestTVert + 4 + iVar6) =
                   (*(float *)(count + 4) - pfVar12[1]) * fVar10 + pfVar12[1];
              g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 2;
              pfVar15 = (float *)g_dwDestVert;
            }
            if (*pfVar13 <= PUN(float,frustum[2])) {
              pfVar15 = (float *)((int)pfVar15 + iVar7);
              fVar11 = PUN(float,(PUN(int,(float)fVar11) + 1));
              iVar7 = iVar7 + 0xc;
              *pfVar15 = pfVar13[-1];
              pfVar15[1] = *pfVar13;
              pfVar15[2] = pfVar13[1];
              *(undefined4 *)((g_dwDestTVert - 8) + PUN(int,(float)fVar11) * 8) = *(undefined4 *)count;
              *(undefined4 *)((g_dwDestTVert - 4) + PUN(int,(float)fVar11) * 8) = *(undefined4 *)(count + 4);
              pfVar15 = (float *)g_dwDestVert;
            }
          }
          pfVar8 = pfVar13 + -1;
          pfVar13 = pfVar13 + 3;
          local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
          pfVar12 = (float *)count;
          iVar6 = iVar7;
          pfVar16 = (float *)g_dwSourceVert;
          count = count + 8;
        } while (local_4 != 0.0f);
      }
      g_dwSourceVert = (uint)pfVar16;
      if (PUN(int,(float)fVar11) < 3) {
        return PUN(uint,(float)fVar11);
      }
    }
    if (pfVar15 != verts) {
      for (uVar9 = PUN(int,(float)fVar11) * 3 & 0x3fffffff; uVar9 != 0; uVar9 = uVar9 - 1) {
        *verts = *pfVar15;
        pfVar15 = pfVar15 + 1;
        verts = verts + 1;
      }
      for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
        *(undefined1 *)verts = *(undefined1 *)pfVar15;
        pfVar15 = (float *)((int)pfVar15 + 1);
        verts = (float *)((int)verts + 1);
      }
      pfVar15 = (float *)g_dwDestTVert;
      for (iVar6 = (PUN(uint,(float)fVar11) & 0x1fffffff) << 1; iVar6 != 0; iVar6 = iVar6 + -1) {
        *tverts = *pfVar15;
        pfVar15 = pfVar15 + 1;
        tverts = tverts + 1;
      }
      for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
        *(undefined1 *)tverts = *(undefined1 *)pfVar15;
        pfVar15 = (float *)((int)pfVar15 + 1);
        tverts = (float *)((int)tverts + 1);
      }
    }
    return PUN(uint,(float)fVar11);
  }
  return local_10;
}
#endif


/* ---- 0x0044be80  rdClip_Face3TOrtho ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdClip_Face3TOrtho (the remaster's GrimFandango (Linux): the matching branch of the
   rdPrimit3_ClipFace switch (geometry/lighting mode, perspective or ortho camera)); was
   rdClip_Face3_PosUvFlags. */

uint __cdecl rdClip_Face3TOrtho(int *frustum,float *verts,float *tverts,uint count)

{
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
  uint local_c;
  uint local_8;
  uint local_4;
  
  g_dwRdClip_faceStatus = 0;
  local_c = 0;
  puVar9 = &g_dwWorkVerts;
  g_dwSourceVert = (uint)verts;
  g_dwDestVert = (uint)&g_dwWorkVerts;
  g_dwSourceTVert = (uint)tverts;
  g_dwDestTVert = (uint)&g_dwWorkTVerts;
  if (0 < (int)count) {
    iVar13 = 0;
    local_8 = count;
    pfVar10 = verts + count * 3 + -3;
    pfVar12 = verts;
    pfVar5 = tverts + count * 2 + -2;
    pfVar8 = tverts;
    do {
      fVar2 = PUN(float,frustum[3]);
      fVar1 = PUN(float,frustum[3]);
      if ((fVar2 <= *pfVar10) || (fVar1 <= *pfVar12)) {
        iVar14 = iVar13;
        if (((*pfVar10 != fVar2) && (fVar1 != *pfVar12)) &&
           ((*pfVar10 < fVar2 || (*pfVar12 < fVar1)))) {
          fVar3 = (fVar2 - *pfVar10) / (*pfVar12 - *pfVar10);
          iVar14 = iVar13 + 0xc;
          iVar4 = local_c * 8;
          local_c = local_c + 1;
          *(float *)((int)puVar9 + iVar13) = fVar2;
          *(float *)((g_dwDestVert - 8) + iVar14) = (pfVar12[1] - pfVar10[1]) * fVar3 + pfVar10[1];
          *(float *)((g_dwDestVert - 4) + iVar14) = (pfVar12[2] - pfVar10[2]) * fVar3 + pfVar10[2];
          *(float *)(g_dwDestTVert + iVar4) = (*pfVar8 - *pfVar5) * fVar3 + *pfVar5;
          *(float *)(g_dwDestTVert + 4 + iVar4) = (pfVar8[1] - pfVar5[1]) * fVar3 + pfVar5[1];
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x10;
          puVar9 = (uint *)g_dwDestVert;
        }
        iVar13 = iVar14;
        if (fVar1 <= *pfVar12) {
          pfVar10 = (float *)((int)puVar9 + iVar14);
          *pfVar10 = *pfVar12;
          pfVar10[1] = pfVar12[1];
          pfVar10[2] = pfVar12[2];
          *(float *)(g_dwDestTVert + local_c * 8) = *pfVar8;
          *(float *)(g_dwDestTVert + 4 + local_c * 8) = pfVar8[1];
          local_c = local_c + 1;
          iVar13 = iVar14 + 0xc;
          puVar9 = (uint *)g_dwDestVert;
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
  uVar6 = g_dwSourceTVert;
  if (2 < (int)local_c) {
    g_dwDestVert = g_dwSourceVert;
    g_dwSourceTVert = g_dwDestTVert;
    local_c = 0;
    uVar11 = g_dwSourceVert;
    pfVar10 = (float *)puVar9;
    if (0 < (int)local_8) {
      iVar13 = 0;
      pfVar12 = (float *)(puVar9 + local_8 * 3 + -3);
      pfVar5 = (float *)((g_dwDestTVert - 8) + local_8 * 8);
      pfVar8 = (float *)g_dwDestTVert;
      g_dwDestTVert = uVar6;
      g_dwSourceVert = (uint)puVar9;
      do {
        fVar2 = PUN(float,frustum[5]);
        fVar1 = PUN(float,frustum[5]);
        if ((*pfVar12 <= fVar2) || (PUN(float,*puVar9) <= fVar1)) {
          if (((*pfVar12 != fVar2) && (fVar1 != PUN(float,*puVar9))) &&
             ((fVar2 < *pfVar12 || (fVar1 < PUN(float,*puVar9))))) {
            fVar3 = (fVar2 - *pfVar12) / (PUN(float,*puVar9) - *pfVar12);
            iVar13 = iVar13 + 0xc;
            iVar14 = local_c * 8;
            local_c = local_c + 1;
            *(float *)((uVar11 - 0xc) + iVar13) = fVar2;
            *(float *)((g_dwDestVert - 8) + iVar13) =
                 (PUN(float,puVar9[1]) - pfVar12[1]) * fVar3 + pfVar12[1];
            *(float *)((g_dwDestVert - 4) + iVar13) =
                 (PUN(float,puVar9[2]) - pfVar12[2]) * fVar3 + pfVar12[2];
            *(float *)(g_dwDestTVert + iVar14) = (*pfVar8 - *pfVar5) * fVar3 + *pfVar5;
            *(float *)(g_dwDestTVert + 4 + iVar14) = (pfVar8[1] - pfVar5[1]) * fVar3 + pfVar5[1];
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x20;
            uVar11 = g_dwDestVert;
          }
          if (PUN(float,*puVar9) <= fVar1) {
            pfVar10 = (float *)(uVar11 + iVar13);
            *pfVar10 = PUN(float,*puVar9);
            pfVar10[1] = PUN(float,puVar9[1]);
            pfVar10[2] = PUN(float,puVar9[2]);
            *(float *)(g_dwDestTVert + local_c * 8) = *pfVar8;
            *(float *)(g_dwDestTVert + 4 + local_c * 8) = pfVar8[1];
            local_c = local_c + 1;
            iVar13 = iVar13 + 0xc;
            uVar11 = g_dwDestVert;
          }
        }
        local_8 = local_8 - 1;
        pfVar12 = (float *)puVar9;
        puVar9 = puVar9 + 3;
        pfVar5 = pfVar8;
        pfVar8 = pfVar8 + 2;
        uVar6 = g_dwDestTVert;
        pfVar10 = (float *)g_dwSourceVert;
      } while (local_8 != 0);
    }
    g_dwSourceVert = (uint)pfVar10;
    g_dwDestTVert = uVar6;
    count = local_c;
    uVar6 = g_dwSourceTVert;
    if (2 < (int)local_c) {
      g_dwDestVert = g_dwSourceVert;
      g_dwSourceTVert = g_dwDestTVert;
      local_c = 0;
      pfVar10 = (float *)((uVar11 - 0xc) + count * 0xc);
      uVar7 = g_dwSourceVert;
      if (0 < (int)count) {
        pfVar12 = (float *)(uVar11 + 8);
        iVar13 = 0;
        pfVar5 = (float *)((g_dwDestTVert - 8) + count * 8);
        pfVar8 = (float *)g_dwDestTVert;
        g_dwDestTVert = uVar6;
        g_dwSourceVert = uVar11;
        do {
          fVar2 = PUN(float,frustum[4]);
          fVar1 = PUN(float,frustum[4]);
          if ((pfVar10[2] <= fVar2) || (*pfVar12 <= fVar1)) {
            if (((pfVar10[2] != fVar2) && (fVar1 != *pfVar12)) &&
               ((fVar2 < pfVar10[2] || (fVar1 < *pfVar12)))) {
              fVar3 = (fVar2 - pfVar10[2]) / (*pfVar12 - pfVar10[2]);
              iVar13 = iVar13 + 0xc;
              iVar14 = local_c * 8;
              local_c = local_c + 1;
              *(float *)((uVar7 - 0xc) + iVar13) = (pfVar12[-2] - *pfVar10) * fVar3 + *pfVar10;
              *(float *)((g_dwDestVert - 8) + iVar13) =
                   (pfVar12[-1] - pfVar10[1]) * fVar3 + pfVar10[1];
              *(float *)((g_dwDestVert - 4) + iVar13) = fVar2;
              *(float *)(g_dwDestTVert + iVar14) = (*pfVar8 - *pfVar5) * fVar3 + *pfVar5;
              *(float *)(g_dwDestTVert + 4 + iVar14) = (pfVar8[1] - pfVar5[1]) * fVar3 + pfVar5[1];
              g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 4;
              uVar7 = g_dwDestVert;
            }
            if (*pfVar12 <= fVar1) {
              pfVar10 = (float *)(uVar7 + iVar13);
              *pfVar10 = pfVar12[-2];
              pfVar10[1] = pfVar12[-1];
              pfVar10[2] = *pfVar12;
              *(float *)(g_dwDestTVert + local_c * 8) = *pfVar8;
              *(float *)(g_dwDestTVert + 4 + local_c * 8) = pfVar8[1];
              local_c = local_c + 1;
              iVar13 = iVar13 + 0xc;
              uVar7 = g_dwDestVert;
            }
          }
          pfVar10 = pfVar12 + -2;
          pfVar12 = pfVar12 + 3;
          count = count - 1;
          pfVar5 = pfVar8;
          pfVar8 = pfVar8 + 2;
          uVar6 = g_dwDestTVert;
          uVar11 = g_dwSourceVert;
        } while (count != 0);
      }
      g_dwSourceVert = uVar11;
      g_dwDestTVert = uVar6;
      count = local_c;
      uVar6 = g_dwSourceTVert;
      if (2 < (int)local_c) {
        g_dwSourceTVert = g_dwDestTVert;
        local_c = 0;
        pfVar10 = (float *)((uVar7 - 0xc) + count * 0xc);
        uVar11 = g_dwSourceVert;
        g_dwDestVert = g_dwSourceVert;
        if (0 < (int)count) {
          pfVar12 = (float *)(uVar7 + 8);
          iVar13 = 0;
          pfVar5 = (float *)((g_dwDestTVert - 8) + count * 8);
          pfVar8 = (float *)g_dwDestTVert;
          g_dwDestTVert = uVar6;
          g_dwSourceVert = uVar7;
          do {
            fVar2 = PUN(float,frustum[6]);
            fVar1 = PUN(float,frustum[6]);
            if ((fVar2 <= pfVar10[2]) || (fVar1 <= *pfVar12)) {
              if (((pfVar10[2] != fVar2) && (fVar1 != *pfVar12)) &&
                 ((pfVar10[2] < fVar2 || (*pfVar12 < fVar1)))) {
                fVar3 = (fVar2 - pfVar10[2]) / (*pfVar12 - pfVar10[2]);
                iVar13 = iVar13 + 0xc;
                iVar14 = local_c * 8;
                local_c = local_c + 1;
                *(float *)((uVar11 - 0xc) + iVar13) = (pfVar12[-2] - *pfVar10) * fVar3 + *pfVar10;
                *(float *)((g_dwDestVert - 8) + iVar13) =
                     (pfVar12[-1] - pfVar10[1]) * fVar3 + pfVar10[1];
                *(float *)((g_dwDestVert - 4) + iVar13) = fVar2;
                *(float *)(g_dwDestTVert + iVar14) = (*pfVar8 - *pfVar5) * fVar3 + *pfVar5;
                *(float *)(g_dwDestTVert + 4 + iVar14) = (pfVar8[1] - pfVar5[1]) * fVar3 + pfVar5[1]
                ;
                g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 8;
                uVar11 = g_dwDestVert;
              }
              if (fVar1 <= *pfVar12) {
                pfVar10 = (float *)(uVar11 + iVar13);
                *pfVar10 = pfVar12[-2];
                pfVar10[1] = pfVar12[-1];
                pfVar10[2] = *pfVar12;
                *(float *)(g_dwDestTVert + local_c * 8) = *pfVar8;
                *(float *)(g_dwDestTVert + 4 + local_c * 8) = pfVar8[1];
                local_c = local_c + 1;
                iVar13 = iVar13 + 0xc;
                uVar11 = g_dwDestVert;
              }
            }
            pfVar10 = pfVar12 + -2;
            pfVar12 = pfVar12 + 3;
            count = count - 1;
            pfVar5 = pfVar8;
            pfVar8 = pfVar8 + 2;
            uVar6 = g_dwDestTVert;
            uVar7 = g_dwSourceVert;
          } while (count != 0);
        }
        g_dwSourceVert = uVar7;
        g_dwDestTVert = uVar6;
        uVar6 = g_dwSourceTVert;
        if ((int)local_c < 3) {
          return local_c;
        }
        uVar7 = 0;
        g_dwSourceTVert = g_dwDestTVert;
        pfVar10 = (float *)((uVar11 - 0xc) + local_c * 0xc);
        iVar13 = g_dwDestTVert - 8;
        local_8 = g_dwDestTVert;
        pfVar12 = (float *)g_dwSourceVert;
        g_dwDestTVert = uVar6;
        g_dwDestVert = g_dwSourceVert;
        if (0 < (int)local_c) {
          pfVar5 = (float *)(uVar11 + 4);
          iVar14 = 0;
          count = local_c;
          pfVar8 = (float *)(iVar13 + local_c * 8);
          g_dwSourceVert = uVar11;
          do {
            if ((PUN(float,frustum[1]) <= pfVar10[1]) || (PUN(float,frustum[1]) <= *pfVar5)) {
              if (((pfVar10[1] != PUN(float,frustum[1])) && (*pfVar5 != PUN(float,frustum[1]))) &&
                 ((pfVar10[1] < PUN(float,frustum[1]) || (*pfVar5 < PUN(float,frustum[1]))))) {
                iVar4 = iVar14 + 0xc;
                fVar1 = (PUN(float,frustum[1]) - pfVar10[1]) / (*pfVar5 - pfVar10[1]);
                *(int *)((int)pfVar12 + iVar14 + 4) = frustum[1];
                iVar13 = uVar7 * 8;
                uVar7 = uVar7 + 1;
                *(float *)((g_dwDestVert - 4) + iVar4) =
                     (pfVar5[1] - pfVar10[2]) * fVar1 + pfVar10[2];
                *(float *)((g_dwDestVert - 0xc) + iVar4) =
                     (pfVar5[-1] - *pfVar10) * fVar1 + *pfVar10;
                *(float *)(g_dwDestTVert + iVar13) = (*(float *)local_8 - *pfVar8) * fVar1 + *pfVar8
                ;
                *(float *)(g_dwDestTVert + 4 + iVar13) =
                     (*(float *)(local_8 + 4) - pfVar8[1]) * fVar1 + pfVar8[1];
                g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 1;
                pfVar12 = (float *)g_dwDestVert;
                iVar14 = iVar4;
              }
              if (PUN(float,frustum[1]) <= *pfVar5) {
                pfVar12 = (float *)((int)pfVar12 + iVar14);
                uVar7 = uVar7 + 1;
                iVar14 = iVar14 + 0xc;
                *pfVar12 = pfVar5[-1];
                pfVar12[1] = *pfVar5;
                pfVar12[2] = pfVar5[1];
                *(undefined4 *)((g_dwDestTVert - 8) + uVar7 * 8) = *(undefined4 *)local_8;
                *(undefined4 *)((g_dwDestTVert - 4) + uVar7 * 8) = *(undefined4 *)(local_8 + 4);
                pfVar12 = (float *)g_dwDestVert;
              }
            }
            pfVar10 = pfVar5 + -1;
            pfVar5 = pfVar5 + 3;
            count = count - 1;
            pfVar8 = (float *)local_8;
            uVar11 = g_dwSourceVert;
            local_8 = local_8 + 8;
          } while (count != 0);
        }
        g_dwSourceVert = uVar11;
        uVar6 = g_dwSourceTVert;
        if ((int)uVar7 < 3) {
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x40;
          return uVar7;
        }
        local_c = uVar7;
        pfVar10 = pfVar12;
        if (*frustum != 0) {
          local_c = 0;
          g_dwDestVert = g_dwSourceVert;
          g_dwSourceTVert = g_dwDestTVert;
          pfVar5 = pfVar12 + uVar7 * 3 + -3;
          iVar13 = g_dwDestTVert - 8;
          local_8 = g_dwDestTVert;
          pfVar10 = (float *)g_dwSourceVert;
          g_dwDestTVert = uVar6;
          if (0 < (int)uVar7) {
            iVar14 = 0;
            pfVar15 = pfVar12 + 1;
            pfVar8 = (float *)(iVar13 + uVar7 * 8);
            g_dwSourceVert = (uint)pfVar12;
            count = uVar7;
            do {
              if ((pfVar5[1] <= PUN(float,frustum[2])) || (*pfVar15 <= PUN(float,frustum[2]))) {
                if (((pfVar5[1] != PUN(float,frustum[2])) && (*pfVar15 != PUN(float,frustum[2]))) &&
                   ((PUN(float,frustum[2]) < pfVar5[1] || (PUN(float,frustum[2]) < *pfVar15)))) {
                  iVar4 = iVar14 + 0xc;
                  fVar1 = (PUN(float,frustum[2]) - pfVar5[1]) / (*pfVar15 - pfVar5[1]);
                  *(int *)((int)pfVar10 + iVar14 + 4) = frustum[2];
                  iVar13 = local_c * 8;
                  local_c = local_c + 1;
                  *(float *)((g_dwDestVert - 4) + iVar4) =
                       (pfVar15[1] - pfVar5[2]) * fVar1 + pfVar5[2];
                  *(float *)((g_dwDestVert - 0xc) + iVar4) =
                       (pfVar15[-1] - *pfVar5) * fVar1 + *pfVar5;
                  *(float *)(g_dwDestTVert + iVar13) =
                       (*(float *)local_8 - *pfVar8) * fVar1 + *pfVar8;
                  *(float *)(g_dwDestTVert + 4 + iVar13) =
                       (*(float *)(local_8 + 4) - pfVar8[1]) * fVar1 + pfVar8[1];
                  g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 2;
                  iVar14 = iVar4;
                  pfVar10 = (float *)g_dwDestVert;
                }
                if (*pfVar15 <= PUN(float,frustum[2])) {
                  pfVar10 = (float *)((int)pfVar10 + iVar14);
                  local_c = local_c + 1;
                  iVar14 = iVar14 + 0xc;
                  *pfVar10 = pfVar15[-1];
                  pfVar10[1] = *pfVar15;
                  pfVar10[2] = pfVar15[1];
                  *(undefined4 *)((g_dwDestTVert - 8) + local_c * 8) = *(undefined4 *)local_8;
                  *(undefined4 *)((g_dwDestTVert - 4) + local_c * 8) = *(undefined4 *)(local_8 + 4);
                  pfVar10 = (float *)g_dwDestVert;
                }
              }
              pfVar5 = pfVar15 + -1;
              pfVar15 = pfVar15 + 3;
              count = count - 1;
              pfVar8 = (float *)local_8;
              pfVar12 = (float *)g_dwSourceVert;
              local_8 = local_8 + 8;
            } while (count != 0);
          }
          g_dwSourceVert = (uint)pfVar12;
          if ((int)local_c < 3) {
            return local_c;
          }
        }
        if (pfVar10 != verts) {
          for (uVar6 = local_c * 3 & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1) {
            *verts = *pfVar10;
            pfVar10 = pfVar10 + 1;
            verts = verts + 1;
          }
          for (iVar13 = 0; iVar13 != 0; iVar13 = iVar13 + -1) {
            *(undefined1 *)verts = *(undefined1 *)pfVar10;
            pfVar10 = (float *)((int)pfVar10 + 1);
            verts = (float *)((int)verts + 1);
          }
          pfVar10 = (float *)g_dwDestTVert;
          for (iVar13 = (local_c & 0x1fffffff) << 1; iVar13 != 0; iVar13 = iVar13 + -1) {
            *tverts = *pfVar10;
            pfVar10 = pfVar10 + 1;
            tverts = tverts + 1;
          }
          for (iVar13 = 0; iVar13 != 0; iVar13 = iVar13 + -1) {
            *(undefined1 *)tverts = *(undefined1 *)pfVar10;
            pfVar10 = (float *)((int)pfVar10 + 1);
            tverts = (float *)((int)tverts + 1);
          }
        }
      }
    }
  }
  return local_c;
}
#endif


/* ---- 0x0044c9d0  rdClip_Face3GT ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdClip_Face3GT (the remaster's GrimFandango (Linux): the matching branch of the
   rdPrimit3_ClipFace switch (geometry/lighting mode, perspective or ortho camera)); was
   rdClip_Face3_PosUvLitColor. */

uint __cdecl rdClip_Face3GT(int *frustum,float *verts,float *tverts,uint *ivert,uint count)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  uint uVar9;
  int iVar10;
  float fVar11;
  float *pfVar12;
  uint *puVar13;
  float *pfVar14;
  float *pfVar15;
  undefined4 *puVar16;
  uint uVar17;
  int iVar18;
  float *pfVar19;
  uint local_18;
  #define local_14 (*(float (*)[2])(_frame + (0x30 - 0x14)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  uint local_8;
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  g_dwSourceIVert = (uint)ivert;
  local_14[0] = PUN(float,(ivert + (count - 1)));
  fVar7 = 0.0f;
  puVar13 = &g_dwWorkVerts;
  g_dwRdClip_faceStatus = 0;
  g_dwSourceVert = (uint)verts;
  g_dwDestVert = (uint)&g_dwWorkVerts;
  g_dwSourceTVert = (uint)tverts;
  g_dwDestTVert = (uint)&g_dwWorkTVerts;
  g_dwDestIVert = (uint)&g_dwWorkIVerts;
  local_18 = (uint)ivert;
  if (0 < (int)count) {
    iVar10 = 0;
    local_4 = PUN(float,count);
    pfVar14 = verts;
    pfVar15 = tverts;
    pfVar8 = tverts + count * 2 + -2;
    count = (uint)(verts + count * 3 + -3);
    do {
      pfVar19 = pfVar15;
      pfVar12 = pfVar14;
      fVar11 = PUN(float,frustum[0xc]) * *(float *)(count + 4);
      fVar2 = PUN(float,frustum[0xc]) * pfVar12[1];
      if ((fVar11 <= *(float *)count) || (fVar2 <= *pfVar12)) {
        if (((*(float *)count != fVar11) && (fVar2 != *pfVar12)) &&
           ((*(float *)count < fVar11 || (*pfVar12 < fVar2)))) {
          fVar11 = pfVar12[1] - *(float *)(count + 4);
          fVar3 = *pfVar12 - *(float *)count;
          fVar1 = PUN(float,frustum[0xc]) * fVar11 - fVar3;
          fVar4 = pfVar12[1] * *(float *)count - *(float *)(count + 4) * *pfVar12;
          if (fVar1 != 0.0f) {
            fVar4 = fVar4 / fVar1;
          }
          fVar1 = fVar11;
          if (fVar11 < 0.0f) {
            fVar1 = -fVar11;
          }
          fVar5 = fVar3;
          if (fVar3 < 0.0f) {
            fVar5 = -fVar3;
          }
          if (fVar1 <= fVar5) {
            fVar11 = (PUN(float,frustum[0xc]) * fVar4 - *(float *)count) / fVar3;
          }
          else {
            fVar11 = (fVar4 - *(float *)(count + 4)) / fVar11;
          }
          *(float *)((int)puVar13 + iVar10) = PUN(float,frustum[0xc]) * fVar4;
          iVar10 = iVar10 + 0xc;
          *(float *)((g_dwDestVert - 8) + iVar10) = fVar4;
          fVar7 = PUN(float,(PUN(int,(float)fVar7) + 1));
          *(float *)((g_dwDestVert - 4) + iVar10) =
               (pfVar12[2] - *(float *)(count + 8)) * fVar11 + *(float *)(count + 8);
          *(float *)((g_dwDestTVert - 8) + PUN(int,(float)fVar7) * 8) = (*pfVar19 - *pfVar8) * fVar11 + *pfVar8
          ;
          *(float *)((g_dwDestTVert - 4) + PUN(int,(float)fVar7) * 8) =
               (pfVar19[1] - pfVar8[1]) * fVar11 + pfVar8[1];
          *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar7) * 4) =
               (*(float *)local_18 - *PUN(float *,(float)local_14[0])) * fVar11 + *PUN(float *,(float)local_14[0]);
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x10;
          puVar13 = (uint *)g_dwDestVert;
        }
        if (fVar2 <= *pfVar12) {
          pfVar14 = (float *)((int)puVar13 + iVar10);
          fVar7 = PUN(float,(PUN(int,(float)fVar7) + 1));
          iVar10 = iVar10 + 0xc;
          *pfVar14 = *pfVar12;
          pfVar14[1] = pfVar12[1];
          pfVar14[2] = pfVar12[2];
          *(float *)((g_dwDestTVert - 8) + PUN(int,(float)fVar7) * 8) = *pfVar19;
          *(float *)((g_dwDestTVert - 4) + PUN(int,(float)fVar7) * 8) = pfVar19[1];
          *(undefined4 *)((g_dwDestIVert - 4) + PUN(int,(float)fVar7) * 4) = *(undefined4 *)local_18;
          puVar13 = (uint *)g_dwDestVert;
        }
      }
      local_14[0] = PUN(float,local_18);
      local_18 = local_18 + 4;
      local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
      pfVar14 = pfVar12 + 3;
      pfVar15 = pfVar19 + 2;
      pfVar8 = pfVar19;
      count = (uint)pfVar12;
    } while (local_4 != 0.0f);
  }
  local_18 = g_dwDestIVert;
  uVar9 = g_dwSourceTVert;
  if (PUN(int,(float)fVar7) < 3) {
    return PUN(uint,(float)fVar7);
  }
  g_dwSourceTVert = g_dwDestTVert;
  g_dwDestIVert = g_dwSourceIVert;
  g_dwSourceIVert = local_18;
  fVar11 = 0.0f;
  local_14[0] = PUN(float,((local_18 - 4) + PUN(int,(float)fVar7) * 4));
  uVar17 = g_dwSourceVert;
  g_dwDestVert = g_dwSourceVert;
  pfVar14 = (float *)puVar13;
  if (0 < PUN(int,(float)fVar7)) {
    iVar10 = 0;
    pfVar15 = (float *)g_dwDestTVert;
    pfVar8 = (float *)((g_dwDestTVert - 8) + PUN(int,(float)fVar7) * 8);
    g_dwDestTVert = uVar9;
    g_dwSourceVert = (uint)puVar13;
    count = (uint)(puVar13 + PUN(int,(float)fVar7) * 3 + -3);
    local_4 = fVar7;
    do {
      pfVar12 = (float *)puVar13;
      pfVar14 = pfVar15;
      fVar7 = PUN(float,frustum[10]) * *(float *)(count + 4);
      fVar2 = PUN(float,frustum[10]) * pfVar12[1];
      if ((*(float *)count <= fVar7) || (*pfVar12 <= fVar2)) {
        if (((*(float *)count != fVar7) && (fVar2 != *pfVar12)) &&
           ((fVar7 < *(float *)count || (fVar2 < *pfVar12)))) {
          fVar7 = pfVar12[1] - *(float *)(count + 4);
          fVar3 = *pfVar12 - *(float *)count;
          fVar1 = PUN(float,frustum[10]) * fVar7 - fVar3;
          fVar4 = pfVar12[1] * *(float *)count - *(float *)(count + 4) * *pfVar12;
          if (fVar1 != 0.0f) {
            fVar4 = fVar4 / fVar1;
          }
          fVar1 = fVar7;
          if (fVar7 < 0.0f) {
            fVar1 = -fVar7;
          }
          fVar5 = fVar3;
          if (fVar3 < 0.0f) {
            fVar5 = -fVar3;
          }
          if (fVar1 <= fVar5) {
            fVar7 = (PUN(float,frustum[10]) * fVar4 - *(float *)count) / fVar3;
          }
          else {
            fVar7 = (fVar4 - *(float *)(count + 4)) / fVar7;
          }
          *(float *)(uVar17 + iVar10) = PUN(float,frustum[10]) * fVar4;
          iVar10 = iVar10 + 0xc;
          *(float *)((g_dwDestVert - 8) + iVar10) = fVar4;
          fVar11 = PUN(float,(PUN(int,(float)fVar11) + 1));
          *(float *)((g_dwDestVert - 4) + iVar10) =
               (pfVar12[2] - *(float *)(count + 8)) * fVar7 + *(float *)(count + 8);
          *(float *)((g_dwDestTVert - 8) + PUN(int,(float)fVar11) * 8) = (*pfVar14 - *pfVar8) * fVar7 + *pfVar8
          ;
          *(float *)((g_dwDestTVert - 4) + PUN(int,(float)fVar11) * 8) =
               (pfVar14[1] - pfVar8[1]) * fVar7 + pfVar8[1];
          *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar11) * 4) =
               (*(float *)local_18 - *PUN(float *,(float)local_14[0])) * fVar7 + *PUN(float *,(float)local_14[0]);
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x20;
          uVar17 = g_dwDestVert;
        }
        if (*pfVar12 <= fVar2) {
          pfVar15 = (float *)(uVar17 + iVar10);
          fVar11 = PUN(float,(PUN(int,(float)fVar11) + 1));
          iVar10 = iVar10 + 0xc;
          *pfVar15 = *pfVar12;
          pfVar15[1] = pfVar12[1];
          pfVar15[2] = pfVar12[2];
          *(float *)((g_dwDestTVert - 8) + PUN(int,(float)fVar11) * 8) = *pfVar14;
          *(float *)((g_dwDestTVert - 4) + PUN(int,(float)fVar11) * 8) = pfVar14[1];
          *(undefined4 *)((g_dwDestIVert - 4) + PUN(int,(float)fVar11) * 4) = *(undefined4 *)local_18;
          uVar17 = g_dwDestVert;
        }
      }
      local_14[0] = PUN(float,local_18);
      local_18 = local_18 + 4;
      local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
      pfVar15 = pfVar14 + 2;
      puVar13 = (uint *)(pfVar12 + 3);
      pfVar8 = pfVar14;
      uVar9 = g_dwDestTVert;
      pfVar14 = (float *)g_dwSourceVert;
      count = (uint)pfVar12;
    } while (local_4 != 0.0f);
  }
  g_dwSourceVert = (uint)pfVar14;
  g_dwDestTVert = uVar9;
  local_18 = g_dwDestIVert;
  pfVar14 = (float *)g_dwDestTVert;
  uVar9 = g_dwSourceIVert;
  if (2 < PUN(int,(float)fVar11)) {
    g_dwDestTVert = g_dwSourceTVert;
    g_dwSourceIVert = g_dwDestIVert;
    g_dwSourceTVert = (uint)pfVar14;
    g_dwDestIVert = uVar9;
    fVar7 = 0.0f;
    g_dwDestVert = g_dwSourceVert;
    pfVar15 = (float *)((uVar17 - 0xc) + PUN(int,(float)fVar11) * 0xc);
    local_14[0] = PUN(float,((local_18 - 4) + PUN(int,(float)fVar11) * 4));
    uVar9 = g_dwSourceVert;
    if (0 < PUN(int,(float)fVar11)) {
      iVar10 = 0;
      local_c = uVar17 + 8;
      pfVar8 = (float *)(((int)pfVar14 - 8U) + PUN(int,(float)fVar11) * 8);
      g_dwSourceVert = uVar17;
      local_4 = fVar11;
      do {
        pfVar12 = pfVar14;
        fVar11 = PUN(float,frustum[0xb]) * pfVar15[1];
        fVar2 = PUN(float,frustum[0xb]) * *(float *)(local_c - 4);
        if ((pfVar15[2] <= fVar11) || (*(float *)local_c <= fVar2)) {
          if (((pfVar15[2] != fVar11) && (fVar2 != *(float *)local_c)) &&
             ((fVar11 < pfVar15[2] || (fVar2 < *(float *)local_c)))) {
            fVar11 = *(float *)(local_c - 4) - pfVar15[1];
            fVar3 = *(float *)local_c - pfVar15[2];
            fVar1 = PUN(float,frustum[0xb]) * fVar11 - fVar3;
            fVar4 = pfVar15[2] * *(float *)(local_c - 4) - pfVar15[1] * *(float *)local_c;
            if (fVar1 != 0.0f) {
              fVar4 = fVar4 / fVar1;
            }
            fVar1 = PUN(float,frustum[0xb]);
            fVar5 = fVar11;
            if (fVar11 < 0.0f) {
              fVar5 = -fVar11;
            }
            fVar6 = fVar3;
            if (fVar3 < 0.0f) {
              fVar6 = -fVar3;
            }
            if (fVar5 <= fVar6) {
              fVar11 = (fVar1 * fVar4 - pfVar15[2]) / fVar3;
            }
            else {
              fVar11 = (fVar4 - pfVar15[1]) / fVar11;
            }
            iVar10 = iVar10 + 0xc;
            fVar7 = PUN(float,(PUN(int,(float)fVar7) + 1));
            *(float *)((uVar9 - 0xc) + iVar10) =
                 (*(float *)(local_c - 8) - *pfVar15) * fVar11 + *pfVar15;
            *(float *)((g_dwDestVert - 8) + iVar10) = fVar4;
            *(float *)((g_dwDestVert - 4) + iVar10) = fVar1 * fVar4;
            *(float *)((g_dwDestTVert - 8) + PUN(int,(float)fVar7) * 8) =
                 (*pfVar12 - *pfVar8) * fVar11 + *pfVar8;
            *(float *)((g_dwDestTVert - 4) + PUN(int,(float)fVar7) * 8) =
                 (pfVar12[1] - pfVar8[1]) * fVar11 + pfVar8[1];
            *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar7) * 4) =
                 (*(float *)local_18 - *PUN(float *,(float)local_14[0])) * fVar11 + *PUN(float *,(float)local_14[0]);
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 4;
            uVar9 = g_dwDestVert;
          }
          if (*(float *)local_c <= fVar2) {
            puVar16 = (undefined4 *)(uVar9 + iVar10);
            fVar7 = PUN(float,(PUN(int,(float)fVar7) + 1));
            iVar10 = iVar10 + 0xc;
            *puVar16 = *(undefined4 *)(local_c - 8);
            puVar16[1] = *(undefined4 *)(local_c - 4);
            puVar16[2] = *(undefined4 *)local_c;
            *(float *)((g_dwDestTVert - 8) + PUN(int,(float)fVar7) * 8) = *pfVar12;
            *(float *)((g_dwDestTVert - 4) + PUN(int,(float)fVar7) * 8) = pfVar12[1];
            *(undefined4 *)((g_dwDestIVert - 4) + PUN(int,(float)fVar7) * 4) = *(undefined4 *)local_18;
            uVar9 = g_dwDestVert;
          }
        }
        pfVar15 = (float *)(local_c - 8);
        local_c = local_c + 0xc;
        local_14[0] = PUN(float,local_18);
        local_18 = local_18 + 4;
        local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
        pfVar14 = pfVar12 + 2;
        pfVar8 = pfVar12;
        uVar17 = g_dwSourceVert;
      } while (local_4 != 0.0f);
    }
    g_dwSourceVert = uVar17;
    local_18 = g_dwDestIVert;
    pfVar14 = (float *)g_dwDestTVert;
    if (PUN(int,(float)fVar7) < 3) {
      return PUN(uint,(float)fVar7);
    }
    g_dwDestTVert = g_dwSourceTVert;
    g_dwDestIVert = g_dwSourceIVert;
    g_dwSourceIVert = local_18;
    fVar11 = 0.0f;
    local_14[0] = PUN(float,((local_18 - 4) + PUN(int,(float)fVar7) * 4));
    pfVar15 = (float *)((uVar9 - 0xc) + PUN(int,(float)fVar7) * 0xc);
    g_dwDestVert = g_dwSourceVert;
    g_dwSourceTVert = (uint)pfVar14;
    uVar17 = g_dwSourceVert;
    if (0 < PUN(int,(float)fVar7)) {
      iVar10 = 0;
      local_c = uVar9 + 8;
      pfVar8 = (float *)(((int)pfVar14 - 8U) + PUN(int,(float)fVar7) * 8);
      g_dwSourceVert = uVar9;
      local_4 = fVar7;
      do {
        pfVar12 = pfVar14;
        fVar7 = PUN(float,frustum[8]) * pfVar15[1];
        fVar2 = PUN(float,frustum[8]) * *(float *)(local_c - 4);
        if ((fVar7 <= pfVar15[2]) || (fVar2 <= *(float *)local_c)) {
          if (((pfVar15[2] != fVar7) && (fVar2 != *(float *)local_c)) &&
             ((pfVar15[2] < fVar7 || (*(float *)local_c < fVar2)))) {
            fVar7 = *(float *)(local_c - 4) - pfVar15[1];
            fVar3 = *(float *)local_c - pfVar15[2];
            fVar1 = PUN(float,frustum[8]) * fVar7 - fVar3;
            fVar4 = pfVar15[2] * *(float *)(local_c - 4) - pfVar15[1] * *(float *)local_c;
            if (fVar1 != 0.0f) {
              fVar4 = fVar4 / fVar1;
            }
            fVar1 = PUN(float,frustum[8]);
            fVar5 = fVar7;
            if (fVar7 < 0.0f) {
              fVar5 = -fVar7;
            }
            fVar6 = fVar3;
            if (fVar3 < 0.0f) {
              fVar6 = -fVar3;
            }
            if (fVar5 <= fVar6) {
              fVar7 = (fVar1 * fVar4 - pfVar15[2]) / fVar3;
            }
            else {
              fVar7 = (fVar4 - pfVar15[1]) / fVar7;
            }
            iVar10 = iVar10 + 0xc;
            fVar11 = PUN(float,(PUN(int,(float)fVar11) + 1));
            *(float *)((uVar17 - 0xc) + iVar10) =
                 (*(float *)(local_c - 8) - *pfVar15) * fVar7 + *pfVar15;
            *(float *)((g_dwDestVert - 8) + iVar10) = fVar4;
            *(float *)((g_dwDestVert - 4) + iVar10) = fVar1 * fVar4;
            *(float *)((g_dwDestTVert - 8) + PUN(int,(float)fVar11) * 8) =
                 (*pfVar12 - *pfVar8) * fVar7 + *pfVar8;
            *(float *)((g_dwDestTVert - 4) + PUN(int,(float)fVar11) * 8) =
                 (pfVar12[1] - pfVar8[1]) * fVar7 + pfVar8[1];
            *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar11) * 4) =
                 (*(float *)local_18 - *PUN(float *,(float)local_14[0])) * fVar7 + *PUN(float *,(float)local_14[0]);
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 8;
            uVar17 = g_dwDestVert;
          }
          if (fVar2 <= *(float *)local_c) {
            puVar16 = (undefined4 *)(uVar17 + iVar10);
            fVar11 = PUN(float,(PUN(int,(float)fVar11) + 1));
            iVar10 = iVar10 + 0xc;
            *puVar16 = *(undefined4 *)(local_c - 8);
            puVar16[1] = *(undefined4 *)(local_c - 4);
            puVar16[2] = *(undefined4 *)local_c;
            *(float *)((g_dwDestTVert - 8) + PUN(int,(float)fVar11) * 8) = *pfVar12;
            *(float *)((g_dwDestTVert - 4) + PUN(int,(float)fVar11) * 8) = pfVar12[1];
            *(undefined4 *)((g_dwDestIVert - 4) + PUN(int,(float)fVar11) * 4) = *(undefined4 *)local_18;
            uVar17 = g_dwDestVert;
          }
        }
        pfVar15 = (float *)(local_c - 8);
        local_c = local_c + 0xc;
        local_14[0] = PUN(float,local_18);
        local_18 = local_18 + 4;
        local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
        pfVar14 = pfVar12 + 2;
        pfVar8 = pfVar12;
        uVar9 = g_dwSourceVert;
      } while (local_4 != 0.0f);
    }
    g_dwSourceVert = uVar9;
    local_18 = g_dwDestIVert;
    count = g_dwDestTVert;
    if (PUN(int,(float)fVar11) < 3) {
      return PUN(uint,(float)fVar11);
    }
    g_dwDestTVert = g_dwSourceTVert;
    g_dwDestIVert = g_dwSourceIVert;
    g_dwSourceTVert = count;
    g_dwSourceIVert = local_18;
    fVar7 = 0.0f;
    local_14[0] = PUN(float,((local_18 - 4) + PUN(int,(float)fVar11) * 4));
    pfVar14 = (float *)((uVar17 - 0xc) + PUN(int,(float)fVar11) * 0xc);
    g_dwDestVert = g_dwSourceVert;
    pfVar15 = (float *)g_dwSourceVert;
    if (0 < PUN(int,(float)fVar11)) {
      pfVar12 = (float *)(uVar17 + 4);
      pfVar8 = (float *)((count - 8) + PUN(int,(float)fVar11) * 8);
      iVar10 = 0;
      g_dwSourceVert = uVar17;
      local_4 = fVar11;
      do {
        iVar18 = iVar10;
        if ((PUN(float,frustum[1]) <= pfVar14[1]) || (PUN(float,frustum[1]) <= *pfVar12)) {
          if (((pfVar14[1] != PUN(float,frustum[1])) && (*pfVar12 != PUN(float,frustum[1]))) &&
             ((pfVar14[1] < PUN(float,frustum[1]) || (*pfVar12 < PUN(float,frustum[1]))))) {
            iVar18 = iVar10 + 0xc;
            fVar7 = PUN(float,(PUN(int,(float)fVar7) + 1));
            fVar11 = (PUN(float,frustum[1]) - pfVar14[1]) / (*pfVar12 - pfVar14[1]);
            *(int *)((int)pfVar15 + iVar10 + 4) = frustum[1];
            *(float *)((g_dwDestVert - 4) + iVar18) =
                 (pfVar12[1] - pfVar14[2]) * fVar11 + pfVar14[2];
            *(float *)((g_dwDestVert - 0xc) + iVar18) = (pfVar12[-1] - *pfVar14) * fVar11 + *pfVar14
            ;
            *(float *)((g_dwDestTVert - 8) + PUN(int,(float)fVar7) * 8) =
                 (*(float *)count - *pfVar8) * fVar11 + *pfVar8;
            *(float *)((g_dwDestTVert - 4) + PUN(int,(float)fVar7) * 8) =
                 (*(float *)(count + 4) - pfVar8[1]) * fVar11 + pfVar8[1];
            *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar7) * 4) =
                 (*(float *)local_18 - *PUN(float *,(float)local_14[0])) * fVar11 + *PUN(float *,(float)local_14[0]);
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 1;
            pfVar15 = (float *)g_dwDestVert;
          }
          if (PUN(float,frustum[1]) <= *pfVar12) {
            pfVar15 = (float *)((int)pfVar15 + iVar18);
            fVar7 = PUN(float,(PUN(int,(float)fVar7) + 1));
            iVar18 = iVar18 + 0xc;
            *pfVar15 = pfVar12[-1];
            pfVar15[1] = *pfVar12;
            pfVar15[2] = pfVar12[1];
            *(undefined4 *)((g_dwDestTVert - 8) + PUN(int,(float)fVar7) * 8) = *(undefined4 *)count;
            *(undefined4 *)((g_dwDestTVert - 4) + PUN(int,(float)fVar7) * 8) = *(undefined4 *)(count + 4);
            *(undefined4 *)((g_dwDestIVert - 4) + PUN(int,(float)fVar7) * 4) = *(undefined4 *)local_18;
            pfVar15 = (float *)g_dwDestVert;
          }
        }
        pfVar14 = pfVar12 + -1;
        local_14[0] = PUN(float,local_18);
        local_18 = local_18 + 4;
        pfVar12 = pfVar12 + 3;
        local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
        pfVar8 = (float *)count;
        iVar10 = iVar18;
        uVar17 = g_dwSourceVert;
        count = count + 8;
      } while (local_4 != 0.0f);
    }
    g_dwSourceVert = uVar17;
    uVar17 = g_dwSourceTVert;
    uVar9 = g_dwSourceIVert;
    if (PUN(int,(float)fVar7) < 3) {
      g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x40;
      return PUN(uint,(float)fVar7);
    }
    fVar11 = fVar7;
    pfVar14 = pfVar15;
    if (*frustum != 0) {
      g_dwSourceTVert = g_dwDestTVert;
      g_dwSourceIVert = g_dwDestIVert;
      fVar11 = 0.0f;
      count = g_dwDestTVert;
      local_14[0] = (float)((g_dwDestIVert - 4) + PUN(int,(float)fVar7) * 4);
      pfVar8 = pfVar15 + PUN(int,(float)fVar7) * 3 + -3;
      iVar10 = g_dwDestTVert - 8;
      local_18 = g_dwDestIVert;
      pfVar14 = (float *)g_dwSourceVert;
      g_dwDestTVert = uVar17;
      g_dwDestVert = g_dwSourceVert;
      g_dwDestIVert = uVar9;
      if (0 < PUN(int,(float)fVar7)) {
        pfVar19 = pfVar15 + 1;
        pfVar12 = (float *)(iVar10 + PUN(int,(float)fVar7) * 8);
        iVar10 = 0;
        g_dwSourceVert = (uint)pfVar15;
        local_4 = fVar7;
        do {
          iVar18 = iVar10;
          if ((pfVar8[1] <= PUN(float,frustum[2])) || (*pfVar19 <= PUN(float,frustum[2]))) {
            if (((pfVar8[1] != PUN(float,frustum[2])) && (*pfVar19 != PUN(float,frustum[2]))) &&
               ((PUN(float,frustum[2]) < pfVar8[1] || (PUN(float,frustum[2]) < *pfVar19)))) {
              iVar18 = iVar10 + 0xc;
              fVar11 = PUN(float,(PUN(int,(float)fVar11) + 1));
              fVar7 = (PUN(float,frustum[2]) - pfVar8[1]) / (*pfVar19 - pfVar8[1]);
              *(int *)((int)pfVar14 + iVar10 + 4) = frustum[2];
              *(float *)((g_dwDestVert - 4) + iVar18) = (pfVar19[1] - pfVar8[2]) * fVar7 + pfVar8[2]
              ;
              *(float *)((g_dwDestVert - 0xc) + iVar18) = (pfVar19[-1] - *pfVar8) * fVar7 + *pfVar8;
              *(float *)((g_dwDestTVert - 8) + PUN(int,(float)fVar11) * 8) =
                   (*(float *)count - *pfVar12) * fVar7 + *pfVar12;
              *(float *)((g_dwDestTVert - 4) + PUN(int,(float)fVar11) * 8) =
                   (*(float *)(count + 4) - pfVar12[1]) * fVar7 + pfVar12[1];
              *(float *)((g_dwDestIVert - 4) + PUN(int,(float)fVar11) * 4) =
                   (*(float *)local_18 - *PUN(float *,(float)local_14[0])) * fVar7 + *PUN(float *,(float)local_14[0]);
              g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 2;
              pfVar14 = (float *)g_dwDestVert;
            }
            if (*pfVar19 <= PUN(float,frustum[2])) {
              pfVar14 = (float *)((int)pfVar14 + iVar18);
              fVar11 = PUN(float,(PUN(int,(float)fVar11) + 1));
              iVar18 = iVar18 + 0xc;
              *pfVar14 = pfVar19[-1];
              pfVar14[1] = *pfVar19;
              pfVar14[2] = pfVar19[1];
              *(undefined4 *)((g_dwDestTVert - 8) + PUN(int,(float)fVar11) * 8) = *(undefined4 *)count;
              *(undefined4 *)((g_dwDestTVert - 4) + PUN(int,(float)fVar11) * 8) = *(undefined4 *)(count + 4);
              *(undefined4 *)((g_dwDestIVert - 4) + PUN(int,(float)fVar11) * 4) = *(undefined4 *)local_18;
              pfVar14 = (float *)g_dwDestVert;
            }
          }
          pfVar8 = pfVar19 + -1;
          local_14[0] = PUN(float,local_18);
          local_18 = local_18 + 4;
          pfVar19 = pfVar19 + 3;
          local_4 = PUN(float,(PUN(int,(float)local_4) + -1));
          pfVar12 = (float *)count;
          iVar10 = iVar18;
          pfVar15 = (float *)g_dwSourceVert;
          count = count + 8;
        } while (local_4 != 0.0f);
      }
      g_dwSourceVert = (uint)pfVar15;
      if (PUN(int,(float)fVar11) < 3) {
        return PUN(uint,(float)fVar11);
      }
    }
    if (pfVar14 != verts) {
      for (uVar9 = PUN(int,(float)fVar11) * 3 & 0x3fffffff; uVar9 != 0; uVar9 = uVar9 - 1) {
        *verts = *pfVar14;
        pfVar14 = pfVar14 + 1;
        verts = verts + 1;
      }
      for (iVar10 = 0; iVar10 != 0; iVar10 = iVar10 + -1) {
        *(undefined1 *)verts = *(undefined1 *)pfVar14;
        pfVar14 = (float *)((int)pfVar14 + 1);
        verts = (float *)((int)verts + 1);
      }
      pfVar14 = (float *)g_dwDestTVert;
      for (iVar10 = (PUN(uint,(float)fVar11) & 0x1fffffff) << 1; iVar10 != 0; iVar10 = iVar10 + -1) {
        *tverts = *pfVar14;
        pfVar14 = pfVar14 + 1;
        tverts = tverts + 1;
      }
      for (iVar10 = 0; fVar7 = fVar11, puVar13 = (uint *)g_dwDestIVert, iVar10 != 0;
          iVar10 = iVar10 + -1) {
        *(undefined1 *)tverts = *(undefined1 *)pfVar14;
        pfVar14 = (float *)((int)pfVar14 + 1);
        tverts = (float *)((int)tverts + 1);
      }
      for (; fVar7 != 0.0f; fVar7 = PUN(float,(PUN(int,(float)fVar7) - 1))) {
        *ivert = *puVar13;
        puVar13 = puVar13 + 1;
        ivert = ivert + 1;
      }
    }
  }
  return PUN(uint,(float)fVar11);
}
#undef local_14
#undef local_4
#undef local_c

#endif


/* ---- 0x0044da40  rdClip_Face3GTOrtho ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdClip_Face3GTOrtho (the remaster's GrimFandango (Linux): the matching branch of
   the rdPrimit3_ClipFace switch (geometry/lighting mode, perspective or ortho camera)); was
   rdClip_Face3_PosUvLitFlags. */

uint __cdecl rdClip_Face3GTOrtho(int *frustum,float *verts,uint *tverts,uint *ivert,uint count)

{
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
  uint *puVar16;
  int iVar17;
  int iVar18;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  g_dwSourceIVert = (uint)ivert;
  g_dwSourceVert = (uint)verts;
  uVar7 = 0;
  puVar12 = &g_dwWorkVerts;
  local_c = (uint)(ivert + (count - 1));
  local_10 = (uint)tverts;
  local_14 = (uint)ivert;
  g_dwRdClip_faceStatus = 0;
  g_dwDestVert = (uint)&g_dwWorkVerts;
  g_dwSourceTVert = (uint)tverts;
  g_dwDestTVert = (uint)&g_dwWorkTVerts;
  g_dwDestIVert = (uint)&g_dwWorkIVerts;
  if (0 < (int)count) {
    iVar17 = 0;
    pfVar13 = verts + count * 3 + -3;
    pfVar15 = verts;
    pfVar5 = (float *)(tverts + count * 2 + -2);
    do {
      fVar2 = PUN(float,frustum[3]);
      fVar1 = PUN(float,frustum[3]);
      if ((fVar2 <= *pfVar13) || (fVar1 <= *pfVar15)) {
        if (((*pfVar13 != fVar2) && (fVar1 != *pfVar15)) &&
           ((*pfVar13 < fVar2 || (*pfVar15 < fVar1)))) {
          fVar3 = (fVar2 - *pfVar13) / (*pfVar15 - *pfVar13);
          iVar18 = iVar17 + 0xc;
          uVar7 = uVar7 + 1;
          *(float *)((int)puVar12 + iVar17) = fVar2;
          *(float *)((g_dwDestVert - 8) + iVar18) = (pfVar15[1] - pfVar13[1]) * fVar3 + pfVar13[1];
          *(float *)((g_dwDestVert - 4) + iVar18) = (pfVar15[2] - pfVar13[2]) * fVar3 + pfVar13[2];
          *(float *)((g_dwDestTVert - 8) + uVar7 * 8) =
               (*(float *)local_10 - *pfVar5) * fVar3 + *pfVar5;
          *(float *)((g_dwDestTVert - 4) + uVar7 * 8) =
               (*(float *)(local_10 + 4) - pfVar5[1]) * fVar3 + pfVar5[1];
          *(float *)((g_dwDestIVert - 4) + uVar7 * 4) =
               (*(float *)local_14 - *(float *)local_c) * fVar3 + *(float *)local_c;
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x10;
          puVar12 = (uint *)g_dwDestVert;
          iVar17 = iVar18;
        }
        if (fVar1 <= *pfVar15) {
          pfVar13 = (float *)((int)puVar12 + iVar17);
          uVar7 = uVar7 + 1;
          iVar17 = iVar17 + 0xc;
          *pfVar13 = *pfVar15;
          pfVar13[1] = pfVar15[1];
          pfVar13[2] = pfVar15[2];
          *(undefined4 *)((g_dwDestTVert - 8) + uVar7 * 8) = *(undefined4 *)local_10;
          *(undefined4 *)((g_dwDestTVert - 4) + uVar7 * 8) = *(undefined4 *)(local_10 + 4);
          *(undefined4 *)((g_dwDestIVert - 4) + uVar7 * 4) = *(undefined4 *)local_14;
          puVar12 = (uint *)g_dwDestVert;
        }
      }
      local_c = local_14;
      local_14 = local_14 + 4;
      count = count - 1;
      pfVar13 = pfVar15;
      pfVar15 = pfVar15 + 3;
      pfVar5 = (float *)local_10;
      local_10 = local_10 + 8;
    } while (count != 0);
  }
  uVar4 = g_dwSourceTVert;
  uVar6 = g_dwSourceIVert;
  if (2 < (int)uVar7) {
    iVar17 = g_dwDestTVert - 8;
    local_c = (g_dwDestIVert - 4) + uVar7 * 4;
    uVar9 = 0;
    g_dwSourceTVert = g_dwDestTVert;
    g_dwSourceIVert = g_dwDestIVert;
    local_10 = g_dwDestTVert;
    local_14 = g_dwDestIVert;
    uVar8 = g_dwSourceVert;
    g_dwDestTVert = uVar4;
    g_dwDestVert = g_dwSourceVert;
    g_dwDestIVert = uVar6;
    pfVar13 = (float *)puVar12;
    if (0 < (int)uVar7) {
      iVar18 = 0;
      pfVar15 = (float *)(puVar12 + uVar7 * 3 + -3);
      pfVar5 = (float *)(iVar17 + uVar7 * 8);
      g_dwSourceVert = (uint)puVar12;
      count = uVar7;
      do {
        fVar2 = PUN(float,frustum[5]);
        fVar1 = PUN(float,frustum[5]);
        if ((*pfVar15 <= fVar2) || (PUN(float,*puVar12) <= fVar1)) {
          if (((*pfVar15 != fVar2) && (fVar1 != PUN(float,*puVar12))) &&
             ((fVar2 < *pfVar15 || (fVar1 < PUN(float,*puVar12))))) {
            fVar3 = (fVar2 - *pfVar15) / (PUN(float,*puVar12) - *pfVar15);
            iVar18 = iVar18 + 0xc;
            uVar9 = uVar9 + 1;
            *(float *)((uVar8 - 0xc) + iVar18) = fVar2;
            *(float *)((g_dwDestVert - 8) + iVar18) =
                 (PUN(float,puVar12[1]) - pfVar15[1]) * fVar3 + pfVar15[1];
            *(float *)((g_dwDestVert - 4) + iVar18) =
                 (PUN(float,puVar12[2]) - pfVar15[2]) * fVar3 + pfVar15[2];
            *(float *)((g_dwDestTVert - 8) + uVar9 * 8) =
                 (*(float *)local_10 - *pfVar5) * fVar3 + *pfVar5;
            *(float *)((g_dwDestTVert - 4) + uVar9 * 8) =
                 (*(float *)(local_10 + 4) - pfVar5[1]) * fVar3 + pfVar5[1];
            *(float *)((g_dwDestIVert - 4) + uVar9 * 4) =
                 (*(float *)local_14 - *(float *)local_c) * fVar3 + *(float *)local_c;
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x20;
            uVar8 = g_dwDestVert;
          }
          if (PUN(float,*puVar12) <= fVar1) {
            pfVar13 = (float *)(uVar8 + iVar18);
            uVar9 = uVar9 + 1;
            iVar18 = iVar18 + 0xc;
            *pfVar13 = PUN(float,*puVar12);
            pfVar13[1] = PUN(float,puVar12[1]);
            pfVar13[2] = PUN(float,puVar12[2]);
            *(undefined4 *)((g_dwDestTVert - 8) + uVar9 * 8) = *(undefined4 *)local_10;
            *(undefined4 *)((g_dwDestTVert - 4) + uVar9 * 8) = *(undefined4 *)(local_10 + 4);
            *(undefined4 *)((g_dwDestIVert - 4) + uVar9 * 4) = *(undefined4 *)local_14;
            uVar8 = g_dwDestVert;
          }
        }
        local_c = local_14;
        local_14 = local_14 + 4;
        count = count - 1;
        pfVar15 = (float *)puVar12;
        puVar12 = puVar12 + 3;
        pfVar5 = (float *)local_10;
        pfVar13 = (float *)g_dwSourceVert;
        local_10 = local_10 + 8;
      } while (count != 0);
    }
    g_dwSourceVert = (uint)pfVar13;
    uVar4 = g_dwSourceTVert;
    uVar6 = g_dwSourceIVert;
    if ((int)uVar9 < 3) {
      return uVar9;
    }
    pfVar13 = (float *)((uVar8 - 0xc) + uVar9 * 0xc);
    iVar17 = g_dwDestTVert - 8;
    local_c = (g_dwDestIVert - 4) + uVar9 * 4;
    uVar7 = 0;
    g_dwDestVert = g_dwSourceVert;
    g_dwSourceTVert = g_dwDestTVert;
    g_dwSourceIVert = g_dwDestIVert;
    local_10 = g_dwDestTVert;
    local_14 = g_dwDestIVert;
    uVar14 = g_dwSourceVert;
    g_dwDestTVert = uVar4;
    g_dwDestIVert = uVar6;
    if (0 < (int)uVar9) {
      iVar18 = 0;
      pfVar15 = (float *)(uVar8 + 8);
      pfVar5 = (float *)(iVar17 + uVar9 * 8);
      g_dwSourceVert = uVar8;
      count = uVar9;
      do {
        fVar2 = PUN(float,frustum[4]);
        fVar1 = PUN(float,frustum[4]);
        if ((pfVar13[2] <= fVar2) || (*pfVar15 <= fVar1)) {
          if (((pfVar13[2] != fVar2) && (fVar1 != *pfVar15)) &&
             ((fVar2 < pfVar13[2] || (fVar1 < *pfVar15)))) {
            fVar3 = (fVar2 - pfVar13[2]) / (*pfVar15 - pfVar13[2]);
            iVar18 = iVar18 + 0xc;
            uVar7 = uVar7 + 1;
            *(float *)((uVar14 - 0xc) + iVar18) = (pfVar15[-2] - *pfVar13) * fVar3 + *pfVar13;
            *(float *)((g_dwDestVert - 8) + iVar18) =
                 (pfVar15[-1] - pfVar13[1]) * fVar3 + pfVar13[1];
            *(float *)((g_dwDestVert - 4) + iVar18) = fVar2;
            *(float *)((g_dwDestTVert - 8) + uVar7 * 8) =
                 (*(float *)local_10 - *pfVar5) * fVar3 + *pfVar5;
            *(float *)((g_dwDestTVert - 4) + uVar7 * 8) =
                 (*(float *)(local_10 + 4) - pfVar5[1]) * fVar3 + pfVar5[1];
            *(float *)((g_dwDestIVert - 4) + uVar7 * 4) =
                 (*(float *)local_14 - *(float *)local_c) * fVar3 + *(float *)local_c;
            g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 4;
            uVar14 = g_dwDestVert;
          }
          if (*pfVar15 <= fVar1) {
            pfVar13 = (float *)(uVar14 + iVar18);
            uVar7 = uVar7 + 1;
            iVar18 = iVar18 + 0xc;
            *pfVar13 = pfVar15[-2];
            pfVar13[1] = pfVar15[-1];
            pfVar13[2] = *pfVar15;
            *(undefined4 *)((g_dwDestTVert - 8) + uVar7 * 8) = *(undefined4 *)local_10;
            *(undefined4 *)((g_dwDestTVert - 4) + uVar7 * 8) = *(undefined4 *)(local_10 + 4);
            *(undefined4 *)((g_dwDestIVert - 4) + uVar7 * 4) = *(undefined4 *)local_14;
            uVar14 = g_dwDestVert;
          }
        }
        pfVar13 = pfVar15 + -2;
        local_c = local_14;
        local_14 = local_14 + 4;
        pfVar15 = pfVar15 + 3;
        count = count - 1;
        pfVar5 = (float *)local_10;
        uVar8 = g_dwSourceVert;
        local_10 = local_10 + 8;
      } while (count != 0);
    }
    g_dwSourceVert = uVar8;
    uVar4 = g_dwSourceTVert;
    uVar6 = g_dwSourceIVert;
    if (2 < (int)uVar7) {
      g_dwDestVert = g_dwSourceVert;
      uVar8 = 0;
      g_dwSourceTVert = g_dwDestTVert;
      g_dwSourceIVert = g_dwDestIVert;
      local_10 = g_dwDestTVert;
      local_14 = g_dwDestIVert;
      pfVar13 = (float *)((uVar14 - 0xc) + uVar7 * 0xc);
      iVar17 = g_dwDestTVert - 8;
      local_c = (g_dwDestIVert - 4) + uVar7 * 4;
      uVar9 = g_dwSourceVert;
      g_dwDestTVert = uVar4;
      g_dwDestIVert = uVar6;
      if (0 < (int)uVar7) {
        iVar18 = 0;
        pfVar15 = (float *)(uVar14 + 8);
        pfVar5 = (float *)(iVar17 + uVar7 * 8);
        g_dwSourceVert = uVar14;
        count = uVar7;
        do {
          fVar2 = PUN(float,frustum[6]);
          fVar1 = PUN(float,frustum[6]);
          if ((fVar2 <= pfVar13[2]) || (fVar1 <= *pfVar15)) {
            if (((pfVar13[2] != fVar2) && (fVar1 != *pfVar15)) &&
               ((pfVar13[2] < fVar2 || (*pfVar15 < fVar1)))) {
              fVar3 = (fVar2 - pfVar13[2]) / (*pfVar15 - pfVar13[2]);
              iVar18 = iVar18 + 0xc;
              uVar8 = uVar8 + 1;
              *(float *)((uVar9 - 0xc) + iVar18) = (pfVar15[-2] - *pfVar13) * fVar3 + *pfVar13;
              *(float *)((g_dwDestVert - 8) + iVar18) =
                   (pfVar15[-1] - pfVar13[1]) * fVar3 + pfVar13[1];
              *(float *)((g_dwDestVert - 4) + iVar18) = fVar2;
              *(float *)((g_dwDestTVert - 8) + uVar8 * 8) =
                   (*(float *)local_10 - *pfVar5) * fVar3 + *pfVar5;
              *(float *)((g_dwDestTVert - 4) + uVar8 * 8) =
                   (*(float *)(local_10 + 4) - pfVar5[1]) * fVar3 + pfVar5[1];
              *(float *)((g_dwDestIVert - 4) + uVar8 * 4) =
                   (*(float *)local_14 - *(float *)local_c) * fVar3 + *(float *)local_c;
              g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 8;
              uVar9 = g_dwDestVert;
            }
            if (fVar1 <= *pfVar15) {
              pfVar13 = (float *)(uVar9 + iVar18);
              uVar8 = uVar8 + 1;
              iVar18 = iVar18 + 0xc;
              *pfVar13 = pfVar15[-2];
              pfVar13[1] = pfVar15[-1];
              pfVar13[2] = *pfVar15;
              *(undefined4 *)((g_dwDestTVert - 8) + uVar8 * 8) = *(undefined4 *)local_10;
              *(undefined4 *)((g_dwDestTVert - 4) + uVar8 * 8) = *(undefined4 *)(local_10 + 4);
              *(undefined4 *)((g_dwDestIVert - 4) + uVar8 * 4) = *(undefined4 *)local_14;
              uVar9 = g_dwDestVert;
            }
          }
          pfVar13 = pfVar15 + -2;
          local_c = local_14;
          local_14 = local_14 + 4;
          pfVar15 = pfVar15 + 3;
          count = count - 1;
          pfVar5 = (float *)local_10;
          uVar14 = g_dwSourceVert;
          local_10 = local_10 + 8;
        } while (count != 0);
      }
      g_dwSourceVert = uVar14;
      uVar7 = uVar8;
      uVar4 = g_dwSourceTVert;
      uVar6 = g_dwSourceIVert;
      if (2 < (int)uVar7) {
        g_dwDestVert = g_dwSourceVert;
        uVar8 = 0;
        g_dwSourceTVert = g_dwDestTVert;
        g_dwSourceIVert = g_dwDestIVert;
        local_10 = g_dwDestTVert;
        local_14 = g_dwDestIVert;
        pfVar13 = (float *)((uVar9 - 0xc) + uVar7 * 0xc);
        iVar17 = g_dwDestTVert - 8;
        local_c = (g_dwDestIVert - 4) + uVar7 * 4;
        pfVar15 = (float *)g_dwSourceVert;
        g_dwDestTVert = uVar4;
        g_dwDestIVert = uVar6;
        if (0 < (int)uVar7) {
          iVar18 = 0;
          pfVar5 = (float *)(uVar9 + 4);
          pfVar11 = (float *)(iVar17 + uVar7 * 8);
          g_dwSourceVert = uVar9;
          count = uVar7;
          do {
            if ((PUN(float,frustum[1]) <= pfVar13[1]) || (PUN(float,frustum[1]) <= *pfVar5)) {
              if (((pfVar13[1] != PUN(float,frustum[1])) && (*pfVar5 != PUN(float,frustum[1]))) &&
                 ((pfVar13[1] < PUN(float,frustum[1]) || (*pfVar5 < PUN(float,frustum[1]))))) {
                iVar17 = iVar18 + 0xc;
                uVar8 = uVar8 + 1;
                fVar1 = (PUN(float,frustum[1]) - pfVar13[1]) / (*pfVar5 - pfVar13[1]);
                *(int *)((int)pfVar15 + iVar18 + 4) = frustum[1];
                *(float *)((g_dwDestVert - 4) + iVar17) =
                     (pfVar5[1] - pfVar13[2]) * fVar1 + pfVar13[2];
                *(float *)((g_dwDestVert - 0xc) + iVar17) =
                     (pfVar5[-1] - *pfVar13) * fVar1 + *pfVar13;
                *(float *)((g_dwDestTVert - 8) + uVar8 * 8) =
                     (*(float *)local_10 - *pfVar11) * fVar1 + *pfVar11;
                *(float *)((g_dwDestTVert - 4) + uVar8 * 8) =
                     (*(float *)(local_10 + 4) - pfVar11[1]) * fVar1 + pfVar11[1];
                *(float *)((g_dwDestIVert - 4) + uVar8 * 4) =
                     (*(float *)local_14 - *(float *)local_c) * fVar1 + *(float *)local_c;
                g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 1;
                pfVar15 = (float *)g_dwDestVert;
                iVar18 = iVar17;
              }
              if (PUN(float,frustum[1]) <= *pfVar5) {
                pfVar15 = (float *)((int)pfVar15 + iVar18);
                uVar8 = uVar8 + 1;
                iVar18 = iVar18 + 0xc;
                *pfVar15 = pfVar5[-1];
                pfVar15[1] = *pfVar5;
                pfVar15[2] = pfVar5[1];
                *(undefined4 *)((g_dwDestTVert - 8) + uVar8 * 8) = *(undefined4 *)local_10;
                *(undefined4 *)((g_dwDestTVert - 4) + uVar8 * 8) = *(undefined4 *)(local_10 + 4);
                *(undefined4 *)((g_dwDestIVert - 4) + uVar8 * 4) = *(undefined4 *)local_14;
                pfVar15 = (float *)g_dwDestVert;
              }
            }
            pfVar13 = pfVar5 + -1;
            local_c = local_14;
            local_14 = local_14 + 4;
            pfVar5 = pfVar5 + 3;
            count = count - 1;
            pfVar11 = (float *)local_10;
            uVar9 = g_dwSourceVert;
            local_10 = local_10 + 8;
          } while (count != 0);
        }
        g_dwSourceVert = uVar9;
        uVar4 = g_dwSourceTVert;
        uVar6 = g_dwSourceIVert;
        if ((int)uVar8 < 3) {
          g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 0x40;
          return uVar8;
        }
        uVar7 = uVar8;
        pfVar13 = pfVar15;
        if (*frustum != 0) {
          g_dwDestVert = g_dwSourceVert;
          g_dwSourceIVert = g_dwDestIVert;
          local_14 = g_dwDestIVert;
          uVar7 = 0;
          g_dwSourceTVert = g_dwDestTVert;
          local_10 = g_dwDestTVert;
          pfVar5 = pfVar15 + uVar8 * 3 + -3;
          iVar17 = g_dwDestTVert - 8;
          local_c = (g_dwDestIVert - 4) + uVar8 * 4;
          pfVar13 = (float *)g_dwSourceVert;
          g_dwDestTVert = uVar4;
          g_dwDestIVert = uVar6;
          if (0 < (int)uVar8) {
            iVar18 = 0;
            pfVar10 = pfVar15 + 1;
            pfVar11 = (float *)(iVar17 + uVar8 * 8);
            g_dwSourceVert = (uint)pfVar15;
            count = uVar8;
            do {
              if ((pfVar5[1] <= PUN(float,frustum[2])) || (*pfVar10 <= PUN(float,frustum[2]))) {
                if (((pfVar5[1] != PUN(float,frustum[2])) && (*pfVar10 != PUN(float,frustum[2]))) &&
                   ((PUN(float,frustum[2]) < pfVar5[1] || (PUN(float,frustum[2]) < *pfVar10)))) {
                  iVar17 = iVar18 + 0xc;
                  uVar7 = uVar7 + 1;
                  fVar1 = (PUN(float,frustum[2]) - pfVar5[1]) / (*pfVar10 - pfVar5[1]);
                  *(int *)((int)pfVar13 + iVar18 + 4) = frustum[2];
                  *(float *)((g_dwDestVert - 4) + iVar17) =
                       (pfVar10[1] - pfVar5[2]) * fVar1 + pfVar5[2];
                  *(float *)((g_dwDestVert - 0xc) + iVar17) =
                       (pfVar10[-1] - *pfVar5) * fVar1 + *pfVar5;
                  *(float *)((g_dwDestTVert - 8) + uVar7 * 8) =
                       (*(float *)local_10 - *pfVar11) * fVar1 + *pfVar11;
                  *(float *)((g_dwDestTVert - 4) + uVar7 * 8) =
                       (*(float *)(local_10 + 4) - pfVar11[1]) * fVar1 + pfVar11[1];
                  *(float *)((g_dwDestIVert - 4) + uVar7 * 4) =
                       (*(float *)local_14 - *(float *)local_c) * fVar1 + *(float *)local_c;
                  g_dwRdClip_faceStatus = g_dwRdClip_faceStatus | 2;
                  pfVar13 = (float *)g_dwDestVert;
                  iVar18 = iVar17;
                }
                if (*pfVar10 <= PUN(float,frustum[2])) {
                  pfVar13 = (float *)((int)pfVar13 + iVar18);
                  uVar7 = uVar7 + 1;
                  iVar18 = iVar18 + 0xc;
                  *pfVar13 = pfVar10[-1];
                  pfVar13[1] = *pfVar10;
                  pfVar13[2] = pfVar10[1];
                  *(undefined4 *)((g_dwDestTVert - 8) + uVar7 * 8) = *(undefined4 *)local_10;
                  *(undefined4 *)((g_dwDestTVert - 4) + uVar7 * 8) = *(undefined4 *)(local_10 + 4);
                  *(undefined4 *)((g_dwDestIVert - 4) + uVar7 * 4) = *(undefined4 *)local_14;
                  pfVar13 = (float *)g_dwDestVert;
                }
              }
              pfVar5 = pfVar10 + -1;
              local_c = local_14;
              local_14 = local_14 + 4;
              pfVar10 = pfVar10 + 3;
              count = count - 1;
              pfVar11 = (float *)local_10;
              pfVar15 = (float *)g_dwSourceVert;
              local_10 = local_10 + 8;
            } while (count != 0);
          }
          g_dwSourceVert = (uint)pfVar15;
          if ((int)uVar7 < 3) {
            return uVar7;
          }
        }
        if (pfVar13 != verts) {
          for (uVar6 = uVar7 * 3 & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1) {
            *verts = *pfVar13;
            pfVar13 = pfVar13 + 1;
            verts = verts + 1;
          }
          for (iVar17 = 0; iVar17 != 0; iVar17 = iVar17 + -1) {
            *(undefined1 *)verts = *(undefined1 *)pfVar13;
            pfVar13 = (float *)((int)pfVar13 + 1);
            verts = (float *)((int)verts + 1);
          }
          puVar12 = (uint *)g_dwDestTVert;
          for (iVar17 = (uVar7 & 0x1fffffff) << 1; iVar17 != 0; iVar17 = iVar17 + -1) {
            *tverts = *puVar12;
            puVar12 = puVar12 + 1;
            tverts = tverts + 1;
          }
          for (iVar17 = 0; uVar6 = uVar7, puVar16 = (uint *)g_dwDestIVert, iVar17 != 0;
              iVar17 = iVar17 + -1) {
            *(char *)tverts = (char)*puVar12;
            puVar12 = (uint *)((int)puVar12 + 1);
            tverts = (uint *)((int)tverts + 1);
          }
          for (; uVar6 != 0; uVar6 = uVar6 - 1) {
            *ivert = *puVar16;
            puVar16 = puVar16 + 1;
            ivert = ivert + 1;
          }
        }
      }
    }
  }
  return uVar7;
}
#endif



/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned int grim_def_g_dwDestIVert __asm__("_g_dwDestIVert");
extern unsigned int grim_def_g_dwDestTVert __asm__("_g_dwDestTVert");
extern unsigned int grim_def_g_dwDestVert __asm__("_g_dwDestVert");
extern unsigned int grim_def_g_dwRdClip_faceStatus __asm__("_g_dwRdClip_faceStatus");
extern unsigned int grim_def_g_dwSourceIVert __asm__("_g_dwSourceIVert");
extern unsigned int grim_def_g_dwSourceTVert __asm__("_g_dwSourceTVert");
extern unsigned int grim_def_g_dwSourceVert __asm__("_g_dwSourceVert");
/* 0x007f4618, 4 bytes */ GRIM_DATA("007f4618") unsigned int grim_def_g_dwSourceIVert __asm__("_g_dwSourceIVert") = 0x0;
/* 0x007f461c, 140 bytes */ GRIM_DATA("007f461c") unsigned int grim_def_g_dwSourceTVert __asm__("_g_dwSourceTVert") = 0x0;
/* 0x007f4620, 136 bytes: the rest of grim_def_g_dwSourceTVert's span */ GRIM_DATA("007f461c") static unsigned char g_dwSourceTVert__tail[136] __attribute__((used)) = {0};
/* 0x007f46a8, 4 bytes */ GRIM_DATA("007f46a8") unsigned int grim_def_g_dwDestTVert __asm__("_g_dwDestTVert") = 0x0;
/* 0x007f46ac, 4 bytes */ GRIM_DATA("007f46ac") unsigned int grim_def_g_dwDestVert __asm__("_g_dwDestVert") = 0x0;
/* 0x007f46b0, 8 bytes */ GRIM_DATA("007f46b0") unsigned int grim_def_g_dwDestIVert __asm__("_g_dwDestIVert") = 0x0;
/* 0x007f46b4, 4 bytes: the rest of grim_def_g_dwDestIVert's span */ GRIM_DATA("007f46b0") static unsigned char g_dwDestIVert__tail[4] __attribute__((used)) = {0};
/* 0x007f47b8, 8 bytes */ GRIM_DATA("007f47b8") unsigned int grim_def_g_dwSourceVert __asm__("_g_dwSourceVert") = 0x0;
/* 0x007f47bc, 4 bytes: the rest of grim_def_g_dwSourceVert's span */ GRIM_DATA("007f47b8") static unsigned char g_dwSourceVert__tail[4] __attribute__((used)) = {0};
/* 0x007f4ac4, 4 bytes */ GRIM_DATA("007f4ac4") unsigned int grim_def_g_dwRdClip_faceStatus __asm__("_g_dwRdClip_faceStatus") = 0x0;
