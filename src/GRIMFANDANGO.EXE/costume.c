/* GRIMFANDANGO.EXE :: costume.c
 * functions 0x00493410 .. 0x00496020 (17 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00493410  FadeInChore ---- */
/* Cos_StartChoreFaded(inst, chore, ms): play the chore, advance it 70 ms, fade its keyframes in
   over ms (130 for the move chores). Original name FadeInChore (the remaster's GrimFandango
   (Linux): the only unmatched caller of Chore_FadeIn; 1 matched neighbours agree, 0 disagree); was
   Cos_StartChoreFaded. */

void FadeInChore(void *param_1,uint param_2,int param_3)

{
  Cos_InstPlayChore((int)param_1,param_2,1,0);
  Cos_InstUpdateChore((int)param_1,param_2,0x46);
  sputCostume_FadeKeysIn(param_1,param_2,param_3);
  return;
}

/* ---- 0x00493450  FadeOutChore ---- */
/* Cos_StopChoreFaded(inst, chore, ms): fade the chore's keyframes out over ms, then stop the chore
   (chore -1: all). Original name FadeOutChore (the remaster's GrimFandango (Linux): the only
   unmatched callee of sputActor_SetWalkChore; the only unmatched caller of Chore_FadeOut; 2 matched
   neighbours agree, 0 disagree); was Cos_StopChoreFaded. */

undefined * __cdecl FadeOutChore(void *param_1,int param_2,int param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  
  if (param_2 == -1) {
    puVar1 = (undefined *)Cos_InstCountChores((int)param_1);
    iVar3 = 0;
    if (0 < (int)puVar1) {
      do {
        puVar2 = FadeOutChore(param_1,iVar3,param_3);
        iVar3 = iVar3 + 1;
      } while (iVar3 < (int)puVar1);
      return puVar2;
    }
  }
  else {
    sputCostume_FadeKeysOut(param_1,param_2,param_3);
    puVar1 = (undefined *)Cos_InstStopChore((int)param_1,param_2);
  }
  return puVar1;
}

/* ---- 0x00494d10  sputCostume_PrintCostumeInfo ---- */
/* Original name sputCostume_PrintCostumeInfo (the remaster's GrimFandango (Linux): the only
   unmatched callee of Lua_PrintActorCostumes; 1 matched neighbours agree, 0 disagree); was
   Costume_PrintList. */

