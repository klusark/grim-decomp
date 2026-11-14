/* LUA.DLL :: ltable.c
 * functions 0x1000c190 .. 0x1000c810 (15 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000c190  luaH_free ---- */
/* Original name luaH_free (the remaster's libLua.so: same body: frees a list of tables (nblocks -=
   1 + size / 16), callers lua_close, lua_collectgarbage); was ltable__c190. */

void __cdecl luaH_free(Hash *frees)

{
  Hash *pHVar1;
  
  while (frees != (Hash *)0x0) {
    pHVar1 = frees->pNext;
    g_dwLState_nblocks = g_dwLState_nblocks + (-1 - ((uint)frees->nNhash >> 4));
    freeHash(frees);
    frees = pHVar1;
  }
  return;
}

/* ---- 0x1000c1d0  freeHash ---- */
/* Named freeHash (not in the remaster, gcc inlined it there): Lua 3.1 source name (ltable.c: frees
   the node vector and the table, used by luaH_free); was ltable__c1d0. */

void __cdecl freeHash(Hash *t)

{
  (**(code **)(g_dwLuaHS + 0x24))(t->pNode);
  (**(code **)(g_dwLuaHS + 0x24))(t);
  return;
}

/* ---- 0x1000c200  luaH_save ---- */
/* ltable.c: Grim save-game table writer (asserts writtenItems == numItems) */

