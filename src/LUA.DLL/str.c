/* LUA.DLL :: str.c
 * functions 0x100095b0 .. 0x1000a680 (22 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x100095b0  str_sub ---- */
/* lstrlib.c strsub */

void str_sub(void)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  longlong lVar8;
  float fVar9;
  
  pcVar2 = (char *)luaL_check_string(1);
  uVar5 = 0xffffffff;
  pcVar7 = pcVar2;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  iVar6 = ~uVar5 - 1;
  fVar9 = luaL_check_number(2);
  lVar8 = FTOL((float10)fVar9);
  iVar3 = (int)lVar8;
  fVar9 = luaL_opt_number(3,-1.0f);
  lVar8 = FTOL((float10)fVar9);
  iVar4 = (int)lVar8;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 1 + iVar6;
  }
  if (iVar4 < 0) {
    iVar4 = iVar4 + 1 + iVar6;
  }
  if (((0 < iVar3) && (iVar3 <= iVar4)) && (iVar4 <= iVar6)) {
    luaL_resetbuffer();
    addnchar((uint *)(pcVar2 + iVar3 + -1),(iVar4 - iVar3) + 1);
    closeandpush();
    return;
  }
  lua_pushstring(&DAT_1002bedc);
  return;
}

/* ---- 0x10009650  addnchar ---- */
/* Named addnchar (not in the remaster, gcc inlined it there): Lua 3.1 source name (lstrlib.c static
   addnchar: luaL_openspace, strncpy, luaL_addsize); was str_addnchar. */

void __cdecl addnchar(uint *s,uint n)

{
  uint *puVar1;
  
  puVar1 = (uint *)luaL_openspace(n);
  strncpy(puVar1,s,n);
  luaL_addsize(n);
  return;
}

/* ---- 0x10009680  closeandpush ---- */
/* Named closeandpush (not in the remaster, gcc inlined it there): Lua 3.1 source name (lstrlib.c
   static closeandpush: luaL_addchar(0), lua_pushstring(luaL_buffer())); was str_closeandpush. */

void closeandpush(void)

{
  byte *str;
  
  luaL_addchar(0);
  str = (byte *)luaL_buffer();
  lua_pushstring(str);
  return;
}

/* ---- 0x100096a0  str_lower ---- */
/* Original name str_lower (the remaster's libLua.so: strlib entry 'strlower'); was FUN_100096a0. */

void __cdecl str_lower(void)

{
  byte *pbVar1;
  byte bVar2;
  byte *pbVar3;
  uint uVar4;
  
  luaL_resetbuffer();
  pbVar3 = (byte *)luaL_check_string(1);
  bVar2 = *pbVar3;
  while (bVar2 != 0) {
    uVar4 = tolower((uint)bVar2);
    luaL_addchar((char)uVar4);
    pbVar1 = pbVar3 + 1;
    pbVar3 = pbVar3 + 1;
    bVar2 = *pbVar1;
  }
  closeandpush();
  return;
}

/* ---- 0x100096e0  str_upper ---- */
/* Original name str_upper (the remaster's libLua.so: strlib entry 'strupper'); was FUN_100096e0. */

void __cdecl str_upper(void)

{
  byte *pbVar1;
  byte bVar2;
  byte *pbVar3;
  uint uVar4;
  
  luaL_resetbuffer();
  pbVar3 = (byte *)luaL_check_string(1);
  bVar2 = *pbVar3;
  while (bVar2 != 0) {
    uVar4 = toupper((uint)bVar2);
    luaL_addchar((char)uVar4);
    pbVar1 = pbVar3 + 1;
    pbVar3 = pbVar3 + 1;
    bVar2 = *pbVar1;
  }
  closeandpush();
  return;
}

/* ---- 0x10009720  str_rep ---- */
/* Original name str_rep (the remaster's libLua.so: strlib entry 'strrep'); was FUN_10009720. */

void __cdecl str_rep(void)

