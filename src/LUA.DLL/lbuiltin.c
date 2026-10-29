/* LUA.DLL :: lbuiltin.c
 * functions 0x10002d10 .. 0x10003df0 (41 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10002d10  lbuiltin__2d10 ---- */
/* Unidentified function of lbuiltin.c (built-in functions) */

void __cdecl lbuiltin__2d10(int param_1)

{
  DAT_1002bf4c = DAT_1002bf4c + param_1;
  return;
}

/* ---- 0x10002d30  lbuiltin__2d30 ---- */
/* Unidentified function of lbuiltin.c (built-in functions) */

int __cdecl lbuiltin__2d30(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_1002befc - DAT_1002bf40;
  if (DAT_1002bf28 < (uint)(param_1 + DAT_1002bf4c)) {
    luaL_growbuffer(param_1);
  }
  DAT_1002befc = DAT_1002bf4c + DAT_1002bf40;
  return iVar1;
}

/* ---- 0x10002d80  lbuiltin__2d80 ---- */
/* Unidentified function of lbuiltin.c (built-in functions) */

void __cdecl lbuiltin__2d80(int param_1)

{
  DAT_1002bf4c = DAT_1002befc - DAT_1002bf40;
  DAT_1002befc = param_1 + DAT_1002bf40;
  return;
}

/* ---- 0x10002da0  lbuiltin__2da0 ---- */
/* Unidentified function of lbuiltin.c (built-in functions) */

undefined4 lbuiltin__2da0(void)

{
  return DAT_1002befc;
}

/* ---- 0x10002db0  FUN_10002db0 ---- */
void FUN_10002db0(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  iVar1 = luaL_nonnullarg(1);
  piVar2 = (int *)lapi__11e0(iVar1);
  piVar3 = DAT_1002bf00;
  if (*piVar2 != -7) {
    if (*piVar2 != -2) {
      luaL_argerror(1,IMG_ADDR(0x100266a0));
    }
    piVar3 = (int *)piVar2[1];
    if (piVar3 == (int *)*piVar3) {
      luaL_argerror(1,IMG_ADDR(0x100266a0));
    }
    piVar3 = (int *)*piVar3;
  }
  if (piVar3 != (int *)0x0) {
    do {
      if (piVar3[4] != -7) break;
      piVar3 = (int *)*piVar3;
    } while (piVar3 != (int *)0x0);
    if (piVar3 != (int *)0x0) {
      lbuiltin__2e40(piVar3);
      luaA_pushobject(piVar3 + 4);
    }
  }
  return;
}

/* ---- 0x10002e40  lbuiltin__2e40 ---- */
/* Unidentified function of lbuiltin.c (built-in functions) */

