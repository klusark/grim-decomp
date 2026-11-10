/* GRIMFANDANGO.EXE :: list.c
 * functions 0x0048ac00 .. 0x0048ac00 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048ac00  List_Unlink ---- */
/* Removes a {prev,next} doubly linked node */

void __cdecl List_Unlink(void *obj)

{
  if (obj != (void *)0x0) {
    if (*(int *)obj != 0) {
      *(undefined4 *)(*(int *)obj + 4) = *(undefined4 *)((int)obj + 4);
    }
    if (*(undefined4 **)((int)obj + 4) != (undefined4 *)0x0) {
      **(undefined4 **)((int)obj + 4) = *(undefined4 *)obj;
    }
    if (obj == g_pTextQueue) {
      g_pTextQueue = *(void **)obj;
    }
    Pool_Free(obj);
  }
  return;
}
