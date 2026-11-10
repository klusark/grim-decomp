/* GRIMFANDANGO.EXE :: sputtext.c
 * functions 0x0048acc0 .. 0x0048cd80 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048acc0  sputText_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputText_Initialize(GrimServices *param_1,undefined4 *param_2)

{
  int iVar1;
  
  _g_pSputtextHS = param_1;
  *param_2 = sputText_Initialize;
  param_2[1] = sputText_Terminate;
  param_2[2] = sputText_Startup;
  param_2[3] = sputText_Shutdown;
  param_2[4] = sputText_Save;
  param_2[5] = sputText_Restore;
  param_2[6] = 0;
  param_2[7] = 0;
  iVar1 = Graph_SysInitialize(param_1,&g_aGraphMS);
  if (iVar1 == 0) {
    iVar1 = Text_SysInitialize(param_1,&g_aTextMS);
    if (iVar1 == 0) {
      g_dwSputtextInitialize = 1;
      return 0;
    }
  }
  return 1;
}

/* ---- 0x0048c4d0  sputText_Terminate ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Module interface slot 1 (sputText): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. */

void sputText_Terminate(void)

{
  _g_pSputtextHS = 0;
  (*(code *)UINT_008ca11c)();
  (*(code *)UINT_008ca0bc)();
  if (g_dwSputtextInitialize != 0) {
    g_dwSputtextInitialize = 0;
  }
  return;
}

/* ---- 0x0048c500  sputText_Startup ---- */
/* Module interface slot 2 (sputText): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start registers the text Lua API table and the
   field-name refs (fgcolor, justify, ...), creates the 0x260-byte text object pool. */

undefined4 sputText_Startup(void)

{
  int iVar1;
  
  if (g_dwSputtextStartup == 0) {
    iVar1 = (*(code *)UINT_008ca120)();
    if (iVar1 == 0) {
      iVar1 = (*(code *)UINT_008ca0c0)();
      if (iVar1 == 0) {
        UINT_004e84a0 = Text_GetSystemFont();
        UINT_004e84d0 = UINT_004e84a0;
        UINT_004e8500 = UINT_004e84a0;
        g_hFont = UINT_004e84a0;
        sputLua_RegisterFunctions(&g_pTextFunctionsToRegister,UINT_004e85d8);
        lua_pushstring(&DAT_004e8454);
        g_dwLrX = lua_ref(1);
        lua_pushstring(&DAT_004e8450);
        g_dwLrY = lua_ref(1);
        lua_pushstring(&DAT_004e87c0);
        g_dwLrFont = lua_ref(1);
        lua_pushstring(s_width_004e8440);
        g_dwLrWidth = lua_ref(1);
        lua_pushstring(s_height_004e8438);
        g_dwLrHeight = lua_ref(1);
        lua_pushstring(s_fgcolor_004e87b8);
        g_dwLrFGColor = lua_ref(1);
        lua_pushstring(s_bgcolor_004e87b0);
        g_dwLrBGColor = lua_ref(1);
        lua_pushstring(s_fxcolor_004e87a8);
        g_dwLrFXColor = lua_ref(1);
        lua_pushstring(s_hicolor_004e87a0);
        g_dwLrHiColor = lua_ref(1);
        lua_pushstring(s_duration_004e8794);
        g_dwLrDuration = lua_ref(1);
        lua_pushstring(s_center_004e878c);
        g_dwLrCenter = lua_ref(1);
        lua_pushstring(s_ljustify_004e8780);
        g_dwLrLJustify = lua_ref(1);
        lua_pushstring(s_rjustify_004e8774);
        g_dwLrRJustify = lua_ref(1);
        lua_pushstring(s_volume_004e876c);
        g_dwLrVolume = lua_ref(1);
        lua_pushstring(&DAT_004e8768);
        g_dwLrPan = lua_ref(1);
        lua_pushstring(s_background_004e875c);
        g_dwLrBackground = lua_ref(1);
        g_pTextEventPool = (void **)Memory_AllocatePool(0x260,0x10,8);
        g_dwSputtextStartup = 1;
        return 0;
      }
    }
  }
  return 1;
}

