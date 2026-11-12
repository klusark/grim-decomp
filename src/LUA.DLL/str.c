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
  lVar8 = FTOL(luaL_check_number(2));
  iVar3 = (int)lVar8;
  lVar8 = FTOL(luaL_opt_number(3,-1.0));
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

void __cdecl addnchar(uint *param_1,uint param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)luaL_openspace(param_2);
  strncpy(puVar1,param_1,param_2);
  luaL_addsize(param_2);
  return;
}

/* ---- 0x10009680  closeandpush ---- */
/* Named closeandpush (not in the remaster, gcc inlined it there): Lua 3.1 source name (lstrlib.c
   static closeandpush: luaL_addchar(0), lua_pushstring(luaL_buffer())); was str_closeandpush. */

void closeandpush(void)

{
  byte *pbVar1;
  
  luaL_addchar(0);
  pbVar1 = (byte *)luaL_buffer();
  lua_pushstring(pbVar1);
  return;
}

/* ---- 0x100096a0  str_lower ---- */
/* Original name str_lower (the remaster's libLua.so: strlib entry 'strlower'); was FUN_100096a0. */

void str_lower(void)

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

void str_upper(void)

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

void str_rep(void)

{
  uint *puVar1;
  int iVar2;
  longlong lVar3;
  
  puVar1 = (uint *)luaL_check_string(1);
  lVar3 = FTOL(luaL_check_number(2));
  iVar2 = (int)lVar3;
  luaL_resetbuffer();
  if (0 < iVar2) {
    do {
      addstr(puVar1);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  closeandpush();
  return;
}

/* ---- 0x10009760  addstr ---- */
/* Named addstr (not in the remaster, gcc inlined it there): Lua 3.1 source name (lstrlib.c static
   addstr: addnchar(s, strlen(s))); was str_addstr. */

void __cdecl addstr(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  
  uVar2 = 0xffffffff;
  puVar3 = param_1;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    uVar1 = *puVar3;
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((char)uVar1 != '\0');
  addnchar(param_1,~uVar2 - 1);
  return;
}

/* ---- 0x10009780  str_ascii ---- */
/* Original name str_ascii (the remaster's libLua.so: strlib entry 'ascii'); was FUN_10009780. */

void str_ascii(void)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  longlong lVar6;
  
  pcVar2 = (char *)luaL_check_string(1);
  lVar6 = FTOL(luaL_opt_number(2,1.0));
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

uint __cdecl luaI_singlematch(uint param_1,char *param_2,int *param_3)

{
  char *pcVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  char *pcVar5;
  uint *puVar6;
  uint *puVar7;
  
  switch(*param_2) {
  case '\0':
    *param_3 = (int)param_2;
    return 0;
  default:
    *param_3 = (int)(param_2 + 1);
    return (uint)((int)*param_2 == param_1);
  case '%':
    if (param_2[1] == '\0') {
      luaL_verror(s_incorrect_pattern__ends_with___c_100279a0,0x25);
    }
    *param_3 = (int)(param_2 + 2);
    uVar3 = matchclass(param_1,(int)param_2[1]);
    return uVar3;
  case '.':
    *param_3 = (int)(param_2 + 1);
    return (uint)(param_1 != 0);
  case '[':
    break;
  }
  pcVar1 = param_2 + 1;
  puVar2 = bracket_end(pcVar1);
  pcVar5 = param_2;
  if (*pcVar1 == '^') {
    pcVar5 = pcVar1;
  }
  param_2 = (char *)(uint)(*pcVar1 != '^');
  if (puVar2 == (uint *)0x0) {
    lua_error((byte *)s_incorrect_pattern__missing______10027980);
  }
  *param_3 = (int)puVar2 + 1;
  if (param_1 != 0) {
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
            uVar3 = matchclass(param_1,(int)*pcVar1);
            if (uVar3 != 0) {
              return (uint)param_2;
            }
          }
        }
        else if (((char)*puVar7 == '-') && (puVar4 < puVar2)) {
          uVar3 = *puVar6;
          puVar6 = (uint *)((int)puVar6 + 2);
          puVar7 = (uint *)((int)puVar7 + 2);
          puVar4 = (uint *)((int)puVar4 + 2);
          if (((int)(char)uVar3 <= (int)param_1) && ((int)param_1 <= (int)*(char *)puVar6)) {
            return (uint)param_2;
          }
        }
        else if ((int)(char)*puVar6 == param_1) {
          return (uint)param_2;
        }
        puVar6 = (uint *)((int)puVar6 + 1);
        puVar7 = (uint *)((int)puVar7 + 1);
        puVar4 = (uint *)((int)puVar4 + 1);
      } while (puVar6 < puVar2);
    }
    return (uint)(param_2 == (char *)0x0);
  }
  return 0;
}

