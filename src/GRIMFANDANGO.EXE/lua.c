/* GRIMFANDANGO.EXE :: lua.c
 * functions 0x00401ca0 .. 0x004be2a0 (281 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00401ca0  sputLua_Is3DHardwareEnabledL ---- */
/* Lua opcode: Is3DHardwareEnabled Original name sputLua_Is3DHardwareEnabledL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'Is3DHardwareEnabled'); was
   Lua_Is3DHardwareEnabled. */

void sputLua_Is3DHardwareEnabledL(void)

{
  if (g_pStd3D_CurDevice != (void *)0x0) {
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
  if (g_pStd3D_CurDevice == (void *)0x0) {
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
  if (g_pStd3D_CurDevice != (void *)0x0) {
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
  if (g_pStd3D_CurDevice == (void *)0x0) {
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
  if ((((-1 < (int)UINT_004dd340) && ((int)UINT_004dd340 < (int)g_dwStdDisplay_numDevices)) &&
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
  uVar2 = (uint)(g_nDeveloper == 0);
  if (uVar2 < g_dwStdDisplay_numDevices) {
    pcVar3 = &DAT_00902ce0 + uVar2 * 0x298;
    do {
      lua_pushobject(iVar1);
      lua_pushnumber((float)uVar2);
      lua_pushstring(pcVar3);
      lua_settable();
      uVar2 = uVar2 + 1;
      pcVar3 = pcVar3 + 0x298;
    } while (uVar2 < g_dwStdDisplay_numDevices);
  }
  lua_pushobject(iVar1);
  return;
}
#undef local_1c


/* ---- 0x00482880  grimlib_NextSetup ---- */
/* Lua opcode: NextSetup Original name grimlib_NextSetup (the remaster's GrimFandango (Linux): Lua /
   module table entry 'NextSetup'); was Lua_NextSetup. */

void grimlib_NextSetup(void)

{
  void *pvVar1;
  
  pvVar1 = sputRoom_GetCurrentRoom();
  grimlib_MakeCurrentSetup((*(int *)((int)pvVar1 + 0xb4) + 1U) % *(uint *)((int)pvVar1 + 0xb0));
  return;
}

/* ---- 0x004828a0  grimlib_PreviousSetup ---- */
/* Lua opcode: PreviousSetup Original name grimlib_PreviousSetup (the remaster's GrimFandango
   (Linux): Lua / module table entry 'PreviousSetup'); was Lua_PreviousSetup. */

void grimlib_PreviousSetup(void)

{
  void *pvVar1;
  
  pvVar1 = sputRoom_GetCurrentRoom();
  grimlib_MakeCurrentSetup
            ((*(int *)((int)pvVar1 + 0xb4) + -1 + *(uint *)((int)pvVar1 + 0xb0)) %
             *(uint *)((int)pvVar1 + 0xb0));
  return;
}

/* ---- 0x00486f50  sputRender_ClearIris ---- */
/* Lua opcode: IrisClear Original name sputRender_ClearIris (the remaster's GrimFandango (Linux):
   Lua / module table entry 'IrisClear'); was Lua_IrisClear. */

void sputRender_ClearIris(void)

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
  MarkDirtyRect((int *)&local_10,0);
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00489840  sputPrimitive_DrawLine ---- */
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Lua opcode: DrawLine Original name sputPrimitive_DrawLine (the remaster's GrimFandango (Linux):
   Lua / module table entry 'DrawLine'); was Lua_DrawLine. */

void sputPrimitive_DrawLine(void)

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
          uVar6 = PrimitiveQueue_addLine
                            (&g_dwPrimitiveQ,(int)lVar7,(int)lVar8,(int)lVar9,(int)lVar10,local_1c,
                             local_18);
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


/* ---- 0x00489a80  sputPrimitive_DrawPolygon ---- */
/* WARNING: Variable defined which should be unmapped: local_38 */
/* Lua opcode: DrawPolygon Original name sputPrimitive_DrawPolygon (the remaster's GrimFandango
   (Linux): Lua / module table entry 'DrawPolygon'); was Lua_DrawPolygon. */

void sputPrimitive_DrawPolygon(void)

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
      uVar5 = PrimitiveQueue_addPolygon(&g_dwPrimitiveQ,uVar5,(int *)local_14,local_18,local_c);
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


/* ---- 0x00489d70  sputPrimitive_DrawRectangle ---- */
/* WARNING: Variable defined which should be unmapped: local_34 */
/* Lua opcode: DrawRectangle Original name sputPrimitive_DrawRectangle (the remaster's GrimFandango
   (Linux): Lua / module table entry 'DrawRectangle'); was Lua_DrawRectangle. */

void sputPrimitive_DrawRectangle(void)

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
    uVar7 = PrimitiveQueue_addRect
                      (&g_dwPrimitiveQ,(int)lVar8,(int)lVar9,(int)lVar10,(int)lVar11,local_20,
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


/* ---- 0x00489fe0  sputPrimitive_ChangePrimitive ---- */
/* Lua opcode: ChangePrimitive Original name sputPrimitive_ChangePrimitive (the remaster's
   GrimFandango (Linux): Lua / module table entry 'ChangePrimitive'); was Lua_ChangePrimitive. */

void sputPrimitive_ChangePrimitive(void)

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
      PrimitiveQueue_changeColor
                (&g_dwPrimitiveQ,iVar1,
                 (uint)(PIECE(local_10,2,1) >> ((byte)UINT_004ddac8 & 0x1f)) <<
                 ((byte)UINT_004ddabc & 0x1f) & 0xffff |
                 ((uVar5 >> 8 & 0xff) >> ((byte)UINT_004ddac4 & 0x1f)) <<
                 ((byte)UINT_004ddab8 & 0x1f) & 0xffff |
                 ((uVar5 & 0xff) >> ((byte)UINT_004ddac0 & 0x1f)) << ((byte)UINT_004ddab4 & 0x1f) &
                 0xffff);
    }
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_layer_004e8390);
    iVar3 = lua_gettable();
    iVar4 = lua_isnumber(iVar3);
    if (iVar4 != 0) {
      lVar7 = (longlong)lua_getnumber(iVar3);
      PrimitiveQueue_changeLayer(&g_dwPrimitiveQ,iVar1,(int)lVar7);
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
      PrimitiveQueue_move(&g_dwPrimitiveQ,iVar1,local_8,iVar3);
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
      PrimitiveQueue_moveTo(&g_dwPrimitiveQ,iVar1,local_8,iVar3);
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
      PrimitiveQueue_moveEndpoint(&g_dwPrimitiveQ,iVar1,local_8,iVar3);
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
    PrimitiveQueue_changeDimensions(&g_dwPrimitiveQ,iVar1,iVar3,iVar6);
    return;
  }
  return;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0048a460  sputPrimitive_KillPrimitive ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: KillPrimitive Original name sputPrimitive_KillPrimitive (the remaster's GrimFandango
   (Linux): Lua / module table entry 'KillPrimitive'); was Lua_KillPrimitive. */

void __cdecl sputPrimitive_KillPrimitive(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    PrimitiveQueue_deletePrimitive(&g_dwPrimitiveQ,(int)lVar3);
  }
  return;
}

/* ---- 0x0048a4a0  sputPrimitive_PurgeQueue ---- */
/* Lua opcode: PurgePrimitiveQueue Original name sputPrimitive_PurgeQueue (the remaster's
   GrimFandango (Linux): Lua / module table entry 'PurgePrimitiveQueue'); was
   Lua_PurgePrimitiveQueue. */

void sputPrimitive_PurgeQueue(void)

{
  PrimitiveQueue_purge((int *)&g_dwPrimitiveQ);
  PrimitiveQueue_resetId();
  return;
}

/* ---- 0x0048ad60  sputText_SetOffscreenTextPosL ---- */
/* Lua opcode: SetOffscreenTextPos Original name sputText_SetOffscreenTextPosL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetOffscreenTextPos'); was
   Lua_SetOffscreenTextPos. */

void sputText_SetOffscreenTextPosL(void)

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

/* ---- 0x0048ade0  sputText_SetEmergencyFontL ---- */
/* Lua opcode: SetEmergencyFont Original name sputText_SetEmergencyFontL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetEmergencyFont'); was Lua_SetEmergencyFont. */

void sputText_SetEmergencyFontL(void)

{
  int iVar1;
  int iVar2;
  char *filename;
  void **outFont;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    if (g_hEmergencyFont != (void *)0x0) {
      Text_FreeFont(g_hEmergencyFont);
      g_hEmergencyFont = (void *)0x0;
    }
    outFont = &g_hEmergencyFont;
    filename = (char *)lua_getstring(iVar1);
    Text_LoadNativeFont(filename,outFont);
    return;
  }
  iVar1 = lua_isnil(iVar1);
  if ((iVar1 != 0) && (g_hEmergencyFont != (void *)0x0)) {
    Text_FreeFont(g_hEmergencyFont);
    g_hEmergencyFont = (void *)0x0;
  }
  return;
}

/* ---- 0x0048ae60  sputText_LocalizeStringL ---- */
/* Lua opcode: LocalizeString Original name sputText_LocalizeStringL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'LocalizeString'); was Lua_LocalizeString. */

void sputText_LocalizeStringL(void)

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
    pcVar3 = sputText_ExtractSayLineData(line,pcVar3);
    sprintf(local_280,s___s__s_004e8754,local_2a0,pcVar3);
    lua_pushstring(local_280);
  }
  return;
}
#undef local_280
#undef local_2a0


/* ---- 0x0048aed0  sputText_MakeColorL ---- */
/* Lua opcode: MakeColor Original name sputText_MakeColorL (the remaster's GrimFandango (Linux): Lua
   / module table entry 'MakeColor'); was Lua_MakeColor. */

void sputText_MakeColorL(void)

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


/* ---- 0x0048b100  sputText_GetColorComponentsL ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: GetColorComponents Original name sputText_GetColorComponentsL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetColorComponents'); was Lua_GetColorComponents.
    */

void sputText_GetColorComponentsL(void)

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


/* ---- 0x0048b190  sputText_SetActorTalkColorL ---- */
/* Lua opcode: SetActorTalkColor Original name sputText_SetActorTalkColorL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorTalkColor'); was Lua_SetActorTalkColor.
    */

void sputText_SetActorTalkColorL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  uint uVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      iVar1 = lua_isuserdata(iVar2);
      if (iVar1 != 0) {
        iVar1 = lua_tag(iVar2);
        if (iVar1 == 0x524c4f43) {
          uVar4 = lua_getuserdata(iVar2);
          actor->pExtra->dwTalkColor = uVar4;
        }
      }
    }
  }
  return;
}

/* ---- 0x0048b230  sputText_GetActorTalkColorL ---- */
/* Lua opcode: GetActorTalkColor Original name sputText_GetActorTalkColorL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetActorTalkColor'); was Lua_GetActorTalkColor.
    */

void sputText_GetActorTalkColorL(void)

{
  int iVar1;
  int iVar2;
  Actor *pAVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar3 = sputActor_ActorDeref(iVar1);
      if (pAVar3->pExtra != (ActorExtra *)0x0) {
        lua_pushusertag((char *)pAVar3->pExtra->dwTalkColor,0x524c4f43);
        return;
      }
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0048b2a0  sputText_SetSayLineDefaultsL ---- */
/* Lua opcode: SetSayLineDefaults Original name sputText_SetSayLineDefaultsL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetSayLineDefaults'); was Lua_SetSayLineDefaults.
    */

void sputText_SetSayLineDefaultsL(void)

{
  void *table;
  int iVar1;
  
  table = (void *)lua_lua2C(1);
  if (table != (void *)0x0) {
    iVar1 = lua_istable((int)table);
    if (iVar1 != 0) {
      GetTextParamsFromTable(&g_SubtitleTextCtx,table,(TextObject *)0x0);
    }
  }
  return;
}

/* ---- 0x0048b4c0  sputText_SayLineL ---- */
/* Lua opcode: SayLine Original name sputText_SayLineL (the remaster's GrimFandango (Linux): Lua /
   module table entry 'SayLine'); was Lua_SayLine. */

void sputText_SayLineL(void)

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
      local_38 = (uint)sputActor_ActorDeref(iVar1);
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
            sputText_ExtractSayLineData((char *)local_34,local_20);
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
        sputActor_SayLine((Actor *)local_38,(char *)local_34,local_3c,local_24,local_28,local_2c,
                          local_30);
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
  iVar1 = lua_getref(g_dwLrX);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (*param_5 != 0)) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    *param_5 = (int)lVar3;
  }
  lua_pushobject(param_1);
  iVar1 = lua_getref(g_dwLrY);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (*param_6 != 0)) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    *param_6 = (int)lVar3;
  }
  lua_pushobject(param_1);
  iVar1 = lua_getref(g_dwLrBackground);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar1 = lua_isnil(iVar1);
  if ((iVar1 == 0) && (*param_2 != 0)) {
    *param_2 = 0;
  }
  lua_pushobject(param_1);
  iVar1 = lua_getref(g_dwLrVolume);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (*param_3 != 0)) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    *param_3 = (int)lVar3;
  }
  lua_pushobject(param_1);
  iVar1 = lua_getref(g_dwLrPan);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (*param_4 != 0)) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    *param_4 = (int)lVar3;
  }
  return;
}

/* ---- 0x0048b830  sputText_PrintLineL ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: PrintLine Original name sputText_PrintLineL (the remaster's GrimFandango (Linux): Lua
   / module table entry 'PrintLine'); was Lua_PrintLine. */

void sputText_PrintLineL(void)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  void *table;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  TextObject *obj;
  undefined4 unaff_ESI;
  TextContext *pTVar6;
  undefined4 unaff_EDI;
  undefined4 *puVar7;
  longlong lVar8;
  #define local_5c (*(uint *)(_frame + (0x70 - 0x5c)))
  #define local_58 (*(int *)(_frame + (0x70 - 0x58)))
  #define local_50 (*(char (*)[32])(_frame + (0x70 - 0x50)))
  #define local_30 (*(undefined4 (*)[12])(_frame + (0x70 - 0x30)))
  
  iVar2 = lua_lua2C(1);
  table = (void *)lua_lua2C(2);
  local_58 = -1;
  if ((int)UINT_008a94bc <= (int)UINT_004e8480) {
    UINT_004e8480 = UINT_008a94bc;
  }
  if ((int)UINT_008a94c0 <= (int)UINT_004e8484) {
    UINT_004e8484 = UINT_008a94c0;
  }
  iVar3 = lua_isstring(iVar2);
  if (((iVar3 != 0) || (iVar3 = lua_isnil(iVar2), iVar3 != 0)) &&
     ((iVar3 = lua_istable((int)table), iVar3 != 0 || (iVar3 = lua_isnil((int)table), iVar3 != 0))))
  {
    iVar3 = lua_isnil(iVar2);
    if (iVar3 == 0) {
      local_5c = (uint)local_30;
      pTVar6 = &g_PrintLineTextCtx;
      puVar7 = local_30;
      for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar7 = pTVar6->pUnused;
        pTVar6 = (TextContext *)&pTVar6->pClipRect;
        puVar7 = puVar7 + 1;
      }
    }
    else {
      local_5c = (uint)&g_PrintLineTextCtx;
    }
    iVar3 = lua_istable((int)table);
    if (iVar3 != 0) {
      local_58 = GetTextParamsFromTable((TextContext *)local_5c,table,(TextObject *)0x0);
    }
    iVar3 = lua_isstring(iVar2);
    if (iVar3 != 0) {
      pcVar5 = local_50;
      pcVar4 = (char *)lua_getstring(iVar2);
      pcVar5 = sputText_ExtractSayLineData(pcVar4,pcVar5);
      if (local_58 < 0) {
        iVar2 = -1;
        pcVar4 = pcVar5;
        do {
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          cVar1 = *pcVar4;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        local_58 = (int)lVar8;
      }
      iVar2 = 0;
      obj = TextObject_New((TextContext *)local_5c,pcVar5,local_58,0);
      sputText_AddToQueue(obj,local_58,iVar2);
    }
  }
  return;
}
#undef local_30
#undef local_50
#undef local_58
#undef local_5c

#endif


/* ---- 0x0048b9a0  sputText_IsMessageGoingL ---- */
/* Lua opcode: IsMessageGoing Original name sputText_IsMessageGoingL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsMessageGoing'); was Lua_IsMessageGoing. */

void sputText_IsMessageGoingL(void)

{
  TextObject *pTVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  
  iVar2 = lua_lua2C(1);
  if ((iVar2 == 0) ||
     (((iVar3 = lua_isuserdata(iVar2), iVar3 != 0 && (iVar3 = lua_tag(iVar2), iVar3 == 0x52544341))
      || (iVar3 = lua_isnil(iVar2), iVar3 != 0)))) {
    iVar3 = lua_isuserdata(iVar2);
    if ((iVar3 == 0) || (iVar3 = lua_tag(iVar2), iVar3 != 0x52544341)) {
      pTVar1 = g_pTextQueue;
      iVar2 = sputActor_GetNumActorsTalking();
      if (iVar2 != 0) {
        lua_pushnumber(1.0);
        return;
      }
      for (; pTVar1 != (TextObject *)0x0; pTVar1 = pTVar1->pNext) {
        if ((pTVar1->dwFlags & 1) == 0) goto LAB_0048ba30;
      }
    }
    else {
      iVar2 = lua_getuserdata(iVar2);
      pAVar4 = sputActor_ActorDeref(iVar2);
      if (((pAVar4 != (Actor *)0x0) && (pAVar4->pExtra != (ActorExtra *)0x0)) &&
         (pAVar4->pExtra->nTalking != 0)) {
LAB_0048ba30:
        lua_pushnumber(1.0);
        return;
      }
    }
    lua_pushnil();
  }
  return;
}

/* ---- 0x0048ba90  sputText_ExpireTextQueueL ---- */
/* Lua opcode: ExpireText Original name sputText_ExpireTextQueueL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ExpireText'); was Lua_ExpireText. */

void sputText_ExpireTextQueueL(void)

{
  TextObject *obj;
  
  for (obj = g_pTextQueue; obj != (TextObject *)0x0; obj = obj->pNext) {
    if ((obj->dwFlags & 4) != 0) {
      List_Unlink(obj);
      obj->dwFlags = obj->dwFlags & 0xfffffffa;
      obj->pActor->pExtra->pText = (TextObject *)0x0;
    }
    obj->nDuration = -1;
  }
  return;
}

/* ---- 0x0048baf0  sputText_PurgeTextQueueL ---- */
/* Lua opcode: PurgeText Original name sputText_PurgeTextQueueL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'PurgeText'); was Lua_PurgeText. */

void sputText_PurgeTextQueueL(void)

{
  TextObject *pTVar1;
  
  for (pTVar1 = g_pTextQueue; pTVar1 != (TextObject *)0x0; pTVar1 = pTVar1->pNext) {
    pTVar1->nDuration = -1;
    pTVar1->dwFlags = pTVar1->dwFlags & 0xfffffffe;
  }
  return;
}

/* ---- 0x0048bb20  sputText_KillTextObjectL ---- */
/* Lua opcode: KillTextObject Original name sputText_KillTextObjectL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'KillTextObject'); was Lua_KillTextObject. */

void sputText_KillTextObjectL(void)

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

/* ---- 0x0048bb70  sputText_GetFontDimensionsL ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetFontDimensions Original name sputText_GetFontDimensionsL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetFontDimensions'); was Lua_GetFontDimensions.
    */

void sputText_GetFontDimensionsL(void)

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


/* ---- 0x0048bbc0  sputText_GetTextObjectDimensionsL ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: GetTextObjectDimensions Original name sputText_GetTextObjectDimensionsL (the
   remaster's GrimFandango (Linux): Lua / module table entry 'GetTextObjectDimensions'); was
   Lua_GetTextObjectDimensions. */

void sputText_GetTextObjectDimensionsL(void)

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
      iVar2 = Text_GetStringWidth((TextContext *)(iVar1 + 0x208),(char *)(iVar1 + 8));
      lua_pushnumber((float)iVar2);
      iVar1 = Text_GetStringHeight((TextContext *)(iVar1 + 0x208),(char *)(iVar1 + 8));
      lua_pushnumber((float)iVar1);
    }
  }
  return;
}
#undef local_14
#undef local_4


/* ---- 0x0048bc50  sputText_GetTextCharPositionL ---- */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* Lua opcode: GetTextCharPosition Original name sputText_GetTextCharPositionL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetTextCharPosition'); was
   Lua_GetTextCharPosition. */

void sputText_GetTextCharPositionL(void)

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
          iVar2 = Text_GetCharKernedWidth((TextContext *)(iVar1 + 0x208),(int)*pcVar4);
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


/* ---- 0x0048bd10  sputText_ChangeTextObjectL ---- */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* Lua opcode: ChangeTextObject Original name sputText_ChangeTextObjectL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'ChangeTextObject'); was Lua_ChangeTextObject. */

void sputText_ChangeTextObjectL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  TextObject *textObj;
  void *table;
  char *pcVar3;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x54584554) {
      textObj = (TextObject *)lua_getuserdata(iVar1);
      local_4 = 0;
      iVar1 = 2;
      do {
        table = (void *)lua_lua2C(iVar1);
        if (table == (void *)0x0) break;
        iVar2 = lua_isstring((int)table);
        if (iVar2 == 0) {
          iVar2 = lua_istable((int)table);
          if (iVar2 == 0) break;
          GetTextParamsFromTable(&textObj->ctx,table,textObj);
        }
        else {
          pcVar3 = (char *)lua_getstring((int)table);
          pcVar3 = sputText_ExtractSayLineData(pcVar3,(char *)0x0);
          strncpy(textObj->aText,pcVar3,0x1ff);
          textObj->aText[0x1ff] = '\0';
        }
        local_4 = local_4 + 1;
        iVar1 = iVar1 + 1;
      } while ((int)local_4 < 2);
      iVar1 = Text_GetStringWidth(&textObj->ctx,textObj->aText);
      lua_pushnumber((float)iVar1);
      iVar1 = Text_GetStringHeight(&textObj->ctx,textObj->aText);
      lua_pushnumber((float)iVar1);
    }
  }
  return;
}
#undef local_18
#undef local_4


/* ---- 0x0048be30  sputText_MakeTextObjectL ---- */
/* WARNING: Variable defined which should be unmapped: local_78 */
/* Lua opcode: MakeTextObject Original name sputText_MakeTextObjectL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'MakeTextObject'); was Lua_MakeTextObject. */

void sputText_MakeTextObjectL(void)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *pcVar3;
  void *table;
  TextObject *obj;
  int unaff_EBX;
  TextContext *pTVar4;
  int unaff_EDI;
  undefined4 *puVar5;
  #define local_78 (*(uint *)(_frame + (0x90 - 0x78)))
  #define local_64 (*(uint *)(_frame + (0x90 - 0x64)))
  #define local_60 (*(uint *)(_frame + (0x90 - 0x60)))
  #define local_5c (*(uint *)(_frame + (0x90 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x90 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x90 - 0x54)))
  #define local_50 (*(char (*)[32])(_frame + (0x90 - 0x50)))
  #define local_2c (*(uint *)(_frame + (0x90 - 0x2c)))
  
  local_60 = 0;
  local_5c = 0;
  local_58 = UINT_008a94bc;
  local_54 = UINT_008a94c0;
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    pcVar3 = (char *)lua_getstring(iVar1);
    pTVar4 = &g_TextObjectCtx;
    puVar5 = (undefined4 *)(_frame + (0x90 - 0x30));
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar5 = pTVar4->pUnused;
      pTVar4 = (TextContext *)&pTVar4->pClipRect;
      puVar5 = puVar5 + 1;
    }
    local_2c = (uint)&local_60;
    table = (void *)lua_lua2C(2);
    if (table != (void *)0x0) {
      iVar1 = lua_istable((int)table);
      if (iVar1 != 0) {
        GetTextParamsFromTable((TextContext *)(_frame + (0x90 - 0x30)),table,(TextObject *)0x0);
      }
    }
    pcVar3 = sputText_ExtractSayLineData(pcVar3,local_50);
    obj = TextObject_New((TextContext *)(_frame + (0x90 - 0x30)),pcVar3,unaff_EBX,unaff_EDI);
    lua_pushusertag((char *)obj,0x54584554);
    iVar1 = Text_GetStringWidth(&obj->ctx,obj->aText);
    lua_pushnumber((float)iVar1);
    iVar1 = Text_GetStringHeight(&obj->ctx,obj->aText);
    lua_pushnumber((float)iVar1);
    sputText_AddToQueue(obj,0,1);
  }
  return;
}
#undef local_2c
#undef local_50
#undef local_54
#undef local_58
#undef local_5c
#undef local_60
#undef local_64
#undef local_78


/* ---- 0x0048bf50  sputText_BlastText ---- */
/* Lua opcode: BlastText Original name sputText_BlastText (the remaster's GrimFandango (Linux): Lua
   / module table entry 'BlastText'); was Lua_BlastText. */

