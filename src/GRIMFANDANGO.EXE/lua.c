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

void __cdecl sputLua_Is3DHardwareEnabledL(void)

{
  if (g_pStd3D_CurDevice != (Std3DDevice *)0x0) {
    lua_pushnumber(1.0f);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00401cb8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lua_pushnil();
  return;
}

/* ---- 0x00401cc0  Lua_SetHardwareState ---- */
/* Lua opcode: SetHardwareState */

void __cdecl Lua_SetHardwareState(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = lua_lua2C(1);
  uVar1 = UINT_00901758;
  uVar3 = UINT_00900530;
  if (g_pStd3D_CurDevice == (Std3DDevice *)0x0) {
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

void __cdecl Lua_GetVideoDevices(void)

{
  uint local_10;
  
  lua_pushnumber((float)UINT_00901758);
  if (g_pStd3D_CurDevice != (Std3DDevice *)0x0) {
    lua_pushnumber((float)UINT_00900530);
    return;
  }
  lua_pushnumber(-1.0f);
  return;
}

/* ---- 0x00401da0  Lua_SetVideoDevices ---- */
/* Lua opcode: SetVideoDevices */

void __cdecl Lua_SetVideoDevices(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  longlong lVar6;
  float fVar7;
  uint local_4;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  uVar1 = UINT_00901758;
  if (g_pStd3D_CurDevice == (Std3DDevice *)0x0) {
    local_4 = 0xffffffff;
  }
  else {
    local_4 = UINT_00900530;
  }
  iVar4 = lua_isnumber(iVar2);
  if (iVar4 != 0) {
    lua_isnumber(iVar3);
  }
  fVar7 = lua_getnumber(iVar2);
  lVar6 = FTOL((float10)fVar7);
  UINT_004dd340 = (uint)lVar6;
  puVar5 = (uint *)(UINT_004dd340 * 0x10 + (int)g_pDisplayModes);
  UINT_004dd344 =
       Display_FindClosestMode((VideoMode *)&UINT_004f4d38,(VideoMode *)puVar5[1],*puVar5);
  fVar7 = lua_getnumber(iVar3);
  lVar6 = FTOL((float10)fVar7);
  UINT_004dd348 = (uint)lVar6;
  if ((((-1 < (int)UINT_004dd340) && ((int)UINT_004dd340 < (int)g_dwStdDisplay_numDevices)) &&
      (-2 < (int)UINT_004dd348)) &&
     (((int)UINT_004dd348 < *(int *)(UINT_004dd340 * 0x10 + 8 + (int)g_pDisplayModes) &&
      ((UINT_004dd340 != uVar1 || (UINT_004dd348 != local_4)))))) {
    UINT_004f5a50 = 1;
  }
  return;
}

/* ---- 0x00401e90  Lua_Enumerate3DDevices ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* Lua opcode: Enumerate3DDevices */

void __cdecl Lua_Enumerate3DDevices(void)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  uint uVar4;
  int iVar5;
  longlong lVar6;
  float fVar7;
  uint local_1c;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    return;
  }
  fVar7 = lua_getnumber(iVar1);
  lVar6 = FTOL((float10)fVar7);
  iVar1 = (int)lVar6;
  iVar2 = lua_createtable();
  if (((&UINT_00902d6c)[iVar1 * 0xa6] != 0) || ((&UINT_00902d68)[iVar1 * 0xa6] == 0)) {
    lua_pushobject(iVar2);
    lua_pushnumber(-1.0f);
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

/* ---- 0x00401fb0  Lua_EnumerateVideoDevices ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* Lua opcode: EnumerateVideoDevices */

void __cdecl Lua_EnumerateVideoDevices(void)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  uint local_1c;
  
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

/* ---- 0x00482880  grimlib_NextSetup ---- */
/* Lua opcode: NextSetup Original name grimlib_NextSetup (the remaster's GrimFandango (Linux): Lua /
   module table entry 'NextSetup'); was Lua_NextSetup. */

void __cdecl grimlib_NextSetup(void)

{
  Set *pSVar1;
  
  pSVar1 = sputRoom_GetCurrentRoom();
  grimlib_MakeCurrentSetup((pSVar1->nCurSetup + 1U) % (uint)pSVar1->nSetups);
  return;
}

/* ---- 0x004828a0  grimlib_PreviousSetup ---- */
/* Lua opcode: PreviousSetup Original name grimlib_PreviousSetup (the remaster's GrimFandango
   (Linux): Lua / module table entry 'PreviousSetup'); was Lua_PreviousSetup. */

void __cdecl grimlib_PreviousSetup(void)

{
  Set *pSVar1;
  
  pSVar1 = sputRoom_GetCurrentRoom();
  grimlib_MakeCurrentSetup((uint)(pSVar1->nCurSetup + -1 + pSVar1->nSetups) % (uint)pSVar1->nSetups)
  ;
  return;
}

/* ---- 0x00486f50  sputRender_ClearIris ---- */
/* Lua opcode: IrisClear Original name sputRender_ClearIris (the remaster's GrimFandango (Linux):
   Lua / module table entry 'IrisClear'); was Lua_IrisClear. */

void __cdecl sputRender_ClearIris(void)

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

void __cdecl sputPrimitive_DrawLine(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
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
  float fVar12;
  uint local_30;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  uint local_14;
  uint local_10;
  uint local_c;
  
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
          fVar12 = lua_getnumber(iVar1);
          lVar7 = FTOL((float10)fVar12);
          fVar12 = lua_getnumber(iVar2);
          lVar8 = FTOL((float10)fVar12);
          fVar12 = lua_getnumber(iVar3);
          lVar9 = FTOL((float10)fVar12);
          fVar12 = lua_getnumber(local_1c);
          lVar10 = FTOL((float10)fVar12);
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
              fVar12 = lua_getnumber(iVar1);
              lVar11 = FTOL((float10)fVar12);
              local_18 = (uint)lVar11;
            }
          }
          uVar6 = PrimitiveQueue_addLine
                            (g_dwPrimitiveQ,(int)lVar7,(int)lVar8,(int)lVar9,(int)lVar10,local_1c,
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
#undef local_18
#undef local_1c


/* ---- 0x00489a80  sputPrimitive_DrawPolygon ---- */
/* WARNING: Variable defined which should be unmapped: local_38 */
/* Lua opcode: DrawPolygon Original name sputPrimitive_DrawPolygon (the remaster's GrimFandango
   (Linux): Lua / module table entry 'DrawPolygon'); was Lua_DrawPolygon. */

void __cdecl sputPrimitive_DrawPolygon(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint uVar7;
  code *pcVar8;
  longlong lVar9;
  float fVar10;
  uint local_38;
  uint local_24;
  uint local_20;
  uint local_1c;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  
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
        fVar10 = lua_getnumber(iVar2);
        lVar9 = FTOL((float10)fVar10);
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
          fVar10 = lua_getnumber(iVar2);
          lVar9 = FTOL((float10)fVar10);
          puVar6[-1] = (int)lVar9;
          lua_pushobject(iVar1);
          local_24 = local_24 + 2;
          lua_pushnumber((float)iVar3);
          iVar2 = (*pcVar8)();
          iVar3 = lua_isnil(iVar2);
          if (iVar3 == 0) {
            fVar10 = lua_getnumber(iVar2);
            lVar9 = FTOL((float10)fVar10);
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
      uVar5 = PrimitiveQueue_addPolygon(g_dwPrimitiveQ,uVar5,(int *)local_14,local_18,local_c);
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
#undef local_c


/* ---- 0x00489d70  sputPrimitive_DrawRectangle ---- */
/* WARNING: Variable defined which should be unmapped: local_34 */
/* Lua opcode: DrawRectangle Original name sputPrimitive_DrawRectangle (the remaster's GrimFandango
   (Linux): Lua / module table entry 'DrawRectangle'); was Lua_DrawRectangle. */

void __cdecl sputPrimitive_DrawRectangle(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
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
  float fVar13;
  uint local_34;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  uint local_1c;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  uint local_10;
  uint local_c;
  
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
    fVar13 = lua_getnumber(iVar1);
    lVar8 = FTOL((float10)fVar13);
    fVar13 = lua_getnumber(iVar2);
    lVar9 = FTOL((float10)fVar13);
    fVar13 = lua_getnumber(iVar3);
    lVar10 = FTOL((float10)fVar13);
    fVar13 = lua_getnumber(iVar4);
    lVar11 = FTOL((float10)fVar13);
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
        fVar13 = lua_getnumber(iVar1);
        lVar12 = FTOL((float10)fVar13);
        local_18 = (uint)lVar12;
      }
    }
    uVar7 = PrimitiveQueue_addRect
                      (g_dwPrimitiveQ,(int)lVar8,(int)lVar9,(int)lVar10,(int)lVar11,local_20,
                       local_14,local_18);
    lua_pushnumber((float)uVar7);
    return;
  }
  lua_pushnil();
  return;
}
#undef local_14
#undef local_18
#undef local_20


/* ---- 0x00489fe0  sputPrimitive_ChangePrimitive ---- */
/* Lua opcode: ChangePrimitive Original name sputPrimitive_ChangePrimitive (the remaster's
   GrimFandango (Linux): Lua / module table entry 'ChangePrimitive'); was Lua_ChangePrimitive. */

void __cdecl sputPrimitive_ChangePrimitive(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  longlong lVar7;
  float fVar8;
  uint local_14;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  uint local_c;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  uint local_4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(iVar1);
  if (iVar3 == 0) {
    return;
  }
  iVar3 = lua_istable(iVar2);
  if (iVar3 != 0) {
    fVar8 = lua_getnumber(iVar1);
    lVar7 = FTOL((float10)fVar8);
    iVar1 = (int)lVar7;
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_color_004e8368);
    iVar3 = lua_gettable();
    iVar4 = lua_isuserdata(iVar3);
    if ((iVar4 != 0) && (iVar4 = lua_tag(iVar3), iVar4 == 0x524c4f43)) {
      uVar5 = lua_getuserdata(iVar3);
      PIECE(local_10,2,1) = (byte)(uVar5 >> 0x10);
      PrimitiveQueue_changeColor
                (g_dwPrimitiveQ,iVar1,
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
      fVar8 = lua_getnumber(iVar3);
      lVar7 = FTOL((float10)fVar8);
      PrimitiveQueue_changeLayer(g_dwPrimitiveQ,iVar1,(int)lVar7);
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
        fVar8 = lua_getnumber(iVar3);
        lVar7 = FTOL((float10)fVar8);
        local_8 = (uint)lVar7;
      }
      iVar3 = lua_isnumber(iVar4);
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        fVar8 = lua_getnumber(iVar4);
        lVar7 = FTOL((float10)fVar8);
        iVar3 = (int)lVar7;
      }
      PrimitiveQueue_move(g_dwPrimitiveQ,iVar1,local_8,iVar3);
    }
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_x_004e8374);
    iVar3 = lua_gettable();
    lua_pushobject(iVar2);
    lua_pushstring(PTR_s_y_004e8378);
    iVar4 = lua_gettable();
    iVar6 = lua_isnumber(iVar3);
    if ((iVar6 != 0) || (iVar6 = lua_isnumber(iVar4), iVar6 != 0)) {
      local_8 = 0xffffffff;
      iVar6 = lua_isnumber(iVar3);
      if (iVar6 != 0) {
        fVar8 = lua_getnumber(iVar3);
        lVar7 = FTOL((float10)fVar8);
        local_8 = (uint)lVar7;
      }
      iVar3 = lua_isnumber(iVar4);
      if (iVar3 == 0) {
        iVar3 = -1;
      }
      else {
        fVar8 = lua_getnumber(iVar4);
        lVar7 = FTOL((float10)fVar8);
        iVar3 = (int)lVar7;
      }
      PrimitiveQueue_moveTo(g_dwPrimitiveQ,iVar1,local_8,iVar3);
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
        fVar8 = lua_getnumber(iVar3);
        lVar7 = FTOL((float10)fVar8);
        local_8 = (uint)lVar7;
      }
      iVar3 = lua_isnumber(iVar4);
      if (iVar3 == 0) {
        iVar3 = -1;
      }
      else {
        fVar8 = lua_getnumber(iVar4);
        lVar7 = FTOL((float10)fVar8);
        iVar3 = (int)lVar7;
      }
      PrimitiveQueue_moveEndpoint(g_dwPrimitiveQ,iVar1,local_8,iVar3);
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
      fVar8 = lua_getnumber(iVar3);
      lVar7 = FTOL((float10)fVar8);
      iVar3 = (int)lVar7;
    }
    iVar4 = lua_isnumber(iVar2);
    if (iVar4 != 0) {
      fVar8 = lua_getnumber(iVar2);
      lVar7 = FTOL((float10)fVar8);
      iVar6 = (int)lVar7;
    }
    PrimitiveQueue_changeDimensions(g_dwPrimitiveQ,iVar1,iVar3,iVar6);
    return;
  }
  return;
}
#undef local_10
#undef local_8


/* ---- 0x0048a460  sputPrimitive_KillPrimitive ---- */
/* Lua opcode: KillPrimitive Original name sputPrimitive_KillPrimitive (the remaster's GrimFandango
   (Linux): Lua / module table entry 'KillPrimitive'); was Lua_KillPrimitive. */

void __cdecl sputPrimitive_KillPrimitive(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    PrimitiveQueue_deletePrimitive(g_dwPrimitiveQ,(int)lVar3);
  }
  return;
}

/* ---- 0x0048a4a0  sputPrimitive_PurgeQueue ---- */
/* Lua opcode: PurgePrimitiveQueue Original name sputPrimitive_PurgeQueue (the remaster's
   GrimFandango (Linux): Lua / module table entry 'PurgePrimitiveQueue'); was
   Lua_PurgePrimitiveQueue. */

void sputPrimitive_PurgeQueue(void)

{
  PrimitiveQueue_purge((int *)g_dwPrimitiveQ);
  PrimitiveQueue_resetId();
  return;
}

/* ---- 0x0048ad60  sputText_SetOffscreenTextPosL ---- */
/* Lua opcode: SetOffscreenTextPos Original name sputText_SetOffscreenTextPosL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetOffscreenTextPos'); was
   Lua_SetOffscreenTextPos. */

void __cdecl sputText_SetOffscreenTextPosL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(iVar1);
  if (iVar3 == 0) {
    g_nSubtitleDefaultX = 0x140;
  }
  else {
    fVar5 = lua_getnumber(iVar1);
    lVar4 = FTOL((float10)fVar5);
    g_nSubtitleDefaultX = (int)lVar4;
  }
  iVar1 = lua_isnumber(iVar2);
  if (iVar1 != 0) {
    fVar5 = lua_getnumber(iVar2);
    lVar4 = FTOL((float10)fVar5);
    g_nSubtitleDefaultY = (int)lVar4;
    return;
  }
  g_nSubtitleDefaultY = 0x1c2;
  return;
}

/* ---- 0x0048ade0  sputText_SetEmergencyFontL ---- */
/* Lua opcode: SetEmergencyFont Original name sputText_SetEmergencyFontL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetEmergencyFont'); was Lua_SetEmergencyFont. */

void __cdecl sputText_SetEmergencyFontL(void)

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

void __cdecl sputText_LocalizeStringL(void)

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

void __cdecl sputText_MakeColorL(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  longlong lVar9;
  float fVar10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  iVar3 = lua_lua2C(1);
  iVar4 = lua_lua2C(2);
  iVar5 = lua_lua2C(3);
  iVar6 = lua_lua2C(4);
  iVar7 = lua_isnumber(iVar3);
  if (iVar7 == 0) {
    iVar7 = 0;
  }
  else {
    fVar10 = lua_getnumber(iVar3);
    lVar9 = FTOL((float10)fVar10);
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
      fVar10 = lua_getnumber(iVar3);
      lVar9 = FTOL((float10)fVar10);
      iVar7 = (int)lVar9;
    }
    if (iVar7 < 0x100) {
      iVar7 = lua_isnumber(iVar3);
      if (iVar7 == 0) goto LAB_0048af7b;
      fVar10 = lua_getnumber(iVar3);
      lVar9 = FTOL((float10)fVar10);
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
    fVar10 = lua_getnumber(iVar4);
    lVar9 = FTOL((float10)fVar10);
    iVar3 = (int)lVar9;
  }
  if (-1 < iVar3) {
    iVar3 = lua_isnumber(iVar4);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      fVar10 = lua_getnumber(iVar4);
      lVar9 = FTOL((float10)fVar10);
      iVar3 = (int)lVar9;
    }
    if (iVar3 < 0x100) {
      iVar3 = lua_isnumber(iVar4);
      if (iVar3 != 0) {
        fVar10 = lua_getnumber(iVar4);
        lVar9 = FTOL((float10)fVar10);
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
    fVar10 = lua_getnumber(iVar5);
    lVar9 = FTOL((float10)fVar10);
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
      fVar10 = lua_getnumber(iVar5);
      lVar9 = FTOL((float10)fVar10);
      iVar3 = (int)lVar9;
    }
    if (iVar3 < 0x100) {
      iVar3 = lua_isnumber(iVar5);
      if (iVar3 == 0) goto LAB_0048b053;
      fVar10 = lua_getnumber(iVar5);
      lVar9 = FTOL((float10)fVar10);
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
    fVar10 = lua_getnumber(iVar6);
    lVar9 = FTOL((float10)fVar10);
    iVar3 = (int)lVar9;
  }
  if (-1 < iVar3) {
    iVar3 = lua_isnumber(iVar6);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      fVar10 = lua_getnumber(iVar6);
      lVar9 = FTOL((float10)fVar10);
      iVar3 = (int)lVar9;
    }
    if (0xff < iVar3) {
      uVar2 = 0xff;
      goto LAB_0048b0c2;
    }
    iVar3 = lua_isnumber(iVar6);
    if (iVar3 != 0) {
      fVar10 = lua_getnumber(iVar6);
      lVar9 = FTOL((float10)fVar10);
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

/* ---- 0x0048b100  sputText_GetColorComponentsL ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: GetColorComponents Original name sputText_GetColorComponentsL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetColorComponents'); was Lua_GetColorComponents.
    */

void __cdecl sputText_GetColorComponentsL(void)

{
  int iVar1;
  uint uVar2;
  uint local_14;
  
  iVar1 = lua_lua2C(1);
  uVar2 = lua_getuserdata(iVar1);
  lua_pushnumber((float)(uVar2 & 0xff));
  lua_pushnumber((float)(uVar2 >> 8 & 0xff));
  lua_pushnumber((float)(uVar2 >> 0x10 & 0xff));
  return;
}

/* ---- 0x0048b190  sputText_SetActorTalkColorL ---- */
/* Lua opcode: SetActorTalkColor Original name sputText_SetActorTalkColorL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorTalkColor'); was Lua_SetActorTalkColor.
    */

void __cdecl sputText_SetActorTalkColorL(void)

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

void __cdecl sputText_GetActorTalkColorL(void)

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

void __cdecl sputText_SetSayLineDefaultsL(void)

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

void __cdecl sputText_SayLineL(void)

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
          Lua_ParseSayLineTable
                    (iVar1,(int *)&local_3c,(int *)&local_24,(int *)&local_28,(int *)&local_2c,
                     (int *)&local_30);
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

void __cdecl
Lua_ParseSayLineTable
          (int table,int *outBackground,int *outX,int *outY,int *outLayer,int *outSkipLog)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  lua_pushobject(table);
  iVar1 = lua_getref(g_dwLrX);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (*outLayer != 0)) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    *outLayer = (int)lVar3;
  }
  lua_pushobject(table);
  iVar1 = lua_getref(g_dwLrY);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (*outSkipLog != 0)) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    *outSkipLog = (int)lVar3;
  }
  lua_pushobject(table);
  iVar1 = lua_getref(g_dwLrBackground);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar1 = lua_isnil(iVar1);
  if ((iVar1 == 0) && (*outBackground != 0)) {
    *outBackground = 0;
  }
  lua_pushobject(table);
  iVar1 = lua_getref(g_dwLrVolume);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (*outX != 0)) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    *outX = (int)lVar3;
  }
  lua_pushobject(table);
  iVar1 = lua_getref(g_dwLrPan);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (*outY != 0)) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    *outY = (int)lVar3;
  }
  return;
}

/* ---- 0x0048b830  sputText_PrintLineL ---- */
/* Lua opcode: PrintLine Original name sputText_PrintLineL (the remaster's GrimFandango (Linux): Lua
   / module table entry 'PrintLine'); was Lua_PrintLine. */

void __cdecl sputText_PrintLineL(void)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  void *table;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  TextObject *obj;
  uint uVar6;
  TextContext *pTVar7;
  undefined4 *puVar8;
  longlong lVar9;
  uint local_5c;
  int local_58;
  #define local_50 (*(char (*)[32])(_frame + (0x60 - 0x50)))
  #define local_30 (*(undefined4 (*)[12])(_frame + (0x60 - 0x30)))
  
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
      pTVar7 = &g_PrintLineTextCtx;
      puVar8 = local_30;
      for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar8 = pTVar7->pUnused;
        pTVar7 = (TextContext *)&pTVar7->pClipRect;
        puVar8 = puVar8 + 1;
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
        uVar6 = 0xffffffff;
        pcVar4 = pcVar5;
        do {
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          cVar1 = *pcVar4;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        lVar9 = FTOL((float10)((~uVar6 - 1) * UINT_004e8474 + UINT_004e8470) * (float10)16.666668f);
        local_58 = (int)lVar9;
      }
      iVar2 = 0;
      obj = TextObject_New((TextContext *)local_5c,pcVar5);
      sputText_AddToQueue(obj,local_58,iVar2);
    }
  }
  return;
}
#undef local_30
#undef local_50


/* ---- 0x0048b9a0  sputText_IsMessageGoingL ---- */
/* Lua opcode: IsMessageGoing Original name sputText_IsMessageGoingL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsMessageGoing'); was Lua_IsMessageGoing. */

void __cdecl sputText_IsMessageGoingL(void)

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
        lua_pushnumber(1.0f);
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
        lua_pushnumber(1.0f);
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

void __cdecl sputText_ExpireTextQueueL(void)

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

void __cdecl sputText_PurgeTextQueueL(void)

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

void __cdecl sputText_KillTextObjectL(void)

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

void __cdecl sputText_GetFontDimensionsL(void)

{
  int *piVar1;
  uint local_c;
  
  piVar1 = (int *)lua_lua2C(1);
  lua_pushnumber((float)*(int *)(*piVar1 + 4));
  lua_pushnumber((float)*(int *)(*piVar1 + 8));
  lua_pushnumber((float)*(int *)(*piVar1 + 0xc));
  lua_pushnumber((float)*(int *)(*piVar1 + 0x10));
  return;
}

/* ---- 0x0048bbc0  sputText_GetTextObjectDimensionsL ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: GetTextObjectDimensions Original name sputText_GetTextObjectDimensionsL (the
   remaster's GrimFandango (Linux): Lua / module table entry 'GetTextObjectDimensions'); was
   Lua_GetTextObjectDimensions. */

void __cdecl sputText_GetTextObjectDimensionsL(void)

{
  int iVar1;
  int iVar2;
  uint local_14;
  uint local_4;
  
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

/* ---- 0x0048bc50  sputText_GetTextCharPositionL ---- */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* Lua opcode: GetTextCharPosition Original name sputText_GetTextCharPositionL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetTextCharPosition'); was
   Lua_GetTextCharPosition. */

void __cdecl sputText_GetTextCharPositionL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  longlong lVar5;
  float fVar6;
  uint local_18;
  uint local_4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x54584554) {
      iVar1 = lua_getuserdata(iVar1);
      fVar6 = lua_getnumber(iVar2);
      lVar5 = FTOL((float10)fVar6);
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

/* ---- 0x0048bd10  sputText_ChangeTextObjectL ---- */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* Lua opcode: ChangeTextObject Original name sputText_ChangeTextObjectL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'ChangeTextObject'); was Lua_ChangeTextObject. */

void __cdecl sputText_ChangeTextObjectL(void)

{
  int iVar1;
  int iVar2;
  TextObject *textObj;
  void *table;
  char *line;
  uint *puVar3;
  uint local_18;
  uint local_4;
  
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
          line = (char *)lua_getstring((int)table);
          puVar3 = (uint *)sputText_ExtractSayLineData(line,(char *)0x0);
          strncpy((uint *)textObj->aText,puVar3,0x1ff);
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

/* ---- 0x0048be30  sputText_MakeTextObjectL ---- */
/* WARNING: Variable defined which should be unmapped: local_78 */
/* Lua opcode: MakeTextObject Original name sputText_MakeTextObjectL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'MakeTextObject'); was Lua_MakeTextObject. */

void __cdecl sputText_MakeTextObjectL(void)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *pcVar3;
  void *table;
  TextObject *obj;
  TextContext *pTVar4;
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
    obj = TextObject_New((TextContext *)(_frame + (0x90 - 0x30)),pcVar3);
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

void __cdecl sputText_BlastText(void)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *pcVar3;
  VBuffer *pVVar4;
  uint *puVar5;
  void *table;
  TextObject *obj;
  TextContext *pTVar6;
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
    pVVar4 = (VBuffer *)Render_GetBackBuffer();
    stdDisplay_VBufferLock(pVVar4);
    pTVar6 = &g_TextObjectCtx;
    puVar5 = &local_30;
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar5 = (uint)pTVar6->pUnused;
      pTVar6 = (TextContext *)&pTVar6->pClipRect;
      puVar5 = puVar5 + 1;
    }
    puVar5 = Render_GetBackBuffer();
    local_2c = (uint)&local_60;
    *(uint *)local_30 = puVar5[0x17];
    table = (void *)lua_lua2C(2);
    if (table != (void *)0x0) {
      iVar1 = lua_istable((int)table);
      if (iVar1 != 0) {
        GetTextParamsFromTable((TextContext *)&local_30,table,(TextObject *)0x0);
      }
    }
    pcVar3 = sputText_ExtractSayLineData(pcVar3,local_50);
    obj = TextObject_New((TextContext *)&local_30,pcVar3);
    TextObject_Draw(obj,0);
    pVVar4 = (VBuffer *)Render_GetBackBuffer();
    stdDisplay_VBufferUnlock(pVVar4);
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

void __cdecl sputText_GetTranslationModeL(void)

{
  uint local_4;
  
  lua_pushnumber((float)g_nTranslationType);
  return;
}

/* ---- 0x0048c980  sputText_SetTranslationModeL ---- */
/* Lua opcode: SetTranslationMode Original name sputText_SetTranslationModeL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetTranslationMode'); was Lua_SetTranslationMode.
    */

void __cdecl sputText_SetTranslationModeL(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isnumber(iVar1);
    if (iVar2 == 0) {
      return;
    }
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
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

void __cdecl sputCostume_GetKeyLengthL(void)

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
  lua_pushnumber(((float)*(uint *)(iVar1 + 0x34) / *(float *)(piVar3[1] + 0x30)) * 1000.0f);
  return;
}

/* ---- 0x00495900  sputCostume_GetSmushLengthL ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetSmushLength Original name sputCostume_GetSmushLengthL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetSmushLength'); was Lua_GetSmushLength. */

void __cdecl sputCostume_GetSmushLengthL(void)

{
  int iVar1;
  int iVar2;
  char *name;
  uint local_c;
  uint local_4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x534d5348) {
      name = (char *)lua_getuserdata(iVar1);
      iVar1 = sputSmush_GetMovieLength(name);
      lua_pushnumber((float)iVar1);
    }
  }
  return;
}

/* ---- 0x00497830  Lua_Stub ---- */
/* Lua opcodes: PutActorAtOrigin, GetClippedPos, DriveActorTo, WalkActorToInterest, UnLockFont,
   LockSound, UnlockSound, LockCostume, UnlockCostume, PlaySound, PlaySoundAt, PlaySoundAttached,
   IsSoundPlaying, GetSectorVertices, LoadBundle, UnloadBundle
   Shared handler for opcodes that the shipped engine does not implement */

void __cdecl Lua_Stub(char *fmt,...)

{
  return;
}

/* ---- 0x00498d80  sputLua_GetMemoryUsageL ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: GetMemoryUsage Original name sputLua_GetMemoryUsageL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetMemoryUsage'); was Lua_GetMemoryUsage. */

void __cdecl sputLua_GetMemoryUsageL(void)

{
  int iVar1;
  uint local_8;
  uint local_4;
  
  iVar1 = daTotalAllocated();
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x00498da0  sputLua_GetDiskFreeSpaceL ---- */
/* Lua opcode: GetDiskFreeSpace Original name sputLua_GetDiskFreeSpaceL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetDiskFreeSpace'); was Lua_GetDiskFreeSpace. */

void __cdecl sputLua_GetDiskFreeSpaceL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_4 (*(undefined1 (*)[4])(_frame + (0x30 - 0x4)))
  
  GetDiskFreeSpaceA(0,(int)(local_18 + 1),(int)local_18,(int)(local_18 + 2),(int)local_4);
  lua_pushnumber((float)PUN(uint,(float)local_18[0]) * 0.0009765625f * (float)PUN(int,(float)local_18[1]) * 0.0009765625f *
                 (float)PUN(int,(float)local_18[2]));
  return;
}
#undef local_18
#undef local_4


/* ---- 0x00498e20  sputLua_Test ---- */
/* Lua opcode: TEST Original name sputLua_Test (the remaster's GrimFandango (Linux): Lua / module
   table entry 'TEST'); was Lua_TEST. */

void __cdecl sputLua_Test(void)

{
  ShrinkBoxes(0.005f);
  return;
}

/* ---- 0x00498e50  sputLua_ShrinkBoxes ---- */
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

/* ---- 0x00498e90  sputLua_UnShrinkBoxes ---- */
/* Lua opcode: UnShrinkBoxes Original name sputLua_UnShrinkBoxes (the remaster's GrimFandango
   (Linux): Lua / module table entry 'UnShrinkBoxes'); was Lua_UnShrinkBoxes. */

void sputLua_UnShrinkBoxes(void)

{
  WalkPlane_RestoreCache();
  WalkPlane_DestroyCache();
  return;
}

/* ---- 0x00498ea0  sputLua_GetShrinkPosition ---- */
/* Lua opcode: GetShrinkPos Original name sputLua_GetShrinkPosition (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetShrinkPos'); was Lua_GetShrinkPos. */

void __cdecl sputLua_GetShrinkPosition(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  WalkPlane *this;
  float fVar6;
  float fVar7;
  float fVar8;
  float radius;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  float pos [3];
  
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
          fVar8 = lua_getnumber(iVar3);
          radius = lua_getnumber(iVar4);
          pos[0] = fVar6;
          pos[1] = fVar7;
          pos[2] = fVar8;
          WalkPlane_BuildCache();
          ShrinkBoxes(radius);
          this = WalkPlane_PlaneClosest(pos,0x1000);
          if (this != (WalkPlane *)0x0) {
            WalkPlane_ClosestPoint(this,(int)pos);
          }
          sputLua_UnShrinkBoxes();
          if (this != (WalkPlane *)0x0) {
            lua_pushnumber(pos[0]);
            lua_pushnumber(pos[1]);
            lua_pushnumber(pos[2]);
            return;
          }
          lua_pushnil();
        }
      }
    }
  }
  return;
}

/* ---- 0x00499000  sputLua_SetSoundParametersL ---- */
/* Lua opcode: SetSoundParameters Original name sputLua_SetSoundParametersL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetSoundParameters'); was Lua_SetSoundParameters.
    */

void __cdecl sputLua_SetSoundParametersL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  Set *set;
  int iVar6;
  byte pan;
  byte volume;
  longlong lVar7;
  float fVar8;
  uint local_28;
  uint local_24;
  #define local_20 (*(float (*)[3])(_frame + (0x30 - 0x20)))
  #define local_14 (*(float (*)[2])(_frame + (0x30 - 0x14)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  set = sputRoom_GetCurrentRoom();
  if (set != (Set *)0x0) {
    iVar6 = lua_isnil(iVar1);
    if ((((iVar6 != 0) && (iVar6 = lua_isnil(iVar2), iVar6 != 0)) &&
        (iVar6 = lua_isnil(iVar3), iVar6 != 0)) &&
       ((iVar6 = lua_isnil(iVar4), iVar6 != 0 && (iVar6 = lua_isnil(iVar5), iVar6 != 0)))) {
      sputRoom_SetSoundParameters((int)set,0x41000000,0x14,0x7f,0x3fc00000,0x3f4ccccd);
      return;
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
    pan = (byte)local_c;
    if (iVar4 == 0) {
      fVar8 = lua_getnumber(iVar3);
      lVar7 = FTOL((float10)fVar8);
      pan = (byte)lVar7;
    }
    iVar3 = lua_isnil(iVar2);
    volume = (byte)local_8;
    if (iVar3 == 0) {
      fVar8 = lua_getnumber(iVar2);
      lVar7 = FTOL((float10)fVar8);
      volume = (byte)lVar7;
    }
    iVar2 = lua_isnil(iVar1);
    if (iVar2 == 0) {
      local_20[0] = lua_getnumber(iVar1);
    }
    else {
      local_20[0] = local_4;
    }
    sputRoom_SetSoundParameters
              ((int)set,PUN(uint,(float)local_20[0]),volume,pan,PUN(uint,(float)local_20[2]),PUN(uint,(float)local_20[1]));
  }
  return;
}
#undef local_14
#undef local_20
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004991c0  sputLua_GetSoundParametersL ---- */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: GetSoundParameters Original name sputLua_GetSoundParametersL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetSoundParameters'); was Lua_GetSoundParameters.
    */

