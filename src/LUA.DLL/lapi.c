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
  return g_pLuaState[8] + -8 + param_1 * 8;
}

/* ---- 0x10001200  luaA_packresults ---- */
/* Unidentified function of lapi.c (Lua 3.1 C API) */

void luaA_packresults(void)

{
  luaV_pack(g_pLuaState[0xb],g_pLuaState[0xc],(undefined4 *)g_pLuaState[7]);
  if ((uint)g_pLuaState[9] <= (uint)g_pLuaState[7]) {
    luaD_checkstack(1);
  }
  g_pLuaState[7] = g_pLuaState[7] + 8;
  return;
}

/* ---- 0x10001240  luaA_passresults ---- */
/* Original name luaA_passresults (the remaster's libLua.so: same body (luaD_checkstack(Cnresults),
   copies the C results); callers internaldofile / internaldostring); was lapi__1240. */

int luaA_passresults(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  luaD_checkstack(g_pLuaState[0xc]);
  puVar2 = (undefined4 *)(g_pLuaState[8] + g_pLuaState[0xb] * 8);
  puVar3 = (undefined4 *)g_pLuaState[7];
  for (iVar1 = (g_pLuaState[0xc] & 0x1fffffffU) << 1; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined1 *)puVar3 = *(undefined1 *)puVar2;
    puVar2 = (undefined4 *)((int)puVar2 + 1);
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  g_pLuaState[7] = g_pLuaState[7] + g_pLuaState[0xc] * 8;
  return g_pLuaState[0xc];
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
  if (g_pLuaState[7] - g_pLuaState[8] >> 3 < g_pLuaState[10] + param_1) {
    lua_error((byte *)s_API_error___wrong_number_of_argu_100260f8);
  }
  return;
}

/* ---- 0x100012e0  put_luaObjectonTop ---- */
/* Named put_luaObjectonTop (not in the remaster, gcc inlined it there): Lua 3.1 source name
   (lapi.c: luaD_openstack, moves the top value to the C stack slot); was lapi__12e0. */

int put_luaObjectonTop(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  luaD_openstack((g_pLuaState[7] - g_pLuaState[8] >> 3) - g_pLuaState[10]);
  g_pLuaState[7] = g_pLuaState[7] + -8;
  puVar1 = (undefined4 *)g_pLuaState[7];
  iVar2 = g_pLuaState[10];
  iVar3 = g_pLuaState[8];
  *(undefined4 *)(iVar3 + iVar2 * 8) = *puVar1;
  *(undefined4 *)(iVar3 + 4 + iVar2 * 8) = puVar1[1];
  g_pLuaState[10] = g_pLuaState[10] + 1;
  return g_pLuaState[10];
}

/* ---- 0x10001340  lua_lua2C ---- */
int __cdecl lua_lua2C(int param_1)

