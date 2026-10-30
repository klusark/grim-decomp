/* GRIMFANDANGO.EXE :: sputtime.c
 * functions 0x004a3d00 .. 0x004a3da0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a3d00  sputTime_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputTime_Initialize(undefined4 param_1,undefined4 *param_2)

{
  _DAT_008cab94 = param_1;
  *param_2 = sputTime_Initialize;
  param_2[1] = sputTime_Terminate;
  param_2[2] = sputTime_Start;
  param_2[3] = sputTime_Stop;
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  UINT_008cab98 = 1;
  return 0;
}

/* ---- 0x004a3d50  sputTime_Terminate ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Module interface slot 1 (sputTime): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. */

void sputTime_Terminate(void)

{
  _DAT_008cab94 = 0;
  if (UINT_008cab98 != 0) {
    UINT_008cab98 = 0;
  }
  return;
}

/* ---- 0x004a3d70  sputTime_Start ---- */
/* Module interface slot 2 (sputTime): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start resets the frame timer. */

undefined4 sputTime_Start(void)

{
  if (UINT_008cab9c != 0) {
    return 1;
  }
  UINT_008cab9c = 1;
  Timer_Reset();
  return 0;
}

/* ---- 0x004a3da0  sputTime_Stop ---- */
/* Module interface slot 3 (sputTime): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. */

void sputTime_Stop(void)

{
  UINT_008cab9c = 0;
  return;
}
