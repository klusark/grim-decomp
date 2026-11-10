/* GRIMFANDANGO.EXE :: sputcostume.c
 * functions 0x004957f0 .. 0x004988a0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004957f0  sputCostume_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

int sputCostume_Initialize(GrimServices *param_1,undefined4 *param_2)

{
  int iVar1;
  
  g_pSputCosHS = param_1;
  *param_2 = sputCostume_Initialize;
  param_2[1] = sputCostume_Terminate;
  param_2[2] = sputCostume_Startup;
  param_2[3] = sputCostume_Shutdown;
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  iVar1 = Cos_Initialize((int)param_1,(int *)&g_aChoreMS);
  g_dwSputCosInitialize = (uint)(iVar1 == 0);
  return iVar1 != 0;
}

/* ---- 0x00495960  sputCostume_Terminate ---- */
/* Module interface slot 1 (sputCostume): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. */

void sputCostume_Terminate(void)

{
  g_pSputCosHS = (GrimServices *)0x0;
  if (g_dwSputCosInitialize != 0) {
    g_dwSputCosInitialize = 0;
    (*(code *)UINT_008ca774)();
    if (g_pShadowColormap != (void *)0x0) {
      rdColormap_Free(g_pShadowColormap);
    }
  }
  return;
}

/* ---- 0x004959a0  sputCostume_Startup ---- */
/* Module interface slot 2 (sputCostume): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). Original name sputCostume_Startup (the remaster's
   GrimFandango (Linux): aligned call in sputCostume_Initialize); was sputCostume_Start. */

