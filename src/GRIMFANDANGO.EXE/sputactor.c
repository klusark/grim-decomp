/* GRIMFANDANGO.EXE :: sputactor.c
 * functions 0x0048e2c0 .. 0x00490ef0 (7 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048e2c0  sputActor_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

uint __cdecl sputActor_Initialize(uint services,undefined4 *iface)

{
  g_dwSputActHS = services;
  *iface = sputActor_Initialize;
  iface[1] = sputActor_Terminate;
  iface[2] = sputActor_Startup;
  iface[3] = sputActor_Shutdown;
  iface[4] = sputActor_Save;
  iface[5] = sputActor_Restore;
  iface[6] = 0;
  iface[7] = 0;
  g_pTalkingActors[0] = (Actor *)0x0;
  g_dwSputActInitialize = 1;
  g_pTalkingActors[1] = (Actor *)0x0;
  g_pTalkingActors[2] = (Actor *)0x0;
  g_pTalkingActors[3] = (Actor *)0x0;
  return 0;
}

/* ---- 0x0048e330  sputActor_Save ---- */
/* Module interface slot 4 (sputActor): save-game writer, calls the SaveGame_Write callback it is
   handed for every field. Original name sputActor_Save (the remaster's GrimFandango (Linux):
   aligned call in sputActor_Initialize); was sputActor_SaveState. */

