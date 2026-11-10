/* LUA.DLL :: lmem.c
 * functions 0x100073b0 .. 0x100073f0 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100073b0  luaM_malloc ---- */
/* lmem.c (memory through the service table) */

void * __cdecl luaM_malloc(uint size)

{
  void *pvVar1;
  
  pvVar1 = (void *)(**(code **)(g_dwLuaHS + 0x20))
                             (size,s_C__grimsrc_libs_lua_src_lmem_cpp_10027080,0x11);
  return pvVar1;
}

/* ---- 0x100073d0  luaM_free ---- */
/* Unidentified function of lmem.c (memory through the service table) */

void __cdecl luaM_free(void *block)

{
  (**(code **)(g_dwLuaHS + 0x24))(block);
  return;
}

/* ---- 0x100073f0  luaM_growaux ---- */
/* lmem.c (memory through the service table) */

uint __cdecl luaM_growaux(undefined4 *param_1,uint param_2,int param_3,byte *param_4,uint param_5)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_5 <= param_2) {
    lua_error(param_4);
  }
  if (param_2 == 0) {
    uVar2 = 0x20;
  }
  else {
    uVar2 = param_2 * 2;
  }
  if (param_5 < uVar2) {
    uVar2 = param_5;
  }
  uVar1 = (**(code **)(g_dwLuaHS + 0x28))
                    (*param_1,param_3 * uVar2,s_C__grimsrc_libs_lua_src_lmem_cpp_10027080,0x22);
  *param_1 = uVar1;
  return uVar2;
}
