/* GRIMFANDANGO.EXE :: lua.c
 * functions 0x00401ca0 .. 0x004be2a0 (313 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00401ca0  Lua_Is3DHardwareEnabled ---- */
/* Lua opcode: Is3DHardwareEnabled */

void Lua_Is3DHardwareEnabled(void)

{
  if (g_pD3dDriver != (void *)0x0) {
    lua_pushnumber(FBITS(0x3f800000));
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
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  uVar2 = lua_lua2C(1);
  uVar1 = UINT_00901758;
  uVar4 = UINT_00900530;
  if (g_pD3dDriver == (void *)0x0) {
    uVar4 = 0xffffffff;
  }
  iVar3 = lua_isnil(uVar2);
  Display_PickDefault(0,(uint)(iVar3 == 0),(int *)&UINT_004dd340,(int *)&UINT_004dd344,
                      (int *)&UINT_004dd348);
  if ((UINT_004dd340 != uVar1) || (UINT_004dd348 != uVar4)) {
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
  lua_pushnumber(FBITS(0xbf800000));
  return;
}
#undef local_10


/* ---- 0x00401da0  Lua_SetVideoDevices ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetVideoDevices */

void Lua_SetVideoDevices(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint *puVar5;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  uVar1 = UINT_00901758;
  if (g_pD3dDriver == (void *)0x0) {
    local_4 = 0xffffffff;
  }
  else {
    local_4 = UINT_00900530;
  }
  iVar4 = lua_isnumber(uVar2);
  if (iVar4 != 0) {
    lua_isnumber(uVar3);
  }
  lua_getnumber(uVar2);
  lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  UINT_004dd340 = (uint)lVar6;
  puVar5 = (uint *)(UINT_004dd340 * 0x10 + (int)g_pDisplayModes);
  UINT_004dd344 = Display_FindClosestMode(&UINT_004f4d38,(void *)puVar5[1],*puVar5);
  lua_getnumber(uVar3);
  lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
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

#endif


/* ---- 0x00401e90  Lua_Enumerate3DDevices ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_1c */
/* Lua opcode: Enumerate3DDevices */

void Lua_Enumerate3DDevices(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  void *pvVar3;
  undefined4 unaff_EBX;
  uint uVar4;
  undefined4 unaff_EBP;
  int iVar5;
  longlong lVar6;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 == 0) {
    return;
  }
  lua_getnumber(uVar1);
  lVar6 = _ftol((double)CONCAT44(unaff_EBP,unaff_EBX));
  iVar2 = (int)lVar6;
  uVar1 = lua_createtable();
  if (((&UINT_00902d6c)[iVar2 * 0xa6] != 0) || ((&UINT_00902d68)[iVar2 * 0xa6] == 0)) {
    lua_pushobject(uVar1);
    lua_pushnumber(FBITS(0xbf800000));
    lua_pushstring(s__engn003_Software_004dd688);
    lua_settable();
    if ((&UINT_00902d68)[iVar2 * 0xa6] == 0) goto LAB_00401f9e;
  }
  uVar4 = 0;
  iVar2 = iVar2 * 0x10;
  if (*(int *)((int)g_pDisplayModes + iVar2 + 8) != 0) {
    iVar5 = 0;
    pvVar3 = g_pDisplayModes;
    do {
      if (*(int *)(*(int *)((int)pvVar3 + iVar2 + 0xc) + iVar5) != 0) {
        lua_pushobject(uVar1);
        lua_pushnumber((float)uVar4);
        lua_pushstring(*(int *)((int)g_pDisplayModes + iVar2 + 0xc) + 200 + iVar5);
        lua_settable();
        pvVar3 = g_pDisplayModes;
      }
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 0x22c;
    } while (uVar4 < *(uint *)((int)pvVar3 + iVar2 + 8));
  }
LAB_00401f9e:
  lua_pushobject(uVar1);
  return;
}
#undef local_1c

#endif


/* ---- 0x00401fb0  Lua_EnumerateVideoDevices ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* Lua opcode: EnumerateVideoDevices */

void Lua_EnumerateVideoDevices(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  uint uVar2;
  undefined *puVar3;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  
  uVar1 = lua_createtable();
  uVar2 = (uint)(INT_004f5a24 == 0);
  if (uVar2 < g_dwDisplayDeviceCount) {
    puVar3 = &DAT_00902ce0 + uVar2 * 0x298;
    do {
      lua_pushobject(uVar1);
      lua_pushnumber((float)uVar2);
      lua_pushstring(puVar3);
      lua_settable();
      uVar2 = uVar2 + 1;
      puVar3 = puVar3 + 0x298;
    } while (uVar2 < g_dwDisplayDeviceCount);
  }
  lua_pushobject(uVar1);
  return;
}
#undef local_1c


/* ---- 0x00402050  FUN_00402050 ---- */
void FUN_00402050(void)

{
  g_quitRequested = 1;
  return;
}

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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Lua opcode: DrawLine */

void Lua_DrawLine(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
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
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  local_1c = lua_lua2C(4);
  uVar4 = lua_lua2C(5);
  iVar5 = lua_isnumber(uVar1);
  if (iVar5 != 0) {
    iVar5 = lua_isnumber(uVar2);
    if (iVar5 != 0) {
      iVar5 = lua_isnumber(uVar3);
      if (iVar5 != 0) {
        iVar5 = lua_isnumber(local_1c);
        if (iVar5 != 0) {
          lua_getnumber(uVar1);
          lVar7 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          lua_getnumber(uVar2);
          lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          lua_getnumber(uVar3);
          lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          lua_getnumber(local_1c);
          lVar10 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          iVar5 = lua_istable(uVar4);
          if (iVar5 != 0) {
            lua_pushobject(uVar4);
            lua_pushstring(PTR_s_color_004e8368);
            uVar1 = lua_gettable();
            iVar5 = lua_isuserdata(uVar1);
            if (iVar5 != 0) {
              iVar5 = lua_tag(uVar1);
              if (iVar5 == 0x524c4f43) {
                uVar6 = lua_getuserdata(uVar1);
                PIECE(local_1c,2,1) = (byte)(uVar6 >> 0x10);
                local_1c = ((uVar6 >> 8 & 0xff) >> ((byte)UINT_004ddac4 & 0x1f)) <<
                           ((byte)UINT_004ddab8 & 0x1f) & 0xffff |
                           (uint)(PIECE(local_1c,2,1) >> ((byte)UINT_004ddac8 & 0x1f)) <<
                           ((byte)UINT_004ddabc & 0x1f) & 0xffff |
                           ((uVar6 & 0xff) >> ((byte)UINT_004ddac0 & 0x1f)) <<
                           ((byte)UINT_004ddab4 & 0x1f) & 0xffff;
              }
            }
            lua_pushobject(uVar4);
            lua_pushstring(PTR_s_layer_004e8390);
            uVar1 = lua_gettable();
            iVar5 = lua_isnumber(uVar1);
            if (iVar5 != 0) {
              lua_getnumber(uVar1);
              lVar11 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
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

#endif


/* ---- 0x00489a80  Lua_DrawPolygon ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_38 */
/* Lua opcode: DrawPolygon */

void Lua_DrawPolygon(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 unaff_ESI;
  code *pcVar8;
  undefined4 unaff_EDI;
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
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_istable(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_istable(uVar2);
    pcVar8 = lua_gettable_exref;
    if (iVar3 != 0) {
      lua_pushobject(uVar2);
      lua_pushstring(PTR_s_color_004e8368);
      pcVar8 = lua_gettable_exref;
      uVar4 = lua_gettable();
      iVar3 = lua_isuserdata(uVar4);
      if ((iVar3 != 0) && (iVar3 = lua_tag(uVar4), iVar3 == 0x524c4f43)) {
        uVar5 = lua_getuserdata(uVar4);
        PIECE(local_18,2,1) = (byte)(uVar5 >> 0x10);
        local_18 = ((uVar5 >> 8 & 0xff) >> ((byte)UINT_004ddac4 & 0x1f)) <<
                   ((byte)UINT_004ddab8 & 0x1f) & 0xffff |
                   (uint)(PIECE(local_18,2,1) >> ((byte)UINT_004ddac8 & 0x1f)) <<
                   ((byte)UINT_004ddabc & 0x1f) & 0xffff |
                   ((uVar5 & 0xff) >> ((byte)UINT_004ddac0 & 0x1f)) << ((byte)UINT_004ddab4 & 0x1f)
                   & 0xffff;
      }
      lua_pushobject(uVar2);
      lua_pushstring(PTR_s_layer_004e8390);
      uVar2 = lua_gettable();
      iVar3 = lua_isnumber(uVar2);
      if (iVar3 != 0) {
        lua_getnumber(uVar2);
        lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        local_c = (uint)lVar9;
      }
    }
    uVar5 = 0;
    local_24 = 1;
    do {
      lua_pushobject(uVar1);
      lua_pushnumber((float)(int)local_24);
      uVar2 = (*pcVar8)();
      iVar3 = lua_isnil(uVar2);
      if (iVar3 != 0) break;
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
          lua_pushobject(uVar1);
          iVar3 = local_24 + 1;
          lua_pushnumber((float)(int)local_24);
          uVar2 = (*pcVar8)();
          lua_getnumber(uVar2);
          lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          puVar6[-1] = (int)lVar9;
          lua_pushobject(uVar1);
          local_24 = local_24 + 2;
          lua_pushnumber((float)iVar3);
          uVar2 = (*pcVar8)();
          iVar3 = lua_isnil(uVar2);
          if (iVar3 == 0) {
            lua_getnumber(uVar2);
            lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
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

#endif


/* ---- 0x00489d70  Lua_DrawRectangle ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_34 */
/* Lua opcode: DrawRectangle */

void Lua_DrawRectangle(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
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
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  uVar5 = lua_lua2C(5);
  iVar6 = lua_isnumber(uVar1);
  if ((((iVar6 != 0) && (iVar6 = lua_isnumber(uVar2), iVar6 != 0)) &&
      (iVar6 = lua_isnumber(uVar3), iVar6 != 0)) && (iVar6 = lua_isnumber(uVar4), iVar6 != 0)) {
    lua_getnumber(uVar1);
    lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    lua_getnumber(uVar2);
    lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    lua_getnumber(uVar3);
    lVar10 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    lua_getnumber(uVar4);
    lVar11 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar6 = lua_istable(uVar5);
    if (iVar6 != 0) {
      lua_pushobject(uVar5);
      lua_pushstring(PTR_s_color_004e8368);
      uVar1 = lua_gettable();
      iVar6 = lua_isuserdata(uVar1);
      if ((iVar6 != 0) && (iVar6 = lua_tag(uVar1), iVar6 == 0x524c4f43)) {
        uVar7 = lua_getuserdata(uVar1);
        PIECE(local_20,2,1) = (byte)(uVar7 >> 0x10);
        local_20 = ((uVar7 >> 8 & 0xff) >> ((byte)UINT_004ddac4 & 0x1f)) <<
                   ((byte)UINT_004ddab8 & 0x1f) & 0xffff |
                   (uint)(PIECE(local_20,2,1) >> ((byte)UINT_004ddac8 & 0x1f)) <<
                   ((byte)UINT_004ddabc & 0x1f) & 0xffff |
                   ((uVar7 & 0xff) >> ((byte)UINT_004ddac0 & 0x1f)) << ((byte)UINT_004ddab4 & 0x1f)
                   & 0xffff;
      }
      lua_pushobject(uVar5);
      lua_pushstring(PTR_s_filled_004e838c);
      uVar1 = lua_gettable();
      iVar6 = lua_isnil(uVar1);
      local_14 = (uint)(iVar6 == 0);
      lua_pushobject(uVar5);
      lua_pushstring(PTR_s_layer_004e8390);
      uVar1 = lua_gettable();
      iVar6 = lua_isnumber(uVar1);
      if (iVar6 != 0) {
        lua_getnumber(uVar1);
        lVar12 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
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

#endif


/* ---- 0x00489fe0  Lua_ChangePrimitive ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: ChangePrimitive */

void Lua_ChangePrimitive(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  int a3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar8;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(uVar1);
  if (iVar3 == 0) {
    return;
  }
  iVar3 = lua_istable(uVar2);
  if (iVar3 != 0) {
    lua_getnumber(uVar1);
    lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar3 = (int)lVar8;
    lua_pushobject(uVar2);
    lua_pushstring(PTR_s_color_004e8368);
    uVar1 = lua_gettable();
    iVar4 = lua_isuserdata(uVar1);
    if ((iVar4 != 0) && (iVar4 = lua_tag(uVar1), iVar4 == 0x524c4f43)) {
      uVar5 = lua_getuserdata(uVar1);
      PIECE(local_10,2,1) = (byte)(uVar5 >> 0x10);
      Primitive_SetColor(iVar3,(uint)(PIECE(local_10,2,1) >> ((byte)UINT_004ddac8 & 0x1f)) <<
                               ((byte)UINT_004ddabc & 0x1f) & 0xffff |
                               ((uVar5 >> 8 & 0xff) >> ((byte)UINT_004ddac4 & 0x1f)) <<
                               ((byte)UINT_004ddab8 & 0x1f) & 0xffff |
                               ((uVar5 & 0xff) >> ((byte)UINT_004ddac0 & 0x1f)) <<
                               ((byte)UINT_004ddab4 & 0x1f) & 0xffff);
    }
    lua_pushobject(uVar2);
    lua_pushstring(PTR_s_layer_004e8390);
    uVar1 = lua_gettable();
    iVar4 = lua_isnumber(uVar1);
    if (iVar4 != 0) {
      lua_getnumber(uVar1);
      lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      Primitive_SetLayer(iVar3,(int)lVar8);
    }
    lua_pushobject(uVar2);
    lua_pushstring(PTR_s_xoffset_004e836c);
    uVar1 = lua_gettable();
    lua_pushobject(uVar2);
    lua_pushstring(PTR_s_yoffset_004e8370);
    uVar6 = lua_gettable();
    iVar4 = lua_isnumber(uVar1);
    if ((iVar4 != 0) || (iVar4 = lua_isnumber(uVar6), iVar4 != 0)) {
      local_8 = 0;
      iVar4 = lua_isnumber(uVar1);
      if (iVar4 != 0) {
        lua_getnumber(uVar1);
        lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        local_8 = (uint)lVar8;
      }
      iVar4 = lua_isnumber(uVar6);
      if (iVar4 == 0) {
        iVar4 = 0;
      }
      else {
        lua_getnumber(uVar6);
        lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        iVar4 = (int)lVar8;
      }
      Primitive_Offset(iVar3,local_8,iVar4);
    }
    lua_pushobject(uVar2);
    lua_pushstring(PTR_DAT_004e8374);
    uVar1 = lua_gettable();
    lua_pushobject(uVar2);
    lua_pushstring(PTR_DAT_004e8378);
    uVar6 = lua_gettable();
    iVar4 = lua_isnumber(uVar1);
    if ((iVar4 != 0) || (iVar4 = lua_isnumber(uVar6), iVar4 != 0)) {
      local_8 = 0xffffffff;
      iVar4 = lua_isnumber(uVar1);
      if (iVar4 != 0) {
        lua_getnumber(uVar1);
        lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        local_8 = (uint)lVar8;
      }
      iVar4 = lua_isnumber(uVar6);
      if (iVar4 == 0) {
        iVar4 = -1;
      }
      else {
        lua_getnumber(uVar6);
        lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        iVar4 = (int)lVar8;
      }
      Primitive_MoveTo(iVar3,local_8,iVar4);
    }
    lua_pushobject(uVar2);
    lua_pushstring(PTR_DAT_004e837c);
    uVar1 = lua_gettable();
    lua_pushobject(uVar2);
    lua_pushstring(PTR_DAT_004e8380);
    uVar6 = lua_gettable();
    iVar4 = lua_isnumber(uVar1);
    if ((iVar4 != 0) || (iVar4 = lua_isnumber(uVar6), iVar4 != 0)) {
      local_8 = 0xffffffff;
      iVar4 = lua_isnumber(uVar1);
      if (iVar4 != 0) {
        lua_getnumber(uVar1);
        lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        local_8 = (uint)lVar8;
      }
      iVar4 = lua_isnumber(uVar6);
      if (iVar4 == 0) {
        iVar4 = -1;
      }
      else {
        lua_getnumber(uVar6);
        lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        iVar4 = (int)lVar8;
      }
      Primitive_SetEnd(iVar3,local_8,iVar4);
    }
    lua_pushobject(uVar2);
    lua_pushstring(PTR_s_width_004e8384);
    uVar1 = lua_gettable();
    lua_pushobject(uVar2);
    lua_pushstring(PTR_s_height_004e8388);
    uVar2 = lua_gettable();
    iVar4 = lua_isnumber(uVar1);
    if ((iVar4 == 0) && (iVar4 = lua_isnumber(uVar2), iVar4 == 0)) {
      return;
    }
    a3 = -1;
    iVar4 = lua_isnumber(uVar1);
    if (iVar4 == 0) {
      iVar4 = -1;
    }
    else {
      lua_getnumber(uVar1);
      lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      iVar4 = (int)lVar8;
    }
    iVar7 = lua_isnumber(uVar2);
    if (iVar7 != 0) {
      lua_getnumber(uVar2);
      lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      a3 = (int)lVar8;
    }
    Primitive_SetSize(iVar3,iVar4,a3);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: KillPrimitive */

void __cdecl Lua_KillPrimitive(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    Primitive_Kill(&UINT_008ca0a0,(int)lVar3);
  }
  return;
}
#endif


/* ---- 0x0048a4a0  Lua_PurgePrimitiveQueue ---- */
/* Lua opcode: PurgePrimitiveQueue */

void Lua_PurgePrimitiveQueue(void)

{
  PrimitiveList_Clear((int *)&UINT_008ca0a0);
  Primitive_ResetIds();
  return;
}

/* ---- 0x0048ad60  Lua_SetOffscreenTextPos ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetOffscreenTextPos */

void Lua_SetOffscreenTextPos(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(uVar1);
  if (iVar3 == 0) {
    g_nSubtitleDefaultX = 0x140;
  }
  else {
    lua_getnumber(uVar1);
    lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    g_nSubtitleDefaultX = (int)lVar4;
  }
  iVar3 = lua_isnumber(uVar2);
  if (iVar3 != 0) {
    lua_getnumber(uVar2);
    lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    g_nSubtitleDefaultY = (int)lVar4;
    return;
  }
  g_nSubtitleDefaultY = 0x1c2;
  return;
}
#endif


/* ---- 0x0048ade0  Lua_SetEmergencyFont ---- */
/* Lua opcode: SetEmergencyFont */

void Lua_SetEmergencyFont(void)

{
  undefined4 uVar1;
  int iVar2;
  char *filename;
  void **outFont;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    if (g_pOverrideFont != (void *)0x0) {
      Font_Free(g_pOverrideFont);
      g_pOverrideFont = (void *)0x0;
    }
    outFont = &g_pOverrideFont;
    filename = (char *)lua_getstring(uVar1);
    Font_LoadFile(filename,outFont);
    return;
  }
  iVar2 = lua_isnil(uVar1);
  if ((iVar2 != 0) && (g_pOverrideFont != (void *)0x0)) {
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
  undefined4 uVar1;
  int iVar2;
  char *line;
  char *pcVar3;
  #define local_2a0 (*(char (*)[32])(_frame + (0x2b0 - 0x2a0)))
  #define local_280 (*(char (*)[640])(_frame + (0x2b0 - 0x280)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    pcVar3 = local_2a0;
    line = (char *)lua_getstring(uVar1);
    pcVar3 = Text_ParseLineId(line,pcVar3);
    sprintf(local_280,s___s__s_004e8754,local_2a0,pcVar3);
    lua_pushstring(local_280);
  }
  return;
}
#undef local_280
#undef local_2a0


/* ---- 0x0048aed0  Lua_MakeColor ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: MakeColor */

void Lua_MakeColor(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined1 uVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 unaff_ESI;
  uint uVar8;
  undefined4 unaff_EDI;
  longlong lVar9;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar3 = lua_lua2C(1);
  uVar4 = lua_lua2C(2);
  uVar5 = lua_lua2C(3);
  uVar6 = lua_lua2C(4);
  iVar7 = lua_isnumber(uVar3);
  if (iVar7 == 0) {
    iVar7 = 0;
  }
  else {
    lua_getnumber(uVar3);
    lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar7 = (int)lVar9;
  }
  uVar8 = 0;
  if (iVar7 < 0) {
LAB_0048af7b:
    local_c = 0;
  }
  else {
    iVar7 = lua_isnumber(uVar3);
    if (iVar7 == 0) {
      iVar7 = 0;
    }
    else {
      lua_getnumber(uVar3);
      lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      iVar7 = (int)lVar9;
    }
    if (iVar7 < 0x100) {
      iVar7 = lua_isnumber(uVar3);
      if (iVar7 == 0) goto LAB_0048af7b;
      lua_getnumber(uVar3);
      lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      local_c = (uint)lVar9;
    }
    else {
      local_c = 0xff;
    }
  }
  iVar7 = lua_isnumber(uVar4);
  if (iVar7 == 0) {
    iVar7 = 0;
  }
  else {
    lua_getnumber(uVar4);
    lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar7 = (int)lVar9;
  }
  if (-1 < iVar7) {
    iVar7 = lua_isnumber(uVar4);
    if (iVar7 == 0) {
      iVar7 = 0;
    }
    else {
      lua_getnumber(uVar4);
      lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      iVar7 = (int)lVar9;
    }
    if (iVar7 < 0x100) {
      iVar7 = lua_isnumber(uVar4);
      if (iVar7 != 0) {
        lua_getnumber(uVar4);
        lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        uVar8 = (uint)lVar9;
      }
    }
    else {
      uVar8 = 0xff;
    }
  }
  iVar7 = lua_isnumber(uVar5);
  if (iVar7 == 0) {
    iVar7 = 0;
  }
  else {
    lua_getnumber(uVar5);
    lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar7 = (int)lVar9;
  }
  if (iVar7 < 0) {
LAB_0048b053:
    uVar1 = 0;
  }
  else {
    iVar7 = lua_isnumber(uVar5);
    if (iVar7 == 0) {
      iVar7 = 0;
    }
    else {
      lua_getnumber(uVar5);
      lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      iVar7 = (int)lVar9;
    }
    if (iVar7 < 0x100) {
      iVar7 = lua_isnumber(uVar5);
      if (iVar7 == 0) goto LAB_0048b053;
      lua_getnumber(uVar5);
      lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      uVar1 = (undefined1)lVar9;
    }
    else {
      uVar1 = 0xff;
    }
  }
  iVar7 = lua_isnumber(uVar6);
  if (iVar7 == 0) {
    iVar7 = 0;
  }
  else {
    lua_getnumber(uVar6);
    lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar7 = (int)lVar9;
  }
  if (-1 < iVar7) {
    iVar7 = lua_isnumber(uVar6);
    if (iVar7 == 0) {
      iVar7 = 0;
    }
    else {
      lua_getnumber(uVar6);
      lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      iVar7 = (int)lVar9;
    }
    if (0xff < iVar7) {
      uVar2 = 0xff;
      goto LAB_0048b0c2;
    }
    iVar7 = lua_isnumber(uVar6);
    if (iVar7 != 0) {
      lua_getnumber(uVar6);
      lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      uVar2 = (undefined1)lVar9;
      goto LAB_0048b0c2;
    }
  }
  uVar2 = 0;
LAB_0048b0c2:
  lua_pushusertag(((uint)CONCAT11(uVar2,uVar1) << 8 | uVar8 & 0xff) << 8 | local_c & 0xff,0x524c4f43
                 );
  return;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x0048b100  Lua_GetColorComponents ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: GetColorComponents */

void Lua_GetColorComponents(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  uint uVar2;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_getuserdata(uVar1);
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
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar3 = Actor_FromHandle(uVar1);
      if (*(int *)(iVar3 + 0xa4) == 0) {
        Actor_CreateExtra(iVar3);
      }
      iVar4 = lua_isuserdata(uVar2);
      if (iVar4 != 0) {
        iVar4 = lua_tag(uVar2);
        if (iVar4 == 0x524c4f43) {
          uVar1 = lua_getuserdata(uVar2);
          *(undefined4 *)(*(int *)(iVar3 + 0xa4) + 0x418) = uVar1;
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
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      if (*(int *)(iVar2 + 0xa4) != 0) {
        lua_pushusertag(*(undefined4 *)(*(int *)(iVar2 + 0xa4) + 0x418),0x524c4f43);
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
    iVar1 = lua_istable(table);
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
  undefined4 uVar1;
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
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if ((((iVar2 != 0) && (iVar2 = lua_tag(uVar1), iVar2 == 0x52544341)) ||
      (iVar2 = lua_isstring(uVar1), iVar2 != 0)) || (iVar2 = lua_istable(uVar1), iVar2 != 0)) {
    local_38 = (uint)g_pSelectedActor;
    iVar2 = lua_isuserdata(uVar1);
    pcVar3 = lua_lua2C_exref;
    if ((iVar2 != 0) && (iVar2 = lua_tag(uVar1), pcVar3 = lua_lua2C_exref, iVar2 == 0x52544341)) {
      uVar1 = lua_getuserdata(uVar1);
      local_38 = Actor_FromHandle(uVar1);
      pcVar3 = lua_lua2C_exref;
      iVar4 = 3;
      uVar1 = lua_lua2C(2);
    }
    if (local_38 != 0) {
      iVar2 = lua_isnil(uVar1);
      while (iVar2 == 0) {
        iVar2 = lua_isstring(uVar1);
        if (((iVar2 == 0) && (iVar2 = lua_isnumber(uVar1), iVar2 == 0)) &&
           (iVar2 = lua_istable(uVar1), iVar2 == 0)) {
          return;
        }
        iVar2 = lua_istable(uVar1);
        if (iVar2 == 0) {
          iVar2 = lua_isnumber(uVar1);
          if (iVar2 == 0) {
            local_34 = lua_getstring(uVar1);
            Text_ParseLineId((char *)local_34,local_20);
          }
          else {
            local_3c = 0;
          }
        }
        else {
          Lua_ParseSayLineTable(uVar1,&local_3c,&local_24,&local_28,&local_2c,&local_30);
        }
        uVar1 = (*pcVar3)(iVar4);
        iVar2 = lua_isnil(uVar1);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Reads volume, pan, background, x, y overrides from the SayLine options table */

void Lua_ParseSayLineTable
               (undefined4 param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar3;
  
  lua_pushobject(param_1);
  uVar1 = lua_getref(UINT_008ca0dc);
  lua_pushobject(uVar1);
  uVar1 = lua_gettable();
  iVar2 = lua_isnumber(uVar1);
  if ((iVar2 != 0) && (*param_5 != 0)) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    *param_5 = (int)lVar3;
  }
  lua_pushobject(param_1);
  uVar1 = lua_getref(UINT_008ca0e0);
  lua_pushobject(uVar1);
  uVar1 = lua_gettable();
  iVar2 = lua_isnumber(uVar1);
  if ((iVar2 != 0) && (*param_6 != 0)) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    *param_6 = (int)lVar3;
  }
  lua_pushobject(param_1);
  uVar1 = lua_getref(UINT_008ca0e4);
  lua_pushobject(uVar1);
  uVar1 = lua_gettable();
  iVar2 = lua_isnil(uVar1);
  if ((iVar2 == 0) && (*param_2 != 0)) {
    *param_2 = 0;
  }
  lua_pushobject(param_1);
  uVar1 = lua_getref(UINT_008ca100);
  lua_pushobject(uVar1);
  uVar1 = lua_gettable();
  iVar2 = lua_isnumber(uVar1);
  if ((iVar2 != 0) && (*param_3 != 0)) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    *param_3 = (int)lVar3;
  }
  lua_pushobject(param_1);
  uVar1 = lua_getref(UINT_008ca114);
  lua_pushobject(uVar1);
  uVar1 = lua_gettable();
  iVar2 = lua_isnumber(uVar1);
  if ((iVar2 != 0) && (*param_4 != 0)) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    *param_4 = (int)lVar3;
  }
  return;
}
#endif


/* ---- 0x0048b830  Lua_PrintLine ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: PrintLine */

void Lua_PrintLine(void)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined4 uVar2;
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
  
  uVar2 = lua_lua2C(1);
  pvVar3 = (void *)lua_lua2C(2);
  local_58 = -1;
  if ((int)UINT_008a94bc <= (int)UINT_004e8480) {
    UINT_004e8480 = UINT_008a94bc;
  }
  if ((int)UINT_008a94c0 <= (int)UINT_004e8484) {
    UINT_004e8484 = UINT_008a94c0;
  }
  iVar4 = lua_isstring(uVar2);
  if (((iVar4 != 0) || (iVar4 = lua_isnil(uVar2), iVar4 != 0)) &&
     ((iVar4 = lua_istable(pvVar3), iVar4 != 0 || (iVar4 = lua_isnil(pvVar3), iVar4 != 0)))) {
    iVar4 = lua_isnil(uVar2);
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
    iVar4 = lua_istable(pvVar3);
    if (iVar4 != 0) {
      local_58 = Text_ParseLuaTable((void *)local_5c,pvVar3,(void *)0x0);
    }
    iVar4 = lua_isstring(uVar2);
    if (iVar4 != 0) {
      pcVar6 = local_50;
      pcVar5 = (char *)lua_getstring(uVar2);
      pcVar6 = Text_ParseLineId(pcVar5,pcVar6);
      if (local_58 < 0) {
        iVar4 = -1;
        pcVar5 = pcVar6;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar1 != '\0');
        lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        local_58 = (int)lVar9;
      }
      iVar4 = 0;
      pvVar3 = TextObject_New((void *)local_5c,pcVar6,local_58,0);
      TextObject_Activate(pvVar3,local_58,iVar4);
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
  undefined4 uVar4;
  
  iVar2 = lua_lua2C(1);
  if ((iVar2 == 0) ||
     (((iVar3 = lua_isuserdata(iVar2), iVar3 != 0 && (iVar3 = lua_tag(iVar2), iVar3 == 0x52544341))
      || (iVar3 = lua_isnil(iVar2), iVar3 != 0)))) {
    iVar3 = lua_isuserdata(iVar2);
    if ((iVar3 == 0) || (iVar3 = lua_tag(iVar2), iVar3 != 0x52544341)) {
      puVar1 = g_pTextObjectList;
      iVar2 = Render_GetFrameCounter();
      if (iVar2 != 0) {
        lua_pushnumber(FBITS(0x3f800000));
        return;
      }
      for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
        if ((*(byte *)(puVar1 + 0x96) & 1) == 0) goto LAB_0048ba30;
      }
    }
    else {
      uVar4 = lua_getuserdata(iVar2);
      iVar2 = Actor_FromHandle(uVar4);
      if (((iVar2 != 0) && (*(int *)(iVar2 + 0xa4) != 0)) &&
         (*(int *)(*(int *)(iVar2 + 0xa4) + 0x1c4) != 0)) {
LAB_0048ba30:
        lua_pushnumber(FBITS(0x3f800000));
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
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x54584554) {
      iVar2 = lua_getuserdata(uVar1);
      iVar3 = Text_MeasureWidth((void *)(iVar2 + 0x208),(char *)(iVar2 + 8));
      lua_pushnumber((float)iVar3);
      iVar2 = Text_MeasureHeight((void *)(iVar2 + 0x208),(char *)(iVar2 + 8));
      lua_pushnumber((float)iVar2);
    }
  }
  return;
}
#undef local_14
#undef local_4


/* ---- 0x0048bc50  Lua_GetTextCharPosition ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_18 */
/* Lua opcode: GetTextCharPosition */

void Lua_GetTextCharPosition(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 unaff_EBP;
  char *pcVar5;
  undefined4 unaff_EDI;
  longlong lVar6;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x54584554) {
      iVar3 = lua_getuserdata(uVar1);
      lua_getnumber(uVar2);
      lVar6 = _ftol((double)CONCAT44(unaff_EDI,unaff_EBP));
      local_4 = 0;
      if (0 < (int)lVar6) {
        pcVar5 = (char *)(iVar3 + 8);
        do {
          if (*pcVar5 == '\0') break;
          iVar4 = Text_CharWidth((void *)(iVar3 + 0x208),(int)*pcVar5);
          local_4 = local_4 + iVar4;
          pcVar5 = pcVar5 + 1;
        } while ((int)(pcVar5 + (-8 - iVar3)) < (int)lVar6);
      }
      lua_pushnumber((float)(int)local_4);
    }
  }
  return;
}
#undef local_18
#undef local_4

#endif


/* ---- 0x0048bd10  Lua_ChangeTextObject ---- */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* Lua opcode: ChangeTextObject */

void Lua_ChangeTextObject(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  void *textObj;
  void *table;
  int iVar3;
  char *pcVar4;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x54584554) {
      textObj = (void *)lua_getuserdata(uVar1);
      local_4 = 0;
      iVar2 = 2;
      do {
        table = (void *)lua_lua2C(iVar2);
        if (table == (void *)0x0) break;
        iVar3 = lua_isstring(table);
        if (iVar3 == 0) {
          iVar3 = lua_istable(table);
          if (iVar3 == 0) break;
          Text_ParseLuaTable((void *)((int)textObj + 0x208),table,textObj);
        }
        else {
          pcVar4 = (char *)lua_getstring();
          pcVar4 = Text_ParseLineId(pcVar4,(char *)0x0);
          strncpy((int)textObj + 8,pcVar4,0x1ff);
          *(undefined1 *)((int)textObj + 0x207) = 0;
        }
        local_4 = local_4 + 1;
        iVar2 = iVar2 + 1;
      } while ((int)local_4 < 2);
      iVar2 = Text_MeasureWidth((void *)((int)textObj + 0x208),(char *)((int)textObj + 8));
      lua_pushnumber((float)iVar2);
      iVar2 = Text_MeasureHeight((void *)((int)textObj + 0x208),(char *)((int)textObj + 8));
      lua_pushnumber((float)iVar2);
    }
  }
  return;
}
#undef local_18
#undef local_4


/* ---- 0x0048be30  Lua_MakeTextObject ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_78 */
/* Lua opcode: MakeTextObject */

void Lua_MakeTextObject(void)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  void *pvVar4;
  int unaff_EBX;
  uint *puVar5;
  int unaff_EDI;
  uint *puVar6;
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
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    pcVar3 = (char *)lua_getstring(uVar1);
    puVar5 = &g_TextObjectCtx;
    puVar6 = &local_30;
    for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    local_2c = (uint)&local_60;
    pvVar4 = (void *)lua_lua2C(2);
    if (pvVar4 != (void *)0x0) {
      iVar2 = lua_istable(pvVar4);
      if (iVar2 != 0) {
        Text_ParseLuaTable(&local_30,pvVar4,(void *)0x0);
      }
    }
    pcVar3 = Text_ParseLineId(pcVar3,local_50);
    pvVar4 = TextObject_New(&local_30,pcVar3,unaff_EBX,unaff_EDI);
    lua_pushusertag(pvVar4,0x54584554);
    iVar2 = Text_MeasureWidth((void *)((int)pvVar4 + 0x208),(char *)((int)pvVar4 + 8));
    lua_pushnumber((float)iVar2);
    iVar2 = Text_MeasureHeight((void *)((int)pvVar4 + 0x208),(char *)((int)pvVar4 + 8));
    lua_pushnumber((float)iVar2);
    TextObject_Activate(pvVar4,0,1);
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

#endif


/* ---- 0x0048bf50  Lua_BlastText ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: BlastText */

void Lua_BlastText(void)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  void *pvVar4;
  void *surface;
  int unaff_EBP;
  uint *puVar5;
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
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    pcVar3 = (char *)lua_getstring(uVar1);
    pvVar4 = (void *)Render_GetBackBuffer();
    Surface_Lock(pvVar4);
    puVar5 = &g_TextObjectCtx;
    puVar6 = &local_30;
    for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    iVar2 = Render_GetBackBuffer();
    local_2c = (uint)&local_60;
    *(undefined4 *)local_30 = *(undefined4 *)(iVar2 + 0x5c);
    pvVar4 = (void *)lua_lua2C(2);
    if (pvVar4 != (void *)0x0) {
      iVar2 = lua_istable(pvVar4);
      if (iVar2 != 0) {
        Text_ParseLuaTable(&local_30,pvVar4,(void *)0x0);
      }
    }
    pcVar3 = Text_ParseLineId(pcVar3,local_50);
    pvVar4 = TextObject_New(&local_30,pcVar3,unaff_EBP,unaff_EDI);
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

#endif


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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: SetTranslationMode */

void Lua_SetTranslationMode(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(uVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isnumber(uVar1);
    if (iVar2 == 0) {
      return;
    }
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
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
#endif


/* ---- 0x00495850  Lua_GetKeyLength ---- */
/* Lua opcode: GetKeyLength */

void Lua_GetKeyLength(void)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    lua_tag(uVar1);
  }
  piVar3 = (int *)lua_getuserdata(uVar1);
  if (*piVar3 == 0) {
    (*g_pSvcMain->pAssertFail)
              (s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3);
  }
  iVar2 = piVar3[1];
  if (*piVar3 == 0) {
    (*g_pSvcMain->pAssertFail)
              (s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3);
  }
  lua_pushnumber(((float)*(uint *)(iVar2 + 0x34) / *(float *)(piVar3[1] + 0x30)) * 1000.0);
  return;
}

/* ---- 0x00495900  Lua_GetSmushLength ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetSmushLength */

void Lua_GetSmushLength(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x534d5348) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Movie_SetFile(uVar1);
      lua_pushnumber((float)iVar2);
    }
  }
  return;
}
#undef local_4
#undef local_c


/* ---- 0x00495960  FUN_00495960 ---- */
void FUN_00495960(void)

{
  g_pSvcCostume = (GrimServices *)0x0;
  if (UINT_008ca798 != 0) {
    UINT_008ca798 = 0;
    (*(code *)UINT_008ca774)();
    if (g_pShadowColormap != (void *)0x0) {
      rdColormap_Free(g_pShadowColormap);
    }
  }
  return;
}

/* ---- 0x004959a0  FUN_004959a0 ---- */
undefined4 FUN_004959a0(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  code **ppcVar2;
  #define local_38 (*(code *(*)[14])(_frame + (0x50 - 0x38)))
  
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  ppcVar2 = local_38 + 7;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  if (UINT_008ca79c != 0) {
    return 1;
  }
  (*(code *)UINT_008ca778)();
  g_pCostumePool = (void **)Pool_Create(0xb4,10,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = ModelComponent_SetVisibleFlag;
  local_38[1] = FUN_00496b60;
  local_38[2] = ModelComponent_Destroy;
  local_38[3] = FUN_00496b40;
  local_38[4] = ModelComponent_EditParentOffset;
  local_38[5] = ModelComponent_NewInstance;
  Cos_NewStateBasedTag(0x4c444d4d,s_MAIN_RDroid_Thing___3DO__004ea3a0,0,local_38,2);
  Cos_NewStateBasedTag(0x4c444f4d,s_RDroid_Thing___3DO__004ea38c,0,local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = Lua_Stub;
  local_38[1] = CmapComponent_Create;
  local_38[2] = CmapComponent_Destroy;
  local_38[3] = (code *)0x0;
  local_38[4] = (code *)0x0;
  local_38[5] = FUN_00496370;
  Cos_NewStateBasedTag(0x70616d63,s_RDroid_Colormap_004ea37c,0,local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = FUN_00496d40;
  local_38[1] = ModelComponent_Create;
  local_38[2] = FUN_00498180;
  local_38[3] = FUN_00496e10;
  local_38[5] = SpriteComponent_NewInstance;
  local_38[4] = FUN_00497180;
  Cos_NewStateBasedTag(0x4853454d,s_RDroid_Thing_Mesh_004ea368,0,local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = FUN_004965d0;
  local_38[1] = FUN_00496670;
  local_38[2] = FUN_00498180;
  local_38[3] = (code *)0x0;
  local_38[5] = CmapComponent_NewInstance;
  local_38[6] = FUN_004965b0;
  Cos_NewStateBasedTag(0x2054414d,s_RDroid_Animated_Material_004ea34c,0,local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = FUN_00497890;
  local_38[1] = FUN_00497e10;
  local_38[2] = BitmapComponent_Destroy;
  local_38[3] = KeyframeComponent_Stop;
  local_38[4] = FUN_00498000;
  local_38[5] = FUN_00497d10;
  local_38[6] = (code *)0x0;
  Cos_NewStateBasedTag(0x4659454b,s_RDroid_Keyframe___KEY__004ea334,0,local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = Component_SetBitmapFrame;
  local_38[1] = FUN_004960a0;
  local_38[2] = SpriteComponent_Destroy;
  local_38[3] = (code *)0x0;
  local_38[4] = (code *)0x0;
  local_38[5] = (code *)0x0;
  Cos_NewStateBasedTag(0x444e4b42,s_General_Bitmap_004ea324,0,local_38,1);
  Cos_NewStateBasedTag(0x6d696e61,s_Animation__old_use_Bitmap__004ea308,0,local_38,1);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = FUN_004971a0;
  local_38[1] = FUN_00497460;
  local_38[2] = FUN_00497640;
  local_38[3] = FUN_00497660;
  local_38[4] = FUN_00497320;
  Cos_NewStateBasedTag(0x73736d69,s_iMuse_Streamed_Sound_FX_004ea2f0,0,local_38,2);
  Cos_NewStateBasedTag(0x736c6d69,s_iMuse_Resident_Sound_FX_004ea2d8,0,local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = FUN_00498160;
  local_38[1] = FUN_00498190;
  local_38[2] = FUN_00498140;
  local_38[3] = (code *)0x0;
  local_38[4] = (code *)0x0;
  local_38[6] = FUN_00498180;
  Cos_NewStateBasedTag(0x534d5348,s_Smush_Movie_004ea2cc,0,local_38,2);
  ppcVar2 = local_38;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (code *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_38[0] = FUN_00498550;
  local_38[1] = FUN_00498280;
  local_38[2] = KeyframeComponent_Destroy;
  local_38[3] = (code *)0x0;
  local_38[4] = FUN_004986e0;
  local_38[5] = FUN_004985c0;
  Cos_NewStateBasedTag(0x74727073,s_Sprite_004ea2c4,0,local_38,2);
  local_38[4] = (code *)0x0;
  local_38[7] = Lua_Stub;
  local_38[8] = FUN_00497840;
  local_38[9] = FUN_00498180;
  local_38[10] = (code *)0x0;
  Cos_NewIntTag(0x65736d69,s_iMuse_Sequence_004ea2b4,0,local_38 + 7,2);
  Cos_NewIntTag(0x74736d69,s_iMuse_State_004ea2a8,0,local_38 + 7,2);
  local_38[7] = FUN_00497680;
  local_38[8] = FUN_00497710;
  local_38[9] = FUN_004977f0;
  local_38[10] = FUN_00497810;
  local_38[0xb] = FUN_004976a0;
  Cos_NewIntTag(0x7661756c,s_Lua_Variable_004ea298,0,local_38 + 7,1);
  UINT_008ca7ac = Cos_RegisterInstanceHook(FUN_00496020);
  UINT_008ca7b0 = Cos_RegisterSaveHook(FUN_00495e90);
  Lua_OpenEngineLib(&PTR_s_GetKeyLength_004ea058,UINT_004ea068);
  UINT_008ca79c = 1;
  Config_GetPath(s_KeyframePath_004ea27c,&DAT_008ca7b8,s_Animation_004ea28c);
  Config_GetPath(s_ColormapPath_004ea260,&DAT_008ca8b8,s_Colormaps_004ea270);
  Config_GetPath(s_MaterialPath_004ea244,&DAT_008ca938,s_Materials_004ea254);
  Config_GetPath(s_ModelPath_004ea230,&DAT_008ca9b8,s_Models_004ea23c);
  Config_GetPath(s_SoundPath_004ea220,&DAT_008caa38,&DAT_004ea22c);
  Config_GetPath(s_SmushPath_004ea20c,&DAT_008caab8,s_Movies_004ea218);
  Config_GetPath(s_BitmapPath_004ea1f8,&DAT_008ca838,s_Objects_004ea204);
  return 0;
}
#undef local_38


/* ---- 0x00495e90  FUN_00495e90 ---- */
undefined4 FUN_00495e90(char *param_1,undefined4 param_2,undefined4 param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void **ppvVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  char *pcVar9;
  #define acStack_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  iVar3 = strrchr(param_1,0x5c);
  pcVar5 = param_1;
  if (iVar3 != 0) {
    pcVar5 = (char *)(iVar3 + 1);
  }
  uVar4 = Cos_GetCostumeName(param_2);
  iVar3 = _stricmp(pcVar5,uVar4);
  if (iVar3 == 0) {
    uVar6 = 0xffffffff;
    pcVar5 = param_1;
    do {
      pcVar9 = pcVar5;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar9 = pcVar5 + 1;
      cVar2 = *pcVar5;
      pcVar5 = pcVar9;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pcVar5 = pcVar9 + -uVar6;
    pcVar9 = g_szDialogFileName;
    for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar9 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar9 = pcVar9 + 1;
    }
    pcVar5 = Str_FileExtension(g_szDialogFileName);
    sprintf(pcVar5,&DAT_004ea45c);
  }
  else {
    iVar3 = Plat_SaveFileDialog(s_Name_chore_list_file____004ea460,
                                s_Script_files____lua____def__004ea478);
    if (iVar3 == 0) {
      return 0;
    }
  }
  iVar3 = (*g_pSvcCostume->pFopen)(g_szDialogFileName,&DAT_004dd478);
  if (iVar3 != 0) {
    ppvVar1 = &g_pSvcCostume->pFprintf;
    pcVar5 = Str_Basename(param_1);
    (*(code *)*ppvVar1)(iVar3,s____Chore_numbering_for__s__004ea3d4,pcVar5);
    (*g_pSvcCostume->pFprintf)(iVar3,s_____s_004ea3cc,param_3);
    Str_CopyBasenameNoExt(acStack_20,0x20,param_1);
    uVar4 = Cos_CreateCosInstance(param_2,0);
    uVar6 = Cos_InstCountChores(uVar4);
    uVar8 = 0;
    if (uVar6 != 0) {
      do {
        ppvVar1 = &g_pSvcCostume->pFprintf;
        uVar7 = Cos_InstChoreName(uVar4,uVar8,uVar8);
        (*(code *)*ppvVar1)(iVar3,s__s__s____d_004ea3bc,acStack_20,uVar7);
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar6);
    }
    (*g_pSvcCostume->pFclose)(iVar3);
    Cos_FreeCosInstance(uVar4);
    return 1;
  }
  Plat_MessageBox(s_File_Error__004ea3f0,s_Unable_to_open_chore_list_file__C_004ea3fc,0);
  return 0;
}
#undef acStack_20


/* ---- 0x00496020  FUN_00496020 ---- */
undefined4 FUN_00496020(undefined4 param_1,int param_2)

{
  if (param_2 != 0) {
    Cos_InstSetUserData(param_1,0);
    return 1;
  }
  Cos_InstSetUserData(param_1,0);
  return 1;
}

/* ---- 0x00497830  Lua_Stub ---- */
/* Lua opcodes: PutActorAtOrigin, GetClippedPos, DriveActorTo, WalkActorToInterest, UnLockFont,
   LockSound, UnlockSound, LockCostume, UnlockCostume, PlaySound, PlaySoundAt, PlaySoundAttached,
   IsSoundPlaying, GetSectorVertices, LoadBundle, UnloadBundle
   Shared handler for opcodes that the shipped engine does not implement */

void Lua_Stub(void)

{
  return;
}

/* ---- 0x00497840  FUN_00497840 ---- */
bool FUN_00497840(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  char *pcVar1;
  int iVar2;
  
  if (param_3 != 0) {
    return false;
  }
  pcVar1 = s_iMuse_Sequence_004ea2b4;
  if (param_2 != 0x65736d69) {
    pcVar1 = s_iMuse_State_004ea2a8;
  }
  iVar2 = Cos_RegisterComponent(param_1,pcVar1,1,param_2,0,param_4,0);
  return iVar2 != 0;
}

/* ---- 0x00497890  FUN_00497890 ---- */
void FUN_00497890(undefined4 param_1,int *param_2,undefined4 param_3,int param_4,uint param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  void *puppet;
  void *data;
  float fVar1;
  bool bVar2;
  undefined4 *puVar3;
  uint track;
  
  puppet = *(void **)(*(int *)(*param_2 + 0x40) + 0x14);
  if (param_2[1] == 0) {
    (*g_pSvcMain->pAssertFail)
              (s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3);
  }
  data = (void *)param_2[2];
  bVar2 = false;
  track = 0;
  puVar3 = (undefined4 *)((int)puppet + 0x130);
  do {
    if ((void *)*puVar3 == data) break;
    track = track + 1;
    puVar3 = puVar3 + 0x4d;
  } while ((int)track < 6);
  if (*(uint *)(&DAT_004e9f60 + param_4 * 4) < 8) {
    if (track == 6) {
      track = rdPuppet_AddTrack(puppet,(uint)data,param_2[0xf],param_2[0xe]);
      if ((int)track < 0) {
        return;
      }
      *(int *)(*(int *)(*param_2 + 0x40) + 0x48) = *param_2;
      ResRef_Add((void *)(*param_2 + 0x54 + track * 0x34),data,
                 s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xe3a);
      *(undefined4 *)(*param_2 + 0x18c) = param_8;
      rdPuppet_SetTrackUserData(puppet,track,FUN_00497cb0);
      bVar2 = true;
      goto LAB_00497960;
    }
  }
  else {
LAB_00497960:
    if (track == 6) {
      return;
    }
  }
  switch(*(undefined4 *)(&DAT_004e9f60 + param_4 * 4)) {
  case 0:
    if (bVar2) {
      rdPuppet_AdvanceTrack(puppet,track,(float)param_5 * 0.001);
    }
    rdPuppet_ClearTrackNodes(puppet,track);
    rdPuppet_SetTrackFlags(puppet,track,0x20);
    rdPuppet_PlayTrack(puppet,track);
    return;
  case 1:
    if (bVar2) {
      rdPuppet_AdvanceTrack(puppet,track,(float)param_5 * 0.001);
    }
    if ((*(byte *)((int)puppet + track * 0x134 + 8) & 0xc) == 0) {
      rdPuppet_PlayTrack(puppet,track);
      return;
    }
    break;
  case 2:
    if (bVar2) {
      rdPuppet_AdvanceTrack(puppet,track,(float)param_5 * 0.001);
    }
    rdPuppet_ClearTrackNodes(puppet,track);
    rdPuppet_SetTrackFlags(puppet,track,0x40);
    rdPuppet_PlayTrack(puppet,track);
    return;
  case 3:
    if (bVar2) {
      rdPuppet_AdvanceTrack(puppet,track,(float)param_5 * 0.001);
    }
    rdPuppet_ClearTrackNodes(puppet,track);
    rdPuppet_SetTrackFlags(puppet,track,0x80);
    rdPuppet_PlayTrack(puppet,track);
    return;
  case 4:
    rdPuppet_FadeInTrack(puppet,track,1.0);
    if (bVar2) {
      fVar1 = (float)param_5;
LAB_00497bc4:
      rdPuppet_AdvanceTrack(puppet,track,fVar1 * 0.001);
      return;
    }
    break;
  case 5:
    rdPuppet_FadeInTrack(puppet,track,0.5);
    if (bVar2) {
      fVar1 = (float)param_5;
      goto LAB_00497bc4;
    }
    break;
  case 6:
    rdPuppet_FadeInTrack(puppet,track,0.25);
    if (bVar2) {
      fVar1 = (float)param_5;
      goto LAB_00497bc4;
    }
    break;
  case 7:
    rdPuppet_FadeInTrack(puppet,track,0.125);
    if (bVar2) {
      fVar1 = (float)param_5;
      goto LAB_00497bc4;
    }
    break;
  case 8:
    if ((*(byte *)((int)puppet + track * 0x134 + 8) & 8) == 0) {
      rdPuppet_StopTrack(puppet,track);
      return;
    }
    break;
  case 9:
    rdPuppet_SetTrackFlags(puppet,track,0x10);
    return;
  case 10:
    *(uint *)((int)puppet + track * 0x134 + 8) =
         *(uint *)((int)puppet + track * 0x134 + 8) & 0xffffffef | 2;
    if (bVar2) {
      fVar1 = (float)param_5;
      goto LAB_00497bc4;
    }
    break;
  case 0xb:
    rdPuppet_FadeOutTrack(puppet,track,1.0);
    return;
  case 0xc:
    rdPuppet_FadeOutTrack(puppet,track,0.5);
    return;
  case 0xd:
    rdPuppet_FadeOutTrack(puppet,track,0.25);
    return;
  case 0xe:
    rdPuppet_FadeOutTrack(puppet,track,0.125);
  }
  return;
}

/* ---- 0x00497cb0  FUN_00497cb0 ---- */
void FUN_00497cb0(int param_1,int param_2,uint param_3)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = Cos_InstGetUserData(*(undefined4 *)(param_1 + 0x18c));
    Lua_CallCostumeMarkerHandler((void *)((int)g_pActorTable + iVar1 * 0xa8),param_3);
    if (param_3 == 0) {
      ResRef_Remove((void *)(param_1 + 0x54 + param_2 * 0x34));
    }
  }
  return;
}

/* ---- 0x00497d10  FUN_00497d10 ---- */
undefined4 * FUN_00497d10(undefined4 param_1,int *param_2,int param_3)

{
  void *data;
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  
  uVar4 = param_1;
  if (param_3 == 0) {
    iVar2 = Cos_InstGetInstanceData(param_1,param_2,0);
    ResRef_Remove((void *)(iVar2 + 4));
    (*g_pSvcCostume->pFree)(iVar2);
    return (undefined4 *)0x0;
  }
  Cos_InstComponentInfo(param_1,param_2,&param_3,&param_2,&param_1);
  piVar1 = param_2;
  if (*param_2 == 0) {
    (*g_pSvcMain->pAssertFail)
              (s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3);
  }
  data = (void *)piVar1[1];
  puVar3 = (undefined4 *)
           (*g_pSvcCostume->pAlloc)(0x40,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xed8);
  puVar5 = puVar3;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  ResRef_Add(puVar3 + 1,data,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xeda);
  puVar3[0xe] = param_2[0xd];
  puVar3[0xf] = param_2[0xe];
  uVar4 = Cos_InstGetInstanceData(uVar4,param_1,0);
  *puVar3 = uVar4;
  return puVar3;
}

/* ---- 0x00497e10  FUN_00497e10 ---- */
bool FUN_00497e10(undefined4 param_1,undefined4 param_2,int param_3,int param_4,uint param_5)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *name;
  void *data;
  uint uVar1;
  undefined4 uVar2;
  undefined4 *ref;
  int iVar3;
  undefined4 *puVar4;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(undefined1 *)(_frame + (0x40 - 0x20)))
  #define local_1f (*(undefined4 *)(_frame + (0x40 - 0x1f)))
  #define local_1 (*(undefined1 *)(_frame + (0x40 - 0x1)))
  
  local_20 = DAT_004f5a98;
  local_24 = 0;
  puVar4 = &local_1f;
  for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined2 *)puVar4 = 0;
  *(undefined1 *)((int)puVar4 + 2) = 0;
  local_2c = 1;
  local_28 = 5;
  if ((param_4 == 0x4c444f4d) || (param_4 == 0x4c444d4d)) {
    if (param_3 == 0) {
      return false;
    }
    if (param_5 == 0) {
      if (DAT_008ca7b8 != '\0') {
        Plat_SetDialogDirectory(&DAT_008ca7b8);
      }
      iVar3 = Plat_OpenFileDialog(s_Select_keyframe_file_to_add____004ea76c,
                                  s_Keyframe_files____key__004ea78c);
      if (iVar3 == 0) {
        return false;
      }
      uVar2 = ((code *)Plat_GetDialogFileName)(0x7f);
      ((code *)strncpy)(&DAT_008ca7b8,uVar2);
      DAT_008ca837 = 0;
      local_24 = (uint)Str_Basename(g_szDialogFileName);
      data = Resource_Load(0x4659454b,g_szDialogFileName);
    }
    else {
      strncpy(&local_20,param_5,0x1f);
      local_1 = 0;
      name = (char *)strtok(&local_20,&DAT_004ea52c);
      data = Resource_Load(0x4659454b,name);
      uVar1 = strtok(0,&DAT_004ea52c);
      if (uVar1 != 0) {
        local_2c = (uint)atoi(uVar1);
        uVar1 = strtok(0,&DAT_004ea52c);
        local_28 = (uint)atoi(uVar1);
      }
    }
    if (data != (void *)0x0) {
      ref = (undefined4 *)
            (*g_pSvcCostume->pAlloc)(0x3c,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xf27);
      puVar4 = ref;
      for (iVar3 = 0xf; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
      ResRef_Add(ref,data,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xf29);
      ref[0xe] = local_2c;
      ref[0xd] = local_28;
      if (param_5 == 0) {
        param_5 = local_24;
      }
      iVar3 = Cos_RegisterComponent(param_1,param_5,ref,param_2,param_3,param_4,&DAT_004e9fe0);
      return iVar3 != 0;
    }
  }
  return false;
}
#undef local_1
#undef local_1f
#undef local_20
#undef local_24
#undef local_28
#undef local_2c


/* ---- 0x00498000  FUN_00498000 ---- */
undefined4 FUN_00498000(int *param_1,undefined4 param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(char (*)[32])(_frame + (0x40 - 0x20)))
  
  local_28 = (uint)s_Tagged_Priority_004ea7dc;
  local_24 = (uint)s_Normal_Priority_004ea7cc;
  iVar1 = *param_1;
  local_30 = *(uint *)(iVar1 + 0x34);
  local_2c = *(uint *)(iVar1 + 0x38);
  iVar2 = Plat_PromptDialog(param_2,&local_28,&local_30,2);
  if (iVar2 != 0) {
    iVar2 = strtok(param_2,&DAT_004ea52c);
    *(uint *)(iVar1 + 0x34) = local_30;
    *(uint *)(iVar1 + 0x38) = local_2c;
    sprintf(local_20,s__s__d__d_004ea7c0,iVar2,local_2c,local_30);
    strncpy(iVar2,local_20,0x1f);
    *(undefined1 *)(iVar2 + 0x1f) = 0;
    return 1;
  }
  return 0;
}
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30


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
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(int *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(int *)(_frame + (0x30 - 0x10)))
  #define fStack_c (*(float *)(_frame + (0x30 - 0xc)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(undefined1 (*)[4])(_frame + (0x30 - 0x4)))
  
  GetDiskFreeSpaceA(0,(int)&local_14,(int)&local_18,(int)&local_10,(int)local_4);
  uStack_8 = 0;
  fStack_c = (float)local_18 * 0.0009765625 * (float)local_14 * 0.0009765625 * (float)local_10;
  lua_pushnumber(fStack_c);
  return;
}
#undef fStack_c
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef uStack_8


/* ---- 0x00498e20  Lua_TEST ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: TEST */

void Lua_TEST(uint param_1,uint param_2,float param_3,float param_4,float param_5,float *param_6,
             float param_7,float param_8,float param_9,float param_10,uint param_11,
             undefined4 param_12,double param_13)

{
  uint unaff_retaddr;
  
  SectorList_ShrinkWalkSectors
            (0.005,unaff_retaddr,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
             param_9,param_10,param_11,param_13);
  return;
}
#endif


/* ---- 0x00498e50  Lua_ShrinkBoxes ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: ShrinkBoxes */

void Lua_ShrinkBoxes(uint param_1,float param_2,float param_3,float param_4,float *param_5,
                    float param_6,float param_7,float param_8,float param_9,uint param_10,
                    undefined4 param_11,double param_12)

{
  undefined4 uVar1;
  int iVar2;
  uint unaff_ESI;
  float10 fVar3;
  uint unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(uVar1);
  if (iVar2 == 0) {
    Lua_UnShrinkBoxes();
    SectorList_SaveForShrink();
    fVar3 = (float10)lua_getnumber(uVar1);
    SectorList_ShrinkWalkSectors
              ((float)fVar3,unaff_ESI,unaff_retaddr,param_1,param_2,param_3,param_4,param_5,param_6,
               param_7,param_8,param_9,param_10,param_12);
  }
  return;
}
#endif


/* ---- 0x00498e90  Lua_UnShrinkBoxes ---- */
/* Lua opcode: UnShrinkBoxes */

void Lua_UnShrinkBoxes(void)

{
  SectorList_RestoreAfterShrink();
  SectorList_FreeShrinkSave();
  return;
}

/* ---- 0x00498ea0  Lua_GetShrinkPos ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_1c */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* WARNING: Variable defined which should be unmapped: local_c */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Lua opcode: GetShrinkPos */

void Lua_GetShrinkPos(undefined4 param_1,double param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  void *this;
  float unaff_EBX;
  uint unaff_EBP;
  uint unaff_ESI;
  uint unaff_EDI;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  uint unaff_retaddr;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  iVar5 = lua_isnumber(uVar1);
  if (iVar5 != 0) {
    iVar5 = lua_isnumber(uVar2);
    if (iVar5 != 0) {
      iVar5 = lua_isnumber(uVar3);
      if (iVar5 != 0) {
        iVar5 = lua_isnumber(uVar4);
        if (iVar5 != 0) {
          fVar6 = (float10)lua_getnumber(uVar1);
          fVar7 = (float10)lua_getnumber(uVar2);
          fVar8 = (float10)lua_getnumber(uVar3);
          fVar9 = (float10)lua_getnumber(uVar4);
          local_c = (uint)(float)fVar6;
          local_8 = (uint)(float)fVar7;
          local_4 = (uint)(float)fVar8;
          SectorList_SaveForShrink();
          SectorList_ShrinkWalkSectors
                    ((float)fVar9,unaff_EDI,unaff_ESI,unaff_EBP,unaff_EBX,(float)fVar6,(float)fVar7,
                     PUN(float *,(float)(float)fVar8),(float)fVar9,(float)local_c,(float)local_8,(float)local_4
                     ,unaff_retaddr,param_2);
          this = (void *)SectorList_FindNearestPoint(&local_c,0x1000);
          if (this != (void *)0x0) {
            Sector_ClampPoint(this,(int)&local_c);
          }
          Lua_UnShrinkBoxes();
          if (this != (void *)0x0) {
            lua_pushnumber(local_c);
            lua_pushnumber(local_8);
            lua_pushnumber(local_4);
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
#undef local_8
#undef local_c

#endif


/* ---- 0x00499000  Lua_SetSoundParameters ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetSoundParameters */

void Lua_SetSoundParameters(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  void *set;
  int iVar6;
  uint uVar7;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  uint uVar8;
  float10 fVar9;
  longlong lVar10;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  uVar5 = lua_lua2C(5);
  set = Set_GetCurrent();
  if (set != (void *)0x0) {
    iVar6 = lua_isnil(uVar1);
    if (iVar6 != 0) {
      iVar6 = lua_isnil(uVar2);
      if (iVar6 != 0) {
        iVar6 = lua_isnil(uVar3);
        if (iVar6 != 0) {
          iVar6 = lua_isnil(uVar4);
          if (iVar6 != 0) {
            iVar6 = lua_isnil(uVar5);
            if (iVar6 != 0) {
              Set_SetSoundParams(set,0x41000000,0x14,0x7f,0x3fc00000,0x3f4ccccd);
              return;
            }
          }
        }
      }
    }
    Set_GetSoundParams(set,(float *)&local_4,(char *)&local_8,(char *)&local_c,(float *)&local_10,
                       (float *)&local_14);
    iVar6 = lua_isnil(uVar5);
    if (iVar6 == 0) {
      fVar9 = (float10)lua_getnumber(uVar5);
      local_1c = (uint)(float)fVar9;
    }
    else {
      local_1c = local_14;
    }
    iVar6 = lua_isnil(uVar4);
    if (iVar6 == 0) {
      fVar9 = (float10)lua_getnumber(uVar4);
      local_18 = (uint)(float)fVar9;
    }
    else {
      local_18 = local_10;
    }
    iVar6 = lua_isnil(uVar3);
    if (iVar6 == 0) {
      lua_getnumber(uVar3);
      lVar10 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      uVar7 = (uint)lVar10;
    }
    else {
      uVar7 = local_c & 0xff;
    }
    iVar6 = lua_isnil(uVar2);
    if (iVar6 == 0) {
      lua_getnumber(uVar2);
      lVar10 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      uVar8 = (uint)lVar10;
    }
    else {
      uVar8 = local_8 & 0xff;
    }
    iVar6 = lua_isnil(uVar1);
    if (iVar6 == 0) {
      fVar9 = (float10)lua_getnumber(uVar1);
      local_20 = (uint)(float)fVar9;
    }
    else {
      local_20 = local_4;
    }
    Set_SetSoundParams(set,local_20,uVar8,uVar7,local_18,local_1c);
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


/* ---- 0x004991c0  Lua_GetSoundParameters ---- */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: GetSoundParameters */

void Lua_GetSoundParameters(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *set;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  set = Set_GetCurrent();
  if (set != (void *)0x0) {
    Set_GetSoundParams(set,(float *)&local_18,(char *)&local_14,(char *)&local_c,(float *)&local_8,
                       (float *)&local_4);
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
/* Lua opcode: EngineDisplay */

void Lua_EngineDisplay(void)

{
  undefined4 uVar1;
  longlong lVar2;
  double in_stack_00000000;
  
  uVar1 = lua_lua2C(1);
  lua_getnumber(uVar1);
  lVar2 = _ftol(in_stack_00000000);
  Render_SetDrawEnabled((int)lVar2);
  return;
}

/* ---- 0x004992b0  Lua_LoadActor ---- */
/* Lua opcode: LoadActor */

void Lua_LoadActor(void)

{
  int iVar1;
  
  iVar1 = Actor_Create();
  if (-1 < iVar1) {
    lua_pushusertag(iVar1,0x52544341);
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
  undefined4 uVar1;
  int iVar2;
  void *pvVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      uVar1 = Actor_FromHandle(uVar1);
      pvVar3 = Set_GetCurrent();
      if (pvVar3 != (void *)0x0) {
        iVar2 = *(int *)((int)pvVar3 + 0xac) + 0x2c + *(int *)((int)pvVar3 + 0xb4) * 300;
        local_c = *(uint *)(*(int *)((int)pvVar3 + 0xac) + 0x2c + *(int *)((int)pvVar3 + 0xb4) * 300
                           );
        local_8 = *(uint *)(iVar2 + 4);
        local_4 = *(uint *)(iVar2 + 8);
        Actor_SetPositionClamped(uVar1,&local_c);
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
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      iVar2 = lua_getuserdata(uVar1);
      iVar2 = Actor_SetSelected(iVar2);
      if (-1 < iVar2) {
        lua_pushusertag(iVar2,0x52544341);
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
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  iVar5 = lua_isuserdata(uVar1);
  if (iVar5 != 0) {
    iVar5 = lua_tag(uVar1);
    if (iVar5 == 0x52544341) {
      iVar5 = lua_isnumber(uVar2);
      if (iVar5 != 0) {
        iVar5 = lua_isnumber(uVar3);
        if (iVar5 != 0) {
          iVar5 = lua_isnumber(uVar4);
          if (iVar5 != 0) {
            uVar1 = lua_getuserdata(uVar1);
            uVar1 = Actor_FromHandle(uVar1);
            fVar6 = (float10)lua_getnumber(uVar2);
            local_c = (uint)(float)fVar6;
            fVar6 = (float10)lua_getnumber(uVar3);
            local_8 = (uint)(float)fVar6;
            fVar6 = (float10)lua_getnumber(uVar4);
            local_4 = (uint)(float)fVar6;
            Actor_SetPositionClamped(uVar1,&local_c);
          }
        }
      }
    }
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004994a0  Lua_PutActorInSet ---- */
/* Lua opcode: PutActorInSet */

void Lua_PutActorInSet(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  void *pvVar5;
  char *pcVar6;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(uVar1), iVar3 == 0x52544341)) {
    uVar1 = lua_getuserdata(uVar1);
    pcVar4 = (char *)Actor_FromHandle(uVar1);
    iVar3 = lua_isstring(uVar2);
    if ((iVar3 == 0) && (iVar3 = lua_isnil(uVar2), iVar3 == 0)) {
      return;
    }
    pcVar6 = pcVar4;
    pvVar5 = (void *)lua_getstring(uVar2);
    Actor_PutInSet(pvVar5,pcVar6);
    if ((((*(int *)(pcVar4 + 0xa4) != 0) && (iVar3 = lua_isstring(uVar2), iVar3 != 0)) &&
        (*(int *)(*(int *)(pcVar4 + 0xa4) + 0x1b4) != 0)) &&
       (*(int *)(*(int *)(pcVar4 + 0xa4) + 0x1b8) != 0)) {
      pcVar6 = (char *)lua_getstring(uVar2);
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
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  void *actor;
  float *pfVar9;
  float *pfVar10;
  int iVar11;
  float10 fVar12;
  float fVar13;
  float fVar14;
  #define local_78 (*(uint *)(_frame + (0x90 - 0x78)))
  #define local_64 (*(uint *)(_frame + (0x90 - 0x64)))
  #define local_60 (*(uint *)(_frame + (0x90 - 0x60)))
  #define local_5c (*(uint *)(_frame + (0x90 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x90 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x90 - 0x54)))
  #define local_50 (*(uint *)(_frame + (0x90 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0x90 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x90 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x90 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x90 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x90 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x90 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x90 - 0x34)))
  #define local_30 (*(float (*)[9])(_frame + (0x90 - 0x30)))
  #define local_c (*(uint *)(_frame + (0x90 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x90 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x90 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  uVar4 = lua_lua2C(3);
  uVar5 = lua_lua2C(4);
  uVar6 = lua_lua2C(5);
  uVar7 = lua_lua2C(6);
  iVar8 = lua_isuserdata(uVar2);
  if (iVar8 != 0) {
    iVar8 = lua_tag(uVar2);
    if (iVar8 == 0x52544341) {
      iVar8 = lua_isuserdata(uVar3);
      if (iVar8 != 0) {
        iVar8 = lua_tag(uVar3);
        if (iVar8 == 0x52544341) {
          uVar2 = lua_getuserdata(uVar2);
          iVar8 = Actor_FromHandle(uVar2);
          uVar2 = lua_getuserdata(uVar3);
          actor = (void *)Actor_FromHandle(uVar2);
          fVar12 = (float10)lua_getnumber(uVar4);
          local_54 = (uint)(float)fVar12;
          fVar12 = (float10)lua_getnumber(uVar5);
          local_50 = (uint)(float)fVar12;
          fVar12 = (float10)lua_getnumber(uVar6);
          local_4c = (uint)(float)fVar12;
          pfVar9 = Actor_GetFrame(actor);
          pfVar10 = local_30;
          for (iVar11 = 0xc; iVar11 != 0; iVar11 = iVar11 + -1) {
            *pfVar10 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            pfVar10 = pfVar10 + 1;
          }
          iVar11 = lua_isnumber(uVar7);
          if (iVar11 != 0) {
            fVar12 = (float10)lua_getnumber(uVar7);
            local_38 = (uint)(float)fVar12;
            local_c = 0;
            local_8 = 0;
            local_3c = 0;
            local_34 = 0;
            local_4 = 0;
            Matrix_BuildTransform(local_30,&local_3c);
          }
          Vec3_Transform((float *)&local_54,local_30);
          iVar11 = 3;
          pfVar9 = (float *)(iVar8 + 0xc);
          pfVar10 = (float *)&local_54;
          do {
            fVar1 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            iVar11 = iVar11 + -1;
            *pfVar10 = fVar1 + *pfVar10;
            pfVar10 = pfVar10 + 1;
          } while (iVar11 != 0);
          local_48 = local_54;
          local_44 = local_50;
          local_40 = local_4c;
          Walker_ToLocalSpace(*(void **)(*(int *)(iVar8 + 0xa4) + 0x1b4),(float *)&local_48);
          Vec3_Normalize((float *)&local_48);
          fVar13 = Math_AsinDegreesSeries((float)local_44);
          fVar1 = *(float *)(*(int *)(iVar8 + 0xa4) + 0x1c);
          if (*(float *)(*(int *)(iVar8 + 0xa4) + 0x1c) < 0.0) {
            fVar1 = -fVar1;
          }
          fVar14 = Timer_GetFrameSeconds();
          Walker_TurnToPoint(*(void **)(*(int *)(iVar8 + 0xa4) + 0x1b4),(int)&local_54,
                             (int)(fVar14 * fVar1 + fVar14 * fVar1));
          if (90.0 - fVar13 < 90.0) {
            *(uint *)(iVar8 + 8) = *(uint *)(iVar8 + 8) & 0xfffffffe;
            Actor_WalkForward(iVar8);
          }
        }
      }
    }
  }
  return;
}
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_4
#undef local_40
#undef local_44
#undef local_48
#undef local_4c
#undef local_50
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
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      *(uint *)(iVar2 + 8) = *(uint *)(iVar2 + 8) & 0xfffffffe;
      Actor_WalkForward(iVar2);
    }
  }
  return;
}

/* ---- 0x00499860  Lua_WalkActorTo ---- */
/* Lua opcode: WalkActorTo */

void Lua_WalkActorTo(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  float10 fVar7;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  uVar5 = lua_lua2C(5);
  lua_lua2C(6);
  lua_lua2C(7);
  iVar6 = lua_isuserdata(uVar1);
  if ((iVar6 != 0) && (iVar6 = lua_tag(uVar1), iVar6 == 0x52544341)) {
    uVar1 = lua_getuserdata(uVar1);
    uVar1 = Actor_FromHandle(uVar1);
    iVar6 = lua_isnumber(uVar2);
    if (iVar6 == 0) {
      iVar6 = lua_isuserdata();
      if (iVar6 == 0) {
        return;
      }
      iVar6 = lua_tag(uVar2);
      if (iVar6 != 0x52544341) {
        return;
      }
      uVar2 = lua_getuserdata(uVar2);
      iVar6 = Actor_FromHandle(uVar2);
      local_18 = *(uint *)(iVar6 + 0xc);
      local_14 = *(uint *)(iVar6 + 0x10);
      local_10 = *(uint *)(iVar6 + 0x14);
    }
    else {
      fVar7 = (float10)lua_getnumber(uVar2);
      local_18 = (uint)(float)fVar7;
      fVar7 = (float10)lua_getnumber(uVar3);
      local_14 = (uint)(float)fVar7;
      fVar7 = (float10)lua_getnumber(uVar4);
      local_10 = (uint)(float)fVar7;
    }
    fVar7 = (float10)lua_getnumber(uVar5);
    local_c = (uint)(float)fVar7;
    fVar7 = (float10)lua_getnumber(uVar5);
    local_8 = (uint)(float)fVar7;
    fVar7 = (float10)lua_getnumber(uVar5);
    local_4 = (uint)(float)fVar7;
    Walker_ReplanPath(uVar1,&local_18,&local_c,0);
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


/* ---- 0x004999d0  Lua_WalkActorToAvoiding ---- */
/* Lua opcode: WalkActorToAvoiding */

void Lua_WalkActorToAvoiding(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  float10 fVar8;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  uVar5 = lua_lua2C(5);
  uVar6 = lua_lua2C(6);
  lua_lua2C(7);
  lua_lua2C(8);
  iVar7 = lua_isuserdata(uVar1);
  if ((((iVar7 != 0) && (iVar7 = lua_tag(uVar1), iVar7 == 0x52544341)) &&
      (iVar7 = lua_isuserdata(uVar2), iVar7 != 0)) && (iVar7 = lua_tag(uVar2), iVar7 == 0x52544341))
  {
    uVar1 = lua_getuserdata(uVar1);
    uVar1 = Actor_FromHandle(uVar1);
    uVar2 = lua_getuserdata(uVar2);
    uVar2 = Actor_FromHandle(uVar2);
    iVar7 = lua_isnumber(uVar3);
    if (iVar7 == 0) {
      iVar7 = lua_isuserdata();
      if (iVar7 == 0) {
        return;
      }
      iVar7 = lua_tag(uVar3);
      if (iVar7 != 0x52544341) {
        return;
      }
      uVar3 = lua_getuserdata(uVar3);
      iVar7 = Actor_FromHandle(uVar3);
      local_18 = *(uint *)(iVar7 + 0xc);
      local_14 = *(uint *)(iVar7 + 0x10);
      local_10 = *(uint *)(iVar7 + 0x14);
    }
    else {
      fVar8 = (float10)lua_getnumber(uVar3);
      local_18 = (uint)(float)fVar8;
      fVar8 = (float10)lua_getnumber(uVar4);
      local_14 = (uint)(float)fVar8;
      fVar8 = (float10)lua_getnumber(uVar5);
      local_10 = (uint)(float)fVar8;
    }
    fVar8 = (float10)lua_getnumber(uVar6);
    local_c = (uint)(float)fVar8;
    fVar8 = (float10)lua_getnumber(uVar6);
    local_8 = (uint)(float)fVar8;
    fVar8 = (float10)lua_getnumber(uVar6);
    local_4 = (uint)(float)fVar8;
    Walker_ReplanPath(uVar1,&local_18,&local_c,uVar2);
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


/* ---- 0x00499b80  Lua_IsActorMoving ---- */
/* Lua opcode: IsActorMoving */

void Lua_IsActorMoving(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      if ((*(byte *)(iVar2 + 8) & 1) != 0) {
        lua_pushnumber(FBITS(0x3f800000));
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
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      if (*(int *)(iVar2 + 0xa4) == 0) {
        Actor_CreateExtra(iVar2);
      }
      if (*(float *)(*(int *)(iVar2 + 0xa4) + 0x28) != 0.0) {
        lua_pushnumber(FBITS(0x3f800000));
      }
      lua_pushnil();
    }
  }
  return;
}

/* ---- 0x00499c70  Lua_SetActorChoreLooping ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetActorChoreLooping */

void Lua_SetActorChoreLooping(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *luaObj;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 unaff_EDI;
  longlong lVar7;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  luaObj = (void *)lua_lua2C(4);
  iVar4 = lua_isuserdata(uVar1);
  if (iVar4 != 0) {
    iVar4 = lua_tag(uVar1);
    if (iVar4 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar4 = Actor_FromHandle(uVar1);
      iVar4 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar4 + 0xa0),(void **)&local_4);
      if ((iVar4 != 0) && (local_4 != 0)) {
        iVar4 = lua_isnumber(uVar2);
        if (iVar4 != 0) {
          iVar4 = lua_isnil(uVar3);
          uVar5 = (uint)(iVar4 == 0);
          lua_getnumber(uVar2);
          lVar7 = _ftol((double)CONCAT44(unaff_EDI,uVar5));
          Cos_InstSetChoreLoop(*(undefined4 *)local_4,(int)lVar7);
          return;
        }
        iVar4 = lua_isnil(uVar2);
        if (iVar4 != 0) {
          uVar5 = Cos_InstCountChores(*(undefined4 *)local_4);
          lua_isnil(uVar3);
          uVar6 = 0;
          if (uVar5 != 0) {
            do {
              iVar4 = lua_isnil(uVar3);
              Cos_InstSetChoreLoop(*(undefined4 *)local_4,uVar6,iVar4 == 0);
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

#endif


/* ---- 0x00499da0  Lua_IsActorResting ---- */
/* Lua opcode: IsActorResting */

void Lua_IsActorResting(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      if (*(int *)(iVar2 + 0xa4) == 0) {
        Actor_CreateExtra(iVar2);
      }
      if (*(int *)(*(int *)(iVar2 + 0xa4) + 0x14) != 0) {
        lua_pushnumber(FBITS(0x3f800000));
        return;
      }
      lua_pushnil();
    }
  }
  return;
}

/* ---- 0x00499e20  Lua_IsActorChoring ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: IsActorChoring */

void Lua_IsActorChoring(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *luaObj;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 unaff_ESI;
  uint uVar8;
  undefined4 unaff_EDI;
  longlong lVar9;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  luaObj = (void *)lua_lua2C(4);
  local_4 = 0xffffffff;
  iVar4 = lua_isuserdata(uVar1);
  if ((iVar4 != 0) && (iVar4 = lua_tag(uVar1), iVar4 == 0x52544341)) {
    uVar1 = lua_getuserdata(uVar1);
    iVar4 = Actor_FromHandle(uVar1);
    iVar4 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar4 + 0xa0),(void **)&local_c);
    if (iVar4 != 0) {
      iVar4 = lua_isnil(uVar3);
      if (local_c != 0) {
        iVar5 = lua_isnumber(uVar2);
        if (iVar5 == 0) {
          iVar5 = lua_isnil(uVar2);
          if (iVar5 != 0) {
            uVar7 = Cos_InstCountChores(*(undefined4 *)local_c);
            uVar8 = 0;
            local_8 = 0;
            uVar6 = local_8;
            if (uVar7 != 0) {
              do {
                uVar6 = Cos_InstChoreStatus(*(undefined4 *)local_c,uVar8);
                if (((uVar6 & 1) != 0) &&
                   (((iVar4 != 0 || ((uVar6 & 2) == 0)) && (local_4 = uVar8, (uVar6 & 2) != 0)))) {
                  local_8 = uVar8;
                  lua_pushnumber((float)(int)uVar8);
                  lua_pushnumber(FBITS(0x3f800000));
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
          lua_getnumber();
          lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          uVar6 = Cos_InstChoreStatus(*(undefined4 *)local_c,(int)lVar9);
          if ((uVar6 & 1) != 0) {
            if ((iVar4 == 0) && ((uVar6 & 2) != 0)) {
              return;
            }
            lua_pushobject(uVar2);
            if ((uVar6 & 2) != 0) {
              lua_pushnumber(FBITS(0x3f800000));
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

#endif


/* ---- 0x00499ff0  Lua_GetActorChores ---- */
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: GetActorChores */

void Lua_GetActorChores(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  undefined4 uVar2;
  void *luaObj;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x40 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  luaObj = (void *)lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar2);
  if ((iVar3 != 0) && (iVar3 = lua_tag(uVar2), iVar3 == 0x52544341)) {
    uVar2 = lua_getuserdata(uVar2);
    iVar3 = Actor_FromHandle(uVar2);
    iVar3 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar3 + 0xa0),(void **)&local_18);
    if (iVar3 == 0) {
      return;
    }
    uVar6 = 0;
    if (local_18 != 0) {
      uVar2 = lua_createtable();
      uVar4 = Cos_InstCountChores(*(undefined4 *)local_18);
      local_14 = 0;
      local_c = uVar4;
      if (uVar4 != 0) {
        do {
          uVar5 = Cos_InstChoreStatus(*(undefined4 *)local_18,uVar6);
          if ((uVar5 & 1) != 0) {
            lua_pushobject(uVar2);
            uStack_4 = 0;
            fVar1 = (float)uVar6;
            local_10 = (uint)fVar1;
            local_8 = uVar6;
            lua_pushnumber(fVar1);
            lua_pushnumber(fVar1);
            lua_settable();
            local_14 = local_14 + 1;
            uVar4 = local_c;
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < uVar4);
      }
      lua_pushobject(uVar2);
      lua_pushstring(s_count_004ec384);
      local_8 = local_14;
      uStack_4 = 0;
      lua_pushnumber((float)local_14);
      lua_settable();
      lua_pushobject(uVar2);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_2c
#undef local_8
#undef local_c
#undef uStack_4


/* ---- 0x0049a160  Lua_GetActorCostumeDepth ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: GetActorCostumeDepth */

void Lua_GetActorCostumeDepth(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar3 = 0;
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if ((iVar2 != 0) && (iVar2 = lua_tag(uVar1), iVar2 == 0x52544341)) {
    uVar1 = lua_getuserdata(uVar1);
    iVar2 = Actor_FromHandle(uVar1);
    for (iVar2 = *(int *)(iVar2 + 0xa0); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0xb0)) {
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: GetActorCostume */

void Lua_GetActorCostume(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 *puVar4;
  undefined4 unaff_EDI;
  longlong lVar5;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(uVar1), iVar3 == 0x52544341)) {
    uVar1 = lua_getuserdata(uVar1);
    iVar3 = Actor_FromHandle(uVar1);
    puVar4 = *(undefined4 **)(iVar3 + 0xa0);
    iVar3 = lua_isnil(uVar2);
    if (iVar3 == 0) {
      iVar3 = lua_isnumber(uVar2);
      if (iVar3 == 0) {
        return;
      }
      lua_getnumber(uVar2);
      lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      iVar3 = (int)lVar5;
      if (puVar4 == (undefined4 *)0x0) goto LAB_0049a295;
      do {
        if (iVar3 < 1) break;
        puVar4 = (undefined4 *)puVar4[0x2c];
        iVar3 = iVar3 + -1;
      } while (puVar4 != (undefined4 *)0x0);
    }
    if (puVar4 != (undefined4 *)0x0) {
      uVar1 = Cos_InstGetCostume(*puVar4,0);
      lua_pushstring(uVar1);
      return;
    }
  }
LAB_0049a295:
  lua_pushnil();
  return;
}
#endif


/* ---- 0x0049a2a0  Lua_GetActorLoopingChores ---- */
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: GetActorLoopingChores */

void Lua_GetActorLoopingChores(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  undefined4 uVar2;
  void *luaObj;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x40 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  luaObj = (void *)lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar2);
  if ((iVar3 != 0) && (iVar3 = lua_tag(uVar2), iVar3 == 0x52544341)) {
    uVar2 = lua_getuserdata(uVar2);
    iVar3 = Actor_FromHandle(uVar2);
    iVar3 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar3 + 0xa0),(void **)&local_18);
    if (iVar3 == 0) {
      return;
    }
    uVar6 = 0;
    if (local_18 != 0) {
      uVar2 = lua_createtable();
      uVar4 = Cos_InstCountChores(*(undefined4 *)local_18);
      local_14 = 0;
      local_c = uVar4;
      if (uVar4 != 0) {
        do {
          uVar5 = Cos_InstChoreStatus(*(undefined4 *)local_18,uVar6);
          if (((uVar5 & 1) != 0) && ((uVar5 & 2) != 0)) {
            lua_pushobject(uVar2);
            uStack_4 = 0;
            fVar1 = (float)uVar6;
            local_10 = (uint)fVar1;
            local_8 = uVar6;
            lua_pushnumber(fVar1);
            lua_pushnumber(fVar1);
            lua_settable();
            local_14 = local_14 + 1;
            uVar4 = local_c;
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < uVar4);
      }
      lua_pushobject(uVar2);
      lua_pushstring(s_count_004ec384);
      local_8 = local_14;
      uStack_4 = 0;
      lua_pushnumber((float)local_14);
      lua_settable();
      lua_pushobject(uVar2);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_2c
#undef local_8
#undef local_c
#undef uStack_4


/* ---- 0x0049a410  Lua_SetActorColormap ---- */
/* Source: Scripts/sputLua.cpp (line 2035, from __FILE__/__LINE__ passed to the allocator) */

void Lua_SetActorColormap(void)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  char *name;
  void *data;
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(uVar2);
  if ((iVar4 != 0) && (iVar4 = lua_tag(uVar2), iVar4 == 0x52544341)) {
    uVar2 = lua_getuserdata(uVar2);
    piVar5 = (int *)Actor_FromHandle(uVar2);
    iVar4 = lua_isstring(uVar3);
    if (iVar4 != 0) {
      name = (char *)lua_getstring();
      data = Resource_Load(0x50414d43,name);
      piVar1 = (int *)*piVar5;
      iVar4 = *piVar1;
      if (iVar4 != 0) {
        if (iVar4 == 0) {
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
    iVar4 = lua_isnil(uVar3);
    if (iVar4 != 0) {
      ResRef_Remove((void *)*piVar5);
    }
  }
  return;
}

/* ---- 0x0049a500  Lua_SetActorCostume ---- */
/* Lua opcode: SetActorCostume */

void Lua_SetActorCostume(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  void *actor;
  char *name;
  int iVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar4 = 0;
  iVar3 = lua_isuserdata(uVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(uVar1), iVar3 == 0x52544341)) {
    uVar1 = lua_getuserdata(uVar1);
    actor = (void *)Actor_FromHandle(uVar1);
    iVar3 = lua_isstring(uVar2);
    if (iVar3 == 0) {
      iVar3 = lua_isnil(uVar2);
      if (iVar3 != 0) {
        iVar3 = *(int *)((int)actor + 0xa0);
        while (iVar3 != 0) {
          Actor_PopCostume(actor,1);
          iVar3 = *(int *)((int)actor + 0xa0);
        }
        iVar4 = 1;
      }
    }
    else {
      iVar3 = 0;
      name = (char *)lua_getstring(uVar2);
      iVar4 = Actor_SetCostume(actor,name,iVar3);
    }
    if (iVar4 != 0) {
      lua_pushnumber(FBITS(0x3f800000));
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
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  lua_lua2C(2);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      Costume_PrintList(*(void **)(iVar2 + 0xa0));
    }
  }
  return;
}

/* ---- 0x0049a640  Lua_PushActorCostume ---- */
/* Lua opcode: PushActorCostume */

void Lua_PushActorCostume(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  void *actor;
  char *name;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      actor = (void *)Actor_FromHandle(uVar1);
      iVar3 = lua_isstring(uVar2);
      if (iVar3 != 0) {
        iVar3 = 0;
        name = (char *)lua_getstring(uVar2);
        Actor_PushCostume(actor,name,iVar3);
      }
    }
  }
  return;
}

/* ---- 0x0049a6c0  Lua_PopActorCostume ---- */
/* Lua opcode: PopActorCostume */

void Lua_PopActorCostume(void)

{
  undefined4 uVar1;
  int iVar2;
  void *actor;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      actor = (void *)Actor_FromHandle(uVar1);
      if (*(undefined4 **)((int)actor + 0xa0) != (undefined4 *)0x0) {
        uVar1 = Cos_InstGetCostume(**(undefined4 **)((int)actor + 0xa0),0);
        lua_pushstring(uVar1);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: StopActorChore */

void Lua_StopActorChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  void *luaObj;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar3 = Actor_FromHandle(uVar1);
      iVar3 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar3 + 0xa0),(void **)&local_4);
      if ((iVar3 != 0) && (local_4 != 0)) {
        iVar3 = lua_isnumber(uVar2);
        if (iVar3 != 0) {
          lua_getnumber();
          lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          Cos_InstStopChore(*(undefined4 *)local_4,(int)lVar4);
          return;
        }
        iVar3 = lua_isnil(uVar2);
        if (iVar3 != 0) {
          Cos_InstStopChores(*(undefined4 *)local_4);
        }
      }
    }
  }
  return;
}
#undef local_4

#endif


/* ---- 0x0049a830  Lua_PlayActorChore ---- */
/* Lua opcode: PlayActorChore */

void Lua_PlayActorChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  void *luaObj;
  int iVar3;
  longlong lVar4;
  undefined4 uVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar3 = Actor_FromHandle(uVar1);
      iVar3 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar3 + 0xa0),(void **)&local_4);
      if (iVar3 != 0) {
        if (local_4 != 0) {
          iVar3 = lua_isnumber(uVar2);
          if (iVar3 != 0) {
            uVar5 = 0;
            uVar1 = 0;
            lua_getnumber(uVar2);
            lVar4 = _ftol((double)CONCAT44(uVar5,uVar1));
            iVar3 = Cos_InstPlayChore(*(undefined4 *)local_4,(int)lVar4);
            if (iVar3 != 0) {
              lua_pushnumber(FBITS(0x3f800000));
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: CompleteActorChore */

void Lua_CompleteActorChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  void *luaObj;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar3 = Actor_FromHandle(uVar1);
      iVar3 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar3 + 0xa0),(void **)&local_4);
      if (iVar3 != 0) {
        if (local_4 != 0) {
          iVar3 = lua_isnumber(uVar2);
          if (iVar3 != 0) {
            lua_getnumber(uVar2);
            lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
            iVar3 = Cos_InstCompleteChore(*(undefined4 *)local_4,(int)lVar4);
            if (iVar3 != 0) {
              lua_pushnumber(FBITS(0x3f800000));
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

#endif


/* ---- 0x0049a9e0  Lua_PlayActorChoreLooping ---- */
/* Lua opcode: PlayActorChoreLooping */

void Lua_PlayActorChoreLooping(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  void *luaObj;
  int iVar3;
  longlong lVar4;
  undefined4 uVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar3 = Actor_FromHandle(uVar1);
      iVar3 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar3 + 0xa0),(void **)&local_4);
      if (iVar3 != 0) {
        if (local_4 != 0) {
          iVar3 = lua_isnumber(uVar2);
          if (iVar3 != 0) {
            uVar5 = 0;
            uVar1 = 1;
            lua_getnumber(uVar2);
            lVar4 = _ftol((double)CONCAT44(uVar5,uVar1));
            iVar3 = Cos_InstPlayChore(*(undefined4 *)local_4,(int)lVar4);
            if (iVar3 != 0) {
              lua_pushnumber(FBITS(0x3f800000));
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
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar3 = lua_lua2C(1);
  uVar4 = lua_lua2C(2);
  uVar5 = lua_lua2C(3);
  lua_lua2C(4);
  uVar6 = lua_lua2C(5);
  iVar7 = lua_isuserdata(uVar3);
  if ((iVar7 != 0) && (iVar7 = lua_tag(uVar3), iVar7 == 0x52544341)) {
    uVar3 = lua_getuserdata(uVar3);
    iVar7 = Actor_FromHandle(uVar3);
    if (*(int *)(iVar7 + 0xa4) == 0) {
      Actor_CreateExtra(iVar7);
    }
    if (*(int *)(iVar7 + 0xa0) != 0) {
      iVar8 = lua_isnumber(uVar6);
      if (iVar8 != 0) {
        fVar9 = (float10)lua_getnumber(uVar6);
        *(float *)(*(int *)(iVar7 + 0xa0) + 0x18) = (float)fVar9;
      }
      iVar8 = lua_isnil(uVar4);
      if (iVar8 == 0) {
        iVar8 = lua_isnumber(uVar4);
        if (iVar8 != 0) {
          uVar3 = lua_lua2C(3);
          uVar5 = lua_lua2C(4);
          fVar9 = (float10)lua_getnumber(uVar4);
          **(float **)(iVar7 + 0xa4) = (float)fVar9;
          iVar8 = lua_isnumber(uVar3);
          if (iVar8 == 0) {
            fVar9 = (float10)0.0;
          }
          else {
            fVar9 = (float10)lua_getnumber(uVar3);
          }
          *(float *)(*(int *)(iVar7 + 0xa4) + 4) = (float)fVar9;
          iVar8 = lua_isnumber(uVar5);
          if (iVar8 != 0) {
            fVar9 = (float10)lua_getnumber(uVar5);
            *(float *)(*(int *)(iVar7 + 0xa4) + 8) = (float)fVar9;
            *(uint *)(iVar7 + 8) = *(uint *)(iVar7 + 8) | 2;
            return;
          }
          *(undefined4 *)(*(int *)(iVar7 + 0xa4) + 8) = 0;
          *(uint *)(iVar7 + 8) = *(uint *)(iVar7 + 8) | 2;
          return;
        }
        iVar8 = lua_isuserdata(uVar4);
        if (iVar8 == 0) {
          return;
        }
        iVar8 = lua_tag(uVar4);
        if (iVar8 != 0x52544341) {
          return;
        }
        uVar3 = lua_getuserdata(uVar4);
        iVar8 = Actor_FromHandle(uVar3);
        puVar2 = *(undefined4 **)(iVar7 + 0xa4);
        *puVar2 = *(undefined4 *)(iVar8 + 0xc);
        puVar2[1] = *(undefined4 *)(iVar8 + 0x10);
        puVar2[2] = *(undefined4 *)(iVar8 + 0x14);
        iVar8 = lua_isnumber(uVar5);
        if (iVar8 != 0) {
          fVar9 = (float10)lua_getnumber(uVar5);
          *(float *)(*(int *)(iVar7 + 0xa0) + 0x18) = (float)fVar9;
        }
      }
      else {
        pfVar1 = *(float **)(iVar7 + 0xa4);
        if (((*pfVar1 == 0.0) && (pfVar1[1] == 0.0)) && (pfVar1[2] == 0.0)) {
          return;
        }
        *pfVar1 = 0.0;
        pfVar1[1] = 0.0;
        pfVar1[2] = 0.0;
        iVar8 = lua_isnumber(uVar5);
        if (iVar8 != 0) {
          fVar9 = (float10)lua_getnumber(uVar5);
          *(float *)(*(int *)(iVar7 + 0xa0) + 0x18) = (float)fVar9;
          *(uint *)(iVar7 + 8) = *(uint *)(iVar7 + 8) | 2;
          return;
        }
      }
      *(uint *)(iVar7 + 8) = *(uint *)(iVar7 + 8) | 2;
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
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      if ((*(byte *)(iVar2 + 8) & 2) != 0) {
        lua_pushnumber(FBITS(0x3f800000));
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
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(uVar2);
      if (iVar3 != 0) {
        uVar1 = lua_getuserdata(uVar1);
        iVar3 = Actor_FromHandle(uVar1);
        if (*(int *)(iVar3 + 0xa0) != 0) {
          fVar4 = (float10)lua_getnumber(uVar2);
          *(float *)(*(int *)(iVar3 + 0xa0) + 0x18) = (float)fVar4;
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
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      if (*(int *)(iVar2 + 0xa0) != 0) {
        lua_pushnumber(*(undefined4 *)(*(int *)(iVar2 + 0xa0) + 0x18));
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
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar3 = Actor_FromHandle(uVar1);
      if (iVar2 != 0) {
        iVar2 = lua_isnil(iVar2);
        if (iVar2 == 0) {
          *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xfffffffd;
          return;
        }
      }
      *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 2;
    }
  }
  return;
}

/* ---- 0x0049af00  Lua_SetActorFollowBoxes ---- */
/* Lua opcode: SetActorFollowBoxes */

void Lua_SetActorFollowBoxes(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar4 = 1;
  uVar1 = lua_lua2C(1);
  iVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 == 0) {
    return;
  }
  iVar3 = lua_tag(uVar1);
  if (iVar3 == 0x52544341) {
    uVar1 = lua_getuserdata(uVar1);
    uVar1 = Actor_FromHandle(uVar1);
    if ((iVar2 == 0) || (iVar2 = lua_isnil(iVar2), iVar2 != 0)) {
      uVar4 = 0;
    }
    Actor_SetFollowBoxes(uVar1,uVar4);
    return;
  }
  return;
}

/* ---- 0x0049af80  Lua_ShutUpActor ---- */
/* Lua opcode: ShutUpActor */

void Lua_ShutUpActor(void)

{
  undefined4 uVar1;
  int iVar2;
  void *actor;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      actor = (void *)Actor_FromHandle(uVar1);
      if (actor != (void *)0x0) {
        Actor_ShutUp(actor);
      }
    }
  }
  return;
}

/* ---- 0x0049afd0  Lua_SetActorFrustrumCull ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetActorFrustrumCull */

void Lua_SetActorFrustrumCull(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      uVar1 = Actor_FromHandle(uVar1);
      lua_getnumber(uVar2);
      lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      Actor_SetFrustumCull(uVar1,(int)lVar4);
    }
  }
  return;
}
#endif


/* ---- 0x0049b040  Lua_GetCameraActor ---- */
/* Lua opcode: GetCameraActor */

void Lua_GetCameraActor(void)

{
  lua_pushusertag(g_nCameraActor,0x52544341);
  return;
}

/* ---- 0x0049b060  Lua_GetActorWalkRate ---- */
/* Lua opcode: GetActorWalkRate */

void Lua_GetActorWalkRate(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      if (*(int *)(iVar2 + 0xa4) == 0) {
        Actor_CreateExtra(iVar2);
      }
      lua_pushnumber(*(undefined4 *)(*(int *)(iVar2 + 0xa4) + 0x18));
    }
  }
  return;
}

/* ---- 0x0049b0d0  Lua_SetActorWalkRate ---- */
/* Lua opcode: SetActorWalkRate */

void Lua_SetActorWalkRate(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(uVar2);
      if (iVar3 != 0) {
        uVar1 = lua_getuserdata(uVar1);
        iVar3 = Actor_FromHandle(uVar1);
        if (*(int *)(iVar3 + 0xa4) == 0) {
          Actor_CreateExtra(iVar3);
        }
        fVar4 = (float10)lua_getnumber(uVar2);
        *(float *)(*(int *)(iVar3 + 0xa4) + 0x18) = (float)fVar4;
      }
    }
  }
  return;
}

/* ---- 0x0049b160  Lua_GetActorTurnRate ---- */
/* Lua opcode: GetActorTurnRate */

void Lua_GetActorTurnRate(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      if (*(int *)(iVar2 + 0xa4) == 0) {
        Actor_CreateExtra(iVar2);
      }
      lua_pushnumber(*(undefined4 *)(*(int *)(iVar2 + 0xa4) + 0x1c));
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
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(uVar2);
  if (iVar4 != 0) {
    iVar4 = lua_tag(uVar2);
    if (iVar4 == 0x52544341) {
      iVar4 = lua_isnumber(uVar3);
      if (iVar4 != 0) {
        fVar5 = (float10)lua_getnumber(uVar3);
        fVar1 = (float)fVar5;
        uVar2 = lua_getuserdata(uVar2);
        iVar4 = Actor_FromHandle(uVar2);
        if (*(int *)(iVar4 + 0xa4) == 0) {
          Actor_CreateExtra(iVar4);
        }
        if (*(float *)(*(int *)(iVar4 + 0xa4) + 0x1c) < 0.0) {
          fVar1 = fVar1 * -1.0;
        }
        *(float *)(*(int *)(iVar4 + 0xa4) + 0x1c) = fVar1;
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x0049b280  Lua_SetActorWalkChore ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetActorWalkChore */

void Lua_SetActorWalkChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  void *luaObj;
  int iVar3;
  void *actor;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(uVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(uVar1), iVar3 == 0x52544341)) {
    iVar3 = lua_isnumber(uVar2);
    if ((iVar3 == 0) && (iVar3 = lua_isnil(uVar2), iVar3 == 0)) {
      return;
    }
    uVar1 = lua_getuserdata(uVar1);
    actor = (void *)Actor_FromHandle(uVar1);
    iVar3 = Lua_ResolveCostumeArg(luaObj,*(void **)((int)actor + 0xa0),(void **)&local_4);
    if (iVar3 != 0) {
      iVar3 = lua_isnumber(uVar2);
      if (iVar3 == 0) {
        iVar3 = -1;
      }
      else {
        lua_getnumber(uVar2);
        lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        iVar3 = (int)lVar4;
      }
      Actor_SetWalkChore(actor,iVar3,(void *)local_4);
    }
  }
  return;
}
#undef local_4

#endif


/* ---- 0x0049b350  Lua_SetActorTurnChores ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetActorTurnChores */

void Lua_SetActorTurnChores(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *luaObj;
  int iVar4;
  void *actor;
  undefined4 unaff_EDI;
  longlong lVar5;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  luaObj = (void *)lua_lua2C(4);
  iVar4 = lua_isuserdata(uVar1);
  if (iVar4 != 0) {
    iVar4 = lua_tag(uVar1);
    if (iVar4 == 0x52544341) {
      iVar4 = lua_isnumber(uVar2);
      if (iVar4 != 0) {
        iVar4 = lua_isnumber(uVar3);
        if (iVar4 != 0) {
          uVar1 = lua_getuserdata(uVar1);
          actor = (void *)Actor_FromHandle(uVar1);
          iVar4 = Lua_ResolveCostumeArg(luaObj,*(void **)((int)actor + 0xa0),(void **)&local_4);
          if (iVar4 != 0) {
            lua_getnumber(uVar3);
            lVar5 = _ftol((double)CONCAT44(unaff_EDI,local_4));
            iVar4 = (int)lVar5;
            lua_getnumber(uVar2);
            lVar5 = _ftol((double)CONCAT44(local_4,iVar4));
            Actor_SetTurnChores(actor,(int)lVar5,iVar4,(void *)local_4);
          }
        }
      }
    }
  }
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x0049b430  Lua_SetActorRestChore ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetActorRestChore */

void Lua_SetActorRestChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  void *luaObj;
  int iVar3;
  void *actor;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(uVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(uVar1), iVar3 == 0x52544341)) {
    iVar3 = lua_isnumber(uVar2);
    if ((iVar3 == 0) && (iVar3 = lua_isnil(uVar2), iVar3 == 0)) {
      return;
    }
    uVar1 = lua_getuserdata(uVar1);
    actor = (void *)Actor_FromHandle(uVar1);
    iVar3 = Lua_ResolveCostumeArg(luaObj,*(void **)((int)actor + 0xa0),(void **)&local_4);
    if (iVar3 != 0) {
      iVar3 = lua_isnil(uVar2);
      if (iVar3 == 0) {
        lua_getnumber(uVar2);
        lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        iVar3 = (int)lVar4;
      }
      else {
        iVar3 = -1;
      }
      Actor_SetRestChore(actor,iVar3,(void *)local_4);
    }
  }
  return;
}
#undef local_4

#endif


/* ---- 0x0049b500  Lua_SetActorMumblechore ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetActorMumblechore */

void Lua_SetActorMumblechore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  void *luaObj;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  luaObj = (void *)lua_lua2C(3);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(uVar2);
      if (iVar3 != 0) {
        lua_getnumber(uVar2);
        lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        uVar1 = lua_getuserdata(uVar1);
        iVar3 = Actor_FromHandle(uVar1);
        iVar3 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar3 + 0xa0),(void **)&local_4);
        if ((iVar3 != 0) && (local_4 != 0)) {
          *(int *)(local_4 + 0x78) = (int)lVar4;
        }
      }
    }
  }
  return;
}
#undef local_4

#endif


/* ---- 0x0049b5a0  Lua_SetActorTalkChore ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetActorTalkChore */

void Lua_SetActorTalkChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *luaObj;
  int iVar4;
  int iVar5;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  luaObj = (void *)lua_lua2C(4);
  iVar4 = lua_isuserdata(uVar1);
  if (((iVar4 != 0) && (iVar4 = lua_tag(uVar1), iVar4 == 0x52544341)) &&
     (iVar4 = lua_isnumber(uVar2), iVar4 != 0)) {
    iVar4 = lua_isnumber(uVar3);
    if ((iVar4 == 0) && (iVar4 = lua_isnil(uVar3), iVar4 == 0)) {
      return;
    }
    lua_getnumber(uVar2);
    lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar4 = (int)lVar6;
    if ((0 < iVar4) && (iVar4 < 0x11)) {
      uVar1 = lua_getuserdata(uVar1);
      iVar5 = Actor_FromHandle(uVar1);
      iVar5 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar5 + 0xa0),(void **)&local_4);
      if ((iVar5 != 0) && (local_4 != 0)) {
        iVar5 = lua_isnumber(uVar3);
        if (iVar5 == 0) {
          uVar1 = 0xffffffff;
        }
        else {
          lua_getnumber(uVar3);
          lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          uVar1 = (undefined4)lVar6;
        }
        *(undefined4 *)(local_4 + 0x34 + iVar4 * 4) = uVar1;
        lua_isnil(uVar3);
      }
    }
  }
  return;
}
#undef local_4

#endif


/* ---- 0x0049b6c0  Lua_SetActorHead ---- */
/* WARNING: Variable defined which should be unmapped: local_24 */
/* WARNING: Variable defined which should be unmapped: local_28 */
/* WARNING: Variable defined which should be unmapped: local_2c */
/* Lua opcode: SetActorHead */

void Lua_SetActorHead(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float maxRoll;
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  void *actor;
  int joint2;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  longlong lVar12;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  uVar5 = lua_lua2C(5);
  uVar6 = lua_lua2C(6);
  uVar7 = lua_lua2C(7);
  iVar8 = lua_isuserdata(uVar1);
  if (iVar8 != 0) {
    iVar8 = lua_tag(uVar1);
    if (iVar8 == 0x52544341) {
      iVar8 = lua_isnumber(uVar2);
      if (iVar8 != 0) {
        iVar8 = lua_isnumber(uVar3);
        if (iVar8 != 0) {
          iVar8 = lua_isnumber(uVar4);
          if (iVar8 != 0) {
            iVar8 = lua_isnumber(uVar5);
            if (iVar8 != 0) {
              iVar8 = lua_isnumber(uVar6);
              if (iVar8 != 0) {
                iVar8 = lua_isnumber(uVar7);
                if (iVar8 != 0) {
                  uVar1 = lua_getuserdata(uVar1);
                  actor = (void *)Actor_FromHandle(uVar1);
                  fVar9 = (float10)lua_getnumber(uVar7);
                  fVar10 = (float10)lua_getnumber(uVar6);
                  fVar11 = (float10)lua_getnumber(uVar5);
                  maxRoll = (float)fVar11;
                  lua_getnumber(uVar4);
                  lVar12 = _ftol((double)CONCAT44((float)fVar10,maxRoll));
                  iVar8 = (int)lVar12;
                  lua_getnumber(uVar3);
                  lVar12 = _ftol((double)CONCAT44(maxRoll,iVar8));
                  joint2 = (int)lVar12;
                  lua_getnumber(uVar2);
                  lVar12 = _ftol((double)CONCAT44(iVar8,joint2));
                  Actor_SetHead(actor,(int)lVar12,joint2,iVar8,maxRoll,(float)fVar10,(float)fVar9);
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
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  void *target;
  undefined4 uVar4;
  void *target_00;
  float10 fVar5;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 == 0) {
    return;
  }
  iVar3 = lua_tag(uVar1);
  if (iVar3 != 0x52544341) {
    return;
  }
  uVar1 = lua_getuserdata(uVar1);
  target = (void *)Actor_FromHandle(uVar1);
  local_10 = (uint)target;
  iVar3 = lua_isnumber(uVar2);
  if (iVar3 == 0) {
    iVar3 = lua_isuserdata(uVar2);
    if ((iVar3 == 0) || (iVar3 = lua_tag(uVar2), iVar3 != 0x52544341)) {
      iVar3 = lua_isnil(uVar2);
      if (iVar3 == 0) {
        return;
      }
      if (g_pSelectedActor == (void *)0x0) {
        return;
      }
      iVar3 = Actor_CanSee(g_pSelectedActor,target,(float *)&local_14);
      if (iVar3 != 0) {
        lua_pushnumber(local_14);
        return;
      }
    }
    else {
      uVar1 = lua_getuserdata(uVar2);
      target_00 = (void *)Actor_FromHandle(uVar1);
      iVar3 = Actor_CanSee(target,target_00,(float *)&local_14);
      if (iVar3 != 0) {
        lua_pushnumber(local_14);
        return;
      }
    }
  }
  else {
    uVar1 = lua_lua2C(3);
    uVar4 = lua_lua2C(4);
    fVar5 = (float10)lua_getnumber(uVar2);
    local_c = (uint)(float)fVar5;
    iVar3 = lua_isnumber(uVar1);
    if (iVar3 == 0) {
      local_8 = 0;
    }
    else {
      fVar5 = (float10)lua_getnumber(uVar1);
      local_8 = (uint)(float)fVar5;
    }
    iVar3 = lua_isnumber(uVar4);
    if (iVar3 == 0) {
      local_4 = 0;
    }
    else {
      fVar5 = (float10)lua_getnumber(uVar4);
      local_4 = (uint)(float)fVar5;
    }
    iVar3 = Actor_CanSeePoint((void *)local_10,(float *)&local_c,(float *)&local_14);
    if (iVar3 != 0) {
      lua_pushnumber(local_14);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0049b9e0  Lua_GetVisibleThings ---- */
/* Lua opcode: GetVisibleThings */

void Lua_GetVisibleThings(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *target;
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(uVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isuserdata(uVar1);
    if ((iVar2 != 0) && (iVar2 = lua_tag(uVar1), iVar2 == 0x52544341)) {
      uVar1 = lua_getuserdata(uVar1);
      local_8 = Actor_FromHandle(uVar1);
    }
  }
  else {
    local_8 = (uint)g_pSelectedActor;
    if (g_pSelectedActor == (void *)0x0) {
      return;
    }
  }
  uVar1 = lua_createtable();
  if (*(char *)(local_8 + 0x7c) == '\0') {
    lua_pushobject(uVar1);
  }
  for (piVar3 = Set_GetActorListByName((char *)(local_8 + 0x7c)); piVar3 != (int *)0x0;
      piVar3 = (int *)piVar3[2]) {
    target = (void *)((int)g_pActorTable + *piVar3 * 0xa8);
    if ((((target != (void *)0x0) && (target != (void *)local_8)) &&
        ((*(byte *)(local_8 + 4) & 1) == 0)) &&
       (iVar2 = Actor_CanSee((void *)local_8,target,&local_4), iVar2 != 0)) {
      lua_pushobject(uVar1);
      iVar2 = Actor_GetHandle(target,0x52544341);
      lua_pushusertag(iVar2);
      lua_pushnumber(FBITS(0x3f800000));
      lua_settable();
    }
  }
  lua_pushobject(uVar1);
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
  undefined4 uVar1;
  int iVar2;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      if ((iVar2 != 0) && (*(int *)(iVar2 + 0x68) != 0)) {
        lua_pushnumber((float)*(int *)(iVar2 + 0x6c));
        lua_pushnumber((float)*(int *)(iVar2 + 0x70));
        lua_pushnumber((float)*(int *)(iVar2 + 0x74));
        lua_pushnumber((float)*(int *)(iVar2 + 0x78));
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
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(uVar2);
  if ((iVar4 != 0) && (iVar4 = lua_tag(uVar2), iVar4 == 0x52544341)) {
    iVar4 = lua_isnil(uVar3);
    uVar2 = lua_getuserdata(uVar2);
    iVar5 = Actor_FromHandle(uVar2);
    if (*(int *)(iVar5 + 0xa4) == 0) {
      Actor_CreateExtra(iVar5);
    }
    if ((iVar5 != 0) &&
       (pfVar1 = *(float **)(*(int *)(iVar5 + 0xa4) + 0x1b4), pfVar1 != (float *)0x0)) {
      local_c = (uint)pfVar1[6];
      local_8 = (uint)pfVar1[7];
      local_4 = (uint)pfVar1[8];
      if (iVar4 == 0) {
        local_c = (uint)((float)local_c + *pfVar1);
        local_8 = (uint)(pfVar1[1] + (float)local_8);
        local_4 = (uint)(pfVar1[2] + (float)local_4);
      }
      lua_pushnumber(local_c);
      lua_pushnumber(local_8);
      lua_pushnumber(local_4);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0049bcc0  Lua_GetActorYawToPoint ---- */
/* Lua opcode: GetActorYawToPoint(actor, x, y, z | {x, y, z}). Creates the extra and the walker if
   missing, then returns Actor_GetYawToPoint. */

void Lua_GetActorYawToPoint(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float10 fVar7;
  float fVar8;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar3 = Actor_FromHandle(uVar1);
      iVar4 = lua_istable(uVar2);
      if (iVar4 == 0) {
        uVar1 = lua_lua2C(3);
        uVar6 = lua_lua2C(4);
      }
      else {
        lua_pushobject(uVar2);
        lua_pushstring(&DAT_004e8454);
        uVar5 = lua_gettable();
        lua_pushobject(uVar2);
        lua_pushstring(&DAT_004e8450);
        uVar1 = lua_gettable();
        lua_pushobject(uVar2);
        lua_pushstring(&DAT_004ec3b8);
        uVar6 = lua_gettable();
        uVar2 = uVar5;
      }
      fVar7 = (float10)lua_getnumber(uVar2);
      local_c = (uint)(float)fVar7;
      fVar7 = (float10)lua_getnumber(uVar1);
      local_8 = (uint)(float)fVar7;
      fVar7 = (float10)lua_getnumber(uVar6);
      local_4 = (uint)(float)fVar7;
      if (*(int *)(iVar3 + 0xa4) == 0) {
        Actor_CreateExtra(iVar3);
      }
      if (*(int *)(*(int *)(iVar3 + 0xa4) + 0x1b4) == 0) {
        Actor_CreateWalker(iVar3,1);
      }
      fVar8 = Actor_GetYawToPoint(*(void **)(*(int *)(iVar3 + 0xa4) + 0x1b4),(int)&local_c);
      lua_pushnumber(fVar8);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0049be40  Lua_SetActorReflection ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: SetActorReflection */

void Lua_SetActorReflection(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  void *actor;
  float10 fVar4;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      actor = (void *)Actor_FromHandle(uVar1);
      fVar4 = (float10)lua_getnumber(uVar2);
      Actor_SetReflection(actor,(float)fVar4);
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
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      lua_pushnumber(*(undefined4 *)(iVar2 + 0xc));
      lua_pushnumber(*(undefined4 *)(iVar2 + 0x10));
      lua_pushnumber(*(undefined4 *)(iVar2 + 0x14));
    }
  }
  return;
}

/* ---- 0x0049bf30  Lua_GetActorRot ---- */
/* Lua opcode: GetActorRot */

void Lua_GetActorRot(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      lua_pushnumber(*(undefined4 *)(iVar2 + 0x24));
      lua_pushnumber(*(undefined4 *)(iVar2 + 0x28));
      lua_pushnumber(*(undefined4 *)(iVar2 + 0x2c));
    }
  }
  return;
}

/* ---- 0x0049bfa0  Lua_SetActorRot ---- */
/* Lua opcode: SetActorRot */

void Lua_SetActorRot(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  float10 fVar7;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  uVar5 = lua_lua2C(5);
  iVar6 = lua_isuserdata(uVar1);
  if (iVar6 != 0) {
    iVar6 = lua_tag(uVar1);
    if (iVar6 == 0x52544341) {
      iVar6 = lua_isnumber(uVar2);
      if (iVar6 != 0) {
        iVar6 = lua_isnumber(uVar3);
        if (iVar6 != 0) {
          iVar6 = lua_isnumber(uVar4);
          if (iVar6 != 0) {
            uVar1 = lua_getuserdata(uVar1);
            uVar1 = Actor_FromHandle(uVar1);
            fVar7 = (float10)lua_getnumber(uVar2);
            local_c = (uint)(float)fVar7;
            fVar7 = (float10)lua_getnumber(uVar3);
            local_8 = (uint)(float)fVar7;
            fVar7 = (float10)lua_getnumber(uVar4);
            local_4 = (uint)(float)fVar7;
            uVar2 = lua_isnil(uVar5);
            Actor_SetRot(uVar1,&local_c,uVar2);
          }
        }
      }
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0049c0a0  Lua_SetActorPitch ---- */
/* Lua opcode: SetActorPitch */

void Lua_SetActorPitch(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar3 = Actor_FromHandle(uVar1);
      fVar4 = (float10)lua_getnumber(uVar2);
      *(float *)(iVar3 + 0x24) = (float)fVar4;
      *(undefined4 *)(iVar3 + 0x34) = 0;
    }
  }
  return;
}

/* ---- 0x0049c110  Lua_SetActorRoll ---- */
/* Lua opcode: SetActorRoll */

void Lua_SetActorRoll(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar3 = Actor_FromHandle(uVar1);
      fVar4 = (float10)lua_getnumber(uVar2);
      *(float *)(iVar3 + 0x2c) = (float)fVar4;
      *(undefined4 *)(iVar3 + 0x34) = 0;
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
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(uVar2);
      if (iVar3 != 0) {
        uVar1 = lua_getuserdata(uVar1);
        iVar3 = Actor_FromHandle(uVar1);
        *(uint *)(iVar3 + 8) = *(uint *)(iVar3 + 8) & 0xfffffffe;
        fVar4 = (float10)lua_getnumber(uVar2);
        Actor_TurnKey(iVar3,(float)fVar4);
      }
    }
  }
  return;
}
#undef local_c


/* ---- 0x0049c200  Lua_GetActorSector ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetActorSector */

void Lua_GetActorSector(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnumber(uVar2);
      if (iVar3 != 0) {
        uVar1 = lua_getuserdata(uVar1);
        iVar3 = Actor_FromHandle(uVar1);
        lua_getnumber(uVar2);
        lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        iVar3 = SectorList_FindByPoint(iVar3 + 0xc,(int)lVar4);
        if (iVar3 != 0) {
          lua_pushnumber((float)*(int *)(iVar3 + 0x20));
          lua_pushstring(iVar3);
          lua_pushnumber((float)*(int *)(iVar3 + 0x24));
          return;
        }
        lua_pushnil();
      }
    }
  }
  return;
}
#undef local_c

#endif


/* ---- 0x0049c2c0  Lua_IsActorInSector ---- */
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: IsActorInSector */

void Lua_IsActorInSector(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  void *this;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isstring(uVar2);
      if (iVar3 != 0) {
        uVar1 = lua_getuserdata(uVar1);
        iVar3 = Actor_FromHandle(uVar1);
        uVar1 = lua_getstring(uVar2);
        this = g_pSectorList;
        if (g_pSectorList != (void *)0x0) {
          do {
            iVar4 = String_ContainsSubstring(this,uVar1);
            if (iVar4 != 0) {
              iVar4 = Sector_ContainsPoint(this,(float *)(iVar3 + 0xc),1);
              if (iVar4 != 0) {
                lua_pushnumber((float)*(int *)((int)this + 0x20));
                lua_pushstring(this);
                lua_pushnumber((float)*(int *)((int)this + 0x24));
                return;
              }
            }
            this = *(void **)((int)this + 0x70);
          } while (this != (void *)0x0);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_24 */
/* Lua opcode: GetPointSector */

void Lua_GetPointSector(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  float10 fVar6;
  longlong lVar7;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  iVar5 = lua_isnumber(uVar1);
  if (iVar5 != 0) {
    iVar5 = lua_isnumber(uVar2);
    if (iVar5 != 0) {
      iVar5 = lua_isnumber(uVar3);
      if (iVar5 != 0) {
        iVar5 = lua_isnil(uVar4);
        if (iVar5 == 0) {
          lua_getnumber(uVar4);
          lVar7 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          uVar4 = (undefined4)lVar7;
        }
        else {
          uVar4 = 0x1000;
        }
        fVar6 = (float10)lua_getnumber(uVar1);
        local_c = (uint)(float)fVar6;
        fVar6 = (float10)lua_getnumber(uVar2);
        local_8 = (uint)(float)fVar6;
        fVar6 = (float10)lua_getnumber(uVar3);
        local_4 = (uint)(float)fVar6;
        iVar5 = SectorList_FindByPoint(&local_c,uVar4);
        if (iVar5 != 0) {
          lua_pushnumber((float)*(int *)(iVar5 + 0x20));
          lua_pushstring(iVar5);
          lua_pushnumber((float)*(int *)(iVar5 + 0x24));
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
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x0049c4c0  Lua_IsPointInSector ---- */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: IsPointInSector */

void Lua_IsPointInSector(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  void *this;
  float10 fVar6;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  iVar5 = lua_isnumber(uVar1);
  if ((((iVar5 != 0) && (iVar5 = lua_isnumber(uVar2), iVar5 != 0)) &&
      (iVar5 = lua_isnumber(uVar3), iVar5 != 0)) && (iVar5 = lua_isstring(uVar4), iVar5 != 0)) {
    fVar6 = (float10)lua_getnumber(uVar1);
    local_c = (uint)(float)fVar6;
    fVar6 = (float10)lua_getnumber(uVar2);
    local_8 = (uint)(float)fVar6;
    fVar6 = (float10)lua_getnumber(uVar3);
    local_4 = (uint)(float)fVar6;
    uVar1 = lua_getstring(uVar4);
    this = g_pSectorList;
    if (g_pSectorList != (void *)0x0) {
      do {
        iVar5 = String_ContainsSubstring(this,uVar1);
        if ((iVar5 != 0) && (iVar5 = Sector_ContainsPoint(this,(float *)&local_c,1), iVar5 != 0)) {
          lua_pushnumber((float)*(int *)((int)this + 0x20));
          lua_pushstring(this);
          lua_pushnumber((float)*(int *)((int)this + 0x24));
          break;
        }
        this = *(void **)((int)this + 0x70);
      } while (this != (void *)0x0);
      if (this != (void *)0x0) {
        return;
      }
    }
  }
  lua_pushnil();
  return;
}
#undef local_20
#undef local_4
#undef local_8
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
  undefined4 uVar1;
  int iVar2;
  
  if (flag == 0) {
    lua_pushnil();
  }
  else {
    lua_pushnumber(FBITS(0x3f800000));
  }
  if (str == (char *)0x0) {
    lua_pushnil();
  }
  else {
    lua_pushstring(str);
  }
  uVar1 = lua_getglobal(&DAT_004ec3c8);
  iVar2 = lua_callfunction(uVar1);
  return (uint)(iVar2 == 0);
}

/* ---- 0x0049c660  Lua_CallCamChangeHandler ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* system.camChangeHandler(from, to) */

void __cdecl Lua_CallCamChangeHandler(int fromSetup,int toSetup)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  lua_beginblock();
  uVar1 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar1);
  lua_pushstring(s_camChangeHandler_004ec3d0);
  uVar1 = lua_gettable();
  iVar2 = lua_isfunction(uVar1);
  if (iVar2 != 0) {
    lua_pushnumber((float)fromSetup);
    lua_pushnumber((float)toSetup);
    lua_callfunction(uVar1);
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
  undefined4 uVar1;
  int iVar2;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  lua_beginblock();
  uVar1 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar1);
  lua_pushstring(s_postCamChangeHandler_004ec3e4);
  uVar1 = lua_gettable();
  iVar2 = lua_isfunction(uVar1);
  if (iVar2 != 0) {
    lua_pushnumber((float)setup);
    lua_callfunction(uVar1);
  }
  lua_endblock();
  return;
}
#undef local_8


/* ---- 0x0049c8f0  Lua_UpdateFrame ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* Per frame: stores system.frameTime and system.movieTime, collects garbage every 10 s, runs
   lua_updatetasks */

void Lua_UpdateFrame(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  undefined4 uVar2;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  
  g_dwMovieTime = Insane_Poll();
  uVar1 = Timer_GetFrameMs();
  g_dwLuaGcTimerMs = g_dwLuaGcTimerMs + uVar1;
  if (10000.0 < (float)g_dwLuaGcTimerMs) {
    lua_collectgarbage(0);
    g_dwLuaGcTimerMs = 0;
  }
  lua_beginblock();
  uVar2 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar2);
  lua_pushstring(s_frameTime_004ec41c);
  lua_pushnumber((float)uVar1);
  lua_settable();
  uVar2 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar2);
  lua_pushstring(s_movieTime_004ec410);
  lua_pushnumber((float)(int)g_dwMovieTime);
  lua_settable();
  lua_endblock();
  lua_updatetasks(0);
  return;
}
#undef local_1c


/* ---- 0x0049ca60  Lua_OpenEngineLib ---- */
/* lua_openlib() wrapper used to register the 279-entry engine opcode table at 0x004ea8b0 */

void Lua_OpenEngineLib(undefined4 param_1,undefined4 param_2)

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
    lua_pushnumber(FBITS(0x3f800000));
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
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    lua_tag(uVar1);
  }
  uVar1 = lua_getuserdata(uVar1);
  iVar3 = Actor_FromHandle(uVar1);
  iVar4 = lua_isnil(uVar2);
  if (iVar4 != 0) {
    *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xfffffff7;
    return;
  }
  *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 8;
  return;
}

/* ---- 0x0049cb10  Lua_ResolveCostumeArg ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Turns the optional costume argument of the chore opcodes (nil, index or name) into the costume
   record in the actor's list */

int __cdecl Lua_ResolveCostumeArg(void *luaObj,void *costumeList,void **outCostume)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  
  *outCostume = costumeList;
  iVar2 = lua_isnil(luaObj);
  if (iVar2 != 0) {
    return 1;
  }
  iVar2 = lua_isnumber(luaObj);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(luaObj);
    if (iVar2 == 0) {
      return 0;
    }
    uVar3 = lua_getstring(luaObj);
    pvVar1 = *outCostume;
    while (pvVar1 != (void *)0x0) {
      uVar4 = Cos_InstGetCostume(*(undefined4 *)*outCostume,0,uVar3);
      iVar2 = ((code *)_stricmp)(uVar4);
      if (iVar2 == 0) break;
      pvVar1 = *(void **)((int)*outCostume + 0xb0);
      *outCostume = pvVar1;
    }
  }
  else {
    lua_getnumber();
    lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
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
#endif


/* ---- 0x0049cbe0  Lua_FunctionName ---- */
/* Lua opcode: FunctionName */

void Lua_FunctionName(void)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined4 uVar2;
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
  uVar2 = lua_lua2C(1);
  iVar5 = lua_isfunction(uVar2);
  if (iVar5 != 0) {
    lua_funcinfo(uVar2,&local_108,&local_10c);
    pcVar3 = (char *)lua_getobjname(uVar2,&local_104);
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
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = lua_lua2C(1);
  iVar3 = lua_isstring(uVar2);
  if (iVar3 != 0) {
    ppvVar1 = &g_pSvcLua->pFopen;
    uVar2 = lua_getstring(uVar2,&DAT_004dda54);
    iVar3 = (*(code *)*ppvVar1)(uVar2);
    if (iVar3 == 0) {
      lua_pushnil();
      return;
    }
    (*g_pSvcLua->pFclose)(iVar3);
    lua_pushnumber(FBITS(0x3f800000));
  }
  return;
}

/* ---- 0x0049cd10  Lua_NukeResources ---- */
/* Lua opcode: NukeResources */

void Lua_NukeResources(void)

{
  Set_SetCurrent((void *)0x0);
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
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  char *caption;
  char *text;
  uint flags;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  uVar4 = lua_lua2C(3);
  iVar5 = lua_isstring(uVar2);
  if (iVar5 != 0) {
    iVar5 = lua_isstring(uVar3);
    if (iVar5 != 0) {
      iVar5 = lua_isstring(uVar4);
      if (iVar5 != 0) {
        ppvVar1 = &g_pSvcLua->pFopen;
        uVar6 = lua_getstring(uVar4,&DAT_004dda54);
        iVar5 = (*(code *)*ppvVar1)(uVar6);
        if (iVar5 == 0) {
          ImSetState(0);
          ImStopAllSounds();
          SoundsCloseVoiceFile();
          do {
            flags = 1;
            caption = (char *)lua_getstring(uVar3);
            text = (char *)lua_getstring(uVar2);
            iVar5 = Plat_MessageBox(text,caption,flags);
            if (iVar5 == 2) {
              lua_pushnil();
              lua_pushnil();
              return;
            }
            Resource_CloseArchives();
            Resource_OpenArchives();
            ppvVar1 = &g_pSvcLua->pFopen;
            uVar6 = lua_getstring(uVar4,&DAT_004dda54);
            iVar5 = (*(code *)*ppvVar1)(uVar6);
          } while (iVar5 == 0);
          (*g_pSvcLua->pFclose)(iVar5);
          lua_pushnumber(FBITS(0x3f800000));
          lua_pushnumber(FBITS(0x3f800000));
          return;
        }
        (*g_pSvcLua->pFclose)(iVar5);
        lua_pushnumber(FBITS(0x3f800000));
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
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(uVar1);
  if (iVar2 != 0) {
    Engine_RequestLoad(0);
    return;
  }
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    uVar1 = lua_getstring(uVar1);
    Engine_RequestLoad(uVar1);
  }
  return;
}

/* ---- 0x0049cef0  Lua_Save ---- */
/* Lua opcode: Save */

void Lua_Save(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(uVar1);
  if (iVar2 != 0) {
    Engine_RequestSave(0);
    return;
  }
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    uVar1 = lua_getstring(uVar1);
    Engine_RequestSave(uVar1);
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
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  iVar4 = lua_isnumber(uVar1);
  if (iVar4 != 0) {
    iVar4 = lua_isnumber(uVar2);
    if (iVar4 != 0) {
      iVar4 = lua_isnumber(uVar3);
      if (iVar4 != 0) {
        fVar5 = (float10)lua_getnumber(uVar1);
        local_18 = (uint)(float)fVar5;
        fVar5 = (float10)lua_getnumber(uVar2);
        local_14 = (uint)(float)fVar5;
        fVar5 = (float10)lua_getnumber(uVar3);
        local_10 = (uint)(float)fVar5;
        iVar4 = rdCamera_ProjectPoint((float *)&local_18,(float *)&local_c);
        if (iVar4 != 0) {
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
#undef local_10
#undef local_14
#undef local_18
#undef local_2c
#undef local_8
#undef local_c


/* ---- 0x0049d030  Lua_ScreenToWorld ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: ScreenToWorld */

void Lua_ScreenToWorld(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  float *outPos;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  iVar4 = lua_isnumber(uVar2);
  if (iVar4 != 0) {
    iVar4 = lua_isnumber(uVar3);
    if (iVar4 != 0) {
      lua_getnumber(uVar2);
      lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      if ((int)lVar5 < 0) {
        bVar1 = false;
      }
      else {
        lua_getnumber(uVar2);
        lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        bVar1 = (int)lVar5 < 0x280;
      }
      if (bVar1) {
        lua_getnumber(uVar3);
        lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        if ((int)lVar5 < 0) {
          bVar1 = false;
        }
        else {
          lua_getnumber(uVar3);
          lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          bVar1 = (int)lVar5 < 0x1e0;
        }
        if (bVar1) {
          outPos = (float *)&local_c;
          lua_getnumber(uVar3);
          lVar5 = _ftol((double)CONCAT44(unaff_EDI,outPos));
          iVar4 = (int)lVar5;
          lua_getnumber(uVar2);
          lVar5 = _ftol((double)CONCAT44(outPos,iVar4));
          Render_ScreenToWorld((int)lVar5,iVar4,outPos);
          lua_pushnumber(local_c);
          lua_pushnumber(local_8);
          lua_pushnumber(local_4);
        }
      }
    }
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x0049d140  Lua_TypeOverride ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: Lua_TypeOverride */

void Lua_TypeOverride(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
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
    lua_pushstring(local_14);
    iVar2 = lua_tag(uVar1);
    lua_pushnumber((float)iVar2);
    return;
  }
LAB_0049d199:
  uVar3 = lua_getref(UINT_008cab48);
  lua_pushobject(uVar1);
  lua_callfunction(uVar3);
  uVar1 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  lua_pushobject(uVar1);
  lua_pushobject(uVar3);
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
  undefined4 uVar4;
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
          uVar4 = lua_getref(UINT_008cab44);
          lua_callfunction(uVar4);
          uVar4 = lua_lua2C(1);
          lua_pushobject(uVar4);
          return;
        }
        uVar4 = lua_getuserdata(uVar2);
        iVar3 = Actor_FromHandle(uVar4);
        if ((*(int *)(iVar3 + 0xa0) == 0) ||
           (iVar3 = *(int *)(*(int *)(iVar3 + 0xa0) + 4), iVar3 == 0)) {
          puVar5 = &DAT_004f5a98;
        }
        else {
          puVar5 = *(undefined1 **)(iVar3 + 4);
        }
        sprintf(pcVar9,s__actor_d__s__004ec494,uVar4,puVar5);
      }
      else {
        sprintf(pcVar9,s__nil__004ec4a4);
      }
    }
    else {
      fmt = (char *)lua_getstring();
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: exit */

void Lua_exit(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    Engine_Quit((int)lVar3);
    return;
  }
  Engine_Quit(0);
  return;
}
#endif


/* ---- 0x0049d3f0  Lua_EnableControl ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: EnableControl */

void Lua_EnableControl(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 == 0) {
    lua_pushnil();
    return;
  }
  lua_getnumber(uVar1);
  lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
  Control_Enable((int)lVar3);
  return;
}
#endif


/* ---- 0x0049d430  Lua_DisableControl ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: DisableControl */

void Lua_DisableControl(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 == 0) {
    lua_pushnil();
    return;
  }
  lua_getnumber(uVar1);
  lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
  Control_Disable((int)lVar3);
  return;
}
#endif


/* ---- 0x0049d470  Lua_GetControlState ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: GetControlState */

void Lua_GetControlState(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    uVar3 = (uint)lVar4;
    if (uVar3 <= g_nControlCount - 1U) {
      if (((&g_ControlTable)[uVar3 * 4] & 4) != 0) {
        iVar2 = Input_GetButtonState
                          (*(int *)(&DAT_004e87cc + uVar3 * 0x10),&local_4,(int *)&local_8);
        if (iVar2 == 0) {
          lua_pushnil();
        }
        else {
          lua_pushnumber(FBITS(0x3f800000));
        }
        if (local_8 != 0) {
          lua_pushnumber(FBITS(0x3f800000));
          return;
        }
        lua_pushnil();
        return;
      }
      local_c = (uint)Input_GetAxis(*(int *)(&DAT_004e87cc + uVar3 * 0x10));
      if (((&g_ControlTable)[uVar3 * 4] & 8) != 0) {
        local_c = (uint)-(float)local_c;
      }
      lua_pushnumber(local_c);
    }
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x0049d550  Lua_CallCostumeOverrideHandler ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Lua_CallCostumeOverrideHandler(void *actor,int flag)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  bool bVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int unaff_EDI;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  bVar1 = false;
  bVar2 = false;
  lua_beginblock();
  iVar3 = Actor_GetHandle(actor,unaff_EDI);
  uVar4 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar4);
  lua_pushstring(s_costumeOverrideHandler_004ec4ac);
  iVar5 = lua_gettable();
  iVar6 = lua_istable(iVar5);
  if (iVar6 == 0) {
    iVar6 = lua_isfunction(iVar5);
    if (iVar6 == 0) {
      lua_isnil(iVar5);
      iVar6 = iVar3;
    }
    else {
      bVar2 = false;
      bVar1 = true;
      iVar6 = iVar5;
    }
  }
  else {
    lua_pushobject();
    lua_pushstring(s_costumeOverrideHandler_004ec4ac);
    iVar6 = lua_gettable();
    iVar7 = lua_isfunction(iVar6);
    if (iVar7 != 0) {
      bVar1 = true;
      bVar2 = true;
    }
  }
  if (bVar1) {
    if (bVar2) {
      lua_pushobject(iVar5);
    }
    lua_pushusertag(iVar3,0x52544341);
    if (flag == 0) {
      lua_pushnil();
    }
    else {
      lua_pushnumber(FBITS(0x3f800000));
    }
    lua_callfunction(iVar6);
  }
  lua_endblock();
  return;
}
#undef local_4

#endif


/* ---- 0x0049d670  Lua_CallCostumeMarkerHandler ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_1c */
/* system.costumeMarkerHandler(actor, marker) from keyframe markers */

void __cdecl Lua_CallCostumeMarkerHandler(void *actor,uint marker)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  bool bVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int unaff_EBX;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  
  bVar1 = false;
  bVar2 = false;
  if (marker != 0) {
    iVar3 = Actor_GetHandle(actor,unaff_EBX);
    lua_beginblock();
    uVar4 = lua_getref(g_nLuaSystemTableRef);
    lua_pushobject(uVar4);
    lua_pushstring(s_costumeMarkerHandler_004ec4c4);
    uVar5 = lua_gettable();
    iVar6 = lua_istable(uVar5);
    if (iVar6 == 0) {
      iVar6 = lua_isfunction(uVar5);
      if (iVar6 == 0) {
        lua_isnil(uVar5);
        uVar7 = marker;
      }
      else {
        bVar2 = false;
        bVar1 = true;
        uVar7 = uVar5;
      }
    }
    else {
      lua_pushobject();
      lua_pushstring(s_costumeMarkerHandler_004ec4c4);
      uVar7 = lua_gettable();
      iVar6 = lua_isfunction(uVar7);
      if (iVar6 != 0) {
        bVar1 = true;
        bVar2 = true;
      }
    }
    if (bVar1) {
      if (bVar2) {
        lua_pushobject(uVar5);
      }
      lua_pushusertag(iVar3,0x52544341);
      lua_pushnumber((float)marker);
      lua_callfunction(uVar7);
    }
    lua_endblock();
  }
  return;
}
#undef local_1c

#endif


/* ---- 0x0049d7b0  Lua_CallUserPaintHandler ---- */
/* system.userPaintHandler() after a restore */

void Lua_CallUserPaintHandler(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  bVar1 = false;
  bVar2 = false;
  lua_beginblock();
  uVar3 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar3);
  lua_pushstring(s_userPaintHandler_004ec4dc);
  uVar3 = lua_gettable();
  iVar4 = lua_istable(uVar3);
  if (iVar4 == 0) {
    iVar4 = lua_isfunction(uVar3);
    if (iVar4 == 0) {
      lua_isnil(uVar3);
      uVar5 = 0;
    }
    else {
      bVar2 = false;
      bVar1 = true;
      uVar5 = uVar3;
    }
  }
  else {
    lua_pushobject();
    lua_pushstring(s_userPaintHandler_004ec4dc);
    uVar5 = lua_gettable();
    iVar4 = lua_isfunction(uVar5);
    if (iVar4 != 0) {
      bVar1 = true;
      bVar2 = true;
    }
  }
  if (bVar1) {
    if (bVar2) {
      lua_pushobject(uVar3);
    }
    lua_callfunction(uVar5);
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
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  bVar1 = false;
  local_4 = 0;
  lua_beginblock();
  uVar2 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar2);
  lua_pushstring(s_exitHandler_004ec4f0);
  uVar2 = lua_gettable();
  iVar3 = lua_istable(uVar2);
  if (iVar3 == 0) {
    iVar3 = lua_isfunction(uVar2);
    if (iVar3 == 0) {
      lua_isnil(uVar2);
      uVar4 = 0;
    }
    else {
      bVar1 = false;
      local_4 = 1;
      uVar4 = uVar2;
    }
  }
  else {
    lua_pushobject();
    lua_pushstring(s_exitHandler_004ec4f0);
    uVar4 = lua_gettable();
    iVar3 = lua_isfunction(uVar4);
    if (iVar3 != 0) {
      bVar1 = true;
      local_4 = 1;
    }
  }
  if (local_4 != 0) {
    if (bVar1) {
      lua_pushobject(uVar2);
    }
    lua_callfunction(uVar4);
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
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  bVar1 = false;
  local_4 = 0;
  lua_beginblock();
  uVar2 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar2);
  lua_pushstring(s_pauseHandler_004ec4fc);
  uVar2 = lua_gettable();
  iVar3 = lua_istable(uVar2);
  if (iVar3 == 0) {
    iVar3 = lua_isfunction(uVar2);
    if (iVar3 == 0) {
      lua_isnil(uVar2);
      uVar4 = 0;
    }
    else {
      bVar1 = false;
      local_4 = 1;
      uVar4 = uVar2;
    }
  }
  else {
    lua_pushobject();
    lua_pushstring(s_pauseHandler_004ec4fc);
    uVar4 = lua_gettable();
    iVar3 = lua_isfunction(uVar4);
    if (iVar3 != 0) {
      bVar1 = true;
      local_4 = 1;
    }
  }
  if (local_4 != 0) {
    if (bVar1) {
      lua_pushobject(uVar2);
    }
    lua_callfunction(uVar4);
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
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  #define local_6 (*(ushort *)(_frame + (0x20 - 0x6)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar6 = 0;
  bVar1 = false;
  local_4 = 0;
  lua_beginblock();
  uVar2 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar2);
  lua_pushstring(s_characterHandler_004ec50c);
  iVar3 = lua_gettable();
  iVar4 = lua_istable(iVar3);
  if (iVar4 == 0) {
    iVar4 = lua_isfunction(iVar3);
    if (iVar4 == 0) {
      lua_isnil(iVar3);
      iVar4 = ch;
    }
    else {
      local_4 = 0;
      bVar1 = true;
      iVar4 = iVar3;
    }
  }
  else {
    lua_pushobject();
    lua_pushstring(s_characterHandler_004ec50c);
    iVar4 = lua_gettable();
    iVar5 = lua_isfunction(iVar4);
    if (iVar5 != 0) {
      bVar1 = true;
      local_4 = 1;
    }
  }
  if (bVar1) {
    if (local_4 != 0) {
      lua_pushobject(iVar3);
    }
    local_6 = (ushort)(byte)ch;
    lua_pushstring(&local_6);
    lua_callfunction(iVar4);
    uVar2 = lua_lua2C(1);
    iVar3 = lua_isnil(uVar2);
    uVar6 = (uint)(iVar3 == 0);
  }
  lua_endblock();
  return uVar6;
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
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
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
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  void *pvVar5;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    pcVar3 = Set_GetCurrentName();
    uVar4 = lua_getstring(uVar1,pcVar3);
    iVar2 = ((code *)_stricmp)(uVar4);
    if (iVar2 == 0) {
      pvVar5 = Set_GetCurrent();
      if (pvVar5 != (void *)0x0) {
        pvVar5 = Set_GetCurrent();
        lua_pushnumber((float)*(int *)((int)pvVar5 + 0xb4));
        return;
      }
      lua_pushnil();
      return;
    }
    pcVar3 = (char *)lua_getstring(uVar1);
    pvVar5 = Res_Find(0x20544553,pcVar3);
    if (pvVar5 != (void *)0x0) {
      pcVar3 = (char *)lua_getstring(uVar1);
      pvVar5 = Resource_Load(0x20544553,pcVar3);
      lua_pushnumber((float)*(int *)((int)pvVar5 + 0xb4));
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
  undefined4 uVar1;
  int iVar2;
  char *name;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 == 0) {
    Set_MakeCurrent((char *)0x0);
    return;
  }
  name = (char *)lua_getstring(uVar1);
  Set_MakeCurrent(name);
  return;
}

/* ---- 0x0049dcb0  Lua_LockSet ---- */
/* Source: Scripts/sputLua.cpp (line 5305, from __FILE__/__LINE__ passed to the allocator) */

void Lua_LockSet(void)

{
  undefined4 uVar1;
  int iVar2;
  char *name;
  void *data;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(uVar1);
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
  undefined4 uVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(uVar1);
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
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = lua_lua2C(1);
  iVar3 = lua_isnil(uVar2);
  if (iVar3 != 0) {
    (*g_pSvcLua->pPrintf2)(s__nil__004ec4a4);
    return;
  }
  iVar3 = lua_isstring(uVar2);
  if (iVar3 != 0) {
    ppvVar1 = &g_pSvcLua->pPrintf2;
    uVar2 = lua_getstring(uVar2);
    (*(code *)*ppvVar1)(uVar2);
  }
  return;
}

/* ---- 0x0049ddd0  Lua_Print_NoOp ---- */
/* Lua opcodes: PrintError, PrintWarning, PrintDebug
   PrintError / PrintWarning / PrintDebug: no-op in the release build */

void Lua_Print_NoOp(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(uVar1);
  if (iVar2 == 0) {
    lua_isstring(uVar1);
  }
  return;
}

/* ---- 0x0049de00  Lua_InitGameLibs ---- */
undefined4 Lua_InitGameLibs(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
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
  lua_recognizelib(&PTR_s_concatfallback_004ea890,4);
  g_nLuaSystemTableRef = Lua_CreateSystemTable();
  uVar2 = lua_getglobal(&DAT_004ec54c);
  lua_pushobject(uVar2);
  UINT_008cab48 = lua_ref(1);
  lua_pushCclosure(Lua_TypeOverride,0);
  lua_setglobal(&DAT_004ec54c);
  lua_pushnumber(0);
  lua_setglobal(&DAT_004ec544);
  lua_pushnumber(FBITS(0x45800000));
  lua_setglobal(&DAT_004ec53c);
  lua_pushnumber(FBITS(0x46000000));
  lua_setglobal(s_CAMERA_004ec534);
  lua_pushnumber(FBITS(0x46800000));
  lua_setglobal(s_SPECIAL_004ec52c);
  lua_pushnumber(FBITS(0x47000000));
  lua_setglobal(&DAT_004ec528);
  uVar2 = lua_setfallback(s_concat_004ec520,Lua_ConcatFallback);
  lua_pushobject(uVar2);
  UINT_008cab44 = lua_ref(1);
  *(code **)lua_savehook_exref = Lua_SaveUserdataHook;
  *(code **)lua_restorehook_exref = Lua_RestoreUserdataHook;
  Engine_RegisterShutdownHook(Lua_DispatchControlHandlers);
  return 0;
}
#undef acStack_20


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
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  float fVar6;
  code *pcVar7;
  uint *puVar8;
  #define local_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define local_44 (*(uint *)(_frame + (0x70 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x70 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x70 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x70 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x70 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x70 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x70 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x70 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x70 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x70 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x70 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x70 - 0x18)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x70 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x70 - 0x10)))
  #define uStack_c (*(undefined4 *)(_frame + (0x70 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x70 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x70 - 0x4)))
  
  bVar1 = false;
  bVar2 = false;
  lua_beginblock();
  uVar3 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar3);
  lua_pushstring(s_buttonHandler_004ec574);
  uVar4 = lua_gettable();
  local_24 = uVar4;
  iVar5 = lua_istable(uVar4);
  pcVar7 = lua_isfunction_exref;
  if (iVar5 == 0) {
    iVar5 = lua_isfunction(uVar4);
    if (iVar5 == 0) {
      local_44 = 0;
    }
    else {
      bVar1 = false;
      local_44 = 1;
      local_2c = uVar4;
    }
  }
  else {
    lua_pushobject();
    lua_pushstring(s_buttonHandler_004ec574);
    local_2c = lua_gettable();
    pcVar7 = lua_isfunction_exref;
    iVar5 = lua_isfunction(local_2c);
    if (iVar5 != 0) {
      bVar1 = true;
      local_44 = 1;
    }
  }
  uVar3 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar3);
  lua_pushstring(s_axisHandler_004ec568);
  uVar4 = lua_gettable();
  local_1c = uVar4;
  iVar5 = lua_istable(uVar4);
  if (iVar5 == 0) {
    iVar5 = (*pcVar7)(uVar4);
    if (iVar5 == 0) {
      local_3c = 0;
    }
    else {
      bVar2 = false;
      local_3c = 1;
      local_28 = uVar4;
    }
  }
  else {
    lua_pushobject();
    lua_pushstring(s_axisHandler_004ec568);
    local_28 = lua_gettable();
    iVar5 = (*pcVar7)(local_28);
    if (iVar5 != 0) {
      bVar2 = true;
      local_3c = 1;
    }
  }
  uVar4 = 0;
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
              lua_pushobject(local_1c);
            }
            uStack_4 = 0;
            local_8 = uVar4;
            lua_pushnumber((float)uVar4);
            lua_pushnumber(fVar6);
            lua_callfunction(local_28);
            *puVar8 = (uint)fVar6;
          }
        }
        else {
          local_30 = 0;
          fVar6 = (float)Input_GetButtonState(puVar8[-1],(int *)&local_30,(int *)&local_20);
          if ((fVar6 != (float)*puVar8) && (local_44 != 0)) {
            if (bVar1) {
              lua_pushobject(local_24);
            }
            uStack_14 = 0;
            local_18 = uVar4;
            lua_pushnumber((float)uVar4);
            if (fVar6 == 0.0) {
              lua_pushnil();
            }
            else {
              lua_pushnumber(FBITS(0x3f800000));
            }
            uStack_c = 0;
            local_10 = local_30;
            lua_pushnumber((float)local_30);
            lua_pushnumber((float)(int)local_20);
            lua_callfunction(local_2c);
            *puVar8 = (uint)fVar6;
          }
        }
      }
      uVar4 = uVar4 + 1;
      puVar8 = puVar8 + 4;
    } while (uVar4 < (uint)g_nControlCount);
  }
  lua_endblock();
  return 0;
}
#undef local_10
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_44
#undef local_58
#undef local_8
#undef uStack_14
#undef uStack_4
#undef uStack_c


/* ---- 0x0049e380  Lua_CreateSystemTable ---- */
/* Creates the global `system` table with the controls table and stub camChange/axis/button
   handlers; returns its ref */

undefined4 Lua_CreateSystemTable(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = lua_createtable();
  lua_pushobject(uVar1);
  lua_setglobal(s_system_004ec584);
  lua_pushobject(uVar1);
  uVar1 = lua_ref(1);
  Lua_CreateControlsTable(uVar1);
  uVar2 = lua_getref(uVar1);
  lua_pushobject(uVar2);
  lua_pushstring(s_camChangeHandler_004ec3d0);
  lua_pushCclosure(Lua_Stub,0);
  lua_settable();
  uVar2 = lua_getref(uVar1);
  lua_pushobject(uVar2);
  lua_pushstring(s_axisHandler_004ec568);
  lua_pushCclosure(Lua_Stub,0);
  lua_settable();
  uVar2 = lua_getref(uVar1);
  lua_pushobject(uVar2);
  lua_pushstring(s_buttonHandler_004ec574);
  lua_pushCclosure(Lua_Stub,0);
  lua_settable();
  return uVar1;
}

/* ---- 0x0049e460  Lua_CreateControlsTable ---- */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* system.controls[name] = index for every entry of g_ControlTable (name at control+0xc) */

void Lua_CreateControlsTable(undefined4 param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined **ppuVar4;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  
  uVar1 = lua_createtable();
  uVar2 = lua_getref(param_1);
  lua_pushobject(uVar2);
  lua_pushstring(s_controls_004ec58c);
  lua_pushobject(uVar1);
  lua_settable();
  uVar3 = 0;
  if (g_nControlCount != 0) {
    ppuVar4 = &PTR_s_KEY_ESCAPE_004e87d4;
    do {
      lua_pushobject(uVar1);
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


/* ---- 0x0049e500  FUN_0049e500 ---- */
void FUN_0049e500(void)

{
  g_pSvcLua = (GrimServices *)0x0;
  if (UINT_008cab7c != 0) {
    (*(code *)UINT_008cab54)();
    UINT_008cab7c = 0;
  }
  return;
}

/* ---- 0x0049e530  FUN_0049e530 ---- */
void FUN_0049e530(void)

{
  if (g_pLuaFileFind != (void *)0x0) {
    stdFileUtil_DisposeFind(g_pLuaFileFind);
    g_pLuaFileFind = (void *)0x0;
  }
  lua_unref(g_nLuaSystemTableRef);
  *(undefined4 *)lua_savehook_exref = 0;
  *(undefined4 *)lua_restorehook_exref = 0;
  (*(code *)UINT_008cab5c)();
  UINT_008cab80 = 0;
  return;
}

/* ---- 0x0049e590  Lua_SetSoundPosition ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetSoundPosition */

void Lua_SetSoundPosition(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  void *set;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 unaff_ESI;
  int iVar7;
  undefined4 unaff_EDI;
  float10 fVar8;
  longlong lVar9;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  set = Set_GetCurrent();
  local_20 = 0x41000000;
  local_1c = 0x3f800000;
  local_24 = CONCAT31(PIECE(local_24,1,3),10);
  local_28 = CONCAT31(PIECE(local_28,1,3),0x7f);
  local_18 = 0x3fc00000;
  if (set != (void *)0x0) {
    Set_GetSoundParams(set,(float *)&local_20,(char *)&local_24,(char *)&local_28,(float *)&local_18
                       ,(float *)&local_1c);
  }
  uVar2 = lua_lua2C(1);
  local_10 = uVar2;
  iVar3 = lua_isnumber(uVar2);
  if ((iVar3 == 0) && (iVar3 = lua_isstring(uVar2), iVar3 == 0)) {
    return;
  }
  iVar7 = 3;
  uVar4 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar4);
  if ((iVar3 == 0) || (iVar3 = lua_tag(uVar4), iVar3 != 0x52544341)) {
    iVar3 = lua_isnumber(uVar4);
    if (iVar3 != 0) {
      uVar5 = lua_lua2C(3);
      iVar7 = 5;
      local_14 = lua_lua2C(4);
      fVar8 = (float10)lua_getnumber(uVar4);
      local_c = (uint)(float)fVar8;
      fVar8 = (float10)lua_getnumber(uVar5);
      local_8 = (uint)(float)fVar8;
      fVar8 = (float10)lua_getnumber(local_14);
      local_4 = (uint)(float)fVar8;
    }
  }
  else {
    uVar4 = lua_getuserdata(uVar4);
    iVar3 = Actor_FromHandle(uVar4);
    if (iVar3 == 0) {
      return;
    }
    local_c = *(uint *)(iVar3 + 0xc);
    local_8 = *(uint *)(iVar3 + 0x10);
    local_4 = *(uint *)(iVar3 + 0x14);
  }
  uVar4 = lua_lua2C(iVar7);
  uVar5 = lua_lua2C(iVar7 + 1);
  uVar6 = lua_lua2C(iVar7 + 2);
  iVar3 = lua_isnumber(uVar4);
  if (iVar3 != 0) {
    lua_getnumber(uVar4);
    lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    local_24 = CONCAT31(PIECE(local_24,1,3),(byte)lVar9);
    if (0x7f < (byte)lVar9) {
      local_24 = CONCAT31(PIECE(local_24,1,3),0x7f);
    }
  }
  iVar3 = lua_isnumber(uVar5);
  if (iVar3 != 0) {
    lua_getnumber(uVar5);
    lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    bVar1 = (byte)lVar9;
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
  iVar3 = lua_isnumber(uVar6);
  if (iVar3 != 0) {
    fVar8 = (float10)lua_getnumber(uVar6);
    local_20 = (uint)(float)fVar8;
    if (fVar8 < (float10)0.0) {
      local_20 = 0;
    }
  }
  uVar2 = local_10;
  iVar3 = lua_isnumber(local_10);
  if (iVar3 == 0) {
    uVar4 = lua_getstring(uVar2);
  }
  else {
    lua_getnumber();
    lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    uVar4 = (undefined4)lVar9;
  }
  Sound_SetPosition(uVar4,&local_c,local_24 & 0xff,local_28 & 0xff,local_20,0x3f4ccccd);
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


/* ---- 0x0049e7e0  Lua_StartFullscreenMovie ---- */
/* Lua opcode: StartFullscreenMovie */

void Lua_StartFullscreenMovie(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isstring(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_isnil(uVar2,0xffffffff,0xffffffff);
    uVar1 = lua_getstring(uVar1,1,iVar3 == 0);
    iVar3 = ((code *)Engine_BlitToBackBuffer)(uVar1);
    if (iVar3 == 1) {
      lua_pushnumber(FBITS(0x3f800000));
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
  undefined4 uVar1;
  int paused;
  
  uVar1 = lua_lua2C(1);
  paused = lua_isnil(uVar1);
  Movie_SetPaused(paused);
  return;
}

/* ---- 0x0049e880  Lua_StartMovie ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: StartMovie */

void Lua_StartMovie(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar6;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  iVar5 = lua_isstring(uVar1);
  if (iVar5 != 0) {
    SoundsFloodMusicBuffer();
    iVar5 = lua_isnumber(uVar4);
    if (iVar5 == 0) {
      uVar4 = 0xffffffff;
    }
    else {
      lua_getnumber(uVar4);
      lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      uVar4 = (undefined4)lVar6;
    }
    iVar5 = lua_isnumber(uVar3);
    if (iVar5 == 0) {
      uVar3 = 0xffffffff;
    }
    else {
      lua_getnumber(uVar3);
      lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      uVar3 = (undefined4)lVar6;
    }
    iVar5 = lua_isnil(uVar2,uVar3,uVar4);
    uVar1 = lua_getstring(uVar1,0,iVar5 == 0);
    iVar5 = ((code *)Engine_BlitToBackBuffer)(uVar1);
    if (iVar5 == 1) {
      lua_pushnumber(FBITS(0x3f800000));
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x0049e960  Lua_IsMoviePlaying ---- */
/* Lua opcodes: IsFullscreenMoviePlaying, IsMoviePlaying
   also registered as IsFullscreenMoviePlaying */

void Lua_IsMoviePlaying(void)

{
  int iVar1;
  
  iVar1 = Movie_IsPlaying();
  if (iVar1 != 0) {
    lua_pushnumber(FBITS(0x3f800000));
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
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  char *ext;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isstring(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_isnil(uVar2);
    local_4 = (uint)param_1;
    if (iVar3 == 0) {
      local_4 = lua_getstring(uVar2);
    }
    ext = (char *)lua_getstring(uVar1);
    Lua_FileFindDispose();
    iVar3 = lua_isnil(uVar2);
    if (iVar3 != 0) {
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
  #define local_10c (*(undefined1 (*)[260])(_frame + (0x120 - 0x10c)))
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
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  char *text;
  char *caption;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  iVar4 = lua_isstring(uVar1);
  if (iVar4 != 0) {
    iVar4 = lua_isstring(uVar2);
    if (iVar4 != 0) {
      text = (char *)lua_getstring(uVar1);
      caption = (char *)lua_getstring(uVar2);
      iVar4 = lua_isnil(uVar3);
      iVar4 = Plat_MessageBox(text,caption,(iVar4 != 0) + 3);
      if (iVar4 == 2) {
        lua_pushnumber(0);
        return;
      }
      if (iVar4 != 7) {
        lua_pushnumber(FBITS(0x3f800000));
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
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  char *title;
  char *prompt;
  char *defaultText;
  char *pcVar5;
  #define local_6c (*(uint *)(_frame + (0x80 - 0x6c)))
  #define local_68 (*(char (*)[104])(_frame + (0x80 - 0x68)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  iVar4 = lua_isstring(uVar1);
  if (iVar4 != 0) {
    iVar4 = lua_isstring(uVar2);
    if (iVar4 != 0) {
      iVar4 = lua_isnil(uVar3);
      if (iVar4 == 0) {
        iVar4 = lua_isstring(uVar3);
        if (iVar4 == 0) goto LAB_0049ec38;
      }
      title = (char *)lua_getstring(uVar1);
      prompt = (char *)lua_getstring(uVar2);
      iVar4 = lua_isstring(uVar3);
      if (iVar4 == 0) {
        defaultText = (char *)0x0;
      }
      else {
        defaultText = (char *)lua_getstring(uVar3);
      }
      pcVar5 = local_68;
      for (iVar4 = 0x19; iVar4 != 0; iVar4 = iVar4 + -1) {
        pcVar5[0] = '\0';
        pcVar5[1] = '\0';
        pcVar5[2] = '\0';
        pcVar5[3] = '\0';
        pcVar5 = pcVar5 + 4;
      }
      *pcVar5 = '\0';
      iVar4 = Plat_InputDialog(title,prompt,local_68,0x65,defaultText);
      if (iVar4 != 0) {
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
  undefined4 uVar1;
  int iVar2;
  char *name;
  char *value;
  float10 fVar3;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(uVar1);
    uVar1 = lua_lua2C(2);
    iVar2 = lua_isstring(uVar1);
    if (iVar2 != 0) {
      value = (char *)lua_getstring();
      Reg_SetString(name,value);
      return;
    }
    iVar2 = lua_isnumber(uVar1);
    if (iVar2 != 0) {
      fVar3 = (float10)lua_getnumber(uVar1);
      Reg_SetFloat(name,(float)fVar3);
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
  undefined4 uVar1;
  int iVar2;
  char *name;
  float fVar3;
  #define local_104 (*(uint *)(_frame + (0x120 - 0x104)))
  #define local_100 (*(char (*)[256])(_frame + (0x120 - 0x100)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(uVar1);
    iVar2 = Reg_GetValueType(name);
    if (iVar2 == 3) {
      fVar3 = Reg_GetFloat(name,0.0);
      lua_pushnumber(fVar3);
      return;
    }
    if (iVar2 == 1) {
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
  undefined4 uVar3;
  char *name;
  void *a2;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if ((iVar2 == 0x52544341) && (iVar1 != 0)) {
      uVar3 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(uVar3);
      uVar3 = lua_lua2C(2);
      iVar2 = lua_isstring(uVar3);
      if (iVar2 != 0) {
        name = (char *)lua_getstring(uVar3);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: IsSectorActive */

void Lua_IsSectorActive(void)

{
  undefined4 uVar1;
  int iVar2;
  void *pvVar3;
  char *name;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(uVar1);
    if (iVar2 == 0) goto LAB_0049eea2;
  }
  pvVar3 = Set_GetCurrent();
  if (pvVar3 != (void *)0x0) {
    iVar2 = lua_isstring(uVar1);
    if (iVar2 == 0) {
      lua_getnumber(uVar1);
      lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      pvVar3 = Sector_FindById((int)lVar4);
    }
    else {
      name = (char *)lua_getstring();
      pvVar3 = Sector_FindByName(name);
    }
    if ((pvVar3 != (void *)0x0) && (*(int *)((int)pvVar3 + 0x28) != 0)) {
      lua_pushnumber(FBITS(0x3f800000));
    }
  }
LAB_0049eea2:
  lua_pushnil();
  return;
}
#endif


/* ---- 0x0049eeb0  Lua_MakeSectorActive ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: MakeSectorActive */

void Lua_MakeSectorActive(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  char *name;
  void *pvVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if ((iVar2 == 0) && (iVar2 = lua_isstring(uVar1), iVar2 == 0)) {
    return;
  }
  uVar3 = lua_lua2C(2);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 == 0) {
    lua_getnumber(uVar1);
    lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    pvVar4 = Sector_FindById((int)lVar5);
  }
  else {
    name = (char *)lua_getstring();
    pvVar4 = Sector_FindByName(name);
  }
  if (pvVar4 != (void *)0x0) {
    iVar2 = lua_isnil(uVar3);
    if (iVar2 != 0) {
      *(undefined4 *)((int)pvVar4 + 0x28) = 0;
      return;
    }
    *(undefined4 *)((int)pvVar4 + 0x28) = 1;
  }
  return;
}
#endif


/* ---- 0x0049ef50  Lua_PreRender ---- */
/* Lua opcode: PreRender */

void Lua_PreRender(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  uint redrawDepth;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isnil(uVar2);
  redrawDepth = (uint)(iVar3 == 0);
  iVar3 = lua_isnil(uVar1);
  Render_InvalidateBackground((uint)(iVar3 == 0),redrawDepth);
  return;
}

/* ---- 0x0049efc0  Lua_GetCurrentScript ---- */
/* Lua opcode: GetCurrentScript */

void Lua_GetCurrentScript(void)

{
  undefined4 uVar1;
  
  uVar1 = lua_currenttask();
  lua_pushtask(uVar1);
  return;
}

/* ---- 0x0049efe0  Lua_LockFont ---- */
/* Lua opcode: LockFont */

void Lua_LockFont(void)

{
  undefined4 uVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 == 0) {
    lua_pushnil();
    return;
  }
  name = (char *)lua_getstring(uVar1);
  pvVar3 = Resource_Load(0x544e4f46,name);
  if (pvVar3 == (void *)0x0) {
    lua_pushnil();
    return;
  }
  lua_pushusertag(pvVar3,0x544e4f46);
  return;
}

/* ---- 0x0049f040  Lua_LoadCostume ---- */
/* Lua opcode: LoadCostume */

void Lua_LoadCostume(void)

{
  undefined4 uVar1;
  int iVar2;
  char *name;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 == 0) {
    lua_pushnil();
    return;
  }
  name = (char *)lua_getstring(uVar1);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetMemoryUsage */

void Lua_SetMemoryUsage(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int b;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar3;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  lua_getnumber(uVar2);
  lVar3 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  b = (int)lVar3;
  lua_getnumber(uVar1);
  lVar3 = _ftol((double)CONCAT44(unaff_EDI,b));
  Resource_SetMemoryUsage((int)lVar3,b);
  return;
}
#endif


/* ---- 0x0049f0f0  Lua_RotateVector ---- */
/* Lua opcode: RotateVector */

void Lua_RotateVector(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  float10 fVar5;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_istable(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_istable(uVar2);
    if (iVar3 != 0) {
      lua_pushobject(uVar1);
      lua_pushstring(&DAT_004e8454);
      uVar4 = lua_gettable();
      fVar5 = (float10)lua_getnumber(uVar4);
      local_18 = (uint)(float)fVar5;
      lua_pushobject(uVar1);
      lua_pushstring(&DAT_004e8450);
      uVar4 = lua_gettable();
      fVar5 = (float10)lua_getnumber(uVar4);
      local_14 = (uint)(float)fVar5;
      lua_pushobject(uVar1);
      lua_pushstring(&DAT_004ec3b8);
      uVar1 = lua_gettable();
      fVar5 = (float10)lua_getnumber(uVar1);
      local_10 = (uint)(float)fVar5;
      lua_pushobject(uVar2);
      lua_pushstring(&DAT_004e8454);
      uVar1 = lua_gettable();
      fVar5 = (float10)lua_getnumber(uVar1);
      local_c = (uint)(float)fVar5;
      lua_pushobject(uVar2);
      lua_pushstring(&DAT_004e8450);
      uVar1 = lua_gettable();
      fVar5 = (float10)lua_getnumber(uVar1);
      local_8 = (uint)(float)fVar5;
      lua_pushobject(uVar2);
      lua_pushstring(&DAT_004ec3b8);
      uVar1 = lua_gettable();
      fVar5 = (float10)lua_getnumber(uVar1);
      local_4 = (uint)(float)fVar5;
      Vec3_Rotate((float *)&local_18,(float *)&local_c);
      uVar1 = lua_createtable();
      lua_pushobject(uVar1);
      lua_pushstring(&DAT_004e8454);
      lua_pushnumber(local_18);
      lua_settable();
      lua_pushobject(uVar1);
      lua_pushstring(&DAT_004e8450);
      lua_pushnumber(local_14);
      lua_settable();
      lua_pushobject(uVar1);
      lua_pushstring(&DAT_004ec3b8);
      lua_pushnumber(local_10);
      lua_settable();
      lua_pushobject(uVar1);
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
#undef local_4
#undef local_8
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
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  if (g_pCameraSetup == (float *)0x0) {
    lua_pushnil();
  }
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(1);
  iVar4 = lua_isnumber(uVar1);
  if (iVar4 != 0) {
    iVar4 = lua_isnumber(uVar2);
    if (iVar4 != 0) {
      iVar4 = lua_isnumber(uVar3);
      if (iVar4 != 0) goto LAB_0049f40e;
    }
  }
  lua_pushnil();
LAB_0049f40e:
  fVar5 = (float10)lua_getnumber(uVar1);
  *g_pCameraSetup = (float)fVar5;
  fVar5 = (float10)lua_getnumber(uVar2);
  g_pCameraSetup[1] = (float)fVar5;
  fVar5 = (float10)lua_getnumber(uVar3);
  g_pCameraSetup[2] = (float)fVar5;
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
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  if (g_pCameraSetup == (float *)0x0) {
    lua_pushnil();
  }
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(1);
  iVar4 = lua_isnumber(uVar1);
  if (iVar4 != 0) {
    iVar4 = lua_isnumber(uVar2);
    if (iVar4 != 0) {
      iVar4 = lua_isnumber(uVar3);
      if (iVar4 != 0) goto LAB_0049f4de;
    }
  }
  lua_pushnil();
LAB_0049f4de:
  fVar5 = (float10)lua_getnumber(uVar1);
  g_pCameraSetup[3] = (float)fVar5;
  fVar5 = (float10)lua_getnumber(uVar2);
  g_pCameraSetup[4] = (float)fVar5;
  fVar5 = (float10)lua_getnumber(uVar3);
  g_pCameraSetup[5] = (float)fVar5;
  Camera_BuildBasis(g_pCameraSetup + 0xc,g_pCameraSetup,g_pCameraSetup + 3,g_pCameraSetup[6]);
  rdCamera_SetFrame(g_pCameraSetup + 0xc);
  return;
}
#undef local_14


/* ---- 0x0049f550  Lua_SetActorScale ---- */
/* Lua opcode: SetActorScale */

void Lua_SetActorScale(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  float10 fVar5;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar3 = Actor_FromHandle(uVar1);
      iVar4 = lua_isnumber(uVar2);
      if (iVar4 != 0) {
        fVar5 = (float10)lua_getnumber(uVar2);
        *(float *)(iVar3 + 0x30) = (float)fVar5;
        return;
      }
      *(undefined4 *)(iVar3 + 0x30) = 0x3f800000;
    }
  }
  return;
}

/* ---- 0x0049f5d0  Lua_SetActorTimeScale ---- */
/* Lua opcode: SetActorTimeScale */

void Lua_SetActorTimeScale(void)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(uVar2);
  if (iVar4 != 0) {
    iVar4 = lua_tag(uVar2);
    if (iVar4 == 0x52544341) {
      uVar2 = lua_getuserdata(uVar2);
      iVar4 = Actor_FromHandle(uVar2);
      if (*(int *)(iVar4 + 0xa4) == 0) {
        Actor_CreateExtra(iVar4);
      }
      iVar5 = lua_isnumber(uVar3);
      if (iVar5 == 0) {
        fVar6 = (float10)1.0;
      }
      else {
        fVar6 = (float10)lua_getnumber(uVar3);
      }
      *(float *)(*(int *)(iVar4 + 0xa4) + 0x41c) = (float)fVar6;
      iVar4 = *(int *)(iVar4 + 0xa4);
      fVar1 = *(float *)(iVar4 + 0x41c);
      if (*(float *)(iVar4 + 0x41c) < 0.0) {
        fVar1 = -fVar1;
      }
      *(float *)(iVar4 + 0x41c) = fVar1;
    }
  }
  return;
}

/* ---- 0x0049f690  Lua_GetActorNodeLocation ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: GetActorNodeLocation */

void Lua_GetActorNodeLocation(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  void *actor;
  float *pfVar5;
  uint uVar6;
  float *frame;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar7;
  #define local_3c (*(uint *)(_frame + (0x50 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(float (*)[9])(_frame + (0x50 - 0x30)))
  #define local_c (*(uint *)(_frame + (0x50 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x50 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x50 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(uVar2);
  if (iVar4 != 0) {
    iVar4 = lua_tag(uVar2);
    if (iVar4 == 0x52544341) {
      iVar4 = lua_isnumber(uVar3);
      if (iVar4 != 0) {
        uVar2 = lua_getuserdata(uVar2);
        actor = (void *)Actor_FromHandle(uVar2);
        if ((*(int *)((int)actor + 0xa0) != 0) && (*(int *)(*(int *)((int)actor + 0xa0) + 4) != 0))
        {
          if (*(int *)((int)actor + 0x68) == 0) {
            pfVar5 = Actor_GetFrame(actor);
            rdPuppet_UpdateFrame(*(void **)(*(int *)((int)actor + 0xa0) + 4),pfVar5);
          }
          pfVar5 = local_30;
          lua_getnumber(uVar3);
          lVar7 = _ftol((double)CONCAT44(unaff_EDI,pfVar5));
          uVar6 = (uint)lVar7;
          frame = Actor_GetFrame(actor);
          rdPuppet_BuildJointMatrices
                    (*(void **)(*(int *)((int)actor + 0xa0) + 4),frame,uVar6,(uint)pfVar5);
          lua_getnumber(uVar3);
          lVar7 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          puVar1 = (uint *)(*(int *)(*(int *)(*(int *)(*(int *)((int)actor + 0xa0) + 4) + 4) + 0x58)
                            + 100 + (int)lVar7 * 0xb8);
          local_3c = *puVar1;
          local_38 = puVar1[1];
          local_34 = puVar1[2];
          Vec3_Transform((float *)&local_3c,local_30);
          local_3c = (uint)((float)local_3c + (float)local_c);
          local_38 = (uint)((float)local_38 + (float)local_8);
          local_34 = (uint)((float)local_34 + (float)local_4);
          lua_pushnumber(local_3c);
          lua_pushnumber(local_38);
          lua_pushnumber(local_34);
        }
      }
    }
  }
  return;
}
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x0049f810  Lua_GetActorScale ---- */
/* Lua opcode: GetActorScale */

void Lua_GetActorScale(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      lua_pushnumber(*(undefined4 *)(iVar2 + 0x30));
    }
  }
  return;
}

/* ---- 0x0049f860  Lua_GetActorTimeScale ---- */
/* Lua opcode: GetActorTimeScale */

void Lua_GetActorTimeScale(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar2 = Actor_FromHandle(uVar1);
      if (*(int *)(iVar2 + 0xa4) == 0) {
        Actor_CreateExtra(iVar2);
      }
      lua_pushnumber(*(undefined4 *)(*(int *)(iVar2 + 0xa4) + 0x41c));
    }
  }
  return;
}

/* ---- 0x0049f8d0  Lua_SetCameraFOV ---- */
/* Lua opcode: SetCameraFOV */

void Lua_SetCameraFOV(void)

{
  undefined4 uVar1;
  int iVar2;
  float10 fVar3;
  
  if (g_pCameraSetup == (float *)0x0) {
    lua_pushnil();
  }
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 == 0) {
    lua_pushnil();
  }
  fVar3 = (float10)lua_getnumber(uVar1);
  g_pCameraSetup[7] = (float)fVar3;
  *(float *)((int)g_pCameraSetup[10] + 0x38) = g_pCameraSetup[7];
  return;
}

/* ---- 0x0049f930  Lua_SetCameraRoll ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: SetCameraRoll */

void Lua_SetCameraRoll(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  float10 fVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  if (g_pCameraSetup == (float *)0x0) {
    lua_pushnil();
  }
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 == 0) {
    lua_pushnil();
  }
  fVar3 = (float10)lua_getnumber(uVar1);
  g_pCameraSetup[6] = (float)fVar3;
  Camera_BuildBasis(g_pCameraSetup + 0xc,g_pCameraSetup,g_pCameraSetup + 3,g_pCameraSetup[6]);
  rdCamera_SetFrame(g_pCameraSetup + 0xc);
  return;
}
#undef local_c


/* ---- 0x0049f9b0  Lua_GetCameraLookVector ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: GetCameraLookVector */

void Lua_GetCameraLookVector(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  void *pvVar3;
  int iVar4;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  longlong lVar5;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  pvVar3 = Set_GetCurrent();
  if (pvVar3 == (void *)0x0) {
    lua_pushnil();
    return;
  }
  iVar4 = lua_isnumber(uVar2);
  if (iVar4 == 0) {
    iVar4 = *(int *)((int)pvVar3 + 0xb4);
  }
  else {
    lua_getnumber(uVar2);
    lVar5 = _ftol((double)CONCAT44(unaff_EBP,unaff_EBX));
    iVar4 = (int)lVar5;
  }
  iVar4 = iVar4 * 300;
  iVar1 = *(int *)((int)pvVar3 + 0xac) + 0x20 + iVar4;
  local_c = (uint)(*(float *)(*(int *)((int)pvVar3 + 0xac) + 0x20 + iVar4) -
                  *(float *)(*(int *)((int)pvVar3 + 0xac) + 0x2c + iVar4));
  local_8 = (uint)(*(float *)(iVar1 + 4) - *(float *)(*(int *)((int)pvVar3 + 0xac) + 0x30 + iVar4));
  local_4 = (uint)(*(float *)(iVar1 + 8) - *(float *)(*(int *)((int)pvVar3 + 0xac) + 0x34 + iVar4));
  Vec3_Normalize((float *)&local_c);
  uVar2 = lua_createtable();
  lua_pushobject(uVar2);
  lua_pushstring(&DAT_004e8454);
  lua_pushnumber(local_c);
  lua_settable();
  lua_pushobject(uVar2);
  lua_pushstring(&DAT_004e8450);
  lua_pushnumber(local_8);
  lua_settable();
  lua_pushobject(uVar2);
  lua_pushstring(&DAT_004ec3b8);
  lua_pushnumber(local_4);
  lua_settable();
  lua_pushobject(uVar2);
  return;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x0049fb00  Lua_PointActorAt ---- */
/* Lua opcode: PointActorAt(actor, x, y, z | actor). Creates the walker if missing, turns the walker
   heading all the way to the point (Walker_TurnToPoint with FLT_MAX) and negates the turn rate so
   Walker_UpdateYaw snaps the visible yaw next frame. Only the yaw changes; pitch and roll are not
   touched. */

void Lua_PointActorAt(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  float10 fVar7;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  iVar5 = lua_isuserdata(iVar1);
  if (((iVar5 == 0) || (iVar5 = lua_tag(iVar1), iVar5 != 0x52544341)) || (iVar1 == 0)) {
    lua_pushnil();
    return;
  }
  uVar6 = lua_getuserdata(iVar1);
  iVar1 = Actor_FromHandle(uVar6);
  iVar5 = lua_isuserdata(uVar2);
  if ((iVar5 == 0) || (iVar5 = lua_tag(uVar2), iVar5 != 0x52544341)) {
    fVar7 = (float10)lua_getnumber(uVar2);
    local_c = (uint)(float)fVar7;
    fVar7 = (float10)lua_getnumber(uVar3);
    local_8 = (uint)(float)fVar7;
    fVar7 = (float10)lua_getnumber(uVar4);
    local_4 = (uint)(float)fVar7;
  }
  else {
    uVar2 = lua_getuserdata(uVar2);
    iVar5 = Actor_FromHandle(uVar2);
    local_c = *(uint *)(iVar5 + 0xc);
    local_8 = *(uint *)(iVar5 + 0x10);
    local_4 = *(uint *)(iVar5 + 0x14);
  }
  if (*(int *)(*(int *)(iVar1 + 0xa4) + 0x1b4) == 0) {
    Actor_CreateWalker(iVar1,1);
  }
  Walker_TurnToPoint(*(void **)(*(int *)(iVar1 + 0xa4) + 0x1b4),(int)&local_c,0x7f7fffff);
  iVar1 = *(int *)(iVar1 + 0xa4);
  if (*(float *)(iVar1 + 0x1c) <= 0.0) {
    return;
  }
  *(float *)(iVar1 + 0x1c) = *(float *)(iVar1 + 0x1c) * -1.0;
  return;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
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
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  uVar4 = lua_lua2C(3);
  uVar5 = lua_lua2C(4);
  iVar6 = lua_isuserdata(iVar2);
  if (iVar6 == 0) goto LAB_0049fde2;
  iVar6 = lua_tag(iVar2);
  if ((iVar6 != 0x52544341) || (iVar2 == 0)) goto LAB_0049fde2;
  uVar7 = lua_getuserdata(iVar2);
  iVar2 = Actor_FromHandle(uVar7);
  iVar6 = lua_isuserdata(uVar3);
  if (iVar6 == 0) {
LAB_0049fd1e:
    fVar8 = (float10)lua_getnumber(uVar3);
    local_c = (uint)(float)fVar8;
    fVar8 = (float10)lua_getnumber(uVar4);
    local_8 = (uint)(float)fVar8;
    fVar8 = (float10)lua_getnumber(uVar5);
    local_4 = (uint)(float)fVar8;
  }
  else {
    iVar6 = lua_tag(uVar3);
    if (iVar6 != 0x52544341) goto LAB_0049fd1e;
    uVar3 = lua_getuserdata(uVar3);
    iVar6 = Actor_FromHandle(uVar3);
    local_c = *(uint *)(iVar6 + 0xc);
    local_8 = *(uint *)(iVar6 + 0x10);
    local_4 = *(uint *)(iVar6 + 0x14);
  }
  if (*(int *)(*(int *)(iVar2 + 0xa4) + 0x1b4) == 0) {
    Actor_CreateWalker(iVar2,1);
  }
  fVar1 = *(float *)(*(int *)(iVar2 + 0xa4) + 0x1c);
  if (*(float *)(*(int *)(iVar2 + 0xa4) + 0x1c) < 0.0) {
    fVar1 = -fVar1;
  }
  fVar9 = Timer_GetFrameSeconds();
  fVar10 = Walker_TurnToPoint(*(void **)(*(int *)(iVar2 + 0xa4) + 0x1b4),(int)&local_c,
                              (int)(fVar9 * fVar1));
  if (fVar10 < 0.0) {
    fVar10 = -fVar10;
  }
  if (fVar9 * fVar1 <= fVar10) {
    lua_pushnumber(FBITS(0x3f800000));
    return;
  }
LAB_0049fde2:
  lua_pushnil();
  return;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0049fdf0  Lua_PerSecond ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: PerSecond */

void Lua_PerSecond(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  float10 fVar2;
  float fVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  if (lua_isnumber_exref == (code *)0x0) {
    lua_pushnil();
  }
  fVar3 = Timer_GetFrameSeconds();
  fVar2 = (float10)lua_getnumber(uVar1);
  lua_pushnumber((float)(fVar2 * (float10)fVar3));
  return;
}
#undef local_4
#undef local_c


/* ---- 0x0049fe40  Lua_SnapToPlane ---- */
/* Lua opcode: SnapToPlane */

void Lua_SnapToPlane(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char *name;
  void *this;
  float10 fVar5;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  name = (char *)lua_getstring(uVar1);
  this = Sector_FindByName(name);
  if (this == (void *)0x0) {
    lua_pushnil();
    return;
  }
  fVar5 = (float10)lua_getnumber(uVar2);
  local_c = (uint)(float)fVar5;
  fVar5 = (float10)lua_getnumber(uVar3);
  local_8 = (uint)(float)fVar5;
  fVar5 = (float10)lua_getnumber(uVar4);
  local_4 = (uint)(float)fVar5;
  Sector_SnapToPlane(this,(float *)&local_c);
  lua_pushnumber(local_c);
  lua_pushnumber(local_8);
  lua_pushnumber(local_4);
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0049ff00  Lua_GetAngleBetweenVectors ---- */
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Lua opcode: GetAngleBetweenVectors */

void Lua_GetAngleBetweenVectors(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  float10 fVar5;
  float fVar6;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_istable(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_istable(uVar2);
    if (iVar3 != 0) {
      lua_pushobject(uVar1);
      lua_pushstring(&DAT_004e8454);
      uVar4 = lua_gettable();
      fVar5 = (float10)lua_getnumber(uVar4);
      local_c = (uint)(float)fVar5;
      lua_pushobject(uVar1);
      lua_pushstring(&DAT_004e8450);
      uVar4 = lua_gettable();
      fVar5 = (float10)lua_getnumber(uVar4);
      local_8 = (uint)(float)fVar5;
      lua_pushobject(uVar1);
      lua_pushstring(&DAT_004ec3b8);
      uVar1 = lua_gettable();
      fVar5 = (float10)lua_getnumber(uVar1);
      local_4 = (uint)(float)fVar5;
      lua_pushobject(uVar2);
      lua_pushstring(&DAT_004e8454);
      uVar1 = lua_gettable();
      fVar5 = (float10)lua_getnumber(uVar1);
      local_18 = (uint)(float)fVar5;
      lua_pushobject(uVar2);
      lua_pushstring(&DAT_004e8450);
      uVar1 = lua_gettable();
      fVar5 = (float10)lua_getnumber(uVar1);
      local_14 = (uint)(float)fVar5;
      lua_pushobject(uVar2);
      lua_pushstring(&DAT_004ec3b8);
      uVar1 = lua_gettable();
      fVar5 = (float10)lua_getnumber(uVar1);
      local_10 = (uint)(float)fVar5;
      Vec3_Normalize((float *)&local_c);
      Vec3_Normalize((float *)&local_18);
      fVar6 = Math_AsinDegreesSeries
                        ((float)local_10 * (float)local_4 +
                         (float)local_14 * (float)local_8 + (float)local_18 * (float)local_c);
      lua_pushnumber(90.0 - fVar6);
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
#undef local_30
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a00a0  Lua_GetAngleBetweenActors ---- */
/* WARNING: Variable defined which should be unmapped: local_30 */
/* Lua opcode: GetAngleBetweenActors */

void Lua_GetAngleBetweenActors(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  iVar4 = lua_isuserdata(uVar2);
  if (iVar4 != 0) {
    iVar4 = lua_tag(uVar2);
    if (iVar4 == 0x52544341) {
      iVar4 = lua_isuserdata(uVar3);
      if (iVar4 != 0) {
        iVar4 = lua_tag(uVar3);
        if (iVar4 == 0x52544341) {
          uVar2 = lua_getuserdata(uVar2);
          iVar4 = Actor_FromHandle(uVar2);
          uVar2 = lua_getuserdata(uVar3);
          iVar5 = Actor_FromHandle(uVar2);
          if (((iVar4 != 0) && (iVar5 != 0)) &&
             (iVar1 = *(int *)(*(int *)(iVar4 + 0xa4) + 0x1b4), iVar1 != 0)) {
            local_c = *(uint *)(iVar1 + 0x18);
            local_8 = *(uint *)(iVar1 + 0x1c);
            local_4 = *(uint *)(iVar1 + 0x20);
            local_18 = (uint)(*(float *)(iVar5 + 0xc) - *(float *)(iVar4 + 0xc));
            local_14 = (uint)(*(float *)(iVar5 + 0x10) - *(float *)(iVar4 + 0x10));
            local_10 = (uint)((float)local_4 - *(float *)(iVar4 + 0x14));
            Vec3_Normalize((float *)&local_c);
            Vec3_Normalize((float *)&local_18);
            fVar6 = Math_AsinDegreesSeries
                              ((float)local_10 * (float)local_4 +
                               (float)local_14 * (float)local_8 + (float)local_18 * (float)local_c);
            lua_pushnumber(90.0 - fVar6);
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


/* ---- 0x004a0230  Lua_SetAmbientLight ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: SetAmbientLight */

void Lua_SetAmbientLight(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  void *pvVar3;
  float10 fVar4;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    pvVar3 = Set_GetCurrent();
    if (pvVar3 != (void *)0x0) {
      fVar4 = (float10)lua_getnumber(uVar1);
      rdCamera_SetAmbientLight
                (*(void **)(*(int *)((int)pvVar3 + 0xac) + 0x48 + *(int *)((int)pvVar3 + 0xb4) * 300
                           ),(float)fVar4);
    }
  }
  return;
}
#undef local_c


/* ---- 0x004a0290  Lua_FindLight ---- */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: FindLight */

void Lua_FindLight(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  char *name;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    name = (char *)lua_getstring(uVar1);
    iVar2 = Light_FindByName((void *)0x0,name);
    if (iVar2 != -1) {
      lua_pushnumber((float)iVar2);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_4
#undef local_c


/* ---- 0x004a02f0  Lua_TurnLightOn ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: TurnLightOn */

void Lua_TurnLightOn(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  char *name;
  void *pvVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(uVar1);
  if (iVar3 == 0) {
    iVar3 = lua_isstring(uVar1);
    if (iVar3 == 0) {
      return;
    }
    name = (char *)lua_getstring(uVar1);
    iVar3 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar3 = (int)lVar5;
  }
  pvVar4 = Light_Get((void *)0x0,iVar3);
  if (pvVar4 != (void *)0x0) {
    iVar3 = lua_isnil(uVar2);
    *(uint *)((int)pvVar4 + 0x34) = (uint)(iVar3 == 0);
  }
  return;
}
#endif


/* ---- 0x004a0380  Lua_IsLightOn ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: IsLightOn */

void Lua_IsLightOn(void)

{
  undefined4 uVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  undefined4 unaff_ESI;
  longlong lVar4;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(uVar1);
    if (iVar2 == 0) goto LAB_004a03f5;
    name = (char *)lua_getstring(uVar1);
    iVar2 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar4 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    iVar2 = (int)lVar4;
  }
  pvVar3 = Light_Get((void *)0x0,iVar2);
  if ((pvVar3 != (void *)0x0) && (*(int *)((int)pvVar3 + 0x34) != 0)) {
    lua_pushnumber(FBITS(0x3f800000));
    return;
  }
LAB_004a03f5:
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a0400  Lua_SetLightType ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetLightType */

void Lua_SetLightType(void)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *pvVar4;
  int iVar5;
  char *name;
  void *pvVar6;
  int iVar7;
  uint uVar8;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar9;
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  pvVar4 = Set_GetCurrent();
  iVar5 = lua_isnumber(uVar2);
  if (iVar5 == 0) {
    iVar5 = lua_isstring(uVar2);
    if (iVar5 == 0) {
      return;
    }
    name = (char *)lua_getstring(uVar2);
    iVar5 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar5 = (int)lVar9;
  }
  pvVar6 = Light_Get((void *)0x0,iVar5);
  if (pvVar6 != (void *)0x0) {
    iVar7 = lua_isstring(uVar3);
    if (iVar7 != 0) {
      uVar2 = lua_getstring(uVar3);
      iVar7 = String_ContainsSubstring(uVar2,s_parallel_004ec5a8);
      if ((iVar7 == 0) && (iVar7 = String_ContainsSubstring(uVar2,s_global_004ec5a0), iVar7 == 0)) {
        iVar7 = String_ContainsSubstring(uVar2,&DAT_004ec598);
        if (iVar7 == 0) {
          *(undefined4 *)((int)pvVar6 + 0x30) = 2;
        }
        else {
          *(undefined4 *)((int)pvVar6 + 0x30) = 3;
        }
      }
      else {
        *(undefined4 *)((int)pvVar6 + 0x30) = 1;
      }
      uVar8 = 0;
      if (*(int *)((int)pvVar4 + 0xb0) != 0) {
        iVar7 = 0;
        do {
          uVar8 = uVar8 + 1;
          piVar1 = (int *)(*(int *)((int)pvVar4 + 0xac) + 0x48 + iVar7);
          iVar7 = iVar7 + 300;
          *(undefined4 *)(*(int *)(*piVar1 + iVar5 * 4 + 0x5c) + 4) =
               *(undefined4 *)((int)pvVar6 + 0x30);
        } while (uVar8 < *(uint *)((int)pvVar4 + 0xb0));
      }
      return;
    }
    return;
  }
  return;
}
#endif


/* ---- 0x004a0530  Lua_GetLightType ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: GetLightType */

void Lua_GetLightType(void)

{
  undefined4 uVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  undefined4 unaff_ESI;
  longlong lVar4;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(uVar1);
    if (iVar2 == 0) goto LAB_004a05d0;
    name = (char *)lua_getstring(uVar1);
    iVar2 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar4 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    iVar2 = (int)lVar4;
  }
  pvVar3 = Light_Get((void *)0x0,iVar2);
  if (pvVar3 != (void *)0x0) {
    iVar2 = *(int *)((int)pvVar3 + 0x30);
    if (iVar2 == 1) {
      lua_pushstring(s_parallel_004ec5a8);
      return;
    }
    if (iVar2 == 3) {
      lua_pushstring(&DAT_004ec598);
      return;
    }
    if (iVar2 == 2) {
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetLightPosition */

void Lua_SetLightPosition(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  char *name;
  void *pvVar7;
  void *pvVar8;
  int iVar9;
  uint uVar10;
  float *pfVar11;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  longlong lVar15;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  uVar4 = lua_lua2C(3);
  uVar5 = lua_lua2C(4);
  iVar6 = lua_isnumber(uVar2);
  if (iVar6 == 0) {
    iVar6 = lua_isstring(uVar2);
    if (iVar6 == 0) {
      return;
    }
    name = (char *)lua_getstring(uVar2);
    iVar6 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar15 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar6 = (int)lVar15;
  }
  pvVar7 = Set_GetCurrent();
  if ((((pvVar7 != (void *)0x0) && (pvVar8 = Light_Get((void *)0x0,iVar6), pvVar8 != (void *)0x0))
      && (iVar9 = lua_isnumber(uVar3), iVar9 != 0)) &&
     ((iVar9 = lua_isnumber(uVar4), iVar9 != 0 && (iVar9 = lua_isnumber(uVar5), iVar9 != 0)))) {
    fVar12 = (float10)lua_getnumber(uVar3);
    fVar13 = (float10)lua_getnumber(uVar4);
    fVar14 = (float10)lua_getnumber(uVar5);
    *(float *)((int)pvVar8 + 0x20) = (float)fVar12;
    *(float *)((int)pvVar8 + 0x24) = (float)fVar13;
    *(float *)((int)pvVar8 + 0x28) = (float)fVar14;
    uVar10 = 0;
    if (*(int *)((int)pvVar7 + 0xb0) != 0) {
      iVar9 = 0;
      do {
        piVar1 = (int *)(*(int *)((int)pvVar7 + 0xac) + 0x48 + iVar9);
        iVar9 = iVar9 + 300;
        pfVar11 = (float *)(*piVar1 + (iVar6 + 0x1d) * 0xc);
        uVar10 = uVar10 + 1;
        *pfVar11 = (float)fVar12;
        pfVar11[1] = (float)fVar13;
        pfVar11[2] = (float)fVar14;
      } while (uVar10 < *(uint *)((int)pvVar7 + 0xb0));
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: GetLightPosition */

void Lua_GetLightPosition(void)

{
  undefined4 uVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(uVar1);
    if (iVar2 == 0) goto LAB_004a07f0;
    name = (char *)lua_getstring(uVar1);
    iVar2 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar2 = (int)lVar4;
  }
  pvVar3 = Set_GetCurrent();
  if (pvVar3 != (void *)0x0) {
    pvVar3 = Light_Get((void *)0x0,iVar2);
    if (pvVar3 != (void *)0x0) {
      lua_pushnumber(*(undefined4 *)((int)pvVar3 + 0x20));
      lua_pushnumber(*(undefined4 *)((int)pvVar3 + 0x24));
      lua_pushnumber(*(undefined4 *)((int)pvVar3 + 0x28));
      return;
    }
  }
LAB_004a07f0:
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a0800  Lua_SetLightRotation ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetLightRotation */

void Lua_SetLightRotation(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  void *pvVar7;
  int iVar8;
  char *name;
  void *pvVar9;
  int iVar10;
  uint uVar11;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  float10 fVar12;
  longlong lVar13;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  uVar3 = lua_lua2C(1);
  uVar4 = lua_lua2C(2);
  uVar5 = lua_lua2C(3);
  uVar6 = lua_lua2C(4);
  pvVar7 = Set_GetCurrent();
  iVar8 = lua_isnumber(uVar3);
  if (iVar8 == 0) {
    iVar8 = lua_isstring(uVar3);
    if (iVar8 == 0) {
      return;
    }
    name = (char *)lua_getstring(uVar3);
    iVar8 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar13 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar8 = (int)lVar13;
  }
  pvVar9 = Light_Get((void *)0x0,iVar8);
  if (pvVar9 != (void *)0x0) {
    iVar10 = lua_isnumber(uVar4);
    if (iVar10 == 0) {
      local_c = 0;
    }
    else {
      fVar12 = (float10)lua_getnumber(uVar4);
      local_c = (uint)(float)fVar12;
    }
    iVar10 = lua_isnumber(uVar5);
    if (iVar10 == 0) {
      local_8 = 0;
    }
    else {
      fVar12 = (float10)lua_getnumber(uVar5);
      local_8 = (uint)(float)fVar12;
    }
    iVar10 = lua_isnumber(uVar6);
    if (iVar10 == 0) {
      local_4 = 0;
    }
    else {
      fVar12 = (float10)lua_getnumber(uVar6);
      local_4 = (uint)(float)fVar12;
    }
    local_18 = 0;
    local_14 = 0x3f800000;
    local_10 = 0;
    Vec3_Rotate((float *)&local_18,(float *)&local_c);
    *(uint *)((int)pvVar9 + 0x38) = local_18;
    *(uint *)((int)pvVar9 + 0x3c) = local_14;
    uVar11 = 0;
    *(uint *)((int)pvVar9 + 0x40) = local_10;
    if (*(int *)((int)pvVar7 + 0xb0) != 0) {
      iVar10 = 0;
      do {
        piVar1 = (int *)(*(int *)((int)pvVar7 + 0xac) + 0x48 + iVar10);
        iVar10 = iVar10 + 300;
        iVar2 = *(int *)(*piVar1 + iVar8 * 4 + 0x5c);
        uVar11 = uVar11 + 1;
        *(uint *)(iVar2 + 0xc) = local_18;
        *(uint *)(iVar2 + 0x10) = local_14;
        *(uint *)(iVar2 + 0x14) = local_10;
      } while (uVar11 < *(uint *)((int)pvVar7 + 0xb0));
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_c */
/* Lua opcode: GetLightRotation */

void Lua_GetLightRotation(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  undefined4 unaff_ESI;
  longlong lVar4;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(uVar1);
    if (iVar2 == 0) goto LAB_004a0a3b;
    name = (char *)lua_getstring(uVar1);
    iVar2 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar4 = _ftol((double)CONCAT44(local_c,unaff_ESI));
    iVar2 = (int)lVar4;
  }
  pvVar3 = Light_Get((void *)0x0,iVar2);
  if (pvVar3 != (void *)0x0) {
    Matrix_GetAngles((float *)((int)pvVar3 + 0x38),(float *)&local_c);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetLightAngles */

void Lua_SetLightAngles(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  char *name;
  void *pvVar5;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  float10 fVar6;
  longlong lVar7;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  iVar4 = lua_isnumber(uVar1);
  if (iVar4 == 0) {
    iVar4 = lua_isstring(uVar1);
    if (iVar4 == 0) {
      return;
    }
    name = (char *)lua_getstring(uVar1);
    iVar4 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar7 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar4 = (int)lVar7;
  }
  pvVar5 = Light_Get((void *)0x0,iVar4);
  if (pvVar5 != (void *)0x0) {
    iVar4 = lua_isnumber(uVar2);
    if (iVar4 == 0) {
      local_4 = 0;
    }
    else {
      fVar6 = (float10)lua_getnumber(uVar2);
      local_4 = (uint)(float)fVar6;
    }
    iVar4 = lua_isnumber(uVar3);
    if (iVar4 == 0) {
      local_8 = 0;
    }
    else {
      fVar6 = (float10)lua_getnumber(uVar3);
      local_8 = (uint)(float)fVar6;
    }
    rdLight_SetAngles((void *)((int)pvVar5 + 0x2c),(float)local_4,(float)local_8);
  }
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a0b40  Lua_GetLightAngles ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: GetLightAngles */

void Lua_GetLightAngles(void)

{
  undefined4 uVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(uVar1);
    if (iVar2 == 0) goto LAB_004a0bbc;
    name = (char *)lua_getstring(uVar1);
    iVar2 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar2 = (int)lVar4;
  }
  pvVar3 = Light_Get((void *)0x0,iVar2);
  if (pvVar3 != (void *)0x0) {
    lua_pushnumber(*(undefined4 *)((int)pvVar3 + 0x4c));
    lua_pushnumber(*(undefined4 *)((int)pvVar3 + 0x54));
    return;
  }
LAB_004a0bbc:
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a0bd0  Lua_PointLightAt ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: PointLightAt */

void Lua_PointLightAt(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  char *name;
  void *pvVar6;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  float10 fVar7;
  longlong lVar8;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  iVar5 = lua_isnumber(uVar1);
  if (iVar5 == 0) {
    iVar5 = lua_isstring(uVar1);
    if (iVar5 == 0) {
      return;
    }
    name = (char *)lua_getstring(uVar1);
    iVar5 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar5 = (int)lVar8;
  }
  pvVar6 = Light_Get((void *)0x0,iVar5);
  if (pvVar6 != (void *)0x0) {
    iVar5 = lua_isuserdata(uVar2);
    if (((iVar5 == 0) || (iVar5 = lua_tag(uVar2), iVar5 != 0x52544341)) &&
       (iVar5 = lua_isnumber(uVar2), iVar5 == 0)) {
      return;
    }
    iVar5 = lua_isuserdata(uVar2);
    if ((iVar5 == 0) || (iVar5 = lua_tag(uVar2), iVar5 != 0x52544341)) {
      fVar7 = (float10)lua_getnumber(uVar2);
      local_18 = (uint)(float)fVar7;
      iVar5 = lua_isnumber(uVar3);
      if (iVar5 == 0) {
        local_14 = 0;
      }
      else {
        fVar7 = (float10)lua_getnumber(uVar3);
        local_14 = (uint)(float)fVar7;
      }
      iVar5 = lua_isnumber(uVar4);
      if (iVar5 == 0) {
        local_10 = 0;
      }
      else {
        fVar7 = (float10)lua_getnumber(uVar4);
        local_10 = (uint)(float)fVar7;
      }
    }
    else {
      uVar1 = lua_getuserdata(uVar2);
      iVar5 = Actor_FromHandle(uVar1);
      local_18 = *(uint *)(iVar5 + 0xc);
      local_14 = *(uint *)(iVar5 + 0x10);
      local_10 = *(uint *)(iVar5 + 0x14);
    }
    local_c = (uint)((float)local_18 - *(float *)((int)pvVar6 + 0x20));
    local_8 = (uint)((float)local_14 - *(float *)((int)pvVar6 + 0x24));
    local_4 = (uint)((float)local_10 - *(float *)((int)pvVar6 + 0x28));
    Vec3_Normalize((float *)&local_c);
    *(uint *)((int)pvVar6 + 0x38) = local_c;
    *(uint *)((int)pvVar6 + 0x3c) = local_8;
    *(uint *)((int)pvVar6 + 0x40) = local_4;
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetLightIntensity */

void Lua_SetLightIntensity(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *pvVar4;
  int iVar5;
  char *name;
  void *pvVar6;
  int iVar7;
  uint uVar8;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  float10 fVar9;
  longlong lVar10;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar2 = lua_lua2C(1);
  uVar3 = lua_lua2C(2);
  pvVar4 = Set_GetCurrent();
  iVar5 = lua_isnumber(uVar2);
  if (iVar5 == 0) {
    iVar5 = lua_isstring(uVar2);
    if (iVar5 == 0) {
      return;
    }
    name = (char *)lua_getstring(uVar2);
    iVar5 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar10 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar5 = (int)lVar10;
  }
  pvVar6 = Light_Get((void *)0x0,iVar5);
  if ((pvVar6 != (void *)0x0) && (iVar7 = lua_isnumber(uVar3), iVar7 != 0)) {
    fVar9 = (float10)lua_getnumber(uVar3);
    *(float *)((int)pvVar6 + 0x44) = (float)fVar9;
    uVar8 = 0;
    if (*(int *)((int)pvVar4 + 0xb0) != 0) {
      iVar7 = 0;
      do {
        fVar9 = (float10)lua_getnumber(uVar3);
        uVar8 = uVar8 + 1;
        piVar1 = (int *)(*(int *)((int)pvVar4 + 0xac) + 0x48 + iVar7);
        iVar7 = iVar7 + 300;
        *(float *)(*(int *)(*piVar1 + iVar5 * 4 + 0x5c) + 0x18) = (float)fVar9;
      } while (uVar8 < *(uint *)((int)pvVar4 + 0xb0));
    }
  }
  return;
}
#undef local_4

#endif


/* ---- 0x004a0e90  Lua_GetLightIntensity ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: GetLightIntensity */

void Lua_GetLightIntensity(void)

{
  undefined4 uVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  
  uVar1 = lua_lua2C(1);
  lua_lua2C(2);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(uVar1);
    if (iVar2 == 0) goto LAB_004a0f08;
    name = (char *)lua_getstring(uVar1);
    iVar2 = Light_FindByName((void *)0x0,name);
  }
  else {
    lua_getnumber();
    lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar2 = (int)lVar4;
  }
  pvVar3 = Light_Get((void *)0x0,iVar2);
  if (pvVar3 != (void *)0x0) {
    lua_pushnumber(*(undefined4 *)((int)pvVar3 + 0x44));
    return;
  }
LAB_004a0f08:
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a0f20  Lua_ImStartRecording ---- */
/* Lua opcode: ImStartRecording */

void Lua_ImStartRecording(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isstring(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_isnil(uVar2);
    uVar1 = lua_getstring(uVar1,iVar3 == 0);
    ImStartRecording(uVar1);
  }
  return;
}

/* ---- 0x004a0f80  Lua_ImStartSound ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_18 */
/* Lua opcodes: ImStartSound, play
   also registered as `play` */

void Lua_ImStartSound(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  iVar4 = lua_isstring(uVar1);
  if ((iVar4 == 0) && (iVar4 = lua_isnil(uVar1), iVar4 == 0)) {
    return;
  }
  iVar4 = lua_isnumber(uVar2);
  if ((iVar4 != 0) && (iVar4 = lua_isnumber(uVar3), iVar4 != 0)) {
    lua_getnumber(uVar3);
    lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    lua_getnumber(uVar2);
    lVar5 = _ftol((double)CONCAT44(unaff_EDI,(int)lVar5));
    uVar1 = lua_getstring(uVar1,(int)lVar5);
    iVar4 = SoundsLoadStartSound(uVar1);
    lua_pushnumber((float)iVar4);
  }
  return;
}
#undef local_18
#undef local_4

#endif


/* ---- 0x004a1030  Lua_ImStopSound ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImStopSound */

void Lua_ImStopSound(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber();
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    SoundsStopSound((int)lVar3,unaff_ESI);
    return;
  }
  uVar1 = lua_getstring(uVar1);
  SoundsStopSound(uVar1);
  return;
}
#endif


/* ---- 0x004a1090  Lua_ImGetParam ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_10 */
/* Lua opcode: ImGetParam */

void Lua_ImGetParam(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(uVar1);
  if (iVar3 == 0) {
    iVar3 = lua_isstring(uVar2);
    if (iVar3 == 0) {
      lua_pushnumber(FBITS(0xbf800000));
      return;
    }
    lua_getnumber(uVar2);
    lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    uVar1 = lua_getstring(uVar1,(int)lVar4);
  }
  else {
    lua_getnumber();
    lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    lua_getnumber(uVar1);
    lVar4 = _ftol((double)CONCAT44(unaff_EDI,(int)lVar4));
    uVar1 = (undefined4)lVar4;
  }
  iVar3 = SoundsGetParam(uVar1);
  lua_pushnumber((float)iVar3);
  return;
}
#undef local_10
#undef local_4

#endif


/* ---- 0x004a1140  Lua_ImSetParam ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: ImSetParam */

void Lua_ImSetParam(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  iVar4 = lua_isnumber(uVar1);
  if ((iVar4 == 0) && (iVar4 = lua_isstring(uVar1), iVar4 == 0)) {
    return;
  }
  iVar4 = lua_isnumber(uVar2);
  if ((iVar4 != 0) && (iVar4 = lua_isnumber(uVar3), iVar4 != 0)) {
    iVar4 = lua_isnumber(uVar1);
    if (iVar4 != 0) {
      lua_getnumber(uVar3);
      lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      if ((int)lVar5 < 1) {
        uVar3 = 0;
      }
      else {
        lua_getnumber(uVar3);
        lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        uVar3 = (undefined4)lVar5;
      }
      lua_getnumber(uVar2);
      lVar5 = _ftol((double)CONCAT44(unaff_EDI,uVar3));
      uVar2 = (undefined4)lVar5;
      lua_getnumber(uVar1);
      lVar5 = _ftol((double)CONCAT44(uVar3,uVar2));
      SoundsSetParam((int)lVar5);
      return;
    }
    iVar4 = lua_isstring(uVar1);
    if (iVar4 != 0) {
      lua_getnumber(uVar3);
      lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      if ((int)lVar5 < 1) {
        uVar3 = 0;
      }
      else {
        lua_getnumber(uVar3);
        lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        uVar3 = (undefined4)lVar5;
      }
      lua_getnumber(uVar2);
      lVar5 = _ftol((double)CONCAT44(unaff_EDI,uVar3));
      uVar1 = lua_getstring(uVar1,(int)lVar5);
      SoundsSetParam(uVar1);
    }
  }
  return;
}
#endif


/* ---- 0x004a1260  Lua_ImFadeParam ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: ImFadeParam */

void Lua_ImFadeParam(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  iVar5 = lua_isstring(uVar1);
  if (iVar5 == 0) {
    iVar5 = lua_isnumber(uVar1);
    if (iVar5 == 0) {
      lua_pushnumber(0);
      return;
    }
  }
  iVar5 = lua_isnumber(uVar2);
  if (iVar5 != 0) {
    iVar5 = lua_isnumber(uVar3);
    if (iVar5 != 0) {
      iVar5 = lua_isnumber(uVar4);
      if (iVar5 != 0) {
        iVar5 = lua_isnumber(uVar1);
        if (iVar5 != 0) {
          lua_getnumber(uVar3);
          lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          if ((int)lVar6 < 1) {
            uVar3 = 0;
          }
          else {
            lua_getnumber(uVar3);
            lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
            uVar3 = (undefined4)lVar6;
          }
          lua_getnumber(uVar4);
          lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          uVar4 = (undefined4)lVar6;
          lua_getnumber(uVar2);
          lVar6 = _ftol((double)CONCAT44(uVar4,uVar3));
          uVar2 = (undefined4)lVar6;
          lua_getnumber(uVar1);
          lVar6 = _ftol((double)CONCAT44(uVar3,uVar2));
          SoundsFadeParam((int)lVar6);
          return;
        }
        lua_getnumber(uVar3);
        lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        if ((int)lVar6 < 1) {
          uVar3 = 0;
        }
        else {
          lua_getnumber(uVar3);
          lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
          uVar3 = (undefined4)lVar6;
        }
        lua_getnumber(uVar4);
        lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        uVar4 = (undefined4)lVar6;
        lua_getnumber(uVar2);
        lVar6 = _ftol((double)CONCAT44(uVar4,uVar3));
        uVar1 = lua_getstring(uVar1,(int)lVar6);
        SoundsFadeParam(uVar1);
      }
    }
  }
  return;
}
#undef local_4

#endif


/* ---- 0x004a13d0  Lua_ImGetMasterVol ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Lua opcode: ImGetMasterVol */

void __fastcall Lua_ImGetMasterVol(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ImSetGroupVol(0,0xffffffff,param_1);
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004a1400  Lua_ImSetMasterVol ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetMasterVol */

void Lua_ImSetMasterVol(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    ImSetGroupVol(0,(int)lVar3,unaff_ESI);
  }
  return;
}
#endif


/* ---- 0x004a1440  Lua_ImGetSfxVol ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Lua opcode: ImGetSfxVol */

void __fastcall Lua_ImGetSfxVol(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ImSetGroupVol(1,0xffffffff,param_1);
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004a1470  Lua_ImSetSfxVol ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetSfxVol */

void Lua_ImSetSfxVol(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    ImSetGroupVol(1,(int)lVar3,unaff_ESI);
  }
  return;
}
#endif


/* ---- 0x004a14b0  Lua_ImGetVoiceVol ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Lua opcode: ImGetVoiceVol */

void __fastcall Lua_ImGetVoiceVol(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ImSetGroupVol(2,0xffffffff,param_1);
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004a14e0  Lua_ImSetVoiceVol ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetVoiceVol */

void Lua_ImSetVoiceVol(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    ImSetGroupVol(2,(int)lVar3,unaff_ESI);
  }
  return;
}
#endif


/* ---- 0x004a1520  Lua_ImGetMusicVol ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Lua opcode: ImGetMusicVol */

void __fastcall Lua_ImGetMusicVol(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = ImSetGroupVol(3,0xffffffff,param_1);
  lua_pushnumber((float)iVar1);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004a1550  Lua_ImSetMusicVol ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetMusicVol */

void Lua_ImSetMusicVol(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    ImSetGroupVol(3,(int)lVar3,unaff_ESI);
  }
  return;
}
#endif


/* ---- 0x004a1590  Lua_ImStartVoice ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: ImStartVoice */

void Lua_ImStartVoice(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  iVar4 = lua_isstring(uVar1);
  if ((iVar4 == 0) && (iVar4 = lua_isnil(uVar1), iVar4 == 0)) {
    return;
  }
  iVar4 = lua_isnumber(uVar2);
  if ((iVar4 != 0) && (iVar4 = lua_isnumber(uVar3), iVar4 != 0)) {
    lua_getnumber(uVar3);
    lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    uVar3 = (undefined4)lVar5;
    lua_getnumber(uVar2);
    lVar5 = _ftol((double)CONCAT44(unaff_EDI,uVar3));
    uVar1 = lua_getstring(uVar1,(int)lVar5);
    SoundStartVoiceStream(uVar1);
  }
  return;
}
#endif


/* ---- 0x004a1640  Lua_ImSetState ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetState */

void Lua_ImSetState(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    Engine_SetIMuseState((int)lVar3);
  }
  return;
}
#endif


/* ---- 0x004a1680  Lua_ImSetSequence ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_c */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* Lua opcode: ImSetSequence */

void __fastcall Lua_ImSetSequence(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(param_1,unaff_ESI));
    iVar2 = ImSetSequence((int)lVar3);
    lua_pushnumber((float)iVar2);
  }
  return;
}
#undef local_4
#undef local_c

#endif


/* ---- 0x004a16d0  Lua_ImSetCuePoint ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: ImSetCuePoint */

void Lua_ImSetCuePoint(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    ImSetCuePoint((int)lVar3,unaff_ESI);
  }
  return;
}
#endif


/* ---- 0x004a1710  Lua_ImSetAttribute ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Lua opcode: ImSetAttribute */

void Lua_ImSetAttribute(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isnumber(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_isnumber(uVar2);
    if (iVar3 != 0) {
      lua_getnumber(uVar2);
      lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      lua_getnumber(uVar1);
      lVar4 = _ftol((double)CONCAT44(unaff_EDI,(int)lVar4));
      iVar3 = ImSetAttribute((int)lVar4);
      lua_pushnumber((float)iVar3);
    }
  }
  return;
}
#undef local_14
#undef local_4

#endif


/* ---- 0x004a17b0  Lua_ImSetVoiceEffect ---- */
/* Lua opcodes: vfx, ImSetVoiceEffect
   also registered as `vfx` */

void Lua_ImSetVoiceEffect(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if ((iVar2 == 0) && (iVar2 = lua_isnil(uVar1), iVar2 == 0)) {
    return;
  }
  uVar1 = lua_getstring(uVar1);
  iMUSE_SetVoiceEffect(uVar1);
  return;
}

/* ---- 0x004a17f0  Lua_ImGetMemoryFootprint ---- */
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


/* ---- 0x004a1820  Lua_ImGetSoundCacheSize ---- */
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


/* ---- 0x004a1850  Lua_SetGamma ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* Lua opcode: SetGamma */

void Lua_SetGamma(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  float10 fVar3;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if ((iVar2 != 0) && (UINT_008a8c40 != 4)) {
    fVar3 = (float10)lua_getnumber(uVar1);
    Render_SetGamma((float)fVar3);
  }
  return;
}
#undef local_8


/* ---- 0x004a1890  Lua_SetActorWalkDominate ---- */
/* Lua opcode: SetActorWalkDominate */

void Lua_SetActorWalkDominate(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  void *actor;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnil(uVar2);
      uVar1 = lua_getuserdata(uVar1);
      actor = (void *)Actor_FromHandle(uVar1);
      Actor_SetWalkDominate(actor,iVar3);
    }
  }
  return;
}

/* ---- 0x004a1900  Lua_SetActorConstrain ---- */
/* Lua opcode: SetActorConstrain */

void Lua_SetActorConstrain(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnil(uVar2);
      uVar1 = lua_getuserdata(uVar1);
      uVar1 = Actor_FromHandle(uVar1);
      Actor_SetConstrain(uVar1,iVar3 == 0);
    }
  }
  return;
}

/* ---- 0x004a1970  Lua_RenderModeUser ---- */
/* Lua opcode: RenderModeUser */

void Lua_RenderModeUser(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(uVar1);
  if ((iVar2 != 0) && (UINT_008a8c40 == 4)) {
    Movie_SetPaused(0);
    Render_RequestFullRedraw();
    UINT_008a8c40 = Engine_GetSavedValue();
    return;
  }
  iVar2 = lua_isnil(uVar1);
  if ((iVar2 == 0) && (UINT_008a8c40 != 4)) {
    Engine_SetSavedValue(UINT_008a8c40);
    Movie_SetPaused(1);
    UINT_008a8c40 = 4;
  }
  return;
}

/* ---- 0x004a19f0  Lua_DimScreen ---- */
/* Lua opcode: DimScreen */

void Lua_DimScreen(void)

{
  Render_DimBackground(0,2);
  return;
}

/* ---- 0x004a1a00  Lua_DimRegion ---- */
/* replaced by the hand-written version in build/overrides.c */
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
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  float unaff_ESI;
  float unaff_EDI;
  float10 fVar6;
  longlong lVar7;
  longlong lVar8;
  longlong lVar9;
  longlong lVar10;
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_4 (*(uint *)(_frame + (0x50 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  uVar5 = lua_lua2C(5);
  lua_getnumber(uVar1);
  lVar7 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  lua_getnumber(uVar2);
  lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  lua_getnumber(uVar3);
  lVar9 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  lua_getnumber(uVar4);
  lVar10 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  fVar6 = (float10)lua_getnumber(uVar5);
  Render_FillRect((int)lVar7,(int)lVar8,(int)lVar9,(int)lVar10,(float)fVar6,unaff_EDI,unaff_ESI);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: SetSpeechMode */

void Lua_SetSpeechMode(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    iVar2 = (int)lVar3;
    if (iVar2 == 1) {
      Speech_SetMode(1);
    }
    else {
      if (iVar2 == 2) {
        Speech_SetMode(2);
        return;
      }
      if (iVar2 == 3) {
        Speech_SetMode(3);
        return;
      }
    }
  }
  return;
}
#endif


/* ---- 0x004a1b40  Lua_GetSpeechMode ---- */
/* Lua opcode: GetSpeechMode */

void Lua_GetSpeechMode(void)

{
  byte bVar1;
  
  bVar1 = Speech_GetMode();
  if ((bVar1 & 2) == 0) {
    if ((bVar1 & 1) != 0) {
      lua_pushnumber(FBITS(0x3f800000));
      return;
    }
  }
  else if ((bVar1 & 1) != 0) {
    lua_pushnumber(FBITS(0x40400000));
    return;
  }
  lua_pushnumber(FBITS(0x40000000));
  return;
}

/* ---- 0x004a1b80  Lua_ActorShadow ---- */
/* Lua opcode: ActorShadow */

void Lua_ActorShadow(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  void *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if ((iVar2 == 0x52544341) && (iVar1 != 0)) {
      uVar3 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(uVar3);
      iVar1 = Actor_HasShadow(actor);
      if (iVar1 != 0) {
        lua_pushnumber(FBITS(0x3f800000));
        return;
      }
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a1bf0  Lua_ActivateActorShadow ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: ActivateActorShadow */

void Lua_ActivateActorShadow(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  void *actor;
  undefined4 unaff_EDI;
  longlong lVar6;
  uint active;
  
  iVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  iVar4 = lua_isuserdata(iVar1);
  if (iVar4 != 0) {
    iVar4 = lua_tag(iVar1);
    if ((iVar4 == 0x52544341) && (iVar1 != 0)) {
      uVar5 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(uVar5);
      iVar1 = lua_isnil(uVar3);
      active = (uint)(iVar1 == 0);
      lua_getnumber(uVar2);
      lVar6 = _ftol((double)CONCAT44(unaff_EDI,active));
      Actor_ActivateShadow(actor,(int)lVar6,active);
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a1c90  Lua_SetActorShadowPlane ---- */
/* Lua opcode: SetActorShadowPlane */

void Lua_SetActorShadowPlane(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      uVar4 = lua_getuserdata(iVar1);
      uVar4 = Actor_FromHandle(uVar4);
      uVar2 = lua_getstring(uVar2);
      Actor_SetShadowPlane(uVar4,uVar2);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a1d10  Lua_SetActorShadowPoint ---- */
/* WARNING: Variable defined which should be unmapped: local_18 */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: SetActorShadowPoint */

void Lua_SetActorShadowPoint(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  void *actor;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  iVar5 = lua_isuserdata(iVar1);
  if (iVar5 != 0) {
    iVar5 = lua_tag(iVar1);
    if ((iVar5 == 0x52544341) && (iVar1 != 0)) {
      uVar6 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(uVar6);
      fVar7 = (float10)lua_getnumber(uVar4);
      fVar8 = (float10)lua_getnumber(uVar3);
      fVar9 = (float10)lua_getnumber(uVar2);
      Actor_SetShadowPoint(actor,(float)fVar9,(float)fVar8,(float)fVar7);
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


/* ---- 0x004a1dc0  Lua_SetActiveShadow ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetActiveShadow */

void Lua_SetActiveShadow(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  
  iVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      uVar4 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(uVar4);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      lua_getnumber(uVar2);
      lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      *(int *)(*(int *)(iVar1 + 0xa4) + 500) = (int)lVar5;
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a1e50  Lua_ActorDistToShadowPlane ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: ActorDistToShadowPlane */

void Lua_ActorDistToShadowPlane(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar7;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar4 = lua_lua2C(1);
  uVar5 = lua_lua2C(2);
  lua_getnumber(uVar5);
  lVar7 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  iVar6 = lua_isuserdata(iVar4);
  if (iVar6 != 0) {
    iVar6 = lua_tag(iVar4);
    if ((iVar6 == 0x52544341) && (iVar4 != 0)) {
      uVar5 = lua_getuserdata(iVar4);
      iVar4 = Actor_FromHandle(uVar5);
      if (*(int *)(iVar4 + 0xa4) == 0) {
        Actor_CreateExtra(iVar4);
      }
      iVar6 = (int)lVar7 + 6;
      iVar2 = *(int *)(iVar4 + 0xa4);
      iVar1 = iVar2 + iVar6 * 0x54;
      fVar3 = *(float *)(iVar4 + 0x10) * *(float *)(iVar1 + 0xc) +
              *(float *)(iVar2 + 0x10 + iVar6 * 0x54) * *(float *)(iVar4 + 0x14) +
              *(float *)(iVar2 + 8 + iVar6 * 0x54) * *(float *)(iVar4 + 0xc) +
              *(float *)(iVar1 + 0x14);
      if (fVar3 < 0.0) {
        fVar3 = -fVar3;
      }
      lua_pushnumber(fVar3);
      return;
    }
  }
  lua_pushnil();
  return;
}
#undef local_4

#endif


/* ---- 0x004a1f30  Lua_AddShadowPlane ---- */
/* Lua opcode: AddShadowPlane */

void Lua_AddShadowPlane(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  void *actor;
  char *sectorName;
  
  iVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      uVar4 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(uVar4);
      if (*(int *)((int)actor + 0xa4) == 0) {
        Actor_CreateExtra(actor);
      }
      sectorName = (char *)lua_getstring(uVar2);
      Actor_AddShadowPlane(actor,*(int *)(*(int *)((int)actor + 0xa4) + 500),sectorName);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a1fd0  Lua_SetActorShadowValid ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetActorShadowValid */

void Lua_SetActorShadowValid(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  void *actor;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  
  iVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      uVar4 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(uVar4);
      if (*(int *)((int)actor + 0xa4) == 0) {
        Actor_CreateExtra(actor);
      }
      lua_getnumber(uVar2);
      lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      Actor_SetShadowValid(actor,*(int *)(*(int *)((int)actor + 0xa4) + 500),(int)lVar5);
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a2070  Lua_KillActorShadows ---- */
/* Lua opcode: KillActorShadows */

void Lua_KillActorShadows(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  void *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if ((iVar2 == 0x52544341) && (iVar1 != 0)) {
      uVar3 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(uVar3);
      Actor_KillShadows(actor);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a20d0  Lua_SetShadowColor ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetShadowColor */

void Lua_SetShadowColor(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int b;
  int g;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  lua_getnumber(uVar3);
  lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  b = (int)lVar4;
  lua_getnumber(uVar2);
  lVar4 = _ftol((double)CONCAT44(unaff_EDI,b));
  g = (int)lVar4;
  lua_getnumber(uVar1);
  lVar4 = _ftol((double)CONCAT44(b,g));
  Shadow_SetColor((int)lVar4,g,b);
  return;
}
#endif


/* ---- 0x004a2130  Lua_NewObjectState ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: NewObjectState */

void Lua_NewObjectState(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  char *zbitmap;
  char *bitmap;
  void *pvVar7;
  undefined4 unaff_ESI;
  int visible;
  undefined4 unaff_EDI;
  longlong lVar8;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  uVar5 = lua_lua2C(5);
  visible = -1;
  iVar6 = lua_isnil(uVar5);
  if (iVar6 == 0) {
    lua_getnumber(uVar5);
    lVar8 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    visible = (int)lVar8;
  }
  zbitmap = (char *)lua_getstring(uVar4);
  bitmap = (char *)lua_getstring(uVar3);
  lua_getnumber(uVar2);
  lVar8 = _ftol((double)CONCAT44(zbitmap,bitmap));
  iVar6 = (int)lVar8;
  lua_getnumber(uVar1);
  lVar8 = _ftol((double)CONCAT44(bitmap,iVar6));
  pvVar7 = ObjectState_Create((int)lVar8,iVar6,bitmap,zbitmap,visible);
  lua_pushusertag(pvVar7,0x54415453);
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a21f0  Lua_FreeObjectState ---- */
/* Lua opcode: FreeObjectState */

void Lua_FreeObjectState(void)

{
  undefined4 uVar1;
  int iVar2;
  void *state;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x54415453) {
      state = (void *)lua_getuserdata(uVar1);
      if (state != (void *)0x0) {
        ObjectState_Free(state);
      }
    }
  }
  return;
}

/* ---- 0x004a2240  Lua_SendObjectToBack ---- */
/* Lua opcode: SendObjectToBack */

void Lua_SendObjectToBack(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  void *pvVar4;
  void *pvVar5;
  
  uVar2 = lua_lua2C(1);
  iVar3 = lua_isuserdata(uVar2);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar2);
    if (iVar3 == 0x54415453) {
      pvVar4 = (void *)lua_getuserdata(uVar2);
      if (pvVar4 != (void *)0x0) {
        iVar3 = *(int *)((int)pvVar4 + 8);
        pvVar5 = Set_GetCurrent();
        iVar1 = *(int *)((int)pvVar5 + 0xac);
        pvVar4 = ObjectState_SendToBack(pvVar4,*(void **)(iVar1 + 0x128 + iVar3 * 300));
        *(void **)(iVar1 + iVar3 * 300 + 0x128) = pvVar4;
      }
    }
  }
  return;
}

/* ---- 0x004a22b0  Lua_SendObjectToFront ---- */
/* Lua opcode: SendObjectToFront */

void Lua_SendObjectToFront(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  void *pvVar4;
  void *pvVar5;
  
  uVar2 = lua_lua2C(1);
  iVar3 = lua_isuserdata(uVar2);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar2);
    if (iVar3 == 0x54415453) {
      pvVar4 = (void *)lua_getuserdata(uVar2);
      if (pvVar4 != (void *)0x0) {
        iVar3 = *(int *)((int)pvVar4 + 8);
        pvVar5 = Set_GetCurrent();
        iVar1 = *(int *)((int)pvVar5 + 0xac);
        pvVar4 = ObjectState_SendToFront(pvVar4,*(void **)(iVar1 + 0x128 + iVar3 * 300));
        *(void **)(iVar1 + iVar3 * 300 + 0x128) = pvVar4;
      }
    }
  }
  return;
}

/* ---- 0x004a2320  Lua_SetObjectType ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetObjectType */

void Lua_SetObjectType(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x54415453) {
      iVar3 = lua_getuserdata(uVar1);
      if (iVar3 != 0) {
        lua_getnumber(uVar2);
        lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        *(int *)(iVar3 + 4) = (int)lVar4;
      }
    }
  }
  return;
}
#endif


/* ---- 0x004a2380  Lua_ActorToClean ---- */
/* Lua opcode: ActorToClean */

void Lua_ActorToClean(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  void *actor;
  
  iVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(iVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(iVar1);
    if ((iVar2 == 0x52544341) && (iVar1 != 0)) {
      uVar3 = lua_getuserdata(iVar1);
      actor = (void *)Actor_FromHandle(uVar3);
      Actor_ToClean(actor);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a23e0  Lua_SetActorCollisionMode ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetActorCollisionMode */

void Lua_SetActorCollisionMode(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  
  iVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      uVar4 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(uVar4);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      lua_getnumber(uVar2);
      lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      *(int *)(*(int *)(iVar1 + 0xa4) + 0x3f0) = (int)lVar5;
      return;
    }
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a2470  Lua_SetActorCollisionScale ---- */
/* Lua opcode: SetActorCollisionScale */

void Lua_SetActorCollisionScale(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  float10 fVar5;
  
  iVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      uVar4 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(uVar4);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      fVar5 = (float10)lua_getnumber(uVar2);
      *(float *)(*(int *)(iVar1 + 0xa4) + 0x3f4) = (float)fVar5;
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a2500  Lua_SetActorOffsetYaw ---- */
/* Lua opcode: SetActorOffsetYaw */

void Lua_SetActorOffsetYaw(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  float10 fVar5;
  
  iVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(iVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(iVar1);
    if ((iVar3 == 0x52544341) && (iVar1 != 0)) {
      uVar4 = lua_getuserdata(iVar1);
      iVar1 = Actor_FromHandle(uVar4);
      if (*(int *)(iVar1 + 0xa4) == 0) {
        Actor_CreateExtra(iVar1);
      }
      fVar5 = (float10)lua_getnumber(uVar2);
      *(float *)(*(int *)(iVar1 + 0xa4) + 0x24) = (float)fVar5;
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a2590  Lua_CacheRect ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_18 */
/* WARNING: Variable defined which should be unmapped: local_1c */
/* WARNING: Variable defined which should be unmapped: local_24 */
/* WARNING: Variable defined which should be unmapped: local_20 */
/* Lua opcode: CacheRect */

void Lua_CacheRect(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  void *pvVar6;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar7;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  iVar5 = lua_isuserdata(uVar1);
  if (iVar5 != 0) {
    iVar5 = lua_tag(uVar1);
    if (iVar5 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar5 = Actor_FromHandle(uVar1);
      if (((*(int *)(iVar5 + 0x68) == 0) || (*(int *)(iVar5 + 0x74) < 1)) ||
         (*(int *)(iVar5 + 0x78) < 1)) {
        lua_pushnil();
        return;
      }
      local_24 = *(uint *)(iVar5 + 0x6c);
      local_20 = *(uint *)(iVar5 + 0x70);
      local_1c = *(uint *)(iVar5 + 0x74);
      local_18 = *(uint *)(iVar5 + 0x78);
      goto LAB_004a268a;
    }
  }
  lua_getnumber(uVar1);
  lVar7 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  local_24 = (uint)lVar7;
  lua_getnumber(uVar2);
  lVar7 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  local_20 = (uint)lVar7;
  lua_getnumber(uVar3);
  lVar7 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  local_1c = (uint)lVar7;
  lua_getnumber(uVar4);
  lVar7 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  local_18 = (uint)lVar7;
LAB_004a268a:
  pvVar6 = CacheRect_Create(local_24,local_20,local_1c,local_18);
  lua_pushusertag(pvVar6,0x504f494e);
  return;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_4

#endif


/* ---- 0x004a26b0  Lua_RestoreCacheRect ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: RestoreCacheRect */

void Lua_RestoreCacheRect(void)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  piVar2 = (int *)lua_getuserdata(uVar1);
  if ((piVar2 != (int *)0x0) && (*piVar2 == 0x11111111)) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    ((code *)CacheRect_Restore)((int)lVar3,unaff_ESI);
  }
  return;
}
#endif


/* ---- 0x004a26f0  Lua_ResReport ---- */
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


/* ---- 0x004a2720  Lua_HardwareAccelerated ---- */
/* Lua opcode: HardwareAccelerated */

void Lua_HardwareAccelerated(void)

{
  if (g_nZBufferEnabled != 0) {
    lua_pushnumber(FBITS(0x3f800000));
    return;
  }
  lua_pushnumber(0);
  return;
}

/* ---- 0x004a2750  Lua_SetActorClipActive ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetActorClipActive */

void Lua_SetActorClipActive(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar1 = lua_getuserdata(uVar1);
  iVar3 = Actor_FromHandle(uVar1);
  if (iVar3 != 0) {
    lua_getnumber(uVar2);
    lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    Actor_SetClipActive(iVar3,(int)lVar4);
  }
  return;
}
#endif


/* ---- 0x004a27b0  Lua_SetActorClipPlane ---- */
/* Lua opcode: SetActorClipPlane */

void Lua_SetActorClipPlane(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  float10 fVar10;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  uVar5 = lua_lua2C(5);
  uVar6 = lua_lua2C(6);
  uVar7 = lua_lua2C(7);
  uVar1 = lua_getuserdata(uVar1);
  iVar8 = Actor_FromHandle(uVar1);
  if (iVar8 != 0) {
    iVar9 = lua_isnumber(uVar2);
    if (iVar9 != 0) {
      iVar9 = lua_isnumber(uVar3);
      if (iVar9 != 0) {
        iVar9 = lua_isnumber(uVar4);
        if (iVar9 != 0) {
          iVar9 = lua_isnumber(uVar5);
          if (iVar9 != 0) {
            iVar9 = lua_isnumber(uVar6);
            if (iVar9 != 0) {
              iVar9 = lua_isnumber(uVar7);
              if (iVar9 != 0) {
                fVar10 = (float10)lua_getnumber(uVar2);
                local_18 = (uint)(float)fVar10;
                fVar10 = (float10)lua_getnumber(uVar3);
                local_14 = (uint)(float)fVar10;
                fVar10 = (float10)lua_getnumber(uVar4);
                local_10 = (uint)(float)fVar10;
                Vec3_Normalize((float *)&local_18);
                fVar10 = (float10)lua_getnumber(uVar5);
                local_c = (uint)(float)fVar10;
                fVar10 = (float10)lua_getnumber(uVar6);
                local_8 = (uint)(float)fVar10;
                fVar10 = (float10)lua_getnumber(uVar7);
                local_4 = (uint)(float)fVar10;
                Actor_SetClipPlane(iVar8,&local_18,&local_c);
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


/* ---- 0x004a2920  Lua_MarkDirtyRect ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: MarkDirtyRect */

void Lua_MarkDirtyRect(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar6;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  iVar5 = lua_isuserdata(uVar1);
  if (iVar5 != 0) {
    iVar5 = lua_tag(uVar1);
    if (iVar5 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar5 = Actor_FromHandle(uVar1);
      if (((*(int *)(iVar5 + 0x68) != 0) && (0 < *(int *)(iVar5 + 0x74))) &&
         (0 < *(int *)(iVar5 + 0x78))) {
        Render_InvalidateRectLastBuffer((int *)(iVar5 + 0x6c),1);
        return;
      }
      lua_pushnil();
      return;
    }
  }
  lua_getnumber(uVar1);
  lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  local_10 = (uint)lVar6;
  lua_getnumber(uVar2);
  lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  local_c = (uint)lVar6;
  lua_getnumber(uVar3);
  lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  local_8 = (uint)lVar6;
  lua_getnumber(uVar4);
  lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: FadeOutChore */

void Lua_FadeOutChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  void *luaObj;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar6;
  longlong lVar7;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  luaObj = (void *)lua_lua2C(2);
  uVar2 = lua_lua2C(3);
  uVar3 = lua_lua2C(4);
  iVar4 = lua_isuserdata(uVar1);
  if ((iVar4 != 0) && (iVar4 = lua_tag(uVar1), iVar4 == 0x52544341)) {
    uVar1 = lua_getuserdata(uVar1);
    iVar4 = Actor_FromHandle(uVar1);
    lua_getnumber(uVar2);
    lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    lua_getnumber(uVar3);
    lVar7 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar5 = lua_isstring(luaObj);
    if ((iVar5 == 0) && (iVar5 = lua_isnumber(luaObj), iVar5 == 0)) {
      return;
    }
    iVar4 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar4 + 0xa0),(void **)&local_4);
    if (iVar4 != 0) {
      Chore_FadeOut(*(void **)local_4,(int)lVar6,(int)lVar7);
    }
  }
  return;
}
#undef local_4

#endif


/* ---- 0x004a2b00  Lua_FadeInChore ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: FadeInChore */

void Lua_FadeInChore(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  void *luaObj;
  undefined4 uVar2;
  int iVar3;
  int chore;
  int iVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  luaObj = (void *)lua_lua2C(2);
  uVar2 = lua_lua2C(3);
  local_4 = lua_lua2C(4);
  iVar3 = lua_isuserdata(uVar1);
  if ((iVar3 != 0) && (iVar3 = lua_tag(uVar1), iVar3 == 0x52544341)) {
    uVar1 = lua_getuserdata(uVar1);
    iVar3 = Actor_FromHandle(uVar1);
    lua_getnumber(uVar2);
    lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    chore = (int)lVar5;
    lua_getnumber(local_4);
    lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar4 = lua_isstring(luaObj);
    if ((iVar4 == 0) && (iVar4 = lua_isnumber(luaObj), iVar4 == 0)) {
      return;
    }
    iVar3 = Lua_ResolveCostumeArg(luaObj,*(void **)(iVar3 + 0xa0),(void **)&local_8);
    if (iVar3 != 0) {
      Cos_InstPlayChore(*(undefined4 *)local_8,chore,0,0);
      Cos_InstUpdateChore(*(undefined4 *)local_8,chore,100);
      Chore_FadeIn(*(void **)local_8,chore,(int)lVar5);
    }
  }
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004a2c10  Lua_IrisDown ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: IrisDown */

void Lua_IrisDown(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int durationMs;
  int y;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  lua_getnumber(uVar3);
  lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  durationMs = (int)lVar4;
  lua_getnumber(uVar2);
  lVar4 = _ftol((double)CONCAT44(unaff_EDI,durationMs));
  y = (int)lVar4;
  lua_getnumber(uVar1);
  lVar4 = _ftol((double)CONCAT44(durationMs,y));
  Render_StartIrisClose((int)lVar4,y,durationMs);
  return;
}
#endif


/* ---- 0x004a2c70  Lua_IrisUp ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: IrisUp */

void Lua_IrisUp(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int durationMs;
  int y;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  lua_getnumber(uVar3);
  lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  durationMs = (int)lVar4;
  lua_getnumber(uVar2);
  lVar4 = _ftol((double)CONCAT44(unaff_EDI,durationMs));
  y = (int)lVar4;
  lua_getnumber(uVar1);
  lVar4 = _ftol((double)CONCAT44(durationMs,y));
  Render_StartIrisOpen((int)lVar4,y,durationMs);
  return;
}
#endif


/* ---- 0x004a2cd0  Lua_IrisComplete ---- */
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


/* ---- 0x004a2d00  Lua_TextFileGetLineCount ---- */
/* WARNING: Variable defined which should be unmapped: local_21c */
/* Lua opcode: TextFileGetLineCount */

void Lua_TextFileGetLineCount(void)

{
  unsigned char _frame[0x230] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined *puVar5;
  #define local_21c (*(uint *)(_frame + (0x230 - 0x21c)))
  #define local_208 (*(uint *)(_frame + (0x230 - 0x208)))
  #define local_204 (*(uint *)(_frame + (0x230 - 0x204)))
  #define local_200 (*(undefined1 (*)[512])(_frame + (0x230 - 0x200)))
  
  uVar2 = lua_lua2C(1);
  local_208 = 0;
  iVar3 = lua_isnil(uVar2);
  if (iVar3 != 0) {
    lua_pushnil();
    return;
  }
  uVar4 = lua_getstring(uVar2);
  puVar5 = fopen(uVar4,IMG_ADDR(0x004ec5bc));
  if (puVar5 != (undefined *)0x0) {
    uVar2 = lua_createtable();
    bVar1 = puVar5[0xc];
    while ((bVar1 & 0x10) == 0) {
      lua_pushobject(uVar2);
      lua_pushnumber((float)(int)local_208);
      iVar3 = ftell(puVar5);
      lua_pushnumber((float)iVar3);
      lua_settable();
      fgets(local_200,0x200,puVar5);
      local_208 = local_208 + 1;
      bVar1 = puVar5[0xc];
    }
    fclose(puVar5);
    lua_pushobject(uVar2);
    lua_pushstring(s_count_004ec384);
    lua_pushnumber((float)(int)local_208);
    lua_settable();
    lua_pushobject(uVar2);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: TextFileGetLine */

void Lua_TextFileGetLine(void)

{
  unsigned char _frame[0x210] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  undefined *puVar6;
  #define local_200 (*(undefined1 (*)[512])(_frame + (0x210 - 0x200)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isnil(uVar1);
  if (iVar3 == 0) {
    iVar3 = lua_isnil(uVar2);
    if (iVar3 == 0) {
      puVar6 = &DAT_004ec5bc;
      uVar4 = lua_getstring(uVar1);
      puVar6 = fopen(uVar4,(uint)puVar6);
      if (puVar6 != (undefined *)0x0) {
        lua_getnumber(uVar2);
        lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        fseek(puVar6,(int)lVar5,0);
        local_200[0] = 0;
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: ScreenShot */

void Lua_ScreenShot(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar6;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isnil(uVar1);
  if (iVar3 == 0) {
    iVar3 = lua_isnumber(uVar1);
    if (iVar3 == 0) goto LAB_004a2f2f;
    lua_getnumber(uVar1);
    lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar3 = (int)lVar6;
  }
  else {
LAB_004a2f2f:
    iVar3 = 0x280;
  }
  iVar4 = lua_isnil(uVar2);
  if (iVar4 == 0) {
    iVar4 = lua_isnumber(uVar2);
    if (iVar4 != 0) {
      lua_getnumber(uVar2);
      lVar6 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      iVar4 = (int)lVar6;
      goto LAB_004a2f5e;
    }
  }
  iVar4 = 0x1e0;
LAB_004a2f5e:
  pvVar5 = Render_CaptureThumbnail(iVar3,iVar4);
  if (pvVar5 != (void *)0x0) {
    lua_pushusertag(pvVar5,0x46554256);
    return;
  }
  lua_pushnil();
  return;
}
#endif


/* ---- 0x004a2f90  Lua_SaveScreen ---- */
/* Lua opcode: SaveScreen */

void Lua_SaveScreen(void)

{
  undefined4 uVar1;
  int iVar2;
  char *filename;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(uVar1);
  if (iVar2 == 0) {
    iVar2 = lua_isstring(uVar1);
    if (iVar2 != 0) {
      filename = (char *)lua_getstring(uVar1);
      Render_SaveScreen(filename);
    }
  }
  return;
}

/* ---- 0x004a2fd0  Lua_GetSaveGameImage ---- */
/* Lua opcode: GetSaveGameImage */

void Lua_GetSaveGameImage(void)

{
  undefined4 uVar1;
  int iVar2;
  char *filename;
  void *pvVar3;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 == 0) {
    lua_pushnil();
    return;
  }
  filename = (char *)lua_getstring(uVar1);
  pvVar3 = SaveGame_LoadThumbnail(filename);
  if (pvVar3 == (void *)0x0) {
    lua_pushnil();
    return;
  }
  Render_RemapPixels(*(ushort **)((int)pvVar3 + 0x5c),
                     *(int *)((int)pvVar3 + 0x10) * *(int *)((int)pvVar3 + 0xc));
  lua_pushusertag(pvVar3,0x46554256);
  return;
}

/* ---- 0x004a3040  Lua_GetImage ---- */
/* Lua opcode: GetImage */

void Lua_GetImage(void)

{
  undefined4 uVar1;
  int iVar2;
  char *filename;
  void *bitmap;
  int iVar3;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    iVar3 = 0;
    iVar2 = 0;
    filename = (char *)lua_getstring(uVar1);
    bitmap = stdBitmap_Load(filename,iVar2,iVar3);
    if (bitmap != (void *)0x0) {
      iVar2 = **(int **)((int)bitmap + 0x78);
      *(undefined4 *)(iVar2 + 0x60) = 0xf81f;
      **(undefined4 **)((int)bitmap + 0x78) = 0;
      stdBitmap_Free(bitmap);
      Render_RemapPixels(*(ushort **)(iVar2 + 0x5c),*(int *)(iVar2 + 0x10) * *(int *)(iVar2 + 0xc));
      Render_RemapPixels((ushort *)(iVar2 + 0x60),1);
      lua_pushusertag(iVar2,0x46554256);
      return;
    }
  }
  lua_pushnil();
  return;
}

/* ---- 0x004a30e0  Lua_FreeImage ---- */
/* Lua opcode: FreeImage */

void Lua_FreeImage(void)

{
  undefined4 uVar1;
  int iVar2;
  void *surface;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isuserdata(uVar1);
  if (iVar2 != 0) {
    iVar2 = lua_tag(uVar1);
    if (iVar2 == 0x46554256) {
      surface = (void *)lua_getuserdata(uVar1);
      Surface_Free(surface);
    }
  }
  return;
}

/* ---- 0x004a3130  Lua_BlastImage ---- */
/* Lua opcode: BlastImage */

void Lua_BlastImage(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  void *src;
  int x;
  void *dst;
  longlong lVar6;
  int *srcRect;
  uint colorKey;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  uVar3 = lua_lua2C(3);
  uVar4 = lua_lua2C(4);
  iVar5 = lua_isnil(uVar4);
  colorKey = (uint)(iVar5 == 0);
  iVar5 = lua_isuserdata(uVar1);
  if (iVar5 != 0) {
    iVar5 = lua_tag(uVar1);
    if (iVar5 == 0x46554256) {
      iVar5 = lua_isnumber(uVar2);
      if (iVar5 != 0) {
        iVar5 = lua_isnumber(uVar3);
        if (iVar5 != 0) {
          src = (void *)lua_getuserdata(uVar1);
          srcRect = (int *)0x0;
          lua_getnumber(uVar3);
          lVar6 = _ftol((double)CONCAT44(colorKey,srcRect));
          iVar5 = (int)lVar6;
          lua_getnumber(uVar2);
          lVar6 = _ftol((double)CONCAT44(srcRect,iVar5));
          x = (int)lVar6;
          dst = (void *)Render_GetBackBuffer();
          Surface_Blit(dst,src,x,iVar5,srcRect,colorKey);
        }
      }
    }
  }
  return;
}

/* ---- 0x004a31f0  Lua_BlastRect ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: BlastRect */

void Lua_BlastRect(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined2 *puVar9;
  undefined2 *puVar10;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  uint uVar11;
  longlong lVar12;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  local_10 = lua_lua2C(3);
  local_c = lua_lua2C(4);
  uVar3 = lua_lua2C(5);
  local_14 = 0xffff;
  local_8 = 0;
  iVar4 = lua_isnumber(uVar1);
  if ((((iVar4 == 0) || (iVar4 = lua_isnumber(uVar2), iVar4 == 0)) ||
      (iVar4 = lua_isnumber(local_10), iVar4 == 0)) || (iVar4 = lua_isnumber(local_c), iVar4 == 0))
  {
    lua_pushnil();
  }
  else {
    lua_getnumber(uVar1);
    lVar12 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    local_4 = (uint)lVar12;
    lua_getnumber(uVar2);
    lVar12 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar4 = (int)lVar12;
    lua_getnumber(local_10);
    lVar12 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar5 = (int)lVar12;
    lua_getnumber(local_c);
    lVar12 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
    iVar6 = (int)lVar12;
    iVar7 = lua_istable(uVar3);
    if (iVar7 != 0) {
      lua_pushobject(uVar3);
      lua_pushstring(s_color_004e8468);
      local_c = lua_gettable();
      iVar7 = lua_isuserdata(local_c);
      if ((iVar7 != 0) && (iVar7 = lua_tag(local_c), iVar7 == 0x524c4f43)) {
        uVar8 = lua_getuserdata(local_c);
        local_14 = ((uVar8 >> 3) << 6 | uVar8 >> 10 & 0x3f) << 5 | uVar8 >> 0x13 & 0x1f;
        Render_RemapPixels((ushort *)&local_14,1);
      }
      lua_pushobject(uVar3);
      lua_pushstring(s_filled_004e8430);
      uVar1 = lua_gettable();
      iVar7 = lua_isnil(uVar1);
      if (iVar7 == 0) {
        local_8 = 1;
      }
    }
    uVar8 = local_4;
    if ((((int)local_4 <= iVar5) && (iVar4 <= iVar6)) &&
       ((-1 < (int)local_4 && (((-1 < iVar4 && (iVar5 < 0x280)) && (iVar6 < 0x1e0)))))) {
      local_4 = Render_GetBackBuffer();
      uVar11 = iVar5 - uVar8;
      local_c = (iVar6 - iVar4) + 1;
      Surface_Lock((void *)local_4);
      puVar9 = (undefined2 *)
               (iVar4 * *(int *)(local_4 + 0x18) + *(int *)(local_4 + 0x5c) + uVar8 * 2);
      if (uVar11 != 0xffffffff) {
        iVar4 = uVar11 + 1;
        puVar10 = puVar9;
        do {
          *puVar10 = (undefined2)local_14;
          puVar10 = puVar10 + 1;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
      if (2 < (int)local_c) {
        for (iVar4 = local_c - 2; iVar4 != 0; iVar4 = iVar4 + -1) {
          puVar9 = (undefined2 *)((int)puVar9 + *(int *)(local_4 + 0x18));
          puVar10 = puVar9;
          uVar8 = uVar11;
          if (local_8 == 0) {
            uVar8 = 1;
          }
          for (; uVar8 != 0; uVar8 = uVar8 - 1) {
            *puVar10 = (undefined2)local_14;
            puVar10 = puVar10 + 1;
          }
          puVar9[uVar11] = (undefined2)local_14;
        }
      }
      if ((1 < (int)local_c) &&
         (puVar9 = (undefined2 *)((int)puVar9 + *(int *)(local_4 + 0x18)), uVar11 != 0xffffffff)) {
        iVar4 = uVar11 + 1;
        do {
          *puVar9 = (undefined2)local_14;
          puVar9 = puVar9 + 1;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
      local_10 = uVar11;
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
/* system.saveGameCallback(); the script answers with SubmitSaveGameData */

void __cdecl Lua_CallSaveGameCallback(void *writeFn)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  bool bVar2;
  undefined4 uVar3;
  void *pvVar4;
  int iVar5;
  void *pvVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  bVar1 = false;
  bVar2 = false;
  g_pfnLuaSaveWrite = writeFn;
  g_nLuaSaveStringCount = 0;
  lua_beginblock();
  uVar3 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar3);
  lua_pushstring(s_saveGameCallback_004ec5c0);
  pvVar4 = (void *)lua_gettable();
  iVar5 = lua_istable(pvVar4);
  if (iVar5 == 0) {
    iVar5 = lua_isfunction(pvVar4);
    if (iVar5 == 0) {
      lua_isnil(pvVar4);
      pvVar6 = writeFn;
    }
    else {
      bVar2 = false;
      bVar1 = true;
      pvVar6 = pvVar4;
    }
  }
  else {
    lua_pushobject();
    lua_pushstring(s_saveGameCallback_004ec5c0);
    pvVar6 = (void *)lua_gettable();
    iVar5 = lua_isfunction(pvVar6);
    if (iVar5 != 0) {
      bVar1 = true;
      bVar2 = true;
    }
  }
  if (bVar1) {
    if (bVar2) {
      lua_pushobject(pvVar4);
    }
    lua_callfunction(pvVar6);
  }
  if (g_nLuaSaveStringCount == 0) {
    (*(code *)writeFn)(&g_nLuaSaveStringCount,4);
  }
  lua_endblock();
  return;
}
#undef local_4


/* ---- 0x004a35d0  Lua_SubmitSaveGameData ---- */
/* Lua opcode: SubmitSaveGameData */

void Lua_SubmitSaveGameData(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  uint uVar7;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define uStack_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_10 = 0;
  uVar2 = lua_lua2C(1);
  g_nLuaSaveStringCount = 0;
  do {
    lua_pushobject(uVar2);
    local_4 = (uint)(float)(int)local_10;
    local_10 = local_10 + 1;
    lua_pushnumber(local_4);
    uVar3 = lua_gettable();
    iVar4 = lua_isnil(uVar3);
    if (iVar4 != 0) {
      if (g_nLuaSaveStringCount != 0) {
        (*(code *)g_pfnLuaSaveWrite)(&g_nLuaSaveStringCount,4);
        local_10 = 0;
        while( true ) {
          lua_pushobject(uVar2);
          local_4 = (uint)(float)(int)local_10;
          local_10 = local_10 + 1;
          lua_pushnumber(local_4);
          uVar3 = lua_gettable();
          iVar4 = lua_isnil(uVar3);
          if (iVar4 != 0) break;
          pcVar6 = (char *)lua_getstring(uVar3);
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
    iVar4 = lua_isstring(uVar3);
    if (iVar4 == 0) {
      return;
    }
    pcVar5 = (char *)lua_getstring(uVar3);
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


/* ---- 0x004a3720  Lua_GetSaveGameData ---- */
/* Lua opcode: GetSaveGameData */

void Lua_GetSaveGameData(void)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  char *name;
  void *pvVar3;
  char *mode;
  #define local_90 (*(uint *)(_frame + (0xa0 - 0x90)))
  #define local_8c (*(uint *)(_frame + (0xa0 - 0x8c)))
  #define local_88 (*(uint *)(_frame + (0xa0 - 0x88)))
  #define local_84 (*(uint *)(_frame + (0xa0 - 0x84)))
  #define local_80 (*(undefined1 (*)[128])(_frame + (0xa0 - 0x80)))
  
  local_90 = 0;
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isstring(uVar1);
  if (iVar2 != 0) {
    mode = &DAT_004ddb18;
    name = (char *)lua_getstring(uVar1);
    pvVar3 = SaveFile_Open(name,mode);
    if (pvVar3 != (void *)0x0) {
      uVar1 = lua_createtable();
      gzread(pvVar3,&local_8c,4);
      for (; 0 < (int)local_8c; local_8c = local_8c + (-4 - local_88)) {
        gzread(pvVar3,&local_88,4);
        gzread(pvVar3,local_80,local_88);
        lua_pushobject(uVar1);
        local_84 = (uint)(float)(int)local_90;
        local_90 = local_90 + 1;
        lua_pushnumber(local_84);
        lua_pushstring(local_80);
        lua_settable();
      }
      lua_pushobject(uVar1);
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


/* ---- 0x004a3830  Lua_GetTextSpeed ---- */
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


/* ---- 0x004a3850  Lua_SetTextSpeed ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: SetTextSpeed */

void Lua_SetTextSpeed(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnumber(uVar1);
  if (iVar2 != 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    Text_SetSpeed((int)lVar3);
  }
  return;
}
#endif


/* ---- 0x004a3890  Lua_FindFileOnAnyCD ---- */
/* Lua opcode: FindFileOnAnyCD */

void Lua_FindFileOnAnyCD(void)

{
  unsigned char _frame[0x190] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *a1;
  char cVar1;
  bool bVar2;
  undefined4 uVar3;
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
  
  uVar3 = lua_lua2C(1);
  bVar2 = false;
  iVar4 = lua_isstring(uVar3);
  if ((iVar4 != 0) && (pcVar5 = (char *)lua_getstring(uVar3), pcVar5 != (char *)0x0)) {
    iVar4 = GetLogicalDriveStringsA(0,0);
    if (iVar4 != 0) {
      a2 = (char *)(*g_pSvcLua->pAlloc)
                             (iVar4 + 1,s_C__grimsrc_libs_grimlib_Scripts__004ec38c,0x2728);
      GetLogicalDriveStringsA(iVar4,(int)a2);
      a1 = a2;
      while (((a1 != (char *)0x0 && (*a1 != '\0')) && (!bVar2))) {
        iVar4 = GetDriveTypeA((int)a1);
        if (iVar4 == 5) {
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
          iVar4 = -1;
          pcVar8 = acStack_174;
          do {
            pcVar9 = pcVar8;
            if (iVar4 == 0) break;
            iVar4 = iVar4 + -1;
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
          iVar4 = FindFirstFileA((int)acStack_174,(int)auStack_140);
          if (iVar4 != -1) {
            bVar2 = true;
            FindClose(iVar4);
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
      lua_pushnumber(FBITS(0x3f800000));
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


/* ---- 0x004a3a10  Lua_ActorPuckOrient ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: ActorPuckOrient */

void Lua_ActorPuckOrient(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar5;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      uVar1 = lua_getuserdata(uVar1);
      iVar3 = Actor_FromHandle(uVar1);
      iVar4 = lua_isnil(uVar2);
      if (iVar4 == 0) {
        lua_getnumber(uVar2);
        lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        if ((int)lVar5 != 0) {
          *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x10;
          return;
        }
      }
      *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) & 0xffffffef;
    }
  }
  return;
}
#endif


/* ---- 0x004a3aa0  Lua_GetTickCount ---- */
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


/* ---- 0x004a3ae0  Lua_SetActorInvClipNode ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Lua opcode: SetActorInvClipNode */

void Lua_SetActorInvClipNode(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  
  uVar1 = lua_lua2C(1);
  uVar2 = lua_lua2C(2);
  iVar3 = lua_isuserdata(uVar1);
  if (iVar3 != 0) {
    iVar3 = lua_tag(uVar1);
    if (iVar3 == 0x52544341) {
      iVar3 = lua_isnil(uVar2);
      if (iVar3 == 0) {
        lua_getnumber(uVar2);
        lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
        uVar2 = (undefined4)lVar4;
      }
      else {
        uVar2 = 0xffffffff;
      }
      uVar1 = lua_getuserdata(uVar1);
      iVar3 = Actor_FromHandle(uVar1);
      if (*(int *)(iVar3 + 0xa4) == 0) {
        Actor_CreateExtra(iVar3);
      }
      *(undefined4 *)(*(int *)(iVar3 + 0xa4) + 0x420) = uVar2;
    }
  }
  return;
}
#endif


/* ---- 0x004a3b80  Lua_SetWalkSystemFadeTime ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: This function may have set the stack pointer */
/* Lua opcode: SetWalkSystemFadeTime */

void Lua_SetWalkSystemFadeTime(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_ESI;
  longlong lVar3;
  undefined4 unaff_retaddr;
  
  uVar1 = lua_lua2C(1);
  iVar2 = lua_isnil(uVar1);
  if (iVar2 == 0) {
    lua_getnumber(uVar1);
    lVar3 = _ftol((double)CONCAT44(unaff_retaddr,unaff_ESI));
    Walker_SetFadeTime((int)lVar3);
  }
  return;
}
#endif


/* ---- 0x004be180  Lua_LightMgrStartup ---- */
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

/* ---- 0x004be260  Lua_LightMgrSetChange ---- */
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

/* ---- 0x004be2a0  Lua_LightMgrShutdown ---- */
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
