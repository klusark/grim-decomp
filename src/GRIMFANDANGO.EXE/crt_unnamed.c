/* GRIMFANDANGO.EXE :: crt_unnamed.c
 * functions 0x004ac690 .. 0x004d610b (314 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004ac690  FUN_004ac690 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004ac690(void)

{
  FUN_004ac6b0();
  UINT_008d0aa0 = (uint)FUN_004b05c0();
  FUN_004b0550();
  return;
}
#endif


/* ---- 0x004ac6b0  FUN_004ac6b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004ac6b0(void)

{
  PTR_FUN_004ed30c = FUN_004b0650;
  PTR_FUN_004ed308 = FUN_004b0ab0;
  PTR_FUN_004ed310 = FUN_004b06e0;
  PTR_FUN_004ed314 = FUN_004b05f0;
  PTR_FUN_004ed318 = FUN_004b06c0;
  PTR_FUN_004ed31c = FUN_004b0ab0;
  return;
}
#endif


/* ---- 0x004acb8d  FUN_004acb8d ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004acb8d(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  uVar1 = *(undefined4 *)**(undefined4 **)(unaff_EBP + -0x14);
  *(undefined4 *)(unaff_EBP + -0x68) = uVar1;
  FUN_004b0d30(uVar1,*(undefined4 **)(unaff_EBP + -0x14));
  return;
}
#endif


/* ---- 0x004acba2  FUN_004acba2 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

void FUN_004acba2(void)

{
  int iVar1;
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  iVar1 = *(int *)(unaff_EBP + -0x18);
  *(undefined4 *)(iVar1 + -4) = *(undefined4 *)(unaff_EBP + -0x68);
  *(undefined4 *)(iVar1 + -8) = 0x4acbae;
  ((code *)_exit)();
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return;
}
#endif


/* ---- 0x004acc10  FUN_004acc10 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004acc10(undefined4 param_1)

{
  if (UINT_008d0aac == 1) {
    _FF_MSGBANNER();
  }
  _NMSG_WRITE(param_1);
  ExitProcess(0xff);
  return;
}
#endif


/* ---- 0x004acd10  FUN_004acd10 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004acd10(void)

{
  if (PTR_FUN_004ed098 != (undefined *)0x0) {
    (*(code *)PTR_FUN_004ed098)();
  }
  _initterm(&DAT_004dd00c,&DAT_004dd020);
  _initterm(&DAT_004dd000,&DAT_004dd008);
  return;
}
#endif


/* ---- 0x004acf30  FUN_004acf30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004acf30(void)

{
  g_pOnExitBegin = (void **)malloc(0x80);
  if (g_pOnExitBegin == (void **)0x0) {
    _amsg_exit(0x18);
  }
  *g_pOnExitBegin = (void *)0x0;
  g_pOnExitEnd = g_pOnExitBegin;
  return;
}
#endif


/* ---- 0x004ad2b0  FUN_004ad2b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004ad2b0(void)

{
  time(&UINT_008d0af8);
  return;
}
#endif


/* ---- 0x004addf0  FUN_004addf0 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FUN_004addf0(void)

{
  unsigned char _frame[0x1010];  /* Ghidra stack frame, see tools/frame_locals.py */
  uint in_EAX;
  undefined1 *puVar1;
  uint local_res0;
  #define local_ffc (*(uint *)(_frame + (0x1010 - 0xffc)))
  #define local_4 (*(uint *)(_frame + (0x1010 - 0x4)))
  
  puVar1 = &STACK0X(0x00000004);
  for (; 0xfff < in_EAX; in_EAX = in_EAX - 0x1000) {
    puVar1 = puVar1 + -0x1000;
  }
  *(uint *)(puVar1 + (-4 - in_EAX)) = local_res0;
  return local_res0;
}
#undef local_4
#undef local_ffc

#endif


/* ---- 0x004adef0  FUN_004adef0 ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
short * FUN_004adef0(short *param_1,int param_2,undefined4 param_3)

{
  short sVar1;
  short *psVar2;
  
  if (param_2 < 1) {
    return (short *)0x0;
  }
  _lock_file(param_3);
  param_2 = param_2 + -1;
  psVar2 = param_1;
  if (param_2 != 0) {
    while( true ) {
      sVar1 = ((code *)FUN_004b4440)(param_3);
      if (sVar1 == -1) break;
      *psVar2 = sVar1;
      psVar2 = psVar2 + 1;
      if ((sVar1 == 10) || (param_2 = param_2 + -1, param_2 == 0)) goto LAB_004adf40;
    }
    if (psVar2 == param_1) {
      _unlock_file(param_3);
      return (short *)0x0;
    }
  }
LAB_004adf40:
  *psVar2 = 0;
  _unlock_file(param_3);
  return param_1;
}
#endif


/* ---- 0x004ae410  FUN_004ae410 ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint * FUN_004ae410(uint *param_1,uint *param_2,uint param_3)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  
  puVar5 = param_1;
  if (param_3 == 0) {
    return param_1;
  }
  do {
    if (((uint)puVar5 & 3) == 0) goto LAB_004ae43a;
    uVar4 = *puVar5;
    puVar5 = (uint *)((int)puVar5 + 1);
  } while ((byte)uVar4 != 0);
  goto LAB_004ae46b;
  while( true ) {
    if ((uVar4 & 0xff0000) == 0) {
      puVar6 = (uint *)((int)puVar6 + 2);
      goto LAB_004ae47b;
    }
    if ((uVar4 & 0xff000000) == 0) break;
LAB_004ae43a:
    do {
      puVar6 = puVar5;
      puVar5 = puVar6 + 1;
    } while (((*puVar6 ^ 0xffffffff ^ *puVar6 + 0x7efefeff) & 0x81010100) == 0);
    uVar4 = *puVar6;
    if ((char)uVar4 == '\0') goto LAB_004ae47b;
    if ((char)(uVar4 >> 8) == '\0') {
      puVar6 = (uint *)((int)puVar6 + 1);
      goto LAB_004ae47b;
    }
  }
LAB_004ae46b:
  puVar6 = (uint *)((int)puVar5 + -1);
LAB_004ae47b:
  if (((uint)param_2 & 3) == 0) {
    uVar3 = param_3 >> 2;
  }
  else {
    do {
      bVar1 = (byte)*param_2;
      uVar4 = (uint)bVar1;
      param_2 = (uint *)((int)param_2 + 1);
      if (bVar1 == 0) goto LAB_004ae4ca;
      *(byte *)puVar6 = bVar1;
      puVar6 = (uint *)((int)puVar6 + 1);
      param_3 = param_3 - 1;
      if (param_3 == 0) goto LAB_004ae4c0;
    } while (((uint)param_2 & 3) != 0);
    uVar3 = param_3 >> 2;
  }
  do {
    if (uVar3 == 0) {
      for (param_3 = param_3 & 3; param_3 != 0; param_3 = param_3 - 1) {
        uVar4 = *param_2;
        param_2 = (uint *)((int)param_2 + 1);
        *(byte *)puVar6 = (byte)uVar4;
        puVar6 = (uint *)((int)puVar6 + 1);
        if ((byte)uVar4 == 0) {
          return param_1;
        }
      }
LAB_004ae4c0:
      *(byte *)puVar6 = 0;
      return param_1;
    }
    uVar2 = *param_2;
    uVar4 = *param_2;
    param_2 = param_2 + 1;
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar4 == '\0') {
LAB_004ae4ca:
        *(byte *)puVar6 = (byte)uVar4;
        return param_1;
      }
      if ((char)(uVar4 >> 8) == '\0') {
        *(short *)puVar6 = (short)uVar4;
        return param_1;
      }
      if ((uVar4 & 0xff0000) == 0) {
        *(short *)puVar6 = (short)uVar4;
        *(byte *)((int)puVar6 + 2) = 0;
        return param_1;
      }
      if ((uVar4 & 0xff000000) == 0) {
        *puVar6 = uVar4;
        return param_1;
      }
    }
    *puVar6 = uVar4;
    puVar6 = puVar6 + 1;
    uVar3 = uVar3 - 1;
  } while( true );
}
#endif


/* ---- 0x004ae735  FUN_004ae735 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float __cdecl FUN_004ae735(void)

{
  float10 in_ST0;
  float10 in_ST1;
  
  if (ROUND(in_ST0) == in_ST0) {
    return (float)in_ST1;
  }
  return (float)in_ST1;
}
#endif


/* ---- 0x004aeb60  FUN_004aeb60 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004aeb60(void)

{
  _flushall(1);
  return;
}
#endif


/* ---- 0x004af340  FUN_004af340 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004af340(undefined4 param_1,code *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x004af345. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}
#endif


/* ---- 0x004af3f0  FUN_004af3f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined * FUN_004af3f0(uint param_1,uint param_2,int param_3,int param_4,int param_5)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined *puVar1;
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  local_8 = param_4 + 1;
  local_14 = (uint)FUN_004af450;
  local_10 = param_2;
  local_c = param_1;
  local_18 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_18;
  puVar1 = FUN_004b5c10(param_3,param_1,param_5);
  *unaff_FS_OFFSET = local_18;
  return puVar1;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_8
#undef local_c

#endif


/* ---- 0x004af450  FUN_004af450 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004af450(undefined4 param_1,int param_2,undefined4 param_3)

{
  __InternalCxxFrameHandler
            (param_1,*(undefined4 *)(param_2 + 0xc),param_3,0,*(undefined4 *)(param_2 + 8),
             *(undefined4 *)(param_2 + 0x10),param_2,0);
  return;
}
#endif


/* ---- 0x004af480  FUN_004af480 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4
FUN_004af480(undefined4 *param_1,uint param_2,uint param_3,undefined4 param_4,uint param_5,
            uint param_6,uint param_7)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[96] __attribute__((aligned(16)));  /* the original frame below the return address */
  int iVar1;
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x50 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x50 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x50 - 0x8)))
  
  local_c = (uint)(_stkneg + 92);
  local_10 = (uint)(_stkneg + 28);
  local_28 = (uint)FUN_004af550;
  local_24 = param_5;
  local_20 = param_2;
  local_1c = param_6;
  local_18 = param_7;
  local_8 = 0;
  local_14 = 0x4af51c;
  local_2c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_2c;
  local_34 = (uint)param_1;
  local_30 = param_3;
  iVar1 = ((code *)_getptd)(*param_1,&local_34);
  (**(code **)(iVar1 + 0x68))();
  if (local_8 == 0) {
    *unaff_FS_OFFSET = local_2c;
  }
  else {
    *(undefined4 *)local_2c = *(undefined4 *)*unaff_FS_OFFSET;
    *unaff_FS_OFFSET = local_2c;
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
#undef local_38
#undef local_8
#undef local_c

#endif


/* ---- 0x004af550  FUN_004af550 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004af550(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 4) & 0x66) != 0) {
    *(undefined4 *)(param_2 + 0x24) = 1;
    return 1;
  }
  __InternalCxxFrameHandler
            (param_1,*(undefined4 *)(param_2 + 0xc),param_3,0,*(undefined4 *)(param_2 + 8),
             *(undefined4 *)(param_2 + 0x10),*(undefined4 *)(param_2 + 0x14),1);
  if (*(int *)(param_2 + 0x24) == 0) {
    _UnwindNestedFrames(param_2,param_1);
  }
                    /* WARNING: Could not recover jumptable at 0x004af5c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(param_2 + 0x18))();
  return uVar1;
}
#endif


/* ---- 0x004af5e0  FUN_004af5e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_004af5e0(int param_1,int param_2,int param_3,uint *param_4,uint *param_5)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = *(int *)(param_1 + 0x10);
  uVar5 = *(uint *)(param_1 + 0xc);
  uVar3 = uVar5;
  uVar4 = uVar5;
  while (-1 < param_2) {
    if (uVar5 == 0xffffffff) {
      FUN_004b5cf0();
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
    FUN_004b5cf0();
  }
  return iVar2 + uVar5 * 0x14;
}
#undef local_4

#endif


/* ---- 0x004af72d  FUN_004af72d ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void __fastcall FUN_004af72d(uint param_1)

{
  uint in_EAX;
  uint unaff_EBP;
  
  UINT_004ed0d8 = param_1;
  UINT_004ed0d4 = in_EAX;
  UINT_004ed0dc = unaff_EBP;
  return;
}
#endif


/* ---- 0x004af7b0  FUN_004af7b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004af7b0(void)

{
  InitializeCriticalSection((int)PTR_DAT_004ed124);
  InitializeCriticalSection((int)PTR_DAT_004ed114);
  InitializeCriticalSection((int)PTR_DAT_004ed104);
  InitializeCriticalSection((int)PTR_DAT_004ed0e4);
  return;
}
#endif


/* ---- 0x004b0550  FUN_004b0550 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b0550(void)

{
  FUN_004b6f90(0x10000,0x30000);
  return;
}
#endif


/* ---- 0x004b0570  FUN_004b0570 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Removing unreachable block (ram,0x004b05b1) */

undefined4 FUN_004b0570(void)

{
  return 0;
}
#endif


/* ---- 0x004b05c0  FUN_004b05c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * FUN_004b05c0(void)

{
  int a1;
  code *pcVar1;
  undefined *puVar2;
  
  a1 = GetModuleHandleA(IMG_ADDR(0x004d8a84));
  if (a1 != 0) {
    pcVar1 = (code *)GetProcAddress(a1,IMG_ADDR(0x004d8a68));
    if (pcVar1 != (code *)0x0) {
      puVar2 = (undefined *)(*pcVar1)(0);
      return puVar2;
    }
  }
  puVar2 = (undefined *)FUN_004b0570();
  return puVar2;
}
#endif


/* ---- 0x004b05f0  FUN_004b05f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b05f0(char *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = tolower((int)*param_1);
  if (iVar3 != 0x65) {
    do {
      param_1 = param_1 + 1;
      if ((int)UINT_004ed52c < 2) {
        uVar4 = (byte)PTR_DAT_004ed320[*param_1 * 2] & 4;
      }
      else {
        uVar4 = _isctype((int)*param_1,4);
      }
    } while (uVar4 != 0);
  }
  cVar2 = *param_1;
  *param_1 = DAT_004ed530;
  do {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    *param_1 = cVar2;
    cVar2 = cVar1;
  } while (*param_1 != '\0');
  return;
}
#endif


/* ---- 0x004b0650  FUN_004b0650 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b0650(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  
  cVar1 = *param_1;
  while ((cVar1 != '\0' && (cVar1 != DAT_004ed530))) {
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
    if (*pcVar4 == DAT_004ed530) {
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


/* ---- 0x004b06c0  FUN_004b06c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b06c0(double *param_1)

{
  if (0.0 <= *param_1) {
    return 1;
  }
  return 0;
}
#endif


/* ---- 0x004b06e0  FUN_004b06e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b06e0(int param_1,undefined4 *param_2,undefined4 param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  if (param_1 != 0) {
    FUN_004b7580(&local_8,param_3);
    *param_2 = local_8;
    param_2[1] = local_4;
    return;
  }
  FUN_004b75c0(&param_3,param_3);
  *param_2 = param_3;
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004b0740  FUN_004b0740 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_004b0740(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_18 (*(undefined1 (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_004b76a0(*param_1,param_1[1],&local_28,local_18);
  FUN_004b7600((uint)(local_28 == 0x2d) + param_2 + (uint)(0 < param_3),param_3 + 1,&local_28);
  FUN_004b07c0(param_2,param_3,param_4,&local_28,0);
  return param_2;
}
#undef local_18
#undef local_28

#endif


/* ---- 0x004b07c0  FUN_004b07c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined1 * FUN_004b07c0(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5)

{
  undefined1 *puVar1;
  int iVar2;
  uint *puVar3;
  
  if (param_5 != '\0') {
    FUN_004b0b20(param_1 + (*param_4 == 0x2d),0 < param_2);
  }
  puVar1 = param_1;
  if (*param_4 == 0x2d) {
    *param_1 = 0x2d;
    puVar1 = param_1 + 1;
  }
  if (0 < param_2) {
    *puVar1 = puVar1[1];
    puVar1 = puVar1 + 1;
    *puVar1 = DAT_004ed530;
  }
  puVar3 = (uint *)(puVar1 + param_2 + (uint)(param_5 == '\0'));
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
    *(char *)(puVar3 + 1) = (char)puVar3[1] + (char)iVar2;
  }
  return param_1;
}
#endif


/* ---- 0x004b08c0  FUN_004b08c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_004b08c0(undefined4 *param_1,int param_2,int param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_18 (*(undefined1 (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_004b76a0(*param_1,param_1[1],&local_28,local_18);
  FUN_004b7600((uint)(local_28 == 0x2d) + param_2,local_24 + param_3,&local_28);
  FUN_004b0930(param_2,param_3,&local_28,0);
  return param_2;
}
#undef local_18
#undef local_24
#undef local_28

#endif


/* ---- 0x004b0930  FUN_004b0930 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined1 * FUN_004b0930(undefined1 *param_1,uint param_2,int *param_3,char param_4)

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
    FUN_004b0b20(puVar4,1);
    *puVar4 = 0x30;
    puVar4 = puVar4 + 1;
  }
  else {
    puVar4 = puVar4 + param_3[1];
  }
  if (0 < (int)param_2) {
    FUN_004b0b20(puVar4,1);
    *puVar4 = DAT_004ed530;
    iVar1 = param_3[1];
    if (iVar1 < 0) {
      if ((param_4 != '\0') || (-iVar1 <= (int)param_2)) {
        param_2 = -iVar1;
      }
      FUN_004b0b20(puVar4 + 1,param_2);
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


/* ---- 0x004b09f0  FUN_004b09f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b09f0(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  char cVar3;
  char *pcVar4;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_18 (*(undefined1 (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_004b76a0(*param_1,param_1[1],&local_28,local_18);
  iVar1 = local_24 - 1;
  pcVar4 = (char *)((uint)(local_28 == 0x2d) + param_2);
  FUN_004b7600(pcVar4,param_3,&local_28);
  iVar2 = local_24 - 1;
  if ((-5 < iVar2) && (iVar2 < param_3)) {
    if (iVar1 < iVar2) {
      cVar3 = *pcVar4;
      while (cVar3 != '\0') {
        cVar3 = pcVar4[1];
        pcVar4 = pcVar4 + 1;
      }
      pcVar4[-1] = '\0';
    }
    FUN_004b0930(param_2,param_3,&local_28,1);
    return;
  }
  FUN_004b07c0(param_2,param_3,param_4,&local_28,1);
  return;
}
#undef local_18
#undef local_24
#undef local_28

#endif


/* ---- 0x004b0ab0  FUN_004b0ab0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b0ab0(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                 undefined4 param_5)

{
  if ((param_3 != 0x65) && (param_3 != 0x45)) {
    if (param_3 == 0x66) {
      FUN_004b08c0(param_1,param_2,param_4);
      return;
    }
    FUN_004b09f0(param_1,param_2,param_4,param_5);
    return;
  }
  FUN_004b0740(param_1,param_2,param_4,param_5);
  return;
}
#endif


/* ---- 0x004b0b20  FUN_004b0b20 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b0b20(char *param_1,int param_2)

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
    memmove(param_1 + param_2,param_1,~uVar2);
  }
  return;
}
#endif


/* ---- 0x004b0c30  FUN_004b0c30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b0c30(void)

{
  int *a2;
  int iVar1;
  
  FUN_004af7b0();
  UINT_004ed540 = TlsAlloc();
  if (UINT_004ed540 != 0xffffffff) {
    a2 = (int *)calloc(1,0x74);
    if (a2 != (int *)0x0) {
      iVar1 = TlsSetValue(UINT_004ed540,(int)a2);
      if (iVar1 != 0) {
        _initptd(a2);
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


/* ---- 0x004b0d30  FUN_004b0d30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b0d30(undefined4 param_1,undefined4 param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar3 = _getptd();
  piVar4 = (int *)FUN_004b0f40(param_1,*(undefined4 *)(iVar3 + 0x50));
  if ((piVar4 == (int *)0x0) || (pcVar1 = (code *)piVar4[2], pcVar1 == (code *)0x0)) {
    uVar5 = UnhandledExceptionFilter(param_2);
    return uVar5;
  }
  if (pcVar1 == (code *)0x5) {
    piVar4[2] = 0;
    return 1;
  }
  if (pcVar1 == (code *)0x1) {
    return 0xffffffff;
  }
  uVar5 = *(undefined4 *)(iVar3 + 0x54);
  *(undefined4 *)(iVar3 + 0x54) = param_2;
  if (piVar4[1] != 8) {
    piVar4[2] = 0;
    (*pcVar1)(piVar4[1]);
    *(undefined4 *)(iVar3 + 0x54) = uVar5;
    return 0xffffffff;
  }
  if ((int)UINT_004ed5c0 < (int)(UINT_004ed5c4 + UINT_004ed5c0)) {
    iVar7 = UINT_004ed5c0 * 0xc;
    uVar6 = UINT_004ed5c0;
    do {
      uVar6 = uVar6 + 1;
      *(undefined4 *)(*(int *)(iVar3 + 0x50) + 8 + iVar7) = 0;
      iVar7 = iVar7 + 0xc;
    } while ((int)uVar6 < (int)(UINT_004ed5c4 + UINT_004ed5c0));
  }
  iVar7 = *piVar4;
  uVar2 = *(undefined4 *)(iVar3 + 0x58);
  if (iVar7 == -0x3fffff72) {
    *(undefined4 *)(iVar3 + 0x58) = 0x83;
    (*pcVar1)(8,*(undefined4 *)(iVar3 + 0x58));
    *(undefined4 *)(iVar3 + 0x58) = uVar2;
    *(undefined4 *)(iVar3 + 0x54) = uVar5;
    return 0xffffffff;
  }
  if (iVar7 == -0x3fffff70) {
    *(undefined4 *)(iVar3 + 0x58) = 0x81;
    (*pcVar1)(8,*(undefined4 *)(iVar3 + 0x58));
    *(undefined4 *)(iVar3 + 0x58) = uVar2;
    *(undefined4 *)(iVar3 + 0x54) = uVar5;
    return 0xffffffff;
  }
  if (iVar7 != -0x3fffff6f) {
    if (iVar7 == -0x3fffff6d) {
      *(undefined4 *)(iVar3 + 0x58) = 0x85;
      (*pcVar1)(8,*(undefined4 *)(iVar3 + 0x58));
      *(undefined4 *)(iVar3 + 0x58) = uVar2;
      *(undefined4 *)(iVar3 + 0x54) = uVar5;
      return 0xffffffff;
    }
    if (iVar7 != -0x3fffff73) {
      if (iVar7 != -0x3fffff71) {
        if (iVar7 == -0x3fffff6e) {
          *(undefined4 *)(iVar3 + 0x58) = 0x8a;
        }
        (*pcVar1)(8,*(undefined4 *)(iVar3 + 0x58));
        *(undefined4 *)(iVar3 + 0x58) = uVar2;
        *(undefined4 *)(iVar3 + 0x54) = uVar5;
        return 0xffffffff;
      }
      *(undefined4 *)(iVar3 + 0x58) = 0x86;
      (*pcVar1)(8,*(undefined4 *)(iVar3 + 0x58));
      *(undefined4 *)(iVar3 + 0x58) = uVar2;
      *(undefined4 *)(iVar3 + 0x54) = uVar5;
      return 0xffffffff;
    }
    *(undefined4 *)(iVar3 + 0x58) = 0x82;
    (*pcVar1)(8,*(undefined4 *)(iVar3 + 0x58));
    *(undefined4 *)(iVar3 + 0x58) = uVar2;
    *(undefined4 *)(iVar3 + 0x54) = uVar5;
    return 0xffffffff;
  }
  *(undefined4 *)(iVar3 + 0x58) = 0x84;
  (*pcVar1)(8,*(undefined4 *)(iVar3 + 0x58));
  *(undefined4 *)(iVar3 + 0x58) = uVar2;
  *(undefined4 *)(iVar3 + 0x54) = uVar5;
  return 0xffffffff;
}
#undef local_4

#endif


/* ---- 0x004b0f40  FUN_004b0f40 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int * FUN_004b0f40(int param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = param_2;
  if (*param_2 != param_1) {
    do {
      piVar1 = piVar1 + 3;
      if (param_2 + UINT_004ed5cc * 3 <= piVar1) break;
    } while (*piVar1 != param_1);
  }
  if ((param_2 + UINT_004ed5cc * 3 <= piVar1) || (*piVar1 != param_1)) {
    piVar1 = (int *)0x0;
  }
  return piVar1;
}
#endif


/* ---- 0x004b0f80  FUN_004b0f80 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined * __cdecl FUN_004b0f80(uint param_1)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)FUN_004b0fa0(param_1,0,4);
  return puVar1;
}
#endif


/* ---- 0x004b0fa0  FUN_004b0fa0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b0fa0(uint param_1,uint param_2,byte param_3)

{
  if ((*(byte *)((int)&UINT_008d0ca0 + (param_1 & 0xff) + 1) & param_3) == 0) {
    if (param_2 == 0) {
      param_2 = 0;
    }
    else {
      param_2 = *(ushort *)(&DAT_004ed32a + (param_1 & 0xff) * 2) & param_2;
    }
    if (param_2 == 0) {
      return 0;
    }
  }
  return 1;
}
#endif


/* ---- 0x004b0fe0  FUN_004b0fe0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b0fe0(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  int iVar9;
  char *pcVar10;
  char *pcVar11;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar9 = 0;
  cVar2 = *(char *)UINT_008d0aa4;
  pcVar8 = (char *)UINT_008d0aa4;
  while (cVar2 != '\0') {
    if (cVar2 != '=') {
      iVar9 = iVar9 + 1;
    }
    uVar5 = 0xffffffff;
    pcVar10 = pcVar8;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar2 = *pcVar10;
      pcVar10 = pcVar10 + 1;
    } while (cVar2 != '\0');
    pcVar10 = pcVar8 + ~uVar5;
    pcVar8 = pcVar8 + ~uVar5;
    cVar2 = *pcVar10;
  }
  puVar3 = (undefined4 *)malloc(iVar9 * 4 + 4);
  UINT_008d0ad0 = (uint)puVar3;
  if (puVar3 == (undefined4 *)0x0) {
    _amsg_exit(9);
  }
  cVar2 = *(char *)UINT_008d0aa4;
  local_4 = (uint)puVar3;
  pcVar8 = (char *)UINT_008d0aa4;
  do {
    if (cVar2 == '\0') {
      free(UINT_008d0aa4);
      UINT_008d0aa4 = 0;
      *puVar3 = 0;
      return;
    }
    uVar5 = 0xffffffff;
    pcVar10 = pcVar8;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar10 + 1;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    if (cVar2 != '=') {
      puVar4 = malloc(uVar5);
      *puVar3 = puVar4;
      if (puVar4 == (undefined *)0x0) {
        _amsg_exit(9);
      }
      uVar6 = 0xffffffff;
      pcVar10 = pcVar8;
      do {
        pcVar11 = pcVar10;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar10 + 1;
        cVar2 = *pcVar10;
        pcVar10 = pcVar11;
      } while (cVar2 != '\0');
      uVar6 = ~uVar6;
      pcVar10 = pcVar11 + -uVar6;
      pcVar11 = *(char **)local_4;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar11 = pcVar11 + 4;
      }
      puVar3 = (undefined4 *)(local_4 + 4);
      for (uVar6 = uVar6 & 3; local_4 = (uint)puVar3, uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar11 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar11 = pcVar11 + 1;
      }
    }
    cVar2 = pcVar8[uVar5];
    pcVar8 = pcVar8 + uVar5;
  } while( true );
}
#undef local_4

#endif


/* ---- 0x004b10d0  FUN_004b10d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004b10d0(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined *puVar1;
  undefined *puVar2;
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  GetModuleFileNameA(0,IMG_ADDR(0x008d0b90),0x104);
  _DAT_008d0ae0 = &DAT_008d0b90;
  puVar2 = (undefined *)UINT_00906c18;
  if (*(char *)UINT_00906c18 == '\0') {
    puVar2 = &DAT_008d0b90;
  }
  FUN_004b1170(puVar2,0,0,&iStack_8,&iStack_4);
  puVar1 = malloc(iStack_4 + iStack_8 * 4);
  if (puVar1 == (undefined *)0x0) {
    _amsg_exit(8);
  }
  FUN_004b1170(puVar2,puVar1,puVar1 + iStack_8 * 4,&iStack_8,&iStack_4);
  _DAT_008d0ac8 = puVar1;
  _DAT_008d0ac4 = iStack_8 + -1;
  return;
}
#undef iStack_4
#undef iStack_8

#endif


/* ---- 0x004b1170  FUN_004b1170 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b1170(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5)

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
      if (((*(byte *)((int)&UINT_008d0ca0 + bVar2 + 1) & 4) != 0) &&
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
      if ((*(byte *)((int)&UINT_008d0ca0 + (int)param_5 + 1U) & 4) != 0) {
        *piVar6 = *piVar6 + 1;
        if (param_3 != (byte *)0x0) {
          *param_3 = *pbVar7;
          param_3 = param_3 + 1;
        }
        pbVar7 = param_1 + 2;
      }
      if (bVar2 == 0x20) break;
      if (bVar2 == 0) goto LAB_004b1249;
      param_1 = pbVar7;
    } while (bVar2 != 9);
    if (bVar2 == 0) {
LAB_004b1249:
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
          if ((*(byte *)((int)&UINT_008d0ca0 + bVar2 + 1) & 4) != 0) {
            pbVar7 = pbVar7 + 1;
            *piVar6 = *piVar6 + 1;
          }
          *piVar6 = *piVar6 + 1;
          goto LAB_004b1345;
        }
        if ((*(byte *)((int)&UINT_008d0ca0 + bVar2 + 1) & 4) != 0) {
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
LAB_004b1345:
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


/* ---- 0x004b1380  FUN_004b1380 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
char * FUN_004b1380(void)

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
  if (UINT_008d0c98 == 0) {
    a3 = (short *)GetEnvironmentStringsW();
    if (a3 == (short *)0x0) {
      pcVar9 = (char *)GetEnvironmentStrings();
      if (pcVar9 == (char *)0x0) {
        return (char *)0x0;
      }
      UINT_008d0c98 = 2;
    }
    else {
      UINT_008d0c98 = 1;
    }
  }
  if (UINT_008d0c98 == 1) {
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
      if ((uVar6 != 0) && (pcVar9 = malloc(uVar6), pcVar9 != (char *)0x0)) {
        iVar5 = WideCharToMultiByte(0,0,(int)a3,iVar5,(int)pcVar9,uVar6,0,0);
        if (iVar5 == 0) {
          free(pcVar9);
          pcVar9 = (char *)0x0;
        }
        FreeEnvironmentStringsW((int)a3);
        return pcVar9;
      }
      FreeEnvironmentStringsW((int)a3);
      return (char *)0x0;
    }
  }
  else if ((UINT_008d0c98 == 2) &&
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
    pcVar8 = malloc((uint)pcVar7);
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
      FreeEnvironmentStringsA((int)pcVar9);
      return pcVar8;
    }
    FreeEnvironmentStringsA((int)pcVar9);
    return (char *)0x0;
  }
  return (char *)0x0;
}
#endif


/* ---- 0x004b14e0  FUN_004b14e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004b14e0(undefined4 param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  uint a1;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  byte *pbVar10;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define abStack_e (*(byte (*)[14])(_frame + (0x30 - 0xe)))
  
  _lock(0x19);
  a1 = FUN_004b1710(param_1);
  if (a1 == UINT_008d0ea8) {
    _unlock(0x19);
    return 0;
  }
  if (a1 == 0) {
    FUN_004b17c0();
    FUN_004b1800();
    _unlock(0x19);
    return 0;
  }
  iVar8 = 0;
  puVar4 = &UINT_004ed5d8;
  do {
    if (*puVar4 == a1) {
      puVar4 = &UINT_008d0ca0;
      for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
      *(undefined1 *)puVar4 = 0;
      uVar5 = 0;
      iVar8 = iVar8 * 0x30;
      pbVar9 = (byte *)(iVar8 + IMG_ADDR(0x004ed5e8));
      do {
        bVar2 = *pbVar9;
        for (pbVar10 = pbVar9; (bVar2 != 0 && (bVar2 = pbVar10[1], bVar2 != 0));
            pbVar10 = pbVar10 + 2) {
          uVar6 = (uint)*pbVar10;
          if (uVar6 <= bVar2) {
            bVar3 = (&DAT_004ed5d0)[uVar5];
            do {
              pbVar1 = (byte *)((int)&UINT_008d0ca0 + uVar6 + 1);
              *pbVar1 = *pbVar1 | bVar3;
              uVar6 = uVar6 + 1;
            } while (uVar6 <= bVar2);
          }
          bVar2 = pbVar10[2];
        }
        uVar5 = uVar5 + 1;
        pbVar9 = pbVar9 + 8;
      } while (uVar5 < 4);
      _DAT_00906c04 = 1;
      UINT_008d0ea8 = a1;
      UINT_008d0eac = FUN_004b1760(a1);
      _DAT_008d0eb0 = *(undefined4 *)(iVar8 + IMG_ADDR(0x004ed5dc));
      _DAT_008d0eb4 = *(undefined4 *)(iVar8 + IMG_ADDR(0x004ed5e0));
      _DAT_008d0eb8 = *(undefined4 *)(iVar8 + IMG_ADDR(0x004ed5e4));
      goto LAB_004b1632;
    }
    puVar4 = puVar4 + 0xc;
    iVar8 = iVar8 + 1;
  } while (puVar4 < &DAT_004ed6c8);
  iVar8 = GetCPInfo(a1,(int)&local_14);
  if (iVar8 == 1) {
    puVar4 = &UINT_008d0ca0;
    for (iVar8 = 0x40; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    *(undefined1 *)puVar4 = 0;
    UINT_008d0eac = 0;
    if (local_14 < 2) {
      _DAT_00906c04 = 0;
      UINT_008d0ea8 = a1;
    }
    else {
      UINT_008d0ea8 = a1;
      if (abStack_e[0] != 0) {
        pbVar9 = abStack_e + 1;
        do {
          bVar2 = *pbVar9;
          if (bVar2 == 0) break;
          for (uVar5 = (uint)pbVar9[-1]; uVar5 <= bVar2; uVar5 = uVar5 + 1) {
            *(byte *)((int)&UINT_008d0ca0 + uVar5 + 1) =
                 *(byte *)((int)&UINT_008d0ca0 + uVar5 + 1) | 4;
          }
          pbVar10 = pbVar9 + 1;
          pbVar9 = pbVar9 + 2;
        } while (*pbVar10 != 0);
      }
      uVar5 = 1;
      do {
        *(byte *)((int)&UINT_008d0ca0 + uVar5 + 1) = *(byte *)((int)&UINT_008d0ca0 + uVar5 + 1) | 8;
        uVar5 = uVar5 + 1;
      } while (uVar5 < 0xff);
      UINT_008d0eac = FUN_004b1760(a1);
      _DAT_00906c04 = 1;
    }
    _DAT_008d0eb0 = 0;
    _DAT_008d0eb4 = 0;
    _DAT_008d0eb8 = 0;
  }
  else {
    if (UINT_008d0ebc == 0) {
      _unlock(0x19);
      return 0xffffffff;
    }
    FUN_004b17c0();
  }
LAB_004b1632:
  FUN_004b1800();
  _unlock(0x19);
  return 0;
}
#undef abStack_e
#undef local_14

#endif


/* ---- 0x004b1710  FUN_004b1710 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004b1710(uint param_1)

{
  uint uVar1;
  bool bVar2;
  
  if (param_1 == 0xfffffffe) {
    UINT_008d0ebc = 1;
                    /* WARNING: Could not recover jumptable at 0x004b172d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = GetOEMCP();
    return uVar1;
  }
  if (param_1 == 0xfffffffd) {
    UINT_008d0ebc = 1;
                    /* WARNING: Could not recover jumptable at 0x004b1742. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = GetACP();
    return uVar1;
  }
  bVar2 = param_1 == 0xfffffffc;
  if (bVar2) {
    param_1 = UINT_008d0b80;
  }
  UINT_008d0ebc = (uint)bVar2;
  return param_1;
}
#endif


/* ---- 0x004b1760  FUN_004b1760 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b1760(undefined4 param_1)

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


/* ---- 0x004b17c0  FUN_004b17c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004b17c0(void)

{
  int iVar1;
  uint *puVar2;
  
  puVar2 = &UINT_008d0ca0;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  UINT_008d0ea8 = 0;
  _DAT_00906c04 = 0;
  UINT_008d0eac = 0;
  _DAT_008d0eb0 = 0;
  _DAT_008d0eb4 = 0;
  _DAT_008d0eb8 = 0;
  return;
}
#endif


/* ---- 0x004b1800  FUN_004b1800 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b1800(void)

{
  unsigned char _frame[0x530] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  ushort *puVar6;
  undefined4 *puVar7;
  #define local_514 (*(undefined1 (*)[6])(_frame + (0x530 - 0x514)))
  #define bStack_50e (*(byte *)(_frame + (0x530 - 0x50e)))
  #define abStack_50d (*(byte (*)[13])(_frame + (0x530 - 0x50d)))
  #define auStack_500 (*(undefined4 (*)[64])(_frame + (0x530 - 0x500)))
  #define auStack_400 (*(undefined1 (*)[256])(_frame + (0x530 - 0x400)))
  #define auStack_300 (*(undefined1 (*)[256])(_frame + (0x530 - 0x300)))
  #define auStack_200 (*(ushort (*)[256])(_frame + (0x530 - 0x200)))
  
  iVar1 = GetCPInfo(UINT_008d0ea8,(int)local_514);
  if (iVar1 == 1) {
    uVar2 = 0;
    do {
      *(char *)((int)auStack_500 + uVar2) = (char)uVar2;
      uVar2 = uVar2 + 1;
    } while (uVar2 < 0x100);
    auStack_500[0]._0_1_ = 0x20;
    if (bStack_50e != 0) {
      pbVar5 = abStack_50d;
      do {
        uVar2 = (uint)bStack_50e;
        if (uVar2 <= *pbVar5) {
          uVar3 = (*pbVar5 - uVar2) + 1;
          puVar7 = (undefined4 *)((int)auStack_500 + uVar2);
          for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
            *puVar7 = 0x20202020;
            puVar7 = puVar7 + 1;
          }
          for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
            *(undefined1 *)puVar7 = 0x20;
            puVar7 = (undefined4 *)((int)puVar7 + 1);
          }
        }
        bStack_50e = pbVar5[1];
        pbVar5 = pbVar5 + 2;
      } while (bStack_50e != 0);
    }
    __crtGetStringTypeA(1,auStack_500,0x100,auStack_200,UINT_008d0ea8,UINT_008d0eac,0);
    __crtLCMapStringA(UINT_008d0eac,0x100,auStack_500,0x100,auStack_400,0x100,UINT_008d0ea8,0);
    __crtLCMapStringA(UINT_008d0eac,0x200,auStack_500,0x100,auStack_300,0x100,UINT_008d0ea8,0);
    uVar2 = 0;
    puVar6 = auStack_200;
    do {
      if ((*puVar6 & 1) == 0) {
        if ((*puVar6 & 2) == 0) {
          (&DAT_008d0da8)[uVar2] = 0;
        }
        else {
          *(byte *)((int)&UINT_008d0ca0 + uVar2 + 1) =
               *(byte *)((int)&UINT_008d0ca0 + uVar2 + 1) | 0x20;
          (&DAT_008d0da8)[uVar2] = auStack_300[uVar2];
        }
      }
      else {
        *(byte *)((int)&UINT_008d0ca0 + uVar2 + 1) =
             *(byte *)((int)&UINT_008d0ca0 + uVar2 + 1) | 0x10;
        (&DAT_008d0da8)[uVar2] = auStack_400[uVar2];
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
        (&DAT_008d0da8)[uVar2] = 0;
      }
      else {
        *(byte *)((int)&UINT_008d0ca0 + uVar2 + 1) =
             *(byte *)((int)&UINT_008d0ca0 + uVar2 + 1) | 0x20;
        (&DAT_008d0da8)[uVar2] = (char)uVar2 + -0x20;
      }
    }
    else {
      *(byte *)((int)&UINT_008d0ca0 + uVar2 + 1) = *(byte *)((int)&UINT_008d0ca0 + uVar2 + 1) | 0x10
      ;
      (&DAT_008d0da8)[uVar2] = (char)uVar2 + ' ';
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x100);
  return;
}
#undef abStack_50d
#undef auStack_200
#undef auStack_300
#undef auStack_400
#undef auStack_500
#undef bStack_50e
#undef local_514

#endif


/* ---- 0x004b19e0  FUN_004b19e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b19e0(void)

{
  FUN_004b14e0(0xfffffffd);
  return;
}
#endif


/* ---- 0x004b19f0  FUN_004b19f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b19f0(void)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  uint *puVar7;
  uint uVar8;
  byte *pbVar9;
  #define local_48 (*(uint *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(undefined1 (*)[50])(_frame + (0x60 - 0x44)))
  #define local_12 (*(short *)(_frame + (0x60 - 0x12)))
  #define local_10 (*(uint *)(_frame + (0x60 - 0x10)))
  
  piVar2 = (int *)malloc(0x480);
  if (piVar2 == (int *)0x0) {
    _amsg_exit(0x1b);
  }
  UINT_00906c00 = 0x20;
  PTR_00906b00 = piVar2;
  if (piVar2 < piVar2 + 0x120) {
    do {
      *(undefined1 *)(piVar2 + 1) = 0;
      *piVar2 = -1;
      *(undefined1 *)((int)piVar2 + 5) = 10;
      piVar2[2] = 0;
      piVar2 = piVar2 + 9;
    } while (piVar2 < PTR_00906b00 + 0x120);
  }
  GetStartupInfoA((int)local_44);
  if ((local_12 != 0) && (local_10 != 0)) {
    local_48 = *(uint *)local_10;
    pbVar9 = (byte *)(local_10 + 4);
    pbVar6 = pbVar9 + local_48;
    if (0x7ff < (int)local_48) {
      local_48 = 0x800;
    }
    if ((int)UINT_00906c00 < (int)local_48) {
      puVar7 = &UINT_00906b04;
      do {
        puVar3 = (undefined4 *)malloc(0x480);
        if (puVar3 == (undefined4 *)0x0) {
          local_48 = UINT_00906c00;
          break;
        }
        *puVar7 = (uint)puVar3;
        UINT_00906c00 = UINT_00906c00 + 0x20;
        if (puVar3 < puVar3 + 0x120) {
          do {
            *(undefined1 *)(puVar3 + 1) = 0;
            *puVar3 = 0xffffffff;
            *(undefined1 *)((int)puVar3 + 5) = 10;
            puVar3[2] = 0;
            puVar3 = puVar3 + 9;
          } while (puVar3 < (undefined4 *)(*puVar7 + 0x480));
        }
        puVar7 = puVar7 + 1;
      } while ((int)UINT_00906c00 < (int)local_48);
    }
    uVar8 = 0;
    if (0 < (int)local_48) {
      do {
        if (((*(int *)pbVar6 != -1) && ((*pbVar9 & 1) != 0)) &&
           (((*pbVar9 & 8) != 0 || (iVar4 = GetFileType(*(int *)pbVar6), iVar4 != 0)))) {
          piVar2 = (&PTR_00906b00)[(int)uVar8 >> 5];
          piVar2[(uVar8 & 0x1f) * 9] = *(int *)pbVar6;
          *(byte *)(piVar2 + (uVar8 & 0x1f) * 9 + 1) = *pbVar9;
        }
        uVar8 = uVar8 + 1;
        pbVar9 = pbVar9 + 1;
        pbVar6 = pbVar6 + 4;
      } while ((int)uVar8 < (int)local_48);
    }
  }
  iVar4 = 0;
  do {
    piVar2 = PTR_00906b00 + iVar4 * 9;
    if (PTR_00906b00[iVar4 * 9] == -1) {
      *(undefined1 *)(piVar2 + 1) = 0x81;
      if (iVar4 == 0) {
        iVar5 = -10;
      }
      else {
        iVar5 = -0xb - (uint)(iVar4 != 1);
      }
      iVar5 = GetStdHandle(iVar5);
      if ((iVar5 == -1) || (uVar8 = GetFileType(iVar5), uVar8 == 0)) {
        bVar1 = *(byte *)(piVar2 + 1) | 0x40;
        goto LAB_004b1bde;
      }
      *piVar2 = iVar5;
      if ((uVar8 & 0xff) == 2) {
        bVar1 = *(byte *)(piVar2 + 1) | 0x40;
        goto LAB_004b1bde;
      }
      if ((uVar8 & 0xff) == 3) {
        bVar1 = *(byte *)(piVar2 + 1) | 8;
        goto LAB_004b1bde;
      }
    }
    else {
      bVar1 = *(byte *)(piVar2 + 1) | 0x80;
LAB_004b1bde:
      *(byte *)(piVar2 + 1) = bVar1;
    }
    iVar4 = iVar4 + 1;
    if (2 < iVar4) {
      SetHandleCount(UINT_00906c00);
      return;
    }
  } while( true );
}
#undef local_10
#undef local_12
#undef local_44
#undef local_48

#endif


/* ---- 0x004b1c00  FUN_004b1c00 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b1c00(void)

{
  int iVar1;
  
  UINT_00906ae4 = HeapCreate(0,0x1000,0);
  if (UINT_00906ae4 == 0) {
    return 0;
  }
  iVar1 = __sbh_alloc_new_region();
  if (iVar1 == 0) {
    HeapDestroy(UINT_00906ae4);
    return 0;
  }
  return 1;
}
#endif


/* ---- 0x004b1c48  FUN_004b1c48 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b1c48(int param_1,int param_2,undefined4 param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[32] __attribute__((aligned(16)));  /* the original frame below the return address */
  int iVar1;
  int extraout_ECX;
  undefined1 *puVar2;
  int iVar3;
  #define local_c (*(int *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  
  puVar2 = (_stkneg + 28);
  if ((*(uint *)(param_1 + 4) & 6) == 0) {
    local_c = param_1;
    local_8 = param_3;
    *(int **)(param_2 + -4) = &local_c;
    iVar1 = *(int *)(param_2 + 8);
    for (iVar3 = *(int *)(param_2 + 0xc); iVar3 != -1; iVar3 = *(int *)(iVar1 + iVar3 * 0xc)) {
      if (*(int *)(iVar1 + 4 + iVar3 * 0xc) != 0) {
        iVar1 = (**(code **)(iVar1 + 4 + iVar3 * 0xc))();
        param_2 = *(int *)(puVar2 + 0xc);
        if (iVar1 != 0) {
          if (iVar1 < 0) {
            return 0;
          }
          iVar1 = *(int *)(param_2 + 8);
          _global_unwind2(param_2);
          puVar2 = (undefined1 *)(param_2 + 0x10);
          _local_unwind2(param_2,iVar3);
          _NLG_Notify(1);
          *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(iVar1 + extraout_ECX * 4);
          (**(code **)(iVar1 + 8 + extraout_ECX * 4))();
        }
      }
      iVar1 = *(int *)(param_2 + 8);
    }
  }
  else {
    ((code *)_local_unwind2)(param_2,0xffffffff,(_stkneg + 28),(_stkneg + 28));
  }
  return 1;
}
#undef local_8
#undef local_c

