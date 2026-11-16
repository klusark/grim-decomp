/* GRIMFANDANGO.EXE :: stddisplay.c
 * functions 0x00402580 .. 0x0047bbb0 (60 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00402580  Display_Shutdown3D ---- */
void __cdecl Display_Shutdown3D(void)

{
  uint uVar1;
  
  uVar1 = D3D_IsAvailable();
  if (uVar1 != 0) {
    D3D_ReleaseDriver();
    D3D_Release();
    g_nRdroid_curAcceleration = g_nRdroid_curAcceleration & 0xfffffffe;
    grimlib_Using3DHardware(0);
  }
  return;
}

/* ---- 0x004025b0  Display_Select ---- */
/* Tears down the current display, selects device/mode (falling back to the closest mode), creates
   the back buffer and stores LastDisplayDevice in the registry */

int __cdecl Display_Select(int deviceIdx,int modeIdx,int threeDIdx)

{
  unsigned char _frame[0xb0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  uint *puVar5;
  ColorFormat *pCVar6;
  VBufferFormat *pVVar7;
  VideoMode *pVVar8;
  uint *puVar9;
  VBufferFormat *pVVar10;
  #define VStack_a0 (*(VBufferFormat *)(_frame + (0xb0 - 0xa0)))
  #define local_54 (*(VideoMode *)(_frame + (0xb0 - 0x54)))
  
  UINT_004e814c = 0;
  Grim_ShutdownDisplay();
  if (g_nDisplayDeviceOpen != 0) {
    return 0;
  }
  stdControl_ShowMouseCursor((uint)((&UINT_00902d70)[deviceIdx * 0xa6] == 0));
  Reg_SetInt(s_ExperimentalDisplay_004dd5e4,1);
  iVar1 = Display_SelectDevice(deviceIdx);
  if ((iVar1 != 0) && (iVar1 = Display_OpenMode(modeIdx,&DAT_004f41e0,1), iVar1 != 0)) {
    if ((g_pDisplayDevice->nFullscreen == 0) || (UINT_004f5a84 != 0)) {
LAB_00402747:
      pCVar6 = &(g_pVideoMode->format).colorFormat;
      puVar5 = &g_dwRdColormap_colorInfo;
      for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar5 = pCVar6->nColorMode;
        pCVar6 = (ColorFormat *)&pCVar6->nBpp;
        puVar5 = puVar5 + 1;
      }
      Surface_Fill((VBuffer *)&g_dwStdDisplay_backBuffer,0,(int *)0x0);
      stdDisplay_Update();
      Surface_Fill((VBuffer *)&g_dwStdDisplay_backBuffer,0,(int *)0x0);
      iVar1 = Display_Select3DDevice(threeDIdx);
      if (iVar1 == 0) {
        pVVar7 = &g_pVideoMode->format;
        pVVar10 = &VStack_a0;
        for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
          pVVar10->nWidth = pVVar7->nWidth;
          pVVar7 = (VBufferFormat *)&pVVar7->nHeight;
          pVVar10 = (VBufferFormat *)&pVVar10->nHeight;
        }
        VStack_a0.colorFormat.nBpp = 0x10;
        UINT_004f5a34 = (uint)stdDisplay_VBufferNew(&VStack_a0,0,0,0);
      }
      else {
        UINT_004f5a34 = (uint)&DAT_00901400;
      }
      grimlib_SetDisplay((VBuffer *)&g_dwStdDisplay_backBuffer,UINT_004f5a34);
      Win_SetWindowedSize((uint)(g_pDisplayDevice->nFullscreen != 0),(g_pVideoMode->format).nWidth,
                          (g_pVideoMode->format).nHeight);
      Reg_SetBinary(s_LastDisplayDevice_004dd738,g_pDisplayDevice->aGuid,0x10);
      stdControl_ShowMouseCursor(0);
      g_bWindowedMode = (uint)(g_pDisplayDevice->nFullscreen == 0);
      UINT_004e814c = 1;
      return 1;
    }
    UINT_004f5a84 = 1;
    iVar3 = deviceIdx * 0x10;
    piVar4 = (int *)(*(int *)((int)g_pDisplayModes + iVar3 + 4) + modeIdx * 0x54);
    pVVar8 = &local_54;
    for (iVar1 = 0x15; iVar1 != 0; iVar1 = iVar1 + -1) {
      pVVar8->nFullscreen = *piVar4;
      piVar4 = piVar4 + 1;
      pVVar8 = (VideoMode *)&pVVar8->dwUnknown4;
    }
    Grim_ShutdownDisplay();
    iVar1 = Display_SelectDevice(deviceIdx);
    if (iVar1 != 0) {
      if (g_dwVideoModeCount != *(uint *)((int)g_pDisplayModes + iVar3)) {
        (*g_pStd_HS->pAssertFail)
                  (s_stdDisplay_numVideoModes____grim_004dd74c,
                   s_C__grimsrc_tools_grimdemo_grimde_004dd50c,0x60b);
      }
      puVar5 = &UINT_00901760;
      puVar9 = *(uint **)((int)g_pDisplayModes + iVar3 + 4);
      for (uVar2 = g_dwVideoModeCount * 0x15 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar9 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar9 = puVar9 + 1;
      }
      for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
        *(char *)puVar9 = (char)*puVar5;
        puVar5 = (uint *)((int)puVar5 + 1);
        puVar9 = (uint *)((int)puVar9 + 1);
      }
      uVar2 = Display_FindClosestMode
                        (&local_54,*(VideoMode **)((int)g_pDisplayModes + iVar3 + 4),
                         *(uint *)((int)g_pDisplayModes + iVar3));
      iVar1 = Display_OpenMode(uVar2,&DAT_004f41e0,1);
      if (iVar1 != 0) goto LAB_00402747;
    }
  }
  UINT_004e814c = 0;
  return 0;
}
#undef VStack_a0
#undef local_54


/* ---- 0x00402860  Display_Select3DDevice ---- */
/* Activates the 3D driver record threeDNum (-1 = software) and records Last3DDevice in the registry
    */

int __cdecl Display_Select3DDevice(int threeDNum)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  Display_Shutdown3D();
  if (threeDNum != -1) {
    uVar1 = D3D_Enumerate();
    if (uVar1 != 0) {
      if ((threeDNum < 0) ||
         (*(int *)(UINT_00901758 * 0x10 + 8 + (int)g_pDisplayModes) <= threeDNum)) {
        (*g_pStd_HS->pAssertFail)
                  (s_threeDNum____0____threeDNum____i_004dd7a4,
                   s_C__grimsrc_tools_grimdemo_grimde_004dd50c,0x54d);
      }
      iVar2 = D3D_SelectDriver(threeDNum,1);
      if (iVar2 != 0) {
        g_nRdroid_curAcceleration = g_nRdroid_curAcceleration | 1;
        grimlib_Using3DHardware(1);
        Reg_SetBinary(s_Last3DDevice_004dd794,g_pStd3D_CurDevice->aGuid,0x10);
        return 1;
      }
    }
  }
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  Reg_SetBinary(s_Last3DDevice_004dd794,&local_10,0x10);
  return 0;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00402930  Display_InitFromConfig ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Uses the registry's last display, else picks a default, then Display_Select */

undefined * Display_InitFromConfig(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined *puVar2;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = Display_GetLastFromRegistry(&local_4,&local_8,&local_c);
  if (iVar1 == 0) {
    if ((g_bWindowedMode == 0) || (g_nDeveloper == 0)) {
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
    }
    Display_PickDefault(iVar1,UINT_004f5a28,(int *)&local_4,(int *)&local_8,(int *)&local_c);
  }
  puVar2 = (undefined *)Display_Select(local_4,local_8,local_c);
  return puVar2;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004029b0  Display_GetLastFromRegistry ---- */
/* Matches LastDisplayDevice/Last3DDevice GUIDs from the registry against the enumerated tables.
   Fails when ExperimentalDisplay is set (last switch crashed). */

int __cdecl Display_GetLastFromRegistry(uint *deviceIdx,uint *modeIdx,uint *threeDIdx)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  void *pvVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  bool bVar9;
  byte a3DGuid [16];
  byte aDeviceGuid [16];
  byte aNullGuid [16];
  
  iVar1 = Reg_GetInt(s_ExperimentalDisplay_004dd5e4,1);
  if (iVar1 != 0) {
    OutputDebugStringA(((unsigned)(uintptr_t)&DAT_004dd874));
    return 0;
  }
  aNullGuid[0] = 0;
  aNullGuid[1] = 0;
  aNullGuid[2] = 0;
  aNullGuid[3] = 0;
  aNullGuid[4] = 0;
  aNullGuid[5] = 0;
  aNullGuid[6] = 0;
  aNullGuid[7] = 0;
  aDeviceGuid[0] = 0;
  aDeviceGuid[1] = 0;
  aDeviceGuid[2] = 0;
  aDeviceGuid[3] = 0;
  aNullGuid[8] = 0;
  aNullGuid[9] = 0;
  aNullGuid[10] = 0;
  aNullGuid[0xb] = 0;
  a3DGuid[0] = 0;
  a3DGuid[1] = 0;
  a3DGuid[2] = 0;
  a3DGuid[3] = 0;
  aNullGuid[0xc] = 0;
  aNullGuid[0xd] = 0;
  aNullGuid[0xe] = 0;
  aNullGuid[0xf] = 0;
  aDeviceGuid[4] = 0;
  aDeviceGuid[5] = 0;
  aDeviceGuid[6] = 0;
  aDeviceGuid[7] = 0;
  a3DGuid[4] = 0;
  a3DGuid[5] = 0;
  a3DGuid[6] = 0;
  a3DGuid[7] = 0;
  aDeviceGuid[8] = 0;
  aDeviceGuid[9] = 0;
  aDeviceGuid[10] = 0;
  aDeviceGuid[0xb] = 0;
  a3DGuid[8] = 0;
  a3DGuid[9] = 0;
  a3DGuid[10] = 0;
  a3DGuid[0xb] = 0;
  aDeviceGuid[0xc] = 0;
  aDeviceGuid[0xd] = 0;
  aDeviceGuid[0xe] = 0;
  aDeviceGuid[0xf] = 0;
  a3DGuid[0xc] = 0;
  a3DGuid[0xd] = 0;
  a3DGuid[0xe] = 0;
  a3DGuid[0xf] = 0;
  Reg_GetBinary(s_LastDisplayDevice_004dd738,aDeviceGuid,0x10);
  Reg_GetBinary(s_Last3DDevice_004dd794,a3DGuid,0x10);
  uVar2 = 0;
  if (g_dwStdDisplay_numDevices != 0) {
    pbVar6 = &DAT_00902ee8;
    do {
      iVar1 = 0x10;
      bVar9 = true;
      pbVar7 = pbVar6;
      pbVar8 = aDeviceGuid;
      do {
        if (iVar1 == 0) break;
        iVar1 = iVar1 + -1;
        bVar9 = *pbVar7 == *pbVar8;
        pbVar7 = pbVar7 + 1;
        pbVar8 = pbVar8 + 1;
      } while (bVar9);
      if (bVar9) break;
      uVar2 = uVar2 + 1;
      pbVar6 = pbVar6 + 0x298;
    } while (uVar2 < g_dwStdDisplay_numDevices);
  }
  if (uVar2 == g_dwStdDisplay_numDevices) {
    OutputDebugStringA(((unsigned)(uintptr_t)&DAT_004dd838));
    return 0;
  }
  *deviceIdx = uVar2;
  puVar3 = (uint *)(uVar2 * 0x10 + (int)g_pDisplayModes);
  uVar2 = Display_FindClosestMode((VideoMode *)&UINT_004f4d38,(VideoMode *)puVar3[1],*puVar3);
  *modeIdx = uVar2;
  iVar1 = 0x10;
  bVar9 = true;
  pbVar6 = a3DGuid;
  pbVar7 = aNullGuid;
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar9 = *pbVar6 == *pbVar7;
    pbVar6 = pbVar6 + 1;
    pbVar7 = pbVar7 + 1;
  } while (bVar9);
  if (bVar9) {
    *threeDIdx = 0xffffffff;
    return 1;
  }
  pvVar4 = (void *)((int)g_pDisplayModes + *deviceIdx * 0x10);
  uVar2 = 0;
  if (*(int *)((int)pvVar4 + 8) != 0) {
    iVar1 = 0;
    do {
      iVar5 = 0x10;
      bVar9 = true;
      pbVar6 = (byte *)(*(int *)((int)pvVar4 + 0xc) + 0x21c + iVar1);
      pbVar7 = a3DGuid;
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        bVar9 = *pbVar6 == *pbVar7;
        pbVar6 = pbVar6 + 1;
        pbVar7 = pbVar7 + 1;
      } while (bVar9);
      if (bVar9) break;
      pvVar4 = (void *)((int)g_pDisplayModes + *deviceIdx * 0x10);
      uVar2 = uVar2 + 1;
      iVar1 = iVar1 + 0x22c;
    } while (uVar2 < *(uint *)((int)pvVar4 + 8));
  }
  if (uVar2 == *(uint *)(*deviceIdx * 0x10 + 8 + (int)g_pDisplayModes)) {
    OutputDebugStringA(((unsigned)(uintptr_t)&DAT_004dd800));
    return 0;
  }
  *threeDIdx = uVar2;
  return 1;
}

/* ---- 0x00402b60  Display_PickDefault ---- */
int __cdecl
Display_PickDefault(int wantFullscreen,int want3D,int *deviceIdx,int *modeIdx,int *threeDIdx)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  local_8 = (uint)(want3D == 0);
  local_4 = (uint)(wantFullscreen == 0);
  local_10 = UINT_004dd33c;
  local_14 = (uint)(wantFullscreen == 0);
  local_c = want3D;
  uVar1 = Display_FindClosestDevice(&local_14);
  *deviceIdx = uVar1;
  puVar2 = (uint *)(uVar1 * 0x10 + (int)g_pDisplayModes);
  uVar1 = Display_FindClosestMode((VideoMode *)&UINT_004f4d38,(VideoMode *)puVar2[1],*puVar2);
  *modeIdx = uVar1;
  uVar1 = *(uint *)((int)g_pDisplayModes + *deviceIdx * 0x10 + 8);
  if ((uVar1 == 0) || (want3D == 0)) {
    *threeDIdx = -1;
  }
  else {
    uVar1 = D3D_FindClosestDriver
                      ((int *)&UINT_004f44e8,
                       *(int *)((int)g_pDisplayModes + *deviceIdx * 0x10 + 0xc),uVar1);
    *threeDIdx = uVar1;
    if (*(int *)(*(int *)(*deviceIdx * 0x10 + 0xc + (int)g_pDisplayModes) + uVar1 * 0x22c) == 0) {
      *threeDIdx = -1;
      return 1;
    }
  }
  return 1;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004730d0  stdDisplay_BuildBitmapInfo8 ---- */
/* Fills a BITMAPINFO (0x28 header, negative height) with a 256-entry palette */

void __cdecl stdDisplay_BuildBitmapInfo8(int info,uint width,int height,int bpp,undefined1 *palette)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  BitmapInfoHeader header;
  uint aPalette [256];
  
  header.nHeight = -height;
  header.nWidth = width;
  header.dwSize = 0x28;
  header.wPlanes = 1;
  header.wBitCount = 8;
  header.dwCompression = 0;
  header.dwSizeImage = 0;
  header.nXPelsPerMeter = 0;
  header.nYPelsPerMeter = 0;
  header.dwClrUsed = 0;
  header.dwClrImportant = 0;
  iVar3 = 0x100;
  puVar2 = (undefined1 *)((int)aPalette + 1);
  do {
    puVar2[1] = *palette;
    puVar1 = palette + 2;
    *puVar2 = palette[1];
    palette = palette + 3;
    puVar2[-1] = *puVar1;
    puVar2[2] = 0;
    iVar3 = iVar3 + -1;
    puVar2 = puVar2 + 4;
  } while (iVar3 != 0);
  CreateDIBSection(info,(int)&header,0,bpp,0,0);
  return;
}

/* ---- 0x00473180  stdDisplay_BuildBitmapInfo16 ---- */
void __cdecl stdDisplay_BuildBitmapInfo16(int info,uint width,int height,int bpp)

{
  BitmapInfoHeader header;
  
  header.nWidth = width;
  header.dwSize = 0x28;
  header.nHeight = -height;
  header.dwCompression = 0;
  header.dwSizeImage = 0;
  header.nXPelsPerMeter = 0;
  header.nYPelsPerMeter = 0;
  header.dwClrUsed = 0;
  header.dwClrImportant = 0;
  header.wPlanes = 1;
  header.wBitCount = 0x10;
  CreateDIBSection(info,(int)&header,0,bpp,0,0);
  return;
}

