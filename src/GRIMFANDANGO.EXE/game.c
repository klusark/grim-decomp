/* GRIMFANDANGO.EXE :: game.c
 * functions 0x004016a0 .. 0x004016a0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004016a0  Game_FrameUpdate ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Per-frame function of the main loop. Passes the one-shot global DAT_004f5a48 ("fixed frame time",
   ms) to Engine_UpdateFrame and zeroes it. The load of that global at 0x401721 is what
   tools/patch_simtime.py replaces with `mov eax,17` to run on a fixed 17 ms frame. The call at
   0x401753 (timeGetTime) is the hook of the frame limiter (grimdlg.dll GrimFrameLimit). */

void Game_FrameUpdate(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  uint *puVar3;
  uint y;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  
  uVar1 = UINT_008a8c40;
  y = 0x1e;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0x50;
  local_c = 0x1e;
  if (g_quitRequested == 0) {
    if (UINT_004f5a50 != 0) {
      Display_Select(UINT_004dd340,UINT_004dd344,UINT_004dd348);
      UINT_008a8c40 = 2;
      ((code *)Render_DimBackground)(1);
      UINT_004f5a50 = 0;
    }
    _DAT_004dd384 = 300;
    UINT_008a8c40 = uVar1;
    ((code *)Engine_UpdateFrame)(UINT_008d0a70);
    g_dwFrameCounter = g_dwFrameCounter + 1;
    g_fixedFrameMs = 0;
    _DAT_004f5a60 = timeGetTime();
    if (1000 < _DAT_004f5a60 - UINT_004f5a64) {
      iVar2 = g_dwFrameCounter - UINT_004f5a5c;
      UINT_004f5a5c = g_dwFrameCounter;
      g_measuredFps = ((float)iVar2 * 1000.0) / (float)(_DAT_004f5a60 - UINT_004f5a64);
      UINT_004f5a64 = _DAT_004f5a60;
    }
    if (_g_bShowFps != 0) {
      sprintf(&DAT_009056c0,s__02_3f_004dd680,(double)g_measuredFps);
      Display_DrawText(&DAT_009056c0,4,4);
      ((code *)Engine_InvalidateRect)(&local_18);
    }
    if (g_bShowProfile != 0) {
      puVar3 = &UINT_004e7b50;
      do {
        sprintf(&DAT_009056c0,s__s__02_3f_004dd674,puVar3 + -10,*puVar3);
        Display_DrawText(&DAT_009056c0,4,y);
        local_18 = 4;
        local_10 = 0xbe;
        local_c = 0x14;
        local_14 = y;
        ((code *)Engine_InvalidateRect)(&local_18);
        *puVar3 = 0;
        puVar3[1] = 0;
        y = y + 0x14;
        puVar3 = puVar3 + 0xc;
      } while ((int)y < 0x122);
    }
    if (UINT_008d0a70 != 0) {
      Engine_PresentFrame();
    }
    if (g_quitRequested != 0) {
      ((code *)Win_RemoveMessageHook)();
      ((code *)Win_RemoveMessageHook)();
      iVar2 = Win_GetMainHwnd();
      DestroyWindow(iVar2);
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_c

#endif

