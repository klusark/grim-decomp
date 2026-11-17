/* GRIMFANDANGO.EXE :: control.c
 * functions 0x0048d090 .. 0x0048d170 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048d090  sputControl_EnableControl ---- */
/* Lua EnableControl Original name sputControl_EnableControl (the remaster's GrimFandango (Linux):
   same body (range check, stdControl_EnableAxis for axis controls, set bit 0); called by
   sputLua_EnableControlL in both builds); was Control_Enable. */

void __cdecl sputControl_EnableControl(int control)

{
  ControlSymbol *pCVar1;
  
  if ((uint)control <= g_nSputControl_numControlSymbols - 1U) {
    pCVar1 = g_aControlSymbols + control;
    if ((pCVar1->dwFlags & 2) != 0) {
      stdControl_EnableAxis(g_aControlSymbols[control].nId);
    }
    if ((pCVar1->dwFlags & 1) == 0) {
      pCVar1->dwFlags = pCVar1->dwFlags | 1;
    }
  }
  return;
}

/* ---- 0x0048d0d0  sputControl_DisableControl ---- */
/* Lua DisableControl Original name sputControl_DisableControl (the remaster's GrimFandango (Linux):
   same body (range check, clear bit 0); called by sputLua_DisableControlL in both builds); was
   Control_Disable. */

void __cdecl sputControl_DisableControl(int control)

{
  uint uVar1;
  
  if ((uint)control <= g_nSputControl_numControlSymbols - 1U) {
    uVar1 = g_aControlSymbols[control].dwFlags;
    if ((uVar1 & 1) != 0) {
      g_aControlSymbols[control].dwFlags = uVar1 & 0xfffffffe;
    }
  }
  return;
}

/* ---- 0x0048d150  sputControl_Open ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name sputControl_Open (the remaster's GrimFandango (Linux): the control call of
   grimlib_Open, same body (stdControl_Open, then bControlOpen)); was Control_Capture. */

undefined * sputControl_Open(void)

{
  uint uVar1;
  
  uVar1 = stdControl_Open();
  if (uVar1 == 0) {
    return (undefined *)0x0;
  }
  g_nControlOpen = 1;
  return (undefined *)0x1;
}

/* ---- 0x0048d170  sputControl_Close ---- */
/* Original name sputControl_Close (the remaster's GrimFandango (Linux): same body (if open:
   stdControl_Close, clear the flag); called by grimlib_Close in both builds); was Control_Release.
    */

uint __cdecl sputControl_Close(void)

{
  uint uVar1;
  
  if (g_nControlOpen == 0) {
    return 0;
  }
  uVar1 = stdControl_Close();
  if (uVar1 == 0) {
    return 0;
  }
  g_nControlOpen = 0;
  return 1;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern int grim_def_g_nControlOpen __asm__("_g_nControlOpen");
static unsigned char grim_anchor_008ca1c4[0] __attribute__((section(".data$grim_008ca1c4"), aligned(16), used));
static unsigned char grim_pad_008ca1c4[4] __attribute__((section(".data$grim_008ca1c4_"), aligned(4), used));
/* 0x008ca1c4, 12 bytes */ GRIM_DATA("008ca1c4z") int grim_def_g_nControlOpen __asm__("_g_nControlOpen") = 0;
/* 0x008ca1c8, 8 bytes: the rest of grim_def_g_nControlOpen's span */ GRIM_DATA("008ca1c4z") static unsigned char g_nControlOpen__tail[8] __attribute__((used)) = {0};
