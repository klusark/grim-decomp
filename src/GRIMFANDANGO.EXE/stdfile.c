/* GRIMFANDANGO.EXE :: stdfile.c
 * functions 0x004c5e30 .. 0x004c5f50 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004c5e30  StdFile_Tell ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Returns the current position of a StdFile through the file service */

int __cdecl StdFile_Tell(void *file)

{
  int iVar1;
  
  iVar1 = (*(code *)g_pStdFileIo[4])(file);
  return iVar1;
}
#endif


/* ---- 0x004c5e90  StdFile_Size ---- */
/* Returns the size of a StdFile by seeking to its end and back */

int __cdecl StdFile_Size(void *file)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = (*(code *)g_pStdFileIo[4])(file);
  (*(code *)g_pStdFileIo[5])(file,0,2);
  iVar2 = (*(code *)g_pStdFileIo[4])(file);
  (*(code *)g_pStdFileIo[5])(file,uVar1,0);
  return iVar2;
}

/* ---- 0x004c5f50  StdFile_IsEof ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* True when the position of a StdFile is at or past its size */

int __cdecl StdFile_IsEof(void *file)

{
  int iVar1;
  int iVar2;
  
  iVar1 = StdFile_Size(file);
  iVar2 = StdFile_Tell(file);
  return (uint)(iVar1 <= iVar2);
}
#endif