void __cdecl sputLua_GetSoundParametersL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Set *set;
  uint local_20;
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  set = sputRoom_GetCurrentRoom();
  if (set != (Set *)0x0) {
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
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00499250  sputLua_SetDebugToggleCallback ---- */
/* Original name sputLua_SetDebugToggleCallback (the remaster's GrimFandango (Linux): stores
   pDebugToggleFunc); was Lua_SetDebugKeysCallback. */

void __cdecl sputLua_SetDebugToggleCallback(uint callback)

{
  g_dwDebugToggleFunc = callback;
  return;
}

/* ---- 0x00499260  sputLua_EnginePause ---- */
/* Lua opcode: EnginePause Original name sputLua_EnginePause (the remaster's GrimFandango (Linux):
   Lua / module table entry 'EnginePause'); was Lua_EnginePause. */

void __cdecl sputLua_EnginePause(void)

{
  grimlib_SetPause(1);
  return;
}

/* ---- 0x00499270  sputLua_EngineResume ---- */
/* Lua opcode: EngineResume Original name sputLua_EngineResume (the remaster's GrimFandango (Linux):
   Lua / module table entry 'EngineResume'); was Lua_EngineResume. */

void __cdecl sputLua_EngineResume(void)

{
  grimlib_SetPause(0);
  return;
}

/* ---- 0x00499280  sputLua_EngineDisplay ---- */
/* Lua opcode: EngineDisplay Original name sputLua_EngineDisplay (the remaster's GrimFandango
   (Linux): Lua / module table entry 'EngineDisplay'); was Lua_EngineDisplay. */

void __cdecl sputLua_EngineDisplay(void)

{
  int iVar1;
  longlong lVar2;
  float fVar3;
  
  iVar1 = lua_lua2C(1);
  fVar3 = lua_getnumber(iVar1);
  lVar2 = FTOL((float10)fVar3);
  sputRender_SetPageFlip((int)lVar2);
  return;
}

/* ---- 0x004992b0  sputLua_AllocateActorL ---- */
/* Lua opcode: LoadActor Original name sputLua_AllocateActorL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'LoadActor'); was Lua_LoadActor. */

void __cdecl sputLua_AllocateActorL(void)

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

void __cdecl sputLua_PutActorAtInterestL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Setup *pSVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  Set *pSVar4;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_isuserdata(iVar2);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar2);
    if (iVar3 == 0x52544341) {
      iVar2 = lua_getuserdata(iVar2);
      actor = sputActor_ActorDeref(iVar2);
      pSVar4 = sputRoom_GetCurrentRoom();
      if (pSVar4 != (Set *)0x0) {
        iVar2 = pSVar4->nCurSetup;
        pSVar1 = pSVar4->pSetups;
        local_c = *(uint *)&pSVar1[iVar2].field_0x2c;
        local_8 = *(uint *)&pSVar1[iVar2].field_0x30;
        local_4 = *(uint *)&pSVar1[iVar2].field_0x34;
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

void __cdecl sputLua_SetSelectedActorL(void)

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

void __cdecl sputLua_PutActorAtL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  Actor *actor;
  uint local_10;
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
#undef local_c


/* ---- 0x004994a0  sputLua_PutActorInSetL ---- */
/* Lua opcode: PutActorInSet Original name sputLua_PutActorInSetL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'PutActorInSet'); was Lua_PutActorInSet. */

void __cdecl sputLua_PutActorInSetL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  char *pcVar5;
  void *pvVar6;
  Actor *actor;
  
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
    actor = pAVar4;
    pcVar5 = (char *)lua_getstring(iVar2);
    sputRoom_AddActor(pcVar5,actor);
    if ((((pAVar4->pExtra != (ActorExtra *)0x0) && (iVar1 = lua_isstring(iVar2), iVar1 != 0)) &&
        (pAVar4->pExtra->pPuck != (Puck *)0x0)) && (pAVar4->pExtra->nFollowBoxes != 0)) {
      pcVar5 = (char *)lua_getstring(iVar2);
      pvVar6 = Res_Loaded(0x20544553,pcVar5);
      if (pvVar6 != (void *)0x0) {
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

void __cdecl sputLua_WalkActorVectorL(void)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
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
  uint local_78;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  #define local_54 (*(float (*)[3])(_frame + (0x70 - 0x54)))
  #define local_48 (*(float (*)[3])(_frame + (0x70 - 0x48)))
  #define local_3c (*(uint *)(_frame + (0x70 - 0x3c)))
  #define local_38 (*(float (*)[2])(_frame + (0x70 - 0x38)))
  #define local_30 (*(float (*)[12])(_frame + (0x70 - 0x30)))
  
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
            local_30[9] = 0.0f;
            local_30[10] = 0.0f;
            local_3c = 0;
            local_38[1] = 0.0f;
            local_30[0xb] = 0.0f;
            Matrix_BuildTransform(local_30,(uint)&local_3c);
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
          if (actor->pExtra->flTurnRate < 0.0f) {
            fVar1 = -fVar1;
          }
          fVar12 = sputTime_GetFrameTimeFlex();
          Puck_PointAt(actor->pExtra->pPuck,local_54,fVar12 * fVar1 + fVar12 * fVar1);
          if (90.0f - fVar11 < 90.0f) {
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
#undef local_48
#undef local_54


/* ---- 0x00499800  sputLua_WalkActorForwardL ---- */
/* Lua opcode: WalkActorForward Original name sputLua_WalkActorForwardL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'WalkActorForward'); was Lua_WalkActorForward. */

void __cdecl sputLua_WalkActorForwardL(void)

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

void __cdecl sputLua_WalkActorToL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  Actor *actor;
  Actor *pAVar7;
  uint local_24;
  uint local_20;
  uint local_1c;
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
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
    sputActor_ActorWalkTo(actor,(int)local_18,local_c,(Actor *)0x0);
  }
  return;
}
#undef local_18
#undef local_c


/* ---- 0x004999d0  sputLua_WalkActorToAvoidingL ---- */
/* Lua opcode: WalkActorToAvoiding Original name sputLua_WalkActorToAvoidingL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'WalkActorToAvoiding'); was
   Lua_WalkActorToAvoiding. */

void __cdecl sputLua_WalkActorToAvoidingL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  Actor *actor;
  Actor *other;
  Actor *pAVar8;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
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
    other = sputActor_ActorDeref(iVar1);
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
      pAVar8 = sputActor_ActorDeref(iVar1);
      local_18[0] = pAVar8->aPos[0];
      local_18[1] = pAVar8->aPos[1];
      local_18[2] = pAVar8->aPos[2];
    }
    else {
      local_18[0] = lua_getnumber(iVar3);
      local_18[1] = lua_getnumber(iVar4);
      local_18[2] = lua_getnumber(iVar5);
    }
    local_c[0] = lua_getnumber(iVar6);
    local_c[1] = lua_getnumber(iVar6);
    local_c[2] = lua_getnumber(iVar6);
    sputActor_ActorWalkTo(actor,(int)local_18,local_c,other);
  }
  return;
}
#undef local_18
#undef local_c


/* ---- 0x00499b80  sputLua_IsActorMovingL ---- */
/* Lua opcode: IsActorMoving Original name sputLua_IsActorMovingL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsActorMoving'); was Lua_IsActorMoving. */

void __cdecl sputLua_IsActorMovingL(void)

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
        lua_pushnumber(1.0f);
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

void __cdecl sputLua_IsActorTurningL(void)

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
      if (actor->pExtra->flYawLeft != 0.0f) {
        lua_pushnumber(1.0f);
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

void __cdecl sputLua_SetActorChoreLoopingL(void)

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
  float fVar9;
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
          fVar9 = lua_getnumber(iVar2);
          lVar8 = FTOL((float10)fVar9);
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

void __cdecl sputLua_IsActorRestingL(void)

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
        lua_pushnumber(1.0f);
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

void __cdecl sputLua_IsActorChoringL(void)

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
  uint uVar8;
  longlong lVar9;
  float fVar10;
  uint local_20;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
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
                  lua_pushnumber(1.0f);
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
          fVar10 = lua_getnumber(iVar2);
          lVar9 = FTOL((float10)fVar10);
          uVar6 = Cos_InstChoreStatus(*(int *)local_c,(uint)lVar9);
          if ((uVar6 & 1) != 0) {
            if ((iVar1 == 0) && ((uVar6 & 2) != 0)) {
              return;
            }
            lua_pushobject(iVar2);
            if ((uVar6 & 2) != 0) {
              lua_pushnumber(1.0f);
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
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00499ff0  sputLua_GetActorChoresL ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: GetActorChores Original name sputLua_GetActorChoresL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetActorChores'); was Lua_GetActorChores. */

void __cdecl sputLua_GetActorChoresL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *luaObj;
  int iVar2;
  Actor *pAVar3;
  float fVar4;
  uint uVar5;
  float fVar6;
  uint local_2c;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float (*)[3])(_frame + (0x30 - 0x14)))
  
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
    fVar6 = 0.0f;
    if (local_18 != 0) {
      iVar1 = lua_createtable();
      fVar4 = (float)Cos_InstCountChores(*(int *)local_18);
      local_14[0] = 0.0f;
      local_14[2] = fVar4;
      if (fVar4 != 0.0f) {
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

#endif


/* ---- 0x0049a160  sputLua_GetActorCostumeDepthL ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: GetActorCostumeDepth Original name sputLua_GetActorCostumeDepthL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetActorCostumeDepth'); was
   Lua_GetActorCostumeDepth. */

void __cdecl sputLua_GetActorCostumeDepthL(void)

{
  CostumeNode *pCVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  int iVar5;
  uint local_10;
  uint local_4;
  
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

/* ---- 0x0049a2a0  sputLua_GetActorLoopingChoresL ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: GetActorLoopingChores Original name sputLua_GetActorLoopingChoresL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetActorLoopingChores'); was
   Lua_GetActorLoopingChores. */

void __cdecl sputLua_GetActorLoopingChoresL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *luaObj;
  int iVar2;
  Actor *pAVar3;
  float fVar4;
  uint uVar5;
  float fVar6;
  uint local_2c;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float (*)[3])(_frame + (0x30 - 0x14)))
  
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
    fVar6 = 0.0f;
    if (local_18 != 0) {
      iVar1 = lua_createtable();
      fVar4 = (float)Cos_InstCountChores(*(int *)local_18);
      local_14[0] = 0.0f;
      local_14[2] = fVar4;
      if (fVar4 != 0.0f) {
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

#endif


/* ---- 0x0049a410  sputLua_SetActorColormapL ---- */
/* Source: Scripts/sputLua.cpp (line 2035, from __FILE__/__LINE__ passed to the allocator) Original
   name sputLua_SetActorColormapL (the remaster's GrimFandango (Linux): Lua / module table entry
   'SetActorColormap'); was Lua_SetActorColormap. */

void __cdecl sputLua_SetActorColormapL(void)

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

void __cdecl sputLua_SetActorCostumeL(void)

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
      lua_pushnumber(1.0f);
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

void __cdecl sputLua_PrintActorCostumesL(void)

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

void __cdecl sputLua_PushActorCostumeL(void)

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

void __cdecl sputLua_PopActorCostumeL(void)

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

void __cdecl sputLua_StopActorChoreL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *pAVar4;
  longlong lVar5;
  float fVar6;
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
          fVar6 = lua_getnumber(iVar2);
          lVar5 = FTOL((float10)fVar6);
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

void __cdecl sputLua_PlayActorChoreL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *pAVar4;
  longlong lVar5;
  float fVar6;
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
            fVar6 = lua_getnumber(iVar2);
            lVar5 = FTOL((float10)fVar6);
            iVar1 = Cos_InstPlayChore(*(int *)local_4,(uint)lVar5,iVar1,iVar3);
            if (iVar1 != 0) {
              lua_pushnumber(1.0f);
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

void __cdecl sputLua_CompleteActorChoreL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *pAVar4;
  longlong lVar5;
  float fVar6;
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
            fVar6 = lua_getnumber(iVar2);
            lVar5 = FTOL((float10)fVar6);
            iVar1 = Cos_InstCompleteChore(*(int *)local_4,(uint)lVar5);
            if (iVar1 != 0) {
              lua_pushnumber(1.0f);
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

void __cdecl sputLua_PlayActorChoreLoopingL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *pAVar4;
  longlong lVar5;
  float fVar6;
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
            fVar6 = lua_getnumber(iVar2);
            lVar5 = FTOL((float10)fVar6);
            iVar1 = Cos_InstPlayChore(*(int *)local_4,(uint)lVar5,iVar1,iVar3);
            if (iVar1 != 0) {
              lua_pushnumber(1.0f);
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

void __cdecl sputLua_ActorLookAtL(void)

{
  ActorExtra *pAVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  Actor *actor;
  Actor *pAVar7;
  float fVar8;
  uint local_8;
  uint local_4;
  
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
            fVar8 = 0.0f;
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
          actor->pExtra->aLookAt[2] = 0.0f;
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
        if (((pAVar1->aLookAt[0] == 0.0f) && (pAVar1->aLookAt[1] == 0.0f)) &&
           (pAVar1->aLookAt[2] == 0.0f)) {
          return;
        }
        pAVar1->aLookAt[0] = 0.0f;
        pAVar1->aLookAt[1] = 0.0f;
        pAVar1->aLookAt[2] = 0.0f;
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

/* ---- 0x0049ad30  sputLua_IsActorLookingL ---- */
/* Lua opcode: IsActorLooking Original name sputLua_IsActorLookingL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsActorLooking'); was Lua_IsActorLooking. */

void __cdecl sputLua_IsActorLookingL(void)

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
        lua_pushnumber(1.0f);
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

void __cdecl sputLua_SetActorLookRate(void)

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

void __cdecl sputLua_GetActorLookRate(void)

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

void __cdecl sputLua_SetActorVisibilityL(void)

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

void __cdecl sputLua_SetActorFollowBoxesL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  int enable;
  
  enable = 1;
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
      enable = 0;
    }
    sputActor_EnableWalkSystem(actor,enable);
    return;
  }
  return;
}

/* ---- 0x0049af80  sputLua_ShutUpActorL ---- */
/* Lua opcode: ShutUpActor Original name sputLua_ShutUpActorL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'ShutUpActor'); was Lua_ShutUpActor. */

void __cdecl sputLua_ShutUpActorL(void)

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

void __cdecl sputLua_SetActorFrustrumCull(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  longlong lVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      fVar5 = lua_getnumber(iVar2);
      lVar4 = FTOL((float10)fVar5);
      sputActor_SetFrustrumCull(actor,(int)lVar4);
    }
  }
  return;
}

/* ---- 0x0049b040  sputLua_GetCameraActorL ---- */
/* Lua opcode: GetCameraActor Original name sputLua_GetCameraActorL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetCameraActor'); was Lua_GetCameraActor. */

void __cdecl sputLua_GetCameraActorL(void)

{
  lua_pushusertag((char *)g_nCamActorIndex,0x52544341);
  return;
}

/* ---- 0x0049b060  sputLua_GetActorWalkRateL ---- */
/* Lua opcode: GetActorWalkRate Original name sputLua_GetActorWalkRateL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetActorWalkRate'); was Lua_GetActorWalkRate. */

void __cdecl sputLua_GetActorWalkRateL(void)

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

void __cdecl sputLua_SetActorWalkRateL(void)

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

void __cdecl sputLua_GetActorTurnRateL(void)

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

void __cdecl sputLua_SetActorTurnRateL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  float fVar4;
  uint local_4;
  
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
        if (actor->pExtra->flTurnRate < 0.0f) {
          fVar4 = fVar4 * -1.0f;
        }
        actor->pExtra->flTurnRate = fVar4;
      }
    }
  }
  return;
}

/* ---- 0x0049b280  sputLua_SetActorWalkChoresL ---- */
/* Lua opcode: SetActorWalkChore Original name sputLua_SetActorWalkChoresL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorWalkChore'); was Lua_SetActorWalkChore.
    */

void __cdecl sputLua_SetActorWalkChoresL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *actor;
  longlong lVar4;
  float fVar5;
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
        fVar5 = lua_getnumber(iVar2);
        lVar4 = FTOL((float10)fVar5);
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

void __cdecl sputLua_SetActorTurnChoresL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  void *luaObj;
  int iVar4;
  Actor *actor;
  longlong lVar5;
  float fVar6;
  uint local_8;
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
            fVar6 = lua_getnumber(iVar3);
            lVar5 = FTOL((float10)fVar6);
            iVar1 = (int)lVar5;
            fVar6 = lua_getnumber(iVar2);
            lVar5 = FTOL((float10)fVar6);
            sputActor_SetTurnChores(actor,(int)lVar5,iVar1,(CostumeNode *)local_4);
          }
        }
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049b430  sputLua_SetActorRestChoreL ---- */
/* Lua opcode: SetActorRestChore Original name sputLua_SetActorRestChoreL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorRestChore'); was Lua_SetActorRestChore.
    */

void __cdecl sputLua_SetActorRestChoreL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *actor;
  longlong lVar4;
  float fVar5;
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
        fVar5 = lua_getnumber(iVar2);
        lVar4 = FTOL((float10)fVar5);
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

void __cdecl sputLua_SetActorMumbleChoreL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *luaObj;
  int iVar3;
  Actor *pAVar4;
  longlong lVar5;
  float fVar6;
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
        fVar6 = lua_getnumber(iVar2);
        lVar5 = FTOL((float10)fVar6);
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

void __cdecl sputLua_SetActorTalkChoreL(void)

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
  float fVar8;
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
    fVar8 = lua_getnumber(iVar2);
    lVar7 = FTOL((float10)fVar8);
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
          fVar8 = lua_getnumber(iVar3);
          lVar7 = FTOL((float10)fVar8);
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

void __cdecl sputLua_SetActorHeadL(void)

{
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
  float fVar10;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
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
                  fVar10 = lua_getnumber(iVar4);
                  lVar9 = FTOL((float10)fVar10);
                  iVar1 = (int)lVar9;
                  fVar10 = lua_getnumber(iVar3);
                  lVar9 = FTOL((float10)fVar10);
                  iVar3 = (int)lVar9;
                  fVar10 = lua_getnumber(iVar2);
                  lVar9 = FTOL((float10)fVar10);
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

/* ---- 0x0049b830  sputLua_CanActorSeeL ---- */
/* Lua opcode: CanActorSee Original name sputLua_CanActorSeeL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'CanActorSee'); was Lua_CanActorSee. */

void __cdecl sputLua_CanActorSeeL(void)

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
      local_c[1] = 0.0f;
    }
    else {
      local_c[1] = lua_getnumber(iVar1);
    }
    iVar1 = lua_isnumber(iVar3);
    if (iVar1 == 0) {
      local_c[2] = 0.0f;
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: GetVisibleThings Original name sputLua_GetVisibleThingsL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetVisibleThings'); was Lua_GetVisibleThings. */

void __cdecl sputLua_GetVisibleThingsL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Actor *target;
  int iVar1;
  int iVar2;
  RoomActorNode *pRVar3;
  char *pcVar4;
  uint uVar5;
  uint local_8;
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
  for (pRVar3 = GetRoomActors((char *)(local_8 + 0x7c)); pRVar3 != (RoomActorNode *)0x0;
      pRVar3 = pRVar3->pNext) {
    target = g_pActors + pRVar3->nActor;
    if ((((target != (Actor *)0x0) && (target != (Actor *)local_8)) &&
        ((*(byte *)(local_8 + 4) & 1) == 0)) &&
       (iVar2 = sputActor_CanActorSeeActor((Actor *)local_8,target,&local_4), iVar2 != 0)) {
      lua_pushobject(iVar1);
      uVar5 = 0x52544341;
      pcVar4 = (char *)sputActor_GetActorHandle(target);
      lua_pushusertag(pcVar4,uVar5);
      lua_pushnumber(1.0f);
      lua_settable();
    }
  }
  lua_pushobject(iVar1);
  return;
}
#undef local_4

#endif


/* ---- 0x0049bb10  sputLua_GetActorRectL ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetActorRect Original name sputLua_GetActorRectL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetActorRect'); was Lua_GetActorRect. */

void __cdecl sputLua_GetActorRectL(void)

{
  int iVar1;
  int iVar2;
  Actor *pAVar3;
  uint local_c;
  
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

/* ---- 0x0049bba0  sputLua_GetActorPuckVectorL ---- */
/* Lua opcode: GetActorPuckVector Original name sputLua_GetActorPuckVectorL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetActorPuckVector'); was Lua_GetActorPuckVector.
    */

void __cdecl sputLua_GetActorPuckVectorL(void)

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

void __cdecl sputLua_GetActorYawToPoint(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  int iVar4;
  float n;
  uint local_18;
  uint local_14;
  uint local_10;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
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
        lua_pushstring(s_x_004e8454);
        iVar4 = lua_gettable();
        lua_pushobject(iVar2);
        lua_pushstring(s_y_004e8450);
        iVar1 = lua_gettable();
        lua_pushobject(iVar2);
        lua_pushstring(s_z_004ec3b8);
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
#undef local_c


/* ---- 0x0049be40  sputLua_SetActorReflection ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: SetActorReflection Original name sputLua_SetActorReflection (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorReflection'); was Lua_SetActorReflection.
    */

void __cdecl sputLua_SetActorReflection(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  float angle;
  uint local_c;
  
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

/* ---- 0x0049bec0  sputLua_GetActorPosL ---- */
/* Lua opcode: GetActorPos Original name sputLua_GetActorPosL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'GetActorPos'); was Lua_GetActorPos. */

void __cdecl sputLua_GetActorPosL(void)

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

void __cdecl sputLua_GetActorRotL(void)

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

void __cdecl sputLua_SetActorRotL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  Actor *actor;
  uint local_14;
  uint local_10;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
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
#undef local_c


/* ---- 0x0049c0a0  sputLua_SetActorPitch ---- */
/* Lua opcode: SetActorPitch Original name sputLua_SetActorPitch (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetActorPitch'); was Lua_SetActorPitch. */

void __cdecl sputLua_SetActorPitch(void)

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

void __cdecl sputLua_SetActorRoll(void)

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

void __cdecl sputLua_TurnActorL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  float dir;
  uint local_c;
  
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
        dir = lua_getnumber(iVar2);
        sputActor_Turn(actor,dir);
      }
    }
  }
  return;
}

/* ---- 0x0049c200  sputLua_GetActorSectorL ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetActorSector Original name sputLua_GetActorSectorL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetActorSector'); was Lua_GetActorSector. */

void __cdecl sputLua_GetActorSectorL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  WalkPlane *pWVar5;
  longlong lVar6;
  float fVar7;
  uint local_c;
  
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
        fVar7 = lua_getnumber(iVar2);
        lVar6 = FTOL((float10)fVar7);
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

/* ---- 0x0049c2c0  sputLua_IsActorInSector ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: IsActorInSector Original name sputLua_IsActorInSector (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsActorInSector'); was Lua_IsActorInSector. */

