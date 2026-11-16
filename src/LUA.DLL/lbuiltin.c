/* LUA.DLL :: lbuiltin.c
 * functions 0x10002d10 .. 0x10003df0 (41 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10002d10  luaL_addsize ---- */
/* Original name luaL_addsize (the remaster's libLua.so: Mbuffnext += n); was lbuiltin__2d10. */

void __cdecl luaL_addsize(int n)

{
  g_dwLState_Mbuffnext = g_dwLState_Mbuffnext + n;
  return;
}

/* ---- 0x10002d30  luaL_newbuffer ---- */
/* Original name luaL_newbuffer (the remaster's libLua.so: returns the old base, opens space, new
   base = Mbuffer + Mbuffnext); was lbuiltin__2d30. */

int __cdecl luaL_newbuffer(int size)

{
  int iVar1;
  
  iVar1 = g_dwLState_Mbuffbase - g_dwLState_Mbuffer;
  if (g_dwLState_Mbuffsize < (uint)(size + g_dwLState_Mbuffnext)) {
    Lbuffer_Openspace(size);
  }
  g_dwLState_Mbuffbase = g_dwLState_Mbuffnext + g_dwLState_Mbuffer;
  return iVar1;
}

/* ---- 0x10002d80  luaL_oldbuffer ---- */
/* Original name luaL_oldbuffer (the remaster's libLua.so: restores Mbuffnext and the base); was
   lbuiltin__2d80. */

void __cdecl luaL_oldbuffer(int old)

{
  g_dwLState_Mbuffnext = g_dwLState_Mbuffbase - g_dwLState_Mbuffer;
  g_dwLState_Mbuffbase = old + g_dwLState_Mbuffer;
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

void __cdecl nextvar(void)

{
  int o;
  int *piVar1;
  int *piVar2;
  
  o = luaL_nonnullarg(1);
  piVar1 = (int *)luaA_Address(o);
  piVar2 = g_dwLState_rootglobal;
  if (*piVar1 != -7) {
    if (*piVar1 != -2) {
      luaL_argerror(1,((unsigned)(uintptr_t)&s_variable_name_expected_100266a0));
    }
    piVar2 = (int *)piVar1[1];
    if (piVar2 == (int *)*piVar2) {
      luaL_argerror(1,((unsigned)(uintptr_t)&s_variable_name_expected_100266a0));
    }
    piVar2 = (int *)*piVar2;
  }
  if (piVar2 != (int *)0x0) {
    do {
      if (piVar2[4] != -7) break;
      piVar2 = (int *)*piVar2;
    } while (piVar2 != (int *)0x0);
    if (piVar2 != (int *)0x0) {
      pushstring((uint)piVar2);
      luaA_pushobject((TObject *)(piVar2 + 4));
    }
  }
  return;
}

/* ---- 0x10002e40  pushstring ---- */
/* Named pushstring (not in the remaster, gcc inlined it there): Lua 3.1 source name (lbuiltin.c:
   TObject {LUA_T_STRING, ts} pushed with luaA_pushobject, used by nextvar / foreachvar); was
   lbuiltin__2e40. */

void __cdecl pushstring(uint s)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(TObject *)(_frame + (0x20 - 0x8)))
  
  local_8.nTtype = -2;
  local_8.dwValue = s;
  luaA_pushobject(&local_8);
  return;
}
#undef local_8


/* ---- 0x10002e70  foreachvar ---- */
/* Original name foreachvar (the remaster's libLua.so: int_funcs entry 'foreachvar'); was
   FUN_10002e70. */