uint __cdecl sputActor_Save(code *write)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Actor *actor;
  undefined4 *puVar1;
  ModelComponent *pMVar2;
  void *pvVar3;
  CostumeNode *pCVar4;
  Set *pSVar5;
  int *piVar6;
  Actor *pAVar7;
  int iVar8;
  int *piVar9;
  int iStack_a8;
  #define iStack_a4 (*(int *)(_frame + (0xc0 - 0xa4)))
  #define iStack_a0 (*(int *)(_frame + (0xc0 - 0xa0)))
  #define iStack_9c (*(int *)(_frame + (0xc0 - 0x9c)))
  #define iStack_98 (*(int *)(_frame + (0xc0 - 0x98)))
  #define iStack_94 (*(int *)(_frame + (0xc0 - 0x94)))
  #define iStack_90 (*(int *)(_frame + (0xc0 - 0x90)))
  #define iStack_8c (*(int *)(_frame + (0xc0 - 0x8c)))
  #define uStack_88 (*(uint *)(_frame + (0xc0 - 0x88)))
  #define local_84 (*(uint *)(_frame + (0xc0 - 0x84)))
  #define aiStack_80 (*(int (*)[32])(_frame + (0xc0 - 0x80)))
  
  local_84 = g_nNumActors;
  (*write)(&g_nMaxActors,4);
  (*write)(&local_84,4);
  iStack_94 = 0;
  pAVar7 = g_pActors;
  if (0 < g_nMaxActors) {
    iStack_98 = 0;
    do {
      actor = (Actor *)((int)pAVar7->aPos + iStack_98 + -0xc);
      if (*(int *)(pAVar7->aSetName + iStack_98 + 0x20) != 0) {
        iStack_8c = ((int)actor - (int)pAVar7) / 0xa8;
        (*write)(&iStack_8c,4);
        (*write)((int)actor->pColormapRef + 4,4);
        (*write)(&actor->dwFlags,4);
        (*write)(&actor->dwMoveFlags,4);
        (*write)(actor->aPos,4);
        (*write)(actor->aPos + 1,4);
        (*write)(actor->aPos + 2,4);
        (*write)(actor->aPrevPos,4);
        (*write)(actor->aPrevPos + 1,4);
        (*write)(actor->aPrevPos + 2,4);
        (*write)(actor->aRot,4);
        (*write)(actor->aRot + 1,4);
        (*write)(actor->aRot + 2,4);
        (*write)(&actor->flScale,4);
        (*write)(&actor->nMatrixDirty,4);
        (*write)(actor->aOrient,4);
        (*write)(actor->aOrient + 1,4);
        (*write)(actor->aOrient + 2,4);
        (*write)(actor->aOrient + 3,4);
        (*write)(actor->aOrient + 4,4);
        (*write)(actor->aOrient + 5,4);
        (*write)(actor->aOrient + 6,4);
        (*write)(actor->aOrient + 7,4);
        (*write)(actor->aOrient + 8,4);
        (*write)(actor->aOrient + 9,4);
        (*write)(actor->aOrient + 10,4);
        (*write)(actor->aOrient + 0xb,4);
        (*write)(&actor->nScreenBoxValid,4);
        (*write)(actor->aScreenBox,4);
        (*write)(actor->aScreenBox + 1,4);
        (*write)(actor->aScreenBox + 2,4);
        (*write)(actor->aScreenBox + 3,4);
        (*write)(actor->aSetName,0x20);
        uStack_88 = (uint)(actor->pExtra != (ActorExtra *)0x0);
        (*write)(&uStack_88,4);
        iStack_9c = Actor_CountCostumes(actor);
        (*write)(&iStack_9c,4);
        pCVar4 = actor->pCostumes;
        if (-1 < iStack_9c + -1) {
          piVar6 = aiStack_80 + iStack_9c + -1;
          iVar8 = iStack_9c;
          do {
            *piVar6 = (int)pCVar4;
            pCVar4 = pCVar4->pNext;
            piVar6 = piVar6 + -1;
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
        }
        iStack_a8 = 0;
        if (0 < iStack_9c) {
          piVar6 = aiStack_80;
          do {
            puVar1 = (undefined4 *)*piVar6;
            (*write)(puVar1,4);
            (*write)(puVar1 + 3,0xc);
            (*write)(puVar1 + 6,4);
            (*write)(puVar1 + 7,4);
            (*write)(puVar1 + 8,4);
            (*write)(puVar1 + 9,4);
            (*write)(puVar1 + 10,4);
            (*write)(puVar1 + 0xb,4);
            (*write)(puVar1 + 0xc,4);
            (*write)(puVar1 + 0xd,4);
            (*write)(puVar1 + 0xe,0x40);
            (*write)(puVar1 + 0x1e,4);
            if (puVar1[0x1f] == 0) {
              (**(code **)(g_dwSputActHS + 0x18))
                        (s_Valid_Ref___pCosNode__rCostume___004e9e1c,
                         s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x1c1);
            }
            (*write)(puVar1 + 0x20,4);
            Cos_SaveInstance(*puVar1,write);
            iStack_a8 = iStack_a8 + 1;
            piVar6 = piVar6 + 1;
          } while (iStack_a8 < iStack_9c);
        }
        if (actor->pCostumes != (CostumeNode *)0x0) {
          iStack_a4 = 0;
          for (pMVar2 = actor->pCostumes->pComponents; pMVar2 != (ModelComponent *)0x0;
              pMVar2 = pMVar2->pNext) {
            iStack_a4 = iStack_a4 + 1;
          }
          (*write)(&iStack_a4,4);
          for (pMVar2 = actor->pCostumes->pComponents; pMVar2 != (ModelComponent *)0x0;
              pMVar2 = pMVar2->pNext) {
            (*write)(&pMVar2->nRoot,4);
            (*write)(&pMVar2->nComponentFlags,4);
            (*write)(&pMVar2->nParentNode,4);
            if (pMVar2->pThing->nType == 1) {
              if ((pMVar2->modelRef).nValid == 0) {
                (*g_pStd_HS->pAssertFail)
                          (s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
              }
              (*write)(pMVar2->pThing->pHierarchyExtra,
                       *(int *)((int)(pMVar2->modelRef).pData + 0x54) << 2);
            }
            iStack_a0 = 0;
            if ((pMVar2->pThing == (rdThing *)0x0) ||
               (pvVar3 = pMVar2->pThing->pPuppet, pvVar3 == (void *)0x0)) {
              (*write)(&iStack_a0,4);
            }
            else {
              piVar6 = (int *)((int)pvVar3 + 0x130);
              iVar8 = 6;
              piVar9 = piVar6;
              do {
                if (*piVar9 != 0) {
                  iStack_a0 = iStack_a0 + 1;
                }
                piVar9 = piVar9 + 0x4d;
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
              (*write)(&iStack_a0,4);
              iStack_a8 = 6;
              do {
                if (*piVar6 != 0) {
                  (*write)(*piVar6,0x20);
                  (*write)(piVar6 + -0x48,4);
                  (*write)(piVar6 + -0x47,4);
                  (*write)(piVar6 + -0x4a,4);
                  (*write)(piVar6 + -2,4);
                  (*write)(piVar6 + -1,4);
                  (*write)(piVar6 + -0x44,4);
                  (*write)(piVar6 + -0x43,4);
                }
                piVar6 = piVar6 + 0x4d;
                iStack_a8 = iStack_a8 + -1;
              } while (iStack_a8 != 0);
            }
          }
        }
        pAVar7 = g_pActors;
        if (actor->pExtra != (ActorExtra *)0x0) {
          (*write)(actor->pExtra,4);
          (*write)(actor->pExtra->aLookAt + 1,4);
          (*write)(actor->pExtra->aLookAt + 2,4);
          (*write)(&actor->pExtra->nWalking,4);
          (*write)(&actor->pExtra->nTurning,4);
          (*write)(&actor->pExtra->nResting,4);
          (*write)(&actor->pExtra->flWalkRate,4);
          (*write)(&actor->pExtra->flTurnRate,4);
          (*write)(&actor->pExtra->nAlignTurn,4);
          (*write)(&actor->pExtra->flOffsetYaw,4);
          (*write)(&actor->pExtra->flYawLeft,4);
          (*write)(actor->pExtra->aWaypoint,4);
          (*write)(actor->pExtra->aWaypoint + 1,4);
          (*write)(actor->pExtra->aWaypoint + 2,4);
          (*write)(actor->pExtra->aDest,4);
          (*write)(actor->pExtra->aDest + 1,4);
          (*write)(actor->pExtra->aDest + 2,4);
          (*write)(&actor->pExtra->nPathNodes,4);
          iVar8 = 0;
          do {
            (*write)((int)actor->pExtra->aPath[0] + iVar8,4);
            (*write)((int)actor->pExtra->aPath[0] + iVar8 + 4,4);
            (*write)((int)actor->pExtra->aPath[0] + iVar8 + 8,4);
            iVar8 = iVar8 + 0xc;
          } while (iVar8 < 0x168);
          (*write)(&actor->pExtra->nPathIndex,4);
          (*write)(&actor->pExtra->pPuck,4);
          (*write)(&actor->pExtra->nFollowBoxes,4);
          (*write)(&actor->pExtra->nWalkDominate,4);
          (*write)(&actor->pExtra->flPuckRadius,4);
          (*write)(&actor->pExtra->nTalking,4);
          (*write)(&actor->pExtra->nVoiceSound,4);
          (*write)(&actor->pExtra->nTalkTime,4);
          (*write)(actor->pExtra->aMsgId,0xc);
          (*write)(actor->pExtra->aVoiceFile,0xf);
          (*write)(&actor->pExtra->pText,4);
          (*write)(&actor->pExtra->nLipSync,4);
          (*write)(&actor->pExtra->nActiveShadow,4);
          (*write)(&actor->pExtra->nCollisionMode,4);
          (*write)(&actor->pExtra->flCollisionScale,4);
          (*write)(&actor->pExtra->nCollided,4);
          (*write)(&actor->pExtra->nClipPlaneActive,4);
          (*write)(actor->pExtra->aClipNormal,4);
          (*write)(actor->pExtra->aClipNormal + 1,4);
          (*write)(actor->pExtra->aClipNormal + 2,4);
          (*write)(actor->pExtra->aClipPoint,4);
          (*write)(actor->pExtra->aClipPoint + 1,4);
          (*write)(actor->pExtra->aClipPoint + 2,4);
          (*write)(&actor->pExtra->dwTalkColor,4);
          (*write)(&actor->pExtra->flTimeScale,4);
          (*write)(&actor->pExtra->nInvClipNode,4);
          pSVar5 = sputRoom_GetCurrentRoom();
          if (pSVar5 == (Set *)0x0) {
            sputActor_ResetShadows(actor);
          }
          iStack_a8 = 0x1f8;
          do {
            iVar8 = (int)actor->pExtra->aLookAt + iStack_a8;
            iStack_a4 = 0;
            (*write)(iVar8,4);
            (*write)(iVar8 + 4,4);
            (*write)(iVar8 + 8,4);
            (*write)(iVar8 + 0xc,4);
            (*write)(iVar8 + 0x10,4);
            (*write)(iVar8 + 0x14,4);
            (*write)(iVar8 + 0x18,4);
            (*write)(iVar8 + 0x1c,4);
            (*write)(iVar8 + 0x20,4);
            piVar9 = (int *)(iVar8 + 0x24);
            iVar8 = 0xc;
            piVar6 = piVar9;
            do {
              if (*piVar6 != 0) {
                iStack_a4 = iStack_a4 + 1;
              }
              piVar6 = piVar6 + 1;
              iVar8 = iVar8 + -1;
            } while (iVar8 != 0);
            (*write)(&iStack_a4,4);
            iVar8 = 0xc;
            do {
              if (*piVar9 != 0) {
                (*write)(*piVar9,0x20);
              }
              piVar9 = piVar9 + 1;
              iVar8 = iVar8 + -1;
            } while (iVar8 != 0);
            iStack_a8 = iStack_a8 + 0x54;
            pAVar7 = g_pActors;
          } while (iStack_a8 < 0x3f0);
        }
      }
      iStack_94 = iStack_94 + 1;
      iStack_98 = iStack_98 + 0xa8;
    } while (iStack_94 < g_nMaxActors);
  }
  iStack_90 = -1;
  if (g_pSelectedActor != (Actor *)0x0) {
    iStack_90 = ((int)g_pSelectedActor - (int)pAVar7) / 0xa8;
  }
  (*write)(&iStack_90,4);
  return 0;
}
#undef aiStack_80
#undef iStack_8c
#undef iStack_90
#undef iStack_94
#undef iStack_98
#undef iStack_9c
#undef iStack_a0
#undef iStack_a4
#undef local_84
#undef uStack_88


/* ---- 0x0048ecd0  sputActor_Restore ---- */
/* Module interface slot 5 (sputActor): save-game reader, calls the SaveGame_Read callback it is
   handed; returns non-zero on a short read. Original name sputActor_Restore (the remaster's
   GrimFandango (Linux): the only unmatched caller of rdPuppet_AddTrack; 4 matched neighbours agree,
   2 disagree); was sputActor_RestoreState. */

uint __cdecl sputActor_Restore(code *read)

{
  unsigned char _frame[0x180] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Actor *pAVar1;
  char cVar2;
  ModelComponent *pMVar3;
  void *pvVar4;
  undefined4 *puVar5;
  char *pcVar6;
  void *keyframe;
  Actor **ppAVar7;
  TextObject *pTVar8;
  WalkPlane *pWVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int *piVar13;
  int iVar14;
  Actor *pAVar15;
  char *pcVar16;
  int *piVar17;
  #define iStack_164 (*(int *)(_frame + (0x180 - 0x164)))
  #define pvStack_160 (*(void **)(_frame + (0x180 - 0x160)))
  #define local_15c (*(int *)(_frame + (0x180 - 0x15c)))
  #define iStack_158 (*(int *)(_frame + (0x180 - 0x158)))
  #define iStack_154 (*(int *)(_frame + (0x180 - 0x154)))
  #define iStack_150 (*(int *)(_frame + (0x180 - 0x150)))
  #define iStack_14c (*(int *)(_frame + (0x180 - 0x14c)))
  #define iStack_148 (*(int *)(_frame + (0x180 - 0x148)))
  #define uStack_144 (*(uint *)(_frame + (0x180 - 0x144)))
  #define iStack_140 (*(int *)(_frame + (0x180 - 0x140)))
  #define iStack_13c (*(int *)(_frame + (0x180 - 0x13c)))
  #define uStack_138 (*(uint *)(_frame + (0x180 - 0x138)))
  #define auStack_134 (*(undefined1 (*)[12])(_frame + (0x180 - 0x134)))
  #define iStack_128 (*(int *)(_frame + (0x180 - 0x128)))
  #define iStack_124 (*(int *)(_frame + (0x180 - 0x124)))
  #define iStack_120 (*(int *)(_frame + (0x180 - 0x120)))
  #define fStack_11c (*(float *)(_frame + (0x180 - 0x11c)))
  #define fStack_118 (*(float *)(_frame + (0x180 - 0x118)))
  #define fStack_114 (*(float *)(_frame + (0x180 - 0x114)))
  #define fStack_110 (*(float *)(_frame + (0x180 - 0x110)))
  #define iStack_10c (*(int *)(_frame + (0x180 - 0x10c)))
  #define iStack_108 (*(int *)(_frame + (0x180 - 0x108)))
  #define iStack_104 (*(int *)(_frame + (0x180 - 0x104)))
  #define iStack_100 (*(int *)(_frame + (0x180 - 0x100)))
  #define aiStack_fc (*(int (*)[16])(_frame + (0x180 - 0xfc)))
  #define iStack_bc (*(int *)(_frame + (0x180 - 0xbc)))
  #define RStack_b8 (*(ResRef *)(_frame + (0x180 - 0xb8)))
  #define acStack_80 (*(char (*)[32])(_frame + (0x180 - 0x80)))
  #define acStack_60 (*(char (*)[32])(_frame + (0x180 - 0x60)))
  #define acStack_40 (*(char (*)[64])(_frame + (0x180 - 0x40)))
  
  g_pTalkingActors[0] = (Actor *)0x0;
  g_pTalkingActors[1] = (Actor *)0x0;
  g_pTalkingActors[2] = (Actor *)0x0;
  g_pTalkingActors[3] = (Actor *)0x0;
  iVar14 = 0;
  g_nNumActorsTalking = 0;
  if (0 < g_nMaxActors) {
    iVar12 = 0;
    do {
      sputActor_FreeActor((Actor *)((int)g_pActors->aPos + iVar12 + -0xc));
      iVar14 = iVar14 + 1;
      iVar12 = iVar12 + 0xa8;
    } while (iVar14 < g_nMaxActors);
  }
  (*read)(&local_15c,4);
  if (g_nMaxActors < local_15c) {
    g_pActors = (Actor *)(**(code **)(g_dwSputActHS + 0x28))
                                   (g_pActors,local_15c * 0xa8,
                                    s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x28a);
    pAVar15 = g_pActors + g_nMaxActors;
    for (iVar14 = ((local_15c - g_nMaxActors) * 0x15 & 0x1fffffffU) << 1; iVar14 != 0;
        iVar14 = iVar14 + -1) {
      pAVar15->pColormapRef = (void *)0x0;
      pAVar15 = (Actor *)&pAVar15->dwFlags;
    }
    for (iVar14 = 0; iVar14 != 0; iVar14 = iVar14 + -1) {
      *(undefined1 *)&pAVar15->pColormapRef = 0;
      pAVar15 = (Actor *)((int)&pAVar15->pColormapRef + 1);
    }
    g_nMaxActors = local_15c;
  }
  (*read)(&g_nNumActors,4);
  iStack_150 = 0;
  if (0 < g_nNumActors) {
    do {
      (*read)(&iStack_140,4);
      pAVar15 = g_pActors + iStack_140;
      pAVar1 = g_pActors + iStack_140;
      pAVar15->nInUse = 1;
      if (pAVar1->pColormapRef == (void *)0x0) {
        puVar5 = (undefined4 *)
                 (**(code **)(g_dwSputActHS + 0x20))
                           (0x34,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x29f);
        pAVar15->pColormapRef = puVar5;
        for (iVar14 = 0xd; iVar14 != 0; iVar14 = iVar14 + -1) {
          *puVar5 = 0;
          puVar5 = puVar5 + 1;
        }
      }
      (*read)((int)pAVar15->pColormapRef + 4,4);
      (*read)(&pAVar15->dwFlags,4);
      (*read)(&pAVar15->dwMoveFlags,4);
      (*read)(pAVar15->aPos,4);
      (*read)(pAVar15->aPos + 1,4);
      (*read)(pAVar15->aPos + 2,4);
      (*read)(pAVar15->aPrevPos,4);
      (*read)(pAVar15->aPrevPos + 1,4);
      (*read)(pAVar15->aPrevPos + 2,4);
      (*read)(pAVar15->aRot,4);
      (*read)(pAVar15->aRot + 1,4);
      (*read)(pAVar15->aRot + 2,4);
      (*read)(&pAVar15->flScale,4);
      (*read)(&pAVar15->nMatrixDirty,4);
      pAVar15->nMatrixDirty = 0;
      (*read)(pAVar15->aOrient,4);
      (*read)(pAVar15->aOrient + 1,4);
      (*read)(pAVar15->aOrient + 2,4);
      (*read)(pAVar15->aOrient + 3,4);
      (*read)(pAVar15->aOrient + 4,4);
      (*read)(pAVar15->aOrient + 5,4);
      (*read)(pAVar15->aOrient + 6,4);
      (*read)(pAVar15->aOrient + 7,4);
      (*read)(pAVar15->aOrient + 8,4);
      (*read)(pAVar15->aOrient + 9,4);
      (*read)(pAVar15->aOrient + 10,4);
      (*read)(pAVar15->aOrient + 0xb,4);
      (*read)(&pAVar15->nScreenBoxValid,4);
      (*read)(pAVar15->aScreenBox,4);
      (*read)(pAVar15->aScreenBox + 1,4);
      (*read)(pAVar15->aScreenBox + 2,4);
      (*read)(pAVar15->aScreenBox + 3,4);
      pcVar6 = pAVar15->aSetName;
      (*read)(pcVar6,0x20);
      (*read)(&iStack_13c,4);
      Res_ResolveToSerialNumber(pAVar15->pColormapRef);
      if (*pcVar6 != '\0') {
        uVar10 = 0xffffffff;
        do {
          pcVar16 = pcVar6;
          if (uVar10 == 0) break;
          uVar10 = uVar10 - 1;
          pcVar16 = pcVar6 + 1;
          cVar2 = *pcVar6;
          pcVar6 = pcVar16;
        } while (cVar2 != '\0');
        uVar10 = ~uVar10;
        pcVar6 = pcVar16 + -uVar10;
        pcVar16 = acStack_40;
        for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
          *(undefined4 *)pcVar16 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar16 = pcVar16 + 4;
        }
        for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
          *pcVar16 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar16 = pcVar16 + 1;
        }
        pAVar15->aSetName[0] = '\0';
        sputRoom_AddActor(acStack_40,pAVar15);
      }
      pAVar15->pCostumes = (CostumeNode *)0x0;
      (*read)(&iStack_148,4);
      iStack_164 = 0;
      if (0 < iStack_148) {
        do {
          (*read)(auStack_134,4);
          (*read)(&iStack_128,0xc);
          (*read)(&fStack_11c,4);
          (*read)(&fStack_118,4);
          (*read)(&fStack_114,4);
          (*read)(&fStack_110,4);
          (*read)(&iStack_10c,4);
          (*read)(&iStack_108,4);
          (*read)(&iStack_104,4);
          (*read)(&iStack_100,4);
          (*read)(aiStack_fc,0x40);
          (*read)(&iStack_bc,4);
          (*read)(&RStack_b8.pData,4);
          Res_ResolveToSerialNumber(&RStack_b8);
          if (RStack_b8.nValid == 0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Bad_costume_Reference_004e9e90,s_main_sputResource_h_004e80a8,0xb8);
          }
          pcVar6 = (char *)CosUtil_PtrFromHandle((int)RStack_b8.pData);
          if (iStack_164 == 0) {
            sputActor_SetCostume(pAVar15,pcVar6,0);
          }
          else {
            sputActor_PushCostume(pAVar15,pcVar6,0);
          }
          Cos_RestoreInstance(pAVar15->pCostumes->dwInstance,read);
          pAVar15->pCostumes->aHeadJoints[0] = iStack_128;
          pAVar15->pCostumes->aHeadJoints[1] = iStack_124;
          pAVar15->pCostumes->aHeadJoints[2] = iStack_120;
          pAVar15->pCostumes->flLookRate = fStack_11c;
          pAVar15->pCostumes->flMaxPitch = fStack_118;
          pAVar15->pCostumes->flMaxYaw = fStack_114;
          pAVar15->pCostumes->flViewCos = fStack_110;
          pAVar15->pCostumes->nWalkChore = iStack_10c;
          pAVar15->pCostumes->nTurnLeftChore = iStack_108;
          pAVar15->pCostumes->nTurnRightChore = iStack_104;
          pAVar15->pCostumes->nRestChore = iStack_100;
          piVar13 = aiStack_fc;
          piVar17 = pAVar15->pCostumes->aTalkChores;
          for (iVar14 = 0x10; iVar14 != 0; iVar14 = iVar14 + -1) {
            *piVar17 = *piVar13;
            piVar13 = piVar13 + 1;
            piVar17 = piVar17 + 1;
          }
          pAVar15->pCostumes->nMumbleChore = iStack_bc;
          Res_RemoveReference(&RStack_b8);
          iStack_164 = iStack_164 + 1;
        } while (iStack_164 < iStack_148);
      }
      if (pAVar15->pCostumes != (CostumeNode *)0x0) {
        pMVar3 = pAVar15->pCostumes->pComponents;
        (*read)(&iStack_158,4);
        if (0 < iStack_158) {
          for (; pMVar3 != (ModelComponent *)0x0; pMVar3 = pMVar3->pNext) {
            (*read)(&pMVar3->nRoot,4);
            (*read)(&pMVar3->nComponentFlags,4);
            (*read)(&pMVar3->nParentNode,4);
            if (pMVar3->pThing->nType == 1) {
              if ((pMVar3->modelRef).nValid == 0) {
                (*g_pStd_HS->pAssertFail)
                          (s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
              }
              (*read)(pMVar3->pThing->pHierarchyExtra,
                      *(int *)((int)(pMVar3->modelRef).pData + 0x54) << 2);
            }
            (*read)(&iStack_14c,4);
            iStack_164 = 0;
            if (0 < iStack_14c) {
              do {
                pvStack_160 = pMVar3->pThing->pPuppet;
                (*read)(acStack_60,0x20);
                keyframe = sputResource_Alloc(0x4659454b,acStack_60);
                if (keyframe != (void *)0x0) {
                  (*read)(&uStack_144,4);
                  (*read)(&uStack_138,4);
                  pvVar4 = pvStack_160;
                  uVar10 = rdPuppet_AddTrack(pvStack_160,(uint)keyframe,uStack_144,uStack_138);
                  (*read)((int)pvVar4 + uVar10 * 0x134 + 8,4);
                  (*read)((int)pvVar4 + uVar10 * 0x134 + 0x128,4);
                  (*read)((int)pvVar4 + uVar10 * 0x134 + 300,4);
                  (*read)((int)pvVar4 + uVar10 * 0x134 + 0x20,4);
                  (*read)((int)pvVar4 + uVar10 * 0x134 + 0x24,4);
                }
                iStack_164 = iStack_164 + 1;
              } while (iStack_164 < iStack_14c);
            }
            iStack_158 = iStack_158 + -1;
          }
        }
      }
      if (iStack_13c != 0) {
        pAVar15->pExtra = (ActorExtra *)0x0;
        sputActor_AllocateActorExtra(pAVar15);
        (*read)(pAVar15->pExtra,4);
        (*read)(pAVar15->pExtra->aLookAt + 1,4);
        (*read)(pAVar15->pExtra->aLookAt + 2,4);
        (*read)(&pAVar15->pExtra->nWalking,4);
        (*read)(&pAVar15->pExtra->nTurning,4);
        (*read)(&pAVar15->pExtra->nResting,4);
        (*read)(&pAVar15->pExtra->flWalkRate,4);
        (*read)(&pAVar15->pExtra->flTurnRate,4);
        (*read)(&pAVar15->pExtra->nAlignTurn,4);
        (*read)(&pAVar15->pExtra->flOffsetYaw,4);
        (*read)(&pAVar15->pExtra->flYawLeft,4);
        (*read)(pAVar15->pExtra->aWaypoint,4);
        (*read)(pAVar15->pExtra->aWaypoint + 1,4);
        (*read)(pAVar15->pExtra->aWaypoint + 2,4);
        (*read)(pAVar15->pExtra->aDest,4);
        (*read)(pAVar15->pExtra->aDest + 1,4);
        (*read)(pAVar15->pExtra->aDest + 2,4);
        (*read)(&pAVar15->pExtra->nPathNodes,4);
        iVar14 = 0;
        do {
          (*read)((int)pAVar15->pExtra->aPath[0] + iVar14,4);
          (*read)((int)pAVar15->pExtra->aPath[0] + iVar14 + 4,4);
          (*read)((int)pAVar15->pExtra->aPath[0] + iVar14 + 8,4);
          iVar14 = iVar14 + 0xc;
        } while (iVar14 < 0x168);
        (*read)(&pAVar15->pExtra->nPathIndex,4);
        (*read)(&pAVar15->pExtra->pPuck,4);
        (*read)(&pAVar15->pExtra->nFollowBoxes,4);
        (*read)(&pAVar15->pExtra->nWalkDominate,4);
        (*read)(&pAVar15->pExtra->flPuckRadius,4);
        (*read)(&pAVar15->pExtra->nTalking,4);
        (*read)(&pAVar15->pExtra->nVoiceSound,4);
        (*read)(&pAVar15->pExtra->nTalkTime,4);
        (*read)(pAVar15->pExtra->aMsgId,0xc);
        (*read)(pAVar15->pExtra->aVoiceFile,0xf);
        (*read)(&pAVar15->pExtra->pText,4);
        (*read)(&pAVar15->pExtra->nLipSync,4);
        (*read)(&pAVar15->pExtra->nActiveShadow,4);
        (*read)(&pAVar15->pExtra->nCollisionMode,4);
        (*read)(&pAVar15->pExtra->flCollisionScale,4);
        (*read)(&pAVar15->pExtra->nCollided,4);
        (*read)(&pAVar15->pExtra->nClipPlaneActive,4);
        (*read)(pAVar15->pExtra->aClipNormal,4);
        (*read)(pAVar15->pExtra->aClipNormal + 1,4);
        (*read)(pAVar15->pExtra->aClipNormal + 2,4);
        (*read)(pAVar15->pExtra->aClipPoint,4);
        (*read)(pAVar15->pExtra->aClipPoint + 1,4);
        (*read)(pAVar15->pExtra->aClipPoint + 2,4);
        (*read)(&pAVar15->pExtra->dwTalkColor,4);
        (*read)(&pAVar15->pExtra->flTimeScale,4);
        (*read)(&pAVar15->pExtra->nInvClipNode,4);
        if (pAVar15->pExtra->pPuck != (Puck *)0x0) {
          pAVar15->pExtra->pPuck = (Puck *)0x0;
          sputActor_EnablePuck(pAVar15,1);
          if (pAVar15->pExtra->nFollowBoxes != 0) {
            Puck_Validate(pAVar15->pExtra->pPuck);
          }
        }
        if (pAVar15->pExtra->nTalking != 0) {
          iVar14 = 0;
          ppAVar7 = g_pTalkingActors;
          do {
            if (*ppAVar7 == (Actor *)0x0) {
              g_pTalkingActors[iVar14] = pAVar15;
              g_nNumActorsTalking = g_nNumActorsTalking + 1;
              break;
            }
            ppAVar7 = ppAVar7 + 1;
            iVar14 = iVar14 + 1;
          } while ((int)ppAVar7 < ((unsigned)(uintptr_t)&FLOAT_008ca320));
        }
        pTVar8 = pAVar15->pExtra->pText;
        if (pTVar8 != (TextObject *)0x0) {
          pTVar8 = sputText_FindSerialNumber((int)pTVar8);
          pAVar15->pExtra->pText = pTVar8;
        }
        sputActor_ResetShadows(pAVar15);
        pvStack_160 = (void *)0x1f8;
        do {
          iVar12 = (int)pvStack_160 + (int)pAVar15->pExtra;
          iVar14 = 0;
          iStack_164 = 0;
          (*read)(iVar12,4);
          (*read)(iVar12 + 4,4);
          (*read)(iVar12 + 8,4);
          (*read)(iVar12 + 0xc,4);
          (*read)(iVar12 + 0x10,4);
          (*read)(iVar12 + 0x14,4);
          (*read)(iVar12 + 0x18,4);
          (*read)(iVar12 + 0x1c,4);
          (*read)(iVar12 + 0x20,4);
          (*read)(&iStack_164,4);
          if (0xb < iStack_164) {
            (**(code **)(g_dwSputActHS + 0x18))
                      (s_tot_clips___MAX_SHADOW_CLIPS_004e9e70,
                       s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x3a5);
          }
          if (0 < iStack_164) {
            puVar5 = (undefined4 *)(iVar12 + 0x24);
            do {
              acStack_80[0] = '\0';
              (*read)(acStack_80,0x20);
              pWVar9 = WalkPlane_PlaneNamed(acStack_80);
              *puVar5 = pWVar9;
              iVar14 = iVar14 + 1;
              puVar5 = puVar5 + 1;
            } while (iVar14 < iStack_164);
          }
          pvStack_160 = (void *)((int)pvStack_160 + 0x54);
        } while ((int)pvStack_160 < 0x3f0);
      }
      iStack_150 = iStack_150 + 1;
    } while (iStack_150 < g_nNumActors);
  }
  iStack_154 = -1;
  g_pSelectedActor = (Actor *)0x0;
  (*read)(&iStack_154,4);
  if (iStack_154 != -1) {
    g_pSelectedActor = g_pActors + iStack_154;
  }
  return 0;
}
#undef RStack_b8
#undef acStack_40
#undef acStack_60
#undef acStack_80
#undef aiStack_fc
#undef auStack_134
#undef fStack_110
#undef fStack_114
#undef fStack_118
#undef fStack_11c
#undef iStack_100
#undef iStack_104
#undef iStack_108
#undef iStack_10c
#undef iStack_120
#undef iStack_124
#undef iStack_128
#undef iStack_13c
#undef iStack_140
#undef iStack_148
#undef iStack_14c
#undef iStack_150
#undef iStack_154
#undef iStack_158
#undef iStack_164
#undef iStack_bc
#undef local_15c
#undef pvStack_160
#undef uStack_138
#undef uStack_144


