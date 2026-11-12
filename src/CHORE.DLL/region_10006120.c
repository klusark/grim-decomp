/* CHORE.DLL :: region_10006120.c
 * functions 0x10006120 .. 0x100084d0 (49 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10006120  FUN_10006120 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10006120(undefined4 param_1)

{
  if ((_DAT_10014408 == 1) || ((_DAT_10014408 == 0 && (_DAT_1001440c == 1)))) {
    FUN_100089a0();
  }
  FUN_100089e0(param_1);
  (*_DAT_100106c0)(0xff);
  return;
}
#endif


/* ---- 0x10006160  FUN_10006160 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10006160(void)

{
  FUN_10008c00(0x10000,0x30000);
  return;
}
#endif


/* ---- 0x100061d0  FUN_100061d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Removing unreachable block (ram,0x100061c1) */

undefined4 FUN_100061d0(void)

{
  int a1;
  code *pcVar1;
  undefined4 uVar2;
  
  a1 = GetModuleHandleA(&UNK_1000e0fc);
  if ((a1 != 0) && (pcVar1 = (code *)GetProcAddress(a1,((unsigned)(uintptr_t)&DAT_1000e0e0)), pcVar1 != (code *)0x0)) {
    uVar2 = (*pcVar1)(0);
    return uVar2;
  }
  return 0;
}
#endif


