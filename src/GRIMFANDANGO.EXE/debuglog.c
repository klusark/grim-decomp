/* GRIMFANDANGO.EXE :: debuglog.c
 * functions 0x00401040 .. 0x00402560 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00401040  grimdemo_EnableDebugging ---- */
/* Opens debug.log / resource.log and installs the debug-print callbacks into the service table
   Original name grimdemo_EnableDebugging (the remaster's GrimFandango (Linux): the debug-toggle
   callback of Main_Startup; sets the same five host-service print slots (+4, +8, +0xc, +0x10,
   +0x14)); was DebugLog_Init. */

void __cdecl grimdemo_EnableDebugging(int enable)

{
  void *hwnd;
  char *text;
  char *caption;
  uint type;
  
  if (enable != 0) {
    if (UINT_004f5a54 == 0) {
      if (((UINT_004f5a18 != 0) && (g_nDeveloper != 0)) &&
         (UINT_004f44e0 = Res_FOpen(s_debug_log_004dd46c,s_w_004dd478), UINT_004f44e0 == 0)) {
        caption = s_Uh_oh__004dd464;
        text = s_Unable_to_open_debug_log_in_the_c_004dd424;
        type = UINT_004f44e0;
        hwnd = Win_GetMainHwnd();
        Grim_FatalMessageBox((int)hwnd,(int)text,(int)caption,type);
        return;
      }
      if (UINT_004f5a1c != 0) {
        grimlib_LogResources(((unsigned)(uintptr_t)&DAT_004dd414));
      }
      UINT_004f5a08 = DebugLog_Load();
      g_aHs.pPrintf2 = grimdemo_MessagePrint;
      g_aHs.pPrintf = grimdemo_StatusPrint;
      g_aHs.pError = grimdemo_ErrorPrint;
      g_aHs.pWarning = grimdemo_WarningPrint;
      g_aHs.pDebug = grimdemo_DebugPrint;
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

char * __cdecl grimdemo_MessagePrint(char *fmt,...)

{
  _vsnprintf(&g_aGrimdemo_MessagePrint_grimMessageBuffer,0x400,fmt,&STACK0X(0x00000008));
  if ((UINT_004f5a08 == 0) || (g_bWindowedMode == 0)) {
    stdPlatform_Printf(&g_aGrimdemo_MessagePrint_grimMessageBuffer);
  }
  else {
    fmt = (char *)(*(code *)UINT_004f5a3c)(&g_aGrimdemo_MessagePrint_grimMessageBuffer);
  }
  if (UINT_004f5a18 != 0) {
    DebugLog_Write(&g_aGrimdemo_MessagePrint_grimMessageBuffer,0);
  }
  return fmt;
}

/* ---- 0x004023a0  grimdemo_StatusPrint ---- */
/* g_MainServices.pPrintf: snprintf into a 0x400 buffer, prints to the debugger/window and appends
   to debug.log. Original name grimdemo_StatusPrint (the remaster's GrimFandango (Linux): the
   host-service slot +4 grimdemo_EnableDebugging sets); was DebugLog_Printf. */

char * __cdecl grimdemo_StatusPrint(char *fmt,...)

{
  _vsnprintf(&g_aGrimdemo_StatusPrint_grimStatusBuffer,0x400,fmt,&STACK0X(0x00000008));
  if ((UINT_004f5a08 == 0) || (g_bWindowedMode == 0)) {
    stdPlatform_Printf(&g_aGrimdemo_StatusPrint_grimStatusBuffer);
  }
  else {
    fmt = (char *)(*(code *)UINT_004f5a3c)(&g_aGrimdemo_StatusPrint_grimStatusBuffer);
  }
  if (UINT_004f5a18 != 0) {
    DebugLog_Write(&g_aGrimdemo_StatusPrint_grimStatusBuffer,0);
  }
  return fmt;
}

/* ---- 0x00402410  grimdemo_ErrorPrint ---- */
/* g_MainServices.pError: formats into a 0x400 buffer, prints and appends to debug.log. Original
   name grimdemo_ErrorPrint (the remaster's GrimFandango (Linux): the host-service slot +0x10
   grimdemo_EnableDebugging sets); was DebugLog_Error. */

char * __cdecl grimdemo_ErrorPrint(char *fmt,...)

{
  _vsnprintf(&g_aGrimdemo_ErrorPrint_grimErrorBuffer,0x400,fmt,&STACK0X(0x00000008));
  if ((UINT_004f5a08 == 0) || (g_bWindowedMode == 0)) {
    stdPlatform_Printf(&g_aGrimdemo_ErrorPrint_grimErrorBuffer);
  }
  else {
    fmt = (char *)(*(code *)UINT_004f5a3c)(&g_aGrimdemo_ErrorPrint_grimErrorBuffer);
  }
  if (UINT_004f5a18 != 0) {
    DebugLog_Write(&g_aGrimdemo_ErrorPrint_grimErrorBuffer,0);
  }
  return fmt;
}

/* ---- 0x00402480  grimdemo_WarningPrint ---- */
/* g_MainServices.pWarning: formats into a 0x400 buffer, prints and appends to debug.log. Original
   name grimdemo_WarningPrint (the remaster's GrimFandango (Linux): the host-service slot +0xc
   grimdemo_EnableDebugging sets); was DebugLog_Warning. */

char * __cdecl grimdemo_WarningPrint(char *fmt,...)

{
  _vsnprintf(&g_aGrimdemo_WarningPrint_grimWarningBuffer,0x400,fmt,&STACK0X(0x00000008));
  if ((UINT_004f5a08 == 0) || (g_bWindowedMode == 0)) {
    stdPlatform_Printf(&g_aGrimdemo_WarningPrint_grimWarningBuffer);
  }
  else {
    fmt = (char *)(*(code *)UINT_004f5a3c)(&g_aGrimdemo_WarningPrint_grimWarningBuffer);
  }
  if (UINT_004f5a18 != 0) {
    DebugLog_Write(&g_aGrimdemo_WarningPrint_grimWarningBuffer,0);
  }
  return fmt;
}

/* ---- 0x004024f0  grimdemo_DebugPrint ---- */
/* g_MainServices.pDebug: formats into a 0x400 buffer, prints and appends to debug.log. Original
   name grimdemo_DebugPrint (the remaster's GrimFandango (Linux): the host-service slot +0x14
   grimdemo_EnableDebugging sets); was DebugLog_Debug. */

char * __cdecl grimdemo_DebugPrint(char *fmt,...)

{
  _vsnprintf(&g_aGrimdemo_DebugPrint_grimDebugBuffer,0x400,fmt,&STACK0X(0x00000008));
  if ((UINT_004f5a08 == 0) || (g_bWindowedMode == 0)) {
    stdPlatform_Printf(&g_aGrimdemo_DebugPrint_grimDebugBuffer);
  }
  else {
    fmt = (char *)(*(code *)UINT_004f5a3c)(&g_aGrimdemo_DebugPrint_grimDebugBuffer);
  }
  if (UINT_004f5a18 != 0) {
    DebugLog_Write(&g_aGrimdemo_DebugPrint_grimDebugBuffer,0);
  }
  return fmt;
}

/* ---- 0x00402560  DebugLog_Write ---- */
void __cdecl DebugLog_Write(char *fmt,uint arg)

{
  Res_FPrintf(UINT_004f44e0,fmt,arg);
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_004dd414[16] __asm__("_DAT_004dd414");
extern unsigned char grim_def_DAT_004dd6c4[16] __asm__("_DAT_004dd6c4");
extern unsigned int grim_def_UINT_004f5a04 __asm__("_UINT_004f5a04");
extern unsigned int grim_def_UINT_004f5a08 __asm__("_UINT_004f5a08");
extern unsigned int grim_def_UINT_004f5a3c __asm__("_UINT_004f5a3c");
extern unsigned int grim_def_UINT_004f5a40 __asm__("_UINT_004f5a40");
extern unsigned int grim_def_UINT_004f5a54 __asm__("_UINT_004f5a54");
extern unsigned int grim_def_UINT_004f5a68 __asm__("_UINT_004f5a68");
extern unsigned char grim_def_g_aGrimdemo_DebugPrint_grimDebugBuffer[1024] __asm__("_g_aGrimdemo_DebugPrint_grimDebugBuffer");
extern unsigned char grim_def_g_aGrimdemo_ErrorPrint_grimErrorBuffer[1024] __asm__("_g_aGrimdemo_ErrorPrint_grimErrorBuffer");
extern unsigned char grim_def_g_aGrimdemo_MessagePrint_grimMessageBuffer[1024] __asm__("_g_aGrimdemo_MessagePrint_grimMessageBuffer");
extern unsigned char grim_def_g_aGrimdemo_StatusPrint_grimStatusBuffer[1024] __asm__("_g_aGrimdemo_StatusPrint_grimStatusBuffer");
extern unsigned char grim_def_g_aGrimdemo_WarningPrint_grimWarningBuffer[1024] __asm__("_g_aGrimdemo_WarningPrint_grimWarningBuffer");
extern char grim_def_s_Grim_Debug_004dd69c[12] __asm__("_s_Grim_Debug_004dd69c");
extern char grim_def_s_Uh_oh__004dd464[8] __asm__("_s_Uh_oh__004dd464");
extern char grim_def_s_Unable_to_open_debug_log_in_the_c_004dd424[64] __asm__("_s_Unable_to_open_debug_log_in_the_c_004dd424");
extern char grim_def_s__ShowDebugLog_004dd6a8[16] __asm__("_s__ShowDebugLog_004dd6a8");
extern char grim_def_s__logPrintf_004dd6b8[12] __asm__("_s__logPrintf_004dd6b8");
extern char grim_def_s_debug_log_004dd46c[12] __asm__("_s_debug_log_004dd46c");
/* 0x004dd414, 16 bytes */ GRIM_DATA("004dd414") unsigned char grim_def_DAT_004dd414[16] __asm__("_DAT_004dd414") = { 0x72, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x2e, 0x6c, 0x6f, 0x67 };
/* 0x004dd424, 64 bytes */ GRIM_DATA("004dd424") char grim_def_s_Unable_to_open_debug_log_in_the_c_004dd424[64] __asm__("_s_Unable_to_open_debug_log_in_the_c_004dd424") = "Unable to open debug.log in the current directory for writing!";
/* 0x004dd464, 8 bytes */ GRIM_DATA("004dd464") char grim_def_s_Uh_oh__004dd464[8] __asm__("_s_Uh_oh__004dd464") = "Uh oh!";
/* 0x004dd46c, 12 bytes */ GRIM_DATA("004dd46c") char grim_def_s_debug_log_004dd46c[12] __asm__("_s_debug_log_004dd46c") = "debug.log";
/* 0x004dd69c, 12 bytes */ GRIM_DATA("004dd69c") char grim_def_s_Grim_Debug_004dd69c[12] __asm__("_s_Grim_Debug_004dd69c") = "Grim Debug";
/* 0x004dd6a8, 16 bytes */ GRIM_DATA("004dd6a8") char grim_def_s__ShowDebugLog_004dd6a8[16] __asm__("_s__ShowDebugLog_004dd6a8") = "_ShowDebugLog";
/* 0x004dd6b8, 12 bytes */ GRIM_DATA("004dd6b8") char grim_def_s__logPrintf_004dd6b8[12] __asm__("_s__logPrintf_004dd6b8") = "_logPrintf";
/* 0x004dd6c4, 16 bytes */ GRIM_DATA("004dd6c4") unsigned char grim_def_DAT_004dd6c4[16] __asm__("_DAT_004dd6c4") = { 0x44, 0x65, 0x62, 0x75, 0x67, 0x4c, 0x6f, 0x67, 0x2e, 0x64, 0x6c, 0x6c };
/* 0x004f4538, 1024 bytes */ GRIM_DATA("004f4538") unsigned char grim_def_g_aGrimdemo_StatusPrint_grimStatusBuffer[1024] __asm__("_g_aGrimdemo_StatusPrint_grimStatusBuffer") = {0};
/* 0x004f4938, 1024 bytes */ GRIM_DATA("004f4938") unsigned char grim_def_g_aGrimdemo_DebugPrint_grimDebugBuffer[1024] __asm__("_g_aGrimdemo_DebugPrint_grimDebugBuffer") = {0};
/* 0x004f4db0, 1024 bytes */ GRIM_DATA("004f4db0") unsigned char grim_def_g_aGrimdemo_ErrorPrint_grimErrorBuffer[1024] __asm__("_g_aGrimdemo_ErrorPrint_grimErrorBuffer") = {0};
/* 0x004f51b0, 1024 bytes */ GRIM_DATA("004f51b0") unsigned char grim_def_g_aGrimdemo_WarningPrint_grimWarningBuffer[1024] __asm__("_g_aGrimdemo_WarningPrint_grimWarningBuffer") = {0};
/* 0x004f55b0, 1024 bytes */ GRIM_DATA("004f55b0") unsigned char grim_def_g_aGrimdemo_MessagePrint_grimMessageBuffer[1024] __asm__("_g_aGrimdemo_MessagePrint_grimMessageBuffer") = {0};
/* 0x004f5a04, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a04 __asm__("_UINT_004f5a04") = 0x0;
/* 0x004f5a08, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a08 __asm__("_UINT_004f5a08") = 0x0;
/* 0x004f5a3c, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a3c __asm__("_UINT_004f5a3c") = 0x0;
/* 0x004f5a40, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a40 __asm__("_UINT_004f5a40") = 0x0;
/* 0x004f5a54, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a54 __asm__("_UINT_004f5a54") = 0x0;
/* 0x004f5a68, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a68 __asm__("_UINT_004f5a68") = 0x0;