void sputText_BlastText(void)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *pcVar3;
  void *pvVar4;
  TextObject *obj;
  int unaff_EBP;
  TextContext *pTVar5;
  int unaff_EDI;
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
    stdDisplay_VBufferLock(pvVar4);
    pTVar5 = &g_TextObjectCtx;
    puVar6 = &local_30;
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar6 = (uint)pTVar5->pUnused;
      pTVar5 = (TextContext *)&pTVar5->pClipRect;
      puVar6 = puVar6 + 1;
    }
    iVar1 = Render_GetBackBuffer();
    local_2c = (uint)&local_60;
    *(undefined4 *)local_30 = *(undefined4 *)(iVar1 + 0x5c);
    pvVar4 = (void *)lua_lua2C(2);
    if (pvVar4 != (void *)0x0) {
      iVar1 = lua_istable((int)pvVar4);
      if (iVar1 != 0) {
        GetTextParamsFromTable((TextContext *)&local_30,pvVar4,(TextObject *)0x0);
      }
    }
    pcVar3 = sputText_ExtractSayLineData(pcVar3,local_50);
    obj = TextObject_New((TextContext *)&local_30,pcVar3,unaff_EBP,unaff_EDI);
    TextObject_Draw(obj,0);
    pvVar4 = (void *)Render_GetBackBuffer();
    stdDisplay_VBufferUnlock(pvVar4);
    List_Unlink(obj);
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


/* ---- 0x0048c960  sputText_GetTranslationModeL ---- */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Lua opcode: GetTranslationMode Original name sputText_GetTranslationModeL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetTranslationMode'); was Lua_GetTranslationMode.
    */

void sputText_GetTranslationModeL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  lua_pushnumber((float)g_nTranslationType);
  return;
}
#undef local_4


/* ---- 0x0048c980  sputText_SetTranslationModeL ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: SetTranslationMode Original name sputText_SetTranslationModeL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetTranslationMode'); was Lua_SetTranslationMode.
    */

void sputText_SetTranslationModeL(void)

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
    g_nTranslationType = (int)lVar3;
    if (-1 < g_nTranslationType) {
      if (2 < g_nTranslationType) {
        g_nTranslationType = 2;
        return;
      }
      return;
    }
  }
  g_nTranslationType = 0;
  return;
}

/* ---- 0x00495850  sputCostume_GetKeyLengthL ---- */
/* Lua opcode: GetKeyLength Original name sputCostume_GetKeyLengthL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetKeyLength'); was Lua_GetKeyLength. */

void sputCostume_GetKeyLengthL(void)

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
    (*g_pStd_HS->pAssertFail)(s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3)
    ;
  }
  iVar1 = piVar3[1];
  if (*piVar3 == 0) {
    (*g_pStd_HS->pAssertFail)(s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3)
    ;
  }
  lua_pushnumber(((float)*(uint *)(iVar1 + 0x34) / *(float *)(piVar3[1] + 0x30)) * 1000.0);
  return;
}

/* ---- 0x00495900  sputCostume_GetSmushLengthL ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetSmushLength Original name sputCostume_GetSmushLengthL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetSmushLength'); was Lua_GetSmushLength. */

void sputCostume_GetSmushLengthL(void)

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
      iVar1 = sputSmush_GetMovieLength(iVar1);
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

/* ---- 0x00498d80  sputLua_GetMemoryUsageL ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: GetMemoryUsage Original name sputLua_GetMemoryUsageL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetMemoryUsage'); was Lua_GetMemoryUsage. */

void sputLua_GetMemoryUsageL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = daTotalAllocated();
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x00498da0  sputLua_GetDiskFreeSpaceL ---- */
/* Lua opcode: GetDiskFreeSpace Original name sputLua_GetDiskFreeSpaceL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetDiskFreeSpace'); was Lua_GetDiskFreeSpace. */

void sputLua_GetDiskFreeSpaceL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_4 (*(undefined1 (*)[4])(_frame + (0x30 - 0x4)))
  
  GetDiskFreeSpaceA(0,(int)(local_18 + 1),(int)local_18,(int)(local_18 + 2),(int)local_4);
  lua_pushnumber((float)PUN(uint,(float)local_18[0]) * 0.0009765625 * (float)PUN(int,(float)local_18[1]) * 0.0009765625 *
                 (float)PUN(int,(float)local_18[2]));
  return;
}
#undef local_18
#undef local_4


/* ---- 0x00498e20  sputLua_Test ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: TEST Original name sputLua_Test (the remaster's GrimFandango (Linux): Lua / module
   table entry 'TEST'); was Lua_TEST. */

void __cdecl sputLua_Test(void)

{
  ShrinkBoxes(0.005);
  return;
}
#endif


/* ---- 0x00498e50  sputLua_ShrinkBoxes ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: ShrinkBoxes Original name sputLua_ShrinkBoxes (the remaster's GrimFandango (Linux):
   Lua / module table entry 'ShrinkBoxes'); was Lua_ShrinkBoxes. */

void __cdecl sputLua_ShrinkBoxes(void)

{
  int iVar1;
  int iVar2;
  float radius;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 == 0) {
    sputLua_UnShrinkBoxes();
    WalkPlane_BuildCache();
    radius = lua_getnumber(iVar1);
    ShrinkBoxes(radius);
  }
  return;
}
#endif


/* ---- 0x00498e90  sputLua_UnShrinkBoxes ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: UnShrinkBoxes Original name sputLua_UnShrinkBoxes (the remaster's GrimFandango
   (Linux): Lua / module table entry 'UnShrinkBoxes'); was Lua_UnShrinkBoxes. */

void sputLua_UnShrinkBoxes(void)

{
  WalkPlane_RestoreCache();
  WalkPlane_DestroyCache();
  return;
}
#endif


/* ---- 0x00498ea0  sputLua_GetShrinkPosition ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: GetShrinkPos Original name sputLua_GetShrinkPosition (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetShrinkPos'); was Lua_GetShrinkPos. */

void __cdecl sputLua_GetShrinkPosition(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  WalkPlane *this;
  float fVar6;
  float fVar7;
  float n;
  float radius;
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
          n = lua_getnumber(iVar3);
          radius = lua_getnumber(iVar4);
          local_c[0] = fVar6;
          local_c[1] = fVar7;
          WalkPlane_BuildCache();
          ShrinkBoxes(radius);
          this = WalkPlane_PlaneClosest(local_c,0x1000);
          if (this != (WalkPlane *)0x0) {
            WalkPlane_ClosestPoint(this,(int)local_c);
          }
          sputLua_UnShrinkBoxes();
          if (this != (WalkPlane *)0x0) {
            lua_pushnumber(local_c[0]);
            lua_pushnumber(local_c[1]);
            lua_pushnumber(n);
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


/* ---- 0x00499000  sputLua_SetSoundParametersL ---- */
/* Lua opcode: SetSoundParameters Original name sputLua_SetSoundParametersL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetSoundParameters'); was Lua_SetSoundParameters.
    */

void sputLua_SetSoundParametersL(void)

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
  set = sputRoom_GetCurrentRoom();
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
              sputRoom_SetSoundParameters(set,0x41000000,0x14,0x7f,0x3fc00000,0x3f4ccccd);
              return;
            }
          }
        }
      }
    }
    sputRoom_GetSoundParameters
              (set,&local_4,(char *)&local_8,(char *)&local_c,local_14 + 1,local_14);
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
    sputRoom_SetSoundParameters(set,PUN(undefined4,(float)(local_20[0])),uVar8,uVar7,PUN(undefined4,(float)(local_20[2])),PUN(undefined4,(float)(local_20[1])));
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


/* ---- 0x004991c0  sputLua_GetSoundParametersL ---- */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: GetSoundParameters Original name sputLua_GetSoundParametersL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetSoundParameters'); was Lua_GetSoundParameters.
    */

void sputLua_GetSoundParametersL(void)

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
  
  set = sputRoom_GetCurrentRoom();
  if (set != (void *)0x0) {
    sputRoom_GetSoundParameters(set,&local_18,(char *)&local_14,(char *)&local_c,&local_8,&local_4);
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


/* ---- 0x00499250  sputLua_SetDebugToggleCallback ---- */
/* Original name sputLua_SetDebugToggleCallback (the remaster's GrimFandango (Linux): stores
   pDebugToggleFunc); was Lua_SetDebugKeysCallback. */

void sputLua_SetDebugToggleCallback(uint param_1)

{
  g_dwDebugToggleFunc = param_1;
  return;
}

/* ---- 0x00499260  sputLua_EnginePause ---- */
/* Lua opcode: EnginePause Original name sputLua_EnginePause (the remaster's GrimFandango (Linux):
   Lua / module table entry 'EnginePause'); was Lua_EnginePause. */

void sputLua_EnginePause(void)

{
  grimlib_SetPause(1);
  return;
}

/* ---- 0x00499270  sputLua_EngineResume ---- */
/* Lua opcode: EngineResume Original name sputLua_EngineResume (the remaster's GrimFandango (Linux):
   Lua / module table entry 'EngineResume'); was Lua_EngineResume. */

void sputLua_EngineResume(void)

{
  grimlib_SetPause(0);
  return;
}

/* ---- 0x00499280  sputLua_EngineDisplay ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: EngineDisplay Original name sputLua_EngineDisplay (the remaster's GrimFandango
   (Linux): Lua / module table entry 'EngineDisplay'); was Lua_EngineDisplay. */

void sputLua_EngineDisplay(void)

{
  int iVar1;
  longlong lVar2;
  double in_stack_00000000;
  
  iVar1 = lua_lua2C(1);
  lua_getnumber(iVar1);
  lVar2 = _ftol(in_stack_00000000);
  sputRender_SetPageFlip((int)lVar2);
  return;
}
#endif


/* ---- 0x004992b0  sputLua_AllocateActorL ---- */
/* Lua opcode: LoadActor Original name sputLua_AllocateActorL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'LoadActor'); was Lua_LoadActor. */

void sputLua_AllocateActorL(void)

{
  char *pcVar1;
  
  pcVar1 = (char *)sputActor_AllocateActor();
  if (-1 < (int)pcVar1) {
    lua_pushusertag(pcVar1,0x52544341);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x004992c9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lua_pushnil();
  return;
}

/* ---- 0x004992d0  sputLua_PutActorAtInterestL ---- */
/* Lua opcode: PutActorAtInterest Original name sputLua_PutActorAtInterestL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'PutActorAtInterest'); was Lua_PutActorAtInterest.
    */

void sputLua_PutActorAtInterestL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  Actor *actor;
  void *pvVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      pvVar3 = sputRoom_GetCurrentRoom();
      if (pvVar3 != (void *)0x0) {
        iVar1 = *(int *)((int)pvVar3 + 0xac) + 0x2c + *(int *)((int)pvVar3 + 0xb4) * 300;
        local_c = *(uint *)(*(int *)((int)pvVar3 + 0xac) + 0x2c + *(int *)((int)pvVar3 + 0xb4) * 300
                           );
        local_8 = *(uint *)(iVar1 + 4);
        local_4 = *(uint *)(iVar1 + 8);
        sputActor_SetActorPosition(actor,(float *)&local_c);
      }
    }
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00499360  sputLua_SetSelectedActorL ---- */
/* Lua opcode: SetSelectedActor Original name sputLua_SetSelectedActorL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetSelectedActor'); was Lua_SetSelectedActor. */

void sputLua_SetSelectedActorL(void)

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
      pcVar3 = (char *)sputActor_SetSelectedActor(iVar1);
      if (-1 < (int)pcVar3) {
        lua_pushusertag(pcVar3,0x52544341);
        return;
      }
      lua_pushnil();
    }
  }
  return;
}

/* ---- 0x004993c0  sputLua_PutActorAtL ---- */
/* Lua opcode: PutActorAt Original name sputLua_PutActorAtL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'PutActorAt'); was Lua_PutActorAt. */

void sputLua_PutActorAtL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  Actor *actor;
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
            actor = sputActor_ActorDeref(iVar1);
            local_c[0] = lua_getnumber(iVar2);
            local_c[1] = lua_getnumber(iVar3);
            local_c[2] = lua_getnumber(iVar4);
            sputActor_SetActorPosition(actor,local_c);
          }
        }
      }
    }
  }
  return;
}
#undef local_10
#undef local_c


/* ---- 0x004994a0  sputLua_PutActorInSetL ---- */
/* Lua opcode: PutActorInSet Original name sputLua_PutActorInSetL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'PutActorInSet'); was Lua_PutActorInSet. */

void sputLua_PutActorInSetL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  Actor *actor;
  char *name;
  void *pvVar5;
  Actor *setName;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(iVar1), iVar3 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    pAVar4 = sputActor_ActorDeref(iVar1);
    iVar1 = lua_isstring(iVar2);
    if ((iVar1 == 0) && (iVar1 = lua_isnil(iVar2), iVar1 == 0)) {
      return;
    }
    setName = pAVar4;
    actor = (Actor *)lua_getstring(iVar2);
    sputRoom_AddActor(actor,(char *)setName);
    if ((((pAVar4->pExtra != (ActorExtra *)0x0) && (iVar1 = lua_isstring(iVar2), iVar1 != 0)) &&
        (pAVar4->pExtra->pPuck != (Puck *)0x0)) && (pAVar4->pExtra->nFollowBoxes != 0)) {
      name = (char *)lua_getstring(iVar2);
      pvVar5 = Res_Loaded(0x20544553,name);
      if (pvVar5 != (void *)0x0) {
        Puck_Validate(pAVar4->pExtra->pPuck);
      }
    }
  }
  return;
}

/* ---- 0x00499590  sputLua_WalkActorVectorL ---- */
/* WARNING: Variable defined which should be unmapped: local_78 */
/* Lua opcode: WalkActorVector(actor, cameraActor, x, y, z [, yawOffset]). Transforms the vector by
   the camera actor's frame, adds the actor position, turns the walker heading toward it by at most
   2 * |rate| * frameSeconds (Walker_TurnToPoint) and, if the point is less than 90 degrees from the
   heading, clears actor+8 bit 0 and calls Actor_WalkForward. Dereferences the walker without
   creating it. Original name sputLua_WalkActorVectorL (the remaster's GrimFandango (Linux): Lua /
   module table entry 'WalkActorVector'); was Lua_WalkActorVector. */

void sputLua_WalkActorVectorL(void)

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
  Actor *actor;
  Actor *actor_00;
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
          actor = sputActor_ActorDeref(iVar2);
          iVar2 = lua_getuserdata(iVar3);
          actor_00 = sputActor_ActorDeref(iVar2);
          local_54[0] = lua_getnumber(iVar4);
          local_54[1] = lua_getnumber(iVar5);
          local_54[2] = lua_getnumber(iVar6);
          pfVar9 = sputActor_GetOrientMatrix(actor_00);
          pfVar10 = local_30;
          for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
            *pfVar10 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            pfVar10 = pfVar10 + 1;
          }
          iVar2 = lua_isnumber(iVar7);
          if (iVar2 != 0) {
            local_38[0] = lua_getnumber(iVar7);
            local_c = 0;
            local_8 = 0;
            local_3c = 0;
            local_38[1] = 0.0;
            local_4 = 0;
            Matrix_BuildTransform(local_30,&local_3c);
          }
          rdMatrix_TransformVector34Acc(local_54,local_30);
          iVar2 = 3;
          pfVar9 = actor->aPos;
          pfVar10 = local_54;
          do {
            fVar1 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            iVar2 = iVar2 + -1;
            *pfVar10 = fVar1 + *pfVar10;
            pfVar10 = pfVar10 + 1;
          } while (iVar2 != 0);
          local_48[0] = local_54[0];
          local_48[1] = local_54[1];
          local_48[2] = local_54[2];
          Puck_InvXform(actor->pExtra->pPuck,local_48);
          rdVector_Normalize3Acc(local_48);
          fVar11 = stdMath_ArcSin3(local_48[1]);
          fVar1 = actor->pExtra->flTurnRate;
          if (actor->pExtra->flTurnRate < 0.0) {
            fVar1 = -fVar1;
          }
          fVar12 = sputTime_GetFrameTimeFlex();
          Puck_PointAt(actor->pExtra->pPuck,local_54,fVar12 * fVar1 + fVar12 * fVar1);
          if (90.0 - fVar11 < 90.0) {
            actor->dwMoveFlags = actor->dwMoveFlags & 0xfffffffe;
            sputActor_Forward(actor);
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


/* ---- 0x00499800  sputLua_WalkActorForwardL ---- */
/* Lua opcode: WalkActorForward Original name sputLua_WalkActorForwardL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'WalkActorForward'); was Lua_WalkActorForward. */

void sputLua_WalkActorForwardL(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      actor->dwMoveFlags = actor->dwMoveFlags & 0xfffffffe;
      sputActor_Forward(actor);
    }
  }
  return;
}

/* ---- 0x00499860  sputLua_WalkActorToL ---- */
/* Lua opcode: WalkActorTo Original name sputLua_WalkActorToL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'WalkActorTo'); was Lua_WalkActorTo. */

void sputLua_WalkActorToL(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  Actor *actor;
  Actor *pAVar7;
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
    actor = sputActor_ActorDeref(iVar1);
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
      pAVar7 = sputActor_ActorDeref(iVar1);
      local_18[0] = pAVar7->aPos[0];
      local_18[1] = pAVar7->aPos[1];
      local_18[2] = pAVar7->aPos[2];
    }
    else {
      local_18[0] = lua_getnumber(iVar2);
      local_18[1] = lua_getnumber(iVar3);
      local_18[2] = lua_getnumber(iVar4);
    }
    local_c[0] = lua_getnumber(iVar5);
    local_c[1] = lua_getnumber(iVar5);
    local_c[2] = lua_getnumber(iVar5);
    sputActor_ActorWalkTo(actor,(int)local_18,local_c,0);
  }
  return;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_c


/* ---- 0x004999d0  sputLua_WalkActorToAvoidingL ---- */
/* Lua opcode: WalkActorToAvoiding Original name sputLua_WalkActorToAvoidingL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'WalkActorToAvoiding'); was
   Lua_WalkActorToAvoiding. */

void sputLua_WalkActorToAvoidingL(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  Actor *actor;
  Actor *pAVar8;
  Actor *pAVar9;
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
    actor = sputActor_ActorDeref(iVar1);
    iVar1 = lua_getuserdata(iVar2);
    pAVar8 = sputActor_ActorDeref(iVar1);
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
      pAVar9 = sputActor_ActorDeref(iVar1);
      local_18[0] = pAVar9->aPos[0];
      local_18[1] = pAVar9->aPos[1];
      local_18[2] = pAVar9->aPos[2];
    }
    else {
      local_18[0] = lua_getnumber(iVar3);
      local_18[1] = lua_getnumber(iVar4);
      local_18[2] = lua_getnumber(iVar5);
    }
    local_c[0] = lua_getnumber(iVar6);
    local_c[1] = lua_getnumber(iVar6);
    local_c[2] = lua_getnumber(iVar6);
    sputActor_ActorWalkTo(actor,(int)local_18,local_c,pAVar8);
  }
  return;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_c


/* ---- 0x00499b80  sputLua_IsActorMovingL ---- */
/* Lua opcode: IsActorMoving Original name sputLua_IsActorMovingL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsActorMoving'); was Lua_IsActorMoving. */

void sputLua_IsActorMovingL(void)

{
  int iVar1;
  int iVar2;
  Actor *pAVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar3 = sputActor_ActorDeref(iVar1);
      if ((pAVar3->dwMoveFlags & 1) != 0) {
        lua_pushnumber(1.0);
        return;
      }
      lua_pushnil();
    }
  }
  return;
}

/* ---- 0x00499be0  sputLua_IsActorTurningL ---- */
/* Lua opcode: IsActorTurning(actor). TRUE while extra+0x28 (angle left between visible yaw and
   walker heading) is not 0. That field is written only by sputActor_AlignToPuck (0 once under 0.5
   degrees) and Actor_SetRot, so an actor without a walker is never turning. Original name
   sputLua_IsActorTurningL (the remaster's GrimFandango (Linux): Lua / module table entry
   'IsActorTurning'); was Lua_IsActorTurning. */

void sputLua_IsActorTurningL(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      if (actor->pExtra->flYawLeft != 0.0) {
        lua_pushnumber(1.0);
      }
      lua_pushnil();
    }
  }
  return;
}

/* ---- 0x00499c70  sputLua_SetActorChoreLoopingL ---- */
/* Lua opcode: SetActorChoreLooping Original name sputLua_SetActorChoreLoopingL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorChoreLooping'); was
   Lua_SetActorChoreLooping. */

void sputLua_SetActorChoreLoopingL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  void *luaObj;
  int iVar4;
  Actor *pAVar5;
  uint uVar6;
  uint uVar7;
  longlong lVar8;
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
      pAVar5 = sputActor_ActorDeref(iVar1);
      iVar1 = FindCostumeInStack(luaObj,pAVar5->pCostumes,(CostumeNode **)&local_4);
      if ((iVar1 != 0) && (local_4 != 0)) {
        iVar1 = lua_isnumber(iVar2);
        if (iVar1 != 0) {
          iVar1 = lua_isnil(iVar3);
          uVar6 = (uint)(iVar1 == 0);
          lVar8 = (longlong)lua_getnumber(iVar2);
          Cos_InstSetChoreLoop(*(int *)local_4,(uint)lVar8,uVar6);
          return;
        }
        iVar1 = lua_isnil(iVar2);
        if (iVar1 != 0) {
          uVar6 = Cos_InstCountChores(*(int *)local_4);
          lua_isnil(iVar3);
          uVar7 = 0;
          if (uVar6 != 0) {
            do {
              iVar1 = lua_isnil(iVar3);
              Cos_InstSetChoreLoop(*(int *)local_4,uVar7,(uint)(iVar1 == 0));
              uVar7 = uVar7 + 1;
            } while (uVar7 < uVar6);
          }
        }
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x00499da0  sputLua_IsActorRestingL ---- */
/* Lua opcode: IsActorResting Original name sputLua_IsActorRestingL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsActorResting'); was Lua_IsActorResting. */

void sputLua_IsActorRestingL(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      if (actor->pExtra->nResting != 0) {
        lua_pushnumber(1.0);
        return;
      }
      lua_pushnil();
    }
  }
  return;
}

/* ---- 0x00499e20  sputLua_IsActorChoringL ---- */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: IsActorChoring Original name sputLua_IsActorChoringL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsActorChoring'); was Lua_IsActorChoring. */

