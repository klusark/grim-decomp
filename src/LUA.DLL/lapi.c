/* LUA.DLL :: lapi.c
 * functions 0x10001000 .. 0x1000c950 (92 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10001000  lua_recognizelib ---- */
int * __cdecl lua_recognizelib(int param_1,int param_2)

{
  int *piVar1;
  
                    /* 0x1000  68  lua_recognizelib */
  if ((param_1 == 0) || (param_2 < 1)) {
    (**(code **)(g_dwLuaHS + 0x18))
              (s_aEntries____numEntries___0_100260b8,s_C__grimsrc_libs_lua_src_lapi_cpp_100260d4,
               0x68);
  }
  piVar1 = (int *)(**(code **)(g_dwLuaHS + 0x20))
                            (0xc,s_C__grimsrc_libs_lua_src_lapi_cpp_100260d4,0x6a);
  *piVar1 = param_2;
  piVar1[1] = param_1;
  piVar1[2] = (int)g_dwFirstFuncArray;
  g_dwFirstFuncArray = piVar1;
  return piVar1;
}

/* ---- 0x10001060  lua_openlib ---- */
undefined4 __cdecl lua_openlib(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  
                    /* 0x1060  53  lua_openlib */
  puVar2 = param_1;
  iVar3 = param_2;
  if (((param_1 != (undefined4 *)0x0) && (0 < param_2)) ||
     ((**(code **)(g_dwLuaHS + 0x18))
                (s_aEntries____numEntries___0_100260b8,s_C__grimsrc_libs_lua_src_lapi_cpp_100260d4,
                 0x7f), 0 < param_2)) {
    do {
      lua_pushCclosure(puVar2[1],0);
      lua_setglobal((byte *)*puVar2);
      iVar3 = iVar3 + -1;
      puVar2 = puVar2 + 2;
    } while (iVar3 != 0);
  }
  uVar1 = lua_recognizelib((int)param_1,param_2);
  return uVar1;
}

/* ---- 0x100010d0  lua_FuncPtrToID ---- */
uint __cdecl lua_FuncPtrToID(int param_1)

{
  uint *puVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  uint *puVar5;
  
                    /* 0x10d0  6  lua_FuncPtrToID */
  iVar2 = 0;
  puVar5 = g_dwFirstFuncArray;
  if (g_dwFirstFuncArray == (uint *)0x0) {
    return 0;
  }
  do {
    uVar4 = 0;
    if (*puVar5 != 0) {
      piVar3 = (int *)(puVar5[1] + 4);
      do {
        if (*piVar3 == param_1) {
          return iVar2 << 0x10 | uVar4;
        }
        uVar4 = uVar4 + 1;
        piVar3 = piVar3 + 2;
      } while (uVar4 < *puVar5);
    }
    puVar1 = puVar5 + 2;
    iVar2 = iVar2 + 1;
    puVar5 = (uint *)*puVar1;
  } while ((uint *)*puVar1 != (uint *)0x0);
  return 0;
}

/* ---- 0x10001120  lua_IDToFuncPtr ---- */
undefined4 __cdecl lua_IDToFuncPtr(uint param_1)

{
  uint *puVar1;
  uint uVar2;
  
                    /* 0x1120  7  lua_IDToFuncPtr */
  uVar2 = param_1 >> 0x10;
  for (puVar1 = g_dwFirstFuncArray; puVar1 != (uint *)0x0; puVar1 = (uint *)puVar1[2]) {
    if (uVar2 == 0) goto LAB_10001148;
    uVar2 = uVar2 - 1;
  }
  if (uVar2 == 0) {
LAB_10001148:
    if ((puVar1 != (uint *)0x0) && ((param_1 & 0xffff) < *puVar1)) {
      return *(undefined4 *)(puVar1[1] + 4 + (param_1 & 0xffff) * 8);
    }
  }
  return 0;
}

/* ---- 0x10001160  lua_closelibs ---- */
undefined4 __cdecl lua_closelibs(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = g_dwFirstFuncArray;
  while (iVar2 != 0) {
    iVar1 = *(int *)(iVar2 + 8);
    (**(code **)(g_dwLuaHS + 0x24))(iVar2);
    iVar2 = iVar1;
  }
  return 0;
}

/* ---- 0x10001190  lua_Initialize ---- */
undefined4 __cdecl lua_Initialize(undefined4 param_1,undefined4 *param_2)

{
                    /* 0x1190  8  lua_Initialize */
  g_dwLuaHS = param_1;
  *param_2 = lua_Initialize;
  param_2[1] = Lua_Terminate;
  param_2[2] = Lua_Startup;
  param_2[3] = Lua_Shutdown;
  param_2[4] = lua_Save;
  param_2[5] = lua_Restore;
  param_2[6] = 0;
  param_2[7] = 0;
  g_nLuaInitialize = 1;
  return 0;
}

/* ---- 0x100011e0  luaA_Address ---- */
/* Original name luaA_Address (the remaster's libLua.so: stack + o - 1, used as
   luaA_Address(luaL_nonnullarg(1)) by nextvar / foreach); was lapi__11e0. */

int __cdecl luaA_Address(int param_1)

{
  return (int)(g_pLuaState->pStack + param_1 + -1);
}

/* ---- 0x10001200  luaA_packresults ---- */
/* Unidentified function of lapi.c (Lua 3.1 C API) */

void luaA_packresults(void)

{
  luaV_pack((g_pLuaState->Cstack).nLua2C,(g_pLuaState->Cstack).nNum,g_pLuaState->pTop);
  if (g_pLuaState->pLast <= g_pLuaState->pTop) {
    luaD_checkstack(1);
  }
  g_pLuaState->pTop = g_pLuaState->pTop + 1;
  return;
}

/* ---- 0x10001240  luaA_passresults ---- */
/* Original name luaA_passresults (the remaster's libLua.so: same body (luaD_checkstack(Cnresults),
   copies the C results); callers internaldofile / internaldostring); was lapi__1240. */

int luaA_passresults(void)

{
  int iVar1;
  TObject *pTVar2;
  TObject *pTVar3;
  
  luaD_checkstack((g_pLuaState->Cstack).nNum);
  pTVar2 = g_pLuaState->pStack + (g_pLuaState->Cstack).nLua2C;
  pTVar3 = g_pLuaState->pTop;
  for (iVar1 = ((g_pLuaState->Cstack).nNum & 0x1fffffffU) << 1; iVar1 != 0; iVar1 = iVar1 + -1) {
    pTVar3->nTtype = pTVar2->nTtype;
    pTVar2 = (TObject *)&pTVar2->dwValue;
    pTVar3 = (TObject *)&pTVar3->dwValue;
  }
  for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(char *)&pTVar3->nTtype = (char)pTVar2->nTtype;
    pTVar2 = (TObject *)((int)&pTVar2->nTtype + 1);
    pTVar3 = (TObject *)((int)&pTVar3->nTtype + 1);
  }
  g_pLuaState->pTop = g_pLuaState->pTop + (g_pLuaState->Cstack).nNum;
  return (g_pLuaState->Cstack).nNum;
}

/* ---- 0x100012a0  lua_pop ---- */
undefined4 lua_pop(void)

{
  undefined4 uVar1;
  
                    /* 0x12a0  55  lua_pop */
  ((code *)checkCparams)(1);
  uVar1 = put_luaObjectonTop();
  return uVar1;
}

/* ---- 0x100012b0  checkCparams ---- */
/* Named checkCparams (not in the remaster, gcc inlined it there): Lua 3.1 source name (lapi.c
   static checkCparams: error "API error - wrong number of arguments in C2lua stack" when top -
   stack < Cstack.num + nParams); was luaA_checkCparams. */

void __cdecl checkCparams(int param_1)

