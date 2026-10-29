/* GRIMFANDANGO.EXE :: rdlight.c
 * functions 0x00451460 .. 0x004514a0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00451460  rdLight_Init ---- */
/* Defaults: type 2, on, white (0xffffff), intensity 1.0 */

undefined4 rdLight_Init(int param_1)

{
  *(undefined4 *)(param_1 + 4) = 2;
  *(undefined4 *)(param_1 + 8) = 1;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x1c) = 0xffffff;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  return 1;
}

/* ---- 0x004514a0  rdLight_SetAngles ---- */
void __cdecl rdLight_SetAngles(void *light,float inner,float outer)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  *(float *)((int)light + 0x20) = inner;
  *(float *)((int)light + 0x28) = outer;
  Math_SinCosTable(inner,&local_4,(float *)((int)light + 0x24));
  Math_SinCosTable(outer,&local_4,(float *)((int)light + 0x2c));
  fVar1 = *(float *)((int)light + 0x24) - *(float *)((int)light + 0x2c);
  if (0.0 < fVar1) {
    *(float *)((int)light + 0x30) = 1.0 / fVar1;
  }
  return;
}
#undef local_4

