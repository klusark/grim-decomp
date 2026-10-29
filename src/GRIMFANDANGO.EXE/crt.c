/* GRIMFANDANGO.EXE :: crt.c
 * functions 0x004ac550 .. 0x004d5ad0 (214 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004ac550  _stricmp ---- */
/* WARNING: Variable defined which should be unmapped: local_14 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char _stricmp(byte *param_1,byte *param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  iVar2 = _DAT_00906c0c;
  if (UINT_008d0b70 == 0) {
    bVar5 = 0xff;
    do {
      do {
        if (bVar5 == 0) {
          return '\0';
        }
        bVar5 = *param_2;
        param_2 = param_2 + 1;
        bVar4 = *param_1;
        param_1 = param_1 + 1;
      } while (bVar4 == bVar5);
      bVar3 = bVar5 + 0xbf + (-((byte)(bVar5 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar4 = bVar4 + 0xbf;
      bVar5 = bVar4 + (-(bVar4 < 0x1a) & 0x20U) + 0x41;
    } while (bVar5 == bVar3);
    cVar6 = (bVar5 < bVar3) * -2 + '\x01';
  }
  else {
    LOCK();
    _DAT_00906c0c = _DAT_00906c0c + 1;
    UNLOCK();
    bVar1 = 0 < (int)UINT_00906c08;
    if (bVar1) {
      LOCK();
      UNLOCK();
      _DAT_00906c0c = iVar2;
      _lock(0x13);
    }
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_004ac5ff;
        bVar5 = *param_2;
        param_2 = param_2 + 1;
        bVar4 = *param_1;
        param_1 = param_1 + 1;
      } while (bVar5 == bVar4);
      bVar4 = ((code *)_tolower_lk)(bVar4,bVar5);
      bVar5 = ((code *)_tolower_lk)();
    } while (bVar4 == bVar5);
    cVar6 = (bVar4 < bVar5) * -2 + '\x01';
LAB_004ac5ff:
    if (bVar1) {
      _unlock(0x13);
    }
    else {
      LOCK();
      _DAT_00906c0c = _DAT_00906c0c + -1;
      UNLOCK();
    }
  }
  return cVar6;
}
#undef local_14


/* ---- 0x004ac620  sprintf ---- */
int __cdecl sprintf(char *buf,char *fmt,...)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  local_18 = (uint)buf;
  local_20 = (uint)buf;
  local_14 = 0x42;
  local_1c = 0x7fffffff;
  iVar1 = _output(&local_20,fmt,&STACK0X(0x0000000c));
  local_1c = local_1c - 1;
  if (-1 < (int)local_1c) {
    *(undefined1 *)local_20 = 0;
    return iVar1;
  }
  _flsbuf(0,&local_20);
  return iVar1;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20


/* ---- 0x004ac6f0  _ftol ---- */
undefined4 __cdecl _ftol(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float10 in_ST0;
  #define local_10 (*(undefined4 *)(_frame + (0x20 - 0x10)))
  
  local_10 = (undefined4)(longlong)ROUND(in_ST0);
  return local_10;
}
#undef local_10


/* ---- 0x004ac720  _snprintf ---- */
int __cdecl _snprintf(char *buf,uint n,char *fmt,...)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 in_stack_00000010;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  local_18 = (uint)buf;
  local_20 = (uint)buf;
  local_1c = n;
  local_14 = 0x42;
  iVar1 = _output(&local_20,fmt,in_stack_00000010);
  local_1c = local_1c - 1;
  if (-1 < (int)local_1c) {
    *(undefined1 *)local_20 = 0;
    return iVar1;
  }
  _flsbuf(0,&local_20);
  return iVar1;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20


/* ---- 0x004ac790  atol ---- */
int atol(byte *param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  
  while( true ) {
    if ((int)UINT_004ed52c < 2) {
      uVar2 = (byte)PTR_DAT_004ed320[(uint)*param_1 * 2] & 8;
    }
    else {
      uVar2 = _isctype(*param_1,8);
    }
    if (uVar2 == 0) break;
    param_1 = param_1 + 1;
  }
  uVar2 = (uint)*param_1;
  pbVar6 = param_1 + 1;
  if ((uVar2 == 0x2d) || (uVar4 = uVar2, uVar2 == 0x2b)) {
    uVar4 = (uint)*pbVar6;
    pbVar6 = param_1 + 2;
  }
  iVar5 = 0;
  while( true ) {
    if ((int)UINT_004ed52c < 2) {
      uVar3 = (byte)PTR_DAT_004ed320[uVar4 * 2] & 4;
    }
    else {
      uVar3 = _isctype(uVar4,4);
    }
    if (uVar3 == 0) break;
    bVar1 = *pbVar6;
    pbVar6 = pbVar6 + 1;
    iVar5 = (uVar4 - 0x30) + iVar5 * 10;
    uVar4 = (uint)bVar1;
  }
  if (uVar2 == 0x2d) {
    iVar5 = -iVar5;
  }
  return iVar5;
}

/* ---- 0x004ac830  atoi ---- */
undefined * __cdecl atoi(uint param_1)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)atol(param_1);
  return puVar1;
}

/* ---- 0x004ac840  strncpy ---- */
uint * strncpy(uint *param_1,uint *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint *puVar5;
  
  if (param_3 == 0) {
    return param_1;
  }
  puVar5 = param_1;
  if (((uint)param_2 & 3) != 0) {
    while( true ) {
      uVar4 = *param_2;
      param_2 = (uint *)((int)param_2 + 1);
      *(char *)puVar5 = (char)uVar4;
      puVar5 = (uint *)((int)puVar5 + 1);
      param_3 = param_3 - 1;
      if (param_3 == 0) {
        return param_1;
      }
      if ((char)uVar4 == '\0') break;
      if (((uint)param_2 & 3) == 0) {
        uVar4 = param_3 >> 2;
        goto joined_r0x004ac87e;
      }
    }
    do {
      if (((uint)puVar5 & 3) == 0) {
        uVar4 = param_3 >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_004ac8bb;
        goto LAB_004ac929;
      }
      *(char *)puVar5 = '\0';
      puVar5 = (uint *)((int)puVar5 + 1);
      param_3 = param_3 - 1;
    } while (param_3 != 0);
    return param_1;
  }
  uVar4 = param_3 >> 2;
  if (uVar4 != 0) {
    do {
      uVar1 = *param_2;
      uVar2 = *param_2;
      param_2 = param_2 + 1;
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *puVar5 = 0;
joined_r0x004ac925:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_004ac929:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          param_3 = param_3 & 3;
          if (param_3 != 0) goto LAB_004ac8bb;
          return param_1;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x004ac925;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x004ac925;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x004ac925;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x004ac87e:
    } while (uVar4 != 0);
    param_3 = param_3 & 3;
    if (param_3 == 0) {
      return param_1;
    }
  }
  do {
    cVar3 = (char)*param_2;
    param_2 = (uint *)((int)param_2 + 1);
    *(char *)puVar5 = cVar3;
    puVar5 = (uint *)((int)puVar5 + 1);
    if (cVar3 == '\0') {
      while (param_3 = param_3 - 1, param_3 != 0) {
LAB_004ac8bb:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      return param_1;
    }
    param_3 = param_3 - 1;
  } while (param_3 != 0);
  return param_1;
}

/* ---- 0x004ac940  strtok ---- */
uint strtok(byte *param_1,byte *param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  #define local_20 (*(byte (*)[32])(_frame + (0x30 - 0x20)))
  
  iVar3 = _getptd();
  pbVar5 = local_20;
  for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
    pbVar5[0] = 0;
    pbVar5[1] = 0;
    pbVar5[2] = 0;
    pbVar5[3] = 0;
    pbVar5 = pbVar5 + 4;
  }
  do {
    bVar1 = *param_2;
    param_2 = param_2 + 1;
    local_20[bVar1 >> 3] = local_20[bVar1 >> 3] | '\x01' << (bVar1 & 7);
  } while (bVar1 != 0);
  if (param_1 == (byte *)0x0) {
    param_1 = *(byte **)(iVar3 + 0x18);
  }
  bVar1 = *param_1;
  bVar2 = local_20[bVar1 >> 3] & (byte)(1 << (bVar1 & 7));
  while ((bVar2 != 0 && (bVar1 != 0))) {
    bVar1 = param_1[1];
    param_1 = param_1 + 1;
    bVar2 = local_20[bVar1 >> 3] & (byte)(1 << (bVar1 & 7));
  }
  bVar1 = *param_1;
  pbVar5 = param_1;
  do {
    if (bVar1 == 0) {
LAB_004aca0f:
      *(byte **)(iVar3 + 0x18) = pbVar5;
      return -(uint)(param_1 != pbVar5) & (uint)param_1;
    }
    if ((local_20[bVar1 >> 3] & (byte)(1 << (bVar1 & 7))) != 0) {
      *pbVar5 = 0;
      pbVar5 = pbVar5 + 1;
      goto LAB_004aca0f;
    }
    bVar1 = pbVar5[1];
    pbVar5 = pbVar5 + 1;
  } while( true );
}
#undef local_20


/* ---- 0x004aca30  entry ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  unsigned char _frame[0x80] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[144] __attribute__((aligned(16)));  /* the original frame below the return address */
  byte bVar1;
  int iVar2;
  undefined *puVar3;
  uint a4;
  byte *a3;
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  int a2;
  #define local_68 (*(uint *)(_frame + (0x80 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0x80 - 0x64)))
  #define local_60 (*(undefined1 (*)[44])(_frame + (0x80 - 0x60)))
  #define local_34 (*(uint *)(_frame + (0x80 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x80 - 0x30)))
  #define local_1c (*(uint *)(_frame + (0x80 - 0x1c)))
  #define local_14 (*(uint *)(_frame + (0x80 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x80 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x80 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x80 - 0x8)))
  byte *pbVar4;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004d8998;
  puStack_10 = &LAB_004b1c48;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_14;
  local_1c = (uint)(_stkneg + 24);
  _DAT_008d0ab4 = GetVersion();
  _DAT_008d0ac0 = _DAT_008d0ab4 >> 8 & 0xff;
  _DAT_008d0abc = _DAT_008d0ab4 & 0xff;
  _DAT_008d0ab8 = _DAT_008d0abc * 0x100 + _DAT_008d0ac0;
  _DAT_008d0ab4 = _DAT_008d0ab4 >> 0x10;
  iVar2 = FUN_004b1c00();
  if (iVar2 == 0) {
    FUN_004acc10(0x1c);
  }
  iVar2 = FUN_004b0c30();
  if (iVar2 == 0) {
    FUN_004acc10(0x10);
  }
  local_8 = 0;
  FUN_004b19f0();
  FUN_004b19e0();
  UINT_00906c18 = GetCommandLineA();
  UINT_008d0aa4 = FUN_004b1380();
  if ((UINT_008d0aa4 == 0) || (UINT_00906c18 == 0)) {
    exit(0xffffffff);
  }
  FUN_004b10d0();
  FUN_004b0fe0();
  FUN_004acd10();
  a3 = (byte *)UINT_00906c18;
  if (*(char *)UINT_00906c18 == '\"') {
    while( true ) {
      pbVar4 = a3;
      a3 = pbVar4 + 1;
      bVar1 = *a3;
      if ((bVar1 == 0x22) || (bVar1 == 0)) break;
      puVar3 = FUN_004b0f80((uint)bVar1);
      if (puVar3 != (undefined *)0x0) {
        a3 = pbVar4 + 2;
      }
    }
    if (*a3 == 0x22) {
      a3 = pbVar4 + 2;
    }
  }
  else {
    for (; 0x20 < *a3; a3 = a3 + 1) {
    }
  }
  for (; (*a3 != 0 && (*a3 < 0x21)); a3 = a3 + 1) {
  }
  local_34 = 0;
  GetStartupInfoA((int)local_60);
  if ((local_34 & 1) == 0) {
    a4 = 10;
  }
  else {
    a4 = local_30 & 0xffff;
  }
  a2 = 0;
  iVar2 = GetModuleHandleA(0);
  puVar3 = Win_WinMain(iVar2,a2,(int)a3,a4);
  exit(puVar3);
  *unaff_FS_OFFSET = local_14;
  return;
}
#undef local_14
#undef local_1c
#undef local_30
#undef local_34
#undef local_60
#undef local_64
#undef local_68
#undef local_8
#undef puStack_10
#undef puStack_c


/* ---- 0x004acbe0  _amsg_exit ---- */
void _amsg_exit(undefined4 param_1)

{
  if (UINT_008d0aac == 1) {
    _FF_MSGBANNER();
  }
  _NMSG_WRITE(param_1);
  (*(code *)PTR__exit_004ed0b0)(0xff);
  return;
}

/* ---- 0x004acc40  printf ---- */
int __cdecl printf(char *fmt,...)

{
  undefined4 uVar1;
  int iVar2;
  
  _lock_file2(1,&DAT_004ed7a0);
  uVar1 = _stbuf(&DAT_004ed7a0);
  iVar2 = _output(&DAT_004ed7a0,fmt,&STACK0X(0x00000008));
  _ftbuf(uVar1,&DAT_004ed7a0);
  _unlock_file2(1,&DAT_004ed7a0);
  return iVar2;
}

/* ---- 0x004acca0  vsprintf ---- */
undefined4 vsprintf(uint param_1,undefined4 param_2,undefined4 param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  local_18 = param_1;
  local_20 = param_1;
  local_14 = 0x42;
  local_1c = 0x7fffffff;
  uVar1 = _output(&local_20,param_2,param_3);
  local_1c = local_1c - 1;
  if (-1 < (int)local_1c) {
    *(undefined1 *)local_20 = 0;
    return uVar1;
  }
  _flsbuf(0,&local_20);
  return uVar1;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20


/* ---- 0x004acd40  exit ---- */
void exit(undefined4 param_1)

{
  doexit(param_1,0,0);
  return;
}

/* ---- 0x004acd60  _exit ---- */
void _exit(undefined4 param_1)

{
  doexit(param_1,1,0);
  return;
}

/* ---- 0x004acd80  doexit ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void doexit(int param_1,int param_2,int param_3)

{
  int a1;
  void **ppvVar1;
  void **ppvVar2;
  int a2;
  
  _lockexit();
  if (UINT_008d0af0 == 1) {
    a2 = param_1;
    a1 = GetCurrentProcess();
    TerminateProcess(a1,a2);
  }
  _DAT_008d0aec = 1;
  DAT_008d0ae8 = (undefined1)param_3;
  if (param_2 == 0) {
    if ((g_pOnExitBegin != (void **)0x0) &&
       (ppvVar2 = g_pOnExitEnd + -1, ppvVar1 = g_pOnExitBegin, g_pOnExitBegin <= ppvVar2)) {
      do {
        if (*ppvVar2 != (code *)0x0) {
          (*(code *)*ppvVar2)();
          ppvVar1 = g_pOnExitBegin;
        }
        ppvVar2 = ppvVar2 + -1;
      } while (ppvVar1 <= ppvVar2);
    }
    _initterm(&DAT_004dd024,&DAT_004dd02c);
  }
  _initterm(&DAT_004dd030,&DAT_004dd038);
  if (param_3 != 0) {
    _unlockexit();
    return;
  }
  UINT_008d0af0 = 1;
  ExitProcess(param_1);
  return;
}

/* ---- 0x004ace40  _lockexit ---- */
void _lockexit(void)

{
  _lock(0xd);
  return;
}

/* ---- 0x004ace50  _unlockexit ---- */
void _unlockexit(void)

{
  _unlock(0xd);
  return;
}

/* ---- 0x004ace60  _initterm ---- */
void _initterm(undefined4 *param_1,undefined4 *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if ((code *)*param_1 != (code *)0x0) {
      (*(code *)*param_1)();
    }
  }
  return;
}

/* ---- 0x004ace80  _onexit ---- */
void * _onexit(void *param_1)

{
  uint uVar1;
  int iVar2;
  void **ppvVar3;
  
  _lockexit();
  uVar1 = _msize(g_pOnExitBegin);
  if (uVar1 < (uint)((int)g_pOnExitEnd + (4 - (int)g_pOnExitBegin))) {
    iVar2 = _msize(g_pOnExitBegin);
    ppvVar3 = (void **)realloc(g_pOnExitBegin,iVar2 + 0x10);
    if (ppvVar3 == (void **)0x0) {
      _unlockexit();
      return (void *)0x0;
    }
    g_pOnExitEnd = ppvVar3 + ((int)g_pOnExitEnd - (int)g_pOnExitBegin >> 2);
    g_pOnExitBegin = ppvVar3;
  }
  *g_pOnExitEnd = param_1;
  g_pOnExitEnd = g_pOnExitEnd + 1;
  _unlockexit();
  return param_1;
}

/* ---- 0x004acf10  atexit ---- */
int atexit(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = _onexit(param_1);
  return (iVar1 != 0) - 1;
}

/* ---- 0x004acf70  malloc ---- */
undefined * __cdecl malloc(uint param_1)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)_nh_malloc(param_1,UINT_008d0ed4);
  return puVar1;
}

/* ---- 0x004acf90  _nh_malloc ---- */
int _nh_malloc(uint param_1,int param_2)

{
  int iVar1;
  
  if (param_1 < 0xffffffe1) {
    if (param_1 == 0) {
      param_1 = 1;
    }
    do {
      if (param_1 < 0xffffffe1) {
        iVar1 = _heap_alloc(param_1);
      }
      else {
        iVar1 = 0;
      }
      if (iVar1 != 0) {
        return iVar1;
      }
      if (param_2 == 0) {
        return 0;
      }
      iVar1 = _callnewh(param_1);
    } while (iVar1 != 0);
  }
  return 0;
}

/* ---- 0x004acfe0  _heap_alloc ---- */
int _heap_alloc(int param_1)

{
  int iVar1;
  uint a3;
  
  a3 = param_1 + 0xfU & 0xfffffff0;
  if (a3 <= UINT_004efa24) {
    _lock(9);
    iVar1 = __sbh_alloc_block(param_1 + 0xfU >> 4);
    _unlock(9);
    if (iVar1 != 0) {
      return iVar1;
    }
  }
  iVar1 = HeapAlloc(UINT_00906ae4,0,a3);
  return iVar1;
}

/* ---- 0x004ad040  free ---- */
void free(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int a3;
  int iVar1;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  a3 = param_1;
  if (param_1 != 0) {
    _lock(9);
    iVar1 = __sbh_find_block(a3,&local_4,&param_1);
    if (iVar1 != 0) {
      __sbh_free_block(local_4,param_1,iVar1);
      _unlock(9);
      return;
    }
    _unlock(9);
    HeapFree(UINT_00906ae4,0,a3);
  }
  return;
}
#undef local_4


/* ---- 0x004ad0b0  realloc ---- */
undefined4 * realloc(undefined4 *param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (param_1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)malloc(param_2);
    return puVar1;
  }
  if (param_2 == 0) {
    free(param_1);
    return (undefined4 *)0x0;
  }
  uVar4 = param_2;
  if (param_2 < 0xffffffe1) {
    if (param_2 == 0) {
      param_2 = 0x10;
      uVar4 = param_2;
    }
    else {
      param_2 = param_2 + 0xf & 0xfffffff0;
      uVar4 = param_2;
    }
  }
  do {
    puVar1 = (undefined4 *)0x0;
    if (uVar4 < 0xffffffe1) {
      _lock(9);
      pbVar2 = (byte *)__sbh_find_block(param_1,&local_4,&local_8);
      if (pbVar2 == (byte *)0x0) {
        _unlock(9);
        puVar1 = (undefined4 *)HeapReAlloc(UINT_00906ae4,0,(int)param_1,uVar4);
      }
      else {
        if (uVar4 < UINT_004efa24) {
          iVar3 = __sbh_resize_block(local_4,local_8,pbVar2,uVar4 >> 4);
          puVar1 = param_1;
          if (iVar3 != 0) goto LAB_004ad1b5;
          puVar1 = (undefined4 *)__sbh_alloc_block(uVar4 >> 4);
          if (puVar1 != (undefined4 *)0x0) {
            uVar5 = (uint)*pbVar2 << 4;
            if (uVar4 <= (uint)*pbVar2 << 4) {
              uVar5 = uVar4;
            }
            puVar6 = param_1;
            puVar7 = puVar1;
            for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
              *puVar7 = *puVar6;
              puVar6 = puVar6 + 1;
              puVar7 = puVar7 + 1;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
              puVar6 = (undefined4 *)((int)puVar6 + 1);
              puVar7 = (undefined4 *)((int)puVar7 + 1);
            }
            __sbh_free_block(local_4,local_8,pbVar2);
            uVar4 = param_2;
            goto LAB_004ad1b5;
          }
LAB_004ad1b9:
          puVar1 = (undefined4 *)HeapAlloc(UINT_00906ae4,0,uVar4);
          if (puVar1 != (undefined4 *)0x0) {
            uVar5 = (uint)*pbVar2 << 4;
            if (uVar4 <= (uint)*pbVar2 << 4) {
              uVar5 = uVar4;
            }
            puVar6 = param_1;
            puVar7 = puVar1;
            for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
              *puVar7 = *puVar6;
              puVar6 = puVar6 + 1;
              puVar7 = puVar7 + 1;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
              puVar6 = (undefined4 *)((int)puVar6 + 1);
              puVar7 = (undefined4 *)((int)puVar7 + 1);
            }
            __sbh_free_block(local_4,local_8,pbVar2);
            uVar4 = param_2;
          }
        }
        else {
LAB_004ad1b5:
          if (puVar1 == (undefined4 *)0x0) goto LAB_004ad1b9;
        }
        _unlock(9);
      }
    }
    if ((puVar1 != (undefined4 *)0x0) || (UINT_008d0ed4 == 0)) {
      return puVar1;
    }
    iVar3 = _callnewh(uVar4);
    if (iVar3 == 0) {
      return (undefined4 *)0x0;
    }
  } while( true );
}
#undef local_4
#undef local_8


/* ---- 0x004ad2c0  _fsopen ---- */
undefined4 _fsopen(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = _getstream();
  if (iVar1 == 0) {
    return 0;
  }
  uVar2 = _openfile(param_1,param_2,param_3,iVar1);
  _unlock_file(iVar1);
  return uVar2;
}

/* ---- 0x004ad300  fopen ---- */
undefined * __cdecl fopen(uint param_1,uint param_2)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)_fsopen(param_1,param_2,0x40);
  return puVar1;
}

/* ---- 0x004ad320  fclose ---- */
undefined4 fclose(int param_1)

{
  undefined4 uVar1;
  
  if ((*(byte *)(param_1 + 0xc) & 0x40) != 0) {
    *(undefined4 *)(param_1 + 0xc) = 0;
    return 0xffffffff;
  }
  _lock_file(param_1);
  uVar1 = _fclose_lk(param_1);
  _unlock_file(param_1);
  return uVar1;
}

/* ---- 0x004ad360  _fclose_lk ---- */
undefined4 _fclose_lk(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0xffffffff;
  if ((*(byte *)(param_1 + 0xc) & 0x83) != 0) {
    uVar2 = _flush(param_1);
    _freebuf(param_1);
    iVar1 = _close(*(undefined4 *)(param_1 + 0x10));
    if (iVar1 < 0) {
      *(undefined4 *)(param_1 + 0xc) = 0;
      return 0xffffffff;
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      free(*(int *)(param_1 + 0x1c));
      *(undefined4 *)(param_1 + 0x1c) = 0;
    }
  }
  *(undefined4 *)(param_1 + 0xc) = 0;
  return uVar2;
}

/* ---- 0x004ad3d0  fread ---- */
undefined4 fread(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  _lock_file(param_4);
  uVar1 = _fread_lk(param_1,param_2,param_3,param_4);
  _unlock_file(param_4);
  return uVar1;
}

/* ---- 0x004ad410  _fread_lk ---- */
uint _fread_lk(undefined4 *param_1,uint param_2,uint param_3,int *param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  piVar1 = param_4;
  uVar6 = param_3 * param_2;
  if (uVar6 == 0) {
    return 0;
  }
  uVar7 = uVar6;
  if ((param_4[3] & 0x10cU) == 0) {
    param_4 = (int *)0x1000;
    uVar5 = 0x1000;
  }
  else {
    uVar5 = param_4[6];
    param_4 = (int *)uVar5;
  }
  do {
    if (((piVar1[3] & 0x10cU) == 0) || (uVar2 = piVar1[1], uVar2 == 0)) {
      if (uVar7 < uVar5) {
        iVar4 = _filbuf(piVar1);
        if (iVar4 == -1) {
          return (uVar6 - uVar7) / param_2;
        }
        *(char *)param_1 = (char)iVar4;
        uVar5 = piVar1[6];
        param_1 = (undefined4 *)((int)param_1 + 1);
        iVar4 = -1;
        param_4 = (int *)uVar5;
      }
      else {
        uVar2 = uVar7;
        if (uVar5 != 0) {
          uVar2 = uVar7 - uVar7 % uVar5;
        }
        iVar3 = _read(piVar1[4],param_1,uVar2);
        if (iVar3 == 0) {
          piVar1[3] = piVar1[3] | 0x10;
          return (uVar6 - uVar7) / param_2;
        }
        if (iVar3 == -1) {
          piVar1[3] = piVar1[3] | 0x20;
          return (uVar6 - uVar7) / param_2;
        }
        iVar4 = -iVar3;
        param_1 = (undefined4 *)((int)param_1 + iVar3);
      }
    }
    else {
      if (uVar7 < uVar2) {
        uVar2 = uVar7;
      }
      iVar4 = -uVar2;
      puVar8 = (undefined4 *)*piVar1;
      puVar9 = param_1;
      for (uVar5 = uVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar9 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar9 = puVar9 + 1;
      }
      for (uVar5 = uVar2 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined1 *)puVar9 = *(undefined1 *)puVar8;
        puVar8 = (undefined4 *)((int)puVar8 + 1);
        puVar9 = (undefined4 *)((int)puVar9 + 1);
      }
      param_1 = (undefined4 *)((int)param_1 + uVar2);
      piVar1[1] = piVar1[1] - uVar2;
      *piVar1 = *piVar1 + uVar2;
      uVar5 = (uint)param_4;
    }
    uVar7 = uVar7 + iVar4;
    if (uVar7 == 0) {
      return param_3;
    }
  } while( true );
}
#undef local_4


/* ---- 0x004ad550  fgets ---- */
char * fgets(char *param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  
  if (param_2 < 1) {
    return (char *)0x0;
  }
  _lock_file(param_3);
  param_2 = param_2 + -1;
  pcVar3 = param_1;
  if (param_2 != 0) {
    while( true ) {
      iVar1 = param_3[1];
      param_3[1] = iVar1 + -1;
      if (iVar1 + -1 < 0) {
        uVar2 = _filbuf(param_3);
      }
      else {
        uVar2 = (uint)*(byte *)*param_3;
        *param_3 = (byte *)*param_3 + 1;
      }
      if (uVar2 == 0xffffffff) break;
      *pcVar3 = (char)uVar2;
      pcVar3 = pcVar3 + 1;
      if (((char)uVar2 == '\n') || (param_2 = param_2 + -1, param_2 == 0)) goto LAB_004ad5a8;
    }
    if (pcVar3 == param_1) {
      _unlock_file(param_3);
      return (char *)0x0;
    }
  }
LAB_004ad5a8:
  *pcVar3 = '\0';
  _unlock_file(param_3);
  return param_1;
}

/* ---- 0x004ad5e0  fwrite ---- */
undefined4 fwrite(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  _lock_file(param_4);
  uVar1 = _fwrite_lk(param_1,param_2,param_3,param_4);
  _unlock_file(param_4);
  return uVar1;
}

/* ---- 0x004ad620  _fwrite_lk ---- */
uint _fwrite_lk(char *param_1,uint param_2,uint param_3,int *param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  piVar1 = param_4;
  uVar5 = param_3 * param_2;
  if (uVar5 == 0) {
    return 0;
  }
  uVar6 = uVar5;
  if ((param_4[3] & 0x10cU) == 0) {
    param_4 = (int *)0x1000;
  }
  else {
    param_4 = (int *)param_4[6];
  }
  do {
    if (((piVar1[3] & 0x108U) == 0) || (uVar2 = piVar1[1], uVar2 == 0)) {
      if (uVar6 < param_4) {
        iVar3 = _flsbuf((int)*param_1,piVar1);
        if (iVar3 == -1) goto LAB_004ad754;
        param_4 = (int *)piVar1[6];
        param_1 = param_1 + 1;
        uVar6 = uVar6 - 1;
        if ((int)param_4 < 1) {
          param_4 = (int *)0x1;
        }
      }
      else {
        if (((piVar1[3] & 0x108U) != 0) && (iVar3 = _flush(piVar1), iVar3 != 0)) {
LAB_004ad754:
          return (uVar5 - uVar6) / param_2;
        }
        uVar2 = uVar6;
        if (param_4 != (int *)0x0) {
          uVar2 = uVar6 - uVar6 % (uint)param_4;
        }
        uVar4 = _write(piVar1[4],param_1,uVar2);
        if (uVar4 == 0xffffffff) {
LAB_004ad739:
          piVar1[3] = piVar1[3] | 0x20;
          return (uVar5 - uVar6) / param_2;
        }
        uVar6 = uVar6 - uVar4;
        param_1 = param_1 + uVar4;
        if (uVar4 < uVar2) goto LAB_004ad739;
      }
    }
    else {
      if (uVar6 < uVar2) {
        uVar2 = uVar6;
      }
      uVar6 = uVar6 - uVar2;
      pcVar7 = param_1;
      pcVar8 = (char *)*piVar1;
      for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar4 = uVar2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar8 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar8 = pcVar8 + 1;
      }
      param_1 = param_1 + uVar2;
      piVar1[1] = piVar1[1] - uVar2;
      *piVar1 = *piVar1 + uVar2;
    }
    if (uVar6 == 0) {
      return param_3;
    }
  } while( true );
}
#undef local_4


/* ---- 0x004ad770  ftell ---- */
undefined4 ftell(undefined4 param_1)

{
  undefined4 uVar1;
  
  _lock_file(param_1);
  uVar1 = _ftell_lk(param_1);
  _unlock_file(param_1);
  return uVar1;
}

/* ---- 0x004ad7a0  _ftell_lk ---- */
uint _ftell_lk(undefined4 *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  char *pcVar2;
  uint uVar3;
  char *pcVar4;
  undefined4 *puVar5;
  char *pcVar6;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = param_1[4];
  if ((int)param_1[1] < 0) {
    param_1[1] = 0;
  }
  local_4 = _lseek(uVar1,0,1);
  if ((int)local_4 < 0) {
    return 0xffffffff;
  }
  uVar3 = param_1[3];
  if ((uVar3 & 0x108) == 0) {
    return local_4 - param_1[1];
  }
  pcVar6 = (char *)*param_1;
  pcVar2 = (char *)param_1[2];
  local_8 = (int)pcVar6 - (int)pcVar2;
  if ((uVar3 & 3) == 0) {
    if ((uVar3 & 0x80) == 0) {
      puVar5 = (undefined4 *)_errno();
      *puVar5 = 0x16;
      return 0xffffffff;
    }
  }
  else {
    pcVar4 = pcVar2;
    if ((*(byte *)((&PTR_00906b00)[(int)uVar1 >> 5] + (uVar1 & 0x1f) * 9 + 1) & 0x80) != 0) {
      for (; pcVar4 < pcVar6; pcVar4 = pcVar4 + 1) {
        if (*pcVar4 == '\n') {
          local_8 = local_8 + 1;
        }
      }
    }
  }
  if (local_4 == 0) {
    return local_8;
  }
  if ((*(byte *)(param_1 + 3) & 1) == 0) goto LAB_004ad917;
  if (param_1[1] == 0) {
    return local_4;
  }
  pcVar6 = pcVar6 + (param_1[1] - (int)pcVar2);
  if ((*(byte *)((&PTR_00906b00)[(int)uVar1 >> 5] + (uVar1 & 0x1f) * 9 + 1) & 0x80) != 0) {
    uVar3 = _lseek(uVar1,0,2);
    if (uVar3 == local_4) {
      pcVar4 = (char *)param_1[2];
      pcVar2 = pcVar4 + (int)pcVar6;
      for (; pcVar4 < pcVar2; pcVar4 = pcVar4 + 1) {
        if (*pcVar4 == '\n') {
          pcVar6 = pcVar6 + 1;
        }
      }
      if ((param_1[3] & 0x2000) != 0) {
LAB_004ad90e:
        pcVar6 = pcVar6 + 1;
      }
    }
    else {
      _lseek(uVar1,local_4,0);
      if (((pcVar6 < (char *)0x201) && ((param_1[3] & 8) != 0)) && ((param_1[3] & 0x400) == 0)) {
        pcVar6 = (char *)0x200;
      }
      else {
        pcVar6 = (char *)param_1[6];
      }
      if ((*(byte *)((&PTR_00906b00)[(int)uVar1 >> 5] + (uVar1 & 0x1f) * 9 + 1) & 4) != 0)
      goto LAB_004ad90e;
    }
  }
  local_4 = local_4 - (int)pcVar6;
LAB_004ad917:
  return local_4 + local_8;
}
#undef local_4
#undef local_8


/* ---- 0x004ad950  fseek ---- */
undefined4 fseek(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  _lock_file(param_1);
  uVar1 = _fseek_lk(param_1,param_2,param_3);
  _unlock_file(param_1);
  return uVar1;
}

/* ---- 0x004ad990  _fseek_lk ---- */
int _fseek_lk(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (((*(uint *)(param_1 + 0xc) & 0x83) != 0) &&
     (((param_3 == 0 || (param_3 == 1)) || (param_3 == 2)))) {
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xffffffef;
    if (param_3 == 1) {
      iVar2 = _ftell_lk(param_1);
      param_2 = param_2 + iVar2;
      param_3 = 0;
    }
    _flush(param_1);
    uVar1 = *(uint *)(param_1 + 0xc);
    if ((uVar1 & 0x80) == 0) {
      if ((((uVar1 & 1) != 0) && ((uVar1 & 8) != 0)) && ((uVar1 & 0x400) == 0)) {
        *(undefined4 *)(param_1 + 0x18) = 0x200;
      }
    }
    else {
      *(uint *)(param_1 + 0xc) = uVar1 & 0xfffffffc;
    }
    iVar2 = _lseek(*(undefined4 *)(param_1 + 0x10),param_2,param_3);
    return (iVar2 != -1) - 1;
  }
  puVar3 = (undefined4 *)_errno();
  *puVar3 = 0x16;
  return -1;
}

/* ---- 0x004ada30  vfprintf ---- */
undefined4 vfprintf(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  _lock_file(param_1);
  uVar1 = _stbuf(param_1);
  uVar2 = _output(param_1,param_2,param_3);
  _ftbuf(uVar1,param_1);
  _unlock_file(param_1);
  return uVar2;
}

/* ---- 0x004ada80  qsort ---- */
void qsort(uint param_1,uint param_2,uint param_3,code *param_4)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  uint uVar3;
  #define local_100 (*(uint *)(_frame + (0x110 - 0x100)))
  #define local_fc (*(uint *)(_frame + (0x110 - 0xfc)))
  #define local_f8 (*(uint *)(_frame + (0x110 - 0xf8)))
  #define local_f4 (*(uint *)(_frame + (0x110 - 0xf4)))
  #define local_f0 (*(undefined1 (*)[116])(_frame + (0x110 - 0xf0)))
  #define local_7c (*(uint *)(_frame + (0x110 - 0x7c)))
  #define local_78 (*(undefined1 (*)[120])(_frame + (0x110 - 0x78)))
  
  if ((param_2 < 2) || (param_3 == 0)) {
    return;
  }
  local_100 = (param_2 - 1) * param_3 + param_1;
  local_fc = (uint)local_f0;
  local_f8 = (uint)local_78;
  local_f4 = 0;
LAB_004adad4:
  uVar1 = (local_100 - param_1) / param_3 + 1;
  if (8 < uVar1) {
    qsort_swap((uVar1 >> 1) * param_3 + param_1,param_1,param_3);
    uVar3 = local_100 + param_3;
    uVar1 = param_1;
LAB_004adb4e:
    uVar1 = uVar1 + param_3;
    if (uVar1 <= local_100) goto code_r0x004adb58;
    goto LAB_004adb68;
  }
  shortsort(param_1,local_100,param_3,param_4);
  goto LAB_004adaf5;
code_r0x004adb58:
  iVar2 = (*param_4)(uVar1,param_1);
  if (iVar2 < 1) goto LAB_004adb4e;
LAB_004adb68:
  do {
    uVar3 = uVar3 - param_3;
    if (uVar3 <= param_1) break;
    iVar2 = (*param_4)(uVar3,param_1);
  } while (-1 < iVar2);
  if (uVar1 <= uVar3) {
    qsort_swap(uVar1,uVar3,param_3);
    goto LAB_004adb4e;
  }
  qsort_swap(param_1,uVar3,param_3);
  if ((int)((uVar3 - param_1) + -1) < (int)(local_100 - uVar1)) {
    if (uVar1 < local_100) {
      *(uint *)local_f8 = uVar1;
      *(uint *)local_fc = local_100;
      local_f4 = local_f4 + 1;
      local_f8 = local_f8 + 4;
      local_fc = local_fc + 4;
    }
    if (param_1 + param_3 < uVar3) {
      local_100 = uVar3 - param_3;
      goto LAB_004adad4;
    }
  }
  else {
    if (param_1 + param_3 < uVar3) {
      *(uint *)local_f8 = param_1;
      *(uint *)local_fc = uVar3 - param_3;
      local_f4 = local_f4 + 1;
      local_f8 = local_f8 + 4;
      local_fc = local_fc + 4;
    }
    param_1 = uVar1;
    if (uVar1 < local_100) goto LAB_004adad4;
  }
LAB_004adaf5:
  local_f4 = local_f4 - 1;
  local_f8 = local_f8 - 4;
  local_fc = local_fc - 4;
  if ((int)local_f4 < 0) {
    return;
  }
  local_100 = *(uint *)local_fc;
  param_1 = *(uint *)local_f8;
  goto LAB_004adad4;
}
#undef local_100
#undef local_78
#undef local_7c
#undef local_f0
#undef local_f4
#undef local_f8
#undef local_fc


/* ---- 0x004adc30  shortsort ---- */
void shortsort(uint param_1,uint param_2,int param_3,code *param_4)

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
    qsort_swap(uVar2,param_2,param_3);
  }
  return;
}

/* ---- 0x004adc90  qsort_swap ---- */
void qsort_swap(undefined1 *param_1,undefined1 *param_2,int param_3)

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