{
  if ((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3 < (g_pLuaState->Cstack).nBase + param_1
     ) {
    lua_error((byte *)s_API_error___wrong_number_of_argu_100260f8);
  }
  return;
}

/* ---- 0x100012e0  put_luaObjectonTop ---- */
/* Named put_luaObjectonTop (not in the remaster, gcc inlined it there): Lua 3.1 source name
   (lapi.c: luaD_openstack, moves the top value to the C stack slot); was lapi__12e0. */

int put_luaObjectonTop(void)

{
  TObject *pTVar1;
  int iVar2;
  TObject *pTVar3;
  
  luaD_openstack(((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3) -
                 (g_pLuaState->Cstack).nBase);
  g_pLuaState->pTop = g_pLuaState->pTop + -1;
  pTVar1 = g_pLuaState->pTop;
  iVar2 = (g_pLuaState->Cstack).nBase;
  pTVar3 = g_pLuaState->pStack;
  pTVar3[iVar2].nTtype = pTVar1->nTtype;
  pTVar3[iVar2].dwValue = pTVar1->dwValue;
  (g_pLuaState->Cstack).nBase = (g_pLuaState->Cstack).nBase + 1;
  return (g_pLuaState->Cstack).nBase;
}

/* ---- 0x10001340  lua_lua2C ---- */
int __cdecl lua_lua2C(int param_1)

{
                    /* 0x1340  49  lua_lua2C */
  if ((0 < param_1) && (param_1 <= (g_pLuaState->Cstack).nNum)) {
    return (g_pLuaState->Cstack).nLua2C + param_1;
  }
  return 0;
}

/* ---- 0x10001360  lua_callfunction ---- */
undefined4 __cdecl lua_callfunction(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x1360  13  lua_callfunction */
  if (param_1 == 0) {
    return 1;
  }
  luaD_openstack(((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3) -
                 (g_pLuaState->Cstack).nBase);
  set_normalized(g_pLuaState->pStack + (g_pLuaState->Cstack).nBase,
                 g_pLuaState->pStack + param_1 + -1);
  uVar1 = luaD_protectedrun((void *)0xff);
  return uVar1;
}

/* ---- 0x100013c0  set_normalized ---- */
/* Named set_normalized (not in the remaster, gcc inlined it there): Lua 3.1 source name (lapi.c
   static set_normalized: copies the value, the tag through normalized_type); was
   luaA_setnormalized. */

void __cdecl set_normalized(TObject *d,TObject *s)

{
  int iVar1;
  
  d->dwValue = s->dwValue;
  iVar1 = normalized_type(s);
  d->nTtype = iVar1;
  return;
}

/* ---- 0x100013e0  normalized_type ---- */
/* Maps closure/mark tags back to the user-visible type Named normalized_type (not in the remaster,
   gcc inlined it there): Lua 3.1 source name (lapi.c static normalized_type: CMARK -> CPROTO, PMARK
   -> PROTO, CLMARK -> CLOSURE); was luaA_normalizedtype. */

int __cdecl normalized_type(TObject *o)

{
  int iVar1;
  
  iVar1 = o->nTtype;
  if (iVar1 == -0xb) {
    iVar1 = -5;
  }
  else {
    if (iVar1 == -10) {
      return -4;
    }
    if (iVar1 == -9) {
      return -8;
    }
  }
  return iVar1;
}

/* ---- 0x10001410  lua_gettagmethod ---- */
int __cdecl lua_gettagmethod(int param_1,byte *param_2)

{
  TObject *o;
  int iVar1;
  
                    /* 0x1410  36  lua_gettagmethod */
  o = (TObject *)luaT_gettagmethod(param_1,param_2);
  iVar1 = put_luaObject(o);
  return iVar1;
}

/* ---- 0x10001430  put_luaObject ---- */
/* Named put_luaObject (not in the remaster, gcc inlined it there): Lua 3.1 source name (lapi.c:
   luaD_openstack, stores *o in the next C stack slot); was lapi__1430. */

int __cdecl put_luaObject(TObject *o)

{
  int iVar1;
  TObject *pTVar2;
  
  luaD_openstack(((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3) -
                 (g_pLuaState->Cstack).nBase);
  iVar1 = (g_pLuaState->Cstack).nBase;
  pTVar2 = g_pLuaState->pStack;
  pTVar2[iVar1].nTtype = o->nTtype;
  pTVar2[iVar1].dwValue = o->dwValue;
  (g_pLuaState->Cstack).nBase = (g_pLuaState->Cstack).nBase + 1;
  return (g_pLuaState->Cstack).nBase;
}

/* ---- 0x10001490  lua_settagmethod ---- */
undefined4 __cdecl lua_settagmethod(int param_1,byte *param_2)

{
  undefined4 uVar1;
  
                    /* 0x1490  78  lua_settagmethod */
  ((code *)checkCparams)(1);
  luaT_settagmethod(param_1,param_2,&g_pLuaState->pTop[-1].nTtype);
  uVar1 = put_luaObjectonTop();
  return uVar1;
}

/* ---- 0x100014c0  lua_seterrormethod ---- */
int __cdecl lua_seterrormethod(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(TObject *)(_frame + (0x20 - 0x8)))
  
                    /* 0x14c0  72  lua_seterrormethod */
  local_8.nTtype = g_dwLState_errorim;
  local_8.dwValue = DAT_1002bf5c;
  checkCparams(1);
  g_pLuaState->pTop = g_pLuaState->pTop + -1;
  g_dwLState_errorim = g_pLuaState->pTop->nTtype;
  DAT_1002bf5c = g_pLuaState->pTop->dwValue;
  iVar1 = put_luaObject(&local_8);
  return iVar1;
}
#undef local_8


/* ---- 0x10001520  lua_gettable ---- */
undefined4 __cdecl lua_gettable(void)

{
  undefined4 uVar1;
  
                    /* 0x1520  35  lua_gettable */
  ((code *)checkCparams)(2);
  luaV_gettable();
  uVar1 = put_luaObjectonTop();
  return uVar1;
}

/* ---- 0x10001540  lua_rawgettable ---- */
undefined4 lua_rawgettable(void)

{
  TObject *pTVar1;
  TObject *pTVar2;
  undefined4 uVar3;
  
                    /* 0x1540  65  lua_rawgettable */
  ((code *)checkCparams)(2);
  pTVar1 = g_pLuaState->pTop;
  if (pTVar1[-2].nTtype == -3) {
    pTVar2 = luaH_get((Hash *)pTVar1[-2].dwValue,pTVar1 + -1);
    g_pLuaState->pTop = g_pLuaState->pTop + -1;
    pTVar1 = g_pLuaState->pTop;
    if (pTVar2 == (TObject *)0x0) {
      pTVar1[-1].nTtype = -7;
    }
    else {
      pTVar1[-1].nTtype = pTVar2->nTtype;
      pTVar1[-1].dwValue = pTVar2->dwValue;
    }
  }
  else {
    lua_error((byte *)s_indexed_expression_not_a_table_i_10026130);
  }
  uVar3 = put_luaObjectonTop();
  return uVar3;
}

/* ---- 0x100015b0  lua_settable ---- */
undefined4 __cdecl lua_settable(void)

{
  undefined4 extraout_EAX;
  
                    /* 0x15b0  76  lua_settable */
  ((code *)checkCparams)(3);
  luaV_settable(g_pLuaState->pTop + -3,1);
  return extraout_EAX;
}

/* ---- 0x100015e0  lua_rawsettable ---- */
undefined4 __cdecl lua_rawsettable(void)

{
  undefined4 extraout_EAX;
  
                    /* 0x15e0  67  lua_rawsettable */
  ((code *)checkCparams)(3);
  luaV_settable(g_pLuaState->pTop + -3,0);
  return extraout_EAX;
}

/* ---- 0x10001610  lua_createtable ---- */
int __cdecl lua_createtable(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(TObject *)(_frame + (0x20 - 0x8)))
  
                    /* 0x1610  19  lua_createtable */
  ((code *)luaC_checkGC)();
  local_8.dwValue = (uint)luaH_new(0);
  local_8.nTtype = -3;
  iVar1 = put_luaObject(&local_8);
  return iVar1;
}
#undef local_8


/* ---- 0x10001640  lua_getglobal ---- */
undefined4 __cdecl lua_getglobal(byte *param_1)

{
  TaggedString *ts;
  undefined4 uVar1;
  
                    /* 0x1640  29  lua_getglobal */
  ((code *)luaD_checkstack)(2);
  ts = luaS_new((char *)param_1);
  luaV_getglobal(ts);
  uVar1 = put_luaObjectonTop();
  return uVar1;
}

/* ---- 0x10001670  lua_rawgetglobal ---- */
int __cdecl lua_rawgetglobal(byte *param_1)

{
  TaggedString *pTVar1;
  int iVar2;
  
                    /* 0x1670  64  lua_rawgetglobal */
  pTVar1 = luaS_new((char *)param_1);
  iVar2 = put_luaObject(&pTVar1->globalval);
  return iVar2;
}

/* ---- 0x10001690  lua_setglobal ---- */
undefined4 __cdecl lua_setglobal(byte *param_1)

{
  TaggedString *ts;
  undefined4 extraout_EAX;
  
                    /* 0x1690  74  lua_setglobal */
  ((code *)checkCparams)(1);
  luaD_checkstack(2);
  ts = luaS_new((char *)param_1);
  luaV_setglobal(ts);
  return extraout_EAX;
}

/* ---- 0x100016c0  lua_rawsetglobal ---- */
undefined4 __cdecl lua_rawsetglobal(byte *param_1)

{
  TaggedString *ts;
  undefined4 extraout_EAX;
  
                    /* 0x16c0  66  lua_rawsetglobal */
  ts = luaS_new((char *)param_1);
  checkCparams(1);
  g_pLuaState->pTop = g_pLuaState->pTop + -1;
  luaS_rawsetglobal(ts,g_pLuaState->pTop);
  return extraout_EAX;
}

/* ---- 0x10001700  lua_isnil ---- */
undefined4 __cdecl lua_isnil(int param_1)

{
                    /* 0x1700  42  lua_isnil */
  if ((param_1 != 0) && (g_pLuaState->pStack[param_1 + -1].nTtype != -7)) {
    return 0;
  }
  return 1;
}

/* ---- 0x10001730  lua_istable ---- */
undefined4 __cdecl lua_istable(int param_1)

{
                    /* 0x1730  45  lua_istable */
  if ((param_1 != 0) && (g_pLuaState->pStack[param_1 + -1].nTtype == -3)) {
    return 1;
  }
  return 0;
}

/* ---- 0x10001760  lua_isuserdata ---- */
undefined4 __cdecl lua_isuserdata(int param_1)

{
                    /* 0x1760  47  lua_isuserdata */
  if ((param_1 != 0) && (g_pLuaState->pStack[param_1 + -1].nTtype == 0)) {
    return 1;
  }
  return 0;
}

/* ---- 0x10001790  lua_iscfunction ---- */
int __cdecl lua_iscfunction(int param_1)

{
  int iVar1;
  
                    /* 0x1790  40  lua_iscfunction */
  iVar1 = lua_tag(param_1);
  return iVar1 == -5;
}

/* ---- 0x100017b0  lua_isnumber ---- */
undefined4 __cdecl lua_isnumber(int param_1)

{
  int iVar1;
  
                    /* 0x17b0  43  lua_isnumber */
  if (param_1 == 0) {
    return 0;
  }
  if ((g_pLuaState->pStack[param_1 + -1].nTtype != -1) &&
     (iVar1 = luaV_tonumber(&g_pLuaState->pStack[param_1 + -1].nTtype), iVar1 != 0)) {
    return 0;
  }
  return 1;
}

/* ---- 0x100017f0  lua_isstring ---- */
undefined4 __cdecl lua_isstring(int param_1)

{
  int iVar1;
  
                    /* 0x17f0  44  lua_isstring */
  iVar1 = lua_tag(param_1);
  if ((iVar1 != -2) && (iVar1 != -1)) {
    return 0;
  }
  return 1;
}

/* ---- 0x10001810  lua_isfunction ---- */
undefined4 __cdecl lua_isfunction(int param_1)

{
  int iVar1;
  
                    /* 0x1810  41  lua_isfunction */
  iVar1 = lua_tag(param_1);
  if ((iVar1 != -4) && (iVar1 != -5)) {
    return 0;
  }
  return 1;
}

/* ---- 0x10001830  lua_istask ---- */
undefined4 __cdecl lua_istask(int param_1)

{
                    /* 0x1830  46  lua_istask */
  lua_tag(param_1);
  if ((param_1 != 0) && (g_pLuaState->pStack[param_1 + -1].nTtype == -6)) {
    return 1;
  }
  return 0;
}

/* ---- 0x10001860  lua_getnumber ---- */
float __cdecl lua_getnumber(int param_1)

{
  int iVar1;
  
                    /* 0x1860  31  lua_getnumber */
  if (param_1 == 0) {
    return 0.0;
  }
  if (g_pLuaState->pStack[param_1 + -1].nTtype != -1) {
    iVar1 = luaV_tonumber(&g_pLuaState->pStack[param_1 + -1].nTtype);
    if (iVar1 != 0) {
      return 0.0;
    }
  }
  return PUN(float,g_pLuaState->pStack[param_1 + -1].dwValue);
}

/* ---- 0x100018c0  lua_getstring ---- */
int __cdecl lua_getstring(int param_1)

{
  int iVar1;
  
                    /* 0x18c0  34  lua_getstring */
  if (param_1 == 0) {
    return 0;
  }
  if ((g_pLuaState->pStack[param_1 + -1].nTtype != -2) &&
     (iVar1 = luaV_tostring(&g_pLuaState->pStack[param_1 + -1].nTtype), iVar1 != 0)) {
    return 0;
  }
  return g_pLuaState->pStack[param_1 + -1].dwValue + 0x18;
}

/* ---- 0x10001910  lua_getuserdata ---- */
undefined4 __cdecl lua_getuserdata(int param_1)

{
                    /* 0x1910  38  lua_getuserdata */
  if ((param_1 != 0) && (g_pLuaState->pStack[param_1 + -1].nTtype == 0)) {
    return *(undefined4 *)(g_pLuaState->pStack[param_1 + -1].dwValue + 0x14);
  }
  return 0;
}

/* ---- 0x10001940  lua_getcfunction ---- */
int __cdecl lua_getcfunction(int param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  TObject *pTVar2;
  
                    /* 0x1940  28  lua_getcfunction */
  bVar1 = lua_iscfunction(param_1);
  if (((uint)(byte)(bVar1)) == 0) {
    return 0;
  }
  pTVar2 = luaA_protovalue(g_pLuaState->pStack + param_1 + -1);
  return pTVar2->dwValue;
}

/* ---- 0x10001970  luaA_protovalue ---- */
/* Named luaA_protovalue (not in the remaster, gcc inlined it there): Lua 3.1 source name (lapi.c
   luaA_protovalue: a closure (normalized_type) gives its function consts[0], anything else itself;
   used by lua_getcfunction / lua_getlocal); was luaA_normalizeObj. */

TObject * __cdecl luaA_protovalue(TObject *o)

{
  int iVar1;
  
  iVar1 = normalized_type(o);
  if (iVar1 == -8) {
    return (TObject *)(o->dwValue + 0xc);
  }
  return o;
}

/* ---- 0x10001990  lua_gettask ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl lua_gettask(int obj)

{
  longlong lVar1;
  
                    /* 0x1990  37  lua_gettask */
  if ((obj != 0) && (g_pLuaState->pStack[obj + -1].nTtype == -6)) {
    lVar1 = _ftol();
    return (int)lVar1;
  }
  return -1;
}
#endif


/* ---- 0x100019c0  lua_pushtask ---- */
undefined4 __cdecl lua_pushtask(int param_1)

{
  LState *pLVar1;
  
                    /* 0x19c0  62  lua_pushtask */
  g_pLuaState->pTop->nTtype = -6;
  g_pLuaState->pTop->dwValue = PUN(uint,(float)((float)param_1));
  if (g_pLuaState->pLast <= g_pLuaState->pTop) {
    luaD_checkstack(1);
  }
  pLVar1 = g_pLuaState;
  g_pLuaState->pTop = g_pLuaState->pTop + 1;
  return pLVar1;
}

/* ---- 0x10001a10  lua_pushnil ---- */
undefined4 __cdecl lua_pushnil(void)

{
  LState *pLVar1;
  
                    /* 0x1a10  58  lua_pushnil */
  g_pLuaState->pTop->nTtype = -7;
  if (g_pLuaState->pLast <= g_pLuaState->pTop) {
    luaD_checkstack(1);
  }
  pLVar1 = g_pLuaState;
  g_pLuaState->pTop = g_pLuaState->pTop + 1;
  return pLVar1;
}

/* ---- 0x10001a50  lua_pushnumber ---- */
void __cdecl lua_pushnumber(float n)

{
                    /* 0x1a50  59  lua_pushnumber */
  g_pLuaState->pTop->nTtype = -1;
  g_pLuaState->pTop->dwValue = PUN(uint,(float)(n));
  if (g_pLuaState->pLast <= g_pLuaState->pTop) {
    luaD_checkstack(1);
  }
  g_pLuaState->pTop = g_pLuaState->pTop + 1;
  return;
}

/* ---- 0x10001aa0  lua_pushstring ---- */
undefined4 __cdecl lua_pushstring(byte *param_1)

{
  TaggedString *pTVar1;
  undefined4 uVar2;
  
                    /* 0x1aa0  61  lua_pushstring */
  if (param_1 == (byte *)0x0) {
    g_pLuaState->pTop->nTtype = -7;
  }
  else {
    pTVar1 = luaS_new((char *)param_1);
    g_pLuaState->pTop->dwValue = (uint)pTVar1;
    g_pLuaState->pTop->nTtype = -2;
  }
  if (g_pLuaState->pLast <= g_pLuaState->pTop) {
    luaD_checkstack(1);
  }
  g_pLuaState->pTop = g_pLuaState->pTop + 1;
  uVar2 = ((code *)luaC_checkGC)();
  return uVar2;
}

/* ---- 0x10001b10  lua_pushCclosure ---- */
undefined4 __cdecl lua_pushCclosure(int param_1,uint param_2)

{
  undefined4 uVar1;
  
                    /* 0x1b10  57  lua_pushCclosure */
  if (param_1 == 0) {
    lua_error((byte *)s_API_error___attempt_to_push_a_NU_10026160);
  }
  checkCparams(param_2);
  g_pLuaState->pTop->nTtype = -5;
  g_pLuaState->pTop->dwValue = param_1;
  if (g_pLuaState->pLast <= g_pLuaState->pTop) {
    luaD_checkstack(1);
  }
  g_pLuaState->pTop = g_pLuaState->pTop + 1;
  uVar1 = ((code *)luaV_closure)(param_2);
  return uVar1;
}

/* ---- 0x10001b90  lua_pushusertag ---- */
undefined4 __cdecl lua_pushusertag(byte *param_1,uint param_2)

{
  TaggedString *pTVar1;
  undefined4 uVar2;
  
                    /* 0x1b90  63  lua_pushusertag */
  if (((int)param_2 < 0) && (param_2 != 0xffffffff)) {
    luaT_realtag(param_2);
  }
  pTVar1 = luaS_createudata(param_1,param_2);
  g_pLuaState->pTop->dwValue = (uint)pTVar1;
  g_pLuaState->pTop->nTtype = 0;
  if (g_pLuaState->pLast <= g_pLuaState->pTop) {
    luaD_checkstack(1);
  }
  g_pLuaState->pTop = g_pLuaState->pTop + 1;
  uVar2 = ((code *)luaC_checkGC)();
  return uVar2;
}

/* ---- 0x10001c00  luaA_pushobject ---- */
/* Unidentified function of lapi.c (Lua 3.1 C API) */

void __cdecl luaA_pushobject(TObject *o)

{
  TObject *pTVar1;
  
  pTVar1 = g_pLuaState->pTop;
  pTVar1->nTtype = o->nTtype;
  pTVar1->dwValue = o->dwValue;
  if (g_pLuaState->pLast <= g_pLuaState->pTop) {
    luaD_checkstack(1);
  }
  g_pLuaState->pTop = g_pLuaState->pTop + 1;
  return;
}

/* ---- 0x10001c40  lua_pushobject ---- */
undefined4 __cdecl lua_pushobject(int param_1)

{
  LState *pLVar1;
  undefined4 uVar2;
  
                    /* 0x1c40  60  lua_pushobject */
  if (param_1 == 0) {
    uVar2 = lua_error((byte *)s_API_error___attempt_to_push_a_NO_10026190);
    return uVar2;
  }
  set_normalized(g_pLuaState->pTop,g_pLuaState->pStack + param_1 + -1);
  if (g_pLuaState->pLast <= g_pLuaState->pTop) {
    luaD_checkstack(1);
  }
  pLVar1 = g_pLuaState;
  g_pLuaState->pTop = g_pLuaState->pTop + 1;
  return pLVar1;
}

/* ---- 0x10001ca0  lua_tag ---- */
undefined4 __cdecl lua_tag(int param_1)

{
  TObject *pTVar1;
  
                    /* 0x1ca0  81  lua_tag */
  if (param_1 == 0) {
    return 0xfffffff9;
  }
  pTVar1 = g_pLuaState->pStack;
  switch(pTVar1[param_1 + -1].nTtype) {
  case 0:
    return *(undefined4 *)(pTVar1[param_1 + -1].dwValue + 0x10);
  case -0xb:
    return 0xfffffffb;
  case -10:
    return 0xfffffffc;
  case -9:
  case -8:
    return *(undefined4 *)(pTVar1[param_1 + -1].dwValue + 0xc);
  default:
    return pTVar1[param_1 + -1].nTtype;
  case -3:
    return *(undefined4 *)(pTVar1[param_1 + -1].dwValue + 0x14);
  }
}

/* ---- 0x10001d30  lua_settag ---- */
LState * __cdecl lua_settag(int param_1)

{
  TObject *pTVar1;
  int iVar2;
  LState *pLVar3;
  
                    /* 0x1d30  77  lua_settag */
  ((code *)checkCparams)(1);
  luaT_realtag(param_1);
  pTVar1 = g_pLuaState->pTop;
  iVar2 = pTVar1[-1].nTtype;
  if (iVar2 == -3) {
    *(int *)(pTVar1[-1].dwValue + 0x14) = param_1;
    pLVar3 = g_pLuaState;
    g_pLuaState->pTop = g_pLuaState->pTop + -1;
    return pLVar3;
  }
  if (iVar2 != 0) {
    luaL_verror(s_cannot_change_the_tag_of_a___20s_100261b8,(&g_pLuaO_typenames)[-iVar2]);
    pLVar3 = g_pLuaState;
    g_pLuaState->pTop = g_pLuaState->pTop + -1;
    return pLVar3;
  }
  *(int *)(pTVar1[-1].dwValue + 0x10) = param_1;
  pLVar3 = g_pLuaState;
  g_pLuaState->pTop = g_pLuaState->pTop + -1;
  return pLVar3;
}

/* ---- 0x10001db0  lua_pausetasks ---- */
undefined4 __cdecl lua_pausetasks(void)

{
  LState *L;
  
                    /* 0x1db0  54  lua_pausetasks */
  for (L = LState_next(g_dwL_Main); L != (LState *)0x0; L = LState_next(L)) {
    if (L != g_pLuaState) {
      L->nPaused = 1;
    }
  }
  return 0;
}

/* ---- 0x10001de0  lua_unpausetasks ---- */
undefined4 __cdecl lua_unpausetasks(void)

{
  LState *L;
  
                    /* 0x1de0  83  lua_unpausetasks */
  for (L = LState_next(g_dwL_Main); L != (LState *)0x0; L = LState_next(L)) {
    L->nPaused = 0;
  }
  return 0;
}

/* ---- 0x10001e10  lua_updatetasks ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl lua_updatetasks(int param_1)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  LState *pLVar2;
  LState *pLVar3;
  int iVar4;
  uint uVar5;
  undefined4 unaff_ESI;
  LState *pLVar6;
  int unaff_EDI;
  #define local_4c (*(undefined4 (*)[16])(_frame + (0x60 - 0x4c)))
  #define local_c (*(LState **)(_frame + (0x60 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x60 - 0x8)))
  
                    /* 0x1e10  85  lua_updatetasks */
  local_c = g_pLuaState;
LAB_10001e23:
  pLVar3 = LState_next(g_pLuaState);
  pLVar6 = local_c;
  while (local_c = pLVar6, pLVar3 != (LState *)0x0) {
    for (pvVar1 = pLVar3->pExecutionState; pvVar1 != (void *)0x0;
        pvVar1 = *(void **)((int)pvVar1 + 0xc)) {
      ExecutionState_resetcounter((int)pvVar1);
    }
    pLVar3->nUpdated = 0;
    pLVar3 = LState_next(pLVar3);
    pLVar6 = local_c;
  }
  do {
    pLVar3 = LState_next(g_pLuaState);
    while (g_pLuaState = pLVar3, pLVar3 = pLVar6, pLVar2 = pLVar6, g_pLuaState != (LState *)0x0) {
      if ((g_pLuaState->nUpdated == 0) && (g_pLuaState->nPaused == 0)) {
        local_8 = 4;
        g_pLuaState->pErrorJmp = local_4c;
        iVar4 = _setjmp3(local_4c,0,unaff_EDI,unaff_ESI);
        if (iVar4 == 0) {
          if (g_pLuaState->pExecutionState == (void *)0x0) {
            iVar4 = (g_pLuaState->Cstack).nBase;
            luaD_openstack(((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3) - iVar4);
            ((code *)set_normalized)(g_pLuaState->pStack + (g_pLuaState->Cstack).nBase,&g_pLuaState->taskFunc)
            ;
            if (lua_taskhook != 0) {
              luaD_taskHook(g_pLuaState->nTaskId,0);
            }
            uVar5 = luaD_call(iVar4 + 1,0xff);
          }
          else {
            if (lua_taskhook != 0) {
              luaD_taskHook(g_pLuaState->nTaskId,2);
            }
            uVar5 = luaD_call(*(int *)((int)g_pLuaState->pExecutionState + 0x10),
                              *(int *)((int)g_pLuaState->pExecutionState + 0x14));
          }
        }
        else {
          local_8 = 3;
          luaD_deletestates((int)g_pLuaState->pExecutionState);
          uVar5 = 0;
          g_pLuaState->pExecutionState = (void *)0x0;
        }
        if (uVar5 != 0) {
          if (g_pLuaState->pExecutionState == (void *)0x0) {
            (**(code **)(g_dwLuaHS + 0x18))
                      (s_L__pExecutionState_100261dc,s_C__grimsrc_libs_lua_src_lapi_cpp_100260d4,
                       0x2fe);
          }
          if (uVar5 != 0) {
            if (lua_taskhook != 0) {
              luaD_taskHook(g_pLuaState->nTaskId,1);
            }
            g_pLuaState->nUpdated = 1;
            goto LAB_1000201b;
          }
        }
        if (lua_taskhook != 0) {
          luaD_taskHook(g_pLuaState->nTaskId,local_8);
        }
        pLVar3 = LState_next(g_pLuaState);
        pLVar2 = g_pLuaState;
        pLVar6 = local_c;
        if (g_pLuaState != (LState *)0x0) {
          LState_Destruct(g_pLuaState);
          luaM_free(pLVar2);
          pLVar6 = local_c;
        }
      }
      else {
LAB_1000201b:
        pLVar3 = LState_next(g_pLuaState);
        pLVar6 = local_c;
      }
    }
    do {
      g_pLuaState = pLVar2;
      pLVar3 = LState_next(pLVar3);
      if (pLVar3 == (LState *)0x0) {
        if ((param_1 == 0) || (pLVar3 = LState_next(g_pLuaState), pLVar3 == (LState *)0x0)) {
          pLVar3 = LState_next(g_pLuaState);
          return pLVar3 != (LState *)0x0;
        }
        goto LAB_10001e23;
      }
      pLVar2 = g_pLuaState;
    } while ((pLVar3->nUpdated != 0) || (pLVar3->nPaused != 0));
  } while( true );
}
#undef local_4c
#undef local_8
#undef local_c

#endif


/* ---- 0x10002090  lua_stackedfunction ---- */
int __cdecl lua_stackedfunction(int param_1)

{
  int iVar1;
  int iVar2;
  TObject *pTVar3;
  int iVar4;
  
                    /* 0x2090  79  lua_stackedfunction */
  iVar2 = (int)g_pLuaState->pTop + (-8 - (int)g_pLuaState->pStack) >> 3;
  if (iVar2 < 0) {
    return 0;
  }
  pTVar3 = g_pLuaState->pStack + iVar2;
  while ((((iVar1 = pTVar3->nTtype, iVar1 != -9 && (iVar1 != -10)) &&
          (iVar4 = param_1, iVar1 != -0xb)) || (iVar4 = param_1 + -1, param_1 != 0))) {
    iVar2 = iVar2 + -1;
    pTVar3 = pTVar3 + -1;
    param_1 = iVar4;
    if (iVar2 < 0) {
      return 0;
    }
  }
  return (iVar2 * 8 >> 3) + 1;
}

/* ---- 0x100020f0  lua_printstack ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 __cdecl lua_printstack(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
                    /* 0x20f0  56  lua_printstack */
  iVar3 = lua_stackedfunction(1);
  iVar2 = param_1;
  iVar1 = 2;
  do {
    if (iVar3 == 0) {
      return 0;
    }
    lua_funcinfo(iVar3,&param_1,&local_4);
    if (iVar2 != 0) {
      pcVar4 = s_Active_Stack__10026254;
      if (iVar1 != 2) {
        pcVar4 = &DAT_10026250;
      }
      (**(code **)(g_dwLuaHS + 0x54))(iVar2,pcVar4);
    }
    pcVar4 = lua_getobjname(iVar3,&local_8);
    if (*pcVar4 == 'g') {
      if (iVar2 != 0) {
        (**(code **)(g_dwLuaHS + 0x54))(iVar2,s_function__s_10026210,local_8);
      }
    }
    else if (*pcVar4 == 't') {
      if (iVar2 != 0) {
        (**(code **)(g_dwLuaHS + 0x54))(iVar2,s___s__tag_method_1002621c,local_8);
      }
    }
    else {
      if (local_4 == 0) {
        if (iVar2 != 0) {
          (**(code **)(g_dwLuaHS + 0x54))(iVar2,s_main_of__s_10026244,param_1);
          param_1 = 0;
          goto LAB_10002208;
        }
      }
      else if (local_4 < 0) {
        if (iVar2 != 0) {
          (**(code **)(g_dwLuaHS + 0x54))(iVar2,&DAT_10026240,param_1);
          param_1 = 0;
          goto LAB_10002208;
        }
      }
      else if (iVar2 != 0) {
        (**(code **)(g_dwLuaHS + 0x54))(iVar2,s_function___s__d__1002622c,param_1,local_4);
      }
      param_1 = 0;
    }
LAB_10002208:
    iVar3 = lua_currentline(iVar3);
    if ((0 < iVar3) && (iVar2 != 0)) {
      (**(code **)(g_dwLuaHS + 0x54))(iVar2,s_at_line__d_10026204,iVar3);
    }
    if (param_1 == 0) {
LAB_1000224a:
      if (iVar2 != 0) {
        (**(code **)(g_dwLuaHS + 0x54))(iVar2,&DAT_100261f0);
      }
    }
    else if (iVar2 != 0) {
      (**(code **)(g_dwLuaHS + 0x54))(iVar2,s__in_file__s__100261f4,param_1);
      goto LAB_1000224a;
    }
    iVar3 = lua_stackedfunction(iVar1);
    iVar1 = iVar1 + 1;
  } while( true );
}
#undef local_4
#undef local_8

