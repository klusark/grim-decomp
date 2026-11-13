/* GRIMFANDANGO.EXE :: textobjects.c
 * functions 0x0048ac40 .. 0x0048ad50 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048ac40  sputText_Update ---- */
/* Expires timed text objects, draws the visible ones (flag 8 or drawAll) and counts down their time
   Original name sputText_Update (the remaster's GrimFandango (Linux): aligned call in
   sputRender_Update); was TextObjects_Update. */

void __cdecl sputText_Update(int drawAll)

{
  TextObject *pTVar1;
  TextObject *obj;
  int iVar2;
  
  if (g_nSputText_Paused == 0) {
    iVar2 = sputTime_GetFrameTime();
    obj = g_pTextQueue;
    while (obj != (TextObject *)0x0) {
      if ((obj->nDuration < 1) && ((obj->dwFlags & 1) == 0)) {
        pTVar1 = obj->pNext;
        List_Unlink(obj);
        obj = pTVar1;
      }
      else {
        if ((((obj->dwFlags & 8) != 0) || (drawAll != 0)) && ((obj->dwFlags & 2) == 0)) {
          TextObject_Draw(obj,1);
        }
        obj->nDuration = obj->nDuration - iVar2;
        obj = obj->pNext;
      }
    }
  }
  return;
}

/* ---- 0x0048ad40  sputText_Pause ---- */
/* Original name sputText_Pause (the remaster's GrimFandango (Linux): aligned call in
   sputRender_Dim); was TextObjects_Freeze. */

void __cdecl sputText_Pause(void)

{
  g_nSputText_Paused = 1;
  return;
}

/* ---- 0x0048ad50  sputText_Resume ---- */
/* Original name sputText_Resume (the remaster's GrimFandango (Linux): aligned call in
   sputRender_Dim); was TextObjects_Unfreeze. */

void __cdecl sputText_Resume(void)

{
  g_nSputText_Paused = 0;
  return;
}
