/* Readable C for the CHORE.DLL costume loader Cos_LoadEntry, slice 5, second pass (agent asm_o2; see docs/notes/asm_o2.md).
 *
 * Written by hand from the original machine code (src/CHORE.DLL/asm_funcs.s) and checked against it with a
 * differential test in build/difftest/asm_s5/ (chore_test.c).  The text costume format is read line by line with
 * Cos_ReadLine (read a line of at most 0x400 bytes into the buffer at 0x10013e10) and msvc_sscanf (sscanf); the
 * format strings are unnamed .data strings, quoted in the comments.  Ghidra's text of these functions used parameter
 * slots that the original reuses as locals and lost a register-held value; the C below uses locals for them.  The four
 * section readers (Cos_Read*Section) are generated again since 2026-11-13 (the parameter slots are plain C there).
 * tools/build_src.py puts the decompiled text of every function defined here under `#if 0`. */
#include "ghidra_types.h"

#ifdef GRIM_CHORE
#include "globals.h"
#include "functions.h"

#define COS_LINE ((char *)IMG_ADDR(0x10013e10))          /* line buffer, 0x400 bytes */

#endif /* GRIM_CHORE */