void __cdecl foreachvar(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *s;
  int iVar1;
  int *piVar2;
  #define TStack_8 (*(TObject *)(_frame + (0x20 - 0x8)))
  
  iVar1 = luaL_functionarg(1);
  piVar2 = (int *)luaA_Address(iVar1);
  TStack_8.nTtype = *piVar2;
  TStack_8.dwValue = piVar2[1];
  iVar1 = (g_pLuaState->Cstack).nBase;
  (g_pLuaState->Cstack).nBase = iVar1 + 1;
  g_pLuaState->pStack[iVar1].nTtype = -7;
  g_pLuaState->pTop = g_pLuaState->pTop + 1;
  s = g_dwLState_rootglobal;
  do {
    if (s == (undefined4 *)0x0) {
      return;
    }
    if (s[4] != -7) {
      g_pLuaState->pStack[iVar1].nTtype = -2;
      g_pLuaState->pStack[iVar1].dwValue = (uint)s;
      luaA_pushobject(&TStack_8);
      pushstring((uint)s);
      luaA_pushobject((TObject *)(s + 4));
      g_pLuaState->nPreventBreak = g_pLuaState->nPreventBreak + 1;
      luaD_call(((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3) + -2,1);
      g_pLuaState->nPreventBreak = g_pLuaState->nPreventBreak + -1;
      if (g_pLuaState->pTop[-1].nTtype != -7) {
        return;
      }
      g_pLuaState->pTop = g_pLuaState->pTop + -1;
    }
    s = (undefined4 *)*s;
  } while( true );
}
#undef TStack_8


/* ---- 0x10002f80  next ---- */
/* Original name next (the remaster's libLua.so: int_funcs entry 'next'); was FUN_10002f80. */

void __cdecl next(void)

{
  int o;
  int o_00;
  TObject *r;
  TObject *o_01;
  Node *o_02;
  
  o = luaL_tablearg(1);
  o_00 = luaL_nonnullarg(2);
  r = (TObject *)luaA_Address(o_00);
  o_01 = (TObject *)luaA_Address(o);
  o_02 = luaH_next(o_01,r);
  if (o_02 != (Node *)0x0) {
    luaA_pushobject(&o_02->ref);
    luaA_pushobject(&o_02->val);
  }
  return;
}

/* ---- 0x10002fd0  foreach ---- */
/* Original name foreach (the remaster's libLua.so: int_funcs entry 'foreach'); was FUN_10002fd0. */

void __cdecl foreach(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int *piVar3;
  TObject *o;
  uint uStack_10;
  #define TStack_8 (*(TObject *)(_frame + (0x20 - 0x8)))
  
  iVar1 = luaL_tablearg(1);
  iVar1 = luaA_Address(iVar1);
  iVar1 = *(int *)(iVar1 + 4);
  iVar2 = luaL_functionarg(2);
  piVar3 = (int *)luaA_Address(iVar2);
  TStack_8.nTtype = *piVar3;
  iVar2 = 0;
  TStack_8.dwValue = piVar3[1];
  uStack_10 = 0;
  if (*(int *)(iVar1 + 0xc) != 0) {
    do {
      o = (TObject *)(*(int *)(iVar1 + 8) + iVar2);
      if ((o->nTtype != -7) && (o[1].nTtype != -7)) {
        luaA_pushobject(&TStack_8);
        luaA_pushobject(o);
        luaA_pushobject(o + 1);
        g_pLuaState->nPreventBreak = g_pLuaState->nPreventBreak + 1;
        luaD_call(((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3) + -2,1);
        g_pLuaState->nPreventBreak = g_pLuaState->nPreventBreak + -1;
        if (g_pLuaState->pTop[-1].nTtype != -7) {
          return;
        }
        g_pLuaState->pTop = g_pLuaState->pTop + -1;
      }
      uStack_10 = uStack_10 + 1;
      iVar2 = iVar2 + 0x10;
    } while (uStack_10 < *(uint *)(iVar1 + 0xc));
  }
  return;
}
#undef TStack_8


/* ---- 0x100030d0  internaldostring ---- */
/* Original name internaldostring (the remaster's libLua.so: int_funcs entry 'dostring'); was
   FUN_100030d0. */

void __cdecl internaldostring(void)

{
  int iVar1;
  char *str;
  
  iVar1 = lua_lua2C(2);
  if (iVar1 != 0) {
    lua_error((byte *)s_invalid_2nd_argument__probably_o_100266b8);
  }
  str = (char *)luaL_check_string(1);
  iVar1 = lua_dostring(str);
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

void __cdecl internaldofile(void)

{
  char *filename;
  int iVar1;
  
  filename = (char *)luaL_opt_string(1,0);
  iVar1 = lua_dofile(filename);
  if (iVar1 == 0) {
    iVar1 = luaA_passresults();
    if (iVar1 == 0) {
      lua_pushusertag((byte *)0x0,0);
    }
  }
  return;
}

/* ---- 0x10003150  bi_tostring ---- */
/* Original name bi_tostring (the remaster's libLua.so: int_funcs entry 'tostring'); was
   FUN_10003150. */

void __cdecl bi_tostring(void)

{
  int obj;
  byte *str;
  
  obj = lua_lua2C(1);
  str = to_string(obj);
  lua_pushstring(str);
  return;
}

/* ---- 0x10003170  to_string ---- */
/* lbuiltin.c: userdata: %p / task: %d / table: %p formatting Original name to_string (the
   remaster's libLua.so: static to_string: the strings 'nil', 'table: %p', 'task: %d', 'internal
   error', called by bi_tostring); was luaB_tostring. */

undefined1 * __cdecl to_string(int obj)

{
  char *buf;
  undefined4 *puVar1;
  undefined1 *puVar2;
  longlong lVar3;
  undefined4 uVar4;
  
  buf = (char *)luaL_openspace(0x1e);
  puVar1 = (undefined4 *)luaA_Address(obj);
  switch(*puVar1) {
  case 0:
    sprintf(buf,s_userdata___p_10026708,*(undefined4 *)(puVar1[1] + 0x14));
    return buf;
  case 0xfffffff8:
    uVar4 = puVar1[1];
    break;
  case 0xfffffff9:
    return s_nil_100266f8;
  case 0xfffffffa:
    lVar3 = FTOL((float10)PUN(float,puVar1[1]));
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
    puVar2 = (undefined1 *)lua_getstring(obj);
    return puVar2;
  default:
    lua_error((byte *)s_internal_error_100266e8);
    return (undefined1 *)0x0;
  }
  sprintf(buf,s_function___p_10026718,uVar4);
  return buf;
}

/* ---- 0x10003260  luaI_startscript ---- */
/* Original name luaI_startscript (the remaster's libLua.so: int_funcs entry 'start_script'); was
   lbuiltin__3260. */

void luaI_startscript(void)

{
  TObject **ppTVar1;
  TObject *pTVar2;
  LState *pLVar3;
  int iVar4;
  int iVar5;
  LState *pLVar6;
  
  iVar4 = lua_lua2C(1);
  iVar5 = lua_isfunction(iVar4);
  if (iVar5 != 0) {
    pLVar6 = luaM_malloc(0xd4);
    if (pLVar6 == (LState *)0x0) {
      pLVar6 = (LState *)0x0;
    }
    else {
      pLVar6 = LState_Construct(pLVar6);
    }
    pLVar6->nUnread = 0;
    LState_attach(pLVar6,(int)g_pLuaState);
    pTVar2 = g_pLuaState->pStack;
    (pLVar6->taskFunc).nTtype = pTVar2[iVar4 + -1].nTtype;
    (pLVar6->taskFunc).dwValue = pTVar2[iVar4 + -1].dwValue;
    pLVar3 = g_pLuaState;
    iVar5 = lua_lua2C(2);
    iVar4 = 3;
    while (iVar5 != 0) {
      ppTVar1 = &g_pLuaState->pStack;
      g_pLuaState = pLVar6;
      luaA_pushobject(*ppTVar1 + iVar5 + -1);
      g_pLuaState = pLVar3;
      iVar5 = lua_lua2C(iVar4);
      iVar4 = iVar4 + 1;
    }
    lua_pushtask(pLVar6->nTaskId);
  }
  return;
}

/* ---- 0x10003370  luaI_stopscript ---- */
/* Original name luaI_stopscript (the remaster's libLua.so: int_funcs entry 'stop_script', strings
   'Argument to stopscript must be a task handle or function!'); was FUN_10003370. */

void __cdecl luaI_stopscript(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  LState *L;
  int iVar1;
  int iVar2;
  LState *pLVar3;
  TObject *pTVar4;
  int *piVar5;
  bool bVar6;
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
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
      iStack_8 = g_pLuaState->pStack[iVar1 + -1].nTtype;
      uStack_4 = g_pLuaState->pStack[iVar1 + -1].dwValue;
      pLVar3 = LState_next(g_dwL_Main);
      while (L = pLVar3, L != (LState *)0x0) {
        iVar1 = 8;
        bVar6 = true;
        pTVar4 = &L->taskFunc;
        piVar5 = &iStack_8;
        do {
          if (iVar1 == 0) break;
          iVar1 = iVar1 + -1;
          bVar6 = (char)pTVar4->nTtype == (char)*piVar5;
          pTVar4 = (TObject *)((int)&pTVar4->nTtype + 1);
          piVar5 = (int *)((int)piVar5 + 1);
        } while (bVar6);
        if ((bVar6) && (L != g_pLuaState)) {
          pLVar3 = LState_next(L);
          if (L != (LState *)0x0) {
            LState_Destruct(L);
            luaM_free(L);
          }
        }
        else {
          pLVar3 = LState_next(L);
        }
      }
    }
  }
  else {
    iVar1 = lua_gettask(iVar1);
    pLVar3 = LState_next(g_dwL_Main);
    if (pLVar3 != (LState *)0x0) {
      do {
        if (pLVar3->nTaskId == iVar1) break;
        pLVar3 = LState_next(pLVar3);
      } while (pLVar3 != (LState *)0x0);
      if (pLVar3 != (LState *)0x0) {
        if (pLVar3 == g_pLuaState) {
          lua_error((byte *)s_Current_task_is_committing_suici_10026734);
          return;
        }
        LState_Destruct(pLVar3);
        luaM_free(pLVar3);
        return;
      }
    }
  }
  return;
}
#undef iStack_8
#undef uStack_4


/* ---- 0x100034c0  luaI_findscript ---- */
/* Original name luaI_findscript (the remaster's libLua.so: strings 'Too few arguments to
   findscript! ...'); was FUN_100034c0. */

void __cdecl luaI_findscript(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  LState *pLVar3;
  int iVar4;
  TObject *pTVar5;
  int *piVar6;
  bool bVar7;
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
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
      iStack_8 = g_pLuaState->pStack[iVar1 + -1].nTtype;
      uStack_4 = g_pLuaState->pStack[iVar1 + -1].dwValue;
      pLVar3 = LState_next(g_dwL_Main);
      iVar1 = 0;
      for (; pLVar3 != (LState *)0x0; pLVar3 = LState_next(pLVar3)) {
        iVar2 = 8;
        bVar7 = true;
        pTVar5 = &pLVar3->taskFunc;
        piVar6 = &iStack_8;
        do {
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          bVar7 = (char)pTVar5->nTtype == (char)*piVar6;
          pTVar5 = (TObject *)((int)&pTVar5->nTtype + 1);
          piVar6 = (int *)((int)piVar6 + 1);
        } while (bVar7);
        if (bVar7) {
          iVar1 = pLVar3->nTaskId;
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
    iVar4 = lua_gettask(iVar1);
    for (pLVar3 = LState_next(g_dwL_Main); pLVar3 != (LState *)0x0; pLVar3 = LState_next(pLVar3)) {
      if (pLVar3->nTaskId == iVar4) {
        lua_pushobject(iVar1);
        lua_pushnumber(1.0f);
        return;
      }
    }
  }
  lua_pushnil();
  lua_pushnumber(0.0f);
  return;
}
#undef iStack_8
#undef uStack_4


/* ---- 0x10003610  luaI_identifyscript ---- */
/* Original name luaI_identifyscript (the remaster's libLua.so: strings 'Too few arguments to
   identifyscript! ...'); was FUN_10003610. */

void __cdecl luaI_identifyscript(void)

{
  int iVar1;
  int iVar2;
  LState *L;
  
  iVar1 = lua_lua2C(1);
  if (iVar1 == 0) {
    lua_error((byte *)s_Too_few_arguments_to_identifyscr_100268a4);
  }
  iVar2 = lua_istask(iVar1);
  if (iVar2 == 0) {
    lua_error((byte *)s_Argument_to_identifyscript_must_b_10026870);
  }
  iVar1 = lua_gettask(iVar1);
  L = LState_next(g_dwL_Main);
  if (L != (LState *)0x0) {
    do {
      if (L->nTaskId == iVar1) {
        luaA_pushobject(&L->taskFunc);
        return;
      }
      L = LState_next(L);
    } while (L != (LState *)0x0);
    lua_pushnil();
    return;
  }
  lua_pushnil();
  return;
}

/* ---- 0x100036a0  luaI_nextscript ---- */
/* Original name luaI_nextscript (the remaster's libLua.so: strings 'Too few arguments to
   nextscript! ...'); was FUN_100036a0. */

void __cdecl luaI_nextscript(void)

{
  int iVar1;
  int iVar2;
  LState *pLVar3;
  
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
    iVar1 = lua_gettask(iVar1);
    for (pLVar3 = LState_next(g_dwL_Main); pLVar3 != (LState *)0x0; pLVar3 = LState_next(pLVar3)) {
      if (pLVar3->nTaskId == iVar1) {
        pLVar3 = LState_next(pLVar3);
        if (pLVar3 != (LState *)0x0) {
          lua_pushtask(pLVar3->nTaskId);
          return;
        }
        goto LAB_10003741;
      }
    }
  }
  pLVar3 = LState_next(g_dwL_Main);
  if (pLVar3 != (LState *)0x0) {
    lua_pushtask(pLVar3->nTaskId);
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

void __cdecl luaI_print(void)

{
  int number;
  int obj;
  undefined1 *puVar1;
  
  obj = lua_lua2C(1);
  number = 2;
  while (obj != 0) {
    puVar1 = to_string(obj);
    printf(s__s_10026960,puVar1);
    obj = lua_lua2C(number);
    number = number + 1;
  }
  printf(s__100261f0);
  return;
}

/* ---- 0x100037d0  luaI_type ---- */
/* Original name luaI_type (the remaster's libLua.so: int_funcs entry 'type'); was FUN_100037d0. */

void __cdecl luaI_type(void)

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

void __cdecl tonumber(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int o;
  int iVar1;
  uint uVar2;
  uint uVar3;
  longlong lVar4;
  float fVar5;
  #define pbStack_c (*(byte **)(_frame + (0x20 - 0xc)))
  #define uStack_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  fVar5 = luaL_opt_number(2,10.0f);
  lVar4 = FTOL((float10)fVar5);
  uVar2 = (uint)lVar4;
  if (uVar2 == 10) {
    o = lua_lua2C(1);
    iVar1 = lua_isnumber(o);
    if (iVar1 != 0) {
      fVar5 = lua_getnumber(o);
      lua_pushnumber(fVar5);
      return;
    }
  }
  else {
    pbStack_c = (byte *)luaL_check_string(1);
    if (((int)uVar2 < 0) || (0x24 < (int)uVar2)) {
      luaL_argerror(2,((unsigned)(uintptr_t)&s_base_out_of_range_10026964));
    }
    uVar2 = ((code *)strtol)(pbStack_c,&pbStack_c,uVar2);
    uVar3 = FUN_1000f620((int)(char)*pbStack_c);
    while (uVar3 != 0) {
      pbStack_c = pbStack_c + 1;
      uVar3 = FUN_1000f620((int)(char)*pbStack_c);
    }
    if (*pbStack_c == 0) {
      uStack_4 = 0;
      uStack_8 = uVar2;
      lua_pushnumber((float)uVar2);
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

void __cdecl luaI_error(void)

{
  int o;
  byte *s;
  
  o = lua_lua2C(1);
  s = (byte *)lua_getstring(o);
  lua_error(s);
  return;
}

/* ---- 0x10003930  luaI_assert ---- */
/* Original name luaI_assert (the remaster's libLua.so: int_funcs entry 'assert'); was FUN_10003930.
    */

void __cdecl luaI_assert(void)

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

void __cdecl setglobal(void)

{
  byte *str;
  int o;
  
  str = (byte *)luaL_check_string(1);
  o = luaL_nonnullarg(2);
  lua_pushobject(o);
  lua_setglobal(str);
  lua_pushobject(o);
  return;
}

/* ---- 0x100039b0  rawsetglobal ---- */
/* Original name rawsetglobal (the remaster's libLua.so: int_funcs entry 'rawsetglobal'); was
   FUN_100039b0. */

void __cdecl rawsetglobal(void)

{
  byte *str;
  int o;
  
  str = (byte *)luaL_check_string(1);
  o = luaL_nonnullarg(2);
  lua_pushobject(o);
  lua_rawsetglobal(str);
  lua_pushobject(o);
  return;
}

/* ---- 0x100039f0  getglobal ---- */
/* Original name getglobal (the remaster's libLua.so: int_funcs entry 'getglobal'); was
   FUN_100039f0. */

void __cdecl getglobal(void)

{
  byte *str;
  int o;
  
  str = (byte *)luaL_check_string(1);
  o = lua_getglobal(str);
  lua_pushobject(o);
  return;
}

/* ---- 0x10003a10  rawgetglobal ---- */
/* Original name rawgetglobal (the remaster's libLua.so: int_funcs entry 'rawgetglobal'); was
   FUN_10003a10. */

void __cdecl rawgetglobal(void)

{
  byte *str;
  int o;
  
  str = (byte *)luaL_check_string(1);
  o = lua_rawgetglobal(str);
  lua_pushobject(o);
  return;
}

/* ---- 0x10003a30  luatag ---- */
/* Original name luatag (the remaster's libLua.so: int_funcs entry 'tag'); was FUN_10003a30. */

void __cdecl luatag(void)

{
  int iVar1;
  
  iVar1 = lua_lua2C(1);
  iVar1 = lua_tag(iVar1);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x10003a60  luaI_call ---- */
/* Original name luaI_call (the remaster's libLua.so: int_funcs entry 'call'); was FUN_10003a60. */

void __cdecl luaI_call(void)

{
  int iVar1;
  int table;
  uint *puVar2;
  int iVar3;
  int iVar4;
  int o;
  int iVar5;
  int iStack_c;
  
  iVar1 = luaL_nonnullarg(1);
  table = luaL_tablearg(2);
  puVar2 = (uint *)luaL_opt_string(3,&DAT_1002bedc);
  iVar3 = lua_lua2C(4);
  iVar4 = getnarg(table);
  o = 0;
  if (iVar3 != 0) {
    lua_pushobject(iVar3);
    o = lua_seterrormethod();
  }
  iStack_c = 0;
  if (0 < iVar4) {
    do {
      lua_pushobject(table);
      lua_pushnumber((float)iStack_c - -1.0f);
      iVar3 = lua_rawgettable();
      if ((iVar4 == 0xfffe) && (iVar5 = lua_isnil(iVar3), iVar5 != 0)) break;
      lua_pushobject(iVar3);
      iStack_c = iStack_c + 1;
    } while (iStack_c < iVar4);
  }
  iVar1 = lua_callfunction(iVar1);
  if (o != 0) {
    lua_pushobject(o);
    lua_seterrormethod();
  }
  if (iVar1 == 0) {
    puVar2 = strchr(puVar2,'p');
    if (puVar2 != (uint *)0x0) {
      luaA_packresults();
      return;
    }
    luaA_passresults();
  }
  else {
    puVar2 = strchr(puVar2,'x');
    if (puVar2 == (uint *)0x0) {
      lua_error((byte *)0x0);
      return;
    }
  }
  return;
}

/* ---- 0x10003ba0  getnarg ---- */
/* Named getnarg (not in the remaster, gcc inlined it there): Lua 3.1 source name (lbuiltin.c:
   rawgettable(table, "n"), number or MAX_WORD, used by luaI_call); was lbuiltin__3ba0. */

int __cdecl getnarg(int table)

{
  int o;
  int iVar1;
  longlong lVar2;
  float fVar3;
  
  lua_pushobject(table);
  lua_pushstring((byte *)s_n_10026994);
  o = lua_rawgettable();
  iVar1 = lua_isnumber(o);
  if (iVar1 != 0) {
    fVar3 = lua_getnumber(o);
    lVar2 = FTOL((float10)fVar3);
    return (int)lVar2;
  }
  return 0xfffe;
}

/* ---- 0x10003bf0  settag ---- */
/* Original name settag (the remaster's libLua.so: int_funcs entry 'settag'); was FUN_10003bf0. */

void __cdecl settag(void)

{
  int o;
  longlong lVar1;
  float fVar2;
  
  o = luaL_tablearg(1);
  lua_pushobject(o);
  fVar2 = luaL_check_number(2);
  lVar1 = FTOL((float10)fVar2);
  lua_settag((int)lVar1);
  return;
}

/* ---- 0x10003c20  newtag ---- */
/* Original name newtag (the remaster's libLua.so: int_funcs entry 'newtag'); was FUN_10003c20. */

void __cdecl newtag(void)

{
  int iVar1;
  
  iVar1 = lua_newtag();
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x10003c40  copytagmethods ---- */
/* Original name copytagmethods (the remaster's libLua.so: int_funcs entry 'copytagmethods'); was
   FUN_10003c40. */

void __cdecl copytagmethods(void)

{
  int iVar1;
  longlong lVar2;
  float fVar3;
  
  fVar3 = luaL_check_number(2);
  lVar2 = FTOL((float10)fVar3);
  iVar1 = (int)lVar2;
  fVar3 = luaL_check_number(1);
  lVar2 = FTOL((float10)fVar3);
  iVar1 = lua_copytagmethods((int)lVar2,iVar1);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x10003c80  rawgettable ---- */
/* Original name rawgettable (the remaster's libLua.so: int_funcs entry 'rawgettable'); was
   FUN_10003c80. */

void __cdecl rawgettable(void)

{
  int iVar1;
  int o;
  
  iVar1 = luaL_nonnullarg(1);
  o = luaL_nonnullarg(2);
  lua_pushobject(iVar1);
  lua_pushobject(o);
  iVar1 = lua_rawgettable();
  lua_pushobject(iVar1);
  return;
}

/* ---- 0x10003cc0  rawsettable ---- */
/* lbuiltin.c (built-in functions) Original name rawsettable (the remaster's libLua.so: int_funcs
   entry 'rawsettable'); was luaB_rawsettable. */

void rawsettable(void)

{
  int o;
  int o_00;
  int o_01;
  
  o = luaL_nonnullarg(1);
  o_00 = luaL_nonnullarg(2);
  o_01 = luaL_nonnullarg(3);
  lua_pushobject(o);
  lua_pushobject(o_00);
  lua_pushobject(o_01);
  lua_rawsettable();
  return;
}

/* ---- 0x10003d10  settagmethod ---- */
/* Original name settagmethod (the remaster's libLua.so: int_funcs entry 'settagmethod'); was
   FUN_10003d10. */

void __cdecl settagmethod(void)

{
  int iVar1;
  byte *event;
  longlong lVar2;
  float fVar3;
  
  iVar1 = luaL_nonnullarg(3);
  lua_pushobject(iVar1);
  event = (byte *)luaL_check_string(2);
  fVar3 = luaL_check_number(1);
  lVar2 = FTOL((float10)fVar3);
  iVar1 = lua_settagmethod((int)lVar2,event);
  lua_pushobject(iVar1);
  return;
}

/* ---- 0x10003d50  gettagmethod ---- */
/* Original name gettagmethod (the remaster's libLua.so: int_funcs entry 'gettagmethod'); was
   FUN_10003d50. */

void __cdecl gettagmethod(void)

{
  byte *event;
  int o;
  longlong lVar1;
  float fVar2;
  
  event = (byte *)luaL_check_string(2);
  fVar2 = luaL_check_number(1);
  lVar1 = FTOL((float10)fVar2);
  o = lua_gettagmethod((int)lVar1,event);
  lua_pushobject(o);
  return;
}

/* ---- 0x10003d80  seterrormethod ---- */
/* Original name seterrormethod (the remaster's libLua.so: int_funcs entry 'seterrormethod'); was
   FUN_10003d80. */

void __cdecl seterrormethod(void)

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

void __cdecl luaI_collectgarbage(void)

{
  int iVar1;
  longlong lVar2;
  float fVar3;
  
  fVar3 = luaL_opt_number(1,0.0f);
  lVar2 = FTOL((float10)fVar3);
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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char f_bi_tostring[] __asm__("_bi_tostring");
extern char f_copytagmethods[] __asm__("_copytagmethods");
extern char f_foreach[] __asm__("_foreach");
extern char f_foreachvar[] __asm__("_foreachvar");
extern char f_getglobal[] __asm__("_getglobal");
extern char f_gettagmethod[] __asm__("_gettagmethod");
extern char f_internaldofile[] __asm__("_internaldofile");
extern char f_internaldostring[] __asm__("_internaldostring");
extern char f_luaI_assert[] __asm__("_luaI_assert");
extern char f_luaI_breakhere[] __asm__("_luaI_breakhere");
extern char f_luaI_call[] __asm__("_luaI_call");
extern char f_luaI_collectgarbage[] __asm__("_luaI_collectgarbage");
extern char f_luaI_error[] __asm__("_luaI_error");
extern char f_luaI_findscript[] __asm__("_luaI_findscript");
extern char f_luaI_identifyscript[] __asm__("_luaI_identifyscript");
extern char f_luaI_nextscript[] __asm__("_luaI_nextscript");
extern char f_luaI_print[] __asm__("_luaI_print");
extern char f_luaI_startscript[] __asm__("_luaI_startscript");
extern char f_luaI_stopscript[] __asm__("_luaI_stopscript");
extern char f_luaI_type[] __asm__("_luaI_type");
extern char f_luaT_setfallback[] __asm__("_luaT_setfallback");
extern char f_lua_pausetasks[] __asm__("_lua_pausetasks");
extern char f_lua_unpausetasks[] __asm__("_lua_unpausetasks");
extern char f_luatag[] __asm__("_luatag");
extern char f_newtag[] __asm__("_newtag");
extern char f_next[] __asm__("_next");
extern char f_nextvar[] __asm__("_nextvar");
extern char f_rawgetglobal[] __asm__("_rawgetglobal");
extern char f_rawgettable[] __asm__("_rawgettable");
extern char f_rawsetglobal[] __asm__("_rawsetglobal");
extern char f_rawsettable[] __asm__("_rawsettable");
extern char f_seterrormethod[] __asm__("_seterrormethod");
extern char f_setglobal[] __asm__("_setglobal");
extern char f_settag[] __asm__("_settag");
extern char f_settagmethod[] __asm__("_settagmethod");
extern char f_tonumber[] __asm__("_tonumber");
extern char grim_def_DAT_10026568[] __asm__("_DAT_10026568");
extern char grim_def_DAT_10026570[] __asm__("_DAT_10026570");
extern char grim_def_DAT_10026618[] __asm__("_DAT_10026618");
extern char grim_def_DAT_10026684[] __asm__("_DAT_10026684");
extern void *grim_def_g_pInt_funcs[72] __asm__("_g_pInt_funcs");
extern char grim_def_s_Argument_to_findscript_must_be_a_100267ec[60] __asm__("_s_Argument_to_findscript_must_be_a_100267ec");
extern char grim_def_s_Argument_to_identifyscript_must_b_10026870[52] __asm__("_s_Argument_to_identifyscript_must_b_10026870");
extern char grim_def_s_Argument_to_nextscript_must_be_n_100268e8[56] __asm__("_s_Argument_to_nextscript_must_be_n_100268e8");
extern char grim_def_s_Argument_to_stopscript_must_be_a_1002675c[60] __asm__("_s_Argument_to_stopscript_must_be_a_1002675c");
extern char grim_def_s_Current_task_is_committing_suici_10026734[40] __asm__("_s_Current_task_is_committing_suici_10026734");
extern char grim_def_s_Lua_3_1__alpha__100269a4[16] __asm__("_s_Lua_3_1__alpha__100269a4");
extern char grim_def_s_Too_few_arguments_to_findscript__10026828[72] __asm__("_s_Too_few_arguments_to_findscript__10026828");
extern char grim_def_s_Too_few_arguments_to_identifyscr_100268a4[68] __asm__("_s_Too_few_arguments_to_identifyscr_100268a4");
extern char grim_def_s_Too_few_arguments_to_nextscript__10026920[64] __asm__("_s_Too_few_arguments_to_nextscript__10026920");
extern char grim_def_s_Too_few_arguments_to_stopscript__10026798[84] __asm__("_s_Too_few_arguments_to_stopscript__10026798");
extern char grim_def_s__VERSION_10026998[12] __asm__("_s__VERSION_10026998");
extern char grim_def_s__s_10026960[4] __asm__("_s__s_10026960");
extern char grim_def_s_assert_1002668c[] __asm__("_s_assert_1002668c");
extern char grim_def_s_assertion_failed____100s_10026978[28] __asm__("_s_assertion_failed____100s_10026978");
extern char grim_def_s_base_out_of_range_10026964[20] __asm__("_s_base_out_of_range_10026964");
extern char grim_def_s_break_here_100264f8[] __asm__("_s_break_here_100264f8");
extern char grim_def_s_collectgarbage_10026674[] __asm__("_s_collectgarbage_10026674");
extern char grim_def_s_copytagmethods_1002665c[] __asm__("_s_copytagmethods_1002665c");
extern char grim_def_s_dofile_1002666c[] __asm__("_s_dofile_1002666c");
extern char grim_def_s_dostring_10026650[] __asm__("_s_dostring_10026650");
extern char grim_def_s_error_10026648[] __asm__("_s_error_10026648");
extern char grim_def_s_find_script_10026504[] __asm__("_s_find_script_10026504");
extern char grim_def_s_foreach_10026640[] __asm__("_s_foreach_10026640");
extern char grim_def_s_foreachvar_10026634[] __asm__("_s_foreachvar_10026634");
extern char grim_def_s_function___p_10026718[16] __asm__("_s_function___p_10026718");
extern char grim_def_s_getglobal_10026628[] __asm__("_s_getglobal_10026628");
extern char grim_def_s_gettagmethod_10026594[] __asm__("_s_gettagmethod_10026594");
extern char grim_def_s_identify_script_10026530[] __asm__("_s_identify_script_10026530");
extern char grim_def_s_internal_error_100266e8[16] __asm__("_s_internal_error_100266e8");
extern char grim_def_s_invalid_2nd_argument__probably_o_100266b8[48] __asm__("_s_invalid_2nd_argument__probably_o_100266b8");
extern char grim_def_s_newtag_10026620[] __asm__("_s_newtag_10026620");
extern char grim_def_s_next_script_10026540[] __asm__("_s_next_script_10026540");
extern char grim_def_s_nextvar_10026610[] __asm__("_s_nextvar_10026610");
extern char grim_def_s_nil_100266f8[4] __asm__("_s_nil_100266f8");
extern char grim_def_s_pause_scripts_10026520[] __asm__("_s_pause_scripts_10026520");
extern char grim_def_s_print_10026608[] __asm__("_s_print_10026608");
extern char grim_def_s_rawgetglobal_100265f8[] __asm__("_s_rawgetglobal_100265f8");
extern char grim_def_s_rawgettable_100265ec[] __asm__("_s_rawgettable_100265ec");
extern char grim_def_s_rawsetglobal_100265dc[] __asm__("_s_rawsetglobal_100265dc");
extern char grim_def_s_rawsettable_100265d0[] __asm__("_s_rawsettable_100265d0");
extern char grim_def_s_seterrormethod_100265c0[] __asm__("_s_seterrormethod_100265c0");
extern char grim_def_s_setfallback_10026694[] __asm__("_s_setfallback_10026694");
extern char grim_def_s_setglobal_100265b4[] __asm__("_s_setglobal_100265b4");
extern char grim_def_s_settag_1002658c[] __asm__("_s_settag_1002658c");
extern char grim_def_s_settagmethod_100265a4[] __asm__("_s_settagmethod_100265a4");
extern char grim_def_s_start_script_10026558[] __asm__("_s_start_script_10026558");
extern char grim_def_s_stop_script_1002654c[] __asm__("_s_stop_script_1002654c");
extern char grim_def_s_table___p_10026728[12] __asm__("_s_table___p_10026728");
extern char grim_def_s_task___d_100266fc[12] __asm__("_s_task___d_100266fc");
extern char grim_def_s_tonumber_10026580[] __asm__("_s_tonumber_10026580");
extern char grim_def_s_tostring_10026574[] __asm__("_s_tostring_10026574");
extern char grim_def_s_unpause_scripts_10026510[] __asm__("_s_unpause_scripts_10026510");
extern char grim_def_s_userdata___p_10026708[16] __asm__("_s_userdata___p_10026708");
extern char grim_def_s_variable_name_expected_100266a0[24] __asm__("_s_variable_name_expected_100266a0");
static unsigned char grim_anchor_100263d8[0] __attribute__((section(".data$grim_100263d8"), aligned(16), used));
static unsigned char grim_pad_100263d8[8] __attribute__((section(".data$grim_100263d8_"), aligned(4), used));
/* 0x100263d8, 288 bytes */ GRIM_DATA("100263d8z") void *grim_def_g_pInt_funcs[72] __asm__("_g_pInt_funcs") = {
    (void *)&grim_def_s_setfallback_10026694, (void *)f_luaT_setfallback, (void *)&grim_def_s_assert_1002668c, (void *)f_luaI_assert,
    (void *)&grim_def_DAT_10026684, (void *)f_luaI_call, (void *)&grim_def_s_collectgarbage_10026674, (void *)f_luaI_collectgarbage,
    (void *)&grim_def_s_dofile_1002666c, (void *)f_internaldofile, (void *)&grim_def_s_copytagmethods_1002665c, (void *)f_copytagmethods,
    (void *)&grim_def_s_dostring_10026650, (void *)f_internaldostring, (void *)&grim_def_s_error_10026648, (void *)f_luaI_error,
    (void *)&grim_def_s_foreach_10026640, (void *)f_foreach, (void *)&grim_def_s_foreachvar_10026634, (void *)f_foreachvar,
    (void *)&grim_def_s_getglobal_10026628, (void *)f_getglobal, (void *)&grim_def_s_newtag_10026620, (void *)f_newtag,
    (void *)&grim_def_DAT_10026618, (void *)f_next, (void *)&grim_def_s_nextvar_10026610, (void *)f_nextvar,
    (void *)&grim_def_s_print_10026608, (void *)f_luaI_print, (void *)&grim_def_s_rawgetglobal_100265f8, (void *)f_rawgetglobal,
    (void *)&grim_def_s_rawgettable_100265ec, (void *)f_rawgettable, (void *)&grim_def_s_rawsetglobal_100265dc, (void *)f_rawsetglobal,
    (void *)&grim_def_s_rawsettable_100265d0, (void *)f_rawsettable, (void *)&grim_def_s_seterrormethod_100265c0, (void *)f_seterrormethod,
    (void *)&grim_def_s_setglobal_100265b4, (void *)f_setglobal, (void *)&grim_def_s_settagmethod_100265a4, (void *)f_settagmethod,
    (void *)&grim_def_s_gettagmethod_10026594, (void *)f_gettagmethod, (void *)&grim_def_s_settag_1002658c, (void *)f_settag,
    (void *)&grim_def_s_tonumber_10026580, (void *)f_tonumber, (void *)&grim_def_s_tostring_10026574, (void *)f_bi_tostring,
    (void *)&grim_def_DAT_10026570, (void *)f_luatag, (void *)&grim_def_DAT_10026568, (void *)f_luaI_type,
    (void *)&grim_def_s_start_script_10026558, (void *)f_luaI_startscript, (void *)&grim_def_s_stop_script_1002654c, (void *)f_luaI_stopscript,
    (void *)&grim_def_s_next_script_10026540, (void *)f_luaI_nextscript, (void *)&grim_def_s_identify_script_10026530, (void *)f_luaI_identifyscript,
    (void *)&grim_def_s_pause_scripts_10026520, (void *)f_lua_pausetasks, (void *)&grim_def_s_unpause_scripts_10026510, (void *)f_lua_unpausetasks,
    (void *)&grim_def_s_find_script_10026504, (void *)f_luaI_findscript, (void *)&grim_def_s_break_here_100264f8, (void *)f_luaI_breakhere
};
/* 0x100266a0, 24 bytes */ /* loose */ char grim_def_s_variable_name_expected_100266a0[24] __asm__("_s_variable_name_expected_100266a0") = "variable name expected";
/* 0x100266b8, 48 bytes */ /* loose */ char grim_def_s_invalid_2nd_argument__probably_o_100266b8[48] __asm__("_s_invalid_2nd_argument__probably_o_100266b8") = "invalid 2nd argument (probably obsolete code)";
/* 0x100266e8, 16 bytes */ /* loose */ char grim_def_s_internal_error_100266e8[16] __asm__("_s_internal_error_100266e8") = "internal error";
/* 0x100266f8, 4 bytes */ /* loose */ char grim_def_s_nil_100266f8[4] __asm__("_s_nil_100266f8") = "nil";
/* 0x100266fc, 12 bytes */ /* loose */ char grim_def_s_task___d_100266fc[12] __asm__("_s_task___d_100266fc") = "task: %d";
/* 0x10026708, 16 bytes */ /* loose */ char grim_def_s_userdata___p_10026708[16] __asm__("_s_userdata___p_10026708") = "userdata: %p";
/* 0x10026718, 16 bytes */ /* loose */ char grim_def_s_function___p_10026718[16] __asm__("_s_function___p_10026718") = "function: %p";
/* 0x10026728, 12 bytes */ /* loose */ char grim_def_s_table___p_10026728[12] __asm__("_s_table___p_10026728") = "table: %p";
/* 0x10026734, 40 bytes */ /* loose */ char grim_def_s_Current_task_is_committing_suici_10026734[40] __asm__("_s_Current_task_is_committing_suici_10026734") = "Current task is committing suicide!\n";
/* 0x1002675c, 60 bytes */ /* loose */ char grim_def_s_Argument_to_stopscript_must_be_a_1002675c[60] __asm__("_s_Argument_to_stopscript_must_be_a_1002675c") = "Argument to stopscript must be a task handle or function!";
/* 0x10026798, 84 bytes */ /* loose */ char grim_def_s_Too_few_arguments_to_stopscript__10026798[84] __asm__("_s_Too_few_arguments_to_stopscript__10026798") = "Too few arguments to stopscript! Specify the name of a function or a task handle.";
/* 0x100267ec, 60 bytes */ /* loose */ char grim_def_s_Argument_to_findscript_must_be_a_100267ec[60] __asm__("_s_Argument_to_findscript_must_be_a_100267ec") = "Argument to findscript must be a function or task handle!";
/* 0x10026828, 72 bytes */ /* loose */ char grim_def_s_Too_few_arguments_to_findscript__10026828[72] __asm__("_s_Too_few_arguments_to_findscript__10026828") = "Too few arguments to findscript! Specify a function or a task handle.";
/* 0x10026870, 52 bytes */ /* loose */ char grim_def_s_Argument_to_identifyscript_must_b_10026870[52] __asm__("_s_Argument_to_identifyscript_must_b_10026870") = "Argument to identifyscript must be a task handle!";
/* 0x100268a4, 68 bytes */ /* loose */ char grim_def_s_Too_few_arguments_to_identifyscr_100268a4[68] __asm__("_s_Too_few_arguments_to_identifyscr_100268a4") = "Too few arguments to identifyscript! Specify nil or a task handle.";
/* 0x100268e8, 56 bytes */ /* loose */ char grim_def_s_Argument_to_nextscript_must_be_n_100268e8[56] __asm__("_s_Argument_to_nextscript_must_be_n_100268e8") = "Argument to nextscript must be nil or a task handle!";
/* 0x10026920, 64 bytes */ /* loose */ char grim_def_s_Too_few_arguments_to_nextscript__10026920[64] __asm__("_s_Too_few_arguments_to_nextscript__10026920") = "Too few arguments to nextscript! Specify nil or a task handle.";
/* 0x10026960, 4 bytes */ /* loose */ char grim_def_s__s_10026960[4] __asm__("_s__s_10026960") = "%s\t";
/* 0x10026964, 20 bytes */ /* loose */ char grim_def_s_base_out_of_range_10026964[20] __asm__("_s_base_out_of_range_10026964") = "base out of range";
/* 0x10026978, 28 bytes */ /* loose */ char grim_def_s_assertion_failed____100s_10026978[28] __asm__("_s_assertion_failed____100s_10026978") = "assertion failed!  %.100s";
/* 0x10026998, 12 bytes */ /* loose */ char grim_def_s__VERSION_10026998[12] __asm__("_s__VERSION_10026998") = "_VERSION";
/* 0x100269a4, 16 bytes */ /* loose */ char grim_def_s_Lua_3_1__alpha__100269a4[16] __asm__("_s_Lua_3_1__alpha__100269a4") = "Lua 3.1 (alpha)";