void __cdecl luaH_save(undefined *param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int a1;
  int *piVar1;
  int iVar2;
  uint uVar3;
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  uVar3 = 0;
  local_8 = 0;
  local_4 = 0;
  (*(code *)param_1)((int *)(param_2 + 0xc),4);
  iVar2 = *(int *)(param_2 + 0xc);
  if (iVar2 != 0) {
    piVar1 = *(int **)(param_2 + 8);
    do {
      if ((*piVar1 != -7) && (piVar1[2] != -7)) {
        local_8 = local_8 + 1;
      }
      piVar1 = piVar1 + 4;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  (*(code *)param_1)(&local_8,4);
  (*(code *)param_1)(param_2 + 0x14,4);
  if (*(int *)(param_2 + 0xc) != 0) {
    iVar2 = 0;
    do {
      a1 = *(int *)(param_2 + 8) + iVar2;
      if ((*(int *)(*(int *)(param_2 + 8) + iVar2) != -7) && (*(int *)(a1 + 8) != -7)) {
        LState_SaveObject(a1,(int)param_1);
        LState_SaveObject(*(int *)(param_2 + 8) + 8 + iVar2,(int)param_1);
        local_4 = local_4 + 1;
      }
      uVar3 = uVar3 + 1;
      iVar2 = iVar2 + 0x10;
    } while (uVar3 < *(uint *)(param_2 + 0xc));
  }
  if (local_4 != local_8) {
    (**(code **)(g_dwLuaHS + 0x18))
              (s_writtenItems____numItems_10027cd8,s_C__grimsrc_libs_lua_src_ltable_c_10027cf4,0x8a)
    ;
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x1000c2e0  luaH_load ---- */
/* Original name luaH_load (the remaster's libLua.so: luaH_load: callee LoadObject, caller
   GlobalBeginRestore); was luaH_new. */

undefined4 * __cdecl luaH_load(undefined *param_1)

{
  undefined4 *puVar1;
  Node *pNVar2;
  uint uVar3;
  int iVar4;
  
  puVar1 = (undefined4 *)
           (**(code **)(g_dwLuaHS + 0x20))(0x18,s_C__grimsrc_libs_lua_src_ltable_c_10027cf4,0x91);
  (*(code *)param_1)(puVar1 + 3,4);
  (*(code *)param_1)(puVar1 + 4,4);
  (*(code *)param_1)(puVar1 + 5,4);
  pNVar2 = luaH_hashnodecreate(puVar1[3]);
  puVar1[2] = pNVar2;
  luaO_insertlist(&g_dwLState_roottable,puVar1);
  uVar3 = 0;
  if (puVar1[4] != 0) {
    iVar4 = 0;
    do {
      LState_LoadObject(puVar1[2] + iVar4,(int)param_1);
      LState_LoadObject(puVar1[2] + 8 + iVar4,(int)param_1);
      uVar3 = uVar3 + 1;
      iVar4 = iVar4 + 0x10;
    } while (uVar3 < (uint)puVar1[4]);
  }
  return puVar1;
}

/* ---- 0x1000c390  luaH_hashnodecreate ---- */
/* Named luaH_hashnodecreate (not in the remaster: inlined there) Lua 3.1's static
   hashnodecreate(nhash): allocates nhash nodes and sets each key to nil; the name luaH_free belongs
   to 1000c190; was luaH_free. */

Node * __cdecl luaH_hashnodecreate(int nhash)

{
  Node *pNVar1;
  Node *pNVar2;
  
  pNVar1 = (Node *)(**(code **)(g_dwLuaHS + 0x20))
                             (nhash << 4,s_C__grimsrc_libs_lua_src_ltable_c_10027cf4,0x53);
  pNVar2 = pNVar1;
  if (0 < nhash) {
    do {
      (pNVar2->ref).nTtype = -7;
      nhash = nhash + -1;
      pNVar2 = pNVar2 + 1;
    } while (nhash != 0);
  }
  return pNVar1;
}

/* ---- 0x1000c3d0  luaH_new ---- */
/* Original name luaH_new (the remaster's libLua.so: luaH_new: callers lua_createtable, luaV_pack,
   the VM); was luaH_init. */

Hash * __cdecl luaH_new(int nhash)

{
  Hash *pHVar1;
  int nhash_00;
  Node *pNVar2;
  longlong lVar3;
  
  pHVar1 = (Hash *)(**(code **)(g_dwLuaHS + 0x20))
                             (0x18,s_C__grimsrc_libs_lua_src_ltable_c_10027cf4,0xa4);
  lVar3 = FTOL((float10)nhash * (float10)1.4285714285714286);
  nhash_00 = luaO_redimension((int)lVar3);
  pNVar2 = luaH_hashnodecreate(nhash_00);
  pHVar1->pNode = pNVar2;
  pHVar1->nNhash = nhash_00;
  pHVar1->nNuse = 0;
  pHVar1->nHtag = -3;
  luaO_insertlist(&g_dwLState_roottable,(undefined4 *)pHVar1);
  g_dwLState_nblocks = g_dwLState_nblocks + 1 + ((int)(nhash_00 + (nhash_00 >> 0x1f & 0xfU)) >> 4);
  return pHVar1;
}

/* ---- 0x1000c450  luaH_forcerehash ---- */
/* Original name luaH_forcerehash (the remaster's libLua.so: luaH_forcerehash: caller
   GlobalBeginRestore, callee present); was ltable__c450. */

void __cdecl luaH_forcerehash(Hash *t)

{
  Node *pNVar1;
  Node *pNVar2;
  int iVar3;
  Node *pNVar4;
  uint uVar5;
  
  pNVar1 = t->pNode;
  pNVar2 = luaH_hashnodecreate(t->nNhash);
  t->pNode = pNVar2;
  uVar5 = 0;
  pNVar2 = pNVar1;
  if (t->nNuse != 0) {
    do {
      if (((pNVar2->ref).nTtype != -7) && ((pNVar2->val).nTtype != -7)) {
        iVar3 = present(t,&pNVar2->ref);
        pNVar4 = t->pNode + iVar3;
        (pNVar4->ref).nTtype = (pNVar2->ref).nTtype;
        (pNVar4->ref).dwValue = (pNVar2->ref).dwValue;
        (pNVar4->val).nTtype = (pNVar2->val).nTtype;
        (pNVar4->val).dwValue = (pNVar2->val).dwValue;
      }
      uVar5 = uVar5 + 1;
      pNVar2 = pNVar2 + 1;
    } while (uVar5 < (uint)t->nNuse);
  }
  (**(code **)(g_dwLuaHS + 0x24))(pNVar1);
  return;
}

/* ---- 0x1000c4d0  present ---- */
/* Original name present (the remaster's libLua.so: static present(Hash*, TObject*): callers
   luaH_get / luaH_set / luaH_next / luaH_forcerehash); was luaH_present. */

int __cdecl present(Hash *t,TObject *key)

{
  int iVar1;
  int iVar2;
  int iVar3;
  TObject *t2;
  int iVar4;
  int iVar5;
  
  iVar1 = t->nNhash;
  iVar2 = hashindex(key);
  iVar4 = iVar2 % iVar1;
  iVar5 = iVar4 * 0x10;
  if ((t->pNode[iVar4].ref.nTtype != -7) &&
     (iVar3 = luaO_equalObj(key,&t->pNode[iVar4].ref), iVar3 == 0)) {
    iVar2 = iVar2 % (iVar1 + -2) + 1;
    do {
      iVar4 = iVar4 + iVar2;
      iVar5 = iVar5 + iVar2 * 0x10;
      if (iVar1 <= iVar4) {
        iVar4 = iVar4 - iVar1;
        iVar5 = iVar5 + iVar1 * -0x10;
      }
      t2 = (TObject *)((int)&(t->pNode->ref).nTtype + iVar5);
    } while ((t2->nTtype != -7) && (iVar3 = luaO_equalObj(key,t2), iVar3 == 0));
  }
  return iVar4;
}

/* ---- 0x1000c580  hashindex ---- */
/* Named hashindex (not in the remaster, gcc inlined it there): Lua 3.1 source name (ltable.c static
   hashindex: the key's hash by type, error "unexpected type to index table", negative values
   mirrored); was luaH_hashindex. */

int __cdecl hashindex(TObject *ref)

{
  uint uVar1;
  longlong lVar2;
  
  switch(ref->nTtype) {
  case -8:
  case -5:
  case -4:
  case -3:
  case -2:
  case 0:
    uVar1 = ref->dwValue;
    break;
  default:
    lua_error((byte *)s_unexpected_type_to_index_table_10027d18);
    uVar1 = 0;
    break;
  case -6:
  case -1:
    lVar2 = FTOL((float10)PUN(float,ref->dwValue));
    uVar1 = (uint)lVar2;
  }
  if (-1 < (int)uVar1) {
    return uVar1;
  }
  return -1 - uVar1;
}

/* ---- 0x1000c5f0  luaH_get ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

TObject * __cdecl luaH_get(Hash *t,TObject *ref)

{
  int iVar1;
  
  iVar1 = present(t,ref);
  if (t->pNode[iVar1].ref.nTtype != -7) {
    return &t->pNode[iVar1].val;
  }
  return (TObject *)0x0;
}

/* ---- 0x1000c620  luaH_set ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

TObject * __cdecl luaH_set(Hash *t,TObject *ref)

{
  int iVar1;
  uint uVar2;
  Node *pNVar3;
  
  iVar1 = present(t,ref);
  pNVar3 = t->pNode + iVar1;
  if ((pNVar3->ref).nTtype == -7) {
    uVar2 = t->nNuse + 1;
    t->nNuse = uVar2;
    if ((double)(uint)t->nNhash * 0.7 < (double)uVar2) {
      rehash(t);
      iVar1 = present(t,ref);
      pNVar3 = t->pNode + iVar1;
    }
    (pNVar3->ref).nTtype = ref->nTtype;
    (pNVar3->ref).dwValue = ref->dwValue;
    (pNVar3->val).nTtype = -7;
  }
  return &pNVar3->val;
}

/* ---- 0x1000c6b0  rehash ---- */
/* Named rehash (not in the remaster, gcc inlined it there): Lua 3.1 source name (ltable.c static
   rehash: grows by luaO_redimension unless emptyslots, hashnodecreate, re-inserts the live nodes
   with present, nblocks adjusted); was luaH_rehash. */

void __cdecl rehash(Hash *t)

{
  int iVar1;
  Node *pNVar2;
  int iVar3;
  Node *pNVar4;
  int iVar5;
  Node *pNVar6;
  
  iVar1 = t->nNhash;
  pNVar2 = t->pNode;
  iVar3 = emptyslots(t);
  if (iVar3 == 0) {
    iVar3 = luaO_redimension(t->nNhash);
    t->nNhash = iVar3;
  }
  pNVar4 = luaH_hashnodecreate(t->nNhash);
  t->pNode = pNVar4;
  iVar3 = iVar1;
  pNVar4 = pNVar2;
  if (0 < iVar1) {
    do {
      if (((pNVar4->ref).nTtype != -7) && ((pNVar4->val).nTtype != -7)) {
        iVar5 = present(t,&pNVar4->ref);
        pNVar6 = t->pNode + iVar5;
        (pNVar6->ref).nTtype = (pNVar4->ref).nTtype;
        (pNVar6->ref).dwValue = (pNVar4->ref).dwValue;
        (pNVar6->val).nTtype = (pNVar4->val).nTtype;
        (pNVar6->val).dwValue = (pNVar4->val).dwValue;
      }
      iVar3 = iVar3 + -1;
      pNVar4 = pNVar4 + 1;
    } while (iVar3 != 0);
  }
  g_dwLState_nblocks =
       g_dwLState_nblocks + (((uint)t->nNhash >> 4) - ((int)(iVar1 + (iVar1 >> 0x1f & 0xfU)) >> 4));
  (**(code **)(g_dwLuaHS + 0x24))(pNVar2);
  return;
}

/* ---- 0x1000c770  emptyslots ---- */
/* Named emptyslots (not in the remaster, gcc inlined it there): Lua 3.1 source name (ltable.c
   static emptyslots: 1 when a node has a key and a nil value (a deleted slot rehash can reuse));
   was luaH_nuse. */

int __cdecl emptyslots(Hash *t)

{
  Node *pNVar1;
  int iVar2;
  
  iVar2 = t->nNhash + -1;
  if (iVar2 < 0) {
    return 0;
  }
  pNVar1 = t->pNode + iVar2;
  while (((pNVar1->ref).nTtype == -7 || ((pNVar1->val).nTtype != -7))) {
    iVar2 = iVar2 + -1;
    pNVar1 = pNVar1 + -1;
    if (iVar2 < 0) {
      return 0;
    }
  }
  return 1;
}

/* ---- 0x1000c7b0  luaH_next ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

Node * __cdecl luaH_next(TObject *o,TObject *r)

{
  Hash *t;
  Node *pNVar1;
  int iVar2;
  
  t = (Hash *)o->dwValue;
  if (r->nTtype == -7) {
    pNVar1 = hashnext(t,0);
    return pNVar1;
  }
  iVar2 = present(t,r);
  if ((t->pNode[iVar2].ref.nTtype == -7) || (t->pNode[iVar2].val.nTtype == -7)) {
    luaL_argerror(2,((unsigned)(uintptr_t)&s_key_not_found_10027d38));
  }
  pNVar1 = hashnext(t,iVar2 + 1);
  return pNVar1;
}

/* ---- 0x1000c810  hashnext ---- */
/* Named hashnext (not in the remaster, gcc inlined it there): Lua 3.1 source name (ltable.c: the
   next node with non-nil key and value, used by luaH_next); was ltable__c810. */

Node * __cdecl hashnext(Hash *t,int i)

{
  Node *pNVar1;
  
  if (i < t->nNhash) {
    pNVar1 = t->pNode + i;
    do {
      if (((pNVar1->ref).nTtype != -7) && ((pNVar1->val).nTtype != -7)) {
        return t->pNode + i;
      }
      i = i + 1;
      pNVar1 = pNVar1 + 1;
    } while (i < t->nNhash);
  }
  return (Node *)0x0;
}
