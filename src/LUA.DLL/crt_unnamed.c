/* LUA.DLL :: crt_unnamed.c
 * functions 0x1000f070 .. 0x1002205b (155 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000f070  FUN_1000f070 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1000f070(undefined4 param_1,undefined *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x1000f075. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)UNRECOVERED_JUMPTABLE)();
  return;
}
#endif


/* ---- 0x1000f0e0  FUN_1000f0e0 ---- */
undefined4 __cdecl FUN_1000f0e0(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  int *in_EAX;
  undefined4 uVar1;
  
  uVar1 = __InternalCxxFrameHandler(param_1,param_2,param_3,param_4,in_EAX,0,0,'\0');
  return uVar1;
}

/* ---- 0x1000f120  FUN_1000f120 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_1000f120(int param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int *unaff_FS_OFFSET = (int *)TEB_BASE();
  #define local_18 (*(int *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(code **)(_frame + (0x30 - 0x14)))
  #define local_10 (*(undefined4 *)(_frame + (0x30 - 0x10)))
  #define local_c (*(int *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x30 - 0x8)))
  
  local_8 = param_4 + 1;
  local_14 = __CxxFrameHandler;
  local_10 = param_2;
  local_c = param_1;
  local_18 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&local_18;
  uVar1 = FUN_10013ef0(param_3,param_1,param_5);
  *unaff_FS_OFFSET = local_18;
  return uVar1;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_8
#undef local_c

#endif


/* ---- 0x1000f1b0  FUN_1000f1b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl
FUN_1000f1b0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[96] __attribute__((aligned(16)));  /* the original frame below the return address */
  int *piVar1;
  int *unaff_FS_OFFSET = (int *)TEB_BASE();
  undefined4 uVar2;
  undefined4 **ppuVar3;
  #define local_34 (*(undefined4 **)(_frame + (0x50 - 0x34)))
  #define local_30 (*(undefined4 *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(undefined4 **)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(code **)(_frame + (0x50 - 0x28)))
  #define local_24 (*(undefined4 *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(undefined4 *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(undefined4 *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(undefined4 *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(undefined4 *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(undefined1 **)(_frame + (0x50 - 0x10)))
  #define local_c (*(undefined1 **)(_frame + (0x50 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x50 - 0x8)))
  
  local_c = (_stkneg + 92);
  local_10 = (_stkneg + 28);
  local_28 = FUN_1000f280;
  local_24 = param_5;
  local_20 = param_2;
  local_1c = param_6;
  local_18 = param_7;
  local_8 = 0;
  local_14 = 0x1000f24c;
  local_2c = (undefined4 *)*unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&local_2c;
  local_34 = param_1;
  local_30 = param_3;
  ppuVar3 = &local_34;
  uVar2 = *param_1;
  piVar1 = _getptd();
  (*(code *)piVar1[0x1a])(uVar2,ppuVar3);
  if (local_8 == 0) {
    *unaff_FS_OFFSET = (int)local_2c;
  }
  else {
    *local_2c = *(undefined4 *)*unaff_FS_OFFSET;
    *unaff_FS_OFFSET = (int)local_2c;
  }
  return 0;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_8
#undef local_c

#endif


/* ---- 0x1000f280  FUN_1000f280 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_1000f280(int *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((param_1[1] & 0x66U) != 0) {
    *(undefined4 *)(param_2 + 0x24) = 1;
    return 1;
  }
  __InternalCxxFrameHandler
            (param_1,*(int *)(param_2 + 0xc),param_3,0,*(int **)(param_2 + 8),
             *(int *)(param_2 + 0x10),*(int *)(param_2 + 0x14),'\x01');
  if (*(int *)(param_2 + 0x24) == 0) {
    _UnwindNestedFrames(param_2,(int)param_1);
  }
                    /* WARNING: Could not recover jumptable at 0x1000f2f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(param_2 + 0x18))();
  return uVar1;
}
#endif


/* ---- 0x1000f310  FUN_1000f310 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_1000f310(int param_1,int param_2,int param_3,uint *param_4,uint *param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  iVar2 = *(int *)(param_1 + 0x10);
  uVar5 = *(uint *)(param_1 + 0xc);
  uVar3 = uVar5;
  uVar4 = uVar5;
  while (-1 < param_2) {
    if (uVar5 == 0xffffffff) {
      FUN_100141b0();
    }
    uVar5 = uVar5 - 1;
    iVar1 = iVar2 + uVar5 * 0x14;
    if (((*(int *)(iVar1 + 4) < param_3) && (param_3 <= *(int *)(iVar1 + 8))) ||
       (uVar5 == 0xffffffff)) {
      param_2 = param_2 + -1;
      uVar3 = uVar4;
      uVar4 = uVar5;
    }
  }
  uVar5 = uVar5 + 1;
  *param_4 = uVar5;
  *param_5 = uVar3;
  if ((*(uint *)(param_1 + 0xc) < uVar3) || (uVar3 < uVar5)) {
    FUN_100141b0();
  }
  return iVar2 + uVar5 * 0x14;
}
#endif


/* ---- 0x1000f45d  FUN_1000f45d ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __fastcall FUN_1000f45d(undefined4 param_1)

{
  undefined4 in_EAX;
  undefined4 unaff_EBP;
  
  DAT_100282c0 = param_1;
  DAT_100282bc = in_EAX;
  DAT_100282c4 = unaff_EBP;
  return;
}
#endif


/* ---- 0x1000f5c0  FUN_1000f5c0 ---- */
uint __cdecl FUN_1000f5c0(int param_1)

{
  uint uVar1;
  
  if (1 < DAT_10028b5c) {
    uVar1 = _isctype(param_1,0x103);
    return uVar1;
  }
  return *(ushort *)(PTR_DAT_10028950 + param_1 * 2) & 0x103;
}

/* ---- 0x1000f5f0  FUN_1000f5f0 ---- */
uint __cdecl FUN_1000f5f0(int param_1)

{
  uint uVar1;
  
  if (1 < DAT_10028b5c) {
    uVar1 = _isctype(param_1,4);
    return uVar1;
  }
  return (byte)PTR_DAT_10028950[param_1 * 2] & 4;
}

/* ---- 0x1000f620  FUN_1000f620 ---- */
uint __cdecl FUN_1000f620(int param_1)

{
  uint uVar1;
  
  if (1 < DAT_10028b5c) {
    uVar1 = _isctype(param_1,8);
    return uVar1;
  }
  return (byte)PTR_DAT_10028950[param_1 * 2] & 8;
}

/* ---- 0x1000f650  FUN_1000f650 ---- */
uint __cdecl FUN_1000f650(int param_1)

{
  uint uVar1;
  
  if (1 < DAT_10028b5c) {
    uVar1 = _isctype(param_1,0x107);
    return uVar1;
  }
  return *(ushort *)(PTR_DAT_10028950 + param_1 * 2) & 0x107;
}

/* ---- 0x1000fde0  FUN_1000fde0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000fde0(void)

{
  undefined **ppuVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (_DAT_1002d720 == 0) {
    _DAT_1002d720 = 0x200;
  }
  else if (_DAT_1002d720 < 0x14) {
    _DAT_1002d720 = 0x14;
  }
  _DAT_1002c714 = calloc(_DAT_1002d720,4);
  if (_DAT_1002c714 == (int *)0x0) {
    _DAT_1002d720 = 0x14;
    _DAT_1002c714 = calloc(0x14,4);
    if (_DAT_1002c714 == (int *)0x0) {
      _amsg_exit(0x1a);
    }
  }
  iVar3 = 0;
  ppuVar1 = &PTR_DAT_100282d0;
  do {
    *(undefined ***)((int)_DAT_1002c714 + iVar3) = ppuVar1;
    ppuVar1 = ppuVar1 + 8;
    iVar3 = iVar3 + 4;
  } while ((int)ppuVar1 < IMG_ADDR(0x10028550));
  uVar2 = 0;
  puVar4 = (undefined4 *)IMG_ADDR(0x100282e0);
  do {
    if (((&PTR_1002c600)[(int)uVar2 >> 5][(uVar2 & 0x1f) * 9] == -1) ||
       ((&PTR_1002c600)[(int)uVar2 >> 5][(uVar2 & 0x1f) * 9] == 0)) {
      *puVar4 = 0xffffffff;
    }
    puVar4 = puVar4 + 8;
    uVar2 = uVar2 + 1;
  } while ((int)puVar4 < IMG_ADDR(0x10028340));
  return;
}
#endif


/* ---- 0x1000fea0  FUN_1000fea0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __stdcall FUN_1000fea0(int a1,int a2,int a3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = ((code *)FUN_100157a0)();
  if (DAT_1002c0c0 == '\0') {
    return CONCAT31((int3)((uint)uVar1 >> 8),DAT_1002c0c0);
  }
  iVar3 = 0;
  _lock(2);
  iVar4 = 3;
  if (3 < _DAT_1002d720) {
    do {
      iVar2 = *(int *)(_DAT_1002c714 + iVar4 * 4);
      if (iVar2 != 0) {
        if (((*(byte *)(iVar2 + 0xc) & 0x83) != 0) && (iVar2 = FUN_1001edd0(iVar2), iVar2 != -1)) {
          iVar3 = iVar3 + 1;
        }
        if (0x13 < iVar4) {
          DeleteCriticalSection(*(int *)(_DAT_1002c714 + iVar4 * 4) + 0x20);
          free(*(undefined **)(_DAT_1002c714 + iVar4 * 4));
          *(undefined4 *)(_DAT_1002c714 + iVar4 * 4) = 0;
        }
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < _DAT_1002d720);
  }
  _unlock(2);
  return iVar3;
}
#endif


/* ---- 0x100119e0  FUN_100119e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_100119e0(void)

{
  return 0;
}
#endif


/* ---- 0x100119f0  FUN_100119f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_100119f0(char *param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  
  puVar5 = (undefined4 *)&STACK0X(0x0000000c);
  if (0 < param_2) {
    do {
      pcVar6 = (char *)*puVar5;
      puVar5 = puVar5 + 1;
      uVar2 = 0xffffffff;
      do {
        pcVar8 = pcVar6;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar8 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar8;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      iVar3 = -1;
      pcVar6 = param_1;
      do {
        pcVar7 = pcVar6;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar7 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar7;
      } while (cVar1 != '\0');
      pcVar6 = pcVar8 + -uVar2;
      pcVar8 = pcVar7 + -1;
      for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar8 = pcVar8 + 4;
      }
      param_2 = param_2 + -1;
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar8 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar8 = pcVar8 + 1;
      }
    } while (param_2 != 0);
  }
  return;
}
#endif


/* ---- 0x10011e20  FUN_10011e20 ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float __cdecl FUN_10011e20(void)

{
  float10 in_ST0;
  float10 fVar1;
  double dVar2;
  
  dVar2 = (double)in_ST0;
  FUN_10018ec8(SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
  fVar1 = (float10)((code *)FUN_10011e3d)(SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
  return (float)fVar1;
}
#endif


/* ---- 0x10011e3d  FUN_10011e3d ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_10011e3d(int param_1,uint param_2)

{
  uint in_EAX;
  bool in_ZF;
  ushort in_FPUControlWord;
  float10 in_ST0;
  float10 extraout_ST0;
  undefined4 unaff_retaddr;
  
  if (in_ZF) {
    if (((in_EAX & 0xfffff) != 0) || (param_1 != 0)) {
      FUN_10018e6c();
    }
LAB_10011ecc:
    if (DAT_1002bf88 == 0) {
      FUN_10018df7(&DAT_100288e0,0xd,in_FPUControlWord,unaff_retaddr,param_1,param_2);
      return;
    }
  }
  else {
    if (in_FPUControlWord != 0x27f) {
      in_EAX = FUN_10018e55();
      in_ST0 = extraout_ST0;
    }
    if (in_EAX < 0x3ff00000) {
      fpatan(SQRT(((float10)1 - in_ST0) * ((float10)1 + in_ST0)),in_ST0);
    }
    else if ((0x3ff00000 < in_EAX) || ((param_2 & 0xfffff) != 0 || param_1 != 0)) goto LAB_10011ecc;
    if (DAT_1002bf88 == 0) {
      FUN_10018eeb(&DAT_100288e0,0xd,unaff_retaddr,param_1,param_2);
      return;
    }
  }
  return;
}
#endif


/* ---- 0x100120fa  FUN_100120fa ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
float __fastcall FUN_100120fa(undefined4 param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)((code *)FUN_10019b30)(param_1,IMG_ADDR(0x100288f0));
  return (float)fVar1;
}
#endif


/* ---- 0x10012104  FUN_10012104 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_10012104(void)

{
  ushort in_FPUStatusWord;
  float10 in_ST0;
  float10 in_ST1;
  float10 extraout_ST1;
  
  do {
    if (_DAT_1002bf8c == 1) {
      in_ST1 = (float10)FUN_1001a7ac();
      in_ST0 = extraout_ST1;
    }
    else {
      in_ST1 = in_ST1 - (float10)(unkint10)(in_ST1 / in_ST0) * in_ST0;
    }
  } while ((in_FPUStatusWord & 0x400) != 0);
  return in_ST1;
}
#endif


/* ---- 0x10012350  FUN_10012350 ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_10012350(int param_1)

{
  int *piVar1;
  
  piVar1 = _getptd();
  piVar1[5] = param_1;
  return;
}
#endif


/* ---- 0x10012360  FUN_10012360 ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_10012360(void)

{
  uint uVar1;
  int *piVar2;
  
  piVar2 = _getptd();
  uVar1 = piVar2[5] * 0x343fd + 0x269ec3;
  piVar2[5] = uVar1;
  return uVar1 >> 0x10 & 0x7fff;
}
#endif


/* ---- 0x100129a0  FUN_100129a0 ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint * __cdecl FUN_100129a0(uint *param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  uint *puVar4;
  uint uVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  uint *puVar10;
  
  cVar3 = *param_2;
  if (cVar3 == '\0') {
    return param_1;
  }
  if (param_2[1] == '\0') {
    while (((uint)param_1 & 3) != 0) {
      uVar5 = *param_1;
      if ((char)uVar5 == cVar3) {
        return param_1;
      }
      param_1 = (uint *)((int)param_1 + 1);
      if ((char)uVar5 == '\0') {
        return (uint *)0x0;
      }
    }
    while( true ) {
      while( true ) {
        uVar5 = *param_1;
        uVar8 = uVar5 ^ CONCAT22(CONCAT11(cVar3,cVar3),CONCAT11(cVar3,cVar3));
        uVar7 = uVar5 ^ 0xffffffff ^ uVar5 + 0x7efefeff;
        puVar10 = param_1 + 1;
        if (((uVar8 ^ 0xffffffff ^ uVar8 + 0x7efefeff) & 0x81010100) != 0) break;
        param_1 = puVar10;
        if ((uVar7 & 0x81010100) != 0) {
          if ((uVar7 & 0x1010100) != 0) {
            return (uint *)0x0;
          }
          if ((uVar5 + 0x7efefeff & 0x80000000) == 0) {
            return (uint *)0x0;
          }
        }
      }
      uVar5 = *param_1;
      if ((char)uVar5 == cVar3) {
        return param_1;
      }
      if ((char)uVar5 == '\0') {
        return (uint *)0x0;
      }
      cVar6 = (char)(uVar5 >> 8);
      if (cVar6 == cVar3) {
        return (uint *)((int)param_1 + 1);
      }
      if (cVar6 == '\0') {
        return (uint *)0x0;
      }
      cVar6 = (char)(uVar5 >> 0x10);
      if (cVar6 == cVar3) {
        return (uint *)((int)param_1 + 2);
      }
      if (cVar6 == '\0') break;
      cVar6 = (char)(uVar5 >> 0x18);
      if (cVar6 == cVar3) {
        return (uint *)((int)param_1 + 3);
      }
      param_1 = puVar10;
      if (cVar6 == '\0') {
        return (uint *)0x0;
      }
    }
    return (uint *)0x0;
  }
  do {
    cVar6 = (char)*param_1;
    do {
      while (puVar10 = param_1, param_1 = (uint *)((int)puVar10 + 1), cVar6 != cVar3) {
        if (cVar6 == '\0') {
          return (uint *)0x0;
        }
        cVar6 = *(char *)param_1;
      }
      cVar6 = *(char *)param_1;
      pcVar9 = param_2;
      puVar4 = puVar10;
    } while (cVar6 != param_2[1]);
    do {
      if (pcVar9[2] == '\0') {
        return puVar10;
      }
      if (*(char *)((int)puVar4 + 2) != pcVar9[2]) break;
      pcVar1 = pcVar9 + 3;
      if (*pcVar1 == '\0') {
        return puVar10;
      }
      pcVar2 = (char *)((int)puVar4 + 3);
      pcVar9 = pcVar9 + 2;
      puVar4 = (uint *)((int)puVar4 + 2);
    } while (*pcVar1 == *pcVar2);
  } while( true );
}
#endif


/* ---- 0x10012ec0  FUN_10012ec0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10012ec0(void)

{
  FUN_1001d560((void *)0x10000,0x30000);
  return;
}
#endif


/* ---- 0x10012ee0  FUN_10012ee0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Removing unreachable block (ram,0x10012f21) */

