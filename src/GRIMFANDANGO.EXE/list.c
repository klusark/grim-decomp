/* GRIMFANDANGO.EXE :: list.c
 * functions 0x0048ac00 .. 0x0048ac00 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048ac00  List_Unlink ---- */
/* Removes a {prev,next} doubly linked node */

void List_Unlink(int *param_1)

{
  if (param_1 != (int *)0x0) {
    if (*param_1 != 0) {
      *(int *)(*param_1 + 4) = param_1[1];
    }
    if ((int *)param_1[1] != (int *)0x0) {
      *(int *)param_1[1] = *param_1;
    }
    if (param_1 == g_pTextObjectList) {
      g_pTextObjectList = (void *)*param_1;
    }
    Pool_Free(param_1);
  }
  return;
}
