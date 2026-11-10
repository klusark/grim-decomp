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
  
  _DAT_008ca144 = param_1;
  *param_2 = sputText_Initialize;
  param_2[1] = sputText_Terminate;
  param_2[2] = sputText_Startup;
  param_2[3] = sputText_Stop;
  param_2[4] = sputText_SaveState;
  param_2[5] = sputText_RestoreState;
  param_2[6] = 0;
  param_2[7] = 0;
  iVar1 = PlatModule_Init(param_1,&DAT_008ca118);
  if (iVar1 == 0) {
    iVar1 = TextModule_Init(param_1,&DAT_008ca0b8);
    if (iVar1 == 0) {
      UINT_008ca138 = 1;
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
  _DAT_008ca144 = 0;
  (*(code *)UINT_008ca11c)();
  (*(code *)UINT_008ca0bc)();
  if (UINT_008ca138 != 0) {
    UINT_008ca138 = 0;
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
  
  if (UINT_008ca13c == 0) {
    iVar1 = (*(code *)UINT_008ca120)();
    if (iVar1 == 0) {
      iVar1 = (*(code *)UINT_008ca0c0)();
      if (iVar1 == 0) {
        UINT_004e84a0 = Text_GetDefaultFont();
        UINT_004e84d0 = UINT_004e84a0;
        UINT_004e8500 = UINT_004e84a0;
        UINT_008ca148 = UINT_004e84a0;
        Lua_OpenEngineLib(&PTR_s_IsMessageGoing_004e8528,UINT_004e85d8);
        lua_pushstring(&DAT_004e8454);
        UINT_008ca0dc = lua_ref(1);
        lua_pushstring(&DAT_004e8450);
        UINT_008ca0e0 = lua_ref(1);
        lua_pushstring(&DAT_004e87c0);
        UINT_008ca104 = lua_ref(1);
        lua_pushstring(s_width_004e8440);
        UINT_008ca0f8 = lua_ref(1);
        lua_pushstring(s_height_004e8438);
        UINT_008ca0d8 = lua_ref(1);
        lua_pushstring(s_fgcolor_004e87b8);
        UINT_008ca110 = lua_ref(1);
        lua_pushstring(s_bgcolor_004e87b0);
        UINT_008ca0fc = lua_ref(1);
        lua_pushstring(s_fxcolor_004e87a8);
        UINT_008ca0f0 = lua_ref(1);
        lua_pushstring(s_hicolor_004e87a0);
        UINT_008ca0e8 = lua_ref(1);
        lua_pushstring(s_duration_004e8794);
        UINT_008ca0ec = lua_ref(1);
        lua_pushstring(s_center_004e878c);
        UINT_008ca0f4 = lua_ref(1);
        lua_pushstring(s_ljustify_004e8780);
        UINT_008ca108 = lua_ref(1);
        lua_pushstring(s_rjustify_004e8774);
        UINT_008ca10c = lua_ref(1);
        lua_pushstring(s_volume_004e876c);
        UINT_008ca100 = lua_ref(1);
        lua_pushstring(&DAT_004e8768);
        UINT_008ca114 = lua_ref(1);
        lua_pushstring(s_background_004e875c);
        UINT_008ca0e4 = lua_ref(1);
        g_pTextObjectPool = (void **)Pool_Create(0x260,0x10,8);
        UINT_008ca13c = 1;
        return 0;
      }
    }
  }
  return 1;
}

/* ---- 0x0048c6f0  sputText_Stop ---- */
/* Module interface slot 3 (sputText): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. */

void sputText_Stop(void)

{
  (*(code *)UINT_008ca124)();
  (*(code *)UINT_008ca0c4)();
  lua_unref(UINT_008ca0dc);
  lua_unref(UINT_008ca0e0);
  lua_unref(UINT_008ca104);
  lua_unref(UINT_008ca0f8);
  lua_unref(UINT_008ca0d8);
  lua_unref(UINT_008ca110);
  lua_unref(UINT_008ca0fc);
  lua_unref(UINT_008ca0f0);
  lua_unref(UINT_008ca0e8);
  lua_unref(UINT_008ca0ec);
  lua_unref(UINT_008ca0f4);
  lua_unref(UINT_008ca108);
  lua_unref(UINT_008ca10c);
  lua_unref(UINT_008ca100);
  lua_unref(UINT_008ca114);
  lua_unref(UINT_008ca0e4);
  if (g_pTextObjectPool != (void **)0x0) {
    Pool_Destroy(g_pTextObjectPool);
    g_pTextObjectPool = (void **)0x0;
  }
  UINT_008ca13c = 0;
  return;
}

/* ---- 0x0048cbc0  sputText_SaveState ---- */
/* Module interface slot 4 (sputText): save-game writer, calls the SaveGame_Write callback it is
   handed for every field. */

undefined4 sputText_SaveState(code *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  int iVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  for (puVar1 = g_pTextObjectList; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    local_4 = local_4 + 1;
  }
  iVar2 = (*param_1)(&local_4,4);
  puVar1 = g_pTextObjectList;
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


/* ---- 0x0048cd80  sputText_RestoreState ---- */
/* Module interface slot 5 (sputText): save-game reader, calls the SaveGame_Read callback it is
   handed; returns non-zero on a short read. */

undefined4 sputText_RestoreState(code *param_1)

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
  while (g_pTextObjectList != (void *)0x0) {
    List_Unlink(g_pTextObjectList);
  }
  iVar4 = (*param_1)(&local_4,4);
  if (iVar4 == 0) {
    param_1 = (code *)0x0;
    if (0 < local_4) {
      do {
        puVar5 = (undefined4 *)Pool_Alloc(g_pTextObjectPool);
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
        pvVar6 = Res_DataFromHandle((void *)*puVar2);
        *puVar2 = pvVar6;
        if (*piVar1 != 0) {
          *piVar1 = (int)&UINT_008a94b8;
        }
        if (puVar5[0x83] != 0) {
          puVar5[0x83] = puVar5 + 0x90;
        }
        puVar5[0x8d] = g_wTextColors;
        puVar5[1] = 0;
        *puVar5 = g_pTextObjectList;
        if (g_pTextObjectList != (void *)0x0) {
          *(undefined4 **)((int)g_pTextObjectList + 4) = puVar5;
        }
        param_1 = (code *)((int)param_1 + 1);
        g_pTextObjectList = puVar5;
      } while ((int)param_1 < local_4);
    }
    (*pcVar3)(&UINT_004e84a0,4);
    (*pcVar3)(&UINT_004e84d0,4);
    (*pcVar3)(&UINT_004e8500,4);
    UINT_008ca148 = Text_GetDefaultFont();
    UINT_004e84a0 = (uint)Res_DataFromHandle((void *)UINT_004e84a0);
    UINT_004e84d0 = (uint)Res_DataFromHandle((void *)UINT_004e84d0);
    UINT_004e8500 = (uint)Res_DataFromHandle((void *)UINT_004e8500);
    if (UINT_004e84a0 == 0) {
      UINT_004e84a0 = UINT_008ca148;
    }
    if (UINT_004e84d0 == 0) {
      UINT_004e84d0 = UINT_008ca148;
    }
    if ((void *)UINT_004e8500 == (void *)0x0) {
      UINT_004e8500 = UINT_008ca148;
    }
    return 0;
  }
  return 1;
}
#undef local_4

