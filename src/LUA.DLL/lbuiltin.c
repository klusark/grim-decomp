/* LUA.DLL :: lbuiltin.c
 * functions 0x10002d10 .. 0x10003df0 (41 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10002d10  luaL_addsize ---- */
/* Original name luaL_addsize (the remaster's libLua.so: Mbuffnext += n); was lbuiltin__2d10. */

void __cdecl luaL_addsize(int param_1)

{
  g_dwLState_Mbuffnext = g_dwLState_Mbuffnext + param_1;
  return;
}

/* ---- 0x10002d30  luaL_newbuffer ---- */
/* Original name luaL_newbuffer (the remaster's libLua.so: returns the old base, opens space, new
   base = Mbuffer + Mbuffnext); was lbuiltin__2d30. */

int __cdecl luaL_newbuffer(int param_1)

{
  int iVar1;
  
  iVar1 = g_dwLState_Mbuffbase - g_dwLState_Mbuffer;
  if (g_dwLState_Mbuffsize < (uint)(param_1 + g_dwLState_Mbuffnext)) {
    luaL_growbuffer(param_1);
  }
  g_dwLState_Mbuffbase = g_dwLState_Mbuffnext + g_dwLState_Mbuffer;
  return iVar1;
}

/* ---- 0x10002d80  luaL_oldbuffer ---- */
/* Original name luaL_oldbuffer (the remaster's libLua.so: restores Mbuffnext and the base); was
   lbuiltin__2d80. */

void __cdecl luaL_oldbuffer(int param_1)

{
  g_dwLState_Mbuffnext = g_dwLState_Mbuffbase - g_dwLState_Mbuffer;
  g_dwLState_Mbuffbase = param_1 + g_dwLState_Mbuffer;
  return;
}

/* ---- 0x10002da0  luaL_buffer ---- */
/* Original name luaL_buffer (the remaster's libLua.so: returns Mbuffbase); was lbuiltin__2da0. */

undefined4 luaL_buffer(void)

{
  return g_dwLState_Mbuffbase;
}

/* ---- 0x10002db0  nextvar ---- */
/* Original name nextvar (the remaster's libLua.so: int_funcs entry 'nextvar', string 'variable name
   expected'); was FUN_10002db0. */

void nextvar(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  iVar1 = luaL_nonnullarg(1);
  piVar2 = (int *)luaA_Address(iVar1);
  piVar3 = g_dwLState_rootglobal;
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
      pushstring(piVar3);
      luaA_pushobject(piVar3 + 4);
    }
  }
  return;
}

/* ---- 0x10002e40  pushstring ---- */
/* Named pushstring (not in the remaster, gcc inlined it there): Lua 3.1 source name (lbuiltin.c:
   TObject {LUA_T_STRING, ts} pushed with luaA_pushobject, used by nextvar / foreachvar); was
   lbuiltin__2e40. */

void __cdecl pushstring(undefined4 param_1)

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


/* ---- 0x10002e70  foreachvar ---- */
/* Original name foreachvar (the remaster's libLua.so: int_funcs entry 'foreachvar'); was
   FUN_10002e70. */

void foreachvar(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *puVar2;
  #define uStack_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  iVar1 = luaL_functionarg(1);
  puVar2 = (undefined4 *)luaA_Address(iVar1);
  uStack_8 = *puVar2;
  uStack_4 = puVar2[1];
  iVar1 = g_pLuaState[10] * 8;
  g_pLuaState[10] = g_pLuaState[10] + 1;
  *(undefined4 *)(g_pLuaState[8] + iVar1) = 0xfffffff9;
  g_pLuaState[7] = g_pLuaState[7] + 8;
  puVar2 = g_dwLState_rootglobal;
  do {
    if (puVar2 == (undefined4 *)0x0) {
      return;
    }
    if (puVar2[4] != -7) {
      *(undefined4 *)(g_pLuaState[8] + iVar1) = 0xfffffffe;
      *(undefined4 **)(g_pLuaState[8] + 4 + iVar1) = puVar2;
      luaA_pushobject(&uStack_8);
      pushstring(puVar2);
      luaA_pushobject(puVar2 + 4);
      g_pLuaState[2] = g_pLuaState[2] + 1;
      luaD_call((g_pLuaState[7] - g_pLuaState[8] >> 3) + -2,1);
      g_pLuaState[2] = g_pLuaState[2] + -1;
      if (*(int *)(g_pLuaState[7] + -8) != -7) {
        return;
      }
      g_pLuaState[7] = g_pLuaState[7] + -8;
    }
    puVar2 = (undefined4 *)*puVar2;
  } while( true );
}
#undef uStack_4
#undef uStack_8


