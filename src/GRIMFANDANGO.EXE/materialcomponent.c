/* GRIMFANDANGO.EXE :: materialcomponent.c
 * functions 0x004965d0 .. 0x00496670 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004965d0  MaterialComponent_OnKey ---- */
/* Costume tag handler for 'RDroid Animated Material' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, stores the key value as the current frame of the
   animated material (+8). */

void MaterialComponent_OnKey(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined4 *)(param_2 + 8) = param_4;
  return;
}

/* ---- 0x004965e0  MaterialComponent_NewInstance ---- */
/* Costume tag handler, slot 5 of the 'RDroid Animated Material' tag: instance data for an animated
   material. (Was named CmapComponent_NewInstance.) */

void * __cdecl MaterialComponent_NewInstance(void *cosInst,int componentIdx,int create)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  #define auStack_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  if (create == 0) {
    iVar1 = Cos_InstGetInstanceData((int)cosInst,componentIdx,(int *)0x0);
    (*g_pSputCosHS->pFree)(iVar1);
    return (void *)0x0;
  }
  piVar2 = (int *)(*g_pSputCosHS->pAlloc)(0xc,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x9a1);
  Cos_InstComponentInfo((int)cosInst,componentIdx,(int)auStack_4,(int)(piVar2 + 1),(int)&create);
  iVar1 = Cos_InstGetInstanceData((int)cosInst,create,(int *)0x0);
  *piVar2 = iVar1;
  piVar2[2] = 0;
  return piVar2;
}
#undef auStack_4


/* ---- 0x00496670  MaterialRequester ---- */
/* Costume tag handler for 'RDroid Animated Material' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, parses a key or asks for a .mat file ('Select mat
   file to animate...') for a model/sprite component. Original name MaterialRequester (the
   remaster's GrimFandango (Linux): strings: 'Select mat file to animate...'); was
   MaterialComponent_Create. */

int MaterialRequester(uint param_1,int param_2,int *param_3,int param_4,char *param_5)

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
    (*g_pStd_HS->pAssertFail)(s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
  }
  iVar5 = param_3[1];
  if (param_5 == (char *)0x0) {
    if (g_bMaterialPath != '\0') {
      Plat_SetDialogDirectory(&g_bMaterialPath);
    }
    iVar2 = Plat_OpenFileDialog(s_Select_mat_file_to_animate____004ea584,
                                s_Material_files____mat__004ea5a4);
    if (iVar2 == 0) {
      return false;
    }
    uVar3 = ((code *)Plat_GetDialogFileName)(0x7f);
    ((code *)strncpy)(&g_bMaterialPath,uVar3);
    DAT_008ca9b7 = 0;
    pcStack_18 = Str_Basename(g_szGrimlib_aFilename);
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
    if (g_dwLECBitmaps != 0) {
      (*g_pSputCosHS->pFree)(g_dwLECBitmaps);
    }
    g_dwLECBitmaps =
         (*g_pSputCosHS->pAlloc)(local_14 << 4,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x9ee);
    if (*(int *)(iVar5 + 0x60) != 0) {
      iVar2 = 0;
      piVar6 = (int *)(iVar5 + 0x68);
      do {
        iVar1 = *piVar6;
        uVar7 = uVar7 + 1;
        piVar6 = piVar6 + 1;
        iVar2 = iVar2 + 0x10;
        iVar1 = *(int *)(*(int *)(iVar1 + 0x1c) + 0x1c);
        *(undefined4 *)((g_dwLECBitmaps - 0xc) + iVar2) = *(undefined4 *)(iVar1 + 0xc);
        *(undefined4 *)((g_dwLECBitmaps - 8) + iVar2) = *(undefined4 *)(iVar1 + 0x10);
        *(undefined4 *)((g_dwLECBitmaps - 0x10) + iVar2) = *(undefined4 *)(iVar1 + 0x5c);
        *(undefined4 *)((g_dwLECBitmaps - 4) + iVar2) = 1;
      } while (uVar7 < *(uint *)(iVar5 + 0x60));
    }
    local_4 = 0;
    local_8 = g_dwLECBitmaps;
    if (param_5 == (char *)0x0) {
      param_5 = pcStack_18;
    }
    iVar5 = Cos_RegisterComponent
                      (param_1,(int)param_5,uStack_1c,param_2,(int)param_3,param_4,(int)&local_14);
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

