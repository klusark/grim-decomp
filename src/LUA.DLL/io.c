/* LUA.DLL :: io.c
 * functions 0x100053d0 .. 0x10005ad0 (22 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100053d0  gettag ---- */
/* liolib.c helper: numeric argument through lua2C Named gettag (not in the remaster, gcc inlined it
   there): Lua 3.1 source name (liolib.c static gettag: the number of upvalue i, called with IOTAG 1
   and CLOSEDTAG 2); was io_getint. */

longlong __cdecl gettag(int i)

{
  int o;
  longlong lVar1;
  float fVar2;
  
  o = lua_lua2C(i);
  fVar2 = lua_getnumber(o);
  lVar1 = FTOL((float10)fVar2);
  return lVar1;
}

/* ---- 0x100053f0  pushresult ---- */
/* Pushes userdata/nil plus strerror(errno) like Lua 3.1 pushresult Named pushresult (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (liolib.c static pushresult: a user value on
   success, else nil and strerror(errno)); was io_pushresult. */

void __cdecl pushresult(int i)

{
  int *piVar1;
  byte *str;
  
  if (i != 0) {
    lua_pushusertag((byte *)0x0,0);
    return;
  }
  lua_pushnil();
  piVar1 = _errno();
  str = (byte *)strerror(*piVar1);
  lua_pushstring(str);
  return;
}

/* ---- 0x10005430  closefile ---- */
/* Stores a file handle in a global (_INPUT/_OUTPUT) with the file tag Named closefile (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (liolib.c static closefile(name):
   getfile(name), not stdin / stdout, close, then settag(gettag(CLOSEDTAG)) on the global); was
   io_setfile. */

void __cdecl closefile(byte *str)

{
  undefined **ppuVar1;
  int o;
  longlong lVar2;
  
  ppuVar1 = (undefined **)getfile(str);
  if ((ppuVar1 != &PTR_DAT_100282d0) && (ppuVar1 != (undefined **)&DAT_100282f0)) {
    (**(code **)(g_dwLuaHS + 0x34))(ppuVar1);
    o = lua_getglobal(str);
    lua_pushobject(o);
    lVar2 = gettag(2);
    lua_settag((int)lVar2);
  }
  return;
}

/* ---- 0x10005480  getfile ---- */
/* errors '%s is not a file' Named getfile (not in the remaster, gcc inlined it there): Lua 3.1
   source name (liolib.c static getfile(name): the global must be ishandler, error "global variable
   `%.50s' is not a file handle"); was io_getfilebyname. */

int __cdecl getfile(byte *str)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  
  iVar2 = lua_getglobal(str);
  bVar1 = ishandler(iVar2);
  if (((uint)(byte)(bVar1)) == 0) {
    luaL_verror(s_global_variable____50s__is_not_a_10026c08,str);
  }
  iVar2 = lua_getuserdata(iVar2);
  return iVar2;
}

/* ---- 0x100054c0  ishandler ---- */
/* checks the userdata tag and errors 'a closed file' Named ishandler (not in the remaster, gcc
   inlined it there): Lua 3.1 source name (liolib.c static ishandler: a userdata with the CLOSEDTAG
   errors "cannot access a closed file", true when the tag is IOTAG); was io_gethandle. */

int __cdecl ishandler(int f)

{
  int iVar1;
  longlong lVar2;
  
  iVar1 = lua_isuserdata(f);
  if (iVar1 != 0) {
    iVar1 = lua_tag(f);
    lVar2 = gettag(2);
    if (iVar1 == (int)lVar2) {
      lua_error((byte *)s_cannot_access_a_closed_file_10026c38);
    }
    iVar1 = lua_tag(f);
    lVar2 = gettag(1);
    return iVar1 == (int)lVar2;
  }
  return false;
}

/* ---- 0x10005520  setreturn ---- */
/* Named setreturn (not in the remaster, gcc inlined it there): Lua 3.1 source name (liolib.c static
   setreturn(f, name): setfile with gettag(IOTAG), then pushusertag); was io_setreturn. */

