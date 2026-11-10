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
  g_pSvcRender = param_1;
  *param_2 = sputRender_Initialize;
  param_2[1] = sputRender_Terminate;
  param_2[2] = sputRender_Start;
  param_2[3] = sputRender_Stop;
  param_2[4] = Render_SaveState;
  param_2[5] = Render_RestoreState;
  param_2[6] = 0;
  param_2[7] = 0;
  sputControl_AddCallback(FUN_00484a50);
  UINT_008c9788 = 1;
  return 0;
}

/* ---- 0x00486050  sputRender_Terminate ---- */
/* Module interface slot 1 (sputRender): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. */

void sputRender_Terminate(void)

{
  g_pSvcRender = (GrimServices *)0x0;
  if (UINT_008c9788 != 0) {
    UINT_008c9788 = 0;
  }
  return;
}

/* ---- 0x00486070  sputRender_Start ---- */
/* Module interface slot 2 (sputRender): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start creates the dirty-rectangle pool, _Stop frees
   the cache rects and the pool. */

int sputRender_Start(void)

{
  bool bVar1;
  
  bVar1 = UINT_008c978c != 0;
  if (!bVar1) {
    UINT_008c978c = 1;
    UINT_008a9510 = 4;
    UINT_008a9514 = 3;
    UINT_008a9518 = 1;
    UINT_008a951c = 1;
    UINT_008a9520 = 0;
    UINT_008a9524 = 0;
    UINT_008a9528 = 2;
    g_pDirtyRectPool = (void **)Pool_Create(0x24,0x20,8);
  }
  return bVar1;
}

/* ---- 0x004860d0  sputRender_Stop ---- */
/* Module interface slot 3 (sputRender): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. */

void sputRender_Stop(void)

{
  CacheRect_FreeAll();
  if (g_pDirtyRectPool != (void **)0x0) {
    Pool_Destroy(g_pDirtyRectPool);
    g_pDirtyRectPool = (void **)0x0;
  }
  UINT_008c978c = 0;
  return;
}
