/* GRIMFANDANGO.EXE :: platsvc.c
 * functions 0x00477f10 .. 0x00478070 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00477f10  stdPlatform_Assert ---- */
/* GrimServices.pAssertFail of the platform table (Services_InitPlatformTable; the default table of
   Svc_* functions has its own Svc_AssertFail): logs 'file(line): message' to an assert file and
   aborts (DebugBreak + exit(1)); a second failure while handling the first exits immediately.
   Original name stdPlatform_Assert (the remaster's GrimFandango (Linux): strings: '%s(%d):  %s\n');
   was PlatSvc_AssertFail. */

void stdPlatform_Assert(undefined4 param_1,char *param_2,undefined4 param_3)

{
  unsigned char _frame[0x210] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  undefined *fp;
  int iVar5;
  #define acStack_200 (*(char (*)[512])(_frame + (0x210 - 0x200)))
  
  iVar5 = 0;
  bVar3 = false;
  if (g_dwStdPlatform_Assert_enteredOnce != 0) {
    DebugBreak();
    exit(1);
  }
  g_dwStdPlatform_Assert_enteredOnce = 1;
  iVar4 = 0;
  cVar2 = *param_2;
  while (cVar2 != '\0') {
    if (cVar2 == '\\') {
      bVar3 = true;
      iVar5 = iVar4;
    }
    iVar1 = iVar4 + 1;
    iVar4 = iVar4 + 1;
    cVar2 = param_2[iVar1];
  }
  if (bVar3) {
    iVar5 = iVar5 + 1;
  }
  ((code *)_vsnprintf)(acStack_200,0x200,s__s__d____s_004dee38,param_2 + iVar5,param_3,param_1);
  fp = fopen(IMG_ADDR(0x004dee28),IMG_ADDR(0x004dee34));
  if (fp != (undefined *)0x0) {
    fprintf(fp,acStack_200);
    fclose(fp);
  }
  MessageBoxA(0,(int)acStack_200,IMG_ADDR(0x004dee18),0x2000);
  DebugBreak();
  exit(1);
  return;
}
#undef acStack_200


/* ---- 0x00478030  PlatSvc_HAlloc ---- */
/* GrimServices.pHAlloc of the platform table: malloc. */

void PlatSvc_HAlloc(uint param_1)

{
  malloc(param_1);
  return;
}

/* ---- 0x00478040  PlatSvc_HFree ---- */
/* GrimServices.pHFree of the platform table: free. */

void PlatSvc_HFree(undefined4 param_1)

{
  free(param_1);
  return;
}

/* ---- 0x00478050  PlatSvc_HRealloc ---- */
/* GrimServices.pHRealloc of the platform table: realloc. */

void PlatSvc_HRealloc(undefined4 param_1,undefined4 param_2)

{
  realloc(param_1,param_2);
  return;
}

/* ---- 0x00478070  PlatSvc_HLock ---- */
/* GrimServices.pHLock of the platform table: handles are plain pointers, returns its argument. */

undefined4 PlatSvc_HLock(undefined4 param_1)

{
  return param_1;
}
