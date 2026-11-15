/* GRIMFANDANGO.EXE :: math3d.c
 * functions 0x00446880 .. 0x00450410 (36 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00446880  rdVector_Dot2 ---- */
/* Original name rdVector_Dot2 (the remaster's GrimFandango (Linux): same body (a.x * b.x + a.y *
   b.y: the 2D dot product)); was Vec3_Dot. */

float __cdecl rdVector_Dot2(float *a,float *b)

{
  return *a * *b + a[1] * b[1];
}

/* ---- 0x004468a0  rdVector_Dot3 ---- */
/* Original name rdVector_Dot3 (the remaster's GrimFandango (Linux): aligned call in Intersection);
   was Vec3_Dot2. */

float __cdecl rdVector_Dot3(float *a,float *b)

{
  return *a * *b + b[2] * a[2] + a[1] * b[1];
}

/* ---- 0x004468d0  rdVector_Cross3 ---- */
/* Original name rdVector_Cross3 (the remaster's GrimFandango (Linux): same body (out = a x b)); was
   Vec3_Cross. */

void __cdecl rdVector_Cross3(float *out,float *a,float *b)

{
  *out = a[1] * b[2] - a[2] * b[1];
  out[1] = a[2] * *b - b[2] * *a;
  out[2] = b[1] * *a - a[1] * *b;
  return;
}

/* ---- 0x00446920  rdVector_Normalize3 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdVector_Normalize3 (the remaster's GrimFandango (Linux): same body (out = v / |v|,
   or a copy of v when the length is 0); the remaster returns the length); was Vec3_NormalizeTo. */

void __cdecl rdVector_Normalize3(float *out,float *v)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  fVar1 = SQRT(*v * *v + v[2] * v[2] + v[1] * v[1]);
  if (fVar1 != 0.0f) {
    *out = *v / fVar1;
    out[1] = v[1] / fVar1;
    out[2] = v[2] / fVar1;
    return;
  }
  *out = *v;
  out[1] = v[1];
  out[2] = v[2];
  return;
}
#undef local_4

#endif


/* ---- 0x004469a0  rdVector_Normalize3Acc ---- */
/* Original name rdVector_Normalize3Acc (the remaster's GrimFandango (Linux): the only unmatched
   callee of rdLight_CalcFaceIntensity; the only unmatched callee of rdLight_CalcVertexIntensities;
   the only unmatched callee of rdModel3_CalcVertexNormals; 11 matched neighbours agree, 0
   disagree); was Vec3_Normalize. */

float __cdecl rdVector_Normalize3Acc(float *v)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  fVar1 = SQRT(*v * *v + v[2] * v[2] + v[1] * v[1]);
  if (fVar1 != 0.0f) {
    fVar2 = 1.0f / fVar1;
    *v = fVar2 * *v;
    v[1] = v[1] * fVar2;
    v[2] = v[2] * fVar2;
  }
  return fVar1;
}
#undef local_4


/* ---- 0x00446a10  rdVector_Normalize3QuickAcc ---- */
/* Rough vector length: with the absolute values sorted max >= mid >= min, len = max + 0.34375 * mid
   + 0.25 * min. Also divides the vector by it (in place, in floats) and returns the length.
   Original name rdVector_Normalize3QuickAcc (the remaster's GrimFandango (Linux): aligned call in
   SetSoundPosition); was Vec3_NormalizeApprox. */

float __cdecl rdVector_Normalize3QuickAcc(float *v)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  #define local_28 (*(float (*)[3])(_frame + (0x40 - 0x28)))
  #define local_1c (*(float (*)[3])(_frame + (0x40 - 0x1c)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float (*)[2])(_frame + (0x40 - 0xc)))
  
  if (0.0f <= *v) {
    local_28[2] = *v;
  }
  else {
    local_28[2] = -*v;
  }
  local_c[0] = local_28[2];
  if (0.0f <= v[1]) {
    local_28[1] = v[1];
  }
  else {
    local_28[1] = -v[1];
  }
  local_c[1] = local_28[1];
  if (0.0f <= v[2]) {
    local_28[0] = v[2];
  }
  else {
    local_28[0] = -v[2];
  }
  local_1c[0] = local_28[0];
  if (local_28[0] <= local_28[1]) {
    if (local_28[2] < local_28[1]) {
      local_c[1] = local_28[2];
      local_c[0] = local_28[1];
      if (local_28[2] < local_28[0]) {
        local_1c[0] = local_28[2];
        local_c[1] = local_28[0];
      }
    }
  }
  else if (local_28[0] <= local_28[2]) {
    local_1c[0] = local_28[1];
    local_c[1] = local_28[0];
  }
  else {
    local_1c[0] = local_28[2];
    local_c[0] = local_28[0];
    if (local_28[1] < local_28[2]) {
      local_1c[0] = local_28[1];
      local_c[1] = local_28[2];
    }
  }
  fVar1 = local_1c[0] * 0.25f + local_c[1] * 0.34375f + local_c[0];
  fVar2 = 1.0f / fVar1;
  *v = *v * fVar2;
  v[1] = v[1] * fVar2;
  v[2] = v[2] * fVar2;
  return fVar1;
}
#undef local_10
#undef local_1c
#undef local_28
#undef local_c


/* ---- 0x00446ba0  rdVector_Rotate3Acc ---- */
/* Lua RotateVector: rotates a vector by pitch/yaw/roll angles Original name rdVector_Rotate3Acc
   (the remaster's GrimFandango (Linux): the only unmatched callee of sputLua_RotateVectorL; 2
   matched neighbours agree, 0 disagree); was Vec3_Rotate. */

void __cdecl rdVector_Rotate3Acc(float *vec,float *rot)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_30 (*(float (*)[12])(_frame + (0x40 - 0x30)))
  
  rdMatrix_BuildRotate34(local_30,(uint *)rot);
  rdMatrix_TransformVector34Acc(vec,local_30);
  return;
}
#undef local_30


/* ---- 0x00446bd0  rdVector_ExtractAngles ---- */
/* Original name rdVector_ExtractAngles (the remaster's GrimFandango (Linux): same body (z = 0, x =
   stdMath_ArcSin3(m[2]), y = stdMath_ArcTan4(m[1], m[0])); called by sputLua_GetLightRotation in
   both builds); was Matrix_GetAngles. */

