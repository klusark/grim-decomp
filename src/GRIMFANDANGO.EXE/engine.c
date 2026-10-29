/* GRIMFANDANGO.EXE :: engine.c
 * functions 0x00482460 .. 0x0048d1c0 (45 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00482460  Engine_ResetState ---- */
/* Called when nuking resources and before a restore */

void Engine_ResetState(void)

{
  int *piVar1;
  int *res;
  int *res_00;
  
  res = PTR_008a85d4;
  res_00 = PTR_008a85d4;
  if (PTR_008a85d4 != (int *)0x0) {
    do {
      piVar1 = (int *)*res_00;
      if ((*(byte *)(res_00 + 7) & 8) == 0) {
        Res_CallUnload(res_00);
        Res_Unlink(res_00);
        res = PTR_008a85d4;
      }
      res_00 = piVar1;
    } while (piVar1 != (int *)0x0);
    while (res != (int *)0x0) {
      Res_CallUnload(res);
      Res_Unlink(PTR_008a85d4);
      res = PTR_008a85d4;
    }
  }
  return;
}

/* ---- 0x00482530  Engine_OpenResourceLog ---- */
void Engine_OpenResourceLog(undefined4 param_1)

{
  Resource_OpenLog(param_1);
  return;
}

/* ---- 0x004825c0  Engine_PushSelectedActorCostume ---- */
void Engine_PushSelectedActorCostume(int param_1)

{
  if (g_pSelectedActor != (void *)0x0) {
    Lua_CallCostumeOverrideHandler(g_pSelectedActor,1);
    Actor_PushCostume(g_pSelectedActor,(char *)0x0,param_1);
  }
  return;
}

/* ---- 0x004825f0  Engine_PopSelectedActorCostume ---- */
void Engine_PopSelectedActorCostume(void)

{
  if (g_pSelectedActor != (void *)0x0) {
    Lua_CallCostumeOverrideHandler(g_pSelectedActor,0);
    Actor_PopCostume(g_pSelectedActor,0);
  }
  return;
}

/* ---- 0x00482620  Engine_OpenRenderer ---- */
int __cdecl Engine_OpenRenderer(void *mode,int flags)

{
  Render_SetBufferCount(UINT_00803fa0);
  Render_Open(mode,flags,0,0,*(int *)((int)mode + 0xc) + -1,*(int *)((int)mode + 0x10) + -1,
              &DAT_004e7da0);
  return 0;
}

/* ---- 0x00482660  Engine_CloseRenderer ---- */
undefined4 Engine_CloseRenderer(void)

{
  Render_Close();
  return 0;
}

/* ---- 0x004826e0  Engine_ShutdownGame ---- */
/* Releases input, the renderer and the current set */

void Engine_ShutdownGame(void)

{
  if (UINT_008a8c78 != 0) {
    UINT_008a8c40 = 0;
    Control_Release();
    Render_Close();
    Set_SetCurrent((void *)0x0);
    UINT_008a8c78 = 0;
  }
  return;
}

/* ---- 0x00482720  Engine_SetDebugKeysCallback ---- */
void Engine_SetDebugKeysCallback(undefined4 param_1)

{
  Lua_SetDebugKeysCallback(param_1);
  return;
}

/* ---- 0x00482730  Engine_SetRenderUserCallback ---- */
void Engine_SetRenderUserCallback(undefined4 param_1)

{
  Render_SetUserCallback(param_1);
  return;
}

/* ---- 0x00482740  Engine_SetIdleCallback ---- */
void Engine_SetIdleCallback(uint param_1)

{
  UINT_008a8c70 = param_1;
  return;
}

/* ---- 0x00482750  Engine_SetFlipCallback ---- */
void Engine_SetFlipCallback(undefined4 param_1)

{
  Render_SetFlipCallback(param_1);
  return;
}

/* ---- 0x00482760  Engine_SetZBufferEnabled ---- */
void Engine_SetZBufferEnabled(undefined4 param_1)

{
  Render_SetZBufferEnabled(param_1);
  return;
}

/* ---- 0x00482770  Engine_SetExtraDataDir ---- */
void Engine_SetExtraDataDir(char *param_1)

{
  Resource_SetExtraDataDir(param_1);
  return;
}

/* ---- 0x00482790  Engine_RunSystemScript ---- */
bool Engine_RunSystemScript(void)

{
  int iVar1;
  
  iVar1 = Lua_RunSystemScript();
  return iVar1 == 0;
}

/* ---- 0x004827a0  Engine_CallSystemFunction ---- */
undefined4 Engine_CallSystemFunction(int param_1,char *param_2)

