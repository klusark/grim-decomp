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
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  
  piVar5 = g_pLuaState;
  iVar7 = g_pLuaState[7];
  piVar1 = g_pLuaState + 7;
  if (g_pLuaState[9] - iVar7 >> 3 <= param_1) {
    iVar4 = g_pLuaState[8];
    iVar3 = (g_pLuaState[9] - iVar4 >> 3) + 0x101 + param_1;
    iVar2 = iVar3 * 8;
    iVar6 = (**(code **)(g_dwLuaHS + 0x28))
                      (iVar4,iVar2,s_C__grimsrc_libs_lua_src_ldo_cpp_10026a04,0x47);
    piVar5[8] = iVar6;
    piVar5[9] = iVar2 + -8 + iVar6;
    *piVar1 = iVar6 + (iVar7 - iVar4 >> 3) * 8;
    if (5999 < iVar3) {
      iVar7 = lua_stackedfunction(100);
      if (iVar7 == 0) {
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
  
  iVar1 = param_1 - (g_pLuaState[7] - g_pLuaState[8] >> 3);
  if (iVar1 < 1) {
    g_pLuaState[7] = g_pLuaState[7] + iVar1 * 8;
    return;
  }
  luaD_checkstack(iVar1);
  do {
    *(undefined4 *)g_pLuaState[7] = 0xfffffff9;
    iVar1 = iVar1 + -1;
    g_pLuaState[7] = g_pLuaState[7] + 8;
  } while (iVar1 != 0);
  return;
}

/* ---- 0x10003f40  luaD_openstack ---- */
/* Unidentified function of ldo.c (stack and call machinery, Grim task marks) */

void __cdecl luaD_openstack(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(g_pLuaState[7] + param_1 * -8);
  memcpy(puVar1 + 2,puVar1,param_1 * 8);
  if ((uint)g_pLuaState[9] <= (uint)g_pLuaState[7]) {
    luaD_checkstack(1);
  }
  g_pLuaState[7] = g_pLuaState[7] + 8;
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
  int *piVar5;
  
  iVar1 = g_pLuaState[10];
  iVar2 = g_pLuaState[0xb];
  iVar3 = g_pLuaState[0xc];
  g_pLuaState[10] = g_pLuaState[7] - g_pLuaState[8] >> 3;
  g_pLuaState[0xb] = g_pLuaState[10];
  iVar4 = g_pLuaState[0xb];
  g_pLuaState[0xc] = 0;
  (*lua_linehook)(param_1);
  g_pLuaState[7] = g_pLuaState[8] + iVar4 * 8;
  piVar5 = g_pLuaState;
  g_pLuaState[10] = iVar1;
  piVar5[0xb] = iVar2;
  piVar5[0xc] = iVar3;
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
  int *piVar5;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  
  iVar1 = g_pLuaState[10];
  iVar2 = g_pLuaState[0xb];
  iVar3 = g_pLuaState[0xc];
  g_pLuaState[10] = g_pLuaState[7] - g_pLuaState[8] >> 3;
  g_pLuaState[0xb] = g_pLuaState[10];
  iVar4 = g_pLuaState[0xb];
  g_pLuaState[0xc] = 0;
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
  g_pLuaState[7] = g_pLuaState[8] + iVar4 * 8;
  piVar5 = g_pLuaState;
  g_pLuaState[10] = iVar1;
  piVar5[0xb] = iVar2;
  piVar5[0xc] = iVar3;
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

void __cdecl luaD_callTM(undefined4 *param_1,int param_2,void *param_3)

{
  undefined4 *puVar1;
  
  luaD_openstack(param_2);
  puVar1 = (undefined4 *)(g_pLuaState[7] - (param_2 * 8 + 8));
  *puVar1 = *param_1;
  puVar1[1] = param_1[1];
  g_pLuaState[2] = g_pLuaState[2] + 1;
  g_pLuaState[6] = g_pLuaState[6] + 1;
  luaD_call((g_pLuaState[7] - g_pLuaState[8] >> 3) - param_2,param_3);
  g_pLuaState[6] = g_pLuaState[6] + -1;
  g_pLuaState[2] = g_pLuaState[2] + -1;
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

undefined4 luaD_call(code *param_1,void *param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  code *a1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  void *a3;
  void *pvVar8;
  int *piVar9;
  #define iStack_14 (*(int *)(_frame + (0x30 - 0x14)))
  
  a3 = param_2;
  iStack_14 = *g_pLuaState;
  if ((iStack_14 == 0) || (g_pLuaState[6] != 0)) {
    pvVar3 = ExecutionState_New(0x30);
    if (pvVar3 == (void *)0x0) {
      iVar4 = 0;
    }
    else {
      iVar4 = ExecutionState_Construct(pvVar3,*g_pLuaState,(int)param_1,(int)param_2);
    }
    *g_pLuaState = iVar4;
    param_2 = pvVar3;
  }
  else {
    iStack_14 = g_pLuaState[1];
  }
  pvVar3 = param_2;
  iVar4 = (int)param_1;
  do {
    param_1 = (code *)0x0;
    puVar1 = (uint *)(g_pLuaState[8] + -8 + iVar4 * 8);
    switch(*(undefined4 *)(g_pLuaState[8] + -8 + iVar4 * 8)) {
    case 0xfffffff5:
      printf(s_unexpected_cmark_at__d_10026a50,iVar4);
      if (*(int *)(*g_pLuaState + 0x18) == 0) goto switchD_1000422b_caseD_fffffff9;
      break;
    case 0xfffffff6:
      piVar9 = (int *)*g_pLuaState;
      if (piVar9[6] != 0) goto LAB_100042fe;
    default:
switchD_1000422b_caseD_fffffff9:
      uVar6 = luaT_efectivetag(puVar1);
      piVar9 = (int *)(g_dwLState_IMtable + uVar6 * -0x90 + 0x88);
      if (*piVar9 == -7) {
        lua_error((byte *)s_call_expression_not_a_function_10026a30);
      }
      luaD_callTM(piVar9,((g_pLuaState[7] - g_pLuaState[8] >> 3) - iVar4) + 1,a3);
      goto LAB_10004474;
    case 0xfffffff7:
      piVar9 = (int *)*g_pLuaState;
      if (piVar9[6] == 0) goto switchD_1000422b_caseD_fffffff9;
      if (*(int *)(puVar1[1] + 0xc) != -5) goto LAB_100042fe;
      break;
    case 0xfffffff8:
      a1 = (code *)puVar1[1];
      *puVar1 = 0xfffffff7;
      if (*(int *)(a1 + 0xc) != -5) {
        ExecutionState_setvalues((void *)*g_pLuaState,(int)a1,*(int *)(a1 + 0x10),iVar4);
        piVar9 = (int *)*g_pLuaState;
        goto LAB_100042fe;
      }
      pvVar3 = (void *)luaD_callC((int)a1,*(undefined **)(a1 + 0x10),iVar4);
      param_1 = a1;
      param_2 = pvVar3;
      break;
    case 0xfffffffb:
      *puVar1 = 0xfffffff5;
      param_1 = (code *)puVar1[1];
      pvVar3 = (void *)ldo__44e0(param_1,iVar4);
      param_2 = pvVar3;
      break;
    case 0xfffffffc:
      *puVar1 = 0xfffffff6;
      ExecutionState_setvalues((void *)*g_pLuaState,0,puVar1[1],iVar4);
      piVar9 = (int *)*g_pLuaState;
LAB_100042fe:
      pvVar3 = (void *)ExecutionState_execute(piVar9);
      param_2 = pvVar3;
    }
    if ((int)pvVar3 < 1) {
      iVar4 = -(int)pvVar3;
      a3 = (void *)ExecutionState_getaux(*g_pLuaState);
      pvVar8 = ExecutionState_New(0x30);
      if (pvVar8 == (void *)0x0) {
        iVar5 = 0;
      }
      else {
        iVar5 = ExecutionState_Construct(pvVar8,*g_pLuaState,iVar4,(int)a3);
      }
      *g_pLuaState = iVar5;
    }
    else {
      iVar4 = *(int *)(*g_pLuaState + 0x10);
      iVar5 = *(int *)(*g_pLuaState + 0x14);
      if (iVar5 != 0xff) {
        luaD_adjusttop((int)pvVar3 + iVar5);
      }
      iVar4 = iVar4 + -1;
      a3 = (void *)((g_pLuaState[7] - g_pLuaState[8]) + (int)pvVar3 * -8 >> 3);
      if (0 < (int)a3) {
        iVar5 = (int)pvVar3 * 8;
        iVar7 = iVar4 * 8;
        pvVar8 = a3;
        do {
          iVar2 = g_pLuaState[8];
          pvVar8 = (void *)((int)pvVar8 + -1);
          *(undefined4 *)(iVar7 + iVar2) = *(undefined4 *)(iVar5 + iVar2);
          *(undefined4 *)(iVar7 + 4 + iVar2) = *(undefined4 *)(iVar5 + 4 + iVar2);
          iVar5 = iVar5 + 8;
          iVar7 = iVar7 + 8;
          pvVar3 = param_2;
        } while (pvVar8 != (void *)0x0);
      }
      g_pLuaState[7] = g_pLuaState[7] + (iVar4 - (int)pvVar3) * 8;
      iVar5 = *g_pLuaState;
      *g_pLuaState = *(int *)(iVar5 + 0xc);
      ExecutionState_Delete(iVar5);
      iVar5 = *g_pLuaState;
      if (iVar5 != 0) {
        iVar4 = *(int *)(iVar5 + 0x10);
        a3 = *(void **)(iVar5 + 0x14);
      }
      if ((param_1 == luaI_breakhere) && (g_pLuaState[2] == 0)) {
        g_pLuaState[1] = iStack_14;
        return 1;
      }
    }
LAB_10004474:
    if (*g_pLuaState == iStack_14) {
      return 0;
    }
  } while( true );
}
#undef iStack_14

#endif


/* ---- 0x100044e0  ldo__44e0 ---- */
/* Unidentified function of ldo.c (stack and call machinery, Grim task marks) */

int __cdecl ldo__44e0(undefined *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  piVar5 = g_pLuaState;
  piVar1 = g_pLuaState + 10;
  iVar2 = *piVar1;
  iVar3 = g_pLuaState[0xb];
  iVar4 = g_pLuaState[0xc];
  iVar6 = (g_pLuaState[7] - g_pLuaState[8] >> 3) - param_2;
  g_pLuaState[0xb] = param_2;
  piVar5[0xc] = iVar6;
  *piVar1 = iVar6 + param_2;
  if (lua_callhook != 0) {
    luaD_callHook(param_2,0,0);
  }
  g_pLuaState[6] = g_pLuaState[6] + 1;
  (*(code *)param_1)();
  g_pLuaState[6] = g_pLuaState[6] + -1;
  if (lua_callhook != 0) {
    luaD_callHook(param_2,0,1);
  }
  iVar6 = *piVar1;
  *piVar1 = iVar2;
  piVar5[0xb] = iVar3;
  piVar5[0xc] = iVar4;
  return iVar6;
}

/* ---- 0x10004580  luaD_callC ---- */
/* Unidentified function of ldo.c (stack and call machinery, Grim task marks) */

int __cdecl luaD_callC(int param_1,undefined *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  uVar1 = *(uint *)(param_1 + 8);
  luaD_checkstack(uVar1);
  puVar4 = (undefined4 *)(g_pLuaState[8] + param_3 * 8);
  memcpy(puVar4 + uVar1 * 2,puVar4,(g_pLuaState[7] - (int)puVar4 >> 3) << 3);
  puVar3 = (undefined4 *)(param_1 + 0x14);
  for (iVar2 = (uVar1 & 0x1fffffff) << 1; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  g_pLuaState[7] = g_pLuaState[7] + uVar1 * 8;
  iVar2 = ldo__44e0(param_2,param_3);
  return iVar2;
}

/* ---- 0x10004600  luaD_travallstacks ---- */
/* Original name luaD_travallstacks (the remaster's libLua.so: walks every state (LState_next) and
   calls the function on each stack slot); was ldo__4600. */

void __cdecl luaD_travallstacks(undefined *param_1)

{
  int iVar1;
  int iVar2;
  
  for (iVar1 = g_dwL_Main; iVar1 != 0; iVar1 = LState_next(iVar1)) {
    for (iVar2 = (*(int *)(iVar1 + 0x1c) - *(int *)(iVar1 + 0x20)) + -8 >> 3; -1 < iVar2;
        iVar2 = iVar2 + -1) {
      (*(code *)param_1)(*(int *)(iVar1 + 0x20) + iVar2 * 8);
    }
  }
  return;
}

/* ---- 0x100046a0  luaD_message ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* ldo.c message(): pushes the string and calls the error tag method */

void __cdecl luaD_message(byte *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  local_4 = DAT_1002bf5c;
  if (g_dwLState_errorim != -7) {
    lua_pushstring(param_1);
    luaD_callTM(&local_4,1,(void *)0x0);
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
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  undefined4 uVar8;
  int in_stack_ffffffa8;
  undefined4 in_stack_ffffffac;
  
  iVar1 = g_pLuaState[10];
  iVar2 = g_pLuaState[0xb];
  iVar3 = g_pLuaState[0xd];
  iVar4 = g_pLuaState[0xc];
  iVar5 = *g_pLuaState;
  g_pLuaState[0xd] = (int)(_stkneg + 24);
  g_pLuaState[2] = g_pLuaState[2] + 1;
  iVar7 = _setjmp3((undefined4 *)(_stkneg + 24),0,in_stack_ffffffa8,in_stack_ffffffac);
  piVar6 = g_pLuaState;
  if (iVar7 == 0) {
    luaD_callinc(param_1);
    uVar8 = 0;
  }
  else {
    g_pLuaState[10] = iVar1;
    piVar6[0xb] = iVar2;
    piVar6[0xc] = iVar4;
    g_pLuaState[7] = g_pLuaState[8] + g_pLuaState[10] * 8;
    iVar1 = *g_pLuaState;
    while (iVar1 != iVar5) {
      *g_pLuaState = *(int *)(iVar1 + 0xc);
      ExecutionState_Delete(iVar1);
      iVar1 = *g_pLuaState;
    }
    uVar8 = 1;
  }
  g_pLuaState[0xd] = iVar3;
  g_pLuaState[2] = g_pLuaState[2] + -1;
  return uVar8;
}
#endif


/* ---- 0x100047c0  luaD_callinc ---- */
/* Unidentified function of ldo.c (stack and call machinery, Grim task marks) */

void __cdecl luaD_callinc(void *param_1)

{
  int iVar1;
  
  iVar1 = g_pLuaState[10];
  luaD_call(iVar1 + 1,param_1);
  g_pLuaState[0xb] = iVar1;
  g_pLuaState[0xc] = (g_pLuaState[7] - g_pLuaState[8] >> 3) - iVar1;
  g_pLuaState[10] = g_pLuaState[0xc] + iVar1;
  return;
}

/* ---- 0x10004810  luaD_gcIM ---- */
/* Calls the garbage-collection tag method of an object */

void __cdecl luaD_gcIM(uint *param_1)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = luaT_efectivetag(param_1);
  iVar3 = g_dwLState_IMtable + uVar2 * -0x90;
  if (*(int *)(iVar3 + 0x80) != -7) {
    puVar1 = (uint *)g_pLuaState[7];
    *puVar1 = *param_1;
    puVar1[1] = param_1[1];
    if ((uint)g_pLuaState[9] <= (uint)g_pLuaState[7]) {
      luaD_checkstack(1);
    }
    g_pLuaState[7] = g_pLuaState[7] + 8;
    luaD_callTM((undefined4 *)(iVar3 + 0x80),1,(void *)0x0);
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
  int iVar1;
  bool bVar2;
  int iVar3;
  int unaff_ESI;
  undefined4 in_stack_ffffffb8;
  
  iVar1 = g_pLuaState[0xd];
  g_pLuaState[0xd] = (int)(_stkneg + 24);
  iVar3 = _setjmp3((undefined4 *)(_stkneg + 24),0,unaff_ESI,in_stack_ffffffb8);
  if (iVar3 == 0) {
    if (param_2 == 0) {
      iVar3 = luaY_parser((int)param_1);
      bVar2 = false;
    }
    else {
      iVar3 = luaU_undump1(param_1);
      bVar2 = false;
    }
  }
  else {
    iVar3 = 0;
    bVar2 = true;
  }
  g_pLuaState[0xd] = iVar1;
  if (bVar2) {
    return 1;
  }
  if (iVar3 == 0) {
    return 2;
  }
  luaD_adjusttop(g_pLuaState[10] + 1);
  *(undefined4 *)(g_pLuaState[8] + g_pLuaState[10] * 8) = 0xfffffffc;
  *(int *)(g_pLuaState[8] + 4 + g_pLuaState[10] * 8) = iVar3;
  luaV_closure(0);
  return 0;
}
#endif

