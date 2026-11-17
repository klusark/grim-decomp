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
  void *hwnd;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
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
        pcVar8 = subdir;
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
      pcVar8 = pcVar5;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar1 != '\0');
      pcVar5 = pcVar5 + ~uVar6;
    }
    (*g_pStd_HS->pFree)(pcVar4);
  }
  if (!bVar2) {
    iVar3 = 0;
    pcVar5 = PolyglotGetString(s__engn007_Grim_Fandango_could_not_004dd4dc);
    pcVar4 = PolyglotGetString(s__engn006_Please_make_sure_that_t_004dd47c);
    hwnd = Win_GetMainHwnd();
    Grim_FatalMessageBox((int)hwnd,(int)pcVar4,(int)pcVar5,iVar3);
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

uint __cdecl Main_Startup(char *cmdline)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined uVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  void *pvVar5;
  undefined *puVar6;
  undefined3 extraout_var;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  #define local_80 (*(uint *)(_frame + (0x90 - 0x80)))
  #define local_7c (*(uint *)(_frame + (0x90 - 0x7c)))
  #define local_78 (*(undefined2 *)(_frame + (0x90 - 0x78)))
  #define local_76 (*(undefined1 *)(_frame + (0x90 - 0x76)))
  #define local_75 (*(undefined4 (*)[13])(_frame + (0x90 - 0x75)))
  #define abStack_40 (*(byte (*)[64])(_frame + (0x90 - 0x40)))
  
  local_80 = UINT_004dd668;
  local_7c = UINT_004dd66c;
  local_76 = DAT_004dd672;
  local_78 = DAT_004dd670;
  puVar9 = local_75;
  for (iVar8 = 0xd; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  *(undefined1 *)puVar9 = 0;
  HostServicesInitialize(&g_aHs);
  iVar8 = Grim_ParseCommandLine(cmdline);
  if (iVar8 == 0) {
    return 0;
  }
  stdInitServices(&g_aHs);
  g_aHs.pDebug = g_aHs.pWarning;
  stdStartup(&g_aHs);
  PolyglotInitialize(&g_aHs,&g_aPolyglotServices.pfnInitialize);
  (*g_aPolyglotServices.pfnStartup)();
  PolyglotConfigure(s_grim_tab_004dd238);
  Grim_OpenRegistry();
  Grim_DecodeRegKeyName((char *)&local_80);
  wuRegistry_GetStr((char *)&local_80,(char *)abStack_40,0x40,(char *)0x0);
  iVar8 = _stricmp(abStack_40,(byte *)s_TRUE_004dd660);
  if (iVar8 == 0) {
    g_nDeveloper = 1;
  }
  iVar8 = _stricmp(abStack_40,(byte *)s_pl_004dd65c);
  if (iVar8 == 0) {
    g_nDeveloper = 1;
  }
  if (g_nDeveloper == 0) {
    iVar8 = Grim_FindDataOnDrives(s_GrimData_004dd650);
    if (iVar8 == 0) {
      return 0;
    }
  }
  rdStartup(&g_aHs);
  iVar8 = rdOpen(0);
  if (iVar8 == 0) {
    return 0;
  }
  Win_AddMessageHook(Win_WndProc);
  Win_AddMessageHook(Win_IsSysCommandBlocked);
  iVar8 = GetDC(0);
  iVar2 = GetDeviceCaps(iVar8,0xc);
  ReleaseDC(0,iVar8);
  if (iVar2 < 8) {
    iVar8 = 0;
    pcVar3 = PolyglotGetString(s__engn001_Grim_Fandango_004dd638);
    pcVar4 = PolyglotGetString(s__engn002_System_must_be_in_256_c_004dd5f8);
    pvVar5 = Win_GetMainHwnd();
    Grim_FatalMessageBox((int)pvVar5,(int)pcVar4,(int)pcVar3,iVar8);
    return 0;
  }
  iVar8 = stdDisplay_Startup();
  if (iVar8 == 0) {
    return 0;
  }
  Grim_EnumDisplayModes();
  if ((g_nDeveloper != 0) && (g_bWindowedMode != 0)) {
    Reg_SetInt(s_ExperimentalDisplay_004dd5e4,1);
  }
  puVar6 = Display_InitFromConfig();
  if (puVar6 == (undefined *)0x0) {
    return 0;
  }
  puVar6 = grimlib_GameInitialize(&g_aHs,&g_aMs.pfnInitialize);
  if (puVar6 != (undefined *)0x0) {
    return 0;
  }
  uVar1 = (*g_aMs.pfnStartup)();
  if (((uint)(byte)(uVar1)) != 0) {
    iVar8 = 0;
    pcVar3 = PolyglotGetString(s__engn005_Grim_Fandango_could_not_004dd5a8);
    pcVar4 = PolyglotGetString(s__engn004_Please_make_sure_you_ar_004dd534);
    pvVar5 = Win_GetMainHwnd();
    Grim_FatalMessageBox((int)pvVar5,(int)pcVar4,(int)pcVar3,iVar8);
    return 0;
  }
  lua_openlib((int *)&PTR_s_Is3DHardwareEnabled_004dd350,UINT_004dd380);
  grimlib_SetShutdownCallback(((unsigned)(uintptr_t)grimdemo_PleaseShutdown));
  grimlib_SetPaletteCallback(((unsigned)(uintptr_t)grimdemo_SetPalette));
  grimlib_SetPageFlipCallback(((unsigned)(uintptr_t)stdDisplay_Update));
  grimlib_SetDebugToggleCallback(((unsigned)(uintptr_t)grimdemo_EnableDebugging));
  grimlib_FindResources();
  Grim_ShowSplash();
  grimdemo_EnableDebugging(1);
  iVar8 = grimlib_FindSystemFiles();
  if (iVar8 != 0) {
    iVar8 = 0;
    pcVar3 = PolyglotGetString(s__engn007_Grim_Fandango_could_not_004dd4dc);
    pcVar4 = PolyglotGetString(s__engn006_Please_make_sure_that_t_004dd47c);
    pvVar5 = Win_GetMainHwnd();
    Grim_FatalMessageBox((int)pvVar5,(int)pcVar4,(int)pcVar3,iVar8);
    return 0;
  }
  uVar7 = grimlib_Open(UINT_004f5a10,(char *)(-(uint)(UINT_004f5a14 != 0) & ((unsigned)(uintptr_t)&g_szBootFileArg)));
  if (uVar7 != 0) {
    return 0;
  }
  if (UINT_004f5a44 != 0) {
    ChoreFace_Toggle(1);
  }
  pvVar5 = Win_GetMainHwnd();
  SetActiveWindow((int)pvVar5);
  _g_dwGrimlib_MinimizeWhenInactive = 1;
  return 1;
}
#undef abStack_40
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

int __cdecl Grim_FatalMessageBox(int hwnd,int text,int caption,int type)

{
  int iVar1;
  
  UINT_004e814c = 0;
  iVar1 = MessageBoxA(hwnd,text,caption,type);
  Grim_ShutdownDisplay();
  CloseWindow(hwnd);
  stdControl_ShowMouseCursor(1);
  UINT_004e814c = 1;
  return iVar1;
}

/* ---- 0x00401900  Grim_ShutdownDisplay ---- */
void __cdecl Grim_ShutdownDisplay(void)

{
  if (g_nDisplayDeviceOpen != 0) {
    grimlib_UnsetDisplay();
    if (g_pStd3D_CurDevice == (Std3DDevice *)0x0) {
      stdDisplay_VBufferFree((VBuffer *)UINT_004f5a34);
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
  (*g_aMs.pfnShutdown)();
  (*g_aMs.pfnTerminate)();
  rdClose();
  rdShutdown();
  Grim_ShutdownDisplay();
  stdDisplay_Shutdown();
  if (g_bWindowedMode == 0) {
    stdControl_ShowMouseCursor(1);
  }
  wuRegistry_Shutdown();
  if (g_aPolyglotServices.pfnShutdown != (code *)0x0) {
    (*g_aPolyglotServices.pfnShutdown)();
  }
  if (g_aPolyglotServices.pfnTerminate != (code *)0x0) {
    (*g_aPolyglotServices.pfnTerminate)();
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
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  ColorFormat *pCVar6;
  VideoMode *pVVar7;
  Std3DDevice *pSVar8;
  uint *puVar9;
  undefined4 *puVar10;
  int *piVar11;
  ColorFormat format;
  
  format.dwRedBits = 5;
  format.dwBlueBits = 5;
  format.dwGreenShift = 5;
  puVar9 = &UINT_004f44e8;
  for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  puVar9 = &UINT_004f4d38;
  for (iVar2 = 0x13; uVar5 = g_dwStdDisplay_numDevices, iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  iVar4 = 0;
  format.dwGreenLoss = 2;
  _DAT_004f450c = 2;
  format.nColorMode = 1;
  format.nBpp = 0x10;
  format.dwGreenBits = 6;
  format.dwRedShift = 0xb;
  format.dwBlueShift = 0;
  format.dwRedLoss = 3;
  format.dwBlueLoss = 3;
  format.dwUnknown2c = 0;
  format.dwUnknown30 = 0;
  format.dwUnknown34 = 0;
  pCVar6 = &format;
  puVar9 = &UINT_004f4d54;
  for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar9 = pCVar6->nColorMode;
    pCVar6 = (ColorFormat *)&pCVar6->nBpp;
    puVar9 = puVar9 + 1;
  }
  UINT_004f44e8 = 1;
  UINT_004f44ec = 1;
  _DAT_004f44f0 = 1;
  _DAT_004f4d40 = 0x280;
  _DAT_004f4d44 = 0x1e0;
  g_pDisplayModes =
       (void *)(*g_pStd_HS->pAlloc)(uVar5 << 4,s_C__grimsrc_tools_grimdemo_grimde_004dd50c,0x313);
  puVar10 = g_pDisplayModes;
  for (iVar2 = (g_dwStdDisplay_numDevices & 0xfffffff) << 2; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  uVar5 = 0;
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)puVar10 = 0;
    puVar10 = (undefined4 *)((int)puVar10 + 1);
  }
  if (g_dwStdDisplay_numDevices != 0) {
    do {
      Display_SelectDevice(uVar5);
      *(uint *)((int)g_pDisplayModes + iVar4) = g_dwVideoModeCount;
      uVar1 = (*g_pStd_HS->pAlloc)
                        (g_dwVideoModeCount * 0x54,s_C__grimsrc_tools_grimdemo_grimde_004dd50c,0x31e
                        );
      *(undefined4 *)((int)g_pDisplayModes + iVar4 + 4) = uVar1;
      pVVar7 = g_aVideoModes;
      piVar11 = *(int **)((int)g_pDisplayModes + iVar4 + 4);
      for (uVar3 = g_dwVideoModeCount * 0x15 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
        *piVar11 = pVVar7->nFullscreen;
        pVVar7 = (VideoMode *)&pVVar7->dwUnknown4;
        piVar11 = piVar11 + 1;
      }
      for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(char *)piVar11 = (char)pVVar7->nFullscreen;
        pVVar7 = (VideoMode *)((int)&pVVar7->nFullscreen + 1);
        piVar11 = (int *)((int)piVar11 + 1);
      }
      *(undefined4 *)((int)g_pDisplayModes + iVar4 + 8) = 0;
      *(undefined4 *)((int)g_pDisplayModes + iVar4 + 0xc) = 0;
      uVar3 = D3D_Enumerate();
      if (uVar3 != 0) {
        *(uint *)((int)g_pDisplayModes + iVar4 + 8) = g_dwD3dDriverCount;
        if (g_dwD3dDriverCount != 0) {
          uVar1 = (*g_pStd_HS->pAlloc)
                            (g_dwD3dDriverCount * 0x22c,s_C__grimsrc_tools_grimdemo_grimde_004dd50c,
                             0x32a);
          *(undefined4 *)((int)g_pDisplayModes + iVar4 + 0xc) = uVar1;
        }
        pSVar8 = g_aStd3DDevices;
        piVar11 = *(int **)((int)g_pDisplayModes + iVar4 + 0xc);
        for (uVar3 = g_dwD3dDriverCount * 0x8b & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
          *piVar11 = pSVar8->nHardware;
          pSVar8 = (Std3DDevice *)&pSVar8->field_0x4;
          piVar11 = piVar11 + 1;
        }
        for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
          *(char *)piVar11 = (char)pSVar8->nHardware;
          pSVar8 = (Std3DDevice *)((int)&pSVar8->nHardware + 1);
          piVar11 = (int *)((int)piVar11 + 1);
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

uint __cdecl grimdemo_SetPalette(void *palette,int flags)

{
  stdDisplay_SetPalette((uint)palette);
  stdDisplay_SetMasterPalette(palette);
  if (g_pStd3D_CurDevice != (Std3DDevice *)0x0) {
    std3D_SetCurrentPalette(palette,flags);
  }
  return 1;
}

/* ---- 0x00402c80  Grim_ParseCommandLine ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* grimdemo.c: strtok loop over the command line. Options set g_bAlwaysLog, g_bDevMode,
   g_bWindowedStart etc., a bad option shows the 'GRIME: Grim Fandango Executable Usage' box. */

int __cdecl Grim_ParseCommandLine(char *cmdline)

{
  byte *pbVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  void *hwnd;
  char *pcVar5;
  
  pbVar1 = (byte *)strtok((byte *)cmdline,(byte *)s__004dd918);
  if (pbVar1 == (byte *)0x0) {
    return 1;
  }
  do {
    iVar2 = _stricmp(pbVar1,(byte *)s__t_004dd914);
    if ((iVar2 == 0) || (iVar2 = _stricmp(pbVar1,(byte *)s__t_004dd910), iVar2 == 0)) {
      puVar3 = (uint *)strtok((byte *)0x0,(byte *)s__004dd918);
      strncpy((uint *)s_grim_tab_004dd238,puVar3,0x103);
      DAT_004dd33b = 0;
LAB_00402f60:
      pbVar1 = (byte *)strtok((byte *)0x0,(byte *)s__004dd918);
    }
    else {
      iVar2 = _stricmp(pbVar1,(byte *)s__m_004dd90c);
      if ((iVar2 == 0) || (iVar2 = _stricmp(pbVar1,(byte *)s__m_004dd908), iVar2 == 0)) {
        uVar4 = strtok((byte *)0x0,(byte *)s__004dd918);
        _DAT_004dd34c = atoi(uVar4);
        grimlib_SetCacheMax((int)_DAT_004dd34c);
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(pbVar1,(byte *)s__c_004dd904);
      if ((iVar2 == 0) || (iVar2 = _stricmp(pbVar1,(byte *)s__c_004dd900), iVar2 == 0)) {
        UINT_004f5a44 = 1;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(pbVar1,(byte *)s__l_004dd8fc);
      if ((iVar2 == 0) || (iVar2 = _stricmp(pbVar1,(byte *)s__l_004dd8f8), iVar2 == 0)) {
        UINT_004f5a18 = 1;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(pbVar1,(byte *)s__h_004dd8f4);
      if ((iVar2 == 0) || (iVar2 = _stricmp(pbVar1,(byte *)s__h_004dd8f0), iVar2 == 0)) {
        UINT_004f5a28 = 1;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(pbVar1,(byte *)s__r_004dd8ec);
      if ((iVar2 == 0) || (iVar2 = _stricmp(pbVar1,(byte *)s__r_004dd8e8), iVar2 == 0)) {
        UINT_004f5a1c = 1;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(pbVar1,(byte *)s__w_004dd8e4);
      if ((iVar2 == 0) || (iVar2 = _stricmp(pbVar1,(byte *)s__w_004dd8e0), iVar2 == 0)) {
        g_bWindowedMode = 1;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(pbVar1,(byte *)s__s_004dd8dc);
      if ((iVar2 == 0) || (iVar2 = _stricmp(pbVar1,(byte *)s__s_004dd8d8), iVar2 == 0)) {
        UINT_004f5a10 = 1;
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(pbVar1,(byte *)s__b_004dd8d4);
      if ((iVar2 == 0) || (iVar2 = _stricmp(pbVar1,(byte *)s__b_004dd8d0), iVar2 == 0)) {
        UINT_004f5a14 = 1;
        puVar3 = (uint *)strtok((byte *)0x0,(byte *)s__004dd918);
        strncpy((uint *)g_szBootFileArg,puVar3,0x4f);
        g_szBootFileArg[0x4f] = '\0';
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(pbVar1,(byte *)s__p_004dd8cc);
      if ((iVar2 == 0) || (iVar2 = _stricmp(pbVar1,(byte *)s__p_004dd8c8), iVar2 == 0)) {
        pcVar5 = (char *)strtok((byte *)0x0,(byte *)s__004dd918);
        grimlib_AddResourcePath(pcVar5);
        goto LAB_00402f60;
      }
      iVar2 = _stricmp(pbVar1,(byte *)s__z_004dd8c4);
      if ((iVar2 != 0) && (iVar2 = _stricmp(pbVar1,(byte *)s__z_004dd8c0), iVar2 != 0)) {
        iVar2 = _stricmp(pbVar1,(byte *)s____004dd8bc);
        if ((iVar2 == 0) || (iVar2 = _stricmp(pbVar1,(byte *)s____004dd8b8), iVar2 == 0)) {
          cmdline = s_Usage_004dd8b0;
        }
        iVar2 = 0;
        pcVar5 = s_GRIME__Grim_Fandango_Executable_U_004dd048;
        hwnd = Win_GetMainHwnd();
        Grim_FatalMessageBox((int)hwnd,(int)pcVar5,(int)cmdline,iVar2);
        return 0;
      }
      pbVar1 = (byte *)strtok((byte *)0x0,(byte *)s__004dd918);
      UINT_004e806c = 0;
    }
    if (pbVar1 == (byte *)0x0) {
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
  
  Reg_Open((void *)0x80000002,((unsigned)(uintptr_t)&DAT_004dd958),s_1_0_004dd998);
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
  VBuffer *src;
  stdBitmap *bitmap;
  int iVar1;
  
  bitmap = stdBitmap_Load(s_splash_bm_004dd99c,0,0);
  if ((bitmap != (stdBitmap *)0x0) && (src = *bitmap->ppFrames, src != (VBuffer *)0x0)) {
    iVar1 = 0;
    if (0 < (src->format).nHeight) {
      do {
        sputRender_ColorCorrect
                  ((ushort *)(iVar1 * (src->format).nPitch + (int)src->pPixels),(src->format).nWidth
                  );
        iVar1 = iVar1 + 1;
      } while (iVar1 < (src->format).nHeight);
    }
    Surface_Blit((VBuffer *)&g_dwStdDisplay_frontBuffer,src,0,0,(int *)0x0,0);
    stdDisplay_Update();
    Surface_Blit((VBuffer *)&g_dwStdDisplay_frontBuffer,src,0,0,(int *)0x0,0);
    stdBitmap_Free(bitmap);
  }
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char f_Lua_Enumerate3DDevices[] __asm__("_Lua_Enumerate3DDevices");
extern char f_Lua_EnumerateVideoDevices[] __asm__("_Lua_EnumerateVideoDevices");
extern char f_Lua_GetVideoDevices[] __asm__("_Lua_GetVideoDevices");
extern char f_Lua_SetHardwareState[] __asm__("_Lua_SetHardwareState");
extern char f_Lua_SetVideoDevices[] __asm__("_Lua_SetVideoDevices");
extern char f_sputLua_Is3DHardwareEnabledL[] __asm__("_sputLua_Is3DHardwareEnabledL");
extern unsigned char grim_def_DAT_004dd33b __asm__("_DAT_004dd33b");
extern unsigned char grim_def_DAT_004dd34c[4] __asm__("_DAT_004dd34c");
extern unsigned short grim_def_DAT_004dd670 __asm__("_DAT_004dd670");
extern unsigned char grim_def_DAT_004dd672[2] __asm__("_DAT_004dd672");
extern unsigned char grim_def_DAT_004dd958[64] __asm__("_DAT_004dd958");
extern unsigned char grim_def_DAT_004f44f0[28] __asm__("_DAT_004f44f0");
extern unsigned char grim_def_DAT_004f450c[36] __asm__("_DAT_004f450c");
extern unsigned char grim_def_DAT_004f4d40[4] __asm__("_DAT_004f4d40");
extern unsigned char grim_def_DAT_004f4d44[16] __asm__("_DAT_004f4d44");
extern void *grim_def_PTR_s_Is3DHardwareEnabled_004dd350[12] __asm__("_PTR_s_Is3DHardwareEnabled_004dd350");
extern unsigned int grim_def_UINT_004dd380 __asm__("_UINT_004dd380");
extern unsigned int grim_def_UINT_004dd668 __asm__("_UINT_004dd668");
extern unsigned int grim_def_UINT_004dd66c __asm__("_UINT_004dd66c");
extern unsigned int grim_def_UINT_004f44ec __asm__("_UINT_004f44ec");
extern unsigned char grim_def_UINT_004f4d54[60] __asm__("_UINT_004f4d54");
extern unsigned int grim_def_UINT_004f5a10 __asm__("_UINT_004f5a10");
extern unsigned int grim_def_UINT_004f5a14 __asm__("_UINT_004f5a14");
extern unsigned int grim_def_UINT_004f5a44 __asm__("_UINT_004f5a44");
extern SysModuleIface grim_def_g_aMs __asm__("_g_aMs");
extern SysModuleIface grim_def_g_aPolyglotServices __asm__("_g_aPolyglotServices");
extern unsigned char grim_def_g_dwGrimlib_MinimizeWhenInactive[4] __asm__("_g_dwGrimlib_MinimizeWhenInactive");
extern char grim_def_g_szBootFileArg[80] __asm__("_g_szBootFileArg");
extern char grim_def_s_1_0_004dd998[4] __asm__("_s_1_0_004dd998");
extern char grim_def_s_Enumerate3DDevices_004dd3a8[] __asm__("_s_Enumerate3DDevices_004dd3a8");
extern char grim_def_s_EnumerateVideoDevices_004dd390[] __asm__("_s_EnumerateVideoDevices_004dd390");
extern char grim_def_s_GRIME__Grim_Fandango_Executable_U_004dd048[496] __asm__("_s_GRIME__Grim_Fandango_Executable_U_004dd048");
extern char grim_def_s_GetVideoDevices_004dd3e0[] __asm__("_s_GetVideoDevices_004dd3e0");
extern char grim_def_s_GrimData_004dd650[12] __asm__("_s_GrimData_004dd650");
extern char grim_def_s_Is3DHardwareEnabled_004dd3f0[] __asm__("_s_Is3DHardwareEnabled_004dd3f0");
extern char grim_def_s_SetHardwareState_004dd3bc[] __asm__("_s_SetHardwareState_004dd3bc");
extern char grim_def_s_SetVideoDevices_004dd3d0[] __asm__("_s_SetVideoDevices_004dd3d0");
extern char grim_def_s_TRUE_004dd660[8] __asm__("_s_TRUE_004dd660");
extern char grim_def_s_Usage_004dd8b0[8] __asm__("_s_Usage_004dd8b0");
extern char grim_def_s____004dd8b8[4] __asm__("_s____004dd8b8");
extern char grim_def_s____004dd8bc[4] __asm__("_s____004dd8bc");
extern char grim_def_s__b_004dd8d0[4] __asm__("_s__b_004dd8d0");
extern char grim_def_s__b_004dd8d4[4] __asm__("_s__b_004dd8d4");
extern char grim_def_s__c_004dd900[4] __asm__("_s__c_004dd900");
extern char grim_def_s__c_004dd904[4] __asm__("_s__c_004dd904");
extern char grim_def_s__engn001_Grim_Fandango_004dd638[24] __asm__("_s__engn001_Grim_Fandango_004dd638");
extern char grim_def_s__engn002_System_must_be_in_256_c_004dd5f8[64] __asm__("_s__engn002_System_must_be_in_256_c_004dd5f8");
extern char grim_def_s__engn004_Please_make_sure_you_ar_004dd534[116] __asm__("_s__engn004_Please_make_sure_you_ar_004dd534");
extern char grim_def_s__engn005_Grim_Fandango_could_not_004dd5a8[60] __asm__("_s__engn005_Grim_Fandango_could_not_004dd5a8");
extern char grim_def_s__engn006_Please_make_sure_that_t_004dd47c[96] __asm__("_s__engn006_Please_make_sure_that_t_004dd47c");
extern char grim_def_s__engn007_Grim_Fandango_could_not_004dd4dc[48] __asm__("_s__engn007_Grim_Fandango_could_not_004dd4dc");
extern char grim_def_s__h_004dd8f0[4] __asm__("_s__h_004dd8f0");
extern char grim_def_s__h_004dd8f4[4] __asm__("_s__h_004dd8f4");
extern char grim_def_s__l_004dd8f8[4] __asm__("_s__l_004dd8f8");
extern char grim_def_s__l_004dd8fc[4] __asm__("_s__l_004dd8fc");
extern char grim_def_s__m_004dd908[4] __asm__("_s__m_004dd908");
extern char grim_def_s__m_004dd90c[4] __asm__("_s__m_004dd90c");
extern char grim_def_s__p_004dd8c8[4] __asm__("_s__p_004dd8c8");
extern char grim_def_s__p_004dd8cc[4] __asm__("_s__p_004dd8cc");
extern char grim_def_s__r_004dd8e8[4] __asm__("_s__r_004dd8e8");
extern char grim_def_s__r_004dd8ec[4] __asm__("_s__r_004dd8ec");
extern char grim_def_s__s_004dd8d8[4] __asm__("_s__s_004dd8d8");
extern char grim_def_s__s_004dd8dc[4] __asm__("_s__s_004dd8dc");
extern char grim_def_s__t_004dd910[4] __asm__("_s__t_004dd910");
extern char grim_def_s__t_004dd914[4] __asm__("_s__t_004dd914");
extern char grim_def_s__w_004dd8e0[4] __asm__("_s__w_004dd8e0");
extern char grim_def_s__w_004dd8e4[4] __asm__("_s__w_004dd8e4");
extern char grim_def_s__z_004dd8c0[4] __asm__("_s__z_004dd8c0");
extern char grim_def_s__z_004dd8c4[4] __asm__("_s__z_004dd8c4");
extern char grim_def_s_grim_tab_004dd238[259] __asm__("_s_grim_tab_004dd238");
extern char grim_def_s_pl_004dd65c[4] __asm__("_s_pl_004dd65c");
extern char grim_def_s_splash_bm_004dd99c[12] __asm__("_s_splash_bm_004dd99c");
/* 0x004dd048, 496 bytes */ GRIM_DATA("004dd048") char grim_def_s_GRIME__Grim_Fandango_Executable_U_004dd048[496] __asm__("_s_GRIME__Grim_Fandango_Executable_U_004dd048") = "GRIME: Grim Fandango Executable\n\nUsage:\tgrime [-\?] [-w] [-l] [-r] [-h] [-c] [-m ####] [-s] [-b bootparam] [-p path] [-z]\n\n-\?\tDisplay usage and quit\n-w\tDisplay in a window\n-l\tLog messages to debug.log\n-r\tLog resource usage to resource.log\n-h\tAttempt to use hardware\n-c\tAfter starting, invoke the chore tool\n-m\tSet maximum memory usage to ####\n-s\tResume most recently loaded or saved game\n-b\tPass argument to the BOOT script\n-p\tUse path as an additional data directory.\n-z\tAccelerated zbuffers\n\n";
/* 0x004dd238, 259 bytes */ GRIM_DATA("004dd238") char grim_def_s_grim_tab_004dd238[259] __asm__("_s_grim_tab_004dd238") = "grim.tab";
/* 0x004dd33b, 1 bytes */ GRIM_DATA("004dd238") unsigned char grim_def_DAT_004dd33b __asm__("_DAT_004dd33b") = 0x0;
/* 0x004dd34c, 4 bytes */ GRIM_DATA("004dd34c") unsigned char grim_def_DAT_004dd34c[4] __asm__("_DAT_004dd34c") = { 0x00, 0x80, 0xbb };
/* 0x004dd350, 48 bytes */ GRIM_DATA("004dd350") void *grim_def_PTR_s_Is3DHardwareEnabled_004dd350[12] __asm__("_PTR_s_Is3DHardwareEnabled_004dd350") = {
    (void *)&grim_def_s_Is3DHardwareEnabled_004dd3f0, (void *)f_sputLua_Is3DHardwareEnabledL, (void *)&grim_def_s_GetVideoDevices_004dd3e0, (void *)f_Lua_GetVideoDevices,
    (void *)&grim_def_s_SetVideoDevices_004dd3d0, (void *)f_Lua_SetVideoDevices, (void *)&grim_def_s_SetHardwareState_004dd3bc, (void *)f_Lua_SetHardwareState,
    (void *)&grim_def_s_Enumerate3DDevices_004dd3a8, (void *)f_Lua_Enumerate3DDevices, (void *)&grim_def_s_EnumerateVideoDevices_004dd390, (void *)f_Lua_EnumerateVideoDevices
};
/* 0x004dd380, 4 bytes */ GRIM_DATA("004dd380") unsigned int grim_def_UINT_004dd380 __asm__("_UINT_004dd380") = 0x6;
/* 0x004dd47c, 96 bytes */ GRIM_DATA("004dd47c") char grim_def_s__engn006_Please_make_sure_that_t_004dd47c[96] __asm__("_s__engn006_Please_make_sure_that_t_004dd47c") = "/engn006/Please make sure that the game is properly installed and that the CD is in your drive.";
/* 0x004dd4dc, 48 bytes */ GRIM_DATA("004dd4dc") char grim_def_s__engn007_Grim_Fandango_could_not_004dd4dc[48] __asm__("_s__engn007_Grim_Fandango_could_not_004dd4dc") = "/engn007/Grim Fandango could not find files!";
/* 0x004dd534, 116 bytes */ GRIM_DATA("004dd534") char grim_def_s__engn004_Please_make_sure_you_ar_004dd534[116] __asm__("_s__engn004_Please_make_sure_you_ar_004dd534") = "/engn004/Please make sure you are not running any other DirectX apps that take exclusive control of your hardware.";
/* 0x004dd5a8, 60 bytes */ GRIM_DATA("004dd5a8") char grim_def_s__engn005_Grim_Fandango_could_not_004dd5a8[60] __asm__("_s__engn005_Grim_Fandango_could_not_004dd5a8") = "/engn005/Grim Fandango could not initialize your hardware!";
/* 0x004dd5f8, 64 bytes */ GRIM_DATA("004dd5f8") char grim_def_s__engn002_System_must_be_in_256_c_004dd5f8[64] __asm__("_s__engn002_System_must_be_in_256_c_004dd5f8") = "/engn002/System must be in 256 color depth or better to run.";
/* 0x004dd638, 24 bytes */ GRIM_DATA("004dd638") char grim_def_s__engn001_Grim_Fandango_004dd638[24] __asm__("_s__engn001_Grim_Fandango_004dd638") = "/engn001/Grim Fandango";
/* 0x004dd650, 12 bytes */ GRIM_DATA("004dd650") char grim_def_s_GrimData_004dd650[12] __asm__("_s_GrimData_004dd650") = "GrimData";
/* 0x004dd65c, 4 bytes */ GRIM_DATA("004dd65c") char grim_def_s_pl_004dd65c[4] __asm__("_s_pl_004dd65c") = "pl";
/* 0x004dd660, 8 bytes */ GRIM_DATA("004dd660") char grim_def_s_TRUE_004dd660[8] __asm__("_s_TRUE_004dd660") = "TRUE";
/* 0x004dd668, 4 bytes */ GRIM_DATA("004dd668") unsigned int grim_def_UINT_004dd668 __asm__("_UINT_004dd668") = 0x6568726f;
/* 0x004dd66c, 4 bytes */ GRIM_DATA("004dd66c") unsigned int grim_def_UINT_004dd66c __asm__("_UINT_004dd66c") = 0x6e65775a;
/* 0x004dd670, 2 bytes */ GRIM_DATA("004dd670") unsigned short grim_def_DAT_004dd670 __asm__("_DAT_004dd670") = 0x7560;
/* 0x004dd672, 2 bytes */ GRIM_DATA("004dd670") unsigned char grim_def_DAT_004dd672[2] __asm__("_DAT_004dd672") = {0};
/* 0x004dd8b0, 8 bytes */ GRIM_DATA("004dd8b0") char grim_def_s_Usage_004dd8b0[8] __asm__("_s_Usage_004dd8b0") = "Usage";
/* 0x004dd8b8, 4 bytes */ GRIM_DATA("004dd8b8") char grim_def_s____004dd8b8[4] __asm__("_s____004dd8b8") = "/\?";
/* 0x004dd8bc, 4 bytes */ GRIM_DATA("004dd8bc") char grim_def_s____004dd8bc[4] __asm__("_s____004dd8bc") = "-\?";
/* 0x004dd8c0, 4 bytes */ GRIM_DATA("004dd8c0") char grim_def_s__z_004dd8c0[4] __asm__("_s__z_004dd8c0") = "/z";
/* 0x004dd8c4, 4 bytes */ GRIM_DATA("004dd8c4") char grim_def_s__z_004dd8c4[4] __asm__("_s__z_004dd8c4") = "-z";
/* 0x004dd8c8, 4 bytes */ GRIM_DATA("004dd8c8") char grim_def_s__p_004dd8c8[4] __asm__("_s__p_004dd8c8") = "/p";
/* 0x004dd8cc, 4 bytes */ GRIM_DATA("004dd8cc") char grim_def_s__p_004dd8cc[4] __asm__("_s__p_004dd8cc") = "-p";
/* 0x004dd8d0, 4 bytes */ GRIM_DATA("004dd8d0") char grim_def_s__b_004dd8d0[4] __asm__("_s__b_004dd8d0") = "/b";
/* 0x004dd8d4, 4 bytes */ GRIM_DATA("004dd8d4") char grim_def_s__b_004dd8d4[4] __asm__("_s__b_004dd8d4") = "-b";
/* 0x004dd8d8, 4 bytes */ GRIM_DATA("004dd8d8") char grim_def_s__s_004dd8d8[4] __asm__("_s__s_004dd8d8") = "/s";
/* 0x004dd8dc, 4 bytes */ GRIM_DATA("004dd8dc") char grim_def_s__s_004dd8dc[4] __asm__("_s__s_004dd8dc") = "-s";
/* 0x004dd8e0, 4 bytes */ GRIM_DATA("004dd8e0") char grim_def_s__w_004dd8e0[4] __asm__("_s__w_004dd8e0") = "/w";
/* 0x004dd8e4, 4 bytes */ GRIM_DATA("004dd8e4") char grim_def_s__w_004dd8e4[4] __asm__("_s__w_004dd8e4") = "-w";
/* 0x004dd8e8, 4 bytes */ GRIM_DATA("004dd8e8") char grim_def_s__r_004dd8e8[4] __asm__("_s__r_004dd8e8") = "/r";
/* 0x004dd8ec, 4 bytes */ GRIM_DATA("004dd8ec") char grim_def_s__r_004dd8ec[4] __asm__("_s__r_004dd8ec") = "-r";
/* 0x004dd8f0, 4 bytes */ GRIM_DATA("004dd8f0") char grim_def_s__h_004dd8f0[4] __asm__("_s__h_004dd8f0") = "/h";
/* 0x004dd8f4, 4 bytes */ GRIM_DATA("004dd8f4") char grim_def_s__h_004dd8f4[4] __asm__("_s__h_004dd8f4") = "-h";
/* 0x004dd8f8, 4 bytes */ GRIM_DATA("004dd8f8") char grim_def_s__l_004dd8f8[4] __asm__("_s__l_004dd8f8") = "/l";
/* 0x004dd8fc, 4 bytes */ GRIM_DATA("004dd8fc") char grim_def_s__l_004dd8fc[4] __asm__("_s__l_004dd8fc") = "-l";
/* 0x004dd900, 4 bytes */ GRIM_DATA("004dd900") char grim_def_s__c_004dd900[4] __asm__("_s__c_004dd900") = "/c";
/* 0x004dd904, 4 bytes */ GRIM_DATA("004dd904") char grim_def_s__c_004dd904[4] __asm__("_s__c_004dd904") = "-c";
/* 0x004dd908, 4 bytes */ GRIM_DATA("004dd908") char grim_def_s__m_004dd908[4] __asm__("_s__m_004dd908") = "/m";
/* 0x004dd90c, 4 bytes */ GRIM_DATA("004dd90c") char grim_def_s__m_004dd90c[4] __asm__("_s__m_004dd90c") = "-m";
/* 0x004dd910, 4 bytes */ GRIM_DATA("004dd910") char grim_def_s__t_004dd910[4] __asm__("_s__t_004dd910") = "/t";
/* 0x004dd914, 4 bytes */ GRIM_DATA("004dd914") char grim_def_s__t_004dd914[4] __asm__("_s__t_004dd914") = "-t";
/* 0x004dd958, 64 bytes */ GRIM_DATA("004dd958") unsigned char grim_def_DAT_004dd958[64] __asm__("_DAT_004dd958") = {
    0x53, 0x4f, 0x46, 0x54, 0x57, 0x41, 0x52, 0x45, 0x5c, 0x4c, 0x75, 0x63, 0x61, 0x73, 0x41, 0x72,
    0x74, 0x73, 0x20, 0x45, 0x6e, 0x74, 0x65, 0x72, 0x74, 0x61, 0x69, 0x6e, 0x6d, 0x65, 0x6e, 0x74,
    0x20, 0x43, 0x6f, 0x6d, 0x70, 0x61, 0x6e, 0x79, 0x20, 0x4c, 0x4c, 0x43, 0x5c, 0x47, 0x72, 0x69,
    0x6d, 0x20, 0x46, 0x61, 0x6e, 0x64, 0x61, 0x6e, 0x67, 0x6f, 0x5c, 0x76, 0x31, 0x2e, 0x30
};
/* 0x004dd998, 4 bytes */ GRIM_DATA("004dd998") char grim_def_s_1_0_004dd998[4] __asm__("_s_1_0_004dd998") = "1.0";
/* 0x004dd99c, 12 bytes */ GRIM_DATA("004dd99c") char grim_def_s_splash_bm_004dd99c[12] __asm__("_s_splash_bm_004dd99c") = "splash.bm";
/* 0x004f44ec, 4 bytes */ GRIM_DATA("004f44ec") unsigned int grim_def_UINT_004f44ec __asm__("_UINT_004f44ec") = 0x0;
/* 0x004f44f0, 28 bytes */ GRIM_DATA("004f44f0") unsigned char grim_def_DAT_004f44f0[28] __asm__("_DAT_004f44f0") = {0};
/* 0x004f450c, 36 bytes */ GRIM_DATA("004f450c") unsigned char grim_def_DAT_004f450c[36] __asm__("_DAT_004f450c") = {0};
/* 0x004f4d40, 4 bytes */ GRIM_DATA("004f4d40") unsigned char grim_def_DAT_004f4d40[4] __asm__("_DAT_004f4d40") = {0};
/* 0x004f4d44, 16 bytes */ GRIM_DATA("004f4d44") unsigned char grim_def_DAT_004f4d44[16] __asm__("_DAT_004f4d44") = {0};
/* 0x004f4d54, 60 bytes */ GRIM_DATA("004f4d54") unsigned char grim_def_UINT_004f4d54[60] __asm__("_UINT_004f4d54") = {0};
/* 0x004f59b0, 80 bytes */ /* loose */ char grim_def_g_szBootFileArg[80] __asm__("_g_szBootFileArg") = "";
/* 0x004f5a00, 4 bytes */ /* loose */ unsigned char grim_def_g_dwGrimlib_MinimizeWhenInactive[4] __asm__("_g_dwGrimlib_MinimizeWhenInactive") = {0};
/* 0x004f5a10, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a10 __asm__("_UINT_004f5a10") = 0x0;
/* 0x004f5a14, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a14 __asm__("_UINT_004f5a14") = 0x0;
/* 0x004f5a44, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a44 __asm__("_UINT_004f5a44") = 0x0;
/* 0x008ddd80, 32 bytes */ GRIM_DATA("008ddd80") SysModuleIface grim_def_g_aPolyglotServices __asm__("_g_aPolyglotServices") = {0};
/* 0x008dde20, 32 bytes */ GRIM_DATA("008dde20") SysModuleIface grim_def_g_aMs __asm__("_g_aMs") = {0};
