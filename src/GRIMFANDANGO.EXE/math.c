/* GRIMFANDANGO.EXE :: math.c
 * functions 0x004735d0 .. 0x0047c8c0 (14 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004735d0  Math_Log2Int ---- */
int __cdecl Math_Log2Int(int n)

{
  int iVar1;
  
  iVar1 = 0;
  for (; 1 < n; n = n >> 1) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

/* ---- 0x0047bbe0  Math_PowInt ---- */
float __cdecl Math_PowInt(float x,int n)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  local_8 = (uint)x;
  for (local_c = 0; (int)local_c < n + -1; local_c = local_c + 1) {
    local_8 = (uint)((float)local_8 * x);
  }
  return (float)local_8;
}
#undef local_8
#undef local_c


/* ---- 0x0047bc20  Math_NormalizeAngle360 ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */

float __cdecl Math_NormalizeAngle360(float degrees)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float10 fVar2;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  if (0.0 <= degrees) {
    if (degrees < 360.0) {
      return degrees;
    }
    fVar2 = (float10)Math_Round(degrees / 360.0);
    local_c = (uint)(float)((float10)degrees - fVar2 * (float10)360.0);
  }
  else {
    fVar1 = -degrees;
    if (360.0 <= fVar1) {
      fVar2 = (float10)Math_Round(fVar1 / 360.0);
      local_c = (uint)(float)((float10)360.0 - ((float10)fVar1 - fVar2 * (float10)360.0));
    }
    else {
      local_c = (uint)(360.0 - fVar1);
    }
  }
  if (local_c == 0x43b40000) {
    local_c = 0;
  }
  return (float)local_c;
}
#undef local_10
#undef local_1c
#undef local_8
#undef local_c


/* ---- 0x0047bce0  Math_NormalizeAngle180 ---- */
float10 Math_NormalizeAngle180(float param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  local_8 = (uint)Math_NormalizeAngle360(param_1);
  if (180.0 < (float)local_8) {
    local_8 = (uint)-(360.0 - (float)local_8);
  }
  return (float10)(float)local_8;
}
#undef local_8


/* ---- 0x0047bd20  Math_SinCosTable ---- */
/* Math_SinCosTable(deg, &sin, &cos): 4096-entry quarter table, interpolated, per quadrant. Some
   quadrant indexes are one entry (90/4096 = 0.022 deg) off: a walker heading turned by a small
   negative angle turns 0.022 deg less (TurnActorTo right: 1.4229 instead of 1.445 at rate 85, 17
   ms). */