#endif


/* ---- 0x004b2040  FUN_004b2040 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b2040(void)

{
  undefined **ppuVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  
  if (UINT_00906ae0 == 0) {
    UINT_00906ae0 = 0x200;
  }
  else if ((int)UINT_00906ae0 < 0x14) {
    UINT_00906ae0 = 0x14;
  }
  UINT_00905ac4 = calloc(UINT_00906ae0,4);
  if (UINT_00905ac4 == 0) {
    UINT_00906ae0 = 0x14;
    UINT_00905ac4 = calloc(0x14,4);
    if (UINT_00905ac4 == 0) {
      _amsg_exit(0x1a);
    }
  }
  iVar3 = 0;
  ppuVar1 = &PTR_DAT_004ed780;
  do {
    *(undefined ***)(UINT_00905ac4 + iVar3) = ppuVar1;
    ppuVar1 = ppuVar1 + 8;
    iVar3 = iVar3 + 4;
  } while ((int)ppuVar1 < IMG_ADDR(0x004eda00));
  uVar2 = 0;
  puVar4 = &UINT_004ed790;
  do {
    if (((&PTR_00906b00)[(int)uVar2 >> 5][(uVar2 & 0x1f) * 9] == -1) ||
       ((&PTR_00906b00)[(int)uVar2 >> 5][(uVar2 & 0x1f) * 9] == 0)) {
      *puVar4 = 0xffffffff;
    }
    puVar4 = puVar4 + 8;
    uVar2 = uVar2 + 1;
  } while ((int)puVar4 < IMG_ADDR(0x004ed7f0));
  return;
}
#endif


/* ---- 0x004b2100  FUN_004b2100 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b2100(void)

{
  FUN_004aeb60();
  if (DAT_008d0ae8 != '\0') {
    FUN_004b7c10();
    return;
  }
  return;
}
#endif


/* ---- 0x004b4440  FUN_004b4440 ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint __thiscall FUN_004b4440(undefined4 param_1,undefined4 *param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  puVar5 = param_2;
  local_4 = param_1;
  if ((*(byte *)(param_2 + 3) & 0x40) == 0) {
    uVar3 = param_2[4];
    if (uVar3 == 0xffffffff) {
      piVar2 = (int *)&DAT_004ed6c8;
    }
    else {
      piVar2 = (&PTR_00906b00)[(int)uVar3 >> 5] + (uVar3 & 0x1f) * 9;
    }
    if ((*(byte *)(piVar2 + 1) & 0x80) != 0) {
      iVar4 = param_2[1];
      uVar6 = 1;
      param_2[1] = iVar4 + -1;
      if (iVar4 + -1 < 0) {
        uVar3 = _filbuf(param_2);
      }
      else {
        uVar3 = (uint)*(byte *)*param_2;
        *param_2 = (byte *)*param_2 + 1;
      }
      if (uVar3 == 0xffffffff) {
        return 0xffffffff;
      }
      local_4 = CONCAT31(PIECE(local_4,1,3),(char)uVar3);
      if ((PTR_DAT_004ed320[(uVar3 & 0xff) * 2 + 1] & 0x80) != 0) {
        iVar4 = puVar5[1];
        puVar5[1] = iVar4 + -1;
        if (iVar4 + -1 < 0) {
          uVar3 = _filbuf(puVar5);
        }
        else {
          uVar3 = (uint)*(byte *)*puVar5;
          *puVar5 = (byte *)*puVar5 + 1;
        }
        if (uVar3 == 0xffffffff) {
          ungetc((int)(char)local_4,puVar5);
          return 0xffff;
        }
        PIECE(local_4,0,2) = CONCAT11((char)uVar3,(char)local_4);
        uVar6 = 2;
      }
      iVar4 = mbtowc(&param_2,&local_4,uVar6);
      if (iVar4 == -1) {
        puVar5 = (undefined4 *)_errno();
        *puVar5 = 0x2a;
        return 0xffff;
      }
      return (uint)param_2 & 0xffff;
    }
  }
  iVar4 = param_2[1];
  param_2[1] = iVar4 + -2;
  if (-1 < iVar4 + -2) {
    uVar1 = *(ushort *)*param_2;
    *param_2 = (ushort *)*param_2 + 1;
    return (uint)uVar1;
  }
  uVar3 = _filwbuf(param_2);
  return uVar3;
}
#undef local_4

#endif


/* ---- 0x004b4ad4  FUN_004b4ad4 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 FUN_004b4ad4(void)

{
  return (float10)0;
}
#endif


/* ---- 0x004b4b0d  FUN_004b4b0d ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 FUN_004b4b0d(void)

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


/* ---- 0x004b4b0f  FUN_004b4b0f ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 FUN_004b4b0f(void)

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


/* ---- 0x004b4c00  FUN_004b4c00 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
unkbyte10 FUN_004b4c00(void)

{
  float10 in_ST0;
  float10 fVar1;
  unkbyte10 Var2;
  
  fVar1 = (float10)f2xm1(-(ROUND(in_ST0) - in_ST0));
  Var2 = fscale((float10)1 + fVar1,ROUND(in_ST0));
  return Var2;
}
#endif


/* ---- 0x004b4c15  FUN_004b4c15 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * FUN_004b4c15(void)

{
  undefined *in_EAX;
  
  return in_EAX;
}
#endif


/* ---- 0x004b4c45  FUN_004b4c45 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint __fastcall FUN_004b4c45(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_2 + 4) & 0x7ff00000;
  if (uVar1 != 0x7ff00000) {
    return uVar1;
  }
  return *(uint *)(param_2 + 4);
}
#endif


/* ---- 0x004b4c9e  FUN_004b4c9e ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * FUN_004b4c9e(void)

{
  undefined *in_EAX;
  
  return in_EAX;
}
#endif


/* ---- 0x004b4ce9  FUN_004b4ce9 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined * __fastcall FUN_004b4ce9(uint param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined2 uVar2;
  undefined *puVar1;
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
  else {
    uVar2 = (undefined2)((uStack_4 & 0x7ff00000) >> 0x10);
    puVar1 = (undefined *)CONCAT22(uVar2,unaff_retaddr);
    if (((unaff_retaddr == 0x27f) ||
        (puVar1 = (undefined *)(CONCAT22(uVar2,unaff_retaddr) & 0xffff0020),
        (unaff_retaddr & 0x20) != 0)) ||
       (puVar1 = (undefined *)
                 (CONCAT22((short)((uint)puVar1 >> 0x10),in_FPUStatusWord) & 0xffff0020),
       (in_FPUStatusWord & 0x20) == 0)) {
      return puVar1;
    }
  }
  if (param_2 == 0x1d) {
    puVar1 = (undefined *)((code *)_pow_except1)();
    return puVar1;
  }
  puVar1 = (undefined *)((code *)_pow_except2)();
  return puVar1;
}
#undef uStack_4

#endif


/* ---- 0x004b56c6  FUN_004b56c6 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b56c6(void)

{
  int unaff_EBP;
  
  FUN_004b5710(*(undefined4 *)(unaff_EBP + -0x14));
  return;
}
#endif


/* ---- 0x004b56d3  FUN_004b56d3 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

void FUN_004b56d3(void)

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
      *(undefined4 *)(iVar2 + -4) = 0x4b5696;
      FUN_004b5cf0();
    }
    *(undefined4 *)(unaff_EBP + -4) = 0;
    iVar1 = *(int *)(*(int *)(iVar3 + 8) + 4 + iVar5 * 8);
    if (iVar1 != 0) {
      *(undefined4 *)(iVar2 + -4) = 0x103;
      *(int *)(iVar2 + -8) = iVar4;
      *(int *)(iVar2 + -0xc) = iVar1;
      *(undefined4 *)(iVar2 + -0x10) = 0x4b56b4;
      FUN_004b5c10(*(int *)(iVar2 + -0xc),*(int *)(iVar2 + -8),*(int *)(iVar2 + -4));
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


/* ---- 0x004b5710  FUN_004b5710 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b5710(undefined4 *param_1)

{
  if (*(int *)*param_1 == -0x1f928c9d) {
    terminate();
  }
  return 0;
}
#endif


/* ---- 0x004b5884  FUN_004b5884 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

undefined4 FUN_004b5884(void)

{
  int iVar1;
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  iVar1 = *(int *)(unaff_EBP + -0x18);
  *(undefined4 *)(unaff_EBP + -0x2c) = 0;
  *(undefined4 *)(iVar1 + -4) = 0xffffffff;
  *(int *)(iVar1 + -8) = unaff_EBP + -0x10;
  *(undefined4 *)(iVar1 + -0xc) = 0x4b5899;
  ((code *)_local_unwind2)();
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return 0;
}
#endif


/* ---- 0x004b58af  FUN_004b58af ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b58af(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int unaff_EBP;
  
  piVar1 = *(int **)(unaff_EBP + 8);
  iVar2 = *(int *)(unaff_EBP + -0x2c);
  *(undefined4 *)(*(int *)(unaff_EBP + 0xc) + -4) = *(undefined4 *)(unaff_EBP + -0x28);
  iVar3 = _getptd();
  *(undefined4 *)(iVar3 + 0x6c) = *(undefined4 *)(unaff_EBP + -0x1c);
  iVar3 = _getptd();
  *(undefined4 *)(iVar3 + 0x70) = *(undefined4 *)(unaff_EBP + -0x20);
  if ((((*piVar1 == -0x1f928c9d) && (piVar1[4] == 3)) && (piVar1[5] == 0x19930520)) &&
     ((*(int *)(unaff_EBP + -0x24) == 0 && (iVar2 != 0)))) {
    uVar4 = _unwind_handler();
    ((code *)FUN_004b5b60)(piVar1,uVar4);
  }
  return;
}
#endif


/* ---- 0x004b5b60  FUN_004b5b60 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b5b60(int param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define pcStack_10 (*(code **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_004d8e28;
  pcStack_10 = FUN_004b1c48;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_14;
  if ((param_1 != 0) && (iVar1 = *(int *)(*(int *)(param_1 + 0x1c) + 4), iVar1 != 0)) {
    local_8 = 0;
    FUN_004af340(*(undefined4 *)(param_1 + 0x18),iVar1);
  }
  *unaff_FS_OFFSET = local_14;
  return;
}
#undef local_14
#undef local_1c
#undef local_8
#undef pcStack_10
#undef puStack_c

#endif


/* ---- 0x004b5baa  FUN_004b5baa ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_004b5baa(void)

{
  int unaff_EBP;
  
  return *(char *)(unaff_EBP + 0xc) != '\0';
}
#endif


/* ---- 0x004b5bb5  FUN_004b5bb5 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

void FUN_004b5bb5(void)

{
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  *(undefined4 *)(*(int *)(unaff_EBP + -0x18) + -4) = 0x4b5bbd;
  terminate();
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return;
}
#endif


/* ---- 0x004b5be0  FUN_004b5be0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_004b5be0(int param_1,int *param_2)

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


/* ---- 0x004b5c10  FUN_004b5c10 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined * __stdcall FUN_004b5c10(int a1,int a2,int a3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  code *extraout_EAX;
  undefined *extraout_EAX_00;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  FUN_004af72d(a3);
  (*extraout_EAX)();
  if (a3 == 0x100) {
    a3 = 2;
  }
  FUN_004af72d(a3);
  return extraout_EAX_00;
}
#undef local_8

#endif


/* ---- 0x004b5caa  FUN_004b5caa ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b5caa(void)

{
  return 1;
}
#endif


/* ---- 0x004b5cb0  FUN_004b5cb0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

void FUN_004b5cb0(void)

{
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  *(undefined4 *)(unaff_EBP + -4) = 0;
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *(undefined4 *)(*(int *)(unaff_EBP + -0x18) + -4) = 0x4b5cc6;
  FUN_004b5cd7();
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return;
}
#endif


/* ---- 0x004b5cd7  FUN_004b5cd7 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b5cd7(void)

{
  abort();
  return;
}
#endif


/* ---- 0x004b5cf0  FUN_004b5cf0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b5cf0(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define pcStack_10 (*(code **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_004d8e50;
  pcStack_10 = FUN_004b1c48;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_14;
  if (PTR_terminate_004efc40 != (undefined *)0x0) {
    local_8 = 1;
    (*(code *)PTR_terminate_004efc40)();
  }
  local_8 = 0xffffffff;
  FUN_004b5d5e();
  *unaff_FS_OFFSET = local_14;
  return;
}
#undef local_14
#undef local_1c
#undef local_8
#undef pcStack_10
#undef puStack_c

#endif


/* ---- 0x004b5d5e  FUN_004b5d5e ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b5d5e(void)

{
  terminate();
  return;
}
#endif


/* ---- 0x004b5d80  FUN_004b5d80 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b5d80(void)

{
  undefined *puVar1;
  int iVar2;
  
  if (UINT_008d0b7c == 0) {
    PTR_PTR_004f0764 = (undefined *)&PTR_DAT_004f06b8;
    FUN_004b61b0(UINT_008d0ee8);
    free(UINT_008d0ee8);
    UINT_008d0ee8 = 0;
    return 0;
  }
  puVar1 = (undefined *)calloc(1,0xac);
  if (puVar1 == (undefined *)0x0) {
    return 1;
  }
  iVar2 = FUN_004b5e30(puVar1);
  if (iVar2 != 0) {
    FUN_004b61b0(puVar1);
    free(puVar1);
    return 1;
  }
  PTR_PTR_004f0764 = puVar1;
  FUN_004b61b0(UINT_008d0ee8);
  free(UINT_008d0ee8);
  UINT_008d0ee8 = (uint)puVar1;
  return 0;
}
#endif


/* ---- 0x004b5e30  FUN_004b5e30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004b5e30(int param_1)

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
  
  uVar2 = DAT_008d0f28;
  uVar1 = DAT_008d0f26;
  if (param_1 == 0) {
    return 0xffffffff;
  }
  uVar3 = FUN_004ba340(1,DAT_008d0f26,0x31,param_1 + 4);
  uVar4 = FUN_004ba340(1,uVar1,0x32,param_1 + 8);
  uVar5 = FUN_004ba340(1,uVar1,0x33,param_1 + 0xc);
  uVar6 = FUN_004ba340(1,uVar1,0x34,param_1 + 0x10);
  uVar7 = FUN_004ba340(1,uVar1,0x35,param_1 + 0x14);
  uVar8 = FUN_004ba340(1,uVar1,0x36,param_1 + 0x18);
  uVar9 = FUN_004ba340(1,uVar1,0x37,param_1);
  uVar10 = FUN_004ba340(1,uVar1,0x2a,param_1 + 0x20);
  uVar11 = FUN_004ba340(1,uVar1,0x2b,param_1 + 0x24);
  uVar12 = FUN_004ba340(1,uVar1,0x2c,param_1 + 0x28);
  uVar13 = FUN_004ba340(1,uVar1,0x2d,param_1 + 0x2c);
  uVar14 = FUN_004ba340(1,uVar1,0x2e,param_1 + 0x30);
  uVar15 = FUN_004ba340(1,uVar1,0x2f,param_1 + 0x34);
  uVar16 = FUN_004ba340(1,uVar1,0x30,param_1 + 0x1c);
  uVar17 = FUN_004ba340(1,uVar1,0x44,param_1 + 0x38);
  uVar18 = FUN_004ba340(1,uVar1,0x45,param_1 + 0x3c);
  uVar19 = FUN_004ba340(1,uVar1,0x46,param_1 + 0x40);
  uVar20 = FUN_004ba340(1,uVar1,0x47,param_1 + 0x44);
  uVar21 = FUN_004ba340(1,uVar1,0x48,param_1 + 0x48);
  uVar22 = FUN_004ba340(1,uVar1,0x49,param_1 + 0x4c);
  uVar23 = FUN_004ba340(1,uVar1,0x4a,param_1 + 0x50);
  uVar24 = FUN_004ba340(1,uVar1,0x4b,param_1 + 0x54);
  uVar25 = FUN_004ba340(1,uVar1,0x4c,param_1 + 0x58);
  uVar26 = FUN_004ba340(1,uVar1,0x4d,param_1 + 0x5c);
  uVar27 = FUN_004ba340(1,uVar1,0x4e,param_1 + 0x60);
  uVar28 = FUN_004ba340(1,uVar1,0x4f,param_1 + 100);
  uVar29 = FUN_004ba340(1,uVar1,0x38,param_1 + 0x68);
  uVar30 = FUN_004ba340(1,uVar1,0x39,param_1 + 0x6c);
  uVar31 = FUN_004ba340(1,uVar1,0x3a,param_1 + 0x70);
  uVar32 = FUN_004ba340(1,uVar1,0x3b,param_1 + 0x74);
  uVar33 = FUN_004ba340(1,uVar1,0x3c,param_1 + 0x78);
  uVar34 = FUN_004ba340(1,uVar1,0x3d,param_1 + 0x7c);
  uVar35 = FUN_004ba340(1,uVar1,0x3e,param_1 + 0x80);
  uVar36 = FUN_004ba340(1,uVar1,0x3f,param_1 + 0x84);
  uVar37 = FUN_004ba340(1,uVar1,0x40,param_1 + 0x88);
  uVar38 = FUN_004ba340(1,uVar1,0x41,param_1 + 0x8c);
  uVar39 = FUN_004ba340(1,uVar1,0x42,param_1 + 0x90);
  uVar40 = FUN_004ba340(1,uVar1,0x43,param_1 + 0x94);
  uVar41 = FUN_004ba340(1,uVar1,0x28,param_1 + 0x98);
  uVar42 = FUN_004ba340(1,uVar1,0x29,param_1 + 0x9c);
  uVar43 = FUN_004ba340(1,uVar2,0x1f,param_1 + 0xa0);
  uVar44 = FUN_004ba340(1,uVar2,0x20,param_1 + 0xa4);
  uVar45 = FUN_004b63f0(uVar2,param_1);
  return uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10 | uVar11 | uVar12 | uVar13 |
         uVar14 | uVar15 | uVar16 | uVar17 | uVar18 | uVar19 | uVar20 | uVar21 | uVar22 | uVar23 |
         uVar24 | uVar25 | uVar26 | uVar27 | uVar28 | uVar29 | uVar30 | uVar31 | uVar32 | uVar33 |
         uVar34 | uVar35 | uVar36 | uVar37 | uVar38 | uVar39 | uVar40 | uVar41 | uVar42 | uVar43 |
         uVar44 | uVar45;
}
#endif


/* ---- 0x004b61b0  FUN_004b61b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b61b0(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    free(param_1[1]);
    free(param_1[2]);
    free(param_1[3]);
    free(param_1[4]);
    free(param_1[5]);
    free(param_1[6]);
    free(*param_1);
    free(param_1[8]);
    free(param_1[9]);
    free(param_1[10]);
    free(param_1[0xb]);
    free(param_1[0xc]);
    free(param_1[0xd]);
    free(param_1[7]);
    free(param_1[0xe]);
    free(param_1[0xf]);
    free(param_1[0x10]);
    free(param_1[0x11]);
    free(param_1[0x12]);
    free(param_1[0x13]);
    free(param_1[0x14]);
    free(param_1[0x15]);
    free(param_1[0x16]);
    free(param_1[0x17]);
    free(param_1[0x18]);
    free(param_1[0x19]);
    free(param_1[0x1a]);
    free(param_1[0x1b]);
    free(param_1[0x1c]);
    free(param_1[0x1d]);
    free(param_1[0x1e]);
    free(param_1[0x1f]);
    free(param_1[0x20]);
    free(param_1[0x21]);
    free(param_1[0x22]);
    free(param_1[0x23]);
    free(param_1[0x24]);
    free(param_1[0x25]);
    free(param_1[0x26]);
    free(param_1[0x27]);
    free(param_1[0x28]);
    free(param_1[0x29]);
    free(param_1[0x2a]);
  }
  return;
}
#endif


/* ---- 0x004b63f0  FUN_004b63f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004b63f0(char *param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *pcVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined *puVar6;
  char *pcVar7;
  char *pcVar8;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pcVar7 = param_1;
  local_4 = 0;
  local_8 = 0;
  uVar3 = FUN_004ba340(0,param_1,0x23,&local_4);
  uVar4 = FUN_004ba340(0,pcVar7,0x25,&local_8);
  uVar5 = FUN_004ba340(1,pcVar7,0x1e,&param_1);
  uVar5 = uVar3 | uVar4 | uVar5;
  if (uVar5 != 0) {
    return uVar5;
  }
  puVar6 = malloc(0xd);
  *(undefined **)(param_2 + 0xa8) = puVar6;
  if (local_4 == 0) {
    *puVar6 = 0x68;
    pcVar7 = puVar6 + 1;
    if (local_8 == 0) goto LAB_004b648c;
    *pcVar7 = 'h';
  }
  else {
    *puVar6 = 0x48;
    pcVar7 = puVar6 + 1;
    if (local_8 == 0) goto LAB_004b648c;
    *pcVar7 = 'H';
  }
  pcVar7 = puVar6 + 2;
LAB_004b648c:
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
  if (local_8 != 0) {
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
#undef local_4
#undef local_8

#endif


/* ---- 0x004b64f0  FUN_004b64f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004b64f0(void)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  
  uVar1 = DAT_008d0f22;
  if (UINT_008d0b78 == 0) {
    free(UINT_008d0eec);
    free(UINT_008d0ef0);
    free(UINT_008d0ef4);
    UINT_008d0eec = 0;
    UINT_008d0ef0 = 0;
    UINT_008d0ef4 = 0;
    puVar5 = malloc(2);
    *(undefined **)PTR_PTR_004f07a0 = puVar5;
    if (*(undefined2 **)PTR_PTR_004f07a0 == (undefined2 *)0x0) {
      return 0xffffffff;
    }
    **(undefined2 **)PTR_PTR_004f07a0 = DAT_004e793c;
    puVar5 = malloc(2);
    *(undefined **)(PTR_PTR_004f07a0 + 4) = puVar5;
    if (*(undefined1 **)(PTR_PTR_004f07a0 + 4) == (undefined1 *)0x0) {
      return 0xffffffff;
    }
    **(undefined1 **)(PTR_PTR_004f07a0 + 4) = 0;
    puVar5 = malloc(2);
    *(undefined **)(PTR_PTR_004f07a0 + 8) = puVar5;
    if (*(undefined1 **)(PTR_PTR_004f07a0 + 8) == (undefined1 *)0x0) {
      return 0xffffffff;
    }
    **(undefined1 **)(PTR_PTR_004f07a0 + 8) = 0;
  }
  else {
    iVar2 = FUN_004ba340(1,DAT_008d0f22,0xe,&UINT_008d0eec);
    iVar3 = FUN_004ba340(1,uVar1,0xf,&UINT_008d0ef0);
    iVar4 = FUN_004ba340(1,uVar1,0x10,&UINT_008d0ef4);
    FUN_004b66f0(UINT_008d0ef4);
    if ((iVar2 != 0 || iVar3 != 0) || iVar4 != 0) {
      free(UINT_008d0eec);
      free(UINT_008d0ef0);
      free(UINT_008d0ef4);
      UINT_008d0eec = 0;
      UINT_008d0ef0 = 0;
      UINT_008d0ef4 = 0;
      return 0xffffffff;
    }
    if (*(undefined **)PTR_PTR_004f07a0 != &DAT_004f0768) {
      free(*(undefined **)PTR_PTR_004f07a0);
      free(*(undefined4 *)(PTR_PTR_004f07a0 + 4));
      free(*(undefined4 *)(PTR_PTR_004f07a0 + 8));
    }
    *(uint *)PTR_PTR_004f07a0 = UINT_008d0eec;
    *(uint *)(PTR_PTR_004f07a0 + 4) = UINT_008d0ef0;
    *(uint *)(PTR_PTR_004f07a0 + 8) = UINT_008d0ef4;
  }
  _DAT_004ed534 = 1;
  DAT_004ed530 = **(undefined1 **)PTR_PTR_004f07a0;
  return 0;
}
#endif


/* ---- 0x004b66f0  FUN_004b66f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b66f0(char *param_1)

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
      if (cVar2 != ';') goto LAB_004b6706;
      do {
        *pcVar3 = pcVar3[1];
        pcVar1 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
      } while (*pcVar1 != '\0');
    }
    else {
      *param_1 = cVar2 + -0x30;
LAB_004b6706:
      param_1 = param_1 + 1;
    }
    cVar2 = *param_1;
  } while( true );
}
#endif


/* ---- 0x004b6730  FUN_004b6730 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b6730(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (UINT_008d0b74 == 0) {
    PTR_DAT_004f0770 = *(undefined **)PTR_PTR_004f07a0;
    PTR_DAT_004f0774 = *(undefined **)(PTR_PTR_004f07a0 + 4);
    PTR_DAT_004f0778 = *(undefined **)(PTR_PTR_004f07a0 + 8);
    PTR_PTR_004f07a0 = (undefined *)&PTR_DAT_004f0770;
    FUN_004b6970(UINT_008d0ef8);
    free(UINT_008d0ef8);
    UINT_008d0ef8 = 0;
    return 0;
  }
  puVar1 = (undefined4 *)calloc(1,0x30);
  if (puVar1 == (undefined4 *)0x0) {
    return 1;
  }
  iVar2 = FUN_004b6820(puVar1);
  if (iVar2 != 0) {
    FUN_004b6970(puVar1);
    free(puVar1);
    return 1;
  }
  *puVar1 = *(undefined4 *)PTR_PTR_004f07a0;
  puVar1[1] = *(undefined4 *)(PTR_PTR_004f07a0 + 4);
  puVar1[2] = *(undefined4 *)(PTR_PTR_004f07a0 + 8);
  PTR_PTR_004f07a0 = (undefined *)puVar1;
  FUN_004b6970(UINT_008d0ef8);
  free(UINT_008d0ef8);
  UINT_008d0ef8 = (uint)puVar1;
  return 0;
}
#endif


/* ---- 0x004b6820  FUN_004b6820 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004b6820(int param_1)

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
  
  uVar1 = DAT_008d0f1c;
  if (param_1 == 0) {
    return 0xffffffff;
  }
  uVar2 = FUN_004ba340(1,DAT_008d0f1c,0x15,param_1 + 0xc);
  uVar3 = FUN_004ba340(1,uVar1,0x14,param_1 + 0x10);
  uVar4 = FUN_004ba340(1,uVar1,0x16,param_1 + 0x14);
  uVar5 = FUN_004ba340(1,uVar1,0x17,param_1 + 0x18);
  uVar6 = FUN_004ba340(1,uVar1,0x18,(undefined4 *)(param_1 + 0x1c));
  FUN_004b66f0(*(undefined4 *)(param_1 + 0x1c));
  uVar7 = FUN_004ba340(1,uVar1,0x50,param_1 + 0x20);
  uVar8 = FUN_004ba340(1,uVar1,0x51,param_1 + 0x24);
  uVar9 = FUN_004ba340(0,uVar1,0x1a,param_1 + 0x28);
  uVar10 = FUN_004ba340(0,uVar1,0x19,param_1 + 0x29);
  uVar11 = FUN_004ba340(0,uVar1,0x54,param_1 + 0x2a);
  uVar12 = FUN_004ba340(0,uVar1,0x55,param_1 + 0x2b);
  uVar13 = FUN_004ba340(0,uVar1,0x56,param_1 + 0x2c);
  uVar14 = FUN_004ba340(0,uVar1,0x57,param_1 + 0x2d);
  uVar15 = FUN_004ba340(0,uVar1,0x52,param_1 + 0x2e);
  uVar16 = FUN_004ba340(0,uVar1,0x53,param_1 + 0x2f);
  return uVar2 | uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10 | uVar11 | uVar12 |
         uVar13 | uVar14 | uVar15 | uVar16;
}
#endif


/* ---- 0x004b6970  FUN_004b6970 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b6970(int param_1)

{
  if ((param_1 != 0) && (*(undefined **)(param_1 + 0xc) != &DAT_008d1040)) {
    free(*(undefined **)(param_1 + 0xc));
    free(*(undefined4 *)(param_1 + 0x10));
    free(*(undefined4 *)(param_1 + 0x14));
    free(*(undefined4 *)(param_1 + 0x18));
    free(*(undefined4 *)(param_1 + 0x1c));
    free(*(undefined4 *)(param_1 + 0x20));
    free(*(undefined4 *)(param_1 + 0x24));
  }
  return;
}
#endif


/* ---- 0x004b69e0  FUN_004b69e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b69e0(void)

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
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_e (*(byte (*)[14])(_frame + (0x30 - 0xe)))
  
  puVar9 = (undefined *)0x0;
  puVar8 = (undefined2 *)0x0;
  if (UINT_008d0b70 == 0) {
    PTR_DAT_004ed320 = &DAT_004ed32a;
    PTR_DAT_004ed324 = &DAT_004ed32a;
    free(UINT_008d0efc);
    free(UINT_008d0f00);
    UINT_008d0efc = 0;
    UINT_008d0f00 = 0;
    return 0;
  }
  if ((UINT_008d0b80 != 0) || (iVar3 = FUN_004ba340(0,DAT_008d0f14,0xb,&UINT_008d0b80), iVar3 == 0))
  {
    local_18 = (uint)malloc(0x202);
    local_1c = (uint)malloc(0x202);
    puVar9 = malloc(0x101);
    puVar8 = (undefined2 *)malloc(0x202);
    if (((undefined2 *)local_18 != (undefined2 *)0x0) &&
       ((((undefined2 *)local_1c != (undefined2 *)0x0 && (puVar9 != (undefined *)0x0)) &&
        (puVar8 != (undefined2 *)0x0)))) {
      iVar3 = 0;
      do {
        puVar9[iVar3] = (char)iVar3;
        iVar3 = iVar3 + 1;
      } while (iVar3 < 0x100);
      iVar3 = GetCPInfo(UINT_008d0b80,(int)&local_14);
      if ((iVar3 != 0) && (local_14 < 3)) {
        UINT_004ed52c = local_14 & 0xffff;
        if ((1 < UINT_004ed52c) && (local_e[0] != 0)) {
          pbVar5 = local_e + 1;
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
        puVar2 = (undefined2 *)(local_18 + 2);
        iVar3 = __crtGetStringTypeA(1,puVar9,0x100,puVar2,0,0,0);
        if (iVar3 != 0) {
          *(undefined2 *)local_18 = 0;
          iVar3 = 0;
          puVar6 = puVar8;
          do {
            *puVar6 = (short)iVar3;
            puVar6 = puVar6 + 1;
            iVar3 = iVar3 + 1;
          } while (iVar3 < 0x100);
          puVar6 = (undefined2 *)(local_1c + 2);
          iVar3 = FUN_004b7800(1,puVar8,0x100,puVar6,0,0);
          if (iVar3 != 0) {
            *(undefined2 *)local_1c = 0;
            if ((1 < (int)UINT_004ed52c) && (local_e[0] != 0)) {
              pbVar5 = local_e + 1;
              do {
                if (*pbVar5 == 0) break;
                uVar4 = (uint)pbVar5[-1];
                if (uVar4 <= *pbVar5) {
                  puVar7 = (undefined2 *)(local_18 + (uVar4 + 1) * 2);
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
            PTR_DAT_004ed320 = (undefined *)puVar2;
            PTR_DAT_004ed324 = (undefined *)puVar6;
            if (UINT_008d0efc != 0) {
              free(UINT_008d0efc);
            }
            UINT_008d0efc = local_18;
            if (UINT_008d0f00 != 0) {
              free(UINT_008d0f00);
            }
            UINT_008d0f00 = local_1c;
            free(puVar9);
            free(puVar8);
            return 0;
          }
        }
      }
    }
  }
  free(local_18);
  free(local_1c);
  free(puVar9);
  free(puVar8);
  return 1;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_e

#endif


/* ---- 0x004b6f50  FUN_004b6f50 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004b6f50(uint param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  uVar1 = ((code *)FUN_004b6fb0)();
  uVar1 = param_2 & param_1 | ~param_2 & uVar1;
  ((code *)FUN_004b7050)(uVar1);
  return uVar1;
}
#undef local_8

#endif


/* ---- 0x004b6f90  FUN_004b6f90 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b6f90(undefined4 param_1,uint param_2)

{
  FUN_004b6f50(param_1,param_2 & 0xfff7ffff);
  return;
}
#endif


/* ---- 0x004b6fb0  FUN_004b6fb0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004b6fb0(uint param_1)

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


/* ---- 0x004b7050  FUN_004b7050 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b7050(void)

{
  return;
}
#endif


/* ---- 0x004b70e0  FUN_004b70e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b70e0(int param_1,int param_2)

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


/* ---- 0x004b7150  FUN_004b7150 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined * __cdecl FUN_004b7150(int param_1,int param_2)

{
  byte bVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  bVar1 = (byte)(param_2 >> 0x1f);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  puVar2 = (undefined *)
           __addl(*(undefined4 *)(param_1 + iVar3 * 4),
                  1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) & 0x1f),
                  param_1 + iVar3 * 4);
  iVar3 = iVar3 + -1;
  if (-1 < iVar3) {
    puVar4 = (undefined4 *)(param_1 + iVar3 * 4);
    do {
      if (puVar2 == (undefined *)0x0) {
        return (undefined *)0x0;
      }
      puVar2 = (undefined *)__addl(*puVar4,1,puVar4);
      iVar3 = iVar3 + -1;
      puVar4 = puVar4 + -1;
    } while (-1 < iVar3);
  }
  return puVar2;
}
#endif


/* ---- 0x004b71c0  FUN_004b71c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined * FUN_004b71c0(int param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  byte bVar2;
  int iVar3;
  undefined4 *puVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  bVar2 = (byte)(param_2 >> 0x1f);
  bVar2 = 0x1f - ((((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  if (((*(uint *)(param_1 + iVar3 * 4) & 1 << (bVar2 & 0x1f)) != 0) &&
     (iVar1 = FUN_004b70e0(param_1,param_2 + 1), iVar1 == 0)) {
    local_4 = (uint)FUN_004b7150(param_1,param_2 + -1);
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
  return (undefined *)local_4;
}
#undef local_4

#endif


/* ---- 0x004b7260  FUN_004b7260 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b7260(int param_1,undefined4 *param_2)

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


/* ---- 0x004b7280  FUN_004b7280 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b7280(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}
#endif


/* ---- 0x004b7290  FUN_004b7290 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004b7290(int *param_1)

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


/* ---- 0x004b72b0  FUN_004b72b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b72b0(uint *param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
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
#undef local_4
#undef local_8

#endif


/* ---- 0x004b7560  FUN_004b7560 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b7560(undefined4 param_1,undefined4 param_2)

{
  _ld12tocvt(param_1,param_2,&DAT_004f03e8);
  return;
}
#endif


/* ---- 0x004b7580  FUN_004b7580 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b7580(uint param_1,undefined4 param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(undefined1 (*)[12])(_frame + (0x20 - 0xc)))
  
  __strgtold12(local_c,&param_2,param_2,0,0,0,0);
  _ld12tod((uint)local_c,param_1);
  return;
}
#undef local_c

#endif


/* ---- 0x004b75c0  FUN_004b75c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b75c0(undefined4 param_1,undefined4 param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(undefined1 (*)[12])(_frame + (0x20 - 0xc)))
  
  __strgtold12(local_c,&param_2,param_2,0,0,0,0);
  FUN_004b7560(local_c,param_1);
  return;
}
#undef local_c

#endif


/* ---- 0x004b7600  FUN_004b7600 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b7600(char *param_1,int param_2,int param_3)

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


/* ---- 0x004b76a0  FUN_004b76a0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_4c */
/* WARNING: Variable defined which should be unmapped: local_48 */

