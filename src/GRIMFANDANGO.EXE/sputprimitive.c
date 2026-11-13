/* GRIMFANDANGO.EXE :: sputprimitive.c
 * functions 0x00489580 .. 0x00489820 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00489580  sputPrimitive_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

uint __cdecl sputPrimitive_Initialize(uint param_1,undefined4 *param_2)

{
  _g_pSputPrimitiveHS = param_1;
  *param_2 = sputPrimitive_Initialize;
  param_2[1] = sputPrimitive_Terminate;
  param_2[2] = sputPrimitive_Startup;
  param_2[3] = sputPrimitive_Shutdown;
  param_2[4] = sputPrimitive_Save;
  param_2[5] = sputPrimitive_Restore;
  param_2[6] = 0;
  param_2[7] = 0;
  g_dwSputPrimitiveInitialize = 1;
  return 0;
}

/* ---- 0x00489600  sputPrimitive_Save ---- */
/* Module interface slot 4 (sputPrimitive): save-game writer, calls the SaveGame_Write callback it
   is handed for every field. Original name sputPrimitive_Save (the remaster's GrimFandango (Linux):
   aligned call in sputPrimitive_Initialize); was sputPrimitive_SaveState. */

uint __cdecl sputPrimitive_Save(code *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  code *pcVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pcVar2 = param_1;
  local_4 = 0;
  for (puVar1 = (undefined4 *)g_dwPrimitiveQ; puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    local_4 = local_4 + 1;
  }
  (*param_1)(&local_4,4);
  for (puVar1 = (undefined4 *)g_dwPrimitiveQ; puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    param_1 = (code *)puVar1[2];
    (*pcVar2)(&param_1,4);
    (*pcVar2)(puVar1 + 3,4);
    (*pcVar2)(puVar1 + 4,4);
    (*pcVar2)(puVar1 + 5,8);
    (*pcVar2)(puVar1 + 7,8);
    (*pcVar2)(puVar1 + 9,4);
    (*pcVar2)(puVar1 + 10,4);
    (*pcVar2)(puVar1 + 0xb,4);
  }
  return 0;
}
#undef local_4


/* ---- 0x004896b0  sputPrimitive_Restore ---- */
/* Module interface slot 5 (sputPrimitive): save-game reader, calls the SaveGame_Read callback it is
   handed; returns non-zero on a short read. Original name sputPrimitive_Restore (the remaster's
   GrimFandango (Linux): aligned call in sputPrimitive_Initialize); was sputPrimitive_RestoreState.
    */

uint __cdecl sputPrimitive_Restore(code *param_1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  code *pcVar1;
  void *pvVar2;
  #define local_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define iStack_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define uStack_20 (*(undefined4 *)(_frame + (0x40 - 0x20)))
  #define uStack_1c (*(undefined4 *)(_frame + (0x40 - 0x1c)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x40 - 0x18)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x40 - 0x14)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x40 - 0x10)))
  #define uStack_c (*(undefined4 *)(_frame + (0x40 - 0xc)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x40 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x40 - 0x4)))
  
  PrimitiveQueue_purge((int *)&g_dwPrimitiveQ);
  pcVar1 = param_1;
  (*param_1)(&local_28,4);
  while (local_28 != 0) {
    local_28 = local_28 + -1;
    uStack_10 = 0;
    uStack_c = 0;
    uStack_8 = 0;
    uStack_4 = 0;
    (*pcVar1)(&uStack_20,4);
    (*pcVar1)(&param_1,4);
    (*pcVar1)(&iStack_24,4);
    (*pcVar1)(&uStack_10,8);
    (*pcVar1)(&uStack_8,8);
    (*pcVar1)(&uStack_1c,4);
    (*pcVar1)(&uStack_18,4);
    (*pcVar1)(&uStack_14,4);
    pvVar2 = PrimitiveQueue_addObject(&g_dwPrimitiveQ,(int)param_1,iStack_24);
    if (pvVar2 != (void *)0x0) {
      *(undefined4 *)((int)pvVar2 + 8) = uStack_20;
      *(undefined4 *)((int)pvVar2 + 0x14) = uStack_10;
      *(undefined4 *)((int)pvVar2 + 0x18) = uStack_c;
      *(undefined4 *)((int)pvVar2 + 0x1c) = uStack_8;
      *(undefined4 *)((int)pvVar2 + 0x20) = uStack_4;
      *(undefined4 *)((int)pvVar2 + 0x24) = uStack_1c;
      *(undefined4 *)((int)pvVar2 + 0x28) = uStack_18;
      *(undefined4 *)((int)pvVar2 + 0x2c) = uStack_14;
    }
    g_nPrimitiveQueue_nextId = (int)(param_1 + 1);
  }
  return 0;
}
#undef iStack_24
#undef local_28
#undef uStack_10
#undef uStack_14
#undef uStack_18
#undef uStack_1c
#undef uStack_20
#undef uStack_4
#undef uStack_8
#undef uStack_c


/* ---- 0x004897d0  sputPrimitive_Terminate ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Module interface slot 1 (sputPrimitive): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. */

void __cdecl sputPrimitive_Terminate(void)

{
  _g_pSputPrimitiveHS = 0;
  if (g_dwSputPrimitiveInitialize != 0) {
    g_dwSputPrimitiveInitialize = 0;
  }
  return;
}

/* ---- 0x004897f0  sputPrimitive_Startup ---- */
/* Module interface slot 2 (sputPrimitive): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start registers the DrawLine/DrawPolygon/... Lua
   table, _Stop clears the primitive list. Original name sputPrimitive_Startup (the remaster's
   GrimFandango (Linux): aligned call in sputPrimitive_Initialize); was sputPrimitive_Start. */

uint __cdecl sputPrimitive_Startup(void)

{
  if (g_dwSputPrimitiveStartup != 0) {
    return 1;
  }
  sputLua_RegisterFunctions((int *)&g_pPrimitiveFunctionsToRegister,UINT_004e83c8);
  g_dwSputPrimitiveStartup = 1;
  return 0;
}

/* ---- 0x00489820  sputPrimitive_Shutdown ---- */
/* Module interface slot 3 (sputPrimitive): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputPrimitive_Shutdown (the remaster's GrimFandango
   (Linux): aligned call in sputPrimitive_Initialize); was sputPrimitive_Stop. */

void __cdecl sputPrimitive_Shutdown(void)

{
  PrimitiveQueue_purge((int *)&g_dwPrimitiveQ);
  g_dwSputPrimitiveStartup = 0;
  return;
}
