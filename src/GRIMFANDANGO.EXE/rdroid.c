/* GRIMFANDANGO.EXE :: rdroid.c
 * functions 0x00404180 .. 0x00404b80 (16 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00404180  rdroid_Startup ---- */
/* RDroid library startup: stores the service table and builds the reciprocal/fixed-point tables */

int __cdecl rdroid_Startup(GrimServices *svc)

{
  if (UINT_004f5eb8 != 0) {
    return 1;
  }
  g_pRdroid_HS = svc;
  Plat_ReturnTrue();
  Plat_ReturnTrue();
  rdroid_BuildMathTables();
  UINT_004f5eb8 = 1;
  return 1;
}

/* ---- 0x004041c0  rdroid_Shutdown ---- */
void rdroid_Shutdown(void)

{
  if (UINT_004f5eb8 == 1) {
    UINT_004f5eb8 = 0;
  }
  return;
}

/* ---- 0x004041e0  rdroid_Open ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Sets the default render state (geometry/lighting modes) and initialises the rasterizer caches */

int __cdecl rdroid_Open(int flags)

{
  if (UINT_004f5ebc == 0) {
    g_nRdroidGeometryMode = 5;
    g_nRdroid_curLightingMode = 5;
    g_nRdroid_curTextureMode = 3;
    g_dwRdroid_curRenderOptions = 1;
    g_nRdroid_curSortingMethod = 0;
    g_nRdroid_curOcclusionMethod = 0;
    _g_bRdroid_curCullFlags = 1;
    UINT_00900054 = 0;
    stdBitmap_InitHeader(&UINT_00900020);
    UINT_0090004c = 0;
    UINT_004f5eb4 = 0;
    rdroid_InitCaches();
    UINT_004f5ebc = 1;
    g_nRdroid_curAcceleration = flags;
  }
  return 1;
}

/* ---- 0x00404270  rdroid_Close ---- */
void rdroid_Close(void)

{
  if (UINT_004f5ebc != 0) {
    UINT_004f5ebc = 0;
  }
  return;
}

/* ---- 0x00404290  rdroid_SetRenderFlags ---- */
/* Sets g_dwRdroid_curRenderOptions (bit 1: apply camera fog/attenuation at +0x54) */

void rdroid_SetRenderFlags(uint param_1)

{
  g_dwRdroid_curRenderOptions = param_1;
  return;
}

/* ---- 0x004042a0  rdroid_SetGeometryMode ---- */
/* Upper limit for the per-mesh geometry mode (0 none .. 4 textured) */

void rdroid_SetGeometryMode(int param_1)

{
  g_nRdroidGeometryMode = param_1;
  return;
}

/* ---- 0x004042b0  rdroid_SetLightingMode ---- */
void rdroid_SetLightingMode(int param_1)

{
  g_nRdroid_curLightingMode = param_1;
  return;
}

/* ---- 0x004042c0  rdroid_SetTextureMode ---- */
void rdroid_SetTextureMode(int param_1)

{
  g_nRdroid_curTextureMode = param_1;
  return;
}

/* ---- 0x004042d0  rdroid_SetSortMode ---- */
/* 2 = qsort the cached mesh list by depth before drawing */

void rdroid_SetSortMode(int param_1)

{
  g_nRdroid_curSortingMethod = param_1;
  return;
}

/* ---- 0x004042e0  rdroid_SetOcclusionMode ---- */
/* 0 selects the plain software path in rdCache_Flush */

void rdroid_SetOcclusionMode(int param_1)

{
  g_nRdroid_curOcclusionMethod = param_1;
  return;
}

/* ---- 0x004042f0  rdroid_SetZBufferMode ---- */
/* 2 selects the z-buffered software path (rdCache_DrawMeshZ) */

void rdroid_SetZBufferMode(int param_1)

{
  g_nRdroid_curZBufferMethod = param_1;
  return;
}

/* ---- 0x00404300  rdroid_BeginFrame ---- */
/* Resets the caches, bumps the frame counter, clears the canvas and begins the 3D scene */

void rdroid_BeginFrame(void)

{
  rdroid_InitCaches();
  UINT_004f5eb4 = UINT_004f5eb4 + 1;
  rdCamera_ClearCanvas();
  rdCache_BeginScene3D();
  return;
}

/* ---- 0x00404320  rdroid_EndFrame ---- */
/* Flushes the mesh cache, ends the 3D scene and dumps the memory log */

void rdroid_EndFrame(void)

{
  rdCache_Flush();
  rdCache_EndScene3D();
  Mem_DumpLog();
  return;
}

/* ---- 0x00404330  rdroid_InitCaches ---- */
void rdroid_InitCaches(void)

{
  rdCache_ClearStats();
  rdCanvas_ResetPolyCount();
  rdCamera_ResetStats();
  return;
}

/* ---- 0x00404350  rdroid_SetColormap ---- */
undefined4 rdroid_SetColormap(uint param_1)

{
  if (UINT_004f5ec0 != param_1) {
    UINT_004f5ec0 = param_1;
  }
  if (g_dwRdColormap_pCurMap == 0) {
    rdColormap_SetCurrent(param_1);
  }
  return 1;
}

/* ---- 0x00404b80  rdroid_BuildMathTables ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_4 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Fills the 1/n float table and its fixed-point twin used by the span rasterizer */

void rdroid_BuildMathTables(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 unaff_ESI;
  int iVar2;
  longlong lVar3;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  UINT_008fe000 = 0x7f7fc99e;
  _DAT_008fbfc0 = 0x7fffffff;
  local_4 = 1;
  iVar2 = 0;
  do {
    *(float *)((int)&UINT_008fe004 + iVar2) = 1.0 / (float)(int)local_4;
    lVar3 = _ftol((double)CONCAT44(local_4,unaff_ESI));
    *(int *)((int)&UINT_008fbfc4 + iVar2) = (int)lVar3;
    iVar2 = iVar2 + 4;
    local_4 = local_4 + 1;
  } while (iVar2 < 0x1ffc);
  iVar2 = 0;
  do {
    iVar1 = iVar2 + 4;
    *(float *)((int)&UINT_008fdfc0 + iVar2) =
         *(float *)((int)&UINT_008fe000 + iVar2) * _DAT_004ddb30;
    iVar2 = iVar1;
  } while (iVar1 < 0x40);
  return;
}
#undef local_4

#endif

