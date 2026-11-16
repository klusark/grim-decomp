/* GRIMFANDANGO.EXE :: drawlist.c
 * functions 0x00486250 .. 0x004862b0 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00486250  DrawList_Reset ---- */
void __cdecl DrawList_Reset(void)

{
  byte *pbVar1;
  void **ppvVar2;
  
  g_dwTotDrawItems = 0;
  ppvVar2 = g_dwDrawItems;
  pbVar1 = g_abDrawItemPool;
  do {
    *ppvVar2 = pbVar1;
    pbVar1 = pbVar1 + 0xc;
    ppvVar2 = ppvVar2 + 1;
  } while ((int)pbVar1 < ((unsigned)(uintptr_t)&DAT_008a92a8));
  return;
}

/* ---- 0x00486280  DrawList_Alloc ---- */
/* Returns the next of 128 draw-list entries or NULL */

undefined * __cdecl DrawList_Alloc(void)

{
  uint uVar1;
  
  uVar1 = g_dwTotDrawItems;
  if ((int)g_dwTotDrawItems < 0x80) {
    g_dwTotDrawItems = g_dwTotDrawItems + 1;
    return g_abDrawItemPool + uVar1 * 0xc;
  }
  return (undefined *)0x0;
}

/* ---- 0x004862b0  Render_CompareDrawDepth ---- */
/* qsort comparator of Render_BuildActorDrawList: 1 when the depth (+4) of the first entry is less
   than the second's, else 0; was FUN_004862b0. */

uint __cdecl Render_CompareDrawDepth(int *a,int *b)

{
  if (*(float *)(*a + 4) < *(float *)(*b + 4)) {
    return 1;
  }
  return 0;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_g_abDrawItemPool[1536] __asm__("_g_abDrawItemPool");
/* 0x008a8ca8, 1536 bytes */ GRIM_DATA("008a8ca8") unsigned char grim_def_g_abDrawItemPool[1536] __asm__("_g_abDrawItemPool") = {0};
