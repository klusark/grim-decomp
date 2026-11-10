/* CHORE.DLL :: costume.c
 * functions 0x10001000 .. 0x10005590 (71 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10001000  Cos_InstRescue ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Export: points the costume instance `hInst` at the costume `hCostume` again (CosInstance +0),
   without rebuilding it; the EXE's actor update calls it with the current handle of the actor's
   costume resource. Returns g_aCostumeInstances when both handles are valid (the converted index
   otherwise). */

int __cdecl Cos_InstRescue(int hInst,int hCostume)

{
  CosInstance *pCVar1;
  CosInstance *pCVar2;
  CosInstance *pCVar3;
  
                    /* 0x1000  43  Cos_InstRescue */
  pCVar2 = (CosInstance *)Cos_HandleToIndex(hCostume);
  pCVar3 = pCVar2;
  if (-1 < (int)pCVar2) {
    pCVar3 = (CosInstance *)Cos_InstHandleToIndex(hCostume);
    pCVar1 = g_aCostumeInstances;
    if ((-1 < (int)pCVar3) && ((int)pCVar3 < g_nMaxInstances)) {
      g_aCostumeInstances[(int)pCVar3].nCostume = (int)pCVar2;
      pCVar3 = pCVar1;
    }
  }
  return (int)pCVar3;
}
#endif


/* ---- 0x10001040  Cos_Free ---- */
/* Export: frees the costume `hCostume`: every costume instance of it (Cos_FreeCosInstance), then
   its components, chores and keys (Cos_FreeCostume); the slot is marked free and g_nCostumes
   lowered. Returns the new g_nCostumes. */

int __cdecl Cos_Free(int hCostume)

{
  int iVar1;
  int hInst;
  CosInstance *pCVar2;
  int index;
  int iVar3;
  
                    /* 0x1040  26  Cos_Free */
  iVar1 = Cos_HandleToIndex(hCostume);
  index = 0;
  if (0 < g_nMaxInstances) {
    iVar3 = 0;
    pCVar2 = g_aCostumeInstances;
    do {
      if ((*(int *)((int)&pCVar2->nFree + iVar3) == 0) &&
         (*(int *)((int)&pCVar2->nCostume + iVar3) == iVar1)) {
        hInst = Cos_InstIndexToHandle(index);
        Cos_FreeCosInstance(hInst);
        pCVar2 = g_aCostumeInstances;
      }
      index = index + 1;
      iVar3 = iVar3 + 0x14;
    } while (index < g_nMaxInstances);
  }
  Cos_FreeCostume(hCostume);
  g_aCostumes[iVar1].nFree = 1;
  g_nCostumes = g_nCostumes + -1;
  return g_nCostumes;
}

/* ---- 0x100010d0  Cos_NewEntry ---- */
/* Resets a costume record (Costume, 0x3c bytes) to an empty costume: name '<unnamed>', id (+0x24) =
   the next serial number (g_nNextCostumeID), no components (+0x28/+0x2c) and no chores
   (+0x30/+0x34). Original name (libchore.so of the remaster: Cos_NewEntry, with the static
   Cos_NewEntry.nextID). */

void __cdecl Cos_NewEntry(Costume *pCostume)

{
  msvc_strncpy(pCostume,IMG_ADDR(0x10010030),0x1f);
  pCostume->aName[0x1f] = '\0';
  pCostume->nId = g_nNextCostumeID;
  g_nNextCostumeID = g_nNextCostumeID + 1;
  pCostume->dwNumComponents = 0;
  pCostume->pComponents = (CosComponent *)0x0;
  pCostume->dwNumChores = 0;
  pCostume->pChores = (Chore *)0x0;
  return;
}

/* ---- 0x100016a0  Cos_New ---- */
/* Export: a new empty costume (Cos_AllocCostumeSlot + Cos_NewEntry); returns its handle, 0 when no
   slot. */

int __cdecl Cos_New(void)

{
  int iVar1;
  
                    /* 0x16a0  53  Cos_New */
  iVar1 = Cos_AllocCostumeSlot();
  if (iVar1 < 0) {
    return 0;
  }
  Cos_NewEntry(g_aCostumes + iVar1);
  iVar1 = Cos_IndexToHandle(iVar1);
  return iVar1;
}

/* ---- 0x100016e0  Cos_Load ---- */
/* Export: handle of the costume loaded from the text costume file `fileName`: an already loaded
   costume of that name (_stricmp) is shared, otherwise a new slot is filled by Cos_LoadEntry. A
   failed load frees the slot again (Cos_FreeCostume) and returns 0. */

int __cdecl Cos_Load(char *fileName)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
                    /* 0x16e0  51  Cos_Load */
  iVar4 = 0;
  if (0 < g_nMaxCostumes) {
    iVar3 = 0;
    do {
      if (*(int *)(g_aCostumes->aName + iVar3 + 0x38) == 0) {
        iVar1 = msvc_stricmp((byte *)fileName,(byte *)(g_aCostumes->aName + iVar3));
        if (iVar1 == 0) {
          iVar4 = Cos_IndexToHandle(iVar4);
          return iVar4;
        }
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x3c;
    } while (iVar4 < g_nMaxCostumes);
  }
  iVar4 = Cos_AllocCostumeSlot();
  if (iVar4 != -1) {
    iVar3 = Cos_IndexToHandle(iVar4);
    uVar2 = Cos_LoadEntry(fileName,iVar3);
    if (uVar2 != 0) {
      return iVar3;
    }
  }
  iVar4 = Cos_IndexToHandle(iVar4);
  Cos_FreeCostume(iVar4);
  return 0;
}

/* ---- 0x10001770  Cos_LoadEntry ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Export: loads the text costume file `name` into the costume `handle` (sections tags, components,
   chores, keys). Hand-written in build/overrides_asm_o2_chore.c, which has the details. */

uint __cdecl Cos_LoadEntry(char *name,int handle)

{
  unsigned char _stkneg[160] __attribute__((aligned(16)));  /* the original frame below the return address */
  char cVar1;
  Costume *pCostume;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  char *in_stack_0000000c;
  uint uStack00000018;
  uint in_stack_ffffff9c;
  
                    /* 0x1770  52  Cos_LoadEntry */
  pCostume = CosUtil_PtrFromHandle(handle);
  Cos_NewEntry(pCostume);
  pcVar2 = (char *)((code *)msvc_strrchr)();
  if (pcVar2 == (char *)0x0) {
    uVar5 = 0xffffffff;
    pcVar2 = in_stack_0000000c;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
  }
  else {
    uVar5 = 0xffffffff;
    do {
      pcVar2 = pcVar2 + 1;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
    } while (*pcVar2 != '\0');
  }
  if (~uVar5 - 1 < 0x21) {
    ((code *)msvc_strncpy)();
    pCostume->aName[0x1f] = '\0';
    uVar5 = (*(code *)g_pSvcChore->pFopen)();
    if (uVar5 == 0) {
      pCostume->nFree = 1;
      return 0;
    }
    g_nLineNum = 0;
    iVar3 = Cos_ReadLine(uVar5,g_szParseLine,0x400);
    if (iVar3 != 0) {
      msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x10010270),(_stkneg + 28),(_stkneg + 24));
      iVar3 = Cos_ReadLine(uVar5,g_szParseLine,0x400);
      if (((((((iVar3 != 0) && (iVar3 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x10010260)), iVar3 == 0))
             && (uVar4 = Cos_ReadTagsSection(uVar5,(uint)pCostume,(uint)in_stack_0000000c),
                uVar4 != 0)) &&
            ((iVar3 = Cos_ReadLine(uVar5,g_szParseLine,0x400), iVar3 != 0 &&
             (iVar3 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x1001024c)), iVar3 == 0)))) &&
           ((uVar4 = Cos_ReadComponentsSection
                               (uVar5,handle,(uint)in_stack_0000000c,in_stack_ffffff9c), uVar4 != 0
            && ((iVar3 = Cos_ReadLine(uVar5,g_szParseLine,0x400), iVar3 != 0 &&
                (iVar3 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x1001023c)), iVar3 == 0)))))) &&
          (uVar4 = Cos_ReadChoresSection(uVar5,(int)pCostume,(uint)in_stack_0000000c), uVar4 != 0))
         && (((iVar3 = Cos_ReadLine(uVar5,g_szParseLine,0x400), iVar3 != 0 &&
              (iVar3 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x1001022c)), iVar3 == 0)) &&
             ((pCostume->dwNumChores == 0 ||
              (uVar5 = Cos_ReadKeysSection(uVar5,(int)pCostume), uVar5 != 0)))))) {
        pcVar2 = (char *)0x0;
        if (pCostume->dwNumChores != 0) {
          puVar7 = &pCostume->pChores->dwNumTracks;
          do {
            CosUtil_SetChoreLength(pCostume,(uint)pcVar2,puVar7[2]);
            uVar5 = *puVar7;
            uStack00000018 = 0;
            if (uVar5 != 0) {
              iVar3 = 0;
              do {
                uVar4 = 0;
                if (uVar5 != 0) {
                  iVar6 = 0;
                  do {
                    if ((uStack00000018 != uVar4) &&
                       (pCostume = (Costume *)handle,
                       *(int *)((int)&((ChoreTrack *)puVar7[1])->nCompNum + iVar3) ==
                       *(int *)((int)&((ChoreTrack *)puVar7[1])->nCompNum + iVar6)))
                    goto LAB_10001a10;
                    uVar4 = uVar4 + 1;
                    iVar6 = iVar6 + 0x10;
                  } while (uVar4 < uVar5);
                }
                uStack00000018 = uStack00000018 + 1;
                iVar3 = iVar3 + 0x10;
                pcVar2 = name;
              } while (uStack00000018 < uVar5);
            }
            pcVar2 = pcVar2 + 1;
            puVar7 = puVar7 + 0xb;
            name = pcVar2;
          } while (pcVar2 < (char *)pCostume->dwNumChores);
        }
        (*(code *)g_pSvcChore->pFclose)();
        return 1;
      }
    }
  }
LAB_10001a10:
  pCostume->nFree = 1;
  (*(code *)g_pSvcChore->pFclose)();
  return 0;
}
#endif


/* ---- 0x10001a30  Cos_FreeCosInstance ---- */
/* Export: frees the costume instance `hInst`: instance hook (created = 0), Cos_FreeInstanceData,
   record marked free, g_nInstances lowered. Returns the new g_nInstances. */

int __cdecl Cos_FreeCosInstance(int hInst)

{
  int instIndex;
  
                    /* 0x1a30  27  Cos_FreeCosInstance */
  instIndex = Cos_InstHandleToIndex(hInst);
  if (g_pfnInstanceHook != (void *)0x0) {
    (*(code *)g_pfnInstanceHook)(hInst,0);
  }
  Cos_FreeInstanceData(instIndex);
  g_aCostumeInstances[instIndex].nFree = 1;
  g_nInstances = g_nInstances + -1;
  return g_nInstances;
}

/* ---- 0x10001a80  Cos_CreateCosInstance ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Export: creates a costume instance (CosInstance) of the costume `hCostume` for the EXE's actor
   (`userData`): chore states (assert 'pInstance->aChoreInstances != NULL', Cos_InitChoreInstances),
   the instance data array initialised from each component's data (assert 'pInstance->aInstanceData
   != NULL'), then the NewInstance handler (ComponentTag +0x40) of every component, parents before
   children (tree depth, assert 'aTreeDepths != NULL'), whose non-zero result replaces the instance
   data. The instance hook (Cos_RegisterInstanceHook) can refuse the instance. Returns the instance
   handle, 0 on failure. */

int __cdecl Cos_CreateCosInstance(int hCostume,int userData)

