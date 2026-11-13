/* GRIMFANDANGO.EXE :: debuglog.c
 * functions 0x00401040 .. 0x00402560 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00401040  grimdemo_EnableDebugging ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Opens debug.log / resource.log and installs the debug-print callbacks into the service table
   Original name grimdemo_EnableDebugging (the remaster's GrimFandango (Linux): the debug-toggle
   callback of Main_Startup; sets the same five host-service print slots (+4, +8, +0xc, +0x10,
   +0x14)); was DebugLog_Init. */

void __cdecl grimdemo_EnableDebugging(int enable)

{
  void *pvVar1;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  
  if (enable != 0) {
    if (UINT_004f5a54 == 0) {
      if (((UINT_004f5a18 != 0) && (g_nDeveloper != 0)) &&
         (UINT_004f44e0 = Res_FOpen(s_debug_log_004dd46c,&DAT_004dd478), UINT_004f44e0 == 0)) {
        pcVar3 = s_Uh_oh__004dd464;
        pcVar2 = s_Unable_to_open_debug_log_in_the_c_004dd424;
        uVar4 = UINT_004f44e0;
        pvVar1 = Win_GetMainHwnd();
        Grim_FatalMessageBox((int)pvVar1,(int)pcVar2,(int)pcVar3,uVar4);
        return;
      }
      if (UINT_004f5a1c != 0) {
        grimlib_LogResources(((unsigned)(uintptr_t)&DAT_004dd414));
      }
      UINT_004f5a08 = DebugLog_Load();
      _DAT_008ddda8 = grimdemo_MessagePrint;
      _DAT_008ddda4 = grimdemo_StatusPrint;
      _DAT_008dddb0 = grimdemo_ErrorPrint;
      UINT_008dddac = (uint)grimdemo_WarningPrint;
      _DAT_008dddb4 = grimdemo_DebugPrint;
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
      Res_FClose(UINT_004f44e0);
      UINT_004f44e0 = 0;
    }
  }
  return;
}

/* ---- 0x004020a0  DebugLog_Load ---- */
/* Loads DebugLog.dll (_logPrintf/_ShowDebugLog) when running in developer mode */

uint __cdecl DebugLog_Load(void)

{
  void *pvVar1;
  
  if (g_bWindowedMode == 0) {
    UINT_004f5a40 = 0;
  }
  else {
    UINT_004f5a40 = LoadLibraryA(((unsigned)(uintptr_t)&DAT_004dd6c4));
  }
  if (UINT_004f5a40 != 0) {
    UINT_004f5a3c = GetProcAddress(UINT_004f5a40,((unsigned)(uintptr_t)&s__logPrintf_004dd6b8));
    UINT_004f5a68 = GetProcAddress(UINT_004f5a40,((unsigned)(uintptr_t)&s__ShowDebugLog_004dd6a8));
    if ((UINT_004f5a3c != 0) && (UINT_004f5a68 != 0)) {
      pvVar1 = Win_GetMainHwnd();
      (*(code *)UINT_004f5a68)(s_Grim_Debug_004dd69c,1,pvVar1);
      return 1;
    }
  }
  return 0;
}

/* ---- 0x00402330  grimdemo_MessagePrint ---- */
/* g_MainServices.pPrintf2: like DebugLog_Printf with its own 0x400 buffer. Original name
   grimdemo_MessagePrint (the remaster's GrimFandango (Linux): the host-service slot +8
   grimdemo_EnableDebugging sets); was DebugLog_Printf2. */

char * __cdecl grimdemo_MessagePrint(char *param_1)

{
  _vsnprintf(&g_aGrimdemo_MessagePrint_grimMessageBuffer,0x400,param_1,&STACK0X(0x00000008));
  if ((UINT_004f5a08 == 0) || (g_bWindowedMode == 0)) {
    stdPlatform_Printf(&g_aGrimdemo_MessagePrint_grimMessageBuffer);
  }
  else {
    param_1 = (char *)(*(code *)UINT_004f5a3c)(&g_aGrimdemo_MessagePrint_grimMessageBuffer);
  }
  if (UINT_004f5a18 != 0) {
    DebugLog_Write(&g_aGrimdemo_MessagePrint_grimMessageBuffer,0);
  }
  return param_1;
}

/* ---- 0x004023a0  grimdemo_StatusPrint ---- */
/* g_MainServices.pPrintf: snprintf into a 0x400 buffer, prints to the debugger/window and appends
   to debug.log. Original name grimdemo_StatusPrint (the remaster's GrimFandango (Linux): the
   host-service slot +4 grimdemo_EnableDebugging sets); was DebugLog_Printf. */

