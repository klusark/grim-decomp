/* LUA.DLL :: lauxlib.c
 * functions 0x10002960 .. 0x10002cf0 (16 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10002960  lauxlib__2960 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of lauxlib.c (argument checking helpers) */

int __cdecl lauxlib__2960(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(DAT_1002beb8 + 0x38))(param_1,&param_1,1);
  if (iVar1 == 0) {
    return -1;
  }
  return (int)(char)param_1;
}
#endif


/* ---- 0x10002990  lauxlib__2990 ---- */
/* Unidentified function of lauxlib.c (argument checking helpers) */

int __cdecl lauxlib__2990(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if (param_1 == -1) {
    return -1;
  }
  iVar1 = (**(code **)(DAT_1002beb8 + 0x48))(param_2);
  iVar1 = (**(code **)(DAT_1002beb8 + 0x4c))(param_2,iVar1 + -1,0);
  if (iVar1 != 0) {
    return -1;
  }
  return param_1;
}

/* ---- 0x100029d0  luaL_argerror ---- */
/* lauxlib.c: bad argument #%d to function '%s' */

void __cdecl luaL_argerror(undefined4 param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined **ppuVar2;
  #define local_4 (*(undefined **)(_frame + (0x20 - 0x4)))
  
  ppuVar2 = &local_4;
  iVar1 = lua_stackedfunction(0);
  lua_getobjname(iVar1,ppuVar2);
  if (local_4 == (undefined *)0x0) {
    local_4 = &DAT_1002635c;
  }
  if (param_2 == 0) {
    luaL_verror(s_bad_argument___d_to_function_____10026334,param_1,local_4);
    return;
  }
  luaL_verror(s_bad_argument___d_to_function_____10026304,param_1,local_4,param_2);
  return;
}
#undef local_4


/* ---- 0x10002a30  luaL_check_string ---- */
/* lauxlib.c (argument checking helpers) */

int __cdecl luaL_check_string(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(param_1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 == 0) {
    luaL_argerror(param_1,IMG_ADDR(0x10026360));
  }
  iVar1 = lua_getstring(iVar1);
  return iVar1;
}

/* ---- 0x10002a70  luaL_opt_string ---- */
/* lauxlib.c (argument checking helpers) */

undefined4 __cdecl luaL_opt_string(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = lua_lua2C(param_1);
  if (iVar1 == 0) {
    return param_2;
  }
  uVar2 = luaL_check_string(param_1);
  return uVar2;
}

/* ---- 0x10002aa0  luaL_check_number ---- */
/* lauxlib.c (argument checking helpers) */

float __cdecl luaL_check_number(int param_1)

{
  int iVar1;
  int iVar2;
  float fVar3;
  
  iVar1 = lua_lua2C(param_1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    luaL_argerror(param_1,IMG_ADDR(0x10026370));
  }
  fVar3 = lua_getnumber(iVar1);
  return fVar3;
}

/* ---- 0x10002ae0  luaL_opt_number ---- */
/* lauxlib.c (argument checking helpers) */

float __cdecl luaL_opt_number(int param_1,float param_2)

{
  int iVar1;
  float fVar2;
  
  iVar1 = lua_lua2C(param_1);
  if (iVar1 == 0) {
    return param_2;
  }
  fVar2 = luaL_check_number(param_1);
  return fVar2;
}

/* ---- 0x10002b10  luaL_tablearg ---- */
/* lauxlib.c (argument checking helpers) */

int __cdecl luaL_tablearg(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(param_1);
  iVar2 = lua_istable(iVar1);
  if (iVar2 == 0) {
    luaL_argerror(param_1,IMG_ADDR(0x10026380));
  }
  return iVar1;
}

/* ---- 0x10002b50  luaL_functionarg ---- */
/* lauxlib.c (argument checking helpers) */

int __cdecl luaL_functionarg(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(param_1);
  iVar2 = lua_isfunction(iVar1);
  if (iVar2 == 0) {
    luaL_argerror(param_1,IMG_ADDR(0x10026390));
  }
  return iVar1;
}

/* ---- 0x10002b90  luaL_nonnullarg ---- */
/* lauxlib.c (argument checking helpers) */

int __cdecl luaL_nonnullarg(int param_1)

{
  int iVar1;
  
  iVar1 = lua_lua2C(param_1);
  if (iVar1 == 0) {
    luaL_argerror(param_1,IMG_ADDR(0x100263a4));
  }
  return iVar1;
}

/* ---- 0x10002bc0  luaL_openlib ---- */
/* lauxlib.c (argument checking helpers) */

void __cdecl luaL_openlib(undefined4 *param_1,int param_2)

{
  lua_open();
  lua_openlib(param_1,param_2);
  return;
}

/* ---- 0x10002be0  luaL_verror ---- */
/* lauxlib.c: formats the message then lua_error */

void __cdecl luaL_verror(char *fmt,...)

{
  unsigned char _frame[0x210];  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_1f4 (*(byte (*)[500])(_frame + (0x210 - 0x1f4)))
  
  vsprintf((char *)local_1f4,fmt,&STACK0X(0x00000008));
  lua_error(local_1f4);
  return;
}
#undef local_1f4


/* ---- 0x10002c20  luaL_openspace ---- */
/* Unidentified function of lbuffer.c (string buffer) */

int __cdecl luaL_openspace(int param_1)

{
  if (DAT_1002bf28 < (uint)(param_1 + DAT_1002bf4c)) {
    luaL_growbuffer(param_1);
  }
  return DAT_1002bf40 + DAT_1002bf4c;
}

/* ---- 0x10002c50  luaL_growbuffer ---- */
/* lbuffer.c: doubles the shared string buffer through the realloc service */

void __cdecl luaL_growbuffer(int param_1)

{
  int iVar1;
  
  DAT_1002bf28 = DAT_1002bf28 * 2;
  iVar1 = DAT_1002befc - DAT_1002bf40;
  if (DAT_1002bf28 < (uint)(param_1 + DAT_1002bf4c)) {
    DAT_1002bf28 = param_1 + DAT_1002bf4c;
  }
  DAT_1002bf40 = (**(code **)(DAT_1002beb8 + 0x28))
                           (DAT_1002bf40,DAT_1002bf28,s_C__grimsrc_libs_lua_src_lbuffer__100263b4,
                            0x1f);
  DAT_1002befc = iVar1 + DAT_1002bf40;
  return;
}

/* ---- 0x10002cb0  luaL_addchar ---- */
/* Unidentified function of lbuffer.c (string buffer) */

void __cdecl luaL_addchar(undefined1 param_1)

{
  if (DAT_1002bf28 < DAT_1002bf4c + 0x20U) {
    luaL_growbuffer(0x20);
  }
  *(undefined1 *)(DAT_1002bf4c + DAT_1002bf40) = param_1;
  DAT_1002bf4c = DAT_1002bf4c + 1;
  return;
}

/* ---- 0x10002cf0  luaL_resetbuffer ---- */
/* Unidentified function of lbuiltin.c (built-in functions) */

void luaL_resetbuffer(void)

{
  DAT_1002bf4c = DAT_1002befc - DAT_1002bf40;
  return;
}