{
  CosInstance *pCVar1;
  int iVar2;
  code *pcVar3;
  Costume *pCVar4;
  int iVar5;
  int iVar6;
  ChoreInstance *pCVar7;
  int *piVar8;
  uint uVar9;
  int iVar10;
  uint *puVar11;
  uint uVar12;
  int iVar13;
  int in_stack_00000010;
  uint *in_stack_00000018;
  uint uStack0000001c;
  
                    /* 0x1a80  25  Cos_CreateCosInstance */
  iVar5 = Cos_HandleToIndex(hCostume);
  pCVar4 = g_aCostumes;
  if ((iVar5 < 0) || (g_nMaxCostumes <= iVar5)) {
    return 0;
  }
  iVar6 = Cos_AllocInstanceSlot();
  pCVar1 = g_aCostumeInstances + iVar6;
  pCVar1->nCostume = iVar5;
  if (pCVar4[iVar5].dwNumChores == 0) {
    pCVar1->pChoreInstances = (ChoreInstance *)0x0;
  }
  else {
    pCVar7 = (ChoreInstance *)
             (*(code *)g_pSvcChore->pAlloc)
                       (pCVar4[iVar5].dwNumChores * 0xc,s_C__grimsrc_libs_chore_Costume_c_1001020c,
                        0x347);
    pCVar1->pChoreInstances = pCVar7;
    if (pCVar7 == (ChoreInstance *)0x0) {
      (*(code *)g_pSvcChore->pAssertFail)
                (IMG_ADDR(0x100102cc),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x348);
    }
  }
  Cos_InitChoreInstances(pCVar4[iVar5].pChores,pCVar1->pChoreInstances,pCVar4[iVar5].dwNumChores);
  if (pCVar4[iVar5].dwNumComponents == 0) {
    pCVar1->pInstanceData = (int *)0x0;
  }
  else {
    piVar8 = (int *)(*(code *)g_pSvcChore->pAlloc)
                              (pCVar4[iVar5].dwNumComponents * 4,
                               s_C__grimsrc_libs_chore_Costume_c_1001020c,0x354);
    pCVar1->pInstanceData = piVar8;
    if (piVar8 == (int *)0x0) {
      (*(code *)g_pSvcChore->pAssertFail)
                (IMG_ADDR(0x100102a4),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x355);
    }
    if (pCVar4[iVar5].dwNumComponents != 0) {
      iVar10 = 0;
      uVar12 = 0;
      do {
        uVar9 = uVar12 + 1;
        iVar2 = iVar10 + 0x24;
        iVar10 = iVar10 + 0x40;
        pCVar1->pInstanceData[uVar12] = *(int *)((pCVar4[iVar5].pComponents)->aName + iVar2);
        uVar12 = uVar9;
      } while (uVar9 < pCVar4[iVar5].dwNumComponents);
    }
  }
  pCVar1->nUserData = (int)in_stack_00000018;
  iVar6 = Cos_InstIndexToHandle(iVar6);
  uVar12 = 0;
  if (pCVar4[iVar5].dwNumComponents == 0) {
    in_stack_00000018 = (uint *)0x0;
  }
  else {
    in_stack_00000018 =
         (uint *)(*(code *)g_pSvcChore->pAlloc)
                           (pCVar4[iVar5].dwNumComponents * 4,
                            s_C__grimsrc_libs_chore_Costume_c_1001020c,0x369);
    if (in_stack_00000018 == (uint *)0x0) {
      (*(code *)g_pSvcChore->pAssertFail)
                (IMG_ADDR(0x10010288),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x36a);
    }
  }
  userData = 0;
  if (pCVar4[iVar5].dwNumComponents != 0) {
    piVar8 = &(pCVar4[iVar5].pComponents)->nParent;
    puVar11 = in_stack_00000018;
    do {
      iVar10 = *piVar8;
      *puVar11 = 0;
      while (iVar10 != -1) {
        iVar10 = pCVar4[iVar5].pComponents[iVar10].nParent;
        *puVar11 = *puVar11 + 1;
      }
      if ((uint)userData <= *puVar11) {
        userData = *puVar11;
      }
      uVar12 = uVar12 + 1;
      puVar11 = puVar11 + 1;
      piVar8 = piVar8 + 0x10;
    } while (uVar12 < pCVar4[iVar5].dwNumComponents);
  }
  uStack0000001c = 0;
  do {
    uVar12 = 0;
    if (pCVar4[iVar5].dwNumComponents != 0) {
      piVar8 = &(pCVar4[iVar5].pComponents)->nTag;
      do {
        if (in_stack_00000018[uVar12] == uStack0000001c) {
          iVar10 = *piVar8;
          iVar13 = 0;
          iVar2 = g_aComponentTags[iVar10].nKind;
          if (iVar2 == 0) {
            pcVar3 = (code *)g_aComponentTags[iVar10].pfnNewInstance;
joined_r0x10001cd0:
            if (pcVar3 != (code *)0x0) {
              iVar13 = (*pcVar3)(iVar6,uVar12,1);
            }
          }
          else {
            if ((iVar2 == 1) || (iVar2 == 2)) {
              pcVar3 = (code *)g_aComponentTags[iVar10].pfnNewInstance;
              goto joined_r0x10001cd0;
            }
            (*(code *)g_pSvcChore->pAssertFail)
                      (&DAT_10010284,s_C__grimsrc_libs_chore_Costume_c_1001020c,0x3a3);
          }
          if (iVar13 != 0) {
            *(int *)(*(int *)(in_stack_00000010 + 0xc) + uVar12 * 4) = iVar13;
          }
        }
        uVar12 = uVar12 + 1;
        piVar8 = piVar8 + 0x10;
      } while (uVar12 < pCVar4[iVar5].dwNumComponents);
    }
    uStack0000001c = uStack0000001c + 1;
    if ((uint)userData < uStack0000001c) {
      (*(code *)g_pSvcChore->pFree)(in_stack_00000018);
      if (g_pfnInstanceHook == (void *)0x0) {
        *(undefined4 *)(in_stack_00000010 + 8) = 0;
      }
      else {
        iVar5 = (*(code *)g_pfnInstanceHook)(iVar6,1);
        if (iVar5 == 0) {
          Cos_FreeCosInstance(iVar6);
          return 0;
        }
      }
      return iVar6;
    }
  } while( true );
}
#endif


/* ---- 0x10001d70  Cos_InstGetInstanceData ---- */
/* Export: instance data of component `compNum` of the instance (and its tag id through outTagId), 0
   for a bad handle or index. */

int __cdecl Cos_InstGetInstanceData(int hInst,int compNum,int *outTagId)

{
  int iVar1;
  
                    /* 0x1d70  38  Cos_InstGetInstanceData */
  iVar1 = Cos_InstHandleToIndex(hInst);
  if (((-1 < iVar1) && (iVar1 < g_nMaxInstances)) && (-1 < compNum)) {
    if (compNum < (int)g_aCostumes[g_aCostumeInstances[iVar1].nCostume].dwNumComponents) {
      if (outTagId != (int *)0x0) {
        *outTagId = g_aComponentTags
                    [g_aCostumes[g_aCostumeInstances[iVar1].nCostume].pComponents[compNum].nTag].nId
        ;
      }
      return g_aCostumeInstances[iVar1].pInstanceData[compNum];
    }
  }
  return 0;
}

/* ---- 0x10001e00  Cos_RegisterInstanceHook ---- */
/* Export: installs the costume instance hook (g_pfnInstanceHook) and returns the previous one. */

void * __cdecl Cos_RegisterInstanceHook(void *hook)

{
  void *pvVar1;
  
                    /* 0x1e00  58  Cos_RegisterInstanceHook */
  pvVar1 = g_pfnInstanceHook;
  g_pfnInstanceHook = hook;
  return pvVar1;
}

/* ---- 0x10001e10  Cos_RegisterSaveHook ---- */
/* Export: installs the costume save hook (g_pfnSaveHook, asked by CosUtil_Write) and returns the
   previous one. */

void * __cdecl Cos_RegisterSaveHook(void *hook)

{
  void *pvVar1;
  
                    /* 0x1e10  59  Cos_RegisterSaveHook */
  pvVar1 = g_pfnSaveHook;
  g_pfnSaveHook = hook;
  return pvVar1;
}

/* ---- 0x10001e20  Cos_InstGetUserData ---- */
/* Export: the EXE's user data of the instance (CosInstance +8), 0 for a bad handle. */

int __cdecl Cos_InstGetUserData(int hInst)

{
  int iVar1;
  
                    /* 0x1e20  39  Cos_InstGetUserData */
  iVar1 = Cos_InstHandleToIndex(hInst);
  if ((-1 < iVar1) && (iVar1 < g_nMaxInstances)) {
    return g_aCostumeInstances[iVar1].nUserData;
  }
  return 0;
}

/* ---- 0x10001e50  Cos_InstSetUserData ---- */
/* Export: sets the EXE's user data of the instance (CosInstance +8). */

int __cdecl Cos_InstSetUserData(int hInst,int userData)

{
  CosInstance *pCVar1;
  CosInstance *pCVar2;
  
                    /* 0x1e50  46  Cos_InstSetUserData */
  pCVar2 = (CosInstance *)Cos_InstHandleToIndex(hInst);
  pCVar1 = g_aCostumeInstances;
  if ((-1 < (int)pCVar2) && ((int)pCVar2 < g_nMaxInstances)) {
    g_aCostumeInstances[(int)pCVar2].nUserData = userData;
    pCVar2 = pCVar1;
  }
  return (int)pCVar2;
}

/* ---- 0x10001e80  Cos_NewStateBasedTag ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: unused */
/* WARNING: Variable defined which should be unmapped: handlers */
/* Export: registers a state-based component tag (kind 0): id, name, user data and the seven
   handlers (ComponentTag +0x2c). Hand-written in build/overrides_logic_chore.c. */

uint __cdecl Cos_NewStateBasedTag(uint id,uint name,uint unused,uint *handlers,int extra)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *in_stack_00000024;
  int in_stack_00000028;
  
                    /* 0x1e80  56  Cos_NewStateBasedTag */
  iVar1 = Cos_NewTagEntry((ComponentTag **)&extra,id,(char *)name,unused,extra);
  if (iVar1 != 0) {
    *(undefined4 *)(in_stack_00000028 + 4) = 0;
    puVar2 = (undefined4 *)(in_stack_00000028 + 0x2c);
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *in_stack_00000024;
      in_stack_00000024 = in_stack_00000024 + 1;
      puVar2 = puVar2 + 1;
    }
    return 1;
  }
  return 0;
}
#endif


/* ---- 0x10001ed0  Cos_NewTagEntry ---- */
/* Common part of Cos_NewStateBasedTag / Cos_NewIntTag / Cos_NewFloatTag: refuses a tag id that is
   already registered or a name longer than 31 characters, takes the next component tag record
   (Cos_AllocTagSlot, ComponentTag 0x5c bytes in g_aComponentTags), stores id (+0), name (+8) and
   the caller's user data (+0x28) and returns the record through the first argument. Returns 1, 0
   when refused. (Inlined in the remaster's libchore.so.) */

int __cdecl Cos_NewTagEntry(ComponentTag **ppTag,int tagId,char *name,int unused,int userData)

{
  char cVar1;
  uint uVar2;
  ComponentTag *pCVar3;
  char *pcVar4;
  
  uVar2 = 0;
  pCVar3 = g_aComponentTags;
  if (g_dwNumComponentTags != 0) {
    do {
      if (pCVar3->nId == tagId) {
        return 0;
      }
      uVar2 = uVar2 + 1;
      pCVar3 = pCVar3 + 1;
    } while (uVar2 < g_dwNumComponentTags);
  }
  uVar2 = 0xffffffff;
  pcVar4 = name;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  if (0x1f < ~uVar2 - 1) {
    return 0;
  }
  uVar2 = Cos_AllocTagSlot();
  if (g_dwNumComponentTags <= uVar2) {
    (*(code *)g_pSvcChore->pAssertFail)(IMG_ADDR(0x100102f8),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x420)
    ;
  }
  pCVar3 = g_aComponentTags + uVar2;
  *ppTag = pCVar3;
  msvc_strncpy(pCVar3->aName,name,0x1f);
  (*ppTag)->aName[0x1f] = '\0';
  (*ppTag)->nId = tagId;
  (*ppTag)->nUserData = userData;
  return 1;
}

/* ---- 0x10001f80  Cos_NewIntTag ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: unused */
/* WARNING: Variable defined which should be unmapped: handlers */
/* Export: registers an int component tag (kind 1), see Cos_NewStateBasedTag. Hand-written in
   build/overrides_logic_chore.c. */

uint __cdecl Cos_NewIntTag(uint id,uint name,uint unused,uint *handlers,int extra)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *in_stack_00000024;
  int in_stack_00000028;
  
                    /* 0x1f80  55  Cos_NewIntTag */
  iVar1 = Cos_NewTagEntry((ComponentTag **)&extra,id,(char *)name,unused,extra);
  if (iVar1 != 0) {
    *(undefined4 *)(in_stack_00000028 + 4) = 1;
    puVar2 = (undefined4 *)(in_stack_00000028 + 0x2c);
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *in_stack_00000024;
      in_stack_00000024 = in_stack_00000024 + 1;
      puVar2 = puVar2 + 1;
    }
    return 1;
  }
  return 0;
}
#endif


/* ---- 0x10001fd0  Cos_NewFloatTag ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: unused */
/* WARNING: Variable defined which should be unmapped: handlers */
/* Export: registers a float component tag (kind 2), see Cos_NewStateBasedTag. Hand-written in
   build/overrides_logic_chore.c. */

uint __cdecl Cos_NewFloatTag(uint id,uint name,uint unused,uint *handlers,int extra)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *in_stack_00000024;
  int in_stack_00000028;
  
                    /* 0x1fd0  54  Cos_NewFloatTag */
  iVar1 = Cos_NewTagEntry((ComponentTag **)&extra,id,(char *)name,unused,extra);
  if (iVar1 != 0) {
    *(undefined4 *)(in_stack_00000028 + 4) = 2;
    puVar2 = (undefined4 *)(in_stack_00000028 + 0x2c);
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *in_stack_00000024;
      in_stack_00000024 = in_stack_00000024 + 1;
      puVar2 = puVar2 + 1;
    }
    return 1;
  }
  return 0;
}
#endif


/* ---- 0x10002080  Cos_RegisterComponent ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Export, called back by a tag's Create handler: appends a component to the costume: tag `tagId`,
   the EXE's component data `data`, parent = the component with tag `parentTagId` and data
   `parentData` (0 for a root; an unknown tag or parent refuses), the state description `pStates`
   for state-based tags (Cos_InitComponentStates); the component notifier is told. Returns 1, 0 when
   refused. */

int __cdecl
Cos_RegisterComponent
          (uint hCostume,char *name,int data,int tagId,int parentData,int parentTagId,int *pStates)

{
  Costume *pCostume;
  char *pcVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  ComponentTag *pCVar5;
  CosComponent *pCVar6;
  int *piVar7;
  int *in_stack_00000038;
  
                    /* 0x2080  57  Cos_RegisterComponent */
  iVar3 = Cos_HandleToIndex(hCostume);
  if (data == 0) {
    return 0;
  }
  pCostume = g_aCostumes + iVar3;
  if (parentTagId != 0) {
    uVar4 = 0;
    pCVar5 = g_aComponentTags;
    if (g_dwNumComponentTags != 0) {
      do {
        if ((int *)pCVar5->nId == pStates) break;
        uVar4 = uVar4 + 1;
        pCVar5 = pCVar5 + 1;
      } while (uVar4 < g_dwNumComponentTags);
    }
    if (uVar4 == g_dwNumComponentTags) {
      return 0;
    }
    pcVar1 = (char *)pCostume->dwNumComponents;
    name = (char *)0x0;
    if (pcVar1 != (char *)0x0) {
      piVar7 = &pCostume->pComponents->nData;
      do {
        if (((int *)g_aComponentTags[piVar7[-1]].nId == pStates) && (*piVar7 == parentTagId)) break;
        piVar7 = piVar7 + 0x10;
        name = name + 1;
      } while (name < pcVar1);
    }
    if (name == pcVar1) {
      return 0;
    }
  }
  uVar4 = 0;
  pCVar5 = g_aComponentTags;
  if (g_dwNumComponentTags != 0) {
    do {
      if (pCVar5->nId == parentData) break;
      uVar4 = uVar4 + 1;
      pCVar5 = pCVar5 + 1;
    } while (uVar4 < g_dwNumComponentTags);
  }
  if (uVar4 != g_dwNumComponentTags) {
    pCVar6 = (CosComponent *)
             (*(code *)g_pSvcChore->pRealloc)
                       (pCostume->pComponents,(pCostume->dwNumComponents + 1) * 0x40,
                        s_C__grimsrc_libs_chore_Costume_c_1001020c,0x4ef);
    uVar2 = pCostume->dwNumComponents;
    pCostume->pComponents = pCVar6;
    if (parentTagId == 0) {
      name = (char *)0xffffffff;
    }
    Cos_InitComponent(pCostume,pCVar6 + uVar2,(char *)data,uVar4,tagId,(int)name);
    pCostume->dwNumComponents = pCostume->dwNumComponents + 1;
    Cos_InitComponentStates(pCVar6 + uVar2,in_stack_00000038);
    if (g_pfnCompNotifier != (void *)0x0) {
      (*(code *)g_pfnCompNotifier)();
    }
    return 1;
  }
  return 0;
}
#endif


