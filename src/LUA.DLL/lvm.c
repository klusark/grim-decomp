/* LUA.DLL :: lvm.c
 * functions 0x1000d6d0 .. 0x1000ed10 (22 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000d6d0  luaV_closure ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_closure(uint param_1)

{
  int *piVar1;
  Closure *pCVar2;
  int iVar3;
  undefined4 *puVar4;
  Closure *pCVar5;
  
  if (0 < (int)param_1) {
    piVar1 = g_pLuaState + 7;
    pCVar2 = luaF_newclosure(param_1);
    iVar3 = *piVar1;
    pCVar2->aConsts[0].nTtype = *(int *)(iVar3 + -8);
    pCVar2->aConsts[0].dwValue = *(uint *)(iVar3 + -4);
    puVar4 = (undefined4 *)(*piVar1 - (param_1 * 8 + 8));
    pCVar5 = pCVar2 + 1;
    for (iVar3 = (param_1 & 0x1fffffff) << 1; iVar3 != 0; iVar3 = iVar3 + -1) {
      pCVar5->pNext = (Closure *)*puVar4;
      puVar4 = puVar4 + 1;
      pCVar5 = (Closure *)&pCVar5->nMarked;
    }
    for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)&pCVar5->pNext = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      pCVar5 = (Closure *)((int)&pCVar5->pNext + 1);
    }
    iVar3 = *piVar1 + param_1 * -8;
    *piVar1 = iVar3;
    *(undefined4 *)(iVar3 + -8) = 0xfffffff8;
    *(Closure **)(*piVar1 + -4) = pCVar2;
  }
  return;
}

/* ---- 0x1000d740  luaV_gettable ---- */
/* Unidentified function of lvm.c (virtual machine) */

void luaV_gettable(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  TObject *pTVar4;
  
  iVar3 = g_pLuaState[7];
  piVar1 = g_pLuaState + 7;
  if (*(int *)(iVar3 + -0x10) == -3) {
    iVar2 = (*(Hash **)(iVar3 + -0xc))->nHtag;
    pTVar4 = (TObject *)(g_dwLState_IMtable + iVar2 * -0x90);
    if (pTVar4->nTtype == -7) {
      pTVar4 = luaH_get(*(Hash **)(iVar3 + -0xc),(TObject *)(iVar3 + -8));
      if ((pTVar4 != (TObject *)0x0) && (pTVar4->nTtype != -7)) {
        iVar3 = *piVar1;
        *piVar1 = iVar3 + -8;
        *(int *)(iVar3 + -0x10) = pTVar4->nTtype;
        *(uint *)(iVar3 + -0xc) = pTVar4->dwValue;
        return;
      }
      pTVar4 = (TObject *)(g_dwLState_IMtable + iVar2 * -0x90 + 0x10);
      if (pTVar4->nTtype != -7) {
        luaD_callTM(pTVar4,2,1);
        return;
      }
      iVar3 = *piVar1;
      *piVar1 = iVar3 + -8;
      *(undefined4 *)(iVar3 + -0x10) = 0xfffffff9;
      return;
    }
  }
  else {
    iVar3 = luaT_efectivetag((TObject *)(iVar3 + -0x10));
    pTVar4 = (TObject *)(g_dwLState_IMtable + iVar3 * -0x90);
  }
  if (pTVar4->nTtype != -7) {
    luaD_callTM(pTVar4,2,1);
    return;
  }
  lua_error((byte *)s_indexed_expression_not_a_table_10028180);
  return;
}

/* ---- 0x1000d810  luaV_settable ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_settable(TObject *t,int mode)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  TObject *pTVar4;
  int iVar5;
  
  piVar1 = g_pLuaState + 7;
  if (mode == 0) {
    pTVar4 = (TObject *)0x0;
  }
  else {
    iVar5 = luaT_efectivetag(t);
    pTVar4 = (TObject *)(g_dwLState_IMtable + iVar5 * -0x90 + 8);
  }
  if ((t->nTtype == -3) && ((pTVar4 == (TObject *)0x0 || (pTVar4->nTtype == -7)))) {
    pTVar4 = luaH_set((Hash *)t->dwValue,t + 1);
    iVar5 = *piVar1;
    pTVar4->nTtype = *(int *)(iVar5 + -8);
    pTVar4->dwValue = *(uint *)(iVar5 + -4);
    *piVar1 = *piVar1 + ((-(uint)(mode != 2) & 2) + 1) * -8;
    return;
  }
  if ((pTVar4 != (TObject *)0x0) && (pTVar4->nTtype != -7)) {
    if (mode == 2) {
      iVar5 = g_pLuaState[7];
      iVar2 = *piVar1;
      *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(iVar5 + -8);
      *(undefined4 *)(iVar2 + 0xc) = *(undefined4 *)(iVar5 + -4);
      piVar3 = (int *)*piVar1;
      *piVar3 = t[1].nTtype;
      piVar3[1] = t[1].dwValue;
      iVar5 = *piVar1;
      *(int *)(iVar5 + -8) = t->nTtype;
      *(uint *)(iVar5 + -4) = t->dwValue;
      *piVar1 = *piVar1 + 0x10;
    }
    luaD_callTM(pTVar4,3,0);
    return;
  }
  lua_error((byte *)s_indexed_expression_not_a_table_10028180);
  return;
}

/* ---- 0x1000d900  luaV_getglobal ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_getglobal(TaggedString *ts)

{
  TObject *o;
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  o = &ts->globalval;
  iVar3 = luaT_efectivetag(o);
  iVar3 = g_dwLState_IMtable + iVar3 * -0x90;
  if (*(int *)(iVar3 + 0x18) == -7) {
    piVar1 = (int *)g_pLuaState[7];
    *piVar1 = o->nTtype;
    piVar1[1] = (ts->globalval).dwValue;
    g_pLuaState[7] = g_pLuaState[7] + 8;
    return;
  }
  piVar1 = g_pLuaState + 7;
  *(undefined4 *)g_pLuaState[7] = 0xfffffffe;
  *(TaggedString **)(*piVar1 + 4) = ts;
  iVar2 = *piVar1;
  piVar4 = (int *)(iVar2 + 8);
  *piVar1 = (int)piVar4;
  *piVar4 = o->nTtype;
  *(uint *)(iVar2 + 0xc) = (ts->globalval).dwValue;
  *piVar1 = *piVar1 + 8;
  luaD_callTM((TObject *)(iVar3 + 0x18),2,1);
  return;
}

/* ---- 0x1000d990  luaV_setglobal ---- */
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_setglobal(TaggedString *ts)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  undefined4 *puVar7;
  
  iVar5 = luaT_efectivetag(&ts->globalval);
  iVar5 = g_dwLState_IMtable + iVar5 * -0x90;
  if (*(int *)(iVar5 + 0x20) == -7) {
    g_pLuaState[7] = g_pLuaState[7] + -8;
    luaS_rawsetglobal(ts,(TObject *)g_pLuaState[7]);
    return;
  }
  piVar6 = g_pLuaState + 7;
  iVar1 = *piVar6;
  uVar2 = *(undefined4 *)(iVar1 + -8);
  uVar3 = *(undefined4 *)(iVar1 + -4);
  *(undefined4 *)(iVar1 + -8) = 0xfffffffe;
  *(TaggedString **)(*piVar6 + -4) = ts;
  piVar4 = (int *)*piVar6;
  *piVar4 = (ts->globalval).nTtype;
  piVar4[1] = (ts->globalval).dwValue;
  iVar1 = *piVar6;
  puVar7 = (undefined4 *)(iVar1 + 8);
  *piVar6 = (int)puVar7;
  *puVar7 = uVar2;
  *(undefined4 *)(iVar1 + 0xc) = uVar3;
  *piVar6 = *piVar6 + 8;
  luaD_callTM((TObject *)(iVar5 + 0x20),3,0);
  return;
}