undefined4 FUN_10012ee0(void)

{
  return 0;
}
#endif


/* ---- 0x10012f30  FUN_10012f30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10012f30(void)

{
  int a1;
  code *pcVar1;
  undefined4 uVar2;
  
  a1 = GetModuleHandleA(IMG_ADDR(0x10023e0c));
  if (a1 != 0) {
    pcVar1 = (code *)GetProcAddress(a1,IMG_ADDR(0x10023df0));
    if (pcVar1 != (code *)0x0) {
      uVar2 = (*pcVar1)(0);
      return uVar2;
    }
  }
  uVar2 = FUN_10012ee0();
  return uVar2;
}
#endif


/* ---- 0x10012f60  FUN_10012f60 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_10012f60(char *param_1)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  
  uVar3 = tolower((int)*param_1);
  if (uVar3 != 0x65) {
    do {
      param_1 = param_1 + 1;
      if (DAT_10028b5c < 2) {
        uVar3 = (byte)PTR_DAT_10028950[*param_1 * 2] & 4;
      }
      else {
        uVar3 = _isctype((int)*param_1,4);
      }
    } while (uVar3 != 0);
  }
  cVar2 = *param_1;
  *param_1 = DAT_10028b60;
  do {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    *param_1 = cVar2;
    cVar2 = cVar1;
  } while (*param_1 != '\0');
  return;
}
#endif


/* ---- 0x10012fc0  FUN_10012fc0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_10012fc0(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  
  cVar1 = *param_1;
  while ((cVar1 != '\0' && (cVar1 != DAT_10028b60))) {
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
    if (*pcVar4 == DAT_10028b60) {
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


/* ---- 0x10013030  FUN_10013030 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_10013030(double *param_1)

{
  if (0.0 <= *param_1) {
    return 1;
  }
  return 0;
}
#endif


/* ---- 0x10013050  FUN_10013050 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_10013050(int param_1,uint *param_2,byte *param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (param_1 != 0) {
    _atodbl(&local_8,param_3);
    *param_2 = local_8;
    param_2[1] = local_4;
    return;
  }
  _atoflt((uint *)&param_3,param_3);
  *param_2 = (uint)param_3;
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x10013420  FUN_10013420 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_10013420(undefined4 *param_1,char *param_2,int param_3,uint param_4,int param_5)

{
  if ((param_3 != 0x65) && (param_3 != 0x45)) {
    if (param_3 == 0x66) {
      _cftof(param_1,param_2,param_4);
      return;
    }
    _cftog(param_1,param_2,param_4,param_5);
    return;
  }
  _cftoe(param_1,param_2,param_4,param_5);
  return;
}
#endif


/* ---- 0x100139a6  FUN_100139a6 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100139a6(void)

{
  int unaff_EBP;
  
  FUN_100139f0(*(undefined4 *)(unaff_EBP + -0x14));
  return;
}
#endif


/* ---- 0x100139b3  FUN_100139b3 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

void FUN_100139b3(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_EBP;
  int iVar5;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  iVar2 = *(int *)(unaff_EBP + -0x18);
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iVar3 = *(int *)(unaff_EBP + 0x10);
  iVar4 = *(int *)(unaff_EBP + 8);
  iVar5 = *(int *)(*(int *)(iVar3 + 8) + *(int *)(unaff_EBP + -0x1c) * 8);
  *(int *)(unaff_EBP + -0x1c) = iVar5;
  while (iVar5 != *(int *)(unaff_EBP + 0x14)) {
    if ((iVar5 < 0) || (*(int *)(iVar3 + 4) <= iVar5)) {
      *(undefined4 *)(iVar2 + -4) = 0x10013976;
      FUN_100141b0();
    }
    *(undefined4 *)(unaff_EBP + -4) = 0;
    iVar1 = *(int *)(*(int *)(iVar3 + 8) + 4 + iVar5 * 8);
    if (iVar1 != 0) {
      *(undefined4 *)(iVar2 + -4) = 0x103;
      *(int *)(iVar2 + -8) = iVar4;
      *(int *)(iVar2 + -0xc) = iVar1;
      *(undefined4 *)(iVar2 + -0x10) = 0x10013994;
      FUN_10013ef0(*(int *)(iVar2 + -0xc),*(int *)(iVar2 + -8),*(int *)(iVar2 + -4));
    }
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    iVar5 = *(int *)(*(int *)(iVar3 + 8) + iVar5 * 8);
    *(int *)(unaff_EBP + -0x1c) = iVar5;
  }
  *(int *)(iVar4 + 8) = iVar5;
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return;
}
#endif


/* ---- 0x100139f0  FUN_100139f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_100139f0(undefined4 *param_1)

{
  if (*(int *)*param_1 == -0x1f928c9d) {
    terminate();
  }
  return 0;
}
#endif


/* ---- 0x10013b57  FUN_10013b57 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10013b57(void)

{
  int unaff_EBP;
  
  FUN_10013c00(*(undefined4 *)(unaff_EBP + -0x14));
  return;
}
#endif


/* ---- 0x10013b64  FUN_10013b64 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

undefined4 FUN_10013b64(void)

{
  int iVar1;
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  iVar1 = *(int *)(unaff_EBP + -0x18);
  *(undefined4 *)(unaff_EBP + -0x2c) = 0;
  *(undefined4 *)(iVar1 + -4) = 0xffffffff;
  *(int *)(iVar1 + -8) = unaff_EBP + -0x10;
  *(undefined4 *)(iVar1 + -0xc) = 0x10013b79;
  _local_unwind2(*(int *)(iVar1 + -8),*(int *)(iVar1 + -4));
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return 0;
}
#endif


/* ---- 0x10013b8f  FUN_10013b8f ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10013b8f(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int unaff_EBP;
  
  piVar1 = *(int **)(unaff_EBP + 8);
  iVar2 = *(int *)(unaff_EBP + -0x2c);
  *(undefined4 *)(*(int *)(unaff_EBP + 0xc) + -4) = *(undefined4 *)(unaff_EBP + -0x28);
  piVar3 = _getptd();
  piVar3[0x1b] = *(int *)(unaff_EBP + -0x1c);
  piVar3 = _getptd();
  piVar3[0x1c] = *(int *)(unaff_EBP + -0x20);
  if ((((*piVar1 == -0x1f928c9d) && (piVar1[4] == 3)) && (piVar1[5] == 0x19930520)) &&
     ((*(int *)(unaff_EBP + -0x24) == 0 && (iVar2 != 0)))) {
    _unwind_handler();
    FUN_10013e40((int)piVar1);
  }
  return;
}
#endif


/* ---- 0x10013c00  FUN_10013c00 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10013c00(int *param_1)

{
  param_1 = (int *)*param_1;
  if ((((*param_1 == -0x1f928c9d) && (param_1[4] == 3)) && (param_1[5] == 0x19930520)) &&
     (param_1[7] == 0)) {
    return 1;
  }
  return 0;
}
#endif


/* ---- 0x10013e0b  FUN_10013e0b ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10013e0b(void)

{
  return 1;
}
#endif


/* ---- 0x10013e11  FUN_10013e11 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

void FUN_10013e11(void)

{
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  *(undefined4 *)(*(int *)(unaff_EBP + -0x18) + -4) = 0x10013e19;
  terminate();
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return;
}
#endif


/* ---- 0x10013e40  FUN_10013e40 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_10013e40(int param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined *UNRECOVERED_JUMPTABLE;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_10023e60;
  puStack_10 = &LAB_1001dec8;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  if ((param_1 != 0) &&
     (UNRECOVERED_JUMPTABLE = *(undefined **)(*(int *)(param_1 + 0x1c) + 4),
     UNRECOVERED_JUMPTABLE != (undefined *)0x0)) {
    local_8 = 0;
    FUN_1000f070(*(undefined4 *)(param_1 + 0x18),UNRECOVERED_JUMPTABLE);
  }
  *unaff_FS_OFFSET = local_14;
  return;
}
#undef local_14
#undef local_8
#undef puStack_10
#undef puStack_c

#endif


/* ---- 0x10013e8a  FUN_10013e8a ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
bool FUN_10013e8a(void)

{
  int unaff_EBP;
  
  return *(char *)(unaff_EBP + 0xc) != '\0';
}
#endif


/* ---- 0x10013e95  FUN_10013e95 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

void FUN_10013e95(void)

{
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  *(undefined4 *)(*(int *)(unaff_EBP + -0x18) + -4) = 0x10013e9d;
  terminate();
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return;
}
#endif


/* ---- 0x10013ec0  FUN_10013ec0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_10013ec0(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 + *param_2;
  iVar1 = param_2[1];
  if (-1 < iVar1) {
    iVar2 = iVar2 + *(int *)(*(int *)(param_1 + iVar1) + param_2[2]) + iVar1;
  }
  return iVar2;
}
#endif


/* ---- 0x10013ef0  FUN_10013ef0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4 __stdcall FUN_10013ef0(int a1,int a2,int a3)

{
  code *extraout_EAX;
  undefined4 extraout_EAX_00;
  
  FUN_1000f45d(a3);
  (*extraout_EAX)();
  if (a3 == 0x100) {
    a3 = 2;
  }
  FUN_1000f45d(a3);
  return extraout_EAX_00;
}
#endif


/* ---- 0x1001416a  FUN_1001416a ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1001416a(void)

{
  return 1;
}
#endif


/* ---- 0x10014170  FUN_10014170 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

void FUN_10014170(void)

{
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  *(undefined4 *)(unaff_EBP + -4) = 0;
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *(undefined4 *)(*(int *)(unaff_EBP + -0x18) + -4) = 0x10014186;
  FUN_10014197();
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return;
}
#endif


/* ---- 0x10014197  FUN_10014197 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10014197(void)

{
  abort();
  return;
}
#endif


/* ---- 0x100141b0  FUN_100141b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100141b0(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_10023e88;
  puStack_10 = &LAB_1001dec8;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  if (PTR_terminate_10028ba4 != (undefined *)0x0) {
    local_8 = 1;
    (*(code *)PTR_terminate_10028ba4)();
  }
  local_8 = 0xffffffff;
  FUN_1001421e();
  *unaff_FS_OFFSET = local_14;
  return;
}
#undef local_14
#undef local_8
#undef puStack_10
#undef puStack_c

#endif


/* ---- 0x100141f1  FUN_100141f1 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_100141f1(void)

{
  return 1;
}
#endif


/* ---- 0x100141f7  FUN_100141f7 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

void FUN_100141f7(void)

{
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  *(undefined4 *)(unaff_EBP + -4) = 0;
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *(undefined4 *)(*(int *)(unaff_EBP + -0x18) + -4) = 0x1001420d;
  FUN_1001421e();
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return;
}
#endif


/* ---- 0x1001421e  FUN_1001421e ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1001421e(void)

{
  terminate();
  return;
}
#endif


/* ---- 0x10014f80  FUN_10014f80 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10014f80(uint param_1)

{
  if ((IMG_ADDR(0x100282cf) < param_1) && (param_1 < IMG_ADDR(0x10028531))) {
    _lock(((int)(param_1 + 0xeffd7d30) >> 5) + 0x1c);
    return;
  }
  EnterCriticalSection(param_1 + 0x20);
  return;
}
#endif


/* ---- 0x10014ff0  FUN_10014ff0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10014ff0(uint param_1)

{
  if ((IMG_ADDR(0x100282cf) < param_1) && (param_1 < IMG_ADDR(0x10028531))) {
    _unlock(((int)(param_1 + 0xeffd7d30) >> 5) + 0x1c);
    return;
  }
  LeaveCriticalSection(param_1 + 0x20);
  return;
}
#endif


/* ---- 0x10015160  FUN_10015160 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10015160(int a1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_14 (*(undefined1 (*)[16])(_frame + (0x30 - 0x14)))
  
  uVar1 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = local_14;
  *unaff_FS_OFFSET = uVar1;
  return 1;
}
#undef local_14

#endif


/* ---- 0x1001519c  FUN_1001519c ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
bool FUN_1001519c(void)

{
  int unaff_EBP;
  
  return *(int *)**(undefined4 **)(unaff_EBP + -0x14) == -0x3ffffffb;
}
#endif


/* ---- 0x100151b0  FUN_100151b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __stdcall FUN_100151b0(int a1)

{
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return 0;
}
#endif


/* ---- 0x100156f0  FUN_100156f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_100156f0(int *param_1)

{
  int iVar1;
  
  iVar1 = _flush(param_1);
  if (iVar1 != 0) {
    return -1;
  }
  if ((param_1[3] & 0x4000U) != 0) {
    iVar1 = FUN_1001ee80(param_1[4]);
    return -(uint)(iVar1 != 0);
  }
  return 0;
}
#endif


/* ---- 0x100157a0  FUN_100157a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100157a0(void)

{
  FUN_100157b0(1);
  return;
}
#endif


/* ---- 0x100157b0  FUN_100157b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_100157b0(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar3 = 0;
  iStack_4 = 0;
  iVar2 = 0;
  _lock(2);
  if (0 < _DAT_1002d720) {
    do {
      iVar1 = *(int *)(_DAT_1002c714 + iVar3 * 4);
      if ((iVar1 != 0) && ((*(byte *)(iVar1 + 0xc) & 0x83) != 0)) {
        _lock_file2(iVar3,iVar1);
        iVar1 = *(int *)(_DAT_1002c714 + iVar3 * 4);
        if ((*(uint *)(iVar1 + 0xc) & 0x83) != 0) {
          if (param_1 == 1) {
            iVar1 = FUN_100156f0(iVar1);
            if (iVar1 != -1) {
              iStack_4 = iStack_4 + 1;
            }
          }
          else if (((param_1 == 0) && ((*(uint *)(iVar1 + 0xc) & 2) != 0)) &&
                  (iVar1 = FUN_100156f0(iVar1), iVar1 == -1)) {
            iVar2 = -1;
          }
        }
        _unlock_file2(iVar3,*(int *)(_DAT_1002c714 + iVar3 * 4));
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < _DAT_1002d720);
  }
  _unlock(2);
  if (param_1 != 1) {
    iStack_4 = iVar2;
  }
  return iStack_4;
}
#undef iStack_4

#endif


/* ---- 0x10015df0  FUN_10015df0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10015df0(uint param_1)

{
  undefined4 uVar1;
  int *piVar2;
  
  if ((param_1 < DAT_1002c700) &&
     ((*(byte *)((&PTR_1002c600)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    _lock_fhandle(param_1);
    uVar1 = FUN_10015e60(param_1);
    _unlock_fhandle(param_1);
    return uVar1;
  }
  piVar2 = _errno();
  *piVar2 = 9;
  piVar2 = __doserrno();
  *piVar2 = 0;
  return 0xffffffff;
}
#endif


/* ---- 0x10015e60  FUN_10015e60 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10015e60(uint param_1)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  
  iVar1 = _get_osfhandle(param_1);
  if (iVar1 != -1) {
    if ((param_1 == 1) || (param_1 == 2)) {
      iVar1 = _get_osfhandle(1);
      iVar2 = _get_osfhandle(2);
      if (iVar1 == iVar2) goto LAB_10015eb6;
    }
    iVar1 = _get_osfhandle(param_1);
    iVar1 = CloseHandle(iVar1);
    if (iVar1 == 0) {
      puVar3 = (undefined *)GetLastError();
      goto LAB_10015eb8;
    }
  }
LAB_10015eb6:
  puVar3 = (undefined *)0x0;
LAB_10015eb8:
  FUN_1001f5d0(param_1);
  *(undefined1 *)((&PTR_1002c600)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) = 0;
  if (puVar3 != (undefined *)0x0) {
    _dosmaperr(puVar3);
    return 0xffffffff;
  }
  return 0;
}
#endif


/* ---- 0x10015f40  FUN_10015f40 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
char * __cdecl FUN_10015f40(uint param_1,char *param_2,uint param_3)

{
  if ((param_3 == 10) && ((int)param_1 < 0)) {
    FUN_10015f80(param_1,param_2,10,1);
    return param_2;
  }
  FUN_10015f80(param_1,param_2,param_3,0);
  return param_2;
}
#endif


/* ---- 0x10015f80  FUN_10015f80 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_10015f80(uint param_1,char *param_2,uint param_3,int param_4)

{
  ulonglong uVar1;
  char *pcVar2;
  char cVar3;
  char *pcVar4;
  
  pcVar2 = param_2;
  if (param_4 != 0) {
    *param_2 = '-';
    param_2 = param_2 + 1;
    param_1 = -param_1;
    pcVar2 = param_2;
  }
  do {
    pcVar4 = pcVar2;
    uVar1 = (ulonglong)param_1;
    param_1 = param_1 / param_3;
    cVar3 = (char)(uVar1 % (ulonglong)param_3);
    if ((uint)(uVar1 % (ulonglong)param_3) < 10) {
      cVar3 = cVar3 + '0';
    }
    else {
      cVar3 = cVar3 + 'W';
    }
    *pcVar4 = cVar3;
    pcVar2 = pcVar4 + 1;
  } while (param_1 != 0);
  pcVar4[1] = '\0';
  do {
    cVar3 = *pcVar4;
    *pcVar4 = *param_2;
    *param_2 = cVar3;
    pcVar4 = pcVar4 + -1;
    param_2 = param_2 + 1;
  } while (param_2 < pcVar4);
  return;
}
#endif


/* ---- 0x10015ff0  FUN_10015ff0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
char * __cdecl FUN_10015ff0(uint param_1,char *param_2,uint param_3)

{
  FUN_10015f80(param_1,param_2,param_3,0);
  return param_2;
}
#endif


/* ---- 0x100160b0  FUN_100160b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_100160b0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  _lock(2);
  iVar2 = 0;
  if (0 < _DAT_1002d720) {
    do {
      iVar1 = *(int *)(_DAT_1002c714 + iVar2 * 4);
      if (iVar1 != 0) {
        _lock_file2(iVar2,iVar1);
        iVar1 = *(int *)(_DAT_1002c714 + iVar2 * 4);
        if (((*(byte *)(iVar1 + 0xc) & 0x83) != 0) && (*(int *)(iVar1 + 0x1c) != 0)) {
          FUN_1001ee10(iVar1);
          iVar3 = iVar3 + 1;
        }
        _unlock_file2(iVar2,*(int *)(_DAT_1002c714 + iVar2 * 4));
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < _DAT_1002d720);
  }
  _unlock(2);
  return iVar3;
}
#endif


/* ---- 0x10016c80  FUN_10016c80 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10016c80(void)

{
  int *piVar1;
  int iVar2;
  
  if (_DAT_1002c214 == 0) {
    PTR_PTR_10028764 = (undefined *)&PTR_DAT_100286b8;
    FUN_100170b0(_DAT_1002c1bc);
    free((undefined *)_DAT_1002c1bc);
    _DAT_1002c1bc = (int *)0x0;
    return 0;
  }
  piVar1 = calloc(1,0xac);
  if (piVar1 == (int *)0x0) {
    return 1;
  }
  iVar2 = FUN_10016d30(piVar1);
  if (iVar2 != 0) {
    FUN_100170b0(piVar1);
    free((undefined *)piVar1);
    return 1;
  }
  PTR_PTR_10028764 = (undefined *)piVar1;
  FUN_100170b0(_DAT_1002c1bc);
  free((undefined *)_DAT_1002c1bc);
  _DAT_1002c1bc = piVar1;
  return 0;
}
#endif


/* ---- 0x10016d30  FUN_10016d30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_10016d30(char *param_1)

{
  uint uVar1;
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
  
  uVar40 = (uint)_DAT_1002c1f6;
  uVar43 = (uint)_DAT_1002c1f8;
  if (param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  uVar1 = FUN_10020090(1,uVar40,0x31,param_1 + 4);
  uVar2 = FUN_10020090(1,uVar40,0x32,param_1 + 8);
  uVar3 = FUN_10020090(1,uVar40,0x33,param_1 + 0xc);
  uVar4 = FUN_10020090(1,uVar40,0x34,param_1 + 0x10);
  uVar5 = FUN_10020090(1,uVar40,0x35,param_1 + 0x14);
  uVar6 = FUN_10020090(1,uVar40,0x36,param_1 + 0x18);
  uVar7 = FUN_10020090(1,uVar40,0x37,param_1);
  uVar8 = FUN_10020090(1,uVar40,0x2a,param_1 + 0x20);
  uVar9 = FUN_10020090(1,uVar40,0x2b,param_1 + 0x24);
  uVar10 = FUN_10020090(1,uVar40,0x2c,param_1 + 0x28);
  uVar11 = FUN_10020090(1,uVar40,0x2d,param_1 + 0x2c);
  uVar12 = FUN_10020090(1,uVar40,0x2e,param_1 + 0x30);
  uVar13 = FUN_10020090(1,uVar40,0x2f,param_1 + 0x34);
  uVar14 = FUN_10020090(1,uVar40,0x30,param_1 + 0x1c);
  uVar15 = FUN_10020090(1,uVar40,0x44,param_1 + 0x38);
  uVar16 = FUN_10020090(1,uVar40,0x45,param_1 + 0x3c);
  uVar17 = FUN_10020090(1,uVar40,0x46,param_1 + 0x40);
  uVar18 = FUN_10020090(1,uVar40,0x47,param_1 + 0x44);
  uVar19 = FUN_10020090(1,uVar40,0x48,param_1 + 0x48);
  uVar20 = FUN_10020090(1,uVar40,0x49,param_1 + 0x4c);
  uVar21 = FUN_10020090(1,uVar40,0x4a,param_1 + 0x50);
  uVar22 = FUN_10020090(1,uVar40,0x4b,param_1 + 0x54);
  uVar23 = FUN_10020090(1,uVar40,0x4c,param_1 + 0x58);
  uVar24 = FUN_10020090(1,uVar40,0x4d,param_1 + 0x5c);
  uVar25 = FUN_10020090(1,uVar40,0x4e,param_1 + 0x60);
  uVar26 = FUN_10020090(1,uVar40,0x4f,param_1 + 100);
  uVar27 = FUN_10020090(1,uVar40,0x38,param_1 + 0x68);
  uVar28 = FUN_10020090(1,uVar40,0x39,param_1 + 0x6c);
  uVar29 = FUN_10020090(1,uVar40,0x3a,param_1 + 0x70);
  uVar30 = FUN_10020090(1,uVar40,0x3b,param_1 + 0x74);
  uVar31 = FUN_10020090(1,uVar40,0x3c,param_1 + 0x78);
  uVar32 = FUN_10020090(1,uVar40,0x3d,param_1 + 0x7c);
  uVar33 = FUN_10020090(1,uVar40,0x3e,param_1 + 0x80);
  uVar34 = FUN_10020090(1,uVar40,0x3f,param_1 + 0x84);
  uVar35 = FUN_10020090(1,uVar40,0x40,param_1 + 0x88);
  uVar36 = FUN_10020090(1,uVar40,0x41,param_1 + 0x8c);
  uVar37 = FUN_10020090(1,uVar40,0x42,param_1 + 0x90);
  uVar38 = FUN_10020090(1,uVar40,0x43,param_1 + 0x94);
  uVar39 = FUN_10020090(1,uVar40,0x28,param_1 + 0x98);
  uVar40 = FUN_10020090(1,uVar40,0x29,param_1 + 0x9c);
  uVar41 = FUN_10020090(1,uVar43,0x1f,param_1 + 0xa0);
  uVar42 = FUN_10020090(1,uVar43,0x20,param_1 + 0xa4);
  uVar43 = FUN_100172f0(uVar43,param_1);
  return uVar1 | uVar2 | uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10 | uVar11 |
         uVar12 | uVar13 | uVar14 | uVar15 | uVar16 | uVar17 | uVar18 | uVar19 | uVar20 | uVar21 |
         uVar22 | uVar23 | uVar24 | uVar25 | uVar26 | uVar27 | uVar28 | uVar29 | uVar30 | uVar31 |
         uVar32 | uVar33 | uVar34 | uVar35 | uVar36 | uVar37 | uVar38 | uVar39 | uVar40 | uVar41 |
         uVar42 | uVar43;
}
#endif


/* ---- 0x100170b0  FUN_100170b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_100170b0(undefined4 *param_1)

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


/* ---- 0x100172f0  FUN_100172f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_100172f0(char *param_1,int param_2)

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
  uVar3 = FUN_10020090(0,param_1,0x23,(char *)&iStack_4);
  uVar4 = FUN_10020090(0,pcVar7,0x25,(char *)&iStack_8);
  uVar5 = FUN_10020090(1,pcVar7,0x1e,(char *)&param_1);
  uVar5 = uVar3 | uVar4 | uVar5;
  if (uVar5 != 0) {
    return uVar5;
  }
  puVar6 = (undefined1 *)malloc(0xd);
  *(undefined1 **)(param_2 + 0xa8) = puVar6;
  if (iStack_4 == 0) {
    *puVar6 = 0x68;
    pcVar7 = puVar6 + 1;
    if (iStack_8 == 0) goto LAB_1001738c;
    *pcVar7 = 'h';
  }
  else {
    *puVar6 = 0x48;
    pcVar7 = puVar6 + 1;
    if (iStack_8 == 0) goto LAB_1001738c;
    *pcVar7 = 'H';
  }
  pcVar7 = puVar6 + 2;
LAB_1001738c:
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


/* ---- 0x100173f0  FUN_100173f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_100173f0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  
  uVar5 = (uint)DAT_1002c1f2;
  if (DAT_1002c210 == 0) {
    free(DAT_1002c1c0);
    free(DAT_1002c1c4);
    free(DAT_1002c1c8);
    DAT_1002c1c0 = (undefined *)0x0;
    DAT_1002c1c4 = (undefined *)0x0;
    DAT_1002c1c8 = (char *)0x0;
    uVar4 = malloc(2);
    *(undefined4 *)PTR_PTR_1002bbd8 = uVar4;
    if (*(undefined2 **)PTR_PTR_1002bbd8 == (undefined2 *)0x0) {
      return 0xffffffff;
    }
    **(undefined2 **)PTR_PTR_1002bbd8 = 0x2e;
    uVar4 = malloc(2);
    *(undefined4 *)(PTR_PTR_1002bbd8 + 4) = uVar4;
    if (*(undefined1 **)(PTR_PTR_1002bbd8 + 4) == (undefined1 *)0x0) {
      return 0xffffffff;
    }
    **(undefined1 **)(PTR_PTR_1002bbd8 + 4) = 0;
    uVar4 = malloc(2);
    *(undefined4 *)(PTR_PTR_1002bbd8 + 8) = uVar4;
    if (*(undefined1 **)(PTR_PTR_1002bbd8 + 8) == (undefined1 *)0x0) {
      return 0xffffffff;
    }
    **(undefined1 **)(PTR_PTR_1002bbd8 + 8) = 0;
  }
  else {
    iVar1 = FUN_10020090(1,uVar5,0xe,(char *)&DAT_1002c1c0);
    iVar2 = FUN_10020090(1,uVar5,0xf,(char *)&DAT_1002c1c4);
    iVar3 = FUN_10020090(1,uVar5,0x10,(char *)&DAT_1002c1c8);
    FUN_10017830(DAT_1002c1c8);
    if ((iVar1 != 0 || iVar2 != 0) || iVar3 != 0) {
      free(DAT_1002c1c0);
      free(DAT_1002c1c4);
      free(DAT_1002c1c8);
      DAT_1002c1c0 = (undefined *)0x0;
      DAT_1002c1c4 = (undefined *)0x0;
      DAT_1002c1c8 = (char *)0x0;
      return 0xffffffff;
    }
    if (*(undefined **)PTR_PTR_1002bbd8 != &DAT_1002bba0) {
      free(*(undefined **)PTR_PTR_1002bbd8);
      free(*(undefined **)(PTR_PTR_1002bbd8 + 4));
      free(*(undefined **)(PTR_PTR_1002bbd8 + 8));
    }
    *(undefined **)PTR_PTR_1002bbd8 = DAT_1002c1c0;
    *(undefined **)(PTR_PTR_1002bbd8 + 4) = DAT_1002c1c4;
    *(char **)(PTR_PTR_1002bbd8 + 8) = DAT_1002c1c8;
  }
  _DAT_10028b64 = 1;
  DAT_10028b60 = **(undefined1 **)PTR_PTR_1002bbd8;
  return 0;
}
#endif


/* ---- 0x100175f0  FUN_100175f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_100175f0(void)

{
  int *piVar1;
  uint uVar2;
  
  if (DAT_1002c20c == 0) {
    PTR_DAT_1002bba8 = *(undefined **)PTR_PTR_1002bbd8;
    PTR_DAT_1002bbac = *(undefined **)(PTR_PTR_1002bbd8 + 4);
    PTR_DAT_1002bbb0 = *(undefined **)(PTR_PTR_1002bbd8 + 8);
    PTR_PTR_1002bbd8 = (undefined *)&PTR_DAT_1002bba8;
    FUN_10017870((int)DAT_1002c1cc);
    free((undefined *)DAT_1002c1cc);
    DAT_1002c1cc = (int *)0x0;
    return 0;
  }
  piVar1 = calloc(1,0x30);
  if (piVar1 == (int *)0x0) {
    return 1;
  }
  uVar2 = FUN_100176e0((int)piVar1);
  if (uVar2 != 0) {
    FUN_10017870((int)piVar1);
    free((undefined *)piVar1);
    return 1;
  }
  *piVar1 = *(int *)PTR_PTR_1002bbd8;
  piVar1[1] = *(int *)(PTR_PTR_1002bbd8 + 4);
  piVar1[2] = *(int *)(PTR_PTR_1002bbd8 + 8);
  PTR_PTR_1002bbd8 = (undefined *)piVar1;
  FUN_10017870((int)DAT_1002c1cc);
  free((undefined *)DAT_1002c1cc);
  DAT_1002c1cc = piVar1;
  return 0;
}
#endif


/* ---- 0x100176e0  FUN_100176e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint __cdecl FUN_100176e0(int param_1)

{
  uint uVar1;
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
  
  uVar15 = (uint)DAT_1002c1ec;
  if (param_1 == 0) {
    return 0xffffffff;
  }
  uVar1 = FUN_10020090(1,uVar15,0x15,(char *)(param_1 + 0xc));
  uVar2 = FUN_10020090(1,uVar15,0x14,(char *)(param_1 + 0x10));
  uVar3 = FUN_10020090(1,uVar15,0x16,(char *)(param_1 + 0x14));
  uVar4 = FUN_10020090(1,uVar15,0x17,(char *)(param_1 + 0x18));
  uVar5 = FUN_10020090(1,uVar15,0x18,(char *)(param_1 + 0x1c));
  FUN_10017830(*(char **)(param_1 + 0x1c));
  uVar6 = FUN_10020090(1,uVar15,0x50,(char *)(param_1 + 0x20));
  uVar7 = FUN_10020090(1,uVar15,0x51,(char *)(param_1 + 0x24));
  uVar8 = FUN_10020090(0,uVar15,0x1a,(char *)(param_1 + 0x28));
  uVar9 = FUN_10020090(0,uVar15,0x19,(char *)(param_1 + 0x29));
  uVar10 = FUN_10020090(0,uVar15,0x54,(char *)(param_1 + 0x2a));
  uVar11 = FUN_10020090(0,uVar15,0x55,(char *)(param_1 + 0x2b));
  uVar12 = FUN_10020090(0,uVar15,0x56,(char *)(param_1 + 0x2c));
  uVar13 = FUN_10020090(0,uVar15,0x57,(char *)(param_1 + 0x2d));
  uVar14 = FUN_10020090(0,uVar15,0x52,(char *)(param_1 + 0x2e));
  uVar15 = FUN_10020090(0,uVar15,0x53,(char *)(param_1 + 0x2f));
  return uVar1 | uVar2 | uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10 | uVar11 |
         uVar12 | uVar13 | uVar14 | uVar15;
}
#endif


/* ---- 0x10017830  FUN_10017830 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_10017830(char *param_1)

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
      if (cVar2 != ';') goto LAB_10017846;
      do {
        *pcVar3 = pcVar3[1];
        pcVar1 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
      } while (*pcVar1 != '\0');
    }
    else {
      *param_1 = cVar2 + -0x30;
LAB_10017846:
      param_1 = param_1 + 1;
    }
    cVar2 = *param_1;
  } while( true );
}
#endif


/* ---- 0x10017870  FUN_10017870 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_10017870(int param_1)

{
  if ((param_1 != 0) && (*(undefined **)(param_1 + 0xc) != &DAT_1002c5b0)) {
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


/* ---- 0x100178e0  FUN_100178e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_100178e0(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  undefined2 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  byte *pbVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  undefined *puVar10;
  #define puStack_1c (*(undefined2 **)(_frame + (0x30 - 0x1c)))
  #define puStack_18 (*(undefined2 **)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define abStack_e (*(byte (*)[14])(_frame + (0x30 - 0xe)))
  
  puVar10 = (undefined *)0x0;
  puVar9 = (undefined2 *)0x0;
  if (DAT_1002c208 == 0) {
    PTR_DAT_10028950 = &DAT_1002895a;
    PTR_DAT_10028954 = &DAT_1002895a;
    free((undefined *)DAT_1002c1d0);
    free((undefined *)DAT_1002c1d4);
    DAT_1002c1d0 = (undefined2 *)0x0;
    DAT_1002c1d4 = (undefined2 *)0x0;
    return 0;
  }
  if ((DAT_1002c218 != 0) ||
     (iVar4 = FUN_10020090(0,(uint)DAT_1002c1e4,0xb,(char *)&DAT_1002c218), iVar4 == 0)) {
    puStack_18 = (undefined2 *)malloc(0x202);
    puStack_1c = (undefined2 *)malloc(0x202);
    puVar10 = (undefined *)malloc(0x101);
    puVar9 = (undefined2 *)malloc(0x202);
    if ((puStack_18 != (undefined2 *)0x0) &&
       (((puStack_1c != (undefined2 *)0x0 && (puVar10 != (undefined *)0x0)) &&
        (puVar9 != (undefined2 *)0x0)))) {
      iVar4 = 0;
      do {
        puVar10[iVar4] = (char)iVar4;
        iVar4 = iVar4 + 1;
      } while (iVar4 < 0x100);
      iVar4 = GetCPInfo(DAT_1002c218,(int)&uStack_14);
      if ((iVar4 != 0) && (uStack_14 < 3)) {
        DAT_10028b5c = uStack_14 & 0xffff;
        if ((1 < DAT_10028b5c) && (abStack_e[0] != 0)) {
          pbVar7 = abStack_e + 1;
          do {
            if (*pbVar7 == 0) break;
            uVar5 = (uint)pbVar7[-1];
            if (uVar5 <= *pbVar7) {
              do {
                puVar10[uVar5] = 0;
                uVar5 = uVar5 + 1;
              } while ((int)uVar5 <= (int)(uint)*pbVar7);
            }
            pbVar1 = pbVar7 + 1;
            pbVar7 = pbVar7 + 2;
          } while (*pbVar1 != 0);
        }
        puVar2 = puStack_18 + 1;
        iVar4 = __crtGetStringTypeA(1,puVar10,0x100,puVar2,0,0,0);
        if (iVar4 != 0) {
          *puStack_18 = 0;
          iVar4 = 0;
          puVar8 = puVar9;
          do {
            *puVar8 = (short)iVar4;
            puVar8 = puVar8 + 1;
            iVar4 = iVar4 + 1;
          } while (iVar4 < 0x100);
          puVar3 = (undefined4 *)(puStack_1c + 1);
          piVar6 = __crtGetStringTypeW(1,(int)puVar9,0x100,puVar3,0,0);
          if (piVar6 != (int *)0x0) {
            *puStack_1c = 0;
            if ((1 < (int)DAT_10028b5c) && (abStack_e[0] != 0)) {
              pbVar7 = abStack_e + 1;
              do {
                if (*pbVar7 == 0) break;
                uVar5 = (uint)pbVar7[-1];
                if (uVar5 <= *pbVar7) {
                  puVar8 = puStack_18 + uVar5 + 1;
                  do {
                    *puVar8 = 0x8000;
                    uVar5 = uVar5 + 1;
                    puVar8 = puVar8 + 1;
                  } while ((int)uVar5 <= (int)(uint)*pbVar7);
                }
                pbVar1 = pbVar7 + 1;
                pbVar7 = pbVar7 + 2;
              } while (*pbVar1 != 0);
            }
            PTR_DAT_10028950 = (undefined *)puVar2;
            PTR_DAT_10028954 = (undefined *)puVar3;
            if (DAT_1002c1d0 != (undefined2 *)0x0) {
              free((undefined *)DAT_1002c1d0);
            }
            DAT_1002c1d0 = puStack_18;
            if (DAT_1002c1d4 != (undefined2 *)0x0) {
              free((undefined *)DAT_1002c1d4);
            }
            DAT_1002c1d4 = puStack_1c;
            free(puVar10);
            free((undefined *)puVar9);
            return 0;
          }
        }
      }
    }
  }
  free((undefined *)puStack_18);
  free((undefined *)puStack_1c);
  free(puVar10);
  free((undefined *)puVar9);
  return 1;
}
#undef abStack_e
#undef puStack_18
#undef puStack_1c
#undef uStack_14

#endif


/* ---- 0x10017c10  FUN_10017c10 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_10017c10(byte *param_1,byte *param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int iVar2;
  #define abStack_28 (*(byte (*)[32])(_frame + (0x40 - 0x28)))
  
  abStack_28[0x1c] = 0;
  abStack_28[0x1d] = 0;
  abStack_28[0x1e] = 0;
  abStack_28[0x1f] = 0;
  abStack_28[0x18] = 0;
  abStack_28[0x19] = 0;
  abStack_28[0x1a] = 0;
  abStack_28[0x1b] = 0;
  abStack_28[0x14] = 0;
  abStack_28[0x15] = 0;
  abStack_28[0x16] = 0;
  abStack_28[0x17] = 0;
  abStack_28[0x10] = 0;
  abStack_28[0x11] = 0;
  abStack_28[0x12] = 0;
  abStack_28[0x13] = 0;
  abStack_28[0xc] = 0;
  abStack_28[0xd] = 0;
  abStack_28[0xe] = 0;
  abStack_28[0xf] = 0;
  abStack_28[8] = 0;
  abStack_28[9] = 0;
  abStack_28[10] = 0;
  abStack_28[0xb] = 0;
  abStack_28[4] = 0;
  abStack_28[5] = 0;
  abStack_28[6] = 0;
  abStack_28[7] = 0;
  abStack_28[0] = 0;
  abStack_28[1] = 0;
  abStack_28[2] = 0;
  abStack_28[3] = 0;
  while( true ) {
    bVar1 = *param_2;
    if (bVar1 == 0) break;
    param_2 = param_2 + 1;
    abStack_28[(int)(uint)bVar1 >> 3] = abStack_28[(int)(uint)bVar1 >> 3] | '\x01' << (bVar1 & 7);
  }
  iVar2 = -1;
  do {
    iVar2 = iVar2 + 1;
    bVar1 = *param_1;
    if (bVar1 == 0) {
      return iVar2;
    }
    param_1 = param_1 + 1;
  } while ((abStack_28[(int)(uint)bVar1 >> 3] >> (bVar1 & 7) & 1) == 0);
  return iVar2;
}
#undef abStack_28

#endif


/* ---- 0x10017df0  FUN_10017df0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_10017df0(int param_1,int param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  uVar1 = 1;
  if (-1 < param_2) {
    do {
      if (uVar1 == 0) {
        return;
      }
      iVar2 = (iVar3 + param_2) / 2;
      uVar1 = _stricmp((byte *)*param_3,*(byte **)(param_1 + iVar2 * 8));
      if (uVar1 == 0) {
        *param_3 = param_1 + 4 + iVar2 * 8;
      }
      else if ((int)uVar1 < 0) {
        param_2 = iVar2 + -1;
      }
      else {
        iVar3 = iVar2 + 1;
      }
    } while (iVar3 <= param_2);
  }
  return;
}
#endif


/* ---- 0x10018c77  FUN_10018c77 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __fastcall FUN_10018c77(undefined4 param_1,int param_2)

{
  float10 fVar1;
  char cVar2;
  byte bVar3;
  undefined2 uVar4;
  int unaff_EBP;
  float10 in_ST0;
  float10 in_ST1;
  
  if (*(char *)(param_2 + 0xe) == '\x05') {
    uVar4 = (undefined2)
            CONCAT31((uint3)((byte)((ushort)*(undefined2 *)(unaff_EBP + -0xa4) >> 8) & 0xfe | 2),
                     0x3f);
  }
  else {
    uVar4 = 0x133f;
  }
  *(undefined2 *)(unaff_EBP + -0xa2) = uVar4;
  fVar1 = (float10)0;
  *(int *)(unaff_EBP + -0x94) = param_2;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)ISNAN(in_ST0) << 8 | (ushort)(in_ST0 < fVar1) << 9 | (ushort)(in_ST0 != fVar1) << 10 |
       (ushort)(in_ST0 == fVar1) << 0xe;
  *(undefined1 *)(unaff_EBP + -0x90) = 0;
  fVar1 = (float10)0;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)ISNAN(in_ST1) << 8 | (ushort)(in_ST1 < fVar1) << 9 | (ushort)(in_ST1 != fVar1) << 10 |
       (ushort)(in_ST1 == fVar1) << 0xe;
  bVar3 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
  cVar2 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
                    /* WARNING: Could not recover jumptable at 0x10018d01. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(param_2 + (char)((&DAT_100295bc)[(byte)(cVar2 << 1 | cVar2 < '\0') & 0xf] |
                               (&DAT_100295bc)[(byte)((bVar3 & 7) << 1 | (char)bVar3 < '\0')] << 2)
              + 0x10))();
  return;
}
#endif


/* ---- 0x10018d14  FUN_10018d14 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 FUN_10018d14(void)

{
  return (float10)0;
}
#endif


/* ---- 0x10018d4d  FUN_10018d4d ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 FUN_10018d4d(void)

{
  int unaff_EBP;
  float10 in_ST0;
  unkbyte10 in_ST1;
  
  *(unkbyte10 *)(unaff_EBP + -0x9e) = in_ST1;
  if ((*(byte *)(unaff_EBP + -0x97) & 0x40) == 0) {
    *(undefined1 *)(unaff_EBP + -0x90) = 1;
  }
  else {
    *(undefined1 *)(unaff_EBP + -0x90) = 7;
  }
  return *(float10 *)(unaff_EBP + -0x9e) + in_ST0;
}
#endif


/* ---- 0x10018d4f  FUN_10018d4f ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 FUN_10018d4f(void)

{
  int unaff_EBP;
  unkbyte10 in_ST0;
  float10 in_ST1;
  
  *(unkbyte10 *)(unaff_EBP + -0x9e) = in_ST0;
  if ((*(byte *)(unaff_EBP + -0x97) & 0x40) == 0) {
    *(undefined1 *)(unaff_EBP + -0x90) = 1;
  }
  else {
    *(undefined1 *)(unaff_EBP + -0x90) = 7;
  }
  return *(float10 *)(unaff_EBP + -0x9e) + in_ST1;
}
#endif


/* ---- 0x10018d77  FUN_10018d77 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 FUN_10018d77(void)

{
  float10 fVar1;
  int unaff_EBP;
  unkbyte10 in_ST0;
  float10 fVar2;
  float10 in_ST1;
  
  *(unkbyte10 *)(unaff_EBP + -0x9e) = in_ST0;
  fVar1 = *(float10 *)(unaff_EBP + -0x9e);
  fVar2 = fVar1;
  if ((*(byte *)(unaff_EBP + -0x97) & 0x40) != 0) {
    *(float10 *)(unaff_EBP + -0x9e) = in_ST1;
    fVar2 = *(float10 *)(unaff_EBP + -0x9e);
    in_ST1 = fVar1;
    if ((*(byte *)(unaff_EBP + -0x97) & 0x40) != 0) {
      *(undefined1 *)(unaff_EBP + -0x90) = 7;
      goto LAB_10018db3;
    }
  }
  *(undefined1 *)(unaff_EBP + -0x90) = 1;
LAB_10018db3:
  return fVar2 + in_ST1;
}
#endif


/* ---- 0x10018db6  FUN_10018db6 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

unkbyte10 FUN_10018db6(void)

{
  int unaff_EBP;
  unkbyte10 Var1;
  
  Var1 = _DAT_100295a0;
  if (*(char *)(unaff_EBP + -0x90) < '\x01') {
    *(undefined1 *)(unaff_EBP + -0x90) = 1;
  }
  return Var1;
}
#endif


/* ---- 0x10018de0  FUN_10018de0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 __fastcall
FUN_10018de0(undefined4 param_1,uint param_2,undefined2 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float10 in_ST0;
  #define local_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define uStack_20 (*(undefined4 *)(_frame + (0x40 - 0x20)))
  #define uStack_1c (*(undefined4 *)(_frame + (0x40 - 0x1c)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(undefined4 *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(undefined4 *)(_frame + (0x40 - 0x10)))
  #define dStack_c (*(double *)(_frame + (0x40 - 0xc)))
  
  local_14 = param_7;
  local_10 = param_8;
  dStack_c = (double)in_ST0;
  uStack_1c = param_5;
  uStack_18 = param_6;
  uStack_20 = param_1;
  _except1(param_2,&local_24,&param_3);
  return (float10)dStack_c;
}
#undef dStack_c
#undef local_10
#undef local_14
#undef local_24
#undef uStack_18
#undef uStack_1c
#undef uStack_20

#endif


/* ---- 0x10018df7  FUN_10018df7 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 __fastcall
FUN_10018df7(undefined4 param_1,uint param_2,ushort param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float10 in_ST0;
  #define local_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(undefined4 *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(undefined4 *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(undefined4 *)(_frame + (0x40 - 0x18)))
  #define local_c (*(double *)(_frame + (0x40 - 0xc)))
  
  local_c = (double)in_ST0;
  local_1c = param_5;
  local_18 = param_6;
  local_20 = param_1;
  _except1(param_2,&local_24,&param_3);
  return (float10)local_c;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_c

#endif


/* ---- 0x10018e40  FUN_10018e40 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined1 *FUN_10018e40(void)

{
  float10 in_ST0;
  float10 fVar1;
  undefined1 auVar2 [10];
  
  fVar1 = (float10)f2xm1(-(ROUND(in_ST0) - in_ST0));
  auVar2 = (undefined1  [10])fscale((float10)1 + fVar1,ROUND(in_ST0));
  return auVar2;
}
#endif


/* ---- 0x10018e55  FUN_10018e55 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10018e55(void)

{
  undefined4 in_EAX;
  
  return in_EAX;
}
#endif


/* ---- 0x10018e6c  FUN_10018e6c ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_10018e6c(void)

{
  uint in_EAX;
  
  if ((in_EAX & 0x80000) != 0) {
    return 7;
  }
  return 1;
}
#endif


/* ---- 0x10018e85  FUN_10018e85 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint __fastcall FUN_10018e85(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_2 + 4) & 0x7ff00000;
  if (uVar1 != 0x7ff00000) {
    return uVar1;
  }
  return *(uint *)(param_2 + 4);
}
#endif


/* ---- 0x10018ec8  FUN_10018ec8 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint __cdecl FUN_10018ec8(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x7ff00000) != 0x7ff00000) {
    return param_2 & 0x7ff00000;
  }
  return param_2;
}
#endif


/* ---- 0x10018ede  FUN_10018ede ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10018ede(void)

{
  return;
}
#endif


/* ---- 0x10018eeb  FUN_10018eeb ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __fastcall
FUN_10018eeb(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  ushort in_FPUStatusWord;
  ushort unaff_retaddr;
  
  if (((unaff_retaddr != 0x27f) && ((unaff_retaddr & 0x20) != 0)) &&
     ((in_FPUStatusWord & 0x20) != 0)) {
    FUN_10018df7(param_1,param_2,unaff_retaddr,param_3,param_4,param_5);
    return;
  }
  return;
}
#endif


/* ---- 0x10018f29  FUN_10018f29 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __fastcall
FUN_10018f29(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort in_FPUStatusWord;
  float10 in_ST0;
  ushort unaff_retaddr;
  #define uStack_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uStack_4 = (uint)((ulonglong)(double)in_ST0 >> 0x20);
  if (((ulonglong)(double)in_ST0 & 0x7ff0000000000000) == 0) {
    fscale(in_ST0,(float10)1536.0);
  }
  else if ((uStack_4 & 0x7ff00000) == 0x7ff00000) {
    fscale(in_ST0,(float10)-1536.0);
  }
  else if (((unaff_retaddr == 0x27f) || ((unaff_retaddr & 0x20) != 0)) ||
          ((in_FPUStatusWord & 0x20) == 0)) {
    return;
  }
  if (param_2 == 0x1d) {
    FUN_10018de0(param_1,0x1d,unaff_retaddr,param_3,param_4,param_5,param_6,param_7);
    return;
  }
  FUN_10018df7(param_1,param_2,unaff_retaddr,param_3,param_4,param_5);
  return;
}
#undef uStack_4

#endif


/* ---- 0x10018ff0  FUN_10018ff0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 __cdecl FUN_10018ff0(int param_1,int param_2,uint param_3)

{
  int *piVar1;
  float10 extraout_ST0;
  uint in_stack_00000010;
  
  if (DAT_1002bbe0 == 0) {
    FUN_10019770((float10 *)0x1,param_1,param_2,param_3,0,0,param_2,param_3,in_stack_00000010);
    return extraout_ST0;
  }
  piVar1 = _errno();
  *piVar1 = 0x21;
  FUN_10019aa0();
  return (float10)(double)CONCAT44(param_3,param_2);
}
#endif


/* ---- 0x10019040  FUN_10019040 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 __cdecl
FUN_10019040(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
            uint param_7)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  undefined3 extraout_var;
  float10 *__return_storage_ptr__;
  float10 extraout_ST0;
  #define local_58 (*(uint (*)[14])(_frame + (0x70 - 0x58)))
  #define local_20 (*(uint *)(_frame + (0x70 - 0x20)))
  
  bVar1 = _handle_exc(param_1,(double *)&param_5,param_7);
  if (((uint)(bVar1)) == 0) {
    local_20 = local_20 & 0xfffffffe;
    _raise_exc(local_58,&param_7,(byte)param_1,param_2,&param_3,&param_5);
  }
  __return_storage_ptr__ = (float10 *)FUN_10019880(param_1);
  if ((DAT_1002bbe0 == 0) && (__return_storage_ptr__ != (float10 *)0x0)) {
    FUN_10019770(__return_storage_ptr__,param_2,param_3,param_4,0,0,param_5,param_6,param_7);
    return extraout_ST0;
  }
  FUN_10019820((int)__return_storage_ptr__);
  FUN_10019aa0();
  return (float10)(double)CONCAT44(param_6,param_5);
}
#undef local_20
#undef local_58

#endif


/* ---- 0x10019770  FUN_10019770 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 * __cdecl
FUN_10019770(float10 *__return_storage_ptr__,int param_1,int param_2,uint param_3,uint param_4,
            uint param_5,uint param_6,uint param_7,uint param_8)

{
  int iVar1;
  float10 *pfVar2;
  
  iVar1 = FUN_10019850(param_1);
  if (iVar1 != 0) {
    FUN_10019aa0();
    pfVar2 = (float10 *)FUN_100119e0();
    if (pfVar2 == (float10 *)0x0) {
      pfVar2 = (float10 *)((code *)FUN_10019820)((int)__return_storage_ptr__);
    }
    return pfVar2;
  }
  FUN_10019aa0();
  pfVar2 = (float10 *)((code *)FUN_10019820)((int)__return_storage_ptr__);
  return pfVar2;
}
#endif


/* ---- 0x10019820  FUN_10019820 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_10019820(int param_1)

{
  int *piVar1;
  
  if (param_1 == 1) {
    piVar1 = _errno();
    *piVar1 = 0x21;
  }
  else if ((1 < param_1) && (param_1 < 4)) {
    piVar1 = _errno();
    *piVar1 = 0x22;
    return;
  }
  return;
}
#endif


/* ---- 0x10019850  FUN_10019850 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_10019850(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = &DAT_100295d0;
  do {
    if (*piVar1 == param_1) {
      return *(undefined4 *)(iVar2 * 8 + IMG_ADDR(0x100295d4));
    }
    piVar1 = piVar1 + 2;
    iVar2 = iVar2 + 1;
  } while ((int)piVar1 < IMG_ADDR(0x100296a8));
  return 0;
}
#endif


/* ---- 0x10019880  FUN_10019880 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_10019880(uint param_1)

{
  if ((param_1 & 0x20) != 0) {
    return 5;
  }
  if ((param_1 & 8) != 0) {
    return 1;
  }
  if ((param_1 & 4) != 0) {
    return 2;
  }
  if ((param_1 & 1) != 0) {
    return 3;
  }
  return (param_1 & 2) << 1;
}
#endif


/* ---- 0x100198c0  FUN_100198c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float __cdecl FUN_100198c0(undefined4 param_1,undefined4 param_2,short param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define uStack_4 (*(undefined2 *)(_frame + (0x20 - 0x4)))
  
  uStack_4 = (undefined2)param_2;
  return (float)(double)CONCAT26(PIECE(param_2,2,2) & 0x800f | (param_3 + 0x3fe) * 0x10,
                                 CONCAT24(uStack_4,param_1));
}
#undef uStack_4

#endif


/* ---- 0x10019900  FUN_10019900 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_10019900(int param_1,uint param_2)

{
  if ((param_2 == 0x7ff00000) && (param_1 == 0)) {
    return 1;
  }
  if ((param_2 == 0xfff00000) && (param_1 == 0)) {
    return 2;
  }
  if ((PIECE(param_2,2,2) & 0x7ff8) == 0x7ff8) {
    return 3;
  }
  if (((PIECE(param_2,2,2) & 0x7ff8) == 0x7ff0) && (((param_2 & 0x7ffff) != 0 || (param_1 != 0)))) {
    return 4;
  }
  return 0;
}
#endif


/* ---- 0x10019960  FUN_10019960 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float __cdecl FUN_10019960(uint param_1,uint param_2,int *param_3)

{
  ushort uVar1;
  double dVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  float fVar6;
  
  if ((double)CONCAT17(PIECE(param_2,3,1),CONCAT16(PIECE(param_2,2,1),CONCAT24((undefined2)param_2,param_1)))
      == 0.0) {
    *param_3 = 0;
    return 0.0;
  }
  if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    dVar2 = (double)CONCAT17(PIECE(param_2,3,1),
                             CONCAT16(PIECE(param_2,2,1),CONCAT24((undefined2)param_2,param_1)));
    iVar5 = -0x3fd;
    uVar4 = param_2;
    uVar3 = param_2;
    while ((uVar3 & 0x100000) == 0) {
      uVar3 = uVar4 << 1;
      PIECE(param_2,0,2) = (undefined2)uVar3;
      PIECE(param_2,2,1) = (undefined1)(uVar3 >> 0x10);
      PIECE(param_2,3,1) = (byte)(uVar3 >> 0x18);
      uVar4 = uVar3;
      if ((param_1 & 0x80000000) != 0) {
        uVar4 = uVar3 | 1;
        PIECE(param_2,0,2) = (undefined2)uVar4;
      }
      param_1 = param_1 << 1;
      iVar5 = iVar5 + -1;
    }
    uVar1 = CONCAT11(PIECE(param_2,3,1),PIECE(param_2,2,1)) & 0xffef;
    PIECE(param_2,2,1) = (undefined1)uVar1;
    PIECE(param_2,3,1) = (byte)(uVar1 >> 8);
    if (dVar2 < 0.0) {
      PIECE(param_2,3,1) = PIECE(param_2,3,1) | 0x80;
    }
    fVar6 = FUN_100198c0(param_1,CONCAT13(PIECE(param_2,3,1),CONCAT12(PIECE(param_2,2,1),(undefined2)param_2))
                         ,0);
    *param_3 = iVar5;
    return fVar6;
  }
  fVar6 = FUN_100198c0(param_1,param_2,0);
  *param_3 = (short)((ushort)(param_2 >> 0x14) & 0x7ff) + -0x3fe;
  return fVar6;
}
#endif


/* ---- 0x10019a70  FUN_10019a70 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_10019a70(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}
#endif


/* ---- 0x10019a80  FUN_10019a80 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_10019a80(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}
#endif


/* ---- 0x10019aa0  FUN_10019aa0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_10019aa0(void)

{
  short in_FPUControlWord;
  
  return (int)in_FPUControlWord;
}
#endif


/* ---- 0x10019ad0  FUN_10019ad0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10019ad0(void)

{
  return;
}
#endif


/* ---- 0x10019b30  FUN_10019b30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __fastcall FUN_10019b30(undefined4 param_1,int param_2)

{
  FUN_10018c77(param_1,param_2);
  FUN_10019bfa();
  return;
}
#endif


/* ---- 0x10019bfa  FUN_10019bfa ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10019bfa(void)

{
  char cVar1;
  ushort uVar2;
  int unaff_EBP;
  ushort in_FPUStatusWord;
  float10 in_ST0;
  
  if (DAT_1002bf88 != 0) {
    return;
  }
  *(double *)(unaff_EBP + -0x2d0) = (double)in_ST0;
  cVar1 = *(char *)(unaff_EBP + -0x90);
  if (cVar1 != '\0') {
    if ((cVar1 != -1) && (cVar1 != -2)) {
      if (cVar1 == '\0') {
        return;
      }
      *(int *)(unaff_EBP + -0x8e) = (int)cVar1;
      goto LAB_10019cc9;
    }
    uVar2 = *(ushort *)(unaff_EBP + -0x2ca) & 0x7ff0;
    if (uVar2 == 0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 4;
      in_ST0 = (float10)fscale(in_ST0,(float10)1536.0);
      if (ABS(in_ST0) < (float10)2.2250738585072014e-308) {
        in_ST0 = in_ST0 * (float10)0.0;
      }
      goto LAB_10019cc9;
    }
    if (uVar2 == 0x7ff0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 3;
      in_ST0 = (float10)fscale(in_ST0,(float10)-1536.0);
      if ((float10)1.7976931348623157e+308 < ABS(in_ST0)) {
        in_ST0 = in_ST0 * (float10)INFINITY;
      }
      goto LAB_10019cc9;
    }
  }
  if ((*(ushort *)(unaff_EBP + -0xa4) & 0x20) != 0) {
    return;
  }
  if ((in_FPUStatusWord & 0x20) == 0) {
    return;
  }
  *(undefined4 *)(unaff_EBP + -0x8e) = 8;
LAB_10019cc9:
  *(int *)(unaff_EBP + -0x8a) = *(int *)(unaff_EBP + -0x94) + 1;
  if ((*(byte *)(unaff_EBP + -0x2c8) & 1) == 0) {
    *(undefined4 *)(unaff_EBP + -0x86) = *(undefined4 *)(unaff_EBP + 8);
    *(undefined4 *)(unaff_EBP + -0x82) = *(undefined4 *)(unaff_EBP + 0xc);
    if (*(char *)(*(int *)(unaff_EBP + -0x94) + 0xd) != '\x01') {
      *(undefined4 *)(unaff_EBP + -0x7e) = *(undefined4 *)(unaff_EBP + 0x10);
      *(undefined4 *)(unaff_EBP + -0x7a) = *(undefined4 *)(unaff_EBP + 0x14);
    }
  }
  *(double *)(unaff_EBP + -0x76) = (double)in_ST0;
  _except1((int)*(char *)(*(int *)(unaff_EBP + -0x94) + 0xe),(int *)(unaff_EBP + -0x8e),
           (ushort *)(unaff_EBP + -0xa4));
  return;
}
#endif


/* ---- 0x1001a5a6  FUN_1001a5a6 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
FUN_1001a5a6(undefined4 param_1,uint param_2,ushort param_3,uint param_4,uint param_5,uint param_6,
            uint param_7,uint param_8,ushort param_9)

{
  uint uVar1;
  undefined4 in_EAX;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  
  if ((((((CONCAT22(param_3,PIECE(param_2,2,2)) ^ 0x700) & 0x700) == 0) &&
       (*(char *)(((PIECE(param_2,2,2) & 0x7800) >> 0xb) + IMG_ADDR(0x1002970c)) != '\0')) &&
      ((param_3 & 0x7fff) != 0x7fff)) &&
     ((((param_9 & 0x7fff) != 0 && ((param_9 & 0x7fff) != 0x7fff)) &&
      (((param_8 & 0x7fffffff) == 0 && ((param_2 & 0x7fffffff) == 0)))))) {
    uVar1 = param_8;
    if ((ushort)((param_3 & 0x7fff) + 0x3f) < (param_9 & 0x7fff)) {
      iVar2 = ((param_9 & 0x7fff) - (param_3 & 0x7fff) & 0x3f | 0x20) + 1;
      fVar4 = ABS((float10)CONCAT28(param_9 & 0x7fff | param_3 & 0x8000,
                                    CONCAT26(PIECE(param_2,2,2),CONCAT24((undefined2)param_2,param_1))));
      fVar3 = ABS((float10)CONCAT28(param_9,CONCAT26(PIECE(param_8,2,2),
                                                     CONCAT24((undefined2)param_8,param_7))));
      do {
        if (fVar4 <= fVar3) {
          fVar3 = fVar3 - fVar4;
        }
        fVar4 = fVar4 * (float10)_DAT_1002973c;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    else {
      while( true ) {
        PIECE(param_8,2,2) = (undefined2)(uVar1 >> 0x10);
        PIECE(param_8,0,2) = (undefined2)uVar1;
        if ((int)((param_9 & 0x7fff) - ((param_3 & 0x7fff) + 10)) < 0) break;
        fVar3 = (float10)CONCAT28(param_9,CONCAT26(PIECE(param_8,2,2),
                                                   CONCAT24((undefined2)param_8,param_7)));
        fVar4 = (float10)CONCAT28((param_9 & 0x7fff) - ((param_9 & 0x7fff) - param_3 & 7 | 4) |
                                  param_3 & 0x8000,
                                  CONCAT26(PIECE(param_2,2,2),CONCAT24((undefined2)param_2,param_1)));
        fVar3 = fVar3 - (float10)(unkint10)(fVar3 / fVar4) * fVar4;
        param_7 = SUB104(fVar3,0);
        uVar1 = (uint)((unkuint10)fVar3 >> 0x20);
        param_9 = (ushort)((unkuint10)fVar3 >> 0x40);
      }
    }
  }
  return in_EAX;
}
#endif


/* ---- 0x1001a7ac  FUN_1001a7ac ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_1001a7ac(void)

{
  float10 in_ST0;
  float10 extraout_ST0;
  float10 fVar1;
  float10 extraout_ST0_00;
  float10 in_ST1;
  uint uVar2;
  uint uVar3;
  ushort uVar4;
  uint in_stack_ffffffd8;
  uint in_stack_ffffffdc;
  undefined2 in_stack_ffffffe0;
  undefined2 in_stack_ffffffe2;
  uint uVar5;
  uint uVar6;
  ushort uVar7;
  
  uVar5 = SUB104(in_ST0,0);
  uVar6 = (uint)((unkuint10)in_ST0 >> 0x20);
  uVar7 = (ushort)((unkuint10)in_ST0 >> 0x40);
  uVar2 = SUB104(in_ST1,0);
  uVar3 = (uint)((unkuint10)in_ST1 >> 0x20);
  uVar4 = (ushort)((unkuint10)in_ST1 >> 0x40);
  if (((uint)((unkuint10)in_ST1 >> 0x30) & 0x7fff0000) != 0) {
    FUN_1001a5a6(uVar2,uVar3,uVar4,in_stack_ffffffd8,in_stack_ffffffdc,
                 CONCAT22(in_stack_ffffffe2,in_stack_ffffffe0),uVar5,uVar6,uVar7);
    return extraout_ST0;
  }
  if (uVar2 == 0 && uVar3 == 0) {
    return in_ST0 - (float10)(unkint10)(in_ST0 / in_ST1) * in_ST1;
  }
  if ((uVar7 & 0x7fff) < 0x7fbf) {
    fVar1 = in_ST0 * (float10)_DAT_10029724;
    uVar5 = SUB104(fVar1,0);
    uVar6 = (uint)((unkuint10)fVar1 >> 0x20);
    uVar7 = (ushort)((unkuint10)fVar1 >> 0x40);
  }
  fVar1 = in_ST1 * (float10)_DAT_10029724;
  FUN_1001a5a6(SUB104(fVar1,0),(uint)((unkuint10)fVar1 >> 0x20),(ushort)((unkuint10)fVar1 >> 0x40),
               uVar2,uVar3,CONCAT22(in_stack_ffffffe2,uVar4),uVar5,uVar6,uVar7);
  return extraout_ST0_00;
}
#endif


/* ---- 0x1001c720  FUN_1001c720 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_1001c720(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  undefined *a3;
  
  if (DAT_1002c25c == 0) {
    iVar1 = GetLocaleInfoW(0,1,0,0);
    if (iVar1 == 0) {
      iVar1 = GetLocaleInfoA(0,1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_1002c25c = 2;
    }
    else {
      DAT_1002c25c = 1;
    }
  }
  if (DAT_1002c25c == 2) {
    iVar1 = GetLocaleInfoA(param_1,param_2,param_3,param_4);
    return iVar1;
  }
  if (DAT_1002c25c != 1) {
    return DAT_1002c25c;
  }
  if (param_5 == 0) {
    param_5 = DAT_1002c218;
  }
  iVar1 = GetLocaleInfoW(param_1,param_2,0,0);
  if (iVar1 != 0) {
    a3 = (undefined *)malloc(iVar1 * 2);
    if (a3 == (undefined *)0x0) {
      return 0;
    }
    iVar1 = GetLocaleInfoW(param_1,param_2,(int)a3,iVar1);
    if (iVar1 != 0) {
      if (param_4 == 0) {
        iVar1 = WideCharToMultiByte(param_5,0x220,(int)a3,-1,0,0,0,0);
        if (iVar1 != 0) {
          free(a3);
          return iVar1;
        }
      }
      else {
        iVar1 = WideCharToMultiByte(param_5,0x220,(int)a3,-1,param_3,param_4,0,0);
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


/* ---- 0x1001ce80  FUN_1001ce80 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_1001ce80(undefined4 param_1)

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


/* ---- 0x1001d2f0  FUN_1001d2f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __stdcall FUN_1001d2f0(int a1,int a2,int a3)

{
  return 1;
}
#endif


/* ---- 0x1001d520  FUN_1001d520 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint __thiscall FUN_1001d520(void *this,uint param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  undefined2 in_FPUControlWord;
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  
  local_8 = CONCAT22((short)((uint)this >> 0x10),in_FPUControlWord);
  uVar1 = FUN_1001d580(local_8);
  FUN_1001d620();
  return param_2 & param_1 | ~param_2 & uVar1;
}
#undef local_8

#endif


/* ---- 0x1001d560  FUN_1001d560 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_1001d560(void *param_1,uint param_2)

{
  FUN_1001d520(param_1,(uint)param_1,param_2 & 0xfff7ffff);
  return;
}
#endif


/* ---- 0x1001d580  FUN_1001d580 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint __cdecl FUN_1001d580(uint param_1)

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


/* ---- 0x1001d620  FUN_1001d620 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1001d620(void)

{
  return;
}
#endif


/* ---- 0x1001d6b0  FUN_1001d6b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_1001d6b0(int param_1,int param_2)

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


/* ---- 0x1001d720  FUN_1001d720 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_1001d720(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  
  bVar1 = (byte)(param_2 >> 0x1f);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  iVar2 = __addl(*(uint *)(param_1 + iVar3 * 4),
                 1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) & 0x1f),
                 (uint *)(param_1 + iVar3 * 4));
  iVar3 = iVar3 + -1;
  if (-1 < iVar3) {
    puVar4 = (uint *)(param_1 + iVar3 * 4);
    do {
      if (iVar2 == 0) {
        return 0;
      }
      iVar2 = __addl(*puVar4,1,puVar4);
      iVar3 = iVar3 + -1;
      puVar4 = puVar4 + -1;
    } while (-1 < iVar3);
  }
  return iVar2;
}
#endif


/* ---- 0x1001d790  FUN_1001d790 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_1001d790(int param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  byte bVar2;
  int iVar3;
  undefined4 *puVar4;
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  bVar2 = (byte)(param_2 >> 0x1f);
  bVar2 = 0x1f - ((((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  if (((*(uint *)(param_1 + iVar3 * 4) & 1 << (bVar2 & 0x1f)) != 0) &&
     (iVar1 = FUN_1001d6b0(param_1,param_2 + 1), iVar1 == 0)) {
    local_4 = FUN_1001d720(param_1,param_2 + -1);
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
  return local_4;
}
#undef local_4

#endif


/* ---- 0x1001d830  FUN_1001d830 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_1001d830(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 - (int)param_2;
  iVar2 = 3;
  do {
    *(undefined4 *)((int)param_2 + iVar1) = *param_2;
    param_2 = param_2 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}
#endif


/* ---- 0x1001d850  FUN_1001d850 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_1001d850(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}
#endif


/* ---- 0x1001d860  FUN_1001d860 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_1001d860(int *param_1)

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


/* ---- 0x1001d880  FUN_1001d880 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_1001d880(uint *param_1,int param_2)

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


/* ---- 0x1001dc70  FUN_1001dc70 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int * __cdecl FUN_1001dc70(undefined4 param_1,undefined4 param_2,int *param_3,char *param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  undefined4 in_stack_ffffffbc;
  undefined2 uVar7;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(undefined2 *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(short *)(_frame + (0x40 - 0x1c)))
  #define local_1a (*(char *)(_frame + (0x40 - 0x1a)))
  #define local_18 (*(char (*)[24])(_frame + (0x40 - 0x18)))
  
  uVar7 = (undefined2)((uint)in_stack_ffffffbc >> 0x10);
  FUN_1001dd00(&local_28,&param_1);
  iVar2 = _I10_OUTPUT(local_28,local_24,CONCAT22(uVar7,local_20),0x11,0,&local_1c);
  param_3[2] = iVar2;
  param_3[1] = (int)local_1c;
  *param_3 = (int)local_1a;
  uVar3 = 0xffffffff;
  pcVar5 = local_18;
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
#undef local_18
#undef local_1a
#undef local_1c
#undef local_20
#undef local_24
#undef local_28

#endif


/* ---- 0x1001dd00  FUN_1001dd00 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __cdecl FUN_1001dd00(uint *param_1,uint *param_2)

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


/* ---- 0x1001ddc0  FUN_1001ddc0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_1001ddc0(void)

{
  _amsg_exit(2);
  return;
}
#endif


/* ---- 0x1001ddd0  FUN_1001ddd0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __stdcall FUN_1001ddd0(int a1)

{
  int *piVar1;
  bool bVar2;
  undefined3 extraout_var;
  undefined4 uVar3;
  
  piVar1 = *(int **)a1;
  if (((*piVar1 == -0x1f928c9d) && (piVar1[4] == 3)) && (piVar1[5] == 0x19930520)) {
    terminate();
    return 1;
  }
  if (_DAT_1002c594 != (code *)0x0) {
    bVar2 = _ValidateExecute(_DAT_1002c594);
    if (((uint)(bVar2)) != 0) {
      uVar3 = (*_DAT_1002c594)(a1);
      return uVar3;
    }
  }
  return 0;
}
#endif


/* ---- 0x1001de30  FUN_1001de30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1001de30(void)

{
  _DAT_1002c594 = SetUnhandledExceptionFilter(FUN_1001ddd0);
  return;
}
#endif


/* ---- 0x1001de50  FUN_1001de50 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1001de50(void)

{
  SetUnhandledExceptionFilter(_DAT_1002c594);
  return;
}
#endif


/* ---- 0x1001edd0  FUN_1001edd0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1001edd0(int param_1)

{
  undefined4 uVar1;
  
  if ((*(byte *)(param_1 + 0xc) & 0x40) != 0) {
    *(undefined4 *)(param_1 + 0xc) = 0;
    return 0xffffffff;
  }
  FUN_10014f80(param_1);
  uVar1 = FUN_1001ee10(param_1);
  FUN_10014ff0(param_1);
  return uVar1;
}
#endif


/* ---- 0x1001ee10  FUN_1001ee10 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1001ee10(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0xffffffff;
  if ((*(byte *)(param_1 + 3) & 0x83) != 0) {
    uVar2 = _flush(param_1);
    FUN_10021a10(param_1);
    iVar1 = FUN_10015df0(param_1[4]);
    if (iVar1 < 0) {
      param_1[3] = 0;
      return 0xffffffff;
    }
    if ((undefined *)param_1[7] != (undefined *)0x0) {
      free((undefined *)param_1[7]);
      param_1[7] = 0;
    }
  }
  param_1[3] = 0;
  return uVar2;
}
#endif


/* ---- 0x1001ee80  FUN_1001ee80 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1001ee80(uint param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  
  if (DAT_1002c700 <= param_1) {
LAB_1001ef0c:
    piVar3 = _errno();
    *piVar3 = 9;
    return 0xffffffff;
  }
  if ((*(byte *)((&PTR_1002c600)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) == 0)
  goto LAB_1001ef0c;
  _lock_fhandle(param_1);
  if ((*(byte *)((&PTR_1002c600)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0) {
    uVar1 = _get_osfhandle(param_1);
    iVar2 = FlushFileBuffers(uVar1);
    if (iVar2 == 0) {
      iVar2 = GetLastError();
    }
    else {
      iVar2 = 0;
    }
    uVar1 = 0;
    if (iVar2 == 0) goto LAB_1001eefd;
    piVar3 = __doserrno();
    *piVar3 = iVar2;
  }
  piVar3 = _errno();
  *piVar3 = 9;
  uVar1 = 0xffffffff;
LAB_1001eefd:
  _unlock_fhandle(param_1);
  return uVar1;
}
#endif


/* ---- 0x1001ef20  FUN_1001ef20 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint __cdecl FUN_1001ef20(char *param_1,char *param_2,int param_3)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  
  cVar2 = *param_1;
  while (cVar2 == ';') {
    pcVar3 = param_1 + 1;
    param_1 = param_1 + 1;
    cVar2 = *pcVar3;
  }
  iVar4 = param_3 + -1;
  pcVar3 = param_1;
  if (iVar4 != 0) {
    cVar2 = *param_1;
    while ((cVar2 != '\0' && (cVar2 != ';'))) {
      if (cVar2 == '\"') {
        pcVar1 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
        cVar2 = *pcVar1;
        while ((cVar2 != '\0' && (cVar2 != '\"'))) {
          *param_2 = cVar2;
          param_2 = param_2 + 1;
          pcVar3 = pcVar3 + 1;
          iVar4 = iVar4 + -1;
          if (iVar4 == 0) goto LAB_1001ef81;
          cVar2 = *pcVar3;
        }
        if (*pcVar3 != '\0') {
          pcVar3 = pcVar3 + 1;
        }
      }
      else {
        *param_2 = cVar2;
        param_2 = param_2 + 1;
        pcVar3 = pcVar3 + 1;
        iVar4 = iVar4 + -1;
        if (iVar4 == 0) {
LAB_1001ef81:
          *param_2 = '\0';
          return 0;
        }
      }
      cVar2 = *pcVar3;
    }
    if (*pcVar3 == ';') {
      do {
        pcVar1 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
      } while (*pcVar1 == ';');
      *param_2 = '\0';
      return -(uint)(param_1 != pcVar3) & (uint)pcVar3;
    }
  }
  *param_2 = '\0';
  return -(uint)(param_1 != pcVar3) & (uint)pcVar3;
}
#endif


/* ---- 0x1001f5d0  FUN_1001f5d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_1001f5d0(uint param_1)

{
  uint uVar1;
  int *piVar2;
  undefined4 uVar3;
  
  if (param_1 < DAT_1002c700) {
    uVar1 = param_1 & 0x1f;
    piVar2 = (&PTR_1002c600)[(int)param_1 >> 5];
    if (((*(byte *)(piVar2 + uVar1 * 9 + 1) & 1) != 0) && (piVar2[uVar1 * 9] != -1)) {
      if (DAT_1002c01c == 1) {
        if (param_1 == 0) {
          uVar3 = 0xfffffff6;
        }
        else if (param_1 == 1) {
          uVar3 = 0xfffffff5;
        }
        else {
          if (param_1 != 2) goto LAB_1001f637;
          uVar3 = 0xfffffff4;
        }
        SetStdHandle(uVar3,0);
      }
LAB_1001f637:
      (&PTR_1002c600)[(int)param_1 >> 5][uVar1 * 9] = -1;
      return 0;
    }
  }
  piVar2 = _errno();
  *piVar2 = 9;
  piVar2 = __doserrno();
  *piVar2 = 0;
  return 0xffffffff;
}
#endif


/* ---- 0x10020090  FUN_10020090 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 __cdecl FUN_10020090(int param_1,int param_2,int param_3,char *param_4)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  byte *pbVar7;
  #define local_80 (*(uint (*)[32])(_frame + (0x90 - 0x80)))
  
  if (param_1 != 1) {
    if (param_1 != 0) {
      return 0xffffffff;
    }
    iVar4 = __crtGetLocaleInfoA(param_2,param_3,IMG_ADDR(0x1002c5a8),4,0);
    if (iVar4 != 0) {
      pbVar7 = &DAT_1002c5a8;
      *param_4 = '\0';
      while( true ) {
        bVar1 = *pbVar7;
        if (DAT_10028b5c < 2) {
          uVar3 = (byte)PTR_DAT_10028950[(uint)bVar1 * 2] & 4;
        }
        else {
          uVar3 = _isctype((uint)bVar1,4);
        }
        if (uVar3 == 0) break;
        pbVar7 = pbVar7 + 2;
        *param_4 = *param_4 * '\n' + bVar1 + -0x30;
        if (IMG_ADDR(0x1002c5af) < (int)pbVar7) {
          return 0;
        }
      }
      return 0;
    }
    return 0xffffffff;
  }
  puVar5 = local_80;
  bVar2 = false;
  uVar3 = FUN_1001c720(param_2,param_3,(int)local_80,0x80,0);
  if (uVar3 == 0) {
    iVar4 = GetLastError();
    if (((iVar4 != 0x7a) || (uVar3 = FUN_1001c720(param_2,param_3,0,0,0), uVar3 == 0)) ||
       (puVar5 = (uint *)malloc(uVar3), puVar5 == (uint *)0x0)) goto LAB_10020140;
    bVar2 = true;
    uVar3 = FUN_1001c720(param_2,param_3,(int)puVar5,uVar3,0);
    if (uVar3 == 0) goto LAB_10020140;
  }
  puVar6 = (uint *)malloc(uVar3);
  *(uint **)param_4 = puVar6;
  if (puVar6 != (uint *)0x0) {
    strncpy(puVar6,puVar5,uVar3);
    if (!bVar2) {
      return 0;
    }
    free((undefined *)puVar5);
    return 0;
  }
LAB_10020140:
  if (!bVar2) {
    return 0xffffffff;
  }
  free((undefined *)puVar5);
  return 0xffffffff;
}
#undef local_80

#endif


/* ---- 0x10020470  FUN_10020470 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_10020470(int param_1,uint param_2)

{
  int iVar1;
  
  if ((PIECE(param_2,2,2) & 0x7ff0) != 0x7ff0) {
    if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
      return (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff90) + 0x80;
    }
    if ((double)CONCAT26(PIECE(param_2,2,2),CONCAT24((undefined2)param_2,param_1)) == 0.0) {
      return (-(uint)((param_2 & 0x80000000) != 0) & 0xffffffe0) + 0x40;
    }
    return (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff08) + 0x100;
  }
  iVar1 = FUN_10019900(param_1,param_2);
  if (iVar1 == 1) {
    return 0x200;
  }
  if (iVar1 != 2) {
    if (iVar1 != 3) {
      return 1;
    }
    return 2;
  }
  return 4;
}
#endif


/* ---- 0x100206d0  FUN_100206d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __fastcall FUN_100206d0(byte param_1,int param_2)

{
  int in_EAX;
  
  if (0x3f < param_1) {
    return 0;
  }
  if (param_1 < 0x20) {
    return in_EAX << (param_1 & 0x1f);
  }
  return 0;
}
#endif


/* ---- 0x10021a10  FUN_10021a10 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10021a10(undefined4 *param_1)

{
  if (((param_1[3] & 0x83) != 0) && ((param_1[3] & 8) != 0)) {
    free((undefined *)param_1[2]);
    param_1[3] = param_1[3] & 0xfffffbf7;
    *param_1 = 0;
    param_1[2] = 0;
    param_1[1] = 0;
  }
  return;
}
#endif


/* ---- 0x10021f90  FUN_10021f90 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10021f90(void)

{
  int unaff_EBP;
  
  luaM_free(*(void **)(unaff_EBP + -0x10));
  return;
}
#endif


/* ---- 0x10021f9b  FUN_10021f9b ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_10021f9b(void)

{
  int unaff_EBP;
  
  luaM_free(*(void **)(unaff_EBP + -0x10));
  return;
}
#endif


/* ---- 0x10021fa6  FUN_10021fa6 ---- */
void __cdecl FUN_10021fa6(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  FUN_1000f0e0(param_1,param_2,param_3,param_4);
  return;
}

