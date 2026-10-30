/* GRIMFANDANGO.EXE :: drawlist.c
 * functions 0x00486250 .. 0x004862b0 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00486250  DrawList_Reset ---- */
void DrawList_Reset(void)

{
  undefined *puVar1;
  uint *puVar2;
  
  UINT_008a952c = 0;
  puVar2 = &UINT_008c9568;
  puVar1 = &DAT_008a8ca8;
  do {
    *puVar2 = (uint)puVar1;
    puVar1 = puVar1 + 0xc;
    puVar2 = puVar2 + 1;
  } while ((int)puVar1 < IMG_ADDR(0x008a92a8));
  return;
}

/* ---- 0x00486280  DrawList_Alloc ---- */
/* Returns the next of 128 draw-list entries or NULL */

undefined * DrawList_Alloc(void)

{
  uint uVar1;
  
  uVar1 = UINT_008a952c;
  if ((int)UINT_008a952c < 0x80) {
    UINT_008a952c = UINT_008a952c + 1;
    return &DAT_008a8ca8 + uVar1 * 0xc;
  }
  return (undefined *)0x0;
}

/* ---- 0x004862b0  FUN_004862b0 ---- */
undefined4 FUN_004862b0(int *param_1,int *param_2)

{
  if (*(float *)(*param_1 + 4) < *(float *)(*param_2 + 4)) {
    return 1;
  }
  return 0;
}