/* ---- 0x1000da30  luaV_pack ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of lvm.c (virtual machine) */

void __cdecl luaV_pack(int firstel,int nvararg,TObject *tab)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  Hash *pHVar3;
  TObject *pTVar4;
  int *piVar5;
  #define local_10 (*(TObject *)(_frame + (0x20 - 0x10)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  piVar5 = (int *)(g_pLuaState[8] + firstel * 8);
  if (nvararg < 0) {
    nvararg = 0;
  }
  pHVar3 = luaH_new(nvararg + 1);
  tab->dwValue = (uint)pHVar3;
  tab->nTtype = -3;
  firstel = 0;
  if (0 < nvararg) {
    do {
      iVar1 = *piVar5;
      local_10.dwValue = PUN(uint,(float)((float)firstel - -1.0));
      uVar2 = piVar5[1];
      local_10.nTtype = -1;
      pTVar4 = luaH_set((Hash *)tab->dwValue,&local_10);
      pTVar4->nTtype = iVar1;
      firstel = firstel + 1;
      piVar5 = piVar5 + 2;
      pTVar4->dwValue = uVar2;
    } while (firstel < nvararg);
  }
  local_10.nTtype = -2;
  local_10.dwValue = (uint)luaS_new(&DAT_10026994);
  local_4 = (float)nvararg;
  pTVar4 = luaH_set((Hash *)tab->dwValue,&local_10);
  pTVar4->nTtype = -1;
  pTVar4->dwValue = PUN(uint,(float)local_4);
  return;
}
#undef local_10
#undef local_4

#endif


/* ---- 0x1000db10  ExecutionState_CleanUp ---- */
/* Original name ExecutionState_CleanUp (the remaster's libLua.so: ExecutionState::CleanUp: frees
   the free list of states (same body)); was lvm__db10. */

void ExecutionState_CleanUp(void)

{
  void *pvVar1;
  
  if (g_pExecutionState_pFreeStates != (void *)0x0) {
    do {
      pvVar1 = *(void **)((int)g_pExecutionState_pFreeStates + 0xc);
      luaM_free(g_pExecutionState_pFreeStates);
      g_pExecutionState_pFreeStates = pvVar1;
    } while (pvVar1 != (void *)0x0);
    g_pExecutionState_pFreeStates = (void *)0x0;
  }
  return;
}

/* ---- 0x1000db40  ExecutionState_Save ---- */
/* Original name ExecutionState_Save (the remaster's libLua.so: ExecutionState::Save(writer): the
   previous state first (+0xc), then the fields (caller LState::Save)); was lvm__db40. */

undefined4 __thiscall ExecutionState_Save(void *this,int a1)

{
  int iVar1;
  
  iVar1 = a1;
  if (*(void **)((int)this + 0xc) != (void *)0x0) {
    ExecutionState_Save(*(void **)((int)this + 0xc),a1);
  }
  (*(code *)iVar1)(this,4);
  (*(code *)iVar1)((int *)((int)this + 4),4);
  (*(code *)iVar1)((int)this + 8,4);
  (*(code *)iVar1)((int)this + 0x10,4);
  (*(code *)iVar1)((int)this + 0x14,4);
  (*(code *)iVar1)((int)this + 0x18,4);
  a1 = *(int *)((int)this + 0x20) - *(int *)(*(int *)((int)this + 4) + 0x10);
  (*(code *)iVar1)(&a1,4);
  (*(code *)iVar1)((int)this + 0x24,4);
  return 0;
}

