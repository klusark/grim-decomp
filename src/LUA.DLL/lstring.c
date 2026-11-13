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

TaggedString * __cdecl luaS_createudata(void *udata,int tag)

{
  TaggedString *pTVar1;
  
  pTVar1 = insert(udata,tag,(StringTable *)(g_dwLState_string_root + ((uint)udata % 0x3d) * 0xc));
  return pTVar1;
}

/* ---- 0x10008dc0  insert ---- */
/* Original name insert (the remaster's libLua.so: static insert(char*, int, stringtable*): callers
   luaS_new and luaS_createudata); was lstring__8dc0. */

TaggedString * __cdecl insert(char *buff,int tag,StringTable *tb)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte *h;
  TaggedString *pTVar2;
  uint uVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  bool bVar9;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  h = hash((byte *)buff,tag);
  uVar3 = tb->nSize;
  local_8 = 0xffffffff;
  if ((int)(uVar3 * 2) <= tb->nUse * 3) {
    grow(tb);
    uVar3 = tb->nSize;
  }
  uVar6 = (uint)h % uVar3;
  pTVar2 = tb->ppHash[uVar6];
  uVar7 = local_8;
  do {
    if (pTVar2 == (TaggedString *)0x0) {
      if (uVar7 == 0xffffffff) {
        tb->nUse = tb->nUse + 1;
        uVar7 = uVar6;
      }
      pTVar2 = newone(buff,tag,(uint)h);
      tb->ppHash[uVar7] = pTVar2;
      return tb->ppHash[uVar7];
    }
    local_8 = uVar6;
    if (pTVar2 != (TaggedString *)&g_EMPTY) {
      if (pTVar2->nConstIndex < 0) {
        if (((tag != (pTVar2->globalval).nTtype) && (tag != -1)) ||
           (buff != (char *)(pTVar2->globalval).dwValue)) goto LAB_10008e84;
        bVar9 = true;
      }
      else {
        if (tag == -2) {
          pcVar8 = pTVar2->aStr;
          pbVar4 = (byte *)buff;
          do {
            bVar1 = *pbVar4;
            bVar9 = bVar1 < (byte)*pcVar8;
            if (bVar1 != *pcVar8) {
LAB_10008e6c:
              iVar5 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
              goto LAB_10008e71;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar4[1];
            bVar9 = bVar1 < (byte)pcVar8[1];
            if (bVar1 != pcVar8[1]) goto LAB_10008e6c;
            pbVar4 = pbVar4 + 2;
            pcVar8 = pcVar8 + 2;
          } while (bVar1 != 0);
          iVar5 = 0;
LAB_10008e71:
          if (iVar5 == 0) {
            bVar9 = true;
            goto LAB_10008e86;
          }
        }
LAB_10008e84:
        bVar9 = false;
      }
LAB_10008e86:
      local_8 = uVar7;
      if (bVar9) {
        return pTVar2;
      }
    }
    uVar6 = uVar6 + 1;
    if (uVar6 == uVar3) {
      uVar6 = 0;
    }
    pTVar2 = tb->ppHash[uVar6];
    uVar7 = local_8;
  } while( true );
}
#undef local_8


/* ---- 0x10008f10  hash ---- */
/* Named hash (not in the remaster, gcc inlined it there): Lua 3.1 source name (lstring.c: h = h*31
   ^ c for strings, the pointer otherwise, used by insert); was lstring__8f10. */

byte * __cdecl hash(byte *param_1,int param_2)

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

/* ---- 0x10008f50  grow ---- */
/* Named grow (not in the remaster, gcc inlined it there): Lua 3.1 source name (lstring.c static
   grow: luaO_redimension of the size, rehash every string that is neither NULL nor EMPTY, free the
   old array); was luaS_grow. */

void __cdecl grow(StringTable *tb)

