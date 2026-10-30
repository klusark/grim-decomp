/* GRIMFANDANGO.EXE :: math.c
 * functions 0x004735d0 .. 0x0047c5f0 (11 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004735d0  Math_Log2Int ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
int __cdecl Math_Log2Int(int n)

{
  int iVar1;
  
  iVar1 = 0;
  for (; 1 < n; n = n >> 1) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}
#endif


/* ---- 0x0047bbe0  Math_PowInt ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
float __cdecl Math_PowInt(float x,int n)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  local_8 = PUN(uint,(float)x);
  for (local_c = 0; (int)local_c < n + -1; local_c = local_c + 1) {
    local_8 = PUN(uint,(float)(PUN(float,local_8) * x));
  }
  return PUN(float,local_8);
}
#undef local_8
#undef local_c

#endif


/* ---- 0x0047bc20  Math_NormalizeAngle360 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_1c */

float __cdecl Math_NormalizeAngle360(float degrees)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  if (0.0 <= degrees) {
    if (degrees < 360.0) {
      return degrees;
    }
    fVar2 = Math_Round(degrees / 360.0);
    local_c = PUN(uint,(float)(degrees - fVar2 * 360.0));
  }
  else {
    fVar2 = -degrees;
    if (360.0 <= fVar2) {
      fVar1 = Math_Round(fVar2 / 360.0);
      fVar2 = fVar2 - fVar1 * 360.0;
    }
    local_c = PUN(uint,(float)(360.0 - fVar2));
  }
  if (local_c == 0x43b40000) {
    local_c = 0;
  }
  return PUN(float,local_c);
}
#undef local_10
#undef local_1c
#undef local_8
#undef local_c

#endif


/* ---- 0x0047bce0  Math_NormalizeAngle180 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
float __cdecl Math_NormalizeAngle180(float param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  local_8 = PUN(uint,(float)Math_NormalizeAngle360(param_1));
  if (180.0 < PUN(float,local_8)) {
    local_8 = PUN(uint,(float)-(360.0 - PUN(float,local_8)));
  }
  return PUN(float,local_8);
}
#undef local_8

#endif


/* ---- 0x0047bd20  Math_SinCosTable ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Math_SinCosTable(deg, &sin, &cos): 4096-entry quarter table, interpolated, per quadrant. Some
   quadrant indexes are one entry (90/4096 = 0.022 deg) off: a walker heading turned by a small
   negative angle turns 0.022 deg less (TurnActorTo right: 1.4229 instead of 1.445 at rate 85, 17
   ms). */