undefined4 sputCostume_Startup(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  code **ppcVar2;
  #define local_38 (*(code *(*)[14])(_frame + (0x50 - 0x38)))
  
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  ppcVar2 = local_38 + 7;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  if (g_dwSputCosStartup != 0) {
    return 1;
  }
  (*(code *)UINT_008ca778)();
  g_pCostumePool = (void **)Memory_AllocatePool(0xb4,10,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = ThingChanger;
  local_38[1] = ThingRequester;
  local_38[2] = ThingFreer;
  local_38[3] = ThingStopper;
  local_38[4] = ThingAdjuster;
  local_38[5] = ThingInstancer;
  Cos_NewStateBasedTag(0x4c444d4d,IMG_ADDR(0x004ea3a0),0,(int *)local_38,2);
  Cos_NewStateBasedTag(0x4c444f4d,IMG_ADDR(0x004ea38c),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = Lua_Stub;
  local_38[1] = ColormapRequester;
  local_38[2] = ColormapFreer;
  local_38[3] = (code *)0x0;
  local_38[4] = (code *)0x0;
  local_38[5] = ColormapInstancer;
  Cos_NewStateBasedTag(0x70616d63,IMG_ADDR(0x004ea37c),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = MeshChanger;
  local_38[1] = MeshRequester;
  local_38[2] = CostumeTag_Nop;
  local_38[3] = MeshStopper;
  local_38[5] = MeshInstancer;
  local_38[4] = MeshAdjuster;
  Cos_NewStateBasedTag(0x4853454d,IMG_ADDR(0x004ea368),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = MaterialChanger;
  local_38[1] = MaterialRequester;
  local_38[2] = CostumeTag_Nop;
  local_38[3] = (code *)0x0;
  local_38[5] = MaterialInstancer;
  local_38[6] = MaterialInstanceSaveLoad;
  Cos_NewStateBasedTag(0x2054414d,IMG_ADDR(0x004ea34c),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = KeyframeChanger;
  local_38[1] = KeyframeRequester;
  local_38[2] = KeyframeFreer;
  local_38[3] = KeyframeStopper;
  local_38[4] = KeyframeAdjuster;
  local_38[5] = KeyframeInstancer;
  local_38[6] = (code *)0x0;
  Cos_NewStateBasedTag(0x4659454b,IMG_ADDR(0x004ea334),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = BitmapChanger;
  local_38[1] = BitmapRequester;
  local_38[2] = BitmapFreer;
  local_38[3] = (code *)0x0;
  local_38[4] = (code *)0x0;
  local_38[5] = (code *)0x0;
  Cos_NewStateBasedTag(0x444e4b42,IMG_ADDR(0x004ea324),0,(int *)local_38,1);
  Cos_NewStateBasedTag(0x6d696e61,IMG_ADDR(0x004ea308),0,(int *)local_38,1);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = SoundChanger;
  local_38[1] = SoundRequester;
  local_38[2] = SoundFreer;
  local_38[3] = SoundStopper;
  local_38[4] = SoundAdjuster;
  Cos_NewStateBasedTag(0x73736d69,IMG_ADDR(0x004ea2f0),0,(int *)local_38,2);
  Cos_NewStateBasedTag(0x736c6d69,IMG_ADDR(0x004ea2d8),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = SmushChanger;
  local_38[1] = SmushRequester;
  local_38[2] = SmushFreer;
  local_38[3] = (code *)0x0;
  local_38[4] = (code *)0x0;
  local_38[6] = CostumeTag_Nop;
  Cos_NewStateBasedTag(0x534d5348,IMG_ADDR(0x004ea2cc),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = SpriteChanger;
  local_38[1] = SpriteRequester;
  local_38[2] = SpriteFreer;
  local_38[3] = (code *)0x0;
  local_38[4] = SpriteAdjuster;
  local_38[5] = SpriteInstancer;
  Cos_NewStateBasedTag(0x74727073,IMG_ADDR(0x004ea2c4),0,(int *)local_38,2);
  local_38[4] = (code *)0x0;
  local_38[7] = Lua_Stub;
  local_38[8] = IMuseRequester;
  local_38[9] = CostumeTag_Nop;
  local_38[10] = (code *)0x0;
  Cos_NewIntTag(0x65736d69,IMG_ADDR(0x004ea2b4),0,(int *)(local_38 + 7),2);
  Cos_NewIntTag(0x74736d69,IMG_ADDR(0x004ea2a8),0,(int *)(local_38 + 7),2);
  local_38[7] = LuaVarChanger;
  local_38[8] = LuaVarRequester;
  local_38[9] = LuaVarFreer;
  local_38[10] = LuaVarStopper;
  local_38[0xb] = LuaVarAdjuster;
  Cos_NewIntTag(0x7661756c,IMG_ADDR(0x004ea298),0,(int *)(local_38 + 7),1);
  g_dwOldInstanceHook = Cos_RegisterInstanceHook(((unsigned)(uintptr_t)Costume_InstanceHook));
  g_dwOldSaveHook = Cos_RegisterSaveHook(((unsigned)(uintptr_t)Costume_SaveChoreListFile));
  sputLua_RegisterFunctions(&g_pLuaCostumeFuncs,UINT_004ea068);
  g_dwSputCosStartup = 1;
  Config_GetPath(s_KeyframePath_004ea27c,&g_bKeyframePath,s_Animation_004ea28c);
  Config_GetPath(s_ColormapPath_004ea260,&g_bColormapPath,s_Colormaps_004ea270);
  Config_GetPath(s_MaterialPath_004ea244,&g_bMaterialPath,s_Materials_004ea254);
  Config_GetPath(s_ModelPath_004ea230,&g_bModelPath,s_Models_004ea23c);
  Config_GetPath(s_SoundPath_004ea220,&g_bSoundPath,&DAT_004ea22c);
  Config_GetPath(s_SmushPath_004ea20c,&g_bSmushPath,s_Movies_004ea218);
  Config_GetPath(s_BitmapPath_004ea1f8,&g_bBitmapPath,s_Objects_004ea204);
  return 0;
}
#undef local_38


/* ---- 0x004988a0  sputCostume_Shutdown ---- */
/* Module interface slot 3 (sputCostume): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputCostume_Shutdown (the remaster's GrimFandango
   (Linux): the module's shutdown slot: writes keyframePath, bitmapPath, ... back to the
   configuration); was sputCostume_Stop. */

void sputCostume_Shutdown(void)

{
  Config_SetPath(s_KeyframePath_004ea27c,&g_bKeyframePath);
  Config_SetPath(s_BitmapPath_004ea1f8,&g_bBitmapPath);
  Config_SetPath(s_ColormapPath_004ea260,&g_bColormapPath);
  Config_SetPath(s_MaterialPath_004ea244,&g_bMaterialPath);
  Config_SetPath(s_ModelPath_004ea230,&g_bModelPath);
  Config_SetPath(s_SoundPath_004ea220,&g_bSoundPath);
  Config_SetPath(s_SmushPath_004ea20c,&g_bSmushPath);
  if (g_pCostumePool != (void **)0x0) {
    Memory_FreePool(g_pCostumePool);
    g_pCostumePool = (void **)0x0;
  }
  g_dwOldInstanceHook = Cos_RegisterInstanceHook(g_dwOldInstanceHook);
  g_dwOldSaveHook = Cos_RegisterSaveHook(g_dwOldSaveHook);
  if (g_dwLECBitmaps != 0) {
    (*g_pSputCosHS->pFree)(g_dwLECBitmaps);
  }
  (*(code *)UINT_008ca77c)();
  g_dwSputCosStartup = 0;
  return;
}
