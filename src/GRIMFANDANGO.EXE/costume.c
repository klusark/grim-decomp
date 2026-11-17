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

void __cdecl FadeInChore(void *cosInst,uint chore,int ms)

{
  Cos_InstPlayChore((int)cosInst,chore,1,0);
  Cos_InstUpdateChore((int)cosInst,chore,0x46);
  sputCostume_FadeKeysIn(cosInst,chore,ms);
  return;
}

/* ---- 0x00493450  FadeOutChore ---- */
/* Cos_StopChoreFaded(inst, chore, ms): fade the chore's keyframes out over ms, then stop the chore
   (chore -1: all). Original name FadeOutChore (the remaster's GrimFandango (Linux): the only
   unmatched callee of sputActor_SetWalkChore; the only unmatched caller of Chore_FadeOut; 2 matched
   neighbours agree, 0 disagree); was Cos_StopChoreFaded. */

undefined * __cdecl FadeOutChore(void *cosInst,int chore,int ms)

{
  undefined *puVar1;
  undefined *puVar2;
  int chore_00;
  
  if (chore == -1) {
    puVar1 = (undefined *)Cos_InstCountChores((int)cosInst);
    chore_00 = 0;
    if (0 < (int)puVar1) {
      do {
        puVar2 = FadeOutChore(cosInst,chore_00,ms);
        chore_00 = chore_00 + 1;
      } while (chore_00 < (int)puVar1);
      return puVar2;
    }
  }
  else {
    sputCostume_FadeKeysOut(cosInst,chore,ms);
    puVar1 = (undefined *)Cos_InstStopChore((int)cosInst,chore);
  }
  return puVar1;
}

/* ---- 0x00494d10  sputCostume_PrintCostumeInfo ---- */
/* Original name sputCostume_PrintCostumeInfo (the remaster's GrimFandango (Linux): the only
   unmatched callee of Lua_PrintActorCostumes; 1 matched neighbours agree, 0 disagree); was
   Costume_PrintList. */

void __cdecl sputCostume_PrintCostumeInfo(CostumeNode *costume)

