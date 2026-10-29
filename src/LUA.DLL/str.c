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
  luaL_check_number(2);
  lVar8 = _ftol();
  iVar3 = (int)lVar8;
  luaL_opt_number(3,-1.0);
  lVar8 = _ftol();
  iVar4 = (int)lVar8;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 1 + iVar6;
  }
  if (iVar4 < 0) {
    iVar4 = iVar4 + 1 + iVar6;
  }
  if (((0 < iVar3) && (iVar3 <= iVar4)) && (iVar4 <= iVar6)) {
    luaL_resetbuffer();
    str_addnchar((uint *)(pcVar2 + iVar3 + -1),(iVar4 - iVar3) + 1);
    str_closeandpush();
    return;
  }
  lua_pushstring(&DAT_1002bedc);
  return;
}

/* ---- 0x10009650  str_addnchar ---- */
/* Unidentified function of lstrlib.c (string library) */

void __cdecl str_addnchar(uint *param_1,uint param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)luaL_openspace(param_2);
  strncpy(puVar1,param_1,param_2);
  lbuiltin__2d10(param_2);
  return;
}

/* ---- 0x10009680  str_closeandpush ---- */
/* Unidentified function of lstrlib.c (string library) */

void str_closeandpush(void)

{
  byte *pbVar1;
  
  luaL_addchar(0);
  pbVar1 = (byte *)lbuiltin__2da0();
  lua_pushstring(pbVar1);
  return;
}

/* ---- 0x100096a0  FUN_100096a0 ---- */
void FUN_100096a0(void)

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
  str_closeandpush();
  return;
}

/* ---- 0x100096e0  FUN_100096e0 ---- */
void FUN_100096e0(void)

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
  str_closeandpush();
  return;
}

/* ---- 0x10009720  FUN_10009720 ---- */
void FUN_10009720(void)

{
  uint *puVar1;
  int iVar2;
  longlong lVar3;
  
  puVar1 = (uint *)luaL_check_string(1);
  luaL_check_number(2);
  lVar3 = _ftol();
  iVar2 = (int)lVar3;
  luaL_resetbuffer();
  if (0 < iVar2) {
    do {
      str_addstr(puVar1);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  str_closeandpush();
  return;
}

/* ---- 0x10009760  str_addstr ---- */
/* Unidentified function of lstrlib.c (string library) */

void __cdecl str_addstr(uint *param_1)

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
  str_addnchar(param_1,~uVar2 - 1);
  return;
}

/* ---- 0x10009780  FUN_10009780 ---- */
void FUN_10009780(void)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  longlong lVar6;
  
  pcVar2 = (char *)luaL_check_string(1);
  luaL_opt_number(2,1.0);
  lVar6 = _ftol();
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
  luaL_argerror(2,IMG_ADDR(0x10027970));
LAB_100097c8:
  lua_pushnumber((float)(byte)pcVar2[uVar4]);
  return;
}

/* ---- 0x100097f0  str_singlematch ---- */
/* luaI_singlematch: one pattern item against one char */

uint __cdecl str_singlematch(uint param_1,char *param_2,int *param_3)

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
      luaL_verror(s_incorrect_pattern__ends_with___c_100279a0);
    }
    *param_3 = (int)(param_2 + 2);
    uVar3 = str_matchclass(param_1,(int)param_2[1]);
    return uVar3;
  case '.':
    *param_3 = (int)(param_2 + 1);
    return (uint)(param_1 != 0);
  case '[':
    break;
  }
  pcVar1 = param_2 + 1;
  puVar2 = str_bracket_end(pcVar1);
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
            uVar3 = str_matchclass(param_1,(int)*pcVar1);
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

/* ---- 0x100099e0  str_bracket_end ---- */
/* Unidentified function of lstrlib.c (string library) */

uint * __cdecl str_bracket_end(char *param_1)

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

/* ---- 0x10009a10  str_matchclass ---- */
/* %a %d %s ... character classes */

