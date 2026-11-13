/* GRIMFANDANGO.EXE :: game.c
 * functions 0x004016a0 .. 0x004016a0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004016a0  Main_Service ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Per-frame function of the main loop. Passes the one-shot global DAT_004f5a48 ("fixed frame time",
   ms) to grimlib_UpdateManual and zeroes it. The load of that global at 0x401721 is what
   tools/patch_simtime.py replaces with `mov eax,17` to run on a fixed 17 ms frame. The call at
   0x401753 (timeGetTime) is the hook of the frame limiter (grimdlg.dll GrimFrameLimit). Original
   name Main_Service (the remaster's GrimFandango (Linux): strings: '%02.3f' | '%s %02.3f'); was
   Game_FrameUpdate. */

void Main_Service(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  void *a1;
  int iVar2;
  uint *puVar3;
  uint y;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  
  uVar1 = g_dwGrimlib_mode;
  y = 0x1e;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0x50;
  local_c = 0x1e;
  if (g_nQuitApp == 0) {
    if (UINT_004f5a50 != 0) {
      Display_Select(UINT_004dd340,UINT_004dd344,UINT_004dd348);
      g_dwGrimlib_mode = 2;
      ((code *)sputRender_Dim)(1);
      UINT_004f5a50 = 0;
    }
    _g_dwDeadmanCounter = 300;
    g_dwGrimlib_mode = uVar1;
    grimlib_UpdateManual(g_dwZg_App_bAppActive,g_fixedFrameMs);
    g_dwMain_Service_frameCount = g_dwMain_Service_frameCount + 1;
    g_fixedFrameMs = 0;
    _g_dwMain_Service_frameTime = timeGetTime();
    if (1000 < _g_dwMain_Service_frameTime - g_dwMain_Service_frameTime0) {
      iVar2 = g_dwMain_Service_frameCount - UINT_004f5a5c;
      UINT_004f5a5c = g_dwMain_Service_frameCount;
      g_flMain_Service_frameRate =
           ((float)iVar2 * 1000.0) /
           (float)(_g_dwMain_Service_frameTime - g_dwMain_Service_frameTime0);
      g_dwMain_Service_frameTime0 = _g_dwMain_Service_frameTime;
    }
    if (_g_bDrawFrameRate != 0) {
      sprintf(&g_bStd_genBuffer,s__02_3f_004dd680,(double)g_flMain_Service_frameRate);
      stdDisplay_TextOut(&g_bStd_genBuffer,4,4);
      grimlib_MarkDirtyRect((int *)&local_18,0);
    }
    if (g_nDrawPerfData != 0) {
      puVar3 = &g_dwGrimlib_PerfData;
      do {
        sprintf(&g_bStd_genBuffer,s__s__02_3f_004dd674,puVar3 + -10,*puVar3);
        stdDisplay_TextOut(&g_bStd_genBuffer,4,y);
        local_18 = 4;
        local_10 = 0xbe;
        local_c = 0x14;
        local_14 = y;
        grimlib_MarkDirtyRect((int *)&local_18,0);
        *puVar3 = 0;
        puVar3[1] = 0;
        y = y + 0x14;
        puVar3 = puVar3 + 0xc;
      } while ((int)y < 0x122);
    }
    if (g_dwZg_App_bAppActive != 0) {
      grimlib_Display();
    }
    if (g_nQuitApp != 0) {
      Win_RemoveMessageHook(Win_WndProc);
      Win_RemoveMessageHook(Win_IsSysCommandBlocked);
      a1 = Win_GetMainHwnd();
      DestroyWindow((int)a1);
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_c

#endif

