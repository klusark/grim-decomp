/* GRIMFANDANGO.EXE :: stdmemory.c
 * functions 0x0047fe20 .. 0x0047ff70 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0047fe20  stdMemory_CheckMagic ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Asserts the 0x12345678 guard word stored in front of every stdMemory allocation */

void __cdecl stdMemory_CheckMagic(int p)

{
  if (*(int *)(p + -4) != 0x12345678) {
    (*g_pStd_HS->pAssertFail)
              (s_allocation__magic____0x12345678_004e7948,
               s_C__grimjedi_Libs_Std_General_Std_004e7968,DAT_004e7940 + 3);
  }
  return;
}
#endif


/* ---- 0x0047fe50  stdMemory_Alloc ---- */
void * __cdecl stdMemory_Alloc(uint size,char *file,int line)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)malloc(size + 0x1c);
  if (puVar1 == (undefined4 *)0x0) {
    (*g_pStd_HS->pAssertFail)
              (s_allocation_004e7994,s_C__grimjedi_Libs_Std_General_Std_004e7968,DAT_004e7944 + 8);
  }
  UINT_00825e78 = UINT_00825e78 + 1;
  g_dwStdMemory_curState = g_dwStdMemory_curState + size;
  if ((int)UINT_00825e80 <= (int)g_dwStdMemory_curState) {
    UINT_00825e80 = g_dwStdMemory_curState;
  }
  *puVar1 = 0;
  puVar1[1] = UINT_00825e84;
  puVar1[3] = UINT_00825e78;
  puVar1[2] = file;
  puVar1[4] = line;
  puVar1[5] = size;
  puVar1[6] = 0x12345678;
  if (UINT_00825e84 != 0) {
    *(undefined4 **)UINT_00825e84 = puVar1;
  }
  UINT_00825e84 = (uint)puVar1;
  return puVar1 + 7;
}

/* ---- 0x0047ff00  stdMemory_Free ---- */
void __cdecl stdMemory_Free(void *p)

{
  int *piVar1;
  
  if (p != (void *)0x0) {
    piVar1 = (int *)((int)p + -0x1c);
    stdMemory_CheckMagic((int)p);
    UINT_00825e78 = UINT_00825e78 - 1;
    g_dwStdMemory_curState = g_dwStdMemory_curState - *(int *)((int)p + -8);
    if (piVar1 == (int *)UINT_00825e84) {
      UINT_00825e84 = *(uint *)((int)p + -0x18);
    }
    if (*piVar1 != 0) {
      *(undefined4 *)(*piVar1 + 4) = *(undefined4 *)((int)p + -0x18);
    }
    if (*(int **)((int)p + -0x18) != (int *)0x0) {
      **(int **)((int)p + -0x18) = *piVar1;
    }
    free((int)piVar1);
  }
  return;
}

/* ---- 0x0047ff70  stdMemory_Realloc ---- */
void * __cdecl stdMemory_Realloc(void *p,uint size,char *file,int line)

{
  void *pvVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  if (p == (void *)0x0) {
    pvVar1 = stdMemory_Alloc(size,file,line);
    return pvVar1;
  }
  if (size == 0) {
    stdMemory_Free(p);
    return (void *)0x0;
  }
  stdMemory_CheckMagic((int)p);
  puVar2 = stdMemory_Alloc(size,file,line);
  uVar4 = *(uint *)((int)p + -8);
  if ((int)puVar2[-2] < (int)*(uint *)((int)p + -8)) {
    uVar4 = puVar2[-2];
  }
  puVar5 = p;
  puVar6 = puVar2;
  for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
    puVar6 = (undefined4 *)((int)puVar6 + 1);
  }
  stdMemory_Free(p);
  return puVar2;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_004e7940[4] __asm__("_DAT_004e7940");
extern unsigned char grim_def_DAT_004e7944[4] __asm__("_DAT_004e7944");
extern unsigned int grim_def_UINT_00825e78 __asm__("_UINT_00825e78");
extern unsigned int grim_def_UINT_00825e80 __asm__("_UINT_00825e80");
extern unsigned char grim_def_UINT_00825e84[12] __asm__("_UINT_00825e84");
extern char grim_def_s_C__grimjedi_Libs_Std_General_Std_004e7968[44] __asm__("_s_C__grimjedi_Libs_Std_General_Std_004e7968");
extern char grim_def_s_allocation_004e7994[24] __asm__("_s_allocation_004e7994");
extern char grim_def_s_allocation__magic____0x12345678_004e7948[32] __asm__("_s_allocation__magic____0x12345678_004e7948");
/* 0x004e7940, 4 bytes */ /* loose */ unsigned char grim_def_DAT_004e7940[4] __asm__("_DAT_004e7940") = { 0x63, 0x03 };
/* 0x004e7944, 4 bytes */ /* loose */ unsigned char grim_def_DAT_004e7944[4] __asm__("_DAT_004e7944") = { 0x6a, 0x03 };
/* 0x004e7948, 32 bytes */ /* loose */ char grim_def_s_allocation__magic____0x12345678_004e7948[32] __asm__("_s_allocation__magic____0x12345678_004e7948") = "allocation->magic == 0x12345678";
/* 0x004e7968, 44 bytes */ /* loose */ char grim_def_s_C__grimjedi_Libs_Std_General_Std_004e7968[44] __asm__("_s_C__grimjedi_Libs_Std_General_Std_004e7968") = "C:\\grimjedi\\Libs\\Std\\General\\Stdmemory.c";
static unsigned char grim_anchor_004e7994[0] __attribute__((section(".data$grim_004e7994"), aligned(16), used));
static unsigned char grim_pad_004e7994[4] __attribute__((section(".data$grim_004e7994_"), aligned(4), used));
/* 0x004e7994, 24 bytes */ GRIM_DATA("004e7994z") char grim_def_s_allocation_004e7994[24] __asm__("_s_allocation_004e7994") = "allocation\000\000\000\000\000\000\000\000\000\000HFED";
/* 0x00825e78, 4 bytes */ GRIM_DATA("00825e78") unsigned int grim_def_UINT_00825e78 __asm__("_UINT_00825e78") = 0x0;
/* 0x00825e80, 4 bytes */ GRIM_DATA("00825e80") unsigned int grim_def_UINT_00825e80 __asm__("_UINT_00825e80") = 0x0;
/* 0x00825e84, 12 bytes */ GRIM_DATA("00825e84") unsigned char grim_def_UINT_00825e84[12] __asm__("_UINT_00825e84") = {0};
