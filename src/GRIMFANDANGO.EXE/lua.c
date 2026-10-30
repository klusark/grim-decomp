/* GRIMFANDANGO.EXE :: lua.c
 * functions 0x00401ca0 .. 0x004be2a0 (300 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00401ca0  Lua_Is3DHardwareEnabled ---- */
/* Lua opcode: Is3DHardwareEnabled */

void Lua_Is3DHardwareEnabled(void)

{
  if (g_pD3dDriver != (void *)0x0) {
    lua_pushnumber(1.0);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00401cb8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lua_pushnil();
  return;
}

/* ---- 0x00401cc0  Lua_SetHardwareState ---- */
/* Lua opcode: SetHardwareState */

void Lua_SetHardwareState(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = lua_lua2C(1);
  uVar1 = UINT_00901758;
  uVar3 = UINT_00900530;
  if (g_pD3dDriver == (void *)0x0) {
    uVar3 = 0xffffffff;
  }
  iVar2 = lua_isnil(iVar2);
  Display_PickDefault(0,(uint)(iVar2 == 0),(int *)&UINT_004dd340,(int *)&UINT_004dd344,
                      (int *)&UINT_004dd348);
  if ((UINT_004dd340 != uVar1) || (UINT_004dd348 != uVar3)) {
    UINT_004f5a50 = 1;
  }
  return;
}

/* ---- 0x00401d30  Lua_GetVideoDevices ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: GetVideoDevices */

void Lua_GetVideoDevices(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  
  lua_pushnumber((float)UINT_00901758);
  if (g_pD3dDriver != (void *)0x0) {
    lua_pushnumber((float)UINT_00900530);
    return;
  }
  lua_pushnumber(-1.0);
  return;
}
#undef local_10


/* ---- 0x00401da0  Lua_SetVideoDevices ---- */
/* Lua opcode: SetVideoDevices */

void Lua_SetVideoDevices(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  longlong lVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  uVar1 = UINT_00901758;
  if (g_pD3dDriver == (void *)0x0) {
    local_4 = 0xffffffff;
  }
  else {
    local_4 = UINT_00900530;
  }
  iVar4 = lua_isnumber(iVar2);
  if (iVar4 != 0) {
    lua_isnumber(iVar3);
  }
  lVar6 = (longlong)lua_getnumber(iVar2);
  UINT_004dd340 = (uint)lVar6;
  puVar5 = (uint *)(UINT_004dd340 * 0x10 + (int)g_pDisplayModes);
  UINT_004dd344 = Display_FindClosestMode(&UINT_004f4d38,(void *)puVar5[1],*puVar5);
  lVar6 = (longlong)lua_getnumber(iVar3);
  UINT_004dd348 = (uint)lVar6;
  if ((((-1 < (int)UINT_004dd340) && ((int)UINT_004dd340 < (int)g_dwDisplayDeviceCount)) &&
      (-2 < (int)UINT_004dd348)) &&
     (((int)UINT_004dd348 < *(int *)(UINT_004dd340 * 0x10 + 8 + (int)g_pDisplayModes) &&
      ((UINT_004dd340 != uVar1 || (UINT_004dd348 != local_4)))))) {
    UINT_004f5a50 = 1;
  }
  return;
}
#undef local_4


/* ---- 0x00401e90  Lua_Enumerate3DDevices ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* Lua opcode: Enumerate3DDevices */

void Lua_Enumerate3DDevices(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *pvVar3;
  uint uVar4;
  int iVar5;
  longlong lVar6;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    return;
  }
  lVar6 = (longlong)lua_getnumber(iVar1);
  iVar1 = (int)lVar6;
  iVar2 = lua_createtable();
  if (((&UINT_00902d6c)[iVar1 * 0xa6] != 0) || ((&UINT_00902d68)[iVar1 * 0xa6] == 0)) {
    lua_pushobject(iVar2);
    lua_pushnumber(-1.0);
    lua_pushstring(s__engn003_Software_004dd688);
    lua_settable();
    if ((&UINT_00902d68)[iVar1 * 0xa6] == 0) goto LAB_00401f9e;
  }
  uVar4 = 0;
  iVar1 = iVar1 * 0x10;
  if (*(int *)((int)g_pDisplayModes + iVar1 + 8) != 0) {
    iVar5 = 0;
    pvVar3 = g_pDisplayModes;
    do {
      if (*(int *)(*(int *)((int)pvVar3 + iVar1 + 0xc) + iVar5) != 0) {
        lua_pushobject(iVar2);
        lua_pushnumber((float)uVar4);
        lua_pushstring((char *)(*(int *)((int)g_pDisplayModes + iVar1 + 0xc) + 200 + iVar5));
        lua_settable();
        pvVar3 = g_pDisplayModes;
      }
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 0x22c;
    } while (uVar4 < *(uint *)((int)pvVar3 + iVar1 + 8));
  }
LAB_00401f9e:
  lua_pushobject(iVar2);
  return;
}
#undef local_1c


/* ---- 0x00401fb0  Lua_EnumerateVideoDevices ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* Lua opcode: EnumerateVideoDevices */

void Lua_EnumerateVideoDevices(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  char *pcVar3;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  
  iVar1 = lua_createtable();
  uVar2 = (uint)(INT_004f5a24 == 0);
  if (uVar2 < g_dwDisplayDeviceCount) {
    pcVar3 = &DAT_00902ce0 + uVar2 * 0x298;
    do {
      lua_pushobject(iVar1);
      lua_pushnumber((float)uVar2);
      lua_pushstring(pcVar3);
      lua_settable();
      uVar2 = uVar2 + 1;
      pcVar3 = pcVar3 + 0x298;
    } while (uVar2 < g_dwDisplayDeviceCount);
  }
  lua_pushobject(iVar1);
  return;
}
#undef local_1c


/* ---- 0x00482880  Lua_NextSetup ---- */
/* Lua opcode: NextSetup */

void Lua_NextSetup(void)

{
  void *pvVar1;
  
  pvVar1 = Set_GetCurrent();
  Set_ChangeSetup((*(int *)((int)pvVar1 + 0xb4) + 1U) % *(uint *)((int)pvVar1 + 0xb0));
  return;
}

/* ---- 0x004828a0  Lua_PreviousSetup ---- */
/* Lua opcode: PreviousSetup */

void Lua_PreviousSetup(void)

{
  void *pvVar1;
  
  pvVar1 = Set_GetCurrent();
  Set_ChangeSetup((*(int *)((int)pvVar1 + 0xb4) + -1 + *(uint *)((int)pvVar1 + 0xb0)) %
                  *(uint *)((int)pvVar1 + 0xb0));
  return;
}

/* ---- 0x00486f50  Lua_IrisClear ---- */
/* Lua opcode: IrisClear */

void Lua_IrisClear(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_8 = 0x280;
  g_dwRenderFlags = g_dwRenderFlags & 0xfffffff3;
  local_4 = 0x1e0;
  local_c = 0;
  local_10 = 0;
  Render_InvalidateRect((int *)&local_10,0);
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00489840  Lua_DrawLine ---- */
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Lua opcode: DrawLine */

void Lua_DrawLine(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  longlong lVar7;
  longlong lVar8;
  longlong lVar9;
  longlong lVar10;
  longlong lVar11;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  
  local_18 = 2;
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  local_1c = lua_lua2C(4);
  iVar4 = lua_lua2C(5);
  iVar5 = lua_isnumber(iVar1);
  if (iVar5 != 0) {
    iVar5 = lua_isnumber(iVar2);
    if (iVar5 != 0) {
      iVar5 = lua_isnumber(iVar3);
      if (iVar5 != 0) {
        iVar5 = lua_isnumber(local_1c);
        if (iVar5 != 0) {
          lVar7 = (longlong)lua_getnumber(iVar1);
          lVar8 = (longlong)lua_getnumber(iVar2);
          lVar9 = (longlong)lua_getnumber(iVar3);
          lVar10 = (longlong)lua_getnumber(local_1c);
          iVar1 = lua_istable(iVar4);
          if (iVar1 != 0) {
            lua_pushobject(iVar4);
            lua_pushstring(PTR_s_color_004e8368);
            iVar1 = lua_gettable();
            iVar2 = lua_isuserdata(iVar1);
            if (iVar2 != 0) {
              iVar2 = lua_tag(iVar1);
              if (iVar2 == 0x524c4f43) {
                uVar6 = lua_getuserdata(iVar1);
                PIECE(local_1c,2,1) = (byte)(uVar6 >> 0x10);
                local_1c = ((uVar6 >> 8 & 0xff) >> ((byte)UINT_004ddac4 & 0x1f)) <<
                           ((byte)UINT_004ddab8 & 0x1f) & 0xffff |
                           (uint)(PIECE(local_1c,2,1) >> ((byte)UINT_004ddac8 & 0x1f)) <<
                           ((byte)UINT_004ddabc & 0x1f) & 0xffff |
                           ((uVar6 & 0xff) >> ((byte)UINT_004ddac0 & 0x1f)) <<
                           ((byte)UINT_004ddab4 & 0x1f) & 0xffff;
              }
            }
            lua_pushobject(iVar4);
            lua_pushstring(PTR_s_layer_004e8390);
            iVar1 = lua_gettable();
            iVar2 = lua_isnumber(iVar1);
            if (iVar2 != 0) {
              lVar11 = (longlong)lua_getnumber(iVar1);
              local_18 = (uint)lVar11;
            }
          }
          uVar6 = Primitive_AddLine(&UINT_008ca0a0,(int)lVar7,(int)lVar8,(int)lVar9,(int)lVar10,
                                    local_1c,local_18);
          lua_pushnumber((float)uVar6);
          return;
        }
      }
    }
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_30
#undef local_c


/* ---- 0x00489a80  Lua_DrawPolygon ---- */
/* WARNING: Variable defined which should be unmapped: local_38 */
/* Lua opcode: DrawPolygon */

void Lua_DrawPolygon(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint uVar7;
  code *pcVar8;
  longlong lVar9;
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x50 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x50 - 0xc)))
  
  local_c = 2;
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_istable(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_istable(iVar2);
    pcVar8 = lua_gettable_exref;
    if (iVar3 != 0) {
      lua_pushobject(iVar2);
      lua_pushstring(PTR_s_color_004e8368);
      pcVar8 = lua_gettable_exref;
      iVar3 = lua_gettable();
      iVar4 = lua_isuserdata(iVar3);
      if ((iVar4 != 0) && (iVar4 = lua_tag(iVar3), iVar4 == 0x524c4f43)) {
        uVar5 = lua_getuserdata(iVar3);
        PIECE(local_18,2,1) = (byte)(uVar5 >> 0x10);
        local_18 = ((uVar5 >> 8 & 0xff) >> ((byte)UINT_004ddac4 & 0x1f)) <<
                   ((byte)UINT_004ddab8 & 0x1f) & 0xffff |
                   (uint)(PIECE(local_18,2,1) >> ((byte)UINT_004ddac8 & 0x1f)) <<
                   ((byte)UINT_004ddabc & 0x1f) & 0xffff |
                   ((uVar5 & 0xff) >> ((byte)UINT_004ddac0 & 0x1f)) << ((byte)UINT_004ddab4 & 0x1f)
                   & 0xffff;
      }
      lua_pushobject(iVar2);
      lua_pushstring(PTR_s_layer_004e8390);
      iVar2 = lua_gettable();
      iVar3 = lua_isnumber(iVar2);
      if (iVar3 != 0) {
        lVar9 = (longlong)lua_getnumber(iVar2);
        local_c = (uint)lVar9;
      }
    }
    uVar5 = 0;
    local_24 = 1;
    do {
      lua_pushobject(iVar1);
      lua_pushnumber((float)(int)local_24);
      iVar2 = (*pcVar8)();
      iVar2 = lua_isnil(iVar2);
      if (iVar2 != 0) break;
      local_24 = local_24 + 2;
      uVar5 = uVar5 + 1;
    } while (uVar5 < 0xfa);
    if (0 < (int)uVar5) {
      local_14 = (uint)Plat_Alloc(uVar5 * 8);
      if ((undefined4 *)local_14 == (undefined4 *)0x0) {
        local_14 = 0;
      }
      else {
        puVar6 = (undefined4 *)local_14;
        uVar7 = uVar5;
        if (-1 < (int)(uVar5 - 1)) {
          do {
            *puVar6 = 0;
            puVar6[1] = 0;
            uVar7 = uVar7 - 1;
            puVar6 = puVar6 + 2;
          } while (uVar7 != 0);
        }
      }
      local_24 = 1;
      if (0 < (int)uVar5) {
        puVar6 = (undefined4 *)(local_14 + 4);
        local_10 = uVar5;
        do {
          lua_pushobject(iVar1);
          iVar3 = local_24 + 1;
          lua_pushnumber((float)(int)local_24);
          iVar2 = (*pcVar8)();
          lVar9 = (longlong)lua_getnumber(iVar2);
          puVar6[-1] = (int)lVar9;
          lua_pushobject(iVar1);
          local_24 = local_24 + 2;
          lua_pushnumber((float)iVar3);
          iVar2 = (*pcVar8)();
          iVar3 = lua_isnil(iVar2);
          if (iVar3 == 0) {
            lVar9 = (longlong)lua_getnumber(iVar2);
            *puVar6 = (int)lVar9;
          }
          else {
            *puVar6 = 0;
          }
          puVar6 = puVar6 + 2;
          local_10 = local_10 - 1;
          pcVar8 = lua_gettable_exref;
        } while (local_10 != 0);
      }
      uVar5 = Primitive_AddPolyline(&UINT_008ca0a0,uVar5,(int *)local_14,local_18,local_c);
      lua_pushnumber((float)uVar5);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_38
#undef local_c


/* ---- 0x00489d70  Lua_DrawRectangle ---- */
/* WARNING: Variable defined which should be unmapped: local_34 */
/* Lua opcode: DrawRectangle */

void Lua_DrawRectangle(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  longlong lVar8;
  longlong lVar9;
  longlong lVar10;
  longlong lVar11;
  longlong lVar12;
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x50 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x50 - 0xc)))
  
  local_20 = 0;
  local_14 = 0;
  local_18 = 2;
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  iVar6 = lua_isnumber(iVar1);
  if ((((iVar6 != 0) && (iVar6 = lua_isnumber(iVar2), iVar6 != 0)) &&
      (iVar6 = lua_isnumber(iVar3), iVar6 != 0)) && (iVar6 = lua_isnumber(iVar4), iVar6 != 0)) {
    lVar8 = (longlong)lua_getnumber(iVar1);
    lVar9 = (longlong)lua_getnumber(iVar2);
    lVar10 = (longlong)lua_getnumber(iVar3);
    lVar11 = (longlong)lua_getnumber(iVar4);
    iVar1 = lua_istable(iVar5);
    if (iVar1 != 0) {
      lua_pushobject(iVar5);
      lua_pushstring(PTR_s_color_004e8368);
      iVar1 = lua_gettable();
      iVar2 = lua_isuserdata(iVar1);
      if ((iVar2 != 0) && (iVar2 = lua_tag(iVar1), iVar2 == 0x524c4f43)) {
        uVar7 = lua_getuserdata(iVar1);
        PIECE(local_20,2,1) = (byte)(uVar7 >> 0x10);
        local_20 = ((uVar7 >> 8 & 0xff) >> ((byte)UINT_004ddac4 & 0x1f)) <<
                   ((byte)UINT_004ddab8 & 0x1f) & 0xffff |
                   (uint)(PIECE(local_20,2,1) >> ((byte)UINT_004ddac8 & 0x1f)) <<
                   ((byte)UINT_004ddabc & 0x1f) & 0xffff |
                   ((uVar7 & 0xff) >> ((byte)UINT_004ddac0 & 0x1f)) << ((byte)UINT_004ddab4 & 0x1f)
                   & 0xffff;
      }
      lua_pushobject(iVar5);
      lua_pushstring(PTR_s_filled_004e838c);
      iVar1 = lua_gettable();
      iVar1 = lua_isnil(iVar1);
      local_14 = (uint)(iVar1 == 0);
      lua_pushobject(iVar5);
      lua_pushstring(PTR_s_layer_004e8390);
      iVar1 = lua_gettable();
      iVar2 = lua_isnumber(iVar1);
      if (iVar2 != 0) {
        lVar12 = (longlong)lua_getnumber(iVar1);
        local_18 = (uint)lVar12;
      }
    }
    uVar7 = Primitive_AddRect(&UINT_008ca0a0,(int)lVar8,(int)lVar9,(int)lVar10,(int)lVar11,local_20,
                              local_14,local_18);
    lua_pushnumber((float)uVar7);
    return;
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_34
#undef local_c


/* ---- 0x00489fe0  Lua_ChangePrimitive ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: ChangePrimitive */

void Lua_ChangePrimitive(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  longlong lVar7;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(iVar1);
  if (iVar3 == 0) {
    return;
  }
  iVar3 = lua_istable(iVar2);
  if (iVar3 != 0) {
    lVar7 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar7;
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_color_004e8368);
    iVar3 = lua_gettable();
    iVar4 = lua_isuserdata(iVar3);
    if ((iVar4 != 0) && (iVar4 = lua_tag(iVar3), iVar4 == 0x524c4f43)) {
      uVar5 = lua_getuserdata(iVar3);
      PIECE(local_10,2,1) = (byte)(uVar5 >> 0x10);
      Primitive_SetColor(&UINT_008ca0a0,iVar1,
                         (uint)(PIECE(local_10,2,1) >> ((byte)UINT_004ddac8 & 0x1f)) <<
                         ((byte)UINT_004ddabc & 0x1f) & 0xffff |
                         ((uVar5 >> 8 & 0xff) >> ((byte)UINT_004ddac4 & 0x1f)) <<
                         ((byte)UINT_004ddab8 & 0x1f) & 0xffff |
                         ((uVar5 & 0xff) >> ((byte)UINT_004ddac0 & 0x1f)) <<
                         ((byte)UINT_004ddab4 & 0x1f) & 0xffff);
    }
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_layer_004e8390);
    iVar3 = lua_gettable();
    iVar4 = lua_isnumber(iVar3);
    if (iVar4 != 0) {
      lVar7 = (longlong)lua_getnumber(iVar3);
      Primitive_SetLayer(&UINT_008ca0a0,iVar1,(int)lVar7);
    }
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_xoffset_004e836c);
    iVar3 = lua_gettable();
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_yoffset_004e8370);
    iVar4 = lua_gettable();
    iVar6 = lua_isnumber(iVar3);
    if ((iVar6 != 0) || (iVar6 = lua_isnumber(iVar4), iVar6 != 0)) {
      local_8 = 0;
      iVar6 = lua_isnumber(iVar3);
      if (iVar6 != 0) {
        lVar7 = (longlong)lua_getnumber(iVar3);
        local_8 = (uint)lVar7;
      }
      iVar3 = lua_isnumber(iVar4);
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        lVar7 = (longlong)lua_getnumber(iVar4);
        iVar3 = (int)lVar7;
      }
      Primitive_Offset(&UINT_008ca0a0,iVar1,local_8,iVar3);
    }
    lua_pushobject(iVar2);
    lua_pushstring(PTR_DAT_004e8374);
    iVar3 = lua_gettable();
    lua_pushobject(iVar2);
    lua_pushstring(PTR_DAT_004e8378);
    iVar4 = lua_gettable();
    iVar6 = lua_isnumber(iVar3);
    if ((iVar6 != 0) || (iVar6 = lua_isnumber(iVar4), iVar6 != 0)) {
      local_8 = 0xffffffff;
      iVar6 = lua_isnumber(iVar3);
      if (iVar6 != 0) {
        lVar7 = (longlong)lua_getnumber(iVar3);
        local_8 = (uint)lVar7;
      }
      iVar3 = lua_isnumber(iVar4);
      if (iVar3 == 0) {
        iVar3 = -1;
      }
      else {
        lVar7 = (longlong)lua_getnumber(iVar4);
        iVar3 = (int)lVar7;
      }
      Primitive_MoveTo(&UINT_008ca0a0,iVar1,local_8,iVar3);
    }
    lua_pushobject(iVar2);
    lua_pushstring(PTR_DAT_004e837c);
    iVar3 = lua_gettable();
    lua_pushobject(iVar2);
    lua_pushstring(PTR_DAT_004e8380);
    iVar4 = lua_gettable();
    iVar6 = lua_isnumber(iVar3);
    if ((iVar6 != 0) || (iVar6 = lua_isnumber(iVar4), iVar6 != 0)) {
      local_8 = 0xffffffff;
      iVar6 = lua_isnumber(iVar3);
      if (iVar6 != 0) {
        lVar7 = (longlong)lua_getnumber(iVar3);
        local_8 = (uint)lVar7;
      }
      iVar3 = lua_isnumber(iVar4);
      if (iVar3 == 0) {
        iVar3 = -1;
      }
      else {
        lVar7 = (longlong)lua_getnumber(iVar4);
        iVar3 = (int)lVar7;
      }
      Primitive_SetEnd(&UINT_008ca0a0,iVar1,local_8,iVar3);
    }
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_width_004e8384);
    iVar3 = lua_gettable();
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_height_004e8388);
    iVar2 = lua_gettable();
    iVar4 = lua_isnumber(iVar3);
    if ((iVar4 == 0) && (iVar4 = lua_isnumber(iVar2), iVar4 == 0)) {
      return;
    }
    iVar6 = -1;
    iVar4 = lua_isnumber(iVar3);
    if (iVar4 == 0) {
      iVar3 = -1;
    }
    else {
      lVar7 = (longlong)lua_getnumber(iVar3);
      iVar3 = (int)lVar7;
    }
    iVar4 = lua_isnumber(iVar2);
    if (iVar4 != 0) {
      lVar7 = (longlong)lua_getnumber(iVar2);
      iVar6 = (int)lVar7;
    }
    Primitive_SetSize(&UINT_008ca0a0,iVar1,iVar3,iVar6);
    return;
  }
  return;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x0048a460  Lua_KillPrimitive ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: KillPrimitive */

void __cdecl Lua_KillPrimitive(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    Primitive_Kill(&UINT_008ca0a0,(int)lVar3);
  }
  return;
}

/* ---- 0x0048a4a0  Lua_PurgePrimitiveQueue ---- */
/* Lua opcode: PurgePrimitiveQueue */

void Lua_PurgePrimitiveQueue(void)

{
  PrimitiveList_Clear((int *)&UINT_008ca0a0);
  Primitive_ResetIds();
  return;
}

/* ---- 0x0048ad60  Lua_SetOffscreenTextPos ---- */
/* Lua opcode: SetOffscreenTextPos */

void Lua_SetOffscreenTextPos(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(iVar1);
  if (iVar3 == 0) {
    g_nSubtitleDefaultX = 0x140;
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    g_nSubtitleDefaultX = (int)lVar4;
  }
  iVar1 = lua_isnumber(iVar2);
  if (iVar1 != 0) {
    lVar4 = (longlong)lua_getnumber(iVar2);
    g_nSubtitleDefaultY = (int)lVar4;
    return;
  }
  g_nSubtitleDefaultY = 0x1c2;
  return;
}

/* ---- 0x0048ade0  Lua_SetEmergencyFont ---- */
/* Lua opcode: SetEmergencyFont */

void Lua_SetEmergencyFont(void)

{
  int iVar1;
  int iVar2;
  char *filename;
  void **outFont;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    if (g_pOverrideFont != (void *)0x0) {
      Font_Free(g_pOverrideFont);
      g_pOverrideFont = (void *)0x0;
    }
    outFont = &g_pOverrideFont;
    filename = (char *)lua_getstring(iVar1);
    Font_LoadFile(filename,outFont);
    return;
  }
  iVar1 = lua_isnil(iVar1);
  if ((iVar1 != 0) && (g_pOverrideFont != (void *)0x0)) {
    Font_Free(g_pOverrideFont);
    g_pOverrideFont = (void *)0x0;
  }
  return;
}

/* ---- 0x0048ae60  Lua_LocalizeString ---- */
/* Lua opcode: LocalizeString */

void Lua_LocalizeString(void)

{
  unsigned char _frame[0x2b0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *line;
  char *pcVar3;
  #define local_2a0 (*(char (*)[32])(_frame + (0x2b0 - 0x2a0)))
  #define local_280 (*(char (*)[640])(_frame + (0x2b0 - 0x280)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    pcVar3 = local_2a0;
    line = (char *)lua_getstring(iVar1);
    pcVar3 = Text_ParseLineId(line,pcVar3);
    sprintf(local_280,s___s__s_004e8754,local_2a0,pcVar3);
    lua_pushstring(local_280);
  }
  return;
}
#undef local_280
#undef local_2a0


/* ---- 0x0048aed0  Lua_MakeColor ---- */
/* Lua opcode: MakeColor */

void Lua_MakeColor(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  longlong lVar9;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar3 = lua_lua2C(1);
  iVar4 = lua_lua2C(2);
  iVar5 = lua_lua2C(3);
  iVar6 = lua_lua2C(4);
  iVar7 = lua_isnumber(iVar3);
  if (iVar7 == 0) {
    iVar7 = 0;
  }
  else {
    lVar9 = (longlong)lua_getnumber(iVar3);
    iVar7 = (int)lVar9;
  }
  uVar8 = 0;
  if (iVar7 < 0) {
LAB_0048af7b:
    local_c = 0;
  }
  else {
    iVar7 = lua_isnumber(iVar3);
    if (iVar7 == 0) {
      iVar7 = 0;
    }
    else {
      lVar9 = (longlong)lua_getnumber(iVar3);
      iVar7 = (int)lVar9;
    }
    if (iVar7 < 0x100) {
      iVar7 = lua_isnumber(iVar3);
      if (iVar7 == 0) goto LAB_0048af7b;
      lVar9 = (longlong)lua_getnumber(iVar3);
      local_c = (uint)lVar9;
    }
    else {
      local_c = 0xff;
    }
  }
  iVar3 = lua_isnumber(iVar4);
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    lVar9 = (longlong)lua_getnumber(iVar4);
    iVar3 = (int)lVar9;
  }
  if (-1 < iVar3) {
    iVar3 = lua_isnumber(iVar4);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      lVar9 = (longlong)lua_getnumber(iVar4);
      iVar3 = (int)lVar9;
    }
    if (iVar3 < 0x100) {
      iVar3 = lua_isnumber(iVar4);
      if (iVar3 != 0) {
        lVar9 = (longlong)lua_getnumber(iVar4);
        uVar8 = (uint)lVar9;
      }
    }
    else {
      uVar8 = 0xff;
    }
  }
  iVar3 = lua_isnumber(iVar5);
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    lVar9 = (longlong)lua_getnumber(iVar5);
    iVar3 = (int)lVar9;
  }
  if (iVar3 < 0) {
LAB_0048b053:
    uVar1 = 0;
  }
  else {
    iVar3 = lua_isnumber(iVar5);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      lVar9 = (longlong)lua_getnumber(iVar5);
      iVar3 = (int)lVar9;
    }
    if (iVar3 < 0x100) {
      iVar3 = lua_isnumber(iVar5);
      if (iVar3 == 0) goto LAB_0048b053;
      lVar9 = (longlong)lua_getnumber(iVar5);
      uVar1 = (undefined1)lVar9;
    }
    else {
      uVar1 = 0xff;
    }
  }
  iVar3 = lua_isnumber(iVar6);
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    lVar9 = (longlong)lua_getnumber(iVar6);
    iVar3 = (int)lVar9;
  }
  if (-1 < iVar3) {
    iVar3 = lua_isnumber(iVar6);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      lVar9 = (longlong)lua_getnumber(iVar6);
      iVar3 = (int)lVar9;
    }
    if (0xff < iVar3) {
      uVar2 = 0xff;
      goto LAB_0048b0c2;
    }
    iVar3 = lua_isnumber(iVar6);
    if (iVar3 != 0) {
      lVar9 = (longlong)lua_getnumber(iVar6);
      uVar2 = (undefined1)lVar9;
      goto LAB_0048b0c2;
    }
  }
  uVar2 = 0;
LAB_0048b0c2:
  lua_pushusertag((char *)(((uint)CONCAT11(uVar2,uVar1) << 8 | uVar8 & 0xff) << 8 | local_c & 0xff),
                  0x524c4f43);
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0048b100  Lua_GetColorComponents ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: GetColorComponents */

void Lua_GetColorComponents(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  iVar1 = lua_lua2C(1);
  uVar2 = lua_getuserdata(iVar1);
  lua_pushnumber((float)(uVar2 & 0xff));
  lua_pushnumber((float)(uVar2 >> 8 & 0xff));
  lua_pushnumber((float)(uVar2 >> 0x10 & 0xff));
  return;
}
#undef local_14


/* ---- 0x0048b190  Lua_SetActorTalkColor ---- */
/* Lua opcode: SetActorTalkColor */

void Lua_SetActorTalkColor(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      iVar3 = lua_isuserdata(iVar2);
      if (iVar3 != 0) {
        iVar3 = lua_tag(iVar2);
        if (iVar3 == 0x524c4f43) {
          iVar2 = lua_getuserdata(iVar2);
          *(int *)(*(int *)(iVar1 + 0xa4) + 0x418) = iVar2;
        }
      }
    }
  }
  return;
}

/* ---- 0x0048b230  Lua_GetActorTalkColor ---- */
/* Lua opcode: GetActorTalkColor */

void Lua_GetActorTalkColor(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) != 0) {
        lua_pushusertag(*(char **)(*(int *)(iVar1 + 0xa4) + 0x418),0x524c4f43);
        return;
      }
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0048b2a0  Lua_SetSayLineDefaults ---- */
/* Lua opcode: SetSayLineDefaults */

void Lua_SetSayLineDefaults(void)

{
  void *table;
  int iVar1;
  
  table = (void *)lua_lua2C(1);
  if (table != (void *)0x0) {
    iVar1 = lua_istable((int)table);
    if (iVar1 != 0) {
      Text_ParseLuaTable(&g_SubtitleTextCtx,table,(void *)0x0);
    }
  }
  return;
}

/* ---- 0x0048b4c0  Lua_SayLine ---- */
/* Lua opcode: SayLine */

void Lua_SayLine(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  code *pcVar3;
  int iVar4;
  #define local_3c (*(uint *)(_frame + (0x50 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(char (*)[32])(_frame + (0x50 - 0x20)))
  
  local_34 = 0;
  local_3c = 1;
  local_24 = 0x7f;
  local_28 = 0x40;
  local_2c = 0xffffffff;
  local_30 = 0xffffffff;
  iVar4 = 2;
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if ((((iVar2 != 0) && (iVar2 = lua_tag(iVar1), iVar2 == 0x52544341)) ||
      (iVar2 = lua_isstring(iVar1), iVar2 != 0)) || (iVar2 = lua_istable(iVar1), iVar2 != 0)) {
    local_38 = (uint)g_pSelectedActor;
    iVar2 = lua_isuserdata(iVar1);
    pcVar3 = lua_lua2C_exref;
    if ((iVar2 != 0) && (iVar2 = lua_tag(iVar1), pcVar3 = lua_lua2C_exref, iVar2 == 0x52544341)) {
      iVar1 = lua_getuserdata(iVar1);
      local_38 = Actor_FromHandle(iVar1);
      pcVar3 = lua_lua2C_exref;
      iVar4 = 3;
      iVar1 = lua_lua2C(2);
    }
    if (local_38 != 0) {
      iVar2 = lua_isnil(iVar1);
      while (iVar2 == 0) {
        iVar2 = lua_isstring(iVar1);
        if (((iVar2 == 0) && (iVar2 = lua_isnumber(iVar1), iVar2 == 0)) &&
           (iVar2 = lua_istable(iVar1), iVar2 == 0)) {
          return;
        }
        iVar2 = lua_istable(iVar1);
        if (iVar2 == 0) {
          iVar2 = lua_isnumber(iVar1);
          if (iVar2 == 0) {
            local_34 = lua_getstring(iVar1);
            Text_ParseLineId((char *)local_34,local_20);
          }
          else {
            local_3c = 0;
          }
        }
        else {
          Lua_ParseSayLineTable(iVar1,&local_3c,&local_24,&local_28,&local_2c,&local_30);
        }
        iVar1 = (*pcVar3)(iVar4);
        iVar2 = lua_isnil(iVar1);
        iVar4 = iVar4 + 1;
      }
      if ((char *)local_34 != (char *)0x0) {
        Actor_SayLine((void *)local_38,(char *)local_34,local_3c,local_24,local_28,local_2c,local_30
                     );
      }
    }
  }
  return;
}
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c