void __cdecl sputLua_IsActorInSector(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  char *sub;
  uint *puVar5;
  WalkPlane *this;
  uint local_10;
  
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
        sub = (char *)lua_getstring(iVar2);
        this = g_pWalkPlane_wp_head;
        if (g_pWalkPlane_wp_head != (WalkPlane *)0x0) {
          do {
            puVar5 = String_ContainsSubstring((uint *)this,sub);
            if (puVar5 != (uint *)0x0) {
              iVar1 = WalkPlane_Within(this,pAVar4->aPos,1);
              if (iVar1 != 0) {
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

/* ---- 0x0049c4c0  sputLua_IsPointInSector ---- */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: IsPointInSector Original name sputLua_IsPointInSector (the remaster's GrimFandango
   (Linux): Lua / module table entry 'IsPointInSector'); was Lua_IsPointInSector. */

void __cdecl sputLua_IsPointInSector(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *sub;
  uint *puVar6;
  WalkPlane *this;
  uint local_20;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
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
    sub = (char *)lua_getstring(iVar4);
    this = g_pWalkPlane_wp_head;
    if (g_pWalkPlane_wp_head != (WalkPlane *)0x0) {
      do {
        puVar6 = String_ContainsSubstring((uint *)this,sub);
        if ((puVar6 != (uint *)0x0) &&
           (iVar1 = WalkPlane_Within(this,local_c,1), iVar1 != 0)) {
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
#undef local_c


/* ---- 0x0049c5e0  sputLua_FindSystemFiles ---- */
/* lua_dofile('_system.lua') Original name sputLua_FindSystemFiles (the remaster's GrimFandango
   (Linux): the only call of grimlib_FindSystemFiles, same body (lua_dofile of _system.lua)); was
   Lua_RunSystemScript. */

int __cdecl sputLua_FindSystemFiles(void)

{
  int iVar1;
  
  iVar1 = lua_dofile(s__system_lua_004ec3bc);
  return (uint)(iVar1 == 0);
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
    lua_pushnumber(1.0f);
  }
  if (str == (char *)0x0) {
    lua_pushnil();
  }
  else {
    lua_pushstring(str);
  }
  iVar1 = lua_getglobal(s_BOOT_004ec3c8);
  iVar1 = lua_callfunction(iVar1);
  return (uint)(iVar1 == 0);
}

/* ---- 0x0049c660  sputLua_CameraChange ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* system.camChangeHandler(from, to) Original name sputLua_CameraChange (the remaster's GrimFandango
   (Linux): aligned call in grimlib_MakeCurrentSetup); was Lua_CallCamChangeHandler. */

void __cdecl sputLua_CameraChange(int fromSetup,int toSetup)

{
  int iVar1;
  int iVar2;
  uint local_c;
  
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

/* ---- 0x0049c6e0  sputLua_PostCameraChange ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* system.postCamChangeHandler(setup) Original name sputLua_PostCameraChange (the remaster's
   GrimFandango (Linux): strings: 'postCamChangeHandler'); was Lua_CallPostCamChangeHandler. */

void __cdecl sputLua_PostCameraChange(int setup)

{
  int iVar1;
  int iVar2;
  uint local_8;
  
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

/* ---- 0x0049ca60  sputLua_RegisterFunctions ---- */
/* lua_openlib() wrapper used to register the 279-entry engine opcode table at 0x004ea8b0 Original
   name sputLua_RegisterFunctions (the remaster's GrimFandango (Linux): aligned call in
   sputLua_Startup, sputPrimitive_Startup, sputText_Startup); was Lua_OpenEngineLib. */

void __cdecl sputLua_RegisterFunctions(int *lib,int count)

{
  lua_openlib(lib,count);
  return;
}

/* ---- 0x0049ca80  sputLua_JustLoadedL ---- */
/* Lua opcode: JustLoaded Original name sputLua_JustLoadedL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'JustLoaded'); was Lua_JustLoaded. */

void __cdecl sputLua_JustLoadedL(void)

{
  uint uVar1;
  
  uVar1 = grimlib_JustLoaded();
  if (uVar1 != 0) {
    lua_pushnumber(1.0f);
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

void __cdecl sputLua_ActorVoiceIs3DL(void)

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
  byte *pbVar3;
  byte *pbVar4;
  longlong lVar5;
  float fVar6;
  byte *pbVar7;
  
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
    pbVar3 = (byte *)lua_getstring((int)luaObj);
    pCVar1 = *outCostume;
    while (pCVar1 != (CostumeNode *)0x0) {
      pbVar7 = pbVar3;
      pbVar4 = (byte *)Cos_InstGetCostume((*outCostume)->dwInstance,(int *)0x0);
      iVar2 = _stricmp(pbVar4,pbVar7);
      if (iVar2 == 0) break;
      pCVar1 = (*outCostume)->pNext;
      *outCostume = pCVar1;
    }
  }
  else {
    fVar6 = lua_getnumber((int)luaObj);
    lVar5 = FTOL((float10)fVar6);
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

void __cdecl sputLua_CheckForFileL(void)

{
  void **ppvVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_isstring(iVar2);
  if (iVar3 != 0) {
    pcVar4 = s_r_004dda54;
    ppvVar1 = &g_pSputLuaHS->pFopen;
    iVar2 = lua_getstring(iVar2);
    iVar2 = (*(code *)*ppvVar1)(iVar2,pcVar4);
    if (iVar2 == 0) {
      lua_pushnil();
      return;
    }
    (*g_pSputLuaHS->pFclose)(iVar2);
    lua_pushnumber(1.0f);
  }
  return;
}

/* ---- 0x0049cd10  sputLua_NukeResourcesL ---- */
/* Lua opcode: NukeResources Original name sputLua_NukeResourcesL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'NukeResources'); was Lua_NukeResources. */

void __cdecl sputLua_NukeResourcesL(void)

{
  sputRoom_SetCurrentRoom((Set *)0x0,0);
  sputActor_NukeCostumeStacks();
  Res_FreeAll();
  g_pShadowMaterial = (void *)0x0;
  return;
}

/* ---- 0x0049cd40  sputLua_DetachFromResourcesL ---- */
/* Lua opcode: DetachFromResources Original name sputLua_DetachFromResourcesL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'DetachFromResources'); was
   Lua_DetachFromResources. */

void __cdecl sputLua_DetachFromResourcesL(void)

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

void __cdecl sputLua_AttachToResourcesL(void)

{
  sputResource_CloseResources();
  grimlib_FindResources();
  return;
}

/* ---- 0x0049cd60  sputLua_SearchForFileOrSwapCDsL ---- */
/* Lua opcode: SearchForFileOrSwapCDs Original name sputLua_SearchForFileOrSwapCDsL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SearchForFileOrSwapCDs'); was
   Lua_SearchForFileOrSwapCDs. */

void __cdecl sputLua_SearchForFileOrSwapCDsL(void)

{
  void **ppvVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *text;
  char *pcVar6;
  uint flags;
  uint local_4;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_lua2C(3);
  iVar5 = lua_isstring(iVar2);
  if (iVar5 != 0) {
    iVar5 = lua_isstring(iVar3);
    if (iVar5 != 0) {
      iVar5 = lua_isstring(iVar4);
      if (iVar5 != 0) {
        pcVar6 = s_r_004dda54;
        ppvVar1 = &g_pSputLuaHS->pFopen;
        iVar5 = lua_getstring(iVar4);
        iVar5 = (*(code *)*ppvVar1)(iVar5,pcVar6);
        if (iVar5 == 0) {
          ImSetState(0);
          ImStopAllSounds();
          SoundsCloseVoiceFile();
          do {
            flags = 1;
            pcVar6 = (char *)lua_getstring(iVar3);
            text = (char *)lua_getstring(iVar2);
            iVar5 = grimPlat_QueryDialog(text,pcVar6,flags);
            if (iVar5 == 2) {
              lua_pushnil();
              lua_pushnil();
              return;
            }
            sputResource_CloseResources();
            grimlib_FindResources();
            pcVar6 = s_r_004dda54;
            ppvVar1 = &g_pSputLuaHS->pFopen;
            iVar5 = lua_getstring(iVar4);
            iVar5 = (*(code *)*ppvVar1)(iVar5,pcVar6);
          } while (iVar5 == 0);
          (*g_pSputLuaHS->pFclose)(iVar5);
          lua_pushnumber(1.0f);
          lua_pushnumber(1.0f);
          return;
        }
        (*g_pSputLuaHS->pFclose)(iVar5);
        lua_pushnumber(1.0f);
        lua_pushnil();
      }
    }
  }
  return;
}

/* ---- 0x0049cea0  sputLua_LoadL ---- */
/* Lua opcode: Load Original name sputLua_LoadL (the remaster's GrimFandango (Linux): Lua / module
   table entry 'Load'); was Lua_Load. */

void __cdecl sputLua_LoadL(void)

{
  int iVar1;
  int iVar2;
  char *filename;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 != 0) {
    grimlib_Load((char *)0x0);
    return;
  }
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    filename = (char *)lua_getstring(iVar1);
    grimlib_Load(filename);
  }
  return;
}

/* ---- 0x0049cef0  sputLua_SaveL ---- */
/* Lua opcode: Save Original name sputLua_SaveL (the remaster's GrimFandango (Linux): Lua / module
   table entry 'Save'); was Lua_Save. */

void __cdecl sputLua_SaveL(void)

{
  int iVar1;
  int iVar2;
  char *filename;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 != 0) {
    grimlib_Save((char *)0x0);
    return;
  }
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    filename = (char *)lua_getstring(iVar1);
    grimlib_Save(filename);
  }
  return;
}

/* ---- 0x0049cf40  sputLua_EnableDebugKeysL ---- */
/* Lua opcode: EnableDebugKeys Original name sputLua_EnableDebugKeysL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'EnableDebugKeys'); was Lua_EnableDebugKeys. */

void __cdecl sputLua_EnableDebugKeysL(void)

{
  g_nGrimlib_bDebugKeys = 1;
  if (g_dwDebugToggleFunc != 0) {
    (*(code *)g_dwDebugToggleFunc)(1);
  }
  return;
}

/* ---- 0x0049cf60  sputLua_WorldToScreenL ---- */
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: WorldToScreen Original name sputLua_WorldToScreenL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'WorldToScreen'); was Lua_WorldToScreen. */

void __cdecl sputLua_WorldToScreenL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint local_2c;
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_c (*(ScreenCoord *)(_frame + (0x30 - 0xc)))
  
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
          lua_pushnumber((float)local_c.nX);
          lua_pushnumber((float)local_c.nY);
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
#undef local_c


/* ---- 0x0049d030  sputLua_ScreenToWorldL ---- */
/* Lua opcode: ScreenToWorld Original name sputLua_ScreenToWorldL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ScreenToWorld'); was Lua_ScreenToWorld. */

void __cdecl sputLua_ScreenToWorldL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  float fVar6;
  float *outPos;
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float (*)[2])(_frame + (0x20 - 0x8)))
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  iVar4 = lua_isnumber(iVar2);
  if (iVar4 != 0) {
    iVar4 = lua_isnumber(iVar3);
    if (iVar4 != 0) {
      fVar6 = lua_getnumber(iVar2);
      lVar5 = FTOL((float10)fVar6);
      if ((int)lVar5 < 0) {
        bVar1 = false;
      }
      else {
        fVar6 = lua_getnumber(iVar2);
        lVar5 = FTOL((float10)fVar6);
        bVar1 = (int)lVar5 < 0x280;
      }
      if (bVar1) {
        fVar6 = lua_getnumber(iVar3);
        lVar5 = FTOL((float10)fVar6);
        if ((int)lVar5 < 0) {
          bVar1 = false;
        }
        else {
          fVar6 = lua_getnumber(iVar3);
          lVar5 = FTOL((float10)fVar6);
          bVar1 = (int)lVar5 < 0x1e0;
        }
        if (bVar1) {
          outPos = &local_c;
          fVar6 = lua_getnumber(iVar3);
          lVar5 = FTOL((float10)fVar6);
          iVar3 = (int)lVar5;
          fVar6 = lua_getnumber(iVar2);
          lVar5 = FTOL((float10)fVar6);
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

void __cdecl sputLua_ConcatFallback(void)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  rdThing *prVar3;
  int iVar4;
  char *fmt;
  Actor *pAVar5;
  rdModel3 *prVar6;
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
           (prVar3 = pAVar5->pCostumes->pMainModel, prVar3 == (rdThing *)0x0)) {
          prVar6 = (rdModel3 *)&DAT_004f5a98;
        }
        else {
          prVar6 = prVar3->pModel;
        }
        sprintf(pcVar10,s__actor_d__s__004ec494,iVar4,prVar6);
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
/* Lua opcode: exit Original name sputLua_ExitL (the remaster's GrimFandango (Linux): Lua / module
   table entry 'exit'); was Lua_exit. */

void __cdecl sputLua_ExitL(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    grimlib_RequestShutdown((int)lVar3);
    return;
  }
  grimlib_RequestShutdown(0);
  return;
}

/* ---- 0x0049d3f0  sputLua_EnableControlL ---- */
/* Lua opcode: EnableControl Original name sputLua_EnableControlL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'EnableControl'); was Lua_EnableControl. */

void __cdecl sputLua_EnableControlL(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    lua_pushnil();
    return;
  }
  fVar4 = lua_getnumber(iVar1);
  lVar3 = FTOL((float10)fVar4);
  sputControl_EnableControl((int)lVar3);
  return;
}

/* ---- 0x0049d430  sputLua_DisableControlL ---- */
/* Lua opcode: DisableControl Original name sputLua_DisableControlL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'DisableControl'); was Lua_DisableControl. */

void __cdecl sputLua_DisableControlL(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    lua_pushnil();
    return;
  }
  fVar4 = lua_getnumber(iVar1);
  lVar3 = FTOL((float10)fVar4);
  sputControl_DisableControl((int)lVar3);
  return;
}

/* ---- 0x0049d470  sputLua_GetControlStateL ---- */
/* Lua opcode: GetControlState Original name sputLua_GetControlStateL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetControlState'); was Lua_GetControlState. */

void __cdecl sputLua_GetControlStateL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  longlong lVar4;
  float fVar5;
  float local_c;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    fVar5 = lua_getnumber(iVar1);
    lVar4 = FTOL((float10)fVar5);
    uVar3 = (uint)lVar4;
    if (uVar3 <= g_nSputControl_numControlSymbols - 1U) {
      if ((g_aControlSymbols[uVar3].dwFlags & 4) != 0) {
        iVar1 = stdControl_ReadKey(g_aControlSymbols[uVar3].nId,&local_4,(int *)&local_8);
        if (iVar1 == 0) {
          lua_pushnil();
        }
        else {
          lua_pushnumber(1.0f);
        }
        if (local_8 != 0) {
          lua_pushnumber(1.0f);
          return;
        }
        lua_pushnil();
        return;
      }
      local_c = stdControl_ReadAxis(g_aControlSymbols[uVar3].nId);
      if ((g_aControlSymbols[uVar3].dwFlags & 8) != 0) {
        local_c = -local_c;
      }
      lua_pushnumber(local_c);
    }
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x0049d550  sputLua_DoCostumeOverrideCallback ---- */
/* Original name sputLua_DoCostumeOverrideCallback (the remaster's GrimFandango (Linux): strings:
   'costumeOverrideHandler'); was Lua_CallCostumeOverrideHandler. */

void __cdecl sputLua_DoCostumeOverrideCallback(void *actor,int flag)

{
  bool bVar1;
  bool bVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  uint local_4;
  
  bVar1 = false;
  bVar2 = false;
  lua_beginblock();
  pcVar3 = (char *)sputActor_GetActorHandle(actor);
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
      lua_pushnumber(1.0f);
    }
    lua_callfunction((int)pcVar6);
  }
  lua_endblock();
  return;
}

/* ---- 0x0049d670  sputLua_DoCostumeMarkerCallback ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* system.costumeMarkerHandler(actor, marker) from keyframe markers Original name
   sputLua_DoCostumeMarkerCallback (the remaster's GrimFandango (Linux): strings:
   'costumeMarkerHandler'); was Lua_CallCostumeMarkerHandler. */

void __cdecl sputLua_DoCostumeMarkerCallback(void *actor,uint marker)

{
  bool bVar1;
  bool bVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint local_1c;
  
  bVar1 = false;
  bVar2 = false;
  if (marker != 0) {
    pcVar3 = (char *)sputActor_GetActorHandle(actor);
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

/* ---- 0x0049d7b0  sputLua_DoUserPaintCallback ---- */
/* system.userPaintHandler() after a restore Original name sputLua_DoUserPaintCallback (the
   remaster's GrimFandango (Linux): strings: 'userPaintHandler'); was Lua_CallUserPaintHandler. */

void __cdecl sputLua_DoUserPaintCallback(void)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint local_4;
  
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

/* ---- 0x0049d890  sputLua_DoExitCallback ---- */
/* system.exitHandler(); returns 1 when a handler existed Original name sputLua_DoExitCallback (the
   remaster's GrimFandango (Linux): strings: 'exitHandler'); was Lua_CallExitHandler. */

uint __cdecl sputLua_DoExitCallback(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint local_4;
  
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

/* ---- 0x0049d970  sputLua_DoPauseCallback ---- */
/* system.pauseHandler() (Pause key) Original name sputLua_DoPauseCallback (the remaster's
   GrimFandango (Linux): strings: 'pauseHandler'); was Lua_CallPauseHandler. */

uint __cdecl sputLua_DoPauseCallback(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint local_4;
  
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
/* Lua opcode: MakeCurrentSetup Original name sputLua_MakeCurrentSetupL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'MakeCurrentSetup'); was Lua_MakeCurrentSetup. */

void __cdecl sputLua_MakeCurrentSetupL(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    grimlib_MakeCurrentSetup((uint)lVar3);
  }
  return;
}

/* ---- 0x0049dbb0  sputLua_GetCurrentSetupL ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: GetCurrentSetup Original name sputLua_GetCurrentSetupL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetCurrentSetup'); was Lua_GetCurrentSetup. */

void __cdecl sputLua_GetCurrentSetupL(void)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  Set *pSVar5;
  char *pcVar6;
  Set *pvVar7;
  void *pvVar8;
  uint local_10;
  uint local_4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    pbVar3 = (byte *)sputRoom_GetCurrentRoomName();
    pbVar4 = (byte *)lua_getstring(iVar1);
    iVar2 = _stricmp(pbVar4,pbVar3);
    if (iVar2 == 0) {
      pSVar5 = sputRoom_GetCurrentRoom();
      if (pSVar5 != (Set *)0x0) {
        pSVar5 = sputRoom_GetCurrentRoom();
        lua_pushnumber((float)pSVar5->nCurSetup);
        return;
      }
      lua_pushnil();
      return;
    }
    pcVar6 = (char *)lua_getstring(iVar1);
    pvVar7 = Res_Loaded(0x20544553,pcVar6);
    if (pvVar7 != (Set *)0x0) {
      pcVar6 = (char *)lua_getstring(iVar1);
      pvVar8 = sputResource_Alloc(0x20544553,pcVar6);
      lua_pushnumber((float)*(int *)((int)pvVar8 + 0xb4));
    }
  }
  return;
}

/* ---- 0x0049dc70  sputLua_MakeCurrentSetL ---- */
/* Lua opcode: MakeCurrentSet Original name sputLua_MakeCurrentSetL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'MakeCurrentSet'); was Lua_MakeCurrentSet. */

void __cdecl sputLua_MakeCurrentSetL(void)

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

void __cdecl sputLua_LockSet(void)

{
  int iVar1;
  int iVar2;
  char *name;
  Set *data;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(iVar1);
    data = sputResource_Alloc(0x20544553,name);
    if ((data != (Set *)0x0) && ((data->lockRef).nValid == 0)) {
      Res_SetReference(&data->lockRef,data,s_C__grimsrc_libs_grimlib_Scripts__004ec38c,0x14b9);
    }
  }
  return;
}

/* ---- 0x0049dd10  sputLua_UnLockSet ---- */
/* Lua opcode: UnLockSet Original name sputLua_UnLockSet (the remaster's GrimFandango (Linux): Lua /
   module table entry 'UnLockSet'); was Lua_UnLockSet. */

void __cdecl sputLua_UnLockSet(void)

{
  int iVar1;
  int iVar2;
  char *name;
  Set *pvVar3;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(iVar1);
    pvVar3 = sputResource_Alloc(0x20544553,name);
    if ((pvVar3 != (Set *)0x0) && ((pvVar3->lockRef).nValid != 0)) {
      Res_RemoveReference(&pvVar3->lockRef);
    }
  }
  return;
}

/* ---- 0x0049dd70  sputLua_MessagePrintL ---- */
/* Lua opcode: PrintMessage Original name sputLua_MessagePrintL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'PrintMessage'); was Lua_PrintMessage. */

void __cdecl sputLua_MessagePrintL(void)

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

void __cdecl Lua_Print_NoOp(void)

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

uint __cdecl sputLua_Startup(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define abStack_20 (*(byte (*)[32])(_frame + (0x30 - 0x20)))
  
  if (UINT_008cab80 != 0) {
    return 1;
  }
  (*g_aLuaMS.pfnStartup)();
  wuRegistry_GetStr(s_TextAllowed_004ec55c,(char *)abStack_20,0x20,&DAT_004f5a98);
  iVar1 = _stricmp(abStack_20,(byte *)s_true_004ec554);
  if (iVar1 != 0) {
    *(undefined4 *)lua_assume_binary_exref = 1;
  }
  lua_iolibopen();
  lua_strlibopen();
  lua_mathlibopen();
  sputLua_RegisterFunctions((int *)&PTR_s_EnginePause_004ea8b0,UINT_004eb168);
  lua_recognizelib(((unsigned)(uintptr_t)&PTR_s_concatfallback_004ea890),4);
  g_nLrSystemTable = Lua_CreateSystemTable();
  iVar1 = lua_getglobal(s_type_004ec54c);
  lua_pushobject(iVar1);
  g_dwLrTypeFunction = lua_ref(1);
  lua_pushCclosure(((unsigned)(uintptr_t)sputLua_TypeOverride),0);
  lua_setglobal(s_type_004ec54c);
  lua_pushnumber(0.0f);
  lua_setglobal(s_NONE_004ec544);
  lua_pushnumber(4096.0f);
  lua_setglobal(s_WALK_004ec53c);
  lua_pushnumber(8192.0f);
  lua_setglobal(s_CAMERA_004ec534);
  lua_pushnumber(16384.0f);
  lua_setglobal(s_SPECIAL_004ec52c);
  lua_pushnumber(32768.0f);
  lua_setglobal(s_HOT_004ec528);
  iVar1 = lua_setfallback(s_concat_004ec520,sputLua_ConcatFallback);
  lua_pushobject(iVar1);
  g_dwLrOldConcatFallback = lua_ref(1);
  *(code **)lua_savehook_exref = sputLua_SaveIndirector;
  *(code **)lua_restorehook_exref = sputLua_RestoreIndirector;
  sputControl_AddCallback(sputLua_NotifyControlHandlers);
  return 0;
}
#undef abStack_20

#endif


/* ---- 0x0049dfa0  sputLua_SaveIndirector ---- */
/* lua_savehook: STAT userdata is written as setup<<16 | index in the setup's object state list
   Original name sputLua_SaveIndirector (the remaster's GrimFandango (Linux): aligned call in
   sputLua_Startup); was Lua_SaveUserdataHook. */

uint __cdecl sputLua_SaveIndirector(int tag,uint value)

{
  ObjectState *pOVar1;
  Set *pSVar2;
  uint uVar3;
  ObjectState **ppOVar4;
  uint uVar5;
  
  if (tag != 0x54415453) {
    return value;
  }
  pSVar2 = sputRoom_GetCurrentRoom();
  if (pSVar2 != (Set *)0x0) {
    uVar5 = 0;
    if (pSVar2->nSetups != 0) {
      ppOVar4 = &pSVar2->pSetups->pObjectStates;
      do {
        uVar3 = 0;
        for (pOVar1 = *ppOVar4; pOVar1 != (ObjectState *)0x0; pOVar1 = pOVar1->pNext) {
          if (pOVar1 == (ObjectState *)value) {
            return uVar5 << 0x10 | uVar3;
          }
          uVar3 = uVar3 + 1;
        }
        uVar5 = uVar5 + 1;
        ppOVar4 = ppOVar4 + 0x4b;
      } while (uVar5 < (uint)pSVar2->nSetups);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

/* ---- 0x0049e020  sputLua_RestoreIndirector ---- */
/* lua_restorehook: rebuilds STAT, FONT and TEXT userdata pointers from their saved ids Original
   name sputLua_RestoreIndirector (the remaster's GrimFandango (Linux): aligned call in
   sputLua_Startup); was Lua_RestoreUserdataHook. */

TextObject * __cdecl sputLua_RestoreIndirector(int tag,TextObject *id)

{
  TextObject *pTVar1;
  Set *pSVar2;
  uint uVar3;
  
  if (tag == 0x54415453) {
    if (id == (TextObject *)0xffffffff) {
      id = (TextObject *)0x0;
    }
    else {
      uVar3 = (uint)id & 0xffff;
      pSVar2 = sputRoom_GetCurrentRoom();
      id = (TextObject *)pSVar2->pSetups[(uint)id >> 0x10].pObjectStates;
      if (uVar3 != 0) {
        do {
          id = *(TextObject **)((int)id->aText + 0xf0);
          uVar3 = uVar3 - 1;
        } while (uVar3 != 0);
        return id;
      }
    }
  }
  else {
    if (tag == 0x544e4f46) {
      pTVar1 = Res_HandleFromSerialNumber(id);
      return pTVar1;
    }
    if (tag == 0x54584554) {
      pTVar1 = sputText_FindSerialNumber((int)id);
      return pTVar1;
    }
  }
  return id;
}

/* ---- 0x0049e0b0  sputLua_NotifyControlHandlers ---- */
/* WARNING: Variable defined which should be unmapped: local_58 */
/* Calls system.buttonHandler / system.axisHandler for every enabled control whose state changed
   (last value kept at control+8) Original name sputLua_NotifyControlHandlers (the remaster's
   GrimFandango (Linux): aligned call in sputLua_Startup); was Lua_DispatchControlHandlers. */

uint __cdecl sputLua_NotifyControlHandlers(void)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  uint uVar6;
  code *pcVar7;
  ControlValue *pCVar8;
  uint local_58;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  float axisValue;
  int keyX;
  int buttonHandler;
  int axisHandler;
  int buttonTable;
  int keyY;
  int axisTable;
  longlong llIndex;
  longlong llKeyX;
  longlong llIndex2;
  
  bVar1 = false;
  bVar2 = false;
  lua_beginblock();
  iVar3 = lua_getref(g_nLrSystemTable);
  lua_pushobject(iVar3);
  lua_pushstring(s_buttonHandler_004ec574);
  iVar3 = lua_gettable();
  buttonTable = iVar3;
  iVar4 = lua_istable(iVar3);
  pcVar7 = lua_isfunction_exref;
  if (iVar4 == 0) {
    iVar4 = lua_isfunction(iVar3);
    if (iVar4 == 0) {
      local_44 = 0;
    }
    else {
      bVar1 = false;
      local_44 = 1;
      buttonHandler = iVar3;
    }
  }
  else {
    lua_pushobject(iVar3);
    lua_pushstring(s_buttonHandler_004ec574);
    buttonHandler = lua_gettable();
    pcVar7 = lua_isfunction_exref;
    iVar3 = lua_isfunction(buttonHandler);
    if (iVar3 != 0) {
      bVar1 = true;
      local_44 = 1;
    }
  }
  iVar3 = lua_getref(g_nLrSystemTable);
  lua_pushobject(iVar3);
  lua_pushstring(s_axisHandler_004ec568);
  iVar3 = lua_gettable();
  axisTable = iVar3;
  iVar4 = lua_istable(iVar3);
  if (iVar4 == 0) {
    iVar4 = (*pcVar7)(iVar3);
    if (iVar4 == 0) {
      local_3c = 0;
    }
    else {
      bVar2 = false;
      local_3c = 1;
      axisHandler = iVar3;
    }
  }
  else {
    lua_pushobject(iVar3);
    lua_pushstring(s_axisHandler_004ec568);
    axisHandler = lua_gettable();
    iVar3 = (*pcVar7)(axisHandler);
    if (iVar3 != 0) {
      bVar2 = true;
      local_3c = 1;
    }
  }
  uVar6 = 0;
  if (g_nSputControl_numControlSymbols != 0) {
    pCVar8 = &g_aControlSymbols[0].uValue;
    do {
      if ((((ControlSymbol *)(pCVar8 + -2))->dwFlags & 1) != 0) {
        if ((((ControlSymbol *)(pCVar8 + -2))->dwFlags & 4) == 0) {
          fVar5 = stdControl_ReadAxis(pCVar8[-1].nState);
          if ((((ControlSymbol *)(pCVar8 + -2))->dwFlags & 8) != 0) {
            fVar5 = -fVar5;
          }
          if ((fVar5 != pCVar8->fValue) && (local_3c != 0)) {
            if (bVar2) {
              lua_pushobject(axisTable);
            }
            PIECE(llIndex2,4,4) = 0;
            PIECE(llIndex2,0,4) = uVar6;
            lua_pushnumber((float)uVar6);
            lua_pushnumber(fVar5);
            lua_callfunction(axisHandler);
            pCVar8->fValue = fVar5;
          }
        }
        else {
          keyX = 0;
          fVar5 = (float)stdControl_ReadKey(pCVar8[-1].nState,&keyX,&keyY);
          if ((fVar5 != (float)pCVar8->nState) && (local_44 != 0)) {
            if (bVar1) {
              lua_pushobject(buttonTable);
            }
            PIECE(llIndex,4,4) = 0;
            PIECE(llIndex,0,4) = uVar6;
            lua_pushnumber((float)uVar6);
            if (fVar5 == 0.0f) {
              lua_pushnil();
            }
            else {
              lua_pushnumber(1.0f);
            }
            PIECE(llKeyX,4,4) = 0;
            PIECE(llKeyX,0,4) = keyX;
            lua_pushnumber((float)(uint)keyX);
            lua_pushnumber((float)keyY);
            lua_callfunction(buttonHandler);
            pCVar8->nState = PUN(int,(float)fVar5);
          }
        }
      }
      uVar6 = uVar6 + 1;
      pCVar8 = pCVar8 + 4;
    } while (uVar6 < (uint)g_nSputControl_numControlSymbols);
  }
  lua_endblock();
  return 0;
}

/* ---- 0x0049e380  Lua_CreateSystemTable ---- */
/* Creates the global `system` table with the controls table and stub camChange/axis/button
   handlers; returns its ref */

uint __cdecl Lua_CreateSystemTable(void)

{
  int iVar1;
  uint systemRef;
  
  iVar1 = lua_createtable();
  lua_pushobject(iVar1);
  lua_setglobal(s_system_004ec584);
  lua_pushobject(iVar1);
  systemRef = lua_ref(1);
  Lua_CreateControlsTable(systemRef);
  iVar1 = lua_getref(systemRef);
  lua_pushobject(iVar1);
  lua_pushstring(s_camChangeHandler_004ec3d0);
  lua_pushCclosure(((unsigned)(uintptr_t)Lua_Stub),0);
  lua_settable();
  iVar1 = lua_getref(systemRef);
  lua_pushobject(iVar1);
  lua_pushstring(s_axisHandler_004ec568);
  lua_pushCclosure(((unsigned)(uintptr_t)Lua_Stub),0);
  lua_settable();
  iVar1 = lua_getref(systemRef);
  lua_pushobject(iVar1);
  lua_pushstring(s_buttonHandler_004ec574);
  lua_pushCclosure(((unsigned)(uintptr_t)Lua_Stub),0);
  lua_settable();
  return systemRef;
}

/* ---- 0x0049e460  Lua_CreateControlsTable ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* system.controls[name] = index for every entry of g_dwSputControl_aControlSymbols (name at
   control+0xc) */

void __cdecl Lua_CreateControlsTable(uint systemRef)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  char **ppcVar4;
  uint local_1c;
  
  iVar1 = lua_createtable();
  iVar2 = lua_getref(systemRef);
  lua_pushobject(iVar2);
  lua_pushstring(s_controls_004ec58c);
  lua_pushobject(iVar1);
  lua_settable();
  uVar3 = 0;
  if (g_nSputControl_numControlSymbols != 0) {
    ppcVar4 = &g_aControlSymbols[0].pName;
    do {
      lua_pushobject(iVar1);
      lua_pushstring(*ppcVar4);
      lua_pushnumber((float)uVar3);
      lua_settable();
      uVar3 = uVar3 + 1;
      ppcVar4 = ppcVar4 + 4;
    } while (uVar3 < (uint)g_nSputControl_numControlSymbols);
  }
  return;
}

/* ---- 0x0049e590  sputLua_SetSoundPosition ---- */
/* Lua opcode: SetSoundPosition Original name sputLua_SetSoundPosition (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetSoundPosition'); was Lua_SetSoundPosition. */

void __cdecl sputLua_SetSoundPosition(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  Set *set;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *pAVar5;
  int iVar6;
  uint sound;
  int iVar7;
  longlong lVar8;
  float fVar9;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(float (*)[3])(_frame + (0x40 - 0x20)))
  uint local_14;
  uint local_10;
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  set = sputRoom_GetCurrentRoom();
  local_20[0] = 8.0f;
  local_20[1] = 1.0f;
  local_24 = CONCAT31(PIECE(local_24,1,3),10);
  local_28 = CONCAT31(PIECE(local_28,1,3),0x7f);
  local_20[2] = 1.5f;
  if (set != (Set *)0x0) {
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
    fVar9 = lua_getnumber(iVar3);
    lVar8 = FTOL((float10)fVar9);
    local_24 = CONCAT31(PIECE(local_24,1,3),(byte)lVar8);
    if (0x7f < (byte)lVar8) {
      local_24 = CONCAT31(PIECE(local_24,1,3),0x7f);
    }
  }
  iVar3 = lua_isnumber(iVar4);
  if (iVar3 != 0) {
    fVar9 = lua_getnumber(iVar4);
    lVar8 = FTOL((float10)fVar9);
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
    sound = lua_getstring(iVar2);
  }
  else {
    fVar9 = lua_getnumber(iVar2);
    lVar8 = FTOL((float10)fVar9);
    sound = (uint)lVar8;
  }
  sputRoom_SetSoundPosition
            (sound,(undefined **)local_c,local_24 & 0xff,local_28 & 0xff,PUN(uint,(float)local_20[0]),
             0x3f4ccccd);
  return;
}
#undef local_20
#undef local_24
#undef local_28
#undef local_c


/* ---- 0x0049e7e0  sputLua_StartFullScreenMovieL ---- */
/* Lua opcode: StartFullscreenMovie Original name sputLua_StartFullScreenMovieL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'StartFullscreenMovie'); was
   Lua_StartFullscreenMovie. */

void __cdecl sputLua_StartFullScreenMovieL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint name;
  uint uVar4;
  uint x;
  uint y;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isstring(iVar1);
  if (iVar3 != 0) {
    y = 0xffffffff;
    x = 0xffffffff;
    iVar2 = lua_isnil(iVar2);
    uVar4 = (uint)(iVar2 == 0);
    iVar2 = 1;
    name = lua_getstring(iVar1);
    uVar4 = grimlib_PlayMovie(name,iVar2,uVar4,x,y);
    if (uVar4 == 1) {
      lua_pushnumber(1.0f);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0049e860  sputLua_PauseMovieL ---- */
/* Lua opcode: PauseMovie Original name sputLua_PauseMovieL (the remaster's GrimFandango (Linux):
   Lua / module table entry 'PauseMovie'); was Lua_PauseMovie. */

void __cdecl sputLua_PauseMovieL(void)

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

void __cdecl sputLua_IsMoviePlayingL(void)

{
  int iVar1;
  
  iVar1 = sputSmush_MoviePlaying();
  if (iVar1 != 0) {
    lua_pushnumber(1.0f);
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

void __fastcall sputLua_FileFindFirst(char *pattern)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *ext;
  uint local_4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isstring(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_isnil(iVar2);
    local_4 = (uint)pattern;
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
    if (g_pFrFileReq != (StdFileSearch *)0x0) {
      sputLua_FileFindNext();
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x0049ea20  sputLua_FileFindNext ---- */
/* Lua opcode: FileFindNext Original name sputLua_FileFindNext (the remaster's GrimFandango (Linux):
   Lua / module table entry 'FileFindNext'); was Lua_FileFindNext. */

void __cdecl sputLua_FileFindNext(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[288] __attribute__((aligned(16)));  /* the original frame below the return address */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  iVar1 = 0;
  if (g_pFrFileReq != (void *)0x0) {
    do {
      iVar1 = stdFileUtil_FindNext(g_pFrFileReq,(StdFileEntry *)(_stkneg + 20));
      if (iVar1 != 1) break;
    } while (local_8 != 0);
    if (local_8 != 0) {
      iVar1 = 0;
    }
  }
  if (iVar1 != 0) {
    lua_pushstring((_stkneg + 20));
    return;
  }
  lua_pushnil();
  return;
}
#undef local_8


/* ---- 0x0049ea90  sputLua_FileFindDispose ---- */
/* Lua opcode: FileFindDispose Original name sputLua_FileFindDispose (the remaster's GrimFandango
   (Linux): Lua / module table entry 'FileFindDispose'); was Lua_FileFindDispose. */

void __cdecl sputLua_FileFindDispose(void)

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

void __cdecl sputLua_QueryDialog(void)

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
        lua_pushnumber(0.0f);
        return;
      }
      if (iVar1 != 7) {
        lua_pushnumber(1.0f);
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

void __cdecl sputLua_InputDialog(void)

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
  uint local_6c;
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


/* ---- 0x0049ec50  sputLua_WriteRegistryValue ---- */
/* Lua opcode: WriteRegistryValue Original name sputLua_WriteRegistryValue (the remaster's
   GrimFandango (Linux): Lua / module table entry 'WriteRegistryValue'); was Lua_WriteRegistryValue.
    */

void __cdecl sputLua_WriteRegistryValue(void)

{
  int iVar1;
  int iVar2;
  char *name;
  char *value;
  float value_00;
  uint local_4;
  
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

/* ---- 0x0049ece0  sputLua_ReadRegistryValue ---- */
/* Lua opcode: ReadRegistryValue Original name sputLua_ReadRegistryValue (the remaster's
   GrimFandango (Linux): Lua / module table entry 'ReadRegistryValue'); was Lua_ReadRegistryValue.
    */

void __cdecl sputLua_ReadRegistryValue(void)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *name;
  float n;
  uint local_104;
  #define local_100 (*(char (*)[256])(_frame + (0x110 - 0x100)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(iVar1);
    iVar1 = wuRegistry_QueryType(name);
    if (iVar1 == 3) {
      n = wuRegistry_GetFloat(name,0.0f);
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


/* ---- 0x0049ed90  sputLua_GetSectorOppositeEdge ---- */
/* Lua opcode: GetSectorOppositeEdge Original name sputLua_GetSectorOppositeEdge (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetSectorOppositeEdge'); was
   Lua_GetSectorOppositeEdge. */

void __cdecl sputLua_GetSectorOppositeEdge(void)

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

void __cdecl sputLua_IsSectorActiveL(void)

{
  int iVar1;
  int iVar2;
  Set *pSVar3;
  char *name;
  WalkPlane *pWVar4;
  longlong lVar5;
  float fVar6;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_0049eea2;
  }
  pSVar3 = sputRoom_GetCurrentRoom();
  if (pSVar3 != (Set *)0x0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) {
      fVar6 = lua_getnumber(iVar1);
      lVar5 = FTOL((float10)fVar6);
      pWVar4 = WalkPlane_PlaneNumbered((int)lVar5);
    }
    else {
      name = (char *)lua_getstring(iVar1);
      pWVar4 = WalkPlane_PlaneNamed(name);
    }
    if ((pWVar4 != (WalkPlane *)0x0) && (pWVar4->nVisible != 0)) {
      lua_pushnumber(1.0f);
    }
  }
LAB_0049eea2:
  lua_pushnil();
  return;
}

/* ---- 0x0049eeb0  sputLua_MakeSectorActiveL ---- */
/* Lua opcode: MakeSectorActive Original name sputLua_MakeSectorActiveL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'MakeSectorActive'); was Lua_MakeSectorActive. */

void __cdecl sputLua_MakeSectorActiveL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *name;
  WalkPlane *pWVar4;
  longlong lVar5;
  float fVar6;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 == 0) && (iVar2 = lua_isstring(iVar1), iVar2 == 0)) {
    return;
  }
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isstring(iVar1);
  if (iVar3 == 0) {
    fVar6 = lua_getnumber(iVar1);
    lVar5 = FTOL((float10)fVar6);
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

void __cdecl sputLua_PreRender(void)

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

void __cdecl sputLua_GetCurrentScript(void)

{
  int iVar1;
  
  iVar1 = lua_currenttask();
  lua_pushtask(iVar1);
  return;
}

/* ---- 0x0049efe0  sputLua_LockFontL ---- */
/* Lua opcode: LockFont Original name sputLua_LockFontL (the remaster's GrimFandango (Linux): Lua /
   module table entry 'LockFont'); was Lua_LockFont. */

void __cdecl sputLua_LockFontL(void)

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

void __cdecl sputLua_LoadCostumeL(void)

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
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: GetPhysicalBytes Original name sputLua_GetPhysicalBytes (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetPhysicalBytes'); was Lua_GetPhysicalBytes. */

void __fastcall sputLua_GetPhysicalBytes(undefined4 unused)

{
  uint uVar1;
  uint local_8;
  uint local_4;
  
  uVar1 = stdPlatform_GetPhysicalRam();
  lua_pushnumber((float)(int)uVar1);
  return;
}

/* ---- 0x0049f0a0  sputLua_SetMemoryUsage ---- */
/* Lua opcode: SetMemoryUsage Original name sputLua_SetMemoryUsage (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetMemoryUsage'); was Lua_SetMemoryUsage. */

void __cdecl sputLua_SetMemoryUsage(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  fVar4 = lua_getnumber(iVar2);
  lVar3 = FTOL((float10)fVar4);
  iVar2 = (int)lVar3;
  fVar4 = lua_getnumber(iVar1);
  lVar3 = FTOL((float10)fVar4);
  sputResource_SetMemoryUsage((int)lVar3,iVar2);
  return;
}

/* ---- 0x0049f2b0  sputLua_GetCameraPositionL ---- */
/* Lua opcode: GetCameraPosition Original name sputLua_GetCameraPositionL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetCameraPosition'); was Lua_GetCameraPosition.
    */

void __cdecl sputLua_GetCameraPositionL(void)

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

void __cdecl sputLua_GetCameraInterestL(void)

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

void __cdecl sputLua_GetCameraFOVL(void)

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

void __cdecl sputLua_GetCameraRollL(void)

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

void __cdecl sputLua_SetCameraPositionL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  uint local_14;
  
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
  rdMatrix_LookAt(g_pSputRender_Camera + 0xc,g_pSputRender_Camera,g_pSputRender_Camera + 3,
                  PUN(uint,(float)g_pSputRender_Camera[6]));
  rdCamera_Update(g_pSputRender_Camera + 0xc);
  return;
}

/* ---- 0x0049f480  sputLua_SetCameraInterestL ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: SetCameraInterest Original name sputLua_SetCameraInterestL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetCameraInterest'); was Lua_SetCameraInterest.
    */

void __cdecl sputLua_SetCameraInterestL(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  uint local_14;
  
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
  rdMatrix_LookAt(g_pSputRender_Camera + 0xc,g_pSputRender_Camera,g_pSputRender_Camera + 3,
                  PUN(uint,(float)g_pSputRender_Camera[6]));
  rdCamera_Update(g_pSputRender_Camera + 0xc);
  return;
}

/* ---- 0x0049f550  sputLua_SetActorScaleL ---- */
/* Lua opcode: SetActorScale Original name sputLua_SetActorScaleL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetActorScale'); was Lua_SetActorScale. */

void __cdecl sputLua_SetActorScaleL(void)

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
      pAVar4->flScale = 1.0f;
    }
  }
  return;
}

/* ---- 0x0049f5d0  sputLua_SetActorTimeScaleL ---- */
/* Lua opcode: SetActorTimeScale Original name sputLua_SetActorTimeScaleL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorTimeScale'); was Lua_SetActorTimeScale.
    */

void __cdecl sputLua_SetActorTimeScaleL(void)

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
        fVar5 = 1.0f;
      }
      else {
        fVar5 = lua_getnumber(iVar3);
      }
      actor->pExtra->flTimeScale = fVar5;
      pAVar1 = actor->pExtra;
      fVar5 = pAVar1->flTimeScale;
      if (pAVar1->flTimeScale < 0.0f) {
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

void __cdecl sputLua_GetActorNodeLocationL(void)

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
  float fVar6;
  #define local_3c (*(float (*)[3])(_frame + (0x50 - 0x3c)))
  #define local_30 (*(float (*)[12])(_frame + (0x50 - 0x30)))
  
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
           (actor->pCostumes->pMainModel != (rdThing *)0x0)) {
          if (actor->nScreenBoxValid == 0) {
            pfVar4 = sputActor_GetOrientMatrix(actor);
            rdPuppet_UpdateFrame(actor->pCostumes->pMainModel,pfVar4);
          }
          pfVar4 = local_30;
          fVar6 = lua_getnumber(iVar2);
          lVar5 = FTOL((float10)fVar6);
          index = (uint)lVar5;
          frame = sputActor_GetOrientMatrix(actor);
          rdPuppet_BuildJointMatrices(actor->pCostumes->pMainModel,frame,index,pfVar4);
          fVar6 = lua_getnumber(iVar2);
          lVar5 = FTOL((float10)fVar6);
          pfVar4 = actor->pCostumes->pMainModel->pModel->pHierarchyNodes[(int)lVar5].aPivot;
          local_3c[0] = *pfVar4;
          local_3c[1] = pfVar4[1];
          local_3c[2] = pfVar4[2];
          rdMatrix_TransformVector34Acc(local_3c,local_30);
          local_3c[0] = local_3c[0] + local_30[9];
          local_3c[1] = local_3c[1] + local_30[10];
          local_3c[2] = local_3c[2] + local_30[0xb];
          lua_pushnumber(local_3c[0]);
          lua_pushnumber(local_3c[1]);
          lua_pushnumber(local_3c[2]);
        }
      }
    }
  }
  return;
}
#undef local_30
#undef local_3c


/* ---- 0x0049f810  sputLua_GetActorScaleL ---- */
/* Lua opcode: GetActorScale Original name sputLua_GetActorScaleL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetActorScale'); was Lua_GetActorScale. */

void __cdecl sputLua_GetActorScaleL(void)

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

void __cdecl sputLua_GetActorTimeScaleL(void)

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
/* Lua opcode: SetCameraFOV Original name sputLua_SetCameraFOVL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetCameraFOV'); was Lua_SetCameraFOV. */

void __cdecl sputLua_SetCameraFOVL(void)

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

/* ---- 0x0049f930  sputLua_SetCameraRollL ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: SetCameraRoll Original name sputLua_SetCameraRollL (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetCameraRoll'); was Lua_SetCameraRoll. */

void __cdecl sputLua_SetCameraRollL(void)

{
  int iVar1;
  int iVar2;
  float fVar3;
  uint local_c;
  
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
  rdMatrix_LookAt(g_pSputRender_Camera + 0xc,g_pSputRender_Camera,g_pSputRender_Camera + 3,
                  PUN(uint,(float)g_pSputRender_Camera[6]));
  rdCamera_Update(g_pSputRender_Camera + 0xc);
  return;
}

/* ---- 0x0049f9b0  sputLua_GetCameraLookVectorL ---- */
/* Lua opcode: GetCameraLookVector Original name sputLua_GetCameraLookVectorL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetCameraLookVector'); was
   Lua_GetCameraLookVector. */