/* ---- 0x004731f0  DIB_CreateSection565 ---- */
/* CreateDIBSection of a top-down 16-bit surface with the RGB565 bit masks (0xf800, 0x7e0, 0x1f). */

undefined * __cdecl DIB_CreateSection565(uint hdc,uint width,int height,uint outBits)

{
  undefined *puVar1;
  BitmapInfoHeader header;
  uint aMasks [3];
  
  header.nWidth = width;
  header.dwSize = 0x28;
  header.nHeight = -height;
  header.dwSizeImage = 0;
  header.nXPelsPerMeter = 0;
  header.nYPelsPerMeter = 0;
  header.dwClrUsed = 0;
  header.dwClrImportant = 0;
  header.wPlanes = 1;
  header.wBitCount = 0x10;
  header.dwCompression = 3;
  puVar1 = (undefined *)CreateDIBSection(hdc,(int)&header,0,outBits,0,0);
  return puVar1;
}

/* ---- 0x00473270  Palette_SwapRedBlue ---- */
/* Converts a 768-byte RGB palette to BGR order */

uint __cdecl Palette_SwapRedBlue(int count,undefined1 *palette)

{
  unsigned char _frame[0x820] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  int a2;
  int iVar4;
  #define uStack_808 (*(undefined2 *)(_frame + (0x820 - 0x808)))
  #define uStack_806 (*(undefined2 *)(_frame + (0x820 - 0x806)))
  #define auStack_800 (*(undefined1 (*)[1024])(_frame + (0x820 - 0x800)))
  #define local_400 (*(undefined1 (*)[1024])(_frame + (0x820 - 0x400)))
  
  iVar4 = 0x100;
  puVar2 = palette;
  puVar3 = local_400 + 1;
  do {
    puVar3[1] = *puVar2;
    puVar1 = puVar2 + 2;
    *puVar3 = puVar2[1];
    puVar2 = puVar2 + 3;
    puVar3[-1] = *puVar1;
    puVar3[2] = 0;
    iVar4 = iVar4 + -1;
    puVar3 = puVar3 + 4;
  } while (iVar4 != 0);
  iVar4 = SetDIBColorTable(count,0,0x100,(int)local_400);
  if (iVar4 == 0) {
    return 0;
  }
  uStack_808 = 0x300;
  uStack_806 = 0x100;
  iVar4 = 0x100;
  puVar2 = auStack_800 + 1;
  do {
    puVar2[-1] = *palette;
    puVar3 = palette + 2;
    *puVar2 = palette[1];
    palette = palette + 3;
    puVar2[1] = *puVar3;
    puVar2[2] = 1;
    iVar4 = iVar4 + -1;
    puVar2 = puVar2 + 4;
  } while (iVar4 != 0);
  iVar4 = CreatePalette((int)&uStack_808);
  a2 = SelectPalette(count,iVar4,1);
  AnimatePalette(iVar4,0,0x100,(int)auStack_800);
  RealizePalette(count);
  SelectPalette(count,a2,0);
  DeleteObject(iVar4);
  return 1;
}
#undef auStack_800
#undef local_400
#undef uStack_806
#undef uStack_808


/* ---- 0x00473a40  stdDisplay_Startup ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Adds the 'Window Display Device' (DIBsection windowed) entry then DirectDrawEnumerate adds the
   DirectDraw devices Original name stdDisplay_Startup (the remaster's GrimFandango (Linux):
   strings: 'Window Display Device' | 'DIBsection windowed display'); was Display_EnumDevices. */

int __cdecl stdDisplay_Startup(void)

{
  int iVar1;
  
  _DAT_00902ee8 = 0x92a69f00;
  _g_bStdDisplay_Startup = 1;
  g_dwStdDisplay_numDevices = 0;
  _DAT_00902eec = 0x11d113fa;
  _DAT_00902ef0 = 0xa000c097;
  _DAT_00902ef4 = 0x5302924;
  strncpy((uint *)&DAT_00902c60,(uint *)s_Window_Display_Device_004de9f8,0x7f);
  iVar1 = g_dwStdDisplay_numDevices * 0x298;
  (&DAT_00902cdf)[iVar1] = 0;
  strncpy((uint *)(&DAT_00902ce0 + iVar1),(uint *)s_DIBsection_windowed_display_004de9dc,0x7f);
  (&DAT_00902d5f)[g_dwStdDisplay_numDevices * 0x298] = 0;
  (&UINT_00902d60)[g_dwStdDisplay_numDevices * 0xa6] = 0;
  (&UINT_00902d64)[g_dwStdDisplay_numDevices * 0xa6] = 0;
  (&UINT_00902d68)[g_dwStdDisplay_numDevices * 0xa6] = 0;
  (&UINT_00902d6c)[g_dwStdDisplay_numDevices * 0xa6] = 1;
  (&UINT_00902d70)[g_dwStdDisplay_numDevices * 0xa6] = 0;
  (&UINT_00902d74)[g_dwStdDisplay_numDevices * 0xa6] = 2000000;
  (&UINT_00902d78)[g_dwStdDisplay_numDevices * 0xa6] = 2000000;
  g_dwStdDisplay_numDevices = g_dwStdDisplay_numDevices + 1;
  iVar1 = DirectDrawEnumerateA(((unsigned)(uintptr_t)stdDisplay_EnumDevicesCallback),0);
  return (uint)(iVar1 == 0);
}

/* ---- 0x00473b30  stdDisplay_Shutdown ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* IDirectDraw::RestoreDisplayMode when a DirectDraw device is active Original name
   stdDisplay_Shutdown (the remaster's GrimFandango (Linux): the call after the display close in
   Main_Shutdown in both builds; clears the stdDisplay startup flag (the remaster's is empty)); was
   Display_RestoreMode. */

void __cdecl stdDisplay_Shutdown(void)

{
  _g_bStdDisplay_Startup = 0;
  if ((g_pDisplayDevice->nType == 1) && (g_pDirectDraw != (void *)0x0)) {
    (**(code_std **)(*(int *)g_pDirectDraw + 0x4c))(g_pDirectDraw);
  }
  return;
}

/* ---- 0x00473c80  Display_SelectDevice ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl Display_SelectDevice(int deviceIdx)

{
  void *device;
  int iVar1;
  
  if (g_nDisplayDeviceOpen != 0) {
    return 0;
  }
  if (g_dwStdDisplay_numDevices <= (uint)deviceIdx) {
    return 0;
  }
  UINT_00901758 = deviceIdx;
  g_pDisplayDevice = (DisplayDevice *)(&DAT_00902c60 + deviceIdx * 0x298);
  if ((&UINT_00902d60)[deviceIdx * 0xa6] == 0) {
    _DAT_00901810 = 400;
    _DAT_00901814 = 400;
    _DAT_0090181c = 400;
    _DAT_00901820 = 400;
    _DAT_00901864 = 0x200;
    _DAT_00901870 = 0x200;
    _DAT_00901874 = 0x200;
    UINT_00901760 = 0;
    _DAT_00901768 = 0x140;
    _DAT_0090176c = 200;
    _DAT_00901770 = 64000;
    _DAT_00901774 = 0x140;
    _DAT_00901778 = 0x140;
    _DAT_0090177c = 0;
    _DAT_00901780 = 8;
    _DAT_00901784 = 0;
    _DAT_00901788 = 0;
    _DAT_0090178c = 0;
    _DAT_00901764 = 0x3f400000;
    _DAT_009017b4 = 0;
    _DAT_009017bc = 0x140;
    _DAT_009017c0 = 0xf0;
    _DAT_009017c4 = 0x12c00;
    _DAT_009017c8 = 0x140;
    _DAT_009017cc = 0x140;
    _DAT_009017d0 = 0;
    _DAT_009017d4 = 8;
    _DAT_009017d8 = 0;
    _DAT_009017dc = 0;
    _DAT_009017e0 = 0;
    _DAT_009017b8 = 0x3f800000;
    _DAT_00901808 = 0;
    _DAT_00901818 = 160000;
    _DAT_00901824 = 0;
    _DAT_00901828 = 8;
    _DAT_0090182c = 0;
    _DAT_00901830 = 0;
    _DAT_00901834 = 0;
    _DAT_0090180c = 0x3f800000;
    _DAT_0090185c = 0;
    _DAT_00901868 = 0x180;
    _DAT_0090186c = 0x30000;
    _DAT_00901878 = 0;
    _DAT_0090187c = 8;
    _DAT_00901880 = 0;
    _DAT_00901884 = 0;
    _DAT_00901888 = 0;
    _DAT_00901860 = 0x3f800000;
    _DAT_009018b0 = 0;
    _DAT_009018b8 = 0x280;
    _DAT_009018bc = 0x1e0;
    _DAT_009018c0 = 0x4b000;
    _DAT_009018c4 = 0x280;
    _DAT_009018c8 = 0x280;
    _DAT_009018cc = 0;
    _DAT_009018d0 = 8;
    _DAT_009018d4 = 0;
    _DAT_009018d8 = 0;
    _DAT_009018dc = 0;
    _DAT_009018b4 = 0x3f800000;
    _DAT_00901904 = 0;
    _DAT_0090190c = 0x400;
    _DAT_00901910 = 0x300;
    _DAT_00901914 = 0xc0000;
    _DAT_00901918 = 0x400;
    _DAT_0090191c = 0x400;
    _DAT_00901920 = 0;
    _DAT_00901924 = 8;
    _DAT_00901928 = 0;
    _DAT_0090192c = 0;
    _DAT_00901930 = 0;
    _DAT_00901908 = 0x3f800000;
    _DAT_00901958 = 0;
    _DAT_00901960 = 0x500;
    _DAT_00901964 = 0x400;
    _DAT_00901978 = 8;
    _DAT_009019b4 = 0x140;
    _DAT_009019c4 = 0x140;
    _DAT_00901968 = 0x140000;
    _DAT_0090196c = 0x500;
    _DAT_00901970 = 0x500;
    _DAT_00901974 = 0;
    _DAT_0090197c = 0;
    _DAT_00901980 = 0;
    _DAT_00901984 = 0;
    _DAT_0090195c = 0x3f800000;
    _DAT_009019ac = 0;
    _DAT_009019b8 = 0xf0;
    _DAT_009019bc = 0x25800;
    _DAT_009019c0 = 0x280;
    _DAT_009019c8 = 1;
    _DAT_009019cc = 0x10;
    _DAT_009019d0 = 5;
    _DAT_009019d4 = 5;
    _DAT_009019d8 = 5;
    _DAT_009019e8 = 3;
    _DAT_009019ec = 3;
    _DAT_009019f0 = 3;
    _DAT_009019dc = 10;
    _DAT_009019e0 = 5;
    _DAT_009019e4 = 0;
    _DAT_009019b0 = 0x3f800000;
    _DAT_00901a00 = 0;
    _DAT_00901a08 = 0x280;
    _DAT_00901a0c = 0x1e0;
    _DAT_00901a10 = 0x96000;
    _DAT_00901a14 = 0x500;
    _DAT_00901a18 = 0x280;
    _DAT_00901a1c = 1;
    _DAT_00901a20 = 0x10;
    _DAT_00901a24 = 5;
    _DAT_00901a28 = 5;
    _DAT_00901a2c = 5;
    _DAT_00901a3c = 3;
    _DAT_00901a40 = 3;
    _DAT_00901a44 = 3;
    _DAT_00901a30 = 10;
    _DAT_00901a34 = 5;
    _DAT_00901a38 = 0;
    _DAT_00901a04 = 0x3f800000;
    _DAT_00901a54 = 0;
    _DAT_00901a5c = 0x280;
    _DAT_00901a60 = 0x1e0;
    _DAT_00901a64 = 0x96000;
    _DAT_00901a68 = 0x500;
    _DAT_00901a6c = 0x280;
    _DAT_00901a70 = 1;
    _DAT_00901a74 = 0x10;
    _DAT_00901a78 = 5;
    _DAT_00901a7c = 6;
    _DAT_00901a80 = 5;
    _DAT_00901a90 = 3;
    _DAT_00901a94 = 2;
    _DAT_00901a98 = 3;
    _DAT_00901a84 = 0xb;
    _DAT_00901a88 = 5;
    _DAT_00901a8c = 0;
    _DAT_00901a58 = 0x3f800000;
    g_dwVideoModeCount = 10;
  }
  else if ((&UINT_00902d60)[deviceIdx * 0xa6] == 1) {
    device = Win_GetMainHwnd();
    iVar1 = DDraw_Create((uint)device);
    if (iVar1 == 0) {
      return 0;
    }
  }
  qsort(&UINT_00901760,g_dwVideoModeCount,0x54,Display_CompareVideoModes);
  g_nDisplayDeviceOpen = 1;
  return 1;
}

/* ---- 0x00474100  stdDisplay_Close ---- */
/* Original name stdDisplay_Close (the remaster's GrimFandango (Linux): the device close after
   stdDisplay_ClearMode in both builds (if open: clear the mode if set, clear the open flag)); was
   Display_CloseDevice. */

void __cdecl stdDisplay_Close(void)

{
  if (g_nDisplayDeviceOpen != 0) {
    if (g_nDisplayModeOpen != 0) {
      stdDisplay_ClearMode();
    }
    if (g_pDisplayDevice->nType == 1) {
      DDraw_Release();
    }
    g_nDisplayDeviceOpen = 0;
  }
  return;
}

/* ---- 0x00474140  Display_OpenMode ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Stddisplay.c: selects the video mode, creates the primary and back surfaces (DIB section windowed
   or DirectDraw) and the Arial debug font */

int __cdecl Display_OpenMode(uint modeIdx,void *palette,int use3D)

{
  void *pvVar1;
  int iVar2;
  VideoMode *mode;
  byte *palette_00;
  
  if (g_dwVideoModeCount <= modeIdx) {
    return 0;
  }
  if (g_nDisplayModeOpen != 0) {
    stdDisplay_ClearMode();
  }
  UINT_00803f9c = use3D;
  UINT_0090175c = modeIdx;
  g_dwStdDisplay_numDrawBuffers = 1;
  g_pVideoMode = (VideoMode *)(&UINT_00901760 + modeIdx * 0x15);
  if (g_pDisplayDevice->nType == 0) {
    pvVar1 = Win_GetMainHwnd();
    pvVar1 = DIB_CreateSurface(g_pVideoMode,(VBuffer *)&UINT_007feae0,palette,pvVar1);
    if (pvVar1 == (void *)0x0) {
      return 0;
    }
    g_dwStdDisplay_frontBuffer = 0;
    _DAT_00901684 = 0;
    _DAT_00901688 = 0;
    Mem_Copy(&DAT_0090168c,&g_pVideoMode->format,0x4c);
    _DAT_009016d8 = palette;
    UINT_009016dc = UINT_007feae0;
    g_dwStdDisplay_backBuffer = 0;
    _DAT_009055e8 = 0;
    Mem_Copy(&UINT_009055ec,&g_pVideoMode->format,0x4c);
    _DAT_00905638 = palette;
    UINT_0090563c = UINT_007feae0;
  }
  else if (g_pDisplayDevice->nType == 1) {
    mode = g_pVideoMode;
    palette_00 = palette;
    pvVar1 = Win_GetMainHwnd();
    iVar2 = DDraw_CreateSurfaces(pvVar1,mode,palette_00);
    if (iVar2 == 0) {
      return 0;
    }
  }
  Surface_Fill((VBuffer *)&g_dwStdDisplay_backBuffer,0,(int *)0x0);
  stdDisplay_Update();
  if (use3D != 0) {
    Surface_Fill((VBuffer *)&g_dwStdDisplay_backBuffer,0,(int *)0x0);
  }
  stdDisplay_SetMasterPalette(palette);
  g_pDebugFont = (void *)CreateFontA((-(uint)((uint)(g_pVideoMode->format).nWidth < 0x280) &
                                     0xfffffff4) + 0x18,0,0,0,400,0,0,0,0,0,0,0,2,((unsigned)(uintptr_t)&s_Arial_004dea10));
  _DAT_007feac8 = 0;
  _DAT_007feacc = 0;
  _DAT_007fead0 = (g_pVideoMode->format).nWidth;
  _DAT_007fead4 = (g_pVideoMode->format).nHeight;
  g_nDisplayModeOpen = 1;
  return 1;
}

/* ---- 0x00474310  stdDisplay_ClearMode ---- */
/* Original name stdDisplay_ClearMode (the remaster's GrimFandango (Linux): the mode close of the
   display shutdown in both builds (if a mode is set and the device type at +0x100 is 0, release the
   front / back buffers; clear the mode flag)); was Display_CloseMode. */

void __cdecl stdDisplay_ClearMode(void)

