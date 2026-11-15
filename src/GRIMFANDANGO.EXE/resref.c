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

void __cdecl Res_SetReference(ResRef *ref,void *data,char *file,int line)

{
  Resource *res;
  uint *puVar1;
  
  res = Res_FindByData(data);
  if ((ref == (ResRef *)0x0) || (ref->nValid != 0)) {
    (**(code **)(g_dwResHS + 0x18))
              (s_ref_____ref__valid_004e7b00,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xe4c);
  }
  if (res != (Resource *)0x0) {
    ref->nValid = 1;
    ref->pData = data;
    ref->pPrev = (ResRef *)0x0;
    ref->pNext = res->pRefs;
    puVar1 = (uint *)strrchr(file,'\\');
    if (puVar1 != (uint *)0x0) {
      strncpy((uint *)ref->aTag,puVar1,0x20);
    }
    ref->nLine = line;
    if (ref->pNext != (ResRef *)0x0) {
      ref->pNext->pPrev = ref;
    }
    res->pRefs = ref;
    Res_MoveToFront(res);
    return;
  }
  ref->nValid = 0;
  return;
}

/* ---- 0x00482110  Res_RemoveReference ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name Res_RemoveReference (the remaster's GrimFandango (Linux): the only unmatched callee
   of KeyframeComponent_TrackCallback; the only unmatched callee of Lua_UnLockSet; 5 matched
   neighbours agree, 0 disagree); was ResRef_Remove. */

void Res_RemoveReference(ResRef *ref)

{
  Resource *pRVar1;
  
  if (ref->nValid != 0) {
    pRVar1 = Res_FindByData(ref->pData);
    if (pRVar1 != (Resource *)0x0) {
      if (pRVar1->pRefs == ref) {
        pRVar1->pRefs = ref->pNext;
      }
      if (ref->pPrev != (ResRef *)0x0) {
        ref->pPrev->pNext = ref->pNext;
      }
      if (ref->pNext != (ResRef *)0x0) {
        ref->pNext->pPrev = ref->pPrev;
      }
      ref->nValid = 0;
      ref->pNext = (ResRef *)0x0;
      ref->pPrev = (ResRef *)0x0;
    }
  }
  return;
}

/* ---- 0x00482220  Res_ResolveToSerialNumber ---- */
/* Res.c: clears a ResRef (0x34 bytes) after its record is found Original name
   Res_ResolveToSerialNumber (the remaster's GrimFandango (Linux): aligned call in
   sputActor_Restore); was ResRef_Release. */

void __cdecl Res_ResolveToSerialNumber(ResRef *ref)

{
  Resource *pRVar1;
  
  pRVar1 = Res_FindByHandle(ref->pData);
  if (pRVar1 != (Resource *)0x0) {
    ref->nValid = 0;
    ref->pNext = (ResRef *)0x0;
    ref->pPrev = (ResRef *)0x0;
    Res_SetReference(ref,pRVar1->pData,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xeec);
  }
  return;
}
