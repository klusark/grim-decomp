/* LUA.DLL :: io.c
 * functions 0x100053d0 .. 0x10005ad0 (22 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100053d0  io_getint ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* liolib.c helper: numeric argument through lua2C */

longlong __cdecl io_getint(int param_1)

{
  int iVar1;
  longlong lVar2;
  
  iVar1 = lua_lua2C(param_1);
  lua_getnumber(iVar1);
  lVar2 = _ftol();
  return lVar2;
}
#endif


/* ---- 0x100053f0  io_pushresult ---- */
/* Pushes userdata/nil plus strerror(errno) like Lua 3.1 pushresult */

void __cdecl io_pushresult(int param_1)

{
  int *piVar1;
  byte *pbVar2;
  
  if (param_1 != 0) {
    lua_pushusertag((byte *)0x0,0);
    return;
  }
  lua_pushnil();
  piVar1 = _errno();
  pbVar2 = (byte *)strerror(*piVar1);
  lua_pushstring(pbVar2);
  return;
}

/* ---- 0x10005430  io_setfile ---- */
/* Stores a file handle in a global (_INPUT/_OUTPUT) with the file tag */

void __cdecl io_setfile(byte *param_1)

{
  undefined **ppuVar1;
  int iVar2;
  longlong lVar3;
  
  ppuVar1 = (undefined **)((code *)io_getfilebyname)(param_1);
  if ((ppuVar1 != &PTR_DAT_100282d0) && (ppuVar1 != (undefined **)&DAT_100282f0)) {
    (**(code **)(DAT_1002beb8 + 0x34))(ppuVar1);
    iVar2 = lua_getglobal(param_1);
    lua_pushobject(iVar2);
    lVar3 = io_getint(2);
    lua_settag((int)lVar3);
  }
  return;
}

/* ---- 0x10005480  io_getfilebyname ---- */
/* errors '%s is not a file' */

void __cdecl io_getfilebyname(byte *param_1)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  
  iVar2 = lua_getglobal(param_1);
  bVar1 = io_gethandle(iVar2);
  if (((uint)(bVar1)) == 0) {
    luaL_verror(s_global_variable____50s__is_not_a_10026c08,param_1);
  }
  lua_getuserdata(iVar2);
  return;
}

/* ---- 0x100054c0  io_gethandle ---- */
/* checks the userdata tag and errors 'a closed file' */

bool __cdecl io_gethandle(int param_1)

{
  int iVar1;
  longlong lVar2;
  
  iVar1 = lua_isuserdata(param_1);
  if (iVar1 != 0) {
    iVar1 = lua_tag(param_1);
    lVar2 = io_getint(2);
    if (iVar1 == (int)lVar2) {
      lua_error((byte *)s_cannot_access_a_closed_file_10026c38);
    }
    iVar1 = lua_tag(param_1);
    lVar2 = io_getint(1);
    return iVar1 == (int)lVar2;
  }
  return false;
}

/* ---- 0x10005520  io_setreturn ---- */
/* Unidentified function of liolib.c (file/system library) */

void __cdecl io_setreturn(byte *param_1,byte *param_2)

{
  longlong lVar1;
  
  lVar1 = io_getint(1);
  io_setfilebyname(param_1,param_2,(uint)lVar1);
  lua_pushusertag(param_1,(uint)lVar1);
  return;
}

/* ---- 0x10005550  io_setfilebyname ---- */
/* Unidentified function of liolib.c (file/system library) */

void __cdecl io_setfilebyname(byte *param_1,byte *param_2,uint param_3)

{
  lua_pushusertag(param_1,param_3);
  lua_setglobal(param_2);
  return;
}

/* ---- 0x10005570  FUN_10005570 ---- */
void FUN_10005570(void)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  char *pcVar4;
  longlong lVar5;
  
  iVar1 = lua_lua2C(3);
  if (iVar1 == 0) {
    io_setfile((byte *)s__OUTPUT_10026c58);
    io_setreturn(&DAT_100282f0,(byte *)s__OUTPUT_10026c58);
    return;
  }
  iVar2 = lua_tag(iVar1);
  lVar5 = io_getint(1);
  if (iVar2 == (int)lVar5) {
    pbVar3 = (byte *)lua_getuserdata(iVar1);
    io_setreturn(pbVar3,(byte *)s__OUTPUT_10026c58);
    return;
  }
  pcVar4 = (char *)luaL_check_string(3);
  if (*pcVar4 == '|') {
    pbVar3 = (byte *)0x0;
  }
  else {
    pbVar3 = (byte *)(**(code **)(DAT_1002beb8 + 0x30))(pcVar4,&DAT_10026c54);
  }
  if (pbVar3 == (byte *)0x0) {
    io_pushresult(0);
    return;
  }
  io_setreturn(pbVar3,(byte *)s__OUTPUT_10026c58);
  return;
}

