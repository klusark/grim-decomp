/* GRIMFANDANGO.EXE :: imusemodule.c
 * functions 0x004836b0 .. 0x004836f0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004836b0  IMuseModule_Init ---- */
/* Fills the 8-entry module interface {init, 0, shutdown=FUN_004c1e50, update, 0...} for the sound
   module */

undefined4 IMuseModule_Init(GrimServices *param_1,undefined4 *param_2)

{
  g_pSvcIMuseModule = param_1;
  *param_2 = IMuseModule_Init;
  param_2[1] = 0;
  param_2[2] = LecShare_Nop;
  param_2[3] = IMuseModule_Stop;
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  return 0;
}

/* ---- 0x004836f0  IMuseModule_Stop ---- */
/* Module interface slot 3 of IMuseModule: frees g_pPolyglotText and the string table buffer. */

void IMuseModule_Stop(void)

{
  if (g_pPolyglotText != (char *)0x0) {
    (*g_pSvcIMuseModule->pFree)(g_pPolyglotText);
  }
  if (UINT_008a8c9c != 0) {
    (*g_pSvcIMuseModule->pFree)(UINT_008a8c9c);
  }
  return;
}
