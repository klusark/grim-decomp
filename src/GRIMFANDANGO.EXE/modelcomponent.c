/* GRIMFANDANGO.EXE :: modelcomponent.c
 * functions 0x00496890 .. 0x00496d10 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00496890  ThingAdjuster ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Editor dialog 'Resolve parent offset' Original name ThingAdjuster (the remaster's GrimFandango
   (Linux): strings: '%s,%d' | 'Resolve parent offset (0 = off)'); was
   ModelComponent_EditParentOffset. */

undefined4 ThingAdjuster(int *param_1,undefined4 param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(char (*)[32])(_frame + (0x40 - 0x20)))
  
  uVar2 = param_2;
  iVar1 = *param_1;
  local_24 = (uint)s_Resolve_parent_offset__0___off__004ea5e0;
  param_1 = (int *)(uint)(*(int *)(iVar1 + 0x34) != 0);
  iVar3 = grimPlat_SpinDialog(param_2,&local_24,&param_1,1);
  if (iVar3 != 0) {
    iVar3 = strtok(uVar2,&DAT_004ea52c);
    *(int **)(iVar1 + 0x34) = param_1;
    sprintf(local_20,s__s__d_004ea5d8,iVar3,param_1);
    strncpy(iVar3,local_20,0x1f);
    *(undefined1 *)(iVar3 + 0x1f) = 0;
    return 1;
  }
  return 0;
}
#undef local_20
#undef local_24

#endif


/* ---- 0x00496930  ThingChanger ---- */
/* Original name ThingChanger (the remaster's GrimFandango (Linux): the same handler slot (changer)
   of the same costume tag registration in sputCostume_Startup); was ModelComponent_SetVisibleFlag.
    */

void ThingChanger(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  *(uint *)(param_2 + 0x38) = (uint)(*(int *)(&g_aThingCommands + param_4 * 4) != 0);
  return;
}

/* ---- 0x00496950  ThingInstancer ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* 0x194-byte instance {ResRef model, ..., +0x38 isRoot, +0x40 rdThing, +0x44 parentInstance, +0x48
   parentNode, +0x4c colormap, +0x50 refCount, +0x190 next}; shared with an identical component of
   the actor's current costume
   Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
   Original name ThingInstancer (the remaster's GrimFandango (Linux): the only unmatched caller of
   rdPuppet_New; 3 matched neighbours agree, 0 disagree); was ModelComponent_NewInstance. */

