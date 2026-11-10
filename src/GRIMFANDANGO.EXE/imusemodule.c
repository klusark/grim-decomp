/* GRIMFANDANGO.EXE :: imusemodule.c
 * functions 0x004836b0 .. 0x004836f0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004836b0  PolyglotInitialize ---- */
/* Fills the 8-entry module interface {init, 0, shutdown=FUN_004c1e50, update, 0...} for the sound
   module Original name PolyglotInitialize (the remaster's GrimFandango (Linux): the
   module-interface filler Main_Startup calls after stdStartup, same slots (itself, 0, startup,
   shutdown, 0...) and its pHS (the old name was wrong: it is the polyglot module)); was
   IMuseModule_Init. */

undefined4 PolyglotInitialize(GrimServices *param_1,undefined4 *param_2)

{
  g_pPolyglot_HS = param_1;
  *param_2 = PolyglotInitialize;
  param_2[1] = 0;
  param_2[2] = LecShare_Nop;
  param_2[3] = polyglot_shutdown;
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  return 0;
}

/* ---- 0x004836f0  polyglot_shutdown ---- */
/* Module interface slot 3 of IMuseModule: frees g_pLanguageMalloc and the string table buffer.
   Original name polyglot_shutdown (the remaster's GrimFandango (Linux): the shutdown slot
   PolyglotInitialize fills, same body (frees pLanguageMalloc and ppLanguageLine)); was
   IMuseModule_Stop. */

void polyglot_shutdown(void)

{
  if (g_pLanguageMalloc != (char *)0x0) {
    (*g_pPolyglot_HS->pFree)(g_pLanguageMalloc);
  }
  if (g_dwLanguageLine != 0) {
    (*g_pPolyglot_HS->pFree)(g_dwLanguageLine);
  }
  return;
}
