/* GRIMFANDANGO.EXE :: math3d.c
 * functions 0x00446880 .. 0x00450410 (36 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00446880  Vec3_Dot ---- */
float __cdecl Vec3_Dot(float *a,float *b)

{
  return *a * *b + a[1] * b[1];
}

/* ---- 0x004468a0  Vec3_Dot2 ---- */
float __cdecl Vec3_Dot2(float *a,float *b)

{
  return *a * *b + b[2] * a[2] + a[1] * b[1];
}

/* ---- 0x004468d0  Vec3_Cross ---- */
void __cdecl Vec3_Cross(float *out,float *a,float *b)

{
  *out = a[1] * b[2] - a[2] * b[1];
  out[1] = a[2] * *b - b[2] * *a;
  out[2] = b[1] * *a - a[1] * *b;
  return;
}

/* ---- 0x00446920  Vec3_NormalizeTo ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Vec3_NormalizeTo(float *param_1,float *param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  fVar1 = SQRT(*param_2 * *param_2 + param_2[2] * param_2[2] + param_2[1] * param_2[1]);
  if (fVar1 != 0.0) {
    *param_1 = *param_2 / fVar1;
    param_1[1] = param_2[1] / fVar1;
    param_1[2] = param_2[2] / fVar1;
    return;
  }
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  return;
}
#undef local_4

#endif


/* ---- 0x004469a0  Vec3_Normalize ---- */
float __cdecl Vec3_Normalize(float *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  fVar1 = SQRT(*param_1 * *param_1 + param_1[2] * param_1[2] + param_1[1] * param_1[1]);
  if (fVar1 != 0.0) {
    fVar2 = 1.0 / fVar1;
    *param_1 = fVar2 * *param_1;
    param_1[1] = param_1[1] * fVar2;
    param_1[2] = param_1[2] * fVar2;
  }
  return fVar1;
}
#undef local_4


/* ---- 0x00446a10  Vec3_NormalizeApprox ---- */
/* Rough vector length: with the absolute values sorted max >= mid >= min, len = max + 0.34375 * mid
   + 0.25 * min. Also divides the vector by it (in place, in floats) and returns the length. */

float __cdecl Vec3_NormalizeApprox(float *param_1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  #define local_28 (*(float (*)[3])(_frame + (0x40 - 0x28)))
  #define local_1c (*(float (*)[3])(_frame + (0x40 - 0x1c)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float (*)[2])(_frame + (0x40 - 0xc)))
  
  if (0.0 <= *param_1) {
    local_28[2] = *param_1;
  }
  else {
    local_28[2] = -*param_1;
  }
  local_c[0] = local_28[2];
  if (0.0 <= param_1[1]) {
    local_28[1] = param_1[1];
  }
  else {
    local_28[1] = -param_1[1];
  }
  local_c[1] = local_28[1];
  if (0.0 <= param_1[2]) {
    local_28[0] = param_1[2];
  }
  else {
    local_28[0] = -param_1[2];
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
  fVar1 = local_1c[0] * 0.25 + local_c[1] * 0.34375 + local_c[0];
  fVar2 = 1.0 / fVar1;
  *param_1 = *param_1 * fVar2;
  param_1[1] = param_1[1] * fVar2;
  param_1[2] = param_1[2] * fVar2;
  return fVar1;
}
#undef local_10
#undef local_1c
#undef local_28
#undef local_c


/* ---- 0x00446ba0  Vec3_Rotate ---- */
/* Lua RotateVector: rotates a vector by pitch/yaw/roll angles */

void __cdecl Vec3_Rotate(float *vec,float *rot)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_30 (*(float (*)[12])(_frame + (0x40 - 0x30)))
  
  Angles_ToMatrixNoPos(local_30,rot);
  Vec3_Transform(vec,local_30);
  return;
}
#undef local_30


/* ---- 0x00446bd0  Matrix_GetAngles ---- */
void __cdecl Matrix_GetAngles(float *matrix,float *outAngles)

{
  float fVar1;
  
  outAngles[2] = 0.0;
  fVar1 = Math_AsinDegreesSeries(matrix[2]);
  *outAngles = fVar1;
  fVar1 = Math_Atan2Deg(matrix[1],*matrix);
  outAngles[1] = fVar1;
  return;
}