char * __cdecl grimdemo_StatusPrint(char *param_1)

{
  _vsnprintf(&g_aGrimdemo_StatusPrint_grimStatusBuffer,0x400,param_1,&STACK0X(0x00000008));
  if ((UINT_004f5a08 == 0) || (g_bWindowedMode == 0)) {
    stdPlatform_Printf(&g_aGrimdemo_StatusPrint_grimStatusBuffer);
  }
  else {
    param_1 = (char *)(*(code *)UINT_004f5a3c)(&g_aGrimdemo_StatusPrint_grimStatusBuffer);
  }
  if (UINT_004f5a18 != 0) {
    DebugLog_Write(&g_aGrimdemo_StatusPrint_grimStatusBuffer,0);
  }
  return param_1;
}

/* ---- 0x00402410  grimdemo_ErrorPrint ---- */
/* g_MainServices.pError: formats into a 0x400 buffer, prints and appends to debug.log. Original
   name grimdemo_ErrorPrint (the remaster's GrimFandango (Linux): the host-service slot +0x10
   grimdemo_EnableDebugging sets); was DebugLog_Error. */

char * __cdecl grimdemo_ErrorPrint(char *param_1)

{
  _vsnprintf(&g_aGrimdemo_ErrorPrint_grimErrorBuffer,0x400,param_1,&STACK0X(0x00000008));
  if ((UINT_004f5a08 == 0) || (g_bWindowedMode == 0)) {
    stdPlatform_Printf(&g_aGrimdemo_ErrorPrint_grimErrorBuffer);
  }
  else {
    param_1 = (char *)(*(code *)UINT_004f5a3c)(&g_aGrimdemo_ErrorPrint_grimErrorBuffer);
  }
  if (UINT_004f5a18 != 0) {
    DebugLog_Write(&g_aGrimdemo_ErrorPrint_grimErrorBuffer,0);
  }
  return param_1;
}

/* ---- 0x00402480  grimdemo_WarningPrint ---- */
/* g_MainServices.pWarning: formats into a 0x400 buffer, prints and appends to debug.log. Original
   name grimdemo_WarningPrint (the remaster's GrimFandango (Linux): the host-service slot +0xc
   grimdemo_EnableDebugging sets); was DebugLog_Warning. */

char * __cdecl grimdemo_WarningPrint(char *param_1)

{
  _vsnprintf(&g_aGrimdemo_WarningPrint_grimWarningBuffer,0x400,param_1,&STACK0X(0x00000008));
  if ((UINT_004f5a08 == 0) || (g_bWindowedMode == 0)) {
    stdPlatform_Printf(&g_aGrimdemo_WarningPrint_grimWarningBuffer);
  }
  else {
    param_1 = (char *)(*(code *)UINT_004f5a3c)(&g_aGrimdemo_WarningPrint_grimWarningBuffer);
  }
  if (UINT_004f5a18 != 0) {
    DebugLog_Write(&g_aGrimdemo_WarningPrint_grimWarningBuffer,0);
  }
  return param_1;
}

/* ---- 0x004024f0  grimdemo_DebugPrint ---- */
/* g_MainServices.pDebug: formats into a 0x400 buffer, prints and appends to debug.log. Original
   name grimdemo_DebugPrint (the remaster's GrimFandango (Linux): the host-service slot +0x14
   grimdemo_EnableDebugging sets); was DebugLog_Debug. */

char * __cdecl grimdemo_DebugPrint(char *param_1)

{
  _vsnprintf(&g_aGrimdemo_DebugPrint_grimDebugBuffer,0x400,param_1,&STACK0X(0x00000008));
  if ((UINT_004f5a08 == 0) || (g_bWindowedMode == 0)) {
    stdPlatform_Printf(&g_aGrimdemo_DebugPrint_grimDebugBuffer);
  }
  else {
    param_1 = (char *)(*(code *)UINT_004f5a3c)(&g_aGrimdemo_DebugPrint_grimDebugBuffer);
  }
  if (UINT_004f5a18 != 0) {
    DebugLog_Write(&g_aGrimdemo_DebugPrint_grimDebugBuffer,0);
  }
  return param_1;
}

/* ---- 0x00402560  DebugLog_Write ---- */
void __cdecl DebugLog_Write(char *param_1,uint param_2)

{
  Res_FPrintf(UINT_004f44e0,param_1,param_2);
  return;
}
