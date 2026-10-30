/* GRIMFANDANGO.EXE :: debug.c
 * functions 0x0048d210 .. 0x0048d210 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048d210  Debug_CameraFovKeys ---- */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* With debug keys on, Ctrl+N / Ctrl+J change the current camera's field of view by 0.5 */

undefined4 Debug_CameraFovKeys(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fov;
  int iVar1;
  void *pvVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
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
#undef local_4

