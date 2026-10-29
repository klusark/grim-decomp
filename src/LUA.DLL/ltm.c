/* LUA.DLL :: ltm.c
 * functions 0x1000c850 .. 0x1000ce50 (15 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000c850  luaT_init ---- */
/* ltm.c (tag methods) */

void luaT_init(void)

{
  int iVar1;
  
  DAT_1002bef0 = 0x10;
  DAT_1002bee8 = -7;
  DAT_1002bf48 = (**(code **)(DAT_1002beb8 + 0x20))
                           (0x900,s_C__grimsrc_libs_lua_src_ltm_cpp_10027ed4,0x4e);
  for (iVar1 = DAT_1002bee8; iVar1 < 1; iVar1 = iVar1 + 1) {
    ltm__c8a0(iVar1);
  }
  return;
}

/* ---- 0x1000c8a0  ltm__c8a0 ---- */
/* Unidentified function of ltm.c (tag methods) */

void __cdecl ltm__c8a0(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = iVar2 + param_1 * -0x90;
    iVar2 = iVar2 + 8;
    *(undefined4 *)(DAT_1002bf48 + iVar1) = 0xfffffff9;
  } while (iVar2 < 0x90);
  return;
}

/* ---- 0x1000c920  luaT_checktag ---- */
/* ltm.c: not result of `newtag' */

void __cdecl luaT_checktag(int param_1)

{
  if ((param_1 < DAT_1002bee8) || (-8 < param_1)) {
    luaL_verror(s_tag__d_is_not_result_of__newtag__10027ef4);
  }
  return;
}

/* ---- 0x1000c9c0  luaT_gettm ---- */
/* Unidentified function of ltm.c (tag methods) */

int __cdecl luaT_gettm(int param_1,int param_2)

{
  if (param_1 < -7) {
    return 1;
  }
  return (int)(char)(&DAT_10027db0)[param_2 + param_1 * -0x12];
}

/* ---- 0x1000c9f0  luaT_realtag ---- */
/* ltm.c: %d is not a valid tag */

void __cdecl luaT_realtag(int param_1)

{
  if ((param_1 < DAT_1002bee8) || (0 < param_1)) {
    luaL_verror(s__d_is_not_a_valid_tag_10027f18);
  }
  return;
}

/* ---- 0x1000ca20  luaT_effectivetag ---- */
/* Unidentified function of ltm.c (tag methods) */

uint __cdecl luaT_effectivetag(uint *param_1)

{
  uint uVar1;
  
  uVar1 = *param_1;
  if (uVar1 == 0xfffffff8) {
    uVar1 = *(uint *)(param_1[1] + 0xc);
  }
  else {
    if (uVar1 == 0xfffffffd) {
      return *(uint *)(param_1[1] + 0x14);
    }
    if (uVar1 == 0) {
      return *(uint *)(param_1[1] + 0x10) & (-1 < (int)*(uint *)(param_1[1] + 0x10)) - 1;
    }
  }
  return uVar1;
}

/* ---- 0x1000ca60  ltm__ca60 ---- */
/* Unidentified function of ltm.c (tag methods) */

undefined * __cdecl ltm__ca60(int param_1,byte *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = luaI_checkevent(param_2,&PTR_s_gettable_10027d48);
  luaT_realtag(param_1);
  iVar2 = luaT_gettm(param_1,iVar1);
  if (iVar2 != 0) {
    return (undefined *)(DAT_1002bf48 + (iVar1 + param_1 * -0x12) * 8);
  }
  return &DAT_100270e0;
}

/* ---- 0x1000cab0  luaI_checkevent ---- */
/* ltm.c: not a valid event name */

int __cdecl luaI_checkevent(byte *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = luaO_findstring(param_1,param_2);
  if (iVar1 < 0) {
    luaL_verror(s____50s__is_not_a_valid_event_nam_10027f30);
  }
  return iVar1;
}

/* ---- 0x1000cae0  ltm__cae0 ---- */
/* Unidentified function of ltm.c (tag methods) */

void __cdecl ltm__cae0(int param_1,byte *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  uVar1 = param_3[1];
  uVar2 = *param_3;
  iVar3 = luaI_checkevent(param_2,&PTR_s_gettable_10027d48);
  luaT_realtag(param_1);
  iVar4 = luaT_gettm(param_1,iVar3);
  if (iVar4 == 0) {
    luaL_verror(s_settagmethod__cannot_change_inte_10027f54);
  }
  iVar3 = (iVar3 + param_1 * -0x12) * 8;
  puVar5 = (undefined4 *)(DAT_1002bf48 + iVar3);
  *param_3 = *puVar5;
  param_3[1] = puVar5[1];
  *(undefined4 *)(DAT_1002bf48 + iVar3) = uVar2;
  *(undefined4 *)(DAT_1002bf48 + 4 + iVar3) = uVar1;
  return;
}

/* ---- 0x1000cb80  ltm__cb80 ---- */
/* Unidentified function of ltm.c (tag methods) */

