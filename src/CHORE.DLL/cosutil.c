/* CHORE.DLL :: cosutil.c
 * functions 0x10001110 .. 0x10003100 (24 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10001110  CosUtil_Write ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Export (costume editor): writes `pCostume` as a text costume file: the save hook
   (Cos_RegisterSaveHook) may refuse; then the file is created ('wt+'), the costume renamed after
   the file name, and '# comment', 'costume v0.1', 'section tags' (Cos_CollectUsedTags), 'section
   components', 'section chores' and 'section keys' written with the host's fprintf (GrimServices
   +0x54). A chore with two tracks for one component, a refused save or a file that cannot be
   created return 0; a file name over 32 characters closes the file and returns 0. The result after
   a complete write is a stack slot that only the error paths set (Ghidra: uStack_18). */

int __cdecl CosUtil_Write(char *fileName,Costume *pCostume,char *comment)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  ComponentTag *pCVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  uint *puVar11;
  ChoreTrack *pCVar12;
  char *pcVar13;
  CosComponent *pCVar14;
  Chore *pCVar15;
  ChoreKey *pCVar16;
  #define uStack_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define uStack_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define uStack_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define iStack_1c (*(int *)(_frame + (0x40 - 0x1c)))
  #define iStack_10 (*(int *)(_frame + (0x40 - 0x10)))
  #define uStack_c (*(undefined1 *)(_frame + (0x40 - 0xc)))
  
                    /* 0x1110  24  CosUtil_Write */
  iStack_1c = 1;
  if (pCostume == (Costume *)0x0) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_100101f8),s_C__grimsrc_libs_chore_Costume_c_1001020c);
  }
  uStack_24 = 0;
  if (pCostume->dwNumChores != 0) {
    puVar11 = &pCostume->pChores->dwNumTracks;
    do {
      uVar6 = *puVar11;
      uStack_20 = 0;
      if (uVar6 != 0) {
        iVar10 = 0;
        do {
          uVar7 = 0;
          if (uVar6 != 0) {
            iVar9 = 0;
            do {
              if ((uStack_20 != uVar7) &&
                 (*(int *)((int)&((ChoreTrack *)puVar11[1])->nCompNum + iVar10) ==
                  *(int *)((int)&((ChoreTrack *)puVar11[1])->nCompNum + iVar9))) {
                return 0;
              }
              uVar7 = uVar7 + 1;
              iVar9 = iVar9 + 0x10;
            } while (uVar7 < uVar6);
          }
          uStack_20 = uStack_20 + 1;
          iVar10 = iVar10 + 0x10;
        } while (uStack_20 < uVar6);
      }
      uStack_24 = uStack_24 + 1;
      puVar11 = puVar11 + 0xb;
    } while (uStack_24 < pCostume->dwNumChores);
  }
  uVar6 = Cos_CollectUsedTags(pCostume);
  if (g_pfnSaveHook != (void *)0x0) {
    iVar10 = Cos_IndexToHandle(((int)pCostume - (int)g_aCostumes) / 0x3c);
    iVar10 = (*(code *)g_pfnSaveHook)(fileName,iVar10);
    if (iVar10 == 0) {
      return 0;
    }
  }
  iVar10 = (*(code *)g_pSvcChore->pFopen)(fileName,((unsigned)(uintptr_t)&DAT_100101f4));
  if (iVar10 == 0) {
    return 0;
  }
  iVar9 = msvc_strrchr(fileName,0x5c);
  if (iVar9 == 0) {
    uVar7 = 0xffffffff;
    pcVar13 = fileName;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar2 = *pcVar13;
      pcVar13 = pcVar13 + 1;
    } while (cVar2 != '\0');
    if (0x20 < ~uVar7 - 1) {
      iStack_1c = 0;
      goto LAB_1000167e;
    }
    msvc_strncpy(pCostume,fileName,0x1f);
    pCostume->aName[0x1f] = '\0';
  }
  else {
    uVar7 = 0xffffffff;
    pcVar13 = (char *)(iVar9 + 1);
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar2 = *pcVar13;
      pcVar13 = pcVar13 + 1;
    } while (cVar2 != '\0');
    if (0x20 < ~uVar7 - 1) {
      iStack_1c = 0;
      goto LAB_1000167e;
    }
    msvc_strncpy(pCostume,(char *)(iVar9 + 1),0x1f);
    pCostume->aName[0x1f] = '\0';
  }
  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_100101ec),comment);
  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_100101d8),0,1);
  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_100101c8));
  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_100101b8),uVar6);
  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_100101a0));
  uVar7 = 0;
  if (uVar6 != 0) {
    puVar11 = g_aTagLookups;
    do {
      uVar3 = *puVar11;
      iStack_10 = g_aComponentTags[uVar3].nId;
      uStack_c = 0;
      if (g_aComponentTags[uVar3].nKind == 0) {
        uVar8 = ((unsigned)(uintptr_t)&DAT_1001019c);
      }
      else {
        uVar8 = ((unsigned)(uintptr_t)&DAT_10010198);
        if (g_aComponentTags[uVar3].nKind != 1) {
          uVar8 = ((unsigned)(uintptr_t)&DAT_10010190);
        }
      }
      (*(code *)g_pSvcChore->pFprintf)
                (iVar10,((unsigned)(uintptr_t)&DAT_1001017c),uVar7,&iStack_10,uVar8,g_aComponentTags[uVar3].aName);
      uVar7 = uVar7 + 1;
      puVar11 = puVar11 + 1;
    } while (uVar7 < uVar6);
  }
  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_10010164));
  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_10010150),pCostume->dwNumComponents);
  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_10010130));
  pCVar14 = pCostume->pComponents;
  uStack_28 = 0;
  if (pCostume->dwNumComponents != 0) {
    do {
      uVar7 = 0;
      if (g_aTagLookups[0] != pCVar14->nTag) {
        puVar11 = g_aTagLookups;
        do {
          if (uVar6 <= uVar7) break;
          puVar1 = puVar11 + 1;
          puVar11 = puVar11 + 1;
          uVar7 = uVar7 + 1;
        } while (*puVar1 != pCVar14->nTag);
      }
      if (uVar7 == uVar6) {
        (*(code *)g_pSvcChore->pAssertFail)
                  (((unsigned)(uintptr_t)&DAT_10010120),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x1a9);
      }
      (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_10010108),uStack_28,uVar7,pCVar14->nHash);
      uStack_28 = uStack_28 + 1;
      pCVar14 = pCVar14 + 1;
    } while (uStack_28 < pCostume->dwNumComponents);
  }
  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_100100f4));
  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_100100e4),pCostume->dwNumChores);
  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_100100c8));
  uVar6 = 0;
  pCVar15 = pCostume->pChores;
  if (pCostume->dwNumChores != 0) {
    do {
      uVar7 = pCVar15->dwNumTracks;
      iVar9 = 0;
      if (uVar7 != 0) {
        puVar11 = &pCVar15->pChoreTracks->dwNumKeys;
        do {
          if (*puVar11 != 0) {
            iVar9 = iVar9 + 1;
          }
          puVar11 = puVar11 + 4;
          uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
      }
      (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_100100b4),uVar6,pCVar15->dwLength,iVar9,pCVar15);
      uVar6 = uVar6 + 1;
      pCVar15 = pCVar15 + 1;
    } while (uVar6 < pCostume->dwNumChores);
  }
  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_100100a4));
  uStack_24 = 0;
  pCVar15 = pCostume->pChores;
  if (pCostume->dwNumChores != 0) {
    do {
      (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_10010094),uStack_24,pCVar15);
      pCVar12 = pCVar15->pChoreTracks;
      uStack_20 = 0;
      if (pCVar15->dwNumTracks != 0) {
        do {
          if (pCVar12->dwNumKeys != 0) {
            (*(code *)g_pSvcChore->pFprintf)(iVar10);
            (*(code *)g_pSvcChore->pFprintf)(iVar10);
            (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_10010060),pCVar12->nCompNum,pCVar12->dwNumKeys)
            ;
            pCVar5 = g_aComponentTags;
            pCVar16 = pCVar12->pKeys;
            iVar9 = pCostume->pComponents[pCVar12->nCompNum].nTag;
            uStack_28 = 0;
            if (pCVar12->dwNumKeys != 0) {
              do {
                iVar4 = pCVar5[iVar9].nKind;
                if ((iVar4 == 0) || (iVar4 == 1)) {
                  (*(code *)g_pSvcChore->pFprintf)(iVar10,((unsigned)(uintptr_t)&DAT_10010054),pCVar16->dwTime);
                }
                else if (iVar4 == 2) {
                  (*(code *)g_pSvcChore->pFprintf)
                            (iVar10,((unsigned)(uintptr_t)&DAT_10010048),pCVar16->dwTime,(double)(float)pCVar16->nValue);
                }
                else {
                  (*(code *)g_pSvcChore->pAssertFail)
                            (((unsigned)(uintptr_t)&DAT_10010040),s_C__grimsrc_libs_chore_Costume_c_1001020c);
                }
                uStack_28 = uStack_28 + 1;
                pCVar16 = pCVar16 + 1;
              } while (uStack_28 < pCVar12->dwNumKeys);
            }
            (*(code *)g_pSvcChore->pFprintf)();
          }
          uStack_20 = uStack_20 + 1;
          pCVar12 = pCVar12 + 1;
        } while (uStack_20 < pCVar15->dwNumTracks);
      }
      uStack_24 = uStack_24 + 1;
      pCVar15 = pCVar15 + 1;
    } while (uStack_24 < pCostume->dwNumChores);
  }