void __cdecl setreturn(byte *udata,byte *str)

{
  longlong lVar1;
  
  lVar1 = gettag(1);
  setfile(udata,str,(uint)lVar1);
  lua_pushusertag(udata,(uint)lVar1);
  return;
}

/* ---- 0x10005550  setfile ---- */
/* Named setfile (not in the remaster, gcc inlined it there): Lua 3.1 source name (liolib.c static
   setfile(f, name, tag): pushusertag, setglobal); was io_setfilebyname. */

void __cdecl setfile(byte *udata,byte *str,uint tag)

{
  lua_pushusertag(udata,tag);
  lua_setglobal(str);
  return;
}

/* ---- 0x10005570  io_writeto ---- */
/* Original name io_writeto (the remaster's libLua.so: iolib entry 'writeto'); was FUN_10005570. */

void __cdecl io_writeto(void)

{
  int o;
  int iVar1;
  byte *pbVar2;
  char *pcVar3;
  longlong lVar4;
  
  o = lua_lua2C(3);
  if (o == 0) {
    closefile((byte *)s__OUTPUT_10026c58);
    setreturn(&DAT_100282f0,(byte *)s__OUTPUT_10026c58);
    return;
  }
  iVar1 = lua_tag(o);
  lVar4 = gettag(1);
  if (iVar1 == (int)lVar4) {
    pbVar2 = (byte *)lua_getuserdata(o);
    setreturn(pbVar2,(byte *)s__OUTPUT_10026c58);
    return;
  }
  pcVar3 = (char *)luaL_check_string(3);
  if (*pcVar3 == '|') {
    pbVar2 = (byte *)0x0;
  }
  else {
    pbVar2 = (byte *)(**(code **)(g_dwLuaHS + 0x30))(pcVar3,s_w_10026c54);
  }
  if (pbVar2 == (byte *)0x0) {
    pushresult(0);
    return;
  }
  setreturn(pbVar2,(byte *)s__OUTPUT_10026c58);
  return;
}

/* ---- 0x10005620  io_appendto ---- */
/* Original name io_appendto (the remaster's libLua.so: iolib entry 'appendto'); was FUN_10005620.
    */

void __cdecl io_appendto(void)

{
  undefined4 uVar1;
  byte *udata;
  
  uVar1 = luaL_check_string(3);
  udata = (byte *)(**(code **)(g_dwLuaHS + 0x30))(uVar1,s_a_10026c60);
  if (udata != (byte *)0x0) {
    setreturn(udata,(byte *)s__OUTPUT_10026c58);
    return;
  }
  pushresult(0);
  return;
}

/* ---- 0x10005660  io_read ---- */
/* Original name io_read (the remaster's libLua.so: iolib entry 'read'); was FUN_10005660. */