void __cdecl rdVector_ExtractAngles(float *matrix,float *outAngles)

{
  float fVar1;
  
  outAngles[2] = 0.0f;
  fVar1 = stdMath_ArcSin3(matrix[2]);
  *outAngles = fVar1;
  fVar1 = stdMath_ArcTan4(matrix[1],*matrix);
  outAngles[1] = fVar1;
  return;
}

/* ---- 0x0044e7d0  rdClip_SphereInFrustrum ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdClip_SphereInFrustrum (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_DrawMeshImpl, rdSprite_Draw, rdModel3_Draw); was Frustum_TestSphere. */

uint __cdecl rdClip_SphereInFrustrum(int *frustum,float *center,float radius)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  int iVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pfVar8 = center;
  fVar5 = radius + center[1];
  fVar2 = center[1] - radius;
  if (fVar5 < PUN(float,frustum[1])) {
    return 2;
  }
  bVar4 = PUN(float,frustum[1]) <= fVar2;
  if (*frustum != 0) {
    if (PUN(float,frustum[2]) < fVar2) {
      return 2;
    }
    if (PUN(float,frustum[2]) < fVar5) {
      bVar4 = false;
    }
  }
  fVar6 = radius + center[2];
  fVar7 = center[2] - radius;
  iVar3 = g_pRdCamera_CurCamera->nProjectType;
  if (iVar3 == 1) {
    fVar1 = PUN(float,frustum[7]) * fVar2;
    center = PUN(float *,(float)(PUN(float,frustum[7]) * fVar5));
  }
  else {
    center = (float *)frustum[4];
    fVar1 = PUN(float,frustum[4]);
  }
  if ((fVar1 < fVar7) && (PUN(float,center) < fVar7)) {
    return 2;
  }
  if ((fVar1 < fVar6) || (PUN(float,center) < fVar6)) {
    bVar4 = false;
  }
  if (iVar3 == 1) {
    fVar1 = PUN(float,frustum[8]) * fVar2;
    center = PUN(float *,(float)(PUN(float,frustum[8]) * fVar5));
  }
  else {
    center = (float *)frustum[6];
    fVar1 = PUN(float,frustum[6]);
  }
  if ((fVar6 < fVar1) && (fVar6 < PUN(float,center))) {
    return 2;
  }
  if ((fVar7 < fVar1) || (fVar7 < PUN(float,center))) {
    bVar4 = false;
  }
  fVar7 = radius + *pfVar8;
  fVar6 = *pfVar8 - radius;
  if (iVar3 == 1) {
    fVar1 = PUN(float,frustum[9]) * fVar2;
    radius = PUN(float,frustum[9]) * fVar5;
  }
  else {
    radius = PUN(float,frustum[3]);
    fVar1 = PUN(float,frustum[3]);
  }
  if ((fVar7 < fVar1) && (fVar7 < radius)) {
    return 2;
  }
  if ((fVar6 < fVar1) || (fVar6 < radius)) {
    bVar4 = false;
  }
  if (iVar3 == 1) {
    fVar2 = PUN(float,frustum[10]) * fVar2;
    radius = PUN(float,frustum[10]) * fVar5;
  }
  else {
    radius = PUN(float,frustum[5]);
    fVar2 = PUN(float,frustum[5]);
  }
  if ((fVar2 < fVar6) && (radius < fVar6)) {
    return 2;
  }
  if ((fVar2 < fVar7) || (radius < fVar7)) {
    bVar4 = false;
  }
  return (uint)!bVar4;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x0044ea50  rdClip_FaceToPlane ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdClip_FaceToPlane (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_DrawFace); was Polygon_ClipToPlane. */

