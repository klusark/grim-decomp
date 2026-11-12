/* LUA.DLL :: lobject.c
 * functions 0x10007450 .. 0x100075c0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10007450  luaO_redimension ---- */
/* lmem.c: next prime size for a hash; table overflow past the last prime */

undefined4 __cdecl luaO_redimension(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  if (0x7ffffffc < g_dwDimensions[0]) {
    lua_error((byte *)s_table_overflow_100269c8);
    return 0;
  }
  piVar2 = g_dwDimensions;
  iVar1 = g_dwDimensions[0];
  do {
    if (param_1 < iVar1) {
      return g_dwDimensions[iVar3];
    }
    iVar1 = piVar2[1];
    piVar2 = piVar2 + 1;
    iVar3 = iVar3 + 1;
  } while (iVar1 < 0x7ffffffd);
  lua_error((byte *)s_table_overflow_100269c8);
  return 0;
}

/* ---- 0x100074b0  luaO_equalObj ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of lobject.c */

int __cdecl luaO_equalObj(TObject *t1,TObject *t2)

{
  if (t1->nTtype == t2->nTtype) {
    switch(t1->nTtype) {
    case -8:
    case -5:
    case -4:
    case -3:
      return (uint)(t1->dwValue == t2->dwValue);
    case -7:
      return 1;
    case -6:
    case -1:
      if (PUN(float,t2->dwValue) == PUN(float,t1->dwValue)) {
        return 1;
      }
      break;
    case -2:
    case 0:
      return (uint)(t1->dwValue + 0x18 == t2->dwValue + 0x18);
    default:
      lua_error((byte *)s_internal_error_in__lua_equalObj__10027180);
    }
  }
  return 0;
}
#endif


/* ---- 0x10007550  luaO_findstring ---- */
/* Unidentified function of lobject.c */

int __cdecl luaO_findstring(byte *param_1,undefined4 *param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  
  iVar4 = 0;
  pbVar2 = (byte *)*param_2;
  pbVar5 = param_1;
  if (pbVar2 == (byte *)0x0) {
    return -1;
  }
LAB_10007568:
  do {
    bVar1 = *pbVar2;
    bVar6 = bVar1 < *pbVar5;
    if (bVar1 == *pbVar5) {
      if (bVar1 != 0) {
        bVar1 = pbVar2[1];
        bVar6 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_1000758c;
        pbVar2 = pbVar2 + 2;
        pbVar5 = pbVar5 + 2;
        if (bVar1 != 0) goto LAB_10007568;
      }
      iVar3 = 0;
    }
    else {
LAB_1000758c:
      iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
    }
    if (iVar3 == 0) {
      return iVar4;
    }
    pbVar2 = (byte *)param_2[1];
    param_2 = param_2 + 1;
    iVar4 = iVar4 + 1;
    pbVar5 = param_1;
    if (pbVar2 == (byte *)0x0) {
      return -1;
    }
  } while( true );
}

/* ---- 0x100075c0  luaO_insertlist ---- */
/* Unidentified function of lobject.c */

void __cdecl luaO_insertlist(undefined4 *param_1,undefined4 *param_2)

{
  *param_2 = *param_1;
  *param_1 = param_2;
  param_2[1] = 0;
  return;
}