void __cdecl lbuiltin__2e40(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  local_8 = 0xfffffffe;
  local_4 = param_1;
  luaA_pushobject(&local_8);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x10002e70  FUN_10002e70 ---- */
void FUN_10002e70(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *puVar2;
  #define uStack_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  iVar1 = luaL_functionarg(1);
  puVar2 = (undefined4 *)lapi__11e0(iVar1);
  uStack_8 = *puVar2;
  uStack_4 = puVar2[1];
  iVar1 = PTR_1002bf6c[10] * 8;
  PTR_1002bf6c[10] = PTR_1002bf6c[10] + 1;
  *(undefined4 *)(PTR_1002bf6c[8] + iVar1) = 0xfffffff9;
  PTR_1002bf6c[7] = PTR_1002bf6c[7] + 8;
  puVar2 = DAT_1002bf00;
  do {
    if (puVar2 == (undefined4 *)0x0) {
      return;
    }
    if (puVar2[4] != -7) {
      *(undefined4 *)(PTR_1002bf6c[8] + iVar1) = 0xfffffffe;
      *(undefined4 **)(PTR_1002bf6c[8] + 4 + iVar1) = puVar2;
      luaA_pushobject(&uStack_8);
      lbuiltin__2e40(puVar2);
      luaA_pushobject(puVar2 + 4);
      PTR_1002bf6c[2] = PTR_1002bf6c[2] + 1;
      luaD_call((PTR_1002bf6c[7] - PTR_1002bf6c[8] >> 3) + -2,1);
      PTR_1002bf6c[2] = PTR_1002bf6c[2] + -1;
      if (*(int *)(PTR_1002bf6c[7] + -8) != -7) {
        return;
      }
      PTR_1002bf6c[7] = PTR_1002bf6c[7] + -8;
    }
    puVar2 = (undefined4 *)*puVar2;
  } while( true );
}
#undef uStack_4
#undef uStack_8


/* ---- 0x10002f80  FUN_10002f80 ---- */
void FUN_10002f80(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  
  iVar1 = luaL_tablearg(1);
  iVar2 = luaL_nonnullarg(2);
  piVar3 = (int *)lapi__11e0(iVar2);
  iVar1 = lapi__11e0(iVar1);
  puVar4 = (undefined4 *)((code *)luaH_next)(iVar1,piVar3);
  if (puVar4 != (undefined4 *)0x0) {
    luaA_pushobject(puVar4);
    luaA_pushobject(puVar4 + 2);
  }
  return;
}

/* ---- 0x10002fd0  FUN_10002fd0 ---- */
void FUN_10002fd0(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  #define uStack_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  iVar1 = luaL_tablearg(1);
  iVar1 = lapi__11e0(iVar1);
  iVar1 = *(int *)(iVar1 + 4);
  iVar2 = luaL_functionarg(2);
  puVar3 = (undefined4 *)lapi__11e0(iVar2);
  uStack_8 = *puVar3;
  iVar2 = 0;
  uStack_4 = puVar3[1];
  uStack_10 = 0;
  if (*(int *)(iVar1 + 0xc) != 0) {
    do {
      piVar4 = (int *)(*(int *)(iVar1 + 8) + iVar2);
      if ((*piVar4 != -7) && (piVar4[2] != -7)) {
        luaA_pushobject(&uStack_8);
        luaA_pushobject(piVar4);
        luaA_pushobject(piVar4 + 2);
        PTR_1002bf6c[2] = PTR_1002bf6c[2] + 1;
        luaD_call((PTR_1002bf6c[7] - PTR_1002bf6c[8] >> 3) + -2,1);
        PTR_1002bf6c[2] = PTR_1002bf6c[2] + -1;
        if (*(int *)(PTR_1002bf6c[7] + -8) != -7) {
          return;
        }
        PTR_1002bf6c[7] = PTR_1002bf6c[7] + -8;
      }
      uStack_10 = uStack_10 + 1;
      iVar2 = iVar2 + 0x10;
    } while (uStack_10 < *(uint *)(iVar1 + 0xc));
  }
  return;
}
#undef uStack_10
#undef uStack_4
#undef uStack_8


/* ---- 0x100030d0  FUN_100030d0 ---- */
void FUN_100030d0(void)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = lua_lua2C(2);
  if (iVar1 != 0) {
    lua_error((byte *)s_invalid_2nd_argument__probably_o_100266b8);
  }
  pcVar2 = (char *)luaL_check_string(1);
  iVar1 = lua_dostring(pcVar2);
  if (iVar1 == 0) {
    iVar1 = lapi__1240();
    if (iVar1 == 0) {
      lua_pushusertag((byte *)0x0,0);
    }
  }
  return;
}

/* ---- 0x10003120  FUN_10003120 ---- */
void FUN_10003120(void)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = (char *)luaL_opt_string(1,0);
  iVar2 = lua_dofile(pcVar1);
  if (iVar2 == 0) {
    iVar2 = lapi__1240();
    if (iVar2 == 0) {
      lua_pushusertag((byte *)0x0,0);
    }
  }
  return;
}

/* ---- 0x10003150  FUN_10003150 ---- */
void FUN_10003150(void)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = lua_lua2C(1);
  pbVar2 = luaB_tostring(iVar1);
  lua_pushstring(pbVar2);
  return;
}

/* ---- 0x10003170  luaB_tostring ---- */
/* lbuiltin.c: userdata: %p / task: %d / table: %p formatting */

undefined1 * __cdecl luaB_tostring(int param_1)

