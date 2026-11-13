/* GRIMFANDANGO.EXE :: window.c
 * functions 0x00401010 .. 0x004bff70 (15 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00401010  Win_WinMain ---- */
/* WinMain: the real program entry after the MSVC CRT start-up (entry at 0x4aca30) */

undefined * __stdcall Win_WinMain(int a1,int a2,int a3,int a4)

{
  Win_AbortIfAlreadyRunning((void *)a1,(void *)a2,(char *)a3,a4,s_Grim_Fandango_004dd404);
  return (undefined *)0x0;
}

/* ---- 0x00402fd0  Win_WndProc ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* grimdemo.c window procedure. WM_ACTIVATEAPP pauses/resumes the engine, WM_KEYDOWN handles the
   Backspace-chord debug keys (C choreface, F fps, P profile, S screenshot, T reset textures, Z
   z-buffer dump, F12 grimpatch.bin, NumLock spew). */

undefined * Win_WndProc(undefined4 param_1,uint param_2,int param_3)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  short sVar5;
  int iVar6;
  #define local_40 (*(char (*)[64])(_frame + (0x50 - 0x40)))
  
  uVar2 = UINT_004f5a94;
  uVar1 = UINT_004f5a90;
  if (0x10 < param_2) {
    if (param_2 < 0x1d) {
      if (param_2 == 0x1c) {
        if ((param_3 == 0) && (INT_004dd38c != 0)) {
          if (g_bWindowedMode == 0) {
            grimlib_SetPause(1);
            Grim_ShutdownDisplay();
            iVar6 = 6;
            iVar3 = Win_GetMainHwnd();
            ShowWindow(iVar3,iVar6);
          }
          Input_SetAcquired(0);
          INT_004dd38c = 0;
          return (undefined *)0x0;
        }
        if (param_3 == 0) {
          return (undefined *)0x0;
        }
        if (INT_004dd38c != 0) {
          return (undefined *)0x0;
        }
        if (g_bWindowedMode == 0) {
          grimlib_SetPause(0);
          iVar6 = 9;
          iVar3 = Win_GetMainHwnd();
          ShowWindow(iVar3,iVar6);
          Display_InitFromConfig();
        }
        INT_004dd38c = 1;
        Input_SetAcquired(1);
        sputRender_ForceRefresh();
        stdControl_ShowMouseCursor(g_bWindowedMode);
        return (undefined *)0x0;
      }
      if (param_2 == 0x14) {
        return (undefined *)0x1;
      }
    }
    else if (param_2 < 0x101) {
      if (param_2 == 0x100) {
        switch(param_3) {
        case 8:
          if (g_nGrimlib_bDebugKeys != 0) {
            g_bDebugChordHeld = 1;
            return (undefined *)0x0;
          }
          break;
        case 0x13:
          sputLua_DoPauseCallback();
          return (undefined *)0x1;
        case 0x43:
          if (g_bDebugChordHeld != 0) {
            ChoreFace_Toggle(1);
            return (undefined *)0x1;
          }
          break;
        case 0x46:
          if (g_bDebugChordHeld != 0) {
            _g_bDrawFrameRate = (uint)(_g_bDrawFrameRate == 0);
            return (undefined *)0x1;
          }
          break;
        case 0x50:
          if (g_bDebugChordHeld != 0) {
            g_nDrawPerfData = (uint)(g_nDrawPerfData == 0);
            return (undefined *)0x1;
          }
          break;
        case 0x53:
          if (g_bDebugChordHeld != 0) {
            UINT_004f5a90 = UINT_004f5a90 + 1;
            sprintf(local_40,s__s_d_bmp_004dd928,&DAT_004dd934,uVar1);
            sputRender_SaveDrawBuffer(local_40);
            return (undefined *)0x0;
          }
          break;
        case 0x54:
          if (g_bDebugChordHeld != 0) {
            std3D_PurgeTextureCache();
            return (undefined *)0x1;
          }
          break;
        case 0x5a:
          if (g_bDebugChordHeld != 0) {
            UINT_004f5a94 = UINT_004f5a94 + 1;
            sprintf(local_40,s__s_d_zbm_004dd91c,&DAT_004dd934,uVar2);
            Render_SaveZBufferBmp(local_40);
            return (undefined *)0x0;
          }
          break;
        case 0x7b:
          iVar3 = GetKeyState(8);
          if ((short)iVar3 != 0) {
            lua_dofile(s_grimpatch_bin_004dd93c);
            return (undefined *)0x1;
          }
          break;
        case 0x90:
          Spew_Startup();
          return (undefined *)0x1;
        }
      }
      else if ((param_2 == 0x20) && (g_bWindowedMode == 0)) {
        SetCursor(0);
        return (undefined *)0x1;
      }
    }
    else if (param_2 < 0x219) {
      if (param_2 == 0x218) {
        if (param_3 == 0) {
          return (undefined *)0x0;
        }
      }
      else {
        switch(param_2) {
        case 0x101:
          if (param_3 == 8) {
            g_bDebugChordHeld = 0;
            return (undefined *)0x0;
          }
          if ((param_3 == 0x43) && (g_bDebugChordHeld != 0)) {
            return (undefined *)0x1;
          }
          break;
        case 0x102:
          puVar4 = grimlib_CharacterCallback(param_3);
          return puVar4;
        case 0x104:
          return (undefined *)0x1;
        case 0x105:
          goto switchD_0040336f_caseD_105;
        }
      }
    }
    return (undefined *)0x0;
  }
  if (param_2 == 0x10) {
    iVar3 = ChoreFace_Toggle(0);
    if (iVar3 != 0) {
      iVar3 = Win_GetMainHwnd();
      iVar3 = IsIconic(iVar3);
      if (iVar3 != 0) {
        return (undefined *)0x0;
      }
      iVar3 = grimlib_ConfirmClose();
      return (undefined *)(uint)(iVar3 == 0);
    }
switchD_0040336f_caseD_105:
    return (undefined *)0x1;
  }
  if (param_2 != 6) {
    return (undefined *)0x0;
  }
  if (g_dwZg_App_bAppActive == 0) {
    return (undefined *)0x0;
  }
  sVar5 = (short)param_3;
  if (g_nStdControl_bOpen != 0) {
    Input_SetAcquired((uint)(sVar5 != 0));
    if (sVar5 == 0) goto LAB_0040303f;
    stdControl_Flush();
    stdControl_ShowMouseCursor(g_bWindowedMode);
  }
  if (sVar5 != 0) {
    return (undefined *)0x0;
  }
