/* GRIMFANDANGO.EXE :: sputroom.c
 * functions 0x004a48c0 .. 0x004a4b00 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a48c0  sputRoom_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 __cdecl sputRoom_Initialize(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  DAT_008cb090 = param_1;
  *param_2 = sputRoom_Initialize;
  param_2[1] = FUN_004a5390;
  param_2[2] = FUN_004a53b0;
  param_2[3] = FUN_004a5430;
  param_2[4] = Set_SaveState;
  param_2[5] = Set_RestoreState;
  param_2[6] = 0;
  param_2[7] = 0;
  puVar2 = &g_CurrentSetRef;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_008cb098 = 1;
  g_CurrentSetRef = 0;
  return 0;
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
  (**(code **)(DAT_008cb090 + 0x24))(*(undefined4 **)((int)bitmap + 0x78));
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
undefined4 * FUN_004a49a0(undefined4 param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar2 = (undefined4 *)
           (**(code **)(DAT_008cb090 + 0x20))
                     (0x1b08,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x306);
  if (puVar2 != (undefined4 *)0x0) {
    puVar4 = puVar2;
    for (iVar3 = 0x6c2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    FUN_004a4a70(puVar2);
    iVar3 = FUN_004a4b00(param_1,puVar2);
    if (iVar3 != 0) {
      iVar3 = Set_FindNameInList(param_1);
      if (iVar3 == 0) {
        iVar3 = Set_NormalizeName(param_1);
      }
      puVar2[0x6af] = iVar3;
      for (piVar1 = *(int **)(iVar3 + 0x80); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[2]) {
        iVar3 = *(int *)((int)g_pActorTable + *piVar1 * 0xa8 + 0xa4);
        if (((iVar3 != 0) && (*(int *)(iVar3 + 0x1b4) != 0)) && (*(int *)(iVar3 + 0x1b8) != 0)) {
          ((code *)Walker_ReattachToSet)();
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
bool FUN_004a4b00(char *param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0x7f;
  DAT_008cb0a8 = param_2;
  pcVar1 = Str_Basename(param_1);
  strncpy(param_2,pcVar1,uVar3);
  *(undefined1 *)(param_2 + 0x7f) = 0;
  iVar2 = FUN_004a5550(param_1);
  return iVar2 != 0;
}
