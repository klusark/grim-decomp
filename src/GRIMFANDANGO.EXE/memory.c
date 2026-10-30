/* GRIMFANDANGO.EXE :: memory.c
 * functions 0x0045ff00 .. 0x00488c00 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0045ff00  Mem_DumpLog ---- */
/* Lua DumpMemoryLog */

void Mem_DumpLog(void)

{
  return;
}

/* ---- 0x00478170  Mem_Copy ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void __cdecl Mem_Copy(void *dst,void *src,uint n)

{
  uint uVar1;
  
  if (0 < (int)n) {
    if (((uint)dst & 1) != 0) {
      *(undefined1 *)dst = *(undefined1 *)src;
      n = n - 1;
      src = (void *)((int)src + 1);
      dst = (void *)((int)dst + 1);
    }
    if (1 < (int)n) {
      if (((uint)dst & 3) != 0) {
        *(undefined2 *)dst = *(undefined2 *)src;
        src = (void *)((int)src + 2);
        dst = (void *)((int)dst + 2);
        n = n - 2;
      }
      if (3 < (int)n) {
        if (((uint)dst & 7) != 0) {
          *(undefined4 *)dst = *(undefined4 *)src;
          dst = (void *)((int)dst + 4);
          src = (void *)((int)src + 4);
          n = n - 4;
        }
        if (7 < (int)n) {
          uVar1 = (int)dst + n;
          n = n & 7;
          for (; dst != (undefined8 *)(uVar1 & 0xfffffff8); dst = (void *)((int)dst + 8)) {
            *(undefined8 *)dst = *(undefined8 *)src;
            src = (void *)((int)src + 8);
          }
        }
        if (3 < (int)n) {
          *(undefined4 *)dst = *(undefined4 *)src;
          dst = (void *)((int)dst + 4);
          src = (void *)((int)src + 4);
          n = n - 4;
        }
      }
      if (1 < (int)n) {
        *(undefined2 *)dst = *(undefined2 *)src;
        src = (void *)((int)src + 2);
        dst = (void *)((int)dst + 2);
        n = n - 2;
      }
    }
    if (0 < (int)n) {
      *(undefined1 *)dst = *(undefined1 *)src;
    }
  }
  return;
}
#endif


/* ---- 0x0047fe00  Mem_CheckAlloc ---- */
/* Asserts that an allocation succeeded */

void __cdecl Mem_CheckAlloc(void *p,char *file,int line)

{
  if (*(int *)((int)p + -4) == 0x12345678) {
    *(char **)((int)p + -0x14) = file;
    *(int *)((int)p + -0x10) = line;
  }
  return;
}

/* ---- 0x004888d0  Memory_SysInitialize ---- */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

