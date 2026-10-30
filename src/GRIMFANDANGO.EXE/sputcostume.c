/* GRIMFANDANGO.EXE :: sputcostume.c
 * functions 0x004957f0 .. 0x004988a0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004957f0  sputCostume_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

bool sputCostume_Initialize(GrimServices *param_1,undefined4 *param_2)

{
  int iVar1;
  
  g_pSvcCostume = param_1;
  *param_2 = sputCostume_Initialize;
  param_2[1] = sputCostume_Terminate;
  param_2[2] = sputCostume_Start;
  param_2[3] = sputCostume_Stop;
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  iVar1 = Cos_Initialize((int)param_1,(int *)&DAT_008ca770);
  UINT_008ca798 = (uint)(iVar1 == 0);
  return iVar1 != 0;
}

/* ---- 0x00495960  sputCostume_Terminate ---- */
/* Module interface slot 1 (sputCostume): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. */

void sputCostume_Terminate(void)

{
  g_pSvcCostume = (GrimServices *)0x0;
  if (UINT_008ca798 != 0) {
    UINT_008ca798 = 0;
    (*(code *)UINT_008ca774)();
    if (g_pShadowColormap != (void *)0x0) {
      rdColormap_Free(g_pShadowColormap);
    }
  }
  return;
}

/* ---- 0x004959a0  sputCostume_Start ---- */
/* Module interface slot 2 (sputCostume): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind).  */

