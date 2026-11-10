/* LUA.DLL :: lstring.c
 * functions 0x10008d40 .. 0x10009570 (20 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10008d40  luaS_init ---- */
/* lstring.c (string table) */

void luaS_init(void)

{
  int iVar1;
  
  g_dwLState_string_root =
       (**(code **)(g_dwLuaHS + 0x20))(0x2dc,s_C__grimsrc_libs_lua_src_lstring__100278b4,0x1e);
  iVar1 = 0;
  do {
    iVar1 = iVar1 + 0xc;
    *(undefined4 *)(g_dwLState_string_root + -0xc + iVar1) = 0;
    *(undefined4 *)(g_dwLState_string_root + -8 + iVar1) = 0;
    *(undefined4 *)(g_dwLState_string_root + -4 + iVar1) = 0;
  } while (iVar1 < 0x2dc);
  return;
}

/* ---- 0x10008d90  luaS_createudata ---- */
/* Original name luaS_createudata (the remaster's libLua.so: luaS_createudata: callers
   lua_pushusertag and GlobalBeginRestore, calls insert); was luaS_hash. */

undefined * __cdecl luaS_createudata(byte *param_1,uint param_2)

{
  undefined *puVar1;
  
  puVar1 = insert(param_1,param_2,(uint *)(g_dwLState_string_root + ((uint)param_1 % 0x3d) * 0xc));
  return puVar1;
}

/* ---- 0x10008dc0  insert ---- */
/* Original name insert (the remaster's libLua.so: static insert(char*, int, stringtable*): callers
   luaS_new and luaS_createudata); was lstring__8dc0. */

