/* LUA.DLL :: lstate.c
 * functions 0x100075e0 .. 0x10008c00 (18 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100075e0  LState_Construct ---- */
/* Original name LState_Construct (the remaster's libLua.so: LState::LState (constructor, __thiscall
   here): clears the state, serial number, allocates the 0x400-byte stack (assert file lstate.cpp));
   was lstate__75e0. */

undefined4 * __fastcall LState_Construct(undefined4 *param_1)

{
  int iVar1;
  
  param_1[0x2f] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[6] = 0;
  param_1[2] = 0;
  param_1[3] = 1;
  param_1[4] = 0;
  param_1[5] = 0;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[0x33] = 0;
  param_1[0x34] = 0;
  param_1[0x30] = g_dwLState_numThreads;
  g_dwLState_numThreads = g_dwLState_numThreads + 1;
  iVar1 = (**(code **)(g_dwLuaHS + 0x20))(0x400,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x10e);
  param_1[8] = iVar1;
  param_1[7] = iVar1;
  param_1[9] = iVar1 + 0x3f8;
  return param_1;
}

/* ---- 0x10007660  LState_SerialToPtr ---- */
/* Original name LState_SerialToPtr (the remaster's libLua.so: LState::SerialToPtr(TObject*): sorts
   the four pointer tables (qsort with comparePtrIDs) once and bsearches them; assert 'aStringPtrs
   && aClosurePtrs && aTablePtrs && aProtoPtrs'); was lstate__7660. */

undefined4 __stdcall LState_SerialToPtr(int a1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_8 = 0;
  iVar1 = *(int *)(a1 + 4);
  local_4 = 0;
  if ((((g_dwLState_aStringPtrs == (undefined1 *)0x0) ||
       (g_dwLState_aClosurePtrs == (undefined1 *)0x0)) ||
      (g_dwLState_aTablePtrs == (undefined1 *)0x0)) ||
     (puVar3 = g_dwLState_aStringPtrs, g_dwLState_aProtoPtrs == (undefined1 *)0x0)) {
    puVar3 = (undefined1 *)
             (**(code **)(g_dwLuaHS + 0x18))
                       (s_aStringPtrs____aClosurePtrs____a_100277f0,
                        s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x128);
  }
  if (g_dwLState_bPtrsSorted == 0) {
    qsort(g_dwLState_aStringPtrs,g_dwLState_stringPtrTotal,8,comparePtrIDs);
    qsort(g_dwLState_aClosurePtrs,g_dwLState_closurePtrTotal,8,comparePtrIDs);
    qsort(g_dwLState_aTablePtrs,g_dwLState_tablePtrTotal,8,comparePtrIDs);
    puVar3 = (undefined1 *)((code *)qsort)(g_dwLState_aProtoPtrs,g_dwLState_protoPtrTotal,8,comparePtrIDs);
    g_dwLState_bPtrsSorted = 1;
  }
  if (iVar1 == 0) goto LAB_100077c9;
  switch(*(undefined4 *)a1) {
  case 0xfffffff6:
  case 0xfffffffc:
    puVar3 = g_dwLState_aProtoPtrs;
    uVar5 = g_dwLState_protoPtrTotal;
    break;
  default:
    puVar4 = (undefined4 *)0x0;
    goto LAB_100077b7;
  case 0xfffffff8:
    puVar3 = g_dwLState_aClosurePtrs;
    uVar5 = g_dwLState_closurePtrTotal;
    break;
  case 0xfffffffd:
    puVar3 = g_dwLState_aTablePtrs;
    uVar5 = g_dwLState_tablePtrTotal;
    break;
  case 0xfffffffe:
  case 0:
    puVar3 = g_dwLState_aStringPtrs;
    uVar5 = g_dwLState_stringPtrTotal;
  }
  local_4 = iVar1;
  puVar4 = (undefined4 *)bsearch(&local_8,(uint)puVar3,uVar5,8,comparePtrIDs);
LAB_100077b7:
  puVar3 = (undefined1 *)0x0;
  if (puVar4 != (undefined4 *)0x0) {
    uVar2 = *puVar4;
    *(undefined4 *)(a1 + 4) = uVar2;
    return uVar2;
  }
LAB_100077c9:
  *(undefined4 *)(a1 + 4) = 0;
  return puVar3;
}
#undef local_4
#undef local_8


/* ---- 0x10007810  comparePtrIDs ---- */
/* Original name comparePtrIDs (the remaster's libLua.so: static comparePtrIDs: compares the ids at
   +4); was FUN_10007810. */

uint __cdecl comparePtrIDs(int param_1,int param_2)

{
  if (*(uint *)(param_1 + 4) < *(uint *)(param_2 + 4)) {
    return 0xffffffff;
  }
  return (uint)(*(uint *)(param_2 + 4) < *(uint *)(param_1 + 4));
}

/* ---- 0x10007830  LState_SaveObject ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name LState_SaveObject (the remaster's libLua.so: LState::SaveObject(TObject*, writer):
   writes tag and value, a C function as lua_FuncPtrToID); was lstate__7830. */