/* ---- 0x00490a60  sputActor_SetWalkChore ---- */
void __cdecl sputActor_SetWalkChore(Actor *actor,int chore,CostumeNode *costume)

{
  rdThing **pprVar1;
  uint uVar2;
  CostumeNode *pCVar3;
  
  pCVar3 = actor->pCostumes;
  if (pCVar3 != (CostumeNode *)0x0) {
    if (costume == (CostumeNode *)0x0) {
      costume = pCVar3;
    }
    pprVar1 = &pCVar3->pMainModel;
    if (pCVar3 != (CostumeNode *)0x0) {
      do {
        if ((pCVar3->pMainModel != *pprVar1) || (-1 < pCVar3->nWalkChore)) break;
        pCVar3 = pCVar3->pNext;
      } while (pCVar3 != (CostumeNode *)0x0);
      if ((pCVar3 != (CostumeNode *)0x0) && (pCVar3->pMainModel == *pprVar1)) {
        if (chore == pCVar3->nWalkChore) {
          return;
        }
        uVar2 = Cos_InstChoreStatus(pCVar3->dwInstance,pCVar3->nWalkChore);
        if ((uVar2 != 0) &&
           (FadeOutChore((void *)pCVar3->dwInstance,pCVar3->nWalkChore,g_nWALKSYSTEM_FADE_TIME),
           chore != -1)) {
          Cos_InstPlayChore(pCVar3->dwInstance,chore,uVar2 & 2,~uVar2 >> 2 & 1);
          Cos_InstUpdateChore(pCVar3->dwInstance,chore,100);
          sputCostume_FadeKeysIn((void *)pCVar3->dwInstance,chore,g_nWALKSYSTEM_FADE_TIME);
        }
        pCVar3->nWalkChore = -1;
        costume->nWalkChore = chore;
        return;
      }
    }
    costume->nWalkChore = chore;
  }
  return;
}