int * FUN_004b76a0(undefined4 param_1,undefined4 param_2,int *param_3,char *param_4)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  #define local_4c (*(uint *)(_frame + (0x60 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x60 - 0x48)))
  #define local_28 (*(uint *)(_frame + (0x60 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x60 - 0x24)))
  #define local_20 (*(undefined2 *)(_frame + (0x60 - 0x20)))
  #define local_1c (*(short *)(_frame + (0x60 - 0x1c)))
  #define local_1a (*(char *)(_frame + (0x60 - 0x1a)))
  #define local_18 (*(char (*)[24])(_frame + (0x60 - 0x18)))
  
  FUN_004b7730(&local_28,&param_1);
  iVar2 = FUN_004bb1e0(local_28,local_24,local_20,0x11,0,&local_1c);
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
#undef local_48
#undef local_4c

#endif


/* ---- 0x004b7730  FUN_004b7730 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b7730(uint *param_1,uint *param_2)

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


/* ---- 0x004b77f0  FUN_004b77f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004b77f0(void)

{
  _amsg_exit(2);
  return;
}
#endif


/* ---- 0x004b7800  FUN_004b7800 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004b7800(int param_1,int param_2,int param_3,int param_4,uint param_5,uint param_6)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  int a5;
  int iVar3;
  undefined *a5_00;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  a5_00 = (undefined *)0x0;
  if (UINT_008d0f50 == 0) {
    iVar1 = GetStringTypeW(1,IMG_ADDR(0x004d8d8c),1,(int)&local_4);
    if (iVar1 == 0) {
      iVar1 = GetStringTypeA(0,1,IMG_ADDR(0x008d0874),1,(int)&local_4);
      if (iVar1 == 0) {
        return 0;
      }
      UINT_008d0f50 = 2;
    }
    else {
      UINT_008d0f50 = 1;
    }
  }
  if (UINT_008d0f50 != 1) {
    local_4 = UINT_008d0f50;
    if (UINT_008d0f50 == 2) {
      local_4 = 0;
      if (param_5 == 0) {
        param_5 = UINT_008d0b80;
      }
      iVar1 = WideCharToMultiByte(param_5,0x220,param_2,param_3,0,0,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      a5 = calloc(1,iVar1);
      if (a5 == 0) {
        return 0;
      }
      iVar3 = WideCharToMultiByte(param_5,0x220,param_2,param_3,a5,iVar1,0,0);
      if ((iVar3 != 0) && (a5_00 = malloc(iVar1 * 2 + 2), a5_00 != (undefined *)0x0)) {
        if (param_6 == 0) {
          param_6 = UINT_008d0b70;
        }
        param_3 = param_3 * 2;
        *(undefined2 *)(a5_00 + param_3) = 0xffff;
        *(undefined2 *)(a5_00 + param_3 + -2) = 0xffff;
        local_4 = GetStringTypeA(param_6,param_1,a5,iVar1,(int)a5_00);
        if ((*(short *)(a5_00 + param_3 + -2) == -1) || (*(short *)(a5_00 + param_3) != -1)) {
          local_4 = 0;
        }
        else {
          memmove(param_4,a5_00,param_3);
        }
      }
      free(a5);
      free(a5_00);
    }
    return local_4;
  }
  uVar2 = GetStringTypeW(param_1,param_2,param_3,param_4);
  return uVar2;
}
#undef local_4

#endif


/* ---- 0x004b7c10  FUN_004b7c10 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_004b7c10(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  _lock(2);
  iVar3 = 3;
  if (3 < (int)UINT_00906ae0) {
    do {
      iVar1 = *(int *)(UINT_00905ac4 + iVar3 * 4);
      if (iVar1 != 0) {
        if (((*(byte *)(iVar1 + 0xc) & 0x83) != 0) && (iVar1 = fclose(iVar1), iVar1 != -1)) {
          iVar2 = iVar2 + 1;
        }
        if (0x13 < iVar3) {
          DeleteCriticalSection(*(int *)(UINT_00905ac4 + iVar3 * 4) + 0x20);
          free(*(undefined4 *)(UINT_00905ac4 + iVar3 * 4));
          *(undefined4 *)(UINT_00905ac4 + iVar3 * 4) = 0;
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)UINT_00906ae0);
  }
  _unlock(2);
  return iVar2;
}
#endif


/* ---- 0x004b8f30  FUN_004b8f30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __fastcall FUN_004b8f30(byte param_1,int param_2)

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


/* ---- 0x004b9916  FUN_004b9916 ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
FUN_004b9916(undefined4 param_1,uint param_2,ushort param_3,uint param_4,uint param_5,uint param_6,
            uint param_7,uint param_8,ushort param_9)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  undefined4 in_EAX;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  
  if ((((((CONCAT22(param_3,PIECE(param_2,2,2)) ^ 0x700) & 0x700) == 0) &&
       ((&DAT_004f04dc)[(PIECE(param_2,2,2) & 0x7800) >> 0xb] != '\0')) && ((param_3 & 0x7fff) != 0x7fff)
      ) && ((((param_9 & 0x7fff) != 0 && ((param_9 & 0x7fff) != 0x7fff)) &&
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
        fVar4 = fVar4 * (float10)_DAT_004f050c;
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
        fVar3 = fVar3 - PUN(float10,(unkint10)(fVar3 / fVar4)) * fVar4;
        param_7 = SUB104(fVar3,0);
        uVar1 = (uint)((unkuint10)fVar3 >> 0x20);
        param_9 = (ushort)((unkuint10)fVar3 >> 0x40);
      }
    }
  }
  return in_EAX;
}
#undef local_24

#endif


/* ---- 0x004b9b1c  FUN_004b9b1c ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_004b9b1c(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
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
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  
  uVar5 = SUB104(in_ST0,0);
  uVar6 = (uint)((unkuint10)in_ST0 >> 0x20);
  uVar7 = (ushort)((unkuint10)in_ST0 >> 0x40);
  uVar2 = SUB104(in_ST1,0);
  uVar3 = (uint)((unkuint10)in_ST1 >> 0x20);
  uVar4 = (ushort)((unkuint10)in_ST1 >> 0x40);
  if (((uint)((unkuint10)in_ST1 >> 0x30) & 0x7fff0000) != 0) {
    FUN_004b9916(uVar2,uVar3,uVar4,in_stack_ffffffd8,in_stack_ffffffdc,
                 CONCAT22(in_stack_ffffffe2,in_stack_ffffffe0),uVar5,uVar6,uVar7);
    return extraout_ST0;
  }
  if (uVar2 == 0 && uVar3 == 0) {
    return in_ST0 - PUN(float10,(unkint10)(in_ST0 / in_ST1)) * in_ST1;
  }
  if ((uVar7 & 0x7fff) < 0x7fbf) {
    fVar1 = in_ST0 * (float10)_DAT_004f04f4;
    uVar5 = SUB104(fVar1,0);
    uVar6 = (uint)((unkuint10)fVar1 >> 0x20);
    uVar7 = (ushort)((unkuint10)fVar1 >> 0x40);
  }
  fVar1 = in_ST1 * (float10)_DAT_004f04f4;
  FUN_004b9916(SUB104(fVar1,0),(uint)((unkuint10)fVar1 >> 0x20),(ushort)((unkuint10)fVar1 >> 0x40),
               uVar2,uVar3,CONCAT22(in_stack_ffffffe2,uVar4),uVar5,uVar6,uVar7);
  return extraout_ST0_00;
}
#undef local_10
#undef local_c

#endif


/* ---- 0x004b9fc0  FUN_004b9fc0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float __cdecl FUN_004b9fc0(undefined4 param_1,undefined4 param_2,short param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define uStack_4 (*(undefined2 *)(_frame + (0x20 - 0x4)))
  
  uStack_4 = (undefined2)param_2;
  return (float)(double)CONCAT26(PIECE(param_2,2,2) & 0x800f | (param_3 + 0x3fe) * 0x10,
                                 CONCAT24(uStack_4,param_1));
}
#undef uStack_4

#endif


/* ---- 0x004ba000  FUN_004ba000 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004ba000(int param_1,uint param_2)

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


/* ---- 0x004ba060  FUN_004ba060 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float __cdecl FUN_004ba060(uint param_1,uint param_2,int *param_3)

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
    fVar6 = FUN_004b9fc0(param_1,CONCAT13(PIECE(param_2,3,1),CONCAT12(PIECE(param_2,2,1),(undefined2)param_2))
                         ,0);
    *param_3 = iVar5;
    return fVar6;
  }
  fVar6 = FUN_004b9fc0(param_1,param_2,0);
  *param_3 = (short)((ushort)(param_2 >> 0x14) & 0x7ff) + -0x3fe;
  return fVar6;
}
#endif


/* ---- 0x004ba170  FUN_004ba170 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float __cdecl FUN_004ba170(double param_1)

{
  return (float)ROUND(param_1);
}
#endif


/* ---- 0x004ba190  FUN_004ba190 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_004ba190(int param_1,uint param_2)

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
  iVar1 = FUN_004ba000(param_1,param_2);
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


/* ---- 0x004ba230  FUN_004ba230 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined * __stdcall FUN_004ba230(int a1)

{
  int *piVar1;
  int iVar2;
  undefined *puVar3;
  
  piVar1 = *(int **)a1;
  if (((*piVar1 == -0x1f928c9d) && (piVar1[4] == 3)) && (piVar1[5] == 0x19930520)) {
    terminate();
    return (undefined *)0x1;
  }
  if (UINT_008d1028 != 0) {
    iVar2 = _ValidateExecute(UINT_008d1028);
    if (iVar2 != 0) {
      puVar3 = (undefined *)(*(code *)UINT_008d1028)(a1);
      return puVar3;
    }
  }
  return (undefined *)0x0;
}
#endif


/* ---- 0x004ba290  FUN_004ba290 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004ba290(void)

{
  UINT_008d1028 = SetUnhandledExceptionFilter(FUN_004ba230);
  return;
}
#endif


/* ---- 0x004ba2b0  FUN_004ba2b0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004ba2b0(void)

{
  SetUnhandledExceptionFilter(UINT_008d1028);
  return;
}
#endif


/* ---- 0x004ba340  FUN_004ba340 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004ba340(int param_1,undefined4 param_2,undefined4 param_3,char *param_4)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  undefined *puVar5;
  undefined *puVar6;
  byte *pbVar7;
  #define local_84 (*(uint *)(_frame + (0xa0 - 0x84)))
  #define local_80 (*(undefined1 (*)[128])(_frame + (0xa0 - 0x80)))
  
  if (param_1 != 1) {
    if (param_1 != 0) {
      return 0xffffffff;
    }
    iVar4 = ((code *)FUN_004bc4c0)(param_2,param_3,&DAT_008d1038,4,0);
    if (iVar4 != 0) {
      pbVar7 = &DAT_008d1038;
      *param_4 = '\0';
      while( true ) {
        bVar1 = *pbVar7;
        if ((int)UINT_004ed52c < 2) {
          uVar3 = (byte)PTR_DAT_004ed320[(uint)bVar1 * 2] & 4;
        }
        else {
          uVar3 = _isctype(bVar1,4);
        }
        if (uVar3 == 0) break;
        pbVar7 = pbVar7 + 2;
        *param_4 = *param_4 * '\n' + bVar1 + -0x30;
        if (IMG_ADDR(0x008d103f) < (int)pbVar7) {
          return 0;
        }
      }
      return 0;
    }
    return 0xffffffff;
  }
  puVar5 = local_80;
  bVar2 = false;
  uVar3 = ((code *)FUN_004bc5f0)(param_2,param_3,local_80,0x80,0);
  if (uVar3 == 0) {
    iVar4 = GetLastError();
    if (((iVar4 != 0x7a) || (uVar3 = ((code *)FUN_004bc5f0)(param_2,param_3,0,0,0), uVar3 == 0)) ||
       (puVar5 = malloc(uVar3), puVar5 == (undefined *)0x0)) goto LAB_004ba3f0;
    bVar2 = true;
    uVar3 = ((code *)FUN_004bc5f0)(param_2,param_3,puVar5,uVar3,0);
    if (uVar3 == 0) goto LAB_004ba3f0;
  }
  puVar6 = malloc(uVar3);
  *(undefined **)param_4 = puVar6;
  if (puVar6 != (undefined *)0x0) {
    strncpy(puVar6,puVar5,uVar3);
    if (!bVar2) {
      return 0;
    }
    free(puVar5);
    return 0;
  }
LAB_004ba3f0:
  if (!bVar2) {
    return 0xffffffff;
  }
  free(puVar5);
  return 0xffffffff;
}
#undef local_80
#undef local_84

#endif


/* ---- 0x004bb1e0  FUN_004bb1e0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4
FUN_004bb1e0(int param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6)

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
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(undefined1 *)(_frame + (0x30 - 0x1c)))
  #define local_1b (*(undefined1 *)(_frame + (0x30 - 0x1b)))
  #define local_1a (*(undefined1 *)(_frame + (0x30 - 0x1a)))
  #define local_19 (*(undefined1 *)(_frame + (0x30 - 0x19)))
  #define local_18 (*(undefined1 *)(_frame + (0x30 - 0x18)))
  #define local_17 (*(undefined1 *)(_frame + (0x30 - 0x17)))
  #define local_16 (*(undefined1 *)(_frame + (0x30 - 0x16)))
  #define local_15 (*(undefined1 *)(_frame + (0x30 - 0x15)))
  #define local_14 (*(undefined1 *)(_frame + (0x30 - 0x14)))
  #define local_13 (*(undefined1 *)(_frame + (0x30 - 0x13)))
  #define local_12 (*(undefined1 *)(_frame + (0x30 - 0x12)))
  #define local_11 (*(undefined1 *)(_frame + (0x30 - 0x11)))
  #define local_10 (*(undefined2 *)(_frame + (0x30 - 0x10)))
  #define uStack_e (*(undefined2 *)(_frame + (0x30 - 0xe)))
  #define uStack_c (*(undefined2 *)(_frame + (0x30 - 0xc)))
  #define uStack_a (*(undefined2 *)(_frame + (0x30 - 0xa)))
  #define uStack_8 (*(undefined2 *)(_frame + (0x30 - 0x8)))
  #define local_6 (*(uint *)(_frame + (0x30 - 0x6)))
  
  psVar1 = param_6;
  local_1c = 0xcc;
  local_1b = 0xcc;
  local_1a = 0xcc;
  local_19 = 0xcc;
  local_18 = 0xcc;
  local_17 = 0xcc;
  local_16 = 0xcc;
  local_15 = 0xcc;
  local_14 = 0xcc;
  local_13 = 0xcc;
  uVar4 = param_3 & 0x7fff;
  local_12 = 0xfb;
  local_11 = 0x3f;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((short)uVar4 == 0) && (param_2 == 0)) && (param_1 == 0)) {
    *param_6 = 0;
LAB_004bb3ef:
    *(undefined1 *)(psVar1 + 1) = 0x20;
    *(undefined1 *)((int)psVar1 + 3) = 1;
    *(undefined1 *)(psVar1 + 2) = 0x30;
    *(undefined1 *)((int)psVar1 + 5) = 0;
    return 1;
  }
  if ((short)uVar4 == 0x7fff) {
    *param_6 = 1;
    if (((param_2 != 0x80000000) || (param_1 != 0)) && ((param_2 & 0x40000000) == 0)) {
      *(uint *)(param_6 + 2) = 0x4e532331;
      param_6[4] = 0x4e41;
      *(undefined1 *)((int)param_6 + 3) = 6;
      *(undefined1 *)(param_6 + 5) = 0;
      return 0;
    }
    if ((((param_3 & 0x8000) != 0) && (param_2 == 0xc0000000)) && (param_1 == 0)) {
      *(uint *)(param_6 + 2) = 0x4e492331;
      *(undefined1 *)((int)param_6 + 3) = 5;
      param_6[4] = 0x44;
      return 0;
    }
    if ((param_2 == 0x80000000) && (param_1 == 0)) {
      *(uint *)(param_6 + 2) = 0x4e492331;
      *(undefined1 *)((int)param_6 + 3) = 5;
      param_6[4] = 0x46;
      return 0;
    }
    *(uint *)(param_6 + 2) = 0x4e512331;
    param_6[4] = 0x4e41;
    *(undefined1 *)((int)param_6 + 3) = 6;
    *(undefined1 *)(param_6 + 5) = 0;
    return 0;
  }
  PIECE(local_6,0,1) = (undefined1)uVar4;
  PIECE(local_6,1,1) = (char)(uVar4 >> 8);
  uStack_a = (undefined2)param_2;
  uStack_8 = (undefined2)(param_2 >> 0x10);
  uStack_e = (undefined2)param_1;
  uStack_c = (undefined2)((uint)param_1 >> 0x10);
  local_10 = 0;
  sVar9 = (short)(((uVar4 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar4 * 0x4d10 >>
                 0x10);
  __multtenpow12(&local_10,-(int)sVar9,1);
  if (0x3ffe < CONCAT11(PIECE(local_6,1,1),(undefined1)local_6)) {
    sVar9 = sVar9 + 1;
    __ld12mul(&local_10,&local_1c);
  }
  *psVar1 = sVar9;
  iVar8 = param_4;
  if (((param_5 & 1) != 0) && (iVar8 = param_4 + sVar9, param_4 + sVar9 < 1)) {
    *psVar1 = 0;
    goto LAB_004bb3ef;
  }
  if (0x15 < iVar8) {
    iVar8 = 0x15;
  }
  uVar2 = CONCAT11(PIECE(local_6,1,1),(undefined1)local_6);
  PIECE(local_6,0,1) = 0;
  PIECE(local_6,1,1) = '\0';
  iVar5 = 8;
  iVar10 = uVar2 - 0x3ffe;
  do {
    __shl_12(&local_10);
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  if (iVar10 < 0) {
    for (uVar4 = -iVar10 & 0xff; uVar4 != 0; uVar4 = uVar4 - 1) {
      __shr_12(&local_10);
    }
  }
  psVar1 = psVar1 + 2;
  iVar8 = iVar8 + 1;
  psVar6 = psVar1;
  if (0 < iVar8) {
    do {
      param_1 = CONCAT22(uStack_e,local_10);
      param_2 = CONCAT22(uStack_a,uStack_c);
      param_3 = CONCAT13(PIECE(local_6,1,1),CONCAT12((undefined1)local_6,uStack_8));
      __shl_12(&local_10);
      __shl_12(&local_10);
      __add_12(&local_10,&param_1);
      __shl_12(&local_10);
      cVar3 = PIECE(local_6,1,1) + '0';
      PIECE(local_6,1,1) = '\0';
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
      if (psVar1 <= psVar7) goto LAB_004bb546;
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
      goto LAB_004bb546;
    }
  }
  psVar7 = (short *)((int)psVar7 + 1);
  *param_6 = *param_6 + 1;
  *(char *)psVar7 = *(char *)psVar7 + '\x01';
LAB_004bb546:
  cVar3 = ((char)psVar7 - (char)param_6) + -3;
  *(char *)((int)param_6 + 3) = cVar3;
  *(undefined1 *)((int)param_6 + cVar3 + 4) = 0;
  return 1;
}
#undef local_10
#undef local_11
#undef local_12
#undef local_13
#undef local_14
#undef local_15
#undef local_16
#undef local_17
#undef local_18
#undef local_19
#undef local_1a
#undef local_1b
#undef local_1c
#undef local_20
#undef local_6
#undef uStack_8
#undef uStack_a
#undef uStack_c
#undef uStack_e

#endif


/* ---- 0x004bc3d0  FUN_004bc3d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004bc3d0(int param_1)

{
  undefined4 *puVar1;
  
  if (param_1 == 1) {
    puVar1 = (undefined4 *)_errno();
    *puVar1 = 0x21;
  }
  else if ((1 < param_1) && (param_1 < 4)) {
    puVar1 = (undefined4 *)_errno();
    *puVar1 = 0x22;
    return;
  }
  return;
}
#endif


/* ---- 0x004bc400  FUN_004bc400 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_004bc400(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}
#endif


/* ---- 0x004bc410  FUN_004bc410 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_004bc410(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}
#endif


/* ---- 0x004bc430  FUN_004bc430 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_004bc430(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  short in_FPUControlWord;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  return (int)in_FPUControlWord;
}
#undef local_8

#endif


/* ---- 0x004bc460  FUN_004bc460 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004bc460(void)

{
  return;
}
#endif


/* ---- 0x004bc4c0  FUN_004bc4c0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004bc4c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined *a3;
  int iVar3;
  int unaff_ESI;
  int unaff_EDI;
  
  if (UINT_008d1080 == 0) {
    iVar1 = GetLocaleInfoW(0,1,0,0);
    if (iVar1 == 0) {
      iVar1 = GetLocaleInfoA(0,1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      UINT_008d1080 = 2;
    }
    else {
      UINT_008d1080 = 1;
    }
  }
  if (UINT_008d1080 == 1) {
    uVar2 = GetLocaleInfoW(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  if (UINT_008d1080 != 2) {
    return UINT_008d1080;
  }
  iVar1 = 0;
  uVar2 = GetLocaleInfoA(param_1,param_2,0);
  if (uVar2 != 0) {
    a3 = malloc(uVar2);
    if (a3 == (undefined *)0x0) {
      return 0;
    }
    iVar3 = GetLocaleInfoA(param_1,param_2,a3,uVar2);
    if (iVar3 != 0) {
      if (unaff_EDI == 0) {
        uVar2 = MultiByteToWideChar(unaff_ESI,1,(int)a3,-1,0,0);
        if (uVar2 != 0) {
          free(a3);
          return uVar2;
        }
      }
      else {
        uVar2 = MultiByteToWideChar(unaff_ESI,1,(int)a3,-1,iVar1,unaff_EDI);
        if (uVar2 != 0) {
          free(a3);
          return uVar2;
        }
      }
    }
    free(a3);
    return 0;
  }
  return 0;
}
#endif


/* ---- 0x004bc5f0  FUN_004bc5f0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004bc5f0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined *a3;
  int unaff_ESI;
  int unaff_EDI;
  int a5;
  
  if (UINT_008d1084 == 0) {
    iVar1 = GetLocaleInfoW(0,1,0,0);
    if (iVar1 == 0) {
      iVar1 = GetLocaleInfoA(0,1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      UINT_008d1084 = 2;
    }
    else {
      UINT_008d1084 = 1;
    }
  }
  if (UINT_008d1084 == 2) {
    uVar2 = GetLocaleInfoA(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  if (UINT_008d1084 != 1) {
    return UINT_008d1084;
  }
  a5 = 0;
  iVar1 = GetLocaleInfoW(param_1,param_2,0);
  if (iVar1 != 0) {
    a3 = malloc(iVar1 * 2);
    if (a3 == (undefined *)0x0) {
      return 0;
    }
    iVar1 = GetLocaleInfoW(param_1,param_2,a3,iVar1);
    if (iVar1 != 0) {
      if (unaff_EDI == 0) {
        uVar2 = WideCharToMultiByte(unaff_ESI,0x220,(int)a3,-1,0,0,0,0);
        if (uVar2 != 0) {
          free(a3);
          return uVar2;
        }
      }
      else {
        uVar2 = WideCharToMultiByte(unaff_ESI,0x220,(int)a3,-1,a5,unaff_EDI,0,0);
        if (uVar2 != 0) {
          free(a3);
          return uVar2;
        }
      }
    }
    free(a3);
    return 0;
  }
  return 0;
}
#endif


/* ---- 0x004bcb40  FUN_004bcb40 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_004bcb40(uint param_1,int param_2)

{
  byte bVar1;
  undefined4 *puVar2;
  byte bVar3;
  
  bVar1 = *(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1);
  if (param_2 == 0x8000) {
    bVar3 = bVar1 & 0x7f;
  }
  else {
    if (param_2 != 0x4000) {
      puVar2 = (undefined4 *)_errno();
      *puVar2 = 0x16;
      return -1;
    }
    bVar3 = bVar1 | 0x80;
  }
  *(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) = bVar3;
  return (-(uint)((bVar1 & 0x80) != 0) & 0xffffc000) + 0x8000;
}
#endif


/* ---- 0x004bdad0  FUN_004bdad0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
FUN_004bdad0(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
            uint param_7)

{
  UINT_008d16b8 = param_5;
  _DAT_008d16b0 = param_7;
  if (UINT_008d16bc == 0) {
    UINT_008d16bc = param_7;
  }
  return 0;
}

/* ---- 0x004bdf70  FUN_004bdf70 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004bdf70(int *param_1,undefined4 param_2)

{
  PTR_008d11f8 = param_1;
  _DAT_008d11f0 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_memory_004f0cdc,&PTR_FUN_004f0c18);
  (*(code *)*PTR_008d11f8)(s_MEMORY_insane_004f0ccc,&PTR_FUN_004f0c28);
  return 0;
}

/* ---- 0x004bdfb0  FUN_004bdfb0 ---- */
void FUN_004bdfb0(void)

{
  (*(code *)PTR_008d11f8[1])(s_MEMORY_insane_004f0ccc);
  (*(code *)PTR_008d11f8[1])(s_LECMODULE_insane_memory_004f0cdc);
  return;
}

/* ---- 0x004bdfe0  FUN_004bdfe0 ---- */
void FUN_004bdfe0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (**(code **)(UINT_008d11f4 + 0x20))(param_1,param_2,param_3);
  return;
}

/* ---- 0x004be000  FUN_004be000 ---- */
void FUN_004be000(undefined4 param_1)

{
  (**(code **)(UINT_008d11f4 + 0x24))(param_1);
  return;
}

/* ---- 0x004be020  FUN_004be020 ---- */
void FUN_004be020(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  (**(code **)(UINT_008d11f4 + 0x28))(param_1,param_2,param_3,param_4);
  return;
}

/* ---- 0x004be050  FUN_004be050 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004be050(int *param_1,undefined4 param_2)

{
  PTR_008d11d4 = param_1;
  _DAT_008d1630 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_stdio_004f0cf4,&PTR_FUN_004f0c38);
  (*(code *)*PTR_008d11d4)(s_FILIO_insane_stdio_004f0c64,&PTR_FUN_004f0c48);
  return 0;
}

/* ---- 0x004be090  FUN_004be090 ---- */
void FUN_004be090(void)

{
  (*(code *)PTR_008d11d4[1])(s_FILIO_insane_stdio_004f0c64);
  (*(code *)PTR_008d11d4[1])(s_LECMODULE_insane_stdio_004f0cf4);
  return;
}

/* ---- 0x004be0c0  FUN_004be0c0 ---- */
void FUN_004be0c0(undefined4 param_1,undefined4 param_2)

{
  (**(code **)(UINT_008d11f4 + 0x30))(param_1,param_2);
  return;
}

/* ---- 0x004be0e0  FUN_004be0e0 ---- */
void FUN_004be0e0(undefined4 param_1)

{
  (**(code **)(UINT_008d11f4 + 0x34))(param_1);
  return;
}

/* ---- 0x004be100  FUN_004be100 ---- */
void FUN_004be100(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (**(code **)(UINT_008d11f4 + 0x38))(param_1,param_2,param_3);
  return;
}

/* ---- 0x004be120  FUN_004be120 ---- */
void FUN_004be120(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (**(code **)(UINT_008d11f4 + 0x40))(param_1,param_2,param_3);
  return;
}

/* ---- 0x004be140  FUN_004be140 ---- */
void FUN_004be140(undefined4 param_1)

{
  (**(code **)(UINT_008d11f4 + 0x48))(param_1);
  return;
}

/* ---- 0x004be160  FUN_004be160 ---- */
void FUN_004be160(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (**(code **)(UINT_008d11f4 + 0x4c))(param_1,param_2,param_3);
  return;
}

