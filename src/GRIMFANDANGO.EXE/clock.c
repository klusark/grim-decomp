/* GRIMFANDANGO.EXE :: clock.c
 * functions 0x004ad260 .. 0x004ad260 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004ad260  Clock_ElapsedMs ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Milliseconds since the recorded start time (time() plus a millisecond field); engine helper
   living in the CRT range */

int Clock_ElapsedMs(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  time(&local_c);
  return ((local_8 & 0xffff) + (local_c - UINT_008d0af8) * 1000) - (UINT_008d0afc & 0xffff);
}
#undef local_8
#undef local_c

#endif