#endif


/* ---- 0x10002280  lua_currentline ---- */
uint __cdecl lua_currentline(int param_1)

{
  TObject *pTVar1;
  
                    /* 0x2280  20  lua_currentline */
  pTVar1 = g_pLuaState->pStack + param_1;
  if ((pTVar1 < g_pLuaState->pTop) && (pTVar1->nTtype == -0xc)) {
    return g_pLuaState->pStack[param_1].dwValue;
  }
  return 0xffffffff;
}

/* ---- 0x100022b0  lua_currenttask ---- */
int lua_currenttask(void)

{
                    /* 0x22b0  21  lua_currenttask */
  return g_pLuaState->nTaskId;
}

/* ---- 0x100022c0  lua_getlocal ---- */
int __cdecl lua_getlocal(int param_1,int param_2,int *param_3)

{
  TObject *pTVar1;
  TProtoFunc *func;
  int iVar2;
  TObject *pTVar3;
  char *pcVar4;
  
                    /* 0x22c0  30  lua_getlocal */
  iVar2 = lua_tag(param_1);
  if (iVar2 == -4) {
    pTVar1 = g_pLuaState->pStack;
    pTVar3 = luaA_protovalue(pTVar1 + param_1 + -1);
    func = (TProtoFunc *)pTVar3->dwValue;
    iVar2 = lua_currentline(param_1);
    pcVar4 = luaF_getlocalname(func,param_2,iVar2);
    *param_3 = (int)pcVar4;
    if (pcVar4 != (char *)0x0) {
      return (((param_2 * 8 + 8) - (int)g_pLuaState->pStack) + (int)(pTVar1 + param_1 + -1) >> 3) +
             1;
    }
  }
  return 0;
}