/* ---- 0x0048b6a0  Lua_ParseSayLineTable ---- */
/* Reads volume, pan, background, x, y overrides from the SayLine options table */

void Lua_ParseSayLineTable
               (int param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  lua_pushobject(param_1);
  iVar1 = lua_getref(UINT_008ca0dc);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (*param_5 != 0)) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    *param_5 = (int)lVar3;
  }
  lua_pushobject(param_1);
  iVar1 = lua_getref(UINT_008ca0e0);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (*param_6 != 0)) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    *param_6 = (int)lVar3;
  }
  lua_pushobject(param_1);
  iVar1 = lua_getref(UINT_008ca0e4);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar1 = lua_isnil(iVar1);
  if ((iVar1 == 0) && (*param_2 != 0)) {
    *param_2 = 0;
  }
  lua_pushobject(param_1);
  iVar1 = lua_getref(UINT_008ca100);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (*param_3 != 0)) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    *param_3 = (int)lVar3;
  }
  lua_pushobject(param_1);
  iVar1 = lua_getref(UINT_008ca114);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (*param_4 != 0)) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    *param_4 = (int)lVar3;
  }
  return;
}

/* ---- 0x0048b830  Lua_PrintLine ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: PrintLine */

void Lua_PrintLine(void)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  undefined4 unaff_ESI;
  uint *puVar7;
  undefined4 unaff_EDI;
  uint *puVar8;
  longlong lVar9;
  #define local_5c (*(uint *)(_frame + (0x70 - 0x5c)))
  #define local_58 (*(int *)(_frame + (0x70 - 0x58)))
  #define local_50 (*(char (*)[32])(_frame + (0x70 - 0x50)))
  #define local_30 (*(uint (*)[12])(_frame + (0x70 - 0x30)))
  
  iVar2 = lua_lua2C(1);
  pvVar3 = (void *)lua_lua2C(2);
  local_58 = -1;
  if ((int)UINT_008a94bc <= (int)UINT_004e8480) {
    UINT_004e8480 = UINT_008a94bc;
  }
  if ((int)UINT_008a94c0 <= (int)UINT_004e8484) {
    UINT_004e8484 = UINT_008a94c0;
  }
  iVar4 = lua_isstring(iVar2);
  if (((iVar4 != 0) || (iVar4 = lua_isnil(iVar2), iVar4 != 0)) &&
     ((iVar4 = lua_istable((int)pvVar3), iVar4 != 0 || (iVar4 = lua_isnil((int)pvVar3), iVar4 != 0))
     )) {
    iVar4 = lua_isnil(iVar2);
    if (iVar4 == 0) {
      local_5c = (uint)local_30;
      puVar7 = &g_PrintLineTextCtx;
      puVar8 = local_30;
      for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
    }
    else {
      local_5c = (uint)&g_PrintLineTextCtx;
    }
    iVar4 = lua_istable((int)pvVar3);
    if (iVar4 != 0) {
      local_58 = Text_ParseLuaTable((void *)local_5c,pvVar3,(void *)0x0);
    }
    iVar4 = lua_isstring(iVar2);
    if (iVar4 != 0) {
      pcVar6 = local_50;
      pcVar5 = (char *)lua_getstring(iVar2);
      pcVar6 = Text_ParseLineId(pcVar5,pcVar6);
      if (local_58 < 0) {
        iVar2 = -1;
        pcVar5 = pcVar6;
        do {
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar1 != '\0');
        lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        local_58 = (int)lVar9;
      }
      iVar2 = 0;
      pvVar3 = TextObject_New((void *)local_5c,pcVar6);
      TextObject_Activate(pvVar3,local_58,iVar2);
    }
  }
  return;
}
#undef local_30
#undef local_50
#undef local_58
#undef local_5c

#endif


/* ---- 0x0048b9a0  Lua_IsMessageGoing ---- */
/* Lua opcode: IsMessageGoing */

void Lua_IsMessageGoing(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = lua_lua2C(1);
  if ((iVar2 == 0) ||
     (((iVar3 = lua_isuserdata(iVar2), iVar3 != 0 && (iVar3 = lua_tag(iVar2), iVar3 == 0x52544341))
      || (iVar3 = lua_isnil(iVar2), iVar3 != 0)))) {
    iVar3 = lua_isuserdata(iVar2);
    if ((iVar3 == 0) || (iVar3 = lua_tag(iVar2), iVar3 != 0x52544341)) {
      puVar1 = g_pTextObjectList;
      iVar2 = Render_GetFrameCounter();
      if (iVar2 != 0) {
        lua_pushnumber(1.0);
        return;
      }
      for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
        if ((*(byte *)(puVar1 + 0x96) & 1) == 0) goto LAB_0048ba30;
      }
    }
    else {
      iVar2 = lua_getuserdata(iVar2);
      iVar2 = Actor_FromHandle(iVar2);
      if (((iVar2 != 0) && (*(int *)(iVar2 + 0xa4) != 0)) &&
         (*(int *)(*(int *)(iVar2 + 0xa4) + 0x1c4) != 0)) {
LAB_0048ba30:
        lua_pushnumber(1.0);
        return;
      }
    }
    lua_pushnil();
  }
  return;
}

/* ---- 0x0048ba90  Lua_ExpireText ---- */
/* Lua opcode: ExpireText */

void Lua_ExpireText(void)

{
  undefined4 *obj;
  
  for (obj = g_pTextObjectList; obj != (undefined4 *)0x0; obj = (undefined4 *)*obj) {
    if ((*(byte *)(obj + 0x96) & 4) != 0) {
      List_Unlink(obj);
      obj[0x96] = obj[0x96] & 0xfffffffa;
      *(undefined4 *)(*(int *)(obj[0x95] + 0xa4) + 0x1ec) = 0;
    }
    obj[0x94] = 0xffffffff;
  }
  return;
}

/* ---- 0x0048baf0  Lua_PurgeText ---- */
/* Lua opcode: PurgeText */

void Lua_PurgeText(void)

{
  undefined4 *puVar1;
  
  for (puVar1 = g_pTextObjectList; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    puVar1[0x94] = 0xffffffff;
    puVar1[0x96] = puVar1[0x96] & 0xfffffffe;
  }
  return;
}

/* ---- 0x0048bb20  Lua_KillTextObject ---- */
/* Lua opcode: KillTextObject */

void Lua_KillTextObject(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  if (iVar1 != 0) {
    iVar2 = lua_isuserdata(iVar1);
    if (iVar2 != 0) {
      iVar2 = lua_tag(iVar1);
      if (iVar2 == 0x54584554) {
        iVar1 = lua_getuserdata(iVar1);
        *(uint *)(iVar1 + 600) = *(uint *)(iVar1 + 600) & 0xfffffffe;
      }
    }
  }
  return;
}

/* ---- 0x0048bb70  Lua_GetFontDimensions ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetFontDimensions */

void Lua_GetFontDimensions(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  piVar1 = (int *)lua_lua2C(1);
  lua_pushnumber((float)*(int *)(*piVar1 + 4));
  lua_pushnumber((float)*(int *)(*piVar1 + 8));
  lua_pushnumber((float)*(int *)(*piVar1 + 0xc));
  lua_pushnumber((float)*(int *)(*piVar1 + 0x10));
  return;
}
#undef local_c


/* ---- 0x0048bbc0  Lua_GetTextObjectDimensions ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: GetTextObjectDimensions */

void Lua_GetTextObjectDimensions(void)

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
    if (iVar2 == 0x54584554) {
      iVar1 = lua_getuserdata(iVar1);
      iVar2 = Text_MeasureWidth((void *)(iVar1 + 0x208),(char *)(iVar1 + 8));
      lua_pushnumber((float)iVar2);
      iVar1 = Text_MeasureHeight((void *)(iVar1 + 0x208),(char *)(iVar1 + 8));
      lua_pushnumber((float)iVar1);
    }
  }
  return;
}
#undef local_14
#undef local_4


/* ---- 0x0048bc50  Lua_GetTextCharPosition ---- */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* Lua opcode: GetTextCharPosition */

void Lua_GetTextCharPosition(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  longlong lVar5;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x54584554) {
      iVar1 = lua_getuserdata(iVar1);
      lVar5 = (longlong)lua_getnumber(iVar2);
      local_4 = 0;
      if (0 < (int)lVar5) {
        pcVar4 = (char *)(iVar1 + 8);
        do {
          if (*pcVar4 == '\0') break;
          iVar2 = Text_CharWidth((void *)(iVar1 + 0x208),(int)*pcVar4);
          local_4 = local_4 + iVar2;
          pcVar4 = pcVar4 + 1;
        } while ((int)(pcVar4 + (-8 - iVar1)) < (int)lVar5);
      }
      lua_pushnumber((float)(int)local_4);
    }
  }
  return;
}
#undef local_18
#undef local_4


/* ---- 0x0048bd10  Lua_ChangeTextObject ---- */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* Lua opcode: ChangeTextObject */

void Lua_ChangeTextObject(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *textObj;
  void *table;
  char *pcVar3;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x54584554) {
      textObj = (void *)lua_getuserdata(iVar1);
      local_4 = 0;
      iVar1 = 2;
      do {
        table = (void *)lua_lua2C(iVar1);
        if (table == (void *)0x0) break;
        iVar2 = lua_isstring((int)table);
        if (iVar2 == 0) {
          iVar2 = lua_istable((int)table);
          if (iVar2 == 0) break;
          Text_ParseLuaTable((void *)((int)textObj + 0x208),table,textObj);
        }
        else {
          pcVar3 = (char *)lua_getstring((int)table);
          pcVar3 = Text_ParseLineId(pcVar3,(char *)0x0);
          strncpy((int)textObj + 8,pcVar3,0x1ff);
          *(undefined1 *)((int)textObj + 0x207) = 0;
        }
        local_4 = local_4 + 1;
        iVar1 = iVar1 + 1;
      } while ((int)local_4 < 2);
      iVar1 = Text_MeasureWidth((void *)((int)textObj + 0x208),(char *)((int)textObj + 8));
      lua_pushnumber((float)iVar1);
      iVar1 = Text_MeasureHeight((void *)((int)textObj + 0x208),(char *)((int)textObj + 8));
      lua_pushnumber((float)iVar1);
    }
  }
  return;
}
#undef local_18
#undef local_4


/* ---- 0x0048be30  Lua_MakeTextObject ---- */
/* WARNING: Variable defined which should be unmapped: local_78 */
/* Lua opcode: MakeTextObject */

void Lua_MakeTextObject(void)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *pcVar3;
  void *table;
  uint *puVar4;
  uint *puVar5;
  #define local_78 (*(uint *)(_frame + (0x90 - 0x78)))
  #define local_64 (*(uint *)(_frame + (0x90 - 0x64)))
  #define local_60 (*(uint *)(_frame + (0x90 - 0x60)))
  #define local_5c (*(uint *)(_frame + (0x90 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x90 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x90 - 0x54)))
  #define local_50 (*(char (*)[32])(_frame + (0x90 - 0x50)))
  #define local_30 (*(uint *)(_frame + (0x90 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x90 - 0x2c)))
  
  local_60 = 0;
  local_5c = 0;
  local_58 = UINT_008a94bc;
  local_54 = UINT_008a94c0;
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    pcVar3 = (char *)lua_getstring(iVar1);
    puVar4 = &g_TextObjectCtx;
    puVar5 = &local_30;
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    local_2c = (uint)&local_60;
    table = (void *)lua_lua2C(2);
    if (table != (void *)0x0) {
      iVar1 = lua_istable((int)table);
      if (iVar1 != 0) {
        Text_ParseLuaTable(&local_30,table,(void *)0x0);
      }
    }
    pcVar3 = Text_ParseLineId(pcVar3,local_50);
    pcVar3 = TextObject_New(&local_30,pcVar3);
    lua_pushusertag(pcVar3,0x54584554);
    iVar1 = Text_MeasureWidth(pcVar3 + 0x208,pcVar3 + 8);
    lua_pushnumber((float)iVar1);
    iVar1 = Text_MeasureHeight(pcVar3 + 0x208,pcVar3 + 8);
    lua_pushnumber((float)iVar1);
    TextObject_Activate(pcVar3,0,1);
  }
  return;
}
#undef local_2c
#undef local_30
#undef local_50
#undef local_54
#undef local_58
#undef local_5c
#undef local_60
#undef local_64
#undef local_78


/* ---- 0x0048bf50  Lua_BlastText ---- */
/* Lua opcode: BlastText */

void Lua_BlastText(void)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *pcVar3;
  void *pvVar4;
  void *surface;
  uint *puVar5;
  uint *puVar6;
  #define local_60 (*(uint *)(_frame + (0x70 - 0x60)))
  #define local_5c (*(uint *)(_frame + (0x70 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x70 - 0x54)))
  #define local_50 (*(char (*)[32])(_frame + (0x70 - 0x50)))
  #define local_30 (*(uint *)(_frame + (0x70 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x70 - 0x2c)))
  
  local_60 = 0;
  local_5c = 0;
  local_58 = UINT_008a94bc;
  local_54 = UINT_008a94c0;
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    pcVar3 = (char *)lua_getstring(iVar1);
    pvVar4 = (void *)Render_GetBackBuffer();
    Surface_Lock(pvVar4);
    puVar5 = &g_TextObjectCtx;
    puVar6 = &local_30;
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    iVar1 = Render_GetBackBuffer();
    local_2c = (uint)&local_60;
    *(undefined4 *)local_30 = *(undefined4 *)(iVar1 + 0x5c);
    pvVar4 = (void *)lua_lua2C(2);
    if (pvVar4 != (void *)0x0) {
      iVar1 = lua_istable((int)pvVar4);
      if (iVar1 != 0) {
        Text_ParseLuaTable(&local_30,pvVar4,(void *)0x0);
      }
    }
    pcVar3 = Text_ParseLineId(pcVar3,local_50);
    pvVar4 = TextObject_New(&local_30,pcVar3);
    TextObject_Draw(pvVar4,0);
    surface = (void *)Render_GetBackBuffer();
    Surface_Unlock(surface);
    List_Unlink(pvVar4);
  }
  return;
}
#undef local_2c
#undef local_30
#undef local_50
#undef local_54
#undef local_58
#undef local_5c
#undef local_60


/* ---- 0x0048c960  Lua_GetTranslationMode ---- */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Lua opcode: GetTranslationMode */

void Lua_GetTranslationMode(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  lua_pushnumber((float)g_nTranslationMode);
  return;
}
#undef local_4


/* ---- 0x0048c980  Lua_SetTranslationMode ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: SetTranslationMode */

void Lua_SetTranslationMode(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isnumber(iVar1);
    if (iVar2 == 0) {
      return;
    }
    lVar3 = (longlong)lua_getnumber(iVar1);
    g_nTranslationMode = (int)lVar3;
    if (-1 < g_nTranslationMode) {
      if (2 < g_nTranslationMode) {
        g_nTranslationMode = 2;
        return;
      }
      return;
    }
  }
  g_nTranslationMode = 0;
  return;
}

/* ---- 0x00495850  Lua_GetKeyLength ---- */
/* Lua opcode: GetKeyLength */

void Lua_GetKeyLength(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    lua_tag(iVar1);
  }
  piVar3 = (int *)lua_getuserdata(iVar1);
  if (*piVar3 == 0) {
    (*g_pSvcMain->pAssertFail)
              (s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3);
  }
  iVar1 = piVar3[1];
  if (*piVar3 == 0) {
    (*g_pSvcMain->pAssertFail)
              (s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3);
  }
  lua_pushnumber(((float)*(uint *)(iVar1 + 0x34) / *(float *)(piVar3[1] + 0x30)) * 1000.0);
  return;
}

/* ---- 0x00495900  Lua_GetSmushLength ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetSmushLength */

void Lua_GetSmushLength(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x534d5348) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Movie_SetFile(iVar1);
      lua_pushnumber((float)iVar1);
    }
  }
  return;
}
#undef local_4
#undef local_c


/* ---- 0x00497830  Lua_Stub ---- */
/* Lua opcodes: PutActorAtOrigin, GetClippedPos, DriveActorTo, WalkActorToInterest, UnLockFont,
   LockSound, UnlockSound, LockCostume, UnlockCostume, PlaySound, PlaySoundAt, PlaySoundAttached,
   IsSoundPlaying, GetSectorVertices, LoadBundle, UnloadBundle
   Shared handler for opcodes that the shipped engine does not implement */

void Lua_Stub(void)

{
  return;
}

/* ---- 0x00498d80  Lua_GetMemoryUsage ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: GetMemoryUsage */

void Lua_GetMemoryUsage(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = Res_GetMemoryUsed();
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x00498da0  Lua_GetDiskFreeSpace ---- */
/* Lua opcode: GetDiskFreeSpace */

void Lua_GetDiskFreeSpace(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_4 (*(undefined1 (*)[4])(_frame + (0x30 - 0x4)))
  
  GetDiskFreeSpaceA(0,(int)(local_18 + 1),(int)local_18,(int)(local_18 + 2),(int)local_4);
  lua_pushnumber((float)(uint)local_18[0] * 0.0009765625 * (float)(int)local_18[1] * 0.0009765625 *
                 (float)(int)local_18[2]);
  return;
}
#undef local_18
#undef local_4


/* ---- 0x00498e20  Lua_TEST ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: TEST */

void __cdecl Lua_TEST(void)

{
  uint unaff_retaddr;
  uint in_stack_00000004;
  uint in_stack_00000008;
  float in_stack_0000000c;
  float in_stack_00000010;
  float in_stack_00000014;
  float *in_stack_00000018;
  float in_stack_0000001c;
  float in_stack_00000020;
  float in_stack_00000024;
  float in_stack_00000028;
  uint in_stack_0000002c;
  double in_stack_00000034;
  
  SectorList_ShrinkWalkSectors
            (0.005,unaff_retaddr,in_stack_00000004,in_stack_00000008,in_stack_0000000c,
             in_stack_00000010,in_stack_00000014,in_stack_00000018,in_stack_0000001c,
             in_stack_00000020,in_stack_00000024,in_stack_00000028,in_stack_0000002c,
             in_stack_00000034);
  return;
}
#endif


/* ---- 0x00498e50  Lua_ShrinkBoxes ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: ShrinkBoxes */

void __cdecl Lua_ShrinkBoxes(void)

{
  int iVar1;
  int iVar2;
  uint unaff_ESI;
  float fVar3;
  uint unaff_retaddr;
  uint in_stack_00000004;
  float in_stack_00000008;
  float in_stack_0000000c;
  float in_stack_00000010;
  float *in_stack_00000014;
  float in_stack_00000018;
  float in_stack_0000001c;
  float in_stack_00000020;
  float in_stack_00000024;
  uint in_stack_00000028;
  double in_stack_00000030;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 == 0) {
    Lua_UnShrinkBoxes();
    SectorList_SaveForShrink();
    fVar3 = lua_getnumber(iVar1);
    SectorList_ShrinkWalkSectors
              (fVar3,unaff_ESI,unaff_retaddr,in_stack_00000004,in_stack_00000008,in_stack_0000000c,
               in_stack_00000010,in_stack_00000014,in_stack_00000018,in_stack_0000001c,
               in_stack_00000020,in_stack_00000024,in_stack_00000028,in_stack_00000030);
  }
  return;
}
#endif


/* ---- 0x00498e90  Lua_UnShrinkBoxes ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: UnShrinkBoxes */

void Lua_UnShrinkBoxes(void)

{
  SectorList_RestoreAfterShrink();
  SectorList_FreeShrinkSave();
  return;
}
#endif


/* ---- 0x00498ea0  Lua_GetShrinkPos ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_1c */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* WARNING: Variable defined which should be unmapped: local_c */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Lua opcode: GetShrinkPos */

void __cdecl Lua_GetShrinkPos(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  void *this;
  float unaff_EBX;
  uint unaff_EBP;
  uint unaff_ESI;
  uint unaff_EDI;
  float fVar6;
  float fVar7;
  float *n;
  float fVar8;
  uint unaff_retaddr;
  double in_stack_00000008;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float (*)[2])(_frame + (0x30 - 0xc)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
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
        iVar5 = lua_isnumber(iVar4);
        if (iVar5 != 0) {
          fVar6 = lua_getnumber(iVar1);
          fVar7 = lua_getnumber(iVar2);
          n = (float *)lua_getnumber(iVar3);
          fVar8 = lua_getnumber(iVar4);
          local_c[0] = fVar6;
          local_c[1] = fVar7;
          SectorList_SaveForShrink();
          SectorList_ShrinkWalkSectors
                    (fVar8,unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX,fVar6,fVar7,n,fVar8,local_c[0],
                     local_c[1],PUN(float,n),unaff_retaddr,in_stack_00000008);
          this = (void *)SectorList_FindNearestPoint(local_c,0x1000);
          if (this != (void *)0x0) {
            Sector_ClampPoint(this,(int)local_c);
          }
          Lua_UnShrinkBoxes();
          if (this != (void *)0x0) {
            lua_pushnumber(local_c[0]);
            lua_pushnumber(local_c[1]);
            lua_pushnumber(PUN(float,n));
            return;
          }
          lua_pushnil();
        }
      }
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_4
#undef local_c

#endif


/* ---- 0x00499000  Lua_SetSoundParameters ---- */
/* Lua opcode: SetSoundParameters */

void Lua_SetSoundParameters(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  void *set;
  int iVar6;
  uint uVar7;
  uint uVar8;
  longlong lVar9;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(float (*)[3])(_frame + (0x40 - 0x20)))
  #define local_14 (*(float (*)[2])(_frame + (0x40 - 0x14)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x40 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  set = Set_GetCurrent();
  if (set != (void *)0x0) {
    iVar6 = lua_isnil(iVar1);
    if (iVar6 != 0) {
      iVar6 = lua_isnil(iVar2);
      if (iVar6 != 0) {
        iVar6 = lua_isnil(iVar3);
        if (iVar6 != 0) {
          iVar6 = lua_isnil(iVar4);
          if (iVar6 != 0) {
            iVar6 = lua_isnil(iVar5);
            if (iVar6 != 0) {
              Set_SetSoundParams(set,0x41000000,0x14,0x7f,0x3fc00000,0x3f4ccccd);
              return;
            }
          }
        }
      }
    }
    Set_GetSoundParams(set,&local_4,(char *)&local_8,(char *)&local_c,local_14 + 1,local_14);
    iVar6 = lua_isnil(iVar5);
    if (iVar6 == 0) {
      local_20[1] = lua_getnumber(iVar5);
    }
    else {
      local_20[1] = local_14[0];
    }
    iVar5 = lua_isnil(iVar4);
    if (iVar5 == 0) {
      local_20[2] = lua_getnumber(iVar4);
    }
    else {
      local_20[2] = local_14[1];
    }
    iVar4 = lua_isnil(iVar3);
    if (iVar4 == 0) {
      lVar9 = (longlong)lua_getnumber(iVar3);
      uVar7 = (uint)lVar9;
    }
    else {
      uVar7 = local_c & 0xff;
    }
    iVar3 = lua_isnil(iVar2);
    if (iVar3 == 0) {
      lVar9 = (longlong)lua_getnumber(iVar2);
      uVar8 = (uint)lVar9;
    }
    else {
      uVar8 = local_8 & 0xff;
    }
    iVar2 = lua_isnil(iVar1);
    if (iVar2 == 0) {
      local_20[0] = lua_getnumber(iVar1);
    }
    else {
      local_20[0] = local_4;
    }
    Set_SetSoundParams(set,local_20[0],uVar8,uVar7,local_20[2],local_20[1]);
  }
  return;
}
#undef local_14
#undef local_20
#undef local_24
#undef local_28
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004991c0  Lua_GetSoundParameters ---- */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: GetSoundParameters */

void Lua_GetSoundParameters(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *set;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  set = Set_GetCurrent();
  if (set != (void *)0x0) {
    Set_GetSoundParams(set,&local_18,(char *)&local_14,(char *)&local_c,&local_8,&local_4);
    lua_pushnumber(local_18);
    local_10 = local_14 & 0xff;
    lua_pushnumber((float)local_10);
    local_10 = local_c & 0xff;
    lua_pushnumber((float)local_10);
    lua_pushnumber(local_8);
    lua_pushnumber(local_4);
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_20
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00499250  Lua_SetDebugKeysCallback ---- */
void Lua_SetDebugKeysCallback(uint param_1)

{
  UINT_008cab8c = param_1;
  return;
}

/* ---- 0x00499260  Lua_EnginePause ---- */
/* Lua opcode: EnginePause */

void Lua_EnginePause(void)

{
  Engine_SetPaused(1);
  return;
}

/* ---- 0x00499270  Lua_EngineResume ---- */
/* Lua opcode: EngineResume */

void Lua_EngineResume(void)

{
  Engine_SetPaused(0);
  return;
}

/* ---- 0x00499280  Lua_EngineDisplay ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: EngineDisplay */

void Lua_EngineDisplay(void)

{
  int iVar1;
  longlong lVar2;
  double in_stack_00000000;
  
  iVar1 = lua_lua2C(1);
  lua_getnumber(iVar1);
  lVar2 = _ftol(in_stack_00000000);
  Render_SetDrawEnabled((int)lVar2);
  return;
}
#endif


/* ---- 0x004992b0  Lua_LoadActor ---- */
/* Lua opcode: LoadActor */

void Lua_LoadActor(void)

{
  char *pcVar1;
  
  pcVar1 = (char *)Actor_Create();
  if (-1 < (int)pcVar1) {
    lua_pushusertag(pcVar1,0x52544341);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x004992c9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lua_pushnil();
  return;
}

/* ---- 0x004992d0  Lua_PutActorAtInterest ---- */
/* Lua opcode: PutActorAtInterest */

void Lua_PutActorAtInterest(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  void *pvVar4;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      uVar3 = Actor_FromHandle(iVar1);
      pvVar4 = Set_GetCurrent();
      if (pvVar4 != (void *)0x0) {
        iVar1 = *(int *)((int)pvVar4 + 0xac) + 0x2c + *(int *)((int)pvVar4 + 0xb4) * 300;
        local_c = *(uint *)(*(int *)((int)pvVar4 + 0xac) + 0x2c + *(int *)((int)pvVar4 + 0xb4) * 300
                           );
        local_8 = *(uint *)(iVar1 + 4);
        local_4 = *(uint *)(iVar1 + 8);
        Actor_SetPositionClamped(uVar3,&local_c);
      }
    }
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00499360  Lua_SetSelectedActor ---- */
/* Lua opcode: SetSelectedActor */

void Lua_SetSelectedActor(void)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pcVar3 = (char *)Actor_SetSelected(iVar1);
      if (-1 < (int)pcVar3) {
        lua_pushusertag(pcVar3,0x52544341);
        return;
      }
      lua_pushnil();
    }
  }
  return;
}

/* ---- 0x004993c0  Lua_PutActorAt ---- */
/* Lua opcode: PutActorAt */

void Lua_PutActorAt(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_isuserdata(iVar1);
  if (iVar5 != 0) {
    iVar5 = lua_tag(iVar1);
    if (iVar5 == 0x52544341) {
      iVar5 = lua_isnumber(iVar2);
      if (iVar5 != 0) {
        iVar5 = lua_isnumber(iVar3);
        if (iVar5 != 0) {
          iVar5 = lua_isnumber(iVar4);
          if (iVar5 != 0) {
            iVar1 = lua_getuserdata(iVar1);
            uVar6 = Actor_FromHandle(iVar1);
            local_c[0] = lua_getnumber(iVar2);
            local_c[1] = lua_getnumber(iVar3);
            local_c[2] = lua_getnumber(iVar4);
            Actor_SetPositionClamped(uVar6,local_c);
          }
        }
      }
    }
  }
  return;
}
#undef local_10
#undef local_c


/* ---- 0x004994a0  Lua_PutActorInSet ---- */
/* Lua opcode: PutActorInSet */

void Lua_PutActorInSet(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  void *pvVar5;
  char *pcVar6;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(iVar1), iVar3 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    pcVar4 = (char *)Actor_FromHandle(iVar1);
    iVar1 = lua_isstring(iVar2);
    if ((iVar1 == 0) && (iVar1 = lua_isnil(iVar2), iVar1 == 0)) {
      return;
    }
    pcVar6 = pcVar4;
    pvVar5 = (void *)lua_getstring(iVar2);
    Actor_PutInSet(pvVar5,pcVar6);
    if ((((*(int *)(pcVar4 + 0xa4) != 0) && (iVar1 = lua_isstring(iVar2), iVar1 != 0)) &&
        (*(int *)(*(int *)(pcVar4 + 0xa4) + 0x1b4) != 0)) &&
       (*(int *)(*(int *)(pcVar4 + 0xa4) + 0x1b8) != 0)) {
      pcVar6 = (char *)lua_getstring(iVar2);
      pvVar5 = Res_Find(0x20544553,pcVar6);
      if (pvVar5 != (void *)0x0) {
        Walker_ReattachToSet(*(void **)(*(int *)(pcVar4 + 0xa4) + 0x1b4));
      }
    }
  }
  return;
}

/* ---- 0x00499590  Lua_WalkActorVector ---- */
/* WARNING: Variable defined which should be unmapped: local_78 */
/* Lua opcode: WalkActorVector(actor, cameraActor, x, y, z [, yawOffset]). Transforms the vector by
   the camera actor's frame, adds the actor position, turns the walker heading toward it by at most
   2 * |rate| * frameSeconds (Walker_TurnToPoint) and, if the point is less than 90 degrees from the
   heading, clears actor+8 bit 0 and calls Actor_WalkForward. Dereferences the walker without
   creating it. */