undefined4 Memory_SysInitialize(GrimServices *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  g_pSvcMemory = param_1;
  uVar1 = 1;
  if (UINT_008c9a74 == 0) {
    UINT_008c9a74 = 1;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = Memory_SysInitialize;
      param_2[1] = Memory_Sys_Terminate;
      param_2[2] = Memory_Sys_Start;
      param_2[3] = Memory_Sys_Stop;
      param_2[4] = 0;
      param_2[5] = 0;
      param_2[6] = 0;
      param_2[7] = 0;
    }
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00488930  Memory_Sys_Terminate ---- */
/* Module interface slot 1 (Memory_Sys): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. */

void Memory_Sys_Terminate(void)

{
  UINT_008c9a74 = 0;
  return;
}

/* ---- 0x00488940  Memory_Sys_Start ---- */
/* Module interface slot 2 (Memory_Sys): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind).  */

undefined4 Memory_Sys_Start(void)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if ((UINT_008c9a74 != 0) && (UINT_008c9a78 == 0)) {
    UINT_008c9a78 = 1;
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00488970  Memory_Sys_Stop ---- */
/* Module interface slot 3 (Memory_Sys): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. */

void Memory_Sys_Stop(void)

{
  UINT_008c9a78 = 0;
  return;
}

/* ---- 0x00488980  Pool_Create ---- */
/* Temp/Memory.c: fixed-size item pool. Items are 8-byte-headed (next, pool) blocks carved from
   grown chunks; pools are kept in the g_poolList singly linked list. */

void ** Pool_Create(int param_1,void *param_2,void *param_3)

{
  void **ppvVar1;
  int iVar2;
  void **ppvVar3;
  
  if (param_1 == 0) {
    (*g_pSvcMemory->pAssertFail)
              (s_itemSize___0_004e82cc,s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264,0x349);
  }
  if (param_3 == (void *)0x0) {
    (*g_pSvcMemory->pAssertFail)
              (s_itemGrowBy___0_004e82bc,s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264,0x34b);
  }
  ppvVar1 = (void **)(*g_pSvcMemory->pAlloc)(0x24,s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264,0x34f)
  ;
  if (ppvVar1 == (void **)0x0) {
    (*g_pSvcMemory->pAssertFail)(s_pPool_004e82b4,s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264,0x350)
    ;
  }
  ppvVar3 = ppvVar1;
  for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
    *ppvVar3 = (void *)0x0;
    ppvVar3 = ppvVar3 + 1;
  }
  ppvVar1[1] = g_poolList;
  g_poolList = ppvVar1;
  *ppvVar1 = ppvVar1;
  ppvVar1[2] = (void *)(param_1 + 7U & 0xfffffff8);
  ppvVar1[3] = (void *)0x0;
  ppvVar1[5] = (void *)0x0;
  ppvVar1[6] = param_3;
  ppvVar1[7] = (void *)0x0;
  if (param_2 != (void *)0x0) {
    Pool_Grow(ppvVar1,param_2);
  }
  if (ppvVar1[5] != param_2) {
    (*g_pSvcMemory->pAssertFail)
              (s_pPool__poolItems____itemCount_004e8294,s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264,
               0x362);
  }
  return ppvVar1;
}

/* ---- 0x00488a70  Pool_Destroy ---- */
/* Source: Temp/Memory.c (lines 896-897, from __FILE__/__LINE__ passed to the allocator) */

void Pool_Destroy(void **param_1)

{
  undefined4 *puVar1;
  void **ppvVar2;
  void **ppvVar3;
  undefined4 *puVar4;
  
  if (param_1 == (void **)0x0) {
    (*g_pSvcMemory->pAssertFail)(&DAT_004e82f4,s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264,0x380);
  }
  if (*param_1 != param_1) {
    (*g_pSvcMemory->pAssertFail)
              (s_pPool__pPool____pPool_004e82dc,s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264,0x381);
  }
  ppvVar2 = (void **)0x0;
  for (ppvVar3 = g_poolList; (ppvVar3 != (void **)0x0 && (ppvVar3 != param_1)); ppvVar3 = ppvVar3[1]
      ) {
    ppvVar2 = ppvVar3;
  }
  if (ppvVar2 == (void **)0x0) {
    g_poolList = param_1[1];
  }
  else {
    ppvVar2[1] = param_1[1];
  }
  puVar4 = param_1[8];
  while (puVar4 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar4;
    (*g_pSvcMemory->pFree)(puVar4);
    puVar4 = puVar1;
  }
  (*g_pSvcMemory->pFree)(param_1);
  return;
}

/* ---- 0x00488b10  Pool_Alloc ---- */
/* Pops an item off the free list, growing the pool by growBy when empty. Returns the payload (item
   header + 8). */

int * Pool_Alloc(int *param_1)

{
  int *piVar1;
  uint uVar2;
  
  if (param_1 == (int *)0x0) {
    (*g_pSvcMemory->pAssertFail)(&DAT_004e82f4,s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264,0x42a);
  }
  if ((int *)*param_1 != param_1) {
    (*g_pSvcMemory->pAssertFail)
              (s_pPool__pPool____pPool_004e82dc,s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264,0x42b);
  }
  if (param_1[3] == param_1[5]) {
    Pool_Grow(param_1,param_1[6]);
  }
  piVar1 = (int *)param_1[7];
  if (piVar1 != (int *)0x0) {
    param_1[7] = *piVar1;
    *piVar1 = 0;
    uVar2 = param_1[3] + 1;
    param_1[3] = uVar2;
    if (uVar2 < (uint)param_1[4]) {
      uVar2 = param_1[4];
    }
    param_1[4] = uVar2;
    if (piVar1 != (int *)0x0) {
      return piVar1 + 2;
    }
  }
  return (int *)0x0;
}

/* ---- 0x00488ba0  Pool_Free ---- */
/* Pushes the item back onto its pool's free list (pool pointer lives at item-4). */

void __cdecl Pool_Free(void *item)

{
  int *piVar1;
  
  if (item == (void *)0x0) {
    (*g_pSvcMemory->pAssertFail)(s_pData_004e828c,s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264,0x45c)
    ;
  }
  piVar1 = *(int **)((int)item + -4);
  if ((int *)*piVar1 != piVar1) {
    (*g_pSvcMemory->pAssertFail)
              (s_pPool__pPool____pPool_004e82dc,s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264,0x462);
  }
  *(int *)((int)item + -8) = piVar1[7];
  piVar1[7] = (int)item + -8;
  piVar1[3] = piVar1[3] + -1;
  return;
}

/* ---- 0x00488c00  Pool_Grow ---- */
/* Allocates one chunk of `count` items and threads them onto the free list. */

void Pool_Grow(int param_1,int param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar2 = (undefined4 *)
           (*g_pSvcMemory->pAlloc)
                     ((*(int *)(param_1 + 8) + 8) * param_2 + 8,
                      s_C__grimsrc_libs_grimlib_Temp_Mem_004e8264,0x906);
  if (puVar2 != (undefined4 *)0x0) {
    *puVar2 = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 **)(param_1 + 0x20) = puVar2;
    puVar2[1] = param_1;
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + param_2;
    piVar1 = puVar2 + 2;
    while (param_2 != 0) {
      param_2 = param_2 + -1;
      if (param_2 == 0) {
        iVar3 = *(int *)(param_1 + 0x1c);
      }
      else {
        iVar3 = (int)piVar1 + *(int *)(param_1 + 8) + 8;
      }
      *piVar1 = iVar3;
      piVar1[1] = param_1;
      piVar1 = (int *)*piVar1;
    }
    *(undefined4 **)(param_1 + 0x1c) = puVar2 + 2;
  }
  return;
}
