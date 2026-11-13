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

void __cdecl msvc_fpmath(void)

{
  msvc_cfltcvt_init();
  _DAT_100143f8 = FUN_100061d0();
  FUN_10006160();
  return;
}

/* ---- 0x100056f0  msvc_fpclear ---- */
/* MSVC 6 C runtime _fpclear (fpinit.c), private copy: empty on x86. Not referenced. */

void __cdecl msvc_fpclear(void)

{
  return;
}

/* ---- 0x10005700  msvc_cfltcvt_init ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime _cfltcvt_init (fpinit.c), private copy: fills the floating-point conversion
   table (_cfltcvt, _cropzeros, _fassign, _forcdecpt, _positive) that printf / scanf use. */

void __cdecl msvc_cfltcvt_init(void)

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
  int iVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  uint uVar8;
  uint uVar9;
  uint uVar7;
  
  iVar2 = _DAT_10015af0;
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
    uVar7 = (uint)cVar6;
  }
  else {
    LOCK();
    _DAT_10015af0 = _DAT_10015af0 + 1;
    UNLOCK();
    bVar1 = 0 < _DAT_10015aec;
    if (bVar1) {
      LOCK();
      UNLOCK();
      _DAT_10015af0 = iVar2;
      FUN_10006810(0x13);
    }
    uVar9 = (uint)bVar1;
    uVar7 = 0xff;
    uVar8 = 0;
    do {
      do {
        if ((char)uVar7 == '\0') goto LAB_100057ef;
        bVar5 = *b;
        uVar7 = CONCAT31((int3)(uVar7 >> 8),bVar5);
        b = b + 1;
        bVar4 = *a;
        uVar8 = CONCAT31((int3)(uVar8 >> 8),bVar4);
        a = a + 1;
      } while (bVar5 == bVar4);
      uVar8 = FUN_10006a30(uVar8);
      uVar7 = FUN_10006a30(uVar7);
    } while ((byte)uVar8 == (byte)uVar7);
    uVar8 = (uint)((byte)uVar8 < (byte)uVar7);
    uVar7 = (1 - uVar8) - (uint)(uVar8 != 0);
LAB_100057ef:
    if (uVar9 == 0) {
      LOCK();
      _DAT_10015af0 = _DAT_10015af0 + -1;
      UNLOCK();
    }
    else {
      FUN_10006890();
    }
  }
  return uVar7;
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

void __cdecl msvc_qsort(uint param_1,uint param_2,uint param_3,void *param_4)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  #define puStack_100 (*(undefined1 **)(_frame + (0x110 - 0x100)))
  #define piStack_fc (*(int **)(_frame + (0x110 - 0xfc)))
  #define puStack_f8 (*(undefined4 **)(_frame + (0x110 - 0xf8)))
  #define iStack_f4 (*(int *)(_frame + (0x110 - 0xf4)))
  #define aiStack_f0 (*(int (*)[30])(_frame + (0x110 - 0xf0)))
  #define auStack_78 (*(undefined4 (*)[30])(_frame + (0x110 - 0x78)))
  
  if ((param_2 < 2) || (param_3 == 0)) {
    return;
  }
  puStack_100 = (undefined1 *)((param_2 - 1) * param_3 + param_1);
  piStack_fc = aiStack_f0;
  puStack_f8 = auStack_78;
  iStack_f4 = 0;
LAB_10005bf4:
  uVar1 = ((int)puStack_100 - param_1) / param_3 + 1;
  if (8 < uVar1) {
    msvc_qsort_swap((undefined1 *)(param_1 + (uVar1 >> 1) * param_3),(undefined1 *)param_1,param_3);
    puVar4 = puStack_100 + param_3;
    puVar3 = (undefined1 *)param_1;
LAB_10005c6e:
    puVar3 = puVar3 + param_3;
    if (puVar3 <= puStack_100) goto code_r0x10005c78;
    goto LAB_10005c88;
  }
  msvc_shortsort(param_1,(uint)puStack_100,param_3,param_4);
  goto LAB_10005c15;
code_r0x10005c78:
  iVar2 = (*(code *)param_4)(puVar3,param_1);
  if (iVar2 < 1) goto LAB_10005c6e;
LAB_10005c88:
  do {
    puVar4 = puVar4 + -param_3;
    if (puVar4 <= param_1) break;
    iVar2 = (*(code *)param_4)(puVar4,param_1);
  } while (-1 < iVar2);
  if (puVar3 <= puVar4) {
    msvc_qsort_swap(puVar3,puVar4,param_3);
    goto LAB_10005c6e;
  }
  msvc_qsort_swap((undefined1 *)param_1,puVar4,param_3);
  if ((int)(puVar4 + (-1 - param_1)) < (int)puStack_100 - (int)puVar3) {
    if (puVar3 < puStack_100) {
      *puStack_f8 = puVar3;
      *piStack_fc = (int)puStack_100;
      iStack_f4 = iStack_f4 + 1;
      puStack_f8 = puStack_f8 + 1;
      piStack_fc = piStack_fc + 1;
    }
    if ((undefined1 *)(param_1 + param_3) < puVar4) {
      puStack_100 = puVar4 + -param_3;
      goto LAB_10005bf4;
    }
  }
  else {
    if ((undefined1 *)(param_1 + param_3) < puVar4) {
      *puStack_f8 = param_1;
      *piStack_fc = (int)puVar4 - param_3;
      iStack_f4 = iStack_f4 + 1;
      puStack_f8 = puStack_f8 + 1;
      piStack_fc = piStack_fc + 1;
    }
    param_1 = (uint)puVar3;
    if (puVar3 < puStack_100) goto LAB_10005bf4;
  }
LAB_10005c15:
  iStack_f4 = iStack_f4 + -1;
  puStack_f8 = puStack_f8 + -1;
  piStack_fc = piStack_fc + -1;
  if (iStack_f4 < 0) {
    return;
  }
  puStack_100 = (undefined1 *)*piStack_fc;
  param_1 = (uint)*puStack_f8;
  goto LAB_10005bf4;
}
#undef aiStack_f0
#undef auStack_78
#undef iStack_f4
#undef piStack_fc
#undef puStack_100
#undef puStack_f8


/* ---- 0x10005d50  msvc_shortsort ---- */
/* MSVC 6 C runtime (qsort.c, static shortsort): selection sort of a short range for msvc_qsort */

void __cdecl msvc_shortsort(uint param_1,uint param_2,int param_3,void *param_4)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  
  for (; puVar2 = (undefined1 *)param_1, puVar1 = (undefined1 *)param_1, param_1 < param_2;
      param_2 = param_2 + -param_3) {
    while (puVar1 = puVar1 + param_3, puVar1 <= param_2) {
      iVar3 = (*(code *)param_4)(puVar1,puVar2);
      if (0 < iVar3) {
        puVar2 = puVar1;
      }
    }
    msvc_qsort_swap(puVar2,(undefined1 *)param_2,param_3);
  }
  return;
}

/* ---- 0x10005db0  msvc_qsort_swap ---- */
/* MSVC 6 C runtime (qsort.c, static swap): exchanges two elements byte by byte for msvc_qsort */

void __cdecl msvc_qsort_swap(undefined1 *param_1,undefined1 *param_2,int param_3)

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