void sputLua_IsActorChoringL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  void *luaObj;
  int iVar4;
  Actor *pAVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  longlong lVar9;
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
    pAVar5 = sputActor_ActorDeref(iVar1);
    iVar1 = FindCostumeInStack(luaObj,pAVar5->pCostumes,(CostumeNode **)&local_c);
    if (iVar1 != 0) {
      iVar1 = lua_isnil(iVar3);
      if (local_c != 0) {
        iVar3 = lua_isnumber(iVar2);
        if (iVar3 == 0) {
          iVar2 = lua_isnil(iVar2);
          if (iVar2 != 0) {
            uVar7 = Cos_InstCountChores(*(int *)local_c);
            uVar8 = 0;
            local_8 = 0;
            uVar6 = local_8;
            if (uVar7 != 0) {
              do {
                uVar6 = Cos_InstChoreStatus(*(int *)local_c,uVar8);
                if (((uVar6 & 1) != 0) &&
                   (((iVar1 != 0 || ((uVar6 & 2) == 0)) && (local_4 = uVar8, (uVar6 & 2) != 0)))) {
                  local_8 = uVar8;
                  lua_pushnumber((float)(int)uVar8);
                  lua_pushnumber(1.0);
                  return;
                }
                uVar8 = uVar8 + 1;
                uVar6 = uVar8;
              } while (uVar8 < uVar7);
            }
            local_8 = uVar6;
            if (-1 < (int)local_4) {
              lua_pushnumber((float)(int)local_4);
              return;
            }
          }
        }
        else {
          lVar9 = (longlong)lua_getnumber(iVar2);
          uVar6 = Cos_InstChoreStatus(*(int *)local_c,(uint)lVar9);
          if ((uVar6 & 1) != 0) {
            if ((iVar1 == 0) && ((uVar6 & 2) != 0)) {
              return;
            }
            lua_pushobject(iVar2);
            if ((uVar6 & 2) != 0) {
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


/* ---- 0x00499ff0  sputLua_GetActorChoresL ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: GetActorChores Original name sputLua_GetActorChoresL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetActorChores'); was Lua_GetActorChores. */

void sputLua_GetActorChoresL(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *luaObj;
  int iVar2;
  Actor *pAVar3;
  float fVar4;
  uint uVar5;
  float fVar6;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(float (*)[3])(_frame + (0x40 - 0x14)))
  
  iVar1 = lua_lua2C(1);
  luaObj = (void *)lua_lua2C(2);
  iVar2 = lua_isuserdata(iVar1);
  if ((iVar2 != 0) && (iVar2 = lua_tag(iVar1), iVar2 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    pAVar3 = sputActor_ActorDeref(iVar1);
    iVar1 = FindCostumeInStack(luaObj,pAVar3->pCostumes,(CostumeNode **)&local_18);
    if (iVar1 == 0) {
      return;
    }
    fVar6 = 0.0;
    if (local_18 != 0) {
      iVar1 = lua_createtable();
      fVar4 = (float)Cos_InstCountChores(*(int *)local_18);
      local_14[0] = 0.0;
      local_14[2] = fVar4;
      if (fVar4 != 0.0) {
        do {
          uVar5 = Cos_InstChoreStatus(*(int *)local_18,PUN(uint,(float)fVar6));
          if ((uVar5 & 1) != 0) {
            lua_pushobject(iVar1);
            fVar4 = (float)PUN(uint,(float)fVar6);
            local_14[1] = fVar4;
            lua_pushnumber(fVar4);
            lua_pushnumber(fVar4);
            lua_settable();
            local_14[0] = (float)(PUN(int,(float)local_14[0]) + 1);
            fVar4 = local_14[2];
          }
          fVar6 = (float)(PUN(int,(float)fVar6) + 1);
        } while (PUN(uint,(float)fVar6) < PUN(uint,(float)fVar4));
      }
      lua_pushobject(iVar1);
      lua_pushstring(s_count_004ec384);
      lua_pushnumber((float)PUN(uint,(float)local_14[0]));
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

#endif


/* ---- 0x0049a160  sputLua_GetActorCostumeDepthL ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: GetActorCostumeDepth Original name sputLua_GetActorCostumeDepthL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetActorCostumeDepth'); was
   Lua_GetActorCostumeDepth. */

void sputLua_GetActorCostumeDepthL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  CostumeNode *pCVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  int iVar5;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar5 = 0;
  iVar2 = lua_lua2C(1);
  iVar3 = lua_isuserdata(iVar2);
  if ((iVar3 != 0) && (iVar3 = lua_tag(iVar2), iVar3 == 0x52544341)) {
    iVar2 = lua_getuserdata(iVar2);
    pAVar4 = sputActor_ActorDeref(iVar2);
    for (pCVar1 = pAVar4->pCostumes; pCVar1 != (CostumeNode *)0x0; pCVar1 = pCVar1->pNext) {
      iVar5 = iVar5 + 1;
    }
    lua_pushnumber((float)iVar5);
    return;
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_4


/* ---- 0x0049a2a0  sputLua_GetActorLoopingChoresL ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: GetActorLoopingChores Original name sputLua_GetActorLoopingChoresL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetActorLoopingChores'); was
   Lua_GetActorLoopingChores. */

void sputLua_GetActorLoopingChoresL(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *luaObj;
  int iVar2;
  Actor *pAVar3;
  float fVar4;
  uint uVar5;
  float fVar6;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(float (*)[3])(_frame + (0x40 - 0x14)))
  
  iVar1 = lua_lua2C(1);
  luaObj = (void *)lua_lua2C(2);
  iVar2 = lua_isuserdata(iVar1);
  if ((iVar2 != 0) && (iVar2 = lua_tag(iVar1), iVar2 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    pAVar3 = sputActor_ActorDeref(iVar1);
    iVar1 = FindCostumeInStack(luaObj,pAVar3->pCostumes,(CostumeNode **)&local_18);
    if (iVar1 == 0) {
      return;
    }
    fVar6 = 0.0;
    if (local_18 != 0) {
      iVar1 = lua_createtable();
      fVar4 = (float)Cos_InstCountChores(*(int *)local_18);
      local_14[0] = 0.0;
      local_14[2] = fVar4;
      if (fVar4 != 0.0) {
        do {
          uVar5 = Cos_InstChoreStatus(*(int *)local_18,PUN(uint,(float)fVar6));
          if (((uVar5 & 1) != 0) && ((uVar5 & 2) != 0)) {
            lua_pushobject(iVar1);
            fVar4 = (float)PUN(uint,(float)fVar6);
            local_14[1] = fVar4;
            lua_pushnumber(fVar4);
            lua_pushnumber(fVar4);
            lua_settable();
            local_14[0] = (float)(PUN(int,(float)local_14[0]) + 1);
            fVar4 = local_14[2];
          }
          fVar6 = (float)(PUN(int,(float)fVar6) + 1);
        } while (PUN(uint,(float)fVar6) < PUN(uint,(float)fVar4));
      }
      lua_pushobject(iVar1);
      lua_pushstring(s_count_004ec384);
      lua_pushnumber((float)PUN(uint,(float)local_14[0]));
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

#endif


/* ---- 0x0049a410  sputLua_SetActorColormapL ---- */
/* Source: Scripts/sputLua.cpp (line 2035, from __FILE__/__LINE__ passed to the allocator) Original
   name sputLua_SetActorColormapL (the remaster's GrimFandango (Linux): Lua / module table entry
   'SetActorColormap'); was Lua_SetActorColormap. */

void sputLua_SetActorColormapL(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *pAVar5;
  char *name;
  void *data;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(iVar2);
  if ((iVar4 != 0) && (iVar4 = lua_tag(iVar2), iVar4 == 0x52544341)) {
    iVar2 = lua_getuserdata(iVar2);
    pAVar5 = sputActor_ActorDeref(iVar2);
    iVar2 = lua_isstring(iVar3);
    if (iVar2 != 0) {
      name = (char *)lua_getstring(iVar3);
      data = sputResource_Alloc(0x50414d43,name);
      piVar1 = pAVar5->pColormapRef;
      iVar2 = *piVar1;
      if (iVar2 != 0) {
        if (iVar2 == 0) {
          (*g_pStd_HS->pAssertFail)
                    (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
        }
        if ((void *)piVar1[1] == data) {
          return;
        }
      }
      Res_RemoveReference(pAVar5->pColormapRef);
      Res_SetReference(pAVar5->pColormapRef,data,s_C__grimsrc_libs_grimlib_Scripts__004ec38c,0x7f3);
      return;
    }
    iVar2 = lua_isnil(iVar3);
    if (iVar2 != 0) {
      Res_RemoveReference(pAVar5->pColormapRef);
    }
  }
  return;
}

/* ---- 0x0049a500  sputLua_SetActorCostumeL ---- */
/* Lua opcode: SetActorCostume Original name sputLua_SetActorCostumeL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetActorCostume'); was Lua_SetActorCostume. */

void sputLua_SetActorCostumeL(void)

{
  CostumeNode *pCVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *actor;
  char *name;
  int iVar5;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar5 = 0;
  iVar4 = lua_isuserdata(iVar2);
  if ((iVar4 != 0) && (iVar4 = lua_tag(iVar2), iVar4 == 0x52544341)) {
    iVar2 = lua_getuserdata(iVar2);
    actor = sputActor_ActorDeref(iVar2);
    iVar2 = lua_isstring(iVar3);
    if (iVar2 == 0) {
      iVar2 = lua_isnil(iVar3);
      if (iVar2 != 0) {
        pCVar1 = actor->pCostumes;
        while (pCVar1 != (CostumeNode *)0x0) {
          sputActor_PopCostume(actor,1);
          pCVar1 = actor->pCostumes;
        }
        iVar5 = 1;
      }
    }
    else {
      iVar2 = 0;
      name = (char *)lua_getstring(iVar3);
      iVar5 = sputActor_SetCostume(actor,name,iVar2);
    }
    if (iVar5 != 0) {
      lua_pushnumber(1.0);
      return;
    }
    lua_pushnil();
  }
  return;
}

/* ---- 0x0049a5e0  sputLua_PrintActorCostumesL ---- */
/* Lua opcode: PrintActorCostumes Original name sputLua_PrintActorCostumesL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'PrintActorCostumes'); was Lua_PrintActorCostumes.
    */

void sputLua_PrintActorCostumesL(void)

{
  int iVar1;
  int iVar2;
  Actor *pAVar3;
  
  iVar1 = lua_lua2C(1);
  lua_lua2C(2);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar3 = sputActor_ActorDeref(iVar1);
      sputCostume_PrintCostumeInfo(pAVar3->pCostumes);
    }
  }
  return;
}

/* ---- 0x0049a640  sputLua_PushActorCostumeL ---- */
/* Lua opcode: PushActorCostume Original name sputLua_PushActorCostumeL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'PushActorCostume'); was Lua_PushActorCostume. */

void sputLua_PushActorCostumeL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  char *name;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      iVar1 = lua_isstring(iVar2);
      if (iVar1 != 0) {
        iVar1 = 0;
        name = (char *)lua_getstring(iVar2);
        sputActor_PushCostume(actor,name,iVar1);
      }
    }
  }
  return;
}

/* ---- 0x0049a6c0  sputLua_PopActorCostumeL ---- */
/* Lua opcode: PopActorCostume Original name sputLua_PopActorCostumeL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'PopActorCostume'); was Lua_PopActorCostume. */

void sputLua_PopActorCostumeL(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  char *pcVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pCostumes != (CostumeNode *)0x0) {
        pcVar3 = (char *)Cos_InstGetCostume(actor->pCostumes->dwInstance,(int *)0x0);
        lua_pushstring(pcVar3);
        sputActor_PopCostume(actor,1);
        return;
      }
      lua_pushnil();
      sputActor_PopCostume(actor,1);
    }
  }
  return;
}

/* ---- 0x0049a750  sputLua_StopActorChoreL ---- */
/* Lua opcode: StopActorChore Original name sputLua_StopActorChoreL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'StopActorChore'); was Lua_StopActorChore. */

void sputLua_StopActorChoreL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *pAVar4;
  longlong lVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar4 = sputActor_ActorDeref(iVar1);
      iVar1 = FindCostumeInStack(luaObj,pAVar4->pCostumes,(CostumeNode **)&local_4);
      if ((iVar1 != 0) && (local_4 != 0)) {
        iVar1 = lua_isnumber(iVar2);
        if (iVar1 != 0) {
          lVar5 = (longlong)lua_getnumber(iVar2);
          Cos_InstStopChore(*(int *)local_4,(uint)lVar5);
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


/* ---- 0x0049a830  sputLua_PlayActorChoreL ---- */
/* Lua opcode: PlayActorChore Original name sputLua_PlayActorChoreL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'PlayActorChore'); was Lua_PlayActorChore. */

void sputLua_PlayActorChoreL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *pAVar4;
  longlong lVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar4 = sputActor_ActorDeref(iVar1);
      iVar1 = FindCostumeInStack(luaObj,pAVar4->pCostumes,(CostumeNode **)&local_4);
      if (iVar1 != 0) {
        if (local_4 != 0) {
          iVar1 = lua_isnumber(iVar2);
          if (iVar1 != 0) {
            iVar3 = 0;
            iVar1 = 0;
            lVar5 = (longlong)lua_getnumber(iVar2);
            iVar1 = Cos_InstPlayChore(*(int *)local_4,(uint)lVar5,iVar1,iVar3);
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


/* ---- 0x0049a910  sputLua_CompleteActorChoreL ---- */
/* Lua opcode: CompleteActorChore Original name sputLua_CompleteActorChoreL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'CompleteActorChore'); was Lua_CompleteActorChore.
    */

void sputLua_CompleteActorChoreL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *pAVar4;
  longlong lVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar4 = sputActor_ActorDeref(iVar1);
      iVar1 = FindCostumeInStack(luaObj,pAVar4->pCostumes,(CostumeNode **)&local_4);
      if (iVar1 != 0) {
        if (local_4 != 0) {
          iVar1 = lua_isnumber(iVar2);
          if (iVar1 != 0) {
            lVar5 = (longlong)lua_getnumber(iVar2);
            iVar1 = Cos_InstCompleteChore(*(int *)local_4,(uint)lVar5);
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


/* ---- 0x0049a9e0  sputLua_PlayActorChoreLoopingL ---- */
/* Lua opcode: PlayActorChoreLooping Original name sputLua_PlayActorChoreLoopingL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'PlayActorChoreLooping'); was
   Lua_PlayActorChoreLooping. */

void sputLua_PlayActorChoreLoopingL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *pAVar4;
  longlong lVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar4 = sputActor_ActorDeref(iVar1);
      iVar1 = FindCostumeInStack(luaObj,pAVar4->pCostumes,(CostumeNode **)&local_4);
      if (iVar1 != 0) {
        if (local_4 != 0) {
          iVar1 = lua_isnumber(iVar2);
          if (iVar1 != 0) {
            iVar3 = 0;
            iVar1 = 1;
            lVar5 = (longlong)lua_getnumber(iVar2);
            iVar1 = Cos_InstPlayChore(*(int *)local_4,(uint)lVar5,iVar1,iVar3);
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


/* ---- 0x0049aac0  sputLua_ActorLookAtL ---- */
/* Lua opcode: ActorLookAt Original name sputLua_ActorLookAtL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'ActorLookAt'); was Lua_ActorLookAt. */

void sputLua_ActorLookAtL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ActorExtra *pAVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  Actor *actor;
  Actor *pAVar7;
  float fVar8;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_lua2C(3);
  lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  iVar6 = lua_isuserdata(iVar2);
  if ((iVar6 != 0) && (iVar6 = lua_tag(iVar2), iVar6 == 0x52544341)) {
    iVar2 = lua_getuserdata(iVar2);
    actor = sputActor_ActorDeref(iVar2);
    if (actor->pExtra == (ActorExtra *)0x0) {
      sputActor_AllocateActorExtra(actor);
    }
    if (actor->pCostumes != (CostumeNode *)0x0) {
      iVar2 = lua_isnumber(iVar5);
      if (iVar2 != 0) {
        fVar8 = lua_getnumber(iVar5);
        actor->pCostumes->flLookRate = fVar8;
      }
      iVar2 = lua_isnil(iVar3);
      if (iVar2 == 0) {
        iVar2 = lua_isnumber(iVar3);
        if (iVar2 != 0) {
          iVar2 = lua_lua2C(3);
          iVar4 = lua_lua2C(4);
          fVar8 = lua_getnumber(iVar3);
          actor->pExtra->aLookAt[0] = fVar8;
          iVar3 = lua_isnumber(iVar2);
          if (iVar3 == 0) {
            fVar8 = 0.0;
          }
          else {
            fVar8 = lua_getnumber(iVar2);
          }
          actor->pExtra->aLookAt[1] = fVar8;
          iVar2 = lua_isnumber(iVar4);
          if (iVar2 != 0) {
            fVar8 = lua_getnumber(iVar4);
            actor->pExtra->aLookAt[2] = fVar8;
            actor->dwMoveFlags = actor->dwMoveFlags | 2;
            return;
          }
          actor->pExtra->aLookAt[2] = 0.0;
          actor->dwMoveFlags = actor->dwMoveFlags | 2;
          return;
        }
        iVar2 = lua_isuserdata(iVar3);
        if (iVar2 == 0) {
          return;
        }
        iVar2 = lua_tag(iVar3);
        if (iVar2 != 0x52544341) {
          return;
        }
        iVar2 = lua_getuserdata(iVar3);
        pAVar7 = sputActor_ActorDeref(iVar2);
        pAVar1 = actor->pExtra;
        pAVar1->aLookAt[0] = pAVar7->aPos[0];
        pAVar1->aLookAt[1] = pAVar7->aPos[1];
        pAVar1->aLookAt[2] = pAVar7->aPos[2];
        iVar2 = lua_isnumber(iVar4);
        if (iVar2 != 0) {
          fVar8 = lua_getnumber(iVar4);
          actor->pCostumes->flLookRate = fVar8;
        }
      }
      else {
        pAVar1 = actor->pExtra;
        if (((pAVar1->aLookAt[0] == 0.0) && (pAVar1->aLookAt[1] == 0.0)) &&
           (pAVar1->aLookAt[2] == 0.0)) {
          return;
        }
        pAVar1->aLookAt[0] = 0.0;
        pAVar1->aLookAt[1] = 0.0;
        pAVar1->aLookAt[2] = 0.0;
        iVar2 = lua_isnumber(iVar4);
        if (iVar2 != 0) {
          fVar8 = lua_getnumber(iVar4);
          actor->pCostumes->flLookRate = fVar8;
          actor->dwMoveFlags = actor->dwMoveFlags | 2;
          return;
        }
      }
      actor->dwMoveFlags = actor->dwMoveFlags | 2;
    }
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x0049ad30  sputLua_IsActorLookingL ---- */
/* Lua opcode: IsActorLooking Original name sputLua_IsActorLookingL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsActorLooking'); was Lua_IsActorLooking. */

void sputLua_IsActorLookingL(void)

{
  int iVar1;
  int iVar2;
  Actor *pAVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar3 = sputActor_ActorDeref(iVar1);
      if ((pAVar3->dwMoveFlags & 2) != 0) {
        lua_pushnumber(1.0);
        return;
      }
      lua_pushnil();
    }
  }
  return;
}

/* ---- 0x0049ad90  sputLua_SetActorLookRate ---- */
/* Lua opcode: SetActorLookRate Original name sputLua_SetActorLookRate (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetActorLookRate'); was Lua_SetActorLookRate. */

void sputLua_SetActorLookRate(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(iVar2);
      if (iVar3 != 0) {
        iVar1 = lua_getuserdata(iVar1);
        pAVar4 = sputActor_ActorDeref(iVar1);
        if (pAVar4->pCostumes != (CostumeNode *)0x0) {
          fVar5 = lua_getnumber(iVar2);
          pAVar4->pCostumes->flLookRate = fVar5;
        }
      }
    }
  }
  return;
}

/* ---- 0x0049ae10  sputLua_GetActorLookRate ---- */
/* Lua opcode: GetActorLookRate Original name sputLua_GetActorLookRate (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetActorLookRate'); was Lua_GetActorLookRate. */

void sputLua_GetActorLookRate(void)

{
  int iVar1;
  int iVar2;
  Actor *pAVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar3 = sputActor_ActorDeref(iVar1);
      if (pAVar3->pCostumes != (CostumeNode *)0x0) {
        lua_pushnumber(pAVar3->pCostumes->flLookRate);
        return;
      }
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0049ae80  sputLua_SetActorVisibilityL ---- */
/* Lua opcode: SetActorVisibility Original name sputLua_SetActorVisibilityL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorVisibility'); was Lua_SetActorVisibility.
    */

void sputLua_SetActorVisibilityL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar4 = sputActor_ActorDeref(iVar1);
      if (iVar2 != 0) {
        iVar1 = lua_isnil(iVar2);
        if (iVar1 == 0) {
          pAVar4->dwFlags = pAVar4->dwFlags & 0xfffffffd;
          return;
        }
      }
      pAVar4->dwFlags = pAVar4->dwFlags | 2;
    }
  }
  return;
}

/* ---- 0x0049af00  sputLua_SetActorFollowBoxesL ---- */
/* Lua opcode: SetActorFollowBoxes Original name sputLua_SetActorFollowBoxesL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorFollowBoxes'); was
   Lua_SetActorFollowBoxes. */

void sputLua_SetActorFollowBoxesL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  int iVar4;
  
  iVar4 = 1;
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 == 0) {
    return;
  }
  iVar3 = lua_tag(iVar1);
  if (iVar3 == 0x52544341) {
    iVar1 = lua_getuserdata(iVar1);
    actor = sputActor_ActorDeref(iVar1);
    if ((iVar2 == 0) || (iVar1 = lua_isnil(iVar2), iVar1 != 0)) {
      iVar4 = 0;
    }
    sputActor_EnableWalkSystem(actor,iVar4);
    return;
  }
  return;
}

/* ---- 0x0049af80  sputLua_ShutUpActorL ---- */
/* Lua opcode: ShutUpActor Original name sputLua_ShutUpActorL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'ShutUpActor'); was Lua_ShutUpActor. */

void sputLua_ShutUpActorL(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor != (Actor *)0x0) {
        sputActor_ShutUp(actor);
      }
    }
  }
  return;
}

/* ---- 0x0049afd0  sputLua_SetActorFrustrumCull ---- */
/* Lua opcode: SetActorFrustrumCull Original name sputLua_SetActorFrustrumCull (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorFrustrumCull'); was
   Lua_SetActorFrustrumCull. */

void sputLua_SetActorFrustrumCull(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      lVar4 = (longlong)lua_getnumber(iVar2);
      sputActor_SetFrustrumCull(actor,(int)lVar4);
    }
  }
  return;
}

/* ---- 0x0049b040  sputLua_GetCameraActorL ---- */
/* Lua opcode: GetCameraActor Original name sputLua_GetCameraActorL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetCameraActor'); was Lua_GetCameraActor. */

void sputLua_GetCameraActorL(void)

{
  lua_pushusertag((char *)g_nCamActorIndex,0x52544341);
  return;
}

/* ---- 0x0049b060  sputLua_GetActorWalkRateL ---- */
/* Lua opcode: GetActorWalkRate Original name sputLua_GetActorWalkRateL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetActorWalkRate'); was Lua_GetActorWalkRate. */

void sputLua_GetActorWalkRateL(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      lua_pushnumber(actor->pExtra->flWalkRate);
    }
  }
  return;
}

/* ---- 0x0049b0d0  sputLua_SetActorWalkRateL ---- */
/* Lua opcode: SetActorWalkRate Original name sputLua_SetActorWalkRateL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetActorWalkRate'); was Lua_SetActorWalkRate. */

void sputLua_SetActorWalkRateL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
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
        actor = sputActor_ActorDeref(iVar1);
        if (actor->pExtra == (ActorExtra *)0x0) {
          sputActor_AllocateActorExtra(actor);
        }
        fVar4 = lua_getnumber(iVar2);
        actor->pExtra->flWalkRate = fVar4;
      }
    }
  }
  return;
}

/* ---- 0x0049b160  sputLua_GetActorTurnRateL ---- */
/* Lua opcode: GetActorTurnRate Original name sputLua_GetActorTurnRateL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetActorTurnRate'); was Lua_GetActorTurnRate. */

void sputLua_GetActorTurnRateL(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      lua_pushnumber(actor->pExtra->flTurnRate);
    }
  }
  return;
}

/* ---- 0x0049b1d0  sputLua_SetActorTurnRateL ---- */
/* Lua opcode: SetActorTurnRate(actor, rate). Stores the rate at extra+0x1c, keeping the sign of the
   current rate (a negative rate is the pending snap flag). The value itself is not made absolute
   here; readers take |rate|. Original name sputLua_SetActorTurnRateL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetActorTurnRate'); was Lua_SetActorTurnRate. */

void sputLua_SetActorTurnRateL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
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
        actor = sputActor_ActorDeref(iVar1);
        if (actor->pExtra == (ActorExtra *)0x0) {
          sputActor_AllocateActorExtra(actor);
        }
        if (actor->pExtra->flTurnRate < 0.0) {
          fVar4 = fVar4 * -1.0;
        }
        actor->pExtra->flTurnRate = fVar4;
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049b280  sputLua_SetActorWalkChoresL ---- */
/* Lua opcode: SetActorWalkChore Original name sputLua_SetActorWalkChoresL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorWalkChore'); was Lua_SetActorWalkChore.
    */

void sputLua_SetActorWalkChoresL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *actor;
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
    actor = sputActor_ActorDeref(iVar1);
    iVar1 = FindCostumeInStack(luaObj,actor->pCostumes,(CostumeNode **)&local_4);
    if (iVar1 != 0) {
      iVar1 = lua_isnumber(iVar2);
      if (iVar1 == 0) {
        iVar1 = -1;
      }
      else {
        lVar4 = (longlong)lua_getnumber(iVar2);
        iVar1 = (int)lVar4;
      }
      sputActor_SetWalkChore(actor,iVar1,(CostumeNode *)local_4);
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049b350  sputLua_SetActorTurnChoresL ---- */
/* Lua opcode: SetActorTurnChores Original name sputLua_SetActorTurnChoresL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorTurnChores'); was Lua_SetActorTurnChores.
    */

void sputLua_SetActorTurnChoresL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  void *luaObj;
  int iVar4;
  Actor *actor;
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
          actor = sputActor_ActorDeref(iVar1);
          iVar1 = FindCostumeInStack(luaObj,actor->pCostumes,(CostumeNode **)&local_4);
          if (iVar1 != 0) {
            lVar5 = (longlong)lua_getnumber(iVar3);
            iVar1 = (int)lVar5;
            lVar5 = (longlong)lua_getnumber(iVar2);
            sputActor_SetTurnChores(actor,(int)lVar5,iVar1,(CostumeNode *)local_4);
          }
        }
      }
    }
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x0049b430  sputLua_SetActorRestChoreL ---- */
/* Lua opcode: SetActorRestChore Original name sputLua_SetActorRestChoreL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorRestChore'); was Lua_SetActorRestChore.
    */

