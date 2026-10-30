/* GRIMFANDANGO.EXE :: resref.c
 * functions 0x00482070 .. 0x00482220 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00482070  ResRef_Add ---- */
/* Registers a 0x34-byte reference {valid, data, tag[0x20], line, prev, next} on the resource so it
   cannot be freed */

void __cdecl ResRef_Add(void *ref,void *data,char *file,int line)

{
  void *res;
  int iVar1;
  
  res = Res_FindByData(data);
  if ((ref == (void *)0x0) || (*(int *)ref != 0)) {
    (**(code **)(UINT_008a856c + 0x18))
              (s_ref_____ref__valid_004e7b00,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xe4c);
  }
  if (res != (void *)0x0) {
    *(undefined4 *)ref = 1;
    *(void **)((int)ref + 4) = data;
    *(undefined4 *)((int)ref + 0x2c) = 0;
    *(undefined4 *)((int)ref + 0x30) = *(undefined4 *)((int)res + 0x24);
    iVar1 = strrchr(file,0x5c);
    if (iVar1 != 0) {
      strncpy((int)ref + 8,iVar1,0x20);
    }
    *(int *)((int)ref + 0x28) = line;
    if (*(int *)((int)ref + 0x30) != 0) {
      *(void **)(*(int *)((int)ref + 0x30) + 0x2c) = ref;
    }
    *(void **)((int)res + 0x24) = ref;
    Res_MoveToFront(res);
    return;
  }
  *(undefined4 *)ref = 0;
  return;
}

/* ---- 0x00482110  ResRef_Remove ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ResRef_Remove(void *ref)

{
  void *pvVar1;
  
  if (*(int *)ref != 0) {
    pvVar1 = Res_FindByData(*(void **)((int)ref + 4));
    if (pvVar1 != (void *)0x0) {
      if (*(void **)((int)pvVar1 + 0x24) == ref) {
        *(undefined4 *)((int)pvVar1 + 0x24) = *(undefined4 *)((int)ref + 0x30);
      }
      if (*(int *)((int)ref + 0x2c) != 0) {
        *(undefined4 *)(*(int *)((int)ref + 0x2c) + 0x30) = *(undefined4 *)((int)ref + 0x30);
      }
      if (*(int *)((int)ref + 0x30) != 0) {
        *(undefined4 *)(*(int *)((int)ref + 0x30) + 0x2c) = *(undefined4 *)((int)ref + 0x2c);
      }
      *(undefined4 *)ref = 0;
      *(undefined4 *)((int)ref + 0x30) = 0;
      *(undefined4 *)((int)ref + 0x2c) = 0;
    }
  }
  return;
}

/* ---- 0x00482220  ResRef_Release ---- */
/* Res.c: clears a ResRef (0x34 bytes) after its record is found */

void ResRef_Release(undefined4 *param_1)

{
  void *pvVar1;
  
  pvVar1 = Res_FindByHandle((void *)param_1[1]);
  if (pvVar1 != (void *)0x0) {
    *param_1 = 0;
    param_1[0xc] = 0;
    param_1[0xb] = 0;
    ResRef_Add(param_1,*(void **)((int)pvVar1 + 0x14),s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,
               0xeec);
  }
  return;
}