/* ---- 0x100021f0  Cos_RemoveComponent ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Export: deletes the component with tag `tagId` and component data `data`
   (CosUtil_DeleteComponent). */

int __cdecl Cos_RemoveComponent(int hCostume,int tagId,int data)

{
  Costume *pCVar1;
  int iVar2;
  int *piVar3;
  uint compNum;
  int in_stack_00000010;
  
                    /* 0x21f0  61  Cos_RemoveComponent */
  pCVar1 = CosUtil_PtrFromHandle(hCostume);
  if (pCVar1 != (Costume *)0x0) {
    compNum = 0;
    if (pCVar1->dwNumComponents != 0) {
      piVar3 = &pCVar1->pComponents->nTag;
      while ((iVar2 = piVar3[1], iVar2 != in_stack_00000010 ||
             (iVar2 = *piVar3, g_aComponentTags[iVar2].nId != data))) {
        compNum = compNum + 1;
        piVar3 = piVar3 + 0x10;
        if (pCVar1->dwNumComponents <= compNum) {
          return iVar2;
        }
      }
      pCVar1 = (Costume *)CosUtil_DeleteComponent(tagId,compNum);
    }
  }
  return (int)pCVar1;
}
#endif


/* ---- 0x10002ee0  Cos_InstCountComponents ---- */
/* Export: number of components of the instance's costume. */

int __cdecl Cos_InstCountComponents(int hInst)

{
  int iVar1;
  uint uVar2;
  
                    /* 0x2ee0  36  Cos_InstCountComponents */
  iVar1 = Cos_InstHandleToIndex(hInst);
  if (iVar1 < 0) {
    return 0;
  }
  uVar2 = CosUtil_CountComponents(g_aCostumes + g_aCostumeInstances[iVar1].nCostume);
  return uVar2;
}

/* ---- 0x10002f20  Cos_InstComponentInfo ---- */
/* Export: CosUtil_ComponentInfo for the instance's costume (without the tag kind). */

int __cdecl Cos_InstComponentInfo(int inst,uint index,int *outTag,undefined4 *outA,undefined4 *outB)

{
  int iVar1;
  
                    /* 0x2f20  34  Cos_InstComponentInfo */
  iVar1 = Cos_InstHandleToIndex(inst);
  iVar1 = CosUtil_ComponentInfo
                    ((int)(g_aCostumes + g_aCostumeInstances[iVar1].nCostume),index,outTag,outA,outB
                     ,(int *)0x0);
  return iVar1;
}

/* ---- 0x10002f70  Cos_InstCountChores ---- */
/* Export: number of chores of the instance's costume. */

int __cdecl Cos_InstCountChores(int hInst)

{
  int iVar1;
  
                    /* 0x2f70  35  Cos_InstCountChores */
  iVar1 = Cos_InstHandleToIndex(hInst);
  return g_aCostumes[g_aCostumeInstances[iVar1].nCostume].dwNumChores;
}

/* ---- 0x10002fb0  Cos_GetCostumeName ---- */
/* Export: name of the costume `hCostume` (assert 'whichCostume >= 0 && whichCostume <
   maxCostumes'). */

char * __cdecl Cos_GetCostumeName(int hCostume)

{
  int iVar1;
  
                    /* 0x2fb0  28  Cos_GetCostumeName */
  iVar1 = Cos_HandleToIndex(hCostume);
  if ((iVar1 < 0) || (g_nMaxCostumes <= iVar1)) {
    (*(code *)g_pSvcChore->pAssertFail)(IMG_ADDR(0x10010468),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x7eb)
    ;
  }
  return g_aCostumes[iVar1].aName;
}

/* ---- 0x10003000  Cos_InstGetCostume ---- */
/* Export: the costume of an instance, and its handle through outHandle. */

Costume * __cdecl Cos_InstGetCostume(int hInst,int *outHandle)

{
  Costume *pCVar1;
  int iVar2;
  
                    /* 0x3000  37  Cos_InstGetCostume */
  iVar2 = Cos_InstHandleToIndex(hInst);
  pCVar1 = g_aCostumes + g_aCostumeInstances[iVar2].nCostume;
  if (outHandle != (int *)0x0) {
    iVar2 = Cos_IndexToHandle(g_aCostumeInstances[iVar2].nCostume);
    *outHandle = iVar2;
  }
  return pCVar1;
}

/* ---- 0x10003050  Cos_InstChoreName ---- */
/* Export: name of chore `choreNum` of the instance's costume (assert 'choreNum >= 0 && choreNum <
   pCostume->numChores'). */

char * __cdecl Cos_InstChoreName(int hInst,uint choreNum)

{
  Costume *pCVar1;
  int iVar2;
  
                    /* 0x3050  30  Cos_InstChoreName */
  iVar2 = Cos_InstHandleToIndex(hInst);
  pCVar1 = g_aCostumes;
  iVar2 = g_aCostumeInstances[iVar2].nCostume;
  if (g_aCostumes[iVar2].dwNumChores <= choreNum) {
    (*(code *)g_pSvcChore->pAssertFail)(IMG_ADDR(0x10010498),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x802)
    ;
  }
  return pCVar1[iVar2].pChores[choreNum].aName;
}

/* ---- 0x10003160  Cos_InstStopChores ---- */
/* Export: stops every chore of the instance (flags and time cleared) and calls the Stop handler
   (ComponentTag +0x38, slot 3) of each component that a chore has a track for. */

int __cdecl Cos_InstStopChores(uint hInst)

{
  int iVar1;
  int iVar2;
  Chore *pCVar3;
  int iVar4;
  Costume *pCVar5;
  CosInstance *pCVar6;
  int iVar7;
  ChoreInstance *pCVar8;
  uint uVar9;
  int iVar10;
  
                    /* 0x3160  48  Cos_InstStopChores */
  iVar7 = Cos_InstHandleToIndex(hInst);
  pCVar6 = g_aCostumeInstances;
  pCVar5 = g_aCostumes;
  hInst = 0;
  iVar1 = g_aCostumeInstances[iVar7].nCostume;
  pCVar8 = g_aCostumeInstances[iVar7].pChoreInstances;
  if (g_aCostumes[iVar1].dwNumChores != 0) {
    do {
      iVar2 = pCVar8->nChore;
      iVar10 = 0;
      pCVar8->dwFlags = 0;
      pCVar8->nTime = 0;
      uVar9 = 0;
      pCVar3 = pCVar5[iVar1].pChores;
      if (pCVar3[iVar2].dwNumTracks != 0) {
        do {
          iVar4 = *(int *)((int)&(pCVar3[iVar2].pChoreTracks)->nCompNum + iVar10);
          if ((code *)g_aComponentTags[pCVar5[iVar1].pComponents[iVar4].nTag].pfnStop != (code *)0x0
             ) {
            (*(code *)g_aComponentTags[pCVar5[iVar1].pComponents[iVar4].nTag].pfnStop)
                      (pCVar6[iVar7].pInstanceData[iVar4]);
          }
          uVar9 = uVar9 + 1;
          iVar10 = iVar10 + 0x10;
        } while (uVar9 < pCVar3[iVar2].dwNumTracks);
      }
      hInst = hInst + 1;
      pCVar8 = pCVar8 + 1;
    } while (hInst < pCVar5[iVar1].dwNumChores);
  }
  return 1;
}

/* ---- 0x10003240  Cos_InstStopChore ---- */
/* Export: stops chore `choreNum` of the instance like Cos_InstStopChores. Returns 1, 0 for a bad
   chore. */

int __cdecl Cos_InstStopChore(int hInst,uint choreNum)

{
  ChoreInstance *pCVar1;
  int iVar2;
  int iVar3;
  Chore *pCVar4;
  int iVar5;
  Costume *pCVar6;
  CosInstance *pCVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
                    /* 0x3240  47  Cos_InstStopChore */
  iVar8 = Cos_InstHandleToIndex(hInst);
  pCVar7 = g_aCostumeInstances;
  pCVar6 = g_aCostumes;
  iVar2 = g_aCostumeInstances[iVar8].nCostume;
  if (choreNum < g_aCostumes[iVar2].dwNumChores) {
    iVar10 = 0;
    pCVar1 = g_aCostumeInstances[iVar8].pChoreInstances + choreNum;
    iVar9 = 0;
    pCVar1->dwFlags = 0;
    pCVar1->nTime = 0;
    iVar3 = pCVar1->nChore;
    pCVar4 = pCVar6[iVar2].pChores;
    if (0 < (int)pCVar4[iVar3].dwNumTracks) {
      do {
        iVar5 = *(int *)((int)&(pCVar4[iVar3].pChoreTracks)->nCompNum + iVar10);
        if ((code *)g_aComponentTags[pCVar6[iVar2].pComponents[iVar5].nTag].pfnStop != (code *)0x0)
        {
          (*(code *)g_aComponentTags[pCVar6[iVar2].pComponents[iVar5].nTag].pfnStop)
                    (pCVar7[iVar8].pInstanceData[iVar5]);
        }
        iVar9 = iVar9 + 1;
        iVar10 = iVar10 + 0x10;
      } while (iVar9 < (int)pCVar4[iVar3].dwNumTracks);
    }
    return 1;
  }
  return 0;
}

/* ---- 0x10003300  Cos_InstPauseChores ---- */
/* Export: pauses every chore of the instance (clears the playing flag 1, keeps the time). */

int __cdecl Cos_InstPauseChores(int hInst)

{
  int iVar1;
  Costume *pCVar2;
  int iVar3;
  ChoreInstance *pCVar4;
  uint uVar5;
  
                    /* 0x3300  41  Cos_InstPauseChores */
  iVar3 = Cos_InstHandleToIndex(hInst);
  pCVar2 = g_aCostumes;
  iVar1 = g_aCostumeInstances[iVar3].nCostume;
  uVar5 = 0;
  pCVar4 = g_aCostumeInstances[iVar3].pChoreInstances;
  if (g_aCostumes[iVar1].dwNumChores != 0) {
    do {
      uVar5 = uVar5 + 1;
      pCVar4->dwFlags = pCVar4->dwFlags & 0xfffffffe;
      pCVar4 = pCVar4 + 1;
    } while (uVar5 < pCVar2[iVar1].dwNumChores);
  }
  return 1;
}

/* ---- 0x10003360  Cos_InstPauseChore ---- */
/* Export: pauses chore `choreNum` (clears flag 1). */

int __cdecl Cos_InstPauseChore(int hInst,uint choreNum)

{
  int iVar1;
  
                    /* 0x3360  40  Cos_InstPauseChore */
  iVar1 = Cos_InstHandleToIndex(hInst);
  if (choreNum < g_aCostumes[g_aCostumeInstances[iVar1].nCostume].dwNumChores) {
    g_aCostumeInstances[iVar1].pChoreInstances[choreNum].dwFlags =
         g_aCostumeInstances[iVar1].pChoreInstances[choreNum].dwFlags & 0xfffffffe;
    return 1;
  }
  return 0;
}

/* ---- 0x100033b0  Cos_InstCompleteChore ---- */
/* Export: runs chore `choreNum` to its end at once: flags = playing, Chore_AdvanceTime by the rest
   of its length (every remaining key is applied). */

int __cdecl Cos_InstCompleteChore(int hInst,uint choreNum)

{
  CosInstance *pInst;
  Costume *pCostume;
  int iVar1;
  
                    /* 0x33b0  32  Cos_InstCompleteChore */
  iVar1 = Cos_InstHandleToIndex(hInst);
  pInst = g_aCostumeInstances + iVar1;
  pCostume = g_aCostumes + pInst->nCostume;
  if (choreNum < pCostume->dwNumChores) {
    pInst->pChoreInstances[choreNum].dwFlags = 1;
    Chore_AdvanceTime(pCostume,pInst,choreNum,
                      pCostume->pChores[choreNum].dwLength - pInst->pChoreInstances[choreNum].nTime,
                      hInst);
    return 1;
  }
  return 0;
}

/* ---- 0x10003430  Cos_InstCompleteChores ---- */
/* Export: Cos_InstCompleteChore for every playing chore of the instance. */

