/* GRIMFANDANGO.EXE :: rdroid.c
 * functions 0x00404180 .. 0x00404b80 (16 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00404180  rdStartup ---- */
/* RDroid library startup: stores the service table and builds the reciprocal/fixed-point tables
   Original name rdStartup (the remaster's GrimFandango (Linux): called from Main_Startup with hs on
   both sides, same body (stores rdroid_pHS, once flag bRDroidStartup)); was rdroid_Startup. */

int __cdecl rdStartup(GrimServices *svc)

{
  if (g_dwRDroidStartup != 0) {
    return 1;
  }
  g_pRdroid_HS = svc;
  Plat_ReturnTrue();
  Plat_ReturnTrue();
  rdRaster_Startup();
  g_dwRDroidStartup = 1;
  return 1;
}

/* ---- 0x004041c0  rdShutdown ---- */
/* Original name rdShutdown (the remaster's GrimFandango (Linux): same body (clears bRDroidStartup);
   the call after rdClose in Main_Shutdown in both builds); was rdroid_Shutdown. */

void __cdecl rdShutdown(void)

{
  if (g_dwRDroidStartup == 1) {
    g_dwRDroidStartup = 0;
  }
  return;
}

/* ---- 0x004041e0  rdOpen ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Sets the default render state (geometry/lighting modes) and initialises the rasterizer caches
   Original name rdOpen (the remaster's GrimFandango (Linux): the only unpaired user of
   rdroid_curColorEffects on both sides, same initialisation sequence); was rdroid_Open. */

int __cdecl rdOpen(int flags)

{
  if (g_dwRDroidOpen == 0) {
    g_nRdroid_curGeometryMode = 5;
    g_nRdroid_curLightingMode = 5;
    g_nRdroid_curTextureMode = 3;
    g_dwRdroid_curRenderOptions = 1;
    g_nRdroid_curSortingMethod = 0;
    g_nRdroid_curOcclusionMethod = 0;
    _g_bRdroid_curCullFlags = 1;
    g_dwRdroid_curProcFaceUserData = 0;
    stdPalEffects_ResetEffect(&g_dwRdroid_curColorEffects);
    g_dwRdroid_curVertexColorMode = 0;
    g_dwRdroid_frameTrue = 0;
    rdClearPreStatistics();
    g_dwRDroidOpen = 1;
    g_nRdroid_curAcceleration = flags;
  }
  return 1;
}

/* ---- 0x00404270  rdClose ---- */
/* Original name rdClose (the remaster's GrimFandango (Linux): the only unpaired user of bRDroidOpen
   besides rdOpen, same body (clears the open flag)); was rdroid_Close. */

void __cdecl rdClose(void)

{
  if (g_dwRDroidOpen != 0) {
    g_dwRDroidOpen = 0;
  }
  return;
}

/* ---- 0x00404290  rdSetRenderOptions ---- */
/* Sets g_dwRdroid_curRenderOptions (bit 1: apply camera fog/attenuation at +0x54) Original name
   rdSetRenderOptions (the remaster's GrimFandango (Linux): same body (rdroid_curRenderOptions =
   flags)); was rdroid_SetRenderFlags. */

void __cdecl rdSetRenderOptions(uint param_1)

{
  g_dwRdroid_curRenderOptions = param_1;
  return;
}

/* ---- 0x004042a0  rdSetGeometryMode ---- */
/* Upper limit for the per-mesh geometry mode (0 none .. 4 textured) Original name rdSetGeometryMode
   (the remaster's GrimFandango (Linux): same body (rdroid_curGeometryMode = mode)); was
   rdroid_SetGeometryMode. */

void __cdecl rdSetGeometryMode(int param_1)

{
  g_nRdroid_curGeometryMode = param_1;
  return;
}

/* ---- 0x004042b0  rdSetLightingMode ---- */
/* Original name rdSetLightingMode (the remaster's GrimFandango (Linux): same body
   (rdroid_curLightingMode = mode); between rdSetGeometryMode and rdSetTextureMode in both builds);
   was rdroid_SetLightingMode. */

void __cdecl rdSetLightingMode(int param_1)

{
  g_nRdroid_curLightingMode = param_1;
  return;
}

/* ---- 0x004042c0  rdSetTextureMode ---- */
/* Original name rdSetTextureMode (the remaster's GrimFandango (Linux): same body
   (rdroid_curTextureMode = mode); after rdSetLightingMode in both builds); was
   rdroid_SetTextureMode. */

void __cdecl rdSetTextureMode(int param_1)

{
  g_nRdroid_curTextureMode = param_1;
  return;
}

