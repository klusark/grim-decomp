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
  uint *puVar4;
  undefined4 *puVar5;
  uint *puVar6;
  undefined4 *puVar7;
  #define auStack_a0 (*(undefined4 (*)[6])(_frame + (0xb0 - 0xa0)))
  #define uStack_88 (*(undefined4 *)(_frame + (0xb0 - 0x88)))
  #define local_54 (*(undefined4 (*)[21])(_frame + (0xb0 - 0x54)))
  
  UINT_004e814c = 0;
  Grim_ShutdownDisplay();
  if (g_nDisplayDeviceOpen != 0) {
    return 0;
  }
  stdControl_ShowMouseCursor((uint)((&UINT_00902d70)[deviceIdx * 0xa6] == 0));
  Reg_SetInt(s_ExperimentalDisplay_004dd5e4,1);
  iVar1 = Display_SelectDevice(deviceIdx);
  if ((iVar1 != 0) && (iVar1 = Display_OpenMode(modeIdx,&DAT_004f41e0,1), iVar1 != 0)) {
    if ((*(int *)((int)g_pDisplayDevice + 0x110) == 0) || (UINT_004f5a84 != 0)) {
LAB_00402747:
      puVar4 = (uint *)((int)g_pVideoMode + 0x1c);
      puVar6 = &g_dwRdColormap_colorInfo;
      for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar6 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar6 = puVar6 + 1;
      }
      Surface_Fill(&g_dwStdDisplay_backBuffer,0,(int *)0x0);
      stdDisplay_Update();
      Surface_Fill(&g_dwStdDisplay_backBuffer,0,(int *)0x0);
      iVar1 = Display_Select3DDevice(threeDIdx);
      if (iVar1 == 0) {
        puVar5 = (undefined4 *)((int)g_pVideoMode + 8);
        puVar7 = auStack_a0;
        for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar7 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar7 = puVar7 + 1;
        }
        uStack_88 = 0x10;
        UINT_004f5a34 = (uint)stdDisplay_VBufferNew(auStack_a0,0,0,0);
      }
      else {
        UINT_004f5a34 = (uint)&DAT_00901400;
      }
      grimlib_SetDisplay(&g_dwStdDisplay_backBuffer,UINT_004f5a34);
      Win_SetWindowedSize((uint)(*(int *)((int)g_pDisplayDevice + 0x110) != 0),
                          *(int *)((int)g_pVideoMode + 8),*(int *)((int)g_pVideoMode + 0xc));
      Reg_SetBinary(s_LastDisplayDevice_004dd738,(void *)((int)g_pDisplayDevice + 0x288),0x10);
      stdControl_ShowMouseCursor(0);
      g_bWindowedMode = (uint)(*(int *)((int)g_pDisplayDevice + 0x110) == 0);
      UINT_004e814c = 1;
      return 1;
    }
    UINT_004f5a84 = 1;
    iVar3 = deviceIdx * 0x10;
    puVar5 = (undefined4 *)(*(int *)((int)g_pDisplayModes + iVar3 + 4) + modeIdx * 0x54);
    puVar7 = local_54;
    for (iVar1 = 0x15; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar7 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar7 = puVar7 + 1;
    }
    Grim_ShutdownDisplay();
    iVar1 = Display_SelectDevice(deviceIdx);
    if (iVar1 != 0) {
      if (g_dwVideoModeCount != *(uint *)((int)g_pDisplayModes + iVar3)) {
        (*g_pStd_HS->pAssertFail)
                  (s_stdDisplay_numVideoModes____grim_004dd74c,
                   s_C__grimsrc_tools_grimdemo_grimde_004dd50c,0x60b);
      }
      puVar4 = &UINT_00901760;
      puVar6 = *(uint **)((int)g_pDisplayModes + iVar3 + 4);
      for (uVar2 = g_dwVideoModeCount * 0x15 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar6 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar6 = puVar6 + 1;
      }
      for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
        *(char *)puVar6 = (char)*puVar4;
        puVar4 = (uint *)((int)puVar4 + 1);
        puVar6 = (uint *)((int)puVar6 + 1);
      }
      uVar2 = Display_FindClosestMode
                        (local_54,*(void **)((int)g_pDisplayModes + iVar3 + 4),
                         *(uint *)((int)g_pDisplayModes + iVar3));
      iVar1 = Display_OpenMode(uVar2,&DAT_004f41e0,1);
      if (iVar1 != 0) goto LAB_00402747;
    }
  }
  UINT_004e814c = 0;
  return 0;
}
#undef auStack_a0
#undef local_54
#undef uStack_88


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
        Reg_SetBinary(s_Last3DDevice_004dd794,(void *)((int)g_pStd3D_CurDevice + 0x21c),0x10);
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
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  uint *puVar3;
  void *pvVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  uint *puVar8;
  bool bVar9;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  iVar1 = Reg_GetInt(s_ExperimentalDisplay_004dd5e4,1);
  if (iVar1 != 0) {
    OutputDebugStringA(((unsigned)(uintptr_t)&DAT_004dd874));
    return 0;
  }
  local_10 = 0;
  local_c = 0;
  local_20 = 0;
  local_8 = 0;
  local_30 = 0;
  local_4 = 0;
  local_1c = 0;
  local_2c = 0;
  local_18 = 0;
  local_28 = 0;
  local_14 = 0;
  local_24 = 0;
  Reg_GetBinary(s_LastDisplayDevice_004dd738,&local_20,0x10);
  Reg_GetBinary(s_Last3DDevice_004dd794,&local_30,0x10);
  uVar2 = 0;
  if (g_dwStdDisplay_numDevices != 0) {
    pcVar6 = &DAT_00902ee8;
    do {
      iVar1 = 0x10;
      bVar9 = true;
      pcVar7 = pcVar6;
      puVar3 = &local_20;
      do {
        if (iVar1 == 0) break;
        iVar1 = iVar1 + -1;
        bVar9 = *pcVar7 == (char)*puVar3;
        pcVar7 = pcVar7 + 1;
        puVar3 = (uint *)((int)puVar3 + 1);
      } while (bVar9);
      if (bVar9) break;
      uVar2 = uVar2 + 1;
      pcVar6 = pcVar6 + 0x298;
    } while (uVar2 < g_dwStdDisplay_numDevices);
  }
  if (uVar2 == g_dwStdDisplay_numDevices) {
    OutputDebugStringA(((unsigned)(uintptr_t)&DAT_004dd838));
    return 0;
  }
  *deviceIdx = uVar2;
  puVar3 = (uint *)(uVar2 * 0x10 + (int)g_pDisplayModes);
  uVar2 = Display_FindClosestMode(&UINT_004f4d38,(void *)puVar3[1],*puVar3);
  *modeIdx = uVar2;
  iVar1 = 0x10;
  bVar9 = true;
  puVar3 = &local_30;
  puVar8 = &local_10;
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar9 = (char)*puVar3 == (char)*puVar8;
    puVar3 = (uint *)((int)puVar3 + 1);
    puVar8 = (uint *)((int)puVar8 + 1);
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
      pcVar6 = (char *)(*(int *)((int)pvVar4 + 0xc) + 0x21c + iVar1);
      puVar3 = &local_30;
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        bVar9 = *pcVar6 == (char)*puVar3;
        pcVar6 = pcVar6 + 1;
        puVar3 = (uint *)((int)puVar3 + 1);
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
  uVar1 = Display_FindClosestMode(&UINT_004f4d38,(void *)puVar2[1],*puVar2);
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

void __cdecl
stdDisplay_BuildBitmapInfo8(int param_1,uint param_2,int param_3,int param_4,byte *param_5)

{
  unsigned char _frame[0x440] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  #define local_428 (*(uint *)(_frame + (0x440 - 0x428)))
  #define local_424 (*(uint *)(_frame + (0x440 - 0x424)))
  #define local_420 (*(uint *)(_frame + (0x440 - 0x420)))
  #define local_41c (*(undefined2 *)(_frame + (0x440 - 0x41c)))
  #define local_41a (*(undefined2 *)(_frame + (0x440 - 0x41a)))
  #define local_418 (*(uint *)(_frame + (0x440 - 0x418)))
  #define local_414 (*(uint *)(_frame + (0x440 - 0x414)))
  #define local_410 (*(uint *)(_frame + (0x440 - 0x410)))
  #define local_40c (*(uint *)(_frame + (0x440 - 0x40c)))
  #define local_408 (*(uint *)(_frame + (0x440 - 0x408)))
  #define local_404 (*(uint *)(_frame + (0x440 - 0x404)))
  #define local_400 (*(byte (*)[1024])(_frame + (0x440 - 0x400)))
  
  local_420 = -param_3;
  local_424 = param_2;
  local_428 = 0x28;
  local_41c = 1;
  local_41a = 8;
  local_418 = 0;
  local_414 = 0;
  local_410 = 0;
  local_40c = 0;
  local_408 = 0;
  local_404 = 0;
  iVar3 = 0x100;
  pbVar2 = local_400 + 1;
  do {
    pbVar2[1] = *param_5;
    pbVar1 = param_5 + 2;
    *pbVar2 = param_5[1];
    param_5 = param_5 + 3;
    pbVar2[-1] = *pbVar1;
    pbVar2[2] = 0;
    iVar3 = iVar3 + -1;
    pbVar2 = pbVar2 + 4;
  } while (iVar3 != 0);
  CreateDIBSection(param_1,(int)&local_428,0,param_4,0,0);
  return;
}
#undef local_400
#undef local_404
#undef local_408
#undef local_40c
#undef local_410
#undef local_414
#undef local_418
#undef local_41a
#undef local_41c
#undef local_420
#undef local_424
#undef local_428


/* ---- 0x00473180  stdDisplay_BuildBitmapInfo16 ---- */
void __cdecl stdDisplay_BuildBitmapInfo16(int param_1,uint param_2,int param_3,int param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(undefined2 *)(_frame + (0x40 - 0x20)))
  #define local_1e (*(undefined2 *)(_frame + (0x40 - 0x1e)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  
  local_28 = param_2;
  local_2c = 0x28;
  local_24 = -param_3;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_20 = 1;
  local_1e = 0x10;
  CreateDIBSection(param_1,(int)&local_2c,0,param_4,0,0);
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_1e
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_8
#undef local_c


/* ---- 0x004731f0  DIB_CreateSection565 ---- */
/* CreateDIBSection of a top-down 16-bit surface with the RGB565 bit masks (0xf800, 0x7e0, 0x1f). */

undefined * __cdecl DIB_CreateSection565(uint param_1,uint param_2,int param_3,uint param_4)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined *puVar1;
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(undefined2 *)(_frame + (0x50 - 0x28)))
  #define local_26 (*(undefined2 *)(_frame + (0x50 - 0x26)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x50 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x50 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x50 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x50 - 0x4)))
  
  local_30 = param_2;
  local_34 = 0x28;
  local_2c = -param_3;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_28 = 1;
  local_26 = 0x10;
  local_24 = 3;
  local_c = 0xf800;
  local_8 = 0x7e0;
  local_4 = 0x1f;
  puVar1 = (undefined *)CreateDIBSection(param_1,(int)&local_34,0,param_4,0,0);
  return puVar1;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_26
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00473270  Palette_SwapRedBlue ---- */
/* Converts a 768-byte RGB palette to BGR order */