uint __cdecl
rdClip_FaceToPlane(float *normal,float *point,float *verts,uint *outFlags,float *outVerts,
                  uint *count)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  uint *puVar9;
  int iVar10;
  float *pfVar11;
  uint *puVar12;
  uint *puVar13;
  uint *puVar14;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  local_c[2] = PUN(float,count);
  puVar5 = outFlags;
  iVar3 = (int)count * 3;
  iVar10 = (int)count * 3;
  iVar4 = (int)count * 3;
  local_20 = 0;
  pfVar6 = (float *)(outFlags + (int)count * 2 + -2);
  if (outFlags == (uint *)0x0) {
    pfVar6 = outVerts;
  }
  if (outVerts != (float *)0x0) {
    local_18[2] = outVerts[(int)count + -1];
  }
  if (0 < (int)count) {
    local_24 = (uint)&g_dwWorkIVerts;
    local_c[1] = PUN(float,outVerts);
    local_c[0] = PUN(float,outFlags);
    count = &g_dwWorkTVerts;
    puVar13 = &g_dwWorkVerts;
    local_1c = (uint)&UINT_007f46bc;
    puVar9 = &UINT_007f48c8;
    puVar14 = &UINT_007f48c4;
    pfVar7 = verts + iVar4 + -3;
    pfVar8 = verts;
    pfVar11 = outVerts;
    local_18[0] = ((verts + iVar4 + -3)[1] - point[1]) * normal[1] +
                  (verts[iVar3 + -1] - point[2]) * normal[2] +
                  (verts[iVar10 + -3] - *point) * *normal;
    do {
      if (outFlags != (uint *)0x0) {
        local_18[1] = local_c[0];
      }
      if (outVerts != (float *)0x0) {
        pfVar11 = *PUN(float **,(float)local_c[1]);
      }
      fVar2 = (pfVar8[1] - point[1]) * normal[1] +
              (*pfVar8 - *point) * *normal + (pfVar8[2] - point[2]) * normal[2];
      if ((local_18[0] < 0.0f) || (fVar2 < 0.0f)) {
        if ((0.0f <= local_18[0]) && (fVar2 < 0.0f)) {
          fVar1 = -(local_18[0] / (fVar2 - local_18[0]));
          *puVar13 = PUN(uint,(float)((*pfVar8 - *pfVar7) * fVar1 + *pfVar7));
          *puVar14 = PUN(uint,(float)((pfVar8[1] - pfVar7[1]) * fVar1 + pfVar7[1]));
          *puVar9 = PUN(uint,(float)((pfVar8[2] - pfVar7[2]) * fVar1 + pfVar7[2]));
          if (outFlags != (uint *)0x0) {
            *count = PUN(uint,(float)((*PUN(float *,(float)local_18[1]) - *pfVar6) * fVar1 + *pfVar6));
            *(float *)local_1c = (*(float *)(PUN(int,(float)local_18[1]) + 4) - pfVar6[1]) * fVar1 + pfVar6[1];
          }
          if (outVerts != (float *)0x0) {
            *(float *)local_24 = (PUN(float,pfVar11) - local_18[2]) * fVar1 + local_18[2];
          }
          goto LAB_0044ed90;
        }
        if ((local_18[0] < 0.0f) && (0.0f <= fVar2)) {
          fVar1 = -(local_18[0] / (fVar2 - local_18[0]));
          *puVar13 = PUN(uint,(float)((*pfVar8 - *pfVar7) * fVar1 + *pfVar7));
          *puVar14 = PUN(uint,(float)((pfVar8[1] - pfVar7[1]) * fVar1 + pfVar7[1]));
          *puVar9 = PUN(uint,(float)((pfVar8[2] - pfVar7[2]) * fVar1 + pfVar7[2]));
          if (outFlags != (uint *)0x0) {
            *count = PUN(uint,(float)((*PUN(float *,(float)local_18[1]) - *pfVar6) * fVar1 + *pfVar6));
            *(float *)local_1c = (*(float *)(PUN(int,(float)local_18[1]) + 4) - pfVar6[1]) * fVar1 + pfVar6[1];
          }
          if (outVerts != (float *)0x0) {
            *(float *)local_24 = (PUN(float,pfVar11) - local_18[2]) * fVar1 + local_18[2];
          }
          local_20 = local_20 + 1;
          local_1c = local_1c + 8;
          puVar12 = count + 2;
          local_24 = local_24 + 4;
          pfVar6 = (float *)(puVar13 + 3);
          puVar14 = puVar14 + 3;
          *pfVar6 = *pfVar8;
          puVar9 = puVar9 + 3;
          puVar13[4] = PUN(uint,(float)pfVar8[1]);
          puVar13[5] = PUN(uint,(float)pfVar8[2]);
          if (outFlags != (uint *)0x0) {
            *puVar12 = *PUN(uint *,(float)local_18[1]);
            count[3] = *(uint *)(PUN(int,(float)local_18[1]) + 4);
            count[4] = *(uint *)(PUN(int,(float)local_18[1]) + 8);
          }
          puVar13 = (uint *)pfVar6;
          count = puVar12;
          if (outVerts != (float *)0x0) {
            *(float **)local_24 = pfVar11;
          }
          goto LAB_0044ed90;
        }
      }
      else {
        *puVar13 = PUN(uint,(float)*pfVar8);
        puVar13[1] = PUN(uint,(float)pfVar8[1]);
        puVar13[2] = PUN(uint,(float)pfVar8[2]);
        if (outFlags != (uint *)0x0) {
          *count = *PUN(uint *,(float)local_18[1]);
          count[1] = *(uint *)(PUN(int,(float)local_18[1]) + 4);
          count[2] = *(uint *)(PUN(int,(float)local_18[1]) + 8);
        }
        if (outVerts != (float *)0x0) {
          *(float **)local_24 = pfVar11;
        }
LAB_0044ed90:
        local_20 = local_20 + 1;
        local_1c = local_1c + 8;
        count = count + 2;
        puVar14 = puVar14 + 3;
        puVar9 = puVar9 + 3;
        puVar13 = puVar13 + 3;
        local_24 = local_24 + 4;
      }
      local_c[0] = PUN(float,(PUN(int,(float)local_c[0]) + 8));
      local_c[1] = PUN(float,(PUN(int,(float)local_c[1]) + 4));
      local_c[2] = PUN(float,(PUN(int,(float)local_c[2]) + -1));
      pfVar7 = pfVar8;
      pfVar8 = pfVar8 + 3;
      pfVar6 = PUN(float *,(float)local_18[1]);
      local_18[0] = fVar2;
      local_18[2] = PUN(float,pfVar11);
    } while (local_c[2] != 0.0f);
  }
  if (0 < (int)local_20) {
    iVar10 = (int)&g_dwWorkVerts - (int)verts;
    iVar3 = -(int)outFlags;
    outFlags = (uint *)local_20;
    pfVar6 = outVerts;
    puVar13 = puVar5;
    do {
      pfVar11 = (float *)(iVar10 + (int)verts);
      *verts = *pfVar11;
      verts[1] = pfVar11[1];
      verts[2] = pfVar11[2];
      if (puVar5 != (uint *)0x0) {
        *puVar13 = *(uint *)((int)&g_dwWorkTVerts + iVar3 + (int)puVar13);
        puVar13[1] = *(uint *)((int)&UINT_007f46bc + iVar3 + (int)puVar13);
      }
      if (outVerts != (float *)0x0) {
        *pfVar6 = *(float *)(((int)&g_dwWorkIVerts - (int)outVerts) + (int)pfVar6);
      }
      verts = verts + 3;
      puVar13 = puVar13 + 2;
      pfVar6 = pfVar6 + 1;
      outFlags = (uint *)((int)outFlags + -1);
    } while (outFlags != (uint *)0x0);
  }
  return local_20;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_c

#endif


/* ---- 0x0044eeb0  rdMatrix_Build34 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdMatrix_Build34 (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_BuildExpandedRadius, rdModel3_CalcModelBoundingBox, rdThing_SetModel3); was
   Angles_ToMatrix. */

void __cdecl rdMatrix_Build34(float *out,uint *angles,float *pos)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  #define local_1c (*(float (*)[3])(_frame + (0x30 - 0x1c)))
  #define local_10 (*(float (*)[3])(_frame + (0x30 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  puVar1 = angles;
  stdMath_SinCos(PUN(float,PUN(float,*angles)),(float *)&angles,local_1c);
  stdMath_SinCos(PUN(float,puVar1[1]),local_1c + 2,local_10);
  stdMath_SinCos(PUN(float,puVar1[2]),local_1c + 1,local_10 + 1);
  *out = -(local_1c[1] * local_1c[2]) * PUN(float,angles) + local_10[1] * local_10[0];
  out[1] = local_1c[1] * local_10[0] * PUN(float,angles) + local_10[1] * local_1c[2];
  out[2] = -local_1c[1] * local_1c[0];
  out[3] = -local_1c[2] * local_1c[0];
  out[4] = local_10[0] * local_1c[0];
  out[5] = PUN(float,angles);
  out[6] = local_10[1] * local_1c[2] * PUN(float,angles) + local_1c[1] * local_10[0];
  out[7] = -PUN(float,angles) * local_10[1] * local_10[0] + local_1c[1] * local_1c[2];
  out[8] = local_10[1] * local_1c[0];
  out[9] = *pos;
  out[10] = pos[1];
  out[0xb] = pos[2];
  return;
}
#undef local_10
#undef local_1c
#undef local_4

