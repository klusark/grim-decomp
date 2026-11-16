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
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  int aRectA [4];
  int aRectB [4];
  int aRectC [4];
  
  iVar9 = *rect;
  iVar8 = rect[1];
  iVar4 = rect[2] + iVar9;
  iVar5 = rect[3] + iVar8;
  piVar6 = g_pDirtyRectList;
  do {
    while( true ) {
      if (piVar6 == (int *)0x0) {
        piVar6 = Memory_AllocFixed((int *)g_pDirtyRectPool);
        if (piVar6 == (int *)0x0) {
          return;
        }
        g_nDirtyRectCount = g_nDirtyRectCount + 1;
        piVar6[5] = *rect;
        piVar6[6] = rect[1];
        piVar6[7] = rect[2];
        piVar6[8] = rect[3];
        piVar6[2] = flag;
        piVar6[3] = UINT_008c981c;
        UINT_008c981c = UINT_008c981c + 1;
        piVar6[4] = bufferIdx;
        if (g_pDirtyRectList != (void *)0x0) {
          *(int **)((int)g_pDirtyRectList + 4) = piVar6;
        }
        *piVar6 = (int)g_pDirtyRectList;
        piVar6[1] = 0;
        g_pDirtyRectList = piVar6;
        return;
      }
      if (piVar6[4] == bufferIdx) break;
LAB_0048555c:
      piVar6 = (int *)*piVar6;
    }
    iVar1 = piVar6[5];
    iVar2 = piVar6[6];
    iVar11 = piVar6[7] + iVar1;
    iVar10 = piVar6[8] + iVar2;
    if ((((iVar11 <= iVar9) || (iVar4 <= iVar1)) || (iVar10 <= iVar8)) || (iVar5 <= iVar2))
    goto LAB_0048555c;
    if (((iVar1 <= iVar9) && (iVar2 <= iVar8)) && ((iVar4 <= iVar11 && (iVar5 <= iVar10)))) {
      iVar9 = piVar6[2];
      if (piVar6[2] <= flag) {
        iVar9 = flag;
      }
      piVar6[2] = iVar9;
      return;
    }
    if (*piVar6 != 0) {
      *(int *)(*piVar6 + 4) = piVar6[1];
    }
    if ((int *)piVar6[1] == (int *)0x0) {
      g_pDirtyRectList = (void *)*piVar6;
    }
    else {
      *(int *)piVar6[1] = *piVar6;
    }
    if (flag < piVar6[2]) {
      flag = piVar6[2];
    }
    piVar3 = (int *)*piVar6;
    g_nDirtyRectCount = g_nDirtyRectCount + -1;
    Pool_Free(piVar6);
    if (((iVar1 < iVar9) || (iVar4 < iVar1)) ||
       (((iVar2 < iVar8 || (((iVar5 < iVar2 || (iVar11 < iVar9)) || (iVar4 < iVar11)))) ||
        ((iVar10 < iVar8 || (piVar6 = piVar3, iVar5 < iVar10)))))) {
      aRectA[0] = iVar1;
      if (iVar9 <= iVar1) {
        aRectA[0] = iVar9;
      }
      aRectA[1] = iVar8;
      if (iVar8 < iVar2) {
        aRectA[1] = iVar2;
      }
      iVar7 = iVar4;
      if (iVar4 < iVar11) {
        iVar7 = iVar11;
      }
      aRectA[2] = iVar7 - aRectA[0];
      iVar7 = iVar10;
      if (iVar5 <= iVar10) {
        iVar7 = iVar5;
      }
      aRectA[3] = iVar7 - aRectA[1];
      if ((flag == 0) && ((piVar3 == (int *)0x0 || (piVar3[2] == 0)))) {
        iVar7 = 0;
      }
      else {
        iVar7 = 1;
      }
      DirtyRect_Add(aRectA,iVar7,bufferIdx);
      if (iVar2 != iVar8) {
        if (iVar2 < iVar8) {
          aRectB[2] = iVar11 - iVar1;
          aRectB[0] = iVar1;
          aRectB[1] = iVar2;
        }
        else {
          aRectB[2] = iVar4 - iVar9;
          aRectB[0] = iVar9;
          aRectB[1] = iVar8;
        }
        aRectB[3] = aRectA[1] - aRectB[1];
        if ((flag == 0) && ((piVar3 == (int *)0x0 || (piVar3[2] == 0)))) {
          iVar8 = 0;
        }
        else {
          iVar8 = 1;
        }
        DirtyRect_Add(aRectB,iVar8,bufferIdx);
      }
      if (iVar10 == iVar5) {
        return;
      }
      if (iVar5 < iVar10) {
        aRectC[2] = iVar11 - iVar1;
        aRectC[3] = iVar10 - (aRectA[1] + aRectA[3]);
        aRectC[0] = iVar1;
      }
      else {
        aRectC[2] = iVar4 - iVar9;
        aRectC[3] = iVar5 - (aRectA[3] + aRectA[1]);
        aRectC[0] = iVar9;
      }
      aRectC[1] = aRectA[1] + aRectA[3];
      if ((flag == 0) && ((piVar3 == (int *)0x0 || (piVar3[2] == 0)))) {
        iVar9 = 0;
      }
      else {
        iVar9 = 1;
      }
      DirtyRect_Add(aRectC,iVar9,bufferIdx);
      return;
    }
  } while( true );
}

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
  Set *pSVar3;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  item = g_pDirtyRectList;
  pSVar3 = sputRoom_GetCurrentRoom();
  if (pSVar3 != (Set *)0x0) {
    if (((byte)g_dwDebugFlags & 1) != 0) {
      local_10 = g_pSputRender_Canvas->nX0;
      local_c = g_pSputRender_Canvas->nY0;
      local_8 = (g_pSputRender_Canvas->nX1 - g_pSputRender_Canvas->nX0) + 1;
      local_4 = (g_pSputRender_Canvas->nY1 - g_pSputRender_Canvas->nY0) + 1;
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
          stdDisplay_VBufferLock((VBuffer *)&g_dwStdDisplay_backBuffer);
          rdPrimit2_DrawRectangle
                    (g_pRdCamera_CurCamera->pCanvas,*srcRect,item[6],item[7] + *srcRect,
                     item[8] + item[6],UINT_008c9820 & 0xffff,-1);
          stdDisplay_VBufferUnlock((VBuffer *)&g_dwStdDisplay_backBuffer);
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
