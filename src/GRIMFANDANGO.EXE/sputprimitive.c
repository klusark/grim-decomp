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

uint __cdecl sputPrimitive_Initialize(uint services,undefined4 *iface)

{
  _g_pSputPrimitiveHS = services;
  *iface = sputPrimitive_Initialize;
  iface[1] = sputPrimitive_Terminate;
  iface[2] = sputPrimitive_Startup;
  iface[3] = sputPrimitive_Shutdown;
  iface[4] = sputPrimitive_Save;
  iface[5] = sputPrimitive_Restore;
  iface[6] = 0;
  iface[7] = 0;
  g_dwSputPrimitiveInitialize = 1;
  return 0;
}

/* ---- 0x00489600  sputPrimitive_Save ---- */
/* Module interface slot 4 (sputPrimitive): save-game writer, calls the SaveGame_Write callback it
   is handed for every field. Original name sputPrimitive_Save (the remaster's GrimFandango (Linux):
   aligned call in sputPrimitive_Initialize); was sputPrimitive_SaveState. */

uint __cdecl sputPrimitive_Save(code *write)

{
  undefined4 *puVar1;
  code *pcVar2;
  uint local_4;
  
  pcVar2 = write;
  local_4 = 0;
  for (puVar1 = (undefined4 *)g_dwPrimitiveQ[0]; puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    local_4 = local_4 + 1;
  }
  (*write)(&local_4,4);
  for (puVar1 = (undefined4 *)g_dwPrimitiveQ[0]; puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    write = (code *)puVar1[2];
    (*pcVar2)(&write,4);
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

/* ---- 0x004896b0  sputPrimitive_Restore ---- */
/* Module interface slot 5 (sputPrimitive): save-game reader, calls the SaveGame_Read callback it is
   handed; returns non-zero on a short read. Original name sputPrimitive_Restore (the remaster's
   GrimFandango (Linux): aligned call in sputPrimitive_Initialize); was sputPrimitive_RestoreState.
    */

uint __cdecl sputPrimitive_Restore(code *id)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  code *pcVar1;
  Primitive *pPVar2;
  int local_28;
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  int iStack_18;
  int iStack_14;
  #define iStack_10 (*(int *)(_frame + (0x20 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x20 - 0xc)))
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  PrimitiveQueue_purge((int *)g_dwPrimitiveQ);
  pcVar1 = id;
  (*id)(&local_28,4);
  while (local_28 != 0) {
    local_28 = local_28 + -1;
    iStack_10 = 0;
    iStack_c = 0;
    iStack_8 = 0;
    iStack_4 = 0;
    (*pcVar1)(&iStack_20,4);
    (*pcVar1)(&id,4);
    (*pcVar1)(&iStack_24,4);
    (*pcVar1)(&iStack_10,8);
    (*pcVar1)(&iStack_8,8);
    (*pcVar1)(&iStack_1c,4);
    (*pcVar1)(&iStack_18,4);
    (*pcVar1)(&iStack_14,4);
    pPVar2 = PrimitiveQueue_addObject(g_dwPrimitiveQ,(int)id,iStack_24);
    if (pPVar2 != (Primitive *)0x0) {
      pPVar2->nType = iStack_20;
      pPVar2->nX1 = iStack_10;
      pPVar2->nY1 = iStack_c;
      pPVar2->nX2 = iStack_8;
      pPVar2->nY2 = iStack_4;
      pPVar2->nColor = iStack_1c;
      pPVar2->nPattern = iStack_18;
      pPVar2->nFilled = iStack_14;
    }
    g_nPrimitiveQueue_nextId = (int)(id + 1);
  }
  return 0;
}
#undef iStack_10
#undef iStack_4
#undef iStack_8
#undef iStack_c


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
  PrimitiveQueue_purge((int *)g_dwPrimitiveQ);
  g_dwSputPrimitiveStartup = 0;
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char f_sputPrimitive_ChangePrimitive[] __asm__("_sputPrimitive_ChangePrimitive");
extern char f_sputPrimitive_DrawLine[] __asm__("_sputPrimitive_DrawLine");
extern char f_sputPrimitive_DrawPolygon[] __asm__("_sputPrimitive_DrawPolygon");
extern char f_sputPrimitive_DrawRectangle[] __asm__("_sputPrimitive_DrawRectangle");
extern char f_sputPrimitive_KillPrimitive[] __asm__("_sputPrimitive_KillPrimitive");
extern char f_sputPrimitive_PurgeQueue[] __asm__("_sputPrimitive_PurgeQueue");
extern unsigned int grim_def_UINT_004e83c8 __asm__("_UINT_004e83c8");
extern unsigned int grim_def_g_dwSputPrimitiveInitialize __asm__("_g_dwSputPrimitiveInitialize");
extern unsigned int grim_def_g_dwSputPrimitiveStartup __asm__("_g_dwSputPrimitiveStartup");
extern void *grim_def_g_pPrimitiveFunctionsToRegister[12] __asm__("_g_pPrimitiveFunctionsToRegister");
extern unsigned char grim_def_g_pSputPrimitiveHS[4] __asm__("_g_pSputPrimitiveHS");
extern char grim_def_s_ChangePrimitive_004e83f0[] __asm__("_s_ChangePrimitive_004e83f0");
extern char grim_def_s_DrawLine_004e841c[] __asm__("_s_DrawLine_004e841c");
extern char grim_def_s_DrawPolygon_004e8410[] __asm__("_s_DrawPolygon_004e8410");
extern char grim_def_s_DrawRectangle_004e8400[] __asm__("_s_DrawRectangle_004e8400");
extern char grim_def_s_KillPrimitive_004e83e0[] __asm__("_s_KillPrimitive_004e83e0");
extern char grim_def_s_PurgePrimitiveQueue_004e83cc[] __asm__("_s_PurgePrimitiveQueue_004e83cc");
/* 0x004e8398, 48 bytes */ GRIM_DATA("004e8398") void *grim_def_g_pPrimitiveFunctionsToRegister[12] __asm__("_g_pPrimitiveFunctionsToRegister") = {
    (void *)&grim_def_s_DrawLine_004e841c, (void *)f_sputPrimitive_DrawLine, (void *)&grim_def_s_DrawPolygon_004e8410, (void *)f_sputPrimitive_DrawPolygon,
    (void *)&grim_def_s_DrawRectangle_004e8400, (void *)f_sputPrimitive_DrawRectangle, (void *)&grim_def_s_ChangePrimitive_004e83f0, (void *)f_sputPrimitive_ChangePrimitive,
    (void *)&grim_def_s_KillPrimitive_004e83e0, (void *)f_sputPrimitive_KillPrimitive, (void *)&grim_def_s_PurgePrimitiveQueue_004e83cc, (void *)f_sputPrimitive_PurgeQueue
};
/* 0x004e83c8, 4 bytes */ GRIM_DATA("004e83c8") unsigned int grim_def_UINT_004e83c8 __asm__("_UINT_004e83c8") = 0x6;
/* 0x008ca0a8, 4 bytes */ /* loose */ unsigned int grim_def_g_dwSputPrimitiveInitialize __asm__("_g_dwSputPrimitiveInitialize") = 0x0;
/* 0x008ca0ac, 4 bytes */ /* loose */ unsigned int grim_def_g_dwSputPrimitiveStartup __asm__("_g_dwSputPrimitiveStartup") = 0x0;
/* 0x008ca0b0, 4 bytes */ /* loose */ unsigned char grim_def_g_pSputPrimitiveHS[4] __asm__("_g_pSputPrimitiveHS") = {0};
