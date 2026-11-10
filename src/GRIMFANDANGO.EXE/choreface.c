/* GRIMFANDANGO.EXE :: choreface.c
 * functions 0x00402120 .. 0x00402290 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00402120  ChoreFace_Toggle ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Loads/unloads choreface.dll (the chore editor UI) and shows/hides it */

int __cdecl ChoreFace_Toggle(int show)

{
  int iVar1;
  undefined4 uVar2;
  
  if (show == 0) {
    if (UINT_004f5a6c == 0) {
      return 1;
    }
    iVar1 = (*(code *)UINT_004f5a74)();
    if (iVar1 != 0) {
      (*(code *)UINT_004f4d9c)();
      (*(code *)UINT_004f4d94)();
      UINT_004f5a70 = 0;
      UINT_004f5a74 = 0;
      UINT_004f5a78 = 0;
      _DAT_004f5a7c = (code *)0x0;
      FreeLibrary(UINT_004f4530);
      UINT_004f4530 = 0;
      UINT_004f5a6c = 0;
      return 1;
    }
    return 0;
  }
  if (UINT_004f5a6c == 0) {
    UINT_004f4530 = LoadLibraryA(IMG_ADDR(0x004dd728));
    if (UINT_004f4530 == 0) {
      return 0;
    }
    UINT_004f5a70 = GetProcAddress(UINT_004f4530,IMG_ADDR(0x004dd718));
    UINT_004f5a74 = GetProcAddress(UINT_004f4530,IMG_ADDR(0x004dd708));
    UINT_004f5a78 = GetProcAddress(UINT_004f4530,IMG_ADDR(0x004dd6ec));
    _DAT_004f5a7c = (code *)GetProcAddress(UINT_004f4530,IMG_ADDR(0x004dd6d4));
    if ((((UINT_004f5a70 != 0) && (UINT_004f5a74 != 0)) && (UINT_004f5a78 != 0)) &&
       (_DAT_004f5a7c != (code *)0x0)) {
      iVar1 = (*_DAT_004f5a7c)(PTR_DAT_004dd040,&DAT_004f4d90);
      if (iVar1 == 0) {
        iVar1 = (*(code *)UINT_004f4d98)();
        if (iVar1 == 0) {
          _DAT_004f5a80 = (*(code *)UINT_004f5a78)(ChoreFace_OnCommand);
          UINT_004f5a6c = 1;
          goto LAB_004021fb;
        }
      }
    }
    FreeLibrary(UINT_004f4530);
    UINT_004f4530 = 0;
    return 0;
  }
LAB_004021fb:
  uVar2 = Win_GetMainHwnd();
  (*(code *)UINT_004f5a70)(uVar2);
  return 1;
}

/* ---- 0x00402200  FUN_00402200 ---- */
undefined4 FUN_00402200(void)

{
  (*(code *)UINT_004f5a70)();
  return 1;
}

/* ---- 0x00402290  ChoreFace_OnCommand ---- */
/* Callback handed to choreface.dll (UINT_004f5a78): 1 = frame update, 2/3 = pause/unpause, 4/5 =
   pop/push the selected actor costume (forces windowed mode while editing), >=7 sets
   g_fixedFrameMs. */

void ChoreFace_OnCommand(undefined4 param_1,int param_2)

{
  switch(param_2) {
  case 0:
    goto switchD_00402299_caseD_0;
  case 1:
    Main_Service();
    return;
  case 2:
    grimlib_SetPause(1);
    return;
  case 3:
    grimlib_SetPause(0);
    return;
  case 4:
    if (g_bWindowedMode != UINT_004dd388) {
      g_bWindowedMode = UINT_004dd388;
      Display_InitFromConfig();
    }
    grimlib_RestoreSelectedActorCostume();
    return;
  case 5:
    UINT_004dd388 = g_bWindowedMode;
    if (g_bWindowedMode != 0) {
      g_bWindowedMode = 0;
      Display_InitFromConfig();
    }
switchD_00402299_caseD_0:
    grimlib_OverrideSelectedActorCostume(param_1);
    return;
  case 6:
    return;
  default:
    g_fixedFrameMs = param_2 + -7;
    return;
  }
}
