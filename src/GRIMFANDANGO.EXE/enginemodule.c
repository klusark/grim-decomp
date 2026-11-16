/* GRIMFANDANGO.EXE :: enginemodule.c
 * functions 0x00482540 .. 0x00482cc0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00482540  grimlib_GameInitialize ---- */
/* Fills the engine module interface and registers the two Lua/engine callback tables (8 + 6
   entries) Original name grimlib_GameInitialize (the remaster's GrimFandango (Linux): the
   module-interface filler Main_Startup calls with hs and ms, same slots (itself, terminate,
   grimlib_GameStartup, shutdown) and base-module loop); was EngineModule_Init. */

undefined * __cdecl grimlib_GameInitialize(GrimServices *services,undefined **iface)

{
  undefined *puVar1;
  
  g_pSputmHS = services;
  *iface = grimlib_GameInitialize;
  iface[1] = grimlib_GameTerminate;
  iface[2] = grimlib_GameStartup;
  iface[3] = grimlib_GameShutdown;
  iface[4] = (undefined *)0x0;
  iface[5] = (undefined *)0x0;
  iface[6] = (undefined *)0x0;
  iface[7] = (undefined *)0x0;
  puVar1 = (undefined *)
           Engine_RegisterSubsystems((uint)services,&PTR_FileUtil_SysInitialize_004e7dc0,((unsigned)(uintptr_t)&g_aGrimlib_Filenames),8)
  ;
  if (puVar1 == (undefined *)0x0) {
    puVar1 = (undefined *)
             Engine_RegisterSubsystems
                       ((uint)services,&PTR_sputControl_Initialize_004e7e00,((unsigned)(uintptr_t)&g_aBaseModuleServices),6);
  }
  g_dwSputmInitialize = (uint)(puVar1 == (undefined *)0x0);
  return puVar1;
}

/* ---- 0x00482b60  grimlib_GameTerminate ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Module interface slot 1 (EngineModule): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. Original name
   grimlib_GameTerminate (the remaster's GrimFandango (Linux): the terminate slot
   grimlib_GameInitialize fills, same body (clears psputmHS, undoes the modules when
   bsputmInitialize)); was EngineModule_Terminate. */

undefined * grimlib_GameTerminate(void)

{
  undefined *puVar1;
  
  g_pSputmHS = (GrimServices *)0x0;
  puVar1 = (undefined *)0x0;
  if (g_dwSputmInitialize != 0) {
    Engine_ResetSubsystems(((unsigned)(uintptr_t)&g_aBaseModuleServices),6);
    puVar1 = (undefined *)Engine_ResetSubsystems(((unsigned)(uintptr_t)&g_aGrimlib_Filenames),8);
    g_dwSputmInitialize = 0;
  }
  return puVar1;
}

/* ---- 0x00482ba0  grimlib_GameStartup ---- */
/* Module interface slot 2 (EngineModule): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). Original name grimlib_GameStartup (the remaster's
   GrimFandango (Linux): the only unmatched caller of Plat_GetPhysicalMemory; 1 matched neighbours
   agree, 0 disagree); was EngineModule_Start. */

int __cdecl grimlib_GameStartup(void)

{
  uint uVar1;
  uint uVar2;
  
  if (g_dwSputmStartup != 0) {
    return 1;
  }
  uVar1 = Engine_InitSubsystems(((unsigned)(uintptr_t)&g_aGrimlib_Filenames),8);
  if (uVar1 == 0) {
    uVar1 = DSound_Init();
    if (uVar1 == 0) {
      return 1;
    }
    uVar1 = stdPlatform_GetPhysicalRam();
    if ((int)uVar1 < 0x1000001) {
      iMUSE_DeclareBufferSizes(88000,44000,88000,440000,44000,0x55f00,100000,1,0xac44,2,300000,6);
      uVar1 = 0xa00000;
    }
    else {
      iMUSE_DeclareBufferSizes(88000,44000,88000,440000,44000,0x55f00,100000,1,0xac44,2,300000,9);
      uVar2 = stdPlatform_GetPhysicalRam();
      uVar1 = g_dwMax_ram;
      if ((int)(uVar2 - 0x800000) <= (int)g_dwMax_ram) {
        uVar1 = stdPlatform_GetPhysicalRam();
        uVar1 = uVar1 - 0x800000;
      }
    }
    sputResource_SetMemoryUsage(uVar1,0);
    Sounds_PlatformDevice((int)g_pDirectSound);
    uVar1 = Engine_InitSubsystems(((unsigned)(uintptr_t)&g_aBaseModuleServices),6);
  }
  g_dwSputmStartup = (uint)(uVar1 == 0);
  return uVar1;
}

/* ---- 0x00482cc0  grimlib_GameShutdown ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Module interface slot 3 (EngineModule): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name grimlib_GameShutdown (the remaster's GrimFandango
   (Linux): the shutdown slot grimlib_GameInitialize fills (shuts the modules down in reverse)); was
   EngineModule_Stop. */

undefined * grimlib_GameShutdown(void)

