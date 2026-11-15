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
  int tag;
  
  g_dwLState_IMtable_size = 0x10;
  g_dwLState_last_tag = -7;
  g_dwLState_IMtable =
       (**(code **)(g_dwLuaHS + 0x20))(0x900,s_C__grimsrc_libs_lua_src_ltm_cpp_10027ed4,0x4e);
  for (tag = g_dwLState_last_tag; tag < 1; tag = tag + 1) {
    init_entry(tag);
  }
  return;
}

/* ---- 0x1000c8a0  init_entry ---- */
/* Named init_entry (not in the remaster, gcc inlined it there): Lua 3.1 source name (ltm.c: sets
   the tag methods of a tag to nil, used by luaT_init / lua_newtag); was ltm__c8a0. */

void __cdecl init_entry(int tag)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = iVar2 + tag * -0x90;
    iVar2 = iVar2 + 8;
    *(undefined4 *)(g_dwLState_IMtable + iVar1) = 0xfffffff9;
  } while (iVar2 < 0x90);
  return;
}

/* ---- 0x1000c920  luaT_realtag ---- */
/* ltm.c: not result of `newtag' Original name luaT_realtag (the remaster's libLua.so: string "tag
   %d is not result of `newtag'", callers lua_pushusertag, lua_settag); was luaT_checktag. */

void __cdecl luaT_realtag(int tag)

{
  if ((tag < g_dwLState_last_tag) || (-8 < tag)) {
    luaL_verror(s_tag__d_is_not_result_of__newtag__10027ef4,tag);
  }
  return;
}

/* ---- 0x1000c9c0  validevent ---- */
/* Named validevent (not in the remaster, gcc inlined it there): Lua 3.1 source name (ltm.c static
   validevent(t, e): 1 for tags below LUA_T_NIL, else validevents[-t][e]); was luaT_gettm. */

int __cdecl validevent(int t,int e)

{
  if (t < -7) {
    return 1;
  }
  return (int)g_aValidevents[-t][e];
}

/* ---- 0x1000c9f0  luaT_checktag ---- */
/* ltm.c: %d is not a valid tag Named luaT_checktag (not in the remaster: inlined there) Lua 3.1's
   static checktag: '%d is not a valid tag'; the name luaT_realtag belongs to 1000c920; was
   luaT_realtag. */

void __cdecl luaT_checktag(int tag)

{
  if ((tag < g_dwLState_last_tag) || (0 < tag)) {
    luaL_verror(s__d_is_not_a_valid_tag_10027f18,tag);
  }
  return;
}

/* ---- 0x1000ca20  luaT_efectivetag ---- */
/* Original name luaT_efectivetag (the remaster's libLua.so: the original spelling; callers
   luaD_call, luaD_gcIM, luaV_gettable / settable / getglobal / setglobal, call_binTM); was
   luaT_effectivetag. */

int __cdecl luaT_efectivetag(TObject *o)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = o->nTtype;
  if (iVar2 == -8) {
    iVar2 = *(int *)(o->dwValue + 0xc);
  }
  else {
    if (iVar2 == -3) {
      return *(int *)(o->dwValue + 0x14);
    }
    if (iVar2 == 0) {
      uVar1 = *(uint *)(o->dwValue + 0x10);
      return uVar1 & (-1 < (int)uVar1) - 1;
    }
  }
  return iVar2;
}

/* ---- 0x1000ca60  luaT_gettagmethod ---- */
/* Original name luaT_gettagmethod (the remaster's libLua.so: caller lua_gettagmethod); was
   ltm__ca60. */

undefined * __cdecl luaT_gettagmethod(int t,byte *event)

{
  int e;
  int iVar1;
  
  e = luaI_checkevent(event,&g_pLuaT_eventname);
  luaT_checktag(t);
  iVar1 = validevent(t,e);
  if (iVar1 != 0) {
    return (undefined *)(g_dwLState_IMtable + (e + t * -0x12) * 8);
  }
  return &g_LuaO_nilobject;
}