#endif


/* ---- 0x0044efd0  rdMatrix_InvertOrtho34 ---- */
/* Rigid inverse of a 3x4 matrix: rotation transposed, translation = -(R^T t). Was misnamed
   Matrix_Transpose. Not a true inverse when the matrix has scale. Original name
   rdMatrix_InvertOrtho34 (the remaster's GrimFandango (Linux): aligned call in rdCamera_Update,
   rdModel3_DrawMeshImpl); was Matrix34_InvertRigid. */

void __cdecl rdMatrix_InvertOrtho34(float *out,float *m)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  out[1] = m[3];
  out[2] = m[6];
  out[5] = m[7];
  out[3] = m[1];
  out[6] = m[2];
  out[7] = m[5];
  *out = *m;
  out[4] = m[4];
  out[8] = m[8];
  fVar1 = m[10];
  fVar2 = m[0xb];
  fVar3 = m[9];
  out[9] = -(fVar3 * *m + m[2] * fVar2 + m[1] * fVar1);
  out[10] = -(m[5] * fVar2 + m[3] * fVar3 + m[4] * fVar1);
  out[0xb] = -(m[7] * fVar1 + m[6] * fVar3 + m[8] * fVar2);
  return;
}

/* ---- 0x0044f080  rdMatrix_BuildRotate34 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdMatrix_BuildRotate34 (the remaster's GrimFandango (Linux): aligned call in
   rdVector_Rotate3Acc, sputActor_SetActorRotation); was Angles_ToMatrixNoPos. */

void __cdecl rdMatrix_BuildRotate34(float *out,uint *angles)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  #define local_1c (*(float (*)[3])(_frame + (0x30 - 0x1c)))
  #define local_10 (*(float (*)[3])(_frame + (0x30 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  puVar1 = angles;
  stdMath_SinCos(PUN(float,PUN(float,*angles)),(float *)&angles,local_1c);
  stdMath_SinCos(PUN(float,puVar1[1]),local_1c + 2,local_10);
  stdMath_SinCos(PUN(float,puVar1[2]),local_1c + 1,local_10 + 1);
  *out = -(local_1c[1] * local_1c[2]) * PUN(float,angles) + local_10[1] * local_10[0];
  out[1] = local_1c[1] * local_10[0] * PUN(float,angles) + local_10[1] * local_1c[2];
  out[2] = -local_1c[1] * local_1c[0];
  out[3] = -local_1c[2] * local_1c[0];
  out[4] = local_10[0] * local_1c[0];
  out[5] = PUN(float,angles);
  out[6] = local_10[1] * local_1c[2] * PUN(float,angles) + local_1c[1] * local_10[0];
  out[7] = -PUN(float,angles) * local_10[1] * local_10[0] + local_1c[1] * local_1c[2];
  out[8] = local_10[1] * local_1c[0];
  out[9] = 0.0f;
  out[10] = 0.0f;
  out[0xb] = 0.0f;
  return;
}
#undef local_10
#undef local_1c
#undef local_4

#endif


/* ---- 0x0044f1a0  rdMatrix_BuildTranslate34 ---- */
/* Identity 3x4 (from g_flRdroid_identMatrix34) with the translation column set Original name
   rdMatrix_BuildTranslate34 (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_BuildExpandedRadius, rdModel3_CalcModelBoundingBox); was Matrix_BuildTranslation. */

void __cdecl rdMatrix_BuildTranslate34(float *m,float *pos)

{
  int iVar1;
  float *pfVar2;
  float *pfVar3;
  
  pfVar2 = g_flRdroid_identMatrix34;
  pfVar3 = m;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar3 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar3 = pfVar3 + 1;
  }
  m[9] = *pos;
  m[10] = pos[1];
  m[0xb] = pos[2];
  return;
}

/* ---- 0x0044f1d0  rdMatrix_BuildScale34 ---- */
/* Original name rdMatrix_BuildScale34 (the remaster's GrimFandango (Linux): aligned call in
   rdMatrix_PreScale34); was Matrix_BuildTranslation2. */

void __cdecl rdMatrix_BuildScale34(undefined4 *out,undefined4 *scale)

{
  *out = *scale;
  out[1] = 0;
  out[2] = 0;
  out[3] = 0;
  out[4] = scale[1];
  out[5] = 0;
  out[6] = 0;
  out[7] = 0;
  out[8] = scale[2];
  out[9] = 0;
  out[10] = 0;
  out[0xb] = 0;
  return;
}

/* ---- 0x0044f210  rdMatrix_BuildFromVectorAngle34 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdMatrix_BuildFromVectorAngle34 (the remaster's GrimFandango (Linux): aligned call
   in Rotate, rdMatrix_LookAt); was Matrix_AxisAngle. */