LAB_1000167e:
  (*(code *)g_pSvcChore->pFclose)();
  return iStack_1c;
}
#undef iStack_10
#undef iStack_1c
#undef uStack_20
#undef uStack_24
#undef uStack_28
#undef uStack_c

#endif


/* ---- 0x10002020  CosUtil_CompPtrFromHandle ---- */
/* Export: component `compNum` of the costume, 0 when out of range. */

CosComponent * __cdecl CosUtil_CompPtrFromHandle(Costume *pCostume,uint compNum)

{
                    /* 0x2020  8  CosUtil_CompPtrFromHandle */
  if (pCostume->dwNumComponents <= compNum) {
    return (CosComponent *)0x0;
  }
  return pCostume->pComponents + compNum;
}

/* ---- 0x10002040  CosUtil_PtrFromHandle ---- */
/* Export: the costume record of a costume handle (no range check beyond Cos_HandleToIndex). */

Costume * __cdecl CosUtil_PtrFromHandle(int hCostume)

{
  int iVar1;
  
                    /* 0x2040  18  CosUtil_PtrFromHandle */
  iVar1 = Cos_HandleToIndex(hCostume);
  return g_aCostumes + iVar1;
}

/* ---- 0x10002060  CosUtil_RegisterCompNotifier ---- */
/* Export: installs the component notifier (g_pfnCompNotifier: (costume, component, index, added))
   and returns the previous one. */