void __cdecl io_read(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  char *p;
  uint uVar2;
  byte *str;
  int c;
  int iVar3;
  char *pcVar4;
  #define iStack_c (*(int *)(_frame + (0x20 - 0xc)))
  #define iStack_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define pcStack_4 (*(char **)(_frame + (0x20 - 0x4)))
  
  iStack_c = 3;
  iStack_8 = getfileparam((byte *)s__INPUT_10026c00,&iStack_c);
  p = (char *)luaL_opt_string(iStack_c,s__________10026c88);
  iVar3 = 0;
  c = -2;
  luaL_resetbuffer();
  cVar1 = *p;
  while (cVar1 != '\0') {
    if (cVar1 == '{') {
      iVar3 = iVar3 + 1;
      pcVar4 = p + 1;
    }
    else if (cVar1 == '}') {
      if (iVar3 == 0) {
        lua_error((byte *)s_unbalanced_braces_in_read_patter_10026c64);
      }
      iVar3 = iVar3 + -1;
      pcVar4 = p + 1;
    }
    else {
      if (c == -2) {
        c = luaFGetc(iStack_8);
      }
      if (c == -1) {
        uVar2 = 0;
      }
      else {
        uVar2 = (uint)(char)c;
      }
      uVar2 = luaI_singlematch(uVar2,p,(int *)&pcStack_4);
      if (uVar2 != 0) {
        if (iVar3 == 0) {
          luaL_addchar((char)c);
        }
        c = -2;
      }
      if (*pcStack_4 == '*') {
        pcVar4 = p;
        if (uVar2 == 0) goto LAB_10005731;
      }
      else if (*pcStack_4 == '?') {
LAB_10005731:
        pcVar4 = pcStack_4 + 1;
      }
      else {
        pcVar4 = pcStack_4;
        if (uVar2 == 0) break;
      }
    }
    p = pcVar4;
    cVar1 = *pcVar4;
  }
  if (-1 < c) {
    luaFUngetc(c,iStack_8);
  }
  luaL_addchar(0);
  str = (byte *)luaL_buffer();
  if ((*str != 0) || (*p == '\0')) {
    lua_pushstring(str);
  }
  return;
}
#undef iStack_8
#undef iStack_c
#undef pcStack_4


/* ---- 0x10005780  getfileparam ---- */
/* Named getfileparam (not in the remaster, gcc inlined it there): Lua 3.1 source name (liolib.c
   static getfileparam(name, arg): the parameter if ishandler (and arg++), else getfile(name)); was
   io_getfileparam. */

int __cdecl getfileparam(byte *str,int *arg)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  
  iVar2 = lua_lua2C(*arg);
  bVar1 = ishandler(iVar2);
  if (((uint)(byte)(bVar1)) != 0) {
    *arg = *arg + 1;
    iVar2 = lua_getuserdata(iVar2);
    return iVar2;
  }
  iVar2 = getfile(str);
  return iVar2;
}

/* ---- 0x100057d0  io_write ---- */
/* Original name io_write (the remaster's libLua.so: iolib entry 'write'); was FUN_100057d0. */

void __cdecl io_write(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iStack_4 = 3;
  iVar3 = getfileparam((byte *)s__OUTPUT_10026c58,&iStack_4);
  iVar2 = iStack_4;
  iStack_4 = iStack_4 + 1;
  iVar6 = 1;
  pcVar4 = (char *)luaL_opt_string(iVar2,0);
  do {
    if (pcVar4 == (char *)0x0) {
      pushresult(iVar6);
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
      iVar6 = (**(code **)(g_dwLuaHS + 0x40))(iVar3,pcVar4,~uVar5 - 1);
      if (iVar6 == -1) goto LAB_1000583c;
      iVar6 = 1;
    }
    iVar2 = iStack_4;
    iStack_4 = iStack_4 + 1;
    pcVar4 = (char *)luaL_opt_string(iVar2,0);
  } while( true );
}
#undef iStack_4


/* ---- 0x10005870  io_execute ---- */
/* Original name io_execute (the remaster's libLua.so: iolib entry 'execute'); was FUN_10005870. */

void __cdecl io_execute(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = luaL_check_string(1);
  uVar2 = system(iVar1);
  lua_pushnumber((float)(int)uVar2);
  return;
}

/* ---- 0x100058a0  io_remove ---- */
/* Original name io_remove (the remaster's libLua.so: iolib entry 'remove'); was FUN_100058a0. */

void __cdecl io_remove(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = luaL_check_string(1);
  iVar2 = remove(uVar1);
  pushresult((uint)(iVar2 == 0));
  return;
}

/* ---- 0x100058d0  io_rename ---- */
/* Original name io_rename (the remaster's libLua.so: iolib entry 'rename'); was FUN_100058d0. */

void __cdecl io_rename(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = luaL_check_string(2);
  uVar2 = luaL_check_string(1);
  iVar3 = rename(uVar2,uVar1);
  pushresult((uint)(iVar3 == 0));
  return;
}

