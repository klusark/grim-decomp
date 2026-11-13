/* GRIMFANDANGO.EXE :: rle.c
 * functions 0x004d5e70 .. 0x004d5ed0 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004d5e70  msc_rle_DecompressBlock ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Decodes a number of bytes of a run-length coded stream into a buffer
   Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
   Original name msc_rle_DecompressBlock (the remaster's GrimFandango (Linux): same body
   (Initialize, Getbyte loop, Terminate)); was Rle_Decode. */

void __cdecl msc_rle_DecompressBlock(byte *param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int extraout_ECX;
  
  msc_rle_DecompressInitialize((int *)param_2);
  iVar1 = param_3;
  for (; param_3 != 0; param_3 = param_3 + -1) {
    uVar2 = msc_rle_DecompressGetbyte(iVar1);
    *param_1 = (byte)uVar2;
    param_1 = param_1 + 1;
    iVar1 = extraout_ECX;
  }
  Mem_DumpLog();
  return;
}
#endif


/* ---- 0x004d5eb0  msc_rle_DecompressInitialize ---- */
/* Starts reading a run-length coded byte stream Original name msc_rle_DecompressInitialize (the
   remaster's GrimFandango (Linux): same body (data = p, state = 2)); was Rle_Begin. */

void __cdecl msc_rle_DecompressInitialize(int *param_1)

{
  g_dwMsc_uncompress_state = 2;
  g_pMsc_uncompress_data = param_1;
  return;
}

/* ---- 0x004d5ed0  msc_rle_DecompressGetbyte ---- */
/* Returns the next byte of a run-length coded stream; control byte bit 0 selects a run or literal
   bytes Original name msc_rle_DecompressGetbyte (the remaster's GrimFandango (Linux): same body
   (RLE state 0/1/2)); was Rle_NextByte. */

uint __fastcall msc_rle_DecompressGetbyte(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  #define local_1 (*(undefined1 *)(_frame + (0x20 - 0x1)))
  
  if (g_dwMsc_uncompress_state == 2) {
    g_dwMsc_uncompress_count = (byte)((byte)*g_pMsc_uncompress_data >> 1) + 1;
    if ((*g_pMsc_uncompress_data & 1) == 0) {
      g_dwMsc_uncompress_state = 0;
      g_pMsc_uncompress_data = (int *)((int)g_pMsc_uncompress_data + 1);
    }
    else {
      g_dwMsc_uncompress_state = 1;
      g_bMsc_uncompress_val = *(byte *)((int)g_pMsc_uncompress_data + 1);
      g_pMsc_uncompress_data = (int *)((int)g_pMsc_uncompress_data + 2);
    }
  }
  if (g_dwMsc_uncompress_state == 0) {
    uVar1 = (uint)(byte)*g_pMsc_uncompress_data;
    g_pMsc_uncompress_data = (int *)((int)g_pMsc_uncompress_data + 1);
  }
  else if (g_dwMsc_uncompress_state - 1 == 0) {
    uVar1 = (uint)g_bMsc_uncompress_val;
  }
  else {
    local_1 = (undefined1)((uint)param_1 >> 0x18);
    uVar1 = CONCAT31((int3)(g_dwMsc_uncompress_state - 1 >> 8),local_1);
  }
  g_dwMsc_uncompress_count = g_dwMsc_uncompress_count - 1;
  if (g_dwMsc_uncompress_count == 0) {
    g_dwMsc_uncompress_state = 2;
  }
  return uVar1;
}
#undef local_1

