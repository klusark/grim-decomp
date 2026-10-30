/* GRIMFANDANGO.EXE :: render.c
 * functions 0x004839f0 .. 0x0048f920 (46 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004839f0  Render_GetBackBuffer ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Returns the back buffer surface g_BackBuffer */

uint * Render_GetBackBuffer(void)

{
  return &g_BackBuffer;
}
#endif


/* ---- 0x00483a00  Render_ToggleDebugOverlay ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Flips debug flag 1 and, when turning it off, invalidates the whole canvas on every buffer */

void Render_ToggleDebugOverlay(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int bufferIdx;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if ((g_dwRenderDebugFlags & 1) == 0) {
    g_dwRenderDebugFlags = g_dwRenderDebugFlags | 1;
  }
  else {
    g_dwRenderDebugFlags = g_dwRenderDebugFlags & 0xfffffffe;
  }
  if ((g_dwRenderDebugFlags & 1) == 0) {
    local_10 = *(uint *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x18);
    local_c = *(uint *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x1c);
    local_8 = (*(int *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x20) -
              *(int *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x18)) + 1;
    local_4 = (*(int *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x24) -
              *(int *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x1c)) + 1;
    bufferIdx = 0;
    if (0 < g_nBufferCount) {
      do {
        DirtyRect_Add((int *)&local_10,1,bufferIdx);
        bufferIdx = bufferIdx + 1;
      } while (bufferIdx < g_nBufferCount);
    }
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x00483a80  Render_SetUserCallback ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void Render_SetUserCallback(uint param_1)

{
  UINT_008c97b8 = param_1;
  return;
}
#endif


/* ---- 0x00483a90  Render_SetFlipCallback ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Installs the function Render_Present calls to show the back buffer */

void Render_SetFlipCallback(void *param_1)

{
  g_pfnFlipCallback = param_1;
  return;
}
#endif


/* ---- 0x00483da0  Render_SaveState ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
int __cdecl Render_SaveState(void *writeFn)

{
  (*(code *)writeFn)(&g_dwIrisStartMs,4);
  (*(code *)writeFn)(&g_flIrisDurationMs,4);
  (*(code *)writeFn)(&g_nIrisX,4);
  (*(code *)writeFn)(&g_nIrisY,4);
  (*(code *)writeFn)(&g_flGamma,4);
  (*(code *)writeFn)(&g_dwRenderFlags,4);
  (*(code *)writeFn)(&g_nDrawEnabled,4);
  (*(code *)writeFn)(&g_nCameraActor,4);
  (*(code *)writeFn)(&UINT_008c97f8,4);
  return 0;
}
#endif


/* ---- 0x00483e20  Render_RestoreState ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
int __cdecl Render_RestoreState(void *readFn)

{
  (*(code *)readFn)(&g_dwIrisStartMs,4);
  (*(code *)readFn)(&g_flIrisDurationMs,4);
  (*(code *)readFn)(&g_nIrisX,4);
  (*(code *)readFn)(&g_nIrisY,4);
  (*(code *)readFn)(&g_flGamma,4);
  (*(code *)readFn)(&g_dwRenderFlags,4);
  (*(code *)readFn)(&g_nDrawEnabled,4);
  (*(code *)readFn)(&g_nCameraActor,4);
  (*(code *)readFn)(&UINT_008c97f8,4);
  return 0;
}
#endif


/* ---- 0x00483ea0  Render_SetZBufferEnabled ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void Render_SetZBufferEnabled(int param_1)

{
  g_nZBufferEnabled = param_1;
  return;
}
#endif


/* ---- 0x00483eb0  Render_SetBufferCount ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void __cdecl Render_SetBufferCount(int n)

{
  g_nBufferCount = 1;
  if (0 < n) {
    g_nBufferCount = n;
  }
  return;
}
#endif


/* ---- 0x00483ed0  Render_InvalidateRectLastBuffer ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl Render_InvalidateRectLastBuffer(int *rect,int flag)

{
  int iVar1;
  uint uVar2;
  
  _DAT_008a92b8 = *rect;
  _DAT_008a92bc = rect[1];
  _DAT_008a92c0 = rect[2];
  _DAT_008a92c4 = rect[3];
  if ((0 < (int)_DAT_008a92c0) && (0 < _DAT_008a92c4)) {
    uVar2 = (int)_DAT_008a92b8 >> 0x1f;
    iVar1 = ((_DAT_008a92b8 ^ uVar2) - uVar2 & 3 ^ uVar2) - uVar2;
    _DAT_008a92c0 = _DAT_008a92c0 + iVar1;
    _DAT_008a92b8 = _DAT_008a92b8 - iVar1;
    uVar2 = (int)_DAT_008a92c0 >> 0x1f;
    iVar1 = ((_DAT_008a92c0 ^ uVar2) - uVar2 & 3 ^ uVar2) - uVar2;
    if (iVar1 != 0) {
      _DAT_008a92c0 = _DAT_008a92c0 + (4 - iVar1);
    }
    DirtyRect_Add((int *)&DAT_008a92b8,flag,g_nBufferCount + -1);
  }
  return;
}
#endif


/* ---- 0x00483f60  Render_InvalidateRect ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Aligns x/width to 4 pixels and marks the rectangle dirty on every buffer */

void __cdecl Render_InvalidateRect(int *rect,int flag)

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
    if (0 < g_nBufferCount) {
      do {
        DirtyRect_Add((int *)&DAT_008a92a8,flag,iVar1);
        iVar1 = iVar1 + 1;
      } while (iVar1 < g_nBufferCount);
    }
  }
  return;
}
#endif