/* ---- 0x10002f80  next ---- */
/* Original name next (the remaster's libLua.so: int_funcs entry 'next'); was FUN_10002f80. */

void next(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  
  iVar1 = luaL_tablearg(1);
  iVar2 = luaL_nonnullarg(2);
  piVar3 = (int *)luaA_Address(iVar2);
  iVar1 = luaA_Address(iVar1);
  puVar4 = (undefined4 *)luaH_next(iVar1,piVar3);
  if (puVar4 != (undefined4 *)0x0) {
    luaA_pushobject(puVar4);
    luaA_pushobject(puVar4 + 2);
  }
  return;
}

/* ---- 0x10002fd0  foreach ---- */
/* Original name foreach (the remaster's libLua.so: int_funcs entry 'foreach'); was FUN_10002fd0. */

void foreach(void)

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
  iVar1 = luaA_Address(iVar1);
  iVar1 = *(int *)(iVar1 + 4);
  iVar2 = luaL_functionarg(2);
  puVar3 = (undefined4 *)luaA_Address(iVar2);
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
        g_pLuaState[2] = g_pLuaState[2] + 1;
        luaD_call((g_pLuaState[7] - g_pLuaState[8] >> 3) + -2,1);
        g_pLuaState[2] = g_pLuaState[2] + -1;
        if (*(int *)(g_pLuaState[7] + -8) != -7) {
          return;
        }
        g_pLuaState[7] = g_pLuaState[7] + -8;
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


/* ---- 0x100030d0  internaldostring ---- */
/* Original name internaldostring (the remaster's libLua.so: int_funcs entry 'dostring'); was
   FUN_100030d0. */

void internaldostring(void)

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
    iVar1 = luaA_passresults();
    if (iVar1 == 0) {
      lua_pushusertag((byte *)0x0,0);
    }
  }
  return;
}

/* ---- 0x10003120  internaldofile ---- */
/* Original name internaldofile (the remaster's libLua.so: int_funcs entry 'dofile'); was
   FUN_10003120. */

void internaldofile(void)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = (char *)luaL_opt_string(1,0);
  iVar2 = lua_dofile(pcVar1);
  if (iVar2 == 0) {
    iVar2 = luaA_passresults();
    if (iVar2 == 0) {
      lua_pushusertag((byte *)0x0,0);
    }
  }
  return;
}

/* ---- 0x10003150  bi_tostring ---- */
/* Original name bi_tostring (the remaster's libLua.so: int_funcs entry 'tostring'); was
   FUN_10003150. */

void bi_tostring(void)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = lua_lua2C(1);
  pbVar2 = to_string(iVar1);
  lua_pushstring(pbVar2);
  return;
}

/* ---- 0x10003170  to_string ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* lbuiltin.c: userdata: %p / task: %d / table: %p formatting Original name to_string (the
   remaster's libLua.so: static to_string: the strings 'nil', 'table: %p', 'task: %d', 'internal
   error', called by bi_tostring); was luaB_tostring. */

undefined1 * __cdecl to_string(int param_1)

