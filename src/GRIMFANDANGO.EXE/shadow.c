/* GRIMFANDANGO.EXE :: shadow.c
 * functions 0x00494890 .. 0x00494bf0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00494890  Shadow_SetColor ---- */
/* Lua SetShadowColor */

void __cdecl Shadow_SetColor(int r,int g,int b)

{
  int iVar1;
  int iVar2;
  
  iVar1 = g;
  g = (g >> 2 | (r >> 3) << 6) << 5 | b >> 3;
  Render_RemapPixels((ushort *)&g,1);
  if (g_pShadowColormap == (void *)0x0) {
    g_pShadowColormap = rdColormap_Load(s_shadow_cmp_004ea190);
  }
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 2;
    *(undefined2 *)(*(int *)((int)g_pShadowColormap + 0x348) + -2 + iVar2) = (undefined2)g;
  } while (iVar2 < 0x8000);
  iVar2 = 0;
  do {
    *(undefined1 *)(iVar2 + 0x30 + (int)g_pShadowColormap) = (undefined1)r;
    *(char *)(iVar2 + 0x31 + (int)g_pShadowColormap) = (char)iVar1;
    *(undefined1 *)(iVar2 + 0x32 + (int)g_pShadowColormap) = (undefined1)b;
    iVar2 = iVar2 + 3;
  } while (iVar2 < 0x300);
  return;
}

/* ---- 0x00494bf0  Shadow_DrawClippedPoly ---- */
/* Clips the projected polygon against each sector of the shadow plane and draws it, growing the
   dirty box */

void __cdecl Shadow_DrawClippedPoly(float *verts,int count,float *minXY,float *maxXY,void *shadow)

{
  unsigned char _frame[0xd0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int count_00;
  void *pvVar2;
  undefined4 *puVar3;
  #define local_b4 (*(int *)(_frame + (0xd0 - 0xb4)))
  #define local_90 (*(float (*)[36])(_frame + (0xd0 - 0x90)))
  
  local_b4 = 0;
  puVar3 = (undefined4 *)((int)shadow + 0x24);
  do {
    if ((void *)*puVar3 == (void *)0x0) {
      return;
    }
    count_00 = Sector_ClipPolygon((void *)*puVar3,(int)verts,count,(int)local_90);
    if ((2 < count_00) &&
       (pvVar2 = rdPrimit3_DrawPolygon(local_90,count_00,g_pShadowMaterial), pvVar2 != (void *)0x0))
    {
      fVar1 = (float)*(uint *)((int)pvVar2 + 0x54);
      if (*minXY < fVar1) {
        fVar1 = *minXY;
      }
      *minXY = fVar1;
      fVar1 = (float)*(uint *)((int)pvVar2 + 0x5c);
      if (minXY[1] < fVar1) {
        fVar1 = minXY[1];
      }
      minXY[1] = fVar1;
      fVar1 = (float)*(uint *)((int)pvVar2 + 0x58);
      if (fVar1 < *maxXY) {
        fVar1 = *maxXY;
      }
      *maxXY = fVar1;
      fVar1 = (float)*(uint *)((int)pvVar2 + 0x60);
      if (fVar1 < maxXY[1]) {
        fVar1 = maxXY[1];
      }
      maxXY[1] = fVar1;
    }
    puVar3 = puVar3 + 1;
    local_b4 = local_b4 + 1;
  } while (local_b4 < 0xc);
  return;
}
#undef local_90
#undef local_b4

