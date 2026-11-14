/* LUA.DLL :: math.c
 * functions 0x10006ea0 .. 0x10007300 (22 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10006ea0  math_abs ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua math library: abs(x) */

void __cdecl math_abs(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  uStack_4 = PUN(undefined4,(float)(luaL_check_number(1)));
  if (uStack_4 < 0.0) {
    uStack_4 = -uStack_4;
  }
  lua_pushnumber(PUN(float,uStack_4));
  return;
}
#undef uStack_4

#endif


/* ---- 0x10006ee0  math_sin ---- */
/* Lua math library: sin(degrees); the argument is converted to radians (x * pi / 180) */

void __cdecl math_sin(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = (float10)fsin((float10)fVar2 * (float10)0.017453292519943295);
  lua_pushnumber((float)fVar1);
  return;
}

/* ---- 0x10006f00  math_cos ---- */
/* Lua math library: cos(degrees) */

void __cdecl math_cos(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = (float10)fcos((float10)fVar2 * (float10)0.017453292519943295);
  lua_pushnumber((float)fVar1);
  return;
}

/* ---- 0x10006f20  math_tan ---- */
/* Lua math library: tan(degrees) */

void __cdecl math_tan(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = (float10)fptan((float10)fVar2 * (float10)0.017453292519943295);
  lua_pushnumber((float)fVar1);
  return;
}

/* ---- 0x10006f50  math_asin ---- */
/* Lua math library: asin(x) in degrees (CRT _CIasin, result * 180 / pi) */

void __cdecl math_asin(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = CI_ASIN((float10)fVar2);
  lua_pushnumber((float)(fVar1 * (float10)57.29577951308232));
  return;
}

/* ---- 0x10006f80  math_acos ---- */
/* Lua math library: acos(x) in degrees (CRT _CIacos, result * 180 / pi) */

void __cdecl math_acos(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = CI_ACOS((float10)fVar2);
  lua_pushnumber((float)(fVar1 * (float10)57.29577951308232));
  return;
}

/* ---- 0x10006fb0  math_atan ---- */
/* Lua math library: atan(x) in degrees (fpatan(x, 1) * 180 / pi) */

void __cdecl math_atan(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = (float10)fpatan((float10)fVar2,(float10)1);
  lua_pushnumber((float)(fVar1 * (float10)57.29577951308232));
  return;
}

/* ---- 0x10006fe0  math_atan2 ---- */
/* Lua math library: atan2(y, x) in degrees */

void __cdecl math_atan2(void)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  
  fVar2 = luaL_check_number(1);
  fVar3 = luaL_check_number(2);
  fVar1 = (float10)fpatan((float10)fVar2,(float10)fVar3);
  lua_pushnumber((float)(fVar1 * (float10)57.29577951308232));
  return;
}

/* ---- 0x10007020  math_ceil ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua math library: ceil(x) */

void __cdecl math_ceil(void)

{
  float fVar1;
  
  fVar1 = luaL_check_number(1);
  fVar1 = floor(SUB84((double)fVar1,0),(uint)((ulonglong)(double)fVar1 >> 0x20));
  lua_pushnumber(fVar1);
  return;
}
#endif


/* ---- 0x10007050  math_floor ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua math library: floor(x) */

void __cdecl math_floor(void)

{
  float fVar1;
  
  fVar1 = luaL_check_number(1);
  fVar1 = ceil(SUB84((double)fVar1,0),(uint)((ulonglong)(double)fVar1 >> 0x20));
  lua_pushnumber(fVar1);
  return;
}
#endif


/* ---- 0x10007080  math_mod ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua math library: mod(x, y) = fmod */

void __cdecl math_mod(void)

{
  undefined4 extraout_ECX;
  float n;
  
  luaL_check_number(1);
  luaL_check_number(2);
  n = FUN_100120fa(extraout_ECX);
  lua_pushnumber(n);
  return;
}
#endif


/* ---- 0x100070c0  math_sqrt ---- */
/* Lua math library: sqrt(x) */

void __cdecl math_sqrt(void)

{
  float fVar1;
  
  fVar1 = luaL_check_number(1);
  lua_pushnumber(SQRT(fVar1));
  return;
}

/* ---- 0x100070e0  math_pow ---- */
/* Lua math library: pow(x, y); also installed as the 'pow' tag method of numbers (the ^ operator)
    */