undefined * __cdecl insert(byte *param_1,uint param_2,uint *param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  undefined *puVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  uint uVar7;
  uint uVar8;
  byte *pbVar9;
  bool bVar10;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  pbVar3 = lstring__8f10(param_1,param_2);
  uVar5 = *param_3;
  local_8 = 0xffffffff;
  if ((int)(uVar5 * 2) <= (int)(param_3[1] * 3)) {
    luaS_grow(param_3);
    uVar5 = *param_3;
  }
  uVar7 = (uint)pbVar3 % uVar5;
  puVar2 = *(undefined **)(param_3[2] + uVar7 * 4);
  uVar8 = local_8;
  do {
    if (puVar2 == (undefined *)0x0) {
      if (uVar8 == 0xffffffff) {
        param_3[1] = param_3[1] + 1;
        uVar8 = uVar7;
      }
      iVar4 = luaS_newlstr((char *)param_1,param_2,pbVar3);
      *(int *)(param_3[2] + uVar8 * 4) = iVar4;
      return *(undefined **)(param_3[2] + uVar8 * 4);
    }
    local_8 = uVar7;
    if (puVar2 != &g_EMPTY) {
      if (*(int *)(puVar2 + 8) < 0) {
        if (((param_2 != *(uint *)(puVar2 + 0x10)) && (param_2 != 0xffffffff)) ||
           (param_1 != *(byte **)(puVar2 + 0x14))) goto LAB_10008e84;
        bVar10 = true;
      }
      else {
        if (param_2 == 0xfffffffe) {
          pbVar9 = puVar2 + 0x18;
          pbVar6 = param_1;
          do {
            bVar1 = *pbVar6;
            bVar10 = bVar1 < *pbVar9;
            if (bVar1 != *pbVar9) {
LAB_10008e6c:
              iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
              goto LAB_10008e71;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar6[1];
            bVar10 = bVar1 < pbVar9[1];
            if (bVar1 != pbVar9[1]) goto LAB_10008e6c;
            pbVar6 = pbVar6 + 2;
            pbVar9 = pbVar9 + 2;
          } while (bVar1 != 0);
          iVar4 = 0;
LAB_10008e71:
          if (iVar4 == 0) {
            bVar10 = true;
            goto LAB_10008e86;
          }
        }
LAB_10008e84:
        bVar10 = false;
      }
LAB_10008e86:
      local_8 = uVar8;
      if (bVar10) {
        return puVar2;
      }
    }
    uVar7 = uVar7 + 1;
    if (uVar7 == uVar5) {
      uVar7 = 0;
    }
    puVar2 = *(undefined **)(param_3[2] + uVar7 * 4);
    uVar8 = local_8;
  } while( true );
}
#undef local_8


/* ---- 0x10008f10  lstring__8f10 ---- */
/* Unidentified function of lstring.c (string table) */

byte * __cdecl lstring__8f10(byte *param_1,int param_2)

{
  byte *pbVar1;
  byte bVar2;
  byte *pbVar3;
  
  if (param_2 == -2) {
    pbVar3 = (byte *)0x0;
    bVar2 = *param_1;
    while (bVar2 != 0) {
      pbVar3 = (byte *)((int)pbVar3 * 0x1f ^ (uint)bVar2);
      pbVar1 = param_1 + 1;
      param_1 = param_1 + 1;
      bVar2 = *pbVar1;
    }
    return pbVar3;
  }
  return param_1;
}

/* ---- 0x10008f50  luaS_grow ---- */
/* Unidentified function of lstring.c (string table) */

void __cdecl luaS_grow(uint *param_1)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  int iVar7;
  
  uVar3 = luaO_redimension(*param_1);
  puVar4 = (undefined4 *)
           (**(code **)(g_dwLuaHS + 0x20))
                     (uVar3 * 4,s_C__grimsrc_libs_lua_src_lstring__100278b4,0x38);
  uVar5 = uVar3;
  puVar6 = puVar4;
  if (0 < (int)uVar3) {
    for (; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
  }
  iVar7 = 0;
  param_1[1] = 0;
  if (0 < (int)*param_1) {
    do {
      puVar1 = *(undefined **)(param_1[2] + iVar7 * 4);
      if ((puVar1 != (undefined *)0x0) && (puVar1 != &g_EMPTY)) {
        uVar5 = *(uint *)(puVar1 + 0xc) % uVar3;
        iVar2 = puVar4[uVar5];
        while (iVar2 != 0) {
          uVar5 = (int)(uVar5 + 1) % (int)uVar3;
          iVar2 = puVar4[uVar5];
        }
        puVar4[uVar5] = puVar1;
        param_1[1] = param_1[1] + 1;
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < (int)*param_1);
  }
  (**(code **)(g_dwLuaHS + 0x24))(param_1[2]);
  param_1[2] = (uint)puVar4;
  *param_1 = uVar3;
  return;
}

/* ---- 0x10009000  luaS_newlstr ---- */
/* lstring.c (string table) */

int __cdecl luaS_newlstr(char *param_1,uint param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  if (param_2 == 0xfffffffe) {
    uVar3 = 0xffffffff;
    pcVar6 = param_1;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    iVar4 = ~uVar3 - 1;
    iVar2 = (**(code **)(g_dwLuaHS + 0x20))
                      (~uVar3 + 0x1b,s_C__grimsrc_libs_lua_src_lstring__100278b4,0x52);
    uVar3 = 0xffffffff;
    do {
      pcVar6 = param_1;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar6 = param_1 + 1;
      cVar1 = *param_1;
      param_1 = pcVar6;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar6 = pcVar6 + -uVar3;
    pcVar7 = (char *)(iVar2 + 0x18);
    for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
    *(undefined4 *)(iVar2 + 0x10) = 0xfffffff9;
    *(undefined4 *)(iVar2 + 8) = 0;
    g_dwLState_nblocks = g_dwLState_nblocks + 1 + ((int)(iVar4 + (iVar4 >> 0x1f & 0x3fU)) >> 6);
  }
  else {
    iVar2 = (**(code **)(g_dwLuaHS + 0x20))(0x1c,s_C__grimsrc_libs_lua_src_lstring__100278b4,0x59);
    *(char **)(iVar2 + 0x14) = param_1;
    *(uint *)(iVar2 + 0x10) = -(uint)(param_2 != 0xffffffff) & param_2;
    *(undefined4 *)(iVar2 + 8) = 0xffffffff;
    g_dwLState_nblocks = g_dwLState_nblocks + 1;
  }
  *(undefined4 *)(iVar2 + 4) = 0;
  *(undefined4 *)(iVar2 + 0xc) = param_3;
  *(int *)iVar2 = iVar2;
  return iVar2;
}

/* ---- 0x100090e0  luaS_new ---- */
undefined * __cdecl luaS_new(byte *param_1)

{
  undefined *puVar1;
  
                    /* 0x90e0  2  luaS_new */
  puVar1 = insert(param_1,0xfffffffe,
                  (uint *)(g_dwLState_string_root + ((uint)(int)(char)*param_1 % 0x3d) * 0xc));
  return puVar1;
}

/* ---- 0x10009110  luaS_newfixedstring ---- */
/* lstring.c (string table) */

void __cdecl luaS_newfixedstring(byte *param_1)

{
  int iVar1;
  
  iVar1 = luaS_new(param_1);
  if (*(int *)(iVar1 + 4) == 0) {
    *(undefined4 *)(iVar1 + 4) = 2;
  }
  return;
}

/* ---- 0x10009130  luaS_free ---- */
/* Unidentified function of lstring.c (string table) */

void __cdecl luaS_free(undefined4 *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  
  do {
    if (param_1 == (undefined4 *)0x0) {
      return;
    }
    puVar2 = (undefined4 *)*param_1;
    if (param_1[2] == -1) {
      iVar3 = 1;
    }
    else {
      uVar4 = 0xffffffff;
      pcVar5 = (char *)(param_1 + 6);
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      iVar3 = (~uVar4 - 1 >> 6) + 1;
    }
    g_dwLState_nblocks = g_dwLState_nblocks - iVar3;
    (**(code **)(g_dwLuaHS + 0x24))(param_1);
    param_1 = puVar2;
  } while( true );
}

/* ---- 0x10009180  luaS_writestrings ---- */
/* Original name luaS_writestrings (the remaster's libLua.so: callee SaveObject, caller
   SaveGlobals); was lstring__9180. */

void __cdecl luaS_writestrings(undefined *param_1,int *param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined *a2;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  #define local_c (*(int *)(_frame + (0x20 - 0xc)))
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  a2 = param_1;
  local_c = 0x3d;
  piVar4 = param_2;
  do {
    iVar3 = 0;
    if (0 < *piVar4) {
      do {
        param_2 = *(int **)(piVar4[2] + iVar3 * 4);
        if ((param_2 != (int *)0x0) && (param_2 != (int *)&g_EMPTY)) {
          (*(code *)a2)(&param_2,4);
          (*(code *)a2)(param_2 + 2,4);
          if (param_2[2] == -1) {
            iStack_8 = param_2[4];
            iStack_4 = param_2[5];
            if (lua_savehook != (code *)0x0) {
              iStack_4 = (*lua_savehook)(iStack_8,iStack_4,a2);
            }
            piVar5 = &iStack_8;
          }
          else {
            piVar5 = param_2 + 4;
          }
          LState_SaveObject((int)piVar5,(int)a2);
          if (param_2[2] != -1) {
            uVar2 = 0xffffffff;
            piVar5 = param_2 + 6;
            do {
              if (uVar2 == 0) break;
              uVar2 = uVar2 - 1;
              iVar1 = *piVar5;
              piVar5 = (int *)((int)piVar5 + 1);
            } while ((char)iVar1 != '\0');
            param_1 = (undefined *)(~uVar2 - 1);
            (*(code *)a2)(&param_1,4);
            (*(code *)a2)(param_2 + 6,param_1);
          }
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < *piVar4);
    }
    piVar4 = piVar4 + 3;
    local_c = local_c + -1;
    if (local_c == 0) {
      return;
    }
  } while( true );
}
#undef iStack_4
#undef iStack_8
#undef local_c


/* ---- 0x10009290  luaS_resolvestrings ---- */
/* Original name luaS_resolvestrings (the remaster's libLua.so: callee ResolveObject, caller
   GlobalBeginRestore); was lstring__9290. */

void __cdecl luaS_resolvestrings(int *param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0x3d;
  do {
    iVar3 = 0;
    if (0 < *param_1) {
      do {
        puVar1 = *(undefined **)(param_1[2] + iVar3 * 4);
        if (((puVar1 != (undefined *)0x0) && (puVar1 != &g_EMPTY)) && (*(int *)(puVar1 + 8) != -1))
        {
          LState_ResolveObject((int)(puVar1 + 0x10));
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < *param_1);
    }
    param_1 = param_1 + 3;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}

/* ---- 0x100092e0  luaS_count ---- */
/* Original name luaS_count (the remaster's libLua.so: caller SaveGlobals (string count for the save
   file)); was lstring__92e0. */

int __cdecl luaS_count(int *param_1,uint *param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined *puVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  puVar3 = param_2;
  local_4 = 0;
  *param_2 = 0;
  param_2 = (uint *)0x3d;
  do {
    iVar6 = 0;
    if (0 < *param_1) {
      do {
        puVar2 = *(undefined **)(param_1[2] + iVar6 * 4);
        if (((puVar2 != (undefined *)0x0) && (puVar2 != &g_EMPTY)) &&
           (local_4 = local_4 + 1, *(int *)(puVar2 + 8) != -1)) {
          uVar5 = 0xffffffff;
          pcVar7 = puVar2 + 0x18;
          do {
            if (uVar5 == 0) break;
            uVar5 = uVar5 - 1;
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          uVar4 = *puVar3;
          if (uVar4 <= ~uVar5 - 1) {
            uVar4 = ~uVar5 - 1;
          }
          *puVar3 = uVar4;
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < *param_1);
    }
    param_1 = param_1 + 3;
    param_2 = (uint *)((int)param_2 + -1);
    if (param_2 == (uint *)0x0) {
      return local_4;
    }
  } while( true );
}
#undef local_4


/* ---- 0x10009370  luaS_collector ---- */
/* Original name luaS_collector (the remaster's libLua.so: caller lua_collectgarbage); was
   lstring__9370. */

int luaS_collector(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  piVar5 = (int *)0x0;
  lstring__93e0(&g_dwLState_rootglobal);
  iVar3 = 0;
  do {
    iVar4 = 0;
    piVar1 = (int *)(g_dwLState_string_root + iVar3);
    if (0 < *(int *)(g_dwLState_string_root + iVar3)) {
      do {
        piVar2 = *(int **)(piVar1[2] + iVar4 * 4);
        if (piVar2 != (int *)0x0) {
          if (piVar2[1] == 1) {
            piVar2[1] = 0;
          }
          else if (piVar2[1] == 0) {
            *piVar2 = (int)piVar5;
            *(undefined **)(piVar1[2] + iVar4 * 4) = &g_EMPTY;
            piVar5 = piVar2;
          }
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < *piVar1);
    }
    iVar3 = iVar3 + 0xc;
  } while (iVar3 < 0x2dc);
  return (int)piVar5;
}

/* ---- 0x100093e0  lstring__93e0 ---- */
/* Unidentified function of lstring.c (string table) */

void __cdecl lstring__93e0(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  while (puVar1 = param_1, puVar1 != (undefined4 *)0x0) {
    param_1 = (undefined4 *)*puVar1;
    while ((param_1 != (undefined4 *)0x0 && (param_1[1] == 0))) {
      param_1 = (undefined4 *)*param_1;
      *puVar1 = param_1;
    }
  }
  return;
}

/* ---- 0x10009410  luaS_collectudata ---- */
/* Original name luaS_collectudata (the remaster's libLua.so: caller lua_close (its result goes to
   luaS_free)); was lstring__9410. */

uint * luaS_collectudata(void)

{
  int *piVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  
  puVar3 = (uint *)0x0;
  iVar5 = 0;
  g_dwLState_rootglobal = 0;
  do {
    iVar4 = 0;
    piVar1 = (int *)(g_dwLState_string_root + iVar5);
    if (0 < *(int *)(g_dwLState_string_root + iVar5)) {
      do {
        puVar2 = *(uint **)(piVar1[2] + iVar4 * 4);
        if (((puVar2 != (uint *)0x0) && (puVar2 != (uint *)&g_EMPTY)) && (puVar2[2] == 0xffffffff))
        {
          *puVar2 = (uint)puVar3;
          *(undefined **)(piVar1[2] + iVar4 * 4) = &g_EMPTY;
          puVar3 = puVar2;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < *piVar1);
    }
    iVar5 = iVar5 + 0xc;
  } while (iVar5 < 0x2dc);
  return puVar3;
}

/* ---- 0x10009470  luaS_freeall ---- */
/* Original name luaS_freeall (the remaster's libLua.so: caller lua_close, after luaS_free); was
   lstring__9470. */

void luaS_freeall(void)

{
  int *piVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  do {
    iVar4 = 0;
    piVar1 = (int *)(g_dwLState_string_root + iVar3);
    if (0 < *(int *)(g_dwLState_string_root + iVar3)) {
      do {
        puVar2 = *(undefined **)(piVar1[2] + iVar4 * 4);
        if (puVar2 != &g_EMPTY) {
          (**(code **)(g_dwLuaHS + 0x24))(puVar2);
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < *piVar1);
    }
    (**(code **)(g_dwLuaHS + 0x24))(piVar1[2]);
    iVar3 = iVar3 + 0xc;
  } while (iVar3 < 0x2dc);
  (**(code **)(g_dwLuaHS + 0x24))(g_dwLState_string_root);
  return;
}

/* ---- 0x100094e0  luaS_rawsetglobal ---- */
/* Original name luaS_rawsetglobal (the remaster's libLua.so: callers luaV_setglobal,
   lua_rawsetglobal); was lstring__94e0. */

void __cdecl luaS_rawsetglobal(int *param_1,int *param_2)

{
  param_1[4] = *param_2;
  param_1[5] = param_2[1];
  if ((int *)*param_1 == param_1) {
    *param_1 = (int)g_dwLState_rootglobal;
    g_dwLState_rootglobal = param_1;
  }
  return;
}

/* ---- 0x10009510  luaS_travsymbol ---- */
/* Original name luaS_travsymbol (the remaster's libLua.so: caller lua_getobjname); was
   lstring__9510. */

int * __cdecl luaS_travsymbol(undefined *param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = g_dwLState_rootglobal;
  if (g_dwLState_rootglobal == (int *)0x0) {
    return (int *)0x0;
  }
  do {
    iVar1 = (*(code *)param_1)(piVar2 + 4);
    if (iVar1 != 0) {
      return piVar2 + 6;
    }
    piVar2 = (int *)*piVar2;
  } while (piVar2 != (int *)0x0);
  return (int *)0x0;
}

/* ---- 0x10009550  luaS_globaldefined ---- */
/* Original name luaS_globaldefined (the remaster's libLua.so: luaS_new(name)->value != nil (the
   $ifnot pragma test)); was lstring__9550. */

int __cdecl luaS_globaldefined(byte *param_1)

{
  int iVar1;
  
  iVar1 = luaS_new(param_1);
  return *(int *)(iVar1 + 0x10) != -7;
}

/* ---- 0x10009570  str_len ---- */
/* Original name str_len (the remaster's libLua.so: strlib entry 'strlen'); was FUN_10009570. */

void str_len(void)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  
  pcVar2 = (char *)luaL_check_string(1);
  uVar3 = 0xffffffff;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  lua_pushnumber((float)(~uVar3 - 1));
  return;
}