/* ---- 0x0044e7d0  Frustum_TestSphere ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
uint Frustum_TestSphere(int *param_1,float *param_2,float param_3)

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
  
  pfVar8 = param_2;
  fVar5 = param_3 + param_2[1];
  fVar2 = param_2[1] - param_3;
  if (fVar5 < PUN(float,param_1[1])) {
    return 2;
  }
  bVar4 = PUN(float,param_1[1]) <= fVar2;
  if (*param_1 != 0) {
    if (PUN(float,param_1[2]) < fVar2) {
      return 2;
    }
    if (PUN(float,param_1[2]) < fVar5) {
      bVar4 = false;
    }
  }
  fVar6 = param_3 + param_2[2];
  fVar7 = param_2[2] - param_3;
  iVar3 = *(int *)g_pRdCurrentCamera;
  if (iVar3 == 1) {
    fVar1 = PUN(float,param_1[7]) * fVar2;
    param_2 = PUN(float *,(float)(PUN(float,param_1[7]) * fVar5));
  }
  else {
    param_2 = (float *)param_1[4];
    fVar1 = PUN(float,param_1[4]);
  }
  if ((fVar1 < fVar7) && (PUN(float,param_2) < fVar7)) {
    return 2;
  }
  if ((fVar1 < fVar6) || (PUN(float,param_2) < fVar6)) {
    bVar4 = false;
  }
  if (iVar3 == 1) {
    fVar1 = PUN(float,param_1[8]) * fVar2;
    param_2 = PUN(float *,(float)(PUN(float,param_1[8]) * fVar5));
  }
  else {
    param_2 = (float *)param_1[6];
    fVar1 = PUN(float,param_1[6]);
  }
  if ((fVar6 < fVar1) && (fVar6 < PUN(float,param_2))) {
    return 2;
  }
  if ((fVar7 < fVar1) || (fVar7 < PUN(float,param_2))) {
    bVar4 = false;
  }
  fVar7 = param_3 + *pfVar8;
  fVar6 = *pfVar8 - param_3;
  if (iVar3 == 1) {
    fVar1 = PUN(float,param_1[9]) * fVar2;
    param_3 = PUN(float,param_1[9]) * fVar5;
  }
  else {
    param_3 = PUN(float,param_1[3]);
    fVar1 = PUN(float,param_1[3]);
  }
  if ((fVar7 < fVar1) && (fVar7 < param_3)) {
    return 2;
  }
  if ((fVar6 < fVar1) || (fVar6 < param_3)) {
    bVar4 = false;
  }
  if (iVar3 == 1) {
    fVar2 = PUN(float,param_1[10]) * fVar2;
    param_3 = PUN(float,param_1[10]) * fVar5;
  }
  else {
    param_3 = PUN(float,param_1[5]);
    fVar2 = PUN(float,param_1[5]);
  }
  if ((fVar2 < fVar6) && (param_3 < fVar6)) {
    return 2;
  }
  if ((fVar2 < fVar7) || (param_3 < fVar7)) {
    bVar4 = false;
  }
  return !bVar4;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x0044ea50  Polygon_ClipToPlane ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
uint Polygon_ClipToPlane(float *param_1,float *param_2,float *param_3,undefined4 *param_4,
                        float *param_5,uint *param_6)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  uint *puVar9;
  int iVar10;
  float *pfVar11;
  uint *puVar12;
  undefined4 *puVar13;
  uint *puVar14;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  local_c[2] = PUN(float,param_6);
  puVar5 = param_4;
  iVar3 = (int)param_6 * 3;
  iVar10 = (int)param_6 * 3;
  iVar4 = (int)param_6 * 3;
  local_20 = 0;
  pfVar6 = (float *)(param_4 + (int)param_6 * 2 + -2);
  if (param_4 == (undefined4 *)0x0) {
    pfVar6 = param_5;
  }
  if (param_5 != (float *)0x0) {
    local_18[2] = param_5[(int)param_6 + -1];
  }
  if (0 < (int)param_6) {
    local_24 = (uint)&UINT_007f47c0;
    local_c[1] = PUN(float,param_5);
    local_c[0] = PUN(float,param_4);
    param_6 = &UINT_007f46b8;
    puVar12 = &UINT_007f48c0;
    local_1c = (uint)&UINT_007f46bc;
    puVar9 = &UINT_007f48c8;
    puVar14 = &UINT_007f48c4;
    pfVar7 = param_3 + iVar4 + -3;
    pfVar8 = param_3;
    pfVar11 = param_5;
    local_18[0] = ((param_3 + iVar4 + -3)[1] - param_2[1]) * param_1[1] +
                  (param_3[iVar3 + -1] - param_2[2]) * param_1[2] +
                  (param_3[iVar10 + -3] - *param_2) * *param_1;
    do {
      if (param_4 != (undefined4 *)0x0) {
        local_18[1] = local_c[0];
      }
      if (param_5 != (float *)0x0) {
        pfVar11 = *PUN(float **,(float)local_c[1]);
      }
      fVar2 = (pfVar8[1] - param_2[1]) * param_1[1] +
              (*pfVar8 - *param_2) * *param_1 + (pfVar8[2] - param_2[2]) * param_1[2];
      if ((local_18[0] < 0.0) || (fVar2 < 0.0)) {
        if ((0.0 <= local_18[0]) && (fVar2 < 0.0)) {
          fVar1 = -(local_18[0] / (fVar2 - local_18[0]));
          *puVar12 = PUN(uint,(float)((*pfVar8 - *pfVar7) * fVar1 + *pfVar7));
          *puVar14 = PUN(uint,(float)((pfVar8[1] - pfVar7[1]) * fVar1 + pfVar7[1]));
          *puVar9 = PUN(uint,(float)((pfVar8[2] - pfVar7[2]) * fVar1 + pfVar7[2]));
          if (param_4 != (undefined4 *)0x0) {
            *param_6 = PUN(uint,(float)((*PUN(float *,(float)local_18[1]) - *pfVar6) * fVar1 + *pfVar6));
            *(float *)local_1c = (*(float *)(PUN(int,(float)local_18[1]) + 4) - pfVar6[1]) * fVar1 + pfVar6[1];
          }
          if (param_5 != (float *)0x0) {
            *(float *)local_24 = (PUN(float,pfVar11) - local_18[2]) * fVar1 + local_18[2];
          }
          goto LAB_0044ed90;
        }
        if ((local_18[0] < 0.0) && (0.0 <= fVar2)) {
          fVar1 = -(local_18[0] / (fVar2 - local_18[0]));
          *puVar12 = PUN(uint,(float)((*pfVar8 - *pfVar7) * fVar1 + *pfVar7));
          *puVar14 = PUN(uint,(float)((pfVar8[1] - pfVar7[1]) * fVar1 + pfVar7[1]));
          *puVar9 = PUN(uint,(float)((pfVar8[2] - pfVar7[2]) * fVar1 + pfVar7[2]));
          if (param_4 != (undefined4 *)0x0) {
            *param_6 = PUN(uint,(float)((*PUN(float *,(float)local_18[1]) - *pfVar6) * fVar1 + *pfVar6));
            *(float *)local_1c = (*(float *)(PUN(int,(float)local_18[1]) + 4) - pfVar6[1]) * fVar1 + pfVar6[1];
          }
          if (param_5 != (float *)0x0) {
            *(float *)local_24 = (PUN(float,pfVar11) - local_18[2]) * fVar1 + local_18[2];
          }
          local_20 = local_20 + 1;
          local_1c = local_1c + 8;
          pfVar6 = (float *)(param_6 + 2);
          local_24 = local_24 + 4;
          pfVar7 = (float *)(puVar12 + 3);
          puVar14 = puVar14 + 3;
          *pfVar7 = *pfVar8;
          puVar9 = puVar9 + 3;
          puVar12[4] = PUN(uint,(float)pfVar8[1]);
          puVar12[5] = PUN(uint,(float)pfVar8[2]);
          if (param_4 != (undefined4 *)0x0) {
            *pfVar6 = *PUN(float *,(float)local_18[1]);
            param_6[3] = PUN(uint,(float)*(float *)(PUN(int,(float)local_18[1]) + 4));
            param_6[4] = PUN(uint,(float)*(float *)(PUN(int,(float)local_18[1]) + 8));
          }
          puVar12 = (uint *)pfVar7;
          param_6 = (uint *)pfVar6;
          if (param_5 != (float *)0x0) {
            *(float **)local_24 = pfVar11;
          }
          goto LAB_0044ed90;
        }
      }
      else {
        *puVar12 = PUN(uint,(float)*pfVar8);
        puVar12[1] = PUN(uint,(float)pfVar8[1]);
        puVar12[2] = PUN(uint,(float)pfVar8[2]);
        if (param_4 != (undefined4 *)0x0) {
          *param_6 = PUN(uint,(float)*PUN(float *,(float)local_18[1]));
          param_6[1] = PUN(uint,(float)*(float *)(PUN(int,(float)local_18[1]) + 4));
          param_6[2] = PUN(uint,(float)*(float *)(PUN(int,(float)local_18[1]) + 8));
        }
        if (param_5 != (float *)0x0) {
          *(float **)local_24 = pfVar11;
        }
LAB_0044ed90:
        local_20 = local_20 + 1;
        local_1c = local_1c + 8;
        param_6 = param_6 + 2;
        puVar14 = puVar14 + 3;
        puVar9 = puVar9 + 3;
        puVar12 = puVar12 + 3;
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
    } while (local_c[2] != 0.0);
  }
  if (0 < (int)local_20) {
    iVar10 = (int)&UINT_007f48c0 - (int)param_3;
    iVar3 = -(int)param_4;
    param_4 = (undefined4 *)local_20;
    pfVar6 = param_5;
    puVar13 = puVar5;
    do {
      pfVar11 = (float *)(iVar10 + (int)param_3);
      *param_3 = *pfVar11;
      param_3[1] = pfVar11[1];
      param_3[2] = pfVar11[2];
      if (puVar5 != (undefined4 *)0x0) {
        *puVar13 = *(undefined4 *)((int)&UINT_007f46b8 + iVar3 + (int)puVar13);
        puVar13[1] = *(undefined4 *)((int)&UINT_007f46bc + iVar3 + (int)puVar13);
      }
      if (param_5 != (float *)0x0) {
        *pfVar6 = *(float *)(((int)&UINT_007f47c0 - (int)param_5) + (int)pfVar6);
      }
      param_3 = param_3 + 3;
      puVar13 = puVar13 + 2;
      pfVar6 = pfVar6 + 1;
      param_4 = (undefined4 *)((int)param_4 - 1);
    } while (param_4 != (undefined4 *)0x0);
  }
  return local_20;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_c

#endif


/* ---- 0x0044eeb0  Angles_ToMatrix ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void Angles_ToMatrix(float *param_1,undefined4 *param_2,float *param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  #define local_1c (*(float (*)[3])(_frame + (0x30 - 0x1c)))
  #define local_10 (*(float (*)[3])(_frame + (0x30 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  puVar1 = param_2;
  Math_SinCosTable(*param_2,&param_2,local_1c);
  Math_SinCosTable(PUN(float,puVar1[1]),local_1c + 2,local_10);
  Math_SinCosTable(PUN(float,puVar1[2]),local_1c + 1,local_10 + 1);
  *param_1 = -(local_1c[1] * local_1c[2]) * PUN(float,param_2) + local_10[1] * local_10[0];
  param_1[1] = local_1c[1] * local_10[0] * PUN(float,param_2) + local_10[1] * local_1c[2];
  param_1[2] = -local_1c[1] * local_1c[0];
  param_1[3] = -local_1c[2] * local_1c[0];
  param_1[4] = local_10[0] * local_1c[0];
  param_1[5] = PUN(float,param_2);
  param_1[6] = local_10[1] * local_1c[2] * PUN(float,param_2) + local_1c[1] * local_10[0];
  param_1[7] = -PUN(float,param_2) * local_10[1] * local_10[0] + local_1c[1] * local_1c[2];
  param_1[8] = local_10[1] * local_1c[0];
  param_1[9] = *param_3;
  param_1[10] = param_3[1];
  param_1[0xb] = param_3[2];
  return;
}
#undef local_10
#undef local_1c
#undef local_4

#endif


/* ---- 0x0044efd0  Matrix_Transpose ---- */
void __cdecl Matrix_Transpose(float *out,float *m)

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