void Math_SinCosTable(float param_1,float *param_2,float *param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  float fVar5;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  
  fVar5 = Math_NormalizeAngle360(param_1);
  if (90.0 <= fVar5) {
    if (180.0 <= fVar5) {
      if (270.0 <= fVar5) {
        local_1c = 3;
      }
      else {
        local_1c = 2;
      }
    }
    else {
      local_1c = 1;
    }
  }
  else {
    local_1c = 0;
  }
  fVar4 = (float10)Math_Round(fVar5 * 45.511112);
  fVar5 = (float)((float10)(fVar5 * 45.511112) - fVar4);
  iVar2 = _ftol();
  iVar3 = iVar2 + 1;
  switch(local_1c) {
  case 0:
    if (iVar3 < 0x1000) {
      local_8 = *(uint *)(&DAT_004df600 + iVar3 * 4);
    }
    else {
      local_8 = *(uint *)(&DAT_004df600 + (0xfff - (iVar2 + -0xfff)) * 4);
    }
    *param_2 = ((float)local_8 - *(float *)(&DAT_004df600 + iVar2 * 4)) * fVar5 +
               *(float *)(&DAT_004df600 + iVar2 * 4);
    if (iVar3 < 0x1000) {
      local_8 = *(uint *)(&DAT_004df600 + (0xfff - iVar3) * 4);
    }
    else {
      local_8 = (uint)-*(float *)("DialogBoxIndirectParamA" + iVar3 * 4 + 2);
    }
    *param_3 = ((float)local_8 - *(float *)(&DAT_004df600 + (0xfff - iVar2) * 4)) * fVar5 +
               *(float *)(&DAT_004df600 + (0xfff - iVar2) * 4);
    break;
  case 1:
    if (iVar3 < 0x2000) {
      local_8 = *(uint *)(&DAT_004df600 + (0xfff - (iVar2 + -0xfff)) * 4);
    }
    else {
      local_8 = (uint)-*(float *)(&DAT_004d7600 + iVar3 * 4);
    }
    *param_2 = ((float)local_8 - *(float *)(&DAT_004df600 + (0xfff - (iVar2 + -0x1000)) * 4)) *
               fVar5 + *(float *)(&DAT_004df600 + (0xfff - (iVar2 + -0x1000)) * 4);
    if (iVar3 < 0x2000) {
      fVar1 = *(float *)("DialogBoxIndirectParamA" + iVar3 * 4 + 2);
    }
    else {
      fVar1 = *(float *)(&DAT_004df600 + (0xfff - (iVar2 + -0x1fff)) * 4);
    }
    local_8 = (uint)-fVar1;
    *param_3 = ((float)local_8 - -*(float *)("DialogBoxIndirectParamA" + iVar2 * 4 + 2)) * fVar5 +
               -*(float *)("DialogBoxIndirectParamA" + iVar2 * 4 + 2);
    break;
  case 2:
    if (iVar3 < 0x3000) {
      fVar1 = *(float *)(&DAT_004d7600 + iVar3 * 4);
    }
    else {
      fVar1 = *(float *)(&DAT_004df600 + (0xfff - (iVar2 + -0x2fff)) * 4);
    }
    local_8 = (uint)-fVar1;
    *param_2 = ((float)local_8 - -*(float *)(&DAT_004d7600 + iVar2 * 4)) * fVar5 +
               -*(float *)(&DAT_004d7600 + iVar2 * 4);
    if (iVar3 < 0x3000) {
      local_8 = (uint)-*(float *)(&DAT_004df600 + (0xfff - (iVar2 + -0x1fff)) * 4);
    }
    else {
      local_8 = *(uint *)(iVar3 * 4 + 0x4d3600);
    }
    *param_3 = ((float)local_8 - -*(float *)(&DAT_004df600 + (0xfff - (iVar2 + -0x2000)) * 4)) *
               fVar5 + -*(float *)(&DAT_004df600 + (0xfff - (iVar2 + -0x2000)) * 4);
    break;
  case 3:
    if (iVar3 < 0x4000) {
      local_8 = (uint)-*(float *)(&DAT_004df600 + (0xfff - (iVar2 + -0x2fff)) * 4);
    }
    else {
      local_8 = *(uint *)(iVar3 * 4 + 0x4cf600);
    }
    *param_2 = ((float)local_8 - -*(float *)(&DAT_004df600 + (0xfff - (iVar2 + -0x3000)) * 4)) *
               fVar5 + -*(float *)(&DAT_004df600 + (0xfff - (iVar2 + -0x3000)) * 4);
    fVar1 = *(float *)(iVar2 * 4 + 0x4d3600);
    if (iVar3 < 0x4000) {
      local_8 = *(uint *)(iVar3 * 4 + 0x4d3600);
    }
    else {
      local_8 = *(uint *)(&DAT_004df600 + (0xfff - (iVar2 + -0x3fff)) * 4);
    }
    *param_3 = ((float)local_8 - fVar1) * fVar5 + fVar1;
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_30
#undef local_8
#undef local_c


/* ---- 0x0047c100  Math_Round ---- */
float10 Math_Round(float param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  return (float10)ROUND(param_1);
}
#undef local_8


/* ---- 0x0047c120  Math_SinDeg ---- */
/* Table/polynomial sine of an angle in degrees */

float10 Math_SinDeg(float param_1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float10 fVar3;
  float fVar4;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  
  fVar4 = Math_NormalizeAngle360(param_1);
  if (90.0 <= fVar4) {
    if (180.0 <= fVar4) {
      if (270.0 <= fVar4) {
        local_1c = 3;
      }
      else {
        local_1c = 2;
      }
    }
    else {
      local_1c = 1;
    }
  }
  else {
    local_1c = 0;
  }
  fVar4 = (fVar4 / 360.0) * 16384.0;
  fVar3 = (float10)Math_Round(fVar4);
  fVar4 = (float)((float10)fVar4 - fVar3);
  iVar1 = _ftol();
  iVar2 = iVar1 + 1;
  switch(local_1c) {
  case 0:
    if (iVar2 < 0x1000) {
      local_8 = *(uint *)(&DAT_004e3600 + iVar2 * 4);
    }
    else {
      local_8 = (uint)-*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0xfff)) * 4);
    }
    local_10 = (uint)(((float)local_8 - *(float *)(&DAT_004e3600 + iVar1 * 4)) * fVar4 +
                     *(float *)(&DAT_004e3600 + iVar1 * 4));
    break;
  case 1:
    if (iVar2 < 0x2000) {
      local_8 = (uint)-*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0xfff)) * 4);
    }
    else {
      local_8 = *(uint *)("DialogBoxIndirectParamA" + iVar2 * 4 + 2);
    }
    local_10 = (uint)(((float)local_8 - -*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0x1000)) * 4)
                      ) * fVar4 + -*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0x1000)) * 4));
    break;
  case 2:
    if (iVar2 < 0x3000) {
      local_8 = *(uint *)("DialogBoxIndirectParamA" + iVar2 * 4 + 2);
    }
    else {
      local_8 = (uint)-*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0x2fff)) * 4);
    }
    local_10 = (uint)(((float)local_8 - *(float *)("DialogBoxIndirectParamA" + iVar1 * 4 + 2)) *
                      fVar4 + *(float *)("DialogBoxIndirectParamA" + iVar1 * 4 + 2));
    break;
  case 3:
    if (iVar2 < 0x4000) {
      local_8 = (uint)-*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0x2fff)) * 4);
    }
    else {
      local_8 = *(uint *)(iVar2 * 4 + 0x4d3600);
    }
    local_10 = (uint)(((float)local_8 - -*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0x3000)) * 4)
                      ) * fVar4 + -*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0x3000)) * 4));
  }
  return (float10)(float)local_10;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_30
