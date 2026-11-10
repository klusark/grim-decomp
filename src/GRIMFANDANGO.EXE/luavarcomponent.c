/* GRIMFANDANGO.EXE :: luavarcomponent.c
 * functions 0x00497680 .. 0x00497810 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00497680  LuaVarComponent_OnKey ---- */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Costume tag handler for 'Lua Variable' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, sets the named Lua global to the key value
   (lua_pushnumber + lua_setglobal). */

void LuaVarComponent_OnKey(undefined4 param_1,char *param_2,undefined4 param_3,int param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  lua_pushnumber((float)param_4);
  lua_setglobal(param_2);
  return;
}
#undef local_4


/* ---- 0x004976a0  LuaVarAdjuster ---- */
/* Costume tag handler for 'Lua Variable' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 4, editor dialog 'Change variable properties'. Original
   name LuaVarAdjuster (the remaster's GrimFandango (Linux): strings: 'Change variable properties');
   was LuaVarComponent_EditKey. */

undefined4 LuaVarAdjuster(undefined4 *param_1,int param_2,int param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *defaultText;
  int iVar1;
  #define local_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  defaultText = (char *)*param_1;
  iVar1 = grimPlat_InputDialog
                    (s_Change_variable_properties_004ea72c,s_Variable_name_004ea748,local_20,0x20,
                     defaultText);
  if (iVar1 != 0) {
    strncpy(defaultText,local_20,0x1f);
    defaultText[0x1f] = '\0';
    strncpy(param_2,local_20,param_3 + -1);
    *(undefined1 *)(param_3 + -1 + param_2) = 0;
    return 1;
  }
  return 0;
}
#undef local_20


/* ---- 0x00497710  LuaVarRequester ---- */
/* Costume tag handler for 'Lua Variable' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, asks for the variable name ('Name of variable') in
   the editor. Original name LuaVarRequester (the remaster's GrimFandango (Linux): strings: 'Name of
   variable'); was LuaVarComponent_Create. */

int LuaVarRequester(uint param_1,int param_2,int param_3,int param_4,int param_5)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *puVar2;
  #define local_20 (*(char *)(_frame + (0x30 - 0x20)))
  #define local_1f (*(undefined4 *)(_frame + (0x30 - 0x1f)))
  #define local_1 (*(undefined1 *)(_frame + (0x30 - 0x1)))
  
  local_20 = DAT_004f5a98;
  puVar2 = &local_1f;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)puVar2 = 0;
  *(undefined1 *)((int)puVar2 + 2) = 0;
  if (param_3 != 0) {
    return false;
  }
  if (param_5 == 0) {
    iVar1 = grimPlat_InputDialog
                      (s_Name_of_variable_004ea758,s_Variable_name_004ea748,&local_20,0x20,&local_20
                      );
    if (iVar1 == 0) {
      return false;
    }
  }
  else {
    strncpy(&local_20,param_5,0x1f);
    local_1 = 0;
  }
  iVar1 = (*g_pSvcCostume->pAlloc)(0x20,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xd86);
  if (iVar1 == 0) {
    return false;
  }
  strncpy(iVar1,&local_20,0x1f);
  *(undefined1 *)(iVar1 + 0x1f) = 0;
  iVar1 = Cos_RegisterComponent(param_1,iVar1,iVar1,param_2,0,param_4,0);
  return iVar1 != 0;
}
#undef local_1
#undef local_1f
#undef local_20


/* ---- 0x004977f0  LuaVarComponent_Destroy ---- */
/* Costume tag handler for 'Lua Variable' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 2, frees the key data. */

undefined4 LuaVarComponent_Destroy(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}

/* ---- 0x00497810  LuaVarComponent_Stop ---- */
/* Costume tag handler for 'Lua Variable' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 3, sets the Lua global to nil. */

undefined4 LuaVarComponent_Stop(char *param_1)

{
  lua_pushnil();
  lua_setglobal(param_1);
  return 1;
}