int __cdecl Cos_InstCompleteChores(int hInst)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  CosInstance *pInst;
  Costume *pCostume;
  int iVar1;
  byte *pbVar2;
  int iVar3;
  uint choreNum;
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
                    /* 0x3430  33  Cos_InstCompleteChores */
  iVar1 = Cos_InstHandleToIndex(hInst);
  iVar3 = 0;
  pInst = g_aCostumeInstances + iVar1;
  choreNum = 0;
  pCostume = g_aCostumes + g_aCostumeInstances[iVar1].nCostume;
  if (g_aCostumes[g_aCostumeInstances[iVar1].nCostume].dwNumChores != 0) {
    iStack_4 = 0;
    do {
      pbVar2 = (byte *)((int)&pInst->pChoreInstances->dwFlags + iStack_4);
      if ((*pbVar2 & 1) != 0) {
        Chore_AdvanceTime(pCostume,pInst,choreNum,
                          *(int *)(pCostume->pChores->aName + iVar3 + 0x28) - *(int *)(pbVar2 + 8),
                          hInst);
      }
      choreNum = choreNum + 1;
      iVar3 = iVar3 + 0x2c;
      iStack_4 = iStack_4 + 0xc;
    } while (choreNum < pCostume->dwNumChores);
  }
  return 1;
}
#undef iStack_4


/* ---- 0x100034c0  Cos_InstPlayChore ---- */
/* Export: starts chore `choreNum`: flags 1 (playing), | 2 when `loop`, | 4 (advanced by
   Cos_InstUpdateChores) unless `manual`. The time is kept (Cos_InstStopChore clears it). */

int __cdecl Cos_InstPlayChore(int hInst,uint choreNum,int loop,int manual)

{
  ChoreInstance *pCVar1;
  int iVar2;
  
                    /* 0x34c0  42  Cos_InstPlayChore */
  iVar2 = Cos_InstHandleToIndex(hInst);
  if (choreNum < g_aCostumes[g_aCostumeInstances[iVar2].nCostume].dwNumChores) {
    pCVar1 = g_aCostumeInstances[iVar2].pChoreInstances + choreNum;
    pCVar1->dwFlags = 1;
    if (loop != 0) {
      pCVar1->dwFlags = 3;
    }
    if (manual == 0) {
      pCVar1->dwFlags = pCVar1->dwFlags | 4;
    }
    return 1;
  }
  return 0;
}

/* ---- 0x10003530  Cos_InstUpdateChore ---- */
/* Export: advances chore `choreNum` by `dt` ms when it is playing (Chore_AdvanceTime). */

int __cdecl Cos_InstUpdateChore(int hInst,uint choreNum,int dt)

{
  CosInstance *pInst;
  int iVar1;
  
                    /* 0x3530  49  Cos_InstUpdateChore */
  iVar1 = Cos_InstHandleToIndex(hInst);
  pInst = g_aCostumeInstances + iVar1;
  if (choreNum < g_aCostumes[pInst->nCostume].dwNumChores) {
    if ((pInst->pChoreInstances[choreNum].dwFlags & 1) != 0) {
      Chore_AdvanceTime(g_aCostumes + pInst->nCostume,pInst,choreNum,dt,hInst);
    }
    return 1;
  }
  return 0;
}

/* ---- 0x100035a0  Cos_InstUpdateChores ---- */
/* Export: advances every playing chore with flag 4 (not manual) by `dt` ms. */

int __cdecl Cos_InstUpdateChores(int hInst,int dt)

{
  CosInstance *pInst;
  Costume *pCostume;
  int iVar1;
  ChoreInstance *pCVar2;
  uint choreNum;
  
                    /* 0x35a0  50  Cos_InstUpdateChores */
  iVar1 = Cos_InstHandleToIndex(hInst);
  choreNum = 0;
  pInst = g_aCostumeInstances + iVar1;
  pCVar2 = pInst->pChoreInstances;
  pCostume = g_aCostumes + g_aCostumeInstances[iVar1].nCostume;
  if (g_aCostumes[g_aCostumeInstances[iVar1].nCostume].dwNumChores != 0) {
    do {
      if (((pCVar2->dwFlags & 1) != 0) && ((pCVar2->dwFlags & 4) != 0)) {
        Chore_AdvanceTime(pCostume,pInst,choreNum,dt,hInst);
      }
      choreNum = choreNum + 1;
      pCVar2 = pCVar2 + 1;
    } while (choreNum < pCostume->dwNumChores);
  }
  return 1;
}

/* ---- 0x10003620  Cos_InstSetChoreLoop ---- */
/* Export: sets or clears the looping flag 2 of chore `choreNum`. */

int __cdecl Cos_InstSetChoreLoop(int hInst,uint choreNum,int loop)

{
  ChoreInstance *pCVar1;
  int iVar2;
  
                    /* 0x3620  45  Cos_InstSetChoreLoop */
  iVar2 = Cos_InstHandleToIndex(hInst);
  if (g_aCostumes[g_aCostumeInstances[iVar2].nCostume].dwNumChores <= choreNum) {
    return 0;
  }
  pCVar1 = g_aCostumeInstances[iVar2].pChoreInstances + choreNum;
  if (loop != 0) {
    pCVar1->dwFlags = pCVar1->dwFlags | 2;
    return 1;
  }
  pCVar1->dwFlags = pCVar1->dwFlags & 0xfffffffd;
  return 1;
}

/* ---- 0x10003690  Cos_InstSetChoreAdv ---- */
/* Export: `manual` != 0 clears flag 4 (the chore is no longer advanced by Cos_InstUpdateChores), 0
   sets it. */

int __cdecl Cos_InstSetChoreAdv(int hInst,uint choreNum,int manual)

{
  ChoreInstance *pCVar1;
  int iVar2;
  
                    /* 0x3690  44  Cos_InstSetChoreAdv */
  iVar2 = Cos_InstHandleToIndex(hInst);
  if (g_aCostumes[g_aCostumeInstances[iVar2].nCostume].dwNumChores <= choreNum) {
    return 0;
  }
  pCVar1 = g_aCostumeInstances[iVar2].pChoreInstances + choreNum;
  if (manual != 0) {
    pCVar1->dwFlags = pCVar1->dwFlags & 0xfffffffb;
    return 1;
  }
  pCVar1->dwFlags = pCVar1->dwFlags | 4;
  return 1;
}

/* ---- 0x10003700  Cos_InstChoreStatus ---- */
/* Export: the flags of chore `choreNum` (1 playing, 2 looping, 4 auto-advanced), 0 for a bad chore.
    */

uint __cdecl Cos_InstChoreStatus(int hInst,uint choreNum)

{
  int iVar1;
  
                    /* 0x3700  31  Cos_InstChoreStatus */
  iVar1 = Cos_InstHandleToIndex(hInst);
  if (choreNum < g_aCostumes[g_aCostumeInstances[iVar1].nCostume].dwNumChores) {
    return g_aCostumeInstances[iVar1].pChoreInstances[choreNum].dwFlags;
  }
  return 0;
}

/* ---- 0x10003750  Cos_Initialize ---- */
/* Export, called first by the EXE (sputCostume): keeps the host service table (g_pSvcChore) and
   fills the module interface: Cos_Initialize, Cos_Terminate, Cos_Startup, Cos_Shutdown, Cos_Save,
   Cos_Restore, 0, 0. */

int __cdecl Cos_Initialize(GrimServices *svc,void **moduleIface)

{
                    /* 0x3750  29  Cos_Initialize */
  g_pSvcChore = svc;
  *moduleIface = Cos_Initialize;
  moduleIface[1] = Cos_Terminate;
  moduleIface[2] = Cos_Startup;
  moduleIface[3] = Cos_Shutdown;
  moduleIface[4] = Cos_Save;
  moduleIface[5] = Cos_Restore;
  moduleIface[6] = (void *)0x0;
  moduleIface[7] = (void *)0x0;
  g_nCosInitialize = 1;
  return 0;
}

/* ---- 0x100037a0  Cos_Save ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Module interface slot 4 / export: writes the costume table into the save game. Hand-written in
   build/overrides_logic_chore.c. */

uint __cdecl Cos_Save(void *io)

{
  unsigned char _frame[0x20];  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int in_stack_00000008;
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
                    /* 0x37a0  64  Cos_Save */
  iStack_4 = 0;
  (*(code *)io)(&g_nMaxCostumes,4);
  iVar3 = 0;
  if (0 < g_nMaxCostumes) {
    iVar2 = 0;
    do {
      if (*(int *)(g_aCostumes->aName + iVar2 + 0x38) == 0) {
        if (g_pfnSaveVerify != (void *)0x0) {
          iVar1 = (*(code *)g_pfnSaveVerify)(g_aCostumes->aName + iVar2);
          if (iVar1 == 0) goto LAB_100037ef;
        }
        iStack_4 = iStack_4 + 1;
      }
LAB_100037ef:
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 0x3c;
    } while (iVar3 < g_nMaxCostumes);
  }
  (*(code *)io)(&iStack_4,4);
  iVar3 = 0;
  if (0 < g_nMaxCostumes) {
    iVar2 = 0;
    do {
      if (*(int *)(g_aCostumes->aName + iVar2 + 0x38) == 0) {
        if (g_pfnSaveVerify != (void *)0x0) {
          iVar1 = (*(code *)g_pfnSaveVerify)(g_aCostumes->aName + iVar2);
          if (iVar1 == 0) goto LAB_10003863;
        }
        in_stack_00000008 = Cos_IndexToHandle(iVar3);
        (*(code *)io)(&STACK0X(0x00000008),4);
        (*(code *)io)(g_aCostumes->aName + iVar2,0x20);
      }
LAB_10003863:
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 0x3c;
    } while (iVar3 < g_nMaxCostumes);
  }
  (*(code *)io)(&g_nMaxInstances,4);
  return 0;
}
#undef iStack_4

#endif


/* ---- 0x10003890  Cos_SaveInstance ---- */
/* Export: writes a costume instance into the save game: the Save handler (ComponentTag +0x44, slot
   6) of every component with save = 1, then flags, chore and time of every chore state. */

int __cdecl Cos_SaveInstance(int hInst,void *io)

{
  int iVar1;
  Costume *pCVar2;
  CosInstance *pCVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
                    /* 0x3890  65  Cos_SaveInstance */
  iVar4 = Cos_InstHandleToIndex(hInst);
  pCVar3 = g_aCostumeInstances;
  pCVar2 = g_aCostumes;
  iVar1 = g_aCostumeInstances[iVar4].nCostume;
  iVar6 = 0;
  if (0 < (int)g_aCostumes[iVar1].dwNumComponents) {
    iVar5 = 0;
    do {
      if ((code *)g_aComponentTags[*(int *)((pCVar2[iVar1].pComponents)->aName + iVar5 + 0x20)].
                  pfnSave != (code *)0x0) {
        (*(code *)g_aComponentTags[*(int *)((pCVar2[iVar1].pComponents)->aName + iVar5 + 0x20)].
                  pfnSave)(hInst,iVar6,1,pCVar3[iVar4].pInstanceData[iVar6],io);
      }
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 0x40;
    } while (iVar6 < (int)pCVar2[iVar1].dwNumComponents);
  }
  iVar6 = 0;
  if (0 < (int)pCVar2[iVar1].dwNumChores) {
    hInst = 0;
    do {
      iVar5 = (int)&(pCVar3[iVar4].pChoreInstances)->dwFlags + hInst;
      (*(code *)io)(iVar5,4);
      (*(code *)io)(iVar5 + 4,4);
      (*(code *)io)(iVar5 + 8,4);
      iVar6 = iVar6 + 1;
      hInst = hInst + 0xc;
    } while (iVar6 < (int)pCVar2[iVar1].dwNumChores);
  }
  return 0;
}

/* ---- 0x10003970  Cos_Restore ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Module interface slot 5 / export: reloads the costumes of a save game. Hand-written in
   build/overrides_logic_chore.c. */

uint __cdecl Cos_Restore(void *io)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[64] __attribute__((aligned(16)));  /* the original frame below the return address */
  char *pcVar1;
  void *pvVar2;
  int hCostume;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int unaff_retaddr;
  #define iStack_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define iStack_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define auStack_20 (*(undefined1 (*)[24])(_frame + (0x40 - 0x20)))
  #define iStack_8 (*(int *)(_frame + (0x40 - 0x8)))
  
                    /* 0x3970  62  Cos_Restore */
  iVar3 = 0;
  if (0 < g_nMaxCostumes) {
    iVar5 = 0;
    do {
      if (*(int *)(g_aCostumes->aName + iVar5 + 0x38) == 0) {
        hCostume = Cos_IndexToHandle(iVar3);
        Cos_Free(hCostume);
      }
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 0x3c;
    } while (iVar3 < g_nMaxCostumes);
  }
  pvVar2 = io;
  (*(code *)io)(&iStack_28,4);
  if (g_nMaxCostumes < iStack_28) {
    g_aCostumes = (Costume *)
                  (*(code *)g_pSvcChore->pRealloc)
                            (g_aCostumes,iStack_28 * 0x3c,s_C__grimsrc_libs_chore_Costume_c_1001020c
                             ,0xa2b);
    if (g_nMaxCostumes < iStack_28) {
      iVar3 = g_nMaxCostumes * 0x3c;
      do {
        g_nMaxCostumes = g_nMaxCostumes + 1;
        pcVar1 = g_aCostumes->aName + iVar3 + 0x38;
        pcVar1[0] = '\x01';
        pcVar1[1] = '\0';
        pcVar1[2] = '\0';
        pcVar1[3] = '\0';
        iVar3 = iVar3 + 0x3c;
      } while (g_nMaxCostumes < iStack_28);
    }
    g_nMaxCostumes = iStack_28;
  }
  (*(code *)pvVar2)(&iStack_24,4);
  iVar3 = 0;
  if (0 < iStack_24) {
    do {
      (*(code *)pvVar2)(&io,4);
      (*(code *)pvVar2)(auStack_20,0x20);
      Cos_LoadEntry((_stkneg + 20),iStack_8);
      iVar5 = Cos_HandleToIndex(unaff_retaddr);
      g_aCostumes[iVar5].nFree = 0;
      g_nCostumes = g_nCostumes + 1;
      iVar3 = iVar3 + 1;
    } while (iVar3 < iStack_24);
  }
  (*(code *)pvVar2)(&iStack_28,4);
  if (g_nMaxInstances < iStack_28) {
    g_aCostumeInstances =
         (CosInstance *)
         (*(code *)g_pSvcChore->pRealloc)
                   (g_aCostumeInstances,iStack_28 * 0x14,s_C__grimsrc_libs_chore_Costume_c_1001020c,
                    0xa42);
    g_nMaxInstances = iStack_28;
  }
  iVar3 = 0;
  if (0 < g_nMaxInstances) {
    iVar5 = 0;
    do {
      puVar4 = (undefined4 *)((int)&g_aCostumeInstances->nCostume + iVar5);
      iVar3 = iVar3 + 1;
      *puVar4 = 0;
      puVar4[1] = 0;
      puVar4[2] = 0;
      puVar4[3] = 0;
      puVar4[4] = 0;
      *(undefined4 *)((int)&g_aCostumeInstances->nFree + iVar5) = 1;
      iVar5 = iVar5 + 0x14;
    } while (iVar3 < g_nMaxInstances);
  }
  g_nMaxInstances = iStack_28;
  return 0;
}
#undef auStack_20
#undef iStack_24
#undef iStack_28
#undef iStack_8