void * __cdecl CosUtil_RegisterCompNotifier(void *notifier)

{
  void *pvVar1;
  
                    /* 0x2060  21  CosUtil_RegisterCompNotifier */
  pvVar1 = g_pfnCompNotifier;
  g_pfnCompNotifier = notifier;
  return pvVar1;
}

/* ---- 0x10002070  CosUtil_RegisterBitmapMunger ---- */
/* Export: installs the state bitmap munger (g_pfnBitmapMunger) and returns the previous one. */

void * __cdecl CosUtil_RegisterBitmapMunger(void *munger)

{
  void *pvVar1;
  
                    /* 0x2070  20  CosUtil_RegisterBitmapMunger */
  pvVar1 = g_pfnBitmapMunger;
  g_pfnBitmapMunger = munger;
  return pvVar1;
}

/* ---- 0x10002260  CosUtil_DeleteComponent ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Export (costume editor): deletes component `compNum` and all its descendants: the hashes of later
   components with the same tag and name are renumbered, the component array is compacted and the
   parent indices remapped, the chore tracks of the deleted components and their keys are freed, and
   the component notifier is told about each deleted one. Returns 1, 0 for a bad costume or index.
    */

int __cdecl CosUtil_DeleteComponent(uint hCostume,uint compNum)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  Costume *pCostume;
  int *piVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  CosComponent *pCVar6;
  ChoreTrack *pCVar7;
  int *piVar8;
  uint *puVar9;
  int iVar10;
  uint uVar11;
  ChoreTrack *pCVar12;
  int iVar13;
  char *pcVar14;
  uint uVar15;
  ChoreTrack **ppCVar16;
  #define piStack_c (*(int **)(_frame + (0x20 - 0xc)))
  
                    /* 0x2260  15  CosUtil_DeleteComponent */
  pCostume = CosUtil_PtrFromHandle(hCostume);
  if ((pCostume == (Costume *)0x0) || (pCostume->dwNumComponents <= compNum)) {
    return 0;
  }
  piVar2 = (int *)(*(code *)g_pSvcChore->pAlloc)
                            (pCostume->dwNumComponents * 4,
                             s_C__grimsrc_libs_chore_Costume_c_1001020c,0x539);
  uVar3 = 0;
  piVar8 = piVar2;
  if (pCostume->dwNumComponents != 0) {
    do {
      *piVar8 = 0;
      uVar3 = uVar3 + 1;
      piVar8 = piVar8 + 1;
    } while (uVar3 < pCostume->dwNumComponents);
  }
  puVar4 = (uint *)(*(code *)g_pSvcChore->pAlloc)
                             (pCostume->dwNumComponents << 2,
                              s_C__grimsrc_libs_chore_Costume_c_1001020c,0x53e);
  uVar3 = 0;
  puVar9 = puVar4;
  if (pCostume->dwNumComponents != 0) {
    do {
      *puVar9 = uVar3;
      uVar3 = uVar3 + 1;
      puVar9 = puVar9 + 1;
    } while (uVar3 < pCostume->dwNumComponents);
  }
  hCostume = 0;
  piVar2[compNum] = 1;
  puVar4[compNum] = 0xffffffff;
  if (pCostume->dwNumComponents != 0) {
    iVar13 = 0;
    puVar9 = puVar4;
    do {
      bVar1 = false;
      for (iVar10 = *(int *)(pCostume->pComponents->aName + iVar13 + 0x2c); iVar10 != -1;
          iVar10 = pCostume->pComponents[iVar10].nParent) {
        if (piVar2[iVar10] != 0) {
          bVar1 = true;
          break;
        }
      }
      if (bVar1) {
        *(undefined4 *)(((int)piVar2 - (int)puVar4) + (int)puVar9) = 1;
        *puVar9 = 0xffffffff;
      }
      hCostume = hCostume + 1;
      iVar13 = iVar13 + 0x40;
      puVar9 = puVar9 + 1;
    } while (hCostume < pCostume->dwNumComponents);
  }
  iVar13 = 0;
  hCostume = 0;
  piStack_c = piVar2;
  if (pCostume->dwNumComponents != 0) {
    do {
      if (*piStack_c != 0) {
        pcVar14 = pCostume->pComponents->aName + iVar13;
        iVar10 = *(int *)(pcVar14 + 0x28);
        iVar5 = Cos_FindComponent(pCostume,g_aComponentTags[*(int *)(pcVar14 + 0x20)].nId,iVar10 + 1
                                  ,pcVar14);
        iVar10 = iVar10 + 2;
        while (-1 < iVar5) {
          piVar8 = &pCostume->pComponents[iVar5].nHash;
          *piVar8 = *piVar8 + -1;
          iVar5 = Cos_FindComponent(pCostume,g_aComponentTags[*(int *)(pcVar14 + 0x20)].nId,iVar10,
                                    pcVar14);
          iVar10 = iVar10 + 1;
        }
      }
      hCostume = hCostume + 1;
      iVar13 = iVar13 + 0x40;
      piStack_c = piStack_c + 1;
    } while (hCostume < pCostume->dwNumComponents);
  }
  iVar13 = 0;
  uVar3 = 0;
  if (pCostume->dwNumComponents != 0) {
    hCostume = 0;
    piVar8 = piVar2;
    do {
      iVar13 = iVar13 + (uint)(*piVar8 != 0);
      if ((*piVar8 == 0) && (iVar13 != 0)) {
        *(uint *)(((int)puVar4 - (int)piVar2) + (int)piVar8) = uVar3 - iVar13;
        pcVar14 = pCostume->pComponents->aName + hCostume;
        pCVar6 = pCostume->pComponents + (uVar3 - iVar13);
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          *(undefined4 *)pCVar6->aName = *(undefined4 *)pcVar14;
          pcVar14 = pcVar14 + 4;
          pCVar6 = (CosComponent *)(pCVar6->aName + 4);
        }
      }
      uVar3 = uVar3 + 1;
      piVar8 = piVar8 + 1;
      hCostume = hCostume + 0x40;
    } while (uVar3 < pCostume->dwNumComponents);
  }
  uVar3 = pCostume->dwNumComponents;
  pCostume->dwNumComponents = uVar3 - iVar13;
  pCVar6 = (CosComponent *)
           (*(code *)g_pSvcChore->pRealloc)
                     (pCostume->pComponents,(uVar3 - iVar13) * 0x40,
                      s_C__grimsrc_libs_chore_Costume_c_1001020c,0x583);
  pCostume->pComponents = pCVar6;
  uVar15 = 0;
  if (pCostume->dwNumComponents != 0) {
    iVar13 = 0;
    do {
      iVar10 = *(int *)(pCostume->pComponents->aName + iVar13 + 0x2c);
      if (iVar10 != -1) {
        *(uint *)(pCostume->pComponents->aName + iVar13 + 0x2c) = puVar4[iVar10];
      }
      uVar15 = uVar15 + 1;
      iVar13 = iVar13 + 0x40;
    } while (uVar15 < pCostume->dwNumComponents);
  }
  uVar15 = 0;
  if (pCostume->dwNumChores != 0) {
    puVar9 = &pCostume->pChores->dwNumTracks;
    do {
      uVar11 = 0;
      pCVar7 = (ChoreTrack *)puVar9[1];
      if (*puVar9 != 0) {
        do {
          uVar11 = uVar11 + 1;
          pCVar7->nCompNum = puVar4[pCVar7->nCompNum];
          pCVar7 = pCVar7 + 1;
        } while (uVar11 < *puVar9);
      }
      uVar15 = uVar15 + 1;
      puVar9 = puVar9 + 0xb;
    } while (uVar15 < pCostume->dwNumChores);
  }
  hCostume = 0;
  if (pCostume->dwNumChores != 0) {
    ppCVar16 = &pCostume->pChores->pChoreTracks;
    do {
      pCVar7 = *ppCVar16;
      iVar13 = 0;
      uVar15 = 0;
      if (ppCVar16[-1] != (ChoreTrack *)0x0) {
        piStack_c = (int *)0x0;
        do {
          iVar13 = iVar13 + (uint)(pCVar7->nCompNum == -1);
          if (pCVar7->nCompNum == -1) {
            if (pCVar7->dwNumKeys != 0) {
              (*(code *)g_pSvcChore->pFree)(pCVar7->pKeys);
            }
          }
          else if (iVar13 != 0) {
            piVar8 = (int *)((int)&(*ppCVar16)->nCompNum + (int)piStack_c);
            pCVar12 = *ppCVar16 + (uVar15 - iVar13);
            pCVar12->nCompNum = *piVar8;
            pCVar12->dwLastKeyTime = piVar8[1];
            pCVar12->dwNumKeys = piVar8[2];
            pCVar12->pKeys = (ChoreKey *)piVar8[3];
          }
          uVar15 = uVar15 + 1;
          piStack_c = (int *)((int)piStack_c + 0x10);
          pCVar7 = pCVar7 + 1;
        } while (uVar15 < ppCVar16[-1]);
      }
      uVar15 = (uint)ppCVar16[-1];
      ppCVar16[-1] = (ChoreTrack *)(uVar15 - iVar13);
      pCVar7 = (ChoreTrack *)
               (*(code *)g_pSvcChore->pRealloc)
                         (*ppCVar16,(uVar15 - iVar13) * 0x10,
                          s_C__grimsrc_libs_chore_Costume_c_1001020c,0x5be);
      *ppCVar16 = pCVar7;
      hCostume = hCostume + 1;
      ppCVar16 = ppCVar16 + 0xb;
    } while (hCostume < pCostume->dwNumChores);
  }
  if (g_pfnCompNotifier != (void *)0x0) {
    iVar13 = 0;
    uVar15 = 0;
    piVar8 = piVar2;
    if (uVar3 != 0) {
      do {
        if (*piVar8 != 0) {
          (*(code *)g_pfnCompNotifier)(pCostume,0,uVar15 - iVar13,0);
          iVar13 = iVar13 + 1;
        }
        uVar15 = uVar15 + 1;
        piVar8 = piVar8 + 1;
      } while (uVar15 < uVar3);
    }
  }
  (*(code *)g_pSvcChore->pFree)(piVar2);
  (*(code *)g_pSvcChore->pFree)(puVar4);
  return 1;
}
#undef piStack_c