{
                    /* 0x1340  49  lua_lua2C */
  if ((0 < param_1) && (param_1 <= g_pLuaState[0xc])) {
    return g_pLuaState[0xb] + param_1;
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
  luaD_openstack((g_pLuaState[7] - g_pLuaState[8] >> 3) - g_pLuaState[10]);
  set_normalized((int *)(g_pLuaState[8] + g_pLuaState[10] * 8),
                 (int *)(g_pLuaState[8] + -8 + param_1 * 8));
  uVar1 = luaD_protectedrun((void *)0xff);
  return uVar1;
}

/* ---- 0x100013c0  set_normalized ---- */
/* Named set_normalized (not in the remaster, gcc inlined it there): Lua 3.1 source name (lapi.c
   static set_normalized: copies the value, the tag through normalized_type); was
   luaA_setnormalized. */

void __cdecl set_normalized(int *param_1,int *param_2)

{
  int iVar1;
  
  param_1[1] = param_2[1];
  iVar1 = normalized_type(param_2);
  *param_1 = iVar1;
  return;
}

/* ---- 0x100013e0  normalized_type ---- */
/* Maps closure/mark tags back to the user-visible type Named normalized_type (not in the remaster,
   gcc inlined it there): Lua 3.1 source name (lapi.c static normalized_type: CMARK -> CPROTO, PMARK
   -> PROTO, CLMARK -> CLOSURE); was luaA_normalizedtype. */

int __cdecl normalized_type(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
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
undefined4 __cdecl lua_gettagmethod(int param_1,byte *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
                    /* 0x1410  36  lua_gettagmethod */
  puVar1 = (undefined4 *)luaT_gettagmethod(param_1,param_2);
  uVar2 = put_luaObject(puVar1);
  return uVar2;
}

/* ---- 0x10001430  put_luaObject ---- */
/* Named put_luaObject (not in the remaster, gcc inlined it there): Lua 3.1 source name (lapi.c:
   luaD_openstack, stores *o in the next C stack slot); was lapi__1430. */

int __cdecl put_luaObject(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  luaD_openstack((g_pLuaState[7] - g_pLuaState[8] >> 3) - g_pLuaState[10]);
  iVar1 = g_pLuaState[10];
  iVar2 = g_pLuaState[8];
  *(undefined4 *)(iVar2 + iVar1 * 8) = *param_1;
  *(undefined4 *)(iVar2 + 4 + iVar1 * 8) = param_1[1];
  g_pLuaState[10] = g_pLuaState[10] + 1;
  return g_pLuaState[10];
}

/* ---- 0x10001490  lua_settagmethod ---- */
undefined4 __cdecl lua_settagmethod(int param_1,byte *param_2)

{
  undefined4 uVar1;
  
                    /* 0x1490  78  lua_settagmethod */
  ((code *)checkCparams)(1);
  luaT_settagmethod(param_1,param_2,(undefined4 *)(g_pLuaState[7] + -8));
  uVar1 = put_luaObjectonTop();
  return uVar1;
}

/* ---- 0x100014c0  lua_seterrormethod ---- */
undefined4 __cdecl lua_seterrormethod(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
                    /* 0x14c0  72  lua_seterrormethod */
  local_8 = g_dwLState_errorim;
  local_4 = DAT_1002bf5c;
  checkCparams(1);
  g_pLuaState[7] = g_pLuaState[7] + -8;
  g_dwLState_errorim = *(undefined4 *)g_pLuaState[7];
  DAT_1002bf5c = ((undefined4 *)g_pLuaState[7])[1];
  uVar1 = put_luaObject(&local_8);
  return uVar1;
}
#undef local_4
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
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
                    /* 0x1540  65  lua_rawgettable */
  ((code *)checkCparams)(2);
  iVar1 = g_pLuaState[7];
  if (*(int *)(iVar1 + -0x10) == -3) {
    piVar2 = luaH_get(*(int *)(iVar1 + -0xc),(int *)(iVar1 + -8));
    g_pLuaState[7] = g_pLuaState[7] + -8;
    iVar1 = g_pLuaState[7];
    if (piVar2 == (int *)0x0) {
      *(undefined4 *)(iVar1 + -8) = 0xfffffff9;
    }
    else {
      *(int *)(iVar1 + -8) = *piVar2;
      *(int *)(iVar1 + -4) = piVar2[1];
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
  undefined4 uVar1;
  
                    /* 0x15b0  76  lua_settable */
  ((code *)checkCparams)(3);
  uVar1 = ((code *)luaV_settable)((uint *)(g_pLuaState[7] + -0x18),1);
  return uVar1;
}

/* ---- 0x100015e0  lua_rawsettable ---- */
undefined4 __cdecl lua_rawsettable(void)

{
  undefined4 uVar1;
  
                    /* 0x15e0  67  lua_rawsettable */
  ((code *)checkCparams)(3);
  uVar1 = ((code *)luaV_settable)((uint *)(g_pLuaState[7] + -0x18),0);
  return uVar1;
}

/* ---- 0x10001610  lua_createtable ---- */
undefined4 __cdecl lua_createtable(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 **)(_frame + (0x20 - 0x4)))
  
                    /* 0x1610  19  lua_createtable */
  ((code *)luaC_checkGC)();
  local_4 = luaH_new(0);
  local_8 = 0xfffffffd;
  uVar1 = put_luaObject(&local_8);
  return uVar1;
}
#undef local_4
#undef local_8


/* ---- 0x10001640  lua_getglobal ---- */
undefined4 __cdecl lua_getglobal(byte *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x1640  29  lua_getglobal */
  ((code *)luaD_checkstack)(2);
  iVar1 = luaS_new(param_1);
  luaV_getglobal(iVar1);
  uVar2 = put_luaObjectonTop();
  return uVar2;
}

/* ---- 0x10001670  lua_rawgetglobal ---- */
undefined4 __cdecl lua_rawgetglobal(byte *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x1670  64  lua_rawgetglobal */
  iVar1 = luaS_new(param_1);
  uVar2 = put_luaObject((undefined4 *)(iVar1 + 0x10));
  return uVar2;
}

/* ---- 0x10001690  lua_setglobal ---- */
undefined4 __cdecl lua_setglobal(byte *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
                    /* 0x1690  74  lua_setglobal */
  ((code *)checkCparams)(1);
  luaD_checkstack(2);
  piVar1 = (int *)luaS_new(param_1);
  uVar2 = ((code *)luaV_setglobal)(piVar1);
  return uVar2;
}

/* ---- 0x100016c0  lua_rawsetglobal ---- */
undefined4 __cdecl lua_rawsetglobal(byte *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
                    /* 0x16c0  66  lua_rawsetglobal */
  piVar1 = (int *)luaS_new(param_1);
  checkCparams(1);
  g_pLuaState[7] = g_pLuaState[7] + -8;
  uVar2 = ((code *)luaS_rawsetglobal)(piVar1,(int *)g_pLuaState[7]);
  return uVar2;
}

/* ---- 0x10001700  lua_isnil ---- */
undefined4 __cdecl lua_isnil(int param_1)

{
                    /* 0x1700  42  lua_isnil */
  if ((param_1 != 0) && (*(int *)(g_pLuaState[8] + -8 + param_1 * 8) != -7)) {
    return 0;
  }
  return 1;
}

/* ---- 0x10001730  lua_istable ---- */
undefined4 __cdecl lua_istable(int param_1)

{
                    /* 0x1730  45  lua_istable */
  if ((param_1 != 0) && (*(int *)(g_pLuaState[8] + -8 + param_1 * 8) == -3)) {
    return 1;
  }
  return 0;
}

/* ---- 0x10001760  lua_isuserdata ---- */
undefined4 __cdecl lua_isuserdata(int param_1)

{
                    /* 0x1760  47  lua_isuserdata */
  if ((param_1 != 0) && (*(int *)(g_pLuaState[8] + -8 + param_1 * 8) == 0)) {
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
  if ((*(int *)(g_pLuaState[8] + -8 + param_1 * 8) != -1) &&
     (iVar1 = luaV_tonumber((int *)(g_pLuaState[8] + -8 + param_1 * 8)), iVar1 != 0)) {
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
  if ((param_1 != 0) && (*(int *)(g_pLuaState[8] + -8 + param_1 * 8) == -6)) {
    return 1;
  }
  return 0;
}

/* ---- 0x10001860  lua_getnumber ---- */
float __cdecl lua_getnumber(int param_1)

{
  int iVar1;
  int iVar2;
  
                    /* 0x1860  31  lua_getnumber */
  if (param_1 == 0) {
    return 0.0;
  }
  iVar1 = param_1 * 8;
  if (*(int *)(g_pLuaState[8] + -8 + iVar1) != -1) {
    iVar2 = luaV_tonumber((int *)(g_pLuaState[8] + -8 + iVar1));
    if (iVar2 != 0) {
      return 0.0;
    }
  }
  return *(float *)(g_pLuaState[8] + -4 + iVar1);
}

/* ---- 0x100018c0  lua_getstring ---- */
int __cdecl lua_getstring(int param_1)

{
  int iVar1;
  int iVar2;
  
                    /* 0x18c0  34  lua_getstring */
  if (param_1 == 0) {
    return 0;
  }
  iVar1 = param_1 * 8;
  if ((*(int *)(g_pLuaState[8] + -8 + iVar1) != -2) &&
     (iVar2 = luaV_tostring((int *)(g_pLuaState[8] + -8 + iVar1)), iVar2 != 0)) {
    return 0;
  }
  return *(int *)(g_pLuaState[8] + -4 + iVar1) + 0x18;
}

/* ---- 0x10001910  lua_getuserdata ---- */
undefined4 __cdecl lua_getuserdata(int param_1)

{
                    /* 0x1910  38  lua_getuserdata */
  if ((param_1 != 0) && (*(int *)(g_pLuaState[8] + -8 + param_1 * 8) == 0)) {
    return *(undefined4 *)(*(int *)(g_pLuaState[8] + param_1 * 8 + -4) + 0x14);
  }
  return 0;
}

/* ---- 0x10001940  lua_getcfunction ---- */
int __cdecl lua_getcfunction(int param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  int *piVar2;
  
                    /* 0x1940  28  lua_getcfunction */
  bVar1 = lua_iscfunction(param_1);
  if (((uint)(bVar1)) == 0) {
    return 0;
  }
  piVar2 = luaA_protovalue((int *)(g_pLuaState[8] + -8 + param_1 * 8));
  return piVar2[1];
}

/* ---- 0x10001970  luaA_protovalue ---- */
/* Named luaA_protovalue (not in the remaster, gcc inlined it there): Lua 3.1 source name (lapi.c
   luaA_protovalue: a closure (normalized_type) gives its function consts[0], anything else itself;
   used by lua_getcfunction / lua_getlocal); was luaA_normalizeObj. */

int * __cdecl luaA_protovalue(int *param_1)

{
  int iVar1;
  
  iVar1 = normalized_type(param_1);
  if (iVar1 == -8) {
    return (int *)(param_1[1] + 0xc);
  }
  return param_1;
}

/* ---- 0x10001990  lua_gettask ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl lua_gettask(int obj)

{
  longlong lVar1;
  
                    /* 0x1990  37  lua_gettask */
  if ((obj != 0) && (*(int *)(g_pLuaState[8] + -8 + obj * 8) == -6)) {
    lVar1 = _ftol();
    return (int)lVar1;
  }
  return -1;
}
#endif


/* ---- 0x100019c0  lua_pushtask ---- */
undefined4 __cdecl lua_pushtask(int param_1)

{
  int *piVar1;
  
                    /* 0x19c0  62  lua_pushtask */
  *(undefined4 *)g_pLuaState[7] = 0xfffffffa;
  *(float *)(g_pLuaState[7] + 4) = (float)param_1;
  if ((uint)g_pLuaState[9] <= (uint)g_pLuaState[7]) {
    luaD_checkstack(1);
  }
  piVar1 = g_pLuaState;
  g_pLuaState[7] = g_pLuaState[7] + 8;
  return piVar1;
}

/* ---- 0x10001a10  lua_pushnil ---- */
undefined4 __cdecl lua_pushnil(void)

{
  int *piVar1;
  
                    /* 0x1a10  58  lua_pushnil */
  *(undefined4 *)g_pLuaState[7] = 0xfffffff9;
  if ((uint)g_pLuaState[9] <= (uint)g_pLuaState[7]) {
    luaD_checkstack(1);
  }
  piVar1 = g_pLuaState;
  g_pLuaState[7] = g_pLuaState[7] + 8;
  return piVar1;
}

/* ---- 0x10001a50  lua_pushnumber ---- */
void __cdecl lua_pushnumber(float n)

{
                    /* 0x1a50  59  lua_pushnumber */
  *(undefined4 *)g_pLuaState[7] = 0xffffffff;
  *(float *)(g_pLuaState[7] + 4) = n;
  if ((uint)g_pLuaState[9] <= (uint)g_pLuaState[7]) {
    luaD_checkstack(1);
  }
  g_pLuaState[7] = g_pLuaState[7] + 8;
  return;
}

/* ---- 0x10001aa0  lua_pushstring ---- */
undefined4 __cdecl lua_pushstring(byte *param_1)

{
  undefined4 uVar1;
  
                    /* 0x1aa0  61  lua_pushstring */
  if (param_1 == (byte *)0x0) {
    *(undefined4 *)g_pLuaState[7] = 0xfffffff9;
  }
  else {
    uVar1 = luaS_new(param_1);
    *(undefined4 *)(g_pLuaState[7] + 4) = uVar1;
    *(undefined4 *)g_pLuaState[7] = 0xfffffffe;
  }
  if ((uint)g_pLuaState[9] <= (uint)g_pLuaState[7]) {
    luaD_checkstack(1);
  }
  g_pLuaState[7] = g_pLuaState[7] + 8;
  uVar1 = ((code *)luaC_checkGC)();
  return uVar1;
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
  *(undefined4 *)g_pLuaState[7] = 0xfffffffb;
  *(int *)(g_pLuaState[7] + 4) = param_1;
  if ((uint)g_pLuaState[9] <= (uint)g_pLuaState[7]) {
    luaD_checkstack(1);
  }
  g_pLuaState[7] = g_pLuaState[7] + 8;
  uVar1 = ((code *)luaV_closure)(param_2);
  return uVar1;
}

/* ---- 0x10001b90  lua_pushusertag ---- */
undefined4 __cdecl lua_pushusertag(byte *param_1,uint param_2)

{
  undefined4 uVar1;
  
                    /* 0x1b90  63  lua_pushusertag */
  if (((int)param_2 < 0) && (param_2 != 0xffffffff)) {
    luaT_realtag(param_2);
  }
  uVar1 = luaS_createudata(param_1,param_2);
  *(undefined4 *)(g_pLuaState[7] + 4) = uVar1;
  *(undefined4 *)g_pLuaState[7] = 0;
  if ((uint)g_pLuaState[9] <= (uint)g_pLuaState[7]) {
    luaD_checkstack(1);
  }
  g_pLuaState[7] = g_pLuaState[7] + 8;
  uVar1 = ((code *)luaC_checkGC)();
  return uVar1;
}

/* ---- 0x10001c00  luaA_pushobject ---- */
/* Unidentified function of lapi.c (Lua 3.1 C API) */

void __cdecl luaA_pushobject(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)g_pLuaState[7];
  *puVar1 = *param_1;
  puVar1[1] = param_1[1];
  if ((uint)g_pLuaState[9] <= (uint)g_pLuaState[7]) {
    luaD_checkstack(1);
  }
  g_pLuaState[7] = g_pLuaState[7] + 8;
  return;
}

/* ---- 0x10001c40  lua_pushobject ---- */
undefined4 __cdecl lua_pushobject(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
                    /* 0x1c40  60  lua_pushobject */
  if (param_1 == 0) {
    uVar2 = lua_error((byte *)s_API_error___attempt_to_push_a_NO_10026190);
    return uVar2;
  }
  set_normalized((int *)g_pLuaState[7],(int *)(g_pLuaState[8] + -8 + param_1 * 8));
  if ((uint)g_pLuaState[9] <= (uint)g_pLuaState[7]) {
    luaD_checkstack(1);
  }
  piVar1 = g_pLuaState;
  g_pLuaState[7] = g_pLuaState[7] + 8;
  return piVar1;
}

/* ---- 0x10001ca0  lua_tag ---- */
undefined4 __cdecl lua_tag(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
                    /* 0x1ca0  81  lua_tag */
  if (param_1 == 0) {
    return 0xfffffff9;
  }
  uVar2 = *(undefined4 *)(g_pLuaState[8] + -8 + param_1 * 8);
  iVar1 = g_pLuaState[8] + -8 + param_1 * 8;
  switch(uVar2) {
  case 0:
    return *(undefined4 *)(*(int *)(iVar1 + 4) + 0x10);
  case 0xfffffff5:
    return 0xfffffffb;
  case 0xfffffff6:
    return 0xfffffffc;
  case 0xfffffff7:
  case 0xfffffff8:
    return *(undefined4 *)(*(int *)(iVar1 + 4) + 0xc);
  default:
    return uVar2;
  case 0xfffffffd:
    return *(undefined4 *)(*(int *)(iVar1 + 4) + 0x14);
  }
}

/* ---- 0x10001d30  lua_settag ---- */
int * __cdecl lua_settag(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
                    /* 0x1d30  77  lua_settag */
  ((code *)checkCparams)(1);
  luaT_realtag(param_1);
  iVar1 = g_pLuaState[7];
  iVar2 = *(int *)(iVar1 + -8);
  if (iVar2 == -3) {
    *(int *)(*(int *)(iVar1 + -4) + 0x14) = param_1;
    piVar3 = g_pLuaState;
    g_pLuaState[7] = g_pLuaState[7] + -8;
    return piVar3;
  }
  if (iVar2 != 0) {
    luaL_verror(s_cannot_change_the_tag_of_a___20s_100261b8,(&g_pLuaO_typenames)[-iVar2]);
    piVar3 = g_pLuaState;
    g_pLuaState[7] = g_pLuaState[7] + -8;
    return piVar3;
  }
  *(int *)(*(int *)(iVar1 + -4) + 0x10) = param_1;
  piVar3 = g_pLuaState;
  g_pLuaState[7] = g_pLuaState[7] + -8;
  return piVar3;
}

/* ---- 0x10001db0  lua_pausetasks ---- */
undefined4 __cdecl lua_pausetasks(void)

{
  int *piVar1;
  
                    /* 0x1db0  54  lua_pausetasks */
  for (piVar1 = (int *)LState_next(g_dwL_Main); piVar1 != (int *)0x0;
      piVar1 = (int *)LState_next((int)piVar1)) {
    if (piVar1 != g_pLuaState) {
      piVar1[5] = 1;
    }
  }
  return 0;
}

/* ---- 0x10001de0  lua_unpausetasks ---- */
undefined4 __cdecl lua_unpausetasks(void)

{
  int iVar1;
  
                    /* 0x1de0  83  lua_unpausetasks */
  for (iVar1 = LState_next(g_dwL_Main); iVar1 != 0; iVar1 = LState_next(iVar1)) {
    *(undefined4 *)(iVar1 + 0x14) = 0;
  }
  return 0;
}

/* ---- 0x10001e10  lua_updatetasks ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int __cdecl lua_updatetasks(int param_1)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int *piVar2;
  int iVar3;
  undefined4 unaff_ESI;
  int *piVar4;
  int unaff_EDI;
  #define local_4c (*(undefined4 (*)[16])(_frame + (0x60 - 0x4c)))
  #define local_c (*(int **)(_frame + (0x60 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x60 - 0x8)))
  
                    /* 0x1e10  85  lua_updatetasks */
  local_c = g_pLuaState;
LAB_10001e23:
  piVar2 = (int *)LState_next((int)g_pLuaState);
  piVar4 = local_c;
  while (local_c = piVar4, piVar2 != (int *)0x0) {
    for (iVar3 = *piVar2; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0xc)) {
      ExecutionState_resetcounter(iVar3);
    }
    piVar2[4] = 0;
    piVar2 = (int *)LState_next((int)piVar2);
    piVar4 = local_c;
  }
  do {
    piVar2 = (int *)LState_next((int)g_pLuaState);
    while (g_pLuaState = piVar2, piVar2 = piVar4, piVar1 = piVar4, g_pLuaState != (int *)0x0) {
      if ((g_pLuaState[4] == 0) && (g_pLuaState[5] == 0)) {
        local_8 = 4;
        g_pLuaState[0xd] = (int)local_4c;
        iVar3 = _setjmp3(local_4c,0,unaff_EDI,unaff_ESI);
        if (iVar3 == 0) {
          if (*g_pLuaState == 0) {
            iVar3 = g_pLuaState[10];
            luaD_openstack((g_pLuaState[7] - g_pLuaState[8] >> 3) - iVar3);
            set_normalized((int *)(g_pLuaState[8] + g_pLuaState[10] * 8),g_pLuaState + 0x31);
            if (lua_taskhook != 0) {
              luaD_taskHook(g_pLuaState[0x30],0);
            }
            iVar3 = luaD_call(iVar3 + 1,0xff);
          }
          else {
            if (lua_taskhook != 0) {
              luaD_taskHook(g_pLuaState[0x30],2);
            }
            iVar3 = luaD_call(*(undefined4 *)(*g_pLuaState + 0x10),
                              *(undefined4 *)(*g_pLuaState + 0x14));
          }
        }
        else {
          local_8 = 3;
          luaD_deletestates(*g_pLuaState);
          iVar3 = 0;
          *g_pLuaState = 0;
        }
        if (iVar3 != 0) {
          if (*g_pLuaState == 0) {
            (**(code **)(g_dwLuaHS + 0x18))
                      (s_L__pExecutionState_100261dc,s_C__grimsrc_libs_lua_src_lapi_cpp_100260d4,
                       0x2fe);
          }
          if (iVar3 != 0) {
            if (lua_taskhook != 0) {
              luaD_taskHook(g_pLuaState[0x30],1);
            }
            g_pLuaState[4] = 1;
            goto LAB_1000201b;
          }
        }
        if (lua_taskhook != 0) {
          luaD_taskHook(g_pLuaState[0x30],local_8);
        }
        piVar2 = (int *)LState_next((int)g_pLuaState);
        piVar1 = g_pLuaState;
        piVar4 = local_c;
        if (g_pLuaState != (int *)0x0) {
          LState_Destruct(g_pLuaState);
          luaM_free(piVar1);
          piVar4 = local_c;
        }
      }
      else {
LAB_1000201b:
        piVar2 = (int *)LState_next((int)g_pLuaState);
        piVar4 = local_c;
      }
    }
    do {
      g_pLuaState = piVar1;
      piVar2 = (int *)LState_next((int)piVar2);
      if (piVar2 == (int *)0x0) {
        if ((param_1 == 0) || (iVar3 = LState_next((int)g_pLuaState), iVar3 == 0)) {
          iVar3 = LState_next((int)g_pLuaState);
          return iVar3 != 0;
        }
        goto LAB_10001e23;
      }
      piVar1 = g_pLuaState;
    } while ((piVar2[4] != 0) || (piVar2[5] != 0));
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
  int *piVar3;
  int iVar4;
  
                    /* 0x2090  79  lua_stackedfunction */
  iVar2 = (g_pLuaState[7] - g_pLuaState[8]) + -8 >> 3;
  if (iVar2 < 0) {
    return 0;
  }
  piVar3 = (int *)(g_pLuaState[8] + iVar2 * 8);
  while ((((iVar1 = *piVar3, iVar1 != -9 && (iVar1 != -10)) && (iVar4 = param_1, iVar1 != -0xb)) ||
         (iVar4 = param_1 + -1, param_1 != 0))) {
    iVar2 = iVar2 + -1;
    piVar3 = piVar3 + -2;
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
undefined4 __cdecl lua_currentline(int param_1)

{
  int *piVar1;
  int iVar2;
  
                    /* 0x2280  20  lua_currentline */
  iVar2 = g_pLuaState[8] + -8 + param_1 * 8;
  piVar1 = (int *)(iVar2 + 8);
  if ((piVar1 < (int *)g_pLuaState[7]) && (*piVar1 == -0xc)) {
    return *(undefined4 *)(iVar2 + 0xc);
  }
  return 0xffffffff;
}

/* ---- 0x100022b0  lua_currenttask ---- */
int lua_currenttask(void)

{
                    /* 0x22b0  21  lua_currenttask */
  return g_pLuaState[0x30];
}

/* ---- 0x100022c0  lua_getlocal ---- */
int __cdecl lua_getlocal(int param_1,int param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
                    /* 0x22c0  30  lua_getlocal */
  iVar2 = lua_tag(param_1);
  if (iVar2 == -4) {
    piVar1 = (int *)(g_pLuaState[8] + -8 + param_1 * 8);
    piVar3 = luaA_protovalue(piVar1);
    iVar2 = piVar3[1];
    uVar4 = lua_currentline(param_1);
    iVar2 = luaF_getlocalname(iVar2,param_2,uVar4);
    *param_3 = iVar2;
    if (iVar2 != 0) {
      return (((param_2 * 8 + 8) - g_pLuaState[8]) + (int)piVar1 >> 3) + 1;
    }
  }
  return 0;
}

/* ---- 0x10002330  lua_setlocal ---- */
undefined4 __cdecl lua_setlocal(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
                    /* 0x2330  75  lua_setlocal */
  iVar2 = lua_tag(param_1);
  if (iVar2 == -4) {
    piVar1 = (int *)(g_pLuaState[8] + -8 + param_1 * 8);
    piVar3 = luaA_protovalue(piVar1);
    iVar2 = piVar3[1];
    uVar4 = lua_currentline(param_1);
    iVar2 = luaF_getlocalname(iVar2,param_2,uVar4);
    checkCparams(1);
    g_pLuaState[7] = g_pLuaState[7] + -8;
    if (iVar2 != 0) {
      piVar3 = (int *)g_pLuaState[7];
      piVar1[param_2 * 2 + 2] = *piVar3;
      piVar1[param_2 * 2 + 3] = piVar3[1];
      return 1;
    }
  }
  return 0;
}

/* ---- 0x100023c0  lua_funcinfo ---- */
undefined4 __cdecl lua_funcinfo(int param_1,int *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  
                    /* 0x23c0  27  lua_funcinfo */
  iVar1 = lua_isfunction(param_1);
  if (iVar1 == 0) {
    uVar2 = lua_error((byte *)s_API____funcinfo__called_with_a_n_10026268);
    return uVar2;
  }
  piVar3 = luaA_protovalue((int *)(g_pLuaState[8] + -8 + param_1 * 8));
  iVar1 = normalized_type(piVar3);
  if (iVar1 == -4) {
    *param_2 = *(int *)(piVar3[1] + 0x18) + 0x18;
    iVar1 = piVar3[1];
    *param_3 = *(undefined4 *)(iVar1 + 0x14);
    return iVar1;
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
  ((code *)set_normalized)((int *)g_pLuaState[7],(int *)(g_pLuaState[8] + -8 + param_1 * 8));
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

void __cdecl checkfunc(int *param_1)

{
  luaO_equalObj(param_1,(int *)g_pLuaState[7]);
  return;
}

/* ---- 0x100024c0  lua_beginblock ---- */
int * __cdecl lua_beginblock(void)

{
  int *piVar1;
  int *piVar2;
  
                    /* 0x24c0  12  lua_beginblock */
  if (9 < g_pLuaState[0x2f]) {
    lua_error((byte *)s_too_many_nested_blocks_100262b0);
  }
  piVar1 = g_pLuaState;
  piVar2 = g_pLuaState + g_pLuaState[0x2f] * 3 + 0x11;
  *piVar2 = g_pLuaState[10];
  piVar2[1] = piVar1[0xb];
  piVar2[2] = piVar1[0xc];
  piVar2 = g_pLuaState;
  g_pLuaState[0x2f] = g_pLuaState[0x2f] + 1;
  return piVar2;
}

/* ---- 0x10002510  lua_endblock ---- */
undefined4 __cdecl lua_endblock(void)

{
  int *piVar1;
  int *piVar2;
  undefined4 uVar3;
  
                    /* 0x2510  25  lua_endblock */
  g_pLuaState[0x2f] = g_pLuaState[0x2f] + -1;
  piVar2 = g_pLuaState;
  piVar1 = g_pLuaState + g_pLuaState[0x2f] * 3 + 0x11;
  g_pLuaState[10] = *piVar1;
  piVar2[0xb] = piVar1[1];
  piVar2[0xc] = piVar1[2];
  uVar3 = ((code *)luaD_adjusttop)(g_pLuaState[10]);
  return uVar3;
}

/* ---- 0x10002560  lua_ref ---- */
uint __cdecl lua_ref(int param_1)

{
  uint uVar1;
  
                    /* 0x2560  69  lua_ref */
  ((code *)checkCparams)(1);
  uVar1 = luaC_ref((int *)(g_pLuaState[7] + -8),param_1);
  g_pLuaState[7] = g_pLuaState[7] + -8;
  return uVar1;
}

/* ---- 0x10002590  lua_getref ---- */
undefined4 __cdecl lua_getref(uint param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
                    /* 0x2590  33  lua_getref */
  puVar1 = (undefined4 *)luaC_getref(param_1);
  if (puVar1 != (undefined4 *)0x0) {
    uVar2 = put_luaObject(puVar1);
    return uVar2;
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

void __cdecl do_unprotectedrun(undefined4 param_1,int param_2,void *param_3)

{
  int iVar1;
  
  iVar1 = (g_pLuaState[7] - g_pLuaState[8] >> 3) - param_2;
  luaD_openstack(param_2);
  *(undefined4 *)(g_pLuaState[8] + iVar1 * 8) = 0xfffffffb;
  *(undefined4 *)(g_pLuaState[8] + 4 + iVar1 * 8) = param_1;
  g_pLuaState[2] = g_pLuaState[2] + 1;
  luaD_call(iVar1 + 1,param_3);
  g_pLuaState[2] = g_pLuaState[2] + -1;
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
  int *piVar2;
  int iVar3;
  #define local_4 (*(undefined **)(_frame + (0x20 - 0x4)))
  
                    /* 0x2670  10  lua_Save */
  puVar1 = param_1;
  local_4 = (undefined *)0x0;
  g_dwSaveFunc = param_1;
  lua_collectgarbage(0);
  LState_SaveGlobals(((unsigned)(uintptr_t)LuaSaveWriter));
  luaA_ResetSaveCount();
  for (piVar2 = g_dwL_Main; piVar2 != (int *)0x0; piVar2 = (int *)LState_next((int)piVar2)) {
    if (piVar2 == g_pLuaState) {
      param_1 = local_4;
    }
    local_4 = local_4 + 1;
  }
  (*(code *)puVar1)(&local_4,4);
  (*(code *)puVar1)(&param_1,4);
  piVar2 = g_dwL_Main;
  if (g_dwL_Main == (int *)0x0) {
    return 0;
  }
  do {
    iVar3 = LState_Save(piVar2,((unsigned)(uintptr_t)LuaSaveWriter));
    if (iVar3 != 0) {
      return 1;
    }
    luaA_ResetSaveCount();
    piVar2 = (int *)LState_next((int)piVar2);
  } while (piVar2 != (int *)0x0);
  return 0;
}
#undef local_4


/* ---- 0x10002730  LuaSaveWriter ---- */
/* Original name LuaSaveWriter (the remaster's libLua.so: static LuaSaveWriter(void*, unsigned):
   lua_totalBytesSaved += size, then the save callback); was FUN_10002730. */

void __cdecl LuaSaveWriter(undefined4 param_1,int param_2)

{
  g_dwLua_totalBytesSaved = g_dwLua_totalBytesSaved + param_2;
  (*g_dwSaveFunc)(param_1,param_2);
  return;
}

/* ---- 0x10002760  lua_Restore ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 lua_Restore(code *param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  undefined4 uVar2;
  int *this;
  int iVar3;
  int *a1;
  uint uVar4;
  #define iStack_18 (*(int *)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined4 **)(_frame + (0x30 - 0x10)))
  
                    /* 0x2760  9  lua_Restore */
  lua_close();
  puStack_10 = luaM_malloc(0xd4);
  if (puStack_10 == (undefined4 *)0x0) {
    g_pLuaState = (int *)0x0;
  }
  else {
    g_pLuaState = LState_Construct(puStack_10);
  }
  g_dwL_Main = g_pLuaState;
  LState_initglobals();
  LState_GlobalBeginRestore((int)param_1);
  uVar2 = g_dwLState_numThreads;
  (*param_1)(&uStack_14,4);
  if (uStack_14 == 0) {
    (**(code **)(g_dwLuaHS + 0x18))
              (s_numTasks___0_100262f4,s_C__grimsrc_libs_lua_src_lapi_cpp_100260d4,0x499);
  }
  (*param_1)(&iStack_18,4);
  LState_Restore(g_dwL_Main,(int)param_1);
  uVar4 = 1;
  a1 = g_dwL_Main;
  if (1 < uStack_14) {
    do {
      puStack_10 = luaM_malloc(0xd4);
      if (puStack_10 == (undefined4 *)0x0) {
        this = (int *)0x0;
      }
      else {
        this = LState_Construct(puStack_10);
      }
      iVar3 = LState_Restore(this,(int)param_1);
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
    g_pLuaState = (int *)LState_next((int)g_pLuaState);
  }
  LState_GlobalEndRestore((int)param_1);
  g_dwLState_numThreads = uVar2;
  return 0;
}
#undef iStack_18
#undef puStack_10
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
  undefined4 uVar1;
  
                    /* 0x4650  26  lua_error */
  if (param_1 != (byte *)0x0) {
    message(param_1);
  }
  if (g_pLuaState[0xd] != 0) {
    uVar1 = ((code *)longjmp)(g_pLuaState[0xd]);
    return uVar1;
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
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
                    /* 0x4ee0  17  lua_collectgarbage */
  iVar1 = g_dwLState_nblocks;
  markall();
  invalidaterefs();
  puVar2 = (undefined4 *)luaS_collector();
  puVar3 = (undefined4 *)listcollect(&g_dwLState_roottable);
  puVar4 = (undefined4 *)listcollect(&g_dwLState_rootproto);
  puVar5 = (undefined4 *)listcollect(&g_dwLState_rootcl);
  g_dwLState_GCthreshold = g_dwLState_GCthreshold * 4;
  luaC_hashcallIM(puVar3);
  luaC_strcallIM(puVar2);
  luaD_gcIM((uint *)&g_LuaO_nilobject);
  luaH_free(puVar3);
  luaS_free(puVar2);
  luaF_freeproto(puVar4);
  luaF_freeclosure(puVar5);
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
  ((code *)luaL_openlib)(&g_pIolib,10);
  lua_recognizelib(IMG_ADDR(0x10026b50),5);
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
  ((code *)luaL_openlib)(&g_pMathlib,0x15);
  lua_recognizelib(IMG_ADDR(0x10026fd8),1);
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
int * __cdecl lua_open(void)

{
  int *piVar1;
  
                    /* 0x8b40  52  lua_open */
  piVar1 = g_pLuaState;
  if (g_pLuaState == (int *)0x0) {
    g_pLuaState = lua_newstate();
    luaB_predefine();
    piVar1 = (int *)lua_recognizelib(IMG_ADDR(0x100277b8),1);
  }
  return piVar1;
}

/* ---- 0x10008c30  lua_close ---- */
undefined4 __cdecl lua_close(void)

{
  int *piVar1;
  uint *puVar2;
  int *piVar3;
  undefined4 uVar4;
  
                    /* 0x8c30  15  lua_close */
  puVar2 = luaS_collectudata();
  g_dwLState_GCthreshold = 0x7ffffffd;
  luaC_hashcallIM(g_dwLState_roottable);
  luaC_strcallIM(puVar2);
  luaD_gcIM((uint *)&g_LuaO_nilobject);
  luaH_free(g_dwLState_roottable);
  luaF_freeproto(g_dwLState_rootproto);
  luaF_freeclosure(g_dwLState_rootcl);
  luaS_free(puVar2);
  luaS_freeall();
  (**(code **)(g_dwLuaHS + 0x24))(g_dwLState_IMtable);
  (**(code **)(g_dwLuaHS + 0x24))(g_dwLState_refArray);
  (**(code **)(g_dwLuaHS + 0x24))(g_dwLState_Mbuffer);
  g_dwLState_IMtable = 0;
  g_dwLState_refArray = 0;
  g_dwLState_Mbuffer = 0;
  piVar1 = g_pLuaState;
  piVar3 = g_dwL_Main;
  while (g_pLuaState = piVar3, g_pLuaState != (int *)0x0) {
    piVar3 = (int *)LState_next((int)g_pLuaState);
    piVar1 = g_pLuaState;
    if (g_pLuaState != (int *)0x0) {
      LState_Destruct(g_pLuaState);
      luaM_free(piVar1);
      piVar1 = g_pLuaState;
    }
  }
  g_pLuaState = piVar1;
  uVar4 = ((code *)ExecutionState_CleanUp)();
  g_pLuaState = (int *)0x0;
  g_dwL_Main = (int *)0x0;
  g_dwLState_lstate_class_initialized = 0;
  return uVar4;
}

/* ---- 0x1000a6e0  lua_strlibopen ---- */
undefined4 __cdecl lua_strlibopen(void)

{
  undefined4 uVar1;
  
                    /* 0xa6e0  80  lua_strlibopen */
  uVar1 = ((code *)luaL_openlib)(&g_pStrlib,9);
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
