/* GRIMFANDANGO.EXE :: sputlua.c
 * functions 0x0049c9f0 .. 0x0049c9f0 (1 functions)
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
  param_2[1] = FUN_0049e500;
  param_2[2] = Lua_InitGameLibs;
  param_2[3] = FUN_0049e530;
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  iVar1 = lua_Initialize(param_1,&DAT_008cab50);
  if (iVar1 != 0) {
    UINT_008cab7c = 0;
    return 1;
  }
  UINT_008cab7c = 1;
  return 0;
}
