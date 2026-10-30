/* IMUSE.DLL :: imuse_stream.c
 * functions 0x1000a210 .. 0x1000b8d0 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000a210  iMUSE_stream__a210 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/IMUSE.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

uint * __cdecl iMUSE_stream__a210(uint param_1,uint param_2,uint param_3)

{
  uint *puVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  
  puVar1 = (uint *)iMUSE_dsound__4640(param_2);
  if ((puVar1 != (uint *)0x0) && (param_3 < (uint)((int)puVar1[1] >> 2))) {
    piVar2 = &DAT_10031e98;
    iVar4 = 0;
    while ((*piVar2 == 0 || (piVar2[3] != param_2))) {
      piVar2 = piVar2 + 0xc;
      iVar4 = iVar4 + 1;
      if (2 < iVar4) {
        puVar5 = &DAT_10031e98;
        iVar4 = 0;
        do {
          if (*puVar5 == 0) {
            *puVar5 = param_1;
            puVar5[1] = 0;
            uVar3 = iMUSE_dsound__45c0(param_1,0,2);
            puVar5[2] = uVar3;
            puVar5[3] = param_2;
            puVar5[4] = *puVar1;
            puVar5[5] = (puVar1[1] - param_3) - 4;
            puVar5[6] = puVar1[2];
            uVar3 = puVar1[3];
            puVar5[8] = param_3;
            puVar5[7] = uVar3;
            puVar5[9] = 0;
            puVar5[10] = 0;
            puVar5[0xb] = 0;
            return puVar5;
          }
          puVar5 = puVar5 + 0xc;
          iVar4 = iVar4 + 1;
        } while (iVar4 < 3);
        return (uint *)0x0;
      }
    }
  }
  return (uint *)0x0;
}
#endif


/* ---- 0x1000a2d0  iMUSE_stream__a2d0 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/IMUSE.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl iMUSE_stream__a2d0(undefined4 *param_1)

{
  *param_1 = 0;
  if (DAT_10031e90 == param_1) {
    DAT_10031e90 = (undefined4 *)0x0;
  }
  return 0;
}
#endif


/* ---- 0x1000a420  iMUSE_stream__a420 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/IMUSE.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

int __cdecl iMUSE_stream__a420(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  uVar1 = Im_FindTrack(param_1);
  if ((uVar1 < param_2) || (*(uint *)(param_1 + 0x20) < param_2)) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(param_1 + 0x14);
    if ((uint)(iVar2 - *(int *)(param_1 + 0x28)) < param_2) {
      uVar3 = (param_2 - iVar2) + *(int *)(param_1 + 0x28);
      puVar4 = *(undefined4 **)(param_1 + 0x10);
      puVar5 = (undefined4 *)((int)*(undefined4 **)(param_1 + 0x10) + iVar2);
      for (uVar1 = uVar3 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
    }
    iVar2 = *(int *)(param_1 + 0x10) + *(int *)(param_1 + 0x28);
    uVar1 = *(int *)(param_1 + 0x28) + param_2;
    *(uint *)(param_1 + 0x28) = uVar1;
    if (*(uint *)(param_1 + 0x14) <= uVar1) {
      *(uint *)(param_1 + 0x28) = uVar1 - *(uint *)(param_1 + 0x14);
      return iVar2;
    }
  }
  return iVar2;
}
#endif


/* ---- 0x1000a490  iMUSE_stream__a490 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/IMUSE.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

int __cdecl iMUSE_stream__a490(int param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  uVar2 = Im_FindTrack(param_1);
  if ((param_3 + param_2 <= uVar2) && (param_3 <= *(uint *)(param_1 + 0x20))) {
    iVar1 = *(int *)(param_1 + 0x14);
    iVar4 = *(int *)(param_1 + 0x28) + param_2;
    if (iVar1 <= iVar4) {
      iVar4 = iVar4 - iVar1;
    }
    if ((uint)(iVar1 - iVar4) < param_3) {
      uVar3 = (param_3 + iVar4) - iVar1;
      puVar5 = *(undefined4 **)(param_1 + 0x10);
      puVar6 = (undefined4 *)((int)*(undefined4 **)(param_1 + 0x10) + iVar1);
      for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
        puVar6 = (undefined4 *)((int)puVar6 + 1);
      }
    }
    return *(int *)(param_1 + 0x10) + iVar4;
  }
  return 0;
}
#endif


/* ---- 0x1000a500  iMUSE_stream__a500 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/IMUSE.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl iMUSE_stream__a500(int param_1,uint param_2)

{
  uint uVar1;
  
  DAT_10031e94 = 1;
  uVar1 = Im_FindTrack(param_1);
  if (uVar1 < param_2) {
    return 0xffffffff;
  }
  uVar1 = *(int *)(param_1 + 0x28) + param_2;
  *(uint *)(param_1 + 0x28) = uVar1;
  if (*(uint *)(param_1 + 0x14) <= uVar1) {
    *(uint *)(param_1 + 0x28) = uVar1 - *(uint *)(param_1 + 0x14);
  }
  return 0;
}
#endif


/* ---- 0x1000a540  iMUSE_stream__a540 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/IMUSE.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl iMUSE_stream__a540(int param_1,uint param_2)

{
  uint uVar1;
  
  DAT_10031e94 = 1;
  uVar1 = Im_FindTrack(param_1);
  if (uVar1 < param_2) {
    return 0xffffffff;
  }
  uVar1 = *(int *)(param_1 + 0x28) + param_2;
  *(uint *)(param_1 + 0x24) = uVar1;
  if (*(uint *)(param_1 + 0x14) <= uVar1) {
    *(uint *)(param_1 + 0x24) = uVar1 - *(uint *)(param_1 + 0x14);
  }
  return 0;
}
#endif


/* ---- 0x1000a5a0  iMUSE_stream__a5a0 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/IMUSE.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl iMUSE_stream__a5a0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  DAT_10031e94 = 1;
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = 0;
  param_1[0xb] = 0;
  if (DAT_10031e90 == param_1) {
    DAT_10031e90 = (undefined4 *)0x0;
  }
  return 0;
}
#endif


/* ---- 0x1000b760  iMUSE_stream__b760 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/IMUSE.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl iMUSE_stream__b760(int *param_1,int *param_2)

{
  if (((param_2 != (int *)0x0) && (*param_2 == 0)) && (param_2[1] == 0)) {
    param_2[1] = *param_1;
    if ((undefined4 *)*param_1 != (undefined4 *)0x0) {
      *(undefined4 *)*param_1 = param_2;
    }
    *param_2 = 0;
    *param_1 = (int)param_2;
    return 0;
  }
  return 0xfffffffb;
}
#endif


/* ---- 0x1000b7a0  iMUSE_stream__b7a0 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/IMUSE.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl iMUSE_stream__b7a0(int *param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = (int *)*param_1;
  if ((param_2 == (int *)0x0) || (piVar1 == (int *)0x0)) {
    return 0xfffffffb;
  }
  do {
    if (piVar1 == param_2) break;
    piVar1 = (int *)piVar1[1];
  } while (piVar1 != (int *)0x0);
  if (piVar1 == (int *)0x0) {
    return 0xfffffffd;
  }
  if ((int *)param_2[1] != (int *)0x0) {
    *(int *)param_2[1] = *param_2;
  }
  if (*param_2 != 0) {
    *(int *)(*param_2 + 4) = param_2[1];
    param_2[1] = 0;
    *param_2 = 0;
    return 0;
  }
  *param_1 = param_2[1];
  param_2[1] = 0;
  *param_2 = 0;
  return 0;
}
#endif


/* ---- 0x1000b810  iMUSE_stream__b810 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/IMUSE.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl iMUSE_stream__b810(undefined1 *param_1)

{
  return CONCAT31(CONCAT21(CONCAT11(*param_1,param_1[1]),param_1[2]),param_1[3]);
}
#endif


/* ---- 0x1000b840  iMUSE_stream__b840 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/IMUSE.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of stream tracks (Im_RefillStreamTrack and friends) - module name inferred
    */

