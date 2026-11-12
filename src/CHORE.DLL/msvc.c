/* CHORE.DLL :: msvc.c
 * functions 0x100055a0 .. 0x10008520 (15 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100055a0  msvc_strncpy ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x100056a0  msvc_strrchr ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x100056d0  msvc_fpmath ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime _fpmath (fpinit.c), CHORE.DLL's private copy: msvc_cfltcvt_init, _adjust_fdiv =
   _ms_p5_mp_test_fdiv(), _setdefaultprecision. Reached only from the original start-up code. */

void msvc_fpmath(void)

{
  msvc_cfltcvt_init();
  _DAT_100143f8 = FUN_100061d0();
  FUN_10006160();
  return;
}

/* ---- 0x100056f0  msvc_fpclear ---- */
/* MSVC 6 C runtime _fpclear (fpinit.c), private copy: empty on x86. Not referenced. */

void msvc_fpclear(void)

{
  return;
}

/* ---- 0x10005700  msvc_cfltcvt_init ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime _cfltcvt_init (fpinit.c), private copy: fills the floating-point conversion
   table (_cfltcvt, _cropzeros, _fassign, _forcdecpt, _positive) that printf / scanf use. */

void msvc_cfltcvt_init(void)

{
  _DAT_100106cc = FUN_10006260;
  _DAT_100106c8 = FUN_100066c0;
  _DAT_100106d0 = FUN_100062f0;
  _DAT_100106d4 = FUN_10006200;
  _DAT_100106d8 = FUN_100062d0;
  _DAT_100106dc = FUN_100066c0;
  return;
}

/* ---- 0x10005740  msvc_stricmp ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime _stricmp, CHORE.DLL's private copy (returns -1 / 0 / 1). The msvc_ prefix keeps
   it out of crt.c (a named C runtime function there is served by the host runtime and not linked)
   and keeps the rebuilt chore.dll, which exports every symbol, from exporting an _stricmp the EXE
   would bind to. Hand-written in build/overrides.c (the host _stricmp, sign only). */

int __cdecl msvc_stricmp(byte *a,byte *b)

