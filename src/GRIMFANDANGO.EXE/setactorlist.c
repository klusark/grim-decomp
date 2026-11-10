/* GRIMFANDANGO.EXE :: setactorlist.c
 * functions 0x004a6160 .. 0x004a6160 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a6160  SetActorList_Free ---- */
/* Unlinks a node from the g_pRoomList list (per-set actor lists, link at +0x84) and frees it. */

void SetActorList_Free(void *param_1)

{
  void *pvVar1;
  void *pvVar2;
  void *pvVar3;
  
  pvVar3 = (void *)0x0;
  pvVar2 = g_pRoomList;
  if (g_pRoomList != (void *)0x0) {
    do {
      pvVar1 = pvVar2;
      pvVar2 = pvVar1;
      if (pvVar1 == param_1) break;
      pvVar2 = *(void **)((int)pvVar1 + 0x84);
      pvVar3 = pvVar1;
    } while (pvVar2 != (void *)0x0);
    if (pvVar2 != (void *)0x0) {
      if (pvVar3 == (void *)0x0) {
        g_pRoomList = *(void **)((int)pvVar2 + 0x84);
        (*g_pSputRoomHS->pFree)(pvVar2);
        return;
      }
      *(undefined4 *)((int)pvVar3 + 0x84) = *(undefined4 *)((int)pvVar2 + 0x84);
      (*g_pSputRoomHS->pFree)(pvVar2);
    }
  }
  return;
}
