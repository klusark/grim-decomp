/* GRIMFANDANGO.EXE :: lightmgr.c
 * functions 0x004be310 .. 0x004beee0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004be310  LightMgr_Refresh ---- */
void LightMgr_Refresh(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar4 = 0;
  local_4 = 0;
  pvVar1 = g_pLightEdSet;
  if (*(int *)((int)g_pLightEdSet + 0xb8) != 0) {
    puVar3 = &UINT_008d1730;
    do {
      *puVar3 = (int)pvVar1 + iVar4 + 0xbc;
      puVar3[1] = 1;
      if (*(int *)(*puVar3 + 0x30) == 2) {
        puVar3[2] = 0;
        puVar3[3] = 0;
        puVar3[4] = 0;
      }
      else {
        LightEd_GetLightAngles(*puVar3 + 0x2c,puVar3 + 2);
        pvVar1 = g_pLightEdSet;
      }
      puVar3 = puVar3 + 5;
      puVar5 = (undefined4 *)((int)pvVar1 + iVar4 + 0xbc);
      puVar6 = (undefined4 *)((int)&UINT_008d1c30 + iVar4);
      for (iVar2 = 0x1a; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      local_4 = local_4 + 1;
      iVar4 = iVar4 + 0x68;
    } while (local_4 < *(uint *)((int)pvVar1 + 0xb8));
  }
  UINT_008d3644 = *(uint *)((int)pvVar1 + 0xb8);
  return;
}
#undef local_4


/* ---- 0x004beee0  LightMgr_UpdateDialog ---- */
void LightMgr_UpdateDialog(undefined4 param_1)

{
  if (g_pLightEdSet != (void *)0x0) {
    LightEd_FillListBox(param_1);
    return;
  }
  (*g_pSvcMain->pDebug)(0,s_LightManager_UpdateDialog__No_cu_004f0e3c);
  return;
}
