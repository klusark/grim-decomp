/* LUA.DLL :: lfunc.c
 * functions 0x10004ba0 .. 0x10004e30 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10004ba0  luaF_newclosure ---- */
/* lfunc.c luaF_newclosure(nelems): a closure of nelems + 1 constants (0x14 + 8 * nelems bytes),
   linked into rootcl; caller luaV_closure. Was named luaF_newproto (the two constructors were
   swapped; types round 8, docs/notes/types_8.md). */

Closure * __cdecl luaF_newclosure(int nelems)

{
  Closure *pCVar1;
  
  pCVar1 = (Closure *)
           (**(code **)(g_dwLuaHS + 0x20))
                     (nelems * 8 + 0x14,s_C__grimsrc_libs_lua_src_lfunc_cp_10026aa4,0x16);
  luaO_insertlist(&g_dwLState_rootcl,(undefined4 *)pCVar1);
  g_dwLState_nblocks = g_dwLState_nblocks + 1;
  pCVar1->nNelems = nelems;
  return pCVar1;
}

/* ---- 0x10004bf0  luaF_newproto ---- */
/* lfunc.c luaF_newproto(): an empty function prototype (0x20 bytes, code / constants / locals /
   file name 0), linked into rootproto; callers the parser and lundump's LoadFunction. Was named
   luaF_newclosure (the two constructors were swapped; types round 8, docs/notes/types_8.md). */

TProtoFunc * __cdecl luaF_newproto(void)

{
  TProtoFunc *pTVar1;
  
  pTVar1 = (TProtoFunc *)
           (**(code **)(g_dwLuaHS + 0x20))(0x20,s_C__grimsrc_libs_lua_src_lfunc_cp_10026aa4,0x20);
  pTVar1->pCode = (byte *)0x0;
  pTVar1->nLineDefined = 0;
  pTVar1->pFileName = (TaggedString *)0x0;
  pTVar1->pConsts = (TObject *)0x0;
  pTVar1->nNconsts = 0;
  pTVar1->pLocvars = (LocVar *)0x0;
  luaO_insertlist(&g_dwLState_rootproto,(undefined4 *)pTVar1);
  g_dwLState_nblocks = g_dwLState_nblocks + 5;
  return pTVar1;
}

/* ---- 0x10004c40  luaF_freeproto ---- */
/* Original name luaF_freeproto (the remaster's libLua.so: remaster luaF_freeproto: walks the
   prototype list (luaF_freeproto(rootproto) in lua_close), nblocks -= gcsizeproto, freefunc); was
   luaF_freeclosure. */

void __cdecl luaF_freeproto(TProtoFunc *l)

{
  TProtoFunc *pTVar1;
  
  while (l != (TProtoFunc *)0x0) {
    pTVar1 = l->pNext;
    g_dwLState_nblocks = g_dwLState_nblocks + -5;
    freefunc(l);
    l = pTVar1;
  }
  return;
}

/* ---- 0x10004c70  freefunc ---- */
/* Named freefunc (not in the remaster, gcc inlined it there): Lua 3.1 source name (lfunc.c static
   freefunc: frees code, locvars, consts and the prototype); was luaF_freeproto. */

void __cdecl freefunc(TProtoFunc *f)

{
  (**(code **)(g_dwLuaHS + 0x24))(f->pCode);
  (**(code **)(g_dwLuaHS + 0x24))(f->pLocvars);
  (**(code **)(g_dwLuaHS + 0x24))(f->pConsts);
  (**(code **)(g_dwLuaHS + 0x24))(f);
  return;
}

/* ---- 0x10004cc0  luaF_freeclosure ---- */
/* Original name luaF_freeclosure (the remaster's libLua.so: remaster luaF_freeclosure: walks the
   closure list (rootcl), nblocks--, frees each); was lfunc__4cc0. */

void __cdecl luaF_freeclosure(Closure *l)