#endif


/* ---- 0x10003b40  Cos_RestoreInstance ---- */
/* Export: reads a costume instance back from a save game (Cos_SaveInstance with save = 0). */

int __cdecl Cos_RestoreInstance(int hInst,void *io)

{
  int iVar1;
  Costume *pCVar2;
  CosInstance *pCVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
                    /* 0x3b40  63  Cos_RestoreInstance */
  iVar4 = Cos_InstHandleToIndex(hInst);
  pCVar3 = g_aCostumeInstances;
  pCVar2 = g_aCostumes;
  iVar1 = g_aCostumeInstances[iVar4].nCostume;
  iVar6 = 0;
  if (0 < (int)g_aCostumes[iVar1].dwNumComponents) {
    iVar5 = 0;
    do {
      if ((code *)g_aComponentTags[*(int *)((pCVar2[iVar1].pComponents)->aName + iVar5 + 0x20)].
                  pfnSave != (code *)0x0) {
        (*(code *)g_aComponentTags[*(int *)((pCVar2[iVar1].pComponents)->aName + iVar5 + 0x20)].
                  pfnSave)(hInst,iVar6,0,pCVar3[iVar4].pInstanceData[iVar6],io);
      }
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 0x40;
    } while (iVar6 < (int)pCVar2[iVar1].dwNumComponents);
  }
  iVar6 = 0;
  if (0 < (int)pCVar2[iVar1].dwNumChores) {
    hInst = 0;
    do {
      iVar5 = (int)&(pCVar3[iVar4].pChoreInstances)->dwFlags + hInst;
      (*(code *)io)(iVar5,4);
      (*(code *)io)(iVar5 + 4,4);
      (*(code *)io)(iVar5 + 8,4);
      iVar6 = iVar6 + 1;
      hInst = hInst + 0xc;
    } while (iVar6 < (int)pCVar2[iVar1].dwNumChores);
  }
  return 0;
}

/* ---- 0x10003c20  Cos_CollectUsedTags ---- */
/* Fills g_aTagLookups with the distinct component tag indices the costume's components use, in
   order of first use, and returns their number. CosUtil_Write uses it for the 'section tags' of the
   text costume and to map a component's tag index to its line in that section. */

uint __cdecl Cos_CollectUsedTags(Costume *pCostume)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  int iVar5;
  #define uStack_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar5 = 0;
  uVar1 = 0;
  uStack_4 = 0;
  if (pCostume->dwNumComponents != 0) {
    puVar4 = g_aTagLookups;
    do {
      uVar2 = 0;
      if (IMG_ADDR(0x10014210) < (int)puVar4) {
        puVar3 = g_aTagLookups;
        do {
          if (*puVar3 == *(uint *)(pCostume->pComponents->aName + iVar5 + 0x20)) break;
          uVar2 = uVar2 + 1;
          puVar3 = puVar3 + 1;
        } while ((int)uVar2 < (int)uVar1);
      }
      puVar3 = puVar4;
      if (uVar2 == uVar1) {
        uVar1 = uVar1 + 1;
        puVar3 = puVar4 + 1;
        *puVar4 = *(uint *)(pCostume->pComponents->aName + iVar5 + 0x20);
      }
      uStack_4 = uStack_4 + 1;
      iVar5 = iVar5 + 0x40;
      puVar4 = puVar3;
    } while (uStack_4 < pCostume->dwNumComponents);
  }
  return uVar1;
}
#undef uStack_4


/* ---- 0x10003c90  Cos_AddKey ---- */
/* Adds a key at `time` to the track of component `comp` in chore `choreNum` (assert 'pCostume !=
   NULL'): the track (ChoreTrack, 16 bytes) is appended when the chore has none for that component;
   a key with that time is reused (bsearch with Cos_CompareKeys), otherwise one is appended; the
   track's last key time (+4) and the chore length (+0x28, at least 1) grow to cover it; the keys
   are sorted again (msvc_qsort). Returns the key (ChoreKey: time, value), or 0 when the chore has
   two tracks for the same component. The caller (CosUtil_AddFSKey / AddIntKey / AddFloatKey) stores
   the value. Original static name AddKey (libchore.so). */

ChoreKey * __cdecl Cos_AddKey(Costume *pCostume,uint choreNum,int compNum,uint time)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Chore *pCVar1;
  ChoreTrack *pCVar2;
  uint uVar3;
  ChoreTrack *pCVar4;
  ChoreKey *pCVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  #define auStack_8 (*(uint (*)[2])(_frame + (0x20 - 0x8)))
  
  uVar3 = choreNum;
  if (pCostume == (Costume *)0x0) {
    (*(code *)g_pSvcChore->pAssertFail)(IMG_ADDR(0x1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xa9b)
    ;
  }
  pCVar1 = pCostume->pChores;
  uVar7 = 0;
  uVar6 = pCVar1[choreNum].dwNumTracks;
  pCVar2 = pCVar1[choreNum].pChoreTracks;
  pCVar4 = pCVar2;
  if (uVar6 != 0) {
    do {
      if (pCVar4->nCompNum == compNum) break;
      uVar7 = uVar7 + 1;
      pCVar4 = pCVar4 + 1;
    } while (uVar7 < uVar6);
  }
  if (uVar7 == uVar6) {
    pCVar1[choreNum].dwNumTracks = uVar6 + 1;
    pCVar4 = (ChoreTrack *)
             (*(code *)g_pSvcChore->pRealloc)
                       (pCVar2,(uVar6 + 1) * 0x10,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xaa8);
    pCVar1[choreNum].pChoreTracks = pCVar4;
    pCVar4 = pCVar4 + (pCVar1[choreNum].dwNumTracks - 1);
    pCVar4->dwNumKeys = 0;
    pCVar4->pKeys = (ChoreKey *)0x0;
    pCVar4->dwLastKeyTime = 0;
    pCVar4->nCompNum = compNum;
  }
  auStack_8[0] = time;
  if (pCVar4->dwNumKeys == 0) {
    pCVar5 = (ChoreKey *)0x0;
  }
  else {
    pCVar5 = (ChoreKey *)msvc_bsearch(auStack_8,pCVar4->pKeys,pCVar4->dwNumKeys,8,Cos_CompareKeys);
  }
  if (pCVar5 == (ChoreKey *)0x0) {
    uVar6 = pCVar4->dwNumKeys + 1;
    pCVar4->dwNumKeys = uVar6;
    pCVar5 = (ChoreKey *)
             (*(code *)g_pSvcChore->pRealloc)
                       (pCVar4->pKeys,uVar6 * 8,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xabb);
    pCVar4->pKeys = pCVar5;
    pCVar5 = pCVar5 + (pCVar4->dwNumKeys - 1);
  }
  pCVar5->dwTime = time;
  if (pCVar4->dwLastKeyTime < time) {
    pCVar4->dwLastKeyTime = time;
  }
  uVar6 = 1;
  if (time != 0) {
    uVar6 = time;
  }
  uVar7 = pCVar1[choreNum].dwLength;
  if ((pCVar1[choreNum].dwLength < uVar6) && (uVar7 = time, time == 0)) {
    uVar7 = 1;
  }
  pCVar1[choreNum].dwLength = uVar7;
  msvc_qsort(pCVar4->pKeys,pCVar4->dwNumKeys,8,Cos_CompareKeys);
  uVar6 = pCVar1[choreNum].dwNumTracks;
  choreNum = 0;
  if (uVar6 != 0) {
    pCostume = (Costume *)0x0;
    do {
      uVar7 = 0;
      if (uVar6 != 0) {
        iVar8 = 0;
        do {
          if ((choreNum != uVar7) &&
             (*(int *)((int)&(pCVar1[uVar3].pChoreTracks)->nCompNum + (int)pCostume->aName) ==
              *(int *)((int)&(pCVar1[uVar3].pChoreTracks)->nCompNum + iVar8))) {
            return (ChoreKey *)0x0;
          }
          uVar7 = uVar7 + 1;
          iVar8 = iVar8 + 0x10;
        } while (uVar7 < uVar6);
      }
      choreNum = choreNum + 1;
      pCostume = (Costume *)(pCostume->aName + 0x10);
    } while (choreNum < uVar6);
  }
  pCVar5 = (ChoreKey *)msvc_bsearch(auStack_8,pCVar4->pKeys,pCVar4->dwNumKeys,8,Cos_CompareKeys);
  return pCVar5;
}
#undef auStack_8


/* ---- 0x10003e50  Cos_CompareKeys ---- */
/* qsort / bsearch comparator of two ChoreKey records by time (+0, unsigned): -1 / 0 / 1. Original
   static name CompareKeys (libchore.so). */

int __cdecl Cos_CompareKeys(ChoreKey *a,ChoreKey *b)

{
  if (a->dwTime < b->dwTime) {
    return -1;
  }
  return (uint)(b->dwTime < a->dwTime);
}

/* ---- 0x10003e70  Cos_InitComponentStates ---- */
/* For a component of a state-based tag (kind 0) copies the state description the EXE passed to
   Cos_RegisterComponent ({count, values, names, bitmaps, bitmap args}) into the component: +0x30
   number of states, +0x34 state values (ints), +0x38 state names (copied strings), +0x3c
   apStateBitmaps (0x14-byte records: the 16 bytes of the description plus the result of the bitmap
   munger, CosUtil_RegisterBitmapMunger, at +0x10). Int and float tags have no states. Returns the
   number of states copied (0 for none). */

uint __cdecl Cos_InitComponentStates(CosComponent *pComponent,int *pStates)

{
  char cVar1;
  int *piVar2;
  char **ppcVar3;
  char *pcVar4;
  CosStateBitmap **ppCVar5;
  CosStateBitmap *pCVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int *piVar11;
  char *pcVar12;
  
  uVar8 = g_aComponentTags[pComponent->nTag].nKind;
  if (uVar8 == 0) {
    if (pStates == (int *)0x0) {
      return 0;
    }
    uVar8 = *pStates;
    if (uVar8 == 0) {
      return 0;
    }
    pComponent->dwNumStates = uVar8;
    if (pStates[1] != 0) {
      piVar2 = (int *)(*(code *)g_pSvcChore->pAlloc)
                                (uVar8 << 2,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xaf4);
      pComponent->pStateValues = piVar2;
      piVar11 = (int *)pStates[1];
      for (uVar8 = pComponent->dwNumStates & 0x3fffffff; uVar8 != 0; uVar8 = uVar8 - 1) {
        *piVar2 = *piVar11;
        piVar11 = piVar11 + 1;
        piVar2 = piVar2 + 1;
      }
      for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
        *(char *)piVar2 = (char)*piVar11;
        piVar11 = (int *)((int)piVar11 + 1);
        piVar2 = (int *)((int)piVar2 + 1);
      }
    }
    if (pStates[2] != 0) {
      ppcVar3 = (char **)(*(code *)g_pSvcChore->pAlloc)
                                   (pComponent->dwNumStates << 2,
                                    s_C__grimsrc_libs_chore_Costume_c_1001020c,0xafc);
      pComponent->ppStateNames = ppcVar3;
      uVar8 = 0;
      if (pComponent->dwNumStates != 0) {
        do {
          uVar10 = 0xffffffff;
          pcVar4 = (char *)0x0;
          pcVar12 = *(char **)(pStates[2] + uVar8 * 4);
          do {
            if (uVar10 == 0) break;
            uVar10 = uVar10 - 1;
            cVar1 = *pcVar12;
            pcVar12 = pcVar12 + 1;
          } while (cVar1 != '\0');
          uVar10 = ~uVar10;
          if (uVar10 != 0) {
            pcVar4 = (char *)(*(code *)g_pSvcChore->pAlloc)
                                       (uVar10,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xb00);
          }
          pComponent->ppStateNames[uVar8] = pcVar4;
          msvc_strncpy(pComponent->ppStateNames[uVar8],*(undefined4 *)(pStates[2] + uVar8 * 4),
                       uVar10 - 1);
          ppcVar3 = pComponent->ppStateNames + uVar8;
          uVar8 = uVar8 + 1;
          (*ppcVar3)[uVar10 - 1] = '\0';
        } while (uVar8 < pComponent->dwNumStates);
      }
    }
    uVar8 = 0;
    if (pStates[3] != 0) {
      ppCVar5 = (CosStateBitmap **)
                (*(code *)g_pSvcChore->pAlloc)
                          (pComponent->dwNumStates << 2,s_C__grimsrc_libs_chore_Costume_c_1001020c,
                           0xb0b);
      pComponent->apStateBitmaps = ppCVar5;
      if (ppCVar5 == (CosStateBitmap **)0x0) {
        (*(code *)g_pSvcChore->pAssertFail)
                  (IMG_ADDR(0x100104f8),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xb0c);
      }
      uVar10 = 0;
      uVar8 = 0;
      if (pComponent->dwNumStates != 0) {
        iVar9 = 0;
        do {
          pCVar6 = (CosStateBitmap *)
                   (*(code *)g_pSvcChore->pAlloc)
                             (0x14,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xb0e);
          pComponent->apStateBitmaps[uVar10] = pCVar6;
          piVar11 = (int *)(iVar9 + pStates[3]);
          pCVar6 = pComponent->apStateBitmaps[uVar10];
          pCVar6->aDesc[0] = *piVar11;
          pCVar6->aDesc[1] = piVar11[1];
          pCVar6->aDesc[2] = piVar11[2];
          pCVar6->aDesc[3] = piVar11[3];
          if (g_pfnBitmapMunger == (void *)0x0) {
            pComponent->apStateBitmaps[uVar10]->nMunged = 0;
          }
          else if (pStates[4] == 0) {
            iVar7 = (*(code *)g_pfnBitmapMunger)(iVar9 + pStates[3],0);
            pComponent->apStateBitmaps[uVar10]->nMunged = iVar7;
          }
          else {
            iVar7 = (*(code *)g_pfnBitmapMunger)(iVar9 + pStates[3],*(undefined4 *)(pStates[4] + uVar10 * 4));
            pComponent->apStateBitmaps[uVar10]->nMunged = iVar7;
          }
          uVar8 = pComponent->dwNumStates;
          uVar10 = uVar10 + 1;
          iVar9 = iVar9 + 0x10;
        } while (uVar10 < uVar8);
      }
    }
  }
  return uVar8;
}

