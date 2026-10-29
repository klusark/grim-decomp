/* GRIMFANDANGO.EXE :: resref.c
 * functions 0x00482070 .. 0x00482380 (5 functions)
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

/* ---- 0x00482260  FUN_00482260 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 FUN_00482260(code *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  code *pcVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  char *pcVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  pcVar2 = param_1;
  for (piVar5 = PTR_008a85d4; param_1 = pcVar2, piVar5 != (int *)0x0; piVar5 = (int *)*piVar5) {
    if (((piVar5[9] != 0) && (iVar3 = String_ContainsSubstring(piVar5[2],&DAT_004e7b14), iVar3 == 0)
        ) || ((*(byte *)(piVar5 + 7) & 8) != 0)) {
      local_4 = local_4 + 1;
    }
    pcVar2 = param_1;
  }
  iVar3 = (*pcVar2)(&local_4,4);
  if (iVar3 != 0) {
    return 1;
  }
  local_4 = 0;
  piVar5 = PTR_008a85d4;
  if (PTR_008a85d4 == (int *)0x0) {
    return 0;
  }
  do {
    if (((piVar5[9] != 0) && (iVar3 = String_ContainsSubstring(piVar5[2],&DAT_004e7b14), iVar3 == 0)
        ) || ((*(byte *)(piVar5 + 7) & 8) != 0)) {
      uVar4 = 0xffffffff;
      pcVar6 = (char *)piVar5[2];
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      param_1 = (code *)(~uVar4 - 1);
      iVar3 = (*pcVar2)(&param_1,4);
      if (((iVar3 != 0) || (iVar3 = (*pcVar2)(piVar5[2],param_1), iVar3 != 0)) ||
         (iVar3 = (*pcVar2)(piVar5 + 4,4), iVar3 != 0)) {
        return 1;
      }
      piVar5[6] = piVar5[5];
      iVar3 = (*pcVar2)(piVar5 + 6,4);
      if (iVar3 != 0) {
        return 1;
      }
      local_4 = local_4 + 1;
    }
    piVar5 = (int *)*piVar5;
    if (piVar5 == (int *)0x0) {
      return 0;
    }
  } while( true );
}
#undef local_4

#endif


/* ---- 0x00482380  FUN_00482380 ---- */
undefined4 FUN_00482380(code *param_1)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *pvVar3;
  #define iStack_110 (*(int *)(_frame + (0x120 - 0x110)))
  #define local_10c (*(int *)(_frame + (0x120 - 0x10c)))
  #define iStack_108 (*(int *)(_frame + (0x120 - 0x108)))
  #define iStack_104 (*(int *)(_frame + (0x120 - 0x104)))
  #define acStack_100 (*(char (*)[256])(_frame + (0x120 - 0x100)))
  
  iVar1 = (*param_1)(&local_10c,4);
  if (iVar1 != 0) {
    return 1;
  }
  iVar1 = 0;
  if (local_10c < 1) {
    return 0;
  }
  while( true ) {
    iVar2 = (*param_1)(&iStack_110,4);
    if ((iVar2 != 0) || (0xff < iStack_110)) {
      return 1;
    }
    iVar2 = (*param_1)(acStack_100,iStack_110);
    if (iVar2 != 0) {
      return 1;
    }
    acStack_100[iStack_110] = '\0';
    iVar2 = (*param_1)(&iStack_108,4);
    if (iVar2 != 0) break;
    pvVar3 = Res_LoadInternal(iStack_108,acStack_100,&iStack_104);
    if (iStack_104 == 0) {
      return 1;
    }
    iVar2 = (*param_1)((int)pvVar3 + 0x18,4);
    if (iVar2 != 0) {
      return 1;
    }
    iVar1 = iVar1 + 1;
    if (local_10c <= iVar1) {
      return 0;
    }
  }
  return 1;
}
#undef acStack_100
#undef iStack_104
#undef iStack_108
#undef iStack_110
#undef local_10c

