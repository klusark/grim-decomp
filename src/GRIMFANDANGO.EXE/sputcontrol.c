/* GRIMFANDANGO.EXE :: sputcontrol.c
 * functions 0x0048d100 .. 0x0048d330 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048d100  sputControl_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputControl_Initialize(undefined4 param_1,undefined4 *param_2)

{
  if (g_dwSputConInitialize == 0) {
    _g_pSputConHS = param_1;
    *param_2 = sputControl_Initialize;
    param_2[1] = sputControl_Terminate;
    param_2[2] = sputControl_Startup;
    param_2[3] = sputControl_Shutdown;
    param_2[4] = 0;
    param_2[5] = 0;
    param_2[6] = 0;
    param_2[7] = 0;
    g_dwSputConInitialize = 1;
  }
  return 0;
}

/* ---- 0x0048d2c0  sputControl_Terminate ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Module interface slot 1 (sputControl): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. */

void sputControl_Terminate(void)

{
  _g_pSputConHS = 0;
  if (g_dwSputConInitialize != 0) {
    g_dwSputConInitialize = 0;
  }
  return;
}

/* ---- 0x0048d2e0  sputControl_Startup ---- */
/* Module interface slot 2 (sputControl): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start initialises input and resets all controls.
   Original name sputControl_Startup (the remaster's GrimFandango (Linux): aligned call in
   sputControl_Initialize); was sputControl_Start. */

undefined4 sputControl_Startup(void)

{
  undefined *puVar1;
  
  if (g_dwSputConStartup != 0) {
    return 1;
  }
  if (g_dwStdControl_bStartup == 0) {
    puVar1 = stdControl_Startup();
    if (puVar1 == (undefined *)0x0) {
      return 1;
    }
  }
  sputControl_Reset();
  sputControl_AddCallback(Controls_DebugKeysHook);
  g_dwSputConStartup = 1;
  return 0;
}

/* ---- 0x0048d330  sputControl_Shutdown ---- */
/* Module interface slot 3 (sputControl): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputControl_Shutdown (the remaster's GrimFandango
   (Linux): aligned call in sputControl_Initialize); was sputControl_Stop. */

void sputControl_Shutdown(void)

{
  stdControl_Shutdown();
  g_dwSputConStartup = 0;
  return;
}
