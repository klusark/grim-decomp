/* GRIMFANDANGO.EXE :: resref.c
 * functions 0x00482070 .. 0x00482220 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00482070  Res_SetReference ---- */
/* Registers a 0x34-byte reference {valid, data, tag[0x20], line, prev, next} on the resource so it
   cannot be freed Original name Res_SetReference (the remaster's GrimFandango (Linux): the only
   unmatched callee of Lua_LockSet; 10 matched neighbours agree, 0 disagree); was ResRef_Add. */

void __cdecl Res_SetReference(void *ref,void *data,char *file,int line)

{
  void *res;
  int iVar1;
  
  res = Res_FindByData(data);
  if ((ref == (void *)0x0) || (*(int *)ref != 0)) {
    (**(code **)(g_dwResHS + 0x18))
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

/* ---- 0x00482110  Res_RemoveReference ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name Res_RemoveReference (the remaster's GrimFandango (Linux): the only unmatched callee
   of KeyframeComponent_TrackCallback; the only unmatched callee of Lua_UnLockSet; 5 matched
   neighbours agree, 0 disagree); was ResRef_Remove. */

void Res_RemoveReference(void *ref)

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

/* ---- 0x00482220  Res_ResolveToSerialNumber ---- */
/* Res.c: clears a ResRef (0x34 bytes) after its record is found Original name
   Res_ResolveToSerialNumber (the remaster's GrimFandango (Linux): aligned call in
   sputActor_Restore); was ResRef_Release. */

void Res_ResolveToSerialNumber(undefined4 *param_1)

{
  void *pvVar1;
  
  pvVar1 = Res_FindByHandle((void *)param_1[1]);
  if (pvVar1 != (void *)0x0) {
    *param_1 = 0;
    param_1[0xc] = 0;
    param_1[0xb] = 0;
    Res_SetReference(param_1,*(void **)((int)pvVar1 + 0x14),
                     s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xeec);
  }
  return;
}