{
  Closure *pCVar1;
  
  while (l != (Closure *)0x0) {
    pCVar1 = l->pNext;
    g_dwLState_nblocks = g_dwLState_nblocks + -1;
    (**(code **)(g_dwLuaHS + 0x24))(l);
    l = pCVar1;
  }
  return;
}

/* ---- 0x10004cf0  luaF_getlocalname ---- */
char * __cdecl luaF_getlocalname(TProtoFunc *func,int local_number,int line)

{
  uint uVar1;
  LocVar *pLVar2;
  char *pcVar3;
  LocVar *pLVar4;
  int iVar5;
  
                    /* 0x4cf0  1  luaF_getlocalname */
  iVar5 = 0;
  pcVar3 = (char *)0x0;
  pLVar4 = func->pLocvars;
  if (pLVar4 != (LocVar *)0x0) {
    uVar1 = pLVar4->nLine;
    while ((uVar1 != 0xffffffff && (uVar1 < (uint)line))) {
      if (pLVar4->pVarname == (TaggedString *)0x0) {
        iVar5 = iVar5 + -1;
        if (iVar5 < local_number) {
          pcVar3 = (char *)0x0;
        }
      }
      else {
        iVar5 = iVar5 + 1;
        if (iVar5 == local_number) {
          pcVar3 = pLVar4->pVarname->aStr;
        }
      }
      pLVar2 = pLVar4 + 1;
      pLVar4 = pLVar4 + 1;
      uVar1 = pLVar2->nLine;
    }
    return pcVar3;
  }
  return pcVar3;
}

/* ---- 0x10004d40  luaC_ref ---- */
/* Original name luaC_ref (the remaster's libLua.so: string 'reference table overflow'); was
   lfunc__4d40. */

uint __cdecl luaC_ref(int *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  uVar3 = g_dwLState_refSize;
  if (*param_1 == -7) {
    return 0xffffffff;
  }
  uVar1 = 0;
  if (g_dwLState_refSize != 0) {
    piVar4 = (int *)(g_dwLState_refArray + 8);
    do {
      if (*piVar4 == 2) break;
      uVar1 = uVar1 + 1;
      piVar4 = piVar4 + 3;
    } while (uVar1 < g_dwLState_refSize);
  }
  if ((uVar1 == g_dwLState_refSize) &&
     (g_dwLState_refSize =
           luaM_growaux(&g_dwLState_refArray,g_dwLState_refSize,0xc,
                        (byte *)s_reference_table_overflow_10026ac8,0xfffe), uVar1 = uVar3,
     uVar3 < g_dwLState_refSize)) {
    iVar2 = uVar3 * 0xc;
    do {
      uVar3 = uVar3 + 1;
      *(undefined4 *)(g_dwLState_refArray + 8 + iVar2) = 2;
      iVar2 = iVar2 + 0xc;
    } while (uVar3 < g_dwLState_refSize);
  }
  iVar2 = uVar1 * 0xc;
  *(int *)(g_dwLState_refArray + iVar2) = *param_1;
  *(int *)(g_dwLState_refArray + 4 + iVar2) = param_1[1];
  *(uint *)(g_dwLState_refArray + 8 + iVar2) = (uint)(param_2 == 0);
  return uVar1;
}

/* ---- 0x10004e30  luaC_getref ---- */
/* Original name luaC_getref (the remaster's libLua.so: -1 gives the nil object, otherwise the ref
   record if its status is 0 or 1 (same test)); was lfunc__4e30. */

TObject * __cdecl luaC_getref(int ref)

{
  TObject *pTVar1;
  
  if (ref == -1) {
    return (TObject *)&g_LuaO_nilobject;
  }
  if ((-1 < ref) && ((uint)ref < g_dwLState_refSize)) {
    pTVar1 = (TObject *)(g_dwLState_refArray + ref * 0xc);
    if (pTVar1[1].nTtype == 0) {
      return pTVar1;
    }
    if (pTVar1[1].nTtype == 1) {
      return pTVar1;
    }
  }
  return (TObject *)0x0;
}