undefined4 __stdcall LState_SaveObject(int a1,int a2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = a2;
  iVar1 = a1;
  (*(code *)a2)(a1,4);
  if (*(int *)iVar1 != -5) {
    uVar3 = (*(code *)iVar2)(iVar1 + 4,4);
    return uVar3;
  }
  a1 = lua_FuncPtrToID(*(int *)(iVar1 + 4));
  uVar3 = (*(code *)iVar2)(&a1,4);
  return uVar3;
}
#endif


/* ---- 0x10007880  LState_LoadObject ---- */
/* Original name LState_LoadObject (the remaster's libLua.so: LState::LoadObject(TObject*, reader):
   reads tag and value); was lstate__7880. */

undefined4 __stdcall LState_LoadObject(int a1,int a2)

{
  undefined4 uVar1;
  
  (*(code *)a2)(a1,4);
  uVar1 = (*(code *)a2)(a1 + 4,4);
  return uVar1;
}

/* ---- 0x100078b0  LState_ResolveObject ---- */
/* Original name LState_ResolveObject (the remaster's libLua.so: LState::ResolveObject(TObject*): C
   functions through lua_IDToFuncPtr, other pointers through SerialToPtr); was lstate__78b0. */

int __stdcall LState_ResolveObject(int a1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)a1 + 0xc;
  switch(*(int *)a1) {
  case -0xc:
  case -7:
  case -6:
  case -1:
    goto switchD_100078c7_caseD_fffffff4;
  default:
    iVar1 = LState_SerialToPtr(a1);
switchD_100078c7_caseD_fffffff4:
    return iVar1;
  case -5:
    uVar2 = lua_IDToFuncPtr(*(uint *)(a1 + 4));
    *(undefined4 *)(a1 + 4) = uVar2;
    return uVar2;
  }
}

/* ---- 0x10007910  LState_LoadResolvedObject ---- */
/* Original name LState_LoadResolvedObject (the remaster's libLua.so: LState::LoadResolvedObject:
   LoadObject + ResolveObject); was lstate__7910. */

undefined4 __stdcall LState_LoadResolvedObject(int a1,int a2)

{
  undefined4 uVar1;
  
  LState_LoadObject(a1,a2);
  uVar1 = LState_ResolveObject(a1);
  return uVar1;
}

/* ---- 0x10007930  LState_GlobalEndRestore ---- */
/* Original name LState_GlobalEndRestore (the remaster's libLua.so: LState::GlobalEndRestore: frees
   the four pointer tables, clears the sorted flag (same body)); was lstate__7930. */

undefined4 __stdcall LState_GlobalEndRestore(int a1)

{
  if (g_dwLState_aStringPtrs != 0) {
    (**(code **)(g_dwLuaHS + 0x24))(g_dwLState_aStringPtrs);
    g_dwLState_stringPtrTotal = 0;
    g_dwLState_aStringPtrs = 0;
  }
  if (g_dwLState_aClosurePtrs != 0) {
    (**(code **)(g_dwLuaHS + 0x24))(g_dwLState_aClosurePtrs);
    g_dwLState_closurePtrTotal = 0;
    g_dwLState_aClosurePtrs = 0;
  }
  if (g_dwLState_aTablePtrs != 0) {
    (**(code **)(g_dwLuaHS + 0x24))(g_dwLState_aTablePtrs);
    g_dwLState_tablePtrTotal = 0;
    g_dwLState_aTablePtrs = 0;
  }
  if (g_dwLState_aProtoPtrs != 0) {
    (**(code **)(g_dwLuaHS + 0x24))(g_dwLState_aProtoPtrs);
    g_dwLState_protoPtrTotal = 0;
    g_dwLState_aProtoPtrs = 0;
  }
  g_dwLState_bPtrsSorted = 0;
  return 0;
}

/* ---- 0x100079d0  LState_GlobalBeginRestore ---- */
/* Original name LState_GlobalBeginRestore (the remaster's libLua.so: LState::GlobalBeginRestore:
   assert 'pTString'); was lstate__79d0. */

