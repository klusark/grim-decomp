/* GRIMFANDANGO.EXE :: sputcostume.c
 * functions 0x004957f0 .. 0x004988a0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004957f0  sputCostume_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

int __cdecl sputCostume_Initialize(GrimServices *services,undefined4 *iface)

{
  int iVar1;
  
  g_pSputCosHS = services;
  *iface = sputCostume_Initialize;
  iface[1] = sputCostume_Terminate;
  iface[2] = sputCostume_Startup;
  iface[3] = sputCostume_Shutdown;
  iface[4] = 0;
  iface[5] = 0;
  iface[6] = 0;
  iface[7] = 0;
  iVar1 = Cos_Initialize((int)services,(int *)&g_aChoreMS);
  g_dwSputCosInitialize = (uint)(iVar1 == 0);
  return (uint)(iVar1 != 0);
}

/* ---- 0x00495960  sputCostume_Terminate ---- */
/* Module interface slot 1 (sputCostume): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. */

void __cdecl sputCostume_Terminate(void)

{
  g_pSputCosHS = (GrimServices *)0x0;
  if (g_dwSputCosInitialize != 0) {
    g_dwSputCosInitialize = 0;
    (*g_aChoreMS.pfnTerminate)();
    if (g_pShadowColormap != (rdColormap *)0x0) {
      rdColormap_Free((uint)g_pShadowColormap);
    }
  }
  return;
}

/* ---- 0x004959a0  sputCostume_Startup ---- */
/* Module interface slot 2 (sputCostume): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). Original name sputCostume_Startup (the remaster's
   GrimFandango (Linux): aligned call in sputCostume_Initialize); was sputCostume_Start. */

uint __cdecl sputCostume_Startup(void)

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
  (*g_aChoreMS.pfnStartup)();
  g_pCosNodePool = Memory_AllocatePool(0xb4,(void *)0xa,(void *)0x2);
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
  Cos_NewStateBasedTag(0x4c444d4d,((unsigned)(uintptr_t)&DAT_004ea3a0),0,(int *)local_38,2);
  Cos_NewStateBasedTag(0x4c444f4d,((unsigned)(uintptr_t)&DAT_004ea38c),0,(int *)local_38,2);
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
  Cos_NewStateBasedTag(0x70616d63,((unsigned)(uintptr_t)&s_RDroid_Colormap_004ea37c),0,(int *)local_38,2);
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
  Cos_NewStateBasedTag(0x4853454d,((unsigned)(uintptr_t)&s_RDroid_Thing_Mesh_004ea368),0,(int *)local_38,2);
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
  Cos_NewStateBasedTag(0x2054414d,((unsigned)(uintptr_t)&s_RDroid_Animated_Material_004ea34c),0,(int *)local_38,2);
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
  Cos_NewStateBasedTag(0x4659454b,((unsigned)(uintptr_t)&DAT_004ea334),0,(int *)local_38,2);
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
  Cos_NewStateBasedTag(0x444e4b42,((unsigned)(uintptr_t)&s_General_Bitmap_004ea324),0,(int *)local_38,1);
  Cos_NewStateBasedTag(0x6d696e61,((unsigned)(uintptr_t)&DAT_004ea308),0,(int *)local_38,1);
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
  Cos_NewStateBasedTag(0x73736d69,((unsigned)(uintptr_t)&s_iMuse_Streamed_Sound_FX_004ea2f0),0,(int *)local_38,2);
  Cos_NewStateBasedTag(0x736c6d69,((unsigned)(uintptr_t)&s_iMuse_Resident_Sound_FX_004ea2d8),0,(int *)local_38,2);
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
  Cos_NewStateBasedTag(0x534d5348,((unsigned)(uintptr_t)&s_Smush_Movie_004ea2cc),0,(int *)local_38,2);
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
  Cos_NewStateBasedTag(0x74727073,((unsigned)(uintptr_t)&s_Sprite_004ea2c4),0,(int *)local_38,2);
  local_38[4] = (code *)0x0;
  local_38[7] = Lua_Stub;
  local_38[8] = IMuseRequester;
  local_38[9] = CostumeTag_Nop;
  local_38[10] = (code *)0x0;
  Cos_NewIntTag(0x65736d69,((unsigned)(uintptr_t)&s_iMuse_Sequence_004ea2b4),0,(int *)(local_38 + 7),2);
  Cos_NewIntTag(0x74736d69,((unsigned)(uintptr_t)&s_iMuse_State_004ea2a8),0,(int *)(local_38 + 7),2);
  local_38[7] = LuaVarChanger;
  local_38[8] = LuaVarRequester;
  local_38[9] = LuaVarFreer;
  local_38[10] = LuaVarStopper;
  local_38[0xb] = LuaVarAdjuster;
  Cos_NewIntTag(0x7661756c,((unsigned)(uintptr_t)&s_Lua_Variable_004ea298),0,(int *)(local_38 + 7),1);
  g_dwOldInstanceHook = Cos_RegisterInstanceHook(((unsigned)(uintptr_t)Costume_InstanceHook));
  g_dwOldSaveHook = Cos_RegisterSaveHook(((unsigned)(uintptr_t)sputCostume_SaveHook));
  sputLua_RegisterFunctions((int *)&g_pLuaCostumeFuncs,UINT_004ea068);
  g_dwSputCosStartup = 1;
  Config_GetPath(s_KeyframePath_004ea27c,&g_bKeyframePath,s_Animation_004ea28c);
  Config_GetPath(s_ColormapPath_004ea260,&g_bColormapPath,s_Colormaps_004ea270);
  Config_GetPath(s_MaterialPath_004ea244,&g_bMaterialPath,s_Materials_004ea254);
  Config_GetPath(s_ModelPath_004ea230,&g_bModelPath,s_Models_004ea23c);
  Config_GetPath(s_SoundPath_004ea220,&g_bSoundPath,s_SFX_004ea22c);
  Config_GetPath(s_SmushPath_004ea20c,g_bSmushPath,s_Movies_004ea218);
  Config_GetPath(s_BitmapPath_004ea1f8,&g_bBitmapPath,s_Objects_004ea204);
  return 0;
}
#undef local_38