uint __cdecl str_matchclass(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar2 = param_2 & 0xff;
  uVar1 = toupper(uVar2);
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

/* ---- 0x10009cb0  FUN_10009cb0 ---- */
void FUN_10009cb0(void)

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
  int *unaff_EDI;
  char *pcVar11;
  longlong lVar12;
  #define aiStack_4c (*(int (*)[19])(_frame + (0x60 - 0x4c)))
  
  pcVar3 = (char *)luaL_check_string(1);
  pbVar4 = (byte *)luaL_check_string(2);
  luaL_opt_number(3,1.0);
  lVar12 = _ftol();
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
  luaL_argerror(3,IMG_ADDR(0x10027970));
LAB_10009d07:
  iVar5 = lua_lua2C(4);
  if ((iVar5 == 0) && (pbVar6 = strcmp(pbVar4,(byte *)s___________100279c4), pbVar6 != (byte *)0x0))
  {
    bVar2 = *pbVar4;
    if (bVar2 == 0x5e) {
      pbVar4 = pbVar4 + 1;
    }
    pcVar11 = pcVar3 + uVar10;
    aiStack_4c[0] = 0;
    pcVar7 = str_match(pcVar11,(int *)pbVar4,aiStack_4c);
    while( true ) {
      if (pcVar7 != (char *)0x0) {
        lua_pushnumber((float)(int)(pcVar11 + (1 - (int)pcVar3)));
        lua_pushnumber((float)((int)pcVar7 - (int)pcVar3));
        str_push_captures(aiStack_4c,unaff_EDI);
        return;
      }
      cVar1 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      if ((cVar1 == '\0') || (bVar2 == 0x5e)) break;
      aiStack_4c[0] = 0;
      pcVar7 = str_match(pcVar11,(int *)pbVar4,aiStack_4c);
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


/* ---- 0x10009e40  str_push_captures ---- */
/* errors 'unfinished capture' */

void __cdecl str_push_captures(int *param_1,int *param_2)

{
  uint uVar1;
  uint *puVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = 0;
  if (0 < *param_1) {
    piVar3 = param_1 + 1;
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
    } while (iVar4 < *param_2);
  }
  return;
}

/* ---- 0x10009ea0  str_match ---- */
/* recursive pattern matcher; errors 'too many captures' */

char * __cdecl str_match(char *param_1,int *param_2,int *param_3)

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
        pcVar3 = str_match(param_1,(int *)((int)param_2 + 1),piVar2);
        if (pcVar3 != (char *)0x0) {
          return pcVar3;
        }
        *piVar2 = *piVar2 + -1;
        return (char *)0x0;
      case ')':
        iVar5 = str_capture_to_close(piVar2);
        piVar2[iVar5 * 2 + 2] = (int)param_1 - piVar2[iVar5 * 2 + 1];
        pcVar3 = str_match(param_1,(int *)((int)param_2 + 1),piVar2);
        if (pcVar3 != (char *)0x0) {
          return pcVar3;
        }
        piVar2[iVar5 * 2 + 2] = -1;
        return (char *)0x0;
      }
      pcVar3 = str_matchbalance(param_1,(char *)param_2,piVar2,(int *)&param_3);
      cVar1 = (char)*param_3;
      if (cVar1 != '*') break;
      if (pcVar3 != (char *)0x0) {
LAB_10009f49:
        pcVar3 = str_match(pcVar3,param_2,piVar2);
        if (pcVar3 != (char *)0x0) {
          return pcVar3;
        }
      }
LAB_10009f5e:
      param_2 = (int *)((int)param_3 + 1);
    }
    if (cVar1 == '-') {
      pcVar4 = str_match(param_1,(int *)((int)param_3 + 1),piVar2);
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

/* ---- 0x1000a030  str_capture_to_close ---- */
/* Unidentified function of lstrlib.c (string library) */

int __cdecl str_capture_to_close(int *param_1)

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

/* ---- 0x1000a060  str_matchbalance ---- */
/* errors 'unbalanced pattern' */

char * __cdecl str_matchbalance(char *param_1,char *param_2,int *param_3,int *param_4)

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
      iVar2 = str_check_capture((int)(char)*pbVar4,param_3);
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
      pcVar3 = str_expand(param_1,(int)param_2[2],(int)param_2[3]);
      return pcVar3;
    }
  }
  uVar1 = str_singlematch((int)*param_1,param_2,param_4);
  if (uVar1 == 0) {
    return (char *)0x0;
  }
  return param_1 + 1;
}

/* ---- 0x1000a150  str_check_capture ---- */
/* errors 'invalid capture index' */

int __cdecl str_check_capture(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x31;
  if (((iVar1 < 0) || (*param_2 <= iVar1)) || (param_2[iVar1 * 2 + 2] == -1)) {
    lua_error((byte *)s_invalid_capture_index_10027a24);
  }
  return iVar1;
}

/* ---- 0x1000a180  str_expand ---- */
/* max/min expansion of a repeated pattern item */

char * __cdecl str_expand(char *param_1,int param_2,int param_3)

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

/* ---- 0x1000a1d0  FUN_1000a1d0 ---- */
void FUN_1000a1d0(void)

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
  luaL_opt_number(4,(float)~uVar6);
  lVar8 = _ftol();
  bVar7 = (char)*piVar3 == '^';
  if (bVar7) {
    piVar3 = (int *)((int)piVar3 + 1);
  }
  iStack_60 = 0;
  luaL_resetbuffer();
  if ((int)lVar8 < 1) {
LAB_1000a2b7:
    str_addstr(puVar2);
    str_closeandpush();
    lua_pushnumber((float)iStack_60);
    return;
  }
  do {
    aiStack_4c[0] = 0;
    puVar5 = (uint *)str_match((char *)puVar2,piVar3,aiStack_4c);
    if (puVar5 == (uint *)0x0) {
LAB_1000a291:
      if ((char)*puVar2 == '\0') goto LAB_1000a2b7;
      puVar5 = (uint *)((int)puVar2 + 1);
      luaL_addchar((char)*puVar2);
    }
    else {
      iStack_60 = iStack_60 + 1;
      str_add_value(iVar4,aiStack_4c);
      if ((puVar5 == (uint *)0x0) || (puVar5 <= puVar2)) goto LAB_1000a291;
    }
    puVar2 = puVar5;
    if ((bVar7) || ((int)lVar8 <= iStack_60)) goto LAB_1000a2b7;
  } while( true );
}
#undef aiStack_4c
#undef iStack_60