/* ---- 0x004bf950  FUN_004bf950 ---- */
undefined * __stdcall FUN_004bf950(int a1,int a2,int a3,int a4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *pcVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint *puVar8;
  uint *puVar9;
  undefined4 *puVar10;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  
  iVar4 = g_nLightEdSelected;
  if ((uint)a2 < 0x111) {
    if (a2 == 0x110) {
      SendDlgItemMessageA(a1,0x3fb,0x465,0,32000);
      SendDlgItemMessageA(a1,0x3ff,0x465,0,32000);
      SendDlgItemMessageA(a1,0x400,0x465,0,32000);
      uVar6 = 0;
      puVar8 = &local_24;
      uVar3 = 1;
      do {
        uVar6 = uVar6 + 1;
        puVar8[-1] = uVar6;
        *puVar8 = uVar3;
        uVar3 = uVar3 + 5;
        puVar8 = puVar8 + 2;
      } while ((int)uVar3 < 0x1a);
      SendDlgItemMessageA(a1,0x3fb,0x46b,5,(int)&local_28);
      SendDlgItemMessageA(a1,0x3ff,0x46b,5,(int)&local_28);
      SendDlgItemMessageA(a1,0x400,0x46b,5,(int)&local_28);
      return (undefined *)0x1;
    }
    if (a2 != 0x10) {
      return (undefined *)0x0;
    }
    Lua_LightMgrShutdown();
    return (undefined *)0x1;
  }
  if (a2 != 0x111) {
    if (a2 != 0x115) {
      return (undefined *)0x0;
    }
    uVar3 = a3 & 0xffff;
    uVar6 = (uint)a3 >> 0x10;
    iVar4 = GetDlgItem(a1,0x3fb);
    if (a4 == iVar4) {
      LightEd_RefreshControl(a1,0x3fb,uVar3,uVar6);
      return (undefined *)0x1;
    }
    iVar4 = GetDlgItem(a1,0x3ff);
    if (a4 == iVar4) {
      LightEd_RefreshControl(a1,0x3ff,uVar3,uVar6);
      return (undefined *)0x1;
    }
    iVar4 = GetDlgItem(a1,0x400);
    if (a4 != iVar4) {
      return (undefined *)0x0;
    }
    LightEd_RefreshControl(a1,0x400,uVar3,uVar6);
    return (undefined *)0x1;
  }
  sVar2 = (short)((uint)a3 >> 0x10);
  switch(a3 & 0xffffU) {
  case 1000:
    if (sVar2 != 1) {
      return (undefined *)0x1;
    }
    LightEd_UpdateDialog(a1);
    LightEd_ResetLight(g_nLightEdSelected,1);
    return (undefined *)0x1;
  case 0x3e9:
  case 0x3ea:
  case 0x3eb:
    if (g_pLightEdSet == (void *)0x0) {
      return (undefined *)0x1;
    }
    if (g_nLightEdSelected == -1) {
      return (undefined *)0x1;
    }
    iVar4 = IsDlgButtonChecked(a1,0x3e9);
    if (iVar4 == 1) {
      *(undefined4 *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x30) = 1;
    }
    else {
      iVar4 = IsDlgButtonChecked(a1,0x3ea);
      if (iVar4 == 1) {
        *(undefined4 *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x30) = 2;
      }
      else {
        iVar4 = IsDlgButtonChecked(a1,0x3eb);
        if (iVar4 == 1) {
          *(undefined4 *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x30) = 3;
        }
      }
    }
    LightEd_UpdateDialog(g_hLightEdDialog);
    return (undefined *)0x1;
  case 0x3ec:
  case 0x3ed:
  case 0x3ee:
  case 0x3ef:
  case 0x3f0:
  case 0x3f1:
  case 0x3f2:
  case 0x3f4:
  case 0x3f5:
    if (sVar2 == 0x300) {
      LightEd_ReadControl(a1,a3 & 0xffffU);
      return (undefined *)0x0;
    }
    break;
  case 0x3f6:
    if ((sVar2 == 0) && (g_pLightEdSet != (void *)0x0)) {
      LightEd_AddLight();
      return (undefined *)0x0;
    }
    break;
  case 0x3f7:
    if (((sVar2 == 0) && (g_pLightEdSet != (void *)0x0)) && (g_nLightEdSelected != -1)) {
      LightEd_DeleteLight(g_nLightEdSelected);
      return (undefined *)0x0;
    }
    break;
  case 0x3f8:
    if ((sVar2 == 0) && (g_pLightEdSet != (void *)0x0)) {
      LightEd_SyncFromSet();
      LightMgr_UpdateDialog(a1);
      return (undefined *)0x0;
    }
    break;
  case 0x3f9:
    if ((sVar2 == 0) && (g_pLightEdSet != (void *)0x0)) {
      LightEd_SaveSetFile();
      return (undefined *)0x0;
    }
    break;
  case 0x3fa:
    if (g_pLightEdSet == (void *)0x0) {
      return (undefined *)0x1;
    }
    if (g_nLightEdSelected == -1) {
      return (undefined *)0x1;
    }
    iVar4 = IsDlgButtonChecked(a1,0x3fa);
    *(uint *)((&UINT_008d1730)[g_nLightEdSelected * 5] + 0x34) = (uint)(iVar4 == 1);
    return (undefined *)0x1;
  case 0x3fc:
    LightEd_SetAllEnabled(0);
    return (undefined *)0x1;
  case 0x3fd:
    LightEd_SetAllEnabled(1);
    return (undefined *)0x1;
  case 0x3fe:
    if ((g_pLightEdSet != (void *)0x0) && (g_nLightEdSelected != -1)) {
      iVar4 = IsDlgButtonChecked(a1,0x3fe);
      (&UINT_008d1734)[g_nLightEdSelected * 5] = (uint)(iVar4 == 1);
      LightEd_MoveMarkerActor();
      return (undefined *)0x1;
    }
    return (undefined *)0x1;
  case 0x401:
    if ((sVar2 == 0) && (g_nLightEdSelected != -1)) {
      LightEd_ResetLight(g_nLightEdSelected,0);
      LightEd_UpdateDialog(a1);
      return (undefined *)0x0;
    }
    break;
  case 0x402:
    if (((sVar2 == 0) && (g_nLightEdSelected != -1)) &&
       (iVar5 = Plat_InputDialog(s_New_light_name_004f0ec8,(char *)0x0,(char *)&local_28,0x20,
                                 (char *)0x0), iVar5 != 0)) {
      uVar3 = 0;
      if (*(int *)((int)g_pLightEdSet + 0xb8) != 0) {
        puVar8 = &UINT_008d1730;
        do {
          if ((uVar3 != iVar4) && (iVar5 = _stricmp(*puVar8,&local_28), iVar5 == 0)) break;
          uVar3 = uVar3 + 1;
          puVar8 = puVar8 + 5;
        } while (uVar3 < *(uint *)((int)g_pLightEdSet + 0xb8));
      }
      if (uVar3 < *(uint *)((int)g_pLightEdSet + 0xb8)) {
        MessageBoxA(0,IMG_ADDR(0x004f0e74),IMG_ADDR(0x004f0eb0),0x30);
      }
      else {
        puVar8 = &local_28;
        while ((char)local_28 != '\0') {
          if ((char)*puVar8 == ' ') {
            *(char *)puVar8 = '_';
          }
          pcVar1 = (char *)((int)puVar8 + 1);
          puVar8 = (uint *)((int)puVar8 + 1);
          PIECE(local_28,0,1) = *pcVar1;
        }
        uVar3 = 0xffffffff;
        puVar8 = &local_28;
        do {
          puVar9 = puVar8;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          puVar9 = (uint *)((int)puVar8 + 1);
          uVar6 = *puVar8;
          puVar8 = puVar9;
        } while ((char)uVar6 != '\0');
        uVar3 = ~uVar3;
        puVar7 = (undefined4 *)((int)puVar9 - uVar3);
        puVar10 = (undefined4 *)(&UINT_008d1730)[iVar4 * 5];
        for (uVar6 = uVar3 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *puVar10 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar10 = puVar10 + 1;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined1 *)puVar10 = *(undefined1 *)puVar7;
          puVar7 = (undefined4 *)((int)puVar7 + 1);
          puVar10 = (undefined4 *)((int)puVar10 + 1);
        }
      }
      LightMgr_UpdateDialog(a1);
      SendDlgItemMessageA(a1,1000,0x186,iVar4,0);
      LightEd_UpdateDialog(a1);
      LightEd_ResetLight(iVar4,1);
    }
  }
  return (undefined *)0x0;
}
#undef local_24
#undef local_28


/* ---- 0x004c1900  FUN_004c1900 ---- */
undefined4 FUN_004c1900(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  if (*param_1 == 0) {
    return 1;
  }
  param_1 = param_1 + 3;
  iVar3 = 1;
  iVar1 = *param_1;
  while (iVar1 != 0) {
    piVar2 = param_1 + 3;
    param_1 = param_1 + 3;
    iVar3 = iVar3 + 1;
    iVar1 = *piVar2;
  }
  if (iVar3 == 0) {
    return 0;
  }
  do {
    iVar3 = iVar3 + -1;
    piVar2 = param_1 + -3;
    iVar1 = LecShare_Release(*(undefined4 *)*piVar2);
    if (iVar1 != 0) {
      if (PTR_LecShare_Nop_004f1220 != (undefined *)0x0) {
        (*(code *)PTR_LecShare_Nop_004f1220)
                  (s_LecShare_BatchUnsubscribe_Couldn_004f1298,param_1[-2]);
      }
      return 1;
    }
    *(undefined4 *)*piVar2 = 0;
    param_1 = piVar2;
  } while (iVar3 != 0);
  return 0;
}

/* ---- 0x004c1f40  FUN_004c1f40 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004c1f40(int *param_1,uint param_2)

{
  PTR_00906c40 = param_1;
  UINT_008d6f14 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_animplay_004f1360,&PTR_FUN_004f12e0);
  (*(code *)*PTR_00906c40)(s_ANIMPLAY_insane_004f1350,&PTR_FUN_004f12f0);
  (*(code *)*PTR_00906c40)(s_DEBUG_insane_animplay_004f1338,&PTR_FUN_004f1328);
  _DAT_008d6f0c = 0x4b000;
  _DAT_008d6f08 = 1000;
  return 0;
}

/* ---- 0x004c1fb0  FUN_004c1fb0 ---- */
void FUN_004c1fb0(void)

{
  (*(code *)PTR_00906c40[1])(s_ANIMPLAY_insane_004f1350);
  (*(code *)PTR_00906c40[1])(s_LECMODULE_insane_animplay_004f1360);
  (*(code *)PTR_00906c40[1])(s_DEBUG_insane_animplay_004f1338);
  return;
}

/* ---- 0x004c1ff0  FUN_004c1ff0 ---- */
undefined4 FUN_004c1ff0(void)

{
  g_pAnimMemory = (int *)(*(code *)PTR_00906c40[2])(s_MEMORY_workspace_004f14ec,UINT_008d6f14);
  g_pAnimDebug = (int *)(*(code *)PTR_00906c40[2])(s_VIRTHERC_debug_004f14dc,UINT_008d6f14);
  g_pAnimStreamer = (int *)(*(code *)PTR_00906c40[2])(s_STREAMER_spooler_004f14c8,UINT_008d6f14);
  g_pAnimFrame = (int *)(*(code *)PTR_00906c40[2])(s_ANIMFRAME_render_004f14b4,UINT_008d6f14);
  UINT_008d6f04 = (*(code *)PTR_00906c40[2])(s_BITMAP_buffers_004f14a4,UINT_008d6f14);
  g_pAnimTimer = (int *)(*(code *)PTR_00906c40[2])(s_TIMER_clocks_004f1494,UINT_008d6f14);
  g_pAnimLipsync = (int *)(*(code *)PTR_00906c40[2])(s_SOUND_lipsync_004f1484,UINT_008d6f14);
  if (g_pAnimMemory == (int *)0x0) {
    (*(code *)PTR_00906c40[8])(s_AnimPlay_Module__Cannot_allocate_004f1450);
    return 0xffffffff;
  }
  if (g_pAnimStreamer == (int *)0x0) {
    (*(code *)PTR_00906c40[8])(s_AnimPlay_Module__Cannot_allocate_004f141c);
    return 0xffffffff;
  }
  if (g_pAnimFrame == (int *)0x0) {
    (*(code *)PTR_00906c40[8])(s_AnimPlay_Module__Cannot_allocate_004f13e4);
    return 0xffffffff;
  }
  if (UINT_008d6f04 == 0) {
    (*(code *)PTR_00906c40[8])(s_AnimPlay_Module__Cannot_allocate_004f13b0);
    return 0xffffffff;
  }
  if (g_pAnimTimer == (int *)0x0) {
    (*(code *)PTR_00906c40[8])(s_AnimPlay_Module__Cannot_allocate_004f137c);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004c2150  FUN_004c2150 ---- */
void FUN_004c2150(void)

{
  (*(code *)PTR_00906c40[3])(g_pAnimMemory);
  (*(code *)PTR_00906c40[3])(g_pAnimStreamer);
  (*(code *)PTR_00906c40[3])(g_pAnimFrame);
  (*(code *)PTR_00906c40[3])(UINT_008d6f04);
  (*(code *)PTR_00906c40[3])(g_pAnimTimer);
  if (g_pAnimDebug != (int *)0x0) {
    (*(code *)PTR_00906c40[3])(g_pAnimDebug);
  }
  if (g_pAnimLipsync != (int *)0x0) {
    (*(code *)PTR_00906c40[3])(g_pAnimLipsync);
  }
  return;
}

/* ---- 0x004c21e0  FUN_004c21e0 ---- */
int FUN_004c21e0(char *param_1,int param_2,uint param_3,undefined4 param_4,undefined4 param_5,
                undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
                code *param_10,int param_11,int param_12,int param_13)

{
  unsigned char _frame[0x430] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define pvStack_418 (*(void **)(_frame + (0x430 - 0x418)))
  #define local_414 (*(undefined4 *)(_frame + (0x430 - 0x414)))
  #define local_410 (*(uint *)(_frame + (0x430 - 0x410)))
  #define local_40c (*(uint *)(_frame + (0x430 - 0x40c)))
  #define iStack_408 (*(int *)(_frame + (0x430 - 0x408)))
  #define iStack_404 (*(int *)(_frame + (0x430 - 0x404)))
  #define auStack_400 (*(undefined1 (*)[1024])(_frame + (0x430 - 0x400)))
  
  local_40c = 0;
  local_410 = 0;
  if (param_2 == 0) {
    param_2 = 0xf;
  }
  iVar2 = (**(code **)UINT_008d6f04)(&local_414,param_6,param_7,0xffffffff);
  if (iVar2 != 0) {
    (*(code *)PTR_00906c40[8])(s_Cannot_allocate_render_bitmap__004f1500);
    return -1;
  }
  if (param_11 == 0) {
    param_11 = -1;
  }
  do {
    do {
      iStack_408 = param_11 + -1;
      if (param_11 == 0) {
        (**(code **)(UINT_008d6f04 + 8))(&local_414);
        return iStack_404;
      }
      iStack_404 = AnimPlay_Create(&pvStack_418,param_1,param_2,param_12,param_13,param_3);
      param_11 = iStack_408;
    } while (iStack_404 != 0);
LAB_004c22ac:
    local_40c = 0;
    local_410 = 0;
    iVar2 = FUN_004c25c0(pvStack_418,local_414,0,0,0,auStack_400,&local_410,&local_40c,param_8,
                         param_9);
    if (((iVar2 != 0) && (iVar2 != 2)) && (iVar2 != 1)) {
LAB_004c2364:
      if ((iVar2 < 0) || (iVar2 == 4)) goto LAB_004c2376;
      goto LAB_004c22ac;
    }
    if (((param_10 == (code *)0x0) ||
        (iVar1 = *(int *)((int)pvStack_418 + 0x54),
        (*param_10)(pvStack_418,local_414,auStack_400,local_410,local_40c), iVar1 != 0)) ||
       (*(int *)((int)pvStack_418 + 0x54) == 0)) {
      FUN_004c2650(pvStack_418,local_414,0,param_4,param_5,auStack_400,local_410,local_40c,param_3);
      goto LAB_004c2364;
    }
    iStack_408 = 0;
LAB_004c2376:
    AnimPlay_Destroy(&pvStack_418);
    param_11 = iStack_408;
  } while( true );
}
#undef auStack_400
#undef iStack_404
#undef iStack_408
#undef local_40c
#undef local_410
#undef local_414
#undef pvStack_418


/* ---- 0x004c2590  FUN_004c2590 ---- */
int FUN_004c2590(int param_1)

{
  return (*(int *)(param_1 + 0x20) * 1000) / 0x1234dc;
}

/* ---- 0x004c25c0  FUN_004c25c0 ---- */
int FUN_004c25c0(void *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                int param_7,int param_8,int param_9,int param_10)

{
  int iVar1;
  
  if (*(int *)((int)param_1 + 0x10) == 0) {
    iVar1 = (*(code *)g_pAnimStreamer[7])(*(undefined4 *)((int)param_1 + 0x60));
    if ((iVar1 < 0x3d) || ((int)UINT_004f1334 < 5)) {
      if ((iVar1 < 0x3c) && ((int)UINT_004f1334 < 0xc)) {
        UINT_004f1334 = UINT_004f1334 + 1;
      }
    }
    else {
      UINT_004f1334 = UINT_004f1334 - 1;
    }
    (*(code *)g_pAnimStreamer[4])(*(undefined4 *)((int)param_1 + 0x60),UINT_004f1334 << 0xb);
    iVar1 = AnimPlay_Update(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                            param_10);
    return iVar1;
  }
  return -1;
}

/* ---- 0x004c2650  FUN_004c2650 ---- */
void FUN_004c2650(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                 undefined4 param_9)

{
  (*(code *)g_pAnimFrame[3])(param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ---- 0x004c2720  FUN_004c2720 ---- */
void FUN_004c2720(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = (undefined4)(0x1234dc / (longlong)param_2);
  param_1[7] = uVar1;
  param_1[8] = uVar1;
  (*(code *)g_pAnimTimer[4])(*param_1,uVar1);
  (*(code *)g_pAnimTimer[4])(param_1[1],param_1[7]);
  return;
}

/* ---- 0x004c2760  FUN_004c2760 ---- */
void FUN_004c2760(undefined4 *param_1)

{
  param_1[6] = 0;
  (*(code *)g_pAnimTimer[4])(*param_1,param_1[8]);
  return;
}

/* ---- 0x004c2780  FUN_004c2780 ---- */
undefined4 FUN_004c2780(int param_1)

{
  if ((*(int *)(param_1 + 0x68) != 5) && (*(int *)(param_1 + 0x14) == 0)) {
    return 0;
  }
  return 1;
}

/* ---- 0x004c2a70  FUN_004c2a70 ---- */
void FUN_004c2a70(undefined4 param_1,int param_2)

{
  *(int *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + 1;
  return;
}

/* ---- 0x004c2a80  FUN_004c2a80 ---- */
void FUN_004c2a80(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0x6c) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 8) & 1) == 0) {
LAB_004c2abb:
    if (UINT_008d6f24 == 0) goto LAB_004c2adc;
  }
  else if (UINT_008d6f24 == 0) {
    if (6 < *(int *)(param_2 + 0x18)) {
      UINT_008d6f24 = 1;
      if (g_pAnimLipsync != (int *)0x0) {
        (*(code *)g_pAnimLipsync[2])();
      }
      goto LAB_004c2adc;
    }
    goto LAB_004c2abb;
  }
  if ((*(int *)(param_2 + 0x18) < 0) && (UINT_008d6f24 = 0, g_pAnimLipsync != (int *)0x0)) {
    (*(code *)g_pAnimLipsync[3])();
  }
LAB_004c2adc:
  if ((*(int *)(param_2 + 0x18) < 0x14) && (UINT_008d6f24 == 0)) {
    *(int *)(param_2 + 0x18) = *(int *)(param_2 + 0x18) + 1;
  }
  return;
}

/* ---- 0x004c2b00  FUN_004c2b00 ---- */
char * FUN_004c2b00(int param_1)

{
  if (param_1 == 0) {
    return s_Insane_AnimPlay_004f16ac;
  }
  if (param_1 != 1) {
    if (param_1 != 2) {
      return &DAT_004f5a98;
    }
    return s_This_is_the_debugging_interface_f_004f16dc;
  }
  return s_Insane_AnimPlay_Debug_Interface_004f16bc;
}

/* ---- 0x004c2b30  FUN_004c2b30 ---- */
void FUN_004c2b30(uint param_1)

{
  UINT_008d6f20 = param_1;
  return;
}

/* ---- 0x004c2b40  FUN_004c2b40 ---- */
uint FUN_004c2b40(void)

{
  return UINT_008d6f20;
}

/* ---- 0x004c2b50  FUN_004c2b50 ---- */
undefined4 FUN_004c2b50(int *param_1,uint param_2)

{
  PTR_00906c24 = param_1;
  UINT_008d73e0 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_animframe_004f1780,&PTR_FUN_004f1728);
  (*(code *)*PTR_00906c24)(s_ANIMFRAME_insane_004f176c,&PTR_FUN_004f1738);
  (*(code *)*PTR_00906c24)(s_DEBUG_animframe_004f175c,&PTR_FUN_004f1750);
  return 0;
}

/* ---- 0x004c2ba0  FUN_004c2ba0 ---- */
void FUN_004c2ba0(void)

{
  (*(code *)PTR_00906c24[1])(s_ANIMFRAME_insane_004f176c);
  (*(code *)PTR_00906c24[1])(s_LECMODULE_insane_animframe_004f1780);
  (*(code *)PTR_00906c24[1])(s_DEBUG_animframe_004f175c);
  return;
}

/* ---- 0x004c2be0  FUN_004c2be0 ---- */
int FUN_004c2be0(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  
  UINT_00906c20 = (*(code *)PTR_00906c24[2])(s_BITMAP_buffers_004f14a4,UINT_008d73e0);
  PTR_00906c1c = (int *)(*(code *)PTR_00906c24[2])(s_MEMORY_workspace_004f14ec,UINT_008d73e0);
  if (UINT_00906c20 == 0) {
    (*(code *)PTR_00906c24[8])(s_AnimFrame_Module__Cannot_allocat_004f18a8);
    return -1;
  }
  if (PTR_00906c1c == (int *)0x0) {
    (*(code *)PTR_00906c24[8])(s_AnimFrame_Module__Cannot_allocat_004f1874);
    return -1;
  }
  UINT_00906c28 = (*(code *)PTR_00906c24[2])(s_VIRTHERC_debug_004f14dc,UINT_008d73e0);
  UINT_00906c2c = (*(code *)PTR_00906c24[2])(s_VIDEO_display_004f1864,UINT_008d73e0);
  if (UINT_008d77f8 != 0) {
    UINT_008d77f0 =
         (*(code *)*PTR_00906c1c)(UINT_008d77f8,s_C__grimsrc_libs_lecsmush_insane__004f182c,0xcd);
    iVar1 = (UINT_008d77f0 != 0) - 1;
    if (iVar1 != 0) {
      (*(code *)PTR_00906c24[8])(s_AnimFrame_Module__Can_t_allocate_004f17f0,UINT_008d77f8);
      return iVar1;
    }
  }
  if (UINT_008d77fc != 0) {
    UINT_008d77f4 =
         (*(code *)*PTR_00906c1c)(UINT_008d77fc,s_C__grimsrc_libs_lecsmush_insane__004f182c,0xce);
    iVar1 = (UINT_008d77f4 != 0) - 1;
    if (iVar1 != 0) {
      (*(code *)PTR_00906c24[8])(s_AnimFrame_Module__Can_t_allocate_004f17b4,UINT_008d77fc);
      return iVar1;
    }
  }
  puVar4 = &UINT_008d70c0;
  for (iVar1 = 100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  UINT_008d77ec = (*(code *)PTR_00906c24[7])(s_FLOBDEC_004f17ac);
  if (100 < (int)UINT_008d77ec) {
    UINT_008d77ec = 100;
  }
  iVar1 = 0;
  if (0 < (int)UINT_008d77ec) {
    puVar4 = &UINT_008d6f30;
    do {
      iVar2 = (*(code *)PTR_00906c24[6])(s_FLOBDEC_004f17ac,iVar1);
      if (iVar2 != 0) {
        uVar3 = (*(code *)PTR_00906c24[2])(s_FLOBDEC_temp_004f179c,iVar2);
        (&UINT_008d70c0)[iVar1] = uVar3;
        uVar3 = (**(code **)(uVar3 + 4))();
        (&UINT_008d7250)[iVar1] = uVar3;
        uVar3 = (**(code **)((&UINT_008d70c0)[iVar1] + 8))();
        *puVar4 = uVar3;
      }
      iVar1 = iVar1 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar1 < (int)UINT_008d77ec);
  }
  return 0;
}

/* ---- 0x004c2dc0  FUN_004c2dc0 ---- */
void FUN_004c2dc0(void)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  
  (*(code *)PTR_00906c24[3])(UINT_00906c20);
  (*(code *)PTR_00906c24[3])(PTR_00906c1c);
  if (UINT_00906c2c != 0) {
    (*(code *)PTR_00906c24[3])(UINT_00906c2c);
  }
  if (UINT_00906c28 != 0) {
    (*(code *)PTR_00906c24[3])(UINT_00906c28);
  }
  if (UINT_008d77f0 != 0) {
    (*(code *)PTR_00906c1c[1])(UINT_008d77f0,s_C__grimsrc_libs_lecsmush_insane__004f182c,0x100);
    UINT_008d77f0 = 0;
  }
  if (UINT_008d77f4 != 0) {
    (*(code *)PTR_00906c1c[1])(UINT_008d77f4,s_C__grimsrc_libs_lecsmush_insane__004f182c,0x101);
    UINT_008d77f4 = 0;
  }
  iVar3 = 0;
  if (0 < (int)UINT_008d77ec) {
    puVar2 = &UINT_008d70c0;
    do {
      if (*puVar2 != 0) {
        (*(code *)PTR_00906c24[3])(*puVar2);
      }
      uVar1 = UINT_008d77ec;
      *puVar2 = 0;
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar3 < (int)uVar1);
  }
  UINT_008d77ec = 0;
  return;
}

/* ---- 0x004c2eb0  FUN_004c2eb0 ---- */
void FUN_004c2eb0(void)

{
  uint *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < (int)UINT_008d77ec) {
    puVar1 = &UINT_008d70c0;
    do {
      if (*puVar1 != 0) {
        (**(code_std **)(*puVar1 + 0xc))();
      }
      iVar2 = iVar2 + 1;
      puVar1 = puVar1 + 1;
    } while (iVar2 < (int)UINT_008d77ec);
  }
  return;
}

/* ---- 0x004c2ee0  FUN_004c2ee0 ---- */
undefined4 FUN_004c2ee0(undefined1 *param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar3 = UINT_008d77ec;
  while (4 < param_2) {
    iVar5 = 0;
    uVar2 = CONCAT31(CONCAT21(CONCAT11(*param_1,param_1[1]),param_1[2]),param_1[3]);
    bVar1 = param_1[7];
    iVar4 = CONCAT31(CONCAT21(CONCAT11(param_1[4],param_1[5]),param_1[6]),bVar1);
    if (0 < (int)uVar3) {
      do {
        if (((uVar2 != 0) && (uVar2 == (&UINT_008d7250)[iVar5])) && ((&UINT_008d70c0)[iVar5] != 0))
        {
          (**(code **)((&UINT_008d70c0)[iVar5] + 0x10))(param_1 + 8,iVar4);
          uVar3 = UINT_008d77ec;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < (int)uVar3);
    }
    param_1 = param_1 + iVar4 + 8;
    param_2 = param_2 + (-8 - iVar4);
    if ((bVar1 & 1) != 0) {
      param_1 = param_1 + 1;
      param_2 = param_2 + -1;
    }
  }
  return 0;
}

/* ---- 0x004c2fa0  FUN_004c2fa0 ---- */
uint FUN_004c2fa0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 uint *param_5,uint *param_6,uint *param_7,uint param_8,undefined4 param_9,
                 undefined4 param_10,byte *param_11,int param_12)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  bool bVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint *puVar13;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  puVar7 = param_5;
  bVar6 = false;
  local_10 = 0;
  uVar9 = param_8 & 0x30 | param_8 >> 0xd & 4;
  do {
    if (param_12 < 5) {
      if (UINT_008d7804 != 0) {
        param_5 = (uint *)0x100;
        *param_7 = *param_7 | 1;
        puVar13 = puVar7;
        do {
          uVar9 = *puVar13;
          PIECE(param_12,2,1) = (byte)(uVar9 >> 0x10);
          uVar12 = *(uint *)(((int)&DAT_008d73e8 - (int)puVar7) + (int)puVar13);
          PIECE(param_10,0,1) = (char)(uVar9 >> 0x18);
          PIECE(param_7,0,1) = (char)(uVar9 >> 8);
          *puVar13 = CONCAT31(CONCAT21(CONCAT11((char)(((uVar12 >> 0x18) - (uVar9 >> 0x18)) /
                                                      UINT_008d7804) + (char)param_10,
                                                (char)(((uVar12 >> 0x10 & 0xff) -
                                                       (uint)PIECE(param_12,2,1)) / UINT_008d7804) +
                                                PIECE(param_12,2,1)),
                                       (char)(((uVar12 >> 8 & 0xff) - (uVar9 >> 8 & 0xff)) /
                                             UINT_008d7804) + (char)param_7),
                              (char)(((uVar12 & 0xff) - (uVar9 & 0xff)) / UINT_008d7804) +
                              (char)uVar9);
          param_5 = (uint *)((int)param_5 + -1);
          puVar13 = puVar13 + 1;
        } while (param_5 != (uint *)0x0);
        UINT_008d7804 = UINT_008d7804 - 1;
      }
      return local_10;
    }
    bVar1 = *param_11;
    bVar2 = param_11[1];
    bVar3 = param_11[2];
    bVar4 = param_11[3];
    uVar12 = CONCAT31(CONCAT21(CONCAT11(bVar1,bVar2),bVar3),bVar4);
    bVar5 = param_11[7];
    iVar11 = CONCAT31(CONCAT21(CONCAT11(param_11[4],param_11[5]),param_11[6]),bVar5);
    if ((UINT_00906c28 != 0) && ((UINT_008d77e8 & 0x80000) != 0)) {
      (**(code **)(UINT_00906c28 + 0xc))
                (s_Parsing_Block___c_c_c_c____ld__004f191c,bVar1,bVar2,bVar3,bVar4,iVar11);
    }
    uVar10 = 0;
    if (0 < (int)UINT_008d77ec) {
      do {
        if (((uVar12 != 0) && (uVar12 == (&UINT_008d7250)[uVar10])) &&
           ((&UINT_008d70c0)[uVar10] != 0)) {
          if (((bVar6) && (UINT_008d77f0 != 0)) && (((&UINT_008d6f30)[uVar10] & 0x10) != 0)) {
            if (iVar11 + 8U < UINT_008d77f8) {
              Insane_MemCopyCdecl((void *)UINT_008d77f0,param_11,iVar11 + 8U);
              UINT_004f1720 = uVar10;
            }
            else {
              UINT_004f1720 = 0xffffffff;
            }
            bVar6 = false;
          }
          uVar8 = (**(code **)((&UINT_008d70c0)[uVar10] + 0x14))
                            (param_1,param_2,param_3,param_4,param_5,param_11 + 8,iVar11,uVar9,
                             param_9,param_10);
          if ((uVar8 & 1) != 0) {
            *param_6 = *param_6 | 1;
          }
          if ((uVar8 & 2) != 0) {
            *param_7 = *param_7 | 1;
          }
          if ((uVar8 & 4) != 0) {
            *param_7 = *param_7 | 2;
          }
          if ((uVar8 & 0x80) != 0) {
            local_10 = 2;
          }
          break;
        }
        uVar10 = uVar10 + 1;
      } while ((int)uVar10 < (int)UINT_008d77ec);
    }
    if ((int)UINT_008d77ec <= (int)uVar10) {
      if (uVar12 < 0x6c6f6165) {
        if (uVar12 == 0x6c6f6164) {
          FUN_004c34d0(param_11 + 8,iVar11);
        }
        else if (uVar12 == 0x66746368) {
          if ((UINT_008d77f0 != 0) && (-1 < (int)UINT_004f1720)) {
            uVar12 = (**(code **)((&UINT_008d70c0)[UINT_004f1720] + 0x14))
                               (param_1,param_2,param_3,param_4,param_5,UINT_008d77f0 + 8,
                                CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(UINT_008d77f0 + 4),
                                                           *(undefined1 *)(UINT_008d77f0 + 5)),
                                                  *(undefined1 *)(UINT_008d77f0 + 6)),
                                         *(undefined1 *)(UINT_008d77f0 + 7)),uVar9,param_9,param_10)
            ;
            if ((uVar12 & 1) != 0) {
              *param_6 = *param_6 | 1;
            }
            if ((uVar12 & 2) != 0) {
              *param_7 = *param_7 | 1;
            }
            if ((uVar12 & 4) != 0) {
              *param_7 = *param_7 | 2;
            }
          }
        }
        else {
LAB_004c3182:
          if ((UINT_00906c28 != 0) && ((UINT_008d77e8 & 0x40000) != 0)) {
            (**(code **)(UINT_00906c28 + 0xc))
                      (s_Found_Unknown_Block___c_c_c_c__004f18fc,param_11[4],param_11[5],param_11[6]
                       ,param_11[7]);
          }
          if (((((bVar4 < 0x30) || (0x7a < bVar4)) || (bVar3 < 0x30)) ||
              ((0x7a < bVar3 || (bVar2 < 0x30)))) ||
             ((0x7a < bVar2 || ((bVar1 < 0x30 || (0x7a < bVar1)))))) {
            if ((UINT_00906c28 != 0) && ((UINT_008d77e8 & 0x20000) != 0)) {
              (**(code **)(UINT_00906c28 + 0xc))
                        (s_Bad_Header_Found___c_c_c_c__004f18dc,param_11[4],param_11[5],param_11[6],
                         param_11[7]);
            }
            return local_10 | 0x8000;
          }
        }
      }
      else if (uVar12 == 0x6e70616c) {
        if (*(short *)(param_11 + 0x14) == 0) {
          Insane_MemCopyCdecl(param_5 + *(short *)(param_11 + 0x16) * 4,param_11 + 0x1c,
                              (int)*(short *)(param_11 + 0x18) << 2);
          *param_7 = *param_7 | *(uint *)(param_11 + 0x10);
          UINT_008d7804 = 0;
        }
        else {
          Insane_MemCopyCdecl(&DAT_008d73e8,param_5,0x400);
          Insane_MemCopyCdecl(&DAT_008d73e8 + *(short *)(param_11 + 0x16) * 0x10,param_11 + 0x1c,
                              (int)*(short *)(param_11 + 0x18) << 2);
          UINT_008d7804 = (uint)*(short *)(param_11 + 0x14);
        }
      }
      else {
        if (uVar12 != 0x73746f72) goto LAB_004c3182;
        bVar6 = true;
      }
    }
    param_11 = param_11 + 8 + iVar11;
    param_12 = param_12 + (-8 - iVar11);
    if ((bVar5 & 1) != 0) {
      param_11 = param_11 + 1;
      param_12 = param_12 + -1;
    }
  } while( true );
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004c34d0  FUN_004c34d0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004c34d0(short *param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = (uint)param_1[1];
  if (uVar2 == 0) {
    UINT_004f1724 = 8;
    UINT_008d7800 = 0;
    UINT_008d7808 = 0xffffffff;
    _DAT_008d780c = (int)*param_1;
  }
  uVar1 = UINT_008d7808;
  if ((uVar2 == UINT_008d7808 + 1) &&
     (uVar1 = uVar2, (int)(param_2 + UINT_008d7800) < (int)UINT_008d77fc)) {
    Insane_MemCopyCdecl((void *)(UINT_008d7800 + UINT_008d77f4),param_1 + 5,param_2 - 10);
    UINT_008d7800 = (UINT_008d7800 - 10) + param_2;
  }
  UINT_008d7808 = uVar1;
  return;
}

/* ---- 0x004c3560  FUN_004c3560 ---- */
int FUN_004c3560(int param_1)

{
  if (param_1 < 0) {
    if ((int)(UINT_004f1724 - param_1) <= (int)UINT_008d7800) {
      return (UINT_004f1724 + UINT_008d77f4) - param_1;
    }
  }
  else {
    UINT_004f1724 = UINT_004f1724 + param_1;
    if ((int)UINT_004f1724 <= (int)UINT_008d7800) {
      return (UINT_004f1724 + UINT_008d77f4) - param_1;
    }
    UINT_004f1724 = 8;
  }
  return 0;
}

/* ---- 0x004c35c0  FUN_004c35c0 ---- */
void FUN_004c35c0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,byte param_6,byte param_7,uint param_8)

{
  int iVar1;
  
  if ((UINT_00906c2c != 0) && ((param_7 & 2) != 0)) {
    if (param_1 != 0) {
      iVar1 = (**(code **)(UINT_00906c2c + 4))();
      if (*(int *)(iVar1 + 0x20) != 0) goto LAB_004c360c;
    }
    if ((param_8 & 0x2000) == 0) {
      (**(code **)(UINT_00906c2c + 0x18))(0,0,0x100);
    }
  }
LAB_004c360c:
  if ((((param_6 & 1) != 0) && ((param_8 & 0x4000) == 0)) && (UINT_00906c2c != 0)) {
    (**(code **)(UINT_00906c2c + 8))(param_1,param_3,param_4,param_2);
  }
  if ((((param_7 & 1) != 0) && ((param_8 & 0x2000) == 0)) && (UINT_00906c2c != 0)) {
    (**(code **)(UINT_00906c2c + 0x10))(param_5);
  }
  return;
}

/* ---- 0x004c3660  FUN_004c3660 ---- */
char * FUN_004c3660(int param_1)

{
  if (param_1 == 0) {
    return s_Insane_AnimFrame_004f193c;
  }
  if (param_1 != 1) {
    if (param_1 != 2) {
      return &DAT_004f5a98;
    }
    return s_This_is_the_debugging_interface_f_004f1974;
  }
  return s_Insane_AnimFrame_Debug_Interface_004f1950;
}

/* ---- 0x004c3690  FUN_004c3690 ---- */
void FUN_004c3690(uint param_1)

{
  UINT_008d77e8 = param_1;
  return;
}

/* ---- 0x004c36a0  FUN_004c36a0 ---- */
uint FUN_004c36a0(void)

{
  return UINT_008d77e8;
}

/* ---- 0x004c36f0  FUN_004c36f0 ---- */
uint FUN_004c36f0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11)

{
  uint uVar1;
  undefined1 *puVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0x54) != 0) {
    *(undefined4 *)(param_1 + 0x54) = 0;
    return 0xffffffff;
  }