/* ---- 0x10021fb0  FUN_10021fb0 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void FUN_10021fb0(void)

{
  int unaff_EBP;
  
  luaM_free(*(void **)(unaff_EBP + -0x10));
  return;
}
#endif


/* ---- 0x10021fbb  FUN_10021fbb ---- */
undefined4 FUN_10021fbb(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = __InternalCxxFrameHandler(param_1,param_2,param_3,param_4,(int *)&UNK_10024df8,0,0,'\0');
  return uVar1;
}

/* ---- 0x10021fd0  FUN_10021fd0 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void FUN_10021fd0(void)

{
  int unaff_EBP;
  
  lvm__dd90(*(int *)(unaff_EBP + 8));
  return;
}
#endif


/* ---- 0x10021fdb  FUN_10021fdb ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void FUN_10021fdb(void)

{
  int unaff_EBP;
  
  lvm__dd90(*(int *)(unaff_EBP + 4));
  return;
}
#endif


/* ---- 0x10021fe6  FUN_10021fe6 ---- */
void __cdecl FUN_10021fe6(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  FUN_1000f0e0(param_1,param_2,param_3,param_4);
  return;
}

/* ---- 0x10021ff0  FUN_10021ff0 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void FUN_10021ff0(void)

{
  int unaff_EBP;
  
  lvm__dd90(*(int *)(unaff_EBP + -0x10));
  return;
}
#endif


/* ---- 0x10021ffb  FUN_10021ffb ---- */
void __cdecl FUN_10021ffb(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  FUN_1000f0e0(param_1,param_2,param_3,param_4);
  return;
}

