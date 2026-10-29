/* LUA.DLL :: setsbcs.c
 * functions 0x1001cee0 .. 0x1001cee0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1001cee0  setSBCS ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void setSBCS(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_1002c368;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_1002c570 = 0;
  _DAT_1002c5d8 = 0;
  DAT_1002c574 = 0;
  _DAT_1002c578 = 0;
  _DAT_1002c57c = 0;
  _DAT_1002c580 = 0;
  return;
}
