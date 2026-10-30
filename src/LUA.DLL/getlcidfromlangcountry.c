/* LUA.DLL :: getlcidfromlangcountry.c
 * functions 0x10017e50 .. 0x10017ee0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10017e50  GetLcidFromLangCountry ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void GetLcidFromLangCountry(void)

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
  iVar2 = -1;
  pcVar3 = DAT_1002c230;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  DAT_1002c220 = (uint)(iVar2 == -5);
  DAT_1002c21c = 0;
  if (DAT_1002c228 == 0) {
    DAT_1002c224 = FUN_10018760(DAT_1002c22c);
  }
  else {
    DAT_1002c224 = 2;
  }
  EnumSystemLocalesA(((unsigned)(uintptr_t)FUN_10017ee0),1);
  if ((((DAT_1002c234 & 0x100) == 0) || ((DAT_1002c234 & 0x200) == 0)) || ((DAT_1002c234 & 7) == 0))
  {
    DAT_1002c234 = 0;
  }
  return;
}
#endif


/* ---- 0x10017ee0  FUN_10017ee0 ---- */
undefined4 __stdcall FUN_10017ee0(int a1)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[176] __attribute__((aligned(16)));  /* the original frame below the return address */
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  #define puStack_88 (*(undefined1 **)(_frame + (0xa0 - 0x88)))
  #define local_78 (*(undefined1 (*)[120])(_frame + (0xa0 - 0x78)))
  
  puStack_88 = (undefined1 *)0x10017eef;
  iVar2 = FUN_10018720((char *)a1);
  puStack_88 = local_78;
  iVar3 = (*DAT_1002c23c)();
  if (iVar3 == 0) {
    DAT_1002c234 = iVar3;
    return 1;
  }
  uVar4 = _stricmp(DAT_1002c230,(byte *)&puStack_88);
  if (uVar4 == 0) {
    iVar3 = (*DAT_1002c23c)(iVar2,(-(uint)(DAT_1002c228 != 0) & 0xfffff002) + 0x1001);
    if (iVar3 == 0) {
      DAT_1002c234 = iVar3;
      return 1;
    }
    uVar4 = _stricmp(DAT_1002c22c,(byte *)&puStack_88);
    if (uVar4 == 0) {
      DAT_1002c234 = DAT_1002c234 | 0x304;
      DAT_1002c21c = iVar2;
      DAT_1002c238 = iVar2;
    }
    else if ((DAT_1002c234 & 2) == 0) {
      if ((DAT_1002c224 == 0) ||
         (iVar3 = _strnicmp(DAT_1002c22c,(char *)&puStack_88,DAT_1002c224), iVar3 != 0)) {
        if (((DAT_1002c234 & 1) == 0) && (iVar3 = FUN_100184f0((short)iVar2), iVar3 != 0)) {
          DAT_1002c234 = DAT_1002c234 | 1;
          DAT_1002c238 = iVar2;
        }
      }
      else {
        DAT_1002c234 = DAT_1002c234 | 2;
        uVar4 = 0xffffffff;
        pbVar5 = DAT_1002c22c;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          bVar1 = *pbVar5;
          pbVar5 = pbVar5 + 1;
        } while (bVar1 != 0);
        DAT_1002c238 = iVar2;
        if (~uVar4 - 1 == DAT_1002c224) {
          DAT_1002c21c = iVar2;
        }
      }
    }
  }
  if ((DAT_1002c234 & 0x300) == 0x300) goto LAB_1001819e;
  iVar3 = (*DAT_1002c23c)(iVar2,(-(uint)(DAT_1002c228 != 0) & 0xfffff002) + 0x1001);
  if (iVar3 == 0) {
    DAT_1002c234 = iVar3;
    return 1;
  }
  uVar4 = _stricmp(DAT_1002c22c,(_stkneg + 24));
  if (uVar4 == 0) {
    if (DAT_1002c228 == 0) {
      if (DAT_1002c224 != 0) {
        uVar4 = 0xffffffff;
        pbVar5 = DAT_1002c22c;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          bVar1 = *pbVar5;
          pbVar5 = pbVar5 + 1;
        } while (bVar1 != 0);
        if (~uVar4 - 1 == DAT_1002c224) {
          DAT_1002c234 = DAT_1002c234 | 0x200;
          iVar3 = FUN_10018520(iVar2);
          if (iVar3 == 0) goto LAB_1001819e;
          goto joined_r0x10018129;
        }
      }
      DAT_1002c234 = DAT_1002c234 | 0x300;
    }
    else {
      DAT_1002c234 = CONCAT22((short)(DAT_1002c234 >> 0x10),
                              CONCAT11((char)((DAT_1002c234 | 0x200) >> 8),(char)DAT_1002c234));
joined_r0x10018129:
      DAT_1002c234 = DAT_1002c234 | 0x100;
    }
  }
  else {
    if ((((DAT_1002c228 != 0) || (DAT_1002c224 == 0)) ||
        (iVar3 = _strnicmp(DAT_1002c22c,(_stkneg + 24),DAT_1002c224), iVar3 != 0)) ||
       (iVar3 = FUN_10018520(iVar2), iVar3 == 0)) goto LAB_1001819e;
    DAT_1002c234 = DAT_1002c234 | 0x100;
  }
  if (DAT_1002c21c == 0) {
    DAT_1002c21c = iVar2;
  }
LAB_1001819e:
  return ~DAT_1002c234 >> 2 & 1;
}
#undef local_78
#undef puStack_88

