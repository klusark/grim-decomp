/* GRIMFANDANGO.EXE :: clock.c
 * functions 0x004ad260 .. 0x004ad260 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004ad260  Clock_ElapsedMs ---- */
/* Milliseconds since the recorded start time (time() plus a millisecond field); engine helper
   living in the CRT range */

int __cdecl Clock_ElapsedMs(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  time(&local_c);
  return ((local_8 & 0xffff) + (local_c - UINT_008d0af8) * 1000) - (UINT_008d0afc & 0xffff);
}
#undef local_8
#undef local_c



/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned int grim_def_UINT_008d0af8 __asm__("_UINT_008d0af8");
extern unsigned char grim_def_UINT_008d0afc[12] __asm__("_UINT_008d0afc");
/* 0x008d0af8, 4 bytes */ /* loose */ unsigned int grim_def_UINT_008d0af8 __asm__("_UINT_008d0af8") = 0x0;
static unsigned char grim_anchor_008d0afc[0] __attribute__((section(".data$grim_008d0afc"), aligned(16), used));
static unsigned char grim_pad_008d0afc[12] __attribute__((section(".data$grim_008d0afc_"), aligned(4), used));
/* 0x008d0afc, 12 bytes */ GRIM_DATA("008d0afcz") unsigned char grim_def_UINT_008d0afc[12] __asm__("_UINT_008d0afc") = {0};