void __cdecl math_pow(void)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  
  fVar2 = luaL_check_number(1);
  fVar3 = luaL_check_number(2);
  fVar1 = CI_POW((float10)fVar2,(float10)fVar3);
  lua_pushnumber((float)fVar1);
  return;
}

/* ---- 0x10007120  math_log ---- */
/* Lua math library: log(x), natural logarithm */

void __cdecl math_log(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = (float10)log2((float10)fVar2);
  lua_pushnumber((float)((float10)0.6931471805599453 * fVar1));
  return;
}

/* ---- 0x10007140  math_log10 ---- */
/* Lua math library: log10(x) */

void __cdecl math_log10(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = (float10)log2((float10)fVar2);
  lua_pushnumber((float)((float10)0.3010299956639812 * fVar1));
  return;
}

/* ---- 0x10007160  math_exp ---- */
/* Lua math library: exp(x) */

void __cdecl math_exp(void)

{
  float10 fVar1;
  float10 fVar2;
  float fVar3;
  
  fVar3 = luaL_check_number(1);
  fVar1 = ROUND((float10)1.4426950408889634 * (float10)fVar3);
  fVar2 = (float10)f2xm1((float10)1.4426950408889634 * (float10)fVar3 - fVar1);
  fVar1 = (float10)fscale((float10)1 + fVar2,fVar1);
  lua_pushnumber((float)fVar1);
  return;
}

/* ---- 0x10007190  math_deg ---- */
/* Lua math library: deg(x), radians to degrees */

void __cdecl math_deg(void)

{
  float fVar1;
  
  fVar1 = luaL_check_number(1);
  lua_pushnumber(fVar1 * 57.29578);
  return;
}

/* ---- 0x100071b0  math_rad ---- */
/* Lua math library: rad(x), degrees to radians */

void __cdecl math_rad(void)

{
  float fVar1;
  
  fVar1 = luaL_check_number(1);
  lua_pushnumber(fVar1 * 0.017453292);
  return;
}

/* ---- 0x100071d0  math_min ---- */
/* Lua math library: min(x, ...) */

void __cdecl math_min(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  #define fStack_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  fStack_4 = luaL_check_number(1);
  iVar2 = 2;
  iVar1 = lua_lua2C(2);
  while (iVar1 != 0) {
    fVar3 = luaL_check_number(iVar2);
    if (fVar3 < fStack_4) {
      fStack_4 = fVar3;
    }
    iVar2 = iVar2 + 1;
    iVar1 = lua_lua2C(iVar2);
  }
  lua_pushnumber(fStack_4);
  return;
}
#undef fStack_4


/* ---- 0x10007230  math_max ---- */
/* Lua math library: max(x, ...) */

void __cdecl math_max(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  #define fStack_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  fStack_4 = luaL_check_number(1);
  iVar2 = 2;
  iVar1 = lua_lua2C(2);
  while (iVar1 != 0) {
    fVar3 = luaL_check_number(iVar2);
    if (fStack_4 < fVar3) {
      fStack_4 = fVar3;
    }
    iVar2 = iVar2 + 1;
    iVar1 = lua_lua2C(iVar2);
  }
  lua_pushnumber(fStack_4);
  return;
}
#undef fStack_4


/* ---- 0x10007290  math_random ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua math library: random() in [0,1) (rand() % 32767 / 32768), random(n) in [1,n] */

void __cdecl math_random(void)

{
  float n;
  uint uVar1;
  longlong lVar2;
  float fVar3;
  
  uVar1 = FUN_10012360();
  n = (float)((int)uVar1 % 0x7fff) * 3.051851e-05;
  fVar3 = luaL_opt_number(1,0.0);
  if ((float10)fVar3 == (float10)0.0) {
    lua_pushnumber(n);
    return;
  }
  lVar2 = FTOL((float10)fVar3 * (float10)n);
  lua_pushnumber((float)((int)lVar2 + 1));
  return;
}
#endif


/* ---- 0x10007300  math_randomseed ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua math library: randomseed(x), srand */

void __cdecl math_randomseed(void)

{
  longlong lVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  lVar1 = FTOL((float10)fVar2);
  FUN_10012350((int)lVar1);
  return;
}
#endif