void sputLua_SetActorRestChoreL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *actor;
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
    actor = sputActor_ActorDeref(iVar1);
    iVar1 = FindCostumeInStack(luaObj,actor->pCostumes,(CostumeNode **)&local_4);
    if (iVar1 != 0) {
      iVar1 = lua_isnil(iVar2);
      if (iVar1 == 0) {
        lVar4 = (longlong)lua_getnumber(iVar2);
        iVar1 = (int)lVar4;
      }
      else {
        iVar1 = -1;
      }
      sputActor_SetRestChore(actor,iVar1,(CostumeNode *)local_4);
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049b500  sputLua_SetActorMumbleChoreL ---- */
/* Lua opcode: SetActorMumblechore Original name sputLua_SetActorMumbleChoreL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorMumblechore'); was
   Lua_SetActorMumblechore. */

void sputLua_SetActorMumbleChoreL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *pAVar4;
  longlong lVar5;
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
        lVar5 = (longlong)lua_getnumber(iVar2);
        iVar1 = lua_getuserdata(iVar1);
        pAVar4 = sputActor_ActorDeref(iVar1);
        iVar1 = FindCostumeInStack(luaObj,pAVar4->pCostumes,(CostumeNode **)&local_4);
        if ((iVar1 != 0) && (local_4 != 0)) {
          *(int *)(local_4 + 0x78) = (int)lVar5;
        }
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049b5a0  sputLua_SetActorTalkChoreL ---- */
/* Lua opcode: SetActorTalkChore Original name sputLua_SetActorTalkChoreL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorTalkChore'); was Lua_SetActorTalkChore.
    */

void sputLua_SetActorTalkChoreL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  void *luaObj;
  int iVar4;
  Actor *pAVar5;
  undefined4 uVar6;
  longlong lVar7;
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
    lVar7 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar7;
    if ((0 < iVar2) && (iVar2 < 0x11)) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar5 = sputActor_ActorDeref(iVar1);
      iVar1 = FindCostumeInStack(luaObj,pAVar5->pCostumes,(CostumeNode **)&local_4);
      if ((iVar1 != 0) && (local_4 != 0)) {
        iVar1 = lua_isnumber(iVar3);
        if (iVar1 == 0) {
          uVar6 = 0xffffffff;
        }
        else {
          lVar7 = (longlong)lua_getnumber(iVar3);
          uVar6 = (undefined4)lVar7;
        }
        *(undefined4 *)(local_4 + 0x34 + iVar2 * 4) = uVar6;
        lua_isnil(iVar3);
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049b6c0  sputLua_SetActorHeadL ---- */
/* WARNING: Variable defined which should be unmapped: local_24 */
/* WARNING: Variable defined which should be unmapped: local_28 */
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: SetActorHead Original name sputLua_SetActorHeadL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetActorHead'); was Lua_SetActorHead. */

void sputLua_SetActorHeadL(void)

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
  Actor *actor;
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
                  actor = sputActor_ActorDeref(iVar1);
                  maxYaw = lua_getnumber(iVar7);
                  maxPitch = lua_getnumber(iVar6);
                  maxRoll = lua_getnumber(iVar5);
                  lVar9 = (longlong)lua_getnumber(iVar4);
                  iVar1 = (int)lVar9;
                  lVar9 = (longlong)lua_getnumber(iVar3);
                  iVar3 = (int)lVar9;
                  lVar9 = (longlong)lua_getnumber(iVar2);
                  sputActor_SetActorHead(actor,(int)lVar9,iVar3,iVar1,maxRoll,maxPitch,maxYaw);
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


/* ---- 0x0049b830  sputLua_CanActorSeeL ---- */
/* Lua opcode: CanActorSee Original name sputLua_CanActorSeeL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'CanActorSee'); was Lua_CanActorSee. */

void sputLua_CanActorSeeL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *target;
  Actor *target_00;
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
  target = sputActor_ActorDeref(iVar1);
  local_10 = (uint)target;
  iVar1 = lua_isnumber(iVar2);
  if (iVar1 == 0) {
    iVar1 = lua_isuserdata(iVar2);
    if ((iVar1 == 0) || (iVar1 = lua_tag(iVar2), iVar1 != 0x52544341)) {
      iVar1 = lua_isnil(iVar2);
      if (iVar1 == 0) {
        return;
      }
      if (g_pSelectedActor == (Actor *)0x0) {
        return;
      }
      iVar1 = sputActor_CanActorSeeActor(g_pSelectedActor,target,&local_14);
      if (iVar1 != 0) {
        lua_pushnumber(local_14);
        return;
      }
    }
    else {
      iVar1 = lua_getuserdata(iVar2);
      target_00 = sputActor_ActorDeref(iVar1);
      iVar1 = sputActor_CanActorSeeActor(target,target_00,&local_14);
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
    iVar1 = sputActor_CanActorSeePoint((Actor *)local_10,local_c,&local_14);
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


/* ---- 0x0049b9e0  sputLua_GetVisibleThingsL ---- */
/* Lua opcode: GetVisibleThings Original name sputLua_GetVisibleThingsL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetVisibleThings'); was Lua_GetVisibleThings. */

void sputLua_GetVisibleThingsL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Actor *target;
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
      local_8 = (uint)sputActor_ActorDeref(iVar1);
    }
  }
  else {
    local_8 = (uint)g_pSelectedActor;
    if (g_pSelectedActor == (Actor *)0x0) {
      return;
    }
  }
  iVar1 = lua_createtable();
  if (*(char *)(local_8 + 0x7c) == '\0') {
    lua_pushobject(iVar1);
  }
  for (piVar3 = GetRoomActors((char *)(local_8 + 0x7c)); piVar3 != (int *)0x0;
      piVar3 = (int *)piVar3[2]) {
    target = g_pActors + *piVar3;
    if ((((target != (Actor *)0x0) && (target != (Actor *)local_8)) &&
        ((*(byte *)(local_8 + 4) & 1) == 0)) &&
       (iVar2 = sputActor_CanActorSeeActor((Actor *)local_8,target,&local_4), iVar2 != 0)) {
      lua_pushobject(iVar1);
      uVar5 = 0x52544341;
      pcVar4 = (char *)sputActor_GetActorHandle(target,0x52544341);
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


/* ---- 0x0049bb10  sputLua_GetActorRectL ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetActorRect Original name sputLua_GetActorRectL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetActorRect'); was Lua_GetActorRect. */

void sputLua_GetActorRectL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  Actor *pAVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar3 = sputActor_ActorDeref(iVar1);
      if ((pAVar3 != (Actor *)0x0) && (pAVar3->nScreenBoxValid != 0)) {
        lua_pushnumber((float)pAVar3->aScreenBox[0]);
        lua_pushnumber((float)pAVar3->aScreenBox[1]);
        lua_pushnumber((float)pAVar3->aScreenBox[2]);
        lua_pushnumber((float)pAVar3->aScreenBox[3]);
        return;
      }
      lua_pushnil();
    }
  }
  return;
}
#undef local_c


/* ---- 0x0049bba0  sputLua_GetActorPuckVectorL ---- */
/* Lua opcode: GetActorPuckVector Original name sputLua_GetActorPuckVectorL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetActorPuckVector'); was Lua_GetActorPuckVector.
    */

void sputLua_GetActorPuckVectorL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Puck *pPVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *actor;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(iVar2);
  if ((iVar4 != 0) && (iVar4 = lua_tag(iVar2), iVar4 == 0x52544341)) {
    iVar3 = lua_isnil(iVar3);
    iVar2 = lua_getuserdata(iVar2);
    actor = sputActor_ActorDeref(iVar2);
    if (actor->pExtra == (ActorExtra *)0x0) {
      sputActor_AllocateActorExtra(actor);
    }
    if ((actor != (Actor *)0x0) && (pPVar1 = actor->pExtra->pPuck, pPVar1 != (Puck *)0x0)) {
      local_c[0] = pPVar1->aFrame[3];
      local_c[1] = pPVar1->aFrame[4];
      local_c[2] = pPVar1->aFrame[5];
      if (iVar3 == 0) {
        local_c[0] = local_c[0] + pPVar1->aPos[0];
        local_c[1] = pPVar1->aPos[1] + local_c[1];
        local_c[2] = pPVar1->aPos[2] + local_c[2];
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


/* ---- 0x0049bcc0  sputLua_GetActorYawToPoint ---- */
/* Lua opcode: GetActorYawToPoint(actor, x, y, z | {x, y, z}). Creates the extra and the walker if
   missing, then returns Actor_GetYawToPoint. Original name sputLua_GetActorYawToPoint (the
   remaster's GrimFandango (Linux): Lua / module table entry 'GetActorYawToPoint'); was
   Lua_GetActorYawToPoint. */

void sputLua_GetActorYawToPoint(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  int iVar4;
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
      actor = sputActor_ActorDeref(iVar1);
      iVar1 = lua_istable(iVar2);
      if (iVar1 == 0) {
        iVar1 = lua_lua2C(3);
        iVar3 = lua_lua2C(4);
      }
      else {
        lua_pushobject(iVar2);
        lua_pushstring(&DAT_004e8454);
        iVar4 = lua_gettable();
        lua_pushobject(iVar2);
        lua_pushstring(&DAT_004e8450);
        iVar1 = lua_gettable();
        lua_pushobject(iVar2);
        lua_pushstring(&DAT_004ec3b8);
        iVar3 = lua_gettable();
        iVar2 = iVar4;
      }
      local_c[0] = lua_getnumber(iVar2);
      local_c[1] = lua_getnumber(iVar1);
      local_c[2] = lua_getnumber(iVar3);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      if (actor->pExtra->pPuck == (Puck *)0x0) {
        sputActor_EnablePuck(actor,1);
      }
      n = Puck_GetYawToPoint(actor->pExtra->pPuck,local_c);
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


/* ---- 0x0049be40  sputLua_SetActorReflection ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: SetActorReflection Original name sputLua_SetActorReflection (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorReflection'); was Lua_SetActorReflection.
    */

void sputLua_SetActorReflection(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  float angle;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      angle = lua_getnumber(iVar2);
      sputActor_SetReflection(actor,angle);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_c


/* ---- 0x0049bec0  sputLua_GetActorPosL ---- */
/* Lua opcode: GetActorPos Original name sputLua_GetActorPosL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'GetActorPos'); was Lua_GetActorPos. */

void sputLua_GetActorPosL(void)

{
  int iVar1;
  int iVar2;
  Actor *pAVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar3 = sputActor_ActorDeref(iVar1);
      lua_pushnumber(pAVar3->aPos[0]);
      lua_pushnumber(pAVar3->aPos[1]);
      lua_pushnumber(pAVar3->aPos[2]);
    }
  }
  return;
}

/* ---- 0x0049bf30  sputLua_GetActorRotL ---- */
/* Lua opcode: GetActorRot Original name sputLua_GetActorRotL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'GetActorRot'); was Lua_GetActorRot. */

void sputLua_GetActorRotL(void)

{
  int iVar1;
  int iVar2;
  Actor *pAVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar3 = sputActor_ActorDeref(iVar1);
      lua_pushnumber(pAVar3->aRot[0]);
      lua_pushnumber(pAVar3->aRot[1]);
      lua_pushnumber(pAVar3->aRot[2]);
    }
  }
  return;
}

/* ---- 0x0049bfa0  sputLua_SetActorRotL ---- */
/* Lua opcode: SetActorRot Original name sputLua_SetActorRotL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'SetActorRot'); was Lua_SetActorRot. */

void sputLua_SetActorRotL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  Actor *actor;
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
            actor = sputActor_ActorDeref(iVar1);
            local_c[0] = lua_getnumber(iVar2);
            local_c[1] = lua_getnumber(iVar3);
            local_c[2] = lua_getnumber(iVar4);
            iVar1 = lua_isnil(iVar5);
            sputActor_SetActorRotation(actor,local_c,iVar1);
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


/* ---- 0x0049c0a0  sputLua_SetActorPitch ---- */
/* Lua opcode: SetActorPitch Original name sputLua_SetActorPitch (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetActorPitch'); was Lua_SetActorPitch. */

void sputLua_SetActorPitch(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar4 = sputActor_ActorDeref(iVar1);
      fVar5 = lua_getnumber(iVar2);
      pAVar4->aRot[0] = fVar5;
      pAVar4->nMatrixDirty = 0;
    }
  }
  return;
}

/* ---- 0x0049c110  sputLua_SetActorRoll ---- */
/* Lua opcode: SetActorRoll Original name sputLua_SetActorRoll (the remaster's GrimFandango (Linux):
   Lua / module table entry 'SetActorRoll'); was Lua_SetActorRoll. */

void sputLua_SetActorRoll(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar4 = sputActor_ActorDeref(iVar1);
      fVar5 = lua_getnumber(iVar2);
      pAVar4->aRot[2] = fVar5;
      pAVar4->nMatrixDirty = 0;
    }
  }
  return;
}

/* ---- 0x0049c180  sputLua_TurnActorL ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: TurnActor Original name sputLua_TurnActorL (the remaster's GrimFandango (Linux): Lua
   / module table entry 'TurnActor'); was Lua_TurnActor. */

void sputLua_TurnActorL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
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
        actor = sputActor_ActorDeref(iVar1);
        actor->dwMoveFlags = actor->dwMoveFlags & 0xfffffffe;
        fVar4 = lua_getnumber(iVar2);
        sputActor_Turn(actor,fVar4);
      }
    }
  }
  return;
}
#undef local_c


/* ---- 0x0049c200  sputLua_GetActorSectorL ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetActorSector Original name sputLua_GetActorSectorL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetActorSector'); was Lua_GetActorSector. */

void sputLua_GetActorSectorL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  WalkPlane *pWVar5;
  longlong lVar6;
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
        pAVar4 = sputActor_ActorDeref(iVar1);
        lVar6 = (longlong)lua_getnumber(iVar2);
        pWVar5 = WalkPlane_PlaneAt(pAVar4->aPos,(uint)lVar6);
        if (pWVar5 != (WalkPlane *)0x0) {
          lua_pushnumber((float)pWVar5->nId);
          lua_pushstring(pWVar5->aName);
          lua_pushnumber((float)(int)pWVar5->dwType);
          return;
        }
        lua_pushnil();
      }
    }
  }
  return;
}
#undef local_c


/* ---- 0x0049c2c0  sputLua_IsActorInSector ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: IsActorInSector Original name sputLua_IsActorInSector (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsActorInSector'); was Lua_IsActorInSector. */

void sputLua_IsActorInSector(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  WalkPlane *this;
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
        pAVar4 = sputActor_ActorDeref(iVar1);
        iVar1 = lua_getstring(iVar2);
        this = g_pWalkPlane_wp_head;
        if (g_pWalkPlane_wp_head != (WalkPlane *)0x0) {
          do {
            iVar2 = String_ContainsSubstring(this,iVar1);
            if (iVar2 != 0) {
              iVar2 = WalkPlane_Within(this,pAVar4->aPos,1);
              if (iVar2 != 0) {
                lua_pushnumber((float)this->nId);
                lua_pushstring(this->aName);
                lua_pushnumber((float)(int)this->dwType);
                return;
              }
            }
            this = this->pNext;
          } while (this != (WalkPlane *)0x0);
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


/* ---- 0x0049c4c0  sputLua_IsPointInSector ---- */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: IsPointInSector Original name sputLua_IsPointInSector (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsPointInSector'); was Lua_IsPointInSector. */

void sputLua_IsPointInSector(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  WalkPlane *this;
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
    this = g_pWalkPlane_wp_head;
    if (g_pWalkPlane_wp_head != (WalkPlane *)0x0) {
      do {
        iVar2 = String_ContainsSubstring(this,iVar1);
        if ((iVar2 != 0) && (iVar2 = WalkPlane_Within(this,local_c,1), iVar2 != 0)) {
          lua_pushnumber((float)this->nId);
          lua_pushstring(this->aName);
          lua_pushnumber((float)(int)this->dwType);
          break;
        }
        this = this->pNext;
      } while (this != (WalkPlane *)0x0);
      if (this != (WalkPlane *)0x0) {
        return;
      }
    }
  }
  lua_pushnil();
  return;
}
#undef local_20
#undef local_c


/* ---- 0x0049c5e0  sputLua_FindSystemFiles ---- */
/* lua_dofile('_system.lua') Original name sputLua_FindSystemFiles (the remaster's GrimFandango
   (Linux): the only call of grimlib_FindSystemFiles, same body (lua_dofile of _system.lua)); was
   Lua_RunSystemScript. */

int sputLua_FindSystemFiles(void)

{
  int iVar1;
  
  iVar1 = lua_dofile(s__system_lua_004ec3bc);
  return iVar1 == 0;
}

/* ---- 0x0049c600  sputLua_Boot ---- */
/* Calls the global Lua function named by the string at 0x004ec3c8 with (flag, str) Original name
   sputLua_Boot (the remaster's GrimFandango (Linux): the boot-script call of grimlib_Open, same
   body (pushes the flag and string, calls the boot global)); was Lua_CallSystemFunction. */

int __cdecl sputLua_Boot(int flag,char *str)

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

/* ---- 0x0049c660  sputLua_CameraChange ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* system.camChangeHandler(from, to) Original name sputLua_CameraChange (the remaster's GrimFandango
   (Linux): aligned call in grimlib_MakeCurrentSetup); was Lua_CallCamChangeHandler. */

void __cdecl sputLua_CameraChange(int fromSetup,int toSetup)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  lua_beginblock();
  iVar1 = lua_getref(g_nLrSystemTable);
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


/* ---- 0x0049c6e0  sputLua_PostCameraChange ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* system.postCamChangeHandler(setup) Original name sputLua_PostCameraChange (the remaster's
   GrimFandango (Linux): strings: 'postCamChangeHandler'); was Lua_CallPostCamChangeHandler. */

void __cdecl sputLua_PostCameraChange(int setup)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  lua_beginblock();
  iVar1 = lua_getref(g_nLrSystemTable);
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


/* ---- 0x0049ca60  sputLua_RegisterFunctions ---- */
/* lua_openlib() wrapper used to register the 279-entry engine opcode table at 0x004ea8b0 Original
   name sputLua_RegisterFunctions (the remaster's GrimFandango (Linux): aligned call in
   sputLua_Startup, sputPrimitive_Startup, sputText_Startup); was Lua_OpenEngineLib. */

void sputLua_RegisterFunctions(int *param_1,int param_2)

{
  lua_openlib(param_1,param_2);
  return;
}

/* ---- 0x0049ca80  sputLua_JustLoadedL ---- */
/* Lua opcode: JustLoaded Original name sputLua_JustLoadedL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'JustLoaded'); was Lua_JustLoaded. */

void sputLua_JustLoadedL(void)

{
  int iVar1;
  
  iVar1 = grimlib_JustLoaded();
  if (iVar1 != 0) {
    lua_pushnumber(1.0);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0049ca98. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lua_pushnil();
  return;
}

/* ---- 0x0049caa0  sputLua_ActorVoiceIs3DL ---- */
/* Lua opcode: ActorVoiceIs3D Original name sputLua_ActorVoiceIs3DL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ActorVoiceIs3D'); was Lua_ActorVoiceIs3D. */

void sputLua_ActorVoiceIs3DL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    lua_tag(iVar1);
  }
  iVar1 = lua_getuserdata(iVar1);
  pAVar4 = sputActor_ActorDeref(iVar1);
  iVar1 = lua_isnil(iVar2);
  if (iVar1 != 0) {
    pAVar4->dwFlags = pAVar4->dwFlags & 0xfffffff7;
    return;
  }
  pAVar4->dwFlags = pAVar4->dwFlags | 8;
  return;
}

/* ---- 0x0049cb10  FindCostumeInStack ---- */
/* Turns the optional costume argument of the chore opcodes (nil, index or name) into the costume
   record in the actor's list Original name FindCostumeInStack (the remaster's GrimFandango (Linux):
   the only unmatched callee of Lua_GetActorChores; the only unmatched callee of
   Lua_GetActorLoopingChores; 15 matched neighbours agree, 0 disagree); was Lua_ResolveCostumeArg.
    */

int __cdecl FindCostumeInStack(void *luaObj,CostumeNode *costumeList,CostumeNode **outCostume)

{
  CostumeNode *pCVar1;
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
    pCVar1 = *outCostume;
    while (pCVar1 != (CostumeNode *)0x0) {
      iVar4 = iVar2;
      iVar3 = Cos_InstGetCostume((*outCostume)->dwInstance,(int *)0x0);
      iVar4 = _stricmp(iVar3,iVar4);
      if (iVar4 == 0) break;
      pCVar1 = (*outCostume)->pNext;
      *outCostume = pCVar1;
    }
  }
  else {
    lVar5 = (longlong)lua_getnumber((int)luaObj);
    iVar2 = (int)lVar5;
    if (*outCostume != (CostumeNode *)0x0) {
      while (0 < iVar2) {
        pCVar1 = (*outCostume)->pNext;
        *outCostume = pCVar1;
        iVar2 = iVar2 + -1;
        if (pCVar1 == (CostumeNode *)0x0) {
          return 0;
        }
      }
    }
  }
  return (uint)(*outCostume != (CostumeNode *)0x0);
}

/* ---- 0x0049cca0  sputLua_CheckForFileL ---- */
/* Lua opcode: CheckForFile Original name sputLua_CheckForFileL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'CheckForFile'); was Lua_CheckForFile. */

void sputLua_CheckForFileL(void)

{
  void **ppvVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_isstring(iVar2);
  if (iVar3 != 0) {
    puVar4 = &DAT_004dda54;
    ppvVar1 = &g_pSputLuaHS->pFopen;
    iVar2 = lua_getstring(iVar2);
    iVar2 = (*(code *)*ppvVar1)(iVar2,puVar4);
    if (iVar2 == 0) {
      lua_pushnil();
      return;
    }
    (*g_pSputLuaHS->pFclose)(iVar2);
    lua_pushnumber(1.0);
  }
  return;
}

/* ---- 0x0049cd10  sputLua_NukeResourcesL ---- */
/* Lua opcode: NukeResources Original name sputLua_NukeResourcesL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'NukeResources'); was Lua_NukeResources. */

void sputLua_NukeResourcesL(void)

{
  sputRoom_SetCurrentRoom((void *)0x0,0);
  sputActor_NukeCostumeStacks();
  Res_FreeAll();
  g_pShadowMaterial = (void *)0x0;
  return;
}

/* ---- 0x0049cd40  sputLua_DetachFromResourcesL ---- */
/* Lua opcode: DetachFromResources Original name sputLua_DetachFromResourcesL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'DetachFromResources'); was
   Lua_DetachFromResources. */

void sputLua_DetachFromResourcesL(void)

{
  sputSmush_StopMovie();
  SoundsCloseVoiceFile();
  sputResource_CloseResources();
  return;
}

/* ---- 0x0049cd50  sputLua_AttachToResourcesL ---- */
/* Lua opcode: AttachToResources Original name sputLua_AttachToResourcesL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'AttachToResources'); was Lua_AttachToResources.
    */

void sputLua_AttachToResourcesL(void)

{
  sputResource_CloseResources();
  grimlib_FindResources();
  return;
}

/* ---- 0x0049cd60  sputLua_SearchForFileOrSwapCDsL ---- */
/* Lua opcode: SearchForFileOrSwapCDs Original name sputLua_SearchForFileOrSwapCDsL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SearchForFileOrSwapCDs'); was
   Lua_SearchForFileOrSwapCDs. */

void sputLua_SearchForFileOrSwapCDsL(void)

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
        ppvVar1 = &g_pSputLuaHS->pFopen;
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
            iVar5 = grimPlat_QueryDialog(text,caption,flags);
            if (iVar5 == 2) {
              lua_pushnil();
              lua_pushnil();
              return;
            }
            sputResource_CloseResources();
            grimlib_FindResources();
            puVar6 = &DAT_004dda54;
            ppvVar1 = &g_pSputLuaHS->pFopen;
            iVar5 = lua_getstring(iVar4);
            iVar5 = (*(code *)*ppvVar1)(iVar5,puVar6);
          } while (iVar5 == 0);
          (*g_pSputLuaHS->pFclose)(iVar5);
          lua_pushnumber(1.0);
          lua_pushnumber(1.0);
          return;
        }
        (*g_pSputLuaHS->pFclose)(iVar5);
        lua_pushnumber(1.0);
        lua_pushnil();
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049cea0  sputLua_LoadL ---- */
/* Lua opcode: Load Original name sputLua_LoadL (the remaster's GrimFandango (Linux): Lua / module
   table entry 'Load'); was Lua_Load. */

void sputLua_LoadL(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 != 0) {
    grimlib_Load(0);
    return;
  }
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    iVar1 = lua_getstring(iVar1);
    grimlib_Load(iVar1);
  }
  return;
}

/* ---- 0x0049cef0  sputLua_SaveL ---- */
/* Lua opcode: Save Original name sputLua_SaveL (the remaster's GrimFandango (Linux): Lua / module
   table entry 'Save'); was Lua_Save. */

void sputLua_SaveL(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 != 0) {
    grimlib_Save(0);
    return;
  }
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    iVar1 = lua_getstring(iVar1);
    grimlib_Save(iVar1);
  }
  return;
}

/* ---- 0x0049cf40  sputLua_EnableDebugKeysL ---- */
/* Lua opcode: EnableDebugKeys Original name sputLua_EnableDebugKeysL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'EnableDebugKeys'); was Lua_EnableDebugKeys. */

void sputLua_EnableDebugKeysL(void)