uint __cdecl Palette_SwapRedBlue(int param_1,byte *param_2)

{
  unsigned char _frame[0x820] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  int a2;
  int iVar4;
  #define uStack_808 (*(undefined2 *)(_frame + (0x820 - 0x808)))
  #define uStack_806 (*(undefined2 *)(_frame + (0x820 - 0x806)))
  #define abStack_800 (*(byte (*)[1024])(_frame + (0x820 - 0x800)))
  #define local_400 (*(byte (*)[1024])(_frame + (0x820 - 0x400)))
  
  iVar4 = 0x100;
  pbVar2 = param_2;
  pbVar3 = local_400 + 1;
  do {
    pbVar3[1] = *pbVar2;
    pbVar1 = pbVar2 + 2;
    *pbVar3 = pbVar2[1];
    pbVar2 = pbVar2 + 3;
    pbVar3[-1] = *pbVar1;
    pbVar3[2] = 0;
    iVar4 = iVar4 + -1;
    pbVar3 = pbVar3 + 4;
  } while (iVar4 != 0);
  iVar4 = SetDIBColorTable(param_1,0,0x100,(int)local_400);
  if (iVar4 == 0) {
    return 0;
  }
  uStack_808 = 0x300;
  uStack_806 = 0x100;
  iVar4 = 0x100;
  pbVar2 = abStack_800 + 1;
  do {
    pbVar2[-1] = *param_2;
    pbVar3 = param_2 + 2;
    *pbVar2 = param_2[1];
    param_2 = param_2 + 3;
    pbVar2[1] = *pbVar3;
    pbVar2[2] = 1;
    iVar4 = iVar4 + -1;
    pbVar2 = pbVar2 + 4;
  } while (iVar4 != 0);
  iVar4 = CreatePalette((int)&uStack_808);
  a2 = SelectPalette(param_1,iVar4,1);
  AnimatePalette(iVar4,0,0x100,(int)abStack_800);
  RealizePalette(param_1);
  SelectPalette(param_1,a2,0);
  DeleteObject(iVar4);
  return 1;
}
#undef abStack_800
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
  iVar1 = DirectDrawEnumerateA(((unsigned)(uintptr_t)FUN_004761b0),0);
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
  if ((*(int *)((int)g_pDisplayDevice + 0x100) == 1) && (g_pDirectDraw != (void *)0x0)) {
    (**(code_std **)(*(int *)g_pDirectDraw + 0x4c))(g_pDirectDraw);
  }
  return;
}

/* ---- 0x00473c80  Display_SelectDevice ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl Display_SelectDevice(int deviceIdx)

{
  void *pvVar1;
  int iVar2;
  
  if (g_nDisplayDeviceOpen != 0) {
    return 0;
  }
  if (g_dwStdDisplay_numDevices <= (uint)deviceIdx) {
    return 0;
  }
  UINT_00901758 = deviceIdx;
  g_pDisplayDevice = &DAT_00902c60 + deviceIdx * 0x298;
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
    pvVar1 = Win_GetMainHwnd();
    iVar2 = DDraw_Create((uint)pvVar1);
    if (iVar2 == 0) {
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
    if (*(int *)((int)g_pDisplayDevice + 0x100) == 1) {
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
  uint *mode;
  byte *palette_00;
  
  if (g_dwVideoModeCount <= modeIdx) {
    return 0;
  }
  if (g_nDisplayModeOpen != 0) {
    stdDisplay_ClearMode();
  }
  UINT_00803f9c = use3D;
  _DAT_0090175c = modeIdx;
  g_dwStdDisplay_numDrawBuffers = 1;
  g_pVideoMode = &UINT_00901760 + modeIdx * 0x15;
  if (*(int *)((int)g_pDisplayDevice + 0x100) == 0) {
    pvVar1 = Win_GetMainHwnd();
    pvVar1 = DIB_CreateSurface(g_pVideoMode,&UINT_007feae0,palette,pvVar1);
    if (pvVar1 == (void *)0x0) {
      return 0;
    }
    g_dwStdDisplay_frontBuffer = 0;
    _DAT_00901684 = 0;
    _DAT_00901688 = 0;
    Mem_Copy(&DAT_0090168c,(void *)((int)g_pVideoMode + 8),0x4c);
    _DAT_009016d8 = palette;
    UINT_009016dc = UINT_007feae0;
    g_dwStdDisplay_backBuffer = 0;
    _DAT_009055e8 = 0;
    Mem_Copy(&UINT_009055ec,(void *)((int)g_pVideoMode + 8),0x4c);
    _DAT_00905638 = palette;
    UINT_0090563c = UINT_007feae0;
  }
  else if (*(int *)((int)g_pDisplayDevice + 0x100) == 1) {
    mode = g_pVideoMode;
    palette_00 = palette;
    pvVar1 = Win_GetMainHwnd();
    iVar2 = DDraw_CreateSurfaces(pvVar1,(int *)mode,palette_00);
    if (iVar2 == 0) {
      return 0;
    }
  }
  Surface_Fill(&g_dwStdDisplay_backBuffer,0,(int *)0x0);
  stdDisplay_Update();
  if (use3D != 0) {
    Surface_Fill(&g_dwStdDisplay_backBuffer,0,(int *)0x0);
  }
  stdDisplay_SetMasterPalette(palette);
  g_pDebugFont = (void *)CreateFontA((-(uint)(*(uint *)((int)g_pVideoMode + 8) < 0x280) & 0xfffffff4
                                     ) + 0x18,0,0,0,400,0,0,0,0,0,0,0,2,((unsigned)(uintptr_t)&s_Arial_004dea10));
  _DAT_007feac8 = 0;
  _DAT_007feacc = 0;
  _DAT_007fead0 = *(undefined4 *)((int)g_pVideoMode + 8);
  _DAT_007fead4 = *(undefined4 *)((int)g_pVideoMode + 0xc);
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
    if (*(int *)((int)g_pDisplayDevice + 0x100) == 0) {
      UINT_009016dc = 0;
      UINT_0090563c = 0;
      Surface_Release(&g_dwStdDisplay_frontBuffer);
      Surface_Release(&g_dwStdDisplay_backBuffer);
      DIB_ReleaseSurface();
    }
    else if (*(int *)((int)g_pDisplayDevice + 0x100) == 1) {
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
  
  if (((g_nDisplayDeviceOpen != 0) && (g_nDisplayModeOpen != 0)) &&
     (*(int *)((int)g_pDisplayDevice + 0x100) == 1)) {
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
  
  if (((g_nDisplayDeviceOpen != 0) && (g_nDisplayModeOpen != 0)) &&
     (*(int *)((int)g_pDisplayDevice + 0x100) == 1)) {
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
  
  if (*(int *)((int)g_pDisplayDevice + 0x100) == 0) {
    GdiFlush();
    BitBlt(UINT_00803f7c,0,0,*(int *)((int)g_pVideoMode + 8),*(int *)((int)g_pVideoMode + 0xc),
           UINT_007f6498,0,0,0xcc0020);
  }
  else {
    iVar1 = *(int *)((int)g_pDisplayDevice + 0x100) + -1;
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
/* Std/Win95/Stddisplay.c: creates a surface record (0xd8 bytes) from a 19-dword format/size
   description Original name stdDisplay_VBufferNew (the remaster's GrimFandango (Linux): aligned
   call in rdMaterial_LoadEntry, stdBmp_LoadEntry, stdPic_LoadEntry); was Surface_Create. */

void * __cdecl stdDisplay_VBufferNew(void *info,int videoMem,int b,int c)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[1072] __attribute__((aligned(16)));  /* the original frame below the return address */
  undefined4 *puVar1;
  undefined1 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  undefined1 *puVar7;
  uint uVar8;
  undefined4 *puVar9;
  #define puStack_8 (*(undefined1 **)(_frame + (0x20 - 0x8)))
  
  puVar4 = (undefined4 *)(*g_pStd_HS->pAlloc)(0xd8);
  if (puVar4 == (undefined4 *)0x0) {
    return (void *)0x0;
  }
  puVar4[0x16] = c;
  puVar4[0x17] = 0;
  puVar4[1] = 0;
  Mem_Copy(puVar4 + 3,info,0x4c);
  iVar6 = puVar4[3];
  uVar8 = (uint)puVar4[9] >> 3;
  uVar5 = uVar8 * iVar6;
  puVar4[6] = uVar5;
  puVar4[0x18] = 0;
  puVar4[7] = uVar5 / uVar8;
  iVar6 = uVar8 * iVar6 * puVar4[4];
  puVar4[5] = iVar6;
  if (((videoMem == 0) || (g_nDisplayDeviceOpen == 0)) ||
     (*(int *)((int)g_pDisplayDevice + 0x100) != 1)) {
    *puVar4 = 0;
    puVar4[2] = 0;
    iVar6 = (*g_pStd_HS->pAlloc)(iVar6);
    puVar4[0x17] = iVar6;
    if (iVar6 == 0) {
      return (void *)0x0;
    }
    puVar4[1] = 1;
  }
  else {
    puVar4[2] = 0;
    puVar1 = puVar4 + 0x1b;
    *puVar4 = 1;
    puVar9 = puVar1;
    for (iVar6 = 0x1b; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
    }
    *puVar1 = 0x6c;
    puVar4[0x1c] = 7;
    puVar4[0x35] = 0x40;
    if (b == 0) {
      puVar4[0x35] = 0x840;
    }
    puVar4[0x1e] = puVar4[3];
    puVar4[0x1d] = puVar4[4];
    iVar6 = (**(code_std **)(*(int *)g_pDirectDraw + 0x18))(g_pDirectDraw,puVar1);
    if (iVar6 != 0) {
      return (void *)0x0;
    }
    piVar3 = (int *)puVar4[0x19];
    iVar6 = (**(code_std **)(*piVar3 + 0x58))(piVar3,puVar4 + 0x1b);
    if (iVar6 != 0) {
      return (void *)0x0;
    }
    if ((puVar4[0x35] & 0x4000) != 0) {
      puVar4[2] = 1;
    }
    puVar4[6] = puVar4[0x1f];
    puVar4[7] = (uint)puVar4[0x1f] / uVar8;
    if (puStack_8 == (undefined1 *)0x0) {
      puVar4[0x1a] = 0;
      return puVar4;
    }
    iVar6 = 0xfe;
    puVar7 = (_stkneg + 28);
    do {
      uVar2 = puStack_8[3];
      puVar7[3] = 1;
      *puVar7 = uVar2;
      puVar7[1] = puStack_8[4];
      puVar7[2] = puStack_8[5];
      iVar6 = iVar6 + -1;
      puVar7 = puVar7 + 4;
      puStack_8 = puStack_8 + 3;
    } while (iVar6 != 0);
    iVar6 = (**(code_std **)(*(int *)g_pDirectDraw + 0x14))
                      (g_pDirectDraw,0xc,(_stkneg + 24),puVar4 + 0x1a,0);
    if (iVar6 != 0) {
      return (void *)0x0;
    }
    piVar3 = (int *)puVar4[0x19];
    iVar6 = (**(code_std **)(*piVar3 + 0x7c))(piVar3,puVar4[0x1a]);
    if (iVar6 != 0) {
      return (void *)0x0;
    }
  }
  return puVar4;
}
#undef puStack_8