{
  char *buf;
  undefined4 *puVar1;
  undefined1 *puVar2;
  longlong lVar3;
  undefined4 uVar4;
  
  buf = (char *)luaL_openspace(0x1e);
  puVar1 = (undefined4 *)luaA_Address(param_1);
  switch(*puVar1) {
  case 0:
    sprintf(buf,s_userdata___p_10026708,*(undefined4 *)(puVar1[1] + 0x14));
    return buf;
  case 0xfffffff8:
    uVar4 = puVar1[1];
    break;
  case 0xfffffff9:
    return &DAT_100266f8;
  case 0xfffffffa:
    lVar3 = _ftol();
    sprintf(buf,s_task___d_100266fc,(int)lVar3);
    return buf;
  case 0xfffffffb:
    uVar4 = puVar1[1];
    break;
  case 0xfffffffc:
    uVar4 = puVar1[1];
    break;
  case 0xfffffffd:
    sprintf(buf,s_table___p_10026728,puVar1[1]);
    return buf;
  case 0xfffffffe:
  case 0xffffffff:
    puVar2 = (undefined1 *)lua_getstring(param_1);
    return puVar2;
  default:
    lua_error((byte *)s_internal_error_100266e8);
    return (undefined1 *)0x0;
  }
  sprintf(buf,s_function___p_10026718,uVar4);
  return buf;
}
#endif


/* ---- 0x10003260  luaI_startscript ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name luaI_startscript (the remaster's libLua.so: int_funcs entry 'start_script'); was
   lbuiltin__3260. */

void luaI_startscript(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int *this;
  
  iVar3 = lua_lua2C(1);
  iVar4 = lua_isfunction(iVar3);
  if (iVar4 != 0) {
    puVar5 = luaM_malloc(0xd4);
    if (puVar5 == (undefined4 *)0x0) {
      this = (int *)0x0;
    }
    else {
      this = LState_Construct(puVar5);
    }
    this[3] = 0;
    LState_attach(this,(int)g_pLuaState);
    iVar4 = g_pLuaState[8];
    this[0x31] = *(int *)(iVar4 + -8 + iVar3 * 8);
    this[0x32] = *(int *)(iVar4 + -4 + iVar3 * 8);
    piVar2 = g_pLuaState;
    iVar4 = lua_lua2C(2);
    iVar3 = 3;
    while (iVar4 != 0) {
      piVar1 = g_pLuaState + 8;
      g_pLuaState = this;
      luaA_pushobject((undefined4 *)(*piVar1 + -8 + iVar4 * 8));
      g_pLuaState = piVar2;
      iVar4 = lua_lua2C(iVar3);
      iVar3 = iVar3 + 1;
    }
    lua_pushtask(this[0x30]);
  }
  return;
}
#endif


/* ---- 0x10003370  luaI_stopscript ---- */
/* Original name luaI_stopscript (the remaster's libLua.so: int_funcs entry 'stop_script', strings
   'Argument to stopscript must be a task handle or function!'); was FUN_10003370. */

void luaI_stopscript(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *block;
  int iVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  bool bVar5;
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
      uStack_8 = *(undefined4 *)(g_pLuaState[8] + -8 + iVar1 * 8);
      uStack_4 = *(undefined4 *)(g_pLuaState[8] + -4 + iVar1 * 8);
      piVar3 = (int *)LState_next(g_dwL_Main);
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
        if ((bVar5) && (block != g_pLuaState)) {
          piVar3 = (int *)LState_next((int)block);
          if (block != (int *)0x0) {
            LState_Destruct(block);
            luaM_free(block);
          }
        }
        else {
          piVar3 = (int *)LState_next((int)block);
        }
      }
    }
  }
  else {
    iVar1 = lua_gettask(iVar1);
    piVar3 = (int *)LState_next(g_dwL_Main);
    if (piVar3 != (int *)0x0) {
      do {
        if (piVar3[0x30] == iVar1) break;
        piVar3 = (int *)LState_next((int)piVar3);
      } while (piVar3 != (int *)0x0);
      if (piVar3 != (int *)0x0) {
        if (piVar3 == g_pLuaState) {
          lua_error((byte *)s_Current_task_is_committing_suici_10026734);
          return;
        }
        LState_Destruct(piVar3);
        luaM_free(piVar3);
        return;
      }
    }
  }
  return;
}
#undef uStack_4
#undef uStack_8


/* ---- 0x100034c0  luaI_findscript ---- */
/* Original name luaI_findscript (the remaster's libLua.so: strings 'Too few arguments to
   findscript! ...'); was FUN_100034c0. */

