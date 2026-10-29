/* GRIMFANDANGO.EXE :: controls.c
 * functions 0x0048d050 .. 0x0048d050 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048d050  Controls_ResetAll ---- */
/* Clears the enabled/pressed bits of every control and resets the input devices */

void Controls_ResetAll(void)

{
  uint *puVar1;
  int iVar2;
  
  puVar1 = &g_ControlTable;
  for (iVar2 = g_nControlCount; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = *puVar1 & 0xfffffff6;
    puVar1[2] = 0;
    puVar1 = puVar1 + 4;
  }
  Input_ResetState();
  return;
}