{
  if (g_nDisplayModeOpen != 0) {
    if (g_pDisplayDevice->nType == 0) {
      UINT_009016dc = 0;
      UINT_0090563c = 0;
      Surface_Release((VBuffer *)&g_dwStdDisplay_frontBuffer);
      Surface_Release((VBuffer *)&g_dwStdDisplay_backBuffer);
      DIB_ReleaseSurface();
    }
    else if (g_pDisplayDevice->nType == 1) {
      DDraw_ReleaseSurfaces();
    }
  }
  if (g_pDebugFont != (void *)0x0) {
    DeleteObject((int)g_pDebugFont);
    g_pDebugFont = (void *)0x0;
  }
  g_nDisplayModeOpen = 0;
  return;
}

/* ---- 0x00474380  Display_SuspendForDialog ---- */
void __cdecl Display_SuspendForDialog(void)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (((g_nDisplayDeviceOpen != 0) && (g_nDisplayModeOpen != 0)) && (g_pDisplayDevice->nType == 1))
  {
    uVar3 = 8;
    iVar2 = *(int *)g_pDirectDraw;
    pvVar1 = Win_GetMainHwnd();
    iVar2 = (**(code_std **)(iVar2 + 0x50))(g_pDirectDraw,pvVar1,uVar3);
    if (iVar2 == 0) {
      (**(code_std **)(*(int *)g_pDirectDraw + 0x28))(g_pDirectDraw);
    }
  }
  return;
}

/* ---- 0x004743d0  Display_ResumeAfterDialog ---- */
void __cdecl Display_ResumeAfterDialog(void)

{
  void *pvVar1;
  int iVar2;
  uint uVar3;
  
  if (((g_nDisplayDeviceOpen != 0) && (g_nDisplayModeOpen != 0)) && (g_pDisplayDevice->nType == 1))
  {
    iVar2 = *(int *)g_pDirectDraw;
    uVar3 = UINT_00803fb0;
    pvVar1 = Win_GetMainHwnd();
    iVar2 = (**(code_std **)(iVar2 + 0x50))(g_pDirectDraw,pvVar1,uVar3);
    if (iVar2 == 0) {
      std3D_PurgeTextureCache();
    }
  }
  return;
}

/* ---- 0x00474420  stdDisplay_Update ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* BitBlt of the DIB back buffer or DirectDraw flip Original name stdDisplay_Update (the remaster's
   GrimFandango (Linux): the page-flip callback of Main_Startup (the remaster's is the platform
   rewrite)); was Display_Flip. */

int __cdecl stdDisplay_Update(void)

{
  int iVar1;
  uint uVar2;
  
  if (g_pDisplayDevice->nType == 0) {
    GdiFlush();
    BitBlt(UINT_00803f7c,0,0,(g_pVideoMode->format).nWidth,(g_pVideoMode->format).nHeight,
           UINT_007f6498,0,0,0xcc0020);
  }
  else {
    iVar1 = g_pDisplayDevice->nType + -1;
    if (iVar1 != 0) {
      return iVar1;
    }
    if (UINT_00803f9c != 0) {
      uVar2 = DDraw_Flip();
      return uVar2;
    }
  }
  return 1;
}
#endif


/* ---- 0x00474480  stdDisplay_VBufferNew ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Std/Win95/Stddisplay.c: creates a surface record (0xd8 bytes) from a 19-dword format/size
   description Original name stdDisplay_VBufferNew (the remaster's GrimFandango (Linux): aligned
   call in rdMaterial_LoadEntry, stdBmp_LoadEntry, stdPic_LoadEntry); was Surface_Create. */

VBuffer * __cdecl stdDisplay_VBufferNew(VBufferFormat *format,int videoMem,int b,int c)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[1072] __attribute__((aligned(16)));  /* the original frame below the return address */
  DDSurfaceDesc *pDVar1;
  void **ppvVar2;
  undefined1 uVar3;
  int *piVar4;
  VBuffer *pVVar5;
  uint uVar6;
  void *pvVar7;
  int iVar8;
  undefined1 *puVar9;
  uint uVar10;
  DDSurfaceDesc *pDVar11;
  #define puStack_8 (*(undefined1 **)(_frame + (0x20 - 0x8)))
  
  pVVar5 = (VBuffer *)
           (*g_pStd_HS->pAlloc)
                     (0xd8,s_C__grimjedi_Libs_Std_Win95_Stddi_004dea18,_DAT_004de1d0 + 0xd);
  if (pVVar5 == (VBuffer *)0x0) {
    return (VBuffer *)0x0;
  }
  pVVar5->pPalette = (void *)c;
  pVVar5->pPixels = (void *)0x0;
  pVVar5->nLockCount = 0;
  Mem_Copy(&pVVar5->format,format,0x4c);
  iVar8 = (pVVar5->format).nWidth;
  uVar10 = (uint)(pVVar5->format).colorFormat.nBpp >> 3;
  uVar6 = uVar10 * iVar8;
  (pVVar5->format).nPitch = uVar6;
  pVVar5->dwColorKey = 0;
  (pVVar5->format).nStride = uVar6 / uVar10;
  uVar6 = uVar10 * iVar8 * (pVVar5->format).nHeight;
  (pVVar5->format).dwSize = uVar6;
  if (((videoMem == 0) || (g_nDisplayDeviceOpen == 0)) || (g_pDisplayDevice->nType != 1)) {
    pVVar5->nType = 0;
    pVVar5->nVideoMemory = 0;
    pvVar7 = (void *)(*g_pStd_HS->pAlloc)
                               (uVar6,s_C__grimjedi_Libs_Std_Win95_Stddi_004dea18,
                                _DAT_004de1d0 + 0x2a);
    pVVar5->pPixels = pvVar7;
    if (pvVar7 == (void *)0x0) {
      return (VBuffer *)0x0;
    }
    pVVar5->nLockCount = 1;
  }
  else {
    pVVar5->nVideoMemory = 0;
    pDVar1 = &(pVVar5->ddraw).desc;
    pVVar5->nType = 1;
    pDVar11 = pDVar1;
    for (iVar8 = 0x1b; iVar8 != 0; iVar8 = iVar8 + -1) {
      pDVar11->dwSize = 0;
      pDVar11 = (DDSurfaceDesc *)&pDVar11->dwFlags;
    }
    pDVar1->dwSize = 0x6c;
    (pVVar5->ddraw).desc.dwFlags = 7;
    (pVVar5->ddraw).desc.dwCaps = 0x40;
    if (b == 0) {
      (pVVar5->ddraw).desc.dwCaps = 0x840;
    }
    (pVVar5->ddraw).desc.dwWidth = (pVVar5->format).nWidth;
    (pVVar5->ddraw).desc.dwHeight = (pVVar5->format).nHeight;
    iVar8 = (**(code_std **)(*(int *)g_pDirectDraw + 0x18))(g_pDirectDraw,pDVar1);
    if (iVar8 != 0) {
      return (VBuffer *)0x0;
    }
    piVar4 = (pVVar5->ddraw).pSurface;
    iVar8 = (**(code_std **)(*piVar4 + 0x58))(piVar4,&(pVVar5->ddraw).desc);
    if (iVar8 != 0) {
      return (VBuffer *)0x0;
    }
    if (((pVVar5->ddraw).desc.dwCaps & 0x4000) != 0) {
      pVVar5->nVideoMemory = 1;
    }
    uVar6 = (pVVar5->ddraw).desc.nPitch;
    (pVVar5->format).nPitch = uVar6;
    (pVVar5->format).nStride = uVar6 / uVar10;
    if (puStack_8 == (undefined1 *)0x0) {
      (pVVar5->ddraw).pPalette = (void *)0x0;
      return pVVar5;
    }
    iVar8 = 0xfe;
    puVar9 = (_stkneg + 28);
    do {
      uVar3 = puStack_8[3];
      puVar9[3] = 1;
      *puVar9 = uVar3;
      puVar9[1] = puStack_8[4];
      puVar9[2] = puStack_8[5];
      iVar8 = iVar8 + -1;
      puVar9 = puVar9 + 4;
      puStack_8 = puStack_8 + 3;
    } while (iVar8 != 0);
    ppvVar2 = &(pVVar5->ddraw).pPalette;
    iVar8 = (**(code_std **)(*(int *)g_pDirectDraw + 0x14))
                      (g_pDirectDraw,0xc,(_stkneg + 24),ppvVar2,0);
    if (iVar8 != 0) {
      return (VBuffer *)0x0;
    }
    piVar4 = (pVVar5->ddraw).pSurface;
    iVar8 = (**(code_std **)(*piVar4 + 0x7c))(piVar4,*ppvVar2);
    if (iVar8 != 0) {
      return (VBuffer *)0x0;
    }
  }
  return pVVar5;
}
#undef puStack_8

#endif


/* ---- 0x004746d0  stdDisplay_VBufferFree ---- */
/* Original name stdDisplay_VBufferFree (the remaster's GrimFandango (Linux): aligned call in
   sputLua_FreeImage, sputRender_Close, stdDisplay_VBufferConvertColorFormat); was Surface_Free. */

void __cdecl stdDisplay_VBufferFree(VBuffer *surface)

{
  if (surface != (VBuffer *)0x0) {
    Surface_Release(surface);
    (*g_pStd_HS->pFree)(surface);
  }
  return;
}

/* ---- 0x004746f0  Surface_Release ---- */
/* Releases DirectDraw surfaces (type 1) or frees the system memory pixels (types 0/2) */

void __cdecl Surface_Release(VBuffer *surface)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = surface->nType;
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      piVar2 = (surface->ddraw).pSurface;
      if (piVar2 != (int *)0x0) {
        (**(code_std **)(*piVar2 + 8))(piVar2);
        (surface->ddraw).pSurface = (void *)0x0;
      }
      piVar2 = (surface->ddraw).pPalette;
      if (piVar2 == (int *)0x0) {
        return;
      }
      (**(code_std **)(*piVar2 + 8))(piVar2);
      (surface->ddraw).pPalette = (void *)0x0;
      return;
    }
    if (iVar1 != 2) {
      return;
    }
  }
  if (surface->pPixels != (void *)0x0) {
    (*g_pStd_HS->pFree)(surface->pPixels);
    surface->pPixels = (void *)0x0;
  }
  return;
}

/* ---- 0x00474750  stdDisplay_VBufferLock ---- */
/* Original name stdDisplay_VBufferLock (the remaster's GrimFandango (Linux): aligned call in
   rdMaterial_LoadEntry, stdBmp_LoadEntry, stdPic_LoadEntry); was Surface_Lock. */

int __cdecl stdDisplay_VBufferLock(VBuffer *surface)

{
  uint uVar1;
  uint uVar2;
  void *pvVar3;
  
  if (surface->nType != 0) {
    if (surface->nType != 1) {
      return 1;
    }
    uVar1 = (surface->ddraw).desc.dwCaps;
    if (((uVar1 & 0x20) != 0) && ((uVar1 & 0x200000) != 0)) {
      return 0;
    }
    pvVar3 = (void *)DDraw_LockSurface(&surface->ddraw);
    uVar1 = (surface->format).colorFormat.nBpp;
    uVar2 = (surface->ddraw).desc.nPitch;
    (surface->format).nPitch = uVar2;
    surface->pPixels = pvVar3;
    (surface->format).nStride = uVar2 / (uVar1 >> 3);
    if (pvVar3 == (void *)0x0) {
      return 0;
    }
  }
  surface->nLockCount = surface->nLockCount + 1;
  return 1;
}

/* ---- 0x004747b0  stdDisplay_VBufferUnlock ---- */
/* Original name stdDisplay_VBufferUnlock (the remaster's GrimFandango (Linux): aligned call in
   rdMaterial_LoadEntry, stdBmp_LoadEntry, stdPic_LoadEntry); was Surface_Unlock. */

int __cdecl stdDisplay_VBufferUnlock(VBuffer *surface)

{
  uint uVar1;
  
  if (surface->nType == 0) {
    if (surface->nLockCount != 0) {
      surface->nLockCount = surface->nLockCount + -1;
    }
  }
  else if (surface->nType == 1) {
    if (surface->nLockCount == 0) {
      return (int)surface;
    }
    uVar1 = DDraw_UnlockSurface(&surface->ddraw);
    if (uVar1 == 0) {
      return 0;
    }
    surface->nLockCount = surface->nLockCount + -1;
    return uVar1;
  }
  return 1;
}

/* ---- 0x00474800  Surface_Fill ---- */
int __cdecl Surface_Fill(VBuffer *surface,int color,int *rect)

{
  undefined1 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 *puVar8;
  uint local_8;
  
  if (surface->nType == 0) {
    iVar3 = (surface->format).colorFormat.nBpp;
    if (iVar3 == 8) {
      uVar1 = (undefined1)color;
      if (rect == (int *)0x0) {
        uVar2 = (surface->format).dwSize;
        puVar6 = surface->pPixels;
        for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar6 = CONCAT22(CONCAT11(uVar1,uVar1),CONCAT11(uVar1,uVar1));
          puVar6 = puVar6 + 1;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *(undefined1 *)puVar6 = uVar1;
          puVar6 = (undefined4 *)((int)puVar6 + 1);
        }
        return 1;
      }
      local_8 = 0;
      puVar6 = (undefined4 *)((int)surface->pPixels + *rect + (surface->format).nStride * rect[1]);
      if (0 < rect[3]) {
        do {
          uVar2 = rect[2];
          puVar8 = puVar6;
          for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
            *puVar8 = CONCAT22(CONCAT11(uVar1,uVar1),CONCAT11(uVar1,uVar1));
            puVar8 = puVar8 + 1;
          }
          for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *(undefined1 *)puVar8 = uVar1;
            puVar8 = (undefined4 *)((int)puVar8 + 1);
          }
          puVar6 = (undefined4 *)((int)puVar6 + (surface->format).nPitch);
          local_8 = local_8 + 1;
        } while ((int)local_8 < rect[3]);
      }
    }
    else if (iVar3 == 0x10) {
      if (rect == (int *)0x0) {
        uVar2 = (surface->format).dwSize;
        puVar6 = surface->pPixels;
        uVar4 = uVar2 >> 1;
        if ((uVar4 & 1) == 0) {
          for (uVar2 = uVar2 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar6 = CONCAT22((undefined2)color,(undefined2)color);
            puVar6 = puVar6 + 1;
          }
        }
        else {
          for (; uVar4 != 0; uVar4 = uVar4 - 1) {
            *(undefined2 *)puVar6 = (undefined2)color;
            puVar6 = (undefined4 *)((int)puVar6 + 2);
          }
        }
        return 1;
      }
      local_8 = 0;
      puVar6 = (undefined4 *)
               ((int)surface->pPixels + ((surface->format).nStride * rect[1] + *rect) * 2);
      if (0 < rect[3]) {
        do {
          uVar2 = rect[2];
          puVar8 = puVar6;
          if ((uVar2 & 1) == 0) {
            for (uVar2 = uVar2 >> 1; uVar2 != 0; uVar2 = uVar2 - 1) {
              *puVar8 = CONCAT22((undefined2)color,(undefined2)color);
              puVar8 = puVar8 + 1;
            }
          }
          else {
            for (; uVar2 != 0; uVar2 = uVar2 - 1) {
              *(undefined2 *)puVar8 = (undefined2)color;
              puVar8 = (undefined4 *)((int)puVar8 + 2);
            }
          }
          puVar6 = (undefined4 *)((int)puVar6 + (surface->format).nPitch);
          local_8 = local_8 + 1;
        } while ((int)local_8 < rect[3]);
        return 1;
      }
    }
    else if (iVar3 == 0x20) {
      if (rect == (int *)0x0) {
        piVar5 = surface->pPixels;
        for (uVar2 = (surface->format).dwSize >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
          *piVar5 = color;
          piVar5 = piVar5 + 1;
        }
        return 1;
      }
      local_8 = 0;
      piVar5 = (int *)((int)surface->pPixels + ((surface->format).nStride * rect[1] + *rect) * 4);
      if (0 < rect[3]) {
        do {
          piVar7 = piVar5;
          for (iVar3 = rect[2]; iVar3 != 0; iVar3 = iVar3 + -1) {
            *piVar7 = color;
            piVar7 = piVar7 + 1;
          }
          piVar5 = (int *)((int)piVar5 + (surface->format).nPitch);
          local_8 = local_8 + 1;
        } while ((int)local_8 < rect[3]);
        return 1;
      }
    }
  }
  else if (surface->nType == 1) {
    uVar2 = (surface->ddraw).desc.dwCaps;
    if (((uVar2 & 0x20) != 0) && ((uVar2 & 0x200000) != 0)) {
      return 0;
    }
    uVar2 = DDraw_FillSurface(&surface->ddraw,color,(uint *)rect);
    return uVar2;
  }
  return 1;
}

/* ---- 0x00474a60  Surface_Blit ---- */
int __cdecl Surface_Blit(VBuffer *dst,VBuffer *src,int x,int y,int *srcRect,int colorKey)