void luaI_findscript(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
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
      uStack_8 = *(undefined4 *)(g_pLuaState[8] + -8 + iVar1 * 8);
      uStack_4 = *(undefined4 *)(g_pLuaState[8] + -4 + iVar1 * 8);
      iVar2 = LState_next(g_dwL_Main);
      iVar1 = 0;
      for (; iVar2 != 0; iVar2 = LState_next(iVar2)) {
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
    iVar2 = lua_gettask(iVar1);
    for (iVar4 = LState_next(g_dwL_Main); iVar4 != 0; iVar4 = LState_next(iVar4)) {
      if (*(int *)(iVar4 + 0xc0) == iVar2) {
        lua_pushobject(iVar1);
        lua_pushnumber(1.0);
        return;
      }
    }
  }
  lua_pushnil();
  lua_pushnumber(0.0);
  return;
}
#undef uStack_4
#undef uStack_8


/* ---- 0x10003610  luaI_identifyscript ---- */
/* Original name luaI_identifyscript (the remaster's libLua.so: strings 'Too few arguments to
   identifyscript! ...'); was FUN_10003610. */

void luaI_identifyscript(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  if (iVar1 == 0) {
    lua_error((byte *)s_Too_few_arguments_to_identifyscr_100268a4);
  }
  iVar2 = lua_istask(iVar1);
  if (iVar2 == 0) {
    lua_error((byte *)s_Argument_to_identifyscript_must_b_10026870);
  }
  iVar1 = lua_gettask(iVar1);
  iVar2 = LState_next(g_dwL_Main);
  if (iVar2 != 0) {
    do {
      if (*(int *)(iVar2 + 0xc0) == iVar1) {
        luaA_pushobject((undefined4 *)(iVar2 + 0xc4));
        return;
      }
      iVar2 = LState_next(iVar2);
    } while (iVar2 != 0);
    lua_pushnil();
    return;
  }
  lua_pushnil();
  return;
}

/* ---- 0x100036a0  luaI_nextscript ---- */
/* Original name luaI_nextscript (the remaster's libLua.so: strings 'Too few arguments to
   nextscript! ...'); was FUN_100036a0. */

void luaI_nextscript(void)

{
  int iVar1;
  int iVar2;
  
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
    iVar2 = lua_gettask(iVar1);
    for (iVar1 = LState_next(g_dwL_Main); iVar1 != 0; iVar1 = LState_next(iVar1)) {
      if (*(int *)(iVar1 + 0xc0) == iVar2) {
        iVar1 = LState_next(iVar1);
        if (iVar1 != 0) {
          lua_pushtask(*(int *)(iVar1 + 0xc0));
          return;
        }
        goto LAB_10003741;
      }
    }
  }
  iVar1 = LState_next(g_dwL_Main);
  if (iVar1 != 0) {
    lua_pushtask(*(int *)(iVar1 + 0xc0));
    return;
  }
LAB_10003741:
  lua_pushnil();
  return;
}

/* ---- 0x10003770  luaI_breakhere ---- */
/* Original name luaI_breakhere (the remaster's libLua.so: the empty 'break_here' builtin
   (luaI_breakhere is an empty function in the remaster too)); was FUN_10003770. */

void luaI_breakhere(void)

{
  return;
}

/* ---- 0x10003780  luaI_print ---- */
/* Original name luaI_print (the remaster's libLua.so: int_funcs entry 'print'); was FUN_10003780.
    */

void luaI_print(void)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  
  iVar2 = lua_lua2C(1);
  iVar1 = 2;
  while (iVar2 != 0) {
    puVar3 = to_string(iVar2);
    printf(&DAT_10026960,puVar3);
    iVar2 = lua_lua2C(iVar1);
    iVar1 = iVar1 + 1;
  }
  printf(&DAT_100261f0);
  return;
}

/* ---- 0x100037d0  luaI_type ---- */
/* Original name luaI_type (the remaster's libLua.so: int_funcs entry 'type'); was FUN_100037d0. */

void luaI_type(void)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = luaL_nonnullarg(1);
  piVar2 = (int *)luaA_Address(iVar1);
  lua_pushstring((&g_pLuaO_typenames)[-*piVar2]);
  iVar1 = lua_tag(iVar1);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x10003820  tonumber ---- */