/* ---- 0x1000dbd0  ExecutionState_Restore ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name ExecutionState_Restore (the remaster's libLua.so: ExecutionState::Restore: caller
   LState::Restore, callees ResolveObject, new); was lvm__dbd0. */

undefined4 __thiscall ExecutionState_Restore(void *this,int a1,int a2,int a3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *pvVar2;
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(undefined4 *)(_frame + (0x30 - 0x10)))
  
  iVar1 = a3;
  if (a3 != 0) {
    pvVar2 = ExecutionState_New(0x30);
    if (pvVar2 == (void *)0x0) {
      pvVar2 = (void *)0x0;
    }
    else {
      pvVar2 = (void *)ExecutionState_Construct(pvVar2,0,0,0);
    }
    *(void **)((int)this + 0xc) = pvVar2;
    ExecutionState_Restore(pvVar2,a1,a2,iVar1 + -1);
  }
  *(int *)((int)this + 0x1c) = a2;
  local_14 = 0xfffffff8;
  (*(code *)a1)(&local_10,4);
  LState_ResolveObject((int)&local_14);
  *(undefined4 *)this = local_10;
  local_14 = 0xfffffffc;
  (*(code *)a1)(&local_10,4);
  LState_ResolveObject((int)&local_14);
  *(undefined4 *)((int)this + 4) = local_10;
  (*(code *)a1)((int)this + 8,4);
  (*(code *)a1)((int)this + 0x10,4);
  (*(code *)a1)((int)this + 0x14,4);
  (*(code *)a1)((int)this + 0x18,4);
  (*(code *)a1)(&a3,4);
  *(int *)((int)this + 0x20) = *(int *)(*(int *)((int)this + 4) + 0x10) + a3;
  (*(code *)a1)((int)this + 0x24,4);
  *(undefined4 *)((int)this + 0x2c) = *(undefined4 *)(*(int *)((int)this + 4) + 8);
  return 0;
}
#undef local_10
#undef local_14

#endif


/* ---- 0x1000dd10  ExecutionState_New ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name ExecutionState_New (the remaster's libLua.so: ExecutionState::operator new: takes a
   state from the free list or allocates one); was lvm__dd10. */

void * __cdecl ExecutionState_New(int size)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  int iVar2;
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  pvVar1 = g_pExecutionState_pFreeStates;
  if (g_pExecutionState_pFreeStates == (void *)0x0) {
    iVar2 = 10;
    do {
      local_4 = 0xffffffff;
      pvVar1 = luaM_malloc(0x30);
      local_4 = 0;
      if (pvVar1 == (void *)0x0) {
        pvVar1 = (void *)0x0;
      }
      else {
        pvVar1 = (void *)ExecutionState_Construct(pvVar1,(int)g_pExecutionState_pFreeStates,0,0);
      }
      iVar2 = iVar2 + -1;
      g_pExecutionState_pFreeStates = pvVar1;
    } while (iVar2 != 0);
  }
  g_pExecutionState_pFreeStates = *(void **)((int)pvVar1 + 0xc);
  return pvVar1;
}
#undef local_4

#endif


/* ---- 0x1000dd90  ExecutionState_Delete ---- */
/* Original name ExecutionState_Delete (the remaster's libLua.so: ExecutionState::operator delete:
   puts the state on the free list (+0xc)); was lvm__dd90. */

void __cdecl ExecutionState_Delete(int param_1)

{
  *(void **)(param_1 + 0xc) = g_pExecutionState_pFreeStates;
  g_pExecutionState_pFreeStates = (void *)param_1;
  return;
}

/* ---- 0x1000ddb0  ExecutionState_Construct ---- */
/* Original name ExecutionState_Construct (the remaster's libLua.so:
   ExecutionState::ExecutionState(ExecutionState*, int, int): +0xc, +0x10, +0x14, clears +0x18 /
   +0x28 (same body)); was lvm__ddb0. */

int __thiscall ExecutionState_Construct(void *this,int a1,int a2,int a3)

{
  *(int *)((int)this + 0xc) = a1;
  *(int *)((int)this + 0x10) = a2;
  *(undefined4 *)((int)this + 0x28) = 0;
  *(int *)((int)this + 0x14) = a3;
  *(undefined4 *)((int)this + 0x18) = 0;
  return (int)this;
}

/* ---- 0x1000dde0  ExecutionState_getaux ---- */
/* Original name ExecutionState_getaux (the remaster's libLua.so: ExecutionState::getaux: returns
   +0x24); was lvm__dde0. */

undefined4 __fastcall ExecutionState_getaux(int param_1)

{
  return *(undefined4 *)(param_1 + 0x24);
}

/* ---- 0x1000ddf0  ExecutionState_setvalues ---- */
/* Original name ExecutionState_setvalues (the remaster's libLua.so:
   ExecutionState::setvalues(Closure*, TProtoFunc*, int) (same body)); was lvm__ddf0. */

int __thiscall ExecutionState_setvalues(void *this,int a1,int a2,int a3)

{
  int iVar1;
  
  *(int *)this = a1;
  *(int *)((int)this + 4) = a2;
  *(int *)((int)this + 8) = a3;
  *(undefined4 *)((int)this + 0x20) = *(undefined4 *)(a2 + 0x10);
  iVar1 = *(int *)(a2 + 8);
  *(int *)((int)this + 0x2c) = iVar1;
  *(int **)((int)this + 0x1c) = g_pLuaState + 7;
  return iVar1;
}

/* ---- 0x1000de20  ExecutionState_resetcounter ---- */
/* Original name ExecutionState_resetcounter (the remaster's libLua.so:
   ExecutionState::resetcounter: +0x28 = 0); was lvm__de20. */

void __fastcall ExecutionState_resetcounter(int param_1)

