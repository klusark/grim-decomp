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

void __cdecl stdPlatform_Assert(uint msg,char *file,uint line)

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
  cVar2 = *file;
  while (cVar2 != '\0') {
    if (cVar2 == '\\') {
      bVar3 = true;
      iVar5 = iVar4;
    }
    iVar1 = iVar4 + 1;
    iVar4 = iVar4 + 1;
    cVar2 = file[iVar1];
  }
  if (bVar3) {
    iVar5 = iVar5 + 1;
  }
  _snprintf(acStack_200,0x200,s__s__d____s_004dee38,file + iVar5,line,msg);
  fp = fopen(((unsigned)(uintptr_t)&DAT_004dee28),((unsigned)(uintptr_t)&s_wt_004dee34));
  if (fp != (undefined *)0x0) {
    fprintf(fp,acStack_200);
    fclose((int)fp);
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

uint __cdecl stdPlatform_AllocHandle(uint size)

{
  undefined *puVar1;
  
  puVar1 = malloc(size);
  return (uint)puVar1;
}

/* ---- 0x00478040  stdPlatform_FreeHandle ---- */
/* GrimServices.pHFree of the platform table: free. Original name stdPlatform_FreeHandle (the
   remaster's GrimFandango (Linux): same body (free); after stdPlatform_AllocHandle in both builds);
   was PlatSvc_HFree. */

void __cdecl stdPlatform_FreeHandle(uint handle)

{
  free(handle);
  return;
}

/* ---- 0x00478050  stdPlatform_ReallocHandle ---- */
/* GrimServices.pHRealloc of the platform table: realloc. Original name stdPlatform_ReallocHandle
   (the remaster's GrimFandango (Linux): same body (realloc); after stdPlatform_FreeHandle in both
   builds); was PlatSvc_HRealloc. */

uint __cdecl stdPlatform_ReallocHandle(uint handle,uint size)

{
  undefined4 *puVar1;
  
  puVar1 = realloc((undefined4 *)handle,size);
  return (uint)puVar1;
}

/* ---- 0x00478070  stdPlatform_LockHandle ---- */
/* GrimServices.pHLock of the platform table: handles are plain pointers, returns its argument.
   Original name stdPlatform_LockHandle (the remaster's GrimFandango (Linux): same body (returns the
   handle); after stdPlatform_ReallocHandle in both builds); was PlatSvc_HLock. */

uint __cdecl stdPlatform_LockHandle(uint handle)

{
  return handle;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_004dee28[12] __asm__("_DAT_004dee28");
extern unsigned int grim_def_g_dwStdPlatform_Assert_enteredOnce __asm__("_g_dwStdPlatform_Assert_enteredOnce");
extern char grim_def_s_Assert_Handler_004dee18[16] __asm__("_s_Assert_Handler_004dee18");
extern char grim_def_s__s__d____s_004dee38[16] __asm__("_s__s__d____s_004dee38");
/* 0x004dee18, 16 bytes */ GRIM_DATA("004dee18") char grim_def_s_Assert_Handler_004dee18[16] __asm__("_s_Assert_Handler_004dee18") = "Assert Handler";
/* 0x004dee28, 12 bytes */ GRIM_DATA("004dee28") unsigned char grim_def_DAT_004dee28[12] __asm__("_DAT_004dee28") = { 0x61, 0x73, 0x73, 0x65, 0x72, 0x74, 0x2e, 0x74, 0x78, 0x74 };
/* 0x004dee38, 16 bytes */ GRIM_DATA("004dee38") char grim_def_s__s__d____s_004dee38[16] __asm__("_s__s__d____s_004dee38") = "%s(%d):  %s\n";
/* 0x00805fd4, 4 bytes */ GRIM_DATA("00805fd4") unsigned int grim_def_g_dwStdPlatform_Assert_enteredOnce __asm__("_g_dwStdPlatform_Assert_enteredOnce") = 0x0;
