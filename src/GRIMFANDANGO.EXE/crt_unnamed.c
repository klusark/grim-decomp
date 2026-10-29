/* GRIMFANDANGO.EXE :: crt_unnamed.c
 * functions 0x004ac690 .. 0x004d610b (431 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004ac690  FUN_004ac690 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004ac690(void)

{
  FUN_004ac6b0();
  _DAT_008d0aa0 = FUN_004b05c0();
  FUN_004b0550();
  return;
}

/* ---- 0x004ac6b0  FUN_004ac6b0 ---- */
void FUN_004ac6b0(void)

{
  PTR_FUN_004ed30c = &LAB_004b0650;
  PTR_FUN_004ed308 = &LAB_004b0ab0;
  PTR_FUN_004ed310 = &LAB_004b06e0;
  PTR_FUN_004ed314 = FUN_004b05f0;
  PTR_FUN_004ed318 = &LAB_004b06c0;
  PTR_FUN_004ed31c = &LAB_004b0ab0;
  return;
}

/* ---- 0x004acb8d  FUN_004acb8d ---- */
void FUN_004acb8d(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  uVar1 = *(undefined4 *)**(undefined4 **)(unaff_EBP + -0x14);
  *(undefined4 *)(unaff_EBP + -0x68) = uVar1;
  FUN_004b0d30(uVar1,*(undefined4 **)(unaff_EBP + -0x14));
  return;
}

/* ---- 0x004acba2  FUN_004acba2 ---- */
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

/* ---- 0x004acc10  FUN_004acc10 ---- */
void FUN_004acc10(undefined4 param_1)

{
  if (DAT_008d0aac == 1) {
    _FF_MSGBANNER();
  }
  _NMSG_WRITE(param_1);
  ExitProcess(0xff);
  return;
}

/* ---- 0x004acd10  FUN_004acd10 ---- */
void FUN_004acd10(void)

{
  if (PTR_FUN_004ed098 != (undefined *)0x0) {
    (*(code *)PTR_FUN_004ed098)();
  }
  _initterm(&DAT_004dd00c,&DAT_004dd020);
  _initterm(&DAT_004dd000,&DAT_004dd008);
  return;
}

/* ---- 0x004acf30  FUN_004acf30 ---- */
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

/* ---- 0x004ad2b0  FUN_004ad2b0 ---- */
void FUN_004ad2b0(void)

{
  time(&DAT_008d0af8);
  return;
}

/* ---- 0x004addf0  FUN_004addf0 ---- */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_004addf0(void)

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

/* ---- 0x004adef0  FUN_004adef0 ---- */
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

/* ---- 0x004ae410  FUN_004ae410 ---- */
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

/* ---- 0x004ae735  FUN_004ae735 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined4 FUN_004ae735(void)

{
  undefined4 in_EAX;
  undefined2 uVar1;
  float10 in_ST0;
  float10 fVar2;
  float10 fVar3;
  
  fVar2 = ROUND(in_ST0);
  uVar1 = (undefined2)((uint)in_EAX >> 0x10);
  if ((fVar2 == in_ST0) != 0) {
    fVar2 = in_ST0 * (float10)_DAT_004ed0c0;
    fVar3 = ROUND(fVar2);
    return CONCAT22(uVar1,(ushort)(fVar3 < fVar2) << 8 | (ushort)(ISNAN(fVar3) || ISNAN(fVar2)) << 10 |
                          (ushort)(fVar3 == fVar2) << 0xe);
  }
  return CONCAT22(uVar1,(ushort)(fVar2 < in_ST0) << 8 | (ushort)(ISNAN(fVar2) || ISNAN(in_ST0)) << 10 |
                        (ushort)(fVar2 == in_ST0) << 0xe);
}

/* ---- 0x004aeb60  FUN_004aeb60 ---- */
void FUN_004aeb60(void)

{
  _flushall(1);
  return;
}

/* ---- 0x004af340  FUN_004af340 ---- */
void FUN_004af340(undefined4 param_1,code *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x004af345. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

/* ---- 0x004af3f0  FUN_004af3f0 ---- */
undefined4 FUN_004af3f0(int param_1,undefined4 param_2,int param_3,int param_4,int param_5)

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
  local_14 = FUN_004af450;
  local_10 = param_2;
  local_c = param_1;
  local_18 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&local_18;
  uVar1 = FUN_004b5c10(param_3,param_1,param_5);
  *unaff_FS_OFFSET = local_18;
  return uVar1;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_8
#undef local_c


/* ---- 0x004af450  FUN_004af450 ---- */
void FUN_004af450(undefined4 param_1,int param_2,undefined4 param_3)

{
  __InternalCxxFrameHandler
            (param_1,*(undefined4 *)(param_2 + 0xc),param_3,0,*(undefined4 *)(param_2 + 8),
             *(undefined4 *)(param_2 + 0x10),param_2,0);
  return;
}

/* ---- 0x004af480  FUN_004af480 ---- */
undefined4
FUN_004af480(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *unaff_FS_OFFSET = (int *)TEB_BASE();
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
  
  local_c = &STACK0X(0xfffffffc);
  local_10 = &STACK0X(0xffffffbc);
  local_28 = FUN_004af550;
  local_24 = param_5;
  local_20 = param_2;
  local_1c = param_6;
  local_18 = param_7;
  local_8 = 0;
  local_14 = 0x4af51c;
  local_2c = (undefined4 *)*unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&local_2c;
  local_34 = param_1;
  local_30 = param_3;
  iVar1 = ((code *)_getptd)(*param_1,&local_34);
  (**(code **)(iVar1 + 0x68))();
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


/* ---- 0x004af550  FUN_004af550 ---- */
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

/* ---- 0x004af5e0  FUN_004af5e0 ---- */
int FUN_004af5e0(int param_1,int param_2,int param_3,uint *param_4,uint *param_5)

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

/* ---- 0x004af72d  FUN_004af72d ---- */
void __fastcall FUN_004af72d(undefined4 param_1)

{
  undefined4 in_EAX;
  undefined4 unaff_EBP;
  
  DAT_004ed0d8 = param_1;
  DAT_004ed0d4 = in_EAX;
  DAT_004ed0dc = unaff_EBP;
  return;
}

/* ---- 0x004af7b0  FUN_004af7b0 ---- */
void FUN_004af7b0(void)

{
  InitializeCriticalSection((int)PTR_DAT_004ed124);
  InitializeCriticalSection((int)PTR_DAT_004ed114);
  InitializeCriticalSection((int)PTR_DAT_004ed104);
  InitializeCriticalSection((int)PTR_DAT_004ed0e4);
  return;
}

/* ---- 0x004b0550  FUN_004b0550 ---- */
void FUN_004b0550(void)

{
  FUN_004b6f90(0x10000,0x30000);
  return;
}

/* ---- 0x004b0570  FUN_004b0570 ---- */
/* WARNING: Removing unreachable block (ram,0x004b05b1) */

undefined4 FUN_004b0570(void)

{
  return 0;
}

/* ---- 0x004b05c0  FUN_004b05c0 ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined4 FUN_004b05c0(void)

{
  int a1;
  code *pcVar1;
  undefined4 uVar2;
  
  a1 = GetModuleHandleA(IMG_ADDR(0x004d8a84));
  if (a1 != 0) {
    pcVar1 = (code *)GetProcAddress(a1,IMG_ADDR(0x004d8a68));
    if (pcVar1 != (code *)0x0) {
      uVar2 = (*pcVar1)(0);
      return uVar2;
    }
  }
  uVar2 = FUN_004b0570();
  return uVar2;
}

/* ---- 0x004b05f0  FUN_004b05f0 ---- */
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
      if (DAT_004ed52c < 2) {
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

/* ---- 0x004b0740  FUN_004b0740 ---- */
int FUN_004b0740(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_28 (*(int (*)[4])(_frame + (0x40 - 0x28)))
  #define local_18 (*(undefined1 (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_004b76a0(*param_1,param_1[1],local_28,local_18);
  FUN_004b7600((uint)(local_28[0] == 0x2d) + param_2 + (uint)(0 < param_3),param_3 + 1,local_28);
  FUN_004b07c0(param_2,param_3,param_4,local_28,0);
  return param_2;
}
#undef local_18
#undef local_28


/* ---- 0x004b07c0  FUN_004b07c0 ---- */
undefined1 * FUN_004b07c0(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
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

/* ---- 0x004b08c0  FUN_004b08c0 ---- */
int FUN_004b08c0(undefined4 *param_1,int param_2,int param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define local_18 (*(undefined1 (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_004b76a0(*param_1,param_1[1],&local_28,local_18);
  FUN_004b7600((uint)(local_28 == 0x2d) + param_2,local_24 + param_3,&local_28);
  FUN_004b0930(param_2,param_3,&local_28,0);
  return param_2;
}
#undef local_18
#undef local_24
#undef local_28


/* ---- 0x004b0930  FUN_004b0930 ---- */
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

/* ---- 0x004b09f0  FUN_004b09f0 ---- */
void FUN_004b09f0(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  char cVar2;
  char *pcVar3;
  #define local_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define local_18 (*(undefined1 (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_004b76a0(*param_1,param_1[1],&local_28,local_18);
  iVar1 = local_24 + -1;
  pcVar3 = (char *)((uint)(local_28 == 0x2d) + param_2);
  FUN_004b7600(pcVar3,param_3,&local_28);
  local_24 = local_24 + -1;
  if ((-5 < local_24) && (local_24 < param_3)) {
    if (iVar1 < local_24) {
      cVar2 = *pcVar3;
      while (cVar2 != '\0') {
        cVar2 = pcVar3[1];
        pcVar3 = pcVar3 + 1;
      }
      pcVar3[-1] = '\0';
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


/* ---- 0x004b0b20  FUN_004b0b20 ---- */
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
    memcpy(param_1 + param_2,param_1,~uVar2);
  }
  return;
}

/* ---- 0x004b0c30  FUN_004b0c30 ---- */
undefined4 FUN_004b0c30(void)

{
  int *a2;
  int iVar1;
  
  FUN_004af7b0();
  DAT_004ed540 = TlsAlloc();
  if (DAT_004ed540 != -1) {
    a2 = (int *)calloc(1,0x74);
    if (a2 != (int *)0x0) {
      iVar1 = TlsSetValue(DAT_004ed540,(int)a2);
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

/* ---- 0x004b0d30  FUN_004b0d30 ---- */
undefined4 FUN_004b0d30(undefined4 param_1,undefined4 param_2)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  
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
  if (DAT_004ed5c0 < DAT_004ed5c4 + DAT_004ed5c0) {
    iVar7 = DAT_004ed5c0 * 0xc;
    iVar6 = DAT_004ed5c0;
    do {
      iVar6 = iVar6 + 1;
      *(undefined4 *)(*(int *)(iVar3 + 0x50) + 8 + iVar7) = 0;
      iVar7 = iVar7 + 0xc;
    } while (iVar6 < DAT_004ed5c4 + DAT_004ed5c0);
  }
  iVar6 = *piVar4;
  uVar2 = *(undefined4 *)(iVar3 + 0x58);
  if (iVar6 == -0x3fffff72) {
    *(undefined4 *)(iVar3 + 0x58) = 0x83;
    (*pcVar1)(8,*(undefined4 *)(iVar3 + 0x58));
    *(undefined4 *)(iVar3 + 0x58) = uVar2;
    *(undefined4 *)(iVar3 + 0x54) = uVar5;
    return 0xffffffff;
  }
  if (iVar6 == -0x3fffff70) {
    *(undefined4 *)(iVar3 + 0x58) = 0x81;
    (*pcVar1)(8,*(undefined4 *)(iVar3 + 0x58));
    *(undefined4 *)(iVar3 + 0x58) = uVar2;
    *(undefined4 *)(iVar3 + 0x54) = uVar5;
    return 0xffffffff;
  }
  if (iVar6 != -0x3fffff6f) {
    if (iVar6 == -0x3fffff6d) {
      *(undefined4 *)(iVar3 + 0x58) = 0x85;
      (*pcVar1)(8,*(undefined4 *)(iVar3 + 0x58));
      *(undefined4 *)(iVar3 + 0x58) = uVar2;
      *(undefined4 *)(iVar3 + 0x54) = uVar5;
      return 0xffffffff;
    }
    if (iVar6 != -0x3fffff73) {
      if (iVar6 != -0x3fffff71) {
        if (iVar6 == -0x3fffff6e) {
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

/* ---- 0x004b0f40  FUN_004b0f40 ---- */
int * FUN_004b0f40(int param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = param_2;
  if (*param_2 != param_1) {
    do {
      piVar1 = piVar1 + 3;
      if (param_2 + DAT_004ed5cc * 3 <= piVar1) break;
    } while (*piVar1 != param_1);
  }
  if ((param_2 + DAT_004ed5cc * 3 <= piVar1) || (*piVar1 != param_1)) {
    piVar1 = (int *)0x0;
  }
  return piVar1;
}

/* ---- 0x004b0f80  FUN_004b0f80 ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined4 FUN_004b0f80(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_004b0fa0(param_1,0,4);
  return uVar1;
}

/* ---- 0x004b0fa0  FUN_004b0fa0 ---- */
undefined4 FUN_004b0fa0(uint param_1,uint param_2,byte param_3)

{
  if ((*(byte *)((int)&DAT_008d0ca0 + (param_1 & 0xff) + 1) & param_3) == 0) {
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

/* ---- 0x004b0fe0  FUN_004b0fe0 ---- */
void FUN_004b0fe0(void)

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
  cVar2 = *DAT_008d0aa4;
  pcVar7 = DAT_008d0aa4;
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
  DAT_008d0ad0 = piVar3;
  if (piVar3 == (int *)0x0) {
    _amsg_exit(9);
  }
  cVar2 = *DAT_008d0aa4;
  local_4 = piVar3;
  pcVar7 = DAT_008d0aa4;
  do {
    if (cVar2 == '\0') {
      free(DAT_008d0aa4);
      DAT_008d0aa4 = (char *)0x0;
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


/* ---- 0x004b10d0  FUN_004b10d0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004b10d0(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  char *pcVar2;
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  GetModuleFileNameA(0,IMG_ADDR(0x008d0b90),0x104);
  _DAT_008d0ae0 = &DAT_008d0b90;
  pcVar2 = DAT_00906c18;
  if (*DAT_00906c18 == '\0') {
    pcVar2 = &DAT_008d0b90;
  }
  FUN_004b1170(pcVar2,0,0,&iStack_8,&iStack_4);
  iVar1 = malloc(iStack_4 + iStack_8 * 4);
  if (iVar1 == 0) {
    _amsg_exit(8);
  }
  FUN_004b1170(pcVar2,iVar1,iVar1 + iStack_8 * 4,&iStack_8,&iStack_4);
  _DAT_008d0ac8 = iVar1;
  _DAT_008d0ac4 = iStack_8 + -1;
  return;
}
#undef iStack_4
#undef iStack_8


/* ---- 0x004b1170  FUN_004b1170 ---- */
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
      if (((*(byte *)((int)&DAT_008d0ca0 + bVar2 + 1) & 4) != 0) &&
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
      if ((*(byte *)((int)&DAT_008d0ca0 + (int)param_5 + 1U) & 4) != 0) {
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
          if ((*(byte *)((int)&DAT_008d0ca0 + bVar2 + 1) & 4) != 0) {
            pbVar7 = pbVar7 + 1;
            *piVar6 = *piVar6 + 1;
          }
          *piVar6 = *piVar6 + 1;
          goto LAB_004b1345;
        }
        if ((*(byte *)((int)&DAT_008d0ca0 + bVar2 + 1) & 4) != 0) {
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

/* ---- 0x004b1380  FUN_004b1380 ---- */
char * FUN_004b1380(void)

{
  char cVar1;
  short sVar2;
  short *psVar3;
  int iVar5;
  int a6;
  char *pcVar6;
  char *pcVar7;
  uint uVar8;
  char *pcVar9;
  short *a3;
  char *pcVar10;
  char *pcVar11;
  short *psVar4;
  
  a3 = (short *)0x0;
  pcVar9 = (char *)0x0;
  if (DAT_008d0c98 == 0) {
    a3 = (short *)GetEnvironmentStringsW();
    if (a3 == (short *)0x0) {
      pcVar9 = (char *)GetEnvironmentStrings();
      if (pcVar9 == (char *)0x0) {
        return (char *)0x0;
      }
      DAT_008d0c98 = 2;
    }
    else {
      DAT_008d0c98 = 1;
    }
  }
  if (DAT_008d0c98 == 1) {
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
      a6 = WideCharToMultiByte(0,0,(int)a3,iVar5,0,0,0,0);
      if ((a6 != 0) && (pcVar9 = (char *)malloc(a6), pcVar9 != (char *)0x0)) {
        iVar5 = WideCharToMultiByte(0,0,(int)a3,iVar5,(int)pcVar9,a6,0,0);
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
  else if ((DAT_008d0c98 == 2) &&
          ((pcVar9 != (char *)0x0 ||
           (pcVar9 = (char *)GetEnvironmentStrings(), pcVar9 != (char *)0x0)))) {
    cVar1 = *pcVar9;
    pcVar6 = pcVar9;
    while (cVar1 != '\0') {
      do {
        pcVar7 = pcVar6;
        pcVar6 = pcVar7 + 1;
      } while (pcVar7[1] != '\0');
      pcVar6 = pcVar7 + 2;
      cVar1 = pcVar7[2];
    }
    pcVar6 = pcVar6 + (1 - (int)pcVar9);
    pcVar7 = (char *)malloc(pcVar6);
    if (pcVar7 != (char *)0x0) {
      pcVar10 = pcVar9;
      pcVar11 = pcVar7;
      for (uVar8 = (uint)pcVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar8 = (uint)pcVar6 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar11 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar11 = pcVar11 + 1;
      }
      FreeEnvironmentStringsA((int)pcVar9);
      return pcVar7;
    }
    FreeEnvironmentStringsA((int)pcVar9);
    return (char *)0x0;
  }
  return (char *)0x0;
}

/* ---- 0x004b14e0  FUN_004b14e0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004b14e0(undefined4 param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  int a1;
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
  
  _lock(0x19);
  a1 = FUN_004b1710(param_1);
  if (a1 == DAT_008d0ea8) {
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
  piVar4 = &DAT_004ed5d8;
  do {
    if (*piVar4 == a1) {
      puVar11 = &DAT_008d0ca0;
      for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar11 = 0;
        puVar11 = puVar11 + 1;
      }
      *(undefined1 *)puVar11 = 0;
      uVar5 = 0;
      iVar8 = iVar8 * 0x30;
      pbVar9 = (byte *)(iVar8 + 0x4ed5e8);
      do {
        bVar2 = *pbVar9;
        for (pbVar10 = pbVar9; (bVar2 != 0 && (bVar2 = pbVar10[1], bVar2 != 0));
            pbVar10 = pbVar10 + 2) {
          uVar6 = (uint)*pbVar10;
          if (uVar6 <= bVar2) {
            bVar3 = (&DAT_004ed5d0)[uVar5];
            do {
              pbVar1 = (byte *)((int)&DAT_008d0ca0 + uVar6 + 1);
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
      DAT_008d0ea8 = a1;
      DAT_008d0eac = FUN_004b1760(a1);
      _DAT_008d0eb0 = *(undefined4 *)(iVar8 + IMG_ADDR(0x004ed5dc));
      _DAT_008d0eb4 = *(undefined4 *)(iVar8 + IMG_ADDR(0x004ed5e0));
      _DAT_008d0eb8 = *(undefined4 *)(iVar8 + IMG_ADDR(0x004ed5e4));
      goto LAB_004b1632;
    }
    piVar4 = piVar4 + 0xc;
    iVar8 = iVar8 + 1;
  } while (piVar4 < &DAT_004ed6c8);
  iVar8 = GetCPInfo(a1,(int)&local_14);
  if (iVar8 == 1) {
    puVar11 = &DAT_008d0ca0;
    for (iVar8 = 0x40; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar11 = 0;
      puVar11 = puVar11 + 1;
    }
    *(undefined1 *)puVar11 = 0;
    DAT_008d0eac = 0;
    if (local_14 < 2) {
      _DAT_00906c04 = 0;
      DAT_008d0ea8 = a1;
    }
    else {
      DAT_008d0ea8 = a1;
      if (abStack_e[0] != 0) {
        pbVar9 = abStack_e + 1;
        do {
          bVar2 = *pbVar9;
          if (bVar2 == 0) break;
          for (uVar5 = (uint)pbVar9[-1]; uVar5 <= bVar2; uVar5 = uVar5 + 1) {
            *(byte *)((int)&DAT_008d0ca0 + uVar5 + 1) =
                 *(byte *)((int)&DAT_008d0ca0 + uVar5 + 1) | 4;
          }
          pbVar10 = pbVar9 + 1;
          pbVar9 = pbVar9 + 2;
        } while (*pbVar10 != 0);
      }
      uVar5 = 1;
      do {
        *(byte *)((int)&DAT_008d0ca0 + uVar5 + 1) = *(byte *)((int)&DAT_008d0ca0 + uVar5 + 1) | 8;
        uVar5 = uVar5 + 1;
      } while (uVar5 < 0xff);
      DAT_008d0eac = FUN_004b1760(a1);
      _DAT_00906c04 = 1;
    }
    _DAT_008d0eb0 = 0;
    _DAT_008d0eb4 = 0;
    _DAT_008d0eb8 = 0;
  }
  else {
    if (DAT_008d0ebc == 0) {
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


/* ---- 0x004b1710  FUN_004b1710 ---- */
int FUN_004b1710(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    DAT_008d0ebc = 1;
                    /* WARNING: Could not recover jumptable at 0x004b172d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_008d0ebc = 1;
                    /* WARNING: Could not recover jumptable at 0x004b1742. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_008d0b80;
  }
  DAT_008d0ebc = (uint)bVar2;
  return param_1;
}

/* ---- 0x004b1760  FUN_004b1760 ---- */
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

/* ---- 0x004b17c0  FUN_004b17c0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004b17c0(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_008d0ca0;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_008d0ea8 = 0;
  _DAT_00906c04 = 0;
  DAT_008d0eac = 0;
  _DAT_008d0eb0 = 0;
  _DAT_008d0eb4 = 0;
  _DAT_008d0eb8 = 0;
  return;
}

/* ---- 0x004b1800  FUN_004b1800 ---- */
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
  
  iVar1 = GetCPInfo(DAT_008d0ea8,(int)local_514);
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
    __crtGetStringTypeA(1,auStack_500,0x100,auStack_200,DAT_008d0ea8,DAT_008d0eac,0);
    __crtLCMapStringA(DAT_008d0eac,0x100,auStack_500,0x100,auStack_400,0x100,DAT_008d0ea8,0);
    __crtLCMapStringA(DAT_008d0eac,0x200,auStack_500,0x100,auStack_300,0x100,DAT_008d0ea8,0);
    uVar2 = 0;
    puVar6 = auStack_200;
    do {
      if ((*puVar6 & 1) == 0) {
        if ((*puVar6 & 2) == 0) {
          (&DAT_008d0da8)[uVar2] = 0;
        }
        else {
          *(byte *)((int)&DAT_008d0ca0 + uVar2 + 1) =
               *(byte *)((int)&DAT_008d0ca0 + uVar2 + 1) | 0x20;
          (&DAT_008d0da8)[uVar2] = auStack_300[uVar2];
        }
      }
      else {
        *(byte *)((int)&DAT_008d0ca0 + uVar2 + 1) = *(byte *)((int)&DAT_008d0ca0 + uVar2 + 1) | 0x10
        ;
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
        *(byte *)((int)&DAT_008d0ca0 + uVar2 + 1) = *(byte *)((int)&DAT_008d0ca0 + uVar2 + 1) | 0x20
        ;
        (&DAT_008d0da8)[uVar2] = (char)uVar2 + -0x20;
      }
    }
    else {
      *(byte *)((int)&DAT_008d0ca0 + uVar2 + 1) = *(byte *)((int)&DAT_008d0ca0 + uVar2 + 1) | 0x10;
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


/* ---- 0x004b19e0  FUN_004b19e0 ---- */
void FUN_004b19e0(void)

{
  FUN_004b14e0(0xfffffffd);
  return;
}

/* ---- 0x004b19f0  FUN_004b19f0 ---- */
void FUN_004b19f0(void)

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
  DAT_00906c00 = 0x20;
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
  if ((local_12 != 0) && (local_10 != (int *)0x0)) {
    local_48 = *local_10;
    pbVar8 = (byte *)(local_10 + 1);
    pbVar6 = pbVar8 + local_48;
    if (0x7ff < local_48) {
      local_48 = 0x800;
    }
    if (DAT_00906c00 < local_48) {
      piVar2 = &DAT_00906b04;
      do {
        puVar3 = (undefined4 *)malloc(0x480);
        if (puVar3 == (undefined4 *)0x0) {
          local_48 = DAT_00906c00;
          break;
        }
        *piVar2 = (int)puVar3;
        DAT_00906c00 = DAT_00906c00 + 0x20;
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
      } while (DAT_00906c00 < local_48);
    }
    uVar7 = 0;
    if (0 < local_48) {
      do {
        if (((*(int *)pbVar6 != -1) && ((*pbVar8 & 1) != 0)) &&
           (((*pbVar8 & 8) != 0 || (iVar4 = GetFileType(*(int *)pbVar6), iVar4 != 0)))) {
          piVar2 = (&PTR_00906b00)[(int)uVar7 >> 5];
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
      if ((iVar5 == -1) || (uVar7 = GetFileType(iVar5), uVar7 == 0)) {
        bVar1 = *(byte *)(piVar2 + 1) | 0x40;
        goto LAB_004b1bde;
      }
      *piVar2 = iVar5;
      if ((uVar7 & 0xff) == 2) {
        bVar1 = *(byte *)(piVar2 + 1) | 0x40;
        goto LAB_004b1bde;
      }
      if ((uVar7 & 0xff) == 3) {
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
      SetHandleCount(DAT_00906c00);
      return;
    }
  } while( true );
}
#undef local_10
#undef local_12
#undef local_44
#undef local_48


/* ---- 0x004b1c00  FUN_004b1c00 ---- */
undefined4 FUN_004b1c00(void)

{
  int iVar1;
  
  DAT_00906ae4 = HeapCreate(0,0x1000,0);
  if (DAT_00906ae4 == 0) {
    return 0;
  }
  iVar1 = __sbh_alloc_new_region();
  if (iVar1 == 0) {
    HeapDestroy(DAT_00906ae4);
    return 0;
  }
  return 1;
}

/* ---- 0x004b2040  FUN_004b2040 ---- */
void FUN_004b2040(void)

{
  undefined **ppuVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (DAT_00906ae0 == 0) {
    DAT_00906ae0 = 0x200;
  }
  else if (DAT_00906ae0 < 0x14) {
    DAT_00906ae0 = 0x14;
  }
  DAT_00905ac4 = calloc(DAT_00906ae0,4);
  if (DAT_00905ac4 == 0) {
    DAT_00906ae0 = 0x14;
    DAT_00905ac4 = calloc(0x14,4);
    if (DAT_00905ac4 == 0) {
      _amsg_exit(0x1a);
    }
  }
  iVar3 = 0;
  ppuVar1 = &PTR_DAT_004ed780;
  do {
    *(undefined ***)(DAT_00905ac4 + iVar3) = ppuVar1;
    ppuVar1 = ppuVar1 + 8;
    iVar3 = iVar3 + 4;
  } while ((int)ppuVar1 < IMG_ADDR(0x004eda00));
  uVar2 = 0;
  puVar4 = &DAT_004ed790;
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

/* ---- 0x004b2100  FUN_004b2100 ---- */
void FUN_004b2100(void)

{
  FUN_004aeb60();
  if (DAT_008d0ae8 != '\0') {
    FUN_004b7c10();
    return;
  }
  return;
}

/* ---- 0x004b4440  FUN_004b4440 ---- */
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


/* ---- 0x004b4ad4  FUN_004b4ad4 ---- */
float10 FUN_004b4ad4(void)

{
  return (float10)0;
}

/* ---- 0x004b4b0d  FUN_004b4b0d ---- */
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

/* ---- 0x004b4b0f  FUN_004b4b0f ---- */
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

/* ---- 0x004b4c00  FUN_004b4c00 ---- */
unkbyte10 FUN_004b4c00(void)

{
  float10 in_ST0;
  float10 fVar1;
  unkbyte10 Var2;
  
  fVar1 = (float10)f2xm1(-(ROUND(in_ST0) - in_ST0));
  Var2 = fscale((float10)1 + fVar1,ROUND(in_ST0));
  return Var2;
}

/* ---- 0x004b4c15  FUN_004b4c15 ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined4 FUN_004b4c15(void)

{
  undefined4 in_EAX;
  
  return in_EAX;
}

/* ---- 0x004b4c45  FUN_004b4c45 ---- */
uint __fastcall FUN_004b4c45(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_2 + 4) & 0x7ff00000;
  if (uVar1 != 0x7ff00000) {
    return uVar1;
  }
  return *(uint *)(param_2 + 4);
}

/* ---- 0x004b4c9e  FUN_004b4c9e ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined4 FUN_004b4c9e(void)

{
  undefined4 in_EAX;
  
  return in_EAX;
}

/* ---- 0x004b4ce9  FUN_004b4ce9 ---- */
undefined4 __fastcall FUN_004b4ce9(undefined4 param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  undefined4 uVar2;
  ushort in_FPUStatusWord;
  float10 in_ST0;
  ushort unaff_retaddr;
  #define uStack_4 (*(uint *)(_frame + (0x20 - 0x4)))
  undefined2 uVar3;
  
  uStack_4 = (uint)((ulonglong)(double)in_ST0 >> 0x20);
  if (((ulonglong)(double)in_ST0 & 0x7ff0000000000000) == 0) {
    fscale(in_ST0,(float10)1536.0);
  }
  else if ((uStack_4 & 0x7ff00000) == 0x7ff00000) {
    fscale(in_ST0,(float10)-1536.0);
  }
  else {
    uVar3 = (undefined2)((uStack_4 & 0x7ff00000) >> 0x10);
    uVar1 = CONCAT22(uVar3,unaff_retaddr);
    if (((unaff_retaddr == 0x27f) ||
        (uVar1 = CONCAT22(uVar3,unaff_retaddr) & 0xffff0020, (unaff_retaddr & 0x20) != 0)) ||
       (uVar1 = CONCAT22((short)(uVar1 >> 0x10),in_FPUStatusWord) & 0xffff0020,
       (in_FPUStatusWord & 0x20) == 0)) {
      return uVar1;
    }
  }
  if (param_2 == 0x1d) {
    uVar2 = ((code *)_pow_except1)();
    return uVar2;
  }
  uVar2 = ((code *)_pow_except2)();
  return uVar2;
}
#undef uStack_4


/* ---- 0x004b56c6  FUN_004b56c6 ---- */
void FUN_004b56c6(void)

{
  int unaff_EBP;
  
  FUN_004b5710(*(undefined4 *)(unaff_EBP + -0x14));
  return;
}

/* ---- 0x004b56d3  FUN_004b56d3 ---- */
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

/* ---- 0x004b5710  FUN_004b5710 ---- */
undefined4 FUN_004b5710(undefined4 *param_1)

{
  if (*(int *)*param_1 == -0x1f928c9d) {
    terminate();
  }
  return 0;
}

/* ---- 0x004b5884  FUN_004b5884 ---- */
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

/* ---- 0x004b58af  FUN_004b58af ---- */
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

/* ---- 0x004b5b60  FUN_004b5b60 ---- */
void FUN_004b5b60(int param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_004d8e28;
  puStack_10 = &LAB_004b1c48;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  if ((param_1 != 0) && (iVar1 = *(int *)(*(int *)(param_1 + 0x1c) + 4), iVar1 != 0)) {
    local_8 = 0;
    FUN_004af340(*(undefined4 *)(param_1 + 0x18),iVar1);
  }
  *unaff_FS_OFFSET = local_14;
  return;
}
#undef local_14
#undef local_8
#undef puStack_10
#undef puStack_c


/* ---- 0x004b5baa  FUN_004b5baa ---- */
bool FUN_004b5baa(void)

{
  int unaff_EBP;
  
  return *(char *)(unaff_EBP + 0xc) != '\0';
}

/* ---- 0x004b5bb5  FUN_004b5bb5 ---- */
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

/* ---- 0x004b5be0  FUN_004b5be0 ---- */
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

/* ---- 0x004b5c10  FUN_004b5c10 ---- */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4 __stdcall FUN_004b5c10(int a1,int a2,int a3)

{
  code *pcVar1;
  undefined4 uVar2;
  
  pcVar1 = (code *)((code *)FUN_004af72d)(a3);
  (*pcVar1)();
  if (a3 == 0x100) {
    a3 = 2;
  }
  uVar2 = ((code *)FUN_004af72d)(a3);
  return uVar2;
}

/* ---- 0x004b5caa  FUN_004b5caa ---- */
undefined4 FUN_004b5caa(void)

{
  return 1;
}

/* ---- 0x004b5cb0  FUN_004b5cb0 ---- */
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

/* ---- 0x004b5cd7  FUN_004b5cd7 ---- */
void FUN_004b5cd7(void)

{
  abort();
  return;
}

/* ---- 0x004b5cf0  FUN_004b5cf0 ---- */
void FUN_004b5cf0(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_004d8e50;
  puStack_10 = &LAB_004b1c48;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
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
#undef local_8
#undef puStack_10
#undef puStack_c


/* ---- 0x004b5d5e  FUN_004b5d5e ---- */
void FUN_004b5d5e(void)

{
  terminate();
  return;
}

/* ---- 0x004b5d80  FUN_004b5d80 ---- */
undefined4 FUN_004b5d80(void)

{
  undefined *puVar1;
  int iVar2;
  
  if (DAT_008d0b7c == 0) {
    PTR_PTR_004f0764 = (undefined *)&PTR_DAT_004f06b8;
    FUN_004b61b0(DAT_008d0ee8);
    free(DAT_008d0ee8);
    DAT_008d0ee8 = (undefined *)0x0;
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
  FUN_004b61b0(DAT_008d0ee8);
  free(DAT_008d0ee8);
  DAT_008d0ee8 = puVar1;
  return 0;
}

/* ---- 0x004b5e30  FUN_004b5e30 ---- */
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

/* ---- 0x004b61b0  FUN_004b61b0 ---- */
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

/* ---- 0x004b63f0  FUN_004b63f0 ---- */
uint FUN_004b63f0(char *param_1,int param_2)

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
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
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
  puVar6 = (undefined1 *)malloc(0xd);
  *(undefined1 **)(param_2 + 0xa8) = puVar6;
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


/* ---- 0x004b64f0  FUN_004b64f0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004b64f0(void)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  uVar1 = DAT_008d0f22;
  if (DAT_008d0b78 == 0) {
    free(DAT_008d0eec);
    free(DAT_008d0ef0);
    free(DAT_008d0ef4);
    DAT_008d0eec = 0;
    DAT_008d0ef0 = 0;
    DAT_008d0ef4 = 0;
    uVar5 = malloc(2);
    *(undefined4 *)PTR_PTR_004f07a0 = uVar5;
    if (*(undefined2 **)PTR_PTR_004f07a0 == (undefined2 *)0x0) {
      return 0xffffffff;
    }
    **(undefined2 **)PTR_PTR_004f07a0 = DAT_004e793c;
    uVar5 = malloc(2);
    *(undefined4 *)(PTR_PTR_004f07a0 + 4) = uVar5;
    if (*(undefined1 **)(PTR_PTR_004f07a0 + 4) == (undefined1 *)0x0) {
      return 0xffffffff;
    }
    **(undefined1 **)(PTR_PTR_004f07a0 + 4) = 0;
    uVar5 = malloc(2);
    *(undefined4 *)(PTR_PTR_004f07a0 + 8) = uVar5;
    if (*(undefined1 **)(PTR_PTR_004f07a0 + 8) == (undefined1 *)0x0) {
      return 0xffffffff;
    }
    **(undefined1 **)(PTR_PTR_004f07a0 + 8) = 0;
  }
  else {
    iVar2 = FUN_004ba340(1,DAT_008d0f22,0xe,&DAT_008d0eec);
    iVar3 = FUN_004ba340(1,uVar1,0xf,&DAT_008d0ef0);
    iVar4 = FUN_004ba340(1,uVar1,0x10,&DAT_008d0ef4);
    FUN_004b66f0(DAT_008d0ef4);
    if ((iVar2 != 0 || iVar3 != 0) || iVar4 != 0) {
      free(DAT_008d0eec);
      free(DAT_008d0ef0);
      free(DAT_008d0ef4);
      DAT_008d0eec = 0;
      DAT_008d0ef0 = 0;
      DAT_008d0ef4 = 0;
      return 0xffffffff;
    }
    if (*(undefined **)PTR_PTR_004f07a0 != &DAT_004f0768) {
      free(*(undefined **)PTR_PTR_004f07a0);
      free(*(undefined4 *)(PTR_PTR_004f07a0 + 4));
      free(*(undefined4 *)(PTR_PTR_004f07a0 + 8));
    }
    *(undefined4 *)PTR_PTR_004f07a0 = DAT_008d0eec;
    *(undefined4 *)(PTR_PTR_004f07a0 + 4) = DAT_008d0ef0;
    *(undefined4 *)(PTR_PTR_004f07a0 + 8) = DAT_008d0ef4;
  }
  _DAT_004ed534 = 1;
  DAT_004ed530 = **(undefined1 **)PTR_PTR_004f07a0;
  return 0;
}

/* ---- 0x004b66f0  FUN_004b66f0 ---- */
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

/* ---- 0x004b6730  FUN_004b6730 ---- */
undefined4 FUN_004b6730(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (DAT_008d0b74 == 0) {
    PTR_DAT_004f0770 = *(undefined **)PTR_PTR_004f07a0;
    PTR_DAT_004f0774 = *(undefined **)(PTR_PTR_004f07a0 + 4);
    PTR_DAT_004f0778 = *(undefined **)(PTR_PTR_004f07a0 + 8);
    PTR_PTR_004f07a0 = (undefined *)&PTR_DAT_004f0770;
    FUN_004b6970(DAT_008d0ef8);
    free(DAT_008d0ef8);
    DAT_008d0ef8 = (undefined4 *)0x0;
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
  FUN_004b6970(DAT_008d0ef8);
  free(DAT_008d0ef8);
  DAT_008d0ef8 = puVar1;
  return 0;
}

/* ---- 0x004b6820  FUN_004b6820 ---- */
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

/* ---- 0x004b6970  FUN_004b6970 ---- */
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

/* ---- 0x004b69e0  FUN_004b69e0 ---- */
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
  int iVar9;
  #define local_1c (*(undefined2 **)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(undefined2 **)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_e (*(byte (*)[14])(_frame + (0x30 - 0xe)))
  
  iVar9 = 0;
  puVar8 = (undefined2 *)0x0;
  if (DAT_008d0b70 == 0) {
    PTR_DAT_004ed320 = &DAT_004ed32a;
    PTR_DAT_004ed324 = &DAT_004ed32a;
    free(DAT_008d0efc);
    free(DAT_008d0f00);
    DAT_008d0efc = (undefined2 *)0x0;
    DAT_008d0f00 = (undefined2 *)0x0;
    return 0;
  }
  if ((DAT_008d0b80 != 0) || (iVar3 = FUN_004ba340(0,DAT_008d0f14,0xb,&DAT_008d0b80), iVar3 == 0)) {
    local_18 = (undefined2 *)malloc(0x202);
    local_1c = (undefined2 *)malloc(0x202);
    iVar9 = malloc(0x101);
    puVar8 = (undefined2 *)malloc(0x202);
    if ((local_18 != (undefined2 *)0x0) &&
       (((local_1c != (undefined2 *)0x0 && (iVar9 != 0)) && (puVar8 != (undefined2 *)0x0)))) {
      iVar3 = 0;
      do {
        *(char *)(iVar3 + iVar9) = (char)iVar3;
        iVar3 = iVar3 + 1;
      } while (iVar3 < 0x100);
      iVar3 = GetCPInfo(DAT_008d0b80,(int)&local_14);
      if ((iVar3 != 0) && (local_14 < 3)) {
        DAT_004ed52c = local_14 & 0xffff;
        if ((1 < DAT_004ed52c) && (local_e[0] != 0)) {
          pbVar5 = local_e + 1;
          do {
            if (*pbVar5 == 0) break;
            uVar4 = (uint)pbVar5[-1];
            if (uVar4 <= *pbVar5) {
              do {
                *(undefined1 *)(uVar4 + iVar9) = 0;
                uVar4 = uVar4 + 1;
              } while ((int)uVar4 <= (int)(uint)*pbVar5);
            }
            pbVar1 = pbVar5 + 1;
            pbVar5 = pbVar5 + 2;
          } while (*pbVar1 != 0);
        }
        puVar2 = local_18 + 1;
        iVar3 = __crtGetStringTypeA(1,iVar9,0x100,puVar2,0,0,0);
        if (iVar3 != 0) {
          *local_18 = 0;
          iVar3 = 0;
          puVar6 = puVar8;
          do {
            *puVar6 = (short)iVar3;
            puVar6 = puVar6 + 1;
            iVar3 = iVar3 + 1;
          } while (iVar3 < 0x100);
          puVar6 = local_1c + 1;
          iVar3 = FUN_004b7800(1,puVar8,0x100,puVar6,0,0);
          if (iVar3 != 0) {
            *local_1c = 0;
            if ((1 < (int)DAT_004ed52c) && (local_e[0] != 0)) {
              pbVar5 = local_e + 1;
              do {
                if (*pbVar5 == 0) break;
                uVar4 = (uint)pbVar5[-1];
                if (uVar4 <= *pbVar5) {
                  puVar7 = local_18 + uVar4 + 1;
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
            if (DAT_008d0efc != (undefined2 *)0x0) {
              free(DAT_008d0efc);
            }
            DAT_008d0efc = local_18;
            if (DAT_008d0f00 != (undefined2 *)0x0) {
              free(DAT_008d0f00);
            }
            DAT_008d0f00 = local_1c;
            free(iVar9);
            free(puVar8);
            return 0;
          }
        }
      }
    }
  }
  free(local_18);
  free(local_1c);
  free(iVar9);
  free(puVar8);
  return 1;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_e


/* ---- 0x004b6f50  FUN_004b6f50 ---- */
uint FUN_004b6f50(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = ((code *)FUN_004b6fb0)();
  uVar1 = param_2 & param_1 | ~param_2 & uVar1;
  ((code *)FUN_004b7050)(uVar1);
  return uVar1;
}

/* ---- 0x004b6f90  FUN_004b6f90 ---- */
void FUN_004b6f90(undefined4 param_1,uint param_2)

{
  FUN_004b6f50(param_1,param_2 & 0xfff7ffff);
  return;
}

/* ---- 0x004b6fb0  FUN_004b6fb0 ---- */
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

/* ---- 0x004b7050  FUN_004b7050 ---- */
void FUN_004b7050(void)

{
  return;
}

/* ---- 0x004b70e0  FUN_004b70e0 ---- */
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

/* ---- 0x004b7150  FUN_004b7150 ---- */
int __cdecl FUN_004b7150(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  bVar1 = (byte)(param_2 >> 0x1f);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  iVar2 = __addl(*(undefined4 *)(param_1 + iVar3 * 4),
                 1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) & 0x1f),
                 param_1 + iVar3 * 4);
  iVar3 = iVar3 + -1;
  if (-1 < iVar3) {
    puVar4 = (undefined4 *)(param_1 + iVar3 * 4);
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

/* ---- 0x004b71c0  FUN_004b71c0 ---- */
undefined4 FUN_004b71c0(int param_1,int param_2)

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
     (iVar1 = FUN_004b70e0(param_1,param_2 + 1), iVar1 == 0)) {
    local_4 = FUN_004b7150(param_1,param_2 + -1);
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


/* ---- 0x004b7260  FUN_004b7260 ---- */
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

/* ---- 0x004b7280  FUN_004b7280 ---- */
void FUN_004b7280(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}

/* ---- 0x004b7290  FUN_004b7290 ---- */
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

/* ---- 0x004b72b0  FUN_004b72b0 ---- */
void FUN_004b72b0(uint *param_1,int param_2)

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

/* ---- 0x004b7560  FUN_004b7560 ---- */
void FUN_004b7560(undefined4 param_1,undefined4 param_2)

{
  _ld12tocvt(param_1,param_2,&DAT_004f03e8);
  return;
}

/* ---- 0x004b7580  FUN_004b7580 ---- */
void FUN_004b7580(undefined4 param_1,undefined4 param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(undefined1 (*)[12])(_frame + (0x20 - 0xc)))
  
  __strgtold12(local_c,&param_2,param_2,0,0,0,0);
  _ld12tod(local_c,param_1);
  return;
}
#undef local_c


/* ---- 0x004b75c0  FUN_004b75c0 ---- */
void FUN_004b75c0(undefined4 param_1,undefined4 param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(undefined1 (*)[12])(_frame + (0x20 - 0xc)))
  
  __strgtold12(local_c,&param_2,param_2,0,0,0,0);
  FUN_004b7560(local_c,param_1);
  return;
}
#undef local_c


/* ---- 0x004b7600  FUN_004b7600 ---- */
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

/* ---- 0x004b76a0  FUN_004b76a0 ---- */
int * FUN_004b76a0(undefined4 param_1,undefined4 param_2,int *param_3,char *param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  #define local_28 (*(undefined4 *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(undefined4 *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(undefined2 *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(short *)(_frame + (0x40 - 0x1c)))
  #define local_1a (*(char *)(_frame + (0x40 - 0x1a)))
  #define local_18 (*(char (*)[24])(_frame + (0x40 - 0x18)))
  
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


/* ---- 0x004b7730  FUN_004b7730 ---- */
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

/* ---- 0x004b77f0  FUN_004b77f0 ---- */
void FUN_004b77f0(void)

{
  _amsg_exit(2);
  return;
}

/* ---- 0x004b7800  FUN_004b7800 ---- */
int FUN_004b7800(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int a5;
  int iVar2;
  int iVar3;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar3 = 0;
  if (DAT_008d0f50 == 0) {
    iVar1 = GetStringTypeW(1,IMG_ADDR(0x004d8d8c),1,(int)&local_4);
    if (iVar1 == 0) {
      iVar1 = GetStringTypeA(0,1,IMG_ADDR(0x008d0874),1,(int)&local_4);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_008d0f50 = 2;
    }
    else {
      DAT_008d0f50 = 1;
    }
  }
  if (DAT_008d0f50 != 1) {
    local_4 = DAT_008d0f50;
    if (DAT_008d0f50 == 2) {
      local_4 = 0;
      if (param_5 == 0) {
        param_5 = DAT_008d0b80;
      }
      iVar1 = WideCharToMultiByte(param_5,0x220,param_2,param_3,0,0,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      a5 = calloc(1,iVar1);
      if (a5 == 0) {
        return 0;
      }
      iVar2 = WideCharToMultiByte(param_5,0x220,param_2,param_3,a5,iVar1,0,0);
      if ((iVar2 != 0) && (iVar3 = malloc(iVar1 * 2 + 2), iVar3 != 0)) {
        if (param_6 == 0) {
          param_6 = DAT_008d0b70;
        }
        param_3 = param_3 * 2;
        *(undefined2 *)(iVar3 + param_3) = 0xffff;
        *(undefined2 *)(iVar3 + -2 + param_3) = 0xffff;
        local_4 = GetStringTypeA(param_6,param_1,a5,iVar1,iVar3);
        if ((*(short *)(iVar3 + -2 + param_3) == -1) || (*(short *)(iVar3 + param_3) != -1)) {
          local_4 = 0;
        }
        else {
          memcpy(param_4,iVar3,param_3);
        }
      }
      free(a5);
      free(iVar3);
    }
    return local_4;
  }
  iVar3 = GetStringTypeW(param_1,param_2,param_3,param_4);
  return iVar3;
}
#undef local_4


/* ---- 0x004b7c10  FUN_004b7c10 ---- */
int FUN_004b7c10(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  _lock(2);
  iVar3 = 3;
  if (3 < DAT_00906ae0) {
    do {
      iVar1 = *(int *)(DAT_00905ac4 + iVar3 * 4);
      if (iVar1 != 0) {
        if (((*(byte *)(iVar1 + 0xc) & 0x83) != 0) && (iVar1 = fclose(iVar1), iVar1 != -1)) {
          iVar2 = iVar2 + 1;
        }
        if (0x13 < iVar3) {
          DeleteCriticalSection(*(int *)(DAT_00905ac4 + iVar3 * 4) + 0x20);
          free(*(undefined4 *)(DAT_00905ac4 + iVar3 * 4));
          *(undefined4 *)(DAT_00905ac4 + iVar3 * 4) = 0;
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < DAT_00906ae0);
  }
  _unlock(2);
  return iVar2;
}

/* ---- 0x004b8f30  FUN_004b8f30 ---- */
longlong __fastcall FUN_004b8f30(byte param_1,int param_2)

{
  uint in_EAX;
  
  if (0x3f < param_1) {
    return 0;
  }
  if (param_1 < 0x20) {
    return CONCAT44(param_2 << (param_1 & 0x1f) | in_EAX >> 0x20 - (param_1 & 0x1f),
                    in_EAX << (param_1 & 0x1f));
  }
  return (ulonglong)(in_EAX << (param_1 & 0x1f)) << 0x20;
}

/* ---- 0x004b9916  FUN_004b9916 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004b9916(undefined4 param_1,uint param_2,ushort param_3)

{
  undefined4 in_EAX;
  int iVar1;
  float10 fVar2;
  float10 fVar3;
  undefined4 in_stack_0000001c;
  undefined2 uStack00000020;
  undefined2 uStack00000022;
  ushort in_stack_00000024;
  
  if ((((((CONCAT22(param_3,PIECE(param_2,2,2)) ^ 0x700) & 0x700) == 0) &&
       ((&DAT_004f04dc)[(PIECE(param_2,2,2) & 0x7800) >> 0xb] != '\0')) && ((param_3 & 0x7fff) != 0x7fff)
      ) && ((((in_stack_00000024 & 0x7fff) != 0 && ((in_stack_00000024 & 0x7fff) != 0x7fff)) &&
            (((PIECE(uStack00000020,0,4) & 0x7fffffff) == 0 && ((param_2 & 0x7fffffff) == 0)))))) {
    if ((ushort)((param_3 & 0x7fff) + 0x3f) < (in_stack_00000024 & 0x7fff)) {
      iVar1 = ((in_stack_00000024 & 0x7fff) - (param_3 & 0x7fff) & 0x3f | 0x20) + 1;
      fVar3 = ABS((float10)CONCAT28(in_stack_00000024 & 0x7fff | param_3 & 0x8000,
                                    CONCAT26(PIECE(param_2,2,2),CONCAT24((undefined2)param_2,param_1))));
      fVar2 = ABS((float10)CONCAT28(in_stack_00000024,
                                    CONCAT26(uStack00000022,
                                             CONCAT24(uStack00000020,in_stack_0000001c))));
      do {
        if (fVar3 <= fVar2) {
          fVar2 = fVar2 - fVar3;
        }
        fVar3 = fVar3 * (float10)_DAT_004f050c;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    else {
      while (-1 < (int)((in_stack_00000024 & 0x7fff) - ((param_3 & 0x7fff) + 10))) {
        fVar2 = (float10)CONCAT28(in_stack_00000024,
                                  CONCAT26(uStack00000022,CONCAT24(uStack00000020,in_stack_0000001c)
                                          ));
        fVar3 = (float10)CONCAT28((in_stack_00000024 & 0x7fff) -
                                  ((in_stack_00000024 & 0x7fff) - param_3 & 7 | 4) |
                                  param_3 & 0x8000,
                                  CONCAT26(PIECE(param_2,2,2),CONCAT24((undefined2)param_2,param_1)));
        fVar2 = fVar2 - (float10)(unkint10)(fVar2 / fVar3) * fVar3;
        in_stack_0000001c = SUB104(fVar2,0);
        uStack00000020 = (undefined2)((unkuint10)fVar2 >> 0x20);
        uStack00000022 = (undefined2)((unkuint10)fVar2 >> 0x30);
        in_stack_00000024 = (ushort)((unkuint10)fVar2 >> 0x40);
      }
    }
  }
  return in_EAX;
}

/* ---- 0x004b9b1c  FUN_004b9b1c ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_004b9b1c(void)

{
  float10 in_ST0;
  float10 fVar1;
  float10 in_ST1;
  
  if (((uint)((unkuint10)in_ST1 >> 0x30) & 0x7fff0000) != 0) {
    fVar1 = (float10)((code *)FUN_004b9916)();
    return fVar1;
  }
  if (SUB104(in_ST1,0) != 0 || (int)((unkuint10)in_ST1 >> 0x20) != 0) {
    fVar1 = (float10)((undefined4 (*)(float))FUN_004b9916)(in_ST1 * (float10)_DAT_004f04f4);
    return fVar1;
  }
  return in_ST0 - (float10)(unkint10)(in_ST0 / in_ST1) * in_ST1;
}

/* ---- 0x004b9fc0  FUN_004b9fc0 ---- */
float10 FUN_004b9fc0(undefined4 param_1,undefined4 param_2,short param_3)

{
  return (float10)(double)CONCAT26(PIECE(param_2,2,2) & 0x800f | (param_3 + 0x3fe) * 0x10,
                                   CONCAT24((undefined2)param_2,param_1));
}

/* ---- 0x004ba000  FUN_004ba000 ---- */
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

/* ---- 0x004ba060  FUN_004ba060 ---- */
float10 FUN_004ba060(uint param_1,uint param_2,int *param_3)

{
  ushort uVar1;
  double dVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  
  if ((double)CONCAT17(PIECE(param_2,3,1),CONCAT16(PIECE(param_2,2,1),CONCAT24((undefined2)param_2,param_1)))
      == 0.0) {
    *param_3 = 0;
    return (float10)0.0;
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
    fVar6 = (float10)FUN_004b9fc0(param_1,CONCAT13(PIECE(param_2,3,1),
                                                   CONCAT12(PIECE(param_2,2,1),(undefined2)param_2)),0);
    *param_3 = iVar5;
    return (float10)(double)fVar6;
  }
  fVar6 = (float10)FUN_004b9fc0(param_1,param_2,0);
  *param_3 = (short)((ushort)(param_2 >> 0x14) & 0x7ff) + -0x3fe;
  return (float10)(double)fVar6;
}

/* ---- 0x004ba170  FUN_004ba170 ---- */
float10 FUN_004ba170(double param_1)

{
  return (float10)ROUND(param_1);
}

/* ---- 0x004ba190  FUN_004ba190 ---- */
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

/* ---- 0x004ba230  FUN_004ba230 ---- */
undefined4 __stdcall FUN_004ba230(int a1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  piVar1 = *(int **)a1;
  if (((*piVar1 == -0x1f928c9d) && (piVar1[4] == 3)) && (piVar1[5] == 0x19930520)) {
    terminate();
    return 1;
  }
  if (DAT_008d1028 != (code *)0x0) {
    iVar2 = _ValidateExecute(DAT_008d1028);
    if (iVar2 != 0) {
      uVar3 = (*DAT_008d1028)(a1);
      return uVar3;
    }
  }
  return 0;
}

/* ---- 0x004ba290  FUN_004ba290 ---- */
void FUN_004ba290(void)

{
  DAT_008d1028 = SetUnhandledExceptionFilter(FUN_004ba230);
  return;
}

/* ---- 0x004ba2b0  FUN_004ba2b0 ---- */
void FUN_004ba2b0(void)

{
  SetUnhandledExceptionFilter(DAT_008d1028);
  return;
}

/* ---- 0x004ba340  FUN_004ba340 ---- */
undefined4 FUN_004ba340(int param_1,undefined4 param_2,undefined4 param_3,int *param_4)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  bool bVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  #define local_80 (*(undefined1 (*)[128])(_frame + (0x90 - 0x80)))
  
  if (param_1 != 1) {
    if (param_1 != 0) {
      return 0xffffffff;
    }
    iVar3 = ((code *)FUN_004bc4c0)(param_2,param_3,&DAT_008d1038,4,0);
    if (iVar3 != 0) {
      pbVar7 = &DAT_008d1038;
      *(char *)param_4 = '\0';
      while( true ) {
        bVar1 = *pbVar7;
        if (DAT_004ed52c < 2) {
          uVar6 = (byte)PTR_DAT_004ed320[(uint)bVar1 * 2] & 4;
        }
        else {
          uVar6 = _isctype(bVar1,4);
        }
        if (uVar6 == 0) break;
        pbVar7 = pbVar7 + 2;
        *(byte *)param_4 = (char)*param_4 * '\n' + bVar1 + -0x30;
        if (IMG_ADDR(0x008d103f) < (int)pbVar7) {
          return 0;
        }
      }
      return 0;
    }
    return 0xffffffff;
  }
  puVar4 = local_80;
  bVar2 = false;
  iVar3 = ((code *)FUN_004bc5f0)(param_2,param_3,local_80,0x80,0);
  if (iVar3 == 0) {
    iVar3 = GetLastError();
    if (((iVar3 != 0x7a) || (iVar3 = ((code *)FUN_004bc5f0)(param_2,param_3,0,0,0), iVar3 == 0)) ||
       (puVar4 = (undefined1 *)malloc(iVar3), puVar4 == (undefined1 *)0x0)) goto LAB_004ba3f0;
    bVar2 = true;
    iVar3 = ((code *)FUN_004bc5f0)(param_2,param_3,puVar4,iVar3,0);
    if (iVar3 == 0) goto LAB_004ba3f0;
  }
  iVar5 = malloc(iVar3);
  *param_4 = iVar5;
  if (iVar5 != 0) {
    strncpy(iVar5,puVar4,iVar3);
    if (!bVar2) {
      return 0;
    }
    free(puVar4);
    return 0;
  }
LAB_004ba3f0:
  if (!bVar2) {
    return 0xffffffff;
  }
  free(puVar4);
  return 0xffffffff;
}
#undef local_80


/* ---- 0x004bb1e0  FUN_004bb1e0 ---- */
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
  #define local_6 (*(undefined1 *)(_frame + (0x30 - 0x6)))
  #define cStack_5 (*(char *)(_frame + (0x30 - 0x5)))
  
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
  local_6 = (undefined1)uVar4;
  cStack_5 = (char)(uVar4 >> 8);
  uStack_a = (undefined2)param_2;
  uStack_8 = (undefined2)(param_2 >> 0x10);
  uStack_e = (undefined2)param_1;
  uStack_c = (undefined2)((uint)param_1 >> 0x10);
  local_10 = 0;
  sVar9 = (short)(((uVar4 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar4 * 0x4d10 >>
                 0x10);
  __multtenpow12(&local_10,-(int)sVar9,1);
  if (0x3ffe < CONCAT11(cStack_5,local_6)) {
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
  uVar2 = CONCAT11(cStack_5,local_6);
  local_6 = 0;
  cStack_5 = '\0';
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
      param_3 = CONCAT13(cStack_5,CONCAT12(local_6,uStack_8));
      __shl_12(&local_10);
      __shl_12(&local_10);
      __add_12(&local_10,&param_1);
      __shl_12(&local_10);
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
#undef cStack_5
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
#undef local_6
#undef uStack_8
#undef uStack_a
#undef uStack_c
#undef uStack_e


/* ---- 0x004bc3d0  FUN_004bc3d0 ---- */
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

/* ---- 0x004bc400  FUN_004bc400 ---- */
int FUN_004bc400(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}

/* ---- 0x004bc410  FUN_004bc410 ---- */
int FUN_004bc410(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}

/* ---- 0x004bc430  FUN_004bc430 ---- */
int FUN_004bc430(void)

{
  short in_FPUControlWord;
  
  return (int)in_FPUControlWord;
}

/* ---- 0x004bc460  FUN_004bc460 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004bc460(void)

{
  return;
}

/* ---- 0x004bc4c0  FUN_004bc4c0 ---- */
int FUN_004bc4c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int a3;
  int unaff_ESI;
  int unaff_EDI;
  int a5;
  
  if (DAT_008d1080 == 0) {
    iVar1 = GetLocaleInfoW(0,1,0,0);
    if (iVar1 == 0) {
      iVar1 = GetLocaleInfoA(0,1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_008d1080 = 2;
    }
    else {
      DAT_008d1080 = 1;
    }
  }
  if (DAT_008d1080 == 1) {
    iVar1 = GetLocaleInfoW(param_1,param_2,param_3,param_4);
    return iVar1;
  }
  if (DAT_008d1080 != 2) {
    return DAT_008d1080;
  }
  a5 = 0;
  iVar1 = GetLocaleInfoA(param_1,param_2,0);
  if (iVar1 != 0) {
    a3 = malloc(iVar1);
    if (a3 == 0) {
      return 0;
    }
    iVar1 = GetLocaleInfoA(param_1,param_2,a3,iVar1);
    if (iVar1 != 0) {
      if (unaff_EDI == 0) {
        iVar1 = MultiByteToWideChar(unaff_ESI,1,a3,-1,0,0);
        if (iVar1 != 0) {
          free(a3);
          return iVar1;
        }
      }
      else {
        iVar1 = MultiByteToWideChar(unaff_ESI,1,a3,-1,a5,unaff_EDI);
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

/* ---- 0x004bc5f0  FUN_004bc5f0 ---- */
int FUN_004bc5f0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int a3;
  int unaff_ESI;
  int unaff_EDI;
  int a5;
  
  if (DAT_008d1084 == 0) {
    iVar1 = GetLocaleInfoW(0,1,0,0);
    if (iVar1 == 0) {
      iVar1 = GetLocaleInfoA(0,1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_008d1084 = 2;
    }
    else {
      DAT_008d1084 = 1;
    }
  }
  if (DAT_008d1084 == 2) {
    iVar1 = GetLocaleInfoA(param_1,param_2,param_3,param_4);
    return iVar1;
  }
  if (DAT_008d1084 != 1) {
    return DAT_008d1084;
  }
  a5 = 0;
  iVar1 = GetLocaleInfoW(param_1,param_2,0);
  if (iVar1 != 0) {
    a3 = malloc(iVar1 * 2);
    if (a3 == 0) {
      return 0;
    }
    iVar1 = GetLocaleInfoW(param_1,param_2,a3,iVar1);
    if (iVar1 != 0) {
      if (unaff_EDI == 0) {
        iVar1 = WideCharToMultiByte(unaff_ESI,0x220,a3,-1,0,0,0,0);
        if (iVar1 != 0) {
          free(a3);
          return iVar1;
        }
      }
      else {
        iVar1 = WideCharToMultiByte(unaff_ESI,0x220,a3,-1,a5,unaff_EDI,0,0);
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

/* ---- 0x004bcb40  FUN_004bcb40 ---- */
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

/* ---- 0x004bd430  FUN_004bd430 ---- */
void FUN_004bd430(void)

{
  LecShare_Shutdown();
  DAT_008d16a0 = 0;
  return;
}

/* ---- 0x004bd440  FUN_004bd440 ---- */
undefined4 FUN_004bd440(void)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 1;
  if ((DAT_008d16a0 != 0) && (DAT_008d16a4 == 0)) {
    ((code *)deflateParams_or_SetDictionary)(1,&DAT_004f0cc4,0);
    ((code *)deflateParams_or_SetDictionary)(1,&DAT_004f0cbc,0);
    ((code *)deflateParams_or_SetDictionary)(1,&DAT_004f0cb8,0);
    ((code *)deflateParams_or_SetDictionary)(1,&DAT_004f0cb4,0);
    iVar1 = LecShare_StartupModules();
    if (iVar1 == 0) {
      iVar1 = (*(code *)PTR_008d11d4[4])(&PTR_PTR_004f0b70,0);
      if (iVar1 == 0) {
        DAT_008d16a4 = 1;
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}

/* ---- 0x004bd4d0  FUN_004bd4d0 ---- */
void FUN_004bd4d0(void)

{
  if (DAT_008d16a4 != 0) {
    (*(code *)PTR_008d11d4[5])(&PTR_PTR_004f0b70);
    LecShare_UnwindStartup();
    DAT_008d16a4 = 0;
  }
  return;
}

/* ---- 0x004bdad0  FUN_004bdad0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004bdad0(void)

{
  undefined4 in_stack_00000014;
  int in_stack_0000001c;
  
  DAT_008d16b8 = in_stack_00000014;
  _DAT_008d16b0 = in_stack_0000001c;
  if (DAT_008d16bc == 0) {
    DAT_008d16bc = in_stack_0000001c;
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
  (**(code **)(DAT_008d11f4 + 0x20))(param_1,param_2,param_3);
  return;
}

/* ---- 0x004be000  FUN_004be000 ---- */
void FUN_004be000(undefined4 param_1)

{
  (**(code **)(DAT_008d11f4 + 0x24))(param_1);
  return;
}

/* ---- 0x004be020  FUN_004be020 ---- */
void FUN_004be020(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  (**(code **)(DAT_008d11f4 + 0x28))(param_1,param_2,param_3,param_4);
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
  (**(code **)(DAT_008d11f4 + 0x30))(param_1,param_2);
  return;
}

/* ---- 0x004be0e0  FUN_004be0e0 ---- */
void FUN_004be0e0(undefined4 param_1)

{
  (**(code **)(DAT_008d11f4 + 0x34))(param_1);
  return;
}

/* ---- 0x004be100  FUN_004be100 ---- */
void FUN_004be100(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (**(code **)(DAT_008d11f4 + 0x38))(param_1,param_2,param_3);
  return;
}

/* ---- 0x004be120  FUN_004be120 ---- */
void FUN_004be120(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (**(code **)(DAT_008d11f4 + 0x40))(param_1,param_2,param_3);
  return;
}

/* ---- 0x004be140  FUN_004be140 ---- */
void FUN_004be140(undefined4 param_1)

{
  (**(code **)(DAT_008d11f4 + 0x48))(param_1);
  return;
}

/* ---- 0x004be160  FUN_004be160 ---- */
void FUN_004be160(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (**(code **)(DAT_008d11f4 + 0x4c))(param_1,param_2,param_3);
  return;
}

/* ---- 0x004bf950  FUN_004bf950 ---- */
undefined4 __stdcall FUN_004bf950(int a1,int a2,int a3,int a4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  char *pcVar10;
  #define local_28 (*(undefined4 *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(int (*)[9])(_frame + (0x40 - 0x24)))
  
  iVar3 = g_nLightEdSelected;
  if ((uint)a2 < 0x111) {
    if (a2 == 0x110) {
      SendDlgItemMessageA(a1,0x3fb,0x465,0,32000);
      SendDlgItemMessageA(a1,0x3ff,0x465,0,32000);
      SendDlgItemMessageA(a1,0x400,0x465,0,32000);
      iVar7 = 0;
      piVar6 = local_24;
      iVar3 = 1;
      do {
        iVar7 = iVar7 + 1;
        piVar6[-1] = iVar7;
        *piVar6 = iVar3;
        iVar3 = iVar3 + 5;
        piVar6 = piVar6 + 2;
      } while (iVar3 < 0x1a);
      SendDlgItemMessageA(a1,0x3fb,0x46b,5,(int)&local_28);
      SendDlgItemMessageA(a1,0x3ff,0x46b,5,(int)&local_28);
      SendDlgItemMessageA(a1,0x400,0x46b,5,(int)&local_28);
      return 1;
    }
    if (a2 != 0x10) {
      return 0;
    }
    Lua_LightMgrShutdown();
    return 1;
  }
  if (a2 != 0x111) {
    if (a2 != 0x115) {
      return 0;
    }
    uVar4 = a3 & 0xffff;
    uVar8 = (uint)a3 >> 0x10;
    iVar3 = GetDlgItem(a1,0x3fb);
    if (a4 == iVar3) {
      LightEd_RefreshControl(a1,0x3fb,uVar4,uVar8);
      return 1;
    }
    iVar3 = GetDlgItem(a1,0x3ff);
    if (a4 == iVar3) {
      LightEd_RefreshControl(a1,0x3ff,uVar4,uVar8);
      return 1;
    }
    iVar3 = GetDlgItem(a1,0x400);
    if (a4 != iVar3) {
      return 0;
    }
    LightEd_RefreshControl(a1,0x400,uVar4,uVar8);
    return 1;
  }
  sVar2 = (short)((uint)a3 >> 0x10);
  switch(a3 & 0xffffU) {
  case 1000:
    if (sVar2 != 1) {
      return 1;
    }
    LightEd_UpdateDialog(a1);
    LightEd_ResetLight(g_nLightEdSelected,1);
    return 1;
  case 0x3e9:
  case 0x3ea:
  case 0x3eb:
    if (g_pLightEdSet == (void *)0x0) {
      return 1;
    }
    if (g_nLightEdSelected == -1) {
      return 1;
    }
    iVar3 = IsDlgButtonChecked(a1,0x3e9);
    if (iVar3 == 1) {
      *(undefined4 *)((&DAT_008d1730)[g_nLightEdSelected * 5] + 0x30) = 1;
    }
    else {
      iVar3 = IsDlgButtonChecked(a1,0x3ea);
      if (iVar3 == 1) {
        *(undefined4 *)((&DAT_008d1730)[g_nLightEdSelected * 5] + 0x30) = 2;
      }
      else {
        iVar3 = IsDlgButtonChecked(a1,0x3eb);
        if (iVar3 == 1) {
          *(undefined4 *)((&DAT_008d1730)[g_nLightEdSelected * 5] + 0x30) = 3;
        }
      }
    }
    LightEd_UpdateDialog(g_hLightEdDialog);
    return 1;
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
      return 0;
    }
    break;
  case 0x3f6:
    if ((sVar2 == 0) && (g_pLightEdSet != (void *)0x0)) {
      LightEd_AddLight();
      return 0;
    }
    break;
  case 0x3f7:
    if (((sVar2 == 0) && (g_pLightEdSet != (void *)0x0)) && (g_nLightEdSelected != -1)) {
      LightEd_DeleteLight(g_nLightEdSelected);
      return 0;
    }
    break;
  case 0x3f8:
    if ((sVar2 == 0) && (g_pLightEdSet != (void *)0x0)) {
      LightEd_SyncFromSet();
      LightMgr_UpdateDialog(a1);
      return 0;
    }
    break;
  case 0x3f9:
    if ((sVar2 == 0) && (g_pLightEdSet != (void *)0x0)) {
      LightEd_SaveSetFile();
      return 0;
    }
    break;
  case 0x3fa:
    if (g_pLightEdSet == (void *)0x0) {
      return 1;
    }
    if (g_nLightEdSelected == -1) {
      return 1;
    }
    iVar3 = IsDlgButtonChecked(a1,0x3fa);
    *(uint *)((&DAT_008d1730)[g_nLightEdSelected * 5] + 0x34) = (uint)(iVar3 == 1);
    return 1;
  case 0x3fc:
    LightEd_SetAllEnabled(0);
    return 1;
  case 0x3fd:
    LightEd_SetAllEnabled(1);
    return 1;
  case 0x3fe:
    if ((g_pLightEdSet != (void *)0x0) && (g_nLightEdSelected != -1)) {
      iVar3 = IsDlgButtonChecked(a1,0x3fe);
      (&DAT_008d1734)[g_nLightEdSelected * 5] = (uint)(iVar3 == 1);
      LightEd_MoveMarkerActor();
      return 1;
    }
    return 1;
  case 0x401:
    if ((sVar2 == 0) && (g_nLightEdSelected != -1)) {
      LightEd_ResetLight(g_nLightEdSelected,0);
      LightEd_UpdateDialog(a1);
      return 0;
    }
    break;
  case 0x402:
    if (((sVar2 == 0) && (g_nLightEdSelected != -1)) &&
       (iVar7 = Plat_InputDialog(s_New_light_name_004f0ec8,(char *)0x0,(char *)&local_28,0x20,
                                 (char *)0x0), iVar7 != 0)) {
      uVar4 = 0;
      if (*(int *)((int)g_pLightEdSet + 0xb8) != 0) {
        puVar9 = &DAT_008d1730;
        do {
          if ((uVar4 != iVar3) && (iVar7 = _stricmp(*puVar9,&local_28), iVar7 == 0)) break;
          uVar4 = uVar4 + 1;
          puVar9 = puVar9 + 5;
        } while (uVar4 < *(uint *)((int)g_pLightEdSet + 0xb8));
      }
      if (uVar4 < *(uint *)((int)g_pLightEdSet + 0xb8)) {
        MessageBoxA(0,IMG_ADDR(0x004f0e74),IMG_ADDR(0x004f0eb0),0x30);
      }
      else {
        pcVar5 = (char *)&local_28;
        while ((char)local_28 != '\0') {
          if (*pcVar5 == ' ') {
            *pcVar5 = '_';
          }
          pcVar10 = pcVar5 + 1;
          pcVar5 = pcVar5 + 1;
          PIECE(local_28,0,1) = *pcVar10;
        }
        uVar4 = 0xffffffff;
        pcVar5 = (char *)&local_28;
        do {
          pcVar10 = pcVar5;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar10 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar10;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        pcVar5 = pcVar10 + -uVar4;
        pcVar10 = (char *)(&DAT_008d1730)[iVar3 * 5];
        for (uVar8 = uVar4 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)pcVar10 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar10 = pcVar10 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar10 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar10 = pcVar10 + 1;
        }
      }
      LightMgr_UpdateDialog(a1);
      SendDlgItemMessageA(a1,1000,0x186,iVar3,0);
      LightEd_UpdateDialog(a1);
      LightEd_ResetLight(iVar3,1);
    }
  }
  return 0;
}
#undef local_24
#undef local_28


/* ---- 0x004bffb0  FUN_004bffb0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __stdcall FUN_004bffb0(int a1,int a2,int a3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  if ((((a1 == 0) && (g_hLightEdDialog != (void *)0x0)) &&
      (iVar1 = Win_IsFocusWithin(g_hLightEdDialog), iVar1 != 0)) && (g_nLightEdSelected != -1)) {
    uVar3 = (uint)a3 >> 0x10 & 0x2000;
    uVar2 = (~((uint)a3 >> 0x10) & 0xffff) >> 0xf;
    iVar1 = (&DAT_008d1730)[g_nLightEdSelected * 5];
    if ((uVar2 & (DAT_008d3648 & 0xffff) == a2) == 0) {
      _DAT_004f0d18 = 0.01;
      _DAT_004f0d1c = 1.0;
      DAT_008d3648 = CONCAT22(PIECE(DAT_008d3648,2,2),-(ushort)(uVar2 != 0) & (ushort)a2);
    }
    else {
      _DAT_004f0d18 = _DAT_004f0d18 - -0.005;
      _DAT_004f0d1c = _DAT_004f0d1c - -0.5;
    }
    switch(a2) {
    case 0x12:
      break;
    default:
      goto switchD_004c008d_caseD_13;
    case 0x25:
      if (uVar2 != 0) {
        a3 = (int)(*(float *)(iVar1 + 0x20) - _DAT_004f0d18);
        uVar4 = 0x3ef;
LAB_004c0263:
        LightEd_SetDlgFloat(g_hLightEdDialog,uVar4,a3,1);
        return 1;
      }
      break;
    case 0x26:
      if (uVar2 != 0) {
        if (uVar3 != 0) {
          a3 = (int)(*(float *)(iVar1 + 0x28) + _DAT_004f0d18);
          uVar4 = 0x3f1;
          goto LAB_004c041f;
        }
        a3 = (int)(*(float *)(iVar1 + 0x24) + _DAT_004f0d18);
        uVar4 = 0x3f0;
        goto LAB_004c0263;
      }
      break;
    case 0x27:
      if (uVar2 != 0) {
        LightEd_SetDlgFloat(g_hLightEdDialog,0x3ef,*(float *)(iVar1 + 0x20) + _DAT_004f0d18,1);
        return 1;
      }
      break;
    case 0x28:
      if (uVar2 != 0) {
        if (uVar3 != 0) {
          LightEd_SetDlgFloat(g_hLightEdDialog,0x3f1,*(float *)(iVar1 + 0x28) - _DAT_004f0d18,1);
          return 1;
        }
        LightEd_SetDlgFloat(g_hLightEdDialog,0x3f0,*(float *)(iVar1 + 0x24) - _DAT_004f0d18,1);
        return 1;
      }
      break;
    case 0x62:
      if (uVar2 != 0) {
        a3 = (int)((float)(&DAT_008d1738)[g_nLightEdSelected * 5] + _DAT_004f0d1c);
        if ((float)a3 <= 360.0) {
          if ((float)a3 < -180.0) {
            a3 = (int)((float)a3 - -360.0);
          }
        }
        else {
          a3 = (int)((float)a3 - 360.0);
        }
        uVar4 = 0x3f2;
        goto LAB_004c0263;
      }
      break;
    case 100:
      if (uVar2 != 0) {
        if (uVar3 == 0) {
          a3 = (int)((float)(&DAT_008d173c)[g_nLightEdSelected * 5] - _DAT_004f0d1c);
          if ((float)a3 <= 360.0) {
            if ((float)a3 < -180.0) {
              a3 = (int)((float)a3 - -360.0);
            }
          }
          else {
            a3 = (int)((float)a3 - 360.0);
          }
          LightEd_SetDlgFloat(g_hLightEdDialog,0x3f4,a3,1);
          return 1;
        }
        a3 = (int)((float)(&DAT_008d1740)[g_nLightEdSelected * 5] - _DAT_004f0d1c);
        if ((float)a3 <= 360.0) {
          if ((float)a3 < -180.0) {
            a3 = (int)((float)a3 - -360.0);
          }
        }
        else {
          a3 = (int)((float)a3 - 360.0);
        }
        uVar4 = 0x3f5;
LAB_004c041f:
        LightEd_SetDlgFloat(g_hLightEdDialog,uVar4,a3,1);
        return 1;
      }
      break;
    case 0x66:
      if (uVar2 != 0) {
        if (uVar3 != 0) {
          a3 = (int)((float)(&DAT_008d1740)[g_nLightEdSelected * 5] + _DAT_004f0d1c);
          if ((float)a3 <= 360.0) {
            if ((float)a3 < -180.0) {
              a3 = (int)((float)a3 - -360.0);
            }
          }
          else {
            a3 = (int)((float)a3 - 360.0);
          }
          LightEd_SetDlgFloat(g_hLightEdDialog,0x3f5,a3,1);
          return 1;
        }
        a3 = (int)((float)(&DAT_008d173c)[g_nLightEdSelected * 5] + _DAT_004f0d1c);
        if ((float)a3 <= 360.0) {
          if ((float)a3 < -180.0) {
            a3 = (int)((float)a3 - -360.0);
          }
        }
        else {
          a3 = (int)((float)a3 - 360.0);
        }
        uVar4 = 0x3f4;
        goto LAB_004c041f;
      }
      break;
    case 0x68:
      if (uVar2 != 0) {
        a3 = (int)((float)(&DAT_008d1738)[g_nLightEdSelected * 5] - _DAT_004f0d1c);
        if ((float)a3 <= 360.0) {
          if ((float)a3 < -180.0) {
            a3 = (int)((float)a3 - -360.0);
          }
        }
        else {
          a3 = (int)((float)a3 - 360.0);
        }
        LightEd_SetDlgFloat(g_hLightEdDialog,0x3f2,a3,1);
        return 1;
      }
    }
    return 1;
  }
switchD_004c008d_caseD_13:
  iVar1 = CallNextHookEx(DAT_008d363c,a1,a2,a3);
  return iVar1;
}

/* ---- 0x004c0630  FUN_004c0630 ---- */
void FUN_004c0630(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0x21; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  strncpy(param_1,s_UNKNOWN_004ddb8c,0x1f);
  *(undefined1 *)((int)param_1 + 0x1f) = 0;
  return;
}

/* ---- 0x004c0660  FUN_004c0660 ---- */
int FUN_004c0660(char *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  
  pcVar4 = param_1;
  if (DAT_008d364c != (code *)0x0) {
    iVar1 = (*DAT_008d364c)(param_1);
    return iVar1;
  }
  iVar1 = (*g_pSvcRdroid->pFopen)(param_1,&DAT_004ddb18);
  if (iVar1 != 0) {
    iVar2 = (*g_pSvcRdroid->pAlloc)
                      (0x84,s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,DAT_004f0f08 + 0x11);
    if (iVar2 != 0) {
      (*g_pSvcRdroid->pFread)(iVar1,&param_1,4);
      if (param_1 == (char *)0x4b455946) {
        iVar3 = FUN_004c0ce0(iVar1,iVar2);
        if (iVar3 != 0) {
          uVar5 = 0x1f;
          pcVar4 = Str_FileNameFromPath(pcVar4);
          strncpy(iVar2,pcVar4,uVar5);
          *(undefined1 *)(iVar2 + 0x1f) = 0;
          (*g_pSvcRdroid->pFclose)(iVar1);
          return iVar2;
        }
        (*g_pSvcRdroid->pFclose)(iVar1);
        FUN_004c0e40(iVar2);
        return 0;
      }
      (*g_pSvcRdroid->pFclose)(iVar1);
      iVar1 = FUN_004c0770(pcVar4,iVar2);
      if (iVar1 != 0) {
        return iVar2;
      }
    }
    FUN_004c0e40(iVar2);
  }
  return 0;
}

/* ---- 0x004c0770  FUN_004c0770 ---- */
undefined4 FUN_004c0770(char *param_1,int param_2)

{
  unsigned char _frame[0x80] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  char *pcVar2;
  int iVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  byte *pbVar9;
  bool bVar10;
  undefined4 uVar11;
  #define uStack_68 (*(uint *)(_frame + (0x80 - 0x68)))
  #define iStack_64 (*(int *)(_frame + (0x80 - 0x64)))
  #define iStack_60 (*(int *)(_frame + (0x80 - 0x60)))
  #define uStack_5c (*(uint *)(_frame + (0x80 - 0x5c)))
  #define local_58 (*(undefined4 *)(_frame + (0x80 - 0x58)))
  #define uStack_54 (*(undefined4 *)(_frame + (0x80 - 0x54)))
  #define uStack_50 (*(undefined4 *)(_frame + (0x80 - 0x50)))
  #define uStack_4c (*(undefined4 *)(_frame + (0x80 - 0x4c)))
  #define uStack_48 (*(undefined4 *)(_frame + (0x80 - 0x48)))
  #define uStack_44 (*(undefined4 *)(_frame + (0x80 - 0x44)))
  #define uStack_40 (*(undefined4 *)(_frame + (0x80 - 0x40)))
  #define uStack_3c (*(undefined4 *)(_frame + (0x80 - 0x3c)))
  #define uStack_38 (*(undefined4 *)(_frame + (0x80 - 0x38)))
  #define uStack_34 (*(undefined4 *)(_frame + (0x80 - 0x34)))
  #define uStack_30 (*(undefined4 *)(_frame + (0x80 - 0x30)))
  #define uStack_2c (*(undefined4 *)(_frame + (0x80 - 0x2c)))
  #define uStack_28 (*(undefined4 *)(_frame + (0x80 - 0x28)))
  #define auStack_20 (*(undefined1 (*)[32])(_frame + (0x80 - 0x20)))
  
  FUN_004c0630(param_2);
  uVar11 = 0x1f;
  pcVar2 = Str_FileNameFromPath(param_1);
  strncpy(param_2,pcVar2,uVar11);
  *(undefined1 *)(param_2 + 0x1f) = 0;
  iVar3 = ((code *)FUN_0047c7c0)(param_1);
  if (iVar3 == 0) {
    return 0;
  }
  iVar3 = Std_ParseCommandLine();
  if ((((((iVar3 != 0) && (iVar3 = sscanf(DAT_00900520,s_section___s_004ddd64), iVar3 == 1)) &&
        (iVar3 = Std_ParseCommandLine(), iVar3 != 0)) &&
       ((iVar3 = sscanf(DAT_00900520,s_flags__x_004f0ff0), iVar3 == 1 &&
        (iVar3 = Std_ParseCommandLine(), iVar3 != 0)))) &&
      (iVar3 = sscanf(DAT_00900520,s_type__x_004f0fe4), iVar3 == 1)) &&
     (((iVar3 = Std_ParseCommandLine(), iVar3 != 0 &&
       (iVar3 = sscanf(DAT_00900520,s_frames__d_004f0fd8), iVar3 == 1)) &&
      ((iVar3 = Std_ParseCommandLine(), iVar3 != 0 &&
       (iVar3 = sscanf(DAT_00900520,s_fps__f_004f0fd0), iVar3 == 1)))))) {
    *(undefined4 *)(param_2 + 0x30) = local_58;
    iVar3 = Std_ParseCommandLine();
    if ((iVar3 != 0) && (iVar3 = sscanf(DAT_00900520,s_joints__d_004f0fc4), iVar3 == 1)) {
      puVar4 = (undefined4 *)
               (*g_pSvcRdroid->pAlloc)
                         (param_2 * 0x2c,s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,
                          DAT_004f0f0c + 0x42);
      *(undefined4 **)(param_2 + 0x3c) = puVar4;
      if (puVar4 != (undefined4 *)0x0) {
        for (uVar8 = param_2 * 0xb & 0x3fffffff; uVar8 != 0; uVar8 = uVar8 - 1) {
          *puVar4 = 0;
          puVar4 = puVar4 + 1;
        }
        for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined1 *)puVar4 = 0;
          puVar4 = (undefined4 *)((int)puVar4 + 1);
        }
        *(int *)(param_2 + 0x28) = param_2;
        *(int *)(param_2 + 0x38) = param_2;
        iVar3 = Std_ParseCommandLine();
        if ((iVar3 != 0) && (iVar3 = sscanf(DAT_00900520,s_section___s_004ddd64), iVar3 == 1)) {
          pbVar9 = &DAT_004f0fbc;
          pbVar5 = &DAT_009056c0;
          do {
            bVar1 = *pbVar5;
            bVar10 = bVar1 < *pbVar9;
            if (bVar1 != *pbVar9) {
LAB_004c099a:
              iVar3 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
              goto LAB_004c099f;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar5[1];
            bVar10 = bVar1 < pbVar9[1];
            if (bVar1 != pbVar9[1]) goto LAB_004c099a;
            pbVar5 = pbVar5 + 2;
            pbVar9 = pbVar9 + 2;
          } while (bVar1 != 0);
          iVar3 = 0;
LAB_004c099f:
          if (iVar3 == 0) {
            iVar3 = Std_ParseCommandLine();
            if (((iVar3 == 0) || (iVar3 = sscanf(DAT_00900520,s_markers__d_004f0fb0), iVar3 != 1))
               || (8 < uStack_68)) goto LAB_004c0cbf;
            uVar8 = 0;
            *(uint *)(param_2 + 0x40) = uStack_68;
            if (uStack_68 != 0) {
              do {
                iVar3 = Std_ParseCommandLine();
                if ((iVar3 == 0) || (iVar3 = sscanf(DAT_00900520,s__f__d_004f0fa8), iVar3 != 2))
                goto LAB_004c0cbf;
                uVar8 = uVar8 + 1;
              } while (uVar8 < uStack_68);
            }
            iVar3 = Std_ParseCommandLine();
            if ((iVar3 == 0) || (iVar3 = sscanf(DAT_00900520,s_section___s_004ddd64), iVar3 != 1))
            goto LAB_004c0cbf;
          }
          iVar3 = Std_ParseCommandLine();
          if ((iVar3 != 0) && (iVar3 = sscanf(DAT_00900520,s_nodes__d_004f0f9c), iVar3 == 1)) {
            param_1 = (char *)0x0;
            if (uStack_5c == 0) {
              FUN_0047c8c0();
              return 1;
            }
            while ((((iVar3 = Std_ParseCommandLine(), iVar3 != 0 &&
                     (iVar3 = sscanf(DAT_00900520,s_node__d_004f0f90), iVar3 == 1)) &&
                    (iVar3 = Std_ParseCommandLine(), iVar3 != 0)) &&
                   (iVar3 = sscanf(DAT_00900520,s_mesh_name__s_004f0f80), iVar3 == 1))) {
              iVar3 = *(int *)(param_2 + 0x3c) + iStack_64 * 0x2c;
              strncpy(iVar3,auStack_20,0x1f);
              *(undefined1 *)(iVar3 + 0x1f) = 0;
              iVar6 = Std_ParseCommandLine();
              if ((iVar6 == 0) || (iVar6 = sscanf(DAT_00900520,s_entries__d_004f0f74), iVar6 != 1))
              break;
              *(int *)(iVar3 + 0x20) = iStack_64;
              *(int *)(iVar3 + 0x24) = iStack_60;
              iVar6 = (*g_pSvcRdroid->pAlloc)
                                (iStack_60 * 0x38,s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,
                                 DAT_004f0f0c + 0x9b);
              *(int *)(iVar3 + 0x28) = iVar6;
              if (iVar6 == 0) break;
              uVar8 = 0;
              if (*(int *)(iVar3 + 0x24) != 0) {
                do {
                  iVar7 = Std_ParseCommandLine();
                  if ((iVar7 == 0) ||
                     (iVar7 = sscanf(DAT_00900520,s__d___f__x__f__f__f__f__f__f_004f0f54),
                     iVar7 != 9)) goto LAB_004c0cbf;
                  *(undefined4 *)(iVar6 + 8) = uStack_54;
                  *(undefined4 *)(iVar6 + 0xc) = uStack_50;
                  *(undefined4 *)(iVar6 + 0x10) = uStack_4c;
                  *(undefined4 *)(iVar6 + 0x14) = uStack_48;
                  *(undefined4 *)(iVar6 + 0x18) = uStack_44;
                  *(undefined4 *)(iVar6 + 0x1c) = uStack_40;
                  iVar7 = Std_ParseCommandLine();
                  if ((iVar7 == 0) ||
                     (iVar7 = sscanf(DAT_00900520,s__f__f__f__f__f__f_004f0f40), iVar7 != 6))
                  goto LAB_004c0cbf;
                  *(undefined4 *)(iVar6 + 0x20) = uStack_3c;
                  *(undefined4 *)(iVar6 + 0x24) = uStack_38;
                  *(undefined4 *)(iVar6 + 0x28) = uStack_34;
                  *(undefined4 *)(iVar6 + 0x2c) = uStack_30;
                  *(undefined4 *)(iVar6 + 0x30) = uStack_2c;
                  *(undefined4 *)(iVar6 + 0x34) = uStack_28;
                  iVar6 = iVar6 + 0x38;
                  uVar8 = uVar8 + 1;
                } while (uVar8 < *(uint *)(iVar3 + 0x24));
              }
              param_1 = (char *)((int)param_1 + 1);
              if (uStack_5c <= param_1) {
                FUN_0047c8c0();
                return 1;
              }
            }
          }
        }
      }
    }
  }
LAB_004c0cbf:
  FUN_0047c8c0();
  return 0;
}
#undef auStack_20
#undef iStack_60
#undef iStack_64
#undef local_58
#undef uStack_28
#undef uStack_2c
#undef uStack_30
#undef uStack_34
#undef uStack_38
#undef uStack_3c
#undef uStack_40
#undef uStack_44
#undef uStack_48
#undef uStack_4c
#undef uStack_50
#undef uStack_54
#undef uStack_5c
#undef uStack_68


/* ---- 0x004c0ce0  FUN_004c0ce0 ---- */
undefined4 FUN_004c0ce0(undefined4 param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar2 = param_2;
  (*g_pSvcRdroid->pFread)(param_1,param_2,0x84);
  puVar3 = (undefined4 *)
           (*g_pSvcRdroid->pAlloc)
                     (*(int *)(param_2 + 0x38) * 0x2c,s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,
                      DAT_004f0f10 + 0x16);
  *(undefined4 **)(param_2 + 0x3c) = puVar3;
  if (puVar3 == (undefined4 *)0x0) {
LAB_004c0e2c:
    (*g_pSvcRdroid->pFclose)(param_1);
    return 0;
  }
  piVar1 = (int *)(param_2 + 0x38);
  param_2 = 0;
  for (uVar6 = *piVar1 * 0xb & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1) {
    *(undefined1 *)puVar3 = 0;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  if (0 < *(int *)(iVar2 + 0x38)) {
    iVar7 = 0;
    do {
      (*g_pSvcRdroid->pFread)(param_1,*(int *)(iVar2 + 0x3c) + iVar7,0x2c);
      iVar9 = 0;
      iVar5 = *(int *)(*(int *)(iVar2 + 0x3c) + 0x24 + iVar7);
      if (iVar5 == 0) {
        *(undefined4 *)(*(int *)(iVar2 + 0x3c) + iVar7 + 0x28) = 0;
      }
      else {
        uVar4 = (*g_pSvcRdroid->pAlloc)
                          (iVar5 * 0x38,s_C__grimjedi_Libs_RDroid_Engine_R_004f0f14,
                           DAT_004f0f10 + 0x21);
        *(undefined4 *)(*(int *)(iVar2 + 0x3c) + 0x28 + iVar7) = uVar4;
        iVar5 = *(int *)(iVar2 + 0x3c) + iVar7;
        if (*(int *)(*(int *)(iVar2 + 0x3c) + 0x28 + iVar7) == 0) goto LAB_004c0e2c;
        if (0 < *(int *)(iVar5 + 0x24)) {
          iVar8 = 0;
          do {
            (*g_pSvcRdroid->pFread)(param_1,*(int *)(iVar5 + 0x28) + iVar8,0x38);
            iVar5 = *(int *)(iVar2 + 0x3c) + iVar7;
            iVar9 = iVar9 + 1;
            iVar8 = iVar8 + 0x38;
          } while (iVar9 < *(int *)(iVar5 + 0x24));
        }
      }
      param_2 = param_2 + 1;
      iVar7 = iVar7 + 0x2c;
    } while (param_2 < *(int *)(iVar2 + 0x38));
  }
  (*g_pSvcRdroid->pFclose)(param_1);
  return 1;
}

/* ---- 0x004c0e40  FUN_004c0e40 ---- */
void FUN_004c0e40(int param_1)

{
  if (param_1 != 0) {
    if (DAT_008d3650 != (code *)0x0) {
      (*DAT_008d3650)();
      return;
    }
    FUN_004c0e70(param_1);
    (*g_pSvcRdroid->pFree)(param_1);
  }
  return;
}

/* ---- 0x004c0e70  FUN_004c0e70 ---- */
void FUN_004c0e70(int param_1)

{
  int *piVar1;
  uint uVar2;
  
  if (*(int *)(param_1 + 0x3c) != 0) {
    uVar2 = 0;
    if (*(int *)(param_1 + 0x38) != 0) {
      piVar1 = (int *)(*(int *)(param_1 + 0x3c) + 0x28);
      do {
        if (*piVar1 != 0) {
          (*g_pSvcRdroid->pFree)(*piVar1);
          *piVar1 = 0;
        }
        piVar1 = piVar1 + 0xb;
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(param_1 + 0x38));
    }
    (*g_pSvcRdroid->pFree)(*(undefined4 *)(param_1 + 0x3c));
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  return;
}

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

undefined4 FUN_004c1f40(int *param_1,undefined4 param_2)

{
  PTR_00906c40 = param_1;
  DAT_008d6f14 = param_2;
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
  PTR_00906c3c = (int *)(*(code *)PTR_00906c40[2])(s_MEMORY_workspace_004f14ec,DAT_008d6f14);
  PTR_00906c30 = (int *)(*(code *)PTR_00906c40[2])(s_VIRTHERC_debug_004f14dc,DAT_008d6f14);
  PTR_00906c38 = (int *)(*(code *)PTR_00906c40[2])(s_STREAMER_spooler_004f14c8,DAT_008d6f14);
  PTR_00906c34 = (int *)(*(code *)PTR_00906c40[2])(s_ANIMFRAME_render_004f14b4,DAT_008d6f14);
  DAT_008d6f04 = (*(code *)PTR_00906c40[2])(s_BITMAP_buffers_004f14a4,DAT_008d6f14);
  PTR_008d6f10 = (int *)(*(code *)PTR_00906c40[2])(s_TIMER_clocks_004f1494,DAT_008d6f14);
  DAT_008d6f18 = (*(code *)PTR_00906c40[2])(s_SOUND_lipsync_004f1484,DAT_008d6f14);
  if (PTR_00906c3c == (int *)0x0) {
    (*(code *)PTR_00906c40[8])(s_AnimPlay_Module__Cannot_allocate_004f1450);
    return 0xffffffff;
  }
  if (PTR_00906c38 == (int *)0x0) {
    (*(code *)PTR_00906c40[8])(s_AnimPlay_Module__Cannot_allocate_004f141c);
    return 0xffffffff;
  }
  if (PTR_00906c34 == (int *)0x0) {
    (*(code *)PTR_00906c40[8])(s_AnimPlay_Module__Cannot_allocate_004f13e4);
    return 0xffffffff;
  }
  if (DAT_008d6f04 == 0) {
    (*(code *)PTR_00906c40[8])(s_AnimPlay_Module__Cannot_allocate_004f13b0);
    return 0xffffffff;
  }
  if (PTR_008d6f10 == (int *)0x0) {
    (*(code *)PTR_00906c40[8])(s_AnimPlay_Module__Cannot_allocate_004f137c);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004c2150  FUN_004c2150 ---- */
void FUN_004c2150(void)

{
  (*(code *)PTR_00906c40[3])(PTR_00906c3c);
  (*(code *)PTR_00906c40[3])(PTR_00906c38);
  (*(code *)PTR_00906c40[3])(PTR_00906c34);
  (*(code *)PTR_00906c40[3])(DAT_008d6f04);
  (*(code *)PTR_00906c40[3])(PTR_008d6f10);
  if (PTR_00906c30 != (int *)0x0) {
    (*(code *)PTR_00906c40[3])(PTR_00906c30);
  }
  if (DAT_008d6f18 != 0) {
    (*(code *)PTR_00906c40[3])(DAT_008d6f18);
  }
  return;
}

/* ---- 0x004c21e0  FUN_004c21e0 ---- */
int FUN_004c21e0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                undefined4 param_9,code *param_10,int param_11,undefined4 param_12,
                undefined4 param_13)

{
  unsigned char _frame[0x430] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define iStack_418 (*(int *)(_frame + (0x430 - 0x418)))
  #define local_414 (*(undefined4 *)(_frame + (0x430 - 0x414)))
  #define local_410 (*(undefined4 *)(_frame + (0x430 - 0x410)))
  #define local_40c (*(undefined4 *)(_frame + (0x430 - 0x40c)))
  #define iStack_408 (*(int *)(_frame + (0x430 - 0x408)))
  #define iStack_404 (*(int *)(_frame + (0x430 - 0x404)))
  #define auStack_400 (*(undefined1 (*)[1024])(_frame + (0x430 - 0x400)))
  
  local_40c = 0;
  local_410 = 0;
  if (param_2 == 0) {
    param_2 = 0xf;
  }
  iVar2 = (*(code *)*DAT_008d6f04)(&local_414,param_6,param_7,0xffffffff);
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
        (*(code *)DAT_008d6f04[2])(&local_414);
        return iStack_404;
      }
      iStack_404 = FUN_004c23c0(&iStack_418,param_1,param_2,param_12,param_13,param_3);
      param_11 = iStack_408;
    } while (iStack_404 != 0);
LAB_004c22ac:
    local_40c = 0;
    local_410 = 0;
    iVar2 = FUN_004c25c0(iStack_418,local_414,0,0,0,auStack_400,&local_410,&local_40c,param_8,
                         param_9);
    if (((iVar2 != 0) && (iVar2 != 2)) && (iVar2 != 1)) {
LAB_004c2364:
      if ((iVar2 < 0) || (iVar2 == 4)) goto LAB_004c2376;
      goto LAB_004c22ac;
    }
    if (((param_10 == (code *)0x0) ||
        (iVar1 = *(int *)(iStack_418 + 0x54),
        (*param_10)(iStack_418,local_414,auStack_400,local_410,local_40c), iVar1 != 0)) ||
       (*(int *)(iStack_418 + 0x54) == 0)) {
      FUN_004c2650(iStack_418,local_414,0,param_4,param_5,auStack_400,local_410,local_40c,param_3);
      goto LAB_004c2364;
    }
    iStack_408 = 0;
LAB_004c2376:
    FUN_004c2690(&iStack_418);
    param_11 = iStack_408;
  } while( true );
}
#undef auStack_400
#undef iStack_404
#undef iStack_408
#undef iStack_418
#undef local_40c
#undef local_410
#undef local_414


/* ---- 0x004c23c0  FUN_004c23c0 ---- */
undefined4
FUN_004c23c0(undefined4 *param_1,undefined4 param_2,int param_3,undefined4 param_4,
            undefined4 param_5,int param_6)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(*(code *)*PTR_00906c3c)(0x70,s_C__grimsrc_libs_lecsmush_insane__004f1608,0x140);
  if (piVar1 == (int *)0x0) goto LAB_004c257d;
  iVar2 = (*(code *)*PTR_00906c38)(piVar1 + 0x18,param_4,param_5);
  if (iVar2 == 0) {
    iVar2 = (int)(0x1234dc / (longlong)param_3);
    piVar1[2] = param_6;
    piVar1[6] = 0;
    piVar1[5] = 0;
    piVar1[0x19] = 0;
    piVar1[0x1b] = 0;
    piVar1[0x1a] = 0;
    piVar1[7] = iVar2;
    piVar1[8] = iVar2;
    *param_1 = piVar1;
    iVar2 = ((code *)FUN_004c36b0)(piVar1);
    if (iVar2 == 0) {
      iVar2 = FUN_004c3d30(*param_1,param_2,param_6,0xffffffff,0xffffffff,0);
      if (iVar2 == 0) {
        iVar2 = (*(code *)*PTR_008d6f10)(&LAB_004c2a70,1,2,piVar1);
        *piVar1 = iVar2;
        if (iVar2 == 0) {
          if ((PTR_00906c30 == (int *)0x0) || ((DAT_008d6f20 & 0x20000) == 0)) goto LAB_004c251c;
          (*(code *)PTR_00906c30[3])(s_AnimPlay_Module__Cannot_allocate_004f15ac);
          ((code *)Mem_DumpLog)(*param_1);
        }
        else {
          iVar2 = (*(code *)*PTR_008d6f10)(FUN_004c2a80,piVar1[7],8,piVar1);
          piVar1[1] = iVar2;
          if (iVar2 != 0) {
            piVar1[4] = 0;
            return 0;
          }
          if ((PTR_00906c30 != (int *)0x0) && ((DAT_008d6f20 & 0x20000) != 0)) {
            (*(code *)PTR_00906c30[3])(s_AnimPlay_Module__Cannot_allocate_004f15d8);
          }
          (*(code *)PTR_008d6f10[1])(*piVar1);
          ((code *)Mem_DumpLog)(*param_1);
        }
      }
      else {
        (*(code *)PTR_00906c30[3])(s_AnimPlay_Module__Cannot_open_fil_004f1584,param_2);
LAB_004c251c:
        ((code *)Mem_DumpLog)(*param_1);
      }
    }
    else {
      (*(code *)PTR_00906c30[3])(s_AnimPlay_Module__Cannot_init_Ani_004f1554);
    }
    (*(code *)PTR_00906c38[1])(piVar1 + 0x18);
  }
  else if ((PTR_00906c30 != (int *)0x0) && ((DAT_008d6f20 & 0x20000) != 0)) {
    (*(code *)PTR_00906c30[3])(s_AnimPlay_Module__Cannot_allocate_004f1520);
  }
  (*(code *)PTR_00906c3c[1])(piVar1,s_C__grimsrc_libs_lecsmush_insane__004f1608,0x175);
LAB_004c257d:
  *param_1 = 0;
  return 0xffffffff;
}

/* ---- 0x004c2590  FUN_004c2590 ---- */
int FUN_004c2590(int param_1)

{
  return (*(int *)(param_1 + 0x20) * 1000) / 0x1234dc;
}

/* ---- 0x004c25c0  FUN_004c25c0 ---- */
undefined4
FUN_004c25c0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
            undefined4 param_10)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    iVar1 = (*(code *)PTR_00906c38[7])(*(undefined4 *)(param_1 + 0x60));
    if ((iVar1 < 0x3d) || (DAT_004f1334 < 5)) {
      if ((iVar1 < 0x3c) && (DAT_004f1334 < 0xc)) {
        DAT_004f1334 = DAT_004f1334 + 1;
      }
    }
    else {
      DAT_004f1334 = DAT_004f1334 + -1;
    }
    (*(code *)PTR_00906c38[4])(*(undefined4 *)(param_1 + 0x60),DAT_004f1334 << 0xb);
    uVar2 = FUN_004c27a0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         param_10);
    return uVar2;
  }
  return 0xffffffff;
}

/* ---- 0x004c2650  FUN_004c2650 ---- */
void FUN_004c2650(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                 undefined4 param_9)

{
  (*(code *)PTR_00906c34[3])(param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ---- 0x004c2690  FUN_004c2690 ---- */
void FUN_004c2690(int *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)*param_1;
  (*(code *)PTR_008d6f10[1])(*puVar1);
  (*(code *)PTR_008d6f10[1])(puVar1[1]);
  if ((DAT_008d6f24 != 0) && (DAT_008d6f18 != 0)) {
    (**(code **)(DAT_008d6f18 + 0xc))();
  }
  ((code *)Mem_DumpLog)(puVar1);
  (*(code *)PTR_00906c38[1])(puVar1 + 0x18);
  if (*param_1 != 0) {
    (*(code *)PTR_00906c3c[1])(*param_1,s_C__grimsrc_libs_lecsmush_insane__004f1608,0x1d4);
  }
  *param_1 = 0;
  (*(code *)*PTR_00906c34)();
  return;
}

/* ---- 0x004c2720  FUN_004c2720 ---- */
void FUN_004c2720(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = (undefined4)(0x1234dc / (longlong)param_2);
  param_1[7] = uVar1;
  param_1[8] = uVar1;
  (*(code *)PTR_008d6f10[4])(*param_1,uVar1);
  (*(code *)PTR_008d6f10[4])(param_1[1],param_1[7]);
  return;
}

/* ---- 0x004c2760  FUN_004c2760 ---- */
void FUN_004c2760(undefined4 *param_1)

{
  param_1[6] = 0;
  (*(code *)PTR_008d6f10[4])(*param_1,param_1[8]);
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

/* ---- 0x004c27a0  FUN_004c27a0 ---- */
int FUN_004c27a0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                undefined4 param_9,undefined4 param_10)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  
  if (param_1[0x1a] == 5) {
    iVar3 = FUN_004c36f0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_1[2],
                         param_9,param_10);
    param_1[0x1a] = iVar3;
    if (iVar3 < 0) {
      param_1[4] = 1;
      return iVar3;
    }
  }
  else if (param_1[5] == 0) {
    iVar3 = 6;
  }
  else {
    uVar4 = (*(code *)PTR_00906c38[7])(param_1[0x18]);
    if (param_1[0x1b] == 0) {
      DAT_008d6f1c = 0;
      DAT_008d6f28 = 0;
    }
    DAT_008d6f28 = DAT_008d6f28 + param_1[8];
    Sound_VoiceSampleCount(0);
    iVar3 = _ftol();
    param_1[6] = param_1[6] + -1;
    param_1[5] = 0;
    if ((((iVar3 < 1) && (iVar6 = param_1[0x1a], iVar6 != 2)) && (iVar6 != 3)) && (iVar6 != 4)) {
      if (iVar3 < 0) {
        iVar6 = param_1[7];
        if ((int)param_1[8] < iVar6) {
          param_1[8] = iVar6;
        }
        if (iVar3 == -1) {
          iVar5 = (int)(iVar6 + (iVar6 >> 0x1f & 0xfU)) >> 4;
        }
        else {
          iVar5 = (int)(iVar6 + (iVar6 >> 0x1f & 7U)) >> 3;
        }
        param_1[8] = param_1[8] + iVar5;
        iVar6 = (iVar6 << 2) / 3;
        if (iVar6 < (int)param_1[8]) {
          param_1[8] = iVar6;
        }
      }
    }
    else {
      iVar6 = param_1[7];
      if (iVar6 < (int)param_1[8]) {
        param_1[8] = iVar6;
      }
      if (iVar3 == 1) {
        iVar5 = (int)(iVar6 + (iVar6 >> 0x1f & 0xfU)) >> 4;
      }
      else {
        iVar5 = (int)(iVar6 + (iVar6 >> 0x1f & 7U)) >> 3;
      }
      iVar2 = param_1[8];
      param_1[8] = iVar2 - iVar5;
      if (iVar2 - iVar5 < 1) {
        param_1[8] = 1;
      }
      iVar6 = (int)(iVar6 * 3 + (iVar6 * 3 >> 0x1f & 3U)) >> 2;
      if ((int)param_1[8] < iVar6) {
        param_1[8] = iVar6;
      }
    }
    (*(code *)PTR_008d6f10[4])(*param_1,param_1[8]);
    if (iVar3 < 3) {
      if (iVar3 < 1) {
        param_1[0x19] = 0;
      }
    }
    else {
      param_1[0x19] = 1;
    }
    if ((param_1[0x19] == 0) || ((param_1[2] & 2) != 0)) {
      uVar7 = param_1[2];
    }
    else {
      uVar7 = param_1[2] | 0x8000;
    }
    uVar8 = FUN_004c36f0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar7,
                         param_9,param_10);
    param_1[0x1a] = uVar8;
    if ((PTR_00906c30 != (int *)0x0) && ((DAT_008d6f20 & 0xc0000000) != 0)) {
      piVar1 = PTR_00906c30 + 5;
      uVar8 = (*(code *)PTR_00906c30[7])(4,0x20);
      (*(code *)*piVar1)(0,10,uVar8);
      (*(code *)*PTR_00906c30)(0,10);
      (*(code *)PTR_00906c30[3])(s_Buffer___ld___004f1694,uVar4);
      (*(code *)PTR_00906c30[3])(s_Frame_Delay___ld___ld_target__004f1670,param_1[8],param_1[7]);
      (*(code *)PTR_00906c30[3])(s_Sync_Ticks___ld_004f1658,param_1[6]);
      (*(code *)PTR_00906c30[3])(s_State___d_004f1640,param_1[0x1a]);
    }
    iVar3 = param_1[0x1a];
    if (iVar3 < 0) {
      param_1[4] = 1;
    }
    if (iVar3 == 1) {
      param_1[0x1b] = 1;
      return 1;
    }
  }
  return iVar3;
}

/* ---- 0x004c2a80  FUN_004c2a80 ---- */
void FUN_004c2a80(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0x6c) == 0) {
    return;
  }
  if ((*(byte *)(param_2 + 8) & 1) == 0) {
LAB_004c2abb:
    if (DAT_008d6f24 == 0) goto LAB_004c2adc;
  }
  else if (DAT_008d6f24 == 0) {
    if (6 < *(int *)(param_2 + 0x18)) {
      DAT_008d6f24 = 1;
      if (DAT_008d6f18 != 0) {
        (**(code **)(DAT_008d6f18 + 8))();
      }
      goto LAB_004c2adc;
    }
    goto LAB_004c2abb;
  }
  if ((*(int *)(param_2 + 0x18) < 0) && (DAT_008d6f24 = 0, DAT_008d6f18 != 0)) {
    (**(code **)(DAT_008d6f18 + 0xc))();
  }
LAB_004c2adc:
  if ((*(int *)(param_2 + 0x18) < 0x14) && (DAT_008d6f24 == 0)) {
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
void FUN_004c2b30(undefined4 param_1)

{
  DAT_008d6f20 = param_1;
  return;
}

/* ---- 0x004c2b40  FUN_004c2b40 ---- */
undefined4 FUN_004c2b40(void)

{
  return DAT_008d6f20;
}

/* ---- 0x004c2b50  FUN_004c2b50 ---- */
undefined4 FUN_004c2b50(int *param_1,undefined4 param_2)

{
  PTR_00906c24 = param_1;
  DAT_008d73e0 = param_2;
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
  undefined4 uVar3;
  undefined4 *puVar4;
  
  DAT_00906c20 = (*(code *)PTR_00906c24[2])(s_BITMAP_buffers_004f14a4,DAT_008d73e0);
  PTR_00906c1c = (int *)(*(code *)PTR_00906c24[2])(s_MEMORY_workspace_004f14ec,DAT_008d73e0);
  if (DAT_00906c20 == 0) {
    (*(code *)PTR_00906c24[8])(s_AnimFrame_Module__Cannot_allocat_004f18a8);
    return -1;
  }
  if (PTR_00906c1c == (int *)0x0) {
    (*(code *)PTR_00906c24[8])(s_AnimFrame_Module__Cannot_allocat_004f1874);
    return -1;
  }
  DAT_00906c28 = (*(code *)PTR_00906c24[2])(s_VIRTHERC_debug_004f14dc,DAT_008d73e0);
  DAT_00906c2c = (*(code *)PTR_00906c24[2])(s_VIDEO_display_004f1864,DAT_008d73e0);
  if (DAT_008d77f8 != 0) {
    DAT_008d77f0 = (*(code *)*PTR_00906c1c)
                             (DAT_008d77f8,s_C__grimsrc_libs_lecsmush_insane__004f182c,0xcd);
    iVar1 = (DAT_008d77f0 != 0) - 1;
    if (iVar1 != 0) {
      (*(code *)PTR_00906c24[8])(s_AnimFrame_Module__Can_t_allocate_004f17f0,DAT_008d77f8);
      return iVar1;
    }
  }
  if (DAT_008d77fc != 0) {
    DAT_008d77f4 = (*(code *)*PTR_00906c1c)
                             (DAT_008d77fc,s_C__grimsrc_libs_lecsmush_insane__004f182c,0xce);
    iVar1 = (DAT_008d77f4 != 0) - 1;
    if (iVar1 != 0) {
      (*(code *)PTR_00906c24[8])(s_AnimFrame_Module__Can_t_allocate_004f17b4,DAT_008d77fc);
      return iVar1;
    }
  }
  puVar4 = &DAT_008d70c0;
  for (iVar1 = 100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  DAT_008d77ec = (*(code *)PTR_00906c24[7])(s_FLOBDEC_004f17ac);
  if (100 < DAT_008d77ec) {
    DAT_008d77ec = 100;
  }
  iVar1 = 0;
  if (0 < DAT_008d77ec) {
    puVar4 = &DAT_008d6f30;
    do {
      iVar2 = (*(code *)PTR_00906c24[6])(s_FLOBDEC_004f17ac,iVar1);
      if (iVar2 != 0) {
        iVar2 = (*(code *)PTR_00906c24[2])(s_FLOBDEC_temp_004f179c,iVar2);
        (&DAT_008d70c0)[iVar1] = iVar2;
        uVar3 = (**(code **)(iVar2 + 4))();
        (&DAT_008d7250)[iVar1] = uVar3;
        uVar3 = (**(code **)((&DAT_008d70c0)[iVar1] + 8))();
        *puVar4 = uVar3;
      }
      iVar1 = iVar1 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar1 < DAT_008d77ec);
  }
  return 0;
}

/* ---- 0x004c2dc0  FUN_004c2dc0 ---- */
void FUN_004c2dc0(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  (*(code *)PTR_00906c24[3])(DAT_00906c20);
  (*(code *)PTR_00906c24[3])(PTR_00906c1c);
  if (DAT_00906c2c != 0) {
    (*(code *)PTR_00906c24[3])(DAT_00906c2c);
  }
  if (DAT_00906c28 != 0) {
    (*(code *)PTR_00906c24[3])(DAT_00906c28);
  }
  if (DAT_008d77f0 != 0) {
    (*(code *)PTR_00906c1c[1])(DAT_008d77f0,s_C__grimsrc_libs_lecsmush_insane__004f182c,0x100);
    DAT_008d77f0 = 0;
  }
  if (DAT_008d77f4 != 0) {
    (*(code *)PTR_00906c1c[1])(DAT_008d77f4,s_C__grimsrc_libs_lecsmush_insane__004f182c,0x101);
    DAT_008d77f4 = 0;
  }
  iVar3 = 0;
  if (0 < DAT_008d77ec) {
    piVar2 = &DAT_008d70c0;
    do {
      if (*piVar2 != 0) {
        (*(code *)PTR_00906c24[3])(*piVar2);
      }
      iVar1 = DAT_008d77ec;
      *piVar2 = 0;
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < iVar1);
  }
  DAT_008d77ec = 0;
  return;
}

/* ---- 0x004c2eb0  FUN_004c2eb0 ---- */
void FUN_004c2eb0(void)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < DAT_008d77ec) {
    piVar1 = &DAT_008d70c0;
    do {
      if (*piVar1 != 0) {
        (**(code_std **)(*piVar1 + 0xc))();
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar2 < DAT_008d77ec);
  }
  return;
}

/* ---- 0x004c2ee0  FUN_004c2ee0 ---- */
undefined4 FUN_004c2ee0(undefined1 *param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = DAT_008d77ec;
  while (4 < param_2) {
    iVar5 = 0;
    iVar2 = CONCAT31(CONCAT21(CONCAT11(*param_1,param_1[1]),param_1[2]),param_1[3]);
    bVar1 = param_1[7];
    iVar4 = CONCAT31(CONCAT21(CONCAT11(param_1[4],param_1[5]),param_1[6]),bVar1);
    if (0 < iVar3) {
      do {
        if (((iVar2 != 0) && (iVar2 == (&DAT_008d7250)[iVar5])) && ((&DAT_008d70c0)[iVar5] != 0)) {
          (**(code **)((&DAT_008d70c0)[iVar5] + 0x10))(param_1 + 8,iVar4);
          iVar3 = DAT_008d77ec;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < iVar3);
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
  int iVar10;
  int iVar11;
  uint uVar12;
  uint *puVar13;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  
  puVar7 = param_5;
  bVar6 = false;
  local_10 = 0;
  uVar9 = param_8 & 0x30 | param_8 >> 0xd & 4;
  do {
    if (param_12 < 5) {
      if (DAT_008d7804 != 0) {
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
                                                      DAT_008d7804) + (char)param_10,
                                                (char)(((uVar12 >> 0x10 & 0xff) -
                                                       (uint)PIECE(param_12,2,1)) / DAT_008d7804) +
                                                PIECE(param_12,2,1)),
                                       (char)(((uVar12 >> 8 & 0xff) - (uVar9 >> 8 & 0xff)) /
                                             DAT_008d7804) + (char)param_7),
                              (char)(((uVar12 & 0xff) - (uVar9 & 0xff)) / DAT_008d7804) +
                              (char)uVar9);
          param_5 = (uint *)((int)param_5 + -1);
          puVar13 = puVar13 + 1;
        } while (param_5 != (uint *)0x0);
        DAT_008d7804 = DAT_008d7804 - 1;
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
    if ((DAT_00906c28 != 0) && ((DAT_008d77e8 & 0x80000) != 0)) {
      (**(code **)(DAT_00906c28 + 0xc))
                (s_Parsing_Block___c_c_c_c____ld__004f191c,bVar1,bVar2,bVar3,bVar4,iVar11);
    }
    iVar10 = 0;
    if (0 < DAT_008d77ec) {
      do {
        if (((uVar12 != 0) && (uVar12 == (&DAT_008d7250)[iVar10])) && ((&DAT_008d70c0)[iVar10] != 0)
           ) {
          if (((bVar6) && (DAT_008d77f0 != 0)) && ((*(byte *)(&DAT_008d6f30 + iVar10) & 0x10) != 0))
          {
            if (iVar11 + 8U < DAT_008d77f8) {
              FUN_004c3df0(DAT_008d77f0,param_11,iVar11 + 8U);
              DAT_004f1720 = iVar10;
            }
            else {
              DAT_004f1720 = -1;
            }
            bVar6 = false;
          }
          uVar8 = (**(code **)((&DAT_008d70c0)[iVar10] + 0x14))
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
        iVar10 = iVar10 + 1;
      } while (iVar10 < DAT_008d77ec);
    }
    if (DAT_008d77ec <= iVar10) {
      if (uVar12 < 0x6c6f6165) {
        if (uVar12 == 0x6c6f6164) {
          FUN_004c34d0(param_11 + 8,iVar11);
        }
        else if (uVar12 == 0x66746368) {
          if ((DAT_008d77f0 != 0) && (-1 < DAT_004f1720)) {
            uVar12 = (**(code **)((&DAT_008d70c0)[DAT_004f1720] + 0x14))
                               (param_1,param_2,param_3,param_4,param_5,DAT_008d77f0 + 8,
                                CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(DAT_008d77f0 + 4),
                                                           *(undefined1 *)(DAT_008d77f0 + 5)),
                                                  *(undefined1 *)(DAT_008d77f0 + 6)),
                                         *(undefined1 *)(DAT_008d77f0 + 7)),uVar9,param_9,param_10);
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
          if ((DAT_00906c28 != 0) && ((DAT_008d77e8 & 0x40000) != 0)) {
            (**(code **)(DAT_00906c28 + 0xc))
                      (s_Found_Unknown_Block___c_c_c_c__004f18fc,param_11[4],param_11[5],param_11[6]
                       ,param_11[7]);
          }
          if (((((bVar4 < 0x30) || (0x7a < bVar4)) || (bVar3 < 0x30)) ||
              ((0x7a < bVar3 || (bVar2 < 0x30)))) ||
             ((0x7a < bVar2 || ((bVar1 < 0x30 || (0x7a < bVar1)))))) {
            if ((DAT_00906c28 != 0) && ((DAT_008d77e8 & 0x20000) != 0)) {
              (**(code **)(DAT_00906c28 + 0xc))
                        (s_Bad_Header_Found___c_c_c_c__004f18dc,param_11[4],param_11[5],param_11[6],
                         param_11[7]);
            }
            return local_10 | 0x8000;
          }
        }
      }
      else if (uVar12 == 0x6e70616c) {
        if (*(short *)(param_11 + 0x14) == 0) {
          FUN_004c3df0(param_5 + *(short *)(param_11 + 0x16) * 4,param_11 + 0x1c,
                       (int)*(short *)(param_11 + 0x18) << 2);
          *param_7 = *param_7 | *(uint *)(param_11 + 0x10);
          DAT_008d7804 = 0;
        }
        else {
          FUN_004c3df0(&DAT_008d73e8,param_5,0x400);
          FUN_004c3df0(&DAT_008d73e8 + *(short *)(param_11 + 0x16) * 0x10,param_11 + 0x1c,
                       (int)*(short *)(param_11 + 0x18) << 2);
          DAT_008d7804 = (uint)*(short *)(param_11 + 0x14);
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


/* ---- 0x004c34d0  FUN_004c34d0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004c34d0(short *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (int)param_1[1];
  if (iVar2 == 0) {
    _DAT_004f1724 = 8;
    DAT_008d7800 = 0;
    DAT_008d7808 = -1;
    _DAT_008d780c = (int)*param_1;
  }
  iVar1 = DAT_008d7808;
  if ((iVar2 == DAT_008d7808 + 1) && (iVar1 = iVar2, param_2 + DAT_008d7800 < DAT_008d77fc)) {
    FUN_004c3df0(DAT_008d7800 + DAT_008d77f4,param_1 + 5,param_2 + -10);
    DAT_008d7800 = DAT_008d7800 + -10 + param_2;
  }
  DAT_008d7808 = iVar1;
  return;
}

/* ---- 0x004c3560  FUN_004c3560 ---- */
int FUN_004c3560(int param_1)

{
  if (param_1 < 0) {
    if (DAT_004f1724 - param_1 <= DAT_008d7800) {
      return (DAT_004f1724 + DAT_008d77f4) - param_1;
    }
  }
  else {
    DAT_004f1724 = DAT_004f1724 + param_1;
    if (DAT_004f1724 <= DAT_008d7800) {
      return (DAT_004f1724 + DAT_008d77f4) - param_1;
    }
    DAT_004f1724 = 8;
  }
  return 0;
}

/* ---- 0x004c35c0  FUN_004c35c0 ---- */
void FUN_004c35c0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,byte param_6,byte param_7,uint param_8)

{
  int iVar1;
  
  if ((DAT_00906c2c != 0) && ((param_7 & 2) != 0)) {
    if (param_1 != 0) {
      iVar1 = (**(code **)(DAT_00906c2c + 4))();
      if (*(int *)(iVar1 + 0x20) != 0) goto LAB_004c360c;
    }
    if ((param_8 & 0x2000) == 0) {
      (**(code **)(DAT_00906c2c + 0x18))(0,0,0x100);
    }
  }
LAB_004c360c:
  if ((((param_6 & 1) != 0) && ((param_8 & 0x4000) == 0)) && (DAT_00906c2c != 0)) {
    (**(code **)(DAT_00906c2c + 8))(param_1,param_3,param_4,param_2);
  }
  if ((((param_7 & 1) != 0) && ((param_8 & 0x2000) == 0)) && (DAT_00906c2c != 0)) {
    (**(code **)(DAT_00906c2c + 0x10))(param_5);
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
void FUN_004c3690(undefined4 param_1)

{
  DAT_008d77e8 = param_1;
  return;
}

/* ---- 0x004c36a0  FUN_004c36a0 ---- */
undefined4 FUN_004c36a0(void)

{
  return DAT_008d77e8;
}

/* ---- 0x004c36b0  FUN_004c36b0 ---- */
void FUN_004c36b0(int param_1)

{
  (*(code *)PTR_00906c38[6])(*(undefined4 *)(param_1 + 0x60));
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0x6e756c6c;
  *(undefined4 *)(param_1 + 0x2c) = 1;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  return;
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
      (*(code *)PTR_00906c34[1])(iVar3,*(undefined4 *)(param_1 + 0x30));
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
              iVar3 = (*(code *)PTR_00906c38[3])(*(undefined4 *)(param_1 + 0x60));
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
            iVar3 = (*(code *)PTR_00906c38[3])(*(undefined4 *)(param_1 + 0x60));
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
        iVar3 = (*(code *)PTR_00906c38[3])(*(undefined4 *)(param_1 + 0x60));
        if (iVar3 == 0) {
          if (*(int *)(param_1 + 0x40) == 0) {
            return 5;
          }
          iVar3 = (*(code *)PTR_00906c34[5])(0xfffffff8);
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
      iVar3 = (*(code *)PTR_00906c38[3])(*(undefined4 *)(param_1 + 0x60));
      if ((iVar3 != 0) ||
         ((*(int *)(param_1 + 0x40) != 0 &&
          (iVar3 = (*(code *)PTR_00906c34[5])(0xfffffff8), iVar3 != 0)))) {
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
    iVar2 = (*(code *)PTR_00906c38[5])(*(undefined4 *)(param_1 + 0x60),param_2);
    *(int *)(param_1 + 0x24) = iVar2;
    if ((iVar2 != -1) && (iVar2 == 0)) {
      *(undefined4 *)(param_1 + 0x28) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x38) = 0;
    }
  }
  else {
    uVar1 = (*(code *)PTR_00906c34[5])(param_2);
    *(undefined4 *)(param_1 + 0x24) = uVar1;
    (*(code *)PTR_00906c38[5])(*(undefined4 *)(param_1 + 0x60),0xffffffff);
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
  uVar1 = (*(code *)PTR_00906c34[2])
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
void FUN_004c3c90(int param_1,int param_2,undefined4 param_3,uint *param_4)

{
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0x3c);
  if ((*(uint *)(param_1 + 0x3c) & 0x2000) == 0) {
    FUN_004c3df0(param_3,param_2 + 0x16,0x400);
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
  (*(code *)*PTR_00906c34)();
  *(undefined4 *)(param_1 + 0x54) = 1;
  return;
}

/* ---- 0x004c3d30  FUN_004c3d30 ---- */
undefined4
FUN_004c3d30(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6)

{
  int iVar1;
  
  *(undefined4 *)(param_1 + 0x40) = param_6;
  *(undefined4 *)(param_1 + 0x3c) = param_3;
  iVar1 = (*(code *)PTR_00906c38[2])(*(undefined4 *)(param_1 + 0x60),param_2,8);
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x38) = 1;
  ((code *)_matherr)(*(undefined4 *)(param_1 + 0x60));
  FUN_004c3d90(param_1,param_4,param_5);
  return 0;
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

/* ---- 0x004c3df0  FUN_004c3df0 ---- */
void FUN_004c3df0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  ((code *)FUN_004c3e10)(param_1,param_2,param_3);
  return;
}

/* ---- 0x004c3e10  FUN_004c3e10 ---- */
undefined8 __fastcall
FUN_004c3e10(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4,
            uint param_5)

{
  undefined4 in_EAX;
  uint uVar1;
  
  for (uVar1 = param_5 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)param_3 = *(undefined1 *)param_4;
    param_4 = (undefined4 *)((int)param_4 + 1);
    param_3 = (undefined4 *)((int)param_3 + 1);
  }
  for (param_5 = param_5 >> 2; param_5 != 0; param_5 = param_5 - 1) {
    *param_3 = *param_4;
    param_4 = param_4 + 1;
    param_3 = param_3 + 1;
  }
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004c4650  FUN_004c4650 ---- */
uint FUN_004c4650(int param_1,undefined4 param_2)

{
  uint uVar1;
  
  uVar1 = gz_do_flush(param_1,param_2);
  if (uVar1 == 0) {
    (*(code *)PTR_00906c44[6])(*(undefined4 *)(param_1 + 0x40));
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
  pcVar2 = (char *)malloc(~uVar3 + ~uVar4 + 1);
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
undefined4 FUN_004c4b20(int *param_1,undefined4 param_2)

{
  PTR_008d7818 = param_1;
  DAT_008d7820 = param_2;
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
  PTR_008d7814 = (int *)(*(code *)PTR_008d7818[2])(s_MEMORY_workspace_004f14ec,DAT_008d7820);
  PTR_008d781c = (int *)(*(code *)PTR_008d7818[2])(s_FILIO_io_004f1b00,DAT_008d7820);
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
    if (DAT_008d7824 == 0) {
      uVar2 = param_1[10] + param_1[0xb];
      param_1[10] = uVar2;
      param_1[0xb] = 0;
      if ((uint)param_1[1] <= uVar2) {
        param_1[10] = uVar2 - param_1[2];
      }
      DAT_008d7824 = 1;
    }
    if (param_2 < 0) {
      if (param_1[5] != 0) {
        param_1[0xb] = 0;
        param_1[10] = param_1[7];
      }
      DAT_008d7824 = 0;
      return -1;
    }
    if (param_1[5] != 0) {
      FUN_004c51b0(param_1);
      DAT_008d7824 = 0;
      return 0;
    }
    if (param_1[8] != 0) {
      param_2 = param_2 + param_1[8];
    }
    iVar1 = FUN_004c51e0(param_1,param_2);
    if (iVar1 != 0) {
      DAT_008d7824 = 0;
      param_1[0xb] = param_2;
      iVar1 = (param_2 + param_1[10]) - param_1[1];
      if (0 < iVar1) {
        FUN_004c3df0(param_1[1],*param_1,iVar1);
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
undefined4 FUN_004c5280(int *param_1,undefined4 param_2)

{
  PTR_008d782c = param_1;
  DAT_008d7830 = param_2;
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
  DAT_008d7828 = (*(code *)PTR_008d782c[2])(s_FILE_io_004f1c10,DAT_008d7830);
  if (DAT_008d7828 == 0) {
    (*(code *)PTR_008d782c[8])(s_Directory_Module__Cannot_allocat_004f1bdc);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004c5330  FUN_004c5330 ---- */
void FUN_004c5330(void)

{
  (*(code *)PTR_008d782c[3])(DAT_008d7828);
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
bool FUN_004c5380(int param_1)

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
  #define local_10c (*(undefined1 (*)[268])(_frame + (0x260 - 0x10c)))
  
  iVar3 = 0;
  ((code *)sprintf)(local_10c,&DAT_004e7af8,param_1,param_4);
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
bool FUN_004c54f0(char *param_1,int param_2)

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
    ((code *)sprintf)(&param_1,&DAT_004f1c18,iVar2);
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
undefined4 FUN_004c5790(int *param_1,undefined4 param_2)

{
  PTR_008d7838 = param_1;
  DAT_008d7840 = param_2;
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
  PTR_00906c44 = (int *)(*(code *)PTR_008d7838[2])(s_FILIO_chainto_004f1dcc,DAT_008d7840);
  PTR_008d7834 = (int *)(*(code *)PTR_008d7838[2])(s_MEMORY_buffers_004f1dbc,DAT_008d7840);
  DAT_008d783c = (*(code *)PTR_008d7838[2])(s_VIRTHERC_debug_004f14dc,DAT_008d7840);
  if (PTR_00906c44 == (int *)0x0) {
    (*(code *)PTR_008d7838[8])(s_Zfile_Module__Cannot_allocate_fi_004f1d8c);
    return 0xffffffff;
  }
  if (PTR_008d7834 == (int *)0x0) {
    (*(code *)PTR_008d7838[8])(s_Zfile_Module__Cannot_allocate_me_004f1d5c);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004c5910  FUN_004c5910 ---- */
void FUN_004c5910(void)

{
  (*(code *)PTR_008d7838[3])(PTR_00906c44);
  (*(code *)PTR_008d7838[3])(PTR_008d7834);
  if (DAT_008d783c != 0) {
    (*(code *)PTR_008d7838[3])(DAT_008d783c);
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
  
  piVar1 = (int *)(*(code *)*PTR_008d7834)(0x14,s_C__grimsrc_libs_lecsmush_insane__004f1df4,0xd2);
  iVar6 = 0;
  if (piVar1 == (int *)0x0) {
    if ((DAT_008d783c != 0) && ((DAT_004f1cf0 & 1) != 0)) {
      (**(code **)(DAT_008d783c + 0xc))(s_Zfile_Memory_Alloc_fail_004f1ddc);
      return (int *)0x0;
    }
  }
  else {
    *piVar1 = 0;
    piVar1[1] = 0;
    if (((((*param_2 == 'r') || (*param_2 == 'R')) && (param_2[1] != '+')) &&
        ((param_2[1] == '\0' || (param_2[2] != '+')))) && (0 < DAT_004f1c20)) {
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
            uVar4 = (*(code *)*PTR_00906c44)(param_1,param_2);
            (*(code *)PTR_00906c44[5])(uVar4,0xfffffffc,2);
            (*(code *)PTR_00906c44[2])(uVar4,&iStack_4,4);
            piVar1[2] = iStack_4;
            (*(code *)PTR_00906c44[1])(uVar4);
            return piVar1;
          }
          break;
        }
        iVar6 = iVar6 + 1;
        ppuVar5 = ppuVar5 + 1;
      } while (iVar6 < DAT_004f1c20);
    }
    iVar6 = (*(code *)*PTR_00906c44)(param_1,param_2);
    *piVar1 = iVar6;
    if (iVar6 != 0) {
      return piVar1;
    }
    (*(code *)PTR_008d7834[1])(piVar1,s_C__grimsrc_libs_lecsmush_insane__004f1df4,0x101);
  }
  return (int *)0x0;
}
#undef iStack_4


/* ---- 0x004c5ab0  FUN_004c5ab0 ---- */
void FUN_004c5ab0(int *param_1)

{
  if (*param_1 != 0) {
    if (param_1[1] == 0) {
      (*(code *)PTR_00906c44[1])(*param_1);
    }
    else {
      ((code *)gzclose)();
    }
  }
  if (param_1 != (int *)0x0) {
    (*(code *)PTR_008d7834[1])(param_1,s_C__grimsrc_libs_lecsmush_insane__004f1df4,0x11b);
  }
  return;
}

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
    iVar3 = (*(code *)PTR_00906c44[2])(iVar1,param_2,param_3);
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
    uVar2 = (*(code *)PTR_00906c44[3])(iVar1,param_2,param_3);
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
    iVar1 = (*(code *)PTR_00906c44[4])(*param_1);
  }
  return iVar1;
}

/* ---- 0x004c5c50  FUN_004c5c50 ---- */
void FUN_004c5c50(int *param_1,int param_2,int param_3)

{
  if (*param_1 != 0) {
    if (param_1[1] == 0) {
      (*(code *)PTR_00906c44[5])(*param_1,param_2,param_3);
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
    (*(code *)PTR_00906c44[6])(iVar1);
  }
  return;
}

/* ---- 0x004c5ce0  FUN_004c5ce0 ---- */
undefined4 FUN_004c5ce0(int *param_1,undefined4 param_2)

{
  PTR_008d7844 = param_1;
  DAT_008d784c = param_2;
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
  PTR_008d7848 = (int *)(*(code *)PTR_008d7844[2])(s_FILIO_chainto_004f1dcc,DAT_008d784c);
  if (PTR_008d7848 == (int *)0x0) {
    (*(code *)PTR_008d7844[8])(s_StdFile_Module__Cannot_allocate_f_004f1ea4);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004c5d90  FUN_004c5d90 ---- */
void FUN_004c5d90(void)

{
  (*(code *)PTR_008d7844[3])(PTR_008d7848);
  return;
}

/* ---- 0x004c5db0  FUN_004c5db0 ---- */
void FUN_004c5db0(undefined4 param_1,undefined4 param_2)

{
  (*(code *)*PTR_008d7848)(param_1,param_2);
  return;
}

/* ---- 0x004c5dd0  FUN_004c5dd0 ---- */
void FUN_004c5dd0(undefined4 param_1)

{
  (*(code *)PTR_008d7848[1])(param_1);
  return;
}

/* ---- 0x004c5df0  FUN_004c5df0 ---- */
void FUN_004c5df0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*(code *)PTR_008d7848[2])(param_1,param_2,param_3);
  return;
}

/* ---- 0x004c5e10  FUN_004c5e10 ---- */
void FUN_004c5e10(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*(code *)PTR_008d7848[3])(param_1,param_2,param_3);
  return;
}

/* ---- 0x004c5e30  FUN_004c5e30 ---- */
void FUN_004c5e30(undefined4 param_1)

{
  (*(code *)PTR_008d7848[4])(param_1);
  return;
}

/* ---- 0x004c5e50  FUN_004c5e50 ---- */
void FUN_004c5e50(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*(code *)PTR_008d7848[5])(param_1,param_2,param_3);
  return;
}

/* ---- 0x004c5e70  FUN_004c5e70 ---- */
void FUN_004c5e70(undefined4 param_1)

{
  (*(code *)PTR_008d7848[6])(param_1);
  return;
}

/* ---- 0x004c5e90  FUN_004c5e90 ---- */
undefined4 FUN_004c5e90(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = (*(code *)PTR_008d7848[4])(param_1);
  (*(code *)PTR_008d7848[5])(param_1,0,2);
  uVar2 = (*(code *)PTR_008d7848[4])(param_1);
  (*(code *)PTR_008d7848[5])(param_1,uVar1,0);
  return uVar2;
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

/* ---- 0x004c5f50  FUN_004c5f50 ---- */
bool FUN_004c5f50(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_004c5e90(param_1);
  iVar2 = ((code *)FUN_004c5e30)(param_1);
  return iVar1 <= iVar2;
}

/* ---- 0x004c5f80  FUN_004c5f80 ---- */
void FUN_004c5f80(undefined4 param_1,undefined4 param_2)

{
  unsigned char _frame[0x210] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
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
  (*(code *)PTR_008d7848[3])(param_1,local_1f4,~uVar2 - 1);
  return;
}
#undef local_1f4


/* ---- 0x004c5fe0  FUN_004c5fe0 ---- */
uint FUN_004c5fe0(uint param_1)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_008d7848[2])(param_1,&param_1,1);
  if (iVar1 != 0) {
    return param_1 & 0xff;
  }
  return 0xffffffff;
}

/* ---- 0x004c6010  FUN_004c6010 ---- */
uint FUN_004c6010(undefined4 param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_008d7848[3])(param_1,&param_2,1);
  if (iVar1 != 0) {
    return param_2 & 0xff;
  }
  return 0xffffffff;
}

/* ---- 0x004c6db0  FUN_004c6db0 ---- */
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

/* ---- 0x004c6f10  FUN_004c6f10 ---- */
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

/* ---- 0x004c7040  FUN_004c7040 ---- */
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

/* ---- 0x004c70c0  FUN_004c70c0 ---- */
uint FUN_004c70c0(int *param_1,int param_2)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  uint uVar6;
  byte *pbVar7;
  uint uVar8;
  bool bVar9;
  
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

/* ---- 0x004c73f0  FUN_004c73f0 ---- */
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
  #define local_c (*(char **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
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
  local_c = *(char **)(param_1 + 0x88);
  if (pcVar5 < *(char **)(param_1 + 0x88)) {
    local_c = pcVar5;
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
#undef local_8
#undef local_c


/* ---- 0x004c7570  FUN_004c7570 ---- */
uint FUN_004c7570(int *param_1,int param_2)

{
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

/* ---- 0x004c7b10  FUN_004c7b10 ---- */
void FUN_004c7b10(undefined4 param_1,undefined4 param_2)

{
  free(param_2);
  return;
}

/* ---- 0x004c8990  FUN_004c8990 ---- */
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

/* ---- 0x004c8ba0  FUN_004c8ba0 ---- */
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

/* ---- 0x004c8e90  FUN_004c8e90 ---- */
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

/* ---- 0x004c9090  FUN_004c9090 ---- */
void FUN_004c9090(short *param_1,undefined4 *param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  short *psVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  short *psVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar3 = (int)param_1;
  psVar2 = (short *)*param_2;
  iVar8 = -1;
  iVar7 = *(int *)param_2[2];
  local_4 = ((int *)param_2[2])[3];
  iVar5 = 0;
  local_8 = -1;
  *(undefined4 *)((int)param_1 + 0x1448) = 0;
  *(undefined4 *)((int)param_1 + 0x144c) = 0x23d;
  psVar6 = psVar2;
  if (0 < local_4) {
    do {
      if (*psVar6 == 0) {
        psVar6[1] = 0;
      }
      else {
        iVar8 = *(int *)((int)param_1 + 0x1448) + 1;
        *(int *)((int)param_1 + 0x1448) = iVar8;
        *(int *)((int)param_1 + 0xb54 + iVar8 * 4) = iVar5;
        *(undefined1 *)(iVar5 + 0x1450 + (int)param_1) = 0;
        iVar8 = iVar5;
        local_8 = iVar5;
      }
      iVar5 = iVar5 + 1;
      psVar6 = psVar6 + 2;
    } while (iVar5 < local_4);
  }
  iVar5 = *(int *)((int)param_1 + 0x1448);
  while (iVar5 < 2) {
    if (iVar8 < 2) {
      iVar9 = iVar8 + 1;
      iVar8 = iVar9;
    }
    else {
      iVar9 = 0;
    }
    *(int *)((int)param_1 + 0x1448) = iVar5 + 1;
    *(int *)((int)param_1 + 0xb54 + (iVar5 + 1) * 4) = iVar9;
    psVar2[iVar9 * 2] = 1;
    *(undefined1 *)(iVar9 + 0x1450 + (int)param_1) = 0;
    *(int *)((int)param_1 + 0x16a0) = *(int *)((int)param_1 + 0x16a0) + -1;
    if (iVar7 != 0) {
      *(uint *)((int)param_1 + 0x16a4) =
           *(int *)((int)param_1 + 0x16a4) - (uint)*(ushort *)(iVar7 + 2 + iVar9 * 4);
    }
    local_8 = iVar8;
    iVar5 = *(int *)((int)param_1 + 0x1448);
  }
  param_2[1] = iVar8;
  for (iVar7 = *(int *)((int)param_1 + 0x1448) / 2; 0 < iVar7; iVar7 = iVar7 + -1) {
    FUN_004c92d0(param_1,psVar2,iVar7);
  }
  param_1 = psVar2 + local_4 * 2;
  do {
    iVar7 = *(int *)(iVar3 + 0xb58);
    *(undefined4 *)(iVar3 + 0xb58) = *(undefined4 *)(iVar3 + 0xb54 + *(int *)(iVar3 + 0x1448) * 4);
    *(int *)(iVar3 + 0x1448) = *(int *)(iVar3 + 0x1448) + -1;
    FUN_004c92d0(iVar3,psVar2,1);
    iVar8 = *(int *)(iVar3 + 0xb58);
    iVar5 = *(int *)(iVar3 + 0x144c) + -1;
    *(int *)(iVar3 + 0x144c) = iVar5;
    *(int *)(iVar3 + 0xb54 + iVar5 * 4) = iVar7;
    iVar5 = *(int *)(iVar3 + 0x144c) + -1;
    *(int *)(iVar3 + 0x144c) = iVar5;
    *(int *)(iVar3 + 0xb54 + iVar5 * 4) = iVar8;
    *param_1 = psVar2[iVar8 * 2] + psVar2[iVar7 * 2];
    bVar1 = *(byte *)(iVar7 + 0x1450 + iVar3);
    bVar4 = *(byte *)(iVar8 + 0x1450 + iVar3);
    if (bVar4 <= bVar1) {
      bVar4 = bVar1;
    }
    *(byte *)(local_4 + 0x1450 + iVar3) = bVar4 + 1;
    psVar2[iVar8 * 2 + 1] = (short)local_4;
    psVar2[iVar7 * 2 + 1] = (short)local_4;
    *(int *)(iVar3 + 0xb58) = local_4;
    local_4 = local_4 + 1;
    param_1 = param_1 + 2;
    FUN_004c92d0(iVar3,psVar2,1);
  } while (1 < *(int *)(iVar3 + 0x1448));
  iVar7 = *(int *)(iVar3 + 0x144c) + -1;
  *(int *)(iVar3 + 0x144c) = iVar7;
  *(undefined4 *)(iVar3 + 0xb54 + iVar7 * 4) = *(undefined4 *)(iVar3 + 0xb58);
  FUN_004c9390(iVar3,param_2);
  FUN_004c95c0(psVar2,local_8,iVar3 + 0xb34);
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004c92d0  FUN_004c92d0 ---- */
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

/* ---- 0x004c9390  FUN_004c9390 ---- */
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
  #define local_1c (*(int *)(_frame + (0x30 - 0x1c)))
  #define local_14 (*(int *)(_frame + (0x30 - 0x14)))
  
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
      local_14 = local_14 + -1;
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
      local_1c = local_1c + -2;
    } while (0 < local_1c);
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
#undef local_14
#undef local_1c


/* ---- 0x004c95c0  FUN_004c95c0 ---- */
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


/* ---- 0x004c9640  FUN_004c9640 ---- */
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

/* ---- 0x004c96c0  FUN_004c96c0 ---- */
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


/* ---- 0x004c97b0  FUN_004c97b0 ---- */
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

/* ---- 0x004c9a20  FUN_004c9a20 ---- */
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
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
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
      local_4 = local_4 + -1;
      iVar3 = iVar4;
      uVar5 = uVar6;
    } while (local_4 != 0);
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004c9fa0  FUN_004c9fa0 ---- */
void FUN_004c9fa0(int param_1,int param_2,int param_3)

{
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

/* ---- 0x004ca3f0  FUN_004ca3f0 ---- */
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

/* ---- 0x004ca460  FUN_004ca460 ---- */
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

/* ---- 0x004cba30  FUN_004cba30 ---- */
undefined4 FUN_004cba30(int *param_1,undefined4 param_2)

{
  PTR_008d7864 = param_1;
  DAT_008da4e8 = param_2;
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
  DAT_008da4ec = (*(code *)PTR_008d7864[2])(s_SOUND_004f3434,DAT_008da4e8);
  if (DAT_008da4ec == 0) {
    (*(code *)PTR_008d7864[8])(s_D_WAVE__Cannot_allocate_sound_se_004f340c);
    return -1;
  }
  PTR_008d7850 = (int *)(*(code *)PTR_008d7864[2])(s_MEMORY_004f3404,DAT_008da4e8);
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
  (*(code *)PTR_008d7864[3])(DAT_008da4ec);
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
  DAT_008d7860 = *(undefined4 *)(param_1 + 8);
  return 0;
}

/* ---- 0x004cbc00  FUN_004cbc00 ---- */
undefined4 FUN_004cbc00(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint *puVar6;
  byte *pbVar7;
  uint uVar8;
  uint *in_stack_00000018;
  
  uVar4 = DAT_008d7860;
  uVar8 = 1;
  uVar2 = *in_stack_00000018;
  puVar6 = in_stack_00000018 + 1;
  uVar2 = (uVar2 & 0xff00 | uVar2 << 0x10) << 8 | (uVar2 & 0xff0000 | uVar2 >> 0x10) >> 8;
  if ((int)uVar2 < 0) {
    uVar2 = *puVar6;
    uVar2 = (uVar2 & 0xff00 | uVar2 << 0x10) << 8 | (uVar2 >> 0x10 | uVar2 & 0xff0000) >> 8;
    if (uVar2 != DAT_004f3340) {
      DAT_008d785e = 0;
      DAT_004f3340 = uVar2;
    }
    uVar2 = in_stack_00000018[2];
    uVar2 = (uVar2 & 0xff00 | uVar2 << 0x10) << 8 | (uVar2 >> 0x10 | uVar2 & 0xff0000) >> 8;
    puVar6 = in_stack_00000018 + 3;
  }
  DAT_008d7858 = (byte)*puVar6;
  if ((char)DAT_008d7858 < '\0') {
    DAT_008d7858 = ~DAT_008d7858;
    uVar8 = 2;
  }
  pbVar7 = (byte *)((int)puVar6 + 3);
  DAT_008d785a = CONCAT11((char)*(undefined2 *)((int)puVar6 + 1),
                          (char)((ushort)*(undefined2 *)((int)puVar6 + 1) >> 8));
  if (1 < uVar8) {
    DAT_008d7859 = *pbVar7;
    pbVar7 = (byte *)((int)puVar6 + 6);
    DAT_008d785c = CONCAT11((char)(short)puVar6[1],(char)((ushort)(short)puVar6[1] >> 8));
  }
  if (DAT_008da4ec != (undefined4 *)0x0) {
    if (DAT_008d785e == 0) {
      *PTR_008da4f0 = DAT_004f34b0;
      uVar1 = uVar2 * uVar8 * 2 + 0x2e;
      PTR_008da4f0[1] =
           (uVar1 & 0xff00 | uVar1 * 0x10000) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8;
      *(undefined2 *)(PTR_008da4f0 + 2) = 100;
      *(short *)((int)PTR_008da4f0 + 10) = DAT_008d785e;
      *(undefined2 *)(PTR_008da4f0 + 3) = 100;
      *(undefined1 *)(PTR_008da4f0 + 4) = 0x7f;
      *(undefined1 *)((int)PTR_008da4f0 + 0x11) = 0;
      uVar1 = uVar4 + 0x24;
      *(uint *)((int)PTR_008da4f0 + 0x16) =
           (uVar1 & 0xff00 | uVar1 * 0x10000) << 8 | (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8;
      *(undefined4 *)((int)PTR_008da4f0 + 0x1e) = 0xc000000;
      *(undefined1 *)((int)PTR_008da4f0 + 0x22) = 1;
      *(undefined1 *)((int)PTR_008da4f0 + 0x23) = 8;
      PTR_008da4f0[9] = 0;
      uVar4 = (uVar4 & 0xff00 | uVar4 << 0x10) << 8 | (uVar4 & 0xff0000 | uVar4 >> 0x10) >> 8;
      PTR_008da4f0[10] = uVar4;
      *(undefined1 *)(PTR_008da4f0 + 0xb) = 5;
      *(undefined1 *)((int)PTR_008da4f0 + 0x2d) = 0;
      uVar5 = DAT_004f34a8;
      if (uVar8 != 1) {
        uVar5 = DAT_004f34a0;
      }
      *(undefined4 *)((int)PTR_008da4f0 + 0x2e) = uVar5;
      *(uint *)((int)PTR_008da4f0 + 0x32) = uVar4;
      iVar3 = (int)PTR_008da4f0 + 0x36;
    }
    else {
      *PTR_008da4f0 = DAT_004f34b0;
      uVar4 = uVar2 * uVar8 * 2 + 10;
      PTR_008da4f0[1] =
           (uVar4 & 0xff00 | uVar4 * 0x10000) << 8 | (uVar4 & 0xff0000 | uVar4 >> 0x10) >> 8;
      *(undefined2 *)(PTR_008da4f0 + 2) = 100;
      *(short *)((int)PTR_008da4f0 + 10) = DAT_008d785e;
      *(undefined2 *)(PTR_008da4f0 + 3) = 100;
      *(undefined1 *)(PTR_008da4f0 + 4) = 0x7f;
      *(undefined1 *)((int)PTR_008da4f0 + 0x11) = 0;
      iVar3 = (int)PTR_008da4f0 + 0x12;
    }
    FUN_004cbf50(iVar3,pbVar7,uVar2,uVar8);
    (*(code *)*DAT_008da4ec)(PTR_008da4f0,0xffffffff,0x7f,0,0x40);
    DAT_008d785e = DAT_008d785e + 1;
  }
  if ((DAT_008d785e != 0) && (100000 < DAT_008d7860)) {
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
void FUN_004cbf50(int param_1,undefined1 *param_2,int param_3,uint param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  short sVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  ushort *puVar9;
  byte *pbVar10;
  #define local_28 (*(byte **)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(undefined2 **)(_frame + (0x40 - 0x20)))
  #define local_1c (*(int *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(short **)(_frame + (0x40 - 0x14)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  
  iVar7 = 0;
  if (DAT_008da4f4 == 0) {
    uVar8 = 0;
    local_28 = (byte *)&DAT_008d7868;
    do {
      puVar9 = &DAT_004daa58;
      pbVar10 = local_28;
      do {
        uVar2 = *puVar9;
        uVar3 = 0x20;
        sVar5 = 0;
        do {
          if ((uVar8 & uVar3) != 0) {
            sVar5 = sVar5 + uVar2;
          }
          uVar2 = uVar2 >> 1;
          uVar3 = uVar3 >> 1;
        } while (uVar3 != 0);
        *(short *)pbVar10 = sVar5;
        puVar9 = puVar9 + 1;
        pbVar10 = (byte *)((int)pbVar10 + 0x80);
      } while (puVar9 < &DAT_004dab0a);
      uVar8 = uVar8 + 1;
      local_28 = (byte *)((int)local_28 + 2);
    } while (local_28 < &DAT_008d78e8);
    DAT_008da4f4 = 1;
  }
  local_24 = (uint)CONCAT11(*param_2,param_2[1]);
  local_28 = param_2 + 2;
  local_18 = 0;
  if (param_4 != 0) {
    local_14 = &DAT_008d785a;
    do {
      local_20 = (undefined2 *)(param_1 + -0x8d785a + (int)local_14);
      param_2 = (undefined1 *)(int)(char)(&DAT_008d7858)[local_18];
      uVar8 = (uint)*local_14;
      if (param_3 != 0) {
        local_1c = param_3;
        do {
          bVar1 = (&DAT_004dab10)[(int)param_2];
          iVar7 = iVar7 + (uint)bVar1;
          uVar6 = 1 << (bVar1 - 1 & 0x1f);
          local_c = (uint)(byte)((char)uVar6 - 1);
          uVar3 = (local_24 & 0xffff) >> (0x10U - (char)iVar7 & 0x1f) & (uVar6 | local_c);
          if (7 < iVar7) {
            local_24 = (local_24 & 0xff) << 8 |
                       CONCAT22((short)((uint)local_28 >> 0x10),(ushort)*local_28);
            local_28 = local_28 + 1;
            iVar7 = iVar7 + -8;
          }
          if ((uVar3 & uVar6) == 0) {
            uVar6 = 0;
          }
          else {
            uVar3 = uVar3 ^ uVar6;
          }
          if (uVar3 == local_c) {
            uVar8 = (int)(short)(local_24 << ((byte)iVar7 & 0x1f)) & 0xffffff00U |
                    (ushort)(CONCAT11((undefined1)local_24,*local_28) >> (8 - (byte)iVar7 & 0x1f)) &
                    0xff;
            local_24 = (uint)CONCAT11(*local_28,local_28[1]);
            local_28 = local_28 + 2;
          }
          else {
            uVar4 = (uint)(ushort)(&DAT_008d7868)[uVar3 << (7 - bVar1 & 0x1f) | (int)param_2 << 6];
            if (uVar3 != 0) {
              uVar4 = uVar4 + ((ushort)(&DAT_004daa58)[(int)param_2] >> (bVar1 - 1 & 0x1f));
            }
            if (uVar6 != 0) {
              uVar4 = -uVar4;
            }
            uVar8 = uVar8 + uVar4;
            if ((int)uVar8 < -0x8000) {
              uVar8 = 0xffff8000;
            }
            else if (0x7fff < (int)uVar8) {
              uVar8 = 0x7fff;
            }
          }
          *local_20 = (short)uVar8;
          local_20 = local_20 + param_4;
          param_2 = (undefined1 *)
                    ((int)param_2 +
                    (int)*(char *)(*(int *)(&DAT_004f3348 + (uint)bVar1 * 4) + uVar3));
          if ((int)param_2 < 0) {
            param_2 = (undefined1 *)0x0;
          }
          else if (0x58 < (int)param_2) {
            param_2 = (undefined1 *)0x58;
          }
          local_1c = local_1c + -1;
        } while (local_1c != 0);
      }
      (&DAT_008d7858)[local_18] = PIECE(param_2,0,1);
      *local_14 = (short)uVar8;
      local_18 = local_18 + 1;
      local_14 = local_14 + 1;
    } while (local_18 < param_4);
  }
  return;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_c


/* ---- 0x004cc210  FUN_004cc210 ---- */
undefined4 FUN_004cc210(int *param_1,undefined4 param_2)

{
  PTR_008da500 = param_1;
  DAT_008da504 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_blocky16_flobde_004f3a04,&PTR_FUN_004f34b8);
  (*(code *)*PTR_008da500)(s_FLOBDEC_insane_blocky16_004f39ec,&PTR_FUN_004f34c8);
  return 0;
}

/* ---- 0x004cc250  FUN_004cc250 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004cc250(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)REGISTER0X(0x00000010);
  if (param_1 == 0) {
    return 0;
  }
  do {
    if (param_1 != 1) {
      return 0xffffffff;
    }
    _DAT_008da508 = puVar1[2];
    param_1 = puVar1[3];
    puVar1 = puVar1 + 2;
  } while (param_1 != 0);
  return 0;
}

/* ---- 0x004cc290  FUN_004cc290 ---- */
void FUN_004cc290(void)

{
  (*(code *)PTR_008da500[1])(s_FLOBDEC_insane_blocky16_004f39ec);
  (*(code *)PTR_008da500[1])(s_LECMODULE_insane_blocky16_flobde_004f3a04);
  return;
}

/* ---- 0x004cc2c0  FUN_004cc2c0 ---- */
undefined4 FUN_004cc2c0(void)

{
  PTR_008da4fc = (int *)(*(code *)PTR_008da500[2])(s_BITMAP_clear_004f3aa0,DAT_008da504);
  PTR_008da4f8 = (int *)(*(code *)PTR_008da500[2])(s_MEMORY_workspace_004f14ec,DAT_008da504);
  if (PTR_008da4fc == (int *)0x0) {
    (*(code *)PTR_008da500[8])(s_FlobDec_Blocky16_Module__Cannot_a_004f3a64);
    return 0xffffffff;
  }
  if (PTR_008da4f8 == (int *)0x0) {
    (*(code *)PTR_008da500[8])(s_FlobDec_Blocky16_Module__Cannot_a_004f3a28);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004cc340  FUN_004cc340 ---- */
void FUN_004cc340(void)

{
  thunk_FUN_004cc590();
  (*(code *)PTR_008da500[3])(PTR_008da4fc);
  (*(code *)PTR_008da500[3])(PTR_008da4f8);
  return;
}

/* ---- 0x004cc370  FUN_004cc370 ---- */
char * FUN_004cc370(int param_1)

{
  if (param_1 == 0) {
    return s_Blocky16_Tile_004f3ab0;
  }
  if (param_1 != 1) {
    if (param_1 != 2) {
      return &DAT_004f5a98;
    }
    return s_This_module_decompresses_the_blo_004f3aec;
  }
  return s_Decompresses_a_block16_tile_vide_004f3ac0;
}

/* ---- 0x004cc3a0  FUN_004cc3a0 ---- */
undefined4 FUN_004cc3a0(void)

{
  return 0x426c3136;
}

/* ---- 0x004cc3c0  FUN_004cc3c0 ---- */
undefined4 FUN_004cc3c0(int param_1)

{
  short sVar1;
  uint uVar2;
  
  sVar1 = *(short *)(param_1 + 2);
  uVar2 = (int)*(short *)(param_1 + 4) + 7U & 0xfffffff8;
  if ((((*(short *)(param_1 + 6) != DAT_008da520) || (PTR_008da528 == (int *)0x0)) ||
      ((int)sVar1 != PTR_008da528[1])) || (uVar2 != PTR_008da528[2])) {
    FUN_004cc590();
    FUN_004cc410((int)sVar1,uVar2,(int)*(short *)(param_1 + 6));
  }
  return 0;
}

/* ---- 0x004cc410  FUN_004cc410 ---- */
int FUN_004cc410(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  DAT_008da534 = param_2 * param_1;
  FUN_004cc7d0(4);
  FUN_004cc7d0(8);
  DAT_008da514 = 0;
  DAT_008da518 = 0;
  DAT_008da51c = 0;
  iVar1 = (*(code *)*PTR_008da4fc)(&PTR_008da528,param_1,param_2,param_3);
  if (iVar1 == 0) {
    iVar1 = (*(code *)*PTR_008da4fc)(&DAT_008da52c,param_1,param_2,param_3);
    if (iVar1 == 0) {
      iVar1 = (*(code *)*PTR_008da4fc)(&DAT_008da530,param_1,param_2,param_3);
      if (iVar1 == 0) {
        DAT_008da520 = param_3;
        DAT_00906c74 = *PTR_008da528;
        DAT_0091f080 = *DAT_008da52c;
        DAT_008da50c = *DAT_008da530;
        FUN_004d5e50(DAT_00906c74,0,DAT_008da534 * 2);
        FUN_004d5e50(DAT_0091f080,0,DAT_008da534 * 2);
        FUN_004d5e50(DAT_008da50c,0,DAT_008da534 * 2);
        DAT_008da510 = (*(code *)*PTR_008da4f8)
                                 (0x20000,s_C__grimsrc_libs_lecsmush_insane__004f3bbc,0x13e);
        iVar1 = (DAT_008da510 != 0) - 1;
        if (iVar1 == 0) {
          return 0;
        }
        (*(code *)PTR_008da4fc[2])(&DAT_008da530);
      }
      (*(code *)PTR_008da4fc[2])(&DAT_008da52c);
    }
    (*(code *)PTR_008da4fc[2])(&PTR_008da528);
  }
  return iVar1;
}

/* ---- 0x004cc590  FUN_004cc590 ---- */
void FUN_004cc590(void)

{
  if (PTR_008da528 != (int *)0x0) {
    (*(code *)PTR_008da4fc[2])(&PTR_008da528);
  }
  if (DAT_008da52c != 0) {
    (*(code *)PTR_008da4fc[2])(&DAT_008da52c);
  }
  if (DAT_008da530 != 0) {
    (*(code *)PTR_008da4fc[2])(&DAT_008da530);
  }
  if (DAT_008da510 != 0) {
    (*(code *)PTR_008da4f8[1])(DAT_008da510,s_C__grimsrc_libs_lecsmush_insane__004f3bbc,0x156);
    DAT_008da510 = 0;
  }
  DAT_008da534 = 0;
  return;
}

/* ---- 0x004cc620  FUN_004cc620 ---- */
void FUN_004cc620(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  FUN_004ccd00(param_1,param_2,param_3,param_4,param_5,param_6,param_8);
  return;
}

/* ---- 0x004cc650  FUN_004cc650 ---- */
undefined4
FUN_004cc650(short *param_1,int param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  if (param_2 != 0x100) {
    return 0xffffffff;
  }
  if (param_3 != (int *)0x0) {
    *param_3 = (int)*param_1;
  }
  if (param_4 != (int *)0x0) {
    *param_4 = (int)param_1[2];
  }
  if (param_5 != (int *)0x0) {
    *param_5 = (int)param_1[4];
  }
  if (param_6 != (int *)0x0) {
    *param_6 = (int)param_1[6];
  }
  return 0;
}

/* ---- 0x004cc6a0  FUN_004cc6a0 ---- */
void FUN_004cc6a0(int param_1)

{
  int iVar1;
  short *psVar2;
  short *psVar3;
  short *psVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  short sVar8;
  byte *pbVar9;
  
  if (param_1 != DAT_004f38e4) {
    DAT_004f38e4 = param_1;
    psVar2 = &DAT_004f34e8;
    psVar4 = &DAT_009270a0;
    do {
      psVar3 = psVar2 + 2;
      sVar8 = (short)param_1;
      *psVar4 = psVar2[1] * sVar8 + *psVar2;
      psVar2 = psVar3;
      psVar4 = psVar4 + 1;
    } while ((int)psVar3 < IMG_ADDR(0x004f38e4));
    pbVar9 = &DAT_00906e00;
    pbVar5 = &DAT_0091f100;
    do {
      iVar6 = 0;
      if (*pbVar5 != 0) {
        pbVar7 = pbVar5 + -0x60;
        do {
          iVar1 = iVar6 + -0x20;
          iVar6 = iVar6 + 1;
          *(ushort *)pbVar7 = (ushort)(pbVar5[iVar1] >> 2) * sVar8 + (pbVar5[iVar1] & 3);
          pbVar7 = pbVar7 + 2;
        } while (iVar6 < (int)(uint)*pbVar5);
      }
      iVar6 = 0;
      if (pbVar5[1] != 0) {
        pbVar7 = pbVar5 + -0x40;
        do {
          *(ushort *)pbVar7 =
               (ushort)(pbVar5[iVar6 + -0x10] >> 2) * sVar8 + (pbVar5[iVar6 + -0x10] & 3);
          iVar6 = iVar6 + 1;
          pbVar7 = pbVar7 + 2;
        } while (iVar6 < (int)(uint)pbVar5[1]);
      }
      iVar6 = 0;
      if (*pbVar9 != 0) {
        pbVar7 = pbVar9 + -0x180;
        do {
          iVar1 = iVar6 + -0x80;
          iVar6 = iVar6 + 1;
          *(ushort *)pbVar7 = (ushort)(pbVar9[iVar1] >> 3) * sVar8 + (pbVar9[iVar1] & 7);
          pbVar7 = pbVar7 + 2;
        } while (iVar6 < (int)(uint)*pbVar9);
      }
      iVar6 = 0;
      if (pbVar9[1] != 0) {
        pbVar7 = pbVar9 + -0x100;
        do {
          *(ushort *)pbVar7 =
               (ushort)(pbVar9[iVar6 + -0x40] >> 3) * sVar8 + (pbVar9[iVar6 + -0x40] & 7);
          iVar6 = iVar6 + 1;
          pbVar7 = pbVar7 + 2;
        } while (iVar6 < (int)(uint)pbVar9[1]);
      }
      pbVar5 = pbVar5 + 0x80;
      pbVar9 = pbVar9 + 0x184;
    } while ((int)pbVar5 < IMG_ADDR(0x00927100));
  }
  return;
}

/* ---- 0x004cc7d0  FUN_004cc7d0 ---- */
void FUN_004cc7d0(int param_1)

{
  unsigned char _frame[0x180] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  char cVar14;
  char cVar15;
  int *piVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  bool bVar21;
  #define local_164 (*(int **)(_frame + (0x180 - 0x164)))
  #define local_158 (*(int *)(_frame + (0x180 - 0x158)))
  #define local_150 (*(int *)(_frame + (0x180 - 0x150)))
  #define local_14c (*(int **)(_frame + (0x180 - 0x14c)))
  #define local_148 (*(int **)(_frame + (0x180 - 0x148)))
  #define local_144 (*(int *)(_frame + (0x180 - 0x144)))
  #define local_140 (*(int *)(_frame + (0x180 - 0x140)))
  #define local_138 (*(int *)(_frame + (0x180 - 0x138)))
  #define local_130 (*(int *)(_frame + (0x180 - 0x130)))
  #define local_124 (*(int *)(_frame + (0x180 - 0x124)))
  #define auStack_100 (*(undefined4 (*)[15])(_frame + (0x180 - 0x100)))
  #define local_c4 (*(int (*)[49])(_frame + (0x180 - 0xc4)))
  
  if (param_1 == 8) {
    local_164 = (int *)&DAT_004f3968;
    local_148 = (int *)&DAT_004f39a8;
    puVar2 = &DAT_00906e00;
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + 0x184;
    } while ((int)puVar2 < IMG_ADDR(0x0091f200));
    puVar2 = &DAT_00906e01;
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + 0x184;
    } while ((int)puVar2 < IMG_ADDR(0x0091f201));
  }
  if (param_1 == 4) {
    local_164 = &DAT_004f38e8;
    local_148 = &DAT_004f3928;
    puVar2 = &DAT_0091f100;
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + 0x80;
    } while ((int)puVar2 < IMG_ADDR(0x00927100));
    puVar2 = &DAT_0091f101;
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + 0x80;
    } while ((int)puVar2 < IMG_ADDR(0x00927101));
  }
  iVar3 = param_1 * param_1;
  iVar19 = (int)local_164 - (int)local_148;
  local_138 = 0;
  local_158 = 0;
  local_150 = 0;
  local_14c = local_148;
  do {
    iVar4 = local_158 + 0x800;
    iVar10 = local_150 + 0x1840;
    local_124 = 0x10;
    piVar16 = local_164;
    do {
      iVar9 = *local_14c;
      if (iVar9 == 0) {
        cVar14 = '\0';
      }
      else if (iVar9 == param_1 + -1) {
        cVar14 = '\x01';
      }
      else if (*(int *)(iVar19 + (int)local_14c) == 0) {
        cVar14 = '\x02';
      }
      else {
        cVar14 = (*(int *)(iVar19 + (int)local_14c) != param_1 + -1) + '\x03';
      }
      iVar1 = *(int *)(((int)local_148 - (int)local_164) + (int)piVar16);
      if (iVar1 == 0) {
        cVar15 = '\0';
      }
      else if (iVar1 == param_1 + -1) {
        cVar15 = '\x01';
      }
      else if (*piVar16 == 0) {
        cVar15 = '\x02';
      }
      else {
        cVar15 = (*piVar16 != param_1 + -1) + '\x03';
      }
      if (iVar3 != 0) {
        puVar8 = auStack_100 + iVar3 + -1;
        iVar5 = iVar3;
        do {
          *puVar8 = 0;
          iVar5 = iVar5 + -1;
          puVar8 = puVar8 + -1;
        } while (iVar5 != 0);
      }
      iVar5 = *piVar16;
      if (*(int *)(local_138 + (int)local_164) - iVar5 < 0) {
        iVar17 = *(int *)(iVar19 + (int)local_14c);
        iVar6 = iVar5 - iVar17;
      }
      else {
        iVar17 = *(int *)(iVar19 + (int)local_14c);
        iVar6 = iVar17 - iVar5;
      }
      iVar13 = iVar9 - iVar1;
      iVar18 = iVar13;
      if (iVar13 < 0) {
        iVar18 = iVar1 - iVar9;
      }
      if (iVar18 < iVar6) {
        iVar13 = iVar17 - iVar5;
        if (iVar13 < 0) {
          iVar13 = iVar5 - iVar17;
        }
      }
      else if (iVar13 < 0) {
        iVar13 = iVar1 - iVar9;
      }
      iVar6 = iVar13 + 1;
      if (0 < iVar6) {
        local_140 = 0;
        local_144 = 0;
        iVar20 = iVar1 * iVar6;
        iVar18 = iVar6 * iVar5;
        local_130 = iVar6;
        do {
          iVar7 = iVar9;
          iVar11 = iVar17;
          if (1 < iVar6) {
            iVar7 = ((iVar20 - iVar1) + local_140 + (iVar13 >> 1)) / iVar13;
            iVar11 = ((iVar18 - iVar5) + local_144 + (iVar13 >> 1)) / iVar13;
          }
          puVar8 = auStack_100 + iVar7 * param_1 + iVar11;
          *puVar8 = 1;
          if ((((cVar14 == '\x02') && (cVar15 == '\x03')) ||
              ((cVar15 == '\x02' && (cVar14 == '\x03')))) ||
             ((cVar14 == '\0' && (cVar15 != '\x01')))) {
LAB_004ccab2:
            if (-1 < iVar7) {
              iVar7 = iVar7 + 1;
              do {
                *puVar8 = 1;
                puVar8 = puVar8 + -param_1;
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
            }
          }
          else if (cVar15 == '\0') {
            if (cVar14 != '\x01') goto LAB_004ccab2;
LAB_004ccae4:
            if (cVar15 == '\0') goto LAB_004ccae8;
LAB_004ccaf1:
            if (iVar7 < param_1) {
              iVar7 = param_1 - iVar7;
              do {
                *puVar8 = 1;
                puVar8 = puVar8 + param_1;
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
            }
          }
          else {
            if (cVar14 == '\x01') goto LAB_004ccae4;
LAB_004ccae8:
            if (cVar15 == '\x01') {
              if (cVar14 != '\0') goto LAB_004ccaf1;
LAB_004ccb1e:
              if (cVar15 != '\x01') goto LAB_004ccb23;
            }
            else {
              if (cVar14 == '\0') goto LAB_004ccb1e;
LAB_004ccb23:
              if (((cVar15 != '\0') || (cVar14 != '\x01')) &&
                 ((cVar14 != '\x03' || (cVar15 == '\x02')))) {
                if (cVar15 == '\x03') {
                  if (cVar14 != '\x02') goto LAB_004ccb40;
LAB_004ccb67:
                  if (cVar15 == '\x03') goto LAB_004ccb6c;
                }
                else {
                  if (cVar14 == '\x02') goto LAB_004ccb67;
LAB_004ccb6c:
                  if ((cVar15 != '\x02') || (cVar14 == '\x03')) goto LAB_004ccb89;
                }
                if (-1 < iVar11) {
                  iVar11 = iVar11 + 1;
                  do {
                    *puVar8 = 1;
                    puVar8 = puVar8 + -1;
                    iVar11 = iVar11 + -1;
                  } while (iVar11 != 0);
                }
                goto LAB_004ccb89;
              }
            }
LAB_004ccb40:
            if (iVar11 < param_1) {
              for (iVar11 = param_1 - iVar11; iVar11 != 0; iVar11 = iVar11 + -1) {
                *puVar8 = 1;
                puVar8 = puVar8 + 1;
              }
            }
          }
LAB_004ccb89:
          local_144 = local_144 + iVar17;
          local_140 = local_140 + iVar9;
          iVar18 = iVar18 - iVar5;
          iVar20 = iVar20 - iVar1;
          local_130 = local_130 + -1;
        } while (local_130 != 0);
      }
      if (param_1 == 8) {
        iVar9 = 0x3f;
        piVar12 = (int *)REGISTER0X(0x00000010);
        do {
          piVar12 = piVar12 + -1;
          if (*piVar12 == 0) {
            (&DAT_00906dc0)[local_150 + (uint)(byte)(&DAT_00906e01)[local_150]] = (char)iVar9;
            (&DAT_00906e01)[local_150] = (&DAT_00906e01)[local_150] + '\x01';
          }
          else {
            (&DAT_00906d80)[local_150 + (uint)(byte)(&DAT_00906e00)[local_150]] = (char)iVar9;
            (&DAT_00906e00)[local_150] = (&DAT_00906e00)[local_150] + '\x01';
          }
          bVar21 = iVar9 != 0;
          iVar9 = iVar9 + -1;
        } while (bVar21);
      }
      else if (param_1 == 4) {
        piVar12 = local_c4;
        iVar9 = 0xf;
        do {
          if (*piVar12 == 0) {
            (&DAT_0091f0f0)[local_158 + (uint)(byte)(&DAT_0091f101)[local_158]] = (char)iVar9;
            (&DAT_0091f101)[local_158] = (&DAT_0091f101)[local_158] + '\x01';
          }
          else {
            (&DAT_0091f0e0)[local_158 + (uint)(byte)(&DAT_0091f100)[local_158]] = (char)iVar9;
            (&DAT_0091f100)[local_158] = (&DAT_0091f100)[local_158] + '\x01';
          }
          piVar12 = piVar12 + -1;
          bVar21 = iVar9 != 0;
          iVar9 = iVar9 + -1;
        } while (bVar21);
      }
      local_150 = local_150 + 0x184;
      local_158 = local_158 + 0x80;
      piVar16 = piVar16 + 1;
      local_124 = local_124 + -1;
    } while (local_124 != 0);
    local_138 = local_138 + 4;
    local_14c = local_14c + 1;
    local_158 = iVar4;
    local_150 = iVar10;
    if (0x3f < local_138) {
      return;
    }
  } while( true );
}
#undef auStack_100
#undef local_124
#undef local_130
#undef local_138
#undef local_140
#undef local_144
#undef local_148
#undef local_14c
#undef local_150
#undef local_158
#undef local_164
#undef local_c4


/* ---- 0x004ccd00  FUN_004ccd00 ---- */
undefined4
FUN_004ccd00(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,int param_6,byte param_7)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  
  uVar9 = (uint)*(short *)(param_6 + 8);
  iVar8 = (int)*(short *)(param_6 + 0xc);
  pbVar5 = (byte *)(param_6 + 0x230);
  if (((PTR_008da528 == (int *)0x0) || (uVar9 != PTR_008da528[1])) ||
     ((iVar8 + 7U & 0xfffffff8) != PTR_008da528[2])) {
    FUN_004cc590();
    iVar3 = (int)*(short *)(param_6 + 0x228);
    if (*(short *)(param_6 + 0x228) == 0) {
      iVar3 = 8;
    }
    FUN_004cc410(uVar9,iVar8 + 7U & 0xfffffff8,iVar3);
  }
  iVar3 = (int)DAT_0091f080 - (int)DAT_008da50c;
  iVar4 = (int)DAT_00906c74 - (int)DAT_008da50c;
  if (param_1 != 0) {
    FUN_004cd1e0(param_1);
  }
  if (*(short *)(param_6 + 0x10) == 0) {
    FUN_004cc6a0(uVar9);
    FUN_004cec40(DAT_00906c74,PTR_008da528,PTR_008da528[1] * PTR_008da528[2],param_6 + 0x20);
    FUN_004cec40(DAT_0091f080,PTR_008da528,PTR_008da528[1] * PTR_008da528[2],param_6 + 0x20);
    DAT_004f39e8 = -1;
  }
  DAT_008d6f1c = DAT_008d6f1c + 1;
  switch(*(undefined1 *)(param_6 + 0x12)) {
  case 0:
    goto LAB_004ccf61;
  case 1:
    FUN_004cd300(DAT_008da50c,pbVar5,uVar9,iVar8);
    DAT_008da538 = DAT_008da50c;
    break;
  case 2:
    if (((param_7 & 4) != 0) && (*(char *)(param_6 + 0x13) == '\0')) {
      DAT_004f39e8 = (int)*(short *)(param_6 + 0x10);
      return 0;
    }
    if ((int)*(short *)(param_6 + 0x10) == DAT_004f39e8 + 1) {
      ((code *)FUN_004cd550)(DAT_008da50c,pbVar5,iVar3 >> 1,iVar4 >> 1,uVar9,&DAT_009270a0,param_6 + 0x18,
                   iVar8,uVar9 * 9 - (uVar9 & 0xfffffff8),&DAT_0091f0a0,&DAT_00906c80,param_6 + 0x28
                  );
      DAT_008da538 = DAT_008da50c;
    }
    break;
  case 3:
    pbVar5 = DAT_0091f080;
    if (((param_7 & 4) != 0) && (*(char *)(param_6 + 0x13) == '\0')) {
      DAT_004f39e8 = (int)*(short *)(param_6 + 0x10);
      return 0;
    }
    goto LAB_004ccf61;
  case 4:
    pbVar5 = DAT_00906c74;
    if (((param_7 & 4) != 0) && (*(char *)(param_6 + 0x13) == '\0')) {
      DAT_004f39e8 = (int)*(short *)(param_6 + 0x10);
      return 0;
    }
LAB_004ccf61:
    FUN_004c3df0(DAT_008da50c,pbVar5,uVar9 * iVar8 * 2);
LAB_004ccf67:
    DAT_008da538 = DAT_008da50c;
    break;
  case 5:
    FUN_004d5e70(DAT_008da50c,pbVar5,*(undefined4 *)(param_6 + 0x24));
    goto LAB_004ccf67;
  case 6:
    iVar8 = uVar9 * iVar8;
    pbVar6 = DAT_008da50c;
    DAT_008da538 = DAT_008da50c;
    if (iVar8 != 0) {
      do {
        bVar1 = *pbVar5;
        pbVar5 = pbVar5 + 1;
        iVar8 = iVar8 + -1;
        *(undefined2 *)pbVar6 = *(undefined2 *)(param_6 + 0x28 + (uint)bVar1 * 2);
        pbVar6 = pbVar6 + 2;
      } while (iVar8 != 0);
      DAT_008da538 = DAT_008da50c;
    }
    break;
  case 7:
    FUN_004cd450(DAT_008da50c,pbVar5,uVar9,iVar8,param_6 + 0x28);
    DAT_008da538 = DAT_008da50c;
    break;
  case 8:
    FUN_004d5eb0(pbVar5);
    pbVar5 = DAT_008da50c;
    for (iVar8 = uVar9 * iVar8; iVar8 != 0; iVar8 = iVar8 + -1) {
      uVar9 = ((code *)FUN_004d5ed0)();
      *(undefined2 *)pbVar5 = *(undefined2 *)(param_6 + 0x28 + (uVar9 & 0xff) * 2);
      pbVar5 = pbVar5 + 2;
    }
    Mem_DumpLog();
    DAT_008da538 = DAT_008da50c;
  }
  if ((DAT_008da538 != (byte *)0x0) && (param_1 != 0)) {
    uVar7 = DAT_008da510;
    if ((DAT_008da514 == 0) && (DAT_008da518 == 0)) {
      uVar7 = 0;
    }
    if (DAT_008da508 == (code *)0x0) {
      piVar10 = PTR_008da528;
      if (((DAT_008da538 == (byte *)*PTR_008da528) ||
          (piVar10 = DAT_008da52c, DAT_008da538 == (byte *)*DAT_008da52c)) ||
         (piVar10 = DAT_008da530, DAT_008da538 == (byte *)*DAT_008da530)) {
        FUN_004cea30(param_1,param_2,param_3,param_4,piVar10,param_5,uVar7);
      }
      param_5 = 1;
    }
    else if (DAT_008da538 == (byte *)*PTR_008da528) {
      param_5 = (*DAT_008da508)(param_1,param_2,param_3,param_4,PTR_008da528,param_5,uVar7);
    }
    else if (DAT_008da538 == (byte *)*DAT_008da52c) {
      param_5 = (*DAT_008da508)(param_1,param_2,param_3,param_4,DAT_008da52c,param_5,uVar7);
    }
    else if (DAT_008da538 == (byte *)*DAT_008da530) {
      param_5 = (*DAT_008da508)(param_1,param_2,param_3,param_4,DAT_008da530,param_5,uVar7);
    }
  }
  pbVar2 = DAT_0091f080;
  pbVar6 = DAT_00906c74;
  pbVar5 = DAT_008da50c;
  if ((int)*(short *)(param_6 + 0x10) == DAT_004f39e8 + 1) {
    if (*(char *)(param_6 + 0x13) == '\x01') {
      DAT_0091f080 = DAT_008da50c;
      DAT_008da50c = pbVar2;
      DAT_004f39e8 = (int)*(short *)(param_6 + 0x10);
      return param_5;
    }
    if (*(char *)(param_6 + 0x13) == '\x02') {
      DAT_00906c74 = DAT_0091f080;
      DAT_008da50c = pbVar6;
      DAT_0091f080 = pbVar5;
    }
  }
  DAT_004f39e8 = (int)*(short *)(param_6 + 0x10);
  return param_5;
}

/* ---- 0x004cd1e0  FUN_004cd1e0 ---- */
void FUN_004cd1e0(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  
  if (((((DAT_008da510 != 0) && (*(int *)(param_1 + 0xc) == 2)) &&
       ((*(int *)(param_1 + 0x20) == 1 || (*(int *)(param_1 + 0x20) == 2)))) &&
      (((*(int *)(param_1 + 0x30) != PTR_008da528[0xc] ||
        (*(int *)(param_1 + 0x38) != PTR_008da528[0xe])) ||
       (*(int *)(param_1 + 0x34) != PTR_008da528[0xd])))) &&
     (((*(int *)(param_1 + 0x30) != DAT_008da514 || (*(int *)(param_1 + 0x38) != DAT_008da51c)) ||
      (*(int *)(param_1 + 0x34) != DAT_008da518)))) {
    DAT_008da514 = *(int *)(param_1 + 0x30);
    DAT_008da518 = *(int *)(param_1 + 0x34);
    DAT_008da51c = *(int *)(param_1 + 0x38);
    for (local_8 = 0; local_8 < 0x10000; local_8 = local_8 + 1) {
      *(undefined2 *)(DAT_008da510 + local_8 * 2) = (undefined2)local_8;
    }
    FUN_004cedc0(DAT_008da510,PTR_008da528,0x10000,0,DAT_008da510,param_1,0);
  }
  return;
}
#undef local_8


/* ---- 0x004cd300  FUN_004cd300 ---- */
void FUN_004cd300(int param_1,ushort *param_2,int param_3,int param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int iVar2;
  undefined2 uVar3;
  uint uVar4;
  uint uVar5;
  ushort uVar6;
  undefined2 *puVar7;
  uint *puVar8;
  undefined4 *puVar9;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  
  iVar2 = param_3 * 2;
  if (0 < param_4) {
    local_10 = param_4 + 1U >> 1;
    puVar9 = (undefined4 *)(param_1 + iVar2);
    do {
      puVar8 = puVar9 + 1;
      uVar6 = *param_2;
      param_2 = param_2 + 1;
      *puVar9 = CONCAT22(uVar6,uVar6);
      if (0 < param_3 + -2) {
        uVar5 = param_3 - 1U >> 1;
        do {
          uVar1 = *param_2;
          param_2 = param_2 + 1;
          uVar4 = FUN_004cd3f0(uVar6,uVar1);
          *puVar8 = uVar4 & 0xffff | (uint)uVar1 << 0x10;
          puVar8 = puVar8 + 1;
          uVar5 = uVar5 - 1;
          uVar6 = uVar1;
        } while (uVar5 != 0);
      }
      puVar9 = (undefined4 *)((int)puVar8 + iVar2);
      local_10 = local_10 - 1;
    } while (local_10 != 0);
  }
  FUN_004c3df0(param_1,(undefined4 *)(param_1 + iVar2),iVar2);
  puVar7 = (undefined2 *)(param_1 + param_3 * 4);
  if (param_4 != 2 && -1 < param_4 + -2) {
    uVar5 = param_4 - 1U >> 1;
    iVar2 = param_3;
    do {
      for (; iVar2 != 0; iVar2 = iVar2 + -1) {
        uVar3 = FUN_004cd3f0(puVar7[param_3],puVar7[-param_3]);
        *puVar7 = uVar3;
        puVar7 = puVar7 + 1;
      }
      puVar7 = puVar7 + param_3;
      uVar5 = uVar5 - 1;
      iVar2 = param_3;
    } while (uVar5 != 0);
  }
  return;
}
#undef local_10


/* ---- 0x004cd3f0  FUN_004cd3f0 ---- */
int FUN_004cd3f0(uint param_1,uint param_2)

{
  return (int)((param_1 & 0xf800) + (param_2 & 0xf800) & 0x1f000 |
               (param_1 & 0x7e0) + (param_2 & 0x7e0) & 0xfc0 | (param_2 & 0x1f) + (param_1 & 0x1f))
         >> 1;
}

/* ---- 0x004cd450  FUN_004cd450 ---- */
void FUN_004cd450(int param_1,byte *param_2,int param_3,int param_4,int param_5)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  ushort uVar2;
  int iVar3;
  undefined2 uVar4;
  uint uVar5;
  uint uVar6;
  ushort uVar7;
  undefined2 *puVar8;
  uint *puVar9;
  undefined4 *puVar10;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  
  iVar3 = param_3 * 2;
  if (0 < param_4) {
    local_10 = param_4 + 1U >> 1;
    puVar10 = (undefined4 *)(param_1 + iVar3);
    do {
      bVar1 = *param_2;
      param_2 = param_2 + 1;
      puVar9 = puVar10 + 1;
      uVar7 = *(ushort *)(param_5 + (uint)bVar1 * 2);
      *puVar10 = CONCAT22(uVar7,uVar7);
      if (0 < param_3 + -2) {
        uVar6 = param_3 - 1U >> 1;
        do {
          bVar1 = *param_2;
          param_2 = param_2 + 1;
          uVar2 = *(ushort *)(param_5 + (uint)bVar1 * 2);
          uVar5 = FUN_004cd3f0(uVar7,uVar2);
          *puVar9 = uVar5 & 0xffff | (uint)uVar2 << 0x10;
          puVar9 = puVar9 + 1;
          uVar6 = uVar6 - 1;
          uVar7 = uVar2;
        } while (uVar6 != 0);
      }
      puVar10 = (undefined4 *)((int)puVar9 + iVar3);
      local_10 = local_10 - 1;
    } while (local_10 != 0);
  }
  FUN_004c3df0(param_1,(undefined4 *)(param_1 + iVar3),iVar3);
  puVar8 = (undefined2 *)(param_1 + param_3 * 4);
  if (param_4 != 2 && -1 < param_4 + -2) {
    uVar6 = param_4 - 1U >> 1;
    iVar3 = param_3;
    do {
      for (; iVar3 != 0; iVar3 = iVar3 + -1) {
        uVar4 = FUN_004cd3f0(puVar8[param_3],puVar8[-param_3]);
        *puVar8 = uVar4;
        puVar8 = puVar8 + 1;
      }
      puVar8 = puVar8 + param_3;
      uVar6 = uVar6 - 1;
      iVar3 = param_3;
    } while (uVar6 != 0);
  }
  return;
}
#undef local_10


/* ---- 0x004cd550  FUN_004cd550 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall
FUN_004cd550(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5
            ,int param_6,int param_7,undefined4 param_8,int param_9,int param_10,undefined4 param_11
            ,undefined4 param_12,undefined4 param_13,undefined4 param_14)

{
  undefined4 in_EAX;
  
  _DAT_00906c58 = param_5 * 2;
  DAT_00906c68 = param_6 * 2;
  _DAT_00906c60 = param_7;
  DAT_00906c4c = param_8;
  DAT_00906c54 = param_9 + -0x1f2;
  _DAT_00906c70 = param_12;
  _DAT_00906c50 = param_13;
  DAT_00906c6c = param_14;
  DAT_00906c5c = (char)(param_10 + 7U >> 3);
  DAT_00906c64 = (char)(param_7 + 7U >> 3);
  DAT_00906c48 = param_7 * 0xe;
  do {
    DAT_00906c5d = DAT_00906c64;
    do {
      FUN_004cd610();
      DAT_00906c5d = DAT_00906c5d + -1;
    } while (DAT_00906c5d != '\0');
    DAT_00906c5c = DAT_00906c5c + -1;
  } while (DAT_00906c5c != '\0');
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004cd610  FUN_004cd610 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004cd610(void)

{
  byte bVar1;
  short sVar2;
  bool bVar3;
  undefined2 uVar4;
  ushort *puVar5;
  int iVar6;
  undefined4 uVar7;
  ushort *puVar8;
  int unaff_EBP;
  uint uVar9;
  uint uVar10;
  byte *unaff_ESI;
  undefined4 *puVar11;
  undefined4 *unaff_EDI;
  undefined4 *puVar12;
  
  iVar6 = DAT_00906c68;
  bVar1 = *unaff_ESI;
  if (bVar1 < 0xf6) {
    if (bVar1 == 0xf5) {
      sVar2 = *(short *)(unaff_ESI + 1);
    }
    else {
      sVar2 = *(short *)(DAT_00906c4c + (uint)bVar1 * 2);
    }
    iVar6 = sVar2 * 2 + _DAT_00906c58;
    puVar11 = unaff_EDI + unaff_EBP;
    uVar7 = *(undefined4 *)((int)unaff_EDI + iVar6);
    *puVar11 = *(undefined4 *)((int)puVar11 + iVar6);
    *unaff_EDI = uVar7;
    uVar7 = *(undefined4 *)((int)unaff_EDI + iVar6 + 4);
    puVar11[1] = *(undefined4 *)((int)puVar11 + iVar6 + 4);
    unaff_EDI[1] = uVar7;
    uVar7 = *(undefined4 *)((int)unaff_EDI + iVar6 + 8);
    puVar11[2] = *(undefined4 *)((int)puVar11 + iVar6 + 8);
    unaff_EDI[2] = uVar7;
    uVar7 = *(undefined4 *)((int)unaff_EDI + iVar6 + 0xc);
    puVar11[3] = *(undefined4 *)((int)puVar11 + iVar6 + 0xc);
    unaff_EDI[3] = uVar7;
    puVar11 = (undefined4 *)((int)puVar11 + unaff_EBP);
    puVar12 = (undefined4 *)((int)unaff_EDI + unaff_EBP);
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6);
    *puVar11 = *(undefined4 *)((int)puVar11 + iVar6);
    *puVar12 = uVar7;
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 4);
    puVar11[1] = *(undefined4 *)((int)puVar11 + iVar6 + 4);
    puVar12[1] = uVar7;
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 8);
    puVar11[2] = *(undefined4 *)((int)puVar11 + iVar6 + 8);
    puVar12[2] = uVar7;
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 0xc);
    puVar11[3] = *(undefined4 *)((int)puVar11 + iVar6 + 0xc);
    puVar12[3] = uVar7;
    puVar11 = (undefined4 *)((int)puVar11 + unaff_EBP);
    puVar12 = (undefined4 *)((int)puVar12 + unaff_EBP);
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6);
    *puVar11 = *(undefined4 *)((int)puVar11 + iVar6);
    *puVar12 = uVar7;
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 4);
    puVar11[1] = *(undefined4 *)((int)puVar11 + iVar6 + 4);
    puVar12[1] = uVar7;
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 8);
    puVar11[2] = *(undefined4 *)((int)puVar11 + iVar6 + 8);
    puVar12[2] = uVar7;
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 0xc);
    puVar11[3] = *(undefined4 *)((int)puVar11 + iVar6 + 0xc);
    puVar12[3] = uVar7;
    puVar11 = (undefined4 *)((int)puVar11 + unaff_EBP);
    puVar12 = (undefined4 *)((int)puVar12 + unaff_EBP);
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6);
    *puVar11 = *(undefined4 *)((int)puVar11 + iVar6);
    *puVar12 = uVar7;
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 4);
    puVar11[1] = *(undefined4 *)((int)puVar11 + iVar6 + 4);
    puVar12[1] = uVar7;
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 8);
    puVar11[2] = *(undefined4 *)((int)puVar11 + iVar6 + 8);
    puVar12[2] = uVar7;
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 0xc);
    puVar11[3] = *(undefined4 *)((int)puVar11 + iVar6 + 0xc);
    puVar12[3] = uVar7;
    return;
  }
  if (bVar1 == 0xff) {
    FUN_004cd9b0();
    FUN_004cd9b0();
    FUN_004cd9b0();
    FUN_004cd9b0();
    return;
  }
  if (bVar1 < 0xfe) {
    if (bVar1 == 0xfd) {
      uVar4 = (undefined2)*(undefined4 *)(DAT_00906c6c + (uint)unaff_ESI[1] * 2);
      uVar7 = CONCAT22(uVar4,uVar4);
    }
    else {
      if (bVar1 < 0xf9) {
        if (bVar1 == 0xf8) {
          uVar7 = *(undefined4 *)(unaff_ESI + 2);
          bVar1 = unaff_ESI[1];
        }
        else {
          if (bVar1 != 0xf7) {
            puVar11 = unaff_EDI + unaff_EBP;
            uVar7 = *(undefined4 *)((int)unaff_EDI + DAT_00906c68);
            *puVar11 = *(undefined4 *)((int)puVar11 + DAT_00906c68);
            *unaff_EDI = uVar7;
            uVar7 = *(undefined4 *)((int)unaff_EDI + iVar6 + 4);
            puVar11[1] = *(undefined4 *)((int)puVar11 + iVar6 + 4);
            unaff_EDI[1] = uVar7;
            uVar7 = *(undefined4 *)((int)unaff_EDI + iVar6 + 8);
            puVar11[2] = *(undefined4 *)((int)puVar11 + iVar6 + 8);
            unaff_EDI[2] = uVar7;
            uVar7 = *(undefined4 *)((int)unaff_EDI + iVar6 + 0xc);
            puVar11[3] = *(undefined4 *)((int)puVar11 + iVar6 + 0xc);
            unaff_EDI[3] = uVar7;
            puVar11 = (undefined4 *)((int)puVar11 + unaff_EBP);
            puVar12 = (undefined4 *)((int)unaff_EDI + unaff_EBP);
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6);
            *puVar11 = *(undefined4 *)((int)puVar11 + iVar6);
            *puVar12 = uVar7;
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 4);
            puVar11[1] = *(undefined4 *)((int)puVar11 + iVar6 + 4);
            puVar12[1] = uVar7;
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 8);
            puVar11[2] = *(undefined4 *)((int)puVar11 + iVar6 + 8);
            puVar12[2] = uVar7;
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 0xc);
            puVar11[3] = *(undefined4 *)((int)puVar11 + iVar6 + 0xc);
            puVar12[3] = uVar7;
            puVar11 = (undefined4 *)((int)puVar11 + unaff_EBP);
            puVar12 = (undefined4 *)((int)puVar12 + unaff_EBP);
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6);
            *puVar11 = *(undefined4 *)((int)puVar11 + iVar6);
            *puVar12 = uVar7;
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 4);
            puVar11[1] = *(undefined4 *)((int)puVar11 + iVar6 + 4);
            puVar12[1] = uVar7;
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 8);
            puVar11[2] = *(undefined4 *)((int)puVar11 + iVar6 + 8);
            puVar12[2] = uVar7;
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 0xc);
            puVar11[3] = *(undefined4 *)((int)puVar11 + iVar6 + 0xc);
            puVar12[3] = uVar7;
            puVar11 = (undefined4 *)((int)puVar11 + unaff_EBP);
            puVar12 = (undefined4 *)((int)puVar12 + unaff_EBP);
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6);
            *puVar11 = *(undefined4 *)((int)puVar11 + iVar6);
            *puVar12 = uVar7;
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 4);
            puVar11[1] = *(undefined4 *)((int)puVar11 + iVar6 + 4);
            puVar12[1] = uVar7;
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 8);
            puVar11[2] = *(undefined4 *)((int)puVar11 + iVar6 + 8);
            puVar12[2] = uVar7;
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 0xc);
            puVar11[3] = *(undefined4 *)((int)puVar11 + iVar6 + 0xc);
            puVar12[3] = uVar7;
            return;
          }
          uVar7 = CONCAT22(*(undefined2 *)
                            (DAT_00906c6c +
                            (uint)(byte)((ushort)*(undefined2 *)(unaff_ESI + 2) >> 8) * 2),
                           *(undefined2 *)
                            (DAT_00906c6c + (uint)(byte)*(undefined2 *)(unaff_ESI + 2) * 2));
          bVar1 = unaff_ESI[1];
        }
        puVar5 = (ushort *)((uint)bVar1 * 0x184 + _DAT_00906c50);
        puVar8 = puVar5;
        uVar10 = (uint)(byte)puVar5[0xc0];
        do {
          *(short *)((int)unaff_EDI + (uint)*puVar8 * 2) = (short)uVar7;
          puVar8 = puVar8 + 1;
          uVar9 = uVar10 - 1;
          bVar3 = 0 < (int)uVar10;
          uVar10 = uVar9;
        } while (uVar9 != 0 && bVar3);
        puVar8 = puVar5 + 0x40;
        uVar10 = (uint)*(byte *)((int)puVar5 + 0x181);
        do {
          *(short *)((int)unaff_EDI + (uint)*puVar8 * 2) = (short)((uint)uVar7 >> 0x10);
          puVar8 = puVar8 + 1;
          uVar9 = uVar10 - 1;
          bVar3 = 0 < (int)uVar10;
          uVar10 = uVar9;
        } while (uVar9 != 0 && bVar3);
        return;
      }
      uVar4 = (undefined2)*(undefined4 *)(DAT_00906c54 + (uint)bVar1 * 2);
      uVar7 = CONCAT22(uVar4,uVar4);
    }
  }
  else {
    uVar7 = CONCAT22((short)*(undefined4 *)(unaff_ESI + 1),(short)*(undefined4 *)(unaff_ESI + 1));
  }
  puVar11 = unaff_EDI + unaff_EBP;
  *puVar11 = uVar7;
  *unaff_EDI = uVar7;
  puVar11[1] = uVar7;
  unaff_EDI[1] = uVar7;
  puVar11[2] = uVar7;
  unaff_EDI[2] = uVar7;
  puVar11[3] = uVar7;
  unaff_EDI[3] = uVar7;
  puVar11 = (undefined4 *)((int)puVar11 + unaff_EBP);
  puVar12 = (undefined4 *)((int)unaff_EDI + unaff_EBP);
  *puVar11 = uVar7;
  *puVar12 = uVar7;
  puVar11[1] = uVar7;
  puVar12[1] = uVar7;
  puVar11[2] = uVar7;
  puVar12[2] = uVar7;
  puVar11[3] = uVar7;
  puVar12[3] = uVar7;
  puVar11 = (undefined4 *)((int)puVar11 + unaff_EBP);
  puVar12 = (undefined4 *)((int)puVar12 + unaff_EBP);
  *puVar11 = uVar7;
  *puVar12 = uVar7;
  puVar11[1] = uVar7;
  puVar12[1] = uVar7;
  puVar11[2] = uVar7;
  puVar12[2] = uVar7;
  puVar11[3] = uVar7;
  puVar12[3] = uVar7;
  puVar11 = (undefined4 *)((int)puVar11 + unaff_EBP);
  puVar12 = (undefined4 *)((int)puVar12 + unaff_EBP);
  *puVar11 = uVar7;
  *puVar12 = uVar7;
  puVar11[1] = uVar7;
  puVar12[1] = uVar7;
  puVar11[2] = uVar7;
  puVar12[2] = uVar7;
  puVar11[3] = uVar7;
  puVar12[3] = uVar7;
  return;
}

/* ---- 0x004cd9b0  FUN_004cd9b0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004cd9b0(void)

{
  byte bVar1;
  short sVar2;
  bool bVar3;
  undefined2 uVar4;
  ushort *puVar5;
  int iVar6;
  undefined4 uVar7;
  ushort *puVar8;
  int unaff_EBP;
  uint uVar9;
  uint uVar10;
  byte *unaff_ESI;
  undefined4 *puVar11;
  undefined4 *unaff_EDI;
  undefined4 *puVar12;
  
  iVar6 = DAT_00906c68;
  bVar1 = *unaff_ESI;
  if (bVar1 < 0xf6) {
    if (bVar1 == 0xf5) {
      sVar2 = *(short *)(unaff_ESI + 1);
    }
    else {
      sVar2 = *(short *)(DAT_00906c4c + (uint)bVar1 * 2);
    }
    iVar6 = sVar2 * 2 + _DAT_00906c58;
    puVar11 = (undefined4 *)((int)unaff_EDI + unaff_EBP * 2);
    uVar7 = *(undefined4 *)((int)unaff_EDI + iVar6);
    *puVar11 = *(undefined4 *)((int)puVar11 + iVar6);
    *unaff_EDI = uVar7;
    uVar7 = *(undefined4 *)((int)unaff_EDI + iVar6 + 4);
    puVar11[1] = *(undefined4 *)((int)puVar11 + iVar6 + 4);
    unaff_EDI[1] = uVar7;
    puVar11 = (undefined4 *)((int)puVar11 + unaff_EBP);
    puVar12 = (undefined4 *)((int)unaff_EDI + unaff_EBP);
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6);
    *puVar11 = *(undefined4 *)((int)puVar11 + iVar6);
    *puVar12 = uVar7;
    uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 4);
    puVar11[1] = *(undefined4 *)((int)puVar11 + iVar6 + 4);
    puVar12[1] = uVar7;
    return;
  }
  if (bVar1 == 0xff) {
    FUN_004cdb80();
    FUN_004cdb80();
    FUN_004cdb80();
    FUN_004cdb80();
    return;
  }
  if (bVar1 < 0xfe) {
    if (bVar1 == 0xfd) {
      uVar4 = (undefined2)*(undefined4 *)(DAT_00906c6c + (uint)unaff_ESI[1] * 2);
      uVar7 = CONCAT22(uVar4,uVar4);
    }
    else {
      if (bVar1 < 0xf9) {
        if (bVar1 == 0xf8) {
          uVar7 = *(undefined4 *)(unaff_ESI + 2);
          bVar1 = unaff_ESI[1];
        }
        else {
          if (bVar1 != 0xf7) {
            puVar11 = (undefined4 *)((int)unaff_EDI + unaff_EBP * 2);
            uVar7 = *(undefined4 *)((int)unaff_EDI + DAT_00906c68);
            *puVar11 = *(undefined4 *)((int)puVar11 + DAT_00906c68);
            *unaff_EDI = uVar7;
            uVar7 = *(undefined4 *)((int)unaff_EDI + iVar6 + 4);
            puVar11[1] = *(undefined4 *)((int)puVar11 + iVar6 + 4);
            unaff_EDI[1] = uVar7;
            puVar11 = (undefined4 *)((int)puVar11 + unaff_EBP);
            puVar12 = (undefined4 *)((int)unaff_EDI + unaff_EBP);
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6);
            *puVar11 = *(undefined4 *)((int)puVar11 + iVar6);
            *puVar12 = uVar7;
            uVar7 = *(undefined4 *)((int)puVar12 + iVar6 + 4);
            puVar11[1] = *(undefined4 *)((int)puVar11 + iVar6 + 4);
            puVar12[1] = uVar7;
            return;
          }
          uVar7 = CONCAT22(*(undefined2 *)
                            (DAT_00906c6c +
                            (uint)(byte)((ushort)*(undefined2 *)(unaff_ESI + 2) >> 8) * 2),
                           *(undefined2 *)
                            (DAT_00906c6c + (uint)(byte)*(undefined2 *)(unaff_ESI + 2) * 2));
          bVar1 = unaff_ESI[1];
        }
        puVar5 = (ushort *)((uint)bVar1 * 0x80 + _DAT_00906c70);
        puVar8 = puVar5;
        uVar10 = (uint)(byte)puVar5[0x30];
        do {
          *(short *)((int)unaff_EDI + (uint)*puVar8 * 2) = (short)uVar7;
          puVar8 = puVar8 + 1;
          uVar9 = uVar10 - 1;
          bVar3 = 0 < (int)uVar10;
          uVar10 = uVar9;
        } while (uVar9 != 0 && bVar3);
        puVar8 = puVar5 + 0x10;
        uVar10 = (uint)*(byte *)((int)puVar5 + 0x61);
        do {
          *(short *)((int)unaff_EDI + (uint)*puVar8 * 2) = (short)((uint)uVar7 >> 0x10);
          puVar8 = puVar8 + 1;
          uVar9 = uVar10 - 1;
          bVar3 = 0 < (int)uVar10;
          uVar10 = uVar9;
        } while (uVar9 != 0 && bVar3);
        return;
      }
      uVar4 = (undefined2)*(undefined4 *)(DAT_00906c54 + (uint)bVar1 * 2);
      uVar7 = CONCAT22(uVar4,uVar4);
    }
  }
  else {
    uVar7 = CONCAT22((short)*(undefined4 *)(unaff_ESI + 1),(short)*(undefined4 *)(unaff_ESI + 1));
  }
  *unaff_EDI = uVar7;
  unaff_EDI[1] = uVar7;
  puVar11 = (undefined4 *)((int)unaff_EDI + unaff_EBP);
  *puVar11 = uVar7;
  *(undefined4 *)((int)unaff_EDI + unaff_EBP + 4) = uVar7;
  *(undefined4 *)((int)puVar11 + unaff_EBP) = uVar7;
  *(undefined4 *)((int)unaff_EDI + unaff_EBP * 2 + 4) = uVar7;
  *(undefined4 *)((int)puVar11 + unaff_EBP * 2) = uVar7;
  *(undefined4 *)((int)unaff_EDI + unaff_EBP * 3 + 4) = uVar7;
  return;
}

/* ---- 0x004cdb80  FUN_004cdb80 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004cdb80(void)

{
  byte bVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined2 uVar5;
  int iVar6;
  undefined4 uVar7;
  int unaff_EBP;
  byte *unaff_ESI;
  undefined4 *unaff_EDI;
  
  iVar4 = DAT_00906c6c;
  iVar6 = DAT_00906c68;
  bVar1 = *unaff_ESI;
  if (bVar1 < 0xf6) {
    if (bVar1 == 0xf5) {
      sVar2 = *(short *)(unaff_ESI + 1);
    }
    else {
      sVar2 = *(short *)(DAT_00906c4c + (uint)bVar1 * 2);
    }
    iVar6 = sVar2 * 2 + _DAT_00906c58;
    *unaff_EDI = *(undefined4 *)((int)unaff_EDI + iVar6);
    *(undefined4 *)((int)unaff_EDI + unaff_EBP) =
         *(undefined4 *)((int)unaff_EDI + unaff_EBP + iVar6);
    return;
  }
  if ((bVar1 == 0xff) || (bVar1 == 0xf8)) {
    *unaff_EDI = *(undefined4 *)(unaff_ESI + 1);
    *(undefined4 *)((int)unaff_EDI + unaff_EBP) = *(undefined4 *)(unaff_ESI + 5);
    return;
  }
  if (0xfd < bVar1) {
    uVar7 = CONCAT22((short)*(undefined4 *)(unaff_ESI + 1),(short)*(undefined4 *)(unaff_ESI + 1));
    *unaff_EDI = uVar7;
    *(undefined4 *)((int)unaff_EDI + unaff_EBP) = uVar7;
    return;
  }
  if (bVar1 != 0xfd) {
    if (0xf8 < bVar1) {
      uVar5 = (undefined2)*(undefined4 *)(DAT_00906c54 + (uint)bVar1 * 2);
      uVar7 = CONCAT22(uVar5,uVar5);
      *unaff_EDI = uVar7;
      *(undefined4 *)((int)unaff_EDI + unaff_EBP) = uVar7;
      return;
    }
    if (bVar1 == 0xf7) {
      uVar3 = *(uint *)(unaff_ESI + 1);
      *(short *)unaff_EDI = (short)*(undefined4 *)(DAT_00906c6c + (uVar3 & 0xff) * 2);
      *(short *)((int)unaff_EDI + 2) = (short)*(undefined4 *)(iVar4 + (uVar3 >> 8 & 0xff) * 2);
      *(short *)((int)unaff_EDI + unaff_EBP) =
           (short)*(undefined4 *)(iVar4 + (uVar3 >> 0x10 & 0xff) * 2);
      *(short *)((int)unaff_EDI + unaff_EBP + 2) =
           (short)*(undefined4 *)(iVar4 + (uVar3 >> 0x18) * 2);
      return;
    }
    if (0xf5 < bVar1) {
      *unaff_EDI = *(undefined4 *)((int)unaff_EDI + DAT_00906c68);
      *(undefined4 *)((int)unaff_EDI + unaff_EBP) =
           *(undefined4 *)((int)unaff_EDI + unaff_EBP + iVar6);
    }
    return;
  }
  uVar5 = (undefined2)*(undefined4 *)(DAT_00906c6c + (uint)unaff_ESI[1] * 2);
  uVar7 = CONCAT22(uVar5,uVar5);
  *unaff_EDI = uVar7;
  *(undefined4 *)((int)unaff_EDI + unaff_EBP) = uVar7;
  return;
}

/* ---- 0x004cdc90  FUN_004cdc90 ---- */
undefined4 FUN_004cdc90(int *param_1,undefined4 param_2)

{
  PTR_008da5cc = param_1;
  DAT_008da85c = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_timer_004f3c40,&PTR_FUN_004f3bf8);
  (*(code *)*PTR_008da5cc)(s_TIMER_insane_004f3c30,&PTR_FUN_004f3c08);
  DAT_008da544 = 300;
  return 0;
}

/* ---- 0x004cdce0  FUN_004cdce0 ---- */
void FUN_004cdce0(void)

{
  (*(code *)PTR_008da5cc[1])(s_TIMER_insane_004f3c30);
  (*(code *)PTR_008da5cc[1])(s_LECMODULE_insane_timer_004f3c40);
  return;
}

/* ---- 0x004cdd10  FUN_004cdd10 ---- */
undefined4 FUN_004cdd10(void)

{
  undefined4 uVar1;
  
  DAT_008da540 = (*(code *)PTR_008da5cc[2])(s_MEMORY_workspace_004f14ec,DAT_008da85c);
  if (DAT_008da540 == 0) {
    (*(code *)PTR_008da5cc[8])(s_Timer_Module__Cannot_allocate_me_004f3c58);
    return 0xffffffff;
  }
  uVar1 = ((code *)FUN_004cdd80)((int)(0x1234dc / (longlong)DAT_008da544),0x10000);
  return uVar1;
}

/* ---- 0x004cdd60  FUN_004cdd60 ---- */
void FUN_004cdd60(void)

{
  (*(code *)PTR_008da5cc[3])(DAT_008da540);
  FUN_004cde80();
  return;
}

/* ---- 0x004cdd80  FUN_004cdd80 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004cdd80(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *puVar2;
  bool bVar3;
  #define local_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  iVar1 = DAT_008da874 + 1;
  bVar3 = DAT_008da874 == 0;
  DAT_008da874 = iVar1;
  if (bVar3) {
    puVar2 = &DAT_008da5f8;
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + 8;
    } while ((int)puVar2 < IMG_ADDR(0x008da858));
    DAT_008da860 = 0x4dae;
    DAT_008da858 = CreateThread(0,0,((unsigned)(uintptr_t)Mixer_TimerThread),0,0,(int)local_4);
    SetThreadPriority(DAT_008da858,2);
    _DAT_004f3c2c = 0xffffffff;
  }
  return 0;
}
#undef local_4


/* ---- 0x004cde80  FUN_004cde80 ---- */
void FUN_004cde80(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int unaff_ESI;
  #define local_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  DAT_008da874 = DAT_008da874 + -1;
  if (DAT_008da874 == 0) {
    iVar1 = GetExitCodeThread(DAT_008da858,local_4);
    while ((iVar1 != 0 && (unaff_ESI == 0x103))) {
      OutputDebugStringA(IMG_ADDR(0x004f3c88));
      iVar1 = GetExitCodeThread(DAT_008da858,&STACK0X(0xfffffff4));
    }
    CloseHandle(DAT_008da858);
  }
  return;
}
#undef local_4


/* ---- 0x004cdef0  FUN_004cdef0 ---- */
void FUN_004cdef0(void)

{
  DAT_008da878 = DAT_008da878 + 1;
  return;
}

/* ---- 0x004cdf00  FUN_004cdf00 ---- */
void FUN_004cdf00(void)

{
  DAT_008da878 = DAT_008da878 + -1;
  return;
}

/* ---- 0x004cdf10  FUN_004cdf10 ---- */
int FUN_004cdf10(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = 1;
  piVar2 = &DAT_008da5f8;
  do {
    if (*piVar2 == 0) {
      iVar3 = iVar1 * 0x20;
      *(undefined4 *)(iVar3 + IMG_ADDR(0x008da5e8)) = 0;
      *(undefined4 *)(&DAT_008da5ec + iVar3) = 0;
      *(undefined4 *)(iVar3 + IMG_ADDR(0x008da5e4)) = param_4;
      *(undefined4 *)(iVar3 + IMG_ADDR(0x008da5e0)) = param_3;
      *(undefined4 *)(&DAT_008da5dc + iVar3) = param_2;
      *(undefined4 *)(&DAT_008da5d8 + iVar3) = param_1;
      *(undefined4 *)(iVar3 + IMG_ADDR(0x008da5f0)) = 0;
      *(undefined4 *)(iVar3 + IMG_ADDR(0x008da5f4)) = 0;
      return iVar1;
    }
    piVar2 = piVar2 + 8;
    iVar1 = iVar1 + 1;
  } while ((int)piVar2 < IMG_ADDR(0x008da858));
  return 0;
}

/* ---- 0x004cdf80  FUN_004cdf80 ---- */
void FUN_004cdf80(int param_1)

{
  if ((0 < param_1) && (param_1 < 0x14)) {
    *(undefined4 *)(&DAT_008da5d8 + param_1 * 0x20) = 0;
  }
  return;
}

/* ---- 0x004cdfa0  FUN_004cdfa0 ---- */
void FUN_004cdfa0(int param_1,undefined4 param_2)

{
  if ((0 < param_1) && (param_1 < 0x14)) {
    *(undefined4 *)(&DAT_008da5dc + param_1 * 0x20) = param_2;
    *(undefined4 *)(&DAT_008da5ec + param_1 * 0x20) = 0;
  }
  return;
}

/* ---- 0x004cdfd0  FUN_004cdfd0 ---- */
void FUN_004cdfd0(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_008da5c8;
  param_1 = param_1 + DAT_008da5c8;
  do {
    if (param_1 <= DAT_008da5c8) {
      return;
    }
    FUN_004ce000();
  } while (iVar1 <= DAT_008da5c8);
  return;
}

/* ---- 0x004ce000  FUN_004ce000 ---- */
undefined4 FUN_004ce000(void)

{
  return DAT_008da5c8;
}

/* ---- 0x004ce010  FUN_004ce010 ---- */
undefined4 FUN_004ce010(void)

{
  return DAT_008da860;
}

/* ---- 0x004ce020  FUN_004ce020 ---- */
void FUN_004ce020(int param_1)

{
  int *piVar1;
  
  piVar1 = &DAT_008da60c;
  do {
    if ((piVar1[-5] != 0) && ((*(byte *)(piVar1 + -3) & 8) != 0)) {
      if (0 < param_1) {
        *piVar1 = *piVar1 + (param_1 - piVar1[2]);
      }
      piVar1[2] = 0;
    }
    piVar1 = piVar1 + 8;
  } while ((int)piVar1 < IMG_ADDR(0x008da86c));
  return;
}

/* ---- 0x004ce2e0  FUN_004ce2e0 ---- */
undefined4 FUN_004ce2e0(int *param_1,undefined4 param_2)

{
  PTR_008da894 = param_1;
  DAT_008da898 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_bitmap_004f3cec,&PTR_FUN_004f3cc0);
  (*(code *)*PTR_008da894)(s_BITMAP_insane_004f3cdc,&PTR_FUN_004f3cd0);
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
  PTR_008da890 = (int *)(*(code *)PTR_008da894[2])(s_MEMORY_workspace_004f14ec,DAT_008da898);
  DAT_008da89c = (*(code *)PTR_008da894[2])(s_VIDEO_getbm_004f3d34,DAT_008da898);
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
  if (DAT_008da89c != 0) {
    (*(code *)PTR_008da894[3])(DAT_008da89c);
  }
  return;
}

/* ---- 0x004ce3e0  FUN_004ce3e0 ---- */
undefined4 FUN_004ce3e0(int *param_1,int param_2,int param_3,int param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  switch(param_4) {
  case 1:
    local_4 = 0x100;
  case 0:
    iVar2 = 1;
    break;
  case 2:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
    iVar2 = 2;
    break;
  case 4:
  case 9:
    iVar2 = 3;
    break;
  case 6:
  case 0xb:
  case 0xc:
    iVar2 = 4;
    break;
  case -1:
    if (DAT_008da89c == 0) {
      uVar3 = 0xbe;
      goto LAB_004ce7b5;
    }
    iVar2 = (**(code **)(DAT_008da89c + 4))();
    iVar2 = *(int *)(iVar2 + 0xc);
    break;
  default:
    uVar3 = 0xc4;
LAB_004ce7b5:
    ((code *)FUN_004d5f70)(s__s__line__s__Type__d_not_support_004f3d40,
                 s_C__grimsrc_libs_lecsmush_insane__004f3d64,uVar3,param_4);
    return 0xffffffff;
  }
  iVar1 = (*(code *)*PTR_008da890)
                    (iVar2 * param_3 * param_2 + 0x5c + local_4 * 4,
                     s_C__grimsrc_libs_lecsmush_insane__004f3d64,200);
  if (iVar1 == 0) {
    return 0xffffff9b;
  }
  *param_1 = iVar1 + 8;
  *(int *)(iVar1 + 8) = iVar1 + 0x5c;
  *(int *)(*param_1 + 4) = param_2;
  *(int *)(*param_1 + 0x14) = iVar2 * param_2;
  *(int *)(*param_1 + 8) = param_3;
  *(int *)(*param_1 + 0xc) = iVar2;
  *(undefined4 *)(*param_1 + 0x1c) = 0;
  *(undefined4 *)(*param_1 + 0x18) = 0;
                    /* WARNING: Could not recover jumptable at 0x004ce4a6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar3 = (**(code **)(&DAT_004ce808 + (param_4 + 1) * 4))();
  return uVar3;
}
#undef local_4


/* ---- 0x004ce840  FUN_004ce840 ---- */
undefined4
FUN_004ce840(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6,
            undefined4 *param_7)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *puVar2;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
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
    *(int *)(*param_1 + 0x28) = local_4;
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
    FUN_004cf520(local_14,param_1,1,0,&param_2);
    FUN_004cec40(uVar2,param_1,iVar1 * iVar3,local_14);
  }
  return;
}
#undef local_14


/* ---- 0x004cea30  FUN_004cea30 ---- */
void FUN_004cea30(int *param_1,int *param_2,int param_3,int param_4,int *param_5,undefined4 param_6,
                 undefined1 *param_7)

{
  unsigned char _frame[0x430] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  #define local_420 (*(int *)(_frame + (0x430 - 0x420)))
  #define local_41c (*(int *)(_frame + (0x430 - 0x41c)))
  #define local_418 (*(int *)(_frame + (0x430 - 0x418)))
  #define local_410 (*(int (*)[3])(_frame + (0x430 - 0x410)))
  #define local_404 (*(int *)(_frame + (0x430 - 0x404)))
  #define local_400 (*(undefined1 (*)[1024])(_frame + (0x430 - 0x400)))
  
  if (param_2 == (int *)0x0) {
    param_2 = local_410;
    local_410[0] = 0;
    local_410[1] = 0;
    local_410[2] = param_1[1];
    local_404 = param_1[2];
  }
  local_420 = 0;
  local_41c = param_5[1];
  local_418 = param_5[2];
  iVar2 = *param_2 - param_3;
  if (0 < iVar2) {
    local_41c = local_41c - iVar2;
    param_3 = param_3 + iVar2;
    local_420 = iVar2;
  }
  iVar3 = param_2[1] - param_4;
  iVar2 = 0;
  if (0 < iVar3) {
    local_418 = local_418 - iVar3;
    param_4 = param_4 + iVar3;
    iVar2 = iVar3;
  }
  if (param_2[2] + *param_2 < local_41c + param_3) {
    local_41c = (param_2[2] + *param_2) - param_3;
  }
  iVar3 = param_2[3] + param_2[1];
  if (iVar3 < local_418 + param_4) {
    local_418 = iVar3 - param_4;
  }
  if ((0 < local_41c) && (0 < local_418)) {
    iVar3 = param_3 * param_1[3] + param_4 * param_1[5] + *param_1;
    iVar2 = iVar2 * param_5[5] + local_420 * param_5[3] + *param_5;
    if (((param_5[4] == param_1[4]) && (iVar1 = param_5[8], iVar1 == param_1[8])) &&
       (((iVar1 != 1 && (iVar1 != 2)) ||
        ((param_5[0xc] == param_1[0xc] &&
         ((param_5[0xd] == param_1[0xd] && (param_5[0xe] == param_1[0xe])))))))) {
      FUN_004cfdb0(iVar3,iVar2,0,0,0,0,local_41c * param_1[3],local_418,param_1[5],param_5[5]);
      return;
    }
    local_420 = local_418;
    if ((param_7 == (undefined1 *)0x0) && (param_5[3] == 1)) {
      FUN_004ced70(param_5,param_1,local_400,param_6);
      param_7 = local_400;
    }
    do {
      local_420 = local_420 + -1;
      iVar1 = FUN_004cedc0(iVar2,param_5,local_41c,param_6,iVar3,param_1,param_7);
      if (iVar1 != 0) {
        return;
      }
      iVar2 = iVar2 + param_5[5];
      iVar3 = iVar3 + param_1[5];
    } while (local_420 != 0);
  }
  return;
}
#undef local_400
#undef local_404
#undef local_410
#undef local_418
#undef local_41c
#undef local_420


/* ---- 0x004cec40  FUN_004cec40 ---- */
void FUN_004cec40(char *param_1,int param_2,int param_3,char *param_4)

{
  char cVar1;
  int iVar2;
  undefined3 uVar3;
  
  iVar2 = *(int *)(param_2 + 0xc) + -1;
  uVar3 = (undefined3)((uint)iVar2 >> 8);
  switch(iVar2) {
  case 0:
    FUN_004d5e50(param_1,CONCAT31(uVar3,*param_4),param_3);
    return;
  case 1:
    if (*param_4 == param_4[1]) {
      FUN_004d5e50(param_1,CONCAT31(uVar3,*param_4),param_3 * 2);
      return;
    }
    if (param_3 != 0) {
      do {
        *(undefined2 *)param_1 = *(undefined2 *)param_4;
        param_1 = param_1 + 2;
        param_3 = param_3 + -1;
      } while (param_3 != 0);
      return;
    }
    break;
  case 2:
    if ((*param_4 == param_4[1]) && (param_4[2] == param_4[1])) {
      FUN_004d5e50(param_1,*param_4,param_3 * 3);
      return;
    }
    if (param_3 != 0) {
      do {
        *param_1 = *param_4;
        param_1[1] = param_4[1];
        param_1[2] = param_4[2];
        param_1 = param_1 + 3;
        param_3 = param_3 + -1;
      } while (param_3 != 0);
      return;
    }
    break;
  case 3:
    cVar1 = param_4[1];
    if (((*param_4 == cVar1) && (param_4[2] == cVar1)) && (param_4[3] == cVar1)) {
      FUN_004d5e50(param_1,*param_4,param_3 * 4);
      return;
    }
    for (; param_3 != 0; param_3 = param_3 + -1) {
      *(undefined4 *)param_1 = *(undefined4 *)param_4;
      param_1 = param_1 + 4;
    }
  }
  return;
}

/* ---- 0x004ced70  FUN_004ced70 ---- */
undefined4 FUN_004ced70(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  if ((((*(int *)(param_1 + 0x20) == 0) && (*(int *)(param_1 + 0xc) == 1)) &&
      (*(int *)(param_2 + 0x20) != 0)) &&
     ((iVar1 = *(int *)(param_1 + 0x24), *(int *)(param_1 + 0x24) != 0 ||
      (iVar1 = param_4, param_4 != 0)))) {
    FUN_004cf520(param_3,param_2,0x100,0,iVar1);
    return 0;
  }
  return 0xffffffff;
}

/* ---- 0x004cedc0  FUN_004cedc0 ---- */
undefined4
FUN_004cedc0(int param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6,
            int param_7)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  if (((*(int *)(param_2 + 0x10) == *(int *)(param_6 + 0x10)) &&
      (iVar5 = *(int *)(param_2 + 0x20), iVar5 == *(int *)(param_6 + 0x20))) &&
     (((iVar5 != 1 && (iVar5 != 2)) ||
      (((*(int *)(param_2 + 0x30) == *(int *)(param_6 + 0x30) &&
        (*(int *)(param_2 + 0x34) == *(int *)(param_6 + 0x34))) &&
       (*(int *)(param_2 + 0x38) == *(int *)(param_6 + 0x38))))))) {
    FUN_004c3df0(param_5,param_1,*(int *)(param_6 + 0xc) * param_3);
    return 0;
  }
  if (param_7 != 0) {
    if ((*(int *)(param_2 + 0x20) == 0) && (*(int *)(param_2 + 0xc) == 1)) {
      ((code *)FUN_004cfdf0)(param_5,param_1,param_3,*(undefined4 *)(param_6 + 0xc),param_7);
      return 0;
    }
    if (((param_7 != 0) && (*(int *)(param_2 + 0xc) == 2)) && (*(int *)(param_6 + 0x20) != 0)) {
      ((code *)FUN_004cfea0)(param_5,param_1,param_3,*(undefined4 *)(param_6 + 0xc),param_7);
      return 0;
    }
  }
  if ((((*(int *)(param_2 + 0x20) != 2) || (*(int *)(param_2 + 0xc) != 4)) ||
      (*(int *)(param_2 + 0x30) != 0)) ||
     ((*(int *)(param_2 + 0x34) != 8 || (bVar1 = true, *(int *)(param_2 + 0x38) != 0x10)))) {
    bVar1 = false;
  }
  if (((*(int *)(param_6 + 0x20) != 2) || (*(int *)(param_6 + 0xc) != 4)) ||
     ((*(int *)(param_6 + 0x30) != 0 ||
      ((*(int *)(param_6 + 0x34) != 8 || (bVar2 = true, *(int *)(param_6 + 0x38) != 0x10)))))) {
    bVar2 = false;
  }
  iVar5 = param_3;
  if (0x4ff < param_3) {
    iVar5 = 0x500;
  }
  if (iVar5 < 1) {
    return 0;
  }
  while( true ) {
    if (bVar1) {
      iVar3 = FUN_004cf520(param_5,param_6,iVar5,param_4,param_1);
    }
    else if (bVar2) {
      iVar3 = FUN_004cf010(param_1,param_2,iVar5,param_4,param_5);
    }
    else {
      DAT_008da8a0 = DAT_008da8a0 + 1;
      uVar4 = DAT_008da8a0 & 1;
      iVar3 = FUN_004cf010(param_1,param_2,iVar5,param_4,&DAT_009272a0 + uVar4 * 0x1400);
      if (iVar3 != 0) {
        return 0xffffffff;
      }
      iVar3 = FUN_004cf520(param_5,param_6,iVar5,param_4,&DAT_009272a0 + uVar4 * 0x1400);
    }
    if (iVar3 != 0) break;
    param_3 = param_3 - iVar5;
    param_1 = param_1 + *(int *)(param_2 + 0xc) * iVar5;
    param_5 = param_5 + *(int *)(param_6 + 0xc) * iVar5;
    iVar5 = param_3;
    if (0x4ff < param_3) {
      iVar5 = 0x500;
    }
    if (iVar5 < 1) {
      return 0;
    }
  }
  return 0xffffffff;
}

/* ---- 0x004cf010  FUN_004cf010 ---- */
undefined4 FUN_004cf010(uint *param_1,int param_2,int param_3,int param_4,byte *param_5)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  ushort uVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  
  iVar15 = *(int *)(param_2 + 0x20);
  if ((iVar15 == 1) && (*(int *)(param_2 + 0xc) == 2)) {
    iVar14 = *(int *)(param_2 + 0x30);
    if ((iVar14 == 10) && ((*(int *)(param_2 + 0x34) == 5 && (*(int *)(param_2 + 0x38) == 0)))) {
      ((code *)FUN_004cffe0)(param_5,param_1,param_3);
      return 0;
    }
    if (((iVar14 == 0) && (*(int *)(param_2 + 0x34) == 5)) && (*(int *)(param_2 + 0x38) == 0xb)) {
      ((code *)FUN_004d01f0)(param_5,param_1,param_3);
      return 0;
    }
    if (((iVar14 == 0xb) && (*(int *)(param_2 + 0x34) == 5)) && (*(int *)(param_2 + 0x38) == 0)) {
      ((code *)FUN_004d00f0)(param_5,param_1,param_3);
      return 0;
    }
  }
  if (iVar15 == 0) {
    iVar15 = *(int *)(param_2 + 0x24);
    if ((*(int *)(param_2 + 0x24) == 0) && (iVar15 = param_4, param_4 == 0)) {
      return 0xffffffff;
    }
    ((code *)FUN_004cfdf0)(param_5,param_1,param_3,4,iVar15);
    return 0;
  }
  if (iVar15 == 1) {
    bVar1 = (&DAT_004f3da0)[*(int *)(param_2 + 0x28) * 4];
    bVar2 = (&DAT_004f3da0)[*(int *)(param_2 + 0x24) * 4];
    bVar3 = (&DAT_004f3da0)[*(int *)(param_2 + 0x2c) * 4];
    bVar4 = *(byte *)(param_2 + 0x30);
    bVar5 = *(byte *)(param_2 + 0x34);
    bVar6 = *(byte *)(param_2 + 0x38);
    bVar7 = *(byte *)(param_2 + 0x3c);
    bVar8 = *(byte *)(param_2 + 0x40);
    bVar9 = *(byte *)(param_2 + 0x44);
    iVar15 = *(int *)(param_2 + 0xc);
    if (iVar15 == 2) {
      if (param_3 != 0) {
        do {
          uVar13 = (ushort)*param_1;
          param_1 = (uint *)((int)param_1 + 2);
          *param_5 = (char)(uVar13 >> (bVar4 & 0x1f)) << (bVar7 & 0x1f) & bVar2;
          param_5[1] = (char)(uVar13 >> (bVar5 & 0x1f)) << (bVar8 & 0x1f) & bVar1;
          param_5[2] = (char)(uVar13 >> (bVar6 & 0x1f)) << (bVar9 & 0x1f) & bVar3;
          param_5[3] = 0xff;
          param_5 = param_5 + 4;
          param_3 = param_3 + -1;
        } while (param_3 != 0);
        return 0;
      }
    }
    else if (iVar15 == 3) {
      if (param_3 != 0) {
        do {
          uVar16 = *param_1;
          param_1 = (uint *)((int)param_1 + 3);
          uVar16 = uVar16 & 0xffffff;
          *param_5 = (char)(uVar16 >> (bVar4 & 0x1f)) << (bVar7 & 0x1f) & bVar2;
          param_5[1] = (char)(uVar16 >> (bVar5 & 0x1f)) << (bVar8 & 0x1f) & bVar1;
          param_5[2] = (char)(uVar16 >> (bVar6 & 0x1f)) << (bVar9 & 0x1f) & bVar3;
          param_5[3] = 0xff;
          param_5 = param_5 + 4;
          param_3 = param_3 + -1;
        } while (param_3 != 0);
        return 0;
      }
    }
    else {
      if (iVar15 != 4) {
        return 0xffffffff;
      }
      if (param_3 != 0) {
        do {
          uVar16 = *param_1;
          param_1 = param_1 + 1;
          *param_5 = (char)(uVar16 >> (bVar4 & 0x1f)) << (bVar7 & 0x1f) & bVar2;
          param_5[1] = (char)(uVar16 >> (bVar5 & 0x1f)) << (bVar8 & 0x1f) & bVar1;
          param_5[2] = (char)(uVar16 >> (bVar6 & 0x1f)) << (bVar9 & 0x1f) & bVar3;
          param_5[3] = 0xff;
          param_5 = param_5 + 4;
          param_3 = param_3 + -1;
        } while (param_3 != 0);
        return 0;
      }
    }
  }
  else {
    if (iVar15 != 2) {
      return 0xffffffff;
    }
    bVar1 = (&DAT_004f3da0)[*(int *)(param_2 + 0x28) * 4];
    bVar2 = (&DAT_004f3da0)[*(int *)(param_2 + 0x24) * 4];
    bVar3 = (&DAT_004f3da0)[*(int *)(param_2 + 0x2c) * 4];
    bVar4 = (&DAT_004f3da0)[*(int *)(param_2 + 0x48) * 4];
    bVar5 = *(byte *)(param_2 + 0x30);
    bVar6 = *(byte *)(param_2 + 0x34);
    bVar7 = *(byte *)(param_2 + 0x38);
    bVar8 = *(byte *)(param_2 + 0x4c);
    bVar9 = *(byte *)(param_2 + 0x3c);
    bVar10 = *(byte *)(param_2 + 0x40);
    bVar11 = *(byte *)(param_2 + 0x44);
    bVar12 = *(byte *)(param_2 + 0x50);
    iVar15 = *(int *)(param_2 + 0xc);
    if (iVar15 == 2) {
      if (param_3 != 0) {
        do {
          uVar13 = (ushort)*param_1;
          param_1 = (uint *)((int)param_1 + 2);
          *param_5 = (char)(uVar13 >> (bVar5 & 0x1f)) << (bVar9 & 0x1f) & bVar2;
          param_5[1] = (char)(uVar13 >> (bVar6 & 0x1f)) << (bVar10 & 0x1f) & bVar1;
          param_5[2] = (char)(uVar13 >> (bVar7 & 0x1f)) << (bVar11 & 0x1f) & bVar3;
          param_5[3] = (char)(uVar13 >> (bVar8 & 0x1f)) << (bVar12 & 0x1f) & bVar4;
          param_5 = param_5 + 4;
          param_3 = param_3 + -1;
        } while (param_3 != 0);
        return 0;
      }
    }
    else if (iVar15 == 3) {
      if (param_3 != 0) {
        do {
          uVar16 = *param_1;
          param_1 = (uint *)((int)param_1 + 3);
          uVar16 = uVar16 & 0xffffff;
          *param_5 = (char)(uVar16 >> (bVar5 & 0x1f)) << (bVar9 & 0x1f) & bVar2;
          param_5[1] = (char)(uVar16 >> (bVar6 & 0x1f)) << (bVar10 & 0x1f) & bVar1;
          param_5[2] = (char)(uVar16 >> (bVar7 & 0x1f)) << (bVar11 & 0x1f) & bVar3;
          param_5[3] = (char)(uVar16 >> (bVar8 & 0x1f)) << (bVar12 & 0x1f) & bVar4;
          param_5 = param_5 + 4;
          param_3 = param_3 + -1;
        } while (param_3 != 0);
        return 0;
      }
    }
    else {
      if (iVar15 != 4) {
        return 0xffffffff;
      }
      for (; param_3 != 0; param_3 = param_3 + -1) {
        uVar16 = *param_1;
        param_1 = param_1 + 1;
        *param_5 = (char)(uVar16 >> (bVar5 & 0x1f)) << (bVar9 & 0x1f) & bVar2;
        param_5[1] = (char)(uVar16 >> (bVar6 & 0x1f)) << (bVar10 & 0x1f) & bVar1;
        param_5[2] = (char)(uVar16 >> (bVar7 & 0x1f)) << (bVar11 & 0x1f) & bVar3;
        param_5[3] = (char)(uVar16 >> (bVar8 & 0x1f)) << (bVar12 & 0x1f) & bVar4;
        param_5 = param_5 + 4;
      }
    }
  }
  return 0;
}

/* ---- 0x004cf520  FUN_004cf520 ---- */
undefined4 FUN_004cf520(uint *param_1,int param_2,int param_3,undefined4 param_4,int param_5)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  int iVar13;
  uint uVar14;
  byte *pbVar15;
  uint *puVar16;
  
  if (*(int *)(param_2 + 0x20) == 1) {
    if (*(int *)(param_2 + 0xc) == 2) {
      iVar13 = *(int *)(param_2 + 0x30);
      if (((iVar13 == 10) && (*(int *)(param_2 + 0x34) == 5)) && (*(int *)(param_2 + 0x38) == 0)) {
        ((code *)FUN_004cff60)(param_1,param_5,param_3);
        return 0;
      }
      if (((iVar13 == 0) && (*(int *)(param_2 + 0x34) == 5)) && (*(int *)(param_2 + 0x38) == 0xb)) {
        ((code *)FUN_004d0180)(param_1,param_5,param_3);
        return 0;
      }
      if (((iVar13 == 0xb) && (*(int *)(param_2 + 0x34) == 5)) && (*(int *)(param_2 + 0x38) == 0)) {
        ((code *)FUN_004d0070)(param_1,param_5,param_3);
        return 0;
      }
    }
    bVar1 = *(byte *)(param_2 + 0x34);
    bVar2 = (&DAT_004f3da0)[*(int *)(param_2 + 0x24) * 4];
    bVar3 = (&DAT_004f3da0)[*(int *)(param_2 + 0x28) * 4];
    bVar4 = (&DAT_004f3da0)[*(int *)(param_2 + 0x2c) * 4];
    bVar5 = *(byte *)(param_2 + 0x30);
    bVar6 = *(byte *)(param_2 + 0x38);
    bVar7 = *(byte *)(param_2 + 0x3c);
    bVar8 = *(byte *)(param_2 + 0x40);
    bVar9 = *(byte *)(param_2 + 0x44);
    iVar13 = *(int *)(param_2 + 0xc);
    if (iVar13 == 1) {
      if (param_3 != 0) {
        pbVar15 = (byte *)(param_5 + 2);
        do {
          *(byte *)param_1 =
               (byte)((int)((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar8 & 0x1f)) |
               (byte)((int)((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar9 & 0x1f)) |
               (byte)((int)((uint)(pbVar15[-2] & bVar2) << (bVar5 & 0x1f)) >> (bVar7 & 0x1f));
          param_1 = (uint *)((int)param_1 + 1);
          param_3 = param_3 + -1;
          pbVar15 = pbVar15 + 4;
        } while (param_3 != 0);
        return 0;
      }
    }
    else if (iVar13 == 2) {
      if (param_3 != 0) {
        pbVar15 = (byte *)(param_5 + 2);
        do {
          param_3 = param_3 + -1;
          *(ushort *)param_1 =
               (ushort)((int)((uint)(pbVar15[-2] & bVar2) << (bVar5 & 0x1f)) >> (bVar7 & 0x1f)) |
               (ushort)((int)((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar9 & 0x1f)) |
               (ushort)((int)((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar8 & 0x1f));
          pbVar15 = pbVar15 + 4;
          param_1 = (uint *)((int)param_1 + 2);
        } while (param_3 != 0);
        return 0;
      }
    }
    else if (iVar13 == 3) {
      if (param_3 != 0) {
        puVar16 = param_1;
        pbVar15 = (byte *)(param_5 + 2);
        do {
          uVar14 = ((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar8 & 0x1f) |
                   ((uint)(pbVar15[-2] & bVar2) << (bVar5 & 0x1f)) >> (bVar7 & 0x1f) |
                   ((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar9 & 0x1f);
          *(byte *)puVar16 = (byte)uVar14;
          PIECE(param_1,2,1) = (byte)(uVar14 >> 0x10);
          *(byte *)((int)puVar16 + 1) = (byte)(uVar14 >> 8);
          *(byte *)((int)puVar16 + 2) = PIECE(param_1,2,1);
          puVar16 = (uint *)((int)puVar16 + 3);
          param_3 = param_3 + -1;
          pbVar15 = pbVar15 + 4;
        } while (param_3 != 0);
        return 0;
      }
    }
    else {
      if (iVar13 != 4) {
        return 0xffffffff;
      }
      if (param_3 != 0) {
        pbVar15 = (byte *)(param_5 + 2);
        do {
          param_3 = param_3 + -1;
          *param_1 = ((uint)(pbVar15[-2] & bVar2) << (bVar5 & 0x1f)) >> (bVar7 & 0x1f) |
                     ((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar9 & 0x1f) |
                     ((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar8 & 0x1f);
          pbVar15 = pbVar15 + 4;
          param_1 = param_1 + 1;
        } while (param_3 != 0);
        return 0;
      }
    }
  }
  else {
    if (*(int *)(param_2 + 0x20) != 2) {
      return 0xffffffff;
    }
    bVar1 = *(byte *)(param_2 + 0x34);
    bVar2 = (&DAT_004f3da0)[*(int *)(param_2 + 0x24) * 4];
    bVar3 = (&DAT_004f3da0)[*(int *)(param_2 + 0x28) * 4];
    bVar4 = (&DAT_004f3da0)[*(int *)(param_2 + 0x2c) * 4];
    bVar5 = (&DAT_004f3da0)[*(int *)(param_2 + 0x48) * 4];
    bVar6 = *(byte *)(param_2 + 0x38);
    bVar7 = *(byte *)(param_2 + 0x4c);
    bVar8 = *(byte *)(param_2 + 0x3c);
    bVar9 = *(byte *)(param_2 + 0x40);
    bVar10 = *(byte *)(param_2 + 0x44);
    bVar11 = *(byte *)(param_2 + 0x30);
    bVar12 = *(byte *)(param_2 + 0x50);
    iVar13 = *(int *)(param_2 + 0xc);
    if (iVar13 == 2) {
      if (param_3 != 0) {
        pbVar15 = (byte *)(param_5 + 2);
        do {
          param_3 = param_3 + -1;
          *(ushort *)param_1 =
               (ushort)((int)((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar10 & 0x1f)) |
               (ushort)((int)((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar9 & 0x1f)) |
               (ushort)((int)((uint)(pbVar15[-2] & bVar2) << (bVar11 & 0x1f)) >> (bVar8 & 0x1f)) |
               (ushort)((int)((uint)(pbVar15[1] & bVar5) << (bVar7 & 0x1f)) >> (bVar12 & 0x1f));
          pbVar15 = pbVar15 + 4;
          param_1 = (uint *)((int)param_1 + 2);
        } while (param_3 != 0);
        return 0;
      }
    }
    else if (iVar13 == 3) {
      if (param_3 != 0) {
        puVar16 = param_1;
        pbVar15 = (byte *)(param_5 + 2);
        do {
          uVar14 = ((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar10 & 0x1f) |
                   ((uint)(pbVar15[-2] & bVar2) << (bVar11 & 0x1f)) >> (bVar8 & 0x1f) |
                   ((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar9 & 0x1f) |
                   ((uint)(pbVar15[1] & bVar5) << (bVar7 & 0x1f)) >> (bVar12 & 0x1f);
          *(byte *)puVar16 = (byte)uVar14;
          PIECE(param_1,2,1) = (byte)(uVar14 >> 0x10);
          *(byte *)((int)puVar16 + 1) = (byte)(uVar14 >> 8);
          *(byte *)((int)puVar16 + 2) = PIECE(param_1,2,1);
          puVar16 = (uint *)((int)puVar16 + 3);
          param_3 = param_3 + -1;
          pbVar15 = pbVar15 + 4;
        } while (param_3 != 0);
        return 0;
      }
    }
    else {
      if (iVar13 != 4) {
        return 0xffffffff;
      }
      if (param_3 != 0) {
        pbVar15 = (byte *)(param_5 + 2);
        do {
          param_3 = param_3 + -1;
          *param_1 = ((uint)(pbVar15[1] & bVar5) << (bVar7 & 0x1f)) >> (bVar12 & 0x1f) |
                     ((uint)(pbVar15[-2] & bVar2) << (bVar11 & 0x1f)) >> (bVar8 & 0x1f) |
                     ((uint)(pbVar15[-1] & bVar3) << (bVar1 & 0x1f)) >> (bVar9 & 0x1f) |
                     ((uint)(*pbVar15 & bVar4) << (bVar6 & 0x1f)) >> (bVar10 & 0x1f);
          pbVar15 = pbVar15 + 4;
          param_1 = param_1 + 1;
        } while (param_3 != 0);
      }
    }
  }
  return 0;
}

/* ---- 0x004cfdb0  FUN_004cfdb0 ---- */
void FUN_004cfdb0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                 undefined4 param_9,undefined4 param_10)

{
  ((code *)FUN_004d0260)(param_2,param_1,param_5,param_6,param_3,param_4,param_7,param_8,param_10,param_9);
  return;
}

/* ---- 0x004cfdf0  FUN_004cfdf0 ---- */
undefined8 __fastcall
FUN_004cfdf0(undefined4 param_1,undefined4 param_2,undefined4 *param_3,ushort *param_4,uint param_5,
            char param_6,int param_7)

{
  bool bVar1;
  ushort uVar2;
  undefined4 in_EAX;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  if (param_6 == '\x01') {
    do {
      uVar2 = *param_4;
      param_4 = (ushort *)((int)param_4 + 1);
      *(undefined1 *)param_3 = *(undefined1 *)((uint)(byte)uVar2 + param_7);
      uVar4 = param_5 - 1;
      param_3 = (undefined4 *)((int)param_3 + 1);
      bVar1 = 0 < (int)param_5;
      param_5 = uVar4;
    } while (uVar4 != 0 && bVar1);
  }
  else if (param_6 == '\x02') {
    uVar4 = param_5 >> 1;
    if ((param_5 & 1) != 0) {
      uVar2 = *param_4;
      param_4 = (ushort *)((int)param_4 + 1);
      *(undefined2 *)param_3 = *(undefined2 *)(param_7 + (uint)(byte)uVar2 * 2);
      param_3 = (undefined4 *)((int)param_3 + 2);
    }
    do {
      uVar2 = *param_4;
      param_4 = param_4 + 1;
      *param_3 = CONCAT22(*(undefined2 *)(param_7 + (uint)(byte)(uVar2 >> 8) * 2),
                          *(undefined2 *)(param_7 + (uVar2 & 0xffff00ff) * 2));
      uVar5 = uVar4 - 1;
      param_3 = param_3 + 1;
      bVar1 = 0 < (int)uVar4;
      uVar4 = uVar5;
    } while (uVar5 != 0 && bVar1);
  }
  else if (param_6 == '\x03') {
    iVar3 = 0;
    do {
      iVar3 = CONCAT31((int3)((uint)iVar3 >> 8),(byte)*param_4) * 3;
      param_4 = (ushort *)((int)param_4 + 1);
      *param_3 = *(undefined4 *)(iVar3 + param_7);
      uVar4 = param_5 - 1;
      param_3 = (undefined4 *)((int)param_3 + 3);
      bVar1 = 0 < (int)param_5;
      param_5 = uVar4;
    } while (uVar4 != 0 && bVar1);
  }
  else if (param_6 == '\x04') {
    do {
      uVar2 = *param_4;
      param_4 = (ushort *)((int)param_4 + 1);
      *param_3 = *(undefined4 *)(param_7 + (uint)(byte)uVar2 * 4);
      uVar4 = param_5 - 1;
      param_3 = param_3 + 1;
      bVar1 = 0 < (int)param_5;
      param_5 = uVar4;
    } while (uVar4 != 0 && bVar1);
  }
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004cfea0  FUN_004cfea0 ---- */
undefined8 __fastcall FUN_004cfea0(undefined4 param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  bool bVar3;
  undefined4 in_EAX;
  int iVar4;
  uint uVar5;
  uint *unaff_EBX;
  uint unaff_EBP;
  uint uVar6;
  uint *unaff_ESI;
  char unaff_retaddr;
  
  if (unaff_retaddr == '\x01') {
    do {
      uVar5 = *unaff_EBX;
      unaff_EBX = (uint *)((int)unaff_EBX + 2);
      *(undefined1 *)unaff_ESI = *(undefined1 *)((uint)(ushort)uVar5 + param_3);
      uVar5 = unaff_EBP - 1;
      unaff_ESI = (uint *)((int)unaff_ESI + 1);
      bVar3 = 0 < (int)unaff_EBP;
      unaff_EBP = uVar5;
    } while (uVar5 != 0 && bVar3);
  }
  else if (unaff_retaddr == '\x02') {
    uVar5 = unaff_EBP >> 1;
    if ((unaff_EBP & 1) != 0) {
      uVar5 = *unaff_EBX;
      unaff_EBX = (uint *)((int)unaff_EBX + 2);
      *(undefined2 *)unaff_ESI = *(undefined2 *)(param_3 + (uint)(ushort)uVar5 * 2);
      uVar5 = unaff_EBP >> 1;
      unaff_ESI = (uint *)((int)unaff_ESI + 2);
    }
    do {
      uVar2 = *unaff_EBX;
      unaff_EBX = unaff_EBX + 1;
      uVar1 = *(ushort *)(param_3 + (uVar2 & 0xffff) * 2);
      uVar6 = uVar5 - 1;
      *unaff_ESI = (uint)uVar1 |
                   CONCAT22(uVar1,*(undefined2 *)(param_3 + (uVar2 >> 0x10) * 2)) << 0x10;
      bVar3 = 0 < (int)uVar5;
      uVar5 = uVar6;
      unaff_ESI = unaff_ESI + 1;
    } while (uVar6 != 0 && bVar3);
  }
  else if (unaff_retaddr == '\x03') {
    iVar4 = 0;
    do {
      iVar4 = CONCAT22((short)((uint)iVar4 >> 0x10),(ushort)*unaff_EBX) * 3;
      unaff_EBX = (uint *)((int)unaff_EBX + 2);
      *unaff_ESI = *(uint *)(iVar4 + param_3);
      uVar5 = unaff_EBP - 1;
      unaff_ESI = (uint *)((int)unaff_ESI + 3);
      bVar3 = 0 < (int)unaff_EBP;
      unaff_EBP = uVar5;
    } while (uVar5 != 0 && bVar3);
  }
  else if (unaff_retaddr == '\x04') {
    do {
      uVar5 = *unaff_EBX;
      unaff_EBX = (uint *)((int)unaff_EBX + 2);
      *unaff_ESI = *(uint *)(param_3 + (uint)(ushort)uVar5 * 4);
      uVar5 = unaff_EBP - 1;
      unaff_ESI = unaff_ESI + 1;
      bVar3 = 0 < (int)unaff_EBP;
      unaff_EBP = uVar5;
    } while (uVar5 != 0 && bVar3);
  }
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004cff60  FUN_004cff60 ---- */
undefined8 __fastcall
FUN_004cff60(undefined4 param_1,undefined4 param_2,undefined4 *param_3,uint *param_4,uint param_5)

{
  bool bVar1;
  undefined4 in_EAX;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  uVar2 = param_5 >> 1;
  if ((param_5 & 1) != 0) {
    uVar2 = *param_4 & 0xf8f8f8;
    iVar5 = (uint)CONCAT11((byte)uVar2 >> 3,(char)(uVar2 >> 8)) << 2;
    *(short *)param_3 =
         (short)CONCAT31((int3)((uint)iVar5 >> 8),(byte)iVar5 | (byte)((uVar2 >> 0xb) >> 8));
    param_4 = param_4 + 1;
    param_3 = (undefined4 *)((int)param_3 + 2);
    uVar2 = param_5 >> 1;
  }
  do {
    uVar3 = param_4[1] & 0xf8f8f8;
    uVar4 = *param_4 & 0xf8f8f8;
    iVar6 = (uint)CONCAT11((byte)uVar3 >> 3,(char)(uVar3 >> 8)) << 2;
    iVar5 = (uint)CONCAT11((byte)uVar4 >> 3,(char)(uVar4 >> 8)) << 2;
    *param_3 = CONCAT22((short)CONCAT31((int3)((uint)iVar6 >> 8),
                                        (byte)iVar6 | (byte)((uVar3 >> 0xb) >> 8)),
                        (short)CONCAT31((int3)((uint)iVar5 >> 8),
                                        (byte)iVar5 | (byte)((uVar4 >> 0xb) >> 8)));
    param_4 = param_4 + 2;
    param_3 = param_3 + 1;
    uVar3 = uVar2 - 1;
    bVar1 = 0 < (int)uVar2;
    uVar2 = uVar3;
  } while (uVar3 != 0 && bVar1);
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004cffe0  FUN_004cffe0 ---- */
undefined8 __fastcall
FUN_004cffe0(undefined4 param_1,uint param_2,uint *param_3,ushort *param_4,uint param_5)

{
  ushort uVar1;
  bool bVar2;
  undefined4 in_EAX;
  ushort uVar4;
  uint uVar3;
  uint unaff_EBX;
  ushort uVar5;
  ushort uVar6;
  uint uVar7;
  uint uVar8;
  
  uVar3 = param_2;
  uVar7 = param_5 >> 1;
  if ((param_5 & 1) != 0) {
    uVar1 = *param_4;
    uVar5 = (ushort)(unaff_EBX >> 0x17) | (ushort)(((uint)(byte)(uVar1 >> 8) << 0x19) >> 0x10);
    unaff_EBX = CONCAT31(CONCAT21(uVar5,(char)uVar1 << 3),(char)(((uint)uVar1 << 6) >> 8)) << 8 |
                (uint)(uVar5 >> 8) | 0xff070707;
    *param_3 = unaff_EBX;
    param_4 = param_4 + 1;
    param_3 = param_3 + 1;
  }
  do {
    uVar1 = param_4[1];
    uVar5 = *param_4;
    uVar6 = (ushort)(unaff_EBX >> 0x17) | (ushort)(((uint)(byte)(uVar1 >> 8) << 0x19) >> 0x10);
    uVar4 = (ushort)(uVar3 >> 0x17) | (ushort)(((uint)(byte)(uVar5 >> 8) << 0x19) >> 0x10);
    unaff_EBX = CONCAT31(CONCAT21(uVar6,(char)uVar1 << 3),(char)(((uint)uVar1 << 6) >> 8)) << 8 |
                (uint)(uVar6 >> 8) | 0xff070707;
    uVar3 = CONCAT31(CONCAT21(uVar4,(char)uVar5 << 3),(char)(((uint)uVar5 << 6) >> 8)) << 8 |
            (uint)(uVar4 >> 8) | 0xff070707;
    param_3[1] = unaff_EBX;
    *param_3 = uVar3;
    param_4 = param_4 + 2;
    param_3 = param_3 + 2;
    uVar8 = uVar7 - 1;
    bVar2 = 0 < (int)uVar7;
    uVar7 = uVar8;
  } while (uVar8 != 0 && bVar2);
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004d0070  FUN_004d0070 ---- */
undefined8 __fastcall
FUN_004d0070(undefined4 param_1,undefined4 param_2,undefined4 *param_3,uint *param_4,uint param_5)

{
  bool bVar1;
  undefined4 in_EAX;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  uVar2 = param_5 >> 1;
  if ((param_5 & 1) != 0) {
    uVar2 = *param_4 & 0xf8fcf8;
    iVar5 = (uint)CONCAT11((byte)uVar2 >> 3,(char)(uVar2 >> 8)) << 3;
    *(short *)param_3 =
         (short)CONCAT31((int3)((uint)iVar5 >> 8),(byte)iVar5 | (byte)((uVar2 >> 0xb) >> 8));
    param_4 = param_4 + 1;
    param_3 = (undefined4 *)((int)param_3 + 2);
    uVar2 = param_5 >> 1;
  }
  do {
    uVar3 = param_4[1] & 0xf8fcf8;
    uVar4 = *param_4 & 0xf8fcf8;
    iVar6 = (uint)CONCAT11((byte)uVar3 >> 3,(char)(uVar3 >> 8)) << 3;
    iVar5 = (uint)CONCAT11((byte)uVar4 >> 3,(char)(uVar4 >> 8)) << 3;
    *param_3 = CONCAT22((short)CONCAT31((int3)((uint)iVar6 >> 8),
                                        (byte)iVar6 | (byte)((uVar3 >> 0xb) >> 8)),
                        (short)CONCAT31((int3)((uint)iVar5 >> 8),
                                        (byte)iVar5 | (byte)((uVar4 >> 0xb) >> 8)));
    param_4 = param_4 + 2;
    param_3 = param_3 + 1;
    uVar3 = uVar2 - 1;
    bVar1 = 0 < (int)uVar2;
    uVar2 = uVar3;
  } while (uVar3 != 0 && bVar1);
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004d00f0  FUN_004d00f0 ---- */
undefined8 __fastcall
FUN_004d00f0(undefined4 param_1,uint param_2,uint *param_3,ushort *param_4,uint param_5)

{
  ushort uVar1;
  ushort uVar2;
  bool bVar3;
  undefined4 in_EAX;
  uint uVar4;
  uint unaff_EBX;
  uint uVar5;
  uint uVar6;
  
  uVar4 = param_2;
  uVar5 = param_5 >> 1;
  if ((param_5 & 1) != 0) {
    uVar1 = *param_4;
    unaff_EBX = CONCAT31(CONCAT21(CONCAT11((char)(unaff_EBX >> 0x18),(char)uVar1 << 3),
                                  (char)(((uint)uVar1 << 5) >> 8)),(char)(uVar1 >> 8)) | 0xff070307;
    *param_3 = unaff_EBX;
    param_4 = param_4 + 1;
    param_3 = param_3 + 1;
  }
  do {
    uVar1 = param_4[1];
    uVar2 = *param_4;
    unaff_EBX = CONCAT31(CONCAT21(CONCAT11((char)(unaff_EBX >> 0x18),(char)uVar1 << 3),
                                  (char)(((uint)uVar1 << 5) >> 8)),(char)(uVar1 >> 8)) | 0xff070307;
    uVar4 = CONCAT31(CONCAT21(CONCAT11((char)(uVar4 >> 0x18),(char)uVar2 << 3),
                              (char)(((uint)uVar2 << 5) >> 8)),(char)(uVar2 >> 8)) | 0xff070307;
    param_3[1] = unaff_EBX;
    *param_3 = uVar4;
    param_4 = param_4 + 2;
    param_3 = param_3 + 2;
    uVar6 = uVar5 - 1;
    bVar3 = 0 < (int)uVar5;
    uVar5 = uVar6;
  } while (uVar6 != 0 && bVar3);
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004d0180  FUN_004d0180 ---- */
undefined8 __fastcall
FUN_004d0180(undefined4 param_1,undefined4 param_2,undefined4 *param_3,uint *param_4,uint param_5)

{
  bool bVar1;
  short sVar2;
  undefined4 in_EAX;
  ushort uVar3;
  short sVar4;
  ushort uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar6 = param_5 >> 1;
  if ((param_5 & 1) != 0) {
    uVar3 = (ushort)(*param_4 >> 0x13);
    sVar2 = (short)(*param_4 >> 3) << 1;
    *(short *)param_3 =
         (short)(CONCAT22(uVar3,(short)CONCAT31((int3)(CONCAT22(uVar3,sVar2) >> 8),(char)sVar2 << 2)
                                << 2) >> 5);
    param_4 = param_4 + 1;
    param_3 = (undefined4 *)((int)param_3 + 2);
  }
  do {
    uVar3 = (ushort)(param_4[1] >> 0x13);
    sVar2 = (short)(param_4[1] >> 3) << 1;
    uVar5 = (ushort)(*param_4 >> 0x13);
    sVar4 = (short)(*param_4 >> 3) << 1;
    *param_3 = CONCAT22((short)(CONCAT22(uVar3,(short)CONCAT31((int3)(CONCAT22(uVar3,sVar2) >> 8),
                                                               (char)sVar2 << 2) << 2) >> 5),
                        (short)(CONCAT22(uVar5,(short)CONCAT31((int3)(CONCAT22(uVar5,sVar4) >> 8),
                                                               (char)sVar4 << 2) << 2) >> 5));
    param_4 = param_4 + 2;
    param_3 = param_3 + 1;
    uVar7 = uVar6 - 1;
    bVar1 = 0 < (int)uVar6;
    uVar6 = uVar7;
  } while (uVar7 != 0 && bVar1);
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004d01f0  FUN_004d01f0 ---- */
undefined8 __fastcall
FUN_004d01f0(undefined4 param_1,undefined4 param_2,int *param_3,ushort *param_4,uint param_5)

{
  bool bVar1;
  undefined4 in_EAX;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = param_5 >> 1;
  if ((param_5 & 1) != 0) {
    iVar2 = CONCAT22((short)(((uint)*param_4 << 5) >> 0x10),(ushort)((uint)*param_4 << 5) >> 3) << 1
    ;
    *param_3 = CONCAT31((int3)((uint)iVar2 >> 8),(byte)iVar2 >> 2) << 2;
    param_4 = param_4 + 1;
    param_3 = param_3 + 1;
  }
  do {
    iVar2 = CONCAT22((short)(((uint)param_4[1] << 5) >> 0x10),(ushort)((uint)param_4[1] << 5) >> 3)
            << 1;
    iVar3 = CONCAT22((short)(((uint)*param_4 << 5) >> 0x10),(ushort)((uint)*param_4 << 5) >> 3) << 1
    ;
    param_3[1] = CONCAT31((int3)((uint)iVar2 >> 8),(byte)iVar2 >> 2) << 2;
    *param_3 = CONCAT31((int3)((uint)iVar3 >> 8),(byte)iVar3 >> 2) << 2;
    param_4 = param_4 + 2;
    param_3 = param_3 + 2;
    uVar5 = uVar4 - 1;
    bVar1 = 0 < (int)uVar4;
    uVar4 = uVar5;
  } while (uVar5 != 0 && bVar1);
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004d0260  FUN_004d0260 ---- */
undefined8 __fastcall
FUN_004d0260(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5,uint param_6,
            int param_7,uint param_8,uint param_9,int param_10,uint param_11,uint param_12)

{
  bool bVar1;
  undefined4 in_EAX;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  uVar3 = (param_6 & 0xffff) * (param_11 & 0xffff);
  puVar7 = (undefined4 *)
           (param_3 + param_5 +
           (CONCAT22((short)(param_6 >> 0x10),(short)uVar3) | uVar3 & 0xffff0000));
  uVar3 = (param_8 & 0xffff) * (param_12 & 0xffff);
  puVar8 = (undefined4 *)
           (param_4 + param_7 +
           (CONCAT22((short)(param_8 >> 0x10),(short)uVar3) | uVar3 & 0xffff0000));
  iVar5 = param_11 - param_9;
  iVar4 = param_12 - param_9;
  if ((param_9 & 3) == 0) {
    if (iVar4 == 0) {
      uVar3 = param_9 >> 2;
      do {
        for (; uVar3 != 0; uVar3 = uVar3 - 1) {
          *puVar8 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar8 = puVar8 + 1;
        }
        puVar7 = (undefined4 *)((int)puVar7 + iVar5);
        iVar4 = param_10 + -1;
        bVar1 = 0 < param_10;
        uVar3 = param_9 >> 2;
        param_10 = iVar4;
      } while (iVar4 != 0 && bVar1);
    }
    else {
      uVar3 = param_9 >> 2;
      do {
        for (; uVar3 != 0; uVar3 = uVar3 - 1) {
          *puVar8 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar8 = puVar8 + 1;
        }
        puVar8 = (undefined4 *)((int)puVar8 + iVar4);
        puVar7 = (undefined4 *)((int)puVar7 + iVar5);
        iVar6 = param_10 + -1;
        bVar1 = 0 < param_10;
        uVar3 = param_9 >> 2;
        param_10 = iVar6;
      } while (iVar6 != 0 && bVar1);
    }
  }
  else {
    uVar3 = param_9 >> 2;
    do {
      for (; uVar2 = param_9 & 3, uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      puVar8 = (undefined4 *)((int)puVar8 + iVar4);
      puVar7 = (undefined4 *)((int)puVar7 + iVar5);
      iVar6 = param_10 + -1;
      bVar1 = 0 < param_10;
      uVar3 = param_9 >> 2;
      param_10 = iVar6;
    } while (iVar6 != 0 && bVar1);
  }
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004d0300  FUN_004d0300 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004d0300(int *param_1,undefined4 param_2)

{
  bool bVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  
  PTR_008dacf8 = param_1;
  DAT_008db098 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_sound_004f3e5c,&PTR_FUN_004f3dc8);
  (*(code *)*PTR_008dacf8)(s_SOUND_insane_004f3e4c,&PTR_FUN_004f3dd8);
  iVar4 = 0;
  PTR_008dacf0 = (int *)0x0;
  DAT_008db09c = 0x5622;
  DAT_008dacfc = 64000;
  _DAT_008db1e8 = 0;
  DAT_008dad50 = 0;
  DAT_008dacf4 = 0;
  DAT_008db0a0 = 0;
  puVar2 = &DAT_008dacb0;
  do {
    bVar1 = 0 < iVar4;
    puVar3 = puVar2 + 1;
    iVar4 = iVar4 + 1;
    *puVar2 = bVar1 - 1 & 100000;
    puVar2 = puVar3;
  } while ((int)puVar3 < IMG_ADDR(0x008dacf0));
  DAT_008dacb0 = 500000;
  return 0;
}

/* ---- 0x004d03a0  FUN_004d03a0 ---- */
void FUN_004d03a0(void)

{
  (*(code *)PTR_008dacf8[1])(s_SOUND_insane_004f3e4c);
  (*(code *)PTR_008dacf8[1])(s_LECMODULE_insane_sound_004f3e5c);
  return;
}

/* ---- 0x004d03d0  FUN_004d03d0 ---- */
undefined4 FUN_004d03d0(void)

{
  int iVar1;
  undefined4 uVar2;
  
  PTR_008da8a8 = (int *)(*(code *)PTR_008dacf8[2])(s_MEMORY_workspace_004f14ec,DAT_008db098);
  DAT_008dad48 = (*(code *)PTR_008dacf8[2])(s_TIMER_external_sync_004f3f1c,DAT_008db098);
  iVar1 = DAT_008db0a0;
  if (DAT_008db0a0 == 0) {
    iVar1 = DAT_008db098;
  }
  PTR_008dacf0 = (int *)(*(code *)PTR_008dacf8[2])(s_SNDDRIVER_driver_004f3f08,iVar1);
  if (PTR_008da8a8 == (int *)0x0) {
    (*(code *)PTR_008dacf8[8])(s_Sound_Module__Cannot_allocate_me_004f3ed8);
    return 0xffffffff;
  }
  if (DAT_008dad48 == 0) {
    (*(code *)PTR_008dacf8[8])(s_Sound_Module__Cannot_allocate_ti_004f3ea8);
    return 0xffffffff;
  }
  if (PTR_008dacf0 == (int *)0x0) {
    (*(code *)PTR_008dacf8[8])(s_Sound_Module__Cannot_allocate_sn_004f3e74);
    return 0xffffffff;
  }
  uVar2 = ((code *)FUN_004d0550)(DAT_008db09c,DAT_008dacfc,DAT_008dacb0,DAT_008dacb4,DAT_008dacb8,DAT_008dacbc
                       ,DAT_008dacc0,DAT_008dacc4,DAT_008dacc8,DAT_008daccc,DAT_008dacd0,
                       DAT_008dacd4,DAT_008dacd8,DAT_008dacdc,DAT_008dace0,DAT_008dace4,DAT_008dace8
                       ,DAT_008dacec,0);
  return uVar2;
}

/* ---- 0x004d0510  FUN_004d0510 ---- */
void FUN_004d0510(void)

{
  (*(code *)PTR_008dacf8[3])(PTR_008da8a8);
  (*(code *)PTR_008dacf8[3])(PTR_008dacf0);
  (*(code *)PTR_008dacf8[3])(DAT_008dad48);
  FUN_004d0610();
  return;
}

/* ---- 0x004d0550  FUN_004d0550 ---- */
undefined4 FUN_004d0550(undefined4 param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  uint *puVar2;
  
  DAT_004f3e30 = 0;
  DAT_004f3e34 = 0x7f;
  iVar1 = 0;
  do {
    (&DAT_008db0e8)[iVar1] = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x100);
  puVar2 = (uint *)&STACK0X(0x00000010);
  while( true ) {
    if (param_3 == 0) {
      iVar1 = (*(code *)*PTR_008dacf0)(param_1,DAT_004f3e30,&LAB_004d16a0);
      DAT_008db1f0 = (uint)(iVar1 == 0);
      DAT_004f3e38 = (*(code *)PTR_008dacf0[5])();
      DAT_008dacf4 = 0;
      DAT_008dad40 = 1;
      DAT_008dad4c = 1;
      DAT_008dad44 = 1;
      (**(code **)(DAT_008dad48 + 0x20))(0);
      return 0;
    }
    iVar1 = FUN_004d06a0(param_3 & 0xfffffffc,param_2);
    if (iVar1 != 0) break;
    param_3 = *puVar2;
    puVar2 = puVar2 + 1;
  }
  FUN_004d0610();
  return 0xffffffff;
}

/* ---- 0x004d0610  FUN_004d0610 ---- */
undefined4 FUN_004d0610(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  if (DAT_008db1f0 != 0) {
    (*(code *)PTR_008dacf0[1])();
    DAT_008db1f0 = 0;
  }
  iVar3 = 0;
  if (0 < DAT_004f3e30) {
    piVar2 = &DAT_008dad5c;
    do {
      if (piVar2[-1] != 0) {
        (*(code *)PTR_008da8a8[1])(piVar2[-1],s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1a8);
      }
      piVar2[-1] = 0;
      if (*piVar2 != 0) {
        (*(code *)PTR_008da8a8[1])(*piVar2,s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1a9);
      }
      iVar1 = DAT_004f3e30;
      *piVar2 = 0;
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 0xd;
    } while (iVar3 < iVar1);
  }
  DAT_004f3e30 = 0;
  return DAT_008dacf4;
}

/* ---- 0x004d06a0  FUN_004d06a0 ---- */
undefined4 FUN_004d06a0(uint param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  piVar2 = PTR_008da8a8;
  iVar1 = DAT_004f3e30;
  iVar5 = DAT_004f3e30 * 0x34;
  (&DAT_008dad6e)[iVar5] = 0;
  (&DAT_008dad84)[iVar1 * 0xd] = 0;
  (&DAT_008dad70)[iVar1 * 0xd] = 0;
  (&DAT_008dad74)[iVar1 * 0xd] = 0xffffff01;
  (&DAT_008dad58)[iVar1 * 0xd] = 0;
  (&DAT_008dad5c)[iVar1 * 0xd] = 0;
  *(uint *)(iVar5 + IMG_ADDR(0x008dad68)) = param_1 & 0xfffffffc;
  iVar3 = (*(code *)*piVar2)(0x1800,s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1cf);
  (&DAT_008dad5c)[iVar1 * 0xd] = iVar3;
  if (iVar3 == 0) {
    return 0xffffffff;
  }
  iVar3 = (*(code *)*PTR_008da8a8)
                    (*(undefined4 *)(iVar5 + IMG_ADDR(0x008dad68)),s_C__grimsrc_libs_lecsmush_insane__004f3f30,
                     0x1d1);
  (&DAT_008dad58)[iVar1 * 0xd] = iVar3;
  if (iVar3 == 0) {
    iVar3 = *(int *)(iVar5 + IMG_ADDR(0x008dad68));
    while (param_2 < iVar3) {
      iVar3 = (*(code *)*PTR_008da8a8)
                        (*(undefined4 *)(iVar5 + IMG_ADDR(0x008dad68)),
                         s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1d7);
      (&DAT_008dad58)[iVar1 * 0xd] = iVar3;
      if (iVar3 != 0) break;
      iVar3 = *(int *)(iVar5 + IMG_ADDR(0x008dad68)) + -10000;
      *(int *)(iVar5 + IMG_ADDR(0x008dad68)) = iVar3;
    }
    uVar4 = *(uint *)(iVar5 + IMG_ADDR(0x008dad68)) & 0xfffffffc;
    *(uint *)(iVar5 + IMG_ADDR(0x008dad68)) = uVar4;
    if (param_2 < (int)uVar4) {
      if ((&DAT_008dad58)[iVar1 * 0xd] != 0) {
        (*(code *)PTR_008da8a8[1])
                  ((&DAT_008dad58)[iVar1 * 0xd],s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1e2);
      }
      (&DAT_008dad58)[iVar1 * 0xd] = 0;
      piVar2 = PTR_008da8a8;
      param_2 = *(int *)(iVar5 + IMG_ADDR(0x008dad68)) - param_2;
      *(int *)(iVar5 + IMG_ADDR(0x008dad68)) = param_2;
      iVar3 = (*(code *)*piVar2)(param_2,s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1e5);
      (&DAT_008dad58)[iVar1 * 0xd] = iVar3;
      if (iVar3 != 0) goto LAB_004d0827;
    }
    if ((&DAT_008dad5c)[iVar1 * 0xd] != 0) {
      (*(code *)PTR_008da8a8[1])
                ((&DAT_008dad5c)[iVar1 * 0xd],s_C__grimsrc_libs_lecsmush_insane__004f3f30,0x1ee);
    }
    (&DAT_008dad5c)[iVar1 * 0xd] = 0;
    return 0xfffffffe;
  }
LAB_004d0827:
  FUN_004d5e50((&DAT_008dad58)[iVar1 * 0xd],0x7f,*(undefined4 *)(iVar5 + IMG_ADDR(0x008dad68)));
  DAT_004f3e30 = DAT_004f3e30 + 1;
  return 0;
}

/* ---- 0x004d0860  FUN_004d0860 ---- */
void FUN_004d0860(undefined1 *param_1,undefined4 param_2,int param_3,int param_4,uint param_5)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  if (DAT_008db1f0 != 0) {
    uVar2 = CONCAT31(CONCAT21(CONCAT11(*param_1,param_1[1]),param_1[2]),param_1[3]);
    if (uVar2 < 0x50534145) {
      if (uVar2 != 0x50534144) {
        if (uVar2 != 0x43726561) {
          return;
        }
        iVar3 = (uint)(byte)param_1[0x15] * 0x100 + (uint)(byte)param_1[0x14];
        bVar1 = param_1[iVar3 + 1];
        FUN_004d0f00(param_1 + iVar3 + 6,(uint)CONCAT11(bVar1,bVar1) * 0x100 + (uint)bVar1,param_2,
                     param_3,param_4,param_5);
        return;
      }
    }
    else if (uVar2 != 0x50564f43) {
      if (uVar2 != 0x53415544) {
        return;
      }
      FUN_004d1180(param_1,CONCAT31(CONCAT21(CONCAT11(param_1[4],param_1[5]),param_1[6]),param_1[7])
                           + 8,param_2,param_3,param_4,param_5,0,0,1,0);
      return;
    }
    if ((((param_1[8] == '\0') && (param_1[9] == '\0')) && (param_1[0xc] == '\0')) &&
       (((param_1[0xd] == '\0' && (param_1[0x10] == '\0')) && (param_1[0x11] == '\0')))) {
      FUN_004d1180(param_1 + 0x14,
                   CONCAT31(CONCAT21(CONCAT11(param_1[4],param_1[5]),param_1[6]),param_1[7]) + -0xc,
                   param_2,param_3,param_4,param_5,CONCAT11(param_1[10],param_1[0xb]),
                   CONCAT11(param_1[0xe],param_1[0xf]),CONCAT11(param_1[0x12],param_1[0x13]),1);
      return;
    }
    if ((char)param_1[0x11] < -0x7f) {
      param_4 = 0x80;
    }
    else {
      param_4 = param_4 + (char)param_1[0x11];
    }
    FUN_004d1180(param_1 + 0x12,
                 CONCAT31(CONCAT21(CONCAT11(param_1[4],param_1[5]),param_1[6]),param_1[7]) + -10,
                 param_2,(int)((uint)(byte)param_1[0x10] * param_3) >> 7,param_4,
                 (int)*(short *)(param_1 + 0xe) | param_5,(int)*(short *)(param_1 + 8),
                 (int)*(short *)(param_1 + 10),(int)*(short *)(param_1 + 0xc),1);
  }
  return;
}

/* ---- 0x004d0a50  FUN_004d0a50 ---- */
void FUN_004d0a50(int param_1)

{
  int *piVar1;
  int iVar2;
  
  if (0 < DAT_004f3e30) {
    piVar1 = &DAT_008dad74;
    iVar2 = DAT_004f3e30;
    do {
      if (*piVar1 == param_1) {
        *(undefined1 *)((int)piVar1 + -6) = 0;
        *piVar1 = -0xff;
      }
      piVar1 = piVar1 + 0xd;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

/* ---- 0x004d0a80  FUN_004d0a80 ---- */
void FUN_004d0a80(void)

{
  DAT_008db1ec = DAT_008db1ec + 1;
  return;
}

/* ---- 0x004d0a90  FUN_004d0a90 ---- */
void FUN_004d0a90(void)

{
  if (DAT_008db1ec != 0) {
    DAT_008db1ec = DAT_008db1ec + -1;
  }
  return;
}

/* ---- 0x004d0aa0  FUN_004d0aa0 ---- */
void FUN_004d0aa0(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (0 < DAT_004f3e30) {
    puVar1 = &DAT_008dad74;
    iVar2 = DAT_004f3e30;
    do {
      *(undefined1 *)((int)puVar1 + -6) = 0;
      *puVar1 = 0xffffff01;
      puVar1 = puVar1 + 0xd;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

/* ---- 0x004d0ad0  FUN_004d0ad0 ---- */
void FUN_004d0ad0(int param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  int iVar2;
  
  if (param_1 == -0xff) {
    DAT_004f3e34 = param_2;
    return;
  }
  if (0 < DAT_004f3e30) {
    puVar1 = &DAT_008dad6c;
    iVar2 = DAT_004f3e30;
    do {
      if (*(int *)(puVar1 + 8) == param_1) {
        *puVar1 = (undefined1)param_2;
      }
      puVar1 = puVar1 + 0x34;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

/* ---- 0x004d0b10  FUN_004d0b10 ---- */
int FUN_004d0b10(int param_1)

{
  int iVar1;
  int *piVar2;
  
  if (param_1 == -0xff) {
    return DAT_004f3e34;
  }
  iVar1 = 0;
  if (0 < DAT_004f3e30) {
    piVar2 = &DAT_008dad74;
    do {
      if (*piVar2 == param_1) {
        return (int)(char)(&DAT_008dad6c)[iVar1 * 0x34];
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0xd;
    } while (iVar1 < DAT_004f3e30);
    return -1;
  }
  return -1;
}

/* ---- 0x004d0b60  FUN_004d0b60 ---- */
void FUN_004d0b60(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  int iVar2;
  
  if (0 < DAT_004f3e30) {
    puVar1 = &DAT_008dad6d;
    iVar2 = DAT_004f3e30;
    do {
      if (*(int *)(puVar1 + 7) == param_1) {
        *puVar1 = param_2;
      }
      puVar1 = puVar1 + 0x34;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

/* ---- 0x004d0b90  FUN_004d0b90 ---- */
int FUN_004d0b90(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  if (DAT_004f3e30 < 1) {
    return -1;
  }
  piVar2 = &DAT_008dad74;
  do {
    if (*piVar2 == param_1) {
      return (int)(char)(&DAT_008dad6d)[iVar1 * 0x34];
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 0xd;
  } while (iVar1 < DAT_004f3e30);
  return -1;
}

/* ---- 0x004d0bd0  FUN_004d0bd0 ---- */
void FUN_004d0bd0(undefined4 param_1)

{
  if (PTR_008dacf0 != (int *)0x0) {
    (*(code *)PTR_008dacf0[2])(param_1);
  }
  return;
}

/* ---- 0x004d0bf0  FUN_004d0bf0 ---- */
undefined4 FUN_004d0bf0(void)

{
  undefined4 uVar1;
  
  if (PTR_008dacf0 != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x004d0bf9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*(code *)PTR_008dacf0[3])();
    return uVar1;
  }
  return 0xffffffff;
}

/* ---- 0x004d0c00  FUN_004d0c00 ---- */
void FUN_004d0c00(undefined4 param_1)

{
  DAT_004f3e38 = param_1;
  if (PTR_008dacf0 != (int *)0x0) {
    (*(code *)PTR_008dacf0[4])(param_1);
  }
  return;
}

/* ---- 0x004d0c30  FUN_004d0c30 ---- */
int FUN_004d0c30(int param_1)

{
  int iVar1;
  char *pcVar2;
  int *piVar3;
  
  if (param_1 == -0xff) {
    iVar1 = 0;
    if (0 < DAT_004f3e30) {
      pcVar2 = &DAT_008dad6e;
      do {
        if (*pcVar2 != '\0') {
          return (&DAT_008dad84)[iVar1 * 0xd] + 1;
        }
        iVar1 = iVar1 + 1;
        pcVar2 = pcVar2 + 0x34;
      } while (iVar1 < DAT_004f3e30);
      return 0;
    }
  }
  else if ((param_1 < 0) && (-1 - param_1 < DAT_004f3e30)) {
    if ((&DAT_008dad6e)[(param_1 + 1) * -0x34] != '\0') {
      return (&DAT_008dad84)[(param_1 + 1) * -0xd] + 1;
    }
  }
  else {
    iVar1 = 0;
    if (0 < DAT_004f3e30) {
      piVar3 = &DAT_008dad74;
      while (*piVar3 != param_1) {
        iVar1 = iVar1 + 1;
        piVar3 = piVar3 + 0xd;
        if (DAT_004f3e30 <= iVar1) {
          return 0;
        }
      }
      if ((&DAT_008dad6e)[iVar1 * 0x34] != '\0') {
        return (&DAT_008dad84)[iVar1 * 0xd] + 1;
      }
    }
  }
  return 0;
}

/* ---- 0x004d0d70  FUN_004d0d70 ---- */
undefined4 FUN_004d0d70(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  switch(param_2) {
  case 1:
    FUN_004d0ed0(param_3,param_4);
    return 0;
  case 2:
    if (param_3 != 0) {
      DAT_004f3e3c = param_3;
    }
    if (param_4 != 0) {
      DAT_004f3e40 = param_4;
      return 0;
    }
    break;
  case 3:
    DAT_008dad40 = param_3;
    return 0;
  case 4:
    DAT_008dad4c = param_3;
    return 0;
  case 5:
    DAT_008dad44 = param_3;
    break;
  default:
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004d0e00  FUN_004d0e00 ---- */
undefined4 FUN_004d0e00(undefined4 param_1,undefined4 param_2,uint *param_3,undefined4 *param_4)

{
  uint uVar1;
  
  switch(param_2) {
  case 1:
    if (param_3 != (uint *)0x0) {
      uVar1 = FUN_004d0eb0(param_4);
      *param_3 = uVar1 & 0xff;
      return 0;
    }
    break;
  case 2:
    if (param_3 != (uint *)0x0) {
      *param_3 = DAT_004f3e3c;
    }
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = DAT_004f3e40;
      return 0;
    }
    break;
  case 3:
    if (param_3 != (uint *)0x0) {
      *param_3 = DAT_008dad40;
      return 0;
    }
    break;
  case 4:
    if (param_3 != (uint *)0x0) {
      *param_3 = DAT_008dad4c;
      return 0;
    }
    break;
  case 5:
    if (param_3 != (uint *)0x0) {
      *param_3 = DAT_008dad44;
    }
    break;
  default:
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004d0eb0  FUN_004d0eb0 ---- */
undefined1 FUN_004d0eb0(byte param_1)

{
  if (param_1 == 0xff) {
    return (undefined1)DAT_004f3e34;
  }
  return (&DAT_008db0e8)[param_1];
}

/* ---- 0x004d0ed0  FUN_004d0ed0 ---- */
void FUN_004d0ed0(byte param_1,byte param_2)

{
  if (param_1 == 0xff) {
    DAT_004f3e34 = (uint)param_2;
  }
  (&DAT_008db0e8)[param_1] = param_2;
  return;
}

/* ---- 0x004d0f00  FUN_004d0f00 ---- */
void FUN_004d0f00(undefined4 param_1,int param_2,undefined4 param_3,undefined1 param_4,
                 undefined1 param_5,int param_6)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  #define local_44 (*(int *)(_frame + (0x60 - 0x44)))
  #define aiStack_40 (*(int (*)[16])(_frame + (0x60 - 0x40)))
  
  iVar1 = DAT_004f3e30 + -1;
  local_44 = 0;
  if (-1 < iVar1) {
    piVar3 = (int *)(iVar1 * 0x34 + 0x8dad68);
    iVar6 = DAT_004f3e30;
    do {
      if (local_44 < *piVar3) {
        local_44 = *piVar3;
      }
      piVar3 = piVar3 + -0xd;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  iVar6 = 10000000;
  if (-1 < iVar1) {
    piVar3 = (int *)(iVar1 * 0x34 + 0x8dad68);
    iVar8 = DAT_004f3e30;
    do {
      iVar2 = *piVar3;
      iVar7 = iVar2 - param_2;
      iVar4 = iVar7;
      if (iVar7 < 0) {
        iVar4 = param_2 - iVar2;
      }
      if (((iVar4 < iVar6) && (param_2 < iVar2)) && (iVar6 = iVar7, local_44 = iVar2, iVar7 < 0)) {
        iVar6 = param_2 - iVar2;
      }
      piVar3 = piVar3 + -0xd;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  if (-1 < iVar1) {
    piVar3 = aiStack_40 + iVar1;
    pcVar5 = &DAT_008dad6e + iVar1 * 0x34;
    iVar6 = DAT_004f3e30;
    do {
      iVar8 = *(int *)(pcVar5 + -6);
      *piVar3 = 0;
      if ((iVar8 == local_44) &&
         (((*pcVar5 == '\0' || (*pcVar5 == '\x03')) || (*(int *)(pcVar5 + 2) <= param_6)))) {
        if (*pcVar5 == '\0') {
          *piVar3 = 0x1000;
        }
        iVar8 = *(int *)(pcVar5 + 2);
        if (iVar8 < param_6) {
          *piVar3 = *piVar3 + 0x800;
        }
        if (iVar8 == param_6) {
          *piVar3 = *piVar3 + 0x400;
        }
        if (*pcVar5 == '\x03') {
          *piVar3 = *piVar3 + 0x200;
        }
        *piVar3 = *piVar3 + *(int *)(pcVar5 + 10) + 1;
      }
      pcVar5 = pcVar5 + -0x34;
      piVar3 = piVar3 + -1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  iVar6 = 0;
  iVar8 = -1;
  if (-1 < iVar1) {
    piVar3 = aiStack_40 + iVar1;
    iVar2 = iVar1;
    do {
      if (iVar6 < *piVar3) {
        iVar6 = *piVar3;
        iVar8 = iVar2;
      }
      iVar2 = iVar2 + -1;
      piVar3 = piVar3 + -1;
    } while (-1 < iVar2);
  }
  if (-1 < iVar8) {
    if (-1 < iVar1) {
      piVar3 = (int *)(iVar1 * 0x34 + 0x8dad78);
      iVar1 = DAT_004f3e30;
      do {
        if (*piVar3 < 0x100) {
          *piVar3 = *piVar3 + 1;
        }
        piVar3 = piVar3 + -0xd;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    iVar6 = iVar8 * 0x34;
    *(undefined4 *)(iVar6 + IMG_ADDR(0x008dad78)) = 0;
    (&DAT_008dad6e)[iVar6] = 0;
    *(undefined1 *)(&DAT_008dad58)[iVar8 * 0xd] = 1;
    *(undefined1 *)((&DAT_008dad58)[iVar8 * 0xd] + 1) = 8;
    iVar1 = (&DAT_008dad58)[iVar8 * 0xd];
    *(undefined1 *)(iVar1 + 2) = 0;
    *(undefined1 *)(iVar1 + 3) = 0;
    *(undefined1 *)(iVar1 + 4) = 0;
    *(undefined1 *)(iVar1 + 5) = 0;
    iVar1 = (&DAT_008dad58)[iVar8 * 0xd];
    *(char *)(iVar1 + 6) = (char)((uint)param_2 >> 0x18);
    *(char *)(iVar1 + 7) = (char)((uint)param_2 >> 0x10);
    *(char *)(iVar1 + 8) = (char)((uint)param_2 >> 8);
    *(char *)(iVar1 + 9) = (char)param_2;
    *(undefined1 *)((&DAT_008dad58)[iVar8 * 0xd] + 10) = 0;
    *(undefined1 *)((&DAT_008dad58)[iVar8 * 0xd] + 0xb) = 0;
    FUN_004c3df0((&DAT_008dad58)[iVar8 * 0xd] + 0xc,param_1,param_2);
    (&DAT_008dad60)[iVar8 * 0xd] = (&DAT_008dad58)[iVar8 * 0xd];
    (&DAT_008dad64)[iVar8 * 0xd] = (&DAT_008dad58)[iVar8 * 0xd] + 0xc;
    (&DAT_008dad7c)[iVar8 * 0xd] = *(int *)(iVar6 + IMG_ADDR(0x008dad68)) + -0xc;
    (&DAT_008dad80)[iVar8 * 0xd] = param_2;
    (&DAT_008dad74)[iVar8 * 0xd] = param_3;
    (&DAT_008dad6c)[iVar6] = param_4;
    (&DAT_008dad6d)[iVar6] = param_5;
    (&DAT_008dad70)[iVar8 * 0xd] = param_6;
    (&DAT_008dad84)[iVar8 * 0xd] = 0;
    (&DAT_008dad6e)[iVar6] = 2;
  }
  return;
}
#undef aiStack_40
#undef local_44


/* ---- 0x004d1180  FUN_004d1180 ---- */
void FUN_004d1180(int param_1,int param_2,undefined4 param_3,int param_4,int param_5,uint param_6,
                 int param_7,int param_8,int param_9,int param_10)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  char *pcVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  #define local_44 (*(int *)(_frame + (0x60 - 0x44)))
  #define aiStack_40 (*(int (*)[16])(_frame + (0x60 - 0x40)))
  
  if (param_8 == 0) {
    if ((param_9 != 1) || (iVar10 = 0, param_10 != 0)) {
      iVar10 = CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(param_1 + 4),*(undefined1 *)(param_1 + 5))
                                 ,*(undefined1 *)(param_1 + 6)),*(undefined1 *)(param_1 + 7));
    }
    iVar11 = 0;
    param_8 = 0;
    if (-1 < DAT_004f3e30 + -1) {
      piVar6 = (int *)((DAT_004f3e30 + -1) * 0x34 + 0x8dad68);
      iVar9 = DAT_004f3e30;
      do {
        if (iVar11 < *piVar6) {
          iVar11 = *piVar6;
        }
        piVar6 = piVar6 + -0xd;
        iVar9 = iVar9 + -1;
        param_8 = iVar11;
      } while (iVar9 != 0);
    }
    iVar11 = 10000000;
    if ((param_6 & 0xc0) == 0x40) {
      if (1 < param_9) {
        FUN_004d1690();
      }
    }
    else if (-1 < DAT_004f3e30 + -1) {
      local_44 = DAT_004f3e30;
      piVar6 = (int *)((DAT_004f3e30 + -1) * 0x34 + 0x8dad68);
      do {
        iVar9 = *piVar6;
        iVar12 = iVar9 - iVar10;
        iVar5 = iVar12;
        if (iVar12 < 0) {
          iVar5 = iVar10 - iVar9;
        }
        if ((iVar5 < iVar11) && ((iVar10 * 2) / 3 < iVar9)) {
          iVar5 = param_2;
          if (1 < param_9) {
            iVar5 = param_2 * 2;
          }
          if ((iVar5 < iVar9) && (iVar11 = iVar12, param_8 = iVar9, iVar12 < 0)) {
            iVar11 = iVar10 - iVar9;
          }
        }
        piVar6 = piVar6 + -0xd;
        local_44 = local_44 + -1;
      } while (local_44 != 0);
    }
    iVar10 = DAT_004f3e30 + -1;
    if (-1 < iVar10) {
      piVar6 = aiStack_40 + iVar10;
      pcVar8 = &DAT_008dad6e + iVar10 * 0x34;
      iVar11 = DAT_004f3e30;
      do {
        iVar9 = *(int *)(pcVar8 + -6);
        *piVar6 = 0;
        if (iVar9 == param_8) {
          if (*pcVar8 == '\0') {
LAB_004d12e0:
            *piVar6 = 0x1000;
          }
          else {
            if ((*pcVar8 != '\x03') && ((int)param_6 < *(int *)(pcVar8 + 2))) goto LAB_004d130e;
            if (*pcVar8 == '\0') goto LAB_004d12e0;
          }
          uVar7 = *(uint *)(pcVar8 + 2);
          if ((int)uVar7 < (int)param_6) {
            *piVar6 = *piVar6 + 0x800;
          }
          if (uVar7 == param_6) {
            *piVar6 = *piVar6 + 0x400;
          }
          if (*pcVar8 == '\x03') {
            *piVar6 = *piVar6 + 0x200;
          }
          *piVar6 = *piVar6 + *(int *)(pcVar8 + 10) + 1;
        }
LAB_004d130e:
        pcVar8 = pcVar8 + -0x34;
        piVar6 = piVar6 + -1;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
    }
    iVar9 = -1;
    iVar11 = -1;
    if (-1 < iVar10) {
      piVar6 = aiStack_40 + iVar10;
      iVar5 = iVar10;
      do {
        iVar12 = *piVar6;
        if ((iVar12 != 0) && (iVar9 < iVar12)) {
          iVar11 = iVar5;
          iVar9 = iVar12;
        }
        iVar5 = iVar5 + -1;
        piVar6 = piVar6 + -1;
      } while (-1 < iVar5);
    }
    if (-1 < iVar11) {
      if (-1 < iVar10) {
        piVar6 = (int *)(iVar10 * 0x34 + 0x8dad78);
        iVar10 = DAT_004f3e30;
        do {
          if (*piVar6 < 0xff) {
            *piVar6 = *piVar6 + 1;
          }
          piVar6 = piVar6 + -0xd;
          iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
      }
      *(int *)(iVar11 * 4 + IMG_ADDR(0x008dad00)) = param_7;
      *(int *)(iVar11 * 4 + IMG_ADDR(0x008da8b0)) = param_9;
      iVar9 = iVar11 * 0x34;
      *(undefined4 *)(iVar11 * 4 + IMG_ADDR(0x008db0a8)) = 0;
      *(undefined4 *)(iVar9 + IMG_ADDR(0x008dad78)) = 0;
      (&DAT_008dad6e)[iVar9] = 0;
      iVar10 = CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(param_1 + 0xc),
                                          *(undefined1 *)(param_1 + 0xd)),
                                 *(undefined1 *)(param_1 + 0xe)),*(undefined1 *)(param_1 + 0xf));
      uVar1 = *(undefined1 *)(iVar10 + 0x15 + param_1);
      uVar2 = *(undefined1 *)(iVar10 + 0x16 + param_1);
      uVar3 = *(undefined1 *)(iVar10 + 0x14 + param_1);
      uVar4 = *(undefined1 *)(iVar10 + 0x17 + param_1);
      if ((param_9 == 1) && (param_10 == 0)) {
        (&DAT_008dad60)[iVar11 * 0xd] = param_1 + 0x10;
        iVar5 = param_2;
      }
      else {
        iVar5 = *(int *)(iVar9 + IMG_ADDR(0x008dad68));
        if (param_2 < *(int *)(iVar9 + IMG_ADDR(0x008dad68))) {
          iVar5 = param_2;
        }
        FUN_004c3df0((&DAT_008dad58)[iVar11 * 0xd],param_1,iVar5);
        (&DAT_008dad60)[iVar11 * 0xd] = (&DAT_008dad58)[iVar11 * 0xd] + 0x10;
        iVar5 = *(int *)(iVar9 + IMG_ADDR(0x008dad68));
      }
      (&DAT_008dad7c)[iVar11 * 0xd] = (iVar5 - iVar10) + -0x18;
      (&DAT_008dad64)[iVar11 * 0xd] = iVar10 + 8 + (&DAT_008dad60)[iVar11 * 0xd];
      (&DAT_008dad80)[iVar11 * 0xd] = (param_2 - iVar10) + -0x18;
      (&DAT_008dad88)[iVar11 * 0xd] = CONCAT31(CONCAT21(CONCAT11(uVar3,uVar1),uVar2),uVar4);
      (&DAT_008dad74)[iVar11 * 0xd] = param_3;
      (&DAT_008dad6c)[iVar9] = 0x7f;
      (&DAT_008dad6d)[iVar9] = 0;
      if ((-1 < param_4) && (param_4 < 0x80)) {
        (&DAT_008dad6c)[iVar9] = (char)param_4;
      }
      if ((-0x80 < param_5) && (param_5 < 0x80)) {
        (&DAT_008dad6d)[iVar9] = (char)param_5;
      }
      (&DAT_008dad70)[iVar11 * 0xd] = param_6;
      (&DAT_008dad84)[iVar11 * 0xd] = 0;
      (&DAT_008dad6e)[iVar9] = 2;
      iVar10 = (&DAT_008dad64)[iVar11 * 0xd];
      uVar7 = CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(iVar10 + -8),*(undefined1 *)(iVar10 + -7)),
                                *(undefined1 *)(iVar10 + -6)),*(undefined1 *)(iVar10 + -5));
      if (uVar7 < 0x5336535b) {
        if (uVar7 == 0x5336535a) {
          (&DAT_008dad6f)[iVar9] = 5;
          return;
        }
        if (uVar7 == 0x53364d5a) {
          (&DAT_008dad6f)[iVar9] = 4;
          return;
        }
LAB_004d153e:
        (&DAT_008dad6f)[iVar9] = 0;
        return;
      }
      if (uVar7 < 0x53443254) {
        if (uVar7 != 0x53443253) {
          (&DAT_008dad6f)[iVar9] = 0;
          return;
        }
      }
      else {
        if (uVar7 == 0x5344364d) {
          (&DAT_008dad6f)[iVar9] = 2;
          return;
        }
        if (uVar7 == 0x53443653) {
          (&DAT_008dad6f)[iVar9] = 3;
          return;
        }
        if (uVar7 != 0x53443853) goto LAB_004d153e;
      }
      (&DAT_008dad6f)[iVar9] = 1;
      return;
    }
  }
  else {
    iVar10 = DAT_004f3e30 + -1;
    if (-1 < iVar10) {
      piVar6 = (int *)(iVar10 * 4 + 0x8da8b0);
      pcVar8 = &DAT_008dad6e + iVar10 * 0x34;
      while ((((*pcVar8 == '\0' || (param_7 != *(int *)(iVar10 * 4 + IMG_ADDR(0x008dad00)))) ||
              (param_8 != *(int *)(iVar10 * 4 + IMG_ADDR(0x008db0a8)) + 1)) || (param_9 != *piVar6))) {
        iVar10 = iVar10 + -1;
        pcVar8 = pcVar8 + -0x34;
        piVar6 = piVar6 + -1;
        if (iVar10 < 0) {
          return;
        }
      }
      *(int *)(iVar10 * 4 + IMG_ADDR(0x008db0a8)) = *(int *)(iVar10 * 4 + IMG_ADDR(0x008db0a8)) + 1;
      iVar11 = (&DAT_008dad7c)[iVar10 * 0xd];
      iVar9 = (int)(&DAT_008dad80)[iVar10 * 0xd] % iVar11;
      if (iVar11 < iVar9 + param_2) {
        FUN_004c3df0(iVar9 + (&DAT_008dad64)[iVar10 * 0xd],param_1,iVar11 - iVar9);
        param_1 = (param_1 - iVar9) + (&DAT_008dad7c)[iVar10 * 0xd];
        iVar11 = (&DAT_008dad64)[iVar10 * 0xd];
        iVar9 = (iVar9 + param_2) - (&DAT_008dad7c)[iVar10 * 0xd];
      }
      else {
        iVar11 = (&DAT_008dad64)[iVar10 * 0xd] + iVar9;
        iVar9 = param_2;
      }
      FUN_004c3df0(iVar11,param_1,iVar9);
      if ((-1 < param_4) && (param_4 < 0x7f)) {
        (&DAT_008dad6c)[iVar10 * 0x34] = (char)param_4;
      }
      if ((-0x80 < param_5) && (param_5 < 0x80)) {
        (&DAT_008dad6d)[iVar10 * 0x34] = (char)param_5;
      }
      (&DAT_008dad80)[iVar10 * 0xd] = (&DAT_008dad80)[iVar10 * 0xd] + param_2;
    }
  }
  return;
}
#undef aiStack_40
#undef local_44


/* ---- 0x004d1690  FUN_004d1690 ---- */
void FUN_004d1690(void)

{
  DAT_008db1f8 = (**(code **)(DAT_008dad48 + 0x18))();
  return;
}

/* ---- 0x004d2340  FUN_004d2340 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004d2340(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  _DAT_008db200 = _DAT_008db200 + (double)CONCAT44(param_2,param_1);
  if (DAT_008db1f8 != 0) {
    iVar1 = (**(code **)(DAT_008dad48 + 0x18))();
    if (DAT_008db1f8 < iVar1) {
      iVar1 = iVar1 - DAT_008db1f8;
      if (iVar1 / 5 < 0x1234dc) {
        DAT_008db1f8 = 0;
        _DAT_008db200 = _DAT_008db200 - (double)iVar1;
      }
    }
  }
  uVar2 = _ftol();
  (**(code **)(DAT_008dad48 + 0x20))(uVar2);
  iVar1 = _ftol();
  _DAT_008db200 = _DAT_008db200 - (double)iVar1;
  return;
}

/* ---- 0x004d23e0  FUN_004d23e0 ---- */
void FUN_004d23e0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  ((code *)FUN_004d2cb0)(param_1,param_2,param_3);
  return;
}

/* ---- 0x004d2400  FUN_004d2400 ---- */
void FUN_004d2400(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  ((code *)FUN_004d2ce0)(param_1,param_2,param_3);
  return;
}

/* ---- 0x004d2420  FUN_004d2420 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004d2420(int *param_1,undefined4 param_2)

{
  PTR_008db41c = param_1;
  DAT_008db430 = param_2;
  (*(code *)*param_1)(s_LECMODULE_insane_dsnd_004f3fec,&PTR_FUN_004f3f68);
  (*(code *)*PTR_008db41c)(s_SNDDRIVER_insane_dsnd_004f3fd4,&PTR_FUN_004f3f78);
  _DAT_008db414 = 0xffffffff;
  _DAT_008db20c = 0xffffffff;
  _DAT_008dcc38 = 0xffffffff;
  _DAT_008db42c = 0xffffffff;
  return 0;
}

/* ---- 0x004d2480  FUN_004d2480 ---- */
void FUN_004d2480(void)

{
  (*(code *)PTR_008db41c[1])(s_SNDDRIVER_insane_dsnd_004f3fd4);
  (*(code *)PTR_008db41c[1])(s_LECMODULE_insane_dsnd_004f3fec);
  return;
}

/* ---- 0x004d24b0  FUN_004d24b0 ---- */
undefined4 FUN_004d24b0(void)

{
  PTR_008db424 = (int *)(*(code *)PTR_008db41c[2])(s_TIMER_clock_004f4054,DAT_008db430);
  if (PTR_008db424 == (int *)0x0) {
    (*(code *)PTR_008db41c[8])(s_DirectSoundDriver_Module__Cannot_004f4018);
    return 0xffffffff;
  }
  DAT_008db208 = (*(code *)PTR_008db41c[2])(s_MEMORY_mixertable_004f4004,DAT_008db430);
  if (DAT_008db208 == 0) {
    (*(code *)PTR_008db41c[8])(s_DirectSoundDriver_Module__Cannot_004f4018);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004d2520  FUN_004d2520 ---- */
void FUN_004d2520(void)

{
  (*(code *)PTR_008db41c[3])(PTR_008db424);
  (*(code *)PTR_008db41c[3])(DAT_008db208);
  return;
}

/* ---- 0x004d2550  FUN_004d2550 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004d2550(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  _DAT_008dcc3c = 0;
  if (param_1 < 0x5622) {
    param_1 = 0x5622;
  }
  iVar1 = FUN_004d2940();
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  iVar1 = ((code *)FUN_004d2d40)(DAT_008db208,4,0x400,0,1,1);
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  DAT_008db410 = param_3;
  DAT_004f3f98 = param_1;
  DAT_008dcc54 = (*(code *)*PTR_008db424)
                           (DSound_FillStreamBuffer,
                            (int)(0x1234dc /
                                 (longlong)((int)(param_1 + (param_1 >> 0x1f & 0x3ffU)) >> 10)),2,0)
  ;
  return 0;
}

/* ---- 0x004d25f0  FUN_004d25f0 ---- */
void FUN_004d25f0(void)

{
  if (DAT_008dcc54 != 0) {
    (*(code *)PTR_008db424[1])(DAT_008dcc54);
  }
  DAT_008dcc54 = 0;
  FUN_004d2d70(DAT_008db208);
  FUN_004d2bf0();
  return;
}

/* ---- 0x004d2630  FUN_004d2630 ---- */
/* WARNING: Removing unreachable block (ram,0x004d2765) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004d2630(uint param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  
  if (DAT_008dcc58 == 0) {
    DAT_008db210 = 0xffffd8f0;
    _DAT_008db214 = 0xffffe4a8;
    _DAT_008db218 = 0xffffe890;
    _DAT_008db21c = 0xffffebb0;
    _DAT_008db220 = 0xffffec78;
    _DAT_008db224 = 0xffffee6c;
    _DAT_008db228 = 0xffffef98;
    _DAT_008db22c = 0xffffeffc;
    DAT_008db230 = 0xfffff060;
    iVar4 = 16000;
    piVar2 = &DAT_008db230;
    do {
      iVar1 = iVar4 + -16000;
      piVar3 = piVar2 + 1;
      iVar4 = iVar4 + 2000;
      *piVar2 = iVar1 / 0x17 + -4000;
      piVar2 = piVar3;
    } while ((int)piVar3 < IMG_ADDR(0x008db290));
    iVar4 = 32000;
    piVar2 = &DAT_008db290;
    do {
      iVar1 = iVar4 + -32000;
      piVar3 = piVar2 + 1;
      iVar4 = iVar4 + 1000;
      *piVar2 = iVar1 / 0x1f + -2000;
      piVar2 = piVar3;
    } while ((int)piVar3 < IMG_ADDR(0x008db310));
    iVar4 = 64000;
    piVar2 = &DAT_008db310;
    do {
      iVar1 = iVar4 + -64000;
      piVar3 = piVar2 + 1;
      iVar4 = iVar4 + 1000;
      *piVar2 = iVar1 / 0x3f + -1000;
      piVar2 = piVar3;
    } while ((int)piVar3 < IMG_ADDR(0x008db410));
    DAT_008dcc58 = 1;
  }
  DAT_004f3f9c = param_1 & 0x7f;
  if (DAT_004f3f9c < 0x80) {
    (**(code_std **)(*PTR_008dcc48 + 0x3c))(PTR_008dcc48,(&DAT_008db210)[DAT_004f3f9c]);
    return;
  }
  (**(code_std **)(*PTR_008dcc48 + 0x3c))(PTR_008dcc48,DAT_008db40c);
  return;
}

/* ---- 0x004d27b0  FUN_004d27b0 ---- */
undefined4 FUN_004d27b0(void)

{
  return DAT_004f3f9c;
}

/* ---- 0x004d27c0  FUN_004d27c0 ---- */
undefined4 FUN_004d27c0(void)

{
  return 0x5622;
}

/* ---- 0x004d2940  FUN_004d2940 ---- */
undefined4 FUN_004d2940(void)

{
  int iVar1;
  undefined4 uVar2;
  
  if (PTR_008dcc40 == (int *)0x0) {
    iVar1 = DirectSoundCreate(0,IMG_ADDR(0x008dcc40),0);
    if (iVar1 != 0) {
      PTR_008dcc40 = (int *)0x0;
      ((code *)Lua_Stub)(s_Cannot_create_DirectSound_object_004f40d0);
      return 0xffffffff;
    }
    iVar1 = *PTR_008dcc40;
    uVar2 = Win_GetMainHwnd();
    iVar1 = (**(code **)(iVar1 + 0x18))(PTR_008dcc40,uVar2);
    if (iVar1 != 0) {
      ((code *)Lua_Stub)(s_DirectSound__Error__08X_while_se_004f4098,iVar1);
      if (iVar1 != 0) {
        return 0xffffffff;
      }
    }
    iVar1 = (**(code_std **)(*PTR_008dcc40 + 0xc))(PTR_008dcc40,&STACK0X(0xffffffe0),&PTR_008dcc44,0);
    if (iVar1 != 0) {
      ((code *)Lua_Stub)(s_DirectSound__Error__08X_while_cr_004f4060,iVar1);
      if (iVar1 != 0) {
        return 0xffffffff;
      }
    }
    iVar1 = (**(code_std **)(*PTR_008dcc44 + 0x38))(PTR_008dcc44,&DAT_004f3fa8);
    if (iVar1 != 0) {
      return 0xffffffff;
    }
    iVar1 = (**(code_std **)(*PTR_008dcc44 + 0x18))(PTR_008dcc44,&DAT_004f3fa0);
    if (iVar1 != 0) {
      return 0xffffffff;
    }
    iVar1 = (**(code_std **)(*PTR_008dcc44 + 0x3c))(PTR_008dcc44,0);
    if (iVar1 != 0) {
      return 0xffffffff;
    }
    FUN_004d2aa0(3);
    DAT_008dcc50 = 1;
  }
  return 0;
}

/* ---- 0x004d2aa0  FUN_004d2aa0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004d2aa0(int param_1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 **ppuVar5;
  int *piVar6;
  #define puStack_30 (*(undefined4 **)(_frame + (0x40 - 0x30)))
  #define ppiStack_2c (*(int ***)(_frame + (0x40 - 0x2c)))
  #define piStack_28 (*(int **)(_frame + (0x40 - 0x28)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x40 - 0x14)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x40 - 0x10)))
  #define iStack_c (*(int *)(_frame + (0x40 - 0xc)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x40 - 0x8)))
  #define puStack_4 (*(undefined **)(_frame + (0x40 - 0x4)))
  
  _DAT_008dcc4c = 1;
  if (PTR_008dcc48 != (int *)0x0) {
    piStack_28 = PTR_008dcc48;
    ppiStack_2c = (int **)0x4d2abd;
    (**(code_std **)(*PTR_008dcc48 + 8))();
  }
  piVar1 = PTR_008dcc40;
  PTR_008dcc48 = (int *)0x0;
  if (param_1 < 3) {
    param_1 = 3;
  }
  if (0x10 < param_1) {
    param_1 = 0x10;
  }
  uStack_14 = 0x14;
  uStack_10 = 0x10080;
  iStack_c = param_1 * 0x1800;
  uStack_8 = 0;
  piStack_28 = (int *)0x0;
  puStack_30 = &uStack_14;
  puStack_4 = &DAT_004f3fc0;
  ppiStack_2c = &PTR_008dcc48;
  DAT_008db420 = param_1;
  iVar2 = (**(code_std **)(*PTR_008dcc40 + 0xc))();
  if (iVar2 == 0) {
    (**(code_std **)(*PTR_008dcc48 + 0x3c))(PTR_008dcc48);
    uVar3 = DAT_008db420 * 0x1800;
    iVar2 = (**(code_std **)(*PTR_008dcc48 + 0x2c))(PTR_008dcc48);
    if (iVar2 == 0) {
      ppuVar5 = &puStack_30;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *ppuVar5 = (undefined4 *)0x0;
        ppuVar5 = ppuVar5 + 1;
      }
      for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(undefined1 *)ppuVar5 = 0;
        ppuVar5 = (undefined4 **)((int)ppuVar5 + 1);
      }
      if (piVar1 != (int *)0x0) {
        piVar6 = piVar1;
        for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
          *piVar6 = 0;
          piVar6 = piVar6 + 1;
        }
        for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
          *(undefined1 *)piVar6 = 0;
          piVar6 = (int *)((int)piVar6 + 1);
        }
      }
      (**(code_std **)(*PTR_008dcc48 + 0x4c))(PTR_008dcc48,&puStack_30,uVar3,piVar1,0);
    }
    (**(code_std **)(*PTR_008dcc48 + 0x30))(PTR_008dcc48,0,0,1);
  }
  _DAT_008dcc4c = 0;
  return;
}
#undef iStack_c
#undef piStack_28
#undef ppiStack_2c
#undef puStack_30
#undef puStack_4
#undef uStack_10
#undef uStack_14
#undef uStack_8


/* ---- 0x004d2bf0  FUN_004d2bf0 ---- */
void FUN_004d2bf0(void)

{
  if (PTR_008dcc48 != (int *)0x0) {
    (**(code_std **)(*PTR_008dcc48 + 8))(PTR_008dcc48);
  }
  PTR_008dcc48 = (int *)0x0;
  if ((PTR_008dcc44 != (int *)0x0) && (DAT_008dcc50 != 0)) {
    (**(code_std **)(*PTR_008dcc44 + 0x3c))(PTR_008dcc44,DAT_004f3fa0);
    (**(code_std **)(*PTR_008dcc44 + 8))(PTR_008dcc44);
    PTR_008dcc44 = (int *)0x0;
    DAT_008dcc50 = 0;
  }
  if (PTR_008dcc40 != (int *)0x0) {
    (**(code_std **)(*PTR_008dcc40 + 8))(PTR_008dcc40);
  }
  PTR_008dcc40 = (int *)0x0;
  return;
}

/* ---- 0x004d2cb0  FUN_004d2cb0 ---- */
undefined8 __fastcall
FUN_004d2cb0(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4,
            uint param_5)

{
  undefined4 in_EAX;
  uint uVar1;
  
  if (param_5 != 0) {
    if ((param_5 & 3) != 0) {
      for (uVar1 = param_5 >> 1; uVar1 != 0; uVar1 = uVar1 - 1) {
        *(undefined2 *)param_3 = *(undefined2 *)param_4;
        param_4 = (undefined4 *)((int)param_4 + 2);
        param_3 = (undefined4 *)((int)param_3 + 2);
      }
      for (uVar1 = (uint)((param_5 & 1) != 0); param_5 = 0, uVar1 != 0; uVar1 = uVar1 - 1) {
        *(undefined1 *)param_3 = *(undefined1 *)param_4;
        param_4 = (undefined4 *)((int)param_4 + 1);
        param_3 = (undefined4 *)((int)param_3 + 1);
      }
    }
    for (param_5 = param_5 >> 2; param_5 != 0; param_5 = param_5 - 1) {
      *param_3 = *param_4;
      param_4 = param_4 + 1;
      param_3 = param_3 + 1;
    }
  }
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004d2ce0  FUN_004d2ce0 ---- */
undefined8 __fastcall
FUN_004d2ce0(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined1 param_4,
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
    for (uVar3 = param_5 >> 1; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(short *)param_3 = (short)uVar1;
      param_3 = (undefined4 *)((int)param_3 + 2);
    }
    for (uVar3 = (uint)((param_5 & 1) != 0); uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined1 *)param_3 = param_4;
      param_3 = (undefined4 *)((int)param_3 + 1);
    }
    return CONCAT44(param_2,&STACK0X(0xfffffff0));
  }
  for (param_5 = param_5 >> 2; param_5 != 0; param_5 = param_5 - 1) {
    *param_3 = uVar1;
    param_3 = param_3 + 1;
  }
  return CONCAT44(param_2,in_EAX);
}

/* ---- 0x004d2d40  FUN_004d2d40 ---- */
void FUN_004d2d40(undefined4 param_1,undefined4 param_2,int param_3)

{
  DAT_004f40f8 = param_2;
  FUN_004d2e80(param_1,2,param_3 * 4,0);
  return;
}

/* ---- 0x004d2d70  FUN_004d2d70 ---- */
void FUN_004d2d70(undefined4 param_1)

{
  FUN_004d2fb0(param_1);
  return;
}

/* ---- 0x004d2d90  FUN_004d2d90 ---- */
void FUN_004d2d90(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
                 undefined4 param_5,undefined4 param_6,int param_7,int param_8)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_8;
  iVar2 = param_8;
  switch(param_8) {
  case 0:
    param_8 = 1;
    iVar1 = 8;
    iVar2 = 1;
    break;
  case 1:
    param_8 = 1;
    iVar1 = 8;
    iVar2 = 2;
    break;
  case 2:
    param_8 = 0;
    iVar1 = 0x10;
    iVar2 = 1;
    break;
  case 3:
    param_8 = 0;
    iVar1 = 0x10;
    iVar2 = 2;
    break;
  case 4:
    param_8 = 1;
    iVar1 = 0x10;
    iVar2 = 1;
    break;
  case 5:
    param_8 = 1;
    iVar1 = 0x10;
    iVar2 = 2;
  }
  Mixer_MixVoice(param_1,param_4 / ((iVar1 >> 3) * iVar2),iVar1,iVar2,param_3,param_2,param_6,
                 (param_7 + 0x7f) / 2,param_8,0);
  return;
}

/* ---- 0x004d2e80  FUN_004d2e80 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004d2e80(undefined4 *param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined1 uVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  int iVar4;
  undefined1 *puVar5;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar4 = 0;
  puVar5 = &DAT_008dcc70;
  do {
    local_4 = 0;
    do {
      fsin((float10)local_4 * (float10)3.1415 * (float10)0.03125);
      uVar1 = _ftol();
      *puVar5 = uVar1;
      puVar5 = puVar5 + 1;
      local_4 = local_4 + 1;
    } while (local_4 < 0x11);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x11);
  DAT_008dcc60 = param_2;
  DAT_008dcd9c = param_3 * 4;
  g_pMixAccum = (int *)(*(code *)*param_1)(DAT_008dcd9c,s_C__grimsrc_libs_lecsmush_insane__004f4158,
                                           0x356);
  if (g_pMixAccum == (int *)0x0) {
    return 0xffffffff;
  }
  _DAT_008dcda0 = param_4;
  puVar3 = (undefined2 *)
           (*(code *)*param_1)(DAT_004f40f8 << 0x10,s_C__grimsrc_libs_lecsmush_insane__004f4158,
                               0x35c);
  DAT_008dcc64 = puVar3;
  if (puVar3 == (undefined2 *)0x0) {
    return 0xffffffff;
  }
  iVar4 = 0;
  if (0 < DAT_004f40f8 << 0xf) {
    do {
      uVar2 = _ftol();
      *puVar3 = uVar2;
      puVar3 = puVar3 + 1;
      iVar4 = iVar4 + 1;
    } while (iVar4 < DAT_004f40f8 * 0x8000);
  }
  return 0;
}
#undef local_4


/* ---- 0x004d2fb0  FUN_004d2fb0 ---- */
undefined4 FUN_004d2fb0(int param_1)

{
  if (DAT_008dcc64 != 0) {
    (**(code **)(param_1 + 4))(DAT_008dcc64,s_C__grimsrc_libs_lecsmush_insane__004f4158,0x379);
  }
  DAT_008dcc64 = 0;
  if (g_pMixAccum != (int *)0x0) {
    (**(code **)(param_1 + 4))(g_pMixAccum,s_C__grimsrc_libs_lecsmush_insane__004f4158,0x37a);
  }
  g_pMixAccum = (int *)0x0;
  return 0;
}

/* ---- 0x004d54b4  FUN_004d54b4 ---- */
float10 FUN_004d54b4(void)

{
  ushort in_FPUStatusWord;
  float10 in_ST0;
  float10 in_ST1;
  float10 extraout_ST1;
  
  do {
    if (DAT_008d0aa0 == 1) {
      in_ST1 = (float10)FUN_004b9b1c();
      in_ST0 = extraout_ST1;
    }
    else {
      in_ST1 = in_ST1 - (float10)(unkint10)(in_ST1 / in_ST0) * in_ST0;
    }
  } while ((in_FPUStatusWord & 0x400) != 0);
  return in_ST1;
}

/* ---- 0x004d56f0  FUN_004d56f0 ---- */
int FUN_004d56f0(void)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_104 (*(uint (*)[65])(_frame + (0x120 - 0x104)))
  
  iVar2 = 0;
  iVar1 = GetCurrentDirectoryA(0x104,(int)local_104);
  if ((iVar1 != 0) && ((char)(local_104[0] >> 8) == ':')) {
    iVar2 = toupper(local_104[0] & 0xff);
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
    param_2 = (char *)malloc(uVar4);
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
undefined4 FUN_004d5de0(int a1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int unaff_ESI;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_004dac00;
  puStack_10 = &LAB_004b1c48;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  local_8 = 0;
  uVar1 = FUN_004d5e35(unaff_ESI);
  return uVar1;
}
#undef local_14
#undef local_8
#undef puStack_10
#undef puStack_c


/* ---- 0x004d5e1c  FUN_004d5e1c ---- */
bool FUN_004d5e1c(void)

{
  int unaff_EBP;
  
  return *(int *)**(undefined4 **)(unaff_EBP + -0x14) == -0x3ffffffb;
}

/* ---- 0x004d5e30  FUN_004d5e30 ---- */
undefined4 FUN_004d5e30(void)

{
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return 0;
}

/* ---- 0x004d5e35  FUN_004d5e35 ---- */
undefined4 __stdcall FUN_004d5e35(int a1)

{
  undefined4 in_EAX;
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return in_EAX;
}

/* ---- 0x004d5e50  FUN_004d5e50 ---- */
void FUN_004d5e50(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  ((code *)FUN_004d5fd0)(param_1,param_2,param_3);
  return;
}

/* ---- 0x004d5e70  FUN_004d5e70 ---- */
void FUN_004d5e70(undefined1 *param_1,undefined4 param_2,int param_3)

{
  undefined1 uVar1;
  
  FUN_004d5eb0(param_2);
  for (; param_3 != 0; param_3 = param_3 + -1) {
    uVar1 = ((code *)FUN_004d5ed0)();
    *param_1 = uVar1;
    param_1 = param_1 + 1;
  }
  Mem_DumpLog();
  return;
}

/* ---- 0x004d5eb0  FUN_004d5eb0 ---- */
void FUN_004d5eb0(int *param_1)

{
  DAT_008dcdbc = 2;
  PTR_008dcdc4 = param_1;
  return;
}

/* ---- 0x004d5ed0  FUN_004d5ed0 ---- */
uint __fastcall FUN_004d5ed0(undefined4 param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  #define local_1 (*(undefined1 *)(_frame + (0x20 - 0x1)))
  
  if (DAT_008dcdbc == 2) {
    DAT_008dcdb8 = (byte)((byte)*PTR_008dcdc4 >> 1) + 1;
    if ((*PTR_008dcdc4 & 1) == 0) {
      DAT_008dcdbc = 0;
      PTR_008dcdc4 = (int *)((int)PTR_008dcdc4 + 1);
    }
    else {
      DAT_008dcdbc = 1;
      DAT_008dcdc0 = *(byte *)((int)PTR_008dcdc4 + 1);
      PTR_008dcdc4 = (int *)((int)PTR_008dcdc4 + 2);
    }
  }
  if (DAT_008dcdbc == 0) {
    uVar1 = (uint)(byte)*PTR_008dcdc4;
    PTR_008dcdc4 = (int *)((int)PTR_008dcdc4 + 1);
  }
  else if (DAT_008dcdbc + -1 == 0) {
    uVar1 = (uint)DAT_008dcdc0;
  }
  else {
    local_1 = (undefined1)((uint)param_1 >> 0x18);
    uVar1 = CONCAT31((int3)((uint)(DAT_008dcdbc + -1) >> 8),local_1);
  }
  DAT_008dcdb8 = DAT_008dcdb8 + -1;
  if (DAT_008dcdb8 == 0) {
    DAT_008dcdbc = 2;
  }
  return uVar1;
}
#undef local_1


/* ---- 0x004d5f70  FUN_004d5f70 ---- */
void FUN_004d5f70(undefined4 param_1)

{
  vsprintf(&DAT_008dcdc8 + DAT_008ddd68 * 200,param_1,&STACK0X(0x00000008));
  if (DAT_008ddd68 == 0x13) {
    DAT_008ddd68 = 0;
  }
  else {
    DAT_008ddd68 = DAT_008ddd68 + 1;
  }
  if (DAT_008ddd6c < 0x13) {
    DAT_008ddd6c = DAT_008ddd6c + 1;
  }
  return;
}

/* ---- 0x004d5fd0  FUN_004d5fd0 ---- */
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

/* ---- 0x004d6030  FUN_004d6030 ---- */
void FUN_004d6030(void)

{
  int unaff_EBP;
  
  Plat_Free(*(void **)(unaff_EBP + -0x10));
  return;
}

/* ---- 0x004d6046  FUN_004d6046 ---- */
void FUN_004d6046(void)

{
  ((code *)__CxxFrameHandler)();
  return;
}

/* ---- 0x004d6050  FUN_004d6050 ---- */
void FUN_004d6050(void)

{
  int unaff_EBP;
  
  Plat_Free(*(void **)(unaff_EBP + 8));
  return;
}

/* ---- 0x004d605b  FUN_004d605b ---- */
void FUN_004d605b(void)

{
  ((code *)__CxxFrameHandler)();
  return;
}

/* ---- 0x004d6070  FUN_004d6070 ---- */
void FUN_004d6070(void)

{
  int unaff_EBP;
  
  Plat_Free(*(void **)(unaff_EBP + 4));
  return;
}

/* ---- 0x004d607b  FUN_004d607b ---- */
void FUN_004d607b(void)

{
  ((code *)__CxxFrameHandler)();
  return;
}

/* ---- 0x004d6090  FUN_004d6090 ---- */
void FUN_004d6090(void)

{
  int unaff_EBP;
  
  Plat_Free(*(void **)(unaff_EBP + -0x1fc));
  return;
}

/* ---- 0x004d609e  FUN_004d609e ---- */
void FUN_004d609e(void)

{
  int unaff_EBP;
  
  Plat_Free(*(void **)(unaff_EBP + -0x1fc));
  return;
}

/* ---- 0x004d60ac  FUN_004d60ac ---- */
void FUN_004d60ac(void)

{
  int unaff_EBP;
  
  Plat_Free(*(void **)(unaff_EBP + -0x1fc));
  return;
}

/* ---- 0x004d60ba  FUN_004d60ba ---- */
void FUN_004d60ba(void)

{
  ((code *)__CxxFrameHandler)();
  return;
}

/* ---- 0x004d60d0  FUN_004d60d0 ---- */
void FUN_004d60d0(void)

{
  ((code *)StateImage_Release)();
  return;
}

/* ---- 0x004d60db  FUN_004d60db ---- */
void FUN_004d60db(void)

{
  ((code *)StateImage_Release)();
  return;
}

/* ---- 0x004d60e9  FUN_004d60e9 ---- */
void FUN_004d60e9(void)

{
  ((code *)__CxxFrameHandler)();
  return;
}

/* ---- 0x004d6100  FUN_004d6100 ---- */
void FUN_004d6100(void)

{
  ((code *)StateImage_Release)();
  return;
}

/* ---- 0x004d610b  FUN_004d610b ---- */
void FUN_004d610b(void)

{
  ((code *)__CxxFrameHandler)();
  return;
}
