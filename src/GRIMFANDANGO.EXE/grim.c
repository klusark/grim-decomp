/* GRIMFANDANGO.EXE :: grim.c
 * functions 0x00401140 .. 0x00403520 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00401140  Grim_FindDataOnDrives ---- */
/* grimdemo.c: scans CD-ROM drives (and network drives when g_devMode) for <drive>\<subdir>; shows
   the _engn006/_engn007 'could not find data' message and returns 0 if none has it. */

int __cdecl Grim_FindDataOnDrives(char *subdir)

{
  unsigned char _frame[0x190] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  bool bVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  void *pvVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  #define acStack_174 (*(char (*)[52])(_frame + (0x190 - 0x174)))
  #define auStack_140 (*(undefined1 (*)[320])(_frame + (0x190 - 0x140)))
  
  bVar2 = false;
  iVar3 = GetLogicalDriveStringsA(0,0);
  if (iVar3 != 0) {
    pcVar4 = (char *)(*g_pStd_HS->pAlloc)
                               (iVar3 + 1,s_C__grimsrc_tools_grimdemo_grimde_004dd50c,0x161);
    GetLogicalDriveStringsA(iVar3,(int)pcVar4);
    pcVar5 = pcVar4;
    while (((pcVar5 != (char *)0x0 && (*pcVar5 != '\0')) && (!bVar2))) {
      iVar3 = GetDriveTypeA((int)pcVar5);
      if ((iVar3 == 5) || ((g_nDeveloper != 0 && (iVar3 == 4)))) {
        uVar7 = 0xffffffff;
        pcVar9 = pcVar5;
        do {
          pcVar11 = pcVar9;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar11 = pcVar9 + 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar11;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        pcVar9 = pcVar11 + -uVar7;
        pcVar11 = acStack_174;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
          pcVar9 = pcVar9 + 4;
          pcVar11 = pcVar11 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pcVar11 = *pcVar9;
          pcVar9 = pcVar9 + 1;
          pcVar11 = pcVar11 + 1;
        }
        uVar7 = 0xffffffff;
        pcVar9 = subdir;
        do {
          pcVar11 = pcVar9;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar11 = pcVar9 + 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar11;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        iVar3 = -1;
        pcVar9 = acStack_174;
        do {
          pcVar10 = pcVar9;
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          pcVar10 = pcVar9 + 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar10;
        } while (cVar1 != '\0');
        pcVar9 = pcVar11 + -uVar7;
        pcVar11 = pcVar10 + -1;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
          pcVar9 = pcVar9 + 4;
          pcVar11 = pcVar11 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pcVar11 = *pcVar9;
          pcVar9 = pcVar9 + 1;
          pcVar11 = pcVar11 + 1;
        }
        iVar3 = FindFirstFileA((int)acStack_174,(int)auStack_140);
        if (iVar3 != -1) {
          bVar2 = true;
          FindClose(iVar3);
        }
      }
      uVar7 = 0xffffffff;
      pcVar9 = pcVar5;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      pcVar5 = pcVar5 + ~uVar7;
    }
    (*g_pStd_HS->pFree)(pcVar4);
  }
  if (!bVar2) {
    iVar3 = 0;
    pcVar5 = PolyglotGetString(s__engn007_Grim_Fandango_could_not_004dd4dc);
    pcVar4 = PolyglotGetString(s__engn006_Please_make_sure_that_t_004dd47c);
    pvVar6 = Win_GetMainHwnd();
    Grim_FatalMessageBox((int)pvVar6,(int)pcVar4,(int)pcVar5,iVar3);
    return 0;
  }
  return 1;
}
#undef acStack_174
#undef auStack_140


/* ---- 0x004012b0  Main_Startup ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* grimdemo.c: whole-engine startup: service tables, registry/config, window + 256-colour check,
   display enumeration, resource system, Lua engine lib registration, iMUSE. Original name
   Main_Startup (the remaster's GrimFandango (Linux): the same start-up sequence (developer registry
   key compared with "TRUE" and "pl", rdStartup / rdOpen, the window message hook,
   stdDisplay_Startup, the shutdown / palette / page-flip / debug-toggle callbacks,
   grimlib_FindResources)); was Grim_Init. */