#endif


/* ---- 0x100026a0  CosUtil_AdjustComponent ---- */
/* Export (costume editor): calls the Edit handler (ComponentTag +0x3c, slot 4) of component
   `compNum` with (&data, name, 32). */

int __cdecl CosUtil_AdjustComponent(Costume *pCostume,uint compNum)

{
  int iVar1;
  CosComponent *pCVar2;
  int iVar3;
  
                    /* 0x26a0  6  CosUtil_AdjustComponent */
  if (pCostume == (Costume *)0x0) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x5df)
    ;
  }
  if (pCostume->dwNumComponents <= compNum) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_10010320),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x5e0)
    ;
  }
  pCVar2 = pCostume->pComponents + compNum;
  iVar3 = pCVar2->nTag;
  iVar1 = g_aComponentTags[iVar3].nKind;
  if ((iVar1 != 0) && (iVar1 != 1)) {
    if (iVar1 == 2) {
      iVar3 = (*(code *)g_aComponentTags[iVar3].pfnEdit)(&pCVar2->nData,pCVar2,0x20);
      return iVar3;
    }
    return (int)pCostume;
  }
  iVar3 = (*(code *)g_aComponentTags[iVar3].pfnEdit)(&pCVar2->nData,pCVar2,0x20);
  return iVar3;
}