undefined4 __cdecl iMUSE_stream__b840(int *param_1,int param_2)

{
  if (param_2 == 0) {
    if (*param_1 != 0x80) {
      return 0;
    }
    *param_1 = 0;
  }
  else if (param_2 == *param_1) {
    *param_1 = 0;
    return 0;
  }
  return 0xffffffff;
}
#endif


/* ---- 0x1000b8d0  FUN_1000b8d0 ---- */
/* NOT COMPILED: names/lib_replace.json (host): the system C runtime / zlib (or nothing, for dead code) is used instead; this C text is only for reading */
#if 0
int __cdecl FUN_1000b8d0(undefined1 *param_1,char *param_2,undefined4 *param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_20 (*(undefined1 **)(_frame + (0x30 - 0x20)))
  #define local_1c (*(int *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(undefined1 **)(_frame + (0x30 - 0x18)))
  #define local_14 (*(undefined4 *)(_frame + (0x30 - 0x14)))
  
  local_18 = param_1;
  local_20 = param_1;
  local_14 = 0x42;
  local_1c = 0x7fffffff;
  iVar1 = FUN_1000c670(&local_20,param_2,param_3);
  local_1c = local_1c + -1;
  if (-1 < local_1c) {
    *local_20 = 0;
    return iVar1;
  }
  _flsbuf(0,(int *)&local_20);
  return iVar1;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20

#endif

