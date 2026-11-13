/* GRIMFANDANGO.EXE :: sputactor.c
 * functions 0x0048e2c0 .. 0x00490ef0 (7 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048e2c0  sputActor_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

uint __cdecl sputActor_Initialize(uint param_1,uint *param_2)

{
  g_dwSputActHS = param_1;
  *param_2 = (uint)sputActor_Initialize;
  param_2[1] = (uint)sputActor_Terminate;
  param_2[2] = (uint)sputActor_Startup;
  param_2[3] = (uint)sputActor_Shutdown;
  param_2[4] = (uint)sputActor_Save;
  param_2[5] = (uint)sputActor_Restore;
  param_2[6] = 0;
  param_2[7] = 0;
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

uint __cdecl sputActor_Save(code *param_1)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Actor *actor;
  undefined4 *puVar1;
  CostumeNode *pCVar2;
  int *piVar3;
  void *pvVar4;
  int *piVar5;
  Actor *pAVar6;
  int iVar7;
  int *piVar8;
  #define iStack_a8 (*(int *)(_frame + (0xc0 - 0xa8)))
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
  (*param_1)(&g_nMaxActors,4);
  (*param_1)(&local_84,4);
  iStack_94 = 0;
  pAVar6 = g_pActors;
  if (0 < g_nMaxActors) {
    iStack_98 = 0;
    do {
      actor = (Actor *)((int)pAVar6->aPos + iStack_98 + -0xc);
      if (*(int *)(pAVar6->aSetName + iStack_98 + 0x20) != 0) {
        iStack_8c = ((int)actor - (int)pAVar6) / 0xa8;
        (*param_1)(&iStack_8c,4);
        (*param_1)((int)actor->pColormapRef + 4,4);
        (*param_1)(&actor->dwFlags,4);
        (*param_1)(&actor->dwMoveFlags,4);
        (*param_1)(actor->aPos,4);
        (*param_1)(actor->aPos + 1,4);
        (*param_1)(actor->aPos + 2,4);
        (*param_1)(actor->aPrevPos,4);
        (*param_1)(actor->aPrevPos + 1,4);
        (*param_1)(actor->aPrevPos + 2,4);
        (*param_1)(actor->aRot,4);
        (*param_1)(actor->aRot + 1,4);
        (*param_1)(actor->aRot + 2,4);
        (*param_1)(&actor->flScale,4);
        (*param_1)(&actor->nMatrixDirty,4);
        (*param_1)(actor->aOrient,4);
        (*param_1)(actor->aOrient + 1,4);
        (*param_1)(actor->aOrient + 2,4);
        (*param_1)(actor->aOrient + 3,4);
        (*param_1)(actor->aOrient + 4,4);
        (*param_1)(actor->aOrient + 5,4);
        (*param_1)(actor->aOrient + 6,4);
        (*param_1)(actor->aOrient + 7,4);
        (*param_1)(actor->aOrient + 8,4);
        (*param_1)(actor->aOrient + 9,4);
        (*param_1)(actor->aOrient + 10,4);
        (*param_1)(actor->aOrient + 0xb,4);
        (*param_1)(&actor->nScreenBoxValid,4);
        (*param_1)(actor->aScreenBox,4);
        (*param_1)(actor->aScreenBox + 1,4);
        (*param_1)(actor->aScreenBox + 2,4);
        (*param_1)(actor->aScreenBox + 3,4);
        (*param_1)(actor->aSetName,0x20);
        uStack_88 = (uint)(actor->pExtra != (ActorExtra *)0x0);
        (*param_1)(&uStack_88,4);
        iStack_9c = Actor_CountCostumes(actor);
        (*param_1)(&iStack_9c,4);
        pCVar2 = actor->pCostumes;
        if (-1 < iStack_9c + -1) {
          piVar5 = aiStack_80 + iStack_9c + -1;
          iVar7 = iStack_9c;
          do {
            *piVar5 = (int)pCVar2;
            pCVar2 = pCVar2->pNext;
            piVar5 = piVar5 + -1;
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
        }
        iStack_a8 = 0;
        if (0 < iStack_9c) {
          piVar5 = aiStack_80;
          do {
            puVar1 = (undefined4 *)*piVar5;
            (*param_1)(puVar1,4);
            (*param_1)(puVar1 + 3,0xc);
            (*param_1)(puVar1 + 6,4);
            (*param_1)(puVar1 + 7,4);
            (*param_1)(puVar1 + 8,4);
            (*param_1)(puVar1 + 9,4);
            (*param_1)(puVar1 + 10,4);
            (*param_1)(puVar1 + 0xb,4);
            (*param_1)(puVar1 + 0xc,4);
            (*param_1)(puVar1 + 0xd,4);
            (*param_1)(puVar1 + 0xe,0x40);
            (*param_1)(puVar1 + 0x1e,4);
            if (puVar1[0x1f] == 0) {
              (**(code **)(g_dwSputActHS + 0x18))
                        (s_Valid_Ref___pCosNode__rCostume___004e9e1c,
                         s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x1c1);
            }
            (*param_1)(puVar1 + 0x20,4);
            Cos_SaveInstance(*puVar1,param_1);
            iStack_a8 = iStack_a8 + 1;
            piVar5 = piVar5 + 1;
          } while (iStack_a8 < iStack_9c);
        }
        if (actor->pCostumes != (CostumeNode *)0x0) {
          iStack_a4 = 0;
          for (pvVar4 = actor->pCostumes->pComponents; pvVar4 != (void *)0x0;
              pvVar4 = *(void **)((int)pvVar4 + 400)) {
            iStack_a4 = iStack_a4 + 1;
          }
          (*param_1)(&iStack_a4,4);
          for (piVar5 = actor->pCostumes->pComponents; piVar5 != (int *)0x0;
              piVar5 = (int *)piVar5[100]) {
            (*param_1)(piVar5 + 0xe,4);
            (*param_1)(piVar5 + 0xf,4);
            (*param_1)(piVar5 + 0x12,4);
            if (*(int *)piVar5[0x10] == 1) {
              if (*piVar5 == 0) {
                (*g_pStd_HS->pAssertFail)
                          (s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
              }
              (*param_1)(*(undefined4 *)(piVar5[0x10] + 0x2c),*(int *)(piVar5[1] + 0x54) << 2);
            }
            iStack_a0 = 0;
            if ((piVar5[0x10] == 0) || (iVar7 = *(int *)(piVar5[0x10] + 0x14), iVar7 == 0)) {
              (*param_1)(&iStack_a0,4);
            }
            else {
              piVar8 = (int *)(iVar7 + 0x130);
              iVar7 = 6;
              piVar3 = piVar8;
              do {
                if (*piVar3 != 0) {
                  iStack_a0 = iStack_a0 + 1;
                }
                piVar3 = piVar3 + 0x4d;
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
              (*param_1)(&iStack_a0,4);
              iStack_a8 = 6;
              do {
                if (*piVar8 != 0) {
                  (*param_1)(*piVar8,0x20);
                  (*param_1)(piVar8 + -0x48,4);
                  (*param_1)(piVar8 + -0x47,4);
                  (*param_1)(piVar8 + -0x4a,4);
                  (*param_1)(piVar8 + -2,4);
                  (*param_1)(piVar8 + -1,4);
                  (*param_1)(piVar8 + -0x44,4);
                  (*param_1)(piVar8 + -0x43,4);
                }
                piVar8 = piVar8 + 0x4d;
                iStack_a8 = iStack_a8 + -1;
              } while (iStack_a8 != 0);
            }
          }
        }
        pAVar6 = g_pActors;
        if (actor->pExtra != (ActorExtra *)0x0) {
          (*param_1)(actor->pExtra,4);
          (*param_1)(actor->pExtra->aLookAt + 1,4);
          (*param_1)(actor->pExtra->aLookAt + 2,4);
          (*param_1)(&actor->pExtra->nWalking,4);
          (*param_1)(&actor->pExtra->nTurning,4);
          (*param_1)(&actor->pExtra->nResting,4);
          (*param_1)(&actor->pExtra->flWalkRate,4);
          (*param_1)(&actor->pExtra->flTurnRate,4);
          (*param_1)(&actor->pExtra->nAlignTurn,4);
          (*param_1)(&actor->pExtra->flOffsetYaw,4);
          (*param_1)(&actor->pExtra->flYawLeft,4);
          (*param_1)(actor->pExtra->aWaypoint,4);
          (*param_1)(actor->pExtra->aWaypoint + 1,4);
          (*param_1)(actor->pExtra->aWaypoint + 2,4);
          (*param_1)(actor->pExtra->aDest,4);
          (*param_1)(actor->pExtra->aDest + 1,4);
          (*param_1)(actor->pExtra->aDest + 2,4);
          (*param_1)(&actor->pExtra->nPathNodes,4);
          iVar7 = 0;
          do {
            (*param_1)((int)actor->pExtra->aPath[0] + iVar7,4);
            (*param_1)((int)actor->pExtra->aPath[0] + iVar7 + 4,4);
            (*param_1)((int)actor->pExtra->aPath[0] + iVar7 + 8,4);
            iVar7 = iVar7 + 0xc;
          } while (iVar7 < 0x168);
          (*param_1)(&actor->pExtra->nPathIndex,4);
          (*param_1)(&actor->pExtra->pPuck,4);
          (*param_1)(&actor->pExtra->nFollowBoxes,4);
          (*param_1)(&actor->pExtra->nWalkDominate,4);
          (*param_1)(&actor->pExtra->flPuckRadius,4);
          (*param_1)(&actor->pExtra->nTalking,4);
          (*param_1)(&actor->pExtra->nVoiceSound,4);
          (*param_1)(&actor->pExtra->nTalkTime,4);
          (*param_1)(actor->pExtra->aMsgId,0xc);
          (*param_1)(actor->pExtra->aVoiceFile,0xf);
          (*param_1)(&actor->pExtra->pText,4);
          (*param_1)(&actor->pExtra->nLipSync,4);
          (*param_1)(&actor->pExtra->nActiveShadow,4);
          (*param_1)(&actor->pExtra->nCollisionMode,4);
          (*param_1)(&actor->pExtra->flCollisionScale,4);
          (*param_1)(&actor->pExtra->nCollided,4);
          (*param_1)(&actor->pExtra->nClipPlaneActive,4);
          (*param_1)(actor->pExtra->aClipNormal,4);
          (*param_1)(actor->pExtra->aClipNormal + 1,4);
          (*param_1)(actor->pExtra->aClipNormal + 2,4);
          (*param_1)(actor->pExtra->aClipPoint,4);
          (*param_1)(actor->pExtra->aClipPoint + 1,4);
          (*param_1)(actor->pExtra->aClipPoint + 2,4);
          (*param_1)(&actor->pExtra->dwTalkColor,4);
          (*param_1)(&actor->pExtra->flTimeScale,4);
          (*param_1)(&actor->pExtra->nInvClipNode,4);
          pvVar4 = sputRoom_GetCurrentRoom();
          if (pvVar4 == (void *)0x0) {
            sputActor_ResetShadows(actor);
          }
          iStack_a8 = 0x1f8;
          do {
            iVar7 = (int)actor->pExtra->aLookAt + iStack_a8;
            iStack_a4 = 0;
            (*param_1)(iVar7,4);
            (*param_1)(iVar7 + 4,4);
            (*param_1)(iVar7 + 8,4);
            (*param_1)(iVar7 + 0xc,4);
            (*param_1)(iVar7 + 0x10,4);
            (*param_1)(iVar7 + 0x14,4);
            (*param_1)(iVar7 + 0x18,4);
            (*param_1)(iVar7 + 0x1c,4);
            (*param_1)(iVar7 + 0x20,4);
            piVar8 = (int *)(iVar7 + 0x24);
            iVar7 = 0xc;
            piVar5 = piVar8;
            do {
              if (*piVar5 != 0) {
                iStack_a4 = iStack_a4 + 1;
              }
              piVar5 = piVar5 + 1;
              iVar7 = iVar7 + -1;
            } while (iVar7 != 0);
            (*param_1)(&iStack_a4,4);
            iVar7 = 0xc;
            do {
              if (*piVar8 != 0) {
                (*param_1)(*piVar8,0x20);
              }
              piVar8 = piVar8 + 1;
              iVar7 = iVar7 + -1;
            } while (iVar7 != 0);
            iStack_a8 = iStack_a8 + 0x54;
            pAVar6 = g_pActors;
          } while (iStack_a8 < 0x3f0);
        }
      }
      iStack_94 = iStack_94 + 1;
      iStack_98 = iStack_98 + 0xa8;
    } while (iStack_94 < g_nMaxActors);
  }
  iStack_90 = -1;
  if (g_pSelectedActor != (Actor *)0x0) {
    iStack_90 = ((int)g_pSelectedActor - (int)pAVar6) / 0xa8;
  }
  (*param_1)(&iStack_90,4);
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
#undef iStack_a8
#undef local_84
#undef uStack_88


/* ---- 0x0048ecd0  sputActor_Restore ---- */
/* Module interface slot 5 (sputActor): save-game reader, calls the SaveGame_Read callback it is
   handed; returns non-zero on a short read. Original name sputActor_Restore (the remaster's
   GrimFandango (Linux): the only unmatched caller of rdPuppet_AddTrack; 4 matched neighbours agree,
   2 disagree); was sputActor_RestoreState. */