LAB_0040303f:
  if ((g_bWindowedMode == 0) && (UINT_004e814c != 0)) {
    iVar6 = 6;
    iVar3 = Win_GetMainHwnd();
    ShowWindow(iVar3,iVar6);
    return (undefined *)0x0;
  }
  return (undefined *)0x0;
}
#undef local_40


/* ---- 0x00473360  Win_SetMainHwnd ---- */
void Win_SetMainHwnd(void *param_1)

{
  g_pMainHwnd = param_1;
  return;
}

/* ---- 0x00473370  Win_GetMainHwnd ---- */
void * Win_GetMainHwnd(void)

{
  return g_pMainHwnd;
}

/* ---- 0x00473380  Win_SetInstance ---- */
void Win_SetInstance(uint param_1)

{
  UINT_007f608c = param_1;
  return;
}

/* ---- 0x00473390  Win_GetInstance ---- */
/* Returns the HINSTANCE of the executable */

uint Win_GetInstance(void)

{
  return UINT_007f608c;
}

/* ---- 0x004772d0  Win_IsSysCommandBlocked ---- */
/* Window-message filter: true for WM_SYSCOMMAND with SC_KEYMENU (0xf100) or SC_SCREENSAVE (0xf140).
    */

undefined4 Win_IsSysCommandBlocked(undefined4 param_1,int param_2,int param_3)

{
  if (param_2 != 0x112) {
    return 0;
  }
  if ((param_3 != 0xf100) && (param_3 != 0xf140)) {
    return 0;
  }
  return 1;
}

/* ---- 0x004abf40  Win_AbortIfAlreadyRunning ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WinMain helper: brings an existing 'wKernel' window to the front and exits */

void __cdecl
Win_AbortIfAlreadyRunning
          (void *hInstance,void *hPrevInstance,char *cmdLine,int nCmdShow,char *appName)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FindWindowA(((unsigned)(uintptr_t)&s_wKernel_004ed080),(int)appName);
  if (iVar1 != 0) {
    SetForegroundWindow(iVar1);
    ShowWindow(iVar1,9);
    exit(0xffffffff);
  }
  UINT_008d0a7c = 0;
  g_dwWinDialogCount = 0;
  g_nWinQuit = 0;
  UINT_008d0a8c = 0;
  UINT_008d09e4 = (uint)hInstance;
  _DAT_008d09e0 = nCmdShow;
  Win_CreateMainWindow(hInstance,nCmdShow,appName);
  Win_SetMainHwnd(g_pWinMainHwnd);
  Win_SetInstance(UINT_008d09e4);
  InitCommonControls();
  iVar1 = GetSystemMetrics(0x20);
  UINT_008d0a84 = iVar1 << 1;
  iVar1 = GetSystemMetrics(0x20);
  iVar2 = GetSystemMetrics(0xf);
  UINT_008d0a88 = iVar2 + iVar1 * 2;
  iVar1 = Main_Startup(cmdLine);
  if (iVar1 != 0) {
    UINT_008d0a8c = 1;
    do {
      Win_PumpMessages();
    } while (g_nWinQuit == 0);
  }
  return;
}
#endif


