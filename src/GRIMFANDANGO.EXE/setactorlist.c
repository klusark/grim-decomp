/* GRIMFANDANGO.EXE :: setactorlist.c
 * functions 0x004a6160 .. 0x004a6160 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a6160  SetActorList_Free ---- */
/* Unlinks a node from the g_pRoomList list (per-set actor lists, link at +0x84) and frees it. */

void __cdecl SetActorList_Free(RoomActors *list)

{
  RoomActors *pRVar1;
  RoomActors *pRVar2;
  RoomActors *pRVar3;
  
  pRVar3 = (RoomActors *)0x0;
  pRVar2 = g_pRoomList;
  if (g_pRoomList != (RoomActors *)0x0) {
    do {
      pRVar1 = pRVar2;
      pRVar2 = pRVar1;
      if (pRVar1 == list) break;
      pRVar2 = pRVar1->pNext;
      pRVar3 = pRVar1;
    } while (pRVar2 != (RoomActors *)0x0);
    if (pRVar2 != (RoomActors *)0x0) {
      if (pRVar3 == (RoomActors *)0x0) {
        g_pRoomList = pRVar2->pNext;
        (*g_pSputRoomHS->pFree)(pRVar2);
        return;
      }
      pRVar3->pNext = pRVar2->pNext;
      (*g_pSputRoomHS->pFree)(pRVar2);
    }
  }
  return;
}