{
  if (src->nType != 0) {
    if (dst->nType == 1) {
      Surface_BlitDDraw(dst,src,x,y,(uint *)srcRect,(byte)colorKey);
      return 1;
    }
    Surface_BlitLockedDst(dst,src,(void *)x,y,srcRect,(void *)colorKey);
    return 1;
  }
  if (dst->nType == 0) {
    Surface_BlitSoftware(dst,src,x,y,srcRect,colorKey);
    return 1;
  }
  Surface_BlitLockedSrc(dst,src,(void *)x,y,srcRect,(void *)colorKey);
  return 1;
}

/* ---- 0x00474ae0  stdDisplay_VBufferSetColorKey ---- */
/* Original name stdDisplay_VBufferSetColorKey (the remaster's GrimFandango (Linux): aligned call in
   rdMaterial_LoadEntry, stdBitmap_ConvertColorFormat); was Surface_SetColorKey. */

int __cdecl stdDisplay_VBufferSetColorKey(VBuffer *surface,int color)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (surface->nType == 0) {
    surface->dwColorKey = color;
  }
  else if (surface->nType == 1) {
    local_8 = color;
    local_4 = color;
    piVar1 = (surface->ddraw).pSurface;
    (**(code_std **)(*piVar1 + 0x74))(piVar1,8,&local_8);
    return 1;
  }
  return 1;
}
#undef local_4
#undef local_8


/* ---- 0x00474b30  stdDisplay_VBufferDeCompress ---- */
/* Turns a type 2 (LZSS compressed) surface into a plain system memory surface Original name
   stdDisplay_VBufferDeCompress (the remaster's GrimFandango (Linux): aligned call in
   stdBitmap_DeCompress); was Surface_Decompress. */

void __cdecl stdDisplay_VBufferDeCompress(VBuffer *surface)

{
  void *dst;
  uint uVar1;
  
  if (surface->nType == 2) {
    dst = (void *)(*g_pStd_HS->pAlloc)
                            ((surface->format).nPitch * (surface->format).nHeight,
                             s_C__grimjedi_Libs_Std_Win95_Stddi_004dea18,DAT_004de1d8 + 0xc);
    if (dst != (void *)0x0) {
      uVar1 = LzssDecompress(dst,surface->pPixels,(surface->format).dwSize);
      (*g_pStd_HS->pFree)(surface->pPixels);
      (surface->format).dwSize = uVar1;
      surface->nType = 0;
      surface->pPixels = dst;
    }
  }
  return;
}

/* ---- 0x00474ba0  stdDisplay_VBufferDeCompressTo ---- */
/* Original name stdDisplay_VBufferDeCompressTo (the remaster's GrimFandango (Linux): aligned call
   in sputRender_Decompress, sputRender_UseSetup); was Surface_CopyConvert. */

int __cdecl stdDisplay_VBufferDeCompressTo(VBuffer *src,VBuffer *dst)

{
  int iVar1;
  
  stdDisplay_VBufferLock(dst);
  LzssDecompress(dst->pPixels,src->pPixels,(src->format).dwSize);
  iVar1 = stdDisplay_VBufferUnlock(dst);
  return iVar1;
}

/* ---- 0x00474be0  stdDisplay_VBufferConvertColorFormat ---- */
/* Original name stdDisplay_VBufferConvertColorFormat (the remaster's GrimFandango (Linux): aligned
   call in stdBitmap_ConvertColorFormat); was Surface_CreateFromBitmap. */

VBuffer * __cdecl stdDisplay_VBufferConvertColorFormat(ColorFormat *want,VBuffer *buffer)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  VBuffer *surface;
  int iVar2;
  ColorFormat *pCVar3;
  VBufferFormat *pVVar4;
  ColorFormat *pCVar5;
  ColorFormat *pCVar6;
  VBufferFormat *pVVar7;
  bool bVar8;
  #define local_4c (*(VBufferFormat *)(_frame + (0x60 - 0x4c)))
  
  iVar2 = 0x38;
  pCVar5 = &(buffer->format).colorFormat;
  bVar8 = true;
  pCVar3 = want;
  pCVar6 = pCVar5;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar8 = (char)pCVar3->nColorMode == (char)pCVar6->nColorMode;
    pCVar3 = (ColorFormat *)((int)&pCVar3->nColorMode + 1);
    pCVar6 = (ColorFormat *)((int)&pCVar6->nColorMode + 1);
  } while (bVar8);
  if (bVar8) {
    return buffer;
  }
  if ((pCVar5->nColorMode == 0) && (want->nColorMode == 0)) {
    return buffer;
  }
  surface = buffer;
  if ((buffer->format).colorFormat.nBpp != want->nBpp) {
    pVVar4 = &buffer->format;
    pVVar7 = &local_4c;
    for (iVar2 = 0x13; iVar2 != 0; iVar2 = iVar2 + -1) {
      pVVar7->nWidth = pVVar4->nWidth;
      pVVar4 = (VBufferFormat *)&pVVar4->nHeight;
      pVVar7 = (VBufferFormat *)&pVVar7->nHeight;
    }
    pCVar5 = want;
    pCVar3 = &local_4c.colorFormat;
    for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
      pCVar3->nColorMode = pCVar5->nColorMode;
      pCVar5 = (ColorFormat *)&pCVar5->nBpp;
      pCVar3 = (ColorFormat *)&pCVar3->nBpp;
    }
    surface = stdDisplay_VBufferNew(&local_4c,0,0,0);
    if (surface == (VBuffer *)0x0) {
      return (VBuffer *)0x0;
    }
  }
  stdDisplay_VBufferLock(buffer);
  stdDisplay_VBufferLock(surface);
  iVar2 = 0;
  if (0 < (surface->format).nHeight) {
    do {
      stdColor_ColorConvertOneRow
                ((ushort *)(iVar2 * (surface->format).nPitch + (int)surface->pPixels),(int)want,
                 (ushort *)(iVar2 * (buffer->format).nPitch + (int)buffer->pPixels),
                 (int)&(buffer->format).colorFormat,(surface->format).nWidth);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (surface->format).nHeight);
  }
  stdDisplay_VBufferUnlock(buffer);
  stdDisplay_VBufferUnlock(surface);
  uVar1 = stdColor_ColorConvertOnePixel
                    ((int)want,buffer->dwColorKey,(int)&(buffer->format).colorFormat);
  surface->dwColorKey = uVar1;
  pCVar5 = &(surface->format).colorFormat;
  for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
    pCVar5->nColorMode = want->nColorMode;
    want = (ColorFormat *)&want->nBpp;
    pCVar5 = (ColorFormat *)&pCVar5->nBpp;
  }
  if (surface != buffer) {
    stdDisplay_VBufferFree(buffer);
  }
  return surface;
}
#undef local_4c


/* ---- 0x00474d10  stdDisplay_SetPalette ---- */
/* Original name stdDisplay_SetPalette (the remaster's GrimFandango (Linux): the first call of
   grimdemo_SetPalette; the remaster's is a stub); was Display_SetDIBPalette. */

int __cdecl stdDisplay_SetPalette(uint palette)

{
  int iVar1;
  uint uVar2;
  
  if ((g_pVideoMode->format).colorFormat.nColorMode != 0) {
    return 0;
  }
  if (g_pDisplayDevice->nType == 0) {
    uVar2 = Palette_SwapRedBlue(UINT_007f6498,(undefined1 *)palette);
    if (uVar2 == 0) {
      return 0;
    }
    GdiFlush();
    iVar1 = BitBlt(UINT_00803f7c,0,0,(g_pVideoMode->format).nWidth,(g_pVideoMode->format).nHeight,
                   UINT_007f6498,0,0,0xcc0020);
  }
  else {
    iVar1 = g_pDisplayDevice->nType + -1;
    if (iVar1 == 0) {
      uVar2 = DDraw_SetPalette((undefined1 *)palette);
      return uVar2;
    }
  }
  return iVar1;
}

/* ---- 0x00474d90  stdDisplay_SetMasterPalette ---- */
/* Original name stdDisplay_SetMasterPalette (the remaster's GrimFandango (Linux): the second call
   of grimdemo_SetPalette; the remaster's is a stub); was Display_SetPalette. */

void __cdecl stdDisplay_SetMasterPalette(void *palette)

{
  Mem_Copy(&DAT_007fa7b8,palette,0x300);
  Palette_ApplyGamma(&DAT_007f64a0,&DAT_007fa7b8,0x100,UINT_00803fb8);
  return;
}

/* ---- 0x00474dd0  Palette_ApplyGamma ---- */
int __cdecl Palette_ApplyGamma(void *dst,void *src,int count,int gammaIdx)

{
  if (PTR_00803fc0 == (double *)0x0) {
    Mem_Copy(dst,src,0x300);
    return 0;
  }
  if (gammaIdx != 0) {
    Palette_FromFloatTable
              (dst,src,0x100,
               PUN(double,CONCAT44(*(undefined4 *)((int)PTR_00803fc0 + gammaIdx * 8 + -4),
                                *(undefined4 *)(PTR_00803fc0 + gammaIdx + -1))));
    return 1;
  }
  Mem_Copy(dst,src,0x300);
  return 1;
}

/* ---- 0x00474e40  stdDisplay_TextOut ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* GDI TextOut of the debug font onto the back buffer (DIB or locked DirectDraw DC)
   Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
   Original name stdDisplay_TextOut (the remaster's GrimFandango (Linux): aligned call in
   Main_Service); was Display_DrawText. */

int __cdecl stdDisplay_TextOut(char *text,int x,int y)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  int unaff_ESI;
  char *pcVar4;
  int unaff_retaddr;
  #define local_4 (*(char **)(_frame + (0x20 - 0x4)))
  
  if (g_pDisplayDevice->nType == 0) {
    iVar2 = SelectObject(UINT_007f6498,(int)g_pDebugFont);
    SetBkMode(UINT_007f6498,1);
    SetTextColor(UINT_007f6498,0xffff);
    uVar3 = 0xffffffff;
    pcVar4 = text;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    TextOutA(UINT_007f6498,x,y,(int)text,~uVar3 - 1);
    SelectObject(UINT_007f6498,iVar2);
    return 1;
  }
  if (g_pDisplayDevice->nType == 1) {
    if (UINT_00803f9c == 0) {
      iVar2 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x44))
                        (g_pDDrawPrimary->pSurface,&local_4);
      if (iVar2 == 0) {
        SetBkMode(unaff_ESI,1);
        SelectObject(unaff_ESI,(int)g_pDebugFont);
        SetTextColor(unaff_ESI,0xffff);
        uVar3 = 0xffffffff;
        pcVar4 = local_4;
        do {
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          cVar1 = *pcVar4;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        TextOutA(unaff_ESI,unaff_retaddr,(int)text,(int)local_4,~uVar3 - 1);
        (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x68))(g_pDDrawPrimary->pSurface,unaff_ESI)
        ;
        return 1;
      }
    }
    else {
      iVar2 = (**(code_std **)(*(int *)g_pDDrawBack->pSurface + 0x44))(g_pDDrawBack->pSurface,&local_4);
      if (iVar2 == 0) {
        SetBkMode(unaff_ESI,1);
        SelectObject(unaff_ESI,(int)g_pDebugFont);
        SetTextColor(unaff_ESI,0xffff);
        uVar3 = 0xffffffff;
        pcVar4 = local_4;
        do {
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          cVar1 = *pcVar4;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        TextOutA(unaff_ESI,unaff_retaddr,(int)text,(int)local_4,~uVar3 - 1);
        (**(code_std **)(*(int *)g_pDDrawBack->pSurface + 0x68))(g_pDDrawBack->pSurface,unaff_ESI);
        return 1;
      }
    }
  }
  return 0;
}
#undef local_4

#endif


/* ---- 0x00475000  Display_FindClosestDevice ---- */
uint __cdecl Display_FindClosestDevice(uint *want)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint local_4;
  
  uVar1 = 0;
  if (g_dwStdDisplay_numDevices == 0) {
    return uVar1;
  }
  uVar4 = 0;
  local_4 = 0;
  if (g_dwStdDisplay_numDevices != 0) {
    puVar3 = &UINT_00902d60;
    do {
      uVar2 = 0;
      if ((((puVar3[4] == want[4]) && (uVar2 = 1, *puVar3 == *want)) &&
          (uVar2 = 2, puVar3[3] == want[3])) &&
         ((uVar2 = 3, puVar3[2] == want[2] && (uVar2 = 4, puVar3[1] == want[1])))) {
        return uVar1;
      }
      if (uVar4 < uVar2) {
        uVar4 = uVar2;
        local_4 = uVar1;
      }
      puVar3 = puVar3 + 0xa6;
      uVar1 = uVar1 + 1;
    } while (uVar1 < g_dwStdDisplay_numDevices);
  }
  return local_4;
}

/* ---- 0x00475090  Display_FindClosestMode ---- */
uint __cdecl Display_FindClosestMode(VideoMode *wanted,VideoMode *modes,uint count)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  uint local_4;
  
  uVar2 = 0;
  if (g_dwVideoModeCount == 0) {
    return uVar2;
  }
  uVar5 = 0;
  local_4 = 0;
  if (count != 0) {
    iVar1 = (wanted->format).colorFormat.nColorMode;
    piVar4 = &(modes->format).colorFormat.nBpp;
    do {
      uVar3 = 0;
      if ((((((ColorFormat *)(piVar4 + -1))->nColorMode == iVar1) &&
           (uVar3 = 1, *piVar4 == (wanted->format).colorFormat.nBpp)) &&
          (uVar3 = 2, piVar4[-6] == (wanted->format).nWidth)) &&
         (uVar3 = 3, piVar4[-5] == (wanted->format).nHeight)) {
        uVar3 = 4;
        if (iVar1 != 1) {
          return uVar2;
        }
        if (((piVar4[1] == (wanted->format).colorFormat.dwRedBits) &&
            (piVar4[2] == (wanted->format).colorFormat.dwGreenBits)) &&
           (piVar4[3] == (wanted->format).colorFormat.dwBlueBits)) {
          return uVar2;
        }
      }
      if (uVar5 < uVar3) {
        uVar5 = uVar3;
        local_4 = uVar2;
      }
      piVar4 = piVar4 + 0x15;
      uVar2 = uVar2 + 1;
    } while (uVar2 < count);
  }
  return local_4;
}

/* ---- 0x00475140  Display_CompareVideoModes ---- */
/* qsort comparator of Display_SelectDevice for the video mode list. */

int __cdecl Display_CompareVideoModes(VideoMode *a,VideoMode *b)

{
  int iVar1;
  int iVar2;
  
  if (a->nFullscreen == 0) {
    if (b->nFullscreen == 0) goto LAB_00475180;
  }
  else if (b->nFullscreen == 0) {
    return (-(uint)((a->format).nWidth != (b->format).nWidth) & 0xfffffffe) + 1;
  }
  if (a->nFullscreen == 0) {
    return (-(uint)((b->format).nWidth != (a->format).nWidth) & 2) - 1;
  }
LAB_00475180:
  iVar1 = (a->format).colorFormat.nBpp;
  iVar2 = (b->format).colorFormat.nBpp;
  if (iVar1 != iVar2) {
    return iVar1 - iVar2;
  }
  iVar1 = (a->format).nWidth;
  iVar2 = (b->format).nWidth;
  if (iVar1 != iVar2) {
    return iVar1 - iVar2;
  }
  return (a->format).nHeight - (b->format).nHeight;
}

/* ---- 0x004751b0  Surface_BlitSoftware ---- */
/* System memory blit for 8/16/24/32 bpp, with colour key when flags & 1 */

int __cdecl Surface_BlitSoftware(VBuffer *dst,VBuffer *src,uint x,uint y,int *srcRect,uint flags)

