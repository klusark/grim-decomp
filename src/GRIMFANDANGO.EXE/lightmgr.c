/* GRIMFANDANGO.EXE :: lightmgr.c
 * functions 0x004be310 .. 0x004beee0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004be310  LightMgr_Refresh ---- */
void __cdecl LightMgr_Refresh(void)

{
  Set *pSVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  char *pcVar5;
  undefined4 *puVar6;
  uint local_4;
  
  iVar4 = 0;
  local_4 = 0;
  pSVar1 = g_pLightEdSet;
  if (g_pLightEdSet->nLights != 0) {
    puVar3 = &UINT_008d1730;
    do {
      *puVar3 = (uint)(pSVar1->aLights[0].aName + iVar4);
      puVar3[1] = 1;
      if (*(int *)(*puVar3 + 0x30) == 2) {
        puVar3[2] = 0;
        puVar3[3] = 0;
        puVar3[4] = 0;
      }
      else {
        LightEd_GetLightAngles(*puVar3 + 0x2c,(float *)(puVar3 + 2));
        pSVar1 = g_pLightEdSet;
      }
      puVar3 = puVar3 + 5;
      pcVar5 = pSVar1->aLights[0].aName + iVar4;
      puVar6 = (undefined4 *)((int)&UINT_008d1c30 + iVar4);
      for (iVar2 = 0x1a; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        puVar6 = puVar6 + 1;
      }
      local_4 = local_4 + 1;
      iVar4 = iVar4 + 0x68;
    } while (local_4 < (uint)pSVar1->nLights);
  }
  UINT_008d3644 = pSVar1->nLights;
  return;
}

/* ---- 0x004beee0  LightMgr_UpdateDialog ---- */
void __cdecl LightMgr_UpdateDialog(uint hDlg)

{
  if (g_pLightEdSet != (Set *)0x0) {
    LightEd_FillListBox(hDlg);
    return;
  }
  (*g_pStd_HS->pDebug)(0,s_LightManager_UpdateDialog__No_cu_004f0e3c);
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char grim_def_s_LightManager_UpdateDialog__No_cu_004f0e3c[44] __asm__("_s_LightManager_UpdateDialog__No_cu_004f0e3c");
/* 0x004f0e3c, 44 bytes */ GRIM_DATA("004f0e3c") char grim_def_s_LightManager_UpdateDialog__No_cu_004f0e3c[44] __asm__("_s_LightManager_UpdateDialog__No_cu_004f0e3c") = "LightManager_UpdateDialog: No current set.\n";