/* ---- 0x004ac020  Win_PumpMessages ---- */
/* One message-loop iteration: runs Main_Service when idle, routes messages to registered dialogs */

uint Win_PumpMessages(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  void **ppvVar3;
  #define local_1c (*(undefined1 (*)[8])(_frame + (0x30 - 0x1c)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  iVar1 = PeekMessageA((int)local_1c,0,0,0,0);
  if (iVar1 == 0) {
    Main_Service();
    return 0;
  }
  iVar1 = GetMessageA((int)local_1c,0,0,0);
  do {
    if (iVar1 == 0) {
      g_nWinQuit = 1;
      return local_14;
    }
    uVar2 = 0;
    if (g_dwWinDialogCount != 0) {
      ppvVar3 = &g_pWinDialogs;
      do {
        iVar1 = IsDialogMessageA((int)*ppvVar3,(int)local_1c);
        if (iVar1 != 0) break;
        uVar2 = uVar2 + 1;
        ppvVar3 = ppvVar3 + 1;
      } while (uVar2 < g_dwWinDialogCount);
    }
    if (uVar2 == g_dwWinDialogCount) {
      TranslateMessage((int)local_1c);
      DispatchMessageA((int)local_1c);
    }
    iVar1 = PeekMessageA((int)local_1c,0,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    iVar1 = GetMessageA((int)local_1c,0,0,0);
  } while( true );
}
#undef local_14
#undef local_1c


/* ---- 0x004ac100  Win_SetWindowedSize ---- */
int __cdecl Win_SetWindowedSize(int fullscreen,int w,int h)

{
  UINT_008d09dc = fullscreen;
  if (fullscreen == 0) {
    SetWindowLongA((int)g_pWinMainHwnd,-0x10,0x10cf0000);
    SetWindowPos((int)g_pWinMainHwnd,0,0,0,w + UINT_008d0a84,h + UINT_008d0a88,6);
  }
  return 1;
}

/* ---- 0x004ac160  Win_AddMessageHook ---- */
void Win_AddMessageHook(void *param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = &g_nWinMessageHookOn;
  do {
    if (*piVar1 == 0) break;
    piVar1 = piVar1 + 2;
    iVar2 = iVar2 + 1;
  } while ((int)piVar1 < ((unsigned)(uintptr_t)&UINT_008d0a6c));
  (&g_pWinMessageHooks)[iVar2 * 2] = param_1;
  (&g_nWinMessageHookOn)[iVar2 * 2] = 1;
  UINT_008d0a7c = UINT_008d0a7c + 1;
  return;
}

/* ---- 0x004ac1a0  Win_RemoveMessageHook ---- */
undefined4 Win_RemoveMessageHook(void *param_1)

{
  void **ppvVar1;
  int iVar2;
  
  iVar2 = 0;
  ppvVar1 = &g_pWinMessageHooks;
  do {
    if (*ppvVar1 == param_1) break;
    ppvVar1 = ppvVar1 + 2;
    iVar2 = iVar2 + 1;
  } while ((int)ppvVar1 < ((unsigned)(uintptr_t)&DAT_008d0a68));
  (&g_pWinMessageHooks)[iVar2 * 2] = (void *)0x0;
  (&g_nWinMessageHookOn)[iVar2 * 2] = 0;
  UINT_008d0a7c = UINT_008d0a7c - 1;
  return 1;
}

/* ---- 0x004ac1f0  Win_CreateMainWindow ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 Win_CreateMainWindow(uint param_1,undefined4 param_2,int param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int a7;
  int a9;
  int a10;
  uint a11;
  int a12;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
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
  
  local_30 = 0x30;
  local_1c = param_1;
  local_8 = (uint)s_wKernel_004ed080;
  local_c = 0;
  local_28 = (uint)Win_KernelWndProc;
  local_2c = 3;
  local_18 = LoadIconA(param_1,((unsigned)(uintptr_t)&s_APPICON_004ed088));
  if (local_18 == 0) {
    local_18 = LoadIconA(0,0x7f00);
  }
  local_4 = LoadIconA(param_1,((unsigned)(uintptr_t)&s_APPICON_004ed088));
  if (local_4 == 0) {
    local_4 = LoadIconA(0,0x7f00);
  }
  local_14 = LoadCursorA(0,0x7f00);
  local_24 = 0;
  local_20 = 0;
  local_10 = GetStockObject(4);
  iVar1 = RegisterClassExA((int)&local_30);
  if ((short)iVar1 == 0) {
    return 0;
  }
  iVar1 = FindWindowA(((unsigned)(uintptr_t)&s_wKernel_004ed080),param_3);
  if (iVar1 != 0) {
    exit(0xffffffff);
  }
  a12 = 0;
  a10 = 0;
  a9 = 0;
  a11 = param_1;
  iVar1 = GetSystemMetrics(1);
  a7 = GetSystemMetrics(0);
  g_pWinMainHwnd =
       (void *)CreateWindowExA(0x40000,((unsigned)(uintptr_t)&s_wKernel_004ed080),param_3,-0x70000000,0,0,a7,iVar1,a9,a10,a11,a12);
  if (g_pWinMainHwnd == (void *)0x0) {
    return 0;
  }
  UINT_008d09e4 = param_1;
  ShowWindow((int)g_pWinMainHwnd,1);
  UpdateWindow((int)g_pWinMainHwnd);
  return 1;
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
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004ac340  Win_KernelWndProc ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Window procedure of the wKernel window class; forwards to the registered message hooks
   (Win_WndProc) */

undefined * __stdcall Win_KernelWndProc(int a1,int a2,int a3,int a4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  int a1_00;
  undefined *puVar2;
  int iVar3;
  void **ppvVar4;
  int iVar5;
  bool bVar6;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined **)(_frame + (0x20 - 0x4)))
  
  a1_00 = a4;
  iVar5 = 0;
  bVar1 = true;
  switch(a2) {
  case 1:
    g_dwZg_App_bAppActive = 0;
    UINT_008d0a6c = 0;
    break;
  case 2:
    UINT_008d0a8c = 0;
    Main_Shutdown();
    PostQuitMessage(0);
    bVar1 = false;
    break;
  case 6:
    if (((short)a3 == 2) || ((short)a3 == 1)) {
      UINT_008d0a6c = 1;
      if ((UINT_008d0a90 != 0) && (UINT_008d0a90 = 0, UINT_008d0a98 != 0)) {
        (*(code *)UINT_008d0a98)();
      }
      SetFocus((int)g_pWinMainHwnd);
    }
    else {
      if ((((UINT_008d09dc == 1) && (UINT_008d0a8c != 0)) && (g_dwZg_App_bAppActive != 0)) &&
         (UINT_008d0a90 == 0)) {
        bVar6 = a4 != 0;
        local_8 = 0;
        a4 = 1;
        if (bVar6) {
          GetWindowThreadProcessId(a1_00,(int)&a4);
          GetWindowThreadProcessId(a1,(int)&local_8);
        }
        if ((local_8 == a4) && (UINT_008d0a90 = 1, UINT_008d0a94 != 0)) {
          (*(code *)UINT_008d0a94)();
        }
      }
      UINT_008d0a6c = 0;
    }
    break;
  case 0x1c:
    g_dwZg_App_bAppActive = (uint)(a3 != 0);
  }
  if ((g_dwZg_App_bAppActive == 0) || (_DAT_008d0a68 = 1, UINT_008d0a6c == 0)) {
    _DAT_008d0a68 = 0;
  }
  if ((bVar1) && (iVar3 = 0, 0 < (int)UINT_008d0a7c)) {
    ppvVar4 = &g_pWinMessageHooks;
    do {
      if ((ppvVar4[1] != (void *)0x0) && (iVar5 = (*(code *)*ppvVar4)(a1,a2,a3,a1_00,&local_4), iVar5 != 0))
      {
        return local_4;
      }
      iVar3 = iVar3 + 1;
      ppvVar4 = ppvVar4 + 2;
    } while (iVar3 < (int)UINT_008d0a7c);
  }
  if (iVar5 == 0) {
    puVar2 = (undefined *)DefWindowProcA(a1,a2,a3,a1_00);
    return puVar2;
  }
  return (undefined *)0x1;
}
#undef local_4
#undef local_8


/* ---- 0x004bff70  Win_IsFocusWithin ---- */
/* True when the focused window is hwnd or one of its descendants */

int __cdecl Win_IsFocusWithin(void *hwnd)

{
  void *a1;
  int iVar1;
  
  a1 = (void *)GetFocus();
  iVar1 = 0;
  if (a1 != (void *)0x0) {
    while (a1 != hwnd) {
      a1 = (void *)GetParent((int)a1);
      if (a1 == (void *)0x0) {
        return 0;
      }
    }
    iVar1 = 1;
  }
  return iVar1;
}
