/* GRIMFANDANGO.EXE :: sputroom.c
 * functions 0x004a48c0 .. 0x004a5430 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a48c0  sputRoom_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined * __cdecl sputRoom_Initialize(uint param_1,undefined **param_2)

{
  int iVar1;
  uint *puVar2;
  
  g_pSvcRoom = (GrimServices *)param_1;
  *param_2 = sputRoom_Initialize;
  param_2[1] = sputRoom_Terminate;
  param_2[2] = sputRoom_Start;
  param_2[3] = sputRoom_Stop;
  param_2[4] = Set_SaveState;
  param_2[5] = Set_RestoreState;
  param_2[6] = (undefined *)0x0;
  param_2[7] = (undefined *)0x0;
  puVar2 = &g_CurrentSetRef;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  UINT_008cb098 = 1;
  g_CurrentSetRef = 0;
  return (undefined *)0x0;
}

/* ---- 0x004a5390  sputRoom_Terminate ---- */
/* Module interface slot 1 (sputRoom): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. */

void sputRoom_Terminate(void)

{
  g_pSvcRoom = (GrimServices *)0x0;
  if (UINT_008cb098 != 0) {
    UINT_008cb098 = 0;
  }
  return;
}

/* ---- 0x004a53b0  sputRoom_Start ---- */
/* Module interface slot 2 (sputRoom): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start registers the set-file chunk handlers
   (colormaps, setups, lights, sectors) and creates the positioned-sound pool. */

undefined4 sputRoom_Start(void)

{
  if (UINT_008cb09c != 0) {
    return 1;
  }
  Set_RegisterHandle(s_colormaps_004ec734,SetFile_ParseColormaps);
  Set_RegisterHandle(s_setups_004ec72c,SetFile_ParseSetups);
  Set_RegisterHandle(s_lights_004ec724,SetFile_ParseLights);
  Set_RegisterHandle(s_sectors_004ec71c,SetFile_SectorsSectionHandler);
  g_pPositionedSoundPool = (void **)Pool_Create(0x24,0x10,8);
  UINT_008cb09c = 1;
  return 0;
}

/* ---- 0x004a5430  sputRoom_Stop ---- */
/* Module interface slot 3 (sputRoom): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. */

void sputRoom_Stop(void)

{
  int iVar1;
  void *pvVar2;
  void *pvVar3;
  int iVar4;
  
  pvVar3 = g_pSetActorLists;
  while (pvVar3 != (void *)0x0) {
    iVar4 = *(int *)((int)pvVar3 + 0x80);
    while (iVar4 != 0) {
      iVar1 = *(int *)(iVar4 + 8);
      (*g_pSvcRoom->pFree)(iVar4);
      iVar4 = iVar1;
    }
    pvVar2 = *(void **)((int)pvVar3 + 0x84);
    (*g_pSvcRoom->pFree)(pvVar3);
    pvVar3 = pvVar2;
  }
  if (g_pPositionedSoundPool != (void **)0x0) {
    Pool_Destroy(g_pPositionedSoundPool);
    g_pPositionedSoundPool = (void **)0x0;
  }
  UINT_008cb09c = 0;
  return;
}
