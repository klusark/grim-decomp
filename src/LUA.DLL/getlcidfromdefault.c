/* LUA.DLL :: getlcidfromdefault.c
 * functions 0x100183e0 .. 0x100183e0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100183e0  GetLcidFromDefault ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void GetLcidFromDefault(void)

{
  DAT_1002c234 = DAT_1002c234 | 0x104;
  DAT_1002c238 = GetUserDefaultLCID();
  DAT_1002c21c = DAT_1002c238;
  return;
}