/* Original name tonumber (the remaster's libLua.so: int_funcs entry 'tonumber', string 'base out of
   range'); was FUN_10003820. */

void tonumber(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  longlong lVar5;
  float n;
  #define pbStack_c (*(byte **)(_frame + (0x20 - 0xc)))
  #define uStack_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  lVar5 = FTOL(luaL_opt_number(2,10.0));
  uVar3 = (uint)lVar5;
  if (uVar3 == 10) {
    iVar1 = lua_lua2C(1);
    iVar2 = lua_isnumber(iVar1);
    if (iVar2 != 0) {
      n = lua_getnumber(iVar1);
      lua_pushnumber(n);
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


/* ---- 0x10003910  luaI_error ---- */
/* Original name luaI_error (the remaster's libLua.so: int_funcs entry 'error'); was FUN_10003910.
    */

void luaI_error(void)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = lua_lua2C(1);
  pbVar2 = (byte *)lua_getstring(iVar1);
  lua_error(pbVar2);
  return;
}

/* ---- 0x10003930  luaI_assert ---- */
/* Original name luaI_assert (the remaster's libLua.so: int_funcs entry 'assert'); was FUN_10003930.
    */

void luaI_assert(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = lua_lua2C(1);
  if ((iVar1 != 0) && (iVar1 = lua_isnil(iVar1), iVar1 == 0)) {
    return;
  }
  uVar2 = luaL_opt_string(2,&DAT_1002bedc);
  luaL_verror(s_assertion_failed____100s_10026978,uVar2);
  return;
}

/* ---- 0x10003970  setglobal ---- */
/* Original name setglobal (the remaster's libLua.so: int_funcs entry 'setglobal'); was
   FUN_10003970. */

void setglobal(void)

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

/* ---- 0x100039b0  rawsetglobal ---- */
/* Original name rawsetglobal (the remaster's libLua.so: int_funcs entry 'rawsetglobal'); was
   FUN_100039b0. */

void rawsetglobal(void)

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

/* ---- 0x100039f0  getglobal ---- */
/* Original name getglobal (the remaster's libLua.so: int_funcs entry 'getglobal'); was
   FUN_100039f0. */

void getglobal(void)

{
  byte *pbVar1;
  int iVar2;
  
  pbVar1 = (byte *)luaL_check_string(1);
  iVar2 = lua_getglobal(pbVar1);
  lua_pushobject(iVar2);
  return;
}

/* ---- 0x10003a10  rawgetglobal ---- */
/* Original name rawgetglobal (the remaster's libLua.so: int_funcs entry 'rawgetglobal'); was
   FUN_10003a10. */

void rawgetglobal(void)

{
  byte *pbVar1;
  int iVar2;
  
  pbVar1 = (byte *)luaL_check_string(1);
  iVar2 = lua_rawgetglobal(pbVar1);
  lua_pushobject(iVar2);
  return;
}

/* ---- 0x10003a30  luatag ---- */
/* Original name luatag (the remaster's libLua.so: int_funcs entry 'tag'); was FUN_10003a30. */

void luatag(void)

{
  int iVar1;
  
  iVar1 = lua_lua2C(1);
  iVar1 = lua_tag(iVar1);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x10003a60  luaI_call ---- */
/* Original name luaI_call (the remaster's libLua.so: int_funcs entry 'call'); was FUN_10003a60. */

void luaI_call(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  #define iStack_c (*(int *)(_frame + (0x20 - 0xc)))
  
  iVar1 = luaL_nonnullarg(1);
  iVar2 = luaL_tablearg(2);
  puVar3 = (uint *)luaL_opt_string(3,&DAT_1002bedc);
  iVar4 = lua_lua2C(4);
  iVar5 = getnarg(iVar2);
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
    luaA_passresults();
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


/* ---- 0x10003ba0  getnarg ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Named getnarg (not in the remaster, gcc inlined it there): Lua 3.1 source name (lbuiltin.c:
   rawgettable(table, "n"), number or MAX_WORD, used by luaI_call); was lbuiltin__3ba0. */

int __cdecl getnarg(int param_1)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  lua_pushobject(param_1);
  lua_pushstring(&DAT_10026994);
  iVar1 = lua_rawgettable();
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = FTOL(lua_getnumber(iVar1));
    return (int)lVar3;
  }
  return 0xfffe;
}
#endif


/* ---- 0x10003bf0  settag ---- */
/* Original name settag (the remaster's libLua.so: int_funcs entry 'settag'); was FUN_10003bf0. */

void settag(void)

{
  int iVar1;
  longlong lVar2;
  
  iVar1 = luaL_tablearg(1);
  lua_pushobject(iVar1);
  lVar2 = FTOL(luaL_check_number(2));
  lua_settag((int)lVar2);
  return;
}

/* ---- 0x10003c20  newtag ---- */
/* Original name newtag (the remaster's libLua.so: int_funcs entry 'newtag'); was FUN_10003c20. */

void newtag(void)

{
  int iVar1;
  
  iVar1 = lua_newtag();
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x10003c40  copytagmethods ---- */
/* Original name copytagmethods (the remaster's libLua.so: int_funcs entry 'copytagmethods'); was
   FUN_10003c40. */

void copytagmethods(void)

{
  int iVar1;
  longlong lVar2;
  
  lVar2 = FTOL(luaL_check_number(2));
  iVar1 = (int)lVar2;
  lVar2 = FTOL(luaL_check_number(1));
  iVar1 = lua_copytagmethods((int)lVar2,iVar1);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x10003c80  rawgettable ---- */
/* Original name rawgettable (the remaster's libLua.so: int_funcs entry 'rawgettable'); was
   FUN_10003c80. */

void rawgettable(void)

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

/* ---- 0x10003cc0  rawsettable ---- */
/* lbuiltin.c (built-in functions) Original name rawsettable (the remaster's libLua.so: int_funcs
   entry 'rawsettable'); was luaB_rawsettable. */

void rawsettable(void)

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

/* ---- 0x10003d10  settagmethod ---- */
/* Original name settagmethod (the remaster's libLua.so: int_funcs entry 'settagmethod'); was
   FUN_10003d10. */

void settagmethod(void)

{
  int iVar1;
  byte *pbVar2;
  longlong lVar3;
  
  iVar1 = luaL_nonnullarg(3);
  lua_pushobject(iVar1);
  pbVar2 = (byte *)luaL_check_string(2);
  lVar3 = FTOL(luaL_check_number(1));
  iVar1 = lua_settagmethod((int)lVar3,pbVar2);
  lua_pushobject(iVar1);
  return;
}

/* ---- 0x10003d50  gettagmethod ---- */
/* Original name gettagmethod (the remaster's libLua.so: int_funcs entry 'gettagmethod'); was
   FUN_10003d50. */

void gettagmethod(void)

{
  byte *pbVar1;
  int iVar2;
  longlong lVar3;
  
  pbVar1 = (byte *)luaL_check_string(2);
  lVar3 = FTOL(luaL_check_number(1));
  iVar2 = lua_gettagmethod((int)lVar3,pbVar1);
  lua_pushobject(iVar2);
  return;
}

/* ---- 0x10003d80  seterrormethod ---- */
/* Original name seterrormethod (the remaster's libLua.so: int_funcs entry 'seterrormethod'); was
   FUN_10003d80. */

void seterrormethod(void)

{
  int iVar1;
  
  iVar1 = luaL_functionarg(1);
  lua_pushobject(iVar1);
  iVar1 = lua_seterrormethod();
  lua_pushobject(iVar1);
  return;
}

/* ---- 0x10003db0  luaI_collectgarbage ---- */
/* Original name luaI_collectgarbage (the remaster's libLua.so: int_funcs entry 'collectgarbage');
   was FUN_10003db0. */

void luaI_collectgarbage(void)

{
  int iVar1;
  longlong lVar2;
  
  lVar2 = FTOL(luaL_opt_number(1,0.0));
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
  luaL_openlib(&g_pInt_funcs,0x24);
  lua_pushstring((byte *)s_Lua_3_1__alpha__100269a4);
  lua_setglobal((byte *)s__VERSION_10026998);
  return;
}
