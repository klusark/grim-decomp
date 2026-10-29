/* GRIMFANDANGO.EXE :: modelcomponent.c
 * functions 0x00496890 .. 0x00497810 (19 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00496890  ModelComponent_EditParentOffset ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Editor dialog 'Resolve parent offset' */

undefined4 ModelComponent_EditParentOffset(int *param_1,undefined4 param_2)

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
  iVar3 = Plat_PromptDialog(param_2,&local_24,&param_1,1);
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


/* ---- 0x00496930  ModelComponent_SetVisibleFlag ---- */
void ModelComponent_SetVisibleFlag(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  *(uint *)(param_2 + 0x38) = (uint)(*(int *)(&DAT_004e9ef8 + param_4 * 4) != 0);
  return;
}

/* ---- 0x00496950  ModelComponent_NewInstance ---- */
/* 0x194-byte instance {ResRef model, ..., +0x38 isRoot, +0x40 rdThing, +0x44 parentInstance, +0x48
   parentNode, +0x4c colormap, +0x50 refCount, +0x190 next}; shared with an identical component of
   the actor's current costume */

void * __cdecl ModelComponent_NewInstance(void *cosInst,int componentIdx,int create)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *ref;
  void *thing;
  undefined4 *puVar6;
  int iVar7;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  if (create == 0) {
    pvVar1 = (void *)Cos_InstGetInstanceData(cosInst,componentIdx,0);
    iVar2 = *(int *)((int)pvVar1 + 0x50) + -1;
    *(int *)((int)pvVar1 + 0x50) = iVar2;
    if (iVar2 == 0) {
      ResRef_Remove(pvVar1);
      rdThing_Free(*(undefined4 *)((int)pvVar1 + 0x40));
      (*g_pSvcCostume->pFree)(pvVar1);
    }
    return (void *)0x0;
  }
  local_8 = Cos_InstComponentInfo(cosInst,componentIdx,&local_c,&componentIdx,&local_4);
  iVar2 = Cos_InstGetUserData(cosInst);
  if (iVar2 != 0) {
    iVar3 = Cos_InstCountComponents(iVar2);
    iVar7 = 0;
    if (0 < iVar3) {
      do {
        uVar4 = Cos_InstComponentInfo(iVar2,iVar7,&create,0,0);
        if (create == local_c) {
          iVar5 = _stricmp(uVar4,local_8);
          if (iVar5 == 0) {
            pvVar1 = (void *)Cos_InstGetInstanceData(iVar2,iVar7,0);
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
    (*g_pSvcMain->pAssertFail)(s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
  }
  pvVar1 = *(void **)(iVar2 + 4);
  ref = (undefined4 *)
        (*g_pSvcCostume->pAlloc)(0x194,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xa8d);
  puVar6 = ref;
  for (iVar2 = 0x65; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  ResRef_Add(ref,pvVar1,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xa91);
  thing = (void *)rdThing_New(0);
  rdThing_SetModel(thing,pvVar1);
  uVar4 = rdPuppet_New(thing);
  *(undefined4 *)((int)thing + 0x14) = uVar4;
  ref[0x10] = thing;
  ref[0xf] = *(undefined4 *)(componentIdx + 0x34);
  if (-1 < local_4) {
    puVar6 = (undefined4 *)Cos_InstGetInstanceData(cosInst,local_4,0);
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


/* ---- 0x00496b40  FUN_00496b40 ---- */
undefined4 FUN_00496b40(int param_1)

{
  *(uint *)(param_1 + 0x38) = (uint)(*(int *)(param_1 + 0x44) == 0);
  return 1;
}

/* ---- 0x00496b60  FUN_00496b60 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
bool FUN_00496b60(undefined4 param_1,undefined4 param_2,int param_3,int param_4,char *param_5)

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
    if (DAT_008ca9b8 != '\0') {
      Plat_SetDialogDirectory(&DAT_008ca9b8);
    }
    iVar3 = Plat_OpenFileDialog(s_Select_model_file_to_add____004ea600,
                                s_Model_files____3do__004ea61c);
    if (iVar3 == 0) {
      return false;
    }
    uVar2 = ((code *)Plat_GetDialogFileName)(0x7f);
    ((code *)strncpy)(&DAT_008ca9b8,uVar2);
    DAT_008caa37 = 0;
    param_5 = Str_Basename(g_szDialogFileName);
    data = Resource_Load(0x4c444f4d,g_szDialogFileName);
  }
  else {
    strncpy(&local_20,param_5,0x1f);
    local_1 = 0;
    name = (char *)strtok(&local_20,&DAT_004ea52c);
    uVar1 = strtok(0,&DAT_004ea52c);
    data = Resource_Load(0x4c444f4d,name);
    if (uVar1 != 0) {
      local_24 = (uint)atoi(uVar1);
    }
  }
  if (data == (void *)0x0) {
    return false;
  }
  ref = (undefined4 *)
        (*g_pSvcCostume->pAlloc)(0x38,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xaf9);
  puVar5 = ref;
  for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  ResRef_Add(ref,data,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xafc);
  ref[0xd] = local_24;
  if (pcVar4 == (char *)0x0) {
    pcVar4 = param_5;
  }
  iVar3 = Cos_RegisterComponent(param_1,pcVar4,ref,param_2,param_3,param_4,&DAT_004e9f08);
  return iVar3 != 0;
}
#undef local_1
#undef local_1f
#undef local_20
#undef local_24

#endif


/* ---- 0x00496d10  ModelComponent_Destroy ---- */
undefined4 ModelComponent_Destroy(undefined4 param_1,undefined4 param_2,void *param_3)

{
  ResRef_Remove(param_3);
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}

/* ---- 0x00496d40  FUN_00496d40 ---- */
void FUN_00496d40(undefined4 param_1,int *param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(&DAT_004e9f38 + param_4 * 4);
  iVar2 = *(int *)(*param_2 + 0x40);
  param_2[2] = (uint)(iVar1 != 0);
  *(uint *)(*(int *)(iVar2 + 0x2c) + param_2[1] * 4) = (uint)(iVar1 != 0);
  return;
}

/* ---- 0x00496e20  ModelComponent_Create ---- */
/* Registers a MODL/MMDL component attached to a mesh node ('Mesh N: name'); with no node name the
   editor shows 'Select mesh node to add' */

undefined4
ModelComponent_Create(undefined4 param_1,undefined4 param_2,int *param_3,int param_4,char *param_5)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  bool bVar2;
  char *buf;
  int iVar3;
  undefined *puVar4;
  char **items;
  int iVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  char **ppcVar9;
  uint uVar10;
  char *pcVar11;
  undefined *puVar12;
  #define uStack_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_8 = 1;
  if ((param_3 == (int *)0x0) || ((param_4 != 0x4c444f4d && (param_4 != 0x4c444d4d)))) {
    return 0;
  }
  if (*param_3 == 0) {
    (*g_pSvcMain->pAssertFail)(s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
  }
  iVar6 = param_3[1];
  buf = (char *)(*g_pSvcCostume->pAlloc)(0x2d,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xb94);
  if (param_5 == (char *)0x0) {
    items = (char **)(*g_pSvcCostume->pAlloc)
                               (*(int *)(iVar6 + 0x54) << 2,
                                s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xbb1);
    uStack_c = 0;
    if (*(int *)(iVar6 + 0x54) != 0) {
      iVar3 = 0;
      ppcVar9 = items;
      do {
        pcVar8 = (char *)(*g_pSvcCostume->pAlloc)
                                   (0x2a,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,2999);
        *ppcVar9 = pcVar8;
        iVar5 = 1;
        if (0 < *(int *)(iVar3 + 0x50 + *(int *)(iVar6 + 0x58))) {
          do {
            *pcVar8 = '\t';
            pcVar8 = pcVar8 + 1;
            bVar2 = iVar5 < *(int *)(iVar3 + 0x50 + *(int *)(iVar6 + 0x58));
            iVar5 = iVar5 + 1;
          } while (bVar2);
        }
        strncpy(pcVar8,iVar3 + *(int *)(iVar6 + 0x58),
                0x1f - *(int *)(iVar3 + 0x50 + *(int *)(iVar6 + 0x58)));
        ppcVar9 = ppcVar9 + 1;
        iVar5 = iVar3 + 0x50;
        iVar3 = iVar3 + 0xb8;
        uStack_c = uStack_c + 1;
        pcVar8[0x1f - *(int *)(iVar5 + *(int *)(iVar6 + 0x58))] = '\0';
      } while (uStack_c < *(uint *)(iVar6 + 0x54));
    }
    puVar4 = (undefined *)
             Plat_TreeSelectDialog
                       (s_Select_mesh_node_to_add____004ea65c,items,*(int *)(iVar6 + 0x54),
                        (int *)&local_8);
    if (((local_8 != 0) && (-1 < (int)puVar4)) &&
       (puVar12 = puVar4 + 1, puVar12 < *(undefined **)(iVar6 + 0x54))) {
      iStack_4 = (int)puVar4 * 0xb8;
      iVar3 = (int)puVar12 * 0xb8;
      do {
        iVar5 = *(int *)(iVar6 + 0x58);
        if (*(int *)(iVar3 + 0x50 + iVar5) <= *(int *)(iStack_4 + 0x50 + iVar5)) break;
        sprintf(buf,s_Mesh__d___s__004ea64c,puVar12,iVar3 + iVar5);
        ModelComponent_Create(param_1,param_2,param_3,param_4,buf);
        puVar12 = puVar12 + 1;
        iVar3 = iVar3 + 0xb8;
      } while (puVar12 < *(undefined **)(iVar6 + 0x54));
    }
    uVar7 = 0;
    ppcVar9 = items;
    if (*(int *)(iVar6 + 0x54) != 0) {
      do {
        (*g_pSvcCostume->pFree)(*ppcVar9);
        uVar7 = uVar7 + 1;
        ppcVar9 = ppcVar9 + 1;
      } while (uVar7 < *(uint *)(iVar6 + 0x54));
    }
    (*g_pSvcCostume->pFree)(items);
    if ((int)puVar4 < 0) goto LAB_004970d4;
    sprintf(buf,s_Mesh__d___s__004ea64c,puVar4,*(int *)(iVar6 + 0x58) + (int)puVar4 * 0xb8);
  }
  else {
    uVar7 = 0xffffffff;
    pcVar8 = param_5;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar1 != '\0');
    iVar3 = isdigit((int)*param_5);
    pcVar8 = param_5;
    for (uVar10 = 0; (iVar3 == 0 && (uVar10 <= ~uVar7 - 1)); uVar10 = uVar10 + 1) {
      pcVar11 = pcVar8 + 1;
      pcVar8 = pcVar8 + 1;
      iVar3 = isdigit((int)*pcVar11);
    }
    iVar3 = isdigit((int)*pcVar8);
    if (iVar3 == 0) {
LAB_004970d4:
      (*g_pSvcCostume->pFree)(buf);
      return 0;
    }
    puVar4 = atoi((uint)pcVar8);
    if ((-1 < (int)puVar4) && ((int)puVar4 < *(int *)(iVar6 + 0x54))) {
      uVar7 = 0xffffffff;
      do {
        pcVar8 = param_5;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar8 = param_5 + 1;
        cVar1 = *param_5;
        param_5 = pcVar8;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      pcVar8 = pcVar8 + -uVar7;
      pcVar11 = buf;
      for (uVar10 = uVar7 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar11 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar11 = pcVar11 + 1;
      }
    }
  }
  iVar6 = Cos_RegisterComponent
                    (param_1,buf,(int)puVar4 << 0x10 | (uint)param_3 & 0xffff,param_2,param_3,
                     param_4,&DAT_004e9f48);
  if (iVar6 == 0) {
    (*g_pSvcCostume->pFree)();
    return 0;
  }
  (*g_pSvcCostume->pFree)(buf);
  return 1;
}
#undef iStack_4
#undef local_8
#undef uStack_c


/* ---- 0x00497180  FUN_00497180 ---- */
bool FUN_00497180(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = strchr(param_2,0x29);
  return iVar1 == 0;
}

/* ---- 0x004971a0  FUN_004971a0 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl
FUN_004971a0(int param_1,float param_2,undefined4 param_3,float param_4,uint param_5,uint param_6,
            uint param_7,uint param_8)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  float fVar2;
  float fVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  void *set;
  undefined4 uVar7;
  uint uVar8;
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  iVar5 = Cos_InstGetUserData(param_8);
  fVar3 = param_4;
  fVar2 = param_2;
  pvVar1 = g_pActorTable;
  if ((*(int *)(&DAT_004e9ff8 + (int)param_4 * 4) == 0) &&
     (iVar6 = SoundsIsSoundPlaying(param_2), iVar6 == 0)) {
    if (param_1 != 0x736c6d69) {
      if (param_1 != 0x73736d69) {
        return;
      }
      SoundStartVoiceStream
                (fVar2,*(undefined1 *)((int)fVar2 + 0x20),(int)*(char *)((int)fVar2 + 0x21));
      SoundsSetParam(fVar2,0x400,1);
      SoundsSetParam(fVar2,0x500,*(undefined4 *)((int)fVar2 + 0x24));
      return;
    }
    set = Set_GetCurrent();
    uVar7 = SoundsLoadStartSound(fVar2,*(undefined4 *)((int)fVar2 + 0x24),1);
    if (set == (void *)0x0) {
      return;
    }
    Set_GetSoundParams(set,&param_2,(char *)&param_8,(char *)&param_1,&local_4,&param_4);
    bVar4 = *(byte *)((int)fVar2 + 0x20);
    if ((byte)param_1 < *(byte *)((int)fVar2 + 0x20)) {
      bVar4 = (byte)param_1;
    }
    uVar8 = param_8 & 0xff;
    if ((int)(param_8 & 0xff) <= (int)*(uint *)((int)fVar2 + 0x28)) {
      uVar8 = *(uint *)((int)fVar2 + 0x28);
    }
    Sound_SetPosition(uVar7,(int)pvVar1 + iVar5 * 0xa8 + 0xc,uVar8,bVar4,param_2,param_4);
    return;
  }
  if (*(int *)(&DAT_004e9ff8 + (int)fVar3 * 4) == 1) {
    if (param_1 == 0x736c6d69) {
      SoundsStopSound(fVar2);
      return;
    }
    if (param_1 == 0x73736d69) {
      SoundStopVoiceStream();
      return;
    }
  }
  else if (*(int *)(&DAT_004e9ff8 + (int)fVar3 * 4) == 2) {
    iMUSE_SetHook(fVar2,0x80);
  }
  return;
}
#undef local_4

#endif


/* ---- 0x00497320  FUN_00497320 ---- */
undefined4 FUN_00497320(int *param_1,undefined4 param_2)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  char cVar6;
  #define local_40 (*(uint *)(_frame + (0x50 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x50 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(char (*)[32])(_frame + (0x50 - 0x20)))
  
  iVar1 = *param_1;
  local_30 = (uint)s_Maximum_Volume_004ea6a8;
  local_2c = (uint)&DAT_004ea6a4;
  local_28 = (uint)s_Priority_004ea698;
  local_24 = (uint)s_Minimum_Volume_004ea688;
  local_40 = (uint)*(byte *)(iVar1 + 0x20);
  local_3c = (uint)*(char *)(iVar1 + 0x21);
  local_38 = *(uint *)(iVar1 + 0x24);
  local_34 = *(uint *)(iVar1 + 0x28);
  iVar2 = Plat_PromptDialog(param_2,&local_30,&local_40,4);
  if ((iVar2 != 0) && ((int)local_34 <= (int)local_40)) {
    iVar2 = strtok(param_2,&DAT_004ea52c);
    if ((int)local_40 < 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = local_40;
      if (0x7f < (int)local_40) {
        uVar4 = 0x7f;
      }
    }
    *(char *)(iVar1 + 0x20) = (char)uVar4;
    if ((int)local_3c < 0) {
      cVar6 = '\0';
    }
    else if ((int)local_3c < 0x80) {
      cVar6 = (char)local_3c;
    }
    else {
      cVar6 = '\x7f';
    }
    *(char *)(iVar1 + 0x21) = cVar6;
    if ((int)local_38 < 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = local_38;
      if (0x7f < (int)local_38) {
        uVar5 = 0x7f;
      }
    }
    *(uint *)(iVar1 + 0x24) = uVar5;
    if ((int)local_34 < 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = local_34;
      if (0x7f < (int)local_34) {
        uVar3 = 0x7f;
      }
    }
    *(uint *)(iVar1 + 0x28) = uVar3;
    sprintf(local_20,s__s__d__d__d__d_004ea678,iVar2,uVar4 & 0xff,(int)cVar6,uVar5,uVar3);
    strncpy(iVar2,local_20,0x1f);
    *(undefined1 *)(iVar2 + 0x1f) = 0;
    return 1;
  }
  return 0;
}
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40


/* ---- 0x00497460  FUN_00497460 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
bool FUN_00497460(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,char *param_5
                 )

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  undefined4 uVar2;
  char *pcVar3;
  int iVar4;
  undefined1 uVar5;
  undefined *puVar6;
  undefined4 *puVar7;
  #define local_25 (*(undefined1 *)(_frame + (0x40 - 0x25)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(char *)(_frame + (0x40 - 0x20)))
  #define local_1f (*(undefined4 *)(_frame + (0x40 - 0x1f)))
  #define local_1 (*(undefined1 *)(_frame + (0x40 - 0x1)))
  
  local_20 = DAT_004f5a98;
  uVar5 = 0x7f;
  puVar7 = &local_1f;
  for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  *(undefined2 *)puVar7 = 0;
  *(undefined1 *)((int)puVar7 + 2) = 0;
  local_25 = 0x40;
  puVar6 = (undefined *)0x64;
  local_24 = 1;
  if (param_3 != 0) {
    return false;
  }
  if (param_5 == (char *)0x0) {
    if (DAT_008caa38 != '\0') {
      Plat_SetDialogDirectory(&DAT_008caa38);
    }
    iVar4 = Plat_OpenFileDialog(s_Select_sound_file_to_add____004ea6b8,
                                s_Sound_files____imu____imc____wvc_004ea6d4);
    if (iVar4 == 0) {
      return false;
    }
    uVar2 = ((code *)Plat_GetDialogFileName)(0x7f);
    ((code *)strncpy)(&DAT_008caa38,uVar2);
    DAT_008caab7 = 0;
    param_5 = Str_Basename(g_szDialogFileName);
  }
  else {
    strncpy(&local_20,param_5,0x1f);
    local_1 = 0;
    strtok(&local_20,&DAT_004ea52c);
    uVar1 = strtok(0,&DAT_004ea52c);
    if (uVar1 != 0) {
      puVar6 = atoi(uVar1);
      uVar5 = SUB41(puVar6,0);
      uVar1 = strtok(0,&DAT_004ea52c);
      puVar6 = atoi(uVar1);
      local_25 = SUB41(puVar6,0);
      uVar1 = strtok(0,&DAT_004ea52c);
      puVar6 = atoi(uVar1);
      uVar1 = strtok(0,&DAT_004ea52c);
      local_24 = (uint)atoi(uVar1);
    }
  }
  iVar4 = (*g_pSvcCostume->pAlloc)(0x2c,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xcee);
  if (iVar4 == 0) {
    return false;
  }
  pcVar3 = &local_20;
  if (local_20 == '\0') {
    pcVar3 = param_5;
  }
  strncpy(iVar4,pcVar3,0x1f);
  *(undefined1 *)(iVar4 + 0x21) = local_25;
  *(uint *)(iVar4 + 0x28) = local_24;
  *(undefined1 *)(iVar4 + 0x1f) = 0;
  *(undefined1 *)(iVar4 + 0x20) = uVar5;
  *(undefined **)(iVar4 + 0x24) = puVar6;
  iVar4 = Cos_RegisterComponent(param_1,param_5,iVar4,param_2,0,param_4,&DAT_004ea018);
  return iVar4 != 0;
}
#undef local_1
#undef local_1f
#undef local_20
#undef local_24
#undef local_25

#endif


/* ---- 0x00497640  FUN_00497640 ---- */
undefined4 FUN_00497640(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}

/* ---- 0x00497660  FUN_00497660 ---- */
undefined4 FUN_00497660(undefined4 param_1)

{
  SoundsStopSound(param_1);
  return 1;
}

/* ---- 0x00497680  FUN_00497680 ---- */
/* WARNING: Variable defined which should be unmapped: local_4 */

void FUN_00497680(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  lua_pushnumber((float)param_4);
  lua_setglobal(param_2);
  return;
}
#undef local_4


/* ---- 0x004976a0  FUN_004976a0 ---- */
undefined4 FUN_004976a0(undefined4 *param_1,int param_2,int param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *defaultText;
  int iVar1;
  #define local_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  defaultText = (char *)*param_1;
  iVar1 = Plat_InputDialog(s_Change_variable_properties_004ea72c,s_Variable_name_004ea748,local_20,
                           0x20,defaultText);
  if (iVar1 != 0) {
    strncpy(defaultText,local_20,0x1f);
    defaultText[0x1f] = '\0';
    strncpy(param_2,local_20,param_3 + -1);
    *(undefined1 *)(param_3 + -1 + param_2) = 0;
    return 1;
  }
  return 0;
}
#undef local_20


/* ---- 0x00497710  FUN_00497710 ---- */
bool FUN_00497710(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *puVar2;
  #define local_20 (*(char *)(_frame + (0x30 - 0x20)))
  #define local_1f (*(undefined4 *)(_frame + (0x30 - 0x1f)))
  #define local_1 (*(undefined1 *)(_frame + (0x30 - 0x1)))
  
  local_20 = DAT_004f5a98;
  puVar2 = &local_1f;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)puVar2 = 0;
  *(undefined1 *)((int)puVar2 + 2) = 0;
  if (param_3 != 0) {
    return false;
  }
  if (param_5 == 0) {
    iVar1 = Plat_InputDialog(s_Name_of_variable_004ea758,s_Variable_name_004ea748,&local_20,0x20,
                             &local_20);
    if (iVar1 == 0) {
      return false;
    }
  }
  else {
    strncpy(&local_20,param_5,0x1f);
    local_1 = 0;
  }
  iVar1 = (*g_pSvcCostume->pAlloc)(0x20,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xd86);
  if (iVar1 == 0) {
    return false;
  }
  strncpy(iVar1,&local_20,0x1f);
  *(undefined1 *)(iVar1 + 0x1f) = 0;
  iVar1 = Cos_RegisterComponent(param_1,iVar1,iVar1,param_2,0,param_4,0);
  return iVar1 != 0;
}
#undef local_1
#undef local_1f
#undef local_20


/* ---- 0x004977f0  FUN_004977f0 ---- */
undefined4 FUN_004977f0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}

/* ---- 0x00497810  FUN_00497810 ---- */
undefined4 FUN_00497810(undefined4 param_1)

{
  lua_pushnil();
  lua_setglobal(param_1);
  return 1;
}