/* ---- 0x10002740  CosUtil_ComponentHasAdjuster ---- */
/* Export (costume editor): 1 when the component's tag has an Edit handler (ComponentTag +0x3c). */

int __cdecl CosUtil_ComponentHasAdjuster(Costume *pCostume,uint compNum)

{
  int iVar1;
  int iVar2;
  
                    /* 0x2740  9  CosUtil_ComponentHasAdjuster */
  if (pCostume == (Costume *)0x0) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x604)
    ;
  }
  if (pCostume->dwNumComponents <= compNum) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_10010320),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x605)
    ;
  }
  iVar1 = pCostume->pComponents[compNum].nTag;
  iVar2 = g_aComponentTags[iVar1].nKind;
  if ((((iVar2 != 0) || (g_aComponentTags[iVar1].pfnEdit == (undefined *)0x0)) &&
      ((iVar2 != 1 || (g_aComponentTags[iVar1].pfnEdit == (undefined *)0x0)))) &&
     ((iVar2 != 2 || (g_aComponentTags[iVar1].pfnEdit == (undefined *)0x0)))) {
    return 0;
  }
  return 1;
}

/* ---- 0x100027e0  CosUtil_AddComponent ---- */
/* Export: adds a component through the Create handler (ComponentTag +0x30, slot 1) of tag `tagId`:
   (costume, tag id, parent data, parent tag id, name); the handler builds the EXE's data and calls
   Cos_RegisterComponent. Returns 1 on success. */

int __cdecl CosUtil_AddComponent(int hCostume,char *name,int tagId,int parentData,int parentTagId)

{
  ComponentTag *pCVar1;
  code *pcVar2;
  int iVar3;
  uint uVar4;
  
                    /* 0x27e0  2  CosUtil_AddComponent */
  uVar4 = 0;
  pCVar1 = g_aComponentTags;
  if (g_dwNumComponentTags != 0) {
    do {
      if (pCVar1->nId == tagId) break;
      uVar4 = uVar4 + 1;
      pCVar1 = pCVar1 + 1;
    } while (uVar4 < g_dwNumComponentTags);
  }
  if (uVar4 == g_dwNumComponentTags) {
    return 0;
  }
  iVar3 = pCVar1->nKind;
  if (iVar3 == 0) {
    pcVar2 = (code *)pCVar1->pfnCreate;
    if (pcVar2 == (code *)0x0) {
      return 0;
    }
  }
  else {
    if ((iVar3 != 1) && (iVar3 != 2)) {
      (*(code *)g_pSvcChore->pAssertFail)
                (&DAT_10010284,s_C__grimsrc_libs_chore_Costume_c_1001020c,0x652);
      return (uint)(name != (char *)0x0);
    }
    pcVar2 = (code *)pCVar1->pfnCreate;
    if (pcVar2 == (code *)0x0) {
      return 0;
    }
  }
  iVar3 = (*pcVar2)(hCostume,tagId,parentData,parentTagId,name);
  return (uint)(iVar3 != 0);
}

/* ---- 0x10002880  CosUtil_AddChore ---- */
/* Export (costume editor): appends an empty chore (Cos_InitChore) and returns its index. */

int __cdecl CosUtil_AddChore(Costume *pCostume)

{
  Chore *pCVar1;
  uint uVar2;
  
                    /* 0x2880  1  CosUtil_AddChore */
  if (pCostume == (Costume *)0x0) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x668)
    ;
  }
  uVar2 = pCostume->dwNumChores + 1;
  pCostume->dwNumChores = uVar2;
  pCVar1 = (Chore *)(*(code *)g_pSvcChore->pRealloc)
                              (pCostume->pChores,uVar2 * 0x2c,
                               s_C__grimsrc_libs_chore_Costume_c_1001020c,0x66c);
  pCostume->pChores = pCVar1;
  Cos_InitChore(pCVar1 + (pCostume->dwNumChores - 1));
  return pCostume->dwNumChores - 1;
}

