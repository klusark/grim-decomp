/* GRIMFANDANGO.EXE :: debug.c
 * functions 0x0048d210 .. 0x0048d330 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048d210  Debug_CameraFovKeys ---- */
/* With debug keys on, Ctrl+N / Ctrl+J change the current camera's field of view by 0.5 */

undefined4 Debug_CameraFovKeys(void)

{
  float fov;
  int iVar1;
  void *pvVar2;
  
  if ((g_nDebugKeysEnabled != 0) &&
     (iVar1 = Input_GetButtonState(0x1d,(int *)0x0,(int *)0x0), iVar1 != 0)) {
    iVar1 = Input_GetButtonState(0x4e,(int *)0x0,(int *)0x0);
    if (iVar1 == 0) {
      iVar1 = Input_GetButtonState(0x4a,(int *)0x0,(int *)0x0);
      if (iVar1 == 0) {
        return 0;
      }
      pvVar2 = Set_GetCurrent();
      pvVar2 = *(void **)(*(int *)((int)pvVar2 + 0xac) + 0x48 + *(int *)((int)pvVar2 + 0xb4) * 300);
      fov = *(float *)((int)pvVar2 + 0x38) - 0.5;
    }
    else {
      pvVar2 = Set_GetCurrent();
      pvVar2 = *(void **)(*(int *)((int)pvVar2 + 0xac) + 0x48 + *(int *)((int)pvVar2 + 0xb4) * 300);
      fov = *(float *)((int)pvVar2 + 0x38) - -0.5;
    }
    rdCamera_SetFov(pvVar2,fov);
    return 1;
  }
  return 0;
}

/* ---- 0x0048d2c0  FUN_0048d2c0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048d2c0(void)

{
  _DAT_008ca1b8 = 0;
  if (DAT_008ca1bc != 0) {
    DAT_008ca1bc = 0;
  }
  return;
}

/* ---- 0x0048d2e0  FUN_0048d2e0 ---- */
undefined4 FUN_0048d2e0(void)

{
  int iVar1;
  
  if (DAT_008ca1c0 != 0) {
    return 1;
  }
  if (DAT_00805f98 == 0) {
    iVar1 = Input_Init();
    if (iVar1 == 0) {
      return 1;
    }
  }
  Controls_ResetAll();
  Engine_RegisterShutdownHook(FUN_0048d030);
  DAT_008ca1c0 = 1;
  return 0;
}

/* ---- 0x0048d330  FUN_0048d330 ---- */
void FUN_0048d330(void)

{
  Input_Shutdown();
  DAT_008ca1c0 = 0;
  return;
}