{
  int iVar1;
  VBuffer *pVVar2;
  int iVar3;
  uint *puVar4;
  short *psVar5;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  uint *puVar9;
  short *psVar10;
  char *pcVar11;
  uint uVar12;
  int iVar13;
  void *pvVar14;
  uint uVar15;
  int iVar16;
  
  pVVar2 = src;
  if (srcRect == (int *)0x0) {
    iVar13 = (src->format).nWidth;
    iVar7 = (src->format).nHeight;
    src = (VBuffer *)0x0;
    iVar3 = 0;
  }
  else {
    src = (VBuffer *)*srcRect;
    iVar3 = srcRect[1];
    iVar13 = srcRect[2];
    iVar7 = srcRect[3];
  }
  if (((((int)x < (dst->format).nWidth) && (iVar13 + x != 0)) && ((int)y < (dst->format).nHeight))
     && (iVar7 + y != 0)) {
    uVar12 = (iVar13 + x) - 1;
    uVar15 = (iVar7 + y) - 1;
    if ((int)y < 0) {
      iVar3 = iVar3 - y;
      y = 0;
    }
    uVar8 = (dst->format).nHeight;
    if (uVar8 <= uVar15) {
      uVar15 = uVar8 - 1;
    }
    if ((int)x < 0) {
      src = (VBuffer *)((int)src - x);
      x = 0;
    }
    uVar8 = (dst->format).nWidth;
    if (uVar8 <= uVar12) {
      uVar12 = uVar8 - 1;
    }
    iVar13 = (uVar12 - x) + 1;
    if (iVar13 != 0) {
      uVar8 = ((uint)(pVVar2->format).colorFormat.nBpp >> 3) * iVar13;
      switch((pVVar2->format).colorFormat.nBpp) {
      case 8:
        if ((flags & 1) == 0) {
          flags = (int)(iVar3 * (pVVar2->format).nStride + (int)pVVar2->pPixels) + (int)src;
          pvVar14 = (void *)((int)dst->pPixels + x + y * (dst->format).nStride);
          if (y <= uVar15) {
            iVar3 = (uVar15 - y) + 1;
            do {
              Mem_Copy(pvVar14,(void *)flags,uVar8);
              flags = flags + (pVVar2->format).nStride;
              pvVar14 = (void *)((int)pvVar14 + (dst->format).nStride);
              iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
          }
        }
        else {
          iVar7 = (pVVar2->format).nStride;
          iVar1 = (dst->format).nStride;
          pcVar6 = (char *)((int)(iVar3 * (pVVar2->format).nStride + (int)pVVar2->pPixels) +
                           (int)src);
          pcVar11 = (char *)((int)dst->pPixels + x + y * (dst->format).nStride);
          if (y <= uVar15) {
            iVar3 = (uVar15 - y) + 1;
            do {
              iVar16 = iVar13;
              if (x <= uVar12) {
                do {
                  if (*pcVar6 != (char)pVVar2->dwColorKey) {
                    *pcVar11 = *pcVar6;
                  }
                  pcVar6 = pcVar6 + 1;
                  pcVar11 = pcVar11 + 1;
                  iVar16 = iVar16 + -1;
                } while (iVar16 != 0);
              }
              pcVar11 = pcVar11 + (iVar1 - iVar13);
              pcVar6 = pcVar6 + (iVar7 - iVar13);
              iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
            return 1;
          }
        }
        break;
      case 0x10:
        if ((flags & 1) == 0) {
          pvVar14 = (void *)((int)pVVar2->pPixels +
                            (int)((int)&src->nType + iVar3 * (pVVar2->format).nStride) * 2);
          x = (int)dst->pPixels + (y * (dst->format).nStride + x) * 2;
          if (y <= uVar15) {
            iVar3 = (uVar15 - y) + 1;
            do {
              Mem_Copy((void *)x,pvVar14,uVar8);
              pvVar14 = (void *)((int)pvVar14 + (pVVar2->format).nStride * 2);
              iVar3 = iVar3 + -1;
              x = x + (dst->format).nStride * 2;
            } while (iVar3 != 0);
            return 1;
          }
        }
        else {
          iVar7 = (pVVar2->format).nStride;
          iVar1 = (dst->format).nStride;
          psVar5 = (short *)((int)pVVar2->pPixels +
                            (int)((int)&src->nType + iVar3 * (pVVar2->format).nStride) * 2);
          psVar10 = (short *)((int)dst->pPixels + (y * (dst->format).nStride + x) * 2);
          if (y <= uVar15) {
            iVar3 = (uVar15 - y) + 1;
            do {
              iVar16 = iVar13;
              if (x <= uVar12) {
                do {
                  if (*psVar5 != (short)pVVar2->dwColorKey) {
                    *psVar10 = *psVar5;
                  }
                  psVar5 = psVar5 + 1;
                  psVar10 = psVar10 + 1;
                  iVar16 = iVar16 + -1;
                } while (iVar16 != 0);
              }
              iVar3 = iVar3 + -1;
              psVar10 = psVar10 + (iVar1 - iVar13);
              psVar5 = psVar5 + (iVar7 - iVar13);
            } while (iVar3 != 0);
            return 1;
          }
        }
        break;
      case 0x18:
        flags = (int)pVVar2->pPixels + (int)src * 3 + iVar3 * (pVVar2->format).nPitch;
        pvVar14 = (void *)((int)dst->pPixels + x * 3 + y * (dst->format).nPitch);
        if (y <= uVar15) {
          iVar3 = (uVar15 - y) + 1;
          do {
            Mem_Copy(pvVar14,(void *)flags,uVar8);
            flags = flags + (pVVar2->format).nPitch;
            pvVar14 = (void *)((int)pvVar14 + (dst->format).nPitch);
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
          return 1;
        }
        break;
      case 0x20:
        if ((flags & 1) == 0) {
          pvVar14 = (void *)((int)pVVar2->pPixels +
                            (int)((int)&src->nType + iVar3 * (pVVar2->format).nStride) * 4);
          x = (int)dst->pPixels + (y * (dst->format).nStride + x) * 4;
          if (y <= uVar15) {
            iVar3 = (uVar15 - y) + 1;
            do {
              Mem_Copy((void *)x,pvVar14,uVar8);
              pvVar14 = (void *)((int)pvVar14 + (pVVar2->format).nStride * 4);
              iVar3 = iVar3 + -1;
              x = x + (dst->format).nStride * 4;
            } while (iVar3 != 0);
            return 1;
          }
        }
        else {
          iVar7 = (pVVar2->format).nStride;
          iVar1 = (dst->format).nStride;
          puVar4 = (uint *)((int)pVVar2->pPixels +
                           (int)((int)&src->nType + iVar3 * (pVVar2->format).nStride) * 4);
          puVar9 = (uint *)((int)dst->pPixels + (y * (dst->format).nStride + x) * 4);
          if (y <= uVar15) {
            iVar3 = (uVar15 - y) + 1;
            do {
              iVar16 = iVar13;
              if (x <= uVar12) {
                do {
                  if (*puVar4 != pVVar2->dwColorKey) {
                    *puVar9 = *puVar4;
                  }
                  puVar4 = puVar4 + 1;
                  puVar9 = puVar9 + 1;
                  iVar16 = iVar16 + -1;
                } while (iVar16 != 0);
              }
              iVar3 = iVar3 + -1;
              puVar9 = puVar9 + (iVar1 - iVar13);
              puVar4 = puVar4 + (iVar7 - iVar13);
            } while (iVar3 != 0);
            return 1;
          }
        }
      }
    }
    return 1;
  }
  return 0;
}

/* ---- 0x004755e0  Surface_BlitDDraw ---- */
uint __cdecl Surface_BlitDDraw(VBuffer *dst,VBuffer *src,uint x,uint y,uint *srcRect,byte colorKey)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  undefined4 uVar7;
  #define local_84 (*(uint *)(_frame + (0xa0 - 0x84)))
  #define local_80 (*(uint *)(_frame + (0xa0 - 0x80)))
  #define local_7c (*(uint *)(_frame + (0xa0 - 0x7c)))
  #define local_78 (*(uint *)(_frame + (0xa0 - 0x78)))
  #define local_74 (*(uint *)(_frame + (0xa0 - 0x74)))
  #define local_70 (*(uint *)(_frame + (0xa0 - 0x70)))
  #define local_6c (*(uint *)(_frame + (0xa0 - 0x6c)))
  #define local_68 (*(uint *)(_frame + (0xa0 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0xa0 - 0x64)))
  
  if ((dst->nLockCount != 0) || (src->nLockCount != 0)) {
    return 0;
  }
  if ((dst->nVideoMemory == 0) || (src->nVideoMemory == 0)) {
    local_74 = x;
    local_70 = y;
    if (srcRect == (uint *)0x0) {
      local_7c = (src->format).nWidth;
      local_84 = 0;
      local_80 = 0;
      uVar3 = (src->format).nHeight;
      local_78 = uVar3;
      uVar2 = local_7c;
    }
    else {
      uVar2 = srcRect[2];
      if (uVar2 == 0) {
        return 0;
      }
      uVar3 = srcRect[3];
      if (uVar3 == 0) {
        return 0;
      }
      local_84 = *srcRect;
      local_80 = srcRect[1];
      local_7c = local_84 + uVar2;
      local_78 = local_80 + uVar3;
    }
    local_6c = x + uVar2;
    local_68 = y + uVar3;
    puVar6 = &local_64;
    for (iVar5 = 0x19; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    local_64 = 100;
    uVar7 = 0x1000000;
    if ((colorKey & 1) != 0) {
      uVar7 = 0x1008000;
    }
    while (piVar1 = (dst->ddraw).pSurface,
          iVar5 = (**(code_std **)(*piVar1 + 0x14))
                            (piVar1,&local_74,(src->ddraw).pSurface,&local_84,uVar7,&local_64),
          iVar5 != 0) {
      if (iVar5 == -0x7789fe3e) {
        if (((dst->ddraw).desc.dwCaps & 4) == 0) {
          piVar1 = (dst->ddraw).pSurface;
          iVar5 = (**(code_std **)(*piVar1 + 0x6c))(piVar1);
        }
        else {
          iVar5 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x6c))(g_pDDrawPrimary->pSurface)
          ;
        }
        if (iVar5 != 0) {
          return 0;
        }
        if (((src->ddraw).desc.dwCaps & 4) == 0) {
          piVar1 = (src->ddraw).pSurface;
          iVar4 = (**(code_std **)(*piVar1 + 0x6c))(piVar1);
        }
        else {
          iVar4 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x6c))(g_pDDrawPrimary->pSurface)
          ;
        }
        iVar5 = 0;
        if (iVar4 != 0) {
          return 0;
        }
      }
      if (iVar5 != 0) {
        return 0;
      }
    }
  }
  else {
    if (srcRect == (uint *)0x0) {
      local_7c = (src->format).nWidth;
      local_84 = 0;
      local_80 = 0;
      local_78 = (src->format).nHeight;
    }
    else {
      if (srcRect[2] == 0) {
        return 0;
      }
      if (srcRect[3] == 0) {
        return 0;
      }
      local_84 = *srcRect;
      local_80 = srcRect[1];
      local_7c = local_84 + srcRect[2];
      local_78 = local_80 + srcRect[3];
    }
    puVar6 = &local_64;
    for (iVar5 = 0x19; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    local_64 = 100;
    uVar7 = 0x10;
    if ((colorKey & 1) != 0) {
      uVar7 = 0x11;
    }
    while (piVar1 = (dst->ddraw).pSurface,
          iVar5 = (**(code_std **)(*piVar1 + 0x1c))(piVar1,x,y,(src->ddraw).pSurface,&local_84,uVar7),
          iVar5 != 0) {
      if (iVar5 == -0x7789fe3e) {
        if (((dst->ddraw).desc.dwCaps & 4) == 0) {
          piVar1 = (dst->ddraw).pSurface;
          iVar5 = (**(code_std **)(*piVar1 + 0x6c))(piVar1);
        }
        else {
          iVar5 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x6c))(g_pDDrawPrimary->pSurface)
          ;
        }
        if (iVar5 != 0) {
          return 0;
        }
        if (((src->ddraw).desc.dwCaps & 4) == 0) {
          piVar1 = (src->ddraw).pSurface;
          iVar4 = (**(code_std **)(*piVar1 + 0x6c))(piVar1);
        }
        else {
          iVar4 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x6c))(g_pDDrawPrimary->pSurface)
          ;
        }
        iVar5 = 0;
        if (iVar4 != 0) {
          return 0;
        }
      }
      if (iVar5 != 0) {
        return 0;
      }
    }
  }
  return 1;
}
#undef local_64
#undef local_68
#undef local_6c
#undef local_70
#undef local_74
#undef local_78
#undef local_7c
#undef local_80
#undef local_84


/* ---- 0x004758a0  Surface_BlitLockedSrc ---- */
uint __cdecl
Surface_BlitLockedSrc(VBuffer *dst,VBuffer *src,void *x,uint y,int *srcRect,void *flags)