/* ---- 0x004988a0  sputCostume_Shutdown ---- */
/* Module interface slot 3 (sputCostume): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputCostume_Shutdown (the remaster's GrimFandango
   (Linux): the module's shutdown slot: writes keyframePath, bitmapPath, ... back to the
   configuration); was sputCostume_Stop. */

void __cdecl sputCostume_Shutdown(void)

{
  Config_SetPath(s_KeyframePath_004ea27c,&g_bKeyframePath);
  Config_SetPath(s_BitmapPath_004ea1f8,&g_bBitmapPath);
  Config_SetPath(s_ColormapPath_004ea260,&g_bColormapPath);
  Config_SetPath(s_MaterialPath_004ea244,&g_bMaterialPath);
  Config_SetPath(s_ModelPath_004ea230,&g_bModelPath);
  Config_SetPath(s_SoundPath_004ea220,&g_bSoundPath);
  Config_SetPath(s_SmushPath_004ea20c,g_bSmushPath);
  if (g_pCosNodePool != (void **)0x0) {
    Memory_FreePool(g_pCosNodePool);
    g_pCosNodePool = (void **)0x0;
  }
  g_dwOldInstanceHook = Cos_RegisterInstanceHook(g_dwOldInstanceHook);
  g_dwOldSaveHook = Cos_RegisterSaveHook(g_dwOldSaveHook);
  if (g_dwLECBitmaps != 0) {
    (*g_pSputCosHS->pFree)(g_dwLECBitmaps);
  }
  (*g_aChoreMS.pfnShutdown)();
  g_dwSputCosStartup = 0;
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char f_sputCostume_GetKeyLengthL[] __asm__("_sputCostume_GetKeyLengthL");
extern char f_sputCostume_GetSmushLengthL[] __asm__("_sputCostume_GetSmushLengthL");
extern unsigned char grim_def_DAT_004ea308[28] __asm__("_DAT_004ea308");
extern unsigned char grim_def_DAT_004ea334[24] __asm__("_DAT_004ea334");
extern unsigned char grim_def_DAT_004ea38c[20] __asm__("_DAT_004ea38c");
extern unsigned char grim_def_DAT_004ea3a0[28] __asm__("_DAT_004ea3a0");
extern unsigned int grim_def_UINT_004ea068 __asm__("_UINT_004ea068");
extern SysModuleIface grim_def_g_aChoreMS __asm__("_g_aChoreMS");
extern unsigned int grim_def_g_dwOldInstanceHook __asm__("_g_dwOldInstanceHook");
extern unsigned int grim_def_g_dwOldSaveHook __asm__("_g_dwOldSaveHook");
extern unsigned int grim_def_g_dwSputCosInitialize __asm__("_g_dwSputCosInitialize");
extern unsigned int grim_def_g_dwSputCosStartup __asm__("_g_dwSputCosStartup");
extern void *grim_def_g_pLuaCostumeFuncs[4] __asm__("_g_pLuaCostumeFuncs");
extern char grim_def_s_Animation_004ea28c[12] __asm__("_s_Animation_004ea28c");
extern char grim_def_s_BitmapPath_004ea1f8[12] __asm__("_s_BitmapPath_004ea1f8");
extern char grim_def_s_ColormapPath_004ea260[16] __asm__("_s_ColormapPath_004ea260");
extern char grim_def_s_Colormaps_004ea270[12] __asm__("_s_Colormaps_004ea270");
extern char grim_def_s_General_Bitmap_004ea324[16] __asm__("_s_General_Bitmap_004ea324");
extern char grim_def_s_GetKeyLength_004ea07c[] __asm__("_s_GetKeyLength_004ea07c");
extern char grim_def_s_GetSmushLength_004ea06c[] __asm__("_s_GetSmushLength_004ea06c");
extern char grim_def_s_KeyframePath_004ea27c[16] __asm__("_s_KeyframePath_004ea27c");
extern char grim_def_s_Lua_Variable_004ea298[16] __asm__("_s_Lua_Variable_004ea298");
extern char grim_def_s_MaterialPath_004ea244[16] __asm__("_s_MaterialPath_004ea244");
extern char grim_def_s_Materials_004ea254[12] __asm__("_s_Materials_004ea254");
extern char grim_def_s_ModelPath_004ea230[12] __asm__("_s_ModelPath_004ea230");
extern char grim_def_s_Models_004ea23c[8] __asm__("_s_Models_004ea23c");
extern char grim_def_s_Movies_004ea218[8] __asm__("_s_Movies_004ea218");
extern char grim_def_s_Objects_004ea204[8] __asm__("_s_Objects_004ea204");
extern char grim_def_s_RDroid_Animated_Material_004ea34c[28] __asm__("_s_RDroid_Animated_Material_004ea34c");
extern char grim_def_s_RDroid_Colormap_004ea37c[16] __asm__("_s_RDroid_Colormap_004ea37c");
extern char grim_def_s_RDroid_Thing_Mesh_004ea368[20] __asm__("_s_RDroid_Thing_Mesh_004ea368");
extern char grim_def_s_SFX_004ea22c[4] __asm__("_s_SFX_004ea22c");
extern char grim_def_s_SmushPath_004ea20c[12] __asm__("_s_SmushPath_004ea20c");
extern char grim_def_s_Smush_Movie_004ea2cc[12] __asm__("_s_Smush_Movie_004ea2cc");
extern char grim_def_s_SoundPath_004ea220[12] __asm__("_s_SoundPath_004ea220");
extern char grim_def_s_Sprite_004ea2c4[8] __asm__("_s_Sprite_004ea2c4");
extern char grim_def_s_iMuse_Resident_Sound_FX_004ea2d8[24] __asm__("_s_iMuse_Resident_Sound_FX_004ea2d8");
extern char grim_def_s_iMuse_Streamed_Sound_FX_004ea2f0[24] __asm__("_s_iMuse_Streamed_Sound_FX_004ea2f0");
/* 0x004ea058, 16 bytes */ GRIM_DATA("004ea058") void *grim_def_g_pLuaCostumeFuncs[4] __asm__("_g_pLuaCostumeFuncs") = {
    (void *)&grim_def_s_GetKeyLength_004ea07c, (void *)f_sputCostume_GetKeyLengthL, (void *)&grim_def_s_GetSmushLength_004ea06c, (void *)f_sputCostume_GetSmushLengthL
};
/* 0x004ea068, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004ea068 __asm__("_UINT_004ea068") = 0x2;
/* 0x004ea1f8, 12 bytes */ /* loose */ char grim_def_s_BitmapPath_004ea1f8[12] __asm__("_s_BitmapPath_004ea1f8") = "BitmapPath";
/* 0x004ea204, 8 bytes */ /* loose */ char grim_def_s_Objects_004ea204[8] __asm__("_s_Objects_004ea204") = "Objects";
/* 0x004ea20c, 12 bytes */ /* loose */ char grim_def_s_SmushPath_004ea20c[12] __asm__("_s_SmushPath_004ea20c") = "SmushPath";
/* 0x004ea218, 8 bytes */ /* loose */ char grim_def_s_Movies_004ea218[8] __asm__("_s_Movies_004ea218") = "Movies";
/* 0x004ea220, 12 bytes */ /* loose */ char grim_def_s_SoundPath_004ea220[12] __asm__("_s_SoundPath_004ea220") = "SoundPath";
/* 0x004ea22c, 4 bytes */ /* loose */ char grim_def_s_SFX_004ea22c[4] __asm__("_s_SFX_004ea22c") = "SFX";
/* 0x004ea230, 12 bytes */ /* loose */ char grim_def_s_ModelPath_004ea230[12] __asm__("_s_ModelPath_004ea230") = "ModelPath";
/* 0x004ea23c, 8 bytes */ /* loose */ char grim_def_s_Models_004ea23c[8] __asm__("_s_Models_004ea23c") = "Models";
/* 0x004ea244, 16 bytes */ /* loose */ char grim_def_s_MaterialPath_004ea244[16] __asm__("_s_MaterialPath_004ea244") = "MaterialPath";
/* 0x004ea254, 12 bytes */ /* loose */ char grim_def_s_Materials_004ea254[12] __asm__("_s_Materials_004ea254") = "Materials";
/* 0x004ea260, 16 bytes */ /* loose */ char grim_def_s_ColormapPath_004ea260[16] __asm__("_s_ColormapPath_004ea260") = "ColormapPath";
/* 0x004ea270, 12 bytes */ /* loose */ char grim_def_s_Colormaps_004ea270[12] __asm__("_s_Colormaps_004ea270") = "Colormaps";
/* 0x004ea27c, 16 bytes */ /* loose */ char grim_def_s_KeyframePath_004ea27c[16] __asm__("_s_KeyframePath_004ea27c") = "KeyframePath";
/* 0x004ea28c, 12 bytes */ /* loose */ char grim_def_s_Animation_004ea28c[12] __asm__("_s_Animation_004ea28c") = "Animation";
/* 0x004ea298, 16 bytes */ /* loose */ char grim_def_s_Lua_Variable_004ea298[16] __asm__("_s_Lua_Variable_004ea298") = "Lua Variable";
/* 0x004ea2c4, 8 bytes */ /* loose */ char grim_def_s_Sprite_004ea2c4[8] __asm__("_s_Sprite_004ea2c4") = "Sprite";
/* 0x004ea2cc, 12 bytes */ /* loose */ char grim_def_s_Smush_Movie_004ea2cc[12] __asm__("_s_Smush_Movie_004ea2cc") = "Smush Movie";
/* 0x004ea2d8, 24 bytes */ /* loose */ char grim_def_s_iMuse_Resident_Sound_FX_004ea2d8[24] __asm__("_s_iMuse_Resident_Sound_FX_004ea2d8") = "iMuse Resident Sound FX";
/* 0x004ea2f0, 24 bytes */ /* loose */ char grim_def_s_iMuse_Streamed_Sound_FX_004ea2f0[24] __asm__("_s_iMuse_Streamed_Sound_FX_004ea2f0") = "iMuse Streamed Sound FX";
static unsigned char grim_anchor_004ea308[0] __attribute__((section(".data$grim_004ea308"), aligned(16), used));
static unsigned char grim_pad_004ea308[8] __attribute__((section(".data$grim_004ea308_"), aligned(4), used));
/* 0x004ea308, 28 bytes */ GRIM_DATA("004ea308z") unsigned char grim_def_DAT_004ea308[28] __asm__("_DAT_004ea308") = {
    0x41, 0x6e, 0x69, 0x6d, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x28, 0x6f, 0x6c, 0x64, 0x2c, 0x75,
    0x73, 0x65, 0x20, 0x42, 0x69, 0x74, 0x6d, 0x61, 0x70, 0x29
};
/* 0x004ea324, 16 bytes */ GRIM_DATA("004ea324") char grim_def_s_General_Bitmap_004ea324[16] __asm__("_s_General_Bitmap_004ea324") = "General Bitmap";
/* 0x004ea334, 24 bytes */ GRIM_DATA("004ea334") unsigned char grim_def_DAT_004ea334[24] __asm__("_DAT_004ea334") = {
    0x52, 0x44, 0x72, 0x6f, 0x69, 0x64, 0x20, 0x4b, 0x65, 0x79, 0x66, 0x72, 0x61, 0x6d, 0x65, 0x20,
    0x28, 0x2e, 0x4b, 0x45, 0x59, 0x29
};
/* 0x004ea34c, 28 bytes */ GRIM_DATA("004ea34c") char grim_def_s_RDroid_Animated_Material_004ea34c[28] __asm__("_s_RDroid_Animated_Material_004ea34c") = "RDroid Animated Material";
/* 0x004ea368, 20 bytes */ /* loose */ char grim_def_s_RDroid_Thing_Mesh_004ea368[20] __asm__("_s_RDroid_Thing_Mesh_004ea368") = "RDroid Thing Mesh";
/* 0x004ea37c, 16 bytes */ /* loose */ char grim_def_s_RDroid_Colormap_004ea37c[16] __asm__("_s_RDroid_Colormap_004ea37c") = "RDroid Colormap";
static unsigned char grim_anchor_004ea38c[0] __attribute__((section(".data$grim_004ea38c"), aligned(16), used));
static unsigned char grim_pad_004ea38c[12] __attribute__((section(".data$grim_004ea38c_"), aligned(4), used));
/* 0x004ea38c, 20 bytes */ GRIM_DATA("004ea38cz") unsigned char grim_def_DAT_004ea38c[20] __asm__("_DAT_004ea38c") = {
    0x52, 0x44, 0x72, 0x6f, 0x69, 0x64, 0x20, 0x54, 0x68, 0x69, 0x6e, 0x67, 0x20, 0x28, 0x2e, 0x33,
    0x44, 0x4f, 0x29
};
/* 0x004ea3a0, 28 bytes */ GRIM_DATA("004ea3a0") unsigned char grim_def_DAT_004ea3a0[28] __asm__("_DAT_004ea3a0") = {
    0x4d, 0x41, 0x49, 0x4e, 0x20, 0x52, 0x44, 0x72, 0x6f, 0x69, 0x64, 0x20, 0x54, 0x68, 0x69, 0x6e,
    0x67, 0x20, 0x28, 0x2e, 0x33, 0x44, 0x4f, 0x29
};
static unsigned char grim_anchor_008ca770[0] __attribute__((section(".data$grim_008ca770"), aligned(16), used));
static unsigned char grim_pad_008ca770[0] __attribute__((section(".data$grim_008ca770_"), aligned(4), used));
/* 0x008ca770, 32 bytes */ GRIM_DATA("008ca770z") SysModuleIface grim_def_g_aChoreMS __asm__("_g_aChoreMS") = {0};
/* 0x008ca798, 4 bytes */ /* loose */ unsigned int grim_def_g_dwSputCosInitialize __asm__("_g_dwSputCosInitialize") = 0x0;
/* 0x008ca79c, 4 bytes */ /* loose */ unsigned int grim_def_g_dwSputCosStartup __asm__("_g_dwSputCosStartup") = 0x0;
/* 0x008ca7ac, 4 bytes */ /* loose */ unsigned int grim_def_g_dwOldInstanceHook __asm__("_g_dwOldInstanceHook") = 0x0;
/* 0x008ca7b0, 4 bytes */ /* loose */ unsigned int grim_def_g_dwOldSaveHook __asm__("_g_dwOldSaveHook") = 0x0;