{
  undefined1 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = (undefined1 *)luaL_openspace(0x1e);
  puVar2 = (undefined4 *)lapi__11e0(param_1);
  switch(*puVar2) {
  case 0:
    sprintf(puVar1,s_userdata___p_10026708);
    return puVar1;
  case 0xfffffff8:
    break;
  case 0xfffffff9:
    return &DAT_100266f8;
  case 0xfffffffa:
    _ftol();
    sprintf(puVar1,s_task___d_100266fc);
    return puVar1;
  case 0xfffffffb:
    break;
  case 0xfffffffc:
    break;
  case 0xfffffffd:
    sprintf(puVar1,s_table___p_10026728);
    return puVar1;
  case 0xfffffffe:
  case 0xffffffff:
    puVar1 = (undefined1 *)lua_getstring(param_1);
    return puVar1;
  default:
    lua_error((byte *)s_internal_error_100266e8);
    return (undefined1 *)0x0;
  }
  sprintf(puVar1,s_function___p_10026718);
  return puVar1;
}

/* ---- 0x10003260  lbuiltin__3260 ---- */
/* Unidentified function of lbuiltin.c (built-in functions) */

void lbuiltin__3260(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int *this;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_c (*(undefined4 *)(_frame + (0x20 - 0xc)))
  #define puStack_8 (*(undefined **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0xffffffff;
  puStack_8 = &DAT_10021fbb;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  iVar3 = lua_lua2C(1);
  iVar4 = lua_isfunction(iVar3);
  if (iVar4 != 0) {
    puVar5 = luaM_malloc(0xd4);
    local_4 = 0;
    if (puVar5 == (undefined4 *)0x0) {
      this = (int *)0x0;
    }
    else {
      this = lstate__75e0(puVar5);
    }
    this[3] = 0;
    local_4 = 0xffffffff;
    lstate__8b70(this,(int)PTR_1002bf6c);
    iVar4 = PTR_1002bf6c[8];
    this[0x31] = *(int *)(iVar4 + -8 + iVar3 * 8);
    this[0x32] = *(int *)(iVar4 + -4 + iVar3 * 8);
    piVar2 = PTR_1002bf6c;
    iVar4 = lua_lua2C(2);
    iVar3 = 3;
    while (iVar4 != 0) {
      piVar1 = PTR_1002bf6c + 8;
      PTR_1002bf6c = this;
      luaA_pushobject((undefined4 *)(*piVar1 + -8 + iVar4 * 8));
      PTR_1002bf6c = piVar2;
      iVar4 = lua_lua2C(iVar3);
      iVar3 = iVar3 + 1;
    }
    lua_pushtask(this[0x30]);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}
#undef local_4
#undef local_c
#undef puStack_8


/* ---- 0x10003370  FUN_10003370 ---- */
void FUN_10003370(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *block;
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 extraout_ECX;
  int extraout_EDX;
  char *pcVar4;
  bool bVar5;
  longlong lVar6;
  #define uStack_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  if (iVar1 == 0) {
    lua_error((byte *)s_Too_few_arguments_to_stopscript__10026798);
  }
  iVar2 = lua_isfunction(iVar1);
  if ((iVar2 == 0) && (iVar2 = lua_istask(iVar1), iVar2 == 0)) {
    lua_error((byte *)s_Argument_to_stopscript_must_be_a_1002675c);
  }
  iVar2 = lua_istask(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isfunction(iVar1);
    if (iVar2 != 0) {
      uStack_8 = *(undefined4 *)(PTR_1002bf6c[8] + -8 + iVar1 * 8);
      uStack_4 = *(undefined4 *)(PTR_1002bf6c[8] + -4 + iVar1 * 8);
      piVar3 = (int *)lstate__8bf0(DAT_1002bf70);
      while (block = piVar3, block != (int *)0x0) {
        iVar1 = 8;
        bVar5 = true;
        piVar3 = block + 0x31;
        pcVar4 = (char *)&uStack_8;
        do {
          if (iVar1 == 0) break;
          iVar1 = iVar1 + -1;
          bVar5 = (char)*piVar3 == *pcVar4;
          piVar3 = (int *)((int)piVar3 + 1);
          pcVar4 = pcVar4 + 1;
        } while (bVar5);
        if ((bVar5) && (block != PTR_1002bf6c)) {
          piVar3 = (int *)lstate__8bf0((int)block);
          if (block != (int *)0x0) {
            lstate__8c00(block);
            luaM_free(block);
          }
        }
        else {
          piVar3 = (int *)lstate__8bf0((int)block);
        }
      }
    }
  }
  else {
    lVar6 = lua_gettask(extraout_ECX,extraout_EDX,iVar1);
    piVar3 = (int *)lstate__8bf0(DAT_1002bf70);
    if (piVar3 != (int *)0x0) {
      do {
        if (piVar3[0x30] == (int)lVar6) break;
        piVar3 = (int *)lstate__8bf0((int)piVar3);
      } while (piVar3 != (int *)0x0);
      if (piVar3 != (int *)0x0) {
        if (piVar3 == PTR_1002bf6c) {
          lua_error((byte *)s_Current_task_is_committing_suici_10026734);
          return;
        }
        lstate__8c00(piVar3);
        luaM_free(piVar3);
        return;
      }
    }
  }
  return;
}
#undef uStack_4
#undef uStack_8


