/* GRIMFANDANGO.EXE :: sputroom.c
 * functions 0x004a48c0 .. 0x004a4b00 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a48c0  sputRoom_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined * __cdecl sputRoom_Initialize(uint param_1,undefined **param_2)

{
  int iVar1;
  uint *puVar2;
  
  g_pSvcRoom = (GrimServices *)param_1;
  *param_2 = sputRoom_Initialize;
  param_2[1] = FUN_004a5390;
  param_2[2] = FUN_004a53b0;
  param_2[3] = FUN_004a5430;
  param_2[4] = Set_SaveState;
  param_2[5] = Set_RestoreState;
  param_2[6] = (undefined *)0x0;
  param_2[7] = (undefined *)0x0;
  puVar2 = &g_CurrentSetRef;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  UINT_008cb098 = 1;
  g_CurrentSetRef = 0;
  return (undefined *)0x0;
}

/* ---- 0x004a4920  FUN_004a4920 ---- */
void FUN_004a4920(undefined4 param_1)

{
  FUN_004a4930(param_1);
  return;
}

/* ---- 0x004a4930  FUN_004a4930 ---- */
undefined4 FUN_004a4930(char *param_1)

{
  undefined4 uVar1;
  void *bitmap;
  
  bitmap = stdBitmap_LoadFile(param_1,0,0);
  if (bitmap == (void *)0x0) {
    return 0;
  }
  uVar1 = **(undefined4 **)((int)bitmap + 0x78);
  (*g_pSvcRoom->pFree)(*(undefined4 **)((int)bitmap + 0x78));
  *(undefined4 *)((int)bitmap + 0x78) = 0;
  *(undefined4 *)((int)bitmap + 100) = 0;
  stdBitmap_Free(bitmap);
  return uVar1;
}

/* ---- 0x004a4980  FUN_004a4980 ---- */
void FUN_004a4980(undefined4 param_1)

{
  FUN_004a4990(param_1);
  return;
}

/* ---- 0x004a4990  FUN_004a4990 ---- */
void FUN_004a4990(void *param_1)

{
  Surface_Free(param_1);
  return;
}

/* ---- 0x004a49a0  FUN_004a49a0 ---- */
undefined4 * FUN_004a49a0(char *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  void *pvVar3;
  int iVar4;
  undefined4 *puVar5;
  
  puVar2 = (undefined4 *)
           (*g_pSvcRoom->pAlloc)(0x1b08,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x306);
  if (puVar2 != (undefined4 *)0x0) {
    puVar5 = puVar2;
    for (iVar4 = 0x6c2; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    FUN_004a4a70(puVar2);
    iVar4 = FUN_004a4b00(param_1,puVar2);
    if (iVar4 != 0) {
      pvVar3 = (void *)Set_FindNameInList(param_1);
      if (pvVar3 == (void *)0x0) {
        pvVar3 = Set_NormalizeName(param_1);
      }
      puVar2[0x6af] = pvVar3;
      for (piVar1 = *(int **)((int)pvVar3 + 0x80); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[2])
      {
        iVar4 = *(int *)((int)g_pActorTable + *piVar1 * 0xa8 + 0xa4);
        if (((iVar4 != 0) && (*(void **)(iVar4 + 0x1b4) != (void *)0x0)) &&
           (*(int *)(iVar4 + 0x1b8) != 0)) {
          Walker_ReattachToSet(*(void **)(iVar4 + 0x1b4));
        }
      }
      return puVar2;
    }
  }
  FUN_004a4c40(puVar2);
  return (undefined4 *)0x0;
}

/* ---- 0x004a4a70  FUN_004a4a70 ---- */
void FUN_004a4a70(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0x6c2; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[0x2e] = 0;
  param_1[0x2c] = 0;
  param_1[0x2b] = 0;
  param_1[0x2d] = 0;
  param_1[0x22] = 0;
  param_1[0x21] = 1;
  param_1[0x20] = 0;
  *(undefined1 *)(param_1 + 0x23) = 0;
  strncpy(param_1 + 0x23,&DAT_004ec60c,0x1f);
  *(undefined1 *)((int)param_1 + 0xab) = 0;
  strncpy(param_1,&DAT_004f5a98,0x1f);
  *(undefined1 *)((int)param_1 + 0x1f) = 0;
  param_1[0x6bd] = 0x1b08;
  return;
}

/* ---- 0x004a4b00  FUN_004a4b00 ---- */
bool FUN_004a4b00(char *param_1,uint param_2)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0x7f;
  UINT_008cb0a8 = param_2;
  pcVar1 = Str_Basename(param_1);
  strncpy(param_2,pcVar1,uVar3);
  *(undefined1 *)(param_2 + 0x7f) = 0;
  iVar2 = FUN_004a5550(param_1);
  return iVar2 != 0;
}
