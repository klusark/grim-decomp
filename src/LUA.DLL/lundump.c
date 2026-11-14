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
    uVar3 = LoadChunk((int *)&local_c);
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


/* ---- 0x1000cf10  LoadChunk ---- */
/* Named LoadChunk (not in the remaster, gcc inlined it there): Lua 3.1 source name (lundump.c
   static LoadChunk: LoadHeader, then LoadFunction); was luaU_LoadChunk. */

undefined4 * __cdecl LoadChunk(int *param_1)

{
  undefined4 *puVar1;
  
  LoadHeader(param_1);
  puVar1 = LoadFunction(param_1);
  return puVar1;
}

/* ---- 0x1000cf30  LoadFunction ---- */
/* Original name LoadFunction (the remaster's libLua.so: static LoadFunction(ZIO*): luaF_newproto,
   the code, locals, constants and nested functions (caller luaU_undump1's chunk loader)); was
   luaU_LoadFunction. */

undefined4 * __cdecl LoadFunction(int *param_1)

{
  uint *puVar1;
  TProtoFunc *pTVar2;
  uint uVar3;
  TaggedString *pTVar4;
  byte *pbVar5;
  uint *puVar6;
  
  puVar1 = (uint *)*param_1;
  pTVar2 = luaF_newproto();
  uVar3 = LoadWord((int *)puVar1);
  pTVar2->nLineDefined = uVar3;
  pTVar4 = (TaggedString *)LoadTString(puVar1);
  pTVar2->pFileName = pTVar4;
  puVar6 = puVar1;
  uVar3 = LoadSize((int *)puVar1);
  pbVar5 = (byte *)lundump__d030(uVar3,puVar6);
  pTVar2->pCode = pbVar5;
  LoadConstants((int)pTVar2,param_1);
  LoadLocals((int)pTVar2,puVar1);
  lundump__d3c0((int)pTVar2,param_1);
  return &pTVar2->pNext;
}

/* ---- 0x1000cfa0  LoadWord ---- */
/* Named LoadWord (not in the remaster, gcc inlined it there): Lua 3.1 source name (lundump.c: two
   ezgetc bytes, high first); was lundump__cfa0. */

uint __cdecl LoadWord(int *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = ezgetc(param_1);
  uVar2 = ezgetc(param_1);
  return uVar1 << 8 | uVar2;
}

/* ---- 0x1000cfd0  ezgetc ---- */
/* Named ezgetc (not in the remaster, gcc inlined it there): Lua 3.1 source name (lundump.c: zgetc,
   unexpected end of file on EOZ); was lundump__cfd0. */

uint __cdecl ezgetc(int *param_1)

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
    unexpectedEOZ((int)param_1);
  }
  return uVar2;
}

/* ---- 0x1000d010  unexpectedEOZ ---- */
/* Named unexpectedEOZ (not in the remaster, gcc inlined it there): Lua 3.1 source name (lundump.c
   static unexpectedEOZ: error "unexpected end of binary file %s"); was luaU_unexpectedEOZ. */

void __cdecl unexpectedEOZ(int param_1)

{
  luaL_verror(s_unexpected_end_of_binary_file__s_10027fe8,*(undefined4 *)(param_1 + 0x10));
  return;
}

/* ---- 0x1000d030  lundump__d030 ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

undefined4 * __cdecl lundump__d030(uint param_1,uint *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)
           (**(code **)(g_dwLuaHS + 0x20))(param_1,s_C__grimsrc_libs_lua_src_lundump__1002800c,0x31)
  ;
  ezread(param_2,puVar1,param_1);
  return puVar1;
}

/* ---- 0x1000d060  ezread ---- */
/* Named ezread (not in the remaster, gcc inlined it there): Lua 3.1 source name (lundump.c static
   ezread: zread, unexpectedEOZ when bytes are missing); was luaU_LoadBlock. */

uint __cdecl ezread(uint *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = luaZ_read(param_1,param_2,param_3);
  if (uVar1 != 0) {
    unexpectedEOZ((int)param_1);
  }
  return uVar1;
}

/* ---- 0x1000d090  LoadSize ---- */
/* Named LoadSize (not in the remaster, gcc inlined it there): Lua 3.1 source name (lundump.c static
   LoadSize: two LoadWord as hi << 16 | lo, error "code too long (%ld bytes)"; called by
   LoadFunction for the code size); was luaU_LoadCode. */

uint __cdecl LoadSize(int *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = LoadWord(param_1);
  uVar2 = LoadWord(param_1);
  uVar3 = uVar1 << 0x10 | uVar2;
  if ((uVar1 != 0) && (uVar3 == uVar2)) {
    luaL_verror(s_code_too_long___ld_bytes__10028030,uVar3);
  }
  return uVar3;
}