/* ---- 0x10002330  lua_setlocal ---- */
undefined4 __cdecl lua_setlocal(int param_1,int param_2)

{
  TObject *o;
  TProtoFunc *func;
  int iVar1;
  TObject *pTVar2;
  char *pcVar3;
  
                    /* 0x2330  75  lua_setlocal */
  iVar1 = lua_tag(param_1);
  if (iVar1 == -4) {
    o = g_pLuaState->pStack + param_1 + -1;
    pTVar2 = luaA_protovalue(o);
    func = (TProtoFunc *)pTVar2->dwValue;
    iVar1 = lua_currentline(param_1);
    pcVar3 = luaF_getlocalname(func,param_2,iVar1);
    checkCparams(1);
    g_pLuaState->pTop = g_pLuaState->pTop + -1;
    if (pcVar3 != (char *)0x0) {
      pTVar2 = g_pLuaState->pTop;
      o[param_2 + 1].nTtype = pTVar2->nTtype;
      o[param_2 + 1].dwValue = pTVar2->dwValue;
      return 1;
    }
  }
  return 0;
}

/* ---- 0x100023c0  lua_funcinfo ---- */
undefined4 __cdecl lua_funcinfo(int param_1,int *param_2,undefined4 *param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  TObject *o;
  
                    /* 0x23c0  27  lua_funcinfo */
  iVar2 = lua_isfunction(param_1);
  if (iVar2 == 0) {
    uVar3 = lua_error((byte *)s_API____funcinfo__called_with_a_n_10026268);
    return uVar3;
  }
  o = luaA_protovalue(g_pLuaState->pStack + param_1 + -1);
  iVar2 = normalized_type(o);
  if (iVar2 == -4) {
    *param_2 = *(int *)(o->dwValue + 0x18) + 0x18;
    uVar1 = o->dwValue;
    *param_3 = *(undefined4 *)(uVar1 + 0x14);
    return uVar1;
  }
  *param_2 = (int)&DAT_10026264;
  *param_3 = 0xffffffff;
  return param_2;
}

