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
  uint *puVar1;
  
  if ((uint)control <= g_nSputControl_numControlSymbols - 1U) {
    puVar1 = &g_dwSputControl_aControlSymbols + control * 4;
    if ((*puVar1 & 2) != 0) {
      stdControl_EnableAxis(*(uint *)(&DAT_004e87cc + control * 0x10));
    }
    if ((*puVar1 & 1) == 0) {
      *puVar1 = *puVar1 | 1;
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
    uVar1 = (&g_dwSputControl_aControlSymbols)[control * 4];
    if ((uVar1 & 1) != 0) {
      (&g_dwSputControl_aControlSymbols)[control * 4] = uVar1 & 0xfffffffe;
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
  int iVar1;
  
  iVar1 = stdControl_Open();
  if (iVar1 == 0) {
    return (undefined *)0x0;
  }
  g_nControlOpen = 1;
  return (undefined *)0x1;
}

/* ---- 0x0048d170  sputControl_Close ---- */
/* Original name sputControl_Close (the remaster's GrimFandango (Linux): same body (if open:
   stdControl_Close, clear the flag); called by grimlib_Close in both builds); was Control_Release.
    */

undefined4 sputControl_Close(void)

{
  int iVar1;
  
  if (g_nControlOpen == 0) {
    return 0;
  }
  iVar1 = stdControl_Close();
  if (iVar1 == 0) {
    return 0;
  }
  g_nControlOpen = 0;
  return 1;
}
