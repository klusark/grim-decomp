/* GRIMFANDANGO.EXE :: enginemodule.c
 * functions 0x00482540 .. 0x00482540 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00482540  EngineModule_Init ---- */
/* Fills the engine module interface and registers the two Lua/engine callback tables (8 + 6
   entries) */

undefined * __cdecl EngineModule_Init(GrimServices *param_1,undefined **param_2)

{
  undefined *puVar1;
  
  g_pSvcEngineModule = param_1;
  *param_2 = EngineModule_Init;
  param_2[1] = FUN_00482b60;
  param_2[2] = FUN_00482ba0;
  param_2[3] = FUN_00482cc0;
  param_2[4] = (undefined *)0x0;
  param_2[5] = (undefined *)0x0;
  param_2[6] = (undefined *)0x0;
  param_2[7] = (undefined *)0x0;
  puVar1 = (undefined *)
           Engine_RegisterSubsystems(param_1,&PTR_FileUtil_SysInitialize_004e7dc0,&DAT_008a85f0,8);
  if (puVar1 == (undefined *)0x0) {
    puVar1 = (undefined *)
             Engine_RegisterSubsystems(param_1,&PTR_sputControl_Initialize_004e7e00,&DAT_008a8778,6)
    ;
  }
  UINT_008a8c58 = (uint)(puVar1 == (undefined *)0x0);
  return puVar1;
}