LAB_004c371b:
  uVar1 = *(uint *)(param_1 + 0x34);
  if (uVar1 < 0x464c4845) {
    if (uVar1 == 0x464c4844) {
      FUN_004c3b30(param_1,*(undefined4 *)(param_1 + 0x30));
      iVar3 = *(int *)(param_1 + 0x24);
      if (iVar3 == -1) {
        return 5;
      }
      if (iVar3 == -2) {
        return 0xfffffffe;
      }
      (*(code *)g_pAnimFrame[1])(iVar3,*(undefined4 *)(param_1 + 0x30));
      *(undefined4 *)(param_1 + 0x34) = 0x6e756c6c;
      goto LAB_004c371b;
    }
    if (uVar1 == 0x414e4e4f) {
      FUN_004c3b30(param_1,*(undefined4 *)(param_1 + 0x30));
      if (*(int *)(param_1 + 0x24) == -1) {
        return 5;
      }
      if (*(int *)(param_1 + 0x24) == -2) {
        return 0xfffffffe;
      }
      *(undefined4 *)(param_1 + 0x34) = 0x6e756c6c;
      goto LAB_004c371b;
    }
  }
  else {
    if (uVar1 < 0x53484453) {
      if (uVar1 == 0x53484452) {
        FUN_004c3b30(param_1,*(undefined4 *)(param_1 + 0x30));
        iVar3 = *(int *)(param_1 + 0x24);
        if (iVar3 == -1) {
          return 5;
        }
        if (iVar3 == -2) {
          return 0xfffffffe;
        }
        *(undefined4 *)(param_1 + 0x34) = 0x6e756c6c;
        if (iVar3 != 0) {
          FUN_004c3c90(param_1,iVar3,param_6,param_8);
        }
      }
      else {
        if (uVar1 != 0x46524d45) goto LAB_004c3a66;
        FUN_004c3b30(param_1,*(undefined4 *)(param_1 + 0x30));
        iVar3 = *(int *)(param_1 + 0x24);
        if (iVar3 == -1) {
          return 5;
        }
        if (iVar3 == -2) {
          return 0xfffffffe;
        }
        *(undefined4 *)(param_1 + 0x34) = 0x6e756c6c;
        if (iVar3 != 0) {
          *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
          if ((*(int *)(param_1 + 0x44) != 0) || (iVar3 = FUN_004c3bb0(param_1), iVar3 == 0)) {
            FUN_004c3c00(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         param_10,param_11);
            if ((*(int *)(param_1 + 0x28) < *(int *)(param_1 + 0x2c) + -1) ||
               (*(int *)(param_1 + 0x44) != 0)) {
              if (*(int *)(param_1 + 0x58) == 1) {
                *(undefined4 *)(param_1 + 0x34) = 0x70617773;
              }
              else if (*(int *)(param_1 + 0x58) == 3) {
                *(undefined4 *)(param_1 + 0x58) = 1;
              }
            }
            else {
              iVar3 = (*(code *)g_pAnimStreamer[3])(*(undefined4 *)(param_1 + 0x60));
              if ((iVar3 == 0) && (*(int *)(param_1 + 0x40) == 0)) {
                *(undefined4 *)(param_1 + 0x34) = 0x656e6420;
              }
              else {
                *(undefined4 *)(param_1 + 0x34) = 0x6e756c6c;
              }
            }
            if (*(int *)(param_1 + 0x44) != 0) {
              return 2;
            }
            if (*(int *)(param_1 + 0x28) < 10) {
              return 1;
            }
            return (*(int *)(param_1 + 0x28) < *(int *)(param_1 + 0x2c) + -1) - 1 & 4;
          }
          if (*(int *)(param_1 + 0x2c) + -1 <= *(int *)(param_1 + 0x28)) {
            iVar3 = (*(code *)g_pAnimStreamer[3])(*(undefined4 *)(param_1 + 0x60));
            if ((iVar3 == 0) && (*(int *)(param_1 + 0x40) == 0)) {
              *(undefined4 *)(param_1 + 0x34) = 0x656e6420;
            }
            else {
              *(undefined4 *)(param_1 + 0x34) = 0x6e756c6c;
            }
          }
        }
      }
      goto LAB_004c371b;
    }
    if (0x6e756c6c < uVar1) {
      if (uVar1 == 0x70617773) {
        FUN_004c3c00(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                     param_10,param_11);
        if (*(int *)(param_1 + 0x58) != 1) {
          if (*(int *)(param_1 + 0x58) == 3) {
            *(undefined4 *)(param_1 + 0x58) = 1;
          }
          *(undefined4 *)(param_1 + 0x34) = 0x6e756c6c;
        }
        return 3;
      }
      if (uVar1 == 0x77616974) {
        iVar3 = (*(code *)g_pAnimStreamer[3])(*(undefined4 *)(param_1 + 0x60));
        if (iVar3 == 0) {
          if (*(int *)(param_1 + 0x40) == 0) {
            return 5;
          }
          iVar3 = (*(code *)g_pAnimFrame[5])(0xfffffff8);
          if (iVar3 == 0) {
            return 5;
          }
        }
        *(undefined4 *)(param_1 + 0x34) = 0x6e756c6c;
        return 5;
      }
      goto LAB_004c3a66;
    }
    if (uVar1 == 0x6e756c6c) {
      if (*(int *)(param_1 + 0x40) != 0) {
        *(undefined4 *)(param_1 + 0x40) = 0;
        *(undefined4 *)(param_1 + 0x44) = 1;
      }
      FUN_004c3b30(param_1,8);
      puVar2 = *(undefined1 **)(param_1 + 0x24);
      if (puVar2 == (undefined1 *)0xffffffff) {
        return 5;
      }
      if (puVar2 == (undefined1 *)0xfffffffe) {
        return 0xfffffffe;
      }
      if (puVar2 != (undefined1 *)0x0) {
        *(uint *)(param_1 + 0x34) =
             CONCAT31(CONCAT21(CONCAT11(*puVar2,puVar2[1]),puVar2[2]),puVar2[3]);
        *(uint *)(param_1 + 0x30) =
             CONCAT31(CONCAT21(CONCAT11(puVar2[4],puVar2[5]),puVar2[6]),puVar2[7]) + 1U & 0xfffffffe
        ;
      }
      goto LAB_004c371b;
    }
    if (uVar1 == 0x656e6420) {
      *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
      iVar3 = FUN_004c3bb0(param_1);
      if (iVar3 == 0) {
        FUN_004c3c00(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                     param_10,param_11);
      }
      iVar3 = (*(code *)g_pAnimStreamer[3])(*(undefined4 *)(param_1 + 0x60));
      if ((iVar3 != 0) ||
         ((*(int *)(param_1 + 0x40) != 0 &&
          (iVar3 = (*(code *)g_pAnimFrame[5])(0xfffffff8), iVar3 != 0)))) {
        *(undefined4 *)(param_1 + 0x34) = 0x6e756c6c;
      }
      return 4;
    }
  }
LAB_004c3a66:
  uVar1 = *(uint *)(param_1 + 0x34);
  (*(code *)PTR_00906c40[8])
            (s_Read_invalid_frame_header__c_c_c_004f19bc,uVar1 >> 0x18,uVar1 >> 0x10,uVar1 >> 8,
             uVar1);
  return 0xfffffffe;
}

/* ---- 0x004c3b30  FUN_004c3b30 ---- */
void FUN_004c3b30(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x44) == 0) {
    iVar2 = (*(code *)g_pAnimStreamer[5])(*(undefined4 *)(param_1 + 0x60),param_2);
    *(int *)(param_1 + 0x24) = iVar2;
    if ((iVar2 != -1) && (iVar2 == 0)) {
      *(undefined4 *)(param_1 + 0x28) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x38) = 0;
    }
  }
  else {
    uVar1 = (*(code *)g_pAnimFrame[5])(param_2);
    *(undefined4 *)(param_1 + 0x24) = uVar1;
    (*(code *)g_pAnimStreamer[5])(*(undefined4 *)(param_1 + 0x60),0xffffffff);
    if (*(int *)(param_1 + 0x24) == 0) {
      *(undefined4 *)(param_1 + 0x44) = 0;
      *(undefined4 *)(param_1 + 0x50) = 0;
      *(undefined4 *)(param_1 + 0x4c) = 0;
      *(undefined4 *)(param_1 + 0x34) = 0x77616974;
      return;
    }
  }
  return;
}

/* ---- 0x004c3bb0  FUN_004c3bb0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004c3bb0(int param_1)

{
  if (*(int *)(param_1 + 0x44) == 0) {
    if (*(int *)(param_1 + 0x38) == 0) {
      if (-1 < *(int *)(param_1 + 0x48)) {
        if (*(int *)(param_1 + 0x28) < *(int *)(param_1 + 0x48)) {
          return 1;
        }
        *(undefined4 *)(param_1 + 0x48) = 0xffffffff;
      }
    }
    else if ((-1 < *(int *)(param_1 + 0x50)) &&
            (*(int *)(param_1 + 0x4c) + *(int *)(param_1 + 0x50) < *(int *)(param_1 + 0x28))) {
      return 1;
    }
    _DAT_008d7810 = *(undefined4 *)(param_1 + 0x28);
  }
  return 0;
}

/* ---- 0x004c3c00  FUN_004c3c00 ---- */
undefined4
FUN_004c3c00(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6,undefined4 param_7,undefined4 param_8,uint param_9,
            undefined4 param_10,undefined4 param_11)

{
  uint uVar1;
  
  if (((param_9 | *(uint *)(param_1 + 0xc)) & 4) == 0) {
    FUN_004ce9b0(param_2,0);
  }
  uVar1 = (*(code *)g_pAnimFrame[2])
                    (param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     param_9 | *(uint *)(param_1 + 0xc),param_10,param_11,
                     *(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x30));
  if ((uVar1 & 1) != 0) {
    FUN_004c3d10(param_1);
  }
  if ((uVar1 & 2) != 0) {
    (*(code *)PTR_FUN_004f131c)(param_1);
  }
  return 0;
}

/* ---- 0x004c3c90  FUN_004c3c90 ---- */
void FUN_004c3c90(int param_1,int param_2,void *param_3,uint *param_4)

{
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0x3c);
  if ((*(uint *)(param_1 + 0x3c) & 0x2000) == 0) {
    Insane_MemCopyCdecl(param_3,(void *)(param_2 + 0x16),0x400);
    *param_4 = *param_4 | 3;
  }
  *(int *)(param_1 + 0x2c) = (int)*(short *)(param_2 + 2);
  if ((*(int *)(param_2 + 0xe) != 0) && ((*(byte *)(param_1 + 0xc) & 8) == 0)) {
    (*(code *)PTR_FUN_004f1318)(param_1,(int)(1000000 / (longlong)*(int *)(param_2 + 0xe)));
    (*(code *)PTR_FUN_004f131c)(param_1);
  }
  return;
}

/* ---- 0x004c3d00  FUN_004c3d00 ---- */
undefined4 FUN_004c3d00(int param_1)

{
  return *(undefined4 *)(param_1 + 0x38);
}

/* ---- 0x004c3d10  FUN_004c3d10 ---- */
void FUN_004c3d10(int param_1)

{
  (*(code *)*g_pAnimFrame)();
  *(undefined4 *)(param_1 + 0x54) = 1;
  return;
}

/* ---- 0x004c3d90  FUN_004c3d90 ---- */
void FUN_004c3d90(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x50) = param_2;
  return;
}

/* ---- 0x004c3db0  FUN_004c3db0 ---- */
uint FUN_004c3db0(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == 2) {
    uVar1 = (uint)(*(int *)(param_1 + 0x58) == 0);
    *(uint *)(param_1 + 0x58) = uVar1;
    return uVar1;
  }
  if (param_2 == 4) {
    if (*(int *)(param_1 + 0x58) != 0) {
      *(undefined4 *)(param_1 + 0x58) = 3;
      return *(uint *)(param_1 + 0x58);
    }
  }
  else if (param_2 != 5) {
    *(int *)(param_1 + 0x58) = param_2;
  }
  return *(uint *)(param_1 + 0x58);
}

/* ---- 0x004c4650  FUN_004c4650 ---- */
uint FUN_004c4650(int param_1,undefined4 param_2)

{
  uint uVar1;
  
  uVar1 = gz_do_flush(param_1,param_2);
  if (uVar1 == 0) {
    (*(code *)g_pZfileFileIo[6])(*(undefined4 *)(param_1 + 0x40));
    uVar1 = -(uint)(*(uint *)(param_1 + 0x38) != 1) & *(uint *)(param_1 + 0x38);
  }
  return uVar1;
}

/* ---- 0x004c4a00  FUN_004c4a00 ---- */
undefined * FUN_004c4a00(int param_1,int *param_2)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  
  if (param_1 == 0) {
    *param_2 = -2;
    return PTR_s_stream_error_004f1f58;
  }
  iVar5 = *(int *)(param_1 + 0x38);
  *param_2 = iVar5;
  if (iVar5 == 0) {
    return &DAT_004f5a98;
  }
  pcVar6 = &DAT_004f5a98;
  if (iVar5 != -1) {
    pcVar6 = *(char **)(param_1 + 0x18);
  }
  if ((pcVar6 == (char *)0x0) || (*pcVar6 == '\0')) {
    pcVar6 = (&PTR_DAT_004f1f50)[-*(int *)(param_1 + 0x38)];
  }
  if (*(int *)(param_1 + 0x50) != 0) {
    free(*(int *)(param_1 + 0x50));
  }
  uVar3 = 0xffffffff;
  pcVar2 = pcVar6;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  uVar4 = 0xffffffff;
  pcVar2 = *(char **)(param_1 + 0x54);
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = malloc(~uVar3 + ~uVar4 + 1);
  uVar3 = 0xffffffff;
  *(char **)(param_1 + 0x50) = pcVar2;
  pcVar7 = *(char **)(param_1 + 0x54);
  do {
    pcVar8 = pcVar7;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar7 = pcVar8 + -uVar3;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar2 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar2 = pcVar2 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar2 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar2 = pcVar2 + 1;
  }
  uVar3 = 0xffffffff;
  pcVar2 = &DAT_004f1a28;
  do {
    pcVar7 = pcVar2;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar7 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar7;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar5 = -1;
  pcVar2 = *(char **)(param_1 + 0x50);
  do {
    pcVar8 = pcVar2;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar8 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar8;
  } while (cVar1 != '\0');
  pcVar2 = pcVar7 + -uVar3;
  pcVar7 = pcVar8 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar7 = pcVar7 + 1;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar2 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar2 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar2;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar5 = -1;
  pcVar6 = *(char **)(param_1 + 0x50);
  do {
    pcVar7 = pcVar6;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  pcVar6 = pcVar2 + -uVar3;
  pcVar2 = pcVar7 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar2 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar2 = pcVar2 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar2 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar2 = pcVar2 + 1;
  }
  return *(undefined **)(param_1 + 0x50);
}

/* ---- 0x004c4b20  FUN_004c4b20 ---- */
undefined4 FUN_004c4b20(int *param_1,uint param_2)

{
  PTR_008d7818 = param_1;
  UINT_008d7820 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_streamer_004f1a7c,&PTR_FUN_004f1a30);
  (*(code *)*PTR_008d7818)(s_STREAMER_insane_streamer_004f1a60,&PTR_FUN_004f1a40);
  return 0;
}

/* ---- 0x004c4b60  FUN_004c4b60 ---- */
void FUN_004c4b60(void)

{
  (*(code *)PTR_008d7818[1])(s_STREAMER_insane_streamer_004f1a60);
  (*(code *)PTR_008d7818[1])(s_LECMODULE_insane_streamer_004f1a7c);
  return;
}

/* ---- 0x004c4b90  FUN_004c4b90 ---- */
undefined4 FUN_004c4b90(void)

{
  PTR_008d7814 = (int *)(*(code *)PTR_008d7818[2])(s_MEMORY_workspace_004f14ec,UINT_008d7820);
  PTR_008d781c = (int *)(*(code *)PTR_008d7818[2])(s_FILIO_io_004f1b00,UINT_008d7820);
  if (PTR_008d7814 == (int *)0x0) {
    (*(code *)PTR_008d7818[8])(s_Streamer_Module__Cannot_allocate_004f1acc);
    return 0xffffffff;
  }
  if (PTR_008d781c == (int *)0x0) {
    (*(code *)PTR_008d7818[8])(s_Streamer_Module__Cannot_allocate_004f1a98);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004c4c10  FUN_004c4c10 ---- */
void FUN_004c4c10(void)

{
  (*(code *)PTR_008d7818[3])(PTR_008d7814);
  (*(code *)PTR_008d7818[3])(PTR_008d781c);
  return;
}

/* ---- 0x004c4c50  FUN_004c4c50 ---- */
int FUN_004c4c50(undefined4 *param_1,uint param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar1 = (undefined4 *)
           (*(code *)*PTR_008d7814)(0x110,s_C__grimsrc_libs_lecsmush_insane__004f1b0c,0xd5);
  iVar3 = (puVar1 != (undefined4 *)0x0) - 1;
  if (iVar3 == 0) {
    puVar1[0x43] = 0;
    puVar2 = (undefined4 *)
             (*(code *)*PTR_008d7814)
                       (param_3 + param_2,s_C__grimsrc_libs_lecsmush_insane__004f1b0c,0xd9);
    *puVar1 = puVar2;
    iVar3 = (puVar2 != (undefined4 *)0x0) - 1;
    if (iVar3 == 0) {
      param_2 = param_2 & 0xfffff800;
      puVar1[3] = param_3;
      puVar1[2] = param_2;
      puVar1[0xc] = 0;
      puVar1[0x41] = 0;
      puVar1[1] = (undefined1 *)(param_2 + (int)puVar2);
      puVar1[0x42] = 0;
      for (param_2 = param_2 >> 2; param_2 != 0; param_2 = param_2 - 1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
      for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined1 *)puVar2 = 0;
        puVar2 = (undefined4 *)((int)puVar2 + 1);
      }
      *param_1 = puVar1;
      return 0;
    }
    if (puVar1 != (undefined4 *)0x0) {
      (*(code *)PTR_008d7814[1])(puVar1,s_C__grimsrc_libs_lecsmush_insane__004f1b0c,0xe8);
    }
  }
  return iVar3;
}

/* ---- 0x004c4d20  FUN_004c4d20 ---- */
void FUN_004c4d20(int *param_1)

{
  int *piVar1;
  
  if (param_1 != (int *)0x0) {
    piVar1 = (int *)*param_1;
    if (piVar1[0xc] != 0) {
      (*(code *)PTR_008d781c[1])(piVar1[0xc]);
      piVar1[0xc] = 0;
    }
    if (*piVar1 != 0) {
      (*(code *)PTR_008d7814[1])(*piVar1,s_C__grimsrc_libs_lecsmush_insane__004f1b0c,0x101);
    }
    *piVar1 = 0;
    if (*param_1 != 0) {
      (*(code *)PTR_008d7814[1])(*param_1,s_C__grimsrc_libs_lecsmush_insane__004f1b0c,0x102);
    }
    *param_1 = 0;
  }
  return;
}

/* ---- 0x004c4d90  FUN_004c4d90 ---- */
void FUN_004c4d90(undefined4 *param_1)

{
  param_1[5] = 0;
  param_1[9] = *param_1;
  param_1[10] = *param_1;
  param_1[6] = 0;
  param_1[0xb] = 0;
  param_1[8] = 0;
  if (param_1[0xc] != 0) {
    (*(code *)PTR_008d781c[1])(param_1[0xc]);
    param_1[0xc] = 0;
  }
  param_1[4] = 0;
  return;
}

/* ---- 0x004c4dd0  FUN_004c4dd0 ---- */
void FUN_004c4dd0(uint *param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = FUN_004c4f60(param_1);
  if (param_1[0xc] == 0) {
    return;
  }
  if ((int)param_1[0xe] <= (int)param_1[0xd]) {
    return;
  }
  uVar4 = param_1[10];
  uVar3 = param_1[9];
  if (uVar3 < uVar4) {
    if (uVar4 == *param_1) goto LAB_004c4e1a;
  }
  else {
    if (uVar4 != *param_1) {
      uVar4 = param_1[1] - uVar3;
      goto LAB_004c4e49;
    }
LAB_004c4e1a:
    if (0x800 < (int)(param_1[1] - uVar3)) {
      uVar4 = (param_1[1] - uVar3) - 0x800;
      goto LAB_004c4e49;
    }
  }
  uVar4 = (uVar4 - uVar3) - 0x800 & 0xfffff800;
  if ((int)uVar4 < 0x800) {
    return;
  }
LAB_004c4e49:
  if (iVar1 == 0) {
    param_2 = param_1[3];
  }
  if ((int)param_2 < (int)uVar4) {
    uVar4 = param_2;
  }
  uVar2 = param_1[0xe] - param_1[0xd];
  if ((int)uVar4 <= (int)uVar2) {
    uVar2 = uVar4;
  }
  uVar3 = (*(code *)PTR_008d781c[2])(param_1[0xc],uVar3,uVar2);
  if (uVar3 == uVar2) {
    uVar3 = uVar4 + param_1[9];
    param_1[0xd] = param_1[0xd] + uVar4;
    if (param_1[1] <= uVar3) {
      uVar3 = uVar3 - param_1[2];
    }
    param_1[9] = uVar3;
    if (param_1[5] != 0) {
      param_1[6] = 1;
      return;
    }
  }
  else {
    (*(code *)PTR_008d781c[5])(param_1[0xc],param_1[0xd],0);
    if ((code *)param_1[0x43] != (code *)0x0) {
      (*(code *)param_1[0x43])(0,0);
    }
  }
  return;
}

/* ---- 0x004c4ee0  FUN_004c4ee0 ---- */
undefined4 FUN_004c4ee0(int param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  if (param_2 == (char *)0x0) {
    *(undefined1 *)(param_1 + 0x3c) = 0;
  }
  else {
    iVar2 = (*(code *)*PTR_008d781c)(param_2,&DAT_004ddb18);
    if (iVar2 == 0) {
      return 0xffffffff;
    }
    (*(code *)PTR_008d781c[1])(iVar2);
    uVar3 = 0xffffffff;
    do {
      pcVar5 = param_2;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar5 = param_2 + 1;
      cVar1 = *param_2;
      param_2 = pcVar5;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar5 = pcVar5 + -uVar3;
    pcVar6 = (char *)(param_1 + 0x3c);
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
  }
  *(undefined4 *)(param_1 + 0x104) = param_3;
  *(undefined4 *)(param_1 + 0x108) = 1;
  return 0;
}

/* ---- 0x004c4f60  FUN_004c4f60 ---- */
undefined4 FUN_004c4f60(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = 0xffffffff;
  if (*(int *)(param_1 + 0x108) != 0) {
    iVar1 = param_1 + 0x3c;
    if (*(char *)(param_1 + 0x3c) != '\0') {
      iVar3 = (*(code *)*PTR_008d781c)(iVar1,&DAT_004ddb18);
      while (iVar3 == 0) {
        if ((*(code **)(param_1 + 0x10c) == (code *)0x0) ||
           (iVar3 = (**(code **)(param_1 + 0x10c))(1,iVar1), iVar3 != 0)) {
          *(undefined4 *)(param_1 + 0x108) = 0;
          return 0xfffffffe;
        }
        iVar3 = (*(code *)*PTR_008d781c)(iVar1,&DAT_004ddb18);
      }
      if (*(int *)(param_1 + 0x30) != 0) {
        (*(code *)PTR_008d781c[1])(*(int *)(param_1 + 0x30));
        *(undefined4 *)(param_1 + 0x30) = 0;
      }
      *(int *)(param_1 + 0x30) = iVar3;
      (*(code *)PTR_008d781c[5])(iVar3,0,2);
      uVar2 = (*(code *)PTR_008d781c[4])(*(undefined4 *)(param_1 + 0x30));
      *(undefined4 *)(param_1 + 0x38) = uVar2;
    }
    (*(code *)PTR_008d781c[5])
              (*(undefined4 *)(param_1 + 0x30),*(uint *)(param_1 + 0x104) & 0xfffff800,0);
    *(uint *)(param_1 + 0x20) = *(uint *)(param_1 + 0x104) & 0x7ff;
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x10);
    *(uint *)(param_1 + 0x34) = *(uint *)(param_1 + 0x104) & 0xfffff800;
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x14) = 1;
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 *)(param_1 + 0x108) = 0;
    uVar2 = 0;
  }
  return uVar2;
}

/* ---- 0x004c5080  FUN_004c5080 ---- */
undefined4 FUN_004c5080(int param_1)

{
  if ((*(int *)(param_1 + 0x18) != 0) && (*(int *)(param_1 + 0x14) != 0)) {
    return 1;
  }
  return 0;
}

/* ---- 0x004c50a0  FUN_004c50a0 ---- */
int FUN_004c50a0(undefined4 *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  if ((param_1[4] == 0) && (param_1[0xc] != 0)) {
    if ((int)param_1[3] < param_2) {
      (*(code *)PTR_008d7818[8])(s_File_Streamer__Invalid_frame_siz_004f1b44,param_2);
      return -2;
    }
    if (UINT_008d7824 == 0) {
      uVar2 = param_1[10] + param_1[0xb];
      param_1[10] = uVar2;
      param_1[0xb] = 0;
      if ((uint)param_1[1] <= uVar2) {
        param_1[10] = uVar2 - param_1[2];
      }
      UINT_008d7824 = 1;
    }
    if (param_2 < 0) {
      if (param_1[5] != 0) {
        param_1[0xb] = 0;
        param_1[10] = param_1[7];
      }
      UINT_008d7824 = 0;
      return -1;
    }
    if (param_1[5] != 0) {
      FUN_004c51b0(param_1);
      UINT_008d7824 = 0;
      return 0;
    }
    if (param_1[8] != 0) {
      param_2 = param_2 + param_1[8];
    }
    iVar1 = FUN_004c51e0(param_1,param_2);
    if (iVar1 != 0) {
      UINT_008d7824 = 0;
      param_1[0xb] = param_2;
      uVar2 = (param_2 + param_1[10]) - (int)param_1[1];
      if (0 < (int)uVar2) {
        Insane_MemCopyCdecl((void *)param_1[1],(void *)*param_1,uVar2);
      }
      if ((param_1[5] == 0) && (iVar1 = param_1[8], iVar1 != 0)) {
        param_1[8] = 0;
        return iVar1 + param_1[10];
      }
      return param_1[10];
    }
  }
  return -1;
}

/* ---- 0x004c51b0  FUN_004c51b0 ---- */
undefined4 FUN_004c51b0(int param_1)

{
  if (*(int *)(param_1 + 0x14) != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x1c);
    *(undefined4 *)(param_1 + 0x2c) = 0;
    return 0;
  }
  return 0xffffffff;
}

/* ---- 0x004c51e0  FUN_004c51e0 ---- */
undefined4 FUN_004c51e0(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x28);
  uVar2 = *(uint *)(param_1 + 0x24);
  if (uVar2 < uVar1) {
    if (param_2 + uVar1 <= *(int *)(param_1 + 8) + uVar2) {
      return 1;
    }
  }
  else if (param_2 + uVar1 <= uVar2) {
    return 1;
  }
  return 0;
}

/* ---- 0x004c5220  FUN_004c5220 ---- */
int FUN_004c5220(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  if (*(int *)(param_1 + 0x30) == 0) {
    return 100;
  }
  if (*(int *)(param_1 + 0x38) + -0x800 <= *(int *)(param_1 + 0x34)) {
    return 100;
  }
  uVar1 = *(uint *)(param_1 + 0x28);
  uVar2 = *(uint *)(param_1 + 0x24);
  if (uVar1 <= uVar2) {
    return (int)((uVar2 - uVar1) * 100) / *(int *)(param_1 + 8);
  }
  return (int)(((*(int *)(param_1 + 8) - uVar1) + uVar2) * 100) / *(int *)(param_1 + 8);
}

/* ---- 0x004c5280  FUN_004c5280 ---- */
undefined4 FUN_004c5280(int *param_1,uint param_2)

{
  PTR_008d782c = param_1;
  UINT_008d7830 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_directory_004f1bc0,&PTR_FUN_004f1b70);
  (*(code *)*PTR_008d782c)(s_DIRECTORY_insane_directory_004f1ba4,&PTR_FUN_004f1b80);
  return 0;
}

/* ---- 0x004c52c0  FUN_004c52c0 ---- */
void FUN_004c52c0(void)

{
  (*(code *)PTR_008d782c[1])(s_DIRECTORY_insane_directory_004f1ba4);
  (*(code *)PTR_008d782c[1])(s_LECMODULE_insane_directory_004f1bc0);
  return;
}

/* ---- 0x004c52f0  FUN_004c52f0 ---- */
undefined4 FUN_004c52f0(void)

{
  UINT_008d7828 = (*(code *)PTR_008d782c[2])(s_FILE_io_004f1c10,UINT_008d7830);
  if (UINT_008d7828 == 0) {
    (*(code *)PTR_008d782c[8])(s_Directory_Module__Cannot_allocat_004f1bdc);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004c5330  FUN_004c5330 ---- */
void FUN_004c5330(void)

{
  (*(code *)PTR_008d782c[3])(UINT_008d7828);
  return;
}

/* ---- 0x004c5350  FUN_004c5350 ---- */
void FUN_004c5350(undefined4 param_1,undefined4 *param_2)

{
  FUN_004d5740(param_1);
  *param_2 = 1;
  return;
}

/* ---- 0x004c5370  FUN_004c5370 ---- */
void FUN_004c5370(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_004d56f0();
  *param_1 = uVar1;
  return;
}

/* ---- 0x004c5380  FUN_004c5380 ---- */
int FUN_004c5380(int param_1)

{
  unsigned char _frame[0x150] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_140 (*(undefined1 (*)[320])(_frame + (0x150 - 0x140)))
  
  iVar1 = FindFirstFileA(param_1,(int)local_140);
  return iVar1 != -1;
}
#undef local_140


/* ---- 0x004c53b0  FUN_004c53b0 ---- */
void FUN_004c53b0(undefined4 param_1,undefined4 param_2)

{
  FUN_004d57c0(param_1,param_2);
  return;
}

/* ---- 0x004c53d0  FUN_004c53d0 ---- */
void FUN_004c53d0(undefined4 param_1)

{
  FUN_004d5800(param_1);
  return;
}

/* ---- 0x004c53e0  FUN_004c53e0 ---- */
int FUN_004c53e0(undefined4 param_1,int param_2,int param_3,undefined4 param_4,byte param_5)

{
  unsigned char _frame[0x260] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  #define local_24c (*(byte (*)[44])(_frame + (0x260 - 0x24c)))
  #define local_220 (*(char (*)[276])(_frame + (0x260 - 0x220)))
  #define local_10c (*(char (*)[268])(_frame + (0x260 - 0x10c)))
  
  iVar3 = 0;
  sprintf(local_10c,&DAT_004e7af8,param_1,param_4);
  if (((param_5 & 1) == 0) &&
     (iVar1 = FindFirstFileA((int)local_10c,(int)local_24c), iVar2 = param_2, iVar1 != -1)) {
    do {
      iVar4 = iVar2;
      if (((local_24c[0] & 0x10) != 0) && (local_220[0] != '.')) {
        iVar3 = iVar3 + 1;
        iVar4 = iVar2 + 0x40;
        strncpy(iVar2,local_220,0x40);
      }
      iVar2 = FindNextFileA(iVar1,(int)local_24c);
    } while ((iVar2 != 0) && (iVar2 = iVar4, iVar3 < param_3));
  }
  if (((param_5 & 2) == 0) &&
     ((iVar3 < param_3 && (iVar2 = FindFirstFileA((int)local_10c,(int)local_24c), iVar2 != -1)))) {
    iVar1 = iVar3 * 0x40 + param_2;
    do {
      iVar4 = iVar1;
      if ((local_24c[0] & 0x10) == 0) {
        iVar3 = iVar3 + 1;
        iVar4 = iVar1 + 0x40;
        strncpy(iVar1,local_220,0x40);
      }
      iVar1 = FindNextFileA(iVar2,(int)local_24c);
    } while ((iVar1 != 0) && (iVar1 = iVar4, iVar3 < param_3));
  }
  return iVar3;
}
#undef local_10c
#undef local_220
#undef local_24c


/* ---- 0x004c54f0  FUN_004c54f0 ---- */
int FUN_004c54f0(char *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  iVar2 = FUN_004d5830(param_1,param_2);
  if (iVar2 != 0) {
    uVar3 = 0xffffffff;
    pcVar7 = param_1;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    if ((((uVar3 != 1) && ((int)(uVar3 - 1) < param_2)) &&
        (cVar1 = param_1[uVar3 - 2], cVar1 != ':')) && ((cVar1 != '\\' && (cVar1 != '/')))) {
      uVar3 = 0xffffffff;
      pcVar7 = &DAT_004e9c60;
      do {
        pcVar6 = pcVar7;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar6 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar6;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      iVar4 = -1;
      do {
        pcVar7 = param_1;
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        pcVar7 = param_1 + 1;
        cVar1 = *param_1;
        param_1 = pcVar7;
      } while (cVar1 != '\0');
      pcVar6 = pcVar6 + -uVar3;
      pcVar7 = pcVar7 + -1;
      for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar7 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar7 = pcVar7 + 1;
      }
    }
  }
  return iVar2 == 0;
}

/* ---- 0x004c5570  FUN_004c5570 ---- */
undefined4 FUN_004c5570(int param_1,char *param_2)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  
  uVar3 = 0xffffffff;
  pcVar5 = param_2;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar2 != '\0');
  iVar4 = ~uVar3 - 1;
  if (((iVar4 < 3) || (param_2[~uVar3 - 3] == ':')) ||
     (pcVar5 = param_2 + iVar4, (param_2 + iVar4)[-1] != '\\')) {
    return 0xffffffff;
  }
  do {
    iVar4 = iVar4 + -1;
    if ((iVar4 == 0) || (pcVar1 = pcVar5 + -2, *pcVar1 == '\\')) break;
    pcVar5 = pcVar5 + -1;
  } while (*pcVar1 != ':');
  strncpy(param_1,param_2,iVar4);
  *(undefined1 *)(iVar4 + param_1) = 0;
  return 0;
}

/* ---- 0x004c55d0  FUN_004c55d0 ---- */
undefined4 FUN_004c55d0(char *param_1,char *param_2,char *param_3,undefined4 param_4)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  
  pcVar6 = param_3;
  uVar4 = 0xffffffff;
  pcVar7 = param_3;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  if ((~uVar4 - 1 < 2) || (param_3[1] != ':')) {
    if (param_1 != param_2) {
      uVar4 = 0xffffffff;
      pcVar7 = param_2;
      do {
        pcVar9 = pcVar7;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      pcVar7 = pcVar9 + -uVar4;
      pcVar9 = param_1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
    }
  }
  else {
    FUN_004c5370(&param_2);
    cVar1 = *pcVar6;
    if ((cVar1 < 'a') || ('z' < cVar1)) {
      iVar3 = (int)cVar1;
    }
    else {
      iVar3 = cVar1 + -0x20;
    }
    FUN_004c5350(iVar3 + -0x40,&param_3);
    FUN_004c54f0(param_1,param_4);
    FUN_004c5350(param_2,&param_3);
    pcVar6 = pcVar6 + 2;
  }
  if ((*pcVar6 == '\\') && (pcVar6[1] != '\\')) {
    param_1[2] = '\\';
    param_1[3] = '\0';
    pcVar6 = pcVar6 + 1;
  }
  cVar1 = *pcVar6;
  do {
    cVar2 = cVar1;
    pcVar7 = pcVar6;
    if (cVar1 == '\0') {
      return 0;
    }
    while ((cVar2 != '\0' && (cVar2 != '\\'))) {
      cVar2 = pcVar7[1];
      pcVar7 = pcVar7 + 1;
    }
    if (cVar1 == '.') {
      if (pcVar6[1] == '.') {
        FUN_004c5570(param_1,param_1);
      }
    }
    else {
      FUN_004ae410(param_1,pcVar6,(int)pcVar7 - (int)pcVar6);
      uVar4 = 0xffffffff;
      pcVar6 = &DAT_004e9c60;
      do {
        pcVar9 = pcVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      pcVar6 = param_1;
      do {
        pcVar8 = pcVar6;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar8 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar8;
      } while (cVar1 != '\0');
      pcVar6 = pcVar9 + -uVar4;
      pcVar9 = pcVar8 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar9 = pcVar9 + 1;
      }
    }
    if (*pcVar7 == '\0') {
      return 0;
    }
    cVar1 = pcVar7[1];
    pcVar6 = pcVar7 + 1;
  } while( true );
}

/* ---- 0x004c5720  FUN_004c5720 ---- */
int FUN_004c5720(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar2 = 0x41;
  puVar3 = (undefined1 *)(param_1 + 2);
  do {
    sprintf((char *)&param_1,&DAT_004f1c18,iVar2);
    iVar1 = GetDriveTypeA((int)&param_1);
    if (((((iVar1 == 3) || (iVar1 == 4)) || (iVar1 == 5)) || (iVar1 == 2)) && (iVar4 < param_2)) {
      puVar3[-2] = (char)iVar2;
      puVar3[-1] = 0x3a;
      *puVar3 = 0;
      iVar4 = iVar4 + 1;
      puVar3 = puVar3 + 0x1e;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x5b);
  return iVar4;
}

/* ---- 0x004c5790  FUN_004c5790 ---- */
undefined4 FUN_004c5790(int *param_1,uint param_2)

{
  PTR_008d7838 = param_1;
  UINT_008d7840 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_zfilio_004f1d24,&PTR_FUN_004f1cf8);
  (*(code *)*PTR_008d7838)(s_FILIO_insane_zfilio_004f0ca0,&PTR_FUN_004f1d08);
  return 0;
}

/* ---- 0x004c5840  FUN_004c5840 ---- */
void FUN_004c5840(void)

{
  (*(code *)PTR_008d7838[1])(s_FILIO_insane_zfilio_004f0ca0);
  (*(code *)PTR_008d7838[1])(s_LECMODULE_insane_zfilio_004f1d24);
  return;
}

/* ---- 0x004c5870  FUN_004c5870 ---- */
undefined4 FUN_004c5870(void)