/* ---- 0x10022010  FUN_10022010 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void FUN_10022010(void)

{
  int unaff_EBP;
  
  luaM_free(*(void **)(unaff_EBP + -0x10));
  return;
}
#endif


/* ---- 0x1002201b  FUN_1002201b ---- */
undefined4 FUN_1002201b(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = __InternalCxxFrameHandler(param_1,param_2,param_3,param_4,(int *)&UNK_10024e78,0,0,'\0');
  return uVar1;
}

/* ---- 0x10022030  FUN_10022030 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void FUN_10022030(void)

{
  int unaff_EBP;
  
  lvm__dd90(*(int *)(unaff_EBP + 8));
  return;
}
#endif


/* ---- 0x1002203b  FUN_1002203b ---- */
void __cdecl FUN_1002203b(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  FUN_1000f0e0(param_1,param_2,param_3,param_4);
  return;
}

/* ---- 0x10022050  FUN_10022050 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void FUN_10022050(void)

{
  int unaff_EBP;
  
  luaM_free(*(void **)(unaff_EBP + -0x10));
  return;
}
#endif


/* ---- 0x1002205b  FUN_1002205b ---- */
void __cdecl FUN_1002205b(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  FUN_1000f0e0(param_1,param_2,param_3,param_4);
  return;
}