void __cdecl sputLua_GetCameraLookVectorL(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Setup *pSVar1;
  int iVar2;
  Set *pSVar3;
  int iVar4;
  longlong lVar5;
  float fVar6;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
  iVar2 = lua_lua2C(1);
  pSVar3 = sputRoom_GetCurrentRoom();
  if (pSVar3 == (Set *)0x0) {
    lua_pushnil();
    return;
  }
  iVar4 = lua_isnumber(iVar2);
  if (iVar4 == 0) {
    iVar2 = pSVar3->nCurSetup;
  }
  else {
    fVar6 = lua_getnumber(iVar2);
    lVar5 = FTOL((float10)fVar6);
    iVar2 = (int)lVar5;
  }
  pSVar1 = pSVar3->pSetups;
  local_c[0] = pSVar1[iVar2].aPos[0] - *(float *)&pSVar3->pSetups[iVar2].field_0x2c;
  local_c[1] = pSVar1[iVar2].aPos[1] - *(float *)&pSVar3->pSetups[iVar2].field_0x30;
  local_c[2] = pSVar1[iVar2].aPos[2] - *(float *)&pSVar3->pSetups[iVar2].field_0x34;
  rdVector_Normalize3Acc(local_c);
  iVar2 = lua_createtable();
  lua_pushobject(iVar2);
  lua_pushstring(s_x_004e8454);
  lua_pushnumber(local_c[0]);
  lua_settable();
  lua_pushobject(iVar2);
  lua_pushstring(s_y_004e8450);
  lua_pushnumber(local_c[1]);
  lua_settable();
  lua_pushobject(iVar2);
  lua_pushstring(s_z_004ec3b8);
  lua_pushnumber(local_c[2]);
  lua_settable();
  lua_pushobject(iVar2);
  return;
}
#undef local_c


/* ---- 0x0049fb00  sputLua_PointActorAtL ---- */
/* Lua opcode: PointActorAt(actor, x, y, z | actor). Creates the walker if missing, turns the walker
   heading all the way to the point (Walker_TurnToPoint with FLT_MAX) and negates the turn rate so
   sputActor_AlignToPuck snaps the visible yaw next frame. Only the yaw changes; pitch and roll are
   not touched. Original name sputLua_PointActorAtL (the remaster's GrimFandango (Linux): Lua /
   module table entry 'PointActorAt'); was Lua_PointActorAt. */

void __cdecl sputLua_PointActorAtL(void)

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
  uint local_14;
  uint local_10;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
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
  if (pAVar1->flTurnRate <= 0.0f) {
    return;
  }
  pAVar1->flTurnRate = pAVar1->flTurnRate * -1.0f;
  return;
}
#undef local_c


/* ---- 0x0049fc60  sputLua_TurnActorTo ---- */
/* Lua opcode: TurnActorTo(actor, x, y, z | actor). Creates the walker if missing, turns the heading
   by at most |rate| * frameSeconds (no time scale) and returns TRUE while a whole step was taken
   (angle left >= step), nil once done. With a turn rate of 0 the step is 0 and it returns TRUE
   forever. Original name sputLua_TurnActorTo (the remaster's GrimFandango (Linux): Lua / module
   table entry 'TurnActorTo'); was Lua_TurnActorTo. */

void __cdecl sputLua_TurnActorTo(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
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
  uint local_14;
  uint local_10;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
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
  if (actor->pExtra->flTurnRate < 0.0f) {
    fVar1 = -fVar1;
  }
  fVar8 = sputTime_GetFrameTimeFlex();
  fVar9 = Puck_PointAt(actor->pExtra->pPuck,local_c,fVar8 * fVar1);
  if (fVar9 < 0.0f) {
    fVar9 = -fVar9;
  }
  if (fVar8 * fVar1 <= fVar9) {
    lua_pushnumber(1.0f);
    return;
  }
LAB_0049fde2:
  lua_pushnil();
  return;
}
#undef local_c


/* ---- 0x0049fdf0  sputLua_PerSecondL ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: PerSecond Original name sputLua_PerSecondL (the remaster's GrimFandango (Linux): Lua
   / module table entry 'PerSecond'); was Lua_PerSecond. */

void __cdecl sputLua_PerSecondL(void)

{
  int iVar1;
  float fVar2;
  float fVar3;
  uint local_c;
  uint local_4;
  
  iVar1 = lua_lua2C(1);
  if (lua_isnumber_exref == (code *)0x0) {
    lua_pushnil();
  }
  fVar2 = sputTime_GetFrameTimeFlex();
  fVar3 = lua_getnumber(iVar1);
  lua_pushnumber(fVar3 * fVar2);
  return;
}

/* ---- 0x0049fe40  sputLua_SnapToPlane ---- */
/* Lua opcode: SnapToPlane Original name sputLua_SnapToPlane (the remaster's GrimFandango (Linux):
   Lua / module table entry 'SnapToPlane'); was Lua_SnapToPlane. */

void __cdecl sputLua_SnapToPlane(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *name;
  WalkPlane *this;
  uint local_10;
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
#undef local_c


/* ---- 0x0049ff00  sputLua_GetAngleBetweenVectorsL ---- */
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Lua opcode: GetAngleBetweenVectors Original name sputLua_GetAngleBetweenVectorsL (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetAngleBetweenVectors'); was
   Lua_GetAngleBetweenVectors. */

void __cdecl sputLua_GetAngleBetweenVectorsL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  uint local_30;
  uint local_1c;
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_istable(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_istable(iVar2);
    if (iVar3 != 0) {
      lua_pushobject(iVar1);
      lua_pushstring(s_x_004e8454);
      iVar3 = lua_gettable();
      local_c[0] = lua_getnumber(iVar3);
      lua_pushobject(iVar1);
      lua_pushstring(s_y_004e8450);
      iVar3 = lua_gettable();
      local_c[1] = lua_getnumber(iVar3);
      lua_pushobject(iVar1);
      lua_pushstring(s_z_004ec3b8);
      iVar1 = lua_gettable();
      local_c[2] = lua_getnumber(iVar1);
      lua_pushobject(iVar2);
      lua_pushstring(s_x_004e8454);
      iVar1 = lua_gettable();
      local_18[0] = lua_getnumber(iVar1);
      lua_pushobject(iVar2);
      lua_pushstring(s_y_004e8450);
      iVar1 = lua_gettable();
      local_18[1] = lua_getnumber(iVar1);
      lua_pushobject(iVar2);
      lua_pushstring(s_z_004ec3b8);
      iVar1 = lua_gettable();
      local_18[2] = lua_getnumber(iVar1);
      rdVector_Normalize3Acc(local_c);
      rdVector_Normalize3Acc(local_18);
      fVar4 = stdMath_ArcSin3(local_18[2] * local_c[2] +
                              local_18[1] * local_c[1] + local_18[0] * local_c[0]);
      lua_pushnumber(90.0f - fVar4);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_18
#undef local_c


/* ---- 0x004a00a0  sputLua_GetAngleBetweenActorsL ---- */
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Lua opcode GetAngleBetweenActors(a, b) (Grim). forward = walker heading axis (walker+0x18..0x20,
   not the eased visible yaw); delta = b.pos - a.pos normalized in 3D; returns 90 -
   asin(dot(forward, delta)) = unsigned angle between them, in degrees. (The z of delta in the
   decompile reads forward.z - a.z, probably a decompiler slot mix-up.) Original name
   sputLua_GetAngleBetweenActorsL (the remaster's GrimFandango (Linux): Lua / module table entry
   'GetAngleBetweenActors'); was Lua_GetAngleBetweenActors. */

void __cdecl sputLua_GetAngleBetweenActorsL(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Puck *pPVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *pAVar5;
  Actor *pAVar6;
  float fVar7;
  uint local_30;
  uint local_1c;
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
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
            local_c[0] = pPVar1->aFrame[3];
            local_c[1] = pPVar1->aFrame[4];
            local_c[2] = pPVar1->aFrame[5];
            local_18[0] = pAVar6->aPos[0] - pAVar5->aPos[0];
            local_18[1] = pAVar6->aPos[1] - pAVar5->aPos[1];
            local_18[2] = local_c[2] - pAVar5->aPos[2];
            rdVector_Normalize3Acc(local_c);
            rdVector_Normalize3Acc(local_18);
            fVar7 = stdMath_ArcSin3(local_18[2] * local_c[2] +
                                    local_18[1] * local_c[1] + local_18[0] * local_c[0]);
            lua_pushnumber(90.0f - fVar7);
            return;
          }
        }
      }
    }
  }
  lua_pushnil();
  return;
}
#undef local_18
#undef local_c


/* ---- 0x004a0230  sputLua_SetAmbientLight ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: SetAmbientLight Original name sputLua_SetAmbientLight (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetAmbientLight'); was Lua_SetAmbientLight. */

void __cdecl sputLua_SetAmbientLight(void)

{
  int iVar1;
  int iVar2;
  Set *pSVar3;
  float ambient;
  uint local_c;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    pSVar3 = sputRoom_GetCurrentRoom();
    if (pSVar3 != (Set *)0x0) {
      ambient = lua_getnumber(iVar1);
      ((int (*)(rdCamera *, float))rdCamera_SetAmbientLight)(*(rdCamera **)&pSVar3->pSetups[pSVar3->nCurSetup].field_0x48,ambient)
      ;
    }
  }
  return;
}

/* ---- 0x004a0290  sputLua_FindLight ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: FindLight Original name sputLua_FindLight (the remaster's GrimFandango (Linux): Lua /
   module table entry 'FindLight'); was Lua_FindLight. */

void __cdecl sputLua_FindLight(void)

{
  int iVar1;
  int iVar2;
  char *name;
  uint local_c;
  uint local_4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(iVar1);
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
    if (iVar1 != -1) {
      lua_pushnumber((float)iVar1);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a02f0  sputLua_TurnLightOn ---- */
/* Lua opcode: TurnLightOn Original name sputLua_TurnLightOn (the remaster's GrimFandango (Linux):
   Lua / module table entry 'TurnLightOn'); was Lua_TurnLightOn. */

void __cdecl sputLua_TurnLightOn(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *name;
  SetLight *pSVar4;
  longlong lVar5;
  float fVar6;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(iVar1);
  if (iVar3 == 0) {
    iVar3 = lua_isstring(iVar1);
    if (iVar3 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar1);
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar6 = lua_getnumber(iVar1);
    lVar5 = FTOL((float10)fVar6);
    iVar1 = (int)lVar5;
  }
  pSVar4 = sputRoom_GetLight((Set *)0x0,iVar1);
  if (pSVar4 != (SetLight *)0x0) {
    iVar1 = lua_isnil(iVar2);
    (pSVar4->light).nActive = (uint)(iVar1 == 0);
  }
  return;
}

/* ---- 0x004a0380  sputLua_IsLightOn ---- */
/* Lua opcode: IsLightOn Original name sputLua_IsLightOn (the remaster's GrimFandango (Linux): Lua /
   module table entry 'IsLightOn'); was Lua_IsLightOn. */

void __cdecl sputLua_IsLightOn(void)

{
  int iVar1;
  int iVar2;
  char *name;
  SetLight *pSVar3;
  longlong lVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_004a03f5;
    name = (char *)lua_getstring(iVar1);
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar5 = lua_getnumber(iVar1);
    lVar4 = FTOL((float10)fVar5);
    iVar1 = (int)lVar4;
  }
  pSVar3 = sputRoom_GetLight((Set *)0x0,iVar1);
  if ((pSVar3 != (SetLight *)0x0) && ((pSVar3->light).nActive != 0)) {
    lua_pushnumber(1.0f);
    return;
  }
LAB_004a03f5:
  lua_pushnil();
  return;
}

/* ---- 0x004a0400  sputLua_SetLightType ---- */
/* Lua opcode: SetLightType Original name sputLua_SetLightType (the remaster's GrimFandango (Linux):
   Lua / module table entry 'SetLightType'); was Lua_SetLightType. */

void __cdecl sputLua_SetLightType(void)

{
  int iVar1;
  int iVar2;
  Set *pSVar3;
  int iVar4;
  char *name;
  SetLight *pSVar5;
  uint *puVar6;
  uint *puVar7;
  uint uVar8;
  longlong lVar9;
  float fVar10;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  pSVar3 = sputRoom_GetCurrentRoom();
  iVar4 = lua_isnumber(iVar1);
  if (iVar4 == 0) {
    iVar4 = lua_isstring(iVar1);
    if (iVar4 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar1);
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar10 = lua_getnumber(iVar1);
    lVar9 = FTOL((float10)fVar10);
    iVar1 = (int)lVar9;
  }
  pSVar5 = sputRoom_GetLight((Set *)0x0,iVar1);
  if (pSVar5 != (SetLight *)0x0) {
    iVar4 = lua_isstring(iVar2);
    if (iVar4 != 0) {
      puVar6 = (uint *)lua_getstring(iVar2);
      puVar7 = String_ContainsSubstring(puVar6,s_parallel_004ec5a8);
      if ((puVar7 == (uint *)0x0) &&
         (puVar7 = String_ContainsSubstring(puVar6,s_global_004ec5a0), puVar7 == (uint *)0x0)) {
        puVar6 = String_ContainsSubstring(puVar6,s_spot_004ec598);
        if (puVar6 == (uint *)0x0) {
          (pSVar5->light).nType = 2;
        }
        else {
          (pSVar5->light).nType = 3;
        }
      }
      else {
        (pSVar5->light).nType = 1;
      }
      uVar8 = 0;
      if (pSVar3->nSetups != 0) {
        iVar2 = 0;
        do {
          uVar8 = uVar8 + 1;
          iVar4 = iVar2 + 0x28;
          iVar2 = iVar2 + 300;
          *(int *)(*(int *)(*(int *)((int)pSVar3->pSetups->aPos + iVar4) + iVar1 * 4 + 0x5c) + 4) =
               (pSVar5->light).nType;
        } while (uVar8 < (uint)pSVar3->nSetups);
      }
      return;
    }
    return;
  }
  return;
}

/* ---- 0x004a0530  sputLua_GetLightType ---- */
/* Lua opcode: GetLightType Original name sputLua_GetLightType (the remaster's GrimFandango (Linux):
   Lua / module table entry 'GetLightType'); was Lua_GetLightType. */

void __cdecl sputLua_GetLightType(void)

{
  int iVar1;
  int iVar2;
  char *name;
  SetLight *pSVar3;
  longlong lVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_004a05d0;
    name = (char *)lua_getstring(iVar1);
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar5 = lua_getnumber(iVar1);
    lVar4 = FTOL((float10)fVar5);
    iVar1 = (int)lVar4;
  }
  pSVar3 = sputRoom_GetLight((Set *)0x0,iVar1);
  if (pSVar3 != (SetLight *)0x0) {
    iVar1 = (pSVar3->light).nType;
    if (iVar1 == 1) {
      lua_pushstring(s_parallel_004ec5a8);
      return;
    }
    if (iVar1 == 3) {
      lua_pushstring(s_spot_004ec598);
      return;
    }
    if (iVar1 == 2) {
      lua_pushstring(s_omni_004ec5b4);
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

void __cdecl sputLua_SetLightPosition(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *name;
  Set *pSVar6;
  SetLight *pSVar7;
  uint uVar8;
  float *pfVar9;
  longlong lVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
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
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar11 = lua_getnumber(iVar1);
    lVar10 = FTOL((float10)fVar11);
    iVar1 = (int)lVar10;
  }
  pSVar6 = sputRoom_GetCurrentRoom();
  if ((((pSVar6 != (Set *)0x0) &&
       (pSVar7 = sputRoom_GetLight((Set *)0x0,iVar1), pSVar7 != (SetLight *)0x0)) &&
      (iVar5 = lua_isnumber(iVar2), iVar5 != 0)) &&
     ((iVar5 = lua_isnumber(iVar3), iVar5 != 0 && (iVar5 = lua_isnumber(iVar4), iVar5 != 0)))) {
    fVar11 = lua_getnumber(iVar2);
    fVar12 = lua_getnumber(iVar3);
    fVar13 = lua_getnumber(iVar4);
    pSVar7->aPos[0] = fVar11;
    pSVar7->aPos[1] = fVar12;
    pSVar7->aPos[2] = fVar13;
    uVar8 = 0;
    if (pSVar6->nSetups != 0) {
      iVar2 = 0;
      do {
        iVar3 = iVar2 + 0x28;
        iVar2 = iVar2 + 300;
        pfVar9 = (float *)(*(int *)((int)pSVar6->pSetups->aPos + iVar3) + (iVar1 + 0x1d) * 0xc);
        uVar8 = uVar8 + 1;
        *pfVar9 = fVar11;
        pfVar9[1] = fVar12;
        pfVar9[2] = fVar13;
      } while (uVar8 < (uint)pSVar6->nSetups);
    }
  }
  return;
}

/* ---- 0x004a0760  sputLua_GetLightPosition ---- */
/* Lua opcode: GetLightPosition Original name sputLua_GetLightPosition (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetLightPosition'); was Lua_GetLightPosition. */

void __cdecl sputLua_GetLightPosition(void)

{
  int iVar1;
  int iVar2;
  char *name;
  Set *pSVar3;
  SetLight *pSVar4;
  longlong lVar5;
  float fVar6;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_004a07f0;
    name = (char *)lua_getstring(iVar1);
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar6 = lua_getnumber(iVar1);
    lVar5 = FTOL((float10)fVar6);
    iVar1 = (int)lVar5;
  }
  pSVar3 = sputRoom_GetCurrentRoom();
  if (pSVar3 != (Set *)0x0) {
    pSVar4 = sputRoom_GetLight((Set *)0x0,iVar1);
    if (pSVar4 != (SetLight *)0x0) {
      lua_pushnumber(pSVar4->aPos[0]);
      lua_pushnumber(pSVar4->aPos[1]);
      lua_pushnumber(pSVar4->aPos[2]);
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

void __cdecl sputLua_SetLightRotation(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  Set *pSVar5;
  int iVar6;
  char *name;
  SetLight *pSVar7;
  uint uVar8;
  longlong lVar9;
  float fVar10;
  uint local_24;
  uint local_20;
  uint local_1c;
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  pSVar5 = sputRoom_GetCurrentRoom();
  iVar6 = lua_isnumber(iVar1);
  if (iVar6 == 0) {
    iVar6 = lua_isstring(iVar1);
    if (iVar6 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar1);
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar10 = lua_getnumber(iVar1);
    lVar9 = FTOL((float10)fVar10);
    iVar1 = (int)lVar9;
  }
  pSVar7 = sputRoom_GetLight((Set *)0x0,iVar1);
  if (pSVar7 != (SetLight *)0x0) {
    iVar6 = lua_isnumber(iVar2);
    if (iVar6 == 0) {
      local_c[0] = 0.0f;
    }
    else {
      local_c[0] = lua_getnumber(iVar2);
    }
    iVar2 = lua_isnumber(iVar3);
    if (iVar2 == 0) {
      local_c[1] = 0.0f;
    }
    else {
      local_c[1] = lua_getnumber(iVar3);
    }
    iVar2 = lua_isnumber(iVar4);
    if (iVar2 == 0) {
      local_c[2] = 0.0f;
    }
    else {
      local_c[2] = lua_getnumber(iVar4);
    }
    local_18[0] = 0.0f;
    local_18[1] = 1.0f;
    local_18[2] = 0.0f;
    rdVector_Rotate3Acc(local_18,local_c);
    (pSVar7->light).aDirection[0] = local_18[0];
    (pSVar7->light).aDirection[1] = local_18[1];
    uVar8 = 0;
    (pSVar7->light).aDirection[2] = local_18[2];
    if (pSVar5->nSetups != 0) {
      iVar2 = 0;
      do {
        iVar3 = iVar2 + 0x28;
        iVar2 = iVar2 + 300;
        iVar3 = *(int *)(*(int *)((int)pSVar5->pSetups->aPos + iVar3) + iVar1 * 4 + 0x5c);
        uVar8 = uVar8 + 1;
        *(float *)(iVar3 + 0xc) = local_18[0];
        *(float *)(iVar3 + 0x10) = local_18[1];
        *(float *)(iVar3 + 0x14) = local_18[2];
      } while (uVar8 < (uint)pSVar5->nSetups);
    }
  }
  return;
}
#undef local_18
#undef local_c


/* ---- 0x004a09a0  sputLua_GetLightRotation ---- */
/* Lua opcode: GetLightRotation Original name sputLua_GetLightRotation (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetLightRotation'); was Lua_GetLightRotation. */

void __cdecl sputLua_GetLightRotation(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *name;
  SetLight *pSVar3;
  longlong lVar4;
  float fVar5;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_004a0a3b;
    name = (char *)lua_getstring(iVar1);
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar5 = lua_getnumber(iVar1);
    lVar4 = FTOL((float10)fVar5);
    iVar1 = (int)lVar4;
  }
  pSVar3 = sputRoom_GetLight((Set *)0x0,iVar1);
  if (pSVar3 != (SetLight *)0x0) {
    rdVector_ExtractAngles((pSVar3->light).aDirection,local_c);
    lua_pushnumber(local_c[0]);
    lua_pushnumber(local_c[1]);
    lua_pushnumber(local_c[2]);
    return;
  }
LAB_004a0a3b:
  lua_pushnil();
  return;
}
#undef local_c


/* ---- 0x004a0a50  sputLua_SetLightAngles ---- */
/* Lua opcode: SetLightAngles Original name sputLua_SetLightAngles (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetLightAngles'); was Lua_SetLightAngles. */

void __cdecl sputLua_SetLightAngles(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *name;
  SetLight *pSVar5;
  longlong lVar6;
  float fVar7;
  float local_8;
  float local_4;
  
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
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar7 = lua_getnumber(iVar1);
    lVar6 = FTOL((float10)fVar7);
    iVar1 = (int)lVar6;
  }
  pSVar5 = sputRoom_GetLight((Set *)0x0,iVar1);
  if (pSVar5 != (SetLight *)0x0) {
    iVar1 = lua_isnumber(iVar2);
    if (iVar1 == 0) {
      local_4 = 0.0f;
    }
    else {
      local_4 = lua_getnumber(iVar2);
    }
    iVar1 = lua_isnumber(iVar3);
    if (iVar1 == 0) {
      local_8 = 0.0f;
    }
    else {
      local_8 = lua_getnumber(iVar3);
    }
    rdLight_SetAngles(&pSVar5->light,local_4,local_8);
  }
  return;
}

/* ---- 0x004a0b40  sputLua_GetLightAngles ---- */
/* Lua opcode: GetLightAngles Original name sputLua_GetLightAngles (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetLightAngles'); was Lua_GetLightAngles. */

void __cdecl sputLua_GetLightAngles(void)

{
  int iVar1;
  int iVar2;
  char *name;
  SetLight *pSVar3;
  longlong lVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_004a0bbc;
    name = (char *)lua_getstring(iVar1);
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar5 = lua_getnumber(iVar1);
    lVar4 = FTOL((float10)fVar5);
    iVar1 = (int)lVar4;
  }
  pSVar3 = sputRoom_GetLight((Set *)0x0,iVar1);
  if (pSVar3 != (SetLight *)0x0) {
    lua_pushnumber((pSVar3->light).flInnerAngle);
    lua_pushnumber((pSVar3->light).flOuterAngle);
    return;
  }
LAB_004a0bbc:
  lua_pushnil();
  return;
}

/* ---- 0x004a0bd0  sputLua_PointLightAt ---- */
/* Lua opcode: PointLightAt Original name sputLua_PointLightAt (the remaster's GrimFandango (Linux):
   Lua / module table entry 'PointLightAt'); was Lua_PointLightAt. */

void __cdecl sputLua_PointLightAt(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *name;
  SetLight *pSVar6;
  Actor *pAVar7;
  longlong lVar8;
  float fVar9;
  uint local_20;
  uint local_1c;
  float local_18;
  float local_14;
  float local_10;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
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
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar9 = lua_getnumber(iVar1);
    lVar8 = FTOL((float10)fVar9);
    iVar1 = (int)lVar8;
  }
  pSVar6 = sputRoom_GetLight((Set *)0x0,iVar1);
  if (pSVar6 != (SetLight *)0x0) {
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
        local_14 = 0.0f;
      }
      else {
        local_14 = lua_getnumber(iVar3);
      }
      iVar1 = lua_isnumber(iVar4);
      if (iVar1 == 0) {
        local_10 = 0.0f;
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
    local_c[0] = local_18 - pSVar6->aPos[0];
    local_c[1] = local_14 - pSVar6->aPos[1];
    local_c[2] = local_10 - pSVar6->aPos[2];
    rdVector_Normalize3Acc(local_c);
    (pSVar6->light).aDirection[0] = local_c[0];
    (pSVar6->light).aDirection[1] = local_c[1];
    (pSVar6->light).aDirection[2] = local_c[2];
    return;
  }
  return;
}
#undef local_c


/* ---- 0x004a0da0  sputLua_SetLightIntensity ---- */
/* Lua opcode: SetLightIntensity Original name sputLua_SetLightIntensity (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetLightIntensity'); was Lua_SetLightIntensity.
    */

void __cdecl sputLua_SetLightIntensity(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Set *pSVar4;
  int iVar5;
  char *name;
  SetLight *pSVar6;
  uint uVar7;
  longlong lVar8;
  float fVar9;
  uint local_4;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  pSVar4 = sputRoom_GetCurrentRoom();
  iVar5 = lua_isnumber(iVar2);
  if (iVar5 == 0) {
    iVar5 = lua_isstring(iVar2);
    if (iVar5 == 0) {
      return;
    }
    name = (char *)lua_getstring(iVar2);
    iVar2 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar9 = lua_getnumber(iVar2);
    lVar8 = FTOL((float10)fVar9);
    iVar2 = (int)lVar8;
  }
  pSVar6 = sputRoom_GetLight((Set *)0x0,iVar2);
  if ((pSVar6 != (SetLight *)0x0) && (iVar5 = lua_isnumber(iVar3), iVar5 != 0)) {
    fVar9 = lua_getnumber(iVar3);
    (pSVar6->light).flIntensity = fVar9;
    uVar7 = 0;
    if (pSVar4->nSetups != 0) {
      iVar5 = 0;
      do {
        fVar9 = lua_getnumber(iVar3);
        uVar7 = uVar7 + 1;
        iVar1 = iVar5 + 0x28;
        iVar5 = iVar5 + 300;
        *(float *)(*(int *)(*(int *)((int)pSVar4->pSetups->aPos + iVar1) + iVar2 * 4 + 0x5c) + 0x18)
             = fVar9;
      } while (uVar7 < (uint)pSVar4->nSetups);
    }
  }
  return;
}

/* ---- 0x004a0e90  sputLua_GetLightIntensity ---- */
/* Lua opcode: GetLightIntensity Original name sputLua_GetLightIntensity (the remaster's
   GrimFandango (Linux): Lua / module table entry 'GetLightIntensity'); was Lua_GetLightIntensity.
    */

void __cdecl sputLua_GetLightIntensity(void)

{
  int iVar1;
  int iVar2;
  char *name;
  SetLight *pSVar3;
  longlong lVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  lua_lua2C(2);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(iVar1);
    if (iVar2 == 0) goto LAB_004a0f08;
    name = (char *)lua_getstring(iVar1);
    iVar1 = sputRoom_FindLightByName((Set *)0x0,name);
  }
  else {
    fVar5 = lua_getnumber(iVar1);
    lVar4 = FTOL((float10)fVar5);
    iVar1 = (int)lVar4;
  }
  pSVar3 = sputRoom_GetLight((Set *)0x0,iVar1);
  if (pSVar3 != (SetLight *)0x0) {
    lua_pushnumber((pSVar3->light).flIntensity);
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

void __fastcall sputLua_ImGetMasterVol(undefined4 unused)

{
  int iVar1;
  uint local_8;
  uint local_4;
  
  iVar1 = ImSetGroupVol(0,0xffffffff);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x004a1400  sputLua_ImSetMasterVol ---- */
/* Lua opcode: ImSetMasterVol Original name sputLua_ImSetMasterVol (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImSetMasterVol'); was Lua_ImSetMasterVol. */

void __cdecl sputLua_ImSetMasterVol(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    ImSetGroupVol(0,(uint)lVar3);
  }
  return;
}

/* ---- 0x004a1440  sputLua_ImGetSfxVol ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ImGetSfxVol Original name sputLua_ImGetSfxVol (the remaster's GrimFandango (Linux):
   Lua / module table entry 'ImGetSfxVol'); was Lua_ImGetSfxVol. */

void __fastcall sputLua_ImGetSfxVol(undefined4 unused)

{
  int iVar1;
  uint local_8;
  uint local_4;
  
  iVar1 = ImSetGroupVol(1,0xffffffff);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x004a1470  sputLua_ImSetSfxVol ---- */
/* Lua opcode: ImSetSfxVol Original name sputLua_ImSetSfxVol (the remaster's GrimFandango (Linux):
   Lua / module table entry 'ImSetSfxVol'); was Lua_ImSetSfxVol. */

void __cdecl sputLua_ImSetSfxVol(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    ImSetGroupVol(1,(uint)lVar3);
  }
  return;
}

/* ---- 0x004a14b0  sputLua_ImGetVoiceVol ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ImGetVoiceVol Original name sputLua_ImGetVoiceVol (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImGetVoiceVol'); was Lua_ImGetVoiceVol. */

void __fastcall sputLua_ImGetVoiceVol(undefined4 unused)

{
  int iVar1;
  uint local_8;
  uint local_4;
  
  iVar1 = ImSetGroupVol(2,0xffffffff);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x004a14e0  sputLua_ImSetVoiceVol ---- */
/* Lua opcode: ImSetVoiceVol Original name sputLua_ImSetVoiceVol (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImSetVoiceVol'); was Lua_ImSetVoiceVol. */

void __cdecl sputLua_ImSetVoiceVol(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    ImSetGroupVol(2,(uint)lVar3);
  }
  return;
}

/* ---- 0x004a1520  sputLua_ImGetMusicVol ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ImGetMusicVol Original name sputLua_ImGetMusicVol (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImGetMusicVol'); was Lua_ImGetMusicVol. */

void __fastcall sputLua_ImGetMusicVol(undefined4 unused)

{
  int iVar1;
  uint local_8;
  uint local_4;
  
  iVar1 = ImSetGroupVol(3,0xffffffff);
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x004a1550  sputLua_ImSetMusicVol ---- */
/* Lua opcode: ImSetMusicVol Original name sputLua_ImSetMusicVol (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImSetMusicVol'); was Lua_ImSetMusicVol. */

void __cdecl sputLua_ImSetMusicVol(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    ImSetGroupVol(3,(uint)lVar3);
  }
  return;
}

/* ---- 0x004a1640  sputLua_ImSetState ---- */
/* Lua opcode: ImSetState Original name sputLua_ImSetState (the remaster's GrimFandango (Linux): Lua
   / module table entry 'ImSetState'); was Lua_ImSetState. */

void __cdecl sputLua_ImSetState(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    gimlib_SetImuseState((int)lVar3);
  }
  return;
}

/* ---- 0x004a16d0  sputLua_ImSetCuePoint ---- */
/* Lua opcode: ImSetCuePoint Original name sputLua_ImSetCuePoint (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ImSetCuePoint'); was Lua_ImSetCuePoint. */

void __cdecl sputLua_ImSetCuePoint(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    ImSetCuePoint((int)lVar3);
  }
  return;
}

/* ---- 0x004a17f0  sputLua_ImGetMemoryFootprint ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: ImGetMemoryFootprint Original name sputLua_ImGetMemoryFootprint (the remaster's
   GrimFandango (Linux): Lua / module table entry 'ImGetMemoryFootprint'); was
   Lua_ImGetMemoryFootprint. */

void __cdecl sputLua_ImGetMemoryFootprint(void)

{
  uint uVar1;
  uint local_c;
  
  uVar1 = iMUSE_GetMemoryFootprint();
  lua_pushnumber((float)uVar1);
  return;
}

/* ---- 0x004a1820  sputLua_ImGetSoundCacheSize ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: ImGetSoundCacheSize Original name sputLua_ImGetSoundCacheSize (the remaster's
   GrimFandango (Linux): Lua / module table entry 'ImGetSoundCacheSize'); was
   Lua_ImGetSoundCacheSize. */

void __cdecl sputLua_ImGetSoundCacheSize(void)

{
  uint uVar1;
  uint local_c;
  
  uVar1 = iMUSE_GetSoundCacheSize();
  lua_pushnumber((float)uVar1);
  return;
}

/* ---- 0x004a1850  sputLua_SetGamma ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: SetGamma Original name sputLua_SetGamma (the remaster's GrimFandango (Linux): Lua /
   module table entry 'SetGamma'); was Lua_SetGamma. */

void __cdecl sputLua_SetGamma(void)

{
  int iVar1;
  int iVar2;
  float gamma;
  uint local_8;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if ((iVar2 != 0) && (g_dwGrimlib_mode != 4)) {
    gamma = lua_getnumber(iVar1);
    sputRender_SetGamma(gamma);
  }
  return;
}

/* ---- 0x004a1890  sputLua_SetActorWalkDominate ---- */
/* Lua opcode: SetActorWalkDominate Original name sputLua_SetActorWalkDominate (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorWalkDominate'); was
   Lua_SetActorWalkDominate. */

void __cdecl sputLua_SetActorWalkDominate(void)

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

void __cdecl sputLua_SetActorConstrain(void)

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

void __cdecl sputLua_RenderModeUser(void)

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

void __cdecl sputLua_DimScreen(void)

{
  sputRender_Dim((ushort *)0x0,2);
  return;
}

/* ---- 0x004a1a00  sputLua_DimRegion ---- */
/* WARNING: Variable defined which should be unmapped: local_28 */
/* WARNING: Variable defined which should be unmapped: local_38 */
/* WARNING: Variable defined which should be unmapped: local_34 */
/* WARNING: Variable defined which should be unmapped: local_30 */
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: DimRegion Original name sputLua_DimRegion (the remaster's GrimFandango (Linux): Lua /
   module table entry 'DimRegion'); was Lua_DimRegion. */

void __cdecl sputLua_DimRegion(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  longlong lVar9;
  float fVar10;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_14;
  uint local_4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  fVar10 = lua_getnumber(iVar1);
  lVar6 = FTOL((float10)fVar10);
  fVar10 = lua_getnumber(iVar2);
  lVar7 = FTOL((float10)fVar10);
  fVar10 = lua_getnumber(iVar3);
  lVar8 = FTOL((float10)fVar10);
  fVar10 = lua_getnumber(iVar4);
  lVar9 = FTOL((float10)fVar10);
  fVar10 = lua_getnumber(iVar5);
  sputRender_DimRegion((int)lVar6,(int)lVar7,(int)lVar8,(int)lVar9,fVar10);
  return;
}

/* ---- 0x004a1ae0  sputLua_SetSpeechMode ---- */
/* Lua opcode: SetSpeechMode Original name sputLua_SetSpeechMode (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetSpeechMode'); was Lua_SetSpeechMode. */