{
  uint *s;
  int iVar1;
  longlong lVar2;
  float fVar3;
  
  s = (uint *)luaL_check_string(1);
  fVar3 = luaL_check_number(2);
  lVar2 = FTOL((float10)fVar3);
  iVar1 = (int)lVar2;
  luaL_resetbuffer();
  if (0 < iVar1) {
    do {
      addstr(s);
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  closeandpush();
  return;
}

/* ---- 0x10009760  addstr ---- */
/* Named addstr (not in the remaster, gcc inlined it there): Lua 3.1 source name (lstrlib.c static
   addstr: addnchar(s, strlen(s))); was str_addstr. */

void __cdecl addstr(uint *s)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  
  uVar2 = 0xffffffff;
  puVar3 = s;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    uVar1 = *puVar3;
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((char)uVar1 != '\0');
  addnchar(s,~uVar2 - 1);
  return;
}

/* ---- 0x10009780  str_ascii ---- */
/* Original name str_ascii (the remaster's libLua.so: strlib entry 'ascii'); was FUN_10009780. */

void __cdecl str_ascii(void)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  longlong lVar6;
  float fVar7;
  
  pcVar2 = (char *)luaL_check_string(1);
  fVar7 = luaL_opt_number(2,1.0f);
  lVar6 = FTOL((float10)fVar7);
  uVar4 = (int)lVar6 - 1;
  if (-1 < (int)uVar4) {
    uVar3 = 0xffffffff;
    pcVar5 = pcVar2;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    if (uVar4 < ~uVar3 - 1) goto LAB_100097c8;
  }
  luaL_argerror(2,((unsigned)(uintptr_t)&s_out_of_range_10027970));
LAB_100097c8:
  lua_pushnumber((float)(byte)pcVar2[uVar4]);
  return;
}

/* ---- 0x100097f0  luaI_singlematch ---- */
/* luaI_singlematch: one pattern item against one char Original name luaI_singlematch (the
   remaster's libLua.so: strings "incorrect pattern (ends with `%c')", "incorrect pattern (missing
   `]')"); was str_singlematch. */

uint __cdecl luaI_singlematch(uint c,char *p,int *ep)

{
  char *pcVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  char *pcVar5;
  uint *puVar6;
  uint *puVar7;
  
  switch(*p) {
  case '\0':
    *ep = (int)p;
    return 0;
  default:
    *ep = (int)(p + 1);
    return (uint)((int)*p == c);
  case '%':
    if (p[1] == '\0') {
      luaL_verror(s_incorrect_pattern__ends_with___c_100279a0,0x25);
    }
    *ep = (int)(p + 2);
    uVar3 = matchclass(c,(int)p[1]);
    return uVar3;
  case '.':
    *ep = (int)(p + 1);
    return (uint)(c != 0);
  case '[':
    break;
  }
  pcVar1 = p + 1;
  puVar2 = bracket_end(pcVar1);
  pcVar5 = p;
  if (*pcVar1 == '^') {
    pcVar5 = pcVar1;
  }
  p = (char *)(uint)(*pcVar1 != '^');
  if (puVar2 == (uint *)0x0) {
    lua_error((byte *)s_incorrect_pattern__missing______10027980);
  }
  *ep = (int)puVar2 + 1;
  if (c != 0) {
    puVar6 = (uint *)(pcVar5 + 1);
    if (puVar6 < puVar2) {
      puVar4 = (uint *)(pcVar5 + 3);
      puVar7 = (uint *)(pcVar5 + 2);
      do {
        if ((char)*puVar6 == '%') {
          if (puVar7 < puVar2) {
            pcVar1 = (char *)((int)puVar6 + 1);
            puVar6 = (uint *)((int)puVar6 + 1);
            puVar7 = (uint *)((int)puVar7 + 1);
            puVar4 = (uint *)((int)puVar4 + 1);
            uVar3 = matchclass(c,(int)*pcVar1);
            if (uVar3 != 0) {
              return (uint)p;
            }
          }
        }
        else if (((char)*puVar7 == '-') && (puVar4 < puVar2)) {
          uVar3 = *puVar6;
          puVar6 = (uint *)((int)puVar6 + 2);
          puVar7 = (uint *)((int)puVar7 + 2);
          puVar4 = (uint *)((int)puVar4 + 2);
          if (((int)(char)uVar3 <= (int)c) && ((int)c <= (int)*(char *)puVar6)) {
            return (uint)p;
          }
        }
        else if ((int)(char)*puVar6 == c) {
          return (uint)p;
        }
        puVar6 = (uint *)((int)puVar6 + 1);
        puVar7 = (uint *)((int)puVar7 + 1);
        puVar4 = (uint *)((int)puVar4 + 1);
      } while (puVar6 < puVar2);
    }
    return (uint)(p == (char *)0x0);
  }
  return 0;
}