/* ---- 0x00490e60  sputActor_Terminate ---- */
/* Module interface slot 1 (sputActor): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. */

void __cdecl sputActor_Terminate(void)

{
  g_dwSputActHS = 0;
  if (g_dwSputActInitialize != 0) {
    g_dwSputActInitialize = 0;
  }
  return;
}

/* ---- 0x00490e80  sputActor_Startup ---- */
/* Module interface slot 2 (sputActor): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start allocates the 0x2a000-byte actor table and
   sorts the phoneme table; _Stop destroys every actor. Original name sputActor_Startup (the
   remaster's GrimFandango (Linux): aligned call in sputActor_Initialize); was sputActor_Start. */

uint __cdecl sputActor_Startup(void)

{
  int iVar1;
  Actor *pAVar2;
  
  if (g_dwSputActStartup != 0) {
    return 1;
  }
  g_pActors = (Actor *)(**(code **)(g_dwSputActHS + 0x20))
                                 (0x2a000,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x81b);
  pAVar2 = g_pActors;
  for (iVar1 = 0xa800; iVar1 != 0; iVar1 = iVar1 + -1) {
    pAVar2->pColormapRef = (void *)0x0;
    pAVar2 = (Actor *)&pAVar2->dwFlags;
  }
  qsort(g_aPhonemeTable,g_nPhonemeCount,8,ComparePhonemes);
  g_dwSputActStartup = 1;
  return 0;
}

/* ---- 0x00490ef0  sputActor_Shutdown ---- */
/* Module interface slot 3 (sputActor): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputActor_Shutdown (the remaster's GrimFandango
   (Linux): aligned call in sputActor_Initialize); was sputActor_Stop. */

void __cdecl sputActor_Shutdown(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < g_nMaxActors) {
    iVar1 = 0;
    do {
      sputActor_FreeActor((Actor *)((int)g_pActors->aPos + iVar1 + -0xc));
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0xa8;
    } while (iVar2 < g_nMaxActors);
  }
  if (g_pActors != (Actor *)0x0) {
    (**(code **)(g_dwSputActHS + 0x24))(g_pActors);
  }
  g_dwSputActStartup = 0;
  return;
}