/* ---- 0x10002440  lua_getobjname ---- */
char * __cdecl lua_getobjname(int param_1,undefined4 *param_2)

{
  char *pcVar1;
  int *piVar2;
  
                    /* 0x2440  32  lua_getobjname */
  ((code *)set_normalized)(g_pLuaState->pTop,g_pLuaState->pStack + param_1 + -1);
  pcVar1 = luaT_travtagmethods(checkfunc);
  *param_2 = pcVar1;
  if (pcVar1 != (char *)0x0) {
    return s_tag_method_100262a4;
  }
  piVar2 = luaS_travsymbol(checkfunc);
  *param_2 = piVar2;
  pcVar1 = s_global_1002629c;
  if (piVar2 == (int *)0x0) {
    pcVar1 = &DAT_1002bedc;
  }
  return pcVar1;
}

/* ---- 0x100024a0  checkfunc ---- */
/* Original name checkfunc (the remaster's libLua.so: static checkfunc(TObject*): luaO_equalObj(o,
   top), called by lua_getobjname); was FUN_100024a0. */

uint __cdecl checkfunc(TObject *o)

{
  uint uVar1;
  
  uVar1 = luaO_equalObj(o,g_pLuaState->pTop);
  return uVar1;
}

/* ---- 0x100024c0  lua_beginblock ---- */
LState * __cdecl lua_beginblock(void)

