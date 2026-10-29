/* LUA.DLL :: lfunc.c
 * functions 0x10004ba0 .. 0x10004e30 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10004ba0  luaF_newproto ---- */
/* lfunc.c (prototypes and closures) */

undefined4 * __cdecl luaF_newproto(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)
           (**(code **)(DAT_1002beb8 + 0x20))
                     (param_1 * 8 + 0x14,s_C__grimsrc_libs_lua_src_lfunc_cp_10026aa4,0x16);
  luaO_insertlist(&DAT_1002bf20,puVar1);
  DAT_1002beec = DAT_1002beec + 1;
  puVar1[2] = param_1;
  return puVar1;
}

/* ---- 0x10004bf0  luaF_newclosure ---- */
/* lfunc.c (prototypes and closures) */

undefined4 * luaF_newclosure(void)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)
           (**(code **)(DAT_1002beb8 + 0x20))(0x20,s_C__grimsrc_libs_lua_src_lfunc_cp_10026aa4,0x20)
  ;
  puVar1[4] = 0;
  puVar1[5] = 0;
  puVar1[6] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[7] = 0;
  luaO_insertlist(&DAT_1002bf38,puVar1);
  DAT_1002beec = DAT_1002beec + 5;
  return puVar1;
}

/* ---- 0x10004c40  luaF_freeclosure ---- */
/* Unidentified function of lfunc.c (prototypes and closures) */

void __cdecl luaF_freeclosure(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  while (param_1 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*param_1;
    DAT_1002beec = DAT_1002beec + -5;
    luaF_freeproto((int)param_1);
    param_1 = puVar1;
  }
  return;
}

/* ---- 0x10004c70  luaF_freeproto ---- */
/* Unidentified function of lfunc.c (prototypes and closures) */

void __cdecl luaF_freeproto(int param_1)

{
  (**(code **)(DAT_1002beb8 + 0x24))(*(undefined4 *)(param_1 + 0x10));
  (**(code **)(DAT_1002beb8 + 0x24))(*(undefined4 *)(param_1 + 0x1c));
  (**(code **)(DAT_1002beb8 + 0x24))(*(undefined4 *)(param_1 + 8));
  (**(code **)(DAT_1002beb8 + 0x24))(param_1);
  return;
}

/* ---- 0x10004cc0  lfunc__4cc0 ---- */
/* Unidentified function of lfunc.c (prototypes and closures) */

void __cdecl lfunc__4cc0(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  while (param_1 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*param_1;
    DAT_1002beec = DAT_1002beec + -1;
    (**(code **)(DAT_1002beb8 + 0x24))(param_1);
    param_1 = puVar1;
  }
  return;
}

/* ---- 0x10004cf0  luaF_getlocalname ---- */
int __cdecl luaF_getlocalname(int param_1,int param_2,uint param_3)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
                    /* 0x4cf0  1  luaF_getlocalname */
  iVar5 = 0;
  iVar3 = 0;
  piVar4 = *(int **)(param_1 + 0x1c);
  if (piVar4 != (int *)0x0) {
    uVar2 = piVar4[1];
    while ((uVar2 != 0xffffffff && (uVar2 < param_3))) {
      if (*piVar4 == 0) {
        iVar5 = iVar5 + -1;
        if (iVar5 < param_2) {
          iVar3 = 0;
        }
      }
      else {
        iVar5 = iVar5 + 1;
        if (iVar5 == param_2) {
          iVar3 = *piVar4 + 0x18;
        }
      }
      puVar1 = (uint *)(piVar4 + 3);
      piVar4 = piVar4 + 2;
      uVar2 = *puVar1;
    }
    return iVar3;
  }
  return iVar3;
}

/* ---- 0x10004d40  lfunc__4d40 ---- */
/* Unidentified function of lfunc.c (prototypes and closures) */

uint __cdecl lfunc__4d40(int *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  uVar3 = DAT_1002bf08;
  if (*param_1 == -7) {
    return 0xffffffff;
  }
  uVar1 = 0;
  if (DAT_1002bf08 != 0) {
    piVar4 = (int *)(DAT_1002bf34 + 8);
    do {
      if (*piVar4 == 2) break;
      uVar1 = uVar1 + 1;
      piVar4 = piVar4 + 3;
    } while (uVar1 < DAT_1002bf08);
  }
  if ((uVar1 == DAT_1002bf08) &&
     (DAT_1002bf08 = luaM_growaux(&DAT_1002bf34,DAT_1002bf08,0xc,
                                  (byte *)s_reference_table_overflow_10026ac8,0xfffe), uVar1 = uVar3
     , uVar3 < DAT_1002bf08)) {
    iVar2 = uVar3 * 0xc;
    do {
      uVar3 = uVar3 + 1;
      *(undefined4 *)(DAT_1002bf34 + 8 + iVar2) = 2;
      iVar2 = iVar2 + 0xc;
    } while (uVar3 < DAT_1002bf08);
  }
  iVar2 = uVar1 * 0xc;
  *(int *)(DAT_1002bf34 + iVar2) = *param_1;
  *(int *)(DAT_1002bf34 + 4 + iVar2) = param_1[1];
  *(uint *)(DAT_1002bf34 + 8 + iVar2) = (uint)(param_2 == 0);
  return uVar1;
}

/* ---- 0x10004e30  lfunc__4e30 ---- */
/* Unidentified function of lfunc.c (prototypes and closures) */

undefined * __cdecl lfunc__4e30(uint param_1)

{
  undefined *puVar1;
  
  if (param_1 == 0xffffffff) {
    return &DAT_100270e0;
  }
  if ((-1 < (int)param_1) && (param_1 < DAT_1002bf08)) {
    puVar1 = (undefined *)(DAT_1002bf34 + param_1 * 0xc);
    if (*(int *)(puVar1 + 8) == 0) {
      return puVar1;
    }
    if (*(int *)(puVar1 + 8) == 1) {
      return puVar1;
    }
  }
  return (undefined *)0x0;
}
