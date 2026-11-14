/* GRIMFANDANGO.EXE :: light.c
 * functions 0x004a5cc0 .. 0x004a5cf0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a5cc0  sputRoom_GetLight ---- */
/* Light record: +0x20 position, +0x2c/+0x38 orientation, +0x30 type (1 parallel/global, 2 omni, 3
   spot), +0x34 on, +0x44 intensity, +0x4c/+0x54 cone angles Original name sputRoom_GetLight (the
   remaster's GrimFandango (Linux): aligned call in sputLua_IsLightOn, sputLua_SetLightType,
   sputLua_TurnLightOn); was Light_Get. */

SetLight * __cdecl sputRoom_GetLight(Set *set,int index)

{
  if (set == (Set *)0x0) {
    set = sputRoom_GetCurrentRoom();
  }
  if ((-1 < index) && (index < set->nLights)) {
    return set->aLights + index;
  }
  return (SetLight *)0x0;
}

/* ---- 0x004a5cf0  sputRoom_FindLightByName ---- */
/* Returns the light index in the current set or -1 Original name sputRoom_FindLightByName (the
   remaster's GrimFandango (Linux): the only unmatched callee of Lua_FindLight; 14 matched
   neighbours agree, 1 disagree); was Light_FindByName. */

int __cdecl sputRoom_FindLightByName(Set *set,char *name)

{
  int iVar1;
  int iVar2;
  SetLight *pSVar3;
  
  if (set == (Set *)0x0) {
    set = sputRoom_GetCurrentRoom();
  }
  iVar2 = 0;
  if (0 < set->nLights) {
    pSVar3 = set->aLights;
    do {
      iVar1 = _stricmp((byte *)name,(byte *)pSVar3);
      if (iVar1 == 0) break;
      iVar2 = iVar2 + 1;
      pSVar3 = pSVar3 + 1;
    } while (iVar2 < set->nLights);
  }
  if (iVar2 < set->nLights) {
    return iVar2;
  }
  return -1;
}