{
  *(undefined4 *)(param_1 + 0x28) = 0;
  return;
}

/* ---- 0x1000de30  ExecutionState_execute ---- */
/* Original name ExecutionState_execute (the remaster's libLua.so: ExecutionState::execute:
   checkstack, adjust varargs, call hook, CrunchOpcodes (caller luaD_call)); was lvm__de30. */

int __fastcall ExecutionState_execute(int *param_1)

{
  byte bVar1;
  int iVar2;
  
  if (param_1[6] == 0) {
    ExecutionState_resetcounter((int)param_1);
    if (lua_callhook != 0) {
      luaD_callHook(param_1[2],param_1[1],0);
    }
    bVar1 = *(byte *)param_1[8];
    param_1[8] = (int)((byte *)param_1[8] + 1);
    luaD_checkstack(bVar1 + 5);
    bVar1 = *(byte *)param_1[8];
    if (bVar1 < 0x40) {
      param_1[8] = (int)((byte *)param_1[8] + 1);
      luaD_adjusttop(param_1[2] + (uint)bVar1);
      param_1[6] = 1;
      iVar2 = ExecutionState_CrunchOpcodes(param_1);
      return iVar2;
    }
    luaC_checkGC();
    bVar1 = *(byte *)param_1[8];
    param_1[8] = (int)((byte *)param_1[8] + 1);
    adjust_varargs(param_1[2] + -0x40 + (uint)bVar1);
    param_1[6] = 1;
  }
  iVar2 = ExecutionState_CrunchOpcodes(param_1);
  return iVar2;
}

/* ---- 0x1000dee0  adjust_varargs ---- */
/* Named adjust_varargs (not in the remaster, gcc inlined it there): Lua 3.1 source name (lvm.c
   static adjust_varargs: luaV_pack of the extra arguments into a table, luaD_adjusttop, push the
   table); was luaV_adjust_varargs. */

void __cdecl adjust_varargs(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  #define local_8 (*(TObject *)(_frame + (0x20 - 0x8)))
  
  luaV_pack(param_1,(g_pLuaState[7] - g_pLuaState[8] >> 3) - param_1,&local_8);
  luaD_adjusttop(param_1);
  piVar1 = (int *)g_pLuaState[7];
  *piVar1 = local_8.nTtype;
  piVar1[1] = local_8.dwValue;
  g_pLuaState[7] = g_pLuaState[7] + 8;
  return;
}
#undef local_8


/* ---- 0x1000df40  ExecutionState_CrunchOpcodes ---- */
/* lvm.c: opcode interpreter loop Original name ExecutionState_CrunchOpcodes (the remaster's
   libLua.so: ExecutionState::CrunchOpcodes, the VM loop: strings 'WARNING: Killing Lua script that
   ran without a break_here() ...', 'WARNING: Lua nesting level now %d inside breakable section!');
   was luaV_execute. */

int __fastcall ExecutionState_CrunchOpcodes(int *param_1)