{
  g_nGrimlib_bDebugKeys = 1;
  if (g_dwDebugToggleFunc != 0) {
    (*(code *)g_dwDebugToggleFunc)(1);
  }
  return;
}

/* ---- 0x0049cf60  sputLua_WorldToScreenL ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: WorldToScreen Original name sputLua_WorldToScreenL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'WorldToScreen'); was Lua_WorldToScreen. */

void sputLua_WorldToScreenL(void)

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
        iVar1 = rdPrimit3_GetScreenCoord(local_18,&local_c);
        if (iVar1 != 0) {
          lua_pushnumber((float)PUN(int,(float)local_c));
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

#endif


/* ---- 0x0049d030  sputLua_ScreenToWorldL ---- */
/* Lua opcode: ScreenToWorld Original name sputLua_ScreenToWorldL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ScreenToWorld'); was Lua_ScreenToWorld. */

void sputLua_ScreenToWorldL(void)

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
          sputRender_ReverseProject((int)lVar5,iVar3,outPos);
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


/* ---- 0x0049d220  sputLua_ConcatFallback ---- */
/* Lua opcode: Lua_ConcatFallback Original name sputLua_ConcatFallback (the remaster's GrimFandango
   (Linux): Lua / module table entry '  concatfallback'); was Lua_ConcatFallback. */

void sputLua_ConcatFallback(void)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  char *fmt;
  Actor *pAVar5;
  undefined1 *puVar6;
  uint uVar7;
  uint *puVar8;
  int iVar9;
  char *pcVar10;
  #define local_88 (*(uint *)(_frame + (0xa0 - 0x88)))
  #define local_84 (*(uint *)(_frame + (0xa0 - 0x84)))
  #define local_80 (*(char (*)[128])(_frame + (0xa0 - 0x80)))
  
  local_80[0] = '\0';
  local_88 = lua_lua2C(1);
  local_84 = lua_lua2C(2);
  iVar9 = 0;
  puVar8 = &local_88;
  do {
    uVar2 = *puVar8;
    iVar4 = lua_isstring(uVar2);
    if (iVar4 == 0) {
      iVar4 = lua_isnil(uVar2);
      if (iVar4 == 0) {
        iVar4 = lua_isuserdata(uVar2);
        if (iVar4 == 0) goto LAB_0049d34b;
      }
    }
    uVar7 = 0xffffffff;
    pcVar10 = local_80;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar10 + 1;
    } while (cVar1 != '\0');
    pcVar10 = local_80 + (~uVar7 - 1);
    iVar4 = lua_isstring(uVar2);
    if (iVar4 == 0) {
      iVar4 = lua_isnil(uVar2);
      if (iVar4 == 0) {
        iVar4 = lua_tag(uVar2);
        if (iVar4 != 0x52544341) {
LAB_0049d34b:
          lua_pushobject(local_88);
          lua_pushobject(local_84);
          iVar9 = lua_getref(g_dwLrOldConcatFallback);
          lua_callfunction(iVar9);
          iVar9 = lua_lua2C(1);
          lua_pushobject(iVar9);
          return;
        }
        iVar4 = lua_getuserdata(uVar2);
        pAVar5 = sputActor_ActorDeref(iVar4);
        if ((pAVar5->pCostumes == (CostumeNode *)0x0) ||
           (pvVar3 = pAVar5->pCostumes->pMainModel, pvVar3 == (void *)0x0)) {
          puVar6 = &DAT_004f5a98;
        }
        else {
          puVar6 = *(undefined1 **)((int)pvVar3 + 4);
        }
        sprintf(pcVar10,s__actor_d__s__004ec494,iVar4,puVar6);
      }
      else {
        sprintf(pcVar10,s__nil__004ec4a4);
      }
    }
    else {
      fmt = (char *)lua_getstring(uVar2);
      sprintf(pcVar10,fmt);
    }
    iVar9 = iVar9 + 1;
    puVar8 = puVar8 + 1;
    if (1 < iVar9) {
      lua_pushstring(local_80);
      return;
    }
  } while( true );
}
#undef local_80
#undef local_84
#undef local_88


/* ---- 0x0049d3a0  sputLua_ExitL ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: exit Original name sputLua_ExitL (the remaster's GrimFandango (Linux): Lua / module
   table entry 'exit'); was Lua_exit. */

void sputLua_ExitL(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    grimlib_RequestShutdown((int)lVar3);
    return;
  }
  grimlib_RequestShutdown(0);
  return;
}

/* ---- 0x0049d3f0  sputLua_EnableControlL ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: EnableControl Original name sputLua_EnableControlL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'EnableControl'); was Lua_EnableControl. */

void sputLua_EnableControlL(void)

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
  sputControl_EnableControl((int)lVar3);
  return;
}

/* ---- 0x0049d430  sputLua_DisableControlL ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: DisableControl Original name sputLua_DisableControlL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'DisableControl'); was Lua_DisableControl. */

void sputLua_DisableControlL(void)

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
  sputControl_DisableControl((int)lVar3);
  return;
}

/* ---- 0x0049d470  sputLua_GetControlStateL ---- */
/* Lua opcode: GetControlState Original name sputLua_GetControlStateL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetControlState'); was Lua_GetControlState. */

void sputLua_GetControlStateL(void)

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
    if (uVar3 <= g_nSputControl_numControlSymbols - 1U) {
      if (((&g_dwSputControl_aControlSymbols)[uVar3 * 4] & 4) != 0) {
        iVar1 = stdControl_ReadKey(*(int *)(&DAT_004e87cc + uVar3 * 0x10),&local_4,(int *)&local_8);
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
      local_c = stdControl_ReadAxis(*(int *)(&DAT_004e87cc + uVar3 * 0x10));
      if (((&g_dwSputControl_aControlSymbols)[uVar3 * 4] & 8) != 0) {
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


/* ---- 0x0049d550  sputLua_DoCostumeOverrideCallback ---- */
/* Original name sputLua_DoCostumeOverrideCallback (the remaster's GrimFandango (Linux): strings:
   'costumeOverrideHandler'); was Lua_CallCostumeOverrideHandler. */

void __cdecl sputLua_DoCostumeOverrideCallback(void *actor,int flag)

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
  pcVar3 = (char *)sputActor_GetActorHandle(actor,unaff_EDI);
  iVar4 = lua_getref(g_nLrSystemTable);
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


/* ---- 0x0049d670  sputLua_DoCostumeMarkerCallback ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* system.costumeMarkerHandler(actor, marker) from keyframe markers Original name
   sputLua_DoCostumeMarkerCallback (the remaster's GrimFandango (Linux): strings:
   'costumeMarkerHandler'); was Lua_CallCostumeMarkerHandler. */

void __cdecl sputLua_DoCostumeMarkerCallback(void *actor,uint marker)

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
    pcVar3 = (char *)sputActor_GetActorHandle(actor,unaff_EBX);
    lua_beginblock();
    iVar4 = lua_getref(g_nLrSystemTable);
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


/* ---- 0x0049d7b0  sputLua_DoUserPaintCallback ---- */
/* system.userPaintHandler() after a restore Original name sputLua_DoUserPaintCallback (the
   remaster's GrimFandango (Linux): strings: 'userPaintHandler'); was Lua_CallUserPaintHandler. */

void sputLua_DoUserPaintCallback(void)

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
  iVar3 = lua_getref(g_nLrSystemTable);
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


/* ---- 0x0049d890  sputLua_DoExitCallback ---- */
/* system.exitHandler(); returns 1 when a handler existed Original name sputLua_DoExitCallback (the
   remaster's GrimFandango (Linux): strings: 'exitHandler'); was Lua_CallExitHandler. */

uint sputLua_DoExitCallback(void)

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
  iVar2 = lua_getref(g_nLrSystemTable);
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


/* ---- 0x0049d970  sputLua_DoPauseCallback ---- */
/* system.pauseHandler() (Pause key) Original name sputLua_DoPauseCallback (the remaster's
   GrimFandango (Linux): strings: 'pauseHandler'); was Lua_CallPauseHandler. */

uint sputLua_DoPauseCallback(void)

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
  iVar2 = lua_getref(g_nLrSystemTable);
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


/* ---- 0x0049da50  sputLua_DoCharacterCallback ---- */
/* system.characterHandler(char); true when the script consumed it Original name
   sputLua_DoCharacterCallback (the remaster's GrimFandango (Linux): strings: 'characterHandler');
   was Lua_CallCharacterHandler. */

int __cdecl sputLua_DoCharacterCallback(int ch)

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
  iVar2 = lua_getref(g_nLrSystemTable);
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


/* ---- 0x0049db70  sputLua_MakeCurrentSetupL ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: MakeCurrentSetup Original name sputLua_MakeCurrentSetupL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'MakeCurrentSetup'); was Lua_MakeCurrentSetup. */

void sputLua_MakeCurrentSetupL(void)

{
  int iVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    ((code *)grimlib_MakeCurrentSetup)((int)lVar3,unaff_ESI);
  }
  return;
}
#endif


/* ---- 0x0049dbb0  sputLua_GetCurrentSetupL ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: GetCurrentSetup Original name sputLua_GetCurrentSetupL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetCurrentSetup'); was Lua_GetCurrentSetup. */

void sputLua_GetCurrentSetupL(void)

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
    pcVar3 = sputRoom_GetCurrentRoomName();
    iVar2 = lua_getstring(iVar1);
    iVar2 = _stricmp(iVar2,pcVar3);
    if (iVar2 == 0) {
      pvVar4 = sputRoom_GetCurrentRoom();
      if (pvVar4 != (void *)0x0) {
        pvVar4 = sputRoom_GetCurrentRoom();
        lua_pushnumber((float)*(int *)((int)pvVar4 + 0xb4));
        return;
      }
      lua_pushnil();
      return;
    }
    pcVar3 = (char *)lua_getstring(iVar1);
    pvVar4 = Res_Loaded(0x20544553,pcVar3);
    if (pvVar4 != (void *)0x0) {
      pcVar3 = (char *)lua_getstring(iVar1);
      pvVar4 = sputResource_Alloc(0x20544553,pcVar3);
      lua_pushnumber((float)*(int *)((int)pvVar4 + 0xb4));
    }
  }
  return;
}
#undef local_10
#undef local_4


/* ---- 0x0049dc70  sputLua_MakeCurrentSetL ---- */
/* Lua opcode: MakeCurrentSet Original name sputLua_MakeCurrentSetL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'MakeCurrentSet'); was Lua_MakeCurrentSet. */

void sputLua_MakeCurrentSetL(void)

{
  int iVar1;
  int iVar2;
  char *name;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 == 0) {
    grimlib_MakeCurrentSet((char *)0x0);
    return;
  }
  name = (char *)lua_getstring(iVar1);
  grimlib_MakeCurrentSet(name);
  return;
}

/* ---- 0x0049dcb0  sputLua_LockSet ---- */
/* Source: Scripts/sputLua.cpp (line 5305, from __FILE__/__LINE__ passed to the allocator) Original
   name sputLua_LockSet (the remaster's GrimFandango (Linux): Lua / module table entry 'LockSet');
   was Lua_LockSet. */

void sputLua_LockSet(void)

{
  int iVar1;
  int iVar2;
  char *name;
  void *data;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(iVar1);
    data = sputResource_Alloc(0x20544553,name);
    if ((data != (void *)0x0) && (*(int *)((int)data + 0x1ac0) == 0)) {
      Res_SetReference((void *)((int)data + 0x1ac0),data,s_C__grimsrc_libs_grimlib_Scripts__004ec38c
                       ,0x14b9);
    }
  }
  return;
}

/* ---- 0x0049dd10  sputLua_UnLockSet ---- */
/* Lua opcode: UnLockSet Original name sputLua_UnLockSet (the remaster's GrimFandango (Linux): Lua /
   module table entry 'UnLockSet'); was Lua_UnLockSet. */

void sputLua_UnLockSet(void)

{
  int iVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(iVar1);
    pvVar3 = sputResource_Alloc(0x20544553,name);
    if ((pvVar3 != (void *)0x0) && (*(int *)((int)pvVar3 + 0x1ac0) != 0)) {
      Res_RemoveReference((void *)((int)pvVar3 + 0x1ac0));
    }
  }
  return;
}

/* ---- 0x0049dd70  sputLua_MessagePrintL ---- */
/* Lua opcode: PrintMessage Original name sputLua_MessagePrintL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'PrintMessage'); was Lua_PrintMessage. */

void sputLua_MessagePrintL(void)