/* ---- 0x100034c0  FUN_100034c0 ---- */
void FUN_100034c0(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 extraout_ECX;
  int iVar3;
  int extraout_EDX;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  longlong lVar8;
  #define uStack_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  iVar4 = 0;
  iVar1 = lua_lua2C(1);
  if (iVar1 == 0) {
    lua_error((byte *)s_Too_few_arguments_to_findscript__10026828);
  }
  iVar2 = lua_isfunction(iVar1);
  if ((iVar2 == 0) && (iVar2 = lua_istask(iVar1), iVar2 == 0)) {
    lua_error((byte *)s_Argument_to_findscript_must_be_a_100267ec);
  }
  iVar2 = lua_istask(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isfunction(iVar1);
    if (iVar2 != 0) {
      uStack_8 = *(undefined4 *)(PTR_1002bf6c[8] + -8 + iVar1 * 8);
      uStack_4 = *(undefined4 *)(PTR_1002bf6c[8] + -4 + iVar1 * 8);
      iVar2 = lstate__8bf0(DAT_1002bf70);
      iVar1 = 0;
      for (; iVar2 != 0; iVar2 = lstate__8bf0(iVar2)) {
        iVar3 = 8;
        bVar7 = true;
        pcVar5 = (char *)(iVar2 + 0xc4);
        pcVar6 = (char *)&uStack_8;
        do {
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          bVar7 = *pcVar5 == *pcVar6;
          pcVar5 = pcVar5 + 1;
          pcVar6 = pcVar6 + 1;
        } while (bVar7);
        if (bVar7) {
          iVar1 = *(int *)(iVar2 + 0xc0);
          iVar4 = iVar4 + 1;
        }
      }
      if (iVar4 != 0) {
        lua_pushtask(iVar1);
        lua_pushnumber((float)iVar4);
        return;
      }
    }
  }
  else {
    lVar8 = lua_gettask(extraout_ECX,extraout_EDX,iVar1);
    for (iVar4 = lstate__8bf0(DAT_1002bf70); iVar4 != 0; iVar4 = lstate__8bf0(iVar4)) {
      if (*(int *)(iVar4 + 0xc0) == (int)lVar8) {
        lua_pushobject(iVar1);
        lua_pushnumber(0x3f800000);
        return;
      }
    }
  }
  lua_pushnil();
  lua_pushnumber(0);
  return;
}
#undef uStack_4
#undef uStack_8


/* ---- 0x10003610  FUN_10003610 ---- */
void FUN_10003610(void)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar3;
  int extraout_EDX;
  int extraout_EDX_00;
  int iVar4;
  longlong lVar5;
  
  iVar1 = lua_lua2C(1);
  if (iVar1 == 0) {
    lua_error((byte *)s_Too_few_arguments_to_identifyscr_100268a4);
  }
  iVar2 = lua_istask(iVar1);
  uVar3 = extraout_ECX;
  iVar4 = extraout_EDX;
  if (iVar2 == 0) {
    lua_error((byte *)s_Argument_to_identifyscript_must_b_10026870);
    uVar3 = extraout_ECX_00;
    iVar4 = extraout_EDX_00;
  }
  lVar5 = lua_gettask(uVar3,iVar4,iVar1);
  iVar1 = lstate__8bf0(DAT_1002bf70);
  if (iVar1 != 0) {
    do {
      if (*(int *)(iVar1 + 0xc0) == (int)lVar5) {
        luaA_pushobject((undefined4 *)(iVar1 + 0xc4));
        return;
      }
      iVar1 = lstate__8bf0(iVar1);
    } while (iVar1 != 0);
    lua_pushnil();
    return;
  }
  lua_pushnil();
  return;
}

