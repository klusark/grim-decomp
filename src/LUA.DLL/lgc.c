/* LUA.DLL :: lgc.c
 * functions 0x10004e70 .. 0x10005320 (15 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10004e70  luaC_hashcallIM ---- */
/* Unidentified function of lgc.c (garbage collector) */

void __cdecl luaC_hashcallIM(undefined4 *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 **)(_frame + (0x20 - 0x4)))
  
  local_8 = 0xfffffffd;
  for (; param_1 != (undefined4 *)0x0; param_1 = (undefined4 *)*param_1) {
    local_4 = param_1;
    luaD_gcIM(&local_8);
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x10004ea0  luaC_strcallIM ---- */
/* Unidentified function of lgc.c (garbage collector) */

void __cdecl luaC_strcallIM(undefined4 *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 **)(_frame + (0x20 - 0x4)))
  
  local_8 = 0;
  for (; param_1 != (undefined4 *)0x0; param_1 = (undefined4 *)*param_1) {
    if (param_1[2] == -1) {
      local_4 = param_1;
      luaD_gcIM(&local_8);
    }
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x10004fc0  lgc__4fc0 ---- */
/* Unidentified function of lgc.c (garbage collector) */

void lgc__4fc0(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (DAT_1002bf08 != 0) {
    iVar2 = 0;
    do {
      if ((((undefined4 *)(DAT_1002bf34 + iVar2))[2] == 1) &&
         (iVar1 = lgc__5010((undefined4 *)(DAT_1002bf34 + iVar2)), iVar1 == 0)) {
        *(undefined4 *)(DAT_1002bf34 + 8 + iVar2) = 3;
      }
      uVar3 = uVar3 + 1;
      iVar2 = iVar2 + 0xc;
    } while (uVar3 < DAT_1002bf08);
  }
  return;
}

/* ---- 0x10005010  lgc__5010 ---- */
/* Unidentified function of lgc.c (garbage collector) */

undefined4 __cdecl lgc__5010(undefined4 *param_1)

{
  switch(*param_1) {
  case 0xfffffff8:
    return *(undefined4 *)(param_1[1] + 4);
  default:
    return 1;
  case 0xfffffffc:
  case 0xfffffffe:
  case 0:
    return *(undefined4 *)(param_1[1] + 4);
  case 0xfffffffd:
    return *(undefined4 *)(param_1[1] + 4);
  }
}

/* ---- 0x10005070  lgc__5070 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Unidentified function of lgc.c (garbage collector) */

void __cdecl lgc__5070(undefined4 *param_1)

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
  return;
}
#endif


/* ---- 0x100050b0  luaC_markall ---- */
/* Unidentified function of lgc.c (garbage collector) */

void luaC_markall(void)

{
  ldo__4600(luaC_markobject);
  luaC_travglobal();
  luaC_travstack();
  ltm__cb80(luaC_markobject);
  return;
}

/* ---- 0x100050e0  luaC_travstack ---- */
/* Unidentified function of lgc.c (garbage collector) */

void luaC_travstack(void)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (DAT_1002bf08 != 0) {
    iVar1 = 0;
    do {
      if (((undefined4 *)(DAT_1002bf34 + iVar1))[2] == 0) {
        luaC_markobject((undefined4 *)(DAT_1002bf34 + iVar1));
      }
      uVar2 = uVar2 + 1;
      iVar1 = iVar1 + 0xc;
    } while (uVar2 < DAT_1002bf08);
  }
  return;
}

/* ---- 0x10005120  luaC_travglobal ---- */
/* Unidentified function of lgc.c (garbage collector) */

void luaC_travglobal(void)

{
  undefined4 *puVar1;
  
  for (puVar1 = DAT_1002bf00; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    if (puVar1[4] != -7) {
      luaC_markobject(puVar1 + 4);
      luaC_strmark((int)puVar1);
    }
  }
  return;
}

/* ---- 0x10005150  luaC_strmark ---- */
/* Unidentified function of lgc.c (garbage collector) */

void __cdecl luaC_strmark(int param_1)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 4) == 0)) {
    *(undefined4 *)(param_1 + 4) = 1;
  }
  return;
}

/* ---- 0x10005170  luaC_markobject ---- */
/* Unidentified function of lgc.c (garbage collector) */

undefined4 __cdecl luaC_markobject(undefined4 *param_1)