{
  int iVar1;
  VBuffer *pVVar2;
  uint uVar3;
  uint *puVar4;
  short *psVar5;
  char *pcVar6;
  void *pvVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint *puVar12;
  short *psVar13;
  char *pcVar14;
  void *pvVar15;
  int iVar16;
  uint local_4;
  
  pVVar2 = src;
  if (dst->nLockCount == 0) {
    if (srcRect == (int *)0x0) {
      iVar8 = (src->format).nWidth;
      iVar9 = (src->format).nHeight;
      src = (VBuffer *)0x0;
      iVar11 = 0;
    }
    else {
      iVar8 = srcRect[2];
      if (iVar8 == 0) {
        return 0;
      }
      iVar9 = srcRect[3];
      if (iVar9 == 0) {
        return 0;
      }
      src = (VBuffer *)*srcRect;
      iVar11 = srcRect[1];
    }
    pvVar15 = (void *)(dst->format).nWidth;
    if (((((int)x < (int)pvVar15) && (iVar8 + (int)x != 0)) &&
        (uVar3 = (dst->format).nHeight, (int)y < (int)uVar3)) && (iVar9 + y != 0)) {
      pvVar7 = (void *)((iVar8 + (int)x) - 1);
      uVar10 = (iVar9 + y) - 1;
      if ((int)y < 0) {
        iVar11 = iVar11 - y;
        y = 0;
      }
      if (uVar3 <= uVar10) {
        uVar10 = uVar3 - 1;
      }
      if ((int)x < 0) {
        src = (VBuffer *)((int)src - (int)x);
        x = (void *)0x0;
      }
      if (pvVar15 <= pvVar7) {
        pvVar7 = (void *)((int)pvVar15 - 1);
      }
      iVar8 = (int)pvVar7 + (1 - (int)x);
      if (iVar8 != 0) {
        uVar3 = ((uint)(pVVar2->format).colorFormat.nBpp >> 3) * iVar8;
        stdDisplay_VBufferLock(dst);
        iVar9 = (pVVar2->format).colorFormat.nBpp;
        if (iVar9 == 8) {
          if (((uint)flags & 1) == 0) {
            flags = (void *)((int)(iVar11 * (pVVar2->format).nStride + (int)pVVar2->pPixels) +
                            (int)src);
            pvVar15 = (void *)((int)(y * (dst->format).nStride + (int)dst->pPixels) + (int)x);
            if (y <= uVar10) {
              iVar8 = (uVar10 - y) + 1;
              do {
                Mem_Copy(pvVar15,flags,uVar3);
                flags = (void *)((int)flags + (pVVar2->format).nStride);
                pvVar15 = (void *)((int)pvVar15 + (dst->format).nStride);
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
            }
          }
          else {
            iVar9 = (pVVar2->format).nStride;
            iVar1 = (dst->format).nStride;
            pcVar14 = (char *)((int)(iVar11 * iVar9 + (int)pVVar2->pPixels) + (int)src);
            pcVar6 = (char *)((int)(y * (dst->format).nStride + (int)dst->pPixels) + (int)x);
            if (y <= uVar10) {
              iVar11 = (uVar10 - y) + 1;
              do {
                iVar16 = iVar8;
                if (x <= pvVar7) {
                  do {
                    if (*pcVar14 != (char)pVVar2->dwColorKey) {
                      *pcVar6 = *pcVar14;
                    }
                    pcVar14 = pcVar14 + 1;
                    pcVar6 = pcVar6 + 1;
                    iVar16 = iVar16 + -1;
                  } while (iVar16 != 0);
                }
                pcVar6 = pcVar6 + (iVar1 - iVar8);
                pcVar14 = pcVar14 + (iVar9 - iVar8);
                iVar11 = iVar11 + -1;
              } while (iVar11 != 0);
            }
          }
        }
        else if (iVar9 == 0x10) {
          if (((uint)flags & 1) == 0) {
            pvVar15 = (void *)((int)pVVar2->pPixels +
                              (int)((int)&src->nType + iVar11 * (pVVar2->format).nStride) * 2);
            x = (void *)((int)dst->pPixels + (int)(y * (dst->format).nStride + (int)x) * 2);
            if (y <= uVar10) {
              iVar8 = (uVar10 - y) + 1;
              do {
                Mem_Copy(x,pvVar15,uVar3);
                iVar8 = iVar8 + -1;
                pvVar15 = (void *)((int)pvVar15 + (pVVar2->format).nStride * 2);
                x = (void *)((int)x + (dst->format).nStride * 2);
              } while (iVar8 != 0);
            }
          }
          else {
            iVar9 = (pVVar2->format).nStride;
            iVar1 = (dst->format).nStride;
            psVar13 = (short *)((int)pVVar2->pPixels + (int)((int)&src->nType + iVar11 * iVar9) * 2)
            ;
            psVar5 = (short *)((int)dst->pPixels + (int)(y * (dst->format).nStride + (int)x) * 2);
            if (y <= uVar10) {
              iVar11 = (uVar10 - y) + 1;
              do {
                iVar16 = iVar8;
                if (x <= pvVar7) {
                  do {
                    if (*psVar13 != (short)pVVar2->dwColorKey) {
                      *psVar5 = *psVar13;
                    }
                    psVar13 = psVar13 + 1;
                    psVar5 = psVar5 + 1;
                    iVar16 = iVar16 + -1;
                  } while (iVar16 != 0);
                }
                iVar11 = iVar11 + -1;
                psVar5 = psVar5 + (iVar1 - iVar8);
                psVar13 = psVar13 + (iVar9 - iVar8);
              } while (iVar11 != 0);
            }
          }
        }
        else if (iVar9 == 0x20) {
          if (((uint)flags & 1) == 0) {
            pvVar15 = (void *)((int)pVVar2->pPixels +
                              (int)((int)&src->nType + iVar11 * (pVVar2->format).nStride) * 4);
            x = (void *)((int)dst->pPixels + (int)(y * (dst->format).nStride + (int)x) * 4);
            if (y <= uVar10) {
              iVar8 = (uVar10 - y) + 1;
              do {
                Mem_Copy(x,pvVar15,uVar3);
                iVar8 = iVar8 + -1;
                pvVar15 = (void *)((int)pvVar15 + (pVVar2->format).nStride * 4);
                x = (void *)((int)x + (dst->format).nStride * 4);
              } while (iVar8 != 0);
            }
          }
          else {
            iVar9 = (pVVar2->format).nStride;
            iVar1 = (dst->format).nStride;
            puVar12 = (uint *)((int)pVVar2->pPixels + (int)((int)&src->nType + iVar11 * iVar9) * 4);
            puVar4 = (uint *)((int)dst->pPixels + (int)(y * (dst->format).nStride + (int)x) * 4);
            if (y <= uVar10) {
              iVar11 = (uVar10 - y) + 1;
              do {
                iVar16 = iVar8;
                if (x <= pvVar7) {
                  do {
                    if (*puVar12 != pVVar2->dwColorKey) {
                      *puVar4 = *puVar12;
                    }
                    puVar12 = puVar12 + 1;
                    puVar4 = puVar4 + 1;
                    iVar16 = iVar16 + -1;
                  } while (iVar16 != 0);
                }
                iVar11 = iVar11 + -1;
                puVar4 = puVar4 + (iVar1 - iVar8);
                puVar12 = puVar12 + (iVar9 - iVar8);
              } while (iVar11 != 0);
            }
          }
        }
        stdDisplay_VBufferUnlock(dst);
      }
      return 1;
    }
  }
  return 0;
}

/* ---- 0x00475c90  Surface_BlitLockedDst ---- */
uint __cdecl
Surface_BlitLockedDst(VBuffer *dst,VBuffer *src,void *x,uint y,int *srcRect,void *flags)

{
  int *piVar1;
  void *pvVar2;
  int iVar3;
  VBuffer *pVVar4;
  VBuffer *surface;
  VBuffer *pVVar5;
  uint n;
  uint *puVar6;
  int iVar7;
  short *psVar8;
  char *pcVar9;
  int iVar10;
  void *pvVar11;
  int iVar12;
  uint *puVar13;
  short *psVar14;
  char *pcVar15;
  int iVar16;
  uint local_4;
  
  surface = src;
  pVVar4 = dst;
  if (src->nLockCount == 0) {
    if (srcRect == (int *)0x0) {
      iVar7 = (src->format).nWidth;
      pVVar5 = (VBuffer *)0x0;
      iVar12 = 0;
      src = (VBuffer *)(src->format).nHeight;
    }
    else {
      iVar7 = srcRect[2];
      if (iVar7 == 0) {
        return 0;
      }
      if ((VBuffer *)srcRect[3] == (VBuffer *)0x0) {
        return 0;
      }
      pVVar5 = (VBuffer *)*srcRect;
      iVar12 = srcRect[1];
      src = (VBuffer *)srcRect[3];
    }
    if (((((int)x < (dst->format).nWidth) && (iVar7 + (int)x != 0)) &&
        ((int)y < (dst->format).nHeight)) && (iVar10 = (int)&src->nType + y, iVar10 != 0)) {
      pvVar11 = (void *)((iVar7 + (int)x) - 1);
      srcRect = (int *)(iVar10 - 1);
      if ((int)y < 0) {
        iVar12 = iVar12 - y;
        y = 0;
      }
      piVar1 = (int *)(dst->format).nHeight;
      if (piVar1 <= srcRect) {
        srcRect = (int *)((int)piVar1 - 1);
      }
      dst = pVVar5;
      if ((int)x < 0) {
        dst = (VBuffer *)((int)pVVar5 - (int)x);
        x = (void *)0x0;
      }
      pvVar2 = (void *)(pVVar4->format).nWidth;
      if (pvVar2 <= pvVar11) {
        pvVar11 = (void *)((int)pvVar2 - 1);
      }
      iVar7 = (int)pvVar11 + (1 - (int)x);
      if (iVar7 != 0) {
        n = ((uint)(surface->format).colorFormat.nBpp >> 3) * iVar7;
        stdDisplay_VBufferLock(surface);
        iVar10 = (surface->format).colorFormat.nBpp;
        if (iVar10 == 8) {
          if (((uint)flags & 1) == 0) {
            flags = (void *)((int)(iVar12 * (surface->format).nStride + (int)surface->pPixels) +
                            (int)dst);
            pvVar11 = (void *)((int)(y * (pVVar4->format).nStride + (int)pVVar4->pPixels) + (int)x);
            if (y <= srcRect) {
              iVar7 = (int)srcRect + (1 - y);
              do {
                Mem_Copy(pvVar11,flags,n);
                flags = (void *)((int)flags + (surface->format).nStride);
                pvVar11 = (void *)((int)pvVar11 + (pVVar4->format).nStride);
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
            }
          }
          else {
            iVar10 = (surface->format).nStride;
            iVar3 = (pVVar4->format).nStride;
            pcVar15 = (char *)((int)(iVar12 * iVar10 + (int)surface->pPixels) + (int)dst);
            pcVar9 = (char *)((int)(y * (pVVar4->format).nStride + (int)pVVar4->pPixels) + (int)x);
            if (y <= srcRect) {
              iVar12 = (int)srcRect + (1 - y);
              do {
                iVar16 = iVar7;
                if (x <= pvVar11) {
                  do {
                    if (*pcVar15 != (char)surface->dwColorKey) {
                      *pcVar9 = *pcVar15;
                    }
                    pcVar15 = pcVar15 + 1;
                    pcVar9 = pcVar9 + 1;
                    iVar16 = iVar16 + -1;
                  } while (iVar16 != 0);
                }
                pcVar9 = pcVar9 + (iVar3 - iVar7);
                pcVar15 = pcVar15 + (iVar10 - iVar7);
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
              stdDisplay_VBufferUnlock(surface);
              return 1;
            }
          }
        }
        else if (iVar10 == 0x10) {
          if (((uint)flags & 1) == 0) {
            pvVar11 = (void *)((int)surface->pPixels +
                              (int)((int)&dst->nType + iVar12 * (surface->format).nStride) * 2);
            x = (void *)((int)pVVar4->pPixels + (int)(y * (pVVar4->format).nStride + (int)x) * 2);
            if (y <= srcRect) {
              iVar7 = (int)srcRect + (1 - y);
              do {
                Mem_Copy(x,pvVar11,n);
                pvVar11 = (void *)((int)pvVar11 + (surface->format).nStride * 2);
                iVar7 = iVar7 + -1;
                x = (void *)((int)x + (pVVar4->format).nStride * 2);
              } while (iVar7 != 0);
              stdDisplay_VBufferUnlock(surface);
              return 1;
            }
          }
          else {
            iVar10 = (surface->format).nStride;
            iVar3 = (pVVar4->format).nStride;
            psVar14 = (short *)((int)surface->pPixels +
                               (int)((int)&dst->nType + iVar12 * iVar10) * 2);
            psVar8 = (short *)((int)pVVar4->pPixels +
                              (int)(y * (pVVar4->format).nStride + (int)x) * 2);
            if (y <= srcRect) {
              iVar12 = (int)srcRect + (1 - y);
              do {
                iVar16 = iVar7;
                if (x <= pvVar11) {
                  do {
                    if (*psVar14 != (short)surface->dwColorKey) {
                      *psVar8 = *psVar14;
                    }
                    psVar14 = psVar14 + 1;
                    psVar8 = psVar8 + 1;
                    iVar16 = iVar16 + -1;
                  } while (iVar16 != 0);
                }
                iVar12 = iVar12 + -1;
                psVar8 = psVar8 + (iVar3 - iVar7);
                psVar14 = psVar14 + (iVar10 - iVar7);
              } while (iVar12 != 0);
              stdDisplay_VBufferUnlock(surface);
              return 1;
            }
          }
        }
        else if (iVar10 == 0x20) {
          if (((uint)flags & 1) == 0) {
            pvVar11 = (void *)((int)surface->pPixels +
                              (int)((int)&dst->nType + iVar12 * (surface->format).nStride) * 4);
            x = (void *)((int)pVVar4->pPixels + (int)(y * (pVVar4->format).nStride + (int)x) * 4);
            if (y <= srcRect) {
              iVar7 = (int)srcRect + (1 - y);
              do {
                Mem_Copy(x,pvVar11,n);
                pvVar11 = (void *)((int)pvVar11 + (surface->format).nStride * 4);
                iVar7 = iVar7 + -1;
                x = (void *)((int)x + (pVVar4->format).nStride * 4);
              } while (iVar7 != 0);
              stdDisplay_VBufferUnlock(surface);
              return 1;
            }
          }
          else {
            iVar10 = (surface->format).nStride;
            iVar3 = (pVVar4->format).nStride;
            puVar13 = (uint *)((int)surface->pPixels + (int)((int)&dst->nType + iVar12 * iVar10) * 4
                              );
            puVar6 = (uint *)((int)pVVar4->pPixels +
                             (int)(y * (pVVar4->format).nStride + (int)x) * 4);
            if (y <= srcRect) {
              iVar12 = (int)srcRect + (1 - y);
              do {
                iVar16 = iVar7;
                if (x <= pvVar11) {
                  do {
                    if (*puVar13 != surface->dwColorKey) {
                      *puVar6 = *puVar13;
                    }
                    puVar13 = puVar13 + 1;
                    puVar6 = puVar6 + 1;
                    iVar16 = iVar16 + -1;
                  } while (iVar16 != 0);
                }
                iVar12 = iVar12 + -1;
                puVar6 = puVar6 + (iVar3 - iVar7);
                puVar13 = puVar13 + (iVar10 - iVar7);
              } while (iVar12 != 0);
              stdDisplay_VBufferUnlock(surface);
              return 1;
            }
          }
        }
        stdDisplay_VBufferUnlock(surface);
      }
      return 1;
    }
  }
  return 0;
}

/* ---- 0x004760d0  DDraw_Create ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl DDraw_Create(uint device)

{
  int iVar1;
  byte *a1;
  
  if (g_pDisplayDevice->nPrimary == 0) {
    a1 = g_pDisplayDevice->aGuid;
  }
  else {
    a1 = (byte *)0x0;
  }
  iVar1 = DirectDrawCreate((int)a1,((unsigned)(uintptr_t)&g_pDirectDraw),0);
  if (iVar1 != 0) {
    return 0;
  }
  g_dwVideoModeCount = 0;
  iVar1 = (**(code_std **)(*(int *)g_pDirectDraw + 0x50))(g_pDirectDraw,device,0x51);
  if (iVar1 != 0) {
    return 0;
  }
  iVar1 = (**(code_std **)(*(int *)g_pDirectDraw + 0x20))
                    (g_pDirectDraw,0,0,0,DDraw_EnumModesCallback320);
  if (iVar1 != 0) {
    return 0;
  }
  iVar1 = (**(code_std **)(*(int *)g_pDirectDraw + 0x50))(g_pDirectDraw,device,0x11);
  if (iVar1 != 0) {
    return 0;
  }
  iVar1 = (**(code_std **)(*(int *)g_pDirectDraw + 0x20))(g_pDirectDraw,0,0,0,DDraw_EnumModesCallback);
  if (iVar1 != 0) {
    return 0;
  }
  iVar1 = (**(code_std **)(*(int *)g_pDirectDraw + 0x50))(g_pDirectDraw,device,8);
  return (uint)(iVar1 == 0);
}
#endif


/* ---- 0x00476190  DDraw_Release ---- */
void __cdecl DDraw_Release(void)

{
  if (g_pDirectDraw != (void *)0x0) {
    (**(code_std **)(*(int *)g_pDirectDraw + 8))(g_pDirectDraw);
    g_pDirectDraw = (void *)0x0;
  }
  return;
}

/* ---- 0x004761b0  stdDisplay_EnumDevicesCallback ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* DirectDrawEnumerate callback (guid, description, driver name, context): fills display device
   record g_dwStdDisplay_numDevices (at most 16, 0x298 bytes each). Hand-written in
   build/overrides_asm_o2.c; was FUN_004761b0. */

undefined * __stdcall stdDisplay_EnumDevicesCallback(int a1,int a2,int a3,int a4)

{
  unsigned char _frame[0x2f0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[768] __attribute__((aligned(16)));  /* the original frame below the return address */
  uint uVar1;
  int iVar2;
  int *piVar3;
  void *pvVar4;
  int *unaff_ESI;
  uint unaff_EDI;
  undefined4 *puVar5;
  int *piVar6;
  undefined4 uVar7;
  #define local_2dc (*(uint *)(_frame + (0x2f0 - 0x2dc)))
  #define uStack_2b4 (*(uint *)(_frame + (0x2f0 - 0x2b4)))
  #define uStack_2b0 (*(uint *)(_frame + (0x2f0 - 0x2b0)))
  #define auStack_178 (*(undefined4 (*)[94])(_frame + (0x2f0 - 0x178)))
  
  uVar1 = g_dwStdDisplay_numDevices;
  local_2dc = 0;
  if (g_dwStdDisplay_numDevices < 0x10) {
    iVar2 = g_dwStdDisplay_numDevices * 0x298;
    (&UINT_00902d60)[g_dwStdDisplay_numDevices * 0xa6] = 1;
    (&UINT_00902d70)[uVar1 * 0xa6] = 1;
    if (a1 == 0) {
      *(undefined4 *)(&DAT_00902ee8 + iVar2) = 0;
      *(undefined4 *)(&DAT_00902eec + iVar2) = 0;
      *(undefined4 *)(&DAT_00902ef0 + iVar2) = 0;
      *(undefined4 *)(&DAT_00902ef4 + iVar2) = 0;
      (&UINT_00902d6c)[uVar1 * 0xa6] = 1;
    }
    else {
      Mem_Copy(&DAT_00902ee8 + iVar2,(void *)a1,0x10);
      (&UINT_00902d6c)[uVar1 * 0xa6] = 0;
    }
    strncpy((uint *)(&DAT_00902ce0 + iVar2),(uint *)a2,0x7f);
    (&DAT_00902d5f)[iVar2] = 0;
    strncpy((uint *)(&DAT_00902c60 + iVar2),(uint *)a3,0x7f);
    (&DAT_00902cdf)[iVar2] = 0;
    if (a1 == 0) {
      (&UINT_00902d64)[uVar1 * 0xa6] = 0;
    }
    else {
      (&UINT_00902d64)[uVar1 * 0xa6] = 1;
    }
    iVar2 = DirectDrawCreate(a1,(int)&local_2dc,0);
    if (iVar2 != 0) {
      return (undefined *)0x1;
    }
    uVar7 = 0x11;
    iVar2 = *(int *)local_2dc;
    piVar3 = Win_GetMainHwnd();
    iVar2 = (**(code_std **)(iVar2 + 0x50))(local_2dc,piVar3,uVar7);
    if (iVar2 == 0) {
      puVar5 = (undefined4 *)(_stkneg + 28);
      for (iVar2 = 0x5b; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      puVar5 = auStack_178;
      for (iVar2 = 0x5b; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      auStack_178[0] = 0x16c;
      piVar6 = (int *)(_stkneg + 28);
      iVar2 = (**(code_std **)(*unaff_ESI + 0x2c))(unaff_ESI,piVar6,auStack_178);
      if (iVar2 != 0) {
        (**(code_std **)(*piVar3 + 8))(piVar3);
        return (undefined *)0x1;
      }
      if ((unaff_EDI & 1) == 0) {
        (&UINT_00902d68)[uVar1 * 0xa6] = 0;
      }
      else {
        (&UINT_00902d68)[uVar1 * 0xa6] = 1;
      }
      uVar7 = 8;
      (&UINT_00902d74)[uVar1 * 0xa6] = uStack_2b4;
      (&UINT_00902d78)[uVar1 * 0xa6] = uStack_2b0;
      iVar2 = *piVar3;
      pvVar4 = Win_GetMainHwnd();
      iVar2 = (**(code_std **)(iVar2 + 0x50))(piVar3,pvVar4,uVar7);
      if (iVar2 == 0) {
        (**(code_std **)(*piVar6 + 8))(piVar6);
        g_dwStdDisplay_numDevices = g_dwStdDisplay_numDevices + 1;
        return (undefined *)0x1;
      }
    }
  }
  return (undefined *)0x0;
}
#undef auStack_178
#undef local_2dc
#undef uStack_2b0
#undef uStack_2b4

#endif


/* ---- 0x00476390  DDraw_EnumModesCallback ---- */
/* DirectDraw EnumDisplayModes callback used by DDraw_Create: stores width, height, pitch, bit depth
   and the colour shift/loss of each mode (up to 64). */

undefined * __stdcall DDraw_EnumModesCallback(int a1,int a2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if (0x3f < g_dwVideoModeCount) {
    return (undefined *)0x0;
  }
  iVar1 = g_dwVideoModeCount * 0x54;
  (&UINT_00901760)[g_dwVideoModeCount * 0x15] = 0;
  iVar3 = *(int *)(a1 + 0xc);
  *(int *)(&DAT_00901768 + iVar1) = iVar3;
  iVar2 = *(int *)(a1 + 8);
  *(int *)(&DAT_0090176c + iVar1) = iVar2;
  *(undefined4 *)(&DAT_00901774 + iVar1) = *(undefined4 *)(a1 + 0x10);
  if ((iVar3 == 0x140) && (iVar2 == 200)) {
    *(undefined4 *)(&DAT_00901764 + iVar1) = 0x3f400000;
  }
  else {
    *(undefined4 *)(&DAT_00901764 + iVar1) = 0x3f800000;
  }
  if ((*(uint *)(a1 + 0x4c) & 0x20) == 0) {
    if ((*(uint *)(a1 + 0x4c) & 0x40) != 0) {
      *(undefined4 *)(&DAT_0090177c + iVar1) = 1;
      *(undefined4 *)(&DAT_00901780 + iVar1) = *(undefined4 *)(a1 + 0x54);
      iVar3 = 0;
      for (uVar4 = *(uint *)(a1 + 0x58); (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_00901790 + iVar1) = iVar3;
      iVar3 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x58) >> ((byte)iVar3 & 0x1f))))
      ;
      *(int *)(&DAT_0090179c + iVar1) = iVar3;
      iVar3 = 0;
      for (; (uVar4 & 1) != 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_00901784 + iVar1) = iVar3;
      iVar3 = 0;
      for (uVar4 = *(uint *)(a1 + 0x5c); (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_00901794 + iVar1) = iVar3;
      iVar3 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x5c) >> ((byte)iVar3 & 0x1f))))
      ;
      *(int *)(&DAT_009017a0 + iVar1) = iVar3;
      iVar3 = 0;
      for (; (uVar4 & 1) != 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_00901788 + iVar1) = iVar3;
      iVar3 = 0;
      for (uVar4 = *(uint *)(a1 + 0x60); (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_00901798 + iVar1) = iVar3;
      iVar3 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x60) >> ((byte)iVar3 & 0x1f))))
      ;
      *(int *)(&DAT_009017a4 + iVar1) = iVar3;
      iVar3 = 0;
      for (; (uVar4 & 1) != 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_0090178c + iVar1) = iVar3;
    }
  }
  else {
    *(undefined4 *)(&DAT_0090177c + iVar1) = 0;
    *(undefined4 *)(&DAT_00901780 + iVar1) = 8;
    *(undefined4 *)(&DAT_00901784 + iVar1) = 0;
    *(undefined4 *)(&DAT_00901788 + iVar1) = 0;
    *(undefined4 *)(&DAT_0090178c + iVar1) = 0;
  }
  switch(*(uint *)(&DAT_00901780 + iVar1)) {
  case 8:
    uVar4 = *(uint *)(&DAT_00901774 + iVar1);
    goto LAB_00476535;
  case 0x10:
    *(uint *)(&DAT_00901778 + iVar1) = *(uint *)(&DAT_00901774 + iVar1) >> 1;
    break;
  case 0x18:
    *(uint *)(&DAT_00901778 + iVar1) = *(uint *)(&DAT_00901774 + iVar1) / 3;
    break;
  case 0x20:
    uVar4 = *(uint *)(&DAT_00901774 + iVar1) >> 2;
LAB_00476535:
    *(uint *)(&DAT_00901778 + iVar1) = uVar4;
  }
  *(uint *)(&DAT_00901770 + iVar1) =
       (*(uint *)(&DAT_00901780 + iVar1) >> 3) * *(int *)(&DAT_0090176c + iVar1) *
       *(int *)(&DAT_00901768 + iVar1);
  g_dwVideoModeCount = g_dwVideoModeCount + 1;
  return (undefined *)0x1;
}