{
  CLuaStack *pCVar1;
  LState *pLVar2;
  
                    /* 0x24c0  12  lua_beginblock */
  if (9 < g_pLuaState->nNumCblocks) {
    lua_error((byte *)s_too_many_nested_blocks_100262b0);
  }
  pLVar2 = g_pLuaState;
  pCVar1 = g_pLuaState->aCblocks + g_pLuaState->nNumCblocks;
  pCVar1->nBase = (g_pLuaState->Cstack).nBase;
  pCVar1->nLua2C = (pLVar2->Cstack).nLua2C;
  pCVar1->nNum = (pLVar2->Cstack).nNum;
  pLVar2 = g_pLuaState;
  g_pLuaState->nNumCblocks = g_pLuaState->nNumCblocks + 1;
  return pLVar2;
}

/* ---- 0x10002510  lua_endblock ---- */
undefined4 __cdecl lua_endblock(void)

{
  CLuaStack *pCVar1;
  LState *pLVar2;
  undefined4 uVar3;
  
                    /* 0x2510  25  lua_endblock */
  g_pLuaState->nNumCblocks = g_pLuaState->nNumCblocks + -1;
  pLVar2 = g_pLuaState;
  pCVar1 = g_pLuaState->aCblocks + g_pLuaState->nNumCblocks;
  (g_pLuaState->Cstack).nBase = pCVar1->nBase;
  (pLVar2->Cstack).nLua2C = pCVar1->nLua2C;
  (pLVar2->Cstack).nNum = pCVar1->nNum;
  uVar3 = ((code *)luaD_adjusttop)((g_pLuaState->Cstack).nBase);
  return uVar3;
}

/* ---- 0x10002560  lua_ref ---- */
uint __cdecl lua_ref(int param_1)

{
  uint uVar1;
  
                    /* 0x2560  69  lua_ref */
  ((code *)checkCparams)(1);
  uVar1 = luaC_ref(&g_pLuaState->pTop[-1].nTtype,param_1);
  g_pLuaState->pTop = g_pLuaState->pTop + -1;
  return uVar1;
}

/* ---- 0x10002590  lua_getref ---- */
int __cdecl lua_getref(uint param_1)

{
  TObject *o;
  int iVar1;
  
                    /* 0x2590  33  lua_getref */
  o = luaC_getref(param_1);
  if (o != (TObject *)0x0) {
    iVar1 = put_luaObject(o);
    return iVar1;
  }
  return 0;
}

/* ---- 0x100025b0  lua_setfallback ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 __cdecl lua_setfallback(byte *name,int fallback)

{
  undefined4 uVar1;
  int in_stack_0000000c;
  
                    /* 0x25b0  73  lua_setfallback */
  lua_pushstring(name);
  lua_pushCclosure(in_stack_0000000c,0);
  do_unprotectedrun(luaT_setfallback,2,(void *)0x1);
  uVar1 = put_luaObjectonTop();
  return uVar1;
}
#endif


/* ---- 0x100025f0  do_unprotectedrun ---- */
/* Opens stack space and runs luaD_call for the C API Named do_unprotectedrun (not in the remaster,
   gcc inlined it there): Lua 3.1 source name (lapi.c static do_unprotectedrun of the fallback
   compatibility code: luaD_openstack(nParams), a CPROTO in the base slot, luaD_call; its only
   caller is lua_setfallback with luaT_setfallback, 2, 1); was luaA_callObject. */

void __cdecl do_unprotectedrun(uint param_1,int param_2,void *param_3)

{
  int iVar1;
  
  iVar1 = ((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3) - param_2;
  luaD_openstack(param_2);
  g_pLuaState->pStack[iVar1].nTtype = -5;
  g_pLuaState->pStack[iVar1].dwValue = param_1;
  g_pLuaState->nPreventBreak = g_pLuaState->nPreventBreak + 1;
  luaD_call(iVar1 + 1,(int)param_3);
  g_pLuaState->nPreventBreak = g_pLuaState->nPreventBreak + -1;
  return;
}

/* ---- 0x10002660  luaA_ResetSaveCount ---- */
/* Original name luaA_ResetSaveCount (the remaster's libLua.so: clears the saved-bytes counter that
   LuaSaveWriter adds to); was lapi__2660. */

void luaA_ResetSaveCount(void)

{
  g_dwLua_totalBytesSaved = 0;
  return;
}

/* ---- 0x10002670  lua_Save ---- */
undefined4 __cdecl lua_Save(undefined *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined *puVar1;
  LState *pLVar2;
  int iVar3;
  #define local_4 (*(undefined **)(_frame + (0x20 - 0x4)))
  
                    /* 0x2670  10  lua_Save */
  puVar1 = param_1;
  local_4 = (undefined *)0x0;
  g_dwSaveFunc = param_1;
  lua_collectgarbage(0);
  LState_SaveGlobals(((unsigned)(uintptr_t)LuaSaveWriter));
  luaA_ResetSaveCount();
  for (pLVar2 = g_dwL_Main; pLVar2 != (LState *)0x0; pLVar2 = LState_next(pLVar2)) {
    if (pLVar2 == g_pLuaState) {
      param_1 = local_4;
    }
    local_4 = local_4 + 1;
  }
  (*(code *)puVar1)(&local_4,4);
  (*(code *)puVar1)(&param_1,4);
  pLVar2 = g_dwL_Main;
  if (g_dwL_Main == (LState *)0x0) {
    return 0;
  }
  do {
    iVar3 = LState_Save(pLVar2,((unsigned)(uintptr_t)LuaSaveWriter));
    if (iVar3 != 0) {
      return 1;
    }
    luaA_ResetSaveCount();
    pLVar2 = LState_next(pLVar2);
  } while (pLVar2 != (LState *)0x0);
  return 0;
}
#undef local_4


/* ---- 0x10002730  LuaSaveWriter ---- */
/* Original name LuaSaveWriter (the remaster's libLua.so: static LuaSaveWriter(void*, unsigned):
   lua_totalBytesSaved += size, then the save callback); was FUN_10002730. */

uint __cdecl LuaSaveWriter(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  g_dwLua_totalBytesSaved = g_dwLua_totalBytesSaved + param_2;
  uVar1 = (*g_dwSaveFunc)(param_1,param_2);
  return uVar1;
}

/* ---- 0x10002760  lua_Restore ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
uint __cdecl lua_Restore(void *readFunc)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  undefined4 uVar2;
  LState *this;
  int iVar3;
  LState *a1;
  uint uVar4;
  #define iStack_18 (*(int *)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define pLStack_10 (*(LState **)(_frame + (0x30 - 0x10)))
  
                    /* 0x2760  9  lua_Restore */
  lua_close();
  pLStack_10 = luaM_malloc(0xd4);
  if (pLStack_10 == (LState *)0x0) {
    g_pLuaState = (LState *)0x0;
  }
  else {
    g_pLuaState = LState_Construct(pLStack_10);
  }
  g_dwL_Main = g_pLuaState;
  LState_initglobals();
  LState_GlobalBeginRestore((int)readFunc);
  uVar2 = g_dwLState_numThreads;
  (*(code *)readFunc)(&uStack_14,4);
  if (uStack_14 == 0) {
    (**(code **)(g_dwLuaHS + 0x18))
              (s_numTasks___0_100262f4,s_C__grimsrc_libs_lua_src_lapi_cpp_100260d4,0x499);
  }
  (*(code *)readFunc)(&iStack_18,4);
  LState_Restore(g_dwL_Main,(int)readFunc);
  uVar4 = 1;
  a1 = g_dwL_Main;
  if (1 < uStack_14) {
    do {
      pLStack_10 = luaM_malloc(0xd4);
      if (pLStack_10 == (LState *)0x0) {
        this = (LState *)0x0;
      }
      else {
        this = LState_Construct(pLStack_10);
      }
      iVar3 = LState_Restore(this,(int)readFunc);
      if (iVar3 != 0) {
        (**(code **)(g_dwLuaHS + 0x18))
                  (s_pNewState__Restore_restoreFunc____100262c8,
                   s_C__grimsrc_libs_lua_src_lapi_cpp_100260d4,0x4a2);
      }
      LState_attach(this,(int)a1);
      uVar4 = uVar4 + 1;
      a1 = this;
    } while (uVar4 < uStack_14);
  }
  while (bVar1 = iStack_18 != 0, iStack_18 = iStack_18 + -1, bVar1) {
    g_pLuaState = LState_next(g_pLuaState);
  }
  LState_GlobalEndRestore((int)readFunc);
  g_dwLState_numThreads = uVar2;
  return 0;
}
#undef iStack_18
#undef pLStack_10
#undef uStack_14

