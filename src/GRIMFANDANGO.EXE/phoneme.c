/* GRIMFANDANGO.EXE :: phoneme.c
 * functions 0x00490e00 .. 0x00490ef0 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00490e00  Phoneme_ToTalkChore ---- */
/* bsearch in the phoneme table g_PhonemeTable (8-byte {phoneme, chore} entries) */

ushort __cdecl Phoneme_ToTalkChore(void *unused,int phoneme)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  if (phoneme == 0x5f) {
    return 0;
  }
  local_8 = phoneme;
  iVar1 = bsearch(&local_8,&g_PhonemeTable,g_nPhonemeCount,8,FUN_00490e50);
  if (iVar1 != 0) {
    return *(ushort *)(iVar1 + 4);
  }
  return 1;
}
#undef local_8


/* ---- 0x00490e50  FUN_00490e50 ---- */
int FUN_00490e50(int *param_1,int *param_2)

{
  return *param_1 - *param_2;
}

/* ---- 0x00490e60  FUN_00490e60 ---- */
void FUN_00490e60(void)

{
  UINT_008ca32c = 0;
  if (UINT_008ca768 != 0) {
    UINT_008ca768 = 0;
  }
  return;
}

/* ---- 0x00490e80  FUN_00490e80 ---- */
undefined4 FUN_00490e80(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (UINT_008ca76c != 0) {
    return 1;
  }
  g_pActorTable =
       (void *)(**(code **)(UINT_008ca32c + 0x20))
                         (0x2a000,s_C__grimsrc_libs_grimlib_Engine_s_004e9e40,0x81b);
  puVar2 = g_pActorTable;
  for (iVar1 = 0xa800; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  qsort(&g_PhonemeTable,g_nPhonemeCount,8,FUN_00490e50);
  UINT_008ca76c = 1;
  return 0;
}

/* ---- 0x00490ef0  FUN_00490ef0 ---- */
void FUN_00490ef0(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < g_nActorCapacity) {
    iVar1 = 0;
    do {
      Actor_Destroy((void *)((int)g_pActorTable + iVar1));
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0xa8;
    } while (iVar2 < g_nActorCapacity);
  }
  if (g_pActorTable != (void *)0x0) {
    (**(code **)(UINT_008ca32c + 0x24))(g_pActorTable);
  }
  UINT_008ca76c = 0;
  return;
}
