/* LUA.DLL :: translatename.c
 * functions 0x10018400 .. 0x10018760 (7 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10018400  TranslateName ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl TranslateName(byte *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  bool bVar5;
  #define local_8 (*(byte (*)[8])(_frame + (0x20 - 0x8)))
  
  if ((param_1 == (byte *)0x0) || (*param_1 == 0)) {
LAB_100184ac:
    iVar3 = (*DAT_1002c23c)(DAT_1002c238,0x1004,local_8,8);
    if (iVar3 == 0) {
      return 0;
    }
  }
  else {
    pbVar4 = &DAT_10024950;
    pbVar2 = param_1;
    do {
      bVar1 = *pbVar2;
      bVar5 = bVar1 < *pbVar4;
      if (bVar1 != *pbVar4) {
LAB_1001844a:
        iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
        goto LAB_1001844f;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar5 = bVar1 < pbVar4[1];
      if (bVar1 != pbVar4[1]) goto LAB_1001844a;
      pbVar2 = pbVar2 + 2;
      pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_1001844f:
    if (iVar3 == 0) goto LAB_100184ac;
    pbVar4 = &DAT_1002494c;
    pbVar2 = param_1;
    do {
      bVar1 = *pbVar2;
      bVar5 = bVar1 < *pbVar4;
      if (bVar1 != *pbVar4) {
LAB_10018482:
        iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
        goto LAB_10018487;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar5 = bVar1 < pbVar4[1];
      if (bVar1 != pbVar4[1]) goto LAB_10018482;
      pbVar2 = pbVar2 + 2;
      pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_10018487:
    if (iVar3 != 0) goto LAB_100184d3;
    iVar3 = (*DAT_1002c23c)(DAT_1002c238,0xb,local_8,8);
    if (iVar3 == 0) {
      return 0;
    }
  }
  param_1 = local_8;
LAB_100184d3:
  iVar3 = atol(param_1);
  return iVar3;
}
#undef local_8


/* ---- 0x100184f0  FUN_100184f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_100184f0(short param_1)

{
  short *psVar1;
  
  psVar1 = &DAT_100290e0;
  do {
    if (param_1 == *psVar1) {
      return 0;
    }
    psVar1 = psVar1 + 1;
  } while (psVar1 < &DAT_100290f4);
  return 1;
}
#endif


/* ---- 0x10018520  FUN_10018520 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_10018520(int param_1)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  #define puStack_88 (*(undefined1 **)(_frame + (0xa0 - 0x88)))
  #define uStack_84 (*(undefined4 *)(_frame + (0xa0 - 0x84)))
  #define local_78 (*(undefined1 (*)[112])(_frame + (0xa0 - 0x78)))
  #define iStack_8 (*(int *)(_frame + (0xa0 - 0x8)))
  
  puStack_88 = local_78;
  uStack_84 = 0x78;
  iVar2 = (*DAT_1002c23c)((ushort)param_1 & 0x3ff | 0x400,1);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = FUN_10018720((char *)&puStack_88);
  if ((param_1 != iVar2) && (iStack_8 != 0)) {
    iVar2 = FUN_10018760(DAT_1002c22c);
    uVar3 = 0xffffffff;
    pcVar4 = DAT_1002c22c;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    if (iVar2 == ~uVar3 - 1) {
      return 0;
    }
  }
  return 1;
}
#undef iStack_8
#undef local_78
#undef puStack_88
#undef uStack_84

#endif


/* ---- 0x100185b0  FUN_100185b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_100185b0(void)

{
  unsigned char _frame[0xb0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_94 (*(undefined4 (*)[4])(_frame + (0xb0 - 0x94)))
  #define iStack_84 (*(int *)(_frame + (0xb0 - 0x84)))
  
  local_94[0] = 0x94;
  iVar1 = GetVersionExA((int)local_94);
  if ((iVar1 != 0) && (iStack_84 == 2)) {
    return 1;
  }
  return 0;
}
#undef iStack_84
#undef local_94

#endif


/* ---- 0x100185f0  FUN_100185f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __stdcall FUN_100185f0(int a1,int a2,int a3,int a4)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 0;
  iVar5 = 0x1a;
  puVar3 = (uint *)0x0;
  do {
    iVar2 = (iVar5 + iVar4) / 2;
    uVar1 = *(uint *)(iVar2 * 0x2c + ((unsigned)(uintptr_t)&DAT_100290f8));
    if (a1 == uVar1) {
      if ((uint)a2 < 8) {
        if (a2 == 7) {
          puVar3 = (uint *)(iVar2 * 0x2c + ((unsigned)(uintptr_t)&DAT_10029110));
        }
        else if (a2 == 1) {
          puVar3 = (uint *)(iVar2 * 0x2c + ((unsigned)(uintptr_t)&DAT_100290fc));
        }
        else if (a2 == 3) {
          puVar3 = (uint *)(iVar2 * 0x2c + ((unsigned)(uintptr_t)&DAT_10029108));
        }
      }
      else if ((uint)a2 < 0x1002) {
        if (a2 == 0x1001) {
          puVar3 = *(uint **)(iVar2 * 0x2c + ((unsigned)(uintptr_t)&DAT_10029104));
        }
        else if (a2 == 0xb) {
          puVar3 = (uint *)(iVar2 * 0x2c + ((unsigned)(uintptr_t)&DAT_10029114));
        }
      }
      else if (a2 == 0x1002) {
        puVar3 = *(uint **)(iVar2 * 0x2c + ((unsigned)(uintptr_t)&DAT_1002910c));
      }
      else if (a2 == 0x1004) {
        puVar3 = (uint *)(iVar2 * 0x2c + ((unsigned)(uintptr_t)&DAT_1002911c));
      }
      if ((puVar3 != (uint *)0x0) && (0 < a4)) {
        strncpy((uint *)a3,puVar3,a4 - 1);
        *(undefined1 *)(a4 + -1 + a3) = 0;
        return 1;
      }
      break;
    }
    if ((uint)a1 < uVar1) {
      iVar5 = iVar2 + -1;
    }
    else {
      iVar4 = iVar2 + 1;
    }
  } while (iVar4 <= iVar5);
  iVar5 = GetLocaleInfoA(a1,a2,a3,a4);
  return iVar5;
}
#endif


/* ---- 0x10018720  FUN_10018720 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_10018720(char *param_1)

{
  int iVar1;
  char cVar2;
  
  iVar1 = 0;
  cVar2 = *param_1;
  while (cVar2 != '\0') {
    param_1 = param_1 + 1;
    if ((cVar2 < 'a') || ('f' < cVar2)) {
      if (('@' < cVar2) && (cVar2 < 'G')) {
        cVar2 = cVar2 + -7;
      }
    }
    else {
      cVar2 = cVar2 + -0x27;
    }
    iVar1 = (iVar1 + 0xffffffd) * 0x10 + (int)cVar2;
    cVar2 = *param_1;
  }
  return iVar1;
}
#endif


/* ---- 0x10018760  FUN_10018760 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_10018760(char *param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    if (((cVar1 < 'A') || ('Z' < cVar1)) && ((cVar1 < 'a' || ('z' < cVar1)))) break;
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}
#endif

