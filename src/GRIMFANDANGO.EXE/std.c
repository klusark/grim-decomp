/* GRIMFANDANGO.EXE :: std.c
 * functions 0x0047fc50 .. 0x0047fd00 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047fc50  Std_Swap32 ---- */
uint Std_Swap32(uint param_1)

{
  return (param_1 << 0x10 | param_1 & 0xff00) << 8 | (param_1 >> 0x10 | param_1 & 0xff0000) >> 8;
}

/* ---- 0x0047fd00  Std_Swap16 ---- */
uint Std_Swap16(uint param_1)

{
  return (param_1 & 0xffff) >> 8 | (param_1 & 0xff) << 8;
}
