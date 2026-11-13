/* LUA.DLL :: lgc.c
 * functions 0x10004e70 .. 0x10005320 (15 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10004e70  luaC_hashcallIM ---- */
/* Unidentified function of lgc.c (garbage collector) */

void __cdecl luaC_hashcallIM(Hash *l)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(TObject *)(_frame + (0x20 - 0x8)))
  
  local_8.nTtype = -3;
  for (; l != (Hash *)0x0; l = l->pNext) {
    local_8.dwValue = (uint)l;
    luaD_gcIM(&local_8);
  }
  return;
}
#undef local_8


/* ---- 0x10004ea0  luaC_strcallIM ---- */
/* Unidentified function of lgc.c (garbage collector) */

void __cdecl luaC_strcallIM(TaggedString *l)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(TObject *)(_frame + (0x20 - 0x8)))
  
  local_8.nTtype = 0;
  for (; l != (TaggedString *)0x0; l = l->pNext) {
    if (l->nConstIndex == -1) {
      local_8.dwValue = (uint)l;
      luaD_gcIM(&local_8);
    }
  }
  return;
}
#undef local_8


/* ---- 0x10004fc0  invalidaterefs ---- */
/* Named invalidaterefs (not in the remaster, gcc inlined it there): Lua 3.1 source name (lgc.c:
   HOLD references whose object is not marked become COLLECTED); was lgc__4fc0. */

void invalidaterefs(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (g_dwLState_refSize != 0) {
    iVar2 = 0;
    do {
      if ((((TObject *)(g_dwLState_refArray + iVar2))[1].nTtype == 1) &&
         (iVar1 = ismarked((TObject *)(g_dwLState_refArray + iVar2)), iVar1 == 0)) {
        *(undefined4 *)(g_dwLState_refArray + 8 + iVar2) = 3;
      }
      uVar3 = uVar3 + 1;
      iVar2 = iVar2 + 0xc;
    } while (uVar3 < g_dwLState_refSize);
  }
  return;
}

/* ---- 0x10005010  ismarked ---- */
/* Named ismarked (not in the remaster, gcc inlined it there): Lua 3.1 source name (lgc.c: the mark
   bit by object type, used by invalidaterefs); was lgc__5010. */

int __cdecl ismarked(TObject *o)

{
  switch(o->nTtype) {
  case -8:
    return *(int *)(o->dwValue + 4);
  default:
    return 1;
  case -4:
  case -2:
  case 0:
    return *(int *)(o->dwValue + 4);
  case -3:
    return *(int *)(o->dwValue + 4);
  }
}

/* ---- 0x10005070  listcollect ---- */
/* Named listcollect (not in the remaster, gcc inlined it there): Lua 3.1 source name (lgc.c:
   unlinks the unmarked nodes of a GC list and returns them); was lgc__5070. */

int __cdecl listcollect(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)0x0;
  while (puVar1 = param_1, puVar1 != (undefined4 *)0x0) {
    puVar1[1] = 0;
    puVar2 = (undefined4 *)*puVar1;
    while ((param_1 = puVar2, param_1 != (undefined4 *)0x0 && (param_1[1] == 0))) {
      *puVar1 = *param_1;
      *param_1 = puVar3;
      puVar3 = param_1;
      puVar2 = (undefined4 *)*puVar1;
    }
  }
  return (int)puVar3;
}

/* ---- 0x100050b0  markall ---- */
/* Named markall (not in the remaster, gcc inlined it there): Lua 3.1 source name (lgc.c static
   markall: the stacks with markobject, globalmark, travlock, luaT_travtagmethods(markobject), in
   that order; called by lua_collectgarbage); was luaC_markall. */

void markall(void)

{
  luaD_travallstacks(markobject);
  globalmark();
  travlock();
  luaT_travtagmethods(markobject);
  return;
}

/* ---- 0x100050e0  travlock ---- */
/* Named travlock (not in the remaster, gcc inlined it there): Lua 3.1 source name (lgc.c static
   travlock: markobject of every locked entry of LState refArray / refSize); was luaC_travstack. */

void travlock(void)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (g_dwLState_refSize != 0) {
    iVar1 = 0;
    do {
      if (((TObject *)(g_dwLState_refArray + iVar1))[1].nTtype == 0) {
        markobject((TObject *)(g_dwLState_refArray + iVar1));
      }
      uVar2 = uVar2 + 1;
      iVar1 = iVar1 + 0xc;
    } while (uVar2 < g_dwLState_refSize);
  }
  return;
}

/* ---- 0x10005120  globalmark ---- */
/* Named globalmark (not in the remaster, gcc inlined it there): Lua 3.1 source name (lgc.c static
   globalmark: for every global of rootglobal that is not nil, markobject of its value and strmark
   of its name); was luaC_travglobal. */

void globalmark(void)

{
  TaggedString *s;
  
  for (s = g_dwLState_rootglobal; s != (TaggedString *)0x0; s = s->pNext) {
    if ((s->globalval).nTtype != -7) {
      markobject(&s->globalval);
      strmark(s);
    }
  }
  return;
}

/* ---- 0x10005150  strmark ---- */
/* Named strmark (not in the remaster, gcc inlined it there): Lua 3.1 source name (lgc.c static
   strmark: marks a string, marked = 1); was luaC_strmark. */

void __cdecl strmark(TaggedString *s)