/* ---- 0x100099e0  bracket_end ---- */
/* Named bracket_end (not in the remaster, gcc inlined it there): Lua 3.1 source name (lstrlib.c
   static bracket_end: strchr for the closing bracket, skipping a leading ^); was str_bracket_end.
    */

uint * __cdecl bracket_end(char *p)

{
  uint *puVar1;
  
  if (*p == '\0') {
    return (uint *)0x0;
  }
  puVar1 = (uint *)(p + 2);
  if (*p != '^') {
    puVar1 = (uint *)(p + 1);
  }
  puVar1 = strchr(puVar1,']');
  return puVar1;
}

/* ---- 0x10009a10  matchclass ---- */
/* %a %d %s ... character classes Original name matchclass (the remaster's libLua.so: static
   matchclass: the only callee of luaI_singlematch (character classes)); was str_matchclass. */

uint __cdecl matchclass(uint c,uint cl)

{
  uint uVar1;
  uint uVar2;
  
  if (c == 0) {
    return 0;
  }
  uVar2 = cl & 0xff;
  uVar1 = tolower(uVar2);
  switch(uVar1) {
  case 0x61:
    if (DAT_10028b5c < 2) {
      uVar1 = *(ushort *)(PTR_DAT_10028950 + (c & 0xff) * 2) & 0x103;
    }
    else {
      uVar1 = _isctype(c & 0xff,0x103);
    }
    break;
  default:
    return (uint)(cl == c);
  case 99:
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(c & 0xff) * 2] & 0x20;
    }
    else {
      uVar1 = _isctype(c & 0xff,0x20);
    }
    break;
  case 100:
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(c & 0xff) * 2] & 4;
    }
    else {
      uVar1 = _isctype(c & 0xff,4);
    }
    break;
  case 0x6c:
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(c & 0xff) * 2] & 2;
    }
    else {
      uVar1 = _isctype(c & 0xff,2);
    }
    break;
  case 0x70:
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(c & 0xff) * 2] & 0x10;
    }
    else {
      uVar1 = _isctype(c & 0xff,0x10);
    }
    break;
  case 0x73:
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(c & 0xff) * 2] & 8;
    }
    else {
      uVar1 = _isctype(c & 0xff,8);
    }
    break;
  case 0x75:
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(c & 0xff) * 2] & 1;
    }
    else {
      uVar1 = _isctype(c & 0xff,1);
    }
    break;
  case 0x77:
    if (DAT_10028b5c < 2) {
      uVar1 = *(ushort *)(PTR_DAT_10028950 + (c & 0xff) * 2) & 0x107;
    }
    else {
      uVar1 = _isctype(c & 0xff,0x107);
    }
  }
  if (DAT_10028b5c < 2) {
    uVar2 = (byte)PTR_DAT_10028950[uVar2 * 2] & 2;
  }
  else {
    uVar2 = _isctype(uVar2,2);
  }
  if (uVar2 != 0) {
    return uVar1;
  }
  return (uint)(uVar1 == 0);
}

/* ---- 0x10009cb0  str_find ---- */
/* Original name str_find (the remaster's libLua.so: strlib entry 'strfind'); was FUN_10009cb0. */