/* ---- 0x1000cab0  luaI_checkevent ---- */
/* ltm.c: not a valid event name */

int __cdecl luaI_checkevent(byte *name,undefined4 *luaT_eventname)

{
  int iVar1;
  
  iVar1 = luaO_findstring(name,luaT_eventname);
  if (iVar1 < 0) {
    luaL_verror(s____50s__is_not_a_valid_event_nam_10027f30,name);
  }
  return iVar1;
}

/* ---- 0x1000cae0  luaT_settagmethod ---- */
/* Original name luaT_settagmethod (the remaster's libLua.so: string "settagmethod: cannot change
   internal method `%.20s' for tag %d"); was ltm__cae0. */

void __cdecl luaT_settagmethod(int t,byte *event,undefined4 *func)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  uVar1 = func[1];
  uVar2 = *func;
  iVar3 = luaI_checkevent(event,&g_pLuaT_eventname);
  luaT_checktag(t);
  iVar4 = validevent(t,iVar3);
  if (iVar4 == 0) {
    luaL_verror(s_settagmethod__cannot_change_inte_10027f54,(&g_pLuaT_eventname)[iVar3],t);
  }
  iVar3 = (iVar3 + t * -0x12) * 8;
  puVar5 = (undefined4 *)(g_dwLState_IMtable + iVar3);
  *func = *puVar5;
  func[1] = puVar5[1];
  *(undefined4 *)(g_dwLState_IMtable + iVar3) = uVar2;
  *(undefined4 *)(g_dwLState_IMtable + 4 + iVar3) = uVar1;
  return;
}

/* ---- 0x1000cb80  luaT_travtagmethods ---- */
/* Original name luaT_travtagmethods (the remaster's libLua.so: string 'error', callers
   lua_collectgarbage (markall) and lua_getobjname); was ltm__cb80. */

char * __cdecl luaT_travtagmethods(undefined *fn)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = (*(code *)fn)(&g_dwLState_errorim);
  if (iVar1 != 0) {
    return s_error_10026648;
  }
  iVar2 = 0;
  iVar1 = g_dwLState_last_tag;
  do {
    iVar4 = 0;
    if (iVar1 < 1) {
      iVar3 = iVar2 * 8;
      do {
        iVar1 = (*(code *)fn)(g_dwLState_IMtable + iVar3);
        if (iVar1 != 0) {
          return (&g_pLuaT_eventname)[iVar2];
        }
        iVar4 = iVar4 + -1;
        iVar3 = iVar3 + 0x90;
        iVar1 = g_dwLState_last_tag;
      } while (g_dwLState_last_tag <= iVar4);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x12);
  return (char *)0x0;
}

/* ---- 0x1000cbf0  errorFB ---- */
/* Original name errorFB (the remaster's libLua.so: fallback table entry '  errorFB'); was
   FUN_1000cbf0. */

void errorFB(void)

{
  int o;
  
  o = lua_lua2C(1);
  lua_isstring(o);
  return;
}

/* ---- 0x1000cc10  nilFB ---- */
/* Original name nilFB (the remaster's libLua.so: fallback table entry '  nilFB' (an empty function
   in ltm.c; MSVC folded lstate's identical empty stderrorim into it: the 'stderrorim' entry points
   here too)); was FUN_1000cc10. */

void nilFB(void)

{
  return;
}

/* ---- 0x1000cc20  typeFB ---- */
/* Original name typeFB (the remaster's libLua.so: fallback table entry '  typeFB', string
   'unexpected type'); was FUN_1000cc20. */

void typeFB(void)

{
  lua_error((byte *)s_unexpected_type_10027f94);
  return;
}

/* ---- 0x1000cc30  luaT_setfallback ---- */
/* Original name luaT_setfallback (the remaster's libLua.so: string "`%.50s' is not a valid fallback
   name"); was FUN_1000cc30. */

