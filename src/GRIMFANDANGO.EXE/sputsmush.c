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

uint __cdecl sputSmush_Initialize(uint services,undefined4 *iface)

{
  _g_dwSmushHS = services;
  *iface = sputSmush_Initialize;
  iface[1] = &DAT_004891a0;
  iface[2] = sputSmush_Startup;
  iface[3] = sputSmush_Shutdown;
  iface[4] = sputSmush_Save;
  iface[5] = sputSmush_Restore;
  iface[6] = 0;
  iface[7] = 0;
  SmushPlay_SysInitialize(services,(undefined4 *)&g_aSmushPlayMS);
  SmushPlay_SysSetVideoCallbacks((uint *)&g_pSputVideoCallBacks);
  g_pPresentBuf = (VBuffer *)0x0;
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
  #define local_c (*(byte (*)[12])(_frame + (0x20 - 0xc)))
  
  iVar1 = wuRegistry_GetStr(s_StartSmush_004e8358,(char *)local_c,10,&DAT_004f5a98);
  if ((iVar1 != 0) && (iVar1 = _stricmp(local_c,(byte *)s_FALSE_004e8350), iVar1 == 0)) {
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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_008c9fc4[52] __asm__("_DAT_008c9fc4");
extern unsigned int grim_def_UINT_008c9fc0 __asm__("_UINT_008c9fc0");
extern unsigned char grim_def_g_aSmushPlayMS[4] __asm__("_g_aSmushPlayMS");
extern unsigned char grim_def_g_dwSmushBuf[4] __asm__("_g_dwSmushBuf");
extern unsigned char grim_def_g_dwSmushHS[776] __asm__("_g_dwSmushHS");
extern char grim_def_s_FALSE_004e8350[8] __asm__("_s_FALSE_004e8350");
extern char grim_def_s_StartSmush_004e8358[16] __asm__("_s_StartSmush_004e8358");
/* 0x004e8350, 8 bytes */ GRIM_DATA("004e8350") char grim_def_s_FALSE_004e8350[8] __asm__("_s_FALSE_004e8350") = "FALSE";
/* 0x004e8358, 16 bytes */ /* loose */ char grim_def_s_StartSmush_004e8358[16] __asm__("_s_StartSmush_004e8358") = "StartSmush";
static unsigned char grim_anchor_008c9ca8[0] __attribute__((section(".data$grim_008c9ca8"), aligned(16), used));
static unsigned char grim_pad_008c9ca8[8] __attribute__((section(".data$grim_008c9ca8_"), aligned(4), used));
/* 0x008c9ca8, 776 bytes */ GRIM_DATA("008c9ca8z") unsigned char grim_def_g_dwSmushHS[776] __asm__("_g_dwSmushHS") = {0};
/* 0x008c9fb8, 4 bytes */ GRIM_DATA("008c9fb8") unsigned char grim_def_g_aSmushPlayMS[4] __asm__("_g_aSmushPlayMS") = {0};
/* 0x008c9fc0, 4 bytes */ GRIM_DATA("008c9fc0") unsigned int grim_def_UINT_008c9fc0 __asm__("_UINT_008c9fc0") = 0x0;
/* 0x008c9fc4, 52 bytes */ GRIM_DATA("008c9fc4") unsigned char grim_def_DAT_008c9fc4[52] __asm__("_DAT_008c9fc4") = {0};
/* 0x008ca080, 4 bytes */ /* loose */ unsigned char grim_def_g_dwSmushBuf[4] __asm__("_g_dwSmushBuf") = {0};