void __cdecl str_find(void)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  byte bVar2;
  char *pcVar3;
  byte *pat;
  int iVar4;
  byte *pbVar5;
  char *pcVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  longlong lVar11;
  float fVar12;
  #define aiStack_4c (*(int (*)[19])(_frame + (0x60 - 0x4c)))
  
  pcVar3 = (char *)luaL_check_string(1);
  pat = (byte *)luaL_check_string(2);
  fVar12 = luaL_opt_number(3,1.0f);
  lVar11 = FTOL((float10)fVar12);
  uVar9 = (int)lVar11 - 1;
  if (-1 < (int)uVar9) {
    uVar8 = 0xffffffff;
    pcVar10 = pcVar3;
    do {
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar10 + 1;
    } while (cVar1 != '\0');
    if (uVar9 <= ~uVar8 - 1) goto LAB_10009d07;
  }
  luaL_argerror(3,((unsigned)(uintptr_t)&s_out_of_range_10027970));
LAB_10009d07:
  iVar4 = lua_lua2C(4);
  if ((iVar4 == 0) && (pbVar5 = strpbrk(pat,(byte *)s___________100279c4), pbVar5 != (byte *)0x0)) {
    bVar2 = *pat;
    if (bVar2 == 0x5e) {
      pat = pat + 1;
    }
    pcVar10 = pcVar3 + uVar9;
    aiStack_4c[0] = 0;
    pcVar6 = match(pcVar10,(int *)pat,aiStack_4c);
    while( true ) {
      if (pcVar6 != (char *)0x0) {
        lua_pushnumber((float)(int)(pcVar10 + (1 - (int)pcVar3)));
        lua_pushnumber((float)((int)pcVar6 - (int)pcVar3));
        push_captures(aiStack_4c);
        return;
      }
      cVar1 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      if ((cVar1 == '\0') || (bVar2 == 0x5e)) break;
      aiStack_4c[0] = 0;
      pcVar6 = match(pcVar10,(int *)pat,aiStack_4c);
    }
  }
  else {
    puVar7 = FUN_100129a0((uint *)(pcVar3 + uVar9),(char *)pat);
    if (puVar7 != (uint *)0x0) {
      lua_pushnumber((float)((int)puVar7 + (1 - (int)pcVar3)));
      uVar9 = 0xffffffff;
      do {
        if (uVar9 == 0) break;
        uVar9 = uVar9 - 1;
        bVar2 = *pat;
        pat = pat + 1;
      } while (bVar2 != 0);
      lua_pushnumber((float)((int)puVar7 + ((~uVar9 - 1) - (int)pcVar3)));
    }
  }
  return;
}
#undef aiStack_4c


/* ---- 0x10009e40  push_captures ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* errors 'unfinished capture' Named push_captures (not in the remaster, gcc inlined it there): Lua
   3.1 source name (lstrlib.c static push_captures: each capture as a string, error "unfinished
   capture"); was str_push_captures. */

void __cdecl push_captures(int *ms)

{
  uint uVar1;
  uint *str;
  int *piVar2;
  int iVar3;
  int *in_stack_00000008;
  
  iVar3 = 0;
  if (0 < *ms) {
    piVar2 = ms + 1;
    do {
      uVar1 = piVar2[1];
      str = (uint *)luaL_openspace(uVar1 + 1);
      if (uVar1 == 0xffffffff) {
        lua_error((byte *)s_unfinished_capture_100279d0);
      }
      strncpy(str,(uint *)*piVar2,uVar1);
      *(undefined1 *)((int)str + uVar1) = 0;
      lua_pushstring((byte *)str);
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 2;
    } while (iVar3 < *in_stack_00000008);
  }
  return;
}
#endif


/* ---- 0x10009ea0  match ---- */
/* recursive pattern matcher; errors 'too many captures' Original name match (the remaster's
   libLua.so: static match: string 'too many captures'); was str_match. */