/* ---- 0x0048c6f0  sputText_Shutdown ---- */
/* Module interface slot 3 (sputText): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputText_Shutdown (the remaster's GrimFandango
   (Linux): the module's shutdown slot: graphMS / textMS shutdown, lua_unref of every lr*
   reference); was sputText_Stop. */

void sputText_Shutdown(void)

{
  (*(code *)UINT_008ca124)();
  (*(code *)UINT_008ca0c4)();
  lua_unref(g_dwLrX);
  lua_unref(g_dwLrY);
  lua_unref(g_dwLrFont);
  lua_unref(g_dwLrWidth);
  lua_unref(g_dwLrHeight);
  lua_unref(g_dwLrFGColor);
  lua_unref(g_dwLrBGColor);
  lua_unref(g_dwLrFXColor);
  lua_unref(g_dwLrHiColor);
  lua_unref(g_dwLrDuration);
  lua_unref(g_dwLrCenter);
  lua_unref(g_dwLrLJustify);
  lua_unref(g_dwLrRJustify);
  lua_unref(g_dwLrVolume);
  lua_unref(g_dwLrPan);
  lua_unref(g_dwLrBackground);
  if (g_pTextEventPool != (void **)0x0) {
    Memory_FreePool(g_pTextEventPool);
    g_pTextEventPool = (void **)0x0;
  }
  g_dwSputtextStartup = 0;
  return;
}

/* ---- 0x0048cbc0  sputText_Save ---- */
/* Module interface slot 4 (sputText): save-game writer, calls the SaveGame_Write callback it is
   handed for every field. Original name sputText_Save (the remaster's GrimFandango (Linux): aligned
   call in sputText_Initialize); was sputText_SaveState. */

undefined4 sputText_Save(code *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  int iVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  for (puVar1 = g_pTextQueue; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    local_4 = local_4 + 1;
  }
  iVar2 = (*param_1)(&local_4,4);
  puVar1 = g_pTextQueue;
  if (iVar2 != 0) {
    return 1;
  }
  for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    puVar1[0x97] = puVar1;
    (*param_1)(puVar1 + 2,0x200);
    (*param_1)(puVar1 + 0x82,4);
    (*param_1)(puVar1 + 0x83,4);
    (*param_1)(puVar1 + 0x84,4);
    (*param_1)(puVar1 + 0x85,4);
    (*param_1)(puVar1 + 0x86,4);
    (*param_1)(puVar1 + 0x87,4);
    (*param_1)(puVar1 + 0x88,4);
    (*param_1)(puVar1 + 0x89,4);
    (*param_1)(puVar1 + 0x8a,4);
    (*param_1)(puVar1 + 0x8b,4);
    (*param_1)(puVar1 + 0x8c,4);
    (*param_1)(puVar1 + 0x8e,4);
    (*param_1)(puVar1 + 0x8f,4);
    (*param_1)(puVar1 + 0x90,4);
    (*param_1)(puVar1 + 0x91,4);
    (*param_1)(puVar1 + 0x92,4);
    (*param_1)(puVar1 + 0x93,4);
    (*param_1)(puVar1 + 0x94,4);
    (*param_1)(puVar1 + 0x95,4);
    (*param_1)(puVar1 + 0x96,4);
    (*param_1)(puVar1 + 0x97,4);
  }
  (*param_1)(&UINT_004e84a0,4);
  (*param_1)(&UINT_004e84d0,4);
  (*param_1)(&UINT_004e8500,4);
  return 0;
}
#undef local_4