char * __cdecl ltm__cb80(undefined *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = (*(code *)param_1)(&DAT_1002bf58);
  if (iVar1 != 0) {
    return s_error_10026648;
  }
  iVar2 = 0;
  iVar1 = DAT_1002bee8;
  do {
    iVar4 = 0;
    if (iVar1 < 1) {
      iVar3 = iVar2 * 8;
      do {
        iVar1 = (*(code *)param_1)(DAT_1002bf48 + iVar3);
        if (iVar1 != 0) {
          return (&PTR_s_gettable_10027d48)[iVar2];
        }
        iVar4 = iVar4 + -1;
        iVar3 = iVar3 + 0x90;
        iVar1 = DAT_1002bee8;
      } while (DAT_1002bee8 <= iVar4);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x12);
  return (char *)0x0;
}

/* ---- 0x1000cbf0  FUN_1000cbf0 ---- */
void FUN_1000cbf0(void)

{
  int iVar1;
  
  iVar1 = lua_lua2C(1);
  lua_isstring(iVar1);
  return;
}

/* ---- 0x1000cc10  FUN_1000cc10 ---- */
void FUN_1000cc10(void)

{
  return;
}

/* ---- 0x1000cc20  FUN_1000cc20 ---- */
void FUN_1000cc20(void)

{
  lua_error((byte *)s_unexpected_type_10027f94);
  return;
}

/* ---- 0x1000cc30  FUN_1000cc30 ---- */
void FUN_1000cc30(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  code *pcVar6;
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  if (DAT_1002bf80 == 0) {
    lua_recognizelib(IMG_ADDR(0x10027d98),3);
    DAT_1002bf80 = 1;
  }
  pbVar1 = (byte *)luaL_check_string(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isfunction(iVar2);
  if (iVar3 == 0) {
    luaL_argerror(2,IMG_ADDR(0x10026390));
  }
  iVar3 = luaO_findstring(pbVar1,&PTR_s_error_10027e40);
  switch(iVar3) {
  case 0:
    local_8 = DAT_1002bf58;
    local_4 = DAT_1002bf5c;
    piVar4 = (int *)lapi__11e0(iVar2);
    DAT_1002bf58 = *piVar4;
    DAT_1002bf5c = piVar4[1];
    pcVar6 = FUN_1000cbf0;
    break;
  case 1:
    local_8 = *(int *)(DAT_1002bf48 + 0x408);
    local_4 = *(int *)(DAT_1002bf48 + 0x40c);
    puVar5 = (undefined4 *)lapi__11e0(iVar2);
    *(undefined4 *)(DAT_1002bf48 + 0x408) = *puVar5;
    *(undefined4 *)(DAT_1002bf48 + 0x40c) = puVar5[1];
    pcVar6 = FUN_1000cc10;
    break;
  case 2:
    iVar3 = 5;
    local_8 = *(int *)(DAT_1002bf48 + 0xd8);
    local_4 = *(int *)(DAT_1002bf48 + 0xdc);
    do {
      puVar5 = (undefined4 *)lapi__11e0(iVar2);
      luaT_gettmbyObj(iVar3,puVar5);
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0xb);
    pcVar6 = FUN_1000cc20;
    break;
  case 3:
    iVar3 = 0xb;
    local_8 = *(int *)(DAT_1002bf48 + 0x448);
    local_4 = *(int *)(DAT_1002bf48 + 0x44c);
    do {
      puVar5 = (undefined4 *)lapi__11e0(iVar2);
      luaT_gettmbyObj(iVar3,puVar5);
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0xf);
    pcVar6 = FUN_1000cc20;
    break;
  default:
    iVar3 = luaO_findstring(pbVar1,&PTR_s_gettable_10027d48);
    if (iVar3 < 0) {
      luaL_verror(s____50s__is_not_a_valid_fallback_n_10027fa4);
      pcVar6 = (code *)0x0;
    }
    else {
      local_8 = *(int *)(DAT_1002bf48 + 0x3f0 + iVar3 * 8);
      local_4 = *(int *)(DAT_1002bf48 + 0x3f4 + iVar3 * 8);
      puVar5 = (undefined4 *)lapi__11e0(iVar2);
      luaT_gettmbyObj(iVar3,puVar5);
      if ((iVar3 == 0x10) || (iVar3 == 2)) {
        pcVar6 = FUN_1000cc10;
      }
      else {
        pcVar6 = FUN_1000cc20;
      }
    }
  }
  if (local_8 == -7) {
    lua_pushCclosure((int)pcVar6,0);
    return;
  }
  luaA_pushobject(&local_8);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x1000ce50  luaT_gettmbyObj ---- */
/* Unidentified function of ltm.c (tag methods) */

void __cdecl luaT_gettmbyObj(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = -7;
  iVar3 = param_1 * 8 + 0x3f0;
  do {
    iVar1 = luaT_gettm(iVar2,param_1);
    if (iVar1 != 0) {
      *(undefined4 *)(DAT_1002bf48 + iVar3) = *param_2;
      *(undefined4 *)(DAT_1002bf48 + 4 + iVar3) = param_2[1];
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + -0x90;
  } while (iVar2 < 1);
  return;
}