#endif


/* ---- 0x10002900  Lua_Terminate ---- */
/* Original name Lua_Terminate (the remaster's libLua.so: static Lua_Terminate: service table = 0,
   initialize flag cleared); was FUN_10002900. */

void Lua_Terminate(void)

{
  g_dwLuaHS = 0;
  if (g_nLuaInitialize != 0) {
    g_nLuaInitialize = 0;
  }
  return;
}

/* ---- 0x10002920  Lua_Startup ---- */
/* Original name Lua_Startup (the remaster's libLua.so: static Lua_Startup: returns the old startup
   flag and sets it); was FUN_10002920. */

undefined4 Lua_Startup(void)

{
  if (g_nLuaStartup != 0) {
    return 1;
  }
  g_nLuaStartup = 1;
  return 0;
}

/* ---- 0x10002940  Lua_Shutdown ---- */
/* Original name Lua_Shutdown (the remaster's libLua.so: static Lua_Shutdown: lua_close, frees the
   libraries (lua_closelibs, inlined there), startup flag = 0); was FUN_10002940. */

void Lua_Shutdown(void)

{
  lua_close();
  lua_closelibs();
  g_nLuaStartup = 0;
  return;
}

/* ---- 0x10004650  lua_error ---- */
undefined4 __cdecl lua_error(byte *param_1)

{
  undefined4 extraout_EAX;
  undefined4 uVar1;
  
                    /* 0x4650  26  lua_error */
  if (param_1 != (byte *)0x0) {
    message(param_1);
  }
  if (g_pLuaState->pErrorJmp != (void *)0x0) {
    longjmp((int)g_pLuaState->pErrorJmp);
    return extraout_EAX;
  }
  uVar1 = (**(code **)(g_dwLuaHS + 0x18))
                    (s_lua__Unable_to_recover__10026a68,s_C__grimsrc_libs_lua_src_ldo_cpp_10026a04,
                     0x1bb);
  return uVar1;
}

/* ---- 0x10004890  lua_dofile ---- */
int __cdecl lua_dofile(char *param_1)

{
  unsigned char _frame[0x130] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  undefined **ppuVar3;
  #define local_114 (*(int (*)[69])(_frame + (0x130 - 0x114)))
  
                    /* 0x4890  23  lua_dofile */
  uVar2 = 1;
  if (lua_assume_binary == 0) {
    if (param_1 == (char *)0x0) {
      ppuVar3 = &PTR_DAT_100282d0;
    }
    else {
      ppuVar3 = (undefined **)(**(code **)(g_dwLuaHS + 0x30))(param_1,&DAT_10026a80);
    }
    if (ppuVar3 == (undefined **)0x0) {
      return 2;
    }
    if (param_1 == (char *)0x0) {
      param_1 = s__stdin__10026a84;
    }
    iVar1 = luaFGetc(ppuVar3);
    luaFUngetc(iVar1,ppuVar3);
    uVar2 = (uint)(iVar1 == 0x1b);
    if (uVar2 != 0) {
      (**(code **)(g_dwLuaHS + 0x34))(ppuVar3);
      ppuVar3 = (undefined **)(**(code **)(g_dwLuaHS + 0x30))(param_1,&DAT_10026a8c);
    }
  }
  else {
    if (param_1 == (char *)0x0) {
      ppuVar3 = &PTR_DAT_100282d0;
    }
    else {
      ppuVar3 = (undefined **)(**(code **)(g_dwLuaHS + 0x30))(param_1,&DAT_10026a8c);
    }
    if (ppuVar3 == (undefined **)0x0) {
      return 2;
    }
    if (param_1 == (char *)0x0) {
      param_1 = s__stdin__10026a84;
    }
  }
  luaZ_Fopen(local_114,(int)ppuVar3,param_1);
  iVar1 = do_main(local_114,uVar2);
  if (ppuVar3 != &PTR_DAT_100282d0) {
    (**(code **)(g_dwLuaHS + 0x34))(ppuVar3);
  }
  return iVar1;
}
#undef local_114


/* ---- 0x10004b20  lua_dostring ---- */
int __cdecl lua_dostring(char *param_1)

{
  unsigned char _frame[0x160] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  int iVar2;
  #define local_144 (*(uint (*)[12])(_frame + (0x160 - 0x144)))
  #define local_114 (*(int (*)[69])(_frame + (0x160 - 0x114)))
  
                    /* 0x4b20  24  lua_dostring */
  if (param_1 == (char *)0x0) {
    return 1;
  }
  sprintf((char *)local_144,s__dostring_______20s_10026a90,param_1);
  puVar1 = strchr(local_144,'\n');
  if (puVar1 != (uint *)0x0) {
    *(undefined1 *)puVar1 = 0;
  }
  luaZ_sopen(local_114,param_1,local_144);
  iVar2 = do_main(local_114,0);
  return iVar2;
}
#undef local_114
#undef local_144


/* ---- 0x10004e00  lua_unref ---- */
uint __cdecl lua_unref(uint param_1)

{
  uint uVar1;
  
                    /* 0x4e00  84  lua_unref */
  uVar1 = param_1;
  if ((-1 < (int)param_1) && (param_1 < g_dwLState_refSize)) {
    uVar1 = param_1 * 3;
    *(undefined4 *)(g_dwLState_refArray + 8 + param_1 * 0xc) = 2;
  }
  return uVar1;
}

/* ---- 0x10004ee0  lua_collectgarbage ---- */
int __cdecl lua_collectgarbage(int param_1)

{
  int iVar1;
  TaggedString *l;
  Hash *l_00;
  TProtoFunc *l_01;
  Closure *l_02;
  
                    /* 0x4ee0  17  lua_collectgarbage */
  iVar1 = g_dwLState_nblocks;
  markall();
  invalidaterefs();
  l = (TaggedString *)luaS_collector();
  l_00 = (Hash *)listcollect(&g_dwLState_roottable);
  l_01 = (TProtoFunc *)listcollect(&g_dwLState_rootproto);
  l_02 = (Closure *)listcollect(&g_dwLState_rootcl);
  g_dwLState_GCthreshold = g_dwLState_GCthreshold * 4;
  luaC_hashcallIM(l_00);
  luaC_strcallIM(l);
  luaD_gcIM((TObject *)&g_LuaO_nilobject);
  luaH_free(l_00);
  luaS_free(l);
  luaF_freeproto(l_01);
  luaF_freeclosure(l_02);
  if (param_1 == 0) {
    g_dwLState_GCthreshold = g_dwLState_nblocks * 2;
    return iVar1 - g_dwLState_nblocks;
  }
  g_dwLState_GCthreshold = param_1 + g_dwLState_nblocks;
  return iVar1 - g_dwLState_nblocks;
}

/* ---- 0x10005ae0  lua_iolibopen ---- */
undefined4 __cdecl lua_iolibopen(void)

{
  undefined4 uVar1;
  
                    /* 0x5ae0  39  lua_iolibopen */
  luaL_openlib(&g_pIolib,10);
  lua_recognizelib(((unsigned)(uintptr_t)&g_pIolibtag),5);
  openwithtags();
  lua_pushCclosure(((unsigned)(uintptr_t)errorfb),0);
  uVar1 = lua_seterrormethod();
  return uVar1;
}