char * __cdecl match(char *s,int *pat,int *cap)

{
  char cVar1;
  int *cap_00;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  
  cap_00 = cap;
  do {
    while( true ) {
      switch((int)((char)*pat)) {
      case '\0':
      case '$':
        if (((char)*pat == '\0') || ((*(char *)((int)pat + 1) == '\0' && (*s == '\0')))) {
          return s;
        }
        break;
      case '(':
        if (8 < *cap_00) {
          lua_error((byte *)s_too_many_captures_100279e4);
        }
        cap_00[*cap_00 * 2 + 1] = (int)s;
        cap_00[*cap_00 * 2 + 2] = -1;
        *cap_00 = *cap_00 + 1;
        pcVar2 = match(s,(int *)((int)pat + 1),cap_00);
        if (pcVar2 != (char *)0x0) {
          return pcVar2;
        }
        *cap_00 = *cap_00 + -1;
        return (char *)0x0;
      case ')':
        iVar4 = capture_to_close(cap_00);
        cap_00[iVar4 * 2 + 2] = (int)s - cap_00[iVar4 * 2 + 1];
        pcVar2 = match(s,(int *)((int)pat + 1),cap_00);
        if (pcVar2 != (char *)0x0) {
          return pcVar2;
        }
        cap_00[iVar4 * 2 + 2] = -1;
        return (char *)0x0;
      }
      pcVar2 = matchitem(s,(char *)pat,cap_00,(int *)&cap);
      cVar1 = (char)*cap;
      if (cVar1 != '*') break;
      if (pcVar2 != (char *)0x0) {
LAB_10009f49:
        pcVar2 = match(pcVar2,pat,cap_00);
        if (pcVar2 != (char *)0x0) {
          return pcVar2;
        }
      }
LAB_10009f5e:
      pat = (int *)((int)cap + 1);
    }
    if (cVar1 == '-') {
      pcVar3 = match(s,(int *)((int)cap + 1),cap_00);
      if (pcVar3 != (char *)0x0) {
        return pcVar3;
      }
    }
    else {
      pat = cap;
      if (cVar1 == '?') {
        if (pcVar2 != (char *)0x0) {
          pat = (int *)((int)cap + 1);
          goto LAB_10009f49;
        }
        goto LAB_10009f5e;
      }
    }
    s = pcVar2;
    if (pcVar2 == (char *)0x0) {
      return (char *)0x0;
    }
  } while( true );
}

/* ---- 0x1000a030  capture_to_close ---- */
/* Named capture_to_close (not in the remaster, gcc inlined it there): Lua 3.1 source name
   (lstrlib.c static capture_to_close: the last open capture (len -1), error "invalid pattern
   capture"); was str_capture_to_close. */

int __cdecl capture_to_close(int *cap)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *cap + -1;
  if (-1 < iVar1) {
    piVar2 = cap + iVar1 * 2 + 2;
    do {
      if (*piVar2 == -1) {
        return iVar1;
      }
      iVar1 = iVar1 + -1;
      piVar2 = piVar2 + -2;
    } while (-1 < iVar1);
  }
  lua_error((byte *)s_invalid_pattern_capture_100279f8);
  return 0;
}

/* ---- 0x1000a060  matchitem ---- */
/* errors 'unbalanced pattern' Named matchitem (not in the remaster, gcc inlined it there): Lua 3.1
   source name (lstrlib.c static matchitem: %digit compares a capture (check_cap), %b calls
   matchbalance with error "unbalanced pattern", else luaI_singlematch); was str_matchbalance. */