/* ---- 0x00484030  Render_Open ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Creates the rdCanvas, the background, temp and z-buffer surfaces, programs the pixel format into
   RDroid and draws the current set */

undefined4
Render_Open(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
           undefined4 param_6,int param_7)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  bool bVar5;
  #define local_4c (*(undefined4 (*)[19])(_frame + (0x60 - 0x4c)))
  
  Render_Close();
  g_pCanvas = (void *)rdCanvas_New(1,param_1,param_2,param_3,param_4,param_5,param_6,0);
  UINT_008c97a4 = param_2;
  UINT_008c97a0 = param_1;
  puVar3 = (undefined4 *)(param_1 + 0xc);
  puVar4 = local_4c;
  for (iVar2 = 0x13; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  g_pTempSurface = Surface_Create(local_4c,0,0,0);
  bVar5 = *(int *)(param_1 + 8) != 0;
  g_pBackgroundSurface = Surface_Create(local_4c,(uint)bVar5,(uint)bVar5,0);
  if ((g_nZBufferEnabled == 0) || (UINT_004e806c != 0)) {
    iVar2 = 0;
  }
  else {
    iVar2 = 1;
  }
  g_pZBufferSurface = Surface_Create(local_4c,iVar2,iVar2,0);
  if ((g_pBackgroundSurface != (void *)0x0) && (g_pZBufferSurface != (void *)0x0)) {
    UINT_008a94b8 = UINT_0090563c;
    _DAT_008a94c4 = UINT_00905604 >> 3;
    UINT_008a94c0 = UINT_009055f0;
    UINT_008a94bc = *(uint *)(UINT_008c97a0 + 0xc);
    _DAT_008a94cc = UINT_009055f8;
    *(uint *)(param_7 + 0xc) = *(uint *)(param_7 + 0xc) | 2;
    Render_SetPixelFormat(param_7);
    pvVar1 = Set_GetCurrent();
    if (pvVar1 != (void *)0x0) {
      rdCamera_SetAmbientLight
                (*(void **)(*(int *)((int)pvVar1 + 0xac) + 0x48 + *(int *)((int)pvVar1 + 0xb4) * 300
                           ),g_flAmbientLight);
    }
    UINT_008c9780 = (uint)&DAT_00905600;
    Render_InitColorConstants(&UINT_004ddaa0);
    _DAT_008c9790 = 1;
    pvVar1 = Set_GetCurrent();
    if (pvVar1 != (void *)0x0) {
      pvVar1 = Set_GetCurrent();
      iVar2 = *(int *)((int)pvVar1 + 0xb4);
      pvVar1 = Set_GetCurrent();
      Set_SwitchSetup(pvVar1,iVar2);
    }
    Render_RequestFullRedraw();
    return 1;
  }
  return 0;
}
#undef local_4c

#endif


/* ---- 0x004841f0  Render_Close ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Render_Close(void)

{
  if (g_pCanvas != (void *)0x0) {
    rdCanvas_Free(g_pCanvas);
    g_pCanvas = (void *)0x0;
  }
  if (g_pBackgroundSurface != (void *)0x0) {
    Surface_Free(g_pBackgroundSurface);
    g_pBackgroundSurface = (void *)0x0;
  }
  if (g_pZBufferSurface != (void *)0x0) {
    Surface_Free(g_pZBufferSurface);
    g_pZBufferSurface = (void *)0x0;
  }
  if (g_pTempSurface != (void *)0x0) {
    Surface_Free(g_pTempSurface);
    g_pTempSurface = (void *)0x0;
  }
  _DAT_008c9790 = 0;
  return;
}
#endif


/* ---- 0x004849a0  Render_Present ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Calls the flip callback unless the frame was flagged to skip presentation */

void Render_Present(void)

{
  if ((g_nDrawEnabled != 0) && (UINT_008c97f8 == 0)) {
    (*(code *)g_pfnFlipCallback)();
  }
  UINT_008c97f8 = 0;
  return;
}
#endif


/* ---- 0x004849d0  Render_SetPixelFormat ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Copies the 7-dword pixel format and pushes each component shift/mask into RDroid */

void Render_SetPixelFormat(uint *param_1)

{
  int iVar1;
  uint *puVar2;
  
  puVar2 = &UINT_008a9510;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  rdroid_SetGeometryMode(UINT_008a9510);
  rdroid_SetLightingMode(UINT_008a9514);
  rdroid_SetTextureMode(UINT_008a9518);
  rdroid_SetRenderFlags(UINT_008a951c);
  rdroid_SetSortMode(UINT_008a9520);
  rdroid_SetOcclusionMode(UINT_008a9524);
  rdroid_SetZBufferMode(UINT_008a9528);
  return;
}
#endif


