/* GRIMFANDANGO.EXE :: light.c
 * functions 0x004a5cc0 .. 0x004a5cf0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a5cc0  Light_Get ---- */
/* Light record: +0x20 position, +0x2c/+0x38 orientation, +0x30 type (1 parallel/global, 2 omni, 3
   spot), +0x34 on, +0x44 intensity, +0x4c/+0x54 cone angles */

void * __cdecl Light_Get(void *set,int index)

{
  if (set == (void *)0x0) {
    set = Set_GetCurrent();
  }
  if ((-1 < index) && (index < *(int *)((int)set + 0xb8))) {
    return (void *)((int)set + index * 0x68 + 0xbc);
  }
  return (void *)0x0;
}

/* ---- 0x004a5cf0  Light_FindByName ---- */
/* Returns the light index in the current set or -1 */

int __cdecl Light_FindByName(void *set,char *name)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (set == (void *)0x0) {
    set = Set_GetCurrent();
  }
  iVar2 = 0;
  if (0 < *(int *)((int)set + 0xb8)) {
    iVar3 = (int)set + 0xbc;
    do {
      iVar1 = _stricmp(name,iVar3);
      if (iVar1 == 0) break;
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x68;
    } while (iVar2 < *(int *)((int)set + 0xb8));
  }
  if (iVar2 < *(int *)((int)set + 0xb8)) {
    return iVar2;
  }
  return -1;
}