{
  switch(*param_1) {
  case 0xfffffff6:
  case 0xfffffffc:
    luaC_hashmark(param_1[1]);
    break;
  case 0xfffffff7:
  case 0xfffffff8:
    luaC_protomark(param_1[1]);
    return 0;
  case 0xfffffffd:
    luaC_closuremark(param_1[1]);
    return 0;
  case 0xfffffffe:
  case 0:
    luaC_strmark(param_1[1]);
    return 0;
  }
  return 0;
}

/* ---- 0x100051f0  luaC_hashmark ---- */
/* Unidentified function of lgc.c (garbage collector) */

void __cdecl luaC_hashmark(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  if (*(int *)(param_1 + 4) == 0) {
    piVar4 = *(int **)(param_1 + 0x1c);
    *(undefined4 *)(param_1 + 4) = 1;
    if (*(int *)(param_1 + 0x18) != 0) {
      luaC_strmark(*(int *)(param_1 + 0x18));
    }
    uVar3 = 0;
    if (*(int *)(param_1 + 0xc) != 0) {
      do {
        luaC_markobject((undefined4 *)(*(int *)(param_1 + 8) + uVar3 * 8));
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(param_1 + 0xc));
    }
    if (piVar4 != (int *)0x0) {
      iVar2 = piVar4[1];
      while (iVar2 != -1) {
        if (*piVar4 != 0) {
          luaC_strmark(*piVar4);
        }
        piVar1 = piVar4 + 3;
        piVar4 = piVar4 + 2;
        iVar2 = *piVar1;
      }
    }
  }
  return;
}

/* ---- 0x10005270  luaC_protomark ---- */
/* Unidentified function of lgc.c (garbage collector) */

void __cdecl luaC_protomark(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 4) == 0) {
    iVar2 = *(int *)(param_1 + 8);
    *(undefined4 *)(param_1 + 4) = 1;
    if (-1 < iVar2) {
      puVar1 = (undefined4 *)(param_1 + 0xc + iVar2 * 8);
      iVar2 = iVar2 + 1;
      do {
        luaC_markobject(puVar1);
        puVar1 = puVar1 + -2;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  return;
}

/* ---- 0x100052b0  luaC_closuremark ---- */
/* Unidentified function of lgc.c (garbage collector) */

void __cdecl luaC_closuremark(int param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  if (*(int *)(param_1 + 4) == 0) {
    uVar2 = 0;
    *(undefined4 *)(param_1 + 4) = 1;
    if (*(int *)(param_1 + 0xc) != 0) {
      iVar1 = 0;
      do {
        piVar3 = (int *)(*(int *)(param_1 + 8) + iVar1);
        if (*piVar3 != -7) {
          luaC_markobject(piVar3);
          luaC_markobject(piVar3 + 2);
        }
        uVar2 = uVar2 + 1;
        iVar1 = iVar1 + 0x10;
      } while (uVar2 < *(uint *)(param_1 + 0xc));
    }
  }
  return;
}

/* ---- 0x10005300  lgc__5300 ---- */
/* Unidentified function of lgc.c (garbage collector) */

void lgc__5300(void)

{
  if (DAT_1002bf64 <= DAT_1002beec) {
    lua_collectgarbage(0);
  }
  return;
}

/* ---- 0x10005320  FUN_10005320 ---- */
void FUN_10005320(void)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  char *pcVar4;
  longlong lVar5;
  
  iVar1 = lua_lua2C(3);
  if (iVar1 == 0) {
    io_setfile((byte *)s__INPUT_10026c00);
    io_setreturn((byte *)&PTR_DAT_100282d0,(byte *)s__INPUT_10026c00);
    return;
  }
  iVar2 = lua_tag(iVar1);
  lVar5 = io_getint(1);
  if (iVar2 == (int)lVar5) {
    pbVar3 = (byte *)lua_getuserdata(iVar1);
    io_setreturn(pbVar3,(byte *)s__INPUT_10026c00);
    return;
  }
  pcVar4 = (char *)luaL_check_string(3);
  if (*pcVar4 == '|') {
    pbVar3 = (byte *)0x0;
  }
  else {
    pbVar3 = (byte *)(**(code **)(DAT_1002beb8 + 0x30))(pcVar4,&DAT_10026a80);
  }
  if (pbVar3 == (byte *)0x0) {
    io_pushresult(0);
    return;
  }
  io_setreturn(pbVar3,(byte *)s__INPUT_10026c00);
  return;
}