#endif


/* ---- 0x004746d0  stdDisplay_VBufferFree ---- */
/* Original name stdDisplay_VBufferFree (the remaster's GrimFandango (Linux): aligned call in
   sputLua_FreeImage, sputRender_Close, stdDisplay_VBufferConvertColorFormat); was Surface_Free. */

void __cdecl stdDisplay_VBufferFree(void *surface)

{
  if (surface != (void *)0x0) {
    Surface_Release(surface);
    (*g_pStd_HS->pFree)(surface);
  }
  return;
}

/* ---- 0x004746f0  Surface_Release ---- */
/* Releases DirectDraw surfaces (type 1) or frees the system memory pixels (types 0/2) */

void __cdecl Surface_Release(void *surface)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *(int *)surface;
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      piVar2 = *(int **)((int)surface + 100);
      if (piVar2 != (int *)0x0) {
        (**(code_std **)(*piVar2 + 8))(piVar2);
        *(undefined4 *)((int)surface + 100) = 0;
      }
      piVar2 = *(int **)((int)surface + 0x68);
      if (piVar2 == (int *)0x0) {
        return;
      }
      (**(code_std **)(*piVar2 + 8))(piVar2);
      *(undefined4 *)((int)surface + 0x68) = 0;
      return;
    }
    if (iVar1 != 2) {
      return;
    }
  }
  if (*(int *)((int)surface + 0x5c) != 0) {
    (*g_pStd_HS->pFree)(*(int *)((int)surface + 0x5c));
    *(undefined4 *)((int)surface + 0x5c) = 0;
  }
  return;
}

/* ---- 0x00474750  stdDisplay_VBufferLock ---- */
/* Original name stdDisplay_VBufferLock (the remaster's GrimFandango (Linux): aligned call in
   rdMaterial_LoadEntry, stdBmp_LoadEntry, stdPic_LoadEntry); was Surface_Lock. */

int __cdecl stdDisplay_VBufferLock(void *surface)

{
  uint uVar1;
  
  if (*(int *)surface != 0) {
    if (*(int *)surface != 1) {
      return 1;
    }
    if (((*(uint *)((int)surface + 0xd4) & 0x20) != 0) &&
       ((*(uint *)((int)surface + 0xd4) & 0x200000) != 0)) {
      return 0;
    }
    uVar1 = DDraw_LockSurface((uint *)((int)surface + 100));
    *(uint *)((int)surface + 0x18) = *(uint *)((int)surface + 0x7c);
    *(uint *)((int)surface + 0x5c) = uVar1;
    *(uint *)((int)surface + 0x1c) =
         *(uint *)((int)surface + 0x7c) / (*(uint *)((int)surface + 0x24) >> 3);
    if (uVar1 == 0) {
      return 0;
    }
  }
  *(int *)((int)surface + 4) = *(int *)((int)surface + 4) + 1;
  return 1;
}

/* ---- 0x004747b0  stdDisplay_VBufferUnlock ---- */
/* Original name stdDisplay_VBufferUnlock (the remaster's GrimFandango (Linux): aligned call in
   rdMaterial_LoadEntry, stdBmp_LoadEntry, stdPic_LoadEntry); was Surface_Unlock. */

int __cdecl stdDisplay_VBufferUnlock(void *surface)

{
  uint uVar1;
  
  if (*(int *)surface == 0) {
    if (*(int *)((int)surface + 4) != 0) {
      *(int *)((int)surface + 4) = *(int *)((int)surface + 4) + -1;
    }
  }
  else if (*(int *)surface == 1) {
    if (*(int *)((int)surface + 4) == 0) {
      return (int)surface;
    }
    uVar1 = DDraw_UnlockSurface((uint *)((int)surface + 100));
    if (uVar1 == 0) {
      return 0;
    }
    *(int *)((int)surface + 4) = *(int *)((int)surface + 4) + -1;
    return uVar1;
  }
  return 1;
}

/* ---- 0x00474800  Surface_Fill ---- */
int __cdecl Surface_Fill(void *surface,int color,int *rect)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined1 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 *puVar8;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  if (*(int *)surface == 0) {
    iVar3 = *(int *)((int)surface + 0x24);
    if (iVar3 == 8) {
      uVar1 = (undefined1)color;
      if (rect == (int *)0x0) {
        uVar2 = *(uint *)((int)surface + 0x14);
        puVar6 = *(undefined4 **)((int)surface + 0x5c);
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
      puVar6 = (undefined4 *)
               (*(int *)((int)surface + 0x1c) * rect[1] + *(int *)((int)surface + 0x5c) + *rect);
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
          puVar6 = (undefined4 *)((int)puVar6 + *(int *)((int)surface + 0x18));
          local_8 = local_8 + 1;
        } while ((int)local_8 < rect[3]);
      }
    }
    else if (iVar3 == 0x10) {
      if (rect == (int *)0x0) {
        puVar6 = *(undefined4 **)((int)surface + 0x5c);
        uVar2 = *(uint *)((int)surface + 0x14) >> 1;
        if ((uVar2 & 1) == 0) {
          for (uVar2 = *(uint *)((int)surface + 0x14) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar6 = CONCAT22((undefined2)color,(undefined2)color);
            puVar6 = puVar6 + 1;
          }
        }
        else {
          for (; uVar2 != 0; uVar2 = uVar2 - 1) {
            *(undefined2 *)puVar6 = (undefined2)color;
            puVar6 = (undefined4 *)((int)puVar6 + 2);
          }
        }
        return 1;
      }
      local_8 = 0;
      puVar6 = (undefined4 *)
               (*(int *)((int)surface + 0x5c) +
               (*(int *)((int)surface + 0x1c) * rect[1] + *rect) * 2);
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
          puVar6 = (undefined4 *)((int)puVar6 + *(int *)((int)surface + 0x18));
          local_8 = local_8 + 1;
        } while ((int)local_8 < rect[3]);
        return 1;
      }
    }
    else if (iVar3 == 0x20) {
      if (rect == (int *)0x0) {
        piVar5 = *(int **)((int)surface + 0x5c);
        for (uVar2 = *(uint *)((int)surface + 0x14) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
          *piVar5 = color;
          piVar5 = piVar5 + 1;
        }
        return 1;
      }
      local_8 = 0;
      piVar5 = (int *)(*(int *)((int)surface + 0x5c) +
                      (*(int *)((int)surface + 0x1c) * rect[1] + *rect) * 4);
      if (0 < rect[3]) {
        do {
          piVar7 = piVar5;
          for (iVar3 = rect[2]; iVar3 != 0; iVar3 = iVar3 + -1) {
            *piVar7 = color;
            piVar7 = piVar7 + 1;
          }
          piVar5 = (int *)((int)piVar5 + *(int *)((int)surface + 0x18));
          local_8 = local_8 + 1;
        } while ((int)local_8 < rect[3]);
        return 1;
      }
    }
  }
  else if (*(int *)surface == 1) {
    if (((*(uint *)((int)surface + 0xd4) & 0x20) != 0) &&
       ((*(uint *)((int)surface + 0xd4) & 0x200000) != 0)) {
      return 0;
    }
    uVar2 = DDraw_FillSurface((uint *)((int)surface + 100),color,(uint *)rect);
    return uVar2;
  }
  return 1;
}
#undef local_8


/* ---- 0x00474a60  Surface_Blit ---- */
int __cdecl Surface_Blit(void *dst,void *src,int x,int y,int *srcRect,int colorKey)

{
  if (*(int *)src != 0) {
    if (*(int *)dst == 1) {
      Surface_BlitDDraw((int)dst,(int)src,x,y,(uint *)srcRect,(byte)colorKey);
      return 1;
    }
    Surface_BlitLockedDst((int)dst,src,(void *)x,y,srcRect,(void *)colorKey);
    return 1;
  }
  if (*(int *)dst == 0) {
    Surface_BlitSoftware(dst,src,x,y,srcRect,colorKey);
    return 1;
  }
  Surface_BlitLockedSrc(dst,(int)src,(void *)x,y,srcRect,(void *)colorKey);
  return 1;
}

/* ---- 0x00474ae0  stdDisplay_VBufferSetColorKey ---- */
/* Original name stdDisplay_VBufferSetColorKey (the remaster's GrimFandango (Linux): aligned call in
   rdMaterial_LoadEntry, stdBitmap_ConvertColorFormat); was Surface_SetColorKey. */