void Lua_WalkActorVector(void)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  void *actor;
  float *pfVar9;
  float *pfVar10;
  float fVar11;
  float fVar12;
  #define local_78 (*(uint *)(_frame + (0x90 - 0x78)))
  #define local_64 (*(uint *)(_frame + (0x90 - 0x64)))
  #define local_60 (*(uint *)(_frame + (0x90 - 0x60)))
  #define local_5c (*(uint *)(_frame + (0x90 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x90 - 0x58)))
  #define local_54 (*(float (*)[3])(_frame + (0x90 - 0x54)))
  #define local_48 (*(float (*)[3])(_frame + (0x90 - 0x48)))
  #define local_3c (*(uint *)(_frame + (0x90 - 0x3c)))
  #define local_38 (*(float (*)[2])(_frame + (0x90 - 0x38)))
  #define local_30 (*(float (*)[9])(_frame + (0x90 - 0x30)))
  #define local_c (*(uint *)(_frame + (0x90 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x90 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x90 - 0x4)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_lua2C(3);
  iVar5 = lua_lua2C(4);
  iVar6 = lua_lua2C(5);
  iVar7 = lua_lua2C(6);
  iVar8 = lua_isuserdata(iVar2);
  if (iVar8 != 0) {
    iVar8 = lua_tag(iVar2);
    if (iVar8 == 0x52544341) {
      iVar8 = lua_isuserdata(iVar3);
      if (iVar8 != 0) {
        iVar8 = lua_tag(iVar3);
        if (iVar8 == 0x52544341) {
          iVar2 = lua_getuserdata(iVar2);
          iVar2 = Actor_FromHandle(iVar2);
          iVar3 = lua_getuserdata(iVar3);
          actor = (void *)Actor_FromHandle(iVar3);
          local_54[0] = lua_getnumber(iVar4);
          local_54[1] = lua_getnumber(iVar5);
          local_54[2] = lua_getnumber(iVar6);
          pfVar9 = Actor_GetFrame(actor);
          pfVar10 = local_30;
          for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
            *pfVar10 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            pfVar10 = pfVar10 + 1;
          }
          iVar3 = lua_isnumber(iVar7);
          if (iVar3 != 0) {
            local_38[0] = lua_getnumber(iVar7);
            local_c = 0;
            local_8 = 0;
            local_3c = 0;
            local_38[1] = 0.0;
            local_4 = 0;
            Matrix_BuildTransform(local_30,&local_3c);
          }
          Vec3_Transform(local_54,local_30);
          iVar3 = 3;
          pfVar9 = (float *)(iVar2 + 0xc);
          pfVar10 = local_54;
          do {
            fVar1 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            iVar3 = iVar3 + -1;
            *pfVar10 = fVar1 + *pfVar10;
            pfVar10 = pfVar10 + 1;
          } while (iVar3 != 0);
          local_48[0] = local_54[0];
          local_48[1] = local_54[1];
          local_48[2] = local_54[2];
          Walker_ToLocalSpace(*(void **)(*(int *)(iVar2 + 0xa4) + 0x1b4),local_48);
          Vec3_Normalize(local_48);
          fVar11 = Math_AsinDegreesSeries(local_48[1]);
          fVar1 = *(float *)(*(int *)(iVar2 + 0xa4) + 0x1c);
          if (*(float *)(*(int *)(iVar2 + 0xa4) + 0x1c) < 0.0) {
            fVar1 = -fVar1;
          }
          fVar12 = Timer_GetFrameSeconds();
          Walker_TurnToPoint(*(void **)(*(int *)(iVar2 + 0xa4) + 0x1b4),local_54,
                             fVar12 * fVar1 + fVar12 * fVar1);
          if (90.0 - fVar11 < 90.0) {
            *(uint *)(iVar2 + 8) = *(uint *)(iVar2 + 8) & 0xfffffffe;
            Actor_WalkForward(iVar2);
          }
        }
      }
    }
  }
  return;
}
#undef local_30
#undef local_38
#undef local_3c
#undef local_4
#undef local_48
#undef local_54
#undef local_58
#undef local_5c
#undef local_60
#undef local_64
#undef local_78
#undef local_8
#undef local_c


/* ---- 0x00499800  Lua_WalkActorForward ---- */
/* Lua opcode: WalkActorForward */

void Lua_WalkActorForward(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) & 0xfffffffe;
      Actor_WalkForward(iVar1);
    }
  }
  return;
}

/* ---- 0x00499860  Lua_WalkActorTo ---- */
/* Lua opcode: WalkActorTo */

void Lua_WalkActorTo(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  lua_lua2C(6);
  lua_lua2C(7);
  iVar6 = lua_isuserdata(iVar1);
  if ((iVar6 != 0) && (iVar6 = lua_tag(iVar1), iVar6 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    uVar7 = Actor_FromHandle(iVar1);
    iVar1 = lua_isnumber(iVar2);
    if (iVar1 == 0) {
      iVar1 = lua_isuserdata(iVar2);
      if (iVar1 == 0) {
        return;
      }
      iVar1 = lua_tag(iVar2);
      if (iVar1 != 0x52544341) {
        return;
      }
      iVar1 = lua_getuserdata(iVar2);
      iVar1 = Actor_FromHandle(iVar1);
      local_18[0] = *(float *)(iVar1 + 0xc);
      local_18[1] = *(float *)(iVar1 + 0x10);
      local_18[2] = *(float *)(iVar1 + 0x14);
    }
    else {
      local_18[0] = lua_getnumber(iVar2);
      local_18[1] = lua_getnumber(iVar3);
      local_18[2] = lua_getnumber(iVar4);
    }
    local_c[0] = lua_getnumber(iVar5);
    local_c[1] = lua_getnumber(iVar5);
    local_c[2] = lua_getnumber(iVar5);
    Walker_ReplanPath(uVar7,local_18,local_c,0);
  }
  return;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_c


/* ---- 0x004999d0  Lua_WalkActorToAvoiding ---- */
/* Lua opcode: WalkActorToAvoiding */

void Lua_WalkActorToAvoiding(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  iVar6 = lua_lua2C(6);
  lua_lua2C(7);
  lua_lua2C(8);
  iVar7 = lua_isuserdata(iVar1);
  if ((((iVar7 != 0) && (iVar7 = lua_tag(iVar1), iVar7 == 0x52544341)) &&
      (iVar7 = lua_isuserdata(iVar2), iVar7 != 0)) && (iVar7 = lua_tag(iVar2), iVar7 == 0x52544341))
  {
    iVar1 = lua_getuserdata(iVar1);
    uVar8 = Actor_FromHandle(iVar1);
    iVar1 = lua_getuserdata(iVar2);
    uVar9 = Actor_FromHandle(iVar1);
    iVar1 = lua_isnumber(iVar3);
    if (iVar1 == 0) {
      iVar1 = lua_isuserdata(iVar3);
      if (iVar1 == 0) {
        return;
      }
      iVar1 = lua_tag(iVar3);
      if (iVar1 != 0x52544341) {
        return;
      }
      iVar1 = lua_getuserdata(iVar3);
      iVar1 = Actor_FromHandle(iVar1);
      local_18[0] = *(float *)(iVar1 + 0xc);
      local_18[1] = *(float *)(iVar1 + 0x10);
      local_18[2] = *(float *)(iVar1 + 0x14);
    }
    else {
      local_18[0] = lua_getnumber(iVar3);
      local_18[1] = lua_getnumber(iVar4);
      local_18[2] = lua_getnumber(iVar5);
    }
    local_c[0] = lua_getnumber(iVar6);
    local_c[1] = lua_getnumber(iVar6);
    local_c[2] = lua_getnumber(iVar6);
    Walker_ReplanPath(uVar8,local_18,local_c,uVar9);
  }
  return;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_c


/* ---- 0x00499b80  Lua_IsActorMoving ---- */
/* Lua opcode: IsActorMoving */

void Lua_IsActorMoving(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if ((*(byte *)(iVar1 + 8) & 1) != 0) {
        lua_pushnumber(1.0);
        return;
      }
      lua_pushnil();
    }
  }
  return;
}

/* ---- 0x00499be0  Lua_IsActorTurning ---- */
/* Lua opcode: IsActorTurning(actor). TRUE while extra+0x28 (angle left between visible yaw and
   walker heading) is not 0. That field is written only by Walker_UpdateYaw (0 once under 0.5
   degrees) and Actor_SetRot, so an actor without a walker is never turning. */

void Lua_IsActorTurning(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      if (*(float *)(*(int *)(iVar1 + 0xa4) + 0x28) != 0.0) {
        lua_pushnumber(1.0);
      }
      lua_pushnil();
    }
  }
  return;
}

/* ---- 0x00499c70  Lua_SetActorChoreLooping ---- */
/* Lua opcode: SetActorChoreLooping */

void Lua_SetActorChoreLooping(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  void *luaObj;
  int iVar4;
  uint uVar5;
  uint uVar6;
  longlong lVar7;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  luaObj = (void *)lua_lua2C(4);
  iVar4 = lua_isuserdata(iVar1);
  if (iVar4 != 0) {
    iVar4 = lua_tag(iVar1);
    if (iVar4 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_4);
      if ((iVar1 != 0) && (local_4 != 0)) {
        iVar1 = lua_isnumber(iVar2);
        if (iVar1 != 0) {
          iVar1 = lua_isnil(iVar3);
          uVar5 = (uint)(iVar1 == 0);
          lVar7 = (longlong)lua_getnumber(iVar2);
          Cos_InstSetChoreLoop(*(int *)local_4,(uint)lVar7,uVar5);
          return;
        }
        iVar1 = lua_isnil(iVar2);
        if (iVar1 != 0) {
          uVar5 = Cos_InstCountChores(*(int *)local_4);
          lua_isnil(iVar3);
          uVar6 = 0;
          if (uVar5 != 0) {
            do {
              iVar1 = lua_isnil(iVar3);
              Cos_InstSetChoreLoop(*(int *)local_4,uVar6,(uint)(iVar1 == 0));
              uVar6 = uVar6 + 1;
            } while (uVar6 < uVar5);
          }
        }
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x00499da0  Lua_IsActorResting ---- */
/* Lua opcode: IsActorResting */

void Lua_IsActorResting(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      if (*(int *)(*(int *)(iVar1 + 0xa4) + 0x14) != 0) {
        lua_pushnumber(1.0);
        return;
      }
      lua_pushnil();
    }
  }
  return;
}

/* ---- 0x00499e20  Lua_IsActorChoring ---- */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: IsActorChoring */

void Lua_IsActorChoring(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  void *luaObj;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  longlong lVar8;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  luaObj = (void *)lua_lua2C(4);
  local_4 = 0xffffffff;
  iVar4 = lua_isuserdata(iVar1);
  if ((iVar4 != 0) && (iVar4 = lua_tag(iVar1), iVar4 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    iVar1 = Actor_FromHandle(iVar1);
    iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_c);
    if (iVar1 != 0) {
      iVar1 = lua_isnil(iVar3);
      if (local_c != 0) {
        iVar3 = lua_isnumber(iVar2);
        if (iVar3 == 0) {
          iVar2 = lua_isnil(iVar2);
          if (iVar2 != 0) {
            uVar6 = Cos_InstCountChores(*(int *)local_c);
            uVar7 = 0;
            local_8 = 0;
            uVar5 = local_8;
            if (uVar6 != 0) {
              do {
                uVar5 = Cos_InstChoreStatus(*(int *)local_c,uVar7);
                if (((uVar5 & 1) != 0) &&
                   (((iVar1 != 0 || ((uVar5 & 2) == 0)) && (local_4 = uVar7, (uVar5 & 2) != 0)))) {
                  local_8 = uVar7;
                  lua_pushnumber((float)(int)uVar7);
                  lua_pushnumber(1.0);
                  return;
                }
                uVar7 = uVar7 + 1;
                uVar5 = uVar7;
              } while (uVar7 < uVar6);
            }
            local_8 = uVar5;
            if (-1 < (int)local_4) {
              lua_pushnumber((float)(int)local_4);
              return;
            }
          }
        }
        else {
          lVar8 = (longlong)lua_getnumber(iVar2);
          uVar5 = Cos_InstChoreStatus(*(int *)local_c,(uint)lVar8);
          if ((uVar5 & 1) != 0) {
            if ((iVar1 == 0) && ((uVar5 & 2) != 0)) {
              return;
            }
            lua_pushobject(iVar2);
            if ((uVar5 & 2) != 0) {
              lua_pushnumber(1.0);
              return;
            }
          }
        }
      }
      lua_pushnil();
    }
  }
  return;
}
#undef local_20
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00499ff0  Lua_GetActorChores ---- */
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: GetActorChores */

void Lua_GetActorChores(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *luaObj;
  int iVar2;
  float fVar3;
  uint uVar4;
  float fVar5;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(float (*)[3])(_frame + (0x40 - 0x14)))
  
  iVar1 = lua_lua2C(1);
  luaObj = (void *)lua_lua2C(2);
  iVar2 = lua_isuserdata(iVar1);
  if ((iVar2 != 0) && (iVar2 = lua_tag(iVar1), iVar2 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    iVar1 = Actor_FromHandle(iVar1);
    iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_18);
    if (iVar1 == 0) {
      return;
    }
    fVar5 = 0.0;
    if (local_18 != 0) {
      iVar1 = lua_createtable();
      fVar3 = (float)Cos_InstCountChores(*(int *)local_18);
      local_14[0] = 0.0;
      local_14[2] = fVar3;
      if (fVar3 != 0.0) {
        do {
          uVar4 = Cos_InstChoreStatus(*(int *)local_18,(uint)fVar5);
          if ((uVar4 & 1) != 0) {
            lua_pushobject(iVar1);
            fVar3 = (float)(uint)fVar5;
            local_14[1] = fVar3;
            lua_pushnumber(fVar3);
            lua_pushnumber(fVar3);
            lua_settable();
            local_14[0] = (float)((int)local_14[0] + 1);
            fVar3 = local_14[2];
          }
          fVar5 = (float)((int)fVar5 + 1);
        } while ((uint)fVar5 < (uint)fVar3);
      }
      lua_pushobject(iVar1);
      lua_pushstring(s_count_004ec384);
      lua_pushnumber((float)(uint)local_14[0]);
      lua_settable();
      lua_pushobject(iVar1);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_14
#undef local_18
#undef local_2c


/* ---- 0x0049a160  Lua_GetActorCostumeDepth ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: GetActorCostumeDepth */

void Lua_GetActorCostumeDepth(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar3 = 0;
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if ((iVar2 != 0) && (iVar2 = lua_tag(iVar1), iVar2 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    iVar1 = Actor_FromHandle(iVar1);
    for (iVar1 = *(int *)(iVar1 + 0xa0); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xb0)) {
      iVar3 = iVar3 + 1;
    }
    lua_pushnumber((float)iVar3);
    return;
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_4


/* ---- 0x0049a1e0  Lua_GetActorCostume ---- */
/* Lua opcode: GetActorCostume */

void Lua_GetActorCostume(void)

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
    iVar1 = Actor_FromHandle(iVar1);
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

/* ---- 0x0049a2a0  Lua_GetActorLoopingChores ---- */
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: GetActorLoopingChores */

void Lua_GetActorLoopingChores(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *luaObj;
  int iVar2;
  float fVar3;
  uint uVar4;
  float fVar5;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(float (*)[3])(_frame + (0x40 - 0x14)))
  
  iVar1 = lua_lua2C(1);
  luaObj = (void *)lua_lua2C(2);
  iVar2 = lua_isuserdata(iVar1);
  if ((iVar2 != 0) && (iVar2 = lua_tag(iVar1), iVar2 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    iVar1 = Actor_FromHandle(iVar1);
    iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_18);
    if (iVar1 == 0) {
      return;
    }
    fVar5 = 0.0;
    if (local_18 != 0) {
      iVar1 = lua_createtable();
      fVar3 = (float)Cos_InstCountChores(*(int *)local_18);
      local_14[0] = 0.0;
      local_14[2] = fVar3;
      if (fVar3 != 0.0) {
        do {
          uVar4 = Cos_InstChoreStatus(*(int *)local_18,(uint)fVar5);
          if (((uVar4 & 1) != 0) && ((uVar4 & 2) != 0)) {
            lua_pushobject(iVar1);
            fVar3 = (float)(uint)fVar5;
            local_14[1] = fVar3;
            lua_pushnumber(fVar3);
            lua_pushnumber(fVar3);
            lua_settable();
            local_14[0] = (float)((int)local_14[0] + 1);
            fVar3 = local_14[2];
          }
          fVar5 = (float)((int)fVar5 + 1);
        } while ((uint)fVar5 < (uint)fVar3);
      }
      lua_pushobject(iVar1);
      lua_pushstring(s_count_004ec384);
      lua_pushnumber((float)(uint)local_14[0]);
      lua_settable();
      lua_pushobject(iVar1);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_14
#undef local_18
#undef local_2c


/* ---- 0x0049a410  Lua_SetActorColormap ---- */
/* Source: Scripts/sputLua.cpp (line 2035, from __FILE__/__LINE__ passed to the allocator) */

void Lua_SetActorColormap(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  char *name;
  void *data;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(iVar2);
  if ((iVar4 != 0) && (iVar4 = lua_tag(iVar2), iVar4 == 0x52544341)) {
    iVar2 = lua_getuserdata(iVar2);
    piVar5 = (int *)Actor_FromHandle(iVar2);
    iVar2 = lua_isstring(iVar3);
    if (iVar2 != 0) {
      name = (char *)lua_getstring(iVar3);
      data = Resource_Load(0x50414d43,name);
      piVar1 = (int *)*piVar5;
      iVar2 = *piVar1;
      if (iVar2 != 0) {
        if (iVar2 == 0) {
          (*g_pSvcMain->pAssertFail)
                    (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
        }
        if ((void *)piVar1[1] == data) {
          return;
        }
      }
      ResRef_Remove((void *)*piVar5);
      ResRef_Add((void *)*piVar5,data,s_C__grimsrc_libs_grimlib_Scripts__004ec38c,0x7f3);
      return;
    }
    iVar2 = lua_isnil(iVar3);
    if (iVar2 != 0) {
      ResRef_Remove((void *)*piVar5);
    }
  }
  return;
}

/* ---- 0x0049a500  Lua_SetActorCostume ---- */
/* Lua opcode: SetActorCostume */

void Lua_SetActorCostume(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  void *actor;
  char *name;
  int iVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar4 = 0;
  iVar3 = lua_isuserdata(iVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(iVar1), iVar3 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    actor = (void *)Actor_FromHandle(iVar1);
    iVar1 = lua_isstring(iVar2);
    if (iVar1 == 0) {
      iVar1 = lua_isnil(iVar2);
      if (iVar1 != 0) {
        iVar1 = *(int *)((int)actor + 0xa0);
        while (iVar1 != 0) {
          Actor_PopCostume(actor,1);
          iVar1 = *(int *)((int)actor + 0xa0);
        }
        iVar4 = 1;
      }
    }
    else {
      iVar1 = 0;
      name = (char *)lua_getstring(iVar2);
      iVar4 = Actor_SetCostume(actor,name,iVar1);
    }
    if (iVar4 != 0) {
      lua_pushnumber(1.0);
      return;
    }
    lua_pushnil();
  }
  return;
}

/* ---- 0x0049a5e0  Lua_PrintActorCostumes ---- */
/* Lua opcode: PrintActorCostumes */

void Lua_PrintActorCostumes(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  lua_lua2C(2);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      Costume_PrintList(*(void **)(iVar1 + 0xa0));
    }
  }
  return;
}

/* ---- 0x0049a640  Lua_PushActorCostume ---- */
/* Lua opcode: PushActorCostume */

void Lua_PushActorCostume(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  void *actor;
  char *name;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(iVar1);
      iVar1 = lua_isstring(iVar2);
      if (iVar1 != 0) {
        iVar1 = 0;
        name = (char *)lua_getstring(iVar2);
        Actor_PushCostume(actor,name,iVar1);
      }
    }
  }
  return;
}

/* ---- 0x0049a6c0  Lua_PopActorCostume ---- */
/* Lua opcode: PopActorCostume */

void Lua_PopActorCostume(void)

{
  int iVar1;
  int iVar2;
  void *actor;
  char *pcVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(iVar1);
      if (*(int **)((int)actor + 0xa0) != (int *)0x0) {
        pcVar3 = (char *)Cos_InstGetCostume(**(int **)((int)actor + 0xa0),(int *)0x0);
        lua_pushstring(pcVar3);
        Actor_PopCostume(actor,1);
        return;
      }
      lua_pushnil();
      Actor_PopCostume(actor,1);
    }
  }
  return;
}

/* ---- 0x0049a750  Lua_StopActorChore ---- */
/* Lua opcode: StopActorChore */

void Lua_StopActorChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  longlong lVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_4);
      if ((iVar1 != 0) && (local_4 != 0)) {
        iVar1 = lua_isnumber(iVar2);
        if (iVar1 != 0) {
          lVar4 = (longlong)lua_getnumber(iVar2);
          Cos_InstStopChore(*(int *)local_4,(uint)lVar4);
          return;
        }
        iVar1 = lua_isnil(iVar2);
        if (iVar1 != 0) {
          Cos_InstStopChores(*(uint *)local_4);
        }
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049a830  Lua_PlayActorChore ---- */
/* Lua opcode: PlayActorChore */

void Lua_PlayActorChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  longlong lVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_4);
      if (iVar1 != 0) {
        if (local_4 != 0) {
          iVar1 = lua_isnumber(iVar2);
          if (iVar1 != 0) {
            iVar3 = 0;
            iVar1 = 0;
            lVar4 = (longlong)lua_getnumber(iVar2);
            iVar1 = Cos_InstPlayChore(*(int *)local_4,(uint)lVar4,iVar1,iVar3);
            if (iVar1 != 0) {
              lua_pushnumber(1.0);
              return;
            }
          }
        }
        lua_pushnil();
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049a910  Lua_CompleteActorChore ---- */
/* Lua opcode: CompleteActorChore */

void Lua_CompleteActorChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  longlong lVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_4);
      if (iVar1 != 0) {
        if (local_4 != 0) {
          iVar1 = lua_isnumber(iVar2);
          if (iVar1 != 0) {
            lVar4 = (longlong)lua_getnumber(iVar2);
            iVar1 = Cos_InstCompleteChore(*(int *)local_4,(uint)lVar4);
            if (iVar1 != 0) {
              lua_pushnumber(1.0);
              return;
            }
          }
        }
        lua_pushnil();
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049a9e0  Lua_PlayActorChoreLooping ---- */
/* Lua opcode: PlayActorChoreLooping */

void Lua_PlayActorChoreLooping(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  longlong lVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_4);
      if (iVar1 != 0) {
        if (local_4 != 0) {
          iVar1 = lua_isnumber(iVar2);
          if (iVar1 != 0) {
            iVar3 = 0;
            iVar1 = 1;
            lVar4 = (longlong)lua_getnumber(iVar2);
            iVar1 = Cos_InstPlayChore(*(int *)local_4,(uint)lVar4,iVar1,iVar3);
            if (iVar1 != 0) {
              lua_pushnumber(1.0);
              return;
            }
          }
        }
        lua_pushnil();
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049aac0  Lua_ActorLookAt ---- */
/* Lua opcode: ActorLookAt */

void Lua_ActorLookAt(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *pfVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar3 = lua_lua2C(1);
  iVar4 = lua_lua2C(2);
  iVar5 = lua_lua2C(3);
  lua_lua2C(4);
  iVar6 = lua_lua2C(5);
  iVar7 = lua_isuserdata(iVar3);
  if ((iVar7 != 0) && (iVar7 = lua_tag(iVar3), iVar7 == 0x52544341)) {
    iVar3 = lua_getuserdata(iVar3);
    iVar3 = Actor_FromHandle(iVar3);
    if (*(int *)(iVar3 + 0xa4) == 0) {
      Actor_CreateExtra(iVar3);
    }
    if (*(int *)(iVar3 + 0xa0) != 0) {
      iVar7 = lua_isnumber(iVar6);
      if (iVar7 != 0) {
        fVar8 = lua_getnumber(iVar6);
        *(float *)(*(int *)(iVar3 + 0xa0) + 0x18) = fVar8;
      }
      iVar6 = lua_isnil(iVar4);
      if (iVar6 == 0) {
        iVar6 = lua_isnumber(iVar4);
        if (iVar6 != 0) {
          iVar5 = lua_lua2C(3);
          iVar6 = lua_lua2C(4);
          fVar8 = lua_getnumber(iVar4);
          **(float **)(iVar3 + 0xa4) = fVar8;
          iVar4 = lua_isnumber(iVar5);
          if (iVar4 == 0) {
            fVar8 = 0.0;
          }
          else {
            fVar8 = lua_getnumber(iVar5);
          }
          *(float *)(*(int *)(iVar3 + 0xa4) + 4) = fVar8;
          iVar4 = lua_isnumber(iVar6);
          if (iVar4 != 0) {
            fVar8 = lua_getnumber(iVar6);
            *(float *)(*(int *)(iVar3 + 0xa4) + 8) = fVar8;
            *(uint *)(iVar3 + 8) = *(uint *)(iVar3 + 8) | 2;
            return;
          }
          *(undefined4 *)(*(int *)(iVar3 + 0xa4) + 8) = 0;
          *(uint *)(iVar3 + 8) = *(uint *)(iVar3 + 8) | 2;
          return;
        }
        iVar6 = lua_isuserdata(iVar4);
        if (iVar6 == 0) {
          return;
        }
        iVar6 = lua_tag(iVar4);
        if (iVar6 != 0x52544341) {
          return;
        }
        iVar4 = lua_getuserdata(iVar4);
        iVar4 = Actor_FromHandle(iVar4);
        puVar2 = *(undefined4 **)(iVar3 + 0xa4);
        *puVar2 = *(undefined4 *)(iVar4 + 0xc);
        puVar2[1] = *(undefined4 *)(iVar4 + 0x10);
        puVar2[2] = *(undefined4 *)(iVar4 + 0x14);
        iVar4 = lua_isnumber(iVar5);
        if (iVar4 != 0) {
          fVar8 = lua_getnumber(iVar5);
          *(float *)(*(int *)(iVar3 + 0xa0) + 0x18) = fVar8;
        }
      }
      else {
        pfVar1 = *(float **)(iVar3 + 0xa4);
        if (((*pfVar1 == 0.0) && (pfVar1[1] == 0.0)) && (pfVar1[2] == 0.0)) {
          return;
        }
        *pfVar1 = 0.0;
        pfVar1[1] = 0.0;
        pfVar1[2] = 0.0;
        iVar4 = lua_isnumber(iVar5);
        if (iVar4 != 0) {
          fVar8 = lua_getnumber(iVar5);
          *(float *)(*(int *)(iVar3 + 0xa0) + 0x18) = fVar8;
          *(uint *)(iVar3 + 8) = *(uint *)(iVar3 + 8) | 2;
          return;
        }
      }
      *(uint *)(iVar3 + 8) = *(uint *)(iVar3 + 8) | 2;
    }
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x0049ad30  Lua_IsActorLooking ---- */
/* Lua opcode: IsActorLooking */

void Lua_IsActorLooking(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if ((*(byte *)(iVar1 + 8) & 2) != 0) {
        lua_pushnumber(1.0);
        return;
      }
      lua_pushnil();
    }
  }
  return;
}

/* ---- 0x0049ad90  Lua_SetActorLookRate ---- */
/* Lua opcode: SetActorLookRate */

void Lua_SetActorLookRate(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(iVar2);
      if (iVar3 != 0) {
        iVar1 = lua_getuserdata(iVar1);
        iVar1 = Actor_FromHandle(iVar1);
        if (*(int *)(iVar1 + 0xa0) != 0) {
          fVar4 = lua_getnumber(iVar2);
          *(float *)(*(int *)(iVar1 + 0xa0) + 0x18) = fVar4;
        }
      }
    }
  }
  return;
}

/* ---- 0x0049ae10  Lua_GetActorLookRate ---- */
/* Lua opcode: GetActorLookRate */

void Lua_GetActorLookRate(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa0) != 0) {
        lua_pushnumber(*(float *)(*(int *)(iVar1 + 0xa0) + 0x18));
        return;
      }
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0049ae80  Lua_SetActorVisibility ---- */
/* Lua opcode: SetActorVisibility */

void Lua_SetActorVisibility(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (iVar2 != 0) {
        iVar2 = lua_isnil(iVar2);
        if (iVar2 == 0) {
          *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xfffffffd;
          return;
        }
      }
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 2;
    }
  }
  return;
}

/* ---- 0x0049af00  Lua_SetActorFollowBoxes ---- */
/* Lua opcode: SetActorFollowBoxes */

void Lua_SetActorFollowBoxes(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  uVar5 = 1;
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 == 0) {
    return;
  }
  iVar3 = lua_tag(iVar1);
  if (iVar3 == 0x52544341) {
    iVar1 = lua_getuserdata(iVar1);
    uVar4 = Actor_FromHandle(iVar1);
    if ((iVar2 == 0) || (iVar1 = lua_isnil(iVar2), iVar1 != 0)) {
      uVar5 = 0;
    }
    Actor_SetFollowBoxes(uVar4,uVar5);
    return;
  }
  return;
}

/* ---- 0x0049af80  Lua_ShutUpActor ---- */
/* Lua opcode: ShutUpActor */

void Lua_ShutUpActor(void)

{
  int iVar1;
  int iVar2;
  void *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(iVar1);
      if (actor != (void *)0x0) {
        Actor_ShutUp(actor);
      }
    }
  }
  return;
}

/* ---- 0x0049afd0  Lua_SetActorFrustrumCull ---- */
/* Lua opcode: SetActorFrustrumCull */

void Lua_SetActorFrustrumCull(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      uVar4 = Actor_FromHandle(iVar1);
      lVar5 = (longlong)lua_getnumber(iVar2);
      Actor_SetFrustumCull(uVar4,(int)lVar5);
    }
  }
  return;
}

/* ---- 0x0049b040  Lua_GetCameraActor ---- */
/* Lua opcode: GetCameraActor */

void Lua_GetCameraActor(void)

{
  lua_pushusertag((char *)g_nCameraActor,0x52544341);
  return;
}

/* ---- 0x0049b060  Lua_GetActorWalkRate ---- */
/* Lua opcode: GetActorWalkRate */

void Lua_GetActorWalkRate(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      lua_pushnumber(*(float *)(*(int *)(iVar1 + 0xa4) + 0x18));
    }
  }
  return;
}

/* ---- 0x0049b0d0  Lua_SetActorWalkRate ---- */
/* Lua opcode: SetActorWalkRate */

void Lua_SetActorWalkRate(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(iVar2);
      if (iVar3 != 0) {
        iVar1 = lua_getuserdata(iVar1);
        iVar1 = Actor_FromHandle(iVar1);
        if (*(int *)(iVar1 + 0xa4) == 0) {
          Actor_CreateExtra(iVar1);
        }
        fVar4 = lua_getnumber(iVar2);
        *(float *)(*(int *)(iVar1 + 0xa4) + 0x18) = fVar4;
      }
    }
  }
  return;
}

/* ---- 0x0049b160  Lua_GetActorTurnRate ---- */
/* Lua opcode: GetActorTurnRate */

void Lua_GetActorTurnRate(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      lua_pushnumber(*(float *)(*(int *)(iVar1 + 0xa4) + 0x1c));
    }
  }
  return;
}

/* ---- 0x0049b1d0  Lua_SetActorTurnRate ---- */
/* Lua opcode: SetActorTurnRate(actor, rate). Stores the rate at extra+0x1c, keeping the sign of the
   current rate (a negative rate is the pending snap flag). The value itself is not made absolute
   here; readers take |rate|. */