{
  int iVar1;
  undefined *puVar2;
  
  if (UINT_008a8c78 != 0) {
    return 1;
  }
  iVar1 = Lua_CallSystemFunction(param_1,param_2);
  if (iVar1 == 0) {
    return 1;
  }
  UINT_008a8c40 = 2;
  Engine_CreateCameraActor();
  puVar2 = Control_Capture();
  if (puVar2 == (undefined *)0x0) {
    return 1;
  }
  UINT_008a8c78 = 1;
  return 0;
}

/* ---- 0x00482800  Engine_InvalidateRect ---- */
void Engine_InvalidateRect(int *param_1,int param_2)

{
  Render_InvalidateRectLastBuffer(param_1,param_2);
  return;
}

/* ---- 0x004828d0  Engine_CallExitHandler ---- */
bool Engine_CallExitHandler(void)

{
  int iVar1;
  
  iVar1 = Lua_CallExitHandler();
  return iVar1 == 0;
}

/* ---- 0x004828e0  Engine_Quit ---- */
/* Lua exit() */

void __cdecl Engine_Quit(int exitCode)

{
  if (UINT_008a8c70 != 0) {
    (*(code *)UINT_008a8c70)(exitCode);
  }
  return;
}

/* ---- 0x00482900  Engine_SetPaused ---- */
/* Lua EnginePause/EngineResume and WM_ACTIVATEAPP use this to freeze the engine clock */

void __cdecl Engine_SetPaused(int paused)

{
  if (UINT_008a8c40 != 0) {
    if (paused != 0) {
      if (UINT_008a8c40 != 1) {
        UINT_008a8c90 = UINT_008a8c40;
        UINT_008a8c94 = UINT_008a8c44;
        UINT_008a8c40 = 1;
        ImPause();
        Movie_SetPaused(1);
        return;
      }
      if (paused != 0) {
        return;
      }
    }
    if (UINT_008a8c40 == 1) {
      UINT_008a8c40 = UINT_008a8c90;
      UINT_008a8c44 = UINT_008a8c94;
      ImResume();
      Movie_SetPaused(0);
    }
  }
  return;
}

/* ---- 0x00482980  Engine_CallCharacterHandler ---- */
undefined * __cdecl Engine_CallCharacterHandler(int param_1)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)Lua_CallCharacterHandler(param_1);
  return puVar1;
}

/* ---- 0x00482990  Engine_UpdateFrame ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Engine_UpdateFrame(draw, fixedMs). Runs the frame: sound (SoundsPeriodic), then the timer
   (Timer_UpdateFromWallClock when fixedMs==0, Timer_UpdateFixedStep(fixedMs) otherwise), the Lua
   tasks (FUN_0049c8f0) and the actor update (FUN_0048fcf0 with the frame seconds). */

void Engine_UpdateFrame(int param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  float fVar2;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  if (UINT_008a8c7c != 0) {
    Engine_SaveGame();
  }
  if (UINT_008a8c80 != 0) {
    Engine_LoadGame();
  }
  Profile_Begin(0);
  Profile_Begin(10);
  SoundsPeriodic();
  Profile_End(10);
  if (UINT_008a8c40 != 0) {
    Profile_Begin(1);
    uVar1 = Timer_GetFrameMs();
    fVar2 = Timer_GetFrameSeconds();
    ((code *)Engine_RunShutdownHooks)(fVar2,uVar1);
    Profile_End(1);
    if ((UINT_008a8c40 != 1) || (param_2 != 0)) {
      UINT_008a8c3c = UINT_008a8c3c + 1;
      if (param_2 == 0) {
        Timer_UpdateFromWallClock();
      }
      else {
        Timer_UpdateFixedStep(param_2);
      }
      if (UINT_004e7d98 != 0) {
        Profile_Begin(2);
        Lua_UpdateFrame();
        Profile_End(2);
      }
      if ((UINT_008a8c40 != 3) && (UINT_008a8c40 != 4)) {
        Profile_Begin(3);
        fVar2 = Timer_GetFrameSeconds();
        Actors_UpdateAll(fVar2);
        Profile_End(3);
      }
    }
    if ((param_1 != 0) && ((UINT_008a8c40 != 1 || (param_2 != 0)))) {
      Engine_RenderFrame();
      UINT_008a8c60 = 1;
    }
    Profile_End(0);
    if (UINT_004e7e30 != 0xffffffff) {
      ImSetState(UINT_004e7e30);
      UINT_004e7e30 = 0xffffffff;
    }
  }
  return;
}
#undef local_8
#undef local_c


/* ---- 0x00482ae0  Engine_SetIMuseState ---- */
/* Lua ImSetState */

void __cdecl Engine_SetIMuseState(int state)

{
  UINT_004e7e30 = state;
  return;
}

/* ---- 0x00482af0  Engine_PresentFrame ---- */
/* Profile slot 8: presents the back buffer when the game state is 3 */

void Engine_PresentFrame(void)