void Math_SinCosTable(float param_1,float *param_2,float *param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  float fVar5;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define uStack_2c (*(undefined4 *)(_frame + (0x40 - 0x2c)))
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
  fVar5 = Math_Round(fVar4 * 45.511112);
  fVar5 = fVar4 * 45.511112 - fVar5;
  lVar3 = _ftol((double)CONCAT44(uStack_2c,local_30));
  iVar1 = (int)lVar3;
  iVar2 = iVar1 + 1;
  switch(local_1c) {
  case 0:
    if (iVar2 < 0x1000) {
      local_8 = *(uint *)(&DAT_004df600 + iVar2 * 4);
    }
    else {
      local_8 = *(uint *)(&DAT_004df600 + (0xfff - (iVar1 + -0xfff)) * 4);
    }
    *param_2 = (PUN(float,local_8) - *(float *)(&DAT_004df600 + iVar1 * 4)) * fVar5 +
               *(float *)(&DAT_004df600 + iVar1 * 4);
    if (iVar2 < 0x1000) {
      local_8 = *(uint *)(&DAT_004df600 + (0xfff - iVar2) * 4);
    }
    else {
      local_8 = PUN(uint,(float)-*(float *)("DialogBoxIndirectParamA" + iVar2 * 4 + 2));
    }
    *param_3 = (PUN(float,local_8) - *(float *)(&DAT_004df600 + (0xfff - iVar1) * 4)) * fVar5 +
               *(float *)(&DAT_004df600 + (0xfff - iVar1) * 4);
    break;
  case 1:
    if (iVar2 < 0x2000) {
      local_8 = *(uint *)(&DAT_004df600 + (0xfff - (iVar1 + -0xfff)) * 4);
    }
    else {
      local_8 = PUN(uint,(float)-*(float *)(&DAT_004d7600 + iVar2 * 4));
    }
    *param_2 = (PUN(float,local_8) - *(float *)(&DAT_004df600 + (0xfff - (iVar1 + -0x1000)) * 4)) *
               fVar5 + *(float *)(&DAT_004df600 + (0xfff - (iVar1 + -0x1000)) * 4);
    if (iVar2 < 0x2000) {
      fVar4 = *(float *)("DialogBoxIndirectParamA" + iVar2 * 4 + 2);
    }
    else {
      fVar4 = *(float *)(&DAT_004df600 + (0xfff - (iVar1 + -0x1fff)) * 4);
    }
    local_8 = PUN(uint,(float)-fVar4);
    *param_3 = (PUN(float,local_8) - -*(float *)("DialogBoxIndirectParamA" + iVar1 * 4 + 2)) * fVar5 +
               -*(float *)("DialogBoxIndirectParamA" + iVar1 * 4 + 2);
    break;
  case 2:
    if (iVar2 < 0x3000) {
      fVar4 = *(float *)(&DAT_004d7600 + iVar2 * 4);
    }
    else {
      fVar4 = *(float *)(&DAT_004df600 + (0xfff - (iVar1 + -0x2fff)) * 4);
    }
    local_8 = PUN(uint,(float)-fVar4);
    *param_2 = (PUN(float,local_8) - -*(float *)(&DAT_004d7600 + iVar1 * 4)) * fVar5 +
               -*(float *)(&DAT_004d7600 + iVar1 * 4);
    if (iVar2 < 0x3000) {
      local_8 = PUN(uint,(float)-*(float *)(&DAT_004df600 + (0xfff - (iVar1 + -0x1fff)) * 4));
    }
    else {
      local_8 = *(uint *)(iVar2 * 4 + 0x4d3600);
    }
    *param_3 = (PUN(float,local_8) - -*(float *)(&DAT_004df600 + (0xfff - (iVar1 + -0x2000)) * 4)) *
               fVar5 + -*(float *)(&DAT_004df600 + (0xfff - (iVar1 + -0x2000)) * 4);
    break;
  case 3:
    if (iVar2 < 0x4000) {
      local_8 = PUN(uint,(float)-*(float *)(&DAT_004df600 + (0xfff - (iVar1 + -0x2fff)) * 4));
    }
    else {
      local_8 = *(uint *)(iVar2 * 4 + 0x4cf600);
    }
    *param_2 = (PUN(float,local_8) - -*(float *)(&DAT_004df600 + (0xfff - (iVar1 + -0x3000)) * 4)) *
               fVar5 + -*(float *)(&DAT_004df600 + (0xfff - (iVar1 + -0x3000)) * 4);
    fVar4 = *(float *)(iVar1 * 4 + 0x4d3600);
    if (iVar2 < 0x4000) {
      local_8 = *(uint *)(iVar2 * 4 + 0x4d3600);
    }
    else {
      local_8 = *(uint *)(&DAT_004df600 + (0xfff - (iVar1 + -0x3fff)) * 4);
    }
    *param_3 = (PUN(float,local_8) - fVar4) * fVar5 + fVar4;
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
#undef uStack_2c

#endif


/* ---- 0x0047c100  Math_Round ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
float __cdecl Math_Round(float param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  return ROUND(param_1);
}
#undef local_8

#endif


/* ---- 0x0047c120  Math_SinDeg ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Table/polynomial sine of an angle in degrees */

float10 Math_SinDeg(float param_1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  float fVar5;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define uStack_2c (*(undefined4 *)(_frame + (0x40 - 0x2c)))
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
  fVar5 = Math_Round(fVar4);
  fVar4 = fVar4 - fVar5;
  lVar3 = _ftol((double)CONCAT44(uStack_2c,local_30));
  iVar1 = (int)lVar3;
  iVar2 = iVar1 + 1;
  switch(local_1c) {
  case 0:
    if (iVar2 < 0x1000) {
      local_8 = *(uint *)(&DAT_004e3600 + iVar2 * 4);
    }
    else {
      local_8 = PUN(uint,(float)-*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0xfff)) * 4));
    }
    local_10 = PUN(uint,(float)((PUN(float,local_8) - *(float *)(&DAT_004e3600 + iVar1 * 4)) * fVar4 +
                     *(float *)(&DAT_004e3600 + iVar1 * 4)));
    break;
  case 1:
    if (iVar2 < 0x2000) {
      local_8 = PUN(uint,(float)-*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0xfff)) * 4));
    }
    else {
      local_8 = *(uint *)("DialogBoxIndirectParamA" + iVar2 * 4 + 2);
    }
    local_10 = PUN(uint,(float)((PUN(float,local_8) - -*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0x1000)) * 4)
                      ) * fVar4 + -*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0x1000)) * 4)));
    break;
  case 2:
    if (iVar2 < 0x3000) {
      local_8 = *(uint *)("DialogBoxIndirectParamA" + iVar2 * 4 + 2);
    }
    else {
      local_8 = PUN(uint,(float)-*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0x2fff)) * 4));
    }
    local_10 = PUN(uint,(float)((PUN(float,local_8) - *(float *)("DialogBoxIndirectParamA" + iVar1 * 4 + 2)) *
                      fVar4 + *(float *)("DialogBoxIndirectParamA" + iVar1 * 4 + 2)));
    break;
  case 3:
    if (iVar2 < 0x4000) {
      local_8 = PUN(uint,(float)-*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0x2fff)) * 4));
    }
    else {
      local_8 = *(uint *)(iVar2 * 4 + 0x4d3600);
    }
    local_10 = PUN(uint,(float)((PUN(float,local_8) - -*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0x3000)) * 4)
                      ) * fVar4 + -*(float *)(&DAT_004e3600 + (0xfff - (iVar1 + -0x3000)) * 4)));
  }
  return (float10)PUN(float,local_10);
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
#undef uStack_2c

