/* LUA.DLL :: getlcidfromcountryonly.c
 * functions 0x10018300 .. 0x10018340 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10018300  GetLcidFromCountryOnly ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void GetLcidFromCountryOnly(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  iVar2 = -1;
  pcVar3 = DAT_1002c230;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  DAT_1002c220 = (uint)(iVar2 == -5);
  EnumSystemLocalesA(((unsigned)(uintptr_t)FUN_10018340),1);
  if ((DAT_1002c234 & 4) == 0) {
    DAT_1002c234 = 0;
  }
  return;
}

/* ---- 0x10018340  FUN_10018340 ---- */
undefined4 __stdcall FUN_10018340(int a1)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  #define iStack_88 (*(int *)(_frame + (0xa0 - 0x88)))
  #define puStack_84 (*(undefined1 **)(_frame + (0xa0 - 0x84)))
  #define local_78 (*(undefined1 (*)[120])(_frame + (0xa0 - 0x78)))
  
  puStack_84 = (undefined1 *)0x1001834e;
  iVar1 = FUN_10018720((char *)a1);
  puStack_84 = local_78;
  iStack_88 = (-(uint)(DAT_1002c220 != 0) & 0xfffff005) + 0x1002;
  iVar2 = (*DAT_1002c23c)(iVar1);
  if (iVar2 == 0) {
    DAT_1002c234 = iVar2;
    return 1;
  }
  uVar3 = _stricmp(DAT_1002c230,(byte *)&iStack_88);
  if (uVar3 == 0) {
    iVar2 = FUN_100184f0((short)iVar1);
    if (iVar2 != 0) {
      DAT_1002c234 = DAT_1002c234 | 4;
      DAT_1002c21c = iVar1;
      DAT_1002c238 = iVar1;
    }
  }
  return ~DAT_1002c234 >> 2 & 1;
}
#undef iStack_88
#undef local_78
#undef puStack_84