void __cdecl rdMatrix_BuildFromVectorAngle34(float *out,float *axis,float angle)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  #define local_28 (*(float (*)[3])(_frame + (0x40 - 0x28)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  stdMath_SinCos(angle,local_28,&angle);
  fVar1 = 1.0f - axis[2];
  fVar2 = fVar1;
  if (fVar1 < 0.0f) {
    fVar2 = -fVar1;
  }
  if (fVar2 <= 1e-05f) {
    fVar1 = 0.0f;
  }
  if (fVar1 == 0.0f) {
    *out = angle;
    out[4] = angle;
    out[3] = -local_28[0];
    out[1] = local_28[0];
  }
  else {
    fVar1 = axis[2] - -1.0f;
    fVar2 = fVar1;
    if (fVar1 < 0.0f) {
      fVar2 = -fVar1;
    }
    if (fVar2 <= 1e-05f) {
      fVar1 = 0.0f;
    }
    if (fVar1 != 0.0f) {
      fVar6 = *axis * *axis;
      fVar8 = axis[1] * axis[1];
      fVar7 = fVar6 * angle;
      fVar9 = (1.0f - fVar6) - fVar8;
      fVar10 = fVar8 * angle;
      fVar11 = 1.0f - angle;
      fVar1 = axis[1];
      fVar2 = axis[1];
      fVar3 = *axis;
      fVar4 = axis[2];
      fVar5 = *axis;
      fVar12 = axis[2] * *axis * fVar11;
      fVar13 = axis[1] * axis[2] * fVar11;
      *out = (fVar7 * fVar9 + fVar10) / (1.0f - fVar9) + fVar6;
      fVar11 = fVar1 * fVar3 * fVar11;
      out[9] = 0.0f;
      out[10] = 0.0f;
      out[4] = (fVar10 * fVar9 + fVar7) / (1.0f - fVar9) + fVar8;
      out[8] = fVar10 + fVar7 + fVar9;
      out[1] = fVar4 * local_28[0] + fVar11;
      out[3] = fVar11 - fVar4 * local_28[0];
      out[2] = fVar12 - fVar2 * local_28[0];
      out[5] = fVar13 + local_28[0] * fVar5;
      out[6] = fVar12 + fVar2 * local_28[0];
      out[7] = fVar13 - local_28[0] * fVar5;
      out[0xb] = 0.0f;
      return;
    }
    *out = angle;
    out[4] = angle;
    out[1] = -local_28[0];
    out[3] = local_28[0];
  }
  out[2] = 0.0f;
  out[5] = 0.0f;
  out[6] = 0.0f;
  out[7] = 0.0f;
  out[8] = 1.0f;
  out[9] = 0.0f;
  out[10] = 0.0f;
  out[0xb] = 0.0f;
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_28
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x0044f490  rdMatrix_LookAt ---- */
/* Camera basis from (position, interest, roll) into out[0..11]: out+0 right = normalise(forward x
   rolledUp), out+0xc forward = normalise(interest - position), out+0x18 up = right-forward cross,
   out+0x24 position. The up used is (0,0,1) rolled about the forward by roll with Matrix_AxisAngle
   ((0,1,0) or (-0,-1,-0) when the forward is within 0.999 of vertical). Original name
   rdMatrix_LookAt (the remaster's GrimFandango (Linux): aligned call in sputLua_SetCameraInterestL,
   sputLua_SetCameraPositionL, sputLua_SetCameraRollL); was Camera_BuildBasis. */

void __cdecl rdMatrix_LookAt(float *out,float *from,float *to,uint roll)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *v;
  float fVar1;
  float *v_00;
  #define local_48 (*(float *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(float (*)[2])(_frame + (0x60 - 0x44)))
  #define local_3c (*(float (*)[3])(_frame + (0x60 - 0x3c)))
  #define local_30 (*(float (*)[12])(_frame + (0x60 - 0x30)))
  
  v = out + 3;
  *v = *to - *from;
  out[4] = to[1] - from[1];
  out[5] = to[2] - from[2];
  rdVector_Normalize3Acc(v);
  rdMatrix_BuildFromVectorAngle34(local_30,v,PUN(float,roll));
  fVar1 = *v * 0.0f + out[4] * 0.0f + out[5] * 1.0f;
  if (fVar1 < 0.0f) {
    fVar1 = -fVar1;
  }
  if (fVar1 <= 0.999) {
    v_00 = (float *)&DAT_004d7540;
  }
  else if (out[5] <= 0.0f) {
    v_00 = (float *)&DAT_004d7530;
  }
  else {
    local_3c[0] = -0.0f;
    local_3c[1] = -1.0f;
    v_00 = local_3c;
    local_3c[2] = -0.0f;
  }
  rdMatrix_TransformVector34(&local_48,v_00,local_30);
  *out = out[4] * local_44[1] - out[5] * local_44[0];
  out[1] = out[5] * local_48 - *v * local_44[1];
  out[2] = *v * local_44[0] - out[4] * local_48;
  rdVector_Normalize3Acc(out);
  out[6] = out[5] * out[1] - out[4] * out[2];
  out[7] = out[2] * *v - out[5] * *out;
  out[8] = out[4] * *out - out[1] * *v;
  rdVector_Normalize3Acc(out + 6);
  out[9] = *from;
  out[10] = from[1];
  out[0xb] = from[2];
  return;
}
#undef local_30
#undef local_3c
#undef local_44
#undef local_48


/* ---- 0x0044f650  rdMatrix_ExtractAngles34 ---- */
/* WARNING: Variable defined which should be unmapped: local_28 */
/* Original name rdMatrix_ExtractAngles34 (the remaster's GrimFandango (Linux): aligned call in
   rdCamera_Update); was Matrix_ToAngles. */

