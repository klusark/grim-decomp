/* GRIMFANDANGO.EXE :: engine.c
 * functions 0x00482460 .. 0x0048d1c0 (42 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00482460  Res_FreeAll ---- */
/* Called when nuking resources and before a restore Original name Res_FreeAll (the remaster's
   GrimFandango (Linux): aligned call in Res_SysShutdown, sputLua_NukeResourcesL); was
   Engine_ResetState. */

void Res_FreeAll(void)

{
  int *piVar1;
  int *res;
  int *res_00;
  
  res = g_pNewestResNode;
  res_00 = g_pNewestResNode;
  if (g_pNewestResNode != (int *)0x0) {
    do {
      piVar1 = (int *)*res_00;
      if ((*(byte *)(res_00 + 7) & 8) == 0) {
        Res_CallUnload(res_00);
        Res_Unlink(res_00);
        res = g_pNewestResNode;
      }
      res_00 = piVar1;
    } while (piVar1 != (int *)0x0);
    while (res != (int *)0x0) {
      Res_CallUnload(res);
      Res_Unlink(g_pNewestResNode);
      res = g_pNewestResNode;
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

/* ---- 0x004825c0  grimlib_OverrideSelectedActorCostume ---- */
/* Original name grimlib_OverrideSelectedActorCostume (the remaster's GrimFandango (Linux): the only
   unmatched caller of Actor_PushCostume; 2 matched neighbours agree, 0 disagree); was
   Engine_PushSelectedActorCostume. */

void grimlib_OverrideSelectedActorCostume(int param_1)

{
  if (g_pSelectedActor != (void *)0x0) {
    sputLua_DoCostumeOverrideCallback(g_pSelectedActor,1);
    sputActor_PushCostume(g_pSelectedActor,(char *)0x0,param_1);
  }
  return;
}

/* ---- 0x004825f0  grimlib_RestoreSelectedActorCostume ---- */
/* Original name grimlib_RestoreSelectedActorCostume (the remaster's GrimFandango (Linux): the only
   unmatched caller of Actor_PopCostume; 2 matched neighbours agree, 0 disagree); was
   Engine_PopSelectedActorCostume. */

void grimlib_RestoreSelectedActorCostume(void)

{
  if (g_pSelectedActor != (void *)0x0) {
    sputLua_DoCostumeOverrideCallback(g_pSelectedActor,0);
    sputActor_PopCostume(g_pSelectedActor,0);
  }
  return;
}

/* ---- 0x00482620  grimlib_SetDisplay ---- */
/* Original name grimlib_SetDisplay (the remaster's GrimFandango (Linux): the only unmatched caller
   of Render_Open; 2 matched neighbours agree, 0 disagree); was Engine_OpenRenderer. */

int __cdecl grimlib_SetDisplay(void *mode,int flags)

{
  sputRender_PageCountIs(g_dwStdDisplay_numDrawBuffers);
  sputRender_SetDisplay
            (mode,flags,0,0,*(int *)((int)mode + 0xc) + -1,*(int *)((int)mode + 0x10) + -1,
             &g_aGrimlib_renderOptions);
  return 0;
}

/* ---- 0x00482660  Engine_CloseRenderer ---- */
undefined4 Engine_CloseRenderer(void)

{
  sputRender_Close();
  return 0;
}

/* ---- 0x004826e0  Engine_ShutdownGame ---- */
/* Releases input, the renderer and the current set */

void Engine_ShutdownGame(void)

{
  if (UINT_008a8c78 != 0) {
    g_dwGrimlib_mode = 0;
    Control_Release();
    sputRender_Close();
    sputRoom_SetCurrentRoom((void *)0x0,0);
    UINT_008a8c78 = 0;
  }
  return;
}

/* ---- 0x00482720  Engine_SetDebugKeysCallback ---- */
void Engine_SetDebugKeysCallback(undefined4 param_1)

{
  sputLua_SetDebugToggleCallback(param_1);
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
int Engine_RunSystemScript(void)

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
  g_dwGrimlib_mode = 2;
  Engine_CreateCameraActor();
  puVar2 = Control_Capture();
  if (puVar2 == (undefined *)0x0) {
    return 1;
  }
  UINT_008a8c78 = 1;
  return 0;
}

/* ---- 0x00482800  grimlib_MarkDirtyRect ---- */
/* Original name grimlib_MarkDirtyRect (the remaster's GrimFandango (Linux): aligned call in
   Main_Service); was Engine_InvalidateRect. */

void grimlib_MarkDirtyRect(int *param_1,int param_2)

{
  Render_InvalidateRectLastBuffer(param_1,param_2);
  return;
}

/* ---- 0x004828d0  grimlib_ConfirmClose ---- */
/* Original name grimlib_ConfirmClose (the remaster's GrimFandango (Linux): the only unmatched
   caller of Lua_CallExitHandler; 1 matched neighbours agree, 0 disagree); was
   Engine_CallExitHandler. */

int grimlib_ConfirmClose(void)

{
  int iVar1;
  
  iVar1 = sputLua_DoExitCallback();
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

/* ---- 0x00482900  grimlib_SetPause ---- */
/* Lua EnginePause/EngineResume and WM_ACTIVATEAPP use this to freeze the engine clock Original name
   grimlib_SetPause (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_EnginePause; the only unmatched callee of Lua_EngineResume; 2 matched neighbours agree, 0
   disagree); was Engine_SetPaused. */

void __cdecl grimlib_SetPause(int paused)

{
  if (g_dwGrimlib_mode != 0) {
    if (paused != 0) {
      if (g_dwGrimlib_mode != 1) {
        UINT_008a8c90 = g_dwGrimlib_mode;
        g_dwGrimlib_SetPause_oldmode = UINT_008a8c44;
        g_dwGrimlib_mode = 1;
        ImPause();
        sputSmush_Pause(1);
        return;
      }
      if (paused != 0) {
        return;
      }
    }
    if (g_dwGrimlib_mode == 1) {
      g_dwGrimlib_mode = UINT_008a8c90;
      UINT_008a8c44 = g_dwGrimlib_SetPause_oldmode;
      ImResume();
      sputSmush_Pause(0);
    }
  }
  return;
}

/* ---- 0x00482980  Engine_CallCharacterHandler ---- */
undefined * __cdecl Engine_CallCharacterHandler(int param_1)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)sputLua_DoCharacterCallback(param_1);
  return puVar1;
}

/* ---- 0x00482990  grimlib_UpdateManual ---- */
/* WARNING: Variable defined which should be unmapped: local_8 */
/* WARNING: Variable defined which should be unmapped: local_c */
/* Engine_UpdateFrame(draw, fixedMs). Runs the frame: sound (SoundsPeriodic), then the timer
   (Timer_UpdateFromWallClock when fixedMs==0, Timer_UpdateFixedStep(fixedMs) otherwise), the Lua
   tasks (FUN_0049c8f0) and the actor update (FUN_0048fcf0 with the frame seconds). Original name
   grimlib_UpdateManual (the remaster's GrimFandango (Linux): aligned call in Main_Service); was
   Engine_UpdateFrame. */

void grimlib_UpdateManual(int param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  float fVar2;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  if (UINT_008a8c7c != 0) {
    Engine_SaveGame();
  }
  if (g_dwDoLoad != 0) {
    Engine_LoadGame();
  }
  PerfBegin(0);
  PerfBegin(10);
  SoundsPeriodic();
  PerfEnd(10);
  if (g_dwGrimlib_mode != 0) {
    PerfBegin(1);
    uVar1 = sputTime_GetFrameTime();
    fVar2 = sputTime_GetFrameTimeFlex();
    sputControl_Update(PUN(undefined4,(float)(fVar2)),uVar1);
    PerfEnd(1);
    if ((g_dwGrimlib_mode != 1) || (param_2 != 0)) {
      g_dwGrimlib_frameNumber = g_dwGrimlib_frameNumber + 1;
      if (param_2 == 0) {
        sputTime_Advance();
      }
      else {
        sputTime_AdvanceManual(param_2);
      }
      if (g_dwUpdateLua != 0) {
        PerfBegin(2);
        sputLua_Update();
        PerfEnd(2);
      }
      if ((g_dwGrimlib_mode != 3) && (g_dwGrimlib_mode != 4)) {
        PerfBegin(3);
        fVar2 = sputTime_GetFrameTimeFlex();
        sputActor_UpdateActors(fVar2);
        PerfEnd(3);
      }
    }
    if ((param_1 != 0) && ((g_dwGrimlib_mode != 1 || (param_2 != 0)))) {
      sputRender_Update();
      UINT_008a8c60 = 1;
    }
    PerfEnd(0);
    if (g_dwGrimlib_NewImuseState != 0xffffffff) {
      ImSetState(g_dwGrimlib_NewImuseState);
      g_dwGrimlib_NewImuseState = 0xffffffff;
    }
  }
  return;
}
#undef local_8
#undef local_c


/* ---- 0x00482ae0  gimlib_SetImuseState ---- */
/* Lua ImSetState Original name gimlib_SetImuseState (the remaster's GrimFandango (Linux): aligned
   call in sputLua_ImSetState); was Engine_SetIMuseState. */

void __cdecl gimlib_SetImuseState(int state)

{
  g_dwGrimlib_NewImuseState = state;
  return;
}

/* ---- 0x00482af0  grimlib_Display ---- */
/* Profile slot 8: presents the back buffer when the game state is 3 Original name grimlib_Display
   (the remaster's GrimFandango (Linux): aligned call in Main_Service); was Engine_PresentFrame. */

void grimlib_Display(void)

{
  int iVar1;
  
  PerfBegin(8);
  if (g_dwGrimlib_mode == 3) {
    iVar1 = Render_CanvasIsPaletted();
    if (iVar1 == 0) {
      Render_Present();
      PerfEnd(8);
      return;
    }
  }
  else {
    if (g_dwGrimlib_mode == 2) {
      Render_Present();
      PerfEnd(8);
      return;
    }
    if ((g_dwGrimlib_mode == 1) && (UINT_008a8c60 != 0)) {
      Render_Present();
      UINT_008a8c60 = 0;
    }
  }
  PerfEnd(8);
  return;
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

/* ---- 0x00482e30  PerfBegin ---- */
/* Source: Main/sputmain.cpp (line 1453, from __FILE__/__LINE__ passed to the allocator) Original
   name PerfBegin (the remaster's GrimFandango (Linux): aligned call in grimlib_Display,
   sputCostume_DrawActorShadow, sputRender_Update); was Profile_Begin. */

void PerfBegin(int param_1)

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


/* ---- 0x00482e80  PerfEnd ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Source: Main/sputmain.cpp (line 1462, from __FILE__/__LINE__ passed to the allocator) Original
   name PerfEnd (the remaster's GrimFandango (Linux): aligned call in grimlib_Display,
   sputCostume_DrawActorShadow, sputRender_Update); was Profile_End. */

undefined * __cdecl PerfEnd(int param_1)

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
  *(double *)(&g_dwGrimlib_PerfData + param_1 * 0xc) =
       (((double)lStack_10 - *(double *)(&DAT_004e7b48 + param_1 * 0x30)) / dStack_8) * 1000.0;
  lVar1 = _ftol((double)CONCAT44(in_stack_ffffffe8,unaff_ESI));
  return (undefined *)lVar1;
}
#undef dStack_8
#undef lStack_10
#undef uStack_14

#endif


/* ---- 0x00482f00  grimlib_PlayMovie ---- */
/* Original name grimlib_PlayMovie (the remaster's GrimFandango (Linux): the only unmatched callee
   of Lua_StartFullscreenMovie; 2 matched neighbours agree, 0 disagree); was
   Engine_BlitToBackBuffer. */

undefined4
grimlib_PlayMovie(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  uint *surface;
  
  if (param_2 == 0) {
    surface = (uint *)Render_GetBackBuffer();
  }
  else {
    surface = &g_dwStdDisplay_frontBuffer;
  }
  sputSmush_SetTarget(surface);
  iVar1 = sputSmush_StartMovie(param_1,param_3,param_4,param_5);
  if (iVar1 == 0) {
    if (param_2 != 0) {
      g_dwGrimlib_mode = 3;
      return 1;
    }
    if (g_dwGrimlib_mode == 3) {
      g_dwGrimlib_mode = 2;
    }
    return 1;
  }
  return 0;
}

/* ---- 0x00482f80  grimlib_UserPaint ---- */
/* Original name grimlib_UserPaint (the remaster's GrimFandango (Linux): the only unmatched caller
   of Lua_CallUserPaintHandler; 2 matched neighbours agree, 0 disagree); was Engine_CallUserPaint.
    */

void grimlib_UserPaint(void)

{
  if (g_dwGrimlib_mode == 4) {
    sputLua_DoUserPaintCallback();
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

/* ---- 0x00482fb0  grimlib_Load ---- */
/* Original name grimlib_Load (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_Load; 1 matched neighbours agree, 0 disagree); was Engine_RequestLoad. */

void grimlib_Load(char *param_1)

{
  g_dwDoLoad = 1;
  g_pSaveFileName = param_1;
  return;
}

/* ---- 0x00482fd0  grimlib_JustLoaded ---- */
/* Original name grimlib_JustLoaded (the remaster's GrimFandango (Linux): the only unmatched callee
   of Lua_JustLoaded; 1 matched neighbours agree, 0 disagree); was Engine_TakeRestoreFlag. */

uint grimlib_JustLoaded(void)

{
  uint uVar1;
  
  uVar1 = g_dwJustLoaded;
  g_dwJustLoaded = 0;
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
    sputLua_SaveGameCallback(SaveGame_Write);
    pvVar1 = sputRender_ScreenShot(0xfa,0xbc);
    pvVar1 = (void *)stdDisplay_VBufferConvertColorFormat(&local_38,pvVar1);
    SaveGame_Write((int *)((int)pvVar1 + 0x14),4);
    SaveGame_Write(*(void **)((int)pvVar1 + 0x5c),*(int *)((int)pvVar1 + 0x14));
    stdDisplay_VBufferFree(pvVar1);
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
    SaveGame_Write(&g_dwGrimlib_prevmode,4);
    Render_DrawProgressBar(0.75);
    lua_Save((int *)SaveGame_Write);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
void Engine_LoadGame(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *name;
  void *set;
  int setupIdx;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define aiStack_10 (*(int (*)[4])(_frame + (0x30 - 0x10)))
  
  g_dwDoLoad = 0;
  name = g_pSaveFileName;
  if (g_pSaveFileName == (char *)0x0) {
    name = s_grim_sav_004e7fc8;
  }
  UINT_008a8770 = (uint)SaveFile_Open(name,&DAT_004ddb18);
  if ((void *)UINT_008a8770 != (void *)0x0) {
    Render_SetWaitCursorEnabled(0);
    Render_DrawProgressBar(0.1);
    ImStopAllSounds();
    sputSmush_StopMovie();
    sputSmush_Periodic();
    Res_FreeAll();
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
    g_dwGrimlib_mode = 4;
    SaveGame_Read(&g_dwGrimlib_prevmode,4);
    Render_DrawProgressBar(0.75);
    lua_Restore(SaveGame_Read);
    Render_DrawProgressBar(1.0);
    if (g_pfnIMuseRestoreHook != (void *)0x0) {
      (*(code *)g_pfnIMuseRestoreHook)(SaveGame_Read);
    }
    Resource_SetNoPurge(0);
    set = sputRoom_GetCurrentRoom();
    if (set == (void *)0x0) {
      setupIdx = 0;
    }
    else {
      setupIdx = *(int *)((int)set + 0xb4);
    }
    sputRender_UseSetup(set,setupIdx);
    gzclose(UINT_008a8770);
    lua_dofile(s_patch05_bin_004e7fe8);
    g_dwJustLoaded = 1;
    Render_SetWaitCursorEnabled(1);
    aiStack_10[0] = 0;
    aiStack_10[1] = 0;
    aiStack_10[2] = 0x280;
    aiStack_10[3] = 0x1e0;
    MarkDirtyRect(aiStack_10,1);
  }
  return;
}
#undef aiStack_10
#undef local_14
#undef local_18

#endif


/* ---- 0x004835f0  SetPrevMode ---- */
/* Stores the dword that Engine_SaveGame writes after the module hooks Original name SetPrevMode
   (the remaster's GrimFandango (Linux): aligned call in sputLua_RenderModeUser); was
   Engine_SetSavedValue. */

void SetPrevMode(uint param_1)

{
  g_dwGrimlib_prevmode = param_1;
  return;
}

/* ---- 0x00483600  Engine_GetSavedValue ---- */
uint Engine_GetSavedValue(void)

{
  return g_dwGrimlib_prevmode;
}

/* ---- 0x00484000  Engine_CreateCameraActor ---- */
/* Creates the hidden actor that carries the camera frame (g_hCameraActor) */

undefined4 Engine_CreateCameraActor(void)

{
  int iVar1;
  
  g_nCamActorIndex = sputActor_AllocateActor();
  iVar1 = sputActor_ActorDeref(g_nCamActorIndex);
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 1;
  return 1;
}

/* ---- 0x00484260  sputRender_Update ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* sputRender.cpp: draws one frame. Mode 3 polls the movie; otherwise re-prepares the set when it
   changed, draws object states, actors (profile slots 4-7), overlays, the iris/fade (flag 4 of
   g_dwRenderFlags) and text
   Ported to C (build/overrides_big_engine_renderframe.c): differential test vs recorder stand-ins,
   0 differences (docs/notes/big_engine_renderframe.md). Original name sputRender_Update (the
   remaster's GrimFandango (Linux): the only unmatched caller of Lua_CallPostCamChangeHandler; 6
   matched neighbours agree, 1 disagree); was Engine_RenderFrame. */

void sputRender_Update(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *actor;
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  float *pfVar6;
  float *pfVar7;
  float fVar8;
  uint *puVar9;
  #define local_1c (*(float (*)[3])(_frame + (0x30 - 0x1c)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define fStack_c (*(float *)(_frame + (0x30 - 0xc)))
  #define fStack_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define fStack_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  if (g_dwGrimlib_mode != 0) {
    if (g_dwGrimlib_mode == 3) {
      sputSmush_SetTarget(&g_dwStdDisplay_backBuffer);
      iVar4 = sputSmush_Periodic();
      if (iVar4 != 0) {
        iVar4 = 0;
        g_dwGrimlib_mode = 2;
        local_1c[0] = 0.0;
        local_1c[1] = 0.0;
        local_1c[2] = 8.96831e-43;
        if (0 < g_nNumPages) {
          do {
            DirtyRect_Add((int *)local_1c,1,iVar4);
            iVar4 = iVar4 + 1;
          } while (iVar4 < g_nNumPages);
        }
        sputRender_ForceRefresh();
        g_dwMovieJustFinished = 1;
      }
      local_1c[0] = sputTime_GetFrameTimeFlex();
      sputActor_UpdateSpeechOnly(local_1c[0]);
      stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
      UINT_008a94b8 = UINT_0090563c;
      sputText_Update(0);
      stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
      Render_Present();
      return;
    }
    if (g_dwGrimlib_mode == 4) {
      if (g_nSputRender_Reset != 0) {
        grimlib_UserPaint();
        g_nSputRender_Reset = 0;
        return;
      }
    }
    else {
      if (UINT_008c9804 != 0) {
        lua_printstack(0);
      }
      pvVar5 = sputRoom_GetCurrentRoom();
      if (pvVar5 == (void *)0x0) {
        return;
      }
      pvVar5 = sputRoom_GetCurrentRoom();
      if (((g_pRenderedSet != pvVar5) ||
          (pvVar5 = sputRoom_GetCurrentRoom(),
          *(int *)((int)pvVar5 + 0xb4) != g_nSputRender_Update_RenderSetup)) ||
         (g_nSputRender_Reset != 0)) {
        DirtyRect_Clear();
        g_pRenderedSet = sputRoom_GetCurrentRoom();
        g_nSputRender_Update_RenderSetup = *(int *)((int)g_pRenderedSet + 0xb4);
        sputRender_UseSetup(g_pRenderedSet,g_nSputRender_Update_RenderSetup);
        sputLua_PostCameraChange(g_nSputRender_Update_RenderSetup);
      }
      fVar8 = (float)(*(int *)((int)g_pRenderedSet + 0xac) + g_nSputRender_Update_RenderSetup * 300)
      ;
      local_1c[0] = fVar8;
      sputRender_SyncCamera(g_pRenderedSet,g_nSputRender_Update_RenderSetup);
      for (pvVar5 = *(void **)(PUN(int,(float)fVar8) + 0x128); pvVar5 != (void *)0x0;
          pvVar5 = *(void **)((int)pvVar5 + 0xf8)) {
        ObjectState_Draw(pvVar5,3,g_pSputRender_CleanBuffer,g_pSputRender_CleanZBuffer);
      }
      PerfBegin(4);
      if (g_nDoTheFlip != 0) {
        DirtyRect_Flush(&g_dwStdDisplay_backBuffer,(void *)UINT_008c97a4);
      }
      PerfEnd(4);
      sputSmush_SetTarget(&g_dwStdDisplay_backBuffer);
      sputSmush_Periodic();
      stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
      sputPrimitive_Update(1);
      stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
      for (pvVar5 = *(void **)(PUN(int,(float)fVar8) + 0x128); pvVar5 != (void *)0x0;
          pvVar5 = *(void **)((int)pvVar5 + 0xf8)) {
        ObjectState_Draw(pvVar5,1,&g_dwStdDisplay_backBuffer,(void *)UINT_008c97a4);
      }
      rdroid_BeginFrame();
      Render_BuildActorDrawList();
      if ((g_dwTotDrawItems != 0) || (((byte)g_dwDebugFlags & 1) != 0)) {
        PerfBegin(5);
        iVar4 = 0;
        if (0 < (int)g_dwTotDrawItems) {
          puVar9 = &g_dwDrawItems;
          do {
            if (*(char *)*puVar9 == '\0') {
              sputCostume_Draw2D(**(undefined4 **)
                                   ((int)g_pActors + *(int *)((char *)*puVar9 + 8) * 0xa8 + 0xa0));
            }
            iVar4 = iVar4 + 1;
            puVar9 = puVar9 + 1;
          } while (iVar4 < (int)g_dwTotDrawItems);
        }
        PerfEnd(5);
        if (((byte)g_dwDebugFlags & 1) != 0) {
          stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
          if (((byte)g_dwDebugFlags & 8) == 0) {
            Render_DrawDebugGrid();
          }
          else {
            sputRoom_GetCurrentRoom();
            Sector_DrawAllDebug();
          }
          stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
        }
        PerfBegin(6);
        if (iVar4 != 0) {
          puVar9 = &g_dwDrawItems + iVar4 + -1;
          do {
            actor = (int *)((int)g_pActors + *(int *)(*puVar9 + 8) * 0xa8);
            fVar8 = *(float *)((int)g_pActors + *(int *)(*puVar9 + 8) * 0xa8 + 0x30);
            if (fVar8 != 1.0) {
              fStack_8 = (float)actor[0xc];
              pfVar7 = &fStack_c;
              fStack_4 = (float)actor[0xc];
              fStack_c = fVar8;
              pfVar6 = sputActor_GetOrientMatrix(actor);
              rdMatrix_PreScale34(pfVar6,pfVar7);
            }
            if (*(char *)*puVar9 == '\0') {
              piVar1 = (int *)*actor;
              iVar2 = *piVar1;
              if (iVar2 == 0) {
                iVar2 = *(int *)((int)g_pRenderedSet + 0x88);
                iVar3 = *(int *)((int)g_pRenderedSet + 0x80);
                if (*(int *)(iVar3 + iVar2 * 0x34) == 0) {
                  (*g_pStd_HS->pAssertFail)
                            (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
                }
                rdroid_SetColormap(*(undefined4 *)(iVar3 + iVar2 * 0x34 + 4));
                iVar2 = *(int *)((int)g_pRenderedSet + 0x88);
                iVar3 = *(int *)((int)g_pRenderedSet + 0x80);
                if (*(int *)(iVar3 + iVar2 * 0x34) == 0) {
                  (*g_pStd_HS->pAssertFail)
                            (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
                }
                iVar2 = *(int *)(iVar3 + iVar2 * 0x34 + 4);
              }
              else {
                if (iVar2 == 0) {
                  (*g_pStd_HS->pAssertFail)
                            (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
                }
                rdroid_SetColormap(piVar1[1]);
                piVar1 = (int *)*actor;
                if (*piVar1 == 0) {
                  (*g_pStd_HS->pAssertFail)
                            (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
                }
                iVar2 = piVar1[1];
              }
              (*(code *)UINT_008c97b8)(iVar2 + 0x30,0);
              pfVar7 = sputActor_GetOrientMatrix(actor);
              sputCostume_Draw3D(actor[0x28],pfVar7);
              if (((byte)g_dwDebugFlags & 1) != 0) {
                Actor_DrawDebugWalker(actor);
              }
            }
            else if (*(char *)*puVar9 == '\x01') {
              if (g_nSputRender_b3DAcceleration == 0) {
                stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
              }
              Actor_ComputeScreenBox(actor);
              if (g_nSputRender_b3DAcceleration == 0) {
                stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
              }
              Render_InvalidateRectLastBuffer(actor + 0x1b,1);
            }
            if (actor[0xc] != 0x3f800000) {
              fStack_c = 1.0 / (float)actor[0xc];
              pfVar7 = &fStack_c;
              fStack_8 = fStack_c;
              fStack_4 = fStack_c;
              pfVar6 = sputActor_GetOrientMatrix(actor);
              rdMatrix_PreScale34(pfVar6,pfVar7);
            }
            iVar4 = iVar4 + -1;
            puVar9 = puVar9 + -1;
            fVar8 = local_1c[0];
          } while (iVar4 != 0);
        }
        PerfEnd(6);
        PerfBegin(7);
        rdroid_EndFrame();
        PerfEnd(7);
        for (pvVar5 = *(void **)(PUN(int,(float)fVar8) + 0x128); pvVar5 != (void *)0x0;
            pvVar5 = *(void **)((int)pvVar5 + 0xf8)) {
          ObjectState_Draw(pvVar5,2,&g_dwStdDisplay_backBuffer,(void *)UINT_008c97a4);
        }
      }
      stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
      sputPrimitive_Update(2);
      stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
      if (((byte)g_dwDebugFlags & 1) != 0) {
        pvVar5 = sputRoom_GetCurrentRoom();
        if (((byte)g_dwDebugFlags & 2) != 0) {
          Set_DrawDebugLights(pvVar5);
        }
        if (((byte)g_dwDebugFlags & 4) != 0) {
          Set_DrawDebugCameras(pvVar5,0xffffffff);
        }
      }
      if ((g_dwRenderFlags & 4) != 0) {
        iVar4 = sputTime_GetGameTime();
        local_1c[1] = 0.0;
        local_1c[0] = (float)(iVar4 - g_dwIrisStart) / g_flIrisDuration;
        if (local_1c[0] < 0.0) {
          local_1c[0] = -local_1c[0];
        }
        if (local_1c[0] <= 1.0) {
          g_dwRenderFlags = g_dwRenderFlags & 0xfffffff7;
        }
        else {
          local_1c[0] = 1.0;
          if (0.0 <= g_flIrisDuration) {
            g_dwRenderFlags = g_dwRenderFlags | 8;
          }
          else {
            g_dwRenderFlags = g_dwRenderFlags & 0xfffffffb;
          }
        }
        if (g_flIrisDuration <= 0.0) {
          local_1c[0] = 1.0 - local_1c[0];
        }
        sputRender_DrawIrisEffect(local_1c[0],g_nIrisX,g_nIrisY);
        if (g_flIrisDuration < 0.0) {
          local_1c[1] = 0.0;
          local_1c[0] = 0.0;
          local_1c[2] = 8.96831e-43;
          MarkDirtyRect((int *)local_1c,0);
        }
      }
      stdDisplay_VBufferLock(&g_dwStdDisplay_backBuffer);
      UINT_008a94b8 = UINT_0090563c;
      sputText_Update(1);
      stdDisplay_VBufferUnlock(&g_dwStdDisplay_backBuffer);
    }
    g_nSputRender_Reset = 0;
  }
  return;
}
#undef fStack_4
#undef fStack_8
#undef fStack_c
#undef local_10
#undef local_1c

#endif


/* ---- 0x0048d1a0  sputControl_AddCallback ---- */
/* Appends fn to the 9-slot hook array g_apControlCallbacks Original name sputControl_AddCallback
   (the remaster's GrimFandango (Linux): the only unmatched callee of sputRender_Initialize; 2
   matched neighbours agree, 0 disagree); was Engine_RegisterShutdownHook. */

void __cdecl sputControl_AddCallback(void *fn)

{
  if (g_nNumControlCallbacks < 9) {
    (&g_apControlCallbacks)[g_nNumControlCallbacks] = fn;
    g_nNumControlCallbacks = g_nNumControlCallbacks + 1;
  }
  return;
}

/* ---- 0x0048d1c0  sputControl_Update ---- */
/* Runs the registered shutdown hooks (Engine_RegisterShutdownHook) then dumps the memory log
   Original name sputControl_Update (the remaster's GrimFandango (Linux): aligned call in
   grimlib_UpdateManual); was Engine_RunShutdownHooks. */

void __cdecl sputControl_Update(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  void **ppvVar2;
  int iVar3;
  
  if (0 < g_nNumControlCallbacks) {
    stdControl_ReadControls();
    iVar3 = 0;
    if (0 < g_nNumControlCallbacks) {
      ppvVar2 = &g_apControlCallbacks;
      do {
        if (*ppvVar2 != (code *)0x0) {
          iVar1 = (*(code *)*ppvVar2)(param_1);
          if (iVar1 != 0) break;
        }
        iVar3 = iVar3 + 1;
        ppvVar2 = ppvVar2 + 1;
      } while (iVar3 < g_nNumControlCallbacks);
    }
    Mem_DumpLog();
  }
  return;
}
