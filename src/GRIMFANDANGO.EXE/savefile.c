/* GRIMFANDANGO.EXE :: savefile.c
 * functions 0x00488d80 .. 0x004c3e40 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00488d80  SaveFile_CheckFUTBHeader ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Reads three dwords through readFn and expects 'FUTB', 1, 0. Returns 0 when the header matches, 1
   otherwise. */

undefined4 SaveFile_CheckFUTBHeader(code *param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  
  pcVar1 = param_1;
  uVar2 = 1;
  (*param_1)(&param_1,4);
  if (param_1 == (code *)0x42545546) {
    (*pcVar1)(&param_1,4);
    if (param_1 == (code *)0x1) {
      (*pcVar1)(&param_1,4);
      if (param_1 == (code *)0x0) {
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}
#endif


/* ---- 0x004c3e40  SaveFile_Open ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * SaveFile_Open(char *name,char *mode)

{
  void *pvVar1;
  
  pvVar1 = (void *)gz_open(name,mode,0xffffffff);
  return pvVar1;
}