/* ---- 0x0044f080  Angles_ToMatrixNoPos ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void Angles_ToMatrixNoPos(float *param_1,undefined4 *param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  #define local_1c (*(float (*)[3])(_frame + (0x30 - 0x1c)))
  #define local_10 (*(float (*)[3])(_frame + (0x30 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  puVar1 = param_2;
  Math_SinCosTable(*param_2,&param_2,local_1c);
  Math_SinCosTable(PUN(float,puVar1[1]),local_1c + 2,local_10);
  Math_SinCosTable(PUN(float,puVar1[2]),local_1c + 1,local_10 + 1);
  *param_1 = -(local_1c[1] * local_1c[2]) * PUN(float,param_2) + local_10[1] * local_10[0];
  param_1[1] = local_1c[1] * local_10[0] * PUN(float,param_2) + local_10[1] * local_1c[2];
  param_1[2] = -local_1c[1] * local_1c[0];
  param_1[3] = -local_1c[2] * local_1c[0];
  param_1[4] = local_10[0] * local_1c[0];
  param_1[5] = PUN(float,param_2);
  param_1[6] = local_10[1] * local_1c[2] * PUN(float,param_2) + local_1c[1] * local_10[0];
  param_1[7] = -PUN(float,param_2) * local_10[1] * local_10[0] + local_1c[1] * local_1c[2];
  param_1[8] = local_10[1] * local_1c[0];
  param_1[9] = 0.0;
  param_1[10] = 0.0;
  param_1[0xb] = 0.0;
  return;
}
#undef local_10
#undef local_1c
#undef local_4

#endif


/* ---- 0x0044f1a0  Matrix_BuildTranslation ---- */
/* Identity 3x4 (from g_MatrixIdentity) with the translation column set */