/* ---- 0x004765a0  DDraw_EnumModesCallback320 ---- */
/* Variant of DDraw_EnumModesCallback that keeps only 320-pixel-wide modes (marked with flag 1). */

undefined * __stdcall DDraw_EnumModesCallback320(int a1,int a2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if (0x3f < g_dwVideoModeCount) {
    return (undefined *)0x0;
  }
  iVar1 = g_dwVideoModeCount * 0x54;
  if (*(int *)(a1 + 0xc) != 0x140) {
    return (undefined *)0x1;
  }
  (&UINT_00901760)[g_dwVideoModeCount * 0x15] = 1;
  *(undefined4 *)(&DAT_00901768 + iVar1) = *(undefined4 *)(a1 + 0xc);
  iVar2 = *(int *)(a1 + 8);
  *(int *)(&DAT_0090176c + iVar1) = iVar2;
  *(undefined4 *)(&DAT_00901774 + iVar1) = *(undefined4 *)(a1 + 0x10);
  if (iVar2 == 200) {
    *(undefined4 *)(&DAT_00901764 + iVar1) = 0x3f400000;
  }
  else {
    *(undefined4 *)(&DAT_00901764 + iVar1) = 0x3f800000;
  }
  if ((*(uint *)(a1 + 0x4c) & 0x20) == 0) {
    if ((*(uint *)(a1 + 0x4c) & 0x40) != 0) {
      *(undefined4 *)(&DAT_0090177c + iVar1) = 1;
      *(undefined4 *)(&DAT_00901780 + iVar1) = *(undefined4 *)(a1 + 0x54);
      iVar2 = 0;
      for (uVar3 = *(uint *)(a1 + 0x58); (uVar3 & 1) == 0; uVar3 = uVar3 >> 1) {
        iVar2 = iVar2 + 1;
      }
      *(int *)(&DAT_00901790 + iVar1) = iVar2;
      iVar2 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x58) >> ((byte)iVar2 & 0x1f))))
      ;
      *(int *)(&DAT_0090179c + iVar1) = iVar2;
      iVar2 = 0;
      for (; (uVar3 & 1) != 0; uVar3 = uVar3 >> 1) {
        iVar2 = iVar2 + 1;
      }
      *(int *)(&DAT_00901784 + iVar1) = iVar2;
      iVar2 = 0;
      for (uVar3 = *(uint *)(a1 + 0x5c); (uVar3 & 1) == 0; uVar3 = uVar3 >> 1) {
        iVar2 = iVar2 + 1;
      }
      *(int *)(&DAT_00901794 + iVar1) = iVar2;
      iVar2 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x5c) >> ((byte)iVar2 & 0x1f))))
      ;
      *(int *)(&DAT_009017a0 + iVar1) = iVar2;
      iVar2 = 0;
      for (; (uVar3 & 1) != 0; uVar3 = uVar3 >> 1) {
        iVar2 = iVar2 + 1;
      }
      *(int *)(&DAT_00901788 + iVar1) = iVar2;
      iVar2 = 0;
      for (uVar3 = *(uint *)(a1 + 0x60); (uVar3 & 1) == 0; uVar3 = uVar3 >> 1) {
        iVar2 = iVar2 + 1;
      }
      *(int *)(&DAT_00901798 + iVar1) = iVar2;
      iVar2 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x60) >> ((byte)iVar2 & 0x1f))))
      ;
      *(int *)(&DAT_009017a4 + iVar1) = iVar2;
      iVar2 = 0;
      for (; (uVar3 & 1) != 0; uVar3 = uVar3 >> 1) {
        iVar2 = iVar2 + 1;
      }
      *(int *)(&DAT_0090178c + iVar1) = iVar2;
    }
  }
  else {
    *(undefined4 *)(&DAT_0090177c + iVar1) = 0;
    *(undefined4 *)(&DAT_00901780 + iVar1) = 8;
    *(undefined4 *)(&DAT_00901784 + iVar1) = 0;
    *(undefined4 *)(&DAT_00901788 + iVar1) = 0;
    *(undefined4 *)(&DAT_0090178c + iVar1) = 0;
  }
  switch(*(uint *)(&DAT_00901780 + iVar1)) {
  case 8:
    uVar3 = *(uint *)(&DAT_00901774 + iVar1);
    goto LAB_0047675b;
  case 0x10:
    *(uint *)(&DAT_00901778 + iVar1) = *(uint *)(&DAT_00901774 + iVar1) >> 1;
    break;
  case 0x18:
    *(uint *)(&DAT_00901778 + iVar1) = *(uint *)(&DAT_00901774 + iVar1) / 3;
    break;
  case 0x20:
    uVar3 = *(uint *)(&DAT_00901774 + iVar1) >> 2;
LAB_0047675b:
    *(uint *)(&DAT_00901778 + iVar1) = uVar3;
  }
  *(uint *)(&DAT_00901770 + iVar1) =
       (*(uint *)(&DAT_00901780 + iVar1) >> 3) * *(int *)(&DAT_00901768 + iVar1) *
       *(int *)(&DAT_0090176c + iVar1);
  g_dwVideoModeCount = g_dwVideoModeCount + 1;
  return (undefined *)0x1;
}

/* ---- 0x004767c0  DDraw_Get ---- */
void * __cdecl DDraw_Get(void)

{
  return g_pDirectDraw;
}

/* ---- 0x004767d0  DDraw_CreateSurfaces ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Sets the display mode and creates the primary (+ back buffer when triple buffering) surfaces and
   palette */

undefined4 __cdecl DDraw_CreateSurfaces(undefined4 hwnd,VideoMode *mode,byte *palette)

{
  unsigned char _frame[0x410] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  VBufferFormat *src;
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  uint uVar5;
  uint *puVar6;
  #define abStack_400 (*(byte (*)[1024])(_frame + (0x410 - 0x400)))
  
  uVar5 = 0x11;
  if ((UINT_00803f9c != 0) && (mode->nFullscreen != 0)) {
    uVar5 = 0x51;
  }
  iVar2 = (**(code_std **)(*(int *)g_pDirectDraw + 0x50))(g_pDirectDraw,hwnd,uVar5);
  if (iVar2 != 0) {
    return 0;
  }
  src = &mode->format;
  UINT_00803fb0 = uVar5;
  iVar2 = (**(code_std **)(*(int *)g_pDirectDraw + 0x54))
                    (g_pDirectDraw,src->nWidth,(mode->format).nHeight,
                     (mode->format).colorFormat.nBpp);
  if (iVar2 != 0) {
    return 0;
  }
  uVar5 = (uint)(mode->format).colorFormat.nBpp >> 3;
  g_dwStdDisplay_frontBuffer = 1;
  _DAT_00901684 = 0;
  _DAT_00901688 = 0;
  Mem_Copy(&DAT_0090168c,src,0x4c);
  _DAT_009016d8 = palette;
  UINT_009016dc = 0;
  g_pDDrawPrimary = (DDrawSurfaceRec *)&UINT_009016e4;
  puVar6 = &UINT_009016ec;
  for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  (g_pDDrawPrimary->desc).dwWidth = src->nWidth;
  (g_pDDrawPrimary->desc).dwHeight = (mode->format).nHeight;
  (g_pDDrawPrimary->desc).dwSize = 0x6c;
  g_pDDrawPrimary->pPalette = (void *)0x0;
  if (UINT_00803f9c == 0) {
    (g_pDDrawPrimary->desc).dwFlags = 1;
    (g_pDDrawPrimary->desc).dwCaps = 0x2200;
  }
  else {
    (g_pDDrawPrimary->desc).dwBackBufferCount = 1;
    (g_pDDrawPrimary->desc).dwFlags = 0x21;
    (g_pDDrawPrimary->desc).dwCaps = 0x2218;
  }
  iVar2 = (**(code_std **)(*(int *)g_pDirectDraw + 0x18))
                    (g_pDirectDraw,&g_pDDrawPrimary->desc,g_pDDrawPrimary,0);
  if (iVar2 != 0) {
    return 0;
  }
  iVar2 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x58))
                    (g_pDDrawPrimary->pSurface,&g_pDDrawPrimary->desc);
  if (iVar2 != 0) {
    return 0;
  }
  g_dwStdDisplay_numDrawBuffers = (g_pDDrawPrimary->desc).dwBackBufferCount + 1;
  UINT_00901698 = (g_pDDrawPrimary->desc).nPitch;
  _DAT_0090169c = UINT_00901698 / uVar5;
  if (((g_pDDrawPrimary->desc).dwCaps & 0x4000) != 0) {
    _DAT_00901688 = 1;
  }
  if (UINT_00803f9c != 0) {
    g_dwStdDisplay_backBuffer = 1;
    _DAT_009055e4 = 0;
    _DAT_009055e8 = 0;
    Mem_Copy(&UINT_009055ec,src,0x4c);
    _DAT_00905638 = palette;
    UINT_0090563c = 0;
    g_pDDrawBack = (DDrawSurfaceRec *)&PTR_00905644;
    puVar6 = &UINT_0090564c;
    for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    (g_pDDrawBack->desc).dwWidth = src->nWidth;
    (g_pDDrawBack->desc).dwHeight = (mode->format).nHeight;
    (g_pDDrawBack->desc).dwSize = 0x6c;
    (g_pDDrawBack->desc).dwFlags = 0x21;
    (g_pDDrawBack->desc).dwCaps = 4;
    (g_pDDrawBack->desc).dwBackBufferCount = 1;
    iVar2 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x30))
                      (g_pDDrawPrimary->pSurface,&(g_pDDrawBack->desc).dwCaps,g_pDDrawBack);
    if (iVar2 != 0) {
      return 0;
    }
    iVar2 = (**(code_std **)(*(int *)g_pDDrawBack->pSurface + 0x58))
                      (g_pDDrawBack->pSurface,&g_pDDrawBack->desc);
    if (iVar2 != 0) {
      return 0;
    }
    if (((g_pDDrawBack->desc).dwCaps & 0x4000) != 0) {
      _DAT_009055e8 = 1;
    }
    UINT_009055f8 = (g_pDDrawBack->desc).nPitch;
    _DAT_009055fc = UINT_009055f8 / uVar5;
    g_pDDrawBack->pPalette = (void *)0x0;
  }
  if ((mode->format).colorFormat.nColorMode == 0) {
    iVar2 = GetDC(0);
    GetSystemPaletteEntries(iVar2,0,0x100,(int)abStack_400);
    ReleaseDC(0,iVar2);
    iVar2 = 0x100;
    pbVar4 = abStack_400;
    do {
      bVar1 = *palette;
      pbVar4[3] = 1;
      *pbVar4 = bVar1;
      pbVar3 = palette + 2;
      pbVar4[1] = palette[1];
      palette = palette + 3;
      pbVar4[2] = *pbVar3;
      iVar2 = iVar2 + -1;
      pbVar4 = pbVar4 + 4;
    } while (iVar2 != 0);
    iVar2 = (**(code_std **)(*(int *)g_pDirectDraw + 0x14))
                      (g_pDirectDraw,0x4c,abStack_400,&g_pDDrawPrimary->pPalette,0);
    if (iVar2 != 0) {
      return 0;
    }
    iVar2 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x7c))
                      (g_pDDrawPrimary->pSurface,g_pDDrawPrimary->pPalette);
    if (iVar2 != 0) {
      return 0;
    }
    if (UINT_00803f9c == 0) goto LAB_00476b98;
    iVar2 = (**(code_std **)(*(int *)g_pDDrawBack->pSurface + 0x7c))
                      (g_pDDrawBack->pSurface,g_pDDrawPrimary->pPalette);
    if (iVar2 != 0) {
      return 0;
    }
  }
  if (UINT_00803f9c != 0) {
    return 1;
  }
