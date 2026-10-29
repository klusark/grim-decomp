/* LUA.DLL :: lundump.c
 * functions 0x1000cea0 .. 0x1000d620 (22 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000cea0  luaU_undump1 ---- */
undefined4 __cdecl luaU_undump1(int *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  #define local_c (*(int **)(_frame + (0x20 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
                    /* 0xcea0  3  luaU_undump1 */
  iVar1 = *param_1;
  *param_1 = iVar1 + -1;
  if (iVar1 + -1 < 0) {
    uVar2 = (*(code *)param_1[2])(param_1);
  }
  else {
    uVar2 = (uint)*(byte *)param_1[1];
    param_1[1] = (int)((byte *)param_1[1] + 1);
  }
  local_c = param_1;
  local_8 = 0;
  local_4 = 1;
  if (uVar2 == 0x1b) {
    uVar3 = luaU_LoadChunk((int *)&local_c);
    return uVar3;
  }
  if (uVar2 != 0xffffffff) {
    luaL_verror(s__s_is_not_a_lua_binary_file_10027fcc,param_1[4]);
  }
  return 0;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x1000cf10  luaU_LoadChunk ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

undefined4 * __cdecl luaU_LoadChunk(int *param_1)

{
  undefined4 *puVar1;
  
  luaU_loadheader(param_1);
  puVar1 = luaU_LoadFunction(param_1);
  return puVar1;
}

/* ---- 0x1000cf30  luaU_LoadFunction ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

undefined4 * __cdecl luaU_LoadFunction(int *param_1)

{
  uint *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  uint *puVar6;
  
  puVar1 = (uint *)*param_1;
  puVar2 = luaF_newclosure();
  uVar3 = lundump__cfa0((int *)puVar1);
  puVar2[5] = uVar3;
  uVar4 = luaU_LoadString(puVar1);
  puVar2[6] = uVar4;
  puVar6 = puVar1;
  uVar3 = luaU_LoadCode((int *)puVar1);
  puVar5 = lundump__d030(uVar3,puVar6);
  puVar2[4] = puVar5;
  luaU_LoadConstants((int)puVar2,param_1);
  luaU_LoadLocals((int)puVar2,puVar1);
  lundump__d3c0((int)puVar2,param_1);
  return puVar2;
}

/* ---- 0x1000cfa0  lundump__cfa0 ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

uint __cdecl lundump__cfa0(int *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = lundump__cfd0(param_1);
  uVar2 = lundump__cfd0(param_1);
  return uVar1 << 8 | uVar2;
}

/* ---- 0x1000cfd0  lundump__cfd0 ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

uint __cdecl lundump__cfd0(int *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *param_1;
  *param_1 = iVar1 + -1;
  if (iVar1 + -1 < 0) {
    uVar2 = (*(code *)param_1[2])(param_1);
  }
  else {
    uVar2 = (uint)*(byte *)param_1[1];
    param_1[1] = (int)((byte *)param_1[1] + 1);
  }
  if (uVar2 == 0xffffffff) {
    luaU_unexpectedEOZ();
  }
  return uVar2;
}

/* ---- 0x1000d010  luaU_unexpectedEOZ ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

void luaU_unexpectedEOZ(void)

{
  int in_stack_00000004;
  
  ((code *)luaL_verror)(s_unexpected_end_of_binary_file__s_10027fe8,*(undefined4 *)(in_stack_00000004 + 0x10))
  ;
  return;
}

/* ---- 0x1000d030  lundump__d030 ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

undefined4 * __cdecl lundump__d030(uint param_1,uint *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)
           (**(code **)(DAT_1002beb8 + 0x20))
                     (param_1,s_C__grimsrc_libs_lua_src_lundump__1002800c,0x31);
  luaU_LoadBlock(param_2,puVar1,param_1);
  return puVar1;
}

/* ---- 0x1000d060  luaU_LoadBlock ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

uint __cdecl luaU_LoadBlock(uint *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = luaZ_read(param_1,param_2,param_3);
  if (uVar1 != 0) {
    luaU_unexpectedEOZ();
  }
  return uVar1;
}

/* ---- 0x1000d090  luaU_LoadCode ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

uint __cdecl luaU_LoadCode(int *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = lundump__cfa0(param_1);
  uVar2 = lundump__cfa0(param_1);
  uVar3 = uVar1 << 0x10 | uVar2;
  if ((uVar1 != 0) && (uVar3 == uVar2)) {
    luaL_verror(s_code_too_long___ld_bytes__10028030,uVar3);
  }
  return uVar3;
}

/* ---- 0x1000d0d0  luaU_LoadString ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

undefined4 __cdecl luaU_LoadString(uint *param_1)

{
  uint *puVar1;
  undefined4 uVar2;
  
  puVar1 = lundump__d0f0(param_1);
  if (puVar1 == (uint *)0x0) {
    return 0;
  }
  uVar2 = luaS_new((byte *)puVar1);
  return uVar2;
}

/* ---- 0x1000d0f0  lundump__d0f0 ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

uint * __cdecl lundump__d0f0(uint *param_1)

{
  uint uVar1;
  uint *puVar2;
  
  uVar1 = lundump__cfa0((int *)param_1);
  if (uVar1 == 0) {
    return (uint *)0x0;
  }
  puVar2 = (uint *)luaL_openspace(uVar1);
  luaU_LoadBlock(param_1,puVar2,uVar1);
  lundump__d130(puVar2,uVar1);
  return puVar2;
}

/* ---- 0x1000d130  lundump__d130 ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

void __cdecl lundump__d130(uint *param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 != 0) {
    uVar1 = (uint)param_1 & 3;
    if ((int)param_2 < (int)((uint)param_1 & 3)) {
      uVar1 = param_2;
    }
    iVar3 = param_2 - uVar1;
    for (; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(byte *)param_1 = ~(byte)*param_1;
      param_1 = (uint *)((int)param_1 + 1);
    }
    iVar2 = (int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2;
    iVar3 = iVar3 + iVar2 * -4;
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      *param_1 = ~*param_1;
      param_1 = param_1 + 1;
    }
    for (; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(byte *)param_1 = ~(byte)*param_1;
      param_1 = (uint *)((int)param_1 + 1);
    }
  }
  return;
}

/* ---- 0x1000d1a0  luaU_LoadLocals ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

void __cdecl luaU_LoadLocals(int param_1,uint *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  uVar1 = lundump__cfa0((int *)param_2);
  if (uVar1 != 0) {
    uVar2 = (**(code **)(DAT_1002beb8 + 0x20))
                      (uVar1 * 8 + 8,s_C__grimsrc_libs_lua_src_lundump__1002800c,0xa4);
    iVar4 = 0;
    *(undefined4 *)(param_1 + 0x1c) = uVar2;
    if (0 < (int)uVar1) {
      do {
        uVar3 = lundump__cfa0((int *)param_2);
        *(uint *)(*(int *)(param_1 + 0x1c) + 4 + iVar4 * 8) = uVar3;
        uVar2 = luaU_LoadString(param_2);
        *(undefined4 *)(*(int *)(param_1 + 0x1c) + iVar4 * 8) = uVar2;
        iVar4 = iVar4 + 1;
      } while (iVar4 < (int)uVar1);
    }
    *(undefined4 *)(*(int *)(param_1 + 0x1c) + 4 + iVar4 * 8) = 0xffffffff;
    *(undefined4 *)(*(int *)(param_1 + 0x1c) + iVar4 * 8) = 0;
  }
  return;
}

/* ---- 0x1000d230  luaU_LoadConstants ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

void __cdecl luaU_LoadConstants(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  float fVar6;
  
  uVar2 = lundump__cfa0((int *)*param_2);
  *(uint *)(param_1 + 0xc) = uVar2;
  if (uVar2 != 0) {
    uVar3 = (**(code **)(DAT_1002beb8 + 0x20))
                      (uVar2 * 8,s_C__grimsrc_libs_lua_src_lundump__1002800c,0xb3);
    iVar5 = 0;
    *(undefined4 *)(param_1 + 8) = uVar3;
    if (0 < (int)uVar2) {
      do {
        puVar1 = (undefined4 *)(*(int *)(param_1 + 8) + iVar5 * 8);
        uVar4 = lundump__cfd0((int *)*param_2);
        if (uVar4 == 0x46) {
          *puVar1 = 0xfffffffc;
          puVar1[1] = 0;
        }
        else if (uVar4 == 0x4e) {
          *puVar1 = 0xffffffff;
          fVar6 = luaU_LoadNumber(param_2);
          puVar1[1] = fVar6;
        }
        else if (uVar4 == 0x53) {
          *puVar1 = 0xfffffffe;
          uVar3 = luaU_LoadString((uint *)*param_2);
          puVar1[1] = uVar3;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < (int)uVar2);
    }
  }
  return;
}

/* ---- 0x1000d2f0  luaU_LoadNumber ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

float __cdecl luaU_LoadNumber(undefined4 *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  #define local_8 (*(double *)(_frame + (0x20 - 0x8)))
  
  puVar1 = param_1;
  if (param_1[2] != 0) {
    luaU_LoadBlock((uint *)*param_1,&param_1,4);
    if (puVar1[1] != 0) {
      lundump__d360((undefined1 *)&param_1);
    }
    return PUN(float,param_1);
  }
  luaU_LoadBlock((uint *)*param_1,(undefined4 *)&local_8,8);
  if (puVar1[1] != 0) {
    lundump__d380((undefined1 *)&local_8);
  }
  return (float)local_8;
}
#undef local_8


/* ---- 0x1000d360  lundump__d360 ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

void __cdecl lundump__d360(undefined1 *param_1)

{
  undefined1 uVar1;
  
  uVar1 = *param_1;
  *param_1 = param_1[3];
  param_1[3] = uVar1;
  uVar1 = param_1[1];
  param_1[1] = param_1[2];
  param_1[2] = uVar1;
  return;
}

/* ---- 0x1000d380  lundump__d380 ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

void __cdecl lundump__d380(undefined1 *param_1)

{
  undefined1 uVar1;
  
  uVar1 = *param_1;
  *param_1 = param_1[7];
  param_1[7] = uVar1;
  uVar1 = param_1[1];
  param_1[1] = param_1[6];
  param_1[6] = uVar1;
  uVar1 = param_1[2];
  param_1[2] = param_1[5];
  param_1[5] = uVar1;
  uVar1 = param_1[3];
  param_1[3] = param_1[4];
  param_1[4] = uVar1;
  return;
}

/* ---- 0x1000d3c0  lundump__d3c0 ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

void __cdecl lundump__d3c0(int param_1,int *param_2)

{
  int *piVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  while( true ) {
    *(int *)*param_2 = *(int *)*param_2 + -1;
    piVar1 = (int *)*param_2;
    if (*piVar1 < 0) {
      uVar2 = (*(code *)piVar1[2])(piVar1);
    }
    else {
      uVar2 = (uint)*(byte *)piVar1[1];
      piVar1[1] = (int)((byte *)piVar1[1] + 1);
    }
    if (uVar2 != 0x23) break;
    uVar2 = lundump__cfa0((int *)*param_2);
    puVar3 = luaU_LoadFunction(param_2);
    *(undefined4 **)(*(int *)(param_1 + 8) + 4 + uVar2 * 8) = puVar3;
  }
  return;
}

/* ---- 0x1000d420  luaU_loadheader ---- */
/* lundump.c: binary file %s too new/old version */

void __cdecl luaU_loadheader(undefined4 *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  #define local_8 (*(double *)(_frame + (0x20 - 0x8)))
  
  puVar2 = param_1;
  puVar1 = (uint *)*param_1;
  luaU_LoadSignature((int *)puVar1);
  uVar3 = lundump__cfd0((int *)puVar1);
  if (0x31 < (int)uVar3) {
    luaL_verror(s_binary_file__s_too_new__version__1002810c,puVar1[4],uVar3,0x31);
  }
  if ((int)uVar3 < 0x31) {
    luaL_verror(s_binary_file__s_too_old__version__100280c8,puVar1[4],uVar3,0x31);
  }
  uVar3 = lundump__cfd0((int *)puVar1);
  if (uVar3 == 4) {
    luaU_LoadBlock(puVar1,&param_1,4);
    if (PUN(float,param_1) != 1.2345679e-24) {
      lundump__d360((undefined1 *)&param_1);
      if (PUN(float,param_1) != 1.2345679e-24) {
        luaL_verror(s_unknown_float_representation_in_b_10028098,puVar1[4]);
      }
      puVar2[1] = 1;
    }
    puVar2[2] = 1;
    return;
  }
  if (uVar3 == 8) {
    luaU_LoadBlock(puVar1,(undefined4 *)&local_8,8);
    if (local_8 != 1.2345679083165624e-24) {
      lundump__d380((undefined1 *)&local_8);
      if (local_8 != 1.2345679083165624e-24) {
        luaL_verror(s_unknown_float_representation_in_b_10028098,puVar1[4]);
      }
      puVar2[1] = 1;
    }
    puVar2[2] = 0;
    return;
  }
  luaL_verror(s_floats_in_binary_file__s_have__d_1002804c,puVar1[4],uVar3,4);
  return;
}
#undef local_8


/* ---- 0x1000d570  luaU_LoadSignature ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

void __cdecl luaU_LoadSignature(int *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  cVar1 = DAT_1002816c;
  for (pcVar3 = &DAT_1002816c;
      (cVar1 != '\0' && (uVar2 = lundump__cfd0(param_1), uVar2 == (int)*pcVar3));
      pcVar3 = pcVar3 + 1) {
    cVar1 = pcVar3[1];
  }
  if (*pcVar3 != '\0') {
    luaL_verror(s_bad_signature_in_binary_file__s_1002814c,param_1[4]);
  }
  return;
}

/* ---- 0x1000d5c0  luaU_str2number ---- */
/* lundump.c: parses %lf %c */

undefined4 __cdecl luaU_str2number(int *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  #define local_8 (*(double *)(_frame + (0x20 - 0x8)))
  
  piVar1 = param_1;
  if (*param_1 != -2) {
    return 1;
  }
  iVar2 = sscanf((char *)(param_1[1] + 0x18),s__lf__c_10028170,&local_8,&param_1);
  if (iVar2 == 1) {
    *piVar1 = -1;
    piVar1[1] = (int)(float)local_8;
    return 0;
  }
  return 2;
}
#undef local_8


/* ---- 0x1000d620  lundump__d620 ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

undefined4 __cdecl lundump__d620(int *param_1)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  longlong lVar3;
  #define local_3c (*(byte (*)[60])(_frame + (0x50 - 0x3c)))
  
  if (*param_1 != -1) {
    return 1;
  }
  fVar1 = (float)param_1[1];
  if ((-2.1474836e+09 <= fVar1) && (fVar1 <= 2.1474836e+09)) {
    lVar3 = _ftol();
    if ((float)(int)lVar3 == fVar1) {
      sprintf((char *)local_3c,&DAT_1002817c);
      goto LAB_1000d6ae;
    }
  }
  sprintf((char *)local_3c,&DAT_10028178,(double)(float)param_1[1]);
LAB_1000d6ae:
  iVar2 = luaS_new(local_3c);
  param_1[1] = iVar2;
  *param_1 = -2;
  return 0;
}
#undef local_3c