{
  g_pZfileFileIo = (int *)(*(code *)PTR_008d7838[2])(s_FILIO_chainto_004f1dcc,UINT_008d7840);
  g_pZfileMemory = (int *)(*(code *)PTR_008d7838[2])(s_MEMORY_buffers_004f1dbc,UINT_008d7840);
  UINT_008d783c = (*(code *)PTR_008d7838[2])(s_VIRTHERC_debug_004f14dc,UINT_008d7840);
  if (g_pZfileFileIo == (int *)0x0) {
    (*(code *)PTR_008d7838[8])(s_Zfile_Module__Cannot_allocate_fi_004f1d8c);
    return 0xffffffff;
  }
  if (g_pZfileMemory == (int *)0x0) {
    (*(code *)PTR_008d7838[8])(s_Zfile_Module__Cannot_allocate_me_004f1d5c);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004c5910  FUN_004c5910 ---- */
void FUN_004c5910(void)

{
  (*(code *)PTR_008d7838[3])(g_pZfileFileIo);
  (*(code *)PTR_008d7838[3])(g_pZfileMemory);
  if (UINT_008d783c != 0) {
    (*(code *)PTR_008d7838[3])(UINT_008d783c);
  }
  return;
}

/* ---- 0x004c5950  FUN_004c5950 ---- */
int * FUN_004c5950(char *param_1,char *param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  void *pvVar3;
  undefined4 uVar4;
  undefined **ppuVar5;
  int iVar6;
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  piVar1 = (int *)(*(code *)*g_pZfileMemory)(0x14,s_C__grimsrc_libs_lecsmush_insane__004f1df4,0xd2);
  iVar6 = 0;
  if (piVar1 == (int *)0x0) {
    if ((UINT_008d783c != 0) && ((DAT_004f1cf0 & 1) != 0)) {
      (**(code **)(UINT_008d783c + 0xc))(s_Zfile_Memory_Alloc_fail_004f1ddc);
      return (int *)0x0;
    }
  }
  else {
    *piVar1 = 0;
    piVar1[1] = 0;
    if (((((*param_2 == 'r') || (*param_2 == 'R')) && (param_2[1] != '+')) &&
        ((param_2[1] == '\0' || (param_2[2] != '+')))) && (0 < (int)UINT_004f1c20)) {
      ppuVar5 = &PTR_DAT_004f1c28;
      do {
        iVar2 = String_ContainsSubstring(param_1,*ppuVar5);
        if (iVar2 != 0) {
          pvVar3 = SaveFile_Open(param_1,param_2);
          *piVar1 = (int)pvVar3;
          if (pvVar3 != (void *)0x0) {
            piVar1[1] = 1;
            piVar1[3] = 0;
            piVar1[4] = 0;
            uVar4 = (*(code *)*g_pZfileFileIo)(param_1,param_2);
            (*(code *)g_pZfileFileIo[5])(uVar4,0xfffffffc,2);
            (*(code *)g_pZfileFileIo[2])(uVar4,&iStack_4,4);
            piVar1[2] = iStack_4;
            (*(code *)g_pZfileFileIo[1])(uVar4);
            return piVar1;
          }
          break;
        }
        iVar6 = iVar6 + 1;
        ppuVar5 = ppuVar5 + 1;
      } while (iVar6 < (int)UINT_004f1c20);
    }
    iVar6 = (*(code *)*g_pZfileFileIo)(param_1,param_2);
    *piVar1 = iVar6;
    if (iVar6 != 0) {
      return piVar1;
    }
    (*(code *)g_pZfileMemory[1])(piVar1,s_C__grimsrc_libs_lecsmush_insane__004f1df4,0x101);
  }
  return (int *)0x0;
}
#undef iStack_4


/* ---- 0x004c5b00  FUN_004c5b00 ---- */
int FUN_004c5b00(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = param_1;
  iVar3 = 0;
  iVar1 = *param_1;
  if (iVar1 != 0) {
    if (param_1[1] != 0) {
      if (param_1[3] != param_1[4]) {
        iVar3 = gzseek(iVar1,param_1[4],0);
        if (iVar3 < 0) {
          FUN_004c4a00(*piVar2,&param_1);
        }
        else {
          piVar2[3] = piVar2[4];
        }
      }
      iVar1 = param_3;
      if (-1 < iVar3) {
        iVar3 = gzread(*piVar2,param_2,param_3);
      }
      if (-1 < iVar3) {
        piVar2[4] = piVar2[4] + iVar1;
        piVar2[3] = piVar2[3] + iVar1;
        return iVar3;
      }
      FUN_004c4a00(*piVar2,&param_1);
      return iVar3;
    }
    iVar3 = (*(code *)g_pZfileFileIo[2])(iVar1,param_2,param_3);
  }
  return iVar3;
}

/* ---- 0x004c5bc0  FUN_004c5bc0 ---- */
undefined4 FUN_004c5bc0(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = *param_1;
  if (iVar1 != 0) {
    if (param_1[1] != 0) {
      uVar2 = gzwrite(iVar1,param_2,param_3);
      param_1[3] = param_1[3] + param_3;
      param_1[4] = param_1[4] + param_3;
      return uVar2;
    }
    uVar2 = (*(code *)g_pZfileFileIo[3])(iVar1,param_2,param_3);
  }
  return uVar2;
}

/* ---- 0x004c5c20  FUN_004c5c20 ---- */
int FUN_004c5c20(int *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (*param_1 != 0) {
    if (param_1[1] != 0) {
      return param_1[4];
    }
    iVar1 = (*(code *)g_pZfileFileIo[4])(*param_1);
  }
  return iVar1;
}

/* ---- 0x004c5c50  FUN_004c5c50 ---- */
void FUN_004c5c50(int *param_1,int param_2,int param_3)

{
  if (*param_1 != 0) {
    if (param_1[1] == 0) {
      (*(code *)g_pZfileFileIo[5])(*param_1,param_2,param_3);
    }
    else {
      if (param_3 == 0) {
        param_1[4] = param_2;
        return;
      }
      if (param_3 == 1) {
        param_1[4] = param_1[4] + param_2;
        return;
      }
      if (param_3 == 2) {
        param_1[4] = param_1[2] + param_2;
        return;
      }
    }
  }
  return;
}

/* ---- 0x004c5cb0  FUN_004c5cb0 ---- */
void FUN_004c5cb0(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    if (param_1[1] != 0) {
      FUN_004c4650(iVar1,4);
      return;
    }
    (*(code *)g_pZfileFileIo[6])(iVar1);
  }
  return;
}

/* ---- 0x004c5ce0  FUN_004c5ce0 ---- */
undefined4 FUN_004c5ce0(int *param_1,uint param_2)

{
  PTR_008d7844 = param_1;
  UINT_008d784c = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_stdfile_004f1e88,&PTR_FUN_004f1e30);
  (*(code *)*PTR_008d7844)(s_FILE_insane_stdfile_004f1e74,&PTR_FUN_004f1e40);
  return 0;
}

/* ---- 0x004c5d20  FUN_004c5d20 ---- */
void FUN_004c5d20(void)

{
  (*(code *)PTR_008d7844[1])(s_FILE_insane_stdfile_004f1e74);
  (*(code *)PTR_008d7844[1])(s_LECMODULE_insane_stdfile_004f1e88);
  return;
}

/* ---- 0x004c5d50  FUN_004c5d50 ---- */
undefined4 FUN_004c5d50(void)

{
  g_pStdFileIo = (int *)(*(code *)PTR_008d7844[2])(s_FILIO_chainto_004f1dcc,UINT_008d784c);
  if (g_pStdFileIo == (int *)0x0) {
    (*(code *)PTR_008d7844[8])(s_StdFile_Module__Cannot_allocate_f_004f1ea4);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004c5d90  FUN_004c5d90 ---- */
void FUN_004c5d90(void)

{
  (*(code *)PTR_008d7844[3])(g_pStdFileIo);
  return;
}

/* ---- 0x004c5db0  FUN_004c5db0 ---- */
void FUN_004c5db0(undefined4 param_1,undefined4 param_2)

{
  (*(code *)*g_pStdFileIo)(param_1,param_2);
  return;
}

/* ---- 0x004c5dd0  FUN_004c5dd0 ---- */
void FUN_004c5dd0(undefined4 param_1)

{
  (*(code *)g_pStdFileIo[1])(param_1);
  return;
}

/* ---- 0x004c5df0  FUN_004c5df0 ---- */
void FUN_004c5df0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*(code *)g_pStdFileIo[2])(param_1,param_2,param_3);
  return;
}

/* ---- 0x004c5e10  FUN_004c5e10 ---- */
void FUN_004c5e10(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*(code *)g_pStdFileIo[3])(param_1,param_2,param_3);
  return;
}

/* ---- 0x004c5e50  FUN_004c5e50 ---- */
void FUN_004c5e50(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*(code *)g_pStdFileIo[5])(param_1,param_2,param_3);
  return;
}

/* ---- 0x004c5e70  FUN_004c5e70 ---- */
void FUN_004c5e70(undefined4 param_1)

{
  (*(code *)g_pStdFileIo[6])(param_1);
  return;
}

/* ---- 0x004c5ee0  FUN_004c5ee0 ---- */
int FUN_004c5ee0(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  if (0 < param_3) {
    iVar2 = 1;
    while( true ) {
      iVar1 = FUN_004c5fe0(param_1);
      if (iVar1 == -1) {
        if (iVar3 == 0) {
          return 0;
        }
        *(undefined1 *)(iVar3 + param_2) = 0;
        return param_2;
      }
      *(char *)(param_2 + -1 + iVar2) = (char)iVar1;
      if ((iVar1 == 10) && (iVar2 < param_3)) break;
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 1;
      if (param_3 <= iVar3) {
        return param_2;
      }
    }
    *(undefined1 *)(iVar3 + 1 + param_2) = 0;
  }
  return param_2;
}

/* ---- 0x004c5f80  FUN_004c5f80 ---- */
void FUN_004c5f80(undefined4 param_1,undefined4 param_2)

{
  unsigned char _frame[0x210];  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  char *pcVar3;
  #define local_1f4 (*(char (*)[500])(_frame + (0x210 - 0x1f4)))
  
  vsprintf(local_1f4,param_2,&STACK0X(0x0000000c));
  uVar2 = 0xffffffff;
  pcVar3 = local_1f4;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  (*(code *)g_pStdFileIo[3])(param_1,local_1f4,~uVar2 - 1);
  return;
}
#undef local_1f4


/* ---- 0x004c5fe0  FUN_004c5fe0 ---- */
uint FUN_004c5fe0(uint param_1)

{
  int iVar1;
  
  iVar1 = (*(code *)g_pStdFileIo[2])(param_1,&param_1,1);
  if (iVar1 != 0) {
    return param_1 & 0xff;
  }
  return 0xffffffff;
}

/* ---- 0x004c6010  FUN_004c6010 ---- */
uint FUN_004c6010(undefined4 param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = (*(code *)g_pStdFileIo[3])(param_1,&param_2,1);
  if (iVar1 != 0) {
    return param_2 & 0xff;
  }
  return 0xffffffff;
}