#undef local_8
#undef local_c


/* ---- 0x0047c3b0  Math_AsinDegrees ---- */
/* WARNING: Variable defined which should be unmapped: local_18 */

float __cdecl Math_AsinDegrees(float x)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float10 fVar1;
  float fVar2;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  if (0.0 <= x) {
    local_14 = (uint)x;
  }
  else {
    local_14 = (uint)-x;
  }
  if ((float)local_14 <= 0.70710677) {
    fVar2 = Math_PowInt((float)local_14,3);
    local_8 = (uint)((fVar2 * 0.212749 + (float)local_14) * 57.295784);
  }
  else {
    fVar1 = (float10)Math_Sqrt(1.0 - (float)local_14 * (float)local_14);
    fVar2 = Math_PowInt((float)fVar1,3);
    local_8 = (uint)(90.0 - (fVar2 * 0.212749 + (float)fVar1) * 57.295784);
  }
  if (0.0 > x) {
    local_8 = (uint)-(float)local_8;
  }
  return (float)local_8;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_8
#undef local_c


/* ---- 0x0047c490  Math_Sqrt ---- */
float10 Math_Sqrt(float param_1)

{
  return SQRT((float10)param_1);
}

/* ---- 0x0047c4a0  Math_AsinDegreesSeries ---- */
/* WARNING: Variable defined which should be unmapped: local_28 */