{
  int iVar1;
  
  Profile_Begin(8);
  if (UINT_008a8c40 == 3) {
    iVar1 = Render_CanvasIsPaletted();
    if (iVar1 == 0) {
      Render_Present();
      Profile_End(8);
      return;
    }
  }
  else {
    if (UINT_008a8c40 == 2) {
      Render_Present();
      Profile_End(8);
      return;
    }
    if ((UINT_008a8c40 == 1) && (UINT_008a8c60 != 0)) {
      Render_Present();
      UINT_008a8c60 = 0;
    }
  }
  Profile_End(8);
  return;
}

/* ---- 0x00482b60  FUN_00482b60 ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * FUN_00482b60(void)

{
  undefined *puVar1;
  
  g_pSvcEngineModule = (GrimServices *)0x0;
  puVar1 = (undefined *)0x0;
  if (UINT_008a8c58 != 0) {
    Engine_ResetSubsystems(&DAT_008a8778,6);
    puVar1 = (undefined *)Engine_ResetSubsystems(&DAT_008a85f0,8);
    UINT_008a8c58 = 0;
  }
  return puVar1;
}

/* ---- 0x00482ba0  FUN_00482ba0 ---- */
int FUN_00482ba0(void)

{
  int iVar1;
  uint budget;
  
  if (UINT_008a8c5c != 0) {
    return 1;
  }
  iVar1 = Engine_InitSubsystems(&DAT_008a85f0,8);
  if (iVar1 == 0) {
    iVar1 = DSound_Init();
    if (iVar1 == 0) {
      return 1;
    }
    iVar1 = Plat_GetPhysicalMemory();
    if (iVar1 < 0x1000001) {
      iMUSE_DeclareBufferSizes
                (88000,44000,88000,440000,44000,0x55f00,100000,1,0xac44,2,300000,6,150000);
      budget = 0xa00000;
    }
    else {
      iMUSE_DeclareBufferSizes
                (88000,44000,88000,440000,44000,0x55f00,100000,1,0xac44,2,300000,9,150000);
      iVar1 = Plat_GetPhysicalMemory();
      budget = UINT_004e7b20;
      if (iVar1 + -0x800000 <= (int)UINT_004e7b20) {
        iVar1 = Plat_GetPhysicalMemory();
        budget = iVar1 - 0x800000;
      }
    }
    Resource_SetMemoryUsage(budget,0);
    Sounds_PlatformDevice(g_pDirectSound);
    iVar1 = Engine_InitSubsystems(&DAT_008a8778,6);
  }
  UINT_008a8c5c = (uint)(iVar1 == 0);
  return iVar1;
}

/* ---- 0x00482cc0  FUN_00482cc0 ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * FUN_00482cc0(void)

{
  undefined *puVar1;
  
  Engine_ShutdownSubsystems(&DAT_008a8778,6);
  DSound_Shutdown();
  puVar1 = (undefined *)Engine_ShutdownSubsystems(&DAT_008a85f0,8);
  UINT_008a8c5c = 0;
  return puVar1;
}

/* ---- 0x00482cf0  Engine_RegisterSubsystems ---- */
/* Walks the {fn,name} subsystem table and calls each init, stopping at the first failure */