uint __cdecl Main_Startup(char *param_1)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  void *pvVar4;
  undefined *puVar5;
  int iVar6;
  undefined4 *puVar7;
  #define local_80 (*(uint *)(_frame + (0x90 - 0x80)))
  #define local_7c (*(uint *)(_frame + (0x90 - 0x7c)))
  #define local_78 (*(undefined2 *)(_frame + (0x90 - 0x78)))
  #define local_76 (*(undefined1 *)(_frame + (0x90 - 0x76)))
  #define local_75 (*(undefined4 (*)[13])(_frame + (0x90 - 0x75)))
  #define acStack_40 (*(char (*)[64])(_frame + (0x90 - 0x40)))
  
  local_80 = UINT_004dd668;
  local_7c = UINT_004dd66c;
  local_76 = DAT_004dd672;
  local_78 = DAT_004dd670;
  puVar7 = local_75;
  for (iVar6 = 0xd; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  *(undefined1 *)puVar7 = 0;
  HostServicesInitialize((GrimServices *)&g_aHs);
  iVar6 = Grim_ParseCommandLine(param_1);
  if (iVar6 == 0) {
    return 0;
  }
  stdInitServices(&g_aHs);
  _DAT_008dddb4 = UINT_008dddac;
  stdStartup((GrimServices *)&g_aHs);
  PolyglotInitialize(&g_aHs,&g_aPolyglotServices);
  (*(code *)UINT_008ddd88)();
  PolyglotConfigure(s_grim_tab_004dd238);
  Grim_OpenRegistry();
  Grim_DecodeRegKeyName((char *)&local_80);
  wuRegistry_GetStr((char *)&local_80,acStack_40,0x40,(char *)0x0);
  iVar6 = _stricmp(acStack_40,&DAT_004dd660);
  if (iVar6 == 0) {
    g_nDeveloper = 1;
  }
  iVar6 = _stricmp(acStack_40,&DAT_004dd65c);
  if (iVar6 == 0) {
    g_nDeveloper = 1;
  }
  if (g_nDeveloper == 0) {
    iVar6 = Grim_FindDataOnDrives(s_GrimData_004dd650);
    if (iVar6 == 0) {
      return 0;
    }
  }
  rdStartup((GrimServices *)&g_aHs);
  iVar6 = rdOpen(0);
  if (iVar6 == 0) {
    return 0;
  }
  Win_AddMessageHook(Win_WndProc);
  Win_AddMessageHook(Win_IsSysCommandBlocked);
  iVar6 = GetDC(0);
  iVar1 = GetDeviceCaps(iVar6,0xc);
  ReleaseDC(0,iVar6);
  if (iVar1 < 8) {
    iVar6 = 0;
    pcVar2 = PolyglotGetString(s__engn001_Grim_Fandango_004dd638);
    pcVar3 = PolyglotGetString(s__engn002_System_must_be_in_256_c_004dd5f8);
    pvVar4 = Win_GetMainHwnd();
    Grim_FatalMessageBox((int)pvVar4,(int)pcVar3,(int)pcVar2,iVar6);
    return 0;
  }
  iVar6 = stdDisplay_Startup();
  if (iVar6 == 0) {
    return 0;
  }
  Grim_EnumDisplayModes();
  if ((g_nDeveloper != 0) && (g_bWindowedMode != 0)) {
    Reg_SetInt(s_ExperimentalDisplay_004dd5e4,1);
  }
  puVar5 = Display_InitFromConfig();
  if (puVar5 == (undefined *)0x0) {
    return 0;
  }
  puVar5 = grimlib_GameInitialize((GrimServices *)&g_aHs,(undefined **)&g_aMs);
  if (puVar5 != (undefined *)0x0) {
    return 0;
  }
  iVar6 = (*(code *)UINT_008dde28)();
  if (iVar6 != 0) {
    iVar6 = 0;
    pcVar2 = PolyglotGetString(s__engn005_Grim_Fandango_could_not_004dd5a8);
    pcVar3 = PolyglotGetString(s__engn004_Please_make_sure_you_ar_004dd534);
    pvVar4 = Win_GetMainHwnd();
    Grim_FatalMessageBox((int)pvVar4,(int)pcVar3,(int)pcVar2,iVar6);
    return 0;
  }
  lua_openlib((int *)&PTR_s_Is3DHardwareEnabled_004dd350,UINT_004dd380);
  grimlib_SetShutdownCallback(grimdemo_PleaseShutdown);
  grimlib_SetPaletteCallback(grimdemo_SetPalette);
  grimlib_SetPageFlipCallback(stdDisplay_Update);
  grimlib_SetDebugToggleCallback(grimdemo_EnableDebugging);
  grimlib_FindResources();
  Grim_ShowSplash();
  grimdemo_EnableDebugging(1);
  iVar6 = grimlib_FindSystemFiles();
  if (iVar6 != 0) {
    iVar6 = 0;
    pcVar2 = PolyglotGetString(s__engn007_Grim_Fandango_could_not_004dd4dc);
    pcVar3 = PolyglotGetString(s__engn006_Please_make_sure_that_t_004dd47c);
    pvVar4 = Win_GetMainHwnd();
    Grim_FatalMessageBox((int)pvVar4,(int)pcVar3,(int)pcVar2,iVar6);
    return 0;
  }
  iVar6 = grimlib_Open(UINT_004f5a10,-(uint)(UINT_004f5a14 != 0) & 0x4f59b0);
  if (iVar6 != 0) {
    return 0;
  }
  if (UINT_004f5a44 != 0) {
    ChoreFace_Toggle(1);
  }
  pvVar4 = Win_GetMainHwnd();
  SetActiveWindow((int)pvVar4);
  _g_dwGrimlib_MinimizeWhenInactive = 1;
  return 1;
}
#undef acStack_40
#undef local_75
#undef local_76
#undef local_78
#undef local_7c
#undef local_80