{
  void **ppvVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_isnil(iVar2);
  if (iVar3 != 0) {
    (*g_pSputLuaHS->pPrintf2)(s__nil__004ec4a4);
    return;
  }
  iVar3 = lua_isstring(iVar2);
  if (iVar3 != 0) {
    ppvVar1 = &g_pSputLuaHS->pPrintf2;
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


/* ---- 0x0049de00  sputLua_Startup ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
   Original name sputLua_Startup (the remaster's GrimFandango (Linux): strings: 'concat' | 'WALK' |
   'SPECIAL' | 'HOT'); was Lua_InitGameLibs. */

undefined4 sputLua_Startup(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define acStack_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  if (UINT_008cab80 != 0) {
    return 1;
  }
  (*(code *)UINT_008cab58)();
  wuRegistry_GetStr(s_TextAllowed_004ec55c,acStack_20,0x20,&DAT_004f5a98);
  iVar1 = _stricmp(acStack_20,&DAT_004ec554);
  if (iVar1 != 0) {
    *(undefined4 *)lua_assume_binary_exref = 1;
  }
  lua_iolibopen();
  lua_strlibopen();
  lua_mathlibopen();
  sputLua_RegisterFunctions(&PTR_s_EnginePause_004ea8b0,UINT_004eb168);
  lua_recognizelib(((unsigned)(uintptr_t)&PTR_s_concatfallback_004ea890),4);
  g_nLrSystemTable = Lua_CreateSystemTable();
  iVar1 = lua_getglobal(&DAT_004ec54c);
  lua_pushobject(iVar1);
  g_dwLrTypeFunction = lua_ref(1);
  lua_pushCclosure(((unsigned)(uintptr_t)sputLua_TypeOverride),0);
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
  iVar1 = lua_setfallback(s_concat_004ec520,sputLua_ConcatFallback);
  lua_pushobject(iVar1);
  g_dwLrOldConcatFallback = lua_ref(1);
  *(code **)lua_savehook_exref = sputLua_SaveIndirector;
  *(code **)lua_restorehook_exref = sputLua_RestoreIndirector;
  sputControl_AddCallback(sputLua_NotifyControlHandlers);
  return 0;
}
#undef acStack_20

#endif


/* ---- 0x0049dfa0  sputLua_SaveIndirector ---- */
/* lua_savehook: STAT userdata is written as setup<<16 | index in the setup's object state list
   Original name sputLua_SaveIndirector (the remaster's GrimFandango (Linux): aligned call in
   sputLua_Startup); was Lua_SaveUserdataHook. */

uint sputLua_SaveIndirector(int param_1,uint param_2)

{
  uint uVar1;
  void *pvVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  
  if (param_1 != 0x54415453) {
    return param_2;
  }
  pvVar2 = sputRoom_GetCurrentRoom();
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

/* ---- 0x0049e020  sputLua_RestoreIndirector ---- */
/* lua_restorehook: rebuilds STAT, FONT and TEXT userdata pointers from their saved ids Original
   name sputLua_RestoreIndirector (the remaster's GrimFandango (Linux): aligned call in
   sputLua_Startup); was Lua_RestoreUserdataHook. */

TextObject * sputLua_RestoreIndirector(int param_1,TextObject *param_2)

{
  TextObject *pTVar1;
  void *pvVar2;
  uint uVar3;
  
  if (param_1 == 0x54415453) {
    if (param_2 == (TextObject *)0xffffffff) {
      param_2 = (TextObject *)0x0;
    }
    else {
      uVar3 = (uint)param_2 & 0xffff;
      pvVar2 = sputRoom_GetCurrentRoom();
      param_2 = *(TextObject **)
                 (*(int *)((int)pvVar2 + 0xac) + 0x128 + ((uint)param_2 >> 0x10) * 300);
      if (uVar3 != 0) {
        do {
          param_2 = *(TextObject **)(param_2->aText + 0xf0);
          uVar3 = uVar3 - 1;
        } while (uVar3 != 0);
        return param_2;
      }
    }
  }
  else {
    if (param_1 == 0x544e4f46) {
      pTVar1 = Res_HandleFromSerialNumber(param_2);
      return pTVar1;
    }
    if (param_1 == 0x54584554) {
      pTVar1 = sputText_FindSerialNumber((int)param_2);
      return pTVar1;
    }
  }
  return param_2;
}

/* ---- 0x0049e0b0  sputLua_NotifyControlHandlers ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_58 */
/* Calls system.buttonHandler / system.axisHandler for every enabled control whose state changed
   (last value kept at control+8) Original name sputLua_NotifyControlHandlers (the remaster's
   GrimFandango (Linux): aligned call in sputLua_Startup); was Lua_DispatchControlHandlers. */

undefined4 sputLua_NotifyControlHandlers(void)

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
  iVar3 = lua_getref(g_nLrSystemTable);
  lua_pushobject(iVar3);
  lua_pushstring(s_buttonHandler_004ec574);
  fVar4 = (float)lua_gettable();
  iVar3 = lua_istable(PUN(int,(float)fVar4));
  pcVar7 = lua_isfunction_exref;
  if (iVar3 == 0) {
    iVar3 = lua_isfunction(PUN(int,(float)fVar4));
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
    lua_pushobject(PUN(int,(float)fVar4));
    lua_pushstring(s_buttonHandler_004ec574);
    local_30[1] = (float)lua_gettable();
    pcVar7 = lua_isfunction_exref;
    iVar3 = lua_isfunction(PUN(int,(float)local_30[1]));
    if (iVar3 != 0) {
      bVar1 = true;
      local_44 = 1;
    }
  }
  iVar3 = lua_getref(g_nLrSystemTable);
  lua_pushobject(iVar3);
  lua_pushstring(s_axisHandler_004ec568);
  fVar5 = (float)lua_gettable();
  local_1c[0] = fVar5;
  iVar3 = lua_istable(PUN(int,(float)fVar5));
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
    lua_pushobject(PUN(int,(float)fVar5));
    lua_pushstring(s_axisHandler_004ec568);
    local_30[2] = (float)lua_gettable();
    iVar3 = (*pcVar7)(local_30[2]);
    if (iVar3 != 0) {
      bVar2 = true;
      local_3c = 1;
    }
  }
  fVar5 = 0.0;
  if (g_nSputControl_numControlSymbols != 0) {
    puVar8 = &UINT_004e87d0;
    do {
      if ((puVar8[-2] & 1) != 0) {
        if ((puVar8[-2] & 4) == 0) {
          fVar6 = stdControl_ReadAxis(puVar8[-1]);
          if ((puVar8[-2] & 8) != 0) {
            fVar6 = -fVar6;
          }
          if ((fVar6 != (float)*puVar8) && (local_3c != 0)) {
            if (bVar2) {
              lua_pushobject(PUN(int,(float)local_1c[0]));
            }
            lua_pushnumber((float)PUN(uint,(float)fVar5));
            lua_pushnumber(fVar6);
            lua_callfunction(PUN(int,(float)local_30[2]));
            *puVar8 = PUN(uint,(float)fVar6);
          }
        }
        else {
          local_30[0] = 0.0;
          fVar6 = (float)stdControl_ReadKey(puVar8[-1],(int *)local_30,(int *)&local_20);
          if ((fVar6 != (float)*puVar8) && (local_44 != 0)) {
            if (bVar1) {
              lua_pushobject(PUN(int,(float)fVar4));
            }
            local_1c[1] = fVar5;
            lua_pushnumber((float)PUN(uint,(float)fVar5));
            if (fVar6 == 0.0) {
              lua_pushnil();
            }
            else {
              lua_pushnumber(1.0);
            }
            lua_pushnumber((float)PUN(uint,(float)local_30[0]));
            lua_pushnumber((float)(int)local_20);
            lua_callfunction(PUN(int,(float)local_30[1]));
            *puVar8 = PUN(uint,(float)fVar6);
          }
        }
      }
      fVar5 = (float)(PUN(int,(float)fVar5) + 1);
      puVar8 = puVar8 + 4;
    } while (PUN(uint,(float)fVar5) < (uint)g_nSputControl_numControlSymbols);
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

#endif


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
/* system.controls[name] = index for every entry of g_dwSputControl_aControlSymbols (name at
   control+0xc) */

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
  if (g_nSputControl_numControlSymbols != 0) {
    ppuVar4 = &PTR_s_KEY_ESCAPE_004e87d4;
    do {
      lua_pushobject(iVar1);
      lua_pushstring(*ppuVar4);
      lua_pushnumber((float)uVar3);
      lua_settable();
      uVar3 = uVar3 + 1;
      ppuVar4 = ppuVar4 + 4;
    } while (uVar3 < (uint)g_nSputControl_numControlSymbols);
  }
  return;
}
#undef local_1c


/* ---- 0x0049e590  sputLua_SetSoundPosition ---- */
/* Lua opcode: SetSoundPosition Original name sputLua_SetSoundPosition (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetSoundPosition'); was Lua_SetSoundPosition. */

void sputLua_SetSoundPosition(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  void *set;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *pAVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(float (*)[3])(_frame + (0x40 - 0x20)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  set = sputRoom_GetCurrentRoom();
  local_20[0] = 8.0;
  local_20[1] = 1.0;
  local_24 = CONCAT31(PIECE(local_24,1,3),10);
  local_28 = CONCAT31(PIECE(local_28,1,3),0x7f);
  local_20[2] = 1.5;
  if (set != (void *)0x0) {
    sputRoom_GetSoundParameters
              (set,local_20,(char *)&local_24,(char *)&local_28,local_20 + 2,local_20 + 1);
  }
  iVar2 = lua_lua2C(1);
  iVar3 = lua_isnumber(iVar2);
  if ((iVar3 == 0) && (iVar3 = lua_isstring(iVar2), iVar3 == 0)) {
    return;
  }
  iVar7 = 3;
  iVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(iVar3);
  if ((iVar4 == 0) || (iVar4 = lua_tag(iVar3), iVar4 != 0x52544341)) {
    iVar4 = lua_isnumber(iVar3);
    if (iVar4 != 0) {
      iVar4 = lua_lua2C(3);
      iVar7 = 5;
      iVar6 = lua_lua2C(4);
      local_c[0] = lua_getnumber(iVar3);
      local_c[1] = lua_getnumber(iVar4);
      local_c[2] = lua_getnumber(iVar6);
    }
  }
  else {
    iVar3 = lua_getuserdata(iVar3);
    pAVar5 = sputActor_ActorDeref(iVar3);
    if (pAVar5 == (Actor *)0x0) {
      return;
    }
    local_c[0] = pAVar5->aPos[0];
    local_c[1] = pAVar5->aPos[1];
    local_c[2] = pAVar5->aPos[2];
  }
  iVar3 = lua_lua2C(iVar7);
  iVar4 = lua_lua2C(iVar7 + 1);
  iVar7 = lua_lua2C(iVar7 + 2);
  iVar6 = lua_isnumber(iVar3);
  if (iVar6 != 0) {
    lVar8 = (longlong)lua_getnumber(iVar3);
    local_24 = CONCAT31(PIECE(local_24,1,3),(byte)lVar8);
    if (0x7f < (byte)lVar8) {
      local_24 = CONCAT31(PIECE(local_24,1,3),0x7f);
    }
  }
  iVar3 = lua_isnumber(iVar4);
  if (iVar3 != 0) {
    lVar8 = (longlong)lua_getnumber(iVar4);
    bVar1 = (byte)lVar8;
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
  iVar3 = lua_isnumber(iVar7);
  if ((iVar3 != 0) && (local_20[0] = lua_getnumber(iVar7), local_20[0] < 0.0)) {
    local_20[0] = 0.0;
  }
  iVar3 = lua_isnumber(iVar2);
  if (iVar3 == 0) {
    iVar2 = lua_getstring(iVar2);
  }
  else {
    lVar8 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar8;
  }
  sputRoom_SetSoundPosition(iVar2,local_c,local_24 & 0xff,local_28 & 0xff,PUN(uint,(float)(local_20[0])),0x3f4ccccd);
  return;
}
#undef local_10
#undef local_14
#undef local_20
#undef local_24
#undef local_28
#undef local_c


/* ---- 0x0049e7e0  sputLua_StartFullScreenMovieL ---- */
/* Lua opcode: StartFullscreenMovie Original name sputLua_StartFullScreenMovieL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'StartFullscreenMovie'); was
   Lua_StartFullscreenMovie. */

void sputLua_StartFullScreenMovieL(void)

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
    iVar1 = grimlib_PlayMovie(iVar1,uVar4,uVar5,uVar6,uVar7);
    if (iVar1 == 1) {
      lua_pushnumber(1.0);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0049e860  sputLua_PauseMovieL ---- */
/* Lua opcode: PauseMovie Original name sputLua_PauseMovieL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'PauseMovie'); was Lua_PauseMovie. */

void sputLua_PauseMovieL(void)

{
  int iVar1;
  
  iVar1 = lua_lua2C(1);
  iVar1 = lua_isnil(iVar1);
  sputSmush_Pause(iVar1);
  return;
}

/* ---- 0x0049e960  sputLua_IsMoviePlayingL ---- */
/* Lua opcodes: IsFullscreenMoviePlaying, IsMoviePlaying
   also registered as IsFullscreenMoviePlaying Original name sputLua_IsMoviePlayingL (the remaster's
   GrimFandango (Linux): same body (pushes 1 or nil by sputSmush_MoviePlaying)); was
   Lua_IsMoviePlaying. */

void sputLua_IsMoviePlayingL(void)

{
  int iVar1;
  
  iVar1 = sputSmush_MoviePlaying();
  if (iVar1 != 0) {
    lua_pushnumber(1.0);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0049e978. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lua_pushnil();
  return;
}

/* ---- 0x0049e980  sputLua_FileFindFirst ---- */
/* Lua opcode: FileFindFirst Original name sputLua_FileFindFirst (the remaster's GrimFandango
   (Linux): Lua / module table entry 'FileFindFirst'); was Lua_FileFindFirst. */

void __fastcall sputLua_FileFindFirst(char *param_1)

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
    sputLua_FileFindDispose();
    iVar1 = lua_isnil(iVar2);
    if (iVar1 != 0) {
      local_4 = (uint)&DAT_004f5a98;
    }
    g_pFrFileReq = stdFileUtil_NewFind((char *)local_4,3,ext);
    if (g_pFrFileReq != (void *)0x0) {
      sputLua_FileFindNext();
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_4


/* ---- 0x0049ea20  sputLua_FileFindNext ---- */
/* Lua opcode: FileFindNext Original name sputLua_FileFindNext (the remaster's GrimFandango (Linux):
   Lua / module table entry 'FileFindNext'); was Lua_FileFindNext. */

void sputLua_FileFindNext(void)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_10c (*(char (*)[260])(_frame + (0x120 - 0x10c)))
  #define local_8 (*(uint *)(_frame + (0x120 - 0x8)))
  
  iVar1 = 0;
  if (g_pFrFileReq != (void *)0x0) {
    do {
      iVar1 = stdFileUtil_FindNext(g_pFrFileReq,local_10c);
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


/* ---- 0x0049ea90  sputLua_FileFindDispose ---- */
/* Lua opcode: FileFindDispose Original name sputLua_FileFindDispose (the remaster's GrimFandango
   (Linux): Lua / module table entry 'FileFindDispose'); was Lua_FileFindDispose. */

void sputLua_FileFindDispose(void)

{
  if (g_pFrFileReq != (void *)0x0) {
    stdFileUtil_DisposeFind(g_pFrFileReq);
    g_pFrFileReq = (void *)0x0;
  }
  return;
}

/* ---- 0x0049eab0  sputLua_QueryDialog ---- */
/* Lua opcode: QueryDialog Original name sputLua_QueryDialog (the remaster's GrimFandango (Linux):
   Lua / module table entry 'QueryDialog'); was Lua_QueryDialog. */

void sputLua_QueryDialog(void)

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
      iVar1 = grimPlat_QueryDialog(text,caption,(iVar1 != 0) + 3);
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

/* ---- 0x0049eb60  sputLua_InputDialog ---- */
/* Lua opcode: InputDialog Original name sputLua_InputDialog (the remaster's GrimFandango (Linux):
   Lua / module table entry 'InputDialog'); was Lua_InputDialog. */

void sputLua_InputDialog(void)

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
      iVar1 = grimPlat_InputDialog(title,prompt,local_68,0x65,defaultText);
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


/* ---- 0x0049ec50  sputLua_WriteRegistryValue ---- */
/* Lua opcode: WriteRegistryValue Original name sputLua_WriteRegistryValue (the remaster's
   GrimFandango (Linux): Lua / module table entry 'WriteRegistryValue'); was Lua_WriteRegistryValue.
    */

void sputLua_WriteRegistryValue(void)

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
      wuRegistry_SaveStr(name,value);
      return;
    }
    iVar2 = lua_isnumber(iVar1);
    if (iVar2 != 0) {
      value_00 = lua_getnumber(iVar1);
      wuRegistry_SaveFloat(name,value_00);
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049ece0  sputLua_ReadRegistryValue ---- */
/* Lua opcode: ReadRegistryValue Original name sputLua_ReadRegistryValue (the remaster's
   GrimFandango (Linux): Lua / module table entry 'ReadRegistryValue'); was Lua_ReadRegistryValue.
    */

void sputLua_ReadRegistryValue(void)

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
    iVar1 = wuRegistry_QueryType(name);
    if (iVar1 == 3) {
      n = wuRegistry_GetFloat(name,0.0);
      lua_pushnumber(n);
      return;
    }
    if (iVar1 == 1) {
      wuRegistry_GetStr(name,local_100,0xff,&DAT_004f5a98);
      lua_pushstring(local_100);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_100
#undef local_104


/* ---- 0x0049ed90  sputLua_GetSectorOppositeEdge ---- */
/* Lua opcode: GetSectorOppositeEdge Original name sputLua_GetSectorOppositeEdge (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetSectorOppositeEdge'); was
   Lua_GetSectorOppositeEdge. */

void sputLua_GetSectorOppositeEdge(void)

{
  int iVar1;
  int iVar2;
  Actor *a1;
  char *name;
  WalkPlane *a2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if ((iVar2 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      a1 = sputActor_ActorDeref(iVar1);
      iVar1 = lua_lua2C(2);
      iVar2 = lua_isstring(iVar1);
      if (iVar2 != 0) {
        name = (char *)lua_getstring(iVar1);
        a2 = WalkPlane_PlaneNamed(name);
        if (a2 != (WalkPlane *)0x0) {
          sputActor_LeaveSector((int)a1,(int)a2);
          return;
        }
      }
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0049ee20  sputLua_IsSectorActiveL ---- */
/* Lua opcode: IsSectorActive Original name sputLua_IsSectorActiveL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsSectorActive'); was Lua_IsSectorActive. */

void sputLua_IsSectorActiveL(void)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  char *name;
  WalkPlane *pWVar4;
  longlong lVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_0049eea2;
  }
  pvVar3 = sputRoom_GetCurrentRoom();
  if (pvVar3 != (void *)0x0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) {
      lVar5 = (longlong)lua_getnumber(iVar1);
      pWVar4 = WalkPlane_PlaneNumbered((int)lVar5);
    }
    else {
      name = (char *)lua_getstring(iVar1);
      pWVar4 = WalkPlane_PlaneNamed(name);
    }
    if ((pWVar4 != (WalkPlane *)0x0) && (pWVar4->nVisible != 0)) {
      lua_pushnumber(1.0);
    }
  }
LAB_0049eea2:
  lua_pushnil();
  return;
}

/* ---- 0x0049eeb0  sputLua_MakeSectorActiveL ---- */
/* Lua opcode: MakeSectorActive Original name sputLua_MakeSectorActiveL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'MakeSectorActive'); was Lua_MakeSectorActive. */

void sputLua_MakeSectorActiveL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *name;
  WalkPlane *pWVar4;
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
    pWVar4 = WalkPlane_PlaneNumbered((int)lVar5);
  }
  else {
    name = (char *)lua_getstring(iVar1);
    pWVar4 = WalkPlane_PlaneNamed(name);
  }
  if (pWVar4 != (WalkPlane *)0x0) {
    iVar1 = lua_isnil(iVar2);
    if (iVar1 != 0) {
      pWVar4->nVisible = 0;
      return;
    }
    pWVar4->nVisible = 1;
  }
  return;
}

/* ---- 0x0049ef50  sputLua_PreRender ---- */
/* Lua opcode: PreRender Original name sputLua_PreRender (the remaster's GrimFandango (Linux): Lua /
   module table entry 'PreRender'); was Lua_PreRender. */

void sputLua_PreRender(void)

{
  int iVar1;
  int iVar2;
  uint redrawDepth;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar2 = lua_isnil(iVar2);
  redrawDepth = (uint)(iVar2 == 0);
  iVar1 = lua_isnil(iVar1);
  sputRender_PreRendered((uint)(iVar1 == 0),redrawDepth);
  return;
}

/* ---- 0x0049efc0  sputLua_GetCurrentScript ---- */
/* Lua opcode: GetCurrentScript Original name sputLua_GetCurrentScript (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetCurrentScript'); was Lua_GetCurrentScript. */

void sputLua_GetCurrentScript(void)

{
  int iVar1;
  
  iVar1 = lua_currenttask();
  lua_pushtask(iVar1);
  return;
}

/* ---- 0x0049efe0  sputLua_LockFontL ---- */
/* Lua opcode: LockFont Original name sputLua_LockFontL (the remaster's GrimFandango (Linux): Lua /
   module table entry 'LockFont'); was Lua_LockFont. */

void sputLua_LockFontL(void)

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
  pcVar3 = sputResource_Alloc(0x544e4f46,pcVar3);
  if (pcVar3 == (char *)0x0) {
    lua_pushnil();
    return;
  }
  lua_pushusertag(pcVar3,0x544e4f46);
  return;
}

/* ---- 0x0049f040  sputLua_LoadCostumeL ---- */
/* Lua opcode: LoadCostume Original name sputLua_LoadCostumeL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'LoadCostume'); was Lua_LoadCostume. */

void sputLua_LoadCostumeL(void)

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
  sputResource_Alloc(0x54534f43,name);
  return;
}

/* ---- 0x0049f080  sputLua_GetPhysicalBytes ---- */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: GetPhysicalBytes Original name sputLua_GetPhysicalBytes (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetPhysicalBytes'); was Lua_GetPhysicalBytes. */

void __fastcall sputLua_GetPhysicalBytes(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ((code *)stdPlatform_GetPhysicalRam)(param_1);
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x0049f0a0  sputLua_SetMemoryUsage ---- */
/* Lua opcode: SetMemoryUsage Original name sputLua_SetMemoryUsage (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetMemoryUsage'); was Lua_SetMemoryUsage. */

void sputLua_SetMemoryUsage(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  lVar3 = (longlong)lua_getnumber(iVar2);
  iVar2 = (int)lVar3;
  lVar3 = (longlong)lua_getnumber(iVar1);
  sputResource_SetMemoryUsage((int)lVar3,iVar2);
  return;
}

/* ---- 0x0049f2b0  sputLua_GetCameraPositionL ---- */
/* Lua opcode: GetCameraPosition Original name sputLua_GetCameraPositionL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetCameraPosition'); was Lua_GetCameraPosition.
    */

void sputLua_GetCameraPositionL(void)

{
  if (g_pSputRender_Camera == (float *)0x0) {
    lua_pushnil();
  }
  lua_pushnumber(*g_pSputRender_Camera);
  lua_pushnumber(g_pSputRender_Camera[1]);
  lua_pushnumber(g_pSputRender_Camera[2]);
  return;
}

/* ---- 0x0049f300  sputLua_GetCameraInterestL ---- */
/* Lua opcode: GetCameraInterest Original name sputLua_GetCameraInterestL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetCameraInterest'); was Lua_GetCameraInterest.
    */

void sputLua_GetCameraInterestL(void)

{
  if (g_pSputRender_Camera == (float *)0x0) {
    lua_pushnil();
  }
  lua_pushnumber(g_pSputRender_Camera[3]);
  lua_pushnumber(g_pSputRender_Camera[4]);
  lua_pushnumber(g_pSputRender_Camera[5]);
  return;
}

/* ---- 0x0049f350  sputLua_GetCameraFOVL ---- */
/* Lua opcode: GetCameraFOV Original name sputLua_GetCameraFOVL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetCameraFOV'); was Lua_GetCameraFOV. */

void sputLua_GetCameraFOVL(void)

{
  if (g_pSputRender_Camera == (float *)0x0) {
    lua_pushnil();
  }
  lua_pushnumber(g_pSputRender_Camera[7]);
  return;
}

/* ---- 0x0049f380  sputLua_GetCameraRollL ---- */
/* Lua opcode: GetCameraRoll Original name sputLua_GetCameraRollL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetCameraRoll'); was Lua_GetCameraRoll. */

void sputLua_GetCameraRollL(void)

{
  if (g_pSputRender_Camera == (float *)0x0) {
    lua_pushnil();
  }
  lua_pushnumber(g_pSputRender_Camera[6]);
  return;
}

/* ---- 0x0049f3b0  sputLua_SetCameraPositionL ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: SetCameraPosition Original name sputLua_SetCameraPositionL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetCameraPosition'); was Lua_SetCameraPosition.
    */

void sputLua_SetCameraPositionL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  if (g_pSputRender_Camera == (float *)0x0) {
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
  *g_pSputRender_Camera = fVar5;
  fVar5 = lua_getnumber(iVar2);
  g_pSputRender_Camera[1] = fVar5;
  fVar5 = lua_getnumber(iVar3);
  g_pSputRender_Camera[2] = fVar5;
  rdMatrix_LookAt(g_pSputRender_Camera + 0xc,g_pSputRender_Camera,g_pSputRender_Camera + 3,PUN(undefined4,(float)(g_pSputRender_Camera[6])));
  rdCamera_Update(g_pSputRender_Camera + 0xc);
  return;
}
#undef local_14


/* ---- 0x0049f480  sputLua_SetCameraInterestL ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: SetCameraInterest Original name sputLua_SetCameraInterestL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetCameraInterest'); was Lua_SetCameraInterest.
    */

void sputLua_SetCameraInterestL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  if (g_pSputRender_Camera == (float *)0x0) {
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
  g_pSputRender_Camera[3] = fVar5;
  fVar5 = lua_getnumber(iVar2);
  g_pSputRender_Camera[4] = fVar5;
  fVar5 = lua_getnumber(iVar3);
  g_pSputRender_Camera[5] = fVar5;
  rdMatrix_LookAt(g_pSputRender_Camera + 0xc,g_pSputRender_Camera,g_pSputRender_Camera + 3,PUN(undefined4,(float)(g_pSputRender_Camera[6])));
  rdCamera_Update(g_pSputRender_Camera + 0xc);
  return;
}
#undef local_14


/* ---- 0x0049f550  sputLua_SetActorScaleL ---- */
/* Lua opcode: SetActorScale Original name sputLua_SetActorScaleL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetActorScale'); was Lua_SetActorScale. */

void sputLua_SetActorScaleL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar4 = sputActor_ActorDeref(iVar1);
      iVar1 = lua_isnumber(iVar2);
      if (iVar1 != 0) {
        fVar5 = lua_getnumber(iVar2);
        pAVar4->flScale = fVar5;
        return;
      }
      pAVar4->flScale = 1.0;
    }
  }
  return;
}

/* ---- 0x0049f5d0  sputLua_SetActorTimeScaleL ---- */
/* Lua opcode: SetActorTimeScale Original name sputLua_SetActorTimeScaleL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorTimeScale'); was Lua_SetActorTimeScale.
    */

void sputLua_SetActorTimeScaleL(void)

{
  ActorExtra *pAVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *actor;
  float fVar5;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(iVar2);
  if (iVar4 != 0) {
    iVar4 = lua_tag(iVar2);
    if (iVar4 == 0x52544341) {
      iVar2 = lua_getuserdata(iVar2);
      actor = sputActor_ActorDeref(iVar2);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      iVar2 = lua_isnumber(iVar3);
      if (iVar2 == 0) {
        fVar5 = 1.0;
      }
      else {
        fVar5 = lua_getnumber(iVar3);
      }
      actor->pExtra->flTimeScale = fVar5;
      pAVar1 = actor->pExtra;
      fVar5 = pAVar1->flTimeScale;
      if (pAVar1->flTimeScale < 0.0) {
        fVar5 = -fVar5;
      }
      pAVar1->flTimeScale = fVar5;
    }
  }
  return;
}

/* ---- 0x0049f690  sputLua_GetActorNodeLocationL ---- */
/* Lua opcode: GetActorNodeLocation Original name sputLua_GetActorNodeLocationL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetActorNodeLocation'); was
   Lua_GetActorNodeLocation. */

void sputLua_GetActorNodeLocationL(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
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
        actor = sputActor_ActorDeref(iVar1);
        if ((actor->pCostumes != (CostumeNode *)0x0) &&
           (actor->pCostumes->pMainModel != (void *)0x0)) {
          if (actor->nScreenBoxValid == 0) {
            pfVar4 = sputActor_GetOrientMatrix(actor);
            rdPuppet_UpdateFrame(actor->pCostumes->pMainModel,pfVar4);
          }
          pfVar4 = local_30;
          lVar5 = (longlong)lua_getnumber(iVar2);
          index = (uint)lVar5;
          frame = sputActor_GetOrientMatrix(actor);
          rdPuppet_BuildJointMatrices(actor->pCostumes->pMainModel,frame,index,pfVar4);
          lVar5 = (longlong)lua_getnumber(iVar2);
          pfVar4 = (float *)(*(int *)(*(int *)((int)actor->pCostumes->pMainModel + 4) + 0x58) + 100
                            + (int)lVar5 * 0xb8);
          local_3c = *pfVar4;
          local_38[0] = pfVar4[1];
          local_38[1] = pfVar4[2];
          rdMatrix_TransformVector34Acc(&local_3c,local_30);
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


/* ---- 0x0049f810  sputLua_GetActorScaleL ---- */
/* Lua opcode: GetActorScale Original name sputLua_GetActorScaleL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetActorScale'); was Lua_GetActorScale. */

void sputLua_GetActorScaleL(void)

{
  int iVar1;
  int iVar2;
  Actor *pAVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar3 = sputActor_ActorDeref(iVar1);
      lua_pushnumber(pAVar3->flScale);
    }
  }
  return;
}

/* ---- 0x0049f860  sputLua_GetActorTimeScaleL ---- */
/* Lua opcode: GetActorTimeScale Original name sputLua_GetActorTimeScaleL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetActorTimeScale'); was Lua_GetActorTimeScale.
    */

void sputLua_GetActorTimeScaleL(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      lua_pushnumber(actor->pExtra->flTimeScale);
    }
  }
  return;
}

/* ---- 0x0049f8d0  sputLua_SetCameraFOVL ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetCameraFOV Original name sputLua_SetCameraFOVL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetCameraFOV'); was Lua_SetCameraFOV. */

void sputLua_SetCameraFOVL(void)

{
  int iVar1;
  int iVar2;
  float fVar3;
  
  if (g_pSputRender_Camera == (float *)0x0) {
    lua_pushnil();
  }
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    lua_pushnil();
  }
  fVar3 = lua_getnumber(iVar1);
  g_pSputRender_Camera[7] = fVar3;
  *(float *)(PUN(int,(float)g_pSputRender_Camera[10]) + 0x38) = g_pSputRender_Camera[7];
  return;
}
#endif


/* ---- 0x0049f930  sputLua_SetCameraRollL ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: SetCameraRoll Original name sputLua_SetCameraRollL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetCameraRoll'); was Lua_SetCameraRoll. */

void sputLua_SetCameraRollL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  if (g_pSputRender_Camera == (float *)0x0) {
    lua_pushnil();
  }
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    lua_pushnil();
  }
  fVar3 = lua_getnumber(iVar1);
  g_pSputRender_Camera[6] = fVar3;
  rdMatrix_LookAt(g_pSputRender_Camera + 0xc,g_pSputRender_Camera,g_pSputRender_Camera + 3,PUN(undefined4,(float)(g_pSputRender_Camera[6])));
  rdCamera_Update(g_pSputRender_Camera + 0xc);
  return;
}
#undef local_c


/* ---- 0x0049f9b0  sputLua_GetCameraLookVectorL ---- */
/* Lua opcode: GetCameraLookVector Original name sputLua_GetCameraLookVectorL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetCameraLookVector'); was
   Lua_GetCameraLookVector. */

void sputLua_GetCameraLookVectorL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *pvVar2;
  int iVar3;
  longlong lVar4;
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float (*)[2])(_frame + (0x20 - 0x8)))
  
  iVar1 = lua_lua2C(1);
  pvVar2 = sputRoom_GetCurrentRoom();
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
  rdVector_Normalize3Acc(&local_c);
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


/* ---- 0x0049fb00  sputLua_PointActorAtL ---- */
/* Lua opcode: PointActorAt(actor, x, y, z | actor). Creates the walker if missing, turns the walker
   heading all the way to the point (Walker_TurnToPoint with FLT_MAX) and negates the turn rate so
   sputActor_AlignToPuck snaps the visible yaw next frame. Only the yaw changes; pitch and roll are
   not touched. Original name sputLua_PointActorAtL (the remaster's GrimFandango (Linux): Lua /
   module table entry 'PointActorAt'); was Lua_PointActorAt. */

void sputLua_PointActorAtL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ActorExtra *pAVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  Actor *actor;
  Actor *pAVar7;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_lua2C(3);
  iVar5 = lua_lua2C(4);
  iVar6 = lua_isuserdata(iVar2);
  if (((iVar6 == 0) || (iVar6 = lua_tag(iVar2), iVar6 != 0x52544341)) || (iVar2 == 0)) {
    lua_pushnil();
    return;
  }
  iVar2 = lua_getuserdata(iVar2);
  actor = sputActor_ActorDeref(iVar2);
  iVar2 = lua_isuserdata(iVar3);
  if ((iVar2 == 0) || (iVar2 = lua_tag(iVar3), iVar2 != 0x52544341)) {
    local_c[0] = lua_getnumber(iVar3);
    local_c[1] = lua_getnumber(iVar4);
    local_c[2] = lua_getnumber(iVar5);
  }
  else {
    iVar2 = lua_getuserdata(iVar3);
    pAVar7 = sputActor_ActorDeref(iVar2);
    local_c[0] = pAVar7->aPos[0];
    local_c[1] = pAVar7->aPos[1];
    local_c[2] = pAVar7->aPos[2];
  }
  if (actor->pExtra->pPuck == (Puck *)0x0) {
    sputActor_EnablePuck(actor,1);
  }
  Puck_PointAt(actor->pExtra->pPuck,local_c,3.4028235e+38);
  pAVar1 = actor->pExtra;
  if (pAVar1->flTurnRate <= 0.0) {
    return;
  }
  pAVar1->flTurnRate = pAVar1->flTurnRate * -1.0;
  return;
}
#undef local_10
#undef local_14
#undef local_c


/* ---- 0x0049fc60  sputLua_TurnActorTo ---- */
/* Lua opcode: TurnActorTo(actor, x, y, z | actor). Creates the walker if missing, turns the heading
   by at most |rate| * frameSeconds (no time scale) and returns TRUE while a whole step was taken
   (angle left >= step), nil once done. With a turn rate of 0 the step is 0 and it returns TRUE
   forever. Original name sputLua_TurnActorTo (the remaster's GrimFandango (Linux): Lua / module
   table entry 'TurnActorTo'); was Lua_TurnActorTo. */

