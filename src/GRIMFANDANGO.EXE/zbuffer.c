/* GRIMFANDANGO.EXE :: zbuffer.c
 * functions 0x004a4920 .. 0x004a4990 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a4920  sputRoom_LoadZBuffer ---- */
/* Loads a ZBUF resource: wrapper of ZBuffer_LoadFile. Original name sputRoom_LoadZBuffer (the
   remaster's GrimFandango (Linux): the load call of the 'ZBUF' resource handler
   (sputResource_ZBufferHandler); the remaster inlined ZBuffer_LoadFile); was ZBuffer_Load. */

uint __cdecl sputRoom_LoadZBuffer(uint param_1)

{
  uint uVar1;
  
  uVar1 = ZBuffer_LoadFile((char *)param_1);
  return uVar1;
}

/* ---- 0x004a4930  ZBuffer_LoadFile ---- */
/* Loads a z-buffer .zbm through stdLoadImageData and detaches the pixel plane (bitmap+0x78) from
   the bitmap, returning it. */

uint __cdecl ZBuffer_LoadFile(char *param_1)

{
  uint uVar1;
  void *bitmap;
  
  bitmap = stdLoadImageData(param_1,0,0);
  if (bitmap == (void *)0x0) {
    return 0;
  }
  uVar1 = **(uint **)((int)bitmap + 0x78);
  (*g_pSputRoomHS->pFree)(*(uint **)((int)bitmap + 0x78));
  *(undefined4 *)((int)bitmap + 0x78) = 0;
  *(undefined4 *)((int)bitmap + 100) = 0;
  stdBitmap_Free(bitmap);
  return uVar1;
}

/* ---- 0x004a4980  sputRoom_FreeZBuffer ---- */
/* Frees a ZBUF resource (wrapper of ZBuffer_FreeData). Original name sputRoom_FreeZBuffer (the
   remaster's GrimFandango (Linux): the free call of the 'ZBUF' resource handler
   (sputResource_ZBufferHandler) on both sides); was ZBuffer_Free. */

void __cdecl sputRoom_FreeZBuffer(uint param_1)

{
  ZBuffer_FreeData((void *)param_1);
  return;
}

/* ---- 0x004a4990  ZBuffer_FreeData ---- */
/* stdDisplay_VBufferFree of the z-buffer surface. */

void __cdecl ZBuffer_FreeData(void *param_1)

{
  stdDisplay_VBufferFree(param_1);
  return;
}
