/* GRIMFANDANGO.EXE :: control.c
 * functions 0x0048d090 .. 0x0048d170 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048d090  Control_Enable ---- */
/* Lua EnableControl */

void __cdecl Control_Enable(int control)

{
  uint *puVar1;
  
  if ((uint)control <= g_nControlCount - 1U) {
    puVar1 = &g_ControlTable + control * 4;
    if ((*puVar1 & 2) != 0) {
      Input_EnableAxis(*(uint *)(&DAT_004e87cc + control * 0x10));
    }
    if ((*puVar1 & 1) == 0) {
      *puVar1 = *puVar1 | 1;
    }
  }
  return;
}

/* ---- 0x0048d0d0  Control_Disable ---- */
/* Lua DisableControl */

void __cdecl Control_Disable(int control)

{
  uint uVar1;
  
  if ((uint)control <= g_nControlCount - 1U) {
    uVar1 = (&g_ControlTable)[control * 4];
    if ((uVar1 & 1) != 0) {
      (&g_ControlTable)[control * 4] = uVar1 & 0xfffffffe;
    }
  }
  return;
}

/* ---- 0x0048d150  Control_Capture ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * Control_Capture(void)

{
  int iVar1;
  
  iVar1 = Input_Enable();
  if (iVar1 == 0) {
    return (undefined *)0x0;
  }
  g_nInputCaptured = 1;
  return (undefined *)0x1;
}

/* ---- 0x0048d170  Control_Release ---- */
undefined4 Control_Release(void)

{
  int iVar1;
  
  if (g_nInputCaptured == 0) {
    return 0;
  }
  iVar1 = Input_Disable();
  if (iVar1 == 0) {
    return 0;
  }
  g_nInputCaptured = 0;
  return 1;
}