uint __cdecl sputActor_Restore(code *param_1)

{
  unsigned char _frame[0x180] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Actor *pAVar1;
  char cVar2;
  void *pvVar3;
  undefined4 *puVar4;
  char *pcVar5;
  void *keyframe;
  Actor **ppAVar6;
  TextObject *pTVar7;
  WalkPlane *pWVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  Actor *pAVar14;
  char *pcVar15;
  int *piVar16;
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
  #define uStack_b8 (*(uint *)(_frame + (0x180 - 0xb8)))
  #define aiStack_b4 (*(int (*)[13])(_frame + (0x180 - 0xb4)))
  #define acStack_80 (*(char (*)[32])(_frame + (0x180 - 0x80)))
  #define acStack_60 (*(char (*)[32])(_frame + (0x180 - 0x60)))
  #define acStack_40 (*(char (*)[64])(_frame + (0x180 - 0x40)))
  
  g_pTalkingActors[0] = (Actor *)0x0;
  g_pTalkingActors[1] = (Actor *)0x0;
  g_pTalkingActors[2] = (Actor *)0x0;
  g_pTalkingActors[3] = (Actor *)0x0;
  iVar13 = 0;
  g_nNumActorsTalking = 0;
  if (0 < g_nMaxActors) {
    iVar11 = 0;
    do {
      sputActor_FreeActor((Actor *)((int)g_pActors->aPos + iVar11 + -0xc));
      iVar13 = iVar13 + 1;
      iVar11 = iVar11 + 0xa8;
    } while (iVar13 < g_nMaxActors);
  }
  (*param_1)(&local_15c,4);
  if (g_nMaxActors < local_15c) {
    g_pActors = (Actor *)(**(code **)(g_dwSputActHS + 0x28))
                                   (g_pActors,local_15c * 0xa8,
                                    s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x28a);
    pAVar14 = g_pActors + g_nMaxActors;
    for (iVar13 = ((local_15c - g_nMaxActors) * 0x15 & 0x1fffffffU) << 1; iVar13 != 0;
        iVar13 = iVar13 + -1) {
      pAVar14->pColormapRef = (void *)0x0;
      pAVar14 = (Actor *)&pAVar14->dwFlags;
    }
    for (iVar13 = 0; iVar13 != 0; iVar13 = iVar13 + -1) {
      *(undefined1 *)&pAVar14->pColormapRef = 0;
      pAVar14 = (Actor *)((int)&pAVar14->pColormapRef + 1);
    }
    g_nMaxActors = local_15c;
  }
  (*param_1)(&g_nNumActors,4);
  iStack_150 = 0;
  if (0 < g_nNumActors) {
    do {
      (*param_1)(&iStack_140,4);
      pAVar14 = g_pActors + iStack_140;
      pAVar1 = g_pActors + iStack_140;
      pAVar14->nInUse = 1;
      if (pAVar1->pColormapRef == (void *)0x0) {
        puVar4 = (undefined4 *)
                 (**(code **)(g_dwSputActHS + 0x20))
                           (0x34,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x29f);
        pAVar14->pColormapRef = puVar4;
        for (iVar13 = 0xd; iVar13 != 0; iVar13 = iVar13 + -1) {
          *puVar4 = 0;
          puVar4 = puVar4 + 1;
        }
      }
      (*param_1)((int)pAVar14->pColormapRef + 4,4);
      (*param_1)(&pAVar14->dwFlags,4);
      (*param_1)(&pAVar14->dwMoveFlags,4);
      (*param_1)(pAVar14->aPos,4);
      (*param_1)(pAVar14->aPos + 1,4);
      (*param_1)(pAVar14->aPos + 2,4);
      (*param_1)(pAVar14->aPrevPos,4);
      (*param_1)(pAVar14->aPrevPos + 1,4);
      (*param_1)(pAVar14->aPrevPos + 2,4);
      (*param_1)(pAVar14->aRot,4);
      (*param_1)(pAVar14->aRot + 1,4);
      (*param_1)(pAVar14->aRot + 2,4);
      (*param_1)(&pAVar14->flScale,4);
      (*param_1)(&pAVar14->nMatrixDirty,4);
      pAVar14->nMatrixDirty = 0;
      (*param_1)(pAVar14->aOrient,4);
      (*param_1)(pAVar14->aOrient + 1,4);
      (*param_1)(pAVar14->aOrient + 2,4);
      (*param_1)(pAVar14->aOrient + 3,4);
      (*param_1)(pAVar14->aOrient + 4,4);
      (*param_1)(pAVar14->aOrient + 5,4);
      (*param_1)(pAVar14->aOrient + 6,4);
      (*param_1)(pAVar14->aOrient + 7,4);
      (*param_1)(pAVar14->aOrient + 8,4);
      (*param_1)(pAVar14->aOrient + 9,4);
      (*param_1)(pAVar14->aOrient + 10,4);
      (*param_1)(pAVar14->aOrient + 0xb,4);
      (*param_1)(&pAVar14->nScreenBoxValid,4);
      (*param_1)(pAVar14->aScreenBox,4);
      (*param_1)(pAVar14->aScreenBox + 1,4);
      (*param_1)(pAVar14->aScreenBox + 2,4);
      (*param_1)(pAVar14->aScreenBox + 3,4);
      pcVar5 = pAVar14->aSetName;
      (*param_1)(pcVar5,0x20);
      (*param_1)(&iStack_13c,4);
      Res_ResolveToSerialNumber(pAVar14->pColormapRef);
      if (*pcVar5 != '\0') {
        uVar9 = 0xffffffff;
        do {
          pcVar15 = pcVar5;
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          pcVar15 = pcVar5 + 1;
          cVar2 = *pcVar5;
          pcVar5 = pcVar15;
        } while (cVar2 != '\0');
        uVar9 = ~uVar9;
        pcVar5 = pcVar15 + -uVar9;
        pcVar15 = acStack_40;
        for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pcVar15 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar15 = pcVar15 + 4;
        }
        for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *pcVar15 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar15 = pcVar15 + 1;
        }
        pAVar14->aSetName[0] = '\0';
        sputRoom_AddActor((Actor *)acStack_40,(char *)pAVar14);
      }
      pAVar14->pCostumes = (CostumeNode *)0x0;
      (*param_1)(&iStack_148,4);
      iStack_164 = 0;
      if (0 < iStack_148) {
        do {
          (*param_1)(auStack_134,4);
          (*param_1)(&iStack_128,0xc);
          (*param_1)(&fStack_11c,4);
          (*param_1)(&fStack_118,4);
          (*param_1)(&fStack_114,4);
          (*param_1)(&fStack_110,4);
          (*param_1)(&iStack_10c,4);
          (*param_1)(&iStack_108,4);
          (*param_1)(&iStack_104,4);
          (*param_1)(&iStack_100,4);
          (*param_1)(aiStack_fc,0x40);
          (*param_1)(&iStack_bc,4);
          (*param_1)(aiStack_b4,4);
          Res_ResolveToSerialNumber(&uStack_b8);
          if (uStack_b8 == 0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Bad_costume_Reference_004e9e90,s_main_sputResource_h_004e80a8,0xb8);
          }
          pcVar5 = (char *)CosUtil_PtrFromHandle(aiStack_b4[0]);
          if (iStack_164 == 0) {
            sputActor_SetCostume(pAVar14,pcVar5,0);
          }
          else {
            sputActor_PushCostume(pAVar14,pcVar5,0);
          }
          Cos_RestoreInstance(pAVar14->pCostumes->dwInstance,param_1);
          pAVar14->pCostumes->aHeadJoints[0] = iStack_128;
          pAVar14->pCostumes->aHeadJoints[1] = iStack_124;
          pAVar14->pCostumes->aHeadJoints[2] = iStack_120;
          pAVar14->pCostumes->flLookRate = fStack_11c;
          pAVar14->pCostumes->flMaxPitch = fStack_118;
          pAVar14->pCostumes->flMaxYaw = fStack_114;
          pAVar14->pCostumes->flViewCos = fStack_110;
          pAVar14->pCostumes->nWalkChore = iStack_10c;
          pAVar14->pCostumes->nTurnLeftChore = iStack_108;
          pAVar14->pCostumes->nTurnRightChore = iStack_104;
          pAVar14->pCostumes->nRestChore = iStack_100;
          piVar12 = aiStack_fc;
          piVar16 = pAVar14->pCostumes->aTalkChores;
          for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
            *piVar16 = *piVar12;
            piVar12 = piVar12 + 1;
            piVar16 = piVar16 + 1;
          }
          pAVar14->pCostumes->nMumbleChore = iStack_bc;
          Res_RemoveReference(&uStack_b8);
          iStack_164 = iStack_164 + 1;
        } while (iStack_164 < iStack_148);
      }
      if (pAVar14->pCostumes != (CostumeNode *)0x0) {
        piVar12 = pAVar14->pCostumes->pComponents;
        (*param_1)(&iStack_158,4);
        if (0 < iStack_158) {
          for (; piVar12 != (int *)0x0; piVar12 = (int *)piVar12[100]) {
            (*param_1)(piVar12 + 0xe,4);
            (*param_1)(piVar12 + 0xf,4);
            (*param_1)(piVar12 + 0x12,4);
            if (*(int *)piVar12[0x10] == 1) {
              if (*piVar12 == 0) {
                (*g_pStd_HS->pAssertFail)
                          (s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
              }
              (*param_1)(*(undefined4 *)(piVar12[0x10] + 0x2c),*(int *)(piVar12[1] + 0x54) << 2);
            }
            (*param_1)(&iStack_14c,4);
            iStack_164 = 0;
            if (0 < iStack_14c) {
              do {
                pvStack_160 = *(void **)(piVar12[0x10] + 0x14);
                (*param_1)(acStack_60,0x20);
                keyframe = sputResource_Alloc(0x4659454b,acStack_60);
                if (keyframe != (void *)0x0) {
                  (*param_1)(&uStack_144,4);
                  (*param_1)(&uStack_138,4);
                  pvVar3 = pvStack_160;
                  uVar9 = rdPuppet_AddTrack(pvStack_160,(uint)keyframe,uStack_144,uStack_138);
                  (*param_1)((int)pvVar3 + uVar9 * 0x134 + 8,4);
                  (*param_1)((int)pvVar3 + uVar9 * 0x134 + 0x128,4);
                  (*param_1)((int)pvVar3 + uVar9 * 0x134 + 300,4);
                  (*param_1)((int)pvVar3 + uVar9 * 0x134 + 0x20,4);
                  (*param_1)((int)pvVar3 + uVar9 * 0x134 + 0x24,4);
                }
                iStack_164 = iStack_164 + 1;
              } while (iStack_164 < iStack_14c);
            }
            iStack_158 = iStack_158 + -1;
          }
        }
      }
      if (iStack_13c != 0) {
        pAVar14->pExtra = (ActorExtra *)0x0;
        sputActor_AllocateActorExtra(pAVar14);
        (*param_1)(pAVar14->pExtra,4);
        (*param_1)(pAVar14->pExtra->aLookAt + 1,4);
        (*param_1)(pAVar14->pExtra->aLookAt + 2,4);
        (*param_1)(&pAVar14->pExtra->nWalking,4);
        (*param_1)(&pAVar14->pExtra->nTurning,4);
        (*param_1)(&pAVar14->pExtra->nResting,4);
        (*param_1)(&pAVar14->pExtra->flWalkRate,4);
        (*param_1)(&pAVar14->pExtra->flTurnRate,4);
        (*param_1)(&pAVar14->pExtra->nAlignTurn,4);
        (*param_1)(&pAVar14->pExtra->flOffsetYaw,4);
        (*param_1)(&pAVar14->pExtra->flYawLeft,4);
        (*param_1)(pAVar14->pExtra->aWaypoint,4);
        (*param_1)(pAVar14->pExtra->aWaypoint + 1,4);
        (*param_1)(pAVar14->pExtra->aWaypoint + 2,4);
        (*param_1)(pAVar14->pExtra->aDest,4);
        (*param_1)(pAVar14->pExtra->aDest + 1,4);
        (*param_1)(pAVar14->pExtra->aDest + 2,4);
        (*param_1)(&pAVar14->pExtra->nPathNodes,4);
        iVar13 = 0;
        do {
          (*param_1)((int)pAVar14->pExtra->aPath[0] + iVar13,4);
          (*param_1)((int)pAVar14->pExtra->aPath[0] + iVar13 + 4,4);
          (*param_1)((int)pAVar14->pExtra->aPath[0] + iVar13 + 8,4);
          iVar13 = iVar13 + 0xc;
        } while (iVar13 < 0x168);
        (*param_1)(&pAVar14->pExtra->nPathIndex,4);
        (*param_1)(&pAVar14->pExtra->pPuck,4);
        (*param_1)(&pAVar14->pExtra->nFollowBoxes,4);
        (*param_1)(&pAVar14->pExtra->nWalkDominate,4);
        (*param_1)(&pAVar14->pExtra->flPuckRadius,4);
        (*param_1)(&pAVar14->pExtra->nTalking,4);
        (*param_1)(&pAVar14->pExtra->nVoiceSound,4);
        (*param_1)(&pAVar14->pExtra->nTalkTime,4);
        (*param_1)(pAVar14->pExtra->aMsgId,0xc);
        (*param_1)(pAVar14->pExtra->aVoiceFile,0xf);
        (*param_1)(&pAVar14->pExtra->pText,4);
        (*param_1)(&pAVar14->pExtra->nLipSync,4);
        (*param_1)(&pAVar14->pExtra->nActiveShadow,4);
        (*param_1)(&pAVar14->pExtra->nCollisionMode,4);
        (*param_1)(&pAVar14->pExtra->flCollisionScale,4);
        (*param_1)(&pAVar14->pExtra->nCollided,4);
        (*param_1)(&pAVar14->pExtra->nClipPlaneActive,4);
        (*param_1)(pAVar14->pExtra->aClipNormal,4);
        (*param_1)(pAVar14->pExtra->aClipNormal + 1,4);
        (*param_1)(pAVar14->pExtra->aClipNormal + 2,4);
        (*param_1)(pAVar14->pExtra->aClipPoint,4);
        (*param_1)(pAVar14->pExtra->aClipPoint + 1,4);
        (*param_1)(pAVar14->pExtra->aClipPoint + 2,4);
        (*param_1)(&pAVar14->pExtra->dwTalkColor,4);
        (*param_1)(&pAVar14->pExtra->flTimeScale,4);
        (*param_1)(&pAVar14->pExtra->nInvClipNode,4);
        if (pAVar14->pExtra->pPuck != (Puck *)0x0) {
          pAVar14->pExtra->pPuck = (Puck *)0x0;
          sputActor_EnablePuck(pAVar14,1);
          if (pAVar14->pExtra->nFollowBoxes != 0) {
            Puck_Validate(pAVar14->pExtra->pPuck);
          }
        }
        if (pAVar14->pExtra->nTalking != 0) {
          iVar13 = 0;
          ppAVar6 = g_pTalkingActors;
          do {
            if (*ppAVar6 == (Actor *)0x0) {
              g_pTalkingActors[iVar13] = pAVar14;
              g_nNumActorsTalking = g_nNumActorsTalking + 1;
              break;
            }
            ppAVar6 = ppAVar6 + 1;
            iVar13 = iVar13 + 1;
          } while ((int)ppAVar6 < ((unsigned)(uintptr_t)&DAT_008ca320));
        }
        pTVar7 = pAVar14->pExtra->pText;
        if (pTVar7 != (TextObject *)0x0) {
          pTVar7 = sputText_FindSerialNumber((int)pTVar7);
          pAVar14->pExtra->pText = pTVar7;
        }
        sputActor_ResetShadows(pAVar14);
        pvStack_160 = (void *)0x1f8;
        do {
          iVar11 = (int)pvStack_160 + (int)pAVar14->pExtra;
          iVar13 = 0;
          iStack_164 = 0;
          (*param_1)(iVar11,4);
          (*param_1)(iVar11 + 4,4);
          (*param_1)(iVar11 + 8,4);
          (*param_1)(iVar11 + 0xc,4);
          (*param_1)(iVar11 + 0x10,4);
          (*param_1)(iVar11 + 0x14,4);
          (*param_1)(iVar11 + 0x18,4);
          (*param_1)(iVar11 + 0x1c,4);
          (*param_1)(iVar11 + 0x20,4);
          (*param_1)(&iStack_164,4);
          if (0xb < iStack_164) {
            (**(code **)(g_dwSputActHS + 0x18))
                      (s_tot_clips___MAX_SHADOW_CLIPS_004e9e70,
                       s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x3a5);
          }
          if (0 < iStack_164) {
            puVar4 = (undefined4 *)(iVar11 + 0x24);
            do {
              acStack_80[0] = '\0';
              (*param_1)(acStack_80,0x20);
              pWVar8 = WalkPlane_PlaneNamed(acStack_80);
              *puVar4 = pWVar8;
              iVar13 = iVar13 + 1;
              puVar4 = puVar4 + 1;
            } while (iVar13 < iStack_164);
          }
          pvStack_160 = (void *)((int)pvStack_160 + 0x54);
        } while ((int)pvStack_160 < 0x3f0);
      }
      iStack_150 = iStack_150 + 1;
    } while (iStack_150 < g_nNumActors);
  }
  iStack_154 = -1;
  g_pSelectedActor = (Actor *)0x0;
  (*param_1)(&iStack_154,4);
  if (iStack_154 != -1) {
    g_pSelectedActor = g_pActors + iStack_154;
  }
  return 0;
}
#undef acStack_40
#undef acStack_60
#undef acStack_80
#undef aiStack_b4
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
#undef uStack_b8


/* ---- 0x00490a60  sputActor_SetWalkChore ---- */
void __cdecl sputActor_SetWalkChore(Actor *actor,int chore,CostumeNode *costume)

{
  void **ppvVar1;
  uint uVar2;
  CostumeNode *pCVar3;
  
  pCVar3 = actor->pCostumes;
  if (pCVar3 != (CostumeNode *)0x0) {
    if (costume == (CostumeNode *)0x0) {
      costume = pCVar3;
    }
    ppvVar1 = &pCVar3->pMainModel;
    if (pCVar3 != (CostumeNode *)0x0) {
      do {
        if ((pCVar3->pMainModel != *ppvVar1) || (-1 < pCVar3->nWalkChore)) break;
        pCVar3 = pCVar3->pNext;
      } while (pCVar3 != (CostumeNode *)0x0);
      if ((pCVar3 != (CostumeNode *)0x0) && (pCVar3->pMainModel == *ppvVar1)) {
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

void sputActor_Terminate(void)

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

undefined4 sputActor_Startup(void)

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

void sputActor_Shutdown(void)

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
