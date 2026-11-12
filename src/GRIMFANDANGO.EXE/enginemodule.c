/* GRIMFANDANGO.EXE :: enginemodule.c
 * functions 0x00482540 .. 0x00482cc0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00482540  grimlib_GameInitialize ---- */
/* Fills the engine module interface and registers the two Lua/engine callback tables (8 + 6
   entries) Original name grimlib_GameInitialize (the remaster's GrimFandango (Linux): the
   module-interface filler Main_Startup calls with hs and ms, same slots (itself, terminate,
   grimlib_GameStartup, shutdown) and base-module loop); was EngineModule_Init. */

undefined * __cdecl grimlib_GameInitialize(GrimServices *param_1,undefined **param_2)

{
  undefined *puVar1;
  
  g_pSputmHS = param_1;
  *param_2 = grimlib_GameInitialize;
  param_2[1] = grimlib_GameTerminate;
  param_2[2] = grimlib_GameStartup;
  param_2[3] = grimlib_GameShutdown;
  param_2[4] = (undefined *)0x0;
  param_2[5] = (undefined *)0x0;
  param_2[6] = (undefined *)0x0;
  param_2[7] = (undefined *)0x0;
  puVar1 = (undefined *)
           Engine_RegisterSubsystems
                     (param_1,&PTR_FileUtil_SysInitialize_004e7dc0,&g_aGrimlib_Filenames,8);
  if (puVar1 == (undefined *)0x0) {
    puVar1 = (undefined *)
             Engine_RegisterSubsystems
                       (param_1,&PTR_sputControl_Initialize_004e7e00,&g_aBaseModuleServices,6);
  }
  g_dwSputmInitialize = (uint)(puVar1 == (undefined *)0x0);
  return puVar1;
}

/* ---- 0x00482b60  grimlib_GameTerminate ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Module interface slot 1 (EngineModule): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. Original name
   grimlib_GameTerminate (the remaster's GrimFandango (Linux): the terminate slot
   grimlib_GameInitialize fills, same body (clears psputmHS, undoes the modules when
   bsputmInitialize)); was EngineModule_Terminate. */

undefined * grimlib_GameTerminate(void)

{
  undefined *puVar1;
  
  g_pSputmHS = (GrimServices *)0x0;
  puVar1 = (undefined *)0x0;
  if (g_dwSputmInitialize != 0) {
    Engine_ResetSubsystems(&g_aBaseModuleServices,6);
    puVar1 = (undefined *)Engine_ResetSubsystems(&g_aGrimlib_Filenames,8);
    g_dwSputmInitialize = 0;
  }
  return puVar1;
}

/* ---- 0x00482ba0  grimlib_GameStartup ---- */
/* Module interface slot 2 (EngineModule): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). Original name grimlib_GameStartup (the remaster's
   GrimFandango (Linux): the only unmatched caller of Plat_GetPhysicalMemory; 1 matched neighbours
   agree, 0 disagree); was EngineModule_Start. */

int grimlib_GameStartup(void)

{
  int iVar1;
  uint budget;
  
  if (g_dwSputmStartup != 0) {
    return 1;
  }
  iVar1 = Engine_InitSubsystems(&g_aGrimlib_Filenames,8);
  if (iVar1 == 0) {
    iVar1 = DSound_Init();
    if (iVar1 == 0) {
      return 1;
    }
    iVar1 = stdPlatform_GetPhysicalRam();
    if (iVar1 < 0x1000001) {
      iMUSE_DeclareBufferSizes(88000,44000,88000,440000,44000,0x55f00,100000,1,0xac44,2,300000,6);
      budget = 0xa00000;
    }
    else {
      iMUSE_DeclareBufferSizes(88000,44000,88000,440000,44000,0x55f00,100000,1,0xac44,2,300000,9);
      iVar1 = stdPlatform_GetPhysicalRam();
      budget = g_dwMax_ram;
      if (iVar1 - (int)((unsigned)(uintptr_t)&DAT_00800000) <= (int)g_dwMax_ram) {
        iVar1 = stdPlatform_GetPhysicalRam();
        budget = iVar1 - 0x800000;
      }
    }
    sputResource_SetMemoryUsage(budget,0);
    Sounds_PlatformDevice((int)g_pDirectSound);
    iVar1 = Engine_InitSubsystems(&g_aBaseModuleServices,6);
  }
  g_dwSputmStartup = (uint)(iVar1 == 0);
  return iVar1;
}

/* ---- 0x00482cc0  grimlib_GameShutdown ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Module interface slot 3 (EngineModule): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name grimlib_GameShutdown (the remaster's GrimFandango
   (Linux): the shutdown slot grimlib_GameInitialize fills (shuts the modules down in reverse)); was
   EngineModule_Stop. */

undefined * grimlib_GameShutdown(void)

{
  undefined *puVar1;
  
  Engine_ShutdownSubsystems(&g_aBaseModuleServices,6);
  DSound_Shutdown();
  puVar1 = (undefined *)Engine_ShutdownSubsystems(&g_aGrimlib_Filenames,8);
  g_dwSputmStartup = 0;
  return puVar1;
}
