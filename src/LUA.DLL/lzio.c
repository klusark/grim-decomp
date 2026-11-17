/* LUA.DLL :: lzio.c
 * functions 0x1000edc0 .. 0x1000ef40 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000edc0  luaZ_mopen ---- */
/* Unidentified function of lvm.c (virtual machine) */

undefined4 * __cdecl luaZ_mopen(undefined4 *z,int b,undefined4 size,undefined4 name)

{
  if (b == 0) {
    return (undefined4 *)0x0;
  }
  z[1] = b;
  *z = size;
  z[2] = zmfilbuf;
  z[3] = 0;
  z[4] = name;
  return z;
}

/* ---- 0x1000edf0  zmfilbuf ---- */
/* Original name zmfilbuf (the remaster's libLua.so: static zmfilbuf: returns EOZ (-1)); was
   FUN_1000edf0. */

undefined4 zmfilbuf(void)

{
  return 0xffffffff;
}

/* ---- 0x1000ee00  luaZ_sopen ---- */
/* Unidentified function of lvm.c (virtual machine) */

undefined4 * __cdecl luaZ_sopen(undefined4 *z,char *s,undefined4 name)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  char *pcVar4;
  
  if (s == (char *)0x0) {
    return (undefined4 *)0x0;
  }
  uVar3 = 0xffffffff;
  pcVar4 = s;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  puVar2 = luaZ_mopen(z,(int)s,~uVar3 - 1,name);
  return puVar2;
}

/* ---- 0x1000ee30  luaZ_Fopen ---- */
undefined4 * __cdecl luaZ_Fopen(undefined4 *z,int f,undefined4 name)

{
                    /* 0xee30  5  luaZ_Fopen */
  if (f == 0) {
    return (undefined4 *)0x0;
  }
  z[3] = f;
  *z = 0;
  z[1] = z + 5;
  z[2] = zffilbuf;
  z[4] = name;
  return z;
}

/* ---- 0x1000ee60  zffilbuf ---- */
/* Original name zffilbuf (the remaster's libLua.so: static zffilbuf: refills 256 bytes through the
   service table +0x38); was FUN_1000ee60. */

uint __cdecl zffilbuf(int *z)

{
  byte *pbVar1;
  int iVar2;
  
  pbVar1 = (byte *)(z + 5);
  iVar2 = (**(code **)(g_dwLuaHS + 0x38))(z[3],pbVar1,0x100);
  if (iVar2 == 0) {
    return 0xffffffff;
  }
  z[1] = (int)pbVar1;
  *z = iVar2 + -1;
  z[1] = (int)z + 0x15;
  return (uint)*pbVar1;
}

/* ---- 0x1000eea0  luaZ_read ---- */
/* Unidentified function of lzio.c (input streams) */

uint __cdecl luaZ_read(uint *z,undefined4 *b,uint n)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if (n == 0) {
    return 0;
  }
  do {
    if (*z == 0) {
      iVar1 = (*(code *)z[2])(z);
      if (iVar1 == -1) {
        return n;
      }
      *z = *z + 1;
      z[1] = z[1] - 1;
    }
    uVar2 = *z;
    if ((int)n <= (int)*z) {
      uVar2 = n;
    }
    puVar4 = (undefined4 *)z[1];
    puVar5 = b;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    b = (undefined4 *)((int)b + uVar2);
    for (uVar3 = uVar2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    n = n - uVar2;
    *z = *z - uVar2;
    z[1] = z[1] + uVar2;
  } while (n != 0);
  return 0;
}

/* ---- 0x1000ef20  _fpmath ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* MSVC C runtime _fpmath: _cfltcvt_init, then the floating-point start-up of the runtime. (Placed
   with lzio.c by address only.); was lzio__ef20. */

void _fpmath(void)

{
  _cfltcvt_init();
  _DAT_1002bf8c = FUN_10012f30();
  FUN_10012ec0();
  return;
}

/* ---- 0x1000ef40  _cfltcvt_init ---- */
/* MSVC C runtime _cfltcvt_init: fills the floating-point conversion table (_cfltcvt, _cropzeros,
   _fassign, _forcdecpt, _positive, _cldcvt) that printf / scanf use; was lzio__ef40. */

void _cfltcvt_init(void)

{
  PTR_FUN_10028b7c = FUN_10012fc0;
  PTR_FUN_10028b78 = FUN_10013420;
  PTR_FUN_10028b80 = FUN_10013050;
  PTR_FUN_10028b84 = FUN_10012f60;
  PTR_FUN_10028b88 = FUN_10013030;
  PTR_FUN_10028b8c = FUN_10013420;
  return;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
typedef struct __attribute__((packed)) { void *p0; void *p4; unsigned char b8[12]; } grim_span_10028b8c;
extern char f_FUN_1001ddc0[] __asm__("_FUN_1001ddc0");
extern char f_FUN_1001ddd0[] __asm__("_FUN_1001ddd0");
extern unsigned char grim_def_DAT_1002bf8c[4] __asm__("_DAT_1002bf8c");
extern void *grim_def_PTR_FUN_10028b78 __asm__("_PTR_FUN_10028b78");
extern void *grim_def_PTR_FUN_10028b7c __asm__("_PTR_FUN_10028b7c");
extern void *grim_def_PTR_FUN_10028b80 __asm__("_PTR_FUN_10028b80");
extern void *grim_def_PTR_FUN_10028b84 __asm__("_PTR_FUN_10028b84");
extern void *grim_def_PTR_FUN_10028b88 __asm__("_PTR_FUN_10028b88");
extern grim_span_10028b8c grim_def_PTR_FUN_10028b8c __asm__("_PTR_FUN_10028b8c");
/* 0x10028b78, 4 bytes */ GRIM_DATA("10028b78") void *grim_def_PTR_FUN_10028b78 __asm__("_PTR_FUN_10028b78") = (void *)f_FUN_1001ddc0;
/* 0x10028b7c, 4 bytes */ GRIM_DATA("10028b7c") void *grim_def_PTR_FUN_10028b7c __asm__("_PTR_FUN_10028b7c") = (void *)f_FUN_1001ddc0;
/* 0x10028b80, 4 bytes */ GRIM_DATA("10028b80") void *grim_def_PTR_FUN_10028b80 __asm__("_PTR_FUN_10028b80") = (void *)f_FUN_1001ddc0;
/* 0x10028b84, 4 bytes */ GRIM_DATA("10028b84") void *grim_def_PTR_FUN_10028b84 __asm__("_PTR_FUN_10028b84") = (void *)f_FUN_1001ddc0;
/* 0x10028b88, 4 bytes */ GRIM_DATA("10028b88") void *grim_def_PTR_FUN_10028b88 __asm__("_PTR_FUN_10028b88") = (void *)f_FUN_1001ddc0;
/* 0x10028b8c, 20 bytes */ GRIM_DATA("10028b8c") grim_span_10028b8c grim_def_PTR_FUN_10028b8c __asm__("_PTR_FUN_10028b8c") = {
    (void *)f_FUN_1001ddc0,
    (void *)f_FUN_1001ddd0,
    {0}
};
/* 0x1002bf8c, 4 bytes */ /* loose */ unsigned char grim_def_DAT_1002bf8c[4] __asm__("_DAT_1002bf8c") = {0};
