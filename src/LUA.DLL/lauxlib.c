/* LUA.DLL :: lauxlib.c
 * functions 0x10002960 .. 0x10002cf0 (16 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10002960  luaFGetc ---- */
/* Original name luaFGetc (the remaster's libLua.so: reads one char through the service table +0x38,
   -1 at the end); was lauxlib__2960. */

int __cdecl luaFGetc(undefined4 f)

{
  int iVar1;
  
  iVar1 = (**(code **)(g_dwLuaHS + 0x38))(f,&f,1);
  if (iVar1 == 0) {
    return -1;
  }
  return (int)(char)f;
}

/* ---- 0x10002990  luaFUngetc ---- */
/* Original name luaFUngetc (the remaster's libLua.so: -1 stays -1, otherwise seeks back one
   character (service +0x48 / +0x4c)); was lauxlib__2990. */

int __cdecl luaFUngetc(int c,undefined4 f)

{
  int iVar1;
  
  if (c == -1) {
    return -1;
  }
  iVar1 = (**(code **)(g_dwLuaHS + 0x48))(f);
  iVar1 = (**(code **)(g_dwLuaHS + 0x4c))(f,iVar1 + -1,0);
  if (iVar1 != 0) {
    return -1;
  }
  return c;
}

/* ---- 0x100029d0  luaL_argerror ---- */
/* lauxlib.c: bad argument #%d to function '%s' */

void __cdecl luaL_argerror(undefined4 numarg,int extramsg)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int o;
  undefined **name;
  #define local_4 (*(undefined **)(_frame + (0x20 - 0x4)))
  
  name = &local_4;
  o = lua_stackedfunction(0);
  lua_getobjname(o,name);
  if (local_4 == (undefined *)0x0) {
    local_4 = &DAT_1002635c;
  }
  if (extramsg == 0) {
    luaL_verror(s_bad_argument___d_to_function_____10026334,numarg,local_4);
    return;
  }
  luaL_verror(s_bad_argument___d_to_function_____10026304,numarg,local_4,extramsg);
  return;
}
#undef local_4


/* ---- 0x10002a30  luaL_check_string ---- */
/* lauxlib.c (argument checking helpers) */

int __cdecl luaL_check_string(int numArg)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(numArg);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 == 0) {
    luaL_argerror(numArg,((unsigned)(uintptr_t)&s_string_expected_10026360));
  }
  iVar1 = lua_getstring(iVar1);
  return iVar1;
}

/* ---- 0x10002a70  luaL_opt_string ---- */
/* lauxlib.c (argument checking helpers) */

undefined4 __cdecl luaL_opt_string(int numArg,undefined4 def)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = lua_lua2C(numArg);
  if (iVar1 == 0) {
    return def;
  }
  uVar2 = luaL_check_string(numArg);
  return uVar2;
}

/* ---- 0x10002aa0  luaL_check_number ---- */
/* lauxlib.c (argument checking helpers) */

float __cdecl luaL_check_number(int numArg)

{
  int o;
  int iVar1;
  float fVar2;
  
  o = lua_lua2C(numArg);
  iVar1 = lua_isnumber(o);
  if (iVar1 == 0) {
    luaL_argerror(numArg,((unsigned)(uintptr_t)&s_number_expected_10026370));
  }
  fVar2 = lua_getnumber(o);
  return fVar2;
}

/* ---- 0x10002ae0  luaL_opt_number ---- */
/* lauxlib.c (argument checking helpers) */

float __cdecl luaL_opt_number(int numArg,float def)

{
  int iVar1;
  float fVar2;
  
  iVar1 = lua_lua2C(numArg);
  if (iVar1 == 0) {
    return def;
  }
  fVar2 = luaL_check_number(numArg);
  return fVar2;
}

/* ---- 0x10002b10  luaL_tablearg ---- */
/* lauxlib.c (argument checking helpers) */

int __cdecl luaL_tablearg(int arg)

