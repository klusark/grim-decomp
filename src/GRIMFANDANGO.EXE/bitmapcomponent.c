/* GRIMFANDANGO.EXE :: bitmapcomponent.c
 * functions 0x004960a0 .. 0x00496340 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004960a0  BitmapRequester ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Costume tag handler for 'General Bitmap / Animation (old use Bitmap)' (registered by
   sputCostume_Start through Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, builds a bitmap key or
   asks for an image file (.pcx/.gif/.lbm) and loads it as a bitmap resource. */

undefined4 BitmapRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  char cVar2;
  int iVar3;
  char *name;
  undefined4 uVar4;
  char *data;
  undefined4 *ref;
  uint uVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  undefined4 *puVar10;
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(undefined1 (*)[31])(_frame + (0x50 - 0x20)))
  #define local_1 (*(undefined1 *)(_frame + (0x50 - 0x1)))
  
  local_34 = 1;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  if (param_5 == (char *)0x0) {
    if (DAT_008ca838 != '\0') {
      Plat_SetDialogDirectory(&DAT_008ca838);
    }
    iVar7 = Plat_OpenFileDialog(s_Select_image_file_to_add____004ea4b8,
                                s_Graphics_files____pcx____gif___l_004ea4d4);
    if (iVar7 == 0) {
      return 0;
    }
    uVar4 = ((code *)Plat_GetDialogFileName)(0x7f);
    ((code *)strncpy)(&DAT_008ca838,uVar4);
    DAT_008ca8b7 = 0;
    name = Str_Basename(g_szDialogFileName);
  }
  else {
    strncpy(local_20,param_5,0x1f);
    local_1 = 0;
    name = (char *)strtok(local_20,&DAT_004ea52c);
  }
  data = sputResource_Alloc(0x444e4b42,name);
  if (data == (char *)0x0) {
    return 0;
  }
  uVar5 = 0xffffffff;
  pcVar8 = name;
  do {
    pcVar9 = pcVar8;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar9 = pcVar8 + 1;
    cVar2 = *pcVar8;
    pcVar8 = pcVar9;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  pcVar8 = pcVar9 + -uVar5;
  pcVar9 = data;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar9 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar9 = pcVar9 + 1;
  }
  ref = (undefined4 *)
        (*g_pSvcCostume->pAlloc)(0x34,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x87f);
  puVar10 = ref;
  for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  Res_SetReference(ref,data,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x881);
  local_34 = *(int *)(data + 100) + 1;
  local_30 = 0;
  local_30 = (*g_pSvcCostume->pAlloc)
                       (local_34 * 4,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x885);
  *(undefined4 *)local_30 = 0;
  if (UINT_008ca7a4 != 0) {
    (*g_pSvcCostume->pFree)(UINT_008ca7a4);
  }
  UINT_008ca7a4 =
       (*g_pSvcCostume->pAlloc)
                 (*(int *)(data + 100) << 4,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x88b);
  uVar5 = 0;
  if (*(int *)(data + 100) != 0) {
    iVar7 = 0;
    do {
      iVar1 = uVar5 * 4;
      uVar5 = uVar5 + 1;
      iVar7 = iVar7 + 0x10;
      iVar3 = *(int *)(iVar1 + *(int *)(data + 0x78));
      *(uint *)(local_30 + 4 + iVar1) = uVar5;
      *(undefined4 *)((UINT_008ca7a4 - 0xc) + iVar7) = *(undefined4 *)(iVar3 + 0xc);
      *(undefined4 *)((UINT_008ca7a4 - 8) + iVar7) = *(undefined4 *)(iVar3 + 0x10);
      *(undefined4 *)((UINT_008ca7a4 - 0x10) + iVar7) = *(undefined4 *)(iVar3 + 0x5c);
      *(undefined4 *)((UINT_008ca7a4 - 4) + iVar7) = 1;
    } while (uVar5 < *(uint *)(data + 100));
  }
  if ((data[0x24] & 2U) == 0) {
    local_24 = 0;
  }
  else {
    local_24 = (uint)(data + 0x60);
  }
  local_28 = -(uint)((char *)local_24 != (char *)0x0) & UINT_008ca7a4;
  if (param_5 == (char *)0x0) {
    param_5 = name;
  }
  iVar7 = Cos_RegisterComponent
                    (param_1,(int)param_5,(int)ref,param_2,param_3,param_4,(int)&local_34);
  if (iVar7 != 0) {
    if (local_30 != 0) {
      (*g_pSvcCostume->pFree)(local_30);
    }
    _DAT_008ca7b4 = data;
    return 1;
  }
  if (local_30 != 0) {
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


/* ---- 0x00496340  BitmapComponent_Destroy ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Costume tag handler, slot 2 of the 'General Bitmap' / 'Animation (old use Bitmap)' tags: frees
   the key data. (Was named SpriteComponent_Destroy; the tag table in sputCostume_Start pairs it
   with the bitmap tags.) */

undefined4 BitmapComponent_Destroy(undefined4 param_1,undefined4 param_2,void *param_3)

{
  _DAT_008ca7b4 = param_3;
  Res_RemoveReference(param_3);
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}
