/* GRIMFANDANGO.EXE :: fileutil.c
 * functions 0x00488c80 .. 0x00488d30 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00488c80  FileUtil_SysInitialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 FileUtil_SysInitialize(GrimServices *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  g_pSvcFileutil = param_1;
  if (UINT_008c9a94 == 0) {
    UINT_008c9a94 = 1;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = FileUtil_SysInitialize;
      param_2[1] = FileUtil_Sys_Terminate;
      param_2[2] = FileUtil_Sys_Start;
      param_2[3] = FileUtil_Sys_Stop;
      param_2[4] = FileUtil_Sys_SaveState;
      param_2[5] = SaveFile_CheckFUTBHeader;
      param_2[6] = zlibVersion;
      param_2[7] = zlibVersion;
    }
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00488ce0  FileUtil_Sys_Terminate ---- */
/* Module interface slot 1 (FileUtil_Sys): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. */

void FileUtil_Sys_Terminate(void)

{
  UINT_008c9a94 = 0;
  return;
}

/* ---- 0x00488cf0  FileUtil_Sys_Start ---- */
/* Module interface slot 2 (FileUtil_Sys): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind).  */

undefined4 FileUtil_Sys_Start(void)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if ((UINT_008c9a94 != 0) && (UINT_008c9a98 == 0)) {
    UINT_008c9a98 = 1;
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00488d20  FileUtil_Sys_Stop ---- */
/* Module interface slot 3 (FileUtil_Sys): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. */

void FileUtil_Sys_Stop(void)

{
  UINT_008c9a98 = 0;
  return;
}

/* ---- 0x00488d30  FileUtil_Sys_SaveState ---- */
/* Module interface slot 4 (FileUtil_Sys): save-game writer, calls the SaveGame_Write callback it is
   handed for every field. */

undefined4 FileUtil_Sys_SaveState(code *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0x42545546;
  (*param_1)(&local_4,4);
  local_4 = 1;
  (*param_1)(&local_4,4);
  local_4 = 0;
  (*param_1)(&local_4,4);
  return 0;
}
#undef local_4

