/* GRIMFANDANGO.EXE :: cmapcomponent.c
 * functions 0x00496460 .. 0x00496670 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00496460  CmapComponent_Create ---- */
/* Registers a 'cmap' colormap component (CMAP resource, 0x34-byte ResRef); with no name a file
   dialog asks for one (editor) */

bool CmapComponent_Create
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,char *param_5)

{
  undefined4 uVar1;
  void *data;
  undefined4 *ref;
  char *pcVar2;
  int iVar3;
  undefined4 *puVar4;
  char *name;
  
  pcVar2 = param_5;
  if (((param_4 != 0x4c444f4d) && (param_4 != 0x4c444d4d)) && (param_4 != 0x74727073)) {
    return false;
  }
  name = param_5;
  if (param_5 == (char *)0x0) {
    if (DAT_008ca8b8 != '\0') {
      Plat_SetDialogDirectory(&DAT_008ca8b8);
    }
    iVar3 = Plat_OpenFileDialog(s_Select_colormap_file_to_add____004ea530,
                                s_Colormap_files____cmp__004ea550);
    if (iVar3 == 0) {
      return false;
    }
    uVar1 = ((code *)Plat_GetDialogFileName)(0x7f);
    ((code *)strncpy)(&DAT_008ca8b8,uVar1);
    DAT_008ca937 = 0;
    param_5 = Str_Basename(g_szDialogFileName);
    name = g_szDialogFileName;
  }
  data = Resource_Load(0x50414d43,name);
  if (data != (void *)0x0) {
    ref = (undefined4 *)
          (*g_pSvcCostume->pAlloc)(0x34,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x938);
    puVar4 = ref;
    for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    ResRef_Add(ref,data,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x93a);
    if (pcVar2 == (char *)0x0) {
      pcVar2 = param_5;
    }
    iVar3 = Cos_RegisterComponent(param_1,pcVar2,ref,param_2,param_3,param_4,&DAT_004e9f20);
    return iVar3 != 0;
  }
  return false;
}

/* ---- 0x00496580  CmapComponent_Destroy ---- */
undefined4 CmapComponent_Destroy(undefined4 param_1,undefined4 param_2,void *param_3)

{
  ResRef_Remove(param_3);
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}

/* ---- 0x004965b0  FUN_004965b0 ---- */
undefined4 FUN_004965b0(void)

{
  int in_stack_00000010;
  code *in_stack_00000014;
  
  (*in_stack_00000014)(in_stack_00000010 + 8,4);
  return 1;
}

/* ---- 0x004965d0  FUN_004965d0 ---- */
void FUN_004965d0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined4 *)(param_2 + 8) = param_4;
  return;
}

/* ---- 0x004965e0  CmapComponent_NewInstance ---- */
/* Source: Engine/sputCostume.cpp (line 2465, from __FILE__/__LINE__ passed to the allocator) */

void * __cdecl CmapComponent_NewInstance(void *cosInst,int componentIdx,int create)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 *puVar2;
  #define auStack_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  if (create == 0) {
    uVar1 = Cos_InstGetInstanceData(cosInst,componentIdx,0);
    (*g_pSvcCostume->pFree)(uVar1);
    return (void *)0x0;
  }
  puVar2 = (undefined4 *)
           (*g_pSvcCostume->pAlloc)(0xc,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x9a1);
  Cos_InstComponentInfo(cosInst,componentIdx,auStack_4,puVar2 + 1,&create);
  uVar1 = Cos_InstGetInstanceData(cosInst,create,0);
  *puVar2 = uVar1;
  puVar2[2] = 0;
  return puVar2;
}
#undef auStack_4


/* ---- 0x00496670  FUN_00496670 ---- */
bool FUN_00496670(undefined4 param_1,undefined4 param_2,int *param_3,int param_4,char *param_5)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  #define uStack_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define pcStack_18 (*(char **)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  local_14 = 1;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  if (((param_4 != 0x4c444f4d) && (param_4 != 0x4c444d4d)) && (param_4 != 0x74727073)) {
    return false;
  }
  if (*param_3 == 0) {
    (*g_pSvcMain->pAssertFail)(s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
  }
  iVar5 = param_3[1];
  if (param_5 == (char *)0x0) {
    if (DAT_008ca938 != '\0') {
      Plat_SetDialogDirectory(&DAT_008ca938);
    }
    iVar2 = Plat_OpenFileDialog(s_Select_mat_file_to_animate____004ea584,
                                s_Material_files____mat__004ea5a4);
    if (iVar2 == 0) {
      return false;
    }
    uVar3 = ((code *)Plat_GetDialogFileName)(0x7f);
    ((code *)strncpy)(&DAT_008ca938,uVar3);
    DAT_008ca9b7 = 0;
    pcStack_18 = Str_Basename(g_szDialogFileName);
  }
  uVar7 = 0;
  uStack_1c = 0;
  if (*(int *)(iVar5 + 0x4c) != 0) {
    do {
      pcVar4 = param_5;
      if (param_5 == (char *)0x0) {
        pcVar4 = pcStack_18;
      }
      iVar2 = _stricmp(pcVar4,*(int *)(*(int *)(iVar5 + 0x48) + uVar7 * 4) + 4);
      uStack_1c = uVar7;
    } while ((iVar2 != 0) && (uVar7 = uVar7 + 1, uStack_1c = uVar7, uVar7 < *(uint *)(iVar5 + 0x4c))
            );
  }
  if (uStack_1c != *(uint *)(iVar5 + 0x4c)) {
    uVar7 = 0;
    iVar5 = *(int *)(*(int *)(iVar5 + 0x48) + uStack_1c * 4);
    local_14 = *(uint *)(iVar5 + 0x60);
    local_10 = 0;
    local_c = 0;
    if (UINT_008ca7a4 != 0) {
      (*g_pSvcCostume->pFree)(UINT_008ca7a4);
    }
    UINT_008ca7a4 =
         (*g_pSvcCostume->pAlloc)(local_14 << 4,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x9ee);
    if (*(int *)(iVar5 + 0x60) != 0) {
      iVar2 = 0;
      piVar6 = (int *)(iVar5 + 0x68);
      do {
        iVar1 = *piVar6;
        uVar7 = uVar7 + 1;
        piVar6 = piVar6 + 1;
        iVar2 = iVar2 + 0x10;
        iVar1 = *(int *)(*(int *)(iVar1 + 0x1c) + 0x1c);
        *(undefined4 *)((UINT_008ca7a4 - 0xc) + iVar2) = *(undefined4 *)(iVar1 + 0xc);
        *(undefined4 *)((UINT_008ca7a4 - 8) + iVar2) = *(undefined4 *)(iVar1 + 0x10);
        *(undefined4 *)((UINT_008ca7a4 - 0x10) + iVar2) = *(undefined4 *)(iVar1 + 0x5c);
        *(undefined4 *)((UINT_008ca7a4 - 4) + iVar2) = 1;
      } while (uVar7 < *(uint *)(iVar5 + 0x60));
    }
    local_4 = 0;
    local_8 = UINT_008ca7a4;
    if (param_5 == (char *)0x0) {
      param_5 = pcStack_18;
    }
    iVar5 = Cos_RegisterComponent(param_1,param_5,uStack_1c,param_2,param_3,param_4,&local_14);
    return iVar5 != 0;
  }
  return false;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c
#undef pcStack_18
#undef uStack_1c