void __cdecl Matrix_BuildTranslation(float *m,float *pos)

{
  int iVar1;
  float *pfVar2;
  float *pfVar3;
  
  pfVar2 = g_MatrixIdentity;
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

/* ---- 0x0044f1d0  Matrix_BuildTranslation2 ---- */
void Matrix_BuildTranslation2(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = param_2[1];
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = param_2[2];
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  return;
}

/* ---- 0x0044f210  Matrix_AxisAngle ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void Matrix_AxisAngle(float *param_1,float *param_2,float param_3)

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
  #define local_28 (*(float (*)[3])(_frame + (0x40 - 0x28)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  Math_SinCosTable(param_3,local_28,&param_3);
  fVar1 = 1.0 - param_2[2];
  fVar2 = fVar1;
  if (fVar1 < 0.0) {
    fVar2 = -fVar1;
  }
  if (fVar2 <= 1e-05) {
    fVar1 = 0.0;
  }
  if (fVar1 == 0.0) {
    *param_1 = param_3;
    param_1[4] = param_3;
    param_1[3] = -local_28[0];
    param_1[1] = local_28[0];
  }
  else {
    fVar1 = param_2[2] - -1.0;
    fVar2 = fVar1;
    if (fVar1 < 0.0) {
      fVar2 = -fVar1;
    }
    if (fVar2 <= 1e-05) {
      fVar1 = 0.0;
    }
    if (fVar1 != 0.0) {
      fVar6 = *param_2 * *param_2;
      fVar8 = param_2[1] * param_2[1];
      fVar7 = fVar6 * param_3;
      fVar9 = (1.0 - fVar6) - fVar8;
      fVar10 = fVar8 * param_3;
      param_3 = 1.0 - param_3;
      fVar1 = param_2[1];
      fVar2 = param_2[1];
      fVar3 = *param_2;
      fVar4 = param_2[2];
      fVar5 = *param_2;
      fVar11 = param_2[2] * *param_2 * param_3;
      fVar12 = param_2[1] * param_2[2] * param_3;
      *param_1 = (fVar7 * fVar9 + fVar10) / (1.0 - fVar9) + fVar6;
      param_3 = fVar1 * fVar3 * param_3;
      param_1[9] = 0.0;
      param_1[10] = 0.0;
      param_1[4] = (fVar10 * fVar9 + fVar7) / (1.0 - fVar9) + fVar8;
      param_1[8] = fVar10 + fVar7 + fVar9;
      param_1[1] = fVar4 * local_28[0] + param_3;
      param_1[3] = param_3 - fVar4 * local_28[0];
      param_1[2] = fVar11 - fVar2 * local_28[0];
      param_1[5] = fVar12 + local_28[0] * fVar5;
      param_1[6] = fVar11 + fVar2 * local_28[0];
      param_1[7] = fVar12 - local_28[0] * fVar5;
      param_1[0xb] = 0.0;
      return;
    }
    *param_1 = param_3;
    param_1[4] = param_3;
    param_1[1] = -local_28[0];
    param_1[3] = local_28[0];
  }
  param_1[2] = 0.0;
  param_1[5] = 0.0;
  param_1[6] = 0.0;
  param_1[7] = 0.0;
  param_1[8] = 1.0;
  param_1[9] = 0.0;
  param_1[10] = 0.0;
  param_1[0xb] = 0.0;
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


/* ---- 0x0044f490  Camera_BuildBasis ---- */
/* Camera basis from (position, interest, roll) into out[0..11]: out+0 right = normalise(forward x
   rolledUp), out+0xc forward = normalise(interest - position), out+0x18 up = right-forward cross,
   out+0x24 position. The up used is (0,0,1) rolled about the forward by roll with Matrix_AxisAngle
   ((0,1,0) or (-0,-1,-0) when the forward is within 0.999 of vertical). */

void Camera_BuildBasis(float *param_1,float *param_2,float *param_3,undefined4 param_4)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *pfVar1;
  float fVar2;
  float *v;
  #define local_48 (*(float *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(float (*)[2])(_frame + (0x60 - 0x44)))
  #define local_3c (*(float (*)[3])(_frame + (0x60 - 0x3c)))
  #define local_30 (*(float (*)[12])(_frame + (0x60 - 0x30)))
  
  pfVar1 = param_1 + 3;
  *pfVar1 = *param_3 - *param_2;
  param_1[4] = param_3[1] - param_2[1];
  param_1[5] = param_3[2] - param_2[2];
  Vec3_Normalize(pfVar1);
  Matrix_AxisAngle(local_30,pfVar1,PUN(float,param_4));
  fVar2 = *pfVar1 * 0.0 + param_1[4] * 0.0 + param_1[5] * 1.0;
  if (fVar2 < 0.0) {
    fVar2 = -fVar2;
  }
  if (fVar2 <= 0.999) {
    v = (float *)&DAT_004d7540;
  }
  else if (param_1[5] <= 0.0) {
    v = (float *)&DAT_004d7530;
  }
  else {
    local_3c[0] = -0.0;
    local_3c[1] = -1.0;
    v = local_3c;
    local_3c[2] = -0.0;
  }
  Vec3_Copy(&local_48,v,local_30);
  *param_1 = param_1[4] * local_44[1] - param_1[5] * local_44[0];
  param_1[1] = param_1[5] * local_48 - *pfVar1 * local_44[1];
  param_1[2] = *pfVar1 * local_44[0] - param_1[4] * local_48;
  Vec3_Normalize(param_1);
  param_1[6] = param_1[5] * param_1[1] - param_1[4] * param_1[2];
  param_1[7] = param_1[2] * *pfVar1 - param_1[5] * *param_1;
  param_1[8] = param_1[4] * *param_1 - param_1[1] * *pfVar1;
  Vec3_Normalize(param_1 + 6);
  param_1[9] = *param_2;
  param_1[10] = param_2[1];
  param_1[0xb] = param_2[2];
  return;
}
#undef local_30
#undef local_3c
#undef local_44
#undef local_48


