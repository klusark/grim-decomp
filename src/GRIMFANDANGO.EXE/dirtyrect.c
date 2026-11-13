/* GRIMFANDANGO.EXE :: dirtyrect.c
 * functions 0x00485420 .. 0x00486020 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00485420  DirtyRect_Add ---- */
/* Adds a dirty rectangle for one display buffer. Rectangles contained in an existing one are
   merged; partial overlaps are split into up to three non-overlapping pieces (recursive). Records
   come from g_pDirtyRectPool. */

void __cdecl DirtyRect_Add(int *rect,int flag,int bufferIdx)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  #define local_44 (*(uint *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x60 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x60 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x60 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x60 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x60 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x60 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x60 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x60 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x60 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x60 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x60 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x60 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x60 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x60 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x60 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x60 - 0x4)))
  
  uVar1 = *rect;
  uVar2 = rect[1];
  iVar6 = rect[2] + uVar1;
  iVar7 = rect[3] + uVar2;
  piVar8 = g_pDirtyRectList;
  do {
    while( true ) {
      if (piVar8 == (int *)0x0) {
        piVar8 = Memory_AllocFixed((int *)g_pDirtyRectPool);
        if (piVar8 == (int *)0x0) {
          return;
        }
        g_nDirtyRectCount = g_nDirtyRectCount + 1;
        piVar8[5] = *rect;
        piVar8[6] = rect[1];
        piVar8[7] = rect[2];
        piVar8[8] = rect[3];
        piVar8[2] = flag;
        piVar8[3] = UINT_008c981c;
        UINT_008c981c = UINT_008c981c + 1;
        piVar8[4] = bufferIdx;
        if (g_pDirtyRectList != (void *)0x0) {
          *(int **)((int)g_pDirtyRectList + 4) = piVar8;
        }
        *piVar8 = (int)g_pDirtyRectList;
        piVar8[1] = 0;
        g_pDirtyRectList = piVar8;
        return;
      }
      if (piVar8[4] == bufferIdx) break;
LAB_0048555c:
      piVar8 = (int *)*piVar8;
    }
    uVar3 = piVar8[5];
    uVar4 = piVar8[6];
    iVar11 = piVar8[7] + uVar3;
    iVar10 = piVar8[8] + uVar4;
    if ((((iVar11 <= (int)uVar1) || (iVar6 <= (int)uVar3)) || (iVar10 <= (int)uVar2)) ||
       (iVar7 <= (int)uVar4)) goto LAB_0048555c;
    if ((((int)uVar3 <= (int)uVar1) && ((int)uVar4 <= (int)uVar2)) &&
       ((iVar6 <= iVar11 && (iVar7 <= iVar10)))) {
      iVar6 = piVar8[2];
      if (piVar8[2] <= flag) {
        iVar6 = flag;
      }
      piVar8[2] = iVar6;
      return;
    }
    if (*piVar8 != 0) {
      *(int *)(*piVar8 + 4) = piVar8[1];
    }
    if ((int *)piVar8[1] == (int *)0x0) {
      g_pDirtyRectList = (void *)*piVar8;
    }
    else {
      *(int *)piVar8[1] = *piVar8;
    }
    if (flag < piVar8[2]) {
      flag = piVar8[2];
    }
    piVar5 = (int *)*piVar8;
    g_nDirtyRectCount = g_nDirtyRectCount + -1;
    Pool_Free(piVar8);
    if ((((int)uVar3 < (int)uVar1) || (iVar6 < (int)uVar3)) ||
       ((((int)uVar4 < (int)uVar2 ||
         (((iVar7 < (int)uVar4 || (iVar11 < (int)uVar1)) || (iVar6 < iVar11)))) ||
        ((iVar10 < (int)uVar2 || (piVar8 = piVar5, iVar7 < iVar10)))))) {
      local_30 = uVar3;
      if ((int)uVar1 <= (int)uVar3) {
        local_30 = uVar1;
      }
      local_2c = uVar2;
      if ((int)uVar2 < (int)uVar4) {
        local_2c = uVar4;
      }
      iVar9 = iVar6;
      if (iVar6 < iVar11) {
        iVar9 = iVar11;
      }
      local_28 = iVar9 - local_30;
      iVar9 = iVar10;
      if (iVar7 <= iVar10) {
        iVar9 = iVar7;
      }
      local_24 = iVar9 - local_2c;
      if ((flag == 0) && ((piVar5 == (int *)0x0 || (piVar5[2] == 0)))) {
        iVar9 = 0;
      }
      else {
        iVar9 = 1;
      }
      DirtyRect_Add((int *)&local_30,iVar9,bufferIdx);
      if (uVar4 != uVar2) {
        if ((int)uVar4 < (int)uVar2) {
          local_18 = iVar11 - uVar3;
          local_20 = uVar3;
          local_1c = uVar4;
        }
        else {
          local_18 = iVar6 - uVar1;
          local_20 = uVar1;
          local_1c = uVar2;
        }
        local_14 = local_2c - local_1c;
        if ((flag == 0) && ((piVar5 == (int *)0x0 || (piVar5[2] == 0)))) {
          iVar9 = 0;
        }
        else {
          iVar9 = 1;
        }
        DirtyRect_Add((int *)&local_20,iVar9,bufferIdx);
      }
      if (iVar10 == iVar7) {
        return;
      }
      if (iVar7 < iVar10) {
        local_8 = iVar11 - uVar3;
        local_4 = iVar10 - (local_2c + local_24);
        local_10 = uVar3;
      }
      else {
        local_8 = iVar6 - uVar1;
        local_4 = iVar7 - (local_24 + local_2c);
        local_10 = uVar1;
      }
      local_c = local_2c + local_24;
      if ((flag == 0) && ((piVar5 == (int *)0x0 || (piVar5[2] == 0)))) {
        iVar6 = 0;
      }
      else {
        iVar6 = 1;
      }
      DirtyRect_Add((int *)&local_10,iVar6,bufferIdx);
      return;
    }
  } while( true );
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_4
#undef local_40
#undef local_44
#undef local_8
#undef local_c