/* ---- 0x004c6db0  FUN_004c6db0 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004c6db0(int *param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  uVar5 = 0xffff;
  if (param_1[3] - 5U < 0xffff) {
    uVar5 = param_1[3] - 5U;
  }
  do {
    uVar2 = param_1[0x1b];
    if (uVar2 < 2) {
      FUN_004c6f10(param_1);
      uVar2 = param_1[0x1b];
      if (uVar2 == 0) {
        if (param_2 == 0) {
          return 0;
        }
        iVar4 = param_1[0x15];
        if (iVar4 < 0) {
          iVar3 = 0;
        }
        else {
          iVar3 = param_1[0xc] + iVar4;
        }
        FUN_004c8e90(param_1,iVar3,param_1[0x19] - iVar4,param_2 == 4);
        param_1[0x15] = param_1[0x19];
        flush_pending(*param_1);
        if (*(int *)(*param_1 + 0x10) != 0) {
          return (-(uint)(param_2 != 4) & 0xfffffffe) + 3;
        }
        return (param_2 != 4) - 1 & 2;
      }
    }
    iVar4 = param_1[0x19];
    param_1[0x1b] = 0;
    param_1[0x19] = iVar4 + uVar2;
    iVar3 = param_1[0x15];
    uVar1 = uVar5 + iVar3;
    if ((iVar4 + uVar2 == 0) || (uVar1 <= (uint)param_1[0x19])) {
      param_1[0x1b] = param_1[0x19] - uVar1;
      param_1[0x19] = uVar1;
      if (iVar3 < 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = param_1[0xc] + iVar3;
      }
      FUN_004c8e90(param_1,iVar4,uVar1 - iVar3,0);
      param_1[0x15] = param_1[0x19];
      flush_pending(*param_1);
      if (*(int *)(*param_1 + 0x10) == 0) {
        return 0;
      }
    }
    iVar4 = param_1[0x15];
    if (param_1[9] - 0x106U <= (uint)(param_1[0x19] - iVar4)) {
      if (iVar4 < 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = param_1[0xc] + iVar4;
      }
      FUN_004c8e90(param_1,iVar3,param_1[0x19] - iVar4,0);
      param_1[0x15] = param_1[0x19];
      flush_pending(*param_1);
      if (*(int *)(*param_1 + 0x10) == 0) {
        return 0;
      }
    }
  } while( true );
}
#endif


/* ---- 0x004c6f10  FUN_004c6f10 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c6f10(int *param_1)

{
  uint uVar1;
  ushort uVar2;
  int iVar3;
  ushort *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  
  uVar1 = param_1[9];
  while( true ) {
    uVar5 = param_1[0x19];
    uVar6 = (param_1[0xd] - uVar5) - param_1[0x1b];
    if (((uVar6 != 0) || (uVar5 != 0)) || (uVar7 = uVar1, param_1[0x1b] != 0)) {
      if (uVar6 == 0xffffffff) {
        uVar7 = 0xfffffffe;
      }
      else {
        uVar7 = uVar6;
        if ((uVar1 - 0x106) + param_1[9] <= uVar5) {
          puVar8 = (undefined4 *)(uVar1 + param_1[0xc]);
          puVar9 = (undefined4 *)param_1[0xc];
          for (uVar5 = uVar1 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *puVar9 = *puVar8;
            puVar8 = puVar8 + 1;
            puVar9 = puVar9 + 1;
          }
          for (uVar5 = uVar1 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined1 *)puVar9 = *(undefined1 *)puVar8;
            puVar8 = (undefined4 *)((int)puVar8 + 1);
            puVar9 = (undefined4 *)((int)puVar9 + 1);
          }
          param_1[0x1a] = param_1[0x1a] - uVar1;
          iVar3 = param_1[0x11];
          param_1[0x19] = param_1[0x19] - uVar1;
          param_1[0x15] = param_1[0x15] - uVar1;
          puVar4 = (ushort *)(param_1[0xf] + iVar3 * 2);
          do {
            puVar4 = puVar4 + -1;
            if (*puVar4 < uVar1) {
              uVar2 = 0;
            }
            else {
              uVar2 = *puVar4 - (short)uVar1;
            }
            iVar3 = iVar3 + -1;
            *puVar4 = uVar2;
          } while (iVar3 != 0);
          puVar4 = (ushort *)(param_1[0xe] + uVar1 * 2);
          uVar5 = uVar1;
          do {
            puVar4 = puVar4 + -1;
            if (*puVar4 < uVar1) {
              uVar2 = 0;
            }
            else {
              uVar2 = *puVar4 - (short)uVar1;
            }
            uVar5 = uVar5 - 1;
            *puVar4 = uVar2;
          } while (uVar5 != 0);
          uVar7 = uVar6 + uVar1;
        }
      }
    }
    if (*(int *)(*param_1 + 4) == 0) break;
    iVar3 = FUN_004c7040(*param_1,param_1[0xc] + param_1[0x1b] + param_1[0x19],uVar7);
    uVar5 = param_1[0x1b] + iVar3;
    param_1[0x1b] = uVar5;
    if (2 < uVar5) {
      uVar6 = (uint)*(byte *)(param_1[0xc] + param_1[0x19]);
      param_1[0x10] = uVar6;
      param_1[0x10] =
           (uVar6 << ((byte)param_1[0x14] & 0x1f) ^
           (uint)((byte *)(param_1[0xc] + param_1[0x19]))[1]) & param_1[0x13];
    }
    if (0x105 < uVar5) {
      return;
    }
    if (*(int *)(*param_1 + 4) == 0) {
      return;
    }
  }
  return;
}
#endif


/* ---- 0x004c7040  FUN_004c7040 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004c7040(int *param_1,undefined4 *param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  uVar2 = param_1[1];
  uVar3 = uVar2;
  if (param_3 < uVar2) {
    uVar3 = param_3;
  }
  if (uVar3 == 0) {
    return 0;
  }
  param_1[1] = uVar2 - uVar3;
  if (*(int *)(param_1[7] + 0x18) == 0) {
    iVar1 = FUN_004c8990(param_1[0xc],*param_1,uVar3);
    param_1[0xc] = iVar1;
  }
  puVar4 = (undefined4 *)*param_1;
  for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *param_2 = *puVar4;
    puVar4 = puVar4 + 1;
    param_2 = param_2 + 1;
  }
  for (uVar2 = uVar3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)param_2 = *(undefined1 *)puVar4;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
    param_2 = (undefined4 *)((int)param_2 + 1);
  }
  *param_1 = *param_1 + uVar3;
  param_1[2] = param_1[2] + uVar3;
  return uVar3;
}
#endif


/* ---- 0x004c70c0  FUN_004c70c0 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004c70c0(int *param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  uint uVar6;
  byte *pbVar7;
  uint uVar8;
  bool bVar9;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar8 = 0;
  do {
    uVar6 = param_1[0x1b];
    if (uVar6 < 0x106) {
      FUN_004c6f10(param_1);
      uVar6 = param_1[0x1b];
      if ((uVar6 < 0x106) && (param_2 == 0)) {
        return 0;
      }
      if (uVar6 == 0) {
        iVar3 = param_1[0x15];
        if (iVar3 < 0) {
          iVar4 = 0;
        }
        else {
          iVar4 = param_1[0xc] + iVar3;
        }
        FUN_004c8e90(param_1,iVar4,param_1[0x19] - iVar3,param_2 == 4);
        param_1[0x15] = param_1[0x19];
        flush_pending(*param_1);
        if (*(int *)(*param_1 + 0x10) == 0) {
          return (param_2 != 4) - 1 & 2;
        }
        return (-(uint)(param_2 != 4) & 0xfffffffe) + 3;
      }
    }
    if (2 < uVar6) {
      uVar8 = (param_1[0x10] << ((byte)param_1[0x14] & 0x1f) ^
              (uint)*(byte *)(param_1[0xc] + 2 + param_1[0x19])) & param_1[0x13];
      param_1[0x10] = uVar8;
      uVar2 = *(ushort *)(param_1[0xf] + uVar8 * 2);
      uVar8 = (uint)uVar2;
      *(ushort *)(param_1[0xe] + (param_1[0xb] & param_1[0x19]) * 2) = uVar2;
      *(short *)(param_1[0xf] + param_1[0x10] * 2) = (short)param_1[0x19];
    }
    if (((uVar8 != 0) && (param_1[0x19] - uVar8 <= param_1[9] - 0x106U)) && (param_1[0x20] != 2)) {
      iVar3 = FUN_004c73f0(param_1,uVar8);
      param_1[0x16] = iVar3;
    }
    if ((uint)param_1[0x16] < 3) {
      bVar5 = *(byte *)(param_1[0xc] + param_1[0x19]);
      *(undefined2 *)(param_1[0x5a7] + param_1[0x5a6] * 2) = 0;
      *(byte *)(param_1[0x5a4] + param_1[0x5a6]) = bVar5;
      param_1[0x5a6] = param_1[0x5a6] + 1;
      *(short *)(param_1 + bVar5 + 0x23) = (short)param_1[bVar5 + 0x23] + 1;
      bVar9 = param_1[0x5a6] == param_1[0x5a5] + -1;
      param_1[0x1b] = param_1[0x1b] + -1;
LAB_004c732b:
      param_1[0x19] = param_1[0x19] + 1;
    }
    else {
      sVar1 = (short)param_1[0x19] - (short)param_1[0x1a];
      iVar3 = param_1[0x16];
      *(short *)(param_1[0x5a7] + param_1[0x5a6] * 2) = sVar1;
      bVar5 = (char)iVar3 - 3;
      uVar2 = sVar1 - 1;
      *(byte *)(param_1[0x5a4] + param_1[0x5a6]) = bVar5;
      param_1[0x5a6] = param_1[0x5a6] + 1;
      *(short *)(param_1 + (byte)(&DAT_004da548)[bVar5] + 0x124) =
           (short)param_1[(byte)(&DAT_004da548)[bVar5] + 0x124] + 1;
      if (uVar2 < 0x100) {
        bVar5 = (&DAT_004da348)[uVar2];
      }
      else {
        bVar5 = (&DAT_004da448)[uVar2 >> 7];
      }
      *(short *)(param_1 + bVar5 + 0x260) = (short)param_1[bVar5 + 0x260] + 1;
      bVar9 = param_1[0x5a6] == param_1[0x5a5] + -1;
      uVar6 = param_1[0x16];
      iVar3 = param_1[0x1b];
      param_1[0x1b] = iVar3 - uVar6;
      if ((uVar6 <= (uint)param_1[0x1e]) && (2 < iVar3 - uVar6)) {
        param_1[0x16] = uVar6 - 1;
        do {
          iVar3 = param_1[0x19];
          uVar6 = iVar3 + 1;
          param_1[0x19] = uVar6;
          uVar8 = ((uint)*(byte *)(iVar3 + 3 + param_1[0xc]) ^
                  param_1[0x10] << ((byte)param_1[0x14] & 0x1f)) & param_1[0x13];
          param_1[0x10] = uVar8;
          uVar2 = *(ushort *)(param_1[0xf] + uVar8 * 2);
          uVar8 = (uint)uVar2;
          *(ushort *)(param_1[0xe] + (param_1[0xb] & uVar6) * 2) = uVar2;
          *(short *)(param_1[0xf] + param_1[0x10] * 2) = (short)param_1[0x19];
          iVar3 = param_1[0x16];
          param_1[0x16] = iVar3 + -1;
        } while (iVar3 + -1 != 0);
        goto LAB_004c732b;
      }
      iVar3 = param_1[0x19];
      param_1[0x16] = 0;
      param_1[0x19] = iVar3 + uVar6;
      pbVar7 = (byte *)(param_1[0xc] + iVar3 + uVar6);
      uVar6 = (uint)*pbVar7;
      param_1[0x10] = uVar6;
      param_1[0x10] = (uVar6 << ((byte)param_1[0x14] & 0x1f) ^ (uint)pbVar7[1]) & param_1[0x13];
    }
    if (bVar9) {
      iVar3 = param_1[0x15];
      if (iVar3 < 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = iVar3 + param_1[0xc];
      }
      FUN_004c8e90(param_1,iVar4,param_1[0x19] - iVar3,0);
      param_1[0x15] = param_1[0x19];
      flush_pending(*param_1);
      if (*(int *)(*param_1 + 0x10) == 0) {
        return 0;
      }
    }
  } while( true );
}
#undef local_4

#endif


/* ---- 0x004c73f0  FUN_004c73f0 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
char * FUN_004c73f0(int param_1,uint param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  #define local_11 (*(char *)(_frame + (0x30 - 0x11)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  local_10 = *(uint *)(param_1 + 0x74);
  uVar4 = *(uint *)(param_1 + 100);
  pcVar9 = *(char **)(param_1 + 0x70);
  pcVar2 = (char *)(uVar4 + *(int *)(param_1 + 0x30));
  if (*(int *)(param_1 + 0x24) - 0x106U < uVar4) {
    local_8 = (uVar4 - *(int *)(param_1 + 0x24)) + 0x106;
  }
  else {
    local_8 = 0;
  }
  cVar3 = pcVar2[(int)(pcVar9 + -1)];
  pcVar1 = pcVar2 + 0x102;
  local_11 = pcVar2[(int)pcVar9];
  if (*(char **)(param_1 + 0x84) <= pcVar9) {
    local_10 = local_10 >> 2;
  }
  pcVar5 = *(char **)(param_1 + 0x6c);
  local_c = (uint)*(char **)(param_1 + 0x88);
  if (pcVar5 < *(char **)(param_1 + 0x88)) {
    local_c = (uint)pcVar5;
  }
  do {
    pcVar8 = (char *)(param_2 + *(int *)(param_1 + 0x30));
    if ((((pcVar8[(int)pcVar9] == local_11) && (pcVar8[(int)(pcVar9 + -1)] == cVar3)) &&
        (*pcVar8 == *pcVar2)) && (pcVar8[1] == pcVar2[1])) {
      pcVar8 = pcVar8 + 2;
      pcVar6 = pcVar2 + 2;
      while (((((pcVar7 = pcVar6 + 1, pcVar6[1] == pcVar8[1] &&
                (pcVar7 = pcVar6 + 2, pcVar6[2] == pcVar8[2])) &&
               ((pcVar7 = pcVar6 + 3, pcVar6[3] == pcVar8[3] &&
                ((pcVar7 = pcVar6 + 4, pcVar6[4] == pcVar8[4] &&
                 (pcVar7 = pcVar6 + 5, pcVar6[5] == pcVar8[5])))))) &&
              (pcVar7 = pcVar6 + 6, pcVar6[6] == pcVar8[6])) &&
             (pcVar7 = pcVar6 + 7, pcVar6[7] == pcVar8[7]))) {
        pcVar7 = pcVar6 + 8;
        pcVar8 = pcVar8 + 8;
        if ((pcVar6[8] != *pcVar8) || (pcVar6 = pcVar7, pcVar1 <= pcVar7)) break;
      }
      pcVar8 = pcVar7 + (0x102 - (int)pcVar1);
      if ((int)pcVar9 < (int)pcVar8) {
        *(uint *)(param_1 + 0x68) = param_2;
        if ((int)local_c <= (int)pcVar8) {
LAB_004c754f:
          if (pcVar8 <= pcVar5) {
            pcVar5 = pcVar8;
          }
          return pcVar5;
        }
        cVar3 = pcVar2[(int)(pcVar7 + (0x101 - (int)pcVar1))];
        local_11 = pcVar2[(int)pcVar8];
        pcVar9 = pcVar8;
      }
    }
    pcVar8 = pcVar9;
    param_2 = (uint)*(ushort *)
                     (*(int *)(param_1 + 0x38) + (*(uint *)(param_1 + 0x2c) & param_2) * 2);
    if ((param_2 <= local_8) || (local_10 = local_10 - 1, pcVar9 = pcVar8, local_10 == 0))
    goto LAB_004c754f;
  } while( true );
}
#undef local_10
#undef local_11
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004c7570  FUN_004c7570 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004c7570(int *param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  short sVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte bVar8;
  uint uVar9;
  uint uVar10;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar10 = 0;
  do {
    uVar9 = param_1[0x1b];
    if (uVar9 < 0x106) {
      FUN_004c6f10(param_1);
      uVar9 = param_1[0x1b];
      if ((uVar9 < 0x106) && (param_2 == 0)) {
        return 0;
      }
      if (uVar9 == 0) {
        if (param_1[0x18] != 0) {
          bVar8 = *(byte *)(param_1[0xc] + -1 + param_1[0x19]);
          *(undefined2 *)(param_1[0x5a7] + param_1[0x5a6] * 2) = 0;
          *(byte *)(param_1[0x5a4] + param_1[0x5a6]) = bVar8;
          param_1[0x5a6] = param_1[0x5a6] + 1;
          *(short *)(param_1 + bVar8 + 0x23) = (short)param_1[bVar8 + 0x23] + 1;
          param_1[0x18] = 0;
        }
        iVar5 = param_1[0x15];
        if (iVar5 < 0) {
          iVar7 = 0;
        }
        else {
          iVar7 = param_1[0xc] + iVar5;
        }
        FUN_004c8e90(param_1,iVar7,param_1[0x19] - iVar5,param_2 == 4);
        param_1[0x15] = param_1[0x19];
        flush_pending(*param_1);
        if (*(int *)(*param_1 + 0x10) == 0) {
          return (param_2 != 4) - 1 & 2;
        }
        return (-(uint)(param_2 != 4) & 0xfffffffe) + 3;
      }
    }
    if (2 < uVar9) {
      uVar10 = (param_1[0x10] << ((byte)param_1[0x14] & 0x1f) ^
               (uint)*(byte *)(param_1[0xc] + 2 + param_1[0x19])) & param_1[0x13];
      param_1[0x10] = uVar10;
      uVar4 = *(ushort *)(param_1[0xf] + uVar10 * 2);
      uVar10 = (uint)uVar4;
      *(ushort *)(param_1[0xe] + (param_1[0xb] & param_1[0x19]) * 2) = uVar4;
      *(short *)(param_1[0xf] + param_1[0x10] * 2) = (short)param_1[0x19];
    }
    uVar9 = param_1[0x16];
    param_1[0x1c] = uVar9;
    param_1[0x17] = param_1[0x1a];
    param_1[0x16] = 2;
    if (((uVar10 != 0) && (uVar9 < (uint)param_1[0x1e])) &&
       (param_1[0x19] - uVar10 <= param_1[9] - 0x106U)) {
      if (param_1[0x20] != 2) {
        iVar5 = FUN_004c73f0(param_1,uVar10);
        param_1[0x16] = iVar5;
      }
      if (((uint)param_1[0x16] < 6) &&
         ((param_1[0x20] == 1 ||
          ((param_1[0x16] == 3 && (0x1000 < (uint)(param_1[0x19] - param_1[0x1a]))))))) {
        param_1[0x16] = 2;
      }
    }
    if (((uint)param_1[0x1c] < 3) || ((uint)param_1[0x1c] < (uint)param_1[0x16])) {
      if (param_1[0x18] == 0) {
        param_1[0x18] = 1;
        param_1[0x19] = param_1[0x19] + 1;
        param_1[0x1b] = param_1[0x1b] + -1;
      }
      else {
        bVar8 = *(byte *)(param_1[0x19] + -1 + param_1[0xc]);
        *(undefined2 *)(param_1[0x5a7] + param_1[0x5a6] * 2) = 0;
        *(byte *)(param_1[0x5a4] + param_1[0x5a6]) = bVar8;
        param_1[0x5a6] = param_1[0x5a6] + 1;
        *(short *)(param_1 + bVar8 + 0x23) = (short)param_1[bVar8 + 0x23] + 1;
        if (param_1[0x5a6] == param_1[0x5a5] + -1) {
          iVar5 = param_1[0x15];
          if (iVar5 < 0) {
            iVar7 = 0;
          }
          else {
            iVar7 = param_1[0xc] + iVar5;
          }
          FUN_004c8e90(param_1,iVar7,param_1[0x19] - iVar5,0);
          param_1[0x15] = param_1[0x19];
          flush_pending(*param_1);
        }
        param_1[0x19] = param_1[0x19] + 1;
        param_1[0x1b] = param_1[0x1b] + -1;
        if (*(int *)(*param_1 + 0x10) == 0) {
          return 0;
        }
      }
    }
    else {
      iVar5 = param_1[0x19];
      iVar7 = param_1[0x1b];
      sVar3 = (short)param_1[0x19] - (short)param_1[0x17];
      bVar8 = (char)param_1[0x1c] - 3;
      *(short *)(param_1[0x5a7] + param_1[0x5a6] * 2) = sVar3 + -1;
      uVar4 = sVar3 - 2;
      *(byte *)(param_1[0x5a4] + param_1[0x5a6]) = bVar8;
      param_1[0x5a6] = param_1[0x5a6] + 1;
      *(short *)(param_1 + (byte)(&DAT_004da548)[bVar8] + 0x124) =
           (short)param_1[(byte)(&DAT_004da548)[bVar8] + 0x124] + 1;
      if (uVar4 < 0x100) {
        bVar8 = (&DAT_004da348)[uVar4];
      }
      else {
        bVar8 = (&DAT_004da448)[uVar4 >> 7];
      }
      *(short *)(param_1 + bVar8 + 0x260) = (short)param_1[bVar8 + 0x260] + 1;
      iVar6 = param_1[0x5a5];
      iVar1 = param_1[0x5a6];
      param_1[0x1b] = param_1[0x1b] + (1 - param_1[0x1c]);
      param_1[0x1c] = param_1[0x1c] + -2;
      do {
        uVar9 = param_1[0x19] + 1;
        param_1[0x19] = uVar9;
        if (uVar9 <= (uint)(iVar5 + -3 + iVar7)) {
          uVar10 = (param_1[0x10] << ((byte)param_1[0x14] & 0x1f) ^
                   (uint)*(byte *)(param_1[0xc] + 2 + uVar9)) & param_1[0x13];
          param_1[0x10] = uVar10;
          uVar4 = *(ushort *)(param_1[0xf] + uVar10 * 2);
          uVar10 = (uint)uVar4;
          *(ushort *)(param_1[0xe] + (param_1[0xb] & uVar9) * 2) = uVar4;
          *(short *)(param_1[0xf] + param_1[0x10] * 2) = (short)param_1[0x19];
        }
        iVar2 = param_1[0x1c];
        param_1[0x1c] = iVar2 + -1;
      } while (iVar2 + -1 != 0);
      iVar5 = param_1[0x19];
      param_1[0x18] = 0;
      param_1[0x16] = 2;
      param_1[0x19] = iVar5 + 1;
      if (iVar1 == iVar6 + -1) {
        iVar7 = param_1[0x15];
        if (iVar7 < 0) {
          iVar6 = 0;
        }
        else {
          iVar6 = param_1[0xc] + iVar7;
        }
        FUN_004c8e90(param_1,iVar6,(iVar5 + 1) - iVar7,0);
        param_1[0x15] = param_1[0x19];
        flush_pending(*param_1);
        if (*(int *)(*param_1 + 0x10) == 0) {
          return 0;
        }
      }
    }
  } while( true );
}
#undef local_4

#endif


/* ---- 0x004c7b10  FUN_004c7b10 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c7b10(undefined4 param_1,undefined4 param_2)

{
  free(param_2);
  return;
}
#endif


/* ---- 0x004c8990  FUN_004c8990 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004c8990(uint param_1,byte *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  byte *pbVar19;
  
  uVar2 = param_1 & 0xffff;
  param_1 = param_1 >> 0x10;
  if (param_2 == (byte *)0x0) {
    return 1;
  }
  while (param_3 != 0) {
    uVar1 = param_3;
    if (0x15af < param_3) {
      uVar1 = 0x15b0;
    }
    param_3 = param_3 - uVar1;
    if (0xf < (int)uVar1) {
      uVar18 = uVar1 >> 4;
      pbVar19 = param_2;
      do {
        uVar1 = uVar1 - 0x10;
        param_2 = pbVar19 + 0x10;
        iVar3 = uVar2 + *pbVar19;
        iVar4 = iVar3 + (uint)pbVar19[1];
        iVar5 = iVar4 + (uint)pbVar19[2];
        iVar6 = iVar5 + (uint)pbVar19[3];
        iVar7 = iVar6 + (uint)pbVar19[4];
        iVar8 = iVar7 + (uint)pbVar19[5];
        iVar9 = iVar8 + (uint)pbVar19[6];
        iVar10 = iVar9 + (uint)pbVar19[7];
        iVar11 = iVar10 + (uint)pbVar19[8];
        iVar12 = iVar11 + (uint)pbVar19[9];
        iVar13 = iVar12 + (uint)pbVar19[10];
        iVar14 = iVar13 + (uint)pbVar19[0xb];
        iVar15 = iVar14 + (uint)pbVar19[0xc];
        iVar16 = iVar15 + (uint)pbVar19[0xd];
        iVar17 = iVar16 + (uint)pbVar19[0xe];
        uVar2 = iVar17 + (uint)pbVar19[0xf];
        param_1 = param_1 + iVar3 + iVar4 + iVar5 + iVar6 + iVar7 + iVar8 + iVar9 + iVar10 + iVar11
                  + iVar12 + iVar13 + iVar14 + iVar15 + iVar16 + iVar17 + uVar2;
        uVar18 = uVar18 - 1;
        pbVar19 = param_2;
      } while (uVar18 != 0);
    }
    for (; uVar1 != 0; uVar1 = uVar1 - 1) {
      uVar2 = uVar2 + *param_2;
      param_2 = param_2 + 1;
      param_1 = param_1 + uVar2;
    }
    uVar2 = uVar2 % 0xfff1;
    param_1 = param_1 % 0xfff1;
  }
  return param_1 << 0x10 | uVar2;
}
#endif


/* ---- 0x004c8ba0  FUN_004c8ba0 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c8ba0(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x16b4);
  if (iVar1 < 0xe) {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | (ushort)(param_4 << ((byte)iVar1 & 0x1f));
    *(int *)(param_1 + 0x16b4) = iVar1 + 3;
  }
  else {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | (ushort)(param_4 << ((byte)iVar1 & 0x1f));
    *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
         *(undefined1 *)(param_1 + 0x16b0);
    iVar1 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar1;
    *(undefined1 *)(*(int *)(param_1 + 8) + iVar1) = *(undefined1 *)(param_1 + 0x16b1);
    iVar1 = *(int *)(param_1 + 0x16b4);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x16b4) = iVar1 + -0xd;
    *(ushort *)(param_1 + 0x16b0) = (ushort)param_4 >> (0x10U - (char)iVar1 & 0x1f);
  }
  copy_block(param_1,param_2,param_3,1);
  return;
}
#endif


/* ---- 0x004c8e90  FUN_004c8e90 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c8e90(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined *puVar7;
  undefined *puVar8;
  
  iVar2 = 0;
  if (*(int *)(param_1 + 0x7c) < 1) {
    uVar4 = param_3 + 5;
  }
  else {
    if (*(char *)(param_1 + 0x1c) == '\x02') {
      FUN_004ca3f0(param_1);
    }
    FUN_004c9090(param_1,param_1 + 0xb10);
    FUN_004c9090(param_1,param_1 + 0xb1c);
    iVar2 = ((code *)FUN_004c9640)(param_1);
    uVar5 = *(int *)(param_1 + 0x16a0) + 10U >> 3;
    uVar4 = *(int *)(param_1 + 0x16a4) + 10U >> 3;
    if (uVar5 < uVar4) goto LAB_004c8f00;
  }
  uVar5 = uVar4;
LAB_004c8f00:
  if ((uVar5 < param_3 + 4U) || (param_2 == 0)) {
    iVar6 = *(int *)(param_1 + 0x16b4);
    bVar3 = (byte)iVar6;
    if (uVar4 == uVar5) {
      iVar2 = param_4 + 2;
      if (iVar6 < 0xe) {
        puVar8 = &DAT_004da2d0;
        puVar7 = &DAT_004d9e50;
        *(ushort *)(param_1 + 0x16b0) =
             *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar2 << (bVar3 & 0x1f));
        *(int *)(param_1 + 0x16b4) = iVar6 + 3;
      }
      else {
        puVar8 = &DAT_004da2d0;
        puVar7 = &DAT_004d9e50;
        *(ushort *)(param_1 + 0x16b0) =
             *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar2 << (bVar3 & 0x1f));
        *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) =
             *(undefined1 *)(param_1 + 0x16b0);
        iVar6 = *(int *)(param_1 + 0x14) + 1;
        *(int *)(param_1 + 0x14) = iVar6;
        *(undefined1 *)(iVar6 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
        iVar6 = *(int *)(param_1 + 0x16b4);
        *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
        *(int *)(param_1 + 0x16b4) = iVar6 + -0xd;
        *(ushort *)(param_1 + 0x16b0) = (ushort)iVar2 >> (0x10U - (char)iVar6 & 0x1f);
      }
    }
    else {
      iVar1 = param_4 + 4;
      if (iVar6 < 0xe) {
        *(ushort *)(param_1 + 0x16b0) =
             *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar1 << (bVar3 & 0x1f));
        *(int *)(param_1 + 0x16b4) = iVar6 + 3;
      }
      else {
        *(ushort *)(param_1 + 0x16b0) =
             *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar1 << (bVar3 & 0x1f));
        *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) =
             *(undefined1 *)(param_1 + 0x16b0);
        iVar6 = *(int *)(param_1 + 0x14) + 1;
        *(int *)(param_1 + 0x14) = iVar6;
        *(undefined1 *)(iVar6 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
        iVar6 = *(int *)(param_1 + 0x16b4);
        *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
        *(int *)(param_1 + 0x16b4) = iVar6 + -0xd;
        *(ushort *)(param_1 + 0x16b0) = (ushort)iVar1 >> (0x10U - (char)iVar6 & 0x1f);
      }
      FUN_004c97b0(param_1,*(int *)(param_1 + 0xb14) + 1,*(int *)(param_1 + 0xb20) + 1,iVar2 + 1);
      puVar8 = (undefined *)(param_1 + 0x980);
      puVar7 = (undefined *)(param_1 + 0x8c);
    }
    FUN_004c9fa0(param_1,puVar7,puVar8);
  }
  else {
    FUN_004c8ba0(param_1,param_2,param_3,param_4);
  }
  init_block(param_1);
  if (param_4 != 0) {
    bi_windup(param_1);
  }
  return;
}
#endif


/* ---- 0x004c9090  FUN_004c9090 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c9090(short *param_1,undefined4 *param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  short *psVar2;
  int iVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar3 = (int)param_1;
  psVar2 = (short *)*param_2;
  uVar10 = 0xffffffff;
  iVar9 = *(int *)param_2[2];
  local_4 = ((int *)param_2[2])[3];
  uVar5 = 0;
  local_8 = 0xffffffff;
  *(undefined4 *)((int)param_1 + 0x1448) = 0;
  *(undefined4 *)((int)param_1 + 0x144c) = 0x23d;
  psVar7 = psVar2;
  if (0 < (int)local_4) {
    do {
      if (*psVar7 == 0) {
        psVar7[1] = 0;
      }
      else {
        iVar6 = *(int *)((int)param_1 + 0x1448) + 1;
        *(int *)((int)param_1 + 0x1448) = iVar6;
        *(uint *)((int)param_1 + 0xb54 + iVar6 * 4) = uVar5;
        *(undefined1 *)(uVar5 + 0x1450 + (int)param_1) = 0;
        uVar10 = uVar5;
        local_8 = uVar5;
      }
      uVar5 = uVar5 + 1;
      psVar7 = psVar7 + 2;
    } while ((int)uVar5 < (int)local_4);
  }
  iVar6 = *(int *)((int)param_1 + 0x1448);
  while (iVar6 < 2) {
    if ((int)uVar10 < 2) {
      uVar5 = uVar10 + 1;
      uVar10 = uVar5;
    }
    else {
      uVar5 = 0;
    }
    *(int *)((int)param_1 + 0x1448) = iVar6 + 1;
    *(uint *)((int)param_1 + 0xb54 + (iVar6 + 1) * 4) = uVar5;
    psVar2[uVar5 * 2] = 1;
    *(undefined1 *)(uVar5 + 0x1450 + (int)param_1) = 0;
    *(int *)((int)param_1 + 0x16a0) = *(int *)((int)param_1 + 0x16a0) + -1;
    if (iVar9 != 0) {
      *(uint *)((int)param_1 + 0x16a4) =
           *(int *)((int)param_1 + 0x16a4) - (uint)*(ushort *)(iVar9 + 2 + uVar5 * 4);
    }
    local_8 = uVar10;
    iVar6 = *(int *)((int)param_1 + 0x1448);
  }
  param_2[1] = uVar10;
  for (iVar9 = *(int *)((int)param_1 + 0x1448) / 2; 0 < iVar9; iVar9 = iVar9 + -1) {
    FUN_004c92d0(param_1,psVar2,iVar9);
  }
  param_1 = psVar2 + local_4 * 2;
  do {
    iVar9 = *(int *)(iVar3 + 0xb58);
    *(undefined4 *)(iVar3 + 0xb58) = *(undefined4 *)(iVar3 + 0xb54 + *(int *)(iVar3 + 0x1448) * 4);
    *(int *)(iVar3 + 0x1448) = *(int *)(iVar3 + 0x1448) + -1;
    FUN_004c92d0(iVar3,psVar2,1);
    iVar6 = *(int *)(iVar3 + 0xb58);
    iVar8 = *(int *)(iVar3 + 0x144c) + -1;
    *(int *)(iVar3 + 0x144c) = iVar8;
    *(int *)(iVar3 + 0xb54 + iVar8 * 4) = iVar9;
    iVar8 = *(int *)(iVar3 + 0x144c) + -1;
    *(int *)(iVar3 + 0x144c) = iVar8;
    *(int *)(iVar3 + 0xb54 + iVar8 * 4) = iVar6;
    *param_1 = psVar2[iVar6 * 2] + psVar2[iVar9 * 2];
    bVar1 = *(byte *)(iVar9 + 0x1450 + iVar3);
    bVar4 = *(byte *)(iVar6 + 0x1450 + iVar3);
    if (bVar4 <= bVar1) {
      bVar4 = bVar1;
    }
    *(byte *)(local_4 + 0x1450 + iVar3) = bVar4 + 1;
    psVar2[iVar6 * 2 + 1] = (short)local_4;
    psVar2[iVar9 * 2 + 1] = (short)local_4;
    *(uint *)(iVar3 + 0xb58) = local_4;
    local_4 = local_4 + 1;
    param_1 = param_1 + 2;
    FUN_004c92d0(iVar3,psVar2,1);
  } while (1 < *(int *)(iVar3 + 0x1448));
  iVar9 = *(int *)(iVar3 + 0x144c) + -1;
  *(int *)(iVar3 + 0x144c) = iVar9;
  *(undefined4 *)(iVar3 + 0xb54 + iVar9 * 4) = *(undefined4 *)(iVar3 + 0xb58);
  FUN_004c9390(iVar3,param_2);
  FUN_004c95c0(psVar2,local_8,iVar3 + 0xb34);
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004c92d0  FUN_004c92d0 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c92d0(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  
  iVar3 = *(int *)(param_1 + 0xb54 + param_3 * 4);
  iVar4 = *(int *)(param_1 + 0x1448);
  iVar7 = param_3 * 2;
  if (iVar7 <= iVar4) {
    bVar8 = SBORROW4(iVar7,iVar4);
    iVar4 = iVar7 - iVar4;
    do {
      iVar6 = iVar7;
      if (bVar8 != iVar4 < 0) {
        iVar4 = *(int *)(param_1 + 0xb58 + iVar7 * 4);
        iVar5 = *(int *)(param_1 + 0xb54 + iVar7 * 4);
        uVar1 = *(ushort *)(param_2 + iVar4 * 4);
        uVar2 = *(ushort *)(param_2 + iVar5 * 4);
        if ((uVar1 < uVar2) ||
           ((uVar1 == uVar2 &&
            (*(byte *)(param_1 + 0x1450 + iVar4) <= *(byte *)(param_1 + 0x1450 + iVar5))))) {
          iVar6 = iVar7 + 1;
        }
      }
      iVar4 = *(int *)(param_1 + 0xb54 + iVar6 * 4);
      uVar1 = *(ushort *)(param_2 + iVar3 * 4);
      uVar2 = *(ushort *)(param_2 + iVar4 * 4);
      if ((uVar1 < uVar2) ||
         ((uVar1 == uVar2 &&
          (*(byte *)(iVar3 + 0x1450 + param_1) <= *(byte *)(param_1 + 0x1450 + iVar4))))) break;
      iVar7 = iVar6 * 2;
      *(int *)(param_1 + 0xb54 + param_3 * 4) = iVar4;
      iVar5 = *(int *)(param_1 + 0x1448);
      bVar8 = SBORROW4(iVar7,iVar5);
      iVar4 = iVar7 - iVar5;
      param_3 = iVar6;
    } while (iVar4 == 0 || iVar7 < iVar5);
  }
  *(int *)(param_1 + 0xb54 + param_3 * 4) = iVar3;
  return;
}
#endif


/* ---- 0x004c9390  FUN_004c9390 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c9390(int *param_1,int *param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  ushort *puVar2;
  ushort uVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  short *psVar15;
  int iVar16;
  ushort *puVar17;
  undefined4 *puVar18;
  uint uVar19;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar11 = (int)param_1;
  iVar5 = *param_2;
  iVar6 = param_2[1];
  piVar7 = (int *)param_2[2];
  iVar13 = *piVar7;
  iVar8 = piVar7[1];
  uVar19 = piVar7[4];
  iVar9 = piVar7[2];
  local_1c = 0;
  puVar18 = (undefined4 *)((int)param_1 + 0xb34);
  for (iVar14 = 8; iVar14 != 0; iVar14 = iVar14 + -1) {
    *puVar18 = 0;
    puVar18 = puVar18 + 1;
  }
  *(undefined2 *)
   (iVar5 + 2 + *(int *)((int)param_1 + 0xb54 + *(int *)((int)param_1 + 0x144c) * 4) * 4) = 0;
  iVar14 = *(int *)((int)param_1 + 0x144c) + 1;
  if (iVar14 < 0x23d) {
    param_1 = (int *)((int)param_1 + 0xb54 + iVar14 * 4);
    local_14 = 0x23d - iVar14;
    iVar14 = iVar14 + local_14;
    do {
      iVar10 = *param_1;
      iVar1 = iVar10 * 4;
      uVar12 = *(ushort *)(iVar5 + 2 + (uint)*(ushort *)(iVar5 + 2 + iVar10 * 4) * 4) + 1;
      if ((int)uVar19 < (int)uVar12) {
        local_1c = local_1c + 1;
        uVar12 = uVar19;
      }
      *(short *)(iVar5 + 2 + iVar1) = (short)uVar12;
      if (iVar10 <= iVar6) {
        psVar15 = (short *)(iVar11 + 0xb34 + uVar12 * 2);
        *psVar15 = *psVar15 + 1;
        iVar16 = 0;
        if (iVar9 <= iVar10) {
          iVar16 = *(int *)(iVar8 + (iVar10 - iVar9) * 4);
        }
        uVar3 = *(ushort *)(iVar5 + iVar1);
        *(uint *)(iVar11 + 0x16a0) = *(int *)(iVar11 + 0x16a0) + (uVar12 + iVar16) * (uint)uVar3;
        if (iVar13 != 0) {
          *(uint *)(iVar11 + 0x16a4) =
               *(int *)(iVar11 + 0x16a4) +
               ((uint)*(ushort *)(iVar13 + 2 + iVar1) + iVar16) * (uint)uVar3;
        }
      }
      param_1 = param_1 + 1;
      local_14 = local_14 - 1;
    } while (local_14 != 0);
  }
  if (local_1c != 0) {
    do {
      iVar13 = uVar19 - 1;
      psVar15 = (short *)(iVar11 + 0xb34 + iVar13 * 2);
      sVar4 = *(short *)(iVar11 + 0xb34 + iVar13 * 2);
      while (sVar4 == 0) {
        psVar15 = psVar15 + -1;
        iVar13 = iVar13 + -1;
        sVar4 = *psVar15;
      }
      psVar15 = (short *)(iVar11 + 0xb34 + iVar13 * 2);
      *psVar15 = *psVar15 + -1;
      psVar15 = (short *)(iVar11 + 0xb36 + iVar13 * 2);
      *psVar15 = *psVar15 + 2;
      psVar15 = (short *)(iVar11 + 0xb34 + uVar19 * 2);
      *psVar15 = *psVar15 + -1;
      local_1c = local_1c - 2;
    } while (0 < (int)local_1c);
    if (uVar19 != 0) {
      puVar17 = (ushort *)(iVar11 + 0xb34 + uVar19 * 2);
      param_2 = (int *)iVar14;
      do {
        uVar12 = (uint)*puVar17;
        if (uVar12 != 0) {
          iVar13 = iVar11 + 0xb54 + iVar14 * 4;
          param_1 = (int *)uVar12;
          do {
            iVar8 = *(int *)(iVar13 + -4);
            iVar14 = (int)param_2 + -1;
            iVar13 = iVar13 + -4;
            if (iVar8 <= iVar6) {
              puVar2 = (ushort *)(iVar5 + 2 + iVar8 * 4);
              uVar12 = (uint)*puVar2;
              if (uVar12 != uVar19) {
                *(uint *)(iVar11 + 0x16a0) =
                     *(int *)(iVar11 + 0x16a0) +
                     (uVar19 - uVar12) * (uint)*(ushort *)(iVar5 + iVar8 * 4);
                *puVar2 = (ushort)uVar19;
              }
              uVar12 = (int)param_1 - 1;
              param_1 = (int *)uVar12;
            }
            param_2 = (int *)iVar14;
          } while (uVar12 != 0);
        }
        uVar19 = uVar19 - 1;
        puVar17 = puVar17 + -1;
      } while (uVar19 != 0);
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004c95c0  FUN_004c95c0 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c95c0(undefined2 *param_1,int param_2,short *param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  short sVar1;
  undefined2 uVar2;
  uint uVar3;
  short *psVar4;
  int iVar5;
  #define asStack_20 (*(short (*)[16])(_frame + (0x30 - 0x20)))
  
  sVar1 = 0;
  psVar4 = asStack_20;
  iVar5 = 0xf;
  do {
    psVar4 = psVar4 + 1;
    sVar1 = (*param_3 + sVar1) * 2;
    iVar5 = iVar5 + -1;
    *psVar4 = sVar1;
    param_3 = param_3 + 1;
  } while (iVar5 != 0);
  if (-1 < param_2) {
    param_2 = param_2 + 1;
    do {
      uVar3 = (uint)(ushort)param_1[1];
      if (uVar3 != 0) {
        sVar1 = asStack_20[uVar3];
        asStack_20[uVar3] = sVar1 + 1;
        uVar2 = FUN_004ca460(sVar1,uVar3);
        *param_1 = uVar2;
      }
      param_1 = param_1 + 2;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return;
}
#undef asStack_20

#endif


/* ---- 0x004c9640  FUN_004c9640 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c9640(int param_1)

{
  int iVar1;
  
  FUN_004c96c0(param_1,param_1 + 0x8c,*(undefined4 *)(param_1 + 0xb14));
  FUN_004c96c0(param_1,param_1 + 0x980,*(undefined4 *)(param_1 + 0xb20));
  FUN_004c9090(param_1,param_1 + 0xb28);
  iVar1 = 0x12;
  do {
    if (*(short *)(param_1 + 0xa76 + (uint)(byte)(&DAT_004d9e38)[iVar1] * 4) != 0) break;
    iVar1 = iVar1 + -1;
  } while (2 < iVar1);
  *(int *)(param_1 + 0x16a0) = *(int *)(param_1 + 0x16a0) + iVar1 * 3 + 0x11;
  return;
}
#endif


/* ---- 0x004c96c0  FUN_004c96c0 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c96c0(int param_1,int param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  short *psVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  ushort *puVar6;
  int iVar7;
  int iVar8;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar2 = *(ushort *)(param_2 + 2);
  iVar7 = 0;
  local_4 = 0xffffffff;
  iVar3 = 7;
  iVar8 = 4;
  if (uVar2 == 0) {
    iVar3 = 0x8a;
    iVar8 = 3;
  }
  *(undefined2 *)(param_2 + 6 + param_3 * 4) = 0xffff;
  if (-1 < param_3) {
    puVar6 = (ushort *)(param_2 + 6);
    uVar4 = (uint)uVar2;
    param_2 = param_3 + 1;
    do {
      uVar5 = (uint)*puVar6;
      iVar7 = iVar7 + 1;
      if ((iVar3 <= iVar7) || (uVar4 != uVar5)) {
        if (iVar7 < iVar8) {
          psVar1 = (short *)(param_1 + 0xa74 + uVar4 * 4);
          *psVar1 = *psVar1 + (short)iVar7;
        }
        else if (uVar4 == 0) {
          if (iVar7 < 0xb) {
            *(short *)(param_1 + 0xab8) = *(short *)(param_1 + 0xab8) + 1;
          }
          else {
            *(short *)(param_1 + 0xabc) = *(short *)(param_1 + 0xabc) + 1;
          }
        }
        else {
          if (uVar4 != local_4) {
            psVar1 = (short *)(param_1 + 0xa74 + uVar4 * 4);
            *psVar1 = *psVar1 + 1;
          }
          *(short *)(param_1 + 0xab4) = *(short *)(param_1 + 0xab4) + 1;
        }
        iVar7 = 0;
        local_4 = uVar4;
        if (uVar5 == 0) {
          iVar3 = 0x8a;
          iVar8 = 3;
        }
        else if (uVar4 == uVar5) {
          iVar3 = 6;
          iVar8 = 3;
        }
        else {
          iVar3 = 7;
          iVar8 = 4;
        }
      }
      puVar6 = puVar6 + 2;
      param_2 = param_2 + -1;
      uVar4 = uVar5;
    } while (param_2 != 0);
  }
  return;
}
#undef local_4

#endif


/* ---- 0x004c97b0  FUN_004c97b0 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c97b0(int param_1,int param_2,int param_3,int param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(param_1 + 0x16b4);
  if (iVar2 < 0xc) {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | (ushort)(param_2 + -0x101 << ((byte)iVar2 & 0x1f));
    *(int *)(param_1 + 0x16b4) = iVar2 + 5;
  }
  else {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | (ushort)(param_2 + -0x101 << ((byte)iVar2 & 0x1f));
    *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) =
         *(undefined1 *)(param_1 + 0x16b0);
    iVar2 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar2;
    *(undefined1 *)(iVar2 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
    iVar2 = *(int *)(param_1 + 0x16b4);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x16b4) = iVar2 + -0xb;
    *(ushort *)(param_1 + 0x16b0) = (ushort)(param_2 + -0x101) >> (0x10U - (char)iVar2 & 0x1f);
  }
  iVar2 = *(int *)(param_1 + 0x16b4);
  if (iVar2 < 0xc) {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | (ushort)(param_3 + -1 << ((byte)iVar2 & 0x1f));
    *(int *)(param_1 + 0x16b4) = iVar2 + 5;
  }
  else {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | (ushort)(param_3 + -1 << ((byte)iVar2 & 0x1f));
    *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) =
         *(undefined1 *)(param_1 + 0x16b0);
    iVar2 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar2;
    *(undefined1 *)(iVar2 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
    iVar2 = *(int *)(param_1 + 0x16b4);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x16b4) = iVar2 + -0xb;
    *(ushort *)(param_1 + 0x16b0) = (ushort)(param_3 + -1) >> (0x10U - (char)iVar2 & 0x1f);
  }
  iVar3 = *(int *)(param_1 + 0x16b4);
  iVar2 = param_4 + -4;
  if (iVar3 < 0xd) {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar2 << ((byte)iVar3 & 0x1f));
    *(int *)(param_1 + 0x16b4) = iVar3 + 4;
  }
  else {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar2 << ((byte)iVar3 & 0x1f));
    *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) =
         *(undefined1 *)(param_1 + 0x16b0);
    iVar3 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar3;
    *(undefined1 *)(iVar3 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
    iVar3 = *(int *)(param_1 + 0x16b4);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x16b4) = iVar3 + -0xc;
    *(ushort *)(param_1 + 0x16b0) = (ushort)iVar2 >> (0x10U - (char)iVar3 & 0x1f);
  }
  iVar2 = 0;
  if (0 < param_4) {
    do {
      iVar3 = *(int *)(param_1 + 0x16b4);
      if (iVar3 < 0xe) {
        *(ushort *)(param_1 + 0x16b0) =
             *(ushort *)(param_1 + 0x16b0) |
             *(short *)(param_1 + 0xa76 + (uint)(byte)(&DAT_004d9e38)[iVar2] * 4) <<
             ((byte)iVar3 & 0x1f);
        *(int *)(param_1 + 0x16b4) = iVar3 + 3;
      }
      else {
        uVar1 = *(ushort *)(param_1 + 0xa76 + (uint)(byte)(&DAT_004d9e38)[iVar2] * 4);
        *(ushort *)(param_1 + 0x16b0) =
             *(ushort *)(param_1 + 0x16b0) | uVar1 << ((byte)iVar3 & 0x1f);
        *(undefined1 *)(*(int *)(param_1 + 0x14) + *(int *)(param_1 + 8)) =
             *(undefined1 *)(param_1 + 0x16b0);
        iVar3 = *(int *)(param_1 + 0x14) + 1;
        *(int *)(param_1 + 0x14) = iVar3;
        *(undefined1 *)(iVar3 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
        iVar3 = *(int *)(param_1 + 0x16b4);
        *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
        *(int *)(param_1 + 0x16b4) = iVar3 + -0xd;
        *(ushort *)(param_1 + 0x16b0) = uVar1 >> (0x10U - (char)iVar3 & 0x1f);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < param_4);
  }
  FUN_004c9a20(param_1,param_1 + 0x8c,param_2 + -1);
  FUN_004c9a20(param_1,param_1 + 0x980,param_3 + -1);
  return;
}
#endif


/* ---- 0x004c9a20  FUN_004c9a20 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c9a20(int param_1,int param_2,ushort *param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_8 = 0xffffffff;
  iVar2 = 7;
  iVar7 = 4;
  if (*(ushort *)(param_2 + 2) == 0) {
    iVar2 = 0x8a;
    iVar7 = 3;
  }
  if (-1 < (int)param_3) {
    local_4 = (int)param_3 + 1;
    iVar3 = 0;
    uVar5 = (uint)*(ushort *)(param_2 + 2);
    param_3 = (ushort *)(param_2 + 6);
    do {
      iVar4 = iVar3 + 1;
      uVar6 = (uint)*param_3;
      if ((iVar2 <= iVar4) || (uVar5 != uVar6)) {
        if (iVar4 < iVar7) {
          do {
            iVar2 = *(int *)(param_1 + 0x16b4);
            uVar8 = (uint)*(ushort *)(param_1 + 0xa76 + uVar5 * 4);
            if ((int)(0x10 - uVar8) < iVar2) {
              uVar1 = *(ushort *)(param_1 + 0xa74 + uVar5 * 4);
              *(ushort *)(param_1 + 0x16b0) =
                   *(ushort *)(param_1 + 0x16b0) | uVar1 << ((byte)iVar2 & 0x1f);
              *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
                   *(undefined1 *)(param_1 + 0x16b0);
              iVar2 = *(int *)(param_1 + 0x14) + 1;
              *(int *)(param_1 + 0x14) = iVar2;
              *(undefined1 *)(iVar2 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
              *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
              *(ushort *)(param_1 + 0x16b0) =
                   uVar1 >> (0x10U - (char)*(int *)(param_1 + 0x16b4) & 0x1f);
              *(uint *)(param_1 + 0x16b4) = (uVar8 - 0x10) + *(int *)(param_1 + 0x16b4);
            }
            else {
              *(ushort *)(param_1 + 0x16b0) =
                   *(ushort *)(param_1 + 0x16b0) |
                   *(short *)(param_1 + 0xa74 + uVar5 * 4) << ((byte)iVar2 & 0x1f);
              *(uint *)(param_1 + 0x16b4) = uVar8 + iVar2;
            }
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
        }
        else if (uVar5 == 0) {
          if (iVar4 < 0xb) {
            iVar2 = *(int *)(param_1 + 0x16b4);
            uVar8 = (uint)*(ushort *)(param_1 + 0xaba);
            if ((int)(0x10 - uVar8) < iVar2) {
              uVar1 = *(ushort *)(param_1 + 0xab8);
              *(ushort *)(param_1 + 0x16b0) =
                   *(ushort *)(param_1 + 0x16b0) | uVar1 << ((byte)iVar2 & 0x1f);
              *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
                   *(undefined1 *)(param_1 + 0x16b0);
              iVar2 = *(int *)(param_1 + 0x14) + 1;
              *(int *)(param_1 + 0x14) = iVar2;
              *(undefined1 *)(iVar2 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
              *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
              *(ushort *)(param_1 + 0x16b0) =
                   uVar1 >> (0x10U - (char)*(int *)(param_1 + 0x16b4) & 0x1f);
              *(uint *)(param_1 + 0x16b4) = (uVar8 - 0x10) + *(int *)(param_1 + 0x16b4);
            }
            else {
              *(ushort *)(param_1 + 0x16b0) =
                   *(ushort *)(param_1 + 0x16b0) |
                   *(short *)(param_1 + 0xab8) << ((byte)iVar2 & 0x1f);
              *(uint *)(param_1 + 0x16b4) = uVar8 + iVar2;
            }
            iVar2 = *(int *)(param_1 + 0x16b4);
            if (iVar2 < 0xe) {
              *(ushort *)(param_1 + 0x16b0) =
                   *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar3 + -2 << ((byte)iVar2 & 0x1f));
              iVar2 = iVar2 + 3;
LAB_004c9f39:
              *(int *)(param_1 + 0x16b4) = iVar2;
            }
            else {
              *(ushort *)(param_1 + 0x16b0) =
                   *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar3 + -2 << ((byte)iVar2 & 0x1f));
              *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
                   *(undefined1 *)(param_1 + 0x16b0);
              iVar2 = *(int *)(param_1 + 0x14) + 1;
              *(int *)(param_1 + 0x14) = iVar2;
              *(undefined1 *)(iVar2 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
              iVar2 = *(int *)(param_1 + 0x16b4);
              *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
              *(int *)(param_1 + 0x16b4) = iVar2 + -0xd;
              *(ushort *)(param_1 + 0x16b0) = (ushort)(iVar3 + -2) >> (0x10U - (char)iVar2 & 0x1f);
            }
          }
          else {
            iVar2 = *(int *)(param_1 + 0x16b4);
            uVar8 = (uint)*(ushort *)(param_1 + 0xabe);
            if ((int)(0x10 - uVar8) < iVar2) {
              uVar1 = *(ushort *)(param_1 + 0xabc);
              *(ushort *)(param_1 + 0x16b0) =
                   *(ushort *)(param_1 + 0x16b0) | uVar1 << ((byte)iVar2 & 0x1f);
              *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
                   *(undefined1 *)(param_1 + 0x16b0);
              iVar2 = *(int *)(param_1 + 0x14) + 1;
              *(int *)(param_1 + 0x14) = iVar2;
              *(undefined1 *)(iVar2 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
              *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
              *(ushort *)(param_1 + 0x16b0) =
                   uVar1 >> (0x10U - (char)*(int *)(param_1 + 0x16b4) & 0x1f);
              *(uint *)(param_1 + 0x16b4) = (uVar8 - 0x10) + *(int *)(param_1 + 0x16b4);
            }
            else {
              *(ushort *)(param_1 + 0x16b0) =
                   *(ushort *)(param_1 + 0x16b0) |
                   *(short *)(param_1 + 0xabc) << ((byte)iVar2 & 0x1f);
              *(uint *)(param_1 + 0x16b4) = uVar8 + iVar2;
            }
            iVar2 = *(int *)(param_1 + 0x16b4);
            if (iVar2 < 10) {
              *(ushort *)(param_1 + 0x16b0) =
                   *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar3 + -10 << ((byte)iVar2 & 0x1f));
              iVar2 = iVar2 + 7;
              goto LAB_004c9f39;
            }
            *(ushort *)(param_1 + 0x16b0) =
                 *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar3 + -10 << ((byte)iVar2 & 0x1f));
            *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
                 *(undefined1 *)(param_1 + 0x16b0);
            iVar2 = *(int *)(param_1 + 0x14) + 1;
            *(int *)(param_1 + 0x14) = iVar2;
            *(undefined1 *)(iVar2 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
            iVar2 = *(int *)(param_1 + 0x16b4);
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
            *(int *)(param_1 + 0x16b4) = iVar2 + -9;
            *(ushort *)(param_1 + 0x16b0) = (ushort)(iVar3 + -10) >> (0x10U - (char)iVar2 & 0x1f);
          }
        }
        else {
          if (uVar5 != local_8) {
            iVar2 = *(int *)(param_1 + 0x16b4);
            uVar8 = (uint)*(ushort *)(param_1 + 0xa76 + uVar5 * 4);
            iVar4 = iVar3;
            if ((int)(0x10 - uVar8) < iVar2) {
              uVar1 = *(ushort *)(param_1 + 0xa74 + uVar5 * 4);
              *(ushort *)(param_1 + 0x16b0) =
                   *(ushort *)(param_1 + 0x16b0) | uVar1 << ((byte)iVar2 & 0x1f);
              *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
                   *(undefined1 *)(param_1 + 0x16b0);
              iVar2 = *(int *)(param_1 + 0x14) + 1;
              *(int *)(param_1 + 0x14) = iVar2;
              *(undefined1 *)(iVar2 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
              *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
              *(ushort *)(param_1 + 0x16b0) =
                   uVar1 >> (0x10U - (char)*(int *)(param_1 + 0x16b4) & 0x1f);
              *(uint *)(param_1 + 0x16b4) = (uVar8 - 0x10) + *(int *)(param_1 + 0x16b4);
            }
            else {
              *(ushort *)(param_1 + 0x16b0) =
                   *(ushort *)(param_1 + 0x16b0) |
                   *(short *)(param_1 + 0xa74 + uVar5 * 4) << ((byte)iVar2 & 0x1f);
              *(uint *)(param_1 + 0x16b4) = uVar8 + iVar2;
            }
          }
          iVar2 = *(int *)(param_1 + 0x16b4);
          uVar8 = (uint)*(ushort *)(param_1 + 0xab6);
          if ((int)(0x10 - uVar8) < iVar2) {
            uVar1 = *(ushort *)(param_1 + 0xab4);
            *(ushort *)(param_1 + 0x16b0) =
                 *(ushort *)(param_1 + 0x16b0) | uVar1 << ((byte)iVar2 & 0x1f);
            *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
                 *(undefined1 *)(param_1 + 0x16b0);
            iVar2 = *(int *)(param_1 + 0x14) + 1;
            *(int *)(param_1 + 0x14) = iVar2;
            *(undefined1 *)(iVar2 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
            *(ushort *)(param_1 + 0x16b0) =
                 uVar1 >> (0x10U - (char)*(int *)(param_1 + 0x16b4) & 0x1f);
            *(uint *)(param_1 + 0x16b4) = (uVar8 - 0x10) + *(int *)(param_1 + 0x16b4);
          }
          else {
            *(ushort *)(param_1 + 0x16b0) =
                 *(ushort *)(param_1 + 0x16b0) | *(short *)(param_1 + 0xab4) << ((byte)iVar2 & 0x1f)
            ;
            *(uint *)(param_1 + 0x16b4) = uVar8 + iVar2;
          }
          iVar2 = *(int *)(param_1 + 0x16b4);
          if (iVar2 < 0xf) {
            *(ushort *)(param_1 + 0x16b0) =
                 *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar4 + -3 << ((byte)iVar2 & 0x1f));
            iVar2 = iVar2 + 2;
            goto LAB_004c9f39;
          }
          *(ushort *)(param_1 + 0x16b0) =
               *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar4 + -3 << ((byte)iVar2 & 0x1f));
          *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
               *(undefined1 *)(param_1 + 0x16b0);
          iVar2 = *(int *)(param_1 + 0x14) + 1;
          *(int *)(param_1 + 0x14) = iVar2;
          *(undefined1 *)(iVar2 + *(int *)(param_1 + 8)) = *(undefined1 *)(param_1 + 0x16b1);
          iVar2 = *(int *)(param_1 + 0x16b4);
          *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
          *(int *)(param_1 + 0x16b4) = iVar2 + -0xe;
          *(ushort *)(param_1 + 0x16b0) = (ushort)(iVar4 + -3) >> (0x10U - (char)iVar2 & 0x1f);
        }
        iVar4 = 0;
        local_8 = uVar5;
        if (uVar6 == 0) {
          iVar2 = 0x8a;
          iVar7 = 3;
        }
        else if (uVar5 == uVar6) {
          iVar2 = 6;
          iVar7 = 3;
        }
        else {
          iVar2 = 7;
          iVar7 = 4;
        }
      }
      param_3 = param_3 + 2;
      local_4 = local_4 - 1;
      iVar3 = iVar4;
      uVar5 = uVar6;
    } while (local_4 != 0);
  }
  return;
}
#undef local_4
#undef local_8

#endif


/* ---- 0x004c9fa0  FUN_004c9fa0 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004c9fa0(int param_1,int param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar3 = 0;
  if (*(int *)(param_1 + 0x1698) != 0) {
    do {
      uVar9 = (uint)*(ushort *)(*(int *)(param_1 + 0x169c) + uVar3 * 2);
      uVar10 = (uint)*(byte *)(uVar3 + *(int *)(param_1 + 0x1690));
      uVar3 = uVar3 + 1;
      if (uVar9 == 0) {
        uVar9 = (uint)*(ushort *)(param_2 + 2 + uVar10 * 4);
        iVar6 = *(int *)(param_1 + 0x16b4);
        if ((int)(0x10 - uVar9) < iVar6) {
          uVar2 = *(ushort *)(param_2 + uVar10 * 4);
          *(ushort *)(param_1 + 0x16b0) =
               *(ushort *)(param_1 + 0x16b0) | uVar2 << ((byte)iVar6 & 0x1f);
          *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
               *(undefined1 *)(param_1 + 0x16b0);
          iVar6 = *(int *)(param_1 + 0x14) + 1;
          *(int *)(param_1 + 0x14) = iVar6;
          *(undefined1 *)(*(int *)(param_1 + 8) + iVar6) = *(undefined1 *)(param_1 + 0x16b1);
          iVar6 = *(int *)(param_1 + 0x16b4);
          *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
          *(uint *)(param_1 + 0x16b4) = (uVar9 - 0x10) + iVar6;
          *(ushort *)(param_1 + 0x16b0) = uVar2 >> (0x10U - (char)iVar6 & 0x1f);
        }
        else {
          *(ushort *)(param_1 + 0x16b0) =
               *(ushort *)(param_1 + 0x16b0) |
               *(short *)(param_2 + uVar10 * 4) << ((byte)iVar6 & 0x1f);
          *(uint *)(param_1 + 0x16b4) = uVar9 + iVar6;
        }
      }
      else {
        uVar4 = (uint)(byte)(&DAT_004da548)[uVar10];
        iVar5 = uVar4 * 4;
        uVar8 = (uint)*(ushort *)(param_2 + 0x406 + iVar5);
        iVar6 = *(int *)(param_1 + 0x16b4);
        if ((int)(0x10 - uVar8) < iVar6) {
          uVar2 = *(ushort *)(param_2 + 0x404 + uVar4 * 4);
          *(ushort *)(param_1 + 0x16b0) =
               *(ushort *)(param_1 + 0x16b0) | uVar2 << ((byte)iVar6 & 0x1f);
          *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
               *(undefined1 *)(param_1 + 0x16b0);
          iVar6 = *(int *)(param_1 + 0x14) + 1;
          *(int *)(param_1 + 0x14) = iVar6;
          *(undefined1 *)(*(int *)(param_1 + 8) + iVar6) = *(undefined1 *)(param_1 + 0x16b1);
          *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
          *(ushort *)(param_1 + 0x16b0) = uVar2 >> (0x10U - (char)*(int *)(param_1 + 0x16b4) & 0x1f)
          ;
          *(uint *)(param_1 + 0x16b4) = (uVar8 - 0x10) + *(int *)(param_1 + 0x16b4);
        }
        else {
          *(ushort *)(param_1 + 0x16b0) =
               *(ushort *)(param_1 + 0x16b0) |
               *(short *)(param_2 + 0x404 + uVar4 * 4) << ((byte)iVar6 & 0x1f);
          *(uint *)(param_1 + 0x16b4) = uVar8 + iVar6;
        }
        iVar6 = *(int *)(&DAT_004d9cf8 + iVar5);
        if (iVar6 != 0) {
          iVar7 = *(int *)(param_1 + 0x16b4);
          iVar5 = uVar10 - *(int *)(&DAT_004da648 + iVar5);
          if (0x10 - iVar6 < iVar7) {
            *(ushort *)(param_1 + 0x16b0) =
                 *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar5 << ((byte)iVar7 & 0x1f));
            *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
                 *(undefined1 *)(param_1 + 0x16b0);
            iVar7 = *(int *)(param_1 + 0x14) + 1;
            *(int *)(param_1 + 0x14) = iVar7;
            *(undefined1 *)(*(int *)(param_1 + 8) + iVar7) = *(undefined1 *)(param_1 + 0x16b1);
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
            *(ushort *)(param_1 + 0x16b0) =
                 (ushort)iVar5 >> (0x10U - (char)*(int *)(param_1 + 0x16b4) & 0x1f);
            *(int *)(param_1 + 0x16b4) = iVar6 + -0x10 + *(int *)(param_1 + 0x16b4);
          }
          else {
            *(ushort *)(param_1 + 0x16b0) =
                 *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar5 << ((byte)iVar7 & 0x1f));
            *(int *)(param_1 + 0x16b4) = iVar6 + iVar7;
          }
        }
        uVar10 = uVar9 - 1;
        if (uVar10 < 0x100) {
          bVar1 = (&DAT_004da347)[uVar9];
        }
        else {
          bVar1 = (&DAT_004da448)[uVar10 >> 7];
        }
        iVar6 = (uint)bVar1 * 4;
        iVar5 = *(int *)(param_1 + 0x16b4);
        uVar9 = (uint)*(ushort *)(param_3 + 2 + iVar6);
        if ((int)(0x10 - uVar9) < iVar5) {
          uVar2 = *(ushort *)(param_3 + iVar6);
          *(ushort *)(param_1 + 0x16b0) =
               *(ushort *)(param_1 + 0x16b0) | uVar2 << ((byte)iVar5 & 0x1f);
          *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
               *(undefined1 *)(param_1 + 0x16b0);
          iVar5 = *(int *)(param_1 + 0x14) + 1;
          *(int *)(param_1 + 0x14) = iVar5;
          *(undefined1 *)(*(int *)(param_1 + 8) + iVar5) = *(undefined1 *)(param_1 + 0x16b1);
          *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
          *(ushort *)(param_1 + 0x16b0) = uVar2 >> (0x10U - (char)*(int *)(param_1 + 0x16b4) & 0x1f)
          ;
          *(uint *)(param_1 + 0x16b4) = (uVar9 - 0x10) + *(int *)(param_1 + 0x16b4);
        }
        else {
          *(ushort *)(param_1 + 0x16b0) =
               *(ushort *)(param_1 + 0x16b0) | *(short *)(param_3 + iVar6) << ((byte)iVar5 & 0x1f);
          *(uint *)(param_1 + 0x16b4) = uVar9 + iVar5;
        }
        iVar5 = *(int *)(&DAT_004d9d70 + iVar6);
        if (iVar5 != 0) {
          iVar7 = uVar10 - *(int *)(&DAT_004da6c0 + iVar6);
          iVar6 = *(int *)(param_1 + 0x16b4);
          if (0x10 - iVar5 < iVar6) {
            *(ushort *)(param_1 + 0x16b0) =
                 *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar7 << ((byte)iVar6 & 0x1f));
            *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
                 *(undefined1 *)(param_1 + 0x16b0);
            iVar6 = *(int *)(param_1 + 0x14) + 1;
            *(int *)(param_1 + 0x14) = iVar6;
            *(undefined1 *)(*(int *)(param_1 + 8) + iVar6) = *(undefined1 *)(param_1 + 0x16b1);
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
            iVar5 = iVar5 + -0x10 + *(int *)(param_1 + 0x16b4);
            *(ushort *)(param_1 + 0x16b0) =
                 (ushort)iVar7 >> (0x10U - (char)*(int *)(param_1 + 0x16b4) & 0x1f);
          }
          else {
            *(ushort *)(param_1 + 0x16b0) =
                 *(ushort *)(param_1 + 0x16b0) | (ushort)(iVar7 << ((byte)iVar6 & 0x1f));
            iVar5 = iVar5 + iVar6;
          }
          *(int *)(param_1 + 0x16b4) = iVar5;
        }
      }
    } while (uVar3 < *(uint *)(param_1 + 0x1698));
  }
  iVar6 = *(int *)(param_1 + 0x16b4);
  uVar3 = (uint)*(ushort *)(param_2 + 0x402);
  if ((int)(0x10 - uVar3) < iVar6) {
    uVar2 = *(ushort *)(param_2 + 0x400);
    *(ushort *)(param_1 + 0x16b0) = *(ushort *)(param_1 + 0x16b0) | uVar2 << ((byte)iVar6 & 0x1f);
    *(undefined1 *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14)) =
         *(undefined1 *)(param_1 + 0x16b0);
    iVar6 = *(int *)(param_1 + 0x14) + 1;
    *(int *)(param_1 + 0x14) = iVar6;
    *(undefined1 *)(*(int *)(param_1 + 8) + iVar6) = *(undefined1 *)(param_1 + 0x16b1);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
    *(ushort *)(param_1 + 0x16b0) = uVar2 >> (0x10U - (char)*(int *)(param_1 + 0x16b4) & 0x1f);
    *(uint *)(param_1 + 0x16b4) = (uVar3 - 0x10) + *(int *)(param_1 + 0x16b4);
  }
  else {
    *(ushort *)(param_1 + 0x16b0) =
         *(ushort *)(param_1 + 0x16b0) | *(short *)(param_2 + 0x400) << ((byte)iVar6 & 0x1f);
    *(uint *)(param_1 + 0x16b4) = uVar3 + iVar6;
  }
  *(uint *)(param_1 + 0x16ac) = (uint)*(ushort *)(param_2 + 0x402);
  return;
}
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004ca3f0  FUN_004ca3f0 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004ca3f0(int param_1)

{
  ushort uVar1;
  ushort *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  uVar5 = 0;
  uVar3 = 0;
  puVar2 = (ushort *)(param_1 + 0x8c);
  iVar4 = 7;
  do {
    uVar1 = *puVar2;
    puVar2 = puVar2 + 2;
    uVar3 = uVar3 + uVar1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  puVar2 = (ushort *)(param_1 + 0xa8);
  iVar4 = 0x79;
  do {
    uVar1 = *puVar2;
    puVar2 = puVar2 + 2;
    uVar5 = uVar5 + uVar1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  puVar2 = (ushort *)(param_1 + 0x28c);
  iVar4 = 0x80;
  do {
    uVar1 = *puVar2;
    puVar2 = puVar2 + 2;
    uVar3 = uVar3 + uVar1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  *(char *)(param_1 + 0x1c) = '\x01' - (uVar5 >> 2 < uVar3);
  return;
}
#endif


/* ---- 0x004ca460  FUN_004ca460 ---- */
/* NOT COMPILED: names/lib_replace.json (zlib): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
uint FUN_004ca460(uint param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = 0;
  do {
    uVar2 = uVar1;
    uVar3 = param_1 & 1;
    param_1 = param_1 >> 1;
    param_2 = param_2 + -1;
    uVar1 = (uVar2 | uVar3) << 1;
  } while (0 < param_2);
  return uVar2 & 0x7fffffff | uVar3;
}
#endif


/* ---- 0x004cba30  FUN_004cba30 ---- */
undefined4 FUN_004cba30(int *param_1,uint param_2)

