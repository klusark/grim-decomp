/* GRIMFANDANGO.EXE :: component.c
 * functions 0x00496060 .. 0x00496060 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00496060  Component_SetBitmapFrame ---- */
void Component_SetBitmapFrame(undefined4 param_1,int *param_2,undefined4 param_3,int param_4)

{
  if (*param_2 == 0) {
    (*g_pStd_HS->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
  }
  *(int *)(param_2[1] + 0x68) = param_4 + -1;
  return;
}