undefined4 __stdcall LState_GlobalBeginRestore(int a1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  Hash *t;
  int a2;
  undefined4 *puVar2;
  char *str;
  TaggedString *pTVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  #define puStack_2c (*(undefined4 **)(_frame + (0x40 - 0x2c)))
  #define puStack_28 (*(undefined4 **)(_frame + (0x40 - 0x28)))
  #define puStack_24 (*(undefined4 **)(_frame + (0x40 - 0x24)))
  #define local_20 (*(int *)(_frame + (0x40 - 0x20)))
  #define pvStack_1c (*(void **)(_frame + (0x40 - 0x1c)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x40 - 0x18)))
  #define iStack_14 (*(int *)(_frame + (0x40 - 0x14)))
  #define puStack_10 (*(undefined4 **)(_frame + (0x40 - 0x10)))
  #define uStack_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define iStack_8 (*(int *)(_frame + (0x40 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x40 - 0x4)))
  
  a2 = a1;
  (*(code *)a1)(&g_dwLState_stringPtrTotal,4);
  (*(code *)a1)(&g_dwLState_closurePtrTotal,4);
  (*(code *)a1)(&g_dwLState_tablePtrTotal,4);
  (*(code *)a1)(&g_dwLState_protoPtrTotal,4);
  (*(code *)a1)(&uStack_c,4);
  puVar2 = (undefined4 *)
           (**(code **)(g_dwLuaHS + 0x20))
                     (g_dwLState_stringPtrTotal * 8,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,
                      0x1cf);
  g_dwLState_aStringPtrs = puVar2;
  (*(code *)a1)(&iStack_8,4);
  str = (char *)(**(code **)(g_dwLuaHS + 0x20))
                          (iStack_8 + 5,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x1d3);
  a1 = 0;
  if (g_dwLState_stringPtrTotal != 0) {
    puStack_2c = puVar2 + 1;
    do {
      (*(code *)a2)(puStack_2c,4);
      (*(code *)a2)(&iStack_14,4);
      (*(code *)a2)(&puStack_28,4);
      (*(code *)a2)(&pvStack_1c,4);
      if (iStack_14 == -1) {
        puVar4 = puStack_28;
        if (puStack_28 == (undefined4 *)0x0) {
          puVar4 = (undefined4 *)0xffffffff;
        }
        pTVar3 = luaS_createudata(pvStack_1c,(int)puVar4);
        if (lua_restorehook != (code *)0x0) {
          uVar7 = (*lua_restorehook)((pTVar3->globalval).nTtype,(pTVar3->globalval).dwValue,a2);
          (pTVar3->globalval).dwValue = uVar7;
        }
      }
      else {
        (*(code *)a2)(&puStack_24,4);
        (*(code *)a2)(str,puStack_24);
        *(char *)((int)puStack_24 + (int)str) = '\0';
        pTVar3 = luaS_new(str);
        (pTVar3->globalval).dwValue = (uint)pvStack_1c;
        (pTVar3->globalval).nTtype = (int)puStack_28;
      }
      pTVar3->nConstIndex = iStack_14;
      *puVar2 = pTVar3;
      puStack_2c = puStack_2c + 2;
      a1 = a1 + 1;
      puVar2 = puVar2 + 2;
    } while ((uint)a1 < g_dwLState_stringPtrTotal);
  }
  (**(code **)(g_dwLuaHS + 0x24))(str);
  g_dwLState_aClosurePtrs =
       (undefined4 *)
       (**(code **)(g_dwLuaHS + 0x20))
                 (g_dwLState_closurePtrTotal * 8,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x207);
  a1 = 0;
  if (g_dwLState_closurePtrTotal != 0) {
    puStack_28 = g_dwLState_aClosurePtrs + 1;
    puStack_2c = g_dwLState_aClosurePtrs;
    do {
      (*(code *)a2)(puStack_28,4);
      (*(code *)a2)(&iStack_14,4);
      puVar4 = (undefined4 *)
               (**(code **)(g_dwLuaHS + 0x20))
                         (iStack_14 * 8 + 0x14,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x211);
      luaO_insertlist(&g_dwLState_rootcl,puVar4);
      puVar4[2] = iStack_14;
      uVar7 = 0;
      puVar2 = puVar4 + 3;
      do {
        LState_LoadObject((int)puVar2,a2);
        uVar7 = uVar7 + 1;
        puVar2 = puVar2 + 2;
      } while (uVar7 <= (uint)puVar4[2]);
      *puStack_2c = puVar4;
      puStack_2c = puStack_2c + 2;
      puStack_28 = puStack_28 + 2;
      a1 = a1 + 1;
    } while ((uint)a1 < g_dwLState_closurePtrTotal);
  }
  puVar2 = (undefined4 *)
           (**(code **)(g_dwLuaHS + 0x20))
                     (g_dwLState_tablePtrTotal * 8,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x220
                     );
  uVar7 = 0;
  g_dwLState_aTablePtrs = puVar2;
  if (g_dwLState_tablePtrTotal != 0) {
    puVar4 = puVar2 + 1;
    do {
      (*(code *)a2)(puVar4,4);
      puVar5 = luaH_load((undefined *)a2);
      *puVar2 = puVar5;
      puVar2 = puVar2 + 2;
      puVar4 = puVar4 + 2;
      uVar7 = uVar7 + 1;
    } while (uVar7 < g_dwLState_tablePtrTotal);
  }
  g_dwLState_aProtoPtrs =
       (undefined4 *)
       (**(code **)(g_dwLuaHS + 0x20))
                 (g_dwLState_protoPtrTotal * 8,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x22c);
  a1 = 0;
  if (g_dwLState_protoPtrTotal != 0) {
    puStack_24 = g_dwLState_aProtoPtrs + 1;
    puStack_2c = g_dwLState_aProtoPtrs;
    do {
      (*(code *)a2)(puStack_24,4);
      puVar2 = (undefined4 *)
               (**(code **)(g_dwLuaHS + 0x20))
                         (0x20,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x235);
      luaO_insertlist(&g_dwLState_rootproto,puVar2);
      (*(code *)a2)(puVar2 + 6,4);
      (*(code *)a2)(puVar2 + 5,4);
      puVar1 = puVar2 + 3;
      (*(code *)a2)(puVar1,4);
      uVar6 = (**(code **)(g_dwLuaHS + 0x20))
                        (*puVar1 << 3,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x23a);
      puVar2[2] = uVar6;
      uVar7 = 0;
      if (*puVar1 != 0) {
        do {
          LState_LoadObject(puVar2[2] + uVar7 * 8,a2);
          uVar7 = uVar7 + 1;
        } while (uVar7 < *puVar1);
      }
      (*(code *)a2)(&puStack_28,4);
      puVar4 = (undefined4 *)0x0;
      if (puStack_28 == (undefined4 *)0x0) {
        puVar2[7] = 0;
      }
      else {
        uVar6 = (**(code **)(g_dwLuaHS + 0x20))
                          ((int)puStack_28 * 8,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x244);
        puVar2[7] = uVar6;
      }
      if (puStack_28 != (undefined4 *)0x0) {
        do {
          (*(code *)a2)(puVar2[7] + (int)puVar4 * 8,4);
          (*(code *)a2)(puVar2[7] + 4 + (int)puVar4 * 8,4);
          puVar4 = (undefined4 *)((int)puVar4 + 1);
        } while (puVar4 < puStack_28);
      }
      (*(code *)a2)(&iStack_14,4);
      uVar6 = (**(code **)(g_dwLuaHS + 0x20))
                        (iStack_14,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x250);
      puVar2[4] = uVar6;
      (*(code *)a2)(uVar6,iStack_14);
      *puStack_2c = puVar2;
      puStack_2c = puStack_2c + 2;
      puStack_24 = puStack_24 + 2;
      a1 = a1 + 1;
    } while ((uint)a1 < g_dwLState_protoPtrTotal);
  }
  luaS_resolvestrings(g_dwLState_string_root);
  for (puVar2 = g_dwLState_rootproto; t = g_dwLState_roottable, puVar2 != (undefined4 *)0x0;
      puVar2 = (undefined4 *)*puVar2) {
    iStack_14 = -2;
    puStack_10 = (undefined4 *)puVar2[6];
    LState_ResolveObject((int)&iStack_14);
    uVar7 = 0;
    puVar2[6] = puStack_10;
    if (puVar2[3] != 0) {
      do {
        LState_ResolveObject(puVar2[2] + uVar7 * 8);
        uVar7 = uVar7 + 1;
      } while (uVar7 < (uint)puVar2[3]);
    }
    puVar4 = (undefined4 *)puVar2[7];
    if ((puVar4 != (undefined4 *)0x0) && (puVar4[1] != -1)) {
      iVar8 = 0;
      do {
        pvStack_1c = (void *)0xfffffffe;
        uStack_18 = *puVar4;
        LState_ResolveObject((int)&pvStack_1c);
        *(undefined4 *)(puVar2[7] + iVar8) = uStack_18;
        iVar8 = iVar8 + 8;
        puVar4 = (undefined4 *)(puVar2[7] + iVar8);
      } while (puVar4[1] != -1);
    }
  }
  for (; puVar2 = g_dwLState_rootcl, t != (Hash *)0x0; t = t->pNext) {
    uVar7 = 0;
    if (t->nNuse != 0) {
      iVar8 = 0;
      do {
        LState_ResolveObject((int)&(t->pNode->ref).nTtype + iVar8);
        LState_ResolveObject((int)&(t->pNode->val).nTtype + iVar8);
        uVar7 = uVar7 + 1;
        iVar8 = iVar8 + 0x10;
      } while (uVar7 < (uint)t->nNuse);
    }
    luaH_forcerehash(t);
  }
  for (; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2) {
    uVar7 = 0;
    puVar4 = puVar2 + 3;
    do {
      LState_ResolveObject((int)puVar4);
      uVar7 = uVar7 + 1;
      puVar4 = puVar4 + 2;
    } while (uVar7 <= (uint)puVar2[2]);
  }
  uVar7 = 0;
  puVar2 = &g_dwLState_rootglobal;
  puVar4 = puVar2;
  if (uStack_c != 0) {
    do {
      iStack_14 = -2;
      (*(code *)a2)(&puStack_10,4);
      LState_ResolveObject((int)&iStack_14);
      puVar2 = puStack_10;
      if (puStack_10 == (undefined4 *)0x0) {
        (**(code **)(g_dwLuaHS + 0x18))
                  (s_pTString_10027828,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x2aa);
      }
      *puVar4 = puVar2;
      uVar7 = uVar7 + 1;
      puVar4 = puVar2;
    } while (uVar7 < uStack_c);
  }
  *puVar2 = 0;
  (*(code *)a2)(&g_dwLState_lstate_class_initialized,4);
  LState_LoadResolvedObject(((unsigned)(uintptr_t)&g_dwLState_errorim),a2);
  (*(code *)a2)(&g_dwLState_IMtable_size,4);
  g_dwLState_IMtable =
       (**(code **)(g_dwLuaHS + 0x20))
                 (g_dwLState_IMtable_size * 0x90,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x2b6);
  a1 = 0;
  if (g_dwLState_IMtable_size != 0) {
    local_20 = 0;
    do {
      iVar9 = 0x12;
      iVar8 = g_dwLState_IMtable + local_20;
      do {
        LState_LoadResolvedObject(iVar8,a2);
        iVar8 = iVar8 + 8;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
      a1 = a1 + 1;
      local_20 = local_20 + 0x90;
    } while ((uint)a1 < g_dwLState_IMtable_size);
  }
  (*(code *)a2)(&g_dwLState_last_tag,4);
  (*(code *)a2)(&g_dwLState_refSize,4);
  g_dwLState_refArray =
       (**(code **)(g_dwLuaHS + 0x20))
                 (g_dwLState_refSize * 0xc,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x2c2);
  uVar7 = 0;
  if (g_dwLState_refSize != 0) {
    iVar8 = 0;
    do {
      LState_LoadResolvedObject(g_dwLState_refArray + iVar8,a2);
      (*(code *)a2)(g_dwLState_refArray + 8 + iVar8,4);
      uVar7 = uVar7 + 1;
      iVar8 = iVar8 + 0xc;
    } while (uVar7 < g_dwLState_refSize);
  }
  (*(code *)a2)(&g_dwLState_GCthreshold,4);
  (*(code *)a2)(&g_dwLState_nblocks,4);
  (*(code *)a2)(&g_dwLState_Mbuffsize,4);
  g_dwLState_Mbuffer =
       (**(code **)(g_dwLuaHS + 0x20))
                 (g_dwLState_Mbuffsize,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x2ce);
  (*(code *)a2)(g_dwLState_Mbuffer,g_dwLState_Mbuffsize);
  (*(code *)a2)(&iStack_4,4);
  g_dwLState_Mbuffbase = iStack_4 + g_dwLState_Mbuffer;
  (*(code *)a2)(&g_dwLState_Mbuffnext,4);
  (*(code *)a2)(&g_dwLState_numThreads,4);
  return 0;
}
#undef iStack_14
#undef iStack_4
#undef iStack_8
#undef local_20
#undef puStack_10
#undef puStack_24
#undef puStack_28
#undef puStack_2c
#undef pvStack_1c
#undef uStack_18
#undef uStack_c


/* ---- 0x100081c0  LState_SaveGlobals ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name LState_SaveGlobals (the remaster's libLua.so: LState::SaveGlobals(writer):
   luaA_ResetSaveCount, luaS_writestrings, luaH_save, SaveObject (caller lua_Save)); was
   lstate__81c0. */

undefined4 __stdcall LState_SaveGlobals(int a1)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  undefined4 *puVar2;
  int a2;
  int iVar3;
  uint uVar4;
  int iVar5;
  #define puStack_34 (*(undefined4 **)(_frame + (0x50 - 0x34)))
  #define puStack_30 (*(undefined4 **)(_frame + (0x50 - 0x30)))
  #define puStack_2c (*(undefined4 **)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(int *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(int *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(int *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(int *)(_frame + (0x50 - 0x1c)))
  #define apuStack_18 (*(undefined4 *(*)[2])(_frame + (0x50 - 0x18)))
  #define local_10 (*(int *)(_frame + (0x50 - 0x10)))
  #define pbStack_c (*(byte **)(_frame + (0x50 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x50 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x50 - 0x4)))
  
  local_1c = 0;
  local_20 = 0;
  local_28 = 0;
  local_24 = 0;
  local_10 = 0;
  local_10 = luaS_count(g_dwLState_string_root,&local_8);
  a2 = a1;
  for (puVar1 = g_dwLState_rootcl; puVar2 = g_dwLState_roottable, puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    local_28 = local_28 + 1;
  }
  for (; puVar1 = g_dwLState_rootproto, puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2)
  {
    local_24 = local_24 + 1;
  }
  for (; puVar2 = g_dwLState_rootglobal, puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1
      ) {
    local_20 = local_20 + 1;
  }
  for (; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2) {
    local_1c = local_1c + 1;
  }
  (*(code *)a1)(&local_10,4);
  (*(code *)a2)(&local_28,4);
  (*(code *)a2)(&local_24,4);
  (*(code *)a2)(&local_20,4);
  (*(code *)a2)(&local_1c,4);
  (*(code *)a2)(&local_8,4);
  luaA_ResetSaveCount();
  luaS_writestrings((undefined *)a2,g_dwLState_string_root);
  luaA_ResetSaveCount();
  for (puStack_30 = g_dwLState_rootcl; puStack_30 != (undefined4 *)0x0;
      puStack_30 = (undefined4 *)*puStack_30) {
    (*(code *)a2)(&puStack_30,4);
    (*(code *)a2)(puStack_30 + 2,4);
    uVar4 = 0;
    do {
      LState_SaveObject((int)(puStack_30 + uVar4 * 2 + 3),a2);
      uVar4 = uVar4 + 1;
    } while (uVar4 <= (uint)puStack_30[2]);
  }
  luaA_ResetSaveCount();
  for (puStack_2c = g_dwLState_roottable; puStack_2c != (undefined4 *)0x0;
      puStack_2c = (undefined4 *)*puStack_2c) {
    (*(code *)a2)(&puStack_2c,4);
    luaH_save((undefined *)a2,(int)puStack_2c);
  }
  luaA_ResetSaveCount();
  for (puStack_34 = g_dwLState_rootproto; puStack_34 != (undefined4 *)0x0;
      puStack_34 = (undefined4 *)*puStack_34) {
    (*(code *)a2)(&puStack_34,4);
    (*(code *)a2)(puStack_34 + 6,4);
    (*(code *)a2)(puStack_34 + 5,4);
    (*(code *)a2)(puStack_34 + 3,4);
    uVar4 = 0;
    if (puStack_34[3] != 0) {
      do {
        LState_SaveObject(puStack_34[2] + uVar4 * 8,a2);
        uVar4 = uVar4 + 1;
      } while (uVar4 < (uint)puStack_34[3]);
    }
    a1 = 0;
    if (puStack_34[7] != 0) {
      a1 = 1;
      iVar5 = *(int *)(puStack_34[7] + 4);
      while (iVar5 != -1) {
        a1 = a1 + 1;
        iVar5 = *(int *)(puStack_34[7] + -4 + a1 * 8);
      }
    }
    (*(code *)a2)(&a1,4);
    uVar4 = 0;
    if (a1 != 0) {
      do {
        (*(code *)a2)(puStack_34[7] + uVar4 * 8,4);
        (*(code *)a2)(puStack_34[7] + 4 + uVar4 * 8,4);
        uVar4 = uVar4 + 1;
      } while (uVar4 < (uint)a1);
    }
    pbStack_c = lstate__85e0((int)puStack_34);
    (*(code *)a2)(&pbStack_c,4);
    (*(code *)a2)(puStack_34[4],pbStack_c);
  }
  luaA_ResetSaveCount();
  puVar2 = g_dwLState_rootglobal;
  puVar1 = _DAT_1002bf0c;
  while (_DAT_1002bf0c = puVar2, apuStack_18[0] = _DAT_1002bf0c, _DAT_1002bf0c != (undefined4 *)0x0)
  {
    (*(code *)a2)(apuStack_18,4);
    puVar1 = _DAT_1002bf0c;
    puVar2 = (undefined4 *)*apuStack_18[0];
  }
  _DAT_1002bf0c = puVar1;
  luaA_ResetSaveCount();
  (*(code *)a2)(&g_dwLState_lstate_class_initialized,4);
  LState_SaveObject(((unsigned)(uintptr_t)&g_dwLState_errorim),a2);
  (*(code *)a2)(&g_dwLState_IMtable_size,4);
  uVar4 = 0;
  iVar5 = g_dwLState_IMtable;
  if (g_dwLState_IMtable_size != 0) {
    do {
      iVar3 = 0x12;
      do {
        LState_SaveObject(iVar5,a2);
        iVar5 = iVar5 + 8;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      uVar4 = uVar4 + 1;
    } while (uVar4 < g_dwLState_IMtable_size);
  }
  uVar4 = 0;
  (*(code *)a2)(&g_dwLState_last_tag,4);
  (*(code *)a2)(&g_dwLState_refSize,4);
  if (g_dwLState_refSize != 0) {
    iVar5 = 0;
    do {
      LState_SaveObject(g_dwLState_refArray + iVar5,a2);
      (*(code *)a2)(g_dwLState_refArray + 8 + iVar5,4);
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 0xc;
    } while (uVar4 < g_dwLState_refSize);
  }
  (*(code *)a2)(&g_dwLState_GCthreshold,4);
  (*(code *)a2)(&g_dwLState_nblocks,4);
  (*(code *)a2)(&g_dwLState_Mbuffsize,4);
  (*(code *)a2)(g_dwLState_Mbuffer,g_dwLState_Mbuffsize);
  iStack_4 = g_dwLState_Mbuffbase - g_dwLState_Mbuffer;
  (*(code *)a2)(&iStack_4,4);
  (*(code *)a2)(&g_dwLState_Mbuffnext,4);
  (*(code *)a2)(&g_dwLState_numThreads,4);
  luaA_ResetSaveCount();
  return 0;
}
#undef apuStack_18
#undef iStack_4
#undef local_10
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_8
#undef pbStack_c
#undef puStack_2c
#undef puStack_30
#undef puStack_34


/* ---- 0x100085e0  lstate__85e0 ---- */
/* Unidentified function of lstate.c (Grim execution states / tasks) */

byte * __cdecl lstate__85e0(int param_1)

{
  uint uVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  pbVar2 = (byte *)(*(int *)(param_1 + 0x10) + 2);
  pbVar3 = pbVar2;
  do {
    uVar1 = (uint)*pbVar3;
    if (0x80 < uVar1) {
      (**(code **)(g_dwLuaHS + 0x18))
                (s_op____sizeof_opcodeDirectory__si_10027834,
                 s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0xef);
    }
    pbVar3 = pbVar3 + *(int *)(&g_aOpcodeDirectory + uVar1 * 0xc);
  } while (uVar1 != 0);
  return pbVar3 + (2 - (int)pbVar2);
}

/* ---- 0x10008640  LState_Save ---- */
/* Original name LState_Save (the remaster's libLua.so: LState::Save(writer): assert
   'pExecutionState || !pPreviousState'); was lstate__8640. */

undefined4 __thiscall LState_Save(void *this,int a1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define iStack_c (*(int *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_8 = 0;
  local_4 = -1;
  if ((*(int *)this == 0) && (*(int *)((int)this + 4) != 0)) {
    (**(code **)(g_dwLuaHS + 0x18))
              (s_pExecutionState_____pPreviousSta_10027870,
               s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x39e);
  }
  iVar1 = *(int *)this;
  if (iVar1 != 0) {
    do {
      if ((*(int *)((int)this + 4) != 0) && (*(int *)((int)this + 4) == iVar1)) {
        local_4 = local_8;
      }
      local_8 = local_8 + 1;
      iVar1 = *(int *)(iVar1 + 0xc);
    } while (iVar1 != 0);
  }
  (*(code *)a1)(&local_8,4);
  if (*(void **)this != (void *)0x0) {
    ExecutionState_Save(*(void **)this,a1);
  }
  (*(code *)a1)(&local_4,4);
  (*(code *)a1)((int)this + 8,4);
  (*(code *)a1)((int)this + 0xc,4);
  (*(code *)a1)((int)this + 0x10,4);
  (*(code *)a1)((int)this + 0x14,4);
  (*(code *)a1)((int)this + 0x18,4);
  iStack_c = (*(int *)((int)this + 0x24) - *(int *)((int)this + 0x20) >> 3) + 1;
  (*(code *)a1)(&iStack_c,4);
  iStack_c = *(int *)((int)this + 0x1c) - *(int *)((int)this + 0x20) >> 3;
  (*(code *)a1)(&iStack_c,4);
  iVar1 = 0;
  if (0 < iStack_c) {
    do {
      LState_SaveObject(*(int *)((int)this + 0x20) + iVar1 * 8,a1);
      iVar1 = iVar1 + 1;
    } while (iVar1 < iStack_c);
  }
  (*(code *)a1)((int)this + 0x28,4);
  (*(code *)a1)((int)this + 0x2c,4);
  (*(code *)a1)((int)this + 0x30,4);
  (*(code *)a1)((int *)((int)this + 0xbc),4);
  iVar1 = 0;
  if (0 < *(int *)((int)this + 0xbc)) {
    iVar2 = (int)this + 0x48;
    do {
      (*(code *)a1)(iVar2 + -4,4);
      (*(code *)a1)(iVar2,4);
      (*(code *)a1)(iVar2 + 4,4);
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 0xc;
    } while (iVar1 < *(int *)((int)this + 0xbc));
  }
  (*(code *)a1)((int)this + 0xc0,4);
  LState_SaveObject((int)this + 0xc4,a1);
  return 0;
}
#undef iStack_c
#undef local_4
#undef local_8


/* ---- 0x100087f0  LState_Restore ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name LState_Restore (the remaster's libLua.so: LState::Restore(reader): caller
   lua_Restore, restores the execution states (ExecutionState_Restore / _New)); was lstate__87f0. */

undefined4 __thiscall LState_Restore(void *this,int a1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  int a1_00;
  void *this_00;
  int iVar2;
  int iVar3;
  #define local_1c (*(int *)(_frame + (0x30 - 0x1c)))
  #define iStack_18 (*(int *)(_frame + (0x30 - 0x18)))
  #define iStack_14 (*(int *)(_frame + (0x30 - 0x14)))
  #define pvStack_10 (*(void **)(_frame + (0x30 - 0x10)))
  
  a1_00 = a1;
  iVar3 = 0;
  local_1c = 0;
  (*(code *)a1)(&local_1c,4);
  if (local_1c == 0) {
    *(undefined4 *)this = 0;
  }
  else {
    pvStack_10 = ExecutionState_New(0x30);
    if (pvStack_10 == (void *)0x0) {
      this_00 = (void *)0x0;
    }
    else {
      this_00 = (void *)ExecutionState_Construct(pvStack_10,0,0,0);
    }
    *(void **)this = this_00;
    ExecutionState_Restore(this_00,a1_00,(int)this + 0x1c,local_1c + -1);
  }
  (*(code *)a1_00)(&a1,4);
  if (a1 < 0) {
    *(undefined4 *)((int)this + 4) = 0;
  }
  else {
    iVar2 = *(int *)this;
    while (bVar1 = a1 != 0, a1 = a1 + -1, bVar1) {
      iVar2 = *(int *)(iVar2 + 0xc);
    }
    *(int *)((int)this + 4) = iVar2;
    a1 = -1;
  }
  (*(code *)a1_00)((int)this + 8,4);
  (*(code *)a1_00)((int)this + 0xc,4);
  (*(code *)a1_00)((int)this + 0x10,4);
  (*(code *)a1_00)((int)this + 0x14,4);
  (*(code *)a1_00)((int)this + 0x18,4);
  (*(code *)a1_00)(&iStack_18,4);
  if (*(int *)((int)this + 0x20) != 0) {
    (**(code **)(g_dwLuaHS + 0x24))(*(int *)((int)this + 0x20));
  }
  iVar2 = (**(code **)(g_dwLuaHS + 0x20))
                    (iStack_18 * 8,s_C__grimsrc_libs_lua_src_lstate_c_100277cc,0x41e);
  *(int *)((int)this + 0x20) = iVar2;
  *(int *)((int)this + 0x24) = iVar2 + -8 + iStack_18 * 8;
  (*(code *)a1_00)(&iStack_14,4);
  iVar2 = 0;
  *(int *)((int)this + 0x1c) = *(int *)((int)this + 0x20) + iStack_14 * 8;
  if (0 < iStack_14) {
    do {
      LState_LoadResolvedObject(*(int *)((int)this + 0x20) + iVar2 * 8,a1_00);
      iVar2 = iVar2 + 1;
    } while (iVar2 < iStack_14);
  }
  (*(code *)a1_00)((int)this + 0x28,4);
  (*(code *)a1_00)((int)this + 0x2c,4);
  (*(code *)a1_00)((int)this + 0x30,4);
  (*(code *)a1_00)((int *)((int)this + 0xbc),4);
  if (0 < *(int *)((int)this + 0xbc)) {
    iVar2 = (int)this + 0x48;
    do {
      (*(code *)a1_00)(iVar2 + -4,4);
      (*(code *)a1_00)(iVar2,4);
      (*(code *)a1_00)(iVar2 + 4,4);
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 0xc;
    } while (iVar3 < *(int *)((int)this + 0xbc));
  }
  (*(code *)a1_00)((int)this + 0xc0,4);
  LState_LoadResolvedObject((int)this + 0xc4,a1_00);
  return 0;
}
#undef iStack_14
#undef iStack_18
#undef local_1c
#undef pvStack_10

#endif


/* ---- 0x10008ad0  lua_newstate ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name lua_newstate (the remaster's libLua.so: lua_newstate(): new LState (0xd4 bytes),
   initglobals; only callee of lua_open); was lstate__8ad0. */

undefined4 * lua_newstate(void)

{
  int *piVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  piVar1 = g_pLuaState;
  puVar2 = luaM_malloc(0xd4);
  piVar3 = (int *)0x0;
  if (puVar2 != (undefined4 *)0x0) {
    piVar3 = LState_Construct(puVar2);
  }
  g_pLuaState = piVar3;
  LState_initglobals();
  g_pLuaState = piVar1;
  return piVar3;
}
#endif


/* ---- 0x10008b70  LState_attach ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name LState_attach (the remaster's libLua.so: LState::attach(LState*): links the state
   after another (+0xcc next, +0xd0 prev)); was lstate__8b70. */

int __thiscall LState_attach(void *this,int a1)

{
  int extraout_EAX;
  int iVar1;
  
  LState_detach((int)this);
  iVar1 = extraout_EAX;
  if (a1 != 0) {
    iVar1 = *(int *)(a1 + 0xcc);
    *(int *)((int)this + 0xcc) = iVar1;
    if (iVar1 != 0) {
      *(void **)(iVar1 + 0xd0) = this;
    }
    *(void **)(a1 + 0xcc) = this;
    *(int *)((int)this + 0xd0) = a1;
  }
  return iVar1;
}
#endif


/* ---- 0x10008bb0  LState_detach ---- */
/* Original name LState_detach (the remaster's libLua.so: LState::detach: unlinks the state); was
   lstate__8bb0. */

void __fastcall LState_detach(int param_1)

{
  if (*(int *)(param_1 + 0xd0) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xd0) + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
  }
  if (*(int *)(param_1 + 0xcc) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xcc) + 0xd0) = *(undefined4 *)(param_1 + 0xd0);
  }
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 0xd0) = 0;
  return;
}

/* ---- 0x10008bf0  LState_next ---- */
/* Original name LState_next (the remaster's libLua.so: LState::next: returns +0xcc); was
   lstate__8bf0. */

undefined4 __fastcall LState_next(int param_1)

{
  return *(undefined4 *)(param_1 + 0xcc);
}

/* ---- 0x10008c00  LState_Destruct ---- */
/* Original name LState_Destruct (the remaster's libLua.so: LState::~LState: detach,
   luaD_deletestates, frees the stack); was lstate__8c00. */

void __fastcall LState_Destruct(int *param_1)

{
  LState_detach((int)param_1);
  if (*param_1 != 0) {
    luaD_deletestates(*param_1);
  }
  (**(code **)(g_dwLuaHS + 0x24))(param_1[8]);
  return;
}
