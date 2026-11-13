/* LUA.DLL :: ldo.c
 * functions 0x10003e40 .. 0x10004a50 (18 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10003e40  luaD_checkstack ---- */
/* ldo.c: Lua2C - C2Lua overflow / stack size overflow */

void __cdecl luaD_checkstack(int param_1)

{
  TObject **ppTVar1;
  TObject *pTVar2;
  TObject *pTVar3;
  LState *pLVar4;
  TObject *pTVar5;
  int iVar6;
  
  pLVar4 = g_pLuaState;
  pTVar2 = g_pLuaState->pTop;
  ppTVar1 = &g_pLuaState->pTop;
  if ((int)g_pLuaState->pLast - (int)pTVar2 >> 3 <= param_1) {
    pTVar3 = g_pLuaState->pStack;
    iVar6 = ((int)g_pLuaState->pLast - (int)pTVar3 >> 3) + 0x101 + param_1;
    pTVar5 = (TObject *)
             (**(code **)(g_dwLuaHS + 0x28))
                       (pTVar3,iVar6 * 8,s_C__grimsrc_libs_lua_src_ldo_cpp_10026a04,0x47);
    pLVar4->pStack = pTVar5;
    pLVar4->pLast = pTVar5 + iVar6 + -1;
    *ppTVar1 = pTVar5 + ((int)pTVar2 - (int)pTVar3 >> 3);
    if (5999 < iVar6) {
      iVar6 = lua_stackedfunction(100);
      if (iVar6 == 0) {
        lua_error((byte *)s_Lua2C___C2Lua_overflow_100269ec);
        return;
      }
      lua_error((byte *)s_stack_size_overflow_100269d8);
    }
  }
  return;
}

/* ---- 0x10003ee0  luaD_adjusttop ---- */
/* Unidentified function of ldo.c (stack and call machinery, Grim task marks) */

