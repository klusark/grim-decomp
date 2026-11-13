/* GRIMFANDANGO.EXE :: fileutil.c
 * functions 0x00488c80 .. 0x00488d30 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00488c80  FileUtil_SysInitialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

uint __cdecl FileUtil_SysInitialize(GrimServices *param_1,uint *param_2)

{
  uint uVar1;
  
  uVar1 = 1;
  g_pSvcFileutil = param_1;
  if (g_dwFileUtilSysInitialized == 0) {
    g_dwFileUtilSysInitialized = 1;
    if (param_2 != (uint *)0x0) {
      *param_2 = (uint)FileUtil_SysInitialize;
      param_2[1] = (uint)FileUtil_SysTerminate;
      param_2[2] = (uint)FileUtil_SysStartup;
      param_2[3] = (uint)FileUtil_SysShutdown;
      param_2[4] = (uint)FileUtil_SysSave;
      param_2[5] = (uint)FileUtil_SysRestore;
      param_2[6] = (uint)zlibVersion;
      param_2[7] = (uint)zlibVersion;
    }
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00488ce0  FileUtil_SysTerminate ---- */
/* Module interface slot 1 (FileUtil_Sys): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. Original name
   FileUtil_SysTerminate (the remaster's GrimFandango (Linux): aligned call in
   FileUtil_SysInitialize); was FileUtil_Sys_Terminate. */

void __cdecl FileUtil_SysTerminate(void)

{
  g_dwFileUtilSysInitialized = 0;
  return;
}

/* ---- 0x00488cf0  FileUtil_SysStartup ---- */
/* Module interface slot 2 (FileUtil_Sys): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). Original name FileUtil_SysStartup (the remaster's
   GrimFandango (Linux): aligned call in FileUtil_SysInitialize); was FileUtil_Sys_Start. */

uint __cdecl FileUtil_SysStartup(void)

{
  uint uVar1;
  
  uVar1 = 1;
  if ((g_dwFileUtilSysInitialized != 0) && (g_dwFileUtilSysStarted == 0)) {
    g_dwFileUtilSysStarted = 1;
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00488d20  FileUtil_SysShutdown ---- */
/* Module interface slot 3 (FileUtil_Sys): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name FileUtil_SysShutdown (the remaster's GrimFandango
   (Linux): aligned call in FileUtil_SysInitialize); was FileUtil_Sys_Stop. */

void __cdecl FileUtil_SysShutdown(void)

{
  g_dwFileUtilSysStarted = 0;
  return;
}

/* ---- 0x00488d30  FileUtil_SysSave ---- */
/* Module interface slot 4 (FileUtil_Sys): save-game writer, calls the SaveGame_Write callback it is
   handed for every field. Original name FileUtil_SysSave (the remaster's GrimFandango (Linux):
   aligned call in FileUtil_SysInitialize); was FileUtil_Sys_SaveState. */

uint __cdecl FileUtil_SysSave(code *param_1)

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