{
  undefined *puVar1;
  
  Engine_ShutdownSubsystems(((unsigned)(uintptr_t)&g_aBaseModuleServices),6);
  DSound_Shutdown();
  puVar1 = (undefined *)Engine_ShutdownSubsystems(((unsigned)(uintptr_t)&g_aGrimlib_Filenames),8);
  g_dwSputmStartup = 0;
  return puVar1;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char f_FileUtil_SysInitialize[] __asm__("_FileUtil_SysInitialize");
extern char f_Memory_SysInitialize[] __asm__("_Memory_SysInitialize");
extern char f_SoundsInitialize[] __asm__("_SoundsInitialize");
extern char f_sputActor_Initialize[] __asm__("_sputActor_Initialize");
extern char f_sputControl_Initialize[] __asm__("_sputControl_Initialize");
extern char f_sputCostume_Initialize[] __asm__("_sputCostume_Initialize");
extern char f_sputLua_Initialize[] __asm__("_sputLua_Initialize");
extern char f_sputPrimitive_Initialize[] __asm__("_sputPrimitive_Initialize");
extern char f_sputRender_Initialize[] __asm__("_sputRender_Initialize");
extern char f_sputResource_Initialize[] __asm__("_sputResource_Initialize");
extern char f_sputRoom_Initialize[] __asm__("_sputRoom_Initialize");
extern char f_sputSmush_Initialize[] __asm__("_sputSmush_Initialize");
extern char f_sputText_Initialize[] __asm__("_sputText_Initialize");
extern char f_sputTime_Initialize[] __asm__("_sputTime_Initialize");
extern void *grim_def_PTR_FileUtil_SysInitialize_004e7dc0[16] __asm__("_PTR_FileUtil_SysInitialize_004e7dc0");
extern void *grim_def_PTR_sputControl_Initialize_004e7e00[12] __asm__("_PTR_sputControl_Initialize_004e7e00");
extern unsigned int grim_def_g_dwSputmInitialize __asm__("_g_dwSputmInitialize");
extern unsigned int grim_def_g_dwSputmStartup __asm__("_g_dwSputmStartup");
extern char grim_def_s_FileUtil_SysInitialize_004e7f5c[] __asm__("_s_FileUtil_SysInitialize_004e7f5c");
extern char grim_def_s_Memory_SysInitialize_004e7f44[] __asm__("_s_Memory_SysInitialize_004e7f44");
extern char grim_def_s_SoundsInitialize_004e7e94[] __asm__("_s_SoundsInitialize_004e7e94");
extern char grim_def_s_sputActor_Initialize_004e7ed8[] __asm__("_s_sputActor_Initialize_004e7ed8");
extern char grim_def_s_sputControl_Initialize_004e7ea8[] __asm__("_s_sputControl_Initialize_004e7ea8");
extern char grim_def_s_sputCostume_Initialize_004e7ef0[] __asm__("_s_sputCostume_Initialize_004e7ef0");
extern char grim_def_s_sputLua_Initialize_004e7f08[] __asm__("_s_sputLua_Initialize_004e7f08");
extern char grim_def_s_sputPrimitive_Initialize_004e7e4c[] __asm__("_s_sputPrimitive_Initialize_004e7e4c");
extern char grim_def_s_sputRender_Initialize_004e7e7c[] __asm__("_s_sputRender_Initialize_004e7e7c");
extern char grim_def_s_sputResource_Initialize_004e7ec0[] __asm__("_s_sputResource_Initialize_004e7ec0");
extern char grim_def_s_sputRoom_Initialize_004e7f30[] __asm__("_s_sputRoom_Initialize_004e7f30");
extern char grim_def_s_sputSmush_Initialize_004e7e34[] __asm__("_s_sputSmush_Initialize_004e7e34");
extern char grim_def_s_sputText_Initialize_004e7e68[] __asm__("_s_sputText_Initialize_004e7e68");
extern char grim_def_s_sputTime_Initialize_004e7f1c[] __asm__("_s_sputTime_Initialize_004e7f1c");
/* 0x004e7dc0, 64 bytes */ GRIM_DATA("004e7dc0") void *grim_def_PTR_FileUtil_SysInitialize_004e7dc0[16] __asm__("_PTR_FileUtil_SysInitialize_004e7dc0") = {
    (void *)f_FileUtil_SysInitialize, (void *)&grim_def_s_FileUtil_SysInitialize_004e7f5c, (void *)f_Memory_SysInitialize, (void *)&grim_def_s_Memory_SysInitialize_004e7f44,
    (void *)f_sputRoom_Initialize, (void *)&grim_def_s_sputRoom_Initialize_004e7f30, (void *)f_sputTime_Initialize, (void *)&grim_def_s_sputTime_Initialize_004e7f1c,
    (void *)f_sputLua_Initialize, (void *)&grim_def_s_sputLua_Initialize_004e7f08, (void *)f_sputCostume_Initialize, (void *)&grim_def_s_sputCostume_Initialize_004e7ef0,
    (void *)f_sputActor_Initialize, (void *)&grim_def_s_sputActor_Initialize_004e7ed8, (void *)f_sputResource_Initialize, (void *)&grim_def_s_sputResource_Initialize_004e7ec0
};
/* 0x004e7e00, 48 bytes */ GRIM_DATA("004e7e00") void *grim_def_PTR_sputControl_Initialize_004e7e00[12] __asm__("_PTR_sputControl_Initialize_004e7e00") = {
    (void *)f_sputControl_Initialize, (void *)&grim_def_s_sputControl_Initialize_004e7ea8, (void *)f_SoundsInitialize, (void *)&grim_def_s_SoundsInitialize_004e7e94,
    (void *)f_sputRender_Initialize, (void *)&grim_def_s_sputRender_Initialize_004e7e7c, (void *)f_sputText_Initialize, (void *)&grim_def_s_sputText_Initialize_004e7e68,
    (void *)f_sputPrimitive_Initialize, (void *)&grim_def_s_sputPrimitive_Initialize_004e7e4c, (void *)f_sputSmush_Initialize, (void *)&grim_def_s_sputSmush_Initialize_004e7e34
};
/* 0x008a8c58, 4 bytes */ /* loose */ unsigned int grim_def_g_dwSputmInitialize __asm__("_g_dwSputmInitialize") = 0x0;
/* 0x008a8c5c, 4 bytes */ /* loose */ unsigned int grim_def_g_dwSputmStartup __asm__("_g_dwSputmStartup") = 0x0;
