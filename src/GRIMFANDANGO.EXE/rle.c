/* GRIMFANDANGO.EXE :: rle.c
 * functions 0x004d5e70 .. 0x004d5ed0 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004d5e70  msc_rle_DecompressBlock ---- */
/* Decodes a number of bytes of a run-length coded stream into a buffer
   Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
   Original name msc_rle_DecompressBlock (the remaster's GrimFandango (Linux): same body
   (Initialize, Getbyte loop, Terminate)); was Rle_Decode. */

void __cdecl msc_rle_DecompressBlock(byte *fob_blk16_render_buffer,uint src,int count)

{
  int iVar1;
  uint uVar2;
  int extraout_ECX;
  
  msc_rle_DecompressInitialize((int *)src);
  iVar1 = count;
  for (; count != 0; count = count + -1) {
    uVar2 = msc_rle_DecompressGetbyte(iVar1);
    *fob_blk16_render_buffer = (byte)uVar2;
    fob_blk16_render_buffer = fob_blk16_render_buffer + 1;
    iVar1 = extraout_ECX;
  }
  Mem_DumpLog();
  return;
}

/* ---- 0x004d5eb0  msc_rle_DecompressInitialize ---- */
/* Starts reading a run-length coded byte stream Original name msc_rle_DecompressInitialize (the
   remaster's GrimFandango (Linux): same body (data = p, state = 2)); was Rle_Begin. */

void __cdecl msc_rle_DecompressInitialize(int *src)

{
  g_dwMsc_uncompress_state = 2;
  g_pMsc_uncompress_data = src;
  return;
}

/* ---- 0x004d5ed0  msc_rle_DecompressGetbyte ---- */
/* Returns the next byte of a run-length coded stream; control byte bit 0 selects a run or literal
   bytes Original name msc_rle_DecompressGetbyte (the remaster's GrimFandango (Linux): same body
   (RLE state 0/1/2)); was Rle_NextByte. */

uint __fastcall msc_rle_DecompressGetbyte(undefined4 param_1)

{
  uint uVar1;
  undefined1 local_1;
  
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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_g_bMsc_uncompress_val[4] __asm__("_g_bMsc_uncompress_val");
extern unsigned int grim_def_g_dwMsc_uncompress_count __asm__("_g_dwMsc_uncompress_count");
extern unsigned int grim_def_g_dwMsc_uncompress_state __asm__("_g_dwMsc_uncompress_state");
extern unsigned char grim_def_g_pMsc_uncompress_data[4] __asm__("_g_pMsc_uncompress_data");
/* 0x008dcdb8, 4 bytes */ /* loose */ unsigned int grim_def_g_dwMsc_uncompress_count __asm__("_g_dwMsc_uncompress_count") = 0x0;
/* 0x008dcdbc, 4 bytes */ /* loose */ unsigned int grim_def_g_dwMsc_uncompress_state __asm__("_g_dwMsc_uncompress_state") = 0x0;
/* 0x008dcdc0, 4 bytes */ /* loose */ unsigned char grim_def_g_bMsc_uncompress_val[4] __asm__("_g_bMsc_uncompress_val") = {0};
static unsigned char grim_anchor_008dcdc4[0] __attribute__((section(".data$grim_008dcdc4"), aligned(16), used));
static unsigned char grim_pad_008dcdc4[4] __attribute__((section(".data$grim_008dcdc4_"), aligned(4), used));
/* 0x008dcdc4, 4 bytes */ GRIM_DATA("008dcdc4z") unsigned char grim_def_g_pMsc_uncompress_data[4] __asm__("_g_pMsc_uncompress_data") = {0};