/* ---- 0x100036a0  FUN_100036a0 ---- */
void FUN_100036a0(void)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_ECX;
  int extraout_EDX;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  if (iVar1 == 0) {
    lua_error((byte *)s_Too_few_arguments_to_nextscript__10026920);
  }
  iVar2 = lua_isnil(iVar1);
  if ((iVar2 == 0) && (iVar2 = lua_istask(iVar1), iVar2 == 0)) {
    lua_error((byte *)s_Argument_to_nextscript_must_be_n_100268e8);
  }
  iVar2 = lua_istask(iVar1);
  if (iVar2 != 0) {
    lVar3 = lua_gettask(extraout_ECX,extraout_EDX,iVar1);
    for (iVar1 = lstate__8bf0(DAT_1002bf70); iVar1 != 0; iVar1 = lstate__8bf0(iVar1)) {
      if (*(int *)(iVar1 + 0xc0) == (int)lVar3) {
        iVar1 = lstate__8bf0(iVar1);
        if (iVar1 != 0) {
          lua_pushtask(*(int *)(iVar1 + 0xc0));
          return;
        }
        goto LAB_10003741;
      }
    }
  }
  iVar1 = lstate__8bf0(DAT_1002bf70);
  if (iVar1 != 0) {
    lua_pushtask(*(int *)(iVar1 + 0xc0));
    return;
  }
LAB_10003741:
  lua_pushnil();
  return;
}

/* ---- 0x10003770  FUN_10003770 ---- */
void FUN_10003770(void)

{
  return;
}

/* ---- 0x10003780  FUN_10003780 ---- */
void FUN_10003780(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = lua_lua2C(1);
  iVar1 = 2;
  while (iVar2 != 0) {
    luaB_tostring(iVar2);
    printf(&DAT_10026960);
    iVar2 = lua_lua2C(iVar1);
    iVar1 = iVar1 + 1;
  }
  printf(&DAT_100261f0);
  return;
}

/* ---- 0x100037d0  FUN_100037d0 ---- */
void FUN_100037d0(void)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = luaL_nonnullarg(1);
  piVar2 = (int *)lapi__11e0(iVar1);
  lua_pushstring((&PTR_s_userdata_100270a8)[-*piVar2]);
  iVar1 = lua_tag(iVar1);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x10003820  FUN_10003820 ---- */
void FUN_10003820(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  float10 fVar5;
  longlong lVar6;
  #define pbStack_c (*(byte **)(_frame + (0x20 - 0xc)))
  #define uStack_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  luaL_opt_number(2,10.0);
  lVar6 = _ftol();
  uVar3 = (uint)lVar6;
  if (uVar3 == 10) {
    iVar1 = lua_lua2C(1);
    iVar2 = lua_isnumber(iVar1);
    if (iVar2 != 0) {
      fVar5 = lua_getnumber(iVar1);
      lua_pushnumber((float)fVar5);
      return;
    }
  }
  else {
    pbStack_c = (byte *)luaL_check_string(1);
    if (((int)uVar3 < 0) || (0x24 < (int)uVar3)) {
      luaL_argerror(2,IMG_ADDR(0x10026964));
    }
    uVar3 = ((code *)strtol)(pbStack_c,&pbStack_c,uVar3);
    uVar4 = FUN_1000f620((int)(char)*pbStack_c);
    while (uVar4 != 0) {
      pbStack_c = pbStack_c + 1;
      uVar4 = FUN_1000f620((int)(char)*pbStack_c);
    }
    if (*pbStack_c == 0) {
      uStack_4 = 0;
      uStack_8 = uVar3;
      lua_pushnumber((float)uVar3);
    }
  }
  return;
}
#undef pbStack_c
#undef uStack_4
#undef uStack_8


