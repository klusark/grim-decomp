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
  CacheRect *pCVar1;
  VBuffer *pVVar2;
  int iVar3;
  VBufferFormat *pVVar4;
  CacheRect *pCVar5;
  VBufferFormat *pVVar6;
  #define VStack_4c (*(VBufferFormat *)(_frame + (0x60 - 0x4c)))
  
  pCVar1 = (CacheRect *)
           (*g_pSputRendHS->pAlloc)(0x20,s_C__grimsrc_libs_grimlib_Engine_s_004e80bc,0x9ba);
  if (pCVar1 == (CacheRect *)0x0) {
    return (void *)0x0;
  }
  srcRect = &pCVar1->nX;
  pCVar5 = pCVar1;
  for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
    pCVar5->dwMagic = 0;
    pCVar5 = (CacheRect *)&pCVar5->nX;
  }
  pCVar1->dwMagic = 0x11111111;
  *srcRect = x;
  pCVar1->nY = y;
  pCVar1->nWidth = w;
  pCVar1->nHeight = h;
  pVVar4 = &g_pSputRender_CleanBuffer->format;
  pVVar6 = &VStack_4c;
  for (iVar3 = 0x13; iVar3 != 0; iVar3 = iVar3 + -1) {
    pVVar6->nWidth = pVVar4->nWidth;
    pVVar4 = (VBufferFormat *)&pVVar4->nHeight;
    pVVar6 = (VBufferFormat *)&pVVar6->nHeight;
  }
  VStack_4c.nHeight = h;
  VStack_4c.nWidth = w;
  pVVar2 = stdDisplay_VBufferNew(&VStack_4c,0,0,0);
  pCVar1->pClean = pVVar2;
  Surface_Blit(pVVar2,g_pSputRender_CleanBuffer,0,0,srcRect,0);
  pVVar4 = &g_pSputRender_CleanZBuffer->format;
  pVVar6 = &VStack_4c;
  for (iVar3 = 0x13; iVar3 != 0; iVar3 = iVar3 + -1) {
    pVVar6->nWidth = pVVar4->nWidth;
    pVVar4 = (VBufferFormat *)&pVVar4->nHeight;
    pVVar6 = (VBufferFormat *)&pVVar6->nHeight;
  }
  VStack_4c.nWidth = w;
  VStack_4c.nHeight = h;
  pVVar2 = stdDisplay_VBufferNew(&VStack_4c,0,0,0);
  pCVar1->pCleanZ = pVVar2;
  Surface_Blit(pVVar2,g_pSputRender_CleanZBuffer,0,0,srcRect,0);
  pCVar1->pNext = g_pCacheRectList;
  g_pCacheRectList = pCVar1;
  return pCVar1;
}
#undef VStack_4c


/* ---- 0x00486c50  sputRender_RestoreCacheRect ---- */
/* Lua RestoreCacheRect: copies the most recent cached rectangle back and invalidates it Original
   name sputRender_RestoreCacheRect (the remaster's GrimFandango (Linux): aligned call in
   sputLua_RestoreCacheRect); was CacheRect_Restore. */

void __cdecl sputRender_RestoreCacheRect(int unused)

{
  int *piVar1;
  int *rect;
  CacheRect *pCVar2;
  
  pCVar2 = g_pCacheRectList;
  piVar1 = &g_pCacheRectList->nY;
  rect = &g_pCacheRectList->nX;
  Surface_Blit(g_pSputRender_CleanBuffer,g_pCacheRectList->pClean,g_pCacheRectList->nX,
               g_pCacheRectList->nY,(int *)0x0,0);
  Surface_Blit(g_pSputRender_CleanZBuffer,pCVar2->pCleanZ,*rect,*piVar1,(int *)0x0,0);
  MarkDirtyRect(rect,1);
  return;
}

/* ---- 0x00486cb0  CacheRect_FreeAll ---- */
void __cdecl CacheRect_FreeAll(void)

{
  CacheRect *pCVar1;
  
  pCVar1 = g_pCacheRectList;
  while (pCVar1 != (CacheRect *)0x0) {
    g_pCacheRectList = pCVar1->pNext;
    if (pCVar1->pClean != (VBuffer *)0x0) {
      stdDisplay_VBufferFree(pCVar1->pClean);
    }
    if (pCVar1->pCleanZ != (VBuffer *)0x0) {
      stdDisplay_VBufferFree(pCVar1->pCleanZ);
    }
    (*g_pSputRendHS->pFree)(pCVar1);
    pCVar1 = g_pCacheRectList;
  }
  g_pCacheRectList = pCVar1;
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_g_pCacheRectList[4] __asm__("_g_pCacheRectList");
/* 0x008c97f4, 4 bytes */ /* loose */ unsigned char grim_def_g_pCacheRectList[4] __asm__("_g_pCacheRectList") = {0};