void __cdecl rdMatrix_ExtractAngles34(float *m,float *outAngles)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  fVar3 = m[3];
  fVar4 = m[4];
  fVar9 = *m;
  fVar8 = fVar4 * fVar4 + fVar3 * fVar3;
  fVar1 = m[2];
  fVar2 = m[5];
  fVar5 = SQRT(fVar8);
  fVar6 = -m[1];
  if (0.001f <= fVar5) {
    fVar7 = stdMath_ArcSin3(fVar4 / fVar5);
    fVar7 = 90.0f - fVar7;
    if (0.0f < fVar3) {
      fVar7 = -fVar7;
    }
    outAngles[1] = fVar7;
  }
  else {
    fVar7 = stdMath_ArcSin3(--fVar9);
    fVar7 = 90.0f - fVar7;
    if (((0.0f < fVar6) && (0.0f < fVar2)) || ((fVar6 < 0.0f && (fVar2 < 0.0f)))) {
      fVar7 = -fVar7;
    }
    outAngles[2] = fVar7;
    outAngles[1] = 0.0f;
  }
  if (0.001f <= fVar5) {
    fVar8 = fVar8 / fVar5;
    if (fVar8 < 1.0f) {
      fVar8 = stdMath_ArcSin3(fVar8);
      *outAngles = 90.0f - fVar8;
    }
    else {
      *outAngles = 0.0f;
    }
  }
  else {
    *outAngles = 90.0f;
  }
  if (fVar2 < 0.0f) {
    *outAngles = -*outAngles;
  }
  fVar4 = -fVar4;
  if (0.001f <= fVar5) {
    fVar9 = (fVar6 * fVar3 + fVar4 * -fVar9) / SQRT(fVar4 * fVar4 + fVar3 * fVar3);
    if (fVar9 < 1.0f) {
      if (-1.0f < fVar9) {
        fVar9 = stdMath_ArcSin3(fVar9);
        outAngles[2] = 90.0f - fVar9;
      }
      else {
        outAngles[2] = 180.0f;
      }
    }
    else {
      outAngles[2] = 0.0f;
    }
    if (-fVar1 < 0.0f) {
      outAngles[2] = -outAngles[2];
      return;
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_28
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0044f880  rdMatrix_Identity34 ---- */
/* Original name rdMatrix_Identity34 (the remaster's GrimFandango (Linux): the only unmatched callee
   of Actor_Create; 1 matched neighbours agree, 0 disagree); was Matrix_Identity. */

void __cdecl rdMatrix_Identity34(float *m)

{
  int iVar1;
  float *pfVar2;
  
  pfVar2 = g_flRdroid_identMatrix34;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *m = *pfVar2;
    pfVar2 = pfVar2 + 1;
    m = m + 1;
  }
  return;
}

/* ---- 0x0044f8a0  rdMatrix_Multiply34 ---- */
/* 3x4 affine matrix product Original name rdMatrix_Multiply34 (the remaster's GrimFandango (Linux):
   aligned call in rdModel3_BuildExpandedRadius, rdModel3_CalcModelBoundingBox,
   rdModel3_DrawMeshImpl); was Matrix_Mul34. */

void __cdecl rdMatrix_Multiply34(float *out,float *a,float *b)

{
  *out = *a * *b + a[3] * b[1] + b[2] * a[6];
  out[1] = b[2] * a[7] + b[1] * a[4] + a[1] * *b;
  out[2] = b[1] * a[5] + b[2] * a[8] + a[2] * *b;
  out[3] = a[6] * b[5] + a[3] * b[4] + b[3] * *a;
  out[4] = a[1] * b[3] + a[4] * b[4] + a[7] * b[5];
  out[5] = a[2] * b[3] + b[4] * a[5] + a[8] * b[5];
  out[6] = a[3] * b[7] + a[6] * b[8] + b[6] * *a;
  out[7] = a[7] * b[8] + a[4] * b[7] + a[1] * b[6];
  out[8] = a[5] * b[7] + a[2] * b[6] + a[8] * b[8];
  out[9] = a[3] * b[10] + a[6] * b[0xb] + b[9] * *a + a[9];
  out[10] = a[7] * b[0xb] + a[4] * b[10] + a[1] * b[9] + a[10];
  out[0xb] = a[8] * b[0xb] + a[2] * b[9] + a[5] * b[10] + a[0xb];
  return;
}

/* ---- 0x0044fa70  rdMatrix_PreMultiply34 ---- */
/* Rotation 3x4 from pitch/yaw/roll angles in degrees Original name rdMatrix_PreMultiply34 (the
   remaster's GrimFandango (Linux): aligned call in rdMatrix_PreScale34); was Matrix_BuildRotation.
    */

void __cdecl rdMatrix_PreMultiply34(float *m,float *angles)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  #define local_30 (*(float *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(float (*)[2])(_frame + (0x40 - 0x2c)))
  #define local_24 (*(float (*)[3])(_frame + (0x40 - 0x24)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  fVar1 = angles[1];
  fVar2 = angles[2];
  pfVar4 = m;
  pfVar5 = &local_30;
  for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar5 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar5 = pfVar5 + 1;
  }
  *m = local_30 * *angles + fVar2 * local_18[0] + fVar1 * local_24[0];
  m[1] = local_2c[0] * *angles + angles[2] * local_18[1] + angles[1] * local_24[1];
  m[2] = local_2c[1] * *angles + angles[2] * local_18[2] + angles[1] * local_24[2];
  m[3] = angles[5] * local_18[0] + angles[3] * local_30 + angles[4] * local_24[0];
  m[4] = angles[5] * local_18[1] + angles[3] * local_2c[0] + angles[4] * local_24[1];
  m[5] = angles[5] * local_18[2] + angles[3] * local_2c[1] + angles[4] * local_24[2];
  m[6] = angles[8] * local_18[0] + angles[6] * local_30 + angles[7] * local_24[0];
  m[7] = angles[8] * local_18[1] + angles[6] * local_2c[0] + angles[7] * local_24[1];
  m[8] = angles[8] * local_18[2] + angles[6] * local_2c[1] + angles[7] * local_24[2];
  m[9] = angles[0xb] * local_18[0] + angles[9] * local_30 + angles[10] * local_24[0] + local_c[0];
  m[10] = angles[0xb] * local_18[1] + angles[9] * local_2c[0] + angles[10] * local_24[1] +
          local_c[1];
  m[0xb] = angles[0xb] * local_18[2] + angles[9] * local_2c[1] + angles[10] * local_24[2] +
           local_c[2];
  return;
}
#undef local_18
#undef local_24
#undef local_2c
#undef local_30
#undef local_c


/* ---- 0x0044fc60  rdMatrix_PostMultiply34 ---- */
/* Original name rdMatrix_PostMultiply34 (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_BuildExpandedRadius, rdModel3_CalcModelBoundingBox); was Matrix_Multiply. */

void __cdecl rdMatrix_PostMultiply34(float *m,float *other)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  #define local_30 (*(float *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(float (*)[2])(_frame + (0x40 - 0x2c)))
  #define local_24 (*(float (*)[3])(_frame + (0x40 - 0x24)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  fVar1 = other[3];
  fVar2 = other[6];
  pfVar4 = m;
  pfVar5 = &local_30;
  for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar5 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar5 = pfVar5 + 1;
  }
  *m = local_30 * *other + fVar2 * local_2c[1] + fVar1 * local_2c[0];
  m[1] = other[4] * local_2c[0] + other[1] * local_30 + other[7] * local_2c[1];
  m[2] = other[8] * local_2c[1] + other[2] * local_30 + other[5] * local_2c[0];
  m[3] = local_24[0] * *other + other[6] * local_24[2] + other[3] * local_24[1];
  m[4] = other[4] * local_24[1] + other[1] * local_24[0] + other[7] * local_24[2];
  m[5] = other[8] * local_24[2] + other[2] * local_24[0] + other[5] * local_24[1];
  m[6] = local_18[0] * *other + other[6] * local_18[2] + other[3] * local_18[1];
  m[7] = other[4] * local_18[1] + other[1] * local_18[0] + other[7] * local_18[2];
  m[8] = other[8] * local_18[2] + other[2] * local_18[0] + other[5] * local_18[1];
  m[9] = local_c[0] * *other + other[6] * local_c[2] + other[3] * local_c[1] + other[9];
  m[10] = other[4] * local_c[1] + other[1] * local_c[0] + other[7] * local_c[2] + other[10];
  m[0xb] = other[8] * local_c[2] + other[2] * local_c[0] + other[5] * local_c[1] + other[0xb];
  return;
}
#undef local_18
#undef local_24
#undef local_2c
#undef local_30
#undef local_c