/* ---- 0x00401640  Grim_DecodeRegKeyName ---- */
/* De-obfuscates the 10-character registry key name in place by adding per-character offsets */

void __cdecl Grim_DecodeRegKeyName(char *s)

{
  *s = *s + -8;
  s[1] = s[1] + -3;
  s[2] = s[2] + '\a';
  s[3] = s[3] + -1;
  s[4] = s[4] + '\x05';
  s[5] = s[5] + -3;
  s[6] = s[6] + '\x04';
  s[7] = s[7] + -1;
  s[8] = s[8] + '\x05';
  s[9] = s[9] + -2;
  return;
}

/* ---- 0x004018b0  Grim_FatalMessageBox ---- */
/* MessageBoxA wrapper that first tears down the display so the box is visible */

int __cdecl Grim_FatalMessageBox(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  UINT_004e814c = 0;
  iVar1 = MessageBoxA(param_1,param_2,param_3,param_4);
  Grim_ShutdownDisplay();
  CloseWindow(param_1);
  stdControl_ShowMouseCursor(1);
  UINT_004e814c = 1;
  return iVar1;
}

/* ---- 0x00401900  Grim_ShutdownDisplay ---- */
void __cdecl Grim_ShutdownDisplay(void)

{
  if (g_nDisplayDeviceOpen != 0) {
    grimlib_UnsetDisplay();
    if (g_pStd3D_CurDevice == (void *)0x0) {
      stdDisplay_VBufferFree((void *)UINT_004f5a34);
    }
    else {
      Display_Shutdown3D();
    }
    UINT_004f5a34 = 0;
    stdDisplay_ClearMode();
    stdDisplay_Close();
    Reg_SetInt(s_ExperimentalDisplay_004dd5e4,0);
  }
  return;
}

/* ---- 0x00401950  Main_Shutdown ---- */
/* grimdemo.c: frees the display-mode tables, closes resources, Lua, window, iMUSE, memory services
   Original name Main_Shutdown (the remaster's GrimFandango (Linux): the same shutdown sequence:
   free the display-mode lists, debug shutdown, grimlib_Close, the two service shutdowns, rdClose,
   rdShutdown, display close, mouse cursor, registry, polyglot shutdowns, std shutdown); was
   Grim_Shutdown. */