void Lua_SetActorTurnRate(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(iVar2);
      if (iVar3 != 0) {
        fVar4 = lua_getnumber(iVar2);
        iVar1 = lua_getuserdata(iVar1);
        iVar1 = Actor_FromHandle(iVar1);
        if (*(int *)(iVar1 + 0xa4) == 0) {
          Actor_CreateExtra(iVar1);
        }
        if (*(float *)(*(int *)(iVar1 + 0xa4) + 0x1c) < 0.0) {
          fVar4 = fVar4 * -1.0;
        }
        *(float *)(*(int *)(iVar1 + 0xa4) + 0x1c) = fVar4;
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049b280  Lua_SetActorWalkChore ---- */
/* Lua opcode: SetActorWalkChore */

void Lua_SetActorWalkChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  void *actor;
  longlong lVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(iVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(iVar1), iVar3 == 0x52544341)) {
    iVar3 = lua_isnumber(iVar2);
    if ((iVar3 == 0) && (iVar3 = lua_isnil(iVar2), iVar3 == 0)) {
      return;
    }
    iVar1 = lua_getuserdata(iVar1);
    actor = (void *)Actor_FromHandle(iVar1);
    iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)((int)actor + 0xa0),(void **)&local_4);
    if (iVar1 != 0) {
      iVar1 = lua_isnumber(iVar2);
      if (iVar1 == 0) {
        iVar1 = -1;
      }
      else {
        lVar4 = (longlong)lua_getnumber(iVar2);
        iVar1 = (int)lVar4;
      }
      Actor_SetWalkChore(actor,iVar1,(void *)local_4);
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049b350  Lua_SetActorTurnChores ---- */
/* Lua opcode: SetActorTurnChores */

void Lua_SetActorTurnChores(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  void *luaObj;
  int iVar4;
  void *actor;
  longlong lVar5;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  luaObj = (void *)lua_lua2C(4);
  iVar4 = lua_isuserdata(iVar1);
  if (iVar4 != 0) {
    iVar4 = lua_tag(iVar1);
    if (iVar4 == 0x52544341) {
      iVar4 = lua_isnumber(iVar2);
      if (iVar4 != 0) {
        iVar4 = lua_isnumber(iVar3);
        if (iVar4 != 0) {
          iVar1 = lua_getuserdata(iVar1);
          actor = (void *)Actor_FromHandle(iVar1);
          iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)((int)actor + 0xa0),(void **)&local_4);
          if (iVar1 != 0) {
            lVar5 = (longlong)lua_getnumber(iVar3);
            iVar1 = (int)lVar5;
            lVar5 = (longlong)lua_getnumber(iVar2);
            Actor_SetTurnChores(actor,(int)lVar5,iVar1,(void *)local_4);
          }
        }
      }
    }
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x0049b430  Lua_SetActorRestChore ---- */
/* Lua opcode: SetActorRestChore */

void Lua_SetActorRestChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  void *actor;
  longlong lVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(iVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(iVar1), iVar3 == 0x52544341)) {
    iVar3 = lua_isnumber(iVar2);
    if ((iVar3 == 0) && (iVar3 = lua_isnil(iVar2), iVar3 == 0)) {
      return;
    }
    iVar1 = lua_getuserdata(iVar1);
    actor = (void *)Actor_FromHandle(iVar1);
    iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)((int)actor + 0xa0),(void **)&local_4);
    if (iVar1 != 0) {
      iVar1 = lua_isnil(iVar2);
      if (iVar1 == 0) {
        lVar4 = (longlong)lua_getnumber(iVar2);
        iVar1 = (int)lVar4;
      }
      else {
        iVar1 = -1;
      }
      Actor_SetRestChore(actor,iVar1,(void *)local_4);
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049b500  Lua_SetActorMumblechore ---- */
/* Lua opcode: SetActorMumblechore */

void Lua_SetActorMumblechore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  longlong lVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(iVar2);
      if (iVar3 != 0) {
        lVar4 = (longlong)lua_getnumber(iVar2);
        iVar1 = lua_getuserdata(iVar1);
        iVar1 = Actor_FromHandle(iVar1);
        iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_4);
        if ((iVar1 != 0) && (local_4 != 0)) {
          *(int *)(local_4 + 0x78) = (int)lVar4;
        }
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049b5a0  Lua_SetActorTalkChore ---- */
/* Lua opcode: SetActorTalkChore */

void Lua_SetActorTalkChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  void *luaObj;
  int iVar4;
  undefined4 uVar5;
  longlong lVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  luaObj = (void *)lua_lua2C(4);
  iVar4 = lua_isuserdata(iVar1);
  if (((iVar4 != 0) && (iVar4 = lua_tag(iVar1), iVar4 == 0x52544341)) &&
     (iVar4 = lua_isnumber(iVar2), iVar4 != 0)) {
    iVar4 = lua_isnumber(iVar3);
    if ((iVar4 == 0) && (iVar4 = lua_isnil(iVar3), iVar4 == 0)) {
      return;
    }
    lVar6 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar6;
    if ((0 < iVar2) && (iVar2 < 0x11)) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_4);
      if ((iVar1 != 0) && (local_4 != 0)) {
        iVar1 = lua_isnumber(iVar3);
        if (iVar1 == 0) {
          uVar5 = 0xffffffff;
        }
        else {
          lVar6 = (longlong)lua_getnumber(iVar3);
          uVar5 = (undefined4)lVar6;
        }
        *(undefined4 *)(local_4 + 0x34 + iVar2 * 4) = uVar5;
        lua_isnil(iVar3);
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049b6c0  Lua_SetActorHead ---- */
/* WARNING: Variable defined which should be unmapped: local_24 */
/* WARNING: Variable defined which should be unmapped: local_28 */
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: SetActorHead */

void Lua_SetActorHead(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  void *actor;
  longlong lVar9;
  float maxYaw;
  float maxPitch;
  float maxRoll;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  iVar6 = lua_lua2C(6);
  iVar7 = lua_lua2C(7);
  iVar8 = lua_isuserdata(iVar1);
  if (iVar8 != 0) {
    iVar8 = lua_tag(iVar1);
    if (iVar8 == 0x52544341) {
      iVar8 = lua_isnumber(iVar2);
      if (iVar8 != 0) {
        iVar8 = lua_isnumber(iVar3);
        if (iVar8 != 0) {
          iVar8 = lua_isnumber(iVar4);
          if (iVar8 != 0) {
            iVar8 = lua_isnumber(iVar5);
            if (iVar8 != 0) {
              iVar8 = lua_isnumber(iVar6);
              if (iVar8 != 0) {
                iVar8 = lua_isnumber(iVar7);
                if (iVar8 != 0) {
                  iVar1 = lua_getuserdata(iVar1);
                  actor = (void *)Actor_FromHandle(iVar1);
                  maxYaw = lua_getnumber(iVar7);
                  maxPitch = lua_getnumber(iVar6);
                  maxRoll = lua_getnumber(iVar5);
                  lVar9 = (longlong)lua_getnumber(iVar4);
                  iVar1 = (int)lVar9;
                  lVar9 = (longlong)lua_getnumber(iVar3);
                  iVar3 = (int)lVar9;
                  lVar9 = (longlong)lua_getnumber(iVar2);
                  Actor_SetHead(actor,(int)lVar9,iVar3,iVar1,maxRoll,maxPitch,maxYaw);
                }
              }
            }
          }
        }
      }
    }
  }
  return;
}
#undef local_10
#undef local_24
#undef local_28
#undef local_2c
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0049b830  Lua_CanActorSee ---- */
/* Lua opcode: CanActorSee */

void Lua_CanActorSee(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  void *target;
  void *target_00;
  #define local_14 (*(float *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 == 0) {
    return;
  }
  iVar3 = lua_tag(iVar1);
  if (iVar3 != 0x52544341) {
    return;
  }
  iVar1 = lua_getuserdata(iVar1);
  target = (void *)Actor_FromHandle(iVar1);
  local_10 = (uint)target;
  iVar1 = lua_isnumber(iVar2);
  if (iVar1 == 0) {
    iVar1 = lua_isuserdata(iVar2);
    if ((iVar1 == 0) || (iVar1 = lua_tag(iVar2), iVar1 != 0x52544341)) {
      iVar1 = lua_isnil(iVar2);
      if (iVar1 == 0) {
        return;
      }
      if (g_pSelectedActor == (void *)0x0) {
        return;
      }
      iVar1 = Actor_CanSee(g_pSelectedActor,target,&local_14);
      if (iVar1 != 0) {
        lua_pushnumber(local_14);
        return;
      }
    }
    else {
      iVar1 = lua_getuserdata(iVar2);
      target_00 = (void *)Actor_FromHandle(iVar1);
      iVar1 = Actor_CanSee(target,target_00,&local_14);
      if (iVar1 != 0) {
        lua_pushnumber(local_14);
        return;
      }
    }
  }
  else {
    iVar1 = lua_lua2C(3);
    iVar3 = lua_lua2C(4);
    local_c[0] = lua_getnumber(iVar2);
    iVar2 = lua_isnumber(iVar1);
    if (iVar2 == 0) {
      local_c[1] = 0.0;
    }
    else {
      local_c[1] = lua_getnumber(iVar1);
    }
    iVar1 = lua_isnumber(iVar3);
    if (iVar1 == 0) {
      local_c[2] = 0.0;
    }
    else {
      local_c[2] = lua_getnumber(iVar3);
    }
    iVar1 = Actor_CanSeePoint((void *)local_10,local_c,&local_14);
    if (iVar1 != 0) {
      lua_pushnumber(local_14);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_14
#undef local_c


/* ---- 0x0049b9e0  Lua_GetVisibleThings ---- */
/* Lua opcode: GetVisibleThings */

void Lua_GetVisibleThings(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *target;
  int iVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  uint uVar5;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isuserdata(iVar1);
    if ((iVar2 != 0) && (iVar2 = lua_tag(iVar1), iVar2 == 0x52544341)) {
      iVar1 = lua_getuserdata(iVar1);
      local_8 = Actor_FromHandle(iVar1);
    }
  }
  else {
    local_8 = (uint)g_pSelectedActor;
    if (g_pSelectedActor == (void *)0x0) {
      return;
    }
  }
  iVar1 = lua_createtable();
  if (*(char *)(local_8 + 0x7c) == '\0') {
    lua_pushobject(iVar1);
  }
  for (piVar3 = Set_GetActorListByName((char *)(local_8 + 0x7c)); piVar3 != (int *)0x0;
      piVar3 = (int *)piVar3[2]) {
    target = (void *)((int)g_pActorTable + *piVar3 * 0xa8);
    if ((((target != (void *)0x0) && (target != (void *)local_8)) &&
        ((*(byte *)(local_8 + 4) & 1) == 0)) &&
       (iVar2 = Actor_CanSee((void *)local_8,target,&local_4), iVar2 != 0)) {
      lua_pushobject(iVar1);
      uVar5 = 0x52544341;
      pcVar4 = (char *)Actor_GetHandle(target,0x52544341);
      lua_pushusertag(pcVar4,uVar5);
      lua_pushnumber(1.0);
      lua_settable();
    }
  }
  lua_pushobject(iVar1);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x0049bb10  Lua_GetActorRect ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetActorRect */

void Lua_GetActorRect(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if ((iVar1 != 0) && (*(int *)(iVar1 + 0x68) != 0)) {
        lua_pushnumber((float)*(int *)(iVar1 + 0x6c));
        lua_pushnumber((float)*(int *)(iVar1 + 0x70));
        lua_pushnumber((float)*(int *)(iVar1 + 0x74));
        lua_pushnumber((float)*(int *)(iVar1 + 0x78));
        return;
      }
      lua_pushnil();
    }
  }
  return;
}
#undef local_c


/* ---- 0x0049bba0  Lua_GetActorPuckVector ---- */
/* Lua opcode: GetActorPuckVector */

void Lua_GetActorPuckVector(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(iVar2);
  if ((iVar4 != 0) && (iVar4 = lua_tag(iVar2), iVar4 == 0x52544341)) {
    iVar3 = lua_isnil(iVar3);
    iVar2 = lua_getuserdata(iVar2);
    iVar2 = Actor_FromHandle(iVar2);
    if (*(int *)(iVar2 + 0xa4) == 0) {
      Actor_CreateExtra(iVar2);
    }
    if ((iVar2 != 0) &&
       (pfVar1 = *(float **)(*(int *)(iVar2 + 0xa4) + 0x1b4), pfVar1 != (float *)0x0)) {
      local_c[0] = pfVar1[6];
      local_c[1] = pfVar1[7];
      local_c[2] = pfVar1[8];
      if (iVar3 == 0) {
        local_c[0] = local_c[0] + *pfVar1;
        local_c[1] = pfVar1[1] + local_c[1];
        local_c[2] = pfVar1[2] + local_c[2];
      }
      lua_pushnumber(local_c[0]);
      lua_pushnumber(local_c[1]);
      lua_pushnumber(local_c[2]);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_c


/* ---- 0x0049bcc0  Lua_GetActorYawToPoint ---- */
/* Lua opcode: GetActorYawToPoint(actor, x, y, z | {x, y, z}). Creates the extra and the walker if
   missing, then returns Actor_GetYawToPoint. */

void Lua_GetActorYawToPoint(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float n;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      iVar3 = lua_istable(iVar2);
      if (iVar3 == 0) {
        iVar3 = lua_lua2C(3);
        iVar5 = lua_lua2C(4);
      }
      else {
        lua_pushobject(iVar2);
        lua_pushstring(&DAT_004e8454);
        iVar4 = lua_gettable();
        lua_pushobject(iVar2);
        lua_pushstring(&DAT_004e8450);
        iVar3 = lua_gettable();
        lua_pushobject(iVar2);
        lua_pushstring(&DAT_004ec3b8);
        iVar5 = lua_gettable();
        iVar2 = iVar4;
      }
      local_c[0] = lua_getnumber(iVar2);
      local_c[1] = lua_getnumber(iVar3);
      local_c[2] = lua_getnumber(iVar5);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      if (*(int *)(*(int *)(iVar1 + 0xa4) + 0x1b4) == 0) {
        Actor_CreateWalker(iVar1,1);
      }
      n = Actor_GetYawToPoint(*(void **)(*(int *)(iVar1 + 0xa4) + 0x1b4),local_c);
      lua_pushnumber(n);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_c


/* ---- 0x0049be40  Lua_SetActorReflection ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: SetActorReflection */

void Lua_SetActorReflection(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  void *actor;
  float angle;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(iVar1);
      angle = lua_getnumber(iVar2);
      Actor_SetReflection(actor,angle);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_c


/* ---- 0x0049bec0  Lua_GetActorPos ---- */
/* Lua opcode: GetActorPos */

void Lua_GetActorPos(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      lua_pushnumber(*(float *)(iVar1 + 0xc));
      lua_pushnumber(*(float *)(iVar1 + 0x10));
      lua_pushnumber(*(float *)(iVar1 + 0x14));
    }
  }
  return;
}

/* ---- 0x0049bf30  Lua_GetActorRot ---- */
/* Lua opcode: GetActorRot */

void Lua_GetActorRot(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      lua_pushnumber(*(float *)(iVar1 + 0x24));
      lua_pushnumber(*(float *)(iVar1 + 0x28));
      lua_pushnumber(*(float *)(iVar1 + 0x2c));
    }
  }
  return;
}

/* ---- 0x0049bfa0  Lua_SetActorRot ---- */
/* Lua opcode: SetActorRot */

void Lua_SetActorRot(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  iVar6 = lua_isuserdata(iVar1);
  if (iVar6 != 0) {
    iVar6 = lua_tag(iVar1);
    if (iVar6 == 0x52544341) {
      iVar6 = lua_isnumber(iVar2);
      if (iVar6 != 0) {
        iVar6 = lua_isnumber(iVar3);
        if (iVar6 != 0) {
          iVar6 = lua_isnumber(iVar4);
          if (iVar6 != 0) {
            iVar1 = lua_getuserdata(iVar1);
            uVar7 = Actor_FromHandle(iVar1);
            local_c[0] = lua_getnumber(iVar2);
            local_c[1] = lua_getnumber(iVar3);
            local_c[2] = lua_getnumber(iVar4);
            iVar1 = lua_isnil(iVar5);
            Actor_SetRot(uVar7,local_c,iVar1);
          }
        }
      }
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_c


/* ---- 0x0049c0a0  Lua_SetActorPitch ---- */
/* Lua opcode: SetActorPitch */

void Lua_SetActorPitch(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      fVar4 = lua_getnumber(iVar2);
      *(float *)(iVar1 + 0x24) = fVar4;
      *(undefined4 *)(iVar1 + 0x34) = 0;
    }
  }
  return;
}

/* ---- 0x0049c110  Lua_SetActorRoll ---- */
/* Lua opcode: SetActorRoll */

void Lua_SetActorRoll(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      fVar4 = lua_getnumber(iVar2);
      *(float *)(iVar1 + 0x2c) = fVar4;
      *(undefined4 *)(iVar1 + 0x34) = 0;
    }
  }
  return;
}

/* ---- 0x0049c180  Lua_TurnActor ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: TurnActor */

void Lua_TurnActor(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(iVar2);
      if (iVar3 != 0) {
        iVar1 = lua_getuserdata(iVar1);
        iVar1 = Actor_FromHandle(iVar1);
        *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) & 0xfffffffe;
        fVar4 = lua_getnumber(iVar2);
        Actor_TurnKey(iVar1,fVar4);
      }
    }
  }
  return;
}
#undef local_c


/* ---- 0x0049c200  Lua_GetActorSector ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetActorSector */

void Lua_GetActorSector(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  longlong lVar5;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(iVar2);
      if (iVar3 != 0) {
        iVar1 = lua_getuserdata(iVar1);
        iVar1 = Actor_FromHandle(iVar1);
        lVar5 = (longlong)lua_getnumber(iVar2);
        pcVar4 = (char *)SectorList_FindByPoint(iVar1 + 0xc,(int)lVar5);
        if (pcVar4 != (char *)0x0) {
          lua_pushnumber((float)*(int *)(pcVar4 + 0x20));
          lua_pushstring(pcVar4);
          lua_pushnumber((float)*(int *)(pcVar4 + 0x24));
          return;
        }
        lua_pushnil();
      }
    }
  }
  return;
}
#undef local_c


/* ---- 0x0049c2c0  Lua_IsActorInSector ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: IsActorInSector */

void Lua_IsActorInSector(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  char *this;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isstring(iVar2);
      if (iVar3 != 0) {
        iVar1 = lua_getuserdata(iVar1);
        iVar1 = Actor_FromHandle(iVar1);
        iVar2 = lua_getstring(iVar2);
        this = g_pSectorList;
        if (g_pSectorList != (void *)0x0) {
          do {
            iVar3 = String_ContainsSubstring(this,iVar2);
            if (iVar3 != 0) {
              iVar3 = Sector_ContainsPoint(this,(float *)(iVar1 + 0xc),1);
              if (iVar3 != 0) {
                lua_pushnumber((float)*(int *)(this + 0x20));
                lua_pushstring(this);
                lua_pushnumber((float)*(int *)(this + 0x24));
                return;
              }
            }
            this = *(char **)(this + 0x70);
          } while (this != (char *)0x0);
          lua_pushnil();
          return;
        }
      }
      lua_pushnil();
    }
  }
  return;
}
#undef local_10


/* ---- 0x0049c3b0  Lua_GetPointSector ---- */
/* WARNING: Variable defined which should be unmapped: local_24 */
/* Lua opcode: GetPointSector */

void Lua_GetPointSector(void)

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


/* ---- 0x0049c4c0  Lua_IsPointInSector ---- */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: IsPointInSector */

void Lua_IsPointInSector(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *this;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_isnumber(iVar1);
  if ((((iVar5 != 0) && (iVar5 = lua_isnumber(iVar2), iVar5 != 0)) &&
      (iVar5 = lua_isnumber(iVar3), iVar5 != 0)) && (iVar5 = lua_isstring(iVar4), iVar5 != 0)) {
    local_c[0] = lua_getnumber(iVar1);
    local_c[1] = lua_getnumber(iVar2);
    local_c[2] = lua_getnumber(iVar3);
    iVar1 = lua_getstring(iVar4);
    this = g_pSectorList;
    if (g_pSectorList != (void *)0x0) {
      do {
        iVar2 = String_ContainsSubstring(this,iVar1);
        if ((iVar2 != 0) && (iVar2 = Sector_ContainsPoint(this,local_c,1), iVar2 != 0)) {
          lua_pushnumber((float)*(int *)(this + 0x20));
          lua_pushstring(this);
          lua_pushnumber((float)*(int *)(this + 0x24));
          break;
        }
        this = *(char **)(this + 0x70);
      } while (this != (char *)0x0);
      if (this != (char *)0x0) {
        return;
      }
    }
  }
  lua_pushnil();
  return;
}
#undef local_20
#undef local_c


/* ---- 0x0049c5e0  Lua_RunSystemScript ---- */
/* lua_dofile('_system.lua') */

bool Lua_RunSystemScript(void)

{
  int iVar1;
  
  iVar1 = lua_dofile(s__system_lua_004ec3bc);
  return iVar1 == 0;
}

/* ---- 0x0049c600  Lua_CallSystemFunction ---- */
/* Calls the global Lua function named by the string at 0x004ec3c8 with (flag, str) */

int __cdecl Lua_CallSystemFunction(int flag,char *str)

{
  int iVar1;
  
  if (flag == 0) {
    lua_pushnil();
  }
  else {
    lua_pushnumber(1.0);
  }
  if (str == (char *)0x0) {
    lua_pushnil();
  }
  else {
    lua_pushstring(str);
  }
  iVar1 = lua_getglobal(&DAT_004ec3c8);
  iVar1 = lua_callfunction(iVar1);
  return (uint)(iVar1 == 0);
}

/* ---- 0x0049c660  Lua_CallCamChangeHandler ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* system.camChangeHandler(from, to) */

void __cdecl Lua_CallCamChangeHandler(int fromSetup,int toSetup)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  lua_beginblock();
  iVar1 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(iVar1);
  lua_pushstring(s_camChangeHandler_004ec3d0);
  iVar1 = lua_gettable();
  iVar2 = lua_isfunction(iVar1);
  if (iVar2 != 0) {
    lua_pushnumber((float)fromSetup);
    lua_pushnumber((float)toSetup);
    lua_callfunction(iVar1);
  }
  lua_endblock();
  return;
}
#undef local_c


/* ---- 0x0049c6e0  Lua_CallPostCamChangeHandler ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* system.postCamChangeHandler(setup) */

void __cdecl Lua_CallPostCamChangeHandler(int setup)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  lua_beginblock();
  iVar1 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(iVar1);
  lua_pushstring(s_postCamChangeHandler_004ec3e4);
  iVar1 = lua_gettable();
  iVar2 = lua_isfunction(iVar1);
  if (iVar2 != 0) {
    lua_pushnumber((float)setup);
    lua_callfunction(iVar1);
  }
  lua_endblock();
  return;
}
#undef local_8


/* ---- 0x0049c8f0  Lua_UpdateFrame ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_1c */
/* Per frame: stores system.frameTime and system.movieTime, collects garbage every 10 s, runs
   lua_updatetasks */

void Lua_UpdateFrame(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  
  g_dwMovieTime = Insane_Poll();
  uVar1 = Timer_GetFrameMs();
  g_dwLuaGcTimerMs = g_dwLuaGcTimerMs + uVar1;
  if (10000.0 < (float)g_dwLuaGcTimerMs) {
    lua_collectgarbage(0);
    g_dwLuaGcTimerMs = 0;
  }
  lua_beginblock();
  iVar2 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(iVar2);
  lua_pushstring(s_frameTime_004ec41c);
  lua_pushnumber((float)uVar1);
  lua_settable();
  iVar2 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(iVar2);
  lua_pushstring(s_movieTime_004ec410);
  lua_pushnumber((float)(int)g_dwMovieTime);
  lua_settable();
  lua_endblock();
  lua_updatetasks(0);
  return;
}
#undef local_1c

#endif


/* ---- 0x0049ca60  Lua_OpenEngineLib ---- */
/* lua_openlib() wrapper used to register the 279-entry engine opcode table at 0x004ea8b0 */

void Lua_OpenEngineLib(int *param_1,int param_2)

{
  lua_openlib(param_1,param_2);
  return;
}

/* ---- 0x0049ca80  Lua_JustLoaded ---- */
/* Lua opcode: JustLoaded */

void Lua_JustLoaded(void)

{
  int iVar1;
  
  iVar1 = Engine_TakeRestoreFlag();
  if (iVar1 != 0) {
    lua_pushnumber(1.0);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0049ca98. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lua_pushnil();
  return;
}

/* ---- 0x0049caa0  Lua_ActorVoiceIs3D ---- */
/* Lua opcode: ActorVoiceIs3D */

void Lua_ActorVoiceIs3D(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    lua_tag(iVar1);
  }
  iVar1 = lua_getuserdata(iVar1);
  iVar1 = Actor_FromHandle(iVar1);
  iVar2 = lua_isnil(iVar2);
  if (iVar2 != 0) {
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xfffffff7;
    return;
  }
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 8;
  return;
}

/* ---- 0x0049cb10  Lua_ResolveCostumeArg ---- */
/* Turns the optional costume argument of the chore opcodes (nil, index or name) into the costume
   record in the actor's list */

int __cdecl Lua_ResolveCostumeArg(void *luaObj,void *costumeList,void **outCostume)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  
  *outCostume = costumeList;
  iVar2 = lua_isnil((int)luaObj);
  if (iVar2 != 0) {
    return 1;
  }
  iVar2 = lua_isnumber((int)luaObj);
  if (iVar2 == 0) {
    iVar2 = lua_isstring((int)luaObj);
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = lua_getstring((int)luaObj);
    pvVar1 = *outCostume;
    while (pvVar1 != (void *)0x0) {
      iVar4 = iVar2;
      iVar3 = Cos_InstGetCostume(*(int *)*outCostume,(int *)0x0);
      iVar4 = _stricmp(iVar3,iVar4);
      if (iVar4 == 0) break;
      pvVar1 = *(void **)((int)*outCostume + 0xb0);
      *outCostume = pvVar1;
    }
  }
  else {
    lVar5 = (longlong)lua_getnumber((int)luaObj);
    iVar2 = (int)lVar5;
    if (*outCostume != (void *)0x0) {
      while (0 < iVar2) {
        pvVar1 = *(void **)((int)*outCostume + 0xb0);
        *outCostume = pvVar1;
        iVar2 = iVar2 + -1;
        if (pvVar1 == (void *)0x0) {
          return 0;
        }
      }
    }
  }
  return (uint)(*outCostume != (void *)0x0);
}

/* ---- 0x0049cbe0  Lua_FunctionName ---- */
/* Lua opcode: FunctionName */

void Lua_FunctionName(void)

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


/* ---- 0x0049cca0  Lua_CheckForFile ---- */
/* Lua opcode: CheckForFile */

void Lua_CheckForFile(void)

{
  void **ppvVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_isstring(iVar2);
  if (iVar3 != 0) {
    puVar4 = &DAT_004dda54;
    ppvVar1 = &g_pSvcLua->pFopen;
    iVar2 = lua_getstring(iVar2);
    iVar2 = (*(code *)*ppvVar1)(iVar2,puVar4);
    if (iVar2 == 0) {
      lua_pushnil();
      return;
    }
    (*g_pSvcLua->pFclose)(iVar2);
    lua_pushnumber(1.0);
  }
  return;
}

/* ---- 0x0049cd10  Lua_NukeResources ---- */
/* Lua opcode: NukeResources */

void Lua_NukeResources(void)

{
  Set_SetCurrent((void *)0x0,0);
  Actors_FreeAllCostumes();
  Engine_ResetState();
  g_pShadowMaterial = (void *)0x0;
  return;
}

/* ---- 0x0049cd40  Lua_DetachFromResources ---- */
/* Lua opcode: DetachFromResources */

void Lua_DetachFromResources(void)

{
  Movie_Stop();
  SoundsCloseVoiceFile();
  Resource_CloseArchives();
  return;
}

/* ---- 0x0049cd50  Lua_AttachToResources ---- */
/* Lua opcode: AttachToResources */

void Lua_AttachToResources(void)

{
  Resource_CloseArchives();
  Resource_OpenArchives();
  return;
}

/* ---- 0x0049cd60  Lua_SearchForFileOrSwapCDs ---- */
/* Lua opcode: SearchForFileOrSwapCDs */

void Lua_SearchForFileOrSwapCDs(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void **ppvVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *caption;
  char *text;
  undefined *puVar6;
  uint flags;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_lua2C(3);
  iVar5 = lua_isstring(iVar2);
  if (iVar5 != 0) {
    iVar5 = lua_isstring(iVar3);
    if (iVar5 != 0) {
      iVar5 = lua_isstring(iVar4);
      if (iVar5 != 0) {
        puVar6 = &DAT_004dda54;
        ppvVar1 = &g_pSvcLua->pFopen;
        iVar5 = lua_getstring(iVar4);
        iVar5 = (*(code *)*ppvVar1)(iVar5,puVar6);
        if (iVar5 == 0) {
          ImSetState(0);
          ImStopAllSounds();
          SoundsCloseVoiceFile();
          do {
            flags = 1;
            caption = (char *)lua_getstring(iVar3);
            text = (char *)lua_getstring(iVar2);
            iVar5 = Plat_MessageBox(text,caption,flags);
            if (iVar5 == 2) {
              lua_pushnil();
              lua_pushnil();
              return;
            }
            Resource_CloseArchives();
            Resource_OpenArchives();
            puVar6 = &DAT_004dda54;
            ppvVar1 = &g_pSvcLua->pFopen;
            iVar5 = lua_getstring(iVar4);
            iVar5 = (*(code *)*ppvVar1)(iVar5,puVar6);
          } while (iVar5 == 0);
          (*g_pSvcLua->pFclose)(iVar5);
          lua_pushnumber(1.0);
          lua_pushnumber(1.0);
          return;
        }
        (*g_pSvcLua->pFclose)(iVar5);
        lua_pushnumber(1.0);
        lua_pushnil();
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049cea0  Lua_Load ---- */
/* Lua opcode: Load */

void Lua_Load(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 != 0) {
    Engine_RequestLoad(0);
    return;
  }
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    iVar1 = lua_getstring(iVar1);
    Engine_RequestLoad(iVar1);
  }
  return;
}

/* ---- 0x0049cef0  Lua_Save ---- */
/* Lua opcode: Save */

void Lua_Save(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 != 0) {
    Engine_RequestSave(0);
    return;
  }
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    iVar1 = lua_getstring(iVar1);
    Engine_RequestSave(iVar1);
  }
  return;
}

/* ---- 0x0049cf40  Lua_EnableDebugKeys ---- */
/* Lua opcode: EnableDebugKeys */

void Lua_EnableDebugKeys(void)

{
  g_nDebugKeysEnabled = 1;
  if (UINT_008cab8c != 0) {
    (*(code *)UINT_008cab8c)(1);
  }
  return;
}

/* ---- 0x0049cf60  Lua_WorldToScreen ---- */
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: WorldToScreen */

void Lua_WorldToScreen(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_isnumber(iVar1);
  if (iVar4 != 0) {
    iVar4 = lua_isnumber(iVar2);
    if (iVar4 != 0) {
      iVar4 = lua_isnumber(iVar3);
      if (iVar4 != 0) {
        local_18[0] = lua_getnumber(iVar1);
        local_18[1] = lua_getnumber(iVar2);
        local_18[2] = lua_getnumber(iVar3);
        iVar1 = rdCamera_ProjectPoint(local_18,&local_c);
        if (iVar1 != 0) {
          lua_pushnumber((float)(int)local_c);
          lua_pushnumber((float)(int)local_8);
          return;
        }
        lua_pushnil();
        lua_pushnil();
      }
    }
  }
  return;
}
#undef local_18
#undef local_2c
#undef local_8
#undef local_c


/* ---- 0x0049d030  Lua_ScreenToWorld ---- */
/* Lua opcode: ScreenToWorld */

void Lua_ScreenToWorld(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  float *outPos;
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float (*)[2])(_frame + (0x20 - 0x8)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_isnumber(iVar2);
  if (iVar4 != 0) {
    iVar4 = lua_isnumber(iVar3);
    if (iVar4 != 0) {
      lVar5 = (longlong)lua_getnumber(iVar2);
      if ((int)lVar5 < 0) {
        bVar1 = false;
      }
      else {
        lVar5 = (longlong)lua_getnumber(iVar2);
        bVar1 = (int)lVar5 < 0x280;
      }
      if (bVar1) {
        lVar5 = (longlong)lua_getnumber(iVar3);
        if ((int)lVar5 < 0) {
          bVar1 = false;
        }
        else {
          lVar5 = (longlong)lua_getnumber(iVar3);
          bVar1 = (int)lVar5 < 0x1e0;
        }
        if (bVar1) {
          outPos = &local_c;
          lVar5 = (longlong)lua_getnumber(iVar3);
          iVar3 = (int)lVar5;
          lVar5 = (longlong)lua_getnumber(iVar2);
          Render_ScreenToWorld((int)lVar5,iVar3,outPos);
          lua_pushnumber(local_c);
          lua_pushnumber(local_8[0]);
          lua_pushnumber(local_8[1]);
        }
      }
    }
  }
  return;
}
#undef local_8
#undef local_c


/* ---- 0x0049d140  Lua_TypeOverride ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: Lua_TypeOverride */

void Lua_TypeOverride(void)

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
  iVar2 = lua_getref(UINT_008cab48);
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


/* ---- 0x0049d220  Lua_ConcatFallback ---- */
/* Lua opcode: Lua_ConcatFallback */