{
  if ((s != (TaggedString *)0x0) && (s->nMarked == 0)) {
    s->nMarked = 1;
  }
  return;
}

/* ---- 0x10005170  markobject ---- */
/* Original name markobject (the remaster's libLua.so: static markobject(TObject*): switch on the
   tag (closure, table, proto, string)); was luaC_markobject. */

int __cdecl markobject(TObject *o)

{
  switch(o->nTtype) {
  case -10:
  case -4:
    luaC_protomark((TProtoFunc *)o->dwValue);
    break;
  case -9:
  case -8:
    closuremark((Closure *)o->dwValue);
    return 0;
  case -3:
    hashmark((Hash *)o->dwValue);
    return 0;
  case -2:
  case 0:
    strmark((TaggedString *)o->dwValue);
    return 0;
  }
  return 0;
}

/* ---- 0x100051f0  luaC_protomark ---- */
/* Named luaC_protomark (not in the remaster: inlined into markobject there) Lua 3.1's static
   protomark: marks the source name, the constants and the local names of a prototype (markobject's
   PROTO / PMARK case); was misnamed luaC_hashmark; was luaC_hashmark. */

void __cdecl luaC_protomark(TProtoFunc *f)

{
  int iVar1;
  LocVar *pLVar2;
  uint uVar3;
  LocVar *pLVar4;
  
  if (f->nMarked == 0) {
    pLVar4 = f->pLocvars;
    f->nMarked = 1;
    if (f->pFileName != (TaggedString *)0x0) {
      strmark(f->pFileName);
    }
    uVar3 = 0;
    if (f->nNconsts != 0) {
      do {
        markobject(f->pConsts + uVar3);
        uVar3 = uVar3 + 1;
      } while (uVar3 < (uint)f->nNconsts);
    }
    if (pLVar4 != (LocVar *)0x0) {
      iVar1 = pLVar4->nLine;
      while (iVar1 != -1) {
        if (pLVar4->pVarname != (TaggedString *)0x0) {
          strmark(pLVar4->pVarname);
        }
        pLVar2 = pLVar4 + 1;
        pLVar4 = pLVar4 + 1;
        iVar1 = pLVar2->nLine;
      }
    }
  }
  return;
}

/* ---- 0x10005270  closuremark ---- */
/* Original name closuremark (the remaster's libLua.so: static closuremark(Closure*): marks the
   closure's nelems + 1 consts (markobject's CLOSURE / CLMARK case)); was luaC_protomark. */

void __cdecl closuremark(Closure *f)

{
  TObject *o;
  int iVar1;
  
  if (f->nMarked == 0) {
    iVar1 = f->nNelems;
    f->nMarked = 1;
    if (-1 < iVar1) {
      o = f->aConsts + iVar1;
      iVar1 = iVar1 + 1;
      do {
        markobject(o);
        o = o + -1;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
  }
  return;
}

/* ---- 0x100052b0  hashmark ---- */
/* Original name hashmark (the remaster's libLua.so: static hashmark(Hash*): marks key and value of
   every node (markobject's ARRAY case)); was luaC_closuremark. */

void __cdecl hashmark(Hash *h)

{
  int iVar1;
  uint uVar2;
  TObject *o;
  
  if (h->nMarked == 0) {
    uVar2 = 0;
    h->nMarked = 1;
    if (h->nNhash != 0) {
      iVar1 = 0;
      do {
        o = (TObject *)((int)&(h->pNode->ref).nTtype + iVar1);
        if (o->nTtype != -7) {
          markobject(o);
          markobject(o + 1);
        }
        uVar2 = uVar2 + 1;
        iVar1 = iVar1 + 0x10;
      } while (uVar2 < (uint)h->nNhash);
    }
  }
  return;
}

/* ---- 0x10005300  luaC_checkGC ---- */
/* Original name luaC_checkGC (the remaster's libLua.so: nblocks >= GCthreshold ->
   lua_collectgarbage(0)); was lgc__5300. */

void luaC_checkGC(void)

{
  if (g_dwLState_GCthreshold <= g_dwLState_nblocks) {
    lua_collectgarbage(0);
  }
  return;
}

/* ---- 0x10005320  io_readfrom ---- */
/* Original name io_readfrom (the remaster's libLua.so: iolib entry 'readfrom'); was FUN_10005320.
    */

void __cdecl io_readfrom(void)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  char *pcVar4;
  longlong lVar5;
  
  iVar1 = lua_lua2C(3);
  if (iVar1 == 0) {
    closefile((byte *)s__INPUT_10026c00);
    setreturn((byte *)&PTR_DAT_100282d0,(byte *)s__INPUT_10026c00);
    return;
  }
  iVar2 = lua_tag(iVar1);
  lVar5 = gettag(1);
  if (iVar2 == (int)lVar5) {
    pbVar3 = (byte *)lua_getuserdata(iVar1);
    setreturn(pbVar3,(byte *)s__INPUT_10026c00);
    return;
  }
  pcVar4 = (char *)luaL_check_string(3);
  if (*pcVar4 == '|') {
    pbVar3 = (byte *)0x0;
  }
  else {
    pbVar3 = (byte *)(**(code **)(g_dwLuaHS + 0x30))(pcVar4,&DAT_10026a80);
  }
  if (pbVar3 == (byte *)0x0) {
    pushresult(0);
    return;
  }
  setreturn(pbVar3,(byte *)s__INPUT_10026c00);
  return;
}