{
  PTR_008d7864 = param_1;
  UINT_008da4e8 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_wave_flobdec_004f337c,&PTR_FUN_004f3310);
  (*(code *)*PTR_008d7864)(s_FLOBDEC_insane_wave_004f3368,&PTR_FUN_004f3320);
  return 0;
}

/* ---- 0x004cba70  FUN_004cba70 ---- */
void FUN_004cba70(void)

{
  (*(code *)PTR_008d7864[1])(s_FLOBDEC_insane_wave_004f3368);
  (*(code *)PTR_008d7864[1])(s_LECMODULE_insane_wave_flobdec_004f337c);
  return;
}

/* ---- 0x004cbaa0  FUN_004cbaa0 ---- */
int FUN_004cbaa0(void)

{
  UINT_008da4ec = (*(code *)PTR_008d7864[2])(s_SOUND_004f3434,UINT_008da4e8);
  if (UINT_008da4ec == 0) {
    (*(code *)PTR_008d7864[8])(s_D_WAVE__Cannot_allocate_sound_se_004f340c);
    return -1;
  }
  PTR_008d7850 = (int *)(*(code *)PTR_008d7864[2])(s_MEMORY_004f3404,UINT_008da4e8);
  if (PTR_008d7850 == (int *)0x0) {
    (*(code *)PTR_008d7864[8])(s_D_WAVE__Cannot_allocate_memory_s_004f33d8);
    return -1;
  }
  PTR_008da4f0 = (int *)(*(code *)*PTR_008d7850)
                                  (500000,s_C__grimsrc_libs_lecsmush_insane__004f339c,0x72);
  return (PTR_008da4f0 != (int *)0x0) - 1;
}

/* ---- 0x004cbb30  FUN_004cbb30 ---- */
void FUN_004cbb30(void)

{
  (*(code *)PTR_008d7864[3])(UINT_008da4ec);
  (*(code *)PTR_008d7864[3])(PTR_008d7850);
  if (PTR_008da4f0 != (int *)0x0) {
    (*(code *)PTR_008d7850[1])(PTR_008da4f0,s_C__grimsrc_libs_lecsmush_insane__004f339c,0x82);
  }
  PTR_008da4f0 = (int *)0x0;
  return;
}

/* ---- 0x004cbb80  FUN_004cbb80 ---- */
char * FUN_004cbb80(int param_1)

{
  if (param_1 == 0) {
    return s_Audio_004f343c;
  }
  if (param_1 != 1) {
    if (param_1 != 2) {
      return &DAT_004f5a98;
    }
    return s_Decompresses_Variable_Bit_Rate_A_004f346c;
  }
  return s_Decompresses_VBR_ADPCM_16_bit_au_004f3444;
}

/* ---- 0x004cbbb0  FUN_004cbbb0 ---- */
undefined4 FUN_004cbbb0(void)

{
  return 0x57617665;
}

/* ---- 0x004cbbc0  FUN_004cbbc0 ---- */
undefined4 FUN_004cbbc0(void)

{
  return 4;
}

/* ---- 0x004cbbd0  FUN_004cbbd0 ---- */
void FUN_004cbbd0(void)

{
  DAT_008d785e = 0;
  return;
}

/* ---- 0x004cbbe0  FUN_004cbbe0 ---- */
undefined4 FUN_004cbbe0(int param_1)

{
  DAT_008d785e = 0;
  UINT_008d7860 = *(uint *)(param_1 + 8);
  return 0;
}

/* ---- 0x004cbc00  FUN_004cbc00 ---- */
undefined4 __cdecl
FUN_004cbc00(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint *param_6)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  byte *pbVar6;
  uint uVar7;
  
  uVar4 = UINT_008d7860;
  uVar7 = 1;
  uVar1 = *param_6;
  puVar5 = param_6 + 1;
  uVar1 = (uVar1 & 0xff00 | uVar1 << 0x10) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8;
  if ((int)uVar1 < 0) {
    uVar1 = *puVar5;
    uVar1 = (uVar1 & 0xff00 | uVar1 << 0x10) << 8 | (uVar1 >> 0x10 | uVar1 & 0xff0000) >> 8;
    if (uVar1 != UINT_004f3340) {
      DAT_008d785e = 0;
      UINT_004f3340 = uVar1;
    }
    uVar1 = param_6[2];
    uVar1 = (uVar1 & 0xff00 | uVar1 << 0x10) << 8 | (uVar1 >> 0x10 | uVar1 & 0xff0000) >> 8;
    puVar5 = param_6 + 3;
  }
  DAT_008d7858 = (byte)*puVar5;
  if ((char)DAT_008d7858 < '\0') {
    DAT_008d7858 = ~DAT_008d7858;
    uVar7 = 2;
  }
  pbVar6 = (byte *)((int)puVar5 + 3);
  DAT_008d785a = CONCAT11((char)*(undefined2 *)((int)puVar5 + 1),
                          (char)((ushort)*(undefined2 *)((int)puVar5 + 1) >> 8));
  if (1 < uVar7) {
    DAT_008d7859 = *pbVar6;
    pbVar6 = (byte *)((int)puVar5 + 6);
    DAT_008d785c = CONCAT11((char)(short)puVar5[1],(char)((ushort)(short)puVar5[1] >> 8));
  }
  if (UINT_008da4ec != 0) {
    if (DAT_008d785e == 0) {
      *PTR_008da4f0 = UINT_004f34b0;
      uVar3 = uVar1 * uVar7 * 2 + 0x2e;
      PTR_008da4f0[1] =
           (uVar3 & 0xff00 | uVar3 * 0x10000) << 8 | (uVar3 & 0xff0000 | uVar3 >> 0x10) >> 8;
      *(undefined2 *)(PTR_008da4f0 + 2) = 100;
      *(short *)((int)PTR_008da4f0 + 10) = DAT_008d785e;
      *(undefined2 *)(PTR_008da4f0 + 3) = 100;
      *(undefined1 *)(PTR_008da4f0 + 4) = 0x7f;
      *(undefined1 *)((int)PTR_008da4f0 + 0x11) = 0;
      uVar3 = uVar4 + 0x24;
      *(uint *)((int)PTR_008da4f0 + 0x16) =
           (uVar3 & 0xff00 | uVar3 * 0x10000) << 8 | (uVar3 & 0xff0000 | uVar3 >> 0x10) >> 8;
      *(undefined4 *)((int)PTR_008da4f0 + 0x1e) = 0xc000000;
      *(undefined1 *)((int)PTR_008da4f0 + 0x22) = 1;
      *(undefined1 *)((int)PTR_008da4f0 + 0x23) = 8;
      PTR_008da4f0[9] = 0;
      uVar3 = (uVar4 & 0xff00 | uVar4 << 0x10) << 8 | (uVar4 & 0xff0000 | uVar4 >> 0x10) >> 8;
      PTR_008da4f0[10] = uVar3;
      *(undefined1 *)(PTR_008da4f0 + 0xb) = 5;
      *(undefined1 *)((int)PTR_008da4f0 + 0x2d) = 0;
      uVar4 = UINT_004f34a8;
      if (uVar7 != 1) {
        uVar4 = UINT_004f34a0;
      }
      *(uint *)((int)PTR_008da4f0 + 0x2e) = uVar4;
      *(uint *)((int)PTR_008da4f0 + 0x32) = uVar3;
      iVar2 = (int)PTR_008da4f0 + 0x36;
    }
    else {
      *PTR_008da4f0 = UINT_004f34b0;
      uVar4 = uVar1 * uVar7 * 2 + 10;
      PTR_008da4f0[1] =
           (uVar4 & 0xff00 | uVar4 * 0x10000) << 8 | (uVar4 & 0xff0000 | uVar4 >> 0x10) >> 8;
      *(undefined2 *)(PTR_008da4f0 + 2) = 100;
      *(short *)((int)PTR_008da4f0 + 10) = DAT_008d785e;
      *(undefined2 *)(PTR_008da4f0 + 3) = 100;
      *(undefined1 *)(PTR_008da4f0 + 4) = 0x7f;
      *(undefined1 *)((int)PTR_008da4f0 + 0x11) = 0;
      iVar2 = (int)PTR_008da4f0 + 0x12;
    }
    FUN_004cbf50(iVar2,pbVar6,uVar1,uVar7);
    (**(code **)UINT_008da4ec)(PTR_008da4f0,0xffffffff,0x7f,0,0x40);
    DAT_008d785e = DAT_008d785e + 1;
  }
  if ((DAT_008d785e != 0) && (100000 < UINT_008d7860)) {
    return 0;
  }
  return 0x80;
}

/* ---- 0x004cbf40  FUN_004cbf40 ---- */
undefined4 FUN_004cbf40(void)

{
  return 0xffffffff;
}

/* ---- 0x004cbf50  FUN_004cbf50 ---- */
void FUN_004cbf50(int param_1,undefined1 *param_2,uint param_3,uint param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  ushort *puVar8;
  undefined2 *puVar9;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  iVar6 = 0;
  if (UINT_008da4f4 == 0) {
    uVar7 = 0;
    local_28 = (uint)&DAT_008d7868;
    do {
      puVar8 = &DAT_004daa58;
      puVar9 = (undefined2 *)local_28;
      do {
        local_24 = (uint)*puVar8;
        uVar2 = 0x20;
        iVar4 = 0;
        do {
          if ((uVar7 & uVar2) != 0) {
            iVar4 = iVar4 + local_24;
          }
          local_24 = local_24 >> 1;
          uVar2 = uVar2 >> 1;
        } while (uVar2 != 0);
        *puVar9 = (short)iVar4;
        puVar8 = puVar8 + 1;
        puVar9 = puVar9 + 0x40;
      } while (puVar8 < &DAT_004dab0a);
      uVar7 = uVar7 + 1;
      local_28 = local_28 + 2;
    } while (local_28 < &DAT_008d78e8);
    UINT_008da4f4 = 1;
  }
  local_24 = (uint)CONCAT11(*param_2,param_2[1]);
  local_28 = (uint)(param_2 + 2);
  local_18 = 0;
  if (param_4 != 0) {
    local_14 = (uint)&DAT_008d785a;
    do {
      local_20 = param_1 - (int)IMG_ADDR(0x008d785a) + local_14;
      param_2 = (undefined1 *)(int)(char)(&DAT_008d7858)[local_18];
      uVar7 = (uint)*(short *)local_14;
      if (param_3 != 0) {
        local_1c = param_3;
        do {
          bVar1 = (&DAT_004dab10)[(int)param_2];
          local_10 = (uint)bVar1;
          iVar6 = iVar6 + local_10;
          uVar5 = 1 << (bVar1 - 1 & 0x1f);
          local_c = (uint)(byte)((char)uVar5 - 1);
          uVar2 = (local_24 & 0xffff) >> (0x10U - (char)iVar6 & 0x1f) & (uVar5 | local_c);
          if (7 < iVar6) {
            local_24 = (local_24 & 0xff) << 8 |
                       CONCAT22((short)(local_28 >> 0x10),(ushort)*(byte *)local_28);
            local_28 = local_28 + 1;
            iVar6 = iVar6 + -8;
          }
          if ((uVar2 & uVar5) == 0) {
            uVar5 = 0;
          }
          else {
            uVar2 = uVar2 ^ uVar5;
          }
          if (uVar2 == local_c) {
            uVar7 = (int)(short)(local_24 << ((byte)iVar6 & 0x1f)) & 0xffffff00U |
                    (ushort)(CONCAT11((undefined1)local_24,*(undefined1 *)local_28) >>
                            (8 - (byte)iVar6 & 0x1f)) & 0xff;
            local_24 = (uint)CONCAT11(*(undefined1 *)local_28,*(undefined1 *)(local_28 + 1));
            local_28 = local_28 + 2;
          }
          else {
            uVar3 = (uint)(ushort)(&DAT_008d7868)[uVar2 << (7 - bVar1 & 0x1f) | (int)param_2 << 6];
            if (uVar2 != 0) {
              uVar3 = uVar3 + ((ushort)(&DAT_004daa58)[(int)param_2] >> (bVar1 - 1 & 0x1f));
            }
            if (uVar5 != 0) {
              uVar3 = -uVar3;
            }
            uVar7 = uVar7 + uVar3;
            if ((int)uVar7 < -0x8000) {
              uVar7 = 0xffff8000;
            }
            else if (0x7fff < (int)uVar7) {
              uVar7 = 0x7fff;
            }
          }
          *(short *)local_20 = (short)uVar7;
          local_20 = local_20 + param_4 * 2;
          param_2 = (undefined1 *)
                    ((int)param_2 + (int)*(char *)(*(int *)(&DAT_004f3348 + local_10 * 4) + uVar2));
          if ((int)param_2 < 0) {
            param_2 = (undefined1 *)0x0;
          }
          else if (0x58 < (int)param_2) {
            param_2 = (undefined1 *)0x58;
          }
          local_1c = local_1c - 1;
        } while (local_1c != 0);
      }
      (&DAT_008d7858)[local_18] = PIECE(param_2,0,1);
      *(short *)local_14 = (short)uVar7;
      local_18 = local_18 + 1;
      local_14 = local_14 + 2;
    } while (local_18 < param_4);
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004cd3f0  FUN_004cd3f0 ---- */
int FUN_004cd3f0(uint param_1,uint param_2)

{
  return (int)((param_1 & 0xf800) + (param_2 & 0xf800) & 0x1f000 |
               (param_1 & 0x7e0) + (param_2 & 0x7e0) & 0xfc0 | (param_2 & 0x1f) + (param_1 & 0x1f))
         >> 1;
}

/* ---- 0x004ce010  FUN_004ce010 ---- */
uint FUN_004ce010(void)

{
  return g_dwTimerStep;
}

/* ---- 0x004ce020  FUN_004ce020 ---- */
void FUN_004ce020(int param_1)

{
  uint *puVar1;
  
  puVar1 = &UINT_008da60c;
  do {
    if ((puVar1[-5] != 0) && ((puVar1[-3] & 8) != 0)) {
      if (0 < param_1) {
        *puVar1 = *puVar1 + (param_1 - puVar1[2]);
      }
      puVar1[2] = 0;
    }
    puVar1 = puVar1 + 8;
  } while ((int)puVar1 < IMG_ADDR(0x008da86c));
  return;
}

/* ---- 0x004ce2e0  FUN_004ce2e0 ---- */
undefined4 FUN_004ce2e0(int *param_1,uint param_2)

{
  PTR_008da894 = param_1;
  UINT_008da898 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_bitmap_004f3cec,&PTR_FUN_004f3cc0);
  (*(code *)*PTR_008da894)(s_BITMAP_insane_004f3cdc,&PTR_VideoBitmap_Create_004f3cd0);
  return 0;
}

/* ---- 0x004ce320  FUN_004ce320 ---- */
void FUN_004ce320(void)

{
  (*(code *)PTR_008da894[1])(s_BITMAP_insane_004f3cdc);
  (*(code *)PTR_008da894[1])(s_LECMODULE_insane_bitmap_004f3cec);
  return;
}

/* ---- 0x004ce350  FUN_004ce350 ---- */
undefined4 FUN_004ce350(void)

{
  PTR_008da890 = (int *)(*(code *)PTR_008da894[2])(s_MEMORY_workspace_004f14ec,UINT_008da898);
  UINT_008da89c = (*(code *)PTR_008da894[2])(s_VIDEO_getbm_004f3d34,UINT_008da898);
  if (PTR_008da890 == (int *)0x0) {
    (*(code *)PTR_008da894[8])(s_Video_Module__Cannot_allocate_me_004f3d04);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004ce3b0  FUN_004ce3b0 ---- */
void FUN_004ce3b0(void)

{
  (*(code *)PTR_008da894[3])(PTR_008da890);
  if (UINT_008da89c != 0) {
    (*(code *)PTR_008da894[3])(UINT_008da89c);
  }
  return;
}

/* ---- 0x004ce840  FUN_004ce840 ---- */
undefined4
FUN_004ce840(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6,
            undefined4 *param_7)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *puVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  if (param_4 == 0) {
    local_4 = param_7[1];
  }
  iVar1 = (*(code *)*PTR_008da890)
                    (param_5 * param_3 * param_2 + 0x5c + local_4 * 4,
                     s_C__grimsrc_libs_lecsmush_insane__004f3d64,0x162);
  if (iVar1 == 0) {
    return 0xffffff9b;
  }
  *param_1 = iVar1 + 8;
  *(int *)(iVar1 + 8) = iVar1 + 0x5c;
  *(int *)(*param_1 + 4) = param_2;
  *(int *)(*param_1 + 0x14) = param_5 * param_2;
  *(int *)(*param_1 + 8) = param_3;
  *(int *)(*param_1 + 0xc) = param_5;
  *(undefined4 *)(*param_1 + 0x10) = param_6;
  *(undefined4 *)(*param_1 + 0x1c) = 0;
  *(undefined4 *)(*param_1 + 0x18) = 0;
  *(int *)(*param_1 + 0x20) = param_4;
  switch(param_4) {
  case 0:
    *(uint *)(*param_1 + 0x28) = local_4;
    *(int *)(*param_1 + 0x24) = iVar1 + 0x5c;
    return 0;
  case 1:
  case 3:
  case 5:
    puVar2 = (undefined4 *)(*param_1 + 0x24);
    for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_7;
      param_7 = param_7 + 1;
      puVar2 = puVar2 + 1;
    }
    return 0;
  case 2:
  case 4:
  case 6:
    puVar2 = (undefined4 *)(*param_1 + 0x24);
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_7;
      param_7 = param_7 + 1;
      puVar2 = puVar2 + 1;
    }
    return 0;
  case 7:
    iVar1 = *param_1;
    *(undefined4 *)(iVar1 + 0x24) = *param_7;
    *(undefined4 *)(iVar1 + 0x28) = param_7[1];
    *(undefined4 *)(iVar1 + 0x2c) = param_7[2];
  }
  return 0;
}
#undef local_4


/* ---- 0x004ce980  FUN_004ce980 ---- */
void FUN_004ce980(int *param_1)

{
  if (*param_1 + -8 != 0) {
    (*(code *)PTR_008da890[1])(*param_1 + -8,s_C__grimsrc_libs_lecsmush_insane__004f3d64,0x1be);
  }
  *param_1 = 0;
  return;
}

/* ---- 0x004ce9b0  FUN_004ce9b0 ---- */
void FUN_004ce9b0(undefined4 *param_1,undefined4 param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  #define local_14 (*(undefined1 (*)[20])(_frame + (0x30 - 0x14)))
  
  if (0 < (int)param_1[5]) {
    if (param_1[8] == 0) {
      FUN_004d5e50(*param_1,param_2,param_1[3] * param_1[2] * param_1[5]);
      return;
    }
    iVar1 = param_1[2];
    uVar2 = *param_1;
    iVar3 = param_1[1];
    Video_PixelsFromRgba(local_14,param_1,1,0,(byte *)&param_2);
    Video_FillPixels(uVar2,param_1,iVar1 * iVar3,local_14);
  }
  return;
}
#undef local_14


/* ---- 0x004ced70  FUN_004ced70 ---- */
undefined4 FUN_004ced70(int param_1,void *param_2,void *param_3,byte *param_4)

{
  byte *src;
  
  if ((((*(int *)(param_1 + 0x20) == 0) && (*(int *)(param_1 + 0xc) == 1)) &&
      (*(int *)((int)param_2 + 0x20) != 0)) &&
     ((src = *(byte **)(param_1 + 0x24), *(byte **)(param_1 + 0x24) != (byte *)0x0 ||
      (src = param_4, param_4 != (byte *)0x0)))) {
    Video_PixelsFromRgba(param_3,param_2,0x100,0,src);
    return 0;
  }
  return 0xffffffff;
}

/* ---- 0x004d2d70  FUN_004d2d70 ---- */
void FUN_004d2d70(int *param_1)

{
  Mixer_Free(param_1);
  return;
}

/* ---- 0x004d54b4  FUN_004d54b4 ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
float10 FUN_004d54b4(void)

{
  ushort in_FPUStatusWord;
  float10 in_ST0;
  float10 in_ST1;
  float10 extraout_ST1;
  
  do {
    if (UINT_008d0aa0 == 1) {
      in_ST1 = (float10)FUN_004b9b1c();
      in_ST0 = extraout_ST1;
    }
    else {
      in_ST1 = in_ST1 - PUN(float10,(unkint10)(in_ST1 / in_ST0)) * in_ST0;
    }
  } while ((in_FPUStatusWord & 0x400) != 0);
  return in_ST1;
}
#endif


/* ---- 0x004d56f0  FUN_004d56f0 ---- */
int FUN_004d56f0(void)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_104 (*(uint *)(_frame + (0x120 - 0x104)))
  
  iVar2 = 0;
  iVar1 = GetCurrentDirectoryA(0x104,(int)&local_104);
  if ((iVar1 != 0) && ((char)(local_104 >> 8) == ':')) {
    iVar2 = toupper(local_104 & 0xff);
    iVar2 = iVar2 + -0x40;
  }
  return iVar2;
}
#undef local_104


/* ---- 0x004d5740  FUN_004d5740 ---- */
undefined4 FUN_004d5740(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar3 = param_1;
  if ((0 < param_1) && (param_1 < 0x20)) {
    _lock(0xc);
    iVar1 = param_1;
    param_1 = CONCAT31(0x3a,(char)iVar3 + '@');
    uVar2 = param_1;
    PIECE(param_1,3,1) = SUB41(iVar1,3);
    PIECE(param_1,0,3) = (uint3)(ushort)uVar2;
    iVar3 = SetCurrentDirectoryA(&param_1);
    if (iVar3 != 0) {
      _unlock(0xc);
      return 0;
    }
    iVar3 = GetLastError();
    _dosmaperr(iVar3);
    _unlock(0xc);
    return 0xffffffff;
  }
  puVar4 = (undefined4 *)_errno();
  *puVar4 = 0xd;
  puVar4 = (undefined4 *)__doserrno();
  *puVar4 = 0xf;
  return 0xffffffff;
}

/* ---- 0x004d57c0  FUN_004d57c0 ---- */
undefined4 FUN_004d57c0(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = MoveFileA(param_1,param_2);
  if (iVar1 == 0) {
    iVar1 = GetLastError();
  }
  else {
    iVar1 = 0;
  }
  if (iVar1 != 0) {
    _dosmaperr(iVar1);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004d5800  FUN_004d5800 ---- */
undefined4 FUN_004d5800(int param_1)

{
  int iVar1;
  
  iVar1 = DeleteFileA(param_1);
  if (iVar1 == 0) {
    iVar1 = GetLastError();
  }
  else {
    iVar1 = 0;
  }
  if (iVar1 != 0) {
    _dosmaperr(iVar1);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004d5830  FUN_004d5830 ---- */
undefined4 FUN_004d5830(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  _lock(0xc);
  uVar1 = FUN_004d5860(0,param_1,param_2);
  _unlock(0xc);
  return uVar1;
}

/* ---- 0x004d5860  FUN_004d5860 ---- */
char * FUN_004d5860(int param_1,char *param_2,uint param_3)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  #define local_10c (*(char (*)[8])(_frame + (0x120 - 0x10c)))
  #define local_104 (*(char (*)[260])(_frame + (0x120 - 0x104)))
  
  if (param_1 == 0) {
    iVar2 = GetCurrentDirectoryA(0x104,(int)local_104);
  }
  else {
    iVar2 = FUN_004d5990(param_1);
    if (iVar2 == 0) {
      puVar3 = (undefined4 *)__doserrno();
      *puVar3 = 0xf;
      puVar3 = (undefined4 *)_errno();
      *puVar3 = 0xd;
      return (char *)0x0;
    }
    local_10c[0] = (char)param_1 + '@';
    local_10c[1] = 0x3a;
    local_10c[2] = 0x2e;
    local_10c[3] = 0;
    iVar2 = GetFullPathNameA(local_10c,0x104,local_104,local_10c + 4);
  }
  if ((iVar2 == 0) || (uVar4 = iVar2 + 1, 0x104 < uVar4)) {
    return (char *)0x0;
  }
  if (param_2 == (char *)0x0) {
    if ((int)uVar4 <= (int)param_3) {
      uVar4 = param_3;
    }
    param_2 = malloc(uVar4);
    if (param_2 == (char *)0x0) {
      puVar3 = (undefined4 *)_errno();
      *puVar3 = 0xc;
      return (char *)0x0;
    }
  }
  else if ((int)param_3 < (int)uVar4) {
    puVar3 = (undefined4 *)_errno();
    *puVar3 = 0x22;
    return (char *)0x0;
  }
  uVar4 = 0xffffffff;
  pcVar6 = local_104;
  do {
    pcVar7 = pcVar6;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar6 = pcVar7 + -uVar4;
  pcVar7 = param_2;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  return param_2;
}
#undef local_104
#undef local_10c


/* ---- 0x004d5990  FUN_004d5990 ---- */
undefined4 FUN_004d5990(uint param_1)

{
  char cVar1;
  int iVar2;
  
  if (param_1 == 0) {
    return 1;
  }
  cVar1 = (char)param_1;
  param_1 = (uint)CONCAT12(0x5c,CONCAT11(0x3a,cVar1 + '@'));
  iVar2 = GetDriveTypeA((int)&param_1);
  if ((iVar2 != 0) && (iVar2 != 1)) {
    return 1;
  }
  return 0;
}

/* ---- 0x004d5de0  FUN_004d5de0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined * FUN_004d5de0(int a1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined *puVar1;
  int unaff_ESI;
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define pcStack_10 (*(code **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_004dac00;
  pcStack_10 = FUN_004b1c48;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_14;
  local_8 = 0;
  puVar1 = FUN_004d5e35(unaff_ESI);
  return puVar1;
}
#undef local_14
#undef local_1c
#undef local_20
#undef local_8
#undef pcStack_10
#undef puStack_c

#endif


/* ---- 0x004d5e1c  FUN_004d5e1c ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int FUN_004d5e1c(void)

{
  int unaff_EBP;
  
  return *(int *)**(undefined4 **)(unaff_EBP + -0x14) == -0x3ffffffb;
}
#endif


/* ---- 0x004d5e30  FUN_004d5e30 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined4 FUN_004d5e30(void)

{
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return 0;
}
#endif


/* ---- 0x004d5e35  FUN_004d5e35 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
undefined * __stdcall FUN_004d5e35(int a1)

{
  undefined *in_EAX;
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return in_EAX;
}
#endif


/* ---- 0x004d5e50  FUN_004d5e50 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void FUN_004d5e50(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  ((code *)FUN_004d5fd0)(param_1,param_2,param_3);
  return;
}
#endif


/* ---- 0x004d5f70  FUN_004d5f70 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FUN_004d5f70(void)

{
  uint uVar1;
  
  ((code *)vsprintf)(&DAT_008dcdc8 + UINT_008ddd68 * 200);
  uVar1 = 0x13;
  if (UINT_008ddd68 == 0x13) {
    UINT_008ddd68 = 0;
  }
  else {
    UINT_008ddd68 = UINT_008ddd68 + 1;
  }
  if ((int)UINT_008ddd6c < 0x13) {
    uVar1 = UINT_008ddd6c + 1;
    UINT_008ddd6c = uVar1;
  }
  return uVar1;
}
#endif


/* ---- 0x004d5fd0  FUN_004d5fd0 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined8 __fastcall
FUN_004d5fd0(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined1 param_4,
            uint param_5)

{
  undefined4 in_EAX;
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = CONCAT31(CONCAT21(CONCAT11(param_4,param_4),param_4),param_4);
  if (19999 < (int)param_5) {
    do {
      for (iVar2 = 5000; iVar2 != 0; iVar2 = iVar2 + -1) {
        *param_3 = uVar1;
        param_3 = param_3 + 1;
      }
      param_5 = param_5 - 20000;
    } while (20000 < (int)param_5);
  }
  if ((param_5 & 3) != 0) {
    for (uVar3 = param_5 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined1 *)param_3 = param_4;
      param_3 = (undefined4 *)((int)param_3 + 1);
    }
  }
  for (param_5 = param_5 >> 2; param_5 != 0; param_5 = param_5 - 1) {
    *param_3 = uVar1;
    param_3 = param_3 + 1;
  }
  return CONCAT44(param_2,in_EAX);
}
#endif


/* ---- 0x004d6030  FUN_004d6030 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d6030(void)

{
  int unaff_EBP;
  
  Plat_Free(*(void **)(unaff_EBP + -0x10));
  return;
}
#endif


/* ---- 0x004d6046  FUN_004d6046 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d6046(void)

{
  ((code *)__CxxFrameHandler)();
  return;
}
#endif


/* ---- 0x004d6050  FUN_004d6050 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d6050(void)

{
  int unaff_EBP;
  
  Plat_Free(*(void **)(unaff_EBP + 8));
  return;
}
#endif


/* ---- 0x004d605b  FUN_004d605b ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d605b(void)

{
  ((code *)__CxxFrameHandler)();
  return;
}
#endif


/* ---- 0x004d6070  FUN_004d6070 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d6070(void)

{
  int unaff_EBP;
  
  Plat_Free(*(void **)(unaff_EBP + 4));
  return;
}
#endif


/* ---- 0x004d607b  FUN_004d607b ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d607b(void)

{
  ((code *)__CxxFrameHandler)();
  return;
}
#endif


/* ---- 0x004d6090  FUN_004d6090 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d6090(void)

{
  int unaff_EBP;
  
  Plat_Free(*(void **)(unaff_EBP + -0x1fc));
  return;
}
#endif


/* ---- 0x004d609e  FUN_004d609e ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d609e(void)

{
  int unaff_EBP;
  
  Plat_Free(*(void **)(unaff_EBP + -0x1fc));
  return;
}
#endif


/* ---- 0x004d60ac  FUN_004d60ac ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d60ac(void)

{
  int unaff_EBP;
  
  Plat_Free(*(void **)(unaff_EBP + -0x1fc));
  return;
}
#endif


/* ---- 0x004d60ba  FUN_004d60ba ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d60ba(void)

{
  ((code *)__CxxFrameHandler)();
  return;
}
#endif


/* ---- 0x004d60d0  FUN_004d60d0 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d60d0(void)

{
  int unaff_EBP;
  
  StateImage_Release(*(int *)(unaff_EBP + -0x10) + 0xc);
  return;
}
#endif


/* ---- 0x004d60db  FUN_004d60db ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d60db(void)

{
  int unaff_EBP;
  
  StateImage_Release(*(int *)(unaff_EBP + -0x10) + 0x80);
  return;
}
#endif


/* ---- 0x004d60e9  FUN_004d60e9 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d60e9(void)

{
  ((code *)__CxxFrameHandler)();
  return;
}
#endif


/* ---- 0x004d6100  FUN_004d6100 ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d6100(void)

{
  int unaff_EBP;
  
  StateImage_Release(*(int *)(unaff_EBP + -0x10) + 0xc);
  return;
}
#endif


/* ---- 0x004d610b  FUN_004d610b ---- */
/* NOT COMPILED: names/lib_replace.json (dead): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
void FUN_004d610b(void)

{
  ((code *)__CxxFrameHandler)();
  return;
}
#endif

