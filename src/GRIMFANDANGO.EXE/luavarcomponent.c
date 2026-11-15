/* GRIMFANDANGO.EXE :: luavarcomponent.c
 * functions 0x00497680 .. 0x00497810 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00497680  LuaVarChanger ---- */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Costume tag handler for 'Lua Variable' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, sets the named Lua global to the key value
   (lua_pushnumber + lua_setglobal). Original name LuaVarChanger (the remaster's GrimFandango
   (Linux): the same handler slot (changer) of the same costume tag registration in
   sputCostume_Startup); was LuaVarComponent_OnKey. */

void __cdecl LuaVarChanger(uint cosInst,char *name,uint tag,int value)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  lua_pushnumber((float)value);
  lua_setglobal(name);
  return;
}
#undef local_4


/* ---- 0x004976a0  LuaVarAdjuster ---- */
/* Costume tag handler for 'Lua Variable' (registered by sputCostume_Startup through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 4, editor dialog 'Change variable properties'. Original
   name LuaVarAdjuster (the remaster's GrimFandango (Linux): strings: 'Change variable properties');
   was LuaVarComponent_EditKey. */

uint __cdecl LuaVarAdjuster(undefined4 *comp,int outText,int size)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *defaultText;
  int iVar1;
  #define local_20 (*(uint (*)[8])(_frame + (0x30 - 0x20)))
  
  defaultText = (uint *)*comp;
  iVar1 = grimPlat_InputDialog
                    (s_Change_variable_properties_004ea72c,s_Variable_name_004ea748,(char *)local_20
                     ,0x20,(char *)defaultText);
  if (iVar1 != 0) {
    strncpy(defaultText,local_20,0x1f);
    *(undefined1 *)((int)defaultText + 0x1f) = 0;
    strncpy((uint *)outText,local_20,size - 1);
    *(undefined1 *)(size + -1 + outText) = 0;
    return 1;
  }
  return 0;
}
#undef local_20


/* ---- 0x00497710  LuaVarRequester ---- */
/* Costume tag handler for 'Lua Variable' (registered by sputCostume_Startup through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, asks for the variable name ('Name of variable') in
   the editor. Original name LuaVarRequester (the remaster's GrimFandango (Linux): strings: 'Name of
   variable'); was LuaVarComponent_Create. */

int __cdecl LuaVarRequester(uint cosInst,int tag,int parent,int type,int name)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  int iVar2;
  undefined4 *puVar3;
  #define local_20 (*(undefined1 *)(_frame + (0x30 - 0x20)))
  #define local_1f (*(undefined4 *)(_frame + (0x30 - 0x1f)))
  #define local_1 (*(undefined1 *)(_frame + (0x30 - 0x1)))
  
  local_20 = DAT_004f5a98;
  puVar3 = &local_1f;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = 0;
  *(undefined1 *)((int)puVar3 + 2) = 0;
  if (parent != 0) {
    return 0;
  }
  if (name == 0) {
    iVar2 = grimPlat_InputDialog
                      (s_Name_of_variable_004ea758,s_Variable_name_004ea748,&local_20,0x20,&local_20
                      );
    if (iVar2 == 0) {
      return 0;
    }
  }
  else {
    strncpy((uint *)&local_20,(uint *)name,0x1f);
    local_1 = 0;
  }
  puVar1 = (uint *)(*g_pSputCosHS->pAlloc)(0x20,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xd86);
  if (puVar1 == (uint *)0x0) {
    return 0;
  }
  strncpy(puVar1,(uint *)&local_20,0x1f);
  *(undefined1 *)((int)puVar1 + 0x1f) = 0;
  iVar2 = Cos_RegisterComponent(cosInst,(int)puVar1,(int)puVar1,tag,0,type,0);
  return (uint)(iVar2 != 0);
}
#undef local_1
#undef local_1f
#undef local_20


/* ---- 0x004977f0  LuaVarFreer ---- */
/* Costume tag handler for 'Lua Variable' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 2, frees the key data. Original name LuaVarFreer (the
   remaster's GrimFandango (Linux): the same handler slot (freer) of the same costume tag
   registration in sputCostume_Startup); was LuaVarComponent_Destroy. */

uint __cdecl LuaVarFreer(uint tag,uint inst,uint data)

{
  (*g_pSputCosHS->pFree)(data);
  return 1;
}

/* ---- 0x00497810  LuaVarStopper ---- */
/* Costume tag handler for 'Lua Variable' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 3, sets the Lua global to nil. Original name
   LuaVarStopper (the remaster's GrimFandango (Linux): the same handler slot (stopper) of the same
   costume tag registration in sputCostume_Startup); was LuaVarComponent_Stop. */

uint __cdecl LuaVarStopper(char *name)

{
  lua_pushnil();
  lua_setglobal(name);
  return 1;
}
