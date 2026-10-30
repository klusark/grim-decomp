/* LUA.DLL :: getlcidfromlanguage.c
 * functions 0x100181c0 .. 0x10018220 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100181c0  GetLcidFromLanguage ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void GetLcidFromLanguage(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  iVar2 = -1;
  pcVar3 = DAT_1002c22c;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  DAT_1002c228 = (uint)(iVar2 == -5);
  if (DAT_1002c228 == 0) {
    DAT_1002c224 = FUN_10018760(DAT_1002c22c);
  }
  else {
    DAT_1002c224 = 2;
  }
  EnumSystemLocalesA(((unsigned)(uintptr_t)FUN_10018220),1);
  if ((DAT_1002c234 & 4) == 0) {
    DAT_1002c234 = 0;
  }
  return;
}
#endif


/* ---- 0x10018220  FUN_10018220 ---- */
undefined4 __stdcall FUN_10018220(int a1)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  #define iStack_88 (*(int *)(_frame + (0xa0 - 0x88)))
  #define puStack_84 (*(undefined1 **)(_frame + (0xa0 - 0x84)))
  #define local_78 (*(undefined1 (*)[120])(_frame + (0xa0 - 0x78)))
  
  puStack_84 = (undefined1 *)0x1001822e;
  iVar1 = FUN_10018720((char *)a1);
  puStack_84 = local_78;
  iStack_88 = (-(uint)(DAT_1002c228 != 0) & 0xfffff002) + 0x1001;
  iVar2 = (*DAT_1002c23c)(iVar1);
  if (iVar2 == 0) {
    DAT_1002c234 = iVar2;
    return 1;
  }
  uVar3 = _stricmp(DAT_1002c22c,(byte *)&iStack_88);
  if (uVar3 == 0) {
    if (DAT_1002c228 == 0) {
      iVar2 = FUN_10018520(iVar1);
      goto joined_r0x100182d0;
    }
  }
  else {
    if (((DAT_1002c228 != 0) || (DAT_1002c224 == 0)) ||
       (iVar2 = _strnicmp(DAT_1002c22c,(char *)&iStack_88,DAT_1002c224), iVar2 != 0))
    goto LAB_100182ea;
    iVar2 = FUN_10018520(iVar1);
joined_r0x100182d0:
    if (iVar2 == 0) goto LAB_100182ea;
  }
  DAT_1002c234 = DAT_1002c234 | 4;
  DAT_1002c21c = iVar1;
  DAT_1002c238 = iVar1;
LAB_100182ea:
  return ~DAT_1002c234 >> 2 & 1;
}
#undef iStack_88
#undef local_78
#undef puStack_84