char * __cdecl matchitem(char *s,char *p,int *cap,int *ep)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  byte *pbVar4;
  
  if (*p == '%') {
    pbVar4 = (byte *)(p + 1);
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(uint)*pbVar4 * 2] & 4;
    }
    else {
      uVar1 = _isctype((uint)*pbVar4,4);
    }
    if (uVar1 != 0) {
      iVar2 = check_cap((int)(char)*pbVar4,cap);
      *ep = (int)(p + 2);
      uVar1 = strncmp((char *)cap[iVar2 * 2 + 1],s,cap[iVar2 * 2 + 2]);
      if (uVar1 != 0) {
        return (char *)0x0;
      }
      return s + cap[iVar2 * 2 + 2];
    }
    if (*pbVar4 == 0x62) {
      if ((p[2] == '\0') || (p[3] == '\0')) {
        lua_error((byte *)s_unbalanced_pattern_10027a10);
      }
      *ep = (int)(p + 4);
      pcVar3 = matchbalance(s,(int)p[2],(int)p[3]);
      return pcVar3;
    }
  }
  uVar1 = luaI_singlematch((int)*s,p,ep);
  if (uVar1 == 0) {
    return (char *)0x0;
  }
  return s + 1;
}

/* ---- 0x1000a150  check_cap ---- */
/* errors 'invalid capture index' Named check_cap (not in the remaster, gcc inlined it there): Lua
   3.1 source name (lstrlib.c static check_cap: l = c - '1', error "invalid capture index"); was
   str_check_capture. */

int __cdecl check_cap(int l,int *cap)

{
  int iVar1;
  
  iVar1 = l + -0x31;
  if (((iVar1 < 0) || (*cap <= iVar1)) || (cap[iVar1 * 2 + 2] == -1)) {
    lua_error((byte *)s_invalid_capture_index_10027a24);
  }
  return iVar1;
}

/* ---- 0x1000a180  matchbalance ---- */
/* max/min expansion of a repeated pattern item Named matchbalance (not in the remaster, gcc inlined
   it there): Lua 3.1 source name (lstrlib.c static matchbalance(s, b, e): counts nested b / e and
   returns the position after the balancing e; called by matchitem for %b); was str_expand. */

char * __cdecl matchbalance(char *s,int b,int e)

{
  char cVar1;
  int iVar2;
  
  if (*s == b) {
    cVar1 = s[1];
    iVar2 = 1;
    if (cVar1 != '\0') {
      do {
        if (cVar1 == e) {
          iVar2 = iVar2 + -1;
          if (iVar2 == 0) {
            return s + 2;
          }
        }
        else if (cVar1 == b) {
          iVar2 = iVar2 + 1;
        }
        cVar1 = s[2];
        s = s + 1;
      } while (cVar1 != '\0');
      return (char *)0x0;
    }
  }
  return (char *)0x0;
}

/* ---- 0x1000a1d0  str_gsub ---- */
/* Original name str_gsub (the remaster's libLua.so: strlib entry 'gsub'); was FUN_1000a1d0. */

void __cdecl str_gsub(void)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *s;
  int *pat;
  int newp;
  uint *puVar2;
  uint uVar3;
  bool bVar4;
  longlong lVar5;
  float fVar6;
  int iStack_60;
  #define aiStack_4c (*(int (*)[19])(_frame + (0x60 - 0x4c)))
  
  s = (uint *)luaL_check_string(1);
  pat = (int *)luaL_check_string(2);
  newp = lua_lua2C(3);
  uVar3 = 0xffffffff;
  puVar2 = s;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
  fVar6 = luaL_opt_number(4,(float)~uVar3);
  lVar5 = FTOL((float10)fVar6);
  bVar4 = (char)*pat == '^';
  if (bVar4) {
    pat = (int *)((int)pat + 1);
  }
  iStack_60 = 0;
  luaL_resetbuffer();
  if ((int)lVar5 < 1) {
LAB_1000a2b7:
    addstr(s);
    closeandpush();
    lua_pushnumber((float)iStack_60);
    return;
  }
  do {
    aiStack_4c[0] = 0;
    puVar2 = (uint *)match((char *)s,pat,aiStack_4c);
    if (puVar2 == (uint *)0x0) {
LAB_1000a291:
      if ((char)*s == '\0') goto LAB_1000a2b7;
      puVar2 = (uint *)((int)s + 1);
      luaL_addchar((char)*s);
    }
    else {
      iStack_60 = iStack_60 + 1;
      add_s(newp,aiStack_4c);
      if ((puVar2 == (uint *)0x0) || (puVar2 <= s)) goto LAB_1000a291;
    }
    s = puVar2;
    if ((bVar4) || ((int)lVar5 <= iStack_60)) goto LAB_1000a2b7;
  } while( true );
}
#undef aiStack_4c