int __cdecl stdDisplay_VBufferSetColorKey(void *surface,int color)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (*(int *)surface == 0) {
    *(int *)((int)surface + 0x60) = color;
  }
  else if (*(int *)surface == 1) {
    local_8 = color;
    local_4 = color;
    (**(code_std **)(**(int **)((int)surface + 100) + 0x74))(*(int **)((int)surface + 100),8,&local_8);
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

void __cdecl stdDisplay_VBufferDeCompress(void *surface)

{
  void *dst;
  int iVar1;
  
  if (*(int *)surface == 2) {
    dst = (void *)(*g_pStd_HS->pAlloc)
                            (*(int *)((int)surface + 0x18) * *(int *)((int)surface + 0x10),
                             s_C__grimjedi_Libs_Std_Win95_Stddi_004dea18,DAT_004de1d8 + 0xc);
    if (dst != (void *)0x0) {
      iVar1 = LzssDecompress(dst,*(void **)((int)surface + 0x5c),*(int *)((int)surface + 0x14));
      (*g_pStd_HS->pFree)(*(undefined4 *)((int)surface + 0x5c));
      *(int *)((int)surface + 0x14) = iVar1;
      *(undefined4 *)surface = 0;
      *(void **)((int)surface + 0x5c) = dst;
    }
  }
  return;
}

/* ---- 0x00474ba0  stdDisplay_VBufferDeCompressTo ---- */
/* Original name stdDisplay_VBufferDeCompressTo (the remaster's GrimFandango (Linux): aligned call
   in sputRender_Decompress, sputRender_UseSetup); was Surface_CopyConvert. */

int __cdecl stdDisplay_VBufferDeCompressTo(void *src,void *dst)

{
  int iVar1;
  
  stdDisplay_VBufferLock(dst);
  LzssDecompress(*(void **)((int)dst + 0x5c),*(void **)((int)src + 0x5c),*(int *)((int)src + 0x14));
  iVar1 = stdDisplay_VBufferUnlock(dst);
  return iVar1;
}

/* ---- 0x00474be0  stdDisplay_VBufferConvertColorFormat ---- */
/* Original name stdDisplay_VBufferConvertColorFormat (the remaster's GrimFandango (Linux): aligned
   call in stdBitmap_ConvertColorFormat); was Surface_CreateFromBitmap. */

void * __cdecl stdDisplay_VBufferConvertColorFormat(int *param_1,void *param_2)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *surface;
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *piVar5;
  bool bVar6;
  #define local_4c (*(undefined4 (*)[5])(_frame + (0x60 - 0x4c)))
  #define local_38 (*(int (*)[14])(_frame + (0x60 - 0x38)))
  
  iVar1 = 0x38;
  bVar6 = true;
  piVar3 = param_1;
  piVar5 = (int *)((int)param_2 + 0x20);
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar6 = (char)*piVar3 == (char)*piVar5;
    piVar3 = (int *)((int)piVar3 + 1);
    piVar5 = (int *)((int)piVar5 + 1);
  } while (bVar6);
  if (bVar6) {
    return param_2;
  }
  if ((*(int *)((int)param_2 + 0x20) == 0) && (*param_1 == 0)) {
    return param_2;
  }
  surface = param_2;
  if (*(int *)((int)param_2 + 0x24) != param_1[1]) {
    puVar2 = (undefined4 *)((int)param_2 + 0xc);
    puVar4 = local_4c;
    for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    piVar3 = param_1;
    piVar5 = local_38;
    for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar5 = *piVar3;
      piVar3 = piVar3 + 1;
      piVar5 = piVar5 + 1;
    }
    surface = stdDisplay_VBufferNew(local_4c,0,0,0);
    if (surface == (void *)0x0) {
      return (void *)0x0;
    }
  }
  stdDisplay_VBufferLock(param_2);
  stdDisplay_VBufferLock(surface);
  iVar1 = 0;
  if (0 < *(int *)((int)surface + 0x10)) {
    do {
      stdColor_ColorConvertOneRow
                ((ushort *)(iVar1 * *(int *)((int)surface + 0x18) + *(int *)((int)surface + 0x5c)),
                 (int)param_1,
                 (ushort *)(iVar1 * *(int *)((int)param_2 + 0x18) + *(int *)((int)param_2 + 0x5c)),
                 (int)param_2 + 0x20,*(uint *)((int)surface + 0xc));
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)((int)surface + 0x10));
  }
  stdDisplay_VBufferUnlock(param_2);
  stdDisplay_VBufferUnlock(surface);
  iVar1 = stdColor_ColorConvertOnePixel
                    ((int)param_1,*(uint *)((int)param_2 + 0x60),(int)param_2 + 0x20);
  *(int *)((int)surface + 0x60) = iVar1;
  piVar3 = (int *)((int)surface + 0x20);
  for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar3 = *param_1;
    param_1 = param_1 + 1;
    piVar3 = piVar3 + 1;
  }
  if (surface != param_2) {
    stdDisplay_VBufferFree(param_2);
  }
  return surface;
}
#undef local_38
#undef local_4c


/* ---- 0x00474d10  stdDisplay_SetPalette ---- */
/* Original name stdDisplay_SetPalette (the remaster's GrimFandango (Linux): the first call of
   grimdemo_SetPalette; the remaster's is a stub); was Display_SetDIBPalette. */

int __cdecl stdDisplay_SetPalette(uint param_1)

{
  int iVar1;
  uint uVar2;
  
  if (*(int *)((int)g_pVideoMode + 0x1c) != 0) {
    return 0;
  }
  if (*(int *)((int)g_pDisplayDevice + 0x100) == 0) {
    uVar2 = Palette_SwapRedBlue(UINT_007f6498,(byte *)param_1);
    if (uVar2 == 0) {
      return 0;
    }
    GdiFlush();
    iVar1 = BitBlt(UINT_00803f7c,0,0,*(int *)((int)g_pVideoMode + 8),
                   *(int *)((int)g_pVideoMode + 0xc),UINT_007f6498,0,0,0xcc0020);
  }
  else {
    iVar1 = *(int *)((int)g_pDisplayDevice + 0x100) + -1;
    if (iVar1 == 0) {
      uVar2 = DDraw_SetPalette((byte *)param_1);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl Palette_ApplyGamma(void *dst,void *src,int count,int gammaIdx)

{
  undefined4 unaff_retaddr;
  
  if (UINT_00803fc0 == 0) {
    Mem_Copy(dst,src,0x300);
    return 0;
  }
  if (gammaIdx != 0) {
    Palette_FromFloatTable
              (dst,src,0x100,
               (double)CONCAT44(unaff_retaddr,*(undefined4 *)((UINT_00803fc0 - 4) + gammaIdx * 8)));
    return 1;
  }
  Mem_Copy(dst,src,0x300);
  return 1;
}
#endif


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
  
  if (*(int *)((int)g_pDisplayDevice + 0x100) == 0) {
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
  if (*(int *)((int)g_pDisplayDevice + 0x100) == 1) {
    if (UINT_00803f9c == 0) {
      iVar2 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x44))(*(int **)g_pDDrawPrimary,&local_4);
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
        (**(code_std **)(**(int **)g_pDDrawPrimary + 0x68))(*(int **)g_pDDrawPrimary,unaff_ESI);
        return 1;
      }
    }
    else {
      iVar2 = (**(code_std **)(**(int **)g_pDDrawBack + 0x44))(*(int **)g_pDDrawBack,&local_4);
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
        (**(code_std **)(**(int **)g_pDDrawBack + 0x68))(*(int **)g_pDDrawBack,unaff_ESI);
        return 1;
      }
    }
  }
  return 0;
}
#undef local_4

#endif