/* ---- 0x10006200  FUN_10006200 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10006200(char *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = FUN_100069a0((int)*param_1);
  if (iVar3 != 0x65) {
    do {
      param_1 = param_1 + 1;
      if (_DAT_10010ac8 < 2) {
        uVar4 = *(byte *)(_DAT_10010ad8 + *param_1 * 2) & 4;
      }
      else {
        uVar4 = FUN_10008d50((int)*param_1,4);
      }
    } while (uVar4 != 0);
  }
  cVar2 = *param_1;
  *param_1 = DAT_10010acc;
  do {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    *param_1 = cVar2;
    cVar2 = cVar1;
  } while (*param_1 != '\0');
  return;
}
#endif


/* ---- 0x10006260  FUN_10006260 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10006260(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  
  cVar1 = *param_1;
  while ((cVar1 != '\0' && (cVar1 != DAT_10010acc))) {
    pcVar2 = param_1 + 1;
    param_1 = param_1 + 1;
    cVar1 = *pcVar2;
  }
  pcVar2 = param_1 + 1;
  if (*param_1 != '\0') {
    cVar1 = *pcVar2;
    while (((cVar1 != '\0' && (cVar1 != 'e')) && (cVar1 != 'E'))) {
      pcVar3 = pcVar2 + 1;
      pcVar2 = pcVar2 + 1;
      cVar1 = *pcVar3;
    }
    cVar1 = pcVar2[-1];
    pcVar3 = pcVar2;
    while (pcVar4 = pcVar3 + -1, cVar1 == '0') {
      cVar1 = pcVar3[-2];
      pcVar3 = pcVar4;
    }
    if (*pcVar4 == DAT_10010acc) {
      pcVar4 = pcVar3 + -2;
    }
    cVar1 = *pcVar2;
    pcVar4 = pcVar4 + 1;
    *pcVar4 = cVar1;
    while (cVar1 != '\0') {
      pcVar2 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar4 = pcVar4 + 1;
      *pcVar4 = cVar1;
    }
  }
  return;
}
#endif


/* ---- 0x100062d0  FUN_100062d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_100062d0(double *param_1)

{
  if (0.0 <= *param_1) {
    return 1;
  }
  return 0;
}
#endif


/* ---- 0x100062f0  FUN_100062f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100062f0(int param_1,undefined4 *param_2,undefined4 param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define uStack_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  if (param_1 != 0) {
    FUN_10009290(&uStack_8,param_3);
    *param_2 = uStack_8;
    param_2[1] = uStack_4;
    return;
  }
  FUN_100092d0(&param_3,param_3);
  *param_2 = param_3;
  return;
}
#undef uStack_4
#undef uStack_8

#endif


/* ---- 0x10006350  FUN_10006350 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_10006350(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define aiStack_28 (*(int (*)[4])(_frame + (0x40 - 0x28)))
  #define auStack_18 (*(undefined1 (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_100093b0(*param_1,param_1[1],aiStack_28,auStack_18);
  ((code *)FUN_10009310)((uint)(aiStack_28[0] == 0x2d) + param_2 + (uint)(0 < param_3),param_3 + 1,aiStack_28)
  ;
  FUN_100063d0(param_2,param_3,param_4,aiStack_28,0);
  return param_2;
}
#undef aiStack_28
#undef auStack_18

#endif


/* ---- 0x100063d0  FUN_100063d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined1 * FUN_100063d0(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (param_5 != '\0') {
    FUN_10006730(param_1 + (*param_4 == 0x2d),0 < param_2);
  }
  puVar1 = param_1;
  if (*param_4 == 0x2d) {
    *param_1 = 0x2d;
    puVar1 = param_1 + 1;
  }
  if (0 < param_2) {
    *puVar1 = puVar1[1];
    puVar1 = puVar1 + 1;
    *puVar1 = DAT_10010acc;
  }
  puVar3 = (undefined4 *)(puVar1 + param_2 + (uint)(param_5 == '\0'));
  *puVar3 = 0x30302b65;
  *(undefined2 *)(puVar3 + 1) = 0x30;
  if (param_3 != 0) {
    *(undefined1 *)puVar3 = 0x45;
  }
  if (*(char *)param_4[3] != '0') {
    iVar2 = param_4[1] + -1;
    if (iVar2 < 0) {
      iVar2 = -iVar2;
      *(undefined1 *)((int)puVar3 + 1) = 0x2d;
    }
    if (99 < iVar2) {
      *(char *)((int)puVar3 + 2) =
           *(char *)((int)puVar3 + 2) +
           (((char)(iVar2 / 100) + (char)(iVar2 >> 0x1f)) -
           (char)((longlong)iVar2 * 0x51eb851f >> 0x3f));
      iVar2 = iVar2 % 100;
    }
    if (9 < iVar2) {
      *(char *)((int)puVar3 + 3) =
           *(char *)((int)puVar3 + 3) +
           (((char)(iVar2 / 10) + (char)(iVar2 >> 0x1f)) -
           (char)((longlong)iVar2 * 0x66666667 >> 0x3f));
      iVar2 = iVar2 % 10;
    }
    *(char *)(puVar3 + 1) = *(char *)(puVar3 + 1) + (char)iVar2;
  }
  return param_1;
}
#endif


/* ---- 0x100064d0  FUN_100064d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_100064d0(undefined4 *param_1,int param_2,int param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define iStack_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define iStack_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define auStack_18 (*(undefined1 (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_100093b0(*param_1,param_1[1],&iStack_28,auStack_18);
  FUN_10009310((uint)(iStack_28 == 0x2d) + param_2,iStack_24 + param_3,&iStack_28);
  FUN_10006540(param_2,param_3,&iStack_28,0);
  return param_2;
}
#undef auStack_18
#undef iStack_24
#undef iStack_28

#endif


/* ---- 0x10006540  FUN_10006540 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined1 * FUN_10006540(undefined1 *param_1,uint param_2,int *param_3,char param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  
  iVar1 = param_3[1];
  uVar3 = iVar1 - 1;
  if ((param_4 != '\0') && (iVar2 = *param_3, uVar3 == param_2)) {
    param_1[uVar3 + (iVar2 == 0x2d)] = 0x30;
    param_1[iVar1 + (uint)(iVar2 == 0x2d)] = 0;
  }
  puVar4 = param_1;
  if (*param_3 == 0x2d) {
    *param_1 = 0x2d;
    puVar4 = param_1 + 1;
  }
  if (param_3[1] < 1) {
    FUN_10006730(puVar4,1);
    *puVar4 = 0x30;
    puVar4 = puVar4 + 1;
  }
  else {
    puVar4 = puVar4 + param_3[1];
  }
  if (0 < (int)param_2) {
    FUN_10006730(puVar4,1);
    *puVar4 = DAT_10010acc;
    iVar1 = param_3[1];
    if (iVar1 < 0) {
      if ((param_4 != '\0') || (-iVar1 <= (int)param_2)) {
        param_2 = -iVar1;
      }
      FUN_10006730(puVar4 + 1,param_2);
      puVar5 = (undefined4 *)(puVar4 + 1);
      for (uVar3 = param_2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar5 = 0x30303030;
        puVar5 = puVar5 + 1;
      }
      for (param_2 = param_2 & 3; param_2 != 0; param_2 = param_2 - 1) {
        *(undefined1 *)puVar5 = 0x30;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
    }
  }
  return param_1;
}
#endif


/* ---- 0x10006600  FUN_10006600 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10006600(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  char cVar2;
  char *pcVar3;
  #define iStack_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define iStack_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define auStack_18 (*(undefined1 (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_100093b0(*param_1,param_1[1],&iStack_28,auStack_18);
  iVar1 = iStack_24 + -1;
  pcVar3 = (char *)((uint)(iStack_28 == 0x2d) + param_2);
  FUN_10009310(pcVar3,param_3,&iStack_28);
  iStack_24 = iStack_24 + -1;
  if ((-5 < iStack_24) && (iStack_24 < param_3)) {
    if (iVar1 < iStack_24) {
      cVar2 = *pcVar3;
      while (cVar2 != '\0') {
        cVar2 = pcVar3[1];
        pcVar3 = pcVar3 + 1;
      }
      pcVar3[-1] = '\0';
    }
    FUN_10006540(param_2,param_3,&iStack_28,1);
    return;
  }
  FUN_100063d0(param_2,param_3,param_4,&iStack_28,1);
  return;
}
#undef auStack_18
#undef iStack_24
#undef iStack_28

#endif


/* ---- 0x100066c0  FUN_100066c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100066c0(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                 undefined4 param_5)

{
  if ((param_3 != 0x65) && (param_3 != 0x45)) {
    if (param_3 == 0x66) {
      FUN_100064d0(param_1,param_2,param_4);
      return;
    }
    FUN_10006600(param_1,param_2,param_4,param_5);
    return;
  }
  FUN_10006350(param_1,param_2,param_4,param_5);
  return;
}
#endif


/* ---- 0x10006730  FUN_10006730 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10006730(char *param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  if (param_2 != 0) {
    uVar2 = 0xffffffff;
    pcVar3 = param_1;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    msvc_memmove(param_1 + param_2,param_1,~uVar2);
  }
  return;
}
#endif


/* ---- 0x10006760  FUN_10006760 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10006760(void)

{
  InitializeCriticalSection(_DAT_10010724);
  InitializeCriticalSection(_DAT_10010714);
  InitializeCriticalSection(_DAT_10010704);
  InitializeCriticalSection(_DAT_100106e4);
  return;
}
#endif


/* ---- 0x10006790  FUN_10006790 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10006790(void)

{
  int *piVar1;
  
  piVar1 = (int *)((unsigned)(uintptr_t)&DAT_100106e0);
  do {
    if ((((*piVar1 != 0) && (piVar1 != (int *)&DAT_10010724)) && (piVar1 != (int *)&DAT_10010714))
       && ((piVar1 != (int *)&DAT_10010704 && (piVar1 != (int *)&DAT_100106e4)))) {
      DeleteCriticalSection(*piVar1);
      FUN_10009510();
    }
    piVar1 = piVar1 + 1;
  } while ((int)piVar1 < ((unsigned)(uintptr_t)&DAT_100107a0));
  DeleteCriticalSection(_DAT_10010704);
  DeleteCriticalSection(_DAT_10010714);
  DeleteCriticalSection(_DAT_10010724);
  DeleteCriticalSection(_DAT_100106e4);
  return;
}
#endif


/* ---- 0x10006810  FUN_10006810 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10006810(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 * 4 + ((unsigned)(uintptr_t)&DAT_100106e0)) == 0) {
    iVar1 = FUN_10009580(0x18);
    if (iVar1 == 0) {
      FUN_10006120(0x11);
    }
    FUN_10006810(0x11);
    if (*(int *)(param_1 * 4 + ((unsigned)(uintptr_t)&DAT_100106e0)) == 0) {
      InitializeCriticalSection(iVar1);
      *(int *)(param_1 * 4 + ((unsigned)(uintptr_t)&DAT_100106e0)) = iVar1;
    }
    else {
      FUN_10009510();
    }
    FUN_10006890();
  }
  EnterCriticalSection(*(undefined4 *)(param_1 * 4 + ((unsigned)(uintptr_t)&DAT_100106e0)));
  return;
}
#endif


/* ---- 0x10006890  FUN_10006890 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FUN_10006890(void)

{
  int iVar1;
  int in_stack_00000004;
  
  iVar1 = LeaveCriticalSection(*(undefined4 *)(in_stack_00000004 * 4 + ((unsigned)(uintptr_t)&DAT_100106e0)));
  return iVar1;
}
#endif


/* ---- 0x100068b0  FUN_100068b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100068b0(uint param_1)

{
  if ((((unsigned)(uintptr_t)&DAT_10010d17) < param_1) && (param_1 < ((unsigned)(uintptr_t)&DAT_10010f79))) {
    FUN_10006810(((int)(param_1 + 0xeffef2e8) >> 5) + 0x1c);
    return;
  }
  EnterCriticalSection(param_1 + 0x20);
  return;
}
#endif


/* ---- 0x100068f0  FUN_100068f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100068f0(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    FUN_10006810(param_1 + 0x1c);
    return;
  }
  EnterCriticalSection(param_2 + 0x20);
  return;
}
#endif


/* ---- 0x10006920  FUN_10006920 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10006920(uint param_1)

{
  if ((((unsigned)(uintptr_t)&DAT_10010d17) < param_1) && (param_1 < ((unsigned)(uintptr_t)&DAT_10010f79))) {
    FUN_10006890();
    return;
  }
  LeaveCriticalSection(param_1 + 0x20);
  return;
}
#endif


/* ---- 0x10006960  FUN_10006960 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10006960(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    FUN_10006890();
    return;
  }
  LeaveCriticalSection(param_2 + 0x20);
  return;
}
#endif


/* ---- 0x10006990  FUN_10006990 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10006990(void)

{
  return 0;
}
#endif


/* ---- 0x100069a0  FUN_100069a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_100069a0(int param_1)

{
  bool bVar1;
  
  if (_DAT_10014478 == 0) {
    if ((0x40 < param_1) && (param_1 < 0x5b)) {
      return param_1 + 0x20;
    }
  }
  else {
    InterlockedIncrement(((unsigned)(uintptr_t)&DAT_10015af0));
    bVar1 = _DAT_10015aec != 0;
    if (bVar1) {
      InterlockedDecrement(((unsigned)(uintptr_t)&DAT_10015af0));
      FUN_10006810(0x13);
    }
    param_1 = FUN_10006a30(param_1);
    if (bVar1) {
      FUN_10006890();
      return param_1;
    }
    InterlockedDecrement(((unsigned)(uintptr_t)&DAT_10015af0));
  }
  return param_1;
}
#endif


/* ---- 0x10006a30  FUN_10006a30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_10006a30(uint param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  #define auStack_8 (*(uint (*)[2])(_frame + (0x20 - 0x8)))
  
  uVar1 = param_1;
  if (_DAT_10014478 == 0) {
    if ((0x40 < (int)param_1) && ((int)param_1 < 0x5b)) {
      return param_1 + 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if (_DAT_10010ac8 < 2) {
        uVar2 = *(byte *)(_DAT_10010ad8 + param_1 * 2) & 1;
      }
      else {
        uVar2 = FUN_10008d50(param_1,1);
      }
      if (uVar2 == 0) {
        return uVar1;
      }
    }
    uVar2 = param_1;
    if ((*(byte *)(_DAT_10010ad8 + 1 + ((int)uVar1 >> 8 & 0xffU) * 2) & 0x80) == 0) {
      PIECE(param_1,0,2) = (ushort)(byte)uVar1;
      uVar3 = 1;
    }
    else {
      PIECE(param_1,0,2) = CONCAT11((byte)uVar1,(char)(uVar1 >> 8));
      PIECE(param_1,3,1) = SUB41(uVar2,3);
      PIECE(param_1,0,3) = (uint3)(ushort)param_1;
      uVar3 = 2;
    }
    iVar4 = FUN_1000a710(_DAT_10014478,0x100,&param_1,uVar3,auStack_8,3,0,1);
    if (iVar4 == 0) {
      return uVar1;
    }
    if (iVar4 == 1) {
      return auStack_8[0] & 0xff;
    }
    param_1 = (auStack_8[0] >> 8 & 0xff) << 8 | auStack_8[0] & 0xff;
  }
  return param_1;
}
#undef auStack_8

#endif


/* ---- 0x10006b30  FUN_10006b30 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_10006b30(undefined4 param_1,byte *param_2,undefined4 *param_3)

{
  unsigned char _frame[0x1e0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte bVar2;
  undefined4 *puVar3;
  uint *puVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  uint uVar10;
  byte bVar11;
  byte *pbVar12;
  int iVar13;
  byte *pbVar14;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint extraout_EDX_01;
  uint *puVar15;
  char *pcVar16;
  char *pcVar17;
  uint *puVar18;
  uint a2;
  bool bVar19;
  bool bVar20;
  #define cStack_1cd (*(char *)(_frame + (0x1e0 - 0x1cd)))
  #define uStack_1cc (*(uint *)(_frame + (0x1e0 - 0x1cc)))
  #define cStack_1c7 (*(char *)(_frame + (0x1e0 - 0x1c7)))
  #define cStack_1c6 (*(char *)(_frame + (0x1e0 - 0x1c6)))
  #define cStack_1c5 (*(char *)(_frame + (0x1e0 - 0x1c5)))
  #define iStack_1c4 (*(int *)(_frame + (0x1e0 - 0x1c4)))
  #define cStack_1c0 (*(char *)(_frame + (0x1e0 - 0x1c0)))
  #define cStack_1bf (*(char *)(_frame + (0x1e0 - 0x1bf)))
  #define cStack_1be (*(char *)(_frame + (0x1e0 - 0x1be)))
  #define bStack_1bd (*(byte *)(_frame + (0x1e0 - 0x1bd)))
  #define uStack_1bc (*(uint *)(_frame + (0x1e0 - 0x1bc)))
  #define puStack_1b8 (*(uint **)(_frame + (0x1e0 - 0x1b8)))
  #define uStack_1b4 (*(uint *)(_frame + (0x1e0 - 0x1b4)))
  #define iStack_1b0 (*(int *)(_frame + (0x1e0 - 0x1b0)))
  #define iStack_1ac (*(int *)(_frame + (0x1e0 - 0x1ac)))
  #define iStack_1a8 (*(int *)(_frame + (0x1e0 - 0x1a8)))
  #define uStack_1a4 (*(uint *)(_frame + (0x1e0 - 0x1a4)))
  #define bStack_19e (*(byte *)(_frame + (0x1e0 - 0x19e)))
  #define uStack_19d (*(undefined1 *)(_frame + (0x1e0 - 0x19d)))
  #define uStack_19c (*(uint *)(_frame + (0x1e0 - 0x19c)))
  #define uStack_198 (*(uint *)(_frame + (0x1e0 - 0x198)))
  #define uStack_194 (*(undefined4 *)(_frame + (0x1e0 - 0x194)))
  #define uStack_18e (*(undefined2 *)(_frame + (0x1e0 - 0x18e)))
  #define puStack_18c (*(undefined4 **)(_frame + (0x1e0 - 0x18c)))
  #define iStack_188 (*(int *)(_frame + (0x1e0 - 0x188)))
  #define uStack_184 (*(undefined4 *)(_frame + (0x1e0 - 0x184)))
  #define abStack_180 (*(byte (*)[11])(_frame + (0x1e0 - 0x180)))
  #define uStack_175 (*(undefined1 *)(_frame + (0x1e0 - 0x175)))
  #define cStack_160 (*(char *)(_frame + (0x1e0 - 0x160)))
  #define acStack_15f (*(char (*)[351])(_frame + (0x1e0 - 0x15f)))
  
  cStack_1bf = '\0';
  uStack_1cc = 0;
  iStack_1ac = 0;
  bVar11 = *param_2;
  puVar9 = puStack_18c;
  do {
    if (bVar11 == 0) {
LAB_10007786:
      if ((puVar9 == (undefined4 *)0xffffffff) && ((iStack_1ac == 0 && (cStack_1bf == '\0')))) {
        iStack_1ac = -1;
      }
      return iStack_1ac;
    }
    iVar13 = 0;
    if (_DAT_10010ac8 < 2) {
      uVar5 = *(byte *)(_DAT_10010ad8 + (uint)bVar11 * 2) & 8;
    }
    else {
      uVar5 = FUN_10008d50(bVar11,8);
    }
    if (uVar5 != 0) {
      uStack_1cc = uStack_1cc - 1;
      uVar6 = ((code *)FUN_10007900)(&uStack_1cc,param_1,param_1);
      ((code *)FUN_100078e0)(uVar6);
      param_2 = param_2 + 1;
      iVar7 = FUN_1000aaf0(*param_2);
      while (iVar7 != 0) {
        param_2 = param_2 + 1;
        iVar7 = FUN_1000aaf0(*param_2);
      }
    }
    if (*param_2 != 0x25) {
      uStack_1cc = uStack_1cc + 1;
      puVar9 = (undefined4 *)FUN_100078b0(param_1);
      if ((undefined4 *)(uint)*param_2 != puVar9) goto LAB_1000776d;
      pbVar12 = param_2 + 1;
      if ((*(byte *)(_DAT_10010ad8 + 1 + ((uint)puVar9 & 0xff) * 2) & 0x80) != 0) {
        uStack_1cc = uStack_1cc + 1;
        uVar5 = FUN_100078b0(param_1);
        if (param_2[1] != uVar5) {
          uStack_1cc = uStack_1cc - 1;
          FUN_100078e0(uVar5,param_1);
          goto LAB_1000776d;
        }
        uStack_1cc = uStack_1cc - 1;
        pbVar12 = param_2 + 2;
      }
      goto LAB_10007733;
    }
    uStack_1a4 = 0;
    uStack_1b4 = uStack_1b4 & 0xffffff00;
    iStack_1a8 = 0;
    iStack_1b0 = 0;
    iStack_1c4 = 0;
    bStack_1bd = 0;
    cStack_1be = '\0';
    cStack_1c5 = '\0';
    cStack_1cd = '\0';
    cStack_1c0 = '\0';
    cStack_1c7 = '\0';
    cStack_1c6 = '\x01';
    iStack_188 = 0;
    do {
      pbVar12 = param_2 + 1;
      uVar5 = (uint)*pbVar12;
      if (_DAT_10010ac8 < 2) {
        uVar8 = *(byte *)(_DAT_10010ad8 + uVar5 * 2) & 4;
      }
      else {
        uVar8 = FUN_10008d50(uVar5,4);
      }
      if (uVar8 == 0) {
        switch(uVar5) {
        case 0x2a:
          cStack_1c5 = cStack_1c5 + '\x01';
          break;
        default:
LAB_10006d06:
          cStack_1cd = cStack_1cd + '\x01';
          break;
        case 0x46:
        case 0x4e:
          break;
        case 0x49:
          if ((param_2[2] != 0x36) || (param_2[3] != 0x34)) goto LAB_10006d06;
          iVar13 = iVar13 + 1;
          uStack_19c = 0;
          uStack_198 = 0;
          pbVar12 = param_2 + 3;
          break;
        case 0x4c:
          cStack_1c6 = cStack_1c6 + '\x01';
          break;
        case 0x68:
          cStack_1c6 = cStack_1c6 + -1;
          cStack_1c7 = cStack_1c7 + -1;
          break;
        case 0x6c:
          cStack_1c6 = cStack_1c6 + '\x01';
        case 0x77:
          cStack_1c7 = cStack_1c7 + '\x01';
        }
      }
      else {
        iStack_1b0 = iStack_1b0 + 1;
        iStack_1c4 = (uVar5 - 0x30) + iStack_1c4 * 10;
      }
      param_2 = pbVar12;
    } while (cStack_1cd == '\0');
    puVar3 = param_3;
    if (cStack_1c5 == '\0') {
      puStack_1b8 = (uint *)*param_3;
      puVar3 = param_3 + 1;
      puStack_18c = param_3;
    }
    param_3 = puVar3;
    bVar20 = false;
    if ((cStack_1c7 == '\0') && ((*param_2 == 0x53 || (cStack_1c7 = -1, *param_2 == 0x43)))) {
      cStack_1c7 = '\x01';
    }
    uStack_1bc = *param_2 | 0x20;
    iStack_188 = iVar13;
    if (uStack_1bc != 0x6e) {
      if ((uStack_1bc == 99) || (uStack_1bc == 0x7b)) {
        uStack_1cc = uStack_1cc + 1;
        puVar9 = (undefined4 *)FUN_100078b0(param_1);
      }
      else {
        puVar9 = (undefined4 *)FUN_10007900(&uStack_1cc,param_1);
      }
    }
    puVar15 = puStack_1b8;
    uVar5 = uStack_1bc;
    if ((iStack_1b0 != 0) && (iStack_1c4 == 0)) {
LAB_1000776d:
      uStack_1cc = uStack_1cc - 1;
      FUN_100078e0(puVar9,param_1);
      goto LAB_10007786;
    }
    switch(uStack_1bc) {
    case 99:
      if (iStack_1b0 == 0) {
        iStack_1b0 = 1;
        iStack_1c4 = iStack_1c4 + 1;
      }
      if ('\0' < cStack_1c7) {
        cStack_1c0 = '\x01';
      }
      pbVar12 = (byte *)((unsigned)(uintptr_t)&DAT_10010904);
      goto code_r0x10006e2e;
    case 100:
    case 0x6f:
    case 0x75:
      goto code_r0x10007129;
    case 0x65:
    case 0x66:
    case 0x67:
      pcVar16 = &cStack_160;
      if (puVar9 == (undefined4 *)0x2d) {
        cStack_160 = '-';
        pcVar16 = acStack_15f;
code_r0x10007473:
        iStack_1c4 = iStack_1c4 + -1;
        uStack_1cc = uStack_1cc + 1;
        puVar9 = (undefined4 *)FUN_100078b0(param_1);
      }
      else if (puVar9 == (undefined4 *)0x2b) goto code_r0x10007473;
      iVar13 = iStack_1a8;
      if ((iStack_1b0 == 0) || (0x15d < iStack_1c4)) {
        iStack_1c4 = 0x15d;
      }
      while( true ) {
        if (_DAT_10010ac8 < 2) {
          uVar5 = *(byte *)(_DAT_10010ad8 + (int)puVar9 * 2) & 4;
        }
        else {
          uVar5 = FUN_10008d50(puVar9,4);
        }
        if ((uVar5 == 0) ||
           (iVar7 = iStack_1c4 + -1, bVar20 = iStack_1c4 == 0, iStack_1c4 = iVar7, bVar20)) break;
        *pcVar16 = (char)puVar9;
        pcVar16 = pcVar16 + 1;
        uStack_1cc = uStack_1cc + 1;
        puVar9 = (undefined4 *)FUN_100078b0(param_1);
        iVar13 = iVar13 + 1;
      }
      if ((DAT_10010acc == (char)puVar9) &&
         (iVar7 = iStack_1c4 + -1, bVar20 = iStack_1c4 != 0, iStack_1c4 = iVar7, bVar20)) {
        uStack_1cc = uStack_1cc + 1;
        puVar9 = (undefined4 *)FUN_100078b0(param_1);
        *pcVar16 = DAT_10010acc;
        while( true ) {
          pcVar16 = pcVar16 + 1;
          if (_DAT_10010ac8 < 2) {
            uVar5 = *(byte *)(_DAT_10010ad8 + (int)puVar9 * 2) & 4;
          }
          else {
            uVar5 = FUN_10008d50(puVar9,4);
          }
          if ((uVar5 == 0) ||
             (iVar7 = iStack_1c4 + -1, bVar20 = iStack_1c4 == 0, iStack_1c4 = iVar7, bVar20)) break;
          *pcVar16 = (char)puVar9;
          iVar13 = iVar13 + 1;
          uStack_1cc = uStack_1cc + 1;
          puVar9 = (undefined4 *)FUN_100078b0(param_1);
        }
      }
      pcVar17 = pcVar16;
      if ((iVar13 != 0) &&
         (((puVar9 == (undefined4 *)0x65 || (puVar9 == (undefined4 *)0x45)) &&
          (iVar7 = iStack_1c4 + -1, bVar20 = iStack_1c4 != 0, iStack_1c4 = iVar7, bVar20)))) {
        *pcVar16 = 'e';
        pcVar17 = pcVar16 + 1;
        uStack_1cc = uStack_1cc + 1;
        puVar9 = (undefined4 *)FUN_100078b0(param_1);
        if (puVar9 == (undefined4 *)0x2d) {
          *pcVar17 = '-';
          pcVar17 = pcVar16 + 2;
code_r0x100075ce:
          iVar7 = iStack_1c4 + -1;
          if (iStack_1c4 != 0) goto code_r0x100075e3;
        }
        else if (puVar9 == (undefined4 *)0x2b) goto code_r0x100075ce;
        while( true ) {
          if (_DAT_10010ac8 < 2) {
            uVar5 = *(byte *)(_DAT_10010ad8 + (int)puVar9 * 2) & 4;
          }
          else {
            uVar5 = FUN_10008d50(puVar9,4);
          }
          if ((uVar5 == 0) ||
             (iVar7 = iStack_1c4 + -1, bVar20 = iStack_1c4 == 0, iStack_1c4 = iVar7, bVar20)) break;
          iVar13 = iVar13 + 1;
          *pcVar17 = (char)puVar9;
          pcVar17 = pcVar17 + 1;
code_r0x100075e3:
          iStack_1c4 = iVar7;
          uStack_1cc = uStack_1cc + 1;
          puVar9 = (undefined4 *)FUN_100078b0(param_1);
        }
      }
      uStack_1cc = uStack_1cc - 1;
      FUN_100078e0(puVar9,param_1);
      if (iVar13 == 0) goto LAB_10007786;
      if (cStack_1c5 == '\0') {
        iStack_1ac = iStack_1ac + 1;
        *pcVar17 = '\0';
        (*_DAT_100106d0)(cStack_1c6 + -1,puStack_1b8,&cStack_160);
      }
      break;
    default:
      if ((undefined4 *)(uint)*param_2 != puVar9) goto LAB_1000776d;
      cStack_1bf = cStack_1bf + -1;
      if (cStack_1c5 == '\0') {
        param_3 = puStack_18c;
      }
      break;
    case 0x69:
      uStack_1bc = 100;
    case 0x78:
      uVar5 = uStack_1bc;
      if (puVar9 == (undefined4 *)0x2d) {
        cStack_1be = '\x01';
code_r0x10007082:
        iStack_1c4 = iStack_1c4 + -1;
        if ((iStack_1c4 == 0) && (iStack_1b0 != 0)) {
          bVar20 = true;
        }
        else {
          uStack_1cc = uStack_1cc + 1;
          puVar9 = (undefined4 *)FUN_100078b0(param_1);
        }
      }
      else if (puVar9 == (undefined4 *)0x2b) goto code_r0x10007082;
      if (puVar9 == (undefined4 *)0x30) {
        uStack_1cc = uStack_1cc + 1;
        puVar9 = (undefined4 *)FUN_100078b0(param_1);
        if (((char)puVar9 == 'x') || ((char)puVar9 == 'X')) {
          uStack_1cc = uStack_1cc + 1;
          puVar9 = (undefined4 *)FUN_100078b0(param_1);
          uVar5 = 0x78;
          uStack_1bc = 0x78;
        }
        else {
          iStack_1a8 = 1;
          if (uVar5 == 0x78) {
            uStack_1cc = uStack_1cc - 1;
            FUN_100078e0(puVar9,param_1);
            puVar9 = (undefined4 *)0x30;
          }
          else {
            uVar5 = 0x6f;
            uStack_1bc = 0x6f;
          }
        }
      }
      goto code_r0x10007164;
    case 0x6e:
      uVar5 = uStack_1cc;
      if (cStack_1c5 != '\0') break;
      goto code_r0x10007425;
    case 0x70:
      cStack_1c6 = '\x01';
code_r0x10007129:
      if (puVar9 == (undefined4 *)0x2d) {
        cStack_1be = '\x01';
code_r0x1000713a:
        iStack_1c4 = iStack_1c4 + -1;
        if ((iStack_1c4 == 0) && (iStack_1b0 != 0)) {
          bVar20 = true;
        }
        else {
          uStack_1cc = uStack_1cc + 1;
          puVar9 = (undefined4 *)FUN_100078b0(param_1);
        }
      }
      else if (puVar9 == (undefined4 *)0x2b) goto code_r0x1000713a;
code_r0x10007164:
      uVar8 = uStack_1a4;
      uVar10 = uStack_19c;
      a2 = uStack_198;
      if (iVar13 == 0) {
        while (!bVar20) {
          if ((uVar5 == 0x78) || (uVar5 == 0x70)) {
            if (_DAT_10010ac8 < 2) {
              uVar10 = *(byte *)(_DAT_10010ad8 + (int)puVar9 * 2) & 0x80;
            }
            else {
              uVar10 = FUN_10008d50(puVar9,0x80);
            }
            if (uVar10 != 0) {
              uVar8 = uVar8 << 4;
              puVar9 = (undefined4 *)FUN_10007870(puVar9);
              goto code_r0x1000735a;
            }
code_r0x10007356:
            bVar20 = true;
          }
          else {
            if (_DAT_10010ac8 < 2) {
              uVar10 = *(byte *)(_DAT_10010ad8 + (int)puVar9 * 2) & 4;
            }
            else {
              uVar10 = FUN_10008d50(puVar9,4);
            }
            if (uVar10 == 0) goto code_r0x10007356;
            if (uVar5 == 0x6f) {
              if (0x37 < (int)puVar9) goto code_r0x10007356;
              uVar8 = uVar8 << 3;
            }
            else {
              uVar8 = uVar8 * 10;
            }
          }
code_r0x1000735a:
          if (bVar20) {
            uStack_1cc = uStack_1cc - 1;
            FUN_100078e0(puVar9,param_1);
          }
          else {
            iStack_1a8 = iStack_1a8 + 1;
            uVar8 = (uVar8 - 0x30) + (int)puVar9;
            if ((iStack_1b0 == 0) || (iStack_1c4 = iStack_1c4 + -1, iStack_1c4 != 0)) {
              uStack_1cc = uStack_1cc + 1;
              puVar9 = (undefined4 *)FUN_100078b0(param_1);
            }
            else {
              bVar20 = true;
            }
          }
        }
        uStack_1a4 = uVar8;
        if (cStack_1be != '\0') {
          uStack_1a4 = -uVar8;
        }
      }
      else {
        while (!bVar20) {
          if (uStack_1bc == 0x78) {
            if (_DAT_10010ac8 < 2) {
              uVar5 = *(byte *)(_DAT_10010ad8 + (int)puVar9 * 2) & 0x80;
            }
            else {
              uVar5 = FUN_10008d50(puVar9,0x80);
            }
            if (uVar5 != 0) {
              uVar10 = FUN_1000ab60(4,a2);
              puVar9 = (undefined4 *)FUN_10007870(puVar9);
              a2 = extraout_EDX;
              goto code_r0x10007231;
            }
code_r0x1000722d:
            bVar20 = true;
          }
          else {
            if (_DAT_10010ac8 < 2) {
              uVar5 = *(byte *)(_DAT_10010ad8 + (int)puVar9 * 2) & 4;
            }
            else {
              uVar5 = FUN_10008d50(puVar9,4);
            }
            if (uVar5 == 0) goto code_r0x1000722d;
            if (uStack_1bc == 0x6f) {
              if (0x37 < (int)puVar9) goto code_r0x1000722d;
              uVar10 = FUN_1000ab60(3,a2);
              a2 = extraout_EDX_00;
            }
            else {
              uVar10 = FUN_1000ab20(uVar10,a2,10,0);
              a2 = extraout_EDX_01;
            }
          }
code_r0x10007231:
          if (bVar20) {
            uStack_1cc = uStack_1cc - 1;
            FUN_100078e0(puVar9,param_1);
          }
          else {
            puVar3 = puVar9 + -0xc;
            iStack_1a8 = iStack_1a8 + 1;
            bVar19 = CARRY4(uVar10,(uint)puVar3);
            uVar10 = uVar10 + (int)puVar3;
            a2 = a2 + ((int)puVar3 >> 0x1f) + (uint)bVar19;
            if ((iStack_1b0 == 0) || (iStack_1c4 = iStack_1c4 + -1, iStack_1c4 != 0)) {
              uStack_1cc = uStack_1cc + 1;
              puVar9 = (undefined4 *)FUN_100078b0(param_1);
            }
            else {
              bVar20 = true;
            }
          }
        }
        uStack_19c = uVar10;
        uStack_198 = a2;
        if (cStack_1be != '\0') {
          uStack_19c = -uVar10;
          uStack_198 = -(a2 + (uVar10 != 0));
        }
      }
      iVar13 = iStack_1a8;
      if (uStack_1bc == 0x46) {
        iVar13 = 0;
      }
      if (iVar13 == 0) goto LAB_10007786;
      if (cStack_1c5 == '\0') {
        iStack_1ac = iStack_1ac + 1;
        uVar5 = uStack_1a4;
        iVar13 = iStack_188;
code_r0x10007425:
        if (iVar13 == 0) {
          if (cStack_1c6 == '\0') {
            *(short *)puStack_1b8 = (short)uVar5;
          }
          else {
            *puStack_1b8 = uVar5;
          }
        }
        else {
          *puStack_1b8 = uStack_19c;
          puStack_1b8[1] = uStack_198;
        }
      }
      break;
    case 0x73:
      if ('\0' < cStack_1c7) {
        cStack_1c0 = '\x01';
      }
      pbVar12 = (byte *)((unsigned)(uintptr_t)&DAT_100108fc);
code_r0x10006e2e:
      bStack_1bd = 0xff;
      pbVar14 = param_2;
code_r0x10006e33:
      param_2 = pbVar14;
      pbVar14 = abStack_180;
      for (iVar13 = 8; iVar13 != 0; iVar13 = iVar13 + -1) {
        pbVar14[0] = 0;
        pbVar14[1] = 0;
        pbVar14[2] = 0;
        pbVar14[3] = 0;
        pbVar14 = pbVar14 + 4;
      }
      if ((uStack_1bc == 0x7b) && (*pbVar12 == 0x5d)) {
        uStack_1b4 = CONCAT31(PIECE(uStack_1b4,1,3),0x5d);
        pbVar12 = pbVar12 + 1;
        uStack_175 = 0x20;
      }
      bVar11 = *pbVar12;
      uVar5 = uStack_1b4;
      while (bVar11 != 0x5d) {
        pbVar14 = pbVar12 + 1;
        uVar8 = (uint)uStack_184 >> 8;
        uStack_184 = CONCAT31((int3)uVar8,bVar11);
        PIECE(uStack_1b4,1,3) = (undefined3)(uVar5 >> 8);
        if (((bVar11 == 0x2d) &&
            (PIECE(uStack_1b4,0,1) = (byte)uVar5, bVar2 = (byte)uStack_1b4, (byte)uStack_1b4 != 0)) &&
           (bVar1 = *pbVar14, bVar1 != 0x5d)) {
          pbVar14 = pbVar12 + 2;
          uVar8 = (uint)uStack_194 >> 8;
          bVar11 = (byte)uStack_1b4;
          if (bVar1 <= (byte)uStack_1b4) {
            uStack_1b4 = CONCAT31(PIECE(uStack_1b4,1,3),bVar1);
            bVar11 = bVar1;
            uVar5 = uStack_1b4;
            bVar1 = bVar2;
          }
          uStack_1b4 = uVar5;
          uStack_194 = CONCAT31((int3)uVar8,bVar1);
          if (bVar11 <= bVar1) {
            uVar5 = uStack_1b4 & 0xff;
            iVar13 = (bVar1 - uVar5) + 1;
            do {
              uVar8 = uVar5 >> 3;
              bVar11 = (byte)uVar5;
              uVar5 = uVar5 + 1;
              iVar13 = iVar13 + -1;
              abStack_180[uVar8] = abStack_180[uVar8] | '\x01' << (bVar11 & 7);
            } while (iVar13 != 0);
          }
          uStack_1b4 = uStack_1b4 & 0xffffff00;
        }
        else {
          uStack_1b4 = CONCAT31(PIECE(uStack_1b4,1,3),bVar11);
          abStack_180[bVar11 >> 3] = abStack_180[bVar11 >> 3] | '\x01' << (bVar11 & 7);
        }
        pbVar12 = pbVar14;
        uVar5 = uStack_1b4;
        bVar11 = *pbVar14;
      }
      if (*pbVar12 == 0) goto LAB_10007786;
      if (uStack_1bc == 0x7b) {
        param_2 = pbVar12;
      }
      uStack_1cc = uStack_1cc - 1;
      uStack_1b4 = uVar5;
      FUN_100078e0(puVar9,param_1);
      puVar18 = puVar15;
      while( true ) {
        if ((iStack_1b0 != 0) &&
           (iVar13 = iStack_1c4 + -1, bVar20 = iStack_1c4 == 0, iStack_1c4 = iVar13,
           puVar4 = puVar18, bVar20)) goto code_r0x1000701c;
        uStack_1cc = uStack_1cc + 1;
        puVar9 = (undefined4 *)FUN_100078b0(param_1);
        if ((puVar9 == (undefined4 *)0xffffffff) ||
           (bVar11 = (byte)puVar9,
           ((int)(char)(abStack_180[(int)puVar9 >> 3] ^ bStack_1bd) & 1 << (bVar11 & 7)) == 0))
        break;
        if (cStack_1c5 == '\0') {
          if (cStack_1c0 == '\0') {
            *(byte *)puVar18 = bVar11;
            puVar18 = (uint *)((int)puVar18 + 1);
          }
          else {
            bStack_19e = bVar11;
            if ((*(byte *)(_DAT_10010ad8 + 1 + ((uint)puVar9 & 0xff) * 2) & 0x80) != 0) {
              uStack_1cc = uStack_1cc + 1;
              uStack_19d = FUN_100078b0(param_1);
            }
            FUN_1000a970(&uStack_18e,&bStack_19e,_DAT_10010ac8);
            *(undefined2 *)puVar18 = uStack_18e;
            puVar18 = (uint *)((int)puVar18 + 2);
          }
        }
        else {
          puVar15 = (uint *)((int)puVar15 + 1);
        }
      }
      uStack_1cc = uStack_1cc - 1;
      puStack_1b8 = puVar18;
      FUN_100078e0(puVar9,param_1);
      puVar4 = puStack_1b8;
code_r0x1000701c:
      puStack_1b8 = puVar4;
      if (puVar15 == puVar18) goto LAB_10007786;
      if ((cStack_1c5 == '\0') && (iStack_1ac = iStack_1ac + 1, uStack_1bc != 99)) {
        if (cStack_1c0 == '\0') {
          *(byte *)puStack_1b8 = 0;
        }
        else {
          *(undefined2 *)puStack_1b8 = 0;
        }
      }
      break;
    case 0x7b:
      if ('\0' < cStack_1c7) {
        cStack_1c0 = '\x01';
      }
      pbVar14 = param_2 + 1;
      pbVar12 = pbVar14;
      if (*pbVar14 == 0x5e) {
        pbVar12 = param_2 + 2;
        param_2 = pbVar14;
        goto code_r0x10006e2e;
      }
      goto code_r0x10006e33;
    }
    cStack_1bf = cStack_1bf + '\x01';
    pbVar12 = param_2 + 1;
LAB_10007733:
    param_2 = pbVar12;
    if ((puVar9 == (undefined4 *)0xffffffff) && ((*param_2 != 0x25 || (param_2[1] != 0x6e))))
    goto LAB_10007786;
    bVar11 = *param_2;
  } while( true );
}
#undef abStack_180
#undef acStack_15f
#undef bStack_19e
#undef bStack_1bd
#undef cStack_160
#undef cStack_1be
#undef cStack_1bf
#undef cStack_1c0
#undef cStack_1c5
#undef cStack_1c6
#undef cStack_1c7
#undef cStack_1cd
#undef iStack_188
#undef iStack_1a8
#undef iStack_1ac
#undef iStack_1b0
#undef iStack_1c4
#undef puStack_18c
#undef puStack_1b8
#undef uStack_175
#undef uStack_184
#undef uStack_18e
#undef uStack_194
#undef uStack_198
#undef uStack_19c
#undef uStack_19d
#undef uStack_1a4
#undef uStack_1b4
#undef uStack_1bc
#undef uStack_1cc

#endif


/* ---- 0x10007870  FUN_10007870 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_10007870(uint param_1)

{
  uint uVar1;
  
  if (_DAT_10010ac8 < 2) {
    uVar1 = *(byte *)(_DAT_10010ad8 + param_1 * 2) & 4;
  }
  else {
    uVar1 = FUN_10008d50(param_1,4);
  }
  if (uVar1 == 0) {
    param_1 = (param_1 & 0xffffffdf) - 7;
  }
  return param_1;
}
#endif


/* ---- 0x100078b0  FUN_100078b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_100078b0(undefined4 *param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = param_1[1];
  param_1[1] = iVar2 + -1;
  if (-1 < iVar2 + -1) {
    bVar1 = *(byte *)*param_1;
    *param_1 = (byte *)*param_1 + 1;
    return (uint)bVar1;
  }
  uVar3 = FUN_1000ab80(param_1);
  return uVar3;
}
#endif


/* ---- 0x100078e0  FUN_100078e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100078e0(int param_1,undefined4 param_2)

{
  if (param_1 != -1) {
    FUN_1000ac70(param_1,param_2);
  }
  return;
}
#endif


/* ---- 0x10007900  FUN_10007900 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10007900(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *param_1 = *param_1 + 1;
  uVar1 = FUN_100078b0(param_2);
  iVar2 = FUN_1000aaf0(uVar1);
  while (iVar2 != 0) {
    *param_1 = *param_1 + 1;
    uVar1 = FUN_100078b0(param_2);
    iVar2 = FUN_1000aaf0(uVar1);
  }
  return uVar1;
}
#endif


/* ---- 0x10007950  FUN_10007950 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10007950(void)

{
  if (_DAT_100106a8 != (code *)0x0) {
    (*_DAT_100106a8)();
  }
  FUN_10007a90(((unsigned)(uintptr_t)&DAT_10010008),((unsigned)(uintptr_t)&DAT_10010010));
  FUN_10007a90(&DAT_10010000,((unsigned)(uintptr_t)&DAT_10010004));
  return;
}
#endif


/* ---- 0x10007980  FUN_10007980 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10007980(undefined4 param_1)

{
  FUN_100079b0(param_1,1,0);
  return;
}
#endif


/* ---- 0x100079a0  FUN_100079a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100079a0(void)

{
  FUN_100079b0(0,0,1);
  return;
}
#endif


/* ---- 0x100079b0  FUN_100079b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100079b0(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  
  FUN_10007a70();
  if (_DAT_100144d8 == 1) {
    uVar4 = param_1;
    iVar1 = GetCurrentProcess();
    TerminateProcess(iVar1,uVar4);
  }
  _DAT_100144d4 = 1;
  DAT_100144d0 = (undefined1)param_3;
  if (param_2 == 0) {
    if ((_DAT_10015ae8 != (undefined4 *)0x0) &&
       (puVar3 = (undefined4 *)(_DAT_10015ae4 + -4), puVar2 = _DAT_10015ae8, _DAT_10015ae8 <= puVar3
       )) {
      do {
        if ((code *)*puVar3 != (code *)0x0) {
          (*(code *)*puVar3)();
          puVar2 = _DAT_10015ae8;
        }
        puVar3 = puVar3 + -1;
      } while (puVar2 <= puVar3);
    }
    FUN_10007a90(((unsigned)(uintptr_t)&DAT_10010014),((unsigned)(uintptr_t)&DAT_1001001c));
  }
  FUN_10007a90(((unsigned)(uintptr_t)&DAT_10010020),((unsigned)(uintptr_t)&DAT_10010024));
  if (param_3 != 0) {
    FUN_10007a80();
    return;
  }
  _DAT_100144d8 = 1;
  ExitProcess(param_1);
  return;
}
#endif


/* ---- 0x10007a70  FUN_10007a70 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10007a70(void)

{
  FUN_10006810(0xd);
  return;
}
#endif


/* ---- 0x10007a80  FUN_10007a80 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10007a80(void)

{
  FUN_10006890();
  return;
}
#endif


/* ---- 0x10007a90  FUN_10007a90 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10007a90(undefined4 *param_1,undefined4 *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if ((code *)*param_1 != (code *)0x0) {
      (*(code *)*param_1)();
    }
  }
  return;
}
#endif


/* ---- 0x10007ab0  FUN_10007ab0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10007ab0(void)

{
  int *piVar1;
  int iVar2;
  
  FUN_10006760();
  _DAT_10010908 = TlsAlloc();
  if (_DAT_10010908 != -1) {
    piVar1 = (int *)FUN_1000ad00(1,0x74);
    if (piVar1 != (int *)0x0) {
      iVar2 = TlsSetValue(_DAT_10010908,piVar1);
      if (iVar2 != 0) {
        FUN_10007b40(piVar1);
        iVar2 = GetCurrentThreadId();
        *piVar1 = iVar2;
        piVar1[1] = -1;
        return 1;
      }
    }
  }
  return 0;
}
#endif


/* ---- 0x10007b10  FUN_10007b10 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10007b10(void)

{
  FUN_10006790();
  if (_DAT_10010908 != -1) {
    TlsFree(_DAT_10010908);
    _DAT_10010908 = -1;
  }
  return;
}
#endif


/* ---- 0x10007b40  FUN_10007b40 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10007b40(int param_1)

{
  *(undefined4 *)(param_1 + 0x50) = ((unsigned)(uintptr_t)&DAT_10011720);
  *(undefined4 *)(param_1 + 0x14) = 1;
  return;
}
#endif


/* ---- 0x10007b60  FUN_10007b60 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * FUN_10007b60(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = GetLastError();
  piVar2 = (int *)TlsGetValue(_DAT_10010908);
  if (piVar2 == (int *)0x0) {
    piVar2 = (int *)FUN_1000ad00(1,0x74);
    if (piVar2 != (int *)0x0) {
      iVar3 = TlsSetValue(_DAT_10010908,piVar2);
      if (iVar3 != 0) {
        FUN_10007b40(piVar2);
        iVar3 = GetCurrentThreadId();
        *piVar2 = iVar3;
        piVar2[1] = -1;
        SetLastError(iVar1);
        return piVar2;
      }
    }
    FUN_10006120(0x10);
  }
  SetLastError(iVar1);
  return piVar2;
}
#endif


/* ---- 0x10007be0  FUN_10007be0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10007be0(int param_1)

{
  if (_DAT_10010908 != -1) {
    if ((param_1 != 0) || (param_1 = TlsGetValue(_DAT_10010908), param_1 != 0)) {
      if (*(int *)(param_1 + 0x24) != 0) {
        FUN_10009510();
      }
      if (*(int *)(param_1 + 0x28) != 0) {
        FUN_10009510();
      }
      if (*(int *)(param_1 + 0x30) != 0) {
        FUN_10009510();
      }
      if (*(int *)(param_1 + 0x38) != 0) {
        FUN_10009510();
      }
      if (*(int *)(param_1 + 0x40) != 0) {
        FUN_10009510();
      }
      if (*(int *)(param_1 + 0x44) != 0) {
        FUN_10009510();
      }
      if (*(int *)(param_1 + 0x50) != ((unsigned)(uintptr_t)&DAT_10011720)) {
        FUN_10009510();
      }
      FUN_10009510();
    }
    TlsSetValue(_DAT_10010908,0);
    return;
  }
  return;
}
#endif


/* ---- 0x10007c90  FUN_10007c90 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10007c90(void)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  int *piVar6;
  uint uVar7;
  byte *pbVar8;
  #define iStack_44 (*(int *)(_frame + (0x60 - 0x44)))
  #define aiStack_40 (*(int (*)[12])(_frame + (0x60 - 0x40)))
  #define sStack_e (*(short *)(_frame + (0x60 - 0xe)))
  #define piStack_c (*(int **)(_frame + (0x60 - 0xc)))
  
  puVar2 = (undefined4 *)FUN_10009580(0x480);
  if (puVar2 == (undefined4 *)0x0) {
    FUN_10006120(0x1b);
  }
  _DAT_10015ae0 = 0x20;
  _DAT_100159e0 = puVar2;
  if (puVar2 < puVar2 + 0x120) {
    do {
      *(undefined1 *)(puVar2 + 1) = 0;
      *puVar2 = 0xffffffff;
      *(undefined1 *)((int)puVar2 + 5) = 10;
      puVar2[2] = 0;
      puVar2 = puVar2 + 9;
    } while (puVar2 < _DAT_100159e0 + 0x120);
  }
  GetStartupInfoA((int)aiStack_40);
  if ((sStack_e != 0) && (piStack_c != (int *)0x0)) {
    iStack_44 = *piStack_c;
    pbVar8 = (byte *)(piStack_c + 1);
    pbVar5 = pbVar8 + iStack_44;
    if (0x7ff < iStack_44) {
      iStack_44 = 0x800;
    }
    if (_DAT_10015ae0 < iStack_44) {
      piVar6 = (int *)((unsigned)(uintptr_t)&DAT_100159e4);
      do {
        puVar2 = (undefined4 *)FUN_10009580(0x480);
        if (puVar2 == (undefined4 *)0x0) {
          aiStack_40[0] = _DAT_10015ae0;
          break;
        }
        *piVar6 = (int)puVar2;
        _DAT_10015ae0 = _DAT_10015ae0 + 0x20;
        if (puVar2 < puVar2 + 0x120) {
          do {
            *(undefined1 *)(puVar2 + 1) = 0;
            *puVar2 = 0xffffffff;
            *(undefined1 *)((int)puVar2 + 5) = 10;
            puVar2[2] = 0;
            puVar2 = puVar2 + 9;
          } while (puVar2 < (undefined4 *)(*piVar6 + 0x480));
        }
        piVar6 = piVar6 + 1;
      } while (_DAT_10015ae0 < aiStack_40[0]);
    }
    uVar7 = 0;
    if (0 < iStack_44) {
      do {
        if (((*(int *)pbVar5 != -1) && ((*pbVar8 & 1) != 0)) &&
           (((*pbVar8 & 8) != 0 || (iVar3 = GetFileType(*(int *)pbVar5), iVar3 != 0)))) {
          puVar2 = (undefined4 *)
                   (*(int *)(&DAT_100159e0 + ((int)uVar7 >> 5) * 4) + (uVar7 & 0x1f) * 0x24);
          *puVar2 = *(undefined4 *)pbVar5;
          *(byte *)(puVar2 + 1) = *pbVar8;
        }
        uVar7 = uVar7 + 1;
        pbVar8 = pbVar8 + 1;
        pbVar5 = pbVar5 + 4;
      } while ((int)uVar7 < iStack_44);
    }
  }
  iVar3 = 0;
  do {
    piVar6 = _DAT_100159e0 + iVar3 * 9;
    if (_DAT_100159e0[iVar3 * 9] == -1) {
      *(undefined1 *)(piVar6 + 1) = 0x81;
      if (iVar3 == 0) {
        iVar4 = -10;
      }
      else {
        iVar4 = -0xb - (uint)(iVar3 != 1);
      }
      iVar4 = GetStdHandle(iVar4);
      if ((iVar4 == -1) || (uVar7 = GetFileType(iVar4), uVar7 == 0)) {
        bVar1 = *(byte *)(piVar6 + 1) | 0x40;
        goto LAB_10007e7e;
      }
      *piVar6 = iVar4;
      if ((uVar7 & 0xff) == 2) {
        bVar1 = *(byte *)(piVar6 + 1) | 0x40;
        goto LAB_10007e7e;
      }
      if ((uVar7 & 0xff) == 3) {
        bVar1 = *(byte *)(piVar6 + 1) | 8;
        goto LAB_10007e7e;
      }
    }
    else {
      bVar1 = *(byte *)(piVar6 + 1) | 0x80;
LAB_10007e7e:
      *(byte *)(piVar6 + 1) = bVar1;
    }
    iVar3 = iVar3 + 1;
    if (2 < iVar3) {
      SetHandleCount(_DAT_10015ae0);
      return;
    }
  } while( true );
}
#undef aiStack_40
#undef iStack_44
#undef piStack_c
#undef sStack_e

#endif


/* ---- 0x10007ea0  FUN_10007ea0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10007ea0(void)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  puVar1 = (uint *)&DAT_100159e0;
  do {
    uVar2 = *puVar1;
    if (uVar2 != 0) {
      if (uVar2 < uVar2 + 0x480) {
        iVar3 = uVar2 + 0xc;
        do {
          if (*(int *)(iVar3 + -4) != 0) {
            DeleteCriticalSection(iVar3);
          }
          uVar2 = uVar2 + 0x24;
          iVar3 = iVar3 + 0x24;
        } while (uVar2 < *puVar1 + 0x480);
      }
      FUN_10009510();
      *puVar1 = 0;
    }
    puVar1 = puVar1 + 1;
  } while ((int)puVar1 < ((unsigned)(uintptr_t)&DAT_10015ae0));
  return;
}
#endif


/* ---- 0x10007f00  FUN_10007f00 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10007f00(void)

{
  char cVar1;
  char cVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  int *piVar11;
  
  iVar8 = 0;
  cVar2 = *_DAT_10014400;
  pcVar7 = _DAT_10014400;
  while (cVar2 != '\0') {
    if (cVar2 != '=') {
      iVar8 = iVar8 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar9 = pcVar7;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar2 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar2 != '\0');
    pcVar9 = pcVar7 + ~uVar4;
    pcVar7 = pcVar7 + ~uVar4;
    cVar2 = *pcVar9;
  }
  piVar3 = (int *)FUN_10009580(iVar8 * 4 + 4);
  _DAT_100144b8 = piVar3;
  if (piVar3 == (int *)0x0) {
    FUN_10006120(9);
  }
  cVar2 = *_DAT_10014400;
  piVar11 = piVar3;
  pcVar7 = _DAT_10014400;
  do {
    if (cVar2 == '\0') {
      FUN_10009510();
      _DAT_10014400 = (char *)0x0;
      *piVar3 = 0;
      return;
    }
    uVar4 = 0xffffffff;
    pcVar9 = pcVar7;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    if (cVar2 != '=') {
      iVar8 = FUN_10009580(uVar4);
      *piVar3 = iVar8;
      if (iVar8 == 0) {
        FUN_10006120(9);
      }
      uVar5 = 0xffffffff;
      pcVar9 = pcVar7;
      do {
        pcVar10 = pcVar9;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar10 = pcVar9 + 1;
        cVar2 = *pcVar9;
        pcVar9 = pcVar10;
      } while (cVar2 != '\0');
      uVar5 = ~uVar5;
      pcVar9 = pcVar10 + -uVar5;
      pcVar10 = (char *)*piVar11;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar10 = pcVar10 + 4;
      }
      piVar3 = piVar11 + 1;
      for (uVar5 = uVar5 & 3; piVar11 = piVar3, uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar10 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar10 = pcVar10 + 1;
      }
    }
    cVar2 = pcVar7[uVar4];
    pcVar7 = pcVar7 + uVar4;
  } while( true );
}
#endif


/* ---- 0x10007ff0  FUN_10007ff0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10007ff0(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int unaff_EDI;
  char *pcVar2;
  #define iStack_14 (*(int *)(_frame + (0x30 - 0x14)))
  
  iStack_14 = 0x104;
  GetModuleFileNameA(0,((unsigned)(uintptr_t)&DAT_100144e0));
  _DAT_100144c8 = ((unsigned)(uintptr_t)&DAT_100144e0);
  pcVar2 = _DAT_10015af4;
  if (*_DAT_10015af4 == '\0') {
    pcVar2 = (char *)((unsigned)(uintptr_t)&DAT_100144e0);
  }
  FUN_10008090(pcVar2,0,0,&iStack_14,(_frame + (0x30 - 0x10)));
  iVar1 = FUN_10009580(unaff_EDI + iStack_14 * 4);
  if (iVar1 == 0) {
    FUN_10006120(8);
  }
  FUN_10008090(pcVar2,iVar1,iVar1 + unaff_EDI * 4,(_frame + (0x30 - 0x10)),(_frame + (0x30 - 0xc)));
  _DAT_100144b0 = iVar1;
  _DAT_100144ac = unaff_EDI + -1;
  return;
}
#undef iStack_14

#endif


/* ---- 0x10008090  FUN_10008090 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10008090(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5)

{
  byte *pbVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int *piVar6;
  byte *pbVar7;
  uint uVar8;
  
  piVar6 = param_5;
  *param_5 = 0;
  *param_4 = 1;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = param_3;
    param_2 = param_2 + 1;
  }
  if (*param_1 == 0x22) {
    bVar2 = param_1[1];
    while ((pbVar7 = param_1 + 1, bVar2 != 0x22 && (bVar2 != 0))) {
      if (((*(byte *)(bVar2 + ((unsigned)(uintptr_t)&DAT_100145e9)) & 4) != 0) &&
         (*param_5 = *param_5 + 1, param_3 != (byte *)0x0)) {
        *param_3 = *pbVar7;
        param_3 = param_3 + 1;
        pbVar7 = param_1 + 2;
      }
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *pbVar7;
        param_3 = param_3 + 1;
      }
      param_1 = pbVar7;
      bVar2 = pbVar7[1];
    }
    *param_5 = *param_5 + 1;
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    if (*pbVar7 == 0x22) {
      pbVar7 = param_1 + 2;
    }
  }
  else {
    do {
      *piVar6 = *piVar6 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *param_1;
        param_3 = param_3 + 1;
      }
      bVar2 = *param_1;
      pbVar7 = param_1 + 1;
      param_5 = (int *)(uint)bVar2;
      if ((*(byte *)((int)param_5 + ((unsigned)(uintptr_t)&DAT_100145e9)) & 4) != 0) {
        *piVar6 = *piVar6 + 1;
        if (param_3 != (byte *)0x0) {
          *param_3 = *pbVar7;
          param_3 = param_3 + 1;
        }
        pbVar7 = param_1 + 2;
      }
      if (bVar2 == 0x20) break;
      if (bVar2 == 0) goto LAB_10008169;
      param_1 = pbVar7;
    } while (bVar2 != 9);
    if (bVar2 == 0) {
LAB_10008169:
      pbVar7 = pbVar7 + -1;
    }
    else if (param_3 != (byte *)0x0) {
      param_3[-1] = 0;
    }
  }
  bVar4 = false;
  bVar5 = false;
  while (*pbVar7 != 0) {
    for (; (*pbVar7 == 0x20 || (*pbVar7 == 9)); pbVar7 = pbVar7 + 1) {
    }
    if (*pbVar7 == 0) break;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = param_3;
      param_2 = param_2 + 1;
    }
    *param_4 = *param_4 + 1;
    while( true ) {
      uVar8 = 0;
      bVar3 = true;
      bVar2 = *pbVar7;
      while (bVar2 == 0x5c) {
        pbVar1 = pbVar7 + 1;
        pbVar7 = pbVar7 + 1;
        uVar8 = uVar8 + 1;
        bVar2 = *pbVar1;
      }
      if (*pbVar7 == 0x22) {
        if ((uVar8 & 1) == 0) {
          if ((bVar4) && (pbVar7[1] == 0x22)) {
            pbVar7 = pbVar7 + 1;
          }
          else {
            bVar3 = false;
          }
          bVar4 = !bVar5;
          bVar5 = bVar4;
        }
        uVar8 = uVar8 >> 1;
      }
      for (; uVar8 != 0; uVar8 = uVar8 - 1) {
        if (param_3 != (byte *)0x0) {
          *param_3 = 0x5c;
          param_3 = param_3 + 1;
        }
        *piVar6 = *piVar6 + 1;
      }
      bVar2 = *pbVar7;
      if ((bVar2 == 0) || ((!bVar4 && ((bVar2 == 0x20 || (bVar2 == 9)))))) break;
      if (bVar3) {
        if (param_3 == (byte *)0x0) {
          if ((*(byte *)(bVar2 + ((unsigned)(uintptr_t)&DAT_100145e9)) & 4) != 0) {
            pbVar7 = pbVar7 + 1;
            *piVar6 = *piVar6 + 1;
          }
          *piVar6 = *piVar6 + 1;
          goto LAB_10008265;
        }
        if ((*(byte *)(bVar2 + ((unsigned)(uintptr_t)&DAT_100145e9)) & 4) != 0) {
          *param_3 = bVar2;
          param_3 = param_3 + 1;
          pbVar7 = pbVar7 + 1;
          *piVar6 = *piVar6 + 1;
        }
        *param_3 = *pbVar7;
        param_3 = param_3 + 1;
        *piVar6 = *piVar6 + 1;
        pbVar7 = pbVar7 + 1;
      }
      else {
LAB_10008265:
        pbVar7 = pbVar7 + 1;
      }
    }
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    *piVar6 = *piVar6 + 1;
  }
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = 0;
  }
  *param_4 = *param_4 + 1;
  return;
}
#endif


/* ---- 0x100082a0  FUN_100082a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_100082a0(undefined4 param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[48] __attribute__((aligned(16)));  /* the original frame below the return address */
  byte bVar1;
  byte bVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  undefined4 unaff_EBX;
  uint unaff_EBP;
  byte *pbVar10;
  undefined4 *puVar11;
  #define abStack_14 (*(byte (*)[16])(_frame + (0x30 - 0x14)))
  #define iStack_4 (*(int *)(_frame + (0x30 - 0x4)))
  
  FUN_10006810(0x19);
  iVar3 = FUN_100084d0(param_1);
  if (iVar3 == _DAT_100147f0) {
    FUN_10006890();
    return 0;
  }
  if (iVar3 == 0) {
    FUN_10008580();
    FUN_100085c0();
    FUN_10006890();
    return 0;
  }
  iVar8 = 0;
  piVar4 = (int *)((unsigned)(uintptr_t)&DAT_10010940);
  do {
    if (*piVar4 == iVar3) {
      puVar11 = (undefined4 *)((unsigned)(uintptr_t)&DAT_100145e8);
      for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar11 = 0;
        puVar11 = puVar11 + 1;
      }
      *(undefined1 *)puVar11 = 0;
      uVar5 = 0;
      iVar8 = iVar8 * 0x30;
      pbVar9 = (byte *)(iVar8 + ((unsigned)(uintptr_t)&DAT_10010950));
      do {
        bVar1 = *pbVar9;
        for (pbVar10 = pbVar9; (bVar1 != 0 && (bVar1 = pbVar10[1], bVar1 != 0));
            pbVar10 = pbVar10 + 2) {
          uVar6 = (uint)*pbVar10;
          if (uVar6 <= bVar1) {
            bVar2 = *(byte *)(uVar5 + ((unsigned)(uintptr_t)&DAT_10010938));
            do {
              *(byte *)(uVar6 + ((unsigned)(uintptr_t)&DAT_100145e9)) = *(byte *)(uVar6 + ((unsigned)(uintptr_t)&DAT_100145e9)) | bVar2;
              uVar6 = uVar6 + 1;
            } while (uVar6 <= bVar1);
          }
          bVar1 = pbVar10[2];
        }
        uVar5 = uVar5 + 1;
        pbVar9 = pbVar9 + 8;
      } while (uVar5 < 4);
      _DAT_100159c8 = 1;
      _DAT_100147f0 = iVar3;
      _DAT_100147f4 = msvc_CPtoLCID(iVar3);
      _DAT_100147f8 = *(undefined4 *)(iVar8 + ((unsigned)(uintptr_t)&DAT_10010944));
      _DAT_100147fc = *(undefined4 *)(iVar8 + ((unsigned)(uintptr_t)&DAT_10010948));
      _DAT_10014800 = *(undefined4 *)(iVar8 + ((unsigned)(uintptr_t)&DAT_1001094c));
      goto LAB_100083f2;
    }
    piVar4 = piVar4 + 0xc;
    iVar8 = iVar8 + 1;
  } while (piVar4 < (int *)((unsigned)(uintptr_t)&DAT_10010a30));
  iVar3 = GetCPInfo(iVar3,abStack_14);
  if (iVar3 == 1) {
    puVar11 = (undefined4 *)((unsigned)(uintptr_t)&DAT_100145e8);
    for (iVar3 = 0x40; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar11 = 0;
      puVar11 = puVar11 + 1;
    }
    *(undefined1 *)puVar11 = 0;
    _DAT_100147f0 = iStack_4;
    _DAT_100147f4 = 0;
    if (unaff_EBP < 2) {
      _DAT_100159c8 = 0;
    }
    else {
      if ((char)((uint)unaff_EBX >> 0x10) != '\0') {
        pbVar9 = (_stkneg + 27);
        do {
          bVar1 = *pbVar9;
          if (bVar1 == 0) break;
          for (uVar5 = (uint)pbVar9[-1]; uVar5 <= bVar1; uVar5 = uVar5 + 1) {
            *(byte *)(uVar5 + ((unsigned)(uintptr_t)&DAT_100145e9)) = *(byte *)(uVar5 + ((unsigned)(uintptr_t)&DAT_100145e9)) | 4;
          }
          pbVar10 = pbVar9 + 1;
          pbVar9 = pbVar9 + 2;
        } while (*pbVar10 != 0);
      }
      uVar5 = 1;
      do {
        *(byte *)(uVar5 + ((unsigned)(uintptr_t)&DAT_100145e9)) = *(byte *)(uVar5 + ((unsigned)(uintptr_t)&DAT_100145e9)) | 8;
        uVar5 = uVar5 + 1;
      } while (uVar5 < 0xff);
      _DAT_100147f4 = msvc_CPtoLCID(iStack_4);
      _DAT_100159c8 = 1;
    }
    _DAT_100147f8 = 0;
    _DAT_100147fc = 0;
    _DAT_10014800 = 0;
  }
  else {
    if (_DAT_10014804 == 0) {
      FUN_10006890();
      return 0xffffffff;
    }
    FUN_10008580();
  }
LAB_100083f2:
  FUN_100085c0();
  FUN_10006890();
  return 0;
}
#undef abStack_14
#undef iStack_4

#endif


/* ---- 0x100084d0  FUN_100084d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_100084d0(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    _DAT_10014804 = 1;
                    /* WARNING: Could not recover jumptable at 0x100084ed. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    _DAT_10014804 = 1;
                    /* WARNING: Could not recover jumptable at 0x10008502. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = _DAT_10014488;
  }
  _DAT_10014804 = (uint)bVar2;
  return param_1;
}
#endif