/* ---- 0x100028f0  CosUtil_DeleteChore ---- */
/* Export (costume editor): deletes chore `choreNum` with its tracks and keys and shifts the later
   chores down; returns the reallocated chore array. */

Chore * __cdecl CosUtil_DeleteChore(Costume *pCostume,uint choreNum)

{
  Chore *pCVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
                    /* 0x28f0  14  CosUtil_DeleteChore */
  if ((pCostume == (Costume *)0x0) || (pCostume->dwNumChores <= choreNum)) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_10010364),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x67d)
    ;
  }
  pCVar1 = pCostume->pChores + choreNum;
  uVar2 = pCostume->pChores[choreNum].dwNumTracks;
  if (uVar2 != 0) {
    uVar3 = 0;
    if (uVar2 != 0) {
      iVar4 = 0;
      do {
        if (*(int *)((int)&pCVar1->pChoreTracks->dwNumKeys + iVar4) != 0) {
          (*(code *)g_pSvcChore->pFree)(*(undefined4 *)((int)&pCVar1->pChoreTracks->pKeys + iVar4));
        }
        uVar3 = uVar3 + 1;
        iVar4 = iVar4 + 0x10;
      } while (uVar3 < pCVar1->dwNumTracks);
    }
    (*(code *)g_pSvcChore->pFree)(pCVar1->pChoreTracks);
  }
  if (choreNum < pCostume->dwNumChores - 1) {
    msvc_memmove(pCVar1,pCVar1 + 1,pCostume->dwNumChores * 0x2c + (choreNum + 1) * -0x2c);
  }
  uVar2 = pCostume->dwNumChores - 1;
  pCostume->dwNumChores = uVar2;
  pCVar1 = (Chore *)(*(code *)g_pSvcChore->pRealloc)
                              (pCostume->pChores,uVar2 * 0x2c,
                               s_C__grimsrc_libs_chore_Costume_c_1001020c,0x697);
  pCostume->pChores = pCVar1;
  return pCVar1;
}

/* ---- 0x100029e0  CosUtil_SetChoreLength ---- */
/* Export: sets the length of chore `choreNum` (ms); when it shrinks, keys after the old length are
   dropped from every track. Returns the chore. */

Chore * __cdecl CosUtil_SetChoreLength(Costume *pCostume,uint choreNum,uint length)

{
  uint uVar1;
  Chore *pCVar2;
  ChoreKey *pCVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  
                    /* 0x29e0  22  CosUtil_SetChoreLength */
  if ((pCostume == (Costume *)0x0) || (pCostume->dwNumChores <= choreNum)) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_10010364),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x6a3)
    ;
  }
  pCVar2 = pCostume->pChores + choreNum;
  if (length <= pCostume->pChores[choreNum].dwLength) {
    uVar4 = 0;
    if (pCVar2->dwNumTracks != 0) {
      puVar6 = &pCVar2->pChoreTracks->dwNumKeys;
      do {
        uVar1 = *puVar6;
        uVar5 = 0;
        if (uVar1 != 0) {
          pCVar3 = (ChoreKey *)puVar6[1];
          do {
            if (pCVar2->dwLength < pCVar3->dwTime) break;
            uVar5 = uVar5 + 1;
            pCVar3 = pCVar3 + 1;
          } while (uVar5 < uVar1);
        }
        if (uVar5 < uVar1) {
          pCVar3 = (ChoreKey *)
                   (*(code *)g_pSvcChore->pRealloc)
                             ((ChoreKey *)puVar6[1],uVar5 * 8,
                              s_C__grimsrc_libs_chore_Costume_c_1001020c,0x6b6);
          puVar6[1] = (uint)pCVar3;
          *puVar6 = uVar5;
        }
        uVar4 = uVar4 + 1;
        puVar6 = puVar6 + 4;
        pCVar2 = pCostume->pChores + choreNum;
      } while (uVar4 < pCVar2->dwNumTracks);
    }
  }
  pCostume->pChores[choreNum].dwLength = length;
  return pCVar2;
}

/* ---- 0x10002ab0  CosUtil_NameChore ---- */
/* Export (costume editor): renames chore `choreNum` (at most 31 characters, spaces become '_'). */

char * __cdecl CosUtil_NameChore(Costume *pCostume,int choreNum,char *name)

{
  char cVar1;
  Chore *pCVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  
                    /* 0x2ab0  17  CosUtil_NameChore */
  if (pCostume == (Costume *)0x0) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x6c6)
    ;
  }
  uVar3 = 0xffffffff;
  pCVar2 = (Chore *)0x0;
  pcVar6 = name;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  iVar4 = ~uVar3 - 1;
  if (iVar4 < 0x20) {
    msvc_strncpy(pCostume->pChores + choreNum,name,0x1f);
    pCVar2 = pCostume->pChores;
    iVar5 = 0;
    pCVar2[choreNum].aName[0x1f] = '\0';
    if (0 < iVar4) {
      do {
        pCVar2 = (Chore *)(pCostume->pChores[choreNum].aName + iVar5);
        if (pCostume->pChores[choreNum].aName[iVar5] == ' ') {
          pCVar2->aName[0] = '_';
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < iVar4);
    }
  }
  return pCVar2->aName;
}

