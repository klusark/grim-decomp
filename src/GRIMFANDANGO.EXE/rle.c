/* GRIMFANDANGO.EXE :: rle.c
 * functions 0x004d5e70 .. 0x004d5ed0 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004d5e70  Rle_Decode ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Decodes a number of bytes of a run-length coded stream into a buffer
   Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
    */

void Rle_Decode(undefined1 *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int extraout_ECX;
  
  Rle_Begin(param_2);
  iVar1 = param_3;
  for (; param_3 != 0; param_3 = param_3 + -1) {
    uVar2 = Rle_NextByte(iVar1);
    *param_1 = (char)uVar2;
    param_1 = param_1 + 1;
    iVar1 = extraout_ECX;
  }
  Mem_DumpLog();
  return;
}
#endif


/* ---- 0x004d5eb0  Rle_Begin ---- */
/* Starts reading a run-length coded byte stream */

void Rle_Begin(int *param_1)

{
  UINT_008dcdbc = 2;
  PTR_008dcdc4 = param_1;
  return;
}

/* ---- 0x004d5ed0  Rle_NextByte ---- */
/* Returns the next byte of a run-length coded stream; control byte bit 0 selects a run or literal
   bytes */

uint __fastcall Rle_NextByte(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  #define local_1 (*(undefined1 *)(_frame + (0x20 - 0x1)))
  
  if (UINT_008dcdbc == 2) {
    UINT_008dcdb8 = (byte)((byte)*PTR_008dcdc4 >> 1) + 1;
    if ((*PTR_008dcdc4 & 1) == 0) {
      UINT_008dcdbc = 0;
      PTR_008dcdc4 = (int *)((int)PTR_008dcdc4 + 1);
    }
    else {
      UINT_008dcdbc = 1;
      DAT_008dcdc0 = *(byte *)((int)PTR_008dcdc4 + 1);
      PTR_008dcdc4 = (int *)((int)PTR_008dcdc4 + 2);
    }
  }
  if (UINT_008dcdbc == 0) {
    uVar1 = (uint)(byte)*PTR_008dcdc4;
    PTR_008dcdc4 = (int *)((int)PTR_008dcdc4 + 1);
  }
  else if (UINT_008dcdbc - 1 == 0) {
    uVar1 = (uint)DAT_008dcdc0;
  }
  else {
    local_1 = (undefined1)((uint)param_1 >> 0x18);
    uVar1 = CONCAT31((int3)(UINT_008dcdbc - 1 >> 8),local_1);
  }
  UINT_008dcdb8 = UINT_008dcdb8 - 1;
  if (UINT_008dcdb8 == 0) {
    UINT_008dcdbc = 2;
  }
  return uVar1;
}
#undef local_1

