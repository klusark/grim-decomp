/* GRIMFANDANGO.EXE :: component.c
 * functions 0x00496060 .. 0x004960a0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00496060  Component_SetBitmapFrame ---- */
void Component_SetBitmapFrame(undefined4 param_1,int *param_2,undefined4 param_3,int param_4)

{
  if (*param_2 == 0) {
    (*g_pSvcMain->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
  }
  *(int *)(param_2[1] + 0x68) = param_4 + -1;
  return;
}

/* ---- 0x004960a0  FUN_004960a0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_004960a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            char *param_5)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  char *name;
  undefined4 uVar3;
  char *data;
  undefined4 *ref;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  undefined4 *puVar9;
  #define local_34 (*(int *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(undefined4 **)(_frame + (0x50 - 0x30)))
  #define local_2c (*(undefined4 *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(char **)(_frame + (0x50 - 0x24)))
  #define local_20 (*(undefined1 (*)[31])(_frame + (0x50 - 0x20)))
  #define local_1 (*(undefined1 *)(_frame + (0x50 - 0x1)))
  
  local_34 = 1;
  local_30 = (undefined4 *)0x0;
  local_2c = 0;
  local_28 = 0;
  local_24 = (char *)0x0;
  if (param_5 == (char *)0x0) {
    if (DAT_008ca838 != '\0') {
      Plat_SetDialogDirectory(&DAT_008ca838);
    }
    iVar6 = Plat_OpenFileDialog(s_Select_image_file_to_add____004ea4b8,
                                s_Graphics_files____pcx____gif___l_004ea4d4);
    if (iVar6 == 0) {
      return 0;
    }
    uVar3 = ((code *)Plat_GetDialogFileName)(0x7f);
    ((code *)strncpy)(&DAT_008ca838,uVar3);
    DAT_008ca8b7 = 0;
    name = Str_Basename(g_szDialogFileName);
  }
  else {
    strncpy(local_20,param_5,0x1f);
    local_1 = 0;
    name = (char *)strtok(local_20,&DAT_004ea52c);
  }
  data = Resource_Load(0x444e4b42,name);
  if (data == (char *)0x0) {
    return 0;
  }
  uVar4 = 0xffffffff;
  pcVar7 = name;
  do {
    pcVar8 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar8 + -uVar4;
  pcVar8 = data;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  ref = (undefined4 *)
        (*g_pSvcCostume->pAlloc)(0x34,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x87f);
  puVar9 = ref;
  for (iVar6 = 0xd; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  ResRef_Add(ref,data,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x881);
  local_34 = *(int *)(data + 100) + 1;
  local_30 = (undefined4 *)0x0;
  local_30 = (undefined4 *)
             (*g_pSvcCostume->pAlloc)
                       (local_34 * 4,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x885);
  *local_30 = 0;
  if (DAT_008ca7a4 != 0) {
    (*g_pSvcCostume->pFree)(DAT_008ca7a4);
  }
  DAT_008ca7a4 = (*g_pSvcCostume->pAlloc)
                           (*(int *)(data + 100) << 4,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,
                            0x88b);
  if (*(int *)(data + 100) != 0) {
    iVar6 = 0;
    uVar4 = 0;
    do {
      uVar5 = uVar4 + 1;
      iVar6 = iVar6 + 0x10;
      iVar2 = *(int *)(uVar4 * 4 + *(int *)(data + 0x78));
      local_30[uVar4 + 1] = uVar5;
      *(undefined4 *)((DAT_008ca7a4 - 0xc) + iVar6) = *(undefined4 *)(iVar2 + 0xc);
      *(undefined4 *)((DAT_008ca7a4 - 8) + iVar6) = *(undefined4 *)(iVar2 + 0x10);
      *(undefined4 *)((DAT_008ca7a4 - 0x10) + iVar6) = *(undefined4 *)(iVar2 + 0x5c);
      *(undefined4 *)((DAT_008ca7a4 - 4) + iVar6) = 1;
      uVar4 = uVar5;
    } while (uVar5 < *(uint *)(data + 100));
  }
  if ((data[0x24] & 2U) == 0) {
    local_24 = (char *)0x0;
  }
  else {
    local_24 = data + 0x60;
  }
  local_28 = -(uint)(local_24 != (char *)0x0) & DAT_008ca7a4;
  if (param_5 == (char *)0x0) {
    param_5 = name;
  }
  iVar6 = Cos_RegisterComponent(param_1,param_5,ref,param_2,param_3,param_4,&local_34);
  if (iVar6 != 0) {
    if (local_30 != (undefined4 *)0x0) {
      (*g_pSvcCostume->pFree)(local_30);
    }
    _DAT_008ca7b4 = data;
    return 1;
  }
  if (local_30 != (undefined4 *)0x0) {
    (*g_pSvcCostume->pFree)(local_30);
  }
  _DAT_008ca7b4 = (char *)0x0;
  return 0;
}
#undef local_1
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34

