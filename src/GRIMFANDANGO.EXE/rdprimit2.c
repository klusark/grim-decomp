/* GRIMFANDANGO.EXE :: rdprimit2.c
 * functions 0x00451b80 .. 0x00451f20 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00451b80  rdPrimit2_DrawLine ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void __cdecl rdPrimit2_DrawLine(void *canvas,int x1,int y1,int x2,int y2,int color,int mask)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar2 = rdClip_Line2D(canvas,&x1,&y1,&x2,&y2);
  if (iVar2 != 0) {
    iVar2 = *(int *)((int)canvas + 4);
    local_10 = 0x80000000;
    if (*(int *)(iVar2 + 0x24) == 8) {
      local_14 = y2 - y1;
      local_c = x2 - x1;
      iVar3 = (((int)local_c < 1) - 1 & 2) - 1;
      iVar4 = (((int)local_14 < 1) - 1 & 2) - 1;
      if (iVar3 < 0) {
        local_14 = -local_14;
      }
      if (0 < iVar4) {
        local_c = -local_c;
      }
      if ((mask & 0x80000000U) != 0) {
        *(undefined1 *)(*(int *)(iVar2 + 0x18) * y1 + *(int *)(iVar2 + 0x5c) + x1) =
             (undefined1)color;
      }
      uVar5 = 0;
      while ((x1 != x2 || (y1 != y2))) {
        local_10 = local_10 >> 1;
        if (local_10 == 0) {
          local_10 = 0x80000000;
        }
        uVar1 = uVar5 + local_14;
        uVar5 = uVar5 + local_c;
        if ((int)((uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f)) <
            (int)((uVar5 ^ (int)uVar5 >> 0x1f) - ((int)uVar5 >> 0x1f))) {
          x1 = x1 + iVar3;
          uVar5 = uVar1;
        }
        else {
          y1 = y1 + iVar4;
        }
        if ((mask & local_10) != 0) {
          *(undefined1 *)
           (*(int *)(*(int *)((int)canvas + 4) + 0x18) * y1 +
            *(int *)(*(int *)((int)canvas + 4) + 0x5c) + x1) = (undefined1)color;
        }
      }
    }
    else {
      local_14 = y2 - y1;
      local_c = x2 - x1;
      iVar3 = (((int)local_c < 1) - 1 & 2) - 1;
      iVar4 = (((int)local_14 < 1) - 1 & 2) - 1;
      if (iVar3 < 0) {
        local_14 = -local_14;
      }
      if (0 < iVar4) {
        local_c = -local_c;
      }
      if ((mask & 0x80000000U) != 0) {
        *(undefined2 *)(*(int *)(iVar2 + 0x5c) + (*(int *)(iVar2 + 0x1c) * y1 + x1) * 2) =
             (undefined2)color;
      }
      uVar5 = 0;
      while ((x1 != x2 || (y1 != y2))) {
        local_10 = local_10 >> 1;
        if (local_10 == 0) {
          local_10 = 0x80000000;
        }
        uVar1 = uVar5 + local_14;
        uVar5 = uVar5 + local_c;
        if ((int)((uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f)) <
            (int)((uVar5 ^ (int)uVar5 >> 0x1f) - ((int)uVar5 >> 0x1f))) {
          x1 = x1 + iVar3;
          uVar5 = uVar1;
        }
        else {
          y1 = y1 + iVar4;
        }
        if ((mask & local_10) != 0) {
          *(undefined2 *)
           (*(int *)(*(int *)((int)canvas + 4) + 0x5c) +
           (*(int *)(*(int *)((int)canvas + 4) + 0x1c) * y1 + x1) * 2) = (undefined2)color;
        }
      }
    }
    return;
  }
  return;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x00451f20  rdPrimit2_DrawRect ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void __cdecl rdPrimit2_DrawRect(void *canvas,int x1,int y1,int x2,int y2,int color,int mask)

{
  rdPrimit2_DrawLine(canvas,x1,y1,x2,y1,color,mask);
  rdPrimit2_DrawLine(canvas,x2,y1,x2,y2,color,mask);
  rdPrimit2_DrawLine(canvas,x1,y1,x1,y2,color,mask);
  rdPrimit2_DrawLine(canvas,x1,y2,x2,y2,color,mask);
  return;
}
#endif

