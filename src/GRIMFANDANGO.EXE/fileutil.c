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
      param_2[1] = FUN_00488ce0;
      param_2[2] = FUN_00488cf0;
      param_2[3] = FUN_00488d20;
      param_2[4] = FUN_00488d30;
      param_2[5] = SaveFile_CheckFUTBHeader;
      param_2[6] = zlibVersion;
      param_2[7] = zlibVersion;
    }
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00488ce0  FUN_00488ce0 ---- */
void FUN_00488ce0(void)

{
  UINT_008c9a94 = 0;
  return;
}

/* ---- 0x00488cf0  FUN_00488cf0 ---- */
undefined4 FUN_00488cf0(void)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if ((UINT_008c9a94 != 0) && (UINT_008c9a98 == 0)) {
    UINT_008c9a98 = 1;
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00488d20  FUN_00488d20 ---- */
void FUN_00488d20(void)

{
  UINT_008c9a98 = 0;
  return;
}

/* ---- 0x00488d30  FUN_00488d30 ---- */
undefined4 FUN_00488d30(code *param_1)

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

