/* GRIMFANDANGO.EXE :: textobject.c
 * functions 0x0048c470 .. 0x0048d030 (10 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048c470  TextObject_Activate ---- */
/* Links a new text object into g_pTextObjectList with its lifetime (ms, -1 = until killed) and
   flags (1 keep, 2 hidden, 4 speech, 8 always draw) */

void __cdecl TextObject_Activate(void *obj,int durationMs,int flags)

{
  int iVar1;
  
  if (obj != (void *)0x0) {
    *(int *)((int)obj + 0x250) = durationMs;
    *(int *)((int)obj + 600) = flags;
    *(undefined4 *)((int)obj + 0x238) = *(undefined4 *)((int)obj + 0x214);
    iVar1 = *(int *)((int)obj + 0x218) - *(int *)(**(int **)((int)obj + 0x210) + 8);
    *(int *)((int)obj + 0x23c) = iVar1;
    *(int *)((int)obj + 0x218) = iVar1;
    *(void **)obj = g_pTextObjectList;
    if (g_pTextObjectList != (void *)0x0) {
      *(void **)((int)g_pTextObjectList + 4) = obj;
    }
    g_pTextObjectList = obj;
  }
  return;
}

/* ---- 0x0048c4d0  FUN_0048c4d0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048c4d0(void)

{
  _DAT_008ca144 = 0;
  (*(code *)UINT_008ca11c)();
  (*(code *)UINT_008ca0bc)();
  if (UINT_008ca138 != 0) {
    UINT_008ca138 = 0;
  }
  return;
}

/* ---- 0x0048c500  FUN_0048c500 ---- */
undefined4 FUN_0048c500(void)

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

/* ---- 0x0048c6f0  FUN_0048c6f0 ---- */
void FUN_0048c6f0(void)

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

/* ---- 0x0048c7e0  TextObject_New ---- */
void * __cdecl TextObject_New(void *ctx,char *text,int durationMs,int flags)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar1 = (undefined4 *)Pool_Alloc(g_pTextObjectPool);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
    puVar1[1] = 0;
    strncpy(puVar1 + 2,text,0x1ff);
    *(undefined1 *)((int)puVar1 + 0x207) = 0;
    puVar1[0x8e] = *(undefined4 *)((int)ctx + 0xc);
    puVar1[0x8f] = *(undefined4 *)((int)ctx + 0x10);
    puVar3 = ctx;
    puVar4 = puVar1 + 0x82;
    for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    if (g_pOverrideFont != (void *)0x0) {
      puVar1[0x84] = g_pOverrideFont;
    }
    puVar3 = puVar1 + 0x90;
    puVar1[0x8d] = g_wTextColors;
    puVar1[0x83] = puVar3;
    puVar4 = *(undefined4 **)((int)ctx + 4);
    if (puVar4 != (undefined4 *)0x0) {
      *puVar3 = *puVar4;
      puVar1[0x91] = puVar4[1];
      puVar1[0x92] = puVar4[2];
      puVar1[0x93] = puVar4[3];
      puVar1[0x95] = 0;
      puVar1[0x97] = puVar1;
      return puVar1;
    }
    *puVar3 = 0;
    puVar1[0x91] = 0;
    puVar1[0x92] = UINT_008a94bc;
    puVar1[0x93] = UINT_008a94c0;
    puVar1[0x95] = 0;
    puVar1[0x97] = puVar1;
  }
  return puVar1;
}

/* ---- 0x0048c9f0  TextObject_Draw ---- */
void __cdecl TextObject_Draw(void *obj,int invalidate)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (obj != (void *)0x0) {
    local_10 = *(uint *)((int)obj + 0x238);
    *(uint *)((int)obj + 0x214) = local_10;
    iVar4 = *(int *)(**(int **)((int)obj + 0x210) + 8) + *(int *)((int)obj + 0x23c);
    *(int *)((int)obj + 0x218) = iVar4;
    local_c = iVar4 - *(int *)(**(int **)((int)obj + 0x210) + 8);
    local_8 = Text_MeasureWidth((void *)((int)obj + 0x208),(char *)((int)obj + 8));
    local_4 = Text_MeasureHeight((void *)((int)obj + 0x208),(char *)((int)obj + 8));
    if ((*(byte *)((int)obj + 0x230) & 1) != 0) {
      local_10 = local_10 - (int)local_8 / 2;
    }
    uVar1 = *(uint *)((int)obj + 0x21c);
    g_wTextColors[0] =
         (ushort)((uVar1 >> 10 & 0x3f | ((int)uVar1 >> 3) << 6) << 5) |
         (ushort)(uVar1 >> 0x13) & 0x1f;
    uVar2 = *(uint *)((int)obj + 0x220);
    g_wTextColors[1] =
         (ushort)((uVar2 >> 10 & 0x3f | ((int)uVar2 >> 3) << 6) << 5) |
         (ushort)(uVar2 >> 0x13) & 0x1f;
    uVar3 = *(uint *)((int)obj + 0x224);
    g_wTextColors[2] =
         (ushort)((uVar3 >> 10 & 0x3f | ((int)uVar3 >> 3) << 6) << 5) |
         (ushort)(uVar3 >> 0x13) & 0x1f;
    Render_RemapPixels(g_wTextColors,3);
    *(undefined4 *)((int)obj + 0x21c) = 0;
    *(undefined4 *)((int)obj + 0x220) = 1;
    *(undefined4 *)((int)obj + 0x224) = 2;
    Text_DrawFormatted((int)obj + 0x208,(int)obj + 8);
    *(undefined4 *)((int)obj + 0x214) = *(undefined4 *)((int)obj + 0x238);
    *(int *)((int)obj + 0x218) =
         *(int *)(**(int **)((int)obj + 0x210) + 8) + *(int *)((int)obj + 0x23c);
    if (invalidate != 0) {
      Render_InvalidateRectLastBuffer((int *)&local_10,0);
    }
    *(uint *)((int)obj + 0x224) = uVar3;
    *(uint *)((int)obj + 0x220) = uVar2;
    *(uint *)((int)obj + 0x21c) = uVar1;
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0048cba0  TextObject_FindBySelf ---- */
undefined4 * TextObject_FindBySelf(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = g_pTextObjectList;
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    if (puVar1[0x97] == param_1) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}

/* ---- 0x0048cbc0  FUN_0048cbc0 ---- */
undefined4 FUN_0048cbc0(code *param_1)

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


/* ---- 0x0048cd80  FUN_0048cd80 ---- */
undefined4 FUN_0048cd80(code *param_1)

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


/* ---- 0x0048d030  FUN_0048d030 ---- */
bool FUN_0048d030(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = ((code *)Debug_CameraFovKeys)(param_1);
  return iVar1 != 0;
}