/* ---- 0x10005b20  openwithtags ---- */
/* Registers readfrom/writeto/... and the _INPUT/_OUTPUT globals Named openwithtags (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (liolib.c static openwithtags: two newtags,
   each iolibtag function as a closure with both, then setfile of _INPUT, _OUTPUT, _STDIN, _STDOUT,
   _STDERR); was lua_ioregister. */

void openwithtags(void)

{
  uint uVar1;
  int iVar2;
  undefined **ppuVar3;
  
  uVar1 = lua_newtag();
  iVar2 = lua_newtag();
  ppuVar3 = &g_pIolibtag;
  do {
    lua_pushnumber((float)(int)uVar1);
    lua_pushnumber((float)iVar2);
    lua_pushCclosure((int)ppuVar3[1],2);
    lua_setglobal(*ppuVar3);
    ppuVar3 = ppuVar3 + 2;
  } while (ppuVar3 < s_write_10026b78);
  setfile((byte *)&PTR_DAT_100282d0,(byte *)s__INPUT_10026c00,uVar1);
  setfile(&DAT_100282f0,(byte *)s__OUTPUT_10026c58,uVar1);
  setfile((byte *)&PTR_DAT_100282d0,(byte *)s__STDIN_10026d04,uVar1);
  setfile(&DAT_100282f0,(byte *)s__STDOUT_10026cfc,uVar1);
  setfile(&DAT_10028310,(byte *)s__STDERR_10026cf4,uVar1);
  return;
}

/* ---- 0x10007320  lua_mathlibopen ---- */
undefined4 __cdecl lua_mathlibopen(void)

{
  int iVar1;
  undefined4 uVar2;
  byte *pbVar3;
  
                    /* 0x7320  50  lua_mathlibopen */
  luaL_openlib(&g_pMathlib,0x15);
  lua_recognizelib(((unsigned)(uintptr_t)&PTR_s_math_pow_10026fd8),1);
  lua_pushstring(&DAT_10027004);
  lua_setglobal((byte *)s__TRIGMODE_10027074);
  lua_pushCclosure(((unsigned)(uintptr_t)math_pow),0);
  lua_pushnumber(0.0);
  pbVar3 = &DAT_10027070;
  iVar1 = lua_pop();
  iVar1 = lua_tag(iVar1);
  lua_settagmethod(iVar1,pbVar3);
  lua_pushnumber(3.1415927);
  uVar2 = lua_setglobal(&DAT_1002706c);
  return uVar2;
}

/* ---- 0x10008a00  LState_initglobals ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Grim lstate.c: creates the global state (string table, lexer, tag methods) Original name
   LState_initglobals (the remaster's libLua.so: LState::initglobals: luaS_init, luaX_init,
   luaT_init (callers lua_newstate, lua_Restore)); was lua_initstate. */

void LState_initglobals(void)

{
  if (g_dwLState_lstate_class_initialized == 0) {
    g_dwLState_rootproto = 0;
    _DAT_1002bf3c = 0;
    g_dwLState_rootcl = 0;
    _DAT_1002bf24 = 0;
    g_dwLState_rootglobal = 0;
    _DAT_1002bf04 = 0;
    g_dwLState_roottable = 0;
    _DAT_1002bf1c = 0;
    g_dwLState_IMtable = 0;
    g_dwLState_IMtable_size = 0;
    g_dwLState_refArray = 0;
    g_dwLState_refSize = 0;
    g_dwLState_Mbuffsize = 0;
    g_dwLState_Mbuffnext = 0;
    g_dwLState_Mbuffbase = 0;
    g_dwLState_Mbuffer = 0;
    g_dwLState_nblocks = 0;
    g_dwLState_aStringPtrs = 0;
    g_dwLState_aClosurePtrs = 0;
    g_dwLState_aTablePtrs = 0;
    g_dwLState_aProtoPtrs = 0;
    g_dwLState_stringPtrTotal = 0;
    g_dwLState_closurePtrTotal = 0;
    g_dwLState_tablePtrTotal = 0;
    g_dwLState_protoPtrTotal = 0;
    g_dwLState_GCthreshold = 0x96;
    g_dwLState_errorim = 0xfffffffb;
    DAT_1002bf5c = nilFB;
    g_dwL_Main = g_pLuaState;
    luaS_init();
    luaX_init();
    luaT_init();
    g_dwLState_lstate_class_initialized = 1;
  }
  return;
}

/* ---- 0x10008b40  lua_open ---- */
LState * __cdecl lua_open(void)

{
  LState *pLVar1;
  
                    /* 0x8b40  52  lua_open */
  pLVar1 = g_pLuaState;
  if (g_pLuaState == (LState *)0x0) {
    g_pLuaState = (LState *)lua_newstate();
    luaB_predefine();
    pLVar1 = (LState *)lua_recognizelib(((unsigned)(uintptr_t)&PTR_s_stderrorim_100277b8),1);
  }
  return pLVar1;
}

/* ---- 0x10008c30  lua_close ---- */
undefined4 __cdecl lua_close(void)

{
  LState *pLVar1;
  TaggedString *l;
  LState *pLVar2;
  undefined4 uVar3;
  
                    /* 0x8c30  15  lua_close */
  l = (TaggedString *)luaS_collectudata();
  g_dwLState_GCthreshold = 0x7ffffffd;
  luaC_hashcallIM(g_dwLState_roottable);
  luaC_strcallIM(l);
  luaD_gcIM((TObject *)&g_LuaO_nilobject);
  luaH_free(g_dwLState_roottable);
  luaF_freeproto(g_dwLState_rootproto);
  luaF_freeclosure(g_dwLState_rootcl);
  luaS_free(l);
  luaS_freeall();
  (**(code **)(g_dwLuaHS + 0x24))(g_dwLState_IMtable);
  (**(code **)(g_dwLuaHS + 0x24))(g_dwLState_refArray);
  (**(code **)(g_dwLuaHS + 0x24))(g_dwLState_Mbuffer);
  g_dwLState_IMtable = 0;
  g_dwLState_refArray = 0;
  g_dwLState_Mbuffer = 0;
  pLVar1 = g_pLuaState;
  pLVar2 = g_dwL_Main;
  while (g_pLuaState = pLVar2, g_pLuaState != (LState *)0x0) {
    pLVar2 = LState_next(g_pLuaState);
    pLVar1 = g_pLuaState;
    if (g_pLuaState != (LState *)0x0) {
      LState_Destruct(g_pLuaState);
      luaM_free(pLVar1);
      pLVar1 = g_pLuaState;
    }
  }
  g_pLuaState = pLVar1;
  uVar3 = ((code *)ExecutionState_CleanUp)();
  g_pLuaState = (LState *)0x0;
  g_dwL_Main = (LState *)0x0;
  g_dwLState_lstate_class_initialized = 0;
  return uVar3;
}

/* ---- 0x1000a6e0  lua_strlibopen ---- */
uint __cdecl lua_strlibopen(void)

{
  uint uVar1;
  
                    /* 0xa6e0  80  lua_strlibopen */
  uVar1 = luaL_openlib(&g_pStrlib,9);
  return uVar1;
}

/* ---- 0x1000c8d0  lua_newtag ---- */
int lua_newtag(void)

{
                    /* 0xc8d0  51  lua_newtag */
  g_dwLState_last_tag = g_dwLState_last_tag + -1;
  if ((int)g_dwLState_IMtable_size <= -g_dwLState_last_tag) {
    g_dwLState_IMtable_size =
         luaM_growaux(&g_dwLState_IMtable,g_dwLState_IMtable_size,0x90,
                      (byte *)s_not_enough_memory_100269b4,0x7ffffffd);
  }
  init_entry(g_dwLState_last_tag);
  return g_dwLState_last_tag;
}

/* ---- 0x1000c950  lua_copytagmethods ---- */
int __cdecl lua_copytagmethods(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
                    /* 0xc950  18  lua_copytagmethods */
  ((code *)luaT_checktag)(param_1);
  luaT_checktag(param_2);
  iVar3 = 0;
  do {
    iVar2 = validevent(param_1,iVar3);
    if (iVar2 != 0) {
      puVar1 = (undefined4 *)(g_dwLState_IMtable + (iVar3 + param_2 * -0x12) * 8);
      iVar2 = iVar3 + param_1 * -0x12;
      *(undefined4 *)(g_dwLState_IMtable + iVar2 * 8) = *puVar1;
      *(undefined4 *)(g_dwLState_IMtable + 4 + iVar2 * 8) = puVar1[1];
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x12);
  return param_1;
}