{
  byte bVar1;
  byte *pbVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  TObject *pTVar9;
  Hash *pHVar10;
  int iVar11;
  undefined4 uVar12;
  int *piVar13;
  int iVar14;
  int *piVar15;
  uint uVar16;
  
  if ((g_pLuaState[6] != 0) && (g_pLuaState[2] == 0)) {
    printf(s_WARNING__Lua_nesting_level_now___1002821c,g_pLuaState[6]);
  }
  g_pLuaState[6] = g_pLuaState[6] + 1;
switchD_1000dfaf_default:
  iVar14 = param_1[10];
  param_1[10] = iVar14 + 1;
  if (9999999 < iVar14) {
    lua_error((byte *)s_WARNING__Killing_Lua_script_that_100281c4);
  }
  pbVar2 = (byte *)param_1[8];
  bVar1 = *pbVar2;
  pbVar8 = pbVar2 + 1;
  param_1[9] = (uint)bVar1;
  param_1[8] = (int)pbVar8;
  switch((uint)bVar1) {
  case 0:
    goto switchD_1000dfaf_caseD_0;
  case 1:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    do {
      **(undefined4 **)param_1[7] = 0xfffffff9;
      *(int *)param_1[7] = *(int *)param_1[7] + 8;
      iVar14 = param_1[9];
      param_1[9] = iVar14 + -1;
    } while (iVar14 != 0);
    goto switchD_1000dfaf_default;
  case 2:
    **(undefined4 **)param_1[7] = 0xfffffff9;
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    goto switchD_1000dfaf_default;
  case 3:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    break;
  case 4:
  case 5:
  case 6:
    param_1[9] = param_1[9] + -4;
    break;
  case 7:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
    break;
  case 8:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e1a7;
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
    param_1[9] = param_1[9] + -9;
    goto LAB_1000e1a7;
  case 0x11:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e1a7:
    iVar14 = param_1[9];
    iVar11 = param_1[0xb];
    puVar4 = *(undefined4 **)param_1[7];
    *puVar4 = *(undefined4 *)(iVar11 + iVar14 * 8);
    puVar4[1] = *(undefined4 *)(iVar11 + 4 + iVar14 * 8);
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    goto switchD_1000dfaf_default;
  case 0x12:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e1da;
  case 0x13:
  case 0x14:
    param_1[9] = param_1[9] + -0x13;
LAB_1000e1da:
    iVar14 = param_1[9];
    iVar11 = *param_1;
    puVar4 = *(undefined4 **)param_1[7];
    *puVar4 = *(undefined4 *)(iVar11 + 0x14 + iVar14 * 8);
    puVar4[1] = *(undefined4 *)(iVar11 + 0x18 + iVar14 * 8);
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    goto switchD_1000dfaf_default;
  case 0x15:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e058;
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
    param_1[9] = param_1[9] + -0x16;
LAB_1000e058:
    iVar14 = param_1[2];
    iVar11 = param_1[9];
    iVar6 = ((int *)param_1[7])[1];
    puVar4 = *(undefined4 **)param_1[7];
    *puVar4 = *(undefined4 *)(iVar6 + (iVar14 + iVar11) * 8);
    puVar4[1] = *(undefined4 *)(iVar6 + 4 + (iVar14 + iVar11) * 8);
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    goto switchD_1000dfaf_default;
  case 0x1e:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e0aa;
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
    param_1[9] = param_1[9] + -0x1f;
    goto LAB_1000e0aa;
  case 0x27:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e0aa:
    luaV_getglobal(*(TaggedString **)(param_1[0xb] + 4 + param_1[9] * 8));
    goto switchD_1000dfaf_default;
  case 0x28:
    goto switchD_1000dfaf_caseD_28;
  case 0x29:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e0ed;
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
  case 0x31:
    param_1[9] = param_1[9] + -0x2a;
    goto LAB_1000e0ed;
  case 0x32:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e0ed:
    iVar14 = param_1[9];
    iVar11 = param_1[0xb];
    puVar4 = *(undefined4 **)param_1[7];
    *puVar4 = *(undefined4 *)(iVar11 + iVar14 * 8);
    puVar4[1] = *(undefined4 *)(iVar11 + 4 + iVar14 * 8);
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
switchD_1000dfaf_caseD_28:
    luaV_gettable();
    goto switchD_1000dfaf_default;
  case 0x33:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e13f;
  case 0x34:
  case 0x35:
  case 0x36:
  case 0x37:
  case 0x38:
  case 0x39:
  case 0x3a:
  case 0x3b:
    param_1[9] = param_1[9] + -0x34;
    goto LAB_1000e13f;
  case 0x3c:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e13f:
    iVar14 = param_1[9];
    puVar4 = *(undefined4 **)param_1[7];
    iVar11 = param_1[0xb];
    uVar12 = puVar4[-2];
    uVar3 = puVar4[-1];
    *puVar4 = *(undefined4 *)(iVar11 + iVar14 * 8);
    puVar4[1] = *(undefined4 *)(iVar11 + 4 + iVar14 * 8);
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    luaV_gettable();
    puVar4 = *(undefined4 **)param_1[7];
    *puVar4 = uVar12;
    puVar4[1] = uVar3;
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    goto switchD_1000dfaf_default;
  case 0x3d:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e420;
  case 0x3e:
  case 0x3f:
    param_1[9] = param_1[9] + -0x3e;
    goto LAB_1000e420;
  case 0x40:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e420:
    luaC_checkGC();
    pHVar10 = luaH_new(param_1[9]);
    *(Hash **)(*(int *)param_1[7] + 4) = pHVar10;
    **(undefined4 **)param_1[7] = 0xfffffffd;
    *(int *)param_1[7] = *(int *)param_1[7] + 8;
    goto switchD_1000dfaf_default;
  case 0x41:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e20d;
  case 0x42:
  case 0x43:
  case 0x44:
  case 0x45:
  case 0x46:
  case 0x47:
  case 0x48:
  case 0x49:
    param_1[9] = param_1[9] + -0x42;
LAB_1000e20d:
    *(int *)param_1[7] = *(int *)param_1[7] + -8;
    iVar14 = param_1[2];
    iVar11 = param_1[9];
    puVar4 = *(undefined4 **)param_1[7];
    iVar6 = ((int *)param_1[7])[1];
    *(undefined4 *)(iVar6 + (iVar14 + iVar11) * 8) = *puVar4;
    *(undefined4 *)(iVar6 + 4 + (iVar14 + iVar11) * 8) = puVar4[1];
    goto switchD_1000dfaf_default;
  case 0x4a:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e263;
  case 0x4b:
  case 0x4c:
  case 0x4d:
  case 0x4e:
  case 0x4f:
  case 0x50:
  case 0x51:
  case 0x52:
    param_1[9] = param_1[9] + -0x4b;
    goto LAB_1000e263;
  case 0x53:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e263:
    luaV_setglobal(*(TaggedString **)(param_1[0xb] + 4 + param_1[9] * 8));
    goto switchD_1000dfaf_default;
  case 0x54:
    luaV_settable((TObject *)(*(int *)param_1[7] + -0x18),1);
    goto switchD_1000dfaf_default;
  case 0x55:
    bVar1 = *pbVar8;
    iVar14 = *(int *)param_1[7];
    param_1[8] = (int)(pbVar2 + 2);
    luaV_settable((TObject *)(iVar14 - ((uint)bVar1 * 8 + 0x18)),2);
    goto switchD_1000dfaf_default;
  case 0x56:
    param_1[9] = (uint)*pbVar8 << 6;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e2ed;
  case 0x57:
    param_1[9] = 0;
    goto LAB_1000e2ed;
  case 0x58:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = ((uint)pbVar2[1] + (uint)pbVar2[2] * 0x100) * 0x40;
LAB_1000e2ed:
    uVar16 = (uint)*(byte *)param_1[8];
    param_1[8] = (int)((byte *)param_1[8] + 1);
    iVar11 = *(int *)param_1[7];
    iVar14 = uVar16 * 8;
    for (; uVar16 != 0; uVar16 = uVar16 - 1) {
      **(undefined4 **)param_1[7] = 0xffffffff;
      *(float *)(*(int *)param_1[7] + 4) = (float)(int)uVar16 + (float)param_1[9];
      pTVar9 = *(TObject **)param_1[7];
      iVar6 = pTVar9[-1].nTtype;
      uVar5 = pTVar9[-1].dwValue;
      pTVar9 = luaH_set(*(Hash **)((iVar11 - (iVar14 + 8)) + 4),pTVar9);
      pTVar9->nTtype = iVar6;
      pTVar9->dwValue = uVar5;
      *(int *)param_1[7] = *(int *)param_1[7] + -8;
    }
    goto switchD_1000dfaf_default;
  case 0x59:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e37f;
  case 0x5a:
    param_1[9] = 0;
LAB_1000e37f:
    iVar14 = param_1[9];
    iVar11 = *(int *)param_1[7];
    do {
      iVar6 = *(int *)param_1[7];
      iVar7 = *(int *)(iVar6 + -8);
      uVar16 = *(uint *)(iVar6 + -4);
      pTVar9 = luaH_set(*(Hash **)(iVar11 + iVar14 * -0x10 + -0x14),(TObject *)(iVar6 + -0x10));
      pTVar9->nTtype = iVar7;
      pTVar9->dwValue = uVar16;
      *(int *)param_1[7] = *(int *)param_1[7] + -0x10;
      iVar6 = param_1[9];
      param_1[9] = iVar6 + -1;
    } while (iVar6 != 0);
    goto switchD_1000dfaf_default;
  case 0x5b:
  case 0x5c:
    uVar16 = luaO_equalObj((TObject *)(*(int *)param_1[7] + -0x10),
                           (TObject *)(*(int *)param_1[7] + -8));
    *(int *)param_1[7] = *(int *)param_1[7] + -8;
    if (param_1[9] == 0x5c) {
      uVar16 = (uint)(uVar16 == 0);
    }
    *(uint *)(*(int *)param_1[7] + -8) = (-(uint)(uVar16 != 0) & 6) - 7;
    *(undefined4 *)(*(int *)param_1[7] + -4) = 0x3f800000;
    goto switchD_1000dfaf_default;
  case 0x5d:
    comparison(0xffffffff,0xfffffff9,0xfffffff9,0xb);
    goto switchD_1000dfaf_default;
  case 0x5e:
    comparison(0xffffffff,0xffffffff,0xfffffff9,0xc);
    goto switchD_1000dfaf_default;
  case 0x5f:
    comparison(0xfffffff9,0xfffffff9,0xffffffff,0xd);
    goto switchD_1000dfaf_default;
  case 0x60:
    comparison(0xfffffff9,0xffffffff,0xffffffff,0xe);
    goto switchD_1000dfaf_default;
  case 0x61:
    iVar14 = *(int *)param_1[7];
    if (((*(int *)(iVar14 + -8) == -1) ||
        (iVar11 = luaV_tonumber((int *)(iVar14 + -8)), iVar11 == 0)) &&
       ((*(int *)(iVar14 + -0x10) == -1 ||
        (iVar11 = luaV_tonumber((int *)(iVar14 + -0x10)), iVar11 == 0)))) {
      *(float *)(iVar14 + -0xc) = *(float *)(iVar14 + -4) + *(float *)(iVar14 + -0xc);
      *(int *)param_1[7] = *(int *)param_1[7] + -8;
    }
    else {
      call_arith(5);
    }
    goto switchD_1000dfaf_default;
  case 0x62:
    iVar14 = *(int *)param_1[7];
    if (((*(int *)(iVar14 + -8) == -1) ||
        (iVar11 = luaV_tonumber((int *)(iVar14 + -8)), iVar11 == 0)) &&
       ((*(int *)(iVar14 + -0x10) == -1 ||
        (iVar11 = luaV_tonumber((int *)(iVar14 + -0x10)), iVar11 == 0)))) {
      *(float *)(iVar14 + -0xc) = *(float *)(iVar14 + -0xc) - *(float *)(iVar14 + -4);
      *(int *)param_1[7] = *(int *)param_1[7] + -8;
    }
    else {
      call_arith(6);
    }
    goto switchD_1000dfaf_default;
  case 99:
    iVar14 = *(int *)param_1[7];
    if (((*(int *)(iVar14 + -8) == -1) ||
        (iVar11 = luaV_tonumber((int *)(iVar14 + -8)), iVar11 == 0)) &&
       ((*(int *)(iVar14 + -0x10) == -1 ||
        (iVar11 = luaV_tonumber((int *)(iVar14 + -0x10)), iVar11 == 0)))) {
      *(float *)(iVar14 + -0xc) = *(float *)(iVar14 + -4) * *(float *)(iVar14 + -0xc);
      *(int *)param_1[7] = *(int *)param_1[7] + -8;
    }
    else {
      call_arith(7);
    }
    goto switchD_1000dfaf_default;
  case 100:
    iVar14 = *(int *)param_1[7];
    if (((*(int *)(iVar14 + -8) == -1) ||
        (iVar11 = luaV_tonumber((int *)(iVar14 + -8)), iVar11 == 0)) &&
       ((*(int *)(iVar14 + -0x10) == -1 ||
        (iVar11 = luaV_tonumber((int *)(iVar14 + -0x10)), iVar11 == 0)))) {
      *(float *)(iVar14 + -0xc) = *(float *)(iVar14 + -0xc) / *(float *)(iVar14 + -4);
      *(int *)param_1[7] = *(int *)param_1[7] + -8;
    }
    else {
      call_arith(8);
    }
    goto switchD_1000dfaf_default;
  case 0x65:
    call_arith(9);
    goto switchD_1000dfaf_default;
  case 0x66:
    iVar14 = *(int *)param_1[7];
    if (((*(int *)(iVar14 + -0x10) == -2) ||
        (iVar11 = luaV_tostring((int *)(iVar14 + -0x10)), iVar11 == 0)) &&
       ((*(int *)(iVar14 + -8) == -2 || (iVar11 = luaV_tostring((int *)(iVar14 + -8)), iVar11 == 0))
       )) {
      uVar12 = strconc((char *)(*(int *)(iVar14 + -0xc) + 0x18),
                       (char *)(*(int *)(iVar14 + -4) + 0x18));
      *(undefined4 *)(iVar14 + -0xc) = uVar12;
      *(int *)param_1[7] = *(int *)param_1[7] + -8;
      luaC_checkGC();
    }
    else {
      call_binTM(0xf,s_unexpected_type_for_concatenatio_100281a0);
      luaC_checkGC();
    }
    goto switchD_1000dfaf_default;
  case 0x67:
    if ((*(int *)(*(int *)param_1[7] + -8) == -1) ||
       (iVar14 = luaV_tonumber((int *)(*(int *)param_1[7] + -8)), iVar14 == 0)) {
      *(float *)(*(int *)param_1[7] + -4) = -*(float *)(*(int *)param_1[7] + -4);
    }
    else {
      **(undefined4 **)param_1[7] = 0xfffffff9;
      *(int *)param_1[7] = *(int *)param_1[7] + 8;
      call_arith(10);
    }
    goto switchD_1000dfaf_default;
  case 0x68:
    *(uint *)(*(int *)param_1[7] + -8) =
         (-(uint)(*(int *)(*(int *)param_1[7] + -8) != -7) & 0xfffffffa) - 1;
    *(undefined4 *)(*(int *)param_1[7] + -4) = 0x3f800000;
    goto switchD_1000dfaf_default;
  case 0x69:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e756;
  case 0x6a:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e756:
    piVar13 = (int *)param_1[7];
    piVar15 = (int *)(*piVar13 + -8);
    if (*piVar15 == -7) {
LAB_1000e7b5:
      *piVar13 = (int)piVar15;
    }
    else {
      param_1[8] = param_1[8] + param_1[9];
    }
    goto switchD_1000dfaf_default;
  case 0x6b:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e798;
  case 0x6c:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e798:
    piVar13 = (int *)param_1[7];
    piVar15 = (int *)(*piVar13 + -8);
    if (*piVar15 != -7) goto LAB_1000e7b5;
    param_1[8] = param_1[8] + param_1[9];
    goto switchD_1000dfaf_default;
  case 0x6d:
    bVar1 = *pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    param_1[9] = (uint)bVar1;
    param_1[8] = (int)(pbVar2 + 2 + bVar1);
    goto switchD_1000dfaf_default;
  case 0x6e:
    param_1[8] = (int)(pbVar2 + 3);
    iVar14 = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
    param_1[9] = iVar14;
    param_1[8] = (int)(pbVar2 + 3 + iVar14);
    goto switchD_1000dfaf_default;
  case 0x6f:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e81c;
  case 0x70:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e81c:
    *(int *)param_1[7] = *(int *)param_1[7] + -8;
    if (**(int **)param_1[7] == -7) {
      param_1[8] = param_1[8] + param_1[9];
    }
    goto switchD_1000dfaf_default;
  case 0x71:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e869;
  case 0x72:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e869:
    *(int *)param_1[7] = *(int *)param_1[7] + -8;
    if (**(int **)param_1[7] != -7) {
      param_1[8] = param_1[8] - param_1[9];
    }
    goto switchD_1000dfaf_default;
  case 0x73:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e8b6;
  case 0x74:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e8b6:
    *(int *)param_1[7] = *(int *)param_1[7] + -8;
    if (**(int **)param_1[7] == -7) {
      param_1[8] = param_1[8] - param_1[9];
    }
    goto switchD_1000dfaf_default;
  case 0x75:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e8ef;
  case 0x76:
  case 0x77:
    param_1[9] = param_1[9] + -0x76;
LAB_1000e8ef:
    luaV_closure(param_1[9]);
    luaC_checkGC();
    goto switchD_1000dfaf_default;
  case 0x78:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e9a0;
  case 0x79:
  case 0x7a:
    param_1[9] = param_1[9] + -0x79;
LAB_1000e9a0:
    iVar14 = *(int *)param_1[7];
    iVar11 = ((int *)param_1[7])[1];
    bVar1 = *(byte *)param_1[8];
    param_1[8] = (int)((byte *)param_1[8] + 1);
    iVar14 = -((iVar14 - iVar11 >> 3) - (uint)bVar1);
    goto LAB_1000e9fd;
  case 0x7b:
    goto switchD_1000dfaf_caseD_7b;
  case 0x7c:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e92a;
  case 0x7d:
    param_1[8] = (int)(pbVar2 + 3);
    param_1[9] = (uint)pbVar2[1] + (uint)pbVar2[2] * 0x100;
LAB_1000e92a:
    iVar14 = ((int *)param_1[7])[1];
    if (*(int *)(iVar14 + -8 + param_1[2] * 8) != -0xc) {
      luaD_openstack((*(int *)param_1[7] - iVar14 >> 3) - param_1[2]);
      iVar14 = param_1[2];
      param_1[2] = iVar14 + 1;
      *(undefined4 *)(*(int *)(param_1[7] + 4) + -8 + (iVar14 + 1) * 8) = 0xfffffff4;
    }
    *(int *)(*(int *)(param_1[7] + 4) + -4 + param_1[2] * 8) = param_1[9];
    if (lua_linehook != 0) {
      luaD_lineHook(param_1[9]);
    }
    goto switchD_1000dfaf_default;
  case 0x7e:
    param_1[9] = (uint)*pbVar8;
    param_1[8] = (int)(pbVar2 + 2);
    goto LAB_1000e3dc;
  case 0x7f:
  case 0x80:
    param_1[9] = param_1[9] + -0x7f;
LAB_1000e3dc:
    *(int *)param_1[7] = *(int *)param_1[7] + (-1 - param_1[9]) * 8;
  default:
    goto switchD_1000dfaf_default;
  }
  **(undefined4 **)param_1[7] = 0xffffffff;
  *(float *)(*(int *)param_1[7] + 4) = (float)param_1[9];
  *(int *)param_1[7] = *(int *)param_1[7] + 8;
  goto switchD_1000dfaf_default;
switchD_1000dfaf_caseD_0:
  *(int *)param_1[7] = ((int *)param_1[7])[1] + param_1[2] * 8;
switchD_1000dfaf_caseD_7b:
  if (lua_callhook != 0) {
    luaD_callHook(param_1[2],0,1);
  }
  if (param_1[9] == 0x7b) {
    uVar16 = (uint)*(byte *)param_1[8];
  }
  else {
    uVar16 = 0;
  }
  iVar14 = param_1[2] + uVar16;
LAB_1000e9fd:
  g_pLuaState[6] = g_pLuaState[6] + -1;
  return iVar14;
}

