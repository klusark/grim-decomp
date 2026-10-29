/* GRIMFANDANGO.EXE :: window.c
 * functions 0x00401010 .. 0x004bff70 (14 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00401010  Win_WinMain ---- */
/* WinMain: the real program entry after the MSVC CRT start-up (entry at 0x4aca30) */

undefined4 __stdcall Win_WinMain(int a1,int a2,int a3,int a4)

{
  Win_Main((void *)a1,(void *)a2,(char *)a3,a4,s_Grim_Fandango_004dd404);
  return 0;
}

/* ---- 0x00402fd0  Win_WndProc ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* grimdemo.c window procedure. WM_ACTIVATEAPP pauses/resumes the engine, WM_KEYDOWN handles the
   Backspace-chord debug keys (C choreface, F fps, P profile, S screenshot, T reset textures, Z
   z-buffer dump, F12 grimpatch.bin, NumLock spew). */

uint Win_WndProc(undefined4 param_1,uint param_2,int param_3)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  short sVar3;
  int iVar4;
  #define local_40 (*(char (*)[64])(_frame + (0x50 - 0x40)))
  
  iVar4 = DAT_004f5a94;
  iVar1 = DAT_004f5a90;
  if (0x10 < param_2) {
    if (param_2 < 0x1d) {
      if (param_2 == 0x1c) {
        if ((param_3 == 0) && (DAT_004dd38c != 0)) {
          if (DAT_004f5a20 == 0) {
            Engine_SetPaused(1);
            Grim_ShutdownDisplay();
            iVar4 = 6;
            iVar1 = Win_GetMainHwnd();
            ShowWindow(iVar1,iVar4);
          }
          Input_SetAcquired(0);
          DAT_004dd38c = 0;
          return 0;
        }
        if (param_3 == 0) {
          return 0;
        }
        if (DAT_004dd38c != 0) {
          return 0;
        }
        if (DAT_004f5a20 == 0) {
          Engine_SetPaused(0);
          iVar4 = 9;
          iVar1 = Win_GetMainHwnd();
          ShowWindow(iVar1,iVar4);
          Display_InitFromConfig();
        }
        DAT_004dd38c = 1;
        Input_SetAcquired(1);
        Render_RequestFullRedraw();
        Input_ShowCursor(DAT_004f5a20);
        return 0;
      }
      if (param_2 == 0x14) {
        return 1;
      }
    }
    else if (param_2 < 0x101) {
      if (param_2 == 0x100) {
        switch(param_3) {
        case 8:
          if (g_nDebugKeysEnabled != 0) {
            DAT_004f5a88 = 1;
            return 0;
          }
          break;
        case 0x13:
          Lua_CallPauseHandler();
          return 1;
        case 0x43:
          if (DAT_004f5a88 != 0) {
            ChoreFace_Toggle(1);
            return 1;
          }
          break;
        case 0x46:
          if (DAT_004f5a88 != 0) {
            _g_bShowFps = (uint)(_g_bShowFps == 0);
            return 1;
          }
          break;
        case 0x50:
          if (DAT_004f5a88 != 0) {
            DAT_004f5a30 = (uint)(DAT_004f5a30 == 0);
            return 1;
          }
          break;
        case 0x53:
          if (DAT_004f5a88 != 0) {
            DAT_004f5a90 = DAT_004f5a90 + 1;
            ((code *)sprintf)(local_40,s__s_d_bmp_004dd928,&DAT_004dd934,iVar1);
            Render_SaveScreenshotBmp(local_40);
            return 0;
          }
          break;
        case 0x54:
          if (DAT_004f5a88 != 0) {
            D3D_ResetTextures();
            return 1;
          }
          break;
        case 0x5a:
          if (DAT_004f5a88 != 0) {
            DAT_004f5a94 = DAT_004f5a94 + 1;
            ((code *)sprintf)(local_40,s__s_d_zbm_004dd91c,&DAT_004dd934,iVar4);
            Render_SaveZBufferBmp(local_40);
            return 0;
          }
          break;
        case 0x7b:
          iVar1 = GetKeyState(8);
          if ((short)iVar1 != 0) {
            lua_dofile(s_grimpatch_bin_004dd93c);
            return 1;
          }
          break;
        case 0x90:
          Spew_Startup();
          return 1;
        }
      }
      else if ((param_2 == 0x20) && (DAT_004f5a20 == 0)) {
        SetCursor(0);
        return 1;
      }
    }
    else if (param_2 < 0x219) {
      if (param_2 == 0x218) {
        if (param_3 == 0) {
          return 0;
        }
      }
      else {
        switch(param_2) {
        case 0x101:
          if (param_3 == 8) {
            DAT_004f5a88 = 0;
            return 0;
          }
          if ((param_3 == 0x43) && (DAT_004f5a88 != 0)) {
            return 1;
          }
          break;
        case 0x102:
          uVar2 = Engine_CallCharacterHandler(param_3);
          return uVar2;
        case 0x104:
          return 1;
        case 0x105:
          goto switchD_0040336f_caseD_105;
        }
      }
    }
    return 0;
  }
  if (param_2 == 0x10) {
    iVar1 = ChoreFace_Toggle(0);
    if (iVar1 != 0) {
      iVar1 = Win_GetMainHwnd();
      iVar1 = IsIconic(iVar1);
      if (iVar1 != 0) {
        return 0;
      }
      iVar1 = Engine_CallExitHandler();
      return (uint)(iVar1 == 0);
    }
switchD_0040336f_caseD_105:
    return 1;
  }
  if (param_2 != 6) {
    return 0;
  }
  if (DAT_008d0a70 == 0) {
    return 0;
  }
  sVar3 = (short)param_3;
  if (g_nInputEnabled != 0) {
    Input_SetAcquired((uint)(sVar3 != 0));
    if (sVar3 == 0) goto LAB_0040303f;
    Input_Flush();
    Input_ShowCursor(DAT_004f5a20);
  }
  if (sVar3 != 0) {
    return 0;
  }