uint Engine_RegisterSubsystems(undefined4 param_1,undefined4 *param_2,int param_3,int param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar3 = 0;
  local_4 = 0;
  iVar2 = param_3;
  if (0 < param_4) {
    while (iVar1 = (*(code *)*param_2)(param_1,iVar2), iVar1 == 0) {
      iVar3 = iVar3 + 1;
      param_2 = param_2 + 2;
      iVar2 = iVar2 + 0x20;
      if (param_4 <= iVar3) {
        return 0;
      }
    }
    if (-1 < iVar3 + -1) {
      puVar4 = (undefined4 *)((iVar3 + -1) * 0x20 + 4 + param_3);
      do {
        if ((code *)*puVar4 != (code *)0x0) {
          (*(code *)*puVar4)();
        }
        puVar4 = puVar4 + -8;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    local_4 = 1;
  }
  return local_4;
}
#undef local_4


/* ---- 0x00482d60  Engine_InitSubsystems ---- */
undefined4 Engine_InitSubsystems(int param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = 0;
  if (param_2 < 1) {
    return 0;
  }
  puVar3 = (undefined4 *)(param_1 + 8);
  while (((code *)*puVar3 == (code *)0x0 || (iVar1 = (*(code *)*puVar3)(), iVar1 == 0))) {
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 8;
    if (param_2 <= iVar2) {
      return 0;
    }
  }
  if (-1 < iVar2 + -1) {
    puVar3 = (undefined4 *)((iVar2 + -1) * 0x20 + 0xc + param_1);
    do {
      if ((code *)*puVar3 != (code *)0x0) {
        (*(code *)*puVar3)();
      }
      puVar3 = puVar3 + -8;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return 1;
}
#undef local_4


/* ---- 0x00482dd0  Engine_ShutdownSubsystems ---- */
/* Calls the +0xc entry of each 0x20-byte subsystem record in reverse order */

undefined4 Engine_ShutdownSubsystems(int param_1,int param_2)

{
  undefined4 *puVar1;
  
  if (-1 < param_2 + -1) {
    puVar1 = (undefined4 *)((param_2 + -1) * 0x20 + 0xc + param_1);
    do {
      if ((code *)*puVar1 != (code *)0x0) {
        (*(code *)*puVar1)();
      }
      puVar1 = puVar1 + -8;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return 0;
}

/* ---- 0x00482e00  Engine_ResetSubsystems ---- */
/* Calls the +4 entry of each 0x20-byte subsystem record in reverse order */

undefined4 Engine_ResetSubsystems(int param_1,int param_2)

{
  undefined4 *puVar1;
  
  if (-1 < param_2 + -1) {
    puVar1 = (undefined4 *)((param_2 + -1) * 0x20 + 4 + param_1);
    do {
      if ((code *)*puVar1 != (code *)0x0) {
        (*(code *)*puVar1)();
      }
      puVar1 = puVar1 + -8;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return 0;
}

/* ---- 0x00482e30  Profile_Begin ---- */
/* Source: Main/sputmain.cpp (line 1453, from __FILE__/__LINE__ passed to the allocator) */

void Profile_Begin(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(longlong *)(_frame + (0x20 - 0x8)))
  
  if ((param_1 < 0) || (0xc < param_1)) {
    (*g_pSvcEngineModule->pAssertFail)
              (s_slot____1____slot___PerfTotalEnt_004e7f74,
               s_C__grimsrc_libs_grimlib_Main_spu_004e7f9c,0x5ad);
  }
  QueryPerformanceCounter((int)&local_8);
  *(double *)(&DAT_004e7b48 + param_1 * 0x30) = (double)local_8;
  return;
}
#undef local_8


/* ---- 0x00482e80  Profile_End ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Source: Main/sputmain.cpp (line 1462, from __FILE__/__LINE__ passed to the allocator) */

undefined * __cdecl Profile_End(int param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[48] __attribute__((aligned(16)));  /* the original frame below the return address */
  undefined4 unaff_ESI;
  longlong lVar1;
  undefined4 in_stack_ffffffe8;
  #define uStack_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define lStack_10 (*(longlong *)(_frame + (0x30 - 0x10)))
  #define dStack_8 (*(double *)(_frame + (0x30 - 0x8)))
  
  if ((param_1 < 0) || (0xc < param_1)) {
    (*g_pSvcEngineModule->pAssertFail)
              (s_slot____1____slot___PerfTotalEnt_004e7f74,
               s_C__grimsrc_libs_grimlib_Main_spu_004e7f9c,0x5b6);
  }
  QueryPerformanceFrequency((int)(_stkneg + 24));
  dStack_8 = (double)CONCAT44(uStack_14,in_stack_ffffffe8);
  QueryPerformanceCounter((int)&lStack_10);
  *(double *)(&UINT_004e7b50 + param_1 * 0xc) =
       (((double)lStack_10 - *(double *)(&DAT_004e7b48 + param_1 * 0x30)) / dStack_8) * 1000.0;
  lVar1 = _ftol((double)CONCAT44(in_stack_ffffffe8,unaff_ESI));
  return (undefined *)lVar1;
}
#undef dStack_8
#undef lStack_10
#undef uStack_14

#endif


/* ---- 0x00482f00  Engine_BlitToBackBuffer ---- */
undefined4
Engine_BlitToBackBuffer
          (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  uint *surface;
  
  if (param_2 == 0) {
    surface = (uint *)Render_GetBackBuffer();
  }
  else {
    surface = &g_PrimarySurface;
  }
  Movie_SetTarget(surface);
  iVar1 = Movie_Start(param_1,param_3,param_4,param_5);
  if (iVar1 == 0) {
    if (param_2 != 0) {
      UINT_008a8c40 = 3;
      return 1;
    }
    if (UINT_008a8c40 == 3) {
      UINT_008a8c40 = 2;
    }
    return 1;
  }
  return 0;
}

/* ---- 0x00482f80  Engine_CallUserPaint ---- */
void Engine_CallUserPaint(void)

{
  if (UINT_008a8c40 == 4) {
    Lua_CallUserPaintHandler();
    return;
  }
  return;
}

/* ---- 0x00482f90  Engine_RequestSave ---- */
/* Sets the pending-save flag and the file name; the save happens at the next safe point */

void Engine_RequestSave(char *param_1)

{
  UINT_008a8c7c = 1;
  g_pSaveFileName = param_1;
  return;
}

/* ---- 0x00482fb0  Engine_RequestLoad ---- */
void Engine_RequestLoad(char *param_1)

{
  UINT_008a8c80 = 1;
  g_pSaveFileName = param_1;
  return;
}

/* ---- 0x00482fd0  Engine_TakeRestoreFlag ---- */
uint Engine_TakeRestoreFlag(void)

{
  uint uVar1;
  
  uVar1 = UINT_008a8c84;
  UINT_008a8c84 = 0;
  return uVar1;
}

/* ---- 0x00482fe0  Engine_SaveGame ---- */
/* sputmain.cpp: opens the gzip save file and writes the header, set, actors, Lua state */

void Engine_SaveGame(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *name;
  void *pvVar1;
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
  local_38 = 1;
  local_34 = 0x10;
  local_2c = 6;
  local_24 = 0xb;
  local_1c = 0;
  local_18 = 3;
  local_14 = 2;
  local_10 = 3;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  UINT_008a8c7c = 0;
  Render_SetWaitCursorEnabled(0);
  Render_DrawProgressBar(0.1);
  name = g_pSaveFileName;
  if (g_pSaveFileName == (char *)0x0) {
    name = s_grim_sav_004e7fc8;
  }
  UINT_008a8770 = (uint)SaveFile_Open(name,&DAT_004ddd78);
  if ((void *)UINT_008a8770 != (void *)0x0) {
    Lua_CallSaveGameCallback(SaveGame_Write);
    pvVar1 = Render_CaptureThumbnail(0xfa,0xbc);
    pvVar1 = (void *)Surface_CreateFromBitmap(&local_38,pvVar1);
    SaveGame_Write((int *)((int)pvVar1 + 0x14),4);
    SaveGame_Write(*(void **)((int)pvVar1 + 0x5c),*(int *)((int)pvVar1 + 0x14));
    Surface_Free(pvVar1);
    Render_DrawProgressBar(0.2);
    Cos_Save(SaveGame_Write);
    Render_DrawProgressBar(0.3);
    (*(code *)UINT_008a86e0)(SaveGame_Write);
    Render_DrawProgressBar(0.4);
    (*(code *)UINT_008a87e8)(SaveGame_Write);
    (*(code *)UINT_008a8640)(SaveGame_Write);
    Render_DrawProgressBar(0.5);
    (*(code *)UINT_008a86c0)(SaveGame_Write);
    (*(code *)UINT_008a87c8)(SaveGame_Write);
    (*(code *)UINT_008a8808)(SaveGame_Write);
    (*(code *)UINT_008a8828)(SaveGame_Write);
    SaveGame_Write(&UINT_008a8c48,4);
    Render_DrawProgressBar(0.75);
    lua_Save(SaveGame_Write);
    Render_DrawProgressBar(1.0);
    if (g_pfnIMuseSaveHook != (void *)0x0) {
      (*(code *)g_pfnIMuseSaveHook)(SaveGame_Write);
    }
    gzclose(UINT_008a8770);
    Render_SetWaitCursorEnabled(1);
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


/* ---- 0x00483240  Engine_LoadGame ---- */
void Engine_LoadGame(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *name;
  void *set;
  int setupIdx;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define aiStack_10 (*(int (*)[4])(_frame + (0x30 - 0x10)))
  
  UINT_008a8c80 = 0;
  name = g_pSaveFileName;
  if (g_pSaveFileName == (char *)0x0) {
    name = s_grim_sav_004e7fc8;
  }
  UINT_008a8770 = (uint)SaveFile_Open(name,&DAT_004ddb18);
  if ((void *)UINT_008a8770 != (void *)0x0) {
    Render_SetWaitCursorEnabled(0);
    Render_DrawProgressBar(0.1);
    ImStopAllSounds();
    Movie_Stop();
    Movie_PollPlayback();
    Engine_ResetState();
    g_pShadowMaterial = (void *)0x0;
    Resource_SetNoPurge(1);
    SaveGame_Read(&local_18,4);
    gzseek(UINT_008a8770,local_18,1);
    SaveGame_Read(&local_14,4);
    gzseek(UINT_008a8770,local_14,1);
    Render_DrawProgressBar(0.2);
    Cos_Restore(SaveGame_Read);
    Render_DrawProgressBar(0.3);
    (*(code *)UINT_008a86e4)(SaveGame_Read);
    (*(code *)UINT_008a87ec)(SaveGame_Read);
    Render_DrawProgressBar(0.4);
    (*(code *)UINT_008a8644)(SaveGame_Read);
    (*(code *)UINT_008a86c4)(SaveGame_Read);
    (*(code *)UINT_008a87cc)(SaveGame_Read);
    (*(code *)UINT_008a880c)(SaveGame_Read);
    (*(code *)UINT_008a882c)(SaveGame_Read);
    UINT_008a8c40 = 4;
    SaveGame_Read(&UINT_008a8c48,4);
    Render_DrawProgressBar(0.75);
    lua_Restore(SaveGame_Read);
    Render_DrawProgressBar(1.0);
    if (g_pfnIMuseRestoreHook != (void *)0x0) {
      (*(code *)g_pfnIMuseRestoreHook)(SaveGame_Read);
    }
    Resource_SetNoPurge(0);
    set = Set_GetCurrent();
    if (set == (void *)0x0) {
      setupIdx = 0;
    }
    else {
      setupIdx = *(int *)((int)set + 0xb4);
    }
    Set_SwitchSetup(set,setupIdx);
    gzclose(UINT_008a8770);
    lua_dofile(s_patch05_bin_004e7fe8);
    UINT_008a8c84 = 1;
    Render_SetWaitCursorEnabled(1);
    aiStack_10[0] = 0;
    aiStack_10[1] = 0;
    aiStack_10[2] = 0x280;
    aiStack_10[3] = 0x1e0;
    Render_InvalidateRect(aiStack_10,1);
  }
  return;
}
#undef aiStack_10
#undef local_14
#undef local_18


/* ---- 0x004835f0  Engine_SetSavedValue ---- */
/* Stores the dword that Engine_SaveGame writes after the module hooks */

void Engine_SetSavedValue(uint param_1)

{
  UINT_008a8c48 = param_1;
  return;
}

/* ---- 0x00483600  Engine_GetSavedValue ---- */
uint Engine_GetSavedValue(void)

{
  return UINT_008a8c48;
}

/* ---- 0x00484000  Engine_CreateCameraActor ---- */
/* Creates the hidden actor that carries the camera frame (g_hCameraActor) */

undefined4 Engine_CreateCameraActor(void)

{
  int iVar1;
  
  g_nCameraActor = Actor_Create();
  iVar1 = Actor_FromHandle(g_nCameraActor);
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 1;
  return 1;
}

/* ---- 0x00484260  Engine_RenderFrame ---- */
/* sputRender.cpp: draws one frame. Mode 3 polls the movie; otherwise re-prepares the set when it
   changed, draws object states, actors (profile slots 4-7), overlays, the iris/fade (flag 4 of
   g_dwRenderFlags) and text */

void Engine_RenderFrame(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *actor;
  float fVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  void *pvVar6;
  float *pfVar7;
  float *pfVar8;
  uint uVar9;
  uint *puVar10;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define fStack_c (*(float *)(_frame + (0x30 - 0xc)))
  #define fStack_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define fStack_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  if (UINT_008a8c40 != 0) {
    if (UINT_008a8c40 == 3) {
      Movie_SetTarget(&g_BackBuffer);
      iVar5 = Movie_PollPlayback();
      if (iVar5 != 0) {
        iVar5 = 0;
        UINT_008a8c40 = 2;
        local_1c = 0;
        local_18 = 0;
        local_14 = 0x280;
        local_10 = 0x1e0;
        if (0 < g_nBufferCount) {
          do {
            DirtyRect_Add((int *)&local_1c,1,iVar5);
            iVar5 = iVar5 + 1;
          } while (iVar5 < g_nBufferCount);
        }
        Render_RequestFullRedraw();
        UINT_008c97f8 = 1;
      }
      local_1c = (uint)Timer_GetFrameSeconds();
      Actors_UpdateTalking((float)local_1c);
      Surface_Lock(&g_BackBuffer);
      UINT_008a94b8 = UINT_0090563c;
      TextObjects_Update(0);
      Surface_Unlock(&g_BackBuffer);
      Render_Present();
      return;
    }
    if (UINT_008a8c40 == 4) {
      if (g_nFullRedrawPending != 0) {
        Engine_CallUserPaint();
        g_nFullRedrawPending = 0;
        return;
      }
    }
    else {
      if (UINT_008c9804 != 0) {
        lua_printstack(0);
      }
      pvVar6 = Set_GetCurrent();
      if (pvVar6 == (void *)0x0) {
        return;
      }
      pvVar6 = Set_GetCurrent();
      if (((g_pRenderedSet != pvVar6) ||
          (pvVar6 = Set_GetCurrent(), *(int *)((int)pvVar6 + 0xb4) != g_nRenderedSetup)) ||
         (g_nFullRedrawPending != 0)) {
        DirtyRect_Clear();
        g_pRenderedSet = Set_GetCurrent();
        g_nRenderedSetup = *(int *)((int)g_pRenderedSet + 0xb4);
        Set_SwitchSetup(g_pRenderedSet,g_nRenderedSetup);
        Lua_CallPostCamChangeHandler(g_nRenderedSetup);
      }
      uVar9 = *(int *)((int)g_pRenderedSet + 0xac) + g_nRenderedSetup * 300;
      local_1c = uVar9;
      Set_ApplySetupCamera(g_pRenderedSet,g_nRenderedSetup);
      for (pvVar6 = *(void **)(uVar9 + 0x128); pvVar6 != (void *)0x0;
          pvVar6 = *(void **)((int)pvVar6 + 0xf8)) {
        ObjectState_Draw(pvVar6,3,g_pBackgroundSurface,g_pZBufferSurface);
      }
      Profile_Begin(4);
      if (g_nDrawEnabled != 0) {
        DirtyRect_Flush(&g_BackBuffer,(void *)UINT_008c97a4);
      }
      Profile_End(4);
      Movie_SetTarget(&g_BackBuffer);
      Movie_PollPlayback();
      Surface_Lock(&g_BackBuffer);
      Primitives_DrawAll(1);
      Surface_Unlock(&g_BackBuffer);
      for (pvVar6 = *(void **)(uVar9 + 0x128); pvVar6 != (void *)0x0;
          pvVar6 = *(void **)((int)pvVar6 + 0xf8)) {
        ObjectState_Draw(pvVar6,1,&g_BackBuffer,(void *)UINT_008c97a4);
      }
      rdroid_BeginFrame();
      Render_BuildActorDrawList();
      if ((UINT_008a952c != 0) || (((byte)g_dwRenderDebugFlags & 1) != 0)) {
        Profile_Begin(5);
        iVar5 = 0;
        if (0 < (int)UINT_008a952c) {
          puVar10 = &UINT_008c9568;
          do {
            if (*(char *)*puVar10 == '\0') {
              Costume_TouchComponents
                        (**(undefined4 **)
                           ((int)g_pActorTable + *(int *)((char *)*puVar10 + 8) * 0xa8 + 0xa0));
            }
            iVar5 = iVar5 + 1;
            puVar10 = puVar10 + 1;
          } while (iVar5 < (int)UINT_008a952c);
        }
        Profile_End(5);
        if (((byte)g_dwRenderDebugFlags & 1) != 0) {
          Surface_Lock(&g_BackBuffer);
          if (((byte)g_dwRenderDebugFlags & 8) == 0) {
            Render_DrawDebugGrid();
          }
          else {
            Set_GetCurrent();
            Sector_DrawAllDebug();
          }
          Surface_Unlock(&g_BackBuffer);
        }
        Profile_Begin(6);
        if (iVar5 != 0) {
          puVar10 = &UINT_008c9568 + iVar5 + -1;
          do {
            actor = (int *)((int)g_pActorTable + *(int *)(*puVar10 + 8) * 0xa8);
            fVar1 = *(float *)((int)g_pActorTable + *(int *)(*puVar10 + 8) * 0xa8 + 0x30);
            if (fVar1 != 1.0) {
              fStack_8 = (float)actor[0xc];
              pfVar8 = &fStack_c;
              fStack_4 = (float)actor[0xc];
              fStack_c = fVar1;
              pfVar7 = Actor_GetFrame(actor);
              Matrix_BuildTransform2(pfVar7,pfVar8);
            }
            if (*(char *)*puVar10 == '\0') {
              piVar2 = (int *)*actor;
              iVar3 = *piVar2;
              if (iVar3 == 0) {
                iVar3 = *(int *)((int)g_pRenderedSet + 0x88);
                iVar4 = *(int *)((int)g_pRenderedSet + 0x80);
                if (*(int *)(iVar4 + iVar3 * 0x34) == 0) {
                  (*g_pSvcMain->pAssertFail)
                            (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
                }
                rdroid_SetColormap(*(undefined4 *)(iVar4 + iVar3 * 0x34 + 4));
                iVar3 = *(int *)((int)g_pRenderedSet + 0x88);
                iVar4 = *(int *)((int)g_pRenderedSet + 0x80);
                if (*(int *)(iVar4 + iVar3 * 0x34) == 0) {
                  (*g_pSvcMain->pAssertFail)
                            (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
                }
                iVar3 = *(int *)(iVar4 + iVar3 * 0x34 + 4);
              }
              else {
                if (iVar3 == 0) {
                  (*g_pSvcMain->pAssertFail)
                            (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
                }
                rdroid_SetColormap(piVar2[1]);
                piVar2 = (int *)*actor;
                if (*piVar2 == 0) {
                  (*g_pSvcMain->pAssertFail)
                            (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
                }
                iVar3 = piVar2[1];
              }
              (*(code *)UINT_008c97b8)(iVar3 + 0x30,0);
              pfVar8 = Actor_GetFrame(actor);
              Actor_DrawCostumes(actor[0x28],pfVar8);
              if (((byte)g_dwRenderDebugFlags & 1) != 0) {
                Actor_DrawDebugWalker(actor);
              }
            }
            else if (*(char *)*puVar10 == '\x01') {
              if (g_nZBufferEnabled == 0) {
                Surface_Lock(&g_BackBuffer);
              }
              Actor_ComputeScreenBox(actor);
              if (g_nZBufferEnabled == 0) {
                Surface_Unlock(&g_BackBuffer);
              }
              Render_InvalidateRectLastBuffer(actor + 0x1b,1);
            }
            if (actor[0xc] != 0x3f800000) {
              fStack_c = 1.0 / (float)actor[0xc];
              pfVar8 = &fStack_c;
              fStack_8 = fStack_c;
              fStack_4 = fStack_c;
              pfVar7 = Actor_GetFrame(actor);
              Matrix_BuildTransform2(pfVar7,pfVar8);
            }
            iVar5 = iVar5 + -1;
            puVar10 = puVar10 + -1;
            uVar9 = local_1c;
          } while (iVar5 != 0);
        }
        Profile_End(6);
        Profile_Begin(7);
        rdroid_EndFrame();
        Profile_End(7);
        for (pvVar6 = *(void **)(uVar9 + 0x128); pvVar6 != (void *)0x0;
            pvVar6 = *(void **)((int)pvVar6 + 0xf8)) {
          ObjectState_Draw(pvVar6,2,&g_BackBuffer,(void *)UINT_008c97a4);
        }
      }
      Surface_Lock(&g_BackBuffer);
      Primitives_DrawAll(2);
      Surface_Unlock(&g_BackBuffer);
      if (((byte)g_dwRenderDebugFlags & 1) != 0) {
        pvVar6 = Set_GetCurrent();
        if (((byte)g_dwRenderDebugFlags & 2) != 0) {
          Set_DrawDebugLights(pvVar6);
        }
        if (((byte)g_dwRenderDebugFlags & 4) != 0) {
          Set_DrawDebugCameras(pvVar6,0xffffffff);
        }
      }
      if ((g_dwRenderFlags & 4) != 0) {
        iVar5 = Timer_GetTotalMs();
        local_18 = 0;
        local_1c = (uint)((float)(iVar5 - g_dwIrisStartMs) / g_flIrisDurationMs);
        if ((float)local_1c < 0.0) {
          local_1c = (uint)-(float)local_1c;
        }
        if ((float)local_1c <= 1.0) {
          g_dwRenderFlags = g_dwRenderFlags & 0xfffffff7;
        }
        else {
          local_1c = 0x3f800000;
          if (0.0 <= g_flIrisDurationMs) {
            g_dwRenderFlags = g_dwRenderFlags | 8;
          }
          else {
            g_dwRenderFlags = g_dwRenderFlags & 0xfffffffb;
          }
        }
        if (g_flIrisDurationMs <= 0.0) {
          local_1c = (uint)(1.0 - (float)local_1c);
        }
        Render_DrawIris((float)local_1c,g_nIrisX,g_nIrisY);
        if (g_flIrisDurationMs < 0.0) {
          local_18 = 0;
          local_1c = 0;
          local_14 = 0x280;
          local_10 = 0x1e0;
          Render_InvalidateRect((int *)&local_1c,0);
        }
      }
      Surface_Lock(&g_BackBuffer);
      UINT_008a94b8 = UINT_0090563c;
      TextObjects_Update(1);
      Surface_Unlock(&g_BackBuffer);
    }
    g_nFullRedrawPending = 0;
  }
  return;
}
#undef fStack_4
#undef fStack_8
#undef fStack_c
#undef local_10
#undef local_14
#undef local_18
#undef local_1c


/* ---- 0x0048d1a0  Engine_RegisterShutdownHook ---- */
/* Appends fn to the 9-slot hook array g_pShutdownHooks */

void __cdecl Engine_RegisterShutdownHook(void *fn)

{
  if (g_nShutdownHookCount < 9) {
    (&g_pShutdownHooks)[g_nShutdownHookCount] = fn;
    g_nShutdownHookCount = g_nShutdownHookCount + 1;
  }
  return;
}

/* ---- 0x0048d1c0  Engine_RunShutdownHooks ---- */
/* Runs the registered shutdown hooks (Engine_RegisterShutdownHook) then dumps the memory log */

void Engine_RunShutdownHooks(undefined4 param_1)

{
  int iVar1;
  void **ppvVar2;
  int iVar3;
  
  if (0 < g_nShutdownHookCount) {
    Input_Update();
    iVar3 = 0;
    if (0 < g_nShutdownHookCount) {
      ppvVar2 = &g_pShutdownHooks;
      do {
        if (*ppvVar2 != (code *)0x0) {
          iVar1 = (*(code *)*ppvVar2)(param_1);
          if (iVar1 != 0) break;
        }
        iVar3 = iVar3 + 1;
        ppvVar2 = ppvVar2 + 1;
      } while (iVar3 < g_nShutdownHookCount);
    }
    Mem_DumpLog();
  }
  return;
}