{
  int o;
  int iVar1;
  
  o = lua_lua2C(arg);
  iVar1 = lua_istable(o);
  if (iVar1 == 0) {
    luaL_argerror(arg,((unsigned)(uintptr_t)&s_table_expected_10026380));
  }
  return o;
}

/* ---- 0x10002b50  luaL_functionarg ---- */
/* lauxlib.c (argument checking helpers) */

int __cdecl luaL_functionarg(int arg)

{
  int o;
  int iVar1;
  
  o = lua_lua2C(arg);
  iVar1 = lua_isfunction(o);
  if (iVar1 == 0) {
    luaL_argerror(arg,((unsigned)(uintptr_t)&s_function_expected_10026390));
  }
  return o;
}

/* ---- 0x10002b90  luaL_nonnullarg ---- */
/* lauxlib.c (argument checking helpers) */

int __cdecl luaL_nonnullarg(int numArg)

{
  int iVar1;
  
  iVar1 = lua_lua2C(numArg);
  if (iVar1 == 0) {
    luaL_argerror(numArg,((unsigned)(uintptr_t)&s_value_expected_100263a4));
  }
  return iVar1;
}

/* ---- 0x10002bc0  luaL_openlib ---- */
/* lauxlib.c (argument checking helpers) */

uint __cdecl luaL_openlib(undefined4 *l,int n)

{
  uint uVar1;
  
  lua_open();
  uVar1 = lua_openlib(l,n);
  return uVar1;
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

int __cdecl luaL_openspace(int size)

{
  if (g_dwLState_Mbuffsize < (uint)(size + g_dwLState_Mbuffnext)) {
    Lbuffer_Openspace(size);
  }
  return g_dwLState_Mbuffer + g_dwLState_Mbuffnext;
}

/* ---- 0x10002c50  Lbuffer_Openspace ---- */
/* lbuffer.c: doubles the shared string buffer through the realloc service Named Lbuffer_Openspace
   (not in the remaster, gcc inlined it there): Lua 3.1 source name Openspace, with the module as
   prefix because the bridge refuses the one-token name (lbuffer.c static Openspace: doubles
   Mbuffsize, at least Mbuffnext + size, reallocs Mbuffer and moves Mbuffbase; called by
   luaL_openspace / luaL_addchar / luaL_newbuffer); was luaL_growbuffer. */

void __cdecl Lbuffer_Openspace(int size)

{
  int iVar1;
  
  g_dwLState_Mbuffsize = g_dwLState_Mbuffsize * 2;
  iVar1 = g_dwLState_Mbuffbase - g_dwLState_Mbuffer;
  if (g_dwLState_Mbuffsize < (uint)(size + g_dwLState_Mbuffnext)) {
    g_dwLState_Mbuffsize = size + g_dwLState_Mbuffnext;
  }
  g_dwLState_Mbuffer =
       (**(code **)(g_dwLuaHS + 0x28))
                 (g_dwLState_Mbuffer,g_dwLState_Mbuffsize,
                  s_C__grimsrc_libs_lua_src_lbuffer__100263b4,0x1f);
  g_dwLState_Mbuffbase = iVar1 + g_dwLState_Mbuffer;
  return;
}

/* ---- 0x10002cb0  luaL_addchar ---- */
/* Unidentified function of lbuffer.c (string buffer) */

void __cdecl luaL_addchar(undefined1 c)

{
  if (g_dwLState_Mbuffsize < g_dwLState_Mbuffnext + 0x20U) {
    Lbuffer_Openspace(0x20);
  }
  *(undefined1 *)(g_dwLState_Mbuffnext + g_dwLState_Mbuffer) = c;
  g_dwLState_Mbuffnext = g_dwLState_Mbuffnext + 1;
  return;
}

/* ---- 0x10002cf0  luaL_resetbuffer ---- */
/* Unidentified function of lbuiltin.c (built-in functions) */

void luaL_resetbuffer(void)

{
  g_dwLState_Mbuffnext = g_dwLState_Mbuffbase - g_dwLState_Mbuffer;
  return;
}