/* ---- 0x10003910  FUN_10003910 ---- */
void FUN_10003910(void)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = lua_lua2C(1);
  pbVar2 = (byte *)lua_getstring(iVar1);
  lua_error(pbVar2);
  return;
}

/* ---- 0x10003930  FUN_10003930 ---- */
void FUN_10003930(void)

{
  int iVar1;
  
  iVar1 = lua_lua2C(1);
  if ((iVar1 != 0) && (iVar1 = lua_isnil(iVar1), iVar1 == 0)) {
    return;
  }
  luaL_opt_string(2,&DAT_1002bedc);
  luaL_verror(s_assertion_failed____100s_10026978);
  return;
}

/* ---- 0x10003970  FUN_10003970 ---- */
void FUN_10003970(void)

{
  byte *pbVar1;
  int iVar2;
  
  pbVar1 = (byte *)luaL_check_string(1);
  iVar2 = luaL_nonnullarg(2);
  lua_pushobject(iVar2);
  lua_setglobal(pbVar1);
  lua_pushobject(iVar2);
  return;
}

/* ---- 0x100039b0  FUN_100039b0 ---- */
void FUN_100039b0(void)

{
  byte *pbVar1;
  int iVar2;
  
  pbVar1 = (byte *)luaL_check_string(1);
  iVar2 = luaL_nonnullarg(2);
  lua_pushobject(iVar2);
  lua_rawsetglobal(pbVar1);
  lua_pushobject(iVar2);
  return;
}

/* ---- 0x100039f0  FUN_100039f0 ---- */
void FUN_100039f0(void)

{
  byte *pbVar1;
  int iVar2;
  
  pbVar1 = (byte *)luaL_check_string(1);
  iVar2 = lua_getglobal(pbVar1);
  lua_pushobject(iVar2);
  return;
}

/* ---- 0x10003a10  FUN_10003a10 ---- */
void FUN_10003a10(void)

{
  byte *pbVar1;
  int iVar2;
  
  pbVar1 = (byte *)luaL_check_string(1);
  iVar2 = lua_rawgetglobal(pbVar1);
  lua_pushobject(iVar2);
  return;
}

/* ---- 0x10003a30  FUN_10003a30 ---- */
void FUN_10003a30(void)

{
  int iVar1;
  
  iVar1 = lua_lua2C(1);
  iVar1 = lua_tag(iVar1);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x10003a60  FUN_10003a60 ---- */
void FUN_10003a60(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  #define iStack_c (*(int *)(_frame + (0x20 - 0xc)))
  
  iVar1 = luaL_nonnullarg(1);
  iVar2 = luaL_tablearg(2);
  puVar3 = (uint *)luaL_opt_string(3,&DAT_1002bedc);
  iVar4 = lua_lua2C(4);
  lVar8 = lbuiltin__3ba0(iVar2);
  iVar5 = (int)lVar8;
  iVar6 = 0;
  if (iVar4 != 0) {
    lua_pushobject(iVar4);
    iVar6 = lua_seterrormethod();
  }
  iStack_c = 0;
  if (0 < iVar5) {
    do {
      lua_pushobject(iVar2);
      lua_pushnumber((float)iStack_c - -1.0);
      iVar4 = lua_rawgettable();
      if ((iVar5 == 0xfffe) && (iVar7 = lua_isnil(iVar4), iVar7 != 0)) break;
      lua_pushobject(iVar4);
      iStack_c = iStack_c + 1;
    } while (iStack_c < iVar5);
  }
  iVar1 = lua_callfunction(iVar1);
  if (iVar6 != 0) {
    lua_pushobject(iVar6);
    lua_seterrormethod();
  }
  if (iVar1 == 0) {
    puVar3 = strchr(puVar3,'p');
    if (puVar3 != (uint *)0x0) {
      luaA_packresults();
      return;
    }
    lapi__1240();
  }
  else {
    puVar3 = strchr(puVar3,'x');
    if (puVar3 == (uint *)0x0) {
      lua_error((byte *)0x0);
      return;
    }
  }
  return;
}
#undef iStack_c


/* ---- 0x10003ba0  lbuiltin__3ba0 ---- */
/* Unidentified function of lbuiltin.c (built-in functions) */

longlong __cdecl lbuiltin__3ba0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_EDX;
  longlong lVar3;
  
  lua_pushobject(param_1);
  lua_pushstring(&DAT_10026994);
  iVar1 = lua_rawgettable();
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lua_getnumber(iVar1);
    lVar3 = _ftol();
    return lVar3;
  }
  return CONCAT44(extraout_EDX,0xfffe);
}