/* ---- 0x1000a2e0  add_s ---- */
/* gsub replacement: string or function result Named add_s (not in the remaster, gcc inlined it
   there): Lua 3.1 source name (lstrlib.c static add_s(newp, cap): gsub's replacement, a string with
   %n captures or a function called with push_captures; error "string or function expected"); was
   str_add_value. */

void __cdecl add_s(int newp,int *ms)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  uint *s;
  char *pcVar6;
  
  iVar2 = lua_isstring(newp);
  if (iVar2 == 0) {
    iVar2 = lua_isfunction(newp);
    if (iVar2 != 0) {
      lua_beginblock();
      push_captures(ms);
      iVar2 = luaL_newbuffer(0);
      iVar5 = lua_callfunction(newp);
      luaL_oldbuffer(iVar2);
      if (iVar5 != 0) {
        lua_endblock();
        lua_error((byte *)0x0);
      }
      iVar2 = lua_lua2C(1);
      iVar5 = lua_isstring(iVar2);
      if (iVar5 == 0) {
        addstr((uint *)&DAT_1002bedc);
        lua_endblock();
        return;
      }
      s = (uint *)lua_getstring(iVar2);
      addstr(s);
      lua_endblock();
      return;
    }
    luaL_argerror(3,((unsigned)(uintptr_t)&s_string_or_function_expected_10027a3c));
  }
  else {
    pcVar3 = (char *)lua_getstring(newp);
    cVar1 = *pcVar3;
    if (cVar1 != '\0') {
      do {
        pcVar6 = pcVar3;
        if (cVar1 == '%') {
          if (DAT_10028b5c < 2) {
            uVar4 = (byte)PTR_DAT_10028950[(uint)(byte)pcVar3[1] * 2] & 4;
          }
          else {
            uVar4 = _isctype((uint)(byte)pcVar3[1],4);
          }
          pcVar6 = pcVar3 + 1;
          if (uVar4 == 0) goto LAB_1000a36b;
          pcVar3 = pcVar3 + 2;
          iVar2 = check_cap((int)*pcVar6,ms);
          addnchar((uint *)ms[iVar2 * 2 + 1],ms[iVar2 * 2 + 2]);
        }
        else {
LAB_1000a36b:
          pcVar3 = pcVar6 + 1;
          luaL_addchar(*pcVar6);
        }
        cVar1 = *pcVar3;
        if (cVar1 == '\0') {
          return;
        }
      } while( true );
    }
  }
  return;
}

/* ---- 0x1000a440  str_format ---- */
/* Original name str_format (the remaster's libLua.so: strlib entry 'format'); was FUN_1000a440. */

void __cdecl str_format(void)

