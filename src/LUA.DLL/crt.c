/* LUA.DLL :: crt.c
 * functions 0x1000ef80 .. 0x10021ef0 (233 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000ef80  _ftol ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

longlong _ftol(void)

{
  float10 in_ST0;
  
  return (longlong)ROUND(in_ST0);
}
#endif


/* ---- 0x1000efa8  _setjmp3 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _setjmp3(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

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
  undefined4 unaff_retaddr;
  
  *param_1 = unaff_EBP;
  param_1[1] = unaff_EBX;
  param_1[2] = unaff_EDI;
  param_1[3] = unaff_ESI;
  param_1[4] = REGISTER0X(0x00000010);
  param_1[5] = unaff_retaddr;
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
#endif


/* ---- 0x1000f030  _CallSettingFrame ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _CallSettingFrame(undefined *UNRECOVERED_JUMPTABLE)

{
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  *unaff_FS_OFFSET = *(undefined4 *)*unaff_FS_OFFSET;
                    /* WARNING: Could not recover jumptable at 0x1000f05b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)UNRECOVERED_JUMPTABLE)();
  return;
}

/* ---- 0x1000f080  _UnwindNestedFrames ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __stdcall _UnwindNestedFrames(int a1,int a2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  
  puVar1 = (undefined4 *)*unaff_FS_OFFSET;
  RtlUnwind(a1,0x1000f0ac,a2,0);
  *(uint *)(a2 + 4) = *(uint *)(a2 + 4) & 0xfffffffd;
  uVar2 = *unaff_FS_OFFSET;
  *puVar1 = uVar2;
  *unaff_FS_OFFSET = puVar1;
  return uVar2;
}

/* ---- 0x1000f180  __CxxFrameHandler ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __CxxFrameHandler(int *param_1,int param_2,int param_3)

{
  __InternalCxxFrameHandler
            (param_1,*(int *)(param_2 + 0xc),param_3,0,*(int **)(param_2 + 8),
             *(int *)(param_2 + 0x10),param_2,'\0');
  return;
}

/* ---- 0x1000f390  _global_unwind2 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _global_unwind2(int param_1)

{
  RtlUnwind(param_1,0x1000f3a8,0,0);
  return;
}

/* ---- 0x1000f3d2  _local_unwind2 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _local_unwind2(int param_1,int param_2)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define uStack_1c (*(undefined4 *)(_frame + (0x30 - 0x1c)))
  #define puStack_18 (*(undefined1 **)(_frame + (0x30 - 0x18)))
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define iStack_10 (*(int *)(_frame + (0x30 - 0x10)))
  
  iStack_10 = param_1;
  puStack_18 = &LAB_1000f3b0;
  uStack_1c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(undefined4 *)(iVar1 + iVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
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


/* ---- 0x1000f43a  _unwind_handler ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 _unwind_handler(void)

{
  int iVar1;
  undefined4 uVar2;
  int *unaff_FS_OFFSET = (int *)TEB_BASE();
  
  uVar2 = 0;
  iVar1 = *unaff_FS_OFFSET;
  if ((*(undefined1 **)(iVar1 + 4) == &LAB_1000f3b0) &&
     (*(int *)(iVar1 + 8) == *(int *)(*(int *)(iVar1 + 0xc) + 0xc))) {
    uVar2 = 1;
  }
  return uVar2;
}

/* ---- 0x1000f466  _NLG_Notify ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __stdcall _NLG_Notify(int a1)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  DAT_100282c0 = *(undefined4 *)(unaff_EBP + 8);
  DAT_100282bc = in_EAX;
  DAT_100282c4 = unaff_EBP;
  return in_EAX;
}
#endif


/* ---- 0x1000f480  vsprintf ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl vsprintf(char *buf,char *fmt,void *args)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_20 (*(char **)(_frame + (0x30 - 0x20)))
  #define local_1c (*(int *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(char **)(_frame + (0x30 - 0x18)))
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  
  local_18 = buf;
  local_20 = buf;
  local_14 = 0x42;
  local_1c = 0x7fffffff;
  iVar1 = _output((int *)&local_20,fmt,args);
  local_1c = local_1c + -1;
  if (-1 < local_1c) {
    *local_20 = '\0';
    return iVar1;
  }
  _flsbuf(0,(int *)&local_20);
  return iVar1;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20


/* ---- 0x1000f4f0  sprintf ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl sprintf(char *buf,char *fmt,...)

{
  unsigned char _frame[0x30];  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_20 (*(char **)(_frame + (0x30 - 0x20)))
  #define local_1c (*(int *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(char **)(_frame + (0x30 - 0x18)))
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  
  local_18 = buf;
  local_20 = buf;
  local_14 = 0x42;
  local_1c = 0x7fffffff;
  iVar1 = _output((int *)&local_20,fmt,(undefined4 *)&STACK0X(0x0000000c));
  local_1c = local_1c + -1;
  if (-1 < local_1c) {
    *local_20 = '\0';
    return iVar1;
  }
  _flsbuf(0,(int *)&local_20);
  return iVar1;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20


/* ---- 0x1000f560  printf ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl printf(char *fmt,...)

{
  int iVar1;
  int iVar2;
  
  _lock_file2(1,IMG_ADDR(0x100282f0));
  iVar1 = _stbuf((undefined4 *)&DAT_100282f0);
  iVar2 = _output((int *)&DAT_100282f0,fmt,(undefined4 *)&STACK0X(0x00000008));
  _ftbuf(iVar1,(int *)&DAT_100282f0);
  _unlock_file2(1,IMG_ADDR(0x100282f0));
  return iVar2;
}

/* ---- 0x1000f680  strtol ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl strtol(byte *param_1,undefined4 *param_2,uint param_3)

{
  strtoxl(param_1,param_2,param_3,0);
  return;
}

/* ---- 0x1000f6a0  strtoxl ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl strtoxl(byte *param_1,undefined4 *param_2,uint param_3,uint param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  byte bVar5;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(byte **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  bVar5 = *param_1;
  pbVar1 = param_1;
  while( true ) {
    local_c = (uint)bVar5;
    local_8 = pbVar1 + 1;
    if (DAT_10028b5c < 2) {
      uVar2 = (byte)PTR_DAT_10028950[local_c * 2] & 8;
    }
    else {
      uVar2 = _isctype(local_c,8);
    }
    if (uVar2 == 0) break;
    bVar5 = *local_8;
    pbVar1 = local_8;
  }
  if (bVar5 == 0x2d) {
    param_4 = param_4 | 2;
  }
  else if (bVar5 != 0x2b) goto LAB_1000f72b;
  bVar5 = *local_8;
  local_8 = pbVar1 + 2;
  local_c = (uint)bVar5;
LAB_1000f72b:
  if ((((int)param_3 < 0) || (param_3 == 1)) || (0x24 < (int)param_3)) {
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = param_1;
    }
    return 0;
  }
  if (param_3 == 0) {
    if (bVar5 == 0x30) {
      if ((*local_8 == 0x78) || (param_3 = 8, *local_8 == 0x58)) {
        param_3 = 0x10;
      }
    }
    else {
      param_3 = 10;
    }
  }
  if (((param_3 == 0x10) && (bVar5 == 0x30)) && ((*local_8 == 0x78 || (*local_8 == 0x58)))) {
    bVar5 = local_8[1];
    local_c = (uint)bVar5;
    local_8 = local_8 + 2;
  }
  uVar2 = (uint)(0xffffffff / (ulonglong)param_3);
  do {
    if (DAT_10028b5c < 2) {
      uVar3 = (byte)PTR_DAT_10028950[local_c * 2] & 4;
    }
    else {
      uVar3 = _isctype(local_c,4);
    }
    if (uVar3 == 0) {
      if (DAT_10028b5c < 2) {
        uVar3 = *(ushort *)(PTR_DAT_10028950 + local_c * 2) & 0x103;
      }
      else {
        uVar3 = _isctype(local_c,0x103);
      }
      if (uVar3 == 0) {
LAB_1000f864:
        local_8 = local_8 + -1;
        if ((param_4 & 8) == 0) {
          if (param_2 != (undefined4 *)0x0) {
            local_8 = param_1;
          }
          local_4 = 0;
        }
        else if (((param_4 & 4) != 0) ||
                (((param_4 & 1) == 0 &&
                 ((((param_4 & 2) != 0 && (0x80000000 < local_4)) ||
                  (((param_4 & 2) == 0 && (0x7fffffff < local_4)))))))) {
          piVar4 = _errno();
          *piVar4 = 0x22;
          if ((param_4 & 1) == 0) {
            local_4 = ((param_4 & 2) != 0) + 0x7fffffff;
          }
          else {
            local_4 = 0xffffffff;
          }
        }
        if (param_2 != (undefined4 *)0x0) {
          *param_2 = local_8;
        }
        if ((param_4 & 2) != 0) {
          local_4 = -local_4;
        }
        return local_4;
      }
      uVar3 = tolower((int)(char)bVar5);
      uVar3 = uVar3 - 0x37;
    }
    else {
      uVar3 = (int)(char)bVar5 - 0x30;
    }
    if (param_3 <= uVar3) goto LAB_1000f864;
    if ((local_4 < uVar2) ||
       ((local_4 == uVar2 && (uVar3 <= (uint)(0xffffffff % (ulonglong)param_3))))) {
      local_4 = local_4 * param_3 + uVar3;
      param_4 = param_4 | 8;
    }
    else {
      param_4 = param_4 | 0xc;
    }
    bVar5 = *local_8;
    local_8 = local_8 + 1;
    local_c = (uint)bVar5;
  } while( true );
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x1000f930  strtoul ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl strtoul(byte *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = strtoxl(param_1,param_2,param_3,1);
  return uVar1;
}

/* ---- 0x1000f960  strchr ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint * __cdecl strchr(uint *param_1,char param_2)

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

/* ---- 0x1000fa20  memcpy ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 * __cdecl memcpy(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if ((param_2 < param_1) && (param_1 < (undefined4 *)(param_3 + (int)param_2))) {
    puVar3 = (undefined4 *)((param_3 - 4) + (int)param_2);
    puVar4 = (undefined4 *)((param_3 - 4) + (int)param_1);
    if (((uint)puVar4 & 3) == 0) {
      uVar1 = param_3 >> 2;
      uVar2 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
        switch(uVar2) {
        case 0:
          return param_1;
        case 2:
          goto switchD_1000fbd7_caseD_2;
        case 3:
          goto switchD_1000fbd7_caseD_3;
        }
        goto switchD_1000fbd7_caseD_1;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto switchD_1000fbd7_caseD_0;
      case 1:
        goto switchD_1000fbd7_caseD_1;
      case 2:
        goto switchD_1000fbd7_caseD_2;
      case 3:
        goto switchD_1000fbd7_caseD_3;
      default:
        uVar1 = param_3 - ((uint)puVar4 & 3);
        switch((uint)puVar4 & 3) {
        case 1:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          puVar3 = (undefined4 *)((int)puVar3 + -1);
          uVar1 = uVar1 >> 2;
          puVar4 = (undefined4 *)((int)puVar4 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_1000fbd7_caseD_2;
            case 3:
              goto switchD_1000fbd7_caseD_3;
            }
            goto switchD_1000fbd7_caseD_1;
          }
          break;
        case 2:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          puVar3 = (undefined4 *)((int)puVar3 + -2);
          puVar4 = (undefined4 *)((int)puVar4 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_1000fbd7_caseD_2;
            case 3:
              goto switchD_1000fbd7_caseD_3;
            }
            goto switchD_1000fbd7_caseD_1;
          }
          break;
        case 3:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
          puVar3 = (undefined4 *)((int)puVar3 + -3);
          puVar4 = (undefined4 *)((int)puVar4 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_1000fbd7_caseD_2;
            case 3:
              goto switchD_1000fbd7_caseD_3;
            }
            goto switchD_1000fbd7_caseD_1;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar4[7 - uVar1] = puVar3[7 - uVar1];
    case 6:
      puVar4[6 - uVar1] = puVar3[6 - uVar1];
    case 5:
      puVar4[5 - uVar1] = puVar3[5 - uVar1];
    case 4:
      puVar4[4 - uVar1] = puVar3[4 - uVar1];
    case 3:
      puVar4[3 - uVar1] = puVar3[3 - uVar1];
    case 2:
      puVar4[2 - uVar1] = puVar3[2 - uVar1];
    case 1:
      puVar4[1 - uVar1] = puVar3[1 - uVar1];
      puVar3 = puVar3 + -uVar1;
      puVar4 = puVar4 + -uVar1;
    }
    switch(uVar2) {
    case 1:
switchD_1000fbd7_caseD_1:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      return param_1;
    case 2:
switchD_1000fbd7_caseD_2:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      return param_1;
    case 3:
switchD_1000fbd7_caseD_3:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
      return param_1;
    }
switchD_1000fbd7_caseD_0:
    return param_1;
  }
  puVar3 = param_1;
  if (((uint)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    uVar2 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = *param_2;
        param_2 = param_2 + 1;
        puVar3 = puVar3 + 1;
      }
      switch(uVar2) {
      case 0:
        return param_1;
      case 2:
        goto switchD_1000fa55_caseD_2;
      case 3:
        goto switchD_1000fa55_caseD_3;
      }
      goto switchD_1000fa55_caseD_1;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto switchD_1000fa55_caseD_0;
    case 1:
      goto switchD_1000fa55_caseD_1;
    case 2:
      goto switchD_1000fa55_caseD_2;
    case 3:
      goto switchD_1000fa55_caseD_3;
    default:
      uVar1 = (param_3 - 4) + ((uint)param_1 & 3);
      switch((uint)param_1 & 3) {
      case 1:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 2) = *(undefined1 *)((int)param_2 + 2);
        param_2 = (undefined4 *)((int)param_2 + 3);
        puVar3 = (undefined4 *)((int)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_1000fa55_caseD_2;
          case 3:
            goto switchD_1000fa55_caseD_3;
          }
          goto switchD_1000fa55_caseD_1;
        }
        break;
      case 2:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        param_2 = (undefined4 *)((int)param_2 + 2);
        puVar3 = (undefined4 *)((int)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_1000fa55_caseD_2;
          case 3:
            goto switchD_1000fa55_caseD_3;
          }
          goto switchD_1000fa55_caseD_1;
        }
        break;
      case 3:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar3 = (undefined4 *)((int)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_1000fa55_caseD_2;
          case 3:
            goto switchD_1000fa55_caseD_3;
          }
          goto switchD_1000fa55_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar3[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar3[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar3[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar3[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar3[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar3[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar3[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar3 = puVar3 + uVar1;
  }
  switch(uVar2) {
  case 1:
switchD_1000fa55_caseD_1:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    return param_1;
  case 2:
switchD_1000fa55_caseD_2:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
switchD_1000fa55_caseD_3:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
switchD_1000fa55_caseD_0:
  return param_1;
}

/* ---- 0x1000fd58  longjmp ---- */
/* WARNING: Unable to track spacebase fully for stack */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void longjmp(int param_1)

{
  int iVar1;
  int iVar2;
  int *unaff_FS_OFFSET = (int *)TEB_BASE();
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (iVar1 != *unaff_FS_OFFSET) {
    _global_unwind2(iVar1);
  }
  if (iVar1 != 0) {
    iVar2 = FUN_10015160(param_1 + 0x20);
    if ((iVar2 == 0) || (*(int *)(param_1 + 0x20) != 0x56433230)) {
      _local_unwind2(iVar1,*(int *)(param_1 + 0x1c));
    }
    else if (*(code **)(param_1 + 0x24) != (code *)0x0) {
      (**(code **)(param_1 + 0x24))(param_1);
    }
  }
  _NLG_Notify(0);
                    /* WARNING: Could not recover jumptable at 0x1000fdcd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(param_1 + 0x14))();
  return;
}

/* ---- 0x1000fec0  strerror ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

char * __cdecl strerror(int param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  
  piVar2 = _getptd();
  if (piVar2[9] == 0) {
    iVar3 = malloc(0x86);
    piVar2[9] = iVar3;
    pcVar6 = &DAT_1002bf98;
    if (iVar3 == 0) goto LAB_1000feec;
  }
  pcVar6 = (char *)piVar2[9];
LAB_1000feec:
  if ((param_1 < 0) || (DAT_10028d48 <= param_1)) {
    param_1 = DAT_10028d48;
  }
  uVar4 = 0xffffffff;
  pcVar7 = (&PTR_s_No_error_10028c98)[param_1];
  do {
    pcVar8 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar8 + -uVar4;
  pcVar8 = pcVar6;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  return pcVar6;
}

/* ---- 0x1000ff30  _dosmaperr ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _dosmaperr(undefined *param_1)

{
  int *piVar1;
  undefined **ppuVar2;
  int iVar3;
  
  piVar1 = __doserrno();
  iVar3 = 0;
  *piVar1 = (int)param_1;
  ppuVar2 = (undefined **)&DAT_10028550;
  do {
    if (param_1 == *ppuVar2) {
      piVar1 = _errno();
      *piVar1 = *(int *)(iVar3 * 8 + IMG_ADDR(0x10028554));
      return;
    }
    ppuVar2 = ppuVar2 + 2;
    iVar3 = iVar3 + 1;
  } while (ppuVar2 < &PTR_DAT_100286b8);
  if (((undefined *)0x12 < param_1) && (param_1 < (undefined *)0x25)) {
    piVar1 = _errno();
    *piVar1 = 0xd;
    return;
  }
  if (((undefined *)0xbb < param_1) && (param_1 < (undefined *)0xcb)) {
    piVar1 = _errno();
    *piVar1 = 8;
    return;
  }
  piVar1 = _errno();
  *piVar1 = 0x16;
  return;
}

/* ---- 0x1000ffb0  _errno ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * _errno(void)

{
  int *piVar1;
  
  piVar1 = _getptd();
  return piVar1 + 2;
}

/* ---- 0x1000ffc0  __doserrno ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __doserrno(void)

{
  int *piVar1;
  
  piVar1 = _getptd();
  return piVar1 + 3;
}

/* ---- 0x1000ffd0  system ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl system(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  int *piVar3;
  #define local_10 (*(uint **)(_frame + (0x20 - 0x10)))
  #define local_c (*(undefined **)(_frame + (0x20 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  local_10 = (uint *)getenv((byte *)"COMSPEC");
  if (param_1 == 0) {
    if (local_10 != (uint *)0x0) {
      iVar1 = _access((uint)local_10,0);
      return (uint)(iVar1 == 0);
    }
    return 0;
  }
  local_c = &DAT_10023c40;
  local_8 = param_1;
  local_4 = 0;
  if (local_10 != (uint *)0x0) {
    uVar2 = _spawnvpe(0,local_10,&local_10,(undefined4 *)0x0);
    if (uVar2 != 0xffffffff) {
      return uVar2;
    }
    piVar3 = _errno();
    if ((*piVar3 != 2) && (piVar3 = _errno(), *piVar3 != 0xd)) {
      return 0xffffffff;
    }
  }
  local_10 = (uint *)IMG_ADDR(0x10023c34);
  if ((DAT_1002c08c & 0x8000) == 0) {
    local_10 = (uint *)IMG_ADDR(0x10023c2c);
  }
  uVar2 = _spawnvpe_search(0,local_10,&local_10,(undefined4 *)0x0);
  return uVar2;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x10010090  remove ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl remove(int param_1)

{
  int iVar1;
  undefined *puVar2;
  
  iVar1 = DeleteFileA(param_1);
  if (iVar1 == 0) {
    puVar2 = (undefined *)GetLastError();
  }
  else {
    puVar2 = (undefined *)0x0;
  }
  if (puVar2 != (undefined *)0x0) {
    _dosmaperr(puVar2);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x100100c0  rename ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl rename(int param_1,int param_2)

{
  int iVar1;
  undefined *puVar2;
  
  iVar1 = MoveFileA(param_1,param_2);
  if (iVar1 == 0) {
    puVar2 = (undefined *)GetLastError();
  }
  else {
    puVar2 = (undefined *)0x0;
  }
  if (puVar2 != (undefined *)0x0) {
    _dosmaperr(puVar2);
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x10010100  tmpnam ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

char * __cdecl tmpnam(char *param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  _lock(3);
  if (DAT_1002bfc0 == '\0') {
    tmpnam_genfname(0);
  }
  else {
    iVar2 = FUN_100102a0((byte *)&DAT_1002bfc0);
    if (iVar2 != 0) {
LAB_10010201:
      _unlock(3);
      return (char *)0x0;
    }
  }
  iVar2 = _access(IMG_ADDR(0x1002bfc0),0);
  while (iVar2 == 0) {
    iVar2 = FUN_100102a0((byte *)&DAT_1002bfc0);
    if (iVar2 != 0) goto LAB_10010201;
    iVar2 = _access(IMG_ADDR(0x1002bfc0),0);
  }
  if (param_1 == (char *)0x0) {
    piVar3 = _getptd();
    if (piVar3[10] == 0) {
      iVar2 = malloc(0xe);
      piVar3[10] = iVar2;
      if (iVar2 == 0) {
        _unlock(3);
        return &DAT_1002bfc0;
      }
    }
    uVar4 = 0xffffffff;
    param_1 = (char *)piVar3[10];
    pcVar6 = &DAT_1002bfc0;
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
    pcVar7 = param_1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
  }
  else {
    uVar4 = 0xffffffff;
    pcVar6 = &DAT_1002bfc0;
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
    pcVar7 = param_1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  _unlock(3);
  return param_1;
}

/* ---- 0x10010310  getenv ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl getenv(byte *param_1)

{
  int iVar1;
  
  _lock(0xc);
  iVar1 = _getenv_lk(param_1);
  _unlock(0xc);
  return iVar1;
}

/* ---- 0x10010340  _getenv_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _getenv_lk(byte *param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  int *piVar6;
  byte *pbVar7;
  
  if (((DAT_1002c0a8 != (int *)0x0) ||
      (((DAT_1002c0b0 == 0 || (iVar2 = __crtsetenv_from_wenviron(), iVar2 == 0)) &&
       (DAT_1002c0a8 != (int *)0x0)))) && (param_1 != (byte *)0x0)) {
    uVar3 = 0xffffffff;
    pbVar5 = (byte *)*DAT_1002c0a8;
    pbVar7 = param_1;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      bVar1 = *pbVar7;
      pbVar7 = pbVar7 + 1;
    } while (bVar1 != 0);
    uVar3 = ~uVar3 - 1;
    piVar6 = DAT_1002c0a8;
    if (pbVar5 != (byte *)0x0) {
      do {
        uVar4 = 0xffffffff;
        pbVar7 = pbVar5;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          bVar1 = *pbVar7;
          pbVar7 = pbVar7 + 1;
        } while (bVar1 != 0);
        if (((uVar3 < ~uVar4 - 1) && (pbVar5[uVar3] == 0x3d)) &&
           (iVar2 = _strnicoll(pbVar5,param_1,uVar3), iVar2 == 0)) {
          return *piVar6 + 1 + uVar3;
        }
        pbVar5 = (byte *)piVar6[1];
        piVar6 = piVar6 + 1;
        if (pbVar5 == (byte *)0x0) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}

/* ---- 0x100103d0  strftime ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl strftime(byte *param_1,uint param_2,byte *param_3,int *param_4)

{
  _Strftime(param_1,param_2,param_3,param_4,(undefined *)0x0);
  return;
}

/* ---- 0x100103f0  _Strftime ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _Strftime(byte *param_1,uint param_2,byte *param_3,int *param_4,undefined *param_5)

{
  byte bVar1;
  int *piVar2;
  int *piVar3;
  undefined *puVar4;
  byte *pbVar5;
  byte *pbVar6;
  bool bVar7;
  
  puVar4 = PTR_PTR_10028764;
  if (param_5 != (undefined *)0x0) {
    puVar4 = param_5;
  }
  param_5 = (undefined *)param_2;
  InterlockedIncrement(IMG_ADDR(0x1002c710));
  bVar7 = DAT_1002c70c == 0;
  pbVar5 = param_3;
  piVar2 = param_4;
  if (!bVar7) {
    InterlockedDecrement(IMG_ADDR(0x1002c710));
    _lock(0x13);
    pbVar5 = param_3;
    piVar2 = param_4;
  }
  while ((piVar3 = param_4, param_4 = piVar2, param_5 != (undefined *)0x0 &&
         (bVar1 = *pbVar5, bVar1 != 0))) {
    if (bVar1 == 0x25) {
      pbVar6 = pbVar5 + 1;
      bVar1 = *pbVar6;
      if (bVar1 == 0x23) {
        pbVar6 = pbVar5 + 2;
      }
      DAT_1002bfe0 = (uint)(bVar1 == 0x23);
      _expandtime(*pbVar6,piVar3,(byte *)&param_1,(uint *)&param_5,(int)puVar4);
    }
    else {
      if (((PTR_DAT_10028950[(uint)bVar1 * 2 + 1] & 0x80) != 0) && ((undefined *)0x1 < param_5)) {
        *param_1 = bVar1;
        param_1 = param_1 + 1;
        pbVar5 = pbVar5 + 1;
        param_5 = param_5 + -1;
      }
      *param_1 = *pbVar5;
      param_1 = param_1 + 1;
      param_5 = param_5 + -1;
      pbVar6 = pbVar5;
    }
    piVar2 = param_4;
    param_4 = piVar3;
    pbVar5 = pbVar6 + 1;
  }
  if (bVar7) {
    InterlockedDecrement(IMG_ADDR(0x1002c710));
  }
  else {
    _unlock(0x13);
  }
  if (param_5 == (undefined *)0x0) {
    return 0;
  }
  *param_1 = 0;
  return param_2 - (int)param_5;
}

/* ---- 0x10010540  _expandtime ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _expandtime(undefined1 param_1,int *param_2,byte *param_3,uint *param_4,int param_5)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  
  switch(param_1) {
  case 0x25:
    **(undefined1 **)param_3 = 0x25;
    *(int *)param_3 = *(int *)param_3 + 1;
    *param_4 = *param_4 - 1;
    break;
  case 0x41:
    _store_str(*(char **)(param_5 + 0x1c + param_2[6] * 4),(int *)param_3,(int *)param_4);
    return;
  case 0x42:
    _store_str(*(char **)(param_5 + 0x68 + param_2[4] * 4),(int *)param_3,(int *)param_4);
    return;
  case 0x48:
    DAT_1002bfe4 = DAT_1002bfe0;
    _store_num(param_2[2],2,(int *)param_3,param_4);
    return;
  case 0x49:
    DAT_1002bfe4 = DAT_1002bfe0;
    iVar3 = param_2[2] % 0xc;
    if (iVar3 == 0) {
      iVar3 = 0xc;
    }
    _store_num(iVar3,2,(int *)param_3,param_4);
    return;
  case 0x4d:
    DAT_1002bfe4 = DAT_1002bfe0;
    _store_num(param_2[1],2,(int *)param_3,param_4);
    return;
  case 0x53:
    DAT_1002bfe4 = DAT_1002bfe0;
    _store_num(*param_2,2,(int *)param_3,param_4);
    return;
  case 0x55:
    iVar3 = param_2[6];
    goto LAB_10010877;
  case 0x57:
    if (param_2[6] == 0) {
      iVar3 = 6;
    }
    else {
      iVar3 = param_2[6] + -1;
    }
LAB_10010877:
    DAT_1002bfe4 = DAT_1002bfe0;
    iVar1 = param_2[7];
    if (iVar1 < iVar3) {
      iVar4 = 0;
    }
    else {
      iVar4 = iVar1 / 7;
      if (iVar3 <= iVar1 % 7) {
        iVar4 = iVar4 + 1;
      }
    }
    _store_num(iVar4,2,(int *)param_3,param_4);
    return;
  case 0x58:
    DAT_1002bfe0 = 0;
    _store_winword(*(byte **)(param_5 + 0xa8),param_2,param_3,(int *)param_4,param_5);
    return;
  case 0x59:
    DAT_1002bfe4 = DAT_1002bfe0;
    _store_num(param_2[5] % 100 + (param_2[5] / 100 + 0x13) * 100,4,(int *)param_3,param_4);
    return;
  case 0x5a:
  case 0x7a:
    __tzset();
    _store_str((&PTR_DAT_10028df8)[param_2[8] != 0],(int *)param_3,(int *)param_4);
    return;
  case 0x61:
    _store_str(*(char **)(param_5 + param_2[6] * 4),(int *)param_3,(int *)param_4);
    return;
  case 0x62:
    _store_str(*(char **)(param_5 + 0x38 + param_2[4] * 4),(int *)param_3,(int *)param_4);
    return;
  case 99:
    if (DAT_1002bfe0 == 0) {
      pbVar2 = *(byte **)(param_5 + 0xa0);
    }
    else {
      DAT_1002bfe0 = 0;
      pbVar2 = *(byte **)(param_5 + 0xa4);
    }
    _store_winword(pbVar2,param_2,param_3,(int *)param_4,param_5);
    if (*param_4 != 0) {
      **(undefined1 **)param_3 = 0x20;
      *(int *)param_3 = *(int *)param_3 + 1;
      *param_4 = *param_4 - 1;
      _store_winword(*(byte **)(param_5 + 0xa8),param_2,param_3,(int *)param_4,param_5);
      return;
    }
    break;
  case 100:
    DAT_1002bfe4 = DAT_1002bfe0;
    _store_num(param_2[3],2,(int *)param_3,param_4);
    return;
  case 0x6a:
    DAT_1002bfe4 = DAT_1002bfe0;
    _store_num(param_2[7] + 1,3,(int *)param_3,param_4);
    return;
  case 0x6d:
    DAT_1002bfe4 = DAT_1002bfe0;
    _store_num(param_2[4] + 1,2,(int *)param_3,param_4);
    return;
  case 0x70:
    if (param_2[2] < 0xc) {
      _store_str(*(char **)(param_5 + 0x98),(int *)param_3,(int *)param_4);
      return;
    }
    _store_str(*(char **)(param_5 + 0x9c),(int *)param_3,(int *)param_4);
    return;
  case 0x77:
    DAT_1002bfe4 = DAT_1002bfe0;
    _store_num(param_2[6],1,(int *)param_3,param_4);
    return;
  case 0x78:
    if (DAT_1002bfe0 != 0) {
      DAT_1002bfe0 = 0;
      _store_winword(*(byte **)(param_5 + 0xa4),param_2,param_3,(int *)param_4,param_5);
      return;
    }
    _store_winword(*(byte **)(param_5 + 0xa0),param_2,param_3,(int *)param_4,param_5);
    return;
  case 0x79:
    DAT_1002bfe4 = DAT_1002bfe0;
    _store_num(param_2[5] % 100,2,(int *)param_3,param_4);
    return;
  }
  return;
}

/* ---- 0x10010ae0  _store_str ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _store_str(char *param_1,int *param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = *param_3;
  for (; (iVar1 != 0 && (*param_1 != '\0')); param_1 = param_1 + 1) {
    *(char *)*param_2 = *param_1;
    *param_2 = *param_2 + 1;
    iVar1 = *param_3 + -1;
    *param_3 = iVar1;
  }
  return;
}

/* ---- 0x10010b10  _store_num ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _store_num(int param_1,uint param_2,int *param_3,uint *param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (DAT_1002bfe4 != 0) {
    _store_number(param_1,param_3,param_4);
    return;
  }
  if (*param_4 <= param_2) {
    *param_4 = 0;
    return;
  }
  iVar1 = param_2 - 1;
  if (param_2 != 0) {
    do {
      *(char *)(*param_3 + iVar1) = (char)(param_1 % 10) + '0';
      param_1 = param_1 / 10;
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != -1);
  }
  *param_3 = *param_3 + iVar2;
  *param_4 = *param_4 - iVar2;
  return;
}

/* ---- 0x10010bb0  _store_number ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _store_number(int param_1,int *param_2,uint *param_3)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  char *pcVar4;
  
  pcVar4 = (char *)*param_2;
  uVar3 = *param_3;
  do {
    if (uVar3 < 2) break;
    *pcVar4 = (char)(param_1 % 10) + '0';
    pcVar4 = pcVar4 + 1;
    uVar3 = *param_3 - 1;
    *param_3 = uVar3;
    param_1 = param_1 / 10;
  } while (0 < param_1);
  pcVar2 = (char *)*param_2;
  *param_2 = (int)pcVar4;
  pcVar4 = pcVar4 + -1;
  do {
    cVar1 = *pcVar4;
    *pcVar4 = *pcVar2;
    pcVar4 = pcVar4 + -1;
    *pcVar2 = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (pcVar2 < pcVar4);
  return;
}

/* ---- 0x10010c20  _store_winword ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _store_winword(byte *param_1,int *param_2,byte *param_3,int *param_4,int param_5)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  char cVar6;
  byte *pbVar7;
  
  pbVar2 = param_3;
  bVar1 = *param_1;
  pbVar7 = param_1;
  do {
    if ((bVar1 == 0) || (*param_4 == 0)) {
      return;
    }
    DAT_1002bfe4 = 0;
    cVar6 = '\0';
    PIECE(param_1,0,1) = 0;
    uVar5 = 0;
    pbVar3 = pbVar7 + 1;
    do {
      param_3 = pbVar3;
      uVar4 = uVar5;
      uVar5 = uVar4 + 1;
      pbVar3 = param_3 + 1;
    } while (*param_3 == *pbVar7);
    switch(*pbVar7) {
    case 0x27:
      if ((uVar5 & 1) == 0) {
        param_3 = pbVar7 + uVar5;
      }
      else {
        param_3 = pbVar7 + uVar5;
        bVar1 = *param_3;
        while( true ) {
          if ((bVar1 == 0) || (*param_4 == 0)) goto LAB_10010d0c;
          if (bVar1 == 0x27) break;
          if ((PTR_DAT_10028950[(uint)bVar1 * 2 + 1] & 0x80) != 0) {
            **(byte **)pbVar2 = bVar1;
            param_3 = param_3 + 1;
            *(int *)pbVar2 = *(int *)pbVar2 + 1;
            *param_4 = *param_4 + -1;
          }
          **(byte **)pbVar2 = *param_3;
          param_3 = param_3 + 1;
          *(int *)pbVar2 = *(int *)pbVar2 + 1;
          *param_4 = *param_4 + -1;
          bVar1 = *param_3;
        }
        param_3 = param_3 + 1;
      }
      goto LAB_10010d0c;
    case 0x41:
    case 0x61:
      uVar5 = _stricmp(pbVar7,(byte *)"am/pm");
      if (uVar5 == 0) {
        param_3 = pbVar7 + 5;
        cVar6 = 'p';
        PIECE(param_1,0,1) = 0x70;
      }
      else {
        uVar5 = _stricmp(pbVar7,&DAT_10023d78);
        if (uVar5 == 0) {
          param_3 = pbVar7 + 3;
        }
        cVar6 = 'p';
        PIECE(param_1,0,1) = 0x70;
      }
      break;
    case 0x48:
      if (uVar4 == 0) {
        DAT_1002bfe4 = 1;
      }
      else if (uVar5 != 2) break;
      cVar6 = 'H';
      PIECE(param_1,0,1) = 0x48;
      break;
    case 0x4d:
      switch(uVar4) {
      case 0:
        DAT_1002bfe4 = 1;
      case 1:
        cVar6 = 'm';
        PIECE(param_1,0,1) = 0x6d;
        break;
      case 2:
        cVar6 = 'b';
        PIECE(param_1,0,1) = 0x62;
        break;
      case 3:
        cVar6 = 'B';
        PIECE(param_1,0,1) = 0x42;
      }
      break;
    case 100:
      switch(uVar4) {
      case 0:
        DAT_1002bfe4 = 1;
      case 1:
        cVar6 = 'd';
        PIECE(param_1,0,1) = 100;
        break;
      case 2:
        cVar6 = 'a';
        PIECE(param_1,0,1) = 0x61;
        break;
      case 3:
        cVar6 = 'A';
        PIECE(param_1,0,1) = 0x41;
      }
      break;
    case 0x68:
      if (uVar4 == 0) {
        DAT_1002bfe4 = 1;
      }
      else if (uVar5 != 2) break;
      cVar6 = 'I';
      PIECE(param_1,0,1) = 0x49;
      break;
    case 0x6d:
      if (uVar4 == 0) {
        DAT_1002bfe4 = 1;
      }
      else if (uVar5 != 2) break;
      cVar6 = 'M';
      PIECE(param_1,0,1) = 0x4d;
      break;
    case 0x73:
      if (uVar4 == 0) {
        DAT_1002bfe4 = 1;
      }
      else if (uVar5 != 2) break;
      cVar6 = 'S';
      PIECE(param_1,0,1) = 0x53;
      break;
    case 0x79:
      if (uVar4 == 1) {
        cVar6 = 'y';
        PIECE(param_1,0,1) = 0x79;
      }
      else if (uVar5 == 4) {
        cVar6 = 'Y';
        PIECE(param_1,0,1) = 0x59;
      }
    }
    if (cVar6 == '\0') {
      if ((PTR_DAT_10028950[(uint)*pbVar7 * 2 + 1] & 0x80) != 0) {
        **(byte **)pbVar2 = *pbVar7;
        *(int *)pbVar2 = *(int *)pbVar2 + 1;
        *param_4 = *param_4 + -1;
        pbVar7 = pbVar7 + 1;
      }
      **(byte **)pbVar2 = *pbVar7;
      param_3 = pbVar7 + 1;
      *(int *)pbVar2 = *(int *)pbVar2 + 1;
      *param_4 = *param_4 + -1;
    }
    else {
      _expandtime(PIECE(param_1,0,1),param_2,pbVar2,(uint *)param_4,param_5);
    }
LAB_10010d0c:
    bVar1 = *param_3;
    pbVar7 = param_3;
  } while( true );
}

/* ---- 0x10010f70  localtime ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl localtime(int *param_1)

{
  bool bVar1;
  int *piVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar3;
  int iVar4;
  
  piVar2 = param_1;
  if (*param_1 < 0) {
    return (int *)0x0;
  }
  __tzset();
  iVar3 = *piVar2;
  if ((iVar3 < 0x3f481) || (0x7ffc0b7e < iVar3)) {
    piVar2 = gmtime(piVar2);
    bVar1 = _isindst(piVar2);
    iVar3 = *piVar2;
    if (((uint)(bVar1)) != 0) {
      iVar3 = iVar3 - DAT_10028d70;
    }
    param_1 = (int *)(iVar3 - DAT_10028d68);
    iVar3 = (int)param_1 % 0x3c;
    *piVar2 = iVar3;
    if (iVar3 < 0) {
      *piVar2 = iVar3 + 0x3c;
      param_1 = param_1 + -0xf;
    }
    param_1 = (int *)((int)param_1 / 0x3c + piVar2[1]);
    iVar3 = (int)param_1 % 0x3c;
    piVar2[1] = iVar3;
    if (iVar3 < 0) {
      piVar2[1] = iVar3 + 0x3c;
      param_1 = param_1 + -0xf;
    }
    param_1 = (int *)((int)param_1 / 0x3c + piVar2[2]);
    iVar3 = (int)param_1 % 0x18;
    piVar2[2] = iVar3;
    if (iVar3 < 0) {
      piVar2[2] = iVar3 + 0x18;
      param_1 = param_1 + -6;
    }
    iVar3 = (int)param_1 / 0x18;
    if (0 < iVar3) {
      piVar2[6] = (iVar3 + piVar2[6]) % 7;
      piVar2[3] = piVar2[3] + iVar3;
      piVar2[7] = piVar2[7] + iVar3;
      return piVar2;
    }
    if (iVar3 < 0) {
      piVar2[6] = (iVar3 + 7 + piVar2[6]) % 7;
      iVar4 = piVar2[3] + iVar3;
      piVar2[3] = iVar4;
      if (iVar4 < 1) {
        piVar2[7] = 0x16c;
        piVar2[3] = iVar4 + 0x1f;
        piVar2[4] = 0xb;
        piVar2[5] = piVar2[5] + -1;
        return piVar2;
      }
      piVar2[7] = piVar2[7] + iVar3;
    }
  }
  else {
    param_1 = (int *)(iVar3 - DAT_10028d68);
    piVar2 = gmtime((int *)&param_1);
    if (DAT_10028d6c != 0) {
      bVar1 = _isindst(piVar2);
      if (((uint)(bVar1)) != 0) {
        param_1 = (int *)((int)param_1 - DAT_10028d70);
        piVar2 = gmtime((int *)&param_1);
        piVar2[8] = 1;
        return piVar2;
      }
    }
  }
  return piVar2;
}

/* ---- 0x10011160  time ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl time(int *param_1)

{
  unsigned char _frame[0xe0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define uStack_cc (*(undefined4 *)(_frame + (0xe0 - 0xcc)))
  #define uStack_c8 (*(undefined4 *)(_frame + (0xe0 - 0xc8)))
  #define uStack_c4 (*(undefined4 *)(_frame + (0xe0 - 0xc4)))
  #define uStack_c0 (*(undefined4 *)(_frame + (0xe0 - 0xc0)))
  #define local_bc (*(ushort *)(_frame + (0xe0 - 0xbc)))
  #define uStack_ba (*(ushort *)(_frame + (0xe0 - 0xba)))
  #define uStack_b6 (*(ushort *)(_frame + (0xe0 - 0xb6)))
  #define uStack_b4 (*(ushort *)(_frame + (0xe0 - 0xb4)))
  #define uStack_b2 (*(ushort *)(_frame + (0xe0 - 0xb2)))
  #define uStack_b0 (*(ushort *)(_frame + (0xe0 - 0xb0)))
  #define auStack_ac (*(undefined1 (*)[154])(_frame + (0xe0 - 0xac)))
  #define sStack_12 (*(short *)(_frame + (0xe0 - 0x12)))
  #define iStack_4 (*(int *)(_frame + (0xe0 - 0x4)))
  
  GetLocalTime((int)&local_bc);
  GetSystemTime((int)&uStack_cc);
  if (PIECE(uStack_c4,2,2) == DAT_1002bffa) {
    if ((short)uStack_c4 == DAT_1002bff8) {
      if (PIECE(uStack_c8,2,2) == DAT_1002bff6) {
        if (PIECE(uStack_cc,2,2) == DAT_1002bff2) {
          if ((short)uStack_cc == DAT_1002bff0) goto LAB_1001122f;
        }
      }
    }
  }
  iVar1 = GetTimeZoneInformation((int)auStack_ac);
  if (iVar1 == -1) {
    DAT_1002bfe8 = -1;
  }
  else if (((iVar1 == 2) && (sStack_12 != 0)) && (iStack_4 != 0)) {
    DAT_1002bfe8 = 1;
  }
  else {
    DAT_1002bfe8 = 0;
  }
  _DAT_1002bff0 = uStack_cc;
  _DAT_1002bff4 = uStack_c8;
  _DAT_1002bff8 = uStack_c4;
  _DAT_1002bffc = uStack_c0;
LAB_1001122f:
  iVar1 = __loctotime_t((uint)local_bc,(uint)uStack_ba,(uint)uStack_b6,(uint)uStack_b4,
                        (uint)uStack_b2,(uint)uStack_b0,DAT_1002bfe8);
  if (param_1 != (int *)0x0) {
    *param_1 = iVar1;
  }
  return;
}
#undef auStack_ac
#undef iStack_4
#undef local_bc
#undef sStack_12
#undef uStack_b0
#undef uStack_b2
#undef uStack_b4
#undef uStack_b6
#undef uStack_ba
#undef uStack_c0
#undef uStack_c4
#undef uStack_c8
#undef uStack_cc


/* ---- 0x10011290  setlocale ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

char * __cdecl setlocale(int param_1,uint *param_2)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  byte bVar2;
  bool bVar3;
  char *pcVar4;
  byte *pbVar5;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  uint *puVar10;
  undefined **ppuVar11;
  byte *pbVar12;
  undefined4 *puVar13;
  bool bVar14;
  #define iStack_90 (*(int *)(_frame + (0xa0 - 0x90)))
  #define iStack_88 (*(int *)(_frame + (0xa0 - 0x88)))
  #define uStack_84 (*(undefined4 *)(_frame + (0xa0 - 0x84)))
  
  iVar9 = 0;
  if ((param_1 < 0) || (5 < param_1)) {
    return (char *)0x0;
  }
  _lock(0x13);
  DAT_1002c70c = DAT_1002c70c + 1;
  while (DAT_1002c710 != 0) {
    Sleep(1);
  }
  if (param_1 != 0) {
    if (param_2 == (uint *)0x0) {
      pcVar4 = (&DAT_10028774)[param_1 * 3];
    }
    else {
      pcVar4 = (char *)_setlocale_set_cat(param_1,param_2);
    }
    goto LAB_10011529;
  }
  bVar3 = true;
  iStack_90 = 0;
  if (param_2 != (uint *)0x0) {
    if ((((char)*param_2 == 'L') && (*(char *)((int)param_2 + 1) == 'C')) &&
       (*(char *)((int)param_2 + 2) == '_')) {
      pbVar5 = strcmp((byte *)param_2,&DAT_10023dc8);
      while (((pbVar5 != (byte *)0x0 && (iVar9 = (int)pbVar5 - (int)param_2, iVar9 != 0)) &&
             (*pbVar5 != 0x3b))) {
        iStack_88 = 1;
        ppuVar11 = &PTR_DAT_1002877c;
        do {
          uVar6 = strncmp(*ppuVar11,(char *)param_2,iVar9);
          if (uVar6 == 0) {
            uVar6 = 0xffffffff;
            pcVar4 = *ppuVar11;
            do {
              if (uVar6 == 0) break;
              uVar6 = uVar6 - 1;
              cVar1 = *pcVar4;
              pcVar4 = pcVar4 + 1;
            } while (cVar1 != '\0');
            if (iVar9 == ~uVar6 - 1) break;
          }
          ppuVar11 = ppuVar11 + 3;
          iStack_88 = iStack_88 + 1;
        } while ((int)ppuVar11 < IMG_ADDR(0x100287ad));
        puVar10 = (uint *)(pbVar5 + 1);
        uVar6 = FUN_10017c10((byte *)puVar10,&DAT_10023dc4);
        if ((uVar6 == 0) && ((char)*puVar10 != ';')) break;
        if (iStack_88 < 6) {
          strncpy(&uStack_84,puVar10,uVar6);
          *(undefined1 *)((int)&uStack_84 + uVar6) = 0;
          iVar9 = _setlocale_set_cat(iStack_88,&uStack_84);
          if (iVar9 != 0) {
            iStack_90 = iStack_90 + 1;
          }
        }
        if ((*(char *)((int)puVar10 + uVar6) == '\0') ||
           (param_2 = (uint *)((int)puVar10 + uVar6 + 1),
           *(char *)((int)puVar10 + uVar6 + 1) == '\0')) goto LAB_10011516;
        pbVar5 = strcmp((byte *)param_2,&DAT_10023dc8);
      }
      _unlock(0x13);
      DAT_1002c70c = DAT_1002c70c + -1;
      return (char *)0x0;
    }
    pcVar7 = _expandlocale(param_2,(char *)&uStack_84,(undefined4 *)0x0,(uint *)0x0);
    pcVar4 = (char *)0x0;
    if (pcVar7 == (char *)0x0) goto LAB_10011529;
    puVar13 = &DAT_10028774;
    do {
      if ((undefined **)puVar13 != &DAT_10028774) {
        pbVar12 = (byte *)*puVar13;
        pbVar5 = (byte *)&uStack_84;
        do {
          bVar2 = *pbVar5;
          bVar14 = bVar2 < *pbVar12;
          if (bVar2 != *pbVar12) {
LAB_100114bb:
            iVar8 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
            goto LAB_100114c0;
          }
          if (bVar2 == 0) break;
          bVar2 = pbVar5[1];
          bVar14 = bVar2 < pbVar12[1];
          if (bVar2 != pbVar12[1]) goto LAB_100114bb;
          pbVar5 = pbVar5 + 2;
          pbVar12 = pbVar12 + 2;
        } while (bVar2 != 0);
        iVar8 = 0;
LAB_100114c0:
        if ((iVar8 == 0) || (iVar8 = _setlocale_set_cat(iVar9,&uStack_84), iVar8 != 0)) {
          iStack_90 = iStack_90 + 1;
        }
        else {
          bVar3 = false;
        }
      }
      puVar13 = puVar13 + 3;
      iVar9 = iVar9 + 1;
    } while ((int)puVar13 < IMG_ADDR(0x100287b1));
    if (bVar3) {
      pcVar4 = _setlocale_get_all();
      free(DAT_10028774);
      DAT_10028774 = (undefined *)0x0;
      goto LAB_10011529;
    }
LAB_10011516:
    if (iStack_90 == 0) {
      pcVar4 = (char *)0x0;
      goto LAB_10011529;
    }
  }
  pcVar4 = _setlocale_get_all();
LAB_10011529:
  _unlock(0x13);
  DAT_1002c70c = DAT_1002c70c + -1;
  return pcVar4;
}
#undef iStack_88
#undef iStack_90
#undef uStack_84


/* ---- 0x10011560  _setlocale_set_cat ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _setlocale_set_cat(int param_1,uint *param_2)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined4 uVar2;
  undefined *puVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  char *pcVar10;
  #define local_90 (*(uint *)(_frame + (0xa0 - 0x90)))
  #define local_8c (*(undefined2 *)(_frame + (0xa0 - 0x8c)))
  #define local_88 (*(uint *)(_frame + (0xa0 - 0x88)))
  #define local_84 (*(char (*)[132])(_frame + (0xa0 - 0x84)))
  
  pcVar4 = _expandlocale(param_2,local_84,&local_90,&local_88);
  if (pcVar4 == (char *)0x0) {
    return 0;
  }
  uVar6 = 0xffffffff;
  pcVar4 = local_84;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar4 = (char *)malloc(~uVar6);
  uVar6 = DAT_1002c218;
  if (pcVar4 == (char *)0x0) {
    return 0;
  }
  uVar2 = *(undefined4 *)(&DAT_1002c200 + param_1 * 4);
  puVar3 = (undefined *)(&DAT_10028774)[param_1 * 3];
  uVar7 = 0xffffffff;
  pcVar9 = local_84;
  do {
    pcVar10 = pcVar9;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar10 = pcVar9 + 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar10;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  pcVar9 = pcVar10 + -uVar7;
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
  (&DAT_10028774)[param_1 * 3] = pcVar4;
  *(uint *)(&DAT_1002c200 + param_1 * 4) = local_90 & 0xffff;
  *(uint *)(&DAT_1002c1d8 + param_1 * 6) = local_90;
  *(undefined2 *)(&DAT_1002c1dc + param_1 * 6) = local_8c;
  if (param_1 == 2) {
    DAT_1002c218 = local_88;
  }
  iVar5 = (**(code **)(&DAT_10028778 + param_1 * 0xc))();
  if (iVar5 != 0) {
    (&DAT_10028774)[param_1 * 3] = puVar3;
    free(pcVar4);
    *(undefined4 *)(&DAT_1002c200 + param_1 * 4) = uVar2;
    DAT_1002c218 = uVar6;
    return 0;
  }
  if (puVar3 != &DAT_10028768) {
    free(puVar3);
  }
  return (&DAT_10028774)[param_1 * 3];
}
#undef local_84
#undef local_88
#undef local_8c
#undef local_90


/* ---- 0x100116c0  _setlocale_get_all ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

char * _setlocale_get_all(void)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  byte *pbVar4;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  undefined **ppuVar9;
  byte *pbVar10;
  char *pcVar11;
  char *pcVar12;
  bool bVar13;
  
  bVar3 = true;
  if (DAT_10028774 == (char *)0x0) {
    DAT_10028774 = (char *)malloc(0x351);
  }
  *DAT_10028774 = '\0';
  FUN_100119f0(DAT_10028774,3);
  ppuVar9 = &PTR_DAT_10028780;
  do {
    uVar6 = 0xffffffff;
    pcVar5 = ";";
    do {
      pcVar12 = pcVar5;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar12 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar12;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    iVar7 = -1;
    pcVar5 = DAT_10028774;
    do {
      pcVar11 = pcVar5;
      if (iVar7 == 0) break;
      iVar7 = iVar7 + -1;
      pcVar11 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar11;
    } while (cVar1 != '\0');
    pcVar5 = pcVar12 + -uVar6;
    pcVar12 = pcVar11 + -1;
    for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar12 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar12 = pcVar12 + 1;
    }
    pbVar10 = ppuVar9[3];
    pbVar4 = *ppuVar9;
    do {
      bVar2 = *pbVar4;
      bVar13 = bVar2 < *pbVar10;
      if (bVar2 != *pbVar10) {
LAB_10011770:
        iVar7 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
        goto LAB_10011775;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar4[1];
      bVar13 = bVar2 < pbVar10[1];
      if (bVar2 != pbVar10[1]) goto LAB_10011770;
      pbVar4 = pbVar4 + 2;
      pbVar10 = pbVar10 + 2;
    } while (bVar2 != 0);
    iVar7 = 0;
LAB_10011775:
    if (iVar7 != 0) {
      bVar3 = false;
    }
    ppuVar9 = ppuVar9 + 3;
    FUN_100119f0(DAT_10028774,3);
    if (IMG_ADDR(0x100287af) < (int)ppuVar9) {
      pcVar5 = DAT_10028774;
      if (bVar3) {
        free(DAT_10028774);
        DAT_10028774 = (char *)0x0;
        pcVar5 = PTR_DAT_1002878c;
      }
      return pcVar5;
    }
  } while( true );
}

/* ---- 0x100117e0  _expandlocale ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

char * __cdecl _expandlocale(uint *param_1,char *param_2,undefined4 *param_3,uint *param_4)

{
  unsigned char _frame[0xa0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  char *pcVar9;
  bool bVar10;
  #define local_88 (*(uint (*)[34])(_frame + (0xa0 - 0x88)))
  
  if (param_1 == (uint *)0x0) {
    return (char *)0x0;
  }
  if (((char)*param_1 == 'C') && (*(char *)((int)param_1 + 1) == '\0')) {
    *param_2 = 'C';
    param_2[1] = '\0';
    if (param_3 != (undefined4 *)0x0) {
      *(undefined2 *)param_3 = 0;
      *(undefined2 *)((int)param_3 + 2) = 0;
      *(undefined2 *)(param_3 + 1) = 0;
    }
    pcVar5 = param_2;
    if (param_4 != (uint *)0x0) {
      *param_4 = 0;
      return param_2;
    }
  }
  else {
    pbVar3 = &DAT_10028840;
    puVar8 = param_1;
    do {
      bVar2 = *pbVar3;
      bVar10 = bVar2 < (byte)*puVar8;
      if (bVar2 != (byte)*puVar8) {
LAB_1001187d:
        iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
        goto LAB_10011882;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar3[1];
      bVar10 = bVar2 < *(byte *)((int)puVar8 + 1);
      if (bVar2 != *(byte *)((int)puVar8 + 1)) goto LAB_1001187d;
      pbVar3 = pbVar3 + 2;
      puVar8 = (uint *)((int)puVar8 + 2);
    } while (bVar2 != 0);
    iVar4 = 0;
LAB_10011882:
    if (iVar4 != 0) {
      pbVar3 = &DAT_100287b8;
      puVar8 = param_1;
      do {
        bVar2 = *pbVar3;
        bVar10 = bVar2 < (byte)*puVar8;
        if (bVar2 != (byte)*puVar8) {
LAB_100118b5:
          iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
          goto LAB_100118ba;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar3[1];
        bVar10 = bVar2 < *(byte *)((int)puVar8 + 1);
        if (bVar2 != *(byte *)((int)puVar8 + 1)) goto LAB_100118b5;
        pbVar3 = pbVar3 + 2;
        puVar8 = (uint *)((int)puVar8 + 2);
      } while (bVar2 != 0);
      iVar4 = 0;
LAB_100118ba:
      if (iVar4 != 0) {
        iVar4 = __lc_strtolc(local_88,param_1);
        if (iVar4 != 0) {
          return (char *)0x0;
        }
        iVar4 = __get_qualified_locale((char *)local_88,IMG_ADDR(0x1002c000),(int)local_88);
        if (iVar4 == 0) {
          return (char *)0x0;
        }
        DAT_1002c008 = _DAT_1002c004 & 0xffff;
        __lc_lctostr(&DAT_10028840,(char *)local_88);
        if ((char)*param_1 == '\0') {
          uVar6 = 0xffffffff;
          pcVar5 = &DAT_10028840;
          do {
            pcVar9 = pcVar5;
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            pcVar9 = pcVar5 + 1;
            cVar1 = *pcVar5;
            pcVar5 = pcVar9;
          } while (cVar1 != '\0');
          uVar6 = ~uVar6;
          pcVar5 = pcVar9 + -uVar6;
          pcVar9 = &DAT_100287b8;
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined4 *)pcVar9 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar9 = pcVar9 + 4;
          }
        }
        else {
          uVar6 = 0xffffffff;
          do {
            puVar8 = param_1;
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            puVar8 = (uint *)((int)param_1 + 1);
            uVar7 = *param_1;
            param_1 = puVar8;
          } while ((char)uVar7 != '\0');
          uVar6 = ~uVar6;
          pcVar5 = (char *)((int)puVar8 - uVar6);
          pcVar9 = &DAT_100287b8;
          for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined4 *)pcVar9 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            pcVar9 = pcVar9 + 4;
          }
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar9 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          pcVar9 = pcVar9 + 1;
        }
      }
    }
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = DAT_1002c000;
      *(undefined2 *)(param_3 + 1) = DAT_1002c004;
    }
    if (param_4 != (uint *)0x0) {
      *param_4 = DAT_1002c008;
    }
    uVar6 = 0xffffffff;
    pcVar5 = &DAT_10028840;
    do {
      pcVar9 = pcVar5;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar9 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar9;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar5 = &DAT_10028840;
    pcVar9 = pcVar9 + -uVar6;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)param_2 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      param_2 = param_2 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *param_2 = *pcVar9;
      pcVar9 = pcVar9 + 1;
      param_2 = param_2 + 1;
    }
  }
  return pcVar5;
}
#undef local_88


/* ---- 0x10011a40  __lc_strtolc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl __lc_strtolc(uint *param_1,uint *param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  char *pcVar6;
  char *pcVar7;
  uint *puVar8;
  
  puVar5 = param_1;
  for (iVar2 = 0x22; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  if ((char)*param_2 == '\0') {
    return 0;
  }
  if (((char)*param_2 != '.') || (*(char *)((int)param_2 + 1) == '\0')) {
    iVar2 = 0;
    uVar3 = FUN_10017c10((byte *)param_2,&DAT_10023dd0);
    if (uVar3 == 0) {
      return 0xffffffff;
    }
    do {
      cVar1 = *(char *)(uVar3 + (int)param_2);
      if (((iVar2 != 0) || (0x3f < (int)uVar3)) || (puVar5 = param_1, cVar1 == '.')) {
        if (((iVar2 == 1) && ((int)uVar3 < 0x40)) && (cVar1 != '_')) {
          puVar5 = param_1 + 0x10;
        }
        else {
          if (iVar2 != 2) {
            return 0xffffffff;
          }
          if ((cVar1 != '\0') && (cVar1 != ',')) {
            return 0xffffffff;
          }
          puVar5 = param_1 + 0x20;
        }
      }
      strncpy(puVar5,param_2,uVar3);
      if ((cVar1 == ',') || (cVar1 == '\0')) {
        return 0;
      }
      param_2 = (uint *)(uVar3 + 1 + (int)param_2);
      iVar2 = iVar2 + 1;
      uVar3 = FUN_10017c10((byte *)param_2,&DAT_10023dd0);
      if (uVar3 == 0) {
        return 0xffffffff;
      }
    } while( true );
  }
  uVar3 = 0xffffffff;
  pcVar6 = (char *)((int)param_2 + 1);
  do {
    pcVar7 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  puVar5 = (uint *)(pcVar7 + -uVar3);
  puVar8 = param_1 + 0x20;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar8 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar8 = puVar8 + 1;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(char *)puVar8 = (char)*puVar5;
    puVar5 = (uint *)((int)puVar5 + 1);
    puVar8 = (uint *)((int)puVar8 + 1);
  }
  return 0;
}

/* ---- 0x10011b50  __lc_lctostr ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __lc_lctostr(char *param_1,char *param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  uVar2 = 0xffffffff;
  pcVar4 = param_2;
  do {
    pcVar5 = pcVar4;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar5 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar5;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar5 + -uVar2;
  pcVar5 = param_1;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  if (param_2[0x40] != '\0') {
    FUN_100119f0(param_1,2);
  }
  if (param_2[0x80] != '\0') {
    FUN_100119f0(param_1,2);
  }
  return;
}

/* ---- 0x10011bc0  tolower ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl tolower(uint param_1)

{
  bool bVar1;
  
  if (DAT_1002c208 == 0) {
    if ((0x60 < (int)param_1) && ((int)param_1 < 0x7b)) {
      return param_1 - 0x20;
    }
  }
  else {
    InterlockedIncrement(IMG_ADDR(0x1002c710));
    bVar1 = DAT_1002c70c != 0;
    if (bVar1) {
      InterlockedDecrement(IMG_ADDR(0x1002c710));
      _lock(0x13);
    }
    param_1 = _tolower_lk(param_1);
    if (bVar1) {
      _unlock(0x13);
      return param_1;
    }
    InterlockedDecrement(IMG_ADDR(0x1002c710));
  }
  return param_1;
}

/* ---- 0x10011c50  _tolower_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _tolower_lk(uint param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  int iVar3;
  #define local_8 (*(uint (*)[2])(_frame + (0x20 - 0x8)))
  
  uVar1 = param_1;
  if (DAT_1002c208 == 0) {
    if ((0x60 < (int)param_1) && ((int)param_1 < 0x7b)) {
      return param_1 - 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if (DAT_10028b5c < 2) {
        uVar2 = (byte)PTR_DAT_10028950[param_1 * 2] & 2;
      }
      else {
        uVar2 = _isctype(param_1,2);
      }
      if (uVar2 == 0) {
        return uVar1;
      }
    }
    uVar2 = param_1;
    if ((PTR_DAT_10028950[((int)uVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      PIECE(param_1,0,2) = (ushort)(byte)uVar1;
      iVar3 = 1;
    }
    else {
      PIECE(param_1,0,2) = CONCAT11((byte)uVar1,(char)(uVar1 >> 8));
      PIECE(param_1,3,1) = SUB41(uVar2,3);
      PIECE(param_1,0,3) = (uint3)(ushort)param_1;
      iVar3 = 2;
    }
    iVar3 = __crtLCMapStringA(DAT_1002c208,0x200,(char *)&param_1,iVar3,local_8,3,0,1);
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


/* ---- 0x10011d50  _CIsqrt ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

float __cdecl _CIsqrt(void)

{
  float10 in_ST0;
  float10 fVar1;
  double dVar2;
  
  dVar2 = (double)in_ST0;
  FUN_10018ec8(SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
  fVar1 = (float10)((code *)_sqrt)(SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
  return (float)fVar1;
}
#endif


/* ---- 0x10011d6d  _sqrt ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _sqrt(int param_1,uint param_2)

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
LAB_10011dfc:
    if (DAT_1002bf88 == 0) {
      FUN_10018df7(&DAT_100288d0,0xe,in_FPUControlWord,unaff_retaddr,param_1,param_2);
      return;
    }
  }
  else {
    if (in_FPUControlWord != 0x27f) {
      in_EAX = FUN_10018e55();
      in_ST0 = extraout_ST0;
    }
    if (in_EAX < 0x3ff00000) {
      fpatan(in_ST0,SQRT(((float10)1 - in_ST0) * ((float10)1 + in_ST0)));
    }
    else if ((0x3ff00000 < in_EAX) || ((param_2 & 0xfffff) != 0 || param_1 != 0)) goto LAB_10011dfc;
    if (DAT_1002bf88 == 0) {
      FUN_10018eeb(&DAT_100288d0,0xe,unaff_retaddr,param_1,param_2);
      return;
    }
  }
  return;
}
#endif


/* ---- 0x10011ef0  floor ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure); floor/ceil pair, order not
   verified */

float __cdecl floor(uint param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  double dVar1;
  uint uVar2;
  int iVar3;
  float10 fVar4;
  float fVar5;
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  uVar2 = FUN_10019aa0();
  if ((PIECE(param_2,2,2) & 0x7ff0) != 0x7ff0) {
    fVar5 = _frnd((double)CONCAT44(param_2,param_1));
    dVar1 = (double)fVar5;
    if ((dVar1 != (double)CONCAT26(PIECE(param_2,2,2),CONCAT24((undefined2)param_2,param_1))) &&
       ((uVar2 & 0x20) == 0)) {
      uStack_4 = (undefined4)((ulonglong)dVar1 >> 0x20);
      local_8 = SUB84(dVar1,0);
      fVar4 = FUN_10019040(0x10,0xc,param_1,param_2,local_8,uStack_4,uVar2);
      return (float)fVar4;
    }
    FUN_10019aa0();
    return fVar5;
  }
  iVar3 = FUN_10019900(param_1,param_2);
  if (0 < iVar3) {
    if (iVar3 < 3) {
      FUN_10019aa0();
      return (float)(double)CONCAT26(PIECE(param_2,2,2),CONCAT24((undefined2)param_2,param_1));
    }
    if (iVar3 == 3) {
      fVar4 = FUN_10018ff0(0xc,param_1,param_2);
      return (float)fVar4;
    }
  }
  dVar1 = (double)CONCAT26(PIECE(param_2,2,2),CONCAT24((undefined2)param_2,param_1)) - -1.0;
  fVar4 = FUN_10019040(8,0xc,param_1,param_2,SUB84(dVar1,0),(int)((ulonglong)dVar1 >> 0x20),uVar2);
  return (float)fVar4;
}
#undef local_8
#undef uStack_4


/* ---- 0x10011ff0  ceil ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure); floor/ceil pair, order not
   verified */

float __cdecl ceil(uint param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  double dVar1;
  uint uVar2;
  int iVar3;
  float10 fVar4;
  float fVar5;
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  uVar2 = FUN_10019aa0();
  if ((PIECE(param_2,2,2) & 0x7ff0) != 0x7ff0) {
    fVar5 = _frnd((double)CONCAT44(param_2,param_1));
    dVar1 = (double)fVar5;
    if ((dVar1 != (double)CONCAT26(PIECE(param_2,2,2),CONCAT24((undefined2)param_2,param_1))) &&
       ((uVar2 & 0x20) == 0)) {
      uStack_4 = (undefined4)((ulonglong)dVar1 >> 0x20);
      local_8 = SUB84(dVar1,0);
      fVar4 = FUN_10019040(0x10,0xb,param_1,param_2,local_8,uStack_4,uVar2);
      return (float)fVar4;
    }
    FUN_10019aa0();
    return fVar5;
  }
  iVar3 = FUN_10019900(param_1,param_2);
  if (0 < iVar3) {
    if (iVar3 < 3) {
      FUN_10019aa0();
      return (float)(double)CONCAT26(PIECE(param_2,2,2),CONCAT24((undefined2)param_2,param_1));
    }
    if (iVar3 == 3) {
      fVar4 = FUN_10018ff0(0xb,param_1,param_2);
      return (float)fVar4;
    }
  }
  dVar1 = (double)CONCAT26(PIECE(param_2,2,2),CONCAT24((undefined2)param_2,param_1)) - -1.0;
  fVar4 = FUN_10019040(8,0xb,param_1,param_2,SUB84(dVar1,0),(int)((ulonglong)dVar1 >> 0x20),uVar2);
  return (float)fVar4;
}
#undef local_8
#undef uStack_4


/* ---- 0x10012130  _CIpow ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

float __cdecl _CIpow(void)

{
  float10 in_ST0;
  undefined1 auVar1 [10];
  float10 in_ST1;
  
  auVar1 = _pow(SUB84((double)in_ST1,0),(uint)((ulonglong)(double)in_ST1 >> 0x20),
                SUB84((double)in_ST0,0),(uint)((ulonglong)(double)in_ST0 >> 0x20));
  return (float)(float10)PUN(float,auVar1);
}
#endif


/* ---- 0x10012152  _pow ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Ghidra could not decompile this function: {"error":"Decompilation did not complete. Reason: \nLow-level Error: Overlapping input varnodes"} */
void FUN_10012152(void)

{
  __builtin_trap();
}
#endif


/* ---- 0x10012325  _ftol  (renamed _ftol_10012325: duplicate name) ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _ftol_10012325(void)

{
  undefined4 in_EAX;
  undefined2 uVar1;
  float10 in_ST0;
  float10 fVar2;
  float10 fVar3;
  
  fVar2 = ROUND(in_ST0);
  uVar1 = (undefined2)((uint)in_EAX >> 0x10);
  if ((fVar2 == in_ST0) != 0) {
    fVar2 = in_ST0 * (float10)_DAT_10028940;
    fVar3 = ROUND(fVar2);
    return CONCAT22(uVar1,(ushort)(fVar3 < fVar2) << 8 | (ushort)(ISNAN(fVar3) || ISNAN(fVar2)) << 10 |
                          (ushort)(fVar3 == fVar2) << 0xe);
  }
  return CONCAT22(uVar1,(ushort)(fVar2 < in_ST0) << 8 | (ushort)(ISNAN(fVar2) || ISNAN(in_ST0)) << 10 |
                        (ushort)(fVar2 == in_ST0) << 0xe);
}
#endif


/* ---- 0x10012390  bsearch ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl bsearch(undefined4 param_1,uint param_2,uint param_3,int param_4,undefined *param_5)

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
      iVar2 = (*(code *)param_5)(param_1,uVar5);
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
      iVar2 = (*(code *)param_5)(param_1,uVar4);
      return ~-(uint)(iVar2 != 0) & uVar4;
    }
  }
  return 0;
}

/* ---- 0x10012430  qsort ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl qsort(undefined1 *param_1,uint param_2,uint param_3,undefined *param_4)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  #define local_100 (*(undefined1 **)(_frame + (0x110 - 0x100)))
  #define local_fc (*(int **)(_frame + (0x110 - 0xfc)))
  #define local_f8 (*(undefined4 **)(_frame + (0x110 - 0xf8)))
  #define local_f4 (*(int *)(_frame + (0x110 - 0xf4)))
  #define local_f0 (*(int (*)[30])(_frame + (0x110 - 0xf0)))
  #define local_78 (*(undefined4 (*)[30])(_frame + (0x110 - 0x78)))
  
  if ((param_2 < 2) || (param_3 == 0)) {
    return;
  }
  local_100 = param_1 + (param_2 - 1) * param_3;
  local_fc = local_f0;
  local_f8 = local_78;
  local_f4 = 0;
LAB_10012484:
  uVar1 = (uint)((int)local_100 - (int)param_1) / param_3 + 1;
  if (8 < uVar1) {
    qsort_swap(param_1 + (uVar1 >> 1) * param_3,param_1,param_3);
    puVar4 = local_100 + param_3;
    puVar3 = param_1;
LAB_100124fe:
    puVar3 = puVar3 + param_3;
    if (puVar3 <= local_100) goto code_r0x10012508;
    goto LAB_10012518;
  }
  shortsort(param_1,local_100,param_3,param_4);
  goto LAB_100124a5;
code_r0x10012508:
  iVar2 = (*(code *)param_4)(puVar3,param_1);
  if (iVar2 < 1) goto LAB_100124fe;
LAB_10012518:
  do {
    puVar4 = puVar4 + -param_3;
    if (puVar4 <= param_1) break;
    iVar2 = (*(code *)param_4)(puVar4,param_1);
  } while (-1 < iVar2);
  if (puVar3 <= puVar4) {
    qsort_swap(puVar3,puVar4,param_3);
    goto LAB_100124fe;
  }
  qsort_swap(param_1,puVar4,param_3);
  if ((int)(puVar4 + (-1 - (int)param_1)) < (int)local_100 - (int)puVar3) {
    if (puVar3 < local_100) {
      *local_f8 = puVar3;
      *local_fc = (int)local_100;
      local_f4 = local_f4 + 1;
      local_f8 = local_f8 + 1;
      local_fc = local_fc + 1;
    }
    if (param_1 + param_3 < puVar4) {
      local_100 = puVar4 + -param_3;
      goto LAB_10012484;
    }
  }
  else {
    if (param_1 + param_3 < puVar4) {
      *local_f8 = param_1;
      *local_fc = (int)puVar4 - param_3;
      local_f4 = local_f4 + 1;
      local_f8 = local_f8 + 1;
      local_fc = local_fc + 1;
    }
    param_1 = puVar3;
    if (puVar3 < local_100) goto LAB_10012484;
  }
LAB_100124a5:
  local_f4 = local_f4 + -1;
  local_f8 = local_f8 + -1;
  local_fc = local_fc + -1;
  if (local_f4 < 0) {
    return;
  }
  local_100 = (undefined1 *)*local_fc;
  param_1 = (undefined1 *)*local_f8;
  goto LAB_10012484;
}
#undef local_100
#undef local_78
#undef local_f0
#undef local_f4
#undef local_f8
#undef local_fc


/* ---- 0x100125e0  shortsort ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl shortsort(undefined1 *param_1,undefined1 *param_2,int param_3,undefined *param_4)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  
  for (; puVar2 = param_1, puVar1 = param_1, param_1 < param_2; param_2 = param_2 + -param_3) {
    while (puVar1 = puVar1 + param_3, puVar1 <= param_2) {
      iVar3 = (*(code *)param_4)(puVar1,puVar2);
      if (0 < iVar3) {
        puVar2 = puVar1;
      }
    }
    qsort_swap(puVar2,param_2,param_3);
  }
  return;
}

/* ---- 0x10012640  qsort_swap ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl qsort_swap(undefined1 *param_1,undefined1 *param_2,int param_3)

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

/* ---- 0x10012670  strncpy ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint * __cdecl strncpy(uint *param_1,uint *param_2,uint param_3)

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
        goto joined_r0x100126ae;
      }
    }
    do {
      if (((uint)puVar5 & 3) == 0) {
        uVar4 = param_3 >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_100126eb;
        goto LAB_10012759;
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
joined_r0x10012755:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_10012759:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          param_3 = param_3 & 3;
          if (param_3 != 0) goto LAB_100126eb;
          return param_1;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x10012755;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x10012755;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x10012755;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x100126ae:
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
LAB_100126eb:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      return param_1;
    }
    param_3 = param_3 - 1;
  } while (param_3 != 0);
  return param_1;
}

/* ---- 0x10012770  toupper ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl toupper(uint param_1)

{
  bool bVar1;
  
  if (DAT_1002c208 == 0) {
    if ((0x40 < (int)param_1) && ((int)param_1 < 0x5b)) {
      return param_1 + 0x20;
    }
  }
  else {
    InterlockedIncrement(IMG_ADDR(0x1002c710));
    bVar1 = DAT_1002c70c != 0;
    if (bVar1) {
      InterlockedDecrement(IMG_ADDR(0x1002c710));
      _lock(0x13);
    }
    param_1 = _toupper_lk(param_1);
    if (bVar1) {
      _unlock(0x13);
      return param_1;
    }
    InterlockedDecrement(IMG_ADDR(0x1002c710));
  }
  return param_1;
}

/* ---- 0x10012800  _toupper_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _toupper_lk(uint param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  int iVar3;
  #define local_8 (*(uint (*)[2])(_frame + (0x20 - 0x8)))
  
  uVar1 = param_1;
  if (DAT_1002c208 == 0) {
    if ((0x40 < (int)param_1) && ((int)param_1 < 0x5b)) {
      return param_1 + 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if (DAT_10028b5c < 2) {
        uVar2 = (byte)PTR_DAT_10028950[param_1 * 2] & 1;
      }
      else {
        uVar2 = _isctype(param_1,1);
      }
      if (uVar2 == 0) {
        return uVar1;
      }
    }
    uVar2 = param_1;
    if ((PTR_DAT_10028950[((int)uVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      PIECE(param_1,0,2) = (ushort)(byte)uVar1;
      iVar3 = 1;
    }
    else {
      PIECE(param_1,0,2) = CONCAT11((byte)uVar1,(char)(uVar1 >> 8));
      PIECE(param_1,3,1) = SUB41(uVar2,3);
      PIECE(param_1,0,3) = (uint3)(ushort)param_1;
      iVar3 = 2;
    }
    iVar3 = __crtLCMapStringA(DAT_1002c208,0x100,(char *)&param_1,iVar3,local_8,3,0,1);
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


/* ---- 0x10012900  _isctype ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _isctype(int param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar2 = param_1;
  if (param_1 + 1U < 0x101) {
    return *(ushort *)(PTR_DAT_10028950 + param_1 * 2) & param_2;
  }
  if ((PTR_DAT_10028950[(param_1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
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


/* ---- 0x10012a20  strcmp ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

byte * __cdecl strcmp(byte *param_1,byte *param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte *pbVar2;
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
  do {
    pbVar2 = param_1;
    bVar1 = *pbVar2;
    if (bVar1 == 0) {
      return (byte *)0x0;
    }
    param_1 = pbVar2 + 1;
  } while ((abStack_28[(int)(uint)bVar1 >> 3] >> (bVar1 & 7) & 1) == 0);
  return pbVar2;
}
#undef abStack_28


/* ---- 0x10012a60  strncmp ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl strncmp(char *param_1,char *param_2,int param_3)

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
    iVar3 = param_3 - iVar3;
    do {
      pcVar5 = param_2;
      pcVar6 = param_1;
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
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

/* ---- 0x10012aa0  sscanf ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl sscanf(char *str,char *fmt,...)

{
  unsigned char _frame[0x30];  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  #define local_20 (*(char **)(_frame + (0x30 - 0x20)))
  #define local_1c (*(int *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(char **)(_frame + (0x30 - 0x18)))
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  
  uVar3 = 0xffffffff;
  local_18 = str;
  local_20 = str;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *str;
    str = str + 1;
  } while (cVar1 != '\0');
  local_1c = ~uVar3 - 1;
  local_14 = 0x49;
  iVar2 = _input((int *)&local_20,(byte *)fmt,(undefined4 *)&STACK0X(0x0000000c));
  return iVar2;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20


/* ---- 0x10012af0  strcoll ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl strcoll(byte *param_1,byte *param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int iVar2;
  int *piVar3;
  bool bVar4;
  #define local_10 (*(short (*)[8])(_frame + (0x20 - 0x10)))
  
  if (DAT_1002c204 == 0) {
    while( true ) {
      bVar1 = *param_1;
      bVar4 = bVar1 < *param_2;
      if (bVar1 != *param_2) break;
      if (bVar1 == 0) {
        return 0;
      }
      bVar1 = param_1[1];
      bVar4 = bVar1 < param_2[1];
      if (bVar1 != param_2[1]) break;
      param_1 = param_1 + 2;
      param_2 = param_2 + 2;
      if (bVar1 == 0) {
        return 0;
      }
    }
  }
  else {
    InterlockedIncrement(IMG_ADDR(0x1002c710));
    bVar4 = DAT_1002c70c == 0;
    if (!bVar4) {
      InterlockedDecrement(IMG_ADDR(0x1002c710));
      _lock(0x13);
    }
    if (DAT_1002c204 != 0) {
      iVar2 = __crtGetLocaleInfoA(DAT_1002c204,0xb,(int)local_10,8,0);
      if (iVar2 == 0) {
        if (!bVar4) {
          _unlock(0x13);
          return 0x7fffffff;
        }
        InterlockedDecrement(IMG_ADDR(0x1002c710));
        return 0x7fffffff;
      }
      iVar2 = wcstol(local_10,(undefined4 *)0x0,10);
      iVar2 = __crtCompareStringA(DAT_1002c204,0x1000,param_1,-1,param_2,-1,iVar2);
      if (iVar2 == 0) {
        if (bVar4) {
          InterlockedDecrement(IMG_ADDR(0x1002c710));
        }
        else {
          _unlock(0x13);
        }
        piVar3 = _errno();
        *piVar3 = 0x16;
        return 0x7fffffff;
      }
      if (!bVar4) {
        _unlock(0x13);
        return iVar2 + -2;
      }
      InterlockedDecrement(IMG_ADDR(0x1002c710));
      return iVar2 + -2;
    }
    if (bVar4) {
      InterlockedDecrement(IMG_ADDR(0x1002c710));
    }
    else {
      _unlock(0x13);
    }
    while( true ) {
      bVar1 = *param_1;
      bVar4 = bVar1 < *param_2;
      if (bVar1 != *param_2) break;
      if (bVar1 == 0) {
        return 0;
      }
      bVar1 = param_1[1];
      bVar4 = bVar1 < param_2[1];
      if (bVar1 != param_2[1]) break;
      param_1 = param_1 + 2;
      param_2 = param_2 + 2;
      if (bVar1 == 0) {
        return 0;
      }
    }
  }
  return (1 - (uint)bVar4) - (uint)(bVar4 != 0);
}
#undef local_10


/* ---- 0x10012cb0  _CRT_INIT ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) (DLL entry work: heap, mt, io,
   locale) */

undefined4 __stdcall _CRT_INIT(int a1,int a2,int a3)

{
  int iVar1;
  
  if (a2 != 1) {
    if (a2 != 0) {
      if (a2 == 3) {
        _freeptd((undefined *)0x0);
      }
      return 1;
    }
    if (0 < DAT_1002c00c) {
      DAT_1002c00c = DAT_1002c00c + -1;
      if (DAT_1002c0c4 == 0) {
        _cexit();
      }
      _ioterm();
      _mtterm();
      _heap_term();
      return 1;
    }
    return 0;
  }
  DAT_1002c08c = GetVersion();
  iVar1 = _heap_init();
  if (iVar1 == 0) {
    return 0;
  }
  _DAT_1002c098 = DAT_1002c08c >> 8 & 0xff;
  _DAT_1002c094 = DAT_1002c08c & 0xff;
  _DAT_1002c090 = _DAT_1002c094 * 0x100 + _DAT_1002c098;
  DAT_1002c08c = DAT_1002c08c >> 0x10;
  iVar1 = _mtinit();
  if (iVar1 == 0) {
    _heap_term();
    return 0;
  }
  DAT_1002c704 = GetCommandLineA();
  DAT_1002c010 = __crtGetEnvironmentStringsA();
  if ((DAT_1002c704 != 0) && (DAT_1002c010 != (char *)0x0)) {
    _ioinit();
    __initmbctable();
    _setargv();
    _setenvp();
    _cinit();
    DAT_1002c00c = DAT_1002c00c + 1;
    return 1;
  }
  _mtterm();
  _heap_term();
  return 0;
}

/* ---- 0x10012dd0  entry ---- */
undefined4 __stdcall entry(int a1,int a2,int a3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 1;
  if ((a2 == 0) && (DAT_1002c00c == 0)) {
    return 0;
  }
  if ((a2 != 1) && (a2 != 2)) {
LAB_10012e2e:
    iVar1 = FUN_1001d2f0(a1,a2,a3);
    if ((a2 == 1) && (iVar1 == 0)) {
      _CRT_INIT(a1,0,a3);
    }
    if ((a2 == 0) || (a2 == 3)) {
      iVar2 = _CRT_INIT(a1,a2,a3);
      if (iVar2 == 0) {
        iVar1 = 0;
      }
      if ((iVar1 != 0) && (DAT_1002c708 != (code *)0x0)) {
        iVar1 = (*DAT_1002c708)(a1,a2,a3);
      }
    }
    return iVar1;
  }
  if (DAT_1002c708 != (code *)0x0) {
    iVar1 = (*DAT_1002c708)(a1,a2,a3);
  }
  if (iVar1 != 0) {
    iVar1 = _CRT_INIT(a1,a2,a3);
    if (iVar1 != 0) goto LAB_10012e2e;
  }
  return 0;
}

/* ---- 0x10012e80  _amsg_exit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _amsg_exit(int param_1)

{
  if ((DAT_1002c018 == 1) || ((DAT_1002c018 == 0 && (DAT_1002c01c == 1)))) {
    _FF_MSGBANNER();
  }
  _NMSG_WRITE(param_1);
  (*(code *)PTR_exit_10028b70)(0xff);
  return;
}

/* ---- 0x100130b0  _cftoe ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined1 * __cdecl _cftoe(undefined4 *param_1,undefined1 *param_2,int param_3,int param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_28 (*(int (*)[4])(_frame + (0x40 - 0x28)))
  #define local_18 (*(char (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_1001dc70(*param_1,param_1[1],local_28,local_18);
  _fptostr(param_2 + (uint)(local_28[0] == 0x2d) + (uint)(0 < param_3),param_3 + 1,(int)local_28);
  _cftoe2(param_2,param_3,param_4,local_28,'\0');
  return param_2;
}
#undef local_18
#undef local_28


/* ---- 0x10013130  _cftoe2 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined1 * __cdecl _cftoe2(undefined1 *param_1,int param_2,int param_3,int *param_4,char param_5)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (param_5 != '\0') {
    _shift(param_1 + (*param_4 == 0x2d),(uint)(0 < param_2));
  }
  puVar1 = param_1;
  if (*param_4 == 0x2d) {
    *param_1 = 0x2d;
    puVar1 = param_1 + 1;
  }
  if (0 < param_2) {
    *puVar1 = puVar1[1];
    puVar1 = puVar1 + 1;
    *puVar1 = DAT_10028b60;
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

/* ---- 0x10013230  _cftof ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

char * __cdecl _cftof(undefined4 *param_1,char *param_2,uint param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define local_18 (*(char (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_1001dc70(*param_1,param_1[1],&local_28,local_18);
  _fptostr(param_2 + (local_28 == 0x2d),local_24 + param_3,(int)&local_28);
  _cftof2(param_2,param_3,&local_28,'\0');
  return param_2;
}
#undef local_18
#undef local_24
#undef local_28


/* ---- 0x100132a0  _cftof2 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

char * __cdecl _cftof2(char *param_1,uint param_2,int *param_3,char param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  
  iVar1 = param_3[1];
  uVar3 = iVar1 - 1;
  if ((param_4 != '\0') && (iVar2 = *param_3, uVar3 == param_2)) {
    param_1[uVar3 + (iVar2 == 0x2d)] = '0';
    param_1[iVar1 + (uint)(iVar2 == 0x2d)] = '\0';
  }
  pcVar4 = param_1;
  if (*param_3 == 0x2d) {
    *param_1 = '-';
    pcVar4 = param_1 + 1;
  }
  if (param_3[1] < 1) {
    _shift(pcVar4,1);
    *pcVar4 = '0';
    pcVar4 = pcVar4 + 1;
  }
  else {
    pcVar4 = pcVar4 + param_3[1];
  }
  if (0 < (int)param_2) {
    _shift(pcVar4,1);
    *pcVar4 = DAT_10028b60;
    iVar1 = param_3[1];
    if (iVar1 < 0) {
      if ((param_4 != '\0') || (-iVar1 <= (int)param_2)) {
        param_2 = -iVar1;
      }
      _shift(pcVar4 + 1,param_2);
      uVar3 = param_2 >> 2;
      pcVar4 = pcVar4 + 1;
      while (uVar3 != 0) {
        uVar3 = uVar3 - 1;
        builtin_strncpy(pcVar4,"0000",4);
        pcVar4 = pcVar4 + 4;
      }
      for (uVar3 = param_2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar4 = '0';
        pcVar4 = pcVar4 + 1;
      }
    }
  }
  return param_1;
}

/* ---- 0x10013360  _cftog ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _cftog(undefined4 *param_1,char *param_2,uint param_3,int param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  char cVar2;
  char *pcVar3;
  #define local_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define local_18 (*(char (*)[24])(_frame + (0x40 - 0x18)))
  
  FUN_1001dc70(*param_1,param_1[1],&local_28,local_18);
  iVar1 = local_24 + -1;
  pcVar3 = param_2 + (local_28 == 0x2d);
  _fptostr(pcVar3,param_3,(int)&local_28);
  local_24 = local_24 + -1;
  if ((-5 < local_24) && (local_24 < (int)param_3)) {
    if (iVar1 < local_24) {
      cVar2 = *pcVar3;
      while (cVar2 != '\0') {
        cVar2 = pcVar3[1];
        pcVar3 = pcVar3 + 1;
      }
      pcVar3[-1] = '\0';
    }
    _cftof2(param_2,param_3,&local_28,'\x01');
    return;
  }
  _cftoe2(param_2,param_3,param_4,&local_28,'\x01');
  return;
}
#undef local_18
#undef local_24
#undef local_28


/* ---- 0x10013490  _shift ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _shift(char *param_1,int param_2)

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
    memcpy((undefined4 *)(param_1 + param_2),(undefined4 *)param_1,~uVar2);
  }
  return;
}

/* ---- 0x100134c0  __InternalCxxFrameHandler ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl
__InternalCxxFrameHandler
          (int *param_1,int param_2,int param_3,undefined4 param_4,int *param_5,int param_6,
          int param_7,char param_8)

{
  undefined4 uVar1;
  
  if (*param_5 != 0x19930520) {
    FUN_100141b0();
  }
  if ((*(byte *)(param_1 + 1) & 0x66) == 0) {
    if (param_5[3] != 0) {
      if (((*param_1 == -0x1f928c9d) && (0x19930520 < (uint)param_1[5])) &&
         (*(code **)(param_1[7] + 8) != (code *)0x0)) {
        uVar1 = (**(code **)(param_1[7] + 8))
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        return uVar1;
      }
      FindHandler(param_1,param_2,param_3,param_4,(int)param_5,param_8,param_6,param_7);
    }
  }
  else if ((param_5[1] != 0) && (param_6 == 0)) {
    FrameUnwindToState(param_2,param_4,(int)param_5,-1);
    return 1;
  }
  return 1;
}

/* ---- 0x10013590  FindHandler ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl
FindHandler(int *param_1,int param_2,int param_3,undefined4 param_4,int param_5,char param_6,
           int param_7,int param_8)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  bool bVar2;
  int *piVar3;
  undefined3 extraout_var;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_1c (*(int **)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(int *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(int *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(int *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(int **)(_frame + (0x30 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x30 - 0x4)))
  
  iVar6 = *(int *)(param_2 + 8);
  local_10 = iVar6;
  if ((iVar6 < -1) || (*(int *)(param_5 + 4) <= iVar6)) {
    FUN_100141b0();
  }
  if (*param_1 == -0x1f928c9d) {
    if (((param_1[4] == 3) && (param_1[5] == 0x19930520)) && (param_1[7] == 0)) {
      piVar3 = _getptd();
      if (piVar3[0x1b] == 0) {
        return;
      }
      piVar3 = _getptd();
      param_1 = (int *)piVar3[0x1b];
      piVar3 = _getptd();
      param_3 = piVar3[0x1c];
      bVar2 = _ValidateRead(param_1,1);
      if (((uint)(bVar2)) == 0) {
        FUN_100141b0();
      }
      if (*param_1 != -0x1f928c9d) goto LAB_10013806;
      if (((param_1[4] == 3) && (param_1[5] == 0x19930520)) && (param_1[7] == 0)) {
        FUN_100141b0();
      }
    }
    if (((*param_1 == -0x1f928c9d) && (param_1[4] == 3)) && (param_1[5] == 0x19930520)) {
      local_1c = (int *)FUN_1000f310(param_5,param_7,iVar6,&local_20,&local_c);
      if (local_20 < local_c) {
        do {
          if ((*local_1c <= iVar6) && (iVar6 <= local_1c[1])) {
            local_14 = local_1c[3];
            pbVar8 = (byte *)local_1c[4];
            if (0 < local_14) {
              local_8 = *(int **)(param_1[7] + 0xc) + 1;
              local_4 = **(int **)(param_1[7] + 0xc);
              do {
                local_18 = local_4;
                if (0 < local_4) {
                  iVar6 = *(int *)(pbVar8 + 4);
                  piVar3 = local_8;
                  do {
                    if ((iVar6 == 0) || (pbVar4 = (byte *)(iVar6 + 8), *(char *)(iVar6 + 8) == '\0')
                       ) {
LAB_1001375f:
                      bVar2 = true;
                    }
                    else {
                      iVar5 = *(int *)((byte *)*piVar3 + 4);
                      if (iVar6 == iVar5) {
LAB_1001373a:
                        if (((((*(byte *)*piVar3 & 2) == 0) || ((*pbVar8 & 8) != 0)) &&
                            (((*(uint *)param_1[7] & 1) == 0 || ((*pbVar8 & 1) != 0)))) &&
                           (((*(uint *)param_1[7] & 2) == 0 || ((*pbVar8 & 2) != 0))))
                        goto LAB_1001375f;
                        bVar2 = false;
                      }
                      else {
                        pbVar7 = (byte *)(iVar5 + 8);
                        do {
                          bVar1 = *pbVar4;
                          bVar2 = bVar1 < *pbVar7;
                          if (bVar1 != *pbVar7) {
LAB_1001371d:
                            iVar5 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
                            goto LAB_10013722;
                          }
                          if (bVar1 == 0) break;
                          bVar1 = pbVar4[1];
                          bVar2 = bVar1 < pbVar7[1];
                          if (bVar1 != pbVar7[1]) goto LAB_1001371d;
                          pbVar4 = pbVar4 + 2;
                          pbVar7 = pbVar7 + 2;
                        } while (bVar1 != 0);
                        iVar5 = 0;
LAB_10013722:
                        if (iVar5 == 0) goto LAB_1001373a;
                        bVar2 = false;
                      }
                    }
                    if (bVar2) {
                      CatchIt((int)param_1,param_2,param_3,param_4,param_5,pbVar8,(byte *)*piVar3,
                              local_1c,param_7,param_8);
                      iVar6 = local_10;
                      goto LAB_100137cf;
                    }
                    piVar3 = piVar3 + 1;
                    local_18 = local_18 + -1;
                  } while (0 < local_18);
                }
                local_14 = local_14 + -1;
                pbVar8 = pbVar8 + 0x10;
                iVar6 = local_10;
              } while (0 < local_14);
            }
          }
LAB_100137cf:
          local_20 = local_20 + 1;
          local_1c = local_1c + 5;
        } while (local_20 < local_c);
      }
      if (param_6 == '\0') {
        return;
      }
      FUN_10013e40((int)param_1);
      return;
    }
  }
LAB_10013806:
  if (param_6 != '\0') {
    terminate();
    return;
  }
  Eh_FindForeignHandler(param_1,param_2,param_3,param_4,param_5,iVar6,param_7,param_8);
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x10013850  Eh_FindForeignHandler ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl
Eh_FindForeignHandler
          (undefined4 *param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6,
          int param_7,int param_8)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int iVar3;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  piVar1 = _getptd();
  if ((piVar1[0x1a] != 0) &&
     (iVar2 = FUN_1000f1b0(param_1,param_2,param_3,param_4,param_5,param_7,param_8), iVar2 != 0)) {
    return;
  }
  piVar1 = (int *)FUN_1000f310(param_5,param_7,param_6,&local_8,&local_4);
  if (local_8 < local_4) {
    do {
      if ((*piVar1 <= param_6) && (param_6 <= piVar1[1])) {
        iVar3 = piVar1[4] + piVar1[3] * 0x10;
        iVar2 = *(int *)(iVar3 + -0xc);
        if ((iVar2 == 0) || (*(char *)(iVar2 + 8) == '\0')) {
          CatchIt((int)param_1,param_2,param_3,param_4,param_5,(byte *)(iVar3 + -0x10),(byte *)0x0,
                  piVar1,param_7,param_8);
        }
      }
      local_8 = local_8 + 1;
      piVar1 = piVar1 + 5;
    } while (local_8 < local_4);
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x10013930  FrameUnwindToState ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl FrameUnwindToState(int param_1,undefined4 param_2,int param_3,int param_4)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int a1;
  int iVar1;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_10023e28;
  puStack_10 = &LAB_1001dec8;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  for (iVar1 = *(int *)(param_1 + 8); local_8 = 0xffffffff, iVar1 != param_4;
      iVar1 = *(int *)(*(int *)(param_3 + 8) + iVar1 * 8)) {
    if ((iVar1 < 0) || (*(int *)(param_3 + 4) <= iVar1)) {
      FUN_100141b0();
    }
    local_8 = 0;
    a1 = *(int *)(*(int *)(param_3 + 8) + 4 + iVar1 * 8);
    if (a1 != 0) {
      FUN_10013ef0(a1,param_1,0x103);
    }
  }
  *(int *)(param_1 + 8) = iVar1;
  *unaff_FS_OFFSET = local_14;
  return;
}
#undef local_14
#undef local_8
#undef puStack_10
#undef puStack_c


/* ---- 0x10013a10  CatchIt ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl
CatchIt(int param_1,int param_2,int param_3,undefined4 param_4,int param_5,byte *param_6,
       byte *param_7,int *param_8,int param_9,int param_10)

{
  undefined *UNRECOVERED_JUMPTABLE;
  
  if (param_7 != (byte *)0x0) {
    BuildCatchObject(param_1,param_2,param_6,param_7);
  }
  if (param_10 == 0) {
    param_10 = param_2;
  }
  _UnwindNestedFrames(param_10,param_1);
  FrameUnwindToState(param_2,param_4,param_5,*param_8);
  *(int *)(param_2 + 8) = param_8[1] + 1;
  UNRECOVERED_JUMPTABLE =
       (undefined *)
       CallCatchBlock(param_1,param_2,param_3,param_5,*(undefined4 *)(param_6 + 0xc),param_9,0x100);
  if (UNRECOVERED_JUMPTABLE != (undefined *)0x0) {
    _CallSettingFrame(UNRECOVERED_JUMPTABLE);
  }
  return;
}

/* ---- 0x10013aa0  CallCatchBlock ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl
CallCatchBlock(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5,
              int param_6,int param_7)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_10023e38;
  puStack_10 = &LAB_1001dec8;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  _getptd();
  _getptd();
  piVar1 = _getptd();
  piVar1[0x1b] = param_1;
  piVar1 = _getptd();
  piVar1[0x1c] = param_3;
  local_8 = 1;
  uVar2 = FUN_1000f120(param_2,param_4,param_5,param_6,param_7);
  local_8 = 0xffffffff;
  Eh_CallCatchBlockInner();
  *unaff_FS_OFFSET = local_14;
  return uVar2;
}
#undef local_14
#undef local_8
#undef puStack_10
#undef puStack_c


/* ---- 0x10013b98  Eh_CallCatchBlockInner ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void Eh_CallCatchBlockInner(void)

{
  int *piVar1;
  int unaff_EBX;
  int unaff_EBP;
  int unaff_ESI;
  int *unaff_EDI;
  
  *(undefined4 *)(unaff_ESI + -4) = *(undefined4 *)(unaff_EBP + -0x28);
  piVar1 = _getptd();
  piVar1[0x1b] = *(int *)(unaff_EBP + -0x1c);
  piVar1 = _getptd();
  piVar1[0x1c] = *(int *)(unaff_EBP + -0x20);
  if ((((*unaff_EDI == -0x1f928c9d) && (unaff_EDI[4] == 3)) && (unaff_EDI[5] == 0x19930520)) &&
     ((*(int *)(unaff_EBP + -0x24) == 0 && (unaff_EBX != 0)))) {
    _unwind_handler();
    FUN_10013e40((int)unaff_EDI);
  }
  return;
}
#endif


/* ---- 0x10013c30  BuildCatchObject ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl BuildCatchObject(int param_1,int param_2,byte *param_3,byte *param_4)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  bool bVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar3;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined4 *puVar4;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  uint uVar5;
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_10023e50;
  puStack_10 = &LAB_1001dec8;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  if (((*(int *)(param_3 + 4) != 0) && (*(char *)(*(int *)(param_3 + 4) + 8) != '\0')) &&
     (*(int *)(param_3 + 8) != 0)) {
    piVar1 = (int *)(param_2 + 0xc + *(int *)(param_3 + 8));
    local_8 = 0;
    if ((*param_3 & 8) == 0) {
      if ((*param_4 & 1) == 0) {
        if (*(int *)(param_4 + 0x18) == 0) {
          bVar2 = _ValidateRead(*(undefined4 *)(param_1 + 0x18),1);
          if ((((uint)(bVar2)) != 0) &&
             (bVar2 = _ValidateWrite(piVar1,1), ((uint)(bVar2)) != 0)) {
            uVar5 = *(uint *)(param_4 + 0x14);
            puVar4 = (undefined4 *)FUN_10013ec0(*(int *)(param_1 + 0x18),(int *)(param_4 + 8));
            memcpy(piVar1,puVar4,uVar5);
            goto LAB_10013e20;
          }
        }
        else {
          bVar2 = _ValidateRead(*(undefined4 *)(param_1 + 0x18),1);
          if (((((uint)(bVar2)) != 0) &&
              (bVar2 = _ValidateWrite(piVar1,1), ((uint)(bVar2)) != 0)) &&
             (bVar2 = _ValidateExecute(*(undefined4 *)(param_4 + 0x18)),
             ((uint)(bVar2)) != 0)) {
            if ((*param_4 & 4) == 0) {
              FUN_10013ec0(*(int *)(param_1 + 0x18),(int *)(param_4 + 8));
              FUN_1000f070(piVar1,*(undefined **)(param_4 + 0x18));
            }
            else {
              FUN_10013ec0(*(int *)(param_1 + 0x18),(int *)(param_4 + 8));
              FUN_1000f070(piVar1,*(undefined **)(param_4 + 0x18));
            }
            goto LAB_10013e20;
          }
        }
      }
      else {
        bVar2 = _ValidateRead(*(undefined4 *)(param_1 + 0x18),1);
        if ((((uint)(bVar2)) != 0) &&
           (bVar2 = _ValidateWrite(piVar1,1), ((uint)(bVar2)) != 0)) {
          memcpy(piVar1,*(undefined4 **)(param_1 + 0x18),*(uint *)(param_4 + 0x14));
          if ((*(int *)(param_4 + 0x14) == 4) && (*piVar1 != 0)) {
            iVar3 = FUN_10013ec0(*piVar1,(int *)(param_4 + 8));
            *piVar1 = iVar3;
          }
          goto LAB_10013e20;
        }
      }
    }
    else {
      bVar2 = _ValidateRead(*(undefined4 *)(param_1 + 0x18),1);
      if ((((uint)(bVar2)) != 0) &&
         (bVar2 = _ValidateWrite(piVar1,1), ((uint)(bVar2)) != 0)) {
        iVar3 = *(int *)(param_1 + 0x18);
        *piVar1 = iVar3;
        iVar3 = FUN_10013ec0(iVar3,(int *)(param_4 + 8));
        *piVar1 = iVar3;
        goto LAB_10013e20;
      }
    }
    FUN_100141b0();
  }
LAB_10013e20:
  *unaff_FS_OFFSET = local_14;
  return;
}
#undef local_14
#undef local_8
#undef puStack_10
#undef puStack_c


/* ---- 0x10013f40  _mtinit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 _mtinit(void)

{
  int *a2;
  int iVar1;
  
  _mtinitlocks();
  DAT_10028ba0 = TlsAlloc();
  if (DAT_10028ba0 != -1) {
    a2 = calloc(1,0x74);
    if (a2 != (int *)0x0) {
      iVar1 = TlsSetValue(DAT_10028ba0,(int)a2);
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

/* ---- 0x10013fa0  _mtterm ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _mtterm(void)

{
  _mtdeletelocks();
  if (DAT_10028ba0 != -1) {
    TlsFree(DAT_10028ba0);
    DAT_10028ba0 = -1;
  }
  return;
}

/* ---- 0x10013fd0  _initptd ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _initptd(int param_1)

{
  *(undefined **)(param_1 + 0x50) = &DAT_10029a78;
  *(undefined4 *)(param_1 + 0x14) = 1;
  return;
}

/* ---- 0x10013ff0  _getptd ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * _getptd(void)

{
  int a1;
  int *a2;
  int iVar1;
  
  a1 = GetLastError();
  a2 = (int *)TlsGetValue(DAT_10028ba0);
  if (a2 == (int *)0x0) {
    a2 = calloc(1,0x74);
    if (a2 != (int *)0x0) {
      iVar1 = TlsSetValue(DAT_10028ba0,(int)a2);
      if (iVar1 != 0) {
        _initptd((int)a2);
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

/* ---- 0x10014070  _freeptd ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _freeptd(undefined *param_1)

{
  if (DAT_10028ba0 != -1) {
    if ((param_1 != (undefined *)0x0) ||
       (param_1 = (undefined *)TlsGetValue(DAT_10028ba0), param_1 != (undefined *)0x0)) {
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
      if (*(undefined **)(param_1 + 0x50) != &DAT_10029a78) {
        free(*(undefined **)(param_1 + 0x50));
      }
      free(param_1);
    }
    TlsSetValue(DAT_10028ba0,0);
    return;
  }
  return;
}

/* ---- 0x10014120  terminate ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void terminate(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  #define puStack_10 (*(undefined1 **)(_frame + (0x30 - 0x10)))
  #define puStack_c (*(undefined **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x30 - 0x8)))
  
  puStack_c = &DAT_10023e70;
  puStack_10 = &LAB_1001dec8;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  local_8 = 0;
  piVar1 = _getptd();
  if (piVar1[0x18] != 0) {
    local_8 = 1;
    piVar1 = _getptd();
    (*(code *)piVar1[0x18])();
  }
  local_8 = 0xffffffff;
  FUN_10014197();
  *unaff_FS_OFFSET = local_14;
  return;
}
#undef local_14
#undef local_8
#undef puStack_10
#undef puStack_c


/* ---- 0x10014240  _flsbuf ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _flsbuf(uint param_1,int *param_2)

{
  uint uVar1;
  char *pcVar2;
  int *piVar3;
  byte bVar4;
  undefined3 extraout_var;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  
  piVar3 = param_2;
  uVar7 = param_2[3];
  uVar1 = param_2[4];
  if (((uVar7 & 0x82) == 0) || ((uVar7 & 0x40) != 0)) {
LAB_10014363:
    param_2[3] = uVar7 | 0x20;
    return 0xffffffff;
  }
  uVar6 = 0;
  if ((uVar7 & 1) != 0) {
    param_2[1] = 0;
    if ((uVar7 & 0x10) == 0) goto LAB_10014363;
    *param_2 = param_2[2];
    param_2[3] = uVar7 & 0xfffffffe;
  }
  uVar7 = param_2[3];
  param_2[1] = 0;
  param_2[3] = uVar7 & 0xffffffef | 2;
  if ((uVar7 & 0x10c) == 0) {
    if ((param_2 == (int *)&DAT_100282f0) || (param_2 == (int *)&DAT_10028310)) {
      bVar4 = _isatty(uVar1);
      if (((uint)(bVar4)) != 0) goto LAB_100142b3;
    }
    _getbuf(piVar3);
  }
LAB_100142b3:
  if ((piVar3[3] & 0x108U) == 0) {
    uVar7 = 1;
    uVar6 = _write(uVar1,(char *)&param_1,1);
  }
  else {
    pcVar2 = (char *)piVar3[2];
    uVar7 = *piVar3 - (int)pcVar2;
    *piVar3 = (int)(pcVar2 + 1);
    piVar3[1] = piVar3[6] + -1;
    if ((int)uVar7 < 1) {
      if (uVar1 == 0xffffffff) {
        piVar5 = (int *)&DAT_10028c70;
      }
      else {
        piVar5 = (&PTR_1002c600)[(int)uVar1 >> 5] + (uVar1 & 0x1f) * 9;
      }
      if ((*(byte *)(piVar5 + 1) & 0x20) != 0) {
        _lseek(uVar1,0,2);
      }
      *(undefined1 *)piVar3[2] = (undefined1)param_1;
    }
    else {
      uVar6 = _write(uVar1,pcVar2,uVar7);
      *(undefined1 *)piVar3[2] = (undefined1)param_1;
    }
  }
  if (uVar6 != uVar7) {
    piVar3[3] = piVar3[3] | 0x20;
    return 0xffffffff;
  }
  return param_1 & 0xff;
}

/* ---- 0x10014370  _output ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _output(int *param_1,char *param_2,undefined4 *param_3)

{
  unsigned char _frame[0x260];  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int a3;
  uint uVar2;
  short *psVar3;
  int *piVar4;
  undefined4 uVar5;
  ushort *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int extraout_EDX;
  char cVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  char *pcVar13;
  int iVar14;
  ulonglong uVar15;
  #define local_24c (*(uint *)(_frame + (0x260 - 0x24c)))
  #define local_248 (*(ushort **)(_frame + (0x260 - 0x248)))
  #define local_244 (*(int *)(_frame + (0x260 - 0x244)))
  #define local_240 (*(int *)(_frame + (0x260 - 0x240)))
  #define local_23a (*(char *)(_frame + (0x260 - 0x23a)))
  #define local_239 (*(char *)(_frame + (0x260 - 0x239)))
  #define local_238 (*(int *)(_frame + (0x260 - 0x238)))
  #define local_234 (*(int *)(_frame + (0x260 - 0x234)))
  #define local_230 (*(int *)(_frame + (0x260 - 0x230)))
  #define local_22c (*(int *)(_frame + (0x260 - 0x22c)))
  #define local_228 (*(int *)(_frame + (0x260 - 0x228)))
  #define local_224 (*(int *)(_frame + (0x260 - 0x224)))
  #define local_220 (*(int *)(_frame + (0x260 - 0x220)))
  #define local_21c (*(uint *)(_frame + (0x260 - 0x21c)))
  #define local_218 (*(undefined4 *)(_frame + (0x260 - 0x218)))
  #define local_214 (*(char (*)[4])(_frame + (0x260 - 0x214)))
  #define local_210 (*(undefined4 *)(_frame + (0x260 - 0x210)))
  #define local_20c (*(undefined4 *)(_frame + (0x260 - 0x20c)))
  #define local_204 (*(int *)(_frame + (0x260 - 0x204)))
  #define local_200 (*(undefined1 (*)[511])(_frame + (0x260 - 0x200)))
  #define uStack_1 (*(undefined1 *)(_frame + (0x260 - 0x1)))
  
  local_220 = 0;
  puVar12 = (undefined1 *)0x0;
  local_240 = 0;
  cVar10 = *param_2;
  local_21c = CONCAT31(PIECE(local_21c,1,3),cVar10);
  pcVar13 = param_2;
  do {
    if ((cVar10 == '\0') || (param_2 = pcVar13 + 1, local_240 < 0)) {
      return local_240;
    }
    if ((cVar10 < ' ') || ('x' < cVar10)) {
      uVar2 = 0;
    }
    else {
      uVar2 = *(byte *)((int)&PTR_FUN_10023e80 + (int)cVar10) & 0xf;
    }
    local_220 = (int)(char)(&DAT_10023ea0)[uVar2 * 8 + local_220] >> 4;
    switch(local_220) {
    case 0:
switchD_100143ed_caseD_0:
      local_230 = 0;
      if ((PTR_DAT_10028950[(local_21c & 0xff) * 2 + 1] & 0x80) != 0) {
        write_char((int)cVar10,param_1,&local_240);
        cVar10 = *param_2;
        param_2 = pcVar13 + 2;
      }
      write_char((int)cVar10,param_1,&local_240);
      break;
    case 1:
      local_218 = 0;
      local_228 = 0;
      local_234 = 0;
      local_238 = 0;
      local_24c = 0;
      local_244 = -1;
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
        local_234 = get_int_arg((int *)&param_3);
        if (local_234 < 0) {
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
        local_244 = get_int_arg((int *)&param_3);
        if (local_244 < 0) {
          local_244 = -1;
        }
      }
      else {
        local_244 = cVar10 + -0x30 + local_244 * 10;
      }
      break;
    case 6:
      switch(cVar10) {
      case 'I':
        if ((*param_2 != '6') || (pcVar13[2] != '4')) {
          local_220 = 0;
          goto switchD_100143ed_caseD_0;
        }
        param_2 = pcVar13 + 3;
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
          uVar5 = get_int_arg((int *)&param_3);
          local_200[0] = (char)uVar5;
          puVar12 = (undefined1 *)0x1;
        }
        else {
          uVar5 = get_int64_arg(&param_3);
          puVar12 = (undefined1 *)wctomb(local_200,(ushort)uVar5);
          if ((int)puVar12 < 0) {
            local_248 = (ushort *)local_200;
            local_228 = 1;
            break;
          }
        }
        local_248 = (ushort *)local_200;
        break;
      case 'E':
      case 'G':
        local_218 = 1;
        cVar10 = cVar10 + ' ';
      case 'e':
      case 'f':
      case 'g':
        local_248 = (ushort *)local_200;
        if (local_244 < 0) {
          local_244 = 6;
        }
        else if ((local_244 == 0) && (cVar10 == 'g')) {
          local_244 = 1;
        }
        local_210 = *param_3;
        local_20c = param_3[1];
        param_3 = param_3 + 2;
        (*(code *)PTR_FUN_10028b78)(&local_210,local_200,(int)cVar10,local_244,local_218);
        if (((local_24c & 0x80) != 0) && (local_244 == 0)) {
          (*(code *)PTR_FUN_10028b84)(local_200);
        }
        if ((cVar10 == 'g') && ((local_24c & 0x80) == 0)) {
          (*(code *)PTR_FUN_10028b7c)(local_200);
        }
        uVar2 = local_24c | 0x40;
        if (local_200[0] == '-') {
          local_248 = (ushort *)(local_200 + 1);
          uVar2 = local_24c | 0x140;
        }
        local_24c = uVar2;
        uVar2 = 0xffffffff;
        puVar6 = local_248;
        do {
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          uVar1 = *puVar6;
          puVar6 = (ushort *)((int)puVar6 + 1);
        } while ((char)uVar1 != '\0');
        puVar12 = (undefined1 *)(~uVar2 - 1);
        break;
      case 'S':
        if ((local_24c & 0x830) == 0) {
          local_24c = local_24c | 0x800;
        }
      case 's':
        iVar14 = 0x7fffffff;
        if (local_244 != -1) {
          iVar14 = local_244;
        }
        local_248 = (ushort *)get_int_arg((int *)&param_3);
        if ((local_24c & 0x810) == 0) {
          puVar6 = local_248;
          if (local_248 == (ushort *)0x0) {
            puVar6 = (ushort *)PTR_DAT_10028ba8;
            local_248 = (ushort *)PTR_DAT_10028ba8;
          }
          for (; (iVar14 != 0 && (iVar14 = iVar14 + -1, (char)*puVar6 != '\0'));
              puVar6 = (ushort *)((int)puVar6 + 1)) {
          }
          puVar12 = (undefined1 *)((int)puVar6 - (int)local_248);
        }
        else {
          if (local_248 == (ushort *)0x0) {
            local_248 = (ushort *)PTR_DAT_10028bac;
          }
          local_230 = 1;
          for (puVar6 = local_248; (iVar14 != 0 && (iVar14 = iVar14 + -1, *puVar6 != 0));
              puVar6 = puVar6 + 1) {
          }
          puVar12 = (undefined1 *)((int)puVar6 - (int)local_248 >> 1);
        }
        break;
      case 'X':
        goto switchD_10014601_caseD_58;
      case 'Z':
        psVar3 = (short *)get_int_arg((int *)&param_3);
        if ((psVar3 == (short *)0x0) ||
           (local_248 = *(ushort **)(psVar3 + 2), local_248 == (ushort *)0x0)) {
          uVar2 = 0xffffffff;
          local_248 = (ushort *)PTR_DAT_10028ba8;
          pcVar13 = PTR_DAT_10028ba8;
          do {
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            cVar10 = *pcVar13;
            pcVar13 = pcVar13 + 1;
          } while (cVar10 != '\0');
          puVar12 = (undefined1 *)(~uVar2 - 1);
        }
        else if ((local_24c & 0x800) == 0) {
          puVar12 = (undefined1 *)(int)*psVar3;
          local_230 = 0;
        }
        else {
          local_230 = 1;
          puVar12 = (undefined1 *)((uint)(int)*psVar3 >> 1);
        }
        break;
      case 'd':
      case 'i':
        local_22c = 10;
        local_24c = local_24c | 0x40;
        goto LAB_10014937;
      case 'n':
        piVar4 = (int *)get_int_arg((int *)&param_3);
        if ((local_24c & 0x20) == 0) {
          local_228 = 1;
          *piVar4 = local_240;
        }
        else {
          local_228 = 1;
          *(undefined2 *)piVar4 = (undefined2)local_240;
        }
        break;
      case 'o':
        local_22c = 8;
        if ((local_24c & 0x80) != 0) {
          local_24c = local_24c | 0x200;
        }
        goto LAB_10014937;
      case 'p':
        local_244 = 8;
switchD_10014601_caseD_58:
        local_224 = 7;
LAB_100148f2:
        local_22c = 0x10;
        if ((local_24c & 0x80) != 0) {
          local_23a = '0';
          local_239 = (char)local_224 + 'Q';
          local_238 = 2;
        }
        goto LAB_10014937;
      case 'u':
        local_22c = 10;
LAB_10014937:
        if ((local_24c & 0x8000) == 0) {
          if ((local_24c & 0x20) == 0) {
            if ((local_24c & 0x40) == 0) {
              uVar2 = get_int_arg((int *)&param_3);
              uVar15 = (ulonglong)uVar2;
            }
            else {
              iVar14 = get_int_arg((int *)&param_3);
              uVar15 = (ulonglong)iVar14;
            }
          }
          else if ((local_24c & 0x40) == 0) {
            uVar2 = get_int_arg((int *)&param_3);
            uVar15 = (ulonglong)uVar2 & 0xffffffff0000ffff;
          }
          else {
            uVar5 = get_int_arg((int *)&param_3);
            uVar15 = (ulonglong)(int)(short)uVar5;
          }
        }
        else {
          uVar15 = get_short_arg((int *)&param_3);
        }
        iVar14 = (int)(uVar15 >> 0x20);
        if ((((local_24c & 0x40) != 0) && (iVar14 == 0 || (longlong)uVar15 < 0)) &&
           ((longlong)uVar15 < 0)) {
          local_24c = local_24c | 0x100;
          uVar15 = CONCAT44(-(iVar14 + (uint)((int)uVar15 != 0)),-(int)uVar15);
        }
        iVar14 = (int)(uVar15 >> 0x20);
        iVar8 = (int)uVar15;
        if ((local_24c & 0x8000) == 0) {
          iVar14 = 0;
        }
        if (local_244 < 0) {
          local_244 = 1;
        }
        else {
          local_24c = local_24c & 0xfffffff7;
        }
        local_248 = (ushort *)REGISTER0X(0x00000010);
        if (iVar8 == 0 && iVar14 == 0) {
          local_238 = 0;
        }
        while( true ) {
          a3 = local_22c;
          puVar6 = (ushort *)((int)local_248 + -1);
          iVar9 = local_244 + -1;
          if ((local_244 < 1) && (iVar8 == 0 && iVar14 == 0)) break;
          local_204 = local_22c >> 0x1f;
          iVar7 = _aullrem(iVar8,iVar14,local_22c,local_204);
          iVar7 = iVar7 + 0x30;
          iVar8 = _aulldiv(iVar8,iVar14,a3,local_204);
          if (0x39 < iVar7) {
            iVar7 = iVar7 + local_224;
          }
          *(char *)puVar6 = (char)iVar7;
          local_244 = iVar9;
          iVar14 = extraout_EDX;
          local_248 = puVar6;
        }
        puVar12 = &uStack_1 + -(int)puVar6;
        local_244 = iVar9;
        if (((local_24c & 0x200) != 0) &&
           (((char)*local_248 != '0' || (puVar12 == (undefined1 *)0x0)))) {
          puVar12 = &STACK0X(0x00000000) + -(int)puVar6;
          *(char *)puVar6 = '0';
          local_248 = puVar6;
        }
        break;
      case 'x':
        local_224 = 0x27;
        goto LAB_100148f2;
      }
      if (local_228 == 0) {
        if ((local_24c & 0x40) != 0) {
          if ((local_24c & 0x100) == 0) {
            if ((local_24c & 1) == 0) {
              if ((local_24c & 2) == 0) goto LAB_10014acf;
              local_23a = ' ';
            }
            else {
              local_23a = '+';
            }
          }
          else {
            local_23a = '-';
          }
          local_238 = 1;
        }
LAB_10014acf:
        iVar14 = (local_234 - (int)puVar12) - local_238;
        if ((local_24c & 0xc) == 0) {
          write_multi_char(0x20,iVar14,param_1,&local_240);
        }
        write_string(&local_23a,local_238,param_1,&local_240);
        if (((local_24c & 8) != 0) && ((local_24c & 4) == 0)) {
          write_multi_char(0x30,iVar14,param_1,&local_240);
        }
        if ((local_230 == 0) || (puVar6 = local_248, puVar11 = puVar12, (int)puVar12 < 1)) {
          write_string((char *)local_248,(int)puVar12,param_1,&local_240);
        }
        else {
          do {
            puVar11 = puVar11 + -1;
            iVar8 = wctomb(local_214,*puVar6);
            if (iVar8 < 1) break;
            write_string(local_214,iVar8,param_1,&local_240);
            puVar6 = puVar6 + 1;
          } while (puVar11 != (undefined1 *)0x0);
        }
        if ((local_24c & 4) != 0) {
          write_multi_char(0x20,iVar14,param_1,&local_240);
        }
      }
    }
    cVar10 = *param_2;
    local_21c = CONCAT31(PIECE(local_21c,1,3),cVar10);
    pcVar13 = param_2;
  } while( true );
}
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

#endif


/* ---- 0x10014d00  write_char ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl write_char(uint param_1,int *param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_2[1];
  param_2[1] = iVar1 + -1;
  if (iVar1 + -1 < 0) {
    uVar2 = _flsbuf(param_1,param_2);
  }
  else {
    *(char *)*param_2 = (char)param_1;
    uVar2 = param_1 & 0xff;
    *param_2 = *param_2 + 1;
  }
  if (uVar2 == 0xffffffff) {
    *param_3 = -1;
    return;
  }
  *param_3 = *param_3 + 1;
  return;
}

/* ---- 0x10014d50  write_multi_char ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl write_multi_char(uint param_1,int param_2,int *param_3,int *param_4)

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

/* ---- 0x10014d90  write_string ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl write_string(char *param_1,int param_2,int *param_3,int *param_4)

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

/* ---- 0x10014dd0  get_int_arg ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl get_int_arg(int *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)*param_1;
  *param_1 = (int)(puVar1 + 1);
  return *puVar1;
}

/* ---- 0x10014df0  get_short_arg ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined8 __cdecl get_short_arg(int *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  *param_1 = (int)(puVar1 + 1);
  return *puVar1;
}

/* ---- 0x10014e10  get_int64_arg ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl get_int64_arg(undefined4 *param_1)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  
  puVar1 = (undefined2 *)*param_1;
  puVar2 = puVar1 + 2;
  *param_1 = puVar2;
  return CONCAT22((short)((uint)puVar2 >> 0x10),*puVar1);
}

/* ---- 0x10014e30  _mtinitlocks ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _mtinitlocks(void)

{
  InitializeCriticalSection((int)PTR_DAT_10028bf4);
  InitializeCriticalSection((int)PTR_DAT_10028be4);
  InitializeCriticalSection((int)PTR_DAT_10028bd4);
  InitializeCriticalSection((int)PTR_DAT_10028bb4);
  return;
}

/* ---- 0x10014e60  _mtdeletelocks ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _mtdeletelocks(void)

{
  undefined **ppuVar1;
  
  ppuVar1 = (undefined **)&DAT_10028bb0;
  do {
    if ((((*ppuVar1 != (undefined *)0x0) && (ppuVar1 != &PTR_DAT_10028bf4)) &&
        (ppuVar1 != &PTR_DAT_10028be4)) &&
       ((ppuVar1 != &PTR_DAT_10028bd4 && (ppuVar1 != &PTR_DAT_10028bb4)))) {
      DeleteCriticalSection((int)*ppuVar1);
      free(*ppuVar1);
    }
    ppuVar1 = ppuVar1 + 1;
  } while ((int)ppuVar1 < IMG_ADDR(0x10028c70));
  DeleteCriticalSection((int)PTR_DAT_10028bd4);
  DeleteCriticalSection((int)PTR_DAT_10028be4);
  DeleteCriticalSection((int)PTR_DAT_10028bf4);
  DeleteCriticalSection((int)PTR_DAT_10028bb4);
  return;
}

/* ---- 0x10014ee0  _lock ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _lock(int param_1)

{
  undefined *a1;
  
  if ((&DAT_10028bb0)[param_1] == 0) {
    a1 = (undefined *)malloc(0x18);
    if (a1 == (undefined *)0x0) {
      _amsg_exit(0x11);
    }
    _lock(0x11);
    if ((&DAT_10028bb0)[param_1] == 0) {
      InitializeCriticalSection((int)a1);
      (&DAT_10028bb0)[param_1] = a1;
    }
    else {
      free(a1);
    }
    _unlock(0x11);
  }
  EnterCriticalSection((&DAT_10028bb0)[param_1]);
  return;
}

/* ---- 0x10014f60  _unlock ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _unlock(int param_1)

{
  LeaveCriticalSection((&DAT_10028bb0)[param_1]);
  return;
}

/* ---- 0x10014fc0  _lock_file2 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _lock_file2(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    _lock(param_1 + 0x1c);
    return;
  }
  EnterCriticalSection(param_2 + 0x20);
  return;
}

/* ---- 0x10015030  _unlock_file2 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _unlock_file2(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    _unlock(param_1 + 0x1c);
    return;
  }
  LeaveCriticalSection(param_2 + 0x20);
  return;
}

/* ---- 0x10015060  _stbuf ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _stbuf(undefined4 *param_1)

{
  undefined4 uVar1;
  byte bVar2;
  undefined3 extraout_var;
  int iVar3;
  int iVar4;
  
  bVar2 = _isatty(param_1[4]);
  if (((uint)(bVar2)) == 0) {
    return 0;
  }
  if (param_1 == (undefined4 *)&DAT_100282f0) {
    iVar4 = 0;
  }
  else {
    if (param_1 != (undefined4 *)&DAT_10028310) {
      return 0;
    }
    iVar4 = 1;
  }
  DAT_1002bf90 = DAT_1002bf90 + 1;
  if ((param_1[3] & 0x10c) != 0) {
    return 0;
  }
  if ((&DAT_1002c080)[iVar4] == 0) {
    iVar3 = malloc(0x1000);
    (&DAT_1002c080)[iVar4] = iVar3;
    if (iVar3 == 0) {
      param_1[2] = param_1 + 5;
      *param_1 = param_1 + 5;
      param_1[6] = 2;
      param_1[1] = 2;
      goto LAB_10015100;
    }
  }
  uVar1 = (&DAT_1002c080)[iVar4];
  param_1[6] = 0x1000;
  param_1[2] = uVar1;
  *param_1 = uVar1;
  param_1[1] = 0x1000;
LAB_10015100:
  param_1[3] = param_1[3] | 0x1102;
  return 1;
}

/* ---- 0x10015120  _ftbuf ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _ftbuf(int param_1,int *param_2)

{
  if ((param_1 != 0) && ((param_2[3] & 0x1000U) != 0)) {
    _flush(param_2);
    param_2[6] = 0;
    param_2[3] = param_2[3] & 0xffffeeff;
    *param_2 = 0;
    param_2[2] = 0;
  }
  return;
}

/* ---- 0x100151d0  _ioinit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _ioinit(void)

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
  DAT_1002c700 = 0x20;
  PTR_1002c600 = piVar2;
  if (piVar2 < piVar2 + 0x120) {
    do {
      *(undefined1 *)(piVar2 + 1) = 0;
      *piVar2 = -1;
      *(undefined1 *)((int)piVar2 + 5) = 10;
      piVar2[2] = 0;
      piVar2 = piVar2 + 9;
    } while (piVar2 < PTR_1002c600 + 0x120);
  }
  GetStartupInfoA((int)local_44);
  if ((local_12 != 0) && (local_10 != (int *)0x0)) {
    local_48 = *local_10;
    pbVar8 = (byte *)(local_10 + 1);
    pbVar6 = pbVar8 + local_48;
    if (0x7ff < local_48) {
      local_48 = 0x800;
    }
    if (DAT_1002c700 < local_48) {
      piVar2 = &DAT_1002c604;
      do {
        puVar3 = (undefined4 *)malloc(0x480);
        if (puVar3 == (undefined4 *)0x0) {
          local_48 = DAT_1002c700;
          break;
        }
        *piVar2 = (int)puVar3;
        DAT_1002c700 = DAT_1002c700 + 0x20;
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
      } while (DAT_1002c700 < local_48);
    }
    uVar7 = 0;
    if (0 < local_48) {
      do {
        if (((*(int *)pbVar6 != -1) && ((*pbVar8 & 1) != 0)) &&
           (((*pbVar8 & 8) != 0 || (iVar4 = GetFileType(*(int *)pbVar6), iVar4 != 0)))) {
          piVar2 = (&PTR_1002c600)[(int)uVar7 >> 5];
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
    piVar2 = PTR_1002c600 + iVar4 * 9;
    if (PTR_1002c600[iVar4 * 9] == -1) {
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
        goto LAB_100153be;
      }
      *piVar2 = iVar5;
      if ((uVar7 & 0xff) == 2) {
        bVar1 = *(byte *)(piVar2 + 1) | 0x40;
        goto LAB_100153be;
      }
      if ((uVar7 & 0xff) == 3) {
        bVar1 = *(byte *)(piVar2 + 1) | 8;
        goto LAB_100153be;
      }
    }
    else {
      bVar1 = *(byte *)(piVar2 + 1) | 0x80;
LAB_100153be:
      *(byte *)(piVar2 + 1) = bVar1;
    }
    iVar4 = iVar4 + 1;
    if (2 < iVar4) {
      SetHandleCount(DAT_1002c700);
      return;
    }
  } while( true );
}
#undef local_10
#undef local_12
#undef local_44
#undef local_48


/* ---- 0x100153e0  _ioterm ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _ioterm(void)

{
  int **ppiVar1;
  int *piVar2;
  int *a1;
  
  ppiVar1 = &PTR_1002c600;
  do {
    piVar2 = *ppiVar1;
    if (piVar2 != (int *)0x0) {
      if (piVar2 < piVar2 + 0x120) {
        a1 = piVar2 + 3;
        do {
          if (a1[-1] != 0) {
            DeleteCriticalSection((int)a1);
          }
          piVar2 = piVar2 + 9;
          a1 = a1 + 9;
        } while (piVar2 < *ppiVar1 + 0x120);
      }
      free((undefined *)*ppiVar1);
      *ppiVar1 = (int *)0x0;
    }
    ppiVar1 = ppiVar1 + 1;
  } while ((int)ppiVar1 < IMG_ADDR(0x1002c700));
  return;
}

/* ---- 0x10015440  calloc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl calloc(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint a3;
  int *piVar3;
  int *piVar4;
  
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
    piVar3 = (int *)0x0;
    if (a3 < 0xffffffe1) {
      if (DAT_1002bb24 < a3) {
LAB_100154b4:
        if (piVar3 != (int *)0x0) {
          return piVar3;
        }
      }
      else {
        _lock(9);
        piVar3 = __sbh_alloc_block(a3 >> 4);
        _unlock(9);
        if (piVar3 != (int *)0x0) {
          piVar4 = piVar3;
          for (uVar2 = a3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *piVar4 = 0;
            piVar4 = piVar4 + 1;
          }
          for (uVar2 = a3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *(undefined1 *)piVar4 = 0;
            piVar4 = (int *)((int)piVar4 + 1);
          }
          goto LAB_100154b4;
        }
      }
      piVar3 = (int *)HeapAlloc(DAT_1002c5d4,8,a3);
    }
    if ((piVar3 != (int *)0x0) || (DAT_1002c59c == 0)) {
      return piVar3;
    }
    iVar1 = _callnewh(a3);
    if (iVar1 == 0) {
      return (int *)0x0;
    }
  } while( true );
}

/* ---- 0x10015590  _cinit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _cinit(void)

{
  if (PTR_lzio__ef20_100282ac != (undefined *)0x0) {
    (*(code *)PTR_lzio__ef20_100282ac)();
  }
  _initterm((undefined4 *)&DAT_10026008,(undefined4 *)&DAT_10026014);
  _initterm((undefined4 *)&DAT_10026000,(undefined4 *)&DAT_10026004);
  return;
}

/* ---- 0x100155c0  exit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl exit(undefined4 param_1)

{
  doexit(param_1,1,0);
  return;
}

/* ---- 0x100155e0  _cexit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _cexit(void)

{
  doexit(0,0,1);
  return;
}

/* ---- 0x100155f0  doexit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl doexit(int param_1,int param_2,int param_3)

{
  int a1;
  undefined4 *puVar1;
  undefined4 *puVar2;
  int a2;
  
  _lockexit();
  if (DAT_1002c0c8 == 1) {
    a2 = param_1;
    a1 = GetCurrentProcess();
    TerminateProcess(a1,a2);
  }
  DAT_1002c0c4 = 1;
  DAT_1002c0c0 = (undefined1)param_3;
  if (param_2 == 0) {
    if ((DAT_1002c5e0 != (undefined4 *)0x0) &&
       (puVar2 = (undefined4 *)(DAT_1002c5dc + -4), puVar1 = DAT_1002c5e0, DAT_1002c5e0 <= puVar2))
    {
      do {
        if ((code *)*puVar2 != (code *)0x0) {
          (*(code *)*puVar2)();
          puVar1 = DAT_1002c5e0;
        }
        puVar2 = puVar2 + -1;
      } while (puVar1 <= puVar2);
    }
    _initterm((undefined4 *)&DAT_10026018,(undefined4 *)&DAT_10026024);
  }
  _initterm((undefined4 *)&DAT_10026028,(undefined4 *)&DAT_10026030);
  if (param_3 != 0) {
    _unlockexit();
    return;
  }
  DAT_1002c0c8 = 1;
  ExitProcess(param_1);
  return;
}

/* ---- 0x100156b0  _lockexit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _lockexit(void)

{
  _lock(0xd);
  return;
}

/* ---- 0x100156c0  _unlockexit ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _unlockexit(void)

{
  _unlock(0xd);
  return;
}

/* ---- 0x100156d0  _initterm ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _initterm(undefined4 *param_1,undefined4 *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if ((code *)*param_1 != (code *)0x0) {
      (*(code *)*param_1)();
    }
  }
  return;
}

/* ---- 0x10015730  _flush ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _flush(int *param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar3 = 0;
  if ((((byte)param_1[3] & 3) == 2) && ((param_1[3] & 0x108U) != 0)) {
    uVar4 = *param_1 - param_1[2];
    if (0 < (int)uVar4) {
      uVar2 = _write(param_1[4],(char *)param_1[2],uVar4);
      uVar1 = param_1[3];
      if (uVar2 == uVar4) {
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

/* ---- 0x10015870  malloc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl malloc(uint param_1)

{
  int *piVar1;
  
  piVar1 = _nh_malloc(param_1,DAT_1002c59c);
  return piVar1;
}

/* ---- 0x10015890  _nh_malloc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl _nh_malloc(uint param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if (param_1 < 0xffffffe1) {
    if (param_1 == 0) {
      param_1 = 1;
    }
    do {
      if (param_1 < 0xffffffe1) {
        piVar1 = _heap_alloc(param_1);
      }
      else {
        piVar1 = (int *)0x0;
      }
      if (piVar1 != (int *)0x0) {
        return piVar1;
      }
      if (param_2 == 0) {
        return (int *)0x0;
      }
      iVar2 = _callnewh(param_1);
    } while (iVar2 != 0);
  }
  return (int *)0x0;
}

/* ---- 0x100158e0  _heap_alloc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl _heap_alloc(int param_1)

{
  int *piVar1;
  uint a3;
  
  a3 = param_1 + 0xfU & 0xfffffff0;
  if (a3 <= DAT_1002bb24) {
    _lock(9);
    piVar1 = __sbh_alloc_block(param_1 + 0xfU >> 4);
    _unlock(9);
    if (piVar1 != (int *)0x0) {
      return piVar1;
    }
  }
  piVar1 = (int *)HeapAlloc(DAT_1002c5d4,0,a3);
  return piVar1;
}

/* ---- 0x10015940  _spawnvpe_search ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl
_spawnvpe_search(undefined4 param_1,uint *param_2,undefined4 *param_3,undefined4 *param_4)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  uint *puVar5;
  char *pcVar6;
  byte *pbVar7;
  uint *puVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint *puVar12;
  char *pcVar13;
  uint *puVar14;
  char *pcVar15;
  
  puVar12 = (uint *)0x0;
  iVar3 = _spawnvpe(param_1,param_2,param_3,param_4);
  if ((((iVar3 == -1) && (piVar4 = _errno(), *piVar4 == 2)) &&
      (puVar5 = _mbschr_lk(param_2,0x2f), puVar5 == (uint *)0x0)) &&
     (pcVar6 = (char *)getenv(&DAT_1002425c), pcVar6 != (char *)0x0)) {
    puVar12 = (uint *)malloc(0x104);
    if (puVar12 == (uint *)0x0) {
      return -1;
    }
    pcVar6 = (char *)FUN_1001ef20(pcVar6,(char *)puVar12,0x103);
    while ((pcVar6 != (char *)0x0 && ((char)*puVar12 != '\0'))) {
      uVar9 = 0xffffffff;
      puVar5 = puVar12;
      do {
        if (uVar9 == 0) break;
        uVar9 = uVar9 - 1;
        uVar11 = *puVar5;
        puVar5 = (uint *)((int)puVar5 + 1);
      } while ((char)uVar11 != '\0');
      cVar1 = *(char *)((~uVar9 - 2) + (int)puVar12);
      if (cVar1 == '\\') {
        pbVar7 = _mbschr((byte *)puVar12,0x5c);
        if ((byte *)((~uVar9 - 2) + (int)puVar12) != pbVar7) {
LAB_10015a0e:
          uVar9 = 0xffffffff;
          pcVar13 = "\\";
          do {
            pcVar15 = pcVar13;
            if (uVar9 == 0) break;
            uVar9 = uVar9 - 1;
            pcVar15 = pcVar13 + 1;
            cVar1 = *pcVar13;
            pcVar13 = pcVar15;
          } while (cVar1 != '\0');
          uVar9 = ~uVar9;
          iVar10 = -1;
          puVar5 = puVar12;
          do {
            puVar8 = puVar5;
            if (iVar10 == 0) break;
            iVar10 = iVar10 + -1;
            puVar8 = (uint *)((int)puVar5 + 1);
            uVar11 = *puVar5;
            puVar5 = puVar8;
          } while ((char)uVar11 != '\0');
          pcVar13 = pcVar15 + -uVar9;
          pcVar15 = (char *)((int)puVar8 + -1);
          for (uVar11 = uVar9 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
            *(undefined4 *)pcVar15 = *(undefined4 *)pcVar13;
            pcVar13 = pcVar13 + 4;
            pcVar15 = pcVar15 + 4;
          }
          for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
            *pcVar15 = *pcVar13;
            pcVar13 = pcVar13 + 1;
            pcVar15 = pcVar15 + 1;
          }
        }
      }
      else if (cVar1 != '/') goto LAB_10015a0e;
      uVar9 = 0xffffffff;
      puVar5 = param_2;
      do {
        if (uVar9 == 0) break;
        uVar9 = uVar9 - 1;
        uVar11 = *puVar5;
        puVar5 = (uint *)((int)puVar5 + 1);
      } while ((char)uVar11 != '\0');
      uVar11 = 0xffffffff;
      puVar5 = puVar12;
      do {
        if (uVar11 == 0) break;
        uVar11 = uVar11 - 1;
        uVar2 = *puVar5;
        puVar5 = (uint *)((int)puVar5 + 1);
      } while ((char)uVar2 != '\0');
      if (0x103 < ~uVar9 + (~uVar11 - 2)) break;
      uVar9 = 0xffffffff;
      puVar5 = param_2;
      do {
        puVar8 = puVar5;
        if (uVar9 == 0) break;
        uVar9 = uVar9 - 1;
        puVar8 = (uint *)((int)puVar5 + 1);
        uVar11 = *puVar5;
        puVar5 = puVar8;
      } while ((char)uVar11 != '\0');
      uVar9 = ~uVar9;
      iVar3 = -1;
      puVar5 = puVar12;
      do {
        puVar14 = puVar5;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        puVar14 = (uint *)((int)puVar5 + 1);
        uVar11 = *puVar5;
        puVar5 = puVar14;
      } while ((char)uVar11 != '\0');
      pcVar13 = (char *)((int)puVar8 - uVar9);
      pcVar15 = (char *)((int)puVar14 + -1);
      for (uVar11 = uVar9 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
        *(undefined4 *)pcVar15 = *(undefined4 *)pcVar13;
        pcVar13 = pcVar13 + 4;
        pcVar15 = pcVar15 + 4;
      }
      for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
        *pcVar15 = *pcVar13;
        pcVar13 = pcVar13 + 1;
        pcVar15 = pcVar15 + 1;
      }
      iVar3 = _spawnvpe(param_1,puVar12,param_3,param_4);
      if (iVar3 != -1) break;
      piVar4 = _errno();
      if (*piVar4 != 2) {
        puVar5 = _mbschr_lk(puVar12,0x5c);
        if ((puVar12 != puVar5) && (puVar5 = _mbschr_lk(puVar12,0x2f), puVar12 != puVar5)) break;
        puVar5 = (uint *)((int)puVar12 + 1);
        puVar8 = _mbschr_lk(puVar5,0x5c);
        if ((puVar5 != puVar8) && (puVar8 = _mbschr_lk(puVar5,0x2f), puVar5 != puVar8)) break;
      }
      pcVar6 = (char *)FUN_1001ef20(pcVar6,(char *)puVar12,0x103);
    }
  }
  if (puVar12 != (uint *)0x0) {
    free((undefined *)puVar12);
  }
  return iVar3;
}

/* ---- 0x10015b30  _spawnvpe ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _spawnvpe(undefined4 param_1,uint *param_2,undefined4 *param_3,undefined4 *param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint *puVar2;
  uint *puVar3;
  byte *pbVar4;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined **ppuVar10;
  char *pcVar11;
  uint *puVar12;
  char *pcVar13;
  #define local_c (*(uint **)(_frame + (0x20 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  
  local_c = param_2;
  puVar2 = (uint *)_mbschr((byte *)param_2,0x5c);
  puVar3 = (uint *)_mbschr((byte *)param_2,0x2f);
  if (puVar3 == (uint *)0x0) {
    if ((puVar2 == (uint *)0x0) && (puVar2 = _mbschr_lk(param_2,0x3a), puVar2 == (uint *)0x0)) {
      uVar6 = 0xffffffff;
      puVar2 = param_2;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        uVar8 = *puVar2;
        puVar2 = (uint *)((int)puVar2 + 1);
      } while ((char)uVar8 != '\0');
      local_c = (uint *)malloc(~uVar6 + 2);
      if (local_c == (uint *)0x0) {
        return -1;
      }
      *(undefined2 *)local_c = 0x5c2e;
      *(char *)((int)local_c + 2) = '\0';
      uVar6 = 0xffffffff;
      puVar2 = param_2;
      do {
        puVar3 = puVar2;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        puVar3 = (uint *)((int)puVar2 + 1);
        uVar8 = *puVar2;
        puVar2 = puVar3;
      } while ((char)uVar8 != '\0');
      uVar6 = ~uVar6;
      iVar7 = -1;
      puVar2 = local_c;
      do {
        puVar12 = puVar2;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        puVar12 = (uint *)((int)puVar2 + 1);
        uVar8 = *puVar2;
        puVar2 = puVar12;
      } while ((char)uVar8 != '\0');
      pcVar5 = (char *)((int)puVar3 - uVar6);
      pcVar11 = (char *)((int)puVar12 + -1);
      for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar11 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar11 = pcVar11 + 1;
      }
      puVar2 = (uint *)((int)local_c + 2);
    }
  }
  else if ((puVar2 == (uint *)0x0) || (puVar2 < puVar3)) {
    puVar2 = puVar3;
  }
  local_8 = -1;
  pbVar4 = _mbschr((byte *)puVar2,0x2e);
  if (pbVar4 == (byte *)0x0) {
    uVar6 = 0xffffffff;
    puVar2 = local_c;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      uVar8 = *puVar2;
      puVar2 = (uint *)((int)puVar2 + 1);
    } while ((char)uVar8 != '\0');
    pcVar5 = (char *)malloc(~uVar6 + 4);
    if (pcVar5 == (char *)0x0) {
      return -1;
    }
    uVar6 = 0xffffffff;
    puVar2 = local_c;
    do {
      puVar3 = puVar2;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      puVar3 = (uint *)((int)puVar2 + 1);
      uVar8 = *puVar2;
      puVar2 = puVar3;
    } while ((char)uVar8 != '\0');
    uVar6 = ~uVar6;
    pcVar11 = (char *)((int)puVar3 - uVar6);
    pcVar13 = pcVar5;
    for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
      pcVar11 = pcVar11 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar13 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      pcVar13 = pcVar13 + 1;
    }
    uVar6 = 0xffffffff;
    puVar2 = local_c;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      uVar8 = *puVar2;
      puVar2 = (uint *)((int)puVar2 + 1);
    } while ((char)uVar8 != '\0');
    ppuVar10 = &PTR_DAT_10028d5c;
    do {
      uVar8 = 0xffffffff;
      pcVar11 = *ppuVar10;
      do {
        pcVar13 = pcVar11;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar13 = pcVar11 + 1;
        cVar1 = *pcVar11;
        pcVar11 = pcVar13;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      pcVar11 = pcVar13 + -uVar8;
      pcVar13 = pcVar5 + (~uVar6 - 1);
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
        pcVar11 = pcVar11 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar13 = *pcVar11;
        pcVar11 = pcVar11 + 1;
        pcVar13 = pcVar13 + 1;
      }
      iVar7 = _access((uint)pcVar5,0);
      if (iVar7 != -1) {
        local_8 = _spawnve(param_1,pcVar5,param_3,param_4);
        break;
      }
      ppuVar10 = ppuVar10 + -1;
    } while (IMG_ADDR(0x10028d4f) < (int)ppuVar10);
    free(pcVar5);
  }
  else {
    iVar7 = _access((uint)local_c,0);
    if (iVar7 != -1) {
      local_8 = _spawnve(param_1,(char *)local_c,param_3,param_4);
    }
  }
  if (local_c != param_2) {
    free((undefined *)local_c);
  }
  return local_8;
}
#undef local_8
#undef local_c


/* ---- 0x10015d30  _spawnve ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _spawnve(undefined4 param_1,char *param_2,undefined4 *param_3,undefined4 *param_4)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = param_2;
  iVar2 = _cenvarg(&param_2,param_3,param_4,(int *)&param_2,(int *)&param_4);
  if (iVar2 == -1) {
    return -1;
  }
  iVar2 = _dospawn(param_1,pcVar1,param_2,param_4);
  free(param_2);
  free((undefined *)param_4);
  return iVar2;
}

/* ---- 0x10015da0  _access ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _access(uint param_1,byte param_2)

{
  uint uVar1;
  undefined *puVar2;
  int *piVar3;
  
  uVar1 = GetFileAttributesA(param_1);
  if (uVar1 == 0xffffffff) {
    puVar2 = (undefined *)GetLastError();
    _dosmaperr(puVar2);
    return 0xffffffff;
  }
  if (((uVar1 & 1) != 0) && ((param_2 & 2) != 0)) {
    piVar3 = _errno();
    *piVar3 = 0xd;
    piVar3 = __doserrno();
    *piVar3 = 5;
    return 0xffffffff;
  }
  return 0;
}

/* ---- 0x10015ef0  _strdup ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

char * __cdecl _strdup(char *param_1)

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
    pcVar2 = (char *)malloc(~uVar3);
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

/* ---- 0x10016020  _mbschr ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

byte * __cdecl _mbschr(byte *param_1,uint param_2)

{
  ushort uVar1;
  byte bVar2;
  byte bVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  pbVar5 = (byte *)0x0;
  if (DAT_1002c570 == 0) {
    pbVar5 = (byte *)strrchr((char *)param_1,(char)param_2);
    return pbVar5;
  }
  _lock(0x19);
  do {
    bVar3 = *param_1;
    if ((*(byte *)((int)&DAT_1002c368 + bVar3 + 1) & 4) == 0) {
      pbVar4 = param_1;
      bVar2 = bVar3;
      if (param_2 == bVar3) {
LAB_10016098:
        pbVar5 = pbVar4;
        bVar3 = bVar2;
      }
    }
    else {
      bVar2 = param_1[1];
      pbVar4 = param_1 + 1;
      if (bVar2 == 0) {
        bVar3 = bVar2;
        if (pbVar5 == (byte *)0x0) goto LAB_10016098;
      }
      else {
        uVar1 = CONCAT11(bVar3,bVar2);
        bVar3 = bVar2;
        if (param_2 == uVar1) {
          pbVar5 = param_1;
        }
      }
    }
    param_1 = pbVar4 + 1;
    if (bVar3 == 0) {
      _unlock(0x19);
      return pbVar5;
    }
  } while( true );
}

/* ---- 0x10016130  _strnicoll ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _strnicoll(byte *param_1,byte *param_2,int param_3)

{
  int iVar1;
  
  if (param_3 == 0) {
    return 0;
  }
  iVar1 = __crtCompareStringA(DAT_1002c574,1,param_1,param_3,param_2,param_3,DAT_1002c570);
  if (iVar1 == 0) {
    return 0x7fffffff;
  }
  return iVar1 + -2;
}

/* ---- 0x10016170  __crtsetenv_from_wenviron ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __crtsetenv_from_wenviron(void)

{
  uint a6;
  uint *a5;
  int iVar1;
  int *piVar2;
  
  iVar1 = *DAT_1002c0b0;
  piVar2 = DAT_1002c0b0;
  if (iVar1 == 0) {
    return 0;
  }
  while (((a6 = WideCharToMultiByte(1,0,iVar1,-1,0,0,0,0), a6 != 0 &&
          (a5 = (uint *)malloc(a6), a5 != (uint *)0x0)) &&
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

/* ---- 0x100161f0  __tzset ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __tzset(void)

{
  if (DAT_1002c190 == 0) {
    _lock(0xb);
    if (DAT_1002c190 == 0) {
      _tzset_lk();
      DAT_1002c190 = DAT_1002c190 + 1;
    }
    _unlock(0xb);
  }
  return;
}

/* ---- 0x10016230  _tzset_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _tzset_lk(void)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  uint *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  byte *pbVar9;
  uint *puVar10;
  byte *pbVar11;
  bool bVar12;
  
  _lock(0xc);
  DAT_1002c0d8 = 0;
  DAT_10028e10 = 0xffffffff;
  DAT_10028e00 = 0xffffffff;
  puVar4 = (uint *)_getenv_lk(&DAT_100242c8);
  if (puVar4 == (uint *)0x0) {
    _unlock(0xc);
    iVar5 = GetTimeZoneInformation(IMG_ADDR(0x1002c0e0));
    if (iVar5 == -1) {
      return;
    }
    DAT_1002c0d8 = 1;
    DAT_10028d68 = DAT_1002c0e0 * 0x3c;
    if (DAT_1002c126 != 0) {
      DAT_10028d68 = DAT_10028d68 + DAT_1002c134 * 0x3c;
    }
    if ((DAT_1002c17a == 0) || (DAT_1002c188 == 0)) {
      DAT_10028d6c = 0;
      DAT_10028d70 = 0;
    }
    else {
      DAT_10028d6c = 1;
      DAT_10028d70 = (DAT_1002c188 - DAT_1002c134) * 0x3c;
    }
    wcstombs((int)PTR_DAT_10028df8,(ushort *)&DAT_1002c0e4,0x40);
    wcstombs((int)PTR_DAT_10028dfc,(ushort *)&DAT_1002c138,0x40);
    PTR_DAT_10028dfc[0x3f] = 0;
    PTR_DAT_10028df8[0x3f] = 0;
    return;
  }
  if ((char)*puVar4 != '\0') {
    puVar8 = puVar4;
    pbVar9 = DAT_1002c18c;
    if (DAT_1002c18c != (byte *)0x0) {
      do {
        bVar1 = (byte)*puVar8;
        bVar12 = bVar1 < *pbVar9;
        if (bVar1 != *pbVar9) {
LAB_10016387:
          iVar5 = (1 - (uint)bVar12) - (uint)(bVar12 != 0);
          goto LAB_1001638c;
        }
        if (bVar1 == 0) break;
        bVar1 = *(byte *)((int)puVar8 + 1);
        bVar12 = bVar1 < pbVar9[1];
        if (bVar1 != pbVar9[1]) goto LAB_10016387;
        puVar8 = (uint *)((int)puVar8 + 2);
        pbVar9 = pbVar9 + 2;
      } while (bVar1 != 0);
      iVar5 = 0;
LAB_1001638c:
      if (iVar5 == 0) goto LAB_100164f9;
    }
    free(DAT_1002c18c);
    uVar6 = 0xffffffff;
    puVar8 = puVar4;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      uVar7 = *puVar8;
      puVar8 = (uint *)((int)puVar8 + 1);
    } while ((char)uVar7 != '\0');
    DAT_1002c18c = (byte *)malloc(~uVar6);
    if (DAT_1002c18c != (byte *)0x0) {
      uVar6 = 0xffffffff;
      puVar8 = puVar4;
      do {
        puVar10 = puVar8;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        puVar10 = (uint *)((int)puVar8 + 1);
        uVar7 = *puVar8;
        puVar8 = puVar10;
      } while ((char)uVar7 != '\0');
      uVar6 = ~uVar6;
      pbVar9 = (byte *)((int)puVar10 - uVar6);
      pbVar11 = DAT_1002c18c;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar11 = *(undefined4 *)pbVar9;
        pbVar9 = pbVar9 + 4;
        pbVar11 = pbVar11 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar11 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        pbVar11 = pbVar11 + 1;
      }
      _unlock(0xc);
      strncpy((uint *)PTR_DAT_10028df8,puVar4,3);
      puVar8 = (uint *)((int)puVar4 + 3);
      PTR_DAT_10028df8[3] = 0;
      cVar2 = *(char *)puVar8;
      if (cVar2 == '-') {
        puVar8 = puVar4 + 1;
      }
      iVar5 = atol((byte *)puVar8);
      DAT_10028d68 = iVar5 * 0xe10;
      for (; (cVar3 = (char)*puVar8, cVar3 == '+' || (('/' < cVar3 && (cVar3 < ':'))));
          puVar8 = (uint *)((int)puVar8 + 1)) {
      }
      if ((char)*puVar8 == ':') {
        puVar8 = (uint *)((int)puVar8 + 1);
        iVar5 = atol((byte *)puVar8);
        DAT_10028d68 = DAT_10028d68 + iVar5 * 0x3c;
        bVar1 = *(byte *)puVar8;
        while (('/' < (char)bVar1 && ((char)bVar1 < ':'))) {
          pbVar9 = (byte *)((int)puVar8 + 1);
          puVar8 = (uint *)((int)puVar8 + 1);
          bVar1 = *pbVar9;
        }
        if ((byte)*puVar8 == 0x3a) {
          puVar8 = (uint *)((int)puVar8 + 1);
          iVar5 = atol((byte *)puVar8);
          DAT_10028d68 = DAT_10028d68 + iVar5;
          bVar1 = *(byte *)puVar8;
          while (('/' < (char)bVar1 && ((char)bVar1 < ':'))) {
            pbVar9 = (byte *)((int)puVar8 + 1);
            puVar8 = (uint *)((int)puVar8 + 1);
            bVar1 = *pbVar9;
          }
        }
      }
      if (cVar2 == '-') {
        DAT_10028d68 = -DAT_10028d68;
      }
      DAT_10028d6c = (int)(char)*puVar8;
      if (DAT_10028d6c == 0) {
        *PTR_DAT_10028dfc = 0;
        return;
      }
      strncpy((uint *)PTR_DAT_10028dfc,puVar8,3);
      PTR_DAT_10028dfc[3] = 0;
      return;
    }
  }
LAB_100164f9:
  _unlock(0xc);
  return;
}

/* ---- 0x10016510  _isindst ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

bool __cdecl _isindst(int *param_1)

{
  bool bVar1;
  
  _lock(0xb);
  bVar1 = _isindst_lk(param_1);
  _unlock(0xb);
  return bVar1;
}

/* ---- 0x10016540  _isindst_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

bool __cdecl _isindst_lk(int *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  
  if (DAT_10028d6c == 0) {
    return false;
  }
  uVar7 = param_1[5];
  if ((uVar7 == DAT_10028e00) && (uVar7 == DAT_10028e10)) goto LAB_10016714;
  if (DAT_1002c0d8 == 0) {
    _cvtdate(1,1,uVar7,4,1,0,0,2,0,0,0);
    uVar7 = param_1[5];
    uVar11 = 0;
    uVar3 = 0;
    uVar10 = 0;
    uVar4 = 2;
    uVar1 = 0;
    uVar9 = 5;
    uVar8 = 10;
LAB_10016708:
    uVar5 = 0;
    iVar6 = 1;
  }
  else {
    if (DAT_1002c178 != 0) {
      uVar10 = (uint)PIECE(DAT_1002c17c,2,2);
      uVar3 = 0;
      uVar1 = 0;
    }
    else {
      uVar3 = DAT_1002c17c & 0xffff;
      uVar10 = 0;
      uVar1 = (uint)PIECE(DAT_1002c17c,2,2);
    }
    _cvtdate(1,(uint)(DAT_1002c178 == 0),uVar7,(uint)DAT_1002c17a,uVar1,uVar3,uVar10,
             DAT_1002c180 & 0xffff,DAT_1002c180 >> 0x10,DAT_1002c184 & 0xffff,DAT_1002c184 >> 0x10);
    if (DAT_1002c124 == 0) {
      uVar11 = (uint)PIECE(DAT_1002c130,2,2);
      uVar3 = DAT_1002c130 & 0xffff;
      uVar10 = (uint)PIECE(DAT_1002c12c,2,2);
      uVar4 = DAT_1002c12c & 0xffff;
      uVar1 = DAT_1002c128 & 0xffff;
      uVar9 = (uint)PIECE(DAT_1002c128,2,2);
      uVar8 = (uint)DAT_1002c126;
      uVar7 = param_1[5];
      goto LAB_10016708;
    }
    uVar11 = (uint)PIECE(DAT_1002c130,2,2);
    uVar3 = DAT_1002c130 & 0xffff;
    uVar10 = (uint)PIECE(DAT_1002c12c,2,2);
    uVar5 = (uint)PIECE(DAT_1002c128,2,2);
    uVar4 = DAT_1002c12c & 0xffff;
    uVar7 = param_1[5];
    uVar8 = (uint)DAT_1002c126;
    uVar1 = 0;
    uVar9 = 0;
    iVar6 = 0;
  }
  _cvtdate(0,iVar6,uVar7,uVar8,uVar9,uVar1,uVar5,uVar4,uVar10,uVar3,uVar11);
LAB_10016714:
  iVar6 = param_1[7];
  if (DAT_10028e04 < DAT_10028e14) {
    if ((iVar6 < DAT_10028e04) || (DAT_10028e14 < iVar6)) {
      return false;
    }
    if ((DAT_10028e04 < iVar6) && (iVar6 < DAT_10028e14)) {
      return true;
    }
  }
  else {
    if ((iVar6 < DAT_10028e14) || (DAT_10028e04 < iVar6)) {
      return true;
    }
    if ((DAT_10028e14 < iVar6) && (iVar6 < DAT_10028e04)) {
      return false;
    }
  }
  iVar2 = (*param_1 + (param_1[1] + param_1[2] * 0x3c) * 0x3c) * 1000;
  if (iVar6 != DAT_10028e04) {
    return iVar2 < DAT_10028e18;
  }
  return DAT_10028e08 <= iVar2;
}

/* ---- 0x100167b0  _cvtdate ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl
_cvtdate(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7,
        int param_8,int param_9,int param_10,int param_11)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 1) {
    if ((param_3 & 3) == 0) {
      iVar1 = *(int *)(&DAT_1002bb2c + param_4 * 4);
    }
    else {
      iVar1 = *(int *)(&DAT_1002bb64 + param_4 * 4);
    }
    iVar2 = (int)(((int)(param_3 - 1) >> 2) + -0x63db + param_3 * 0x16d + iVar1 + 1) % 7;
    if (iVar2 < param_6) {
      iVar1 = iVar1 + -6 + (param_5 * 7 - iVar2) + param_6;
    }
    else {
      iVar1 = iVar1 + 1 + (param_5 * 7 - iVar2) + param_6;
    }
    if (param_5 == 5) {
      if ((param_3 & 3) == 0) {
        iVar2 = *(int *)(&DAT_1002bb30 + param_4 * 4);
      }
      else {
        iVar2 = (&DAT_1002bb68)[param_4];
      }
      if (iVar2 < iVar1) {
        iVar1 = iVar1 + -7;
      }
    }
  }
  else {
    if ((param_3 & 3) == 0) {
      iVar1 = *(int *)(&DAT_1002bb2c + param_4 * 4);
    }
    else {
      iVar1 = *(int *)(&DAT_1002bb64 + param_4 * 4);
    }
    iVar1 = iVar1 + param_7;
  }
  if (param_1 == 1) {
    DAT_10028e04 = iVar1;
    DAT_10028e00 = param_3;
    DAT_10028e08 = param_11 + (param_10 + (param_9 + param_8 * 0x3c) * 0x3c) * 1000;
    return;
  }
  DAT_10028e14 = iVar1;
  DAT_10028e18 = param_11 + (param_10 + (param_9 + param_8 * 0x3c) * 0x3c + DAT_10028d70) * 1000;
  if (DAT_10028e18 < 0) {
    DAT_10028e10 = param_3;
    DAT_10028e18 = DAT_10028e18 + 86399999;
    return;
  }
  if (86399999 < DAT_10028e18) {
    DAT_10028e18 = DAT_10028e18 + -86399999;
  }
  DAT_10028e10 = param_3;
  return;
}

/* ---- 0x10016950  _stricmp ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _stricmp(byte *param_1,byte *param_2)

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
  
  iVar2 = DAT_1002c710;
  if (DAT_1002c208 == 0) {
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_1001699e;
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
LAB_1001699e:
    uVar7 = (uint)cVar6;
  }
  else {
    LOCK();
    DAT_1002c710 = DAT_1002c710 + 1;
    UNLOCK();
    bVar1 = 0 < DAT_1002c70c;
    if (bVar1) {
      LOCK();
      UNLOCK();
      DAT_1002c710 = iVar2;
      _lock(0x13);
    }
    uVar9 = (uint)bVar1;
    uVar7 = 0xff;
    uVar8 = 0;
    do {
      do {
        if ((char)uVar7 == '\0') goto LAB_100169ff;
        bVar5 = *param_2;
        uVar7 = CONCAT31((int3)(uVar7 >> 8),bVar5);
        param_2 = param_2 + 1;
        bVar4 = *param_1;
        uVar8 = CONCAT31((int3)(uVar8 >> 8),bVar4);
        param_1 = param_1 + 1;
      } while (bVar5 == bVar4);
      uVar8 = _toupper_lk(uVar8);
      uVar7 = _toupper_lk(uVar7);
    } while ((byte)uVar8 == (byte)uVar7);
    uVar8 = (uint)((byte)uVar8 < (byte)uVar7);
    uVar7 = (1 - uVar8) - (uint)(uVar8 != 0);
LAB_100169ff:
    if (uVar9 == 0) {
      LOCK();
      DAT_1002c710 = DAT_1002c710 + -1;
      UNLOCK();
    }
    else {
      _unlock(0x13);
    }
  }
  return uVar7;
}

/* ---- 0x10016a20  gmtime ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl gmtime(int *param_1)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  bVar1 = false;
  iVar8 = *param_1;
  piVar2 = _getptd();
  if (iVar8 < 0) {
    return (int *)0x0;
  }
  if (piVar2[0x10] == 0) {
    iVar3 = malloc(0x24);
    piVar2[0x10] = iVar3;
    piVar4 = (int *)&DAT_1002c198;
    if (iVar3 == 0) goto LAB_10016a5f;
  }
  piVar4 = (int *)piVar2[0x10];
LAB_10016a5f:
  iVar6 = iVar8 % 0x7861f80;
  iVar8 = (iVar8 / 0x7861f80) * 4;
  iVar3 = iVar8 + 0x46;
  iVar7 = iVar6;
  if (0x1e1337f < iVar6) {
    iVar7 = iVar6 + -0x1e13380;
    iVar3 = iVar8 + 0x47;
    if (0x1e1337f < iVar7) {
      iVar7 = iVar6 + -0x3c26700;
      iVar3 = iVar8 + 0x48;
      if (iVar7 < 0x1e28500) {
        bVar1 = true;
      }
      else {
        iVar3 = iVar8 + 0x49;
        iVar7 = iVar6 + -0x5a4ec00;
      }
    }
  }
  piVar4[5] = iVar3;
  piVar4[7] = iVar7 / 0x15180;
  puVar5 = (undefined4 *)&DAT_1002bb30;
  if (!bVar1) {
    puVar5 = &DAT_1002bb68;
  }
  piVar2 = puVar5 + 1;
  iVar3 = 1;
  iVar8 = *piVar2;
  while (iVar8 < piVar4[7]) {
    piVar2 = piVar2 + 1;
    iVar3 = iVar3 + 1;
    iVar8 = *piVar2;
  }
  piVar4[4] = iVar3 + -1;
  piVar4[3] = piVar4[7] - puVar5[iVar3 + -1];
  iVar8 = *param_1;
  piVar4[8] = 0;
  piVar4[6] = (iVar8 / 0x15180 + 4) % 7;
  piVar4[2] = (iVar7 % 0x15180) / 0xe10;
  iVar8 = (iVar7 % 0x15180) % 0xe10;
  piVar4[1] = iVar8 / 0x3c;
  *piVar4 = iVar8 % 0x3c;
  return piVar4;
}

/* ---- 0x10016b90  __loctotime_t ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl
__loctotime_t(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  bool bVar2;
  undefined3 extraout_var;
  uint uVar3;
  int iVar4;
  #define local_24 (*(int (*)[2])(_frame + (0x40 - 0x24)))
  #define local_1c (*(int *)(_frame + (0x40 - 0x1c)))
  #define local_14 (*(int *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_8 (*(int *)(_frame + (0x40 - 0x8)))
  
  uVar3 = param_1 - 0x76c;
  if (((int)uVar3 < 0x46) || (0x8a < (int)uVar3)) {
    return -1;
  }
  iVar4 = *(int *)(&DAT_1002bb64 + param_2 * 4) + param_3;
  if (((uVar3 & 3) == 0) && (2 < param_2)) {
    iVar4 = iVar4 + 1;
  }
  __tzset();
  local_1c = param_4;
  local_14 = param_2 + -1;
  iVar1 = param_6 + (param_5 +
                    (param_4 + ((param_1 + -0x76d >> 2) + uVar3 * 0x16d + iVar4) * 0x18) * 0x3c) *
                    0x3c + 0x7c558180 + DAT_10028d68;
  if (param_7 != 1) {
    if (param_7 != -1) {
      return iVar1;
    }
    if (DAT_10028d6c == 0) {
      return iVar1;
    }
    local_10 = uVar3;
    local_8 = iVar4;
    bVar2 = _isindst(local_24);
    if (((uint)(bVar2)) == 0) {
      return iVar1;
    }
  }
  return iVar1 + DAT_10028d70;
}
#undef local_10
#undef local_14
#undef local_1c
#undef local_24
#undef local_8


/* ---- 0x10017ba0  free ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl free(undefined *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined *a3;
  byte *pbVar1;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  a3 = param_1;
  if (param_1 != (undefined *)0x0) {
    _lock(9);
    pbVar1 = (byte *)__sbh_find_block(a3,&local_4,(uint *)&param_1);
    if (pbVar1 != (byte *)0x0) {
      __sbh_free_block(local_4,(int)param_1,pbVar1);
      _unlock(9);
      return;
    }
    _unlock(9);
    HeapFree(DAT_1002c5d4,0,(int)a3);
  }
  return;
}
#undef local_4


/* ---- 0x10017c50  __get_qualified_locale ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl __get_qualified_locale(char *param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  if (DAT_1002c23c == (code *)0x0) {
    iVar1 = FUN_100185b0();
    if (iVar1 == 0) {
      DAT_1002c23c = FUN_100185f0;
    }
    else {
      DAT_1002c23c = GetLocaleInfoA_exref;
    }
  }
  if (param_1 != (char *)0x0) {
    DAT_1002c22c = param_1;
    if (*param_1 != '\0') {
      FUN_10017df0(IMG_ADDR(0x10028e20),0x40,(int *)&DAT_1002c22c);
    }
    DAT_1002c230 = param_1 + 0x40;
    if ((DAT_1002c230 != (char *)0x0) && (*DAT_1002c230 != '\0')) {
      FUN_10017df0(IMG_ADDR(0x10029028),0x16,(int *)&DAT_1002c230);
    }
    DAT_1002c234 = 0;
    if ((DAT_1002c22c != (char *)0x0) && (*DAT_1002c22c != '\0')) {
      if ((DAT_1002c230 == (char *)0x0) || (*DAT_1002c230 == '\0')) {
        GetLcidFromLanguage();
      }
      else {
        GetLcidFromLangCountry();
      }
      goto LAB_10017d15;
    }
    if ((DAT_1002c230 != (char *)0x0) && (*DAT_1002c230 != '\0')) {
      GetLcidFromCountryOnly();
      goto LAB_10017d15;
    }
  }
  GetLcidFromDefault();
LAB_10017d15:
  if ((((DAT_1002c234 != 0) && (uVar2 = TranslateName((byte *)(param_1 + 0x80)), uVar2 != 0)) &&
      (iVar1 = IsValidCodePage(uVar2 & 0xffff), iVar1 != 0)) &&
     (iVar1 = IsValidLocale(DAT_1002c21c,1), iVar1 != 0)) {
    if (param_2 != 0) {
      *(undefined2 *)param_2 = (undefined2)DAT_1002c21c;
      *(undefined2 *)(param_2 + 2) = (undefined2)DAT_1002c238;
      *(short *)(param_2 + 4) = (short)uVar2;
    }
    if (param_3 == 0) {
      return 1;
    }
    iVar1 = (*DAT_1002c23c)(DAT_1002c21c,0x1001,param_3,0x40);
    if ((iVar1 != 0) &&
       (iVar1 = (*DAT_1002c23c)(DAT_1002c238,0x1002,param_3 + 0x40,0x40), iVar1 != 0)) {
      FUN_10015f40(uVar2,(char *)(param_3 + 0x80),10);
      return 1;
    }
  }
  return 0;
}

/* ---- 0x10018790  __crtLCMapStringW ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

short * __cdecl
__crtLCMapStringW(int param_1,uint param_2,short *param_3,int param_4,uint *param_5,short *param_6,
                 uint *param_7)

{
  int iVar1;
  short *psVar2;
  uint a6;
  undefined *a5;
  
  if (DAT_1002c240 == (short *)0x0) {
    iVar1 = LCMapStringW(0,0x100,IMG_ADDR(0x10024958),1,0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringA(0,0x100,IMG_ADDR(0x10024954),1,0,0);
      if (iVar1 == 0) {
        return (short *)0x0;
      }
      DAT_1002c240 = (short *)0x2;
    }
    else {
      DAT_1002c240 = (short *)0x1;
    }
  }
  iVar1 = param_4;
  if (0 < param_4) {
    iVar1 = wcsncnt(param_3,param_4);
  }
  if (DAT_1002c240 == (short *)0x1) {
    psVar2 = (short *)LCMapStringW(param_1,param_2,(int)param_3,iVar1,(int)param_5,(int)param_6);
    return psVar2;
  }
  if (DAT_1002c240 != (short *)0x2) {
    return DAT_1002c240;
  }
  param_4 = 0;
  if (param_7 == (uint *)0x0) {
    param_7 = DAT_1002c218;
  }
  a6 = WideCharToMultiByte((int)param_7,0x220,(int)param_3,iVar1,0,0,0,0);
  if (a6 == 0) {
    return (short *)0x0;
  }
  a5 = (undefined *)malloc(a6);
  if (a5 == (undefined *)0x0) {
    return (short *)0x0;
  }
  iVar1 = WideCharToMultiByte((int)param_7,0x220,(int)param_3,iVar1,(int)a5,a6,0,0);
  if ((((iVar1 != 0) &&
       (psVar2 = (short *)LCMapStringA(param_1,param_2,(int)a5,a6,0,0), psVar2 != (short *)0x0)) &&
      (param_4 = malloc((uint)psVar2), (uint *)param_4 != (uint *)0x0)) &&
     (iVar1 = LCMapStringA(param_1,param_2,(int)a5,a6,param_4,(int)psVar2), iVar1 != 0)) {
    if ((param_2 & 0x400) == 0) {
      if (param_6 == (short *)0x0) {
        psVar2 = (short *)MultiByteToWideChar((int)param_7,1,param_4,(int)psVar2,0,0);
      }
      else {
        psVar2 = (short *)MultiByteToWideChar((int)param_7,1,param_4,(int)psVar2,(int)param_5,
                                              (int)param_6);
      }
      if (psVar2 == (short *)0x0) goto LAB_1001897a;
    }
    else if (param_6 != (short *)0x0) {
      if ((int)psVar2 <= (int)param_6) {
        param_6 = psVar2;
      }
      strncpy(param_5,(uint *)param_4,(uint)param_6);
    }
    free(a5);
    free((undefined *)param_4);
    return psVar2;
  }
LAB_1001897a:
  free(a5);
  free((undefined *)param_4);
  return (short *)0x0;
}

/* ---- 0x100189a0  wcsncnt ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl wcsncnt(short *param_1,int param_2)

{
  short *psVar1;
  int iVar2;
  
  psVar1 = param_1;
  iVar2 = param_2;
  while (iVar2 != 0) {
    iVar2 = iVar2 + -1;
    if (*psVar1 == 0) goto LAB_100189c9;
    psVar1 = psVar1 + 1;
  }
  if (*psVar1 != 0) {
    return param_2;
  }
LAB_100189c9:
  return (int)psVar1 - (int)param_1 >> 1;
}

/* ---- 0x100189e0  __crtLCMapStringA ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl
__crtLCMapStringA(int param_1,uint param_2,char *param_3,int param_4,int param_5,int param_6,
                 uint param_7,int param_8)

{
  int iVar1;
  int iVar2;
  undefined *a5;
  
  if (DAT_1002c244 == 0) {
    iVar1 = LCMapStringW(0,0x100,IMG_ADDR(0x10024958),1,0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringA(0,0x100,IMG_ADDR(0x10024954),1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_1002c244 = 2;
    }
    else {
      DAT_1002c244 = 1;
    }
  }
  iVar1 = param_4;
  if (0 < param_4) {
    iVar1 = _strncnt(param_3,param_4);
  }
  if (DAT_1002c244 == 2) {
    iVar1 = LCMapStringA(param_1,param_2,(int)param_3,iVar1,param_5,param_6);
    return iVar1;
  }
  if (DAT_1002c244 != 1) {
    return DAT_1002c244;
  }
  param_4 = 0;
  if (param_7 == 0) {
    param_7 = DAT_1002c218;
  }
  iVar2 = MultiByteToWideChar(param_7,(-(uint)(param_8 != 0) & 8) + 1,(int)param_3,iVar1,0,0);
  if (iVar2 == 0) {
    return 0;
  }
  a5 = (undefined *)malloc(iVar2 * 2);
  if (a5 == (undefined *)0x0) {
    return 0;
  }
  iVar1 = MultiByteToWideChar(param_7,1,(int)param_3,iVar1,(int)a5,iVar2);
  if ((iVar1 != 0) && (iVar1 = LCMapStringW(param_1,param_2,(int)a5,iVar2,0,0), iVar1 != 0)) {
    if ((param_2 & 0x400) == 0) {
      param_4 = malloc(iVar1 * 2);
      if ((param_4 == 0) ||
         (iVar2 = LCMapStringW(param_1,param_2,(int)a5,iVar2,param_4,iVar1), iVar2 == 0))
      goto LAB_10018be8;
      if (param_6 == 0) {
        iVar1 = WideCharToMultiByte(param_7,0x220,param_4,iVar1,0,0,0,0);
        iVar2 = iVar1;
      }
      else {
        iVar1 = WideCharToMultiByte(param_7,0x220,param_4,iVar1,param_5,param_6,0,0);
        iVar2 = iVar1;
      }
    }
    else {
      if (param_6 == 0) goto LAB_10018b4f;
      if (param_6 < iVar1) goto LAB_10018be8;
      iVar2 = LCMapStringW(param_1,param_2,(int)a5,iVar2,param_5,param_6);
    }
    if (iVar2 != 0) {
LAB_10018b4f:
      free(a5);
      free((undefined *)param_4);
      return iVar1;
    }
  }
LAB_10018be8:
  free(a5);
  free((undefined *)param_4);
  return 0;
}

/* ---- 0x10018fd0  _frnd ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

float __cdecl _frnd(double param_1)

{
  return (float)ROUND(param_1);
}

/* ---- 0x10019100  _raise_exc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl
_raise_exc(uint *param_1,uint *param_2,byte param_3,uint param_4,uint *param_5,uint *param_6)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
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
  uVar3 = FUN_10019a70();
  puVar2 = param_6;
  if ((uVar3 & 1) != 0) {
    param_1[3] = param_1[3] | 0x10;
  }
  if ((uVar3 & 4) != 0) {
    param_1[3] = param_1[3] | 8;
  }
  if ((uVar3 & 8) != 0) {
    param_1[3] = param_1[3] | 4;
  }
  if ((uVar3 & 0x10) != 0) {
    param_1[3] = param_1[3] | 2;
  }
  if ((uVar3 & 0x20) != 0) {
    param_1[3] = param_1[3] | 1;
  }
  uVar3 = *puVar1 & 0xc00;
  if (uVar3 < 0x401) {
    if (uVar3 == 0x400) {
      *param_1 = *param_1 & 0xfffffffd | 1;
    }
    else if (uVar3 == 0) {
      *param_1 = *param_1 & 0xfffffffc;
    }
  }
  else if (uVar3 == 0x800) {
    *param_1 = *param_1 & 0xfffffffe | 2;
  }
  else if (uVar3 == 0xc00) {
    *param_1 = *param_1 | 3;
  }
  uVar3 = *puVar1 & 0x300;
  if (uVar3 == 0) {
    *param_1 = *param_1 & 0xffffffeb | 8;
  }
  else if (uVar3 == 0x200) {
    *param_1 = *param_1 & 0xffffffe7 | 4;
  }
  else if (uVar3 == 0x300) {
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
  FUN_10019a80();
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
    uVar3 = *puVar1 & 0xfffff3ff;
    break;
  case 1:
    *puVar1 = *puVar1 & 0xfffff7ff | 0x400;
    goto switchD_1001939b_default;
  case 2:
    uVar3 = *puVar1 & 0xfffffbff | 0x800;
    break;
  case 3:
    uVar3 = *puVar1 | 0xc00;
    break;
  default:
    goto switchD_1001939b_default;
  }
  *puVar1 = uVar3;
switchD_1001939b_default:
  uVar3 = *param_1 >> 2 & 7;
  if (uVar3 == 0) {
    *puVar1 = *puVar1 & 0xfffff3ff | 0x300;
  }
  else {
    if (uVar3 == 1) {
      *puVar1 = *puVar1 & 0xfffff3ff | 0x200;
      *puVar2 = param_1[0x10];
      puVar2[1] = param_1[0x11];
      return;
    }
    if (uVar3 == 2) {
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

/* ---- 0x10019440  _handle_exc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

bool __cdecl _handle_exc(uint param_1,double *param_2,uint param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ulonglong uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  bool bVar5;
  float fVar6;
  #define local_14 (*(int *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(undefined8 *)(_frame + (0x30 - 0x10)))
  
  uVar4 = param_1 & 0x1f;
  if (((param_1 & 8) == 0) || ((param_3 & 1) == 0)) {
    if (((param_1 & 4) == 0) || ((param_3 & 4) == 0)) {
      if (((param_1 & 1) == 0) || ((param_3 & 8) == 0)) {
        if (((param_1 & 2) != 0) && ((param_3 & 0x10) != 0)) {
          bVar5 = (param_1 & 0x10) != 0;
          local_10 = *param_2;
          if (local_10 == 0.0) {
            bVar5 = true;
          }
          else {
            fVar6 = FUN_10019960(*(uint *)param_2,*(uint *)((int)param_2 + 4),&local_14);
            local_14 = local_14 + -0x600;
            if (local_14 < -0x432) {
              bVar5 = true;
              *(undefined4 *)param_2 = 0;
              local_10 = 0.0;
              *(undefined4 *)((int)param_2 + 4) = 0;
            }
            else {
              local_10 = (double)(ulonglong)
                                 (SUB87((double)fVar6,0) & 0xfffffffffffff | 0x10000000000000);
              if (local_14 < -0x3fd) {
                local_14 = -0x3fd - local_14;
                do {
                  if ((((ulonglong)local_10 & 1) != 0) && (!bVar5)) {
                    bVar5 = true;
                  }
                  uVar4 = (uint)local_10 >> 1;
                  uVar1 = (ulonglong)local_10 & 0x100000000;
                  PIECE(local_10,0,4) = uVar4;
                  if (uVar1 != 0) {
                    PIECE(local_10,0,4) = uVar4 | 0x80000000;
                  }
                  local_14 = local_14 + -1;
                  local_10 = (double)CONCAT44(PIECE(local_10,4,4) >> 1,(uint)local_10);
                } while (local_14 != 0);
              }
              if ((double)fVar6 < 0.0) {
                local_10 = -local_10;
              }
              *(uint *)param_2 = (uint)local_10;
              *(uint *)((int)param_2 + 4) = PIECE(local_10,4,4);
            }
          }
          if (bVar5) {
            FUN_10019ad0();
          }
          uVar4 = param_1 & 0x1d;
        }
      }
      else {
        FUN_10019ad0();
        uVar3 = DAT_100296bc;
        uVar2 = DAT_100296ac;
        uVar4 = param_3 & 0xc00;
        if (uVar4 < 0x401) {
          if (uVar4 == 0x400) {
            if (*param_2 <= 0.0) {
              local_10 = -(double)CONCAT44(DAT_100296ac,DAT_100296a8);
              *param_2 = local_10;
              uVar4 = param_1 & 0x1e;
            }
            else {
              *(undefined4 *)param_2 = DAT_100296b8;
              *(undefined4 *)((int)param_2 + 4) = uVar3;
              uVar4 = param_1 & 0x1e;
            }
            goto LAB_1001974b;
          }
          if (uVar4 == 0) {
            if (*param_2 <= 0.0) {
              local_10 = -(double)CONCAT44(DAT_100296ac,DAT_100296a8);
              *param_2 = local_10;
              uVar4 = param_1 & 0x1e;
            }
            else {
              *(undefined4 *)param_2 = DAT_100296a8;
              *(undefined4 *)((int)param_2 + 4) = uVar2;
              uVar4 = param_1 & 0x1e;
            }
            goto LAB_1001974b;
          }
        }
        else if (uVar4 == 0x800) {
          if (0.0 < *param_2) {
            *(undefined4 *)param_2 = DAT_100296a8;
            *(undefined4 *)((int)param_2 + 4) = uVar2;
            uVar4 = param_1 & 0x1e;
            goto LAB_1001974b;
          }
          local_10 = -(double)CONCAT44(DAT_100296bc,DAT_100296b8);
          *param_2 = local_10;
        }
        else if (uVar4 == 0xc00) {
          if (*param_2 <= 0.0) {
            local_10 = -(double)CONCAT44(DAT_100296bc,DAT_100296b8);
            *param_2 = local_10;
            uVar4 = param_1 & 0x1e;
          }
          else {
            *(undefined4 *)param_2 = DAT_100296b8;
            *(undefined4 *)((int)param_2 + 4) = uVar3;
            uVar4 = param_1 & 0x1e;
          }
          goto LAB_1001974b;
        }
        uVar4 = param_1 & 0x1e;
      }
    }
    else {
      FUN_10019ad0();
      uVar4 = param_1 & 0x1b;
    }
  }
  else {
    FUN_10019ad0();
    uVar4 = param_1 & 0x17;
  }
LAB_1001974b:
  if (((param_1 & 0x10) != 0) && ((param_3 & 0x20) != 0)) {
    FUN_10019ad0();
    uVar4 = uVar4 & 0xffffffef;
  }
  return uVar4 == 0;
}
#undef local_10
#undef local_14


/* ---- 0x1001ad40  _pow_special_cases ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _pow_special_cases(double param_1,double param_2,double *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  double dVar3;
  int iVar4;
  
  dVar3 = param_1;
  if (param_1 < 0.0) {
    param_1 = -param_1;
  }
  if (param_2 == INFINITY) {
    if (1.0 < param_1) {
      *(undefined4 *)param_3 = DAT_100296a8;
      *(undefined4 *)((int)param_3 + 4) = DAT_100296ac;
      return 0;
    }
    if (param_1 < 1.0) {
      *(undefined4 *)param_3 = 0;
      *(undefined4 *)((int)param_3 + 4) = 0;
      return 0;
    }
  }
  else {
    if (param_2 != -INFINITY) {
      if (dVar3 == INFINITY) {
        if (0.0 < param_2) {
          *(undefined4 *)param_3 = DAT_100296a8;
          *(undefined4 *)((int)param_3 + 4) = DAT_100296ac;
          return 0;
        }
        *(undefined4 *)param_3 = 0;
        if (param_2 < 0.0) {
          *(undefined4 *)((int)param_3 + 4) = 0;
          return 0;
        }
      }
      else {
        if (dVar3 != -INFINITY) {
          return 0;
        }
        iVar4 = _is_integer_double(param_2);
        uVar2 = DAT_100296cc;
        uVar1 = DAT_100296ac;
        if (0.0 < param_2) {
          if (iVar4 != 1) {
            *(undefined4 *)param_3 = DAT_100296a8;
            *(undefined4 *)((int)param_3 + 4) = uVar1;
            return 0;
          }
          *param_3 = -(double)CONCAT44(DAT_100296ac,DAT_100296a8);
          return 0;
        }
        if (param_2 < 0.0) {
          if (iVar4 != 1) {
            *(undefined4 *)param_3 = 0;
            *(undefined4 *)((int)param_3 + 4) = 0;
            return 0;
          }
          *(undefined4 *)param_3 = DAT_100296c8;
          *(undefined4 *)((int)param_3 + 4) = uVar2;
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
      *(undefined4 *)param_3 = DAT_100296a8;
      *(undefined4 *)((int)param_3 + 4) = DAT_100296ac;
      return 0;
    }
  }
  *(undefined4 *)param_3 = DAT_100296b0;
  *(undefined4 *)((int)param_3 + 4) = DAT_100296b4;
  return 1;
}

/* ---- 0x1001af70  _is_integer_double ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _is_integer_double(double param_1)

{
  uint uVar1;
  float fVar2;
  
  uVar1 = FUN_10020470(PIECE(param_1,0,4),PIECE(param_1,4,4));
  if ((uVar1 & 0x90) == 0) {
    fVar2 = _frnd(param_1);
    if ((double)fVar2 == param_1) {
      fVar2 = _frnd(param_1 / 2.0);
      if (fVar2 == (float)(param_1 / 2.0)) {
        return 2;
      }
      return 1;
    }
  }
  return 0;
}

/* ---- 0x1001b000  __crtGetStringTypeW ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl
__crtGetStringTypeW(int param_1,int param_2,int param_3,undefined4 *param_4,int param_5,int param_6)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 *a5;
  #define local_4 (*(int **)(_frame + (0x20 - 0x4)))
  
  a5 = (undefined4 *)0x0;
  if (DAT_1002c248 == (int *)0x0) {
    iVar2 = GetStringTypeW(1,IMG_ADDR(0x10024958),1,(int)&local_4);
    if (iVar2 == 0) {
      iVar2 = GetStringTypeA(0,1,IMG_ADDR(0x10024954),1,(int)&local_4);
      if (iVar2 == 0) {
        return (int *)0x0;
      }
      DAT_1002c248 = (int *)0x2;
    }
    else {
      DAT_1002c248 = (int *)0x1;
    }
  }
  if (DAT_1002c248 != (int *)0x1) {
    local_4 = DAT_1002c248;
    if (DAT_1002c248 == (int *)0x2) {
      local_4 = (int *)0x0;
      if (param_5 == 0) {
        param_5 = DAT_1002c218;
      }
      iVar2 = WideCharToMultiByte(param_5,0x220,param_2,param_3,0,0,0,0);
      if (iVar2 == 0) {
        return (int *)0x0;
      }
      piVar3 = calloc(1,iVar2);
      if (piVar3 == (int *)0x0) {
        return (int *)0x0;
      }
      iVar4 = WideCharToMultiByte(param_5,0x220,param_2,param_3,(int)piVar3,iVar2,0,0);
      if ((iVar4 != 0) && (a5 = (undefined4 *)malloc(iVar2 * 2 + 2), a5 != (undefined4 *)0x0)) {
        if (param_6 == 0) {
          param_6 = DAT_1002c208;
        }
        uVar1 = param_3 * 2;
        *(undefined2 *)((int)a5 + uVar1) = 0xffff;
        *(undefined2 *)((int)a5 + (uVar1 - 2)) = 0xffff;
        local_4 = (int *)GetStringTypeA(param_6,param_1,(int)piVar3,iVar2,(int)a5);
        if ((*(short *)((int)a5 + (uVar1 - 2)) == -1) || (*(short *)((int)a5 + uVar1) != -1)) {
          local_4 = (int *)0x0;
        }
        else {
          memcpy(param_4,a5,uVar1);
        }
      }
      free((undefined *)piVar3);
      free((undefined *)a5);
    }
    return local_4;
  }
  piVar3 = (int *)GetStringTypeW(param_1,param_2,param_3,(int)param_4);
  return piVar3;
}
#undef local_4


/* ---- 0x1001b190  __crtGetStringTypeA ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl
__crtGetStringTypeA(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                   int param_7)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *a5;
  #define local_2 (*(undefined1 (*)[2])(_frame + (0x20 - 0x2)))
  
  a5 = (int *)0x0;
  if (DAT_1002c24c == 0) {
    iVar1 = GetStringTypeW(1,IMG_ADDR(0x10024958),1,(int)local_2);
    if (iVar1 == 0) {
      iVar1 = GetStringTypeA(0,1,IMG_ADDR(0x10024954),1,(int)local_2);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_1002c24c = 2;
    }
    else {
      DAT_1002c24c = 1;
    }
  }
  if (DAT_1002c24c == 2) {
    if (param_6 == 0) {
      param_6 = DAT_1002c208;
    }
    iVar1 = GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
    return iVar1;
  }
  param_6 = DAT_1002c24c;
  if (DAT_1002c24c == 1) {
    param_6 = 0;
    if (param_5 == 0) {
      param_5 = DAT_1002c218;
    }
    iVar1 = MultiByteToWideChar(param_5,(-(uint)(param_7 != 0) & 8) + 1,param_2,param_3,0,0);
    if (iVar1 != 0) {
      a5 = calloc(2,iVar1);
      if (a5 != (int *)0x0) {
        iVar1 = MultiByteToWideChar(param_5,1,param_2,param_3,(int)a5,iVar1);
        if (iVar1 != 0) {
          iVar1 = GetStringTypeW(param_1,(int)a5,iVar1,param_4);
          free((undefined *)a5);
          return iVar1;
        }
      }
    }
    free((undefined *)a5);
  }
  return param_6;
}
#undef local_2


/* ---- 0x1001b2d0  _input ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _input(int *param_1,byte *param_2,undefined4 *param_3)

{
  unsigned char _frame[0x1e0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte bVar2;
  undefined4 *puVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint uVar8;
  int iVar9;
  byte bVar10;
  byte *pbVar11;
  int iVar12;
  char *pcVar13;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint extraout_EDX_01;
  uint *puVar14;
  char *pcVar15;
  uint *puVar16;
  uint a2;
  bool bVar17;
  bool bVar18;
  int *piVar19;
  #define local_1cd (*(char *)(_frame + (0x1e0 - 0x1cd)))
  #define local_1cc (*(uint *)(_frame + (0x1e0 - 0x1cc)))
  #define local_1c7 (*(char *)(_frame + (0x1e0 - 0x1c7)))
  #define local_1c6 (*(char *)(_frame + (0x1e0 - 0x1c6)))
  #define local_1c5 (*(char *)(_frame + (0x1e0 - 0x1c5)))
  #define local_1c4 (*(int *)(_frame + (0x1e0 - 0x1c4)))
  #define local_1c0 (*(char *)(_frame + (0x1e0 - 0x1c0)))
  #define local_1bf (*(char *)(_frame + (0x1e0 - 0x1bf)))
  #define local_1be (*(char *)(_frame + (0x1e0 - 0x1be)))
  #define local_1bd (*(byte *)(_frame + (0x1e0 - 0x1bd)))
  #define local_1bc (*(uint *)(_frame + (0x1e0 - 0x1bc)))
  #define local_1b8 (*(uint **)(_frame + (0x1e0 - 0x1b8)))
  #define local_1b4 (*(uint *)(_frame + (0x1e0 - 0x1b4)))
  #define local_1b0 (*(int *)(_frame + (0x1e0 - 0x1b0)))
  #define local_1ac (*(int *)(_frame + (0x1e0 - 0x1ac)))
  #define local_1a8 (*(int *)(_frame + (0x1e0 - 0x1a8)))
  #define local_1a4 (*(uint *)(_frame + (0x1e0 - 0x1a4)))
  #define local_19e (*(byte *)(_frame + (0x1e0 - 0x19e)))
  #define local_19d (*(undefined1 *)(_frame + (0x1e0 - 0x19d)))
  #define local_19c (*(uint *)(_frame + (0x1e0 - 0x19c)))
  #define local_198 (*(uint *)(_frame + (0x1e0 - 0x198)))
  #define local_194 (*(undefined4 *)(_frame + (0x1e0 - 0x194)))
  #define local_18e (*(ushort *)(_frame + (0x1e0 - 0x18e)))
  #define local_18c (*(undefined4 **)(_frame + (0x1e0 - 0x18c)))
  #define local_188 (*(int *)(_frame + (0x1e0 - 0x188)))
  #define local_184 (*(undefined4 *)(_frame + (0x1e0 - 0x184)))
  #define local_180 (*(byte (*)[11])(_frame + (0x1e0 - 0x180)))
  #define local_175 (*(undefined1 *)(_frame + (0x1e0 - 0x175)))
  #define local_160 (*(char *)(_frame + (0x1e0 - 0x160)))
  #define local_15f (*(char (*)[351])(_frame + (0x1e0 - 0x15f)))
  
  local_1bf = '\0';
  local_1cc = 0;
  local_1ac = 0;
  bVar10 = *param_2;
  puVar7 = local_18c;
  do {
    if (bVar10 == 0) {
LAB_1001bf26:
      if ((puVar7 == (undefined4 *)0xffffffff) && ((local_1ac == 0 && (local_1bf == '\0')))) {
        local_1ac = -1;
      }
      return local_1ac;
    }
    iVar12 = 0;
    if ((int)DAT_10028b5c < 2) {
      uVar5 = (byte)PTR_DAT_10028950[(uint)bVar10 * 2] & 8;
    }
    else {
      uVar5 = _isctype((uint)bVar10,8);
    }
    if (uVar5 != 0) {
      local_1cc = local_1cc - 1;
      piVar19 = param_1;
      uVar5 = _whiteout((int *)&local_1cc,param_1);
      _un_inc(uVar5,piVar19);
      param_2 = param_2 + 1;
      uVar5 = FUN_1000f620((uint)*param_2);
      while (uVar5 != 0) {
        param_2 = param_2 + 1;
        uVar5 = FUN_1000f620((uint)*param_2);
      }
    }
    if (*param_2 != 0x25) {
      local_1cc = local_1cc + 1;
      puVar7 = (undefined4 *)_inc(param_1);
      if ((undefined4 *)(uint)*param_2 != puVar7) goto LAB_1001bf0d;
      pbVar11 = param_2 + 1;
      if ((PTR_DAT_10028950[((uint)puVar7 & 0xff) * 2 + 1] & 0x80) != 0) {
        local_1cc = local_1cc + 1;
        uVar5 = _inc(param_1);
        if (param_2[1] != uVar5) {
          local_1cc = local_1cc - 1;
          _un_inc(uVar5,param_1);
          goto LAB_1001bf0d;
        }
        local_1cc = local_1cc - 1;
        pbVar11 = param_2 + 2;
      }
      goto LAB_1001bed3;
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
      pbVar11 = param_2 + 1;
      uVar5 = (uint)*pbVar11;
      if ((int)DAT_10028b5c < 2) {
        uVar6 = (byte)PTR_DAT_10028950[uVar5 * 2] & 4;
      }
      else {
        uVar6 = _isctype(uVar5,4);
      }
      if (uVar6 == 0) {
        switch(uVar5) {
        case 0x2a:
          local_1c5 = local_1c5 + '\x01';
          break;
        default:
switchD_1001b450_caseD_2b:
          local_1cd = local_1cd + '\x01';
          break;
        case 0x46:
        case 0x4e:
          break;
        case 0x49:
          if ((param_2[2] != 0x36) || (param_2[3] != 0x34)) goto switchD_1001b450_caseD_2b;
          iVar12 = iVar12 + 1;
          local_19c = 0;
          local_198 = 0;
          pbVar11 = param_2 + 3;
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
      param_2 = pbVar11;
    } while (local_1cd == '\0');
    puVar3 = param_3;
    if (local_1c5 == '\0') {
      local_1b8 = (uint *)*param_3;
      puVar3 = param_3 + 1;
      local_18c = param_3;
    }
    param_3 = puVar3;
    bVar18 = false;
    if ((local_1c7 == '\0') && ((*param_2 == 0x53 || (local_1c7 = -1, *param_2 == 0x43)))) {
      local_1c7 = '\x01';
    }
    local_1bc = *param_2 | 0x20;
    local_188 = iVar12;
    if (local_1bc != 0x6e) {
      if ((local_1bc == 99) || (local_1bc == 0x7b)) {
        local_1cc = local_1cc + 1;
        puVar7 = (undefined4 *)_inc(param_1);
      }
      else {
        puVar7 = (undefined4 *)_whiteout((int *)&local_1cc,param_1);
      }
    }
    puVar14 = local_1b8;
    uVar5 = local_1bc;
    if ((local_1b0 != 0) && (local_1c4 == 0)) {
LAB_1001bf0d:
      local_1cc = local_1cc - 1;
      _un_inc((uint)puVar7,param_1);
      goto LAB_1001bf26;
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
      pcVar13 = &DAT_100298b4;
      goto LAB_1001b5ce;
    case 100:
    case 0x6f:
    case 0x75:
      goto switchD_1001b568_caseD_64;
    case 0x65:
    case 0x66:
    case 0x67:
      pcVar13 = &local_160;
      if (puVar7 == (undefined4 *)0x2d) {
        local_160 = '-';
        pcVar13 = local_15f;
LAB_1001bc13:
        local_1c4 = local_1c4 + -1;
        local_1cc = local_1cc + 1;
        puVar7 = (undefined4 *)_inc(param_1);
      }
      else if (puVar7 == (undefined4 *)0x2b) goto LAB_1001bc13;
      iVar12 = local_1a8;
      if ((local_1b0 == 0) || (0x15d < local_1c4)) {
        local_1c4 = 0x15d;
      }
      while( true ) {
        if ((int)DAT_10028b5c < 2) {
          uVar5 = (byte)PTR_DAT_10028950[(int)puVar7 * 2] & 4;
        }
        else {
          uVar5 = _isctype((int)puVar7,4);
        }
        if ((uVar5 == 0) ||
           (iVar9 = local_1c4 + -1, bVar18 = local_1c4 == 0, local_1c4 = iVar9, bVar18)) break;
        *pcVar13 = (char)puVar7;
        pcVar13 = pcVar13 + 1;
        local_1cc = local_1cc + 1;
        puVar7 = (undefined4 *)_inc(param_1);
        iVar12 = iVar12 + 1;
      }
      if ((DAT_10028b60 == (char)puVar7) &&
         (iVar9 = local_1c4 + -1, bVar18 = local_1c4 != 0, local_1c4 = iVar9, bVar18)) {
        local_1cc = local_1cc + 1;
        puVar7 = (undefined4 *)_inc(param_1);
        *pcVar13 = DAT_10028b60;
        while( true ) {
          pcVar13 = pcVar13 + 1;
          if ((int)DAT_10028b5c < 2) {
            uVar5 = (byte)PTR_DAT_10028950[(int)puVar7 * 2] & 4;
          }
          else {
            uVar5 = _isctype((int)puVar7,4);
          }
          if ((uVar5 == 0) ||
             (iVar9 = local_1c4 + -1, bVar18 = local_1c4 == 0, local_1c4 = iVar9, bVar18)) break;
          *pcVar13 = (char)puVar7;
          iVar12 = iVar12 + 1;
          local_1cc = local_1cc + 1;
          puVar7 = (undefined4 *)_inc(param_1);
        }
      }
      pcVar15 = pcVar13;
      if ((iVar12 != 0) &&
         (((puVar7 == (undefined4 *)0x65 || (puVar7 == (undefined4 *)0x45)) &&
          (iVar9 = local_1c4 + -1, bVar18 = local_1c4 != 0, local_1c4 = iVar9, bVar18)))) {
        *pcVar13 = 'e';
        pcVar15 = pcVar13 + 1;
        local_1cc = local_1cc + 1;
        puVar7 = (undefined4 *)_inc(param_1);
        if (puVar7 == (undefined4 *)0x2d) {
          *pcVar15 = '-';
          pcVar15 = pcVar13 + 2;
LAB_1001bd6e:
          iVar9 = local_1c4 + -1;
          if (local_1c4 != 0) goto LAB_1001bd83;
        }
        else if (puVar7 == (undefined4 *)0x2b) goto LAB_1001bd6e;
        while( true ) {
          if ((int)DAT_10028b5c < 2) {
            uVar5 = (byte)PTR_DAT_10028950[(int)puVar7 * 2] & 4;
          }
          else {
            uVar5 = _isctype((int)puVar7,4);
          }
          if ((uVar5 == 0) ||
             (iVar9 = local_1c4 + -1, bVar18 = local_1c4 == 0, local_1c4 = iVar9, bVar18)) break;
          iVar12 = iVar12 + 1;
          *pcVar15 = (char)puVar7;
          pcVar15 = pcVar15 + 1;
LAB_1001bd83:
          local_1c4 = iVar9;
          local_1cc = local_1cc + 1;
          puVar7 = (undefined4 *)_inc(param_1);
        }
      }
      local_1cc = local_1cc - 1;
      _un_inc((uint)puVar7,param_1);
      if (iVar12 == 0) goto LAB_1001bf26;
      if (local_1c5 == '\0') {
        local_1ac = local_1ac + 1;
        *pcVar15 = '\0';
        (*(code *)PTR_FUN_10028b80)(local_1c6 + -1,local_1b8,&local_160);
      }
      break;
    default:
      if ((undefined4 *)(uint)*param_2 != puVar7) goto LAB_1001bf0d;
      local_1bf = local_1bf + -1;
      if (local_1c5 == '\0') {
        param_3 = local_18c;
      }
      break;
    case 0x69:
      local_1bc = 100;
    case 0x78:
      uVar5 = local_1bc;
      if (puVar7 == (undefined4 *)0x2d) {
        local_1be = '\x01';
LAB_1001b822:
        local_1c4 = local_1c4 + -1;
        if ((local_1c4 == 0) && (local_1b0 != 0)) {
          bVar18 = true;
        }
        else {
          local_1cc = local_1cc + 1;
          puVar7 = (undefined4 *)_inc(param_1);
        }
      }
      else if (puVar7 == (undefined4 *)0x2b) goto LAB_1001b822;
      if (puVar7 == (undefined4 *)0x30) {
        local_1cc = local_1cc + 1;
        puVar7 = (undefined4 *)_inc(param_1);
        if (((char)puVar7 == 'x') || ((char)puVar7 == 'X')) {
          local_1cc = local_1cc + 1;
          puVar7 = (undefined4 *)_inc(param_1);
          uVar5 = 0x78;
          local_1bc = 0x78;
        }
        else {
          local_1a8 = 1;
          if (uVar5 == 0x78) {
            local_1cc = local_1cc - 1;
            _un_inc((uint)puVar7,param_1);
            puVar7 = (undefined4 *)0x30;
          }
          else {
            uVar5 = 0x6f;
            local_1bc = 0x6f;
          }
        }
      }
      goto LAB_1001b904;
    case 0x6e:
      uVar5 = local_1cc;
      if (local_1c5 != '\0') break;
      goto LAB_1001bbc5;
    case 0x70:
      local_1c6 = '\x01';
switchD_1001b568_caseD_64:
      if (puVar7 == (undefined4 *)0x2d) {
        local_1be = '\x01';
LAB_1001b8da:
        local_1c4 = local_1c4 + -1;
        if ((local_1c4 == 0) && (local_1b0 != 0)) {
          bVar18 = true;
        }
        else {
          local_1cc = local_1cc + 1;
          puVar7 = (undefined4 *)_inc(param_1);
        }
      }
      else if (puVar7 == (undefined4 *)0x2b) goto LAB_1001b8da;
LAB_1001b904:
      uVar6 = local_1a4;
      uVar8 = local_19c;
      a2 = local_198;
      if (iVar12 == 0) {
        while (!bVar18) {
          if ((uVar5 == 0x78) || (uVar5 == 0x70)) {
            if ((int)DAT_10028b5c < 2) {
              uVar8 = (byte)PTR_DAT_10028950[(int)puVar7 * 2] & 0x80;
            }
            else {
              uVar8 = _isctype((int)puVar7,0x80);
            }
            if (uVar8 != 0) {
              uVar6 = uVar6 << 4;
              puVar7 = (undefined4 *)_hextodec((uint)puVar7);
              goto LAB_1001bafa;
            }
LAB_1001baf6:
            bVar18 = true;
          }
          else {
            if ((int)DAT_10028b5c < 2) {
              uVar8 = (byte)PTR_DAT_10028950[(int)puVar7 * 2] & 4;
            }
            else {
              uVar8 = _isctype((int)puVar7,4);
            }
            if (uVar8 == 0) goto LAB_1001baf6;
            if (uVar5 == 0x6f) {
              if (0x37 < (int)puVar7) goto LAB_1001baf6;
              uVar6 = uVar6 << 3;
            }
            else {
              uVar6 = uVar6 * 10;
            }
          }
LAB_1001bafa:
          if (bVar18) {
            local_1cc = local_1cc - 1;
            _un_inc((uint)puVar7,param_1);
          }
          else {
            local_1a8 = local_1a8 + 1;
            uVar6 = (uVar6 - 0x30) + (int)puVar7;
            if ((local_1b0 == 0) || (local_1c4 = local_1c4 + -1, local_1c4 != 0)) {
              local_1cc = local_1cc + 1;
              puVar7 = (undefined4 *)_inc(param_1);
            }
            else {
              bVar18 = true;
            }
          }
        }
        local_1a4 = uVar6;
        if (local_1be != '\0') {
          local_1a4 = -uVar6;
        }
      }
      else {
        while (!bVar18) {
          if (local_1bc == 0x78) {
            if ((int)DAT_10028b5c < 2) {
              uVar5 = (byte)PTR_DAT_10028950[(int)puVar7 * 2] & 0x80;
            }
            else {
              uVar5 = _isctype((int)puVar7,0x80);
            }
            if (uVar5 != 0) {
              uVar8 = FUN_100206d0(4,a2);
              puVar7 = (undefined4 *)_hextodec((uint)puVar7);
              a2 = extraout_EDX;
              goto LAB_1001b9d1;
            }
LAB_1001b9cd:
            bVar18 = true;
          }
          else {
            if ((int)DAT_10028b5c < 2) {
              uVar5 = (byte)PTR_DAT_10028950[(int)puVar7 * 2] & 4;
            }
            else {
              uVar5 = _isctype((int)puVar7,4);
            }
            if (uVar5 == 0) goto LAB_1001b9cd;
            if (local_1bc == 0x6f) {
              if (0x37 < (int)puVar7) goto LAB_1001b9cd;
              uVar8 = FUN_100206d0(3,a2);
              a2 = extraout_EDX_00;
            }
            else {
              uVar8 = _allmul(uVar8,a2,10,0);
              a2 = extraout_EDX_01;
            }
          }
LAB_1001b9d1:
          if (bVar18) {
            local_1cc = local_1cc - 1;
            _un_inc((uint)puVar7,param_1);
          }
          else {
            puVar3 = puVar7 + -0xc;
            local_1a8 = local_1a8 + 1;
            bVar17 = CARRY4(uVar8,(uint)puVar3);
            uVar8 = uVar8 + (int)puVar3;
            a2 = a2 + ((int)puVar3 >> 0x1f) + (uint)bVar17;
            if ((local_1b0 == 0) || (local_1c4 = local_1c4 + -1, local_1c4 != 0)) {
              local_1cc = local_1cc + 1;
              puVar7 = (undefined4 *)_inc(param_1);
            }
            else {
              bVar18 = true;
            }
          }
        }
        local_19c = uVar8;
        local_198 = a2;
        if (local_1be != '\0') {
          local_19c = -uVar8;
          local_198 = -(a2 + (uVar8 != 0));
        }
      }
      iVar12 = local_1a8;
      if (local_1bc == 0x46) {
        iVar12 = 0;
      }
      if (iVar12 == 0) goto LAB_1001bf26;
      if (local_1c5 == '\0') {
        local_1ac = local_1ac + 1;
        uVar5 = local_1a4;
        iVar12 = local_188;
LAB_1001bbc5:
        if (iVar12 == 0) {
          if (local_1c6 == '\0') {
            *(short *)local_1b8 = (short)uVar5;
          }
          else {
            *local_1b8 = uVar5;
          }
        }
        else {
          *local_1b8 = local_19c;
          local_1b8[1] = local_198;
        }
      }
      break;
    case 0x73:
      if ('\0' < local_1c7) {
        local_1c0 = '\x01';
      }
      pcVar13 = s_____100298ac;
LAB_1001b5ce:
      local_1bd = 0xff;
      pbVar11 = param_2;
LAB_1001b5d3:
      param_2 = pbVar11;
      pbVar11 = local_180;
      for (iVar12 = 8; iVar12 != 0; iVar12 = iVar12 + -1) {
        pbVar11[0] = 0;
        pbVar11[1] = 0;
        pbVar11[2] = 0;
        pbVar11[3] = 0;
        pbVar11 = pbVar11 + 4;
      }
      if ((local_1bc == 0x7b) && (*pcVar13 == 0x5d)) {
        local_1b4 = CONCAT31(PIECE(local_1b4,1,3),0x5d);
        pcVar13 = pcVar13 + 1;
        local_175 = 0x20;
      }
      bVar10 = *pcVar13;
      uVar5 = local_1b4;
      while (bVar10 != 0x5d) {
        pbVar11 = (byte *)(pcVar13 + 1);
        uVar6 = (uint)local_184 >> 8;
        local_184 = CONCAT31((int3)uVar6,bVar10);
        PIECE(local_1b4,1,3) = (undefined3)(uVar5 >> 8);
        if (((bVar10 == 0x2d) &&
            (PIECE(local_1b4,0,1) = (byte)uVar5, bVar2 = (byte)local_1b4, (byte)local_1b4 != 0)) &&
           (bVar1 = *pbVar11, bVar1 != 0x5d)) {
          pbVar11 = (byte *)(pcVar13 + 2);
          uVar6 = (uint)local_194 >> 8;
          bVar10 = (byte)local_1b4;
          if (bVar1 <= (byte)local_1b4) {
            local_1b4 = CONCAT31(PIECE(local_1b4,1,3),bVar1);
            bVar10 = bVar1;
            uVar5 = local_1b4;
            bVar1 = bVar2;
          }
          local_1b4 = uVar5;
          local_194 = CONCAT31((int3)uVar6,bVar1);
          if (bVar10 <= bVar1) {
            uVar5 = local_1b4 & 0xff;
            iVar12 = (bVar1 - uVar5) + 1;
            do {
              uVar6 = uVar5 >> 3;
              bVar10 = (byte)uVar5;
              uVar5 = uVar5 + 1;
              iVar12 = iVar12 + -1;
              local_180[uVar6] = local_180[uVar6] | '\x01' << (bVar10 & 7);
            } while (iVar12 != 0);
          }
          local_1b4 = local_1b4 & 0xffffff00;
        }
        else {
          local_1b4 = CONCAT31(PIECE(local_1b4,1,3),bVar10);
          local_180[bVar10 >> 3] = local_180[bVar10 >> 3] | '\x01' << (bVar10 & 7);
        }
        pcVar13 = (char *)pbVar11;
        uVar5 = local_1b4;
        bVar10 = *pbVar11;
      }
      if (*pcVar13 == 0) goto LAB_1001bf26;
      if (local_1bc == 0x7b) {
        param_2 = (byte *)pcVar13;
      }
      local_1cc = local_1cc - 1;
      local_1b4 = uVar5;
      _un_inc((uint)puVar7,param_1);
      puVar16 = puVar14;
      while( true ) {
        if ((local_1b0 != 0) &&
           (iVar12 = local_1c4 + -1, bVar18 = local_1c4 == 0, local_1c4 = iVar12, puVar4 = puVar16,
           bVar18)) goto LAB_1001b7bc;
        local_1cc = local_1cc + 1;
        puVar7 = (undefined4 *)_inc(param_1);
        if ((puVar7 == (undefined4 *)0xffffffff) ||
           (bVar10 = (byte)puVar7,
           ((int)(char)(local_180[(int)puVar7 >> 3] ^ local_1bd) & 1 << (bVar10 & 7)) == 0)) break;
        if (local_1c5 == '\0') {
          if (local_1c0 == '\0') {
            *(byte *)puVar16 = bVar10;
            puVar16 = (uint *)((int)puVar16 + 1);
          }
          else {
            local_19e = bVar10;
            if ((PTR_DAT_10028950[((uint)puVar7 & 0xff) * 2 + 1] & 0x80) != 0) {
              local_1cc = local_1cc + 1;
              uVar5 = _inc(param_1);
              local_19d = (undefined1)uVar5;
            }
            mbtowc(&local_18e,&local_19e,DAT_10028b5c);
            *(ushort *)puVar16 = local_18e;
            puVar16 = (uint *)((int)puVar16 + 2);
          }
        }
        else {
          puVar14 = (uint *)((int)puVar14 + 1);
        }
      }
      local_1cc = local_1cc - 1;
      local_1b8 = puVar16;
      _un_inc((uint)puVar7,param_1);
      puVar4 = local_1b8;
LAB_1001b7bc:
      local_1b8 = puVar4;
      if (puVar14 == puVar16) goto LAB_1001bf26;
      if ((local_1c5 == '\0') && (local_1ac = local_1ac + 1, local_1bc != 99)) {
        if (local_1c0 == '\0') {
          *(byte *)local_1b8 = 0;
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
      pbVar11 = param_2 + 1;
      pcVar13 = (char *)pbVar11;
      if (*pbVar11 == 0x5e) {
        pcVar13 = (char *)(param_2 + 2);
        param_2 = pbVar11;
        goto LAB_1001b5ce;
      }
      goto LAB_1001b5d3;
    }
    local_1bf = local_1bf + '\x01';
    pbVar11 = param_2 + 1;
LAB_1001bed3:
    param_2 = pbVar11;
    if ((puVar7 == (undefined4 *)0xffffffff) && ((*param_2 != 0x25 || (param_2[1] != 0x6e))))
    goto LAB_1001bf26;
    bVar10 = *param_2;
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

#endif


/* ---- 0x1001c010  _hextodec ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _hextodec(uint param_1)

{
  uint uVar1;
  
  if (DAT_10028b5c < 2) {
    uVar1 = (byte)PTR_DAT_10028950[param_1 * 2] & 4;
  }
  else {
    uVar1 = _isctype(param_1,4);
  }
  if (uVar1 == 0) {
    param_1 = (param_1 & 0xffffffdf) - 7;
  }
  return param_1;
}

/* ---- 0x1001c050  _inc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _inc(int *param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = param_1[1];
  param_1[1] = iVar2 + -1;
  if (-1 < iVar2 + -1) {
    bVar1 = *(byte *)*param_1;
    *param_1 = (int)((byte *)*param_1 + 1);
    return (uint)bVar1;
  }
  uVar3 = _filbuf(param_1);
  return uVar3;
}

/* ---- 0x1001c080  _un_inc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _un_inc(uint param_1,int *param_2)

{
  if (param_1 != 0xffffffff) {
    _ungetc_lk(param_1,param_2);
  }
  return;
}

/* ---- 0x1001c0a0  _whiteout ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _whiteout(int *param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  
  *param_1 = *param_1 + 1;
  uVar1 = _inc(param_2);
  uVar2 = FUN_1000f620(uVar1);
  while (uVar2 != 0) {
    *param_1 = *param_1 + 1;
    uVar1 = _inc(param_2);
    uVar2 = FUN_1000f620(uVar1);
  }
  return uVar1;
}

/* ---- 0x1001c0f0  __crtCompareStringA ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl
__crtCompareStringA(int param_1,int param_2,byte *param_3,int param_4,byte *param_5,int param_6,
                   int param_7)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  byte *pbVar3;
  undefined *a5;
  int iVar4;
  #define iStack_18 (*(int *)(_frame + (0x30 - 0x18)))
  #define uStack_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define abStack_e (*(byte (*)[14])(_frame + (0x30 - 0xe)))
  
  if (DAT_1002c254 == 0) {
    iVar1 = CompareStringW(0,0,IMG_ADDR(0x10024958),1,IMG_ADDR(0x10024958),1);
    if (iVar1 == 0) {
      iVar1 = CompareStringA(0,0,IMG_ADDR(0x10024954),1,IMG_ADDR(0x10024954),1);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_1002c254 = 2;
    }
    else {
      DAT_1002c254 = 1;
    }
  }
  iVar1 = param_4;
  if (0 < param_4) {
    iVar1 = _strncnt((char *)param_3,param_4);
  }
  if (0 < param_6) {
    param_6 = _strncnt((char *)param_5,param_6);
  }
  if (DAT_1002c254 == 2) {
    iVar1 = CompareStringA(param_1,param_2,(int)param_3,iVar1,(int)param_5,param_6);
    return iVar1;
  }
  iStack_18 = DAT_1002c254;
  if (DAT_1002c254 == 1) {
    iStack_18 = 0;
    param_4 = 0;
    if (param_7 == 0) {
      param_7 = DAT_1002c218;
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
      iVar2 = GetCPInfo(param_7,(int)&uStack_14);
      if (iVar2 == 0) {
        return 0;
      }
      if (0 < iVar1) {
        if (uStack_14 < 2) {
          return 3;
        }
        pbVar3 = abStack_e;
        while( true ) {
          if ((abStack_e[0] == 0) || (pbVar3[1] == 0)) {
            return 3;
          }
          if ((*pbVar3 <= *param_3) && (*param_3 <= pbVar3[1])) break;
          abStack_e[0] = pbVar3[2];
          pbVar3 = pbVar3 + 2;
        }
        return 2;
      }
      if (0 < param_6) {
        if (uStack_14 < 2) {
          return 1;
        }
        pbVar3 = abStack_e;
        while( true ) {
          if ((abStack_e[0] == 0) || (pbVar3[1] == 0)) {
            return 1;
          }
          if ((*pbVar3 <= *param_5) && (*param_5 <= pbVar3[1])) break;
          abStack_e[0] = pbVar3[2];
          pbVar3 = pbVar3 + 2;
        }
        return 2;
      }
    }
    iVar2 = MultiByteToWideChar(param_7,9,(int)param_3,iVar1,0,0);
    if (iVar2 == 0) {
      return 0;
    }
    a5 = (undefined *)malloc(iVar2 * 2);
    if (a5 == (undefined *)0x0) {
      return 0;
    }
    iVar1 = MultiByteToWideChar(param_7,1,(int)param_3,iVar1,(int)a5,iVar2);
    if ((((iVar1 != 0) &&
         (iVar1 = MultiByteToWideChar(param_7,9,(int)param_5,param_6,0,0), iVar1 != 0)) &&
        (param_4 = malloc(iVar1 * 2), param_4 != 0)) &&
       (iVar4 = MultiByteToWideChar(param_7,1,(int)param_5,param_6,param_4,iVar1), iVar4 != 0)) {
      iStack_18 = CompareStringW(param_1,param_2,(int)a5,iVar2,param_4,iVar1);
    }
    free(a5);
    free((undefined *)param_4);
  }
  return iStack_18;
}
#undef abStack_e
#undef iStack_18
#undef uStack_14


/* ---- 0x1001c3c0  _strncnt ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _strncnt(char *param_1,int param_2)

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

/* ---- 0x1001c3f0  wcstol ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl wcstol(short *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = wcstoxl(param_1,param_2,param_3,0);
  return uVar1;
}

/* ---- 0x1001c410  wcstoxl ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl wcstoxl(short *param_1,undefined4 *param_2,uint param_3,uint param_4)

{
  short *psVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  undefined4 unaff_ESI;
  uint uVar6;
  undefined2 uVar7;
  short *psVar8;
  
  uVar5 = 0;
  uVar6 = CONCAT22((short)((uint)unaff_ESI >> 0x10),*param_1);
  uVar2 = iswctype(uVar6,8);
  psVar1 = param_1;
  while( true ) {
    psVar8 = psVar1 + 1;
    uVar7 = (undefined2)(uVar6 >> 0x10);
    if (uVar2 == 0) break;
    uVar6 = CONCAT22(uVar7,*psVar8);
    uVar2 = iswctype(uVar6,8);
    psVar1 = psVar8;
  }
  if ((short)uVar6 == 0x2d) {
    param_4 = param_4 | 2;
  }
  else if ((short)uVar6 != 0x2b) goto LAB_1001c45d;
  uVar6 = CONCAT22(uVar7,*psVar8);
  psVar8 = psVar1 + 2;
LAB_1001c45d:
  if ((((int)param_3 < 0) || (param_3 == 1)) || (0x24 < (int)param_3)) {
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = param_1;
    }
    return 0;
  }
  if (param_3 == 0) {
    if ((short)uVar6 == 0x30) {
      if ((*psVar8 == 0x78) || (param_3 = 8, *psVar8 == 0x58)) {
        param_3 = 0x10;
      }
    }
    else {
      param_3 = 10;
    }
  }
  if (((param_3 == 0x10) && ((short)uVar6 == 0x30)) && ((*psVar8 == 0x78 || (*psVar8 == 0x58)))) {
    uVar6 = CONCAT22((short)(uVar6 >> 0x10),psVar8[1]);
    psVar8 = psVar8 + 2;
  }
  uVar2 = (uint)(0xffffffff / (ulonglong)param_3);
  do {
    uVar3 = iswctype(uVar6,4);
    if (uVar3 == 0) {
      uVar3 = iswctype(uVar6,0x103);
      if (uVar3 == 0) {
LAB_1001c55b:
        psVar8 = psVar8 + -1;
        if ((param_4 & 8) == 0) {
          if (param_2 != (undefined4 *)0x0) {
            psVar8 = param_1;
          }
          uVar5 = 0;
        }
        else if (((param_4 & 4) != 0) ||
                (((param_4 & 1) == 0 &&
                 ((((param_4 & 2) != 0 && (0x80000000 < uVar5)) ||
                  (((param_4 & 2) == 0 && (0x7fffffff < uVar5)))))))) {
          piVar4 = _errno();
          *piVar4 = 0x22;
          if ((param_4 & 1) == 0) {
            uVar5 = ((param_4 & 2) != 0) + 0x7fffffff;
          }
          else {
            uVar5 = 0xffffffff;
          }
        }
        if (param_2 != (undefined4 *)0x0) {
          *param_2 = psVar8;
        }
        if ((param_4 & 2) != 0) {
          uVar5 = -uVar5;
        }
        return uVar5;
      }
      uVar6 = toupper(uVar6);
      uVar6 = (uVar6 & 0xffff) - 0x37;
    }
    else {
      uVar6 = (uVar6 & 0xffff) - 0x30;
    }
    if (param_3 <= uVar6) goto LAB_1001c55b;
    uVar7 = (undefined2)(uVar6 >> 0x10);
    if ((uVar5 < uVar2) || ((uVar5 == uVar2 && (uVar6 <= (uint)(0xffffffff % (ulonglong)param_3)))))
    {
      uVar5 = uVar5 * param_3 + uVar6;
      uVar6 = CONCAT22(uVar7,*psVar8);
      psVar8 = psVar8 + 1;
      param_4 = param_4 | 8;
    }
    else {
      uVar6 = CONCAT22(uVar7,*psVar8);
      psVar8 = psVar8 + 1;
      param_4 = param_4 | 0xc;
    }
  } while( true );
}
#endif


/* ---- 0x1001c5f0  __crtGetLocaleInfoA ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl __crtGetLocaleInfoA(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  uint a4;
  undefined *a3;
  
  if (DAT_1002c258 == 0) {
    iVar1 = GetLocaleInfoW(0,1,0,0);
    if (iVar1 == 0) {
      iVar1 = GetLocaleInfoA(0,1,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_1002c258 = 2;
    }
    else {
      DAT_1002c258 = 1;
    }
  }
  if (DAT_1002c258 == 1) {
    iVar1 = GetLocaleInfoW(param_1,param_2,param_3,param_4);
    return iVar1;
  }
  if (DAT_1002c258 != 2) {
    return DAT_1002c258;
  }
  if (param_5 == 0) {
    param_5 = DAT_1002c218;
  }
  a4 = GetLocaleInfoA(param_1,param_2,0,0);
  if (a4 != 0) {
    a3 = (undefined *)malloc(a4);
    if (a3 == (undefined *)0x0) {
      return 0;
    }
    iVar1 = GetLocaleInfoA(param_1,param_2,(int)a3,a4);
    if (iVar1 != 0) {
      if (param_4 == 0) {
        iVar1 = MultiByteToWideChar(param_5,1,(int)a3,-1,0,0);
        if (iVar1 != 0) {
          free(a3);
          return iVar1;
        }
      }
      else {
        iVar1 = MultiByteToWideChar(param_5,1,(int)a3,-1,param_3,param_4);
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

/* ---- 0x1001c860  _setenvp ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _setenvp(void)

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
  cVar2 = *DAT_1002c010;
  pcVar7 = DAT_1002c010;
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
  DAT_1002c0a8 = piVar3;
  if (piVar3 == (int *)0x0) {
    _amsg_exit(9);
  }
  cVar2 = *DAT_1002c010;
  local_4 = piVar3;
  pcVar7 = DAT_1002c010;
  do {
    if (cVar2 == '\0') {
      free(DAT_1002c010);
      DAT_1002c010 = (char *)0x0;
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


/* ---- 0x1001c950  _setargv ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _setargv(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  byte *pbVar2;
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  GetModuleFileNameA(0,IMG_ADDR(0x1002c260),0x104);
  _DAT_1002c0b8 = &DAT_1002c260;
  pbVar2 = DAT_1002c704;
  if (*DAT_1002c704 == 0) {
    pbVar2 = &DAT_1002c260;
  }
  parse_cmdline(pbVar2,(undefined4 *)0x0,(byte *)0x0,&iStack_8,&iStack_4);
  puVar1 = (undefined4 *)malloc(iStack_4 + iStack_8 * 4);
  if (puVar1 == (undefined4 *)0x0) {
    _amsg_exit(8);
  }
  parse_cmdline(pbVar2,puVar1,(byte *)(puVar1 + iStack_8),&iStack_8,&iStack_4);
  _DAT_1002c0a0 = puVar1;
  _DAT_1002c09c = iStack_8 + -1;
  return;
}
#undef iStack_4
#undef iStack_8


/* ---- 0x1001cc00  _setmbcp ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _setmbcp(int param_1)

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
  a1 = getSystemCP(param_1);
  if (a1 == DAT_1002c570) {
    _unlock(0x19);
    return 0;
  }
  if (a1 == 0) {
    setSBCS();
    setSBUpLow();
    _unlock(0x19);
    return 0;
  }
  iVar8 = 0;
  piVar4 = &DAT_100298c0;
  do {
    if (*piVar4 == a1) {
      puVar11 = &DAT_1002c368;
      for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar11 = 0;
        puVar11 = puVar11 + 1;
      }
      *(undefined1 *)puVar11 = 0;
      uVar5 = 0;
      iVar8 = iVar8 * 0x30;
      pbVar9 = (byte *)(iVar8 + IMG_ADDR(0x100298d0));
      do {
        bVar2 = *pbVar9;
        for (pbVar10 = pbVar9; (bVar2 != 0 && (bVar2 = pbVar10[1], bVar2 != 0));
            pbVar10 = pbVar10 + 2) {
          uVar6 = (uint)*pbVar10;
          if (uVar6 <= bVar2) {
            bVar3 = (&DAT_100298b8)[uVar5];
            do {
              pbVar1 = (byte *)((int)&DAT_1002c368 + uVar6 + 1);
              *pbVar1 = *pbVar1 | bVar3;
              uVar6 = uVar6 + 1;
            } while (uVar6 <= bVar2);
          }
          bVar2 = pbVar10[2];
        }
        uVar5 = uVar5 + 1;
        pbVar9 = pbVar9 + 8;
      } while (uVar5 < 4);
      _DAT_1002c5d8 = 1;
      DAT_1002c570 = a1;
      DAT_1002c574 = FUN_1001ce80(a1);
      _DAT_1002c578 = *(undefined4 *)(iVar8 + IMG_ADDR(0x100298c4));
      _DAT_1002c57c = *(undefined4 *)(iVar8 + IMG_ADDR(0x100298c8));
      _DAT_1002c580 = *(undefined4 *)(iVar8 + IMG_ADDR(0x100298cc));
      goto LAB_1001cd52;
    }
    piVar4 = piVar4 + 0xc;
    iVar8 = iVar8 + 1;
  } while (piVar4 < &DAT_100299b0);
  iVar8 = GetCPInfo(a1,(int)&local_14);
  if (iVar8 == 1) {
    puVar11 = &DAT_1002c368;
    for (iVar8 = 0x40; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar11 = 0;
      puVar11 = puVar11 + 1;
    }
    *(undefined1 *)puVar11 = 0;
    DAT_1002c574 = 0;
    if (local_14 < 2) {
      _DAT_1002c5d8 = 0;
      DAT_1002c570 = a1;
    }
    else {
      DAT_1002c570 = a1;
      if (abStack_e[0] != 0) {
        pbVar9 = abStack_e + 1;
        do {
          bVar2 = *pbVar9;
          if (bVar2 == 0) break;
          for (uVar5 = (uint)pbVar9[-1]; uVar5 <= bVar2; uVar5 = uVar5 + 1) {
            *(byte *)((int)&DAT_1002c368 + uVar5 + 1) =
                 *(byte *)((int)&DAT_1002c368 + uVar5 + 1) | 4;
          }
          pbVar10 = pbVar9 + 1;
          pbVar9 = pbVar9 + 2;
        } while (*pbVar10 != 0);
      }
      uVar5 = 1;
      do {
        *(byte *)((int)&DAT_1002c368 + uVar5 + 1) = *(byte *)((int)&DAT_1002c368 + uVar5 + 1) | 8;
        uVar5 = uVar5 + 1;
      } while (uVar5 < 0xff);
      DAT_1002c574 = FUN_1001ce80(a1);
      _DAT_1002c5d8 = 1;
    }
    _DAT_1002c578 = 0;
    _DAT_1002c57c = 0;
    _DAT_1002c580 = 0;
  }
  else {
    if (DAT_1002c584 == 0) {
      _unlock(0x19);
      return 0xffffffff;
    }
    setSBCS();
  }
LAB_1001cd52:
  setSBUpLow();
  _unlock(0x19);
  return 0;
}
#undef abStack_e
#undef local_14


/* ---- 0x1001d100  __initmbctable ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __initmbctable(void)

{
  _setmbcp(-3);
  return;
}

/* ---- 0x1001d110  __crtGetEnvironmentStringsA ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

char * __crtGetEnvironmentStringsA(void)

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
  if (DAT_1002c58c == 0) {
    a3 = (short *)GetEnvironmentStringsW();
    if (a3 == (short *)0x0) {
      pcVar9 = (char *)GetEnvironmentStrings();
      if (pcVar9 == (char *)0x0) {
        return (char *)0x0;
      }
      DAT_1002c58c = 2;
    }
    else {
      DAT_1002c58c = 1;
    }
  }
  if (DAT_1002c58c == 1) {
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
        FreeEnvironmentStringsW((int)a3);
        return pcVar9;
      }
      FreeEnvironmentStringsW((int)a3);
      return (char *)0x0;
    }
  }
  else if ((DAT_1002c58c == 2) &&
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
      FreeEnvironmentStringsA((int)pcVar9);
      return pcVar8;
    }
    FreeEnvironmentStringsA((int)pcVar9);
    return (char *)0x0;
  }
  return (char *)0x0;
}

/* ---- 0x1001d270  _heap_init ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 _heap_init(void)

{
  undefined **ppuVar1;
  
  DAT_1002c5d4 = HeapCreate(0,0x1000,0);
  if (DAT_1002c5d4 == 0) {
    return 0;
  }
  ppuVar1 = __sbh_alloc_new_region();
  if (ppuVar1 == (undefined **)0x0) {
    HeapDestroy(DAT_1002c5d4);
    return 0;
  }
  return 1;
}

/* ---- 0x1001d2b0  _heap_term ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _heap_term(void)

{
  undefined **ppuVar1;
  
  ppuVar1 = &PTR_LOOP_10029b00;
  do {
    if (ppuVar1[4] != (undefined *)0x0) {
      VirtualFree((int)ppuVar1[4],0,0x8000);
    }
    ppuVar1 = (undefined **)*ppuVar1;
  } while (ppuVar1 != &PTR_LOOP_10029b00);
  HeapDestroy(DAT_1002c5d4);
  return;
}

/* ---- 0x1001d300  _FF_MSGBANNER ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void _FF_MSGBANNER(void)

{
  if ((DAT_1002c018 == 1) || ((DAT_1002c018 == 0 && (DAT_1002c01c == 1)))) {
    _NMSG_WRITE(0xfc);
    if (DAT_1002c590 != (code *)0x0) {
      (*DAT_1002c590)();
    }
    _NMSG_WRITE(0xff);
  }
  return;
}

/* ---- 0x1001d340  _NMSG_WRITE ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _NMSG_WRITE(int param_1)

{
  unsigned char _frame[0x1c0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  undefined4 *puVar8;
  char *pcVar9;
  undefined4 *puVar10;
  uint *puVar11;
  char *pcVar12;
  char *pcVar13;
  #define local_1a8 (*(undefined1 (*)[4])(_frame + (0x1c0 - 0x1a8)))
  #define acStack_1a4 (*(char (*)[100])(_frame + (0x1c0 - 0x1a4)))
  #define auStack_140 (*(uint (*)[15])(_frame + (0x1c0 - 0x140)))
  #define local_104 (*(undefined4 *)(_frame + (0x1c0 - 0x104)))
  
  piVar2 = &DAT_100299b8;
  iVar7 = 0;
  do {
    if (param_1 == *piVar2) break;
    piVar2 = piVar2 + 2;
    iVar7 = iVar7 + 1;
  } while (piVar2 < &DAT_10029a48);
  if (param_1 == (&DAT_100299b8)[iVar7 * 2]) {
    if ((DAT_1002c018 == 1) || ((DAT_1002c018 == 0 && (DAT_1002c01c == 1)))) {
      if ((PTR_1002c600 == (int *)0x0) || (iVar3 = PTR_1002c600[0x12], iVar3 == -1)) {
        iVar3 = GetStdHandle(-0xc);
      }
      pcVar9 = *(char **)(iVar7 * 8 + IMG_ADDR(0x100299bc));
      uVar4 = 0xffffffff;
      pcVar13 = pcVar9;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar13;
        pcVar13 = pcVar13 + 1;
      } while (cVar1 != '\0');
      WriteFile(iVar3,(int)pcVar9,~uVar4 - 1,(int)local_1a8,0);
    }
    else if (param_1 != 0xfc) {
      iVar3 = GetModuleFileNameA(0,(int)&local_104,0x104);
      if (iVar3 == 0) {
        puVar8 = &DAT_10024d30;
        puVar10 = &local_104;
        for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar10 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar10 = puVar10 + 1;
        }
        *(undefined2 *)puVar10 = *(undefined2 *)puVar8;
        *(undefined1 *)((int)puVar10 + 2) = *(undefined1 *)((int)puVar8 + 2);
      }
      uVar4 = 0xffffffff;
      puVar6 = &local_104;
      pcVar9 = (char *)&local_104;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      if (0x3c < ~uVar4) {
        uVar4 = 0xffffffff;
        pcVar9 = (char *)&local_104;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar9 + 1;
        } while (cVar1 != '\0');
        puVar6 = (uint *)((int)auStack_140 + ~uVar4);
        strncpy(puVar6,(uint *)&DAT_10024d2c,3);
      }
      puVar8 = &DAT_10024d10;
      pcVar9 = acStack_1a4;
      for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined4 *)pcVar9 = *puVar8;
        puVar8 = puVar8 + 1;
        pcVar9 = pcVar9 + 4;
      }
      *(undefined2 *)pcVar9 = *(undefined2 *)puVar8;
      uVar4 = 0xffffffff;
      do {
        puVar11 = puVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        puVar11 = (uint *)((int)puVar6 + 1);
        uVar5 = *puVar6;
        puVar6 = puVar11;
      } while ((char)uVar5 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      pcVar9 = acStack_1a4;
      do {
        pcVar13 = pcVar9;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar13 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar13;
      } while (cVar1 != '\0');
      pcVar9 = (char *)((int)puVar11 - uVar4);
      pcVar13 = pcVar13 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar13 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar4 = 0xffffffff;
      pcVar9 = "\n\n";
      do {
        pcVar13 = pcVar9;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar13 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar13;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar3 = -1;
      pcVar9 = acStack_1a4;
      do {
        pcVar12 = pcVar9;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar12 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar12;
      } while (cVar1 != '\0');
      pcVar9 = pcVar13 + -uVar4;
      pcVar13 = pcVar12 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar13 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar13 = pcVar13 + 1;
      }
      uVar4 = 0xffffffff;
      pcVar9 = *(char **)(iVar7 * 8 + IMG_ADDR(0x100299bc));
      do {
        pcVar13 = pcVar9;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar13 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar13;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar7 = -1;
      pcVar9 = acStack_1a4;
      do {
        pcVar12 = pcVar9;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar12 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar12;
      } while (cVar1 != '\0');
      pcVar9 = pcVar13 + -uVar4;
      pcVar13 = pcVar12 + -1;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar13 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar13 = pcVar13 + 1;
      }
      __crtMessageBoxA(acStack_1a4,"Microsoft Visual C++ Runtime Library",0x12010);
      return;
    }
  }
  return;
}
#undef acStack_1a4
#undef auStack_140
#undef local_104
#undef local_1a8


/* ---- 0x1001d940  _ld12tocvt ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _ld12tocvt(ushort *param_1,uint *param_2,int *param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(int *)(_frame + (0x30 - 0x10)))
  #define local_c (*(undefined4 (*)[3])(_frame + (0x30 - 0xc)))
  
  uVar1 = param_1[5];
  local_14 = *(uint *)(param_1 + 1);
  local_18 = *(uint *)(param_1 + 3);
  uVar4 = uVar1 & 0x7fff;
  iVar5 = uVar4 - 0x3fff;
  local_10 = (uint)*param_1 << 0x10;
  if (iVar5 == -0x3fff) {
    iVar5 = 0;
    iVar2 = FUN_1001d860((int *)&local_18);
    if (iVar2 == 0) {
      FUN_1001d850(&local_18);
      uVar3 = 2;
      goto LAB_1001dac1;
    }
  }
  else {
    FUN_1001d830((int)local_c,&local_18);
    iVar2 = FUN_1001d790((int)&local_18,param_3[2]);
    if (iVar2 != 0) {
      iVar5 = uVar4 - 0x3ffe;
    }
    iVar2 = param_3[1];
    if (iVar5 < iVar2 - param_3[2]) {
      FUN_1001d850(&local_18);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_1001dac1;
    }
    if (iVar5 <= iVar2) {
      FUN_1001d830((int)&local_18,local_c);
      FUN_1001d880(&local_18,iVar2 - iVar5);
      FUN_1001d790((int)&local_18,param_3[2]);
      FUN_1001d880(&local_18,param_3[3] + 1);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_1001dac1;
    }
    if (*param_3 <= iVar5) {
      FUN_1001d850(&local_18);
      local_18 = local_18 | 0x80000000;
      FUN_1001d880(&local_18,param_3[3]);
      iVar5 = param_3[5] + *param_3;
      uVar3 = 1;
      goto LAB_1001dac1;
    }
    iVar5 = param_3[5] + iVar5;
    local_18 = local_18 & 0x7fffffff;
    FUN_1001d880(&local_18,param_3[3]);
  }
  uVar3 = 0;
LAB_1001dac1:
  local_18 = iVar5 << (0x1fU - (char)param_3[3] & 0x1f) |
             -(uint)((uVar1 & 0x8000) != 0) & 0x80000000 | local_18;
  if (param_3[4] == 0x40) {
    param_2[1] = local_18;
    *param_2 = local_14;
    return uVar3;
  }
  if (param_3[4] == 0x20) {
    *param_2 = local_18;
  }
  return uVar3;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_c


/* ---- 0x1001db10  _ld12tod ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _ld12tod(ushort *param_1,uint *param_2)

{
  _ld12tocvt(param_1,param_2,(int *)&DAT_10029a48);
  return;
}

/* ---- 0x1001db30  _ld12tof ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _ld12tof(ushort *param_1,uint *param_2)

{
  _ld12tocvt(param_1,param_2,(int *)&DAT_10029a60);
  return;
}

/* ---- 0x1001db50  _atodbl ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _atodbl(uint *param_1,byte *param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(ushort (*)[6])(_frame + (0x20 - 0xc)))
  
  __strgtold12(local_c,(int *)&param_2,param_2,0,0,0,0);
  _ld12tod(local_c,param_1);
  return;
}
#undef local_c


/* ---- 0x1001db90  _atoflt ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _atoflt(uint *param_1,byte *param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_c (*(ushort (*)[6])(_frame + (0x20 - 0xc)))
  
  __strgtold12(local_c,(int *)&param_2,param_2,0,0,0,0);
  _ld12tof(local_c,param_1);
  return;
}
#undef local_c


/* ---- 0x1001dbd0  _fptostr ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _fptostr(char *param_1,int param_2,int param_3)

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

/* ---- 0x1001de60  _ValidateRead ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

bool __cdecl _ValidateRead(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = IsBadReadPtr(param_1,param_2);
  return iVar1 == 0;
}

/* ---- 0x1001de80  _ValidateWrite ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

bool __cdecl _ValidateWrite(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = IsBadWritePtr(param_1,param_2);
  return iVar1 == 0;
}

/* ---- 0x1001dea0  _ValidateExecute ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

bool __cdecl _ValidateExecute(int param_1)

{
  int iVar1;
  
  iVar1 = IsBadCodePtr(param_1);
  return iVar1 == 0;
}

/* ---- 0x1001dfa0  abort ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void abort(void)

{
  _NMSG_WRITE(10);
  raise((int *)0x16);
  exit(3);
  return;
}

/* ---- 0x1001dfc0  _lseek ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _lseek(uint param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  
  if ((param_1 < DAT_1002c700) &&
     ((*(byte *)((&PTR_1002c600)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    _lock_fhandle(param_1);
    iVar1 = _lseek_lk(param_1,param_2,param_3);
    _unlock_fhandle(param_1);
    return iVar1;
  }
  piVar2 = _errno();
  *piVar2 = 9;
  piVar2 = __doserrno();
  *piVar2 = 0;
  return -1;
}

/* ---- 0x1001e040  _lseek_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _lseek_lk(uint param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  undefined *puVar3;
  
  iVar1 = _get_osfhandle(param_1);
  if (iVar1 == -1) {
    piVar2 = _errno();
    *piVar2 = 9;
    return -1;
  }
  iVar1 = SetFilePointer(iVar1,param_2,0,param_3);
  if (iVar1 == -1) {
    puVar3 = (undefined *)GetLastError();
  }
  else {
    puVar3 = (undefined *)0x0;
  }
  if (puVar3 != (undefined *)0x0) {
    _dosmaperr(puVar3);
    return -1;
  }
  *(byte *)((&PTR_1002c600)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) =
       *(byte *)((&PTR_1002c600)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 0xfd;
  return iVar1;
}

/* ---- 0x1001e0c0  _write ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _write(uint param_1,char *param_2,uint param_3)

{
  int iVar1;
  int *piVar2;
  
  if ((param_1 < DAT_1002c700) &&
     ((*(byte *)((&PTR_1002c600)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    _lock_fhandle(param_1);
    iVar1 = _write_lk(param_1,param_2,param_3);
    _unlock_fhandle(param_1);
    return iVar1;
  }
  piVar2 = _errno();
  *piVar2 = 9;
  piVar2 = __doserrno();
  *piVar2 = 0;
  return -1;
}

/* ---- 0x1001e140  _write_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _write_lk(uint param_1,char *param_2,uint param_3)

{
  unsigned char _frame[0x430] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int **ppiVar1;
  char cVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  int *piVar6;
  char *pcVar7;
  #define local_41c (*(int *)(_frame + (0x430 - 0x41c)))
  #define local_414 (*(undefined **)(_frame + (0x430 - 0x414)))
  #define local_410 (*(int *)(_frame + (0x430 - 0x410)))
  #define local_40c (*(int *)(_frame + (0x430 - 0x40c)))
  #define local_408 (*(int ***)(_frame + (0x430 - 0x408)))
  #define local_404 (*(char (*)[1028])(_frame + (0x430 - 0x404)))
  
  local_41c = 0;
  local_40c = 0;
  if (param_3 == 0) {
    return 0;
  }
  ppiVar1 = &PTR_1002c600 + ((int)param_1 >> 5);
  uVar3 = param_1 & 0x1f;
  local_408 = ppiVar1;
  if ((*(byte *)(*ppiVar1 + uVar3 * 9 + 1) & 0x20) != 0) {
    _lseek_lk(param_1,0,2);
  }
  if ((*(byte *)(*ppiVar1 + uVar3 * 9 + 1) & 0x80) == 0) {
    iVar5 = WriteFile((*ppiVar1)[uVar3 * 9],(int)param_2,param_3,(int)&local_410,0);
    if (iVar5 == 0) {
      local_414 = (undefined *)GetLastError();
    }
    else {
      local_41c = local_410;
      local_414 = (undefined *)0x0;
    }
  }
  else {
    local_414 = (undefined *)0x0;
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
        iVar5 = WriteFile((*local_408)[uVar3 * 9],(int)local_404,(int)pcVar4 - (int)local_404,
                          (int)&local_410,0);
        if (iVar5 == 0) {
          local_414 = (undefined *)GetLastError();
          break;
        }
        local_41c = local_41c + local_410;
        if ((local_410 < (int)pcVar4 - (int)local_404) ||
           (param_3 <= (uint)((int)pcVar7 - (int)param_2))) break;
      } while( true );
    }
  }
  if (local_41c != 0) {
    return local_41c - local_40c;
  }
  if (local_414 == (undefined *)0x0) {
    if (((*(byte *)(*local_408 + uVar3 * 9 + 1) & 0x40) != 0) && (*param_2 == '\x1a')) {
      return 0;
    }
    piVar6 = _errno();
    *piVar6 = 0x1c;
    piVar6 = __doserrno();
    *piVar6 = 0;
    return -1;
  }
  if (local_414 != (undefined *)0x5) {
    _dosmaperr(local_414);
    return -1;
  }
  piVar6 = _errno();
  *piVar6 = 9;
  piVar6 = __doserrno();
  *piVar6 = 5;
  return -1;
}
#undef local_404
#undef local_408
#undef local_40c
#undef local_410
#undef local_414
#undef local_41c


/* ---- 0x1001e350  _getbuf ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _getbuf(int *param_1)

{
  int iVar1;
  
  DAT_1002bf90 = DAT_1002bf90 + 1;
  iVar1 = malloc(0x1000);
  param_1[2] = iVar1;
  if (iVar1 != 0) {
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

/* ---- 0x1001e3b0  _isatty ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

byte __cdecl _isatty(uint param_1)

{
  if (DAT_1002c700 <= param_1) {
    return 0;
  }
  return *(byte *)((&PTR_1002c600)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 0x40;
}

/* ---- 0x1001e3e0  wctomb ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl wctomb(undefined1 *param_1,ushort param_2)

{
  int iVar1;
  bool bVar2;
  
  InterlockedIncrement(IMG_ADDR(0x1002c710));
  bVar2 = DAT_1002c70c != 0;
  if (bVar2) {
    InterlockedDecrement(IMG_ADDR(0x1002c710));
    _lock(0x13);
  }
  iVar1 = _wctomb_lk(param_1,param_2);
  if (!bVar2) {
    InterlockedDecrement(IMG_ADDR(0x1002c710));
    return iVar1;
  }
  _unlock(0x13);
  return iVar1;
}

/* ---- 0x1001e450  _wctomb_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _wctomb_lk(undefined1 *param_1,ushort param_2)

{
  undefined1 *a5;
  int iVar1;
  int *piVar2;
  
  a5 = param_1;
  if (param_1 == (undefined1 *)0x0) {
    return 0;
  }
  if (DAT_1002c208 == 0) {
    if (param_2 < 0x100) {
      *param_1 = (char)param_2;
      return 1;
    }
  }
  else {
    param_1 = (undefined1 *)0x0;
    iVar1 = WideCharToMultiByte(DAT_1002c218,0x220,(int)&param_2,1,(int)a5,DAT_10028b5c,0,
                                (int)&param_1);
    if ((iVar1 != 0) && (param_1 == (undefined1 *)0x0)) {
      return iVar1;
    }
  }
  piVar2 = _errno();
  *piVar2 = 0x2a;
  return -1;
}

/* ---- 0x1001e4d0  _aulldiv ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __stdcall _aulldiv(int a1,int a2,int a3,int a4)

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


/* ---- 0x1001e540  _aullrem ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __stdcall _aullrem(int a1,int a2,int a3,int a4)

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


/* ---- 0x1001e5c0  _callnewh ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _callnewh(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_1002c598 != (code *)0x0) {
    iVar1 = (*DAT_1002c598)(param_1);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}

/* ---- 0x1001e5e0  __sbh_alloc_new_region ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined ** __sbh_alloc_new_region(void)

{
  bool bVar1;
  undefined4 *a1;
  int iVar2;
  undefined **ppuVar3;
  undefined **a3;
  undefined4 *puVar4;
  
  if (DAT_10029b10 == -1) {
    a3 = &PTR_LOOP_10029b00;
  }
  else {
    a3 = (undefined **)HeapAlloc(DAT_1002c5d4,0,0x2020);
    if (a3 == (undefined **)0x0) {
      return (undefined **)0x0;
    }
  }
  a1 = (undefined4 *)VirtualAlloc(0,0x400000,0x2000,4);
  if (a1 != (undefined4 *)0x0) {
    iVar2 = VirtualAlloc((int)a1,0x10000,0x1000,4);
    if (iVar2 != 0) {
      if (a3 == &PTR_LOOP_10029b00) {
        if (PTR_LOOP_10029b00 == (undefined *)0x0) {
          PTR_LOOP_10029b00 = (undefined *)&PTR_LOOP_10029b00;
        }
        if (PTR_LOOP_10029b04 == (undefined *)0x0) {
          PTR_LOOP_10029b04 = (undefined *)&PTR_LOOP_10029b00;
        }
      }
      else {
        *a3 = (undefined *)&PTR_LOOP_10029b00;
        a3[1] = PTR_LOOP_10029b04;
        PTR_LOOP_10029b04 = (undefined *)a3;
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
  if (a3 != &PTR_LOOP_10029b00) {
    HeapFree(DAT_1002c5d4,0,(int)a3);
  }
  return (undefined **)0x0;
}

/* ---- 0x1001e750  __sbh_release_region ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __sbh_release_region(undefined **param_1)

{
  VirtualFree((int)param_1[4],0,0x8000);
  if ((undefined **)PTR_LOOP_1002bb20 == param_1) {
    PTR_LOOP_1002bb20 = param_1[1];
  }
  if (param_1 != &PTR_LOOP_10029b00) {
    *(undefined **)param_1[1] = *param_1;
    *(undefined **)(*param_1 + 4) = param_1[1];
    HeapFree(DAT_1002c5d4,0,(int)param_1);
    return;
  }
  DAT_10029b10 = 0xffffffff;
  return;
}

/* ---- 0x1001e7b0  __sbh_decommit_pages ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __sbh_decommit_pages(int param_1)

{
  int iVar1;
  undefined **ppuVar2;
  int iVar3;
  int iVar4;
  undefined **ppuVar5;
  undefined **ppuVar6;
  
  ppuVar6 = (undefined **)PTR_LOOP_10029b04;
  do {
    ppuVar5 = ppuVar6;
    if (ppuVar6[4] != (undefined *)0xffffffff) {
      iVar4 = 0;
      ppuVar5 = ppuVar6 + 0x804;
      iVar3 = 0x3ff000;
      do {
        if (*ppuVar5 == (undefined *)0xf0) {
          iVar1 = VirtualFree((int)(ppuVar6[4] + iVar3),0x1000,0x4000);
          if (iVar1 != 0) {
            *ppuVar5 = (undefined *)0xffffffff;
            DAT_1002c5a0 = DAT_1002c5a0 + -1;
            if (((undefined **)ppuVar6[3] == (undefined **)0x0) || (ppuVar5 < ppuVar6[3])) {
              ppuVar6[3] = (undefined *)ppuVar5;
            }
            iVar4 = iVar4 + 1;
            param_1 = param_1 + -1;
            if (param_1 == 0) break;
          }
        }
        iVar3 = iVar3 + -0x1000;
        ppuVar5 = ppuVar5 + -2;
      } while (-1 < iVar3);
      ppuVar5 = (undefined **)ppuVar6[1];
      if ((iVar4 != 0) && (ppuVar6[6] == (undefined *)0xffffffff)) {
        iVar3 = 1;
        ppuVar2 = ppuVar6 + 8;
        do {
          if (*ppuVar2 != (undefined *)0xffffffff) break;
          iVar3 = iVar3 + 1;
          ppuVar2 = ppuVar2 + 2;
        } while (iVar3 < 0x400);
        if (iVar3 == 0x400) {
          __sbh_release_region(ppuVar6);
        }
      }
    }
    if ((ppuVar5 == (undefined **)PTR_LOOP_10029b04) || (ppuVar6 = ppuVar5, param_1 < 1)) {
      return;
    }
  } while( true );
}

/* ---- 0x1001e880  __sbh_find_block ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl __sbh_find_block(undefined *param_1,undefined4 *param_2,uint *param_3)

{
  undefined **ppuVar1;
  uint uVar2;
  
  ppuVar1 = &PTR_LOOP_10029b00;
  while ((param_1 <= ppuVar1[4] || (ppuVar1[5] <= param_1))) {
    ppuVar1 = (undefined **)*ppuVar1;
    if (ppuVar1 == &PTR_LOOP_10029b00) {
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

/* ---- 0x1001e8e0  __sbh_free_block ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __sbh_free_block(int param_1,int param_2,byte *param_3)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = param_2 - *(int *)(param_1 + 0x10) >> 0xc;
  piVar1 = (int *)(param_1 + 0x18 + iVar2 * 8);
  *piVar1 = *(int *)(param_1 + 0x18 + iVar2 * 8) + (uint)*param_3;
  *param_3 = 0;
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (DAT_1002c5a0 = DAT_1002c5a0 + 1, DAT_1002c5a0 == 0x20)) {
    __sbh_decommit_pages(0x10);
  }
  return;
}

/* ---- 0x1001e940  __sbh_alloc_block ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl __sbh_alloc_block(uint param_1)

{
  undefined **ppuVar1;
  uint *puVar2;
  undefined **ppuVar3;
  undefined *puVar4;
  int *piVar5;
  undefined **ppuVar6;
  undefined **ppuVar7;
  int *piVar8;
  int iVar9;
  uint *puVar10;
  int *piVar11;
  bool bVar12;
  
  piVar11 = (int *)PTR_LOOP_1002bb20;
  do {
    if (piVar11[4] != -1) {
      puVar10 = (uint *)piVar11[2];
      piVar8 = (int *)(((int)puVar10 + (-0x18 - (int)piVar11) >> 3) * 0x1000 + piVar11[4]);
      for (; puVar10 < piVar11 + 0x806; puVar10 = puVar10 + 2) {
        if (((int)param_1 <= (int)*puVar10) && (param_1 < puVar10[1])) {
          piVar5 = (int *)__sbh_alloc_new_group(piVar8,*puVar10,param_1);
          if (piVar5 != (int *)0x0) {
            PTR_LOOP_1002bb20 = (undefined *)piVar11;
            *puVar10 = *puVar10 - param_1;
            piVar11[2] = (int)puVar10;
            return piVar5;
          }
          puVar10[1] = param_1;
        }
        piVar8 = piVar8 + 0x400;
      }
      puVar2 = (uint *)piVar11[2];
      piVar8 = (int *)piVar11[4];
      for (puVar10 = (uint *)(piVar11 + 6); puVar10 < puVar2; puVar10 = puVar10 + 2) {
        if (((int)param_1 <= (int)*puVar10) && (param_1 < puVar10[1])) {
          piVar5 = (int *)__sbh_alloc_new_group(piVar8,*puVar10,param_1);
          if (piVar5 != (int *)0x0) {
            PTR_LOOP_1002bb20 = (undefined *)piVar11;
            *puVar10 = *puVar10 - param_1;
            piVar11[2] = (int)puVar10;
            return piVar5;
          }
          puVar10[1] = param_1;
        }
        piVar8 = piVar8 + 0x400;
      }
    }
    piVar11 = (int *)*piVar11;
  } while (piVar11 != (int *)PTR_LOOP_1002bb20);
  ppuVar7 = &PTR_LOOP_10029b00;
  while ((ppuVar7[4] == (undefined *)0xffffffff || (ppuVar7[3] == (undefined *)0x0))) {
    ppuVar7 = (undefined **)*ppuVar7;
    if (ppuVar7 == &PTR_LOOP_10029b00) {
      ppuVar7 = __sbh_alloc_new_region();
      if (ppuVar7 == (undefined **)0x0) {
        return (int *)0x0;
      }
      piVar11 = (int *)ppuVar7[4];
      *(char *)(piVar11 + 2) = (char)param_1;
      PTR_LOOP_1002bb20 = (undefined *)ppuVar7;
      *piVar11 = (int)piVar11 + param_1 + 8;
      piVar11[1] = 0xf0 - param_1;
      ppuVar7[6] = ppuVar7[6] + -(param_1 & 0xff);
      return piVar11 + 0x40;
    }
  }
  ppuVar3 = (undefined **)ppuVar7[3];
  puVar4 = *ppuVar3;
  piVar11 = (int *)(ppuVar7[4] + ((int)ppuVar3 + (-0x18 - (int)ppuVar7) >> 3) * 0x1000);
  ppuVar6 = ppuVar3;
  for (iVar9 = 0; (puVar4 == (undefined *)0xffffffff && (iVar9 < 0x10)); iVar9 = iVar9 + 1) {
    puVar4 = ppuVar6[2];
    ppuVar6 = ppuVar6 + 2;
  }
  piVar8 = (int *)VirtualAlloc((int)piVar11,iVar9 << 0xc,0x1000,4);
  if (piVar8 != piVar11) {
    return (int *)0x0;
  }
  ppuVar6 = ppuVar3;
  if (0 < iVar9) {
    piVar8 = piVar11 + 1;
    do {
      *piVar8 = 0xf0;
      piVar8[-1] = (int)(piVar8 + 1);
      *(undefined1 *)(piVar8 + 0x3d) = 0xff;
      *ppuVar6 = (undefined *)0xf0;
      ppuVar6[1] = (undefined *)0xf1;
      piVar8 = piVar8 + 0x400;
      ppuVar6 = ppuVar6 + 2;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
  }
  ppuVar1 = ppuVar7 + 0x806;
  bVar12 = false;
  if (ppuVar6 < ppuVar1) {
    do {
      if (*ppuVar6 == (undefined *)0xffffffff) break;
      ppuVar6 = ppuVar6 + 2;
    } while (ppuVar6 < ppuVar1);
    bVar12 = ppuVar6 < ppuVar1;
  }
  PTR_LOOP_1002bb20 = (undefined *)ppuVar7;
  ppuVar7[3] = (undefined *)(-(uint)bVar12 & (uint)ppuVar6);
  *(char *)(piVar11 + 2) = (char)param_1;
  ppuVar7[2] = (undefined *)ppuVar3;
  *ppuVar3 = *ppuVar3 + -param_1;
  piVar11[1] = piVar11[1] - param_1;
  *piVar11 = (int)piVar11 + param_1 + 8;
  return piVar11 + 0x40;
}

/* ---- 0x1001eb80  __sbh_alloc_new_group ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl __sbh_alloc_new_group(int *param_1,uint param_2,uint param_3)

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
            goto LAB_1001eccf;
          }
          *param_1 = (int)(pbVar6 + param_3);
          param_1[1] = uVar5 - param_3;
          goto LAB_1001ecd6;
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
LAB_1001eccf:
            param_1[1] = 0;
          }
LAB_1001ecd6:
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

/* ---- 0x1001ed00  __sbh_resize_block ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl __sbh_resize_block(int param_1,int *param_2,byte *param_3,uint param_4)

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

/* ---- 0x1001efc0  _mbschr_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint * __cdecl _mbschr_lk(uint *param_1,uint param_2)

{
  byte bVar1;
  uint uVar2;
  uint *puVar3;
  
  if (DAT_1002c570 == 0) {
    puVar3 = strchr(param_1,(char)param_2);
    return puVar3;
  }
  _lock(0x19);
  bVar1 = (byte)*param_1;
  while (uVar2 = (uint)bVar1, bVar1 != 0) {
    if ((*(byte *)((int)&DAT_1002c368 + uVar2 + 1) & 4) == 0) {
      puVar3 = param_1;
      if (param_2 == uVar2) break;
    }
    else {
      puVar3 = (uint *)((int)param_1 + 1);
      if (*(char *)((int)param_1 + 1) == '\0') {
        _unlock(0x19);
        return (uint *)0x0;
      }
      if (param_2 == CONCAT11(bVar1,*(char *)((int)param_1 + 1))) {
        _unlock(0x19);
        return param_1;
      }
    }
    param_1 = (uint *)((int)puVar3 + 1);
    bVar1 = *(byte *)((int)puVar3 + 1);
  }
  _unlock(0x19);
  return (uint *)((param_2 != uVar2) - 1 & (uint)param_1);
}

/* ---- 0x1001f090  _dospawn ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _dospawn(int param_1,int param_2,char *param_3,int param_4)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  byte bVar2;
  int *piVar3;
  bool bVar4;
  uint uVar5;
  char *a2;
  char *pcVar6;
  char *pcVar7;
  uint *puVar8;
  undefined *puVar9;
  int *piVar10;
  int iVar11;
  uint uVar12;
  undefined4 *puVar13;
  int iVar14;
  uint *puVar15;
  #define local_54 (*(char **)(_frame + (0x70 - 0x54)))
  #define iStack_50 (*(int *)(_frame + (0x70 - 0x50)))
  #define local_44 (*(undefined4 (*)[12])(_frame + (0x70 - 0x44)))
  #define local_12 (*(ushort *)(_frame + (0x70 - 0x12)))
  #define uStack_10 (*(undefined2 *)(_frame + (0x70 - 0x10)))
  #define uStack_e (*(undefined2 *)(_frame + (0x70 - 0xe)))
  
  a2 = param_3;
  iVar14 = 0;
  bVar4 = false;
  switch(param_1) {
  case 0:
  case 1:
  case 2:
  case 3:
    goto switchD_1001f0aa_caseD_0;
  case 4:
    bVar4 = true;
switchD_1001f0aa_caseD_0:
    cVar1 = *param_3;
    pcVar7 = param_3;
    break;
  default:
    piVar10 = _errno();
    *piVar10 = 0x16;
    piVar10 = __doserrno();
    *piVar10 = 0;
    return -1;
  }
  while (cVar1 != '\0') {
    do {
      pcVar6 = pcVar7;
      pcVar7 = pcVar6 + 1;
    } while (pcVar6[1] != '\0');
    if (pcVar6[2] != '\0') {
      *pcVar7 = ' ';
      pcVar7 = pcVar6 + 2;
    }
    cVar1 = *pcVar7;
  }
  puVar13 = local_44;
  for (iVar11 = 0x11; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  local_44[0] = 0x44;
  uVar12 = DAT_1002c700;
  do {
    uVar5 = uVar12;
    if (uVar5 == 0) break;
    uVar12 = uVar5 - 1;
  } while ((char)(&PTR_1002c600)[(int)uVar12 >> 5][(uVar12 & 0x1f) * 9 + 1] == '\0');
  local_12 = (short)uVar5 * 5 + 4;
  puVar8 = (uint *)calloc((uint)local_12,1);
  uStack_10 = SUB42(puVar8,0);
  uStack_e = (undefined2)((uint)puVar8 >> 0x10);
  *puVar8 = uVar5;
  uVar12 = 0;
  puVar15 = puVar8 + 1;
  piVar10 = (int *)(uVar5 + 4 + (int)puVar8);
  if (0 < (int)uVar5) {
    do {
      piVar3 = (&PTR_1002c600)[(int)uVar12 >> 5];
      bVar2 = *(byte *)(piVar3 + (uVar12 & 0x1f) * 9 + 1);
      if ((bVar2 & 0x10) == 0) {
        *(byte *)puVar15 = bVar2;
        *piVar10 = piVar3[(uVar12 & 0x1f) * 9];
      }
      else {
        *(undefined1 *)puVar15 = 0;
        *piVar10 = -1;
      }
      uVar12 = uVar12 + 1;
      puVar15 = (uint *)((int)puVar15 + 1);
      piVar10 = piVar10 + 1;
    } while ((int)uVar12 < (int)uVar5);
  }
  if (bVar4) {
    iVar14 = 0;
    puVar15 = puVar8 + 1;
    puVar13 = (undefined4 *)(uVar5 + 4 + (int)puVar8);
    while( true ) {
      uVar12 = uVar5;
      if (2 < (int)uVar5) {
        uVar12 = 3;
      }
      if ((int)uVar12 <= iVar14) break;
      *(undefined1 *)puVar15 = 0;
      iVar14 = iVar14 + 1;
      *puVar13 = 0xffffffff;
      puVar15 = (uint *)((int)puVar15 + 1);
      puVar13 = puVar13 + 1;
    }
    iVar14 = 8;
  }
  piVar10 = _errno();
  *piVar10 = 0;
  piVar10 = __doserrno();
  *piVar10 = 0;
  iVar14 = CreateProcessA(param_2,(int)a2,0,0,1,iVar14,param_4,0,(int)local_44,(int)&local_54);
  puVar9 = (undefined *)GetLastError();
  free((undefined *)CONCAT22(uStack_e,uStack_10));
  if (iVar14 == 0) {
    _dosmaperr(puVar9);
    return -1;
  }
  if (param_1 == 2) {
    exit(0);
    CloseHandle(iStack_50);
    return (int)param_3;
  }
  if (param_1 == 0) {
    WaitForSingleObject((int)local_54,-1);
    GetExitCodeProcess((int)local_54,(int)&param_3);
    CloseHandle((int)local_54);
    CloseHandle(iStack_50);
    return (int)param_3;
  }
  if (param_1 == 4) {
    CloseHandle((int)local_54);
    param_3 = (char *)0x0;
    CloseHandle(iStack_50);
    return (int)param_3;
  }
  param_3 = local_54;
  CloseHandle(iStack_50);
  return (int)param_3;
}
#undef iStack_50
#undef local_12
#undef local_44
#undef local_54
#undef uStack_10
#undef uStack_e


/* ---- 0x1001f320  _cenvarg ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __thiscall
_cenvarg(void *this,undefined4 *param_1,undefined4 *param_2,int *param_3,int *param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  undefined4 *puVar5;
  char *pcVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  #define local_4 (*(int **)(_frame + (0x20 - 0x4)))
  
  uVar7 = 2;
  pcVar6 = (char *)*param_1;
  puVar5 = param_1;
  while (pcVar6 != (char *)0x0) {
    uVar4 = 0xffffffff;
    puVar5 = puVar5 + 1;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    uVar7 = uVar7 + ~uVar4;
    pcVar6 = (char *)*puVar5;
  }
  iVar2 = malloc(uVar7);
  *param_3 = iVar2;
  if (iVar2 == 0) {
    *param_4 = 0;
LAB_1001f46c:
    piVar3 = _errno();
    *piVar3 = 0xc;
    piVar3 = __doserrno();
    *piVar3 = 8;
    return 0xffffffff;
  }
  if (param_2 != (undefined4 *)0x0) {
    uVar7 = 2;
    pcVar6 = (char *)*param_2;
    puVar5 = param_2;
    while (pcVar6 != (char *)0x0) {
      uVar4 = 0xffffffff;
      puVar5 = puVar5 + 1;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      uVar7 = uVar7 + ~uVar4;
      pcVar6 = (char *)*puVar5;
    }
  }
  if (param_2 == (undefined4 *)0x0) {
    *param_4 = 0;
    piVar3 = param_4;
    local_4 = this;
  }
  else {
    if (DAT_1002c010 == (char *)0x0) {
      DAT_1002c010 = __crtGetEnvironmentStringsA();
      if (DAT_1002c010 == (char *)0x0) {
        return 0xffffffff;
      }
    }
    local_4 = (int *)0x0;
    if (*DAT_1002c010 != '\0') {
      cVar1 = *DAT_1002c010;
      pcVar6 = DAT_1002c010;
      do {
        if (cVar1 == '=') break;
        uVar4 = 0xffffffff;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        local_4 = (int *)((int)local_4 + ~uVar4);
        pcVar6 = (char *)((int)local_4 + (int)DAT_1002c010);
        cVar1 = *pcVar6;
      } while (cVar1 != '\0');
    }
    cVar1 = *(char *)((int)local_4 + (int)DAT_1002c010);
    piVar3 = local_4;
    while ((((cVar1 == '=' && (DAT_1002c010[(int)piVar3 + 1] != '\0')) &&
            (DAT_1002c010[(int)piVar3 + 2] == ':')) && (DAT_1002c010[(int)piVar3 + 3] == '='))) {
      uVar4 = 0xffffffff;
      pcVar6 = (char *)((int)(piVar3 + 1) + (int)DAT_1002c010);
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      piVar3 = (int *)((int)piVar3 + ~uVar4 + 4);
      cVar1 = *(char *)((int)piVar3 + (int)DAT_1002c010);
    }
    iVar2 = malloc((int)piVar3 + (uVar7 - (int)local_4));
    *param_4 = iVar2;
    if (iVar2 == 0) {
      free((undefined *)*param_3);
      *param_3 = 0;
      goto LAB_1001f46c;
    }
  }
  pcVar6 = (char *)*param_3;
  if ((char *)*param_1 == (char *)0x0) {
    pcVar6 = pcVar6 + 1;
  }
  else {
    uVar7 = 0xffffffff;
    pcVar8 = (char *)*param_1;
    do {
      pcVar9 = pcVar8;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar9 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    pcVar8 = pcVar9 + -uVar7;
    pcVar9 = pcVar6;
    for (uVar4 = uVar7 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar9 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    }
    pcVar8 = (char *)*param_1;
    param_1 = param_1 + 1;
    uVar7 = 0xffffffff;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar1 != '\0');
    pcVar6 = pcVar6 + ~uVar7;
  }
  pcVar8 = (char *)*param_1;
  while (pcVar8 != (char *)0x0) {
    uVar7 = 0xffffffff;
    do {
      pcVar9 = pcVar8;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar9 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    pcVar8 = pcVar9 + -uVar7;
    pcVar9 = pcVar6;
    for (uVar4 = uVar7 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar9 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    }
    uVar7 = 0xffffffff;
    pcVar8 = (char *)*param_1;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar1 != '\0');
    pcVar6[~uVar7 - 1] = ' ';
    pcVar6 = pcVar6 + (~uVar7 - 1) + 1;
    pcVar8 = (char *)param_1[1];
    param_1 = param_1 + 1;
  }
  pcVar6[-1] = '\0';
  *pcVar6 = '\0';
  pcVar6 = (char *)*param_4;
  if (param_2 != (undefined4 *)0x0) {
    pcVar8 = DAT_1002c010 + (int)local_4;
    pcVar9 = pcVar6;
    for (uVar7 = (uint)((int)piVar3 - (int)local_4) >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar7 = (int)piVar3 - (int)local_4 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar9 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    }
    pcVar6 = pcVar6 + ((int)piVar3 - (int)local_4);
    pcVar8 = (char *)*param_2;
    while (pcVar8 != (char *)0x0) {
      uVar7 = 0xffffffff;
      do {
        pcVar9 = pcVar8;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar9 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar9;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      pcVar8 = pcVar9 + -uVar7;
      pcVar9 = pcVar6;
      for (uVar4 = uVar7 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar9 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar9 = pcVar9 + 1;
      }
      uVar7 = 0xffffffff;
      pcVar8 = (char *)*param_2;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar1 != '\0');
      pcVar6 = pcVar6 + ~uVar7;
      pcVar8 = (char *)param_2[1];
      param_2 = param_2 + 1;
    }
  }
  if (pcVar6 != (char *)0x0) {
    if (pcVar6 == (char *)*param_4) {
      *pcVar6 = '\0';
      pcVar6 = pcVar6 + 1;
    }
    *pcVar6 = '\0';
  }
  free(DAT_1002c010);
  DAT_1002c010 = (char *)0x0;
  return 0;
}
#undef local_4


/* ---- 0x1001f670  _get_osfhandle ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _get_osfhandle(uint param_1)

{
  int *piVar1;
  
  if ((param_1 < DAT_1002c700) &&
     ((*(byte *)((&PTR_1002c600)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    return (&PTR_1002c600)[(int)param_1 >> 5][(param_1 & 0x1f) * 9];
  }
  piVar1 = _errno();
  *piVar1 = 9;
  piVar1 = __doserrno();
  *piVar1 = 0;
  return 0xffffffff;
}

/* ---- 0x1001f6c0  _lock_fhandle ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _lock_fhandle(uint param_1)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = param_1 & 0x1f;
  piVar1 = (&PTR_1002c600)[(int)param_1 >> 5];
  if (piVar1[uVar2 * 9 + 2] == 0) {
    _lock(0x11);
    if (piVar1[uVar2 * 9 + 2] == 0) {
      InitializeCriticalSection((int)(piVar1 + uVar2 * 9 + 3));
      piVar1[uVar2 * 9 + 2] = piVar1[uVar2 * 9 + 2] + 1;
    }
    _unlock(0x11);
  }
  EnterCriticalSection((int)((&PTR_1002c600)[(int)param_1 >> 5] + uVar2 * 9 + 3));
  return;
}

/* ---- 0x1001f730  _unlock_fhandle ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _unlock_fhandle(uint param_1)

{
  LeaveCriticalSection((int)((&PTR_1002c600)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 3));
  return;
}

/* ---- 0x1001f760  _read ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _read(uint param_1,char *param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  if ((param_1 < DAT_1002c700) &&
     ((*(byte *)((&PTR_1002c600)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 1) != 0)) {
    _lock_fhandle(param_1);
    iVar1 = _read_lk(param_1,param_2,param_3);
    _unlock_fhandle(param_1);
    return iVar1;
  }
  piVar2 = _errno();
  *piVar2 = 9;
  piVar2 = __doserrno();
  *piVar2 = 0;
  return -1;
}

/* ---- 0x1001f7e0  _read_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl _read_lk(uint param_1,char *param_2,int param_3)

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
    ppiVar1 = &PTR_1002c600 + ((int)param_1 >> 5);
    iVar8 = uVar4 * 0x24;
    bVar3 = *(byte *)((&PTR_1002c600)[(int)param_1 >> 5] + uVar4 * 9 + 1);
    if ((bVar3 & 2) == 0) {
      pcVar11 = param_2;
      if (((bVar3 & 0x48) != 0) &&
         (cVar2 = *(char *)((int)(&PTR_1002c600)[(int)param_1 >> 5] + iVar8 + 5), cVar2 != '\n')) {
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
                    goto LAB_1001f9b8;
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
                        goto LAB_1001f9b8;
                      }
                      _lseek_lk(param_1,0xffffffff,1);
                      if (cStack_9 != '\n') goto LAB_1001f9b5;
                    }
                    else {
                      if (cStack_9 == '\n') {
                        *pcVar11 = '\n';
                        goto LAB_1001f9b8;
                      }
                      *pcVar11 = '\r';
                      pcVar11 = pcVar11 + 1;
                      *(char *)(iVar8 + 5 + (int)*local_4) = cStack_9;
                    }
                  }
                  else {
LAB_1001f9b5:
                    *pcVar11 = '\r';
LAB_1001f9b8:
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


/* ---- 0x1001fa10  strrchr ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

char * __cdecl strrchr(char *param_1,char param_2)

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

/* ---- 0x1001fa40  __crtsetenv ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl __crtsetenv(uint *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined4 *a1;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  bool bVar11;
  
  if (param_1 == (uint *)0x0) {
    return 0xffffffff;
  }
  puVar3 = _mbschr_lk(param_1,0x3d);
  if (puVar3 == (uint *)0x0) {
    return 0xffffffff;
  }
  if (param_1 == puVar3) {
    return 0xffffffff;
  }
  bVar11 = *(char *)((int)puVar3 + 1) == '\0';
  if (DAT_1002c0a8 == DAT_1002c0ac) {
    DAT_1002c0a8 = copy_environ(DAT_1002c0a8);
  }
  if (DAT_1002c0a8 == (int *)0x0) {
    if ((param_2 == 0) || (DAT_1002c0b0 == (undefined4 *)0x0)) {
      if (bVar11) {
        return 0;
      }
      DAT_1002c0a8 = (int *)malloc(4);
      if (DAT_1002c0a8 == (int *)0x0) {
        return 0xffffffff;
      }
      *DAT_1002c0a8 = 0;
      if (DAT_1002c0b0 == (undefined4 *)0x0) {
        DAT_1002c0b0 = (undefined4 *)malloc(4);
        if (DAT_1002c0b0 == (undefined4 *)0x0) {
          return 0xffffffff;
        }
        *DAT_1002c0b0 = 0;
      }
    }
    else {
      iVar4 = __crtsetenv_from_wenviron();
      if (iVar4 != 0) {
        return 0xffffffff;
      }
    }
  }
  piVar6 = DAT_1002c0a8;
  iVar5 = (int)puVar3 - (int)param_1;
  iVar4 = findenv((byte *)param_1,iVar5);
  if ((iVar4 < 0) || (*piVar6 == 0)) {
    if (bVar11) {
      return 0;
    }
    if (iVar4 < 0) {
      iVar4 = -iVar4;
    }
    piVar6 = realloc(piVar6,iVar4 * 4 + 8);
    if (piVar6 == (int *)0x0) {
      return 0xffffffff;
    }
    piVar6[iVar4] = (int)param_1;
    piVar6[iVar4 + 1] = 0;
    DAT_1002c0a8 = piVar6;
  }
  else if (bVar11) {
    free((undefined *)piVar6[iVar4]);
    iVar1 = piVar6[iVar4];
    piVar2 = piVar6 + iVar4;
    while (iVar1 != 0) {
      *piVar2 = piVar2[1];
      iVar4 = iVar4 + 1;
      iVar1 = piVar2[1];
      piVar2 = piVar2 + 1;
    }
    piVar6 = realloc(piVar6,iVar4 * 4);
    if (piVar6 != (int *)0x0) {
      DAT_1002c0a8 = piVar6;
    }
  }
  else {
    piVar6[iVar4] = (int)param_1;
  }
  if (param_2 != 0) {
    uVar7 = 0xffffffff;
    puVar3 = param_1;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      uVar8 = *puVar3;
      puVar3 = (uint *)((int)puVar3 + 1);
    } while ((char)uVar8 != '\0');
    a1 = (undefined4 *)malloc(~uVar7 + 1);
    if (a1 != (undefined4 *)0x0) {
      uVar7 = 0xffffffff;
      do {
        puVar3 = param_1;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        puVar3 = (uint *)((int)param_1 + 1);
        uVar8 = *param_1;
        param_1 = puVar3;
      } while ((char)uVar8 != '\0');
      uVar7 = ~uVar7;
      puVar9 = (undefined4 *)((int)puVar3 - uVar7);
      puVar10 = a1;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *puVar10 = *puVar9;
        puVar9 = puVar9 + 1;
        puVar10 = puVar10 + 1;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined1 *)puVar10 = *(undefined1 *)puVar9;
        puVar9 = (undefined4 *)((int)puVar9 + 1);
        puVar10 = (undefined4 *)((int)puVar10 + 1);
      }
      *(undefined1 *)((int)a1 + iVar5) = 0;
      SetEnvironmentVariableA((int)a1,~-(uint)bVar11 & (int)a1 + iVar5 + 1);
      free((undefined *)a1);
      return 0;
    }
  }
  return 0;
}

/* ---- 0x1001fc50  findenv ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl findenv(byte *param_1,int param_2)

{
  byte *pbVar1;
  int iVar2;
  int *piVar3;
  
  pbVar1 = (byte *)*DAT_1002c0a8;
  piVar3 = DAT_1002c0a8;
  if (pbVar1 == (byte *)0x0) {
    return 0;
  }
  while ((iVar2 = _strnicoll(param_1,pbVar1,param_2), iVar2 != 0 ||
         ((*(char *)(*piVar3 + param_2) != '=' && (*(char *)(*piVar3 + param_2) != '\0'))))) {
    pbVar1 = (byte *)piVar3[1];
    piVar3 = piVar3 + 1;
    if (pbVar1 == (byte *)0x0) {
      return -((int)piVar3 - (int)DAT_1002c0a8 >> 2);
    }
  }
  return (int)piVar3 - (int)DAT_1002c0a8 >> 2;
}

/* ---- 0x1001fcd0  copy_environ ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 * __cdecl copy_environ(int *param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  char *pcVar4;
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
    pcVar4 = (char *)*param_1;
    puVar6 = puVar3;
    while (pcVar4 != (char *)0x0) {
      param_1 = param_1 + 1;
      pcVar4 = _strdup(pcVar4);
      *puVar6 = pcVar4;
      puVar6 = puVar6 + 1;
      pcVar4 = (char *)*param_1;
    }
    *puVar6 = 0;
    return puVar3;
  }
  return (undefined4 *)0x0;
}

/* ---- 0x1001fd40  atol ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl atol(byte *param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  
  while( true ) {
    if (DAT_10028b5c < 2) {
      uVar2 = (byte)PTR_DAT_10028950[(uint)*param_1 * 2] & 8;
    }
    else {
      uVar2 = _isctype((uint)*param_1,8);
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
    if (DAT_10028b5c < 2) {
      uVar3 = (byte)PTR_DAT_10028950[uVar4 * 2] & 4;
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

/* ---- 0x1001fde0  wcstombs ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl wcstombs(int param_1,ushort *param_2,uint param_3)

{
  uint uVar1;
  bool bVar2;
  
  InterlockedIncrement(IMG_ADDR(0x1002c710));
  bVar2 = DAT_1002c70c != 0;
  if (bVar2) {
    InterlockedDecrement(IMG_ADDR(0x1002c710));
    _lock(0x13);
  }
  uVar1 = _wcstombs_lk(param_1,param_2,param_3);
  if (!bVar2) {
    InterlockedDecrement(IMG_ADDR(0x1002c710));
    return uVar1;
  }
  _unlock(0x13);
  return uVar1;
}

/* ---- 0x1001fe60  _wcstombs_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _wcstombs_lk(int param_1,ushort *param_2,uint param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  ushort *puVar6;
  int iVar7;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  uVar4 = param_3;
  puVar6 = param_2;
  uVar2 = 0;
  local_4 = 0;
  if ((param_1 != 0) && (param_3 == 0)) {
    return uVar2;
  }
  if (param_1 == 0) {
    if (DAT_1002c208 == 0) {
      uVar4 = wcslen((short *)param_2);
      return uVar4;
    }
    iVar3 = WideCharToMultiByte(DAT_1002c218,0x220,(int)param_2,-1,0,0,0,(int)&local_4);
    if ((iVar3 != 0) && (local_4 == 0)) {
      return iVar3 - 1;
    }
  }
  else if (DAT_1002c208 == 0) {
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
  else if (DAT_10028b5c == 1) {
    iVar3 = 0;
    if (param_3 != 0) {
      iVar3 = wcsncnt((short *)param_2,param_3);
    }
    uVar4 = WideCharToMultiByte(DAT_1002c218,0x220,(int)puVar6,iVar3,param_1,iVar3,0,(int)&local_4);
    if ((uVar4 != 0) && (local_4 == 0)) {
      if (*(char *)((uVar4 - 1) + param_1) != '\0') {
        return uVar4;
      }
      return uVar4 - 1;
    }
  }
  else {
    iVar3 = WideCharToMultiByte(DAT_1002c218,0x220,(int)param_2,-1,param_1,param_3,0,(int)&local_4);
    if (iVar3 == 0) {
      if ((local_4 == 0) && (iVar3 = GetLastError(), iVar3 == 0x7a)) {
        uVar2 = 0;
        if (uVar4 != 0) {
          do {
            iVar3 = WideCharToMultiByte(DAT_1002c218,0,(int)puVar6,1,(int)&param_2,DAT_10028b5c,0,
                                        (int)&local_4);
            if ((iVar3 == 0) || (local_4 != 0)) goto LAB_10020036;
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
LAB_10020036:
  piVar5 = _errno();
  *piVar5 = 0x2a;
  return 0xffffffff;
}
#undef local_4


/* ---- 0x10020050  wcsncnt  (renamed wcsncnt_10020050: duplicate name) ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl wcsncnt_10020050(short *param_1,int param_2)

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

/* ---- 0x10020240  _strnicmp ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl _strnicmp(byte *param_1,char *param_2,int param_3)

{
  char cVar1;
  int iVar2;
  byte bVar3;
  ushort uVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  bool bVar8;
  uint uVar9;
  
  iVar2 = DAT_1002c710;
  uVar6 = 0;
  if (param_3 != 0) {
    if (DAT_1002c208 == 0) {
      do {
        bVar3 = *param_1;
        cVar1 = *param_2;
        uVar4 = CONCAT11(bVar3,cVar1);
        if (bVar3 == 0) break;
        uVar4 = CONCAT11(bVar3,cVar1);
        uVar7 = (uint)uVar4;
        if (cVar1 == '\0') break;
        param_1 = param_1 + 1;
        param_2 = param_2 + 1;
        if ((0x40 < bVar3) && (bVar3 < 0x5b)) {
          uVar7 = (uint)CONCAT11(bVar3 + 0x20,cVar1);
        }
        uVar4 = (ushort)uVar7;
        bVar3 = (byte)uVar7;
        if ((0x40 < bVar3) && (bVar3 < 0x5b)) {
          uVar4 = (ushort)CONCAT31((int3)(uVar7 >> 8),bVar3 + 0x20);
        }
        bVar3 = (byte)(uVar4 >> 8);
        bVar8 = bVar3 < (byte)uVar4;
        if (bVar3 != (byte)uVar4) goto LAB_1002029f;
        param_3 = param_3 + -1;
      } while (param_3 != 0);
      uVar6 = 0;
      bVar3 = (byte)(uVar4 >> 8);
      bVar8 = bVar3 < (byte)uVar4;
      if (bVar3 != (byte)uVar4) {
LAB_1002029f:
        uVar6 = 0xffffffff;
        if (!bVar8) {
          uVar6 = 1;
        }
      }
    }
    else {
      LOCK();
      DAT_1002c710 = DAT_1002c710 + 1;
      UNLOCK();
      bVar8 = 0 < DAT_1002c70c;
      if (bVar8) {
        LOCK();
        UNLOCK();
        DAT_1002c710 = iVar2;
        _lock(0x13);
      }
      uVar9 = (uint)bVar8;
      uVar7 = 0;
      uVar5 = 0;
      do {
        uVar5 = CONCAT31((int3)(uVar5 >> 8),*param_1);
        uVar7 = CONCAT31((int3)(uVar7 >> 8),*param_2);
        if ((uVar5 == 0) || (uVar7 == 0)) break;
        param_1 = param_1 + 1;
        param_2 = param_2 + 1;
        uVar7 = _toupper_lk(uVar7);
        uVar5 = _toupper_lk(uVar5);
        bVar8 = uVar5 < uVar7;
        if (uVar5 != uVar7) goto LAB_10020315;
        param_3 = param_3 + -1;
      } while (param_3 != 0);
      uVar6 = 0;
      bVar8 = uVar5 < uVar7;
      if (uVar5 != uVar7) {
LAB_10020315:
        uVar6 = 0xffffffff;
        if (!bVar8) {
          uVar6 = 1;
        }
      }
      if (uVar9 == 0) {
        LOCK();
        DAT_1002c710 = DAT_1002c710 + -1;
        UNLOCK();
      }
      else {
        _unlock(0x13);
      }
    }
  }
  return uVar6;
}

/* ---- 0x10020350  _except1 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl _except1(uint param_1,int *param_2,ushort *param_3)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  uint uVar3;
  #define local_58 (*(uint (*)[10])(_frame + (0x70 - 0x58)))
  #define local_30 (*(int *)(_frame + (0x70 - 0x30)))
  #define local_2c (*(int *)(_frame + (0x70 - 0x2c)))
  #define local_20 (*(uint *)(_frame + (0x70 - 0x20)))
  
  param_3 = (ushort *)(uint)*param_3;
  switch(*param_2) {
  case 1:
  case 5:
    uVar3 = 8;
    break;
  case 2:
    uVar3 = 4;
    break;
  case 3:
    uVar3 = 0x11;
    break;
  case 4:
    uVar3 = 0x12;
    break;
  default:
    goto switchD_1002036f_caseD_6;
  case 7:
    *param_2 = 1;
    goto switchD_1002036f_caseD_6;
  case 8:
    uVar3 = 0x10;
  }
  bVar1 = _handle_exc(uVar3,(double *)(param_2 + 6),(uint)param_3);
  if (((uint)(bVar1)) == 0) {
    if (((param_1 == 0x10) || (param_1 == 0x16)) || (param_1 == 0x1d)) {
      local_30 = param_2[4];
      local_20 = local_20 & 0xffffffe3 | 3;
      local_2c = param_2[5];
    }
    else {
      local_20 = local_20 & 0xfffffffe;
    }
    _raise_exc(local_58,(uint *)&param_3,(byte)uVar3,param_1,(uint *)(param_2 + 2),
               (uint *)(param_2 + 6));
  }
switchD_1002036f_caseD_6:
  FUN_10019aa0();
  iVar2 = 0;
  if ((*param_2 != 8) && (DAT_1002bbe0 == 0)) {
    iVar2 = FUN_100119e0();
  }
  if (iVar2 == 0) {
    FUN_10019820(*param_2);
  }
  return;
}
#undef local_20
#undef local_2c
#undef local_30
#undef local_58


/* ---- 0x10020510  mbtowc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl mbtowc(ushort *param_1,byte *param_2,uint param_3)

{
  uint uVar1;
  bool bVar2;
  
  InterlockedIncrement(IMG_ADDR(0x1002c710));
  bVar2 = DAT_1002c70c != 0;
  if (bVar2) {
    InterlockedDecrement(IMG_ADDR(0x1002c710));
    _lock(0x13);
  }
  uVar1 = _mbtowc_lk(param_1,param_2,param_3);
  if (!bVar2) {
    InterlockedDecrement(IMG_ADDR(0x1002c710));
    return uVar1;
  }
  _unlock(0x13);
  return uVar1;
}

/* ---- 0x10020590  _mbtowc_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _mbtowc_lk(ushort *param_1,byte *param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  int *piVar3;
  
  if ((param_2 != (byte *)0x0) && (param_3 != 0)) {
    bVar1 = *param_2;
    if (bVar1 != 0) {
      if (DAT_1002c208 == 0) {
        if (param_1 == (ushort *)0x0) {
          return 1;
        }
        *param_1 = (ushort)bVar1;
        return 1;
      }
      if ((PTR_DAT_10028950[(uint)bVar1 * 2 + 1] & 0x80) == 0) {
        iVar2 = MultiByteToWideChar(DAT_1002c218,9,(int)param_2,1,(int)param_1,
                                    (uint)(param_1 != (ushort *)0x0));
        if (iVar2 != 0) {
          return 1;
        }
      }
      else {
        if (((1 < (int)DAT_10028b5c) && ((int)DAT_10028b5c <= (int)param_3)) &&
           (iVar2 = MultiByteToWideChar(DAT_1002c218,9,(int)param_2,DAT_10028b5c,(int)param_1,
                                        (uint)(param_1 != (ushort *)0x0)), iVar2 != 0)) {
          return DAT_10028b5c;
        }
        if (DAT_10028b5c <= param_3) {
          if (param_2[1] != 0) {
            return DAT_10028b5c;
          }
          piVar3 = _errno();
          *piVar3 = 0x2a;
          return 0xffffffff;
        }
      }
      piVar3 = _errno();
      *piVar3 = 0x2a;
      return 0xffffffff;
    }
    if (param_1 != (ushort *)0x0) {
      *param_1 = 0;
      return 0;
    }
  }
  return 0;
}

/* ---- 0x10020690  _allmul ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __stdcall _allmul(int a1,int a2,int a3,int a4)

{
  if (a4 == 0 && a2 == 0) {
    return a1 * a3;
  }
  return a1 * a3;
}

/* ---- 0x100206f0  _filbuf ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _filbuf(int *param_1)

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
    iVar3 = _read(param_1[4],(char *)param_1[2],param_1[6]);
    param_1[1] = iVar3;
    if ((iVar3 != 0) && (iVar3 != -1)) {
      if ((param_1[3] & 0x82U) == 0) {
        uVar2 = param_1[4];
        if (uVar2 == 0xffffffff) {
          piVar4 = (int *)&DAT_10028c70;
        }
        else {
          piVar4 = (&PTR_1002c600)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 9;
        }
        if ((*(byte *)(piVar4 + 1) & 0x82) == 0x82) {
          param_1[3] = param_1[3] | 0x2000;
        }
      }
      if (((param_1[6] == 0x200) && ((param_1[3] & 8U) != 0)) && ((param_1[3] & 0x400U) == 0)) {
        param_1[6] = 0x1000;
      }
      param_1[1] = iVar3 + -1;
      bVar1 = *(byte *)*param_1;
      *param_1 = (int)((byte *)*param_1 + 1);
      return (uint)bVar1;
    }
    param_1[1] = 0;
    param_1[3] = param_1[3] | (-(uint)(iVar3 != 0) & 0x10) + 0x10;
  }
  return 0xffffffff;
}

/* ---- 0x100207e0  _ungetc_lk ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _ungetc_lk(uint param_1,int *param_2)

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

/* ---- 0x10020870  toupper  (renamed toupper_10020870: duplicate name) ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl toupper_10020870(uint param_1)

{
  uint uVar1;
  undefined2 extraout_var;
  int iVar2;
  bool bVar3;
  
  if (DAT_1002c208 == 0) {
    if ((0x60 < (ushort)param_1) && ((ushort)param_1 < 0x7b)) {
      return param_1 + 0xffe0;
    }
  }
  else {
    InterlockedIncrement(IMG_ADDR(0x1002c710));
    bVar3 = DAT_1002c70c != 0;
    if (bVar3) {
      InterlockedDecrement(IMG_ADDR(0x1002c710));
      _lock(0x13);
    }
    uVar1 = _toupper_lk(param_1);
    if (bVar3) {
      _unlock(0x13);
      return CONCAT22(extraout_var,(short)uVar1);
    }
    iVar2 = InterlockedDecrement(IMG_ADDR(0x1002c710));
    param_1 = CONCAT22((short)((uint)iVar2 >> 0x10),(short)uVar1);
  }
  return param_1;
}

/* ---- 0x10020900  _toupper_lk  (renamed _toupper_lk_10020900: duplicate name) ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl _toupper_lk_10020900(uint param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort uVar1;
  uint uVar2;
  short *psVar3;
  undefined2 uVar4;
  #define local_2 (*(undefined2 *)(_frame + (0x20 - 0x2)))
  
  uVar1 = (ushort)param_1;
  if (uVar1 == 0xffff) {
    return param_1;
  }
  if (DAT_1002c208 == 0) {
    if ((0x60 < uVar1) && (uVar1 < 0x7b)) {
      return param_1 + 0xffe0;
    }
  }
  else {
    if (uVar1 < 0x100) {
      uVar2 = iswctype(param_1,2);
      if (uVar2 == 0) {
        return param_1 & 0xffff;
      }
    }
    psVar3 = __crtLCMapStringW(DAT_1002c208,0x200,(short *)&param_1,1,&local_2,1,(uint *)0x0);
    uVar4 = (undefined2)((uint)psVar3 >> 0x10);
    param_1 = CONCAT22(uVar4,(undefined2)param_1);
    if (psVar3 != (short *)0x0) {
      param_1 = CONCAT22(uVar4,local_2);
    }
  }
  return param_1;
}
#undef local_2


/* ---- 0x10020980  iswctype ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl iswctype(uint param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if ((ushort)param_1 == 0xffff) {
    return 0;
  }
  if ((ushort)param_1 < 0x100) {
    local_4 = (uint)*(ushort *)(PTR_DAT_10028954 + (param_1 & 0xffff) * 2);
  }
  else {
    if (DAT_1002c208 == 0) {
      return 0;
    }
    piVar1 = __crtGetStringTypeW(1,(int)&param_1,1,&local_4,0,0);
    if (piVar1 == (int *)0x0) {
      return 0;
    }
  }
  return local_4 & 0xffff & param_2 & 0xffff;
}
#undef local_4


/* ---- 0x100209f0  wcslen ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int __cdecl wcslen(short *param_1)

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

/* ---- 0x10020a10  __crtMessageBoxA ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl __crtMessageBoxA(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int a1;
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = 0;
  if (DAT_1002c5b4 != (code *)0x0) {
LAB_10020a60:
    if (DAT_1002c5b8 != (code *)0x0) {
      iVar2 = (*DAT_1002c5b8)();
    }
    if ((iVar2 != 0) && (DAT_1002c5bc != (code *)0x0)) {
      iVar2 = (*DAT_1002c5bc)(iVar2);
    }
    uVar1 = (*DAT_1002c5b4)(iVar2,param_1,param_2,param_3);
    return uVar1;
  }
  a1 = LoadLibraryA(IMG_ADDR(0x10024d88));
  if (a1 != 0) {
    DAT_1002c5b4 = (code *)GetProcAddress(a1,IMG_ADDR(0x10024d7c));
    if (DAT_1002c5b4 != (code *)0x0) {
      DAT_1002c5b8 = (code *)GetProcAddress(a1,IMG_ADDR(0x10024d6c));
      DAT_1002c5bc = (code *)GetProcAddress(a1,IMG_ADDR(0x10024d58));
      goto LAB_10020a60;
    }
  }
  return 0;
}

/* ---- 0x10020aa0  raise ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl raise(int *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  bool bVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  code *pcVar8;
  undefined4 *puVar9;
  bool bVar10;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  piVar3 = param_1;
  bVar2 = false;
  piVar4 = param_1;
  switch((int)(param_1)) {
  case 0x2:
    puVar9 = &DAT_1002c5c0;
    bVar2 = true;
    pcVar8 = DAT_1002c5c0;
    break;
  default:
    return 0xffffffff;
  case 0x4:
  case 0x8:
  case 0xb:
    piVar4 = _getptd();
    uVar5 = siglookup((int)param_1,piVar4[0x14]);
    puVar9 = (undefined4 *)(uVar5 + 8);
    pcVar8 = (code *)*puVar9;
    break;
  case 0xf:
    puVar9 = &DAT_1002c5cc;
    bVar2 = true;
    pcVar8 = DAT_1002c5cc;
    break;
  case 0x15:
    puVar9 = &DAT_1002c5c4;
    bVar2 = true;
    pcVar8 = DAT_1002c5c4;
    break;
  case 0x16:
    puVar9 = &DAT_1002c5c8;
    bVar2 = true;
    pcVar8 = DAT_1002c5c8;
  }
  if (bVar2) {
    _lock(1);
  }
  if (pcVar8 == (code *)0x1) {
    if (!bVar2) {
      return 0;
    }
    _unlock(1);
    return 0;
  }
  if (pcVar8 == (code *)0x0) {
    if (bVar2) {
      _unlock(1);
    }
    exit(3);
  }
  if (((param_1 == (int *)0x8) || (param_1 == (int *)0xb)) || (param_1 == (int *)0x4)) {
    piVar1 = (int *)piVar4[0x15];
    bVar10 = param_1 == (int *)0x8;
    piVar4[0x15] = 0;
    param_1 = piVar1;
    if (bVar10) {
      local_4 = piVar4[0x16];
      piVar4[0x16] = 0x8c;
      goto LAB_10020bd3;
    }
  }
  else {
LAB_10020bd3:
    if (piVar3 == (int *)0x8) {
      if (DAT_10029af0 < DAT_10029af4 + DAT_10029af0) {
        iVar7 = DAT_10029af0 * 0xc;
        iVar6 = DAT_10029af0;
        do {
          iVar6 = iVar6 + 1;
          *(undefined4 *)(piVar4[0x14] + 8 + iVar7) = 0;
          iVar7 = iVar7 + 0xc;
        } while (iVar6 < DAT_10029af4 + DAT_10029af0);
      }
      goto LAB_10020c18;
    }
  }
  *puVar9 = 0;
LAB_10020c18:
  if (bVar2) {
    _unlock(1);
  }
  if (piVar3 == (int *)0x8) {
    (*pcVar8)(8,piVar4[0x16]);
  }
  else {
    (*pcVar8)(piVar3);
    if ((piVar3 != (int *)0xb) && (piVar3 != (int *)0x4)) {
      return 0;
    }
  }
  piVar4[0x15] = (int)param_1;
  if (piVar3 == (int *)0x8) {
    piVar4[0x16] = local_4;
  }
  return 0;
}
#undef local_4


/* ---- 0x10020cb0  siglookup ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

uint __cdecl siglookup(int param_1,uint param_2)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = param_2;
  if (*(int *)(param_2 + 4) != param_1) {
    uVar3 = param_2;
    do {
      uVar2 = uVar3 + 0xc;
      if (param_2 + DAT_10029afc * 0xc <= uVar2) break;
      piVar1 = (int *)(uVar3 + 0x10);
      uVar3 = uVar2;
    } while (*piVar1 != param_1);
  }
  if ((param_2 + DAT_10029afc * 0xc <= uVar2) || (*(int *)(uVar2 + 4) != param_1)) {
    uVar2 = 0;
  }
  return uVar2;
}

/* ---- 0x10020cf0  __addl ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl __addl(uint param_1,uint param_2,uint *param_3)

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

/* ---- 0x10020d20  __add_12 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __add_12(uint *param_1,uint *param_2)

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

/* ---- 0x10020d90  __shl_12 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __shl_12(uint *param_1)

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

/* ---- 0x10020dc0  __shr_12 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __shr_12(uint *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  param_1[1] = uVar1 >> 1 | param_1[2] << 0x1f;
  param_1[2] = param_1[2] >> 1;
  *param_1 = *param_1 >> 1 | uVar1 << 0x1f;
  return;
}

/* ---- 0x10020df0  __mtold12 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __mtold12(char *param_1,int param_2,uint *param_3)

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


/* ---- 0x10020ef0  __strgtold12 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl
__strgtold12(ushort *param_1,int *param_2,byte *param_3,int param_4,int param_5,int param_6,
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
  #define local_60 (*(int *)(_frame + (0x70 - 0x60)))
  #define local_5c (*(char **)(_frame + (0x70 - 0x5c)))
  #define local_54 (*(uint *)(_frame + (0x70 - 0x54)))
  #define local_50 (*(byte **)(_frame + (0x70 - 0x50)))
  #define local_4c (*(int *)(_frame + (0x70 - 0x4c)))
  #define local_48 (*(int *)(_frame + (0x70 - 0x48)))
  #define local_30 (*(undefined4 *)(_frame + (0x70 - 0x30)))
  #define local_2c (*(ushort *)(_frame + (0x70 - 0x2c)))
  #define uStack_2a (*(undefined2 *)(_frame + (0x70 - 0x2a)))
  #define uStack_28 (*(undefined2 *)(_frame + (0x70 - 0x28)))
  #define local_26 (*(byte **)(_frame + (0x70 - 0x26)))
  #define local_22 (*(ushort *)(_frame + (0x70 - 0x22)))
  #define local_1c (*(char (*)[23])(_frame + (0x70 - 0x1c)))
  #define local_5 (*(char *)(_frame + (0x70 - 0x5)))
  
  local_5c = local_1c;
  iVar8 = 0;
  uVar13 = 0;
  uVar7 = 0;
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
  local_50 = param_3;
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
        goto LAB_100213c2;
      }
      if (bVar10 == DAT_10028b60) {
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
        if (bVar10 != 0x30) goto switchD_100211b2_caseD_2c;
        iVar8 = 1;
      }
      break;
    case 1:
      bVar2 = true;
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto LAB_100213c2;
      }
      if (bVar10 == DAT_10028b60) {
        iVar8 = 4;
      }
      else {
        switch(bVar10) {
        case 0x2b:
        case 0x2d:
          goto switchD_100211b2_caseD_2b;
        default:
          goto switchD_100211b2_caseD_2c;
        case 0x30:
switchD_10021026_caseD_30:
          iVar8 = 1;
          break;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto switchD_100211b2_caseD_44;
        }
      }
      break;
    case 2:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto LAB_100213c2;
      }
      if (bVar10 == DAT_10028b60) {
        iVar8 = 5;
      }
      else {
        if (bVar10 == 0x30) goto switchD_10021026_caseD_30;
        iVar8 = 10;
        pbVar12 = pbVar14;
      }
      break;
    case 3:
      while( true ) {
        bVar2 = true;
        if (DAT_10028b5c < 2) {
          uVar9 = (byte)PTR_DAT_10028950[((uint)param_3 & 0xff) * 2] & 4;
        }
        else {
          uVar9 = _isctype((uint)param_3 & 0xff,4);
        }
        if (uVar9 == 0) break;
        if (uVar13 < 0x19) {
          uVar13 = uVar13 + 1;
          *local_5c = bVar10 - 0x30;
          bVar10 = *pbVar12;
          local_5c = local_5c + 1;
          param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
          pbVar12 = pbVar12 + 1;
        }
        else {
          bVar10 = *pbVar12;
          local_60 = local_60 + 1;
          param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
          pbVar12 = pbVar12 + 1;
        }
      }
      local_54 = uVar13;
      if (bVar10 != DAT_10028b60) {
        switch(bVar10) {
        case 0x2b:
        case 0x2d:
          goto switchD_100211b2_caseD_2b;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto switchD_100211b2_caseD_44;
        }
switchD_100211b2_caseD_2c:
        iVar8 = 10;
        goto LAB_100213c2;
      }
      iVar8 = 4;
      break;
    case 4:
      bVar4 = true;
      if (uVar13 == 0) {
        while (bVar10 == 0x30) {
          bVar10 = *pbVar12;
          local_60 = local_60 + -1;
          pbVar12 = pbVar12 + 1;
          PIECE(param_3,1,3) = (undefined3)((uint)param_3 >> 8);
          param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
        }
      }
      while( true ) {
        bVar2 = true;
        if (DAT_10028b5c < 2) {
          uVar9 = (byte)PTR_DAT_10028950[((uint)param_3 & 0xff) * 2] & 4;
        }
        else {
          uVar9 = _isctype((uint)param_3 & 0xff,4);
        }
        if (uVar9 == 0) break;
        if (uVar13 < 0x19) {
          uVar13 = uVar13 + 1;
          *local_5c = bVar10 - 0x30;
          local_5c = local_5c + 1;
          local_60 = local_60 + -1;
        }
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
      }
      local_54 = uVar13;
      switch(bVar10) {
      case 0x2b:
      case 0x2d:
switchD_100211b2_caseD_2b:
        bVar2 = true;
        pbVar12 = pbVar12 + -1;
        iVar8 = 0xb;
        break;
      default:
        goto switchD_100211b2_caseD_2c;
      case 0x44:
      case 0x45:
      case 100:
      case 0x65:
switchD_100211b2_caseD_44:
        bVar2 = true;
        iVar8 = 6;
      }
      break;
    case 5:
      bVar4 = true;
      if (DAT_10028b5c < 2) {
        uVar9 = (byte)PTR_DAT_10028950[(uint)bVar10 * 2] & 4;
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
      local_50 = pbVar11;
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 9;
        goto LAB_100213c2;
      }
      if (bVar10 == 0x2b) {
LAB_100213b6:
        iVar8 = 7;
        pbVar14 = pbVar11;
        local_50 = pbVar11;
      }
      else {
        if (bVar10 != 0x2d) goto LAB_100212a6;
LAB_100213a7:
        iVar8 = 7;
        local_4c = -1;
        pbVar14 = pbVar11;
        local_50 = pbVar11;
      }
      break;
    case 7:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 9;
        goto LAB_100213c2;
      }
LAB_100212a6:
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
      if (((char)bVar10 < '1') || ('9' < (char)bVar10)) goto switchD_100211b2_caseD_2c;
      iVar8 = 9;
LAB_100213c2:
      pbVar12 = pbVar12 + -1;
      break;
    case 9:
      bVar3 = true;
      local_48 = 0;
      while( true ) {
        if (DAT_10028b5c < 2) {
          uVar13 = (byte)PTR_DAT_10028950[((uint)param_3 & 0xff) * 2] & 4;
        }
        else {
          uVar13 = _isctype((uint)param_3 & 0xff,4);
        }
        if (uVar13 == 0) goto LAB_1002132a;
        local_48 = (char)bVar10 + -0x30 + local_48 * 10;
        if (0x1450 < local_48) break;
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        param_3 = (byte *)CONCAT31(PIECE(param_3,1,3),bVar10);
      }
      local_48 = 0x1451;
LAB_1002132a:
      while( true ) {
        if (DAT_10028b5c < 2) {
          uVar13 = (byte)PTR_DAT_10028950[((uint)param_3 & 0xff) * 2] & 4;
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
      uVar13 = local_54;
      pbVar14 = local_50;
      break;
    case 0xb:
      if (param_7 == 0) goto switchD_100211b2_caseD_2c;
      if (bVar10 == 0x2b) goto LAB_100213b6;
      if (bVar10 == 0x2d) goto LAB_100213a7;
      iVar8 = 10;
      pbVar12 = pbVar11;
      pbVar14 = pbVar11;
      local_50 = pbVar11;
    }
    pbVar11 = pbVar12;
  } while (iVar8 != 10);
  *param_2 = (int)pbVar12;
  if (bVar2) {
    if (0x18 < uVar13) {
      if ('\x04' < local_5) {
        local_5 = local_5 + '\x01';
      }
      local_5c = local_5c + -1;
      local_60 = local_60 + 1;
      uVar13 = 0x18;
    }
    if (uVar13 == 0) {
      local_2c = 0;
      local_22 = 0;
      param_3 = (byte *)0x0;
      pbVar11 = (byte *)0x0;
      goto LAB_10021494;
    }
    cVar1 = local_5c[-1];
    while (cVar1 == '\0') {
      uVar13 = uVar13 - 1;
      local_60 = local_60 + 1;
      cVar1 = local_5c[-2];
      local_5c = local_5c + -1;
    }
    __mtold12(local_1c,uVar13,(uint *)&local_2c);
    if (local_4c < 0) {
      local_48 = -local_48;
    }
    uVar13 = local_48 + local_60;
    if (!bVar3) {
      uVar13 = uVar13 + param_5;
    }
    if (!bVar4) {
      uVar13 = uVar13 - param_6;
    }
    if ((int)uVar13 < 0x1451) {
      if (-0x1451 < (int)uVar13) {
        __multtenpow12((int *)&local_2c,uVar13,param_4);
        pbVar11 = (byte *)CONCAT22(uStack_28,uStack_2a);
        param_3 = local_26;
        goto LAB_10021494;
      }
      bVar6 = true;
    }
    else {
      bVar5 = true;
    }
  }
  local_2c = (ushort)param_3;
  pbVar11 = param_3;
  local_22 = local_2c;
LAB_10021494:
  if (bVar2) {
    if (bVar5) {
      pbVar11 = (byte *)0x0;
      local_22 = 0x7fff;
      param_3 = (byte *)0x80000000;
      local_2c = 0;
      local_30 = 2;
    }
    else if (bVar6) {
      local_2c = 0;
      local_22 = 0;
      param_3 = (byte *)0x0;
      pbVar11 = (byte *)0x0;
      local_30 = 1;
    }
  }
  else {
    local_2c = 0;
    local_22 = 0;
    param_3 = (byte *)0x0;
    pbVar11 = (byte *)0x0;
    local_30 = 4;
  }
  *param_1 = local_2c;
  *(byte **)(param_1 + 1) = pbVar11;
  *(byte **)(param_1 + 3) = param_3;
  param_1[5] = local_22 | uVar7;
  return local_30;
}
#undef local_1c
#undef local_22
#undef local_26
#undef local_2c
#undef local_30
#undef local_48
#undef local_4c
#undef local_5
#undef local_50
#undef local_54
#undef local_5c
#undef local_60
#undef uStack_28
#undef uStack_2a


/* ---- 0x10021680  _I10_OUTPUT ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

undefined4 __cdecl
_I10_OUTPUT(uint param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  short *psVar1;
  ushort uVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  short *psVar7;
  short *psVar8;
  int iVar9;
  short sVar10;
  int iVar11;
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
  #define uStack_e (*(undefined4 *)(_frame + (0x30 - 0xe)))
  #define uStack_a (*(undefined4 *)(_frame + (0x30 - 0xa)))
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
  uVar5 = param_3 & 0x7fff;
  local_12 = 0xfb;
  local_11 = 0x3f;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((short)uVar5 == 0) && (param_2 == 0)) && (param_1 == 0)) {
    *param_6 = 0;
LAB_1002188f:
    *(undefined1 *)(psVar1 + 1) = 0x20;
    *(undefined1 *)((int)psVar1 + 3) = 1;
    *(undefined1 *)(psVar1 + 2) = 0x30;
    *(undefined1 *)((int)psVar1 + 5) = 0;
    return 1;
  }
  if ((short)uVar5 == 0x7fff) {
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
  local_6 = (undefined1)uVar5;
  cStack_5 = (char)(uVar5 >> 8);
  local_10 = 0;
  sVar10 = (short)(((uVar5 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar5 * 0x4d10 >>
                  0x10);
  uStack_a = param_2;
  uStack_e = param_1;
  __multtenpow12((int *)&local_10,-(int)sVar10,1);
  if (0x3ffe < CONCAT11(cStack_5,local_6)) {
    sVar10 = sVar10 + 1;
    __ld12mul((int *)&local_10,(int *)&local_1c);
  }
  *psVar1 = sVar10;
  iVar9 = param_4;
  if (((param_5 & 1) != 0) && (iVar9 = param_4 + sVar10, param_4 + sVar10 < 1)) {
    *psVar1 = 0;
    goto LAB_1002188f;
  }
  if (0x15 < iVar9) {
    iVar9 = 0x15;
  }
  uVar2 = CONCAT11(cStack_5,local_6);
  local_6 = 0;
  cStack_5 = '\0';
  iVar6 = 8;
  iVar11 = uVar2 - 0x3ffe;
  do {
    __shl_12((uint *)&local_10);
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  if (iVar11 < 0) {
    for (uVar5 = -iVar11 & 0xff; uVar5 != 0; uVar5 = uVar5 - 1) {
      __shr_12((uint *)&local_10);
    }
  }
  psVar1 = psVar1 + 2;
  iVar9 = iVar9 + 1;
  psVar7 = psVar1;
  uVar5 = uStack_e;
  uVar3 = uStack_a;
  if (0 < iVar9) {
    do {
      PIECE(uStack_a,2,2) = (undefined2)(uVar3 >> 0x10);
      PIECE(uStack_a,0,2) = (undefined2)uVar3;
      PIECE(uStack_e,2,2) = (undefined2)(uVar5 >> 0x10);
      PIECE(uStack_e,0,2) = (undefined2)uVar5;
      param_1 = CONCAT22((undefined2)uStack_e,local_10);
      param_2 = CONCAT22((undefined2)uStack_a,PIECE(uStack_e,2,2));
      param_3 = CONCAT13(cStack_5,CONCAT12(local_6,PIECE(uStack_a,2,2)));
      uStack_e = uVar5;
      uStack_a = uVar3;
      __shl_12((uint *)&local_10);
      __shl_12((uint *)&local_10);
      __add_12((uint *)&local_10,&param_1);
      __shl_12((uint *)&local_10);
      cVar4 = cStack_5 + '0';
      cStack_5 = '\0';
      *(char *)psVar7 = cVar4;
      psVar7 = (short *)((int)psVar7 + 1);
      iVar9 = iVar9 + -1;
      uVar5 = uStack_e;
      uVar3 = uStack_a;
    } while (iVar9 != 0);
  }
  psVar8 = psVar7 + -1;
  if (*(char *)((int)psVar7 + -1) < '5') {
    if (psVar1 <= psVar8) {
      do {
        if ((char)*psVar8 != '0') break;
        psVar8 = (short *)((int)psVar8 + -1);
      } while (psVar1 <= psVar8);
      if (psVar1 <= psVar8) goto LAB_100219e6;
    }
    *(char *)psVar1 = '0';
    *param_6 = 0;
    *(undefined1 *)(param_6 + 1) = 0x20;
    *(undefined1 *)((int)param_6 + 3) = 1;
    *(undefined1 *)((int)param_6 + 5) = 0;
    return 1;
  }
  if (psVar1 <= psVar8) {
    do {
      if ((char)*psVar8 != '9') break;
      *(char *)psVar8 = '0';
      psVar8 = (short *)((int)psVar8 + -1);
    } while (psVar1 <= psVar8);
    if (psVar1 <= psVar8) {
      *(char *)psVar8 = (char)*psVar8 + '\x01';
      goto LAB_100219e6;
    }
  }
  psVar8 = (short *)((int)psVar8 + 1);
  *param_6 = *param_6 + 1;
  *(char *)psVar8 = *(char *)psVar8 + '\x01';
LAB_100219e6:
  cVar4 = ((char)psVar8 - (char)param_6) + -3;
  *(char *)((int)param_6 + 3) = cVar4;
  *(undefined1 *)((int)param_6 + cVar4 + 4) = 0;
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
#undef uStack_a
#undef uStack_e


/* ---- 0x10021a80  realloc ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

int * __cdecl realloc(int *param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  int *piVar7;
  #define local_8 (*(int **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  if (param_1 == (int *)0x0) {
    piVar1 = (int *)malloc(param_2);
    return piVar1;
  }
  if (param_2 == 0) {
    free((undefined *)param_1);
    return (int *)0x0;
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
    piVar1 = (int *)0x0;
    if (uVar4 < 0xffffffe1) {
      _lock(9);
      pbVar2 = (byte *)__sbh_find_block((undefined *)param_1,&local_4,(uint *)&local_8);
      if (pbVar2 == (byte *)0x0) {
        _unlock(9);
        piVar1 = (int *)HeapReAlloc(DAT_1002c5d4,0,(int)param_1,uVar4);
      }
      else {
        if (uVar4 < DAT_1002bb24) {
          iVar3 = __sbh_resize_block(local_4,local_8,pbVar2,uVar4 >> 4);
          piVar1 = param_1;
          if (iVar3 != 0) goto LAB_10021b85;
          piVar1 = __sbh_alloc_block(uVar4 >> 4);
          if (piVar1 != (int *)0x0) {
            uVar5 = (uint)*pbVar2 << 4;
            if (uVar4 <= (uint)*pbVar2 << 4) {
              uVar5 = uVar4;
            }
            piVar6 = param_1;
            piVar7 = piVar1;
            for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
              *piVar7 = *piVar6;
              piVar6 = piVar6 + 1;
              piVar7 = piVar7 + 1;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(char *)piVar7 = (char)*piVar6;
              piVar6 = (int *)((int)piVar6 + 1);
              piVar7 = (int *)((int)piVar7 + 1);
            }
            __sbh_free_block(local_4,(int)local_8,pbVar2);
            uVar4 = param_2;
            goto LAB_10021b85;
          }
LAB_10021b89:
          piVar1 = (int *)HeapAlloc(DAT_1002c5d4,0,uVar4);
          if (piVar1 != (int *)0x0) {
            uVar5 = (uint)*pbVar2 << 4;
            if (uVar4 <= (uint)*pbVar2 << 4) {
              uVar5 = uVar4;
            }
            piVar6 = param_1;
            piVar7 = piVar1;
            for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
              *piVar7 = *piVar6;
              piVar6 = piVar6 + 1;
              piVar7 = piVar7 + 1;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(char *)piVar7 = (char)*piVar6;
              piVar6 = (int *)((int)piVar6 + 1);
              piVar7 = (int *)((int)piVar7 + 1);
            }
            __sbh_free_block(local_4,(int)local_8,pbVar2);
            uVar4 = param_2;
          }
        }
        else {
LAB_10021b85:
          if (piVar1 == (int *)0x0) goto LAB_10021b89;
        }
        _unlock(9);
      }
    }
    if ((piVar1 != (int *)0x0) || (DAT_1002c59c == 0)) {
      return piVar1;
    }
    iVar3 = _callnewh(uVar4);
    if (iVar3 == 0) {
      return (int *)0x0;
    }
  } while( true );
}
#undef local_4
#undef local_8


/* ---- 0x10021c30  __ld12mul ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __ld12mul(int *param_1,int *param_2)

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
  #define local_20 (*(short **)(_frame + (0x30 - 0x20)))
  #define local_18 (*(int *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(int *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(int *)(_frame + (0x30 - 0x10)))
  #define local_c (*(byte *)(_frame + (0x30 - 0xc)))
  #define uStack_b (*(undefined1 *)(_frame + (0x30 - 0xb)))
  #define uStack_a (*(undefined2 *)(_frame + (0x30 - 0xa)))
  #define local_8 (*(short *)(_frame + (0x30 - 0x8)))
  #define uStack_6 (*(undefined2 *)(_frame + (0x30 - 0x6)))
  #define local_4 (*(undefined2 *)(_frame + (0x30 - 0x4)))
  #define uStack_2 (*(ushort *)(_frame + (0x30 - 0x2)))
  
  local_14 = 0;
  local_c = 0;
  uStack_b = 0;
  uStack_a = 0;
  local_8 = 0;
  uStack_6 = 0;
  uVar3 = *(ushort *)((int)param_2 + 10) & 0x7fff;
  uVar1 = *(ushort *)((int)param_1 + 10) & 0x7fff;
  uVar6 = (*(ushort *)((int)param_2 + 10) ^ *(ushort *)((int)param_1 + 10)) & 0x8000;
  uVar4 = uVar3 + uVar1;
  local_4 = 0;
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
  local_20 = &local_8;
  local_18 = 0;
  iVar5 = 5;
  do {
    if (0 < iVar5) {
      puVar8 = (ushort *)(param_2 + 2);
      puVar7 = (ushort *)(local_18 * 2 + (int)param_1);
      local_10 = iVar5;
      do {
        iVar2 = __addl(*(uint *)(local_20 + -2),(uint)*puVar8 * (uint)*puVar7,
                       (uint *)(local_20 + -2));
        if (iVar2 != 0) {
          *local_20 = *local_20 + 1;
        }
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + -1;
        local_10 = local_10 + -1;
      } while (local_10 != 0);
    }
    local_20 = local_20 + 1;
    local_18 = local_18 + 1;
    iVar5 = iVar5 + -1;
  } while (0 < iVar5);
  uVar4 = uVar4 + 0xc002;
  while ((0 < (short)uVar4 && ((uStack_2 & 0x8000) == 0))) {
    __shl_12((uint *)&local_c);
    uVar4 = uVar4 - 1;
  }
  if ((short)uVar4 < 1) {
    uVar4 = uVar4 - 1;
    if ((short)uVar4 < 0) {
      iVar5 = -(int)(short)uVar4;
      uVar4 = uVar4 + (short)iVar5;
      do {
        if ((local_c & 1) != 0) {
          local_14 = local_14 + 1;
        }
        __shr_12((uint *)&local_c);
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if (local_14 != 0) {
      local_c = local_c | 1;
    }
  }
  if ((0x8000 < CONCAT11(uStack_b,local_c)) ||
     (iVar2 = CONCAT22(local_4,uStack_6), iVar5 = CONCAT22(local_8,uStack_a),
     (CONCAT22(uStack_a,CONCAT11(uStack_b,local_c)) & 0x1ffff) == 0x18000)) {
    if (CONCAT22(local_8,uStack_a) == -1) {
      iVar5 = 0;
      if (CONCAT22(local_4,uStack_6) == -1) {
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
        iVar2 = CONCAT22(local_4,uStack_6) + 1;
      }
    }
    else {
      iVar5 = CONCAT22(local_8,uStack_a) + 1;
      iVar2 = CONCAT22(local_4,uStack_6);
    }
  }
  local_8 = (short)((uint)iVar5 >> 0x10);
  uStack_a = (undefined2)iVar5;
  local_4 = (undefined2)((uint)iVar2 >> 0x10);
  uStack_6 = (undefined2)iVar2;
  if (0x7ffe < uVar4) {
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar6 != 0) & 0x80000000) + 0x7fff8000;
    return;
  }
  *(undefined2 *)param_1 = uStack_a;
  *(uint *)((int)param_1 + 2) = CONCAT22(uStack_6,local_8);
  *(uint *)((int)param_1 + 6) = CONCAT22(uStack_2,local_4);
  *(ushort *)((int)param_1 + 10) = uVar4 | uVar6;
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_20
#undef local_4
#undef local_8
#undef local_c
#undef uStack_2
#undef uStack_6
#undef uStack_a
#undef uStack_b


/* ---- 0x10021ef0  __multtenpow12 ---- */
/* MSVC 6 C runtime (matched against the EXE runtime by structure) */

void __cdecl __multtenpow12(int *param_1,uint param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int *piVar2;
  int iVar3;
  #define local_c (*(undefined2 *)(_frame + (0x20 - 0xc)))
  #define uStack_a (*(undefined4 *)(_frame + (0x20 - 0xa)))
  #define uStack_6 (*(undefined2 *)(_frame + (0x20 - 0x6)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar3 = IMG_ADDR(0x1002bb90);
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      iVar3 = IMG_ADDR(0x1002bcf0);
    }
    if (param_3 == 0) {
      *(undefined2 *)param_1 = 0;
    }
    while (param_2 != 0) {
      iVar3 = iVar3 + 0x54;
      uVar1 = param_2 & 7;
      param_2 = (int)param_2 >> 3;
      if (uVar1 != 0) {
        piVar2 = (int *)(iVar3 + uVar1 * 0xc);
        if (0x7fff < *(ushort *)(iVar3 + uVar1 * 0xc)) {
          local_c = (undefined2)*piVar2;
          PIECE(uStack_a,0,2) = (undefined2)((uint)*piVar2 >> 0x10);
          PIECE(uStack_a,2,2) = (undefined2)piVar2[1];
          uStack_6 = (undefined2)((uint)piVar2[1] >> 0x10);
          local_4 = piVar2[2];
          uStack_a = CONCAT22(PIECE(uStack_a,2,2),(undefined2)uStack_a) + -1;
          piVar2 = (int *)&local_c;
        }
        __ld12mul(param_1,piVar2);
      }
    }
  }
  return;
}
#undef local_4
#undef local_c
#undef uStack_6
#undef uStack_a

