/* GRIMFANDANGO.EXE :: render.c
 * functions 0x004839f0 .. 0x0048f920 (46 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004839f0  Render_GetBackBuffer ---- */
/* Returns the back buffer surface g_dwStdDisplay_backBuffer */

uint * __cdecl Render_GetBackBuffer(void)

{
  return &g_dwStdDisplay_backBuffer;
}

/* ---- 0x00483a00  sputRender_DrawDebuggingToggle ---- */
/* Flips debug flag 1 and, when turning it off, invalidates the whole canvas on every buffer
   Original name sputRender_DrawDebuggingToggle (the remaster's GrimFandango (Linux): same body
   (toggles bit 0 of debugFlags; when off, marks the camera's viewport dirty); called by
   sputRender_ControlHandler in both builds); was Render_ToggleDebugOverlay. */

void __cdecl sputRender_DrawDebuggingToggle(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int bufferIdx;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if ((g_dwDebugFlags & 1) == 0) {
    g_dwDebugFlags = g_dwDebugFlags | 1;
  }
  else {
    g_dwDebugFlags = g_dwDebugFlags & 0xfffffffe;
  }
  if ((g_dwDebugFlags & 1) == 0) {
    local_10 = *(uint *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x18);
    local_c = *(uint *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x1c);
    local_8 = (*(int *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x20) -
              *(int *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x18)) + 1;
    local_4 = (*(int *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x24) -
              *(int *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x1c)) + 1;
    bufferIdx = 0;
    if (0 < g_nNumPages) {
      do {
        DirtyRect_Add((int *)&local_10,1,bufferIdx);
        bufferIdx = bufferIdx + 1;
      } while (bufferIdx < g_nNumPages);
    }
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00483a80  sputRender_SetPaletteCallback ---- */
/* Original name sputRender_SetPaletteCallback (the remaster's GrimFandango (Linux): the call of
   grimlib_SetPaletteCallback, same body (stores sputRender_pSetPaletteFunc)); was
   Render_SetUserCallback. */

void __cdecl sputRender_SetPaletteCallback(uint param_1)

{
  g_dwSputRender_pSetPaletteFunc = param_1;
  return;
}

/* ---- 0x00483a90  sputRender_SetPageFlipCallback ---- */
/* Installs the function Render_Present calls to show the back buffer Original name
   sputRender_SetPageFlipCallback (the remaster's GrimFandango (Linux): the only unpaired writer of
   sputRender_pPageFlipFunc, same body; grimlib_SetPageFlipCallback jumps to it); was
   Render_SetFlipCallback. */

void __cdecl sputRender_SetPageFlipCallback(void *param_1)

{
  g_pSputRender_PageFlipFunc = param_1;
  return;
}

/* ---- 0x00483da0  sputRender_Save ---- */
/* Original name sputRender_Save (the remaster's GrimFandango (Linux): aligned call in
   sputRender_Initialize); was Render_SaveState. */

int __cdecl sputRender_Save(void *writeFn)

{
  (*(code *)writeFn)(&g_dwIrisStart,4);
  (*(code *)writeFn)(&g_flIrisDuration,4);
  (*(code *)writeFn)(&g_nIrisX,4);
  (*(code *)writeFn)(&g_nIrisY,4);
  (*(code *)writeFn)(&g_flSputRender_GammaCorrection,4);
  (*(code *)writeFn)(&g_dwRenderFlags,4);
  (*(code *)writeFn)(&g_nDoTheFlip,4);
  (*(code *)writeFn)(&g_nCamActorIndex,4);
  (*(code *)writeFn)(&g_dwMovieJustFinished,4);
  return 0;
}

/* ---- 0x00483e20  sputRender_Restore ---- */
/* Original name sputRender_Restore (the remaster's GrimFandango (Linux): aligned call in
   sputRender_Initialize); was Render_RestoreState. */

int __cdecl sputRender_Restore(void *readFn)

{
  (*(code *)readFn)(&g_dwIrisStart,4);
  (*(code *)readFn)(&g_flIrisDuration,4);
  (*(code *)readFn)(&g_nIrisX,4);
  (*(code *)readFn)(&g_nIrisY,4);
  (*(code *)readFn)(&g_flSputRender_GammaCorrection,4);
  (*(code *)readFn)(&g_dwRenderFlags,4);
  (*(code *)readFn)(&g_nDoTheFlip,4);
  (*(code *)readFn)(&g_nCamActorIndex,4);
  (*(code *)readFn)(&g_dwMovieJustFinished,4);
  return 0;
}

/* ---- 0x00483ea0  sputRender_Using3DHardware ---- */
/* Original name sputRender_Using3DHardware (the remaster's GrimFandango (Linux): same body
   (sputRender_b3DAcceleration = flag)); was Render_SetZBufferEnabled. */

void __cdecl sputRender_Using3DHardware(int param_1)

{
  g_nSputRender_b3DAcceleration = param_1;
  return;
}

/* ---- 0x00483eb0  sputRender_PageCountIs ---- */
/* Original name sputRender_PageCountIs (the remaster's GrimFandango (Linux): the only unmatched
   callee of Engine_OpenRenderer; 1 matched neighbours agree, 0 disagree); was
   Render_SetBufferCount. */

void __cdecl sputRender_PageCountIs(int n)

{
  g_nNumPages = 1;
  if (0 < n) {
    g_nNumPages = n;
  }
  return;
}

/* ---- 0x00483ed0  sputRender_MarkDirtyRect ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name sputRender_MarkDirtyRect (the remaster's GrimFandango (Linux): same body (the
   rectangle into the static trect, x rounded down and the width up to multiples of 4, MarkDirtyRect
   for the last page)); was Render_InvalidateRectLastBuffer. */

void __cdecl sputRender_MarkDirtyRect(int *rect,int flag)

{
  int iVar1;
  uint uVar2;
  
  _g_aSputRender_MarkDirtyRect_trect = *rect;
  _DAT_008a92bc = rect[1];
  _DAT_008a92c0 = rect[2];
  _DAT_008a92c4 = rect[3];
  if ((0 < (int)_DAT_008a92c0) && (0 < _DAT_008a92c4)) {
    uVar2 = (int)_g_aSputRender_MarkDirtyRect_trect >> 0x1f;
    iVar1 = ((_g_aSputRender_MarkDirtyRect_trect ^ uVar2) - uVar2 & 3 ^ uVar2) - uVar2;
    _DAT_008a92c0 = _DAT_008a92c0 + iVar1;
    _g_aSputRender_MarkDirtyRect_trect = _g_aSputRender_MarkDirtyRect_trect - iVar1;
    uVar2 = (int)_DAT_008a92c0 >> 0x1f;
    iVar1 = ((_DAT_008a92c0 ^ uVar2) - uVar2 & 3 ^ uVar2) - uVar2;
    if (iVar1 != 0) {
      _DAT_008a92c0 = _DAT_008a92c0 + (4 - iVar1);
    }
    DirtyRect_Add((int *)&g_aSputRender_MarkDirtyRect_trect,flag,g_nNumPages + -1);
  }
  return;
}

/* ---- 0x00483f60  MarkDirtyRect ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Aligns x/width to 4 pixels and marks the rectangle dirty on every buffer Original name
   MarkDirtyRect (the remaster's GrimFandango (Linux): the only unmatched callee of Lua_IrisClear; 2
   matched neighbours agree, 0 disagree); was Render_InvalidateRect. */

void __cdecl MarkDirtyRect(int *rect,int flag)

{
  int iVar1;
  uint uVar2;
  
  _DAT_008a92a8 = *rect;
  _DAT_008a92ac = rect[1];
  _DAT_008a92b0 = rect[2];
  _DAT_008a92b4 = rect[3];
  if ((0 < (int)_DAT_008a92b0) && (0 < _DAT_008a92b4)) {
    uVar2 = (int)_DAT_008a92a8 >> 0x1f;
    iVar1 = ((_DAT_008a92a8 ^ uVar2) - uVar2 & 3 ^ uVar2) - uVar2;
    _DAT_008a92b0 = _DAT_008a92b0 + iVar1;
    _DAT_008a92a8 = _DAT_008a92a8 - iVar1;
    uVar2 = (int)_DAT_008a92b0 >> 0x1f;
    iVar1 = ((_DAT_008a92b0 ^ uVar2) - uVar2 & 3 ^ uVar2) - uVar2;
    if (iVar1 != 0) {
      _DAT_008a92b0 = _DAT_008a92b0 + (4 - iVar1);
    }
    iVar1 = 0;
    if (0 < g_nNumPages) {
      do {
        DirtyRect_Add((int *)&DAT_008a92a8,flag,iVar1);
        iVar1 = iVar1 + 1;
      } while (iVar1 < g_nNumPages);
    }
  }
  return;
}

/* ---- 0x00484030  sputRender_SetDisplay ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Creates the rdCanvas, the background, temp and z-buffer surfaces, programs the pixel format into
   RDroid and draws the current set Original name sputRender_SetDisplay (the remaster's GrimFandango
   (Linux): the only unmatched caller of rdCamera_SetAmbientLight; the only unmatched caller of
   rdCanvas_New; 3 matched neighbours agree, 1 disagree); was Render_Open. */

uint __cdecl
sputRender_SetDisplay
          (uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,int param_7
          )

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  bool bVar5;
  #define local_4c (*(undefined4 (*)[19])(_frame + (0x60 - 0x4c)))
  
  sputRender_Close();
  g_pSputRender_Canvas = rdCanvas_New(1,param_1,param_2,param_3,param_4,param_5,param_6,0);
  UINT_008c97a4 = param_2;
  UINT_008c97a0 = param_1;
  puVar3 = (undefined4 *)(param_1 + 0xc);
  puVar4 = local_4c;
  for (iVar2 = 0x13; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  g_pSputRender_DecompressionBuffer = stdDisplay_VBufferNew(local_4c,0,0,0);
  bVar5 = *(int *)(param_1 + 8) != 0;
  g_pSputRender_CleanBuffer = stdDisplay_VBufferNew(local_4c,(uint)bVar5,(uint)bVar5,0);
  if ((g_nSputRender_b3DAcceleration == 0) || (UINT_004e806c != 0)) {
    iVar2 = 0;
  }
  else {
    iVar2 = 1;
  }
  g_pSputRender_CleanZBuffer = stdDisplay_VBufferNew(local_4c,iVar2,iVar2,0);
  if ((g_pSputRender_CleanBuffer != (void *)0x0) && (g_pSputRender_CleanZBuffer != (void *)0x0)) {
    UINT_008a94b8 = UINT_0090563c;
    _DAT_008a94c4 = UINT_00905604 >> 3;
    UINT_008a94c0 = UINT_009055f0;
    UINT_008a94bc = *(uint *)(UINT_008c97a0 + 0xc);
    _DAT_008a94cc = UINT_009055f8;
    *(uint *)(param_7 + 0xc) = *(uint *)(param_7 + 0xc) | 2;
    Render_SetPixelFormat((uint *)param_7);
    pvVar1 = sputRoom_GetCurrentRoom();
    if (pvVar1 != (void *)0x0) {
      rdCamera_SetAmbientLight
                (*(void **)(*(int *)((int)pvVar1 + 0xac) + 0x48 + *(int *)((int)pvVar1 + 0xb4) * 300
                           ),g_flAmbientLight);
    }
    UINT_008c9780 = (uint)&DAT_00905600;
    Render_InitColorConstants(((unsigned)(uintptr_t)&g_dwRdColormap_colorInfo));
    _DAT_008c9790 = 1;
    pvVar1 = sputRoom_GetCurrentRoom();
    if (pvVar1 != (void *)0x0) {
      pvVar1 = sputRoom_GetCurrentRoom();
      iVar2 = *(int *)((int)pvVar1 + 0xb4);
      pvVar1 = sputRoom_GetCurrentRoom();
      sputRender_UseSetup(pvVar1,iVar2);
    }
    sputRender_ForceRefresh();
    return 1;
  }
  return 0;
}
#undef local_4c


/* ---- 0x004841f0  sputRender_Close ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name sputRender_Close (the remaster's GrimFandango (Linux): the only unmatched caller of
   rdCanvas_Free; 1 matched neighbours agree, 1 disagree); was Render_Close. */

void __cdecl sputRender_Close(void)

{
  if (g_pSputRender_Canvas != (void *)0x0) {
    rdCanvas_Free((int)g_pSputRender_Canvas);
    g_pSputRender_Canvas = (void *)0x0;
  }
  if (g_pSputRender_CleanBuffer != (void *)0x0) {
    stdDisplay_VBufferFree(g_pSputRender_CleanBuffer);
    g_pSputRender_CleanBuffer = (void *)0x0;
  }
  if (g_pSputRender_CleanZBuffer != (void *)0x0) {
    stdDisplay_VBufferFree(g_pSputRender_CleanZBuffer);
    g_pSputRender_CleanZBuffer = (void *)0x0;
  }
  if (g_pSputRender_DecompressionBuffer != (void *)0x0) {
    stdDisplay_VBufferFree(g_pSputRender_DecompressionBuffer);
    g_pSputRender_DecompressionBuffer = (void *)0x0;
  }
  _DAT_008c9790 = 0;
  return;
}

/* ---- 0x004849a0  sputRender_PageFlip ---- */
/* Calls the flip callback unless the frame was flagged to skip presentation Original name
   sputRender_PageFlip (the remaster's GrimFandango (Linux): the only unpaired user of
   MovieJustFinished on both sides, same body (flip callback, clears MovieJustFinished)); was
   Render_Present. */

void __cdecl sputRender_PageFlip(void)

{
  if ((g_nDoTheFlip != 0) && (g_dwMovieJustFinished == 0)) {
    (*(code *)g_pSputRender_PageFlipFunc)();
  }
  g_dwMovieJustFinished = 0;
  return;
}

/* ---- 0x004849d0  Render_SetPixelFormat ---- */
/* Copies the 7-dword pixel format and pushes each component shift/mask into RDroid */

void __cdecl Render_SetPixelFormat(uint *param_1)

{
  int iVar1;
  uint *puVar2;
  
  puVar2 = &g_dwRenderVars;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  rdSetGeometryMode(g_dwRenderVars);
  rdSetLightingMode(UINT_008a9514);
  rdSetTextureMode(UINT_008a9518);
  rdSetRenderOptions(UINT_008a951c);
  rdSetSortingMethod(UINT_008a9520);
  rdSetOcclusionMethod(UINT_008a9524);
  rdSetZBufferMethod(UINT_008a9528);
  return;
}

/* ---- 0x00484a50  sputRender_ControlHandler ---- */
/* Original name sputRender_ControlHandler (the remaster's GrimFandango (Linux): aligned call in
   sputRender_Initialize); was FUN_00484a50. */

uint __cdecl sputRender_ControlHandler(void)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (g_nGrimlib_bDebugKeys == 0) {
    return 0;
  }
  iVar1 = stdControl_ReadKey(0x1d,(int *)0x0,(int *)0x0);
  if (iVar1 != 0) {
    iVar1 = stdControl_ReadKey(0x20,(int *)0x0,(int *)0x0);
    if (iVar1 != 0) {
      uVar2 = 1;
      iVar1 = stdControl_ReadKey(0x39,(int *)0x0,(int *)0x0);
      if (iVar1 == 0) {
        g_dwSputRender_ControlHandler_bLastSpace = 0;
      }
      else if (g_dwSputRender_ControlHandler_bLastSpace == 0) {
        sputRender_DrawDebuggingToggle();
        g_dwSputRender_ControlHandler_bLastSpace = 1;
      }
      if ((g_dwDebugFlags & 1) != 0) {
        iVar1 = stdControl_ReadKey(0x30,(int *)0x0,(int *)0x0);
        if (iVar1 == 0) {
          g_dwSputRender_ControlHandler_bLastB = 0;
        }
        else if (g_dwSputRender_ControlHandler_bLastB == 0) {
          if ((g_dwDebugFlags & 8) == 0) {
            g_dwSputRender_ControlHandler_bLastB = 1;
            g_dwDebugFlags = g_dwDebugFlags | 8;
          }
          else {
            g_dwSputRender_ControlHandler_bLastB = 1;
            g_dwDebugFlags = g_dwDebugFlags & 0xfffffff7;
          }
        }
        iVar1 = stdControl_ReadKey(0x26,(int *)0x0,(int *)0x0);
        if (iVar1 == 0) {
          g_dwSputRender_ControlHandler_bLastL = 0;
        }
        else if (g_dwSputRender_ControlHandler_bLastL == 0) {
          if ((g_dwDebugFlags & 2) == 0) {
            g_dwSputRender_ControlHandler_bLastL = 1;
            g_dwDebugFlags = g_dwDebugFlags | 2;
          }
          else {
            g_dwSputRender_ControlHandler_bLastL = 1;
            g_dwDebugFlags = g_dwDebugFlags & 0xfffffffd;
          }
        }
        iVar1 = stdControl_ReadKey(0x2e,(int *)0x0,(int *)0x0);
        if (iVar1 == 0) {
          g_dwSputRender_ControlHandler_bLastC = 0;
        }
        else if (g_dwSputRender_ControlHandler_bLastC == 0) {
          if ((g_dwDebugFlags & 4) == 0) {
            g_dwSputRender_ControlHandler_bLastC = 1;
            g_dwDebugFlags = g_dwDebugFlags | 4;
          }
          else {
            g_dwSputRender_ControlHandler_bLastC = 1;
            g_dwDebugFlags = g_dwDebugFlags & 0xfffffffb;
          }
        }
        iVar1 = stdControl_ReadKey(0x13,(int *)0x0,(int *)0x0);
        if (iVar1 == 0) {
          g_dwSputRender_ControlHandler_bLastR = 0;
        }
        else if (g_dwSputRender_ControlHandler_bLastR == 0) {
          if ((g_dwDebugFlags & 0x10) != 0) {
            g_dwSputRender_ControlHandler_bLastR = 1;
            g_dwDebugFlags = g_dwDebugFlags & 0xffffffef;
            return 1;
          }
          g_dwSputRender_ControlHandler_bLastR = 1;
          g_dwDebugFlags = g_dwDebugFlags | 0x10;
          return 1;
        }
      }
    }
  }
  return uVar2;
}

/* ---- 0x00484c40  Render_InitColorConstants ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Builds the 16-bit colour constants (black, white, greys, red, green, blue, text colours) for the
   current pixel format */

void __cdecl Render_InitColorConstants(int param_1)

{
  Render_BuildColorTable(UINT_008c9780,g_flSputRender_GammaCorrection);
  g_abSputRender_colorMap[2] =
       (&g_wSputRender_ColorLookup)
       [(0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97c8,0,2) =
       (&g_wSputRender_ColorLookup)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0x80 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0x80 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  DAT_008c97c6 = (&g_wSputRender_ColorLookup)
                 [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
                  ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
                  (0xff >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
                  ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
                  (0xff >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
                  ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97c8,2,2) =
       (&g_wSputRender_ColorLookup)
       [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
        (0xff >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97cc,0,2) =
       (&g_wSputRender_ColorLookup)
       [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97cc,2,2) =
       (&g_wSputRender_ColorLookup)
       [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97d0,0,2) =
       (&g_wSputRender_ColorLookup)
       [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97d4,0,2) =
       (&g_wSputRender_ColorLookup)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97d4,2,2) =
       (&g_wSputRender_ColorLookup)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  _DAT_008c97d8 =
       (&g_wSputRender_ColorLookup)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0x80 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU];
  _DAT_008c97da =
       (&g_wSputRender_ColorLookup)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97d0,2,2) =
       (&g_wSputRender_ColorLookup)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0x80 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU];
  _DAT_008c97dc =
       (&g_wSputRender_ColorLookup)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0x80 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  _DAT_008c97de =
       (&g_wSputRender_ColorLookup)
       [(0xc0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0xc0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0xc0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97e0,0,2) =
       (&g_wSputRender_ColorLookup)
       [(0xdc >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0xc0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0xc0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97e0,2,2) =
       (&g_wSputRender_ColorLookup)
       [(0xf0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0xca >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0xa6 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97e4,0,2) =
       (&g_wSputRender_ColorLookup)
       [(0xb4 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0xb4 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0xb4 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97e4,2,2) =
       (&g_wSputRender_ColorLookup)
       [(100 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (100 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (100 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97e8,0,2) =
       (&g_wSputRender_ColorLookup)
       [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0xff >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97e8,2,2) =
       (&g_wSputRender_ColorLookup)
       [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0xff >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  Resource_ReloadBitmaps();
  Resource_RebuildColormaps();
  return;
}

/* ---- 0x00485bd0  Render_DrawDebugGrid ---- */
void __cdecl Render_DrawDebugGrid(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_1c (*(float *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  iVar1 = 0x14;
  local_1c = -1.0;
  do {
    local_c[0] = -1.0;
    local_c[2] = 0.0;
    local_18[0] = 1.0;
    local_18[2] = 0.0;
    local_18[1] = local_1c;
    local_c[1] = local_1c;
    rdPrimit3_DrawLine(local_c,local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                       UINT_008c97c8 & 0xffff,0xff00ff00);
    local_1c = local_1c - -0.1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  iVar1 = 0x14;
  local_1c = -1.0;
  do {
    local_c[1] = -1.0;
    local_c[2] = 0.0;
    local_18[1] = 1.0;
    local_18[2] = 0.0;
    local_18[0] = local_1c;
    local_c[0] = local_1c;
    rdPrimit3_DrawLine(local_c,local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                       UINT_008c97c8 & 0xffff,0xff00ff00);
    local_1c = local_1c - -0.1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  local_c[0] = 0.0;
  local_c[1] = 0.0;
  local_c[2] = 0.0;
  local_18[0] = 2.0;
  local_18[1] = 0.0;
  local_18[2] = 0.0;
  rdPrimit3_DrawLine(local_c,local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,(uint)DAT_008c97c6
                     ,0xffffffff);
  local_c[0] = 0.0;
  local_c[1] = 0.0;
  local_c[2] = 0.0;
  local_18[0] = 0.0;
  local_18[1] = 2.0;
  local_18[2] = 0.0;
  rdPrimit3_DrawLine(local_c,local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,(uint)DAT_008c97c6
                     ,0xffffffff);
  local_c[0] = 0.0;
  local_c[1] = 0.0;
  local_c[2] = 0.0;
  local_18[0] = 0.0;
  local_18[1] = 0.0;
  local_18[2] = 2.0;
  rdPrimit3_DrawLine(local_c,local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,(uint)DAT_008c97c6
                     ,0xffffffff);
  return;
}
#undef local_18
#undef local_1c
#undef local_c


/* ---- 0x00486100  Render_CanvasIsPaletted ---- */
int __cdecl Render_CanvasIsPaletted(void)

{
  return (uint)(**(int **)((int)g_pSputRender_Canvas + 4) == 1);
}

/* ---- 0x00486120  Render_BuildActorDrawList ---- */
/* Collects the visible actors of the current set with their view-space depth into 12-byte {kind,
   depth, index} entries and sorts them back to front */

void __cdecl Render_BuildActorDrawList(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Actor *pAVar1;
  int *piVar2;
  void *pvVar3;
  undefined *puVar4;
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float (*)[2])(_frame + (0x30 - 0x14)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  DrawList_Reset();
  pvVar3 = sputRoom_GetCurrentRoom();
  piVar2 = *(int **)(*(int *)((int)pvVar3 + 0x1abc) + 0x80);
  do {
    if (piVar2 == (int *)0x0) {
      qsort(&g_dwDrawItems,g_dwTotDrawItems,4,FUN_004862b0);
      return;
    }
    pAVar1 = g_pActors + *piVar2;
    if ((pAVar1 != (Actor *)0x0) && (pAVar1->nScreenBoxValid = 0, (pAVar1->dwFlags & 3) == 0)) {
      puVar4 = DrawList_Alloc();
      if (puVar4 == (undefined *)0x0) {
        return;
      }
      local_18 = pAVar1->aPos[0] - *g_pSputRender_Camera;
      local_14[0] = pAVar1->aPos[1] - g_pSputRender_Camera[1];
      local_14[1] = pAVar1->aPos[2] - g_pSputRender_Camera[2];
      rdMatrix_TransformVectorOrtho34(&local_c,&local_18,g_pSputRender_Camera + 0xc);
      *(uint *)(puVar4 + 4) = local_8;
      if (pAVar1->pCostumes == (CostumeNode *)0x0) {
        *(int *)(puVar4 + 8) = ((int)pAVar1 - (int)g_pActors) / 0xa8;
        if ((pAVar1->pCostumes == (CostumeNode *)0x0) ||
           (pAVar1->pCostumes->pMainModel == (void *)0x0)) {
          *puVar4 = 0xff;
        }
        else {
          *puVar4 = 1;
        }
      }
      else {
        *puVar4 = 0;
        *(int *)(puVar4 + 8) = ((int)pAVar1 - (int)g_pActors) / 0xa8;
      }
    }
    piVar2 = (int *)piVar2[2];
  } while( true );
}
#undef local_14
#undef local_18
#undef local_8
#undef local_c


/* ---- 0x004862e0  sputRender_ReverseProject ---- */
/* Reads the depth image at (x,y) and un-projects the pixel through the current camera frame
   Original name sputRender_ReverseProject (the remaster's GrimFandango (Linux): aligned call in
   sputLua_ScreenToWorldL); was Render_ScreenToWorld. */

void __cdecl sputRender_ReverseProject(int x,int y,float *outPos)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float (*)[2])(_frame + (0x20 - 0x8)))
  
  if ((g_pRdCamera_CurCamera != (void *)0x0) && (*(int *)((int)g_pRdCamera_CurCamera + 4) != 0)) {
    fVar2 = (float)(int)((uint)*(ushort *)
                                (*(int *)(UINT_008c97a4 + 0x5c) +
                                (*(int *)(UINT_008c97a4 + 0xc) * y + x) * 2) <<
                        ((byte)*(undefined4 *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x14) &
                        0x1f)) * 1.5258789e-05;
    fVar1 = *(float *)((int)g_pRdCamera_CurCamera + 0x3c) * fVar2;
    local_8[0] = 1.0 / fVar2 - 1.0;
    local_c = (1.0 / fVar1) * ((float)x - *(float *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 8));
    local_8[1] = (-1.0 / fVar1) *
                 ((float)y - *(float *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0xc));
    rdMatrix_TransformPoint34(outPos,&local_c,g_pSputRender_Camera + 0xc);
  }
  return;
}
#undef local_8
#undef local_c


/* ---- 0x004863b0  sputRender_PreRendered ---- */
/* Original name sputRender_PreRendered (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_PreRender; 1 matched neighbours agree, 0 disagree); was
   Render_InvalidateBackground. */

void __cdecl sputRender_PreRendered(int redrawBackground,int redrawDepth)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  int iVar2;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  g_dwRenderFlags = g_dwRenderFlags | 3;
  pvVar1 = sputRoom_GetCurrentRoom();
  if (pvVar1 != (void *)0x0) {
    pvVar1 = sputRoom_GetCurrentRoom();
    iVar2 = *(int *)((int)pvVar1 + 0xb4);
    pvVar1 = sputRoom_GetCurrentRoom();
    iVar2 = *(int *)((int)pvVar1 + 0xac) + iVar2 * 300;
    if (iVar2 != 0) {
      if ((redrawBackground != 0) && (*(int *)(iVar2 + 0xc0) != 0)) {
        g_dwRenderFlags = g_dwRenderFlags & 0xfffffffe;
      }
      if ((redrawDepth != 0) && (*(int *)(iVar2 + 0xf4) != 0)) {
        g_dwRenderFlags = g_dwRenderFlags & 0xfffffffd;
      }
      local_10 = *(uint *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x18);
      local_c = *(uint *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x1c);
      local_8 = (*(int *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x20) -
                *(int *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x18)) + 1;
      local_4 = (*(int *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x24) -
                *(int *)(*(int *)((int)g_pRdCamera_CurCamera + 4) + 0x1c)) + 1;
      iVar2 = 0;
      if (0 < g_nNumPages) {
        do {
          DirtyRect_Add((int *)&local_10,1,iVar2);
          iVar2 = iVar2 + 1;
        } while (iVar2 < g_nNumPages);
      }
    }
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004864a0  Render_BuildColorTable ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Fills the 65536-entry 16-bit remap table g_wSputRender_ColorLookup for the pixel format and gamma
    */

void __cdecl Render_BuildColorTable(int param_1,float param_2)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  #define local_40 (*(uint *)(_frame + (0x50 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x50 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x50 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x50 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x50 - 0x8)))
  
  local_24 = 0;
  do {
    fVar7 = _CIpow();
    fVar8 = _CIpow();
    fVar9 = _CIpow();
    uVar1 = *(undefined4 *)(param_1 + 0xc);
    uVar2 = *(undefined4 *)(param_1 + 0x10);
    lVar4 = FTOL((float10)((float)((1 << ((byte)*(undefined4 *)(param_1 + 8) & 0x1f)) + -1) * fVar7
                           ));
    uVar3 = *(undefined4 *)(param_1 + 0x14);
    lVar5 = FTOL((float10)((float)((1 << ((byte)uVar1 & 0x1f)) + -1) * fVar8));
    uVar1 = *(undefined4 *)(param_1 + 0x18);
    lVar6 = FTOL((float10)((float)((1 << ((byte)uVar2 & 0x1f)) + -1) * fVar9));
    (&g_wSputRender_ColorLookup)[local_24] =
         (ushort)((int)lVar4 << ((byte)uVar3 & 0x1f)) | (ushort)((int)lVar5 << ((byte)uVar1 & 0x1f))
         | (ushort)((int)lVar6 << ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f));
    local_24 = local_24 + 1;
  } while ((int)local_24 < 0x10000);
  g_flSputRender_GammaCorrection = param_2;
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_8
#undef local_c

#endif


/* ---- 0x00486620  sputRender_ColorCorrect ---- */
/* Original name sputRender_ColorCorrect (the remaster's GrimFandango (Linux): the only unmatched
   callee of Shadow_SetColor; 5 matched neighbours agree, 0 disagree); was Render_RemapPixels. */

void __cdecl sputRender_ColorCorrect(ushort *pixels,uint n)

{
  int iVar1;
  ushort *puVar2;
  uint uVar3;
  
  iVar1 = (int)(n + ((int)n >> 0x1f & 7U)) >> 3;
  puVar2 = pixels;
  if (0 < iVar1) {
    do {
      puVar2 = pixels + 8;
      *pixels = (&g_wSputRender_ColorLookup)[*pixels];
      pixels[1] = (&g_wSputRender_ColorLookup)[pixels[1]];
      pixels[2] = (&g_wSputRender_ColorLookup)[pixels[2]];
      pixels[3] = (&g_wSputRender_ColorLookup)[pixels[3]];
      pixels[4] = (&g_wSputRender_ColorLookup)[pixels[4]];
      pixels[5] = (&g_wSputRender_ColorLookup)[pixels[5]];
      pixels[6] = (&g_wSputRender_ColorLookup)[pixels[6]];
      iVar1 = iVar1 + -1;
      pixels[7] = (&g_wSputRender_ColorLookup)[pixels[7]];
      pixels = puVar2;
    } while (iVar1 != 0);
  }
  uVar3 = n & 7;
  if (uVar3 != 0) {
    puVar2 = puVar2 + (uVar3 - 1);
    do {
      uVar3 = uVar3 - 1;
      *puVar2 = (&g_wSputRender_ColorLookup)[*puVar2];
      puVar2 = puVar2 + -1;
    } while (uVar3 != 0);
  }
  return;
}

/* ---- 0x00486710  sputRender_SetGamma ---- */
/* Rebuilds the colour constants and redraws the current setup when the gamma changes Original name
   sputRender_SetGamma (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_SetGamma; 2 matched neighbours agree, 0 disagree); was Render_SetGamma. */

void __cdecl sputRender_SetGamma(float gamma)

{
  void *pvVar1;
  int setupIdx;
  
  if (g_flSputRender_GammaCorrection != gamma) {
    g_flSputRender_GammaCorrection = gamma;
    Render_InitColorConstants(UINT_008c9780);
    pvVar1 = sputRoom_GetCurrentRoom();
    if (pvVar1 != (void *)0x0) {
      pvVar1 = sputRoom_GetCurrentRoom();
      setupIdx = *(int *)((int)pvVar1 + 0xb4);
      pvVar1 = sputRoom_GetCurrentRoom();
      sputRender_UseSetup(pvVar1,setupIdx);
    }
  }
  return;
}

/* ---- 0x00486760  sputRender_Decompress ---- */
/* Converts a compressed (type 2) background bitmap into g_pSputRender_DecompressionBuffer and
   remaps its pixels Original name sputRender_Decompress (the remaster's GrimFandango (Linux):
   aligned call in sputRender_UseSetup); was Render_ConvertBackground. */

void __cdecl sputRender_Decompress(void *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  
  iVar1 = *(int *)((int)param_1 + 0x10);
  iVar2 = *(int *)((int)param_1 + 0xc);
  stdDisplay_VBufferDeCompressTo(param_1,g_pSputRender_DecompressionBuffer);
  piVar4 = (int *)((int)param_1 + 0xc);
  piVar5 = (int *)((int)g_pSputRender_DecompressionBuffer + 0xc);
  for (iVar3 = 0x13; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar5 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  }
  *(undefined4 *)((int)g_pSputRender_DecompressionBuffer + 0x60) = 0xf81f;
  if (*(int *)((int)param_1 + 0x20) != 5) {
    sputRender_ColorCorrect
              (*(ushort **)((int)g_pSputRender_DecompressionBuffer + 0x5c),iVar1 * iVar2);
    *(uint *)((int)g_pSputRender_DecompressionBuffer + 0x60) = (uint)DAT_008c856e;
  }
  return;
}

/* ---- 0x004867d0  sputRender_Dim ---- */
/* Renders a frame, copies it to the background and darkens every pixel by the given shift (used
   while menus are up) Original name sputRender_Dim (the remaster's GrimFandango (Linux): the only
   unmatched callee of Lua_DimScreen; 2 matched neighbours agree, 1 disagree); was
   Render_DimBackground. */

void __cdecl sputRender_Dim(ushort *param_1,byte param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  void *surface;
  void *pvVar3;
  uint uVar4;
  int iVar5;
  byte bVar6;
  byte bVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  if ((g_dwGrimlib_mode != 4) || (param_1 != (ushort *)0x0)) {
    if (g_dwGrimlib_mode == 3) {
      sputSmush_SetTarget(&g_dwStdDisplay_backBuffer);
    }
    else {
      sputText_Pause();
      sputPrimitive_Pause();
      sputTime_AdvanceManual(0);
      sputRender_Update();
      rdFinishFrame();
      sputText_Resume();
      sputPrimitive_Resume();
    }
    Render_CopyBackBufferToBackground();
    surface = g_pSputRender_CleanBuffer;
    stdDisplay_VBufferLock(g_pSputRender_CleanBuffer);
    uVar1 = *(undefined4 *)((int)surface + 0x2c);
    uVar2 = *(undefined4 *)((int)surface + 0x30);
    local_1c = 0;
    if (0 < *(int *)((int)surface + 0x10)) {
      do {
        param_1 = (ushort *)
                  (local_1c * *(int *)((int)surface + 0x18) + *(int *)((int)surface + 0x5c));
        local_20 = 0;
        if (0 < *(int *)((int)surface + 0xc)) {
          do {
            pvVar3 = sputRoom_GetCurrentRoom();
            if (pvVar3 == (void *)0x0) {
              uVar8 = 0;
            }
            else {
              uVar8 = (uint)*param_1;
            }
            bVar6 = (byte)*(undefined4 *)((int)surface + 0x40);
            uVar9 = (uVar8 >> (*(byte *)((int)surface + 0x34) & 0x1f)) << (bVar6 & 0x1f);
            bVar7 = (byte)*(undefined4 *)((int)surface + 0x44);
            uVar4 = (uVar8 >> (*(byte *)((int)surface + 0x38) & 0x1f) &
                    0xffffffffU >> (0x20U - (char)uVar1 & 0x1f)) << (bVar7 & 0x1f);
            uVar8 = 0xffffffffU >> (0x20U - (char)uVar2 & 0x1f) & uVar8;
            uVar10 = uVar9;
            if ((int)uVar9 <= (int)uVar4) {
              uVar10 = uVar4;
            }
            if (((int)uVar8 < (int)uVar10) && (uVar8 = uVar4, (int)uVar4 < (int)uVar9)) {
              uVar8 = uVar9;
            }
            iVar5 = (int)uVar8 >> (param_2 & 0x1f);
            *param_1 = (ushort)((iVar5 >> (bVar6 & 0x1f)) <<
                               ((byte)*(undefined4 *)((int)surface + 0x34) & 0x1f)) |
                       (ushort)((iVar5 >> (bVar7 & 0x1f)) <<
                               ((byte)*(undefined4 *)((int)surface + 0x38) & 0x1f)) |
                       (ushort)(iVar5 >> ((byte)*(undefined4 *)((int)surface + 0x48) & 0x1f));
            local_20 = local_20 + 1;
            param_1 = param_1 + 1;
          } while ((int)local_20 < *(int *)((int)surface + 0xc));
        }
        local_1c = local_1c + 1;
      } while ((int)local_1c < *(int *)((int)surface + 0x10));
    }
    stdDisplay_VBufferUnlock(surface);
    local_10 = 0;
    local_c = 0;
    local_8 = *(uint *)((int)surface + 0xc);
    local_4 = *(uint *)((int)surface + 0x10);
    MarkDirtyRect((int *)&local_10,0);
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00486990  Render_CopyBackBufferToBackground ---- */
void __cdecl Render_CopyBackBufferToBackground(void)

{
  Surface_Blit(g_pSputRender_CleanBuffer,&g_dwStdDisplay_backBuffer,0,0,(int *)0x0,0);
  return;
}

/* ---- 0x004869b0  Render_CleanBuffer ---- */
/* Lua CleanBuffer: after a restore, copies the background back onto the back buffer */

void __cdecl Render_CleanBuffer(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (g_dwGrimlib_mode == 4) {
    local_10 = 0;
    local_c = 0;
    local_8 = 0x280;
    local_4 = 0x1e0;
    Surface_Blit(&g_dwStdDisplay_backBuffer,g_pSputRender_CleanBuffer,0,0,(int *)&local_10,0);
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00486a00  sputRender_ForceRefresh ---- */
/* Lua opcode: ForceRefresh Original name sputRender_ForceRefresh (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ForceRefresh'); was Render_RequestFullRedraw. */

void __cdecl sputRender_ForceRefresh(void)

{
  g_nSputRender_Reset = 1;
  return;
}

/* ---- 0x00486b00  sputRender_CleanArtBuffer ---- */
/* Original name sputRender_CleanArtBuffer (the remaster's GrimFandango (Linux): aligned call in
   sputActor_DrawToClean); was Render_GetBackgroundSurface. */

void * __cdecl sputRender_CleanArtBuffer(void)

{
  return g_pSputRender_CleanBuffer;
}

/* ---- 0x00486b10  sputRender_CleanZBuffer ---- */
/* Original name sputRender_CleanZBuffer (the remaster's GrimFandango (Linux): aligned call in
   sputActor_DrawToClean); was Render_GetZBufferSurface. */

void * __cdecl sputRender_CleanZBuffer(void)

{
  return g_pSputRender_CleanZBuffer;
}

/* ---- 0x00486b20  sputRender_SetPaletteFunc ---- */
/* Original name sputRender_SetPaletteFunc (the remaster's GrimFandango (Linux): same body (returns
   the palette callback global); the call after the colormap set-up in sputActor_DrawToClean in both
   builds); was Render_GetUserCallback. */

code * __cdecl sputRender_SetPaletteFunc(void)

{
  return (code *)g_dwSputRender_pSetPaletteFunc;
}

/* ---- 0x00486b30  sputRender_SetPageFlip ---- */
/* Original name sputRender_SetPageFlip (the remaster's GrimFandango (Linux): aligned call in
   sputLua_EngineDisplay); was Render_SetDrawEnabled. */

void __cdecl sputRender_SetPageFlip(int param_1)

{
  g_nDoTheFlip = param_1;
  return;
}

/* ---- 0x00486d00  sputRender_DrawIrisEffect ---- */
/* Blacks out the back buffer outside a rectangle centred on (x,y) that has closed by `percent` (0 =
   fully open, 1 = closed) Original name sputRender_DrawIrisEffect (the remaster's GrimFandango
   (Linux): aligned call in sputRender_Update); was Render_DrawIris. */

void __cdecl sputRender_DrawIrisEffect(float percent,int x,int y)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  longlong lVar11;
  longlong lVar12;
  longlong lVar13;
  
  if ((percent < 0.0) || (1.0 < percent)) {
    (*g_pSputRendHS->pAssertFail)
              (s__percent____0_0f______percent____004e80ec,
               s_C__grimsrc_libs_grimlib_Engine_s_004e80bc,0x9f2);
  }
  lVar11 = FTOL((float10)y * (float10)percent);
  iVar3 = (int)lVar11;
  lVar11 = FTOL((float10)x * (float10)percent);
  lVar12 = FTOL((float10)(0x1e0 - y) * (float10)percent);
  lVar13 = FTOL((float10)(0x280 - x) * (float10)percent);
  uVar2 = UINT_0090563c;
  uVar1 = UINT_009055f8;
  uVar4 = (uint)lVar13;
  stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
  puVar7 = (undefined4 *)uVar2;
  iVar8 = iVar3;
  iVar5 = 0;
  if (0 < iVar3) {
    do {
      iVar8 = iVar8 + -1;
      puVar9 = puVar7;
      for (iVar5 = 0x140; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar9 = 0;
        puVar9 = puVar9 + 1;
      }
      puVar7 = (undefined4 *)((int)puVar7 + uVar1);
      iVar5 = iVar3;
    } while (iVar8 != 0);
  }
  iVar8 = 0x1e0 - (int)lVar12;
  if (iVar5 < iVar8) {
    y = iVar8 - iVar5;
    puVar9 = (undefined4 *)(uVar2 + uVar1 * iVar5);
    puVar7 = (undefined4 *)(uVar2 + (0x280 - uVar4) * 2 + uVar1 * iVar5);
    iVar5 = iVar5 + y;
    do {
      puVar10 = puVar9;
      for (uVar6 = ((uint)lVar11 & 0x7fffffff) >> 1; uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar10 = 0;
        puVar10 = puVar10 + 1;
      }
      puVar9 = (undefined4 *)((int)puVar9 + uVar1);
      for (uVar6 = (uint)lVar11 * 2 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined1 *)puVar10 = 0;
        puVar10 = (undefined4 *)((int)puVar10 + 1);
      }
      puVar10 = puVar7;
      for (uVar6 = (uVar4 & 0x7fffffff) >> 1; uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar10 = 0;
        puVar10 = puVar10 + 1;
      }
      puVar7 = (undefined4 *)((int)puVar7 + uVar1);
      for (uVar6 = uVar4 * 2 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined1 *)puVar10 = 0;
        puVar10 = (undefined4 *)((int)puVar10 + 1);
      }
      y = y + -1;
    } while (y != 0);
  }
  if (iVar5 < 0x1e0) {
    iVar8 = 0x1e0 - iVar5;
    puVar7 = (undefined4 *)(uVar1 * iVar5 + uVar2);
    do {
      iVar8 = iVar8 + -1;
      puVar9 = puVar7;
      for (iVar5 = 0x140; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar9 = 0;
        puVar9 = puVar9 + 1;
      }
      puVar7 = (undefined4 *)((int)puVar7 + uVar1);
    } while (iVar8 != 0);
  }
  stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
  return;
}

/* ---- 0x00486eb0  sputRender_IrisDown ---- */
/* Lua IrisDown: starts an iris transition closing over durationMs Original name sputRender_IrisDown
   (the remaster's GrimFandango (Linux): aligned call in sputLua_IrisDown); was
   Render_StartIrisClose. */

void __cdecl sputRender_IrisDown(int x,int y,int durationMs)

{
  g_dwIrisStart = sputTime_GetGameTime();
  g_nIrisY = y;
  g_flIrisDuration = (float)durationMs;
  g_nIrisX = x;
  g_dwRenderFlags = g_dwRenderFlags | 4;
  return;
}

/* ---- 0x00486ef0  sputRender_IrisUp ---- */
/* Lua IrisUp: starts an iris transition opening over durationMs (negative duration) Original name
   sputRender_IrisUp (the remaster's GrimFandango (Linux): aligned call in sputLua_IrisUp); was
   Render_StartIrisOpen. */

void __cdecl sputRender_IrisUp(int x,int y,int durationMs)

{
  g_dwIrisStart = sputTime_GetGameTime();
  g_nIrisY = y;
  g_nIrisX = x;
  g_flIrisDuration = -(float)durationMs;
  g_dwRenderFlags = g_dwRenderFlags | 4;
  return;
}

/* ---- 0x00486f30  sputRender_IrisComplete ---- */
/* Original name sputRender_IrisComplete (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_IrisComplete; 1 matched neighbours agree, 0 disagree); was Render_IsIrisDone. */

uint __cdecl sputRender_IrisComplete(void)

{
  if ((g_dwRenderFlags & 8) != 0) {
    return 1;
  }
  return ~g_dwRenderFlags >> 2 & 1;
}

/* ---- 0x00486f90  sputRender_ScreenShot ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Renders a dimmed frame and scales the background down into a new w x h bitmap (save game
   thumbnail) Original name sputRender_ScreenShot (the remaster's GrimFandango (Linux): the only
   unmatched caller of Render_DimBackground; 2 matched neighbours agree, 0 disagree); was
   Render_CaptureThumbnail. */

void * __cdecl sputRender_ScreenShot(int w,int h)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  void *surface;
  void *surface_00;
  undefined2 *puVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  float10 fVar7;
  float10 extraout_ST0;
  float10 x;
  float10 extraout_ST0_00;
  float10 extraout_ST1;
  longlong lVar8;
  longlong lVar9;
  #define local_5c (*(uint *)(_frame + (0x70 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x70 - 0x54)))
  #define local_50 (*(uint *)(_frame + (0x70 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0x70 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x70 - 0x48)))
  
  uVar2 = g_dwGrimlib_mode;
  g_dwGrimlib_mode = 2;
  g_nSputRender_Reset = 1;
  sputRender_Dim((ushort *)0x1,0);
  surface = g_pSputRender_CleanBuffer;
  puVar5 = (uint *)((int)g_pSputRender_CleanBuffer + 0xc);
  puVar6 = &local_4c;
  for (iVar4 = 0x13; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  local_4c = w;
  local_48 = h;
  g_dwGrimlib_mode = uVar2;
  surface_00 = stdDisplay_VBufferNew(&local_4c,0,0,0);
  stdDisplay_VBufferLock(surface_00);
  stdDisplay_VBufferLock(surface);
  local_58 = 0;
  if (0 < h) {
    fVar7 = (float10)0.0;
    do {
      lVar8 = FTOL(fVar7);
      iVar4 = *(int *)((int)surface + 0x5c);
      iVar1 = *(int *)((int)surface + 0x18);
      x = (float10)0.0;
      puVar3 = (undefined2 *)
               (local_58 * *(int *)((int)surface_00 + 0x18) + *(int *)((int)surface_00 + 0x5c));
      fVar7 = extraout_ST0;
      if (0 < w) {
        local_5c = w;
        do {
          lVar9 = FTOL(x);
          x = extraout_ST0_00 + (float10)(640.0 / (float)w);
          *puVar3 = *(undefined2 *)((int)lVar8 * iVar1 + iVar4 + (int)lVar9 * 2);
          puVar3 = puVar3 + 1;
          local_5c = local_5c - 1;
          fVar7 = extraout_ST1;
        } while (local_5c != 0);
      }
      local_58 = local_58 + 1;
      fVar7 = fVar7 + (float10)(480.0 / (float)h);
    } while ((int)local_58 < h);
  }
  stdDisplay_VBufferUnlock(surface_00);
  stdDisplay_VBufferUnlock(surface);
  g_nSputRender_Reset = 1;
  return surface_00;
}
#undef local_48
#undef local_4c
#undef local_50
#undef local_54
#undef local_58
#undef local_5c

#endif


/* ---- 0x004870e0  sputRender_DimRegion ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name sputRender_DimRegion (the remaster's GrimFandango (Linux): aligned call in
   sputLua_DimRegion); was Render_FillRect. */

void __cdecl sputRender_DimRegion(int x,int y,int w,int h,float scale)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  ushort *puVar5;
  ushort *puVar6;
  longlong lVar7;
  longlong lVar8;
  longlong lVar9;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  cVar2 = (char)UINT_00905608;
  cVar3 = (char)UINT_0090560c;
  cVar4 = (char)UINT_00905610;
  stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
  puVar6 = (ushort *)(UINT_0090563c + y * UINT_009055f8 + x * 2);
  if (0 < h) {
    local_14 = h;
    do {
      if (0 < w) {
        local_1c = w;
        puVar5 = puVar6;
        do {
          uVar1 = *puVar5;
          lVar7 = FTOL((float10)((uint)(uVar1 >> ((byte)_DAT_00905614 & 0x1f)) &
                                 0xffffffffU >> (0x20U - cVar2 & 0x1f)) * (float10)scale);
          lVar8 = FTOL((float10)((uint)(uVar1 >> ((byte)UINT_00905618 & 0x1f)) &
                                 0xffffffffU >> (0x20U - cVar3 & 0x1f)) * (float10)scale);
          lVar9 = FTOL((float10)((uint)(uVar1 >> ((byte)UINT_0090561c & 0x1f)) &
                                 0xffffffffU >> (0x20U - cVar4 & 0x1f)) * (float10)scale);
          *puVar5 = (ushort)((int)lVar9 << ((byte)UINT_0090561c & 0x1f)) |
                    (ushort)((int)lVar8 << ((byte)UINT_00905618 & 0x1f)) |
                    (ushort)((int)lVar7 << ((byte)_DAT_00905614 & 0x1f));
          local_1c = local_1c - 1;
          puVar5 = puVar5 + 1;
        } while (local_1c != 0);
      }
      puVar6 = (ushort *)((int)puVar6 + UINT_009055f8);
      local_14 = local_14 - 1;
    } while (local_14 != 0);
  }
  stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x00487260  sputRender_SaveScreen ---- */
/* Lua SaveScreen Original name sputRender_SaveScreen (the remaster's GrimFandango (Linux): the only
   unmatched callee of Lua_SaveScreen; 3 matched neighbours agree, 0 disagree); was
   Render_SaveScreen. */

void __cdecl sputRender_SaveScreen(char *filename)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *bitmap;
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x50 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x50 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x50 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x50 - 0x4)))
  
  local_30 = 8;
  local_2c = 8;
  local_28 = 8;
  local_20 = 8;
  local_38 = 1;
  local_34 = 0x18;
  local_24 = 0x10;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  if (filename != (char *)0x0) {
    bitmap = (void *)stdBitmap_VBufferToBitmap(&g_dwStdDisplay_backBuffer,0,0);
    stdBitmap_ConvertColorFormat((int *)&local_38,(int)bitmap);
    stdWriteImage(filename,bitmap);
    stdBitmap_Free(bitmap);
  }
  return;
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
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004872f0  Render_SaveZBufferBmp ---- */
void __cdecl Render_SaveZBufferBmp(char *filename)

{
  void *bitmap;
  
  stdDisplay_VBufferLock((void *)UINT_008c97a4);
  stdDisplay_VBufferUnlock((void *)UINT_008c97a4);
  bitmap = (void *)stdBitmap_VBufferToBitmap((void *)UINT_008c97a4,0,0);
  stdBitmap_Write(filename,bitmap);
  stdBitmap_Free(bitmap);
  return;
}

/* ---- 0x00487340  sputRender_SaveDrawBuffer ---- */
/* Debug key S: writes the back buffer as a 24-bit .bmp Original name sputRender_SaveDrawBuffer (the
   remaster's GrimFandango (Linux): the only unmatched caller of stdBitmap_SaveByExtension; 2
   matched neighbours agree, 0 disagree); was Render_SaveScreenshotBmp. */

void __cdecl sputRender_SaveDrawBuffer(char *filename)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *bitmap;
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x50 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x50 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x50 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x50 - 0x4)))
  
  local_30 = 8;
  local_2c = 8;
  local_28 = 8;
  local_20 = 8;
  local_38 = 1;
  local_34 = 0x18;
  local_24 = 0x10;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  bitmap = (void *)stdBitmap_VBufferToBitmap(&g_dwStdDisplay_backBuffer,0,0);
  stdBitmap_ConvertColorFormat((int *)&local_38,(int)bitmap);
  stdWriteImage(filename,bitmap);
  stdBitmap_Free(bitmap);
  return;
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
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004873d0  Render_DrawProgressBar ---- */
/* Draws the save/load progress bar directly on the primary surface */

void __cdecl Render_DrawProgressBar(float fraction)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0xffe0;
  if (1.0 < fraction) {
    fraction = 1.0;
  }
  lVar5 = FTOL((float10)fraction * (float10)540.0);
  sputRender_ColorCorrect((ushort *)&local_4,1);
  stdDisplay_VBufferLock(&g_dwStdDisplay_frontBuffer);
  iVar3 = 0x21c;
  iVar1 = UINT_00901698 * 0x1c7 + UINT_009016dc;
  puVar2 = (undefined2 *)(iVar1 + 100);
  do {
    *puVar2 = (undefined2)local_4;
    puVar2 = puVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 0xc;
  do {
    iVar1 = iVar1 + (UINT_00901698 & 0xfffffffe);
    puVar2 = (undefined2 *)(iVar1 + 100);
    *(undefined2 *)(iVar1 + 0x49a) = 0xffe0;
    *puVar2 = 0xffe0;
    iVar4 = (int)lVar5;
    if (0x32 < (int)lVar5 + 0x32) {
      do {
        *puVar2 = (undefined2)local_4;
        puVar2 = puVar2 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  puVar2 = (undefined2 *)(iVar1 + 100);
  iVar1 = 0x21c;
  do {
    *puVar2 = (undefined2)local_4;
    puVar2 = puVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  stdDisplay_VBufferUnlock(&g_dwStdDisplay_frontBuffer);
  return;
}
#undef local_4


/* ---- 0x004874c0  sputRender_AllowLoadImage ---- */
/* Original name sputRender_AllowLoadImage (the remaster's GrimFandango (Linux): the only unpaired
   writer of LoadImageAllowed on both sides, same body); was Render_SetWaitCursorEnabled. */

void __cdecl sputRender_AllowLoadImage(uint param_1)

{
  g_dwLoadImageAllowed = param_1;
  return;
}

/* ---- 0x004874d0  sputRender_DrawLoadingImage ---- */
/* After 3.5 s without a frame, animates wait.bm (BKND resource) on the primary surface every 250 ms
   Original name sputRender_DrawLoadingImage (the remaster's GrimFandango (Linux): aligned call in
   res_Load); was Render_UpdateWaitCursor. */

void __cdecl sputRender_DrawLoadingImage(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int *piVar2;
  int *piVar3;
  undefined *puVar4;
  void *data;
  #define iStack_10 (*(int *)(_frame + (0x20 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x20 - 0xc)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  if ((UINT_004e808c != 0) && (g_dwLoadImageAllowed != 0)) {
    puVar4 = PerfEnd(0xc);
    PerfBegin(0xc);
    g_dwSputRender_DrawLoadingImage_FrameAccum =
         (uint)(puVar4 + g_dwSputRender_DrawLoadingImage_FrameAccum);
    if (5000 < (int)g_dwSputRender_DrawLoadingImage_FrameAccum) {
      g_dwSputRender_DrawLoadingImage_FrameAccum = 0;
      UINT_008c9770 = 0;
      return;
    }
    if (0xdac < (int)g_dwSputRender_DrawLoadingImage_FrameAccum) {
      g_dwSputRender_DrawLoadingImage_FrameAccum = 0xdad;
      UINT_008c9770 = (uint)(puVar4 + UINT_008c9770);
      if (0xf9 < (int)UINT_008c9770) {
        UINT_008c9770 = 0;
        if (UINT_008a92d0 == 0) {
          UINT_004e808c = 0;
          data = sputResource_Alloc(0x444e4b42,s_wait_bm_004e812c);
          if (data == (void *)0x0) {
            return;
          }
          Res_SetReference(&UINT_008a92d0,data,s_C__grimsrc_libs_grimlib_Engine_s_004e80bc,0xb35);
          UINT_004e808c = 1;
          if (UINT_008a92d0 == 0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
          }
        }
        UINT_008c9824 = (UINT_008c9824 + 1) % *(uint *)(UINT_008a92d4 + 100);
        piVar1 = (int *)(UINT_008a92d4 + 0x70);
        piVar2 = (int *)(UINT_008a92d4 + 0x6c);
        piVar3 = (int *)(UINT_008a92d4 + 0x78);
        Surface_Blit(&g_dwStdDisplay_frontBuffer,*(void **)(*piVar3 + UINT_008c9824 * 4),*piVar2,
                     *piVar1,(int *)0x0,1);
        iStack_10 = *piVar2;
        iStack_c = *piVar1;
        uStack_8 = *(undefined4 *)(*(int *)*piVar3 + 0xc);
        uStack_4 = *(undefined4 *)(*(int *)*piVar3 + 0x10);
        MarkDirtyRect(&iStack_10,1);
      }
    }
  }
  return;
}
#undef iStack_10
#undef iStack_c
#undef uStack_4
#undef uStack_8


/* ---- 0x0048f920  sputActor_GetNumActorsTalking ---- */
/* Original name sputActor_GetNumActorsTalking (the remaster's GrimFandango (Linux): the only
   unmatched callee of Lua_IsMessageGoing; 1 matched neighbours agree, 0 disagree); was
   Render_GetFrameCounter. */

int __cdecl sputActor_GetNumActorsTalking(void)

{
  return g_nNumActorsTalking;
}