{
  bool bVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  uint uVar8;
  int iVar7;
  
  iVar7 = _DAT_10015af0;
  if (_DAT_10014478 == 0) {
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_1000578e;
        bVar5 = *b;
        b = b + 1;
        bVar4 = *a;
        a = a + 1;
      } while (bVar4 == bVar5);
      bVar3 = bVar5 + 0xbf + (-((byte)(bVar5 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar4 = bVar4 + 0xbf;
      bVar5 = bVar4 + (-(bVar4 < 0x1a) & 0x20U) + 0x41;
    } while (bVar5 == bVar3);
    cVar6 = (bVar5 < bVar3) * -2 + '\x01';
LAB_1000578e:
    iVar7 = (int)cVar6;
  }
  else {
    LOCK();
    _DAT_10015af0 = _DAT_10015af0 + 1;
    UNLOCK();
    bVar1 = 0 < _DAT_10015aec;
    if (bVar1) {
      LOCK();
      UNLOCK();
      _DAT_10015af0 = iVar7;
      FUN_10006810(0x13);
    }
    uVar8 = (uint)bVar1;
    iVar7 = 0xff;
    do {
      do {
        if ((char)iVar7 == '\0') goto LAB_100057ef;
        bVar5 = *b;
        iVar7 = CONCAT31((int3)((uint)iVar7 >> 8),bVar5);
        b = b + 1;
        bVar4 = *a;
        a = a + 1;
      } while (bVar5 == bVar4);
      bVar5 = ((code *)FUN_10006a30)(bVar4,iVar7);
      iVar7 = ((code *)FUN_10006a30)();
    } while (bVar5 == (byte)iVar7);
    uVar2 = (uint)(bVar5 < (byte)iVar7);
    iVar7 = (1 - uVar2) - (uint)(uVar2 != 0);
LAB_100057ef:
    if (uVar8 == 0) {
      LOCK();
      _DAT_10015af0 = _DAT_10015af0 + -1;
      UNLOCK();
    }
    else {
      FUN_10006890();
    }
  }
  return iVar7;
}
#endif


/* ---- 0x10005810  msvc_sscanf ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x10005860  msvc_memmove ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x10005ba0  msvc_qsort ---- */
/* MSVC 6 C runtime qsort, CHORE.DLL's private copy, still compiled (Cos_AddKey sorts the keys of a
   track with it). The msvc_ prefix keeps it out of crt.c (named C runtime functions there are
   served by the host runtime and not linked) and keeps the rebuilt chore.dll, which exports every
   symbol, from exporting a qsort that the EXE would bind to. */

void msvc_qsort(uint param_1,uint param_2,uint param_3,code *param_4)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  uint uVar3;
  #define uStack_100 (*(uint *)(_frame + (0x110 - 0x100)))
  #define puStack_fc (*(uint **)(_frame + (0x110 - 0xfc)))
  #define puStack_f8 (*(uint **)(_frame + (0x110 - 0xf8)))
  #define iStack_f4 (*(int *)(_frame + (0x110 - 0xf4)))
  #define auStack_f0 (*(uint (*)[30])(_frame + (0x110 - 0xf0)))
  #define auStack_78 (*(uint (*)[30])(_frame + (0x110 - 0x78)))
  
  if ((param_2 < 2) || (param_3 == 0)) {
    return;
  }
  uStack_100 = (param_2 - 1) * param_3 + param_1;
  puStack_fc = auStack_f0;
  puStack_f8 = auStack_78;
  iStack_f4 = 0;
LAB_10005bf4:
  uVar1 = (uStack_100 - param_1) / param_3 + 1;
  if (8 < uVar1) {
    msvc_qsort_swap((uVar1 >> 1) * param_3 + param_1,param_1,param_3);
    uVar3 = uStack_100 + param_3;
    uVar1 = param_1;
LAB_10005c6e:
    uVar1 = uVar1 + param_3;
    if (uVar1 <= uStack_100) goto code_r0x10005c78;
    goto LAB_10005c88;
  }
  msvc_shortsort(param_1,uStack_100,param_3,param_4);
  goto LAB_10005c15;
code_r0x10005c78:
  iVar2 = (*param_4)(uVar1,param_1);
  if (iVar2 < 1) goto LAB_10005c6e;
LAB_10005c88:
  do {
    uVar3 = uVar3 - param_3;
    if (uVar3 <= param_1) break;
    iVar2 = (*param_4)(uVar3,param_1);
  } while (-1 < iVar2);
  if (uVar1 <= uVar3) {
    msvc_qsort_swap(uVar1,uVar3,param_3);
    goto LAB_10005c6e;
  }
  msvc_qsort_swap(param_1,uVar3,param_3);
  if ((int)((uVar3 - param_1) + -1) < (int)(uStack_100 - uVar1)) {
    if (uVar1 < uStack_100) {
      *puStack_f8 = uVar1;
      *puStack_fc = uStack_100;
      iStack_f4 = iStack_f4 + 1;
      puStack_f8 = puStack_f8 + 1;
      puStack_fc = puStack_fc + 1;
    }
    if (param_1 + param_3 < uVar3) {
      uStack_100 = uVar3 - param_3;
      goto LAB_10005bf4;
    }
  }
  else {
    if (param_1 + param_3 < uVar3) {
      *puStack_f8 = param_1;
      *puStack_fc = uVar3 - param_3;
      iStack_f4 = iStack_f4 + 1;
      puStack_f8 = puStack_f8 + 1;
      puStack_fc = puStack_fc + 1;
    }
    param_1 = uVar1;
    if (uVar1 < uStack_100) goto LAB_10005bf4;
  }
LAB_10005c15:
  iStack_f4 = iStack_f4 + -1;
  puStack_f8 = puStack_f8 + -1;
  puStack_fc = puStack_fc + -1;
  if (iStack_f4 < 0) {
    return;
  }
  uStack_100 = *puStack_fc;
  param_1 = *puStack_f8;
  goto LAB_10005bf4;
}
#undef auStack_78
#undef auStack_f0
#undef iStack_f4
#undef puStack_f8
#undef puStack_fc
#undef uStack_100


/* ---- 0x10005d50  msvc_shortsort ---- */
/* MSVC 6 C runtime (qsort.c, static shortsort): selection sort of a short range for msvc_qsort */

void msvc_shortsort(uint param_1,uint param_2,int param_3,code *param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  for (; uVar2 = param_1, uVar1 = param_1, param_1 < param_2; param_2 = param_2 - param_3) {
    while (uVar1 = param_3 + uVar1, uVar1 <= param_2) {
      iVar3 = (*param_4)(uVar1,uVar2);
      if (0 < iVar3) {
        uVar2 = uVar1;
      }
    }
    msvc_qsort_swap(uVar2,param_2,param_3);
  }
  return;
}

/* ---- 0x10005db0  msvc_qsort_swap ---- */
/* MSVC 6 C runtime (qsort.c, static swap): exchanges two elements byte by byte for msvc_qsort */

void msvc_qsort_swap(undefined1 *param_1,undefined1 *param_2,int param_3)

{
  undefined1 uVar1;
  
  if (param_1 != param_2) {
    for (; param_3 != 0; param_3 = param_3 + -1) {
      uVar1 = *param_1;
      *param_1 = *param_2;
      param_1 = param_1 + 1;
      *param_2 = uVar1;
      param_2 = param_2 + 1;
    }
  }
  return;
}

/* ---- 0x10005de0  msvc_bsearch ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x10005e90  msvc_strchr ---- */
/* not in the source: names/lib_replace.json (host): the system C runtime (msvcrt.dll) has it */


/* ---- 0x10005f50  FUN_10005f50 ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */


/* ---- 0x10008520  msvc_CPtoLCID ---- */
/* not in the source: names/lib_replace.json (dead): original C runtime code that nothing live reaches */