void luaT_setfallback(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *name;
  int o;
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  code *fn;
  #define local_8 (*(TObject *)(_frame + (0x20 - 0x8)))
  
  if (DAT_1002bf80 == 0) {
    lua_recognizelib(((unsigned)(uintptr_t)&PTR_s_typeFB_10027d98),3);
    DAT_1002bf80 = 1;
  }
  name = (byte *)luaL_check_string(1);
  o = lua_lua2C(2);
  iVar1 = lua_isfunction(o);
  if (iVar1 == 0) {
    luaL_argerror(2,((unsigned)(uintptr_t)&s_function_expected_10026390));
  }
  iVar1 = luaO_findstring(name,&g_pLuaT_setfallback_oldnames);
  switch(iVar1) {
  case 0:
    local_8.nTtype = g_dwLState_errorim;
    local_8.dwValue = DAT_1002bf5c;
    piVar2 = (int *)luaA_Address(o);
    g_dwLState_errorim = *piVar2;
    DAT_1002bf5c = piVar2[1];
    fn = errorFB;
    break;
  case 1:
    local_8.nTtype = *(int *)(g_dwLState_IMtable + 0x408);
    local_8.dwValue = *(uint *)(g_dwLState_IMtable + 0x40c);
    puVar3 = (undefined4 *)luaA_Address(o);
    *(undefined4 *)(g_dwLState_IMtable + 0x408) = *puVar3;
    *(undefined4 *)(g_dwLState_IMtable + 0x40c) = puVar3[1];
    fn = nilFB;
    break;
  case 2:
    iVar1 = 5;
    local_8.nTtype = *(int *)(g_dwLState_IMtable + 0xd8);
    local_8.dwValue = *(uint *)(g_dwLState_IMtable + 0xdc);
    do {
      puVar3 = (undefined4 *)luaA_Address(o);
      fillvalids(iVar1,puVar3);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0xb);
    fn = typeFB;
    break;
  case 3:
    iVar1 = 0xb;
    local_8.nTtype = *(int *)(g_dwLState_IMtable + 0x448);
    local_8.dwValue = *(uint *)(g_dwLState_IMtable + 0x44c);
    do {
      puVar3 = (undefined4 *)luaA_Address(o);
      fillvalids(iVar1,puVar3);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0xf);
    fn = typeFB;
    break;
  default:
    iVar1 = luaO_findstring(name,&g_pLuaT_eventname);
    if (iVar1 < 0) {
      luaL_verror(s____50s__is_not_a_valid_fallback_n_10027fa4,name);
      fn = (code *)0x0;
    }
    else {
      local_8.nTtype = *(int *)(g_dwLState_IMtable + 0x3f0 + iVar1 * 8);
      local_8.dwValue = *(uint *)(g_dwLState_IMtable + 0x3f4 + iVar1 * 8);
      puVar3 = (undefined4 *)luaA_Address(o);
      fillvalids(iVar1,puVar3);
      if ((iVar1 == 0x10) || (iVar1 == 2)) {
        fn = nilFB;
      }
      else {
        fn = typeFB;
      }
    }
  }
  if (local_8.nTtype == -7) {
    lua_pushCclosure((int)fn,0);
    return;
  }
  luaA_pushobject(&local_8);
  return;
}
#undef local_8


/* ---- 0x1000ce50  fillvalids ---- */
/* Named fillvalids (not in the remaster, gcc inlined it there): Lua 3.1 source name (ltm.c static
   fillvalids(e, func): for each tag from LUA_T_NIL to LUA_T_USERDATA that validevent allows, stores
   func as its method e; called by luaT_setfallback); was luaT_gettmbyObj. */

void __cdecl fillvalids(int n,undefined4 *func)

{
  int iVar1;
  int t;
  int iVar2;
  
  t = -7;
  iVar2 = n * 8 + 0x3f0;
  do {
    iVar1 = validevent(t,n);
    if (iVar1 != 0) {
      *(undefined4 *)(g_dwLState_IMtable + iVar2) = *func;
      *(undefined4 *)(g_dwLState_IMtable + 4 + iVar2) = func[1];
    }
    t = t + 1;
    iVar2 = iVar2 + -0x90;
  } while (t < 1);
  return;
}
