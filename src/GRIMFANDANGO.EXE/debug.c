/* GRIMFANDANGO.EXE :: debug.c
 * functions 0x0048d210 .. 0x0048d210 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048d210  sputControl_StandardHandler ---- */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* With debug keys on, Ctrl+N / Ctrl+J change the current camera's field of view by 0.5 Original
   name sputControl_StandardHandler (the remaster's GrimFandango (Linux): same body (with
   grimlib_bDebugKeys and a modifier key: the two keys move the current setup's camera FOV by 0.5
   via rdCamera_SetFOV); the control callback sputControl_Startup registers (here through
   Controls_DebugKeysHook)); was Debug_CameraFovKeys. */

uint __cdecl sputControl_StandardHandler(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fov;
  int iVar1;
  Set *pSVar2;
  void *camera;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if ((g_nGrimlib_bDebugKeys != 0) &&
     (iVar1 = stdControl_ReadKey(0x1d,(int *)0x0,(int *)0x0), iVar1 != 0)) {
    iVar1 = stdControl_ReadKey(0x4e,(int *)0x0,(int *)0x0);
    if (iVar1 == 0) {
      iVar1 = stdControl_ReadKey(0x4a,(int *)0x0,(int *)0x0);
      if (iVar1 == 0) {
        return 0;
      }
      pSVar2 = sputRoom_GetCurrentRoom();
      camera = *(void **)&pSVar2->pSetups[pSVar2->nCurSetup].field_0x48;
      fov = *(float *)((int)camera + 0x38) - 0.5;
    }
    else {
      pSVar2 = sputRoom_GetCurrentRoom();
      camera = *(void **)&pSVar2->pSetups[pSVar2->nCurSetup].field_0x48;
      fov = *(float *)((int)camera + 0x38) - -0.5;
    }
    rdCamera_SetFOV(camera,fov);
    return 1;
  }
  return 0;
}
#undef local_4