void __cdecl Main_Shutdown(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if (UINT_004f44e0 != 0) {
    Res_FClose(UINT_004f44e0);
    UINT_004f44e0 = 0;
    UINT_004f5a18 = 0;
  }
  uVar3 = 0;
  if (g_dwStdDisplay_numDevices != 0) {
    iVar2 = 0;
    do {
      iVar1 = *(int *)((int)g_pDisplayModes + iVar2 + 0xc);
      if (iVar1 != 0) {
        (*g_pStd_HS->pFree)(iVar1);
      }
      iVar1 = *(int *)((int)g_pDisplayModes + iVar2 + 4);
      if (iVar1 != 0) {
        (*g_pStd_HS->pFree)(iVar1);
      }
      uVar3 = uVar3 + 1;
      iVar2 = iVar2 + 0x10;
    } while (uVar3 < g_dwStdDisplay_numDevices);
  }
  if (g_pDisplayModes != (void *)0x0) {
    (*g_pStd_HS->pFree)(g_pDisplayModes);
  }
  grimDebug_Shutdown();
  grimlib_Close();
  (*(code *)UINT_008dde2c)();
  (*(code *)UINT_008dde24)();
  rdClose();
  rdShutdown();
  Grim_ShutdownDisplay();
  stdDisplay_Shutdown();
  if (g_bWindowedMode == 0) {
    stdControl_ShowMouseCursor(1);
  }
  wuRegistry_Shutdown();
  if (UINT_008ddd8c != 0) {
    (*(code *)UINT_008ddd8c)();
  }
  if (UINT_008ddd84 != 0) {
    (*(code *)UINT_008ddd84)();
  }
  stdShutdown();
  grimdemo_EnableDebugging(0);
  return;
}

/* ---- 0x00401a50  Grim_EnumDisplayModes ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Builds g_displayModes: per display device, copies the 0x54-byte mode records and (when the device
   has 3D hardware) the 0x22c-byte 3D driver records */

void __cdecl Grim_EnumDisplayModes(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  undefined4 *puVar7;
  uint *puVar8;
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x50 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x50 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x50 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x50 - 0x4)))
  
  local_30 = 5;
  local_28 = 5;
  local_20 = 5;
  puVar6 = &UINT_004f44e8;
  for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  puVar6 = &UINT_004f4d38;
  for (iVar2 = 0x13; uVar5 = g_dwStdDisplay_numDevices, iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  iVar4 = 0;
  local_14 = 2;
  _DAT_004f450c = 2;
  local_38 = 1;
  local_34 = 0x10;
  local_2c = 6;
  local_24 = 0xb;
  local_1c = 0;
  local_18 = 3;
  local_10 = 3;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  puVar6 = &local_38;
  puVar8 = &UINT_004f4d54;
  for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar8 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  UINT_004f44e8 = 1;
  UINT_004f44ec = 1;
  _DAT_004f44f0 = 1;
  _DAT_004f4d40 = 0x280;
  _DAT_004f4d44 = 0x1e0;
  g_pDisplayModes =
       (void *)(*g_pStd_HS->pAlloc)(uVar5 << 4,s_C__grimsrc_tools_grimdemo_grimde_004dd50c,0x313);
  puVar7 = g_pDisplayModes;
  for (iVar2 = (g_dwStdDisplay_numDevices & 0xfffffff) << 2; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  uVar5 = 0;
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)puVar7 = 0;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  if (g_dwStdDisplay_numDevices != 0) {
    do {
      Display_SelectDevice(uVar5);
      *(uint *)((int)g_pDisplayModes + iVar4) = g_dwVideoModeCount;
      uVar1 = (*g_pStd_HS->pAlloc)
                        (g_dwVideoModeCount * 0x54,s_C__grimsrc_tools_grimdemo_grimde_004dd50c,0x31e
                        );
      *(undefined4 *)((int)g_pDisplayModes + iVar4 + 4) = uVar1;
      puVar6 = &UINT_00901760;
      puVar8 = *(uint **)((int)g_pDisplayModes + iVar4 + 4);
      for (uVar3 = g_dwVideoModeCount * 0x15 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar8 = puVar8 + 1;
      }
      for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(char *)puVar8 = (char)*puVar6;
        puVar6 = (uint *)((int)puVar6 + 1);
        puVar8 = (uint *)((int)puVar8 + 1);
      }
      *(undefined4 *)((int)g_pDisplayModes + iVar4 + 8) = 0;
      *(undefined4 *)((int)g_pDisplayModes + iVar4 + 0xc) = 0;
      iVar2 = D3D_Enumerate();
      if (iVar2 != 0) {
        *(uint *)((int)g_pDisplayModes + iVar4 + 8) = g_dwD3dDriverCount;
        if (g_dwD3dDriverCount != 0) {
          uVar1 = (*g_pStd_HS->pAlloc)
                            (g_dwD3dDriverCount * 0x22c,s_C__grimsrc_tools_grimdemo_grimde_004dd50c,
                             0x32a);
          *(undefined4 *)((int)g_pDisplayModes + iVar4 + 0xc) = uVar1;
        }
        puVar6 = &UINT_00900b40;
        puVar8 = *(uint **)((int)g_pDisplayModes + iVar4 + 0xc);
        for (uVar3 = g_dwD3dDriverCount * 0x8b & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
          *puVar8 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar8 = puVar8 + 1;
        }
        for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
          *(char *)puVar8 = (char)*puVar6;
          puVar6 = (uint *)((int)puVar6 + 1);
          puVar8 = (uint *)((int)puVar8 + 1);
        }
        D3D_Release();
      }
      stdDisplay_Close();
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 0x10;
    } while (uVar5 < g_dwStdDisplay_numDevices);
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
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00402050  grimdemo_PleaseShutdown ---- */
/* Sets g_nQuitApp. Original name grimdemo_PleaseShutdown (the remaster's GrimFandango (Linux): sets
   bQuitApp); was Grim_RequestQuit. */

