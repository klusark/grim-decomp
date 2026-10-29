/* LUA.DLL :: ltable.c
 * functions 0x1000c190 .. 0x1000c810 (15 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000c190  ltable__c190 ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

void __cdecl ltable__c190(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  while (param_1 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*param_1;
    DAT_1002beec = DAT_1002beec + (-1 - ((uint)param_1[3] >> 4));
    ltable__c1d0((int)param_1);
    param_1 = puVar1;
  }
  return;
}

/* ---- 0x1000c1d0  ltable__c1d0 ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

void __cdecl ltable__c1d0(int param_1)

{
  (**(code **)(DAT_1002beb8 + 0x24))(*(undefined4 *)(param_1 + 8));
  (**(code **)(DAT_1002beb8 + 0x24))(param_1);
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
        lstate__7830(a1,(int)param_1);
        lstate__7830(*(int *)(param_2 + 8) + 8 + iVar2,(int)param_1);
        local_4 = local_4 + 1;
      }
      uVar3 = uVar3 + 1;
      iVar2 = iVar2 + 0x10;
    } while (uVar3 < *(uint *)(param_2 + 0xc));
  }
  if (local_4 != local_8) {
    (**(code **)(DAT_1002beb8 + 0x18))
              (s_writtenItems____numItems_10027cd8,s_C__grimsrc_libs_lua_src_ltable_c_10027cf4,0x8a)
    ;
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x1000c2e0  luaH_new ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

undefined4 * __cdecl luaH_new(undefined *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  puVar1 = (undefined4 *)
           (**(code **)(DAT_1002beb8 + 0x20))(0x18,s_C__grimsrc_libs_lua_src_ltable_c_10027cf4,0x91)
  ;
  (*(code *)param_1)(puVar1 + 3,4);
  (*(code *)param_1)(puVar1 + 4,4);
  (*(code *)param_1)(puVar1 + 5,4);
  uVar2 = luaH_free(puVar1[3]);
  puVar1[2] = uVar2;
  luaO_insertlist(&DAT_1002bf18,puVar1);
  uVar3 = 0;
  if (puVar1[4] != 0) {
    iVar4 = 0;
    do {
      lstate__7880(puVar1[2] + iVar4,(int)param_1);
      lstate__7880(puVar1[2] + 8 + iVar4,(int)param_1);
      uVar3 = uVar3 + 1;
      iVar4 = iVar4 + 0x10;
    } while (uVar3 < (uint)puVar1[4]);
  }
  return puVar1;
}

/* ---- 0x1000c390  luaH_free ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

undefined4 * __cdecl luaH_free(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = (undefined4 *)
           (**(code **)(DAT_1002beb8 + 0x20))
                     (param_1 << 4,s_C__grimsrc_libs_lua_src_ltable_c_10027cf4,0x53);
  puVar2 = puVar1;
  if (0 < param_1) {
    do {
      *puVar2 = 0xfffffff9;
      param_1 = param_1 + -1;
      puVar2 = puVar2 + 4;
    } while (param_1 != 0);
  }
  return puVar1;
}

/* ---- 0x1000c3d0  luaH_init ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

undefined4 * __cdecl luaH_init(int a1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  longlong lVar4;
  
  puVar1 = (undefined4 *)
           (**(code **)(DAT_1002beb8 + 0x20))(0x18,s_C__grimsrc_libs_lua_src_ltable_c_10027cf4,0xa4)
  ;
  lVar4 = _ftol();
  iVar2 = luaO_redimension((int)lVar4);
  uVar3 = luaH_free(iVar2);
  puVar1[2] = uVar3;
  puVar1[3] = iVar2;
  puVar1[4] = 0;
  puVar1[5] = 0xfffffffd;
  luaO_insertlist(&DAT_1002bf18,puVar1);
  DAT_1002beec = DAT_1002beec + 1 + ((int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4);
  return puVar1;
}
#endif


/* ---- 0x1000c450  ltable__c450 ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

void __cdecl ltable__c450(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int *piVar6;
  
  piVar1 = *(int **)(param_1 + 8);
  uVar2 = luaH_free(*(int *)(param_1 + 0xc));
  *(undefined4 *)(param_1 + 8) = uVar2;
  uVar5 = 0;
  piVar6 = piVar1;
  if (*(int *)(param_1 + 0x10) != 0) {
    do {
      if ((*piVar6 != -7) && (piVar6[2] != -7)) {
        iVar3 = luaH_present(param_1,piVar6);
        piVar4 = (int *)(iVar3 * 0x10 + *(int *)(param_1 + 8));
        *piVar4 = *piVar6;
        piVar4[1] = piVar6[1];
        piVar4[2] = piVar6[2];
        piVar4[3] = piVar6[3];
      }
      uVar5 = uVar5 + 1;
      piVar6 = piVar6 + 4;
    } while (uVar5 < *(uint *)(param_1 + 0x10));
  }
  (**(code **)(DAT_1002beb8 + 0x24))(piVar1);
  return;
}

/* ---- 0x1000c4d0  luaH_present ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

int __cdecl luaH_present(int param_1,int *param_2)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int *piVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar5;
  int iVar6;
  
  iVar1 = *(int *)(param_1 + 0xc);
  iVar3 = luaH_hashindex(param_2);
  iVar5 = iVar3 % iVar1;
  iVar6 = iVar5 * 0x10;
  piVar4 = (int *)(*(int *)(param_1 + 8) + iVar6);
  if ((*piVar4 != -7) && (bVar2 = luaO_equalObj(param_2,piVar4), ((uint)(bVar2)) == 0))
  {
    iVar3 = iVar3 % (iVar1 + -2) + 1;
    do {
      iVar5 = iVar5 + iVar3;
      iVar6 = iVar6 + iVar3 * 0x10;
      if (iVar1 <= iVar5) {
        iVar5 = iVar5 - iVar1;
        iVar6 = iVar6 + iVar1 * -0x10;
      }
      piVar4 = (int *)(*(int *)(param_1 + 8) + iVar6);
    } while ((*piVar4 != -7) &&
            (bVar2 = luaO_equalObj(param_2,piVar4), ((uint)(bVar2)) == 0));
  }
  return iVar5;
}

/* ---- 0x1000c580  luaH_hashindex ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

int __cdecl luaH_hashindex(undefined4 *param_1)

{
  int iVar1;
  longlong lVar2;
  
  switch(*param_1) {
  case 0xfffffff8:
  case 0xfffffffb:
  case 0xfffffffc:
  case 0xfffffffd:
  case 0xfffffffe:
  case 0:
    iVar1 = param_1[1];
    break;
  default:
    lua_error((byte *)s_unexpected_type_to_index_table_10027d18);
    iVar1 = 0;
    break;
  case 0xfffffffa:
  case 0xffffffff:
    lVar2 = _ftol();
    iVar1 = (int)lVar2;
  }
  if (-1 < iVar1) {
    return iVar1;
  }
  return -1 - iVar1;
}
#endif


/* ---- 0x1000c5f0  luaH_get ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

int * __cdecl luaH_get(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = luaH_present(param_1,param_2);
  piVar2 = (int *)(iVar1 * 0x10 + *(int *)(param_1 + 8));
  if (*piVar2 != -7) {
    return piVar2 + 2;
  }
  return (int *)0x0;
}

/* ---- 0x1000c620  luaH_set ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

int * __cdecl luaH_set(int param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  iVar1 = luaH_present(param_1,param_2);
  piVar3 = (int *)(iVar1 * 0x10 + *(int *)(param_1 + 8));
  if (*piVar3 == -7) {
    uVar2 = *(int *)(param_1 + 0x10) + 1;
    *(uint *)(param_1 + 0x10) = uVar2;
    if ((double)*(uint *)(param_1 + 0xc) * 0.7 < (double)uVar2) {
      luaH_rehash(param_1);
      iVar1 = luaH_present(param_1,param_2);
      piVar3 = (int *)(iVar1 * 0x10 + *(int *)(param_1 + 8));
    }
    *piVar3 = *param_2;
    piVar3[1] = param_2[1];
    piVar3[2] = -7;
  }
  return piVar3 + 2;
}

/* ---- 0x1000c6b0  luaH_rehash ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

void __cdecl luaH_rehash(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  
  iVar1 = *(int *)(param_1 + 0xc);
  piVar2 = *(int **)(param_1 + 8);
  iVar3 = luaH_nuse(param_1);
  if (iVar3 == 0) {
    uVar4 = luaO_redimension(*(int *)(param_1 + 0xc));
    *(undefined4 *)(param_1 + 0xc) = uVar4;
  }
  uVar4 = luaH_free(*(int *)(param_1 + 0xc));
  *(undefined4 *)(param_1 + 8) = uVar4;
  iVar3 = iVar1;
  piVar7 = piVar2;
  if (0 < iVar1) {
    do {
      if ((*piVar7 != -7) && (piVar7[2] != -7)) {
        iVar5 = luaH_present(param_1,piVar7);
        piVar6 = (int *)(iVar5 * 0x10 + *(int *)(param_1 + 8));
        *piVar6 = *piVar7;
        piVar6[1] = piVar7[1];
        piVar6[2] = piVar7[2];
        piVar6[3] = piVar7[3];
      }
      iVar3 = iVar3 + -1;
      piVar7 = piVar7 + 4;
    } while (iVar3 != 0);
  }
  DAT_1002beec = DAT_1002beec +
                 ((*(uint *)(param_1 + 0xc) >> 4) - ((int)(iVar1 + (iVar1 >> 0x1f & 0xfU)) >> 4));
  (**(code **)(DAT_1002beb8 + 0x24))(piVar2);
  return;
}

/* ---- 0x1000c770  luaH_nuse ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

undefined4 __cdecl luaH_nuse(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xc) + -1;
  if (iVar2 < 0) {
    return 0;
  }
  piVar1 = (int *)(*(int *)(param_1 + 8) + iVar2 * 0x10);
  while ((*piVar1 == -7 || (piVar1[2] != -7))) {
    iVar2 = iVar2 + -1;
    piVar1 = piVar1 + -4;
    if (iVar2 < 0) {
      return 0;
    }
  }
  return 1;
}

/* ---- 0x1000c7b0  luaH_next ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

void __cdecl luaH_next(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = *(int *)(param_1 + 4);
  if (*param_2 == -7) {
    ltable__c810(iVar1,0);
    return;
  }
  iVar2 = luaH_present(iVar1,param_2);
  piVar3 = (int *)(*(int *)(iVar1 + 8) + iVar2 * 0x10);
  if ((*piVar3 == -7) || (piVar3[2] == -7)) {
    luaL_argerror(2,IMG_ADDR(0x10027d38));
  }
  ltable__c810(iVar1,iVar2 + 1);
  return;
}

/* ---- 0x1000c810  ltable__c810 ---- */
/* Unidentified function of ltable.c (hash tables, with Grim save support) */

int __cdecl ltable__c810(int param_1,int param_2)

{
  int *piVar1;
  
  if (param_2 < *(int *)(param_1 + 0xc)) {
    piVar1 = (int *)(param_2 * 0x10 + *(int *)(param_1 + 8));
    do {
      if ((*piVar1 != -7) && (piVar1[2] != -7)) {
        return param_2 * 0x10 + *(int *)(param_1 + 8);
      }
      param_2 = param_2 + 1;
      piVar1 = piVar1 + 4;
    } while (param_2 < *(int *)(param_1 + 0xc));
  }
  return 0;
}
