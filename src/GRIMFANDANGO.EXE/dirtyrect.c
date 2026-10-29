/* GRIMFANDANGO.EXE :: dirtyrect.c
 * functions 0x00485420 .. 0x004860d0 (6 functions)
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
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int *piVar3;
  int *item;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int flag_00;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  #define local_30 (*(int *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(int *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(int *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(int *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(int *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(int *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(int *)(_frame + (0x40 - 0x10)))
  #define local_c (*(int *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x40 - 0x4)))
  
  iVar8 = *rect;
  iVar7 = rect[1];
  iVar4 = rect[2] + iVar8;
  iVar5 = rect[3] + iVar7;
  item = g_pDirtyRectList;
  do {
    while( true ) {
      if (item == (int *)0x0) {
        puVar6 = (undefined4 *)Pool_Alloc(g_pDirtyRectPool);
        if (puVar6 == (undefined4 *)0x0) {
          return;
        }
        g_nDirtyRectCount = g_nDirtyRectCount + 1;
        puVar6[5] = *rect;
        puVar6[6] = rect[1];
        puVar6[7] = rect[2];
        puVar6[8] = rect[3];
        puVar6[2] = flag;
        puVar6[3] = DAT_008c981c;
        DAT_008c981c = DAT_008c981c + 1;
        puVar6[4] = bufferIdx;
        if (g_pDirtyRectList != (void *)0x0) {
          *(undefined4 **)((int)g_pDirtyRectList + 4) = puVar6;
        }
        *puVar6 = g_pDirtyRectList;
        puVar6[1] = 0;
        g_pDirtyRectList = puVar6;
        return;
      }
      if (item[4] == bufferIdx) break;
LAB_0048555c:
      item = (int *)*item;
    }
    iVar1 = item[5];
    iVar2 = item[6];
    iVar10 = item[7] + iVar1;
    iVar9 = item[8] + iVar2;
    if ((((iVar10 <= iVar8) || (iVar4 <= iVar1)) || (iVar9 <= iVar7)) || (iVar5 <= iVar2))
    goto LAB_0048555c;
    if (((iVar1 <= iVar8) && (iVar2 <= iVar7)) && ((iVar4 <= iVar10 && (iVar5 <= iVar9)))) {
      iVar8 = item[2];
      if (item[2] <= flag) {
        iVar8 = flag;
      }
      item[2] = iVar8;
      return;
    }
    if (*item != 0) {
      *(int *)(*item + 4) = item[1];
    }
    if ((int *)item[1] == (int *)0x0) {
      g_pDirtyRectList = (void *)*item;
    }
    else {
      *(int *)item[1] = *item;
    }
    if (flag < item[2]) {
      flag = item[2];
    }
    piVar3 = (int *)*item;
    g_nDirtyRectCount = g_nDirtyRectCount + -1;
    Pool_Free(item);
    if (((iVar1 < iVar8) || (iVar4 < iVar1)) ||
       (((iVar2 < iVar7 || (((iVar5 < iVar2 || (iVar10 < iVar8)) || (iVar4 < iVar10)))) ||
        ((iVar9 < iVar7 || (item = piVar3, iVar5 < iVar9)))))) {
      local_30 = iVar1;
      if (iVar8 <= iVar1) {
        local_30 = iVar8;
      }
      local_2c = iVar7;
      if (iVar7 < iVar2) {
        local_2c = iVar2;
      }
      local_28 = iVar4;
      if (iVar4 < iVar10) {
        local_28 = iVar10;
      }
      local_28 = local_28 - local_30;
      local_24 = iVar9;
      if (iVar5 <= iVar9) {
        local_24 = iVar5;
      }
      local_24 = local_24 - local_2c;
      if ((flag == 0) && ((piVar3 == (int *)0x0 || (piVar3[2] == 0)))) {
        flag_00 = 0;
      }
      else {
        flag_00 = 1;
      }
      DirtyRect_Add(&local_30,flag_00,bufferIdx);
      if (iVar2 != iVar7) {
        if (iVar2 < iVar7) {
          local_18 = iVar10 - iVar1;
          local_20 = iVar1;
          local_1c = iVar2;
        }
        else {
          local_18 = iVar4 - iVar8;
          local_20 = iVar8;
          local_1c = iVar7;
        }
        local_14 = local_2c - local_1c;
        if ((flag == 0) && ((piVar3 == (int *)0x0 || (piVar3[2] == 0)))) {
          iVar7 = 0;
        }
        else {
          iVar7 = 1;
        }
        DirtyRect_Add(&local_20,iVar7,bufferIdx);
      }
      if (iVar9 == iVar5) {
        return;
      }
      if (iVar5 < iVar9) {
        local_8 = iVar10 - iVar1;
        local_4 = iVar9 - (local_2c + local_24);
        local_10 = iVar1;
      }
      else {
        local_8 = iVar4 - iVar8;
        local_4 = iVar5 - (local_24 + local_2c);
        local_10 = iVar8;
      }
      local_c = local_2c + local_24;
      if ((flag == 0) && ((piVar3 == (int *)0x0 || (piVar3[2] == 0)))) {
        iVar8 = 0;
      }
      else {
        iVar8 = 1;
      }
      DirtyRect_Add(&local_10,iVar8,bufferIdx);
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
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00485e50  DirtyRect_Flush ---- */
/* Restores every dirty rectangle from the background and depth images, dropping records whose
   per-buffer countdown expired; debug flag 0x10 outlines them */