{
  unsigned char _frame[0x130] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  char *buf;
  char *a2;
  int numArg;
  uint *s;
  longlong lVar5;
  float fVar6;
  #define aiStack_114 (*(int (*)[2])(_frame + (0x130 - 0x114)))
  #define iStack_10c (*(int *)(_frame + (0x130 - 0x10c)))
  #define iStack_104 (*(int *)(_frame + (0x130 - 0x104)))
  #define cStack_c8 (*(char *)(_frame + (0x130 - 0xc8)))
  #define uStack_c7 (*(char (*)[199])(_frame + (0x130 - 0xc7)))
  
  numArg = 1;
  pcVar2 = (char *)luaL_check_string(1);
  luaL_resetbuffer();
  cVar1 = *pcVar2;
  do {
    if (cVar1 == '\0') {
      closeandpush();
      return;
    }
    if (cVar1 == '%') {
      s = (uint *)(pcVar2 + 1);
      if (pcVar2[1] == '%') {
        pcVar2 = pcVar2 + 2;
        luaL_addchar(0x25);
      }
      else {
        cStack_c8 = '%';
        aiStack_114[0] = 0;
        pcVar3 = match((char *)s,(int *)s__d_____________d_______d___10027aa4,aiStack_114);
        if ((3 < iStack_10c) || (3 < iStack_104)) {
          lua_error((byte *)s_invalid_format__width_or_precisi_10027a74);
        }
        if (DAT_10028b5c < 2) {
          uVar4 = (byte)PTR_DAT_10028950[(uint)(byte)*s * 2] & 4;
        }
        else {
          uVar4 = _isctype((uint)(byte)*s,4);
        }
        if ((uVar4 != 0) && (pcVar2[2] == '$')) {
          numArg = (char)(byte)*s + -0x30;
          s = (uint *)(pcVar2 + 3);
        }
        numArg = numArg + 1;
        strncpy((uint *)uStack_c7,s,(uint)(pcVar3 + (1 - (int)s)));
        pcVar3[(int)(uStack_c7 + (1 - (int)s))] = '\0';
        buf = (char *)luaL_openspace(1000);
        pcVar2 = pcVar3 + 1;
        switch(*pcVar3) {
        case 'E':
        case 'G':
        case 'e':
        case 'f':
        case 'g':
          fVar6 = luaL_check_number(numArg);
          sprintf(buf,&cStack_c8,(double)fVar6);
          break;
        default:
          lua_error((byte *)s_invalid_option_in__format__10027a58);
          break;
        case 'X':
        case 'c':
        case 'd':
        case 'i':
        case 'o':
        case 'u':
        case 'x':
          fVar6 = luaL_check_number(numArg);
          lVar5 = FTOL((float10)fVar6);
          sprintf(buf,&cStack_c8,(int)lVar5);
          break;
        case 'q':
          pcVar3 = (char *)luaL_check_string(numArg);
          luaI_addquoted(pcVar3);
          goto LAB_1000a5fe;
        case 's':
          a2 = (char *)luaL_check_string(numArg);
          uVar4 = 0xffffffff;
          pcVar3 = a2;
          do {
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            cVar1 = *pcVar3;
            pcVar3 = pcVar3 + 1;
          } while (cVar1 != '\0');
          buf = (char *)luaL_openspace(~uVar4 - 1);
          sprintf(buf,&cStack_c8,a2);
        }
        uVar4 = 0xffffffff;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *buf;
          buf = buf + 1;
        } while (cVar1 != '\0');
        luaL_addsize(~uVar4 - 1);
      }
    }
    else {
      pcVar2 = pcVar2 + 1;
      luaL_addchar(cVar1);
    }
LAB_1000a5fe:
    cVar1 = *pcVar2;
  } while( true );
}
#undef aiStack_114
#undef cStack_c8
#undef iStack_104
#undef iStack_10c
#undef uStack_c7


/* ---- 0x1000a680  luaI_addquoted ---- */
/* gsub replacement string with %n captures Named luaI_addquoted (not in the remaster, gcc inlined
   it there): Lua 3.1 source name (lstrlib.c luaI_addquoted: format %q, the string in double quotes
   with a backslash before the special characters; called by str_format); was str_add_s. */

void __cdecl luaI_addquoted(char *s)

{
  char *pcVar1;
  char cVar2;
  uint *puVar3;
  
  luaL_addchar(0x22);
  cVar2 = *s;
  while (cVar2 != '\0') {
    puVar3 = strchr((uint *)&DAT_10027ac0,cVar2);
    if (puVar3 != (uint *)0x0) {
      luaL_addchar(0x5c);
    }
    luaL_addchar(*s);
    pcVar1 = s + 1;
    s = s + 1;
    cVar2 = *pcVar1;
  }
  luaL_addchar(0x22);
  return;
}