/* ---- 0x004042d0  rdSetSortingMethod ---- */
/* 2 = qsort the cached mesh list by depth before drawing Original name rdSetSortingMethod (the
   remaster's GrimFandango (Linux): same body (rdroid_curSortingMethod = method)); was
   rdroid_SetSortMode. */

void __cdecl rdSetSortingMethod(int param_1)

{
  g_nRdroid_curSortingMethod = param_1;
  return;
}

/* ---- 0x004042e0  rdSetOcclusionMethod ---- */
/* 0 selects the plain software path in rdCache_Flush Original name rdSetOcclusionMethod (the
   remaster's GrimFandango (Linux): same body (rdroid_curOcclusionMethod = method); after
   rdSetSortingMethod in both builds); was rdroid_SetOcclusionMode. */

void __cdecl rdSetOcclusionMethod(int param_1)

{
  g_nRdroid_curOcclusionMethod = param_1;
  return;
}

/* ---- 0x004042f0  rdSetZBufferMethod ---- */
/* 2 selects the z-buffered software path (rdCache_DrawMeshZ) Original name rdSetZBufferMethod (the
   remaster's GrimFandango (Linux): same body (rdroid_curZBufferMethod = method); after
   rdSetOcclusionMethod in both builds); was rdroid_SetZBufferMode. */

void __cdecl rdSetZBufferMethod(int param_1)

{
  g_nRdroid_curZBufferMethod = param_1;
  return;
}

/* ---- 0x00404300  rdAdvanceFrame ---- */
/* Resets the caches, bumps the frame counter, clears the canvas and begins the 3D scene Original
   name rdAdvanceFrame (the remaster's GrimFandango (Linux): same body (counter resets,
   rdroid_frameTrue++, rdCamera_AdvanceFrame, rdCache_AdvanceFrame), called from sputRender_Update
   on both sides); was rdroid_BeginFrame. */

void rdAdvanceFrame(void)

{
  rdClearPreStatistics();
  g_dwRdroid_frameTrue = g_dwRdroid_frameTrue + 1;
  rdCamera_AdvanceFrame();
  rdCache_AdvanceFrame();
  return;
}

/* ---- 0x00404320  rdFinishFrame ---- */
/* Flushes the mesh cache, ends the 3D scene and dumps the memory log Original name rdFinishFrame
   (the remaster's GrimFandango (Linux): same body (rdCache_Flush, rdCache_FinishFrame, the frame
   counters' clear); called by sputRender_Dim in both builds); was rdroid_EndFrame. */

void __cdecl rdFinishFrame(void)

{
  rdCache_Flush();
  rdCache_FinishFrame();
  Mem_DumpLog();
  return;
}

/* ---- 0x00404330  rdClearPreStatistics ---- */
/* Original name rdClearPreStatistics (the remaster's GrimFandango (Linux): the same three counter
   resets (rdCache_ClearFrameCounters, rdActive_ClearFrameCounters, rdModel3_ClearFrameCounters),
   called from rdOpen and rdAdvanceFrame); was rdroid_InitCaches. */

void rdClearPreStatistics(void)

{
  rdCache_ClearFrameCounters();
  rdActive_ClearFrameCounters();
  rdModel3_ClearFrameCounters();
  return;
}

/* ---- 0x00404350  rdroid_SetColormap ---- */
uint __cdecl rdroid_SetColormap(uint param_1)

{
  if (g_dwRdColormap_pIdentityMap != param_1) {
    g_dwRdColormap_pIdentityMap = param_1;
  }
  if (g_dwRdColormap_pCurMap == 0) {
    rdColormap_SetCurrent(param_1);
  }
  return 1;
}

/* ---- 0x00404b80  rdRaster_Startup ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_4 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Fills the 1/n float table and its fixed-point twin used by the span rasterizer Original name
   rdRaster_Startup (the remaster's GrimFandango (Linux): the last call of rdStartup, same body
   (rdRaster_aOneOverNFlex / rdRaster_aOneOverNFixed tables from 0x7f7fc99e / 0x7fffffff)); was
   rdroid_BuildMathTables. */

void __cdecl rdRaster_Startup(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 unaff_ESI;
  int iVar2;
  longlong lVar3;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  g_dwRdRaster_aOneOverNFlex = 0x7f7fc99e;
  _g_aRdRaster_OneOverNFixed = 0x7fffffff;
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
         *(float *)((int)&g_dwRdRaster_aOneOverNFlex + iVar2) * _DAT_004ddb30;
    iVar2 = iVar1;
  } while (iVar1 < 0x40);
  return;
}
#undef local_4

#endif