/* ---- 0x10005900  io_tmpname ---- */
/* Original name io_tmpname (the remaster's libLua.so: iolib entry 'tmpname'); was FUN_10005900. */

void __cdecl io_tmpname(void)

{
  byte *str;
  
  str = (byte *)tmpnam((char *)0x0);
  lua_pushstring(str);
  return;
}

/* ---- 0x10005920  io_getenv ---- */
/* Original name io_getenv (the remaster's libLua.so: iolib entry 'getenv'); was FUN_10005920. */

void __cdecl io_getenv(void)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)luaL_check_string(1);
  pbVar1 = (byte *)getenv(pbVar1);
  lua_pushstring(pbVar1);
  return;
}

/* ---- 0x10005940  io_date ---- */
/* Original name io_date (the remaster's libLua.so: iolib entry 'date'); was FUN_10005940. */

void __cdecl io_date(void)

{
  unsigned char _frame[0x220] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte *pbVar1;
  int *piVar2;
  int iVar3;
  #define iStack_204 (*(int *)(_frame + (0x220 - 0x204)))
  #define abStack_200 (*(byte (*)[512])(_frame + (0x220 - 0x200)))
  
  pbVar1 = (byte *)luaL_opt_string(1,s__c_10026cac);
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


/* ---- 0x100059c0  setloc ---- */
/* Original name setloc (the remaster's libLua.so: iolib entry 'setlocale'); was FUN_100059c0. */

void __cdecl setloc(void)

{
  int iVar1;
  uint *puVar2;
  byte *str;
  longlong lVar3;
  float fVar4;
  
  fVar4 = luaL_opt_number(2,0.0f);
  lVar3 = FTOL((float10)fVar4);
  iVar1 = (int)lVar3;
  if ((iVar1 < 0) || (5 < iVar1)) {
    luaL_argerror(2,((unsigned)(uintptr_t)&s_invalid_option_10026cb0));
  }
  puVar2 = (uint *)luaL_check_string(1);
  str = (byte *)setlocale(*(int *)(&g_aSetloc_cat + iVar1 * 4),puVar2);
  lua_pushstring(str);
  return;
}

/* ---- 0x10005a20  io_exit ---- */
/* Original name io_exit (the remaster's libLua.so: iolib entry 'exit'); was FUN_10005a20. */

void __cdecl io_exit(void)

{
  lua_lua2C(1);
  (**(code **)(g_dwLuaHS + 0x18))
            (s_FALSE_10026cc0,s_C__grimsrc_libs_lua_src_liolib_c_10026cc8,0x134);
  return;
}

/* ---- 0x10005a50  io_debug ---- */
/* Original name io_debug (the remaster's libLua.so: iolib entry 'debug'); was FUN_10005a50. */

void __cdecl io_debug(void)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  char *pcVar4;
  bool bVar5;
  #define abStack_fc (*(byte (*)[252])(_frame + (0x110 - 0xfc)))
  
  do {
    iVar2 = (**(code **)(g_dwLuaHS + 0x3c))(&PTR_DAT_100282d0,abStack_fc,0xfa);
    if (iVar2 == 0) {
      return;
    }
    pcVar4 = s_cont_10026cec;
    pbVar3 = abStack_fc;
    do {
      bVar1 = *pbVar3;
      bVar5 = bVar1 < (byte)*pcVar4;
      if (bVar1 != *pcVar4) {
LAB_10005aa8:
        iVar2 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
        goto LAB_10005aad;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar5 = bVar1 < (byte)pcVar4[1];
      if (bVar1 != pcVar4[1]) goto LAB_10005aa8;
      pbVar3 = pbVar3 + 2;
      pcVar4 = pcVar4 + 2;
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


/* ---- 0x10005ad0  errorfb ---- */
/* Original name errorfb (the remaster's libLua.so: iolib entry 'print_stack'); was FUN_10005ad0. */

void __cdecl errorfb(void)

{
  lua_printstack(0);
  return;
}
