/* GRIMFANDANGO.EXE :: platsvc.c
 * functions 0x00477f10 .. 0x00478070 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00477f10  stdPlatform_Assert ---- */
/* GrimServices.pAssertFail of the platform table (stdPlatform_InitServices; the default table of
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
  _snprintf(acStack_200,0x200,s__s__d____s_004dee38,param_2 + iVar5,param_3,param_1);
  fp = fopen(((unsigned)(uintptr_t)&DAT_004dee28),((unsigned)(uintptr_t)&DAT_004dee34));
  if (fp != (undefined *)0x0) {
    fprintf(fp,acStack_200);
    fclose(fp);
  }
  MessageBoxA(0,(int)acStack_200,((unsigned)(uintptr_t)&s_Assert_Handler_004dee18),0x2000);
  DebugBreak();
  exit(1);
  return;
}
#undef acStack_200


/* ---- 0x00478030  stdPlatform_AllocHandle ---- */
/* GrimServices.pHAlloc of the platform table: malloc. Original name stdPlatform_AllocHandle (the
   remaster's GrimFandango (Linux): same body (malloc); the platform handle service set in both
   builds); was PlatSvc_HAlloc. */

void stdPlatform_AllocHandle(uint param_1)

{
  malloc(param_1);
  return;
}

/* ---- 0x00478040  stdPlatform_FreeHandle ---- */
/* GrimServices.pHFree of the platform table: free. Original name stdPlatform_FreeHandle (the
   remaster's GrimFandango (Linux): same body (free); after stdPlatform_AllocHandle in both builds);
   was PlatSvc_HFree. */

void stdPlatform_FreeHandle(undefined4 param_1)

{
  free(param_1);
  return;
}

/* ---- 0x00478050  stdPlatform_ReallocHandle ---- */
/* GrimServices.pHRealloc of the platform table: realloc. Original name stdPlatform_ReallocHandle
   (the remaster's GrimFandango (Linux): same body (realloc); after stdPlatform_FreeHandle in both
   builds); was PlatSvc_HRealloc. */

void stdPlatform_ReallocHandle(undefined4 param_1,undefined4 param_2)

{
  realloc(param_1,param_2);
  return;
}

/* ---- 0x00478070  stdPlatform_LockHandle ---- */
/* GrimServices.pHLock of the platform table: handles are plain pointers, returns its argument.
   Original name stdPlatform_LockHandle (the remaster's GrimFandango (Linux): same body (returns the
   handle); after stdPlatform_ReallocHandle in both builds); was PlatSvc_HLock. */

undefined4 stdPlatform_LockHandle(undefined4 param_1)

{
  return param_1;
}
