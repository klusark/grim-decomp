/* GRIMFANDANGO.EXE :: sputlua.c
 * functions 0x0049c9f0 .. 0x0049e530 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0049c9f0  sputLua_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputLua_Initialize(GrimServices *param_1,undefined4 *param_2)

{
  int iVar1;
  
  g_pSvcLua = param_1;
  *param_2 = sputLua_Initialize;
  param_2[1] = sputLua_Terminate;
  param_2[2] = Lua_InitGameLibs;
  param_2[3] = sputLua_Stop;
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  iVar1 = lua_Initialize((int)param_1,(int *)&DAT_008cab50);
  if (iVar1 != 0) {
    UINT_008cab7c = 0;
    return 1;
  }
  UINT_008cab7c = 1;
  return 0;
}

/* ---- 0x0049e500  sputLua_Terminate ---- */
/* Module slot 1 of sputLua: clears g_pSvcLua and calls the Lua shutdown hook if the Lua state
   exists. */

void sputLua_Terminate(void)

{
  g_pSvcLua = (GrimServices *)0x0;
  if (UINT_008cab7c != 0) {
    (*(code *)UINT_008cab54)();
    UINT_008cab7c = 0;
  }
  return;
}

/* ---- 0x0049e530  sputLua_Stop ---- */
/* Module slot 3 of sputLua: disposes the Lua file finder, unrefs the system table, clears the
   save/restore hooks and closes the Lua libs. */

void sputLua_Stop(void)

{
  if (g_pLuaFileFind != (void *)0x0) {
    stdFileUtil_DisposeFind(g_pLuaFileFind);
    g_pLuaFileFind = (void *)0x0;
  }
  lua_unref(g_nLuaSystemTableRef);
  *(undefined4 *)lua_savehook_exref = 0;
  *(undefined4 *)lua_restorehook_exref = 0;
  (*(code *)UINT_008cab5c)();
  UINT_008cab80 = 0;
  return;
}