{
  CostumeNode **ppCVar1;
  ModelComponent *pMVar2;
  rdModel3 *prVar3;
  int iVar4;
  uint uVar5;
  CostumeNode *pCVar6;
  uint local_4;
  
  pCVar6 = costume;
  if (costume != (CostumeNode *)0x0) {
    do {
      iVar4 = Cos_InstCountChores(pCVar6->dwInstance);
      uVar5 = 0;
      if (0 < iVar4) {
        do {
          Cos_InstChoreStatus(pCVar6->dwInstance,uVar5);
          uVar5 = uVar5 + 1;
        } while ((int)uVar5 < iVar4);
      }
      ppCVar1 = &pCVar6->pNext;
      pCVar6 = *ppCVar1;
    } while (*ppCVar1 != (CostumeNode *)0x0);
    for (pMVar2 = costume->pComponents; pMVar2 != (ModelComponent *)0x0; pMVar2 = pMVar2->pNext) {
      if (pMVar2->nRoot != 0) {
        uVar5 = 0;
        prVar3 = pMVar2->pThing->pModel;
        if (prVar3->nNumHierarchyNodes != 0) {
          iVar4 = 0;
          do {
            String_ContainsSubstring
                      ((uint *)(prVar3->pHierarchyNodes->aName + iVar4),s_skirt_004ea1a8);
            uVar5 = uVar5 + 1;
            iVar4 = iVar4 + 0xb8;
          } while (uVar5 < (uint)prVar3->nNumHierarchyNodes);
        }
      }
    }
  }
  return;
}

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
    if ((list->costumeRef).nValid != 0) {
      Res_RemoveReference(&list->costumeRef);
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
  rdThing *prVar3;
  ModelComponent *pMVar4;
  uint uVar5;
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
    Res_SetReference(&pCVar1->costumeRef,costumeRes,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,
                     0x47a);
  }
  else {
    pCVar1->dwInstance = flags;
  }
  prVar3 = Costume_GetMainModel((void *)pCVar1->dwInstance);
  pCVar1->pMainModel = prVar3;
  if (((prVar3 != (rdThing *)0x0) && (list != (CostumeNode *)0x0)) && (list->pMainModel == prVar3))
  {
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
  uVar5 = 0;
  if (uVar2 != 0) {
    do {
      pMVar4 = (ModelComponent *)Cos_InstGetInstanceData(pCVar1->dwInstance,uVar5,(int *)&local_4);
      if ((((local_4 == 0x4c444d4d) || (local_4 == 0x4c444f4d)) || (local_4 == 0x74727073)) &&
         (pMVar4->nRefCount == 1)) {
        pMVar4->pNext = pCVar1->pComponents;
        pCVar1->pComponents = pMVar4;
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < uVar2);
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
  ResRef *pRVar3;
  
  node->dwInstance = 0;
  node->aHeadJoints[0] = -1;
  node->aHeadJoints[1] = -1;
  node->aHeadJoints[2] = -1;
  node->flMaxPitch = 30.0f;
  node->flMaxYaw = 90.0f;
  node->flViewCos = -0.35f;
  node->flLookRate = 360.0f;
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
  pRVar3 = &node->costumeRef;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    pRVar3->nValid = 0;
    pRVar3 = (ResRef *)&pRVar3->pData;
  }
  node->pComponents = (ModelComponent *)0x0;
  node->pNext = (CostumeNode *)0x0;
  return;
}

/* ---- 0x00495020  Costume_GetMainModel ---- */
/* rdThing of the first MMDL component */

rdThing * __cdecl Costume_GetMainModel(void *cosInst)

{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint local_4;
  
  pvVar1 = cosInst;
  uVar2 = Cos_InstCountComponents((int)cosInst);
  uVar4 = 0;
  if (uVar2 == 0) {
    return (rdThing *)0x0;
  }
  do {
    iVar3 = Cos_InstGetInstanceData((int)pvVar1,uVar4,(int *)&cosInst);
    if (cosInst == (void *)0x4c444d4d) {
      return *(rdThing **)(iVar3 + 0x40);
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
  return (rdThing *)0x0;
}

/* ---- 0x00495510  Costume_ApplyScale ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Scales every model radius by actor+0x30 and stores the reciprocal so the second call undoes it */

void __cdecl Costume_ApplyScale(Actor *actor,ModelComponent *componentList)

{
  rdThing *prVar1;
  rdModel3 *prVar2;
  rdMesh *prVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  
  for (; componentList != (ModelComponent *)0x0; componentList = componentList->pNext) {
    if (actor->flScale != 1.0f) {
      prVar1 = componentList->pThing;
      prVar2 = prVar1->pModel;
      prVar2->flRadius = prVar2->flRadius * actor->flScale;
      if (prVar1->nType == 1) {
        iVar7 = prVar2->nCurGeoset;
        uVar8 = 0;
        if (prVar2->aGeosets[iVar7].dwMeshes != 0) {
          iVar9 = 0;
          do {
            prVar3 = prVar2->aGeosets[iVar7].pMeshes;
            uVar8 = uVar8 + 1;
            iVar7 = iVar9 + 0x60;
            iVar6 = iVar9 + 0x60;
            iVar9 = iVar9 + 0x7c;
            *(float *)(prVar3->aName + iVar6) = actor->flScale * *(float *)(prVar3->aName + iVar7);
            iVar7 = prVar2->nCurGeoset;
          } while (uVar8 < prVar2->aGeosets[iVar7].dwMeshes);
        }
      }
      fVar4 = 1.0f / actor->flScale;
      fVar5 = 1.0f - fVar4;
      actor->flScale = fVar4;
      fVar4 = fVar5;
      if (fVar5 < 0.0f) {
        fVar4 = -fVar5;
      }
      if (fVar4 <= 1e-05f) {
        fVar5 = 0.0f;
      }
      if (fVar5 == 0.0f) {
        actor->flScale = 1.0f;
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
  int iVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  uint local_4;
  
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

/* ---- 0x004956a0  sputCostume_BuildThingStateMatrices ---- */
/* Recursively positions a model hung on a parent model's node Original name
   sputCostume_BuildThingStateMatrices (the remaster's GrimFandango (Linux): aligned call in
   sputCostume_InternalDraw3D); was Costume_UpdateAttachedFrame. */

void __cdecl sputCostume_BuildThingStateMatrices(ModelComponent *component,float *frame)

{
  rdThing *thing;
  
  thing = component->pThing;
  if (component->pParent != (ModelComponent *)0x0) {
    sputCostume_BuildThingStateMatrices(component->pParent,frame);
    rdPuppet_UpdateFrame
              (thing,component->pParent->pThing->pHierarchyMatrices + component->nParentNode * 0xc);
    return;
  }
  rdPuppet_UpdateFrame(thing,frame);
  return;
}

/* ---- 0x004956f0  sputCostume_Draw2D ---- */
/* Original name sputCostume_Draw2D (the remaster's GrimFandango (Linux): aligned call in
   sputRender_Update); was Costume_TouchComponents. */

void __cdecl sputCostume_Draw2D(int cosInst)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  sputRoom_GetCurrentRoom();
  iVar1 = Cos_InstCountComponents(cosInst);
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      Cos_InstGetInstanceData(cosInst,iVar2,&local_4);
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return;
}
#undef local_4


/* ---- 0x00495730  sputCostume_Update ---- */
/* Original name sputCostume_Update (the remaster's GrimFandango (Linux): the only unmatched caller
   of rdPuppet_Advance; 1 matched neighbours agree, 0 disagree); was Costume_UpdateAll. */

void __cdecl sputCostume_Update(CostumeNode *costumeList,float dt)

{
  rdThing *prVar1;
  ModelComponent *pMVar2;
  void *puppet;
  float10 fVar3;
  CostumeNode *pCVar4;
  ulonglong uVar5;
  
  if (dt * 1000.0f <= 0.0f) {
    fVar3 = (float10)-0.5;
  }
  else {
    fVar3 = (float10)0.5;
  }
  uVar5 = FTOL(fVar3 - (float10)dt * (float10)-1000.0f);
  if (costumeList != (CostumeNode *)0x0) {
    prVar1 = costumeList->pMainModel;
    pCVar4 = costumeList;
    do {
      if (pCVar4->pMainModel != prVar1) break;
      Cos_InstUpdateChores(pCVar4->dwInstance,(int)uVar5);
      pCVar4 = pCVar4->pNext;
    } while (pCVar4 != (CostumeNode *)0x0);
    for (pMVar2 = costumeList->pComponents; pMVar2 != (ModelComponent *)0x0; pMVar2 = pMVar2->pNext)
    {
      puppet = pMVar2->pThing->pPuppet;
      if (puppet != (void *)0x0) {
        rdPuppet_UpdateTracks(puppet,(float)(uVar5 & 0xffffffff) * 0.001f);
      }
    }
  }
  return;
}

/* ---- 0x00495e90  sputCostume_SaveHook ---- */
/* Callback given to Cos_RegisterSaveHook (costume editor): asks for a .lua/.def file name and
   writes the costume's chore list. Original name sputCostume_SaveHook (the remaster's GrimFandango
   (Linux): the only unpaired user of psputCosHS, same body and strings ("Name chore list file...",
   "-- Chore numbering for %s.")); was Costume_SaveChoreListFile. */

uint __cdecl sputCostume_SaveHook(char *path,uint *costume,uint f)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void **ppvVar1;
  char cVar2;
  char *pcVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  uint uVar10;
  char *pcVar11;
  uint uVar12;
  #define acStack_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  pcVar3 = strrchr(path,'\\');
  pbVar9 = (byte *)path;
  if (pcVar3 != (char *)0x0) {
    pbVar9 = (byte *)(pcVar3 + 1);
  }
  pbVar4 = (byte *)Cos_GetCostumeName((int)costume);
  iVar5 = _stricmp(pbVar9,pbVar4);
  if (iVar5 == 0) {
    uVar7 = 0xffffffff;
    pcVar3 = path;
    do {
      pcVar11 = pcVar3;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar11 = pcVar3 + 1;
      cVar2 = *pcVar3;
      pcVar3 = pcVar11;
    } while (cVar2 != '\0');
    uVar7 = ~uVar7;
    pcVar3 = pcVar11 + -uVar7;
    pcVar11 = g_szGrimlib_aFilename;
    for (uVar10 = uVar7 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar11 = pcVar11 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar11 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar11 = pcVar11 + 1;
    }
    pcVar3 = stdFnames_FindExt(g_szGrimlib_aFilename);
    sprintf(pcVar3,s_lua_004ea45c);
  }
  else {
    iVar5 = grimPlat_SaveFileRequest
                      (s_Name_chore_list_file____004ea460,s_Script_files____lua____def__004ea478);
    if (iVar5 == 0) {
      return 0;
    }
  }
  iVar5 = (*g_pSputCosHS->pFopen)(g_szGrimlib_aFilename,s_w_004dd478);
  if (iVar5 != 0) {
    ppvVar1 = &g_pSputCosHS->pFprintf;
    pcVar3 = stdFnames_FindMedName(path);
    (*(code *)*ppvVar1)(iVar5,s____Chore_numbering_for__s__004ea3d4,pcVar3);
    (*g_pSputCosHS->pFprintf)(iVar5,s_____s_004ea3cc,f);
    stdFnames_CopyShortName(acStack_20,0x20,path);
    iVar6 = Cos_CreateCosInstance(costume,0);
    uVar7 = Cos_InstCountChores(iVar6);
    uVar10 = 0;
    if (uVar7 != 0) {
      do {
        ppvVar1 = &g_pSputCosHS->pFprintf;
        uVar12 = uVar10;
        iVar8 = Cos_InstChoreName(iVar6,uVar10);
        (*(code *)*ppvVar1)(iVar5,s__s__s____d_004ea3bc,acStack_20,iVar8,uVar12);
        uVar10 = uVar10 + 1;
      } while (uVar10 < uVar7);
    }
    (*g_pSputCosHS->pFclose)(iVar5);
    Cos_FreeCosInstance(iVar6);
    return 1;
  }
  grimPlat_QueryDialog(s_File_Error__004ea3f0,s_Unable_to_open_chore_list_file__C_004ea3fc,0);
  return 0;
}
#undef acStack_20


/* ---- 0x00496020  Costume_InstanceHook ---- */
/* Callback given to Cos_RegisterInstanceHook: clears the instance's user data (the actor index)
   when an instance is created or destroyed. */

uint __cdecl Costume_InstanceHook(int cosInst,int create)

{
  if (create != 0) {
    Cos_InstSetUserData(cosInst,0);
    return 1;
  }
  Cos_InstSetUserData(cosInst,0);
  return 1;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char grim_def_s_File_Error__004ea3f0[12] __asm__("_s_File_Error__004ea3f0");
extern char grim_def_s_Name_chore_list_file____004ea460[24] __asm__("_s_Name_chore_list_file____004ea460");
extern char grim_def_s_Script_files____lua____def__004ea478[64] __asm__("_s_Script_files____lua____def__004ea478");
extern char grim_def_s_Unable_to_open_chore_list_file__C_004ea3fc[96] __asm__("_s_Unable_to_open_chore_list_file__C_004ea3fc");
extern char grim_def_s____Chore_numbering_for__s__004ea3d4[28] __asm__("_s____Chore_numbering_for__s__004ea3d4");
extern char grim_def_s_____s_004ea3cc[8] __asm__("_s_____s_004ea3cc");
extern char grim_def_s__s__s____d_004ea3bc[16] __asm__("_s__s__s____d_004ea3bc");
extern char grim_def_s_lua_004ea45c[4] __asm__("_s_lua_004ea45c");
extern char grim_def_s_skirt_004ea1a8[8] __asm__("_s_skirt_004ea1a8");
/* 0x004ea1a8, 8 bytes */ /* loose */ char grim_def_s_skirt_004ea1a8[8] __asm__("_s_skirt_004ea1a8") = "skirt";
/* 0x004ea3bc, 16 bytes */ /* loose */ char grim_def_s__s__s____d_004ea3bc[16] __asm__("_s__s__s____d_004ea3bc") = "%s_%s\t\t=\t%d\n";
/* 0x004ea3cc, 8 bytes */ /* loose */ char grim_def_s_____s_004ea3cc[8] __asm__("_s_____s_004ea3cc") = "-- %s\n\n";
/* 0x004ea3d4, 28 bytes */ /* loose */ char grim_def_s____Chore_numbering_for__s__004ea3d4[28] __asm__("_s____Chore_numbering_for__s__004ea3d4") = "-- Chore numbering for %s.\n";
/* 0x004ea3f0, 12 bytes */ /* loose */ char grim_def_s_File_Error__004ea3f0[12] __asm__("_s_File_Error__004ea3f0") = "File Error!";
/* 0x004ea3fc, 96 bytes */ /* loose */ char grim_def_s_Unable_to_open_chore_list_file__C_004ea3fc[96] __asm__("_s_Unable_to_open_chore_list_file__C_004ea3fc") = "Unable to open chore list file. Check to make sure that the destination file is not read-only.";
/* 0x004ea45c, 4 bytes */ /* loose */ char grim_def_s_lua_004ea45c[4] __asm__("_s_lua_004ea45c") = "lua";
/* 0x004ea460, 24 bytes */ /* loose */ char grim_def_s_Name_chore_list_file____004ea460[24] __asm__("_s_Name_chore_list_file____004ea460") = "Name chore list file...";
static unsigned char grim_anchor_004ea478[0] __attribute__((section(".data$grim_004ea478"), aligned(16), used));
static unsigned char grim_pad_004ea478[8] __attribute__((section(".data$grim_004ea478_"), aligned(4), used));
/* 0x004ea478, 64 bytes */ GRIM_DATA("004ea478z") char grim_def_s_Script_files____lua____def__004ea478[64] __asm__("_s_Script_files____lua____def__004ea478") = "Script files (*.lua, *.def)\000*.lua;*.def\000All Files (*.*)\000*.*";