void sputLua_TurnActorTo(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  Actor *actor;
  Actor *pAVar7;
  float fVar8;
  float fVar9;
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
  actor = sputActor_ActorDeref(iVar2);
  iVar2 = lua_isuserdata(iVar3);
  if (iVar2 == 0) {
LAB_0049fd1e:
    local_c[0] = lua_getnumber(iVar3);
    local_c[1] = lua_getnumber(iVar4);
    local_c[2] = lua_getnumber(iVar5);
  }
  else {
    iVar2 = lua_tag(iVar3);
    if (iVar2 != 0x52544341) goto LAB_0049fd1e;
    iVar2 = lua_getuserdata(iVar3);
    pAVar7 = sputActor_ActorDeref(iVar2);
    local_c[0] = pAVar7->aPos[0];
    local_c[1] = pAVar7->aPos[1];
    local_c[2] = pAVar7->aPos[2];
  }
  if (actor->pExtra->pPuck == (Puck *)0x0) {
    sputActor_EnablePuck(actor,1);
  }
  fVar1 = actor->pExtra->flTurnRate;
  if (actor->pExtra->flTurnRate < 0.0) {
    fVar1 = -fVar1;
  }
  fVar8 = sputTime_GetFrameTimeFlex();
  fVar9 = Puck_PointAt(actor->pExtra->pPuck,local_c,fVar8 * fVar1);
  if (fVar9 < 0.0) {
    fVar9 = -fVar9;
  }
  if (fVar8 * fVar1 <= fVar9) {
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


/* ---- 0x0049fdf0  sputLua_PerSecondL ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: PerSecond Original name sputLua_PerSecondL (the remaster's GrimFandango (Linux): Lua
   / module table entry 'PerSecond'); was Lua_PerSecond. */

void sputLua_PerSecondL(void)

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
  fVar2 = sputTime_GetFrameTimeFlex();
  fVar3 = lua_getnumber(iVar1);
  lua_pushnumber(fVar3 * fVar2);
  return;
}
#undef local_4
#undef local_c


/* ---- 0x0049fe40  sputLua_SnapToPlane ---- */
/* Lua opcode: SnapToPlane Original name sputLua_SnapToPlane (the remaster's GrimFandango (Linux):
   Lua / module table entry 'SnapToPlane'); was Lua_SnapToPlane. */

void sputLua_SnapToPlane(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *name;
  WalkPlane *this;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  name = (char *)lua_getstring(iVar1);
  this = WalkPlane_PlaneNamed(name);
  if (this == (WalkPlane *)0x0) {
    lua_pushnil();
    return;
  }
  local_c[0] = lua_getnumber(iVar2);
  local_c[1] = lua_getnumber(iVar3);
  local_c[2] = lua_getnumber(iVar4);
  WalkPlane_SnapTo(this,local_c);
  lua_pushnumber(local_c[0]);
  lua_pushnumber(local_c[1]);
  lua_pushnumber(local_c[2]);
  return;
}
#undef local_10
#undef local_c


/* ---- 0x0049ff00  sputLua_GetAngleBetweenVectorsL ---- */
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Lua opcode: GetAngleBetweenVectors Original name sputLua_GetAngleBetweenVectorsL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetAngleBetweenVectors'); was
   Lua_GetAngleBetweenVectors. */

void sputLua_GetAngleBetweenVectorsL(void)

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
      rdVector_Normalize3Acc(local_c);
      rdVector_Normalize3Acc(local_18);
      fVar4 = stdMath_ArcSin3(local_18[2] * local_c[2] +
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


/* ---- 0x004a00a0  sputLua_GetAngleBetweenActorsL ---- */
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Lua opcode GetAngleBetweenActors(a, b) (Grim). forward = walker heading axis (walker+0x18..0x20,
   not the eased visible yaw); delta = b.pos - a.pos normalized in 3D; returns 90 -
   asin(dot(forward, delta)) = unsigned angle between them, in degrees. (The z of delta in the
   decompile reads forward.z - a.z, probably a decompiler slot mix-up.) Original name
   sputLua_GetAngleBetweenActorsL (the remaster's GrimFandango (Linux): Lua / module table entry
   'GetAngleBetweenActors'); was Lua_GetAngleBetweenActors. */

void sputLua_GetAngleBetweenActorsL(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Puck *pPVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *pAVar5;
  Actor *pAVar6;
  float fVar7;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x40 - 0x4)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(iVar2);
  if (iVar4 != 0) {
    iVar4 = lua_tag(iVar2);
    if (iVar4 == 0x52544341) {
      iVar4 = lua_isuserdata(iVar3);
      if (iVar4 != 0) {
        iVar4 = lua_tag(iVar3);
        if (iVar4 == 0x52544341) {
          iVar2 = lua_getuserdata(iVar2);
          pAVar5 = sputActor_ActorDeref(iVar2);
          iVar2 = lua_getuserdata(iVar3);
          pAVar6 = sputActor_ActorDeref(iVar2);
          if (((pAVar5 != (Actor *)0x0) && (pAVar6 != (Actor *)0x0)) &&
             (pPVar1 = pAVar5->pExtra->pPuck, pPVar1 != (Puck *)0x0)) {
            local_c = pPVar1->aFrame[3];
            local_8 = pPVar1->aFrame[4];
            local_4 = pPVar1->aFrame[5];
            local_18 = pAVar6->aPos[0] - pAVar5->aPos[0];
            local_14 = pAVar6->aPos[1] - pAVar5->aPos[1];
            local_10 = local_4 - pAVar5->aPos[2];
            rdVector_Normalize3Acc(&local_c);
            rdVector_Normalize3Acc(&local_18);
            fVar7 = stdMath_ArcSin3(local_10 * local_4 + local_14 * local_8 + local_18 * local_c);
            lua_pushnumber(90.0 - fVar7);
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


/* ---- 0x004a0230  sputLua_SetAmbientLight ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: SetAmbientLight Original name sputLua_SetAmbientLight (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetAmbientLight'); was Lua_SetAmbientLight. */

void sputLua_SetAmbientLight(void)

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
    pvVar3 = sputRoom_GetCurrentRoom();
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


/* ---- 0x004a0290  sputLua_FindLight ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: FindLight Original name sputLua_FindLight (the remaster's GrimFandango (Linux): Lua /
   module table entry 'FindLight'); was Lua_FindLight. */

void sputLua_FindLight(void)

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
    iVar1 = sputRoom_FindLightByName((void *)0x0,name);
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


/* ---- 0x004a02f0  sputLua_TurnLightOn ---- */
/* Lua opcode: TurnLightOn Original name sputLua_TurnLightOn (the remaster's GrimFandango (Linux):
   Lua / module table entry 'TurnLightOn'); was Lua_TurnLightOn. */

void sputLua_TurnLightOn(void)

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
    iVar1 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar5 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar5;
  }
  pvVar4 = sputRoom_GetLight((void *)0x0,iVar1);
  if (pvVar4 != (void *)0x0) {
    iVar1 = lua_isnil(iVar2);
    *(uint *)((int)pvVar4 + 0x34) = (uint)(iVar1 == 0);
  }
  return;
}

/* ---- 0x004a0380  sputLua_IsLightOn ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: IsLightOn Original name sputLua_IsLightOn (the remaster's GrimFandango (Linux): Lua /
   module table entry 'IsLightOn'); was Lua_IsLightOn. */

void sputLua_IsLightOn(void)

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
    iVar1 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  pvVar3 = sputRoom_GetLight((void *)0x0,iVar1);
  if ((pvVar3 != (void *)0x0) && (*(int *)((int)pvVar3 + 0x34) != 0)) {
    lua_pushnumber(1.0);
    return;
  }
LAB_004a03f5:
  lua_pushnil();
  return;
}

/* ---- 0x004a0400  sputLua_SetLightType ---- */
/* Lua opcode: SetLightType Original name sputLua_SetLightType (the remaster's GrimFandango (Linux):
   Lua / module table entry 'SetLightType'); was Lua_SetLightType. */

void sputLua_SetLightType(void)

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
  pvVar4 = sputRoom_GetCurrentRoom();
  iVar5 = lua_isnumber(iVar2);
  if (iVar5 == 0) {
    iVar5 = lua_isstring(iVar2);
    if (iVar5 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar2);
    iVar2 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar8 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar8;
  }
  pvVar6 = sputRoom_GetLight((void *)0x0,iVar2);
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

/* ---- 0x004a0530  sputLua_GetLightType ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: GetLightType Original name sputLua_GetLightType (the remaster's GrimFandango (Linux):
   Lua / module table entry 'GetLightType'); was Lua_GetLightType. */

void sputLua_GetLightType(void)

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
    iVar1 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  pvVar3 = sputRoom_GetLight((void *)0x0,iVar1);
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

/* ---- 0x004a05e0  sputLua_SetLightPosition ---- */
/* Lua opcode: SetLightPosition Original name sputLua_SetLightPosition (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetLightPosition'); was Lua_SetLightPosition. */

void sputLua_SetLightPosition(void)

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
    iVar2 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar11 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar11;
  }
  pvVar7 = sputRoom_GetCurrentRoom();
  if ((((pvVar7 != (void *)0x0) &&
       (pvVar8 = sputRoom_GetLight((void *)0x0,iVar2), pvVar8 != (void *)0x0)) &&
      (iVar6 = lua_isnumber(iVar3), iVar6 != 0)) &&
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


/* ---- 0x004a0760  sputLua_GetLightPosition ---- */
/* Lua opcode: GetLightPosition Original name sputLua_GetLightPosition (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetLightPosition'); was Lua_GetLightPosition. */

void sputLua_GetLightPosition(void)

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
    iVar1 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  pvVar3 = sputRoom_GetCurrentRoom();
  if (pvVar3 != (void *)0x0) {
    pvVar3 = sputRoom_GetLight((void *)0x0,iVar1);
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

/* ---- 0x004a0800  sputLua_SetLightRotation ---- */
/* Lua opcode: SetLightRotation Original name sputLua_SetLightRotation (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetLightRotation'); was Lua_SetLightRotation. */

void sputLua_SetLightRotation(void)

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
  pvVar6 = sputRoom_GetCurrentRoom();
  iVar7 = lua_isnumber(iVar2);
  if (iVar7 == 0) {
    iVar7 = lua_isstring(iVar2);
    if (iVar7 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar2);
    iVar2 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar10 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar10;
  }
  pvVar8 = sputRoom_GetLight((void *)0x0,iVar2);
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
    rdVector_Rotate3Acc(&local_18,&local_c);
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


/* ---- 0x004a09a0  sputLua_GetLightRotation ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetLightRotation Original name sputLua_GetLightRotation (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetLightRotation'); was Lua_GetLightRotation. */

void sputLua_GetLightRotation(void)

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
    iVar1 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  pvVar3 = sputRoom_GetLight((void *)0x0,iVar1);
  if (pvVar3 != (void *)0x0) {
    rdVector_ExtractAngles((float *)((int)pvVar3 + 0x38),&local_c);
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


/* ---- 0x004a0a50  sputLua_SetLightAngles ---- */
/* Lua opcode: SetLightAngles Original name sputLua_SetLightAngles (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetLightAngles'); was Lua_SetLightAngles. */

void sputLua_SetLightAngles(void)

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
    iVar1 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar6 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar6;
  }
  pvVar5 = sputRoom_GetLight((void *)0x0,iVar1);
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


/* ---- 0x004a0b40  sputLua_GetLightAngles ---- */
/* Lua opcode: GetLightAngles Original name sputLua_GetLightAngles (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetLightAngles'); was Lua_GetLightAngles. */

void sputLua_GetLightAngles(void)

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
    iVar1 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  pvVar3 = sputRoom_GetLight((void *)0x0,iVar1);
  if (pvVar3 != (void *)0x0) {
    lua_pushnumber(*(float *)((int)pvVar3 + 0x4c));
    lua_pushnumber(*(float *)((int)pvVar3 + 0x54));
    return;
  }
LAB_004a0bbc:
  lua_pushnil();
  return;
}

/* ---- 0x004a0bd0  sputLua_PointLightAt ---- */
/* Lua opcode: PointLightAt Original name sputLua_PointLightAt (the remaster's GrimFandango (Linux):
   Lua / module table entry 'PointLightAt'); was Lua_PointLightAt. */

void sputLua_PointLightAt(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *name;
  void *pvVar6;
  Actor *pAVar7;
  longlong lVar8;
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
    iVar1 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar8 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar8;
  }
  pvVar6 = sputRoom_GetLight((void *)0x0,iVar1);
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
      pAVar7 = sputActor_ActorDeref(iVar1);
      local_18 = pAVar7->aPos[0];
      local_14 = pAVar7->aPos[1];
      local_10 = pAVar7->aPos[2];
    }
    local_c = local_18 - *(float *)((int)pvVar6 + 0x20);
    local_8 = local_14 - *(float *)((int)pvVar6 + 0x24);
    local_4 = local_10 - *(float *)((int)pvVar6 + 0x28);
    rdVector_Normalize3Acc(&local_c);
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


/* ---- 0x004a0da0  sputLua_SetLightIntensity ---- */
/* Lua opcode: SetLightIntensity Original name sputLua_SetLightIntensity (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetLightIntensity'); was Lua_SetLightIntensity.
    */

void sputLua_SetLightIntensity(void)

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
  pvVar4 = sputRoom_GetCurrentRoom();
  iVar5 = lua_isnumber(iVar2);
  if (iVar5 == 0) {
    iVar5 = lua_isstring(iVar2);
    if (iVar5 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar2);
    iVar2 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar8 = (longlong)lua_getnumber(iVar2);
    iVar2 = (int)lVar8;
  }
  pvVar6 = sputRoom_GetLight((void *)0x0,iVar2);
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


/* ---- 0x004a0e90  sputLua_GetLightIntensity ---- */
/* Lua opcode: GetLightIntensity Original name sputLua_GetLightIntensity (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetLightIntensity'); was Lua_GetLightIntensity.
    */

void sputLua_GetLightIntensity(void)

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
    iVar1 = sputRoom_FindLightByName((void *)0x0,name);
  }
  else {
    lVar4 = (longlong)lua_getnumber(iVar1);
    iVar1 = (int)lVar4;
  }
  pvVar3 = sputRoom_GetLight((void *)0x0,iVar1);
  if (pvVar3 != (void *)0x0) {
    lua_pushnumber(*(float *)((int)pvVar3 + 0x44));
    return;
  }
LAB_004a0f08:
  lua_pushnil();
  return;
}

/* ---- 0x004a13d0  sputLua_ImGetMasterVol ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ImGetMasterVol Original name sputLua_ImGetMasterVol (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImGetMasterVol'); was Lua_ImGetMasterVol. */

void __fastcall sputLua_ImGetMasterVol(undefined4 param_1)

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


/* ---- 0x004a1400  sputLua_ImSetMasterVol ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetMasterVol Original name sputLua_ImSetMasterVol (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImSetMasterVol'); was Lua_ImSetMasterVol. */

void sputLua_ImSetMasterVol(void)

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

/* ---- 0x004a1440  sputLua_ImGetSfxVol ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ImGetSfxVol Original name sputLua_ImGetSfxVol (the remaster's GrimFandango (Linux):
   Lua / module table entry 'ImGetSfxVol'); was Lua_ImGetSfxVol. */

void __fastcall sputLua_ImGetSfxVol(undefined4 param_1)

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


/* ---- 0x004a1470  sputLua_ImSetSfxVol ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetSfxVol Original name sputLua_ImSetSfxVol (the remaster's GrimFandango (Linux):
   Lua / module table entry 'ImSetSfxVol'); was Lua_ImSetSfxVol. */

void sputLua_ImSetSfxVol(void)

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

/* ---- 0x004a14b0  sputLua_ImGetVoiceVol ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ImGetVoiceVol Original name sputLua_ImGetVoiceVol (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImGetVoiceVol'); was Lua_ImGetVoiceVol. */

void __fastcall sputLua_ImGetVoiceVol(undefined4 param_1)

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


/* ---- 0x004a14e0  sputLua_ImSetVoiceVol ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetVoiceVol Original name sputLua_ImSetVoiceVol (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImSetVoiceVol'); was Lua_ImSetVoiceVol. */

void sputLua_ImSetVoiceVol(void)

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

/* ---- 0x004a1520  sputLua_ImGetMusicVol ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ImGetMusicVol Original name sputLua_ImGetMusicVol (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImGetMusicVol'); was Lua_ImGetMusicVol. */

void __fastcall sputLua_ImGetMusicVol(undefined4 param_1)

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


/* ---- 0x004a1550  sputLua_ImSetMusicVol ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetMusicVol Original name sputLua_ImSetMusicVol (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImSetMusicVol'); was Lua_ImSetMusicVol. */

void sputLua_ImSetMusicVol(void)

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

/* ---- 0x004a1640  sputLua_ImSetState ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetState Original name sputLua_ImSetState (the remaster's GrimFandango (Linux): Lua
   / module table entry 'ImSetState'); was Lua_ImSetState. */

void sputLua_ImSetState(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    gimlib_SetImuseState((int)lVar3);
  }
  return;
}

/* ---- 0x004a16d0  sputLua_ImSetCuePoint ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetCuePoint Original name sputLua_ImSetCuePoint (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImSetCuePoint'); was Lua_ImSetCuePoint. */

void sputLua_ImSetCuePoint(void)

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

/* ---- 0x004a17f0  sputLua_ImGetMemoryFootprint ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: ImGetMemoryFootprint Original name sputLua_ImGetMemoryFootprint (the remaster's
   GrimFandango (Linux): Lua / module table entry 'ImGetMemoryFootprint'); was
   Lua_ImGetMemoryFootprint. */

void sputLua_ImGetMemoryFootprint(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  uVar1 = iMUSE_GetMemoryFootprint();
  lua_pushnumber((float)uVar1);
  return;
}
#undef local_c


/* ---- 0x004a1820  sputLua_ImGetSoundCacheSize ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: ImGetSoundCacheSize Original name sputLua_ImGetSoundCacheSize (the remaster's
   GrimFandango (Linux): Lua / module table entry 'ImGetSoundCacheSize'); was
   Lua_ImGetSoundCacheSize. */

void sputLua_ImGetSoundCacheSize(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  uVar1 = iMUSE_GetSoundCacheSize();
  lua_pushnumber((float)uVar1);
  return;
}
#undef local_c


/* ---- 0x004a1850  sputLua_SetGamma ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: SetGamma Original name sputLua_SetGamma (the remaster's GrimFandango (Linux): Lua /
   module table entry 'SetGamma'); was Lua_SetGamma. */

void sputLua_SetGamma(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float gamma;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (g_dwGrimlib_mode != 4)) {
    gamma = lua_getnumber(iVar1);
    sputRender_SetGamma(gamma);
  }
  return;
}
#undef local_8


/* ---- 0x004a1890  sputLua_SetActorWalkDominate ---- */
/* Lua opcode: SetActorWalkDominate Original name sputLua_SetActorWalkDominate (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorWalkDominate'); was
   Lua_SetActorWalkDominate. */

void sputLua_SetActorWalkDominate(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar2 = lua_isnil(iVar2);
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      sputActor_SetWalkDominate(actor,iVar2);
    }
  }
  return;
}

/* ---- 0x004a1900  sputLua_SetActorConstrain ---- */
/* Lua opcode: SetActorConstrain Original name sputLua_SetActorConstrain (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorConstrain'); was Lua_SetActorConstrain.
    */

void sputLua_SetActorConstrain(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar2 = lua_isnil(iVar2);
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      sputActor_SetActorConstrain(actor,(uint)(iVar2 == 0));
    }
  }
  return;
}

/* ---- 0x004a1970  sputLua_RenderModeUser ---- */
/* Lua opcode: RenderModeUser Original name sputLua_RenderModeUser (the remaster's GrimFandango
   (Linux): Lua / module table entry 'RenderModeUser'); was Lua_RenderModeUser. */

void sputLua_RenderModeUser(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if ((iVar2 != 0) && (g_dwGrimlib_mode == 4)) {
    sputSmush_Pause(0);
    sputRender_ForceRefresh();
    g_dwGrimlib_mode = GetPrevMode();
    return;
  }
  iVar1 = lua_isnil(iVar1);
  if ((iVar1 == 0) && (g_dwGrimlib_mode != 4)) {
    SetPrevMode(g_dwGrimlib_mode);
    sputSmush_Pause(1);
    g_dwGrimlib_mode = 4;
  }
  return;
}

/* ---- 0x004a19f0  sputLua_DimScreen ---- */
/* Lua opcode: DimScreen Original name sputLua_DimScreen (the remaster's GrimFandango (Linux): Lua /
   module table entry 'DimScreen'); was Lua_DimScreen. */

void sputLua_DimScreen(void)

{
  sputRender_Dim(0,2);
  return;
}

/* ---- 0x004a1a00  sputLua_DimRegion ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_28 */
/* WARNING: Variable defined which should be unmapped: local_38 */
/* WARNING: Variable defined which should be unmapped: local_34 */
/* WARNING: Variable defined which should be unmapped: local_30 */
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: DimRegion Original name sputLua_DimRegion (the remaster's GrimFandango (Linux): Lua /
   module table entry 'DimRegion'); was Lua_DimRegion. */

void sputLua_DimRegion(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  longlong lVar9;
  float scale;
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
  scale = lua_getnumber(iVar5);
  sputRender_DimRegion((int)lVar6,(int)lVar7,(int)lVar8,(int)lVar9,scale);
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


/* ---- 0x004a1ae0  sputLua_SetSpeechMode ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: SetSpeechMode Original name sputLua_SetSpeechMode (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetSpeechMode'); was Lua_SetSpeechMode. */

void sputLua_SetSpeechMode(void)

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
      sputActor_SetSpeechMode(1);
    }
    else {
      if (iVar1 == 2) {
        sputActor_SetSpeechMode(2);
        return;
      }
      if (iVar1 == 3) {
        sputActor_SetSpeechMode(3);
        return;
      }
    }
  }
  return;
}

/* ---- 0x004a1b40  sputLua_GetSpeechMode ---- */
/* Lua opcode: GetSpeechMode Original name sputLua_GetSpeechMode (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetSpeechMode'); was Lua_GetSpeechMode. */

void sputLua_GetSpeechMode(void)