void Lua_ConcatFallback(void)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  int iVar3;
  char *fmt;
  int iVar4;
  undefined1 *puVar5;
  uint uVar6;
  uint *puVar7;
  int iVar8;
  char *pcVar9;
  #define local_88 (*(uint *)(_frame + (0xa0 - 0x88)))
  #define local_84 (*(uint *)(_frame + (0xa0 - 0x84)))
  #define local_80 (*(char (*)[128])(_frame + (0xa0 - 0x80)))
  
  local_80[0] = '\0';
  local_88 = lua_lua2C(1);
  local_84 = lua_lua2C(2);
  iVar8 = 0;
  puVar7 = &local_88;
  do {
    uVar2 = *puVar7;
    iVar3 = lua_isstring(uVar2);
    if (iVar3 == 0) {
      iVar3 = lua_isnil(uVar2);
      if (iVar3 == 0) {
        iVar3 = lua_isuserdata(uVar2);
        if (iVar3 == 0) goto LAB_0049d34b;
      }
    }
    uVar6 = 0xffffffff;
    pcVar9 = local_80;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar1 != '\0');
    pcVar9 = local_80 + (~uVar6 - 1);
    iVar3 = lua_isstring(uVar2);
    if (iVar3 == 0) {
      iVar3 = lua_isnil(uVar2);
      if (iVar3 == 0) {
        iVar3 = lua_tag(uVar2);
        if (iVar3 != 0x52544341) {
LAB_0049d34b:
          lua_pushobject(local_88);
          lua_pushobject(local_84);
          iVar8 = lua_getref(UINT_008cab44);
          lua_callfunction(iVar8);
          iVar8 = lua_lua2C(1);
          lua_pushobject(iVar8);
          return;
        }
        iVar3 = lua_getuserdata(uVar2);
        iVar4 = Actor_FromHandle(iVar3);
        if ((*(int *)(iVar4 + 0xa0) == 0) ||
           (iVar4 = *(int *)(*(int *)(iVar4 + 0xa0) + 4), iVar4 == 0)) {
          puVar5 = &DAT_004f5a98;
        }
        else {
          puVar5 = *(undefined1 **)(iVar4 + 4);
        }
        sprintf(pcVar9,s__actor_d__s__004ec494,iVar3,puVar5);
      }
      else {
        sprintf(pcVar9,s__nil__004ec4a4);
      }
    }
    else {
      fmt = (char *)lua_getstring(uVar2);
      sprintf(pcVar9,fmt);
    }
    iVar8 = iVar8 + 1;
    puVar7 = puVar7 + 1;
    if (1 < iVar8) {
      lua_pushstring(local_80);
      return;
    }
  } while( true );
}
#undef local_80
#undef local_84
#undef local_88


/* ---- 0x0049d3a0  Lua_exit ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: exit */

void Lua_exit(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    Engine_Quit((int)lVar3);
    return;
  }
  Engine_Quit(0);
  return;
}

/* ---- 0x0049d3f0  Lua_EnableControl ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: EnableControl */

void Lua_EnableControl(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    lua_pushnil();
    return;
  }
  lVar3 = (longlong)lua_getnumber(iVar1);
  Control_Enable((int)lVar3);
  return;
}

/* ---- 0x0049d430  Lua_DisableControl ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: DisableControl */

void Lua_DisableControl(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    lua_pushnil();
    return;
  }
  lVar3 = (longlong)lua_getnumber(iVar1);
  Control_Disable((int)lVar3);
  return;
}

/* ---- 0x0049d470  Lua_GetControlState ---- */
/* Lua opcode: GetControlState */

void Lua_GetControlState(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  longlong lVar4;
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar4 = (longlong)lua_getnumber(iVar1);
    uVar3 = (uint)lVar4;
    if (uVar3 <= g_nControlCount - 1U) {
      if (((&g_ControlTable)[uVar3 * 4] & 4) != 0) {
        iVar1 = Input_GetButtonState
                          (*(int *)(&DAT_004e87cc + uVar3 * 0x10),&local_4,(int *)&local_8);
        if (iVar1 == 0) {
          lua_pushnil();
        }
        else {
          lua_pushnumber(1.0);
        }
        if (local_8 != 0) {
          lua_pushnumber(1.0);
          return;
        }
        lua_pushnil();
        return;
      }
      local_c = Input_GetAxis(*(int *)(&DAT_004e87cc + uVar3 * 0x10));
      if (((&g_ControlTable)[uVar3 * 4] & 8) != 0) {
        local_c = -local_c;
      }
      lua_pushnumber(local_c);
    }
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0049d550  Lua_CallCostumeOverrideHandler ---- */
void __cdecl Lua_CallCostumeOverrideHandler(void *actor,int flag)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  bool bVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  int unaff_EDI;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  bVar1 = false;
  bVar2 = false;
  lua_beginblock();
  pcVar3 = (char *)Actor_GetHandle(actor,unaff_EDI);
  iVar4 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(iVar4);
  lua_pushstring(s_costumeOverrideHandler_004ec4ac);
  pcVar5 = (char *)lua_gettable();
  iVar4 = lua_istable((int)pcVar5);
  if (iVar4 == 0) {
    iVar4 = lua_isfunction((int)pcVar5);
    if (iVar4 == 0) {
      lua_isnil((int)pcVar5);
      pcVar6 = pcVar3;
    }
    else {
      bVar2 = false;
      bVar1 = true;
      pcVar6 = pcVar5;
    }
  }
  else {
    lua_pushobject((int)pcVar5);
    lua_pushstring(s_costumeOverrideHandler_004ec4ac);
    pcVar6 = (char *)lua_gettable();
    iVar4 = lua_isfunction((int)pcVar6);
    if (iVar4 != 0) {
      bVar1 = true;
      bVar2 = true;
    }
  }
  if (bVar1) {
    if (bVar2) {
      lua_pushobject((int)pcVar5);
    }
    lua_pushusertag(pcVar3,0x52544341);
    if (flag == 0) {
      lua_pushnil();
    }
    else {
      lua_pushnumber(1.0);
    }
    lua_callfunction((int)pcVar6);
  }
  lua_endblock();
  return;
}
#undef local_4


/* ---- 0x0049d670  Lua_CallCostumeMarkerHandler ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* system.costumeMarkerHandler(actor, marker) from keyframe markers */

void __cdecl Lua_CallCostumeMarkerHandler(void *actor,uint marker)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  bool bVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int unaff_EBX;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  
  bVar1 = false;
  bVar2 = false;
  if (marker != 0) {
    pcVar3 = (char *)Actor_GetHandle(actor,unaff_EBX);
    lua_beginblock();
    iVar4 = lua_getref(g_nLuaSystemTableRef);
    lua_pushobject(iVar4);
    lua_pushstring(s_costumeMarkerHandler_004ec4c4);
    uVar5 = lua_gettable();
    iVar4 = lua_istable(uVar5);
    if (iVar4 == 0) {
      iVar4 = lua_isfunction(uVar5);
      if (iVar4 == 0) {
        lua_isnil(uVar5);
        uVar6 = marker;
      }
      else {
        bVar2 = false;
        bVar1 = true;
        uVar6 = uVar5;
      }
    }
    else {
      lua_pushobject(uVar5);
      lua_pushstring(s_costumeMarkerHandler_004ec4c4);
      uVar6 = lua_gettable();
      iVar4 = lua_isfunction(uVar6);
      if (iVar4 != 0) {
        bVar1 = true;
        bVar2 = true;
      }
    }
    if (bVar1) {
      if (bVar2) {
        lua_pushobject(uVar5);
      }
      lua_pushusertag(pcVar3,0x52544341);
      lua_pushnumber((float)marker);
      lua_callfunction(uVar6);
    }
    lua_endblock();
  }
  return;
}
#undef local_1c


/* ---- 0x0049d7b0  Lua_CallUserPaintHandler ---- */
/* system.userPaintHandler() after a restore */

void Lua_CallUserPaintHandler(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  bVar1 = false;
  bVar2 = false;
  lua_beginblock();
  iVar3 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(iVar3);
  lua_pushstring(s_userPaintHandler_004ec4dc);
  iVar3 = lua_gettable();
  iVar4 = lua_istable(iVar3);
  if (iVar4 == 0) {
    iVar4 = lua_isfunction(iVar3);
    if (iVar4 == 0) {
      lua_isnil(iVar3);
      iVar4 = 0;
    }
    else {
      bVar2 = false;
      bVar1 = true;
      iVar4 = iVar3;
    }
  }
  else {
    lua_pushobject(iVar3);
    lua_pushstring(s_userPaintHandler_004ec4dc);
    iVar4 = lua_gettable();
    iVar5 = lua_isfunction(iVar4);
    if (iVar5 != 0) {
      bVar1 = true;
      bVar2 = true;
    }
  }
  if (bVar1) {
    if (bVar2) {
      lua_pushobject(iVar3);
    }
    lua_callfunction(iVar4);
  }
  lua_endblock();
  return;
}
#undef local_4


/* ---- 0x0049d890  Lua_CallExitHandler ---- */
/* system.exitHandler(); returns 1 when a handler existed */

uint Lua_CallExitHandler(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  bVar1 = false;
  local_4 = 0;
  lua_beginblock();
  iVar2 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(iVar2);
  lua_pushstring(s_exitHandler_004ec4f0);
  iVar2 = lua_gettable();
  iVar3 = lua_istable(iVar2);
  if (iVar3 == 0) {
    iVar3 = lua_isfunction(iVar2);
    if (iVar3 == 0) {
      lua_isnil(iVar2);
      iVar3 = 0;
    }
    else {
      bVar1 = false;
      local_4 = 1;
      iVar3 = iVar2;
    }
  }
  else {
    lua_pushobject(iVar2);
    lua_pushstring(s_exitHandler_004ec4f0);
    iVar3 = lua_gettable();
    iVar4 = lua_isfunction(iVar3);
    if (iVar4 != 0) {
      bVar1 = true;
      local_4 = 1;
    }
  }
  if (local_4 != 0) {
    if (bVar1) {
      lua_pushobject(iVar2);
    }
    lua_callfunction(iVar3);
  }
  lua_endblock();
  return local_4;
}
#undef local_4


/* ---- 0x0049d970  Lua_CallPauseHandler ---- */
/* system.pauseHandler() (Pause key) */

uint Lua_CallPauseHandler(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  bVar1 = false;
  local_4 = 0;
  lua_beginblock();
  iVar2 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(iVar2);
  lua_pushstring(s_pauseHandler_004ec4fc);
  iVar2 = lua_gettable();
  iVar3 = lua_istable(iVar2);
  if (iVar3 == 0) {
    iVar3 = lua_isfunction(iVar2);
    if (iVar3 == 0) {
      lua_isnil(iVar2);
      iVar3 = 0;
    }
    else {
      bVar1 = false;
      local_4 = 1;
      iVar3 = iVar2;
    }
  }
  else {
    lua_pushobject(iVar2);
    lua_pushstring(s_pauseHandler_004ec4fc);
    iVar3 = lua_gettable();
    iVar4 = lua_isfunction(iVar3);
    if (iVar4 != 0) {
      bVar1 = true;
      local_4 = 1;
    }
  }
  if (local_4 != 0) {
    if (bVar1) {
      lua_pushobject(iVar2);
    }
    lua_callfunction(iVar3);
  }
  lua_endblock();
  return local_4;
}
#undef local_4


/* ---- 0x0049da50  Lua_CallCharacterHandler ---- */
/* system.characterHandler(char); true when the script consumed it */

int __cdecl Lua_CallCharacterHandler(int ch)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  #define local_6 (*(ushort *)(_frame + (0x20 - 0x6)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar5 = 0;
  bVar1 = false;
  local_4 = 0;
  lua_beginblock();
  iVar2 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(iVar2);
  lua_pushstring(s_characterHandler_004ec50c);
  iVar2 = lua_gettable();
  iVar3 = lua_istable(iVar2);
  if (iVar3 == 0) {
    iVar3 = lua_isfunction(iVar2);
    if (iVar3 == 0) {
      lua_isnil(iVar2);
      iVar3 = ch;
    }
    else {
      local_4 = 0;
      bVar1 = true;
      iVar3 = iVar2;
    }
  }
  else {
    lua_pushobject(iVar2);
    lua_pushstring(s_characterHandler_004ec50c);
    iVar3 = lua_gettable();
    iVar4 = lua_isfunction(iVar3);
    if (iVar4 != 0) {
      bVar1 = true;
      local_4 = 1;
    }
  }
  if (bVar1) {
    if (local_4 != 0) {
      lua_pushobject(iVar2);
    }
    local_6 = (ushort)(byte)ch;
    lua_pushstring((char *)&local_6);
    lua_callfunction(iVar3);
    iVar2 = lua_lua2C(1);
    iVar2 = lua_isnil(iVar2);
    uVar5 = (uint)(iVar2 == 0);
  }
  lua_endblock();
  return uVar5;
}
#undef local_4
#undef local_6


/* ---- 0x0049db70  Lua_MakeCurrentSetup ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: MakeCurrentSetup */

void Lua_MakeCurrentSetup(void)

{
  int iVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    ((code *)Set_ChangeSetup)((int)lVar3,unaff_ESI);
  }
  return;
}
#endif


/* ---- 0x0049dbb0  Lua_GetCurrentSetup ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: GetCurrentSetup */

void Lua_GetCurrentSetup(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *pcVar3;
  void *pvVar4;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    pcVar3 = Set_GetCurrentName();
    iVar2 = lua_getstring(iVar1);
    iVar2 = _stricmp(iVar2,pcVar3);
    if (iVar2 == 0) {
      pvVar4 = Set_GetCurrent();
      if (pvVar4 != (void *)0x0) {
        pvVar4 = Set_GetCurrent();
        lua_pushnumber((float)*(int *)((int)pvVar4 + 0xb4));
        return;
      }
      lua_pushnil();
      return;
    }
    pcVar3 = (char *)lua_getstring(iVar1);
    pvVar4 = Res_Find(0x20544553,pcVar3);
    if (pvVar4 != (void *)0x0) {
      pcVar3 = (char *)lua_getstring(iVar1);
      pvVar4 = Resource_Load(0x20544553,pcVar3);
      lua_pushnumber((float)*(int *)((int)pvVar4 + 0xb4));
    }
  }
  return;
}
#undef local_10
#undef local_4


/* ---- 0x0049dc70  Lua_MakeCurrentSet ---- */
/* Lua opcode: MakeCurrentSet */

void Lua_MakeCurrentSet(void)

{
  int iVar1;
  int iVar2;
  char *name;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 == 0) {
    Set_MakeCurrent((char *)0x0);
    return;
  }
  name = (char *)lua_getstring(iVar1);
  Set_MakeCurrent(name);
  return;
}

/* ---- 0x0049dcb0  Lua_LockSet ---- */
/* Source: Scripts/sputLua.cpp (line 5305, from __FILE__/__LINE__ passed to the allocator) */

void Lua_LockSet(void)

{
  int iVar1;
  int iVar2;
  char *name;
  void *data;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(iVar1);
    data = Resource_Load(0x20544553,name);
    if ((data != (void *)0x0) && (*(int *)((int)data + 0x1ac0) == 0)) {
      ResRef_Add((void *)((int)data + 0x1ac0),data,s_C__grimsrc_libs_grimlib_Scripts__004ec38c,
                 0x14b9);
    }
  }
  return;
}

/* ---- 0x0049dd10  Lua_UnLockSet ---- */
/* Lua opcode: UnLockSet */

void Lua_UnLockSet(void)

{
  int iVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(iVar1);
    pvVar3 = Resource_Load(0x20544553,name);
    if ((pvVar3 != (void *)0x0) && (*(int *)((int)pvVar3 + 0x1ac0) != 0)) {
      ResRef_Remove((void *)((int)pvVar3 + 0x1ac0));
    }
  }
  return;
}

/* ---- 0x0049dd70  Lua_PrintMessage ---- */
/* Lua opcode: PrintMessage */

void Lua_PrintMessage(void)

{
  void **ppvVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_isnil(iVar2);
  if (iVar3 != 0) {
    (*g_pSvcLua->pPrintf2)(s__nil__004ec4a4);
    return;
  }
  iVar3 = lua_isstring(iVar2);
  if (iVar3 != 0) {
    ppvVar1 = &g_pSvcLua->pPrintf2;
    iVar2 = lua_getstring(iVar2);
    (*(code *)*ppvVar1)(iVar2);
  }
  return;
}

/* ---- 0x0049ddd0  Lua_Print_NoOp ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcodes: PrintError, PrintWarning, PrintDebug
   PrintError / PrintWarning / PrintDebug: no-op in the release build */

void Lua_Print_NoOp(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 == 0) {
    lua_isstring(iVar1);
  }
  return;
}
#endif


/* ---- 0x0049de00  Lua_InitGameLibs ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
undefined4 Lua_InitGameLibs(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define acStack_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  if (UINT_008cab80 != 0) {
    return 1;
  }
  (*(code *)UINT_008cab58)();
  Reg_GetString(s_TextAllowed_004ec55c,acStack_20,0x20,&DAT_004f5a98);
  iVar1 = _stricmp(acStack_20,&DAT_004ec554);
  if (iVar1 != 0) {
    *(undefined4 *)lua_assume_binary_exref = 1;
  }
  lua_iolibopen();
  lua_strlibopen();
  lua_mathlibopen();
  Lua_OpenEngineLib(&PTR_s_EnginePause_004ea8b0,UINT_004eb168);
  lua_recognizelib(IMG_ADDR(0x004ea890),4);
  g_nLuaSystemTableRef = Lua_CreateSystemTable();
  iVar1 = lua_getglobal(&DAT_004ec54c);
  lua_pushobject(iVar1);
  UINT_008cab48 = lua_ref(1);
  lua_pushCclosure(((unsigned)(uintptr_t)Lua_TypeOverride),0);
  lua_setglobal(&DAT_004ec54c);
  lua_pushnumber(0.0);
  lua_setglobal(&DAT_004ec544);
  lua_pushnumber(4096.0);
  lua_setglobal(&DAT_004ec53c);
  lua_pushnumber(8192.0);
  lua_setglobal(s_CAMERA_004ec534);
  lua_pushnumber(16384.0);
  lua_setglobal(s_SPECIAL_004ec52c);
  lua_pushnumber(32768.0);
  lua_setglobal(&DAT_004ec528);
  iVar1 = lua_setfallback(s_concat_004ec520,Lua_ConcatFallback);
  lua_pushobject(iVar1);
  UINT_008cab44 = lua_ref(1);
  *(code **)lua_savehook_exref = Lua_SaveUserdataHook;
  *(code **)lua_restorehook_exref = Lua_RestoreUserdataHook;
  Engine_RegisterShutdownHook(Lua_DispatchControlHandlers);
  return 0;
}
#undef acStack_20

#endif


/* ---- 0x0049dfa0  Lua_SaveUserdataHook ---- */
/* lua_savehook: STAT userdata is written as setup<<16 | index in the setup's object state list */

uint Lua_SaveUserdataHook(int param_1,uint param_2)

