/* GRIMFANDANGO.EXE :: actors.c
 * functions 0x0048e240 .. 0x0048fcf0 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048e240  Actors_FreeAllCostumes ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua NukeResources: drops every actor's costume list */

void Actors_FreeAllCostumes(void)

{
  void *costume;
  void *pvVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  if (0 < g_nActorCapacity) {
    iVar2 = 0;
    pvVar1 = g_pActorTable;
    do {
      if (*(int *)((int)pvVar1 + iVar2 + 0x9c) != 0) {
        costume = *(void **)((int)pvVar1 + iVar2 + 0xa0);
        if (costume != (void *)0x0) {
          Costume_PrintList(costume);
          pvVar1 = g_pActorTable;
        }
        Costume_FreeList(*(void **)((int)pvVar1 + iVar2 + 0xa0),1);
        *(undefined4 *)((int)g_pActorTable + iVar2 + 0xa0) = 0;
        pvVar1 = g_pActorTable;
      }
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 0xa8;
    } while (iVar3 < g_nActorCapacity);
  }
  return;
}
#endif


/* ---- 0x0048fcc0  Actors_UpdateTalking ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Advances lip sync for the four actors in g_pTalkingActors */

void __cdecl Actors_UpdateTalking(float dt)

{
  void **ppvVar1;
  
  ppvVar1 = &g_pTalkingActors;
  do {
    if (*ppvVar1 != (void *)0x0) {
      Actor_UpdateTalk(*ppvVar1,dt);
    }
    ppvVar1 = ppvVar1 + 1;
  } while ((int)ppvVar1 < IMG_ADDR(0x008ca320));
  return;
}
#endif


/* ---- 0x0048fcf0  Actors_UpdateAll ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Per-frame update of every actor in the current set: talking, movement, collision */

void __cdecl Actors_UpdateAll(float dt)

{
  void *pvVar1;
  int *piVar2;
  
  g_nDrawableActorCount = 0;
  pvVar1 = Set_GetCurrent();
  if (pvVar1 != (void *)0x0) {
    Actors_UpdateTalking(dt);
    piVar2 = *(int **)(*(int *)((int)pvVar1 + 0x1abc) + 0x80);
    if (piVar2 != (int *)0x0) {
      do {
        pvVar1 = (void *)((int)g_pActorTable + *piVar2 * 0xa8);
        if (pvVar1 != (void *)0x0) {
          if (*(int *)((int)pvVar1 + 0xa4) != 0) {
            *(undefined4 *)(*(int *)((int)pvVar1 + 0xa4) + 0x3f8) = 0;
          }
          if ((*(int *)((int)pvVar1 + 0xa0) != 0) &&
             (*(int *)(*(int *)((int)pvVar1 + 0xa0) + 4) != 0)) {
            (&g_pDrawableActors)[g_nDrawableActorCount] = pvVar1;
            g_nDrawableActorCount = g_nDrawableActorCount + 1;
          }
          Actor_UpdateMovement(pvVar1,dt);
        }
        piVar2 = (int *)piVar2[2];
      } while (piVar2 != (int *)0x0);
      Collision_UpdateMovedActors();
    }
  }
  return;
}
#endif