void __cdecl DirtyRect_Flush(void *dst,void *zdst)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  int *item;
  void *pvVar3;
  #define local_10 (*(int *)(_frame + (0x20 - 0x10)))
  #define local_c (*(int *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  item = g_pDirtyRectList;
  pvVar3 = Set_GetCurrent();
  if (pvVar3 != (void *)0x0) {
    if (((byte)g_dwRenderDebugFlags & 1) != 0) {
      local_10 = *(int *)((int)g_pCanvas + 0x18);
      local_c = *(int *)((int)g_pCanvas + 0x1c);
      local_8 = (*(int *)((int)g_pCanvas + 0x20) - *(int *)((int)g_pCanvas + 0x18)) + 1;
      local_4 = (*(int *)((int)g_pCanvas + 0x24) - *(int *)((int)g_pCanvas + 0x1c)) + 1;
      Surface_Blit(dst,g_pBackgroundSurface,local_10,local_c,&local_10,0);
    }
    PIECE(DAT_008c9820,0,2) = (short)DAT_008c9820 + 1;
    while (item != (int *)0x0) {
      piVar2 = item + 5;
      if ((zdst != (void *)0x0) && (item[2] != 0)) {
        if (((byte)g_dwRenderFlags & 2) == 0) {
          Surface_Blit(zdst,g_pZBufferSurface,*piVar2,item[6],piVar2,0);
        }
        else if (g_nZBufferEnabled == 0) {
          Surface_Fill(zdst,0,piVar2);
        }
        else {
          ((code *)D3D_SetViewportRect)();
          D3D_ClearZBuffer();
        }
      }
      iVar1 = item[4];
      item[4] = iVar1 + -1;
      if (iVar1 < 1) {
        if (((byte)g_dwRenderFlags & 1) == 0) {
          Surface_Blit(dst,g_pBackgroundSurface,*piVar2,item[6],piVar2,0);
        }
        else {
          Surface_Fill(dst,0,piVar2);
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
        if ((((byte)g_dwRenderDebugFlags & 1) != 0) && (((byte)g_dwRenderDebugFlags & 0x10) != 0)) {
          Surface_Lock(&DAT_009055e0);
          rdPrimit2_DrawRect(*(void **)((int)g_pRdCurrentCamera + 4),*piVar2,item[6],
                             item[7] + *piVar2,item[8] + item[6],DAT_008c9820 & 0xffff,-1);
          Surface_Unlock(&DAT_009055e0);
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
void DirtyRect_Clear(void)

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

/* ---- 0x00486050  FUN_00486050 ---- */
void FUN_00486050(void)

{
  g_pSvcRender = (GrimServices *)0x0;
  if (DAT_008c9788 != 0) {
    DAT_008c9788 = 0;
  }
  return;
}

/* ---- 0x00486070  FUN_00486070 ---- */
bool FUN_00486070(void)

{
  bool bVar1;
  
  bVar1 = DAT_008c978c != 0;
  if (!bVar1) {
    DAT_008c978c = 1;
    DAT_008a9510 = 4;
    DAT_008a9514 = 3;
    DAT_008a9518 = 1;
    DAT_008a951c = 1;
    DAT_008a9520 = 0;
    DAT_008a9524 = 0;
    DAT_008a9528 = 2;
    g_pDirtyRectPool = (void **)Pool_Create(0x24,0x20,8);
  }
  return bVar1;
}

/* ---- 0x004860d0  FUN_004860d0 ---- */
void FUN_004860d0(void)

{
  CacheRect_FreeAll();
  if (g_pDirtyRectPool != (void **)0x0) {
    Pool_Destroy(g_pDirtyRectPool);
    g_pDirtyRectPool = (void **)0x0;
  }
  DAT_008c978c = 0;
  return;
}