/* ---- 0x10003bf0  FUN_10003bf0 ---- */
void FUN_10003bf0(void)

{
  int iVar1;
  longlong lVar2;
  
  iVar1 = luaL_tablearg(1);
  lua_pushobject(iVar1);
  luaL_check_number(2);
  lVar2 = _ftol();
  lua_settag((int)lVar2);
  return;
}

/* ---- 0x10003c20  FUN_10003c20 ---- */
void FUN_10003c20(void)

{
  int iVar1;
  
  iVar1 = lua_newtag();
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x10003c40  FUN_10003c40 ---- */
void FUN_10003c40(void)

{
  int iVar1;
  longlong lVar2;
  
  luaL_check_number(2);
  lVar2 = _ftol();
  iVar1 = (int)lVar2;
  luaL_check_number(1);
  lVar2 = _ftol();
  iVar1 = lua_copytagmethods((int)lVar2,iVar1);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x10003c80  FUN_10003c80 ---- */
void FUN_10003c80(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = luaL_nonnullarg(1);
  iVar2 = luaL_nonnullarg(2);
  lua_pushobject(iVar1);
  lua_pushobject(iVar2);
  iVar1 = lua_rawgettable();
  lua_pushobject(iVar1);
  return;
}

/* ---- 0x10003cc0  luaB_rawsettable ---- */
/* lbuiltin.c (built-in functions) */

void luaB_rawsettable(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = luaL_nonnullarg(1);
  iVar2 = luaL_nonnullarg(2);
  iVar3 = luaL_nonnullarg(3);
  lua_pushobject(iVar1);
  lua_pushobject(iVar2);
  lua_pushobject(iVar3);
  lua_rawsettable();
  return;
}

/* ---- 0x10003d10  FUN_10003d10 ---- */
void FUN_10003d10(void)

{
  int iVar1;
  byte *pbVar2;
  longlong lVar3;
  
  iVar1 = luaL_nonnullarg(3);
  lua_pushobject(iVar1);
  pbVar2 = (byte *)luaL_check_string(2);
  luaL_check_number(1);
  lVar3 = _ftol();
  iVar1 = lua_settagmethod((int)lVar3,pbVar2);
  lua_pushobject(iVar1);
  return;
}

/* ---- 0x10003d50  FUN_10003d50 ---- */
void FUN_10003d50(void)

{
  byte *pbVar1;
  int iVar2;
  longlong lVar3;
  
  pbVar1 = (byte *)luaL_check_string(2);
  luaL_check_number(1);
  lVar3 = _ftol();
  iVar2 = lua_gettagmethod((int)lVar3,pbVar1);
  lua_pushobject(iVar2);
  return;
}

/* ---- 0x10003d80  FUN_10003d80 ---- */
void FUN_10003d80(void)

{
  int iVar1;
  
  iVar1 = luaL_functionarg(1);
  lua_pushobject(iVar1);
  iVar1 = lua_seterrormethod();
  lua_pushobject(iVar1);
  return;
}

/* ---- 0x10003db0  FUN_10003db0 ---- */
void FUN_10003db0(void)

{
  int iVar1;
  longlong lVar2;
  
  luaL_opt_number(1,0.0);
  lVar2 = _ftol();
  iVar1 = lua_collectgarbage((int)lVar2);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x10003df0  luaB_predefine ---- */
/* lbuiltin.c: registers the built-in functions and the setfallback compatibility entry */

void luaB_predefine(void)

{
  luaS_newfixedstring((byte *)s_table_overflow_100269c8);
  luaS_newfixedstring((byte *)s_not_enough_memory_100269b4);
  luaL_openlib(&PTR_s_setfallback_100263d8,0x24);
  lua_pushstring((byte *)s_Lua_3_1__alpha__100269a4);
  lua_setglobal((byte *)s__VERSION_10026998);
  return;
}
