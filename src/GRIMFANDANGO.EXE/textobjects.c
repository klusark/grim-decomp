/* GRIMFANDANGO.EXE :: textobjects.c
 * functions 0x0048ac40 .. 0x0048ad50 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048ac40  TextObjects_Update ---- */
/* Expires timed text objects, draws the visible ones (flag 8 or drawAll) and counts down their time
    */

void __cdecl TextObjects_Update(int drawAll)

{
  undefined4 *puVar1;
  undefined4 *obj;
  int iVar2;
  
  if (g_nTextObjectsFrozen == 0) {
    iVar2 = Timer_GetFrameMs();
    obj = g_pTextObjectList;
    while (obj != (undefined4 *)0x0) {
      if (((int)obj[0x94] < 1) && ((*(byte *)(obj + 0x96) & 1) == 0)) {
        puVar1 = (undefined4 *)*obj;
        List_Unlink(obj);
        obj = puVar1;
      }
      else {
        if ((((obj[0x96] & 8) != 0) || (drawAll != 0)) && ((obj[0x96] & 2) == 0)) {
          TextObject_Draw(obj,1);
        }
        obj[0x94] = obj[0x94] - iVar2;
        obj = (undefined4 *)*obj;
      }
    }
  }
  return;
}

/* ---- 0x0048ad40  TextObjects_Freeze ---- */
void TextObjects_Freeze(void)

{
  g_nTextObjectsFrozen = 1;
  return;
}

/* ---- 0x0048ad50  TextObjects_Unfreeze ---- */
void TextObjects_Unfreeze(void)

{
  g_nTextObjectsFrozen = 0;
  return;
}
