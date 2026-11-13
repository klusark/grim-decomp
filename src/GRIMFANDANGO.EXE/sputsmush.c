/* GRIMFANDANGO.EXE :: sputsmush.c
 * functions 0x00488fb0 .. 0x00489190 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00488fb0  sputSmush_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

uint __cdecl sputSmush_Initialize(uint param_1,uint *param_2)

{
  _g_dwSmushHS = param_1;
  *param_2 = (uint)sputSmush_Initialize;
  param_2[1] = (uint)&DAT_004891a0;
  param_2[2] = (uint)sputSmush_Startup;
  param_2[3] = (uint)sputSmush_Shutdown;
  param_2[4] = (uint)sputSmush_Save;
  param_2[5] = (uint)sputSmush_Restore;
  param_2[6] = 0;
  param_2[7] = 0;
  SmushPlay_SysInitialize(param_1,&g_aSmushPlayMS);
  SmushPlay_SysSetVideoCallbacks(&g_pSputVideoCallBacks);
  g_pPresentBuf = (void *)0x0;
  _g_dwSmushBuf = 1;
  return 0;
}

/* ---- 0x00489130  sputSmush_Startup ---- */
/* Module slot 2 of sputSmush: honours the StartSmush registry value (FALSE disables movies),
   otherwise initialises the Smush player through the LecShare table and sets g_nSputSmushStarted.
   Original name sputSmush_Startup (the remaster's GrimFandango (Linux): strings: 'StartSmush'); was
   sputSmush_Start. */

uint __cdecl sputSmush_Startup(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_c (*(char (*)[12])(_frame + (0x20 - 0xc)))
  
  iVar1 = wuRegistry_GetStr(s_StartSmush_004e8358,local_c,10,&DAT_004f5a98);
  if ((iVar1 != 0) && (iVar1 = _stricmp(local_c,s_FALSE_004e8350), iVar1 == 0)) {
    return 0;
  }
  iVar1 = (*(code *)UINT_008c9fc0)();
  if (iVar1 == 0) {
    g_nSputSmushStarted = 1;
    return 0;
  }
  return 1;
}
#undef local_c


/* ---- 0x00489190  sputSmush_Shutdown ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Module slot 3 of sputSmush: jumps through the Smush player's shutdown pointer when movies are
   available. Original name sputSmush_Shutdown (the remaster's GrimFandango (Linux): aligned call in
   sputSmush_Initialize); was sputSmush_Stop. */

void __cdecl sputSmush_Shutdown(void)

{
  if (g_nSputSmushStarted != 0) {
                    /* WARNING: Could not recover jumptable at 0x00489199. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*_DAT_008c9fc4)();
    return;
  }
  return;
}
