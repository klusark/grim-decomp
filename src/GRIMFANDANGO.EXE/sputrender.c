/* GRIMFANDANGO.EXE :: sputrender.c
 * functions 0x00483d40 .. 0x004860d0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00483d40  sputRender_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputRender_Initialize(GrimServices *param_1,undefined4 *param_2)

{
  g_pSputRendHS = param_1;
  *param_2 = sputRender_Initialize;
  param_2[1] = sputRender_Terminate;
  param_2[2] = sputRender_Startup;
  param_2[3] = sputRender_Shutdown;
  param_2[4] = sputRender_Save;
  param_2[5] = sputRender_Restore;
  param_2[6] = 0;
  param_2[7] = 0;
  sputControl_AddCallback(sputRender_ControlHandler);
  g_dwSputRendInitialize = 1;
  return 0;
}

/* ---- 0x00486050  sputRender_Terminate ---- */
/* Module interface slot 1 (sputRender): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. */

void sputRender_Terminate(void)

{
  g_pSputRendHS = (GrimServices *)0x0;
  if (g_dwSputRendInitialize != 0) {
    g_dwSputRendInitialize = 0;
  }
  return;
}

/* ---- 0x00486070  sputRender_Startup ---- */
/* Module interface slot 2 (sputRender): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start creates the dirty-rectangle pool, _Stop frees
   the cache rects and the pool. Original name sputRender_Startup (the remaster's GrimFandango
   (Linux): aligned call in sputRender_Initialize); was sputRender_Start. */

int sputRender_Startup(void)

{
  bool bVar1;
  
  bVar1 = g_dwSputRendStartup != 0;
  if (!bVar1) {
    g_dwSputRendStartup = 1;
    g_dwRenderVars = 4;
    UINT_008a9514 = 3;
    UINT_008a9518 = 1;
    UINT_008a951c = 1;
    UINT_008a9520 = 0;
    UINT_008a9524 = 0;
    UINT_008a9528 = 2;
    g_pDirtyRectPool = (void **)Memory_AllocatePool(0x24,0x20,8);
  }
  return bVar1;
}

/* ---- 0x004860d0  sputRender_Shutdown ---- */
/* Module interface slot 3 (sputRender): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputRender_Shutdown (the remaster's GrimFandango
   (Linux): aligned call in sputRender_Initialize); was sputRender_Stop. */

void sputRender_Shutdown(void)

{
  CacheRect_FreeAll();
  if (g_pDirtyRectPool != (void **)0x0) {
    Memory_FreePool(g_pDirtyRectPool);
    g_pDirtyRectPool = (void **)0x0;
  }
  g_dwSputRendStartup = 0;
  return;
}
