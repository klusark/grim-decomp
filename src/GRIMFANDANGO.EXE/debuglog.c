/* GRIMFANDANGO.EXE :: debuglog.c
 * functions 0x00401040 .. 0x00402560 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00401040  DebugLog_Init ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Opens debug.log / resource.log and installs the debug-print callbacks into the service table */

void __cdecl DebugLog_Init(int enable)

{
  undefined4 uVar1;
  
  if (enable != 0) {
    if (UINT_004f5a54 == 0) {
      if (((UINT_004f5a18 != 0) && (INT_004f5a24 != 0)) &&
         (UINT_004f44e0 = ResFile_Open(s_debug_log_004dd46c,&DAT_004dd478), UINT_004f44e0 == 0)) {
        uVar1 = ((code *)Win_GetMainHwnd)(s_Unable_to_open_debug_log_in_the_c_004dd424,s_Uh_oh__004dd464,0);
        ((code *)Grim_FatalMessageBox)(uVar1);
        return;
      }
      if (UINT_004f5a1c != 0) {
        Engine_OpenResourceLog(s_resource_log_004dd414);
      }
      UINT_004f5a08 = DebugLog_Load();
      _DAT_008ddda8 = FUN_00402330;
      _DAT_008ddda4 = FUN_004023a0;
      _DAT_008dddb0 = FUN_00402410;
      UINT_008dddac = (uint)FUN_00402480;
      _DAT_008dddb4 = FUN_004024f0;
      UINT_004f5a54 = 1;
    }
    if (enable != 0) {
      return;
    }
  }
  if (UINT_004f5a54 != 0) {
    if (UINT_004f5a04 != 0) {
      UINT_004f5a04 = 0;
    }
    if (UINT_004f44e0 != 0) {
      ResFile_Close(UINT_004f44e0);
      UINT_004f44e0 = 0;
    }
  }
  return;
}

/* ---- 0x004020a0  DebugLog_Load ---- */
/* Loads DebugLog.dll (_logPrintf/_ShowDebugLog) when running in developer mode */

undefined4 DebugLog_Load(void)

{
  undefined4 uVar1;
  
  if (g_bWindowedMode == 0) {
    UINT_004f5a40 = 0;
  }
  else {
    UINT_004f5a40 = LoadLibraryA(IMG_ADDR(0x004dd6c4));
  }
  if (UINT_004f5a40 != 0) {
    UINT_004f5a3c = GetProcAddress(UINT_004f5a40,IMG_ADDR(0x004dd6b8));
    UINT_004f5a68 = GetProcAddress(UINT_004f5a40,IMG_ADDR(0x004dd6a8));
    if ((UINT_004f5a3c != 0) && (UINT_004f5a68 != 0)) {
      uVar1 = Win_GetMainHwnd();
      (*(code *)UINT_004f5a68)(s_Grim_Debug_004dd69c,1,uVar1);
      return 1;
    }
  }
  return 0;
}

/* ---- 0x00402560  DebugLog_Write ---- */
void DebugLog_Write(char *param_1,undefined4 param_2)

{
  ResFile_Printf(UINT_004f44e0,param_1,param_2);
  return;
}