/* ---- 0x0044fe50  Matrix_BuildTransform ---- */
/* Rotation then translation */

void __cdecl Matrix_BuildTransform(float *m,uint angles)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_30 (*(float (*)[12])(_frame + (0x40 - 0x30)))
  
  rdMatrix_BuildRotate34(local_30,(uint *)angles);
  rdMatrix_PreMultiply34(m,local_30);
  return;
}
#undef local_30


/* ---- 0x0044fe80  rdMatrix_PostTranslate34 ---- */
/* Original name rdMatrix_PostTranslate34 (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_BuildExpandedRadius, rdModel3_CalcModelBoundingBox); was Matrix_SetTranslation. */

void __cdecl rdMatrix_PostTranslate34(int m,float *v)

{
  *(float *)(m + 0x24) = *v + *(float *)(m + 0x24);
  *(float *)(m + 0x28) = v[1] + *(float *)(m + 0x28);
  *(float *)(m + 0x2c) = v[2] + *(float *)(m + 0x2c);
  return;
}

/* ---- 0x0044feb0  rdMatrix_PreScale34 ---- */
/* Original name rdMatrix_PreScale34 (the remaster's GrimFandango (Linux): aligned call in
   sputActor_DrawToClean, sputRender_Update); was Matrix_BuildTransform2. */

void __cdecl rdMatrix_PreScale34(float *m,uint scale)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_30 (*(float (*)[12])(_frame + (0x40 - 0x30)))
  
  rdMatrix_BuildScale34(local_30,(undefined4 *)scale);
  rdMatrix_PreMultiply34(m,local_30);
  return;
}
#undef local_30


/* ---- 0x0044fee0  rdMatrix_TransformVector34 ---- */
/* Original name rdMatrix_TransformVector34 (the remaster's GrimFandango (Linux): aligned call in
   rdMatrix_LookAt, rdModel3_DrawFace, rdSprite_Draw); was Vec3_Copy. */

void __cdecl rdMatrix_TransformVector34(float *out,float *v,float *m)

{
  *out = *v * *m + v[1] * m[3] + v[2] * m[6];
  out[1] = m[1] * *v + m[4] * v[1] + v[2] * m[7];
  out[2] = m[2] * *v + m[8] * v[2] + v[1] * m[5];
  return;
}

/* ---- 0x0044ff50  rdMatrix_TransformVectorOrtho34 ---- */
/* Original name rdMatrix_TransformVectorOrtho34 (the remaster's GrimFandango (Linux): same body
   (the vector times the transposed 3x3 part); called by Puck::InvXform and the collision box tests
   in both builds); was Vec3_TransformTo. */

void __cdecl rdMatrix_TransformVectorOrtho34(float *out,float *v,float *m)

{
  *out = *v * *m + v[1] * m[1] + v[2] * m[2];
  out[1] = m[3] * *v + m[4] * v[1] + v[2] * m[5];
  out[2] = m[6] * *v + m[8] * v[2] + v[1] * m[7];
  return;
}

/* ---- 0x0044ffc0  rdMatrix_TransformVector34Acc ---- */
/* Transforms the point in place by the 3x4 matrix Original name rdMatrix_TransformVector34Acc (the
   remaster's GrimFandango (Linux): aligned call in rdSprite_Draw, rdVector_Rotate3Acc,
   sputLua_WalkActorVectorL); was Vec3_Transform. */

void __cdecl rdMatrix_TransformVector34Acc(float *vec,float *m)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  fVar1 = m[7];
  fVar2 = m[4];
  fVar3 = m[5];
  fVar4 = m[8];
  fVar5 = m[1];
  fVar6 = *vec;
  fVar7 = m[2];
  fVar8 = vec[1];
  fVar9 = *vec;
  *vec = *vec * *m + vec[1] * m[3] + vec[2] * m[6];
  vec[1] = fVar5 * fVar6 + vec[1] * fVar2 + vec[2] * fVar1;
  vec[2] = fVar7 * fVar9 + vec[2] * fVar4 + fVar3 * fVar8;
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00450060  rdMatrix_TransformPoint34 ---- */
/* out = a * R + t for a 3x4 matrix (rotation in [0..8], translation in [9..11]). Was misnamed
   Vec3_Sub. rdModel_DrawMesh uses it with a zeroed translation (saved and restored around the call)
   to rotate light directions. Original name rdMatrix_TransformPoint34 (the remaster's GrimFandango
   (Linux): aligned call in rdModel3_BuildExpandedRadius, rdModel3_CalcModelBoundingBox,
   rdModel3_Draw); was Matrix34_TransformPoint. */

void __cdecl rdMatrix_TransformPoint34(float *out,float *a,float *b)

{
  *out = *a * *b + a[1] * b[3] + a[2] * b[6] + b[9];
  out[1] = b[1] * *a + b[4] * a[1] + a[2] * b[7] + b[10];
  out[2] = b[2] * *a + b[8] * a[2] + a[1] * b[5] + b[0xb];
  return;
}

/* ---- 0x004500d0  rdMatrix_TransformPoint34Acc ---- */
/* Rotates the vector in place by the 3x3 part of the matrix Original name
   rdMatrix_TransformPoint34Acc (the remaster's GrimFandango (Linux): same body (v = v * R + t in
   place, 3x4 matrix); rdModel3_Draw's call); was Vec3_Rotate3x3. */

