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
  uint local_4;
  
  lua_pushnumber((float)value);
  lua_setglobal(name);
  return;
}

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
  char *pcVar3;
  #define local_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  local_20[0] = DAT_004f5a98;
  pcVar3 = local_20 + 1;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    pcVar3[0] = '\0';
    pcVar3[1] = '\0';
    pcVar3[2] = '\0';
    pcVar3[3] = '\0';
    pcVar3 = pcVar3 + 4;
  }
  pcVar3[0] = '\0';
  pcVar3[1] = '\0';
  pcVar3[2] = '\0';
  if (parent != 0) {
    return 0;
  }
  if (name == 0) {
    iVar2 = grimPlat_InputDialog
                      (s_Name_of_variable_004ea758,s_Variable_name_004ea748,local_20,0x20,local_20);
    if (iVar2 == 0) {
      return 0;
    }
  }
  else {
    strncpy((uint *)local_20,(uint *)name,0x1f);
    local_20[0x1f] = '\0';
  }
  puVar1 = (uint *)(*g_pSputCosHS->pAlloc)(0x20,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xd86);
  if (puVar1 == (uint *)0x0) {
    return 0;
  }
  strncpy(puVar1,(uint *)local_20,0x1f);
  *(undefined1 *)((int)puVar1 + 0x1f) = 0;
  iVar2 = Cos_RegisterComponent(cosInst,(int)puVar1,(int)puVar1,tag,0,type,0);
  return (uint)(iVar2 != 0);
}
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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char grim_def_s_Change_variable_properties_004ea72c[28] __asm__("_s_Change_variable_properties_004ea72c");
extern char grim_def_s_Name_of_variable_004ea758[20] __asm__("_s_Name_of_variable_004ea758");
extern char grim_def_s_Variable_name_004ea748[16] __asm__("_s_Variable_name_004ea748");
/* 0x004ea72c, 28 bytes */ GRIM_DATA("004ea72c") char grim_def_s_Change_variable_properties_004ea72c[28] __asm__("_s_Change_variable_properties_004ea72c") = "Change variable properties";
/* 0x004ea748, 16 bytes */ /* loose */ char grim_def_s_Variable_name_004ea748[16] __asm__("_s_Variable_name_004ea748") = "Variable name";
/* 0x004ea758, 20 bytes */ /* loose */ char grim_def_s_Name_of_variable_004ea758[20] __asm__("_s_Name_of_variable_004ea758") = "Name of variable";
