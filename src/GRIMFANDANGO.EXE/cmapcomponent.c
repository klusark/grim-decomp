/* GRIMFANDANGO.EXE :: cmapcomponent.c
 * functions 0x00496370 .. 0x004965b0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00496370  CmapComponent_NewInstance ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Costume tag handler for 'RDroid Colormap' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 5, instance data for a colormap component (0x38 bytes
   holding a ResRef to the colormap, 'Bad Colormap Reference' assertion); with param 0 it frees the
   instance. */

int * __cdecl CmapComponent_NewInstance(int inst,int component,int create)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define auStack_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  if (create == 0) {
    iVar1 = Cos_InstGetInstanceData(inst,component,(int *)0x0);
    ResRef_Remove((void *)(iVar1 + 4));
    (*g_pSvcCostume->pFree)(iVar1);
    return (int *)0x0;
  }
  piVar2 = (int *)(*g_pSvcCostume->pAlloc)(0x38,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x8fa);
  Cos_InstComponentInfo(inst,component,(int)auStack_4,(int)&create,(int)&iStack_8);
  iVar1 = create;
  piVar4 = piVar2;
  for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar4 = 0;
    piVar4 = piVar4 + 1;
  }
  if (*(int *)create == 0) {
    (*g_pSvcMain->pAssertFail)
              (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
  }
  ResRef_Add(piVar2 + 1,*(void **)(iVar1 + 4),s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x8ff);
  iVar1 = Cos_InstGetInstanceData(inst,iStack_8,(int *)0x0);
  *piVar2 = iVar1;
  return piVar2;
}
#undef auStack_4
#undef iStack_8

#endif


/* ---- 0x00496460  CmapComponent_Create ---- */
/* Registers a 'cmap' colormap component (CMAP resource, 0x34-byte ResRef); with no name a file
   dialog asks for one (editor) */

int CmapComponent_Create(uint param_1,int param_2,int param_3,int param_4,char *param_5)

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
    iVar3 = Cos_RegisterComponent(param_1,(int)pcVar2,(int)ref,param_2,param_3,param_4,IMG_ADDR(0x004e9f20));
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 FUN_004965b0(void)

{
  int in_stack_00000010;
  code *in_stack_00000014;
  
  (*in_stack_00000014)(in_stack_00000010 + 8,4);
  return 1;
}
#endif

