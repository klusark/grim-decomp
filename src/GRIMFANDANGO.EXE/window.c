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

undefined * __cdecl Win_WndProc(uint hwnd,uint msg,int ch)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  void *pvVar3;
  undefined *puVar4;
  short sVar5;
  int iVar6;
  #define local_40 (*(char (*)[64])(_frame + (0x50 - 0x40)))
  
  uVar2 = UINT_004f5a94;
  uVar1 = UINT_004f5a90;
  if (0x10 < msg) {
    if (msg < 0x1d) {
      if (msg == 0x1c) {
        if ((ch == 0) && (INT_004dd38c != 0)) {
          if (g_bWindowedMode == 0) {
            grimlib_SetPause(1);
            Grim_ShutdownDisplay();
            iVar6 = 6;
            pvVar3 = Win_GetMainHwnd();
            ShowWindow((int)pvVar3,iVar6);
          }
          Input_SetAcquired(0);
          INT_004dd38c = 0;
          return (undefined *)0x0;
        }
        if (ch == 0) {
          return (undefined *)0x0;
        }
        if (INT_004dd38c != 0) {
          return (undefined *)0x0;
        }
        if (g_bWindowedMode == 0) {
          grimlib_SetPause(0);
          iVar6 = 9;
          pvVar3 = Win_GetMainHwnd();
          ShowWindow((int)pvVar3,iVar6);
          Display_InitFromConfig();
        }
        INT_004dd38c = 1;
        Input_SetAcquired(1);
        sputRender_ForceRefresh();
        stdControl_ShowMouseCursor(g_bWindowedMode);
        return (undefined *)0x0;
      }
      if (msg == 0x14) {
        return (undefined *)0x1;
      }
    }
    else if (msg < 0x101) {
      if (msg == 0x100) {
        switch(ch) {
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
            sprintf(local_40,s__s_d_bmp_004dd928,s_shot_004dd934,uVar1);
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
            sprintf(local_40,s__s_d_zbm_004dd91c,s_shot_004dd934,uVar2);
            Render_SaveZBufferBmp(local_40);
            return (undefined *)0x0;
          }
          break;
        case 0x7b:
          iVar6 = GetKeyState(8);
          if ((short)iVar6 != 0) {
            lua_dofile(s_grimpatch_bin_004dd93c);
            return (undefined *)0x1;
          }
          break;
        case 0x90:
          Spew_Startup();
          return (undefined *)0x1;
        }
      }
      else if ((msg == 0x20) && (g_bWindowedMode == 0)) {
        SetCursor(0);
        return (undefined *)0x1;
      }
    }
    else if (msg < 0x219) {
      if (msg == 0x218) {
        if (ch == 0) {
          return (undefined *)0x0;
        }
      }
      else {
        switch(msg) {
        case 0x101:
          if (ch == 8) {
            g_bDebugChordHeld = 0;
            return (undefined *)0x0;
          }
          if ((ch == 0x43) && (g_bDebugChordHeld != 0)) {
            return (undefined *)0x1;
          }
          break;
        case 0x102:
          puVar4 = grimlib_CharacterCallback(ch);
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
  if (msg == 0x10) {
    iVar6 = ChoreFace_Toggle(0);
    if (iVar6 != 0) {
      pvVar3 = Win_GetMainHwnd();
      iVar6 = IsIconic((int)pvVar3);
      if (iVar6 != 0) {
        return (undefined *)0x0;
      }
      iVar6 = grimlib_ConfirmClose();
      return (undefined *)(uint)(iVar6 == 0);
    }
switchD_0040336f_caseD_105:
    return (undefined *)0x1;
  }
  if (msg != 6) {
    return (undefined *)0x0;
  }
  if (g_dwZg_App_bAppActive == 0) {
    return (undefined *)0x0;
  }
  sVar5 = (short)ch;
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
    pvVar3 = Win_GetMainHwnd();
    ShowWindow((int)pvVar3,iVar6);
    return (undefined *)0x0;
  }
  return (undefined *)0x0;
}
#undef local_40


/* ---- 0x00473360  Win_SetMainHwnd ---- */
void __cdecl Win_SetMainHwnd(void *hwnd)

{
  g_pMainHwnd = hwnd;
  return;
}

/* ---- 0x00473370  Win_GetMainHwnd ---- */
void * __cdecl Win_GetMainHwnd(void)

{
  return g_pMainHwnd;
}

/* ---- 0x00473380  Win_SetInstance ---- */
void __cdecl Win_SetInstance(uint hInstance)

{
  UINT_007f608c = hInstance;
  return;
}

/* ---- 0x00473390  Win_GetInstance ---- */
/* Returns the HINSTANCE of the executable */

uint __cdecl Win_GetInstance(void)

{
  return UINT_007f608c;
}

/* ---- 0x004772d0  Win_IsSysCommandBlocked ---- */
/* Window-message filter: true for WM_SYSCOMMAND with SC_KEYMENU (0xf100) or SC_SCREENSAVE (0xf140).
    */

uint __cdecl Win_IsSysCommandBlocked(uint hwnd,int cmd,int lParam)

{
  if (cmd != 0x112) {
    return 0;
  }
  if ((lParam != 0xf100) && (lParam != 0xf140)) {
    return 0;
  }
  return 1;
}

/* ---- 0x004abf40  Win_AbortIfAlreadyRunning ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WinMain helper: brings an existing 'wKernel' window to the front and exits */

void __cdecl
Win_AbortIfAlreadyRunning
          (void *hInstance,void *hPrevInstance,char *cmdLine,int nCmdShow,char *appName)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
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
  INT_008d09e0 = nCmdShow;
  Win_CreateMainWindow((uint)hInstance,nCmdShow,(int)appName);
  Win_SetMainHwnd(g_pWinMainHwnd);
  Win_SetInstance(UINT_008d09e4);
  InitCommonControls();
  iVar1 = GetSystemMetrics(0x20);
  UINT_008d0a84 = iVar1 << 1;
  iVar1 = GetSystemMetrics(0x20);
  iVar2 = GetSystemMetrics(0xf);
  UINT_008d0a88 = iVar2 + iVar1 * 2;
  uVar3 = Main_Startup(cmdLine);
  if (uVar3 != 0) {
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

uint __cdecl Win_PumpMessages(void)

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
void __cdecl Win_AddMessageHook(void *hook)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = &g_aWinMessageHooks[0].nOn;
  do {
    if (*piVar1 == 0) break;
    piVar1 = piVar1 + 2;
    iVar2 = iVar2 + 1;
  } while ((int)piVar1 < ((unsigned)(uintptr_t)&UINT_008d0a6c));
  g_aWinMessageHooks[iVar2].pHook = hook;
  g_aWinMessageHooks[iVar2].nOn = 1;
  UINT_008d0a7c = UINT_008d0a7c + 1;
  return;
}

/* ---- 0x004ac1a0  Win_RemoveMessageHook ---- */
undefined4 __cdecl Win_RemoveMessageHook(void *hook)

{
  WinMessageHook *pWVar1;
  int iVar2;
  
  iVar2 = 0;
  pWVar1 = g_aWinMessageHooks;
  do {
    if (pWVar1->pHook == hook) break;
    pWVar1 = pWVar1 + 1;
    iVar2 = iVar2 + 1;
  } while ((int)pWVar1 < ((unsigned)(uintptr_t)&DAT_008d0a68));
  g_aWinMessageHooks[iVar2].pHook = (code *)0x0;
  g_aWinMessageHooks[iVar2].nOn = 0;
  UINT_008d0a7c = UINT_008d0a7c - 1;
  return 1;
}

/* ---- 0x004ac1f0  Win_CreateMainWindow ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
uint __cdecl Win_CreateMainWindow(uint hInstance,uint title,int nCmdShow)

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
  local_1c = hInstance;
  local_8 = (uint)s_wKernel_004ed080;
  local_c = 0;
  local_28 = (uint)Win_KernelWndProc;
  local_2c = 3;
  local_18 = LoadIconA(hInstance,((unsigned)(uintptr_t)&s_APPICON_004ed088));
  if (local_18 == 0) {
    local_18 = LoadIconA(0,0x7f00);
  }
  local_4 = LoadIconA(hInstance,((unsigned)(uintptr_t)&s_APPICON_004ed088));
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
  iVar1 = FindWindowA(((unsigned)(uintptr_t)&s_wKernel_004ed080),nCmdShow);
  if (iVar1 != 0) {
    exit(0xffffffff);
  }
  a12 = 0;
  a10 = 0;
  a9 = 0;
  a11 = hInstance;
  iVar1 = GetSystemMetrics(1);
  a7 = GetSystemMetrics(0);
  g_pWinMainHwnd =
       (void *)CreateWindowExA(0x40000,((unsigned)(uintptr_t)&s_wKernel_004ed080),nCmdShow,-0x70000000,0,0,a7,iVar1,a9,a10,a11,a12);
  if (g_pWinMainHwnd == (void *)0x0) {
    return 0;
  }
  UINT_008d09e4 = hInstance;
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
  undefined uVar2;
  undefined3 extraout_var;
  undefined *puVar3;
  int iVar4;
  WinMessageHook *pWVar5;
  int iVar6;
  bool bVar7;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined **)(_frame + (0x20 - 0x4)))
  
  a1_00 = a4;
  iVar6 = 0;
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
        bVar7 = a4 != 0;
        local_8 = 0;
        a4 = 1;
        if (bVar7) {
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
  if ((bVar1) && (iVar4 = 0, 0 < (int)UINT_008d0a7c)) {
    pWVar5 = g_aWinMessageHooks;
    do {
      if (pWVar5->nOn != 0) {
        uVar2 = (*pWVar5->pHook)(a1,a2,a3,a1_00,&local_4);
        iVar6 = ((uint)(byte)(uVar2));
        if (iVar6 != 0) {
          return local_4;
        }
      }
      iVar4 = iVar4 + 1;
      pWVar5 = pWVar5 + 1;
    } while (iVar4 < (int)UINT_008d0a7c);
  }
  if (iVar6 == 0) {
    puVar3 = (undefined *)DefWindowProcA(a1,a2,a3,a1_00);
    return puVar3;
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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_008d0a68[4] __asm__("_DAT_008d0a68");
extern unsigned int grim_def_INT_004dd38c __asm__("_INT_004dd38c");
extern int grim_def_INT_008d09e0 __asm__("_INT_008d09e0");
extern unsigned int grim_def_UINT_004f5a90 __asm__("_UINT_004f5a90");
extern unsigned int grim_def_UINT_004f5a94 __asm__("_UINT_004f5a94");
extern unsigned int grim_def_UINT_007f608c __asm__("_UINT_007f608c");
extern int grim_def_UINT_008d09dc __asm__("_UINT_008d09dc");
extern unsigned int grim_def_UINT_008d09e4 __asm__("_UINT_008d09e4");
extern unsigned int grim_def_UINT_008d0a6c __asm__("_UINT_008d0a6c");
extern unsigned char grim_def_UINT_008d0a7c[8] __asm__("_UINT_008d0a7c");
extern unsigned int grim_def_UINT_008d0a84 __asm__("_UINT_008d0a84");
extern unsigned int grim_def_UINT_008d0a88 __asm__("_UINT_008d0a88");
extern unsigned int grim_def_UINT_008d0a8c __asm__("_UINT_008d0a8c");
extern unsigned int grim_def_UINT_008d0a90 __asm__("_UINT_008d0a90");
extern unsigned int grim_def_UINT_008d0a94 __asm__("_UINT_008d0a94");
extern unsigned int grim_def_UINT_008d0a98 __asm__("_UINT_008d0a98");
extern WinMessageHook grim_def_g_aWinMessageHooks[16] __asm__("_g_aWinMessageHooks");
extern int grim_def_g_bDebugChordHeld __asm__("_g_bDebugChordHeld");
extern unsigned int grim_def_g_dwWinDialogCount __asm__("_g_dwWinDialogCount");
extern int grim_def_g_nWinQuit __asm__("_g_nWinQuit");
extern unsigned char grim_def_g_pMainHwnd[4] __asm__("_g_pMainHwnd");
extern unsigned char grim_def_g_pWinDialogs[64] __asm__("_g_pWinDialogs");
extern unsigned char grim_def_g_pWinMainHwnd[4] __asm__("_g_pWinMainHwnd");
extern char grim_def_s_APPICON_004ed088[16] __asm__("_s_APPICON_004ed088");
extern char grim_def_s_Grim_Fandango_004dd404[16] __asm__("_s_Grim_Fandango_004dd404");
extern char grim_def_s__s_d_bmp_004dd928[12] __asm__("_s__s_d_bmp_004dd928");
extern char grim_def_s__s_d_zbm_004dd91c[12] __asm__("_s__s_d_zbm_004dd91c");
extern char grim_def_s_grimpatch_bin_004dd93c[16] __asm__("_s_grimpatch_bin_004dd93c");
extern char grim_def_s_shot_004dd934[8] __asm__("_s_shot_004dd934");
extern char grim_def_s_wKernel_004ed080[8] __asm__("_s_wKernel_004ed080");
/* 0x004dd38c, 4 bytes */ GRIM_DATA("004dd38c") unsigned int grim_def_INT_004dd38c __asm__("_INT_004dd38c") = 0x1;
/* 0x004dd404, 16 bytes */ GRIM_DATA("004dd404") char grim_def_s_Grim_Fandango_004dd404[16] __asm__("_s_Grim_Fandango_004dd404") = "Grim Fandango";
/* 0x004dd91c, 12 bytes */ GRIM_DATA("004dd91c") char grim_def_s__s_d_zbm_004dd91c[12] __asm__("_s__s_d_zbm_004dd91c") = "%s%d.zbm";
/* 0x004dd928, 12 bytes */ GRIM_DATA("004dd928") char grim_def_s__s_d_bmp_004dd928[12] __asm__("_s__s_d_bmp_004dd928") = "%s%d.bmp";
/* 0x004dd934, 8 bytes */ GRIM_DATA("004dd934") char grim_def_s_shot_004dd934[8] __asm__("_s_shot_004dd934") = "shot";
/* 0x004dd93c, 16 bytes */ GRIM_DATA("004dd93c") char grim_def_s_grimpatch_bin_004dd93c[16] __asm__("_s_grimpatch_bin_004dd93c") = "grimpatch.bin";
/* 0x004ed080, 8 bytes */ /* loose */ char grim_def_s_wKernel_004ed080[8] __asm__("_s_wKernel_004ed080") = "wKernel";
static unsigned char grim_anchor_004ed088[0] __attribute__((section(".data$grim_004ed088"), aligned(16), used));
static unsigned char grim_pad_004ed088[8] __attribute__((section(".data$grim_004ed088_"), aligned(4), used));
/* 0x004ed088, 16 bytes */ GRIM_DATA("004ed088z") char grim_def_s_APPICON_004ed088[16] __asm__("_s_APPICON_004ed088") = "APPICON\000u\230\000\000s\230";
static unsigned char grim_anchor_004f5a88[0] __attribute__((section(".data$grim_004f5a88"), aligned(16), used));
static unsigned char grim_pad_004f5a88[8] __attribute__((section(".data$grim_004f5a88_"), aligned(4), used));
/* 0x004f5a88, 8 bytes */ GRIM_DATA("004f5a88z") int grim_def_g_bDebugChordHeld __asm__("_g_bDebugChordHeld") = 0;
/* 0x004f5a8c, 4 bytes: the rest of grim_def_g_bDebugChordHeld's span */ GRIM_DATA("004f5a88z") static unsigned char g_bDebugChordHeld__tail[4] __attribute__((used)) = {0};
/* 0x004f5a90, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a90 __asm__("_UINT_004f5a90") = 0x0;
static unsigned char grim_anchor_004f5a94[0] __attribute__((section(".data$grim_004f5a94"), aligned(16), used));
static unsigned char grim_pad_004f5a94[4] __attribute__((section(".data$grim_004f5a94_"), aligned(4), used));
/* 0x004f5a94, 4 bytes */ GRIM_DATA("004f5a94z") unsigned int grim_def_UINT_004f5a94 __asm__("_UINT_004f5a94") = 0x0;
/* 0x007f6088, 4 bytes */ GRIM_DATA("007f6088") unsigned char grim_def_g_pMainHwnd[4] __asm__("_g_pMainHwnd") = {0};
/* 0x007f608c, 4 bytes */ GRIM_DATA("007f608c") unsigned int grim_def_UINT_007f608c __asm__("_UINT_007f608c") = 0x0;
/* 0x008d0998, 64 bytes */ GRIM_DATA("008d0998") unsigned char grim_def_g_pWinDialogs[64] __asm__("_g_pWinDialogs") = {0};
/* 0x008d09d8, 4 bytes */ GRIM_DATA("008d09d8") unsigned char grim_def_g_pWinMainHwnd[4] __asm__("_g_pWinMainHwnd") = {0};
/* 0x008d09dc, 4 bytes */ GRIM_DATA("008d09dc") int grim_def_UINT_008d09dc __asm__("_UINT_008d09dc") = 0;
/* 0x008d09e0, 4 bytes */ GRIM_DATA("008d09e0") int grim_def_INT_008d09e0 __asm__("_INT_008d09e0") = 0;
/* 0x008d09e4, 4 bytes */ GRIM_DATA("008d09e4") unsigned int grim_def_UINT_008d09e4 __asm__("_UINT_008d09e4") = 0x0;
/* 0x008d09e8, 128 bytes */ GRIM_DATA("008d09e8") WinMessageHook grim_def_g_aWinMessageHooks[16] __asm__("_g_aWinMessageHooks") = {0};
/* 0x008d0a68, 4 bytes */ GRIM_DATA("008d0a68") unsigned char grim_def_DAT_008d0a68[4] __asm__("_DAT_008d0a68") = {0};
/* 0x008d0a6c, 4 bytes */ GRIM_DATA("008d0a6c") unsigned int grim_def_UINT_008d0a6c __asm__("_UINT_008d0a6c") = 0x0;
/* 0x008d0a74, 4 bytes */ GRIM_DATA("008d0a74") int grim_def_g_nWinQuit __asm__("_g_nWinQuit") = 0;
/* 0x008d0a78, 4 bytes */ GRIM_DATA("008d0a78") unsigned int grim_def_g_dwWinDialogCount __asm__("_g_dwWinDialogCount") = 0x0;
/* 0x008d0a7c, 8 bytes */ GRIM_DATA("008d0a7c") unsigned char grim_def_UINT_008d0a7c[8] __asm__("_UINT_008d0a7c") = {0};
/* 0x008d0a84, 4 bytes */ GRIM_DATA("008d0a84") unsigned int grim_def_UINT_008d0a84 __asm__("_UINT_008d0a84") = 0x0;
/* 0x008d0a88, 4 bytes */ GRIM_DATA("008d0a88") unsigned int grim_def_UINT_008d0a88 __asm__("_UINT_008d0a88") = 0x0;
/* 0x008d0a8c, 4 bytes */ GRIM_DATA("008d0a8c") unsigned int grim_def_UINT_008d0a8c __asm__("_UINT_008d0a8c") = 0x0;
/* 0x008d0a90, 4 bytes */ GRIM_DATA("008d0a90") unsigned int grim_def_UINT_008d0a90 __asm__("_UINT_008d0a90") = 0x0;
/* 0x008d0a94, 4 bytes */ GRIM_DATA("008d0a94") unsigned int grim_def_UINT_008d0a94 __asm__("_UINT_008d0a94") = 0x0;
/* 0x008d0a98, 4 bytes */ GRIM_DATA("008d0a98") unsigned int grim_def_UINT_008d0a98 __asm__("_UINT_008d0a98") = 0x0;
__asm__(".globl _grim_img_exe_0x004ed080\n\t.set _grim_img_exe_0x004ed080, _s_wKernel_004ed080 + 0\n");
__asm__(".globl _grim_img_exe_0x004ed088\n\t.set _grim_img_exe_0x004ed088, _s_APPICON_004ed088 + 0\n");