/* ---- 0x10002b40  CosUtil_DeleteKey ---- */
/* Export (costume editor): deletes the key at `time` from the track of component `compNum` in chore
   `choreNum`. Returns 1 when one was deleted. */

int __cdecl CosUtil_DeleteKey(Costume *pCostume,uint choreNum,uint compNum,int time)

{
  uint uVar1;
  uint uVar2;
  ChoreKey *pCVar3;
  ChoreTrack *pCVar4;
  
                    /* 0x2b40  16  CosUtil_DeleteKey */
  if (((pCostume == (Costume *)0x0) || (pCostume->dwNumChores <= choreNum)) ||
     (pCostume->dwNumComponents <= compNum)) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_100103b0),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x6e5)
    ;
  }
  pCVar4 = pCostume->pChores[choreNum].pChoreTracks;
  uVar1 = 0;
  uVar2 = pCostume->pChores[choreNum].dwNumTracks;
  if (uVar2 != 0) {
    do {
      if (pCVar4->nCompNum == compNum) break;
      uVar1 = uVar1 + 1;
      pCVar4 = pCVar4 + 1;
    } while (uVar1 < uVar2);
  }
  if (uVar1 != uVar2) {
    pCVar3 = pCVar4->pKeys;
    uVar2 = 0;
    if (pCVar4->dwNumKeys != 0) {
      do {
        if (pCVar3->dwTime == time) {
          msvc_memmove(pCVar3,pCVar4->pKeys + uVar2 + 1,
                       ((uVar2 + 1) * 0x1fffffff + pCVar4->dwNumKeys) * 8);
          uVar2 = pCVar4->dwNumKeys - 1;
          pCVar4->dwNumKeys = uVar2;
          if (uVar2 == 0) {
            (*(code *)g_pSvcChore->pFree)(pCVar4->pKeys);
            pCVar4->pKeys = (ChoreKey *)0x0;
            return 1;
          }
          pCVar3 = (ChoreKey *)
                   (*(code *)g_pSvcChore->pRealloc)
                             (pCVar4->pKeys,uVar2 * 8,s_C__grimsrc_libs_chore_Costume_c_1001020c,
                              0x704);
          pCVar4->pKeys = pCVar3;
          return 1;
        }
        uVar2 = uVar2 + 1;
        pCVar3 = pCVar3 + 1;
      } while (uVar2 < pCVar4->dwNumKeys);
      return 0;
    }
  }
  return 0;
}

/* ---- 0x10002c50  CosUtil_QueryValueAtTime ---- */
/* Export: the key of component `compNum` in chore `choreNum` that is in effect at `time` (the key
   at that time, else the last one before it), 0 for none. */

ChoreKey * __cdecl CosUtil_QueryValueAtTime(Costume *pCostume,uint choreNum,uint compNum,uint time)

{
  uint uVar1;
  ChoreKey *pCVar2;
  uint uVar3;
  ChoreKey *pCVar4;
  ChoreTrack *pCVar5;
  
                    /* 0x2c50  19  CosUtil_QueryValueAtTime */
  if (((pCostume == (Costume *)0x0) || (pCostume->dwNumChores <= choreNum)) ||
     (pCostume->dwNumComponents <= compNum)) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_100103b0),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x722)
    ;
  }
  pCVar5 = pCostume->pChores[choreNum].pChoreTracks;
  uVar3 = 0;
  uVar1 = pCostume->pChores[choreNum].dwNumTracks;
  if (uVar1 != 0) {
    do {
      if (pCVar5->nCompNum == compNum) break;
      uVar3 = uVar3 + 1;
      pCVar5 = pCVar5 + 1;
    } while (uVar3 < uVar1);
  }
  if (uVar3 != uVar1) {
    pCVar2 = pCVar5->pKeys;
    uVar1 = pCVar5->dwNumKeys;
    uVar3 = 0;
    pCVar4 = pCVar2;
    if (uVar1 != 0) {
      do {
        if (pCVar4->dwTime == time) {
          return pCVar4;
        }
        if (time <= pCVar4->dwTime) {
          if (uVar3 == 0) {
            return (ChoreKey *)0x0;
          }
          return pCVar2 + (uVar3 - 1);
        }
        uVar3 = uVar3 + 1;
        pCVar4 = pCVar4 + 1;
      } while (uVar3 < uVar1);
    }
    if (uVar1 != 0) {
      return pCVar2 + (uVar1 - 1);
    }
  }
  return (ChoreKey *)0x0;
}

/* ---- 0x10002cf0  CosUtil_AddFSKey ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Export (costume editor): adds or replaces a key of a state-based component (Cos_AddKey); 0 for
   another tag kind. */

int __cdecl CosUtil_AddFSKey(Costume *pCostume,uint choreNum,int compNum,uint time,int value)

{
  ChoreKey *pCVar1;
  
                    /* 0x2cf0  3  CosUtil_AddFSKey */
  if (g_aComponentTags[pCostume->pComponents[compNum].nTag].nKind != 0) {
    return 0;
  }
  pCVar1 = Cos_AddKey(pCostume,choreNum,compNum,time);
  if (pCVar1 == (ChoreKey *)0x0) {
    return 0;
  }
  pCVar1->nValue = value;
  return 1;
}
#endif