undefined4 sputCostume_Start(void)

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
  if (UINT_008ca79c != 0) {
    return 1;
  }
  (*(code *)UINT_008ca778)();
  g_pCostumePool = (void **)Pool_Create(0xb4,10,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = ModelComponent_SetVisibleFlag;
  local_38[1] = ModelComponent_Create;
  local_38[2] = ModelComponent_Destroy;
  local_38[3] = ModelComponent_Stop;
  local_38[4] = ModelComponent_EditParentOffset;
  local_38[5] = ModelComponent_NewInstance;
  Cos_NewStateBasedTag(0x4c444d4d,IMG_ADDR(0x004ea3a0),0,(int *)local_38,2);
  Cos_NewStateBasedTag(0x4c444f4d,IMG_ADDR(0x004ea38c),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = Lua_Stub;
  local_38[1] = CmapComponent_Create;
  local_38[2] = CmapComponent_Destroy;
  local_38[3] = (code *)0x0;
  local_38[4] = (code *)0x0;
  local_38[5] = CmapComponent_NewInstance;
  Cos_NewStateBasedTag(0x70616d63,IMG_ADDR(0x004ea37c),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = MeshComponent_OnKey;
  local_38[1] = MeshComponent_Create;
  local_38[2] = CostumeTag_Nop;
  local_38[3] = MeshComponent_Stop;
  local_38[5] = MeshComponent_NewInstance;
  local_38[4] = FUN_00497180;
  Cos_NewStateBasedTag(0x4853454d,IMG_ADDR(0x004ea368),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = MaterialComponent_OnKey;
  local_38[1] = MaterialComponent_Create;
  local_38[2] = CostumeTag_Nop;
  local_38[3] = (code *)0x0;
  local_38[5] = MaterialComponent_NewInstance;
  local_38[6] = FUN_004965b0;
  Cos_NewStateBasedTag(0x2054414d,IMG_ADDR(0x004ea34c),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = KeyframeComponent_OnKey;
  local_38[1] = KeyframeComponent_Create;
  local_38[2] = KeyframeComponent_Destroy;
  local_38[3] = KeyframeComponent_Stop;
  local_38[4] = KeyframeComponent_EditKey;
  local_38[5] = KeyframeComponent_NewInstance;
  local_38[6] = (code *)0x0;
  Cos_NewStateBasedTag(0x4659454b,IMG_ADDR(0x004ea334),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = Component_SetBitmapFrame;
  local_38[1] = BitmapComponent_Create;
  local_38[2] = BitmapComponent_Destroy;
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
  local_38[0] = ImuseSoundComponent_OnKey;
  local_38[1] = ImuseSoundComponent_Create;
  local_38[2] = ImuseSoundComponent_Destroy;
  local_38[3] = ImuseSoundComponent_Stop;
  local_38[4] = ImuseSoundComponent_EditKey;
  Cos_NewStateBasedTag(0x73736d69,IMG_ADDR(0x004ea2f0),0,(int *)local_38,2);
  Cos_NewStateBasedTag(0x736c6d69,IMG_ADDR(0x004ea2d8),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = SmushComponent_OnKey;
  local_38[1] = SmushComponent_Create;
  local_38[2] = SmushComponent_Destroy;
  local_38[3] = (code *)0x0;
  local_38[4] = (code *)0x0;
  local_38[6] = CostumeTag_Nop;
  Cos_NewStateBasedTag(0x534d5348,IMG_ADDR(0x004ea2cc),0,(int *)local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = SpriteComponent_OnKey;
  local_38[1] = SpriteComponent_Create;
  local_38[2] = SpriteComponent_Destroy;
  local_38[3] = (code *)0x0;
  local_38[4] = SpriteComponent_EditKey;
  local_38[5] = FUN_004985c0;
  Cos_NewStateBasedTag(0x74727073,IMG_ADDR(0x004ea2c4),0,(int *)local_38,2);
  local_38[4] = (code *)0x0;
  local_38[7] = Lua_Stub;
  local_38[8] = ImuseIntComponent_Create;
  local_38[9] = CostumeTag_Nop;
  local_38[10] = (code *)0x0;
  Cos_NewIntTag(0x65736d69,IMG_ADDR(0x004ea2b4),0,(int *)(local_38 + 7),2);
  Cos_NewIntTag(0x74736d69,IMG_ADDR(0x004ea2a8),0,(int *)(local_38 + 7),2);
  local_38[7] = LuaVarComponent_OnKey;
  local_38[8] = LuaVarComponent_Create;
  local_38[9] = LuaVarComponent_Destroy;
  local_38[10] = LuaVarComponent_Stop;
  local_38[0xb] = LuaVarComponent_EditKey;
  Cos_NewIntTag(0x7661756c,IMG_ADDR(0x004ea298),0,(int *)(local_38 + 7),1);
  UINT_008ca7ac = Cos_RegisterInstanceHook(((unsigned)(uintptr_t)Costume_InstanceHook));
  UINT_008ca7b0 = Cos_RegisterSaveHook(((unsigned)(uintptr_t)Costume_SaveChoreListFile));
  Lua_OpenEngineLib(&PTR_s_GetKeyLength_004ea058,UINT_004ea068);
  UINT_008ca79c = 1;
  Config_GetPath(s_KeyframePath_004ea27c,&DAT_008ca7b8,s_Animation_004ea28c);
  Config_GetPath(s_ColormapPath_004ea260,&DAT_008ca8b8,s_Colormaps_004ea270);
  Config_GetPath(s_MaterialPath_004ea244,&DAT_008ca938,s_Materials_004ea254);
  Config_GetPath(s_ModelPath_004ea230,&DAT_008ca9b8,s_Models_004ea23c);
  Config_GetPath(s_SoundPath_004ea220,&DAT_008caa38,&DAT_004ea22c);
  Config_GetPath(s_SmushPath_004ea20c,&DAT_008caab8,s_Movies_004ea218);
  Config_GetPath(s_BitmapPath_004ea1f8,&DAT_008ca838,s_Objects_004ea204);
  return 0;
}
#undef local_38


/* ---- 0x004988a0  sputCostume_Stop ---- */
/* Module interface slot 3 (sputCostume): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. */

void sputCostume_Stop(void)

{
  Config_SetPath(s_KeyframePath_004ea27c,&DAT_008ca7b8);
  Config_SetPath(s_BitmapPath_004ea1f8,&DAT_008ca838);
  Config_SetPath(s_ColormapPath_004ea260,&DAT_008ca8b8);
  Config_SetPath(s_MaterialPath_004ea244,&DAT_008ca938);
  Config_SetPath(s_ModelPath_004ea230,&DAT_008ca9b8);
  Config_SetPath(s_SoundPath_004ea220,&DAT_008caa38);
  Config_SetPath(s_SmushPath_004ea20c,&DAT_008caab8);
  if (g_pCostumePool != (void **)0x0) {
    Pool_Destroy(g_pCostumePool);
    g_pCostumePool = (void **)0x0;
  }
  UINT_008ca7ac = Cos_RegisterInstanceHook(UINT_008ca7ac);
  UINT_008ca7b0 = Cos_RegisterSaveHook(UINT_008ca7b0);
  if (UINT_008ca7a4 != 0) {
    (*g_pSvcCostume->pFree)(UINT_008ca7a4);
  }
  (*(code *)UINT_008ca77c)();
  UINT_008ca79c = 0;
  return;
}
