/* GRIMFANDANGO.EXE :: dsnd.c
 * functions 0x004d23e0 .. 0x004d2ce0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004d23e0  Dsnd_MemCopyCdecl ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Dsnd_MemCopyCdecl(void *dst,void *src,uint n)

{
  Dsnd_MemCopy(dst,src,n);
  return;
}
#endif


/* ---- 0x004d2400  Dsnd_MemFillCdecl ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Dsnd_MemFillCdecl(void *dst,int value,uint n)

{
  Dsnd_MemFill(dst,value,n);
  return;
}
#endif


/* ---- 0x004d2cb0  Dsnd_MemCopy ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* memcpy for the Smush audio code; __fastcall with two unused register arguments (ECX, EDX) */

void __cdecl Dsnd_MemCopy(void *dst,void *src,uint n)

{
  uint uVar1;
  
  if (n != 0) {
    if ((n & 3) != 0) {
      for (uVar1 = n >> 1; uVar1 != 0; uVar1 = uVar1 - 1) {
        *(undefined2 *)dst = *(undefined2 *)src;
        src = (undefined4 *)((int)src + 2);
        dst = (undefined4 *)((int)dst + 2);
      }
      for (uVar1 = (uint)((n & 1) != 0); n = 0, uVar1 != 0; uVar1 = uVar1 - 1) {
        *(undefined1 *)dst = *(undefined1 *)src;
        src = (undefined4 *)((int)src + 1);
        dst = (undefined4 *)((int)dst + 1);
      }
    }
    for (uVar1 = n >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined4 *)dst = *(undefined4 *)src;
      src = (undefined4 *)((int)src + 4);
      dst = (undefined4 *)((int)dst + 4);
    }
  }
  return;
}
#endif


/* ---- 0x004d2ce0  Dsnd_MemFill ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* memset with a byte value for the Smush audio code; __fastcall with two unused register arguments
    */

void __cdecl Dsnd_MemFill(void *dst,int value,uint n)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = CONCAT31(CONCAT21(CONCAT11((undefined1)value,(undefined1)value),(undefined1)value),
                   (undefined1)value);
  if (19999 < (int)n) {
    do {
      for (iVar2 = 5000; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(undefined4 *)dst = uVar1;
        dst = (undefined4 *)((int)dst + 4);
      }
      n = n - 20000;
    } while (20000 < (int)n);
  }
  if ((n & 3) != 0) {
    for (uVar3 = n >> 1; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(short *)dst = (short)uVar1;
      dst = (undefined4 *)((int)dst + 2);
    }
    for (uVar3 = (uint)((n & 1) != 0); uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined1 *)dst = (undefined1)value;
      dst = (undefined4 *)((int)dst + 1);
    }
    return;
  }
  for (uVar3 = n >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)dst = uVar1;
    dst = (undefined4 *)((int)dst + 4);
  }
  return;
}
#endif