/* ---- 0x0044f650  Matrix_ToAngles ---- */
/* WARNING: Variable defined which should be unmapped: local_28 */

void Matrix_ToAngles(float *param_1,float *param_2)

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
  
  fVar3 = param_1[3];
  fVar4 = param_1[4];
  fVar9 = *param_1;
  fVar8 = fVar4 * fVar4 + fVar3 * fVar3;
  fVar1 = param_1[2];
  fVar2 = param_1[5];
  fVar5 = SQRT(fVar8);
  fVar6 = -param_1[1];
  if (0.001 <= fVar5) {
    fVar7 = Math_AsinDegreesSeries(fVar4 / fVar5);
    fVar7 = 90.0 - fVar7;
    if (0.0 < fVar3) {
      fVar7 = -fVar7;
    }
    param_2[1] = fVar7;
  }
  else {
    fVar7 = Math_AsinDegreesSeries(--fVar9);
    fVar7 = 90.0 - fVar7;
    if (((0.0 < fVar6) && (0.0 < fVar2)) || ((fVar6 < 0.0 && (fVar2 < 0.0)))) {
      fVar7 = -fVar7;
    }
    param_2[2] = fVar7;
    param_2[1] = 0.0;
  }
  if (0.001 <= fVar5) {
    fVar8 = fVar8 / fVar5;
    if (fVar8 < 1.0) {
      fVar8 = Math_AsinDegreesSeries(fVar8);
      *param_2 = 90.0 - fVar8;
    }
    else {
      *param_2 = 0.0;
    }
  }
  else {
    *param_2 = 90.0;
  }
  if (fVar2 < 0.0) {
    *param_2 = -*param_2;
  }
  fVar4 = -fVar4;
  if (0.001 <= fVar5) {
    fVar9 = (fVar6 * fVar3 + fVar4 * -fVar9) / SQRT(fVar4 * fVar4 + fVar3 * fVar3);
    if (fVar9 < 1.0) {
      if (-1.0 < fVar9) {
        fVar9 = Math_AsinDegreesSeries(fVar9);
        param_2[2] = 90.0 - fVar9;
      }
      else {
        param_2[2] = 180.0;
      }
    }
    else {
      param_2[2] = 0.0;
    }
    if (-fVar1 < 0.0) {
      param_2[2] = -param_2[2];
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


/* ---- 0x0044f880  Matrix_Identity ---- */
void __cdecl Matrix_Identity(float *m)

{
  int iVar1;
  float *pfVar2;
  
  pfVar2 = g_MatrixIdentity;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *m = *pfVar2;
    pfVar2 = pfVar2 + 1;
    m = m + 1;
  }
  return;
}

/* ---- 0x0044f8a0  Matrix_Mul34 ---- */
/* 3x4 affine matrix product */

void __cdecl Matrix_Mul34(float *out,float *a,float *b)

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

/* ---- 0x0044fa70  Matrix_BuildRotation ---- */
/* Rotation 3x4 from pitch/yaw/roll angles in degrees */

void __cdecl Matrix_BuildRotation(float *m,float *angles)

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


/* ---- 0x0044fc60  Matrix_Multiply ---- */
void Matrix_Multiply(float *param_1,float *param_2)

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
  
  fVar1 = param_2[3];
  fVar2 = param_2[6];
  pfVar4 = param_1;
  pfVar5 = &local_30;
  for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar5 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    pfVar5 = pfVar5 + 1;
  }
  *param_1 = local_30 * *param_2 + fVar2 * local_2c[1] + fVar1 * local_2c[0];
  param_1[1] = param_2[4] * local_2c[0] + param_2[1] * local_30 + param_2[7] * local_2c[1];
  param_1[2] = param_2[8] * local_2c[1] + param_2[2] * local_30 + param_2[5] * local_2c[0];
  param_1[3] = local_24[0] * *param_2 + param_2[6] * local_24[2] + param_2[3] * local_24[1];
  param_1[4] = param_2[4] * local_24[1] + param_2[1] * local_24[0] + param_2[7] * local_24[2];
  param_1[5] = param_2[8] * local_24[2] + param_2[2] * local_24[0] + param_2[5] * local_24[1];
  param_1[6] = local_18[0] * *param_2 + param_2[6] * local_18[2] + param_2[3] * local_18[1];
  param_1[7] = param_2[4] * local_18[1] + param_2[1] * local_18[0] + param_2[7] * local_18[2];
  param_1[8] = param_2[8] * local_18[2] + param_2[2] * local_18[0] + param_2[5] * local_18[1];
  param_1[9] = local_c[0] * *param_2 + param_2[6] * local_c[2] + param_2[3] * local_c[1] +
               param_2[9];
  param_1[10] = param_2[4] * local_c[1] + param_2[1] * local_c[0] + param_2[7] * local_c[2] +
                param_2[10];
  param_1[0xb] = param_2[8] * local_c[2] + param_2[2] * local_c[0] + param_2[5] * local_c[1] +
                 param_2[0xb];
  return;
}
#undef local_18
#undef local_24
#undef local_2c
#undef local_30
#undef local_c


