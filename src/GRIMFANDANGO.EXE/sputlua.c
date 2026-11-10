/* GRIMFANDANGO.EXE :: sputlua.c
 * functions 0x0049a1e0 .. 0x004a35d0 (22 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0049a1e0  sputLua_GetActorCostumeL ---- */
/* Lua opcode: GetActorCostume */

void sputLua_GetActorCostumeL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int *piVar5;
  longlong lVar6;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(iVar1), iVar3 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    iVar1 = sputActor_ActorDeref(iVar1);
    piVar5 = *(int **)(iVar1 + 0xa0);
    iVar1 = lua_isnil(iVar2);
    if (iVar1 == 0) {
      iVar1 = lua_isnumber(iVar2);
      if (iVar1 == 0) {
        return;
      }
      lVar6 = (longlong)lua_getnumber(iVar2);
      iVar1 = (int)lVar6;
      if (piVar5 == (int *)0x0) goto LAB_0049a295;
      do {
        if (iVar1 < 1) break;
        piVar5 = (int *)piVar5[0x2c];
        iVar1 = iVar1 + -1;
      } while (piVar5 != (int *)0x0);
    }
    if (piVar5 != (int *)0x0) {
      pcVar4 = (char *)Cos_InstGetCostume(*piVar5,(int *)0x0);
      lua_pushstring(pcVar4);
      return;
    }
  }
LAB_0049a295:
  lua_pushnil();
  return;
}

/* ---- 0x0049c3b0  sputLua_GetPointSectorL ---- */
/* WARNING: Variable defined which should be unmapped: local_24 */
/* Lua opcode: GetPointSector */