{
  uint uVar1;
  void *pvVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  
  if (param_1 != 0x54415453) {
    return param_2;
  }
  pvVar2 = Set_GetCurrent();
  if (pvVar2 != (void *)0x0) {
    uVar5 = 0;
    if (*(uint *)((int)pvVar2 + 0xb0) != 0) {
      puVar4 = (uint *)(*(int *)((int)pvVar2 + 0xac) + 0x128);
      do {
        uVar3 = 0;
        for (uVar1 = *puVar4; uVar1 != 0; uVar1 = *(uint *)(uVar1 + 0xf8)) {
          if (uVar1 == param_2) {
            return uVar5 << 0x10 | uVar3;
          }
          uVar3 = uVar3 + 1;
        }
        uVar5 = uVar5 + 1;
        puVar4 = puVar4 + 0x4b;
      } while (uVar5 < *(uint *)((int)pvVar2 + 0xb0));
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

/* ---- 0x0049e020  Lua_RestoreUserdataHook ---- */
/* lua_restorehook: rebuilds STAT, FONT and TEXT userdata pointers from their saved ids */

void * Lua_RestoreUserdataHook(int param_1,void *param_2)

{
  void *pvVar1;
  uint uVar2;
  
  if (param_1 == 0x54415453) {
    if (param_2 == (void *)0xffffffff) {
      param_2 = (void *)0x0;
    }
    else {
      uVar2 = (uint)param_2 & 0xffff;
      pvVar1 = Set_GetCurrent();
      param_2 = *(void **)(*(int *)((int)pvVar1 + 0xac) + 0x128 + ((uint)param_2 >> 0x10) * 300);
      if (uVar2 != 0) {
        do {
          param_2 = *(void **)((int)param_2 + 0xf8);
          uVar2 = uVar2 - 1;
        } while (uVar2 != 0);
        return param_2;
      }
    }
  }
  else {
    if (param_1 == 0x544e4f46) {
      pvVar1 = Res_DataFromHandle(param_2);
      return pvVar1;
    }
    if (param_1 == 0x54584554) {
      pvVar1 = (void *)TextObject_FindBySelf(param_2);
      return pvVar1;
    }
  }
  return param_2;
}

/* ---- 0x0049e0b0  Lua_DispatchControlHandlers ---- */
/* WARNING: Variable defined which should be unmapped: local_58 */
/* Calls system.buttonHandler / system.axisHandler for every enabled control whose state changed
   (last value kept at control+8) */

undefined4 Lua_DispatchControlHandlers(void)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  bool bVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  code *pcVar7;
  uint *puVar8;
  #define local_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define local_44 (*(uint *)(_frame + (0x70 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x70 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x70 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x70 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x70 - 0x34)))
  #define local_30 (*(float (*)[3])(_frame + (0x70 - 0x30)))
  #define local_24 (*(uint *)(_frame + (0x70 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x70 - 0x20)))
  #define local_1c (*(float (*)[2])(_frame + (0x70 - 0x1c)))
  
  bVar1 = false;
  bVar2 = false;
  lua_beginblock();
  iVar3 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(iVar3);
  lua_pushstring(s_buttonHandler_004ec574);
  fVar4 = (float)lua_gettable();
  iVar3 = lua_istable((int)fVar4);
  pcVar7 = lua_isfunction_exref;
  if (iVar3 == 0) {
    iVar3 = lua_isfunction((int)fVar4);
    if (iVar3 == 0) {
      local_44 = 0;
    }
    else {
      bVar1 = false;
      local_44 = 1;
      local_30[1] = fVar4;
    }
  }
  else {
    lua_pushobject((int)fVar4);
    lua_pushstring(s_buttonHandler_004ec574);
    local_30[1] = (float)lua_gettable();
    pcVar7 = lua_isfunction_exref;
    iVar3 = lua_isfunction((int)local_30[1]);
    if (iVar3 != 0) {
      bVar1 = true;
      local_44 = 1;
    }
  }
  iVar3 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(iVar3);
  lua_pushstring(s_axisHandler_004ec568);
  fVar5 = (float)lua_gettable();
  local_1c[0] = fVar5;
  iVar3 = lua_istable((int)fVar5);
  if (iVar3 == 0) {
    iVar3 = (*pcVar7)();
    if (iVar3 == 0) {
      local_3c = 0;
    }
    else {
      bVar2 = false;
      local_3c = 1;
      local_30[2] = fVar5;
    }
  }
  else {
    lua_pushobject((int)fVar5);
    lua_pushstring(s_axisHandler_004ec568);
    local_30[2] = (float)lua_gettable();
    iVar3 = (*pcVar7)(local_30[2]);
    if (iVar3 != 0) {
      bVar2 = true;
      local_3c = 1;
    }
  }
  fVar5 = 0.0;
  if (g_nControlCount != 0) {
    puVar8 = &UINT_004e87d0;
    do {
      if ((puVar8[-2] & 1) != 0) {
        if ((puVar8[-2] & 4) == 0) {
          fVar6 = Input_GetAxis(puVar8[-1]);
          if ((puVar8[-2] & 8) != 0) {
            fVar6 = -fVar6;
          }
          if ((fVar6 != (float)*puVar8) && (local_3c != 0)) {
            if (bVar2) {
              lua_pushobject((int)local_1c[0]);
            }
            lua_pushnumber((float)(uint)fVar5);
            lua_pushnumber(fVar6);
            lua_callfunction((int)local_30[2]);
            *puVar8 = (uint)fVar6;
          }
        }
        else {
          local_30[0] = 0.0;
          fVar6 = (float)Input_GetButtonState(puVar8[-1],(int *)local_30,(int *)&local_20);
          if ((fVar6 != (float)*puVar8) && (local_44 != 0)) {
            if (bVar1) {
              lua_pushobject((int)fVar4);
            }
            local_1c[1] = fVar5;
            lua_pushnumber((float)(uint)fVar5);
            if (fVar6 == 0.0) {
              lua_pushnil();
            }
            else {
              lua_pushnumber(1.0);
            }
            lua_pushnumber((float)(uint)local_30[0]);
            lua_pushnumber((float)(int)local_20);
            lua_callfunction((int)local_30[1]);
            *puVar8 = (uint)fVar6;
          }
        }
      }
      fVar5 = (float)((int)fVar5 + 1);
      puVar8 = puVar8 + 4;
    } while ((uint)fVar5 < (uint)g_nControlCount);
  }
  lua_endblock();
  return 0;
}
#undef local_1c
#undef local_20
#undef local_24
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_44
#undef local_58


/* ---- 0x0049e380  Lua_CreateSystemTable ---- */
/* Creates the global `system` table with the controls table and stub camChange/axis/button
   handlers; returns its ref */

uint Lua_CreateSystemTable(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = lua_createtable();
  lua_pushobject(iVar1);
  lua_setglobal(s_system_004ec584);
  lua_pushobject(iVar1);
  uVar2 = lua_ref(1);
  Lua_CreateControlsTable(uVar2);
  iVar1 = lua_getref(uVar2);
  lua_pushobject(iVar1);
  lua_pushstring(s_camChangeHandler_004ec3d0);
  lua_pushCclosure(((unsigned)(uintptr_t)Lua_Stub),0);
  lua_settable();
  iVar1 = lua_getref(uVar2);
  lua_pushobject(iVar1);
  lua_pushstring(s_axisHandler_004ec568);
  lua_pushCclosure(((unsigned)(uintptr_t)Lua_Stub),0);
  lua_settable();
  iVar1 = lua_getref(uVar2);
  lua_pushobject(iVar1);
  lua_pushstring(s_buttonHandler_004ec574);
  lua_pushCclosure(((unsigned)(uintptr_t)Lua_Stub),0);
  lua_settable();
  return uVar2;
}

/* ---- 0x0049e460  Lua_CreateControlsTable ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* system.controls[name] = index for every entry of g_ControlTable (name at control+0xc) */

void Lua_CreateControlsTable(uint param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined **ppuVar4;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  
  iVar1 = lua_createtable();
  iVar2 = lua_getref(param_1);
  lua_pushobject(iVar2);
  lua_pushstring(s_controls_004ec58c);
  lua_pushobject(iVar1);
  lua_settable();
  uVar3 = 0;
  if (g_nControlCount != 0) {
    ppuVar4 = &PTR_s_KEY_ESCAPE_004e87d4;
    do {
      lua_pushobject(iVar1);
      lua_pushstring(*ppuVar4);
      lua_pushnumber((float)uVar3);
      lua_settable();
      uVar3 = uVar3 + 1;
      ppuVar4 = ppuVar4 + 4;
    } while (uVar3 < (uint)g_nControlCount);
  }
  return;
}
#undef local_1c


/* ---- 0x0049e590  Lua_SetSoundPosition ---- */
/* Lua opcode: SetSoundPosition */

void Lua_SetSoundPosition(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  void *set;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(float (*)[3])(_frame + (0x40 - 0x20)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  set = Set_GetCurrent();
  local_20[0] = 8.0;
  local_20[1] = 1.0;
  local_24 = CONCAT31(PIECE(local_24,1,3),10);
  local_28 = CONCAT31(PIECE(local_28,1,3),0x7f);
  local_20[2] = 1.5;
  if (set != (void *)0x0) {
    Set_GetSoundParams(set,local_20,(char *)&local_24,(char *)&local_28,local_20 + 2,local_20 + 1);
  }
  iVar2 = lua_lua2C(1);
  iVar3 = lua_isnumber(iVar2);
  if ((iVar3 == 0) && (iVar3 = lua_isstring(iVar2), iVar3 == 0)) {
    return;
  }
  iVar6 = 3;
  iVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(iVar3);
  if ((iVar4 == 0) || (iVar4 = lua_tag(iVar3), iVar4 != 0x52544341)) {
    iVar4 = lua_isnumber(iVar3);
    if (iVar4 != 0) {
      iVar4 = lua_lua2C(3);
      iVar6 = 5;
      iVar5 = lua_lua2C(4);
      local_c[0] = lua_getnumber(iVar3);
      local_c[1] = lua_getnumber(iVar4);
      local_c[2] = lua_getnumber(iVar5);
    }
  }
  else {
    iVar3 = lua_getuserdata(iVar3);
    iVar3 = Actor_FromHandle(iVar3);
    if (iVar3 == 0) {
      return;
    }
    local_c[0] = *(float *)(iVar3 + 0xc);
    local_c[1] = *(float *)(iVar3 + 0x10);
    local_c[2] = *(float *)(iVar3 + 0x14);
  }
  iVar3 = lua_lua2C(iVar6);
  iVar4 = lua_lua2C(iVar6 + 1);
  iVar6 = lua_lua2C(iVar6 + 2);
  iVar5 = lua_isnumber(iVar3);
  if (iVar5 != 0) {
    lVar7 = (longlong)lua_getnumber(iVar3);
    local_24 = CONCAT31(PIECE(local_24,1,3),(byte)lVar7);
    if (0x7f < (byte)lVar7) {
      local_24 = CONCAT31(PIECE(local_24,1,3),0x7f);
    }
  }
  iVar3 = lua_isnumber(iVar4);
  if (iVar3 != 0) {
    lVar7 = (longlong)lua_getnumber(iVar4);
    bVar1 = (byte)lVar7;
    local_28 = CONCAT31(PIECE(local_28,1,3),bVar1);
    if (bVar1 < 0x80) {
      if (bVar1 < (byte)local_24) {
        local_28 = CONCAT31(PIECE(local_28,1,3),(byte)local_24);
      }
    }
    else {
      local_28 = CONCAT31(PIECE(local_28,1,3),0x7f);
    }
  }
  iVar3 = lua_isnumber(iVar6);
  if ((iVar3 != 0) && (local_20[0] = lua_getnumber(iVar6), local_20[0] < 0.0)) {
    local_20[0] = 0.0;
  }
  iVar3 = lua_isnumber(iVar2);
  if (iVar3 == 0) {
    iVar2 = lua_getstring(iVar2);
  }
  else {
    lVar7 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar7;
  }
  Sound_SetPosition(iVar2,local_c,local_24 & 0xff,local_28 & 0xff,local_20[0],0x3f4ccccd);
  return;
}
#undef local_10
#undef local_14
#undef local_20
#undef local_24
#undef local_28
#undef local_c


/* ---- 0x0049e7e0  Lua_StartFullscreenMovie ---- */
/* Lua opcode: StartFullscreenMovie */

void Lua_StartFullscreenMovie(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isstring(iVar1);
  if (iVar3 != 0) {
    uVar7 = 0xffffffff;
    uVar6 = 0xffffffff;
    iVar2 = lua_isnil(iVar2);
    uVar5 = (uint)(iVar2 == 0);
    uVar4 = 1;
    iVar1 = lua_getstring(iVar1);
    iVar1 = Engine_BlitToBackBuffer(iVar1,uVar4,uVar5,uVar6,uVar7);
    if (iVar1 == 1) {
      lua_pushnumber(1.0);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0049e860  Lua_PauseMovie ---- */
/* Lua opcode: PauseMovie */

void Lua_PauseMovie(void)

{
  int iVar1;
  
  iVar1 = lua_lua2C(1);
  iVar1 = lua_isnil(iVar1);
  Movie_SetPaused(iVar1);
  return;
}

/* ---- 0x0049e880  Lua_StartMovie ---- */
/* Lua opcode: StartMovie */

void Lua_StartMovie(void)

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
    iVar1 = Engine_BlitToBackBuffer(iVar1,uVar9,uVar10,uVar6,uVar7);
    if (iVar1 == 1) {
      lua_pushnumber(1.0);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0049e960  Lua_IsMoviePlaying ---- */
/* Lua opcodes: IsFullscreenMoviePlaying, IsMoviePlaying
   also registered as IsFullscreenMoviePlaying */

void Lua_IsMoviePlaying(void)

{
  int iVar1;
  
  iVar1 = Movie_IsPlaying();
  if (iVar1 != 0) {
    lua_pushnumber(1.0);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0049e978. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lua_pushnil();
  return;
}

/* ---- 0x0049e980  Lua_FileFindFirst ---- */
/* Lua opcode: FileFindFirst */

void __fastcall Lua_FileFindFirst(char *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  char *ext;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isstring(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_isnil(iVar2);
    local_4 = (uint)param_1;
    if (iVar3 == 0) {
      local_4 = lua_getstring(iVar2);
    }
    ext = (char *)lua_getstring(iVar1);
    Lua_FileFindDispose();
    iVar1 = lua_isnil(iVar2);
    if (iVar1 != 0) {
      local_4 = (uint)&DAT_004f5a98;
    }
    g_pLuaFileFind = stdFileUtil_NewFind((char *)local_4,3,ext);
    if (g_pLuaFileFind != (void *)0x0) {
      Lua_FileFindNext();
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_4


/* ---- 0x0049ea20  Lua_FileFindNext ---- */
/* Lua opcode: FileFindNext */

void Lua_FileFindNext(void)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_10c (*(char (*)[260])(_frame + (0x120 - 0x10c)))
  #define local_8 (*(uint *)(_frame + (0x120 - 0x8)))
  
  iVar1 = 0;
  if (g_pLuaFileFind != (void *)0x0) {
    do {
      iVar1 = stdFileUtil_FindNext(g_pLuaFileFind,local_10c);
      if (iVar1 != 1) break;
    } while (local_8 != 0);
    if (local_8 != 0) {
      iVar1 = 0;
    }
  }
  if (iVar1 != 0) {
    lua_pushstring(local_10c);
    return;
  }
  lua_pushnil();
  return;
}
#undef local_10c
#undef local_8


/* ---- 0x0049ea90  Lua_FileFindDispose ---- */
/* Lua opcode: FileFindDispose */

void Lua_FileFindDispose(void)

{
  if (g_pLuaFileFind != (void *)0x0) {
    stdFileUtil_DisposeFind(g_pLuaFileFind);
    g_pLuaFileFind = (void *)0x0;
  }
  return;
}

/* ---- 0x0049eab0  Lua_QueryDialog ---- */
/* Lua opcode: QueryDialog */

void Lua_QueryDialog(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *text;
  char *caption;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_isstring(iVar1);
  if (iVar4 != 0) {
    iVar4 = lua_isstring(iVar2);
    if (iVar4 != 0) {
      text = (char *)lua_getstring(iVar1);
      caption = (char *)lua_getstring(iVar2);
      iVar1 = lua_isnil(iVar3);
      iVar1 = Plat_MessageBox(text,caption,(iVar1 != 0) + 3);
      if (iVar1 == 2) {
        lua_pushnumber(0.0);
        return;
      }
      if (iVar1 != 7) {
        lua_pushnumber(1.0);
        return;
      }
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0049eb60  Lua_InputDialog ---- */
/* Lua opcode: InputDialog */

void Lua_InputDialog(void)

{
  unsigned char _frame[0x80] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *title;
  char *prompt;
  char *defaultText;
  char *pcVar5;
  #define local_6c (*(uint *)(_frame + (0x80 - 0x6c)))
  #define local_68 (*(char (*)[104])(_frame + (0x80 - 0x68)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_isstring(iVar1);
  if (iVar4 != 0) {
    iVar4 = lua_isstring(iVar2);
    if (iVar4 != 0) {
      iVar4 = lua_isnil(iVar3);
      if (iVar4 == 0) {
        iVar4 = lua_isstring(iVar3);
        if (iVar4 == 0) goto LAB_0049ec38;
      }
      title = (char *)lua_getstring(iVar1);
      prompt = (char *)lua_getstring(iVar2);
      iVar1 = lua_isstring(iVar3);
      if (iVar1 == 0) {
        defaultText = (char *)0x0;
      }
      else {
        defaultText = (char *)lua_getstring(iVar3);
      }
      pcVar5 = local_68;
      for (iVar1 = 0x19; iVar1 != 0; iVar1 = iVar1 + -1) {
        pcVar5[0] = '\0';
        pcVar5[1] = '\0';
        pcVar5[2] = '\0';
        pcVar5[3] = '\0';
        pcVar5 = pcVar5 + 4;
      }
      *pcVar5 = '\0';
      iVar1 = Plat_InputDialog(title,prompt,local_68,0x65,defaultText);
      if (iVar1 != 0) {
        lua_pushstring(local_68);
        return;
      }
    }
  }
LAB_0049ec38:
  lua_pushnil();
  return;
}
#undef local_68
#undef local_6c


/* ---- 0x0049ec50  Lua_WriteRegistryValue ---- */
/* Lua opcode: WriteRegistryValue */

void Lua_WriteRegistryValue(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *name;
  char *value;
  float value_00;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(iVar1);
    iVar1 = lua_lua2C(2);
    iVar2 = lua_isstring(iVar1);
    if (iVar2 != 0) {
      value = (char *)lua_getstring(iVar1);
      Reg_SetString(name,value);
      return;
    }
    iVar2 = lua_isnumber(iVar1);
    if (iVar2 != 0) {
      value_00 = lua_getnumber(iVar1);
      Reg_SetFloat(name,value_00);
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049ece0  Lua_ReadRegistryValue ---- */
/* Lua opcode: ReadRegistryValue */

void Lua_ReadRegistryValue(void)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *name;
  float n;
  #define local_104 (*(uint *)(_frame + (0x120 - 0x104)))
  #define local_100 (*(char (*)[256])(_frame + (0x120 - 0x100)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(iVar1);
    iVar1 = Reg_GetValueType(name);
    if (iVar1 == 3) {
      n = Reg_GetFloat(name,0.0);
      lua_pushnumber(n);
      return;
    }
    if (iVar1 == 1) {
      Reg_GetString(name,local_100,0xff,&DAT_004f5a98);
      lua_pushstring(local_100);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_100
#undef local_104


/* ---- 0x0049ed90  Lua_GetSectorOppositeEdge ---- */
/* Lua opcode: GetSectorOppositeEdge */

void Lua_GetSectorOppositeEdge(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *name;
  void *a2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if ((iVar2 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      iVar2 = lua_lua2C(2);
      iVar3 = lua_isstring(iVar2);
      if (iVar3 != 0) {
        name = (char *)lua_getstring(iVar2);
        a2 = Sector_FindByName(name);
        if (a2 != (void *)0x0) {
          Actor_PushSectorOppositeEdge(iVar1,(int)a2);
          return;
        }
      }
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0049ee20  Lua_IsSectorActive ---- */
/* Lua opcode: IsSectorActive */

void Lua_IsSectorActive(void)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  char *name;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_0049eea2;
  }
  pvVar3 = Set_GetCurrent();
  if (pvVar3 != (void *)0x0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) {
      lVar4 = (longlong)lua_getnumber(iVar1);
      pvVar3 = Sector_FindById((int)lVar4);
    }
    else {
      name = (char *)lua_getstring(iVar1);
      pvVar3 = Sector_FindByName(name);
    }
    if ((pvVar3 != (void *)0x0) && (*(int *)((int)pvVar3 + 0x28) != 0)) {
      lua_pushnumber(1.0);
    }
  }
LAB_0049eea2:
  lua_pushnil();
  return;
}

/* ---- 0x0049eeb0  Lua_MakeSectorActive ---- */
/* Lua opcode: MakeSectorActive */

void Lua_MakeSectorActive(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *name;
  void *pvVar4;
  longlong lVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 == 0) && (iVar2 = lua_isstring(iVar1), iVar2 == 0)) {
    return;
  }
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isstring(iVar1);
  if (iVar3 == 0) {
    lVar5 = (longlong)lua_getnumber(iVar1);
    pvVar4 = Sector_FindById((int)lVar5);
  }
  else {
    name = (char *)lua_getstring(iVar1);
    pvVar4 = Sector_FindByName(name);
  }
  if (pvVar4 != (void *)0x0) {
    iVar1 = lua_isnil(iVar2);
    if (iVar1 != 0) {
      *(undefined4 *)((int)pvVar4 + 0x28) = 0;
      return;
    }
    *(undefined4 *)((int)pvVar4 + 0x28) = 1;
  }
  return;
}

/* ---- 0x0049ef50  Lua_PreRender ---- */
/* Lua opcode: PreRender */

void Lua_PreRender(void)

{
  int iVar1;
  int iVar2;
  uint redrawDepth;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar2 = lua_isnil(iVar2);
  redrawDepth = (uint)(iVar2 == 0);
  iVar1 = lua_isnil(iVar1);
  Render_InvalidateBackground((uint)(iVar1 == 0),redrawDepth);
  return;
}

/* ---- 0x0049efc0  Lua_GetCurrentScript ---- */
/* Lua opcode: GetCurrentScript */

void Lua_GetCurrentScript(void)

{
  int iVar1;
  
  iVar1 = lua_currenttask();
  lua_pushtask(iVar1);
  return;
}

/* ---- 0x0049efe0  Lua_LockFont ---- */
/* Lua opcode: LockFont */

void Lua_LockFont(void)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 == 0) {
    lua_pushnil();
    return;
  }
  pcVar3 = (char *)lua_getstring(iVar1);
  pcVar3 = Resource_Load(0x544e4f46,pcVar3);
  if (pcVar3 == (char *)0x0) {
    lua_pushnil();
    return;
  }
  lua_pushusertag(pcVar3,0x544e4f46);
  return;
}

/* ---- 0x0049f040  Lua_LoadCostume ---- */
/* Lua opcode: LoadCostume */

void Lua_LoadCostume(void)

{
  int iVar1;
  int iVar2;
  char *name;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 == 0) {
    lua_pushnil();
    return;
  }
  name = (char *)lua_getstring(iVar1);
  Resource_Load(0x54534f43,name);
  return;
}

/* ---- 0x0049f080  Lua_GetPhysicalBytes ---- */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: GetPhysicalBytes */

void __fastcall Lua_GetPhysicalBytes(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ((code *)Plat_GetPhysicalMemory)(param_1);
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x0049f0a0  Lua_SetMemoryUsage ---- */
/* Lua opcode: SetMemoryUsage */

void Lua_SetMemoryUsage(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  lVar3 = (longlong)lua_getnumber(iVar2);
  iVar2 = (int)lVar3;
  lVar3 = (longlong)lua_getnumber(iVar1);
  Resource_SetMemoryUsage((int)lVar3,iVar2);
  return;
}

/* ---- 0x0049f0f0  Lua_RotateVector ---- */
/* Lua opcode: RotateVector */

void Lua_RotateVector(void)

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
      Vec3_Rotate(local_18,local_c);
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


/* ---- 0x0049f2b0  Lua_GetCameraPosition ---- */
/* Lua opcode: GetCameraPosition */

void Lua_GetCameraPosition(void)

{
  if (g_pCameraSetup == (float *)0x0) {
    lua_pushnil();
  }
  lua_pushnumber(*g_pCameraSetup);
  lua_pushnumber(g_pCameraSetup[1]);
  lua_pushnumber(g_pCameraSetup[2]);
  return;
}

/* ---- 0x0049f300  Lua_GetCameraInterest ---- */
/* Lua opcode: GetCameraInterest */

void Lua_GetCameraInterest(void)

{
  if (g_pCameraSetup == (float *)0x0) {
    lua_pushnil();
  }
  lua_pushnumber(g_pCameraSetup[3]);
  lua_pushnumber(g_pCameraSetup[4]);
  lua_pushnumber(g_pCameraSetup[5]);
  return;
}

/* ---- 0x0049f350  Lua_GetCameraFOV ---- */
/* Lua opcode: GetCameraFOV */

void Lua_GetCameraFOV(void)

{
  if (g_pCameraSetup == (float *)0x0) {
    lua_pushnil();
  }
  lua_pushnumber(g_pCameraSetup[7]);
  return;
}

/* ---- 0x0049f380  Lua_GetCameraRoll ---- */
/* Lua opcode: GetCameraRoll */

void Lua_GetCameraRoll(void)

{
  if (g_pCameraSetup == (float *)0x0) {
    lua_pushnil();
  }
  lua_pushnumber(g_pCameraSetup[6]);
  return;
}

/* ---- 0x0049f3b0  Lua_SetCameraPosition ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: SetCameraPosition */

void Lua_SetCameraPosition(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  if (g_pCameraSetup == (float *)0x0) {
    lua_pushnil();
  }
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(1);
  iVar4 = lua_isnumber(iVar1);
  if (iVar4 != 0) {
    iVar4 = lua_isnumber(iVar2);
    if (iVar4 != 0) {
      iVar4 = lua_isnumber(iVar3);
      if (iVar4 != 0) goto LAB_0049f40e;
    }
  }
  lua_pushnil();
LAB_0049f40e:
  fVar5 = lua_getnumber(iVar1);
  *g_pCameraSetup = fVar5;
  fVar5 = lua_getnumber(iVar2);
  g_pCameraSetup[1] = fVar5;
  fVar5 = lua_getnumber(iVar3);
  g_pCameraSetup[2] = fVar5;
  Camera_BuildBasis(g_pCameraSetup + 0xc,g_pCameraSetup,g_pCameraSetup + 3,g_pCameraSetup[6]);
  rdCamera_SetFrame(g_pCameraSetup + 0xc);
  return;
}
#undef local_14


/* ---- 0x0049f480  Lua_SetCameraInterest ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: SetCameraInterest */

void Lua_SetCameraInterest(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  if (g_pCameraSetup == (float *)0x0) {
    lua_pushnil();
  }
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(1);
  iVar4 = lua_isnumber(iVar1);
  if (iVar4 != 0) {
    iVar4 = lua_isnumber(iVar2);
    if (iVar4 != 0) {
      iVar4 = lua_isnumber(iVar3);
      if (iVar4 != 0) goto LAB_0049f4de;
    }
  }
  lua_pushnil();
LAB_0049f4de:
  fVar5 = lua_getnumber(iVar1);
  g_pCameraSetup[3] = fVar5;
  fVar5 = lua_getnumber(iVar2);
  g_pCameraSetup[4] = fVar5;
  fVar5 = lua_getnumber(iVar3);
  g_pCameraSetup[5] = fVar5;
  Camera_BuildBasis(g_pCameraSetup + 0xc,g_pCameraSetup,g_pCameraSetup + 3,g_pCameraSetup[6]);
  rdCamera_SetFrame(g_pCameraSetup + 0xc);
  return;
}
#undef local_14


/* ---- 0x0049f550  Lua_SetActorScale ---- */
/* Lua opcode: SetActorScale */

void Lua_SetActorScale(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      iVar3 = lua_isnumber(iVar2);
      if (iVar3 != 0) {
        fVar4 = lua_getnumber(iVar2);
        *(float *)(iVar1 + 0x30) = fVar4;
        return;
      }
      *(undefined4 *)(iVar1 + 0x30) = 0x3f800000;
    }
  }
  return;
}

/* ---- 0x0049f5d0  Lua_SetActorTimeScale ---- */
/* Lua opcode: SetActorTimeScale */

void Lua_SetActorTimeScale(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      iVar3 = lua_isnumber(iVar2);
      if (iVar3 == 0) {
        fVar4 = 1.0;
      }
      else {
        fVar4 = lua_getnumber(iVar2);
      }
      *(float *)(*(int *)(iVar1 + 0xa4) + 0x41c) = fVar4;
      iVar1 = *(int *)(iVar1 + 0xa4);
      fVar4 = *(float *)(iVar1 + 0x41c);
      if (*(float *)(iVar1 + 0x41c) < 0.0) {
        fVar4 = -fVar4;
      }
      *(float *)(iVar1 + 0x41c) = fVar4;
    }
  }
  return;
}

/* ---- 0x0049f690  Lua_GetActorNodeLocation ---- */
/* Lua opcode: GetActorNodeLocation */

void Lua_GetActorNodeLocation(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  void *actor;
  float *pfVar4;
  uint index;
  float *frame;
  longlong lVar5;
  #define local_3c (*(float *)(_frame + (0x50 - 0x3c)))
  #define local_38 (*(float (*)[2])(_frame + (0x50 - 0x38)))
  #define local_30 (*(float (*)[9])(_frame + (0x50 - 0x30)))
  #define local_c (*(float (*)[3])(_frame + (0x50 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(iVar2);
      if (iVar3 != 0) {
        iVar1 = lua_getuserdata(iVar1);
        actor = (void *)Actor_FromHandle(iVar1);
        if ((*(int *)((int)actor + 0xa0) != 0) && (*(int *)(*(int *)((int)actor + 0xa0) + 4) != 0))
        {
          if (*(int *)((int)actor + 0x68) == 0) {
            pfVar4 = Actor_GetFrame(actor);
            rdPuppet_UpdateFrame(*(void **)(*(int *)((int)actor + 0xa0) + 4),pfVar4);
          }
          pfVar4 = local_30;
          lVar5 = (longlong)lua_getnumber(iVar2);
          index = (uint)lVar5;
          frame = Actor_GetFrame(actor);
          rdPuppet_BuildJointMatrices
                    (*(void **)(*(int *)((int)actor + 0xa0) + 4),frame,index,pfVar4);
          lVar5 = (longlong)lua_getnumber(iVar2);
          pfVar4 = (float *)(*(int *)(*(int *)(*(int *)(*(int *)((int)actor + 0xa0) + 4) + 4) + 0x58
                                     ) + 100 + (int)lVar5 * 0xb8);
          local_3c = *pfVar4;
          local_38[0] = pfVar4[1];
          local_38[1] = pfVar4[2];
          Vec3_Transform(&local_3c,local_30);
          local_3c = local_3c + local_c[0];
          local_38[0] = local_38[0] + local_c[1];
          local_38[1] = local_38[1] + local_c[2];
          lua_pushnumber(local_3c);
          lua_pushnumber(local_38[0]);
          lua_pushnumber(local_38[1]);
        }
      }
    }
  }
  return;
}
#undef local_30
#undef local_38
#undef local_3c
#undef local_c


/* ---- 0x0049f810  Lua_GetActorScale ---- */
/* Lua opcode: GetActorScale */

void Lua_GetActorScale(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      lua_pushnumber(*(float *)(iVar1 + 0x30));
    }
  }
  return;
}

/* ---- 0x0049f860  Lua_GetActorTimeScale ---- */
/* Lua opcode: GetActorTimeScale */

void Lua_GetActorTimeScale(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      lua_pushnumber(*(float *)(*(int *)(iVar1 + 0xa4) + 0x41c));
    }
  }
  return;
}

/* ---- 0x0049f8d0  Lua_SetCameraFOV ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetCameraFOV */

void Lua_SetCameraFOV(void)

{
  int iVar1;
  int iVar2;
  float fVar3;
  
  if (g_pCameraSetup == (float *)0x0) {
    lua_pushnil();
  }
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    lua_pushnil();
  }
  fVar3 = lua_getnumber(iVar1);
  g_pCameraSetup[7] = fVar3;
  *(float *)((int)g_pCameraSetup[10] + 0x38) = g_pCameraSetup[7];
  return;
}
#endif


/* ---- 0x0049f930  Lua_SetCameraRoll ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: SetCameraRoll */

void Lua_SetCameraRoll(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  if (g_pCameraSetup == (float *)0x0) {
    lua_pushnil();
  }
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    lua_pushnil();
  }
  fVar3 = lua_getnumber(iVar1);
  g_pCameraSetup[6] = fVar3;
  Camera_BuildBasis(g_pCameraSetup + 0xc,g_pCameraSetup,g_pCameraSetup + 3,g_pCameraSetup[6]);
  rdCamera_SetFrame(g_pCameraSetup + 0xc);
  return;
}
#undef local_c


/* ---- 0x0049f9b0  Lua_GetCameraLookVector ---- */
/* Lua opcode: GetCameraLookVector */

void Lua_GetCameraLookVector(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *pvVar2;
  int iVar3;
  longlong lVar4;
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float (*)[2])(_frame + (0x20 - 0x8)))
  
  iVar1 = lua_lua2C(1);
  pvVar2 = Set_GetCurrent();
  if (pvVar2 == (void *)0x0) {
    lua_pushnil();
    return;
  }
  iVar3 = lua_isnumber(iVar1);
  if (iVar3 == 0) {
    iVar1 = *(int *)((int)pvVar2 + 0xb4);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  iVar1 = iVar1 * 300;
  iVar3 = *(int *)((int)pvVar2 + 0xac) + 0x20 + iVar1;
  local_c = *(float *)(*(int *)((int)pvVar2 + 0xac) + 0x20 + iVar1) -
            *(float *)(*(int *)((int)pvVar2 + 0xac) + 0x2c + iVar1);
  local_8[0] = *(float *)(iVar3 + 4) - *(float *)(*(int *)((int)pvVar2 + 0xac) + 0x30 + iVar1);
  local_8[1] = *(float *)(iVar3 + 8) - *(float *)(*(int *)((int)pvVar2 + 0xac) + 0x34 + iVar1);
  Vec3_Normalize(&local_c);
  iVar1 = lua_createtable();
  lua_pushobject(iVar1);
  lua_pushstring(&DAT_004e8454);
  lua_pushnumber(local_c);
  lua_settable();
  lua_pushobject(iVar1);
  lua_pushstring(&DAT_004e8450);
  lua_pushnumber(local_8[0]);
  lua_settable();
  lua_pushobject(iVar1);
  lua_pushstring(&DAT_004ec3b8);
  lua_pushnumber(local_8[1]);
  lua_settable();
  lua_pushobject(iVar1);
  return;
}
#undef local_8
#undef local_c


/* ---- 0x0049fb00  Lua_PointActorAt ---- */
/* Lua opcode: PointActorAt(actor, x, y, z | actor). Creates the walker if missing, turns the walker
   heading all the way to the point (Walker_TurnToPoint with FLT_MAX) and negates the turn rate so
   Walker_UpdateYaw snaps the visible yaw next frame. Only the yaw changes; pitch and roll are not
   touched. */

void Lua_PointActorAt(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_isuserdata(iVar1);
  if (((iVar5 == 0) || (iVar5 = lua_tag(iVar1), iVar5 != 0x52544341)) || (iVar1 == 0)) {
    lua_pushnil();
    return;
  }
  iVar1 = lua_getuserdata(iVar1);
  iVar1 = Actor_FromHandle(iVar1);
  iVar5 = lua_isuserdata(iVar2);
  if ((iVar5 == 0) || (iVar5 = lua_tag(iVar2), iVar5 != 0x52544341)) {
    local_c[0] = lua_getnumber(iVar2);
    local_c[1] = lua_getnumber(iVar3);
    local_c[2] = lua_getnumber(iVar4);
  }
  else {
    iVar2 = lua_getuserdata(iVar2);
    iVar2 = Actor_FromHandle(iVar2);
    local_c[0] = *(float *)(iVar2 + 0xc);
    local_c[1] = *(float *)(iVar2 + 0x10);
    local_c[2] = *(float *)(iVar2 + 0x14);
  }
  if (*(int *)(*(int *)(iVar1 + 0xa4) + 0x1b4) == 0) {
    Actor_CreateWalker(iVar1,1);
  }
  Walker_TurnToPoint(*(void **)(*(int *)(iVar1 + 0xa4) + 0x1b4),local_c,3.4028235e+38);
  iVar1 = *(int *)(iVar1 + 0xa4);
  if (*(float *)(iVar1 + 0x1c) <= 0.0) {
    return;
  }
  *(float *)(iVar1 + 0x1c) = *(float *)(iVar1 + 0x1c) * -1.0;
  return;
}
#undef local_10
#undef local_14
#undef local_c


/* ---- 0x0049fc60  Lua_TurnActorTo ---- */
/* Lua opcode: TurnActorTo(actor, x, y, z | actor). Creates the walker if missing, turns the heading
   by at most |rate| * frameSeconds (no time scale) and returns TRUE while a whole step was taken
   (angle left >= step), nil once done. With a turn rate of 0 the step is 0 and it returns TRUE
   forever. */

void Lua_TurnActorTo(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_lua2C(3);
  iVar5 = lua_lua2C(4);
  iVar6 = lua_isuserdata(iVar2);
  if (iVar6 == 0) goto LAB_0049fde2;
  iVar6 = lua_tag(iVar2);
  if ((iVar6 != 0x52544341) || (iVar2 == 0)) goto LAB_0049fde2;
  iVar2 = lua_getuserdata(iVar2);
  iVar2 = Actor_FromHandle(iVar2);
  iVar6 = lua_isuserdata(iVar3);
  if (iVar6 == 0) {
LAB_0049fd1e:
    local_c[0] = lua_getnumber(iVar3);
    local_c[1] = lua_getnumber(iVar4);
    local_c[2] = lua_getnumber(iVar5);
  }
  else {
    iVar6 = lua_tag(iVar3);
    if (iVar6 != 0x52544341) goto LAB_0049fd1e;
    iVar3 = lua_getuserdata(iVar3);
    iVar3 = Actor_FromHandle(iVar3);
    local_c[0] = *(float *)(iVar3 + 0xc);
    local_c[1] = *(float *)(iVar3 + 0x10);
    local_c[2] = *(float *)(iVar3 + 0x14);
  }
  if (*(int *)(*(int *)(iVar2 + 0xa4) + 0x1b4) == 0) {
    Actor_CreateWalker(iVar2,1);
  }
  fVar1 = *(float *)(*(int *)(iVar2 + 0xa4) + 0x1c);
  if (*(float *)(*(int *)(iVar2 + 0xa4) + 0x1c) < 0.0) {
    fVar1 = -fVar1;
  }
  fVar7 = Timer_GetFrameSeconds();
  fVar8 = Walker_TurnToPoint(*(void **)(*(int *)(iVar2 + 0xa4) + 0x1b4),local_c,fVar7 * fVar1);
  if (fVar8 < 0.0) {
    fVar8 = -fVar8;
  }
  if (fVar7 * fVar1 <= fVar8) {
    lua_pushnumber(1.0);
    return;
  }
LAB_0049fde2:
  lua_pushnil();
  return;
}
#undef local_10
#undef local_14
#undef local_c


/* ---- 0x0049fdf0  Lua_PerSecond ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: PerSecond */

void Lua_PerSecond(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float fVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  if (lua_isnumber_exref == (code *)0x0) {
    lua_pushnil();
  }
  fVar2 = Timer_GetFrameSeconds();
  fVar3 = lua_getnumber(iVar1);
  lua_pushnumber(fVar3 * fVar2);
  return;
}
#undef local_4
#undef local_c


/* ---- 0x0049fe40  Lua_SnapToPlane ---- */
/* Lua opcode: SnapToPlane */

void Lua_SnapToPlane(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *name;
  void *this;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  name = (char *)lua_getstring(iVar1);
  this = Sector_FindByName(name);
  if (this == (void *)0x0) {
    lua_pushnil();
    return;
  }
  local_c[0] = lua_getnumber(iVar2);
  local_c[1] = lua_getnumber(iVar3);
  local_c[2] = lua_getnumber(iVar4);
  Sector_SnapToPlane(this,local_c);
  lua_pushnumber(local_c[0]);
  lua_pushnumber(local_c[1]);
  lua_pushnumber(local_c[2]);
  return;
}
#undef local_10
#undef local_c


/* ---- 0x0049ff00  Lua_GetAngleBetweenVectors ---- */
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Lua opcode: GetAngleBetweenVectors */