/* ---- 0x004adcc0  bsearch ---- */
uint bsearch(undefined4 param_1,uint param_2,uint param_3,int param_4,code *param_5)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar3 = (param_3 - 1) * param_4 + param_2;
  bVar1 = param_2 <= uVar3;
  uVar4 = param_2;
  param_2 = uVar3;
  if (bVar1) {
    while (uVar3 = param_3 >> 1, uVar3 != 0) {
      uVar5 = uVar3;
      if ((param_3 & 1) == 0) {
        uVar5 = uVar3 - 1;
      }
      uVar5 = param_4 * uVar5 + uVar4;
      iVar2 = (*param_5)(param_1,uVar5);
      if (iVar2 == 0) {
        return uVar5;
      }
      if (iVar2 < 0) {
        param_2 = uVar5 - param_4;
        if ((param_3 & 1) == 0) {
          uVar3 = uVar3 - 1;
        }
      }
      else {
        uVar4 = uVar5 + param_4;
      }
      param_3 = uVar3;
      if (param_2 < uVar4) {
        return 0;
      }
    }
    if (param_3 != 0) {
      iVar2 = (*param_5)(param_1,uVar4);
      return ~-(uint)(iVar2 != 0) & uVar4;
    }
  }
  return 0;
}

/* ---- 0x004add60  memcmp ---- */
uint memcmp(char *param_1,char *param_2,int param_3)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  uVar4 = 0;
  iVar3 = param_3;
  pcVar5 = param_1;
  if (param_3 != 0) {
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    param_3 = param_3 - iVar3;
    do {
      pcVar5 = param_2;
      pcVar6 = param_1;
      if (param_3 == 0) break;
      param_3 = param_3 + -1;
      pcVar6 = param_1 + 1;
      pcVar5 = param_2 + 1;
      cVar2 = *param_1;
      cVar1 = *param_2;
      param_2 = pcVar5;
      param_1 = pcVar6;
    } while (cVar1 == cVar2);
    uVar4 = 0;
    if ((byte)pcVar5[-1] <= (byte)pcVar6[-1]) {
      if (pcVar5[-1] == pcVar6[-1]) {
        return 0;
      }
      uVar4 = 0xfffffffe;
    }
    uVar4 = ~uVar4;
  }
  return uVar4;
}

/* ---- 0x004adda0  sscanf ---- */
int __cdecl sscanf(char *str,char *fmt,...)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  uVar3 = 0xffffffff;
  local_18 = (uint)str;
  local_20 = (uint)str;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *str;
    str = str + 1;
  } while (cVar1 != '\0');
  local_1c = ~uVar3 - 1;
  local_14 = 0x49;
  iVar2 = _input(&local_20,fmt,&STACK0X(0x0000000c));
  return iVar2;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20


/* ---- 0x004ade30  strchr ---- */
/* MSVC 6 C runtime strchr (word-at-a-time scan); _mbschr calls it in SBCS mode */

uint * strchr(uint *param_1,char param_2)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  while (((uint)param_1 & 3) != 0) {
    uVar1 = *param_1;
    if ((char)uVar1 == param_2) {
      return param_1;
    }
    param_1 = (uint *)((int)param_1 + 1);
    if ((char)uVar1 == '\0') {
      return (uint *)0x0;
    }
  }
  while( true ) {
    while( true ) {
      uVar1 = *param_1;
      uVar4 = uVar1 ^ CONCAT22(CONCAT11(param_2,param_2),CONCAT11(param_2,param_2));
      uVar3 = uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff;
      puVar5 = param_1 + 1;
      if (((uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff) & 0x81010100) != 0) break;
      param_1 = puVar5;
      if ((uVar3 & 0x81010100) != 0) {
        if ((uVar3 & 0x1010100) != 0) {
          return (uint *)0x0;
        }
        if ((uVar1 + 0x7efefeff & 0x80000000) == 0) {
          return (uint *)0x0;
        }
      }
    }
    uVar1 = *param_1;
    if ((char)uVar1 == param_2) {
      return param_1;
    }
    if ((char)uVar1 == '\0') {
      return (uint *)0x0;
    }
    cVar2 = (char)(uVar1 >> 8);
    if (cVar2 == param_2) {
      return (uint *)((int)param_1 + 1);
    }
    if (cVar2 == '\0') {
      return (uint *)0x0;
    }
    cVar2 = (char)(uVar1 >> 0x10);
    if (cVar2 == param_2) {
      return (uint *)((int)param_1 + 2);
    }
    if (cVar2 == '\0') break;
    cVar2 = (char)(uVar1 >> 0x18);
    if (cVar2 == param_2) {
      return (uint *)((int)param_1 + 3);
    }
    param_1 = puVar5;
    if (cVar2 == '\0') {
      return (uint *)0x0;
    }
  }
  return (uint *)0x0;
}

/* ---- 0x004adf70  _vsnprintf ---- */
undefined4 _vsnprintf(uint param_1,uint param_2,undefined4 param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  
  local_18 = param_1;
  local_20 = param_1;
  local_1c = param_2;
  local_14 = 0x42;
  uVar1 = _output(&local_20,param_3,&STACK0X(0x00000010));
  local_1c = local_1c - 1;
  if (-1 < (int)local_1c) {
    *(undefined1 *)local_20 = 0;
    return uVar1;
  }
  _flsbuf(0,&local_20);
  return uVar1;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20


/* ---- 0x004adfe0  _strupr ---- */
char * _strupr(char *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  bool bVar8;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pcVar5 = (char *)0x0;
  if (UINT_008d0b70 == 0) {
    pcVar5 = param_1;
    if (*param_1 != '\0') {
      do {
        cVar1 = *param_1;
        if (('`' < cVar1) && (cVar1 < '{')) {
          *param_1 = cVar1 + -0x20;
        }
        pcVar6 = param_1 + 1;
        param_1 = param_1 + 1;
      } while (*pcVar6 != '\0');
      return pcVar5;
    }
  }
  else {
    InterlockedIncrement(IMG_ADDR(0x00906c0c));
    bVar8 = UINT_00906c08 != 0;
    if (bVar8) {
      InterlockedDecrement(IMG_ADDR(0x00906c0c));
      _lock(0x13);
    }
    if (UINT_008d0b70 == 0) {
      if (bVar8) {
        _unlock(0x13);
      }
      else {
        InterlockedDecrement(IMG_ADDR(0x00906c0c));
      }
      pcVar5 = param_1;
      if (*param_1 != '\0') {
        do {
          cVar1 = *param_1;
          if (('`' < cVar1) && (cVar1 < '{')) {
            *param_1 = cVar1 + -0x20;
          }
          pcVar6 = param_1 + 1;
          param_1 = param_1 + 1;
        } while (*pcVar6 != '\0');
        return pcVar5;
      }
    }
    else {
      uVar2 = __crtLCMapStringA(UINT_008d0b70,0x200,param_1,0xffffffff,0,0,0,1);
      if (((uVar2 != 0) && (pcVar5 = malloc(uVar2), pcVar5 != (char *)0x0)) &&
         (iVar3 = __crtLCMapStringA(UINT_008d0b70,0x200,param_1,0xffffffff,pcVar5,uVar2,0,1),
         iVar3 != 0)) {
        uVar2 = 0xffffffff;
        pcVar6 = pcVar5;
        do {
          pcVar7 = pcVar6;
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          pcVar7 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar7;
        } while (cVar1 != '\0');
        uVar2 = ~uVar2;
        pcVar6 = pcVar7 + -uVar2;
        pcVar7 = param_1;
        for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar7 = pcVar7 + 4;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar7 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar7 = pcVar7 + 1;
        }
      }
      if (bVar8) {
        _unlock(0x13);
        free(pcVar5);
        return param_1;
      }
      InterlockedDecrement(IMG_ADDR(0x00906c0c));
      free(pcVar5);
    }
  }
  return param_1;
}
#undef local_4


/* ---- 0x004ae160  strrchr ---- */
/* MSVC 6 C runtime strrchr */

char * strrchr(char *param_1,char param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = -1;
  do {
    pcVar4 = param_1;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar4 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar4;
  } while (cVar1 != '\0');
  iVar2 = -(iVar2 + 1);
  pcVar4 = pcVar4 + -1;
  do {
    pcVar3 = pcVar4;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar3 = pcVar4 + -1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar3;
  } while (param_2 != cVar1);
  pcVar3 = pcVar3 + 1;
  if (*pcVar3 != param_2) {
    pcVar3 = (char *)0x0;
  }
  return pcVar3;
}

/* ---- 0x004ae190  fprintf ---- */
int __cdecl fprintf(void *fp,char *fmt,...)

{
  undefined4 uVar1;
  int iVar2;
  
  _lock_file(fp);
  uVar1 = _stbuf(fp);
  iVar2 = _output(fp,fmt,&STACK0X(0x0000000c));
  _ftbuf(uVar1,fp);
  _unlock_file(fp);
  return iVar2;
}

/* ---- 0x004ae260  wcslen ---- */
int wcslen(short *param_1)

{
  short sVar1;
  short *psVar2;
  
  sVar1 = *param_1;
  psVar2 = param_1;
  while (psVar2 = psVar2 + 1, sVar1 != 0) {
    sVar1 = *psVar2;
  }
  return ((int)psVar2 - (int)param_1 >> 1) + -1;
}

/* ---- 0x004ae280  tolower ---- */
int tolower(int param_1)

{
  bool bVar1;
  
  if (UINT_008d0b70 == 0) {
    if ((0x40 < param_1) && (param_1 < 0x5b)) {
      return param_1 + 0x20;
    }
  }
  else {
    InterlockedIncrement(IMG_ADDR(0x00906c0c));
    bVar1 = UINT_00906c08 != 0;
    if (bVar1) {
      InterlockedDecrement(IMG_ADDR(0x00906c0c));
      _lock(0x13);
    }
    param_1 = _tolower_lk(param_1);
    if (bVar1) {
      _unlock(0x13);
      return param_1;
    }
    InterlockedDecrement(IMG_ADDR(0x00906c0c));
  }
  return param_1;
}

/* ---- 0x004ae310  _tolower_lk ---- */
uint _tolower_lk(uint param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  uVar1 = param_1;
  if (UINT_008d0b70 == 0) {
    if ((0x40 < (int)param_1) && ((int)param_1 < 0x5b)) {
      return param_1 + 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if ((int)UINT_004ed52c < 2) {
        uVar2 = (byte)PTR_DAT_004ed320[param_1 * 2] & 1;
      }
      else {
        uVar2 = _isctype(param_1,1);
      }
      if (uVar2 == 0) {
        return uVar1;
      }
    }
    uVar2 = param_1;
    if ((PTR_DAT_004ed320[((int)uVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      PIECE(param_1,0,2) = (ushort)(byte)uVar1;
      uVar3 = 1;
    }
    else {
      PIECE(param_1,0,2) = CONCAT11((byte)uVar1,(char)(uVar1 >> 8));
      PIECE(param_1,3,1) = SUB41(uVar2,3);
      PIECE(param_1,0,3) = (uint3)(ushort)param_1;
      uVar3 = 2;
    }
    iVar4 = __crtLCMapStringA(UINT_008d0b70,0x100,&param_1,uVar3,&local_8,3,0,1);
    if (iVar4 == 0) {
      return uVar1;
    }
    if (iVar4 == 1) {
      return local_8 & 0xff;
    }
    param_1 = (local_8 >> 8 & 0xff) << 8 | local_8 & 0xff;
  }
  return param_1;
}
#undef local_8


/* ---- 0x004ae540  _CIpow ---- */
float __cdecl _CIpow(void)

{
  float10 in_ST0;
  float10 fVar1;
  float10 in_ST1;
  
  fVar1 = (float10)((float10 (*)(float, float))_pow)((double)in_ST1,(double)in_ST0);
  return (float)fVar1;
}

/* ---- 0x004ae562  _pow ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 _pow(int param_1,uint param_2,int param_3,uint param_4)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined *in_EAX;
  uint uVar1;
  char extraout_CL;
  byte extraout_CL_00;
  char extraout_CL_01;
  undefined *extraout_ECX;
  undefined *puVar2;
  int extraout_ECX_00;
  int iVar3;
  int extraout_ECX_01;
  bool bVar4;
  short in_FPUControlWord;
  float10 extraout_ST0;
  float10 fVar5;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  float10 extraout_ST0_03;
  float10 fVar6;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  float10 extraout_ST1_01;
  float fVar7;
  #define local_78 (*(double *)(_frame + (0x90 - 0x78)))
  
  puVar2 = in_EAX;
  if (in_FPUControlWord != 0x27f) {
    in_EAX = FUN_004b4c15();
    puVar2 = extraout_ECX;
  }
  bVar4 = ((uint)puVar2 & 0x7ff00000) == 0x7ff00000;
  if (bVar4) {
    if (((uint)in_EAX & 0xfffff) == 0 && param_3 == 0) {
      fVar5 = (float10)((code *)FUN_004b4c45)();
      iVar3 = extraout_ECX_01;
      fVar6 = extraout_ST1_01;
      goto LAB_004ae63f;
    }
    fVar5 = (float10)((code *)FUN_004b4c45)();
    fVar6 = extraout_ST1_00;
    if ((param_4 & 0x80000) == 0) {
      iVar3 = extraout_ECX_00 + 1;
      goto LAB_004ae63f;
    }
LAB_004ae60c:
    fVar5 = fVar5 + fVar6;
  }
  else {
    uVar1 = ((code *)FUN_004b4c45)();
    if (!bVar4) {
      if (((uVar1 & 0x7ff00000) != 0) || ((param_2 & 0xfffff) != 0 || param_1 != 0)) {
        fVar6 = extraout_ST0;
        if ((param_2 & 0x80000000) != 0) {
          fVar7 = FUN_004ae735();
          fVar6 = -(float10)fVar7;
          fVar5 = _DAT_004efc00;
          if (extraout_CL_01 == '\0') goto LAB_004ae5da;
        }
        log2(fVar6);
        fVar5 = (float10)FUN_004b4c00();
        if (extraout_CL == '\x01') {
          fVar5 = -fVar5;
        }
        if (UINT_008d0a9c != 0) {
          return fVar5;
        }
        FUN_004b4ce9(IMG_ADDR(0x004ed0c8),0x1d);
        return extraout_ST0_00;
      }
      if ((param_4 & 0x7ff00000) == 0) {
        if ((param_4 & 0xfffff) != 0 || param_3 != 0) {
          FUN_004b4c9e();
          return extraout_ST0_03;
        }
        FUN_004b4c9e();
        return extraout_ST0_02;
      }
      FUN_004ae735();
      if ((param_4 & 0x80000000) == 0) {
        if ((PIECE(param_2,3,1) >> 7 & extraout_CL_00) == 0) {
          return (float10)0;
        }
        FUN_004b4c9e();
        return extraout_ST0_01;
      }
      fVar5 = _DAT_004efba0;
      if ((PIECE(param_2,3,1) >> 7 & extraout_CL_00) != 0) {
        fVar5 = -_DAT_004efba0;
      }
      goto LAB_004ae5da;
    }
    iVar3 = 0;
    fVar5 = extraout_ST0;
    fVar6 = extraout_ST1;
LAB_004ae63f:
    if (((param_2 & 0x7ff00000) == 0x7ff00000) && ((param_2 & 0xfffff) != 0 || param_1 != 0)) {
      if ((param_2 & 0x80000) != 0) goto LAB_004ae60c;
    }
    else if (iVar3 == 0) {
      iVar3 = ((undefined4 (*)(float, float))_pow_special_cases)((double)fVar5,(double)fVar6);
      fVar5 = (float10)local_78;
      if (iVar3 == 0) {
        return (float10)local_78;
      }
      goto LAB_004ae5da;
    }
    fVar5 = fVar5 + fVar6;
  }
LAB_004ae5da:
  if (UINT_008d0a9c != 0) {
    return fVar5;
  }
  fVar5 = (float10)((code *)_pow_except1)();
  return fVar5;
}
#undef local_78


/* ---- 0x004ae760  _strlwr ---- */
char * _strlwr(char *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  bool bVar8;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pcVar5 = (char *)0x0;
  if (UINT_008d0b70 == 0) {
    pcVar5 = param_1;
    if (*param_1 != '\0') {
      do {
        cVar1 = *param_1;
        if (('@' < cVar1) && (cVar1 < '[')) {
          *param_1 = cVar1 + ' ';
        }
        pcVar6 = param_1 + 1;
        param_1 = param_1 + 1;
      } while (*pcVar6 != '\0');
      return pcVar5;
    }
  }
  else {
    InterlockedIncrement(IMG_ADDR(0x00906c0c));
    bVar8 = UINT_00906c08 != 0;
    if (bVar8) {
      InterlockedDecrement(IMG_ADDR(0x00906c0c));
      _lock(0x13);
    }
    if (UINT_008d0b70 == 0) {
      if (bVar8) {
        _unlock(0x13);
      }
      else {
        InterlockedDecrement(IMG_ADDR(0x00906c0c));
      }
      pcVar5 = param_1;
      if (*param_1 != '\0') {
        do {
          cVar1 = *param_1;
          if (('@' < cVar1) && (cVar1 < '[')) {
            *param_1 = cVar1 + ' ';
          }
          pcVar6 = param_1 + 1;
          param_1 = param_1 + 1;
        } while (*pcVar6 != '\0');
        return pcVar5;
      }
    }
    else {
      uVar2 = __crtLCMapStringA(UINT_008d0b70,0x100,param_1,0xffffffff,0,0,0,1);
      if (((uVar2 != 0) && (pcVar5 = malloc(uVar2), pcVar5 != (char *)0x0)) &&
         (iVar3 = __crtLCMapStringA(UINT_008d0b70,0x100,param_1,0xffffffff,pcVar5,uVar2,0,1),
         iVar3 != 0)) {
        uVar2 = 0xffffffff;
        pcVar6 = pcVar5;
        do {
          pcVar7 = pcVar6;
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          pcVar7 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar7;
        } while (cVar1 != '\0');
        uVar2 = ~uVar2;
        pcVar6 = pcVar7 + -uVar2;
        pcVar7 = param_1;
        for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar7 = pcVar7 + 4;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *pcVar7 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar7 = pcVar7 + 1;
        }
      }
      if (bVar8) {
        _unlock(0x13);
        free(pcVar5);
        return param_1;
      }
      InterlockedDecrement(IMG_ADDR(0x00906c0c));
      free(pcVar5);
    }
  }
  return param_1;
}
#undef local_4


/* ---- 0x004ae8e0  toupper ---- */
int toupper(int param_1)

{
  bool bVar1;
  
  if (UINT_008d0b70 == 0) {
    if ((0x60 < param_1) && (param_1 < 0x7b)) {
      return param_1 + -0x20;
    }
  }
  else {
    InterlockedIncrement(IMG_ADDR(0x00906c0c));
    bVar1 = UINT_00906c08 != 0;
    if (bVar1) {
      InterlockedDecrement(IMG_ADDR(0x00906c0c));
      _lock(0x13);
    }
    param_1 = _toupper_lk(param_1);
    if (bVar1) {
      _unlock(0x13);
      return param_1;
    }
    InterlockedDecrement(IMG_ADDR(0x00906c0c));
  }
  return param_1;
}

/* ---- 0x004ae970  _toupper_lk ---- */
uint _toupper_lk(uint param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  uVar1 = param_1;
  if (UINT_008d0b70 == 0) {
    if ((0x60 < (int)param_1) && ((int)param_1 < 0x7b)) {
      return param_1 - 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if ((int)UINT_004ed52c < 2) {
        uVar2 = (byte)PTR_DAT_004ed320[param_1 * 2] & 2;
      }
      else {
        uVar2 = _isctype(param_1,2);
      }
      if (uVar2 == 0) {
        return uVar1;
      }
    }
    uVar2 = param_1;
    if ((PTR_DAT_004ed320[((int)uVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      PIECE(param_1,0,2) = (ushort)(byte)uVar1;
      uVar3 = 1;
    }
    else {
      PIECE(param_1,0,2) = CONCAT11((byte)uVar1,(char)(uVar1 >> 8));
      PIECE(param_1,3,1) = SUB41(uVar2,3);
      PIECE(param_1,0,3) = (uint3)(ushort)param_1;
      uVar3 = 2;
    }
    iVar4 = __crtLCMapStringA(UINT_008d0b70,0x200,&param_1,uVar3,&local_8,3,0,1);
    if (iVar4 == 0) {
      return uVar1;
    }
    if (iVar4 == 1) {
      return local_8 & 0xff;
    }
    param_1 = (local_8 >> 8 & 0xff) << 8 | local_8 & 0xff;
  }
  return param_1;
}
#undef local_8


/* ---- 0x004aea70  fflush ---- */
undefined4 fflush(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    uVar1 = _flushall(0);
    return uVar1;
  }
  _lock_file(param_1);
  uVar1 = _fflush_lk(param_1);
  _unlock_file(param_1);
  return uVar1;
}

/* ---- 0x004aeab0  _fflush_lk ---- */
int _fflush_lk(int param_1)

{
  int iVar1;
  
  iVar1 = _flush(param_1);
  if (iVar1 != 0) {
    return -1;
  }
  if ((*(uint *)(param_1 + 0xc) & 0x4000) != 0) {
    iVar1 = _commit(*(undefined4 *)(param_1 + 0x10));
    return -(uint)(iVar1 != 0);
  }
  return 0;
}

/* ---- 0x004aeaf0  _flush ---- */
undefined4 _flush(int *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar3 = 0;
  if ((((byte)param_1[3] & 3) == 2) && ((param_1[3] & 0x108U) != 0)) {
    iVar4 = *param_1 - param_1[2];
    if (0 < iVar4) {
      iVar2 = _write(param_1[4],param_1[2],iVar4);
      uVar1 = param_1[3];
      if (iVar2 == iVar4) {
        if ((uVar1 & 0x80) != 0) {
          param_1[1] = 0;
          param_1[3] = uVar1 & 0xfffffffd;
          *param_1 = param_1[2];
          return 0;
        }
      }
      else {
        uVar3 = 0xffffffff;
        param_1[3] = uVar1 | 0x20;
      }
    }
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return uVar3;
}

/* ---- 0x004aeb70  _flushall ---- */
uint _flushall(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  int iVar3;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar3 = 0;
  local_4 = 0;
  uVar2 = 0;
  _lock(2);
  if (0 < (int)UINT_00906ae0) {
    do {
      iVar1 = *(int *)(UINT_00905ac4 + iVar3 * 4);
      if ((iVar1 != 0) && ((*(byte *)(iVar1 + 0xc) & 0x83) != 0)) {
        _lock_file2(iVar3,iVar1);
        iVar1 = *(int *)(UINT_00905ac4 + iVar3 * 4);
        if ((*(uint *)(iVar1 + 0xc) & 0x83) != 0) {
          if (param_1 == 1) {
            iVar1 = _fflush_lk(iVar1);
            if (iVar1 != -1) {
              local_4 = local_4 + 1;
            }
          }
          else if (((param_1 == 0) && ((*(uint *)(iVar1 + 0xc) & 2) != 0)) &&
                  (iVar1 = _fflush_lk(iVar1), iVar1 == -1)) {
            uVar2 = 0xffffffff;
          }
        }
        _unlock_file2(iVar3,*(undefined4 *)(UINT_00905ac4 + iVar3 * 4));
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)UINT_00906ae0);
  }
  _unlock(2);
  if (param_1 != 1) {
    local_4 = uVar2;
  }
  return local_4;
}
#undef local_4


/* ---- 0x004aec30  memmove ---- */
undefined4 * memmove(undefined4 *param_1,undefined4 *param_2,uint param_3)

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
          goto switchD_004aede7_caseD_2;
        case 3:
          goto switchD_004aede7_caseD_3;
        }
        goto switchD_004aede7_caseD_1;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto switchD_004aede7_caseD_0;
      case 1:
        goto switchD_004aede7_caseD_1;
      case 2:
        goto switchD_004aede7_caseD_2;
      case 3:
        goto switchD_004aede7_caseD_3;
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
              goto switchD_004aede7_caseD_2;
            case 3:
              goto switchD_004aede7_caseD_3;
            }
            goto switchD_004aede7_caseD_1;
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
              goto switchD_004aede7_caseD_2;
            case 3:
              goto switchD_004aede7_caseD_3;
            }
            goto switchD_004aede7_caseD_1;
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
              goto switchD_004aede7_caseD_2;
            case 3:
              goto switchD_004aede7_caseD_3;
            }
            goto switchD_004aede7_caseD_1;
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
switchD_004aede7_caseD_1:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      return param_1;
    case 2:
switchD_004aede7_caseD_2:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      return param_1;
    case 3:
switchD_004aede7_caseD_3:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
      return param_1;
    }
switchD_004aede7_caseD_0:
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
        goto switchD_004aec65_caseD_2;
      case 3:
        goto switchD_004aec65_caseD_3;
      }
      goto switchD_004aec65_caseD_1;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto switchD_004aec65_caseD_0;
    case 1:
      goto switchD_004aec65_caseD_1;
    case 2:
      goto switchD_004aec65_caseD_2;
    case 3:
      goto switchD_004aec65_caseD_3;
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
            goto switchD_004aec65_caseD_2;
          case 3:
            goto switchD_004aec65_caseD_3;
          }
          goto switchD_004aec65_caseD_1;
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
            goto switchD_004aec65_caseD_2;
          case 3:
            goto switchD_004aec65_caseD_3;
          }
          goto switchD_004aec65_caseD_1;
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
            goto switchD_004aec65_caseD_2;
          case 3:
            goto switchD_004aec65_caseD_3;
          }
          goto switchD_004aec65_caseD_1;
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
switchD_004aec65_caseD_1:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    return param_1;
  case 2:
switchD_004aec65_caseD_2:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
switchD_004aec65_caseD_3:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
switchD_004aec65_caseD_0:
  return param_1;
}

/* ---- 0x004aeff0  _findfirst ---- */
int _findfirst(int param_1,uint *param_2)

{
  unsigned char _frame[0x150] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  char *pcVar7;
  char *pcVar8;
  uint *puVar9;
  #define local_140 (*(uint *)(_frame + (0x150 - 0x140)))
  #define auStack_13c (*(undefined1 (*)[8])(_frame + (0x150 - 0x13c)))
  #define auStack_134 (*(undefined1 (*)[8])(_frame + (0x150 - 0x134)))
  #define auStack_12c (*(undefined1 (*)[12])(_frame + (0x150 - 0x12c)))
  #define uStack_120 (*(uint *)(_frame + (0x150 - 0x120)))
  #define acStack_114 (*(char (*)[276])(_frame + (0x150 - 0x114)))
  
  iVar2 = FindFirstFileA(param_1,(int)&local_140);
  if (iVar2 == -1) {
    iVar2 = GetLastError();
    switch(iVar2) {
    case 2:
    case 3:
    case 0x12:
      puVar3 = (undefined4 *)_errno();
      *puVar3 = 2;
      return -1;
    default:
      puVar3 = (undefined4 *)_errno();
      *puVar3 = 0x16;
      return -1;
    case 8:
      puVar3 = (undefined4 *)_errno();
      *puVar3 = 0xc;
      return -1;
    }
  }
  *param_2 = -(uint)(local_140 != 0x80) & local_140;
  uVar4 = _FileTimeToTime_t(auStack_13c);
  param_2[1] = uVar4;
  uVar4 = _FileTimeToTime_t(auStack_134);
  param_2[2] = uVar4;
  uVar4 = _FileTimeToTime_t(auStack_12c);
  param_2[3] = uVar4;
  uVar4 = 0xffffffff;
  pcVar7 = acStack_114;
  do {
    pcVar8 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  param_2[4] = uStack_120;
  puVar6 = (uint *)(pcVar8 + -uVar4);
  puVar9 = param_2 + 5;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar9 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar9 = puVar9 + 1;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(char *)puVar9 = (char)*puVar6;
    puVar6 = (uint *)((int)puVar6 + 1);
    puVar9 = (uint *)((int)puVar9 + 1);
  }
  return iVar2;
}
#undef acStack_114
#undef auStack_12c
#undef auStack_134
#undef auStack_13c
#undef local_140
#undef uStack_120


/* ---- 0x004af120  _findnext ---- */
undefined4 _findnext(int param_1,uint *param_2)

{
  unsigned char _frame[0x150] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  char *pcVar7;
  char *pcVar8;
  uint *puVar9;
  #define local_140 (*(uint *)(_frame + (0x150 - 0x140)))
  #define auStack_13c (*(undefined1 (*)[8])(_frame + (0x150 - 0x13c)))
  #define auStack_134 (*(undefined1 (*)[8])(_frame + (0x150 - 0x134)))
  #define auStack_12c (*(undefined1 (*)[12])(_frame + (0x150 - 0x12c)))
  #define uStack_120 (*(uint *)(_frame + (0x150 - 0x120)))
  #define acStack_114 (*(char (*)[276])(_frame + (0x150 - 0x114)))
  
  iVar2 = FindNextFileA(param_1,(int)&local_140);
  if (iVar2 == 0) {
    iVar2 = GetLastError();
    switch(iVar2) {
    case 2:
    case 3:
    case 0x12:
      puVar3 = (undefined4 *)_errno();
      *puVar3 = 2;
      return 0xffffffff;
    default:
      puVar3 = (undefined4 *)_errno();
      *puVar3 = 0x16;
      return 0xffffffff;
    case 8:
      puVar3 = (undefined4 *)_errno();
      *puVar3 = 0xc;
      return 0xffffffff;
    }
  }
  *param_2 = -(uint)(local_140 != 0x80) & local_140;
  uVar4 = _FileTimeToTime_t(auStack_13c);
  param_2[1] = uVar4;
  uVar4 = _FileTimeToTime_t(auStack_134);
  param_2[2] = uVar4;
  uVar4 = _FileTimeToTime_t(auStack_12c);
  param_2[3] = uVar4;
  uVar4 = 0xffffffff;
  pcVar7 = acStack_114;
  do {
    pcVar8 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  param_2[4] = uStack_120;
  puVar6 = (uint *)(pcVar8 + -uVar4);
  puVar9 = param_2 + 5;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *puVar9 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar9 = puVar9 + 1;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(char *)puVar9 = (char)*puVar6;
    puVar6 = (uint *)((int)puVar6 + 1);
    puVar9 = (uint *)((int)puVar9 + 1);
  }
  return 0;
}
#undef acStack_114
#undef auStack_12c
#undef auStack_134
#undef auStack_13c
#undef local_140
#undef uStack_120


/* ---- 0x004af240  _findclose ---- */
undefined4 _findclose(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = FindClose(param_1);
  if (iVar1 == 0) {
    puVar2 = (undefined4 *)_errno();
    *puVar2 = 0x16;
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004af270  _FileTimeToTime_t ---- */
undefined4 _FileTimeToTime_t(int *param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  #define local_18 (*(undefined1 (*)[8])(_frame + (0x30 - 0x18)))
  #define uStack_10 (*(undefined2 *)(_frame + (0x30 - 0x10)))
  #define uStack_e (*(undefined2 *)(_frame + (0x30 - 0xe)))
  #define uStack_a (*(undefined2 *)(_frame + (0x30 - 0xa)))
  #define uStack_8 (*(undefined2 *)(_frame + (0x30 - 0x8)))
  #define uStack_6 (*(undefined2 *)(_frame + (0x30 - 0x6)))
  #define uStack_4 (*(undefined2 *)(_frame + (0x30 - 0x4)))
  
  if ((*param_1 != 0) || (param_1[1] != 0)) {
    iVar1 = FileTimeToLocalFileTime((int)param_1,(int)local_18);
    if (iVar1 != 0) {
      iVar1 = FileTimeToSystemTime((int)local_18,(int)&uStack_10);
      if (iVar1 != 0) {
        uVar2 = __loctotime_t(uStack_10,uStack_e,uStack_a,uStack_8,uStack_6,uStack_4,0xffffffff);
        return uVar2;
      }
    }
  }
  return 0xffffffff;
}
#undef local_18
#undef uStack_10
#undef uStack_4
#undef uStack_6
#undef uStack_8
#undef uStack_a
#undef uStack_e


/* ---- 0x004af300  _CallSettingFrame ---- */
void _CallSettingFrame(code *UNRECOVERED_JUMPTABLE)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  *unaff_FS_OFFSET = *(undefined4 *)*unaff_FS_OFFSET;
                    /* WARNING: Could not recover jumptable at 0x004af32b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}
#undef local_8


/* ---- 0x004af350  _UnwindNestedFrames ---- */
undefined * __stdcall _UnwindNestedFrames(int a1,int a2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  undefined *puVar2;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  puVar1 = (undefined4 *)*unaff_FS_OFFSET;
  RtlUnwind(a1,0x4af37c,a2,0);
  *(uint *)(a2 + 4) = *(uint *)(a2 + 4) & 0xfffffffd;
  puVar2 = (undefined *)*unaff_FS_OFFSET;
  *puVar1 = puVar2;
  *unaff_FS_OFFSET = puVar1;
  return puVar2;
}
#undef local_8
#undef local_c


/* ---- 0x004af3b0  __CxxFrameHandler ---- */
undefined4
__CxxFrameHandler(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  uVar1 = ((code *)__InternalCxxFrameHandler)(param_1,param_2,param_3,param_4);
  return uVar1;
}
#undef local_8


/* ---- 0x004af660  _global_unwind2 ---- */
void _global_unwind2(int param_1)

{
  RtlUnwind(param_1,0x4af678,0,0);
  return;
}

/* ---- 0x004af6a2  _local_unwind2 ---- */
void _local_unwind2(int param_1,int param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define uStack_1c (*(undefined4 *)(_frame + (0x30 - 0x1c)))
  #define puStack_18 (*(undefined1 **)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define iStack_10 (*(int *)(_frame + (0x30 - 0x10)))
  
  iStack_10 = param_1;
  puStack_18 = &LAB_004af680;
  uStack_1c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(uint *)(iVar1 + iVar2 * 0xc);
    *(uint *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      _NLG_Notify(0x101);
      (**(code **)(iVar1 + 8 + iVar2 * 0xc))();
    }
  }
  *unaff_FS_OFFSET = uStack_1c;
  return;
}
#undef iStack_10
#undef local_14
#undef puStack_18
#undef uStack_1c


/* ---- 0x004af70a  _unwind_handler ---- */
undefined4 _unwind_handler(void)

{
  int iVar1;
  undefined4 uVar2;
  int *unaff_FS_OFFSET = (int *)TEB_BASE();
  
  uVar2 = 0;
  iVar1 = *unaff_FS_OFFSET;
  if ((*(undefined1 **)(iVar1 + 4) == &LAB_004af680) &&
     (*(int *)(iVar1 + 8) == *(int *)(*(int *)(iVar1 + 0xc) + 0xc))) {
    uVar2 = 1;
  }
  return uVar2;
}

/* ---- 0x004af736  _NLG_Notify ---- */
undefined * __stdcall _NLG_Notify(int a1)

{
  undefined *in_EAX;
  uint unaff_EBP;
  
  UINT_004ed0d8 = *(uint *)(unaff_EBP + 8);
  UINT_004ed0d4 = (uint)in_EAX;
  UINT_004ed0dc = unaff_EBP;
  return in_EAX;
}

/* ---- 0x004af750  isdigit ---- */
uint isdigit(int param_1)

{
  uint uVar1;
  
  if (1 < (int)UINT_004ed52c) {
    uVar1 = _isctype(param_1,4);
    return uVar1;
  }
  return (byte)PTR_DAT_004ed320[param_1 * 2] & 4;
}

/* ---- 0x004af780  isspace ---- */
uint isspace(int param_1)

{
  uint uVar1;
  
  if (1 < (int)UINT_004ed52c) {
    uVar1 = _isctype(param_1,8);
    return uVar1;
  }
  return (byte)PTR_DAT_004ed320[param_1 * 2] & 8;
}

/* ---- 0x004af7e0  _lock ---- */
void _lock(int param_1)

{
  undefined *a1;
  
  if (*(int *)(&DAT_004ed0e0 + param_1 * 4) == 0) {
    a1 = malloc(0x18);
    if (a1 == (undefined *)0x0) {
      _amsg_exit(0x11);
    }
    _lock(0x11);
    if (*(int *)(&DAT_004ed0e0 + param_1 * 4) == 0) {
      InitializeCriticalSection((int)a1);
      *(undefined **)(&DAT_004ed0e0 + param_1 * 4) = a1;
    }
    else {
      ((code *)free)();
    }
    _unlock(0x11);
  }
  EnterCriticalSection(*(int *)(&DAT_004ed0e0 + param_1 * 4));
  return;
}

/* ---- 0x004af860  _unlock ---- */
void _unlock(int param_1)

{
  LeaveCriticalSection(*(int *)(&DAT_004ed0e0 + param_1 * 4));
  return;
}

/* ---- 0x004af880  _lock_file ---- */
void _lock_file(uint param_1)

{
  if ((IMG_ADDR(0x004ed77f) < param_1) && (param_1 < IMG_ADDR(0x004ed9e1))) {
    _lock(((int)(param_1 - 0x4ed780) >> 5) + 0x1c);
    return;
  }
  EnterCriticalSection(param_1 + 0x20);
  return;
}

/* ---- 0x004af8c0  _lock_file2 ---- */
void _lock_file2(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    _lock(param_1 + 0x1c);
    return;
  }
  EnterCriticalSection(param_2 + 0x20);
  return;
}

/* ---- 0x004af8f0  _unlock_file ---- */
void _unlock_file(uint param_1)

{
  if ((IMG_ADDR(0x004ed77f) < param_1) && (param_1 < IMG_ADDR(0x004ed9e1))) {
    _unlock(((int)(param_1 - 0x4ed780) >> 5) + 0x1c);
    return;
  }
  LeaveCriticalSection(param_1 + 0x20);
  return;
}

/* ---- 0x004af930  _unlock_file2 ---- */
void _unlock_file2(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    _unlock(param_1 + 0x1c);
    return;
  }
  LeaveCriticalSection(param_2 + 0x20);
  return;
}

/* ---- 0x004af960  _flsbuf ---- */
uint _flsbuf(uint param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  
  piVar4 = param_2;
  uVar1 = param_2[3];
  uVar2 = param_2[4];
  if (((uVar1 & 0x82) == 0) || ((uVar1 & 0x40) != 0)) {
LAB_004afa83:
    param_2[3] = uVar1 | 0x20;
    return 0xffffffff;
  }
  iVar7 = 0;
  if ((uVar1 & 1) != 0) {
    param_2[1] = 0;
    if ((uVar1 & 0x10) == 0) goto LAB_004afa83;
    *param_2 = param_2[2];
    param_2[3] = uVar1 & 0xfffffffe;
  }
  uVar1 = param_2[3];
  param_2[1] = 0;
  param_2[3] = uVar1 & 0xffffffef | 2;
  if ((uVar1 & 0x10c) == 0) {
    if ((param_2 == (int *)&DAT_004ed7a0) || (param_2 == (int *)&DAT_004ed7c0)) {
      iVar5 = _isatty(uVar2);
      if (iVar5 != 0) goto LAB_004af9d3;
    }
    _getbuf(piVar4);
  }
LAB_004af9d3:
  if ((piVar4[3] & 0x108U) == 0) {
    iVar5 = 1;
    iVar7 = _write(uVar2,&param_1,1);
  }
  else {
    iVar3 = piVar4[2];
    iVar5 = *piVar4 - iVar3;
    *piVar4 = iVar3 + 1;
    piVar4[1] = piVar4[6] + -1;
    if (iVar5 < 1) {
      if (uVar2 == 0xffffffff) {
        piVar6 = (int *)&DAT_004ed6c8;
      }
      else {
        piVar6 = (&PTR_00906b00)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 9;
      }
      if ((*(byte *)(piVar6 + 1) & 0x20) != 0) {
        _lseek(uVar2,0,2);
      }
      *(undefined1 *)piVar4[2] = (undefined1)param_1;
    }
    else {
      iVar7 = _write(uVar2,iVar3,iVar5);
      *(undefined1 *)piVar4[2] = (undefined1)param_1;
    }
  }
  if (iVar7 != iVar5) {
    piVar4[3] = piVar4[3] | 0x20;
    return 0xffffffff;
  }
  return param_1 & 0xff;
}