/* ---- 0x1000ebc0  strconc ---- */
/* lvm.c: string concatenation Named strconc (not in the remaster, gcc inlined it there): Lua 3.1
   source name (lvm.c static strconc(l, r): luaL_openspace(strlen(l) + strlen(r) + 1), strcpy,
   strcat); was luaV_strconc. */

TaggedString * __cdecl strconc(char *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  TaggedString *pTVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  
  uVar4 = 0xffffffff;
  pcVar2 = param_1;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  uVar5 = 0xffffffff;
  pcVar2 = param_2;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = (char *)luaL_openspace(~uVar5 + (~uVar4 - 1));
  uVar5 = 0xffffffff;
  do {
    pcVar7 = param_1;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar7;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar7 = pcVar7 + -uVar5;
  pcVar8 = pcVar2;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar5 = 0xffffffff;
  do {
    pcVar7 = param_2;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = param_2 + 1;
    cVar1 = *param_2;
    param_2 = pcVar7;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar7 = pcVar7 + -uVar5;
  pcVar8 = pcVar2 + (~uVar4 - 1);
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  pTVar3 = luaS_new(pcVar2);
  return pTVar3;
}

/* ---- 0x1000ec50  call_binTM ---- */
/* call_binTM(event, msg): binary tag-method dispatch on the two top stack slots (was mislabelled
   luaV_gettable) Original name call_binTM (the remaster's libLua.so: static call_binTM(int, char*):
   caller of luaT_efectivetag from the VM's arithmetic); was luaV_call_binTM. */

void __cdecl call_binTM(int param_1,byte *param_2)

{
  int iVar1;
  TObject *f;
  
  iVar1 = luaT_efectivetag((TObject *)(g_pLuaState[7] + -0x10));
  iVar1 = param_1 + iVar1 * -0x12;
  f = (TObject *)(g_dwLState_IMtable + iVar1 * 8);
  if (*(int *)(g_dwLState_IMtable + iVar1 * 8) == -7) {
    iVar1 = luaT_efectivetag((TObject *)(g_pLuaState[7] + -8));
    iVar1 = param_1 + iVar1 * -0x12;
    f = (TObject *)(g_dwLState_IMtable + iVar1 * 8);
    if ((*(int *)(g_dwLState_IMtable + iVar1 * 8) == -7) &&
       (f = (TObject *)(g_dwLState_IMtable + param_1 * 8),
       *(int *)(g_dwLState_IMtable + param_1 * 8) == -7)) {
      lua_error(param_2);
    }
  }
  lua_pushstring((&g_pLuaT_eventname)[param_1]);
  luaD_callTM(f,3,1);
  return;
}

/* ---- 0x1000ecf0  call_arith ---- */
/* Named call_arith (not in the remaster, gcc inlined it there): Lua 3.1 source name (lvm.c static
   call_arith: call_binTM(event, "unexpected type in arithmetic operation")); was luaV_call_arith.
    */

void __cdecl call_arith(int param_1)

{
  call_binTM(param_1,s_unexpected_type_in_arithmetic_op_1002825c);
  return;
}

/* ---- 0x1000ed10  comparison ---- */
/* Named comparison (not in the remaster, gcc inlined it there): Lua 3.1 source name (lvm.c static
   comparison(ltue, equl, gtue, event): numbers or strings (strcoll), else call_binTM "unexpected
   type in comparison"); was luaV_comparison. */

void __cdecl comparison(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = g_pLuaState[7];
  piVar1 = g_pLuaState + 7;
  if ((*(int *)(iVar3 + -0x10) == -1) && (*(int *)(iVar3 + -8) == -1)) {
    if (*(float *)(iVar3 + -4) <= *(float *)(iVar3 + -0xc)) {
      if (*(float *)(iVar3 + -4) == *(float *)(iVar3 + -0xc)) {
        iVar3 = 0;
      }
      else {
        iVar3 = 1;
      }
    }
    else {
      iVar3 = -1;
    }
  }
  else {
    if ((*(int *)(iVar3 + -0x10) != -2) || (*(int *)(iVar3 + -8) != -2)) {
      call_binTM(param_4,s_unexpected_type_in_comparison_10028284);
      return;
    }
    iVar3 = strcoll((byte *)(*(int *)(iVar3 + -0xc) + 0x18),(byte *)(*(int *)(iVar3 + -4) + 0x18));
  }
  iVar2 = *piVar1;
  *piVar1 = iVar2 + -8;
  *(undefined4 *)(iVar2 + -0xc) = 0x3f800000;
  if (iVar3 < 0) {
    *(undefined4 *)(*piVar1 + -8) = param_1;
    return;
  }
  if (iVar3 != 0) {
    param_2 = param_3;
  }
  *(undefined4 *)(*piVar1 + -8) = param_2;
  return;
}