void __cdecl luaD_adjusttop(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 - ((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3);
  if (iVar1 < 1) {
    g_pLuaState->pTop = g_pLuaState->pTop + iVar1;
    return;
  }
  luaD_checkstack(iVar1);
  do {
    g_pLuaState->pTop->nTtype = -7;
    iVar1 = iVar1 + -1;
    g_pLuaState->pTop = g_pLuaState->pTop + 1;
  } while (iVar1 != 0);
  return;
}

/* ---- 0x10003f40  luaD_openstack ---- */
/* Unidentified function of ldo.c (stack and call machinery, Grim task marks) */

void __cdecl luaD_openstack(int param_1)

{
  memcpy(&(g_pLuaState->pTop + -param_1)[1].nTtype,&g_pLuaState->pTop[-param_1].nTtype,param_1 * 8);
  if (g_pLuaState->pLast <= g_pLuaState->pTop) {
    luaD_checkstack(1);
  }
  g_pLuaState->pTop = g_pLuaState->pTop + 1;
  return;
}

/* ---- 0x10003f90  luaD_lineHook ---- */
/* Unidentified function of ldo.c (stack and call machinery, Grim task marks) */

void __cdecl luaD_lineHook(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  LState *pLVar5;
  
  iVar1 = (g_pLuaState->Cstack).nBase;
  iVar2 = (g_pLuaState->Cstack).nLua2C;
  iVar3 = (g_pLuaState->Cstack).nNum;
  (g_pLuaState->Cstack).nBase = (int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3;
  (g_pLuaState->Cstack).nLua2C = (g_pLuaState->Cstack).nBase;
  iVar4 = (g_pLuaState->Cstack).nLua2C;
  (g_pLuaState->Cstack).nNum = 0;
  (*lua_linehook)(param_1);
  g_pLuaState->pTop = g_pLuaState->pStack + iVar4;
  pLVar5 = g_pLuaState;
  (g_pLuaState->Cstack).nBase = iVar1;
  (pLVar5->Cstack).nLua2C = iVar2;
  (pLVar5->Cstack).nNum = iVar3;
  return;
}

/* ---- 0x10004000  luaD_callHook ---- */
/* Calls the call hook with the function name or '(return)' */

void __cdecl luaD_callHook(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  LState *pLVar5;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  
  iVar1 = (g_pLuaState->Cstack).nBase;
  iVar2 = (g_pLuaState->Cstack).nLua2C;
  iVar3 = (g_pLuaState->Cstack).nNum;
  (g_pLuaState->Cstack).nBase = (int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3;
  (g_pLuaState->Cstack).nLua2C = (g_pLuaState->Cstack).nBase;
  iVar4 = (g_pLuaState->Cstack).nLua2C;
  (g_pLuaState->Cstack).nNum = 0;
  if (param_3 == 0) {
    if (param_2 == 0) {
      uVar8 = 0xffffffff;
      pcVar7 = &DAT_10026264;
    }
    else {
      uVar8 = *(undefined4 *)(param_2 + 0x14);
      pcVar7 = (char *)(*(int *)(param_2 + 0x18) + 0x18);
    }
    iVar6 = (param_1 * 8 + -8 >> 3) + 1;
  }
  else {
    uVar8 = 0;
    pcVar7 = s__return__10026a24;
    iVar6 = 0;
  }
  (*lua_callhook)(iVar6,pcVar7,uVar8);
  g_pLuaState->pTop = g_pLuaState->pStack + iVar4;
  pLVar5 = g_pLuaState;
  (g_pLuaState->Cstack).nBase = iVar1;
  (pLVar5->Cstack).nLua2C = iVar2;
  (pLVar5->Cstack).nNum = iVar3;
  return;
}

/* ---- 0x100040c0  luaD_taskHook ---- */
/* Original name luaD_taskHook (the remaster's libLua.so: calls lua_taskhook); was ldo__40c0. */

void __cdecl luaD_taskHook(undefined4 param_1,undefined4 param_2)

{
  (*lua_taskhook)(param_1,param_2);
  return;
}

/* ---- 0x100040e0  luaD_callTM ---- */
/* Unidentified function of ldo.c (stack and call machinery, Grim task marks) */

void __cdecl luaD_callTM(TObject *f,int nParams,int nResults)

{
  int *piVar1;
  
  luaD_openstack(nParams);
  piVar1 = (int *)((int)g_pLuaState->pTop - (nParams * 8 + 8));
  *piVar1 = f->nTtype;
  piVar1[1] = f->dwValue;
  g_pLuaState->nPreventBreak = g_pLuaState->nPreventBreak + 1;
  g_pLuaState->nNestingLevel = g_pLuaState->nNestingLevel + 1;
  luaD_call(((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3) - nParams,nResults);
  g_pLuaState->nNestingLevel = g_pLuaState->nNestingLevel + -1;
  g_pLuaState->nPreventBreak = g_pLuaState->nPreventBreak + -1;
  return;
}

/* ---- 0x10004160  luaD_deletestates ---- */
/* Original name luaD_deletestates (the remaster's libLua.so: frees a chain of execution states
   (next at +0xc, ExecutionState_Delete)); was ldo__4160. */

void __cdecl luaD_deletestates(int param_1)

{
  int iVar1;
  
  while (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 0xc);
    ExecutionState_Delete(param_1);
    param_1 = iVar1;
  }
  return;
}

/* ---- 0x10004180  luaD_call ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Dispatches a call at the given stack position: C function, Lua closure or task mark ('unexpected
   cmark' otherwise) */

uint __cdecl luaD_call(int pos,int nres)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint a1;
  void *pvVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  TObject *pTVar10;
  #define pvStack_14 (*(void **)(_frame + (0x30 - 0x14)))
  
  iVar7 = nres;
  pvStack_14 = g_pLuaState->pExecutionState;
  if ((pvStack_14 == (void *)0x0) || (g_pLuaState->nNestingLevel != 0)) {
    pvVar1 = ExecutionState_New(0x30);
    if (pvVar1 == (void *)0x0) {
      pvVar2 = (void *)0x0;
    }
    else {
      pvVar2 = (void *)ExecutionState_Construct(pvVar1,(int)g_pLuaState->pExecutionState,pos,nres);
    }
    g_pLuaState->pExecutionState = pvVar2;
    nres = (int)pvVar1;
  }
  else {
    pvStack_14 = g_pLuaState->pResumeState;
  }
  iVar3 = nres;
  iVar8 = pos;
  do {
    pos = 0;
    pTVar10 = g_pLuaState->pStack + iVar8 + -1;
    switch(g_pLuaState->pStack[iVar8 + -1].nTtype) {
    case -0xb:
      printf(s_unexpected_cmark_at__d_10026a50,iVar8);
      if (*(int *)((int)g_pLuaState->pExecutionState + 0x18) == 0)
      goto switchD_1000422b_caseD_fffffff9;
      break;
    case -10:
      piVar5 = g_pLuaState->pExecutionState;
      if (piVar5[6] != 0) goto LAB_100042fe;
    default:
switchD_1000422b_caseD_fffffff9:
      iVar4 = luaT_efectivetag(pTVar10);
      pTVar10 = (TObject *)(g_dwLState_IMtable + iVar4 * -0x90 + 0x88);
      if (pTVar10->nTtype == -7) {
        lua_error((byte *)s_call_expression_not_a_function_10026a30);
      }
      luaD_callTM(pTVar10,(((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3) - iVar8) + 1,
                  iVar7);
      goto LAB_10004474;
    case -9:
      piVar5 = g_pLuaState->pExecutionState;
      if (piVar5[6] == 0) goto switchD_1000422b_caseD_fffffff9;
      if (*(int *)(pTVar10->dwValue + 0xc) != -5) goto LAB_100042fe;
      break;
    case -8:
      a1 = pTVar10->dwValue;
      pTVar10->nTtype = -9;
      if (*(int *)(a1 + 0xc) != -5) {
        ExecutionState_setvalues(g_pLuaState->pExecutionState,a1,*(int *)(a1 + 0x10),iVar8);
        piVar5 = g_pLuaState->pExecutionState;
        goto LAB_100042fe;
      }
      iVar3 = callCclosure(a1,*(undefined **)(a1 + 0x10),iVar8);
      pos = a1;
      nres = iVar3;
      break;
    case -5:
      pTVar10->nTtype = -0xb;
      pos = pTVar10->dwValue;
      iVar3 = callC((undefined *)pos,iVar8);
      nres = iVar3;
      break;
    case -4:
      pTVar10->nTtype = -10;
      ExecutionState_setvalues(g_pLuaState->pExecutionState,0,pTVar10->dwValue,iVar8);
      piVar5 = g_pLuaState->pExecutionState;
LAB_100042fe:
      iVar3 = ExecutionState_execute(piVar5);
      nres = iVar3;
    }
    if (iVar3 < 1) {
      iVar8 = -iVar3;
      iVar7 = ExecutionState_getaux((int)g_pLuaState->pExecutionState);
      pvVar1 = ExecutionState_New(0x30);
      if (pvVar1 == (void *)0x0) {
        pvVar1 = (void *)0x0;
      }
      else {
        pvVar1 = (void *)ExecutionState_Construct
                                   (pvVar1,(int)g_pLuaState->pExecutionState,iVar8,iVar7);
      }
      g_pLuaState->pExecutionState = pvVar1;
    }
    else {
      iVar8 = *(int *)((int)g_pLuaState->pExecutionState + 0x10);
      iVar7 = *(int *)((int)g_pLuaState->pExecutionState + 0x14);
      if (iVar7 != 0xff) {
        luaD_adjusttop(iVar3 + iVar7);
      }
      iVar8 = iVar8 + -1;
      iVar7 = (int)g_pLuaState->pTop + (iVar3 * -8 - (int)g_pLuaState->pStack) >> 3;
      if (0 < iVar7) {
        iVar4 = iVar3 * 8;
        iVar6 = iVar8 * 8;
        iVar9 = iVar7;
        do {
          pTVar10 = g_pLuaState->pStack;
          iVar9 = iVar9 + -1;
          *(undefined4 *)((int)&pTVar10->nTtype + iVar6) =
               *(undefined4 *)((int)&pTVar10->nTtype + iVar4);
          *(undefined4 *)((int)&pTVar10->dwValue + iVar6) =
               *(undefined4 *)((int)&pTVar10->dwValue + iVar4);
          iVar4 = iVar4 + 8;
          iVar6 = iVar6 + 8;
          iVar3 = nres;
        } while (iVar9 != 0);
      }
      g_pLuaState->pTop = g_pLuaState->pTop + (iVar8 - iVar3);
      pvVar1 = g_pLuaState->pExecutionState;
      g_pLuaState->pExecutionState = *(void **)((int)pvVar1 + 0xc);
      ExecutionState_Delete((int)pvVar1);
      pvVar1 = g_pLuaState->pExecutionState;
      if (pvVar1 != (void *)0x0) {
        iVar8 = *(int *)((int)pvVar1 + 0x10);
        iVar7 = *(int *)((int)pvVar1 + 0x14);
      }
      if (((code *)pos == luaI_breakhere) && (g_pLuaState->nPreventBreak == 0)) {
        g_pLuaState->pResumeState = pvStack_14;
        return 1;
      }
    }
LAB_10004474:
    if (g_pLuaState->pExecutionState == pvStack_14) {
      return 0;
    }
  } while( true );
}
#undef pvStack_14

#endif


/* ---- 0x100044e0  callC ---- */
/* Named callC (not in the remaster, gcc inlined it there): Lua 3.1 source name (ldo.c: saves the C
   stack frame, runs the call hook, calls the C function, used by luaD_call / callCclosure); was
   ldo__44e0. */

int __cdecl callC(undefined *param_1,int param_2)

{
  CLuaStack *pCVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  LState *pLVar5;
  int iVar6;
  
  pLVar5 = g_pLuaState;
  pCVar1 = &g_pLuaState->Cstack;
  iVar2 = pCVar1->nBase;
  iVar3 = (g_pLuaState->Cstack).nLua2C;
  iVar4 = (g_pLuaState->Cstack).nNum;
  iVar6 = ((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3) - param_2;
  (g_pLuaState->Cstack).nLua2C = param_2;
  (pLVar5->Cstack).nNum = iVar6;
  pCVar1->nBase = iVar6 + param_2;
  if (lua_callhook != 0) {
    luaD_callHook(param_2,0,0);
  }
  g_pLuaState->nNestingLevel = g_pLuaState->nNestingLevel + 1;
  (*(code *)param_1)();
  g_pLuaState->nNestingLevel = g_pLuaState->nNestingLevel + -1;
  if (lua_callhook != 0) {
    luaD_callHook(param_2,0,1);
  }
  iVar6 = pCVar1->nBase;
  pCVar1->nBase = iVar2;
  (pLVar5->Cstack).nLua2C = iVar3;
  (pLVar5->Cstack).nNum = iVar4;
  return iVar6;
}

/* ---- 0x10004580  callCclosure ---- */
/* Named callCclosure (not in the remaster, gcc inlined it there): Lua 3.1 source name (ldo.c static
   callCclosure: checkstack(nelems), moves the arguments up, copies the closure's upvalues
   (consts+1) below them, then callC; called by luaD_call); was luaD_callC. */

int __cdecl callCclosure(int param_1,undefined *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  TObject *pTVar4;
  
  uVar1 = *(uint *)(param_1 + 8);
  luaD_checkstack(uVar1);
  pTVar4 = g_pLuaState->pStack + param_3;
  memcpy(&pTVar4[uVar1].nTtype,&pTVar4->nTtype,((int)g_pLuaState->pTop - (int)pTVar4 >> 3) << 3);
  piVar3 = (int *)(param_1 + 0x14);
  for (iVar2 = (uVar1 & 0x1fffffff) << 1; iVar2 != 0; iVar2 = iVar2 + -1) {
    pTVar4->nTtype = *piVar3;
    piVar3 = piVar3 + 1;
    pTVar4 = (TObject *)&pTVar4->dwValue;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(char *)&pTVar4->nTtype = (char)*piVar3;
    piVar3 = (int *)((int)piVar3 + 1);
    pTVar4 = (TObject *)((int)&pTVar4->nTtype + 1);
  }
  g_pLuaState->pTop = g_pLuaState->pTop + uVar1;
  iVar2 = callC(param_2,param_3);
  return iVar2;
}

/* ---- 0x10004600  luaD_travallstacks ---- */
/* Original name luaD_travallstacks (the remaster's libLua.so: walks every state (LState_next) and
   calls the function on each stack slot); was ldo__4600. */

void __cdecl luaD_travallstacks(undefined *param_1)

{
  LState *L;
  int iVar1;
  
  for (L = g_dwL_Main; L != (LState *)0x0; L = LState_next(L)) {
    for (iVar1 = (int)L->pTop + (-8 - (int)L->pStack) >> 3; -1 < iVar1; iVar1 = iVar1 + -1) {
      (*(code *)param_1)(L->pStack + iVar1);
    }
  }
  return;
}

/* ---- 0x100046a0  message ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* ldo.c message(): pushes the string and calls the error tag method Named message (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (ldo.c static message: if errorim is not
   nil, pushstring and luaD_callTM(errorim, 1, 0); called by lua_error); was luaD_message. */

void __cdecl message(byte *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_4 = DAT_1002bf5c;
  if (g_dwLState_errorim != -7) {
    lua_pushstring(param_1);
    luaD_callTM((TObject *)&local_4,1,0);
  }
  return;
}
#undef local_4

#endif


/* ---- 0x100046e0  luaD_protectedrun ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* setjmp-protected call (do_protectedrun) */

undefined4 __cdecl luaD_protectedrun(void *param_1)

{
  unsigned char _stkneg[112] __attribute__((aligned(16)));  /* the original frame below the return address */
  int iVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  void *pvVar5;
  void *pvVar6;
  LState *pLVar7;
  int iVar8;
  undefined4 uVar9;
  int in_stack_ffffffa8;
  undefined4 in_stack_ffffffac;
  
  iVar1 = (g_pLuaState->Cstack).nBase;
  iVar2 = (g_pLuaState->Cstack).nLua2C;
  pvVar3 = g_pLuaState->pErrorJmp;
  iVar4 = (g_pLuaState->Cstack).nNum;
  pvVar5 = g_pLuaState->pExecutionState;
  g_pLuaState->pErrorJmp = (_stkneg + 24);
  g_pLuaState->nPreventBreak = g_pLuaState->nPreventBreak + 1;
  iVar8 = _setjmp3((undefined4 *)(_stkneg + 24),0,in_stack_ffffffa8,in_stack_ffffffac);
  pLVar7 = g_pLuaState;
  if (iVar8 == 0) {
    do_callinc(param_1);
    uVar9 = 0;
  }
  else {
    (g_pLuaState->Cstack).nBase = iVar1;
    (pLVar7->Cstack).nLua2C = iVar2;
    (pLVar7->Cstack).nNum = iVar4;
    g_pLuaState->pTop = g_pLuaState->pStack + (g_pLuaState->Cstack).nBase;
    pvVar6 = g_pLuaState->pExecutionState;
    while (pvVar6 != pvVar5) {
      g_pLuaState->pExecutionState = *(void **)((int)pvVar6 + 0xc);
      ExecutionState_Delete((int)pvVar6);
      pvVar6 = g_pLuaState->pExecutionState;
    }
    uVar9 = 1;
  }
  g_pLuaState->pErrorJmp = pvVar3;
  g_pLuaState->nPreventBreak = g_pLuaState->nPreventBreak + -1;
  return uVar9;
}
#endif


/* ---- 0x100047c0  do_callinc ---- */
/* Named do_callinc (not in the remaster, gcc inlined it there): Lua 3.1 source name (ldo.c static
   do_callinc: luaD_call(base+1, nResults), then Cstack.lua2C / num / base from the new top); was
   luaD_callinc. */

void __cdecl do_callinc(void *param_1)

{
  int iVar1;
  
  iVar1 = (g_pLuaState->Cstack).nBase;
  luaD_call(iVar1 + 1,(int)param_1);
  (g_pLuaState->Cstack).nLua2C = iVar1;
  (g_pLuaState->Cstack).nNum = ((int)g_pLuaState->pTop - (int)g_pLuaState->pStack >> 3) - iVar1;
  (g_pLuaState->Cstack).nBase = (g_pLuaState->Cstack).nNum + iVar1;
  return;
}

/* ---- 0x10004810  luaD_gcIM ---- */
/* Calls the garbage-collection tag method of an object */

void __cdecl luaD_gcIM(TObject *o)

{
  TObject *pTVar1;
  int iVar2;
  
  iVar2 = luaT_efectivetag(o);
  iVar2 = g_dwLState_IMtable + iVar2 * -0x90;
  if (*(int *)(iVar2 + 0x80) != -7) {
    pTVar1 = g_pLuaState->pTop;
    pTVar1->nTtype = o->nTtype;
    pTVar1->dwValue = o->dwValue;
    if (g_pLuaState->pLast <= g_pLuaState->pTop) {
      luaD_checkstack(1);
    }
    g_pLuaState->pTop = g_pLuaState->pTop + 1;
    luaD_callTM((TObject *)(iVar2 + 0x80),1,0);
  }
  return;
}

/* ---- 0x100049b0  do_main ---- */
/* do_main: parse (text or precompiled) then run, both protected Original name do_main (the
   remaster's libLua.so: static do_main(ZIO*, int): the only caller of luaD_protectedrun besides
   lua_dofile / lua_dostring paths); was luaD_domain. */

int __cdecl do_main(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  luaC_checkGC();
  iVar2 = g_dwLState_nblocks;
  iVar1 = protectedparser(param_1,param_2);
  while( true ) {
    if (iVar1 == 1) {
      return 1;
    }
    if (iVar1 == 2) {
      return 0;
    }
    iVar2 = iVar2 * 0x7fffffff + g_dwLState_nblocks;
    g_dwLState_GCthreshold = g_dwLState_GCthreshold + iVar2 * 2;
    iVar1 = luaD_protectedrun((void *)0xff);
    g_dwLState_GCthreshold = g_dwLState_GCthreshold + iVar2 * -2;
    if (param_2 == 0) {
      return iVar1;
    }
    if (iVar1 != 0) break;
    luaC_checkGC();
    iVar2 = g_dwLState_nblocks;
    iVar1 = protectedparser(param_1,param_2);
  }
  return iVar1;
}

/* ---- 0x10004a50  protectedparser ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* ldo.c: runs luaU_undump1 or luaY_parser on the open ZIO Original name protectedparser (the
   remaster's libLua.so: static protectedparser(ZIO*, int): the only caller of luaY_parser /
   luaU_undump1 / luaV_closure here); was luaD_protectedparser. */

undefined4 __cdecl protectedparser(int *param_1,int param_2)

{
  unsigned char _stkneg[96] __attribute__((aligned(16)));  /* the original frame below the return address */
  void *pvVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int unaff_ESI;
  undefined4 in_stack_ffffffb8;
  
  pvVar1 = g_pLuaState->pErrorJmp;
  g_pLuaState->pErrorJmp = (_stkneg + 24);
  iVar3 = _setjmp3((undefined4 *)(_stkneg + 24),0,unaff_ESI,in_stack_ffffffb8);
  if (iVar3 == 0) {
    if (param_2 == 0) {
      uVar4 = luaY_parser((int)param_1);
      bVar2 = false;
    }
    else {
      uVar4 = luaU_undump1(param_1);
      bVar2 = false;
    }
  }
  else {
    uVar4 = 0;
    bVar2 = true;
  }
  g_pLuaState->pErrorJmp = pvVar1;
  if (bVar2) {
    return 1;
  }
  if (uVar4 == 0) {
    return 2;
  }
  luaD_adjusttop((g_pLuaState->Cstack).nBase + 1);
  g_pLuaState->pStack[(g_pLuaState->Cstack).nBase].nTtype = -4;
  g_pLuaState->pStack[(g_pLuaState->Cstack).nBase].dwValue = uVar4;
  luaV_closure(0);
  return 0;
}
#endif