/* ---- 0x00484a50  FUN_00484a50 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
undefined4 FUN_00484a50(void)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (g_nDebugKeysEnabled == 0) {
    return 0;
  }
  iVar1 = Input_GetButtonState(0x1d,(int *)0x0,(int *)0x0);
  if (iVar1 != 0) {
    iVar1 = Input_GetButtonState(0x20,(int *)0x0,(int *)0x0);
    if (iVar1 != 0) {
      uVar2 = 1;
      iVar1 = Input_GetButtonState(0x39,(int *)0x0,(int *)0x0);
      if (iVar1 == 0) {
        UINT_008c9818 = 0;
      }
      else if (UINT_008c9818 == 0) {
        Render_ToggleDebugOverlay();
        UINT_008c9818 = 1;
      }
      if ((g_dwRenderDebugFlags & 1) != 0) {
        iVar1 = Input_GetButtonState(0x30,(int *)0x0,(int *)0x0);
        if (iVar1 == 0) {
          UINT_008c9810 = 0;
        }
        else if (UINT_008c9810 == 0) {
          if ((g_dwRenderDebugFlags & 8) == 0) {
            UINT_008c9810 = 1;
            g_dwRenderDebugFlags = g_dwRenderDebugFlags | 8;
          }
          else {
            UINT_008c9810 = 1;
            g_dwRenderDebugFlags = g_dwRenderDebugFlags & 0xfffffff7;
          }
        }
        iVar1 = Input_GetButtonState(0x26,(int *)0x0,(int *)0x0);
        if (iVar1 == 0) {
          UINT_008c9808 = 0;
        }
        else if (UINT_008c9808 == 0) {
          if ((g_dwRenderDebugFlags & 2) == 0) {
            UINT_008c9808 = 1;
            g_dwRenderDebugFlags = g_dwRenderDebugFlags | 2;
          }
          else {
            UINT_008c9808 = 1;
            g_dwRenderDebugFlags = g_dwRenderDebugFlags & 0xfffffffd;
          }
        }
        iVar1 = Input_GetButtonState(0x2e,(int *)0x0,(int *)0x0);
        if (iVar1 == 0) {
          UINT_008c980c = 0;
        }
        else if (UINT_008c980c == 0) {
          if ((g_dwRenderDebugFlags & 4) == 0) {
            UINT_008c980c = 1;
            g_dwRenderDebugFlags = g_dwRenderDebugFlags | 4;
          }
          else {
            UINT_008c980c = 1;
            g_dwRenderDebugFlags = g_dwRenderDebugFlags & 0xfffffffb;
          }
        }
        iVar1 = Input_GetButtonState(0x13,(int *)0x0,(int *)0x0);
        if (iVar1 == 0) {
          UINT_008c9814 = 0;
        }
        else if (UINT_008c9814 == 0) {
          if ((g_dwRenderDebugFlags & 0x10) != 0) {
            UINT_008c9814 = 1;
            g_dwRenderDebugFlags = g_dwRenderDebugFlags & 0xffffffef;
            return 1;
          }
          UINT_008c9814 = 1;
          g_dwRenderDebugFlags = g_dwRenderDebugFlags | 0x10;
          return 1;
        }
      }
    }
  }
  return uVar2;
}
#endif


/* ---- 0x00484c40  Render_InitColorConstants ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Builds the 16-bit colour constants (black, white, greys, red, green, blue, text colours) for the
   current pixel format */

void Render_InitColorConstants(int param_1)