/* ---- 0x00475000  Display_FindClosestDevice ---- */
uint __cdecl Display_FindClosestDevice(uint *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
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
      if ((((puVar3[4] == param_1[4]) && (uVar2 = 1, *puVar3 == *param_1)) &&
          (uVar2 = 2, puVar3[3] == param_1[3])) &&
         ((uVar2 = 3, puVar3[2] == param_1[2] && (uVar2 = 4, puVar3[1] == param_1[1])))) {
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
#undef local_4


/* ---- 0x00475090  Display_FindClosestMode ---- */
uint __cdecl Display_FindClosestMode(void *wanted,void *modes,uint count)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = 0;
  if (g_dwVideoModeCount == 0) {
    return uVar1;
  }
  uVar4 = 0;
  local_4 = 0;
  if (count != 0) {
    piVar3 = (int *)((int)modes + 0x20);
    do {
      uVar2 = 0;
      if ((((piVar3[-1] == *(int *)((int)wanted + 0x1c)) &&
           (uVar2 = 1, *piVar3 == *(int *)((int)wanted + 0x20))) &&
          (uVar2 = 2, piVar3[-6] == *(int *)((int)wanted + 8))) &&
         (uVar2 = 3, piVar3[-5] == *(int *)((int)wanted + 0xc))) {
        uVar2 = 4;
        if (*(int *)((int)wanted + 0x1c) != 1) {
          return uVar1;
        }
        if (((piVar3[1] == *(int *)((int)wanted + 0x24)) &&
            (piVar3[2] == *(int *)((int)wanted + 0x28))) &&
           (piVar3[3] == *(int *)((int)wanted + 0x2c))) {
          return uVar1;
        }
      }
      if (uVar4 < uVar2) {
        uVar4 = uVar2;
        local_4 = uVar1;
      }
      piVar3 = piVar3 + 0x15;
      uVar1 = uVar1 + 1;
    } while (uVar1 < count);
  }
  return local_4;
}
#undef local_4


/* ---- 0x00475140  Display_CompareVideoModes ---- */
/* qsort comparator of Display_SelectDevice for the video mode list. */

int __cdecl Display_CompareVideoModes(int *param_1,int *param_2)

{
  if (*param_1 == 0) {
    if (*param_2 == 0) goto LAB_00475180;
  }
  else if (*param_2 == 0) {
    return (-(uint)(param_1[2] != param_2[2]) & 0xfffffffe) + 1;
  }
  if (*param_1 == 0) {
    return (-(uint)(param_2[2] != param_1[2]) & 2) - 1;
  }
LAB_00475180:
  if (param_1[8] != param_2[8]) {
    return param_1[8] - param_2[8];
  }
  if (param_1[2] != param_2[2]) {
    return param_1[2] - param_2[2];
  }
  return param_1[3] - param_2[3];
}

/* ---- 0x004751b0  Surface_BlitSoftware ---- */
/* System memory blit for 8/16/24/32 bpp, with colour key when flags & 1 */

int __cdecl Surface_BlitSoftware(void *dst,void *src,uint x,uint y,int *srcRect,uint flags)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  short *psVar5;
  char *pcVar6;
  int iVar7;
  uint n;
  int *piVar8;
  short *psVar9;
  char *pcVar10;
  uint uVar11;
  int iVar12;
  void *pvVar13;
  uint uVar14;
  int iVar15;
  
  pvVar2 = src;
  if (srcRect == (int *)0x0) {
    iVar12 = *(int *)((int)src + 0xc);
    iVar7 = *(int *)((int)src + 0x10);
    src = (void *)0x0;
    iVar3 = 0;
  }
  else {
    src = (void *)*srcRect;
    iVar3 = srcRect[1];
    iVar12 = srcRect[2];
    iVar7 = srcRect[3];
  }
  if (((((int)x < *(int *)((int)dst + 0xc)) && (iVar12 + x != 0)) &&
      ((int)y < *(int *)((int)dst + 0x10))) && (iVar7 + y != 0)) {
    uVar11 = (iVar12 + x) - 1;
    uVar14 = (iVar7 + y) - 1;
    if ((int)y < 0) {
      iVar3 = iVar3 - y;
      y = 0;
    }
    if (*(uint *)((int)dst + 0x10) <= uVar14) {
      uVar14 = *(uint *)((int)dst + 0x10) - 1;
    }
    if ((int)x < 0) {
      src = (void *)((int)src - x);
      x = 0;
    }
    if (*(uint *)((int)dst + 0xc) <= uVar11) {
      uVar11 = *(uint *)((int)dst + 0xc) - 1;
    }
    iVar12 = (uVar11 - x) + 1;
    if (iVar12 != 0) {
      n = (*(uint *)((int)pvVar2 + 0x24) >> 3) * iVar12;
      switch(*(undefined4 *)((int)pvVar2 + 0x24)) {
      case 8:
        if ((flags & 1) == 0) {
          flags = iVar3 * *(int *)((int)pvVar2 + 0x1c) + *(int *)((int)pvVar2 + 0x5c) + (int)src;
          pvVar13 = (void *)(y * *(int *)((int)dst + 0x1c) + *(int *)((int)dst + 0x5c) + x);
          if (y <= uVar14) {
            iVar3 = (uVar14 - y) + 1;
            do {
              Mem_Copy(pvVar13,(void *)flags,n);
              flags = flags + *(int *)((int)pvVar2 + 0x1c);
              pvVar13 = (void *)((int)pvVar13 + *(int *)((int)dst + 0x1c));
              iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
          }
        }
        else {
          iVar7 = *(int *)((int)pvVar2 + 0x1c);
          iVar1 = *(int *)((int)dst + 0x1c);
          pcVar6 = (char *)(iVar3 * *(int *)((int)pvVar2 + 0x1c) + *(int *)((int)pvVar2 + 0x5c) +
                           (int)src);
          pcVar10 = (char *)(y * *(int *)((int)dst + 0x1c) + *(int *)((int)dst + 0x5c) + x);
          if (y <= uVar14) {
            iVar3 = (uVar14 - y) + 1;
            do {
              iVar15 = iVar12;
              if (x <= uVar11) {
                do {
                  if (*pcVar6 != *(char *)((int)pvVar2 + 0x60)) {
                    *pcVar10 = *pcVar6;
                  }
                  pcVar6 = pcVar6 + 1;
                  pcVar10 = pcVar10 + 1;
                  iVar15 = iVar15 + -1;
                } while (iVar15 != 0);
              }
              pcVar10 = pcVar10 + (iVar1 - iVar12);
              pcVar6 = pcVar6 + (iVar7 - iVar12);
              iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
            return 1;
          }
        }
        break;
      case 0x10:
        if ((flags & 1) == 0) {
          pvVar13 = (void *)(*(int *)((int)pvVar2 + 0x5c) +
                            (int)(iVar3 * *(int *)((int)pvVar2 + 0x1c) + (int)src) * 2);
          x = *(int *)((int)dst + 0x5c) + (y * *(int *)((int)dst + 0x1c) + x) * 2;
          if (y <= uVar14) {
            iVar3 = (uVar14 - y) + 1;
            do {
              Mem_Copy((void *)x,pvVar13,n);
              pvVar13 = (void *)((int)pvVar13 + *(int *)((int)pvVar2 + 0x1c) * 2);
              iVar3 = iVar3 + -1;
              x = x + *(int *)((int)dst + 0x1c) * 2;
            } while (iVar3 != 0);
            return 1;
          }
        }
        else {
          iVar7 = *(int *)((int)pvVar2 + 0x1c);
          iVar1 = *(int *)((int)dst + 0x1c);
          psVar5 = (short *)(*(int *)((int)pvVar2 + 0x5c) +
                            (int)(iVar3 * *(int *)((int)pvVar2 + 0x1c) + (int)src) * 2);
          psVar9 = (short *)(*(int *)((int)dst + 0x5c) + (y * *(int *)((int)dst + 0x1c) + x) * 2);
          if (y <= uVar14) {
            iVar3 = (uVar14 - y) + 1;
            do {
              iVar15 = iVar12;
              if (x <= uVar11) {
                do {
                  if (*psVar5 != *(short *)((int)pvVar2 + 0x60)) {
                    *psVar9 = *psVar5;
                  }
                  psVar5 = psVar5 + 1;
                  psVar9 = psVar9 + 1;
                  iVar15 = iVar15 + -1;
                } while (iVar15 != 0);
              }
              iVar3 = iVar3 + -1;
              psVar9 = psVar9 + (iVar1 - iVar12);
              psVar5 = psVar5 + (iVar7 - iVar12);
            } while (iVar3 != 0);
            return 1;
          }
        }
        break;
      case 0x18:
        flags = iVar3 * *(int *)((int)pvVar2 + 0x18) + *(int *)((int)pvVar2 + 0x5c) + (int)src * 3;
        pvVar13 = (void *)(y * *(int *)((int)dst + 0x18) + *(int *)((int)dst + 0x5c) + x * 3);
        if (y <= uVar14) {
          iVar3 = (uVar14 - y) + 1;
          do {
            Mem_Copy(pvVar13,(void *)flags,n);
            flags = flags + *(int *)((int)pvVar2 + 0x18);
            pvVar13 = (void *)((int)pvVar13 + *(int *)((int)dst + 0x18));
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
          return 1;
        }
        break;
      case 0x20:
        if ((flags & 1) == 0) {
          pvVar13 = (void *)(*(int *)((int)pvVar2 + 0x5c) +
                            (int)(iVar3 * *(int *)((int)pvVar2 + 0x1c) + (int)src) * 4);
          x = *(int *)((int)dst + 0x5c) + (y * *(int *)((int)dst + 0x1c) + x) * 4;
          if (y <= uVar14) {
            iVar3 = (uVar14 - y) + 1;
            do {
              Mem_Copy((void *)x,pvVar13,n);
              pvVar13 = (void *)((int)pvVar13 + *(int *)((int)pvVar2 + 0x1c) * 4);
              iVar3 = iVar3 + -1;
              x = x + *(int *)((int)dst + 0x1c) * 4;
            } while (iVar3 != 0);
            return 1;
          }
        }
        else {
          iVar7 = *(int *)((int)pvVar2 + 0x1c);
          iVar1 = *(int *)((int)dst + 0x1c);
          piVar4 = (int *)(*(int *)((int)pvVar2 + 0x5c) +
                          (int)(iVar3 * *(int *)((int)pvVar2 + 0x1c) + (int)src) * 4);
          piVar8 = (int *)(*(int *)((int)dst + 0x5c) + (y * *(int *)((int)dst + 0x1c) + x) * 4);
          if (y <= uVar14) {
            iVar3 = (uVar14 - y) + 1;
            do {
              iVar15 = iVar12;
              if (x <= uVar11) {
                do {
                  if (*piVar4 != *(int *)((int)pvVar2 + 0x60)) {
                    *piVar8 = *piVar4;
                  }
                  piVar4 = piVar4 + 1;
                  piVar8 = piVar8 + 1;
                  iVar15 = iVar15 + -1;
                } while (iVar15 != 0);
              }
              iVar3 = iVar3 + -1;
              piVar8 = piVar8 + (iVar1 - iVar12);
              piVar4 = piVar4 + (iVar7 - iVar12);
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
uint __cdecl
Surface_BlitDDraw(int param_1,int param_2,uint param_3,uint param_4,uint *param_5,byte param_6)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  undefined4 uVar6;
  #define local_84 (*(uint *)(_frame + (0xa0 - 0x84)))
  #define local_80 (*(uint *)(_frame + (0xa0 - 0x80)))
  #define local_7c (*(uint *)(_frame + (0xa0 - 0x7c)))
  #define local_78 (*(uint *)(_frame + (0xa0 - 0x78)))
  #define local_74 (*(uint *)(_frame + (0xa0 - 0x74)))
  #define local_70 (*(uint *)(_frame + (0xa0 - 0x70)))
  #define local_6c (*(uint *)(_frame + (0xa0 - 0x6c)))
  #define local_68 (*(uint *)(_frame + (0xa0 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0xa0 - 0x64)))
  
  if ((*(int *)(param_1 + 4) != 0) || (*(int *)(param_2 + 4) != 0)) {
    return 0;
  }
  if ((*(int *)(param_1 + 8) == 0) || (*(int *)(param_2 + 8) == 0)) {
    local_74 = param_3;
    local_70 = param_4;
    if (param_5 == (uint *)0x0) {
      local_7c = *(uint *)(param_2 + 0xc);
      local_84 = 0;
      local_80 = 0;
      uVar2 = *(uint *)(param_2 + 0x10);
      local_78 = uVar2;
      uVar1 = local_7c;
    }
    else {
      uVar1 = param_5[2];
      if (uVar1 == 0) {
        return 0;
      }
      uVar2 = param_5[3];
      if (uVar2 == 0) {
        return 0;
      }
      local_84 = *param_5;
      local_80 = param_5[1];
      local_7c = local_84 + uVar1;
      local_78 = local_80 + uVar2;
    }
    local_6c = param_3 + uVar1;
    local_68 = param_4 + uVar2;
    puVar5 = &local_64;
    for (iVar4 = 0x19; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    local_64 = 100;
    uVar6 = 0x1000000;
    if ((param_6 & 1) != 0) {
      uVar6 = 0x1008000;
    }
    while (iVar4 = (**(code_std **)(**(int **)(param_1 + 100) + 0x14))
                             (*(int **)(param_1 + 100),&local_74,*(undefined4 *)(param_2 + 100),
                              &local_84,uVar6,&local_64), iVar4 != 0) {
      if (iVar4 == -0x7789fe3e) {
        if ((*(byte *)(param_1 + 0xd4) & 4) == 0) {
          iVar4 = (**(code_std **)(**(int **)(param_1 + 100) + 0x6c))(*(int **)(param_1 + 100));
        }
        else {
          iVar4 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x6c))(*(int **)g_pDDrawPrimary);
        }
        if (iVar4 != 0) {
          return 0;
        }
        if ((*(byte *)(param_2 + 0xd4) & 4) == 0) {
          iVar3 = (**(code_std **)(**(int **)(param_2 + 100) + 0x6c))(*(int **)(param_2 + 100));
        }
        else {
          iVar3 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x6c))(*(int **)g_pDDrawPrimary);
        }
        iVar4 = 0;
        if (iVar3 != 0) {
          return 0;
        }
      }
      if (iVar4 != 0) {
        return 0;
      }
    }
  }
  else {
    if (param_5 == (uint *)0x0) {
      local_7c = *(uint *)(param_2 + 0xc);
      local_84 = 0;
      local_80 = 0;
      local_78 = *(uint *)(param_2 + 0x10);
    }
    else {
      if (param_5[2] == 0) {
        return 0;
      }
      if (param_5[3] == 0) {
        return 0;
      }
      local_84 = *param_5;
      local_80 = param_5[1];
      local_7c = local_84 + param_5[2];
      local_78 = local_80 + param_5[3];
    }
    puVar5 = &local_64;
    for (iVar4 = 0x19; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    local_64 = 100;
    uVar6 = 0x10;
    if ((param_6 & 1) != 0) {
      uVar6 = 0x11;
    }
    while (iVar4 = (**(code_std **)(**(int **)(param_1 + 100) + 0x1c))
                             (*(int **)(param_1 + 100),param_3,param_4,
                              *(undefined4 *)(param_2 + 100),&local_84,uVar6), iVar4 != 0) {
      if (iVar4 == -0x7789fe3e) {
        if ((*(byte *)(param_1 + 0xd4) & 4) == 0) {
          iVar4 = (**(code_std **)(**(int **)(param_1 + 100) + 0x6c))(*(int **)(param_1 + 100));
        }
        else {
          iVar4 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x6c))(*(int **)g_pDDrawPrimary);
        }
        if (iVar4 != 0) {
          return 0;
        }
        if ((*(byte *)(param_2 + 0xd4) & 4) == 0) {
          iVar3 = (**(code_std **)(**(int **)(param_2 + 100) + 0x6c))(*(int **)(param_2 + 100));
        }
        else {
          iVar3 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x6c))(*(int **)g_pDDrawPrimary);
        }
        iVar4 = 0;
        if (iVar3 != 0) {
          return 0;
        }
      }
      if (iVar4 != 0) {
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
Surface_BlitLockedSrc
          (void *param_1,int param_2,void *param_3,uint param_4,int *param_5,void *param_6)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  short *psVar5;
  char *pcVar6;
  void *pvVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int *piVar12;
  short *psVar13;
  char *pcVar14;
  void *pvVar15;
  int iVar16;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = param_2;
  if (*(int *)((int)param_1 + 4) == 0) {
    if (param_5 == (int *)0x0) {
      iVar8 = *(int *)(param_2 + 0xc);
      iVar9 = *(int *)(param_2 + 0x10);
      param_2 = 0;
      iVar11 = 0;
    }
    else {
      iVar8 = param_5[2];
      if (iVar8 == 0) {
        return 0;
      }
      iVar9 = param_5[3];
      if (iVar9 == 0) {
        return 0;
      }
      param_2 = *param_5;
      iVar11 = param_5[1];
    }
    pvVar15 = *(void **)((int)param_1 + 0xc);
    if (((((int)param_3 < (int)pvVar15) && (iVar8 + (int)param_3 != 0)) &&
        (uVar3 = *(uint *)((int)param_1 + 0x10), (int)param_4 < (int)uVar3)) &&
       (iVar9 + param_4 != 0)) {
      pvVar7 = (void *)((iVar8 + (int)param_3) - 1);
      uVar10 = (iVar9 + param_4) - 1;
      if ((int)param_4 < 0) {
        iVar11 = iVar11 - param_4;
        param_4 = 0;
      }
      if (uVar3 <= uVar10) {
        uVar10 = uVar3 - 1;
      }
      if ((int)param_3 < 0) {
        param_2 = param_2 - (int)param_3;
        param_3 = (void *)0x0;
      }
      if (pvVar15 <= pvVar7) {
        pvVar7 = (void *)((int)pvVar15 - 1);
      }
      iVar8 = (int)pvVar7 + (1 - (int)param_3);
      if (iVar8 != 0) {
        uVar3 = (*(uint *)(iVar2 + 0x24) >> 3) * iVar8;
        stdDisplay_VBufferLock(param_1);
        iVar9 = *(int *)(iVar2 + 0x24);
        if (iVar9 == 8) {
          if (((uint)param_6 & 1) == 0) {
            param_6 = (void *)(iVar11 * *(int *)(iVar2 + 0x1c) + *(int *)(iVar2 + 0x5c) + param_2);
            pvVar15 = (void *)(param_4 * *(int *)((int)param_1 + 0x1c) +
                               *(int *)((int)param_1 + 0x5c) + (int)param_3);
            if (param_4 <= uVar10) {
              iVar8 = (uVar10 - param_4) + 1;
              do {
                Mem_Copy(pvVar15,param_6,uVar3);
                param_6 = (void *)((int)param_6 + *(int *)(iVar2 + 0x1c));
                pvVar15 = (void *)((int)pvVar15 + *(int *)((int)param_1 + 0x1c));
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
            }
          }
          else {
            iVar9 = *(int *)(iVar2 + 0x1c);
            iVar1 = *(int *)((int)param_1 + 0x1c);
            pcVar14 = (char *)(iVar11 * iVar9 + *(int *)(iVar2 + 0x5c) + param_2);
            pcVar6 = (char *)(param_4 * *(int *)((int)param_1 + 0x1c) +
                              *(int *)((int)param_1 + 0x5c) + (int)param_3);
            if (param_4 <= uVar10) {
              iVar11 = (uVar10 - param_4) + 1;
              do {
                iVar16 = iVar8;
                if (param_3 <= pvVar7) {
                  do {
                    if (*pcVar14 != *(char *)(iVar2 + 0x60)) {
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
          if (((uint)param_6 & 1) == 0) {
            pvVar15 = (void *)(*(int *)(iVar2 + 0x5c) +
                              (iVar11 * *(int *)(iVar2 + 0x1c) + param_2) * 2);
            param_3 = (void *)(*(int *)((int)param_1 + 0x5c) +
                              (int)(param_4 * *(int *)((int)param_1 + 0x1c) + (int)param_3) * 2);
            if (param_4 <= uVar10) {
              iVar8 = (uVar10 - param_4) + 1;
              do {
                Mem_Copy(param_3,pvVar15,uVar3);
                iVar8 = iVar8 + -1;
                pvVar15 = (void *)((int)pvVar15 + *(int *)(iVar2 + 0x1c) * 2);
                param_3 = (void *)((int)param_3 + *(int *)((int)param_1 + 0x1c) * 2);
              } while (iVar8 != 0);
            }
          }
          else {
            iVar9 = *(int *)(iVar2 + 0x1c);
            iVar1 = *(int *)((int)param_1 + 0x1c);
            psVar13 = (short *)(*(int *)(iVar2 + 0x5c) + (iVar11 * iVar9 + param_2) * 2);
            psVar5 = (short *)(*(int *)((int)param_1 + 0x5c) +
                              (int)(param_4 * *(int *)((int)param_1 + 0x1c) + (int)param_3) * 2);
            if (param_4 <= uVar10) {
              iVar11 = (uVar10 - param_4) + 1;
              do {
                iVar16 = iVar8;
                if (param_3 <= pvVar7) {
                  do {
                    if (*psVar13 != *(short *)(iVar2 + 0x60)) {
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
          if (((uint)param_6 & 1) == 0) {
            pvVar15 = (void *)(*(int *)(iVar2 + 0x5c) +
                              (iVar11 * *(int *)(iVar2 + 0x1c) + param_2) * 4);
            param_3 = (void *)(*(int *)((int)param_1 + 0x5c) +
                              (int)(param_4 * *(int *)((int)param_1 + 0x1c) + (int)param_3) * 4);
            if (param_4 <= uVar10) {
              iVar8 = (uVar10 - param_4) + 1;
              do {
                Mem_Copy(param_3,pvVar15,uVar3);
                iVar8 = iVar8 + -1;
                pvVar15 = (void *)((int)pvVar15 + *(int *)(iVar2 + 0x1c) * 4);
                param_3 = (void *)((int)param_3 + *(int *)((int)param_1 + 0x1c) * 4);
              } while (iVar8 != 0);
            }
          }
          else {
            iVar9 = *(int *)(iVar2 + 0x1c);
            iVar1 = *(int *)((int)param_1 + 0x1c);
            piVar12 = (int *)(*(int *)(iVar2 + 0x5c) + (iVar11 * iVar9 + param_2) * 4);
            piVar4 = (int *)(*(int *)((int)param_1 + 0x5c) +
                            (int)(param_4 * *(int *)((int)param_1 + 0x1c) + (int)param_3) * 4);
            if (param_4 <= uVar10) {
              iVar11 = (uVar10 - param_4) + 1;
              do {
                iVar16 = iVar8;
                if (param_3 <= pvVar7) {
                  do {
                    if (*piVar12 != *(int *)(iVar2 + 0x60)) {
                      *piVar4 = *piVar12;
                    }
                    piVar12 = piVar12 + 1;
                    piVar4 = piVar4 + 1;
                    iVar16 = iVar16 + -1;
                  } while (iVar16 != 0);
                }
                iVar11 = iVar11 + -1;
                piVar4 = piVar4 + (iVar1 - iVar8);
                piVar12 = piVar12 + (iVar9 - iVar8);
              } while (iVar11 != 0);
            }
          }
        }
        stdDisplay_VBufferUnlock(param_1);
      }
      return 1;
    }
  }
  return 0;
}
#undef local_4


/* ---- 0x00475c90  Surface_BlitLockedDst ---- */
uint __cdecl
Surface_BlitLockedDst
          (int param_1,void *param_2,void *param_3,uint param_4,int *param_5,void *param_6)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *surface;
  int iVar2;
  uint n;
  int *piVar3;
  int iVar4;
  short *psVar5;
  char *pcVar6;
  int iVar7;
  void *pvVar8;
  int iVar9;
  int *piVar10;
  short *psVar11;
  char *pcVar12;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  surface = param_2;
  iVar7 = param_1;
  if (*(int *)((int)param_2 + 4) == 0) {
    if (param_5 == (int *)0x0) {
      iVar4 = *(int *)((int)param_2 + 0xc);
      iVar2 = 0;
      iVar9 = 0;
      param_2 = *(void **)((int)param_2 + 0x10);
    }
    else {
      iVar4 = param_5[2];
      if (iVar4 == 0) {
        return 0;
      }
      if ((void *)param_5[3] == (void *)0x0) {
        return 0;
      }
      iVar2 = *param_5;
      iVar9 = param_5[1];
      param_2 = (void *)param_5[3];
    }
    if (((((int)param_3 < *(int *)(param_1 + 0xc)) && (iVar4 + (int)param_3 != 0)) &&
        ((int)param_4 < *(int *)(param_1 + 0x10))) && ((int)param_2 + param_4 != 0)) {
      pvVar8 = (void *)((iVar4 + (int)param_3) - 1);
      param_5 = (int *)(((int)param_2 + param_4) - 1);
      if ((int)param_4 < 0) {
        iVar9 = iVar9 - param_4;
        param_4 = 0;
      }
      if (*(int **)(param_1 + 0x10) <= param_5) {
        param_5 = (int *)((int)*(int **)(param_1 + 0x10) - 1);
      }
      param_1 = iVar2;
      if ((int)param_3 < 0) {
        param_1 = iVar2 - (int)param_3;
        param_3 = (void *)0x0;
      }
      if (*(void **)(iVar7 + 0xc) <= pvVar8) {
        pvVar8 = (void *)((int)*(void **)(iVar7 + 0xc) - 1);
      }
      iVar4 = (int)pvVar8 + (1 - (int)param_3);
      if (iVar4 != 0) {
        n = (*(uint *)((int)surface + 0x24) >> 3) * iVar4;
        stdDisplay_VBufferLock(surface);
        iVar2 = *(int *)((int)surface + 0x24);
        if (iVar2 == 8) {
          if (((uint)param_6 & 1) == 0) {
            param_6 = (void *)(iVar9 * *(int *)((int)surface + 0x1c) + *(int *)((int)surface + 0x5c)
                              + param_1);
            pvVar8 = (void *)(param_4 * *(int *)(iVar7 + 0x1c) + *(int *)(iVar7 + 0x5c) +
                             (int)param_3);
            if (param_4 <= param_5) {
              iVar4 = (int)param_5 + (1 - param_4);
              do {
                Mem_Copy(pvVar8,param_6,n);
                param_6 = (void *)((int)param_6 + *(int *)((int)surface + 0x1c));
                pvVar8 = (void *)((int)pvVar8 + *(int *)(iVar7 + 0x1c));
                iVar4 = iVar4 + -1;
              } while (iVar4 != 0);
            }
          }
          else {
            iVar2 = *(int *)((int)surface + 0x1c);
            iVar1 = *(int *)(iVar7 + 0x1c);
            pcVar12 = (char *)(iVar9 * iVar2 + *(int *)((int)surface + 0x5c) + param_1);
            pcVar6 = (char *)(param_4 * *(int *)(iVar7 + 0x1c) + *(int *)(iVar7 + 0x5c) +
                             (int)param_3);
            if (param_4 <= param_5) {
              iVar7 = (int)param_5 + (1 - param_4);
              do {
                iVar9 = iVar4;
                if (param_3 <= pvVar8) {
                  do {
                    if (*pcVar12 != *(char *)((int)surface + 0x60)) {
                      *pcVar6 = *pcVar12;
                    }
                    pcVar12 = pcVar12 + 1;
                    pcVar6 = pcVar6 + 1;
                    iVar9 = iVar9 + -1;
                  } while (iVar9 != 0);
                }
                pcVar6 = pcVar6 + (iVar1 - iVar4);
                pcVar12 = pcVar12 + (iVar2 - iVar4);
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
              stdDisplay_VBufferUnlock(surface);
              return 1;
            }
          }
        }
        else if (iVar2 == 0x10) {
          if (((uint)param_6 & 1) == 0) {
            pvVar8 = (void *)(*(int *)((int)surface + 0x5c) +
                             (iVar9 * *(int *)((int)surface + 0x1c) + param_1) * 2);
            param_3 = (void *)(*(int *)(iVar7 + 0x5c) +
                              (int)(param_4 * *(int *)(iVar7 + 0x1c) + (int)param_3) * 2);
            if (param_4 <= param_5) {
              iVar4 = (int)param_5 + (1 - param_4);
              do {
                Mem_Copy(param_3,pvVar8,n);
                pvVar8 = (void *)((int)pvVar8 + *(int *)((int)surface + 0x1c) * 2);
                iVar4 = iVar4 + -1;
                param_3 = (void *)((int)param_3 + *(int *)(iVar7 + 0x1c) * 2);
              } while (iVar4 != 0);
              stdDisplay_VBufferUnlock(surface);
              return 1;
            }
          }
          else {
            iVar2 = *(int *)((int)surface + 0x1c);
            iVar1 = *(int *)(iVar7 + 0x1c);
            psVar11 = (short *)(*(int *)((int)surface + 0x5c) + (iVar9 * iVar2 + param_1) * 2);
            psVar5 = (short *)(*(int *)(iVar7 + 0x5c) +
                              (int)(param_4 * *(int *)(iVar7 + 0x1c) + (int)param_3) * 2);
            if (param_4 <= param_5) {
              iVar7 = (int)param_5 + (1 - param_4);
              do {
                iVar9 = iVar4;
                if (param_3 <= pvVar8) {
                  do {
                    if (*psVar11 != *(short *)((int)surface + 0x60)) {
                      *psVar5 = *psVar11;
                    }
                    psVar11 = psVar11 + 1;
                    psVar5 = psVar5 + 1;
                    iVar9 = iVar9 + -1;
                  } while (iVar9 != 0);
                }
                iVar7 = iVar7 + -1;
                psVar5 = psVar5 + (iVar1 - iVar4);
                psVar11 = psVar11 + (iVar2 - iVar4);
              } while (iVar7 != 0);
              stdDisplay_VBufferUnlock(surface);
              return 1;
            }
          }
        }
        else if (iVar2 == 0x20) {
          if (((uint)param_6 & 1) == 0) {
            pvVar8 = (void *)(*(int *)((int)surface + 0x5c) +
                             (iVar9 * *(int *)((int)surface + 0x1c) + param_1) * 4);
            param_3 = (void *)(*(int *)(iVar7 + 0x5c) +
                              (int)(param_4 * *(int *)(iVar7 + 0x1c) + (int)param_3) * 4);
            if (param_4 <= param_5) {
              iVar4 = (int)param_5 + (1 - param_4);
              do {
                Mem_Copy(param_3,pvVar8,n);
                pvVar8 = (void *)((int)pvVar8 + *(int *)((int)surface + 0x1c) * 4);
                iVar4 = iVar4 + -1;
                param_3 = (void *)((int)param_3 + *(int *)(iVar7 + 0x1c) * 4);
              } while (iVar4 != 0);
              stdDisplay_VBufferUnlock(surface);
              return 1;
            }
          }
          else {
            iVar2 = *(int *)((int)surface + 0x1c);
            iVar1 = *(int *)(iVar7 + 0x1c);
            piVar10 = (int *)(*(int *)((int)surface + 0x5c) + (iVar9 * iVar2 + param_1) * 4);
            piVar3 = (int *)(*(int *)(iVar7 + 0x5c) +
                            (int)(param_4 * *(int *)(iVar7 + 0x1c) + (int)param_3) * 4);
            if (param_4 <= param_5) {
              iVar7 = (int)param_5 + (1 - param_4);
              do {
                iVar9 = iVar4;
                if (param_3 <= pvVar8) {
                  do {
                    if (*piVar10 != *(int *)((int)surface + 0x60)) {
                      *piVar3 = *piVar10;
                    }
                    piVar10 = piVar10 + 1;
                    piVar3 = piVar3 + 1;
                    iVar9 = iVar9 + -1;
                  } while (iVar9 != 0);
                }
                iVar7 = iVar7 + -1;
                piVar3 = piVar3 + (iVar1 - iVar4);
                piVar10 = piVar10 + (iVar2 - iVar4);
              } while (iVar7 != 0);
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
#undef local_4


/* ---- 0x004760d0  DDraw_Create ---- */
int __cdecl DDraw_Create(uint param_1)

{
  int iVar1;
  
  if (*(int *)((int)g_pDisplayDevice + 0x10c) == 0) {
    iVar1 = (int)g_pDisplayDevice + 0x288;
  }
  else {
    iVar1 = 0;
  }
  iVar1 = DirectDrawCreate(iVar1,((unsigned)(uintptr_t)&g_pDirectDraw),0);
  if (iVar1 != 0) {
    return 0;
  }
  g_dwVideoModeCount = 0;
  iVar1 = (**(code_std **)(*(int *)g_pDirectDraw + 0x50))(g_pDirectDraw,param_1,0x51);
  if (iVar1 != 0) {
    return 0;
  }
  iVar1 = (**(code_std **)(*(int *)g_pDirectDraw + 0x20))
                    (g_pDirectDraw,0,0,0,DDraw_EnumModesCallback320);
  if (iVar1 != 0) {
    return 0;
  }
  iVar1 = (**(code_std **)(*(int *)g_pDirectDraw + 0x50))(g_pDirectDraw,param_1,0x11);
  if (iVar1 != 0) {
    return 0;
  }
  iVar1 = (**(code_std **)(*(int *)g_pDirectDraw + 0x20))(g_pDirectDraw,0,0,0,DDraw_EnumModesCallback);
  if (iVar1 != 0) {
    return 0;
  }
  iVar1 = (**(code_std **)(*(int *)g_pDirectDraw + 0x50))(g_pDirectDraw,param_1,8);
  return (uint)(iVar1 == 0);
}

/* ---- 0x00476190  DDraw_Release ---- */
void __cdecl DDraw_Release(void)

{
  if (g_pDirectDraw != (void *)0x0) {
    (**(code_std **)(*(int *)g_pDirectDraw + 8))(g_pDirectDraw);
    g_pDirectDraw = (void *)0x0;
  }
  return;
}

/* ---- 0x004761b0  FUN_004761b0 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
    */

undefined * __stdcall FUN_004761b0(int a1,int a2,int a3,int a4)

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

undefined4 __cdecl DDraw_CreateSurfaces(undefined4 hwnd,int *mode,byte *palette)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[1104] __attribute__((aligned(16)));  /* the original frame below the return address */
  int *src;
  undefined1 uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  uint uVar5;
  uint *puVar6;
  void *pvVar7;
  #define puStack_28 (*(undefined1 **)(_frame + (0x40 - 0x28)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x40 - 0x10)))
  
  uVar5 = 0x11;
  if ((UINT_00803f9c != 0) && (*mode != 0)) {
    uVar5 = 0x51;
  }
  iVar2 = (**(code_std **)(*(int *)g_pDirectDraw + 0x50))();
  if (iVar2 != 0) {
    return 0;
  }
  src = mode + 2;
  UINT_00803fb0 = uVar5;
  iVar2 = (**(code_std **)(*(int *)g_pDirectDraw + 0x54))();
  if (iVar2 != 0) {
    return 0;
  }
  g_dwStdDisplay_frontBuffer = 1;
  _DAT_00901684 = 0;
  _DAT_00901688 = 0;
  Mem_Copy(&DAT_0090168c,src,0x4c);
  _DAT_009016d8 = uStack_10;
  UINT_009016dc = 0;
  g_pDDrawPrimary = &UINT_009016e4;
  puVar6 = &UINT_009016ec;
  for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  *(int *)((int)g_pDDrawPrimary + 0x14) = *src;
  *(int *)((int)g_pDDrawPrimary + 0x10) = mode[3];
  *(undefined4 *)((int)g_pDDrawPrimary + 8) = 0x6c;
  *(undefined4 *)((int)g_pDDrawPrimary + 4) = 0;
  if (UINT_00803f9c == 0) {
    *(undefined4 *)((int)g_pDDrawPrimary + 0xc) = 1;
    *(undefined4 *)((int)g_pDDrawPrimary + 0x70) = 0x2200;
  }
  else {
    *(undefined4 *)((int)g_pDDrawPrimary + 0x1c) = 1;
    *(undefined4 *)((int)g_pDDrawPrimary + 0xc) = 0x21;
    *(undefined4 *)((int)g_pDDrawPrimary + 0x70) = 0x2218;
  }
  pvVar7 = g_pDDrawPrimary;
  iVar2 = (**(code_std **)(*(int *)g_pDirectDraw + 0x18))(g_pDirectDraw,(int)g_pDDrawPrimary + 8);
  if (iVar2 != 0) {
    return 0;
  }
  iVar2 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x58))
                    (*(int **)g_pDDrawPrimary,(int)g_pDDrawPrimary + 8);
  if (iVar2 != 0) {
    return 0;
  }
  g_dwStdDisplay_numDrawBuffers = *(int *)((int)g_pDDrawPrimary + 0x1c) + 1;
  UINT_00901698 = *(uint *)((int)g_pDDrawPrimary + 0x18);
  _DAT_0090169c = UINT_00901698 / (uint)pvVar7;
  if ((*(uint *)((int)g_pDDrawPrimary + 0x70) & 0x4000) != 0) {
    _DAT_00901688 = 1;
  }
  if (UINT_00803f9c != 0) {
    g_dwStdDisplay_backBuffer = 1;
    _DAT_009055e4 = 0;
    _DAT_009055e8 = 0;
    Mem_Copy(&UINT_009055ec,src,0x4c);
    _DAT_00905638 = puStack_28;
    UINT_0090563c = 0;
    g_pDDrawBack = &PTR_00905644;
    puVar6 = &UINT_0090564c;
    for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    *(int *)((int)g_pDDrawBack + 0x14) = *src;
    *(int *)((int)g_pDDrawBack + 0x10) = mode[3];
    *(undefined4 *)((int)g_pDDrawBack + 8) = 0x6c;
    *(undefined4 *)((int)g_pDDrawBack + 0xc) = 0x21;
    *(undefined4 *)((int)g_pDDrawBack + 0x70) = 4;
    *(undefined4 *)((int)g_pDDrawBack + 0x1c) = 1;
    iVar2 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x30))
                      (*(int **)g_pDDrawPrimary,(int)g_pDDrawBack + 0x70,g_pDDrawBack);
    if (iVar2 != 0) {
      return 0;
    }
    iVar2 = (**(code_std **)(**(int **)g_pDDrawBack + 0x58))
                      (*(int **)g_pDDrawBack,(int)g_pDDrawBack + 8);
    if (iVar2 != 0) {
      return 0;
    }
    if ((*(uint *)((int)g_pDDrawBack + 0x70) & 0x4000) != 0) {
      _DAT_009055e8 = 1;
    }
    UINT_009055f8 = *(uint *)((int)g_pDDrawBack + 0x18);
    _DAT_009055fc = UINT_009055f8 / (uint)pvVar7;
    *(undefined4 *)((int)g_pDDrawBack + 4) = 0;
  }
  if (mode[7] == 0) {
    iVar2 = GetDC(0);
    GetSystemPaletteEntries(iVar2,0,0x100,(int)(_stkneg + 28));
    ReleaseDC(0,iVar2);
    iVar2 = 0x100;
    puVar4 = (_stkneg + 28);
    do {
      uVar1 = *puStack_28;
      puVar4[3] = 1;
      *puVar4 = uVar1;
      puVar3 = puStack_28 + 2;
      puVar4[1] = puStack_28[1];
      puStack_28 = puStack_28 + 3;
      puVar4[2] = *puVar3;
      iVar2 = iVar2 + -1;
      puVar4 = puVar4 + 4;
    } while (iVar2 != 0);
    iVar2 = (**(code_std **)(*(int *)g_pDirectDraw + 0x14))
                      (g_pDirectDraw,0x4c,(_stkneg + 28),(int)g_pDDrawPrimary + 4,0);
    if (iVar2 != 0) {
      return 0;
    }
    iVar2 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x7c))
                      (*(int **)g_pDDrawPrimary,*(undefined4 *)((int)g_pDDrawPrimary + 4));
    if (iVar2 != 0) {
      return 0;
    }
    if (UINT_00803f9c == 0) goto LAB_00476b98;
    iVar2 = (**(code_std **)(**(int **)g_pDDrawBack + 0x7c))
                      (*(int **)g_pDDrawBack,*(undefined4 *)((int)g_pDDrawPrimary + 4));
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
#undef puStack_28
#undef uStack_10

#endif


/* ---- 0x00476bc0  DDraw_ReleaseSurfaces ---- */
void __cdecl DDraw_ReleaseSurfaces(void)

{
  if (UINT_00803f9c != 0) {
    UINT_00905648 = 0;
    Surface_Release(&g_dwStdDisplay_backBuffer);
  }
  Surface_Release(&g_dwStdDisplay_frontBuffer);
  return;
}

/* ---- 0x00476bf0  DDraw_LockSurface ---- */
uint __cdecl DDraw_LockSurface(uint *param_1)

{
  int iVar1;
  
  do {
    iVar1 = (**(code_std **)(*(int *)*param_1 + 100))((int *)*param_1,0,param_1 + 2,1,0);
    if (iVar1 == 0) break;
    if (iVar1 == -0x7789fe3e) {
      if ((param_1[0x1c] & 4) == 0) {
        iVar1 = (**(code_std **)(*(int *)*param_1 + 0x6c))((int *)*param_1);
      }
      else {
        iVar1 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x6c))(*(int **)g_pDDrawPrimary);
      }
    }
  } while (iVar1 == 0);
  return param_1[0xb];
}

/* ---- 0x00476c40  DDraw_UnlockSurface ---- */
uint __cdecl DDraw_UnlockSurface(uint *param_1)

{
  int iVar1;
  
  do {
    iVar1 = (**(code_std **)(*(int *)*param_1 + 0x80))((int *)*param_1,0);
    if (iVar1 == 0) {
      return 1;
    }
    if (iVar1 == -0x7789fe3e) {
      if ((param_1[0x1c] & 4) == 0) {
        iVar1 = (**(code_std **)(*(int *)*param_1 + 0x6c))((int *)*param_1);
      }
      else {
        iVar1 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x6c))(*(int **)g_pDDrawPrimary);
      }
    }
  } while (iVar1 == 0);
  return 0;
}

/* ---- 0x00476c90  DDraw_Flip ---- */
uint __cdecl DDraw_Flip(void)

{
  int iVar1;
  int iVar2;
  
  do {
    iVar1 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x2c))(*(int **)g_pDDrawPrimary,0,0);
    if (iVar1 == 0) {
      return 1;
    }
    if (iVar1 == -0x7789fe3e) {
      iVar2 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x6c))(*(int **)g_pDDrawPrimary);
      iVar1 = 0;
      if (iVar2 != 0) {
        return 0;
      }
    }
  } while (iVar1 == -0x7789fde4);
  return 0;
}

/* ---- 0x00476cd0  DDraw_FillSurface ---- */
uint __cdecl DDraw_FillSurface(uint *param_1,uint param_2,uint *param_3)

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
  local_14 = param_2;
  if (param_3 == (uint *)0x0) {
    local_6c = param_1[5];
    local_68 = param_1[4];
    local_74 = 0;
    local_70 = 0;
  }
  else {
    if (param_3[2] == 0) {
      return 0;
    }
    if (param_3[3] == 0) {
      return 0;
    }
    local_74 = *param_3;
    local_70 = param_3[1];
    local_6c = local_74 + param_3[2];
    local_68 = local_70 + param_3[3];
  }
  do {
    iVar1 = (**(code_std **)(*(int *)*param_1 + 0x14))
                      ((int *)*param_1,&local_74,0,0,0x1000400,&local_64);
    if (iVar1 == 0) {
      return 1;
    }
    if (iVar1 == -0x7789fe3e) {
      if ((param_1[0x1c] & 4) == 0) {
        iVar1 = (**(code_std **)(*(int *)*param_1 + 0x6c))((int *)*param_1);
      }
      else {
        iVar1 = (**(code_std **)(**(int **)g_pDDrawPrimary + 0x6c))(*(int **)g_pDDrawPrimary);
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
uint __cdecl DDraw_SetPalette(byte *param_1)

{
  unsigned char _frame[0x410] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  #define local_400 (*(byte (*)[1024])(_frame + (0x410 - 0x400)))
  
  if (*(int *)((int)g_pVideoMode + 0x1c) == 0) {
    iVar3 = 0x100;
    pbVar2 = local_400 + 1;
    do {
      pbVar2[-1] = *param_1;
      pbVar1 = param_1 + 2;
      *pbVar2 = param_1[1];
      param_1 = param_1 + 3;
      pbVar2[1] = *pbVar1;
      iVar3 = iVar3 + -1;
      pbVar2 = pbVar2 + 4;
    } while (iVar3 != 0);
    iVar3 = (**(code_std **)(**(int **)((int)g_pDDrawPrimary + 4) + 0x18))
                      (*(int **)((int)g_pDDrawPrimary + 4),0,0,0x100,local_400);
    if (iVar3 != 0) {
      return 0;
    }
  }
  return 1;
}
#undef local_400


/* ---- 0x00476e40  DIB_CreateSurface ---- */
void * __cdecl DIB_CreateSurface(void *mode,void *surface,void *palette,void *hwnd)

{
  UINT_00803f7c = GetDC((int)hwnd);
  if (*(int *)((int)mode + 0x1c) == 0) {
    UINT_00803fb4 =
         ((code *)stdDisplay_BuildBitmapInfo8)(UINT_00803f7c,*(uint *)((int)mode + 8),*(int *)((int)mode + 0xc),(int)surface,
                    palette);
    if (UINT_00803fb4 == 0) {
      return (void *)0x0;
    }
  }
  else if ((*(int *)((int)mode + 0x1c) == 1) && (*(int *)((int)mode + 0x20) == 0x10)) {
    if (*(int *)((int)mode + 0x28) == 6) {
      UINT_00803fb4 =
           (uint)DIB_CreateSection565
                           (UINT_00803f7c,*(uint *)((int)mode + 8),*(int *)((int)mode + 0xc),
                            (uint)surface);
    }
    else {
      UINT_00803fb4 =
           ((code *)stdDisplay_BuildBitmapInfo16)(UINT_00803f7c,*(uint *)((int)mode + 8),*(int *)((int)mode + 0xc),(int)surface)
      ;
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
  if (*(int *)((int)g_pStd3D_CurDevice + 0x10) != 0) {
    if ((*(int *)UINT_00806938 == 2) && (*(int *)(UINT_00806938 + 4) == 0x10)) {
      stdPcx_DecodeRun8(palette,((unsigned)(uintptr_t)&DAT_008061e8),UINT_00806938);
    }
    if (((*(int *)((int)g_pStd3D_CurDevice + 0x18) == 0) && (*(int *)UINT_0080693c == 2)) &&
       (*(int *)(UINT_0080693c + 4) == 0x10)) {
      stdPcx_DecodeRunMasked(palette,((unsigned)(uintptr_t)&DAT_00805fd8),UINT_0080693c,flags);
    }
  }
  return;
}

/* ---- 0x0047b610  Palette_FromFloatTable ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Writes n RGB byte triplets from a float colour table */

void __cdecl Palette_FromFloatTable(byte *out,byte *in,int n,double gamma)

{
  longlong lVar1;
  
  if (0 < n) {
    do {
      lVar1 = FTOL(_CIpow());
      *out = (byte)lVar1;
      lVar1 = FTOL(_CIpow());
      out[1] = (byte)lVar1;
      lVar1 = FTOL(_CIpow());
      out[2] = (byte)lVar1;
      out = out + 3;
      n = n + -1;
    } while (n != 0);
  }
  return;
}
#endif


/* ---- 0x0047b8a0  stdColor_ColorConvertOneRow ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Converts pixels between the 16-bit RGB layouts described by the format records Original name
   stdColor_ColorConvertOneRow (the remaster's GrimFandango (Linux): aligned call in
   stdColor_ColorConvertOnePixel, stdDisplay_VBufferConvertColorFormat); was Pixel_Convert. */

void __cdecl
stdColor_ColorConvertOneRow(ushort *dst,int dstFormat,ushort *src,int srcFormat,uint count)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  char cVar10;
  byte bVar11;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar13;
  longlong lVar14;
  longlong lVar15;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  byte bVar12;
  
  g_dwStdColor_ColorConvertOneRow_row = g_dwStdColor_ColorConvertOneRow_row + 1;
  cVar10 = (char)*(undefined4 *)(srcFormat + 8);
  lVar13 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  lVar14 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  lVar15 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
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
                               0xffffffffU >> (0x20U - cVar10 & 0x1f)) * (int)lVar13) >> 0x10) <<
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
        PIECE(local_c,0,1) = (byte)(0xffffffff >> (0x20U - cVar10 & 0x1f));
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
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x0047bbb0  stdColor_ColorConvertOnePixel ---- */
/* Original name stdColor_ColorConvertOnePixel (the remaster's GrimFandango (Linux): aligned call in
   stdBitmap_ConvertColorFormat, stdDisplay_VBufferConvertColorFormat); was Pixel_ConvertOne. */

int __cdecl stdColor_ColorConvertOnePixel(int param_1,uint param_2,int param_3)

{
  stdColor_ColorConvertOneRow((ushort *)&param_3,param_1,(ushort *)&param_2,param_3,1);
  return param_3;
}