/* ---- 0x004afa90  _output ---- */
/* printf-family formatting core */

uint _output(undefined4 param_1,char *param_2,uint *param_3)

{
  unsigned char _frame[0x260] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  short sVar1;
  uint uVar2;
  undefined4 uVar3;
  short *psVar4;
  uint *puVar5;
  char *pcVar6;
  undefined *puVar7;
  undefined *a1;
  int iVar8;
  uint uVar9;
  int extraout_EDX;
  char cVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  undefined2 *puVar13;
  int iVar14;
  ulonglong uVar15;
  #define local_24c (*(uint *)(_frame + (0x260 - 0x24c)))
  #define local_248 (*(uint *)(_frame + (0x260 - 0x248)))
  #define local_244 (*(uint *)(_frame + (0x260 - 0x244)))
  #define local_240 (*(uint *)(_frame + (0x260 - 0x240)))
  #define local_23a (*(undefined1 *)(_frame + (0x260 - 0x23a)))
  #define local_239 (*(char *)(_frame + (0x260 - 0x239)))
  #define local_238 (*(uint *)(_frame + (0x260 - 0x238)))
  #define local_234 (*(uint *)(_frame + (0x260 - 0x234)))
  #define local_230 (*(uint *)(_frame + (0x260 - 0x230)))
  #define local_22c (*(uint *)(_frame + (0x260 - 0x22c)))
  #define local_228 (*(uint *)(_frame + (0x260 - 0x228)))
  #define local_224 (*(uint *)(_frame + (0x260 - 0x224)))
  #define local_220 (*(uint *)(_frame + (0x260 - 0x220)))
  #define local_21c (*(uint *)(_frame + (0x260 - 0x21c)))
  #define local_218 (*(uint *)(_frame + (0x260 - 0x218)))
  #define local_214 (*(undefined1 (*)[4])(_frame + (0x260 - 0x214)))
  #define local_210 (*(uint *)(_frame + (0x260 - 0x210)))
  #define local_20c (*(uint *)(_frame + (0x260 - 0x20c)))
  #define local_204 (*(uint *)(_frame + (0x260 - 0x204)))
  #define local_200 (*(char *)(_frame + (0x260 - 0x200)))
  #define auStack_1ff (*(undefined1 (*)[510])(_frame + (0x260 - 0x1ff)))
  #define uStack_1 (*(undefined1 *)(_frame + (0x260 - 0x1)))
  
  local_220 = 0;
  puVar12 = (undefined1 *)0x0;
  local_240 = 0;
  cVar10 = *param_2;
  local_21c = CONCAT31(PIECE(local_21c,1,3),cVar10);
  pcVar6 = param_2;
  do {
    if ((cVar10 == '\0') || (param_2 = pcVar6 + 1, (int)local_240 < 0)) {
      return local_240;
    }
    if ((cVar10 < ' ') || ('x' < cVar10)) {
      uVar2 = 0;
    }
    else {
      uVar2 = (byte)(&DAT_004d89c8)[cVar10] & 0xf;
    }
    local_220 = (int)(char)(&DAT_004d89e8)[uVar2 * 8 + local_220] >> 4;
    switch(local_220) {
    case 0:
switchD_004afb0d_caseD_0:
      local_230 = 0;
      if ((PTR_DAT_004ed320[(local_21c & 0xff) * 2 + 1] & 0x80) != 0) {
        write_char((int)cVar10,param_1,&local_240);
        cVar10 = *param_2;
        param_2 = pcVar6 + 2;
      }
      write_char((int)cVar10,param_1,&local_240);
      break;
    case 1:
      local_218 = 0;
      local_228 = 0;
      local_234 = 0;
      local_238 = 0;
      local_24c = 0;
      local_244 = 0xffffffff;
      local_230 = 0;
      break;
    case 2:
      switch(cVar10) {
      case ' ':
        local_24c = local_24c | 2;
        break;
      case '#':
        local_24c = local_24c | 0x80;
        break;
      case '+':
        local_24c = local_24c | 1;
        break;
      case '-':
        local_24c = local_24c | 4;
        break;
      case '0':
        local_24c = local_24c | 8;
      }
      break;
    case 3:
      if (cVar10 == '*') {
        local_234 = get_int_arg(&param_3);
        if ((int)local_234 < 0) {
          local_24c = local_24c | 4;
          local_234 = -local_234;
        }
      }
      else {
        local_234 = cVar10 + -0x30 + local_234 * 10;
      }
      break;
    case 4:
      local_244 = 0;
      break;
    case 5:
      if (cVar10 == '*') {
        local_244 = get_int_arg(&param_3);
        if ((int)local_244 < 0) {
          local_244 = 0xffffffff;
        }
      }
      else {
        local_244 = cVar10 + -0x30 + local_244 * 10;
      }
      break;
    case 6:
      switch(cVar10) {
      case 'I':
        if ((*param_2 != '6') || (pcVar6[2] != '4')) {
          local_220 = 0;
          goto switchD_004afb0d_caseD_0;
        }
        param_2 = pcVar6 + 3;
        local_24c = local_24c | 0x8000;
        break;
      case 'h':
        local_24c = local_24c | 0x20;
        break;
      case 'l':
        local_24c = local_24c | 0x10;
        break;
      case 'w':
        local_24c = local_24c | 0x800;
      }
      break;
    case 7:
      switch(cVar10) {
      case 'C':
        if ((local_24c & 0x830) == 0) {
          local_24c = local_24c | 0x800;
        }
      case 'c':
        if ((local_24c & 0x810) == 0) {
          local_200 = get_int_arg(&param_3);
          puVar12 = (undefined1 *)0x1;
        }
        else {
          uVar3 = get_int64_arg(&param_3);
          puVar12 = (undefined1 *)wctomb(&local_200,uVar3);
          if ((int)puVar12 < 0) {
            local_248 = (uint)&local_200;
            local_228 = 1;
            break;
          }
        }
        local_248 = (uint)&local_200;
        break;
      case 'E':
      case 'G':
        local_218 = 1;
        cVar10 = cVar10 + ' ';
      case 'e':
      case 'f':
      case 'g':
        local_248 = (uint)&local_200;
        if ((int)local_244 < 0) {
          local_244 = 6;
        }
        else if ((local_244 == 0) && (cVar10 == 'g')) {
          local_244 = 1;
        }
        local_210 = *param_3;
        local_20c = param_3[1];
        param_3 = param_3 + 2;
        (*(code *)PTR_FUN_004ed308)(&local_210,&local_200,(int)cVar10,local_244,local_218);
        if (((local_24c & 0x80) != 0) && (local_244 == 0)) {
          (*(code *)PTR_FUN_004ed314)(&local_200);
        }
        if ((cVar10 == 'g') && ((local_24c & 0x80) == 0)) {
          (*(code *)PTR_FUN_004ed30c)(&local_200);
        }
        uVar2 = local_24c | 0x40;
        if (local_200 == '-') {
          local_248 = (uint)auStack_1ff;
          uVar2 = local_24c | 0x140;
        }
        local_24c = uVar2;
        uVar2 = 0xffffffff;
        pcVar6 = (char *)local_248;
        do {
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          cVar10 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar10 != '\0');
        puVar12 = (undefined1 *)(~uVar2 - 1);
        break;
      case 'S':
        if ((local_24c & 0x830) == 0) {
          local_24c = local_24c | 0x800;
        }
      case 's':
        uVar2 = 0x7fffffff;
        if (local_244 != 0xffffffff) {
          uVar2 = local_244;
        }
        local_248 = get_int_arg(&param_3);
        if ((local_24c & 0x810) == 0) {
          psVar4 = (short *)local_248;
          if ((short *)local_248 == (short *)0x0) {
            psVar4 = (short *)PTR_DAT_004ed2fc;
            local_248 = (uint)PTR_DAT_004ed2fc;
          }
          for (; (uVar2 != 0 && (uVar2 = uVar2 - 1, (char)*psVar4 != '\0'));
              psVar4 = (short *)((int)psVar4 + 1)) {
          }
          puVar12 = (undefined1 *)((int)psVar4 - local_248);
        }
        else {
          if ((short *)local_248 == (short *)0x0) {
            local_248 = (uint)PTR_DAT_004ed300;
          }
          local_230 = 1;
          for (psVar4 = (short *)local_248; (uVar2 != 0 && (uVar2 = uVar2 - 1, *psVar4 != 0));
              psVar4 = psVar4 + 1) {
          }
          puVar12 = (undefined1 *)((int)((int)psVar4 - local_248) >> 1);
        }
        break;
      case 'X':
        goto switchD_004afd21_caseD_58;
      case 'Z':
        psVar4 = (short *)get_int_arg(&param_3);
        if ((psVar4 == (short *)0x0) || (local_248 = *(uint *)(psVar4 + 2), local_248 == 0)) {
          uVar2 = 0xffffffff;
          local_248 = (uint)PTR_DAT_004ed2fc;
          pcVar6 = PTR_DAT_004ed2fc;
          do {
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            cVar10 = *pcVar6;
            pcVar6 = pcVar6 + 1;
          } while (cVar10 != '\0');
          puVar12 = (undefined1 *)(~uVar2 - 1);
        }
        else if ((local_24c & 0x800) == 0) {
          puVar12 = (undefined1 *)(int)*psVar4;
          local_230 = 0;
        }
        else {
          local_230 = 1;
          puVar12 = (undefined1 *)((uint)(int)*psVar4 >> 1);
        }
        break;
      case 'd':
      case 'i':
        local_22c = 10;
        local_24c = local_24c | 0x40;
        goto LAB_004b0057;
      case 'n':
        puVar5 = (uint *)get_int_arg(&param_3);
        if ((local_24c & 0x20) == 0) {
          local_228 = 1;
          *puVar5 = local_240;
        }
        else {
          local_228 = 1;
          *(undefined2 *)puVar5 = (undefined2)local_240;
        }
        break;
      case 'o':
        local_22c = 8;
        if ((local_24c & 0x80) != 0) {
          local_24c = local_24c | 0x200;
        }
        goto LAB_004b0057;
      case 'p':
        local_244 = 8;
switchD_004afd21_caseD_58:
        local_224 = 7;
LAB_004b0012:
        local_22c = 0x10;
        if ((local_24c & 0x80) != 0) {
          local_23a = 0x30;
          local_239 = (char)local_224 + 'Q';
          local_238 = 2;
        }
        goto LAB_004b0057;
      case 'u':
        local_22c = 10;
LAB_004b0057:
        if ((local_24c & 0x8000) == 0) {
          if ((local_24c & 0x20) == 0) {
            if ((local_24c & 0x40) == 0) {
              uVar2 = get_int_arg(&param_3);
              uVar15 = (ulonglong)uVar2;
            }
            else {
              iVar14 = get_int_arg(&param_3);
              uVar15 = (ulonglong)iVar14;
            }
          }
          else if ((local_24c & 0x40) == 0) {
            uVar2 = get_int_arg(&param_3);
            uVar15 = (ulonglong)(uVar2 & 0xffff);
          }
          else {
            sVar1 = get_int_arg(&param_3);
            uVar15 = (ulonglong)(int)sVar1;
          }
        }
        else {
          uVar15 = get_short_arg(&param_3);
        }
        if ((((local_24c & 0x40) != 0) && ((longlong)uVar15 < 0x100000000)) &&
           ((longlong)uVar15 < 0)) {
          uVar15 = CONCAT44(-((int)(uVar15 >> 0x20) + (uint)((int)uVar15 != 0)),-(int)uVar15);
          local_24c = local_24c | 0x100;
        }
        iVar14 = (int)(uVar15 >> 0x20);
        a1 = (undefined *)uVar15;
        if ((local_24c & 0x8000) == 0) {
          iVar14 = 0;
        }
        if ((int)local_244 < 0) {
          local_244 = 1;
        }
        else {
          local_24c = local_24c & 0xfffffff7;
        }
        local_248 = (uint)REGISTER0X(0x00000010);
        if (a1 == (undefined *)0x0 && iVar14 == 0) {
          local_238 = 0;
        }
        while( true ) {
          uVar2 = local_22c;
          pcVar6 = (char *)(local_248 + -1);
          uVar9 = local_244 - 1;
          if (((int)local_244 < 1) && (a1 == (undefined *)0x0 && iVar14 == 0)) break;
          local_204 = (int)local_22c >> 0x1f;
          puVar7 = _aullrem((int)a1,iVar14,local_22c,local_204);
          puVar7 = puVar7 + 0x30;
          a1 = _aulldiv((int)a1,iVar14,uVar2,local_204);
          if (0x39 < (int)puVar7) {
            puVar7 = puVar7 + local_224;
          }
          *pcVar6 = (char)puVar7;
          local_244 = uVar9;
          iVar14 = extraout_EDX;
          local_248 = (uint)pcVar6;
        }
        puVar12 = &uStack_1 + -(int)pcVar6;
        local_244 = uVar9;
        if (((local_24c & 0x200) != 0) &&
           ((*(char *)local_248 != '0' || (puVar12 == (undefined1 *)0x0)))) {
          puVar12 = &STACK0X(0x00000000) + -(int)pcVar6;
          *pcVar6 = '0';
          local_248 = (uint)pcVar6;
        }
        break;
      case 'x':
        local_224 = 0x27;
        goto LAB_004b0012;
      }
      if (local_228 == 0) {
        if ((local_24c & 0x40) != 0) {
          if ((local_24c & 0x100) == 0) {
            if ((local_24c & 1) == 0) {
              if ((local_24c & 2) == 0) goto LAB_004b01ef;
              local_23a = 0x20;
            }
            else {
              local_23a = 0x2b;
            }
          }
          else {
            local_23a = 0x2d;
          }
          local_238 = 1;
        }
LAB_004b01ef:
        iVar14 = (local_234 - (int)puVar12) - local_238;
        if ((local_24c & 0xc) == 0) {
          write_multi_char(0x20,iVar14,param_1,&local_240);
        }
        write_string(&local_23a,local_238,param_1,&local_240);
        if (((local_24c & 8) != 0) && ((local_24c & 4) == 0)) {
          write_multi_char(0x30,iVar14,param_1,&local_240);
        }
        if ((local_230 == 0) ||
           (puVar13 = (undefined2 *)local_248, puVar11 = puVar12, (int)puVar12 < 1)) {
          write_string(local_248,puVar12,param_1,&local_240);
        }
        else {
          do {
            puVar11 = puVar11 + -1;
            iVar8 = wctomb(local_214,*puVar13);
            if (iVar8 < 1) break;
            write_string(local_214,iVar8,param_1,&local_240);
            puVar13 = puVar13 + 1;
          } while (puVar11 != (undefined1 *)0x0);
        }
        if ((local_24c & 4) != 0) {
          write_multi_char(0x20,iVar14,param_1,&local_240);
        }
      }
    }
    cVar10 = *param_2;
    local_21c = CONCAT31(PIECE(local_21c,1,3),cVar10);
    pcVar6 = param_2;
  } while( true );
}
#undef auStack_1ff
#undef local_200
#undef local_204
#undef local_20c
#undef local_210
#undef local_214
#undef local_218
#undef local_21c
#undef local_220
#undef local_224
#undef local_228
#undef local_22c
#undef local_230
#undef local_234
#undef local_238
#undef local_239
#undef local_23a
#undef local_240
#undef local_244
#undef local_248
#undef local_24c
#undef uStack_1


/* ---- 0x004b0420  write_char ---- */
void write_char(uint param_1,int *param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = param_2[1];
  param_2[1] = iVar1 + -1;
  if (iVar1 + -1 < 0) {
    param_1 = _flsbuf(param_1,param_2);
  }
  else {
    *(char *)*param_2 = (char)param_1;
    param_1 = param_1 & 0xff;
    *param_2 = *param_2 + 1;
  }
  if (param_1 == 0xffffffff) {
    *param_3 = -1;
    return;
  }
  *param_3 = *param_3 + 1;
  return;
}

/* ---- 0x004b0470  write_multi_char ---- */
void write_multi_char(undefined4 param_1,int param_2,undefined4 param_3,int *param_4)

{
  do {
    if (param_2 < 1) {
      return;
    }
    param_2 = param_2 + -1;
    write_char(param_1,param_3,param_4);
  } while (*param_4 != -1);
  return;
}

/* ---- 0x004b04b0  write_string ---- */
void write_string(char *param_1,int param_2,undefined4 param_3,int *param_4)

{
  char cVar1;
  
  do {
    if (param_2 < 1) {
      return;
    }
    param_2 = param_2 + -1;
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    write_char((int)cVar1,param_3,param_4);
  } while (*param_4 != -1);
  return;
}

/* ---- 0x004b04f0  get_int_arg ---- */
undefined4 get_int_arg(int *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)*param_1;
  *param_1 = (int)(puVar1 + 1);
  return *puVar1;
}

/* ---- 0x004b0510  get_short_arg ---- */
undefined8 get_short_arg(int *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  *param_1 = (int)(puVar1 + 1);
  return *puVar1;
}

/* ---- 0x004b0530  get_int64_arg ---- */
undefined4 get_int64_arg(undefined4 *param_1)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  
  puVar1 = (undefined2 *)*param_1;
  puVar2 = puVar1 + 2;
  *param_1 = puVar2;
  return CONCAT22((short)((uint)puVar2 >> 0x10),*puVar1);
}

/* ---- 0x004b0b50  _isctype ---- */
uint _isctype(int param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = param_1;
  if (param_1 + 1U < 0x101) {
    return *(ushort *)(PTR_DAT_004ed320 + param_1 * 2) & param_2;
  }
  if ((PTR_DAT_004ed320[(param_1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
    PIECE(param_1,0,2) = (ushort)(byte)param_1;
    uVar1 = 1;
  }
  else {
    PIECE(param_1,0,2) = CONCAT11((byte)param_1,(char)((uint)param_1 >> 8));
    PIECE(param_1,3,1) = SUB41(iVar2,3);
    PIECE(param_1,0,3) = (uint3)(ushort)param_1;
    uVar1 = 2;
  }
  iVar2 = __crtGetStringTypeA(1,&param_1,uVar1,&local_4,0,0,1);
  if (iVar2 == 0) {
    return 0;
  }
  return local_4 & 0xffff & param_2;
}
#undef local_4


/* ---- 0x004b0bf0  _allmul ---- */
undefined * __stdcall _allmul(int a1,int a2,int a3,int a4)

{
  if (a4 == 0 && a2 == 0) {
    return (undefined *)(a1 * a3);
  }
  return (undefined *)(a1 * a3);
}

/* ---- 0x004b0c90  _initptd ---- */
void _initptd(int param_1)

{
  *(undefined **)(param_1 + 0x50) = &DAT_004ed548;
  *(undefined4 *)(param_1 + 0x14) = 1;
  return;
}

/* ---- 0x004b0cb0  _getptd ---- */
int * _getptd(void)

{
  int a1;
  int *a2;
  int iVar1;
  
  a1 = GetLastError();
  a2 = (int *)TlsGetValue(UINT_004ed540);
  if (a2 == (int *)0x0) {
    a2 = (int *)calloc(1,0x74);
    if (a2 != (int *)0x0) {
      iVar1 = TlsSetValue(UINT_004ed540,(int)a2);
      if (iVar1 != 0) {
        _initptd(a2);
        iVar1 = GetCurrentThreadId();
        *a2 = iVar1;
        a2[1] = -1;
        SetLastError(a1);
        return a2;
      }
    }
    _amsg_exit(0x10);
  }
  SetLastError(a1);
  return a2;
}

/* ---- 0x004b1d20  _FF_MSGBANNER ---- */
void _FF_MSGBANNER(void)

{
  if ((UINT_008d0aac == 1) || ((UINT_008d0aac == 0 && (UINT_004ed0b4 == 1)))) {
    _NMSG_WRITE(0xfc);
    if (UINT_008d0ec0 != 0) {
      (*(code *)UINT_008d0ec0)();
    }
    _NMSG_WRITE(0xff);
  }
  return;
}

/* ---- 0x004b1d60  _NMSG_WRITE ---- */
void _NMSG_WRITE(undefined *param_1)

{
  unsigned char _frame[0x1c0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  uint *puVar8;
  uint *puVar9;
  char *pcVar10;
  #define local_1a8 (*(undefined1 (*)[4])(_frame + (0x1c0 - 0x1a8)))
  #define auStack_1a4 (*(uint (*)[25])(_frame + (0x1c0 - 0x1a4)))
  #define acStack_140 (*(char (*)[60])(_frame + (0x1c0 - 0x140)))
  #define local_104 (*(undefined4 *)(_frame + (0x1c0 - 0x104)))
  
  puVar2 = &UINT_004ed6f0;
  iVar7 = 0;
  do {
    if (param_1 == (undefined *)*puVar2) break;
    puVar2 = puVar2 + 2;
    iVar7 = iVar7 + 1;
  } while (puVar2 < &PTR_DAT_004ed780);
  if (param_1 == (undefined *)(&UINT_004ed6f0)[iVar7 * 2]) {
    if ((UINT_008d0aac == 1) || ((UINT_008d0aac == 0 && (UINT_004ed0b4 == 1)))) {
      if ((PTR_00906b00 == (int *)0x0) || (iVar3 = PTR_00906b00[0x12], iVar3 == -1)) {
        iVar3 = GetStdHandle(-0xc);
      }
      pcVar6 = *(char **)(iVar7 * 8 + IMG_ADDR(0x004ed6f4));
      uVar4 = 0xffffffff;
      pcVar10 = pcVar6;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      WriteFile(iVar3,(int)pcVar6,~uVar4 - 1,(int)local_1a8,0);
    }
    else if (param_1 != (undefined *)0xfc) {
      iVar3 = GetModuleFileNameA(0,(int)&local_104,0x104);
      if (iVar3 == 0) {
        puVar2 = &UINT_004d8d74;
        puVar9 = &local_104;
        for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar9 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar9 = puVar9 + 1;
        }
        *(short *)puVar9 = (short)*puVar2;
        *(undefined1 *)((int)puVar9 + 2) = *(undefined1 *)((int)puVar2 + 2);
      }
      uVar4 = 0xffffffff;
      pcVar6 = (char *)&local_104;
      pcVar10 = (char *)&local_104;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      if (0x3c < ~uVar4) {
        uVar4 = 0xffffffff;
        pcVar6 = (char *)&local_104;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        pcVar6 = acStack_140 + ~uVar4;
        strncpy(pcVar6,&DAT_004d8d70,3);
      }
      puVar2 = &UINT_004d8d54;
      puVar9 = auStack_1a4;
      for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar9 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar9 = puVar9 + 1;
      }
      *(short *)puVar9 = (short)*puVar2;
      uVar4 = 0xffffffff;
      do {
        pcVar10 = pcVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar10 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar10;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      puVar2 = auStack_1a4;
      do {
        puVar9 = puVar2;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        puVar9 = (uint *)((int)puVar2 + 1);
        uVar5 = *puVar2;
        puVar2 = puVar9;
      } while ((char)uVar5 != '\0');
      pcVar6 = pcVar10 + -uVar4;
      pcVar10 = (char *)((int)puVar9 + -1);
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar10 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar10 = pcVar10 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar10 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar10 = pcVar10 + 1;
      }
      uVar4 = 0xffffffff;
      puVar2 = &UINT_004ddd74;
      do {
        puVar9 = puVar2;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        puVar9 = (uint *)((int)puVar2 + 1);
        uVar5 = *puVar2;
        puVar2 = puVar9;
      } while ((char)uVar5 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      puVar2 = auStack_1a4;
      do {
        puVar8 = puVar2;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        puVar8 = (uint *)((int)puVar2 + 1);
        uVar5 = *puVar2;
        puVar2 = puVar8;
      } while ((char)uVar5 != '\0');
      pcVar6 = (char *)((int)puVar9 - uVar4);
      pcVar10 = (char *)((int)puVar8 + -1);
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar10 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar10 = pcVar10 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar10 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar10 = pcVar10 + 1;
      }
      uVar4 = 0xffffffff;
      pcVar6 = *(char **)(iVar7 * 8 + IMG_ADDR(0x004ed6f4));
      do {
        pcVar10 = pcVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar10 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar10;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar7 = -1;
      puVar2 = auStack_1a4;
      do {
        puVar9 = puVar2;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        puVar9 = (uint *)((int)puVar2 + 1);
        uVar5 = *puVar2;
        puVar2 = puVar9;
      } while ((char)uVar5 != '\0');
      pcVar6 = pcVar10 + -uVar4;
      pcVar10 = (char *)((int)puVar9 + -1);
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar10 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar10 = pcVar10 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar10 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar10 = pcVar10 + 1;
      }
      ((code *)__crtMessageBoxA)(auStack_1a4,"Microsoft Visual C++ Runtime Library");
      return;
    }
  }
  return;
}
#undef acStack_140
#undef auStack_1a4
#undef local_104
#undef local_1a8


/* ---- 0x004b1f40  _stbuf ---- */
undefined4 _stbuf(uint *param_1)

{
  uint uVar1;
  int iVar2;
  undefined *puVar3;
  
  iVar2 = _isatty(param_1[4]);
  if (iVar2 == 0) {
    return 0;
  }
  if (param_1 == (uint *)&DAT_004ed7a0) {
    iVar2 = 0;
  }
  else {
    if (param_1 != (uint *)&DAT_004ed7c0) {
      return 0;
    }
    iVar2 = 1;
  }
  UINT_008d0ed0 = UINT_008d0ed0 + 1;
  if ((param_1[3] & 0x10c) != 0) {
    return 0;
  }
  if ((&UINT_008d0ec8)[iVar2] == 0) {
    puVar3 = malloc(0x1000);
    (&UINT_008d0ec8)[iVar2] = (uint)puVar3;
    if (puVar3 == (undefined *)0x0) {
      param_1[2] = (uint)(param_1 + 5);
      *param_1 = (uint)(param_1 + 5);
      param_1[6] = 2;
      param_1[1] = 2;
      goto LAB_004b1fe0;
    }
  }
  uVar1 = (&UINT_008d0ec8)[iVar2];
  param_1[6] = 0x1000;
  param_1[2] = uVar1;
  *param_1 = uVar1;
  param_1[1] = 0x1000;
LAB_004b1fe0:
  param_1[3] = param_1[3] | 0x1102;
  return 1;
}

/* ---- 0x004b2000  _ftbuf ---- */
void _ftbuf(int param_1,undefined4 *param_2)

{
  if ((param_1 != 0) && ((param_2[3] & 0x1000) != 0)) {
    _flush(param_2);
    param_2[6] = 0;
    param_2[3] = param_2[3] & 0xffffeeff;
    *param_2 = 0;
    param_2[2] = 0;
  }
  return;
}

/* ---- 0x004b2120  _msize ---- */
int _msize(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  #define local_8 (*(undefined1 (*)[4])(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  _lock(9);
  pbVar2 = (byte *)__sbh_find_block(param_1,local_4,local_8);
  if (pbVar2 != (byte *)0x0) {
    bVar1 = *pbVar2;
    _unlock(9);
    return (uint)bVar1 << 4;
  }
  _unlock(9);
  iVar3 = HeapSize(UINT_00906ae4,0,param_1);
  return iVar3;
}
#undef local_4
#undef local_8


/* ---- 0x004b2190  _callnewh ---- */
undefined4 _callnewh(undefined4 param_1)

{
  int iVar1;
  
  if (UINT_008d0ed8 != 0) {
    iVar1 = (*(code *)UINT_008d0ed8)(param_1);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}

/* ---- 0x004b21b0  __sbh_alloc_new_region ---- */
undefined ** __sbh_alloc_new_region(void)

{
  bool bVar1;
  undefined4 *a1;
  int iVar2;
  undefined **ppuVar3;
  undefined **a3;
  undefined4 *puVar4;
  
  if (UINT_004eda10 == 0xffffffff) {
    a3 = &PTR_LOOP_004eda00;
  }
  else {
    a3 = (undefined **)HeapAlloc(UINT_00906ae4,0,0x2020);
    if (a3 == (undefined **)0x0) {
      return (undefined **)0x0;
    }
  }
  a1 = (undefined4 *)VirtualAlloc(0,0x400000,0x2000,4);
  if (a1 != (undefined4 *)0x0) {
    iVar2 = VirtualAlloc((int)a1,0x10000,0x1000,4);
    if (iVar2 != 0) {
      if (a3 == &PTR_LOOP_004eda00) {
        if (PTR_LOOP_004eda00 == (undefined *)0x0) {
          PTR_LOOP_004eda00 = (undefined *)&PTR_LOOP_004eda00;
        }
        if (PTR_LOOP_004eda04 == (undefined *)0x0) {
          PTR_LOOP_004eda04 = (undefined *)&PTR_LOOP_004eda00;
        }
      }
      else {
        *a3 = (undefined *)&PTR_LOOP_004eda00;
        a3[1] = PTR_LOOP_004eda04;
        PTR_LOOP_004eda04 = (undefined *)a3;
        *(undefined ***)a3[1] = a3;
      }
      a3[5] = (undefined *)(a1 + 0x100000);
      a3[4] = (undefined *)a1;
      a3[2] = (undefined *)(a3 + 6);
      a3[3] = (undefined *)(a3 + 0x26);
      iVar2 = 0;
      ppuVar3 = a3 + 6;
      do {
        bVar1 = 0xf < iVar2;
        iVar2 = iVar2 + 1;
        *ppuVar3 = (undefined *)((bVar1 - 1 & 0xf1) - 1);
        ppuVar3[1] = (undefined *)0xf1;
        ppuVar3 = ppuVar3 + 2;
      } while (iVar2 < 0x400);
      puVar4 = a1;
      for (iVar2 = 0x4000; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
      if (a1 < a3[4] + 0x10000) {
        do {
          a1[1] = 0xf0;
          *a1 = a1 + 2;
          *(undefined1 *)(a1 + 0x3e) = 0xff;
          a1 = a1 + 0x400;
        } while (a1 < a3[4] + 0x10000);
      }
      return a3;
    }
    VirtualFree((int)a1,0,0x8000);
  }
  if (a3 != &PTR_LOOP_004eda00) {
    HeapFree(UINT_00906ae4,0,(int)a3);
  }
  return (undefined **)0x0;
}

/* ---- 0x004b2320  __sbh_release_region ---- */
void __sbh_release_region(undefined **param_1)

{
  VirtualFree((int)param_1[4],0,0x8000);
  if ((undefined **)PTR_LOOP_004efa20 == param_1) {
    PTR_LOOP_004efa20 = param_1[1];
  }
  if (param_1 != &PTR_LOOP_004eda00) {
    *(undefined **)param_1[1] = *param_1;
    *(undefined **)(*param_1 + 4) = param_1[1];
    HeapFree(UINT_00906ae4,0,(int)param_1);
    return;
  }
  UINT_004eda10 = 0xffffffff;
  return;
}

/* ---- 0x004b2380  __sbh_decommit_pages ---- */
void __sbh_decommit_pages(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  undefined *puVar6;
  
  puVar5 = PTR_LOOP_004eda04;
  do {
    puVar6 = puVar5;
    if (*(int *)(puVar5 + 0x10) != -1) {
      iVar4 = 0;
      piVar2 = (int *)(puVar5 + 0x2010);
      iVar3 = 0x3ff000;
      do {
        if (*piVar2 == 0xf0) {
          iVar1 = VirtualFree(*(int *)(puVar5 + 0x10) + iVar3,0x1000,0x4000);
          if (iVar1 != 0) {
            *piVar2 = -1;
            UINT_008d0edc = UINT_008d0edc - 1;
            if ((*(int **)(puVar5 + 0xc) == (int *)0x0) || (piVar2 < *(int **)(puVar5 + 0xc))) {
              *(int **)(puVar5 + 0xc) = piVar2;
            }
            iVar4 = iVar4 + 1;
            param_1 = param_1 + -1;
            if (param_1 == 0) break;
          }
        }
        iVar3 = iVar3 + -0x1000;
        piVar2 = piVar2 + -2;
      } while (-1 < iVar3);
      puVar6 = *(undefined **)(puVar5 + 4);
      if ((iVar4 != 0) && (*(int *)(puVar5 + 0x18) == -1)) {
        iVar3 = 1;
        piVar2 = (int *)(puVar5 + 0x20);
        do {
          if (*piVar2 != -1) break;
          iVar3 = iVar3 + 1;
          piVar2 = piVar2 + 2;
        } while (iVar3 < 0x400);
        if (iVar3 == 0x400) {
          __sbh_release_region(puVar5);
        }
      }
    }
    if ((puVar6 == PTR_LOOP_004eda04) || (puVar5 = puVar6, param_1 < 1)) {
      return;
    }
  } while( true );
}

/* ---- 0x004b2450  __sbh_find_block ---- */
int __sbh_find_block(undefined *param_1,undefined4 *param_2,uint *param_3)

{
  undefined **ppuVar1;
  uint uVar2;
  
  ppuVar1 = &PTR_LOOP_004eda00;
  while ((param_1 <= ppuVar1[4] || (ppuVar1[5] <= param_1))) {
    ppuVar1 = (undefined **)*ppuVar1;
    if (ppuVar1 == &PTR_LOOP_004eda00) {
      return 0;
    }
  }
  if (((uint)param_1 & 0xf) != 0) {
    return 0;
  }
  if (((uint)param_1 & 0xfff) < 0x100) {
    return 0;
  }
  *param_2 = ppuVar1;
  uVar2 = (uint)param_1 & 0xfffff000;
  *param_3 = uVar2;
  return ((int)(param_1 + (-0x100 - uVar2)) >> 4) + 8 + uVar2;
}

/* ---- 0x004b24b0  __sbh_free_block ---- */
void __sbh_free_block(int param_1,int param_2,byte *param_3)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = param_2 - *(int *)(param_1 + 0x10) >> 0xc;
  piVar1 = (int *)(param_1 + 0x18 + iVar2 * 8);
  *piVar1 = *(int *)(param_1 + 0x18 + iVar2 * 8) + (uint)*param_3;
  *param_3 = 0;
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (UINT_008d0edc = UINT_008d0edc + 1, UINT_008d0edc == 0x20)) {
    __sbh_decommit_pages(0x10);
  }
  return;
}

/* ---- 0x004b2510  __sbh_alloc_block ---- */
int * __sbh_alloc_block(uint param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined **ppuVar1;
  undefined **ppuVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  undefined *puVar6;
  undefined **ppuVar7;
  undefined **ppuVar8;
  int iVar9;
  int *piVar10;
  bool bVar11;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  piVar10 = (int *)PTR_LOOP_004efa20;
  do {
    if (piVar10[4] != -1) {
      piVar5 = (int *)piVar10[2];
      iVar9 = ((int)piVar5 + (-0x18 - (int)piVar10) >> 3) * 0x1000 + piVar10[4];
      for (; piVar5 < piVar10 + 0x806; piVar5 = piVar5 + 2) {
        if (((int)param_1 <= *piVar5) && (param_1 < (uint)piVar5[1])) {
          piVar3 = (int *)__sbh_alloc_new_group(iVar9,*piVar5,param_1);
          if (piVar3 != (int *)0x0) {
            PTR_LOOP_004efa20 = (undefined *)piVar10;
            *piVar5 = *piVar5 - param_1;
            piVar10[2] = (int)piVar5;
            return piVar3;
          }
          piVar5[1] = param_1;
        }
        iVar9 = iVar9 + 0x1000;
      }
      piVar3 = (int *)piVar10[2];
      iVar9 = piVar10[4];
      for (piVar5 = piVar10 + 6; piVar5 < piVar3; piVar5 = piVar5 + 2) {
        if (((int)param_1 <= *piVar5) && (param_1 < (uint)piVar5[1])) {
          piVar4 = (int *)__sbh_alloc_new_group(iVar9,*piVar5,param_1);
          if (piVar4 != (int *)0x0) {
            PTR_LOOP_004efa20 = (undefined *)piVar10;
            *piVar5 = *piVar5 - param_1;
            piVar10[2] = (int)piVar5;
            return piVar4;
          }
          piVar5[1] = param_1;
        }
        iVar9 = iVar9 + 0x1000;
      }
    }
    piVar10 = (int *)*piVar10;
  } while (piVar10 != (int *)PTR_LOOP_004efa20);
  ppuVar8 = &PTR_LOOP_004eda00;
  while ((ppuVar8[4] == (undefined *)0xffffffff || (ppuVar8[3] == (undefined *)0x0))) {
    ppuVar8 = (undefined **)*ppuVar8;
    if (ppuVar8 == &PTR_LOOP_004eda00) {
      puVar6 = (undefined *)__sbh_alloc_new_region();
      if (puVar6 == (undefined *)0x0) {
        return (int *)0x0;
      }
      piVar10 = *(int **)(puVar6 + 0x10);
      *(char *)(piVar10 + 2) = (char)param_1;
      PTR_LOOP_004efa20 = puVar6;
      *piVar10 = (int)piVar10 + param_1 + 8;
      piVar10[1] = 0xf0 - param_1;
      *(uint *)(puVar6 + 0x18) = *(int *)(puVar6 + 0x18) - (param_1 & 0xff);
      return piVar10 + 0x40;
    }
  }
  ppuVar2 = (undefined **)ppuVar8[3];
  puVar6 = *ppuVar2;
  piVar10 = (int *)(ppuVar8[4] + ((int)ppuVar2 + (-0x18 - (int)ppuVar8) >> 3) * 0x1000);
  ppuVar7 = ppuVar2;
  for (iVar9 = 0; (puVar6 == (undefined *)0xffffffff && (iVar9 < 0x10)); iVar9 = iVar9 + 1) {
    puVar6 = ppuVar7[2];
    ppuVar7 = ppuVar7 + 2;
  }
  piVar5 = (int *)VirtualAlloc((int)piVar10,iVar9 << 0xc,0x1000,4);
  if (piVar5 != piVar10) {
    return (int *)0x0;
  }
  ppuVar7 = ppuVar2;
  if (0 < iVar9) {
    piVar5 = piVar10 + 1;
    do {
      *piVar5 = 0xf0;
      piVar5[-1] = (int)(piVar5 + 1);
      *(undefined1 *)(piVar5 + 0x3d) = 0xff;
      *ppuVar7 = (undefined *)0xf0;
      ppuVar7[1] = (undefined *)0xf1;
      piVar5 = piVar5 + 0x400;
      ppuVar7 = ppuVar7 + 2;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
  }
  ppuVar1 = ppuVar8 + 0x806;
  bVar11 = false;
  if (ppuVar7 < ppuVar1) {
    do {
      if (*ppuVar7 == (undefined *)0xffffffff) break;
      ppuVar7 = ppuVar7 + 2;
    } while (ppuVar7 < ppuVar1);
    bVar11 = ppuVar7 < ppuVar1;
  }
  PTR_LOOP_004efa20 = (undefined *)ppuVar8;
  ppuVar8[3] = (undefined *)(-(uint)bVar11 & (uint)ppuVar7);
  *(char *)(piVar10 + 2) = (char)param_1;
  ppuVar8[2] = (undefined *)ppuVar2;
  *ppuVar2 = *ppuVar2 + -param_1;
  piVar10[1] = piVar10[1] - param_1;
  *piVar10 = (int)piVar10 + param_1 + 8;
  return piVar10 + 0x40;
}
#undef local_4


/* ---- 0x004b2750  __sbh_alloc_new_group ---- */
int __sbh_alloc_new_group(int *param_1,uint param_2,uint param_3)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  uint uVar5;
  byte *pbVar6;
  
  pbVar2 = (byte *)*param_1;
  if (param_3 <= (uint)param_1[1]) {
    *pbVar2 = (byte)param_3;
    if (pbVar2 + param_3 < param_1 + 0x3e) {
      *param_1 = *param_1 + param_3;
      param_1[1] = param_1[1] - param_3;
    }
    else {
      param_1[1] = 0;
      *param_1 = (int)(param_1 + 2);
    }
    return (int)(pbVar2 + 8) * 0x10 + (int)param_1 * -0xf;
  }
  pbVar6 = pbVar2;
  if (pbVar2[param_1[1]] != 0) {
    pbVar6 = pbVar2 + param_1[1];
  }
  if (pbVar6 + param_3 < param_1 + 0x3e) {
    do {
      if (*pbVar6 == 0) {
        pbVar3 = pbVar6 + 1;
        uVar5 = 1;
        bVar1 = pbVar6[1];
        while (bVar1 == 0) {
          pbVar3 = pbVar3 + 1;
          uVar5 = uVar5 + 1;
          bVar1 = *pbVar3;
        }
        if (param_3 <= uVar5) {
          if (param_1 + 0x3e <= pbVar6 + param_3) {
            *param_1 = (int)(param_1 + 2);
            goto LAB_004b289f;
          }
          *param_1 = (int)(pbVar6 + param_3);
          param_1[1] = uVar5 - param_3;
          goto LAB_004b28a6;
        }
        if (pbVar6 == pbVar2) {
          param_1[1] = uVar5;
        }
        else {
          param_2 = param_2 - uVar5;
          if (param_2 < param_3) {
            return 0;
          }
        }
      }
      else {
        pbVar3 = pbVar6 + *pbVar6;
      }
      pbVar6 = pbVar3;
    } while (pbVar3 + param_3 < param_1 + 0x3e);
  }
  pbVar3 = (byte *)(param_1 + 2);
  pbVar6 = pbVar3;
  if (pbVar3 < pbVar2) {
    while (pbVar6 + param_3 < param_1 + 0x3e) {
      if (*pbVar6 == 0) {
        pbVar4 = pbVar6 + 1;
        uVar5 = 1;
        bVar1 = pbVar6[1];
        while (bVar1 == 0) {
          pbVar4 = pbVar4 + 1;
          uVar5 = uVar5 + 1;
          bVar1 = *pbVar4;
        }
        if (param_3 <= uVar5) {
          if (pbVar6 + param_3 < param_1 + 0x3e) {
            *param_1 = (int)(pbVar6 + param_3);
            param_1[1] = uVar5 - param_3;
          }
          else {
            *param_1 = (int)pbVar3;
LAB_004b289f:
            param_1[1] = 0;
          }
LAB_004b28a6:
          *pbVar6 = (byte)param_3;
          return (int)(pbVar6 + 8) * 0x10 + (int)param_1 * -0xf;
        }
        param_2 = param_2 - uVar5;
        if (param_2 < param_3) {
          return 0;
        }
      }
      else {
        pbVar4 = pbVar6 + *pbVar6;
      }
      pbVar6 = pbVar4;
      if (pbVar2 <= pbVar4) {
        return 0;
      }
    }
  }
  return 0;
}

/* ---- 0x004b28d0  __sbh_resize_block ---- */
undefined4 __sbh_resize_block(int param_1,int *param_2,byte *param_3,uint param_4)

{
  byte *pbVar1;
  int iVar2;
  int *piVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  byte *pbVar8;
  
  uVar5 = 0;
  piVar3 = (int *)(param_1 + 0x18 + ((int)param_2 - *(int *)(param_1 + 0x10) >> 0xc) * 8);
  uVar7 = (uint)*param_3;
  if (uVar7 <= param_4) {
    if ((uVar7 < param_4) && (pbVar1 = param_3 + param_4, pbVar1 <= param_2 + 0x3e)) {
      for (pbVar8 = param_3 + uVar7; (pbVar8 < pbVar1 && (*pbVar8 == 0)); pbVar8 = pbVar8 + 1) {
      }
      if (pbVar8 == pbVar1) {
        *param_3 = (byte)param_4;
        if ((param_3 <= (byte *)*param_2) && ((byte *)*param_2 < pbVar1)) {
          if (pbVar1 < param_2 + 0x3e) {
            *param_2 = (int)pbVar1;
            iVar6 = 0;
            bVar4 = *pbVar1;
            while (bVar4 == 0) {
              iVar2 = iVar6 + 1;
              iVar6 = iVar6 + 1;
              bVar4 = pbVar1[iVar2];
            }
            param_2[1] = iVar6;
          }
          else {
            param_2[1] = 0;
            *param_2 = (int)(param_2 + 2);
          }
        }
        *piVar3 = *piVar3 + (uVar7 - param_4);
        uVar5 = 1;
      }
    }
    return uVar5;
  }
  *param_3 = (byte)param_4;
  piVar3[1] = 0xf1;
  *piVar3 = *piVar3 + (uVar7 - param_4);
  return 1;
}

/* ---- 0x004b29a0  time ---- */
void time(undefined4 *param_1)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined *puVar1;
  #define local_34 (*(ushort *)(_frame + (0x50 - 0x34)))
  #define uStack_32 (*(ushort *)(_frame + (0x50 - 0x32)))
  #define uStack_2e (*(ushort *)(_frame + (0x50 - 0x2e)))
  #define uStack_2c (*(ushort *)(_frame + (0x50 - 0x2c)))
  #define uStack_2a (*(ushort *)(_frame + (0x50 - 0x2a)))
  #define uStack_28 (*(ushort *)(_frame + (0x50 - 0x28)))
  #define uStack_26 (*(undefined2 *)(_frame + (0x50 - 0x26)))
  #define uStack_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define uStack_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define uStack_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  #define uStack_18 (*(uint *)(_frame + (0x50 - 0x18)))
  #define iStack_14 (*(int *)(_frame + (0x50 - 0x14)))
  #define iStack_10 (*(int *)(_frame + (0x50 - 0x10)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x50 - 0x4)))
  
  __tzset();
  *(short *)((int)param_1 + 6) =
       ((short)((int)UINT_004f0400 / 0x3c) + (short)((int)UINT_004f0400 >> 0x1f)) -
       (short)((longlong)(int)UINT_004f0400 * 0x88888889 >> 0x3f);
  GetLocalTime((int)&local_34);
  *(undefined2 *)(param_1 + 1) = uStack_26;
  iStack_10 = local_34 - 0x76c;
  uStack_18 = (uint)uStack_2e;
  iStack_14 = uStack_32 - 1;
  uStack_1c = (uint)uStack_2c;
  uStack_20 = (uint)uStack_2a;
  uStack_24 = (uint)uStack_28;
  uStack_4 = 0xffffffff;
  puVar1 = mktime((uint)&uStack_24);
  *param_1 = puVar1;
  *(undefined2 *)(param_1 + 2) = (undefined2)uStack_4;
  return;
}
#undef iStack_10
#undef iStack_14
#undef local_34
#undef uStack_18
#undef uStack_1c
#undef uStack_20
#undef uStack_24
#undef uStack_26
#undef uStack_28
#undef uStack_2a
#undef uStack_2c
#undef uStack_2e
#undef uStack_32
#undef uStack_4


/* ---- 0x004b2a60  _openfile ---- */
undefined4 * _openfile(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 *param_4)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  uint uVar5;
  int iVar6;
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
      uVar7 = UINT_008d1024 | 1;
      goto LAB_004b2a9d;
    }
    if (cVar1 != 'w') {
      return (undefined4 *)0x0;
    }
    uVar5 = 0x301;
  }
  uVar7 = UINT_008d1024 | 2;