void __cdecl sputLua_SetSpeechMode(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
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

void __cdecl sputLua_GetSpeechMode(void)

{
  uint uVar1;
  
  uVar1 = sputActor_GetSpeechMode();
  if ((uVar1 & 2) == 0) {
    if ((uVar1 & 1) != 0) {
      lua_pushnumber(1.0f);
      return;
    }
  }
  else if ((uVar1 & 1) != 0) {
    lua_pushnumber(3.0f);
    return;
  }
  lua_pushnumber(2.0f);
  return;
}

/* ---- 0x004a1b80  sputLua_ActorShadow ---- */
/* Lua opcode: ActorShadow Original name sputLua_ActorShadow (the remaster's GrimFandango (Linux):
   Lua / module table entry 'ActorShadow'); was Lua_ActorShadow. */

void __cdecl sputLua_ActorShadow(void)

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
        lua_pushnumber(1.0f);
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

void __cdecl sputLua_ActivateActorShadow(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *actor;
  longlong lVar5;
  float fVar6;
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
      fVar6 = lua_getnumber(iVar2);
      lVar5 = FTOL((float10)fVar6);
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

void __cdecl sputLua_SetActorShadowPlane(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  char *planeName;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      iVar1 = lua_getuserdata(iVar1);
      actor = sputActor_ActorDeref(iVar1);
      planeName = (char *)lua_getstring(iVar2);
      sputActor_SetShadowPlane(actor,planeName);
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

void __cdecl sputLua_SetActorShadowPoint(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  Actor *actor;
  float z;
  float y;
  float x;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_4;
  
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

/* ---- 0x004a1dc0  sputLua_SetActiveShadow ---- */
/* Lua opcode: SetActiveShadow Original name sputLua_SetActiveShadow (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetActiveShadow'); was Lua_SetActiveShadow. */

void __cdecl sputLua_SetActiveShadow(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  longlong lVar4;
  float fVar5;
  
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
      fVar5 = lua_getnumber(iVar2);
      lVar4 = FTOL((float10)fVar5);
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

void __cdecl sputLua_ActorDistToShadowPlane(void)

{
  ActorExtra *pAVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  Actor *actor;
  longlong lVar5;
  float fVar6;
  uint local_4;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_lua2C(2);
  fVar6 = lua_getnumber(iVar3);
  lVar5 = FTOL((float10)fVar6);
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
      fVar6 = actor->aPos[1] * pAVar1->aShadows[iVar3].aPlane[1] +
              pAVar1->aShadows[iVar3].aPlane[2] * actor->aPos[2] +
              pAVar1->aShadows[iVar3].aPlane[0] * actor->aPos[0] + pAVar1->aShadows[iVar3].aPlane[3]
      ;
      if (fVar6 < 0.0f) {
        fVar6 = -fVar6;
      }
      lua_pushnumber(fVar6);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a1f30  sputLua_AddShadowClipPlane ---- */
/* Lua opcode: AddShadowPlane Original name sputLua_AddShadowClipPlane (the remaster's GrimFandango
   (Linux): Lua / module table entry 'AddShadowPlane'); was Lua_AddShadowPlane. */

void __cdecl sputLua_AddShadowClipPlane(void)

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

void __cdecl sputLua_SetActorShadowValid(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  longlong lVar4;
  float fVar5;
  
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
      fVar5 = lua_getnumber(iVar2);
      lVar4 = FTOL((float10)fVar5);
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

void __cdecl sputLua_KillActorShadows(void)

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

void __cdecl sputLua_SetShadowColor(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  fVar5 = lua_getnumber(iVar3);
  lVar4 = FTOL((float10)fVar5);
  iVar3 = (int)lVar4;
  fVar5 = lua_getnumber(iVar2);
  lVar4 = FTOL((float10)fVar5);
  iVar2 = (int)lVar4;
  fVar5 = lua_getnumber(iVar1);
  lVar4 = FTOL((float10)fVar5);
  sputCostume_SetShadowColor((int)lVar4,iVar2,iVar3);
  return;
}

/* ---- 0x004a2130  sputLua_NewObjectState ---- */
/* Lua opcode: NewObjectState Original name sputLua_NewObjectState (the remaster's GrimFandango
   (Linux): Lua / module table entry 'NewObjectState'); was Lua_NewObjectState. */

void __cdecl sputLua_NewObjectState(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *zbitmap;
  char *bitmap;
  ObjectState *pOVar7;
  int visible;
  longlong lVar8;
  float fVar9;
  uint local_8;
  uint local_4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  iVar4 = lua_lua2C(4);
  iVar5 = lua_lua2C(5);
  visible = -1;
  iVar6 = lua_isnil(iVar5);
  if (iVar6 == 0) {
    fVar9 = lua_getnumber(iVar5);
    lVar8 = FTOL((float10)fVar9);
    visible = (int)lVar8;
  }
  zbitmap = (char *)lua_getstring(iVar4);
  bitmap = (char *)lua_getstring(iVar3);
  fVar9 = lua_getnumber(iVar2);
  lVar8 = FTOL((float10)fVar9);
  iVar2 = (int)lVar8;
  fVar9 = lua_getnumber(iVar1);
  lVar8 = FTOL((float10)fVar9);
  pOVar7 = sputRoom_AddObjectState((int)lVar8,iVar2,bitmap,zbitmap,visible);
  lua_pushusertag((char *)pOVar7,0x54415453);
  return;
}

/* ---- 0x004a21f0  sputLua_FreeObjectState ---- */
/* Lua opcode: FreeObjectState Original name sputLua_FreeObjectState (the remaster's GrimFandango
   (Linux): Lua / module table entry 'FreeObjectState'); was Lua_FreeObjectState. */

void __cdecl sputLua_FreeObjectState(void)

{
  int iVar1;
  int iVar2;
  ObjectState *state;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x54415453) {
      state = (ObjectState *)lua_getuserdata(iVar1);
      if (state != (ObjectState *)0x0) {
        sputRoom_RemoveObjectState(state);
      }
    }
  }
  return;
}

/* ---- 0x004a2240  sputLua_SendObjectToBack ---- */
/* Lua opcode: SendObjectToBack Original name sputLua_SendObjectToBack (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SendObjectToBack'); was Lua_SendObjectToBack. */

void __cdecl sputLua_SendObjectToBack(void)

{
  Setup *pSVar1;
  int iVar2;
  int iVar3;
  ObjectState *pOVar4;
  Set *pSVar5;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_isuserdata(iVar2);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar2);
    if (iVar3 == 0x54415453) {
      pOVar4 = (ObjectState *)lua_getuserdata(iVar2);
      if (pOVar4 != (ObjectState *)0x0) {
        iVar2 = pOVar4->nState;
        pSVar5 = sputRoom_GetCurrentRoom();
        pSVar1 = pSVar5->pSetups;
        pOVar4 = ObjectState_MoveToBack(pOVar4,pSVar1[iVar2].pObjectStates);
        pSVar1[iVar2].pObjectStates = pOVar4;
      }
    }
  }
  return;
}

/* ---- 0x004a22b0  sputLua_SendObjectToFront ---- */
/* Lua opcode: SendObjectToFront Original name sputLua_SendObjectToFront (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SendObjectToFront'); was Lua_SendObjectToFront.
    */

void __cdecl sputLua_SendObjectToFront(void)

{
  Setup *pSVar1;
  int iVar2;
  int iVar3;
  ObjectState *pOVar4;
  Set *pSVar5;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_isuserdata(iVar2);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar2);
    if (iVar3 == 0x54415453) {
      pOVar4 = (ObjectState *)lua_getuserdata(iVar2);
      if (pOVar4 != (ObjectState *)0x0) {
        iVar2 = pOVar4->nState;
        pSVar5 = sputRoom_GetCurrentRoom();
        pSVar1 = pSVar5->pSetups;
        pOVar4 = ObjectState_MoveToFront(pOVar4,pSVar1[iVar2].pObjectStates);
        pSVar1[iVar2].pObjectStates = pOVar4;
      }
    }
  }
  return;
}

/* ---- 0x004a2320  sputLua_SetObjectType ---- */
/* Lua opcode: SetObjectType Original name sputLua_SetObjectType (the remaster's GrimFandango
   (Linux): Lua / module table entry 'SetObjectType'); was Lua_SetObjectType. */

void __cdecl sputLua_SetObjectType(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x54415453) {
      iVar1 = lua_getuserdata(iVar1);
      if (iVar1 != 0) {
        fVar5 = lua_getnumber(iVar2);
        lVar4 = FTOL((float10)fVar5);
        *(int *)(iVar1 + 4) = (int)lVar4;
      }
    }
  }
  return;
}

/* ---- 0x004a2380  sputLua_ActorToClean ---- */
/* Lua opcode: ActorToClean Original name sputLua_ActorToClean (the remaster's GrimFandango (Linux):
   Lua / module table entry 'ActorToClean'); was Lua_ActorToClean. */

void __cdecl sputLua_ActorToClean(void)

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

void __cdecl sputLua_SetActorCollisionMode(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  longlong lVar4;
  float fVar5;
  
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
      fVar5 = lua_getnumber(iVar2);
      lVar4 = FTOL((float10)fVar5);
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

void __cdecl sputLua_SetActorCollisionScale(void)

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

void __cdecl sputLua_SetActorOffsetYaw(void)

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

void __cdecl sputLua_CacheRect(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  Actor *pAVar6;
  char *pcVar7;
  longlong lVar8;
  float fVar9;
  uint local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_4;
  
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
  fVar9 = lua_getnumber(iVar1);
  lVar8 = FTOL((float10)fVar9);
  local_24 = (uint)lVar8;
  fVar9 = lua_getnumber(iVar2);
  lVar8 = FTOL((float10)fVar9);
  local_20 = (uint)lVar8;
  fVar9 = lua_getnumber(iVar3);
  lVar8 = FTOL((float10)fVar9);
  local_1c = (uint)lVar8;
  fVar9 = lua_getnumber(iVar4);
  lVar8 = FTOL((float10)fVar9);
  local_18 = (uint)lVar8;
LAB_004a268a:
  pcVar7 = sputRender_CreateCacheRect(local_24,local_20,local_1c,local_18);
  lua_pushusertag(pcVar7,0x504f494e);
  return;
}

/* ---- 0x004a26b0  sputLua_RestoreCacheRect ---- */
/* Lua opcode: RestoreCacheRect Original name sputLua_RestoreCacheRect (the remaster's GrimFandango
   (Linux): Lua / module table entry 'RestoreCacheRect'); was Lua_RestoreCacheRect. */

void __cdecl sputLua_RestoreCacheRect(void)

{
  int iVar1;
  int *piVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  piVar2 = (int *)lua_getuserdata(iVar1);
  if ((piVar2 != (int *)0x0) && (*piVar2 == 0x11111111)) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    sputRender_RestoreCacheRect((int)lVar3);
  }
  return;
}

/* ---- 0x004a26f0  sputLua_ResReport ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: ResReport Original name sputLua_ResReport (the remaster's GrimFandango (Linux): Lua /
   module table entry 'ResReport'); was Lua_ResReport. */

void __fastcall sputLua_ResReport(undefined4 unused)

{
  int iVar1;
  uint local_8;
  uint local_4;
  
  sputResource_ReportAllocations();
  iVar1 = daTotalAllocated();
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x004a2720  sputLua_HardwareAccelerated ---- */
/* Lua opcode: HardwareAccelerated Original name sputLua_HardwareAccelerated (the remaster's
   GrimFandango (Linux): Lua / module table entry 'HardwareAccelerated'); was
   Lua_HardwareAccelerated. */

void __cdecl sputLua_HardwareAccelerated(void)

{
  if (g_nSputRender_b3DAcceleration != 0) {
    lua_pushnumber(1.0f);
    return;
  }
  lua_pushnumber(0.0f);
  return;
}

/* ---- 0x004a2750  sputLua_SetActorClipActive ---- */
/* Lua opcode: SetActorClipActive Original name sputLua_SetActorClipActive (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorClipActive'); was Lua_SetActorClipActive.
    */

void __cdecl sputLua_SetActorClipActive(void)

{
  int iVar1;
  int iVar2;
  Actor *actor;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar1 = lua_getuserdata(iVar1);
  actor = sputActor_ActorDeref(iVar1);
  if (actor != (Actor *)0x0) {
    fVar4 = lua_getnumber(iVar2);
    lVar3 = FTOL((float10)fVar4);
    sputActor_SetClipPlaneActive(actor,(int)lVar3);
  }
  return;
}

/* ---- 0x004a27b0  sputLua_SetActorClipPlane ---- */
/* Lua opcode: SetActorClipPlane Original name sputLua_SetActorClipPlane (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorClipPlane'); was Lua_SetActorClipPlane.
    */

void __cdecl sputLua_SetActorClipPlane(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  Actor *actor;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
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
                local_18[0] = lua_getnumber(iVar2);
                local_18[1] = lua_getnumber(iVar3);
                local_18[2] = lua_getnumber(iVar4);
                rdVector_Normalize3Acc(local_18);
                local_c = lua_getnumber(iVar5);
                local_8 = lua_getnumber(iVar6);
                local_4 = lua_getnumber(iVar7);
                sputActor_SetClipPlane(actor,local_18,&local_c);
              }
            }
          }
        }
      }
    }
  }
  return;
}
#undef local_18
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a2920  sputLua_MarkDirtyRect ---- */
/* Lua opcode: MarkDirtyRect Original name sputLua_MarkDirtyRect (the remaster's GrimFandango
   (Linux): Lua / module table entry 'MarkDirtyRect'); was Lua_MarkDirtyRect. */