/* ---- 0x00485e50  DirtyRect_Flush ---- */
/* Restores every dirty rectangle from the background and depth images, dropping records whose
   per-buffer countdown expired; debug flag 0x10 outlines them */

void __cdecl DirtyRect_Flush(void *dst,void *zdst)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *srcRect;
  int iVar1;
  int *piVar2;
  int *item;
  void *pvVar3;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  item = g_pDirtyRectList;
  pvVar3 = sputRoom_GetCurrentRoom();
  if (pvVar3 != (void *)0x0) {
    if (((byte)g_dwDebugFlags & 1) != 0) {
      local_10 = *(uint *)((int)g_pSputRender_Canvas + 0x18);
      local_c = *(uint *)((int)g_pSputRender_Canvas + 0x1c);
      local_8 = (*(int *)((int)g_pSputRender_Canvas + 0x20) -
                *(int *)((int)g_pSputRender_Canvas + 0x18)) + 1;
      local_4 = (*(int *)((int)g_pSputRender_Canvas + 0x24) -
                *(int *)((int)g_pSputRender_Canvas + 0x1c)) + 1;
      Surface_Blit(dst,g_pSputRender_CleanBuffer,local_10,local_c,(int *)&local_10,0);
    }
    PIECE(UINT_008c9820,0,2) = (short)UINT_008c9820 + 1;
    while (item != (int *)0x0) {
      srcRect = (uint *)(item + 5);
      if ((zdst != (void *)0x0) && (item[2] != 0)) {
        if (((byte)g_dwRenderFlags & 2) == 0) {
          Surface_Blit(zdst,g_pSputRender_CleanZBuffer,*srcRect,item[6],(int *)srcRect,0);
        }
        else if (g_nSputRender_b3DAcceleration == 0) {
          Surface_Fill(zdst,0,(int *)srcRect);
        }
        else {
          D3D_SetViewportRect(srcRect);
          std3D_ClearZBuffer();
        }
      }
      iVar1 = item[4];
      item[4] = iVar1 + -1;
      if (iVar1 < 1) {
        if (((byte)g_dwRenderFlags & 1) == 0) {
          Surface_Blit(dst,g_pSputRender_CleanBuffer,*srcRect,item[6],(int *)srcRect,0);
        }
        else {
          Surface_Fill(dst,0,(int *)srcRect);
        }
        if (*item != 0) {
          *(int *)(*item + 4) = item[1];
        }
        if ((int *)item[1] != (int *)0x0) {
          *(int *)item[1] = *item;
        }
        if (item == g_pDirtyRectList) {
          g_pDirtyRectList = (void *)*item;
        }
        if ((((byte)g_dwDebugFlags & 1) != 0) && (((byte)g_dwDebugFlags & 0x10) != 0)) {
          stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
          rdPrimit2_DrawRectangle
                    (*(void **)((int)g_pRdCamera_CurCamera + 4),*srcRect,item[6],item[7] + *srcRect,
                     item[8] + item[6],UINT_008c9820 & 0xffff,-1);
          stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
        }
        piVar2 = (int *)*item;
        g_nDirtyRectCount = g_nDirtyRectCount + -1;
        Pool_Free(item);
        item = piVar2;
      }
      else {
        item = (int *)*item;
      }
    }
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00486020  DirtyRect_Clear ---- */
void __cdecl DirtyRect_Clear(void)

{
  void *pvVar1;
  
  if (g_pDirtyRectList != (void *)0x0) {
    do {
      pvVar1 = *(void **)g_pDirtyRectList;
      Pool_Free(g_pDirtyRectList);
      g_pDirtyRectList = pvVar1;
    } while (pvVar1 != (void *)0x0);
    g_pDirtyRectList = (void *)0x0;
  }
  g_nDirtyRectCount = 0;
  return;
}
