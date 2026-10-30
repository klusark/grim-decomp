/* IMUSE.DLL :: soundgetvoicetime.c
 * functions 0x10008990 .. 0x10008990 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10008990  SoundGetVoiceTime ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

uint SoundGetVoiceTime(void)

{
  uint uVar1;
  
                    /* 0x8990  50  SoundGetVoiceTime */
  uVar1 = ImGetParam(10000,0x1a00);
  return uVar1;
}