/* ---- 0x0048cd80  sputText_Restore ---- */
/* Module interface slot 5 (sputText): save-game reader, calls the SaveGame_Read callback it is
   handed; returns non-zero on a short read. Original name sputText_Restore (the remaster's
   GrimFandango (Linux): the module's restore slot: empties textQueue, reads the text events into
   pTextEventPool); was sputText_RestoreState. */

undefined4 sputText_Restore(code *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  undefined4 *puVar2;
  code *pcVar3;
  int iVar4;
  undefined4 *puVar5;
  void *pvVar6;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  pcVar3 = param_1;
  while (g_pTextQueue != (void *)0x0) {
    List_Unlink(g_pTextQueue);
  }
  iVar4 = (*param_1)(&local_4,4);
  if (iVar4 == 0) {
    param_1 = (code *)0x0;
    if (0 < local_4) {
      do {
        puVar5 = (undefined4 *)Memory_AllocFixed(g_pTextEventPool);
        (*pcVar3)(puVar5 + 2,0x200);
        piVar1 = puVar5 + 0x82;
        (*pcVar3)(piVar1,4);
        (*pcVar3)(puVar5 + 0x83,4);
        puVar2 = puVar5 + 0x84;
        (*pcVar3)(puVar2,4);
        (*pcVar3)(puVar5 + 0x85,4);
        (*pcVar3)(puVar5 + 0x86,4);
        (*pcVar3)(puVar5 + 0x87,4);
        (*pcVar3)(puVar5 + 0x88,4);
        (*pcVar3)(puVar5 + 0x89,4);
        (*pcVar3)(puVar5 + 0x8a,4);
        (*pcVar3)(puVar5 + 0x8b,4);
        (*pcVar3)(puVar5 + 0x8c,4);
        (*pcVar3)(puVar5 + 0x8e,4);
        (*pcVar3)(puVar5 + 0x8f,4);
        (*pcVar3)(puVar5 + 0x90,4);
        (*pcVar3)(puVar5 + 0x91,4);
        (*pcVar3)(puVar5 + 0x92,4);
        (*pcVar3)(puVar5 + 0x93,4);
        (*pcVar3)(puVar5 + 0x94,4);
        (*pcVar3)(puVar5 + 0x95,4);
        (*pcVar3)(puVar5 + 0x96,4);
        (*pcVar3)(puVar5 + 0x97,4);
        pvVar6 = Res_HandleFromSerialNumber((void *)*puVar2);
        *puVar2 = pvVar6;
        if (*piVar1 != 0) {
          *piVar1 = (int)&UINT_008a94b8;
        }
        if (puVar5[0x83] != 0) {
          puVar5[0x83] = puVar5 + 0x90;
        }
        puVar5[0x8d] = g_abSputRender_colorMap;
        puVar5[1] = 0;
        *puVar5 = g_pTextQueue;
        if (g_pTextQueue != (void *)0x0) {
          *(undefined4 **)((int)g_pTextQueue + 4) = puVar5;
        }
        param_1 = (code *)((int)param_1 + 1);
        g_pTextQueue = puVar5;
      } while ((int)param_1 < local_4);
    }
    (*pcVar3)(&UINT_004e84a0,4);
    (*pcVar3)(&UINT_004e84d0,4);
    (*pcVar3)(&UINT_004e8500,4);
    g_hFont = Text_GetSystemFont();
    UINT_004e84a0 = (uint)Res_HandleFromSerialNumber((void *)UINT_004e84a0);
    UINT_004e84d0 = (uint)Res_HandleFromSerialNumber((void *)UINT_004e84d0);
    UINT_004e8500 = (uint)Res_HandleFromSerialNumber((void *)UINT_004e8500);
    if (UINT_004e84a0 == 0) {
      UINT_004e84a0 = g_hFont;
    }
    if (UINT_004e84d0 == 0) {
      UINT_004e84d0 = g_hFont;
    }
    if ((void *)UINT_004e8500 == (void *)0x0) {
      UINT_004e8500 = g_hFont;
    }
    return 0;
  }
  return 1;
}
#undef local_4

