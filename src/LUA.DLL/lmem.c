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

uint __cdecl luaM_growaux(undefined4 *block,uint nelems,int size,byte *errormsg,uint limit)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (limit <= nelems) {
    lua_error(errormsg);
  }
  if (nelems == 0) {
    uVar2 = 0x20;
  }
  else {
    uVar2 = nelems * 2;
  }
  if (limit < uVar2) {
    uVar2 = limit;
  }
  uVar1 = (**(code **)(g_dwLuaHS + 0x28))
                    (*block,size * uVar2,s_C__grimsrc_libs_lua_src_lmem_cpp_10027080,0x22);
  *block = uVar1;
  return uVar2;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char grim_def_s_C__grimsrc_libs_lua_src_lmem_cpp_10027080[40] __asm__("_s_C__grimsrc_libs_lua_src_lmem_cpp_10027080");
/* 0x10027080, 40 bytes */ /* loose */ char grim_def_s_C__grimsrc_libs_lua_src_lmem_cpp_10027080[40] __asm__("_s_C__grimsrc_libs_lua_src_lmem_cpp_10027080") = "C:\\grimsrc\\libs\\lua\\src\\lmem.cpp";
