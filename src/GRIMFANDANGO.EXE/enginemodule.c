/* GRIMFANDANGO.EXE :: enginemodule.c
 * functions 0x00482540 .. 0x00482cc0 (4 functions)
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
  param_2[1] = EngineModule_Terminate;
  param_2[2] = EngineModule_Start;
  param_2[3] = EngineModule_Stop;
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

/* ---- 0x00482b60  EngineModule_Terminate ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Module interface slot 1 (EngineModule): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. */

undefined * EngineModule_Terminate(void)

{
  undefined *puVar1;
  
  g_pSvcEngineModule = (GrimServices *)0x0;
  puVar1 = (undefined *)0x0;
  if (UINT_008a8c58 != 0) {
    Engine_ResetSubsystems(&DAT_008a8778,6);
    puVar1 = (undefined *)Engine_ResetSubsystems(&DAT_008a85f0,8);
    UINT_008a8c58 = 0;
  }
  return puVar1;
}

/* ---- 0x00482ba0  EngineModule_Start ---- */
/* Module interface slot 2 (EngineModule): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind).  */

int EngineModule_Start(void)

{
  int iVar1;
  uint budget;
  
  if (UINT_008a8c5c != 0) {
    return 1;
  }
  iVar1 = Engine_InitSubsystems(&DAT_008a85f0,8);
  if (iVar1 == 0) {
    iVar1 = DSound_Init();
    if (iVar1 == 0) {
      return 1;
    }
    iVar1 = Plat_GetPhysicalMemory();
    if (iVar1 < 0x1000001) {
      iMUSE_DeclareBufferSizes
                (88000,44000,88000,440000,44000,0x55f00,100000,1,0xac44,2,300000,6,150000);
      budget = 0xa00000;
    }
    else {
      iMUSE_DeclareBufferSizes
                (88000,44000,88000,440000,44000,0x55f00,100000,1,0xac44,2,300000,9,150000);
      iVar1 = Plat_GetPhysicalMemory();
      budget = UINT_004e7b20;
      if (iVar1 - (int)IMG_ADDR(0x00800000) <= (int)UINT_004e7b20) {
        iVar1 = Plat_GetPhysicalMemory();
        budget = iVar1 - 0x800000;
      }
    }
    Resource_SetMemoryUsage(budget,0);
    Sounds_PlatformDevice(g_pDirectSound);
    iVar1 = Engine_InitSubsystems(&DAT_008a8778,6);
  }
  UINT_008a8c5c = (uint)(iVar1 == 0);
  return iVar1;
}

/* ---- 0x00482cc0  EngineModule_Stop ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Module interface slot 3 (EngineModule): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. */

undefined * EngineModule_Stop(void)

{
  undefined *puVar1;
  
  Engine_ShutdownSubsystems(&DAT_008a8778,6);
  DSound_Shutdown();
  puVar1 = (undefined *)Engine_ShutdownSubsystems(&DAT_008a85f0,8);
  UINT_008a8c5c = 0;
  return puVar1;
}