LAB_00476b98:
  Mem_Copy(&g_dwStdDisplay_backBuffer,&g_dwStdDisplay_frontBuffer,0xd8);
  return 1;
}
#undef abStack_400

#endif


/* ---- 0x00476bc0  DDraw_ReleaseSurfaces ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl DDraw_ReleaseSurfaces(void)

{
  if (UINT_00803f9c != 0) {
    UINT_00905648 = 0;
    Surface_Release((VBuffer *)&g_dwStdDisplay_backBuffer);
  }
  Surface_Release((VBuffer *)&g_dwStdDisplay_frontBuffer);
  return;
}
#endif


/* ---- 0x00476bf0  DDraw_LockSurface ---- */
uint __cdecl DDraw_LockSurface(DDrawSurfaceRec *rec)

{
  int iVar1;
  
  do {
    iVar1 = (**(code_std **)(*(int *)rec->pSurface + 100))(rec->pSurface,0,&rec->desc,1,0);
    if (iVar1 == 0) break;
    if (iVar1 == -0x7789fe3e) {
      if (((rec->desc).dwCaps & 4) == 0) {
        iVar1 = (**(code_std **)(*(int *)rec->pSurface + 0x6c))(rec->pSurface);
      }
      else {
        iVar1 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x6c))(g_pDDrawPrimary->pSurface);
      }
    }
  } while (iVar1 == 0);
  return (uint)(rec->desc).pSurface;
}

/* ---- 0x00476c40  DDraw_UnlockSurface ---- */
uint __cdecl DDraw_UnlockSurface(DDrawSurfaceRec *rec)

{
  int iVar1;
  
  do {
    iVar1 = (**(code_std **)(*(int *)rec->pSurface + 0x80))(rec->pSurface,0);
    if (iVar1 == 0) {
      return 1;
    }
    if (iVar1 == -0x7789fe3e) {
      if (((rec->desc).dwCaps & 4) == 0) {
        iVar1 = (**(code_std **)(*(int *)rec->pSurface + 0x6c))(rec->pSurface);
      }
      else {
        iVar1 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x6c))(g_pDDrawPrimary->pSurface);
      }
    }
  } while (iVar1 == 0);
  return 0;
}

/* ---- 0x00476c90  DDraw_Flip ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
uint __cdecl DDraw_Flip(void)

{
  int iVar1;
  int iVar2;
  
  do {
    iVar1 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x2c))(g_pDDrawPrimary->pSurface,0,0);
    if (iVar1 == 0) {
      return 1;
    }
    if (iVar1 == -0x7789fe3e) {
      iVar2 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x6c))(g_pDDrawPrimary->pSurface);
      iVar1 = 0;
      if (iVar2 != 0) {
        return 0;
      }
    }
  } while (iVar1 == -0x7789fde4);
  return 0;
}
#endif


/* ---- 0x00476cd0  DDraw_FillSurface ---- */
uint __cdecl DDraw_FillSurface(DDrawSurfaceRec *rec,uint color,uint *rect)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint *puVar2;
  #define local_74 (*(uint *)(_frame + (0x90 - 0x74)))
  #define local_70 (*(uint *)(_frame + (0x90 - 0x70)))
  #define local_6c (*(uint *)(_frame + (0x90 - 0x6c)))
  #define local_68 (*(uint *)(_frame + (0x90 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0x90 - 0x64)))
  #define local_14 (*(uint *)(_frame + (0x90 - 0x14)))
  
  puVar2 = &local_64;
  for (iVar1 = 0x19; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  local_64 = 100;
  local_14 = color;
  if (rect == (uint *)0x0) {
    local_6c = (rec->desc).dwWidth;
    local_68 = (rec->desc).dwHeight;
    local_74 = 0;
    local_70 = 0;
  }
  else {
    if (rect[2] == 0) {
      return 0;
    }
    if (rect[3] == 0) {
      return 0;
    }
    local_74 = *rect;
    local_70 = rect[1];
    local_6c = local_74 + rect[2];
    local_68 = local_70 + rect[3];
  }
  do {
    iVar1 = (**(code_std **)(*(int *)rec->pSurface + 0x14))
                      (rec->pSurface,&local_74,0,0,0x1000400,&local_64);
    if (iVar1 == 0) {
      return 1;
    }
    if (iVar1 == -0x7789fe3e) {
      if (((rec->desc).dwCaps & 4) == 0) {
        iVar1 = (**(code_std **)(*(int *)rec->pSurface + 0x6c))(rec->pSurface);
      }
      else {
        iVar1 = (**(code_std **)(*(int *)g_pDDrawPrimary->pSurface + 0x6c))(g_pDDrawPrimary->pSurface);
      }
    }
  } while (iVar1 == 0);
  return 0;
}
#undef local_14
#undef local_64
#undef local_68
#undef local_6c
#undef local_70
#undef local_74


/* ---- 0x00476dc0  DDraw_SetPalette ---- */
uint __cdecl DDraw_SetPalette(undefined1 *palette)

{
  unsigned char _frame[0x410] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  #define local_400 (*(undefined1 (*)[1024])(_frame + (0x410 - 0x400)))
  
  if ((g_pVideoMode->format).colorFormat.nColorMode == 0) {
    iVar3 = 0x100;
    puVar2 = local_400 + 1;
    do {
      puVar2[-1] = *palette;
      puVar1 = palette + 2;
      *puVar2 = palette[1];
      palette = palette + 3;
      puVar2[1] = *puVar1;
      iVar3 = iVar3 + -1;
      puVar2 = puVar2 + 4;
    } while (iVar3 != 0);
    iVar3 = (**(code_std **)(*(int *)g_pDDrawPrimary->pPalette + 0x18))
                      (g_pDDrawPrimary->pPalette,0,0,0x100,local_400);
    if (iVar3 != 0) {
      return 0;
    }
  }
  return 1;
}
#undef local_400


/* ---- 0x00476e40  DIB_CreateSurface ---- */
void * __cdecl DIB_CreateSurface(VideoMode *mode,VBuffer *surface,void *palette,void *hwnd)

{
  int iVar1;
  uint width;
  
  UINT_00803f7c = GetDC((int)hwnd);
  iVar1 = (mode->format).colorFormat.nColorMode;
  if (iVar1 == 0) {
    UINT_00803fb4 =
         ((code *)stdDisplay_BuildBitmapInfo8)(UINT_00803f7c,(mode->format).nWidth,(mode->format).nHeight,(int)surface,palette)
    ;
    if (UINT_00803fb4 == 0) {
      return (void *)0x0;
    }
  }
  else if ((iVar1 == 1) && ((mode->format).colorFormat.nBpp == 0x10)) {
    iVar1 = (mode->format).nHeight;
    width = (mode->format).nWidth;
    if ((mode->format).colorFormat.dwGreenBits == 6) {
      UINT_00803fb4 = (uint)DIB_CreateSection565(UINT_00803f7c,width,iVar1,(uint)surface);
    }
    else {
      UINT_00803fb4 = ((code *)stdDisplay_BuildBitmapInfo16)(UINT_00803f7c,width,iVar1,(int)surface);
    }
    if ((undefined *)UINT_00803fb4 == (undefined *)0x0) {
      return (void *)0x0;
    }
  }
  UINT_007f6498 = CreateCompatibleDC(UINT_00803f7c);
  SelectObject(UINT_007f6498,UINT_00803fb4);
  return (void *)0x1;
}

/* ---- 0x00476ee0  DIB_ReleaseSurface ---- */
void __cdecl DIB_ReleaseSurface(void)

{
  void *a1;
  uint a2;
  
  DeleteObject(UINT_00803fb4);
  a2 = UINT_00803f7c;
  a1 = Win_GetMainHwnd();
  ReleaseDC((int)a1,a2);
  DeleteDC(UINT_007f6498);
  return;
}

/* ---- 0x00478fc0  std3D_SetCurrentPalette ---- */
/* Original name std3D_SetCurrentPalette (the remaster's GrimFandango (Linux): rdColormap_SetCurrent
   calls it with (colormap + 0x30, 0x5a) when rdroid_curAcceleration > 0); was Display_SetPalette3D.
    */

void __cdecl std3D_SetCurrentPalette(void *palette,int flags)

{
  Mem_Copy(&DAT_00806618,palette,0x300);
  if ((*(int *)UINT_00806934 == 1) && (*(int *)(UINT_00806934 + 4) == 0x10)) {
    stdPcx_DecodeRun16(palette,(ushort *)&UINT_00806408,UINT_00806934);
  }
  if (g_pStd3D_CurDevice->nPalettedTextures != 0) {
    if ((*(int *)UINT_00806938 == 2) && (*(int *)(UINT_00806938 + 4) == 0x10)) {
      stdPcx_DecodeRun8(palette,((unsigned)(uintptr_t)&DAT_008061e8),UINT_00806938);
    }
    if (((g_pStd3D_CurDevice->nUnknown18 == 0) && (*(int *)UINT_0080693c == 2)) &&
       (*(int *)(UINT_0080693c + 4) == 0x10)) {
      stdPcx_DecodeRunMasked(palette,((unsigned)(uintptr_t)&DAT_00805fd8),UINT_0080693c,flags);
    }
  }
  return;
}

/* ---- 0x0047b610  Palette_FromFloatTable ---- */
/* Writes n RGB byte triplets from a float colour table */

void __cdecl Palette_FromFloatTable(byte *out,byte *in,int n,double gamma)

{
  byte *pbVar1;
  float10 fVar2;
  longlong lVar3;
  
  if (0 < n) {
    do {
      fVar2 = CI_POW((float10)*in * (float10)0.00392156862745098,(float10)gamma);
      fVar2 = fVar2 * (float10)255.0;
      if ((float10)255.0 < fVar2) {
        fVar2 = (float10)255.0;
      }
      lVar3 = FTOL(fVar2);
      *out = (byte)lVar3;
      pbVar1 = in + 2;
      fVar2 = CI_POW((float10)in[1] * (float10)0.00392156862745098,(float10)gamma);
      fVar2 = fVar2 * (float10)255.0;
      if ((float10)255.0 < fVar2) {
        fVar2 = (float10)255.0;
      }
      lVar3 = FTOL(fVar2);
      out[1] = (byte)lVar3;
      in = in + 3;
      fVar2 = CI_POW((float10)*pbVar1 * (float10)0.00392156862745098,(float10)gamma);
      fVar2 = fVar2 * (float10)255.0;
      if ((float10)255.0 < fVar2) {
        fVar2 = (float10)255.0;
      }
      lVar3 = FTOL(fVar2);
      out[2] = (byte)lVar3;
      out = out + 3;
      n = n + -1;
    } while (n != 0);
  }
  return;
}

/* ---- 0x0047b8a0  stdColor_ColorConvertOneRow ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Converts pixels between the 16-bit RGB layouts described by the format records Original name
   stdColor_ColorConvertOneRow (the remaster's GrimFandango (Linux): aligned call in
   stdColor_ColorConvertOnePixel, stdDisplay_VBufferConvertColorFormat); was Pixel_Convert. */

void __cdecl
stdColor_ColorConvertOneRow(ushort *dst,int dstFormat,ushort *src,int srcFormat,uint count)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  byte bVar10;
  byte bVar11;
  longlong lVar13;
  longlong lVar14;
  longlong lVar15;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  uint local_8;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  byte bVar12;
  
  g_dwStdColor_ColorConvertOneRow_row = g_dwStdColor_ColorConvertOneRow_row + 1;
  bVar10 = (byte)*(undefined4 *)(srcFormat + 8);
  lVar13 = FTOL(((float10)1.0f / (float10)((1 << (bVar10 & 0x1f)) + -1)) *
                 (float10)((1 << ((byte)*(undefined4 *)(dstFormat + 8) & 0x1f)) + -1) *
                 (float10)65536.0f);
  lVar14 = FTOL(((float10)1.0f /
                 (float10)((1 << ((byte)*(undefined4 *)(srcFormat + 0xc) & 0x1f)) + -1)) *
                 (float10)((1 << ((byte)*(undefined4 *)(dstFormat + 0xc) & 0x1f)) + -1) *
                 (float10)65536.0f);
  lVar15 = FTOL(((float10)1.0f /
                 (float10)((1 << ((byte)*(undefined4 *)(srcFormat + 0x10) & 0x1f)) + -1)) *
                 (float10)((1 << ((byte)*(undefined4 *)(dstFormat + 0x10) & 0x1f)) + -1) *
                 (float10)65536.0f);
  bVar11 = (byte)*(undefined4 *)(dstFormat + 0x14);
  bVar12 = (byte)*(undefined4 *)(dstFormat + 0x18);
  if ((*(int *)(srcFormat + 4) == 0x18) && (*(int *)(dstFormat + 4) == 0x10)) {
    uVar9 = g_dwStdColor_ColorConvertOneRow_row & 3;
    do {
      iVar2 = g_anColorDither[uVar9][count & 3];
      *dst = (ushort)(((int)((uint)(byte)*src * (int)lVar13 + iVar2) >> 0x10) << (bVar11 & 0x1f)) |
             (ushort)(((int)((uint)*(byte *)((int)src + 1) * (int)lVar14 + iVar2) >> 0x10) <<
                     (bVar12 & 0x1f)) | (ushort)((uint)(byte)src[1] * (int)lVar15 + iVar2 >> 0x10);
      src = (ushort *)((int)src + 3);
      count = count - 1;
      dst = dst + 1;
    } while (count != 0);
    return;
  }
  if (*(int *)(srcFormat + 4) == 0x10) {
    if (*(int *)(dstFormat + 4) == 0x10) {
      uVar3 = *(undefined4 *)(srcFormat + 0x10);
      uVar4 = *(undefined4 *)(srcFormat + 0x14);
      uVar5 = *(undefined4 *)(srcFormat + 0xc);
      uVar6 = *(undefined4 *)(srcFormat + 0x18);
      do {
        uVar1 = *src;
        src = src + 1;
        count = count - 1;
        *dst = (ushort)(((int)(((uint)(uVar1 >> ((byte)uVar4 & 0x1f)) &
                               0xffffffffU >> (0x20 - bVar10 & 0x1f)) * (int)lVar13) >> 0x10) <<
                       (bVar11 & 0x1f)) |
               (ushort)(((int)(((uint)(uVar1 >> ((byte)uVar6 & 0x1f)) &
                               0xffffffffU >> (0x20U - (char)uVar5 & 0x1f)) * (int)lVar14) >> 0x10)
                       << (bVar12 & 0x1f)) |
               (ushort)(((uint)uVar1 & 0xffffffffU >> (0x20U - (char)uVar3 & 0x1f)) * (int)lVar15 >>
                       0x10);
        dst = dst + 1;
      } while (count != 0);
      return;
    }
    if (*(int *)(dstFormat + 4) == 0x18) {
      uVar3 = *(undefined4 *)(srcFormat + 0x10);
      uVar4 = *(undefined4 *)(srcFormat + 0x18);
      uVar5 = *(undefined4 *)(srcFormat + 0xc);
      uVar6 = *(undefined4 *)(srcFormat + 0x14);
      do {
        uVar1 = *src;
        src = src + 1;
        uVar7 = *(undefined4 *)(srcFormat + 0x24);
        PIECE(local_4,0,1) = (byte)(0xffffffff >> (0x20U - (char)uVar3 & 0x1f));
        uVar8 = *(undefined4 *)(srcFormat + 0x28);
        PIECE(local_c,0,1) = (byte)(0xffffffff >> (0x20 - bVar10 & 0x1f));
        *(byte *)dst = ((byte)(uVar1 >> ((byte)uVar6 & 0x1f)) & (byte)local_c) <<
                       ((byte)*(undefined4 *)(srcFormat + 0x20) & 0x1f);
        *(byte *)((int)dst + 1) =
             ((byte)(uVar1 >> ((byte)uVar4 & 0x1f)) &
             (byte)(0xffffffff >> (0x20U - (char)uVar5 & 0x1f))) << ((byte)uVar7 & 0x1f);
        *(byte *)(dst + 1) = ((byte)uVar1 & (byte)local_4) << ((byte)uVar8 & 0x1f);
        dst = (ushort *)((int)dst + 3);
        count = count - 1;
      } while (count != 0);
    }
  }
  return;
}
#undef local_4
#undef local_c

#endif


/* ---- 0x0047bbb0  stdColor_ColorConvertOnePixel ---- */
/* Original name stdColor_ColorConvertOnePixel (the remaster's GrimFandango (Linux): aligned call in
   stdBitmap_ConvertColorFormat, stdDisplay_VBufferConvertColorFormat); was Pixel_ConvertOne. */

int __cdecl stdColor_ColorConvertOnePixel(int dstFormat,uint pixel,int srcFormat)

{
  stdColor_ColorConvertOneRow((ushort *)&srcFormat,dstFormat,(ushort *)&pixel,srcFormat,1);
  return srcFormat;
}
