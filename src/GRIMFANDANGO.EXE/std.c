/* GRIMFANDANGO.EXE :: std.c
 * functions 0x0047fc50 .. 0x0047fd00 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047fc50  Std_Swap32 ---- */
uint __cdecl Std_Swap32(uint v)

{
  return (v << 0x10 | v & 0xff00) << 8 | (v >> 0x10 | v & 0xff0000) >> 8;
}

/* ---- 0x0047fd00  Std_Swap16 ---- */
uint __cdecl Std_Swap16(uint v)

{
  return (v & 0xffff) >> 8 | (v & 0xff) << 8;
}