/* ---- 0x0044fe50  Matrix_BuildTransform ---- */
/* Rotation then translation */

void Matrix_BuildTransform(float *param_1,undefined4 param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_30 (*(float (*)[12])(_frame + (0x40 - 0x30)))
  
  Angles_ToMatrixNoPos(local_30,param_2);
  Matrix_BuildRotation(param_1,local_30);
  return;
}
#undef local_30


/* ---- 0x0044fe80  Matrix_SetTranslation ---- */
void Matrix_SetTranslation(int param_1,float *param_2)

{
  *(float *)(param_1 + 0x24) = *param_2 + *(float *)(param_1 + 0x24);
  *(float *)(param_1 + 0x28) = param_2[1] + *(float *)(param_1 + 0x28);
  *(float *)(param_1 + 0x2c) = param_2[2] + *(float *)(param_1 + 0x2c);
  return;
}

/* ---- 0x0044feb0  Matrix_BuildTransform2 ---- */
void Matrix_BuildTransform2(float *param_1,undefined4 param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_30 (*(float (*)[12])(_frame + (0x40 - 0x30)))
  
  Matrix_BuildTranslation2(local_30,param_2);
  Matrix_BuildRotation(param_1,local_30);
  return;
}
#undef local_30


/* ---- 0x0044fee0  Vec3_Copy ---- */
void __cdecl Vec3_Copy(float *out,float *v,float *param_3)

