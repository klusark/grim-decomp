/* GRIMFANDANGO.EXE :: choreface.c
 * functions 0x00402120 .. 0x004024f0 (8 functions)
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
    if (DAT_004f5a6c == 0) {
      return 1;
    }
    iVar1 = (*DAT_004f5a74)();
    if (iVar1 != 0) {
      (*DAT_004f4d9c)();
      (*DAT_004f4d94)();
      DAT_004f5a70 = (code *)0x0;
      DAT_004f5a74 = (code *)0x0;
      DAT_004f5a78 = (code *)0x0;
      _DAT_004f5a7c = (code *)0x0;
      FreeLibrary(DAT_004f4530);
      DAT_004f4530 = 0;
      DAT_004f5a6c = 0;
      return 1;
    }
    return 0;
  }
  if (DAT_004f5a6c == 0) {
    DAT_004f4530 = LoadLibraryA(IMG_ADDR(0x004dd728));
    if (DAT_004f4530 == 0) {
      return 0;
    }
    DAT_004f5a70 = (code *)GetProcAddress(DAT_004f4530,IMG_ADDR(0x004dd718));
    DAT_004f5a74 = (code *)GetProcAddress(DAT_004f4530,IMG_ADDR(0x004dd708));
    DAT_004f5a78 = (code *)GetProcAddress(DAT_004f4530,IMG_ADDR(0x004dd6ec));
    _DAT_004f5a7c = (code *)GetProcAddress(DAT_004f4530,IMG_ADDR(0x004dd6d4));
    if ((((DAT_004f5a70 != (code *)0x0) && (DAT_004f5a74 != (code *)0x0)) &&
        (DAT_004f5a78 != (code *)0x0)) && (_DAT_004f5a7c != (code *)0x0)) {
      iVar1 = (*_DAT_004f5a7c)(PTR_DAT_004dd040,&DAT_004f4d90);
      if (iVar1 == 0) {
        iVar1 = (*DAT_004f4d98)();
        if (iVar1 == 0) {
          _DAT_004f5a80 = (*DAT_004f5a78)(FUN_00402290);
          DAT_004f5a6c = 1;
          goto LAB_004021fb;
        }
      }
    }
    FreeLibrary(DAT_004f4530);
    DAT_004f4530 = 0;
    return 0;
  }
LAB_004021fb:
  uVar2 = Win_GetMainHwnd();
  (*DAT_004f5a70)(uVar2);
  return 1;
}

/* ---- 0x00402200  FUN_00402200 ---- */
undefined4 FUN_00402200(void)

{
  (*DAT_004f5a70)();
  return 1;
}

/* ---- 0x00402290  FUN_00402290 ---- */
void FUN_00402290(undefined4 param_1,int param_2)

{
  switch(param_2) {
  case 0:
    goto switchD_00402299_caseD_0;
  case 1:
    Game_FrameUpdate();
    return;
  case 2:
    Engine_SetPaused(1);
    return;
  case 3:
    Engine_SetPaused(0);
    return;
  case 4:
    if (DAT_004f5a20 != DAT_004dd388) {
      DAT_004f5a20 = DAT_004dd388;
      Display_InitFromConfig();
    }
    Engine_PopSelectedActorCostume();
    return;
  case 5:
    DAT_004dd388 = DAT_004f5a20;
    if (DAT_004f5a20 != 0) {
      DAT_004f5a20 = 0;
      Display_InitFromConfig();
    }
switchD_00402299_caseD_0:
    ((code *)Engine_PushSelectedActorCostume)(param_1);
    return;
  case 6:
    return;
  default:
    DAT_004f5a48 = param_2 + -7;
    return;
  }
}

/* ---- 0x00402330  FUN_00402330 ---- */
undefined4 FUN_00402330(undefined4 param_1)

{
  _snprintf(&DAT_004f55b0,0x400,param_1,&STACK0X(0x00000008));
  if ((DAT_004f5a08 == 0) || (DAT_004f5a20 == 0)) {
    Svc_DebugPrintf(&DAT_004f55b0);
  }
  else {
    param_1 = (*DAT_004f5a3c)(&DAT_004f55b0);
  }
  if (DAT_004f5a18 != 0) {
    DebugLog_Write(&DAT_004f55b0,0);
  }
  return param_1;
}

/* ---- 0x004023a0  FUN_004023a0 ---- */
undefined4 FUN_004023a0(undefined4 param_1)

{
  _snprintf(&DAT_004f4538,0x400,param_1,&STACK0X(0x00000008));
  if ((DAT_004f5a08 == 0) || (DAT_004f5a20 == 0)) {
    Svc_DebugPrintf(&DAT_004f4538);
  }
  else {
    param_1 = (*DAT_004f5a3c)(&DAT_004f4538);
  }
  if (DAT_004f5a18 != 0) {
    DebugLog_Write(&DAT_004f4538,0);
  }
  return param_1;
}

/* ---- 0x00402410  FUN_00402410 ---- */
undefined4 FUN_00402410(undefined4 param_1)

{
  _snprintf(&DAT_004f4db0,0x400,param_1,&STACK0X(0x00000008));
  if ((DAT_004f5a08 == 0) || (DAT_004f5a20 == 0)) {
    Svc_DebugPrintf(&DAT_004f4db0);
  }
  else {
    param_1 = (*DAT_004f5a3c)(&DAT_004f4db0);
  }
  if (DAT_004f5a18 != 0) {
    DebugLog_Write(&DAT_004f4db0,0);
  }
  return param_1;
}

/* ---- 0x00402480  FUN_00402480 ---- */
undefined4 FUN_00402480(undefined4 param_1)

{
  _snprintf(&DAT_004f51b0,0x400,param_1,&STACK0X(0x00000008));
  if ((DAT_004f5a08 == 0) || (DAT_004f5a20 == 0)) {
    Svc_DebugPrintf(&DAT_004f51b0);
  }
  else {
    param_1 = (*DAT_004f5a3c)(&DAT_004f51b0);
  }
  if (DAT_004f5a18 != 0) {
    DebugLog_Write(&DAT_004f51b0,0);
  }
  return param_1;
}

/* ---- 0x004024f0  FUN_004024f0 ---- */
undefined4 FUN_004024f0(undefined4 param_1)

{
  _snprintf(&DAT_004f4938,0x400,param_1,&STACK0X(0x00000008));
  if ((DAT_004f5a08 == 0) || (DAT_004f5a20 == 0)) {
    Svc_DebugPrintf(&DAT_004f4938);
  }
  else {
    param_1 = (*DAT_004f5a3c)(&DAT_004f4938);
  }
  if (DAT_004f5a18 != 0) {
    DebugLog_Write(&DAT_004f4938,0);
  }
  return param_1;
}