LAB_004b2a9d:
  param_2 = param_2 + 1;
  bVar2 = true;
  cVar1 = *param_2;
  do {
    if ((cVar1 == '\0') || (!bVar2)) {
      iVar6 = _sopen(param_1,uVar5,param_3,0x1a4);
      if (-1 < iVar6) {
        UINT_008d0ed0 = UINT_008d0ed0 + 1;
        param_4[3] = uVar7;
        param_4[1] = 0;
        *param_4 = 0;
        param_4[2] = 0;
        param_4[7] = 0;
        param_4[4] = iVar6;
        return param_4;
      }
      return (undefined4 *)0x0;
    }
    switch(cVar1) {
    case '+':
      if ((uVar5 & 2) != 0) break;
      uVar5 = uVar5 & 0xfffffffe | 2;
      uVar7 = uVar7 & 0xfffffffc | 0x80;
      goto LAB_004b2b4e;
    case 'D':
      if ((uVar5 & 0x40) == 0) {
        uVar5 = uVar5 | 0x40;
        goto LAB_004b2b4e;
      }
      break;
    case 'R':
      if (!bVar4) {
        bVar4 = true;
        uVar5 = uVar5 | 0x10;
        goto LAB_004b2b4e;
      }
      break;
    case 'S':
      if (!bVar4) {
        bVar4 = true;
        uVar5 = uVar5 | 0x20;
        goto LAB_004b2b4e;
      }
      break;
    case 'T':
      if ((uVar5 & 0x1000) == 0) {
        uVar5 = uVar5 | 0x1000;
        goto LAB_004b2b4e;
      }
      break;
    case 'b':
      if ((uVar5 & 0xc000) == 0) {
        uVar5 = uVar5 | 0x8000;
        goto LAB_004b2b4e;
      }
      break;
    case 'c':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 | 0x4000;
        goto LAB_004b2b4e;
      }
      break;
    case 'n':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 & 0xffffbfff;
        goto LAB_004b2b4e;
      }
      break;
    case 't':
      if ((uVar5 & 0xc000) == 0) {
        uVar5 = uVar5 | 0x4000;
        goto LAB_004b2b4e;
      }
    }
    bVar2 = false;
LAB_004b2b4e:
    param_2 = param_2 + 1;
    cVar1 = *param_2;
  } while( true );
}

/* ---- 0x004b2c30  _getstream ---- */
undefined4 * _getstream(void)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar4 = (undefined4 *)0x0;
  _lock(2);
  iVar3 = 0;
  if (0 < (int)UINT_00906ae0) {
    do {
      iVar1 = *(int *)(UINT_00905ac4 + iVar3 * 4);
      if (iVar1 == 0) {
        iVar3 = iVar3 * 4;
        puVar2 = malloc(0x38);
        *(undefined **)(UINT_00905ac4 + iVar3) = puVar2;
        if (*(int *)(UINT_00905ac4 + iVar3) != 0) {
          InitializeCriticalSection(*(int *)(UINT_00905ac4 + iVar3) + 0x20);
          EnterCriticalSection(*(int *)(UINT_00905ac4 + iVar3) + 0x20);
          puVar4 = *(undefined4 **)(UINT_00905ac4 + iVar3);
        }
        break;
      }
      if ((*(byte *)(iVar1 + 0xc) & 0x83) == 0) {
        _lock_file2(iVar3,iVar1);
        iVar1 = *(int *)(UINT_00905ac4 + iVar3 * 4);
        if ((*(byte *)(iVar1 + 0xc) & 0x83) == 0) {
          puVar4 = *(undefined4 **)(UINT_00905ac4 + iVar3 * 4);
          break;
        }
        _unlock_file2(iVar3,iVar1);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)UINT_00906ae0);
  }
  if (puVar4 != (undefined4 *)0x0) {
    puVar4[1] = 0;
    puVar4[3] = 0;
    puVar4[2] = 0;
    *puVar4 = 0;
    puVar4[7] = 0;
    puVar4[4] = 0xffffffff;
  }
  _unlock(2);
  return puVar4;
}