/* ---- 0x10005620  FUN_10005620 ---- */
void FUN_10005620(void)

{
  undefined4 uVar1;
  byte *pbVar2;
  
  uVar1 = luaL_check_string(3);
  pbVar2 = (byte *)(**(code **)(DAT_1002beb8 + 0x30))(uVar1,&DAT_10026c60);
  if (pbVar2 != (byte *)0x0) {
    io_setreturn(pbVar2,(byte *)s__OUTPUT_10026c58);
    return;
  }
  io_pushresult(0);
  return;
}

/* ---- 0x10005660  FUN_10005660 ---- */
void FUN_10005660(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  char *pcVar2;
  uint uVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  #define iStack_c (*(int *)(_frame + (0x20 - 0xc)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define pcStack_4 (*(char **)(_frame + (0x20 - 0x4)))
  
  iStack_c = 3;
  uStack_8 = ((code *)io_getfileparam)((byte *)s__INPUT_10026c00,&iStack_c);
  pcVar2 = (char *)luaL_opt_string(iStack_c,s__________10026c88);
  iVar6 = 0;
  iVar5 = -2;
  luaL_resetbuffer();
  cVar1 = *pcVar2;
  while (cVar1 != '\0') {
    if (cVar1 == '{') {
      iVar6 = iVar6 + 1;
      pcVar7 = pcVar2 + 1;
    }
    else if (cVar1 == '}') {
      if (iVar6 == 0) {
        lua_error((byte *)s_unbalanced_braces_in_read_patter_10026c64);
      }
      iVar6 = iVar6 + -1;
      pcVar7 = pcVar2 + 1;
    }
    else {
      if (iVar5 == -2) {
        iVar5 = lauxlib__2960(uStack_8);
      }
      if (iVar5 == -1) {
        uVar3 = 0;
      }
      else {
        uVar3 = (uint)(char)iVar5;
      }
      uVar3 = str_singlematch(uVar3,pcVar2,(int *)&pcStack_4);
      if (uVar3 != 0) {
        if (iVar6 == 0) {
          luaL_addchar((char)iVar5);
        }
        iVar5 = -2;
      }
      if (*pcStack_4 == '*') {
        pcVar7 = pcVar2;
        if (uVar3 == 0) goto LAB_10005731;
      }
      else if (*pcStack_4 == '?') {
LAB_10005731:
        pcVar7 = pcStack_4 + 1;
      }
      else {
        pcVar7 = pcStack_4;
        if (uVar3 == 0) break;
      }
    }
    pcVar2 = pcVar7;
    cVar1 = *pcVar7;
  }
  if (-1 < iVar5) {
    lauxlib__2990(iVar5,uStack_8);
  }
  luaL_addchar(0);
  pbVar4 = (byte *)lbuiltin__2da0();
  if ((*pbVar4 != 0) || (*pcVar2 == '\0')) {
    lua_pushstring(pbVar4);
  }
  return;
}
#undef iStack_c
#undef pcStack_4
#undef uStack_8


/* ---- 0x10005780  io_getfileparam ---- */
/* Unidentified function of liolib.c (file/system library) */

void __cdecl io_getfileparam(byte *param_1,int *param_2)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  
  iVar2 = lua_lua2C(*param_2);
  bVar1 = io_gethandle(iVar2);
  if (((uint)(bVar1)) != 0) {
    *param_2 = *param_2 + 1;
    lua_getuserdata(iVar2);
    return;
  }
  io_getfilebyname(param_1);
  return;
}

/* ---- 0x100057d0  FUN_100057d0 ---- */
void FUN_100057d0(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iStack_4 = 3;
  uVar3 = ((code *)io_getfileparam)((byte *)s__OUTPUT_10026c58,&iStack_4);
  iVar2 = iStack_4;
  iStack_4 = iStack_4 + 1;
  iVar6 = 1;
  pcVar4 = (char *)luaL_opt_string(iVar2,0);
  do {
    if (pcVar4 == (char *)0x0) {
      io_pushresult(iVar6);
      return;
    }
    if (iVar6 == 0) {
LAB_1000583c:
      iVar6 = 0;
    }
    else {
      uVar5 = 0xffffffff;
      pcVar7 = pcVar4;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      iVar6 = (**(code **)(DAT_1002beb8 + 0x40))(uVar3,pcVar4,~uVar5 - 1);
      if (iVar6 == -1) goto LAB_1000583c;
      iVar6 = 1;
    }
    iVar2 = iStack_4;
    iStack_4 = iStack_4 + 1;
    pcVar4 = (char *)luaL_opt_string(iVar2,0);
  } while( true );
}
#undef iStack_4


