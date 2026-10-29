/* LUA.DLL :: setsbuplow.c
 * functions 0x1001cf20 .. 0x1001cf20 (1 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1001cf20  setSBUpLow ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void setSBUpLow(void)

{
  unsigned char _frame[0x530] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  ushort *puVar6;
  char *pcVar7;
  #define local_514 (*(undefined1 (*)[6])(_frame + (0x530 - 0x514)))
  #define bStack_50e (*(byte *)(_frame + (0x530 - 0x50e)))
  #define abStack_50d (*(byte (*)[13])(_frame + (0x530 - 0x50d)))
  #define acStack_500 (*(char (*)[256])(_frame + (0x530 - 0x500)))
  #define auStack_400 (*(undefined1 (*)[256])(_frame + (0x530 - 0x400)))
  #define auStack_300 (*(undefined1 (*)[256])(_frame + (0x530 - 0x300)))
  #define auStack_200 (*(ushort (*)[256])(_frame + (0x530 - 0x200)))
  
  iVar1 = GetCPInfo(DAT_1002c570,(int)local_514);
  if (iVar1 == 1) {
    uVar2 = 0;
    do {
      acStack_500[uVar2] = (char)uVar2;
      uVar2 = uVar2 + 1;
    } while (uVar2 < 0x100);
    acStack_500[0] = ' ';
    if (bStack_50e != 0) {
      pbVar5 = abStack_50d;
      do {
        uVar2 = (uint)bStack_50e;
        if (uVar2 <= *pbVar5) {
          uVar3 = (*pbVar5 - uVar2) + 1;
          uVar4 = uVar3 >> 2;
          pcVar7 = acStack_500 + uVar2;
          while (uVar4 != 0) {
            uVar4 = uVar4 - 1;
            builtin_strncpy(pcVar7,"    ",4);
            pcVar7 = pcVar7 + 4;
          }
          for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
            *pcVar7 = ' ';
            pcVar7 = pcVar7 + 1;
          }
        }
        bStack_50e = pbVar5[1];
        pbVar5 = pbVar5 + 2;
      } while (bStack_50e != 0);
    }
    __crtGetStringTypeA(1,acStack_500,0x100,auStack_200,DAT_1002c570,DAT_1002c574,0);
    __crtLCMapStringA(DAT_1002c574,0x100,acStack_500,0x100,auStack_400,0x100,DAT_1002c570,0);
    __crtLCMapStringA(DAT_1002c574,0x200,acStack_500,0x100,auStack_300,0x100,DAT_1002c570,0);
    uVar2 = 0;
    puVar6 = auStack_200;
    do {
      if ((*puVar6 & 1) == 0) {
        if ((*puVar6 & 2) == 0) {
          (&DAT_1002c470)[uVar2] = 0;
        }
        else {
          *(byte *)((int)&DAT_1002c368 + uVar2 + 1) =
               *(byte *)((int)&DAT_1002c368 + uVar2 + 1) | 0x20;
          (&DAT_1002c470)[uVar2] = auStack_300[uVar2];
        }
      }
      else {
        *(byte *)((int)&DAT_1002c368 + uVar2 + 1) = *(byte *)((int)&DAT_1002c368 + uVar2 + 1) | 0x10
        ;
        (&DAT_1002c470)[uVar2] = auStack_400[uVar2];
      }
      uVar2 = uVar2 + 1;
      puVar6 = puVar6 + 1;
    } while (uVar2 < 0x100);
    return;
  }
  uVar2 = 0;
  do {
    if ((uVar2 < 0x41) || (0x5a < uVar2)) {
      if ((uVar2 < 0x61) || (0x7a < uVar2)) {
        (&DAT_1002c470)[uVar2] = 0;
      }
      else {
        *(byte *)((int)&DAT_1002c368 + uVar2 + 1) = *(byte *)((int)&DAT_1002c368 + uVar2 + 1) | 0x20
        ;
        (&DAT_1002c470)[uVar2] = (char)uVar2 + -0x20;
      }
    }
    else {
      *(byte *)((int)&DAT_1002c368 + uVar2 + 1) = *(byte *)((int)&DAT_1002c368 + uVar2 + 1) | 0x10;
      (&DAT_1002c470)[uVar2] = (char)uVar2 + ' ';
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x100);
  return;
}
#undef abStack_50d
#undef acStack_500
#undef auStack_200
#undef auStack_300
#undef auStack_400
#undef bStack_50e
#undef local_514