/* ---- 0x10004090  Cos_InitComponent ---- */
/* Fills a new component record (CosComponent, 0x40 bytes): name (+0, at most 31 characters, else
   nothing is written), tag index (+0x20), the EXE's component data (+0x24), parent component index
   (+0x2c, -1 for a root) and the hash (+0x28): the number of earlier components with the same tag
   and name, so that equal names stay distinct. State fields +0x30..+0x3c are cleared. */

void __cdecl
Cos_InitComponent(Costume *pCostume,CosComponent *pComponent,char *name,int tag,int data,int parent)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  
  uVar3 = 0xffffffff;
  pcVar4 = name;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  if (~uVar3 - 1 < 0x20) {
    msvc_strncpy(pComponent,name,0x1f);
    pComponent->nData = data;
    pComponent->nTag = tag;
    pComponent->aName[0x1f] = '\0';
    pComponent->nParent = parent;
    pComponent->nHash = 0;
    for (iVar2 = Cos_FindComponent(pCostume,g_aComponentTags[tag].nId,0,name); -1 < iVar2;
        iVar2 = Cos_FindComponent(pCostume,g_aComponentTags[pComponent->nTag].nId,iVar2,name)) {
      iVar2 = pComponent->nHash + 1;
      pComponent->nHash = iVar2;
    }
    pComponent->dwNumStates = 0;
    pComponent->pStateValues = (int *)0x0;
    pComponent->ppStateNames = (char **)0x0;
    pComponent->apStateBitmaps = (CosStateBitmap **)0x0;
  }
  return;
}

/* ---- 0x10004140  Cos_InitChore ---- */
/* Resets a chore record (Chore, 0x2c bytes): name '<unnamed>', length (+0x28) 15 ms, no tracks
   (+0x20 count, +0x24 array). */

void __cdecl Cos_InitChore(Chore *pChore)

{
  pChore->dwLength = 0xf;
  pChore->dwNumTracks = 0;
  pChore->pChoreTracks = (ChoreTrack *)0x0;
  msvc_strncpy(pChore,IMG_ADDR(0x10010030),0x1f);
  pChore->aName[0x1f] = '\0';
  return;
}

/* ---- 0x10004170  Cos_FindComponent ---- */
/* Index of the component of the costume with tag id `tagId`, hash `hash` and name `name`
   (_stricmp), or -1. */

int __cdecl Cos_FindComponent(Costume *pCostume,int tagId,int hash,char *name)

{
  int iVar1;
  CosComponent *a;
  uint uVar2;
  
  a = pCostume->pComponents;
  uVar2 = 0;
  if (pCostume->dwNumComponents == 0) {
    return -1;
  }
  while (((a->nHash != hash || (g_aComponentTags[a->nTag].nId != tagId)) ||
         (iVar1 = msvc_stricmp((byte *)a,(byte *)name), iVar1 != 0))) {
    uVar2 = uVar2 + 1;
    a = a + 1;
    if (pCostume->dwNumComponents <= uVar2) {
      return -1;
    }
  }
  return uVar2;
}

/* ---- 0x100041e0  Cos_ReadTagsSection ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Text costume loader, 'section tags': " numtags %d" and one line " %d '%4c' %s %[^\n\r]" per tag
   (index, four-character tag id, type fs / int / float = kind 0 / 1 / 2, name); Cos_FindTag gives
   the registered tag, stored at g_aTagLookups[index]. Hand-written in
   build/overrides_asm_o2_chore.c. */

uint __cdecl Cos_ReadTagsSection(uint file,uint unused2,uint unused3)

{
  unsigned char _stkneg[48];  /* the original frame below the return address */
  uint file_00;
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int in_stack_00000018;
  int in_stack_0000001c;
  uint in_stack_00000050;
  
  file_00 = file;
  iVar1 = Cos_ReadLine(file,g_szParseLine,0x400);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x10010538),&STACK0X(0x00000010));
  if (iVar1 != 1) {
    return 0;
  }
  uVar4 = 0;
  if (in_stack_00000018 == 0) {
    return 1;
  }
  do {
    iVar1 = Cos_ReadLine(file_00,g_szParseLine,0x400);
    if (iVar1 == 0) {
      return 0;
    }
    iVar1 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x10010524),(_stkneg + 32),(_stkneg + 28),
                        (_stkneg + 36),&STACK0X(0x00000000));
    if (iVar1 != 4) {
      return 0;
    }
    iVar2 = msvc_stricmp((_stkneg + 44),(byte *)IMG_ADDR(0x1001019c));
    iVar1 = 0;
    if (iVar2 != 0) {
      iVar1 = msvc_stricmp((byte *)&file,(byte *)IMG_ADDR(0x10010198));
      if (iVar1 == 0) {
        iVar1 = 1;
      }
      else {
        iVar1 = msvc_stricmp((byte *)&unused3,(byte *)IMG_ADDR(0x10010190));
        if (iVar1 != 0) {
          return 0;
        }
        iVar1 = 2;
      }
    }
    uVar3 = Cos_FindTag(unused3,&STACK0X(0x00000020),iVar1);
    uVar4 = uVar4 + 1;
    g_aTagLookups[in_stack_0000001c] = uVar3;
  } while (uVar4 < in_stack_00000050);
  return 1;
}
#endif


/* ---- 0x10004320  Cos_FindTag ---- */
/* Index into g_aComponentTags of the registered tag with id `tagId`, kind `kind` and name `name`
   (_stricmp), or -1. */

int __cdecl Cos_FindTag(int tagId,char *name,int kind)

{
  int iVar1;
  char *a;
  uint uVar2;
  
  uVar2 = 0;
  if (g_dwNumComponentTags != 0) {
    a = g_aComponentTags->aName;
    do {
      if ((((ComponentTag *)(a + -8))->nId == tagId) && (*(int *)(a + -4) == kind)) {
        iVar1 = msvc_stricmp((byte *)a,(byte *)name);
        if (iVar1 == 0) break;
      }
      uVar2 = uVar2 + 1;
      a = a + 0x5c;
    } while (uVar2 < g_dwNumComponentTags);
  }
  if (uVar2 == g_dwNumComponentTags) {
    return -1;
  }
  return uVar2;
}

/* ---- 0x10004390  Cos_ReadComponentsSection ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Text costume loader, 'section components': " numcomponents %d" and one line " %d %d %d %d
   %[^\n\r]" per component (index, tag index, hash, parent index, name). The components are created
   level by level of the parent tree through CosUtil_AddComponent (the tag's Create handler, which
   calls Cos_RegisterComponent back); g_aComponentLookups maps the file's component index to the
   costume's. Hand-written in build/overrides_asm_o2_chore.c. */

uint __cdecl Cos_ReadComponentsSection(uint file,uint handle,uint unused3,uint unused4)

{
  unsigned char _stkneg[32];  /* the original frame below the return address */
  int *name;
  Costume *pCostume;
  int iVar1;
  int iVar2;
  uint *puVar3;
  char *name_00;
  uint uVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  int iStack0000001c;
  uint in_stack_00000024;
  int in_stack_0000002c;
  int in_stack_00000030;
  uint in_stack_00000034;
  int in_stack_00000038;
  int in_stack_00000044;
  uint in_stack_fffffffc;
  
  pCostume = CosUtil_PtrFromHandle(handle);
  iVar1 = Cos_ReadLine(handle,g_szParseLine,0x400);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x10010574),(_stkneg + 20));
  if (iVar1 != 1) {
    return 0;
  }
  uVar7 = 0;
  if (in_stack_fffffffc == 0) {
    iStack0000001c = 0;
    iVar1 = 0;
  }
  else {
    iVar1 = (*(code *)g_pSvcChore->pAlloc)
                      (in_stack_fffffffc << 6,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xbdf);
    iStack0000001c = iVar1;
    if (iVar1 == 0) {
      (*(code *)g_pSvcChore->pAssertFail)
                (IMG_ADDR(0x10010558),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xbe0);
    }
  }
  if (iVar1 == 0) {
    return 0;
  }
  if (g_dwNumComponentLookups < in_stack_fffffffc) {
    g_aComponentLookups =
         (int *)(*(code *)g_pSvcChore->pRealloc)
                          (g_aComponentLookups,in_stack_fffffffc * 4,
                           s_C__grimsrc_libs_chore_Costume_c_1001020c,0xbeb);
    g_dwNumComponentLookups = in_stack_fffffffc;
    in_stack_fffffffc = g_dwNumComponentLookups;
  }
  uVar4 = 0;
  if (in_stack_fffffffc != 0) {
    iVar1 = iVar1 + 0x28;
    do {
      iVar2 = Cos_ReadLine(handle,g_szParseLine,0x400);
      if ((iVar2 == 0) ||
         (iVar2 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x10010544),&STACK0X(0x00000014),&STACK0X(0x0000001c),
                              iVar1,iVar1 + 4), iVar2 != 5)) {
        return 0;
      }
      uVar7 = uVar7 + 1;
      *(uint *)(iVar1 + -8) = g_aTagLookups[in_stack_00000024];
      uVar4 = unused4;
      iVar1 = iVar1 + 0x40;
    } while (uVar7 < unused4);
  }
  if (uVar4 == 0) {
    puVar3 = (uint *)0x0;
    uVar7 = 0;
    puVar8 = (uint *)0x0;
  }
  else {
    uVar7 = in_stack_fffffffc;
    puVar3 = (uint *)(*(code *)g_pSvcChore->pAlloc)
                               (uVar4 * 4,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xc02);
    puVar8 = puVar3;
    in_stack_fffffffc = uVar7;
    if (puVar3 == (uint *)0x0) {
      (*(code *)g_pSvcChore->pAssertFail)
                (IMG_ADDR(0x10010288),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xc03);
      in_stack_fffffffc = uVar7;
    }
  }
  uVar6 = 0;
  file = 0;
  uVar4 = 0;
  if (uVar7 != 0) {
    piVar5 = (int *)(iStack0000001c + 0x2c);
    do {
      iVar1 = *piVar5;
      *puVar3 = 0;
      while (iVar1 != -1) {
        iVar1 = *(int *)(iVar1 * 0x40 + 0x2c + iStack0000001c);
        *puVar3 = *puVar3 + 1;
      }
      if (file <= *puVar3) {
        file = *puVar3;
      }
      uVar6 = uVar6 + 1;
      puVar3 = puVar3 + 1;
      piVar5 = piVar5 + 0x10;
      uVar4 = in_stack_fffffffc;
    } while (uVar6 < in_stack_fffffffc);
  }
  unused3 = 0;
  iVar1 = iStack0000001c;
  do {
    uVar7 = 0;
    if (uVar4 != 0) {
      piVar5 = (int *)(iVar1 + 0x2c);
      do {
        if (puVar8[uVar7] == unused3) {
          name = piVar5 + -0xb;
          iStack0000001c =
               Cos_FindComponentWithParent
                         (pCostume,g_aComponentTags[piVar5[-3]].nId,piVar5[-1],(char *)name,*piVar5)
          ;
          uVar4 = in_stack_00000024;
          unused3 = in_stack_00000034;
          if (iStack0000001c < 0) {
            if (*piVar5 < 0) {
              iVar1 = CosUtil_AddComponent
                                (in_stack_00000034,(char *)name,g_aComponentTags[piVar5[-3]].nId,0,0
                                );
            }
            else {
              name_00 = (char *)(*piVar5 * 0x40 + in_stack_00000030);
              in_stack_0000002c =
                   Cos_FindComponent(pCostume,g_aComponentTags[*(int *)(name_00 + 0x20)].nId,
                                     *(int *)(name_00 + 0x28),name_00);
              if (in_stack_0000002c < 0) goto LAB_1000470a;
              iVar1 = pCostume->pComponents[in_stack_0000002c].nTag;
              in_stack_00000038 = iVar1 * 0x17;
              iVar1 = CosUtil_AddComponent
                                (in_stack_00000044,(char *)name,g_aComponentTags[piVar5[-3]].nId,
                                 pCostume->pComponents[in_stack_0000002c].nData,
                                 g_aComponentTags[iVar1].nId);
            }
            if (iVar1 == 0) {
LAB_1000470a:
              (*(code *)g_pSvcChore->pFree)();
              (*(code *)g_pSvcChore->pFree)();
              return 0;
            }
            puVar8 = (uint *)0x100046c7;
            iVar1 = Cos_FindComponent(pCostume,g_aComponentTags[piVar5[-3]].nId,piVar5[-1],
                                      (char *)name);
            g_aComponentLookups[uVar7] = iVar1;
            uVar4 = in_stack_00000024;
            unused3 = in_stack_00000034;
            file = (uint)pCostume;
            if (g_aComponentLookups[uVar7] < 0) goto LAB_1000470a;
          }
        }
        uVar7 = uVar7 + 1;
        piVar5 = piVar5 + 0x10;
        iVar1 = iStack0000001c;
      } while (uVar7 < uVar4);
    }
    unused3 = unused3 + 1;
    if (file < unused3) {
      (*(code *)g_pSvcChore->pFree)(iVar1);
      (*(code *)g_pSvcChore->pFree)(puVar8);
      return 1;
    }
  } while( true );
}
#endif


