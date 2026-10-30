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
  if (UINT_008ca1bc == 0) {
    _DAT_008ca1b8 = param_1;
    *param_2 = sputControl_Initialize;
    param_2[1] = sputControl_Terminate;
    param_2[2] = sputControl_Start;
    param_2[3] = sputControl_Stop;
    param_2[4] = 0;
    param_2[5] = 0;
    param_2[6] = 0;
    param_2[7] = 0;
    UINT_008ca1bc = 1;
  }
  return 0;
}

/* ---- 0x0048d2c0  sputControl_Terminate ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Module interface slot 1 (sputControl): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. */

void sputControl_Terminate(void)

{
  _DAT_008ca1b8 = 0;
  if (UINT_008ca1bc != 0) {
    UINT_008ca1bc = 0;
  }
  return;
}

/* ---- 0x0048d2e0  sputControl_Start ---- */
/* Module interface slot 2 (sputControl): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start initialises input and resets all controls. */

undefined4 sputControl_Start(void)

{
  undefined *puVar1;
  
  if (UINT_008ca1c0 != 0) {
    return 1;
  }
  if (UINT_00805f98 == 0) {
    puVar1 = Input_Init();
    if (puVar1 == (undefined *)0x0) {
      return 1;
    }
  }
  Controls_ResetAll();
  Engine_RegisterShutdownHook(Controls_DebugKeysHook);
  UINT_008ca1c0 = 1;
  return 0;
}

/* ---- 0x0048d330  sputControl_Stop ---- */
/* Module interface slot 3 (sputControl): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. */

void sputControl_Stop(void)

{
  Input_Shutdown();
  UINT_008ca1c0 = 0;
  return;
}
