/* GRIMFANDANGO.EXE :: cacherect.c
 * functions 0x00486b40 .. 0x00486cb0 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00486b40  sputRender_CreateCacheRect ---- */
/* Lua CacheRect: copies a rectangle of the background and depth images into a 0x20-byte record
   {magic, x, y, w, h, bgCopy, zCopy, next} on g_pCacheRectList Original name
   sputRender_CreateCacheRect (the remaster's GrimFandango (Linux): same body (allocates the
   0x20-byte record in sputRender.cpp, tag 0x11111111, the rectangle, copies the clean buffer's
   format); called by sputLua_CacheRect in both builds); was CacheRect_Create. */

void * __cdecl sputRender_CreateCacheRect(int x,int y,int w,int h)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *srcRect;
  undefined4 *puVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *piVar6;
  #define aiStack_4c (*(int (*)[19])(_frame + (0x60 - 0x4c)))
  
  puVar1 = (undefined4 *)
           (*g_pSputRendHS->pAlloc)(0x20,s_C__grimsrc_libs_grimlib_Engine_s_004e80bc,0x9ba);
  if (puVar1 == (undefined4 *)0x0) {
    return (void *)0x0;
  }
  srcRect = puVar1 + 1;
  puVar5 = puVar1;
  for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  *puVar1 = 0x11111111;
  *srcRect = x;
  puVar1[2] = y;
  puVar1[3] = w;
  puVar1[4] = h;
  piVar4 = (int *)((int)g_pSputRender_CleanBuffer + 0xc);
  piVar6 = aiStack_4c;
  for (iVar3 = 0x13; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar6 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar6 = piVar6 + 1;
  }
  aiStack_4c[1] = h;
  aiStack_4c[0] = w;
  pvVar2 = stdDisplay_VBufferNew(aiStack_4c,0,0,0);
  puVar1[5] = pvVar2;
  Surface_Blit(pvVar2,g_pSputRender_CleanBuffer,0,0,srcRect,0);
  piVar4 = (int *)((int)g_pSputRender_CleanZBuffer + 0xc);
  piVar6 = aiStack_4c;
  for (iVar3 = 0x13; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar6 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar6 = piVar6 + 1;
  }
  aiStack_4c[0] = w;
  aiStack_4c[1] = h;
  pvVar2 = stdDisplay_VBufferNew(aiStack_4c,0,0,0);
  puVar1[6] = pvVar2;
  Surface_Blit(pvVar2,g_pSputRender_CleanZBuffer,0,0,srcRect,0);
  puVar1[7] = g_pCacheRectList;
  g_pCacheRectList = puVar1;
  return puVar1;
}
#undef aiStack_4c


/* ---- 0x00486c50  sputRender_RestoreCacheRect ---- */
/* Lua RestoreCacheRect: copies the most recent cached rectangle back and invalidates it Original
   name sputRender_RestoreCacheRect (the remaster's GrimFandango (Linux): aligned call in
   sputLua_RestoreCacheRect); was CacheRect_Restore. */

void __cdecl sputRender_RestoreCacheRect(int unused)

{
  int *piVar1;
  int *rect;
  void *pvVar2;
  
  pvVar2 = g_pCacheRectList;
  piVar1 = (int *)((int)g_pCacheRectList + 8);
  rect = (int *)((int)g_pCacheRectList + 4);
  Surface_Blit(g_pSputRender_CleanBuffer,*(void **)((int)g_pCacheRectList + 0x14),
               *(int *)((int)g_pCacheRectList + 4),*(int *)((int)g_pCacheRectList + 8),(int *)0x0,0)
  ;
  Surface_Blit(g_pSputRender_CleanZBuffer,*(void **)((int)pvVar2 + 0x18),*rect,*piVar1,(int *)0x0,0)
  ;
  MarkDirtyRect(rect,1);
  return;
}

/* ---- 0x00486cb0  CacheRect_FreeAll ---- */
void CacheRect_FreeAll(void)

{
  void *pvVar1;
  
  pvVar1 = g_pCacheRectList;
  while (pvVar1 != (void *)0x0) {
    g_pCacheRectList = *(void **)((int)pvVar1 + 0x1c);
    if (*(void **)((int)pvVar1 + 0x14) != (void *)0x0) {
      stdDisplay_VBufferFree(*(void **)((int)pvVar1 + 0x14));
    }
    if (*(void **)((int)pvVar1 + 0x18) != (void *)0x0) {
      stdDisplay_VBufferFree(*(void **)((int)pvVar1 + 0x18));
    }
    (*g_pSputRendHS->pFree)(pvVar1);
    pvVar1 = g_pCacheRectList;
  }
  g_pCacheRectList = pvVar1;
  return;
}