/* ---- 0x1000a2e0  str_add_value ---- */
/* gsub replacement: string or function result */

void __cdecl str_add_value(int param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  char *pcVar7;
  int *unaff_EDI;
  
  iVar2 = lua_isstring(param_1);
  if (iVar2 == 0) {
    iVar2 = lua_isfunction(param_1);
    if (iVar2 != 0) {
      lua_beginblock();
      str_push_captures(param_2,unaff_EDI);
      iVar2 = lbuiltin__2d30(0);
      iVar5 = lua_callfunction(param_1);
      lbuiltin__2d80(iVar2);
      if (iVar5 != 0) {
        lua_endblock();
        lua_error((byte *)0x0);
      }
      iVar2 = lua_lua2C(1);
      iVar5 = lua_isstring(iVar2);
      if (iVar5 == 0) {
        str_addstr((uint *)&DAT_1002bedc);
        lua_endblock();
        return;
      }
      puVar6 = (uint *)lua_getstring(iVar2);
      str_addstr(puVar6);
      lua_endblock();
      return;
    }
    luaL_argerror(3,IMG_ADDR(0x10027a3c));
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
          iVar2 = str_check_capture((int)*pcVar7,param_2);
          str_addnchar((uint *)param_2[iVar2 * 2 + 1],param_2[iVar2 * 2 + 2]);
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

/* ---- 0x1000a440  FUN_1000a440 ---- */
void FUN_1000a440(void)

{
  unsigned char _frame[0x130] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  char *pcVar5;
  int iVar6;
  uint *puVar7;
  #define aiStack_114 (*(int (*)[2])(_frame + (0x130 - 0x114)))
  #define iStack_10c (*(int *)(_frame + (0x130 - 0x10c)))
  #define iStack_104 (*(int *)(_frame + (0x130 - 0x104)))
  #define cStack_c8 (*(char *)(_frame + (0x130 - 0xc8)))
  #define uStack_c7 (*(undefined4 *)(_frame + (0x130 - 0xc7)))
  
  iVar6 = 1;
  pcVar2 = (char *)luaL_check_string(1);
  luaL_resetbuffer();
  cVar1 = *pcVar2;
  do {
    if (cVar1 == '\0') {
      str_closeandpush();
      return;
    }
    if (cVar1 == '%') {
      puVar7 = (uint *)(pcVar2 + 1);
      if (pcVar2[1] == '%') {
        pcVar2 = pcVar2 + 2;
        luaL_addchar(0x25);
      }
      else {
        cStack_c8 = '%';
        aiStack_114[0] = 0;
        pcVar3 = str_match((char *)puVar7,(int *)s__d_____________d_______d___10027aa4,aiStack_114);
        if ((3 < iStack_10c) || (3 < iStack_104)) {
          lua_error((byte *)s_invalid_format__width_or_precisi_10027a74);
        }
        if (DAT_10028b5c < 2) {
          uVar4 = (byte)PTR_DAT_10028950[(uint)(byte)*puVar7 * 2] & 4;
        }
        else {
          uVar4 = _isctype((uint)(byte)*puVar7,4);
        }
        if ((uVar4 != 0) && (pcVar2[2] == '$')) {
          iVar6 = (char)(byte)*puVar7 + -0x30;
          puVar7 = (uint *)(pcVar2 + 3);
        }
        iVar6 = iVar6 + 1;
        strncpy(&uStack_c7,puVar7,(uint)(pcVar3 + (1 - (int)puVar7)));
        pcVar3[(int)&uStack_c7 + (1 - (int)puVar7)] = '\0';
        pcVar5 = (char *)luaL_openspace(1000);
        pcVar2 = pcVar3 + 1;
        switch(*pcVar3) {
        case 'E':
        case 'G':
        case 'e':
        case 'f':
        case 'g':
          luaL_check_number(iVar6);
          sprintf(pcVar5,&cStack_c8);
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
          luaL_check_number(iVar6);
          _ftol();
          sprintf(pcVar5,&cStack_c8);
          break;
        case 'q':
          pcVar3 = (char *)luaL_check_string(iVar6);
          str_add_s(pcVar3);
          goto LAB_1000a5fe;
        case 's':
          pcVar3 = (char *)luaL_check_string(iVar6);
          uVar4 = 0xffffffff;
          do {
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            cVar1 = *pcVar3;
            pcVar3 = pcVar3 + 1;
          } while (cVar1 != '\0');
          pcVar5 = (char *)luaL_openspace(~uVar4 - 1);
          sprintf(pcVar5,&cStack_c8);
        }
        uVar4 = 0xffffffff;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar1 != '\0');
        lbuiltin__2d10(~uVar4 - 1);
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


/* ---- 0x1000a680  str_add_s ---- */
/* gsub replacement string with %n captures */

void __cdecl str_add_s(char *param_1)

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