{
  TaggedString *pTVar1;
  TaggedString *pTVar2;
  uint uVar3;
  TaggedString **ppTVar4;
  uint uVar5;
  TaggedString **ppTVar6;
  int iVar7;
  
  uVar3 = luaO_redimension(tb->nSize);
  ppTVar4 = (TaggedString **)
            (**(code **)(g_dwLuaHS + 0x20))
                      (uVar3 * 4,s_C__grimsrc_libs_lua_src_lstring__100278b4,0x38);
  uVar5 = uVar3;
  ppTVar6 = ppTVar4;
  if (0 < (int)uVar3) {
    for (; uVar5 != 0; uVar5 = uVar5 - 1) {
      *ppTVar6 = (TaggedString *)0x0;
      ppTVar6 = ppTVar6 + 1;
    }
  }
  iVar7 = 0;
  tb->nUse = 0;
  if (0 < tb->nSize) {
    do {
      pTVar1 = tb->ppHash[iVar7];
      if ((pTVar1 != (TaggedString *)0x0) && (pTVar1 != (TaggedString *)&g_EMPTY)) {
        uVar5 = pTVar1->dwHash % uVar3;
        pTVar2 = ppTVar4[uVar5];
        while (pTVar2 != (TaggedString *)0x0) {
          uVar5 = (int)(uVar5 + 1) % (int)uVar3;
          pTVar2 = ppTVar4[uVar5];
        }
        ppTVar4[uVar5] = pTVar1;
        tb->nUse = tb->nUse + 1;
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < tb->nSize);
  }
  (**(code **)(g_dwLuaHS + 0x24))(tb->ppHash);
  tb->ppHash = ppTVar4;
  tb->nSize = uVar3;
  return;
}

/* ---- 0x10009000  newone ---- */
/* lstring.c (string table) Named newone (not in the remaster, gcc inlined it there): Lua 3.1 source
   name (lstring.c static newone(buff, tag, h): a string copy for LUA_T_STRING (globalval nil,
   constindex 0, nblocks by length), else a userdata record (tag, constindex -1)); was luaS_newlstr.
    */

TaggedString * __cdecl newone(char *buff,int tag,uint h)

{
  char cVar1;
  TaggedString *pTVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  if (tag == -2) {
    uVar3 = 0xffffffff;
    pcVar6 = buff;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    iVar4 = ~uVar3 - 1;
    pTVar2 = (TaggedString *)
             (**(code **)(g_dwLuaHS + 0x20))
                       (~uVar3 + 0x1b,s_C__grimsrc_libs_lua_src_lstring__100278b4,0x52);
    uVar3 = 0xffffffff;
    do {
      pcVar6 = buff;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar6 = buff + 1;
      cVar1 = *buff;
      buff = pcVar6;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar6 = pcVar6 + -uVar3;
    pcVar7 = pTVar2->aStr;
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
    (pTVar2->globalval).nTtype = -7;
    pTVar2->nConstIndex = 0;
    g_dwLState_nblocks = g_dwLState_nblocks + 1 + ((int)(iVar4 + (iVar4 >> 0x1f & 0x3fU)) >> 6);
  }
  else {
    pTVar2 = (TaggedString *)
             (**(code **)(g_dwLuaHS + 0x20))(0x1c,s_C__grimsrc_libs_lua_src_lstring__100278b4,0x59);
    (pTVar2->globalval).dwValue = (uint)buff;
    (pTVar2->globalval).nTtype = -(uint)(tag != -1) & tag;
    pTVar2->nConstIndex = -1;
    g_dwLState_nblocks = g_dwLState_nblocks + 1;
  }
  pTVar2->nMarked = 0;
  pTVar2->dwHash = h;
  pTVar2->pNext = pTVar2;
  return pTVar2;
}

/* ---- 0x100090e0  luaS_new ---- */
TaggedString * __cdecl luaS_new(char *str)

{
  TaggedString *pTVar1;
  
                    /* 0x90e0  2  luaS_new */
  pTVar1 = insert(str,-2,(StringTable *)(g_dwLState_string_root + ((uint)(int)*str % 0x3d) * 0xc));
  return pTVar1;
}

/* ---- 0x10009110  luaS_newfixedstring ---- */
/* lstring.c (string table) */

void __cdecl luaS_newfixedstring(byte *param_1)

{
  TaggedString *pTVar1;
  
  pTVar1 = luaS_new((char *)param_1);
  if (pTVar1->nMarked == 0) {
    pTVar1->nMarked = 2;
  }
  return;
}

/* ---- 0x10009130  luaS_free ---- */
/* Unidentified function of lstring.c (string table) */

void __cdecl luaS_free(TaggedString *l)

{
  char cVar1;
  TaggedString *pTVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  
  do {
    if (l == (TaggedString *)0x0) {
      return;
    }
    pTVar2 = l->pNext;
    if (l->nConstIndex == -1) {
      iVar3 = 1;
    }
    else {
      uVar4 = 0xffffffff;
      pcVar5 = l->aStr;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      iVar3 = (~uVar4 - 1 >> 6) + 1;
    }
    g_dwLState_nblocks = g_dwLState_nblocks - iVar3;
    (**(code **)(g_dwLuaHS + 0x24))(l);
    l = pTVar2;
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
  remove_from_list(&g_dwLState_rootglobal);
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

/* ---- 0x100093e0  remove_from_list ---- */
/* Named remove_from_list (not in the remaster, gcc inlined it there): Lua 3.1 source name
   (lstring.c: unlinks the unmarked nodes, used by luaS_collector); was lstring__93e0. */

void __cdecl remove_from_list(undefined4 *param_1)

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

void __cdecl luaS_rawsetglobal(TaggedString *ts,TObject *newval)

{
  (ts->globalval).nTtype = newval->nTtype;
  (ts->globalval).dwValue = newval->dwValue;
  if (ts->pNext == ts) {
    ts->pNext = g_dwLState_rootglobal;
    g_dwLState_rootglobal = ts;
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

int __cdecl luaS_globaldefined(char *name)

{
  TaggedString *pTVar1;
  
  pTVar1 = luaS_new(name);
  return (uint)((pTVar1->globalval).nTtype != -7);
}

/* ---- 0x10009570  str_len ---- */
/* Original name str_len (the remaster's libLua.so: strlib entry 'strlen'); was FUN_10009570. */

void __cdecl str_len(void)

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