/* ---- 0x10002d50  CosUtil_AddIntKey ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Export (costume editor): adds or replaces a key of an int component (Cos_AddKey); 0 for another
   tag kind. */

int __cdecl CosUtil_AddIntKey(Costume *pCostume,uint choreNum,int compNum,uint time,int value)

{
  ChoreKey *pCVar1;
  
                    /* 0x2d50  5  CosUtil_AddIntKey */
  if (g_aComponentTags[pCostume->pComponents[compNum].nTag].nKind != 1) {
    return 0;
  }
  pCVar1 = Cos_AddKey(pCostume,choreNum,compNum,time);
  if (pCVar1 == (ChoreKey *)0x0) {
    return 0;
  }
  pCVar1->nValue = value;
  return 1;
}
#endif


/* ---- 0x10002db0  CosUtil_AddFloatKey ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Export (costume editor): adds or replaces a key of a float component (Cos_AddKey; the value is
   stored as its bits); 0 for another tag kind. */

int __cdecl CosUtil_AddFloatKey(Costume *pCostume,uint choreNum,int compNum,uint time,int value)

{
  ChoreKey *pCVar1;
  
                    /* 0x2db0  4  CosUtil_AddFloatKey */
  if (g_aComponentTags[pCostume->pComponents[compNum].nTag].nKind != 2) {
    return 0;
  }
  pCVar1 = Cos_AddKey(pCostume,choreNum,compNum,time);
  if (pCVar1 == (ChoreKey *)0x0) {
    return 0;
  }
  pCVar1->nValue = value;
  return 1;
}
#endif


/* ---- 0x10002e10  CosUtil_CountComponents ---- */
/* Export: number of components of the costume. */

uint __cdecl CosUtil_CountComponents(Costume *pCostume)

{
                    /* 0x2e10  12  CosUtil_CountComponents */
  if (pCostume == (Costume *)0x0) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x789)
    ;
  }
  return pCostume->dwNumComponents;
}

/* ---- 0x10002e40  CosUtil_ComponentInfo ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Export: tag id, component data, parent index and tag kind of component `index`; returns the
   component record (the EXE uses it). Hand-written in build/overrides_logic_chore.c. */

int __cdecl
CosUtil_ComponentInfo(int cos,uint index,int *outTag,undefined4 *outA,undefined4 *outB,int *outKind)

{
  ComponentTag *pCVar1;
  int iVar2;
  
                    /* 0x2e40  10  CosUtil_ComponentInfo */
  if (cos == 0) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_1001034c),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x797)
    ;
  }
  if (*(uint *)(cos + 0x28) <= index) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_10010444),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x798)
    ;
  }
  iVar2 = *(int *)(cos + 0x2c) + index * 0x40;
  pCVar1 = g_aComponentTags + *(int *)(iVar2 + 0x20);
  if (outTag != (int *)0x0) {
    *outTag = pCVar1->nId;
  }
  if (outA != (undefined4 *)0x0) {
    *outA = *(undefined4 *)(iVar2 + 0x24);
  }
  if (outKind != (int *)0x0) {
    *outKind = pCVar1->nKind;
  }
  if (outB != (undefined4 *)0x0) {
    *outB = *(undefined4 *)(iVar2 + 0x2c);
  }
  return iVar2;
}
#endif


/* ---- 0x10002fa0  CosUtil_CountChores ---- */
/* Export: number of chores of the costume. */

uint __cdecl CosUtil_CountChores(Costume *pCostume)

{
                    /* 0x2fa0  11  CosUtil_CountChores */
  return pCostume->dwNumChores;
}

/* ---- 0x100030b0  CosUtil_ChoreName ---- */
/* Export: name of chore `choreNum` of the costume. */

char * __cdecl CosUtil_ChoreName(Costume *pCostume,uint choreNum)

{
                    /* 0x30b0  7  CosUtil_ChoreName */
  if (pCostume->dwNumChores <= choreNum) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_10010498),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x80d)
    ;
  }
  return pCostume->pChores[choreNum].aName;
}

/* ---- 0x100030f0  CosUtil_CountTags ---- */
/* Export: number of registered component tags. */

uint __cdecl CosUtil_CountTags(void)

{
                    /* 0x30f0  13  CosUtil_CountTags */
  return g_dwNumComponentTags;
}

/* ---- 0x10003100  CosUtil_TagInfo ---- */
/* Export: name of registered tag `whichTag` and its id through outTagId (assert 'whichTag >= 0 &&
   whichTag < numComponentTags'). */

char * __cdecl CosUtil_TagInfo(uint whichTag,int *outTagId)

{
                    /* 0x3100  23  CosUtil_TagInfo */
  if (g_dwNumComponentTags <= whichTag) {
    (*(code *)g_pSvcChore->pAssertFail)(((unsigned)(uintptr_t)&DAT_100104c8),s_C__grimsrc_libs_chore_Costume_c_1001020c,0x81f)
    ;
  }
  if (outTagId != (int *)0x0) {
    *outTagId = g_aComponentTags[whichTag].nId;
  }
  return g_aComponentTags[whichTag].aName;
}