/* ---- 0x10005870  FUN_10005870 ---- */
void FUN_10005870(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = luaL_check_string(1);
  uVar2 = system(iVar1);
  lua_pushnumber((float)(int)uVar2);
  return;
}

/* ---- 0x100058a0  FUN_100058a0 ---- */
void FUN_100058a0(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = luaL_check_string(1);
  iVar2 = remove(uVar1);
  io_pushresult((uint)(iVar2 == 0));
  return;
}

/* ---- 0x100058d0  FUN_100058d0 ---- */
void FUN_100058d0(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = luaL_check_string(2);
  uVar2 = luaL_check_string(1);
  iVar3 = rename(uVar2,uVar1);
  io_pushresult((uint)(iVar3 == 0));
  return;
}

/* ---- 0x10005900  FUN_10005900 ---- */
void FUN_10005900(void)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)tmpnam((char *)0x0);
  lua_pushstring(pbVar1);
  return;
}

/* ---- 0x10005920  FUN_10005920 ---- */
void FUN_10005920(void)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)luaL_check_string(1);
  pbVar1 = (byte *)getenv(pbVar1);
  lua_pushstring(pbVar1);
  return;
}

/* ---- 0x10005940  FUN_10005940 ---- */
void FUN_10005940(void)

{
  unsigned char _frame[0x220] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  int *piVar2;
  int iVar3;
  #define iStack_204 (*(int *)(_frame + (0x220 - 0x204)))
  #define abStack_200 (*(byte (*)[512])(_frame + (0x220 - 0x200)))
  
  pbVar1 = (byte *)luaL_opt_string(1,&DAT_10026cac);
  time(&iStack_204);
  piVar2 = localtime(&iStack_204);
  iVar3 = ((code *)strftime)(abStack_200,0x200,pbVar1,piVar2);
  if (iVar3 != 0) {
    lua_pushstring(abStack_200);
    return;
  }
  lua_error((byte *)s_invalid__date__format_10026c94);
  return;
}
#undef abStack_200
#undef iStack_204


/* ---- 0x100059c0  FUN_100059c0 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void FUN_100059c0(void)

{
  int iVar1;
  uint *puVar2;
  byte *pbVar3;
  longlong lVar4;
  
  luaL_opt_number(2,0.0);
  lVar4 = _ftol();
  iVar1 = (int)lVar4;
  if ((iVar1 < 0) || (5 < iVar1)) {
    luaL_argerror(2,IMG_ADDR(0x10026cb0));
  }
  puVar2 = (uint *)luaL_check_string(1);
  pbVar3 = (byte *)setlocale(*(int *)(&DAT_10026ae8 + iVar1 * 4),puVar2);
  lua_pushstring(pbVar3);
  return;
}
#endif


/* ---- 0x10005a20  FUN_10005a20 ---- */
void FUN_10005a20(void)

{
  lua_lua2C(1);
  (**(code **)(DAT_1002beb8 + 0x18))
            (s_FALSE_10026cc0,s_C__grimsrc_libs_lua_src_liolib_c_10026cc8,0x134);
  return;
}

/* ---- 0x10005a50  FUN_10005a50 ---- */
void FUN_10005a50(void)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  bool bVar5;
  #define abStack_fc (*(byte (*)[252])(_frame + (0x110 - 0xfc)))
  
  do {
    iVar2 = (**(code **)(DAT_1002beb8 + 0x3c))(&PTR_DAT_100282d0,abStack_fc,0xfa);
    if (iVar2 == 0) {
      return;
    }
    pbVar4 = &DAT_10026cec;
    pbVar3 = abStack_fc;
    do {
      bVar1 = *pbVar3;
      bVar5 = bVar1 < *pbVar4;
      if (bVar1 != *pbVar4) {
LAB_10005aa8:
        iVar2 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
        goto LAB_10005aad;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar5 = bVar1 < pbVar4[1];
      if (bVar1 != pbVar4[1]) goto LAB_10005aa8;
      pbVar3 = pbVar3 + 2;
      pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    iVar2 = 0;
LAB_10005aad:
    if (iVar2 == 0) {
      return;
    }
    lua_dostring((char *)abStack_fc);
  } while( true );
}
#undef abStack_fc


/* ---- 0x10005ad0  FUN_10005ad0 ---- */
void FUN_10005ad0(void)

{
  lua_printstack(0);
  return;
}