/* ---- 0x1000d0d0  LoadTString ---- */
/* Original name LoadTString (the remaster's libLua.so: static LoadTString(ZIO*): the string
   (luaL_openspace + read) through luaS_new); was luaU_LoadString. */

undefined4 __cdecl LoadTString(uint *param_1)

{
  uint *str;
  TaggedString *pTVar1;
  
  str = Undump_LoadString(param_1);
  if (str == (uint *)0x0) {
    return 0;
  }
  pTVar1 = luaS_new((char *)str);
  return pTVar1;
}

/* ---- 0x1000d0f0  Undump_LoadString ---- */
/* Named Undump_LoadString (the bridge refuses the bare name LoadString beside LoadTString) (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lundump.c: LoadWord size,
   luaL_openspace, LoadBlock); was lundump__d0f0. */

uint * __cdecl Undump_LoadString(uint *param_1)

{
  uint uVar1;
  uint *puVar2;
  
  uVar1 = LoadWord((int *)param_1);
  if (uVar1 == 0) {
    return (uint *)0x0;
  }
  puVar2 = (uint *)luaL_openspace(uVar1);
  ezread(param_1,puVar2,uVar1);
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

/* ---- 0x1000d1a0  LoadLocals ---- */
/* Named LoadLocals (not in the remaster, gcc inlined it there): Lua 3.1 source name (lundump.c
   static LoadLocals: n = LoadWord, then n (line, LoadTString) pairs and a terminator with line -1);
   was luaU_LoadLocals. */

void __cdecl LoadLocals(int param_1,uint *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  uVar1 = LoadWord((int *)param_2);
  if (uVar1 != 0) {
    uVar2 = (**(code **)(g_dwLuaHS + 0x20))
                      (uVar1 * 8 + 8,s_C__grimsrc_libs_lua_src_lundump__1002800c,0xa4);
    iVar4 = 0;
    *(undefined4 *)(param_1 + 0x1c) = uVar2;
    if (0 < (int)uVar1) {
      do {
        uVar3 = LoadWord((int *)param_2);
        *(uint *)(*(int *)(param_1 + 0x1c) + 4 + iVar4 * 8) = uVar3;
        uVar2 = LoadTString(param_2);
        *(undefined4 *)(*(int *)(param_1 + 0x1c) + iVar4 * 8) = uVar2;
        iVar4 = iVar4 + 1;
      } while (iVar4 < (int)uVar1);
    }
    *(undefined4 *)(*(int *)(param_1 + 0x1c) + 4 + iVar4 * 8) = 0xffffffff;
    *(undefined4 *)(*(int *)(param_1 + 0x1c) + iVar4 * 8) = 0;
  }
  return;
}

/* ---- 0x1000d230  LoadConstants ---- */
/* Named LoadConstants (not in the remaster, gcc inlined it there): Lua 3.1 source name (lundump.c
   static LoadConstants: n = LoadWord, each by its type byte 'N' number, 'S' string, 'F' function);
   was luaU_LoadConstants. */

void __cdecl LoadConstants(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  float fVar6;
  
  uVar2 = LoadWord((int *)*param_2);
  *(uint *)(param_1 + 0xc) = uVar2;
  if (uVar2 != 0) {
    uVar3 = (**(code **)(g_dwLuaHS + 0x20))
                      (uVar2 * 8,s_C__grimsrc_libs_lua_src_lundump__1002800c,0xb3);
    iVar5 = 0;
    *(undefined4 *)(param_1 + 8) = uVar3;
    if (0 < (int)uVar2) {
      do {
        puVar1 = (undefined4 *)(*(int *)(param_1 + 8) + iVar5 * 8);
        uVar4 = ezgetc((int *)*param_2);
        if (uVar4 == 0x46) {
          *puVar1 = 0xfffffffc;
          puVar1[1] = 0;
        }
        else if (uVar4 == 0x4e) {
          *puVar1 = 0xffffffff;
          fVar6 = luaU_LoadNumber(param_2);
          puVar1[1] = PUN(undefined4,(float)(fVar6));
        }
        else if (uVar4 == 0x53) {
          *puVar1 = 0xfffffffe;
          uVar3 = LoadTString((uint *)*param_2);
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
    ezread((uint *)*param_1,&param_1,4);
    if (puVar1[1] != 0) {
      lundump__d360((undefined1 *)&param_1);
    }
    return PUN(float,param_1);
  }
  ezread((uint *)*param_1,(undefined4 *)&local_8,8);
  if (puVar1[1] != 0) {
    lundump__d380((undefined1 *)&local_8);
  }
  return (float)local_8;
}
#undef local_8


/* ---- 0x1000d360  lundump__d360 ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

int __cdecl lundump__d360(undefined1 *param_1)

{
  undefined1 uVar1;
  
  uVar1 = *param_1;
  *param_1 = param_1[3];
  param_1[3] = uVar1;
  uVar1 = param_1[1];
  param_1[1] = param_1[2];
  param_1[2] = uVar1;
  return (int)(param_1 + 2);
}

/* ---- 0x1000d380  lundump__d380 ---- */
/* Unidentified function of lundump.c (precompiled chunk loader) */

int __cdecl lundump__d380(undefined1 *param_1)

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
  return (int)(param_1 + 4);
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
    uVar2 = LoadWord((int *)*param_2);
    puVar3 = LoadFunction(param_2);
    *(undefined4 **)(*(int *)(param_1 + 8) + 4 + uVar2 * 8) = puVar3;
  }
  return;
}

/* ---- 0x1000d420  LoadHeader ---- */
/* lundump.c: binary file %s too new/old version Named LoadHeader (not in the remaster, gcc inlined
   it there): Lua 3.1 source name (lundump.c static LoadHeader: LoadSignature, the version 0x31
   ("too new" / "too old"), the float size and test number "unknown float representation"); was
   luaU_loadheader. */

void __cdecl LoadHeader(undefined4 *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  #define local_8 (*(double *)(_frame + (0x20 - 0x8)))
  
  puVar2 = param_1;
  puVar1 = (uint *)*param_1;
  LoadSignature((int *)puVar1);
  uVar3 = ezgetc((int *)puVar1);
  if (0x31 < (int)uVar3) {
    luaL_verror(s_binary_file__s_too_new__version__1002810c,puVar1[4],uVar3,0x31);
  }
  if ((int)uVar3 < 0x31) {
    luaL_verror(s_binary_file__s_too_old__version__100280c8,puVar1[4],uVar3,0x31);
  }
  uVar3 = ezgetc((int *)puVar1);
  if (uVar3 == 4) {
    ezread(puVar1,&param_1,4);
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
    ezread(puVar1,(undefined4 *)&local_8,8);
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


/* ---- 0x1000d570  LoadSignature ---- */
/* Named LoadSignature (not in the remaster, gcc inlined it there): Lua 3.1 source name (lundump.c
   static LoadSignature: compares the signature bytes, error "bad signature in binary file %s"); was
   luaU_LoadSignature. */

void __cdecl LoadSignature(int *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  cVar1 = DAT_1002816c;
  for (pcVar3 = &DAT_1002816c; (cVar1 != '\0' && (uVar2 = ezgetc(param_1), uVar2 == (int)*pcVar3));
      pcVar3 = pcVar3 + 1) {
    cVar1 = pcVar3[1];
  }
  if (*pcVar3 != '\0') {
    luaL_verror(s_bad_signature_in_binary_file__s_1002814c,param_1[4]);
  }
  return;
}

/* ---- 0x1000d5c0  luaV_tonumber ---- */
/* lundump.c: parses %lf %c Original name luaV_tonumber (the remaster's libLua.so: sscanf '%lf %c',
   callers lua_getnumber / lua_isnumber / the VM); was luaU_str2number. */

undefined4 __cdecl luaV_tonumber(int *param_1)

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
    piVar1[1] = PUN(int,(float)(float)local_8);
    return 0;
  }
  return 2;
}
#undef local_8


/* ---- 0x1000d620  luaV_tostring ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name luaV_tostring (the remaster's libLua.so: sprintf of the number, luaS_new; caller
   lua_getstring); was lundump__d620. */

undefined4 __cdecl luaV_tostring(int *param_1)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  TaggedString *pTVar2;
  longlong lVar3;
  #define local_3c (*(char (*)[60])(_frame + (0x50 - 0x3c)))
  
  if (*param_1 != -1) {
    return 1;
  }
  fVar1 = (float)param_1[1];
  if ((-2.1474836e+09 <= fVar1) && (fVar1 <= 2.1474836e+09)) {
    lVar3 = _ftol();
    if ((float)(int)lVar3 == fVar1) {
      sprintf(local_3c,&DAT_1002817c);
      goto LAB_1000d6ae;
    }
  }
  sprintf(local_3c,&DAT_10028178,(double)(float)param_1[1]);
LAB_1000d6ae:
  pTVar2 = luaS_new(local_3c);
  param_1[1] = (int)pTVar2;
  *param_1 = -2;
  return 0;
}
#undef local_3c

#endif