/* ---- 0x10004770  Cos_FindComponentWithParent ---- */
/* Like Cos_FindComponent, also matching the parent component index (+0x2c): index or -1. Used by
   the loader to find a component that an earlier costume already registered. */

int __cdecl Cos_FindComponentWithParent(Costume *pCostume,int tagId,int hash,char *name,int parent)

{
  int iVar1;
  CosComponent *a;
  uint uVar2;
  
  a = pCostume->pComponents;
  uVar2 = 0;
  if (pCostume->dwNumComponents == 0) {
    return -1;
  }
  while ((((a->nHash != hash || (g_aComponentTags[a->nTag].nId != tagId)) || (a->nParent != parent))
         || (iVar1 = msvc_stricmp((byte *)a,(byte *)name), iVar1 != 0))) {
    uVar2 = uVar2 + 1;
    a = a + 1;
    if (pCostume->dwNumComponents <= uVar2) {
      return -1;
    }
  }
  return uVar2;
}

/* ---- 0x100047f0  Cos_ReadChoresSection ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Text costume loader, 'section chores': " numchores %d", the chore array (Cos_InitChore each) and
   one line " %d %d %d %[^\n\r]" per chore (index, length +0x28, track count +0x20, name); allocates
   the tracks (assert 'pChore->aChoreTracks != NULL'). Hand-written in
   build/overrides_asm_o2_chore.c. */

uint __cdecl Cos_ReadChoresSection(uint file,int costume,uint unused3)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  Chore *pChore;
  int in_stack_00000014;
  int in_stack_00000018;
  uint uStack0000001c;
  
  iVar2 = Cos_ReadLine(file,g_szParseLine,0x400);
  if (iVar2 == 0) {
    return 0;
  }
  puVar1 = (uint *)(in_stack_00000014 + 0x30);
  iVar2 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x100105c0),puVar1);
  if (iVar2 != 1) {
    return 0;
  }
  uVar3 = 0;
  if (*puVar1 == 0) {
    *(undefined4 *)(in_stack_00000014 + 0x34) = 0;
  }
  else {
    iVar2 = (*(code *)g_pSvcChore->pAlloc)
                      (*puVar1 * 0x2c,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xc7e);
    *(int *)(in_stack_00000014 + 0x34) = iVar2;
    if (iVar2 == 0) {
      *puVar1 = 0;
      return 0;
    }
  }
  pChore = *(Chore **)(in_stack_00000014 + 0x34);
  if (*puVar1 != 0) {
    do {
      Cos_InitChore(pChore);
      uVar3 = uVar3 + 1;
      pChore = pChore + 1;
    } while (uVar3 < *puVar1);
  }
  uStack0000001c = 0;
  if (*puVar1 != 0) {
    piVar4 = (int *)(*(int *)(in_stack_00000014 + 0x34) + 0x20);
    while( true ) {
      iVar2 = Cos_ReadLine(in_stack_00000018,g_szParseLine,0x400);
      if (iVar2 == 0) {
        return 0;
      }
      iVar2 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x100105ac),&STACK0X(0x0000001c));
      if (iVar2 != 4) break;
      if (*piVar4 == 0) {
        piVar4[1] = 0;
      }
      else {
        iVar2 = (*(code *)g_pSvcChore->pAlloc)();
        piVar4[1] = iVar2;
        if (iVar2 == 0) {
          (*(code *)g_pSvcChore->pAssertFail)
                    (IMG_ADDR(0x10010588),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xca2);
        }
      }
      uStack0000001c = uStack0000001c + 1;
      piVar4 = piVar4 + 0xb;
      if (*puVar1 <= uStack0000001c) {
        return 1;
      }
    }
    return 0;
  }
  return 1;
}
#endif


/* ---- 0x10004970  Cos_ReadKeysSection ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Text costume loader, 'section keys': per chore " chore %d", per track " %d %d" (file component
   index, translated through g_aComponentLookups, and key count) and per key " %d %d" or, for float
   tags, " %d %f" (time, value); assert 'pCTrack->aKeys != NULL'. Hand-written in
   build/overrides_asm_o2_chore.c. */

uint __cdecl Cos_ReadKeysSection(uint file,int costume)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  uint *puVar6;
  int in_stack_00000018;
  int in_stack_0000001c;
  int *in_stack_00000028;
  int in_stack_0000002c;
  int *piVar7;
  char *pcVar8;
  
  piVar7 = (int *)0x0;
  iVar2 = costume;
  if (*(int *)(costume + 0x30) == 0) {
    return 1;
  }
  do {
    iVar1 = Cos_ReadLine(file,g_szParseLine,0x400);
    if ((iVar1 == 0) ||
       (iVar1 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x10010600),&STACK0X(0x00000000)), iVar1 != 1)) {
      return 0;
    }
    pcVar8 = (char *)0x0;
    piVar4 = *(int **)(*(int *)(iVar2 + 0x34) + 0x24 + costume * 0x2c);
    iVar1 = *(int *)(iVar2 + 0x34) + costume * 0x2c;
    if (*(int *)(iVar1 + 0x20) != 0) {
      puVar6 = (uint *)(piVar4 + 2);
      do {
        uVar5 = 0;
        iVar2 = Cos_ReadLine(in_stack_00000018,g_szParseLine,0x400);
        if (iVar2 == 0) {
          return 0;
        }
        piVar7 = piVar4;
        iVar2 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x100105f8),piVar4,puVar6);
        if (iVar2 != 2) {
          return 0;
        }
        uVar3 = *puVar6;
        *piVar4 = g_aComponentLookups[*piVar4];
        if (uVar3 == 0) {
          puVar6[1] = 0;
        }
        else {
          pcVar8 = (char *)0xcda;
          piVar7 = (int *)0x10004a5d;
          uVar3 = (*(code *)g_pSvcChore->pAlloc)
                            (uVar3 << 3,s_C__grimsrc_libs_chore_Costume_c_1001020c);
          puVar6[1] = uVar3;
          if (uVar3 == 0) {
            pcVar8 = (char *)0xcdb;
            piVar7 = (int *)0x10004a7f;
            (*(code *)g_pSvcChore->pAssertFail)
                      (IMG_ADDR(0x100105d8),s_C__grimsrc_libs_chore_Costume_c_1001020c);
          }
        }
        if (*puVar6 != 0) {
          iVar2 = puVar6[1] + 4;
          uVar3 = puVar6[1];
          do {
            file = uVar3;
            costume = iVar2;
            piVar7 = (int *)0x10004ac7;
            iVar2 = Cos_ReadLine(in_stack_0000002c,g_szParseLine,0x400);
            if (iVar2 == 0) {
              return 0;
            }
            if ((*(int *)(in_stack_0000002c + 4) == 0) || (*(int *)(in_stack_0000002c + 4) == 1)) {
              pcVar8 = g_szParseLine;
              iVar2 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x100105f8));
            }
            else {
              pcVar8 = g_szParseLine;
              iVar2 = msvc_sscanf(g_szParseLine,(char *)IMG_ADDR(0x100105d0));
            }
            if (iVar2 != 2) {
              return 0;
            }
            uVar5 = uVar5 + 1;
            piVar4 = in_stack_00000028;
            iVar2 = costume + 8;
            uVar3 = file + 8;
          } while (uVar5 < *puVar6);
        }
        if (*puVar6 == 0) {
          uVar5 = 0;
        }
        else {
          uVar5 = *(uint *)((puVar6[1] - 8) + *puVar6 * 8);
        }
        puVar6[-1] = uVar5;
        pcVar8 = pcVar8 + 1;
        piVar4 = piVar4 + 4;
        puVar6 = puVar6 + 4;
        iVar2 = in_stack_0000001c;
      } while (pcVar8 < *(char **)(iVar1 + 0x20));
    }
    piVar7 = (int *)((int)piVar7 + 1);
    if (*(int **)(iVar2 + 0x30) <= piVar7) {
      return 1;
    }
  } while( true );
}
#endif


/* ---- 0x10004bb0  Cos_ReadLine ---- */
/* Reads the next meaningful line of a text costume into the buffer (g_szParseLine, 0x400 bytes)
   with the host's fgets (GrimServices +0x3c): lines starting with ';', '#' or a newline are
   skipped, a '#' ends the line (comment), g_nLineNum counts the lines read. Returns 1, 0 at the end
   of the file. */

int __cdecl Cos_ReadLine(int file,char *buf,int size)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  undefined1 *puVar4;
  
  bVar2 = false;
  while( true ) {
    if (size + -1 == 0) {
      return 1;
    }
    iVar3 = (*(code *)g_pSvcChore->pFgets)(file,buf,size + -1);
    if (iVar3 == 0) break;
    g_nLineNum = g_nLineNum + 1;
    cVar1 = *buf;
    if (((cVar1 != ';') && (cVar1 != '#')) && (cVar1 != '\n')) {
      puVar4 = (undefined1 *)msvc_strchr(buf,0x23);
      if (puVar4 != (undefined1 *)0x0) {
        *puVar4 = 0;
      }
      if (*buf != '\0') {
        bVar2 = true;
      }
    }
    if (bVar2) {
      return 1;
    }
  }
  return 0;
}

/* ---- 0x10004c40  Cos_InitChoreInstances ---- */
/* Initialises the chore states of a new costume instance: ChoreInstance i (12 bytes) = {flags 0,
   chore i, time 0}. The first argument (the costume's chore array) is not used. */

void __cdecl Cos_InitChoreInstances(Chore *pChores,ChoreInstance *pChoreInstances,uint numChores)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (numChores != 0) {
    piVar1 = &pChoreInstances->nTime;
    do {
      ((ChoreInstance *)(piVar1 + -2))->dwFlags = 0;
      piVar1[-1] = uVar2;
      *piVar1 = 0;
      uVar2 = uVar2 + 1;
      piVar1 = piVar1 + 3;
    } while (uVar2 < numChores);
  }
  return;
}

/* ---- 0x10004c70  Cos_FreeCostume ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Frees everything a costume owns: each component (Cos_FreeComponent: the tag's Destroy handler and
   the state arrays), the component array, every chore's track keys and tracks, the chore array;
   then marks the costume slot free (+0x38 = 1) without changing g_nCostumes (see
   build/overrides_s1_chore.c). Original static name FreeCostume (libchore.so). */

void __cdecl Cos_FreeCostume(int hCostume)

{
  Costume *pCVar1;
  CosComponent *pComponent;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int in_stack_00000008;
  
  pCVar1 = CosUtil_PtrFromHandle(hCostume);
  uVar3 = 0;
  if (pCVar1->dwNumComponents != 0) {
    iVar5 = 0;
    do {
      pComponent = (CosComponent *)(pCVar1->pComponents->aName + iVar5);
      Cos_FreeComponent(hCostume,g_aComponentTags + pComponent->nTag,pComponent);
      uVar3 = uVar3 + 1;
      iVar5 = iVar5 + 0x40;
    } while (uVar3 < pCVar1->dwNumComponents);
  }
  (*(code *)g_pSvcChore->pFree)(pCVar1->pComponents);
  iVar5 = 0;
  uVar3 = 0;
  if (pCVar1->dwNumChores != 0) {
    do {
      uVar4 = 0;
      pcVar2 = pCVar1->pChores->aName + iVar5;
      if (*(uint *)(pcVar2 + 0x20) != 0) {
        iVar6 = 0;
        do {
          (*(code *)g_pSvcChore->pFree)
                    (*(undefined4 *)((int)&(*(ChoreTrack **)(pcVar2 + 0x24))->pKeys + iVar6));
          uVar4 = uVar4 + 1;
          iVar6 = iVar6 + 0x10;
          pcVar2 = pCVar1->pChores->aName + iVar5;
          hCostume = in_stack_00000008;
        } while (uVar4 < *(uint *)(pCVar1->pChores->aName + iVar5 + 0x20));
      }
      (*(code *)g_pSvcChore->pFree)(*(undefined4 *)(pCVar1->pChores->aName + iVar5 + 0x24));
      uVar3 = uVar3 + 1;
      iVar5 = iVar5 + 0x2c;
    } while (uVar3 < pCVar1->dwNumChores);
  }
  (*(code *)g_pSvcChore->pFree)(pCVar1->pChores);
  iVar5 = Cos_HandleToIndex(hCostume);
  g_aCostumes[iVar5].nFree = 1;
  return;
}
#endif


/* ---- 0x10004d70  Cos_FreeComponent ---- */
/* Frees one component: calls the tag's Destroy handler (ComponentTag +0x34, slot 2: (costume
   handle, tag id, component data +0x24)) and frees the state values, names and bitmaps (+0x34 /
   +0x38 / +0x3c). */

void __cdecl Cos_FreeComponent(int hCostume,ComponentTag *pTag,CosComponent *pComponent)

