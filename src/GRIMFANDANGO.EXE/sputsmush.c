/* GRIMFANDANGO.EXE :: sputsmush.c
 * functions 0x00488fb0 .. 0x00489190 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00488fb0  sputSmush_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 sputSmush_Initialize(undefined4 param_1,undefined4 *param_2)

{
  _DAT_008c9ca8 = param_1;
  *param_2 = sputSmush_Initialize;
  param_2[1] = &DAT_004891a0;
  param_2[2] = sputSmush_Startup;
  param_2[3] = sputSmush_Stop;
  param_2[4] = Movie_SaveState;
  param_2[5] = Movie_RestoreState;
  param_2[6] = 0;
  param_2[7] = 0;
  Insane_RegisterFilio(param_1,&DAT_008c9fb8);
  Insane_SetOutputParams(&PTR_Movie_CheckSurfaceFormat_004e8338);
  g_pMovieSurface = (void *)0x0;
  _DAT_008ca080 = 1;
  return 0;
}

/* ---- 0x00489130  sputSmush_Startup ---- */
/* Module slot 2 of sputSmush: honours the StartSmush registry value (FALSE disables movies),
   otherwise initialises the Smush player through the LecShare table and sets g_nMovieAvailable.
   Original name sputSmush_Startup (the remaster's GrimFandango (Linux): strings: 'StartSmush'); was
   sputSmush_Start. */

undefined4 sputSmush_Startup(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_c (*(char (*)[12])(_frame + (0x20 - 0xc)))
  
  iVar1 = Reg_GetString(s_StartSmush_004e8358,local_c,10,&DAT_004f5a98);
  if ((iVar1 != 0) && (iVar1 = _stricmp(local_c,s_FALSE_004e8350), iVar1 == 0)) {
    return 0;
  }
  iVar1 = (*(code *)UINT_008c9fc0)();
  if (iVar1 == 0) {
    g_nMovieAvailable = 1;
    return 0;
  }
  return 1;
}
#undef local_c


/* ---- 0x00489190  sputSmush_Stop ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Module slot 3 of sputSmush: jumps through the Smush player's shutdown pointer when movies are
   available. */

void sputSmush_Stop(void)

{
  if (g_nMovieAvailable != 0) {
                    /* WARNING: Could not recover jumptable at 0x00489199. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*_DAT_008c9fc4)();
    return;
  }
  return;
}