void sputLua_GetPointSectorL(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  undefined4 uVar7;
  longlong lVar8;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_isnumber(iVar1);
  if (iVar5 != 0) {
    iVar5 = lua_isnumber(iVar2);
    if (iVar5 != 0) {
      iVar5 = lua_isnumber(iVar3);
      if (iVar5 != 0) {
        iVar5 = lua_isnil(iVar4);
        if (iVar5 == 0) {
          lVar8 = (longlong)lua_getnumber(iVar4);
          uVar7 = (undefined4)lVar8;
        }
        else {
          uVar7 = 0x1000;
        }
        local_c[0] = lua_getnumber(iVar1);
        local_c[1] = lua_getnumber(iVar2);
        local_c[2] = lua_getnumber(iVar3);
        pcVar6 = (char *)SectorList_FindByPoint(local_c,uVar7);
        if (pcVar6 != (char *)0x0) {
          lua_pushnumber((float)*(int *)(pcVar6 + 0x20));
          lua_pushstring(pcVar6);
          lua_pushnumber((float)*(int *)(pcVar6 + 0x24));
          return;
        }
      }
    }
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_24
#undef local_c


/* ---- 0x0049c8f0  sputLua_Update ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_1c */
/* Per frame: stores system.frameTime and system.movieTime, collects garbage every 10 s, runs
   lua_updatetasks */

void sputLua_Update(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  
  g_dwSputLua_Update_movieTimeMsec = SmushPlay_GetMovieTime();
  uVar1 = sputTime_GetFrameTime();
  g_dwSputLua_Update_collectionTime = g_dwSputLua_Update_collectionTime + uVar1;
  if (10000.0 < (float)g_dwSputLua_Update_collectionTime) {
    lua_collectgarbage(0);
    g_dwSputLua_Update_collectionTime = 0;
  }
  lua_beginblock();
  iVar2 = lua_getref(g_nLrSystemTable);
  lua_pushobject(iVar2);
  lua_pushstring(s_frameTime_004ec41c);
  lua_pushnumber((float)uVar1);
  lua_settable();
  iVar2 = lua_getref(g_nLrSystemTable);
  lua_pushobject(iVar2);
  lua_pushstring(s_movieTime_004ec410);
  lua_pushnumber((float)(int)g_dwSputLua_Update_movieTimeMsec);
  lua_settable();
  lua_endblock();
  lua_updatetasks(0);
  return;
}
#undef local_1c

#endif


/* ---- 0x0049c9f0  sputLua_Initialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputLua_Initialize(GrimServices *param_1,undefined4 *param_2)

{
  int iVar1;
  
  g_pSputLuaHS = param_1;
  *param_2 = sputLua_Initialize;
  param_2[1] = sputLua_Terminate;
  param_2[2] = sputLua_Startup;
  param_2[3] = sputLua_Shutdown;
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  iVar1 = lua_Initialize((int)param_1,(int *)&g_aLuaMS);
  if (iVar1 != 0) {
    g_dwSputLuaInitialize = 0;
    return 1;
  }
  g_dwSputLuaInitialize = 1;
  return 0;
}

/* ---- 0x0049cbe0  sputLua_FunctionNameL ---- */
/* Lua opcode: FunctionName */

void sputLua_FunctionNameL(void)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  undefined4 *puVar6;
  #define local_10c (*(uint *)(_frame + (0x120 - 0x10c)))
  #define local_108 (*(uint *)(_frame + (0x120 - 0x108)))
  #define local_104 (*(uint *)(_frame + (0x120 - 0x104)))
  #define local_100 (*(char *)(_frame + (0x120 - 0x100)))
  #define local_ff (*(undefined4 *)(_frame + (0x120 - 0xff)))
  
  local_100 = DAT_004f5a98;
  puVar6 = &local_ff;
  for (iVar5 = 0x3f; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  *(undefined2 *)puVar6 = 0;
  *(undefined1 *)((int)puVar6 + 2) = 0;
  iVar5 = lua_lua2C(1);
  iVar2 = lua_isfunction(iVar5);
  if (iVar2 != 0) {
    lua_funcinfo(iVar5,(int *)&local_108,(int *)&local_10c);
    pcVar3 = lua_getobjname(iVar5,(int *)&local_104);
    cVar1 = *pcVar3;
    if ((cVar1 == 'g') || (pcVar3 = s__unknown__004ec468, cVar1 == 't')) {
      pcVar3 = (char *)local_104;
    }
    if (cVar1 == 'g') {
      pcVar4 = s_function_004ec45c;
    }
    else {
      pcVar4 = s_tag_method_004ec450;
      if (cVar1 != 't') {
        pcVar4 = s_unnamed_function_004ec43c;
      }
    }
    sprintf(&local_100,s__s___s____s__d__004ec428,pcVar4,pcVar3,local_108,local_10c);
    lua_pushstring(&local_100);
  }
  return;
}
#undef local_100
#undef local_104
#undef local_108
#undef local_10c
#undef local_ff


/* ---- 0x0049d140  sputLua_TypeOverride ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: Lua_TypeOverride */

void sputLua_TypeOverride(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 < 0x4659454c) {
      if (iVar2 == 0x4659454b) {
        local_14 = (uint)s_keyframe_004ec484;
      }
      else {
        if (iVar2 != 0x20544553) goto LAB_0049d199;
        local_14 = (uint)&DAT_004ec490;
      }
    }
    else if (iVar2 == 0x52544341) {
      local_14 = (uint)s_actor_004ec474;
    }
    else {
      if (iVar2 != 0x54534f43) goto LAB_0049d199;
      local_14 = (uint)s_costume_004ec47c;
    }
    lua_pushstring((char *)local_14);
    iVar1 = lua_tag(iVar1);
    lua_pushnumber((float)iVar1);
    return;
  }
LAB_0049d199:
  iVar2 = lua_getref(g_dwLrTypeFunction);
  lua_pushobject(iVar1);
  lua_callfunction(iVar2);
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  lua_pushobject(iVar1);
  lua_pushobject(iVar2);
  return;
}
#undef local_14
#undef local_4


/* ---- 0x0049e500  sputLua_Terminate ---- */
/* Module slot 1 of sputLua: clears g_pSputLuaHS and calls the Lua shutdown hook if the Lua state
   exists. */

void sputLua_Terminate(void)

