/* GRIMFANDANGO.EXE :: phoneme.c
 * functions 0x00490e00 .. 0x00490e50 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00490e00  Phoneme_ToTalkChore ---- */
/* bsearch in the phoneme table g_PhonemeTable (8-byte {phoneme, chore} entries) */

uint __cdecl Phoneme_ToTalkChore(void *unused,int phoneme)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  if (phoneme == 0x5f) {
    return 0;
  }
  local_8 = phoneme;
  iVar1 = bsearch(&local_8,&g_PhonemeTable,g_nPhonemeCount,8,ComparePhonemes);
  if (iVar1 != 0) {
    return *(ushort *)(iVar1 + 4);
  }
  return 1;
}
#undef local_8


/* ---- 0x00490e50  ComparePhonemes ---- */
/* Original name ComparePhonemes (the remaster's GrimFandango (Linux): aligned call in
   sputActor_Startup); was FUN_00490e50. */

int ComparePhonemes(int *param_1,int *param_2)

{
  return *param_1 - *param_2;
}