void __cdecl rdMatrix_TransformPoint34Acc(float *vec,float *m)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  fVar1 = m[7];
  fVar2 = m[4];
  fVar3 = m[5];
  fVar4 = m[8];
  fVar5 = m[1];
  fVar6 = *vec;
  fVar7 = m[10];
  fVar8 = m[2];
  fVar9 = vec[1];
  fVar10 = *vec;
  fVar11 = m[0xb];
  *vec = *vec * *m + vec[1] * m[3] + vec[2] * m[6] + m[9];
  vec[1] = fVar5 * fVar6 + vec[1] * fVar2 + vec[2] * fVar1 + fVar7;
  vec[2] = fVar8 * fVar10 + vec[2] * fVar4 + fVar3 * fVar9 + fVar11;
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00450170  rdMatrix_TransformPointLst34 ---- */
/* Original name rdMatrix_TransformPointLst34 (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_DrawMeshImpl); was Matrix_TransformPoints. */

void __cdecl rdMatrix_TransformPointLst34(float *m,float *in,float *out,int count)

{
  for (; count != 0; count = count + -1) {
    *out = *m * *in + in[2] * m[6] + m[3] * in[1] + m[9];
    out[1] = in[1] * m[4] + in[2] * m[7] + m[1] * *in + m[10];
    out[2] = in[2] * m[8] + in[1] * m[5] + m[2] * *in + m[0xb];
    out = out + 3;
    in = in + 3;
  }
  return;
}

/* ---- 0x00450220  rdFace_NewEntry ---- */
/* Resets a 0x4c-byte face record (rdFace_NewEntry of the Jedi Knight RDroid library): type,
   geometry / lighting / texture modes, material and the vertex lists 0, material index (+0x24) -1.
   Called by rdModel3_LoadEntryText for every face it reads; was FUN_00450220. */

uint __cdecl rdFace_NewEntry(undefined4 *face)

{
  *face = 0;
  face[1] = 0;
  face[5] = 0;
  face[6] = 0;
  face[7] = 0;
  face[8] = 0;
  face[9] = 0xffffffff;
  face[0x10] = 0;
  face[0x11] = 0;
  face[0x12] = 0;
  face[10] = 0;
  face[0xb] = 0;
  face[0xc] = 0;
  return 1;
}

/* ---- 0x00450260  rdFace_FreeEntry ---- */
/* Original name rdFace_FreeEntry (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_FreeEntry); was FUN_00450260. */

void __cdecl rdFace_FreeEntry(int face)

{
  if (*(int *)(face + 0x18) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(face + 0x18));
  }
  if (*(int *)(face + 0x1c) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(face + 0x1c));
  }
  return;
}

/* ---- 0x00450290  rdMath_CalcSurfaceNormal ---- */
/* Normal of the triangle (p0,p1,p2) from the normalised edges p1-p0 and p2-p0, with tiny components
   zeroed. Original name rdMath_CalcSurfaceNormal (the remaster's GrimFandango (Linux): same body
   (two edge vectors from the first point, normalised, cross product, normalised, components below
   1e-6 cleared); called by rdModel3_CalcFaceNormals in both builds); was Math3D_TriangleNormal. */

void __cdecl rdMath_CalcSurfaceNormal(float *out,float *a,float *b,float *c)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float (*)[2])(_frame + (0x30 - 0x14)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float (*)[2])(_frame + (0x30 - 0x8)))
  
  local_c = *b - *a;
  local_18 = *c - *a;
  local_8[0] = b[1] - a[1];
  local_8[1] = b[2] - a[2];
  local_14[0] = c[1] - a[1];
  local_14[1] = c[2] - a[2];
  rdVector_Normalize3Acc(&local_c);
  rdVector_Normalize3Acc(&local_18);
  *out = local_14[1] * local_8[0] - local_14[0] * local_8[1];
  out[1] = local_18 * local_8[1] - local_14[1] * local_c;
  out[2] = local_14[0] * local_c - local_18 * local_8[0];
  rdVector_Normalize3Acc(out);
  rdMath_ClampVector(out,1e-06f);
  return;
}
#undef local_14
#undef local_18
#undef local_8
#undef local_c


/* ---- 0x00450380  rdMath_ClampVector ---- */
/* Sets every component whose magnitude is below the epsilon argument to 0. Original name
   rdMath_ClampVector (the remaster's GrimFandango (Linux): same body (every component whose
   absolute value is below the threshold becomes 0); the remaster inlined it into
   rdMath_CalcSurfaceNormal); was Vec3_ZeroSmallComponents. */

void __cdecl rdMath_ClampVector(float *v,float limit)

{
  float fVar1;
  
  fVar1 = *v;
  if (*v < 0.0f) {
    fVar1 = -fVar1;
  }
  if (limit <= fVar1) {
    fVar1 = *v;
  }
  else {
    fVar1 = 0.0f;
  }
  *v = fVar1;
  fVar1 = v[1];
  if (v[1] < 0.0f) {
    fVar1 = -fVar1;
  }
  if (limit <= fVar1) {
    fVar1 = v[1];
  }
  else {
    fVar1 = 0.0f;
  }
  v[1] = fVar1;
  fVar1 = v[2];
  if (v[2] < 0.0f) {
    fVar1 = -fVar1;
  }
  if (fVar1 < limit) {
    v[2] = 0.0f;
    return;
  }
  v[2] = v[2];
  return;
}

/* ---- 0x00450410  rdMath_PointsCollinear ---- */
/* True when the normalised edges p1-p0 and p2-p0 are parallel (|dot| within 0.999..1.001). Original
   name rdMath_PointsCollinear (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_CalcFaceNormals); was Math3D_PointsCollinear. */

uint __cdecl rdMath_PointsCollinear(float *a,float *b,float *c)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float (*)[2])(_frame + (0x30 - 0x14)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float (*)[2])(_frame + (0x30 - 0x8)))
  
  local_c = *b - *a;
  local_18 = *c - *a;
  local_8[0] = b[1] - a[1];
  local_8[1] = b[2] - a[2];
  local_14[0] = c[1] - a[1];
  local_14[1] = c[2] - a[2];
  rdVector_Normalize3Acc(&local_c);
  rdVector_Normalize3Acc(&local_18);
  fVar1 = local_14[1] * local_8[1] + local_14[0] * local_8[0] + local_18 * local_c;
  if (fVar1 < 0.0f) {
    fVar1 = -fVar1;
  }
  if ((0.999f <= fVar1) && (fVar1 <= 1.001f)) {
    return 1;
  }
  return 0;
}
#undef local_14
#undef local_18
#undef local_8
#undef local_c

