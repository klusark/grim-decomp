/* GRIMFANDANGO.EXE :: spritecomponent.c
 * functions 0x00496340 .. 0x00496e10 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00496340  SpriteComponent_Destroy ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 SpriteComponent_Destroy(undefined4 param_1,undefined4 param_2,void *param_3)

{
  _DAT_008ca7b4 = param_3;
  ResRef_Remove(param_3);
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}

/* ---- 0x00496370  FUN_00496370 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 * FUN_00496370(undefined4 param_1,undefined4 param_2,int *param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  #define uStack_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define auStack_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  if (param_3 == (int *)0x0) {
    iVar2 = Cos_InstGetInstanceData(param_1,param_2,0);
    ResRef_Remove((void *)(iVar2 + 4));
    (*g_pSvcCostume->pFree)(iVar2);
    return (undefined4 *)0x0;
  }
  puVar3 = (undefined4 *)
           (*g_pSvcCostume->pAlloc)(0x38,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x8fa);
  Cos_InstComponentInfo(param_1,param_2,auStack_4,&param_3,&uStack_8);
  piVar1 = param_3;
  puVar5 = puVar3;
  for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  if (*param_3 == 0) {
    (*g_pSvcMain->pAssertFail)
              (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
  }
  ResRef_Add(puVar3 + 1,(void *)piVar1[1],s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x8ff);
  uVar4 = Cos_InstGetInstanceData(param_1,uStack_8,0);
  *puVar3 = uVar4;
  return puVar3;
}
#undef auStack_4
#undef uStack_8

#endif


/* ---- 0x00496d70  SpriteComponent_NewInstance ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Source: Engine/sputCostume.cpp (line 2900, from __FILE__/__LINE__ passed to the allocator) */

undefined4 * SpriteComponent_NewInstance(undefined4 param_1,undefined4 param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  #define auStack_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  if (param_3 == 0) {
    uVar2 = Cos_InstGetInstanceData(param_1,param_2,0);
    (*g_pSvcCostume->pFree)(uVar2);
    return (undefined4 *)0x0;
  }
  puVar3 = (undefined4 *)
           (*g_pSvcCostume->pAlloc)(0xc,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xb54);
  piVar1 = puVar3 + 1;
  Cos_InstComponentInfo(param_1,param_2,auStack_4,piVar1,&param_3);
  *piVar1 = *piVar1 >> 0x10;
  uVar2 = Cos_InstGetInstanceData(param_1,param_3,0);
  *puVar3 = uVar2;
  puVar3[2] = 1;
  return puVar3;
}
#undef auStack_4

#endif


/* ---- 0x00496e10  FUN_00496e10 ---- */
void FUN_00496e10(int param_1)

{
  *(undefined4 *)(param_1 + 8) = 1;
  return;
}