void __cdecl sputCostume_PrintCostumeInfo(CostumeNode *costume)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  CostumeNode **ppCVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  CostumeNode *pCVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pCVar6 = costume;
  if (costume != (CostumeNode *)0x0) {
    do {
      iVar3 = Cos_InstCountChores(pCVar6->dwInstance);
      uVar5 = 0;
      if (0 < iVar3) {
        do {
          Cos_InstChoreStatus(pCVar6->dwInstance,uVar5);
          uVar5 = uVar5 + 1;
        } while ((int)uVar5 < iVar3);
      }
      ppCVar1 = &pCVar6->pNext;
      pCVar6 = *ppCVar1;
    } while (*ppCVar1 != (CostumeNode *)0x0);
    for (pvVar2 = costume->pComponents; pvVar2 != (void *)0x0;
        pvVar2 = *(void **)((int)pvVar2 + 400)) {
      if (*(int *)((int)pvVar2 + 0x38) != 0) {
        uVar5 = 0;
        iVar3 = *(int *)(*(int *)((int)pvVar2 + 0x40) + 4);
        if (*(int *)(iVar3 + 0x54) != 0) {
          iVar4 = 0;
          do {
            String_ContainsSubstring(*(int *)(iVar3 + 0x58) + iVar4,s_skirt_004ea1a8);
            uVar5 = uVar5 + 1;
            iVar4 = iVar4 + 0xb8;
          } while (uVar5 < *(uint *)(iVar3 + 0x54));
        }
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x00494dc0  sputCostume_FreeCostumeNodes ---- */
/* Original name sputCostume_FreeCostumeNodes (the remaster's GrimFandango (Linux): aligned call in
   sputActor_FreeActor); was Costume_FreeList. */

void __cdecl sputCostume_FreeCostumeNodes(CostumeNode *list,int free)

{
  CostumeNode *pCVar1;
  
  while (list != (CostumeNode *)0x0) {
    pCVar1 = list->pNext;
    if (free != 0) {
      Cos_FreeCosInstance(list->dwInstance);
    }
    if (list->aCostumeRef[0] != 0) {
      Res_RemoveReference(list->aCostumeRef);
    }
    Pool_Free(list);
    list = pCVar1;
  }
  return;
}

/* ---- 0x00494e10  sputCostume_PopCostume ---- */
/* Original name sputCostume_PopCostume (the remaster's GrimFandango (Linux): the only unmatched
   callee of Actor_PopCostume; 1 matched neighbours agree, 0 disagree); was Costume_Pop. */

CostumeNode * __cdecl sputCostume_PopCostume(CostumeNode *list,int free)

{
  CostumeNode *pCVar1;
  
  pCVar1 = (CostumeNode *)0x0;
  if (list != (CostumeNode *)0x0) {
    pCVar1 = list->pNext;
    list->pNext = (CostumeNode *)0x0;
    Cos_InstStopChores(list->dwInstance);
    sputCostume_FreeCostumeNodes(list,free);
  }
  return pCVar1;
}

/* ---- 0x00494e50  sputCostume_SetCostume ---- */
/* Original name sputCostume_SetCostume (the remaster's GrimFandango (Linux): aligned call in
   sputActor_SetCostume); was Costume_ReplaceTop. */

CostumeNode * __cdecl sputCostume_SetCostume(CostumeNode *list,void *costumeRes,int flags)

{
  CostumeNode *pCVar1;
  
  pCVar1 = sputCostume_PopCostume(list,1);
  pCVar1 = sputCostume_PushCostume(pCVar1,costumeRes,flags);
  return pCVar1;
}

/* ---- 0x00494e80  sputCostume_PushCostume ---- */
/* Source: Engine/sputCostume.cpp (line 1146, from __FILE__/__LINE__ passed to the allocator)
   Original name sputCostume_PushCostume (the remaster's GrimFandango (Linux): aligned call in
   sputActor_PushCostume, sputCostume_SetCostume); was Costume_Push. */

CostumeNode * __cdecl sputCostume_PushCostume(CostumeNode *list,void *costumeRes,int flags)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  CostumeNode *pCVar1;
  uint uVar2;
  void *pvVar3;
  uint uVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pCVar1 = Costume_AllocRecord();
  pCVar1->pNext = list;
  if (flags == 0) {
    if (list == (CostumeNode *)0x0) {
      uVar2 = 0;
    }
    else {
      uVar2 = list->dwInstance;
    }
    uVar2 = Cos_CreateCosInstance(costumeRes,uVar2);
    pCVar1->dwInstance = uVar2;
    Res_SetReference(pCVar1->aCostumeRef,costumeRes,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,
                     0x47a);
  }
  else {
    pCVar1->dwInstance = flags;
  }
  pvVar3 = Costume_GetMainModel((void *)pCVar1->dwInstance);
  pCVar1->pMainModel = pvVar3;
  if (((pvVar3 != (void *)0x0) && (list != (CostumeNode *)0x0)) && (list->pMainModel == pvVar3)) {
    pCVar1->aHeadJoints[0] = list->aHeadJoints[0];
    pCVar1->aHeadJoints[1] = list->aHeadJoints[1];
    pCVar1->aHeadJoints[2] = list->aHeadJoints[2];
    pCVar1->flLookRate = list->flLookRate;
    pCVar1->flMaxPitch = list->flMaxPitch;
    pCVar1->flMaxYaw = list->flMaxYaw;
    pCVar1->flViewCos = list->flViewCos;
    pCVar1->pComponents = list->pComponents;
  }
  uVar2 = Cos_InstCountComponents(pCVar1->dwInstance);
  uVar4 = 0;
  if (uVar2 != 0) {
    do {
      pvVar3 = (void *)Cos_InstGetInstanceData(pCVar1->dwInstance,uVar4,(int *)&local_4);
      if ((((local_4 == 0x4c444d4d) || (local_4 == 0x4c444f4d)) || (local_4 == 0x74727073)) &&
         (*(int *)((int)pvVar3 + 0x50) == 1)) {
        *(void **)((int)pvVar3 + 400) = pCVar1->pComponents;
        pCVar1->pComponents = pvVar3;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar2);
  }
  return pCVar1;
}
#undef local_4


/* ---- 0x00494f90  Costume_AllocRecord ---- */
CostumeNode * __cdecl Costume_AllocRecord(void)

{
  CostumeNode *node;
  
  node = (CostumeNode *)Memory_AllocFixed((int *)g_pCosNodePool);
  Costume_InitRecord(node);
  return node;
}

/* ---- 0x00494fb0  Costume_InitRecord ---- */
/* 0xb4-byte costume record: [0] CHORE.DLL instance, [1] costume resource, [2] component list, [3-5]
   head joints, [6-8] head limits, [9] look rate, [10-13] walk/left/right/rest chores, [14-29] talk
   chores, [30] mumble chore, [44] next */

void __cdecl Costume_InitRecord(CostumeNode *node)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  
  node->dwInstance = 0;
  node->aHeadJoints[0] = -1;
  node->aHeadJoints[1] = -1;
  node->aHeadJoints[2] = -1;
  node->flMaxPitch = 30.0;
  node->flMaxYaw = 90.0;
  node->flViewCos = -0.35;
  node->flLookRate = 360.0;
  node->nWalkChore = -1;
  node->nTurnLeftChore = -1;
  node->nTurnRightChore = -1;
  node->nRestChore = -1;
  node->nMumbleChore = -1;
  piVar2 = node->aTalkChores;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = -1;
    piVar2 = piVar2 + 1;
  }
  puVar3 = node->aCostumeRef;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  node->pComponents = (void *)0x0;
  node->pNext = (CostumeNode *)0x0;
  return;
}

/* ---- 0x00495020  Costume_GetMainModel ---- */
/* rdThing of the first MMDL component */

void * __cdecl Costume_GetMainModel(void *cosInst)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pvVar1 = cosInst;
  uVar2 = Cos_InstCountComponents((int)cosInst);
  uVar4 = 0;
  if (uVar2 == 0) {
    return (void *)0x0;
  }
  do {
    iVar3 = Cos_InstGetInstanceData((int)pvVar1,uVar4,(int *)&cosInst);
    if (cosInst == (void *)0x4c444d4d) {
      return *(void **)(iVar3 + 0x40);
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
  return (void *)0x0;
}
#undef local_4


/* ---- 0x00495510  Costume_ApplyScale ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Scales every model radius by actor+0x30 and stores the reciprocal so the second call undoes it */

void __cdecl Costume_ApplyScale(void *actor,void *componentList)

{
  float *pfVar1;
  float *pfVar2;
  int *piVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  
  for (; componentList != (void *)0x0; componentList = *(void **)((int)componentList + 400)) {
    if (*(int *)((int)actor + 0x30) != 0x3f800000) {
      piVar3 = *(int **)((int)componentList + 0x40);
      iVar4 = piVar3[1];
      *(float *)(iVar4 + 0x5c) = *(float *)(iVar4 + 0x5c) * *(float *)((int)actor + 0x30);
      if (*piVar3 == 1) {
        iVar7 = *(int *)(iVar4 + 0x50);
        uVar8 = 0;
        if (*(int *)(iVar4 + 0x24 + iVar7 * 8) != 0) {
          iVar9 = 0;
          do {
            iVar7 = *(int *)(iVar4 + 0x28 + iVar7 * 8);
            uVar8 = uVar8 + 1;
            pfVar1 = (float *)(iVar7 + 0x60 + iVar9);
            pfVar2 = (float *)(iVar7 + 0x60 + iVar9);
            iVar9 = iVar9 + 0x7c;
            *pfVar2 = *(float *)((int)actor + 0x30) * *pfVar1;
            iVar7 = *(int *)(iVar4 + 0x50);
          } while (uVar8 < *(uint *)(iVar4 + 0x24 + iVar7 * 8));
        }
      }
      fVar5 = 1.0 / *(float *)((int)actor + 0x30);
      fVar6 = 1.0 - fVar5;
      *(float *)((int)actor + 0x30) = fVar5;
      fVar5 = fVar6;
      if (fVar6 < 0.0) {
        fVar5 = -fVar6;
      }
      if (fVar5 <= 1e-05) {
        fVar6 = 0.0;
      }
      if (fVar6 == 0.0) {
        *(undefined4 *)((int)actor + 0x30) = 0x3f800000;
      }
    }
  }
  return;
}
#endif


/* ---- 0x004955e0  Costume_ApplyComponentState ---- */
/* Walks the CHORE.DLL components of a costume instance: 'MAT ' swaps the material index of the
   mesh, 'cmap' installs the colormap override */

void __cdecl Costume_ApplyComponentState(void *cosInst)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pvVar2 = cosInst;
  iVar3 = Cos_InstCountComponents((int)cosInst);
  iVar6 = 0;
  if (0 < iVar3) {
    do {
      piVar4 = (int *)Cos_InstGetInstanceData((int)pvVar2,iVar6,(int *)&cosInst);
      if (cosInst == (void *)0x2054414d) {
        iVar1 = *(int *)(*(int *)(*(int *)(*(int *)(*piVar4 + 0x40) + 4) + 0x48) + piVar4[1] * 4);
        uVar5 = *(uint *)(iVar1 + 100) ^ piVar4[2];
        *(uint *)(iVar1 + 100) = uVar5;
        uVar5 = piVar4[2] ^ uVar5;
        piVar4[2] = uVar5;
        *(uint *)(iVar1 + 100) = *(uint *)(iVar1 + 100) ^ uVar5;
      }
      else if ((cosInst != (void *)0x4853454d) && (cosInst == (void *)0x70616d63)) {
        if (piVar4[1] == 0) {
          (*g_pStd_HS->pAssertFail)
                    (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
        }
        *(int *)(*piVar4 + 0x4c) = piVar4[2];
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < iVar3);
  }
  return;
}
#undef local_4


/* ---- 0x004956a0  sputCostume_BuildThingStateMatrices ---- */
/* Recursively positions a model hung on a parent model's node Original name
   sputCostume_BuildThingStateMatrices (the remaster's GrimFandango (Linux): aligned call in
   sputCostume_InternalDraw3D); was Costume_UpdateAttachedFrame. */

void __cdecl sputCostume_BuildThingStateMatrices(void *component,float *frame)

{
  void *model;
  
  model = *(void **)((int)component + 0x40);
  if (*(void **)((int)component + 0x44) != (void *)0x0) {
    sputCostume_BuildThingStateMatrices(*(void **)((int)component + 0x44),frame);
    rdPuppet_UpdateFrame
              (model,(float *)(*(int *)((int)component + 0x48) * 0x30 +
                              *(int *)(*(int *)(*(int *)((int)component + 0x44) + 0x40) + 0x20)));
    return;
  }
  rdPuppet_UpdateFrame(model,frame);
  return;
}

/* ---- 0x004956f0  sputCostume_Draw2D ---- */
/* Original name sputCostume_Draw2D (the remaster's GrimFandango (Linux): aligned call in
   sputRender_Update); was Costume_TouchComponents. */

void sputCostume_Draw2D(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  sputRoom_GetCurrentRoom();
  iVar1 = Cos_InstCountComponents(param_1);
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      Cos_InstGetInstanceData(param_1,iVar2,&local_4);
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return;
}
#undef local_4


/* ---- 0x00495730  sputCostume_Update ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name sputCostume_Update (the remaster's GrimFandango (Linux): the only unmatched caller
   of rdPuppet_Advance; 1 matched neighbours agree, 0 disagree); was Costume_UpdateAll. */

void __cdecl sputCostume_Update(CostumeNode *costumeList,float dt)

{
  void *pvVar1;
  void *puppet;
  undefined4 unaff_ESI;
  CostumeNode *pCVar2;
  undefined4 unaff_EDI;
  ulonglong uVar3;
  
  uVar3 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  if (costumeList != (CostumeNode *)0x0) {
    pvVar1 = costumeList->pMainModel;
    pCVar2 = costumeList;
    do {
      if (pCVar2->pMainModel != pvVar1) break;
      Cos_InstUpdateChores(pCVar2->dwInstance,(int)uVar3);
      pCVar2 = pCVar2->pNext;
    } while (pCVar2 != (CostumeNode *)0x0);
    for (pvVar1 = costumeList->pComponents; pvVar1 != (void *)0x0;
        pvVar1 = *(void **)((int)pvVar1 + 400)) {
      puppet = *(void **)(*(int *)((int)pvVar1 + 0x40) + 0x14);
      if (puppet != (void *)0x0) {
        rdPuppet_UpdateTracks(puppet,(float)(uVar3 & 0xffffffff) * 0.001);
      }
    }
  }
  return;
}
#endif


/* ---- 0x00495e90  sputCostume_SaveHook ---- */
/* Callback given to Cos_RegisterSaveHook (costume editor): asks for a .lua/.def file name and
   writes the costume's chore list. Original name sputCostume_SaveHook (the remaster's GrimFandango
   (Linux): the only unpaired user of psputCosHS, same body and strings ("Name chore list file...",
   "-- Chore numbering for %s.")); was Costume_SaveChoreListFile. */

undefined4 sputCostume_SaveHook(char *param_1,uint *param_2,undefined4 param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void **ppvVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  uint uVar10;
  #define acStack_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  iVar3 = strrchr(param_1,0x5c);
  pcVar4 = param_1;
  if (iVar3 != 0) {
    pcVar4 = (char *)(iVar3 + 1);
  }
  iVar3 = Cos_GetCostumeName((int)param_2);
  iVar3 = _stricmp(pcVar4,iVar3);
  if (iVar3 == 0) {
    uVar6 = 0xffffffff;
    pcVar4 = param_1;
    do {
      pcVar9 = pcVar4;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar9 = pcVar4 + 1;
      cVar2 = *pcVar4;
      pcVar4 = pcVar9;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pcVar4 = pcVar9 + -uVar6;
    pcVar9 = g_szGrimlib_aFilename;
    for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar9 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      pcVar9 = pcVar9 + 1;
    }
    pcVar4 = stdFnames_FindExt(g_szGrimlib_aFilename);
    sprintf(pcVar4,&DAT_004ea45c);
  }
  else {
    iVar3 = grimPlat_SaveFileRequest
                      (s_Name_chore_list_file____004ea460,s_Script_files____lua____def__004ea478);
    if (iVar3 == 0) {
      return 0;
    }
  }
  iVar3 = (*g_pSputCosHS->pFopen)(g_szGrimlib_aFilename,&DAT_004dd478);
  if (iVar3 != 0) {
    ppvVar1 = &g_pSputCosHS->pFprintf;
    pcVar4 = stdFnames_FindMedName(param_1);
    (*(code *)*ppvVar1)(iVar3,s____Chore_numbering_for__s__004ea3d4,pcVar4);
    (*g_pSputCosHS->pFprintf)(iVar3,s_____s_004ea3cc,param_3);
    stdFnames_CopyShortName(acStack_20,0x20,param_1);
    iVar5 = Cos_CreateCosInstance(param_2,0);
    uVar6 = Cos_InstCountChores(iVar5);
    uVar8 = 0;
    if (uVar6 != 0) {
      do {
        ppvVar1 = &g_pSputCosHS->pFprintf;
        uVar10 = uVar8;
        iVar7 = Cos_InstChoreName(iVar5,uVar8);
        (*(code *)*ppvVar1)(iVar3,s__s__s____d_004ea3bc,acStack_20,iVar7,uVar10);
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar6);
    }
    (*g_pSputCosHS->pFclose)(iVar3);
    Cos_FreeCosInstance(iVar5);
    return 1;
  }
  grimPlat_QueryDialog(s_File_Error__004ea3f0,s_Unable_to_open_chore_list_file__C_004ea3fc,0);
  return 0;
}
#undef acStack_20


/* ---- 0x00496020  Costume_InstanceHook ---- */
/* Callback given to Cos_RegisterInstanceHook: clears the instance's user data (the actor index)
   when an instance is created or destroyed. */

undefined4 Costume_InstanceHook(int param_1,int param_2)

{
  if (param_2 != 0) {
    Cos_InstSetUserData(param_1,0);
    return 1;
  }
  Cos_InstSetUserData(param_1,0);
  return 1;
}