void __cdecl sputLua_MarkDirtyRect(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  Actor *pAVar6;
  longlong lVar7;
  float fVar8;
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
  fVar8 = lua_getnumber(iVar1);
  lVar7 = FTOL((float10)fVar8);
  local_10 = (uint)lVar7;
  fVar8 = lua_getnumber(iVar2);
  lVar7 = FTOL((float10)fVar8);
  local_c = (uint)lVar7;
  fVar8 = lua_getnumber(iVar3);
  lVar7 = FTOL((float10)fVar8);
  local_8 = (uint)lVar7;
  fVar8 = lua_getnumber(iVar4);
  lVar7 = FTOL((float10)fVar8);
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

void __cdecl sputLua_FadeOutChore(void)

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
  float fVar8;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  luaObj = (void *)lua_lua2C(2);
  iVar2 = lua_lua2C(3);
  iVar3 = lua_lua2C(4);
  iVar4 = lua_isuserdata(iVar1);
  if ((iVar4 != 0) && (iVar4 = lua_tag(iVar1), iVar4 == 0x52544341)) {
    iVar1 = lua_getuserdata(iVar1);
    pAVar5 = sputActor_ActorDeref(iVar1);
    fVar8 = lua_getnumber(iVar2);
    lVar6 = FTOL((float10)fVar8);
    fVar8 = lua_getnumber(iVar3);
    lVar7 = FTOL((float10)fVar8);
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

void __cdecl sputLua_IrisDown(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  fVar5 = lua_getnumber(iVar3);
  lVar4 = FTOL((float10)fVar5);
  iVar3 = (int)lVar4;
  fVar5 = lua_getnumber(iVar2);
  lVar4 = FTOL((float10)fVar5);
  iVar2 = (int)lVar4;
  fVar5 = lua_getnumber(iVar1);
  lVar4 = FTOL((float10)fVar5);
  sputRender_IrisDown((int)lVar4,iVar2,iVar3);
  return;
}

/* ---- 0x004a2c70  sputLua_IrisUp ---- */
/* Lua opcode: IrisUp Original name sputLua_IrisUp (the remaster's GrimFandango (Linux): Lua /
   module table entry 'IrisUp'); was Lua_IrisUp. */

void __cdecl sputLua_IrisUp(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_lua2C(3);
  fVar5 = lua_getnumber(iVar3);
  lVar4 = FTOL((float10)fVar5);
  iVar3 = (int)lVar4;
  fVar5 = lua_getnumber(iVar2);
  lVar4 = FTOL((float10)fVar5);
  iVar2 = (int)lVar4;
  fVar5 = lua_getnumber(iVar1);
  lVar4 = FTOL((float10)fVar5);
  sputRender_IrisUp((int)lVar4,iVar2,iVar3);
  return;
}

/* ---- 0x004a2cd0  sputLua_IrisComplete ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: IrisComplete Original name sputLua_IrisComplete (the remaster's GrimFandango (Linux):
   Lua / module table entry 'IrisComplete'); was Lua_IrisComplete. */

void __fastcall sputLua_IrisComplete(undefined4 unused)

{
  uint uVar1;
  uint local_8;
  uint local_4;
  
  uVar1 = sputRender_IrisComplete();
  lua_pushnumber((float)(uVar1 != 0));
  return;
}

/* ---- 0x004a2d00  Lua_TextFileGetLineCount ---- */
/* WARNING: Variable defined which should be unmapped: local_21c */
/* Lua opcode: TextFileGetLineCount */

void __cdecl Lua_TextFileGetLineCount(void)

{
  unsigned char _frame[0x210] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint local_21c;
  uint local_208;
  uint local_204;
  #define local_200 (*(char (*)[512])(_frame + (0x210 - 0x200)))
  
  iVar2 = lua_lua2C(1);
  local_208 = 0;
  iVar3 = lua_isnil(iVar2);
  if (iVar3 != 0) {
    lua_pushnil();
    return;
  }
  uVar4 = lua_getstring(iVar2);
  puVar5 = (undefined4 *)fopen(uVar4,((unsigned)(uintptr_t)&s_rt_004ec5bc));
  if (puVar5 != (undefined4 *)0x0) {
    iVar2 = lua_createtable();
    bVar1 = *(byte *)(puVar5 + 3);
    while ((bVar1 & 0x10) == 0) {
      lua_pushobject(iVar2);
      lua_pushnumber((float)(int)local_208);
      uVar4 = ftell((uint)puVar5);
      lua_pushnumber((float)(int)uVar4);
      lua_settable();
      fgets(local_200,0x200,puVar5);
      local_208 = local_208 + 1;
      bVar1 = *(byte *)(puVar5 + 3);
    }
    fclose((int)puVar5);
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


/* ---- 0x004a2e20  Lua_TextFileGetLine ---- */
/* Lua opcode: TextFileGetLine */

void __cdecl Lua_TextFileGetLine(void)

{
  unsigned char _frame[0x210] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  longlong lVar6;
  float fVar7;
  char *pcVar8;
  #define local_200 (*(char (*)[512])(_frame + (0x210 - 0x200)))
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnil(iVar1);
  if (iVar3 == 0) {
    iVar3 = lua_isnil(iVar2);
    if (iVar3 == 0) {
      pcVar8 = s_rt_004ec5bc;
      uVar4 = lua_getstring(iVar1);
      puVar5 = (undefined4 *)fopen(uVar4,(uint)pcVar8);
      if (puVar5 != (undefined4 *)0x0) {
        fVar7 = lua_getnumber(iVar2);
        lVar6 = FTOL((float10)fVar7);
        fseek((uint)puVar5,(uint)lVar6,0);
        local_200[0] = '\0';
        fgets(local_200,0x200,puVar5);
        fclose((int)puVar5);
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

void __cdecl sputLua_ScreenShot(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  longlong lVar5;
  float fVar6;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isnil(iVar1);
  if (iVar3 == 0) {
    iVar3 = lua_isnumber(iVar1);
    if (iVar3 == 0) goto LAB_004a2f2f;
    fVar6 = lua_getnumber(iVar1);
    lVar5 = FTOL((float10)fVar6);
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
      fVar6 = lua_getnumber(iVar2);
      lVar5 = FTOL((float10)fVar6);
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

void __cdecl sputLua_SaveScreen(void)

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

void __cdecl sputLua_GetSaveGameImage(void)

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

void __cdecl sputLua_GetImage(void)

{
  VBuffer *pVVar1;
  int iVar2;
  int iVar3;
  char *filename;
  stdBitmap *bitmap;
  int b;
  
  iVar2 = lua_lua2C(1);
  iVar3 = lua_isstring(iVar2);
  if (iVar3 != 0) {
    b = 0;
    iVar3 = 0;
    filename = (char *)lua_getstring(iVar2);
    bitmap = stdLoadImage(filename,iVar3,b);
    if (bitmap != (stdBitmap *)0x0) {
      pVVar1 = *bitmap->ppFrames;
      pVVar1->dwColorKey = 0xf81f;
      *bitmap->ppFrames = (VBuffer *)0x0;
      stdBitmap_Free(bitmap);
      sputRender_ColorCorrect(pVVar1->pPixels,(pVVar1->format).nHeight * (pVVar1->format).nWidth);
      sputRender_ColorCorrect((ushort *)&pVVar1->dwColorKey,1);
      lua_pushusertag((char *)pVVar1,0x46554256);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a30e0  sputLua_FreeImage ---- */
/* Lua opcode: FreeImage Original name sputLua_FreeImage (the remaster's GrimFandango (Linux): Lua /
   module table entry 'FreeImage'); was Lua_FreeImage. */

void __cdecl sputLua_FreeImage(void)

{
  int iVar1;
  int iVar2;
  VBuffer *surface;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if (iVar2 == 0x46554256) {
      surface = (VBuffer *)lua_getuserdata(iVar1);
      stdDisplay_VBufferFree(surface);
    }
  }
  return;
}

/* ---- 0x004a3130  sputLua_BlastImage ---- */
/* Lua opcode: BlastImage Original name sputLua_BlastImage (the remaster's GrimFandango (Linux): Lua
   / module table entry 'BlastImage'); was Lua_BlastImage. */

void __cdecl sputLua_BlastImage(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  VBuffer *src;
  VBuffer *dst;
  longlong lVar5;
  float fVar6;
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
          src = (VBuffer *)lua_getuserdata(iVar1);
          srcRect = (int *)0x0;
          fVar6 = lua_getnumber(iVar3);
          lVar5 = FTOL((float10)fVar6);
          iVar1 = (int)lVar5;
          fVar6 = lua_getnumber(iVar2);
          lVar5 = FTOL((float10)fVar6);
          iVar2 = (int)lVar5;
          dst = (VBuffer *)Render_GetBackBuffer();
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

void __cdecl sputLua_BlastRect(void)

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
  float fVar11;
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
    fVar11 = lua_getnumber(iVar1);
    lVar10 = FTOL((float10)fVar11);
    local_4 = (uint)lVar10;
    fVar11 = lua_getnumber(iVar2);
    lVar10 = FTOL((float10)fVar11);
    iVar1 = (int)lVar10;
    fVar11 = lua_getnumber(local_10);
    lVar10 = FTOL((float10)fVar11);
    iVar2 = (int)lVar10;
    fVar11 = lua_getnumber(local_c);
    lVar10 = FTOL((float10)fVar11);
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
      local_4 = (uint)Render_GetBackBuffer();
      uVar9 = iVar2 - uVar6;
      local_c = (iVar4 - iVar1) + 1;
      stdDisplay_VBufferLock((VBuffer *)local_4);
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
      stdDisplay_VBufferUnlock((VBuffer *)local_4);
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
  bool bVar1;
  bool bVar2;
  int iVar3;
  void *pvVar4;
  void *pvVar5;
  uint local_4;
  
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

/* ---- 0x004a3720  sputLua_GetSaveGameData ---- */
/* Lua opcode: GetSaveGameData Original name sputLua_GetSaveGameData (the remaster's GrimFandango
   (Linux): Lua / module table entry 'GetSaveGameData'); was Lua_GetSaveGameData. */

void __cdecl sputLua_GetSaveGameData(void)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char *name;
  int *file;
  char *mode;
  uint local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  #define local_80 (*(char (*)[128])(_frame + (0x90 - 0x80)))
  
  local_90 = 0;
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(iVar1);
  if (iVar2 != 0) {
    mode = s_rb_004ddb18;
    name = (char *)lua_getstring(iVar1);
    file = SaveFile_Open(name,mode);
    if (file != (int *)0x0) {
      iVar1 = lua_createtable();
      gzread(file,(int)&local_8c,4);
      for (; 0 < (int)local_8c; local_8c = local_8c + (-4 - local_88)) {
        gzread(file,(int)&local_88,4);
        gzread(file,(int)local_80,local_88);
        lua_pushobject(iVar1);
        local_84 = PUN(uint,(float)(float)(int)local_90);
        local_90 = local_90 + 1;
        lua_pushnumber(PUN(float,local_84));
        lua_pushstring(local_80);
        lua_settable();
      }
      lua_pushobject(iVar1);
      gzclose((int)file);
    }
  }
  return;
}
#undef local_80


/* ---- 0x004a3830  sputLua_GetTextSpeed ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: GetTextSpeed Original name sputLua_GetTextSpeed (the remaster's GrimFandango (Linux):
   Lua / module table entry 'GetTextSpeed'); was Lua_GetTextSpeed. */

void __fastcall sputLua_GetTextSpeed(undefined4 unused)

{
  int iVar1;
  uint local_8;
  uint local_4;
  
  iVar1 = sputActor_GetActorTextRate();
  lua_pushnumber((float)iVar1);
  return;
}

/* ---- 0x004a3850  sputLua_SetTextSpeed ---- */
/* Lua opcode: SetTextSpeed Original name sputLua_SetTextSpeed (the remaster's GrimFandango (Linux):
   Lua / module table entry 'SetTextSpeed'); was Lua_SetTextSpeed. */

void __cdecl sputLua_SetTextSpeed(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(iVar1);
  if (iVar2 != 0) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    sputActor_SetActorTextRate((int)lVar3);
  }
  return;
}

/* ---- 0x004a3890  sputLua_FindFileOnAnyCD ---- */
/* Lua opcode: FindFileOnAnyCD Original name sputLua_FindFileOnAnyCD (the remaster's GrimFandango
   (Linux): Lua / module table entry 'FindFileOnAnyCD'); was Lua_FindFileOnAnyCD. */

void __cdecl sputLua_FindFileOnAnyCD(void)

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
  uint local_180;
  uint local_178;
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
      lua_pushnumber(1.0f);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef acStack_174
#undef auStack_140


/* ---- 0x004a3a10  sputLua_ActorPuckOrient ---- */
/* Lua opcode: ActorPuckOrient Original name sputLua_ActorPuckOrient (the remaster's GrimFandango
   (Linux): Lua / module table entry 'ActorPuckOrient'); was Lua_ActorPuckOrient. */

void __cdecl sputLua_ActorPuckOrient(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *pAVar4;
  longlong lVar5;
  float fVar6;
  
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
        fVar6 = lua_getnumber(iVar2);
        lVar5 = FTOL((float10)fVar6);
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

void __cdecl sputLua_GetTickCount(void)

{
  uint uVar1;
  uint local_c;
  
  uVar1 = GetTickCount();
  lua_pushnumber((float)uVar1);
  return;
}

/* ---- 0x004a3ae0  sputLua_SetActorInvClipNode ---- */
/* Lua opcode: SetActorInvClipNode Original name sputLua_SetActorInvClipNode (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetActorInvClipNode'); was
   Lua_SetActorInvClipNode. */

void __cdecl sputLua_SetActorInvClipNode(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Actor *actor;
  longlong lVar4;
  float fVar5;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnil(iVar2);
      if (iVar3 == 0) {
        fVar5 = lua_getnumber(iVar2);
        lVar4 = FTOL((float10)fVar5);
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
/* Lua opcode: SetWalkSystemFadeTime Original name sputLua_SetWalkSystemFadeTime (the remaster's
   GrimFandango (Linux): Lua / module table entry 'SetWalkSystemFadeTime'); was
   Lua_SetWalkSystemFadeTime. */

void __cdecl sputLua_SetWalkSystemFadeTime(void)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(iVar1);
  if (iVar2 == 0) {
    fVar4 = lua_getnumber(iVar1);
    lVar3 = FTOL((float10)fVar4);
    sputActor_SetWalkSystemFadeTime((int)lVar3);
  }
  return;
}

/* ---- 0x004be180  Lua_LightMgrStartup ---- */
/* Debug light manager dialog (Lua LightMgrStartup). Creates the dialog, a keyboard hook and a
   helper actor wearing x_spot.cos */

void __cdecl Lua_LightMgrStartup(void)

{
  uint uVar1;
  char *setName;
  int iVar2;
  int a3;
  code *a4;
  int a5;
  
  if (g_pDisplayDevice->nFullscreen != 0) {
    MessageBeep(0);
    return;
  }
  if (g_hLightEdDialog == (void *)0x0) {
    a5 = 0;
    a4 = FUN_004bf950;
    a3 = 0;
    iVar2 = 0x65;
    uVar1 = Win_GetInstance();
    g_hLightEdDialog = (void *)CreateDialogParamA(uVar1,iVar2,a3,(int)a4,a5);
    if (g_hLightEdDialog == (void *)0x0) {
      (*g_pStd_HS->pDebug)(s_LightManager_Startup__Could_not_c_004f0d34);
    }
    else {
      iVar2 = 0;
      uVar1 = Win_GetInstance();
      g_hLightEdHook = (void *)SetWindowsHookExA(2,((unsigned)(uintptr_t)LightEd_KeyboardProc),uVar1,iVar2);
    }
    if (UINT_004f0d0c == 0xffffffff) {
      UINT_004f0d0c = sputActor_AllocateActor();
    }
    g_pLightEdMarkerActor = sputActor_ActorDeref(UINT_004f0d0c);
    sputActor_SetCostume(g_pLightEdMarkerActor,s_x_spot_cos_004f0d28,0);
    setName = sputRoom_GetCurrentRoomName();
    sputRoom_AddActor(setName,g_pLightEdMarkerActor);
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

void __cdecl Lua_LightMgrSetChange(void)

{
  char *setName;
  
  if (g_hLightEdDialog != (void *)0x0) {
    g_pLightEdSet = sputRoom_GetCurrentRoom();
    setName = sputRoom_GetCurrentRoomName();
    if (g_pLightEdMarkerActor != (Actor *)0x0) {
      sputRoom_AddActor(setName,g_pLightEdMarkerActor);
    }
    LightMgr_Refresh();
    LightMgr_UpdateDialog((uint)g_hLightEdDialog);
  }
  return;
}

/* ---- 0x004be2a0  Lua_LightMgrShutdown ---- */
/* Lua opcode: LightMgrShutdown */

void __cdecl Lua_LightMgrShutdown(void)

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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char f_Lua_LightMgrSetChange[] __asm__("_Lua_LightMgrSetChange");
extern char f_Lua_LightMgrShutdown[] __asm__("_Lua_LightMgrShutdown");
extern char f_Lua_LightMgrStartup[] __asm__("_Lua_LightMgrStartup");
extern char f_Lua_Print_NoOp[] __asm__("_Lua_Print_NoOp");
extern char f_Lua_Stub[] __asm__("_Lua_Stub");
extern char f_Lua_TextFileGetLine[] __asm__("_Lua_TextFileGetLine");
extern char f_Lua_TextFileGetLineCount[] __asm__("_Lua_TextFileGetLineCount");
extern char f_grimlib_NextSetup[] __asm__("_grimlib_NextSetup");
extern char f_grimlib_PreviousSetup[] __asm__("_grimlib_PreviousSetup");
extern char f_sputLua_ActivateActorShadow[] __asm__("_sputLua_ActivateActorShadow");
extern char f_sputLua_ActorDistToShadowPlane[] __asm__("_sputLua_ActorDistToShadowPlane");
extern char f_sputLua_ActorLookAtL[] __asm__("_sputLua_ActorLookAtL");
extern char f_sputLua_ActorPuckOrient[] __asm__("_sputLua_ActorPuckOrient");
extern char f_sputLua_ActorShadow[] __asm__("_sputLua_ActorShadow");
extern char f_sputLua_ActorToClean[] __asm__("_sputLua_ActorToClean");
extern char f_sputLua_ActorVoiceIs3DL[] __asm__("_sputLua_ActorVoiceIs3DL");
extern char f_sputLua_AddShadowClipPlane[] __asm__("_sputLua_AddShadowClipPlane");
extern char f_sputLua_AllocateActorL[] __asm__("_sputLua_AllocateActorL");
extern char f_sputLua_AttachToResourcesL[] __asm__("_sputLua_AttachToResourcesL");
extern char f_sputLua_BlastImage[] __asm__("_sputLua_BlastImage");
extern char f_sputLua_BlastRect[] __asm__("_sputLua_BlastRect");
extern char f_sputLua_BuildCache[] __asm__("_sputLua_BuildCache");
extern char f_sputLua_CacheRect[] __asm__("_sputLua_CacheRect");
extern char f_sputLua_CanActorSeeL[] __asm__("_sputLua_CanActorSeeL");
extern char f_sputLua_CheckForFileL[] __asm__("_sputLua_CheckForFileL");
extern char f_sputLua_CleanBuffer[] __asm__("_sputLua_CleanBuffer");
extern char f_sputLua_CompleteActorChoreL[] __asm__("_sputLua_CompleteActorChoreL");
extern char f_sputLua_ConcatFallback[] __asm__("_sputLua_ConcatFallback");
extern char f_sputLua_DetachFromResourcesL[] __asm__("_sputLua_DetachFromResourcesL");
extern char f_sputLua_DimRegion[] __asm__("_sputLua_DimRegion");
extern char f_sputLua_DimScreen[] __asm__("_sputLua_DimScreen");
extern char f_sputLua_DisableControlL[] __asm__("_sputLua_DisableControlL");
extern char f_sputLua_Display[] __asm__("_sputLua_Display");
extern char f_sputLua_DumpMemoryLogL[] __asm__("_sputLua_DumpMemoryLogL");
extern char f_sputLua_EnableControlL[] __asm__("_sputLua_EnableControlL");
extern char f_sputLua_EnableDebugKeysL[] __asm__("_sputLua_EnableDebugKeysL");
extern char f_sputLua_EngineDisplay[] __asm__("_sputLua_EngineDisplay");
extern char f_sputLua_EnginePause[] __asm__("_sputLua_EnginePause");
extern char f_sputLua_EngineResume[] __asm__("_sputLua_EngineResume");
extern char f_sputLua_ExitL[] __asm__("_sputLua_ExitL");
extern char f_sputLua_FadeInChore[] __asm__("_sputLua_FadeInChore");
extern char f_sputLua_FadeOutChore[] __asm__("_sputLua_FadeOutChore");
extern char f_sputLua_FileFindDispose[] __asm__("_sputLua_FileFindDispose");
extern char f_sputLua_FileFindFirst[] __asm__("_sputLua_FileFindFirst");
extern char f_sputLua_FileFindNext[] __asm__("_sputLua_FileFindNext");
extern char f_sputLua_FindFileOnAnyCD[] __asm__("_sputLua_FindFileOnAnyCD");
extern char f_sputLua_FindLight[] __asm__("_sputLua_FindLight");
extern char f_sputLua_FreeImage[] __asm__("_sputLua_FreeImage");
extern char f_sputLua_FreeObjectState[] __asm__("_sputLua_FreeObjectState");
extern char f_sputLua_FunctionNameL[] __asm__("_sputLua_FunctionNameL");
extern char f_sputLua_GetActorChoresL[] __asm__("_sputLua_GetActorChoresL");
extern char f_sputLua_GetActorCostumeDepthL[] __asm__("_sputLua_GetActorCostumeDepthL");
extern char f_sputLua_GetActorCostumeL[] __asm__("_sputLua_GetActorCostumeL");
extern char f_sputLua_GetActorLookRate[] __asm__("_sputLua_GetActorLookRate");
extern char f_sputLua_GetActorLoopingChoresL[] __asm__("_sputLua_GetActorLoopingChoresL");
extern char f_sputLua_GetActorNodeLocationL[] __asm__("_sputLua_GetActorNodeLocationL");
extern char f_sputLua_GetActorPosL[] __asm__("_sputLua_GetActorPosL");
extern char f_sputLua_GetActorPuckVectorL[] __asm__("_sputLua_GetActorPuckVectorL");
extern char f_sputLua_GetActorRectL[] __asm__("_sputLua_GetActorRectL");
extern char f_sputLua_GetActorRotL[] __asm__("_sputLua_GetActorRotL");
extern char f_sputLua_GetActorScaleL[] __asm__("_sputLua_GetActorScaleL");
extern char f_sputLua_GetActorSectorL[] __asm__("_sputLua_GetActorSectorL");
extern char f_sputLua_GetActorTimeScaleL[] __asm__("_sputLua_GetActorTimeScaleL");
extern char f_sputLua_GetActorTurnRateL[] __asm__("_sputLua_GetActorTurnRateL");
extern char f_sputLua_GetActorWalkRateL[] __asm__("_sputLua_GetActorWalkRateL");
extern char f_sputLua_GetActorYawToPoint[] __asm__("_sputLua_GetActorYawToPoint");
extern char f_sputLua_GetAngleBetweenActorsL[] __asm__("_sputLua_GetAngleBetweenActorsL");
extern char f_sputLua_GetAngleBetweenVectorsL[] __asm__("_sputLua_GetAngleBetweenVectorsL");
extern char f_sputLua_GetCameraActorL[] __asm__("_sputLua_GetCameraActorL");
extern char f_sputLua_GetCameraFOVL[] __asm__("_sputLua_GetCameraFOVL");
extern char f_sputLua_GetCameraInterestL[] __asm__("_sputLua_GetCameraInterestL");
extern char f_sputLua_GetCameraLookVectorL[] __asm__("_sputLua_GetCameraLookVectorL");
extern char f_sputLua_GetCameraPositionL[] __asm__("_sputLua_GetCameraPositionL");
extern char f_sputLua_GetCameraRollL[] __asm__("_sputLua_GetCameraRollL");
extern char f_sputLua_GetControlStateL[] __asm__("_sputLua_GetControlStateL");
extern char f_sputLua_GetCurrentScript[] __asm__("_sputLua_GetCurrentScript");
extern char f_sputLua_GetCurrentSetupL[] __asm__("_sputLua_GetCurrentSetupL");
extern char f_sputLua_GetDiskFreeSpaceL[] __asm__("_sputLua_GetDiskFreeSpaceL");
extern char f_sputLua_GetImage[] __asm__("_sputLua_GetImage");
extern char f_sputLua_GetLightAngles[] __asm__("_sputLua_GetLightAngles");
extern char f_sputLua_GetLightIntensity[] __asm__("_sputLua_GetLightIntensity");
extern char f_sputLua_GetLightPosition[] __asm__("_sputLua_GetLightPosition");
extern char f_sputLua_GetLightRotation[] __asm__("_sputLua_GetLightRotation");
extern char f_sputLua_GetLightType[] __asm__("_sputLua_GetLightType");
extern char f_sputLua_GetMemoryUsageL[] __asm__("_sputLua_GetMemoryUsageL");
extern char f_sputLua_GetPhysicalBytes[] __asm__("_sputLua_GetPhysicalBytes");
extern char f_sputLua_GetPointSectorL[] __asm__("_sputLua_GetPointSectorL");
extern char f_sputLua_GetSaveGameData[] __asm__("_sputLua_GetSaveGameData");
extern char f_sputLua_GetSaveGameImage[] __asm__("_sputLua_GetSaveGameImage");
extern char f_sputLua_GetSectorOppositeEdge[] __asm__("_sputLua_GetSectorOppositeEdge");
extern char f_sputLua_GetShrinkPosition[] __asm__("_sputLua_GetShrinkPosition");
extern char f_sputLua_GetSoundParametersL[] __asm__("_sputLua_GetSoundParametersL");
extern char f_sputLua_GetSpeechMode[] __asm__("_sputLua_GetSpeechMode");
extern char f_sputLua_GetTextSpeed[] __asm__("_sputLua_GetTextSpeed");
extern char f_sputLua_GetTickCount[] __asm__("_sputLua_GetTickCount");
extern char f_sputLua_GetVisibleThingsL[] __asm__("_sputLua_GetVisibleThingsL");
extern char f_sputLua_HardwareAccelerated[] __asm__("_sputLua_HardwareAccelerated");
extern char f_sputLua_ImFadeParam[] __asm__("_sputLua_ImFadeParam");
extern char f_sputLua_ImGetMasterVol[] __asm__("_sputLua_ImGetMasterVol");
extern char f_sputLua_ImGetMemoryFootprint[] __asm__("_sputLua_ImGetMemoryFootprint");
extern char f_sputLua_ImGetMusicVol[] __asm__("_sputLua_ImGetMusicVol");
extern char f_sputLua_ImGetParam[] __asm__("_sputLua_ImGetParam");
extern char f_sputLua_ImGetSfxVol[] __asm__("_sputLua_ImGetSfxVol");
extern char f_sputLua_ImGetSoundCacheSize[] __asm__("_sputLua_ImGetSoundCacheSize");
extern char f_sputLua_ImGetVoiceVol[] __asm__("_sputLua_ImGetVoiceVol");
extern char f_sputLua_ImPause[] __asm__("_sputLua_ImPause");
extern char f_sputLua_ImResume[] __asm__("_sputLua_ImResume");
extern char f_sputLua_ImSetAttribute[] __asm__("_sputLua_ImSetAttribute");
extern char f_sputLua_ImSetCuePoint[] __asm__("_sputLua_ImSetCuePoint");
extern char f_sputLua_ImSetMasterVol[] __asm__("_sputLua_ImSetMasterVol");
extern char f_sputLua_ImSetMusicVol[] __asm__("_sputLua_ImSetMusicVol");
extern char f_sputLua_ImSetParam[] __asm__("_sputLua_ImSetParam");
extern char f_sputLua_ImSetSequence[] __asm__("_sputLua_ImSetSequence");
extern char f_sputLua_ImSetSfxVol[] __asm__("_sputLua_ImSetSfxVol");
extern char f_sputLua_ImSetState[] __asm__("_sputLua_ImSetState");
extern char f_sputLua_ImSetVoiceEffect[] __asm__("_sputLua_ImSetVoiceEffect");
extern char f_sputLua_ImSetVoiceVol[] __asm__("_sputLua_ImSetVoiceVol");
extern char f_sputLua_ImStartRecording[] __asm__("_sputLua_ImStartRecording");
extern char f_sputLua_ImStartSound[] __asm__("_sputLua_ImStartSound");
extern char f_sputLua_ImStartVoice[] __asm__("_sputLua_ImStartVoice");
extern char f_sputLua_ImStopAllSounds[] __asm__("_sputLua_ImStopAllSounds");
extern char f_sputLua_ImStopRecording[] __asm__("_sputLua_ImStopRecording");
extern char f_sputLua_ImStopSound[] __asm__("_sputLua_ImStopSound");
extern char f_sputLua_ImStopVoice[] __asm__("_sputLua_ImStopVoice");
extern char f_sputLua_InputDialog[] __asm__("_sputLua_InputDialog");
extern char f_sputLua_IrisComplete[] __asm__("_sputLua_IrisComplete");
extern char f_sputLua_IrisDown[] __asm__("_sputLua_IrisDown");
extern char f_sputLua_IrisUp[] __asm__("_sputLua_IrisUp");
extern char f_sputLua_IsActorChoringL[] __asm__("_sputLua_IsActorChoringL");
extern char f_sputLua_IsActorInSector[] __asm__("_sputLua_IsActorInSector");
extern char f_sputLua_IsActorLookingL[] __asm__("_sputLua_IsActorLookingL");
extern char f_sputLua_IsActorMovingL[] __asm__("_sputLua_IsActorMovingL");
extern char f_sputLua_IsActorRestingL[] __asm__("_sputLua_IsActorRestingL");
extern char f_sputLua_IsActorTurningL[] __asm__("_sputLua_IsActorTurningL");
extern char f_sputLua_IsLightOn[] __asm__("_sputLua_IsLightOn");
extern char f_sputLua_IsMoviePlayingL[] __asm__("_sputLua_IsMoviePlayingL");
extern char f_sputLua_IsPointInSector[] __asm__("_sputLua_IsPointInSector");
extern char f_sputLua_IsSectorActiveL[] __asm__("_sputLua_IsSectorActiveL");
extern char f_sputLua_JustLoadedL[] __asm__("_sputLua_JustLoadedL");
extern char f_sputLua_KillActorShadows[] __asm__("_sputLua_KillActorShadows");
extern char f_sputLua_LoadCostumeL[] __asm__("_sputLua_LoadCostumeL");
extern char f_sputLua_LoadL[] __asm__("_sputLua_LoadL");
extern char f_sputLua_LockFontL[] __asm__("_sputLua_LockFontL");
extern char f_sputLua_LockSet[] __asm__("_sputLua_LockSet");
extern char f_sputLua_MakeCurrentSetL[] __asm__("_sputLua_MakeCurrentSetL");
extern char f_sputLua_MakeCurrentSetupL[] __asm__("_sputLua_MakeCurrentSetupL");
extern char f_sputLua_MakeSectorActiveL[] __asm__("_sputLua_MakeSectorActiveL");
extern char f_sputLua_MarkDirtyRect[] __asm__("_sputLua_MarkDirtyRect");
extern char f_sputLua_MessagePrintL[] __asm__("_sputLua_MessagePrintL");
extern char f_sputLua_NewObjectState[] __asm__("_sputLua_NewObjectState");
extern char f_sputLua_NukeResourcesL[] __asm__("_sputLua_NukeResourcesL");
extern char f_sputLua_PauseMovieL[] __asm__("_sputLua_PauseMovieL");
extern char f_sputLua_PerSecondL[] __asm__("_sputLua_PerSecondL");
extern char f_sputLua_PlayActorChoreL[] __asm__("_sputLua_PlayActorChoreL");
extern char f_sputLua_PlayActorChoreLoopingL[] __asm__("_sputLua_PlayActorChoreLoopingL");
extern char f_sputLua_PointActorAtL[] __asm__("_sputLua_PointActorAtL");
extern char f_sputLua_PointLightAt[] __asm__("_sputLua_PointLightAt");
extern char f_sputLua_PopActorCostumeL[] __asm__("_sputLua_PopActorCostumeL");
extern char f_sputLua_PreRender[] __asm__("_sputLua_PreRender");
extern char f_sputLua_PrintActorCostumesL[] __asm__("_sputLua_PrintActorCostumesL");
extern char f_sputLua_PushActorCostumeL[] __asm__("_sputLua_PushActorCostumeL");
extern char f_sputLua_PutActorAtInterestL[] __asm__("_sputLua_PutActorAtInterestL");
extern char f_sputLua_PutActorAtL[] __asm__("_sputLua_PutActorAtL");
extern char f_sputLua_PutActorInSetL[] __asm__("_sputLua_PutActorInSetL");
extern char f_sputLua_QueryDialog[] __asm__("_sputLua_QueryDialog");
extern char f_sputLua_ReadRegistryValue[] __asm__("_sputLua_ReadRegistryValue");
extern char f_sputLua_RenderModeUser[] __asm__("_sputLua_RenderModeUser");
extern char f_sputLua_ResReport[] __asm__("_sputLua_ResReport");
extern char f_sputLua_ResetTexturesL[] __asm__("_sputLua_ResetTexturesL");
extern char f_sputLua_RestoreCacheRect[] __asm__("_sputLua_RestoreCacheRect");
extern char f_sputLua_RestoreIMuse[] __asm__("_sputLua_RestoreIMuse");
extern char f_sputLua_RevertCache[] __asm__("_sputLua_RevertCache");
extern char f_sputLua_RotateVectorL[] __asm__("_sputLua_RotateVectorL");
extern char f_sputLua_SaveIMuse[] __asm__("_sputLua_SaveIMuse");
extern char f_sputLua_SaveL[] __asm__("_sputLua_SaveL");
extern char f_sputLua_SaveScreen[] __asm__("_sputLua_SaveScreen");
extern char f_sputLua_ScreenShot[] __asm__("_sputLua_ScreenShot");
extern char f_sputLua_ScreenToWorldL[] __asm__("_sputLua_ScreenToWorldL");
extern char f_sputLua_SearchForFileOrSwapCDsL[] __asm__("_sputLua_SearchForFileOrSwapCDsL");
extern char f_sputLua_SendObjectToBack[] __asm__("_sputLua_SendObjectToBack");
extern char f_sputLua_SendObjectToFront[] __asm__("_sputLua_SendObjectToFront");
extern char f_sputLua_SetActiveShadow[] __asm__("_sputLua_SetActiveShadow");
extern char f_sputLua_SetActorChoreLoopingL[] __asm__("_sputLua_SetActorChoreLoopingL");
extern char f_sputLua_SetActorClipActive[] __asm__("_sputLua_SetActorClipActive");
extern char f_sputLua_SetActorClipPlane[] __asm__("_sputLua_SetActorClipPlane");
extern char f_sputLua_SetActorCollisionMode[] __asm__("_sputLua_SetActorCollisionMode");
extern char f_sputLua_SetActorCollisionScale[] __asm__("_sputLua_SetActorCollisionScale");
extern char f_sputLua_SetActorColormapL[] __asm__("_sputLua_SetActorColormapL");
extern char f_sputLua_SetActorConstrain[] __asm__("_sputLua_SetActorConstrain");
extern char f_sputLua_SetActorCostumeL[] __asm__("_sputLua_SetActorCostumeL");
extern char f_sputLua_SetActorFollowBoxesL[] __asm__("_sputLua_SetActorFollowBoxesL");
extern char f_sputLua_SetActorFrustrumCull[] __asm__("_sputLua_SetActorFrustrumCull");
extern char f_sputLua_SetActorHeadL[] __asm__("_sputLua_SetActorHeadL");
extern char f_sputLua_SetActorInvClipNode[] __asm__("_sputLua_SetActorInvClipNode");
extern char f_sputLua_SetActorLookRate[] __asm__("_sputLua_SetActorLookRate");
extern char f_sputLua_SetActorMumbleChoreL[] __asm__("_sputLua_SetActorMumbleChoreL");
extern char f_sputLua_SetActorOffsetYaw[] __asm__("_sputLua_SetActorOffsetYaw");
extern char f_sputLua_SetActorPitch[] __asm__("_sputLua_SetActorPitch");
extern char f_sputLua_SetActorReflection[] __asm__("_sputLua_SetActorReflection");
extern char f_sputLua_SetActorRestChoreL[] __asm__("_sputLua_SetActorRestChoreL");
extern char f_sputLua_SetActorRoll[] __asm__("_sputLua_SetActorRoll");
extern char f_sputLua_SetActorRotL[] __asm__("_sputLua_SetActorRotL");
extern char f_sputLua_SetActorScaleL[] __asm__("_sputLua_SetActorScaleL");
extern char f_sputLua_SetActorShadowPlane[] __asm__("_sputLua_SetActorShadowPlane");
extern char f_sputLua_SetActorShadowPoint[] __asm__("_sputLua_SetActorShadowPoint");
extern char f_sputLua_SetActorShadowValid[] __asm__("_sputLua_SetActorShadowValid");
extern char f_sputLua_SetActorTalkChoreL[] __asm__("_sputLua_SetActorTalkChoreL");
extern char f_sputLua_SetActorTimeScaleL[] __asm__("_sputLua_SetActorTimeScaleL");
extern char f_sputLua_SetActorTurnChoresL[] __asm__("_sputLua_SetActorTurnChoresL");
extern char f_sputLua_SetActorTurnRateL[] __asm__("_sputLua_SetActorTurnRateL");
extern char f_sputLua_SetActorVisibilityL[] __asm__("_sputLua_SetActorVisibilityL");
extern char f_sputLua_SetActorWalkChoresL[] __asm__("_sputLua_SetActorWalkChoresL");
extern char f_sputLua_SetActorWalkDominate[] __asm__("_sputLua_SetActorWalkDominate");
extern char f_sputLua_SetActorWalkRateL[] __asm__("_sputLua_SetActorWalkRateL");
extern char f_sputLua_SetAmbientLight[] __asm__("_sputLua_SetAmbientLight");
extern char f_sputLua_SetCameraFOVL[] __asm__("_sputLua_SetCameraFOVL");
extern char f_sputLua_SetCameraInterestL[] __asm__("_sputLua_SetCameraInterestL");
extern char f_sputLua_SetCameraPositionL[] __asm__("_sputLua_SetCameraPositionL");
extern char f_sputLua_SetCameraRollL[] __asm__("_sputLua_SetCameraRollL");
extern char f_sputLua_SetGamma[] __asm__("_sputLua_SetGamma");
extern char f_sputLua_SetLightAngles[] __asm__("_sputLua_SetLightAngles");
extern char f_sputLua_SetLightIntensity[] __asm__("_sputLua_SetLightIntensity");
extern char f_sputLua_SetLightPosition[] __asm__("_sputLua_SetLightPosition");
extern char f_sputLua_SetLightRotation[] __asm__("_sputLua_SetLightRotation");
extern char f_sputLua_SetLightType[] __asm__("_sputLua_SetLightType");
extern char f_sputLua_SetMemoryUsage[] __asm__("_sputLua_SetMemoryUsage");
extern char f_sputLua_SetObjectType[] __asm__("_sputLua_SetObjectType");
extern char f_sputLua_SetSelectedActorL[] __asm__("_sputLua_SetSelectedActorL");
extern char f_sputLua_SetShadowColor[] __asm__("_sputLua_SetShadowColor");
extern char f_sputLua_SetSoundParametersL[] __asm__("_sputLua_SetSoundParametersL");
extern char f_sputLua_SetSoundPosition[] __asm__("_sputLua_SetSoundPosition");
extern char f_sputLua_SetSpeechMode[] __asm__("_sputLua_SetSpeechMode");
extern char f_sputLua_SetTextSpeed[] __asm__("_sputLua_SetTextSpeed");
extern char f_sputLua_SetWalkSystemFadeTime[] __asm__("_sputLua_SetWalkSystemFadeTime");
extern char f_sputLua_ShrinkBoxes[] __asm__("_sputLua_ShrinkBoxes");
extern char f_sputLua_ShutUpActorL[] __asm__("_sputLua_ShutUpActorL");
extern char f_sputLua_SnapToPlane[] __asm__("_sputLua_SnapToPlane");
extern char f_sputLua_SpewShutdown[] __asm__("_sputLua_SpewShutdown");
extern char f_sputLua_SpewStartup[] __asm__("_sputLua_SpewStartup");
extern char f_sputLua_StartFullScreenMovieL[] __asm__("_sputLua_StartFullScreenMovieL");
extern char f_sputLua_StartMovieL[] __asm__("_sputLua_StartMovieL");
extern char f_sputLua_StopActorChoreL[] __asm__("_sputLua_StopActorChoreL");
extern char f_sputLua_StopMovieL[] __asm__("_sputLua_StopMovieL");
extern char f_sputLua_SubmitSaveGameData[] __asm__("_sputLua_SubmitSaveGameData");
extern char f_sputLua_Test[] __asm__("_sputLua_Test");
extern char f_sputLua_TurnActorL[] __asm__("_sputLua_TurnActorL");
extern char f_sputLua_TurnActorTo[] __asm__("_sputLua_TurnActorTo");
extern char f_sputLua_TurnLightOn[] __asm__("_sputLua_TurnLightOn");
extern char f_sputLua_TypeOverride[] __asm__("_sputLua_TypeOverride");
extern char f_sputLua_UnLockSet[] __asm__("_sputLua_UnLockSet");
extern char f_sputLua_UnShrinkBoxes[] __asm__("_sputLua_UnShrinkBoxes");
extern char f_sputLua_WalkActorForwardL[] __asm__("_sputLua_WalkActorForwardL");
extern char f_sputLua_WalkActorToAvoidingL[] __asm__("_sputLua_WalkActorToAvoidingL");
extern char f_sputLua_WalkActorToL[] __asm__("_sputLua_WalkActorToL");
extern char f_sputLua_WalkActorVectorL[] __asm__("_sputLua_WalkActorVectorL");
extern char f_sputLua_WorldToScreenL[] __asm__("_sputLua_WorldToScreenL");
extern char f_sputLua_WriteRegistryValue[] __asm__("_sputLua_WriteRegistryValue");
extern char f_sputRender_ClearIris[] __asm__("_sputRender_ClearIris");
extern char f_sputRender_ForceRefresh[] __asm__("_sputRender_ForceRefresh");
extern char f_stdControl_Flush[] __asm__("_stdControl_Flush");
extern char grim_def_DAT_004e8448[] __asm__("_DAT_004e8448");
extern char grim_def_DAT_004e844c[] __asm__("_DAT_004e844c");
extern char grim_def_DAT_004eb16c[] __asm__("_DAT_004eb16c");
extern char grim_def_DAT_004eb17c[] __asm__("_DAT_004eb17c");
extern char grim_def_DAT_004eb18c[] __asm__("_DAT_004eb18c");
extern char grim_def_DAT_004eb198[] __asm__("_DAT_004eb198");
extern char grim_def_DAT_004eb1b0[] __asm__("_DAT_004eb1b0");
extern char grim_def_DAT_004eb1c4[] __asm__("_DAT_004eb1c4");
extern char grim_def_DAT_004eb1d8[] __asm__("_DAT_004eb1d8");
extern char grim_def_DAT_004eb1e8[] __asm__("_DAT_004eb1e8");
extern char grim_def_DAT_004eb1f8[] __asm__("_DAT_004eb1f8");
extern char grim_def_DAT_004eb208[] __asm__("_DAT_004eb208");
extern char grim_def_DAT_004eb214[] __asm__("_DAT_004eb214");
extern char grim_def_DAT_004eb224[] __asm__("_DAT_004eb224");
extern char grim_def_DAT_004eb230[] __asm__("_DAT_004eb230");
extern char grim_def_DAT_004eb240[] __asm__("_DAT_004eb240");
extern char grim_def_DAT_004eb250[] __asm__("_DAT_004eb250");
extern char grim_def_DAT_004eb25c[] __asm__("_DAT_004eb25c");
extern char grim_def_DAT_004eb26c[] __asm__("_DAT_004eb26c");
extern char grim_def_DAT_004eb27c[] __asm__("_DAT_004eb27c");
extern char grim_def_DAT_004eb28c[] __asm__("_DAT_004eb28c");
extern char grim_def_DAT_004eb294[] __asm__("_DAT_004eb294");
extern char grim_def_DAT_004eb2a8[] __asm__("_DAT_004eb2a8");
extern char grim_def_DAT_004eb2bc[] __asm__("_DAT_004eb2bc");
extern char grim_def_DAT_004eb2d0[] __asm__("_DAT_004eb2d0");
extern char grim_def_DAT_004eb2e4[] __asm__("_DAT_004eb2e4");
extern char grim_def_DAT_004eb2f4[] __asm__("_DAT_004eb2f4");
extern char grim_def_DAT_004eb304[] __asm__("_DAT_004eb304");
extern char grim_def_DAT_004eb314[] __asm__("_DAT_004eb314");
extern char grim_def_DAT_004eb324[] __asm__("_DAT_004eb324");
extern char grim_def_DAT_004eb338[] __asm__("_DAT_004eb338");
extern char grim_def_DAT_004eb344[] __asm__("_DAT_004eb344");
extern char grim_def_DAT_004eb350[] __asm__("_DAT_004eb350");
extern char grim_def_DAT_004eb35c[] __asm__("_DAT_004eb35c");
extern char grim_def_DAT_004eb368[] __asm__("_DAT_004eb368");
extern char grim_def_DAT_004eb37c[] __asm__("_DAT_004eb37c");
extern char grim_def_DAT_004eb388[] __asm__("_DAT_004eb388");
extern char grim_def_DAT_004eb394[] __asm__("_DAT_004eb394");
extern char grim_def_DAT_004eb3a4[] __asm__("_DAT_004eb3a4");
extern char grim_def_DAT_004eb3bc[] __asm__("_DAT_004eb3bc");
extern char grim_def_DAT_004eb6e0[] __asm__("_DAT_004eb6e0");
extern char grim_def_DAT_004eb810[] __asm__("_DAT_004eb810");
extern char grim_def_DAT_004ebdec[] __asm__("_DAT_004ebdec");
extern char grim_def_DAT_004ec2dc[] __asm__("_DAT_004ec2dc");
extern char grim_def_DAT_004ec2e4[] __asm__("_DAT_004ec2e4");
extern void *grim_def_PTR_DAT_004e837c __asm__("_PTR_DAT_004e837c");
extern void *grim_def_PTR_DAT_004e8380 __asm__("_PTR_DAT_004e8380");
extern void *grim_def_PTR_s_EnginePause_004ea8b0[558] __asm__("_PTR_s_EnginePause_004ea8b0");
extern void *grim_def_PTR_s_color_004e8368 __asm__("_PTR_s_color_004e8368");
extern void *grim_def_PTR_s_concatfallback_004ea890[8] __asm__("_PTR_s_concatfallback_004ea890");
extern void *grim_def_PTR_s_filled_004e838c __asm__("_PTR_s_filled_004e838c");
extern void *grim_def_PTR_s_height_004e8388 __asm__("_PTR_s_height_004e8388");
extern void *grim_def_PTR_s_layer_004e8390 __asm__("_PTR_s_layer_004e8390");
extern void *grim_def_PTR_s_width_004e8384 __asm__("_PTR_s_width_004e8384");
extern void *grim_def_PTR_s_x_004e8374 __asm__("_PTR_s_x_004e8374");
extern void *grim_def_PTR_s_xoffset_004e836c __asm__("_PTR_s_xoffset_004e836c");
extern void *grim_def_PTR_s_y_004e8378 __asm__("_PTR_s_y_004e8378");
extern void *grim_def_PTR_s_yoffset_004e8370 __asm__("_PTR_s_yoffset_004e8370");
extern unsigned int grim_def_UINT_004ddab4 __asm__("_UINT_004ddab4");
extern unsigned int grim_def_UINT_004ddab8 __asm__("_UINT_004ddab8");
extern unsigned int grim_def_UINT_004ddabc __asm__("_UINT_004ddabc");
extern unsigned int grim_def_UINT_004ddac0 __asm__("_UINT_004ddac0");
extern unsigned int grim_def_UINT_004ddac4 __asm__("_UINT_004ddac4");
extern unsigned char grim_def_UINT_004ddac8[16] __asm__("_UINT_004ddac8");
extern unsigned int grim_def_UINT_004e8470 __asm__("_UINT_004e8470");
extern unsigned int grim_def_UINT_004e8474 __asm__("_UINT_004e8474");
extern unsigned int grim_def_UINT_004e8480 __asm__("_UINT_004e8480");
extern unsigned int grim_def_UINT_004e8484 __asm__("_UINT_004e8484");
extern unsigned int grim_def_UINT_004eb168 __asm__("_UINT_004eb168");
extern unsigned int grim_def_UINT_004f0d0c __asm__("_UINT_004f0d0c");
extern unsigned int grim_def_g_dwDebugToggleFunc __asm__("_g_dwDebugToggleFunc");
extern unsigned int grim_def_g_dwLrOldConcatFallback __asm__("_g_dwLrOldConcatFallback");
extern char grim_def_s_ActivateActorShadow_004eb5bc[] __asm__("_s_ActivateActorShadow_004eb5bc");
extern char grim_def_s_ActorDistToShadowPlane_004eb560[] __asm__("_s_ActorDistToShadowPlane_004eb560");
extern char grim_def_s_ActorLookAt_004ec040[] __asm__("_s_ActorLookAt_004ec040");
extern char grim_def_s_ActorShadow_004eb5b0[] __asm__("_s_ActorShadow_004eb5b0");
extern char grim_def_s_ActorToClean_004eb4c0[] __asm__("_s_ActorToClean_004eb4c0");
extern char grim_def_s_AddShadowPlane_004eb53c[] __asm__("_s_AddShadowPlane_004eb53c");
extern char grim_def_s_BOOT_004ec3c8[8] __asm__("_s_BOOT_004ec3c8");
extern char grim_def_s_CAMERA_004ec534[8] __asm__("_s_CAMERA_004ec534");
extern char grim_def_s_C__grimsrc_libs_grimlib_Scripts__004ec38c[44] __asm__("_s_C__grimsrc_libs_grimlib_Scripts__004ec38c");
extern char grim_def_s_CacheRect_004eb464[] __asm__("_s_CacheRect_004eb464");
extern char grim_def_s_CanActorSee_004ebffc[] __asm__("_s_CanActorSee_004ebffc");
extern char grim_def_s_CheckForFile_004ec2ec[] __asm__("_s_CheckForFile_004ec2ec");
extern char grim_def_s_CleanBuffer_004eb608[] __asm__("_s_CleanBuffer_004eb608");
extern char grim_def_s_CompleteActorChore_004ebe9c[] __asm__("_s_CompleteActorChore_004ebe9c");
extern char grim_def_s_DimRegion_004eb614[] __asm__("_s_DimRegion_004eb614");
extern char grim_def_s_DimScreen_004eb620[] __asm__("_s_DimScreen_004eb620");
extern char grim_def_s_DisableControl_004ebd60[] __asm__("_s_DisableControl_004ebd60");
extern char grim_def_s_Display_004eb600[] __asm__("_s_Display_004eb600");
extern char grim_def_s_DriveActorTo_004ec080[] __asm__("_s_DriveActorTo_004ec080");
extern char grim_def_s_EnableControl_004ebd70[] __asm__("_s_EnableControl_004ebd70");
extern char grim_def_s_EnableDebugKeys_004ebdcc[] __asm__("_s_EnableDebugKeys_004ebdcc");
extern char grim_def_s_EngineDisplay_004ec314[] __asm__("_s_EngineDisplay_004ec314");
extern char grim_def_s_EnginePause_004ec334[] __asm__("_s_EnginePause_004ec334");
extern char grim_def_s_EngineResume_004ec324[] __asm__("_s_EngineResume_004ec324");
extern char grim_def_s_FadeInChore_004eb3ec[] __asm__("_s_FadeInChore_004eb3ec");
extern char grim_def_s_FadeOutChore_004eb3f8[] __asm__("_s_FadeOutChore_004eb3f8");
extern char grim_def_s_FileFindDispose_004ebbcc[] __asm__("_s_FileFindDispose_004ebbcc");
extern char grim_def_s_FileFindFirst_004ebbec[] __asm__("_s_FileFindFirst_004ebbec");
extern char grim_def_s_FileFindNext_004ebbdc[] __asm__("_s_FileFindNext_004ebbdc");
extern char grim_def_s_FindLight_004eb964[] __asm__("_s_FindLight_004eb964");
extern char grim_def_s_FlushControls_004eb4b0[] __asm__("_s_FlushControls_004eb4b0");
extern char grim_def_s_ForceRefresh_004eb62c[] __asm__("_s_ForceRefresh_004eb62c");
extern char grim_def_s_FreeObjectState_004eb508[] __asm__("_s_FreeObjectState_004eb508");
extern char grim_def_s_FunctionName_004ebddc[] __asm__("_s_FunctionName_004ebddc");
extern char grim_def_s_GetActorChores_004ebe44[] __asm__("_s_GetActorChores_004ebe44");
extern char grim_def_s_GetActorCostumeDepth_004ebe14[] __asm__("_s_GetActorCostumeDepth_004ebe14");
extern char grim_def_s_GetActorCostume_004ec2b8[] __asm__("_s_GetActorCostume_004ec2b8");
extern char grim_def_s_GetActorLookRate_004ec008[] __asm__("_s_GetActorLookRate_004ec008");
extern char grim_def_s_GetActorLoopingChores_004ebe2c[] __asm__("_s_GetActorLoopingChores_004ebe2c");
extern char grim_def_s_GetActorNodeLocation_004ec248[] __asm__("_s_GetActorNodeLocation_004ec248");
extern char grim_def_s_GetActorPos_004ec168[] __asm__("_s_GetActorPos_004ec168");
extern char grim_def_s_GetActorPuckVector_004ec144[] __asm__("_s_GetActorPuckVector_004ec144");
extern char grim_def_s_GetActorRect_004ec158[] __asm__("_s_GetActorRect_004ec158");
extern char grim_def_s_GetActorRot_004ebf24[] __asm__("_s_GetActorRot_004ebf24");
extern char grim_def_s_GetActorScale_004ec298[] __asm__("_s_GetActorScale_004ec298");
extern char grim_def_s_GetActorSector_004ebf5c[] __asm__("_s_GetActorSector_004ebf5c");
extern char grim_def_s_GetActorTimeScale_004ec274[] __asm__("_s_GetActorTimeScale_004ec274");
extern char grim_def_s_GetActorTurnRate_004ec194[] __asm__("_s_GetActorTurnRate_004ec194");
extern char grim_def_s_GetActorWalkRate_004ec1bc[] __asm__("_s_GetActorWalkRate_004ec1bc");
extern char grim_def_s_GetActorYawToPoint_004ec130[] __asm__("_s_GetActorYawToPoint_004ec130");
extern char grim_def_s_GetAngleBetweenActors_004eb980[] __asm__("_s_GetAngleBetweenActors_004eb980");
extern char grim_def_s_GetAngleBetweenVectors_004eb998[] __asm__("_s_GetAngleBetweenVectors_004eb998");
extern char grim_def_s_GetCameraActor_004ebfd8[] __asm__("_s_GetCameraActor_004ebfd8");
extern char grim_def_s_GetCameraFOV_004eba28[] __asm__("_s_GetCameraFOV_004eba28");
extern char grim_def_s_GetCameraInterest_004eba4c[] __asm__("_s_GetCameraInterest_004eba4c");
extern char grim_def_s_GetCameraLookVector_004eb9e4[] __asm__("_s_GetCameraLookVector_004eb9e4");
extern char grim_def_s_GetCameraPosition_004eba74[] __asm__("_s_GetCameraPosition_004eba74");
extern char grim_def_s_GetCameraRoll_004eba08[] __asm__("_s_GetCameraRoll_004eba08");
extern char grim_def_s_GetClippedPos_004ec0b4[] __asm__("_s_GetClippedPos_004ec0b4");
extern char grim_def_s_GetControlState_004ebd50[] __asm__("_s_GetControlState_004ebd50");
extern char grim_def_s_GetCurrentScript_004ebb00[] __asm__("_s_GetCurrentScript_004ebb00");
extern char grim_def_s_GetCurrentSetup_004ebcd0[] __asm__("_s_GetCurrentSetup_004ebcd0");
extern char grim_def_s_GetLightAngles_004eb8bc[] __asm__("_s_GetLightAngles_004eb8bc");
extern char grim_def_s_GetLightIntensity_004eb894[] __asm__("_s_GetLightIntensity_004eb894");
extern char grim_def_s_GetLightPosition_004eb904[] __asm__("_s_GetLightPosition_004eb904");
extern char grim_def_s_GetLightRotation_004eb8dc[] __asm__("_s_GetLightRotation_004eb8dc");
extern char grim_def_s_GetLightType_004eb92c[] __asm__("_s_GetLightType_004eb92c");
extern char grim_def_s_GetPhysicalBytes_004ebaa8[] __asm__("_s_GetPhysicalBytes_004ebaa8");
extern char grim_def_s_GetPointSector_004ebf3c[] __asm__("_s_GetPointSector_004ebf3c");
extern char grim_def_s_GetSectorOppositeEdge_004ebb60[] __asm__("_s_GetSectorOppositeEdge_004ebb60");
extern char grim_def_s_GetSectorVertices_004ebb78[] __asm__("_s_GetSectorVertices_004ebb78");
extern char grim_def_s_GetSpeechMode_004eb5e0[] __asm__("_s_GetSpeechMode_004eb5e0");
extern char grim_def_s_GetVisibleThings_004ebfe8[] __asm__("_s_GetVisibleThings_004ebfe8");
extern char grim_def_s_HOT_004ec528[4] __asm__("_s_HOT_004ec528");
extern char grim_def_s_HardwareAccelerated_004eb430[] __asm__("_s_HardwareAccelerated_004eb430");
extern char grim_def_s_ImFadeParam_004eb7c8[] __asm__("_s_ImFadeParam_004eb7c8");
extern char grim_def_s_ImGetMasterVol_004eb7b8[] __asm__("_s_ImGetMasterVol_004eb7b8");
extern char grim_def_s_ImGetMemoryFootprint_004eb6b4[] __asm__("_s_ImGetMemoryFootprint_004eb6b4");
extern char grim_def_s_ImGetMusicVol_004eb760[] __asm__("_s_ImGetMusicVol_004eb760");
extern char grim_def_s_ImGetParam_004eb7e0[] __asm__("_s_ImGetParam_004eb7e0");
extern char grim_def_s_ImGetSfxVol_004eb79c[] __asm__("_s_ImGetSfxVol_004eb79c");
extern char grim_def_s_ImGetSoundCacheSize_004eb6a0[] __asm__("_s_ImGetSoundCacheSize_004eb6a0");
extern char grim_def_s_ImGetVoiceVol_004eb780[] __asm__("_s_ImGetVoiceVol_004eb780");
extern char grim_def_s_ImPause_004eb6f0[] __asm__("_s_ImPause_004eb6f0");
extern char grim_def_s_ImResume_004eb6e4[] __asm__("_s_ImResume_004eb6e4");
extern char grim_def_s_ImSetAttribute_004eb708[] __asm__("_s_ImSetAttribute_004eb708");
extern char grim_def_s_ImSetCuePoint_004eb6f8[] __asm__("_s_ImSetCuePoint_004eb6f8");
extern char grim_def_s_ImSetMasterVol_004eb7a8[] __asm__("_s_ImSetMasterVol_004eb7a8");
extern char grim_def_s_ImSetMusicVol_004eb750[] __asm__("_s_ImSetMusicVol_004eb750");
extern char grim_def_s_ImSetParam_004eb7d4[] __asm__("_s_ImSetParam_004eb7d4");
extern char grim_def_s_ImSetSequence_004eb718[] __asm__("_s_ImSetSequence_004eb718");
extern char grim_def_s_ImSetSfxVol_004eb790[] __asm__("_s_ImSetSfxVol_004eb790");
extern char grim_def_s_ImSetState_004eb728[] __asm__("_s_ImSetState_004eb728");
extern char grim_def_s_ImSetVoiceEffect_004eb6cc[] __asm__("_s_ImSetVoiceEffect_004eb6cc");
extern char grim_def_s_ImSetVoiceVol_004eb770[] __asm__("_s_ImSetVoiceVol_004eb770");
extern char grim_def_s_ImStartRecording_004eb838[] __asm__("_s_ImStartRecording_004eb838");
extern char grim_def_s_ImStartSound_004eb818[] __asm__("_s_ImStartSound_004eb818");
extern char grim_def_s_ImStartVoice_004eb740[] __asm__("_s_ImStartVoice_004eb740");
extern char grim_def_s_ImStopAllSounds_004eb7f4[] __asm__("_s_ImStopAllSounds_004eb7f4");
extern char grim_def_s_ImStopRecording_004eb828[] __asm__("_s_ImStopRecording_004eb828");
extern char grim_def_s_ImStopSound_004eb804[] __asm__("_s_ImStopSound_004eb804");
extern char grim_def_s_ImStopVoice_004eb734[] __asm__("_s_ImStopVoice_004eb734");
extern char grim_def_s_InputDialog_004ebbc0[] __asm__("_s_InputDialog_004ebbc0");
extern char grim_def_s_IrisComplete_004eb3c8[] __asm__("_s_IrisComplete_004eb3c8");
extern char grim_def_s_IrisDown_004eb3e0[] __asm__("_s_IrisDown_004eb3e0");
extern char grim_def_s_IrisUp_004eb3d8[] __asm__("_s_IrisUp_004eb3d8");
extern char grim_def_s_IsActorChoring_004ebe7c[] __asm__("_s_IsActorChoring_004ebe7c");
extern char grim_def_s_IsActorInSector_004ebf6c[] __asm__("_s_IsActorInSector_004ebf6c");
extern char grim_def_s_IsActorLooking_004ec030[] __asm__("_s_IsActorLooking_004ec030");
extern char grim_def_s_IsActorMoving_004ebe8c[] __asm__("_s_IsActorMoving_004ebe8c");
extern char grim_def_s_IsActorResting_004ebe6c[] __asm__("_s_IsActorResting_004ebe6c");
extern char grim_def_s_IsActorTurning_004ebee8[] __asm__("_s_IsActorTurning_004ebee8");
extern char grim_def_s_IsFullscreenMoviePlaying_004ebc80[] __asm__("_s_IsFullscreenMoviePlaying_004ebc80");
extern char grim_def_s_IsLightOn_004eb94c[] __asm__("_s_IsLightOn_004eb94c");
extern char grim_def_s_IsMoviePlaying_004ebc4c[] __asm__("_s_IsMoviePlaying_004ebc4c");
extern char grim_def_s_IsPointInSector_004ebf4c[] __asm__("_s_IsPointInSector_004ebf4c");
extern char grim_def_s_IsSectorActive_004ebb50[] __asm__("_s_IsSectorActive_004ebb50");
extern char grim_def_s_IsSoundPlaying_004ebc10[] __asm__("_s_IsSoundPlaying_004ebc10");
extern char grim_def_s_KillActorShadows_004eb54c[] __asm__("_s_KillActorShadows_004eb54c");
extern char grim_def_s_LightManager_Startup__Could_not_c_004f0d34[56] __asm__("_s_LightManager_Startup__Could_not_c_004f0d34");
extern char grim_def_s_LightMgrSetChange_004eb84c[] __asm__("_s_LightMgrSetChange_004eb84c");
extern char grim_def_s_LightMgrShutdown_004eb860[] __asm__("_s_LightMgrShutdown_004eb860");
extern char grim_def_s_LightMgrStartup_004eb874[] __asm__("_s_LightMgrStartup_004eb874");
extern char grim_def_s_LoadActor_004ec174[] __asm__("_s_LoadActor_004ec174");
extern char grim_def_s_LoadBundle_004eb694[] __asm__("_s_LoadBundle_004eb694");
extern char grim_def_s_LoadCostume_004ebabc[] __asm__("_s_LoadCostume_004ebabc");
extern char grim_def_s_LockCostume_004ebd90[] __asm__("_s_LockCostume_004ebd90");
extern char grim_def_s_LockFont_004ebdc0[] __asm__("_s_LockFont_004ebdc0");
extern char grim_def_s_LockSet_004ebd00[] __asm__("_s_LockSet_004ebd00");
extern char grim_def_s_LockSound_004ebda8[] __asm__("_s_LockSound_004ebda8");
extern char grim_def_s_MakeCurrentSet_004ebd08[] __asm__("_s_MakeCurrentSet_004ebd08");
extern char grim_def_s_MakeCurrentSetup_004ebce0[] __asm__("_s_MakeCurrentSetup_004ebce0");
extern char grim_def_s_MakeSectorActive_004ebb3c[] __asm__("_s_MakeSectorActive_004ebb3c");
extern char grim_def_s_MarkDirtyRect_004eb470[] __asm__("_s_MarkDirtyRect_004eb470");
extern char grim_def_s_NONE_004ec544[8] __asm__("_s_NONE_004ec544");
extern char grim_def_s_NewObjectState_004eb518[] __asm__("_s_NewObjectState_004eb518");
extern char grim_def_s_NextSetup_004ebcc4[] __asm__("_s_NextSetup_004ebcc4");
extern char grim_def_s_PauseMovie_004ebc5c[] __asm__("_s_PauseMovie_004ebc5c");
extern char grim_def_s_PerSecond_004eb9bc[] __asm__("_s_PerSecond_004eb9bc");
extern char grim_def_s_PlayActorChoreLooping_004ebec0[] __asm__("_s_PlayActorChoreLooping_004ebec0");
extern char grim_def_s_PlayActorChore_004ebed8[] __asm__("_s_PlayActorChore_004ebed8");
extern char grim_def_s_PlaySoundAt_004ebc34[] __asm__("_s_PlaySoundAt_004ebc34");
extern char grim_def_s_PlaySoundAttached_004ebc20[] __asm__("_s_PlaySoundAttached_004ebc20");
extern char grim_def_s_PlaySound_004ebc40[] __asm__("_s_PlaySound_004ebc40");
extern char grim_def_s_PointActorAt_004eb9d4[] __asm__("_s_PointActorAt_004eb9d4");
extern char grim_def_s_PointLightAt_004eb884[] __asm__("_s_PointLightAt_004eb884");
extern char grim_def_s_PopActorCostume_004ebac8[] __asm__("_s_PopActorCostume_004ebac8");
extern char grim_def_s_PreRender_004ebb30[] __asm__("_s_PreRender_004ebb30");
extern char grim_def_s_PreviousSetup_004ebcb4[] __asm__("_s_PreviousSetup_004ebcb4");
extern char grim_def_s_PrintActorCostumes_004ebaec[] __asm__("_s_PrintActorCostumes_004ebaec");
extern char grim_def_s_PrintDebug_004ebd18[] __asm__("_s_PrintDebug_004ebd18");
extern char grim_def_s_PrintError_004ebd34[] __asm__("_s_PrintError_004ebd34");
extern char grim_def_s_PrintMessage_004ebd40[] __asm__("_s_PrintMessage_004ebd40");
extern char grim_def_s_PrintWarning_004ebd24[] __asm__("_s_PrintWarning_004ebd24");
extern char grim_def_s_PushActorCostume_004ebad8[] __asm__("_s_PushActorCostume_004ebad8");
extern char grim_def_s_PutActorAtInterest_004ec0f4[] __asm__("_s_PutActorAtInterest_004ec0f4");
extern char grim_def_s_PutActorAtOrigin_004ec0e0[] __asm__("_s_PutActorAtOrigin_004ec0e0");
extern char grim_def_s_PutActorAt_004ec0d4[] __asm__("_s_PutActorAt_004ec0d4");
extern char grim_def_s_PutActorInSet_004ec0c4[] __asm__("_s_PutActorInSet_004ec0c4");
extern char grim_def_s_QueryDialog_004ebbb4[] __asm__("_s_QueryDialog_004ebbb4");
extern char grim_def_s_ReadRegistryValue_004ebb8c[] __asm__("_s_ReadRegistryValue_004ebb8c");
extern char grim_def_s_RenderModeUser_004eb63c[] __asm__("_s_RenderModeUser_004eb63c");
extern char grim_def_s_ResReport_004eb444[] __asm__("_s_ResReport_004eb444");
extern char grim_def_s_RestoreCacheRect_004eb450[] __asm__("_s_RestoreCacheRect_004eb450");
extern char grim_def_s_RotateVector_004eba88[] __asm__("_s_RotateVector_004eba88");
extern char grim_def_s_SPECIAL_004ec52c[8] __asm__("_s_SPECIAL_004ec52c");
extern char grim_def_s_ScreenToWorld_004ebdf4[] __asm__("_s_ScreenToWorld_004ebdf4");
extern char grim_def_s_SearchForFileOrSwapCDs_004ec2fc[] __asm__("_s_SearchForFileOrSwapCDs_004ec2fc");
extern char grim_def_s_SendObjectToBack_004eb4e4[] __asm__("_s_SendObjectToBack_004eb4e4");
extern char grim_def_s_SendObjectToFront_004eb4d0[] __asm__("_s_SendObjectToFront_004eb4d0");
extern char grim_def_s_SetActiveShadow_004eb578[] __asm__("_s_SetActiveShadow_004eb578");
extern char grim_def_s_SetActorChoreLooping_004ebe54[] __asm__("_s_SetActorChoreLooping_004ebe54");
extern char grim_def_s_SetActorClipActive_004eb41c[] __asm__("_s_SetActorClipActive_004eb41c");
extern char grim_def_s_SetActorClipPlane_004eb408[] __asm__("_s_SetActorClipPlane_004eb408");
extern char grim_def_s_SetActorCollisionMode_004eb498[] __asm__("_s_SetActorCollisionMode_004eb498");
extern char grim_def_s_SetActorCollisionScale_004eb480[] __asm__("_s_SetActorCollisionScale_004eb480");
extern char grim_def_s_SetActorColormap_004ec2c8[] __asm__("_s_SetActorColormap_004ec2c8");
extern char grim_def_s_SetActorConstrain_004eb64c[] __asm__("_s_SetActorConstrain_004eb64c");
extern char grim_def_s_SetActorCostume_004ec2a8[] __asm__("_s_SetActorCostume_004ec2a8");
extern char grim_def_s_SetActorFollowBoxes_004ebfa0[] __asm__("_s_SetActorFollowBoxes_004ebfa0");
extern char grim_def_s_SetActorFrustrumCull_004ebf7c[] __asm__("_s_SetActorFrustrumCull_004ebf7c");
extern char grim_def_s_SetActorHead_004ebfc8[] __asm__("_s_SetActorHead_004ebfc8");
extern char grim_def_s_SetActorLookRate_004ec01c[] __asm__("_s_SetActorLookRate_004ec01c");
extern char grim_def_s_SetActorMumblechore_004ec1f8[] __asm__("_s_SetActorMumblechore_004ec1f8");
extern char grim_def_s_SetActorOffsetYaw_004ec108[] __asm__("_s_SetActorOffsetYaw_004ec108");
extern char grim_def_s_SetActorPitch_004ebf08[] __asm__("_s_SetActorPitch_004ebf08");
extern char grim_def_s_SetActorReflection_004ec11c[] __asm__("_s_SetActorReflection_004ec11c");
extern char grim_def_s_SetActorRestChore_004ec20c[] __asm__("_s_SetActorRestChore_004ec20c");
extern char grim_def_s_SetActorRoll_004ebef8[] __asm__("_s_SetActorRoll_004ebef8");
extern char grim_def_s_SetActorRot_004ebf18[] __asm__("_s_SetActorRot_004ebf18");
extern char grim_def_s_SetActorScale_004ec288[] __asm__("_s_SetActorScale_004ec288");
extern char grim_def_s_SetActorShadowPlane_004eb59c[] __asm__("_s_SetActorShadowPlane_004eb59c");
extern char grim_def_s_SetActorShadowPoint_004eb588[] __asm__("_s_SetActorShadowPoint_004eb588");
extern char grim_def_s_SetActorShadowValid_004eb528[] __asm__("_s_SetActorShadowValid_004eb528");
extern char grim_def_s_SetActorTalkChore_004ec1e4[] __asm__("_s_SetActorTalkChore_004ec1e4");
extern char grim_def_s_SetActorTimeScale_004ec260[] __asm__("_s_SetActorTimeScale_004ec260");
extern char grim_def_s_SetActorTurnChores_004ec220[] __asm__("_s_SetActorTurnChores_004ec220");
extern char grim_def_s_SetActorTurnRate_004ec1a8[] __asm__("_s_SetActorTurnRate_004ec1a8");
extern char grim_def_s_SetActorVisibility_004ebfb4[] __asm__("_s_SetActorVisibility_004ebfb4");
extern char grim_def_s_SetActorWalkChore_004ec234[] __asm__("_s_SetActorWalkChore_004ec234");
extern char grim_def_s_SetActorWalkDominate_004eb660[] __asm__("_s_SetActorWalkDominate_004eb660");
extern char grim_def_s_SetActorWalkRate_004ec1d0[] __asm__("_s_SetActorWalkRate_004ec1d0");
extern char grim_def_s_SetAmbientLight_004eb970[] __asm__("_s_SetAmbientLight_004eb970");
extern char grim_def_s_SetCameraFOV_004eba18[] __asm__("_s_SetCameraFOV_004eba18");
extern char grim_def_s_SetCameraInterest_004eba38[] __asm__("_s_SetCameraInterest_004eba38");
extern char grim_def_s_SetCameraPosition_004eba60[] __asm__("_s_SetCameraPosition_004eba60");
extern char grim_def_s_SetCameraRoll_004eb9f8[] __asm__("_s_SetCameraRoll_004eb9f8");
extern char grim_def_s_SetGamma_004eb678[] __asm__("_s_SetGamma_004eb678");
extern char grim_def_s_SetLightAngles_004eb8cc[] __asm__("_s_SetLightAngles_004eb8cc");
extern char grim_def_s_SetLightIntensity_004eb8a8[] __asm__("_s_SetLightIntensity_004eb8a8");
extern char grim_def_s_SetLightPosition_004eb918[] __asm__("_s_SetLightPosition_004eb918");
extern char grim_def_s_SetLightRotation_004eb8f0[] __asm__("_s_SetLightRotation_004eb8f0");
extern char grim_def_s_SetLightType_004eb93c[] __asm__("_s_SetLightType_004eb93c");
extern char grim_def_s_SetMemoryUsage_004eba98[] __asm__("_s_SetMemoryUsage_004eba98");
extern char grim_def_s_SetObjectType_004eb4f8[] __asm__("_s_SetObjectType_004eb4f8");
extern char grim_def_s_SetSelectedActor_004ec180[] __asm__("_s_SetSelectedActor_004ec180");
extern char grim_def_s_SetShadowColor_004eb5d0[] __asm__("_s_SetShadowColor_004eb5d0");
extern char grim_def_s_SetSoundPosition_004ebbfc[] __asm__("_s_SetSoundPosition_004ebbfc");
extern char grim_def_s_SetSpeechMode_004eb5f0[] __asm__("_s_SetSpeechMode_004eb5f0");
extern char grim_def_s_ShutUpActor_004ebf94[] __asm__("_s_ShutUpActor_004ebf94");
extern char grim_def_s_SnapToPlane_004eb9b0[] __asm__("_s_SnapToPlane_004eb9b0");
extern char grim_def_s_SpewShutdown_004ebb14[] __asm__("_s_SpewShutdown_004ebb14");
extern char grim_def_s_SpewStartup_004ebb24[] __asm__("_s_SpewStartup_004ebb24");
extern char grim_def_s_StartFullscreenMovie_004ebc9c[] __asm__("_s_StartFullscreenMovie_004ebc9c");
extern char grim_def_s_StartMovie_004ebc74[] __asm__("_s_StartMovie_004ebc74");
extern char grim_def_s_StopActorChore_004ebeb0[] __asm__("_s_StopActorChore_004ebeb0");
extern char grim_def_s_StopMovie_004ebc68[] __asm__("_s_StopMovie_004ebc68");
extern char grim_def_s_TextAllowed_004ec55c[12] __asm__("_s_TextAllowed_004ec55c");
extern char grim_def_s_TurnActorTo_004eb9c8[] __asm__("_s_TurnActorTo_004eb9c8");
extern char grim_def_s_TurnActor_004ebf30[] __asm__("_s_TurnActor_004ebf30");
extern char grim_def_s_TurnLightOn_004eb958[] __asm__("_s_TurnLightOn_004eb958");
extern char grim_def_s_UnLockFont_004ebdb4[] __asm__("_s_UnLockFont_004ebdb4");
extern char grim_def_s_UnLockSet_004ebcf4[] __asm__("_s_UnLockSet_004ebcf4");
extern char grim_def_s_UnloadBundle_004eb684[] __asm__("_s_UnloadBundle_004eb684");
extern char grim_def_s_UnlockCostume_004ebd80[] __asm__("_s_UnlockCostume_004ebd80");
extern char grim_def_s_UnlockSound_004ebd9c[] __asm__("_s_UnlockSound_004ebd9c");
extern char grim_def_s_WALK_004ec53c[8] __asm__("_s_WALK_004ec53c");
extern char grim_def_s_WalkActorForward_004ec090[] __asm__("_s_WalkActorForward_004ec090");
extern char grim_def_s_WalkActorToAvoiding_004ec060[] __asm__("_s_WalkActorToAvoiding_004ec060");
extern char grim_def_s_WalkActorToInterest_004ec04c[] __asm__("_s_WalkActorToInterest_004ec04c");
extern char grim_def_s_WalkActorTo_004ec074[] __asm__("_s_WalkActorTo_004ec074");
extern char grim_def_s_WalkActorVector_004ec0a4[] __asm__("_s_WalkActorVector_004ec0a4");
extern char grim_def_s_WorldToScreen_004ebe04[] __asm__("_s_WorldToScreen_004ebe04");
extern char grim_def_s_WriteRegistryValue_004ebba0[] __asm__("_s_WriteRegistryValue_004ebba0");
extern char grim_def_s___s__s_004e8754[8] __asm__("_s___s__s_004e8754");
extern char grim_def_s__actor_d__s__004ec494[16] __asm__("_s__actor_d__s__004ec494");
extern char grim_def_s__engn003_Software_004dd688[20] __asm__("_s__engn003_Software_004dd688");
extern char grim_def_s__nil__004ec4a4[8] __asm__("_s__nil__004ec4a4");
extern char grim_def_s__system_lua_004ec3bc[12] __asm__("_s__system_lua_004ec3bc");
extern char grim_def_s_axisHandler_004ec568[12] __asm__("_s_axisHandler_004ec568");
extern char grim_def_s_buttonHandler_004ec574[16] __asm__("_s_buttonHandler_004ec574");
extern char grim_def_s_camChangeHandler_004ec3d0[20] __asm__("_s_camChangeHandler_004ec3d0");
extern char grim_def_s_characterHandler_004ec50c[20] __asm__("_s_characterHandler_004ec50c");
extern char grim_def_s_color_004e8468[8] __asm__("_s_color_004e8468");
extern char grim_def_s_concat_004ec520[8] __asm__("_s_concat_004ec520");
extern char grim_def_s_concatfallback_004ec370[] __asm__("_s_concatfallback_004ec370");
extern char grim_def_s_controls_004ec58c[12] __asm__("_s_controls_004ec58c");
extern char grim_def_s_costumeMarkerHandler_004ec4c4[24] __asm__("_s_costumeMarkerHandler_004ec4c4");
extern char grim_def_s_costumeOverrideHandler_004ec4ac[24] __asm__("_s_costumeOverrideHandler_004ec4ac");
extern char grim_def_s_count_004ec384[8] __asm__("_s_count_004ec384");
extern char grim_def_s_dfltcamera_004ec350[] __asm__("_s_dfltcamera_004ec350");
extern char grim_def_s_dfltcontrol_004ec340[] __asm__("_s_dfltcontrol_004ec340");
extern char grim_def_s_exitHandler_004ec4f0[12] __asm__("_s_exitHandler_004ec4f0");
extern char grim_def_s_filled_004e8430[8] __asm__("_s_filled_004e8430");
extern char grim_def_s_global_004ec5a0[8] __asm__("_s_global_004ec5a0");
extern char grim_def_s_height_004e8438[] __asm__("_s_height_004e8438");
extern char grim_def_s_layer_004e8428[] __asm__("_s_layer_004e8428");
extern char grim_def_s_parallel_004ec5a8[12] __asm__("_s_parallel_004ec5a8");
extern char grim_def_s_pauseHandler_004ec4fc[16] __asm__("_s_pauseHandler_004ec4fc");
extern char grim_def_s_postCamChangeHandler_004ec3e4[24] __asm__("_s_postCamChangeHandler_004ec3e4");
extern char grim_def_s_quiet_004eb7ec[] __asm__("_s_quiet_004eb7ec");
extern char grim_def_s_saveGameCallback_004ec5c0[20] __asm__("_s_saveGameCallback_004ec5c0");
extern char grim_def_s_system_004ec584[8] __asm__("_s_system_004ec584");
extern char grim_def_s_true_004ec554[8] __asm__("_s_true_004ec554");
extern char grim_def_s_type_004ec54c[8] __asm__("_s_type_004ec54c");
extern char grim_def_s_typeoverride_004ec360[] __asm__("_s_typeoverride_004ec360");
extern char grim_def_s_userPaintHandler_004ec4dc[20] __asm__("_s_userPaintHandler_004ec4dc");
extern char grim_def_s_width_004e8440[] __asm__("_s_width_004e8440");
extern char grim_def_s_x_004e8454[] __asm__("_s_x_004e8454");
extern char grim_def_s_x_spot_cos_004f0d28[12] __asm__("_s_x_spot_cos_004f0d28");
extern char grim_def_s_xoffset_004e8460[] __asm__("_s_xoffset_004e8460");
extern char grim_def_s_y_004e8450[] __asm__("_s_y_004e8450");
extern char grim_def_s_yoffset_004e8458[] __asm__("_s_yoffset_004e8458");
/* 0x004dd688, 20 bytes */ /* loose */ char grim_def_s__engn003_Software_004dd688[20] __asm__("_s__engn003_Software_004dd688") = "/engn003/Software";
/* 0x004ddab4, 4 bytes */ GRIM_DATA("004ddab4") unsigned int grim_def_UINT_004ddab4 __asm__("_UINT_004ddab4") = 0xb;
/* 0x004ddab8, 4 bytes */ GRIM_DATA("004ddab8") unsigned int grim_def_UINT_004ddab8 __asm__("_UINT_004ddab8") = 0x5;
/* 0x004ddabc, 4 bytes */ GRIM_DATA("004ddabc") unsigned int grim_def_UINT_004ddabc __asm__("_UINT_004ddabc") = 0x0;
/* 0x004ddac0, 4 bytes */ GRIM_DATA("004ddac0") unsigned int grim_def_UINT_004ddac0 __asm__("_UINT_004ddac0") = 0x3;
/* 0x004ddac4, 4 bytes */ GRIM_DATA("004ddac4") unsigned int grim_def_UINT_004ddac4 __asm__("_UINT_004ddac4") = 0x2;
/* 0x004ddac8, 16 bytes */ GRIM_DATA("004ddac8") unsigned char grim_def_UINT_004ddac8[16] __asm__("_UINT_004ddac8") = { 0x03 };
/* 0x004e8368, 4 bytes */ /* loose */ void *grim_def_PTR_s_color_004e8368 __asm__("_PTR_s_color_004e8368") = (void *)&grim_def_s_color_004e8468;
/* 0x004e836c, 4 bytes */ /* loose */ void *grim_def_PTR_s_xoffset_004e836c __asm__("_PTR_s_xoffset_004e836c") = (void *)&grim_def_s_xoffset_004e8460;
/* 0x004e8370, 4 bytes */ /* loose */ void *grim_def_PTR_s_yoffset_004e8370 __asm__("_PTR_s_yoffset_004e8370") = (void *)&grim_def_s_yoffset_004e8458;
/* 0x004e8374, 4 bytes */ /* loose */ void *grim_def_PTR_s_x_004e8374 __asm__("_PTR_s_x_004e8374") = (void *)&grim_def_s_x_004e8454;
/* 0x004e8378, 4 bytes */ /* loose */ void *grim_def_PTR_s_y_004e8378 __asm__("_PTR_s_y_004e8378") = (void *)&grim_def_s_y_004e8450;
/* 0x004e837c, 4 bytes */ /* loose */ void *grim_def_PTR_DAT_004e837c __asm__("_PTR_DAT_004e837c") = (void *)&grim_def_DAT_004e844c;
/* 0x004e8380, 4 bytes */ /* loose */ void *grim_def_PTR_DAT_004e8380 __asm__("_PTR_DAT_004e8380") = (void *)&grim_def_DAT_004e8448;
/* 0x004e8384, 4 bytes */ /* loose */ void *grim_def_PTR_s_width_004e8384 __asm__("_PTR_s_width_004e8384") = (void *)&grim_def_s_width_004e8440;
/* 0x004e8388, 4 bytes */ /* loose */ void *grim_def_PTR_s_height_004e8388 __asm__("_PTR_s_height_004e8388") = (void *)&grim_def_s_height_004e8438;
/* 0x004e838c, 4 bytes */ /* loose */ void *grim_def_PTR_s_filled_004e838c __asm__("_PTR_s_filled_004e838c") = (void *)&grim_def_s_filled_004e8430;
/* 0x004e8390, 4 bytes */ /* loose */ void *grim_def_PTR_s_layer_004e8390 __asm__("_PTR_s_layer_004e8390") = (void *)&grim_def_s_layer_004e8428;
/* 0x004e8430, 8 bytes */ /* loose */ char grim_def_s_filled_004e8430[8] __asm__("_s_filled_004e8430") = "filled";
/* 0x004e8468, 8 bytes */ /* loose */ char grim_def_s_color_004e8468[8] __asm__("_s_color_004e8468") = "color";
/* 0x004e8470, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004e8470 __asm__("_UINT_004e8470") = 0x28;
static unsigned char grim_anchor_004e8474[0] __attribute__((section(".data$grim_004e8474"), aligned(16), used));
static unsigned char grim_pad_004e8474[4] __attribute__((section(".data$grim_004e8474_"), aligned(4), used));
/* 0x004e8474, 4 bytes */ GRIM_DATA("004e8474z") unsigned int grim_def_UINT_004e8474 __asm__("_UINT_004e8474") = 0x3;
/* 0x004e8480, 4 bytes */ GRIM_DATA("004e8480") unsigned int grim_def_UINT_004e8480 __asm__("_UINT_004e8480") = 0x280;
/* 0x004e8484, 4 bytes */ GRIM_DATA("004e8484") unsigned int grim_def_UINT_004e8484 __asm__("_UINT_004e8484") = 0x1e0;
/* 0x004e8754, 8 bytes */ /* loose */ char grim_def_s___s__s_004e8754[8] __asm__("_s___s__s_004e8754") = "/%s/%s";
static unsigned char grim_anchor_004ea890[0] __attribute__((section(".data$grim_004ea890"), aligned(16), used));
static unsigned char grim_pad_004ea890[0] __attribute__((section(".data$grim_004ea890_"), aligned(4), used));
/* 0x004ea890, 32 bytes */ GRIM_DATA("004ea890z") void *grim_def_PTR_s_concatfallback_004ea890[8] __asm__("_PTR_s_concatfallback_004ea890") = {
    (void *)&grim_def_s_concatfallback_004ec370, (void *)f_sputLua_ConcatFallback, (void *)&grim_def_s_typeoverride_004ec360, (void *)f_sputLua_TypeOverride,
    (void *)&grim_def_s_dfltcamera_004ec350, (void *)f_Lua_Stub, (void *)&grim_def_s_dfltcontrol_004ec340, (void *)f_Lua_Stub
};
/* 0x004ea8b0, 2232 bytes */ GRIM_DATA("004ea8b0") void *grim_def_PTR_s_EnginePause_004ea8b0[558] __asm__("_PTR_s_EnginePause_004ea8b0") = {
    (void *)&grim_def_s_EnginePause_004ec334, (void *)f_sputLua_EnginePause, (void *)&grim_def_s_EngineResume_004ec324, (void *)f_sputLua_EngineResume,
    (void *)&grim_def_s_EngineDisplay_004ec314, (void *)f_sputLua_EngineDisplay, (void *)&grim_def_s_SearchForFileOrSwapCDs_004ec2fc, (void *)f_sputLua_SearchForFileOrSwapCDsL,
    (void *)&grim_def_s_CheckForFile_004ec2ec, (void *)f_sputLua_CheckForFileL, (void *)&grim_def_DAT_004ec2e4, (void *)f_sputLua_LoadL,
    (void *)&grim_def_DAT_004ec2dc, (void *)f_sputLua_SaveL, (void *)&grim_def_s_SetActorColormap_004ec2c8, (void *)f_sputLua_SetActorColormapL,
    (void *)&grim_def_s_GetActorCostume_004ec2b8, (void *)f_sputLua_GetActorCostumeL, (void *)&grim_def_s_SetActorCostume_004ec2a8, (void *)f_sputLua_SetActorCostumeL,
    (void *)&grim_def_s_GetActorScale_004ec298, (void *)f_sputLua_GetActorScaleL, (void *)&grim_def_s_SetActorScale_004ec288, (void *)f_sputLua_SetActorScaleL,
    (void *)&grim_def_s_GetActorTimeScale_004ec274, (void *)f_sputLua_GetActorTimeScaleL, (void *)&grim_def_s_SetActorTimeScale_004ec260, (void *)f_sputLua_SetActorTimeScaleL,
    (void *)&grim_def_s_GetActorNodeLocation_004ec248, (void *)f_sputLua_GetActorNodeLocationL, (void *)&grim_def_s_SetActorWalkChore_004ec234, (void *)f_sputLua_SetActorWalkChoresL,
    (void *)&grim_def_s_SetActorTurnChores_004ec220, (void *)f_sputLua_SetActorTurnChoresL, (void *)&grim_def_s_SetActorRestChore_004ec20c, (void *)f_sputLua_SetActorRestChoreL,
    (void *)&grim_def_s_SetActorMumblechore_004ec1f8, (void *)f_sputLua_SetActorMumbleChoreL, (void *)&grim_def_s_SetActorTalkChore_004ec1e4, (void *)f_sputLua_SetActorTalkChoreL,
    (void *)&grim_def_s_SetActorWalkRate_004ec1d0, (void *)f_sputLua_SetActorWalkRateL, (void *)&grim_def_s_GetActorWalkRate_004ec1bc, (void *)f_sputLua_GetActorWalkRateL,
    (void *)&grim_def_s_SetActorTurnRate_004ec1a8, (void *)f_sputLua_SetActorTurnRateL, (void *)&grim_def_s_GetActorTurnRate_004ec194, (void *)f_sputLua_GetActorTurnRateL,
    (void *)&grim_def_s_SetSelectedActor_004ec180, (void *)f_sputLua_SetSelectedActorL, (void *)&grim_def_s_LoadActor_004ec174, (void *)f_sputLua_AllocateActorL,
    (void *)&grim_def_s_GetActorPos_004ec168, (void *)f_sputLua_GetActorPosL, (void *)&grim_def_s_GetActorRect_004ec158, (void *)f_sputLua_GetActorRectL,
    (void *)&grim_def_s_GetActorPuckVector_004ec144, (void *)f_sputLua_GetActorPuckVectorL, (void *)&grim_def_s_GetActorYawToPoint_004ec130, (void *)f_sputLua_GetActorYawToPoint,
    (void *)&grim_def_s_SetActorReflection_004ec11c, (void *)f_sputLua_SetActorReflection, (void *)&grim_def_s_SetActorOffsetYaw_004ec108, (void *)f_sputLua_SetActorOffsetYaw,
    (void *)&grim_def_s_PutActorAtInterest_004ec0f4, (void *)f_sputLua_PutActorAtInterestL, (void *)&grim_def_s_PutActorAtOrigin_004ec0e0, (void *)f_Lua_Stub,
    (void *)&grim_def_s_PutActorAt_004ec0d4, (void *)f_sputLua_PutActorAtL, (void *)&grim_def_s_PutActorInSet_004ec0c4, (void *)f_sputLua_PutActorInSetL,
    (void *)&grim_def_s_GetClippedPos_004ec0b4, (void *)f_Lua_Stub, (void *)&grim_def_s_WalkActorVector_004ec0a4, (void *)f_sputLua_WalkActorVectorL,
    (void *)&grim_def_s_WalkActorForward_004ec090, (void *)f_sputLua_WalkActorForwardL, (void *)&grim_def_s_DriveActorTo_004ec080, (void *)f_Lua_Stub,
    (void *)&grim_def_s_WalkActorTo_004ec074, (void *)f_sputLua_WalkActorToL, (void *)&grim_def_s_WalkActorToAvoiding_004ec060, (void *)f_sputLua_WalkActorToAvoidingL,
    (void *)&grim_def_s_WalkActorToInterest_004ec04c, (void *)f_Lua_Stub, (void *)&grim_def_s_ActorLookAt_004ec040, (void *)f_sputLua_ActorLookAtL,
    (void *)&grim_def_s_IsActorLooking_004ec030, (void *)f_sputLua_IsActorLookingL, (void *)&grim_def_s_SetActorLookRate_004ec01c, (void *)f_sputLua_SetActorLookRate,
    (void *)&grim_def_s_GetActorLookRate_004ec008, (void *)f_sputLua_GetActorLookRate, (void *)&grim_def_s_CanActorSee_004ebffc, (void *)f_sputLua_CanActorSeeL,
    (void *)&grim_def_s_GetVisibleThings_004ebfe8, (void *)f_sputLua_GetVisibleThingsL, (void *)&grim_def_s_GetCameraActor_004ebfd8, (void *)f_sputLua_GetCameraActorL,
    (void *)&grim_def_s_SetActorHead_004ebfc8, (void *)f_sputLua_SetActorHeadL, (void *)&grim_def_s_SetActorVisibility_004ebfb4, (void *)f_sputLua_SetActorVisibilityL,
    (void *)&grim_def_s_SetActorFollowBoxes_004ebfa0, (void *)f_sputLua_SetActorFollowBoxesL, (void *)&grim_def_s_ShutUpActor_004ebf94, (void *)f_sputLua_ShutUpActorL,
    (void *)&grim_def_s_SetActorFrustrumCull_004ebf7c, (void *)f_sputLua_SetActorFrustrumCull, (void *)&grim_def_s_IsActorInSector_004ebf6c, (void *)f_sputLua_IsActorInSector,
    (void *)&grim_def_s_GetActorSector_004ebf5c, (void *)f_sputLua_GetActorSectorL, (void *)&grim_def_s_IsPointInSector_004ebf4c, (void *)f_sputLua_IsPointInSector,
    (void *)&grim_def_s_GetPointSector_004ebf3c, (void *)f_sputLua_GetPointSectorL, (void *)&grim_def_s_TurnActor_004ebf30, (void *)f_sputLua_TurnActorL,
    (void *)&grim_def_s_GetActorRot_004ebf24, (void *)f_sputLua_GetActorRotL, (void *)&grim_def_s_SetActorRot_004ebf18, (void *)f_sputLua_SetActorRotL,
    (void *)&grim_def_s_SetActorPitch_004ebf08, (void *)f_sputLua_SetActorPitch, (void *)&grim_def_s_SetActorRoll_004ebef8, (void *)f_sputLua_SetActorRoll,
    (void *)&grim_def_s_IsActorTurning_004ebee8, (void *)f_sputLua_IsActorTurningL, (void *)&grim_def_s_PlayActorChore_004ebed8, (void *)f_sputLua_PlayActorChoreL,
    (void *)&grim_def_s_PlayActorChoreLooping_004ebec0, (void *)f_sputLua_PlayActorChoreLoopingL, (void *)&grim_def_s_StopActorChore_004ebeb0, (void *)f_sputLua_StopActorChoreL,
    (void *)&grim_def_s_CompleteActorChore_004ebe9c, (void *)f_sputLua_CompleteActorChoreL, (void *)&grim_def_s_IsActorMoving_004ebe8c, (void *)f_sputLua_IsActorMovingL,
    (void *)&grim_def_s_IsActorChoring_004ebe7c, (void *)f_sputLua_IsActorChoringL, (void *)&grim_def_s_IsActorResting_004ebe6c, (void *)f_sputLua_IsActorRestingL,
    (void *)&grim_def_s_SetActorChoreLooping_004ebe54, (void *)f_sputLua_SetActorChoreLoopingL, (void *)&grim_def_s_GetActorChores_004ebe44, (void *)f_sputLua_GetActorChoresL,
    (void *)&grim_def_s_GetActorLoopingChores_004ebe2c, (void *)f_sputLua_GetActorLoopingChoresL, (void *)&grim_def_s_GetActorCostumeDepth_004ebe14, (void *)f_sputLua_GetActorCostumeDepthL,
    (void *)&grim_def_s_WorldToScreen_004ebe04, (void *)f_sputLua_WorldToScreenL, (void *)&grim_def_s_ScreenToWorld_004ebdf4, (void *)f_sputLua_ScreenToWorldL,
    (void *)&grim_def_DAT_004ebdec, (void *)f_sputLua_ExitL, (void *)&grim_def_s_FunctionName_004ebddc, (void *)f_sputLua_FunctionNameL,
    (void *)&grim_def_s_EnableDebugKeys_004ebdcc, (void *)f_sputLua_EnableDebugKeysL, (void *)&grim_def_s_LockFont_004ebdc0, (void *)f_sputLua_LockFontL,
    (void *)&grim_def_s_UnLockFont_004ebdb4, (void *)f_Lua_Stub, (void *)&grim_def_s_LockSound_004ebda8, (void *)f_Lua_Stub,
    (void *)&grim_def_s_UnlockSound_004ebd9c, (void *)f_Lua_Stub, (void *)&grim_def_s_LockCostume_004ebd90, (void *)f_Lua_Stub,
    (void *)&grim_def_s_UnlockCostume_004ebd80, (void *)f_Lua_Stub, (void *)&grim_def_s_EnableControl_004ebd70, (void *)f_sputLua_EnableControlL,
    (void *)&grim_def_s_DisableControl_004ebd60, (void *)f_sputLua_DisableControlL, (void *)&grim_def_s_GetControlState_004ebd50, (void *)f_sputLua_GetControlStateL,
    (void *)&grim_def_s_PrintMessage_004ebd40, (void *)f_sputLua_MessagePrintL, (void *)&grim_def_s_PrintError_004ebd34, (void *)f_Lua_Print_NoOp,
    (void *)&grim_def_s_PrintWarning_004ebd24, (void *)f_Lua_Print_NoOp, (void *)&grim_def_s_PrintDebug_004ebd18, (void *)f_Lua_Print_NoOp,
    (void *)&grim_def_s_MakeCurrentSet_004ebd08, (void *)f_sputLua_MakeCurrentSetL, (void *)&grim_def_s_LockSet_004ebd00, (void *)f_sputLua_LockSet,
    (void *)&grim_def_s_UnLockSet_004ebcf4, (void *)f_sputLua_UnLockSet, (void *)&grim_def_s_MakeCurrentSetup_004ebce0, (void *)f_sputLua_MakeCurrentSetupL,
    (void *)&grim_def_s_GetCurrentSetup_004ebcd0, (void *)f_sputLua_GetCurrentSetupL, (void *)&grim_def_s_NextSetup_004ebcc4, (void *)f_grimlib_NextSetup,
    (void *)&grim_def_s_PreviousSetup_004ebcb4, (void *)f_grimlib_PreviousSetup, (void *)&grim_def_s_StartFullscreenMovie_004ebc9c, (void *)f_sputLua_StartFullScreenMovieL,
    (void *)&grim_def_s_IsFullscreenMoviePlaying_004ebc80, (void *)f_sputLua_IsMoviePlayingL, (void *)&grim_def_s_StartMovie_004ebc74, (void *)f_sputLua_StartMovieL,
    (void *)&grim_def_s_StopMovie_004ebc68, (void *)f_sputLua_StopMovieL, (void *)&grim_def_s_PauseMovie_004ebc5c, (void *)f_sputLua_PauseMovieL,
    (void *)&grim_def_s_IsMoviePlaying_004ebc4c, (void *)f_sputLua_IsMoviePlayingL, (void *)&grim_def_s_PlaySound_004ebc40, (void *)f_Lua_Stub,
    (void *)&grim_def_s_PlaySoundAt_004ebc34, (void *)f_Lua_Stub, (void *)&grim_def_s_PlaySoundAttached_004ebc20, (void *)f_Lua_Stub,
    (void *)&grim_def_s_IsSoundPlaying_004ebc10, (void *)f_Lua_Stub, (void *)&grim_def_s_SetSoundPosition_004ebbfc, (void *)f_sputLua_SetSoundPosition,
    (void *)&grim_def_s_FileFindFirst_004ebbec, (void *)f_sputLua_FileFindFirst, (void *)&grim_def_s_FileFindNext_004ebbdc, (void *)f_sputLua_FileFindNext,
    (void *)&grim_def_s_FileFindDispose_004ebbcc, (void *)f_sputLua_FileFindDispose, (void *)&grim_def_s_InputDialog_004ebbc0, (void *)f_sputLua_InputDialog,
    (void *)&grim_def_s_QueryDialog_004ebbb4, (void *)f_sputLua_QueryDialog, (void *)&grim_def_s_WriteRegistryValue_004ebba0, (void *)f_sputLua_WriteRegistryValue,
    (void *)&grim_def_s_ReadRegistryValue_004ebb8c, (void *)f_sputLua_ReadRegistryValue, (void *)&grim_def_s_GetSectorVertices_004ebb78, (void *)f_Lua_Stub,
    (void *)&grim_def_s_GetSectorOppositeEdge_004ebb60, (void *)f_sputLua_GetSectorOppositeEdge, (void *)&grim_def_s_IsSectorActive_004ebb50, (void *)f_sputLua_IsSectorActiveL,
    (void *)&grim_def_s_MakeSectorActive_004ebb3c, (void *)f_sputLua_MakeSectorActiveL, (void *)&grim_def_s_PreRender_004ebb30, (void *)f_sputLua_PreRender,
    (void *)&grim_def_s_SpewStartup_004ebb24, (void *)f_sputLua_SpewStartup, (void *)&grim_def_s_SpewShutdown_004ebb14, (void *)f_sputLua_SpewShutdown,
    (void *)&grim_def_s_GetCurrentScript_004ebb00, (void *)f_sputLua_GetCurrentScript, (void *)&grim_def_s_PrintActorCostumes_004ebaec, (void *)f_sputLua_PrintActorCostumesL,
    (void *)&grim_def_s_PushActorCostume_004ebad8, (void *)f_sputLua_PushActorCostumeL, (void *)&grim_def_s_PopActorCostume_004ebac8, (void *)f_sputLua_PopActorCostumeL,
    (void *)&grim_def_s_LoadCostume_004ebabc, (void *)f_sputLua_LoadCostumeL, (void *)&grim_def_s_GetPhysicalBytes_004ebaa8, (void *)f_sputLua_GetPhysicalBytes,
    (void *)&grim_def_s_SetMemoryUsage_004eba98, (void *)f_sputLua_SetMemoryUsage, (void *)&grim_def_s_RotateVector_004eba88, (void *)f_sputLua_RotateVectorL,
    (void *)&grim_def_s_GetCameraPosition_004eba74, (void *)f_sputLua_GetCameraPositionL, (void *)&grim_def_s_SetCameraPosition_004eba60, (void *)f_sputLua_SetCameraPositionL,
    (void *)&grim_def_s_GetCameraInterest_004eba4c, (void *)f_sputLua_GetCameraInterestL, (void *)&grim_def_s_SetCameraInterest_004eba38, (void *)f_sputLua_SetCameraInterestL,
    (void *)&grim_def_s_GetCameraFOV_004eba28, (void *)f_sputLua_GetCameraFOVL, (void *)&grim_def_s_SetCameraFOV_004eba18, (void *)f_sputLua_SetCameraFOVL,
    (void *)&grim_def_s_GetCameraRoll_004eba08, (void *)f_sputLua_GetCameraRollL, (void *)&grim_def_s_SetCameraRoll_004eb9f8, (void *)f_sputLua_SetCameraRollL,
    (void *)&grim_def_s_GetCameraLookVector_004eb9e4, (void *)f_sputLua_GetCameraLookVectorL, (void *)&grim_def_s_PointActorAt_004eb9d4, (void *)f_sputLua_PointActorAtL,
    (void *)&grim_def_s_TurnActorTo_004eb9c8, (void *)f_sputLua_TurnActorTo, (void *)&grim_def_s_PerSecond_004eb9bc, (void *)f_sputLua_PerSecondL,
    (void *)&grim_def_s_SnapToPlane_004eb9b0, (void *)f_sputLua_SnapToPlane, (void *)&grim_def_s_GetAngleBetweenVectors_004eb998, (void *)f_sputLua_GetAngleBetweenVectorsL,
    (void *)&grim_def_s_GetAngleBetweenActors_004eb980, (void *)f_sputLua_GetAngleBetweenActorsL, (void *)&grim_def_s_SetAmbientLight_004eb970, (void *)f_sputLua_SetAmbientLight,
    (void *)&grim_def_s_FindLight_004eb964, (void *)f_sputLua_FindLight, (void *)&grim_def_s_TurnLightOn_004eb958, (void *)f_sputLua_TurnLightOn,
    (void *)&grim_def_s_IsLightOn_004eb94c, (void *)f_sputLua_IsLightOn, (void *)&grim_def_s_SetLightType_004eb93c, (void *)f_sputLua_SetLightType,
    (void *)&grim_def_s_GetLightType_004eb92c, (void *)f_sputLua_GetLightType, (void *)&grim_def_s_SetLightPosition_004eb918, (void *)f_sputLua_SetLightPosition,
    (void *)&grim_def_s_GetLightPosition_004eb904, (void *)f_sputLua_GetLightPosition, (void *)&grim_def_s_SetLightRotation_004eb8f0, (void *)f_sputLua_SetLightRotation,
    (void *)&grim_def_s_GetLightRotation_004eb8dc, (void *)f_sputLua_GetLightRotation, (void *)&grim_def_s_SetLightAngles_004eb8cc, (void *)f_sputLua_SetLightAngles,
    (void *)&grim_def_s_GetLightAngles_004eb8bc, (void *)f_sputLua_GetLightAngles, (void *)&grim_def_s_SetLightIntensity_004eb8a8, (void *)f_sputLua_SetLightIntensity,
    (void *)&grim_def_s_GetLightIntensity_004eb894, (void *)f_sputLua_GetLightIntensity, (void *)&grim_def_s_PointLightAt_004eb884, (void *)f_sputLua_PointLightAt,
    (void *)&grim_def_s_LightMgrStartup_004eb874, (void *)f_Lua_LightMgrStartup, (void *)&grim_def_s_LightMgrShutdown_004eb860, (void *)f_Lua_LightMgrShutdown,
    (void *)&grim_def_s_LightMgrSetChange_004eb84c, (void *)f_Lua_LightMgrSetChange, (void *)&grim_def_s_ImStartRecording_004eb838, (void *)f_sputLua_ImStartRecording,
    (void *)&grim_def_s_ImStopRecording_004eb828, (void *)f_sputLua_ImStopRecording, (void *)&grim_def_s_ImStartSound_004eb818, (void *)f_sputLua_ImStartSound,
    (void *)&grim_def_DAT_004eb810, (void *)f_sputLua_ImStartSound, (void *)&grim_def_s_ImStopSound_004eb804, (void *)f_sputLua_ImStopSound,
    (void *)&grim_def_s_ImStopAllSounds_004eb7f4, (void *)f_sputLua_ImStopAllSounds, (void *)&grim_def_s_quiet_004eb7ec, (void *)f_sputLua_ImStopAllSounds,
    (void *)&grim_def_s_ImGetParam_004eb7e0, (void *)f_sputLua_ImGetParam, (void *)&grim_def_s_ImSetParam_004eb7d4, (void *)f_sputLua_ImSetParam,
    (void *)&grim_def_s_ImFadeParam_004eb7c8, (void *)f_sputLua_ImFadeParam, (void *)&grim_def_s_ImGetMasterVol_004eb7b8, (void *)f_sputLua_ImGetMasterVol,
    (void *)&grim_def_s_ImSetMasterVol_004eb7a8, (void *)f_sputLua_ImSetMasterVol, (void *)&grim_def_s_ImGetSfxVol_004eb79c, (void *)f_sputLua_ImGetSfxVol,
    (void *)&grim_def_s_ImSetSfxVol_004eb790, (void *)f_sputLua_ImSetSfxVol, (void *)&grim_def_s_ImGetVoiceVol_004eb780, (void *)f_sputLua_ImGetVoiceVol,
    (void *)&grim_def_s_ImSetVoiceVol_004eb770, (void *)f_sputLua_ImSetVoiceVol, (void *)&grim_def_s_ImGetMusicVol_004eb760, (void *)f_sputLua_ImGetMusicVol,
    (void *)&grim_def_s_ImSetMusicVol_004eb750, (void *)f_sputLua_ImSetMusicVol, (void *)&grim_def_s_ImStartVoice_004eb740, (void *)f_sputLua_ImStartVoice,
    (void *)&grim_def_s_ImStopVoice_004eb734, (void *)f_sputLua_ImStopVoice, (void *)&grim_def_s_ImSetState_004eb728, (void *)f_sputLua_ImSetState,
    (void *)&grim_def_s_ImSetSequence_004eb718, (void *)f_sputLua_ImSetSequence, (void *)&grim_def_s_ImSetAttribute_004eb708, (void *)f_sputLua_ImSetAttribute,
    (void *)&grim_def_s_ImSetCuePoint_004eb6f8, (void *)f_sputLua_ImSetCuePoint, (void *)&grim_def_s_ImPause_004eb6f0, (void *)f_sputLua_ImPause,
    (void *)&grim_def_s_ImResume_004eb6e4, (void *)f_sputLua_ImResume, (void *)&grim_def_DAT_004eb6e0, (void *)f_sputLua_ImSetVoiceEffect,
    (void *)&grim_def_s_ImSetVoiceEffect_004eb6cc, (void *)f_sputLua_ImSetVoiceEffect, (void *)&grim_def_s_ImGetMemoryFootprint_004eb6b4, (void *)f_sputLua_ImGetMemoryFootprint,
    (void *)&grim_def_s_ImGetSoundCacheSize_004eb6a0, (void *)f_sputLua_ImGetSoundCacheSize, (void *)&grim_def_s_LoadBundle_004eb694, (void *)f_Lua_Stub,
    (void *)&grim_def_s_UnloadBundle_004eb684, (void *)f_Lua_Stub, (void *)&grim_def_s_SetGamma_004eb678, (void *)f_sputLua_SetGamma,
    (void *)&grim_def_s_SetActorWalkDominate_004eb660, (void *)f_sputLua_SetActorWalkDominate, (void *)&grim_def_s_SetActorConstrain_004eb64c, (void *)f_sputLua_SetActorConstrain,
    (void *)&grim_def_s_RenderModeUser_004eb63c, (void *)f_sputLua_RenderModeUser, (void *)&grim_def_s_ForceRefresh_004eb62c, (void *)f_sputRender_ForceRefresh,
    (void *)&grim_def_s_DimScreen_004eb620, (void *)f_sputLua_DimScreen, (void *)&grim_def_s_DimRegion_004eb614, (void *)f_sputLua_DimRegion,
    (void *)&grim_def_s_CleanBuffer_004eb608, (void *)f_sputLua_CleanBuffer, (void *)&grim_def_s_Display_004eb600, (void *)f_sputLua_Display,
    (void *)&grim_def_s_SetSpeechMode_004eb5f0, (void *)f_sputLua_SetSpeechMode, (void *)&grim_def_s_GetSpeechMode_004eb5e0, (void *)f_sputLua_GetSpeechMode,
    (void *)&grim_def_s_SetShadowColor_004eb5d0, (void *)f_sputLua_SetShadowColor, (void *)&grim_def_s_ActivateActorShadow_004eb5bc, (void *)f_sputLua_ActivateActorShadow,
    (void *)&grim_def_s_ActorShadow_004eb5b0, (void *)f_sputLua_ActorShadow, (void *)&grim_def_s_SetActorShadowPlane_004eb59c, (void *)f_sputLua_SetActorShadowPlane,
    (void *)&grim_def_s_SetActorShadowPoint_004eb588, (void *)f_sputLua_SetActorShadowPoint, (void *)&grim_def_s_SetActiveShadow_004eb578, (void *)f_sputLua_SetActiveShadow,
    (void *)&grim_def_s_ActorDistToShadowPlane_004eb560, (void *)f_sputLua_ActorDistToShadowPlane, (void *)&grim_def_s_KillActorShadows_004eb54c, (void *)f_sputLua_KillActorShadows,
    (void *)&grim_def_s_AddShadowPlane_004eb53c, (void *)f_sputLua_AddShadowClipPlane, (void *)&grim_def_s_SetActorShadowValid_004eb528, (void *)f_sputLua_SetActorShadowValid,
    (void *)&grim_def_s_NewObjectState_004eb518, (void *)f_sputLua_NewObjectState, (void *)&grim_def_s_FreeObjectState_004eb508, (void *)f_sputLua_FreeObjectState,
    (void *)&grim_def_s_SetObjectType_004eb4f8, (void *)f_sputLua_SetObjectType, (void *)&grim_def_s_SendObjectToBack_004eb4e4, (void *)f_sputLua_SendObjectToBack,
    (void *)&grim_def_s_SendObjectToFront_004eb4d0, (void *)f_sputLua_SendObjectToFront, (void *)&grim_def_s_ActorToClean_004eb4c0, (void *)f_sputLua_ActorToClean,
    (void *)&grim_def_s_FlushControls_004eb4b0, (void *)f_stdControl_Flush, (void *)&grim_def_s_SetActorCollisionMode_004eb498, (void *)f_sputLua_SetActorCollisionMode,
    (void *)&grim_def_s_SetActorCollisionScale_004eb480, (void *)f_sputLua_SetActorCollisionScale, (void *)&grim_def_s_MarkDirtyRect_004eb470, (void *)f_sputLua_MarkDirtyRect,
    (void *)&grim_def_s_CacheRect_004eb464, (void *)f_sputLua_CacheRect, (void *)&grim_def_s_RestoreCacheRect_004eb450, (void *)f_sputLua_RestoreCacheRect,
    (void *)&grim_def_s_ResReport_004eb444, (void *)f_sputLua_ResReport, (void *)&grim_def_s_HardwareAccelerated_004eb430, (void *)f_sputLua_HardwareAccelerated,
    (void *)&grim_def_s_SetActorClipActive_004eb41c, (void *)f_sputLua_SetActorClipActive, (void *)&grim_def_s_SetActorClipPlane_004eb408, (void *)f_sputLua_SetActorClipPlane,
    (void *)&grim_def_s_FadeOutChore_004eb3f8, (void *)f_sputLua_FadeOutChore, (void *)&grim_def_s_FadeInChore_004eb3ec, (void *)f_sputLua_FadeInChore,
    (void *)&grim_def_s_IrisDown_004eb3e0, (void *)f_sputLua_IrisDown, (void *)&grim_def_s_IrisUp_004eb3d8, (void *)f_sputLua_IrisUp,
    (void *)&grim_def_s_IrisComplete_004eb3c8, (void *)f_sputLua_IrisComplete, (void *)&grim_def_DAT_004eb3bc, (void *)f_sputRender_ClearIris,
    (void *)&grim_def_DAT_004eb3a4, (void *)f_Lua_TextFileGetLineCount, (void *)&grim_def_DAT_004eb394, (void *)f_Lua_TextFileGetLine,
    (void *)&grim_def_DAT_004eb388, (void *)f_sputLua_ScreenShot, (void *)&grim_def_DAT_004eb37c, (void *)f_sputLua_SaveScreen,
    (void *)&grim_def_DAT_004eb368, (void *)f_sputLua_GetSaveGameImage, (void *)&grim_def_DAT_004eb35c, (void *)f_sputLua_GetImage,
    (void *)&grim_def_DAT_004eb350, (void *)f_sputLua_FreeImage, (void *)&grim_def_DAT_004eb344, (void *)f_sputLua_BlastImage,
    (void *)&grim_def_DAT_004eb338, (void *)f_sputLua_BlastRect, (void *)&grim_def_DAT_004eb324, (void *)f_sputLua_SubmitSaveGameData,
    (void *)&grim_def_DAT_004eb314, (void *)f_sputLua_GetSaveGameData, (void *)&grim_def_DAT_004eb304, (void *)f_sputLua_SetTextSpeed,
    (void *)&grim_def_DAT_004eb2f4, (void *)f_sputLua_GetTextSpeed, (void *)&grim_def_DAT_004eb2e4, (void *)f_sputLua_FindFileOnAnyCD,
    (void *)&grim_def_DAT_004eb2d0, (void *)f_sputLua_DetachFromResourcesL, (void *)&grim_def_DAT_004eb2bc, (void *)f_sputLua_AttachToResourcesL,
    (void *)&grim_def_DAT_004eb2a8, (void *)f_sputLua_SetSoundParametersL, (void *)&grim_def_DAT_004eb294, (void *)f_sputLua_GetSoundParametersL,
    (void *)&grim_def_DAT_004eb28c, (void *)f_sputLua_Test, (void *)&grim_def_DAT_004eb27c, (void *)f_sputLua_ActorPuckOrient,
    (void *)&grim_def_DAT_004eb26c, (void *)f_sputLua_GetTickCount, (void *)&grim_def_DAT_004eb25c, (void *)f_sputLua_ActorVoiceIs3DL,
    (void *)&grim_def_DAT_004eb250, (void *)f_sputLua_JustLoadedL, (void *)&grim_def_DAT_004eb240, (void *)f_sputLua_DumpMemoryLogL,
    (void *)&grim_def_DAT_004eb230, (void *)f_sputLua_ResetTexturesL, (void *)&grim_def_DAT_004eb224, (void *)f_sputLua_BuildCache,
    (void *)&grim_def_DAT_004eb214, (void *)f_sputLua_RevertCache, (void *)&grim_def_DAT_004eb208, (void *)f_sputLua_ShrinkBoxes,
    (void *)&grim_def_DAT_004eb1f8, (void *)f_sputLua_UnShrinkBoxes, (void *)&grim_def_DAT_004eb1e8, (void *)f_sputLua_GetShrinkPosition,
    (void *)&grim_def_DAT_004eb1d8, (void *)f_sputLua_NukeResourcesL, (void *)&grim_def_DAT_004eb1c4, (void *)f_sputLua_SetActorInvClipNode,
    (void *)&grim_def_DAT_004eb1b0, (void *)f_sputLua_GetDiskFreeSpaceL, (void *)&grim_def_DAT_004eb198, (void *)f_sputLua_SetWalkSystemFadeTime,
    (void *)&grim_def_DAT_004eb18c, (void *)f_sputLua_SaveIMuse, (void *)&grim_def_DAT_004eb17c, (void *)f_sputLua_RestoreIMuse,
    (void *)&grim_def_DAT_004eb16c, (void *)f_sputLua_GetMemoryUsageL
};
/* 0x004eb168, 4 bytes */ GRIM_DATA("004eb168") unsigned int grim_def_UINT_004eb168 __asm__("_UINT_004eb168") = 0x117;
/* 0x004ec384, 8 bytes */ /* loose */ char grim_def_s_count_004ec384[8] __asm__("_s_count_004ec384") = "count";
/* 0x004ec38c, 44 bytes */ /* loose */ char grim_def_s_C__grimsrc_libs_grimlib_Scripts__004ec38c[44] __asm__("_s_C__grimsrc_libs_grimlib_Scripts__004ec38c") = "C:\\grimsrc\\libs\\grimlib\\Scripts\\sputLua.cpp";
/* 0x004ec3bc, 12 bytes */ /* loose */ char grim_def_s__system_lua_004ec3bc[12] __asm__("_s__system_lua_004ec3bc") = "_system.lua";
/* 0x004ec3c8, 8 bytes */ /* loose */ char grim_def_s_BOOT_004ec3c8[8] __asm__("_s_BOOT_004ec3c8") = "BOOT";
/* 0x004ec3d0, 20 bytes */ /* loose */ char grim_def_s_camChangeHandler_004ec3d0[20] __asm__("_s_camChangeHandler_004ec3d0") = "camChangeHandler";
/* 0x004ec3e4, 24 bytes */ /* loose */ char grim_def_s_postCamChangeHandler_004ec3e4[24] __asm__("_s_postCamChangeHandler_004ec3e4") = "postCamChangeHandler";
/* 0x004ec494, 16 bytes */ /* loose */ char grim_def_s__actor_d__s__004ec494[16] __asm__("_s__actor_d__s__004ec494") = "(actor%d:%s)";
/* 0x004ec4a4, 8 bytes */ /* loose */ char grim_def_s__nil__004ec4a4[8] __asm__("_s__nil__004ec4a4") = "(nil)";
/* 0x004ec4ac, 24 bytes */ /* loose */ char grim_def_s_costumeOverrideHandler_004ec4ac[24] __asm__("_s_costumeOverrideHandler_004ec4ac") = "costumeOverrideHandler";
/* 0x004ec4c4, 24 bytes */ /* loose */ char grim_def_s_costumeMarkerHandler_004ec4c4[24] __asm__("_s_costumeMarkerHandler_004ec4c4") = "costumeMarkerHandler";
/* 0x004ec4dc, 20 bytes */ /* loose */ char grim_def_s_userPaintHandler_004ec4dc[20] __asm__("_s_userPaintHandler_004ec4dc") = "userPaintHandler";
/* 0x004ec4f0, 12 bytes */ /* loose */ char grim_def_s_exitHandler_004ec4f0[12] __asm__("_s_exitHandler_004ec4f0") = "exitHandler";
/* 0x004ec4fc, 16 bytes */ /* loose */ char grim_def_s_pauseHandler_004ec4fc[16] __asm__("_s_pauseHandler_004ec4fc") = "pauseHandler";
/* 0x004ec50c, 20 bytes */ /* loose */ char grim_def_s_characterHandler_004ec50c[20] __asm__("_s_characterHandler_004ec50c") = "characterHandler";
/* 0x004ec520, 8 bytes */ /* loose */ char grim_def_s_concat_004ec520[8] __asm__("_s_concat_004ec520") = "concat";
/* 0x004ec528, 4 bytes */ /* loose */ char grim_def_s_HOT_004ec528[4] __asm__("_s_HOT_004ec528") = "HOT";
/* 0x004ec52c, 8 bytes */ /* loose */ char grim_def_s_SPECIAL_004ec52c[8] __asm__("_s_SPECIAL_004ec52c") = "SPECIAL";
/* 0x004ec534, 8 bytes */ /* loose */ char grim_def_s_CAMERA_004ec534[8] __asm__("_s_CAMERA_004ec534") = "CAMERA";
/* 0x004ec53c, 8 bytes */ /* loose */ char grim_def_s_WALK_004ec53c[8] __asm__("_s_WALK_004ec53c") = "WALK";
/* 0x004ec544, 8 bytes */ /* loose */ char grim_def_s_NONE_004ec544[8] __asm__("_s_NONE_004ec544") = "NONE";
/* 0x004ec54c, 8 bytes */ /* loose */ char grim_def_s_type_004ec54c[8] __asm__("_s_type_004ec54c") = "type";
/* 0x004ec554, 8 bytes */ /* loose */ char grim_def_s_true_004ec554[8] __asm__("_s_true_004ec554") = "true";
/* 0x004ec55c, 12 bytes */ /* loose */ char grim_def_s_TextAllowed_004ec55c[12] __asm__("_s_TextAllowed_004ec55c") = "TextAllowed";
/* 0x004ec568, 12 bytes */ /* loose */ char grim_def_s_axisHandler_004ec568[12] __asm__("_s_axisHandler_004ec568") = "axisHandler";
/* 0x004ec574, 16 bytes */ /* loose */ char grim_def_s_buttonHandler_004ec574[16] __asm__("_s_buttonHandler_004ec574") = "buttonHandler";
/* 0x004ec584, 8 bytes */ /* loose */ char grim_def_s_system_004ec584[8] __asm__("_s_system_004ec584") = "system";
/* 0x004ec58c, 12 bytes */ /* loose */ char grim_def_s_controls_004ec58c[12] __asm__("_s_controls_004ec58c") = "controls";
/* 0x004ec5a0, 8 bytes */ /* loose */ char grim_def_s_global_004ec5a0[8] __asm__("_s_global_004ec5a0") = "global";
/* 0x004ec5a8, 12 bytes */ /* loose */ char grim_def_s_parallel_004ec5a8[12] __asm__("_s_parallel_004ec5a8") = "parallel";
/* 0x004ec5c0, 20 bytes */ /* loose */ char grim_def_s_saveGameCallback_004ec5c0[20] __asm__("_s_saveGameCallback_004ec5c0") = "saveGameCallback";
static unsigned char grim_anchor_004f0d0c[0] __attribute__((section(".data$grim_004f0d0c"), aligned(16), used));
static unsigned char grim_pad_004f0d0c[12] __attribute__((section(".data$grim_004f0d0c_"), aligned(4), used));
/* 0x004f0d0c, 4 bytes */ GRIM_DATA("004f0d0cz") unsigned int grim_def_UINT_004f0d0c __asm__("_UINT_004f0d0c") = 0xffffffff;
/* 0x004f0d28, 12 bytes */ /* loose */ char grim_def_s_x_spot_cos_004f0d28[12] __asm__("_s_x_spot_cos_004f0d28") = "x_spot.cos";
/* 0x004f0d34, 56 bytes */ /* loose */ char grim_def_s_LightManager_Startup__Could_not_c_004f0d34[56] __asm__("_s_LightManager_Startup__Could_not_c_004f0d34") = "LightManager_Startup: Could not create main dialog.\n";
/* 0x008cab44, 4 bytes */ /* loose */ unsigned int grim_def_g_dwLrOldConcatFallback __asm__("_g_dwLrOldConcatFallback") = 0x0;
/* 0x008cab8c, 4 bytes */ /* loose */ unsigned int grim_def_g_dwDebugToggleFunc __asm__("_g_dwDebugToggleFunc") = 0x0;
__asm__(".globl _grim_img_exe_0x004ea890\n\t.set _grim_img_exe_0x004ea890, _PTR_s_concatfallback_004ea890 + 0\n");
__asm__(".globl _grim_img_exe_0x004ea8b0\n\t.set _grim_img_exe_0x004ea8b0, _PTR_s_EnginePause_004ea8b0 + 0\n");
