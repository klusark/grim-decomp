/* GRIMFANDANGO.EXE :: textobject.c
 * functions 0x0048c470 .. 0x0048cba0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048c470  TextObject_Activate ---- */
/* Links a new text object into g_pTextObjectList with its lifetime (ms, -1 = until killed) and
   flags (1 keep, 2 hidden, 4 speech, 8 always draw) */

void __cdecl TextObject_Activate(void *obj,int durationMs,int flags)

{
  int iVar1;
  
  if (obj != (void *)0x0) {
    *(int *)((int)obj + 0x250) = durationMs;
    *(int *)((int)obj + 600) = flags;
    *(undefined4 *)((int)obj + 0x238) = *(undefined4 *)((int)obj + 0x214);
    iVar1 = *(int *)((int)obj + 0x218) - *(int *)(**(int **)((int)obj + 0x210) + 8);
    *(int *)((int)obj + 0x23c) = iVar1;
    *(int *)((int)obj + 0x218) = iVar1;
    *(void **)obj = g_pTextObjectList;
    if (g_pTextObjectList != (void *)0x0) {
      *(void **)((int)g_pTextObjectList + 4) = obj;
    }
    g_pTextObjectList = obj;
  }
  return;
}

/* ---- 0x0048c7e0  TextObject_New ---- */
void * __cdecl TextObject_New(void *ctx,char *text,int durationMs,int flags)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar1 = (undefined4 *)Pool_Alloc(g_pTextObjectPool);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
    puVar1[1] = 0;
    strncpy(puVar1 + 2,text,0x1ff);
    *(undefined1 *)((int)puVar1 + 0x207) = 0;
    puVar1[0x8e] = *(undefined4 *)((int)ctx + 0xc);
    puVar1[0x8f] = *(undefined4 *)((int)ctx + 0x10);
    puVar3 = ctx;
    puVar4 = puVar1 + 0x82;
    for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    if (g_pOverrideFont != (void *)0x0) {
      puVar1[0x84] = g_pOverrideFont;
    }
    puVar3 = puVar1 + 0x90;
    puVar1[0x8d] = g_wTextColors;
    puVar1[0x83] = puVar3;
    puVar4 = *(undefined4 **)((int)ctx + 4);
    if (puVar4 != (undefined4 *)0x0) {
      *puVar3 = *puVar4;
      puVar1[0x91] = puVar4[1];
      puVar1[0x92] = puVar4[2];
      puVar1[0x93] = puVar4[3];
      puVar1[0x95] = 0;
      puVar1[0x97] = puVar1;
      return puVar1;
    }
    *puVar3 = 0;
    puVar1[0x91] = 0;
    puVar1[0x92] = UINT_008a94bc;
    puVar1[0x93] = UINT_008a94c0;
    puVar1[0x95] = 0;
    puVar1[0x97] = puVar1;
  }
  return puVar1;
}

/* ---- 0x0048c9f0  TextObject_Draw ---- */
void __cdecl TextObject_Draw(void *obj,int invalidate)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (obj != (void *)0x0) {
    local_10 = *(uint *)((int)obj + 0x238);
    *(uint *)((int)obj + 0x214) = local_10;
    iVar4 = *(int *)(**(int **)((int)obj + 0x210) + 8) + *(int *)((int)obj + 0x23c);
    *(int *)((int)obj + 0x218) = iVar4;
    local_c = iVar4 - *(int *)(**(int **)((int)obj + 0x210) + 8);
    local_8 = Text_MeasureWidth((void *)((int)obj + 0x208),(char *)((int)obj + 8));
    local_4 = Text_MeasureHeight((void *)((int)obj + 0x208),(char *)((int)obj + 8));
    if ((*(byte *)((int)obj + 0x230) & 1) != 0) {
      local_10 = local_10 - (int)local_8 / 2;
    }
    uVar1 = *(uint *)((int)obj + 0x21c);
    g_wTextColors[0] =
         (ushort)((uVar1 >> 10 & 0x3f | ((int)uVar1 >> 3) << 6) << 5) |
         (ushort)(uVar1 >> 0x13) & 0x1f;
    uVar2 = *(uint *)((int)obj + 0x220);
    g_wTextColors[1] =
         (ushort)((uVar2 >> 10 & 0x3f | ((int)uVar2 >> 3) << 6) << 5) |
         (ushort)(uVar2 >> 0x13) & 0x1f;
    uVar3 = *(uint *)((int)obj + 0x224);
    g_wTextColors[2] =
         (ushort)((uVar3 >> 10 & 0x3f | ((int)uVar3 >> 3) << 6) << 5) |
         (ushort)(uVar3 >> 0x13) & 0x1f;
    sputRender_ColorCorrect(g_wTextColors,3);
    *(undefined4 *)((int)obj + 0x21c) = 0;
    *(undefined4 *)((int)obj + 0x220) = 1;
    *(undefined4 *)((int)obj + 0x224) = 2;
    Text_DrawFormatted((int)obj + 0x208,(int)obj + 8);
    *(undefined4 *)((int)obj + 0x214) = *(undefined4 *)((int)obj + 0x238);
    *(int *)((int)obj + 0x218) =
         *(int *)(**(int **)((int)obj + 0x210) + 8) + *(int *)((int)obj + 0x23c);
    if (invalidate != 0) {
      Render_InvalidateRectLastBuffer((int *)&local_10,0);
    }
    *(uint *)((int)obj + 0x224) = uVar3;
    *(uint *)((int)obj + 0x220) = uVar2;
    *(uint *)((int)obj + 0x21c) = uVar1;
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0048cba0  TextObject_FindBySelf ---- */
undefined4 * TextObject_FindBySelf(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = g_pTextObjectList;
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    if (puVar1[0x97] == param_1) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}