{
  int iVar1;
  code *pcVar2;
  uint uVar3;
  
  iVar1 = pTag->nKind;
  if (iVar1 == 0) {
    pcVar2 = (code *)pTag->pfnDestroy;
  }
  else {
    if ((iVar1 != 1) && (iVar1 != 2)) {
      (*(code *)g_pSvcChore->pAssertFail)
                (&DAT_10010284,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xe9c);
      goto LAB_10004dc2;
    }
    pcVar2 = (code *)pTag->pfnDestroy;
  }
  if (pcVar2 != (code *)0x0) {
    (*pcVar2)(hCostume,pTag->nId,pComponent->nData);
  }
LAB_10004dc2:
  (*(code *)g_pSvcChore->pFree)(pComponent->pStateValues);
  if (pComponent->ppStateNames != (char **)0x0) {
    uVar3 = 0;
    if (pComponent->dwNumStates != 0) {
      do {
        (*(code *)g_pSvcChore->pFree)(pComponent->ppStateNames[uVar3]);
        uVar3 = uVar3 + 1;
      } while (uVar3 < pComponent->dwNumStates);
    }
    (*(code *)g_pSvcChore->pFree)(pComponent->ppStateNames);
  }
  if (pComponent->apStateBitmaps != (CosStateBitmap **)0x0) {
    uVar3 = 0;
    if (pComponent->dwNumStates != 0) {
      do {
        (*(code *)g_pSvcChore->pFree)(pComponent->apStateBitmaps[uVar3]);
        uVar3 = uVar3 + 1;
      } while (uVar3 < pComponent->dwNumStates);
    }
    (*(code *)g_pSvcChore->pFree)(pComponent->apStateBitmaps);
  }
  return;
}

/* ---- 0x10004e50  Cos_AllocCostumeSlot ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Index of a free costume slot (Costume +0x38 != 0), marked in use; the table g_aCostumes grows by
   8 records when none is free. Hand-written in build/overrides_s1_chore.c (the original's growth
   leaves records undefined after a failed load). */

int __cdecl Cos_AllocCostumeSlot(void)

{
  char *pcVar1;
  Costume *pCVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  iVar3 = 0;
  if (0 < g_nMaxCostumes) {
    piVar5 = &g_aCostumes->nFree;
    do {
      if (*piVar5 != 0) {
        g_aCostumes[iVar3].nFree = 0;
        g_nCostumes = g_nCostumes + 1;
        return iVar3;
      }
      iVar3 = iVar3 + 1;
      piVar5 = piVar5 + 0xf;
    } while (iVar3 < g_nMaxCostumes);
  }
  if (g_nMaxCostumes < g_nCostumes + 1) {
    g_nMaxCostumes = g_nMaxCostumes + 8;
    g_aCostumes = (Costume *)
                  (*(code *)g_pSvcChore->pRealloc)
                            (g_aCostumes,g_nMaxCostumes * 0x3c,
                             s_C__grimsrc_libs_chore_Costume_c_1001020c,0xed0);
    if (g_nCostumes < g_nMaxCostumes) {
      iVar4 = g_nCostumes * 0x3c;
      iVar3 = g_nCostumes;
      do {
        pcVar1 = g_aCostumes->aName + iVar4 + 0x38;
        pcVar1[0] = '\x01';
        pcVar1[1] = '\0';
        pcVar1[2] = '\0';
        pcVar1[3] = '\0';
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + 0x3c;
      } while (iVar3 < g_nMaxCostumes);
    }
  }
  iVar3 = g_nCostumes;
  pCVar2 = g_aCostumes + g_nCostumes;
  g_nCostumes = g_nCostumes + 1;
  pCVar2->nFree = 0;
  return iVar3;
}
#endif


/* ---- 0x10004f30  Cos_AllocTagSlot ---- */
/* Index of the next component tag record (g_dwNumComponentTags++), assert 'numComponentTags + 1 <=
   maxComponentTags' (32). */

uint __cdecl Cos_AllocTagSlot(void)

{
  uint uVar1;
  
  if (g_dwMaxComponentTags < g_dwNumComponentTags + 1) {
    (*(code *)g_pSvcChore->pAssertFail)(IMG_ADDR(0x1001060c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xede)
    ;
  }
  uVar1 = g_dwNumComponentTags;
  g_dwNumComponentTags = g_dwNumComponentTags + 1;
  return uVar1;
}

/* ---- 0x10004f70  Cos_FreeInstanceData ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Releases a costume instance record (CosInstance, 0x14 bytes) that is in use: calls each component
   tag's NewInstance handler (ComponentTag +0x40, slot 5) with create = 0, frees the chore states
   and the instance data array and marks the record free (costume -1, +0x10 = 1). */

void __cdecl Cos_FreeInstanceData(int instIndex)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  Costume *pCVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  CosInstance *pCVar8;
  uint uVar9;
  int unaff_retaddr;
  CosInstance *in_stack_00000008;
  
  pCVar4 = g_aCostumes;
  pCVar8 = g_aCostumeInstances + instIndex;
  iVar1 = pCVar8->nCostume;
  iVar5 = Cos_InstIndexToHandle(instIndex);
  if (pCVar8->nFree == 0) {
    uVar9 = 0;
    if (pCVar4[iVar1].dwNumComponents != 0) {
      piVar6 = &(pCVar4[iVar1].pComponents)->nTag;
      do {
        iVar1 = *piVar6;
        iVar7 = 0;
        iVar2 = g_aComponentTags[iVar1].nKind;
        if (iVar2 == 0) {
          pcVar3 = (code *)g_aComponentTags[iVar1].pfnNewInstance;
joined_r0x10005011:
          if (pcVar3 != (code *)0x0) {
            iVar7 = (*pcVar3)(iVar5,uVar9,0);
          }
        }
        else {
          if ((iVar2 == 1) || (iVar2 == 2)) {
            pcVar3 = (code *)g_aComponentTags[iVar1].pfnNewInstance;
            goto joined_r0x10005011;
          }
          (*(code *)g_pSvcChore->pAssertFail)
                    (&DAT_10010284,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xf13);
        }
        if (iVar7 != 0) {
          in_stack_00000008->pInstanceData[uVar9] = iVar7;
        }
        uVar9 = uVar9 + 1;
        piVar6 = piVar6 + 0x10;
        pCVar8 = in_stack_00000008;
      } while (uVar9 < *(uint *)(unaff_retaddr + 0x28));
    }
    if (pCVar8->pChoreInstances != (ChoreInstance *)0x0) {
      (*(code *)g_pSvcChore->pFree)(pCVar8->pChoreInstances);
    }
    if (pCVar8->pInstanceData != (int *)0x0) {
      (*(code *)g_pSvcChore->pFree)(pCVar8->pInstanceData);
    }
    pCVar8->nCostume = 0;
    pCVar8->pChoreInstances = (ChoreInstance *)0x0;
    pCVar8->nUserData = 0;
    pCVar8->pInstanceData = (int *)0x0;
    pCVar8->nFree = 0;
    pCVar8->nCostume = -1;
    pCVar8->nFree = 1;
  }
  return;
}
#endif


/* ---- 0x10005090  Cos_AllocInstanceSlot ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Index of a free costume instance record (CosInstance +0x10 != 0), marked in use;
   g_aCostumeInstances grows by 8 records when none is free. Hand-written in
   build/overrides_s1_chore.c. */

int __cdecl Cos_AllocInstanceSlot(void)

{
  CosInstance *pCVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  iVar2 = 0;
  if (0 < g_nMaxInstances) {
    piVar4 = &g_aCostumeInstances->nFree;
    do {
      if (*piVar4 != 0) {
        g_aCostumeInstances[iVar2].nFree = 0;
        g_nInstances = g_nInstances + 1;
        return iVar2;
      }
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 5;
    } while (iVar2 < g_nMaxInstances);
  }
  if (g_nMaxInstances < g_nInstances + 1) {
    g_nMaxInstances = g_nMaxInstances + 8;
    g_aCostumeInstances =
         (CosInstance *)
         (*(code *)g_pSvcChore->pRealloc)
                   (g_aCostumeInstances,g_nMaxInstances * 0x14,
                    s_C__grimsrc_libs_chore_Costume_c_1001020c,0xf3a);
    if (g_nInstances < g_nMaxInstances) {
      iVar3 = g_nInstances * 0x14;
      iVar2 = g_nInstances;
      do {
        *(undefined4 *)((int)&g_aCostumeInstances->nFree + iVar3) = 1;
        iVar2 = iVar2 + 1;
        iVar3 = iVar3 + 0x14;
      } while (iVar2 < g_nMaxInstances);
    }
  }
  iVar2 = g_nInstances;
  pCVar1 = g_aCostumeInstances + g_nInstances;
  g_nInstances = g_nInstances + 1;
  pCVar1->nFree = 0;
  return iVar2;
}
#endif


/* ---- 0x10005160  Cos_HandleToIndex ---- */
/* Costume handle (1-based, as the EXE sees it) -> index into g_aCostumes, -1 for 0 or a handle
   above g_nMaxCostumes. */

int __cdecl Cos_HandleToIndex(int hCostume)

{
  if ((hCostume != 0) && (hCostume <= g_nMaxCostumes)) {
    return hCostume + -1;
  }
  return -1;
}

/* ---- 0x10005180  Cos_IndexToHandle ---- */
/* Index into g_aCostumes -> costume handle (index + 1), 0 when out of range. */

int __cdecl Cos_IndexToHandle(int index)

{
  if ((-1 < index) && (index < g_nMaxCostumes)) {
    return index + 1;
  }
  return 0;
}

/* ---- 0x100051a0  Cos_InstHandleToIndex ---- */
/* Costume instance handle (1-based) -> index into g_aCostumeInstances, -1 for 0 or a handle above
   g_nMaxInstances. */

int __cdecl Cos_InstHandleToIndex(int hInst)

{
  if ((hInst != 0) && (hInst <= g_nMaxInstances)) {
    return hInst + -1;
  }
  return -1;
}

/* ---- 0x100051c0  Cos_InstIndexToHandle ---- */
/* Index into g_aCostumeInstances -> instance handle (index + 1), 0 when out of range. */

int __cdecl Cos_InstIndexToHandle(int index)

{
  if ((-1 < index) && (index < g_nMaxInstances)) {
    return index + 1;
  }
  return 0;
}

/* ---- 0x100051e0  Cos_Terminate ---- */
/* Module interface slot 1 (the table Cos_Initialize fills): forgets the host service table and
   clears g_nCosInitialize. Original name (libchore.so). */

void __cdecl Cos_Terminate(void)

{
  g_pSvcChore = (GrimServices *)0x0;
  if (g_nCosInitialize != 0) {
    g_nCosInitialize = 0;
  }
  return;
}

/* ---- 0x10005200  Cos_Startup ---- */
/* Module interface slot 2: allocates the tables (once, g_nCosStartup): 32 costume slots
   (g_aCostumes, 0x3c bytes each, all free), 32 component tag records (g_aComponentTags, 0x5c bytes)
   and 32 costume instance records (g_aCostumeInstances, 0x14 bytes, all free). Returns 0, 1 when
   already started. Original name (libchore.so). */

int __cdecl Cos_Startup(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
  if (g_nCosStartup != 0) {
    return 1;
  }
  g_nCostumes = 0;
  g_nMaxCostumes = 0x20;
  g_aCostumes = (Costume *)
                (*(code *)g_pSvcChore->pAlloc)
                          (0x780,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xf91);
  if (g_aCostumes == (Costume *)0x0) {
    (*(code *)g_pSvcChore->pAssertFail)(IMG_ADDR(0x1001067c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xf92)
    ;
  }
  iVar3 = 0;
  do {
    iVar2 = iVar3 + 0x3c;
    pcVar1 = g_aCostumes->aName + iVar3 + 0x38;
    pcVar1[0] = '\x01';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    iVar3 = iVar2;
  } while (iVar2 < 0x780);
  g_dwNumComponentTags = 0;
  g_dwMaxComponentTags = 0x20;
  g_aComponentTags =
       (ComponentTag *)
       (*(code *)g_pSvcChore->pAlloc)(0xb80,s_C__grimsrc_libs_chore_Costume_c_1001020c,0xf99);
  if (g_aComponentTags == (ComponentTag *)0x0) {
    (*(code *)g_pSvcChore->pAssertFail)(IMG_ADDR(0x1001065c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0xf9a)
    ;
  }
  g_nInstances = 0;
  g_nMaxInstances = 0x20;
  g_aCostumeInstances =
       (CosInstance *)
       (*(code *)g_pSvcChore->pAlloc)(0x280,s_C__grimsrc_libs_chore_Costume_c_1001020c,3999);
  if (g_aCostumeInstances == (CosInstance *)0x0) {
    (*(code *)g_pSvcChore->pAssertFail)(IMG_ADDR(0x10010638),s_C__grimsrc_libs_chore_Costume_c_1001020c,4000);
  }
  iVar3 = 0;
  do {
    iVar2 = iVar3 + 0x14;
    *(undefined4 *)((int)&g_aCostumeInstances->nFree + iVar3) = 1;
    iVar3 = iVar2;
  } while (iVar2 < 0x280);
  g_nCosStartup = 1;
  return 0;
}

/* ---- 0x10005350  Cos_Shutdown ---- */
/* Module interface slot 3: frees the costume, tag, instance and component lookup tables and clears
   the counts and g_nCosStartup. The costumes' own memory is not freed. Original name (libchore.so).
    */

void __cdecl Cos_Shutdown(void)

{
  g_nMaxCostumes = 0;
  g_nCostumes = 0;
  (*(code *)g_pSvcChore->pFree)(g_aCostumes);
  g_dwMaxComponentTags = 0;
  g_dwNumComponentTags = 0;
  (*(code *)g_pSvcChore->pFree)(g_aComponentTags);
  g_nMaxInstances = 0;
  g_nInstances = 0;
  (*(code *)g_pSvcChore->pFree)(g_aCostumeInstances);
  if (g_dwNumComponentLookups != 0) {
    (*(code *)g_pSvcChore->pFree)(g_aComponentLookups);
    g_aComponentLookups = (int *)0x0;
    g_dwNumComponentLookups = 0;
  }
  g_nCosStartup = 0;
  return;
}

/* ---- 0x10005590  Cos_RegisterSaveVerify ---- */
/* Export: installs the save verify hook (g_pfnSaveVerify, asked by Cos_Save for every loaded
   costume) and returns it. */

void * __cdecl Cos_RegisterSaveVerify(void *verify)

{
                    /* 0x5590  60  Cos_RegisterSaveVerify */
  g_pfnSaveVerify = verify;
  return verify;
}