LAB_0040303f:
  if ((DAT_004f5a20 == 0) && (DAT_004e814c != 0)) {
    iVar4 = 6;
    iVar1 = Win_GetMainHwnd();
    ShowWindow(iVar1,iVar4);
    return 0;
  }
  return 0;
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
void Win_SetInstance(undefined4 param_1)

{
  DAT_007f608c = param_1;
  return;
}

/* ---- 0x00473390  Win_GetInstance ---- */
/* Returns the HINSTANCE of the executable */

undefined4 Win_GetInstance(void)

{
  return DAT_007f608c;
}

/* ---- 0x004abf40  Win_Main ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WinMain body (grimplat.cpp): aborts if a wKernel window already exists, then Grim_Init,
   Win_CreateMainWindow and the message pump */

void __cdecl Win_Main(void *hInstance,void *hPrevInstance,char *cmdLine,int nCmdShow,char *appName)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FindWindowA(IMG_ADDR(0x004ed080),(int)appName);
  if (iVar1 != 0) {
    SetForegroundWindow(iVar1);
    ShowWindow(iVar1,9);
    exit(0xffffffff);
  }
  DAT_008d0a7c = 0;
  g_dwWinDialogCount = 0;
  g_nWinQuit = 0;
  DAT_008d0a8c = 0;
  DAT_008d09e4 = hInstance;
  _DAT_008d09e0 = nCmdShow;
  Win_CreateMainWindow(hInstance,nCmdShow,appName);
  Win_SetMainHwnd(g_pWinMainHwnd);
  Win_SetInstance(DAT_008d09e4);
  InitCommonControls();
  iVar1 = GetSystemMetrics(0x20);
  DAT_008d0a84 = iVar1 << 1;
  iVar1 = GetSystemMetrics(0x20);
  iVar2 = GetSystemMetrics(0xf);
  DAT_008d0a88 = iVar2 + iVar1 * 2;
  iVar1 = Grim_Init(cmdLine);
  if (iVar1 != 0) {
    DAT_008d0a8c = 1;
    do {
      Win_PumpMessages();
    } while (g_nWinQuit == 0);
  }
  return;
}

/* ---- 0x004ac020  Win_PumpMessages ---- */
/* One message-loop iteration: runs Game_FrameUpdate when idle, routes messages to registered
   dialogs */

undefined4 Win_PumpMessages(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  void **ppvVar3;
  #define local_1c (*(undefined1 (*)[8])(_frame + (0x30 - 0x1c)))
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  
  iVar1 = PeekMessageA((int)local_1c,0,0,0,0);
  if (iVar1 == 0) {
    Game_FrameUpdate();
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
  DAT_008d09dc = fullscreen;
  if (fullscreen == 0) {
    SetWindowLongA((int)g_pWinMainHwnd,-0x10,0x10cf0000);
    SetWindowPos((int)g_pWinMainHwnd,0,0,0,w + DAT_008d0a84,h + DAT_008d0a88,6);
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
  } while ((int)piVar1 < IMG_ADDR(0x008d0a6c));
  (&g_pWinMessageHooks)[iVar2 * 2] = param_1;
  (&g_nWinMessageHookOn)[iVar2 * 2] = 1;
  DAT_008d0a7c = DAT_008d0a7c + 1;
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
  } while ((int)ppvVar1 < IMG_ADDR(0x008d0a68));
  (&g_pWinMessageHooks)[iVar2 * 2] = (void *)0x0;
  (&g_nWinMessageHookOn)[iVar2 * 2] = 0;
  DAT_008d0a7c = DAT_008d0a7c + -1;
  return 1;
}