{
  *out = *v * *param_3 + v[1] * param_3[3] + v[2] * param_3[6];
  out[1] = param_3[1] * *v + param_3[4] * v[1] + v[2] * param_3[7];
  out[2] = param_3[2] * *v + param_3[8] * v[2] + v[1] * param_3[5];
  return;
}

/* ---- 0x0044ff50  Vec3_TransformTo ---- */
void __cdecl Vec3_TransformTo(float *out,float *v,float *m)

{
  *out = *v * *m + v[1] * m[1] + v[2] * m[2];
  out[1] = m[3] * *v + m[4] * v[1] + v[2] * m[5];
  out[2] = m[6] * *v + m[8] * v[2] + v[1] * m[7];
  return;
}

/* ---- 0x0044ffc0  Vec3_Transform ---- */
/* Transforms the point in place by the 3x4 matrix */

void __cdecl Vec3_Transform(float *vec,float *m)

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


/* ---- 0x00450060  Vec3_Sub ---- */
void __cdecl Vec3_Sub(float *out,float *a,float *b)

{
  *out = *a * *b + a[1] * b[3] + a[2] * b[6] + b[9];
  out[1] = b[1] * *a + b[4] * a[1] + a[2] * b[7] + b[10];
  out[2] = b[2] * *a + b[8] * a[2] + a[1] * b[5] + b[0xb];
  return;
}

