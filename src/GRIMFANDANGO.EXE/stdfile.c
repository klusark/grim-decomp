/* GRIMFANDANGO.EXE :: stdfile.c
 * functions 0x004c5e30 .. 0x004c5f50 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004c5e30  StdFile_fle_Tell ---- */
/* Returns the current position of a StdFile through the file service Original name StdFile_fle_Tell
   (the remaster's GrimFandango (Linux): slot 4 of the "FILE=insane_stdfile" service table; fle_Tell
   is a static several LEC modules have, written with the module prefix); was StdFile_Tell. */

int __cdecl StdFile_fle_Tell(void *file)

{
  int iVar1;
  
  iVar1 = (*(code *)g_pStdFile_filio_services[4])(file);
  return iVar1;
}

/* ---- 0x004c5e90  fle_Size ---- */
/* Returns the size of a StdFile by seeking to its end and back Original name fle_Size (the
   remaster's GrimFandango (Linux): slot 7 of the "FILE=insane_stdfile" service table); was
   StdFile_Size. */

int __cdecl fle_Size(void *file)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = (*(code *)g_pStdFile_filio_services[4])(file);
  (*(code *)g_pStdFile_filio_services[5])(file,0,2);
  iVar2 = (*(code *)g_pStdFile_filio_services[4])(file);
  (*(code *)g_pStdFile_filio_services[5])(file,uVar1,0);
  return iVar2;
}

/* ---- 0x004c5f50  fle_Eof ---- */
/* True when the position of a StdFile is at or past its size Original name fle_Eof (the remaster's
   GrimFandango (Linux): slot 9 of the "FILE=insane_stdfile" service table); was StdFile_IsEof. */

int __cdecl fle_Eof(void *file)

{
  int iVar1;
  int iVar2;
  
  iVar1 = fle_Size(file);
  iVar2 = StdFile_fle_Tell(file);
  return (uint)(iVar1 <= iVar2);
}