#endif


/* ---- 0x0047c3b0  Math_AsinDegrees ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_18 */

float __cdecl Math_AsinDegrees(float x)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  if (0.0 <= x) {
    local_14 = PUN(uint,(float)x);
  }
  else {
    local_14 = PUN(uint,(float)-x);
  }
  if (PUN(float,local_14) <= 0.70710677) {
    fVar1 = Math_PowInt(PUN(float,local_14),3);
    local_8 = PUN(uint,(float)((fVar1 * 0.212749 + PUN(float,local_14)) * 57.295784));
  }
  else {
    fVar1 = Math_Sqrt(1.0 - PUN(float,local_14) * PUN(float,local_14));
    fVar2 = Math_PowInt(fVar1,3);
    local_8 = PUN(uint,(float)(90.0 - (fVar2 * 0.212749 + fVar1) * 57.295784));
  }
  if (0.0 > x) {
    local_8 = PUN(uint,(float)-PUN(float,local_8));
  }
  return PUN(float,local_8);
}
#undef local_10
#undef local_14
#undef local_18
#undef local_8
#undef local_c

#endif


/* ---- 0x0047c490  Math_Sqrt ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
float __cdecl Math_Sqrt(float param_1)

{
  return SQRT(param_1);
}
#endif


/* ---- 0x0047c4a0  Math_AsinDegreesSeries ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_28 */

float __cdecl Math_AsinDegreesSeries(float param_1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
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
    local_14 = PUN(uint,(float)param_1);
  }
  else {
    local_14 = PUN(uint,(float)-param_1);
  }
  if (PUN(float,local_14) <= 0.70710677) {
    fVar1 = Math_PowInt(PUN(float,local_14),3);
    fVar2 = Math_PowInt(PUN(float,local_14),5);
    fVar3 = Math_PowInt(PUN(float,local_14),7);
    local_8 = PUN(uint,(float)((fVar3 * 0.066797 + fVar2 * 0.075 + fVar1 / 6.0 + PUN(float,local_14)) * 57.295784))
    ;
  }
  else {
    fVar1 = Math_Sqrt(1.0 - PUN(float,local_14) * PUN(float,local_14));
    fVar2 = Math_PowInt(fVar1,3);
    fVar3 = Math_PowInt(fVar1,5);
    fVar4 = Math_PowInt(fVar1,7);
    local_8 = PUN(uint,(float)(90.0 - (fVar4 * 0.066797 + fVar3 * 0.075 + fVar2 / 6.0 + fVar1) * 57.295784));
  }
  if (0.0 > param_1) {
    local_8 = PUN(uint,(float)-PUN(float,local_8));
  }
  return PUN(float,local_8);
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

#endif


/* ---- 0x0047c5f0  Math_Atan2Deg ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
      local_1c = PUN(uint,(float)y);
    }
    else {
      local_1c = PUN(uint,(float)-y);
    }
    if (0.0 <= x) {
      local_24 = PUN(uint,(float)x);
    }
    else {
      local_24 = PUN(uint,(float)-x);
    }
    if (PUN(float,local_24) <= PUN(float,local_1c)) {
      local_8 = PUN(uint,(float)(PUN(float,local_24) / PUN(float,local_1c)));
    }
    else {
      local_8 = PUN(uint,(float)(PUN(float,local_1c) / PUN(float,local_24)));
    }
    if (0.0 <= PUN(float,local_8)) {
      local_28 = local_8;
    }
    else {
      local_28 = PUN(uint,(float)-PUN(float,local_8));
    }
    fVar1 = Math_PowInt(PUN(float,local_28),3);
    fVar2 = Math_PowInt(PUN(float,local_28),5);
    fVar3 = Math_PowInt(PUN(float,local_28),7);
    fVar4 = Math_PowInt(PUN(float,local_28),9);
    local_c = PUN(uint,(float)((fVar4 * 0.063235 +
                     ((fVar2 / 5.0 + (PUN(float,local_28) - fVar1 / 3.0)) - fVar3 / 7.0)) * 57.295784));
    if (PUN(float,local_24) <= PUN(float,local_1c)) {
      local_c = PUN(uint,(float)(90.0 - PUN(float,local_c)));
    }
    local_c = PUN(uint,(float)(90.0 - PUN(float,local_c)));
    if (y < 0.0) {
      local_c = PUN(uint,(float)(180.0 - PUN(float,local_c)));
    }
    if (0.0 <= x) {
      local_c = PUN(uint,(float)-PUN(float,local_c));
    }
  }
  return PUN(float,local_c);
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

#endif