{
  Render_BuildColorTable(UINT_008c9780,g_flGamma);
  g_wTextColors[2] =
       (&g_wColorTable)
       [(0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97c8,0,2) =
       (&g_wColorTable)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0x80 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0x80 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  DAT_008c97c6 = (&g_wColorTable)
                 [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
                  ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
                  (0xff >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
                  ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
                  (0xff >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
                  ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97c8,2,2) =
       (&g_wColorTable)
       [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
        (0xff >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97cc,0,2) =
       (&g_wColorTable)
       [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97cc,2,2) =
       (&g_wColorTable)
       [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97d0,0,2) =
       (&g_wColorTable)
       [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97d4,0,2) =
       (&g_wColorTable)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97d4,2,2) =
       (&g_wColorTable)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  _DAT_008c97d8 =
       (&g_wColorTable)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0x80 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU];
  _DAT_008c97da =
       (&g_wColorTable)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97d0,2,2) =
       (&g_wColorTable)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0x80 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU];
  _DAT_008c97dc =
       (&g_wColorTable)
       [(0x80 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0x80 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  _DAT_008c97de =
       (&g_wColorTable)
       [(0xc0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0xc0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0xc0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97e0,0,2) =
       (&g_wColorTable)
       [(0xdc >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0xc0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0xc0 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97e0,2,2) =
       (&g_wColorTable)
       [(0xf0 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0xca >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0xa6 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97e4,0,2) =
       (&g_wColorTable)
       [(0xb4 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (0xb4 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0xb4 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97e4,2,2) =
       (&g_wColorTable)
       [(100 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU |
        (100 >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (100 >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97e8,0,2) =
       (&g_wColorTable)
       [(0xff >> ((byte)*(undefined4 *)(param_1 + 0x28) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f) & 0xffffU |
        (0xff >> ((byte)*(undefined4 *)(param_1 + 0x20) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x14) & 0x1f) & 0xffffU |
        (0 >> ((byte)*(undefined4 *)(param_1 + 0x24) & 0x1f)) <<
        ((byte)*(undefined4 *)(param_1 + 0x18) & 0x1f) & 0xffffU];
  PIECE(UINT_008c97e8,2,2) =
       (&g_wColorTable)
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
#endif


/* ---- 0x00485bd0  Render_DrawDebugGrid ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void Render_DrawDebugGrid(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = 0x14;
  local_1c = 0xbf800000;
  do {
    local_c = 0xbf800000;
    local_4 = 0;
    local_18 = 0x3f800000;
    local_10 = 0;
    local_14 = local_1c;
    local_8 = local_1c;
    rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,UINT_008c97c8 & 0xffff,0xff00ff00);
    local_1c = PUN(uint,(float)(PUN(float,local_1c) - -0.1));
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  iVar1 = 0x14;
  local_1c = 0xbf800000;
  do {
    local_8 = 0xbf800000;
    local_4 = 0;
    local_14 = 0x3f800000;
    local_10 = 0;
    local_18 = local_1c;
    local_c = local_1c;
    rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,UINT_008c97c8 & 0xffff,0xff00ff00);
    local_1c = PUN(uint,(float)(PUN(float,local_1c) - -0.1));
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  local_18 = 0x40000000;
  local_14 = 0;
  local_10 = 0;
  rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,DAT_008c97c6,0xffffffff);
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  local_18 = 0;
  local_14 = 0x40000000;
  local_10 = 0;
  rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,DAT_008c97c6,0xffffffff);
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0x40000000;
  rdPrimit3_DrawLine(&local_c,&local_18,0,0,0,0,DAT_008c97c6,0xffffffff);
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


/* ---- 0x00486100  Render_CanvasIsPaletted ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
int Render_CanvasIsPaletted(void)

{
  return **(int **)((int)g_pCanvas + 4) == 1;
}
#endif


/* ---- 0x00486120  Render_BuildActorDrawList ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Collects the visible actors of the current set with their view-space depth into 12-byte {kind,
   depth, index} entries and sorts them back to front */

void Render_BuildActorDrawList(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  void *pvVar2;
  undefined1 *puVar3;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  DrawList_Reset();
  pvVar2 = Set_GetCurrent();
  piVar1 = *(int **)(*(int *)((int)pvVar2 + 0x1abc) + 0x80);
  do {
    if (piVar1 == (int *)0x0) {
      qsort(&UINT_008c9568,UINT_008a952c,4,FUN_004862b0);
      return;
    }
    pvVar2 = (void *)((int)g_pActorTable + *piVar1 * 0xa8);
    if ((pvVar2 != (void *)0x0) &&
       (*(undefined4 *)((int)pvVar2 + 0x68) = 0, (*(byte *)((int)pvVar2 + 4) & 3) == 0)) {
      puVar3 = (undefined1 *)DrawList_Alloc();
      if (puVar3 == (undefined1 *)0x0) {
        return;
      }
      local_18 = PUN(uint,(float)(*(float *)((int)pvVar2 + 0xc) - *g_pCameraSetup));
      local_14 = PUN(uint,(float)(*(float *)((int)pvVar2 + 0x10) - g_pCameraSetup[1]));
      local_10 = PUN(uint,(float)(*(float *)((int)pvVar2 + 0x14) - g_pCameraSetup[2]));
      Vec3_TransformTo(&local_c,(float *)&local_18,g_pCameraSetup + 0xc);
      *(uint *)(puVar3 + 4) = local_8;
      if (*(int *)((int)pvVar2 + 0xa0) == 0) {
        *(int *)(puVar3 + 8) = ((int)pvVar2 - (int)g_pActorTable) / 0xa8;
        if ((*(int *)((int)pvVar2 + 0xa0) == 0) || (*(int *)(*(int *)((int)pvVar2 + 0xa0) + 4) == 0)
           ) {
          *puVar3 = 0xff;
        }
        else {
          *puVar3 = 1;
        }
      }
      else {
        *puVar3 = 0;
        *(int *)(puVar3 + 8) = ((int)pvVar2 - (int)g_pActorTable) / 0xa8;
      }
    }
    piVar1 = (int *)piVar1[2];
  } while( true );
}
#undef local_10
#undef local_14
#undef local_18
#undef local_8
#undef local_c

#endif


/* ---- 0x004862e0  Render_ScreenToWorld ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Reads the depth image at (x,y) and un-projects the pixel through the current camera frame */

void __cdecl Render_ScreenToWorld(int x,int y,float *outPos)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if ((g_pRdCurrentCamera != (void *)0x0) && (*(int *)((int)g_pRdCurrentCamera + 4) != 0)) {
    fVar2 = (float)(int)((uint)*(ushort *)
                                (*(int *)(UINT_008c97a4 + 0x5c) +
                                (*(int *)(UINT_008c97a4 + 0xc) * y + x) * 2) <<
                        ((byte)*(undefined4 *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x14) & 0x1f)
                        ) * 1.5258789e-05;
    fVar1 = *(float *)((int)g_pRdCurrentCamera + 0x3c) * fVar2;
    local_8 = PUN(uint,(float)(1.0 / fVar2 - 1.0));
    local_c = PUN(uint,(float)((1.0 / fVar1) *
                    ((float)x - *(float *)(*(int *)((int)g_pRdCurrentCamera + 4) + 8))));
    local_4 = PUN(uint,(float)((-1.0 / fVar1) *
                    ((float)y - *(float *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0xc))));
    Vec3_Sub(outPos,(float *)&local_c,g_pCameraSetup + 0xc);
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004863b0  Render_InvalidateBackground ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void __cdecl Render_InvalidateBackground(int redrawBackground,int redrawDepth)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  int iVar2;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  g_dwRenderFlags = g_dwRenderFlags | 3;
  pvVar1 = Set_GetCurrent();
  if (pvVar1 != (void *)0x0) {
    pvVar1 = Set_GetCurrent();
    iVar2 = *(int *)((int)pvVar1 + 0xb4);
    pvVar1 = Set_GetCurrent();
    iVar2 = *(int *)((int)pvVar1 + 0xac) + iVar2 * 300;
    if (iVar2 != 0) {
      if ((redrawBackground != 0) && (*(int *)(iVar2 + 0xc0) != 0)) {
        g_dwRenderFlags = g_dwRenderFlags & 0xfffffffe;
      }
      if ((redrawDepth != 0) && (*(int *)(iVar2 + 0xf4) != 0)) {
        g_dwRenderFlags = g_dwRenderFlags & 0xfffffffd;
      }
      local_10 = *(uint *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x18);
      local_c = *(uint *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x1c);
      local_8 = (*(int *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x20) -
                *(int *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x18)) + 1;
      local_4 = (*(int *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x24) -
                *(int *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0x1c)) + 1;
      iVar2 = 0;
      if (0 < g_nBufferCount) {
        do {
          DirtyRect_Add((int *)&local_10,1,iVar2);
          iVar2 = iVar2 + 1;
        } while (iVar2 < g_nBufferCount);
      }
    }
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004864a0  Render_BuildColorTable ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_40 */
/* Fills the 65536-entry 16-bit remap table g_wColorTable for the pixel format and gamma */

void Render_BuildColorTable(int param_1,float param_2)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
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
    _CIpow();
    _CIpow();
    _CIpow();
    iVar3 = (1 << ((byte)*(undefined4 *)(param_1 + 0xc) & 0x1f)) + -1;
    iVar4 = (1 << ((byte)*(undefined4 *)(param_1 + 0x10) & 0x1f)) + -1;
    lVar5 = _ftol((double)CONCAT44(iVar3,iVar4));
    uVar1 = *(undefined4 *)(param_1 + 0x14);
    lVar6 = _ftol((double)CONCAT44(iVar3,iVar4));
    uVar2 = *(undefined4 *)(param_1 + 0x18);
    lVar7 = _ftol((double)CONCAT44(iVar3,iVar4));
    (&g_wColorTable)[local_24] =
         (ushort)((int)lVar5 << ((byte)uVar1 & 0x1f)) | (ushort)((int)lVar6 << ((byte)uVar2 & 0x1f))
         | (ushort)((int)lVar7 << ((byte)*(undefined4 *)(param_1 + 0x1c) & 0x1f));
    local_24 = local_24 + 1;
  } while ((int)local_24 < 0x10000);
  g_flGamma = param_2;
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


/* ---- 0x00486620  Render_RemapPixels ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void __cdecl Render_RemapPixels(ushort *pixels,uint n)

{
  int iVar1;
  ushort *puVar2;
  uint uVar3;
  
  iVar1 = (int)(n + ((int)n >> 0x1f & 7U)) >> 3;
  puVar2 = pixels;
  if (0 < iVar1) {
    do {
      puVar2 = pixels + 8;
      *pixels = (&g_wColorTable)[*pixels];
      pixels[1] = (&g_wColorTable)[pixels[1]];
      pixels[2] = (&g_wColorTable)[pixels[2]];
      pixels[3] = (&g_wColorTable)[pixels[3]];
      pixels[4] = (&g_wColorTable)[pixels[4]];
      pixels[5] = (&g_wColorTable)[pixels[5]];
      pixels[6] = (&g_wColorTable)[pixels[6]];
      iVar1 = iVar1 + -1;
      pixels[7] = (&g_wColorTable)[pixels[7]];
      pixels = puVar2;
    } while (iVar1 != 0);
  }
  uVar3 = n & 7;
  if (uVar3 != 0) {
    puVar2 = puVar2 + (uVar3 - 1);
    do {
      uVar3 = uVar3 - 1;
      *puVar2 = (&g_wColorTable)[*puVar2];
      puVar2 = puVar2 + -1;
    } while (uVar3 != 0);
  }
  return;
}
#endif


/* ---- 0x00486710  Render_SetGamma ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Rebuilds the colour constants and redraws the current setup when the gamma changes */

void __cdecl Render_SetGamma(float gamma)

{
  void *pvVar1;
  int setupIdx;
  
  if (g_flGamma != gamma) {
    g_flGamma = gamma;
    Render_InitColorConstants(UINT_008c9780);
    pvVar1 = Set_GetCurrent();
    if (pvVar1 != (void *)0x0) {
      pvVar1 = Set_GetCurrent();
      setupIdx = *(int *)((int)pvVar1 + 0xb4);
      pvVar1 = Set_GetCurrent();
      Set_SwitchSetup(pvVar1,setupIdx);
    }
  }
  return;
}
#endif


/* ---- 0x00486760  Render_ConvertBackground ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Converts a compressed (type 2) background bitmap into g_pTempSurface and remaps its pixels */

void Render_ConvertBackground(void *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  
  iVar1 = *(int *)((int)param_1 + 0x10);
  iVar2 = *(int *)((int)param_1 + 0xc);
  Surface_CopyConvert(param_1,g_pTempSurface);
  piVar4 = (int *)((int)param_1 + 0xc);
  piVar5 = (int *)((int)g_pTempSurface + 0xc);
  for (iVar3 = 0x13; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar5 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  }
  *(undefined4 *)((int)g_pTempSurface + 0x60) = 0xf81f;
  if (*(int *)((int)param_1 + 0x20) != 5) {
    Render_RemapPixels(*(ushort **)((int)g_pTempSurface + 0x5c),iVar1 * iVar2);
    *(uint *)((int)g_pTempSurface + 0x60) = (uint)DAT_008c856e;
  }
  return;
}
#endif


/* ---- 0x004867d0  Render_DimBackground ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Renders a frame, copies it to the background and darkens every pixel by the given shift (used
   while menus are up) */

void Render_DimBackground(ushort *param_1,byte param_2)

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
  
  if ((UINT_008a8c40 != 4) || (param_1 != (ushort *)0x0)) {
    if (UINT_008a8c40 == 3) {
      Movie_SetTarget(&g_BackBuffer);
    }
    else {
      TextObjects_Freeze();
      Primitives_Hide();
      Timer_UpdateFixedStep(0);
      Engine_RenderFrame();
      rdroid_EndFrame();
      TextObjects_Unfreeze();
      Primitives_Show();
    }
    Render_CopyBackBufferToBackground();
    surface = g_pBackgroundSurface;
    Surface_Lock(g_pBackgroundSurface);
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
            pvVar3 = Set_GetCurrent();
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
    Surface_Unlock(surface);
    local_10 = 0;
    local_c = 0;
    local_8 = *(uint *)((int)surface + 0xc);
    local_4 = *(uint *)((int)surface + 0x10);
    Render_InvalidateRect((int *)&local_10,0);
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

#endif


/* ---- 0x00486990  Render_CopyBackBufferToBackground ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void Render_CopyBackBufferToBackground(void)

{
  Surface_Blit(g_pBackgroundSurface,&g_BackBuffer,0,0,(int *)0x0,0);
  return;
}
#endif


/* ---- 0x004869b0  Render_CleanBuffer ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua CleanBuffer: after a restore, copies the background back onto the back buffer */

void Render_CleanBuffer(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (UINT_008a8c40 == 4) {
    local_10 = 0;
    local_c = 0;
    local_8 = 0x280;
    local_4 = 0x1e0;
    Surface_Blit(&g_BackBuffer,g_pBackgroundSurface,0,0,(int *)&local_10,0);
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x00486a00  Render_RequestFullRedraw ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: ForceRefresh */

void Render_RequestFullRedraw(void)

{
  g_nFullRedrawPending = 1;
  return;
}
#endif


/* ---- 0x00486b00  Render_GetBackgroundSurface ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void * Render_GetBackgroundSurface(void)

{
  return g_pBackgroundSurface;
}
#endif


/* ---- 0x00486b10  Render_GetZBufferSurface ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void * Render_GetZBufferSurface(void)

{
  return g_pZBufferSurface;
}
#endif


/* ---- 0x00486b20  Render_GetUserCallback ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
uint Render_GetUserCallback(void)

{
  return UINT_008c97b8;
}
#endif


/* ---- 0x00486b30  Render_SetDrawEnabled ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void Render_SetDrawEnabled(int param_1)

{
  g_nDrawEnabled = param_1;
  return;
}
#endif


/* ---- 0x00486d00  Render_DrawIris ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Blacks out the back buffer outside a rectangle centred on (x,y) that has closed by `percent` (0 =
   fully open, 1 = closed) */

void __cdecl Render_DrawIris(float percent,int x,int y)

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
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 *puVar10;
  longlong lVar11;
  longlong lVar12;
  longlong lVar13;
  
  if ((percent < 0.0) || (1.0 < percent)) {
    (*g_pSvcRender->pAssertFail)
              (s__percent____0_0f______percent____004e80ec,
               s_C__grimsrc_libs_grimlib_Engine_s_004e80bc,0x9f2);
  }
  lVar11 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  iVar3 = (int)lVar11;
  lVar11 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  lVar12 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  lVar13 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  uVar2 = UINT_0090563c;
  uVar1 = UINT_009055f8;
  uVar4 = (uint)lVar13;
  Surface_Lock(&g_BackBuffer);
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
  Surface_Unlock(&g_BackBuffer);
  return;
}
#endif


/* ---- 0x00486eb0  Render_StartIrisClose ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua IrisDown: starts an iris transition closing over durationMs */

void __cdecl Render_StartIrisClose(int x,int y,int durationMs)

{
  g_dwIrisStartMs = Timer_GetTotalMs();
  g_nIrisY = y;
  g_flIrisDurationMs = (float)durationMs;
  g_nIrisX = x;
  g_dwRenderFlags = g_dwRenderFlags | 4;
  return;
}
#endif


/* ---- 0x00486ef0  Render_StartIrisOpen ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua IrisUp: starts an iris transition opening over durationMs (negative duration) */

void __cdecl Render_StartIrisOpen(int x,int y,int durationMs)

{
  g_dwIrisStartMs = Timer_GetTotalMs();
  g_nIrisY = y;
  g_nIrisX = x;
  g_flIrisDurationMs = -(float)durationMs;
  g_dwRenderFlags = g_dwRenderFlags | 4;
  return;
}
#endif


/* ---- 0x00486f30  Render_IsIrisDone ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
uint Render_IsIrisDone(void)

{
  if ((g_dwRenderFlags & 8) != 0) {
    return 1;
  }
  return ~g_dwRenderFlags >> 2 & 1;
}
#endif


/* ---- 0x00486f90  Render_CaptureThumbnail ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Renders a dimmed frame and scales the background down into a new w x h bitmap (save game
   thumbnail) */

void * __cdecl Render_CaptureThumbnail(int w,int h)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  void *surface;
  void *surface_00;
  undefined2 *puVar3;
  int iVar4;
  undefined4 unaff_ESI;
  uint *puVar5;
  undefined4 unaff_EDI;
  uint *puVar6;
  longlong lVar7;
  longlong lVar8;
  #define local_5c (*(uint *)(_frame + (0x70 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x70 - 0x54)))
  #define local_50 (*(uint *)(_frame + (0x70 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0x70 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x70 - 0x48)))
  
  uVar2 = UINT_008a8c40;
  UINT_008a8c40 = 2;
  g_nFullRedrawPending = 1;
  Render_DimBackground(1,0);
  surface = g_pBackgroundSurface;
  puVar5 = (uint *)((int)g_pBackgroundSurface + 0xc);
  puVar6 = &local_4c;
  for (iVar4 = 0x13; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  local_4c = w;
  local_48 = h;
  UINT_008a8c40 = uVar2;
  surface_00 = Surface_Create(&local_4c,0,0,0);
  Surface_Lock(surface_00);
  Surface_Lock(surface);
  local_58 = 0;
  if (0 < h) {
    do {
      lVar7 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      iVar4 = *(int *)((int)surface + 0x5c);
      iVar1 = *(int *)((int)surface + 0x18);
      puVar3 = (undefined2 *)
               (local_58 * *(int *)((int)surface_00 + 0x18) + *(int *)((int)surface_00 + 0x5c));
      if (0 < w) {
        local_5c = w;
        do {
          lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          *puVar3 = *(undefined2 *)((int)lVar7 * iVar1 + iVar4 + (int)lVar8 * 2);
          puVar3 = puVar3 + 1;
          local_5c = local_5c - 1;
        } while (local_5c != 0);
      }
      local_58 = local_58 + 1;
    } while ((int)local_58 < h);
  }
  Surface_Unlock(surface_00);
  Surface_Unlock(surface);
  g_nFullRedrawPending = 1;
  return surface_00;
}
#undef local_48
#undef local_4c
#undef local_50
#undef local_54
#undef local_58
#undef local_5c

#endif


/* ---- 0x004870e0  Render_FillRect ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl Render_FillRect(int x,int y,int w,int h,float r,float g,float b)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort *puVar1;
  ushort *puVar2;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  Surface_Lock(&g_BackBuffer);
  puVar2 = (ushort *)(UINT_0090563c + y * UINT_009055f8 + x * 2);
  if (0 < h) {
    local_14 = h;
    do {
      if (0 < w) {
        local_1c = w;
        puVar1 = puVar2;
        do {
          lVar3 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          *puVar1 = (ushort)((int)lVar5 << ((byte)UINT_0090561c & 0x1f)) |
                    (ushort)((int)lVar4 << ((byte)UINT_00905618 & 0x1f)) |
                    (ushort)((int)lVar3 << ((byte)_DAT_00905614 & 0x1f));
          local_1c = local_1c - 1;
          puVar1 = puVar1 + 1;
        } while (local_1c != 0);
      }
      puVar2 = (ushort *)((int)puVar2 + UINT_009055f8);
      local_14 = local_14 - 1;
    } while (local_14 != 0);
  }
  Surface_Unlock(&g_BackBuffer);
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


/* ---- 0x00487260  Render_SaveScreen ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua SaveScreen */

void __cdecl Render_SaveScreen(char *filename)

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
    bitmap = (void *)stdBitmap_Convert(&g_BackBuffer,0,0);
    stdBitmap_CopyFrom(&local_38,bitmap);
    stdBitmap_SaveByExtension(filename,bitmap);
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

#endif


/* ---- 0x004872f0  Render_SaveZBufferBmp ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void __cdecl Render_SaveZBufferBmp(char *filename)

{
  void *bitmap;
  
  Surface_Lock((void *)UINT_008c97a4);
  Surface_Unlock((void *)UINT_008c97a4);
  bitmap = (void *)stdBitmap_Convert((void *)UINT_008c97a4,0,0);
  stdBitmap_SaveBM(filename,bitmap);
  stdBitmap_Free(bitmap);
  return;
}
#endif


/* ---- 0x00487340  Render_SaveScreenshotBmp ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Debug key S: writes the back buffer as a 24-bit .bmp */

void __cdecl Render_SaveScreenshotBmp(char *filename)

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
  bitmap = (void *)stdBitmap_Convert(&g_BackBuffer,0,0);
  stdBitmap_CopyFrom(&local_38,bitmap);
  stdBitmap_SaveByExtension(filename,bitmap);
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

#endif


/* ---- 0x004873d0  Render_DrawProgressBar ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Draws the save/load progress bar directly on the primary surface */

void __cdecl Render_DrawProgressBar(float fraction)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0xffe0;
  lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  Render_RemapPixels((ushort *)&local_4,1);
  Surface_Lock(&g_PrimarySurface);
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
  Surface_Unlock(&g_PrimarySurface);
  return;
}
#undef local_4

#endif


/* ---- 0x004874c0  Render_SetWaitCursorEnabled ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void Render_SetWaitCursorEnabled(uint param_1)

{
  UINT_004e8088 = param_1;
  return;
}
#endif


/* ---- 0x004874d0  Render_UpdateWaitCursor ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* After 3.5 s without a frame, animates wait.bm (BKND resource) on the primary surface every 250 ms
    */

void Render_UpdateWaitCursor(void)

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
  
  if ((UINT_004e808c != 0) && (UINT_004e8088 != 0)) {
    puVar4 = Profile_End(0xc);
    Profile_Begin(0xc);
    UINT_008a92c8 = (uint)(puVar4 + UINT_008a92c8);
    if (5000 < (int)UINT_008a92c8) {
      UINT_008a92c8 = 0;
      UINT_008c9770 = 0;
      return;
    }
    if (0xdac < (int)UINT_008a92c8) {
      UINT_008a92c8 = 0xdad;
      UINT_008c9770 = (uint)(puVar4 + UINT_008c9770);
      if (0xf9 < (int)UINT_008c9770) {
        UINT_008c9770 = 0;
        if (UINT_008a92d0 == 0) {
          UINT_004e808c = 0;
          data = Resource_Load(0x444e4b42,s_wait_bm_004e812c);
          if (data == (void *)0x0) {
            return;
          }
          ResRef_Add(&UINT_008a92d0,data,s_C__grimsrc_libs_grimlib_Engine_s_004e80bc,0xb35);
          UINT_004e808c = 1;
          if (UINT_008a92d0 == 0) {
            (*g_pSvcMain->pAssertFail)
                      (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
          }
        }
        UINT_008c9824 = (UINT_008c9824 + 1) % *(uint *)(UINT_008a92d4 + 100);
        piVar1 = (int *)(UINT_008a92d4 + 0x70);
        piVar2 = (int *)(UINT_008a92d4 + 0x6c);
        piVar3 = (int *)(UINT_008a92d4 + 0x78);
        Surface_Blit(&g_PrimarySurface,*(void **)(*piVar3 + UINT_008c9824 * 4),*piVar2,*piVar1,
                     (int *)0x0,1);
        iStack_10 = *piVar2;
        iStack_c = *piVar1;
        uStack_8 = *(undefined4 *)(*(int *)*piVar3 + 0xc);
        uStack_4 = *(undefined4 *)(*(int *)*piVar3 + 0x10);
        Render_InvalidateRect(&iStack_10,1);
      }
    }
  }
  return;
}
#undef iStack_10
#undef iStack_c
#undef uStack_4
#undef uStack_8

#endif


/* ---- 0x0048f920  Render_GetFrameCounter ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
int Render_GetFrameCounter(void)

{
  return g_nTalkingActorCount;
}
#endif