/* ---- 0x004ac1f0  Win_CreateMainWindow ---- */
undefined4 Win_CreateMainWindow(int param_1,undefined4 param_2,int param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int a8;
  int a7;
  int a9;
  int a10;
  int a12;
  #define local_30 (*(undefined4 *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(undefined4 *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(code **)(_frame + (0x40 - 0x28)))
  #define local_24 (*(undefined4 *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(undefined4 *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(int *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(int *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(int *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(int *)(_frame + (0x40 - 0x10)))
  #define local_c (*(undefined4 *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(char **)(_frame + (0x40 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x40 - 0x4)))
  
  local_30 = 0x30;
  local_1c = param_1;
  local_8 = s_wKernel_004ed080;
  local_c = 0;
  local_28 = Win_KernelWndProc;
  local_2c = 3;
  local_18 = LoadIconA(param_1,IMG_ADDR(0x004ed088));
  if (local_18 == 0) {
    local_18 = LoadIconA(0,0x7f00);
  }
  local_4 = LoadIconA(param_1,IMG_ADDR(0x004ed088));
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
  iVar1 = FindWindowA(IMG_ADDR(0x004ed080),param_3);
  if (iVar1 != 0) {
    exit(0xffffffff);
  }
  a12 = 0;
  a10 = 0;
  a9 = 0;
  iVar1 = param_1;
  a8 = GetSystemMetrics(1);
  a7 = GetSystemMetrics(0);
  g_pWinMainHwnd =
       (void *)CreateWindowExA(0x40000,IMG_ADDR(0x004ed080),param_3,-0x70000000,0,0,a7,a8,a9,a10,iVar1,a12);
  if (g_pWinMainHwnd == (void *)0x0) {
    return 0;
  }
  DAT_008d09e4 = param_1;
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


/* ---- 0x004ac340  Win_KernelWndProc ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Window procedure of the wKernel window class; forwards to the registered message hooks
   (Win_WndProc) */

int __stdcall Win_KernelWndProc(int a1,int a2,int a3,int a4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  int iVar2;
  int iVar3;
  void **ppvVar4;
  int iVar5;
  bool bVar6;
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  iVar2 = a4;
  iVar5 = 0;
  bVar1 = true;
  switch(a2) {
  case 1:
    DAT_008d0a70 = 0;
    DAT_008d0a6c = 0;
    break;
  case 2:
    DAT_008d0a8c = 0;
    Grim_Shutdown();
    PostQuitMessage(0);
    bVar1 = false;
    break;
  case 6:
    if (((short)a3 == 2) || ((short)a3 == 1)) {
      DAT_008d0a6c = 1;
      if ((DAT_008d0a90 != 0) && (DAT_008d0a90 = 0, DAT_008d0a98 != (code *)0x0)) {
        (*DAT_008d0a98)();
      }
      SetFocus((int)g_pWinMainHwnd);
    }
    else {
      if ((((DAT_008d09dc == 1) && (DAT_008d0a8c != 0)) && (DAT_008d0a70 != 0)) &&
         (DAT_008d0a90 == 0)) {
        bVar6 = a4 != 0;
        local_8 = 0;
        a4 = 1;
        if (bVar6) {
          GetWindowThreadProcessId(iVar2,(int)&a4);
          GetWindowThreadProcessId(a1,(int)&local_8);
        }
        if ((local_8 == a4) && (DAT_008d0a90 = 1, DAT_008d0a94 != (code *)0x0)) {
          (*DAT_008d0a94)();
        }
      }
      DAT_008d0a6c = 0;
    }
    break;
  case 0x1c:
    DAT_008d0a70 = (uint)(a3 != 0);
  }
  if ((DAT_008d0a70 == 0) || (_DAT_008d0a68 = 1, DAT_008d0a6c == 0)) {
    _DAT_008d0a68 = 0;
  }
  if ((bVar1) && (iVar3 = 0, 0 < DAT_008d0a7c)) {
    ppvVar4 = &g_pWinMessageHooks;
    do {
      if ((ppvVar4[1] != (void *)0x0) && (iVar5 = (*(code *)*ppvVar4)(a1,a2,a3,iVar2,&local_4), iVar5 != 0))
      {
        return local_4;
      }
      iVar3 = iVar3 + 1;
      ppvVar4 = ppvVar4 + 2;
    } while (iVar3 < DAT_008d0a7c);
  }
  if (iVar5 == 0) {
    iVar2 = DefWindowProcA(a1,a2,a3,iVar2);
    return iVar2;
  }
  return 1;
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