/* ---- 0x100099e0  bracket_end ---- */
/* Named bracket_end (not in the remaster, gcc inlined it there): Lua 3.1 source name (lstrlib.c
   static bracket_end: strchr for the closing bracket, skipping a leading ^); was str_bracket_end.
    */

uint * __cdecl bracket_end(char *param_1)

{
  uint *puVar1;
  
  if (*param_1 == '\0') {
    return (uint *)0x0;
  }
  puVar1 = (uint *)(param_1 + 2);
  if (*param_1 != '^') {
    puVar1 = (uint *)(param_1 + 1);
  }
  puVar1 = strchr(puVar1,']');
  return puVar1;
}

/* ---- 0x10009a10  matchclass ---- */
/* %a %d %s ... character classes Original name matchclass (the remaster's libLua.so: static
   matchclass: the only callee of luaI_singlematch (character classes)); was str_matchclass. */

uint __cdecl matchclass(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar2 = param_2 & 0xff;
  uVar1 = tolower(uVar2);
  switch(uVar1) {
  case 0x61:
    if (DAT_10028b5c < 2) {
      uVar1 = *(ushort *)(PTR_DAT_10028950 + (param_1 & 0xff) * 2) & 0x103;
    }
    else {
      uVar1 = _isctype(param_1 & 0xff,0x103);
    }
    break;
  default:
    return (uint)(param_2 == param_1);
  case 99:
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(param_1 & 0xff) * 2] & 0x20;
    }
    else {
      uVar1 = _isctype(param_1 & 0xff,0x20);
    }
    break;
  case 100:
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(param_1 & 0xff) * 2] & 4;
    }
    else {
      uVar1 = _isctype(param_1 & 0xff,4);
    }
    break;
  case 0x6c:
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(param_1 & 0xff) * 2] & 2;
    }
    else {
      uVar1 = _isctype(param_1 & 0xff,2);
    }
    break;
  case 0x70:
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(param_1 & 0xff) * 2] & 0x10;
    }
    else {
      uVar1 = _isctype(param_1 & 0xff,0x10);
    }
    break;
  case 0x73:
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(param_1 & 0xff) * 2] & 8;
    }
    else {
      uVar1 = _isctype(param_1 & 0xff,8);
    }
    break;
  case 0x75:
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(param_1 & 0xff) * 2] & 1;
    }
    else {
      uVar1 = _isctype(param_1 & 0xff,1);
    }
    break;
  case 0x77:
    if (DAT_10028b5c < 2) {
      uVar1 = *(ushort *)(PTR_DAT_10028950 + (param_1 & 0xff) * 2) & 0x107;
    }
    else {
      uVar1 = _isctype(param_1 & 0xff,0x107);
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

void str_find(void)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  byte bVar2;
  char *pcVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  char *pcVar7;
  uint *puVar8;
  uint uVar9;
  uint uVar10;
  char *pcVar11;
  longlong lVar12;
  #define aiStack_4c (*(int (*)[19])(_frame + (0x60 - 0x4c)))
  
  pcVar3 = (char *)luaL_check_string(1);
  pbVar4 = (byte *)luaL_check_string(2);
  lVar12 = FTOL(luaL_opt_number(3,1.0));
  uVar10 = (int)lVar12 - 1;
  if (-1 < (int)uVar10) {
    uVar9 = 0xffffffff;
    pcVar11 = pcVar3;
    do {
      if (uVar9 == 0) break;
      uVar9 = uVar9 - 1;
      cVar1 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar1 != '\0');
    if (uVar10 <= ~uVar9 - 1) goto LAB_10009d07;
  }
  luaL_argerror(3,((unsigned)(uintptr_t)&s_out_of_range_10027970));
LAB_10009d07:
  iVar5 = lua_lua2C(4);
  if ((iVar5 == 0) && (pbVar6 = strpbrk(pbVar4,(byte *)s___________100279c4), pbVar6 != (byte *)0x0)
     ) {
    bVar2 = *pbVar4;
    if (bVar2 == 0x5e) {
      pbVar4 = pbVar4 + 1;
    }
    pcVar11 = pcVar3 + uVar10;
    aiStack_4c[0] = 0;
    pcVar7 = match(pcVar11,(int *)pbVar4,aiStack_4c);
    while( true ) {
      if (pcVar7 != (char *)0x0) {
        lua_pushnumber((float)(int)(pcVar11 + (1 - (int)pcVar3)));
        lua_pushnumber((float)((int)pcVar7 - (int)pcVar3));
        push_captures(aiStack_4c);
        return;
      }
      cVar1 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      if ((cVar1 == '\0') || (bVar2 == 0x5e)) break;
      aiStack_4c[0] = 0;
      pcVar7 = match(pcVar11,(int *)pbVar4,aiStack_4c);
    }
  }
  else {
    puVar8 = FUN_100129a0((uint *)(pcVar3 + uVar10),(char *)pbVar4);
    if (puVar8 != (uint *)0x0) {
      lua_pushnumber((float)((int)puVar8 + (1 - (int)pcVar3)));
      uVar10 = 0xffffffff;
      do {
        if (uVar10 == 0) break;
        uVar10 = uVar10 - 1;
        bVar2 = *pbVar4;
        pbVar4 = pbVar4 + 1;
      } while (bVar2 != 0);
      lua_pushnumber((float)((int)puVar8 + ((~uVar10 - 1) - (int)pcVar3)));
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
  uint *puVar2;
  int *piVar3;
  int iVar4;
  int *in_stack_00000008;
  
  iVar4 = 0;
  if (0 < *ms) {
    piVar3 = ms + 1;
    do {
      uVar1 = piVar3[1];
      puVar2 = (uint *)luaL_openspace(uVar1 + 1);
      if (uVar1 == 0xffffffff) {
        lua_error((byte *)s_unfinished_capture_100279d0);
      }
      strncpy(puVar2,(uint *)*piVar3,uVar1);
      *(undefined1 *)((int)puVar2 + uVar1) = 0;
      lua_pushstring((byte *)puVar2);
      iVar4 = iVar4 + 1;
      piVar3 = piVar3 + 2;
    } while (iVar4 < *in_stack_00000008);
  }
  return;
}
#endif


/* ---- 0x10009ea0  match ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* recursive pattern matcher; errors 'too many captures' Original name match (the remaster's
   libLua.so: static match: string 'too many captures'); was str_match. */

char * __cdecl match(char *param_1,int *param_2,int *param_3)

{
  char cVar1;
  int *piVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  
  piVar2 = param_3;
  do {
    while( true ) {
      switch((int)((char)*param_2)) {
      case '\0':
      case '$':
        if (((char)*param_2 == '\0') ||
           ((*(char *)((int)param_2 + 1) == '\0' && (*param_1 == '\0')))) {
          return param_1;
        }
        break;
      case '(':
        if (8 < *piVar2) {
          lua_error((byte *)s_too_many_captures_100279e4);
        }
        piVar2[*piVar2 * 2 + 1] = (int)param_1;
        piVar2[*piVar2 * 2 + 2] = -1;
        *piVar2 = *piVar2 + 1;
        pcVar3 = match(param_1,(int *)((int)param_2 + 1),piVar2);
        if (pcVar3 != (char *)0x0) {
          return pcVar3;
        }
        *piVar2 = *piVar2 + -1;
        return (char *)0x0;
      case ')':
        iVar5 = capture_to_close(piVar2);
        piVar2[iVar5 * 2 + 2] = (int)param_1 - piVar2[iVar5 * 2 + 1];
        pcVar3 = match(param_1,(int *)((int)param_2 + 1),piVar2);
        if (pcVar3 != (char *)0x0) {
          return pcVar3;
        }
        piVar2[iVar5 * 2 + 2] = -1;
        return (char *)0x0;
      }
      pcVar3 = matchitem(param_1,(char *)param_2,piVar2,(int *)&param_3);
      cVar1 = (char)*param_3;
      if (cVar1 != '*') break;
      if (pcVar3 != (char *)0x0) {
LAB_10009f49:
        pcVar3 = match(pcVar3,param_2,piVar2);
        if (pcVar3 != (char *)0x0) {
          return pcVar3;
        }
      }
LAB_10009f5e:
      param_2 = (int *)((int)param_3 + 1);
    }
    if (cVar1 == '-') {
      pcVar4 = match(param_1,(int *)((int)param_3 + 1),piVar2);
      if (pcVar4 != (char *)0x0) {
        return pcVar4;
      }
    }
    else {
      param_2 = param_3;
      if (cVar1 == '?') {
        if (pcVar3 != (char *)0x0) {
          param_2 = (int *)((int)param_3 + 1);
          goto LAB_10009f49;
        }
        goto LAB_10009f5e;
      }
    }
    param_1 = pcVar3;
    if (pcVar3 == (char *)0x0) {
      return (char *)0x0;
    }
  } while( true );
}
#endif


/* ---- 0x1000a030  capture_to_close ---- */
/* Named capture_to_close (not in the remaster, gcc inlined it there): Lua 3.1 source name
   (lstrlib.c static capture_to_close: the last open capture (len -1), error "invalid pattern
   capture"); was str_capture_to_close. */

int __cdecl capture_to_close(int *param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *param_1 + -1;
  if (-1 < iVar1) {
    piVar2 = param_1 + iVar1 * 2 + 2;
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

char * __cdecl matchitem(char *param_1,char *param_2,int *param_3,int *param_4)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  byte *pbVar4;
  
  if (*param_2 == '%') {
    pbVar4 = (byte *)(param_2 + 1);
    if (DAT_10028b5c < 2) {
      uVar1 = (byte)PTR_DAT_10028950[(uint)*pbVar4 * 2] & 4;
    }
    else {
      uVar1 = _isctype((uint)*pbVar4,4);
    }
    if (uVar1 != 0) {
      iVar2 = check_cap((int)(char)*pbVar4,param_3);
      *param_4 = (int)(param_2 + 2);
      uVar1 = strncmp((char *)param_3[iVar2 * 2 + 1],param_1,param_3[iVar2 * 2 + 2]);
      if (uVar1 != 0) {
        return (char *)0x0;
      }
      return param_1 + param_3[iVar2 * 2 + 2];
    }
    if (*pbVar4 == 0x62) {
      if ((param_2[2] == '\0') || (param_2[3] == '\0')) {
        lua_error((byte *)s_unbalanced_pattern_10027a10);
      }
      *param_4 = (int)(param_2 + 4);
      pcVar3 = matchbalance(param_1,(int)param_2[2],(int)param_2[3]);
      return pcVar3;
    }
  }
  uVar1 = luaI_singlematch((int)*param_1,param_2,param_4);
  if (uVar1 == 0) {
    return (char *)0x0;
  }
  return param_1 + 1;
}

/* ---- 0x1000a150  check_cap ---- */
/* errors 'invalid capture index' Named check_cap (not in the remaster, gcc inlined it there): Lua
   3.1 source name (lstrlib.c static check_cap: l = c - '1', error "invalid capture index"); was
   str_check_capture. */

int __cdecl check_cap(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x31;
  if (((iVar1 < 0) || (*param_2 <= iVar1)) || (param_2[iVar1 * 2 + 2] == -1)) {
    lua_error((byte *)s_invalid_capture_index_10027a24);
  }
  return iVar1;
}

/* ---- 0x1000a180  matchbalance ---- */
/* max/min expansion of a repeated pattern item Named matchbalance (not in the remaster, gcc inlined
   it there): Lua 3.1 source name (lstrlib.c static matchbalance(s, b, e): counts nested b / e and
   returns the position after the balancing e; called by matchitem for %b); was str_expand. */

char * __cdecl matchbalance(char *param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  
  if (*param_1 == param_2) {
    cVar1 = param_1[1];
    iVar2 = 1;
    if (cVar1 != '\0') {
      do {
        if (cVar1 == param_3) {
          iVar2 = iVar2 + -1;
          if (iVar2 == 0) {
            return param_1 + 2;
          }
        }
        else if (cVar1 == param_2) {
          iVar2 = iVar2 + 1;
        }
        cVar1 = param_1[2];
        param_1 = param_1 + 1;
      } while (cVar1 != '\0');
      return (char *)0x0;
    }
  }
  return (char *)0x0;
}

/* ---- 0x1000a1d0  str_gsub ---- */
/* Original name str_gsub (the remaster's libLua.so: strlib entry 'gsub'); was FUN_1000a1d0. */

void str_gsub(void)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  int *piVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  bool bVar7;
  longlong lVar8;
  #define iStack_60 (*(int *)(_frame + (0x70 - 0x60)))
  #define aiStack_4c (*(int (*)[19])(_frame + (0x70 - 0x4c)))
  
  puVar2 = (uint *)luaL_check_string(1);
  piVar3 = (int *)luaL_check_string(2);
  iVar4 = lua_lua2C(3);
  uVar6 = 0xffffffff;
  puVar5 = puVar2;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    uVar1 = *puVar5;
    puVar5 = (uint *)((int)puVar5 + 1);
  } while ((char)uVar1 != '\0');
  lVar8 = FTOL(luaL_opt_number(4,(float)~uVar6));
  bVar7 = (char)*piVar3 == '^';
  if (bVar7) {
    piVar3 = (int *)((int)piVar3 + 1);
  }
  iStack_60 = 0;
  luaL_resetbuffer();
  if ((int)lVar8 < 1) {
LAB_1000a2b7:
    addstr(puVar2);
    closeandpush();
    lua_pushnumber((float)iStack_60);
    return;
  }
  do {
    aiStack_4c[0] = 0;
    puVar5 = (uint *)match((char *)puVar2,piVar3,aiStack_4c);
    if (puVar5 == (uint *)0x0) {
LAB_1000a291:
      if ((char)*puVar2 == '\0') goto LAB_1000a2b7;
      puVar5 = (uint *)((int)puVar2 + 1);
      luaL_addchar((char)*puVar2);
    }
    else {
      iStack_60 = iStack_60 + 1;
      add_s(iVar4,aiStack_4c);
      if ((puVar5 == (uint *)0x0) || (puVar5 <= puVar2)) goto LAB_1000a291;
    }
    puVar2 = puVar5;
    if ((bVar7) || ((int)lVar8 <= iStack_60)) goto LAB_1000a2b7;
  } while( true );
}
#undef aiStack_4c
#undef iStack_60


/* ---- 0x1000a2e0  add_s ---- */
/* gsub replacement: string or function result Named add_s (not in the remaster, gcc inlined it
   there): Lua 3.1 source name (lstrlib.c static add_s(newp, cap): gsub's replacement, a string with
   %n captures or a function called with push_captures; error "string or function expected"); was
   str_add_value. */

void __cdecl add_s(int param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  char *pcVar7;
  
  iVar2 = lua_isstring(param_1);
  if (iVar2 == 0) {
    iVar2 = lua_isfunction(param_1);
    if (iVar2 != 0) {
      lua_beginblock();
      push_captures(param_2);
      iVar2 = luaL_newbuffer(0);
      iVar5 = lua_callfunction(param_1);
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
      puVar6 = (uint *)lua_getstring(iVar2);
      addstr(puVar6);
      lua_endblock();
      return;
    }
    luaL_argerror(3,((unsigned)(uintptr_t)&s_string_or_function_expected_10027a3c));
  }
  else {
    pcVar3 = (char *)lua_getstring(param_1);
    cVar1 = *pcVar3;
    if (cVar1 != '\0') {
      do {
        pcVar7 = pcVar3;
        if (cVar1 == '%') {
          if (DAT_10028b5c < 2) {
            uVar4 = (byte)PTR_DAT_10028950[(uint)(byte)pcVar3[1] * 2] & 4;
          }
          else {
            uVar4 = _isctype((uint)(byte)pcVar3[1],4);
          }
          pcVar7 = pcVar3 + 1;
          if (uVar4 == 0) goto LAB_1000a36b;
          pcVar3 = pcVar3 + 2;
          iVar2 = check_cap((int)*pcVar7,param_2);
          addnchar((uint *)param_2[iVar2 * 2 + 1],param_2[iVar2 * 2 + 2]);
        }
        else {
LAB_1000a36b:
          pcVar3 = pcVar7 + 1;
          luaL_addchar(*pcVar7);
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name str_format (the remaster's libLua.so: strlib entry 'format'); was FUN_1000a440. */

void str_format(void)

{
  unsigned char _frame[0x130] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  char *buf;
  int iVar5;
  uint *puVar6;
  float fVar7;
  #define aiStack_114 (*(int (*)[2])(_frame + (0x130 - 0x114)))
  #define iStack_10c (*(int *)(_frame + (0x130 - 0x10c)))
  #define iStack_104 (*(int *)(_frame + (0x130 - 0x104)))
  #define cStack_c8 (*(char *)(_frame + (0x130 - 0xc8)))
  #define uStack_c7 (*(undefined4 *)(_frame + (0x130 - 0xc7)))
  
  iVar5 = 1;
  pcVar2 = (char *)luaL_check_string(1);
  luaL_resetbuffer();
  cVar1 = *pcVar2;
  do {
    if (cVar1 == '\0') {
      closeandpush();
      return;
    }
    if (cVar1 == '%') {
      puVar6 = (uint *)(pcVar2 + 1);
      if (pcVar2[1] == '%') {
        pcVar2 = pcVar2 + 2;
        luaL_addchar(0x25);
      }
      else {
        cStack_c8 = '%';
        aiStack_114[0] = 0;
        pcVar3 = match((char *)puVar6,(int *)s__d_____________d_______d___10027aa4,aiStack_114);
        if ((3 < iStack_10c) || (3 < iStack_104)) {
          lua_error((byte *)s_invalid_format__width_or_precisi_10027a74);
        }
        if (DAT_10028b5c < 2) {
          uVar4 = (byte)PTR_DAT_10028950[(uint)(byte)*puVar6 * 2] & 4;
        }
        else {
          uVar4 = _isctype((uint)(byte)*puVar6,4);
        }
        if ((uVar4 != 0) && (pcVar2[2] == '$')) {
          iVar5 = (char)(byte)*puVar6 + -0x30;
          puVar6 = (uint *)(pcVar2 + 3);
        }
        iVar5 = iVar5 + 1;
        strncpy(&uStack_c7,puVar6,(uint)(pcVar3 + (1 - (int)puVar6)));
        pcVar3[(int)&uStack_c7 + (1 - (int)puVar6)] = '\0';
        buf = (char *)luaL_openspace(1000);
        pcVar2 = pcVar3 + 1;
        switch(*pcVar3) {
        case 'E':
        case 'G':
        case 'e':
        case 'f':
        case 'g':
          fVar7 = luaL_check_number(iVar5);
          sprintf(buf,&cStack_c8,(double)fVar7);
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
          luaL_check_number(iVar5);
          _ftol();
          sprintf(buf,&cStack_c8);
          break;
        case 'q':
          pcVar3 = (char *)luaL_check_string(iVar5);
          luaI_addquoted(pcVar3);
          goto LAB_1000a5fe;
        case 's':
          pcVar3 = (char *)luaL_check_string(iVar5);
          uVar4 = 0xffffffff;
          do {
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            cVar1 = *pcVar3;
            pcVar3 = pcVar3 + 1;
          } while (cVar1 != '\0');
          buf = (char *)luaL_openspace(~uVar4 - 1);
          sprintf(buf,&cStack_c8);
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

#endif


/* ---- 0x1000a680  luaI_addquoted ---- */
/* gsub replacement string with %n captures Named luaI_addquoted (not in the remaster, gcc inlined
   it there): Lua 3.1 source name (lstrlib.c luaI_addquoted: format %q, the string in double quotes
   with a backslash before the special characters; called by str_format); was str_add_s. */

void __cdecl luaI_addquoted(char *param_1)

{
  char *pcVar1;
  char cVar2;
  uint *puVar3;
  
  luaL_addchar(0x22);
  cVar2 = *param_1;
  while (cVar2 != '\0') {
    puVar3 = strchr((uint *)&DAT_10027ac0,cVar2);
    if (puVar3 != (uint *)0x0) {
      luaL_addchar(0x5c);
    }
    luaL_addchar(*param_1);
    pcVar1 = param_1 + 1;
    param_1 = param_1 + 1;
    cVar2 = *pcVar1;
  }
  luaL_addchar(0x22);
  return;
}