/* ---- 0x004500d0  Vec3_Rotate3x3 ---- */
/* Rotates the vector in place by the 3x3 part of the matrix */

void __cdecl Vec3_Rotate3x3(float *vec,float *m)

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


/* ---- 0x00450170  Matrix_TransformPoints ---- */
void __cdecl Matrix_TransformPoints(float *m,float *in,float *out,int count)

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

/* ---- 0x00450220  FUN_00450220 ---- */
undefined4 FUN_00450220(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0xffffffff;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  return 1;
}

/* ---- 0x00450260  FUN_00450260 ---- */
void FUN_00450260(int param_1)

{
  if (*(int *)(param_1 + 0x18) != 0) {
    (*g_pSvcRdroid->pFree)(*(int *)(param_1 + 0x18));
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    (*g_pSvcRdroid->pFree)(*(int *)(param_1 + 0x1c));
  }
  return;
}

/* ---- 0x00450290  Math3D_TriangleNormal ---- */
/* Normal of the triangle (p0,p1,p2) from the normalised edges p1-p0 and p2-p0, with tiny components
   zeroed. */

void Math3D_TriangleNormal(float *param_1,float *param_2,float *param_3,float *param_4)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float (*)[2])(_frame + (0x30 - 0x14)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float (*)[2])(_frame + (0x30 - 0x8)))
  
  local_c = *param_3 - *param_2;
  local_18 = *param_4 - *param_2;
  local_8[0] = param_3[1] - param_2[1];
  local_8[1] = param_3[2] - param_2[2];
  local_14[0] = param_4[1] - param_2[1];
  local_14[1] = param_4[2] - param_2[2];
  Vec3_Normalize(&local_c);
  Vec3_Normalize(&local_18);
  *param_1 = local_14[1] * local_8[0] - local_14[0] * local_8[1];
  param_1[1] = local_18 * local_8[1] - local_14[1] * local_c;
  param_1[2] = local_14[0] * local_c - local_18 * local_8[0];
  Vec3_Normalize(param_1);
  Vec3_ZeroSmallComponents(param_1,FBITS(0x358637bd));
  return;
}
#undef local_14
#undef local_18
#undef local_8
#undef local_c


/* ---- 0x00450380  Vec3_ZeroSmallComponents ---- */
/* Sets every component whose magnitude is below the epsilon argument to 0. */

void Vec3_ZeroSmallComponents(float *param_1,float param_2)

{
  float fVar1;
  
  fVar1 = *param_1;
  if (*param_1 < 0.0) {
    fVar1 = -fVar1;
  }
  if (param_2 <= fVar1) {
    fVar1 = *param_1;
  }
  else {
    fVar1 = 0.0;
  }
  *param_1 = fVar1;
  fVar1 = param_1[1];
  if (param_1[1] < 0.0) {
    fVar1 = -fVar1;
  }
  if (param_2 <= fVar1) {
    fVar1 = param_1[1];
  }
  else {
    fVar1 = 0.0;
  }
  param_1[1] = fVar1;
  fVar1 = param_1[2];
  if (param_1[2] < 0.0) {
    fVar1 = -fVar1;
  }
  if (fVar1 < param_2) {
    param_1[2] = 0.0;
    return;
  }
  param_1[2] = param_1[2];
  return;
}

/* ---- 0x00450410  Math3D_PointsCollinear ---- */
/* True when the normalised edges p1-p0 and p2-p0 are parallel (|dot| within 0.999..1.001). */

undefined4 Math3D_PointsCollinear(float *param_1,float *param_2,float *param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float (*)[2])(_frame + (0x30 - 0x14)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float (*)[2])(_frame + (0x30 - 0x8)))
  
  local_c = *param_2 - *param_1;
  local_18 = *param_3 - *param_1;
  local_8[0] = param_2[1] - param_1[1];
  local_8[1] = param_2[2] - param_1[2];
  local_14[0] = param_3[1] - param_1[1];
  local_14[1] = param_3[2] - param_1[2];
  Vec3_Normalize(&local_c);
  Vec3_Normalize(&local_18);
  fVar1 = local_14[1] * local_8[1] + local_14[0] * local_8[0] + local_18 * local_c;
  if (fVar1 < 0.0) {
    fVar1 = -fVar1;
  }
  if ((0.999 <= fVar1) && (fVar1 <= 1.001)) {
    return 1;
  }
  return 0;
}
#undef local_14
#undef local_18
#undef local_8
#undef local_c

