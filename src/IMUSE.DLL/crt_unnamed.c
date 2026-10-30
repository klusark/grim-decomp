/* IMUSE.DLL :: crt_unnamed.c
 * functions 0x1000c0a0 .. 0x100147c0 (101 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000c0a0  FUN_1000c0a0 ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_1000c0a0(int param_1)

{
  bool bVar1;
  
  if (DAT_10032fe0 == 0) {
    if ((0x60 < param_1) && (param_1 < 0x7b)) {
      return param_1 + -0x20;
    }
  }
  else {
    InterlockedIncrement(IMG_ADDR(0x100337f0));
    bVar1 = DAT_100337ec != 0;
    if (bVar1) {
      InterlockedDecrement(IMG_ADDR(0x100337f0));
      ImFile_LockInit(0x13);
    }
    param_1 = FUN_1000c130(param_1);
    if (bVar1) {
      ImFile_UnlockInner(0x13);
      return param_1;
    }
    InterlockedDecrement(IMG_ADDR(0x100337f0));
  }
  return param_1;
}
#endif


/* ---- 0x1000c130  FUN_1000c130 ---- */
uint __cdecl FUN_1000c130(uint param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  int iVar3;
  #define local_8 (*(uint (*)[2])(_frame + (0x20 - 0x8)))
  
  uVar1 = param_1;
  if (DAT_10032fe0 == 0) {
    if ((0x60 < (int)param_1) && ((int)param_1 < 0x7b)) {
      return param_1 - 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if (DAT_1001f21c < 2) {
        uVar2 = (byte)PTR_DAT_1001f010[param_1 * 2] & 2;
      }
      else {
        uVar2 = _isctype(param_1,2);
      }
      if (uVar2 == 0) {
        return uVar1;
      }
    }
    uVar2 = param_1;
    if ((PTR_DAT_1001f010[((int)uVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      PIECE(param_1,0,2) = (ushort)(byte)uVar1;
      iVar3 = 1;
    }
    else {
      PIECE(param_1,0,2) = CONCAT11((byte)uVar1,(char)(uVar1 >> 8));
      PIECE(param_1,3,1) = SUB41(uVar2,3);
      PIECE(param_1,0,3) = (uint3)(ushort)param_1;
      iVar3 = 2;
    }
    iVar3 = __crtLCMapStringA(DAT_10032fe0,0x200,(char *)&param_1,iVar3,local_8,3,0,1);
    if (iVar3 == 0) {
      return uVar1;
    }
    if (iVar3 == 1) {
      return local_8[0] & 0xff;
    }
    param_1 = (local_8[0] >> 8 & 0xff) << 8 | local_8[0] & 0xff;
  }
  return param_1;
}
#undef local_8


/* ---- 0x1000c230  FUN_1000c230 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __stdcall FUN_1000c230(int a1,int a2,int a3)

{
  int iVar1;
  
  if (a2 != 1) {
    if (a2 != 0) {
      if (a2 == 3) {
        FUN_1000ec70((undefined *)0x0);
      }
      return 1;
    }
    if (0 < _DAT_10032f54) {
      _DAT_10032f54 = _DAT_10032f54 + -1;
      if (_DAT_10033044 == 0) {
        FUN_1000ea30();
      }
      FUN_1000ef30();
      FUN_1000eba0();
      FUN_1000f9e0();
      return 1;
    }
    return 0;
  }
  _DAT_1003300c = GetVersion();
  iVar1 = FUN_1000f9a0();
  if (iVar1 == 0) {
    return 0;
  }
  _DAT_10033018 = _DAT_1003300c >> 8 & 0xff;
  _DAT_10033014 = _DAT_1003300c & 0xff;
  _DAT_10033010 = _DAT_10033014 * 0x100 + _DAT_10033018;
  _DAT_1003300c = _DAT_1003300c >> 0x10;
  iVar1 = FUN_1000eb40();
  if (iVar1 == 0) {
    FUN_1000f9e0();
    return 0;
  }
  _DAT_10034804 = GetCommandLineA();
  _DAT_10032f58 = FUN_1000f840();
  if ((_DAT_10034804 != 0) && (_DAT_10032f58 != (char *)0x0)) {
    FUN_1000ed20();
    FUN_1000f830();
    FUN_1000f080();
    FUN_1000ef90();
    FUN_1000e9e0();
    _DAT_10032f54 = _DAT_10032f54 + 1;
    return 1;
  }
  FUN_1000eba0();
  FUN_1000f9e0();
  return 0;
}
#endif


/* ---- 0x1000c440  FUN_1000c440 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000c440(void)

{
  InitializeCriticalSection(_DAT_1001ea2c);
  InitializeCriticalSection(_DAT_1001ea1c);
  InitializeCriticalSection(_DAT_1001ea0c);
  InitializeCriticalSection(_DAT_1001e9ec);
  return;
}
#endif


/* ---- 0x1000c470  FUN_1000c470 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000c470(void)

{
  int *piVar1;
  
  piVar1 = (int *)&DAT_1001e9e8;
  do {
    if ((((*piVar1 != 0) && (piVar1 != (int *)&DAT_1001ea2c)) && (piVar1 != (int *)&DAT_1001ea1c))
       && ((piVar1 != (int *)&DAT_1001ea0c && (piVar1 != (int *)&DAT_1001e9ec)))) {
      DeleteCriticalSection(*piVar1);
      free((undefined *)*piVar1);
    }
    piVar1 = piVar1 + 1;
  } while ((int)piVar1 < IMG_ADDR(0x1001eaa8));
  DeleteCriticalSection(_DAT_1001ea0c);
  DeleteCriticalSection(_DAT_1001ea1c);
  DeleteCriticalSection(_DAT_1001ea2c);
  DeleteCriticalSection(_DAT_1001e9ec);
  return;
}
#endif


/* ---- 0x1000d4e0  FUN_1000d4e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_1000d4e0(int *param_1)

{
  int iVar1;
  
  iVar1 = _flush(param_1);
  if (iVar1 != 0) {
    return -1;
  }
  if ((param_1[3] & 0x4000U) != 0) {
    iVar1 = FUN_10010490(param_1[4]);
    return -(uint)(iVar1 != 0);
  }
  return 0;
}
#endif


/* ---- 0x1000d590  FUN_1000d590 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000d590(void)

{
  FUN_1000d5a0(1);
  return;
}
#endif


/* ---- 0x1000d5a0  FUN_1000d5a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_1000d5a0(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar3 = 0;
  iStack_4 = 0;
  iVar2 = 0;
  ImFile_LockInit(2);
  if (0 < _DAT_10034800) {
    do {
      iVar1 = *(int *)(_DAT_100337f4 + iVar3 * 4);
      if ((iVar1 != 0) && ((*(byte *)(iVar1 + 0xc) & 0x83) != 0)) {
        FUN_1000c5d0(iVar3,iVar1);
        iVar1 = *(int *)(_DAT_100337f4 + iVar3 * 4);
        if ((*(uint *)(iVar1 + 0xc) & 0x83) != 0) {
          if (param_1 == 1) {
            iVar1 = FUN_1000d4e0(iVar1);
            if (iVar1 != -1) {
              iStack_4 = iStack_4 + 1;
            }
          }
          else if (((param_1 == 0) && ((*(uint *)(iVar1 + 0xc) & 2) != 0)) &&
                  (iVar1 = FUN_1000d4e0(iVar1), iVar1 == -1)) {
            iVar2 = -1;
          }
        }
        FUN_1000c640(iVar3,*(int *)(_DAT_100337f4 + iVar3 * 4));
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < _DAT_10034800);
  }
  ImFile_UnlockInner(2);
  if (param_1 != 1) {
    iStack_4 = iVar2;
  }
  return iStack_4;
}
#undef iStack_4

#endif


/* ---- 0x1000d810  FUN_1000d810 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __cdecl
FUN_1000d810(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 *param_4)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  
  cVar1 = *param_2;
  bVar3 = false;
  bVar4 = false;
  if (cVar1 == 'a') {
    uVar5 = 0x109;
  }
  else {
    if (cVar1 == 'r') {
      uVar5 = 0;
      uVar7 = _DAT_10033384 | 1;
      goto LAB_1000d84d;
    }
    if (cVar1 != 'w') {
      return (undefined4 *)0x0;
    }
    uVar5 = 0x301;
  }
  uVar7 = _DAT_10033384 | 2;
LAB_1000d84d:
  pcVar6 = param_2 + 1;
  bVar2 = true;
  cVar1 = *pcVar6;
  do {
    if ((cVar1 == '\0') || (!bVar2)) {
      uVar5 = FUN_10010530(param_1,uVar5,param_3,0xa4);
      if (-1 < (int)uVar5) {
        DAT_10032fd0 = DAT_10032fd0 + 1;
        param_4[3] = uVar7;
        param_4[1] = 0;
        *param_4 = 0;
        param_4[2] = 0;
        param_4[7] = 0;
        param_4[4] = uVar5;
        return param_4;
      }
      return (undefined4 *)0x0;
    }
    switch(cVar1) {
    case '+':
      if ((uVar5 & 2) != 0) break;
      uVar5 = uVar5 & 0xfffffffe | 2;
      uVar7 = uVar7 & 0xfffffffc | 0x80;
      goto code_r0x1000d8fe;
    case 'D':
      if ((uVar5 & 0x40) == 0) {
        uVar5 = uVar5 | 0x40;
        goto code_r0x1000d8fe;
      }
      break;
    case 'R':
      if (!bVar4) {
        bVar4 = true;
        uVar5 = uVar5 | 0x10;
        goto code_r0x1000d8fe;
      }
      break;
    case 'S':
      if (!bVar4) {
        bVar4 = true;
        uVar5 = uVar5 | 0x20;
        goto code_r0x1000d8fe;
      }
      break;
    case 'T':
      if ((uVar5 & 0x1000) == 0) {
        uVar5 = uVar5 | 0x1000;
        goto code_r0x1000d8fe;
      }
      break;
    case 'b':
      if ((uVar5 & 0xc000) == 0) {
        uVar5 = uVar5 | 0x8000;
        goto code_r0x1000d8fe;
      }
      break;
    case 'c':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 | 0x4000;
        goto code_r0x1000d8fe;
      }
      break;
    case 'n':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 & 0xffffbfff;
        goto code_r0x1000d8fe;
      }
      break;
    case 't':
      if ((uVar5 & 0xc000) == 0) {
        uVar5 = uVar5 | 0x4000;
        goto code_r0x1000d8fe;
      }
    }
    bVar2 = false;
code_r0x1000d8fe:
    pcVar6 = pcVar6 + 1;
    cVar1 = *pcVar6;
  } while( true );
}
#endif


/* ---- 0x1000d9e0  FUN_1000d9e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_1000d9e0(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar4 = (undefined4 *)0x0;
  ImFile_LockInit(2);
  iVar3 = 0;
  if (0 < _DAT_10034800) {
    do {
      iVar1 = *(int *)(_DAT_100337f4 + iVar3 * 4);
      if (iVar1 == 0) {
        iVar3 = iVar3 * 4;
        uVar2 = malloc(0x38);
        *(undefined4 *)(_DAT_100337f4 + iVar3) = uVar2;
        if (*(int *)(_DAT_100337f4 + iVar3) != 0) {
          InitializeCriticalSection(*(int *)(_DAT_100337f4 + iVar3) + 0x20);
          EnterCriticalSection(*(int *)(_DAT_100337f4 + iVar3) + 0x20);
          puVar4 = *(undefined4 **)(_DAT_100337f4 + iVar3);
        }
        break;
      }
      if ((*(byte *)(iVar1 + 0xc) & 0x83) == 0) {
        FUN_1000c5d0(iVar3,iVar1);
        iVar1 = *(int *)(_DAT_100337f4 + iVar3 * 4);
        if ((*(byte *)(iVar1 + 0xc) & 0x83) == 0) {
          puVar4 = *(undefined4 **)(_DAT_100337f4 + iVar3 * 4);
          break;
        }
        FUN_1000c640(iVar3,iVar1);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < _DAT_10034800);
  }
  if (puVar4 != (undefined4 *)0x0) {
    puVar4[1] = 0;
    puVar4[3] = 0;
    puVar4[2] = 0;
    *puVar4 = 0;
    puVar4[7] = 0;
    puVar4[4] = 0xffffffff;
  }
  ImFile_UnlockInner(2);
  return puVar4;
}
#endif


/* ---- 0x1000dac0  FUN_1000dac0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000dac0(void)

{
  FUN_10010910(0x10000,0x30000);
  return;
}
#endif


/* ---- 0x1000db30  FUN_1000db30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Removing unreachable block (ram,0x1000db21) */

undefined4 FUN_1000db30(void)

{
  int a1;
  code *pcVar1;
  undefined4 uVar2;
  
  a1 = GetModuleHandleA(&UNK_10015454);
  if ((a1 != 0) && (pcVar1 = (code *)GetProcAddress(a1,IMG_ADDR(0x10015438)), pcVar1 != (code *)0x0)) {
    uVar2 = (*pcVar1)(0);
    return uVar2;
  }
  return 0;
}
#endif


/* ---- 0x1000db60  FUN_1000db60 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000db60(char *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = FUN_1000e510((int)*param_1);
  if (iVar3 != 0x65) {
    do {
      param_1 = param_1 + 1;
      if (DAT_1001f21c < 2) {
        uVar4 = (byte)PTR_DAT_1001f010[*param_1 * 2] & 4;
      }
      else {
        uVar4 = _isctype((int)*param_1,4);
      }
    } while (uVar4 != 0);
  }
  cVar2 = *param_1;
  *param_1 = DAT_1001f220;
  do {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    *param_1 = cVar2;
    cVar2 = cVar1;
  } while (*param_1 != '\0');
  return;
}
#endif


/* ---- 0x1000dbc0  FUN_1000dbc0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000dbc0(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  
  cVar1 = *param_1;
  while ((cVar1 != '\0' && (cVar1 != DAT_1001f220))) {
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
    if (*pcVar4 == DAT_1001f220) {
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


/* ---- 0x1000dc30  FUN_1000dc30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1000dc30(double *param_1)

{
  if (0.0 <= *param_1) {
    return 1;
  }
  return 0;
}
#endif


/* ---- 0x1000dc50  FUN_1000dc50 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000dc50(int param_1,undefined4 *param_2,undefined4 param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define uStack_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  if (param_1 != 0) {
    FUN_10010f00(&uStack_8,param_3);
    *param_2 = uStack_8;
    param_2[1] = uStack_4;
    return;
  }
  FUN_10010f40(&param_3,param_3);
  *param_2 = param_3;
  return;
}
#undef uStack_4
#undef uStack_8

#endif


/* ---- 0x1000dcb0  FUN_1000dcb0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_1000dcb0(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define aiStack_28 (*(int (*)[4])(_frame + (0x40 - 0x28)))
  #define auStack_18 (*(undefined1 (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_10011020(*param_1,param_1[1],aiStack_28,auStack_18);
  ((code *)FUN_10010f80)((uint)(aiStack_28[0] == 0x2d) + param_2 + (uint)(0 < param_3),param_3 + 1,aiStack_28)
  ;
  FUN_1000dd30(param_2,param_3,param_4,aiStack_28,0);
  return param_2;
}
#undef aiStack_28
#undef auStack_18

#endif


/* ---- 0x1000dd30  FUN_1000dd30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined1 * FUN_1000dd30(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (param_5 != '\0') {
    FUN_1000e090(param_1 + (*param_4 == 0x2d),0 < param_2);
  }
  puVar1 = param_1;
  if (*param_4 == 0x2d) {
    *param_1 = 0x2d;
    puVar1 = param_1 + 1;
  }
  if (0 < param_2) {
    *puVar1 = puVar1[1];
    puVar1 = puVar1 + 1;
    *puVar1 = DAT_1001f220;
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


/* ---- 0x1000de30  FUN_1000de30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_1000de30(undefined4 *param_1,int param_2,int param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define iStack_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define iStack_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define auStack_18 (*(undefined1 (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_10011020(*param_1,param_1[1],&iStack_28,auStack_18);
  FUN_10010f80((uint)(iStack_28 == 0x2d) + param_2,iStack_24 + param_3,&iStack_28);
  FUN_1000dea0(param_2,param_3,&iStack_28,0);
  return param_2;
}
#undef auStack_18
#undef iStack_24
#undef iStack_28

#endif


/* ---- 0x1000dea0  FUN_1000dea0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined1 * FUN_1000dea0(undefined1 *param_1,uint param_2,int *param_3,char param_4)

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
    FUN_1000e090(puVar4,1);
    *puVar4 = 0x30;
    puVar4 = puVar4 + 1;
  }
  else {
    puVar4 = puVar4 + param_3[1];
  }
  if (0 < (int)param_2) {
    FUN_1000e090(puVar4,1);
    *puVar4 = DAT_1001f220;
    iVar1 = param_3[1];
    if (iVar1 < 0) {
      if ((param_4 != '\0') || (-iVar1 <= (int)param_2)) {
        param_2 = -iVar1;
      }
      FUN_1000e090(puVar4 + 1,param_2);
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


/* ---- 0x1000df60  FUN_1000df60 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000df60(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  char cVar2;
  char *pcVar3;
  #define iStack_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define iStack_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define auStack_18 (*(undefined1 (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_10011020(*param_1,param_1[1],&iStack_28,auStack_18);
  iVar1 = iStack_24 + -1;
  pcVar3 = (char *)((uint)(iStack_28 == 0x2d) + param_2);
  FUN_10010f80(pcVar3,param_3,&iStack_28);
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
    FUN_1000dea0(param_2,param_3,&iStack_28,1);
    return;
  }
  FUN_1000dd30(param_2,param_3,param_4,&iStack_28,1);
  return;
}
#undef auStack_18
#undef iStack_24
#undef iStack_28

#endif


/* ---- 0x1000e020  FUN_1000e020 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000e020(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                 undefined4 param_5)

{
  if ((param_3 != 0x65) && (param_3 != 0x45)) {
    if (param_3 == 0x66) {
      FUN_1000de30(param_1,param_2,param_4);
      return;
    }
    FUN_1000df60(param_1,param_2,param_4,param_5);
    return;
  }
  FUN_1000dcb0(param_1,param_2,param_4,param_5);
  return;
}
#endif


/* ---- 0x1000e090  FUN_1000e090 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000e090(char *param_1,int param_2)

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
    FUN_10011170(param_1 + param_2,param_1,~uVar2);
  }
  return;
}
#endif


/* ---- 0x1000e500  FUN_1000e500 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1000e500(void)

{
  return 0;
}
#endif


/* ---- 0x1000e510  FUN_1000e510 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_1000e510(uint param_1)

{
  bool bVar1;
  
  if (DAT_10032fe0 == 0) {
    if ((0x40 < (int)param_1) && ((int)param_1 < 0x5b)) {
      return param_1 + 0x20;
    }
  }
  else {
    InterlockedIncrement(IMG_ADDR(0x100337f0));
    bVar1 = DAT_100337ec != 0;
    if (bVar1) {
      InterlockedDecrement(IMG_ADDR(0x100337f0));
      ImFile_LockInit(0x13);
    }
    param_1 = _tolower_lk(param_1);
    if (bVar1) {
      ImFile_UnlockInner(0x13);
      return param_1;
    }
    InterlockedDecrement(IMG_ADDR(0x100337f0));
  }
  return param_1;
}
#endif


/* ---- 0x1000e9e0  FUN_1000e9e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000e9e0(void)

{
  if (_DAT_1001e9d0 != (code *)0x0) {
    (*_DAT_1001e9d0)();
  }
  _initterm((undefined4 *)IMG_ADDR(0x10017008),(undefined4 *)IMG_ADDR(0x10017010));
  _initterm((undefined4 *)&DAT_10017000,(undefined4 *)IMG_ADDR(0x10017004));
  return;
}
#endif


/* ---- 0x1000ea30  FUN_1000ea30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000ea30(void)

{
  doexit(0,0,1);
  return;
}
#endif


/* ---- 0x1000eb40  FUN_1000eb40 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1000eb40(void)

{
  int *a2;
  int iVar1;
  
  FUN_1000c440();
  DAT_1001f230 = TlsAlloc();
  if (DAT_1001f230 != -1) {
    a2 = calloc(1,0x74);
    if (a2 != (int *)0x0) {
      iVar1 = TlsSetValue(DAT_1001f230,(int)a2);
      if (iVar1 != 0) {
        _initptd((int)a2);
        iVar1 = GetCurrentThreadId();
        *a2 = iVar1;
        a2[1] = -1;
        return 1;
      }
    }
  }
  return 0;
}
#endif


/* ---- 0x1000eba0  FUN_1000eba0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000eba0(void)

{
  FUN_1000c470();
  if (DAT_1001f230 != -1) {
    TlsFree(DAT_1001f230);
    DAT_1001f230 = -1;
  }
  return;
}
#endif


/* ---- 0x1000ec70  FUN_1000ec70 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_1000ec70(undefined *param_1)

{
  if (DAT_1001f230 != -1) {
    if ((param_1 != (undefined *)0x0) ||
       (param_1 = (undefined *)TlsGetValue(DAT_1001f230), param_1 != (undefined *)0x0)) {
      if (*(undefined **)(param_1 + 0x24) != (undefined *)0x0) {
        free(*(undefined **)(param_1 + 0x24));
      }
      if (*(undefined **)(param_1 + 0x28) != (undefined *)0x0) {
        free(*(undefined **)(param_1 + 0x28));
      }
      if (*(undefined **)(param_1 + 0x30) != (undefined *)0x0) {
        free(*(undefined **)(param_1 + 0x30));
      }
      if (*(undefined **)(param_1 + 0x38) != (undefined *)0x0) {
        free(*(undefined **)(param_1 + 0x38));
      }
      if (*(undefined **)(param_1 + 0x40) != (undefined *)0x0) {
        free(*(undefined **)(param_1 + 0x40));
      }
      if (*(undefined **)(param_1 + 0x44) != (undefined *)0x0) {
        free(*(undefined **)(param_1 + 0x44));
      }
      if (*(undefined **)(param_1 + 0x50) != &DAT_10021bd0) {
        free(*(undefined **)(param_1 + 0x50));
      }
      free(param_1);
    }
    TlsSetValue(DAT_1001f230,0);
    return;
  }
  return;
}
#endif


/* ---- 0x1000ed20  FUN_1000ed20 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000ed20(void)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  uint uVar7;
  byte *pbVar8;
  #define local_48 (*(int *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(undefined1 (*)[50])(_frame + (0x60 - 0x44)))
  #define local_12 (*(short *)(_frame + (0x60 - 0x12)))
  #define local_10 (*(int **)(_frame + (0x60 - 0x10)))
  
  piVar2 = (int *)malloc(0x480);
  if (piVar2 == (int *)0x0) {
    _amsg_exit(0x1b);
  }
  DAT_100337e0 = 0x20;
  PTR_100336e0 = piVar2;
  if (piVar2 < piVar2 + 0x120) {
    do {
      *(undefined1 *)(piVar2 + 1) = 0;
      *piVar2 = -1;
      *(undefined1 *)((int)piVar2 + 5) = 10;
      piVar2[2] = 0;
      piVar2 = piVar2 + 9;
    } while (piVar2 < PTR_100336e0 + 0x120);
  }
  GetStartupInfoA((int)local_44);
  if ((local_12 != 0) && (local_10 != (int *)0x0)) {
    local_48 = *local_10;
    pbVar8 = (byte *)(local_10 + 1);
    pbVar6 = pbVar8 + local_48;
    if (0x7ff < local_48) {
      local_48 = 0x800;
    }
    if (DAT_100337e0 < local_48) {
      piVar2 = &DAT_100336e4;
      do {
        puVar3 = (undefined4 *)malloc(0x480);
        if (puVar3 == (undefined4 *)0x0) {
          local_48 = DAT_100337e0;
          break;
        }
        *piVar2 = (int)puVar3;
        DAT_100337e0 = DAT_100337e0 + 0x20;
        if (puVar3 < puVar3 + 0x120) {
          do {
            *(undefined1 *)(puVar3 + 1) = 0;
            *puVar3 = 0xffffffff;
            *(undefined1 *)((int)puVar3 + 5) = 10;
            puVar3[2] = 0;
            puVar3 = puVar3 + 9;
          } while (puVar3 < (undefined4 *)(*piVar2 + 0x480));
        }
        piVar2 = piVar2 + 1;
      } while (DAT_100337e0 < local_48);
    }
    uVar7 = 0;
    if (0 < local_48) {
      do {
        if (((*(int *)pbVar6 != -1) && ((*pbVar8 & 1) != 0)) &&
           (((*pbVar8 & 8) != 0 || (iVar4 = GetFileType(*(int *)pbVar6), iVar4 != 0)))) {
          piVar2 = (&PTR_100336e0)[(int)uVar7 >> 5];
          piVar2[(uVar7 & 0x1f) * 9] = *(int *)pbVar6;
          *(byte *)(piVar2 + (uVar7 & 0x1f) * 9 + 1) = *pbVar8;
        }
        uVar7 = uVar7 + 1;
        pbVar8 = pbVar8 + 1;
        pbVar6 = pbVar6 + 4;
      } while ((int)uVar7 < local_48);
    }
  }
  iVar4 = 0;
  do {
    piVar2 = PTR_100336e0 + iVar4 * 9;
    if (PTR_100336e0[iVar4 * 9] == -1) {
      *(undefined1 *)(piVar2 + 1) = 0x81;
      if (iVar4 == 0) {
        iVar5 = -10;
      }
      else {
        iVar5 = -0xb - (uint)(iVar4 != 1);
      }
      iVar5 = GetStdHandle(iVar5);
      if ((iVar5 == -1) || (uVar7 = GetFileType(iVar5), uVar7 == 0)) {
        bVar1 = *(byte *)(piVar2 + 1) | 0x40;
        goto LAB_1000ef0e;
      }
      *piVar2 = iVar5;
      if ((uVar7 & 0xff) == 2) {
        bVar1 = *(byte *)(piVar2 + 1) | 0x40;
        goto LAB_1000ef0e;
      }
      if ((uVar7 & 0xff) == 3) {
        bVar1 = *(byte *)(piVar2 + 1) | 8;
        goto LAB_1000ef0e;
      }
    }
    else {
      bVar1 = *(byte *)(piVar2 + 1) | 0x80;
LAB_1000ef0e:
      *(byte *)(piVar2 + 1) = bVar1;
    }
    iVar4 = iVar4 + 1;
    if (2 < iVar4) {
      SetHandleCount(DAT_100337e0);
      return;
    }
  } while( true );
}
#undef local_10
#undef local_12
#undef local_44
#undef local_48

#endif


/* ---- 0x1000ef30  FUN_1000ef30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000ef30(void)

{
  int **ppiVar1;
  int *piVar2;
  int *piVar3;
  
  ppiVar1 = &PTR_100336e0;
  do {
    piVar2 = *ppiVar1;
    if (piVar2 != (int *)0x0) {
      if (piVar2 < piVar2 + 0x120) {
        piVar3 = piVar2 + 3;
        do {
          if (piVar3[-1] != 0) {
            DeleteCriticalSection(piVar3);
          }
          piVar2 = piVar2 + 9;
          piVar3 = piVar3 + 9;
        } while (piVar2 < *ppiVar1 + 0x120);
      }
      free((undefined *)*ppiVar1);
      *ppiVar1 = (int *)0x0;
    }
    ppiVar1 = ppiVar1 + 1;
  } while ((int)ppiVar1 < IMG_ADDR(0x100337e0));
  return;
}
#endif


/* ---- 0x1000ef90  FUN_1000ef90 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000ef90(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
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
  #define local_4 (*(int **)(_frame + (0x20 - 0x4)))
  
  iVar8 = 0;
  cVar2 = *_DAT_10032f58;
  pcVar7 = _DAT_10032f58;
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
  piVar3 = (int *)malloc(iVar8 * 4 + 4);
  _DAT_10033028 = piVar3;
  if (piVar3 == (int *)0x0) {
    _amsg_exit(9);
  }
  cVar2 = *_DAT_10032f58;
  local_4 = piVar3;
  pcVar7 = _DAT_10032f58;
  do {
    if (cVar2 == '\0') {
      free(_DAT_10032f58);
      _DAT_10032f58 = (char *)0x0;
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
      iVar8 = malloc(uVar4);
      *piVar3 = iVar8;
      if (iVar8 == 0) {
        _amsg_exit(9);
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
      pcVar10 = (char *)*local_4;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar10 = pcVar10 + 4;
      }
      piVar3 = local_4 + 1;
      for (uVar5 = uVar5 & 3; local_4 = piVar3, uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar10 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar10 = pcVar10 + 1;
      }
    }
    cVar2 = pcVar7[uVar4];
    pcVar7 = pcVar7 + uVar4;
  } while( true );
}
#undef local_4

#endif


/* ---- 0x1000f080  FUN_1000f080 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000f080(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  byte *pbVar2;
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  GetModuleFileNameA(0,IMG_ADDR(0x10033050),0x104);
  _DAT_10033038 = IMG_ADDR(0x10033050);
  pbVar2 = _DAT_10034804;
  if (*_DAT_10034804 == 0) {
    pbVar2 = (byte *)IMG_ADDR(0x10033050);
  }
  FUN_1000f120(pbVar2,(undefined4 *)0x0,(byte *)0x0,&iStack_8,&iStack_4);
  puVar1 = (undefined4 *)malloc(iStack_4 + iStack_8 * 4);
  if (puVar1 == (undefined4 *)0x0) {
    _amsg_exit(8);
  }
  FUN_1000f120(pbVar2,puVar1,(byte *)(puVar1 + iStack_8),&iStack_8,&iStack_4);
  _DAT_10033020 = puVar1;
  _DAT_1003301c = iStack_8 + -1;
  return;
}
#undef iStack_4
#undef iStack_8

#endif


/* ---- 0x1000f120  FUN_1000f120 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_1000f120(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5)

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
      if (((*(byte *)(bVar2 + IMG_ADDR(0x10033159)) & 4) != 0) &&
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
      if ((*(byte *)((int)param_5 + IMG_ADDR(0x10033159)) & 4) != 0) {
        *piVar6 = *piVar6 + 1;
        if (param_3 != (byte *)0x0) {
          *param_3 = *pbVar7;
          param_3 = param_3 + 1;
        }
        pbVar7 = param_1 + 2;
      }
      if (bVar2 == 0x20) break;
      if (bVar2 == 0) goto LAB_1000f1f9;
      param_1 = pbVar7;
    } while (bVar2 != 9);
    if (bVar2 == 0) {
LAB_1000f1f9:
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
          if ((*(byte *)(bVar2 + IMG_ADDR(0x10033159)) & 4) != 0) {
            pbVar7 = pbVar7 + 1;
            *piVar6 = *piVar6 + 1;
          }
          *piVar6 = *piVar6 + 1;
          goto LAB_1000f2f5;
        }
        if ((*(byte *)(bVar2 + IMG_ADDR(0x10033159)) & 4) != 0) {
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
LAB_1000f2f5:
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


/* ---- 0x1000f330  FUN_1000f330 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_1000f330(int param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte bVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  byte *pbVar10;
  undefined4 *puVar11;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define abStack_e (*(byte (*)[14])(_frame + (0x30 - 0xe)))
  
  ImFile_LockInit(0x19);
  iVar3 = FUN_1000f560(param_1);
  if (iVar3 == _DAT_10033360) {
    ImFile_UnlockInner(0x19);
    return 0;
  }
  if (iVar3 == 0) {
    FUN_1000f610();
    FUN_1000f650();
    ImFile_UnlockInner(0x19);
    return 0;
  }
  iVar8 = 0;
  piVar4 = (int *)IMG_ADDR(0x1001f268);
  do {
    if (*piVar4 == iVar3) {
      puVar11 = (undefined4 *)IMG_ADDR(0x10033158);
      for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar11 = 0;
        puVar11 = puVar11 + 1;
      }
      *(undefined1 *)puVar11 = 0;
      uVar5 = 0;
      iVar8 = iVar8 * 0x30;
      pbVar9 = (byte *)(iVar8 + IMG_ADDR(0x1001f278));
      do {
        bVar1 = *pbVar9;
        for (pbVar10 = pbVar9; (bVar1 != 0 && (bVar1 = pbVar10[1], bVar1 != 0));
            pbVar10 = pbVar10 + 2) {
          uVar6 = (uint)*pbVar10;
          if (uVar6 <= bVar1) {
            bVar2 = *(byte *)(uVar5 + IMG_ADDR(0x1001f260));
            do {
              *(byte *)(uVar6 + IMG_ADDR(0x10033159)) = *(byte *)(uVar6 + IMG_ADDR(0x10033159)) | bVar2;
              uVar6 = uVar6 + 1;
            } while (uVar6 <= bVar1);
          }
          bVar1 = pbVar10[2];
        }
        uVar5 = uVar5 + 1;
        pbVar9 = pbVar9 + 8;
      } while (uVar5 < 4);
      _DAT_100336c4 = 1;
      _DAT_10033360 = iVar3;
      _DAT_10033364 = FUN_1000f5b0(iVar3);
      _DAT_10033368 = *(undefined4 *)(iVar8 + IMG_ADDR(0x1001f26c));
      _DAT_1003336c = *(undefined4 *)(iVar8 + IMG_ADDR(0x1001f270));
      _DAT_10033370 = *(undefined4 *)(iVar8 + IMG_ADDR(0x1001f274));
      goto LAB_1000f482;
    }
    piVar4 = piVar4 + 0xc;
    iVar8 = iVar8 + 1;
  } while (piVar4 < (int *)IMG_ADDR(0x1001f358));
  iVar8 = GetCPInfo(iVar3,&local_14);
  if (iVar8 == 1) {
    puVar11 = (undefined4 *)IMG_ADDR(0x10033158);
    for (iVar8 = 0x40; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar11 = 0;
      puVar11 = puVar11 + 1;
    }
    *(undefined1 *)puVar11 = 0;
    _DAT_10033364 = 0;
    if (local_14 < 2) {
      _DAT_100336c4 = 0;
      _DAT_10033360 = iVar3;
    }
    else {
      _DAT_10033360 = iVar3;
      if (abStack_e[0] != 0) {
        pbVar9 = abStack_e + 1;
        do {
          bVar1 = *pbVar9;
          if (bVar1 == 0) break;
          for (uVar5 = (uint)pbVar9[-1]; uVar5 <= bVar1; uVar5 = uVar5 + 1) {
            *(byte *)(uVar5 + IMG_ADDR(0x10033159)) = *(byte *)(uVar5 + IMG_ADDR(0x10033159)) | 4;
          }
          pbVar10 = pbVar9 + 1;
          pbVar9 = pbVar9 + 2;
        } while (*pbVar10 != 0);
      }
      uVar5 = 1;
      do {
        *(byte *)(uVar5 + IMG_ADDR(0x10033159)) = *(byte *)(uVar5 + IMG_ADDR(0x10033159)) | 8;
        uVar5 = uVar5 + 1;
      } while (uVar5 < 0xff);
      _DAT_10033364 = FUN_1000f5b0(iVar3);
      _DAT_100336c4 = 1;
    }
    _DAT_10033368 = 0;
    _DAT_1003336c = 0;
    _DAT_10033370 = 0;
  }
  else {
    if (_DAT_10033374 == 0) {
      ImFile_UnlockInner(0x19);
      return 0xffffffff;
    }
    FUN_1000f610();
  }
LAB_1000f482:
  FUN_1000f650();
  ImFile_UnlockInner(0x19);
  return 0;
}
#undef abStack_e
#undef local_14

#endif


/* ---- 0x1000f560  FUN_1000f560 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl FUN_1000f560(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    _DAT_10033374 = 1;
                    /* WARNING: Could not recover jumptable at 0x1000f57d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    _DAT_10033374 = 1;
                    /* WARNING: Could not recover jumptable at 0x1000f592. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_10032ff0;
  }
  _DAT_10033374 = (uint)bVar2;
  return param_1;
}
#endif


/* ---- 0x1000f5b0  FUN_1000f5b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_1000f5b0(undefined4 param_1)

{
  switch(param_1) {
  case 0x3a4:
    return 0x411;
  default:
    return 0;
  case 0x3a8:
    return 0x804;
  case 0x3b5:
    return 0x412;
  case 0x3b6:
    return 0x404;
  }
}
#endif


/* ---- 0x1000f610  FUN_1000f610 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000f610(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)IMG_ADDR(0x10033158);
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  _DAT_10033360 = 0;
  _DAT_100336c4 = 0;
  _DAT_10033364 = 0;
  _DAT_10033368 = 0;
  _DAT_1003336c = 0;
  _DAT_10033370 = 0;
  return;
}
#endif


/* ---- 0x1000f650  FUN_1000f650 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000f650(void)

{
  unsigned char _frame[0x530] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[1328] __attribute__((aligned(16)));  /* the original frame below the return address */
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  ushort *puVar7;
  undefined4 unaff_EBX;
  char *pcVar8;
  #define local_514 (*(byte (*)[12])(_frame + (0x530 - 0x514)))
  #define acStack_508 (*(char (*)[256])(_frame + (0x530 - 0x508)))
  #define auStack_408 (*(undefined1 (*)[256])(_frame + (0x530 - 0x408)))
  #define auStack_308 (*(undefined1 (*)[256])(_frame + (0x530 - 0x308)))
  #define auStack_208 (*(ushort (*)[260])(_frame + (0x530 - 0x208)))
  
  iVar2 = GetCPInfo(_DAT_10033360,local_514);
  if (iVar2 == 1) {
    uVar3 = 0;
    do {
      acStack_508[uVar3] = (char)uVar3;
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x100);
    bVar1 = (byte)((uint)unaff_EBX >> 0x10);
    acStack_508[0] = ' ';
    if (bVar1 != 0) {
      pbVar6 = (_stkneg + 27);
      do {
        uVar3 = (uint)bVar1;
        if (uVar3 <= *pbVar6) {
          uVar4 = (*pbVar6 - uVar3) + 1;
          uVar5 = uVar4 >> 2;
          pcVar8 = acStack_508 + uVar3;
          while (uVar5 != 0) {
            uVar5 = uVar5 - 1;
            builtin_strncpy(pcVar8,"    ",4);
            pcVar8 = pcVar8 + 4;
          }
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *pcVar8 = ' ';
            pcVar8 = pcVar8 + 1;
          }
        }
        bVar1 = pbVar6[1];
        pbVar6 = pbVar6 + 2;
      } while (bVar1 != 0);
    }
    __crtGetStringTypeA(1,acStack_508,0x100,auStack_208,_DAT_10033360,_DAT_10033364,0);
    __crtLCMapStringA(_DAT_10033364,0x100,acStack_508,0x100,auStack_408,0x100,_DAT_10033360,0);
    __crtLCMapStringA(_DAT_10033364,0x200,acStack_508,0x100,auStack_308,0x100,_DAT_10033360,0);
    uVar3 = 0;
    puVar7 = auStack_208;
    do {
      if ((*puVar7 & 1) == 0) {
        if ((*puVar7 & 2) == 0) {
          *(undefined1 *)(uVar3 + IMG_ADDR(0x10033260)) = 0;
        }
        else {
          *(byte *)(uVar3 + IMG_ADDR(0x10033159)) = *(byte *)(uVar3 + IMG_ADDR(0x10033159)) | 0x20;
          *(undefined1 *)(uVar3 + IMG_ADDR(0x10033260)) = auStack_308[uVar3];
        }
      }
      else {
        *(byte *)(uVar3 + IMG_ADDR(0x10033159)) = *(byte *)(uVar3 + IMG_ADDR(0x10033159)) | 0x10;
        *(undefined1 *)(uVar3 + IMG_ADDR(0x10033260)) = auStack_408[uVar3];
      }
      uVar3 = uVar3 + 1;
      puVar7 = puVar7 + 1;
    } while (uVar3 < 0x100);
    return;
  }
  uVar3 = 0;
  do {
    if ((uVar3 < 0x41) || (0x5a < uVar3)) {
      if ((uVar3 < 0x61) || (0x7a < uVar3)) {
        *(undefined1 *)(uVar3 + IMG_ADDR(0x10033260)) = 0;
      }
      else {
        *(byte *)(uVar3 + IMG_ADDR(0x10033159)) = *(byte *)(uVar3 + IMG_ADDR(0x10033159)) | 0x20;
        *(char *)(uVar3 + IMG_ADDR(0x10033260)) = (char)uVar3 + -0x20;
      }
    }
    else {
      *(byte *)(uVar3 + IMG_ADDR(0x10033159)) = *(byte *)(uVar3 + IMG_ADDR(0x10033159)) | 0x10;
      *(char *)(uVar3 + IMG_ADDR(0x10033260)) = (char)uVar3 + ' ';
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x100);
  return;
}
#undef acStack_508
#undef auStack_208
#undef auStack_308
#undef auStack_408
#undef local_514

#endif


/* ---- 0x1000f830  FUN_1000f830 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000f830(void)

{
  FUN_1000f330(-3);
  return;
}
#endif


/* ---- 0x1000f840  FUN_1000f840 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * FUN_1000f840(void)

{
  char cVar1;
  short sVar2;
  short *psVar3;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  short *a3;
  char *pcVar10;
  char *pcVar11;
  short *psVar4;
  
  a3 = (short *)0x0;
  pcVar9 = (char *)0x0;
  if (_DAT_1003337c == 0) {
    a3 = (short *)GetEnvironmentStringsW();
    if (a3 == (short *)0x0) {
      pcVar9 = (char *)GetEnvironmentStrings();
      if (pcVar9 == (char *)0x0) {
        return (char *)0x0;
      }
      _DAT_1003337c = 2;
    }
    else {
      _DAT_1003337c = 1;
    }
  }
  if (_DAT_1003337c == 1) {
    if ((a3 != (short *)0x0) || (a3 = (short *)GetEnvironmentStringsW(), a3 != (short *)0x0)) {
      sVar2 = *a3;
      psVar3 = a3;
      while (sVar2 != 0) {
        do {
          psVar4 = psVar3;
          psVar3 = psVar4 + 1;
        } while (*psVar3 != 0);
        psVar3 = psVar4 + 2;
        sVar2 = *psVar3;
      }
      iVar5 = ((int)psVar3 - (int)a3 >> 1) + 1;
      uVar6 = WideCharToMultiByte(0,0,(int)a3,iVar5,0,0,0,0);
      if ((uVar6 != 0) && (pcVar9 = (char *)malloc(uVar6), pcVar9 != (char *)0x0)) {
        iVar5 = WideCharToMultiByte(0,0,(int)a3,iVar5,(int)pcVar9,uVar6,0,0);
        if (iVar5 == 0) {
          free(pcVar9);
          pcVar9 = (char *)0x0;
        }
        FreeEnvironmentStringsW(a3);
        return pcVar9;
      }
      FreeEnvironmentStringsW(a3);
      return (char *)0x0;
    }
  }
  else if ((_DAT_1003337c == 2) &&
          ((pcVar9 != (char *)0x0 ||
           (pcVar9 = (char *)GetEnvironmentStrings(), pcVar9 != (char *)0x0)))) {
    cVar1 = *pcVar9;
    pcVar7 = pcVar9;
    while (cVar1 != '\0') {
      do {
        pcVar8 = pcVar7;
        pcVar7 = pcVar8 + 1;
      } while (pcVar8[1] != '\0');
      pcVar7 = pcVar8 + 2;
      cVar1 = pcVar8[2];
    }
    pcVar7 = pcVar7 + (1 - (int)pcVar9);
    pcVar8 = (char *)malloc((uint)pcVar7);
    if (pcVar8 != (char *)0x0) {
      pcVar10 = pcVar9;
      pcVar11 = pcVar8;
      for (uVar6 = (uint)pcVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar6 = (uint)pcVar7 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar11 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar11 = pcVar11 + 1;
      }
      FreeEnvironmentStringsA(pcVar9);
      return pcVar8;
    }
    FreeEnvironmentStringsA(pcVar9);
    return (char *)0x0;
  }
  return (char *)0x0;
}
#endif


/* ---- 0x1000f9a0  FUN_1000f9a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1000f9a0(void)

{
  undefined **ppuVar1;
  
  DAT_100336c0 = HeapCreate(0,0x1000,0);
  if (DAT_100336c0 == 0) {
    return 0;
  }
  ppuVar1 = __sbh_alloc_new_region();
  if (ppuVar1 == (undefined **)0x0) {
    HeapDestroy(DAT_100336c0);
    return 0;
  }
  return 1;
}
#endif


/* ---- 0x1000f9e0  FUN_1000f9e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000f9e0(void)

{
  undefined **ppuVar1;
  
  ppuVar1 = &PTR_LOOP_1001f420;
  do {
    if (ppuVar1[4] != (undefined *)0x0) {
      VirtualFree((int)ppuVar1[4],0,0x8000);
    }
    ppuVar1 = (undefined **)*ppuVar1;
  } while (ppuVar1 != &PTR_LOOP_1001f420);
  HeapDestroy(DAT_100336c0);
  return;
}
#endif


/* ---- 0x1000fa20  FUN_1000fa20 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __stdcall FUN_1000fa20(int a1,int a2,int a3)

{
  return 1;
}
#endif


/* ---- 0x1000fd50  FUN_1000fd50 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_1000fd50(undefined1 *param_1,ushort param_2)

{
  int iVar1;
  bool bVar2;
  
  InterlockedIncrement(IMG_ADDR(0x100337f0));
  bVar2 = DAT_100337ec != 0;
  if (bVar2) {
    InterlockedDecrement(IMG_ADDR(0x100337f0));
    ImFile_LockInit(0x13);
  }
  iVar1 = FUN_1000fdc0(param_1,param_2);
  if (!bVar2) {
    InterlockedDecrement(IMG_ADDR(0x100337f0));
    return iVar1;
  }
  ImFile_UnlockInner(0x13);
  return iVar1;
}
#endif


/* ---- 0x1000fdc0  FUN_1000fdc0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_1000fdc0(undefined1 *param_1,ushort param_2)

{
  undefined1 *a5;
  int iVar1;
  int *piVar2;
  
  a5 = param_1;
  if (param_1 == (undefined1 *)0x0) {
    return 0;
  }
  if (DAT_10032fe0 == 0) {
    if (param_2 < 0x100) {
      *param_1 = (char)param_2;
      return 1;
    }
  }
  else {
    param_1 = (undefined1 *)0x0;
    iVar1 = WideCharToMultiByte(DAT_10032ff0,0x220,(int)&param_2,1,(int)a5,DAT_1001f21c,0,
                                (int)&param_1);
    if ((iVar1 != 0) && (param_1 == (undefined1 *)0x0)) {
      return iVar1;
    }
  }
  piVar2 = _errno();
  *piVar2 = 0x2a;
  return -1;
}
#endif


/* ---- 0x1000fe40  FUN_1000fe40 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __stdcall FUN_1000fe40(int a1,int a2,int a3,int a4)

{
  ulonglong uVar1;
  longlong lVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  iVar3 = a1;
  uVar8 = a4;
  uVar5 = a2;
  uVar7 = a3;
  if (a4 == 0) {
    iVar3 = (int)(((ulonglong)(uint)a2 % (ulonglong)(uint)a3 << 0x20 | (ulonglong)(uint)a1) /
                 (ulonglong)(uint)a3);
  }
  else {
    do {
      uVar4 = uVar8 >> 1;
      uVar7 = (uint)(CONCAT14((uVar8 & 1) != 0,uVar7) >> 1);
      uVar6 = uVar5 >> 1;
      iVar3 = (int)(CONCAT14((uVar5 & 1) != 0,iVar3) >> 1);
      uVar8 = uVar4;
      uVar5 = uVar6;
    } while (uVar4 != 0);
    uVar1 = CONCAT44(uVar6,iVar3) / (ulonglong)uVar7;
    iVar3 = (int)uVar1;
    lVar2 = (ulonglong)(uint)a3 * (uVar1 & 0xffffffff);
    uVar7 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar8 = uVar7 + iVar3 * a4;
    if (((CARRY4(uVar7,iVar3 * a4)) || ((uint)a2 < uVar8)) ||
       (((uint)a2 <= uVar8 && ((uint)a1 < (uint)lVar2)))) {
      iVar3 = iVar3 + -1;
    }
  }
  return iVar3;
}
#endif


/* ---- 0x1000feb0  FUN_1000feb0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __stdcall FUN_1000feb0(int a1,int a2,int a3,int a4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  
  iVar6 = a1;
  uVar4 = a4;
  uVar8 = a2;
  uVar3 = a3;
  if (a4 == 0) {
    iVar6 = (int)(((ulonglong)(uint)a2 % (ulonglong)(uint)a3 << 0x20 | (ulonglong)(uint)a1) %
                 (ulonglong)(uint)a3);
  }
  else {
    do {
      uVar5 = uVar4 >> 1;
      uVar3 = (uint)(CONCAT14((uVar4 & 1) != 0,uVar3) >> 1);
      uVar7 = uVar8 >> 1;
      iVar6 = (int)(CONCAT14((uVar8 & 1) != 0,iVar6) >> 1);
      uVar4 = uVar5;
      uVar8 = uVar7;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar7,iVar6) / (ulonglong)uVar3;
    uVar3 = (int)uVar1 * a4;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)(uint)a3;
    uVar8 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar4 = (uint)lVar2;
    uVar5 = uVar8 + uVar3;
    if (((CARRY4(uVar8,uVar3)) || ((uint)a2 < uVar5)) || (((uint)a2 <= uVar5 && ((uint)a1 < uVar4)))
       ) {
      uVar4 = uVar4 - a3;
    }
    iVar6 = -(uVar4 - a1);
  }
  return iVar6;
}
#endif


/* ---- 0x100100e0  FUN_100100e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_100100e0(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int **ppiVar3;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_8 = 0xffffffff;
  ImFile_LockInit(0x12);
  local_4 = 0;
  iVar2 = 0;
  ppiVar3 = &PTR_100336e0;
  do {
    piVar1 = *ppiVar3;
    if (piVar1 == (int *)0x0) {
      piVar1 = (int *)malloc(0x480);
      if (piVar1 != (int *)0x0) {
        DAT_100337e0 = DAT_100337e0 + 0x20;
        (&PTR_100336e0)[local_4] = piVar1;
        if (piVar1 < piVar1 + 0x120) {
          do {
            *(undefined1 *)(piVar1 + 1) = 0;
            *piVar1 = -1;
            *(undefined1 *)((int)piVar1 + 5) = 10;
            piVar1[2] = 0;
            piVar1 = piVar1 + 9;
          } while (piVar1 < (&PTR_100336e0)[local_4] + 0x120);
        }
        local_8 = local_4 << 5;
        _lock_fhandle(local_8);
      }
      break;
    }
    if (piVar1 < piVar1 + 0x120) {
      do {
        if ((*(byte *)(piVar1 + 1) & 1) == 0) {
          if (piVar1[2] == 0) {
            ImFile_LockInit(0x11);
            if (piVar1[2] == 0) {
              InitializeCriticalSection((int)(piVar1 + 3));
              piVar1[2] = piVar1[2] + 1;
            }
            ImFile_UnlockInner(0x11);
          }
          EnterCriticalSection((int)(piVar1 + 3));
          if ((*(byte *)(piVar1 + 1) & 1) == 0) {
            *piVar1 = -1;
            local_8 = ((int)piVar1 - (int)*ppiVar3) / 0x24 + iVar2;
            break;
          }
          LeaveCriticalSection((int)(piVar1 + 3));
        }
        piVar1 = piVar1 + 9;
      } while (piVar1 < *ppiVar3 + 0x120);
    }
    if (local_8 != 0xffffffff) break;
    ppiVar3 = ppiVar3 + 1;
    local_4 = local_4 + 1;
    iVar2 = iVar2 + 0x20;
  } while ((int)ppiVar3 < IMG_ADDR(0x100337e0));
  ImFile_UnlockInner(0x12);
  return local_8;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x10010250  FUN_10010250 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_10010250(uint param_1,int param_2)

{
  int *piVar1;
  
  if (param_1 < DAT_100337e0) {
    if ((&PTR_100336e0)[(int)param_1 >> 5][(param_1 & 0x1f) * 9] == -1) {
      if (DAT_10032f64 == 1) {
        if (param_1 == 0) {
          SetStdHandle(-10,param_2);
        }
        else {
          if (param_1 == 1) {
            SetStdHandle(-0xb,param_2);
            PTR_100336e0[9] = param_2;
            return 0;
          }
          if (param_1 == 2) {
            SetStdHandle(-0xc,param_2);
            PTR_100336e0[0x12] = param_2;
            return 0;
          }
        }
      }
      (&PTR_100336e0)[(int)param_1 >> 5][(param_1 & 0x1f) * 9] = param_2;
      return 0;
    }
  }
  piVar1 = _errno();
  *piVar1 = 9;
  piVar1 = __doserrno();
  *piVar1 = 0;
  return 0xffffffff;
}
#endif


/* ---- 0x10010490  FUN_10010490 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10010490(uint param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  
  if (DAT_100337e0 <= param_1) {
LAB_1001051c:
    piVar3 = _errno();
    *piVar3 = 9;
    return 0xffffffff;
  }
  if ((*(byte *)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) == 0)
  goto LAB_1001051c;
  _lock_fhandle(param_1);
  if ((*(byte *)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0) {
    uVar1 = _get_osfhandle(param_1);
    iVar2 = FlushFileBuffers(uVar1);
    if (iVar2 == 0) {
      iVar2 = GetLastError();
    }
    else {
      iVar2 = 0;
    }
    uVar1 = 0;
    if (iVar2 == 0) goto LAB_1001050d;
    piVar3 = __doserrno();
    *piVar3 = iVar2;
  }
  piVar3 = _errno();
  *piVar3 = 9;
  uVar1 = 0xffffffff;
LAB_1001050d:
  _unlock_fhandle(param_1);
  return uVar1;
}
#endif


/* ---- 0x10010530  FUN_10010530 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl FUN_10010530(undefined4 param_1,uint param_2,undefined4 param_3,byte param_4)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  int *piVar7;
  undefined4 uVar8;
  uint uVar9;
  #define bStack_14 (*(byte *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint (*)[4])(_frame + (0x30 - 0x10)))
  
  local_10[1] = 0xc;
  local_10[2] = 0;
  local_10[3] = (uint)((param_2 & 0x80) == 0);
  uVar2 = param_2 & 3;
  if (uVar2 == 0) {
    local_10[0] = 0x80000000;
  }
  else if (uVar2 == 1) {
    local_10[0] = 0x40000000;
  }
  else {
    if (uVar2 != 2) goto LAB_10010864;
    local_10[0] = 0xc0000000;
  }
  switch(param_3) {
  case 0x10:
    uVar8 = 0;
    break;
  default:
    goto LAB_10010864;
  case 0x20:
    uVar8 = 1;
    break;
  case 0x30:
    uVar8 = 2;
    break;
  case 0x40:
    uVar8 = 3;
  }
  uVar2 = param_2 & 0x700;
  if (uVar2 < 0x101) {
    if (uVar2 == 0x100) {
      uVar2 = 4;
    }
    else {
      if (uVar2 != 0) goto LAB_10010864;
code_r0x10010636:
      uVar2 = 3;
    }
  }
  else if (uVar2 < 0x301) {
    if (uVar2 == 0x300) {
      uVar2 = 2;
    }
    else {
      if (uVar2 != 0x200) goto LAB_10010864;
code_r0x10010656:
      uVar2 = 5;
    }
  }
  else {
    if (uVar2 < 0x501) {
      if (uVar2 != 0x500) {
        if (uVar2 != 0x400) {
LAB_10010864:
          piVar7 = _errno();
          *piVar7 = 0x16;
          piVar7 = __doserrno();
          *piVar7 = 0;
          return 0xffffffff;
        }
        goto code_r0x10010636;
      }
    }
    else {
      if (uVar2 == 0x600) goto code_r0x10010656;
      if (uVar2 != 0x700) goto LAB_10010864;
    }
    uVar2 = 1;
  }
  uVar9 = 0x80;
  if (((param_2 & 0x100) != 0) && ((param_4 & ~(byte)(*(uint *)IMG_ADDR(0x10033008)) & 0x80) == 0)) {
    uVar9 = 1;
  }
  if ((param_2 & 0x40) != 0) {
    uVar9 = uVar9 | 0x4000000;
    local_10[0] = local_10[0] | 0x10000;
  }
  if ((param_2 & 0x1000) != 0) {
    uVar9 = uVar9 | 0x100;
  }
  if ((param_2 & 0x20) == 0) {
    if ((param_2 & 0x10) != 0) {
      uVar9 = uVar9 | 0x10000000;
    }
  }
  else {
    uVar9 = uVar9 | 0x8000000;
  }
  uVar3 = FUN_100100e0();
  if (uVar3 == 0xffffffff) {
    piVar7 = _errno();
    *piVar7 = 0x18;
    piVar7 = __doserrno();
    *piVar7 = 0;
    return 0xffffffff;
  }
  iVar4 = CreateFileA(param_1,local_10[0],uVar8,local_10 + 1,uVar2,uVar9,0);
  if (iVar4 == -1) {
code_r0x10010716:
    puVar6 = (undefined *)GetLastError();
    _dosmaperr(puVar6);
    _unlock_fhandle(uVar3);
    return 0xffffffff;
  }
  iVar5 = GetFileType(iVar4);
  if (iVar5 == 0) {
    CloseHandle(iVar4);
    goto code_r0x10010716;
  }
  bVar1 = (byte)(uVar2 >> 0x18);
  if (iVar5 == 2) {
    bVar1 = bVar1 | 0x40;
code_r0x10010751:
    uVar2 = (uint)bVar1 << 0x18;
  }
  else if (iVar5 == 3) {
    bVar1 = bVar1 | 8;
    goto code_r0x10010751;
  }
  FUN_10010250(uVar3,iVar4);
  uVar9 = uVar3 & 0x1f;
  *(byte *)((&PTR_100336e0)[(int)uVar3 >> 5] + uVar9 * 9 + 1) = (byte)(uVar2 >> 0x18) | 1;
  if ((((uVar2 & 0x48000000) == 0) && ((uVar2 & 0x80000000) != 0)) && ((bStack_14 & 2) != 0)) {
    iVar4 = _lseek_lk(uVar3,0xffffffff,2);
    if (iVar4 == -1) {
      piVar7 = __doserrno();
      if (*piVar7 != 0x83) {
code_r0x10010816:
        _close(uVar3);
        _unlock_fhandle(uVar3);
        return 0xffffffff;
      }
    }
    else {
      local_10[0] = local_10[0] & 0xffffff00;
      iVar4 = FUN_10013090(uVar3,(char *)local_10,1);
      if ((((iVar4 == 0) && ((char)local_10[0] == '\x1a')) && (iVar4 = FUN_10012f40(), iVar4 == -1))
         || (iVar4 = _lseek_lk(uVar3,0,0), iVar4 == -1)) goto code_r0x10010816;
    }
  }
  if (((uVar2 & 0x48000000) == 0) && ((bStack_14 & 8) != 0)) {
    *(byte *)((&PTR_100336e0)[(int)uVar3 >> 5] + uVar9 * 9 + 1) =
         *(byte *)((&PTR_100336e0)[(int)uVar3 >> 5] + uVar9 * 9 + 1) | 0x20;
  }
  _unlock_fhandle(uVar3);
  return uVar3;
}
#undef bStack_14
#undef local_10

#endif


/* ---- 0x100108d0  FUN_100108d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_100108d0(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = ((code *)FUN_10010930)();
  uVar1 = param_2 & param_1 | ~param_2 & uVar1;
  ((code *)FUN_100109d0)(uVar1);
  return uVar1;
}
#endif


/* ---- 0x10010910  FUN_10010910 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10010910(undefined4 param_1,uint param_2)

{
  FUN_100108d0(param_1,param_2 & 0xfff7ffff);
  return;
}
#endif


/* ---- 0x10010930  FUN_10010930 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_10010930(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if ((param_1 & 1) != 0) {
    uVar1 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    uVar1 = uVar1 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x80000;
  }
  uVar2 = param_1 & 0xc00;
  if (uVar2 < 0x401) {
    if (uVar2 == 0x400) {
      uVar1 = uVar1 | 0x100;
    }
  }
  else if (uVar2 == 0x800) {
    uVar1 = uVar1 | 0x200;
  }
  else if (uVar2 == 0xc00) {
    uVar1 = uVar1 | 0x300;
  }
  if ((param_1 & 0x300) == 0) {
    uVar1 = uVar1 | 0x20000;
  }
  else if ((param_1 & 0x300) == 0x200) {
    uVar1 = uVar1 | 0x10000;
  }
  if ((param_1 & 0x1000) != 0) {
    uVar1 = uVar1 | 0x40000;
  }
  return uVar1;
}
#endif


/* ---- 0x100109d0  FUN_100109d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100109d0(void)

{
  return;
}
#endif


/* ---- 0x10010a60  FUN_10010a60 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10010a60(int param_1,int param_2)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  
  bVar1 = (byte)(param_2 >> 0x1f);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  if ((*(uint *)(param_1 + iVar3 * 4) &
      ~(-1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) & 0x1f))) != 0) {
    return 0;
  }
  iVar3 = iVar3 + 1;
  if (iVar3 < 3) {
    piVar2 = (int *)(param_1 + iVar3 * 4);
    do {
      if (*piVar2 != 0) {
        return 0;
      }
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < 3);
    return 1;
  }
  return 1;
}
#endif


/* ---- 0x10010ad0  FUN_10010ad0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10010ad0(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  bVar1 = (byte)(param_2 >> 0x1f);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  iVar2 = FUN_100132c0(*(undefined4 *)(param_1 + iVar3 * 4),
                       1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) &
                            0x1f),param_1 + iVar3 * 4);
  iVar3 = iVar3 + -1;
  if (-1 < iVar3) {
    puVar4 = (undefined4 *)(param_1 + iVar3 * 4);
    do {
      if (iVar2 == 0) {
        return;
      }
      iVar2 = FUN_100132c0(*puVar4,1,puVar4);
      iVar3 = iVar3 + -1;
      puVar4 = puVar4 + -1;
    } while (-1 < iVar3);
  }
  return;
}
#endif


/* ---- 0x10010b40  FUN_10010b40 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10010b40(int param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  byte bVar2;
  int iVar3;
  undefined4 *puVar4;
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  uStack_4 = 0;
  bVar2 = (byte)(param_2 >> 0x1f);
  bVar2 = 0x1f - ((((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  if (((*(uint *)(param_1 + iVar3 * 4) & 1 << (bVar2 & 0x1f)) != 0) &&
     (iVar1 = FUN_10010a60(param_1,param_2 + 1), iVar1 == 0)) {
    uStack_4 = ((code *)FUN_10010ad0)(param_1,param_2 + -1);
  }
  *(uint *)(param_1 + iVar3 * 4) = *(uint *)(param_1 + iVar3 * 4) & -1 << (bVar2 & 0x1f);
  iVar3 = iVar3 + 1;
  if (iVar3 < 3) {
    puVar4 = (undefined4 *)(param_1 + iVar3 * 4);
    for (iVar1 = 3 - iVar3; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
  }
  return uStack_4;
}
#undef uStack_4

#endif


/* ---- 0x10010be0  FUN_10010be0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10010be0(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  param_1 = param_1 - (int)param_2;
  iVar1 = 3;
  do {
    *(undefined4 *)((int)param_2 + param_1) = *param_2;
    param_2 = param_2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}
#endif


/* ---- 0x10010c00  FUN_10010c00 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10010c00(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}
#endif


/* ---- 0x10010c10  FUN_10010c10 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10010c10(int *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*param_1 != 0) {
      return 0;
    }
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 1;
  } while (iVar1 < 3);
  return 1;
}
#endif


/* ---- 0x10010c30  FUN_10010c30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10010c30(uint *param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  
  iVar1 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar2 = (byte)(param_2 >> 0x1f);
  uVar5 = 0;
  bVar2 = (((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2;
  param_2 = 3;
  puVar6 = param_1;
  do {
    uVar4 = *puVar6 >> (bVar2 & 0x1f) | uVar5;
    uVar5 = (~(-1 << (bVar2 & 0x1f)) & *puVar6) << (0x20 - bVar2 & 0x1f);
    *puVar6 = uVar4;
    param_2 = param_2 + -1;
    puVar6 = puVar6 + 1;
  } while (param_2 != 0);
  iVar7 = 2;
  iVar3 = 8;
  do {
    if (iVar7 < iVar1) {
      *(undefined4 *)((int)param_1 + iVar3) = 0;
    }
    else {
      *(undefined4 *)((int)param_1 + iVar3) = *(undefined4 *)((int)param_1 + iVar3 + iVar1 * -4);
    }
    iVar7 = iVar7 + -1;
    iVar3 = iVar3 + -4;
  } while (-1 < iVar3);
  return;
}
#endif


/* ---- 0x10010cf0  FUN_10010cf0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10010cf0(ushort *param_1,uint *param_2,int *param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  #define uStack_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define iStack_10 (*(int *)(_frame + (0x30 - 0x10)))
  #define auStack_c (*(undefined1 (*)[12])(_frame + (0x30 - 0xc)))
  
  uVar1 = param_1[5];
  uStack_14 = *(uint *)(param_1 + 1);
  uStack_18 = *(uint *)(param_1 + 3);
  uVar4 = uVar1 & 0x7fff;
  iVar5 = uVar4 - 0x3fff;
  iStack_10 = (uint)*param_1 << 0x10;
  if (iVar5 == -0x3fff) {
    iVar5 = 0;
    iVar2 = FUN_10010c10(&uStack_18);
    if (iVar2 == 0) {
      FUN_10010c00(&uStack_18);
      uVar3 = 2;
      goto LAB_10010e71;
    }
  }
  else {
    FUN_10010be0(auStack_c,&uStack_18);
    iVar2 = FUN_10010b40(&uStack_18,param_3[2]);
    if (iVar2 != 0) {
      iVar5 = uVar4 - 0x3ffe;
    }
    iVar2 = param_3[1];
    if (iVar5 < iVar2 - param_3[2]) {
      FUN_10010c00(&uStack_18);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_10010e71;
    }
    if (iVar5 <= iVar2) {
      FUN_10010be0(&uStack_18,auStack_c);
      FUN_10010c30(&uStack_18,iVar2 - iVar5);
      FUN_10010b40(&uStack_18,param_3[2]);
      FUN_10010c30(&uStack_18,param_3[3] + 1);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_10010e71;
    }
    if (*param_3 <= iVar5) {
      FUN_10010c00(&uStack_18);
      uStack_18 = uStack_18 | 0x80000000;
      FUN_10010c30(&uStack_18,param_3[3]);
      iVar5 = param_3[5] + *param_3;
      uVar3 = 1;
      goto LAB_10010e71;
    }
    iVar5 = param_3[5] + iVar5;
    uStack_18 = uStack_18 & 0x7fffffff;
    FUN_10010c30(&uStack_18,param_3[3]);
  }
  uVar3 = 0;
LAB_10010e71:
  uStack_18 = iVar5 << (0x1fU - (char)param_3[3] & 0x1f) |
              -(uint)((uVar1 & 0x8000) != 0) & 0x80000000 | uStack_18;
  if (param_3[4] == 0x40) {
    param_2[1] = uStack_18;
    *param_2 = uStack_14;
    return uVar3;
  }
  if (param_3[4] == 0x20) {
    *param_2 = uStack_18;
  }
  return uVar3;
}
#undef auStack_c
#undef iStack_10
#undef uStack_14
#undef uStack_18

#endif


/* ---- 0x10010ec0  FUN_10010ec0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10010ec0(undefined4 param_1,undefined4 param_2)

{
  FUN_10010cf0(param_1,param_2,&DAT_1001f3f0);
  return;
}
#endif


/* ---- 0x10010ee0  FUN_10010ee0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10010ee0(undefined4 param_1,undefined4 param_2)

{
  FUN_10010cf0(param_1,param_2,IMG_ADDR(0x1001f408));
  return;
}
#endif


/* ---- 0x10010f00  FUN_10010f00 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10010f00(undefined4 param_1,undefined4 param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define auStack_c (*(undefined1 (*)[12])(_frame + (0x20 - 0xc)))
  
  FUN_100134c0(auStack_c,&param_2,param_2,0,0,0,0);
  FUN_10010ec0(auStack_c,param_1);
  return;
}
#undef auStack_c

#endif


/* ---- 0x10010f40  FUN_10010f40 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10010f40(undefined4 param_1,undefined4 param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define auStack_c (*(undefined1 (*)[12])(_frame + (0x20 - 0xc)))
  
  FUN_100134c0(auStack_c,&param_2,param_2,0,0,0,0);
  FUN_10010ee0(auStack_c,param_1);
  return;
}
#undef auStack_c

#endif


/* ---- 0x10010f80  FUN_10010f80 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10010f80(char *param_1,int param_2,int param_3)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  
  pcVar5 = *(char **)(param_3 + 0xc);
  pcVar7 = param_1 + 1;
  *param_1 = '0';
  pcVar1 = pcVar7;
  iVar6 = param_2;
  if (0 < param_2) {
    do {
      cVar2 = *pcVar5;
      if (cVar2 == '\0') {
        cVar2 = '0';
      }
      else {
        pcVar5 = pcVar5 + 1;
      }
      *pcVar1 = cVar2;
      pcVar1 = pcVar1 + 1;
      iVar6 = iVar6 + -1;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  *pcVar1 = '\0';
  if ((-1 < iVar6) && ('4' < *pcVar5)) {
    cVar2 = pcVar1[-1];
    while (pcVar5 = pcVar1 + -1, cVar2 == '9') {
      *pcVar5 = '0';
      cVar2 = pcVar1[-2];
      pcVar1 = pcVar5;
    }
    *pcVar5 = *pcVar5 + '\x01';
  }
  if (*param_1 == '1') {
    *(int *)(param_3 + 4) = *(int *)(param_3 + 4) + 1;
    return;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = pcVar7;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar5;
  } while (cVar2 != '\0');
  uVar3 = ~uVar3;
  pcVar7 = pcVar5 + -uVar3;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)param_1 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    param_1 = param_1 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *param_1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    param_1 = param_1 + 1;
  }
  return;
}
#endif


/* ---- 0x10011020  FUN_10011020 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int * FUN_10011020(undefined4 param_1,undefined4 param_2,int *param_3,char *param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  #define uStack_28 (*(undefined4 *)(_frame + (0x40 - 0x28)))
  #define uStack_24 (*(undefined4 *)(_frame + (0x40 - 0x24)))
  #define uStack_20 (*(undefined2 *)(_frame + (0x40 - 0x20)))
  #define sStack_1c (*(short *)(_frame + (0x40 - 0x1c)))
  #define cStack_1a (*(char *)(_frame + (0x40 - 0x1a)))
  #define acStack_18 (*(char (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_100110b0(&uStack_28,&param_1);
  iVar2 = FUN_10013c50(uStack_28,uStack_24,uStack_20,0x11,0,&sStack_1c);
  param_3[2] = iVar2;
  param_3[1] = (int)sStack_1c;
  *param_3 = (int)cStack_1a;
  uVar3 = 0xffffffff;
  pcVar5 = acStack_18;
  do {
    pcVar6 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar6 + -uVar3;
  pcVar6 = param_4;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  param_3[3] = (int)param_4;
  return param_3;
}
#undef acStack_18
#undef cStack_1a
#undef sStack_1c
#undef uStack_20
#undef uStack_24
#undef uStack_28

#endif


/* ---- 0x100110b0  FUN_100110b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100110b0(uint *param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar5;
  int iVar6;
  
  uVar4 = 0x80000000;
  uVar1 = *(ushort *)((int)param_2 + 6);
  uVar2 = *param_2;
  uVar3 = (uVar1 & 0x7ff0) >> 4;
  if (uVar3 == 0) {
    uVar4 = 0;
    if (((param_2[1] & 0xfffff) == 0) && (uVar2 == 0)) {
      param_1[1] = 0;
      *param_1 = 0;
      *(undefined2 *)(param_1 + 2) = 0;
      return;
    }
    iVar6 = 0x3c01;
  }
  else if (uVar3 == 0x7ff) {
    iVar6 = 0x7fff;
  }
  else {
    iVar6 = uVar3 + 0x3c00;
  }
  uVar5 = (ushort)iVar6;
  uVar3 = uVar2 >> 0x15 | (param_2[1] & 0xfffff) << 0xb | uVar4;
  param_1[1] = uVar3;
  *param_1 = uVar2 << 0xb;
  for (; uVar4 == 0; uVar4 = uVar4 & 0x80000000) {
    uVar4 = uVar3 * 2;
    uVar3 = *param_1 >> 0x1f | uVar4;
    iVar6 = iVar6 + 0xffff;
    uVar5 = (ushort)iVar6;
    param_1[1] = uVar3;
    *param_1 = *param_1 * 2;
  }
  *(ushort *)(param_1 + 2) = uVar5 | uVar1 & 0x8000;
  return;
}
#endif


/* ---- 0x10011170  FUN_10011170 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 * FUN_10011170(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if ((param_2 < param_1) && (param_1 < (undefined4 *)(param_3 + (int)param_2))) {
    param_2 = (undefined4 *)((param_3 - 4) + (int)param_2);
    puVar2 = (undefined4 *)((param_3 - 4) + (int)param_1);
    if (((uint)puVar2 & 3) == 0) {
      uVar1 = param_3 >> 2;
      param_3 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar2 = *param_2;
          param_2 = param_2 + -1;
          puVar2 = puVar2 + -1;
        }
        switch(param_3) {
        case 0:
          return param_1;
        case 2:
          goto code_r0x10011478;
        case 3:
          goto code_r0x1001148c;
        }
        goto code_r0x10011468;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto code_r0x10011460;
      case 1:
        goto code_r0x10011468;
      case 2:
        goto code_r0x10011478;
      case 3:
        goto code_r0x1001148c;
      default:
        uVar1 = param_3 - ((uint)puVar2 & 3);
        switch((uint)puVar2 & 3) {
        case 1:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          param_2 = (undefined4 *)((int)param_2 + -1);
          uVar1 = uVar1 >> 2;
          puVar2 = (undefined4 *)((int)puVar2 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto code_r0x10011478;
            case 3:
              goto code_r0x1001148c;
            }
            goto code_r0x10011468;
          }
          break;
        case 2:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
          param_2 = (undefined4 *)((int)param_2 + -2);
          puVar2 = (undefined4 *)((int)puVar2 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto code_r0x10011478;
            case 3:
              goto code_r0x1001148c;
            }
            goto code_r0x10011468;
          }
          break;
        case 3:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
          param_2 = (undefined4 *)((int)param_2 + -3);
          puVar2 = (undefined4 *)((int)puVar2 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto code_r0x10011478;
            case 3:
              goto code_r0x1001148c;
            }
            goto code_r0x10011468;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar2[7 - uVar1] = param_2[7 - uVar1];
    case 6:
      puVar2[6 - uVar1] = param_2[6 - uVar1];
    case 5:
      puVar2[5 - uVar1] = param_2[5 - uVar1];
    case 4:
      puVar2[4 - uVar1] = param_2[4 - uVar1];
    case 3:
      puVar2[3 - uVar1] = param_2[3 - uVar1];
    case 2:
      puVar2[2 - uVar1] = param_2[2 - uVar1];
    case 1:
      puVar2[1 - uVar1] = param_2[1 - uVar1];
      param_2 = param_2 + -uVar1;
      puVar2 = puVar2 + -uVar1;
    }
    switch(param_3) {
    case 1:
code_r0x10011468:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      return param_1;
    case 2:
code_r0x10011478:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      return param_1;
    case 3:
code_r0x1001148c:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
      return param_1;
    }
code_r0x10011460:
    return param_1;
  }
  puVar2 = param_1;
  if (((uint)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    param_3 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar2 = *param_2;
        param_2 = param_2 + 1;
        puVar2 = puVar2 + 1;
      }
      switch(param_3) {
      case 0:
        return param_1;
      case 2:
        goto code_r0x100112dc;
      case 3:
        goto code_r0x100112f0;
      }
      goto code_r0x100112d0;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto code_r0x100112c8;
    case 1:
      goto code_r0x100112d0;
    case 2:
      goto code_r0x100112dc;
    case 3:
      goto code_r0x100112f0;
    default:
      uVar1 = (param_3 - 4) + ((uint)param_1 & 3);
      switch((uint)param_1 & 3) {
      case 1:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 2) = *(undefined1 *)((int)param_2 + 2);
        param_2 = (undefined4 *)((int)param_2 + 3);
        puVar2 = (undefined4 *)((int)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto code_r0x100112dc;
          case 3:
            goto code_r0x100112f0;
          }
          goto code_r0x100112d0;
        }
        break;
      case 2:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        param_2 = (undefined4 *)((int)param_2 + 2);
        puVar2 = (undefined4 *)((int)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto code_r0x100112dc;
          case 3:
            goto code_r0x100112f0;
          }
          goto code_r0x100112d0;
        }
        break;
      case 3:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar2 = (undefined4 *)((int)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto code_r0x100112dc;
          case 3:
            goto code_r0x100112f0;
          }
          goto code_r0x100112d0;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar2[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar2[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar2[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar2[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar2[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar2[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar2[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar2 = puVar2 + uVar1;
  }
  switch(param_3) {
  case 1:
code_r0x100112d0:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    return param_1;
  case 2:
code_r0x100112dc:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
code_r0x100112f0:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
code_r0x100112c8:
  return param_1;
}
#endif


/* ---- 0x100114b0  FUN_100114b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100114b0(void)

{
  _amsg_exit(2);
  return;
}
#endif


/* ---- 0x10011be0  FUN_10011be0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10011be0(void)

{
  int *piVar1;
  int iVar2;
  
  if (_DAT_10032fec == 0) {
    _DAT_10021d04 = (int *)IMG_ADDR(0x10021c58);
    FUN_10012010(_DAT_1003338c);
    free((undefined *)_DAT_1003338c);
    _DAT_1003338c = (int *)0x0;
    return 0;
  }
  piVar1 = calloc(1,0xac);
  if (piVar1 == (int *)0x0) {
    return 1;
  }
  iVar2 = FUN_10011c90(piVar1);
  if (iVar2 != 0) {
    FUN_10012010(piVar1);
    free((undefined *)piVar1);
    return 1;
  }
  _DAT_10021d04 = piVar1;
  FUN_10012010(_DAT_1003338c);
  free((undefined *)_DAT_1003338c);
  _DAT_1003338c = piVar1;
  return 0;
}
#endif


/* ---- 0x10011c90  FUN_10011c90 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_10011c90(int param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  uint uVar28;
  uint uVar29;
  uint uVar30;
  uint uVar31;
  uint uVar32;
  uint uVar33;
  uint uVar34;
  uint uVar35;
  uint uVar36;
  uint uVar37;
  uint uVar38;
  uint uVar39;
  uint uVar40;
  uint uVar41;
  uint uVar42;
  uint uVar43;
  uint uVar44;
  uint uVar45;
  
  uVar2 = _DAT_100333c8;
  uVar1 = _DAT_100333c6;
  if (param_1 == 0) {
    return 0xffffffff;
  }
  uVar3 = FUN_10013fe0(1,_DAT_100333c6,0x31,param_1 + 4);
  uVar4 = FUN_10013fe0(1,uVar1,0x32,param_1 + 8);
  uVar5 = FUN_10013fe0(1,uVar1,0x33,param_1 + 0xc);
  uVar6 = FUN_10013fe0(1,uVar1,0x34,param_1 + 0x10);
  uVar7 = FUN_10013fe0(1,uVar1,0x35,param_1 + 0x14);
  uVar8 = FUN_10013fe0(1,uVar1,0x36,param_1 + 0x18);
  uVar9 = FUN_10013fe0(1,uVar1,0x37,param_1);
  uVar10 = FUN_10013fe0(1,uVar1,0x2a,param_1 + 0x20);
  uVar11 = FUN_10013fe0(1,uVar1,0x2b,param_1 + 0x24);
  uVar12 = FUN_10013fe0(1,uVar1,0x2c,param_1 + 0x28);
  uVar13 = FUN_10013fe0(1,uVar1,0x2d,param_1 + 0x2c);
  uVar14 = FUN_10013fe0(1,uVar1,0x2e,param_1 + 0x30);
  uVar15 = FUN_10013fe0(1,uVar1,0x2f,param_1 + 0x34);
  uVar16 = FUN_10013fe0(1,uVar1,0x30,param_1 + 0x1c);
  uVar17 = FUN_10013fe0(1,uVar1,0x44,param_1 + 0x38);
  uVar18 = FUN_10013fe0(1,uVar1,0x45,param_1 + 0x3c);
  uVar19 = FUN_10013fe0(1,uVar1,0x46,param_1 + 0x40);
  uVar20 = FUN_10013fe0(1,uVar1,0x47,param_1 + 0x44);
  uVar21 = FUN_10013fe0(1,uVar1,0x48,param_1 + 0x48);
  uVar22 = FUN_10013fe0(1,uVar1,0x49,param_1 + 0x4c);
  uVar23 = FUN_10013fe0(1,uVar1,0x4a,param_1 + 0x50);
  uVar24 = FUN_10013fe0(1,uVar1,0x4b,param_1 + 0x54);
  uVar25 = FUN_10013fe0(1,uVar1,0x4c,param_1 + 0x58);
  uVar26 = FUN_10013fe0(1,uVar1,0x4d,param_1 + 0x5c);
  uVar27 = FUN_10013fe0(1,uVar1,0x4e,param_1 + 0x60);
  uVar28 = FUN_10013fe0(1,uVar1,0x4f,param_1 + 100);
  uVar29 = FUN_10013fe0(1,uVar1,0x38,param_1 + 0x68);
  uVar30 = FUN_10013fe0(1,uVar1,0x39,param_1 + 0x6c);
  uVar31 = FUN_10013fe0(1,uVar1,0x3a,param_1 + 0x70);
  uVar32 = FUN_10013fe0(1,uVar1,0x3b,param_1 + 0x74);
  uVar33 = FUN_10013fe0(1,uVar1,0x3c,param_1 + 0x78);
  uVar34 = FUN_10013fe0(1,uVar1,0x3d,param_1 + 0x7c);
  uVar35 = FUN_10013fe0(1,uVar1,0x3e,param_1 + 0x80);
  uVar36 = FUN_10013fe0(1,uVar1,0x3f,param_1 + 0x84);
  uVar37 = FUN_10013fe0(1,uVar1,0x40,param_1 + 0x88);
  uVar38 = FUN_10013fe0(1,uVar1,0x41,param_1 + 0x8c);
  uVar39 = FUN_10013fe0(1,uVar1,0x42,param_1 + 0x90);
  uVar40 = FUN_10013fe0(1,uVar1,0x43,param_1 + 0x94);
  uVar41 = FUN_10013fe0(1,uVar1,0x28,param_1 + 0x98);
  uVar42 = FUN_10013fe0(1,uVar1,0x29,param_1 + 0x9c);
  uVar43 = FUN_10013fe0(1,uVar2,0x1f,param_1 + 0xa0);
  uVar44 = FUN_10013fe0(1,uVar2,0x20,param_1 + 0xa4);
  uVar45 = FUN_10012250(uVar2,param_1);
  return uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10 | uVar11 | uVar12 | uVar13 |
         uVar14 | uVar15 | uVar16 | uVar17 | uVar18 | uVar19 | uVar20 | uVar21 | uVar22 | uVar23 |
         uVar24 | uVar25 | uVar26 | uVar27 | uVar28 | uVar29 | uVar30 | uVar31 | uVar32 | uVar33 |
         uVar34 | uVar35 | uVar36 | uVar37 | uVar38 | uVar39 | uVar40 | uVar41 | uVar42 | uVar43 |
         uVar44 | uVar45;
}
#endif


/* ---- 0x10012010  FUN_10012010 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10012010(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    free((undefined *)param_1[1]);
    free((undefined *)param_1[2]);
    free((undefined *)param_1[3]);
    free((undefined *)param_1[4]);
    free((undefined *)param_1[5]);
    free((undefined *)param_1[6]);
    free((undefined *)*param_1);
    free((undefined *)param_1[8]);
    free((undefined *)param_1[9]);
    free((undefined *)param_1[10]);
    free((undefined *)param_1[0xb]);
    free((undefined *)param_1[0xc]);
    free((undefined *)param_1[0xd]);
    free((undefined *)param_1[7]);
    free((undefined *)param_1[0xe]);
    free((undefined *)param_1[0xf]);
    free((undefined *)param_1[0x10]);
    free((undefined *)param_1[0x11]);
    free((undefined *)param_1[0x12]);
    free((undefined *)param_1[0x13]);
    free((undefined *)param_1[0x14]);
    free((undefined *)param_1[0x15]);
    free((undefined *)param_1[0x16]);
    free((undefined *)param_1[0x17]);
    free((undefined *)param_1[0x18]);
    free((undefined *)param_1[0x19]);
    free((undefined *)param_1[0x1a]);
    free((undefined *)param_1[0x1b]);
    free((undefined *)param_1[0x1c]);
    free((undefined *)param_1[0x1d]);
    free((undefined *)param_1[0x1e]);
    free((undefined *)param_1[0x1f]);
    free((undefined *)param_1[0x20]);
    free((undefined *)param_1[0x21]);
    free((undefined *)param_1[0x22]);
    free((undefined *)param_1[0x23]);
    free((undefined *)param_1[0x24]);
    free((undefined *)param_1[0x25]);
    free((undefined *)param_1[0x26]);
    free((undefined *)param_1[0x27]);
    free((undefined *)param_1[0x28]);
    free((undefined *)param_1[0x29]);
    free((undefined *)param_1[0x2a]);
  }
  return;
}
#endif


/* ---- 0x10012250  FUN_10012250 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_10012250(char *param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *pcVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined1 *puVar6;
  char *pcVar7;
  char *pcVar8;
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  pcVar7 = param_1;
  iStack_4 = 0;
  iStack_8 = 0;
  uVar3 = FUN_10013fe0(0,param_1,0x23,&iStack_4);
  uVar4 = FUN_10013fe0(0,pcVar7,0x25,&iStack_8);
  uVar5 = FUN_10013fe0(1,pcVar7,0x1e,&param_1);
  uVar5 = uVar3 | uVar4 | uVar5;
  if (uVar5 != 0) {
    return uVar5;
  }
  puVar6 = (undefined1 *)malloc(0xd);
  *(undefined1 **)(param_2 + 0xa8) = puVar6;
  if (iStack_4 == 0) {
    *puVar6 = 0x68;
    pcVar7 = puVar6 + 1;
    if (iStack_8 == 0) goto LAB_100122ec;
    *pcVar7 = 'h';
  }
  else {
    *puVar6 = 0x48;
    pcVar7 = puVar6 + 1;
    if (iStack_8 == 0) goto LAB_100122ec;
    *pcVar7 = 'H';
  }
  pcVar7 = puVar6 + 2;
LAB_100122ec:
  cVar2 = *param_1;
  pcVar8 = param_1;
  while (cVar2 != '\0') {
    *pcVar7 = cVar2;
    pcVar1 = pcVar8 + 1;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
    cVar2 = *pcVar1;
  }
  *pcVar7 = 'm';
  pcVar8 = pcVar7 + 1;
  if (iStack_8 != 0) {
    *pcVar8 = 'm';
    pcVar8 = pcVar7 + 2;
  }
  cVar2 = *param_1;
  pcVar7 = param_1;
  while (cVar2 != '\0') {
    *pcVar8 = cVar2;
    pcVar1 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
    pcVar7 = pcVar7 + 1;
    cVar2 = *pcVar1;
  }
  *pcVar8 = 's';
  pcVar8[1] = 's';
  pcVar8[2] = '\0';
  free(param_1);
  return 0;
}
#undef iStack_4
#undef iStack_8

#endif


/* ---- 0x10012350  FUN_10012350 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10012350(void)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  uVar1 = _DAT_100333c2;
  if (_DAT_10032fe8 == 0) {
    free(_DAT_10033390);
    free(_DAT_10033394);
    free(_DAT_10033398);
    _DAT_10033390 = (undefined *)0x0;
    _DAT_10033394 = (undefined *)0x0;
    _DAT_10033398 = (undefined *)0x0;
    uVar5 = malloc(2);
    *_DAT_10021d40 = uVar5;
    if ((undefined2 *)*_DAT_10021d40 == (undefined2 *)0x0) {
      return 0xffffffff;
    }
    *(undefined2 *)*_DAT_10021d40 = 0x2e;
    uVar5 = malloc(2);
    _DAT_10021d40[1] = uVar5;
    if ((undefined1 *)_DAT_10021d40[1] == (undefined1 *)0x0) {
      return 0xffffffff;
    }
    *(undefined1 *)_DAT_10021d40[1] = 0;
    uVar5 = malloc(2);
    _DAT_10021d40[2] = uVar5;
    if ((undefined1 *)_DAT_10021d40[2] == (undefined1 *)0x0) {
      return 0xffffffff;
    }
    *(undefined1 *)_DAT_10021d40[2] = 0;
  }
  else {
    iVar2 = FUN_10013fe0(1,_DAT_100333c2,0xe,&DAT_10033390);
    iVar3 = FUN_10013fe0(1,uVar1,0xf,&DAT_10033394);
    iVar4 = FUN_10013fe0(1,uVar1,0x10,&DAT_10033398);
    FUN_10012790(_DAT_10033398);
    if ((iVar2 != 0 || iVar3 != 0) || iVar4 != 0) {
      free(_DAT_10033390);
      free(_DAT_10033394);
      free(_DAT_10033398);
      _DAT_10033390 = (undefined *)0x0;
      _DAT_10033394 = (undefined *)0x0;
      _DAT_10033398 = (undefined *)0x0;
      return 0xffffffff;
    }
    if ((undefined *)*_DAT_10021d40 != (undefined *)IMG_ADDR(0x10021d08)) {
      free((undefined *)*_DAT_10021d40);
      free((undefined *)_DAT_10021d40[1]);
      free((undefined *)_DAT_10021d40[2]);
    }
    *_DAT_10021d40 = _DAT_10033390;
    _DAT_10021d40[1] = _DAT_10033394;
    _DAT_10021d40[2] = _DAT_10033398;
  }
  _DAT_1001f224 = 1;
  DAT_1001f220 = *(undefined1 *)*_DAT_10021d40;
  return 0;
}
#endif


/* ---- 0x10012550  FUN_10012550 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10012550(void)

{
  int *piVar1;
  int iVar2;
  
  if (_DAT_10032fe4 == 0) {
    _DAT_10021d10 = *_DAT_10021d40;
    _DAT_10021d14 = _DAT_10021d40[1];
    _DAT_10021d18 = _DAT_10021d40[2];
    _DAT_10021d40 = (int *)&DAT_10021d10;
    FUN_100127d0(_DAT_1003339c);
    free((undefined *)_DAT_1003339c);
    _DAT_1003339c = (int *)0x0;
    return 0;
  }
  piVar1 = calloc(1,0x30);
  if (piVar1 == (int *)0x0) {
    return 1;
  }
  iVar2 = FUN_10012640(piVar1);
  if (iVar2 != 0) {
    FUN_100127d0(piVar1);
    free((undefined *)piVar1);
    return 1;
  }
  *piVar1 = *_DAT_10021d40;
  piVar1[1] = _DAT_10021d40[1];
  piVar1[2] = _DAT_10021d40[2];
  _DAT_10021d40 = piVar1;
  FUN_100127d0(_DAT_1003339c);
  free((undefined *)_DAT_1003339c);
  _DAT_1003339c = piVar1;
  return 0;
}
#endif


/* ---- 0x10012640  FUN_10012640 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_10012640(int param_1)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  
  uVar1 = _DAT_100333bc;
  if (param_1 == 0) {
    return 0xffffffff;
  }
  uVar2 = FUN_10013fe0(1,_DAT_100333bc,0x15,param_1 + 0xc);
  uVar3 = FUN_10013fe0(1,uVar1,0x14,param_1 + 0x10);
  uVar4 = FUN_10013fe0(1,uVar1,0x16,param_1 + 0x14);
  uVar5 = FUN_10013fe0(1,uVar1,0x17,param_1 + 0x18);
  uVar6 = FUN_10013fe0(1,uVar1,0x18,(undefined4 *)(param_1 + 0x1c));
  FUN_10012790(*(undefined4 *)(param_1 + 0x1c));
  uVar7 = FUN_10013fe0(1,uVar1,0x50,param_1 + 0x20);
  uVar8 = FUN_10013fe0(1,uVar1,0x51,param_1 + 0x24);
  uVar9 = FUN_10013fe0(0,uVar1,0x1a,param_1 + 0x28);
  uVar10 = FUN_10013fe0(0,uVar1,0x19,param_1 + 0x29);
  uVar11 = FUN_10013fe0(0,uVar1,0x54,param_1 + 0x2a);
  uVar12 = FUN_10013fe0(0,uVar1,0x55,param_1 + 0x2b);
  uVar13 = FUN_10013fe0(0,uVar1,0x56,param_1 + 0x2c);
  uVar14 = FUN_10013fe0(0,uVar1,0x57,param_1 + 0x2d);
  uVar15 = FUN_10013fe0(0,uVar1,0x52,param_1 + 0x2e);
  uVar16 = FUN_10013fe0(0,uVar1,0x53,param_1 + 0x2f);
  return uVar2 | uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10 | uVar11 | uVar12 |
         uVar13 | uVar14 | uVar15 | uVar16;
}
#endif


/* ---- 0x10012790  FUN_10012790 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10012790(char *param_1)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  
  cVar2 = *param_1;
  do {
    if (cVar2 == '\0') {
      return;
    }
    if ((cVar2 < '0') || ('9' < cVar2)) {
      pcVar3 = param_1;
      if (cVar2 != ';') goto LAB_100127a6;
      do {
        *pcVar3 = pcVar3[1];
        pcVar1 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
      } while (*pcVar1 != '\0');
    }
    else {
      *param_1 = cVar2 + -0x30;
LAB_100127a6:
      param_1 = param_1 + 1;
    }
    cVar2 = *param_1;
  } while( true );
}
#endif


/* ---- 0x100127d0  FUN_100127d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100127d0(int param_1)

{
  if ((param_1 != 0) && (*(undefined **)(param_1 + 0xc) != (undefined *)IMG_ADDR(0x10033438))) {
    free(*(undefined **)(param_1 + 0xc));
    free(*(undefined **)(param_1 + 0x10));
    free(*(undefined **)(param_1 + 0x14));
    free(*(undefined **)(param_1 + 0x18));
    free(*(undefined **)(param_1 + 0x1c));
    free(*(undefined **)(param_1 + 0x20));
    free(*(undefined **)(param_1 + 0x24));
  }
  return;
}
#endif


/* ---- 0x10012840  FUN_10012840 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10012840(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  undefined2 *puVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  undefined2 *puVar6;
  undefined2 *puVar7;
  undefined2 *puVar8;
  undefined *puVar9;
  #define puStack_1c (*(undefined2 **)(_frame + (0x30 - 0x1c)))
  #define puStack_18 (*(undefined2 **)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define abStack_e (*(byte (*)[14])(_frame + (0x30 - 0xe)))
  
  puVar9 = (undefined *)0x0;
  puVar8 = (undefined2 *)0x0;
  if (DAT_10032fe0 == 0) {
    PTR_DAT_1001f010 = &DAT_1001f01a;
    _DAT_1001f014 = (undefined2 *)&DAT_1001f01a;
    free((undefined *)_DAT_100333a0);
    free((undefined *)_DAT_100333a4);
    _DAT_100333a0 = (undefined2 *)0x0;
    _DAT_100333a4 = (undefined2 *)0x0;
    return 0;
  }
  if ((DAT_10032ff0 != 0) || (iVar3 = FUN_10013fe0(0,_DAT_100333b4,0xb,&DAT_10032ff0), iVar3 == 0))
  {
    puStack_18 = (undefined2 *)malloc(0x202);
    puStack_1c = (undefined2 *)malloc(0x202);
    puVar9 = (undefined *)malloc(0x101);
    puVar8 = (undefined2 *)malloc(0x202);
    if ((puStack_18 != (undefined2 *)0x0) &&
       (((puStack_1c != (undefined2 *)0x0 && (puVar9 != (undefined *)0x0)) &&
        (puVar8 != (undefined2 *)0x0)))) {
      iVar3 = 0;
      do {
        puVar9[iVar3] = (char)iVar3;
        iVar3 = iVar3 + 1;
      } while (iVar3 < 0x100);
      iVar3 = GetCPInfo(DAT_10032ff0,&uStack_14);
      if ((iVar3 != 0) && (uStack_14 < 3)) {
        DAT_1001f21c = uStack_14 & 0xffff;
        if ((1 < DAT_1001f21c) && (abStack_e[0] != 0)) {
          pbVar5 = abStack_e + 1;
          do {
            if (*pbVar5 == 0) break;
            uVar4 = (uint)pbVar5[-1];
            if (uVar4 <= *pbVar5) {
              do {
                puVar9[uVar4] = 0;
                uVar4 = uVar4 + 1;
              } while ((int)uVar4 <= (int)(uint)*pbVar5);
            }
            pbVar1 = pbVar5 + 1;
            pbVar5 = pbVar5 + 2;
          } while (*pbVar1 != 0);
        }
        puVar2 = puStack_18 + 1;
        iVar3 = __crtGetStringTypeA(1,puVar9,0x100,puVar2,0,0,0);
        if (iVar3 != 0) {
          *puStack_18 = 0;
          iVar3 = 0;
          puVar6 = puVar8;
          do {
            *puVar6 = (short)iVar3;
            puVar6 = puVar6 + 1;
            iVar3 = iVar3 + 1;
          } while (iVar3 < 0x100);
          puVar6 = puStack_1c + 1;
          iVar3 = FUN_10012bc0(1,puVar8,0x100,puVar6,0,0);
          if (iVar3 != 0) {
            *puStack_1c = 0;
            if ((1 < (int)DAT_1001f21c) && (abStack_e[0] != 0)) {
              pbVar5 = abStack_e + 1;
              do {
                if (*pbVar5 == 0) break;
                uVar4 = (uint)pbVar5[-1];
                if (uVar4 <= *pbVar5) {
                  puVar7 = puStack_18 + uVar4 + 1;
                  do {
                    *puVar7 = 0x8000;
                    uVar4 = uVar4 + 1;
                    puVar7 = puVar7 + 1;
                  } while ((int)uVar4 <= (int)(uint)*pbVar5);
                }
                pbVar1 = pbVar5 + 1;
                pbVar5 = pbVar5 + 2;
              } while (*pbVar1 != 0);
            }
            PTR_DAT_1001f010 = (undefined *)puVar2;
            _DAT_1001f014 = puVar6;
            if (_DAT_100333a0 != (undefined2 *)0x0) {
              free((undefined *)_DAT_100333a0);
            }
            _DAT_100333a0 = puStack_18;
            if (_DAT_100333a4 != (undefined2 *)0x0) {
              free((undefined *)_DAT_100333a4);
            }
            _DAT_100333a4 = puStack_1c;
            free(puVar9);
            free((undefined *)puVar8);
            return 0;
          }
        }
      }
    }
  }
  free((undefined *)puStack_18);
  free((undefined *)puStack_1c);
  free(puVar9);
  free((undefined *)puVar8);
  return 1;
}
#undef abStack_e
#undef puStack_18
#undef puStack_1c
#undef uStack_14

#endif


/* ---- 0x10012bc0  FUN_10012bc0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_10012bc0(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *a5;
  int iVar2;
  undefined *a5_00;
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  a5_00 = (undefined *)0x0;
  if (_DAT_100333f0 == 0) {
    iVar1 = GetStringTypeW(1,IMG_ADDR(0x100154b8),1,(int)&iStack_4);
    if (iVar1 == 0) {
      iVar1 = GetStringTypeA(0,1,IMG_ADDR(0x100154b4),1,(int)&iStack_4);
      if (iVar1 == 0) {
        return 0;
      }
      _DAT_100333f0 = 2;
    }
    else {
      _DAT_100333f0 = 1;
    }
  }
  if (_DAT_100333f0 != 1) {
    iStack_4 = _DAT_100333f0;
    if (_DAT_100333f0 == 2) {
      iStack_4 = 0;
      if (param_5 == 0) {
        param_5 = DAT_10032ff0;
      }
      iVar1 = WideCharToMultiByte(param_5,0x220,param_2,param_3,0,0,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      a5 = calloc(1,iVar1);
      if (a5 == (int *)0x0) {
        return 0;
      }
      iVar2 = WideCharToMultiByte(param_5,0x220,param_2,param_3,(int)a5,iVar1,0,0);
      if ((iVar2 != 0) && (a5_00 = (undefined *)malloc(iVar1 * 2 + 2), a5_00 != (undefined *)0x0)) {
        if (param_6 == 0) {
          param_6 = DAT_10032fe0;
        }
        param_3 = param_3 * 2;
        *(undefined2 *)(a5_00 + param_3) = 0xffff;
        *(undefined2 *)(a5_00 + param_3 + -2) = 0xffff;
        iStack_4 = GetStringTypeA(param_6,param_1,(int)a5,iVar1,(int)a5_00);
        if ((*(short *)(a5_00 + param_3 + -2) == -1) || (*(short *)(a5_00 + param_3) != -1)) {
          iStack_4 = 0;
        }
        else {
          FUN_10011170(param_4,a5_00,param_3);
        }
      }
      free((undefined *)a5);
      free(a5_00);
    }
    return iStack_4;
  }
  iVar1 = GetStringTypeW(param_1,param_2,param_3,param_4);
  return iVar1;
}
#undef iStack_4

#endif


/* ---- 0x10012f40  FUN_10012f40 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_10012f40(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint in_stack_00001008;
  int in_stack_0000100c;
  
  FUN_10014310();
  iVar6 = 0;
  iVar1 = _lseek_lk(in_stack_00001008,0,1);
  if ((iVar1 == -1) || (iVar2 = _lseek_lk(in_stack_00001008,0,2), iVar2 == -1)) {
    return -1;
  }
  uVar7 = in_stack_0000100c - iVar2;
  if ((int)uVar7 < 1) {
    if ((int)uVar7 < 0) {
      _lseek_lk(in_stack_00001008,in_stack_0000100c,0);
      iVar6 = _get_osfhandle(in_stack_00001008);
      iVar6 = SetEndOfFile(iVar6);
      iVar6 = (iVar6 != 0) - 1;
      if (iVar6 == -1) {
        piVar5 = _errno();
        *piVar5 = 0xd;
        iVar2 = GetLastError();
        piVar5 = __doserrno();
        *piVar5 = iVar2;
      }
    }
    _lseek_lk(in_stack_00001008,iVar1,0);
    return iVar6;
  }
  puVar8 = (undefined4 *)REGISTER0X(0x00000010);
  for (iVar2 = 0x400; puVar8 = puVar8 + 1, iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar8 = 0;
  }
  iVar2 = FUN_100142a0(in_stack_00001008,0x8000);
  while( true ) {
    uVar3 = 0x1000;
    if ((int)uVar7 < 0x1000) {
      uVar3 = uVar7;
    }
    iVar4 = _write_lk(in_stack_00001008,&STACK0X(0x00000004),uVar3);
    if (iVar4 == -1) break;
    uVar7 = uVar7 - iVar4;
    if ((int)uVar7 < 1) {
LAB_10012ffa:
      FUN_100142a0(in_stack_00001008,iVar2);
      _lseek_lk(in_stack_00001008,iVar1,0);
      return iVar6;
    }
  }
  piVar5 = __doserrno();
  if (*piVar5 == 5) {
    piVar5 = _errno();
    *piVar5 = 0xd;
  }
  iVar6 = -1;
  goto LAB_10012ffa;
}
#endif


/* ---- 0x10013090  FUN_10013090 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_10013090(uint param_1,char *param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int **ppiVar1;
  char cVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  undefined *puVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  char *pcVar11;
  char *pcVar12;
  #define cStack_9 (*(char *)(_frame + (0x20 - 0x9)))
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int ***)(_frame + (0x20 - 0x4)))
  
  iVar9 = 0;
  if (param_3 != 0) {
    uVar4 = param_1 & 0x1f;
    ppiVar1 = &PTR_100336e0 + ((int)param_1 >> 5);
    iVar8 = uVar4 * 0x24;
    bVar3 = *(byte *)((&PTR_100336e0)[(int)param_1 >> 5] + uVar4 * 9 + 1);
    if ((bVar3 & 2) == 0) {
      pcVar11 = param_2;
      if (((bVar3 & 0x48) != 0) &&
         (cVar2 = *(char *)((int)(&PTR_100336e0)[(int)param_1 >> 5] + iVar8 + 5), cVar2 != '\n')) {
        *param_2 = cVar2;
        param_3 = param_3 + -1;
        pcVar11 = param_2 + 1;
        iVar9 = 1;
        *(undefined1 *)(iVar8 + 5 + (int)*ppiVar1) = 10;
      }
      local_4 = ppiVar1;
      iVar5 = ReadFile((*ppiVar1)[uVar4 * 9],(int)pcVar11,param_3,(int)&local_8,0);
      if (iVar5 != 0) {
        iVar9 = iVar9 + local_8;
        bVar3 = *(byte *)(*ppiVar1 + uVar4 * 9 + 1);
        if ((bVar3 & 0x80) != 0) {
          if ((local_8 == 0) || (*param_2 != '\n')) {
            bVar3 = bVar3 & 0xfb;
          }
          else {
            bVar3 = bVar3 | 4;
          }
          *(byte *)(*ppiVar1 + uVar4 * 9 + 1) = bVar3;
          pcVar10 = param_2 + iVar9;
          pcVar11 = param_2;
          pcVar12 = param_2;
          if (param_2 < pcVar10) {
            while (cVar2 = *pcVar12, cVar2 != '\x1a') {
              if (cVar2 == '\r') {
                if (pcVar12 < pcVar10 + -1) {
                  if (pcVar12[1] == '\n') {
                    pcVar12 = pcVar12 + 2;
                    *pcVar11 = '\n';
                    goto LAB_10013268;
                  }
                  *pcVar11 = '\r';
                  pcVar11 = pcVar11 + 1;
                  pcVar12 = pcVar12 + 1;
                }
                else {
                  iVar5 = 0;
                  pcVar12 = pcVar12 + 1;
                  iVar9 = ReadFile((*local_4)[uVar4 * 9],(int)&cStack_9,1,(int)&local_8,0);
                  if (iVar9 == 0) {
                    iVar5 = GetLastError();
                  }
                  if ((iVar5 == 0) && (local_8 != 0)) {
                    if ((*(byte *)(*local_4 + uVar4 * 9 + 1) & 0x48) == 0) {
                      if ((pcVar11 == param_2) && (cStack_9 == '\n')) {
                        *pcVar11 = '\n';
                        goto LAB_10013268;
                      }
                      _lseek_lk(param_1,0xffffffff,1);
                      if (cStack_9 != '\n') goto LAB_10013265;
                    }
                    else {
                      if (cStack_9 == '\n') {
                        *pcVar11 = '\n';
                        goto LAB_10013268;
                      }
                      *pcVar11 = '\r';
                      pcVar11 = pcVar11 + 1;
                      *(char *)(iVar8 + 5 + (int)*local_4) = cStack_9;
                    }
                  }
                  else {
LAB_10013265:
                    *pcVar11 = '\r';
LAB_10013268:
                    pcVar11 = pcVar11 + 1;
                  }
                }
              }
              else {
                *pcVar11 = cVar2;
                pcVar11 = pcVar11 + 1;
                pcVar12 = pcVar12 + 1;
              }
              if (pcVar10 <= pcVar12) {
                return (int)pcVar11 - (int)param_2;
              }
            }
            bVar3 = *(byte *)(*local_4 + uVar4 * 9 + 1);
            if ((bVar3 & 0x40) == 0) {
              *(byte *)(*local_4 + uVar4 * 9 + 1) = bVar3 | 2;
            }
          }
          iVar9 = (int)pcVar11 - (int)param_2;
        }
        return iVar9;
      }
      puVar6 = (undefined *)GetLastError();
      if (puVar6 == (undefined *)0x5) {
        piVar7 = _errno();
        *piVar7 = 9;
        piVar7 = __doserrno();
        *piVar7 = 5;
        return -1;
      }
      if (puVar6 != (undefined *)0x6d) {
        _dosmaperr(puVar6);
        return -1;
      }
    }
  }
  return 0;
}
#undef cStack_9
#undef local_4
#undef local_8

#endif


/* ---- 0x100132c0  FUN_100132c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_100132c0(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  uVar1 = param_2 + param_1;
  if ((uVar1 < param_1) || (uVar1 < param_2)) {
    uVar2 = 1;
  }
  *param_3 = uVar1;
  return uVar2;
}
#endif


/* ---- 0x100132f0  FUN_100132f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100132f0(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = FUN_100132c0(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = FUN_100132c0(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = FUN_100132c0(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  FUN_100132c0(param_1[2],param_2[2],param_1 + 2);
  return;
}
#endif


/* ---- 0x10013360  FUN_10013360 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10013360(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  *param_1 = uVar1 * 2;
  param_1[1] = uVar2 * 2 | uVar1 >> 0x1f;
  param_1[2] = param_1[2] << 1 | uVar2 >> 0x1f;
  return;
}
#endif


/* ---- 0x10013390  FUN_10013390 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10013390(uint *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  param_1[1] = uVar1 >> 1 | param_1[2] << 0x1f;
  param_1[2] = param_1[2] >> 1;
  *param_1 = *param_1 >> 1 | uVar1 << 0x1f;
  return;
}
#endif


/* ---- 0x100133c0  FUN_100133c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100133c0(char *param_1,int param_2,uint *param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  short sVar3;
  #define uStack_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define uStack_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  puVar2 = param_3;
  sVar3 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  if (param_2 != 0) {
    param_3 = (uint *)param_2;
    do {
      uStack_c = *puVar2;
      uStack_8 = puVar2[1];
      uStack_4 = puVar2[2];
      FUN_10013360(puVar2);
      FUN_10013360(puVar2);
      FUN_100132f0(puVar2,&uStack_c);
      FUN_10013360(puVar2);
      uStack_c = (uint)*param_1;
      uStack_8 = 0;
      uStack_4 = 0;
      FUN_100132f0(puVar2,&uStack_c);
      param_1 = param_1 + 1;
      param_3 = (uint *)((int)param_3 + -1);
    } while (param_3 != (uint *)0x0);
  }
  uVar1 = puVar2[2];
  while (uVar1 == 0) {
    sVar3 = sVar3 + -0x10;
    puVar2[2] = puVar2[1] >> 0x10;
    uVar1 = puVar2[2];
    puVar2[1] = *puVar2 >> 0x10 | puVar2[1] << 0x10;
    *puVar2 = *puVar2 << 0x10;
  }
  uVar1 = puVar2[2];
  while ((uVar1 & 0x8000) == 0) {
    FUN_10013360(puVar2);
    sVar3 = sVar3 + -1;
    uVar1 = puVar2[2];
  }
  *(short *)((int)puVar2 + 10) = sVar3;
  return;
}
#undef uStack_4
#undef uStack_8
#undef uStack_c

#endif


/* ---- 0x100134c0  FUN_100134c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4
FUN_100134c0(ushort *param_1,int *param_2,byte *param_3,undefined4 param_4,int param_5,int param_6,
            int param_7)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  ushort uVar7;
  int iVar8;
  uint uVar9;
  byte bVar10;
  byte *pbVar11;
  byte *pbVar12;
  uint uVar13;
  byte *pbVar14;
  #define iStack_60 (*(int *)(_frame + (0x70 - 0x60)))
  #define pcStack_5c (*(char **)(_frame + (0x70 - 0x5c)))
  #define uStack_54 (*(uint *)(_frame + (0x70 - 0x54)))
  #define pbStack_50 (*(byte **)(_frame + (0x70 - 0x50)))
  #define iStack_4c (*(int *)(_frame + (0x70 - 0x4c)))
  #define iStack_48 (*(int *)(_frame + (0x70 - 0x48)))
  #define uStack_30 (*(undefined4 *)(_frame + (0x70 - 0x30)))
  #define uStack_2c (*(ushort *)(_frame + (0x70 - 0x2c)))
  #define uStack_2a (*(undefined2 *)(_frame + (0x70 - 0x2a)))
  #define uStack_28 (*(undefined2 *)(_frame + (0x70 - 0x28)))
  #define pbStack_26 (*(byte **)(_frame + (0x70 - 0x26)))
  #define uStack_22 (*(ushort *)(_frame + (0x70 - 0x22)))
  #define acStack_1c (*(char (*)[23])(_frame + (0x70 - 0x1c)))
  #define cStack_5 (*(char *)(_frame + (0x70 - 0x5)))
  
  pcStack_5c = acStack_1c;
  iVar8 = 0;
  uVar13 = 0;
  uVar7 = 0;
  iStack_4c = 1;
  uStack_54 = 0;
  bVar2 = false;
  bVar4 = false;
  bVar3 = false;
  bVar5 = false;
  bVar6 = false;
  iStack_48 = 0;
  iStack_60 = 0;
  uStack_30 = 0;
  pbStack_50 = param_3;
  for (pbVar11 = param_3;
      (((bVar10 = *pbVar11, bVar10 == 0x20 || (bVar10 == 9)) || (bVar10 == 10)) ||
      (pbVar14 = param_3, bVar10 == 0xd)); pbVar11 = pbVar11 + 1) {
  }
  do {
    bVar10 = *pbVar11;
    pbVar12 = pbVar11 + 1;
    param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
    switch(iVar8) {
    case 0:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto code_r0x10013992;
      }
      if (bVar10 == DAT_1001f220) {
        iVar8 = 5;
      }
      else if (bVar10 == 0x2b) {
        iVar8 = 2;
        uVar7 = 0;
      }
      else if (bVar10 == 0x2d) {
        iVar8 = 2;
        uVar7 = 0x8000;
      }
      else {
        if (bVar10 != 0x30) goto code_r0x1001398d;
        iVar8 = 1;
      }
      break;
    case 1:
      bVar2 = true;
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto code_r0x10013992;
      }
      if (bVar10 == DAT_1001f220) {
        iVar8 = 4;
      }
      else {
        switch(bVar10) {
        case 0x2b:
        case 0x2d:
          goto code_r0x10013793;
        default:
          goto code_r0x1001398d;
        case 0x30:
code_r0x10013634:
          iVar8 = 1;
          break;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto code_r0x10013789;
        }
      }
      break;
    case 2:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto code_r0x10013992;
      }
      if (bVar10 == DAT_1001f220) {
        iVar8 = 5;
      }
      else {
        if (bVar10 == 0x30) goto code_r0x10013634;
        iVar8 = 10;
        pbVar12 = pbVar14;
      }
      break;
    case 3:
      while( true ) {
        bVar2 = true;
        if (DAT_1001f21c < 2) {
          uVar9 = (byte)PTR_DAT_1001f010[((uint)param_3 & 0xff) * 2] & 4;
        }
        else {
          uVar9 = _isctype((uint)param_3 & 0xff,4);
        }
        if (uVar9 == 0) break;
        if (uVar13 < 0x19) {
          uVar13 = uVar13 + 1;
          *pcStack_5c = bVar10 - 0x30;
          bVar10 = *pbVar12;
          pcStack_5c = pcStack_5c + 1;
          param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
          pbVar12 = pbVar12 + 1;
        }
        else {
          bVar10 = *pbVar12;
          iStack_60 = iStack_60 + 1;
          param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
          pbVar12 = pbVar12 + 1;
        }
      }
      uStack_54 = uVar13;
      if (bVar10 != DAT_1001f220) {
        switch(bVar10) {
        case 0x2b:
        case 0x2d:
          goto code_r0x10013793;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto code_r0x10013789;
        }
code_r0x1001398d:
        iVar8 = 10;
        goto code_r0x10013992;
      }
      iVar8 = 4;
      break;
    case 4:
      bVar4 = true;
      if (uVar13 == 0) {
        while (bVar10 == 0x30) {
          bVar10 = *pbVar12;
          iStack_60 = iStack_60 + -1;
          pbVar12 = pbVar12 + 1;
          PIECE(param_3,1,3) = (undefined3)((uint)param_3 >> 8);
          param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
        }
      }
      while( true ) {
        bVar2 = true;
        if (DAT_1001f21c < 2) {
          uVar9 = (byte)PTR_DAT_1001f010[((uint)param_3 & 0xff) * 2] & 4;
        }
        else {
          uVar9 = _isctype((uint)param_3 & 0xff,4);
        }
        if (uVar9 == 0) break;
        if (uVar13 < 0x19) {
          uVar13 = uVar13 + 1;
          *pcStack_5c = bVar10 - 0x30;
          pcStack_5c = pcStack_5c + 1;
          iStack_60 = iStack_60 + -1;
        }
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
      }
      uStack_54 = uVar13;
      switch(bVar10) {
      case 0x2b:
      case 0x2d:
code_r0x10013793:
        bVar2 = true;
        pbVar12 = pbVar12 + -1;
        iVar8 = 0xb;
        break;
      default:
        goto code_r0x1001398d;
      case 0x44:
      case 0x45:
      case 100:
      case 0x65:
code_r0x10013789:
        bVar2 = true;
        iVar8 = 6;
      }
      break;
    case 5:
      bVar4 = true;
      if (DAT_1001f21c < 2) {
        uVar9 = (byte)PTR_DAT_1001f010[(uint)bVar10 * 2] & 4;
      }
      else {
        uVar9 = _isctype((uint)bVar10,4);
      }
      if (uVar9 == 0) {
        iVar8 = 10;
        pbVar12 = pbVar14;
      }
      else {
        iVar8 = 4;
        pbVar12 = pbVar11;
      }
      break;
    case 6:
      pbVar11 = pbVar11 + -1;
      pbVar14 = pbVar11;
      pbStack_50 = pbVar11;
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 9;
        goto code_r0x10013992;
      }
      if (bVar10 == 0x2b) {
code_r0x10013986:
        iVar8 = 7;
        pbVar14 = pbVar11;
        pbStack_50 = pbVar11;
      }
      else {
        if (bVar10 != 0x2d) goto code_r0x10013876;
code_r0x10013977:
        iVar8 = 7;
        iStack_4c = -1;
        pbVar14 = pbVar11;
        pbStack_50 = pbVar11;
      }
      break;
    case 7:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 9;
        goto code_r0x10013992;
      }
code_r0x10013876:
      if (bVar10 == 0x30) {
        iVar8 = 8;
      }
      else {
        iVar8 = 10;
        pbVar12 = pbVar14;
      }
      break;
    case 8:
      bVar3 = true;
      while (bVar10 == 0x30) {
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
      }
      if (((char)bVar10 < '1') || ('9' < (char)bVar10)) goto code_r0x1001398d;
      iVar8 = 9;
code_r0x10013992:
      pbVar12 = pbVar12 + -1;
      break;
    case 9:
      bVar3 = true;
      iStack_48 = 0;
      while( true ) {
        if (DAT_1001f21c < 2) {
          uVar13 = (byte)PTR_DAT_1001f010[((uint)param_3 & 0xff) * 2] & 4;
        }
        else {
          uVar13 = _isctype((uint)param_3 & 0xff,4);
        }
        if (uVar13 == 0) goto code_r0x100138fa;
        iStack_48 = (char)bVar10 + -0x30 + iStack_48 * 10;
        if (0x1450 < iStack_48) break;
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
      }
      iStack_48 = 0x1451;
code_r0x100138fa:
      while( true ) {
        if (DAT_1001f21c < 2) {
          uVar13 = (byte)PTR_DAT_1001f010[((uint)param_3 & 0xff) * 2] & 4;
        }
        else {
          uVar13 = _isctype((uint)param_3 & 0xff,4);
        }
        if (uVar13 == 0) break;
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
      }
      iVar8 = 10;
      pbVar12 = pbVar12 + -1;
      uVar13 = uStack_54;
      pbVar14 = pbStack_50;
      break;
    case 0xb:
      if (param_7 == 0) goto code_r0x1001398d;
      if (bVar10 == 0x2b) goto code_r0x10013986;
      if (bVar10 == 0x2d) goto code_r0x10013977;
      iVar8 = 10;
      pbVar12 = pbVar11;
      pbVar14 = pbVar11;
      pbStack_50 = pbVar11;
    }
    pbVar11 = pbVar12;
  } while (iVar8 != 10);
  *param_2 = (int)pbVar12;
  if (bVar2) {
    if (0x18 < uVar13) {
      if ('\x04' < cStack_5) {
        cStack_5 = cStack_5 + '\x01';
      }
      pcStack_5c = pcStack_5c + -1;
      iStack_60 = iStack_60 + 1;
      uVar13 = 0x18;
    }
    if (uVar13 == 0) {
      uStack_2c = 0;
      uStack_22 = 0;
      param_3 = (byte *)0x0;
      pbVar11 = (byte *)0x0;
      goto LAB_10013a64;
    }
    cVar1 = pcStack_5c[-1];
    while (cVar1 == '\0') {
      uVar13 = uVar13 - 1;
      iStack_60 = iStack_60 + 1;
      cVar1 = pcStack_5c[-2];
      pcStack_5c = pcStack_5c + -1;
    }
    FUN_100133c0(acStack_1c,uVar13,&uStack_2c);
    if (iStack_4c < 0) {
      iStack_48 = -iStack_48;
    }
    iStack_48 = iStack_48 + iStack_60;
    if (!bVar3) {
      iStack_48 = iStack_48 + param_5;
    }
    if (!bVar4) {
      iStack_48 = iStack_48 - param_6;
    }
    if (iStack_48 < 0x1451) {
      if (-0x1451 < iStack_48) {
        FUN_10014600(&uStack_2c,iStack_48,param_4);
        pbVar11 = (byte *)CONCAT22(uStack_28,uStack_2a);
        param_3 = pbStack_26;
        goto LAB_10013a64;
      }
      bVar6 = true;
    }
    else {
      bVar5 = true;
    }
  }
  uStack_2c = (ushort)param_3;
  pbVar11 = param_3;
  uStack_22 = uStack_2c;
LAB_10013a64:
  if (bVar2) {
    if (bVar5) {
      pbVar11 = (byte *)0x0;
      uStack_22 = 0x7fff;
      param_3 = (byte *)0x80000000;
      uStack_2c = 0;
      uStack_30 = 2;
    }
    else if (bVar6) {
      uStack_2c = 0;
      uStack_22 = 0;
      param_3 = (byte *)0x0;
      pbVar11 = (byte *)0x0;
      uStack_30 = 1;
    }
  }
  else {
    uStack_2c = 0;
    uStack_22 = 0;
    param_3 = (byte *)0x0;
    pbVar11 = (byte *)0x0;
    uStack_30 = 4;
  }
  *param_1 = uStack_2c;
  *(byte **)(param_1 + 1) = pbVar11;
  *(byte **)(param_1 + 3) = param_3;
  param_1[5] = uStack_22 | uVar7;
  return uStack_30;
}
#undef acStack_1c
#undef cStack_5
#undef iStack_48
#undef iStack_4c
#undef iStack_60
#undef pbStack_26
#undef pbStack_50
#undef pcStack_5c
#undef uStack_22
#undef uStack_28
#undef uStack_2a
#undef uStack_2c
#undef uStack_30
#undef uStack_54

#endif


/* ---- 0x10013c50  FUN_10013c50 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4
FUN_10013c50(int param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  short *psVar1;
  ushort uVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  short *psVar6;
  short *psVar7;
  int iVar8;
  short sVar9;
  int iVar10;
  #define uStack_1c (*(undefined1 *)(_frame + (0x30 - 0x1c)))
  #define uStack_1b (*(undefined1 *)(_frame + (0x30 - 0x1b)))
  #define uStack_1a (*(undefined1 *)(_frame + (0x30 - 0x1a)))
  #define uStack_19 (*(undefined1 *)(_frame + (0x30 - 0x19)))
  #define uStack_18 (*(undefined1 *)(_frame + (0x30 - 0x18)))
  #define uStack_17 (*(undefined1 *)(_frame + (0x30 - 0x17)))
  #define uStack_16 (*(undefined1 *)(_frame + (0x30 - 0x16)))
  #define uStack_15 (*(undefined1 *)(_frame + (0x30 - 0x15)))
  #define uStack_14 (*(undefined1 *)(_frame + (0x30 - 0x14)))
  #define uStack_13 (*(undefined1 *)(_frame + (0x30 - 0x13)))
  #define uStack_12 (*(undefined1 *)(_frame + (0x30 - 0x12)))
  #define uStack_11 (*(undefined1 *)(_frame + (0x30 - 0x11)))
  #define uStack_10 (*(undefined2 *)(_frame + (0x30 - 0x10)))
  #define uStack_e (*(undefined2 *)(_frame + (0x30 - 0xe)))
  #define uStack_c (*(undefined2 *)(_frame + (0x30 - 0xc)))
  #define uStack_a (*(undefined2 *)(_frame + (0x30 - 0xa)))
  #define uStack_8 (*(undefined2 *)(_frame + (0x30 - 0x8)))
  #define uStack_6 (*(undefined1 *)(_frame + (0x30 - 0x6)))
  #define cStack_5 (*(char *)(_frame + (0x30 - 0x5)))
  
  psVar1 = param_6;
  uStack_1c = 0xcc;
  uStack_1b = 0xcc;
  uStack_1a = 0xcc;
  uStack_19 = 0xcc;
  uStack_18 = 0xcc;
  uStack_17 = 0xcc;
  uStack_16 = 0xcc;
  uStack_15 = 0xcc;
  uStack_14 = 0xcc;
  uStack_13 = 0xcc;
  uVar4 = param_3 & 0x7fff;
  uStack_12 = 0xfb;
  uStack_11 = 0x3f;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((short)uVar4 == 0) && (param_2 == 0)) && (param_1 == 0)) {
    *param_6 = 0;
LAB_10013e5f:
    *(undefined1 *)(psVar1 + 1) = 0x20;
    *(undefined1 *)((int)psVar1 + 3) = 1;
    *(undefined1 *)(psVar1 + 2) = 0x30;
    *(undefined1 *)((int)psVar1 + 5) = 0;
    return 1;
  }
  if ((short)uVar4 == 0x7fff) {
    *param_6 = 1;
    if (((param_2 != 0x80000000) || (param_1 != 0)) && ((param_2 & 0x40000000) == 0)) {
      param_6[2] = 0x2331;
      param_6[3] = 0x4e53;
      param_6[4] = 0x4e41;
      *(undefined1 *)((int)param_6 + 3) = 6;
      *(undefined1 *)(param_6 + 5) = 0;
      return 0;
    }
    if ((((param_3 & 0x8000) != 0) && (param_2 == 0xc0000000)) && (param_1 == 0)) {
      param_6[2] = 0x2331;
      param_6[3] = 0x4e49;
      *(undefined1 *)((int)param_6 + 3) = 5;
      param_6[4] = 0x44;
      return 0;
    }
    if ((param_2 == 0x80000000) && (param_1 == 0)) {
      param_6[2] = 0x2331;
      param_6[3] = 0x4e49;
      *(undefined1 *)((int)param_6 + 3) = 5;
      param_6[4] = 0x46;
      return 0;
    }
    param_6[2] = 0x2331;
    param_6[3] = 0x4e51;
    param_6[4] = 0x4e41;
    *(undefined1 *)((int)param_6 + 3) = 6;
    *(undefined1 *)(param_6 + 5) = 0;
    return 0;
  }
  uStack_6 = (undefined1)uVar4;
  cStack_5 = (char)(uVar4 >> 8);
  uStack_a = (undefined2)param_2;
  uStack_8 = (undefined2)(param_2 >> 0x10);
  uStack_e = (undefined2)param_1;
  uStack_c = (undefined2)((uint)param_1 >> 0x10);
  uStack_10 = 0;
  sVar9 = (short)(((uVar4 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar4 * 0x4d10 >>
                 0x10);
  FUN_10014600(&uStack_10,-(int)sVar9,1);
  if (0x3ffe < CONCAT11(cStack_5,uStack_6)) {
    sVar9 = sVar9 + 1;
    FUN_10014340(&uStack_10,&uStack_1c);
  }
  *psVar1 = sVar9;
  iVar8 = param_4;
  if (((param_5 & 1) != 0) && (iVar8 = param_4 + sVar9, param_4 + sVar9 < 1)) {
    *psVar1 = 0;
    goto LAB_10013e5f;
  }
  if (0x15 < iVar8) {
    iVar8 = 0x15;
  }
  uVar2 = CONCAT11(cStack_5,uStack_6);
  uStack_6 = 0;
  cStack_5 = '\0';
  iVar5 = 8;
  iVar10 = uVar2 - 0x3ffe;
  do {
    FUN_10013360(&uStack_10);
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  if (iVar10 < 0) {
    for (uVar4 = -iVar10 & 0xff; uVar4 != 0; uVar4 = uVar4 - 1) {
      FUN_10013390(&uStack_10);
    }
  }
  psVar1 = psVar1 + 2;
  iVar8 = iVar8 + 1;
  psVar6 = psVar1;
  if (0 < iVar8) {
    do {
      param_1 = CONCAT22(uStack_e,uStack_10);
      param_2 = CONCAT22(uStack_a,uStack_c);
      param_3 = CONCAT13(cStack_5,CONCAT12(uStack_6,uStack_8));
      FUN_10013360(&uStack_10);
      FUN_10013360(&uStack_10);
      FUN_100132f0(&uStack_10,&param_1);
      FUN_10013360(&uStack_10);
      cVar3 = cStack_5 + '0';
      cStack_5 = '\0';
      *(char *)psVar6 = cVar3;
      psVar6 = (short *)((int)psVar6 + 1);
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  psVar7 = psVar6 + -1;
  if (*(char *)((int)psVar6 + -1) < '5') {
    if (psVar1 <= psVar7) {
      do {
        if ((char)*psVar7 != '0') break;
        psVar7 = (short *)((int)psVar7 + -1);
      } while (psVar1 <= psVar7);
      if (psVar1 <= psVar7) goto LAB_10013fb6;
    }
    *(undefined1 *)psVar1 = 0x30;
    *param_6 = 0;
    *(undefined1 *)(param_6 + 1) = 0x20;
    *(undefined1 *)((int)param_6 + 3) = 1;
    *(undefined1 *)((int)param_6 + 5) = 0;
    return 1;
  }
  if (psVar1 <= psVar7) {
    do {
      if ((char)*psVar7 != '9') break;
      *(undefined1 *)psVar7 = 0x30;
      psVar7 = (short *)((int)psVar7 + -1);
    } while (psVar1 <= psVar7);
    if (psVar1 <= psVar7) {
      *(char *)psVar7 = (char)*psVar7 + '\x01';
      goto LAB_10013fb6;
    }
  }
  psVar7 = (short *)((int)psVar7 + 1);
  *param_6 = *param_6 + 1;
  *(char *)psVar7 = *(char *)psVar7 + '\x01';
LAB_10013fb6:
  cVar3 = ((char)psVar7 - (char)param_6) + -3;
  *(char *)((int)param_6 + 3) = cVar3;
  *(undefined1 *)((int)param_6 + cVar3 + 4) = 0;
  return 1;
}
#undef cStack_5
#undef uStack_10
#undef uStack_11
#undef uStack_12
#undef uStack_13
#undef uStack_14
#undef uStack_15
#undef uStack_16
#undef uStack_17
#undef uStack_18
#undef uStack_19
#undef uStack_1a
#undef uStack_1b
#undef uStack_1c
#undef uStack_6
#undef uStack_8
#undef uStack_a
#undef uStack_c
#undef uStack_e

#endif


/* ---- 0x10013fe0  FUN_10013fe0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10013fe0(int param_1,undefined4 param_2,undefined4 param_3,char *param_4)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  byte *pbVar7;
  #define auStack_80 (*(uint (*)[32])(_frame + (0x90 - 0x80)))
  
  if (param_1 != 1) {
    if (param_1 != 0) {
      return 0xffffffff;
    }
    iVar4 = ((code *)FUN_10014690)(param_2,param_3,IMG_ADDR(0x10033430),4,0);
    if (iVar4 != 0) {
      pbVar7 = (byte *)IMG_ADDR(0x10033430);
      *param_4 = '\0';
      while( true ) {
        bVar1 = *pbVar7;
        if (DAT_1001f21c < 2) {
          uVar3 = (byte)PTR_DAT_1001f010[(uint)bVar1 * 2] & 4;
        }
        else {
          uVar3 = _isctype((uint)bVar1,4);
        }
        if (uVar3 == 0) break;
        pbVar7 = pbVar7 + 2;
        *param_4 = *param_4 * '\n' + bVar1 + -0x30;
        if (IMG_ADDR(0x10033437) < (int)pbVar7) {
          return 0;
        }
      }
      return 0;
    }
    return 0xffffffff;
  }
  puVar5 = auStack_80;
  bVar2 = false;
  uVar3 = ((code *)FUN_100147c0)(param_2,param_3,auStack_80,0x80,0);
  if (uVar3 == 0) {
    iVar4 = GetLastError();
    if (((iVar4 != 0x7a) || (uVar3 = ((code *)FUN_100147c0)(param_2,param_3,0,0,0), uVar3 == 0)) ||
       (puVar5 = (uint *)malloc(uVar3), puVar5 == (uint *)0x0)) goto LAB_10014090;
    bVar2 = true;
    uVar3 = ((code *)FUN_100147c0)(param_2,param_3,puVar5,uVar3,0);
    if (uVar3 == 0) goto LAB_10014090;
  }
  puVar6 = (uint *)malloc(uVar3);
  *(uint **)param_4 = puVar6;
  if (puVar6 != (uint *)0x0) {
    Im_MemCopy(puVar6,puVar5,uVar3);
    if (!bVar2) {
      return 0;
    }
    free((undefined *)puVar5);
    return 0;
  }
LAB_10014090:
  if (!bVar2) {
    return 0xffffffff;
  }
  free((undefined *)puVar5);
  return 0xffffffff;
}
#undef auStack_80

#endif


/* ---- 0x100142a0  FUN_100142a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_100142a0(uint param_1,int param_2)

{
  byte bVar1;
  int *piVar2;
  byte bVar3;
  
  bVar1 = *(byte *)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1);
  if (param_2 == 0x8000) {
    bVar3 = bVar1 & 0x7f;
  }
  else {
    if (param_2 != 0x4000) {
      piVar2 = _errno();
      *piVar2 = 0x16;
      return -1;
    }
    bVar3 = bVar1 | 0x80;
  }
  *(byte *)((&PTR_100336e0)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) = bVar3;
  return (-(uint)((bVar1 & 0x80) != 0) & 0xffffc000) + 0x8000;
}
#endif


/* ---- 0x10014310  FUN_10014310 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Unable to track spacebase fully for stack */

void FUN_10014310(void)

{
  uint in_EAX;
  undefined1 *puVar1;
  undefined4 unaff_retaddr;
  
  puVar1 = &STACK0X(0x00000004);
  for (; 0xfff < in_EAX; in_EAX = in_EAX - 0x1000) {
    puVar1 = puVar1 + -0x1000;
  }
  *(undefined4 *)(puVar1 + (-4 - in_EAX)) = unaff_retaddr;
  return;
}
#endif


/* ---- 0x10014340  FUN_10014340 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10014340(int *param_1,int *param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  ushort uVar6;
  ushort *puVar7;
  ushort *puVar8;
  #define psStack_20 (*(short **)(_frame + (0x30 - 0x20)))
  #define iStack_18 (*(int *)(_frame + (0x30 - 0x18)))
  #define iStack_14 (*(int *)(_frame + (0x30 - 0x14)))
  #define iStack_10 (*(int *)(_frame + (0x30 - 0x10)))
  #define bStack_c (*(byte *)(_frame + (0x30 - 0xc)))
  #define uStack_b (*(undefined1 *)(_frame + (0x30 - 0xb)))
  #define uStack_a (*(undefined2 *)(_frame + (0x30 - 0xa)))
  #define sStack_8 (*(short *)(_frame + (0x30 - 0x8)))
  #define uStack_6 (*(undefined2 *)(_frame + (0x30 - 0x6)))
  #define uStack_4 (*(undefined2 *)(_frame + (0x30 - 0x4)))
  #define uStack_2 (*(ushort *)(_frame + (0x30 - 0x2)))
  
  iStack_14 = 0;
  bStack_c = 0;
  uStack_b = 0;
  uStack_a = 0;
  sStack_8 = 0;
  uStack_6 = 0;
  uVar3 = *(ushort *)((int)param_2 + 10) & 0x7fff;
  uVar1 = *(ushort *)((int)param_1 + 10) & 0x7fff;
  uVar6 = (*(ushort *)((int)param_2 + 10) ^ *(ushort *)((int)param_1 + 10)) & 0x8000;
  uVar4 = uVar3 + uVar1;
  uStack_4 = 0;
  uStack_2 = 0;
  if (((0x7ffe < uVar1) || (0x7ffe < uVar3)) || (0xbffd < uVar4)) {
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar6 != 0) & 0x80000000) + 0x7fff8000;
    return;
  }
  if (uVar4 < 0x3fc0) {
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  if (((uVar1 == 0) && (uVar4 = uVar4 + 1, (param_1[2] & 0x7fffffffU) == 0)) &&
     ((param_1[1] == 0 && (*param_1 == 0)))) {
    *(undefined2 *)((int)param_1 + 10) = 0;
    return;
  }
  if (((uVar3 == 0) && (uVar4 = uVar4 + 1, (param_2[2] & 0x7fffffffU) == 0)) &&
     ((param_2[1] == 0 && (*param_2 == 0)))) {
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  psStack_20 = &sStack_8;
  iStack_18 = 0;
  iVar5 = 5;
  do {
    if (0 < iVar5) {
      puVar8 = (ushort *)(param_2 + 2);
      puVar7 = (ushort *)(iStack_18 * 2 + (int)param_1);
      iStack_10 = iVar5;
      do {
        iVar2 = FUN_100132c0(*(undefined4 *)(psStack_20 + -2),(uint)*puVar8 * (uint)*puVar7,
                             psStack_20 + -2);
        if (iVar2 != 0) {
          *psStack_20 = *psStack_20 + 1;
        }
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + -1;
        iStack_10 = iStack_10 + -1;
      } while (iStack_10 != 0);
    }
    psStack_20 = psStack_20 + 1;
    iStack_18 = iStack_18 + 1;
    iVar5 = iVar5 + -1;
  } while (0 < iVar5);
  uVar4 = uVar4 + 0xc002;
  while ((0 < (short)uVar4 && ((uStack_2 & 0x8000) == 0))) {
    FUN_10013360(&bStack_c);
    uVar4 = uVar4 - 1;
  }
  if ((short)uVar4 < 1) {
    uVar4 = uVar4 - 1;
    if ((short)uVar4 < 0) {
      iVar5 = -(int)(short)uVar4;
      uVar4 = uVar4 + (short)iVar5;
      do {
        if ((bStack_c & 1) != 0) {
          iStack_14 = iStack_14 + 1;
        }
        FUN_10013390(&bStack_c);
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if (iStack_14 != 0) {
      bStack_c = bStack_c | 1;
    }
  }
  if ((0x8000 < CONCAT11(uStack_b,bStack_c)) ||
     (iVar2 = CONCAT22(uStack_4,uStack_6), iVar5 = CONCAT22(sStack_8,uStack_a),
     (CONCAT22(uStack_a,CONCAT11(uStack_b,bStack_c)) & 0x1ffff) == 0x18000)) {
    if (CONCAT22(sStack_8,uStack_a) == -1) {
      iVar5 = 0;
      if (CONCAT22(uStack_4,uStack_6) == -1) {
        if (uStack_2 == 0xffff) {
          uStack_2 = 0x8000;
          uVar4 = uVar4 + 1;
          iVar2 = 0;
          iVar5 = 0;
        }
        else {
          uStack_2 = uStack_2 + 1;
          iVar2 = 0;
          iVar5 = 0;
        }
      }
      else {
        iVar2 = CONCAT22(uStack_4,uStack_6) + 1;
      }
    }
    else {
      iVar5 = CONCAT22(sStack_8,uStack_a) + 1;
      iVar2 = CONCAT22(uStack_4,uStack_6);
    }
  }
  sStack_8 = (short)((uint)iVar5 >> 0x10);
  uStack_a = (undefined2)iVar5;
  uStack_4 = (undefined2)((uint)iVar2 >> 0x10);
  uStack_6 = (undefined2)iVar2;
  if (0x7ffe < uVar4) {
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar6 != 0) & 0x80000000) + 0x7fff8000;
    return;
  }
  *(undefined2 *)param_1 = uStack_a;
  *(uint *)((int)param_1 + 2) = CONCAT22(uStack_6,sStack_8);
  *(uint *)((int)param_1 + 6) = CONCAT22(uStack_2,uStack_4);
  *(ushort *)((int)param_1 + 10) = uVar4 | uVar6;
  return;
}
#undef bStack_c
#undef iStack_10
#undef iStack_14
#undef iStack_18
#undef psStack_20
#undef sStack_8
#undef uStack_2
#undef uStack_4
#undef uStack_6
#undef uStack_a
#undef uStack_b

#endif


/* ---- 0x10014600  FUN_10014600 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10014600(undefined2 *param_1,uint param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  #define uStack_c (*(undefined2 *)(_frame + (0x20 - 0xc)))
  #define uStack_a (*(undefined4 *)(_frame + (0x20 - 0xa)))
  #define uStack_6 (*(undefined2 *)(_frame + (0x20 - 0x6)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  iVar3 = IMG_ADDR(0x10021da8);
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      iVar3 = IMG_ADDR(0x10021f08);
    }
    if (param_3 == 0) {
      *param_1 = 0;
    }
    while (param_2 != 0) {
      iVar3 = iVar3 + 0x54;
      uVar1 = param_2 & 7;
      param_2 = (int)param_2 >> 3;
      if (uVar1 != 0) {
        puVar2 = (undefined4 *)(iVar3 + uVar1 * 0xc);
        if (0x7fff < *(ushort *)(iVar3 + uVar1 * 0xc)) {
          uStack_c = (undefined2)*puVar2;
          PIECE(uStack_a,0,2) = (undefined2)((uint)*puVar2 >> 0x10);
          PIECE(uStack_a,2,2) = (undefined2)puVar2[1];
          uStack_6 = (undefined2)((uint)puVar2[1] >> 0x10);
          uStack_4 = puVar2[2];
          uStack_a = CONCAT22(PIECE(uStack_a,2,2),(undefined2)uStack_a) + -1;
          puVar2 = (undefined4 *)&uStack_c;
        }
        FUN_10014340(param_1,puVar2);
      }
    }
  }
  return;
}
#undef uStack_4
#undef uStack_6
#undef uStack_a
#undef uStack_c

#endif


/* ---- 0x10014690  FUN_10014690 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_10014690(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined *a3;
  int iVar3;
  int unaff_ESI;
  int unaff_EDI;
  
  if (_DAT_100334fc == 0) {
    iVar1 = GetLocaleInfoW(0,1,0,0);
    if (iVar1 == 0) {
      iVar1 = GetLocaleInfoA(0,1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      _DAT_100334fc = 2;
    }
    else {
      _DAT_100334fc = 1;
    }
  }
  if (_DAT_100334fc == 1) {
    iVar1 = GetLocaleInfoW(param_1,param_2,param_3,param_4);
    return iVar1;
  }
  if (_DAT_100334fc != 2) {
    return _DAT_100334fc;
  }
  iVar1 = 0;
  uVar2 = GetLocaleInfoA(param_1,param_2,0);
  if (uVar2 != 0) {
    a3 = (undefined *)malloc(uVar2);
    if (a3 == (undefined *)0x0) {
      return 0;
    }
    iVar3 = GetLocaleInfoA(param_1,param_2,a3,uVar2);
    if (iVar3 != 0) {
      if (unaff_EDI == 0) {
        iVar1 = MultiByteToWideChar(unaff_ESI,1,(int)a3,-1,0,0);
        if (iVar1 != 0) {
          free(a3);
          return iVar1;
        }
      }
      else {
        iVar1 = MultiByteToWideChar(unaff_ESI,1,(int)a3,-1,iVar1,unaff_EDI);
        if (iVar1 != 0) {
          free(a3);
          return iVar1;
        }
      }
    }
    free(a3);
    return 0;
  }
  return 0;
}
#endif


/* ---- 0x100147c0  FUN_100147c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_100147c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined *a3;
  int unaff_ESI;
  int unaff_EDI;
  int a5;
  
  if (_DAT_10033500 == 0) {
    iVar1 = GetLocaleInfoW(0,1,0,0);
    if (iVar1 == 0) {
      iVar1 = GetLocaleInfoA(0,1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      _DAT_10033500 = 2;
    }
    else {
      _DAT_10033500 = 1;
    }
  }
  if (_DAT_10033500 == 2) {
    iVar1 = GetLocaleInfoA(param_1,param_2,param_3,param_4);
    return iVar1;
  }
  if (_DAT_10033500 != 1) {
    return _DAT_10033500;
  }
  a5 = 0;
  iVar1 = GetLocaleInfoW(param_1,param_2,0);
  if (iVar1 != 0) {
    a3 = (undefined *)malloc(iVar1 * 2);
    if (a3 == (undefined *)0x0) {
      return 0;
    }
    iVar1 = GetLocaleInfoW(param_1,param_2,a3,iVar1);
    if (iVar1 != 0) {
      if (unaff_EDI == 0) {
        iVar1 = WideCharToMultiByte(unaff_ESI,0x220,(int)a3,-1,0,0,0,0);
        if (iVar1 != 0) {
          free(a3);
          return iVar1;
        }
      }
      else {
        iVar1 = WideCharToMultiByte(unaff_ESI,0x220,(int)a3,-1,a5,unaff_EDI,0,0);
        if (iVar1 != 0) {
          free(a3);
          return iVar1;
        }
      }
    }
    free(a3);
    return 0;
  }
  return 0;
}
#endif