float10 Math_AsinDegreesSeries(float param_1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float10 fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  
  if (0.0 <= param_1) {
    local_14 = (uint)param_1;
  }
  else {
    local_14 = (uint)-param_1;
  }
  if ((float)local_14 <= 0.70710677) {
    fVar5 = Math_PowInt((float)local_14,3);
    fVar2 = Math_PowInt((float)local_14,5);
    fVar3 = Math_PowInt((float)local_14,7);
    local_8 = (uint)((fVar3 * 0.066797 + fVar2 * 0.075 + fVar5 / 6.0 + (float)local_14) * 57.295784)
    ;
  }
  else {
    fVar1 = (float10)Math_Sqrt(1.0 - (float)local_14 * (float)local_14);
    fVar5 = (float)fVar1;
    fVar2 = Math_PowInt(fVar5,3);
    fVar3 = Math_PowInt(fVar5,5);
    fVar4 = Math_PowInt(fVar5,7);
    local_8 = (uint)(90.0 - (fVar4 * 0.066797 + fVar3 * 0.075 + fVar2 / 6.0 + fVar5) * 57.295784);
  }
  if (0.0 <= param_1) {
    fVar1 = (float10)(float)local_8;
  }
  else {
    fVar1 = -(float10)(float)local_8;
  }
  return fVar1;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_8
#undef local_c


/* ---- 0x0047c5f0  Math_Atan2Deg ---- */
float __cdecl Math_Atan2Deg(float y,float x)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x50 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x50 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x50 - 0x8)))
  
  if ((x == 0.0) && (y == 0.0)) {
    local_c = 0;
  }
  else {
    if (0.0 <= y) {
      local_1c = (uint)y;
    }
    else {
      local_1c = (uint)-y;
    }
    if (0.0 <= x) {
      local_24 = (uint)x;
    }
    else {
      local_24 = (uint)-x;
    }
    if ((float)local_24 <= (float)local_1c) {
      local_8 = (uint)((float)local_24 / (float)local_1c);
    }
    else {
      local_8 = (uint)((float)local_1c / (float)local_24);
    }
    if (0.0 <= (float)local_8) {
      local_28 = local_8;
    }
    else {
      local_28 = (uint)-(float)local_8;
    }
    fVar1 = Math_PowInt((float)local_28,3);
    fVar2 = Math_PowInt((float)local_28,5);
    fVar3 = Math_PowInt((float)local_28,7);
    fVar4 = Math_PowInt((float)local_28,9);
    local_c = (uint)((fVar4 * 0.063235 +
                     ((fVar2 / 5.0 + ((float)local_28 - fVar1 / 3.0)) - fVar3 / 7.0)) * 57.295784);
    if ((float)local_24 <= (float)local_1c) {
      local_c = (uint)(90.0 - (float)local_c);
    }
    local_c = (uint)(90.0 - (float)local_c);
    if (y < 0.0) {
      local_c = (uint)(180.0 - (float)local_c);
    }
    if (0.0 <= x) {
      local_c = (uint)-(float)local_c;
    }
  }
  return (float)local_c;
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
#undef local_8
#undef local_c


/* ---- 0x0047c7c0  FUN_0047c7c0 ---- */
void FUN_0047c7c0(undefined4 param_1)

{
  FUN_0047c7e0(param_1,&DAT_004dda54);
  return;
}

/* ---- 0x0047c7e0  FUN_0047c7e0 ---- */
undefined4 FUN_0047c7e0(byte *param_1,undefined4 param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  bool bVar5;
  
  if (UINT_0080cbcc != 0) {
    FUN_0047ca00();
  }
  pbVar4 = &DAT_004e7630;
  pbVar2 = param_1;
  do {
    bVar1 = *pbVar2;
    bVar5 = bVar1 < *pbVar4;
    if (bVar1 != *pbVar4) {
LAB_0047c822:
      iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
      goto LAB_0047c827;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar2[1];
    bVar5 = bVar1 < pbVar4[1];
    if (bVar1 != pbVar4[1]) goto LAB_0047c822;
    pbVar2 = pbVar2 + 2;
    pbVar4 = pbVar4 + 2;
  } while (bVar1 != 0);
  iVar3 = 0;
LAB_0047c827:
  if (iVar3 == 0) {
    UINT_0080cbd0 = 0;
  }
  else {
    UINT_0080cbd0 = (*g_pSvcMain->pFopen)(param_1,param_2);
    if ((int)UINT_0080cbd0 < 1) {
      UINT_0080cbd0 = 0;
      if (UINT_0080cbcc != 0) {
        FUN_0047ca90();
      }
      return 0;
    }
  }
  UINT_00900520 =
       (*g_pSvcMain->pAlloc)(0x400,s_C__grimjedi_Libs_Std_General_Std_004e7604,DAT_004e7600 + 0x1d);
  strncpy(&DAT_009004a0,param_1,0x7f);
  DAT_0090051f = 0;
  UINT_0080cbc8 = 0;
  UINT_0080cbcc = 1;
  return 1;
}

/* ---- 0x0047c8c0  FUN_0047c8c0 ---- */
void FUN_0047c8c0(void)

{
  if (UINT_0080cbcc != 0) {
    if (UINT_0080cbd0 != 0) {
      (*g_pSvcMain->pFclose)(UINT_0080cbd0);
    }
    UINT_0080cbd0 = 0;
    (*g_pSvcMain->pFree)(UINT_00900520);
    if (UINT_0080cbd8 != 0) {
      FUN_0047ca90();
      return;
    }
    UINT_0080cbcc = 0;
  }
  return;
}