void * __cdecl ThingInstancer(void *cosInst,int componentIdx,int create)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  int iVar2;
  uint extraout_EAX;
  int iVar3;
  undefined4 extraout_EAX_00;
  int iVar4;
  undefined4 *ref;
  void *thing;
  undefined4 uVar5;
  undefined4 *puVar6;
  int iVar7;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  if (create == 0) {
    pvVar1 = (void *)Cos_InstGetInstanceData((int)cosInst,componentIdx,(int *)0x0);
    iVar2 = *(int *)((int)pvVar1 + 0x50) + -1;
    *(int *)((int)pvVar1 + 0x50) = iVar2;
    if (iVar2 == 0) {
      Res_RemoveReference(pvVar1);
      rdThing_Free(*(undefined4 *)((int)pvVar1 + 0x40));
      (*g_pSputCosHS->pFree)(pvVar1);
    }
    return (void *)0x0;
  }
  Cos_InstComponentInfo((int)cosInst,componentIdx,(int)&local_c,(int)&componentIdx,(int)&local_4);
  local_8 = extraout_EAX;
  iVar2 = Cos_InstGetUserData((int)cosInst);
  if (iVar2 != 0) {
    iVar3 = Cos_InstCountComponents(iVar2);
    iVar7 = 0;
    if (0 < iVar3) {
      do {
        Cos_InstComponentInfo(iVar2,iVar7,(int)&create,0,0);
        if (create == local_c) {
          iVar4 = _stricmp(extraout_EAX_00,local_8);
          if (iVar4 == 0) {
            pvVar1 = (void *)Cos_InstGetInstanceData(iVar2,iVar7,(int *)0x0);
            *(int *)((int)pvVar1 + 0x50) = *(int *)((int)pvVar1 + 0x50) + 1;
            return pvVar1;
          }
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 < iVar3);
    }
  }
  iVar2 = componentIdx;
  if (*(int *)componentIdx == 0) {
    (*g_pStd_HS->pAssertFail)(s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
  }
  pvVar1 = *(void **)(iVar2 + 4);
  ref = (undefined4 *)
        (*g_pSputCosHS->pAlloc)(0x194,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xa8d);
  puVar6 = ref;
  for (iVar2 = 0x65; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  Res_SetReference(ref,pvVar1,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xa91);
  thing = (void *)rdThing_New(0);
  rdThing_SetModel3(thing,pvVar1);
  uVar5 = rdPuppet_New(thing);
  *(undefined4 *)((int)thing + 0x14) = uVar5;
  ref[0x10] = thing;
  ref[0xf] = *(undefined4 *)(componentIdx + 0x34);
  if (-1 < local_4) {
    puVar6 = (undefined4 *)Cos_InstGetInstanceData((int)cosInst,local_4,(int *)0x0);
    ref[0x11] = *puVar6;
    ref[0x12] = puVar6[1];
    ref[0xe] = 0;
    ref[0x14] = ref[0x14] + 1;
    return ref;
  }
  ref[0x11] = 0;
  ref[0x12] = 0xffffffff;
  ref[0xe] = 1;
  ref[0x14] = ref[0x14] + 1;
  return ref;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x00496b40  ThingStopper ---- */
/* Costume tag handler for 'MAIN RDroid Thing (3DO) / RDroid Thing (3DO)' (registered by
   sputCostume_Start through Cos_NewStateBasedTag/Cos_NewIntTag): slot 3, restores the default
   visibility flag (+0x38 = (+0x44 == 0)). Original name ThingStopper (the remaster's GrimFandango
   (Linux): the same handler slot (stopper) of the same costume tag registration in
   sputCostume_Startup); was ModelComponent_Stop. */

undefined4 ThingStopper(int param_1)

{
  *(uint *)(param_1 + 0x38) = (uint)(*(int *)(param_1 + 0x44) == 0);
  return 1;
}

/* ---- 0x00496b60  ThingRequester ---- */
/* Costume tag handler for 'MAIN RDroid Thing (3DO) / RDroid Thing (3DO)' (registered by
   sputCostume_Startup through Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, builds a key from 'name
   x y' text or asks for a .3do file ('Select model file to add...') and loads it as a model
   resource. */

int ThingRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *name;
  uint uVar1;
  void *data;
  undefined4 uVar2;
  undefined4 *ref;
  int iVar3;
  char *pcVar4;
  undefined4 *puVar5;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(undefined1 *)(_frame + (0x40 - 0x20)))
  #define local_1f (*(undefined4 *)(_frame + (0x40 - 0x1f)))
  #define local_1 (*(undefined1 *)(_frame + (0x40 - 0x1)))
  
  pcVar4 = param_5;
  local_20 = DAT_004f5a98;
  local_24 = 1;
  puVar5 = &local_1f;
  for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  *(undefined2 *)puVar5 = 0;
  *(undefined1 *)((int)puVar5 + 2) = 0;
  if ((param_3 != 0) && (param_4 != 0x4853454d)) {
    return false;
  }
  if (param_5 == (char *)0x0) {
    if (g_bModelPath != '\0') {
      grimPlat_SetDefaultOpenPath(&g_bModelPath);
    }
    iVar3 = grimPlat_OpenFileRequest
                      (s_Select_model_file_to_add____004ea600,s_Model_files____3do__004ea61c);
    if (iVar3 == 0) {
      return false;
    }
    uVar2 = ((code *)grimPlat_GetDefaultOpenPath)(0x7f);
    ((code *)strncpy)(&g_bModelPath,uVar2);
    DAT_008caa37 = 0;
    param_5 = stdFnames_FindMedName(g_szGrimlib_aFilename);
    data = sputResource_Alloc(0x4c444f4d,g_szGrimlib_aFilename);
  }
  else {
    strncpy(&local_20,param_5,0x1f);
    local_1 = 0;
    name = (char *)strtok(&local_20,&DAT_004ea52c);
    uVar1 = strtok(0,&DAT_004ea52c);
    data = sputResource_Alloc(0x4c444f4d,name);
    if (uVar1 != 0) {
      local_24 = (uint)atoi(uVar1);
    }
  }
  if (data == (void *)0x0) {
    return false;
  }
  ref = (undefined4 *)
        (*g_pSputCosHS->pAlloc)(0x38,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xaf9);
  puVar5 = ref;
  for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  Res_SetReference(ref,data,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xafc);
  ref[0xd] = local_24;
  if (pcVar4 == (char *)0x0) {
    pcVar4 = param_5;
  }
  iVar3 = Cos_RegisterComponent(param_1,(int)pcVar4,(int)ref,param_2,param_3,param_4,((unsigned)(uintptr_t)&DAT_004e9f08));
  return iVar3 != 0;
}
#undef local_1
#undef local_1f
#undef local_20
#undef local_24


/* ---- 0x00496d10  ThingFreer ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name ThingFreer (the remaster's GrimFandango (Linux): the same handler slot (freer) of
   the same costume tag registration in sputCostume_Startup); was ModelComponent_Destroy. */

undefined4 ThingFreer(undefined4 param_1,undefined4 param_2,void *param_3)

{
  Res_RemoveReference(param_3);
  (*g_pSputCosHS->pFree)(param_3);
  return 1;
}