{
  byte bVar1;
  
  bVar1 = sputActor_GetSpeechMode();
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

/* ---- 0x004a1b80  sputLua_ActorShadow ---- */
/* Lua opcode: ActorShadow Original name sputLua_ActorShadow (the remaster's GrimFandango (Linux):
   Lua / module table entry 'ActorShadow'); was Lua_ActorShadow. */

void sputLua_ActorShadow(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if ((iVar2 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      iVar1 = sputActor_ActorHasShadow(actor);
      if (iVar1 != 0) {
        lua_pushnumber(1.0);
        return;
      }
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a1bf0  sputLua_ActivateActorShadow ---- */
/* Lua opcode: ActivateActorShadow Original name sputLua_ActivateActorShadow (the remaster's
   GrimFandango (Linux): Lua / module table entry 'ActivateActorShadow'); was
   Lua_ActivateActorShadow. */

void sputLua_ActivateActorShadow(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *actor;
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
      actor = sputActor_ActorDeref(iVar1);
      iVar1 = lua_isnil(iVar3);
      active = (uint)(iVar1 == 0);
      lVar5 = (longlong)lua_getnumber(iVar2);
      sputActor_ActivateActorShadow(actor,(int)lVar5,active);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a1c90  sputLua_SetActorShadowPlane ---- */
/* Lua opcode: SetActorShadowPlane Original name sputLua_SetActorShadowPlane (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorShadowPlane'); was
   Lua_SetActorShadowPlane. */

void sputLua_SetActorShadowPlane(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  char *pcVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      pcVar4 = (char *)lua_getstring(iVar2);
      sputActor_SetShadowPlane(actor,pcVar4);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a1d10  sputLua_SetActorShadowPoint ---- */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: SetActorShadowPoint Original name sputLua_SetActorShadowPoint (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorShadowPoint'); was
   Lua_SetActorShadowPoint. */

void sputLua_SetActorShadowPoint(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  Actor *actor;
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
      actor = sputActor_ActorDeref(iVar1);
      z = lua_getnumber(iVar4);
      y = lua_getnumber(iVar3);
      x = lua_getnumber(iVar2);
      sputActor_SetShadowPoint(actor,x,y,z);
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


/* ---- 0x004a1dc0  sputLua_SetActiveShadow ---- */
/* Lua opcode: SetActiveShadow Original name sputLua_SetActiveShadow (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetActiveShadow'); was Lua_SetActiveShadow. */

void sputLua_SetActiveShadow(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      lVar4 = (longlong)lua_getnumber(iVar2);
      actor->pExtra->nActiveShadow = (int)lVar4;
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a1e50  sputLua_ActorDistToShadowPlane ---- */
/* Lua opcode: ActorDistToShadowPlane Original name sputLua_ActorDistToShadowPlane (the remaster's
   GrimFandango (Linux): Lua / module table entry 'ActorDistToShadowPlane'); was
   Lua_ActorDistToShadowPlane. */

void sputLua_ActorDistToShadowPlane(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ActorExtra *pAVar1;
  float n;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *actor;
  longlong lVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  lVar5 = (longlong)lua_getnumber(iVar3);
  iVar3 = (int)lVar5;
  iVar4 = lua_isuserdata(iVar2);
  if (iVar4 != 0) {
    iVar4 = lua_tag(iVar2);
    if ((iVar4 == 0x52544341) && (iVar2 != 0)) {
      iVar2 = lua_getuserdata(iVar2);
      actor = sputActor_ActorDeref(iVar2);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      pAVar1 = actor->pExtra;
      n = actor->aPos[1] * pAVar1->aShadows[iVar3].aPlane[1] +
          pAVar1->aShadows[iVar3].aPlane[2] * actor->aPos[2] +
          pAVar1->aShadows[iVar3].aPlane[0] * actor->aPos[0] + pAVar1->aShadows[iVar3].aPlane[3];
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


/* ---- 0x004a1f30  sputLua_AddShadowClipPlane ---- */
/* Lua opcode: AddShadowPlane Original name sputLua_AddShadowClipPlane (the remaster's GrimFandango
   (Linux): Lua / module table entry 'AddShadowPlane'); was Lua_AddShadowPlane. */

void sputLua_AddShadowClipPlane(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  char *sectorName;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      sectorName = (char *)lua_getstring(iVar2);
      sputActor_AddShadowClipPlane(actor,actor->pExtra->nActiveShadow,sectorName);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a1fd0  sputLua_SetActorShadowValid ---- */
/* Lua opcode: SetActorShadowValid Original name sputLua_SetActorShadowValid (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorShadowValid'); was
   Lua_SetActorShadowValid. */

void sputLua_SetActorShadowValid(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      lVar4 = (longlong)lua_getnumber(iVar2);
      sputActor_SetShadowValid(actor,actor->pExtra->nActiveShadow,(int)lVar4);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a2070  sputLua_KillActorShadows ---- */
/* Lua opcode: KillActorShadows Original name sputLua_KillActorShadows (the remaster's GrimFandango
   (Linux): Lua / module table entry 'KillActorShadows'); was Lua_KillActorShadows. */

void sputLua_KillActorShadows(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if ((iVar2 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      sputActor_ResetShadows(actor);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a20d0  sputLua_SetShadowColor ---- */
/* Lua opcode: SetShadowColor Original name sputLua_SetShadowColor (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetShadowColor'); was Lua_SetShadowColor. */

void sputLua_SetShadowColor(void)

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
  sputCostume_SetShadowColor((int)lVar4,iVar2,iVar3);
  return;
}

/* ---- 0x004a2130  sputLua_NewObjectState ---- */
/* Lua opcode: NewObjectState Original name sputLua_NewObjectState (the remaster's GrimFandango
   (Linux): Lua / module table entry 'NewObjectState'); was Lua_NewObjectState. */

void sputLua_NewObjectState(void)

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
  pcVar7 = sputRoom_AddObjectState((int)lVar8,iVar2,bitmap,pcVar7,visible);
  lua_pushusertag(pcVar7,0x54415453);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004a21f0  sputLua_FreeObjectState ---- */
/* Lua opcode: FreeObjectState Original name sputLua_FreeObjectState (the remaster's GrimFandango
   (Linux): Lua / module table entry 'FreeObjectState'); was Lua_FreeObjectState. */

void sputLua_FreeObjectState(void)

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
        sputRoom_RemoveObjectState(state);
      }
    }
  }
  return;
}

/* ---- 0x004a2240  sputLua_SendObjectToBack ---- */
/* Lua opcode: SendObjectToBack Original name sputLua_SendObjectToBack (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SendObjectToBack'); was Lua_SendObjectToBack. */

void sputLua_SendObjectToBack(void)

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
        pvVar4 = sputRoom_GetCurrentRoom();
        iVar2 = *(int *)((int)pvVar4 + 0xac);
        pvVar3 = ObjectState_MoveToBack(pvVar3,*(void **)(iVar2 + 0x128 + iVar1 * 300));
        *(void **)(iVar2 + iVar1 * 300 + 0x128) = pvVar3;
      }
    }
  }
  return;
}

/* ---- 0x004a22b0  sputLua_SendObjectToFront ---- */
/* Lua opcode: SendObjectToFront Original name sputLua_SendObjectToFront (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SendObjectToFront'); was Lua_SendObjectToFront.
    */

void sputLua_SendObjectToFront(void)

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
        pvVar4 = sputRoom_GetCurrentRoom();
        iVar2 = *(int *)((int)pvVar4 + 0xac);
        pvVar3 = ObjectState_MoveToFront(pvVar3,*(void **)(iVar2 + 0x128 + iVar1 * 300));
        *(void **)(iVar2 + iVar1 * 300 + 0x128) = pvVar3;
      }
    }
  }
  return;
}

/* ---- 0x004a2320  sputLua_SetObjectType ---- */
/* Lua opcode: SetObjectType Original name sputLua_SetObjectType (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetObjectType'); was Lua_SetObjectType. */

void sputLua_SetObjectType(void)

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

/* ---- 0x004a2380  sputLua_ActorToClean ---- */
/* Lua opcode: ActorToClean Original name sputLua_ActorToClean (the remaster's GrimFandango (Linux):
   Lua / module table entry 'ActorToClean'); was Lua_ActorToClean. */

void sputLua_ActorToClean(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if ((iVar2 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      sputActor_DrawToClean(actor);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a23e0  sputLua_SetActorCollisionMode ---- */
/* Lua opcode: SetActorCollisionMode Original name sputLua_SetActorCollisionMode (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorCollisionMode'); was
   Lua_SetActorCollisionMode. */

void sputLua_SetActorCollisionMode(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      lVar4 = (longlong)lua_getnumber(iVar2);
      actor->pExtra->nCollisionMode = (int)lVar4;
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a2470  sputLua_SetActorCollisionScale ---- */
/* Lua opcode: SetActorCollisionScale Original name sputLua_SetActorCollisionScale (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorCollisionScale'); was
   Lua_SetActorCollisionScale. */

void sputLua_SetActorCollisionScale(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      fVar4 = lua_getnumber(iVar2);
      actor->pExtra->flCollisionScale = fVar4;
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a2500  sputLua_SetActorOffsetYaw ---- */
/* Lua opcode: SetActorOffsetYaw Original name sputLua_SetActorOffsetYaw (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorOffsetYaw'); was Lua_SetActorOffsetYaw.
    */

void sputLua_SetActorOffsetYaw(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      fVar4 = lua_getnumber(iVar2);
      actor->pExtra->flOffsetYaw = fVar4;
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a2590  sputLua_CacheRect ---- */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* WARNING: Variable defined which should be unmapped: local_24 */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* Lua opcode: CacheRect Original name sputLua_CacheRect (the remaster's GrimFandango (Linux): Lua /
   module table entry 'CacheRect'); was Lua_CacheRect. */

void sputLua_CacheRect(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  Actor *pAVar6;
  char *pcVar7;
  longlong lVar8;
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
      pAVar6 = sputActor_ActorDeref(iVar1);
      if (((pAVar6->nScreenBoxValid == 0) || (pAVar6->aScreenBox[2] < 1)) ||
         (pAVar6->aScreenBox[3] < 1)) {
        lua_pushnil();
        return;
      }
      local_24 = pAVar6->aScreenBox[0];
      local_20 = pAVar6->aScreenBox[1];
      local_1c = pAVar6->aScreenBox[2];
      local_18 = pAVar6->aScreenBox[3];
      goto LAB_004a268a;
    }
  }
  lVar8 = (longlong)lua_getnumber(iVar1);
  local_24 = (uint)lVar8;
  lVar8 = (longlong)lua_getnumber(iVar2);
  local_20 = (uint)lVar8;
  lVar8 = (longlong)lua_getnumber(iVar3);
  local_1c = (uint)lVar8;
  lVar8 = (longlong)lua_getnumber(iVar4);
  local_18 = (uint)lVar8;
LAB_004a268a:
  pcVar7 = sputRender_CreateCacheRect(local_24,local_20,local_1c,local_18);
  lua_pushusertag(pcVar7,0x504f494e);
  return;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_4


/* ---- 0x004a26b0  sputLua_RestoreCacheRect ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: RestoreCacheRect Original name sputLua_RestoreCacheRect (the remaster's GrimFandango
   (Linux): Lua / module table entry 'RestoreCacheRect'); was Lua_RestoreCacheRect. */

void sputLua_RestoreCacheRect(void)

{
  int iVar1;
  int *piVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  piVar2 = (int *)lua_getuserdata(iVar1);
  if ((piVar2 != (int *)0x0) && (*piVar2 == 0x11111111)) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    ((code *)sputRender_RestoreCacheRect)((int)lVar3,unaff_ESI);
  }
  return;
}
#endif


/* ---- 0x004a26f0  sputLua_ResReport ---- */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ResReport Original name sputLua_ResReport (the remaster's GrimFandango (Linux): Lua /
   module table entry 'ResReport'); was Lua_ResReport. */

void __fastcall sputLua_ResReport(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  ((code *)sputResource_ReportAllocations)(param_1);
  iVar1 = daTotalAllocated();
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004a2720  sputLua_HardwareAccelerated ---- */
/* Lua opcode: HardwareAccelerated Original name sputLua_HardwareAccelerated (the remaster's
   GrimFandango (Linux): Lua / module table entry 'HardwareAccelerated'); was
   Lua_HardwareAccelerated. */

void sputLua_HardwareAccelerated(void)

{
  if (g_nSputRender_b3DAcceleration != 0) {
    lua_pushnumber(1.0);
    return;
  }
  lua_pushnumber(0.0);
  return;
}

/* ---- 0x004a2750  sputLua_SetActorClipActive ---- */
/* Lua opcode: SetActorClipActive Original name sputLua_SetActorClipActive (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorClipActive'); was Lua_SetActorClipActive.
    */

void sputLua_SetActorClipActive(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar1 = lua_getuserdata(iVar1);
  actor = sputActor_ActorDeref(iVar1);
  if (actor != (Actor *)0x0) {
    lVar3 = (longlong)lua_getnumber(iVar2);
    sputActor_SetClipPlaneActive(actor,(int)lVar3);
  }
  return;
}

/* ---- 0x004a27b0  sputLua_SetActorClipPlane ---- */
/* Lua opcode: SetActorClipPlane Original name sputLua_SetActorClipPlane (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorClipPlane'); was Lua_SetActorClipPlane.
    */

void sputLua_SetActorClipPlane(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  Actor *actor;
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
  actor = sputActor_ActorDeref(iVar1);
  if (actor != (Actor *)0x0) {
    iVar1 = lua_isnumber(iVar2);
    if (iVar1 != 0) {
      iVar1 = lua_isnumber(iVar3);
      if (iVar1 != 0) {
        iVar1 = lua_isnumber(iVar4);
        if (iVar1 != 0) {
          iVar1 = lua_isnumber(iVar5);
          if (iVar1 != 0) {
            iVar1 = lua_isnumber(iVar6);
            if (iVar1 != 0) {
              iVar1 = lua_isnumber(iVar7);
              if (iVar1 != 0) {
                local_18 = lua_getnumber(iVar2);
                local_14 = lua_getnumber(iVar3);
                local_10 = lua_getnumber(iVar4);
                rdVector_Normalize3Acc(&local_18);
                local_c = lua_getnumber(iVar5);
                local_8 = lua_getnumber(iVar6);
                local_4 = lua_getnumber(iVar7);
                sputActor_SetClipPlane(actor,&local_18,&local_c);
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


/* ---- 0x004a2920  sputLua_MarkDirtyRect ---- */
/* Lua opcode: MarkDirtyRect Original name sputLua_MarkDirtyRect (the remaster's GrimFandango
   (Linux): Lua / module table entry 'MarkDirtyRect'); was Lua_MarkDirtyRect. */

void sputLua_MarkDirtyRect(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  Actor *pAVar6;
  longlong lVar7;
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
      pAVar6 = sputActor_ActorDeref(iVar1);
      if (((pAVar6->nScreenBoxValid != 0) && (0 < pAVar6->aScreenBox[2])) &&
         (0 < pAVar6->aScreenBox[3])) {
        sputRender_MarkDirtyRect(pAVar6->aScreenBox,1);
        return;
      }
      lua_pushnil();
      return;
    }
  }
  lVar7 = (longlong)lua_getnumber(iVar1);
  local_10 = (uint)lVar7;
  lVar7 = (longlong)lua_getnumber(iVar2);
  local_c = (uint)lVar7;
  lVar7 = (longlong)lua_getnumber(iVar3);
  local_8 = (uint)lVar7;
  lVar7 = (longlong)lua_getnumber(iVar4);
  local_4 = (uint)lVar7;
  sputRender_MarkDirtyRect((int *)&local_10,1);
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a2a20  sputLua_FadeOutChore ---- */
/* Lua opcode: FadeOutChore Original name sputLua_FadeOutChore (the remaster's GrimFandango (Linux):
   Lua / module table entry 'FadeOutChore'); was Lua_FadeOutChore. */

void sputLua_FadeOutChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *luaObj;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *pAVar5;
  longlong lVar6;
  longlong lVar7;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  luaObj = (void *)lua_lua2C(2);
  iVar2 = lua_lua2C(3);
  iVar3 = lua_lua2C(4);
  iVar4 = lua_isuserdata(iVar1);
  if ((iVar4 != 0) && (iVar4 = lua_tag(iVar1), iVar4 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    pAVar5 = sputActor_ActorDeref(iVar1);
    lVar6 = (longlong)lua_getnumber(iVar2);
    lVar7 = (longlong)lua_getnumber(iVar3);
    iVar1 = lua_isstring((int)luaObj);
    if ((iVar1 == 0) && (iVar1 = lua_isnumber((int)luaObj), iVar1 == 0)) {
      return;
    }
    iVar1 = FindCostumeInStack(luaObj,pAVar5->pCostumes,(CostumeNode **)&local_4);
    if (iVar1 != 0) {
      sputCostume_FadeKeysOut(*(void **)local_4,(int)lVar6,(int)lVar7);
    }
  }
  return;
}
#undef local_4


/* ---- 0x004a2c10  sputLua_IrisDown ---- */
/* Lua opcode: IrisDown Original name sputLua_IrisDown (the remaster's GrimFandango (Linux): Lua /
   module table entry 'IrisDown'); was Lua_IrisDown. */

void sputLua_IrisDown(void)

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
  sputRender_IrisDown((int)lVar4,iVar2,iVar3);
  return;
}

/* ---- 0x004a2c70  sputLua_IrisUp ---- */
/* Lua opcode: IrisUp Original name sputLua_IrisUp (the remaster's GrimFandango (Linux): Lua /
   module table entry 'IrisUp'); was Lua_IrisUp. */

void sputLua_IrisUp(void)

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
  sputRender_IrisUp((int)lVar4,iVar2,iVar3);
  return;
}

/* ---- 0x004a2cd0  sputLua_IrisComplete ---- */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: IrisComplete Original name sputLua_IrisComplete (the remaster's GrimFandango (Linux):
   Lua / module table entry 'IrisComplete'); was Lua_IrisComplete. */

void __fastcall sputLua_IrisComplete(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ((code *)sputRender_IrisComplete)(param_1);
  lua_pushnumber((float)(iVar1 != 0));
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004a2d00  Lua_TextFileGetLineCount ---- */
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
  puVar5 = fopen(uVar4,((unsigned)(uintptr_t)&DAT_004ec5bc));
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


/* ---- 0x004a2e20  Lua_TextFileGetLine ---- */
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


/* ---- 0x004a2ee0  sputLua_ScreenShot ---- */
/* Lua opcode: ScreenShot Original name sputLua_ScreenShot (the remaster's GrimFandango (Linux): Lua
   / module table entry 'ScreenShot'); was Lua_ScreenShot. */

void sputLua_ScreenShot(void)

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
  pcVar4 = sputRender_ScreenShot(iVar1,iVar2);
  if (pcVar4 != (char *)0x0) {
    lua_pushusertag(pcVar4,0x46554256);
    return;
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a2f90  sputLua_SaveScreen ---- */
/* Lua opcode: SaveScreen Original name sputLua_SaveScreen (the remaster's GrimFandango (Linux): Lua
   / module table entry 'SaveScreen'); was Lua_SaveScreen. */

void sputLua_SaveScreen(void)

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
      sputRender_SaveScreen(filename);
    }
  }
  return;
}

/* ---- 0x004a2fd0  sputLua_GetSaveGameImage ---- */
/* Lua opcode: GetSaveGameImage Original name sputLua_GetSaveGameImage (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetSaveGameImage'); was Lua_GetSaveGameImage. */

void sputLua_GetSaveGameImage(void)

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
  pcVar3 = sputMain_GetSaveGameImage(pcVar3);
  if (pcVar3 == (char *)0x0) {
    lua_pushnil();
    return;
  }
  sputRender_ColorCorrect
            (*(ushort **)(pcVar3 + 0x5c),*(int *)(pcVar3 + 0x10) * *(int *)(pcVar3 + 0xc));
  lua_pushusertag(pcVar3,0x46554256);
  return;
}

/* ---- 0x004a3040  sputLua_GetImage ---- */
/* Lua opcode: GetImage Original name sputLua_GetImage (the remaster's GrimFandango (Linux): Lua /
   module table entry 'GetImage'); was Lua_GetImage. */

void sputLua_GetImage(void)

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
    bitmap = stdLoadImage(pcVar3,iVar2,iVar4);
    if (bitmap != (void *)0x0) {
      pcVar3 = (char *)**(undefined4 **)((int)bitmap + 0x78);
      pcVar3[0x60] = '\x1f';
      pcVar3[0x61] = -8;
      pcVar3[0x62] = '\0';
      pcVar3[99] = '\0';
      **(undefined4 **)((int)bitmap + 0x78) = 0;
      stdBitmap_Free(bitmap);
      sputRender_ColorCorrect
                (*(ushort **)(pcVar3 + 0x5c),*(int *)(pcVar3 + 0x10) * *(int *)(pcVar3 + 0xc));
      sputRender_ColorCorrect((ushort *)(pcVar3 + 0x60),1);
      lua_pushusertag(pcVar3,0x46554256);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a30e0  sputLua_FreeImage ---- */
/* Lua opcode: FreeImage Original name sputLua_FreeImage (the remaster's GrimFandango (Linux): Lua /
   module table entry 'FreeImage'); was Lua_FreeImage. */

void sputLua_FreeImage(void)

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
      stdDisplay_VBufferFree(surface);
    }
  }
  return;
}

/* ---- 0x004a3130  sputLua_BlastImage ---- */
/* Lua opcode: BlastImage Original name sputLua_BlastImage (the remaster's GrimFandango (Linux): Lua
   / module table entry 'BlastImage'); was Lua_BlastImage. */

void sputLua_BlastImage(void)

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

/* ---- 0x004a31f0  sputLua_BlastRect ---- */
/* Lua opcode: BlastRect Original name sputLua_BlastRect (the remaster's GrimFandango (Linux): Lua /
   module table entry 'BlastRect'); was Lua_BlastRect. */

void sputLua_BlastRect(void)

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
        sputRender_ColorCorrect((ushort *)&local_14,1);
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
      stdDisplay_VBufferLock((void *)local_4);
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
      stdDisplay_VBufferUnlock((void *)local_4);
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


/* ---- 0x004a34c0  sputLua_SaveGameCallback ---- */
/* system.saveGameCallback(); the script answers with SubmitSaveGameData Original name
   sputLua_SaveGameCallback (the remaster's GrimFandango (Linux): strings: 'saveGameCallback'); was
   Lua_CallSaveGameCallback. */

void __cdecl sputLua_SaveGameCallback(void *writeFn)

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
  g_pTheWriter = writeFn;
  g_nTotSaveBytes = 0;
  lua_beginblock();
  iVar3 = lua_getref(g_nLrSystemTable);
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
  if (g_nTotSaveBytes == 0) {
    (*(code *)writeFn)(&g_nTotSaveBytes,4);
  }
  lua_endblock();
  return;
}
#undef local_4


/* ---- 0x004a3720  sputLua_GetSaveGameData ---- */
/* Lua opcode: GetSaveGameData Original name sputLua_GetSaveGameData (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetSaveGameData'); was Lua_GetSaveGameData. */

void sputLua_GetSaveGameData(void)

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
        local_84 = PUN(uint,(float)(float)(int)local_90);
        local_90 = local_90 + 1;
        lua_pushnumber(PUN(float,local_84));
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


/* ---- 0x004a3830  sputLua_GetTextSpeed ---- */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: GetTextSpeed Original name sputLua_GetTextSpeed (the remaster's GrimFandango (Linux):
   Lua / module table entry 'GetTextSpeed'); was Lua_GetTextSpeed. */

void __fastcall sputLua_GetTextSpeed(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ((code *)sputActor_GetActorTextRate)(param_1);
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004a3850  sputLua_SetTextSpeed ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: SetTextSpeed Original name sputLua_SetTextSpeed (the remaster's GrimFandango (Linux):
   Lua / module table entry 'SetTextSpeed'); was Lua_SetTextSpeed. */

void sputLua_SetTextSpeed(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    sputActor_SetActorTextRate((int)lVar3);
  }
  return;
}

/* ---- 0x004a3890  sputLua_FindFileOnAnyCD ---- */
/* Lua opcode: FindFileOnAnyCD Original name sputLua_FindFileOnAnyCD (the remaster's GrimFandango
   (Linux): Lua / module table entry 'FindFileOnAnyCD'); was Lua_FindFileOnAnyCD. */

void sputLua_FindFileOnAnyCD(void)

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
      a2 = (char *)(*g_pSputLuaHS->pAlloc)
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
      (*g_pSputLuaHS->pFree)(a2);
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


/* ---- 0x004a3a10  sputLua_ActorPuckOrient ---- */
/* Lua opcode: ActorPuckOrient Original name sputLua_ActorPuckOrient (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ActorPuckOrient'); was Lua_ActorPuckOrient. */

void sputLua_ActorPuckOrient(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  longlong lVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      pAVar4 = sputActor_ActorDeref(iVar1);
      iVar1 = lua_isnil(iVar2);
      if (iVar1 == 0) {
        lVar5 = (longlong)lua_getnumber(iVar2);
        if ((int)lVar5 != 0) {
          pAVar4->dwFlags = pAVar4->dwFlags | 0x10;
          return;
        }
      }
      pAVar4->dwFlags = pAVar4->dwFlags & 0xffffffef;
    }
  }
  return;
}

/* ---- 0x004a3aa0  sputLua_GetTickCount ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetTickCount Original name sputLua_GetTickCount (the remaster's GrimFandango (Linux):
   Lua / module table entry 'GetTickCount'); was Lua_GetTickCount. */

void sputLua_GetTickCount(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  uVar1 = GetTickCount();
  lua_pushnumber((float)uVar1);
  return;
}
#undef local_c


/* ---- 0x004a3ae0  sputLua_SetActorInvClipNode ---- */
/* Lua opcode: SetActorInvClipNode Original name sputLua_SetActorInvClipNode (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorInvClipNode'); was
   Lua_SetActorInvClipNode. */

void sputLua_SetActorInvClipNode(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  longlong lVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnil(iVar2);
      if (iVar3 == 0) {
        lVar4 = (longlong)lua_getnumber(iVar2);
        iVar2 = (int)lVar4;
      }
      else {
        iVar2 = -1;
      }
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      if (actor->pExtra == (ActorExtra *)0x0) {
        sputActor_AllocateActorExtra(actor);
      }
      actor->pExtra->nInvClipNode = iVar2;
    }
  }
  return;
}

/* ---- 0x004a3b80  sputLua_SetWalkSystemFadeTime ---- */
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: SetWalkSystemFadeTime Original name sputLua_SetWalkSystemFadeTime (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetWalkSystemFadeTime'); was
   Lua_SetWalkSystemFadeTime. */

void sputLua_SetWalkSystemFadeTime(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 == 0) {
    lVar3 = (longlong)lua_getnumber(iVar1);
    sputActor_SetWalkSystemFadeTime((int)lVar3);
  }
  return;
}

/* ---- 0x004be180  Lua_LightMgrStartup ---- */
/* Debug light manager dialog (Lua LightMgrStartup). Creates the dialog, a keyboard hook and a
   helper actor wearing x_spot.cos */

void Lua_LightMgrStartup(void)

{
  int iVar1;
  Actor *actor;
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
      (*g_pStd_HS->pDebug)(s_LightManager_Startup__Could_not_c_004f0d34);
    }
    else {
      iVar2 = 0;
      iVar1 = Win_GetInstance();
      g_hLightEdHook = (void *)SetWindowsHookExA(2,((unsigned)(uintptr_t)LightEd_KeyboardProc),iVar1,iVar2);
    }
    if (UINT_004f0d0c == 0xffffffff) {
      UINT_004f0d0c = sputActor_AllocateActor();
    }
    g_pLightEdMarkerActor = sputActor_ActorDeref(UINT_004f0d0c);
    sputActor_SetCostume(g_pLightEdMarkerActor,s_x_spot_cos_004f0d28,0);
    actor = (Actor *)sputRoom_GetCurrentRoomName();
    sputRoom_AddActor(actor,(char *)g_pLightEdMarkerActor);
    sputActor_EnableWalkSystem(g_pLightEdMarkerActor,0);
    g_pLightEdMarkerActor->dwFlags = g_pLightEdMarkerActor->dwFlags | 2;
    Lua_LightMgrSetChange();
    return;
  }
  Lua_LightMgrShutdown();
  return;
}

/* ---- 0x004be260  Lua_LightMgrSetChange ---- */
/* Lua opcode: LightMgrSetChange */

void Lua_LightMgrSetChange(void)

{
  Actor *actor;
  
  if (g_hLightEdDialog != (void *)0x0) {
    g_pLightEdSet = sputRoom_GetCurrentRoom();
    actor = (Actor *)sputRoom_GetCurrentRoomName();
    if (g_pLightEdMarkerActor != (Actor *)0x0) {
      sputRoom_AddActor(actor,(char *)g_pLightEdMarkerActor);
    }
    LightMgr_Refresh();
    LightMgr_UpdateDialog(g_hLightEdDialog);
  }
  return;
}

/* ---- 0x004be2a0  Lua_LightMgrShutdown ---- */
/* Lua opcode: LightMgrShutdown */

void Lua_LightMgrShutdown(void)

{
  if (g_hLightEdHook != (void *)0x0) {
    UnhookWindowsHookEx((int)g_hLightEdHook);
  }
  if (g_hLightEdDialog != (void *)0x0) {
    DestroyWindow((int)g_hLightEdDialog);
    g_hLightEdDialog = (void *)0x0;
  }
  if (g_pLightEdMarkerActor != (Actor *)0x0) {
    sputRoom_RemoveActor(g_pLightEdMarkerActor->aSetName,g_pLightEdMarkerActor);
    g_pLightEdMarkerActor->aSetName[0] = '\0';
    g_pLightEdMarkerActor->dwFlags = g_pLightEdMarkerActor->dwFlags | 2;
    g_pLightEdMarkerActor = (Actor *)0x0;
  }
  return;
}
