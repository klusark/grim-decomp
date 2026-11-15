/* GRIMFANDANGO.EXE :: controls.c
 * functions 0x0048d030 .. 0x0048d050 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048d030  Controls_DebugKeysHook ---- */
/* Hook registered by sputControl_Startup: forwards to sputControl_StandardHandler. */

int __cdecl Controls_DebugKeysHook(uint key)

{
  uint uVar1;
  
  uVar1 = sputControl_StandardHandler();
  return (uint)(uVar1 != 0);
}

/* ---- 0x0048d050  sputControl_Reset ---- */
/* Clears the enabled/pressed bits of every control and resets the input devices Original name
   sputControl_Reset (the remaster's GrimFandango (Linux): same body (clears bits 0 / 3 and the +8
   field of every control symbol, then stdControl_Reset); called by sputControl_Startup in both
   builds); was Controls_ResetAll. */

void __cdecl sputControl_Reset(void)

{
  ControlSymbol *pCVar1;
  int iVar2;
  
  pCVar1 = g_aControlSymbols;
  for (iVar2 = g_nSputControl_numControlSymbols; iVar2 != 0; iVar2 = iVar2 + -1) {
    pCVar1->dwFlags = pCVar1->dwFlags & 0xfffffff6;
    (pCVar1->uValue).nState = 0;
    pCVar1 = pCVar1 + 1;
  }
  stdControl_Reset();
  return;
}