void __cdecl grimdemo_PleaseShutdown(void)

{
  g_nQuitApp = 1;
  return;
}

/* ---- 0x00402060  grimdemo_SetPalette ---- */
/* Original name grimdemo_SetPalette (the remaster's GrimFandango (Linux): the palette callback of
   Main_Startup, same body (two display palette calls, std3D_SetCurrentPalette with a device)); was
   Grim_OnDisplayModeChange. */

uint __cdecl grimdemo_SetPalette(void *param_1,int param_2)

{
  stdDisplay_SetPalette(param_1);
  stdDisplay_SetMasterPalette(param_1);
  if (g_pStd3D_CurDevice != (void *)0x0) {
    std3D_SetCurrentPalette(param_1,param_2);
  }
  return 1;
}

/* ---- 0x00402c80  Grim_ParseCommandLine ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* grimdemo.c: strtok loop over the command line. Options set g_bAlwaysLog, g_bDevMode,
   g_bWindowedStart etc., a bad option shows the 'GRIME: Grim Fandango Executable Usage' box. */

int __cdecl Grim_ParseCommandLine(char *cmdline)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  void *pvVar5;
  char *pcVar6;
  
  iVar1 = strtok(cmdline,&DAT_004dd918);
  if (iVar1 == 0) {
    return 1;
  }
  do {
    iVar2 = _stricmp(iVar1,&DAT_004dd914);
    if ((iVar2 == 0) || (iVar2 = _stricmp(iVar1,&DAT_004dd910), iVar2 == 0)) {
      uVar3 = strtok(0,&DAT_004dd918);
      strncpy(s_grim_tab_004dd238,uVar3,0x103);
      DAT_004dd33b = 0;
LAB_00402f60:
      iVar1 = strtok(0,&DAT_004dd918);
    }
    else {
      iVar2 = _stricmp(iVar1,&DAT_004dd90c);
      if ((iVar2 == 0) || (iVar2 = _stricmp(iVar1,&DAT_004dd908), iVar2 == 0)) {
        uVar4 = strtok(0,&DAT_004dd918);
        _DAT_004dd34c = atoi(uVar4);
        grimlib_SetCacheMax(_DAT_004dd34c);
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(iVar1,&DAT_004dd904);
      if ((iVar2 == 0) || (iVar2 = _stricmp(iVar1,&DAT_004dd900), iVar2 == 0)) {
        UINT_004f5a44 = 1;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(iVar1,&DAT_004dd8fc);
      if ((iVar2 == 0) || (iVar2 = _stricmp(iVar1,&DAT_004dd8f8), iVar2 == 0)) {
        UINT_004f5a18 = 1;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(iVar1,&DAT_004dd8f4);
      if ((iVar2 == 0) || (iVar2 = _stricmp(iVar1,&DAT_004dd8f0), iVar2 == 0)) {
        UINT_004f5a28 = 1;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(iVar1,&DAT_004dd8ec);
      if ((iVar2 == 0) || (iVar2 = _stricmp(iVar1,&DAT_004dd8e8), iVar2 == 0)) {
        UINT_004f5a1c = 1;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(iVar1,&DAT_004dd8e4);
      if ((iVar2 == 0) || (iVar2 = _stricmp(iVar1,&DAT_004dd8e0), iVar2 == 0)) {
        g_bWindowedMode = 1;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(iVar1,&DAT_004dd8dc);
      if ((iVar2 == 0) || (iVar2 = _stricmp(iVar1,&DAT_004dd8d8), iVar2 == 0)) {
        UINT_004f5a10 = 1;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(iVar1,&DAT_004dd8d4);
      if ((iVar2 == 0) || (iVar2 = _stricmp(iVar1,&DAT_004dd8d0), iVar2 == 0)) {
        UINT_004f5a14 = 1;
        uVar3 = strtok(0,&DAT_004dd918);
        strncpy(&DAT_004f59b0,uVar3,0x4f);
        DAT_004f59ff = 0;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(iVar1,&DAT_004dd8cc);
      if ((iVar2 == 0) || (iVar2 = _stricmp(iVar1,&DAT_004dd8c8), iVar2 == 0)) {
        uVar3 = strtok(0,&DAT_004dd918);
        grimlib_AddResourcePath(uVar3);
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(iVar1,&DAT_004dd8c4);
      if ((iVar2 != 0) && (iVar2 = _stricmp(iVar1,&DAT_004dd8c0), iVar2 != 0)) {
        iVar2 = _stricmp(iVar1,&DAT_004dd8bc);
        if ((iVar2 == 0) || (iVar1 = _stricmp(iVar1,&DAT_004dd8b8), iVar1 == 0)) {
          cmdline = s_Usage_004dd8b0;
        }
        iVar1 = 0;
        pcVar6 = s_GRIME__Grim_Fandango_Executable_U_004dd048;
        pvVar5 = Win_GetMainHwnd();
        Grim_FatalMessageBox((int)pvVar5,(int)pcVar6,(int)cmdline,iVar1);
        return 0;
      }
      iVar1 = strtok(0,&DAT_004dd918);
      UINT_004e806c = 0;
    }
    if (iVar1 == 0) {
      return 1;
    }
  } while( true );
}

/* ---- 0x004034b0  Grim_OpenRegistry ---- */
/* Opens HKLM\SOFTWARE\LucasArts Entertainment Company LLC\... and seeds GrimDataDir with the
   current directory when it is missing */

void __cdecl Grim_OpenRegistry(void)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_104 (*(char (*)[260])(_frame + (0x120 - 0x104)))
  
  Reg_Open((void *)0x80000002,((unsigned)(uintptr_t)&DAT_004dd958),&DAT_004dd998);
  iVar1 = wuRegistry_GetStr(s_GrimDataDir_004dd94c,local_104,0x104,&DAT_004f5a98);
  if (iVar1 == 0) {
    iVar1 = GetCurrentDirectoryA(0x104,(int)local_104);
    if (iVar1 != 0) {
      wuRegistry_SaveStr(s_GrimDataDir_004dd94c,local_104);
    }
  }
  return;
}
#undef local_104


/* ---- 0x00403520  Grim_ShowSplash ---- */
/* Loads splash.bm, converts each row to the screen format and flips it onto the primary surface
   twice */

void __cdecl Grim_ShowSplash(void)

{
  void *src;
  void *bitmap;
  int iVar1;
  
  bitmap = stdBitmap_Load(s_splash_bm_004dd99c,0,0);
  if ((bitmap != (void *)0x0) &&
     (src = (void *)**(undefined4 **)((int)bitmap + 0x78), src != (void *)0x0)) {
    iVar1 = 0;
    if (0 < *(int *)((int)src + 0x10)) {
      do {
        sputRender_ColorCorrect
                  ((ushort *)(iVar1 * *(int *)((int)src + 0x18) + *(int *)((int)src + 0x5c)),
                   *(uint *)((int)src + 0xc));
        iVar1 = iVar1 + 1;
      } while (iVar1 < *(int *)((int)src + 0x10));
    }
    Surface_Blit(&g_dwStdDisplay_frontBuffer,src,0,0,(int *)0x0,0);
    stdDisplay_Update();
    Surface_Blit(&g_dwStdDisplay_frontBuffer,src,0,0,(int *)0x0,0);
    stdBitmap_Free(bitmap);
  }
  return;
}