{
  g_pSputLuaHS = (GrimServices *)0x0;
  if (g_dwSputLuaInitialize != 0) {
    (*(code *)UINT_008cab54)();
    g_dwSputLuaInitialize = 0;
  }
  return;
}

/* ---- 0x0049e530  sputLua_Shutdown ---- */
/* Module slot 3 of sputLua: disposes the Lua file finder, unrefs the system table, clears the
   save/restore hooks and closes the Lua libs. Original name sputLua_Shutdown (the remaster's
   GrimFandango (Linux): the only unmatched caller of stdFileUtil_DisposeFind; 1 matched neighbours
   agree, 0 disagree); was sputLua_Stop. */

void sputLua_Shutdown(void)

{
  if (g_pFrFileReq != (void *)0x0) {
    stdFileUtil_DisposeFind(g_pFrFileReq);
    g_pFrFileReq = (void *)0x0;
  }
  lua_unref(g_nLrSystemTable);
  *(undefined4 *)lua_savehook_exref = 0;
  *(undefined4 *)lua_restorehook_exref = 0;
  (*(code *)UINT_008cab5c)();
  UINT_008cab80 = 0;
  return;
}

/* ---- 0x0049e880  sputLua_StartMovieL ---- */
/* Lua opcode: StartMovie */

void sputLua_StartMovieL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  longlong lVar8;
  undefined4 uVar9;
  uint uVar10;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_isstring(iVar1);
  if (iVar5 != 0) {
    SoundsFloodMusicBuffer();
    iVar5 = lua_isnumber(iVar4);
    if (iVar5 == 0) {
      uVar7 = 0xffffffff;
    }
    else {
      lVar8 = (longlong)lua_getnumber(iVar4);
      uVar7 = (undefined4)lVar8;
    }
    iVar4 = lua_isnumber(iVar3);
    if (iVar4 == 0) {
      uVar6 = 0xffffffff;
    }
    else {
      lVar8 = (longlong)lua_getnumber(iVar3);
      uVar6 = (undefined4)lVar8;
    }
    iVar2 = lua_isnil(iVar2);
    uVar10 = (uint)(iVar2 == 0);
    uVar9 = 0;
    iVar1 = lua_getstring(iVar1);
    iVar1 = grimlib_PlayMovie(iVar1,uVar9,uVar10,uVar6,uVar7);
    if (iVar1 == 1) {
      lua_pushnumber(1.0);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0049f0f0  sputLua_RotateVectorL ---- */
/* Lua opcode: RotateVector */

void sputLua_RotateVectorL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_istable(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_istable(iVar2);
    if (iVar3 != 0) {
      lua_pushobject(iVar1);
      lua_pushstring(&DAT_004e8454);
      iVar3 = lua_gettable();
      local_18[0] = lua_getnumber(iVar3);
      lua_pushobject(iVar1);
      lua_pushstring(&DAT_004e8450);
      iVar3 = lua_gettable();
      local_18[1] = lua_getnumber(iVar3);
      lua_pushobject(iVar1);
      lua_pushstring(&DAT_004ec3b8);
      iVar1 = lua_gettable();
      local_18[2] = lua_getnumber(iVar1);
      lua_pushobject(iVar2);
      lua_pushstring(&DAT_004e8454);
      iVar1 = lua_gettable();
      local_c[0] = lua_getnumber(iVar1);
      lua_pushobject(iVar2);
      lua_pushstring(&DAT_004e8450);
      iVar1 = lua_gettable();
      local_c[1] = lua_getnumber(iVar1);
      lua_pushobject(iVar2);
      lua_pushstring(&DAT_004ec3b8);
      iVar1 = lua_gettable();
      local_c[2] = lua_getnumber(iVar1);
      rdVector_Rotate3Acc(local_18,local_c);
      iVar1 = lua_createtable();
      lua_pushobject(iVar1);
      lua_pushstring(&DAT_004e8454);
      lua_pushnumber(local_18[0]);
      lua_settable();
      lua_pushobject(iVar1);
      lua_pushstring(&DAT_004e8450);
      lua_pushnumber(local_18[1]);
      lua_settable();
      lua_pushobject(iVar1);
      lua_pushstring(&DAT_004ec3b8);
      lua_pushnumber(local_18[2]);
      lua_settable();
      lua_pushobject(iVar1);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_18
#undef local_1c
#undef local_c


/* ---- 0x004a0f20  sputLua_ImStartRecording ---- */
/* Lua opcode: ImStartRecording */

void sputLua_ImStartRecording(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isstring(iVar1);
  if (iVar3 != 0) {
    iVar2 = lua_isnil(iVar2);
    uVar4 = (uint)(iVar2 == 0);
    iVar1 = lua_getstring(iVar1);
    ImStartRecording(iVar1,uVar4);
  }
  return;
}

/* ---- 0x004a0f80  sputLua_ImStartSound ---- */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* Lua opcodes: ImStartSound, play
   also registered as `play` */

void sputLua_ImStartSound(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_isstring(iVar1);
  if ((iVar4 == 0) && (iVar4 = lua_isnil(iVar1), iVar4 == 0)) {
    return;
  }
  iVar4 = lua_isnumber(iVar2);
  if ((iVar4 != 0) && (iVar4 = lua_isnumber(iVar3), iVar4 != 0)) {
    lVar5 = (longlong)lua_getnumber(iVar3);
    lVar6 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar6;
    iVar1 = lua_getstring(iVar1);
    iVar1 = SoundsLoadStartSound(iVar1,iVar2,(uint)lVar5);
    lua_pushnumber((float)iVar1);
  }
  return;
}
#undef local_18
#undef local_4


/* ---- 0x004a1030  sputLua_ImStopSound ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImStopSound */

void sputLua_ImStopSound(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    SoundsStopSound((int)lVar3);
    return;
  }
  iVar1 = lua_getstring(iVar1);
  SoundsStopSound(iVar1);
  return;
}

/* ---- 0x004a1090  sputLua_ImGetParam ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: ImGetParam */

void sputLua_ImGetParam(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  longlong lVar5;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(iVar1);
  if (iVar3 == 0) {
    iVar3 = lua_isstring(iVar2);
    if (iVar3 == 0) {
      lua_pushnumber(-1.0);
      return;
    }
    lVar5 = (longlong)lua_getnumber(iVar2);
    local_10 = (uint)lVar5;
    iVar1 = lua_getstring(iVar1);
  }
  else {
    lVar5 = (longlong)lua_getnumber(iVar2);
    local_10 = (uint)lVar5;
    lVar5 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar5;
  }
  uVar4 = SoundsGetParam(iVar1,local_10);
  lua_pushnumber((float)(int)uVar4);
  return;
}
#undef local_10
#undef local_4


/* ---- 0x004a1140  sputLua_ImSetParam ---- */
/* Lua opcode: ImSetParam */

void sputLua_ImSetParam(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  longlong lVar6;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_isnumber(iVar1);
  if ((iVar4 == 0) && (iVar4 = lua_isstring(iVar1), iVar4 == 0)) {
    return;
  }
  iVar4 = lua_isnumber(iVar2);
  if ((iVar4 != 0) && (iVar4 = lua_isnumber(iVar3), iVar4 != 0)) {
    iVar4 = lua_isnumber(iVar1);
    if (iVar4 != 0) {
      lVar6 = (longlong)lua_getnumber(iVar3);
      if ((int)lVar6 < 1) {
        uVar5 = 0;
      }
      else {
        lVar6 = (longlong)lua_getnumber(iVar3);
        uVar5 = (uint)lVar6;
      }
      lVar6 = (longlong)lua_getnumber(iVar2);
      iVar2 = (int)lVar6;
      lVar6 = (longlong)lua_getnumber(iVar1);
      SoundsSetParam((int)lVar6,iVar2,uVar5);
      return;
    }
    iVar4 = lua_isstring(iVar1);
    if (iVar4 != 0) {
      lVar6 = (longlong)lua_getnumber(iVar3);
      if ((int)lVar6 < 1) {
        uVar5 = 0;
      }
      else {
        lVar6 = (longlong)lua_getnumber(iVar3);
        uVar5 = (uint)lVar6;
      }
      lVar6 = (longlong)lua_getnumber(iVar2);
      iVar2 = (int)lVar6;
      iVar1 = lua_getstring(iVar1);
      SoundsSetParam(iVar1,iVar2,uVar5);
    }
  }
  return;
}

/* ---- 0x004a1260  sputLua_ImFadeParam ---- */
/* Lua opcode: ImFadeParam */

void sputLua_ImFadeParam(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  longlong lVar7;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_isstring(iVar1);
  if (iVar5 == 0) {
    iVar5 = lua_isnumber(iVar1);
    if (iVar5 == 0) {
      lua_pushnumber(0.0);
      return;
    }
  }
  iVar5 = lua_isnumber(iVar2);
  if (iVar5 != 0) {
    iVar5 = lua_isnumber(iVar3);
    if (iVar5 != 0) {
      iVar5 = lua_isnumber(iVar4);
      if (iVar5 != 0) {
        iVar5 = lua_isnumber(iVar1);
        if (iVar5 != 0) {
          lVar7 = (longlong)lua_getnumber(iVar3);
          if ((int)lVar7 < 1) {
            uVar6 = 0;
          }
          else {
            lVar7 = (longlong)lua_getnumber(iVar3);
            uVar6 = (uint)lVar7;
          }
          lVar7 = (longlong)lua_getnumber(iVar4);
          iVar3 = (int)lVar7;
          lVar7 = (longlong)lua_getnumber(iVar2);
          iVar2 = (int)lVar7;
          lVar7 = (longlong)lua_getnumber(iVar1);
          SoundsFadeParam((int)lVar7,iVar2,uVar6,iVar3);
          return;
        }
        lVar7 = (longlong)lua_getnumber(iVar3);
        if ((int)lVar7 < 1) {
          uVar6 = 0;
        }
        else {
          lVar7 = (longlong)lua_getnumber(iVar3);
          uVar6 = (uint)lVar7;
        }
        lVar7 = (longlong)lua_getnumber(iVar4);
        iVar3 = (int)lVar7;
        lVar7 = (longlong)lua_getnumber(iVar2);
        iVar2 = (int)lVar7;
        iVar1 = lua_getstring(iVar1);
        SoundsFadeParam(iVar1,iVar2,uVar6,iVar3);
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x004a1590  sputLua_ImStartVoice ---- */
/* Lua opcode: ImStartVoice */

void sputLua_ImStartVoice(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  longlong lVar6;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_isstring(iVar1);
  if ((iVar4 == 0) && (iVar4 = lua_isnil(iVar1), iVar4 == 0)) {
    return;
  }
  iVar4 = lua_isnumber(iVar2);
  if ((iVar4 != 0) && (iVar4 = lua_isnumber(iVar3), iVar4 != 0)) {
    lVar6 = (longlong)lua_getnumber(iVar3);
    uVar5 = (uint)lVar6;
    lVar6 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar6;
    iVar1 = lua_getstring(iVar1);
    SoundStartVoiceStream(iVar1,iVar2,uVar5);
  }
  return;
}

/* ---- 0x004a1680  sputLua_ImSetSequence ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Lua opcode: ImSetSequence */

void __fastcall sputLua_ImSetSequence(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  longlong lVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    iVar1 = ImSetSequence((int)lVar3);
    lua_pushnumber((float)iVar1);
  }
  return;
}
#undef local_4
#undef local_c


/* ---- 0x004a1710  sputLua_ImSetAttribute ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: ImSetAttribute */

void sputLua_ImSetAttribute(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_isnumber(iVar2);
    if (iVar3 != 0) {
      lVar4 = (longlong)lua_getnumber(iVar2);
      lVar5 = (longlong)lua_getnumber(iVar1);
      iVar1 = ImSetAttribute((int)lVar5,(int)lVar4);
      lua_pushnumber((float)iVar1);
    }
  }
  return;
}
#undef local_14
#undef local_4


/* ---- 0x004a17b0  sputLua_ImSetVoiceEffect ---- */
/* Lua opcodes: vfx, ImSetVoiceEffect
   also registered as `vfx` */

void sputLua_ImSetVoiceEffect(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if ((iVar2 == 0) && (iVar2 = lua_isnil(iVar1), iVar2 == 0)) {
    return;
  }
  iVar1 = lua_getstring(iVar1);
  iMUSE_SetVoiceEffect(iVar1);
  return;
}

/* ---- 0x004a2b00  sputLua_FadeInChore ---- */
/* Lua opcode: FadeInChore */

void sputLua_FadeInChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *luaObj;
  int iVar2;
  int iVar3;
  uint chore;
  longlong lVar4;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  luaObj = (void *)lua_lua2C(2);
  iVar2 = lua_lua2C(3);
  local_4 = lua_lua2C(4);
  iVar3 = lua_isuserdata(iVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(iVar1), iVar3 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    iVar1 = sputActor_ActorDeref(iVar1);
    lVar4 = (longlong)lua_getnumber(iVar2);
    chore = (uint)lVar4;
    lVar4 = (longlong)lua_getnumber(local_4);
    iVar2 = lua_isstring((int)luaObj);
    if ((iVar2 == 0) && (iVar2 = lua_isnumber((int)luaObj), iVar2 == 0)) {
      return;
    }
    iVar1 = FindCostumeInStack(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_8);
    if (iVar1 != 0) {
      Cos_InstPlayChore(*(int *)local_8,chore,0,0);
      Cos_InstUpdateChore(*(int *)local_8,chore,100);
      sputCostume_FadeKeysIn(*(void **)local_8,chore,(int)lVar4);
    }
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004a35d0  sputLua_SubmitSaveGameData ---- */
/* Lua opcode: SubmitSaveGameData */

void sputLua_SubmitSaveGameData(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  uint uVar7;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define uStack_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_10 = 0;
  iVar2 = lua_lua2C(1);
  g_nTotSaveBytes = 0;
  do {
    lua_pushobject(iVar2);
    local_4 = PUN(uint,(float)(float)(int)local_10);
    local_10 = local_10 + 1;
    lua_pushnumber(PUN(float,local_4));
    iVar3 = lua_gettable();
    iVar4 = lua_isnil(iVar3);
    if (iVar4 != 0) {
      if (g_nTotSaveBytes != 0) {
        (*(code *)g_pTheWriter)(&g_nTotSaveBytes,4);
        local_10 = 0;
        while( true ) {
          lua_pushobject(iVar2);
          local_4 = PUN(uint,(float)(float)(int)local_10);
          local_10 = local_10 + 1;
          lua_pushnumber(PUN(float,local_4));
          iVar3 = lua_gettable();
          iVar4 = lua_isnil(iVar3);
          if (iVar4 != 0) break;
          pcVar6 = (char *)lua_getstring(iVar3);
          uStack_8 = 0xffffffff;
          pcVar5 = pcVar6;
          do {
            if (uStack_8 == 0) break;
            uStack_8 = uStack_8 - 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar5 + 1;
          } while (cVar1 != '\0');
          uStack_8 = ~uStack_8;
          (*(code *)g_pTheWriter)(&uStack_8,4);
          (*(code *)g_pTheWriter)(pcVar6,uStack_8);
        }
      }
      return;
    }
    iVar4 = lua_isstring(iVar3);
    if (iVar4 == 0) {
      return;
    }
    pcVar5 = (char *)lua_getstring(iVar3);
    uVar7 = 0xffffffff;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    g_nTotSaveBytes = g_nTotSaveBytes + ~uVar7 + 4;
  } while( true );
}
#undef local_10
#undef local_4
#undef local_c
#undef uStack_8