void Lua_GetAngleBetweenVectors(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_istable(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_istable(iVar2);
    if (iVar3 != 0) {
      lua_pushobject(iVar1);
      lua_pushstring(&DAT_004e8454);
      iVar3 = lua_gettable();
      local_c[0] = lua_getnumber(iVar3);
      lua_pushobject(iVar1);
      lua_pushstring(&DAT_004e8450);
      iVar3 = lua_gettable();
      local_c[1] = lua_getnumber(iVar3);
      lua_pushobject(iVar1);
      lua_pushstring(&DAT_004ec3b8);
      iVar1 = lua_gettable();
      local_c[2] = lua_getnumber(iVar1);
      lua_pushobject(iVar2);
      lua_pushstring(&DAT_004e8454);
      iVar1 = lua_gettable();
      local_18[0] = lua_getnumber(iVar1);
      lua_pushobject(iVar2);
      lua_pushstring(&DAT_004e8450);
      iVar1 = lua_gettable();
      local_18[1] = lua_getnumber(iVar1);
      lua_pushobject(iVar2);
      lua_pushstring(&DAT_004ec3b8);
      iVar1 = lua_gettable();
      local_18[2] = lua_getnumber(iVar1);
      Vec3_Normalize(local_c);
      Vec3_Normalize(local_18);
      fVar4 = Math_AsinDegreesSeries
                        (local_18[2] * local_c[2] +
                         local_18[1] * local_c[1] + local_18[0] * local_c[0]);
      lua_pushnumber(90.0 - fVar4);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_18
#undef local_1c
#undef local_30
#undef local_c


/* ---- 0x004a00a0  Lua_GetAngleBetweenActors ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Lua opcode: GetAngleBetweenActors */

void Lua_GetAngleBetweenActors(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x40 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isuserdata(iVar2);
      if (iVar3 != 0) {
        iVar3 = lua_tag(iVar2);
        if (iVar3 == 0x52544341) {
          iVar1 = lua_getuserdata(iVar1);
          iVar1 = Actor_FromHandle(iVar1);
          iVar2 = lua_getuserdata(iVar2);
          iVar2 = Actor_FromHandle(iVar2);
          if (((iVar1 != 0) && (iVar2 != 0)) &&
             (iVar3 = *(int *)(*(int *)(iVar1 + 0xa4) + 0x1b4), iVar3 != 0)) {
            local_c = *(float *)(iVar3 + 0x18);
            local_8 = *(float *)(iVar3 + 0x1c);
            local_4 = *(float *)(iVar3 + 0x20);
            local_18 = *(float *)(iVar2 + 0xc) - *(float *)(iVar1 + 0xc);
            local_14 = *(float *)(iVar2 + 0x10) - *(float *)(iVar1 + 0x10);
            local_10 = local_4 - *(float *)(iVar1 + 0x14);
            Vec3_Normalize(&local_c);
            Vec3_Normalize(&local_18);
            fVar4 = Math_AsinDegreesSeries
                              (local_10 * local_4 + local_14 * local_8 + local_18 * local_c);
            lua_pushnumber(90.0 - fVar4);
            return;
          }
        }
      }
    }
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_30
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a0230  Lua_SetAmbientLight ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: SetAmbientLight */

void Lua_SetAmbientLight(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *pvVar3;
  float ambient;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    pvVar3 = Set_GetCurrent();
    if (pvVar3 != (void *)0x0) {
      ambient = lua_getnumber(iVar1);
      rdCamera_SetAmbientLight
                (*(void **)(*(int *)((int)pvVar3 + 0xac) + 0x48 + *(int *)((int)pvVar3 + 0xb4) * 300
                           ),ambient);
    }
  }
  return;
}
#undef local_c

#endif


/* ---- 0x004a0290  Lua_FindLight ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: FindLight */

void Lua_FindLight(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *name;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(iVar1);
    iVar1 = Light_FindByName((void *)0x0,name);
    if (iVar1 != -1) {
      lua_pushnumber((float)iVar1);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_4
#undef local_c

#endif


/* ---- 0x004a02f0  Lua_TurnLightOn ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: TurnLightOn */

void Lua_TurnLightOn(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *name;
  void *pvVar4;
  longlong lVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(iVar1);
  if (iVar3 == 0) {
    iVar3 = lua_isstring(iVar1);
    if (iVar3 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar1);
    iVar1 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar5 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar5;
  }
  pvVar4 = Light_Get((void *)0x0,iVar1);
  if (pvVar4 != (void *)0x0) {
    iVar1 = lua_isnil(iVar2);
    *(uint *)((int)pvVar4 + 0x34) = (uint)(iVar1 == 0);
  }
  return;
}
#endif


/* ---- 0x004a0380  Lua_IsLightOn ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: IsLightOn */

void Lua_IsLightOn(void)

{
  int iVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_004a03f5;
    name = (char *)lua_getstring(iVar1);
    iVar1 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  pvVar3 = Light_Get((void *)0x0,iVar1);
  if ((pvVar3 != (void *)0x0) && (*(int *)((int)pvVar3 + 0x34) != 0)) {
    lua_pushnumber(1.0);
    return;
  }
LAB_004a03f5:
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a0400  Lua_SetLightType ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetLightType */

void Lua_SetLightType(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  int iVar5;
  char *name;
  void *pvVar6;
  uint uVar7;
  longlong lVar8;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  pvVar4 = Set_GetCurrent();
  iVar5 = lua_isnumber(iVar2);
  if (iVar5 == 0) {
    iVar5 = lua_isstring(iVar2);
    if (iVar5 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar2);
    iVar2 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar8 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar8;
  }
  pvVar6 = Light_Get((void *)0x0,iVar2);
  if (pvVar6 != (void *)0x0) {
    iVar5 = lua_isstring(iVar3);
    if (iVar5 != 0) {
      iVar3 = lua_getstring(iVar3);
      iVar5 = String_ContainsSubstring(iVar3,s_parallel_004ec5a8);
      if ((iVar5 == 0) && (iVar5 = String_ContainsSubstring(iVar3,s_global_004ec5a0), iVar5 == 0)) {
        iVar3 = String_ContainsSubstring(iVar3,&DAT_004ec598);
        if (iVar3 == 0) {
          *(undefined4 *)((int)pvVar6 + 0x30) = 2;
        }
        else {
          *(undefined4 *)((int)pvVar6 + 0x30) = 3;
        }
      }
      else {
        *(undefined4 *)((int)pvVar6 + 0x30) = 1;
      }
      uVar7 = 0;
      if (*(int *)((int)pvVar4 + 0xb0) != 0) {
        iVar3 = 0;
        do {
          uVar7 = uVar7 + 1;
          piVar1 = (int *)(*(int *)((int)pvVar4 + 0xac) + 0x48 + iVar3);
          iVar3 = iVar3 + 300;
          *(undefined4 *)(*(int *)(*piVar1 + iVar2 * 4 + 0x5c) + 4) =
               *(undefined4 *)((int)pvVar6 + 0x30);
        } while (uVar7 < *(uint *)((int)pvVar4 + 0xb0));
      }
      return;
    }
    return;
  }
  return;
}
#endif


/* ---- 0x004a0530  Lua_GetLightType ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: GetLightType */

void Lua_GetLightType(void)

{
  int iVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_004a05d0;
    name = (char *)lua_getstring(iVar1);
    iVar1 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  pvVar3 = Light_Get((void *)0x0,iVar1);
  if (pvVar3 != (void *)0x0) {
    iVar1 = *(int *)((int)pvVar3 + 0x30);
    if (iVar1 == 1) {
      lua_pushstring(s_parallel_004ec5a8);
      return;
    }
    if (iVar1 == 3) {
      lua_pushstring(&DAT_004ec598);
      return;
    }
    if (iVar1 == 2) {
      lua_pushstring(&DAT_004ec5b4);
      return;
    }
  }
LAB_004a05d0:
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a05e0  Lua_SetLightPosition ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetLightPosition */

void Lua_SetLightPosition(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *name;
  void *pvVar7;
  void *pvVar8;
  uint uVar9;
  float *pfVar10;
  longlong lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_lua2C(3);
  iVar5 = lua_lua2C(4);
  iVar6 = lua_isnumber(iVar2);
  if (iVar6 == 0) {
    iVar6 = lua_isstring(iVar2);
    if (iVar6 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar2);
    iVar2 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar11 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar11;
  }
  pvVar7 = Set_GetCurrent();
  if ((((pvVar7 != (void *)0x0) && (pvVar8 = Light_Get((void *)0x0,iVar2), pvVar8 != (void *)0x0))
      && (iVar6 = lua_isnumber(iVar3), iVar6 != 0)) &&
     ((iVar6 = lua_isnumber(iVar4), iVar6 != 0 && (iVar6 = lua_isnumber(iVar5), iVar6 != 0)))) {
    fVar12 = lua_getnumber(iVar3);
    fVar13 = lua_getnumber(iVar4);
    fVar14 = lua_getnumber(iVar5);
    *(float *)((int)pvVar8 + 0x20) = fVar12;
    *(float *)((int)pvVar8 + 0x24) = fVar13;
    *(float *)((int)pvVar8 + 0x28) = fVar14;
    uVar9 = 0;
    if (*(int *)((int)pvVar7 + 0xb0) != 0) {
      iVar3 = 0;
      do {
        piVar1 = (int *)(*(int *)((int)pvVar7 + 0xac) + 0x48 + iVar3);
        iVar3 = iVar3 + 300;
        pfVar10 = (float *)(*piVar1 + (iVar2 + 0x1d) * 0xc);
        uVar9 = uVar9 + 1;
        *pfVar10 = fVar12;
        pfVar10[1] = fVar13;
        pfVar10[2] = fVar14;
      } while (uVar9 < *(uint *)((int)pvVar7 + 0xb0));
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a0760  Lua_GetLightPosition ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: GetLightPosition */

void Lua_GetLightPosition(void)

{
  int iVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_004a07f0;
    name = (char *)lua_getstring(iVar1);
    iVar1 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  pvVar3 = Set_GetCurrent();
  if (pvVar3 != (void *)0x0) {
    pvVar3 = Light_Get((void *)0x0,iVar1);
    if (pvVar3 != (void *)0x0) {
      lua_pushnumber(*(float *)((int)pvVar3 + 0x20));
      lua_pushnumber(*(float *)((int)pvVar3 + 0x24));
      lua_pushnumber(*(float *)((int)pvVar3 + 0x28));
      return;
    }
  }
LAB_004a07f0:
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a0800  Lua_SetLightRotation ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetLightRotation */

void Lua_SetLightRotation(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  void *pvVar6;
  int iVar7;
  char *name;
  void *pvVar8;
  uint uVar9;
  longlong lVar10;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x40 - 0x4)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_lua2C(3);
  iVar5 = lua_lua2C(4);
  pvVar6 = Set_GetCurrent();
  iVar7 = lua_isnumber(iVar2);
  if (iVar7 == 0) {
    iVar7 = lua_isstring(iVar2);
    if (iVar7 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar2);
    iVar2 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar10 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar10;
  }
  pvVar8 = Light_Get((void *)0x0,iVar2);
  if (pvVar8 != (void *)0x0) {
    iVar7 = lua_isnumber(iVar3);
    if (iVar7 == 0) {
      local_c = 0.0;
    }
    else {
      local_c = lua_getnumber(iVar3);
    }
    iVar3 = lua_isnumber(iVar4);
    if (iVar3 == 0) {
      local_8 = 0.0;
    }
    else {
      local_8 = lua_getnumber(iVar4);
    }
    iVar3 = lua_isnumber(iVar5);
    if (iVar3 == 0) {
      local_4 = 0.0;
    }
    else {
      local_4 = lua_getnumber(iVar5);
    }
    local_18 = 0.0;
    local_14 = 0x3f800000;
    local_10 = 0;
    Vec3_Rotate(&local_18,&local_c);
    *(float *)((int)pvVar8 + 0x38) = local_18;
    *(uint *)((int)pvVar8 + 0x3c) = local_14;
    uVar9 = 0;
    *(uint *)((int)pvVar8 + 0x40) = local_10;
    if (*(int *)((int)pvVar6 + 0xb0) != 0) {
      iVar3 = 0;
      do {
        piVar1 = (int *)(*(int *)((int)pvVar6 + 0xac) + 0x48 + iVar3);
        iVar3 = iVar3 + 300;
        iVar4 = *(int *)(*piVar1 + iVar2 * 4 + 0x5c);
        uVar9 = uVar9 + 1;
        *(float *)(iVar4 + 0xc) = local_18;
        *(uint *)(iVar4 + 0x10) = local_14;
        *(uint *)(iVar4 + 0x14) = local_10;
      } while (uVar9 < *(uint *)((int)pvVar6 + 0xb0));
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a09a0  Lua_GetLightRotation ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetLightRotation */

void Lua_GetLightRotation(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  longlong lVar4;
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_004a0a3b;
    name = (char *)lua_getstring(iVar1);
    iVar1 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  pvVar3 = Light_Get((void *)0x0,iVar1);
  if (pvVar3 != (void *)0x0) {
    Matrix_GetAngles((float *)((int)pvVar3 + 0x38),&local_c);
    lua_pushnumber(local_c);
    lua_pushnumber(local_8);
    lua_pushnumber(local_4);
    return;
  }
LAB_004a0a3b:
  lua_pushnil();
  return;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a0a50  Lua_SetLightAngles ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetLightAngles */

void Lua_SetLightAngles(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *name;
  void *pvVar5;
  longlong lVar6;
  #define local_8 (*(float *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_isnumber(iVar1);
  if (iVar4 == 0) {
    iVar4 = lua_isstring(iVar1);
    if (iVar4 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar1);
    iVar1 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar6 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar6;
  }
  pvVar5 = Light_Get((void *)0x0,iVar1);
  if (pvVar5 != (void *)0x0) {
    iVar1 = lua_isnumber(iVar2);
    if (iVar1 == 0) {
      local_4 = 0.0;
    }
    else {
      local_4 = lua_getnumber(iVar2);
    }
    iVar1 = lua_isnumber(iVar3);
    if (iVar1 == 0) {
      local_8 = 0.0;
    }
    else {
      local_8 = lua_getnumber(iVar3);
    }
    rdLight_SetAngles((void *)((int)pvVar5 + 0x2c),local_4,local_8);
  }
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a0b40  Lua_GetLightAngles ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: GetLightAngles */

void Lua_GetLightAngles(void)

{
  int iVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_004a0bbc;
    name = (char *)lua_getstring(iVar1);
    iVar1 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  pvVar3 = Light_Get((void *)0x0,iVar1);
  if (pvVar3 != (void *)0x0) {
    lua_pushnumber(*(float *)((int)pvVar3 + 0x4c));
    lua_pushnumber(*(float *)((int)pvVar3 + 0x54));
    return;
  }
LAB_004a0bbc:
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a0bd0  Lua_PointLightAt ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: PointLightAt */

void Lua_PointLightAt(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *name;
  void *pvVar6;
  longlong lVar7;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_isnumber(iVar1);
  if (iVar5 == 0) {
    iVar5 = lua_isstring(iVar1);
    if (iVar5 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar1);
    iVar1 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar7 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar7;
  }
  pvVar6 = Light_Get((void *)0x0,iVar1);
  if (pvVar6 != (void *)0x0) {
    iVar1 = lua_isuserdata(iVar2);
    if (((iVar1 == 0) || (iVar1 = lua_tag(iVar2), iVar1 != 0x52544341)) &&
       (iVar1 = lua_isnumber(iVar2), iVar1 == 0)) {
      return;
    }
    iVar1 = lua_isuserdata(iVar2);
    if ((iVar1 == 0) || (iVar1 = lua_tag(iVar2), iVar1 != 0x52544341)) {
      local_18 = lua_getnumber(iVar2);
      iVar1 = lua_isnumber(iVar3);
      if (iVar1 == 0) {
        local_14 = 0.0;
      }
      else {
        local_14 = lua_getnumber(iVar3);
      }
      iVar1 = lua_isnumber(iVar4);
      if (iVar1 == 0) {
        local_10 = 0.0;
      }
      else {
        local_10 = lua_getnumber(iVar4);
      }
    }
    else {
      iVar1 = lua_getuserdata(iVar2);
      iVar1 = Actor_FromHandle(iVar1);
      local_18 = *(float *)(iVar1 + 0xc);
      local_14 = *(float *)(iVar1 + 0x10);
      local_10 = *(float *)(iVar1 + 0x14);
    }
    local_c = local_18 - *(float *)((int)pvVar6 + 0x20);
    local_8 = local_14 - *(float *)((int)pvVar6 + 0x24);
    local_4 = local_10 - *(float *)((int)pvVar6 + 0x28);
    Vec3_Normalize(&local_c);
    *(float *)((int)pvVar6 + 0x38) = local_c;
    *(float *)((int)pvVar6 + 0x3c) = local_8;
    *(float *)((int)pvVar6 + 0x40) = local_4;
    return;
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a0da0  Lua_SetLightIntensity ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetLightIntensity */

void Lua_SetLightIntensity(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  int iVar5;
  char *name;
  void *pvVar6;
  uint uVar7;
  longlong lVar8;
  float fVar9;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  pvVar4 = Set_GetCurrent();
  iVar5 = lua_isnumber(iVar2);
  if (iVar5 == 0) {
    iVar5 = lua_isstring(iVar2);
    if (iVar5 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar2);
    iVar2 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar8 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar8;
  }
  pvVar6 = Light_Get((void *)0x0,iVar2);
  if ((pvVar6 != (void *)0x0) && (iVar5 = lua_isnumber(iVar3), iVar5 != 0)) {
    fVar9 = lua_getnumber(iVar3);
    *(float *)((int)pvVar6 + 0x44) = fVar9;
    uVar7 = 0;
    if (*(int *)((int)pvVar4 + 0xb0) != 0) {
      iVar5 = 0;
      do {
        fVar9 = lua_getnumber(iVar3);
        uVar7 = uVar7 + 1;
        piVar1 = (int *)(*(int *)((int)pvVar4 + 0xac) + 0x48 + iVar5);
        iVar5 = iVar5 + 300;
        *(float *)(*(int *)(*piVar1 + iVar2 * 4 + 0x5c) + 0x18) = fVar9;
      } while (uVar7 < *(uint *)((int)pvVar4 + 0xb0));
    }
  }
  return;
}
#undef local_4

#endif


/* ---- 0x004a0e90  Lua_GetLightIntensity ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: GetLightIntensity */

void Lua_GetLightIntensity(void)

{
  int iVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  lua_lua2C(2);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_004a0f08;
    name = (char *)lua_getstring(iVar1);
    iVar1 = Light_FindByName((void *)0x0,name);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  pvVar3 = Light_Get((void *)0x0,iVar1);
  if (pvVar3 != (void *)0x0) {
    lua_pushnumber(*(float *)((int)pvVar3 + 0x44));
    return;
  }
LAB_004a0f08:
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a0f20  Lua_ImStartRecording ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: ImStartRecording */

void Lua_ImStartRecording(void)

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
#endif


/* ---- 0x004a0f80  Lua_ImStartSound ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_18 */
/* Lua opcodes: ImStartSound, play
   also registered as `play` */

void Lua_ImStartSound(void)

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

#endif


/* ---- 0x004a1030  Lua_ImStopSound ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImStopSound */

void Lua_ImStopSound(void)

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
#endif


/* ---- 0x004a1090  Lua_ImGetParam ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: ImGetParam */

void Lua_ImGetParam(void)

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

#endif


/* ---- 0x004a1140  Lua_ImSetParam ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: ImSetParam */

void Lua_ImSetParam(void)

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
#endif


/* ---- 0x004a1260  Lua_ImFadeParam ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: ImFadeParam */

void Lua_ImFadeParam(void)

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

#endif


/* ---- 0x004a13d0  Lua_ImGetMasterVol ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ImGetMasterVol */

void __fastcall Lua_ImGetMasterVol(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ImSetGroupVol(0,0xffffffff);
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a1400  Lua_ImSetMasterVol ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetMasterVol */

void Lua_ImSetMasterVol(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    ImSetGroupVol(0,(uint)lVar3);
  }
  return;
}
#endif


/* ---- 0x004a1440  Lua_ImGetSfxVol ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ImGetSfxVol */

void __fastcall Lua_ImGetSfxVol(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ImSetGroupVol(1,0xffffffff);
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a1470  Lua_ImSetSfxVol ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetSfxVol */

void Lua_ImSetSfxVol(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    ImSetGroupVol(1,(uint)lVar3);
  }
  return;
}
#endif


/* ---- 0x004a14b0  Lua_ImGetVoiceVol ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ImGetVoiceVol */

void __fastcall Lua_ImGetVoiceVol(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ImSetGroupVol(2,0xffffffff);
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a14e0  Lua_ImSetVoiceVol ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetVoiceVol */

void Lua_ImSetVoiceVol(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    ImSetGroupVol(2,(uint)lVar3);
  }
  return;
}
#endif


/* ---- 0x004a1520  Lua_ImGetMusicVol ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ImGetMusicVol */

void __fastcall Lua_ImGetMusicVol(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ImSetGroupVol(3,0xffffffff);
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a1550  Lua_ImSetMusicVol ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetMusicVol */

void Lua_ImSetMusicVol(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    ImSetGroupVol(3,(uint)lVar3);
  }
  return;
}
#endif


/* ---- 0x004a1590  Lua_ImStartVoice ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: ImStartVoice */

void Lua_ImStartVoice(void)

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
#endif


/* ---- 0x004a1640  Lua_ImSetState ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetState */

void Lua_ImSetState(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    Engine_SetIMuseState((int)lVar3);
  }
  return;
}
#endif


/* ---- 0x004a1680  Lua_ImSetSequence ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_c */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Lua opcode: ImSetSequence */

void __fastcall Lua_ImSetSequence(undefined4 param_1)

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

#endif


/* ---- 0x004a16d0  Lua_ImSetCuePoint ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetCuePoint */

void Lua_ImSetCuePoint(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    ImSetCuePoint((int)lVar3);
  }
  return;
}
#endif


/* ---- 0x004a1710  Lua_ImSetAttribute ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: ImSetAttribute */

void Lua_ImSetAttribute(void)

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

#endif


/* ---- 0x004a17b0  Lua_ImSetVoiceEffect ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcodes: vfx, ImSetVoiceEffect
   also registered as `vfx` */

void Lua_ImSetVoiceEffect(void)

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
#endif


/* ---- 0x004a17f0  Lua_ImGetMemoryFootprint ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: ImGetMemoryFootprint */

void Lua_ImGetMemoryFootprint(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  uVar1 = iMUSE_GetMemoryFootprint();
  lua_pushnumber((float)uVar1);
  return;
}
#undef local_c

#endif


/* ---- 0x004a1820  Lua_ImGetSoundCacheSize ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: ImGetSoundCacheSize */

void Lua_ImGetSoundCacheSize(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  uVar1 = iMUSE_GetSoundCacheSize();
  lua_pushnumber((float)uVar1);
  return;
}
#undef local_c

#endif


/* ---- 0x004a1850  Lua_SetGamma ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: SetGamma */

void Lua_SetGamma(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float gamma;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (UINT_008a8c40 != 4)) {
    gamma = lua_getnumber(iVar1);
    Render_SetGamma(gamma);
  }
  return;
}
#undef local_8

#endif


/* ---- 0x004a1890  Lua_SetActorWalkDominate ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetActorWalkDominate */

void Lua_SetActorWalkDominate(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  void *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar2 = lua_isnil(iVar2);
      iVar1 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(iVar1);
      Actor_SetWalkDominate(actor,iVar2);
    }
  }
  return;
}
#endif


/* ---- 0x004a1900  Lua_SetActorConstrain ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetActorConstrain */

void Lua_SetActorConstrain(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar2 = lua_isnil(iVar2);
      iVar1 = lua_getuserdata(iVar1);
      uVar4 = Actor_FromHandle(iVar1);
      Actor_SetConstrain(uVar4,iVar2 == 0);
    }
  }
  return;
}
#endif


/* ---- 0x004a1970  Lua_RenderModeUser ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: RenderModeUser */

void Lua_RenderModeUser(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if ((iVar2 != 0) && (UINT_008a8c40 == 4)) {
    Movie_SetPaused(0);
    Render_RequestFullRedraw();
    UINT_008a8c40 = Engine_GetSavedValue();
    return;
  }
  iVar1 = lua_isnil(iVar1);
  if ((iVar1 == 0) && (UINT_008a8c40 != 4)) {
    Engine_SetSavedValue(UINT_008a8c40);
    Movie_SetPaused(1);
    UINT_008a8c40 = 4;
  }
  return;
}
#endif


/* ---- 0x004a19f0  Lua_DimScreen ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: DimScreen */

void Lua_DimScreen(void)

{
  Render_DimBackground(0,2);
  return;
}
#endif


/* ---- 0x004a1a00  Lua_DimRegion ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_28 */
/* WARNING: Variable defined which should be unmapped: local_38 */
/* WARNING: Variable defined which should be unmapped: local_34 */
/* WARNING: Variable defined which should be unmapped: local_30 */
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: DimRegion */

void Lua_DimRegion(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float unaff_ESI;
  float unaff_EDI;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  longlong lVar9;
  float r;
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_4 (*(uint *)(_frame + (0x50 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  lVar6 = (longlong)lua_getnumber(iVar1);
  lVar7 = (longlong)lua_getnumber(iVar2);
  lVar8 = (longlong)lua_getnumber(iVar3);
  lVar9 = (longlong)lua_getnumber(iVar4);
  r = lua_getnumber(iVar5);
  Render_FillRect((int)lVar6,(int)lVar7,(int)lVar8,(int)lVar9,r,unaff_EDI,unaff_ESI);
  return;
}
#undef local_14
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_4

#endif


/* ---- 0x004a1ae0  Lua_SetSpeechMode ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: SetSpeechMode */

void Lua_SetSpeechMode(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar3;
    if (iVar1 == 1) {
      Speech_SetMode(1);
    }
    else {
      if (iVar1 == 2) {
        Speech_SetMode(2);
        return;
      }
      if (iVar1 == 3) {
        Speech_SetMode(3);
        return;
      }
    }
  }
  return;
}
#endif


/* ---- 0x004a1b40  Lua_GetSpeechMode ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: GetSpeechMode */

void Lua_GetSpeechMode(void)

{
  byte bVar1;
  
  bVar1 = Speech_GetMode();
  if ((bVar1 & 2) == 0) {
    if ((bVar1 & 1) != 0) {
      lua_pushnumber(1.0);
      return;
    }
  }
  else if ((bVar1 & 1) != 0) {
    lua_pushnumber(3.0);
    return;
  }
  lua_pushnumber(2.0);
  return;
}
#endif


/* ---- 0x004a1b80  Lua_ActorShadow ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: ActorShadow */

void Lua_ActorShadow(void)

{
  int iVar1;
  int iVar2;
  void *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if ((iVar2 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(iVar1);
      iVar1 = Actor_HasShadow(actor);
      if (iVar1 != 0) {
        lua_pushnumber(1.0);
        return;
      }
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a1bf0  Lua_ActivateActorShadow ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: ActivateActorShadow */

void Lua_ActivateActorShadow(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *actor;
  longlong lVar5;
  uint active;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_isuserdata(iVar1);
  if (iVar4 != 0) {
    iVar4 = lua_tag(iVar1);
    if ((iVar4 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(iVar1);
      iVar1 = lua_isnil(iVar3);
      active = (uint)(iVar1 == 0);
      lVar5 = (longlong)lua_getnumber(iVar2);
      Actor_ActivateShadow(actor,(int)lVar5,active);
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a1c90  Lua_SetActorShadowPlane ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetActorShadowPlane */

void Lua_SetActorShadowPlane(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      uVar4 = Actor_FromHandle(iVar1);
      iVar1 = lua_getstring(iVar2);
      Actor_SetShadowPlane(uVar4,iVar1);
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a1d10  Lua_SetActorShadowPoint ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_18 */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: SetActorShadowPoint */

void Lua_SetActorShadowPoint(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  void *actor;
  float z;
  float y;
  float x;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_isuserdata(iVar1);
  if (iVar5 != 0) {
    iVar5 = lua_tag(iVar1);
    if ((iVar5 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(iVar1);
      z = lua_getnumber(iVar4);
      y = lua_getnumber(iVar3);
      x = lua_getnumber(iVar2);
      Actor_SetShadowPoint(actor,x,y,z);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_4

#endif


/* ---- 0x004a1dc0  Lua_SetActiveShadow ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetActiveShadow */

void Lua_SetActiveShadow(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      lVar4 = (longlong)lua_getnumber(iVar2);
      *(int *)(*(int *)(iVar1 + 0xa4) + 500) = (int)lVar4;
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a1e50  Lua_ActorDistToShadowPlane ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: ActorDistToShadowPlane */

void Lua_ActorDistToShadowPlane(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float n;
  int iVar3;
  int iVar4;
  longlong lVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar3 = lua_lua2C(1);
  iVar4 = lua_lua2C(2);
  lVar5 = (longlong)lua_getnumber(iVar4);
  iVar4 = lua_isuserdata(iVar3);
  if (iVar4 != 0) {
    iVar4 = lua_tag(iVar3);
    if ((iVar4 == 0x52544341) && (iVar3 != 0)) {
      iVar3 = lua_getuserdata(iVar3);
      iVar3 = Actor_FromHandle(iVar3);
      if (*(int *)(iVar3 + 0xa4) == 0) {
        Actor_CreateExtra(iVar3);
      }
      iVar4 = (int)lVar5 + 6;
      iVar2 = *(int *)(iVar3 + 0xa4);
      iVar1 = iVar2 + iVar4 * 0x54;
      n = *(float *)(iVar3 + 0x10) * *(float *)(iVar1 + 0xc) +
          *(float *)(iVar2 + 0x10 + iVar4 * 0x54) * *(float *)(iVar3 + 0x14) +
          *(float *)(iVar2 + 8 + iVar4 * 0x54) * *(float *)(iVar3 + 0xc) + *(float *)(iVar1 + 0x14);
      if (n < 0.0) {
        n = -n;
      }
      lua_pushnumber(n);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_4

#endif


/* ---- 0x004a1f30  Lua_AddShadowPlane ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: AddShadowPlane */

void Lua_AddShadowPlane(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  void *actor;
  char *sectorName;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(iVar1);
      if (*(int *)((int)actor + 0xa4) == 0) {
        Actor_CreateExtra(actor);
      }
      sectorName = (char *)lua_getstring(iVar2);
      Actor_AddShadowPlane(actor,*(int *)(*(int *)((int)actor + 0xa4) + 500),sectorName);
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a1fd0  Lua_SetActorShadowValid ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetActorShadowValid */

void Lua_SetActorShadowValid(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  void *actor;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(iVar1);
      if (*(int *)((int)actor + 0xa4) == 0) {
        Actor_CreateExtra(actor);
      }
      lVar4 = (longlong)lua_getnumber(iVar2);
      Actor_SetShadowValid(actor,*(int *)(*(int *)((int)actor + 0xa4) + 500),(int)lVar4);
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a2070  Lua_KillActorShadows ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: KillActorShadows */

void Lua_KillActorShadows(void)

{
  int iVar1;
  int iVar2;
  void *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if ((iVar2 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(iVar1);
      Actor_KillShadows(actor);
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a20d0  Lua_SetShadowColor ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetShadowColor */

void Lua_SetShadowColor(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  lVar4 = (longlong)lua_getnumber(iVar3);
  iVar3 = (int)lVar4;
  lVar4 = (longlong)lua_getnumber(iVar2);
  iVar2 = (int)lVar4;
  lVar4 = (longlong)lua_getnumber(iVar1);
  Shadow_SetColor((int)lVar4,iVar2,iVar3);
  return;
}
#endif


/* ---- 0x004a2130  Lua_NewObjectState ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: NewObjectState */

void Lua_NewObjectState(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *bitmap;
  int visible;
  longlong lVar8;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  visible = -1;
  iVar6 = lua_isnil(iVar5);
  if (iVar6 == 0) {
    lVar8 = (longlong)lua_getnumber(iVar5);
    visible = (int)lVar8;
  }
  pcVar7 = (char *)lua_getstring(iVar4);
  bitmap = (char *)lua_getstring(iVar3);
  lVar8 = (longlong)lua_getnumber(iVar2);
  iVar2 = (int)lVar8;
  lVar8 = (longlong)lua_getnumber(iVar1);
  pcVar7 = ObjectState_Create((int)lVar8,iVar2,bitmap,pcVar7,visible);
  lua_pushusertag(pcVar7,0x54415453);
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a21f0  Lua_FreeObjectState ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: FreeObjectState */

void Lua_FreeObjectState(void)

{
  int iVar1;
  int iVar2;
  void *state;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x54415453) {
      state = (void *)lua_getuserdata(iVar1);
      if (state != (void *)0x0) {
        ObjectState_Free(state);
      }
    }
  }
  return;
}
#endif


/* ---- 0x004a2240  Lua_SendObjectToBack ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SendObjectToBack */

void Lua_SendObjectToBack(void)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  void *pvVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x54415453) {
      pvVar3 = (void *)lua_getuserdata(iVar1);
      if (pvVar3 != (void *)0x0) {
        iVar1 = *(int *)((int)pvVar3 + 8);
        pvVar4 = Set_GetCurrent();
        iVar2 = *(int *)((int)pvVar4 + 0xac);
        pvVar3 = ObjectState_SendToBack(pvVar3,*(void **)(iVar2 + 0x128 + iVar1 * 300));
        *(void **)(iVar2 + iVar1 * 300 + 0x128) = pvVar3;
      }
    }
  }
  return;
}
#endif


/* ---- 0x004a22b0  Lua_SendObjectToFront ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SendObjectToFront */

void Lua_SendObjectToFront(void)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  void *pvVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x54415453) {
      pvVar3 = (void *)lua_getuserdata(iVar1);
      if (pvVar3 != (void *)0x0) {
        iVar1 = *(int *)((int)pvVar3 + 8);
        pvVar4 = Set_GetCurrent();
        iVar2 = *(int *)((int)pvVar4 + 0xac);
        pvVar3 = ObjectState_SendToFront(pvVar3,*(void **)(iVar2 + 0x128 + iVar1 * 300));
        *(void **)(iVar2 + iVar1 * 300 + 0x128) = pvVar3;
      }
    }
  }
  return;
}
#endif


/* ---- 0x004a2320  Lua_SetObjectType ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetObjectType */

void Lua_SetObjectType(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x54415453) {
      iVar1 = lua_getuserdata(iVar1);
      if (iVar1 != 0) {
        lVar4 = (longlong)lua_getnumber(iVar2);
        *(int *)(iVar1 + 4) = (int)lVar4;
      }
    }
  }
  return;
}
#endif


/* ---- 0x004a2380  Lua_ActorToClean ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: ActorToClean */

void Lua_ActorToClean(void)

{
  int iVar1;
  int iVar2;
  void *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if ((iVar2 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(iVar1);
      Actor_ToClean(actor);
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a23e0  Lua_SetActorCollisionMode ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetActorCollisionMode */

void Lua_SetActorCollisionMode(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      lVar4 = (longlong)lua_getnumber(iVar2);
      *(int *)(*(int *)(iVar1 + 0xa4) + 0x3f0) = (int)lVar4;
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a2470  Lua_SetActorCollisionScale ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetActorCollisionScale */

void Lua_SetActorCollisionScale(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      fVar4 = lua_getnumber(iVar2);
      *(float *)(*(int *)(iVar1 + 0xa4) + 0x3f4) = fVar4;
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a2500  Lua_SetActorOffsetYaw ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetActorOffsetYaw */

void Lua_SetActorOffsetYaw(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      fVar4 = lua_getnumber(iVar2);
      *(float *)(*(int *)(iVar1 + 0xa4) + 0x24) = fVar4;
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a2590  Lua_CacheRect ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_18 */
/* WARNING: Variable defined which should be unmapped: local_24 */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* Lua opcode: CacheRect */

void Lua_CacheRect(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  longlong lVar7;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_isuserdata(iVar1);
  if (iVar5 != 0) {
    iVar5 = lua_tag(iVar1);
    if (iVar5 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (((*(int *)(iVar1 + 0x68) == 0) || (*(int *)(iVar1 + 0x74) < 1)) ||
         (*(int *)(iVar1 + 0x78) < 1)) {
        lua_pushnil();
        return;
      }
      local_24 = *(uint *)(iVar1 + 0x6c);
      local_20 = *(uint *)(iVar1 + 0x70);
      local_1c = *(uint *)(iVar1 + 0x74);
      local_18 = *(uint *)(iVar1 + 0x78);
      goto LAB_004a268a;
    }
  }
  lVar7 = (longlong)lua_getnumber(iVar1);
  local_24 = (uint)lVar7;
  lVar7 = (longlong)lua_getnumber(iVar2);
  local_20 = (uint)lVar7;
  lVar7 = (longlong)lua_getnumber(iVar3);
  local_1c = (uint)lVar7;
  lVar7 = (longlong)lua_getnumber(iVar4);
  local_18 = (uint)lVar7;
LAB_004a268a:
  pcVar6 = CacheRect_Create(local_24,local_20,local_1c,local_18);
  lua_pushusertag(pcVar6,0x504f494e);
  return;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_4

#endif


/* ---- 0x004a26b0  Lua_RestoreCacheRect ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: RestoreCacheRect */

void Lua_RestoreCacheRect(void)

{
  int iVar1;
  int *piVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  piVar2 = (int *)lua_getuserdata(iVar1);
  if ((piVar2 != (int *)0x0) && (*piVar2 == 0x11111111)) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    ((code *)CacheRect_Restore)((int)lVar3,unaff_ESI);
  }
  return;
}
#endif


/* ---- 0x004a26f0  Lua_ResReport ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_4 */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ResReport */

void __fastcall Lua_ResReport(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  ((code *)Res_PrintReport)(param_1);
  iVar1 = Res_GetMemoryUsed();
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a2720  Lua_HardwareAccelerated ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: HardwareAccelerated */

void Lua_HardwareAccelerated(void)

{
  if (g_nZBufferEnabled != 0) {
    lua_pushnumber(1.0);
    return;
  }
  lua_pushnumber(0.0);
  return;
}
#endif


/* ---- 0x004a2750  Lua_SetActorClipActive ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetActorClipActive */

void Lua_SetActorClipActive(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar1 = lua_getuserdata(iVar1);
  iVar1 = Actor_FromHandle(iVar1);
  if (iVar1 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar2);
    Actor_SetClipActive(iVar1,(int)lVar3);
  }
  return;
}
#endif


/* ---- 0x004a27b0  Lua_SetActorClipPlane ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetActorClipPlane */

void Lua_SetActorClipPlane(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x40 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  iVar6 = lua_lua2C(6);
  iVar7 = lua_lua2C(7);
  iVar1 = lua_getuserdata(iVar1);
  iVar1 = Actor_FromHandle(iVar1);
  if (iVar1 != 0) {
    iVar8 = lua_isnumber(iVar2);
    if (iVar8 != 0) {
      iVar8 = lua_isnumber(iVar3);
      if (iVar8 != 0) {
        iVar8 = lua_isnumber(iVar4);
        if (iVar8 != 0) {
          iVar8 = lua_isnumber(iVar5);
          if (iVar8 != 0) {
            iVar8 = lua_isnumber(iVar6);
            if (iVar8 != 0) {
              iVar8 = lua_isnumber(iVar7);
              if (iVar8 != 0) {
                local_18 = lua_getnumber(iVar2);
                local_14 = lua_getnumber(iVar3);
                local_10 = lua_getnumber(iVar4);
                Vec3_Normalize(&local_18);
                local_c = lua_getnumber(iVar5);
                local_8 = lua_getnumber(iVar6);
                local_4 = lua_getnumber(iVar7);
                Actor_SetClipPlane(iVar1,&local_18,&local_c);
              }
            }
          }
        }
      }
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a2920  Lua_MarkDirtyRect ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: MarkDirtyRect */

void Lua_MarkDirtyRect(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_isuserdata(iVar1);
  if (iVar5 != 0) {
    iVar5 = lua_tag(iVar1);
    if (iVar5 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (((*(int *)(iVar1 + 0x68) != 0) && (0 < *(int *)(iVar1 + 0x74))) &&
         (0 < *(int *)(iVar1 + 0x78))) {
        Render_InvalidateRectLastBuffer((int *)(iVar1 + 0x6c),1);
        return;
      }
      lua_pushnil();
      return;
    }
  }
  lVar6 = (longlong)lua_getnumber(iVar1);
  local_10 = (uint)lVar6;
  lVar6 = (longlong)lua_getnumber(iVar2);
  local_c = (uint)lVar6;
  lVar6 = (longlong)lua_getnumber(iVar3);
  local_8 = (uint)lVar6;
  lVar6 = (longlong)lua_getnumber(iVar4);
  local_4 = (uint)lVar6;
  Render_InvalidateRectLastBuffer((int *)&local_10,1);
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a2a20  Lua_FadeOutChore ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: FadeOutChore */

void Lua_FadeOutChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *luaObj;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  luaObj = (void *)lua_lua2C(2);
  iVar2 = lua_lua2C(3);
  iVar3 = lua_lua2C(4);
  iVar4 = lua_isuserdata(iVar1);
  if ((iVar4 != 0) && (iVar4 = lua_tag(iVar1), iVar4 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    iVar1 = Actor_FromHandle(iVar1);
    lVar5 = (longlong)lua_getnumber(iVar2);
    lVar6 = (longlong)lua_getnumber(iVar3);
    iVar2 = lua_isstring((int)luaObj);
    if ((iVar2 == 0) && (iVar2 = lua_isnumber((int)luaObj), iVar2 == 0)) {
      return;
    }
    iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_4);
    if (iVar1 != 0) {
      Chore_FadeOut(*(void **)local_4,(int)lVar5,(int)lVar6);
    }
  }
  return;
}
#undef local_4

#endif


/* ---- 0x004a2b00  Lua_FadeInChore ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: FadeInChore */

void Lua_FadeInChore(void)

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
    iVar1 = Actor_FromHandle(iVar1);
    lVar4 = (longlong)lua_getnumber(iVar2);
    chore = (uint)lVar4;
    lVar4 = (longlong)lua_getnumber(local_4);
    iVar2 = lua_isstring((int)luaObj);
    if ((iVar2 == 0) && (iVar2 = lua_isnumber((int)luaObj), iVar2 == 0)) {
      return;
    }
    iVar1 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar1 + 0xa0),(void **)&local_8);
    if (iVar1 != 0) {
      Cos_InstPlayChore(*(int *)local_8,chore,0,0);
      Cos_InstUpdateChore(*(int *)local_8,chore,100);
      Chore_FadeIn(*(void **)local_8,chore,(int)lVar4);
    }
  }
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a2c10  Lua_IrisDown ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: IrisDown */

void Lua_IrisDown(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  lVar4 = (longlong)lua_getnumber(iVar3);
  iVar3 = (int)lVar4;
  lVar4 = (longlong)lua_getnumber(iVar2);
  iVar2 = (int)lVar4;
  lVar4 = (longlong)lua_getnumber(iVar1);
  Render_StartIrisClose((int)lVar4,iVar2,iVar3);
  return;
}
#endif


/* ---- 0x004a2c70  Lua_IrisUp ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: IrisUp */

void Lua_IrisUp(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  lVar4 = (longlong)lua_getnumber(iVar3);
  iVar3 = (int)lVar4;
  lVar4 = (longlong)lua_getnumber(iVar2);
  iVar2 = (int)lVar4;
  lVar4 = (longlong)lua_getnumber(iVar1);
  Render_StartIrisOpen((int)lVar4,iVar2,iVar3);
  return;
}
#endif


/* ---- 0x004a2cd0  Lua_IrisComplete ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_4 */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: IrisComplete */

void __fastcall Lua_IrisComplete(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ((code *)Render_IsIrisDone)(param_1);
  lua_pushnumber((float)(iVar1 != 0));
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a2d00  Lua_TextFileGetLineCount ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_21c */
/* Lua opcode: TextFileGetLineCount */

void Lua_TextFileGetLineCount(void)

{
  unsigned char _frame[0x230] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined *puVar5;
  #define local_21c (*(uint *)(_frame + (0x230 - 0x21c)))
  #define local_208 (*(uint *)(_frame + (0x230 - 0x208)))
  #define local_204 (*(uint *)(_frame + (0x230 - 0x204)))
  #define local_200 (*(undefined1 (*)[512])(_frame + (0x230 - 0x200)))
  
  iVar2 = lua_lua2C(1);
  local_208 = 0;
  iVar3 = lua_isnil(iVar2);
  if (iVar3 != 0) {
    lua_pushnil();
    return;
  }
  uVar4 = lua_getstring(iVar2);
  puVar5 = fopen(uVar4,IMG_ADDR(0x004ec5bc));
  if (puVar5 != (undefined *)0x0) {
    iVar2 = lua_createtable();
    bVar1 = puVar5[0xc];
    while ((bVar1 & 0x10) == 0) {
      lua_pushobject(iVar2);
      lua_pushnumber((float)(int)local_208);
      iVar3 = ftell(puVar5);
      lua_pushnumber((float)iVar3);
      lua_settable();
      fgets(local_200,0x200,puVar5);
      local_208 = local_208 + 1;
      bVar1 = puVar5[0xc];
    }
    fclose(puVar5);
    lua_pushobject(iVar2);
    lua_pushstring(s_count_004ec384);
    lua_pushnumber((float)(int)local_208);
    lua_settable();
    lua_pushobject(iVar2);
    return;
  }
  lua_pushnil();
  return;
}
#undef local_200
#undef local_204
#undef local_208
#undef local_21c

#endif


/* ---- 0x004a2e20  Lua_TextFileGetLine ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: TextFileGetLine */

void Lua_TextFileGetLine(void)

{
  unsigned char _frame[0x210] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  longlong lVar5;
  undefined *puVar6;
  #define local_200 (*(char (*)[512])(_frame + (0x210 - 0x200)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnil(iVar1);
  if (iVar3 == 0) {
    iVar3 = lua_isnil(iVar2);
    if (iVar3 == 0) {
      puVar6 = &DAT_004ec5bc;
      uVar4 = lua_getstring(iVar1);
      puVar6 = fopen(uVar4,(uint)puVar6);
      if (puVar6 != (undefined *)0x0) {
        lVar5 = (longlong)lua_getnumber(iVar2);
        fseek(puVar6,(int)lVar5,0);
        local_200[0] = '\0';
        fgets(local_200,0x200,puVar6);
        fclose(puVar6);
        lua_pushstring(local_200);
        return;
      }
    }
  }
  lua_pushnil();
  return;
}
#undef local_200

#endif


/* ---- 0x004a2ee0  Lua_ScreenShot ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: ScreenShot */

void Lua_ScreenShot(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  longlong lVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnil(iVar1);
  if (iVar3 == 0) {
    iVar3 = lua_isnumber(iVar1);
    if (iVar3 == 0) goto LAB_004a2f2f;
    lVar5 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar5;
  }
  else {
LAB_004a2f2f:
    iVar1 = 0x280;
  }
  iVar3 = lua_isnil(iVar2);
  if (iVar3 == 0) {
    iVar3 = lua_isnumber(iVar2);
    if (iVar3 != 0) {
      lVar5 = (longlong)lua_getnumber(iVar2);
      iVar2 = (int)lVar5;
      goto LAB_004a2f5e;
    }
  }
  iVar2 = 0x1e0;
LAB_004a2f5e:
  pcVar4 = Render_CaptureThumbnail(iVar1,iVar2);
  if (pcVar4 != (char *)0x0) {
    lua_pushusertag(pcVar4,0x46554256);
    return;
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a2f90  Lua_SaveScreen ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SaveScreen */

void Lua_SaveScreen(void)

{
  int iVar1;
  int iVar2;
  char *filename;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 != 0) {
      filename = (char *)lua_getstring(iVar1);
      Render_SaveScreen(filename);
    }
  }
  return;
}
#endif


/* ---- 0x004a2fd0  Lua_GetSaveGameImage ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: GetSaveGameImage */

void Lua_GetSaveGameImage(void)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 == 0) {
    lua_pushnil();
    return;
  }
  pcVar3 = (char *)lua_getstring(iVar1);
  pcVar3 = SaveGame_LoadThumbnail(pcVar3);
  if (pcVar3 == (char *)0x0) {
    lua_pushnil();
    return;
  }
  Render_RemapPixels(*(ushort **)(pcVar3 + 0x5c),*(int *)(pcVar3 + 0x10) * *(int *)(pcVar3 + 0xc));
  lua_pushusertag(pcVar3,0x46554256);
  return;
}
#endif


/* ---- 0x004a3040  Lua_GetImage ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: GetImage */

void Lua_GetImage(void)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  void *bitmap;
  int iVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    iVar4 = 0;
    iVar2 = 0;
    pcVar3 = (char *)lua_getstring(iVar1);
    bitmap = stdBitmap_Load(pcVar3,iVar2,iVar4);
    if (bitmap != (void *)0x0) {
      pcVar3 = (char *)**(undefined4 **)((int)bitmap + 0x78);
      pcVar3[0x60] = '\x1f';
      pcVar3[0x61] = -8;
      pcVar3[0x62] = '\0';
      pcVar3[99] = '\0';
      **(undefined4 **)((int)bitmap + 0x78) = 0;
      stdBitmap_Free(bitmap);
      Render_RemapPixels(*(ushort **)(pcVar3 + 0x5c),
                         *(int *)(pcVar3 + 0x10) * *(int *)(pcVar3 + 0xc));
      Render_RemapPixels((ushort *)(pcVar3 + 0x60),1);
      lua_pushusertag(pcVar3,0x46554256);
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a30e0  Lua_FreeImage ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: FreeImage */

void Lua_FreeImage(void)

{
  int iVar1;
  int iVar2;
  void *surface;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x46554256) {
      surface = (void *)lua_getuserdata(iVar1);
      Surface_Free(surface);
    }
  }
  return;
}
#endif


/* ---- 0x004a3130  Lua_BlastImage ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: BlastImage */

void Lua_BlastImage(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *src;
  void *dst;
  longlong lVar5;
  int *srcRect;
  uint colorKey;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar4 = lua_isnil(iVar4);
  colorKey = (uint)(iVar4 == 0);
  iVar4 = lua_isuserdata(iVar1);
  if (iVar4 != 0) {
    iVar4 = lua_tag(iVar1);
    if (iVar4 == 0x46554256) {
      iVar4 = lua_isnumber(iVar2);
      if (iVar4 != 0) {
        iVar4 = lua_isnumber(iVar3);
        if (iVar4 != 0) {
          src = (void *)lua_getuserdata(iVar1);
          srcRect = (int *)0x0;
          lVar5 = (longlong)lua_getnumber(iVar3);
          iVar1 = (int)lVar5;
          lVar5 = (longlong)lua_getnumber(iVar2);
          iVar2 = (int)lVar5;
          dst = (void *)Render_GetBackBuffer();
          Surface_Blit(dst,src,iVar2,iVar1,srcRect,colorKey);
        }
      }
    }
  }
  return;
}
#endif


/* ---- 0x004a31f0  Lua_BlastRect ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: BlastRect */

void Lua_BlastRect(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined2 *puVar7;
  undefined2 *puVar8;
  uint uVar9;
  longlong lVar10;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  local_10 = lua_lua2C(3);
  local_c = lua_lua2C(4);
  iVar3 = lua_lua2C(5);
  local_14 = 0xffff;
  local_8 = 0;
  iVar4 = lua_isnumber(iVar1);
  if ((((iVar4 == 0) || (iVar4 = lua_isnumber(iVar2), iVar4 == 0)) ||
      (iVar4 = lua_isnumber(local_10), iVar4 == 0)) || (iVar4 = lua_isnumber(local_c), iVar4 == 0))
  {
    lua_pushnil();
  }
  else {
    lVar10 = (longlong)lua_getnumber(iVar1);
    local_4 = (uint)lVar10;
    lVar10 = (longlong)lua_getnumber(iVar2);
    iVar1 = (int)lVar10;
    lVar10 = (longlong)lua_getnumber(local_10);
    iVar2 = (int)lVar10;
    lVar10 = (longlong)lua_getnumber(local_c);
    iVar4 = (int)lVar10;
    iVar5 = lua_istable(iVar3);
    if (iVar5 != 0) {
      lua_pushobject(iVar3);
      lua_pushstring(s_color_004e8468);
      local_c = lua_gettable();
      iVar5 = lua_isuserdata(local_c);
      if ((iVar5 != 0) && (iVar5 = lua_tag(local_c), iVar5 == 0x524c4f43)) {
        uVar6 = lua_getuserdata(local_c);
        local_14 = ((uVar6 >> 3) << 6 | uVar6 >> 10 & 0x3f) << 5 | uVar6 >> 0x13 & 0x1f;
        Render_RemapPixels((ushort *)&local_14,1);
      }
      lua_pushobject(iVar3);
      lua_pushstring(s_filled_004e8430);
      iVar3 = lua_gettable();
      iVar3 = lua_isnil(iVar3);
      if (iVar3 == 0) {
        local_8 = 1;
      }
    }
    uVar6 = local_4;
    if ((((int)local_4 <= iVar2) && (iVar1 <= iVar4)) &&
       ((-1 < (int)local_4 && (((-1 < iVar1 && (iVar2 < 0x280)) && (iVar4 < 0x1e0)))))) {
      local_4 = Render_GetBackBuffer();
      uVar9 = iVar2 - uVar6;
      local_c = (iVar4 - iVar1) + 1;
      Surface_Lock((void *)local_4);
      puVar7 = (undefined2 *)
               (iVar1 * *(int *)(local_4 + 0x18) + *(int *)(local_4 + 0x5c) + uVar6 * 2);
      if (uVar9 != 0xffffffff) {
        iVar1 = uVar9 + 1;
        puVar8 = puVar7;
        do {
          *puVar8 = (undefined2)local_14;
          puVar8 = puVar8 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
      if (2 < (int)local_c) {
        for (iVar1 = local_c - 2; iVar1 != 0; iVar1 = iVar1 + -1) {
          puVar7 = (undefined2 *)((int)puVar7 + *(int *)(local_4 + 0x18));
          puVar8 = puVar7;
          uVar6 = uVar9;
          if (local_8 == 0) {
            uVar6 = 1;
          }
          for (; uVar6 != 0; uVar6 = uVar6 - 1) {
            *puVar8 = (undefined2)local_14;
            puVar8 = puVar8 + 1;
          }
          puVar7[uVar9] = (undefined2)local_14;
        }
      }
      if ((1 < (int)local_c) &&
         (puVar7 = (undefined2 *)((int)puVar7 + *(int *)(local_4 + 0x18)), uVar9 != 0xffffffff)) {
        iVar1 = uVar9 + 1;
        do {
          *puVar7 = (undefined2)local_14;
          puVar7 = puVar7 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
      local_10 = uVar9;
      Surface_Unlock((void *)local_4);
      return;
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a34c0  Lua_CallSaveGameCallback ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* system.saveGameCallback(); the script answers with SubmitSaveGameData */

void __cdecl Lua_CallSaveGameCallback(void *writeFn)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  bool bVar2;
  int iVar3;
  void *pvVar4;
  void *pvVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  bVar1 = false;
  bVar2 = false;
  g_pfnLuaSaveWrite = writeFn;
  g_nLuaSaveStringCount = 0;
  lua_beginblock();
  iVar3 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(iVar3);
  lua_pushstring(s_saveGameCallback_004ec5c0);
  pvVar4 = (void *)lua_gettable();
  iVar3 = lua_istable((int)pvVar4);
  if (iVar3 == 0) {
    iVar3 = lua_isfunction((int)pvVar4);
    if (iVar3 == 0) {
      lua_isnil((int)pvVar4);
      pvVar5 = writeFn;
    }
    else {
      bVar2 = false;
      bVar1 = true;
      pvVar5 = pvVar4;
    }
  }
  else {
    lua_pushobject((int)pvVar4);
    lua_pushstring(s_saveGameCallback_004ec5c0);
    pvVar5 = (void *)lua_gettable();
    iVar3 = lua_isfunction((int)pvVar5);
    if (iVar3 != 0) {
      bVar1 = true;
      bVar2 = true;
    }
  }
  if (bVar1) {
    if (bVar2) {
      lua_pushobject((int)pvVar4);
    }
    lua_callfunction((int)pvVar5);
  }
  if (g_nLuaSaveStringCount == 0) {
    (*(code *)writeFn)(&g_nLuaSaveStringCount,4);
  }
  lua_endblock();
  return;
}
#undef local_4

#endif


/* ---- 0x004a35d0  Lua_SubmitSaveGameData ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SubmitSaveGameData */

void Lua_SubmitSaveGameData(void)

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
  g_nLuaSaveStringCount = 0;
  do {
    lua_pushobject(iVar2);
    local_4 = (uint)(float)(int)local_10;
    local_10 = local_10 + 1;
    lua_pushnumber((float)local_4);
    iVar3 = lua_gettable();
    iVar4 = lua_isnil(iVar3);
    if (iVar4 != 0) {
      if (g_nLuaSaveStringCount != 0) {
        (*(code *)g_pfnLuaSaveWrite)(&g_nLuaSaveStringCount,4);
        local_10 = 0;
        while( true ) {
          lua_pushobject(iVar2);
          local_4 = (uint)(float)(int)local_10;
          local_10 = local_10 + 1;
          lua_pushnumber((float)local_4);
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
          (*(code *)g_pfnLuaSaveWrite)(&uStack_8,4);
          (*(code *)g_pfnLuaSaveWrite)(pcVar6,uStack_8);
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
    g_nLuaSaveStringCount = g_nLuaSaveStringCount + ~uVar7 + 4;
  } while( true );
}
#undef local_10
#undef local_4
#undef local_c
#undef uStack_8

#endif


/* ---- 0x004a3720  Lua_GetSaveGameData ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: GetSaveGameData */

void Lua_GetSaveGameData(void)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  char *mode;
  #define local_90 (*(uint *)(_frame + (0xa0 - 0x90)))
  #define local_8c (*(uint *)(_frame + (0xa0 - 0x8c)))
  #define local_88 (*(uint *)(_frame + (0xa0 - 0x88)))
  #define local_84 (*(uint *)(_frame + (0xa0 - 0x84)))
  #define local_80 (*(char (*)[128])(_frame + (0xa0 - 0x80)))
  
  local_90 = 0;
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    mode = &DAT_004ddb18;
    name = (char *)lua_getstring(iVar1);
    pvVar3 = SaveFile_Open(name,mode);
    if (pvVar3 != (void *)0x0) {
      iVar1 = lua_createtable();
      gzread(pvVar3,&local_8c,4);
      for (; 0 < (int)local_8c; local_8c = local_8c + (-4 - local_88)) {
        gzread(pvVar3,&local_88,4);
        gzread(pvVar3,local_80,local_88);
        lua_pushobject(iVar1);
        local_84 = (uint)(float)(int)local_90;
        local_90 = local_90 + 1;
        lua_pushnumber((float)local_84);
        lua_pushstring(local_80);
        lua_settable();
      }
      lua_pushobject(iVar1);
      gzclose(pvVar3);
    }
  }
  return;
}
#undef local_80
#undef local_84
#undef local_88
#undef local_8c
#undef local_90

#endif


/* ---- 0x004a3830  Lua_GetTextSpeed ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_4 */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: GetTextSpeed */

void __fastcall Lua_GetTextSpeed(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ((code *)Text_GetSpeed)(param_1);
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a3850  Lua_SetTextSpeed ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: SetTextSpeed */

void Lua_SetTextSpeed(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    Text_SetSpeed((int)lVar3);
  }
  return;
}
#endif


/* ---- 0x004a3890  Lua_FindFileOnAnyCD ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: FindFileOnAnyCD */

void Lua_FindFileOnAnyCD(void)

{
  unsigned char _frame[0x190] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *a1;
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *a2;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  #define local_180 (*(uint *)(_frame + (0x190 - 0x180)))
  #define local_178 (*(uint *)(_frame + (0x190 - 0x178)))
  #define acStack_174 (*(char (*)[52])(_frame + (0x190 - 0x174)))
  #define auStack_140 (*(undefined1 (*)[320])(_frame + (0x190 - 0x140)))
  
  iVar3 = lua_lua2C(1);
  bVar2 = false;
  iVar4 = lua_isstring(iVar3);
  if ((iVar4 != 0) && (pcVar5 = (char *)lua_getstring(iVar3), pcVar5 != (char *)0x0)) {
    iVar3 = GetLogicalDriveStringsA(0,0);
    if (iVar3 != 0) {
      a2 = (char *)(*g_pSvcLua->pAlloc)
                             (iVar3 + 1,s_C__grimsrc_libs_grimlib_Scripts__004ec38c,0x2728);
      GetLogicalDriveStringsA(iVar3,(int)a2);
      a1 = a2;
      while (((a1 != (char *)0x0 && (*a1 != '\0')) && (!bVar2))) {
        iVar3 = GetDriveTypeA((int)a1);
        if (iVar3 == 5) {
          uVar6 = 0xffffffff;
          pcVar8 = a1;
          do {
            pcVar10 = pcVar8;
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            pcVar10 = pcVar8 + 1;
            cVar1 = *pcVar8;
            pcVar8 = pcVar10;
          } while (cVar1 != '\0');
          uVar6 = ~uVar6;
          pcVar8 = pcVar10 + -uVar6;
          pcVar10 = acStack_174;
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
            pcVar8 = pcVar8 + 4;
            pcVar10 = pcVar10 + 4;
          }
          for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pcVar10 = *pcVar8;
            pcVar8 = pcVar8 + 1;
            pcVar10 = pcVar10 + 1;
          }
          uVar6 = 0xffffffff;
          pcVar8 = pcVar5;
          do {
            pcVar10 = pcVar8;
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            pcVar10 = pcVar8 + 1;
            cVar1 = *pcVar8;
            pcVar8 = pcVar10;
          } while (cVar1 != '\0');
          uVar6 = ~uVar6;
          iVar3 = -1;
          pcVar8 = acStack_174;
          do {
            pcVar9 = pcVar8;
            if (iVar3 == 0) break;
            iVar3 = iVar3 + -1;
            pcVar9 = pcVar8 + 1;
            cVar1 = *pcVar8;
            pcVar8 = pcVar9;
          } while (cVar1 != '\0');
          pcVar8 = pcVar10 + -uVar6;
          pcVar10 = pcVar9 + -1;
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
            pcVar8 = pcVar8 + 4;
            pcVar10 = pcVar10 + 4;
          }
          for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pcVar10 = *pcVar8;
            pcVar8 = pcVar8 + 1;
            pcVar10 = pcVar10 + 1;
          }
          iVar3 = FindFirstFileA((int)acStack_174,(int)auStack_140);
          if (iVar3 != -1) {
            bVar2 = true;
            FindClose(iVar3);
          }
        }
        uVar6 = 0xffffffff;
        pcVar8 = a1;
        do {
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          cVar1 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar1 != '\0');
        a1 = a1 + ~uVar6;
      }
      (*g_pSvcLua->pFree)(a2);
    }
    if (bVar2) {
      lua_pushnumber(1.0);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef acStack_174
#undef auStack_140
#undef local_178
#undef local_180

#endif


/* ---- 0x004a3a10  Lua_ActorPuckOrient ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: ActorPuckOrient */

void Lua_ActorPuckOrient(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      iVar3 = lua_isnil(iVar2);
      if (iVar3 == 0) {
        lVar4 = (longlong)lua_getnumber(iVar2);
        if ((int)lVar4 != 0) {
          *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x10;
          return;
        }
      }
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xffffffef;
    }
  }
  return;
}
#endif


/* ---- 0x004a3aa0  Lua_GetTickCount ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetTickCount */

void Lua_GetTickCount(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  uVar1 = GetTickCount();
  lua_pushnumber((float)uVar1);
  return;
}
#undef local_c

#endif


/* ---- 0x004a3ae0  Lua_SetActorInvClipNode ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: SetActorInvClipNode */

void Lua_SetActorInvClipNode(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnil(iVar2);
      if (iVar3 == 0) {
        lVar5 = (longlong)lua_getnumber(iVar2);
        uVar4 = (undefined4)lVar5;
      }
      else {
        uVar4 = 0xffffffff;
      }
      iVar1 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(iVar1);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      *(undefined4 *)(*(int *)(iVar1 + 0xa4) + 0x420) = uVar4;
    }
  }
  return;
}
#endif


/* ---- 0x004a3b80  Lua_SetWalkSystemFadeTime ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: SetWalkSystemFadeTime */

void Lua_SetWalkSystemFadeTime(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 == 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    Walker_SetFadeTime((int)lVar3);
  }
  return;
}
#endif


/* ---- 0x004be180  Lua_LightMgrStartup ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Debug light manager dialog (Lua LightMgrStartup). Creates the dialog, a keyboard hook and a
   helper actor wearing x_spot.cos */

void Lua_LightMgrStartup(void)

{
  int iVar1;
  char *actor;
  int iVar2;
  int a3;
  code *a4;
  int a5;
  
  if (*(int *)((int)g_pDisplayDevice + 0x110) != 0) {
    MessageBeep(0);
    return;
  }
  if (g_hLightEdDialog == (void *)0x0) {
    a5 = 0;
    a4 = FUN_004bf950;
    a3 = 0;
    iVar2 = 0x65;
    iVar1 = Win_GetInstance();
    g_hLightEdDialog = (void *)CreateDialogParamA(iVar1,iVar2,a3,(int)a4,a5);
    if (g_hLightEdDialog == (void *)0x0) {
      (*g_pSvcMain->pDebug)(s_LightManager_Startup__Could_not_c_004f0d34);
    }
    else {
      iVar2 = 0;
      iVar1 = Win_GetInstance();
      UINT_008d363c = SetWindowsHookExA(2,((unsigned)(uintptr_t)FUN_004bffb0),iVar1,iVar2);
    }
    if (UINT_004f0d0c == 0xffffffff) {
      UINT_004f0d0c = Actor_Create();
    }
    g_pLightEdMarkerActor = (void *)Actor_FromHandle(UINT_004f0d0c);
    Actor_SetCostume(g_pLightEdMarkerActor,s_x_spot_cos_004f0d28,0);
    actor = Set_GetCurrentName();
    Actor_PutInSet(actor,g_pLightEdMarkerActor);
    Actor_SetFollowBoxes(g_pLightEdMarkerActor,0);
    *(uint *)((int)g_pLightEdMarkerActor + 4) = *(uint *)((int)g_pLightEdMarkerActor + 4) | 2;
    Lua_LightMgrSetChange();
    return;
  }
  Lua_LightMgrShutdown();
  return;
}
#endif


/* ---- 0x004be260  Lua_LightMgrSetChange ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: LightMgrSetChange */

void Lua_LightMgrSetChange(void)

{
  char *actor;
  
  if (g_hLightEdDialog != (void *)0x0) {
    g_pLightEdSet = Set_GetCurrent();
    actor = Set_GetCurrentName();
    if (g_pLightEdMarkerActor != (void *)0x0) {
      Actor_PutInSet(actor,g_pLightEdMarkerActor);
    }
    LightMgr_Refresh();
    LightMgr_UpdateDialog(g_hLightEdDialog);
  }
  return;
}
#endif


/* ---- 0x004be2a0  Lua_LightMgrShutdown ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua opcode: LightMgrShutdown */

void Lua_LightMgrShutdown(void)

{
  if (UINT_008d363c != 0) {
    UnhookWindowsHookEx(UINT_008d363c);
  }
  if (g_hLightEdDialog != (void *)0x0) {
    DestroyWindow((int)g_hLightEdDialog);
    g_hLightEdDialog = (void *)0x0;
  }
  if (g_pLightEdMarkerActor != (void *)0x0) {
    Actor_RemoveFromSet((char *)((int)g_pLightEdMarkerActor + 0x7c),g_pLightEdMarkerActor);
    *(undefined1 *)((int)g_pLightEdMarkerActor + 0x7c) = 0;
    *(uint *)((int)g_pLightEdMarkerActor + 4) = *(uint *)((int)g_pLightEdMarkerActor + 4) | 2;
    g_pLightEdMarkerActor = (void *)0x0;
  }
  return;
}
#endif