/* ---- 0x004b2d10  _close ---- */
undefined4 _close(uint param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if ((param_1 < UINT_00906c00) &&
     ((*(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    _lock_fhandle(param_1);
    uVar1 = _close_lk(param_1);
    _unlock_fhandle(param_1);
    return uVar1;
  }
  puVar2 = (undefined4 *)_errno();
  *puVar2 = 9;
  puVar2 = (undefined4 *)__doserrno();
  *puVar2 = 0;
  return 0xffffffff;
}

/* ---- 0x004b2d80  _close_lk ---- */
undefined4 _close_lk(uint param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = _get_osfhandle(param_1);
  if (iVar1 != -1) {
    if ((param_1 == 1) || (param_1 == 2)) {
      iVar1 = _get_osfhandle(1);
      iVar2 = _get_osfhandle(2);
      if (iVar1 == iVar2) goto LAB_004b2dd6;
    }
    iVar1 = _get_osfhandle(param_1);
    iVar1 = CloseHandle(iVar1);
    if (iVar1 == 0) {
      iVar1 = GetLastError();
      goto LAB_004b2dd8;
    }
  }
LAB_004b2dd6:
  iVar1 = 0;
LAB_004b2dd8:
  _free_osfhnd(param_1);
  *(undefined1 *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) = 0;
  if (iVar1 != 0) {
    _dosmaperr(iVar1);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x004b2e10  _freebuf ---- */
void _freebuf(undefined4 *param_1)

{
  if (((param_1[3] & 0x83) != 0) && ((param_1[3] & 8) != 0)) {
    free(param_1[2]);
    param_1[3] = param_1[3] & 0xfffffbf7;
    *param_1 = 0;
    param_1[2] = 0;
    param_1[1] = 0;
  }
  return;
}

/* ---- 0x004b2e50  _filbuf ---- */
uint _filbuf(undefined4 *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  
  uVar2 = param_1[3];
  if (((uVar2 & 0x83) != 0) && ((uVar2 & 0x40) == 0)) {
    if ((uVar2 & 2) != 0) {
      param_1[3] = uVar2 | 0x20;
      return 0xffffffff;
    }
    param_1[3] = uVar2 | 1;
    if ((uVar2 & 0x10c) == 0) {
      _getbuf(param_1);
    }
    else {
      *param_1 = param_1[2];
    }
    iVar3 = _read(param_1[4],param_1[2],param_1[6]);
    param_1[1] = iVar3;
    if ((iVar3 != 0) && (iVar3 != -1)) {
      if ((param_1[3] & 0x82) == 0) {
        uVar2 = param_1[4];
        if (uVar2 == 0xffffffff) {
          piVar4 = (int *)&DAT_004ed6c8;
        }
        else {
          piVar4 = (&PTR_00906b00)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 9;
        }
        if ((*(byte *)(piVar4 + 1) & 0x82) == 0x82) {
          param_1[3] = param_1[3] | 0x2000;
        }
      }
      if (((param_1[6] == 0x200) && ((param_1[3] & 8) != 0)) && ((param_1[3] & 0x400) == 0)) {
        param_1[6] = 0x1000;
      }
      param_1[1] = iVar3 + -1;
      bVar1 = *(byte *)*param_1;
      *param_1 = (byte *)*param_1 + 1;
      return (uint)bVar1;
    }
    param_1[1] = 0;
    param_1[3] = param_1[3] | (-(uint)(iVar3 != 0) & 0x10) + 0x10;
  }
  return 0xffffffff;
}

/* ---- 0x004b2f40  _read ---- */
undefined4 _read(uint param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if ((param_1 < UINT_00906c00) &&
     ((*(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    _lock_fhandle(param_1);
    uVar1 = _read_lk(param_1,param_2,param_3);
    _unlock_fhandle(param_1);
    return uVar1;
  }
  puVar2 = (undefined4 *)_errno();
  *puVar2 = 9;
  puVar2 = (undefined4 *)__doserrno();
  *puVar2 = 0;
  return 0xffffffff;
}

/* ---- 0x004b2fc0  _read_lk ---- */
int _read_lk(uint param_1,char *param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int **ppiVar1;
  char cVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  #define cStack_9 (*(char *)(_frame + (0x20 - 0x9)))
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar8 = 0;
  if (param_3 != 0) {
    uVar4 = param_1 & 0x1f;
    ppiVar1 = &PTR_00906b00 + ((int)param_1 >> 5);
    iVar7 = uVar4 * 0x24;
    bVar3 = *(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + uVar4 * 9 + 1);
    if ((bVar3 & 2) == 0) {
      pcVar10 = param_2;
      if (((bVar3 & 0x48) != 0) &&
         (cVar2 = *(char *)((int)(&PTR_00906b00)[(int)param_1 >> 5] + iVar7 + 5), cVar2 != '\n')) {
        *param_2 = cVar2;
        param_3 = param_3 + -1;
        pcVar10 = param_2 + 1;
        iVar8 = 1;
        *(undefined1 *)(iVar7 + 5 + (int)*ppiVar1) = 10;
      }
      local_4 = (uint)ppiVar1;
      iVar5 = ReadFile((*ppiVar1)[uVar4 * 9],(int)pcVar10,param_3,(int)&local_8,0);
      if (iVar5 != 0) {
        iVar8 = iVar8 + local_8;
        bVar3 = *(byte *)(*ppiVar1 + uVar4 * 9 + 1);
        if ((bVar3 & 0x80) != 0) {
          if ((local_8 == 0) || (*param_2 != '\n')) {
            bVar3 = bVar3 & 0xfb;
          }
          else {
            bVar3 = bVar3 | 4;
          }
          *(byte *)(*ppiVar1 + uVar4 * 9 + 1) = bVar3;
          pcVar9 = param_2 + iVar8;
          pcVar10 = param_2;
          pcVar11 = param_2;
          if (param_2 < pcVar9) {
            while (cVar2 = *pcVar11, cVar2 != '\x1a') {
              if (cVar2 == '\r') {
                if (pcVar11 < pcVar9 + -1) {
                  if (pcVar11[1] == '\n') {
                    pcVar11 = pcVar11 + 2;
                    *pcVar10 = '\n';
                    goto LAB_004b3198;
                  }
                  *pcVar10 = '\r';
                  pcVar10 = pcVar10 + 1;
                  pcVar11 = pcVar11 + 1;
                }
                else {
                  iVar5 = 0;
                  pcVar11 = pcVar11 + 1;
                  iVar8 = ReadFile(*(int *)(iVar7 + *(int *)local_4),(int)&cStack_9,1,(int)&local_8,
                                   0);
                  if (iVar8 == 0) {
                    iVar5 = GetLastError();
                  }
                  if ((iVar5 == 0) && (local_8 != 0)) {
                    if ((*(byte *)(iVar7 + 4 + *(int *)local_4) & 0x48) == 0) {
                      if ((pcVar10 == param_2) && (cStack_9 == '\n')) {
                        *pcVar10 = '\n';
                        goto LAB_004b3198;
                      }
                      _lseek_lk(param_1,0xffffffff,1);
                      if (cStack_9 != '\n') goto LAB_004b3195;
                    }
                    else {
                      if (cStack_9 == '\n') {
                        *pcVar10 = '\n';
                        goto LAB_004b3198;
                      }
                      *pcVar10 = '\r';
                      pcVar10 = pcVar10 + 1;
                      *(char *)(iVar7 + 5 + *(int *)local_4) = cStack_9;
                    }
                  }
                  else {
LAB_004b3195:
                    *pcVar10 = '\r';
LAB_004b3198:
                    pcVar10 = pcVar10 + 1;
                  }
                }
              }
              else {
                *pcVar10 = cVar2;
                pcVar10 = pcVar10 + 1;
                pcVar11 = pcVar11 + 1;
              }
              if (pcVar9 <= pcVar11) {
                return (int)pcVar10 - (int)param_2;
              }
            }
            bVar3 = *(byte *)(iVar7 + 4 + *(int *)local_4);
            if ((bVar3 & 0x40) == 0) {
              *(byte *)(iVar7 + 4 + *(int *)local_4) = bVar3 | 2;
            }
          }
          iVar8 = (int)pcVar10 - (int)param_2;
        }
        return iVar8;
      }
      iVar8 = GetLastError();
      if (iVar8 == 5) {
        puVar6 = (undefined4 *)_errno();
        *puVar6 = 9;
        puVar6 = (undefined4 *)__doserrno();
        *puVar6 = 5;
        return -1;
      }
      if (iVar8 != 0x6d) {
        _dosmaperr(iVar8);
        return -1;
      }
    }
  }
  return 0;
}
#undef cStack_9
#undef local_4
#undef local_8


/* ---- 0x004b31f0  _write ---- */
undefined4 _write(uint param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if ((param_1 < UINT_00906c00) &&
     ((*(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    _lock_fhandle(param_1);
    uVar1 = _write_lk(param_1,param_2,param_3);
    _unlock_fhandle(param_1);
    return uVar1;
  }
  puVar2 = (undefined4 *)_errno();
  *puVar2 = 9;
  puVar2 = (undefined4 *)__doserrno();
  *puVar2 = 0;
  return 0xffffffff;
}

/* ---- 0x004b3270  _write_lk ---- */
int _write_lk(uint param_1,char *param_2,uint param_3)

{
  unsigned char _frame[0x430] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int **ppiVar1;
  char cVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  undefined4 *puVar6;
  char *pcVar7;
  #define local_41c (*(uint *)(_frame + (0x430 - 0x41c)))
  #define local_418 (*(uint *)(_frame + (0x430 - 0x418)))
  #define local_414 (*(uint *)(_frame + (0x430 - 0x414)))
  #define local_410 (*(uint *)(_frame + (0x430 - 0x410)))
  #define local_40c (*(uint *)(_frame + (0x430 - 0x40c)))
  #define local_408 (*(uint *)(_frame + (0x430 - 0x408)))
  #define local_404 (*(char (*)[1028])(_frame + (0x430 - 0x404)))
  
  local_41c = 0;
  local_40c = 0;
  if (param_3 == 0) {
    return 0;
  }
  ppiVar1 = &PTR_00906b00 + ((int)param_1 >> 5);
  uVar3 = param_1 & 0x1f;
  local_408 = (uint)ppiVar1;
  if ((*(byte *)(*ppiVar1 + uVar3 * 9 + 1) & 0x20) != 0) {
    _lseek_lk(param_1,0,2);
  }
  if ((*(byte *)(*ppiVar1 + uVar3 * 9 + 1) & 0x80) == 0) {
    iVar5 = WriteFile((*ppiVar1)[uVar3 * 9],(int)param_2,param_3,(int)&local_410,0);
    if (iVar5 == 0) {
      local_414 = GetLastError();
    }
    else {
      local_41c = local_410;
      local_414 = 0;
    }
  }
  else {
    local_414 = 0;
    pcVar7 = param_2;
    if (param_3 != 0) {
      do {
        pcVar4 = local_404;
        do {
          if (param_3 <= (uint)((int)pcVar7 - (int)param_2)) break;
          cVar2 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          if (cVar2 == '\n') {
            *pcVar4 = '\r';
            local_40c = local_40c + 1;
            pcVar4 = pcVar4 + 1;
          }
          *pcVar4 = cVar2;
          pcVar4 = pcVar4 + 1;
        } while ((int)pcVar4 - (int)local_404 < 0x400);
        iVar5 = WriteFile(*(int *)(uVar3 * 0x24 + *(int *)local_408),(int)local_404,
                          (int)pcVar4 - (int)local_404,(int)&local_410,0);
        if (iVar5 == 0) {
          local_414 = GetLastError();
          break;
        }
        local_41c = local_41c + local_410;
        if (((int)local_410 < (int)pcVar4 - (int)local_404) ||
           (param_3 <= (uint)((int)pcVar7 - (int)param_2))) break;
      } while( true );
    }
  }
  if (local_41c != 0) {
    return local_41c - local_40c;
  }
  if (local_414 == 0) {
    if (((*(byte *)(uVar3 * 0x24 + 4 + *(int *)local_408) & 0x40) != 0) && (*param_2 == '\x1a')) {
      return 0;
    }
    puVar6 = (undefined4 *)_errno();
    *puVar6 = 0x1c;
    puVar6 = (undefined4 *)__doserrno();
    *puVar6 = 0;
    return -1;
  }
  if (local_414 != 5) {
    _dosmaperr(local_414);
    return -1;
  }
  puVar6 = (undefined4 *)_errno();
  *puVar6 = 9;
  puVar6 = (undefined4 *)__doserrno();
  *puVar6 = 5;
  return -1;
}
#undef local_404
#undef local_408
#undef local_40c
#undef local_410
#undef local_414
#undef local_418
#undef local_41c


/* ---- 0x004b3480  _dosmaperr ---- */
void _dosmaperr(uint param_1)

{
  uint *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar1 = (uint *)__doserrno();
  iVar3 = 0;
  *puVar1 = param_1;
  puVar1 = &UINT_004efa28;
  do {
    if (param_1 == *puVar1) {
      puVar2 = (undefined4 *)_errno();
      *puVar2 = *(undefined4 *)(iVar3 * 8 + IMG_ADDR(0x004efa2c));
      return;
    }
    puVar1 = puVar1 + 2;
    iVar3 = iVar3 + 1;
  } while (puVar1 < s_____004efb90);
  if ((0x12 < param_1) && (param_1 < 0x25)) {
    puVar2 = (undefined4 *)_errno();
    *puVar2 = 0xd;
    return;
  }
  if ((0xbb < param_1) && (param_1 < 0xcb)) {
    puVar2 = (undefined4 *)_errno();
    *puVar2 = 8;
    return;
  }
  puVar2 = (undefined4 *)_errno();
  *puVar2 = 0x16;
  return;
}

/* ---- 0x004b3500  _errno ---- */
int _errno(void)

{
  int iVar1;
  
  iVar1 = _getptd();
  return iVar1 + 8;
}

/* ---- 0x004b3510  __doserrno ---- */
int __doserrno(void)

{
  int iVar1;
  
  iVar1 = _getptd();
  return iVar1 + 0xc;
}

/* ---- 0x004b3520  _lseek ---- */
undefined4 _lseek(uint param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if ((param_1 < UINT_00906c00) &&
     ((*(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    _lock_fhandle(param_1);
    uVar1 = _lseek_lk(param_1,param_2,param_3);
    _unlock_fhandle(param_1);
    return uVar1;
  }
  puVar2 = (undefined4 *)_errno();
  *puVar2 = 9;
  puVar2 = (undefined4 *)__doserrno();
  *puVar2 = 0;
  return 0xffffffff;
}

/* ---- 0x004b35a0  _lseek_lk ---- */
int _lseek_lk(uint param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar1 = _get_osfhandle(param_1);
  if (iVar1 == -1) {
    puVar2 = (undefined4 *)_errno();
    *puVar2 = 9;
    return -1;
  }
  iVar1 = SetFilePointer(iVar1,param_2,0,param_3);
  if (iVar1 == -1) {
    iVar3 = GetLastError();
  }
  else {
    iVar3 = 0;
  }
  if (iVar3 != 0) {
    _dosmaperr(iVar3);
    return -1;
  }
  *(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) =
       *(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 0xfd;
  return iVar1;
}

/* ---- 0x004b3620  _input ---- */
/* scanf-family parsing core */

uint _input(undefined4 param_1,byte *param_2,uint *param_3)

{
  unsigned char _frame[0x1e0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte bVar2;
  uint *puVar3;
  byte *pbVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined *a1;
  uint uVar10;
  byte bVar11;
  byte *pbVar12;
  byte *pbVar13;
  char *pcVar14;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint extraout_EDX_01;
  char *pcVar15;
  uint a2;
  bool bVar16;
  bool bVar17;
  #define local_1cd (*(char *)(_frame + (0x1e0 - 0x1cd)))
  #define local_1cc (*(uint *)(_frame + (0x1e0 - 0x1cc)))
  #define local_1c7 (*(char *)(_frame + (0x1e0 - 0x1c7)))
  #define local_1c6 (*(char *)(_frame + (0x1e0 - 0x1c6)))
  #define local_1c5 (*(char *)(_frame + (0x1e0 - 0x1c5)))
  #define local_1c4 (*(uint *)(_frame + (0x1e0 - 0x1c4)))
  #define local_1c0 (*(char *)(_frame + (0x1e0 - 0x1c0)))
  #define local_1bf (*(char *)(_frame + (0x1e0 - 0x1bf)))
  #define local_1be (*(char *)(_frame + (0x1e0 - 0x1be)))
  #define local_1bd (*(byte *)(_frame + (0x1e0 - 0x1bd)))
  #define local_1bc (*(uint *)(_frame + (0x1e0 - 0x1bc)))
  #define local_1b8 (*(uint *)(_frame + (0x1e0 - 0x1b8)))
  #define local_1b4 (*(uint *)(_frame + (0x1e0 - 0x1b4)))
  #define local_1b0 (*(uint *)(_frame + (0x1e0 - 0x1b0)))
  #define local_1ac (*(uint *)(_frame + (0x1e0 - 0x1ac)))
  #define local_1a8 (*(uint *)(_frame + (0x1e0 - 0x1a8)))
  #define local_1a4 (*(uint *)(_frame + (0x1e0 - 0x1a4)))
  #define local_19e (*(byte *)(_frame + (0x1e0 - 0x19e)))
  #define local_19d (*(undefined1 *)(_frame + (0x1e0 - 0x19d)))
  #define local_19c (*(uint *)(_frame + (0x1e0 - 0x19c)))
  #define local_198 (*(uint *)(_frame + (0x1e0 - 0x198)))
  #define local_194 (*(uint *)(_frame + (0x1e0 - 0x194)))
  #define local_18e (*(undefined2 *)(_frame + (0x1e0 - 0x18e)))
  #define local_18c (*(uint *)(_frame + (0x1e0 - 0x18c)))
  #define local_188 (*(uint *)(_frame + (0x1e0 - 0x188)))
  #define local_184 (*(uint *)(_frame + (0x1e0 - 0x184)))
  #define local_180 (*(byte (*)[11])(_frame + (0x1e0 - 0x180)))
  #define local_175 (*(undefined1 *)(_frame + (0x1e0 - 0x175)))
  #define local_160 (*(char *)(_frame + (0x1e0 - 0x160)))
  #define local_15f (*(char (*)[351])(_frame + (0x1e0 - 0x15f)))
  
  local_1bf = '\0';
  local_1cc = 0;
  local_1ac = 0;
  bVar11 = *param_2;
  uVar9 = local_18c;
  do {
    if (bVar11 == 0) {
LAB_004b4276:
      if ((uVar9 == 0xffffffff) && ((local_1ac == 0 && (local_1bf == '\0')))) {
        local_1ac = 0xffffffff;
      }
      return local_1ac;
    }
    uVar10 = 0;
    if ((int)UINT_004ed52c < 2) {
      uVar5 = (byte)PTR_DAT_004ed320[(uint)bVar11 * 2] & 8;
    }
    else {
      uVar5 = _isctype(bVar11,8);
    }
    if (uVar5 != 0) {
      local_1cc = local_1cc - 1;
      uVar6 = ((code *)_whiteout)(&local_1cc,param_1,param_1);
      ((code *)_un_inc)(uVar6);
      param_2 = param_2 + 1;
      iVar7 = isspace(*param_2);
      while (iVar7 != 0) {
        param_2 = param_2 + 1;
        iVar7 = isspace(*param_2);
      }
    }
    if (*param_2 != 0x25) {
      local_1cc = local_1cc + 1;
      uVar9 = _inc(param_1);
      if (*param_2 != uVar9) goto LAB_004b425d;
      pbVar12 = param_2 + 1;
      if ((PTR_DAT_004ed320[(uVar9 & 0xff) * 2 + 1] & 0x80) != 0) {
        local_1cc = local_1cc + 1;
        uVar10 = _inc(param_1);
        if (param_2[1] != uVar10) {
          local_1cc = local_1cc - 1;
          _un_inc(uVar10,param_1);
          goto LAB_004b425d;
        }
        local_1cc = local_1cc - 1;
        pbVar12 = param_2 + 2;
      }
      goto LAB_004b4223;
    }
    local_1a4 = 0;
    local_1b4 = local_1b4 & 0xffffff00;
    local_1a8 = 0;
    local_1b0 = 0;
    local_1c4 = 0;
    local_1bd = 0;
    local_1be = '\0';
    local_1c5 = '\0';
    local_1cd = '\0';
    local_1c0 = '\0';
    local_1c7 = '\0';
    local_1c6 = '\x01';
    local_188 = 0;
    do {
      pbVar12 = param_2 + 1;
      uVar5 = (uint)*pbVar12;
      if ((int)UINT_004ed52c < 2) {
        uVar8 = (byte)PTR_DAT_004ed320[uVar5 * 2] & 4;
      }
      else {
        uVar8 = _isctype(uVar5,4);
      }
      if (uVar8 == 0) {
        switch(uVar5) {
        case 0x2a:
          local_1c5 = local_1c5 + '\x01';
          break;
        default:
switchD_004b37a0_caseD_2b:
          local_1cd = local_1cd + '\x01';
          break;
        case 0x46:
        case 0x4e:
          break;
        case 0x49:
          if ((param_2[2] != 0x36) || (param_2[3] != 0x34)) goto switchD_004b37a0_caseD_2b;
          uVar10 = uVar10 + 1;
          local_19c = 0;
          local_198 = 0;
          pbVar12 = param_2 + 3;
          break;
        case 0x4c:
          local_1c6 = local_1c6 + '\x01';
          break;
        case 0x68:
          local_1c6 = local_1c6 + -1;
          local_1c7 = local_1c7 + -1;
          break;
        case 0x6c:
          local_1c6 = local_1c6 + '\x01';
        case 0x77:
          local_1c7 = local_1c7 + '\x01';
        }
      }
      else {
        local_1b0 = local_1b0 + 1;
        local_1c4 = (uVar5 - 0x30) + local_1c4 * 10;
      }
      param_2 = pbVar12;
    } while (local_1cd == '\0');
    puVar3 = param_3;
    if (local_1c5 == '\0') {
      local_1b8 = *param_3;
      puVar3 = param_3 + 1;
      local_18c = (uint)param_3;
    }
    param_3 = puVar3;
    bVar17 = false;
    if ((local_1c7 == '\0') && ((*param_2 == 0x53 || (local_1c7 = -1, *param_2 == 0x43)))) {
      local_1c7 = '\x01';
    }
    local_1bc = *param_2 | 0x20;
    local_188 = uVar10;
    if (local_1bc != 0x6e) {
      if ((local_1bc == 99) || (local_1bc == 0x7b)) {
        local_1cc = local_1cc + 1;
        uVar9 = _inc(param_1);
      }
      else {
        uVar9 = _whiteout(&local_1cc,param_1);
      }
    }
    pbVar12 = (byte *)local_1b8;
    uVar5 = local_1bc;
    if ((local_1b0 != 0) && (local_1c4 == 0)) {
LAB_004b425d:
      local_1cc = local_1cc - 1;
      _un_inc(uVar9,param_1);
      goto LAB_004b4276;
    }
    switch(local_1bc) {
    case 99:
      if (local_1b0 == 0) {
        local_1b0 = 1;
        local_1c4 = local_1c4 + 1;
      }
      if ('\0' < local_1c7) {
        local_1c0 = '\x01';
      }
      pcVar14 = &DAT_004efb98;
      goto LAB_004b391e;
    case 100:
    case 0x6f:
    case 0x75:
      goto switchD_004b38b8_caseD_64;
    case 0x65:
    case 0x66:
    case 0x67:
      pcVar14 = &local_160;
      if (uVar9 == 0x2d) {
        local_160 = '-';
        pcVar14 = local_15f;
LAB_004b3f63:
        local_1c4 = local_1c4 - 1;
        local_1cc = local_1cc + 1;
        uVar9 = _inc(param_1);
      }
      else if (uVar9 == 0x2b) goto LAB_004b3f63;
      uVar10 = local_1a8;
      if ((local_1b0 == 0) || (0x15d < (int)local_1c4)) {
        local_1c4 = 0x15d;
      }
      while( true ) {
        if ((int)UINT_004ed52c < 2) {
          uVar5 = (byte)PTR_DAT_004ed320[uVar9 * 2] & 4;
        }
        else {
          uVar5 = _isctype(uVar9,4);
        }
        if ((uVar5 == 0) ||
           (uVar5 = local_1c4 - 1, bVar17 = local_1c4 == 0, local_1c4 = uVar5, bVar17)) break;
        *pcVar14 = (char)uVar9;
        pcVar14 = pcVar14 + 1;
        local_1cc = local_1cc + 1;
        uVar9 = _inc(param_1);
        uVar10 = uVar10 + 1;
      }
      if ((DAT_004ed530 == (char)uVar9) &&
         (uVar5 = local_1c4 - 1, bVar17 = local_1c4 != 0, local_1c4 = uVar5, bVar17)) {
        local_1cc = local_1cc + 1;
        uVar9 = _inc(param_1);
        *pcVar14 = DAT_004ed530;
        while( true ) {
          pcVar14 = pcVar14 + 1;
          if ((int)UINT_004ed52c < 2) {
            uVar5 = (byte)PTR_DAT_004ed320[uVar9 * 2] & 4;
          }
          else {
            uVar5 = _isctype(uVar9,4);
          }
          if ((uVar5 == 0) ||
             (uVar5 = local_1c4 - 1, bVar17 = local_1c4 == 0, local_1c4 = uVar5, bVar17)) break;
          *pcVar14 = (char)uVar9;
          uVar10 = uVar10 + 1;
          local_1cc = local_1cc + 1;
          uVar9 = _inc(param_1);
        }
      }
      pcVar15 = pcVar14;
      if ((uVar10 != 0) &&
         (((uVar9 == 0x65 || (uVar9 == 0x45)) &&
          (uVar5 = local_1c4 - 1, bVar17 = local_1c4 != 0, local_1c4 = uVar5, bVar17)))) {
        *pcVar14 = 'e';
        pcVar15 = pcVar14 + 1;
        local_1cc = local_1cc + 1;
        uVar9 = _inc(param_1);
        if (uVar9 == 0x2d) {
          *pcVar15 = '-';
          pcVar15 = pcVar14 + 2;
LAB_004b40be:
          uVar5 = local_1c4 - 1;
          if (local_1c4 != 0) goto LAB_004b40d3;
        }
        else if (uVar9 == 0x2b) goto LAB_004b40be;
        while( true ) {
          if ((int)UINT_004ed52c < 2) {
            uVar5 = (byte)PTR_DAT_004ed320[uVar9 * 2] & 4;
          }
          else {
            uVar5 = _isctype(uVar9,4);
          }
          if ((uVar5 == 0) ||
             (uVar5 = local_1c4 - 1, bVar17 = local_1c4 == 0, local_1c4 = uVar5, bVar17)) break;
          uVar10 = uVar10 + 1;
          *pcVar15 = (char)uVar9;
          pcVar15 = pcVar15 + 1;
LAB_004b40d3:
          local_1c4 = uVar5;
          local_1cc = local_1cc + 1;
          uVar9 = _inc(param_1);
        }
      }
      local_1cc = local_1cc - 1;
      _un_inc(uVar9,param_1);
      if (uVar10 == 0) goto LAB_004b4276;
      if (local_1c5 == '\0') {
        local_1ac = local_1ac + 1;
        *pcVar15 = '\0';
        (*(code *)PTR_FUN_004ed310)(local_1c6 + -1,local_1b8,&local_160);
      }
      break;
    default:
      if (*param_2 != uVar9) goto LAB_004b425d;
      local_1bf = local_1bf + -1;
      if (local_1c5 == '\0') {
        param_3 = (uint *)local_18c;
      }
      break;
    case 0x69:
      local_1bc = 100;
    case 0x78:
      uVar5 = local_1bc;
      if (uVar9 == 0x2d) {
        local_1be = '\x01';
LAB_004b3b72:
        local_1c4 = local_1c4 - 1;
        if ((local_1c4 == 0) && (local_1b0 != 0)) {
          bVar17 = true;
        }
        else {
          local_1cc = local_1cc + 1;
          uVar9 = _inc(param_1);
        }
      }
      else if (uVar9 == 0x2b) goto LAB_004b3b72;
      if (uVar9 == 0x30) {
        local_1cc = local_1cc + 1;
        uVar9 = _inc(param_1);
        if (((char)uVar9 == 'x') || ((char)uVar9 == 'X')) {
          local_1cc = local_1cc + 1;
          uVar9 = _inc(param_1);
          uVar5 = 0x78;
          local_1bc = 0x78;
        }
        else {
          local_1a8 = 1;
          if (uVar5 == 0x78) {
            local_1cc = local_1cc - 1;
            _un_inc(uVar9,param_1);
            uVar9 = 0x30;
          }
          else {
            uVar5 = 0x6f;
            local_1bc = 0x6f;
          }
        }
      }
      goto LAB_004b3c54;
    case 0x6e:
      uVar5 = local_1cc;
      if (local_1c5 != '\0') break;
      goto LAB_004b3f15;
    case 0x70:
      local_1c6 = '\x01';
switchD_004b38b8_caseD_64:
      if (uVar9 == 0x2d) {
        local_1be = '\x01';
LAB_004b3c2a:
        local_1c4 = local_1c4 - 1;
        if ((local_1c4 == 0) && (local_1b0 != 0)) {
          bVar17 = true;
        }
        else {
          local_1cc = local_1cc + 1;
          uVar9 = _inc(param_1);
        }
      }
      else if (uVar9 == 0x2b) goto LAB_004b3c2a;
LAB_004b3c54:
      uVar8 = local_1a4;
      a1 = (undefined *)local_19c;
      a2 = local_198;
      if (uVar10 == 0) {
        while (!bVar17) {
          if ((uVar5 == 0x78) || (uVar5 == 0x70)) {
            if ((int)UINT_004ed52c < 2) {
              uVar10 = (byte)PTR_DAT_004ed320[uVar9 * 2] & 0x80;
            }
            else {
              uVar10 = _isctype(uVar9,0x80);
            }
            if (uVar10 != 0) {
              uVar8 = uVar8 << 4;
              uVar9 = _hextodec(uVar9);
              goto LAB_004b3e4a;
            }
LAB_004b3e46:
            bVar17 = true;
          }
          else {
            if ((int)UINT_004ed52c < 2) {
              uVar10 = (byte)PTR_DAT_004ed320[uVar9 * 2] & 4;
            }
            else {
              uVar10 = _isctype(uVar9,4);
            }
            if (uVar10 == 0) goto LAB_004b3e46;
            if (uVar5 == 0x6f) {
              if (0x37 < (int)uVar9) goto LAB_004b3e46;
              uVar8 = uVar8 << 3;
            }
            else {
              uVar8 = uVar8 * 10;
            }
          }
LAB_004b3e4a:
          if (bVar17) {
            local_1cc = local_1cc - 1;
            _un_inc(uVar9,param_1);
          }
          else {
            local_1a8 = local_1a8 + 1;
            uVar8 = (uVar8 - 0x30) + uVar9;
            if ((local_1b0 == 0) || (local_1c4 = local_1c4 - 1, local_1c4 != 0)) {
              local_1cc = local_1cc + 1;
              uVar9 = _inc(param_1);
            }
            else {
              bVar17 = true;
            }
          }
        }
        local_1a4 = uVar8;
        if (local_1be != '\0') {
          local_1a4 = -uVar8;
        }
      }
      else {
        while (!bVar17) {
          if (local_1bc == 0x78) {
            if ((int)UINT_004ed52c < 2) {
              uVar10 = (byte)PTR_DAT_004ed320[uVar9 * 2] & 0x80;
            }
            else {
              uVar10 = _isctype(uVar9,0x80);
            }
            if (uVar10 != 0) {
              a1 = (undefined *)FUN_004b8f30(4,a2);
              uVar9 = _hextodec(uVar9);
              a2 = extraout_EDX;
              goto LAB_004b3d21;
            }
LAB_004b3d1d:
            bVar17 = true;
          }
          else {
            if ((int)UINT_004ed52c < 2) {
              uVar10 = (byte)PTR_DAT_004ed320[uVar9 * 2] & 4;
            }
            else {
              uVar10 = _isctype(uVar9,4);
            }
            if (uVar10 == 0) goto LAB_004b3d1d;
            if (local_1bc == 0x6f) {
              if (0x37 < (int)uVar9) goto LAB_004b3d1d;
              a1 = (undefined *)FUN_004b8f30(3,a2);
              a2 = extraout_EDX_00;
            }
            else {
              a1 = _allmul((int)a1,a2,10,0);
              a2 = extraout_EDX_01;
            }
          }
LAB_004b3d21:
          if (bVar17) {
            local_1cc = local_1cc - 1;
            _un_inc(uVar9,param_1);
          }
          else {
            uVar10 = uVar9 - 0x30;
            local_1a8 = local_1a8 + 1;
            bVar16 = CARRY4((uint)a1,uVar10);
            a1 = a1 + uVar10;
            a2 = a2 + ((int)uVar10 >> 0x1f) + (uint)bVar16;
            if ((local_1b0 == 0) || (local_1c4 = local_1c4 - 1, local_1c4 != 0)) {
              local_1cc = local_1cc + 1;
              uVar9 = _inc(param_1);
            }
            else {
              bVar17 = true;
            }
          }
        }
        local_19c = (uint)a1;
        local_198 = a2;
        if (local_1be != '\0') {
          local_19c = -(int)a1;
          local_198 = -(a2 + (a1 != (undefined *)0x0));
        }
      }
      uVar10 = local_1a8;
      if (local_1bc == 0x46) {
        uVar10 = 0;
      }
      if (uVar10 == 0) goto LAB_004b4276;
      if (local_1c5 == '\0') {
        local_1ac = local_1ac + 1;
        uVar5 = local_1a4;
        uVar10 = local_188;
LAB_004b3f15:
        if (uVar10 == 0) {
          if (local_1c6 == '\0') {
            *(short *)local_1b8 = (short)uVar5;
          }
          else {
            *(uint *)local_1b8 = uVar5;
          }
        }
        else {
          *(uint *)local_1b8 = local_19c;
          *(uint *)(local_1b8 + 4) = local_198;
        }
      }
      break;
    case 0x73:
      if ('\0' < local_1c7) {
        local_1c0 = '\x01';
      }
      pcVar14 = s_____004efb90;
LAB_004b391e:
      local_1bd = 0xff;
      pbVar13 = param_2;
LAB_004b3923:
      param_2 = pbVar13;
      pbVar13 = local_180;
      for (iVar7 = 8; iVar7 != 0; iVar7 = iVar7 + -1) {
        pbVar13[0] = 0;
        pbVar13[1] = 0;
        pbVar13[2] = 0;
        pbVar13[3] = 0;
        pbVar13 = pbVar13 + 4;
      }
      if ((local_1bc == 0x7b) && (*pcVar14 == 0x5d)) {
        local_1b4 = CONCAT31(PIECE(local_1b4,1,3),0x5d);
        pcVar14 = pcVar14 + 1;
        local_175 = 0x20;
      }
      bVar11 = *pcVar14;
      uVar10 = local_1b4;
      while (bVar11 != 0x5d) {
        pbVar13 = (byte *)(pcVar14 + 1);
        uVar5 = local_184 >> 8;
        local_184 = CONCAT31((int3)uVar5,bVar11);
        PIECE(local_1b4,1,3) = (undefined3)(uVar10 >> 8);
        if (((bVar11 == 0x2d) &&
            (PIECE(local_1b4,0,1) = (byte)uVar10, bVar2 = (byte)local_1b4, (byte)local_1b4 != 0)) &&
           (bVar1 = *pbVar13, bVar1 != 0x5d)) {
          pbVar13 = (byte *)(pcVar14 + 2);
          uVar5 = local_194 >> 8;
          bVar11 = (byte)local_1b4;
          if (bVar1 <= (byte)local_1b4) {
            local_1b4 = CONCAT31(PIECE(local_1b4,1,3),bVar1);
            bVar11 = bVar1;
            uVar10 = local_1b4;
            bVar1 = bVar2;
          }
          local_1b4 = uVar10;
          local_194 = CONCAT31((int3)uVar5,bVar1);
          if (bVar11 <= bVar1) {
            uVar10 = local_1b4 & 0xff;
            iVar7 = (bVar1 - uVar10) + 1;
            do {
              uVar5 = uVar10 >> 3;
              bVar11 = (byte)uVar10;
              uVar10 = uVar10 + 1;
              iVar7 = iVar7 + -1;
              local_180[uVar5] = local_180[uVar5] | '\x01' << (bVar11 & 7);
            } while (iVar7 != 0);
          }
          local_1b4 = local_1b4 & 0xffffff00;
        }
        else {
          local_1b4 = CONCAT31(PIECE(local_1b4,1,3),bVar11);
          local_180[bVar11 >> 3] = local_180[bVar11 >> 3] | '\x01' << (bVar11 & 7);
        }
        pcVar14 = (char *)pbVar13;
        uVar10 = local_1b4;
        bVar11 = *pbVar13;
      }
      if (*pcVar14 == 0) goto LAB_004b4276;
      if (local_1bc == 0x7b) {
        param_2 = (byte *)pcVar14;
      }
      local_1cc = local_1cc - 1;
      local_1b4 = uVar10;
      _un_inc(uVar9,param_1);
      pbVar13 = pbVar12;
      while( true ) {
        if ((local_1b0 != 0) &&
           (uVar10 = local_1c4 - 1, bVar17 = local_1c4 == 0, local_1c4 = uVar10, pbVar4 = pbVar13,
           bVar17)) goto LAB_004b3b0c;
        local_1cc = local_1cc + 1;
        uVar9 = _inc(param_1);
        if ((uVar9 == 0xffffffff) ||
           (bVar11 = (byte)uVar9,
           ((int)(char)(local_180[(int)uVar9 >> 3] ^ local_1bd) & 1 << (bVar11 & 7)) == 0)) break;
        if (local_1c5 == '\0') {
          if (local_1c0 == '\0') {
            *pbVar13 = bVar11;
            pbVar13 = pbVar13 + 1;
          }
          else {
            local_19e = bVar11;
            if ((PTR_DAT_004ed320[(uVar9 & 0xff) * 2 + 1] & 0x80) != 0) {
              local_1cc = local_1cc + 1;
              local_19d = _inc(param_1);
            }
            mbtowc(&local_18e,&local_19e,UINT_004ed52c);
            *(undefined2 *)pbVar13 = local_18e;
            pbVar13 = pbVar13 + 2;
          }
        }
        else {
          pbVar12 = pbVar12 + 1;
        }
      }
      local_1cc = local_1cc - 1;
      local_1b8 = (uint)pbVar13;
      _un_inc(uVar9,param_1);
      pbVar4 = (byte *)local_1b8;
LAB_004b3b0c:
      local_1b8 = (uint)pbVar4;
      if (pbVar12 == pbVar13) goto LAB_004b4276;
      if ((local_1c5 == '\0') && (local_1ac = local_1ac + 1, local_1bc != 99)) {
        if (local_1c0 == '\0') {
          *(undefined1 *)local_1b8 = 0;
        }
        else {
          *(undefined2 *)local_1b8 = 0;
        }
      }
      break;
    case 0x7b:
      if ('\0' < local_1c7) {
        local_1c0 = '\x01';
      }
      pbVar13 = param_2 + 1;
      pcVar14 = (char *)pbVar13;
      if (*pbVar13 == 0x5e) {
        pcVar14 = (char *)(param_2 + 2);
        param_2 = pbVar13;
        goto LAB_004b391e;
      }
      goto LAB_004b3923;
    }
    local_1bf = local_1bf + '\x01';
    pbVar12 = param_2 + 1;
LAB_004b4223:
    param_2 = pbVar12;
    if ((uVar9 == 0xffffffff) && ((*param_2 != 0x25 || (param_2[1] != 0x6e)))) goto LAB_004b4276;
    bVar11 = *param_2;
  } while( true );
}
#undef local_15f
#undef local_160
#undef local_175
#undef local_180
#undef local_184
#undef local_188
#undef local_18c
#undef local_18e
#undef local_194
#undef local_198
#undef local_19c
#undef local_19d
#undef local_19e
#undef local_1a4
#undef local_1a8
#undef local_1ac
#undef local_1b0
#undef local_1b4
#undef local_1b8
#undef local_1bc
#undef local_1bd
#undef local_1be
#undef local_1bf
#undef local_1c0
#undef local_1c4
#undef local_1c5
#undef local_1c6
#undef local_1c7
#undef local_1cc
#undef local_1cd


/* ---- 0x004b4360  _hextodec ---- */
uint _hextodec(uint param_1)

{
  uint uVar1;
  
  if ((int)UINT_004ed52c < 2) {
    uVar1 = (byte)PTR_DAT_004ed320[param_1 * 2] & 4;
  }
  else {
    uVar1 = _isctype(param_1,4);
  }
  if (uVar1 == 0) {
    param_1 = (param_1 & 0xffffffdf) - 7;
  }
  return param_1;
}

/* ---- 0x004b43a0  _inc ---- */
uint _inc(undefined4 *param_1)

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
  uVar3 = _filbuf(param_1);
  return uVar3;
}

/* ---- 0x004b43d0  _un_inc ---- */
void _un_inc(int param_1,undefined4 param_2)

{
  if (param_1 != -1) {
    _ungetc_lk(param_1,param_2);
  }
  return;
}

/* ---- 0x004b43f0  _whiteout ---- */
undefined4 _whiteout(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *param_1 = *param_1 + 1;
  uVar1 = _inc(param_2);
  iVar2 = isspace(uVar1);
  while (iVar2 != 0) {
    *param_1 = *param_1 + 1;
    uVar1 = _inc(param_2);
    iVar2 = isspace(uVar1);
  }
  return uVar1;
}

/* ---- 0x004b4560  __crtLCMapStringA ---- */
uint __crtLCMapStringA(int param_1,uint param_2,int param_3,undefined *param_4,int param_5,
                      int param_6,uint param_7,int param_8)

{
  int iVar1;
  uint uVar2;
  int a6;
  undefined *a5;
  uint uVar3;
  
  if (UINT_008d0ee4 == 0) {
    iVar1 = LCMapStringW(0,0x100,IMG_ADDR(0x004d8d8c),1,0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringA(0,0x100,IMG_ADDR(0x008d0874),1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      UINT_008d0ee4 = 2;
    }
    else {
      UINT_008d0ee4 = 1;
    }
  }
  iVar1 = (int)param_4;
  if (0 < (int)param_4) {
    iVar1 = _strncnt(param_3,param_4);
  }
  if (UINT_008d0ee4 == 2) {
    uVar2 = LCMapStringA(param_1,param_2,param_3,iVar1,param_5,param_6);
    return uVar2;
  }
  if (UINT_008d0ee4 != 1) {
    return UINT_008d0ee4;
  }
  param_4 = (undefined *)0x0;
  if (param_7 == 0) {
    param_7 = UINT_008d0b80;
  }
  a6 = MultiByteToWideChar(param_7,(-(uint)(param_8 != 0) & 8) + 1,param_3,iVar1,0,0);
  if (a6 == 0) {
    return 0;
  }
  a5 = malloc(a6 * 2);
  if (a5 == (undefined *)0x0) {
    return 0;
  }
  iVar1 = MultiByteToWideChar(param_7,1,param_3,iVar1,(int)a5,a6);
  if ((iVar1 != 0) && (uVar2 = LCMapStringW(param_1,param_2,(int)a5,a6,0,0), uVar2 != 0)) {
    if ((param_2 & 0x400) == 0) {
      param_4 = malloc(uVar2 * 2);
      if ((param_4 == (undefined *)0x0) ||
         (iVar1 = LCMapStringW(param_1,param_2,(int)a5,a6,(int)param_4,uVar2), iVar1 == 0))
      goto LAB_004b4768;
      if (param_6 == 0) {
        uVar2 = WideCharToMultiByte(param_7,0x220,(int)param_4,uVar2,0,0,0,0);
        uVar3 = uVar2;
      }
      else {
        uVar2 = WideCharToMultiByte(param_7,0x220,(int)param_4,uVar2,param_5,param_6,0,0);
        uVar3 = uVar2;
      }
    }
    else {
      if (param_6 == 0) goto LAB_004b46cf;
      if (param_6 < (int)uVar2) goto LAB_004b4768;
      uVar3 = LCMapStringW(param_1,param_2,(int)a5,a6,param_5,param_6);
    }
    if (uVar3 != 0) {
LAB_004b46cf:
      free(a5);
      free(param_4);
      return uVar2;
    }
  }
LAB_004b4768:
  free(a5);
  free(param_4);
  return 0;
}

/* ---- 0x004b4790  _strncnt ---- */
int _strncnt(char *param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = param_2;
  for (pcVar1 = param_1; (iVar2 != 0 && (iVar2 = iVar2 + -1, *pcVar1 != '\0')); pcVar1 = pcVar1 + 1)
  {
  }
  if (*pcVar1 != '\0') {
    return param_2;
  }
  return (int)pcVar1 - (int)param_1;
}

/* ---- 0x004b4ba0  _pow_except1 ---- */
float10 __fastcall
_pow_except1(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,uint param_7,uint param_8)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float10 in_ST0;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define uStack_1c (*(undefined4 *)(_frame + (0x40 - 0x1c)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define dStack_c (*(double *)(_frame + (0x40 - 0xc)))
  
  local_14 = param_7;
  local_10 = param_8;
  dStack_c = (double)in_ST0;
  uStack_1c = param_5;
  uStack_18 = param_6;
  _except1(param_2,&local_24,&param_3);
  return (float10)dStack_c;
}
#undef dStack_c
#undef local_10
#undef local_14
#undef local_24
#undef uStack_18
#undef uStack_1c


/* ---- 0x004b4bb7  _pow_except2 ---- */
float10 __fastcall
_pow_except2(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
            uint param_5,uint param_6)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float10 in_ST0;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_c (*(double *)(_frame + (0x40 - 0xc)))
  
  local_c = (double)in_ST0;
  local_1c = param_5;
  local_18 = param_6;
  _except1(param_2,&local_24,&param_3);
  return (float10)local_c;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_c


/* ---- 0x004b4d90  _pow_special_cases ---- */
/* Handles +-infinity and other special pow() operands */

undefined4 _pow_special_cases(double param_1,double param_2,double *param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = PIECE(param_1,4,4);
  iVar4 = PIECE(param_1,0,4);
  if (param_1 < 0.0) {
    param_1 = -param_1;
  }
  if ((PIECE(param_2,4,4) == 0x7ff00000) && (PIECE(param_2,0,4) == 0)) {
    if (1.0 < param_1) {
      *(uint *)param_3 = UINT_004f0620;
      *(uint *)((int)param_3 + 4) = UINT_004f0624;
      return 0;
    }
    if (param_1 < 1.0) {
      *(undefined4 *)param_3 = 0;
      *(undefined4 *)((int)param_3 + 4) = 0;
      return 0;
    }
  }
  else {
    if ((PIECE(param_2,4,4) != -0x100000) || (PIECE(param_2,0,4) != 0)) {
      if ((iVar3 == 0x7ff00000) && (iVar4 == 0)) {
        if (0.0 < param_2) {
          *(uint *)param_3 = UINT_004f0620;
          *(uint *)((int)param_3 + 4) = UINT_004f0624;
          return 0;
        }
        *(undefined4 *)param_3 = 0;
        if (param_2 < 0.0) {
          *(undefined4 *)((int)param_3 + 4) = 0;
          return 0;
        }
      }
      else {
        if (iVar3 != -0x100000) {
          return 0;
        }
        if (iVar4 != 0) {
          return 0;
        }
        iVar4 = ((undefined4 (*)(double, int))_is_integer_double)(PIECE(param_2,0,4),PIECE(param_2,4,4));
        uVar2 = UINT_004f0644;
        uVar1 = UINT_004f0624;
        if (0.0 < param_2) {
          if (iVar4 == 1) {
            *param_3 = -(double)CONCAT44(UINT_004f0624,UINT_004f0620);
            return 0;
          }
          *(uint *)param_3 = UINT_004f0620;
          *(uint *)((int)param_3 + 4) = uVar1;
          return 0;
        }
        if (param_2 < 0.0) {
          if (iVar4 == 1) {
            *(uint *)param_3 = UINT_004f0640;
            *(uint *)((int)param_3 + 4) = uVar2;
            return 0;
          }
          *(undefined4 *)param_3 = 0;
          *(undefined4 *)((int)param_3 + 4) = 0;
          return 0;
        }
        *(undefined4 *)param_3 = 0;
      }
      *(undefined4 *)((int)param_3 + 4) = 0x3ff00000;
      return 0;
    }
    if (1.0 < param_1) {
      *(undefined4 *)param_3 = 0;
      *(undefined4 *)((int)param_3 + 4) = 0;
      return 0;
    }
    if (param_1 < 1.0) {
      *(uint *)param_3 = UINT_004f0620;
      *(uint *)((int)param_3 + 4) = UINT_004f0624;
      return 0;
    }
  }
  *(uint *)param_3 = UINT_004f0628;
  *(uint *)((int)param_3 + 4) = UINT_004f062c;
  return 1;
}

/* ---- 0x004b4fc0  _is_integer_double ---- */
/* Returns 2 for even integers, 1 for odd integers, 0 otherwise (pow helper) */

undefined4 _is_integer_double(double param_1)

{
  uint uVar1;
  float fVar2;
  
  uVar1 = FUN_004ba190(PIECE(param_1,0,4),PIECE(param_1,4,4));
  if ((uVar1 & 0x90) == 0) {
    fVar2 = FUN_004ba170(param_1);
    if ((double)fVar2 == param_1) {
      fVar2 = FUN_004ba170(param_1 / 2.0);
      if (fVar2 == (float)(param_1 / 2.0)) {
        return 2;
      }
      return 1;
    }
  }
  return 0;
}

/* ---- 0x004b5050  _commit ---- */
undefined4 _commit(uint param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  
  if (UINT_00906c00 <= param_1) {
LAB_004b50dc:
    puVar3 = (undefined4 *)_errno();
    *puVar3 = 9;
    return 0xffffffff;
  }
  if ((*(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) == 0)
  goto LAB_004b50dc;
  _lock_fhandle(param_1);
  if ((*(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0) {
    iVar1 = _get_osfhandle(param_1);
    iVar1 = FlushFileBuffers(iVar1);
    if (iVar1 == 0) {
      iVar1 = GetLastError();
    }
    else {
      iVar1 = 0;
    }
    uVar4 = 0;
    if (iVar1 == 0) goto LAB_004b50cd;
    piVar2 = (int *)__doserrno();
    *piVar2 = iVar1;
  }
  puVar3 = (undefined4 *)_errno();
  *puVar3 = 9;
  uVar4 = 0xffffffff;
LAB_004b50cd:
  _unlock_fhandle(param_1);
  return uVar4;
}

/* ---- 0x004b50f0  __loctotime_t ---- */
int __loctotime_t(int param_1,int param_2,int param_3,uint param_4,int param_5,int param_6,
                 int param_7)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  #define local_24 (*(undefined1 (*)[8])(_frame + (0x40 - 0x24)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  
  uVar3 = param_1 - 0x76c;
  if (((int)uVar3 < 0x46) || (0x8a < (int)uVar3)) {
    return -1;
  }
  uVar4 = *(int *)(&DAT_004f067c + param_2 * 4) + param_3;
  if (((uVar3 & 3) == 0) && (2 < param_2)) {
    uVar4 = uVar4 + 1;
  }
  __tzset();
  local_1c = param_4;
  local_14 = param_2 - 1;
  iVar1 = param_6 + (param_5 +
                    (param_4 + ((param_1 + -0x76d >> 2) + uVar3 * 0x16d + uVar4) * 0x18) * 0x3c) *
                    0x3c + 0x7c558180 + UINT_004f0400;
  if (param_7 != 1) {
    if (param_7 != -1) {
      return iVar1;
    }
    if (UINT_004f0404 == 0) {
      return iVar1;
    }
    local_10 = uVar3;
    local_8 = uVar4;
    iVar2 = _isindst(local_24);
    if (iVar2 == 0) {
      return iVar1;
    }
  }
  return iVar1 + UINT_004f0408;
}
#undef local_10
#undef local_14
#undef local_1c
#undef local_24
#undef local_8


/* ---- 0x004b51e0  __InternalCxxFrameHandler ---- */
undefined4
__InternalCxxFrameHandler
          (int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int *param_5,
          int param_6,undefined4 param_7,uint param_8)

{
  undefined4 uVar1;
  
  if (*param_5 != 0x19930520) {
    FUN_004b5cf0();
  }
  if ((*(byte *)(param_1 + 1) & 0x66) == 0) {
    if (param_5[3] != 0) {
      if (((*param_1 == -0x1f928c9d) && (0x19930520 < (uint)param_1[5])) &&
         (*(code **)(param_1[7] + 8) != (code *)0x0)) {
        uVar1 = (**(code **)(param_1[7] + 8))
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8 & 0xff);
        return uVar1;
      }
      FindHandler(param_1,param_2,param_3,param_4,param_5,param_8,param_6,param_7);
    }
  }
  else if ((param_5[1] != 0) && (param_6 == 0)) {
    FrameUnwindToState(param_2,param_4,param_5,0xffffffff);
    return 1;
  }
  return 1;
}

/* ---- 0x004b52b0  FindHandler ---- */
void FindHandler(int *param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5,
                char param_6,undefined4 param_7,undefined4 param_8)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  byte *pbVar7;
  byte *pbVar8;
  bool bVar9;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  uVar6 = *(uint *)(param_2 + 8);
  local_10 = uVar6;
  if (((int)uVar6 < -1) || (*(int *)(param_5 + 4) <= (int)uVar6)) {
    FUN_004b5cf0();
  }
  if (*param_1 == -0x1f928c9d) {
    if (((param_1[4] == 3) && (param_1[5] == 0x19930520)) && (param_1[7] == 0)) {
      iVar2 = _getptd();
      if (*(int *)(iVar2 + 0x6c) == 0) {
        return;
      }
      iVar2 = _getptd();
      param_1 = *(int **)(iVar2 + 0x6c);
      iVar2 = _getptd();
      param_3 = *(undefined4 *)(iVar2 + 0x70);
      iVar2 = _ValidateRead(param_1,1);
      if (iVar2 == 0) {
        FUN_004b5cf0();
      }
      if (*param_1 != -0x1f928c9d) goto LAB_004b5526;
      if (((param_1[4] == 3) && (param_1[5] == 0x19930520)) && (param_1[7] == 0)) {
        FUN_004b5cf0();
      }
    }
    if (((*param_1 == -0x1f928c9d) && (param_1[4] == 3)) && (param_1[5] == 0x19930520)) {
      local_1c = FUN_004af5e0(param_5,param_7,uVar6,&local_20,&local_c);
      if (local_20 < local_c) {
        do {
          if ((*(int *)local_1c <= (int)uVar6) && ((int)uVar6 <= *(int *)(local_1c + 4))) {
            local_14 = *(uint *)(local_1c + 0xc);
            pbVar8 = *(byte **)(local_1c + 0x10);
            if (0 < (int)local_14) {
              local_8 = (uint)(*(uint **)(param_1[7] + 0xc) + 1);
              local_4 = **(uint **)(param_1[7] + 0xc);
              do {
                local_18 = local_4;
                if (0 < (int)local_4) {
                  iVar2 = *(int *)(pbVar8 + 4);
                  puVar5 = (uint *)local_8;
                  do {
                    if ((iVar2 == 0) || (pbVar3 = (byte *)(iVar2 + 8), *(char *)(iVar2 + 8) == '\0')
                       ) {
LAB_004b547f:
                      bVar9 = true;
                    }
                    else {
                      iVar4 = *(int *)((byte *)*puVar5 + 4);
                      if (iVar2 == iVar4) {
LAB_004b545a:
                        if (((((*(byte *)*puVar5 & 2) == 0) || ((*pbVar8 & 8) != 0)) &&
                            (((*(uint *)param_1[7] & 1) == 0 || ((*pbVar8 & 1) != 0)))) &&
                           (((*(uint *)param_1[7] & 2) == 0 || ((*pbVar8 & 2) != 0))))
                        goto LAB_004b547f;
                        bVar9 = false;
                      }
                      else {
                        pbVar7 = (byte *)(iVar4 + 8);
                        do {
                          bVar1 = *pbVar3;
                          bVar9 = bVar1 < *pbVar7;
                          if (bVar1 != *pbVar7) {
LAB_004b543d:
                            iVar4 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
                            goto LAB_004b5442;
                          }
                          if (bVar1 == 0) break;
                          bVar1 = pbVar3[1];
                          bVar9 = bVar1 < pbVar7[1];
                          if (bVar1 != pbVar7[1]) goto LAB_004b543d;
                          pbVar3 = pbVar3 + 2;
                          pbVar7 = pbVar7 + 2;
                        } while (bVar1 != 0);
                        iVar4 = 0;
LAB_004b5442:
                        if (iVar4 == 0) goto LAB_004b545a;
                        bVar9 = false;
                      }
                    }
                    if (bVar9) {
                      CatchIt(param_1,param_2,param_3,param_4,param_5,pbVar8,*puVar5,local_1c,
                              param_7,param_8);
                      uVar6 = local_10;
                      goto LAB_004b54ef;
                    }
                    puVar5 = puVar5 + 1;
                    local_18 = local_18 - 1;
                  } while (0 < (int)local_18);
                }
                local_14 = local_14 - 1;
                pbVar8 = pbVar8 + 0x10;
                uVar6 = local_10;
              } while (0 < (int)local_14);
            }
          }
LAB_004b54ef:
          local_20 = local_20 + 1;
          local_1c = local_1c + 0x14;
        } while (local_20 < local_c);
      }
      if (param_6 == '\0') {
        return;
      }
      ((code *)FUN_004b5b60)(param_1,1);
      return;
    }
  }
LAB_004b5526:
  if (param_6 != '\0') {
    terminate();
    return;
  }
  Eh_FindForeignHandler(param_1,param_2,param_3,param_4,param_5,uVar6,param_7,param_8);
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004b5570  Eh_FindForeignHandler ---- */
void Eh_FindForeignHandler
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,int param_6,undefined4 param_7,undefined4 param_8)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  int iVar3;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar1 = _getptd();
  if ((*(int *)(iVar1 + 0x68) != 0) &&
     (iVar1 = FUN_004af480(param_1,param_2,param_3,param_4,param_5,param_7,param_8), iVar1 != 0)) {
    return;
  }
  piVar2 = (int *)FUN_004af5e0(param_5,param_7,param_6,&local_8,&local_4);
  if (local_8 < local_4) {
    do {
      if ((*piVar2 <= param_6) && (param_6 <= piVar2[1])) {
        iVar3 = piVar2[4] + piVar2[3] * 0x10;
        iVar1 = *(int *)(iVar3 + -0xc);
        if ((iVar1 == 0) || (*(char *)(iVar1 + 8) == '\0')) {
          CatchIt(param_1,param_2,param_3,param_4,param_5,iVar3 + -0x10,0,piVar2,param_7,param_8);
        }
      }
      local_8 = local_8 + 1;
      piVar2 = piVar2 + 5;
    } while (local_8 < local_4);
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004b5650  FrameUnwindToState ---- */
void FrameUnwindToState(int param_1,undefined4 param_2,int param_3,int param_4)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int a1;
  int iVar1;
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_004d8df0;
  puStack_10 = &LAB_004b1c48;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_14;
  for (iVar1 = *(int *)(param_1 + 8); local_8 = 0xffffffff, iVar1 != param_4;
      iVar1 = *(int *)(*(int *)(param_3 + 8) + iVar1 * 8)) {
    if ((iVar1 < 0) || (*(int *)(param_3 + 4) <= iVar1)) {
      FUN_004b5cf0();
    }
    local_8 = 0;
    a1 = *(int *)(*(int *)(param_3 + 8) + 4 + iVar1 * 8);
    if (a1 != 0) {
      FUN_004b5c10(a1,param_1,0x103);
    }
  }
  *(int *)(param_1 + 8) = iVar1;
  *unaff_FS_OFFSET = local_14;
  return;
}
#undef local_14
#undef local_1c
#undef local_20
#undef local_8
#undef puStack_10
#undef puStack_c


/* ---- 0x004b5730  CatchIt ---- */
void CatchIt(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
            int param_6,int param_7,undefined4 *param_8,undefined4 param_9,int param_10)

{
  int iVar1;
  
  if (param_7 != 0) {
    BuildCatchObject(param_1,param_2,param_6,param_7);
  }
  if (param_10 == 0) {
    param_10 = param_2;
  }
  _UnwindNestedFrames(param_10,param_1);
  FrameUnwindToState(param_2,param_4,param_5,*param_8);
  *(int *)(param_2 + 8) = param_8[1] + 1;
  iVar1 = CallCatchBlock(param_1,param_2,param_3,param_5,*(undefined4 *)(param_6 + 0xc),param_9,
                         0x100);
  if (iVar1 != 0) {
    ((code *)_CallSettingFrame)(iVar1,param_2);
  }
  return;
}

/* ---- 0x004b57c0  CallCatchBlock ---- */
undefined4
CallCatchBlock(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x40 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004d8e00;
  puStack_10 = &LAB_004b1c48;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_14;
  _getptd();
  _getptd();
  iVar1 = _getptd();
  *(undefined4 *)(iVar1 + 0x6c) = param_1;
  iVar1 = _getptd();
  *(undefined4 *)(iVar1 + 0x70) = param_3;
  local_8 = 1;
  uVar2 = FUN_004af3f0(param_2,param_4,param_5,param_6,param_7);
  local_8 = 0xffffffff;
  Eh_CallCatchBlockInner();
  *unaff_FS_OFFSET = local_14;
  return uVar2;
}
#undef local_14
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_8
#undef puStack_10
#undef puStack_c


/* ---- 0x004b58b8  Eh_CallCatchBlockInner ---- */
void Eh_CallCatchBlockInner(void)

{
  int iVar1;
  int unaff_EBX;
  int unaff_EBP;
  int unaff_ESI;
  int *unaff_EDI;
  
  *(undefined4 *)(unaff_ESI + -4) = *(undefined4 *)(unaff_EBP + -0x28);
  iVar1 = _getptd();
  *(undefined4 *)(iVar1 + 0x6c) = *(undefined4 *)(unaff_EBP + -0x1c);
  iVar1 = _getptd();
  *(undefined4 *)(iVar1 + 0x70) = *(undefined4 *)(unaff_EBP + -0x20);
  if ((((*unaff_EDI == -0x1f928c9d) && (unaff_EDI[4] == 3)) && (unaff_EDI[5] == 0x19930520)) &&
     ((*(int *)(unaff_EBP + -0x24) == 0 && (unaff_EBX != 0)))) {
    _unwind_handler();
    ((code *)FUN_004b5b60)();
  }
  return;
}

/* ---- 0x004b5950  BuildCatchObject ---- */
void BuildCatchObject(int param_1,int param_2,byte *param_3,byte *param_4)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_004d8e18;
  puStack_10 = &LAB_004b1c48;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_14;
  if (((*(int *)(param_3 + 4) != 0) && (*(char *)(*(int *)(param_3 + 4) + 8) != '\0')) &&
     (*(int *)(param_3 + 8) != 0)) {
    piVar1 = (int *)(param_2 + 0xc + *(int *)(param_3 + 8));
    local_8 = 0;
    if ((*param_3 & 8) == 0) {
      if ((*param_4 & 1) == 0) {
        if (*(int *)(param_4 + 0x18) == 0) {
          iVar2 = _ValidateRead(*(undefined4 *)(param_1 + 0x18),1);
          if ((iVar2 != 0) && (iVar2 = _ValidateWrite(piVar1,1), iVar2 != 0)) {
            uVar3 = ((code *)FUN_004b5be0)(*(undefined4 *)(param_1 + 0x18),param_4 + 8,
                                 *(undefined4 *)(param_4 + 0x14));
            ((code *)memmove)(piVar1,uVar3);
            goto LAB_004b5b40;
          }
        }
        else {
          iVar2 = _ValidateRead(*(undefined4 *)(param_1 + 0x18),1);
          if (((iVar2 != 0) && (iVar2 = _ValidateWrite(piVar1,1), iVar2 != 0)) &&
             (iVar2 = _ValidateExecute(*(undefined4 *)(param_4 + 0x18)), iVar2 != 0)) {
            if ((*param_4 & 4) == 0) {
              uVar3 = FUN_004b5be0(*(undefined4 *)(param_1 + 0x18),param_4 + 8);
              ((code *)FUN_004af340)(piVar1,*(undefined4 *)(param_4 + 0x18),uVar3);
            }
            else {
              uVar3 = ((code *)FUN_004b5be0)(*(undefined4 *)(param_1 + 0x18),param_4 + 8,1);
              ((code *)FUN_004af340)(piVar1,*(undefined4 *)(param_4 + 0x18),uVar3);
            }
            goto LAB_004b5b40;
          }
        }
      }
      else {
        iVar2 = _ValidateRead(*(undefined4 *)(param_1 + 0x18),1);
        if ((iVar2 != 0) && (iVar2 = _ValidateWrite(piVar1,1), iVar2 != 0)) {
          memmove(piVar1,*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_4 + 0x14));
          if ((*(int *)(param_4 + 0x14) == 4) && (*piVar1 != 0)) {
            iVar2 = FUN_004b5be0(*piVar1,param_4 + 8);
            *piVar1 = iVar2;
          }
          goto LAB_004b5b40;
        }
      }
    }
    else {
      iVar2 = _ValidateRead(*(undefined4 *)(param_1 + 0x18),1);
      if ((iVar2 != 0) && (iVar2 = _ValidateWrite(piVar1,1), iVar2 != 0)) {
        iVar2 = *(int *)(param_1 + 0x18);
        *piVar1 = iVar2;
        iVar2 = FUN_004b5be0(iVar2,param_4 + 8);
        *piVar1 = iVar2;
        goto LAB_004b5b40;
      }
    }
    FUN_004b5cf0();
  }
LAB_004b5b40:
  *unaff_FS_OFFSET = local_14;
  return;
}
#undef local_14
#undef local_1c
#undef local_8
#undef puStack_10
#undef puStack_c


/* ---- 0x004b5c60  terminate ---- */
void terminate(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_004d8e38;
  puStack_10 = &LAB_004b1c48;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_14;
  local_8 = 0;
  iVar1 = _getptd();
  if (*(int *)(iVar1 + 0x60) != 0) {
    local_8 = 1;
    iVar1 = _getptd();
    (**(code **)(iVar1 + 0x60))();
  }
  local_8 = 0xffffffff;
  FUN_004b5cd7();
  *unaff_FS_OFFSET = local_14;
  return;
}
#undef local_14
#undef local_1c
#undef local_8
#undef puStack_10
#undef puStack_c


/* ---- 0x004b6ce0  _getbuf ---- */
void _getbuf(int *param_1)

{
  undefined *puVar1;
  
  UINT_008d0ed0 = UINT_008d0ed0 + 1;
  puVar1 = malloc(0x1000);
  param_1[2] = (int)puVar1;
  if (puVar1 != (undefined *)0x0) {
    param_1[3] = param_1[3] | 8;
    param_1[6] = 0x1000;
    *param_1 = param_1[2];
    param_1[1] = 0;
    return;
  }
  param_1[6] = 2;
  param_1[3] = param_1[3] | 4;
  param_1[2] = (int)(param_1 + 5);
  *param_1 = (int)(param_1 + 5);
  param_1[1] = 0;
  return;
}

/* ---- 0x004b6d40  _isatty ---- */
byte _isatty(uint param_1)

{
  if (UINT_00906c00 <= param_1) {
    return 0;
  }
  return *(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 0x40;
}

/* ---- 0x004b6d70  wctomb ---- */
undefined4 wctomb(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  bool bVar2;
  
  InterlockedIncrement(IMG_ADDR(0x00906c0c));
  bVar2 = UINT_00906c08 != 0;
  if (bVar2) {
    InterlockedDecrement(IMG_ADDR(0x00906c0c));
    _lock(0x13);
  }
  uVar1 = _wctomb_lk(param_1,param_2);
  if (!bVar2) {
    InterlockedDecrement(IMG_ADDR(0x00906c0c));
    return uVar1;
  }
  _unlock(0x13);
  return uVar1;
}

/* ---- 0x004b6de0  _wctomb_lk ---- */
int _wctomb_lk(undefined1 *param_1,ushort param_2)

{
  undefined1 *a5;
  int iVar1;
  undefined4 *puVar2;
  
  a5 = param_1;
  if (param_1 == (undefined1 *)0x0) {
    return 0;
  }
  if (UINT_008d0b70 == 0) {
    if (param_2 < 0x100) {
      *param_1 = (char)param_2;
      return 1;
    }
  }
  else {
    param_1 = (undefined1 *)0x0;
    iVar1 = WideCharToMultiByte(UINT_008d0b80,0x220,(int)&param_2,1,(int)a5,UINT_004ed52c,0,
                                (int)&param_1);
    if ((iVar1 != 0) && (param_1 == (undefined1 *)0x0)) {
      return iVar1;
    }
  }
  puVar2 = (undefined4 *)_errno();
  *puVar2 = 0x2a;
  return -1;
}

/* ---- 0x004b6e60  _aulldiv ---- */
undefined * __stdcall _aulldiv(int a1,int a2,int a3,int a4)

{
  ulonglong uVar1;
  longlong lVar2;
  undefined *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  iVar4 = a1;
  uVar9 = a4;
  uVar6 = a2;
  uVar8 = a3;
  if (a4 == 0) {
    puVar3 = (undefined *)
             (((ulonglong)(uint)a2 % (ulonglong)(uint)a3 << 0x20 | (ulonglong)(uint)a1) /
             (ulonglong)(uint)a3);
  }
  else {
    do {
      uVar5 = uVar9 >> 1;
      uVar8 = (uint)(CONCAT14((uVar9 & 1) != 0,uVar8) >> 1);
      uVar7 = uVar6 >> 1;
      iVar4 = (int)(CONCAT14((uVar6 & 1) != 0,iVar4) >> 1);
      uVar9 = uVar5;
      uVar6 = uVar7;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar7,iVar4) / (ulonglong)uVar8;
    puVar3 = (undefined *)uVar1;
    lVar2 = (ulonglong)(uint)a3 * (uVar1 & 0xffffffff);
    uVar8 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar9 = uVar8 + (int)puVar3 * a4;
    if (((CARRY4(uVar8,(int)puVar3 * a4)) || ((uint)a2 < uVar9)) ||
       (((uint)a2 <= uVar9 && ((uint)a1 < (uint)lVar2)))) {
      puVar3 = puVar3 + -1;
    }
  }
  return puVar3;
}

/* ---- 0x004b6ed0  _aullrem ---- */
undefined * __stdcall _aullrem(int a1,int a2,int a3,int a4)

{
  ulonglong uVar1;
  longlong lVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined *puVar7;
  uint uVar8;
  uint uVar9;
  
  iVar3 = a1;
  uVar5 = a4;
  uVar9 = a2;
  uVar4 = a3;
  if (a4 == 0) {
    puVar7 = (undefined *)
             (((ulonglong)(uint)a2 % (ulonglong)(uint)a3 << 0x20 | (ulonglong)(uint)a1) %
             (ulonglong)(uint)a3);
  }
  else {
    do {
      uVar6 = uVar5 >> 1;
      uVar4 = (uint)(CONCAT14((uVar5 & 1) != 0,uVar4) >> 1);
      uVar8 = uVar9 >> 1;
      iVar3 = (int)(CONCAT14((uVar9 & 1) != 0,iVar3) >> 1);
      uVar5 = uVar6;
      uVar9 = uVar8;
    } while (uVar6 != 0);
    uVar1 = CONCAT44(uVar8,iVar3) / (ulonglong)uVar4;
    uVar4 = (int)uVar1 * a4;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)(uint)a3;
    uVar9 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar5 = (uint)lVar2;
    uVar6 = uVar9 + uVar4;
    if (((CARRY4(uVar9,uVar4)) || ((uint)a2 < uVar6)) || (((uint)a2 <= uVar6 && ((uint)a1 < uVar5)))
       ) {
      uVar5 = uVar5 - a3;
    }
    puVar7 = (undefined *)-(uVar5 - a1);
  }
  return puVar7;
}

/* ---- 0x004b7370  _ld12tocvt ---- */
/* Converts a 12-byte long double record to double/float (float conversion core) */

undefined4 _ld12tocvt(ushort *param_1,uint *param_2,int *param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(undefined1 (*)[12])(_frame + (0x30 - 0xc)))
  
  uVar1 = param_1[5];
  local_14 = *(uint *)(param_1 + 1);
  local_18 = *(uint *)(param_1 + 3);
  uVar4 = uVar1 & 0x7fff;
  iVar5 = uVar4 - 0x3fff;
  local_10 = (uint)*param_1 << 0x10;
  if (iVar5 == -0x3fff) {
    iVar5 = 0;
    iVar2 = FUN_004b7290(&local_18);
    if (iVar2 == 0) {
      FUN_004b7280(&local_18);
      uVar3 = 2;
      goto LAB_004b74f1;
    }
  }
  else {
    FUN_004b7260(local_c,&local_18);
    iVar2 = FUN_004b71c0(&local_18,param_3[2]);
    if (iVar2 != 0) {
      iVar5 = uVar4 - 0x3ffe;
    }
    iVar2 = param_3[1];
    if (iVar5 < iVar2 - param_3[2]) {
      FUN_004b7280(&local_18);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_004b74f1;
    }
    if (iVar5 <= iVar2) {
      FUN_004b7260(&local_18,local_c);
      FUN_004b72b0(&local_18,iVar2 - iVar5);
      FUN_004b71c0(&local_18,param_3[2]);
      FUN_004b72b0(&local_18,param_3[3] + 1);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_004b74f1;
    }
    if (*param_3 <= iVar5) {
      FUN_004b7280(&local_18);
      local_18 = local_18 | 0x80000000;
      FUN_004b72b0(&local_18,param_3[3]);
      iVar5 = param_3[5] + *param_3;
      uVar3 = 1;
      goto LAB_004b74f1;
    }
    iVar5 = param_3[5] + iVar5;
    local_18 = local_18 & 0x7fffffff;
    FUN_004b72b0(&local_18,param_3[3]);
  }
  uVar3 = 0;
LAB_004b74f1:
  uVar4 = iVar5 << (0x1fU - (char)param_3[3] & 0x1f) | -(uint)((uVar1 & 0x8000) != 0) & 0x80000000 |
          local_18;
  if (param_3[4] == 0x40) {
    param_2[1] = uVar4;
    *param_2 = local_14;
    return uVar3;
  }
  if (param_3[4] == 0x20) {
    *param_2 = uVar4;
  }
  return uVar3;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_c


/* ---- 0x004b7540  _ld12tod ---- */
undefined * __cdecl _ld12tod(uint param_1,uint param_2)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)_ld12tocvt(param_1,param_2,&DAT_004f03d0);
  return puVar1;
}

/* ---- 0x004b7990  __crtGetStringTypeA ---- */
uint __crtGetStringTypeA(int param_1,int param_2,int param_3,int param_4,uint param_5,uint param_6,
                        int param_7)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  int a5;
  #define local_2 (*(undefined1 (*)[2])(_frame + (0x20 - 0x2)))
  
  a5 = 0;
  if (UINT_008d0f54 == 0) {
    iVar1 = GetStringTypeW(1,IMG_ADDR(0x004d8d8c),1,(int)local_2);
    if (iVar1 == 0) {
      iVar1 = GetStringTypeA(0,1,IMG_ADDR(0x008d0874),1,(int)local_2);
      if (iVar1 == 0) {
        return 0;
      }
      UINT_008d0f54 = 2;
    }
    else {
      UINT_008d0f54 = 1;
    }
  }
  if (UINT_008d0f54 == 2) {
    if (param_6 == 0) {
      param_6 = UINT_008d0b70;
    }
    uVar2 = GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
    return uVar2;
  }
  param_6 = UINT_008d0f54;
  if (UINT_008d0f54 == 1) {
    param_6 = 0;
    if (param_5 == 0) {
      param_5 = UINT_008d0b80;
    }
    iVar1 = MultiByteToWideChar(param_5,(-(uint)(param_7 != 0) & 8) + 1,param_2,param_3,0,0);
    if (iVar1 != 0) {
      a5 = calloc(2,iVar1);
      if (a5 != 0) {
        iVar1 = MultiByteToWideChar(param_5,1,param_2,param_3,a5,iVar1);
        if (iVar1 != 0) {
          uVar2 = GetStringTypeW(param_1,a5,iVar1,param_4);
          free(a5);
          return uVar2;
        }
      }
    }
    free(a5);
  }
  return param_6;
}
#undef local_2


/* ---- 0x004b7ad0  calloc ---- */
undefined4 * calloc(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint a3;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  a3 = param_2 * param_1;
  if (a3 < 0xffffffe1) {
    if (a3 == 0) {
      a3 = 0x10;
    }
    else {
      a3 = a3 + 0xf & 0xfffffff0;
    }
  }
  do {
    puVar3 = (undefined4 *)0x0;
    if (a3 < 0xffffffe1) {
      if (UINT_004efa24 < a3) {
LAB_004b7b44:
        if (puVar3 != (undefined4 *)0x0) {
          return puVar3;
        }
      }
      else {
        _lock(9);
        puVar3 = (undefined4 *)__sbh_alloc_block(a3 >> 4);
        _unlock(9);
        if (puVar3 != (undefined4 *)0x0) {
          puVar4 = puVar3;
          for (uVar2 = a3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar4 = 0;
            puVar4 = puVar4 + 1;
          }
          for (uVar2 = a3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *(undefined1 *)puVar4 = 0;
            puVar4 = (undefined4 *)((int)puVar4 + 1);
          }
          goto LAB_004b7b44;
        }
      }
      puVar3 = (undefined4 *)HeapAlloc(UINT_00906ae4,8,a3);
    }
    if ((puVar3 != (undefined4 *)0x0) || (UINT_008d0ed4 == 0)) {
      return puVar3;
    }
    iVar1 = _callnewh(a3);
    if (iVar1 == 0) {
      return (undefined4 *)0x0;
    }
  } while( true );
}

/* ---- 0x004b7b80  __crtMessageBoxA ---- */
undefined4 __crtMessageBoxA(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int a1;
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = 0;
  if (UINT_008d0f58 != 0) {
LAB_004b7bd0:
    if (UINT_008d0f5c != 0) {
      iVar2 = (*(code *)UINT_008d0f5c)();
    }
    if ((iVar2 != 0) && (UINT_008d0f60 != 0)) {
      iVar2 = (*(code *)UINT_008d0f60)(iVar2);
    }
    uVar1 = (*(code *)UINT_008d0f58)(iVar2,param_1,param_2,param_3);
    return uVar1;
  }
  a1 = LoadLibraryA(IMG_ADDR(0x004d9518));
  if (a1 != 0) {
    UINT_008d0f58 = GetProcAddress(a1,IMG_ADDR(0x004d950c));
    if (UINT_008d0f58 != 0) {
      UINT_008d0f5c = GetProcAddress(a1,IMG_ADDR(0x004d94fc));
      UINT_008d0f60 = GetProcAddress(a1,IMG_ADDR(0x004d94e8));
      goto LAB_004b7bd0;
    }
  }
  return 0;
}

/* ---- 0x004b7cb0  mktime ---- */
undefined * __cdecl mktime(uint param_1)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)_make_time_t(param_1,1);
  return puVar1;
}

/* ---- 0x004b7cc0  _make_time_t ---- */
int _make_time_t(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  
  piVar7 = param_1;
  uVar4 = param_1[5];
  if ((int)uVar4 < 0x45) {
    return -1;
  }
  if (0x8b < (int)uVar4) {
    return -1;
  }
  iVar5 = param_1[4];
  if ((iVar5 < 0) || (0xb < iVar5)) {
    uVar4 = uVar4 + iVar5 / 0xc;
    iVar5 = iVar5 % 0xc;
    param_1[4] = iVar5;
    if (iVar5 < 0) {
      uVar4 = uVar4 - 1;
      param_1[4] = iVar5 + 0xc;
    }
    if ((int)uVar4 < 0x45) {
      return -1;
    }
    if (0x8b < (int)uVar4) {
      return -1;
    }
  }
  uVar2 = (&UINT_004f0680)[param_1[4]];
  if (((uVar4 & 3) == 0) && (1 < param_1[4])) {
    uVar2 = uVar2 + 1;
  }
  iVar1 = param_1[3];
  iVar6 = uVar4 * 0x16d + -0x63df + uVar2 + ((int)(uVar4 - 1) >> 2);
  iVar5 = iVar6 + iVar1;
  if (iVar6 < 0) {
LAB_004b7d70:
    if ((iVar1 < 0) && (-1 < iVar5)) {
      return -1;
    }
  }
  else {
    if ((-1 < iVar1) && (iVar5 < 0)) {
      return -1;
    }
    if (iVar6 < 0) goto LAB_004b7d70;
  }
  iVar6 = iVar5 * 0x18;
  if (iVar5 != 0 && iVar6 / iVar5 != 0x18) {
    return -1;
  }
  iVar1 = param_1[2];
  iVar5 = iVar1 + iVar6;
  if (iVar6 < 0) {
LAB_004b7dbb:
    if ((iVar1 < 0) && (-1 < iVar5)) {
      return -1;
    }
  }
  else {
    if ((-1 < iVar1) && (iVar5 < 0)) {
      return -1;
    }
    if (iVar6 < 0) goto LAB_004b7dbb;
  }
  iVar6 = iVar5 * 0x3c;
  if (iVar5 != 0 && iVar6 / iVar5 != 0x3c) {
    return -1;
  }
  iVar1 = param_1[1];
  iVar5 = iVar1 + iVar6;
  if (iVar6 < 0) {
LAB_004b7e0a:
    if ((iVar1 < 0) && (-1 < iVar5)) {
      return -1;
    }
  }
  else {
    if ((-1 < iVar1) && (iVar5 < 0)) {
      return -1;
    }
    if (iVar6 < 0) goto LAB_004b7e0a;
  }
  iVar6 = iVar5 * 0x3c;
  if (iVar5 != 0 && iVar6 / iVar5 != 0x3c) {
    return -1;
  }
  iVar5 = *param_1;
  param_1 = (int *)(iVar5 + iVar6);
  if (-1 < iVar6) {
    if ((-1 < iVar5) && ((int)param_1 < 0)) {
      return -1;
    }
    if (-1 < iVar6) goto LAB_004b7e68;
  }
  if ((iVar5 < 0) && (-1 < (int)param_1)) {
    return -1;
  }
LAB_004b7e68:
  if (param_2 == 0) {
    piVar3 = (int *)gmtime(&param_1);
    if (piVar3 == (int *)0x0) {
      return -1;
    }
  }
  else {
    __tzset();
    param_1 = (int *)((int)param_1 + UINT_004f0400);
    piVar3 = (int *)localtime(&param_1);
    if (piVar3 == (int *)0x0) {
      return -1;
    }
    if ((0 < piVar7[8]) || ((piVar7[8] < 0 && (0 < piVar3[8])))) {
      param_1 = (int *)((int)param_1 + UINT_004f0408);
      piVar3 = (int *)localtime(&param_1);
      for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1) {
        *piVar7 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar7 = piVar7 + 1;
      }
      return (int)param_1;
    }
  }
  for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar7 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar7 = piVar7 + 1;
  }
  return (int)param_1;
}

/* ---- 0x004b7f00  __tzset ---- */
void __tzset(void)

{
  if (UINT_008d1020 == 0) {
    _lock(0xb);
    if (UINT_008d1020 == 0) {
      _tzset_lk();
      UINT_008d1020 = UINT_008d1020 + 1;
    }
    _unlock(0xb);
  }
  return;
}

/* ---- 0x004b7f40  _tzset_lk ---- */
void _tzset_lk(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  byte *pbVar8;
  bool bVar9;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  _lock(0xc);
  UINT_008d0f68 = 0;
  UINT_004f04a8 = 0xffffffff;
  UINT_004f0498 = 0xffffffff;
  pbVar3 = (byte *)getenv(&DAT_004d9568);
  if (pbVar3 == (byte *)0x0) {
    _unlock(0xc);
    iVar4 = GetTimeZoneInformation(IMG_ADDR(0x008d0f70));
    if (iVar4 == -1) {
      return;
    }
    UINT_008d0f68 = 1;
    UINT_004f0400 = UINT_008d0f70 * 0x3c;
    if (DAT_008d0fb6 != 0) {
      UINT_004f0400 = UINT_004f0400 + UINT_008d0fc4 * 0x3c;
    }
    if ((DAT_008d100a == 0) || (UINT_008d1018 == 0)) {
      UINT_004f0404 = 0;
      UINT_004f0408 = 0;
    }
    else {
      UINT_004f0404 = 1;
      UINT_004f0408 = (UINT_008d1018 - UINT_008d0fc4) * 0x3c;
    }
    wcstombs(PTR_DAT_004f0490,&DAT_008d0f74,0x40);
    wcstombs(PTR_DAT_004f0494,&DAT_008d0fc8,0x40);
    PTR_DAT_004f0494[0x3f] = 0;
    PTR_DAT_004f0490[0x3f] = 0;
    return;
  }
  if (*pbVar3 != 0) {
    pbVar7 = pbVar3;
    pbVar8 = (byte *)UINT_008d101c;
    if (UINT_008d101c != 0) {
      do {
        bVar1 = *pbVar7;
        bVar9 = bVar1 < *pbVar8;
        if (bVar1 != *pbVar8) {
LAB_004b8097:
          iVar4 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
          goto LAB_004b809c;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar7[1];
        bVar9 = bVar1 < pbVar8[1];
        if (bVar1 != pbVar8[1]) goto LAB_004b8097;
        pbVar7 = pbVar7 + 2;
        pbVar8 = pbVar8 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_004b809c:
      if (iVar4 == 0) goto LAB_004b8209;
    }
    free(UINT_008d101c);
    uVar5 = 0xffffffff;
    pbVar7 = pbVar3;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      bVar1 = *pbVar7;
      pbVar7 = pbVar7 + 1;
    } while (bVar1 != 0);
    UINT_008d101c = (uint)malloc(~uVar5);
    if ((byte *)UINT_008d101c != (byte *)0x0) {
      uVar5 = 0xffffffff;
      pbVar7 = pbVar3;
      do {
        pbVar8 = pbVar7;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pbVar8 = pbVar7 + 1;
        bVar1 = *pbVar7;
        pbVar7 = pbVar8;
      } while (bVar1 != 0);
      uVar5 = ~uVar5;
      pbVar7 = pbVar8 + -uVar5;
      pbVar8 = (byte *)UINT_008d101c;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pbVar8 = *(undefined4 *)pbVar7;
        pbVar7 = pbVar7 + 4;
        pbVar8 = pbVar8 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pbVar8 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        pbVar8 = pbVar8 + 1;
      }
      _unlock(0xc);
      strncpy(PTR_DAT_004f0490,pbVar3,3);
      pbVar7 = pbVar3 + 3;
      PTR_DAT_004f0490[3] = 0;
      bVar1 = *pbVar7;
      if (bVar1 == 0x2d) {
        pbVar7 = pbVar3 + 4;
      }
      iVar4 = atol(pbVar7);
      UINT_004f0400 = iVar4 * 0xe10;
      for (; (bVar2 = *pbVar7, bVar2 == 0x2b || (('/' < (char)bVar2 && ((char)bVar2 < ':'))));
          pbVar7 = pbVar7 + 1) {
      }
      if (*pbVar7 == 0x3a) {
        pbVar7 = pbVar7 + 1;
        iVar4 = atol(pbVar7);
        UINT_004f0400 = UINT_004f0400 + iVar4 * 0x3c;
        bVar2 = *pbVar7;
        while (('/' < (char)bVar2 && ((char)bVar2 < ':'))) {
          pbVar3 = pbVar7 + 1;
          pbVar7 = pbVar7 + 1;
          bVar2 = *pbVar3;
        }
        if (*pbVar7 == 0x3a) {
          pbVar7 = pbVar7 + 1;
          iVar4 = atol(pbVar7);
          UINT_004f0400 = UINT_004f0400 + iVar4;
          bVar2 = *pbVar7;
          while (('/' < (char)bVar2 && ((char)bVar2 < ':'))) {
            pbVar3 = pbVar7 + 1;
            pbVar7 = pbVar7 + 1;
            bVar2 = *pbVar3;
          }
        }
      }
      if (bVar1 == 0x2d) {
        UINT_004f0400 = -UINT_004f0400;
      }
      UINT_004f0404 = (uint)(char)*pbVar7;
      if (UINT_004f0404 == 0) {
        *PTR_DAT_004f0494 = 0;
        return;
      }
      strncpy(PTR_DAT_004f0494,pbVar7,3);
      PTR_DAT_004f0494[3] = 0;
      return;
    }
  }
LAB_004b8209:
  _unlock(0xc);
  return;
}
#undef local_4


/* ---- 0x004b8220  _isindst ---- */
undefined4 _isindst(undefined4 param_1)

{
  undefined4 uVar1;
  
  _lock(0xb);
  uVar1 = _isindst_lk(param_1);
  _unlock(0xb);
  return uVar1;
}

/* ---- 0x004b8250  _isindst_lk ---- */
bool _isindst_lk(int *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  
  if (UINT_004f0404 == 0) {
    return false;
  }
  uVar1 = param_1[5];
  if ((uVar1 == UINT_004f0498) && (uVar1 == UINT_004f04a8)) goto LAB_004b8424;
  if (UINT_008d0f68 == 0) {
    _cvtdate(1,1,uVar1,4,1,0,0,2,0,0,0);
    iVar2 = param_1[5];
    uVar7 = 0;
    uVar1 = 0;
    uVar9 = 0;
    uVar4 = 2;
    uVar3 = 0;
    uVar8 = 5;
    uVar6 = 10;
LAB_004b8418:
    uVar5 = 1;
    uVar10 = 0;
  }
  else {
    if (DAT_008d1008 != 0) {
      uVar3 = 0;
      uVar7 = 0;
      uVar9 = PIECE(UINT_008d100c,2,2);
    }
    else {
      uVar3 = UINT_008d100c & 0xffff;
      uVar7 = PIECE(UINT_008d100c,2,2);
      uVar9 = 0;
    }
    _cvtdate(1,DAT_008d1008 == 0,uVar1,DAT_008d100a,uVar7,uVar3,uVar9,UINT_008d1010 & 0xffff,
             UINT_008d1010 >> 0x10,UINT_008d1014 & 0xffff,UINT_008d1014 >> 0x10);
    uVar7 = PIECE(UINT_008d0fc0,2,2);
    uVar9 = PIECE(UINT_008d0fbc,2,2);
    uVar6 = DAT_008d0fb6;
    if (DAT_008d0fb4 == 0) {
      uVar1 = UINT_008d0fc0 & 0xffff;
      uVar4 = UINT_008d0fbc & 0xffff;
      uVar3 = UINT_008d0fb8 & 0xffff;
      iVar2 = param_1[5];
      uVar8 = PIECE(UINT_008d0fb8,2,2);
      goto LAB_004b8418;
    }
    uVar1 = UINT_008d0fc0 & 0xffff;
    uVar4 = UINT_008d0fbc & 0xffff;
    iVar2 = param_1[5];
    uVar3 = 0;
    uVar8 = 0;
    uVar5 = 0;
    uVar10 = PIECE(UINT_008d0fb8,2,2);
  }
  _cvtdate(0,uVar5,iVar2,uVar6,uVar8,uVar3,uVar10,uVar4,uVar9,uVar1,uVar7);
LAB_004b8424:
  uVar1 = param_1[7];
  if ((int)UINT_004f049c < (int)UINT_004f04ac) {
    if (((int)uVar1 < (int)UINT_004f049c) || ((int)UINT_004f04ac < (int)uVar1)) {
      return false;
    }
    if (((int)UINT_004f049c < (int)uVar1) && ((int)uVar1 < (int)UINT_004f04ac)) {
      return true;
    }
  }
  else {
    if (((int)uVar1 < (int)UINT_004f04ac) || ((int)UINT_004f049c < (int)uVar1)) {
      return true;
    }
    if (((int)UINT_004f04ac < (int)uVar1) && ((int)uVar1 < (int)UINT_004f049c)) {
      return false;
    }
  }
  iVar2 = (*param_1 + (param_1[1] + param_1[2] * 0x3c) * 0x3c) * 1000;
  if (uVar1 != UINT_004f049c) {
    return iVar2 < (int)UINT_004f04b0;
  }
  return (int)UINT_004f04a0 <= iVar2;
}

/* ---- 0x004b84c0  _cvtdate ---- */
void _cvtdate(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7,
             int param_8,int param_9,int param_10,int param_11)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  if (param_2 == 1) {
    if ((param_3 & 3) == 0) {
      uVar1 = (&UINT_004f0644)[param_4];
    }
    else {
      uVar1 = *(uint *)(&DAT_004f067c + param_4 * 4);
    }
    iVar2 = (int)(((int)(param_3 - 1) >> 2) + -0x63db + param_3 * 0x16d + uVar1 + 1) % 7;
    if (iVar2 < param_6) {
      uVar1 = (uVar1 - 6) + (param_5 * 7 - iVar2) + param_6;
    }
    else {
      uVar1 = uVar1 + 1 + (param_5 * 7 - iVar2) + param_6;
    }
    if (param_5 == 5) {
      if ((param_3 & 3) == 0) {
        uVar3 = *(uint *)(&DAT_004f0648 + param_4 * 4);
      }
      else {
        uVar3 = (&UINT_004f0680)[param_4];
      }
      if ((int)uVar3 < (int)uVar1) {
        uVar1 = uVar1 - 7;
      }
    }
  }
  else {
    if ((param_3 & 3) == 0) {
      uVar1 = (&UINT_004f0644)[param_4];
    }
    else {
      uVar1 = *(uint *)(&DAT_004f067c + param_4 * 4);
    }
    uVar1 = uVar1 + param_7;
  }
  if (param_1 == 1) {
    UINT_004f049c = uVar1;
    UINT_004f0498 = param_3;
    UINT_004f04a0 = param_11 + (param_10 + (param_9 + param_8 * 0x3c) * 0x3c) * 1000;
    return;
  }
  UINT_004f04ac = uVar1;
  UINT_004f04b0 = param_11 + (param_10 + (param_9 + param_8 * 0x3c) * 0x3c + UINT_004f0408) * 1000;
  if ((int)UINT_004f04b0 < 0) {
    UINT_004f04a8 = param_3;
    UINT_004f04b0 = UINT_004f04b0 + 86399999;
    return;
  }
  if (86399999 < (int)UINT_004f04b0) {
    UINT_004f04b0 = UINT_004f04b0 + 0xfad9a401;
  }
  UINT_004f04a8 = param_3;
  return;
}

/* ---- 0x004b8660  _sopen ---- */
uint _sopen(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  #define local_11 (*(byte *)(_frame + (0x30 - 0x11)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  bVar7 = (param_2 & 0x80) == 0;
  local_c = 0xc;
  local_8 = 0;
  if (bVar7) {
    local_11 = 0;
  }
  else {
    local_11 = 0x10;
  }
  local_4 = (uint)bVar7;
  if (((param_2 & 0x8000) == 0) && (((param_2 & 0x4000) != 0 || (UINT_008d107c != 0x8000)))) {
    local_11 = local_11 | 0x80;
  }
  uVar1 = param_2 & 3;
  if (uVar1 == 0) {
    local_10 = 0x80000000;
  }
  else if (uVar1 == 1) {
    local_10 = 0x40000000;
  }
  else {
    if (uVar1 != 2) goto switchD_004b86f8_caseD_11;
    local_10 = 0xc0000000;
  }
  switch(param_3) {
  case 0x10:
    iVar5 = 0;
    break;
  default:
    goto switchD_004b86f8_caseD_11;
  case 0x20:
    iVar5 = 1;
    break;
  case 0x30:
    iVar5 = 2;
    break;
  case 0x40:
    iVar5 = 3;
  }
  uVar1 = param_2 & 0x700;
  if (uVar1 < 0x101) {
    if (uVar1 == 0x100) {
      iVar6 = 4;
    }
    else {
      if (uVar1 != 0) goto switchD_004b86f8_caseD_11;
LAB_004b8766:
      iVar6 = 3;
    }
  }
  else if (uVar1 < 0x301) {
    if (uVar1 == 0x300) {
      iVar6 = 2;
    }
    else {
      if (uVar1 != 0x200) goto switchD_004b86f8_caseD_11;
LAB_004b8786:
      iVar6 = 5;
    }
  }
  else {
    if (uVar1 < 0x501) {
      if (uVar1 != 0x500) {
        if (uVar1 != 0x400) {
switchD_004b86f8_caseD_11:
          puVar4 = (undefined4 *)_errno();
          *puVar4 = 0x16;
          puVar4 = (undefined4 *)__doserrno();
          *puVar4 = 0;
          return 0xffffffff;
        }
        goto LAB_004b8766;
      }
    }
    else {
      if (uVar1 == 0x600) goto LAB_004b8786;
      if (uVar1 != 0x700) goto switchD_004b86f8_caseD_11;
    }
    iVar6 = 1;
  }
  uVar1 = 0x80;
  if (((param_2 & 0x100) != 0) && (((byte)param_4 & ~(byte)UINT_008d0ab0 & 0x80) == 0)) {
    uVar1 = 1;
  }
  if ((param_2 & 0x40) != 0) {
    uVar1 = uVar1 | 0x4000000;
    local_10 = local_10 | 0x10000;
  }
  if ((param_2 & 0x1000) != 0) {
    uVar1 = uVar1 | 0x100;
  }
  if ((param_2 & 0x20) == 0) {
    if ((param_2 & 0x10) != 0) {
      uVar1 = uVar1 | 0x10000000;
    }
  }
  else {
    uVar1 = uVar1 | 0x8000000;
  }
  uVar2 = _alloc_osfhnd();
  if (uVar2 == 0xffffffff) {
    puVar4 = (undefined4 *)_errno();
    *puVar4 = 0x18;
    puVar4 = (undefined4 *)__doserrno();
    *puVar4 = 0;
    return 0xffffffff;
  }
  iVar5 = CreateFileA(param_1,local_10,iVar5,(int)&local_c,iVar6,uVar1,0);
  if (iVar5 != -1) {
    iVar6 = GetFileType(iVar5);
    if (iVar6 != 0) {
      if (iVar6 == 2) {
        local_11 = local_11 | 0x40;
      }
      else if (iVar6 == 3) {
        local_11 = local_11 | 8;
      }
      _set_osfhnd(uVar2,iVar5);
      uVar1 = uVar2 & 0x1f;
      *(byte *)((&PTR_00906b00)[(int)uVar2 >> 5] + uVar1 * 9 + 1) = local_11 | 1;
      if ((((local_11 & 0x48) == 0) && ((local_11 & 0x80) != 0)) && ((param_2 & 2) != 0)) {
        iVar5 = _lseek_lk(uVar2,0xffffffff,2);
        if (iVar5 == -1) {
          piVar3 = (int *)__doserrno();
          if (*piVar3 != 0x83) {
LAB_004b8946:
            _close(uVar2);
            _unlock_fhandle(uVar2);
            return 0xffffffff;
          }
        }
        else {
          param_3 = param_3 & 0xffffff00;
          iVar6 = _read_lk(uVar2,&param_3,1);
          if ((((iVar6 == 0) && ((char)param_3 == '\x1a')) &&
              (iVar5 = ((code *)_chsize)(uVar2,iVar5), iVar5 == -1)) ||
             (iVar5 = _lseek_lk(uVar2,0,0), iVar5 == -1)) goto LAB_004b8946;
        }
      }
      if (((local_11 & 0x48) == 0) && ((param_2 & 8) != 0)) {
        *(byte *)((&PTR_00906b00)[(int)uVar2 >> 5] + uVar1 * 9 + 1) =
             *(byte *)((&PTR_00906b00)[(int)uVar2 >> 5] + uVar1 * 9 + 1) | 0x20;
      }
      _unlock_fhandle(uVar2);
      return uVar2;
    }
    CloseHandle(iVar5);
  }
  iVar5 = GetLastError();
  _dosmaperr(iVar5);
  _unlock_fhandle(uVar2);
  return 0xffffffff;
}
#undef local_10
#undef local_11
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004b8a00  _alloc_osfhnd ---- */
uint _alloc_osfhnd(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int **ppiVar3;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_8 = 0xffffffff;
  _lock(0x12);
  local_4 = 0;
  iVar2 = 0;
  ppiVar3 = &PTR_00906b00;
  do {
    piVar1 = *ppiVar3;
    if (piVar1 == (int *)0x0) {
      piVar1 = (int *)malloc(0x480);
      if (piVar1 != (int *)0x0) {
        UINT_00906c00 = UINT_00906c00 + 0x20;
        (&PTR_00906b00)[local_4] = piVar1;
        if (piVar1 < piVar1 + 0x120) {
          do {
            *(undefined1 *)(piVar1 + 1) = 0;
            *piVar1 = -1;
            *(undefined1 *)((int)piVar1 + 5) = 10;
            piVar1[2] = 0;
            piVar1 = piVar1 + 9;
          } while (piVar1 < (&PTR_00906b00)[local_4] + 0x120);
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
            _lock(0x11);
            if (piVar1[2] == 0) {
              InitializeCriticalSection((int)(piVar1 + 3));
              piVar1[2] = piVar1[2] + 1;
            }
            _unlock(0x11);
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
  } while ((int)ppiVar3 < IMG_ADDR(0x00906c00));
  _unlock(0x12);
  return local_8;
}
#undef local_4
#undef local_8


/* ---- 0x004b8b70  _set_osfhnd ---- */
undefined4 _set_osfhnd(uint param_1,int param_2)

{
  undefined4 *puVar1;
  
  if (param_1 < UINT_00906c00) {
    if ((&PTR_00906b00)[(int)param_1 >> 5][(param_1 & 0x1f) * 9] == -1) {
      if (UINT_004ed0b4 == 1) {
        if (param_1 == 0) {
          SetStdHandle(-10,param_2);
        }
        else {
          if (param_1 == 1) {
            SetStdHandle(-0xb,param_2);
            PTR_00906b00[9] = param_2;
            return 0;
          }
          if (param_1 == 2) {
            SetStdHandle(-0xc,param_2);
            PTR_00906b00[0x12] = param_2;
            return 0;
          }
        }
      }
      (&PTR_00906b00)[(int)param_1 >> 5][(param_1 & 0x1f) * 9] = param_2;
      return 0;
    }
  }
  puVar1 = (undefined4 *)_errno();
  *puVar1 = 9;
  puVar1 = (undefined4 *)__doserrno();
  *puVar1 = 0;
  return 0xffffffff;
}

/* ---- 0x004b8c20  _free_osfhnd ---- */
undefined4 _free_osfhnd(uint param_1)

{
  int *piVar1;
  uint uVar2;
  undefined4 *puVar3;
  int a1;
  
  if (param_1 < UINT_00906c00) {
    uVar2 = param_1 & 0x1f;
    piVar1 = (&PTR_00906b00)[(int)param_1 >> 5];
    if (((*(byte *)(piVar1 + uVar2 * 9 + 1) & 1) != 0) && (piVar1[uVar2 * 9] != -1)) {
      if (UINT_004ed0b4 == 1) {
        if (param_1 == 0) {
          a1 = -10;
        }
        else if (param_1 == 1) {
          a1 = -0xb;
        }
        else {
          if (param_1 != 2) goto LAB_004b8c87;
          a1 = -0xc;
        }
        SetStdHandle(a1,0);
      }
LAB_004b8c87:
      (&PTR_00906b00)[(int)param_1 >> 5][uVar2 * 9] = -1;
      return 0;
    }
  }
  puVar3 = (undefined4 *)_errno();
  *puVar3 = 9;
  puVar3 = (undefined4 *)__doserrno();
  *puVar3 = 0;
  return 0xffffffff;
}

/* ---- 0x004b8cc0  _get_osfhandle ---- */
int _get_osfhandle(uint param_1)

{
  undefined4 *puVar1;
  
  if ((param_1 < UINT_00906c00) &&
     ((*(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    return (&PTR_00906b00)[(int)param_1 >> 5][(param_1 & 0x1f) * 9];
  }
  puVar1 = (undefined4 *)_errno();
  *puVar1 = 9;
  puVar1 = (undefined4 *)__doserrno();
  *puVar1 = 0;
  return -1;
}

/* ---- 0x004b8d10  _lock_fhandle ---- */
void _lock_fhandle(uint param_1)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = param_1 & 0x1f;
  piVar1 = (&PTR_00906b00)[(int)param_1 >> 5];
  if (piVar1[uVar2 * 9 + 2] == 0) {
    _lock(0x11);
    if (piVar1[uVar2 * 9 + 2] == 0) {
      InitializeCriticalSection((int)(piVar1 + uVar2 * 9 + 3));
      piVar1[uVar2 * 9 + 2] = piVar1[uVar2 * 9 + 2] + 1;
    }
    _unlock(0x11);
  }
  EnterCriticalSection((int)((&PTR_00906b00)[(int)param_1 >> 5] + uVar2 * 9 + 3));
  return;
}

/* ---- 0x004b8d80  _unlock_fhandle ---- */
void _unlock_fhandle(uint param_1)

{
  LeaveCriticalSection((int)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 3));
  return;
}

/* ---- 0x004b8db0  mbtowc ---- */
undefined4 mbtowc(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  bool bVar2;
  
  InterlockedIncrement(IMG_ADDR(0x00906c0c));
  bVar2 = UINT_00906c08 != 0;
  if (bVar2) {
    InterlockedDecrement(IMG_ADDR(0x00906c0c));
    _lock(0x13);
  }
  uVar1 = _mbtowc_lk(param_1,param_2,param_3);
  if (!bVar2) {
    InterlockedDecrement(IMG_ADDR(0x00906c0c));
    return uVar1;
  }
  _unlock(0x13);
  return uVar1;
}

/* ---- 0x004b8e30  _mbtowc_lk ---- */
uint _mbtowc_lk(ushort *param_1,byte *param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if ((param_2 != (byte *)0x0) && (param_3 != 0)) {
    bVar1 = *param_2;
    if (bVar1 != 0) {
      if (UINT_008d0b70 == 0) {
        if (param_1 == (ushort *)0x0) {
          return 1;
        }
        *param_1 = (ushort)bVar1;
        return 1;
      }
      if ((PTR_DAT_004ed320[(uint)bVar1 * 2 + 1] & 0x80) == 0) {
        iVar2 = MultiByteToWideChar(UINT_008d0b80,9,(int)param_2,1,(int)param_1,
                                    (uint)(param_1 != (ushort *)0x0));
        if (iVar2 != 0) {
          return 1;
        }
      }
      else {
        if (((1 < (int)UINT_004ed52c) && ((int)UINT_004ed52c <= (int)param_3)) &&
           (iVar2 = MultiByteToWideChar(UINT_008d0b80,9,(int)param_2,UINT_004ed52c,(int)param_1,
                                        (uint)(param_1 != (ushort *)0x0)), iVar2 != 0)) {
          return UINT_004ed52c;
        }
        if (UINT_004ed52c <= param_3) {
          if (param_2[1] != 0) {
            return UINT_004ed52c;
          }
          puVar3 = (undefined4 *)_errno();
          *puVar3 = 0x2a;
          return 0xffffffff;
        }
      }
      puVar3 = (undefined4 *)_errno();
      *puVar3 = 0x2a;
      return 0xffffffff;
    }
    if (param_1 != (ushort *)0x0) {
      *param_1 = 0;
      return 0;
    }
  }
  return 0;
}

/* ---- 0x004b8f50  ungetc ---- */
undefined4 ungetc(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  _lock_file(param_2);
  uVar1 = _ungetc_lk(param_1,param_2);
  _unlock_file(param_2);
  return uVar1;
}

/* ---- 0x004b8f80  _ungetc_lk ---- */
uint _ungetc_lk(uint param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  
  if ((param_1 != 0xffffffff) &&
     ((uVar1 = param_2[3], (uVar1 & 1) != 0 || (((uVar1 & 0x80) != 0 && ((uVar1 & 2) == 0)))))) {
    if (param_2[2] == 0) {
      _getbuf(param_2);
    }
    if (*param_2 == param_2[2]) {
      if (param_2[1] != 0) {
        return 0xffffffff;
      }
      *param_2 = *param_2 + 1;
    }
    if ((*(byte *)(param_2 + 3) & 0x40) == 0) {
      iVar2 = *param_2;
      *param_2 = iVar2 + -1;
      *(char *)(iVar2 + -1) = (char)param_1;
    }
    else {
      iVar2 = *param_2;
      pcVar3 = (char *)(iVar2 + -1);
      *param_2 = (int)pcVar3;
      if (*pcVar3 != (char)param_1) {
        *param_2 = iVar2;
        return 0xffffffff;
      }
    }
    param_2[1] = param_2[1] + 1;
    param_2[3] = param_2[3] & 0xffffffefU | 1;
    return param_1 & 0xff;
  }
  return 0xffffffff;
}

/* ---- 0x004b9010  _filwbuf ---- */
undefined2 _filwbuf(undefined4 *param_1)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  
  uVar2 = param_1[3];
  if (((uVar2 & 0x83) != 0) && ((uVar2 & 0x40) == 0)) {
    if ((uVar2 & 2) != 0) {
      param_1[3] = uVar2 | 0x20;
      return 0xffff;
    }
    param_1[3] = uVar2 | 1;
    if ((uVar2 & 0x10c) == 0) {
      _getbuf(param_1);
    }
    else {
      *param_1 = param_1[2];
    }
    iVar3 = _read(param_1[4],param_1[2],param_1[6]);
    param_1[1] = iVar3;
    if (((iVar3 != 0) && (iVar3 != 1)) && (iVar3 != -1)) {
      if ((param_1[3] & 0x82) == 0) {
        uVar2 = param_1[4];
        if (uVar2 == 0xffffffff) {
          piVar4 = (int *)&DAT_004ed6c8;
        }
        else {
          piVar4 = (&PTR_00906b00)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 9;
        }
        if ((*(byte *)(piVar4 + 1) & 0x82) == 0x82) {
          param_1[3] = param_1[3] | 0x2000;
        }
      }
      if (((param_1[6] == 0x200) && ((param_1[3] & 8) != 0)) && ((param_1[3] & 0x400) == 0)) {
        param_1[6] = 0x1000;
      }
      param_1[1] = iVar3 + -2;
      uVar1 = *(undefined2 *)*param_1;
      *param_1 = (undefined2 *)*param_1 + 1;
      return uVar1;
    }
    param_1[1] = 0;
    param_1[3] = param_1[3] | (-(uint)(iVar3 != 0) & 0x10) + 0x10;
  }
  return 0xffff;
}

/* ---- 0x004b9ea0  _except1 ---- */
void _except1(int param_1,int *param_2,ushort *param_3)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  #define local_58 (*(undefined1 (*)[40])(_frame + (0x70 - 0x58)))
  #define local_30 (*(uint *)(_frame + (0x70 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x70 - 0x2c)))
  #define local_20 (*(uint *)(_frame + (0x70 - 0x20)))
  
  param_3 = (ushort *)(uint)*param_3;
  switch(*param_2) {
  case 1:
  case 5:
    uVar2 = 8;
    break;
  case 2:
    uVar2 = 4;
    break;
  case 3:
    uVar2 = 0x11;
    break;
  case 4:
    uVar2 = 0x12;
    break;
  default:
    goto switchD_004b9ebf_caseD_6;
  case 7:
    *param_2 = 1;
    goto switchD_004b9ebf_caseD_6;
  case 8:
    uVar2 = 0x10;
  }
  iVar1 = _handle_exc(uVar2,param_2 + 6,param_3);
  if (iVar1 == 0) {
    if (((param_1 == 0x10) || (param_1 == 0x16)) || (param_1 == 0x1d)) {
      local_30 = param_2[4];
      local_20 = local_20 & 0xffffffe3 | 3;
      local_2c = param_2[5];
    }
    else {
      local_20 = local_20 & 0xfffffffe;
    }
    _raise_exc(local_58,&param_3,uVar2,param_1,param_2 + 2,param_2 + 6);
  }
switchD_004b9ebf_caseD_6:
  ((code *)FUN_004bc430)(param_3,0xffff);
  iVar1 = 0;
  if ((*param_2 != 8) && (UINT_004f0888 == 0)) {
    iVar1 = ((code *)zlibVersion)(param_2);
  }
  if (iVar1 == 0) {
    FUN_004bc3d0(*param_2);
  }
  return;
}
#undef local_20
#undef local_2c
#undef local_30
#undef local_58


/* ---- 0x004ba2c0  _ValidateRead ---- */
bool _ValidateRead(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = IsBadReadPtr(param_1,param_2);
  return iVar1 == 0;
}

/* ---- 0x004ba2e0  _ValidateWrite ---- */
bool _ValidateWrite(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = IsBadWritePtr(param_1,param_2);
  return iVar1 == 0;
}

/* ---- 0x004ba300  _ValidateExecute ---- */
bool _ValidateExecute(int param_1)

{
  int iVar1;
  
  iVar1 = IsBadCodePtr(param_1);
  return iVar1 == 0;
}

/* ---- 0x004ba320  abort ---- */
void abort(void)

{
  _NMSG_WRITE(10);
  raise(0x16);
  _exit(3);
  return;
}

/* ---- 0x004ba600  raise ---- */
undefined4 raise(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  code *pcVar6;
  uint *puVar7;
  bool bVar8;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = param_1;
  bVar1 = false;
  iVar3 = param_1;
  switch(param_1) {
  case 2:
    puVar7 = &UINT_008d1044;
    bVar1 = true;
    pcVar6 = (code *)UINT_008d1044;
    break;
  default:
    return 0xffffffff;
  case 4:
  case 8:
  case 0xb:
    iVar3 = _getptd();
    iVar5 = siglookup(param_1,*(undefined4 *)(iVar3 + 0x50));
    puVar7 = (uint *)(iVar5 + 8);
    pcVar6 = (code *)*puVar7;
    break;
  case 0xf:
    puVar7 = &UINT_008d1050;
    bVar1 = true;
    pcVar6 = (code *)UINT_008d1050;
    break;
  case 0x15:
    puVar7 = &UINT_008d1048;
    bVar1 = true;
    pcVar6 = (code *)UINT_008d1048;
    break;
  case 0x16:
    puVar7 = &UINT_008d104c;
    bVar1 = true;
    pcVar6 = (code *)UINT_008d104c;
  }
  if (bVar1) {
    _lock(1);
  }
  if (pcVar6 == (code *)0x1) {
    if (!bVar1) {
      return 0;
    }
    _unlock(1);
    return 0;
  }
  if (pcVar6 == (code *)0x0) {
    if (bVar1) {
      _unlock(1);
    }
    _exit(3);
  }
  if (((param_1 == 8) || (param_1 == 0xb)) || (param_1 == 4)) {
    iVar5 = *(int *)(iVar3 + 0x54);
    bVar8 = param_1 == 8;
    *(undefined4 *)(iVar3 + 0x54) = 0;
    param_1 = iVar5;
    if (bVar8) {
      local_4 = *(uint *)(iVar3 + 0x58);
      *(undefined4 *)(iVar3 + 0x58) = 0x8c;
      goto LAB_004ba733;
    }
  }
  else {
LAB_004ba733:
    if (iVar2 == 8) {
      if ((int)UINT_004ed5c0 < (int)(UINT_004ed5c4 + UINT_004ed5c0)) {
        iVar5 = UINT_004ed5c0 * 0xc;
        uVar4 = UINT_004ed5c0;
        do {
          uVar4 = uVar4 + 1;
          *(undefined4 *)(*(int *)(iVar3 + 0x50) + 8 + iVar5) = 0;
          iVar5 = iVar5 + 0xc;
        } while ((int)uVar4 < (int)(UINT_004ed5c4 + UINT_004ed5c0));
      }
      goto LAB_004ba778;
    }
  }
  *puVar7 = 0;
LAB_004ba778:
  if (bVar1) {
    _unlock(1);
  }
  if (iVar2 == 8) {
    (*pcVar6)(8,*(undefined4 *)(iVar3 + 0x58));
  }
  else {
    (*pcVar6)(iVar2);
    if ((iVar2 != 0xb) && (iVar2 != 4)) {
      return 0;
    }
  }
  *(int *)(iVar3 + 0x54) = param_1;
  if (iVar2 == 8) {
    *(uint *)(iVar3 + 0x58) = local_4;
  }
  return 0;
}
#undef local_4
#undef local_8


/* ---- 0x004ba810  siglookup ---- */
uint siglookup(int param_1,uint param_2)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = param_2;
  if (*(int *)(param_2 + 4) != param_1) {
    uVar3 = param_2;
    do {
      uVar2 = uVar3 + 0xc;
      if (param_2 + UINT_004ed5cc * 0xc <= uVar2) break;
      piVar1 = (int *)(uVar3 + 0x10);
      uVar3 = uVar2;
    } while (*piVar1 != param_1);
  }
  if ((param_2 + UINT_004ed5cc * 0xc <= uVar2) || (*(int *)(uVar2 + 4) != param_1)) {
    uVar2 = 0;
  }
  return uVar2;
}

/* ---- 0x004ba850  __addl ---- */
undefined4 __addl(uint param_1,uint param_2,uint *param_3)

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

/* ---- 0x004ba880  __add_12 ---- */
void __add_12(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = __addl(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = __addl(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = __addl(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  __addl(param_1[2],param_2[2],param_1 + 2);
  return;
}

/* ---- 0x004ba8f0  __shl_12 ---- */
void __shl_12(uint *param_1)

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

/* ---- 0x004ba920  __shr_12 ---- */
void __shr_12(uint *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  param_1[1] = uVar1 >> 1 | param_1[2] << 0x1f;
  param_1[2] = param_1[2] >> 1;
  *param_1 = *param_1 >> 1 | uVar1 << 0x1f;
  return;
}

/* ---- 0x004ba950  __mtold12 ---- */
void __mtold12(char *param_1,int param_2,uint *param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  short sVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  puVar2 = param_3;
  sVar3 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  if (param_2 != 0) {
    param_3 = (uint *)param_2;
    do {
      local_c = *puVar2;
      local_8 = puVar2[1];
      local_4 = puVar2[2];
      __shl_12(puVar2);
      __shl_12(puVar2);
      __add_12(puVar2,&local_c);
      __shl_12(puVar2);
      local_c = (uint)*param_1;
      local_8 = 0;
      local_4 = 0;
      __add_12(puVar2,&local_c);
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
    __shl_12(puVar2);
    sVar3 = sVar3 + -1;
    uVar1 = puVar2[2];
  }
  *(short *)((int)puVar2 + 10) = sVar3;
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004baa50  __strgtold12 ---- */
uint __strgtold12(ushort *param_1,int *param_2,byte *param_3,undefined4 param_4,int param_5,
                 int param_6,int param_7)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  int iVar7;
  uint uVar8;
  byte bVar9;
  byte *pbVar10;
  byte *pbVar11;
  uint uVar12;
  byte *pbVar13;
  #define local_60 (*(uint *)(_frame + (0x70 - 0x60)))
  #define local_5c (*(uint *)(_frame + (0x70 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x70 - 0x54)))
  #define local_50 (*(uint *)(_frame + (0x70 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0x70 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x70 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x70 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x70 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x70 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x70 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x70 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x70 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x70 - 0x2c)))
  #define uStack_28 (*(undefined2 *)(_frame + (0x70 - 0x28)))
  #define local_26 (*(uint *)(_frame + (0x70 - 0x26)))
  #define local_22 (*(uint *)(_frame + (0x70 - 0x22)))
  #define local_1c (*(undefined1 (*)[23])(_frame + (0x70 - 0x1c)))
  #define local_5 (*(char *)(_frame + (0x70 - 0x5)))
  
  local_5c = (uint)local_1c;
  iVar7 = 0;
  uVar12 = 0;
  local_3c = 0;
  local_4c = 1;
  local_54 = 0;
  bVar2 = false;
  bVar4 = false;
  bVar3 = false;
  bVar5 = false;
  bVar6 = false;
  local_48 = 0;
  local_60 = 0;
  local_30 = 0;
  local_50 = (uint)param_3;
  for (pbVar10 = param_3;
      (((bVar9 = *pbVar10, bVar9 == 0x20 || (bVar9 == 9)) || (bVar9 == 10)) ||
      (pbVar13 = param_3, bVar9 == 0xd)); pbVar10 = pbVar10 + 1) {
  }
  do {
    bVar9 = *pbVar10;
    pbVar11 = pbVar10 + 1;
    param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar9);
    switch(iVar7) {
    case 0:
      if (('0' < (char)bVar9) && ((char)bVar9 < ':')) {
        iVar7 = 3;
        goto LAB_004baf22;
      }
      if (bVar9 == DAT_004ed530) {
        iVar7 = 5;
      }
      else if (bVar9 == 0x2b) {
        iVar7 = 2;
        local_3c = 0;
      }
      else if (bVar9 == 0x2d) {
        iVar7 = 2;
        local_3c = 0x8000;
      }
      else {
        if (bVar9 != 0x30) goto switchD_004bad12_caseD_2c;
        iVar7 = 1;
      }
      break;
    case 1:
      bVar2 = true;
      if (('0' < (char)bVar9) && ((char)bVar9 < ':')) {
        iVar7 = 3;
        goto LAB_004baf22;
      }
      if (bVar9 == DAT_004ed530) {
        iVar7 = 4;
      }
      else {
        switch(bVar9) {
        case 0x2b:
        case 0x2d:
          goto switchD_004bad12_caseD_2b;
        default:
          goto switchD_004bad12_caseD_2c;
        case 0x30:
switchD_004bab86_caseD_30:
          iVar7 = 1;
          break;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto switchD_004bad12_caseD_44;
        }
      }
      break;
    case 2:
      if (('0' < (char)bVar9) && ((char)bVar9 < ':')) {
        iVar7 = 3;
        goto LAB_004baf22;
      }
      if (bVar9 == DAT_004ed530) {
        iVar7 = 5;
      }
      else {
        if (bVar9 == 0x30) goto switchD_004bab86_caseD_30;
        iVar7 = 10;
        pbVar11 = pbVar13;
      }
      break;
    case 3:
      while( true ) {
        bVar2 = true;
        if ((int)UINT_004ed52c < 2) {
          uVar8 = (byte)PTR_DAT_004ed320[((uint)param_3 & 0xff) * 2] & 4;
        }
        else {
          uVar8 = _isctype((uint)param_3 & 0xff,4);
        }
        if (uVar8 == 0) break;
        if (uVar12 < 0x19) {
          uVar12 = uVar12 + 1;
          *(byte *)local_5c = bVar9 - 0x30;
          bVar9 = *pbVar11;
          local_5c = local_5c + 1;
          param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar9);
          pbVar11 = pbVar11 + 1;
        }
        else {
          bVar9 = *pbVar11;
          local_60 = local_60 + 1;
          param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar9);
          pbVar11 = pbVar11 + 1;
        }
      }
      local_54 = uVar12;
      if (bVar9 != DAT_004ed530) {
        switch(bVar9) {
        case 0x2b:
        case 0x2d:
          goto switchD_004bad12_caseD_2b;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto switchD_004bad12_caseD_44;
        }
switchD_004bad12_caseD_2c:
        iVar7 = 10;
        goto LAB_004baf22;
      }
      iVar7 = 4;
      break;
    case 4:
      bVar4 = true;
      if (uVar12 == 0) {
        while (bVar9 == 0x30) {
          bVar9 = *pbVar11;
          local_60 = local_60 - 1;
          pbVar11 = pbVar11 + 1;
          PIECE(param_3,1,3) = (undefined3)((uint)param_3 >> 8);
          param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar9);
        }
      }
      while( true ) {
        bVar2 = true;
        if ((int)UINT_004ed52c < 2) {
          uVar8 = (byte)PTR_DAT_004ed320[((uint)param_3 & 0xff) * 2] & 4;
        }
        else {
          uVar8 = _isctype((uint)param_3 & 0xff,4);
        }
        if (uVar8 == 0) break;
        if (uVar12 < 0x19) {
          uVar12 = uVar12 + 1;
          *(byte *)local_5c = bVar9 - 0x30;
          local_5c = local_5c + 1;
          local_60 = local_60 - 1;
        }
        bVar9 = *pbVar11;
        pbVar11 = pbVar11 + 1;
        param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar9);
      }
      local_54 = uVar12;
      switch(bVar9) {
      case 0x2b:
      case 0x2d:
switchD_004bad12_caseD_2b:
        bVar2 = true;
        pbVar11 = pbVar11 + -1;
        iVar7 = 0xb;
        break;
      default:
        goto switchD_004bad12_caseD_2c;
      case 0x44:
      case 0x45:
      case 100:
      case 0x65:
switchD_004bad12_caseD_44:
        bVar2 = true;
        iVar7 = 6;
      }
      break;
    case 5:
      bVar4 = true;
      if ((int)UINT_004ed52c < 2) {
        uVar8 = (byte)PTR_DAT_004ed320[(uint)bVar9 * 2] & 4;
      }
      else {
        uVar8 = _isctype(bVar9,4);
      }
      if (uVar8 == 0) {
        iVar7 = 10;
        pbVar11 = pbVar13;
      }
      else {
        iVar7 = 4;
        pbVar11 = pbVar10;
      }
      break;
    case 6:
      pbVar10 = pbVar10 + -1;
      pbVar13 = pbVar10;
      local_50 = (uint)pbVar10;
      if (('0' < (char)bVar9) && ((char)bVar9 < ':')) {
        iVar7 = 9;
        goto LAB_004baf22;
      }
      if (bVar9 == 0x2b) {
LAB_004baf16:
        iVar7 = 7;
        pbVar13 = pbVar10;
        local_50 = (uint)pbVar10;
      }
      else {
        if (bVar9 != 0x2d) goto LAB_004bae06;
LAB_004baf07:
        iVar7 = 7;
        local_4c = 0xffffffff;
        pbVar13 = pbVar10;
        local_50 = (uint)pbVar10;
      }
      break;
    case 7:
      if (('0' < (char)bVar9) && ((char)bVar9 < ':')) {
        iVar7 = 9;
        goto LAB_004baf22;
      }
LAB_004bae06:
      if (bVar9 == 0x30) {
        iVar7 = 8;
      }
      else {
        iVar7 = 10;
        pbVar11 = pbVar13;
      }
      break;
    case 8:
      bVar3 = true;
      while (bVar9 == 0x30) {
        bVar9 = *pbVar11;
        pbVar11 = pbVar11 + 1;
      }
      if (((char)bVar9 < '1') || ('9' < (char)bVar9)) goto switchD_004bad12_caseD_2c;
      iVar7 = 9;
LAB_004baf22:
      pbVar11 = pbVar11 + -1;
      break;
    case 9:
      bVar3 = true;
      local_48 = 0;
      while( true ) {
        if ((int)UINT_004ed52c < 2) {
          uVar12 = (byte)PTR_DAT_004ed320[((uint)param_3 & 0xff) * 2] & 4;
        }
        else {
          uVar12 = _isctype((uint)param_3 & 0xff,4);
        }
        if (uVar12 == 0) goto LAB_004bae8a;
        local_48 = (char)bVar9 + -0x30 + local_48 * 10;
        if (0x1450 < (int)local_48) break;
        bVar9 = *pbVar11;
        pbVar11 = pbVar11 + 1;
        param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar9);
      }
      local_48 = 0x1451;
LAB_004bae8a:
      while( true ) {
        if ((int)UINT_004ed52c < 2) {
          uVar12 = (byte)PTR_DAT_004ed320[((uint)param_3 & 0xff) * 2] & 4;
        }
        else {
          uVar12 = _isctype((uint)param_3 & 0xff,4);
        }
        if (uVar12 == 0) break;
        bVar9 = *pbVar11;
        pbVar11 = pbVar11 + 1;
        param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar9);
      }
      iVar7 = 10;
      pbVar11 = pbVar11 + -1;
      uVar12 = local_54;
      pbVar13 = (byte *)local_50;
      break;
    case 0xb:
      if (param_7 == 0) goto switchD_004bad12_caseD_2c;
      if (bVar9 == 0x2b) goto LAB_004baf16;
      if (bVar9 == 0x2d) goto LAB_004baf07;
      iVar7 = 10;
      pbVar11 = pbVar10;
      pbVar13 = pbVar10;
      local_50 = (uint)pbVar10;
    }
    pbVar10 = pbVar11;
  } while (iVar7 != 10);
  *param_2 = (int)pbVar11;
  if (bVar2) {
    if (0x18 < uVar12) {
      if ('\x04' < local_5) {
        local_5 = local_5 + '\x01';
      }
      local_5c = local_5c - 1;
      local_60 = local_60 + 1;
      uVar12 = 0x18;
    }
    if (uVar12 == 0) {
      PIECE(local_2c,0,2) = 0;
      PIECE(local_22,0,2) = 0;
      param_3 = (byte *)0x0;
      pbVar10 = (byte *)0x0;
      goto LAB_004baff4;
    }
    cVar1 = *(char *)(local_5c - 1);
    while (cVar1 == '\0') {
      uVar12 = uVar12 - 1;
      local_60 = local_60 + 1;
      cVar1 = *(char *)(local_5c - 2);
      local_5c = local_5c - 1;
    }
    __mtold12(local_1c,uVar12,&local_2c);
    if ((int)local_4c < 0) {
      local_48 = -local_48;
    }
    iVar7 = local_48 + local_60;
    if (!bVar3) {
      iVar7 = iVar7 + param_5;
    }
    if (!bVar4) {
      iVar7 = iVar7 - param_6;
    }
    if (iVar7 < 0x1451) {
      if (-0x1451 < iVar7) {
        __multtenpow12(&local_2c,iVar7,param_4);
        pbVar10 = (byte *)CONCAT22(uStack_28,PIECE(local_2c,2,2));
        param_3 = (byte *)local_26;
        goto LAB_004baff4;
      }
      bVar6 = true;
    }
    else {
      bVar5 = true;
    }
  }
  PIECE(local_2c,0,2) = (ushort)param_3;
  pbVar10 = param_3;
  PIECE(local_22,0,2) = (ushort)local_2c;
LAB_004baff4:
  if (bVar2) {
    if (bVar5) {
      pbVar10 = (byte *)0x0;
      PIECE(local_22,0,2) = 0x7fff;
      param_3 = (byte *)0x80000000;
      PIECE(local_2c,0,2) = 0;
      local_30 = 2;
    }
    else if (bVar6) {
      PIECE(local_2c,0,2) = 0;
      PIECE(local_22,0,2) = 0;
      param_3 = (byte *)0x0;
      pbVar10 = (byte *)0x0;
      local_30 = 1;
    }
  }
  else {
    PIECE(local_2c,0,2) = 0;
    PIECE(local_22,0,2) = 0;
    param_3 = (byte *)0x0;
    pbVar10 = (byte *)0x0;
    local_30 = 4;
  }
  *param_1 = (ushort)local_2c;
  *(byte **)(param_1 + 1) = pbVar10;
  *(byte **)(param_1 + 3) = param_3;
  param_1[5] = (ushort)local_22 | (ushort)local_3c;
  return local_30;
}
#undef local_1c
#undef local_22
#undef local_26
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_44
#undef local_48
#undef local_4c
#undef local_5
#undef local_50
#undef local_54
#undef local_58
#undef local_5c
#undef local_60
#undef uStack_28


/* ---- 0x004bb570  gmtime ---- */
int * gmtime(int *param_1)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  int *piVar6;
  uint *puVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  
  bVar2 = false;
  iVar5 = *param_1;
  iVar3 = _getptd();
  if (iVar5 < 0) {
    return (int *)0x0;
  }
  if (*(int *)(iVar3 + 0x40) == 0) {
    puVar4 = malloc(0x24);
    *(undefined **)(iVar3 + 0x40) = puVar4;
    piVar6 = (int *)&DAT_008d1058;
    if (puVar4 == (undefined *)0x0) goto LAB_004bb5af;
  }
  piVar6 = *(int **)(iVar3 + 0x40);
LAB_004bb5af:
  iVar9 = iVar5 % 0x7861f80;
  iVar5 = (iVar5 / 0x7861f80) * 4;
  iVar3 = iVar5 + 0x46;
  iVar10 = iVar9;
  if (0x1e1337f < iVar9) {
    iVar10 = iVar9 + -0x1e13380;
    iVar3 = iVar5 + 0x47;
    if (0x1e1337f < iVar10) {
      iVar10 = iVar9 + -0x3c26700;
      iVar3 = iVar5 + 0x48;
      if (iVar10 < 0x1e28500) {
        bVar2 = true;
      }
      else {
        iVar3 = iVar5 + 0x49;
        iVar10 = iVar9 + -0x5a4ec00;
      }
    }
  }
  piVar6[5] = iVar3;
  piVar6[7] = iVar10 / 0x15180;
  puVar8 = (uint *)&DAT_004f0648;
  if (!bVar2) {
    puVar8 = &UINT_004f0680;
  }
  puVar7 = puVar8 + 1;
  iVar5 = 1;
  uVar1 = *puVar7;
  while ((int)uVar1 < piVar6[7]) {
    puVar7 = puVar7 + 1;
    iVar5 = iVar5 + 1;
    uVar1 = *puVar7;
  }
  piVar6[4] = iVar5 + -1;
  piVar6[3] = piVar6[7] - puVar8[iVar5 + -1];
  iVar5 = *param_1;
  piVar6[8] = 0;
  piVar6[6] = (iVar5 / 0x15180 + 4) % 7;
  piVar6[2] = (iVar10 % 0x15180) / 0xe10;
  iVar5 = (iVar10 % 0x15180) % 0xe10;
  piVar6[1] = iVar5 / 0x3c;
  *piVar6 = iVar5 % 0x3c;
  return piVar6;
}

/* ---- 0x004bb6e0  localtime ---- */
int * localtime(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  piVar1 = param_1;
  if (*param_1 < 0) {
    return (int *)0x0;
  }
  __tzset();
  iVar2 = *piVar1;
  if ((iVar2 < 0x3f481) || (0x7ffc0b7e < iVar2)) {
    piVar1 = (int *)gmtime(piVar1);
    iVar3 = _isindst(piVar1);
    iVar2 = *piVar1;
    if (iVar3 != 0) {
      iVar2 = iVar2 - UINT_004f0408;
    }
    param_1 = (int *)(iVar2 - UINT_004f0400);
    iVar2 = (int)param_1 % 0x3c;
    *piVar1 = iVar2;
    if (iVar2 < 0) {
      *piVar1 = iVar2 + 0x3c;
      param_1 = (int *)((int)param_1 + -0x3c);
    }
    param_1 = (int *)((int)param_1 / 0x3c + piVar1[1]);
    iVar2 = (int)param_1 % 0x3c;
    piVar1[1] = iVar2;
    if (iVar2 < 0) {
      piVar1[1] = iVar2 + 0x3c;
      param_1 = (int *)((int)param_1 + -0x3c);
    }
    param_1 = (int *)((int)param_1 / 0x3c + piVar1[2]);
    iVar2 = (int)param_1 % 0x18;
    piVar1[2] = iVar2;
    if (iVar2 < 0) {
      piVar1[2] = iVar2 + 0x18;
      param_1 = (int *)((int)param_1 + -0x18);
    }
    iVar2 = (int)param_1 / 0x18;
    if (0 < iVar2) {
      piVar1[6] = (iVar2 + piVar1[6]) % 7;
      piVar1[3] = piVar1[3] + iVar2;
      piVar1[7] = piVar1[7] + iVar2;
      return piVar1;
    }
    if (iVar2 < 0) {
      piVar1[6] = (iVar2 + 7 + piVar1[6]) % 7;
      iVar3 = piVar1[3] + iVar2;
      piVar1[3] = iVar3;
      if (iVar3 < 1) {
        piVar1[7] = 0x16c;
        piVar1[3] = iVar3 + 0x1f;
        piVar1[4] = 0xb;
        piVar1[5] = piVar1[5] + -1;
        return piVar1;
      }
      piVar1[7] = piVar1[7] + iVar2;
    }
  }
  else {
    param_1 = (int *)(iVar2 - UINT_004f0400);
    piVar1 = (int *)gmtime(&param_1);
    if (UINT_004f0404 != 0) {
      iVar2 = _isindst(piVar1);
      if (iVar2 != 0) {
        param_1 = (int *)((int)param_1 - UINT_004f0408);
        piVar1 = (int *)gmtime(&param_1);
        piVar1[8] = 1;
        return piVar1;
      }
    }
  }
  return piVar1;
}

/* ---- 0x004bb8d0  wcstombs ---- */
undefined4 wcstombs(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  bool bVar2;
  
  InterlockedIncrement(IMG_ADDR(0x00906c0c));
  bVar2 = UINT_00906c08 != 0;
  if (bVar2) {
    InterlockedDecrement(IMG_ADDR(0x00906c0c));
    _lock(0x13);
  }
  uVar1 = _wcstombs_lk(param_1,param_2,param_3);
  if (!bVar2) {
    InterlockedDecrement(IMG_ADDR(0x00906c0c));
    return uVar1;
  }
  _unlock(0x13);
  return uVar1;
}

/* ---- 0x004bb950  _wcstombs_lk ---- */
uint _wcstombs_lk(int param_1,ushort *param_2,uint param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  ushort *puVar6;
  int iVar7;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar4 = param_3;
  puVar6 = param_2;
  uVar2 = 0;
  local_4 = 0;
  if ((param_1 != 0) && (param_3 == 0)) {
    return uVar2;
  }
  if (param_1 == 0) {
    if (UINT_008d0b70 == 0) {
      uVar4 = wcslen(param_2);
      return uVar4;
    }
    iVar3 = WideCharToMultiByte(UINT_008d0b80,0x220,(int)param_2,-1,0,0,0,(int)&local_4);
    if ((iVar3 != 0) && (local_4 == 0)) {
      return iVar3 - 1;
    }
  }
  else if (UINT_008d0b70 == 0) {
    if (param_3 == 0) {
      return 0;
    }
    while (*puVar6 < 0x100) {
      *(char *)(uVar2 + param_1) = (char)*puVar6;
      if (*puVar6 == 0) {
        return uVar2;
      }
      uVar2 = uVar2 + 1;
      puVar6 = puVar6 + 1;
      if (param_3 <= uVar2) {
        return uVar2;
      }
    }
  }
  else if (UINT_004ed52c == 1) {
    iVar3 = 0;
    if (param_3 != 0) {
      iVar3 = wcsncnt(param_2,param_3);
    }
    uVar4 = WideCharToMultiByte(UINT_008d0b80,0x220,(int)puVar6,iVar3,param_1,iVar3,0,(int)&local_4)
    ;
    if ((uVar4 != 0) && (local_4 == 0)) {
      if (*(char *)((uVar4 - 1) + param_1) != '\0') {
        return uVar4;
      }
      return uVar4 - 1;
    }
  }
  else {
    iVar3 = WideCharToMultiByte(UINT_008d0b80,0x220,(int)param_2,-1,param_1,param_3,0,(int)&local_4)
    ;
    if (iVar3 == 0) {
      if ((local_4 == 0) && (iVar3 = GetLastError(), iVar3 == 0x7a)) {
        uVar2 = 0;
        if (uVar4 != 0) {
          do {
            iVar3 = WideCharToMultiByte(UINT_008d0b80,0,(int)puVar6,1,(int)&param_2,UINT_004ed52c,0,
                                        (int)&local_4);
            if ((iVar3 == 0) || (local_4 != 0)) goto LAB_004bbb26;
            if (uVar4 < iVar3 + uVar2) {
              return uVar2;
            }
            iVar7 = 0;
            if (0 < iVar3) {
              do {
                cVar1 = *(char *)((int)&param_2 + iVar7);
                *(char *)(uVar2 + param_1) = cVar1;
                if (cVar1 == '\0') {
                  return uVar2;
                }
                iVar7 = iVar7 + 1;
                uVar2 = uVar2 + 1;
              } while (iVar7 < iVar3);
            }
            puVar6 = puVar6 + 1;
          } while (uVar2 < uVar4);
        }
        return uVar2;
      }
    }
    else if (local_4 == 0) {
      return iVar3 - 1;
    }
  }
LAB_004bbb26:
  puVar5 = (undefined4 *)_errno();
  *puVar5 = 0x2a;
  return 0xffffffff;
}
#undef local_4


/* ---- 0x004bbb40  wcsncnt ---- */
int wcsncnt(short *param_1,int param_2)

{
  short *psVar1;
  int iVar2;
  
  psVar1 = param_1;
  iVar2 = param_2;
  if (param_2 != 0) {
    do {
      if (*psVar1 == 0) break;
      psVar1 = psVar1 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if ((iVar2 != 0) && (*psVar1 == 0)) {
      return ((int)psVar1 - (int)param_1 >> 1) + 1;
    }
  }
  return param_2;
}

/* ---- 0x004bbb80  getenv ---- */
int getenv(char *param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  int *piVar6;
  char *pcVar7;
  
  if (((UINT_008d0ad0 != 0) ||
      (((UINT_008d0ad8 == 0 || (iVar2 = __crtsetenv_from_wenviron(), iVar2 == 0)) &&
       (UINT_008d0ad0 != 0)))) && (param_1 != (char *)0x0)) {
    uVar3 = 0xffffffff;
    pcVar5 = *(char **)UINT_008d0ad0;
    pcVar7 = param_1;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3 - 1;
    piVar6 = (int *)UINT_008d0ad0;
    if (pcVar5 != (char *)0x0) {
      do {
        uVar4 = 0xffffffff;
        pcVar7 = pcVar5;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
        if (((uVar3 < ~uVar4 - 1) && (pcVar5[uVar3] == '=')) &&
           (iVar2 = _strnicoll(pcVar5,param_1,uVar3), iVar2 == 0)) {
          return *piVar6 + 1 + uVar3;
        }
        pcVar5 = (char *)piVar6[1];
        piVar6 = piVar6 + 1;
        if (pcVar5 == (char *)0x0) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}

/* ---- 0x004bbc10  _chsize ---- */
int _chsize(void)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  uint local_res0;
  undefined4 in_stack_00001008;
  int in_stack_0000100c;
  
  FUN_004addf0();
  iVar7 = 0;
  uVar1 = _lseek_lk(in_stack_00001008,0,1);
  if ((uVar1 == 0xffffffff) ||
     (local_res0 = uVar1, iVar2 = _lseek_lk(in_stack_00001008,0,2), iVar2 == -1)) {
    return -1;
  }
  iVar2 = in_stack_0000100c - iVar2;
  if (iVar2 < 1) {
    if (iVar2 < 0) {
      _lseek_lk(in_stack_00001008,in_stack_0000100c,0);
      iVar7 = _get_osfhandle(in_stack_00001008);
      iVar7 = SetEndOfFile(iVar7);
      iVar7 = (iVar7 != 0) - 1;
      if (iVar7 == -1) {
        puVar5 = (undefined4 *)_errno();
        *puVar5 = 0xd;
        iVar2 = GetLastError();
        piVar4 = (int *)__doserrno();
        *piVar4 = iVar2;
      }
    }
    _lseek_lk(in_stack_00001008,uVar1,0);
    return iVar7;
  }
  puVar5 = (undefined4 *)REGISTER0X(0x00000010);
  for (iVar6 = 0x400; puVar5 = puVar5 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar5 = 0;
  }
  uVar3 = FUN_004bcb40(in_stack_00001008,0x8000);
  while( true ) {
    iVar6 = 0x1000;
    if (iVar2 < 0x1000) {
      iVar6 = iVar2;
    }
    iVar6 = _write_lk(in_stack_00001008,&STACK0X(0x00000004),iVar6);
    if (iVar6 == -1) break;
    iVar2 = iVar2 - iVar6;
    if (iVar2 < 1) {
LAB_004bbcca:
      FUN_004bcb40(in_stack_00001008,uVar3);
      _lseek_lk(in_stack_00001008,local_res0,0);
      return iVar7;
    }
  }
  piVar4 = (int *)__doserrno();
  if (*piVar4 == 5) {
    puVar5 = (undefined4 *)_errno();
    *puVar5 = 0xd;
  }
  iVar7 = -1;
  goto LAB_004bbcca;
}

/* ---- 0x004bbd60  _raise_exc ---- */
void _raise_exc(uint *param_1,uint *param_2,byte param_3,uint param_4,uint *param_5,uint *param_6)

{
  uint *puVar1;
  uint *puVar2;
  byte bVar3;
  uint uVar4;
  uint *a1;
  
  puVar1 = param_2;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  a1 = param_1;
  if ((param_3 & 0x10) != 0) {
    param_1[1] = param_1[1] | 1;
    a1 = (uint *)0xc000008f;
  }
  if ((param_3 & 2) != 0) {
    a1 = (uint *)0xc0000093;
    param_1[1] = param_1[1] | 2;
  }
  if ((param_3 & 1) != 0) {
    a1 = (uint *)0xc0000091;
    param_1[1] = param_1[1] | 4;
  }
  if ((param_3 & 4) != 0) {
    a1 = (uint *)0xc000008e;
    param_1[1] = param_1[1] | 8;
  }
  if ((param_3 & 8) != 0) {
    a1 = (uint *)0xc0000090;
    param_1[1] = param_1[1] | 0x10;
  }
  param_1[2] = (~*param_2 & 1) << 4 | param_1[2] & 0xffffffef;
  param_1[2] = (~*param_2 & 4) << 1 | param_1[2] & 0xfffffff7;
  param_1[2] = ~*param_2 >> 1 & 4 | param_1[2] & 0xfffffffb;
  param_1[2] = ~*param_2 >> 3 & 2 | param_1[2] & 0xfffffffd;
  param_1[2] = ~*param_2 >> 5 & 1 | param_1[2] & 0xfffffffe;
  bVar3 = FUN_004bc400();
  puVar2 = param_6;
  if ((bVar3 & 1) != 0) {
    param_1[3] = param_1[3] | 0x10;
  }
  if ((bVar3 & 4) != 0) {
    param_1[3] = param_1[3] | 8;
  }
  if ((bVar3 & 8) != 0) {
    param_1[3] = param_1[3] | 4;
  }
  if ((bVar3 & 0x10) != 0) {
    param_1[3] = param_1[3] | 2;
  }
  if ((bVar3 & 0x20) != 0) {
    param_1[3] = param_1[3] | 1;
  }
  uVar4 = *puVar1 & 0xc00;
  if (uVar4 < 0x401) {
    if (uVar4 == 0x400) {
      *param_1 = *param_1 & 0xfffffffd | 1;
    }
    else if (uVar4 == 0) {
      *param_1 = *param_1 & 0xfffffffc;
    }
  }
  else if (uVar4 == 0x800) {
    *param_1 = *param_1 & 0xfffffffe | 2;
  }
  else if (uVar4 == 0xc00) {
    *param_1 = *param_1 | 3;
  }
  uVar4 = *puVar1 & 0x300;
  if (uVar4 == 0) {
    *param_1 = *param_1 & 0xffffffeb | 8;
  }
  else if (uVar4 == 0x200) {
    *param_1 = *param_1 & 0xffffffe7 | 4;
  }
  else if (uVar4 == 0x300) {
    *param_1 = *param_1 & 0xffffffe3;
  }
  *param_1 = *param_1 & 0xfffe001f | (param_4 & 0xfff) << 5;
  param_1[8] = param_1[8] | 1;
  param_1[8] = param_1[8] & 0xffffffe3 | 2;
  param_1[4] = *param_5;
  param_1[5] = param_5[1];
  param_1[0x14] = param_1[0x14] | 1;
  param_1[0x14] = param_1[0x14] & 0xffffffe3 | 2;
  param_1[0x10] = *param_6;
  param_1[0x11] = param_6[1];
  FUN_004bc410();
  RaiseException((int)a1,0,1,(int)&param_1);
  if ((param_1[2] & 0x10) != 0) {
    *puVar1 = *puVar1 & 0xfffffffe;
  }
  if ((param_1[2] & 8) != 0) {
    *puVar1 = *puVar1 & 0xfffffffb;
  }
  if ((param_1[2] & 4) != 0) {
    *puVar1 = *puVar1 & 0xfffffff7;
  }
  if ((param_1[2] & 2) != 0) {
    *puVar1 = *puVar1 & 0xffffffef;
  }
  if ((param_1[2] & 1) != 0) {
    *puVar1 = *puVar1 & 0xffffffdf;
  }
  switch(*param_1 & 3) {
  case 0:
    uVar4 = *puVar1 & 0xfffff3ff;
    break;
  case 1:
    *puVar1 = *puVar1 & 0xfffff7ff | 0x400;
    goto switchD_004bbffb_default;
  case 2:
    uVar4 = *puVar1 & 0xfffffbff | 0x800;
    break;
  case 3:
    uVar4 = *puVar1 | 0xc00;
    break;
  default:
    goto switchD_004bbffb_default;
  }
  *puVar1 = uVar4;
switchD_004bbffb_default:
  uVar4 = *param_1 >> 2 & 7;
  if (uVar4 == 0) {
    *puVar1 = *puVar1 & 0xfffff3ff | 0x300;
  }
  else {
    if (uVar4 == 1) {
      *puVar1 = *puVar1 & 0xfffff3ff | 0x200;
      *puVar2 = param_1[0x10];
      puVar2[1] = param_1[0x11];
      return;
    }
    if (uVar4 == 2) {
      *puVar1 = *puVar1 & 0xfffff3ff;
      *puVar2 = param_1[0x10];
      puVar2[1] = param_1[0x11];
      return;
    }
  }
  *puVar2 = param_1[0x10];
  puVar2[1] = param_1[0x11];
  return;
}

/* ---- 0x004bc0a0  _handle_exc ---- */
bool _handle_exc(uint param_1,double *param_2,uint param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ulonglong uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;
  float fVar7;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(undefined8 *)(_frame + (0x30 - 0x10)))
  
  uVar5 = param_1 & 0x1f;
  if (((param_1 & 8) == 0) || ((param_3 & 1) == 0)) {
    if (((param_1 & 4) == 0) || ((param_3 & 4) == 0)) {
      if (((param_1 & 1) == 0) || ((param_3 & 8) == 0)) {
        if (((param_1 & 2) != 0) && ((param_3 & 0x10) != 0)) {
          bVar6 = (param_1 & 0x10) != 0;
          local_10 = *param_2;
          if (local_10 == 0.0) {
            bVar6 = true;
          }
          else {
            fVar7 = FUN_004ba060(*(uint *)param_2,*(uint *)((int)param_2 + 4),(int *)&local_14);
            iVar4 = local_14 - 0x600;
            if (iVar4 < -0x432) {
              bVar6 = true;
              *(undefined4 *)param_2 = 0;
              local_10 = 0.0;
              *(undefined4 *)((int)param_2 + 4) = 0;
            }
            else {
              local_10 = (double)(ulonglong)
                                 (SUB87((double)fVar7,0) & 0xfffffffffffff | 0x10000000000000);
              if (iVar4 < -0x3fd) {
                iVar4 = -0x3fd - iVar4;
                do {
                  if ((((ulonglong)local_10 & 1) != 0) && (!bVar6)) {
                    bVar6 = true;
                  }
                  uVar5 = (uint)local_10 >> 1;
                  uVar1 = (ulonglong)local_10 & 0x100000000;
                  PIECE(local_10,0,4) = uVar5;
                  if (uVar1 != 0) {
                    PIECE(local_10,0,4) = uVar5 | 0x80000000;
                  }
                  iVar4 = iVar4 + -1;
                  local_10 = (double)CONCAT44(PIECE(local_10,4,4) >> 1,(uint)local_10);
                } while (iVar4 != 0);
              }
              if ((double)fVar7 < 0.0) {
                local_10 = -local_10;
              }
              *(uint *)param_2 = (uint)local_10;
              *(uint *)((int)param_2 + 4) = PIECE(local_10,4,4);
            }
          }
          if (bVar6) {
            ((code *)FUN_004bc460)(0x10);
          }
          uVar5 = param_1 & 0x1d;
        }
      }
      else {
        ((code *)FUN_004bc460)(8);
        uVar2 = UINT_004f0634;
        uVar5 = UINT_004f0624;
        uVar3 = param_3 & 0xc00;
        if (uVar3 < 0x401) {
          if (uVar3 == 0x400) {
            if (*param_2 <= 0.0) {
              local_10 = -(double)CONCAT44(UINT_004f0624,UINT_004f0620);
              *param_2 = local_10;
              uVar5 = param_1 & 0x1e;
            }
            else {
              *(uint *)param_2 = UINT_004f0630;
              *(uint *)((int)param_2 + 4) = uVar2;
              uVar5 = param_1 & 0x1e;
            }
            goto LAB_004bc3ab;
          }
          if (uVar3 == 0) {
            if (*param_2 <= 0.0) {
              local_10 = -(double)CONCAT44(UINT_004f0624,UINT_004f0620);
              *param_2 = local_10;
              uVar5 = param_1 & 0x1e;
            }
            else {
              *(uint *)param_2 = UINT_004f0620;
              *(uint *)((int)param_2 + 4) = uVar5;
              uVar5 = param_1 & 0x1e;
            }
            goto LAB_004bc3ab;
          }
        }
        else if (uVar3 == 0x800) {
          if (0.0 < *param_2) {
            *(uint *)param_2 = UINT_004f0620;
            *(uint *)((int)param_2 + 4) = uVar5;
            uVar5 = param_1 & 0x1e;
            goto LAB_004bc3ab;
          }
          local_10 = -(double)CONCAT44(UINT_004f0634,UINT_004f0630);
          *param_2 = local_10;
        }
        else if (uVar3 == 0xc00) {
          if (*param_2 <= 0.0) {
            local_10 = -(double)CONCAT44(UINT_004f0634,UINT_004f0630);
            *param_2 = local_10;
            uVar5 = param_1 & 0x1e;
          }
          else {
            *(uint *)param_2 = UINT_004f0630;
            *(uint *)((int)param_2 + 4) = uVar2;
            uVar5 = param_1 & 0x1e;
          }
          goto LAB_004bc3ab;
        }
        uVar5 = param_1 & 0x1e;
      }
    }
    else {
      ((code *)FUN_004bc460)(4);
      uVar5 = param_1 & 0x1b;
    }
  }
  else {
    ((code *)FUN_004bc460)(1);
    uVar5 = param_1 & 0x17;
  }
LAB_004bc3ab:
  if (((param_1 & 0x10) != 0) && ((param_3 & 0x20) != 0)) {
    ((code *)FUN_004bc460)(0x20);
    uVar5 = uVar5 & 0xffffffef;
  }
  return uVar5 == 0;
}
#undef local_10
#undef local_14
#undef local_18


/* ---- 0x004bc730  __ld12mul ---- */
void __ld12mul(int *param_1,int *param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  ushort uVar5;
  uint uVar6;
  ushort uVar7;
  ushort uVar8;
  ushort *puVar9;
  ushort *puVar10;
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  local_14 = 0;
  PIECE(local_c,0,1) = 0;
  PIECE(local_c,1,1) = 0;
  PIECE(local_c,2,2) = 0;
  PIECE(local_8,0,2) = 0;
  PIECE(local_8,2,2) = 0;
  uVar6 = *(ushort *)((int)param_2 + 10) & 0x7fff;
  uVar3 = *(ushort *)((int)param_1 + 10) & 0x7fff;
  uVar8 = (*(ushort *)((int)param_2 + 10) ^ *(ushort *)((int)param_1 + 10)) & 0x8000;
  uVar7 = (ushort)uVar3;
  local_24 = uVar6 + uVar3;
  PIECE(local_4,0,2) = 0;
  PIECE(local_4,2,2) = 0;
  if (((0x7ffe < uVar7) || (uVar5 = (ushort)uVar6, 0x7ffe < uVar5)) || (0xbffd < (ushort)local_24))
  {
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar8 != 0) & 0x80000000) + 0x7fff8000;
    return;
  }
  if ((ushort)local_24 < 0x3fc0) {
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  if (((uVar7 == 0) && (local_24 = local_24 + 1, (param_1[2] & 0x7fffffffU) == 0)) &&
     ((param_1[1] == 0 && (*param_1 == 0)))) {
    *(undefined2 *)((int)param_1 + 10) = 0;
    return;
  }
  if (((uVar5 == 0) && (local_24 = local_24 + 1, (param_2[2] & 0x7fffffffU) == 0)) &&
     ((param_2[1] == 0 && (*param_2 == 0)))) {
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  local_20 = (uint)&local_8;
  local_18 = 0;
  uVar3 = 5;
  do {
    if (0 < (int)uVar3) {
      puVar10 = (ushort *)(param_2 + 2);
      puVar9 = (ushort *)(local_18 * 2 + (int)param_1);
      local_10 = uVar3;
      do {
        iVar4 = __addl(*(undefined4 *)(local_20 - 4),(uint)*puVar10 * (uint)*puVar9,
                       (undefined4 *)(local_20 - 4));
        if (iVar4 != 0) {
          *(short *)local_20 = *(short *)local_20 + 1;
        }
        puVar9 = puVar9 + 1;
        puVar10 = puVar10 + -1;
        local_10 = local_10 - 1;
      } while (local_10 != 0);
    }
    local_20 = local_20 + 2;
    local_18 = local_18 + 1;
    uVar3 = uVar3 - 1;
  } while (0 < (int)uVar3);
  iVar4 = local_24 + 0xc002;
  sVar2 = (short)iVar4;
  while ((0 < sVar2 && ((PIECE(local_4,2,2) & 0x8000) == 0))) {
    __shl_12(&local_c);
    iVar4 = iVar4 + 0xffff;
    sVar2 = (short)iVar4;
  }
  uVar7 = (ushort)iVar4;
  if ((short)uVar7 < 1) {
    uVar7 = uVar7 - 1;
    if ((short)uVar7 < 0) {
      iVar4 = -(int)(short)uVar7;
      uVar7 = uVar7 + (short)iVar4;
      do {
        if (((byte)local_c & 1) != 0) {
          local_14 = local_14 + 1;
        }
        __shr_12(&local_c);
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    if (local_14 != 0) {
      PIECE(local_c,0,1) = (byte)local_c | 1;
    }
  }
  if ((0x8000 < CONCAT11(PIECE(local_c,1,1),(byte)local_c)) ||
     (iVar1 = CONCAT22((undefined2)local_4,PIECE(local_8,2,2)),
     iVar4 = CONCAT22((undefined2)local_8,PIECE(local_c,2,2)),
     (CONCAT22(PIECE(local_c,2,2),CONCAT11(PIECE(local_c,1,1),(byte)local_c)) & 0x1ffff) == 0x18000)) {
    if (CONCAT22((undefined2)local_8,PIECE(local_c,2,2)) == -1) {
      iVar4 = 0;
      if (CONCAT22((undefined2)local_4,PIECE(local_8,2,2)) == -1) {
        if (PIECE(local_4,2,2) == 0xffff) {
          PIECE(local_4,2,2) = 0x8000;
          uVar7 = uVar7 + 1;
          iVar1 = 0;
          iVar4 = 0;
        }
        else {
          PIECE(local_4,2,2) = PIECE(local_4,2,2) + 1;
          iVar1 = 0;
          iVar4 = 0;
        }
      }
      else {
        iVar1 = CONCAT22((undefined2)local_4,PIECE(local_8,2,2)) + 1;
      }
    }
    else {
      iVar4 = CONCAT22((undefined2)local_8,PIECE(local_c,2,2)) + 1;
      iVar1 = CONCAT22((undefined2)local_4,PIECE(local_8,2,2));
    }
  }
  PIECE(local_8,0,2) = (undefined2)((uint)iVar4 >> 0x10);
  PIECE(local_c,2,2) = (undefined2)iVar4;
  PIECE(local_4,0,2) = (undefined2)((uint)iVar1 >> 0x10);
  PIECE(local_8,2,2) = (undefined2)iVar1;
  if (0x7ffe < uVar7) {
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar8 != 0) & 0x80000000) + 0x7fff8000;
    return;
  }
  *(undefined2 *)param_1 = PIECE(local_c,2,2);
  *(uint *)((int)param_1 + 2) = CONCAT22(PIECE(local_8,2,2),(undefined2)local_8);
  *(uint *)((int)param_1 + 6) = CONCAT22(PIECE(local_4,2,2),(undefined2)local_4);
  *(ushort *)((int)param_1 + 10) = uVar7 | uVar8;
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004bc9f0  __multtenpow12 ---- */
void __multtenpow12(undefined2 *param_1,uint param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar4 = IMG_ADDR(0x004f0850);
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      iVar4 = IMG_ADDR(0x004f09b0);
    }
    if (param_3 == 0) {
      *param_1 = 0;
    }
    while (param_2 != 0) {
      iVar2 = CONCAT22((undefined2)local_8,PIECE(local_c,2,2));
      iVar4 = iVar4 + 0x54;
      uVar1 = param_2 & 7;
      param_2 = (int)param_2 >> 3;
      if (uVar1 != 0) {
        puVar3 = (uint *)(iVar4 + uVar1 * 0xc);
        if (0x7fff < *(ushort *)(iVar4 + uVar1 * 0xc)) {
          PIECE(local_c,0,2) = (undefined2)*puVar3;
          PIECE(local_c,2,2) = (undefined2)(*puVar3 >> 0x10);
          PIECE(local_8,0,2) = (undefined2)puVar3[1];
          PIECE(local_8,2,2) = (undefined2)(puVar3[1] >> 0x10);
          local_4 = puVar3[2];
          iVar2 = CONCAT22((undefined2)local_8,PIECE(local_c,2,2)) + -1;
          puVar3 = &local_c;
        }
        PIECE(local_8,0,2) = (undefined2)((uint)iVar2 >> 0x10);
        PIECE(local_c,2,2) = (undefined2)iVar2;
        __ld12mul(param_1,puVar3);
      }
    }
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004bca80  _strnicoll ---- */
int _strnicoll(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  if (param_3 == 0) {
    return 0;
  }
  iVar1 = __crtCompareStringA(UINT_008d0eac,1,param_1,param_3,param_2,param_3,UINT_008d0ea8);
  if (iVar1 == 0) {
    return 0x7fffffff;
  }
  return iVar1 + -2;
}

/* ---- 0x004bcac0  __crtsetenv_from_wenviron ---- */
/* Converts the wide environment block entries and installs them through __crtsetenv */

undefined4 __crtsetenv_from_wenviron(void)

{
  uint a6;
  undefined *a5;
  int iVar1;
  int *piVar2;
  
  iVar1 = *(int *)UINT_008d0ad8;
  piVar2 = (int *)UINT_008d0ad8;
  if (iVar1 == 0) {
    return 0;
  }
  while (((a6 = WideCharToMultiByte(1,0,iVar1,-1,0,0,0,0), a6 != 0 &&
          (a5 = malloc(a6), a5 != (undefined *)0x0)) &&
         (iVar1 = WideCharToMultiByte(1,0,*piVar2,-1,(int)a5,a6,0,0), iVar1 != 0))) {
    __crtsetenv(a5,0);
    iVar1 = piVar2[1];
    piVar2 = piVar2 + 1;
    if (iVar1 == 0) {
      return 0;
    }
  }
  return 0xffffffff;
}

/* ---- 0x004bcbb0  __crtCompareStringA ---- */
uint __crtCompareStringA(int param_1,int param_2,byte *param_3,undefined *param_4,byte *param_5,
                        int param_6,uint param_7)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  undefined *a5;
  int iVar5;
  #define uStack_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define abStack_e (*(byte (*)[14])(_frame + (0x30 - 0xe)))
  
  if (UINT_008d108c == 0) {
    iVar1 = CompareStringW(0,0,IMG_ADDR(0x004d8d8c),1,IMG_ADDR(0x004d8d8c),1);
    if (iVar1 == 0) {
      iVar1 = CompareStringA(0,0,IMG_ADDR(0x008d0874),1,IMG_ADDR(0x008d0874),1);
      if (iVar1 == 0) {
        return 0;
      }
      UINT_008d108c = 2;
    }
    else {
      UINT_008d108c = 1;
    }
  }
  iVar1 = (int)param_4;
  if (0 < (int)param_4) {
    iVar1 = _strncnt(param_3,param_4);
  }
  if (0 < param_6) {
    param_6 = _strncnt(param_5,param_6);
  }
  if (UINT_008d108c == 2) {
    uVar2 = CompareStringA(param_1,param_2,(int)param_3,iVar1,(int)param_5,param_6);
    return uVar2;
  }
  uStack_18 = UINT_008d108c;
  if (UINT_008d108c == 1) {
    uStack_18 = 0;
    param_4 = (undefined *)0x0;
    if (param_7 == 0) {
      param_7 = UINT_008d0b80;
    }
    if ((iVar1 == 0) || (param_6 == 0)) {
      if (iVar1 == param_6) {
        return 2;
      }
      if (1 < param_6) {
        return 1;
      }
      if (1 < iVar1) {
        return 3;
      }
      iVar3 = GetCPInfo(param_7,(int)&uStack_14);
      if (iVar3 == 0) {
        return 0;
      }
      if (0 < iVar1) {
        if (uStack_14 < 2) {
          return 3;
        }
        pbVar4 = abStack_e;
        while( true ) {
          if ((abStack_e[0] == 0) || (pbVar4[1] == 0)) {
            return 3;
          }
          if ((*pbVar4 <= *param_3) && (*param_3 <= pbVar4[1])) break;
          abStack_e[0] = pbVar4[2];
          pbVar4 = pbVar4 + 2;
        }
        return 2;
      }
      if (0 < param_6) {
        if (uStack_14 < 2) {
          return 1;
        }
        pbVar4 = abStack_e;
        while( true ) {
          if ((abStack_e[0] == 0) || (pbVar4[1] == 0)) {
            return 1;
          }
          if ((*pbVar4 <= *param_5) && (*param_5 <= pbVar4[1])) break;
          abStack_e[0] = pbVar4[2];
          pbVar4 = pbVar4 + 2;
        }
        return 2;
      }
    }
    iVar3 = MultiByteToWideChar(param_7,9,(int)param_3,iVar1,0,0);
    if (iVar3 == 0) {
      return 0;
    }
    a5 = malloc(iVar3 * 2);
    if (a5 == (undefined *)0x0) {
      return 0;
    }
    iVar1 = MultiByteToWideChar(param_7,1,(int)param_3,iVar1,(int)a5,iVar3);
    if ((((iVar1 != 0) &&
         (iVar1 = MultiByteToWideChar(param_7,9,(int)param_5,param_6,0,0), iVar1 != 0)) &&
        (param_4 = malloc(iVar1 * 2), param_4 != (undefined *)0x0)) &&
       (iVar5 = MultiByteToWideChar(param_7,1,(int)param_5,param_6,(int)param_4,iVar1), iVar5 != 0))
    {
      uStack_18 = CompareStringW(param_1,param_2,(int)a5,iVar3,(int)param_4,iVar1);
    }
    free(a5);
    free(param_4);
  }
  return uStack_18;
}
#undef abStack_e
#undef uStack_14
#undef uStack_18


/* ---- 0x004bce80  __crtsetenv ---- */
undefined4 __crtsetenv(char *param_1,int param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  char *pcVar10;
  bool bVar11;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  pcVar4 = (char *)_mbschr(param_1,0x3d);
  if (pcVar4 == (char *)0x0) {
    return 0xffffffff;
  }
  if (param_1 == pcVar4) {
    return 0xffffffff;
  }
  bVar11 = pcVar4[1] == '\0';
  if (UINT_008d0ad0 == UINT_008d0ad4) {
    UINT_008d0ad0 = copy_environ(UINT_008d0ad0);
  }
  if (UINT_008d0ad0 == 0) {
    if ((param_2 == 0) || (UINT_008d0ad8 == 0)) {
      if (bVar11) {
        return 0;
      }
      UINT_008d0ad0 = (uint)malloc(4);
      if ((undefined4 *)UINT_008d0ad0 == (undefined4 *)0x0) {
        return 0xffffffff;
      }
      *(undefined4 *)UINT_008d0ad0 = 0;
      if (UINT_008d0ad8 == 0) {
        UINT_008d0ad8 = (uint)malloc(4);
        if ((undefined4 *)UINT_008d0ad8 == (undefined4 *)0x0) {
          return 0xffffffff;
        }
        *(undefined4 *)UINT_008d0ad8 = 0;
      }
    }
    else {
      iVar5 = __crtsetenv_from_wenviron();
      if (iVar5 != 0) {
        return 0xffffffff;
      }
    }
  }
  uVar7 = UINT_008d0ad0;
  iVar6 = (int)pcVar4 - (int)param_1;
  iVar5 = findenv(param_1,iVar6);
  if ((iVar5 < 0) || (*(int *)uVar7 == 0)) {
    if (bVar11) {
      return 0;
    }
    if (iVar5 < 0) {
      iVar5 = -iVar5;
    }
    uVar7 = realloc(uVar7,iVar5 * 4 + 8);
    if (uVar7 == 0) {
      return 0xffffffff;
    }
    *(char **)(uVar7 + iVar5 * 4) = param_1;
    *(undefined4 *)(uVar7 + 4 + iVar5 * 4) = 0;
    UINT_008d0ad0 = uVar7;
  }
  else if (bVar11) {
    piVar1 = (int *)(uVar7 + iVar5 * 4);
    free(*(undefined4 *)(uVar7 + iVar5 * 4));
    iVar3 = *piVar1;
    while (iVar3 != 0) {
      *piVar1 = piVar1[1];
      iVar5 = iVar5 + 1;
      iVar3 = piVar1[1];
      piVar1 = piVar1 + 1;
    }
    uVar7 = realloc(uVar7,iVar5 * 4);
    if (uVar7 != 0) {
      UINT_008d0ad0 = uVar7;
    }
  }
  else {
    *(char **)(uVar7 + iVar5 * 4) = param_1;
  }
  if (param_2 != 0) {
    uVar7 = 0xffffffff;
    pcVar4 = param_1;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar2 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar2 != '\0');
    pcVar4 = malloc(~uVar7 + 1);
    if (pcVar4 != (char *)0x0) {
      uVar7 = 0xffffffff;
      do {
        pcVar9 = param_1;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar9 = param_1 + 1;
        cVar2 = *param_1;
        param_1 = pcVar9;
      } while (cVar2 != '\0');
      uVar7 = ~uVar7;
      pcVar9 = pcVar9 + -uVar7;
      pcVar10 = pcVar4;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar10 = pcVar10 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar10 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar10 = pcVar10 + 1;
      }
      pcVar4[iVar6] = '\0';
      SetEnvironmentVariableA((int)pcVar4,~-(uint)bVar11 & (uint)(pcVar4 + iVar6 + 1));
      free(pcVar4);
      return 0;
    }
  }
  return 0;
}
#undef local_4


/* ---- 0x004bd090  findenv ---- */
int findenv(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *(int *)UINT_008d0ad0;
  piVar2 = (int *)UINT_008d0ad0;
  if (iVar1 == 0) {
    return 0;
  }
  while ((iVar1 = _strnicoll(param_1,iVar1,param_2), iVar1 != 0 ||
         ((*(char *)(*piVar2 + param_2) != '=' && (*(char *)(*piVar2 + param_2) != '\0'))))) {
    iVar1 = piVar2[1];
    piVar2 = piVar2 + 1;
    if (iVar1 == 0) {
      return -((int)((int)piVar2 - UINT_008d0ad0) >> 2);
    }
  }
  return (int)((int)piVar2 - UINT_008d0ad0) >> 2;
}

/* ---- 0x004bd110  copy_environ ---- */
undefined4 * copy_environ(int *param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  
  iVar5 = 0;
  if (param_1 != (int *)0x0) {
    iVar1 = *param_1;
    piVar2 = param_1;
    while (iVar1 != 0) {
      piVar2 = piVar2 + 1;
      iVar5 = iVar5 + 1;
      iVar1 = *piVar2;
    }
    puVar3 = (undefined4 *)malloc(iVar5 * 4 + 4);
    if (puVar3 == (undefined4 *)0x0) {
      _amsg_exit(9);
    }
    iVar5 = *param_1;
    puVar6 = puVar3;
    while (iVar5 != 0) {
      param_1 = param_1 + 1;
      uVar4 = _strdup(iVar5);
      *puVar6 = uVar4;
      puVar6 = puVar6 + 1;
      iVar5 = *param_1;
    }
    *puVar6 = 0;
    return puVar3;
  }
  return (undefined4 *)0x0;
}

/* ---- 0x004bd180  _mbschr ---- */
byte * _mbschr(byte *param_1,uint param_2)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  
  if (UINT_008d0ea8 == 0) {
    pbVar3 = (byte *)strchr(param_1,param_2);
    return pbVar3;
  }
  _lock(0x19);
  bVar1 = *param_1;
  while (uVar2 = (uint)bVar1, bVar1 != 0) {
    if ((*(byte *)((int)&UINT_008d0ca0 + uVar2 + 1) & 4) == 0) {
      pbVar3 = param_1;
      if (param_2 == uVar2) break;
    }
    else {
      pbVar3 = param_1 + 1;
      if (param_1[1] == 0) {
        _unlock(0x19);
        return (byte *)0x0;
      }
      if (param_2 == CONCAT11(bVar1,param_1[1])) {
        _unlock(0x19);
        return param_1;
      }
    }
    param_1 = pbVar3 + 1;
    bVar1 = pbVar3[1];
  }
  _unlock(0x19);
  return (byte *)((param_2 != uVar2) - 1 & (uint)param_1);
}

/* ---- 0x004bd250  _strdup ---- */
char * _strdup(char *param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  if (param_1 != (char *)0x0) {
    uVar3 = 0xffffffff;
    pcVar2 = param_1;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    pcVar2 = malloc(~uVar3);
    if (pcVar2 != (char *)0x0) {
      uVar3 = 0xffffffff;
      do {
        pcVar5 = param_1;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar5 = param_1 + 1;
        cVar1 = *param_1;
        param_1 = pcVar5;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      pcVar5 = pcVar5 + -uVar3;
      pcVar6 = pcVar2;
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
      return pcVar2;
    }
  }
  return (char *)0x0;
}

/* ---- 0x004d5430  atof ---- */
float __cdecl atof(byte *param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint uVar2;
  undefined *puVar3;
  int iVar4;
  byte *pbVar5;
  #define local_18 (*(uint (*)[6])(_frame + (0x30 - 0x18)))
  
  while( true ) {
    if ((int)UINT_004ed52c < 2) {
      uVar2 = (byte)PTR_DAT_004ed320[(uint)*param_1 * 2] & 8;
    }
    else {
      uVar2 = _isctype(*param_1,8);
    }
    if (uVar2 == 0) break;
    param_1 = param_1 + 1;
  }
  iVar4 = -1;
  pbVar5 = param_1;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar1 = *pbVar5;
    pbVar5 = pbVar5 + 1;
  } while (bVar1 != 0);
  puVar3 = _fltin(local_18,(int)param_1);
  return (float)*(double *)(puVar3 + 0x10);
}
#undef local_18


/* ---- 0x004d54e0  _fdopen ---- */
int _fdopen(uint param_1,char *param_2)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  
  if (((UINT_00906c00 <= param_1) ||
      ((*(byte *)((&PTR_00906b00)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) == 0)) ||
     (iVar5 = _getstream(), iVar5 == 0)) {
    return 0;
  }
  cVar1 = *param_2;
  if (cVar1 != 'a') {
    if (cVar1 == 'r') {
      *(undefined4 *)(iVar5 + 0xc) = 1;
      goto LAB_004d5557;
    }
    if (cVar1 != 'w') {
      _unlock_file(0);
      return 0;
    }
  }
  *(undefined4 *)(iVar5 + 0xc) = 2;
LAB_004d5557:
  bVar2 = true;
  bVar4 = false;
  bVar3 = false;
  param_2 = param_2 + 1;
  *(uint *)(iVar5 + 0xc) = *(uint *)(iVar5 + 0xc) | UINT_008d1024;
  cVar1 = *param_2;
  do {
    if ((cVar1 == '\0') || (!bVar2)) {
      UINT_008d0ed0 = UINT_008d0ed0 + 1;
      *(uint *)(iVar5 + 0x10) = param_1;
      _unlock_file(iVar5);
      return iVar5;
    }
    switch(cVar1) {
    case '+':
      if ((*(uint *)(iVar5 + 0xc) & 0x80) != 0) break;
      *(uint *)(iVar5 + 0xc) = *(uint *)(iVar5 + 0xc) & 0xfffffffc | 0x80;
      goto LAB_004d55d5;
    case 'b':
    case 't':
      if (!bVar3) {
        bVar3 = true;
        goto LAB_004d55d5;
      }
      break;
    case 'c':
      if (!bVar4) {
        bVar4 = true;
        *(uint *)(iVar5 + 0xc) = *(uint *)(iVar5 + 0xc) | 0x4000;
        goto LAB_004d55d5;
      }
      break;
    case 'n':
      if (!bVar4) {
        bVar4 = true;
        *(uint *)(iVar5 + 0xc) = *(uint *)(iVar5 + 0xc) & 0xffffbfff;
        goto LAB_004d55d5;
      }
    }
    bVar2 = false;
LAB_004d55d5:
    cVar1 = param_2[1];
    param_2 = param_2 + 1;
  } while( true );
}

/* ---- 0x004d5670  rewind ---- */
void rewind(int param_1)

{
  uint uVar1;
  int *piVar2;
  
  uVar1 = *(uint *)(param_1 + 0x10);
  _lock_file(param_1);
  _flush(param_1);
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xffffffcf;
  if (uVar1 == 0xffffffff) {
    piVar2 = (int *)&DAT_004ed6c8;
  }
  else {
    piVar2 = (&PTR_00906b00)[(int)uVar1 >> 5] + (uVar1 & 0x1f) * 9;
  }
  *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) & 0xfd;
  if ((*(uint *)(param_1 + 0xc) & 0x80) != 0) {
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffffc;
  }
  _lseek(uVar1,0,0);
  _unlock_file(param_1);
  return;
}

/* ---- 0x004d59d0  longjmp ---- */
/* WARNING: Unable to track spacebase fully for stack */

void longjmp(int param_1)

{
  int iVar1;
  undefined *puVar2;
  int *unaff_FS_OFFSET = (int *)TEB_BASE();
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (iVar1 != *unaff_FS_OFFSET) {
    _global_unwind2(iVar1);
  }
  if (iVar1 != 0) {
    puVar2 = FUN_004d5de0(param_1 + 0x20);
    if ((puVar2 == (undefined *)0x0) || (*(int *)(param_1 + 0x20) != 0x56433230)) {
      _local_unwind2(iVar1,*(undefined4 *)(param_1 + 0x1c));
    }
    else if (*(code **)(param_1 + 0x24) != (code *)0x0) {
      (**(code **)(param_1 + 0x24))(param_1);
    }
  }
  _NLG_Notify(0);
                    /* WARNING: Could not recover jumptable at 0x004d5a45. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(param_1 + 0x14))();
  return;
}

/* ---- 0x004d5a4c  _setjmp3 ---- */
undefined4 _setjmp3(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 *puVar3;
  undefined4 unaff_EDI;
  undefined4 *puVar4;
  int *unaff_FS_OFFSET = (int *)TEB_BASE();
  uint local_res0;
  
  *param_1 = unaff_EBP;
  param_1[1] = unaff_EBX;
  param_1[2] = unaff_EDI;
  param_1[3] = unaff_ESI;
  param_1[4] = REGISTER0X(0x00000010);
  param_1[5] = local_res0;
  param_1[8] = 0x56433230;
  param_1[9] = 0;
  iVar1 = *unaff_FS_OFFSET;
  param_1[6] = iVar1;
  if (iVar1 == -1) {
    param_1[7] = 0xffffffff;
  }
  else if ((param_2 == 0) || (param_1[9] = param_3, iVar1 = param_3, param_2 == 1)) {
    param_1[7] = *(undefined4 *)(iVar1 + 0xc);
  }
  else {
    param_1[7] = param_4;
    uVar2 = param_2 - 2;
    if (uVar2 != 0) {
      puVar3 = (undefined4 *)&STACK0X(0x00000014);
      puVar4 = param_1 + 10;
      if (6 < uVar2) {
        uVar2 = 6;
      }
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
    }
  }
  return 0;
}

/* ---- 0x004d5ad0  _fltin ---- */
undefined * __cdecl _fltin(uint *param_1,int param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  undefined *puVar3;
  uint uVar4;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(undefined1 (*)[12])(_frame + (0x30 - 0xc)))
  
  iVar1 = param_2;
  uVar4 = 0;
  uVar2 = __strgtold12(local_c,&param_2,param_2,0,0,0,0);
  if ((uVar2 & 4) == 0) {
    puVar3 = _ld12tod((uint)local_c,(uint)&local_14);
    if (((uVar2 & 2) != 0) || (puVar3 == (undefined *)0x1)) {
      uVar4 = 0x80;
    }
    if (((uVar2 & 1) != 0) || (puVar3 == (undefined *)0x2)) {
      uVar4 = uVar4 | 0x100;
    }
  }
  else {
    uVar4 = 0x200;
    local_14 = 0;
    local_10 = 0;
  }
  *param_1 = uVar4;
  param_1[1] = param_2 - iVar1;
  param_1[4] = local_14;
  param_1[5] = local_10;
  return (undefined *)param_1;
}
#undef local_10
#undef local_14
#undef local_c

