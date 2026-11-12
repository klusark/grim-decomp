/* GRIMFANDANGO.EXE :: actors.c
 * functions 0x0048e240 .. 0x0048fcf0 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048e240  sputActor_NukeCostumeStacks ---- */
/* Lua NukeResources: drops every actor's costume list Original name sputActor_NukeCostumeStacks
   (the remaster's GrimFandango (Linux): the only unmatched caller of Costume_PrintList; 1 matched
   neighbours agree, 1 disagree); was Actors_FreeAllCostumes. */

void sputActor_NukeCostumeStacks(void)

{
  char *pcVar1;
  Actor *pAVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  if (0 < g_nMaxActors) {
    iVar3 = 0;
    pAVar2 = g_pActors;
    do {
      if (*(int *)(pAVar2->aSetName + iVar3 + 0x20) != 0) {
        if (*(CostumeNode **)(pAVar2->aSetName + iVar3 + 0x24) != (CostumeNode *)0x0) {
          sputCostume_PrintCostumeInfo(*(CostumeNode **)(pAVar2->aSetName + iVar3 + 0x24));
          pAVar2 = g_pActors;
        }
        sputCostume_FreeCostumeNodes(*(CostumeNode **)(pAVar2->aSetName + iVar3 + 0x24),1);
        pcVar1 = g_pActors->aSetName + iVar3 + 0x24;
        pcVar1[0] = '\0';
        pcVar1[1] = '\0';
        pcVar1[2] = '\0';
        pcVar1[3] = '\0';
        pAVar2 = g_pActors;
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0xa8;
    } while (iVar4 < g_nMaxActors);
  }
  return;
}

/* ---- 0x0048fcc0  sputActor_UpdateSpeechOnly ---- */
/* Advances lip sync for the four actors in g_pTalkingActors Original name
   sputActor_UpdateSpeechOnly (the remaster's GrimFandango (Linux): aligned call in
   sputActor_UpdateActors, sputRender_Update); was Actors_UpdateTalking. */

void __cdecl sputActor_UpdateSpeechOnly(float dt)

{
  Actor **ppAVar1;
  
  ppAVar1 = g_pTalkingActors;
  do {
    if (*ppAVar1 != (Actor *)0x0) {
      sputActor_UpdateActorSpeech(*ppAVar1,dt);
    }
    ppAVar1 = ppAVar1 + 1;
  } while ((int)ppAVar1 < ((unsigned)(uintptr_t)&DAT_008ca320));
  return;
}

/* ---- 0x0048fcf0  sputActor_UpdateActors ---- */
/* Per-frame update of every actor in the current set: talking, movement, collision Original name
   sputActor_UpdateActors (the remaster's GrimFandango (Linux): aligned call in
   grimlib_UpdateManual); was Actors_UpdateAll. */

void __cdecl sputActor_UpdateActors(float dt)

{
  Actor *actor;
  void *pvVar1;
  int *piVar2;
  
  g_nTotActors = 0;
  pvVar1 = sputRoom_GetCurrentRoom();
  if (pvVar1 != (void *)0x0) {
    sputActor_UpdateSpeechOnly(dt);
    piVar2 = *(int **)(*(int *)((int)pvVar1 + 0x1abc) + 0x80);
    if (piVar2 != (int *)0x0) {
      do {
        actor = g_pActors + *piVar2;
        if (actor != (Actor *)0x0) {
          if (actor->pExtra != (ActorExtra *)0x0) {
            actor->pExtra->nCollided = 0;
          }
          if ((actor->pCostumes != (CostumeNode *)0x0) &&
             (actor->pCostumes->pMainModel != (void *)0x0)) {
            (&g_pDrawableActors)[g_nTotActors] = actor;
            g_nTotActors = g_nTotActors + 1;
          }
          Actor_UpdateMovement(actor,dt);
        }
        piVar2 = (int *)piVar2[2];
      } while (piVar2 != (int *)0x0);
      Collision_UpdateMovedActors();
    }
  }
  return;
}
