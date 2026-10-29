/* GRIMFANDANGO.EXE :: game.c
 * functions 0x004016a0 .. 0x004016a0 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004016a0  Game_FrameUpdate ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Per-frame function of the main loop. Passes the one-shot global DAT_004f5a48 ("fixed frame time",
   ms) to Engine_UpdateFrame and zeroes it. The load of that global at 0x401721 is what
   tools/patch_simtime.py replaces with `mov eax,17` to run on a fixed 17 ms frame. The call at
   0x401753 (timeGetTime) is the hook of the frame limiter (grimdlg.dll GrimFrameLimit). */

void Game_FrameUpdate(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  #define local_18 (*(undefined4 *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(int *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(undefined4 *)(_frame + (0x30 - 0x10)))
  #define local_c (*(undefined4 *)(_frame + (0x30 - 0xc)))
  
  uVar1 = DAT_008a8c40;
  iVar4 = 0x1e;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0x50;
  local_c = 0x1e;
  if (DAT_004f5a0c == 0) {
    if (DAT_004f5a50 != 0) {
      Display_Select(DAT_004dd340,DAT_004dd344,DAT_004dd348);
      DAT_008a8c40 = 2;
      ((code *)Render_DimBackground)(1);
      DAT_004f5a50 = 0;
    }
    _DAT_004dd384 = 300;
    DAT_008a8c40 = uVar1;
    ((code *)Engine_UpdateFrame)(DAT_008d0a70);
    g_dwFrameCounter = g_dwFrameCounter + 1;
    DAT_004f5a48 = 0;
    _DAT_004f5a60 = timeGetTime();
    if (1000 < (uint)(_DAT_004f5a60 - DAT_004f5a64)) {
      iVar2 = g_dwFrameCounter - DAT_004f5a5c;
      DAT_004f5a5c = g_dwFrameCounter;
      _DAT_004f44e4 = ((float)iVar2 * 1000.0) / (float)(uint)(_DAT_004f5a60 - DAT_004f5a64);
      DAT_004f5a64 = _DAT_004f5a60;
    }
    if (_g_bShowFps != 0) {
      ((undefined4 (*)(undefined1 *, undefined4, float))sprintf)(&DAT_009056c0,s__02_3f_004dd680,(double)_DAT_004f44e4);
      Display_DrawText(&DAT_009056c0,4,4);
      ((code *)Engine_InvalidateRect)(&local_18);
    }
    if (DAT_004f5a30 != 0) {
      puVar3 = &DAT_004e7b50;
      do {
        ((code *)sprintf)(&DAT_009056c0,s__s__02_3f_004dd674,puVar3 + -10,*puVar3);
        Display_DrawText(&DAT_009056c0,4,iVar4);
        local_18 = 4;
        local_10 = 0xbe;
        local_c = 0x14;
        local_14 = iVar4;
        ((code *)Engine_InvalidateRect)(&local_18);
        *puVar3 = 0;
        puVar3[1] = 0;
        iVar4 = iVar4 + 0x14;
        puVar3 = puVar3 + 0xc;
      } while (iVar4 < 0x122);
    }
    if (DAT_008d0a70 != 0) {
      Engine_PresentFrame();
    }
    if (DAT_004f5a0c != 0) {
      ((code *)Win_RemoveMessageHook)();
      ((code *)Win_RemoveMessageHook)();
      iVar4 = Win_GetMainHwnd();
      DestroyWindow(iVar4);
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_c

