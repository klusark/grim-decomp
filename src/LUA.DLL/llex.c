/* LUA.DLL :: llex.c
 * functions 0x10005c00 .. 0x10006cb0 (11 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10005c00  luaX_init ---- */
/* llex.c: interns the reserved words */

void luaX_init(void)

{
  undefined *puVar1;
  TaggedString *pTVar2;
  undefined **ppuVar3;
  
  ppuVar3 = (undefined **)&DAT_10026d14;
  do {
    pTVar2 = luaS_new(ppuVar3[-1]);
    puVar1 = *ppuVar3;
    ppuVar3 = ppuVar3 + 2;
    pTVar2->nMarked = (int)puVar1;
  } while (ppuVar3 < &PTR_DAT_10026d94);
  return;
}

/* ---- 0x10005c30  luaX_setinput ---- */
/* Unidentified function of llex.c (lexer) */

void __cdecl luaX_setinput(undefined4 z)

{
  undefined4 *LS;
  
  LS = g_pLuaState->pLexState;
  LS[3] = 0;
  LS[2] = 0;
  LS[5] = 0;
  LS[8] = 0;
  *LS = 10;
  LS[6] = 1;
  LS[1] = z;
  firstline((int)LS);
  luaL_resetbuffer();
  return;
}

/* ---- 0x10005c70  firstline ---- */
/* Named firstline (not in the remaster, gcc inlined it there): Lua 3.1 source name (llex.c: skips a
   first line starting with '#', called by luaX_setinput); was llex__5c70. */

void __cdecl firstline(int LS)

{
  int *piVar1;
  uint uVar2;
  
  **(int **)(LS + 4) = **(int **)(LS + 4) + -1;
  piVar1 = *(int **)(LS + 4);
  if (*piVar1 < 0) {
    uVar2 = (*(code *)piVar1[2])(piVar1);
  }
  else {
    uVar2 = (uint)*(byte *)piVar1[1];
    piVar1[1] = (int)((byte *)piVar1[1] + 1);
  }
  if (uVar2 == 0x23) {
    *(int *)(LS + 8) = *(int *)(LS + 8) + 1;
    do {
      **(int **)(LS + 4) = **(int **)(LS + 4) + -1;
      piVar1 = *(int **)(LS + 4);
      if (*piVar1 < 0) {
        uVar2 = (*(code *)piVar1[2])(piVar1);
      }
      else {
        uVar2 = (uint)*(byte *)piVar1[1];
        piVar1[1] = (int)((byte *)piVar1[1] + 1);
      }
    } while ((uVar2 != 10) && (uVar2 != 0xffffffff));
  }
  **(int **)(LS + 4) = **(int **)(LS + 4) + 1;
  *(int *)(*(int *)(LS + 4) + 4) = *(int *)(*(int *)(LS + 4) + 4) + -1;
  return;
}

/* ---- 0x10005cf0  luaX_lasttoken ---- */
/* save_and_next: appends the current char to the token buffer Original name luaX_lasttoken (the
   remaster's libLua.so: same body: luaL_addchar(0); return luaL_buffer()); was luaX_save. */

int luaX_lasttoken(void)

{
  int iVar1;
  
  luaL_addchar(0);
  iVar1 = luaL_buffer();
  return iVar1;
}

/* ---- 0x10005d00  luaY_lex ---- */
/* llex.c: main tokenizer; numbers are returned through the float out-parameter Original name
   luaY_lex (the remaster's libLua.so: string 'ambiguous syntax (decimal point x string
   concatenation)' (the bison yylex renamed luaY_lex)); was luaX_lex. */

uint __cdecl luaY_lex(float *value)

{
  byte bVar1;
  uint *LS;
  double dVar2;
  uint uVar3;
  uint uVar4;
  TaggedString *pTVar5;
  int *piVar6;
  longlong lVar7;
  undefined1 c;
  uint local_14;
  double local_10;
  double local_8;
  
  LS = g_pLuaState->pLexState;
  luaL_resetbuffer();
  if (lua_debug != 0) {
    luaY_codedebugline(LS[3]);
  }
  LS[3] = LS[2];
  do {
    switch(*LS) {
    default:
      if ((*LS != 0x5f) && (uVar3 = FUN_1000f5c0(*LS), uVar3 == 0)) {
        uVar3 = *LS;
        luaL_addchar((char)uVar3);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar4 = (*(code *)piVar6[2])(piVar6);
          *LS = uVar4;
          return uVar3;
        }
        bVar1 = *(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
        *LS = (uint)bVar1;
        return uVar3;
      }
      do {
        luaL_addchar((char)*LS);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar3 = (*(code *)piVar6[2])(piVar6);
        }
        else {
          uVar3 = (uint)*(byte *)piVar6[1];
          piVar6[1] = (int)((byte *)piVar6[1] + 1);
        }
        *LS = uVar3;
        uVar3 = FUN_1000f650(uVar3);
      } while ((uVar3 != 0) || (*LS == 0x5f));
      luaL_addchar(0);
      pTVar5 = luaS_new(g_dwLState_Mbuffbase);
      if (pTVar5->nMarked < 0x100) {
        *value = PUN(float,pTVar5);
        return 0x112;
      }
      return pTVar5->nMarked;
    case 9:
    case 0xd:
    case 0x20:
      *(int *)LS[1] = *(int *)LS[1] + -1;
      piVar6 = (int *)LS[1];
      if (*piVar6 < 0) {
        uVar3 = (*(code *)piVar6[2])(piVar6);
        *LS = uVar3;
      }
      else {
        bVar1 = *(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
        *LS = (uint)bVar1;
      }
      break;
    case 10:
      inclinenumber(LS);
      LS[3] = LS[2];
      break;
    case 0x22:
    case 0x27:
      uVar3 = *LS;
      c = (undefined1)uVar3;
      luaL_addchar(c);
      *(int *)LS[1] = *(int *)LS[1] + -1;
      piVar6 = (int *)LS[1];
      if (*piVar6 < 0) {
        uVar4 = (*(code *)piVar6[2])(piVar6);
      }
      else {
        uVar4 = (uint)*(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
      }
      *LS = uVar4;
      goto joined_r0x100060f4;
    case 0x2d:
      luaL_addchar((char)*LS);
      *(int *)LS[1] = *(int *)LS[1] + -1;
      piVar6 = (int *)LS[1];
      if (*piVar6 < 0) {
        uVar3 = (*(code *)piVar6[2])(piVar6);
      }
      else {
        uVar3 = (uint)*(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
      }
      *LS = uVar3;
      if (uVar3 != 0x2d) {
        return 0x2d;
      }
      do {
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar3 = (*(code *)piVar6[2])(piVar6);
        }
        else {
          uVar3 = (uint)*(byte *)piVar6[1];
          piVar6[1] = (int)((byte *)piVar6[1] + 1);
        }
        *LS = uVar3;
      } while ((uVar3 != 10) && (uVar3 != 0xffffffff));
      luaL_resetbuffer();
      break;
    case 0x2e:
      luaL_addchar((char)*LS);
      *(int *)LS[1] = *(int *)LS[1] + -1;
      piVar6 = (int *)LS[1];
      if (*piVar6 < 0) {
        uVar3 = (*(code *)piVar6[2])(piVar6);
      }
      else {
        uVar3 = (uint)*(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
      }
      *LS = uVar3;
      if (uVar3 == 0x2e) {
        luaL_addchar(0x2e);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar3 = (*(code *)piVar6[2])(piVar6);
        }
        else {
          uVar3 = (uint)*(byte *)piVar6[1];
          piVar6[1] = (int)((byte *)piVar6[1] + 1);
        }
        *LS = uVar3;
        if (uVar3 != 0x2e) {
          return 0x11a;
        }
        luaL_addchar(0x2e);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar3 = (*(code *)piVar6[2])(piVar6);
          *LS = uVar3;
          return 0x110;
        }
        bVar1 = *(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
        *LS = (uint)bVar1;
        return 0x110;
      }
      uVar3 = FUN_1000f5f0(uVar3);
      if (uVar3 == 0) {
        return 0x2e;
      }
      local_8 = 0.0f;
      goto LAB_10006398;
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
      local_8 = 0.0f;
      do {
        local_8 = (double)(int)(*LS - 0x30) - local_8 * -10.0;
        luaL_addchar((char)*LS);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar3 = (*(code *)piVar6[2])(piVar6);
        }
        else {
          uVar3 = (uint)*(byte *)piVar6[1];
          piVar6[1] = (int)((byte *)piVar6[1] + 1);
        }
        *LS = uVar3;
        uVar3 = FUN_1000f5f0(uVar3);
      } while (uVar3 != 0);
      if (*LS == 0x2e) {
        luaL_addchar(0x2e);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar3 = (*(code *)piVar6[2])(piVar6);
        }
        else {
          uVar3 = (uint)*(byte *)piVar6[1];
          piVar6[1] = (int)((byte *)piVar6[1] + 1);
        }
        *LS = uVar3;
        if (uVar3 == 0x2e) {
          luaL_addchar(0);
          luaY_error(s_ambiguous_syntax__decimal_point_x_10026e5c);
        }
      }
LAB_10006398:
      local_10 = 0.1;
      for (uVar3 = FUN_1000f5f0(*LS); uVar3 != 0; uVar3 = FUN_1000f5f0(uVar3)) {
        local_8 = (double)(int)(*LS - 0x30) * local_10 + local_8;
        local_10 = local_10 * 0.1;
        luaL_addchar((char)*LS);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar3 = (*(code *)piVar6[2])(piVar6);
        }
        else {
          uVar3 = (uint)*(byte *)piVar6[1];
          piVar6[1] = (int)((byte *)piVar6[1] + 1);
        }
        *LS = uVar3;
      }
      uVar3 = toupper(*LS);
      if (uVar3 != 0x45) {
LAB_10006563:
        *value = (float)local_8;
        return 0x111;
      }
      local_14 = 0;
      luaL_addchar((char)*LS);
      *(int *)LS[1] = *(int *)LS[1] + -1;
      piVar6 = (int *)LS[1];
      if (*piVar6 < 0) {
        uVar3 = (*(code *)piVar6[2])(piVar6);
      }
      else {
        uVar3 = (uint)*(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
      }
      *LS = uVar3;
      if ((uVar3 == 0x2b) || (uVar3 == 0x2d)) {
        luaL_addchar((char)uVar3);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar4 = (*(code *)piVar6[2])(piVar6);
        }
        else {
          uVar4 = (uint)*(byte *)piVar6[1];
          piVar6[1] = (int)((byte *)piVar6[1] + 1);
        }
        *LS = uVar4;
      }
      uVar4 = FUN_1000f5f0(*LS);
      if (uVar4 != 0) {
        do {
          uVar4 = *LS;
          lVar7 = FTOL((float10)(int)(uVar4 - 0x30) - (float10)(int)local_14 * (float10)-10.0);
          local_14 = (uint)lVar7;
          luaL_addchar((char)uVar4);
          *(int *)LS[1] = *(int *)LS[1] + -1;
          piVar6 = (int *)LS[1];
          if (*piVar6 < 0) {
            uVar4 = (*(code *)piVar6[2])(piVar6);
          }
          else {
            uVar4 = (uint)*(byte *)piVar6[1];
            piVar6[1] = (int)((byte *)piVar6[1] + 1);
          }
          *LS = uVar4;
          uVar4 = FUN_1000f5f0(uVar4);
        } while (uVar4 != 0);
        if (uVar3 == 0x2d) {
          dVar2 = 0.1;
        }
        else {
          dVar2 = 10.0;
        }
        for (; 0 < (int)local_14; local_14 = (int)local_14 >> 1) {
          if ((local_14 & 1) != 0) {
            local_8 = dVar2 * local_8;
          }
          dVar2 = dVar2 * dVar2;
        }
        goto LAB_10006563;
      }
      goto LAB_100064b9;
    case 0x3c:
      luaL_addchar((char)*LS);
      *(int *)LS[1] = *(int *)LS[1] + -1;
      piVar6 = (int *)LS[1];
      if (*piVar6 < 0) {
        uVar3 = (*(code *)piVar6[2])(piVar6);
      }
      else {
        uVar3 = (uint)*(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
      }
      *LS = uVar3;
      if (uVar3 == 0x3d) {
        luaL_addchar(0x3d);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar3 = (*(code *)piVar6[2])(piVar6);
          *LS = uVar3;
          return 0x118;
        }
        bVar1 = *(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
        *LS = (uint)bVar1;
        return 0x118;
      }
      return 0x3c;
    case 0x3d:
      luaL_addchar((char)*LS);
      *(int *)LS[1] = *(int *)LS[1] + -1;
      piVar6 = (int *)LS[1];
      if (*piVar6 < 0) {
        uVar3 = (*(code *)piVar6[2])(piVar6);
      }
      else {
        uVar3 = (uint)*(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
      }
      *LS = uVar3;
      if (uVar3 == 0x3d) {
        luaL_addchar(0x3d);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar3 = (*(code *)piVar6[2])(piVar6);
          *LS = uVar3;
          return 0x116;
        }
        bVar1 = *(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
        *LS = (uint)bVar1;
        return 0x116;
      }
      return 0x3d;
    case 0x3e:
      luaL_addchar((char)*LS);
      *(int *)LS[1] = *(int *)LS[1] + -1;
      piVar6 = (int *)LS[1];
      if (*piVar6 < 0) {
        uVar3 = (*(code *)piVar6[2])(piVar6);
      }
      else {
        uVar3 = (uint)*(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
      }
      *LS = uVar3;
      if (uVar3 == 0x3d) {
        luaL_addchar(0x3d);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar3 = (*(code *)piVar6[2])(piVar6);
          *LS = uVar3;
          return 0x119;
        }
        bVar1 = *(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
        *LS = (uint)bVar1;
        return 0x119;
      }
      return 0x3e;
    case 0x5b:
      luaL_addchar((char)*LS);
      *(int *)LS[1] = *(int *)LS[1] + -1;
      piVar6 = (int *)LS[1];
      if (*piVar6 < 0) {
        uVar3 = (*(code *)piVar6[2])(piVar6);
      }
      else {
        uVar3 = (uint)*(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
      }
      *LS = uVar3;
      if (uVar3 == 0x5b) {
        luaL_addchar(0x5b);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar3 = (*(code *)piVar6[2])(piVar6);
        }
        else {
          uVar3 = (uint)*(byte *)piVar6[1];
          piVar6[1] = (int)((byte *)piVar6[1] + 1);
        }
        *LS = uVar3;
        uVar3 = read_long_string(LS,value);
        return uVar3;
      }
      return 0x5b;
    case 0x7e:
      luaL_addchar((char)*LS);
      *(int *)LS[1] = *(int *)LS[1] + -1;
      piVar6 = (int *)LS[1];
      if (*piVar6 < 0) {
        uVar3 = (*(code *)piVar6[2])(piVar6);
      }
      else {
        uVar3 = (uint)*(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
      }
      *LS = uVar3;
      if (uVar3 == 0x3d) {
        luaL_addchar(0x3d);
        *(int *)LS[1] = *(int *)LS[1] + -1;
        piVar6 = (int *)LS[1];
        if (*piVar6 < 0) {
          uVar3 = (*(code *)piVar6[2])(piVar6);
          *LS = uVar3;
          return 0x117;
        }
        bVar1 = *(byte *)piVar6[1];
        piVar6[1] = (int)((byte *)piVar6[1] + 1);
        *LS = (uint)bVar1;
        return 0x117;
      }
      return 0x7e;
    case 0xffffffff:
      luaL_addchar(0);
      if (0 < (int)LS[5]) {
        luaY_syntaxerror(s_input_ends_inside_a__if_10026e44,&DAT_1002bedc);
      }
      return 0;
    }
  } while( true );
joined_r0x100060f4:
  if (uVar4 == uVar3) {
    *(int *)LS[1] = *(int *)LS[1] + -1;
    piVar6 = (int *)LS[1];
    if (*piVar6 < 0) {
      uVar3 = (*(code *)piVar6[2])(piVar6);
    }
    else {
      uVar3 = (uint)*(byte *)piVar6[1];
      piVar6[1] = (int)((byte *)piVar6[1] + 1);
    }
    *LS = uVar3;
    luaL_addchar(0);
    pTVar5 = luaS_new(g_dwLState_Mbuffbase + 1);
    *value = PUN(float,pTVar5);
    *(undefined1 *)(g_dwLState_Mbuffnext + -1 + g_dwLState_Mbuffer) = c;
    return 0x113;
  }
  uVar4 = *LS;
  if ((uVar4 == 0xffffffff) || (uVar4 == 10)) {
LAB_100064b9:
    luaL_addchar(0);
    return 0x102;
  }
  if (uVar4 != 0x5c) {
    luaL_addchar((char)uVar4);
    *(int *)LS[1] = *(int *)LS[1] + -1;
    piVar6 = (int *)LS[1];
    if (*piVar6 < 0) goto LAB_10006238;
    uVar4 = (uint)*(byte *)piVar6[1];
    piVar6[1] = (int)((byte *)piVar6[1] + 1);
    goto LAB_1000623f;
  }
  *(int *)LS[1] = *(int *)LS[1] + -1;
  piVar6 = (int *)LS[1];
  if (*piVar6 < 0) {
    uVar4 = (*(code *)piVar6[2])(piVar6);
  }
  else {
    uVar4 = (uint)*(byte *)piVar6[1];
    piVar6[1] = (int)((byte *)piVar6[1] + 1);
  }
  *LS = uVar4;
  switch(uVar4) {
  case 10:
    luaL_addchar(10);
    inclinenumber(LS);
    goto LAB_10006241;
  default:
    luaL_addchar((char)uVar4);
    *(int *)LS[1] = *(int *)LS[1] + -1;
    piVar6 = (int *)LS[1];
    if (*piVar6 < 0) {
LAB_10006238:
      uVar4 = (*(code *)piVar6[2])(piVar6);
    }
    else {
      uVar4 = (uint)*(byte *)piVar6[1];
      piVar6[1] = (int)((byte *)piVar6[1] + 1);
    }
    break;
  case 0x6e:
    luaL_addchar(10);
    *(int *)LS[1] = *(int *)LS[1] + -1;
    piVar6 = (int *)LS[1];
    if (*piVar6 < 0) goto LAB_10006238;
    uVar4 = (uint)*(byte *)piVar6[1];
    piVar6[1] = (int)((byte *)piVar6[1] + 1);
    break;
  case 0x72:
    luaL_addchar(0xd);
    *(int *)LS[1] = *(int *)LS[1] + -1;
    piVar6 = (int *)LS[1];
    if (*piVar6 < 0) goto LAB_10006238;
    uVar4 = (uint)*(byte *)piVar6[1];
    piVar6[1] = (int)((byte *)piVar6[1] + 1);
    break;
  case 0x74:
    luaL_addchar(9);
    *(int *)LS[1] = *(int *)LS[1] + -1;
    piVar6 = (int *)LS[1];
    if (*piVar6 < 0) goto LAB_10006238;
    uVar4 = (uint)*(byte *)piVar6[1];
    piVar6[1] = (int)((byte *)piVar6[1] + 1);
  }
LAB_1000623f:
  *LS = uVar4;
LAB_10006241:
  uVar4 = *LS;
  goto joined_r0x100060f4;
}

/* ---- 0x10006890  inclinenumber ---- */
/* llex.c: handles the $debug / $nodebug / $if pragmas Original name inclinenumber (the remaster's
   libLua.so: static inclinenumber(LexState*): the pragma strings ('unknown pragma', 'too many
   nested $ifs', 'unmatched $else'); the remaster's static table inclinenumber::pragmas); was
   luaX_pragma. */

void __cdecl inclinenumber(uint *LS)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *msg;
  char *token;
  #define local_18 (*(byte (*)[24])(_frame + (0x30 - 0x18)))
  
  *(int *)LS[1] = *(int *)LS[1] + -1;
  piVar1 = (int *)LS[1];
  if (*piVar1 < 0) {
    uVar2 = (*(code *)piVar1[2])(piVar1);
  }
  else {
    uVar2 = (uint)*(byte *)piVar1[1];
    piVar1[1] = (int)((byte *)piVar1[1] + 1);
  }
  *LS = uVar2;
  LS[2] = LS[2] + 1;
  if (uVar2 != 0x24) {
    return;
  }
  uVar5 = 0;
  uVar2 = LS[LS[5] * 3 + 8];
  *(int *)LS[1] = *(int *)LS[1] + -1;
  piVar1 = (int *)LS[1];
  if (*piVar1 < 0) {
    uVar3 = (*(code *)piVar1[2])(piVar1);
  }
  else {
    uVar3 = (uint)*(byte *)piVar1[1];
    piVar1[1] = (int)((byte *)piVar1[1] + 1);
  }
  *LS = uVar3;
  readname(LS,(int)local_18);
  iVar4 = luaO_findstring(local_18,&g_pInclinenumber_pragmas);
  switch(iVar4) {
  case 0:
    if (uVar2 == 0) {
      lua_debug = 1;
    }
    break;
  case 1:
    if (uVar2 == 0) {
      lua_debug = 0;
    }
    break;
  case 2:
    if (uVar2 == 0) {
      *LS = 0xffffffff;
      LS[5] = 0;
    }
    break;
  case 3:
    uVar2 = LS[5];
    LS[5] = uVar2 - 1;
    if (uVar2 != 0) break;
    token = s__end_10026f00;
    msg = s_unmatched__end_10026ef0;
    goto LAB_10006a8e;
  case 4:
    uVar5 = 1;
  case 5:
    if (LS[5] == 4) {
      luaY_syntaxerror(s_too_many_nested__ifs_10026ed4,s__if_10026eec);
    }
    readname(LS,(int)local_18);
    uVar3 = LS[5];
    LS[5] = uVar3 + 1;
    LS[(uVar3 + 3) * 3] = 0;
    uVar3 = checkcond(local_18);
    if (uVar3 != 0) {
      uVar5 = (uint)(uVar5 == 0);
    }
    LS[LS[5] * 3 + 7] = uVar5;
    if ((uVar2 == 0) && (LS[LS[5] * 3 + 7] != 0)) {
      LS[LS[5] * 3 + 8] = 0;
    }
    else {
      LS[LS[5] * 3 + 8] = 1;
    }
    break;
  case 6:
    if (LS[(LS[5] + 2) * 3] != 0) {
      luaY_syntaxerror(s_unmatched__else_10026ebc,s__else_10026ecc);
    }
    LS[(LS[5] + 2) * 3] = 1;
    uVar2 = LS[5];
    if ((LS[uVar2 * 3 + 5] == 0) && (LS[uVar2 * 3 + 7] == 0)) {
      LS[uVar2 * 3 + 8] = 0;
    }
    else {
      LS[uVar2 * 3 + 8] = 1;
    }
    break;
  default:
    token = (char *)local_18;
    msg = s_unknown_pragma_10026eac;
LAB_10006a8e:
    luaY_syntaxerror(msg,token);
  }
  skipspace(LS);
  if (*LS != 10) {
    if (*LS != 0xffffffff) {
      luaY_syntaxerror(s_invalid_pragma_format_10026e94,(char *)local_18);
    }
    ifskip(LS);
    return;
  }
  inclinenumber(LS);
  ifskip(LS);
  return;
}
#undef local_18


/* ---- 0x10006b10  skipspace ---- */
/* Original name skipspace (the remaster's libLua.so: static skipspace(LexState*): skips blanks,
   tabs and CRs); was luaX_inclinenumber. */

void __cdecl skipspace(uint *LS)

{
  byte bVar1;
  int *piVar2;
  uint uVar3;
  
  while (((uVar3 = *LS, uVar3 == 0x20 || (uVar3 == 9)) || (uVar3 == 0xd))) {
    *(int *)LS[1] = *(int *)LS[1] + -1;
    piVar2 = (int *)LS[1];
    if (*piVar2 < 0) {
      uVar3 = (*(code *)piVar2[2])(piVar2);
      *LS = uVar3;
    }
    else {
      bVar1 = *(byte *)piVar2[1];
      piVar2[1] = (int)((byte *)piVar2[1] + 1);
      *LS = (uint)bVar1;
    }
  }
  return;
}

/* ---- 0x10006b60  checkcond ---- */
/* Original name checkcond (the remaster's libLua.so: the remaster's static table checkcond::opts;
   string 'invalid $if condition'); was luaX_error. */

uint __cdecl checkcond(byte *buff)

{
  uint uVar1;
  
  uVar1 = luaO_findstring(buff,&g_pCheckcond_opts);
  if ((int)uVar1 < 0) {
    uVar1 = FUN_1000f5c0((uint)*buff);
    if ((uVar1 == 0) && (*buff != 0x5f)) {
      luaY_syntaxerror(s_invalid__if_condition_10026f08,(char *)buff);
      return 0;
    }
    uVar1 = luaS_globaldefined((char *)buff);
  }
  return uVar1;
}

/* ---- 0x10006bb0  readname ---- */
/* Original name readname (the remaster's libLua.so: static readname(LexState*, char*): string
   'pragma too long'); was llex__6bb0. */

void __cdecl readname(uint *LS,int token)

{
  byte bVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = 0;
  skipspace(LS);
  while( true ) {
    uVar3 = FUN_1000f650(*LS);
    if ((uVar3 == 0) && (*LS != 0x5f)) break;
    if (0x13 < iVar4) {
      *(undefined1 *)(token + 0x14) = 0;
      luaY_syntaxerror(s_pragma_too_long_10026f20,(char *)token);
    }
    *(char *)(iVar4 + token) = (char)*LS;
    iVar4 = iVar4 + 1;
    *(int *)LS[1] = *(int *)LS[1] + -1;
    piVar2 = (int *)LS[1];
    if (*piVar2 < 0) {
      uVar3 = (*(code *)piVar2[2])(piVar2);
      *LS = uVar3;
    }
    else {
      bVar1 = *(byte *)piVar2[1];
      piVar2[1] = (int)((byte *)piVar2[1] + 1);
      *LS = (uint)bVar1;
    }
  }
  *(undefined1 *)(iVar4 + token) = 0;
  return;
}

/* ---- 0x10006c30  ifskip ---- */
/* Named ifskip (not in the remaster, gcc inlined it there): Lua 3.1 source name (llex.c: skips
   input while the $if level is false, 'input ends inside a $if'); was llex__6c30. */

void __cdecl ifskip(uint *LS)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = LS[LS[5] * 3 + 8];
  while (uVar2 != 0) {
    if (*LS == 10) {
      inclinenumber(LS);
    }
    else if (*LS == 0xffffffff) {
      luaY_syntaxerror(s_input_ends_inside_a__if_10026e44,&DAT_1002bedc);
    }
    else {
      *(int *)LS[1] = *(int *)LS[1] + -1;
      piVar1 = (int *)LS[1];
      if (*piVar1 < 0) {
        uVar2 = (*(code *)piVar1[2])(piVar1);
      }
      else {
        uVar2 = (uint)*(byte *)piVar1[1];
        piVar1[1] = (int)((byte *)piVar1[1] + 1);
      }
      *LS = uVar2;
    }
    uVar2 = LS[LS[5] * 3 + 8];
  }
  return;
}

/* ---- 0x10006cb0  read_long_string ---- */
/* Named read_long_string (not in the remaster, gcc inlined it there): Lua 3.1 source name (llex.c:
   [[ ... ]] strings with nesting, called by luaY_lex); was llex__6cb0. */

undefined4 __cdecl read_long_string(uint *LS,undefined4 *l)

{
  byte bVar1;
  int *piVar2;
  uint uVar3;
  TaggedString *pTVar4;
  int iVar5;
  
  iVar5 = 0;
LAB_10006cb8:
  uVar3 = *LS;
  switch(uVar3) {
  default:
    goto LAB_10006d66;
  case 10:
    luaL_addchar(10);
    inclinenumber(LS);
    goto LAB_10006cb8;
  case 0x5b:
    goto switchD_10006cce_caseD_5b;
  case 0x5d:
    break;
  case 0xffffffff:
    luaL_addchar(0);
    return 0x102;
  }
  luaL_addchar((char)uVar3);
  *(int *)LS[1] = *(int *)LS[1] + -1;
  piVar2 = (int *)LS[1];
  if (*piVar2 < 0) {
    uVar3 = (*(code *)piVar2[2])(piVar2);
  }
  else {
    uVar3 = (uint)*(byte *)piVar2[1];
    piVar2[1] = (int)((byte *)piVar2[1] + 1);
  }
  *LS = uVar3;
  if (uVar3 != 0x5d) goto LAB_10006cb8;
  if (iVar5 == 0) {
    luaL_addchar(0x5d);
    *(int *)LS[1] = *(int *)LS[1] + -1;
    piVar2 = (int *)LS[1];
    if (*piVar2 < 0) {
      uVar3 = (*(code *)piVar2[2])(piVar2);
    }
    else {
      uVar3 = (uint)*(byte *)piVar2[1];
      piVar2[1] = (int)((byte *)piVar2[1] + 1);
    }
    *LS = uVar3;
    *(undefined1 *)(g_dwLState_Mbuffnext + -2 + g_dwLState_Mbuffer) = 0;
    pTVar4 = luaS_new((char *)(g_dwLState_Mbuffbase + 2));
    *l = pTVar4;
    *(undefined1 *)(g_dwLState_Mbuffnext + -2 + g_dwLState_Mbuffer) = 0x5d;
    return 0x113;
  }
  iVar5 = iVar5 + -1;
  uVar3 = 0x5d;
LAB_10006d66:
  luaL_addchar((char)uVar3);
  *(int *)LS[1] = *(int *)LS[1] + -1;
  piVar2 = (int *)LS[1];
  if (*piVar2 < 0) {
    uVar3 = (*(code *)piVar2[2])(piVar2);
    *LS = uVar3;
  }
  else {
    bVar1 = *(byte *)piVar2[1];
    piVar2[1] = (int)((byte *)piVar2[1] + 1);
    *LS = (uint)bVar1;
  }
  goto LAB_10006cb8;
switchD_10006cce_caseD_5b:
  luaL_addchar((char)uVar3);
  *(int *)LS[1] = *(int *)LS[1] + -1;
  piVar2 = (int *)LS[1];
  if (*piVar2 < 0) {
    uVar3 = (*(code *)piVar2[2])(piVar2);
  }
  else {
    uVar3 = (uint)*(byte *)piVar2[1];
    piVar2[1] = (int)((byte *)piVar2[1] + 1);
  }
  *LS = uVar3;
  if (uVar3 != 0x5b) goto LAB_10006cb8;
  iVar5 = iVar5 + 1;
  uVar3 = 0x5b;
  goto LAB_10006d66;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
typedef struct __attribute__((packed)) { unsigned char b0[4]; void *p4; unsigned char b8[4]; void *pc; unsigned char b10[4]; void *p14; unsigned char b18[4]; void *p1c; unsigned char b20[4]; void *p24; unsigned char b28[4]; void *p2c; unsigned char b30[4]; void *p34; unsigned char b38[4]; void *p3c; unsigned char b40[4]; void *p44; unsigned char b48[4]; void *p4c; unsigned char b50[4]; void *p54; unsigned char b58[4]; void *p5c; unsigned char b60[4]; void *p64; unsigned char b68[4]; void *p6c; unsigned char b70[4]; void *p74; unsigned char b78[4]; } grim_span_10026d14;
typedef struct __attribute__((packed)) { void *p0; unsigned char b4[8]; } grim_span_10026d94;
extern grim_span_10026d14 grim_def_DAT_10026d14 __asm__("_DAT_10026d14");
extern char grim_def_DAT_10026ddc[] __asm__("_DAT_10026ddc");
extern char grim_def_DAT_10026de0[] __asm__("_DAT_10026de0");
extern char grim_def_DAT_10026de8[] __asm__("_DAT_10026de8");
extern char grim_def_DAT_10026df0[] __asm__("_DAT_10026df0");
extern char grim_def_DAT_10026df8[] __asm__("_DAT_10026df8");
extern char grim_def_DAT_10026e00[] __asm__("_DAT_10026e00");
extern char grim_def_DAT_10026e08[] __asm__("_DAT_10026e08");
extern char grim_def_DAT_10026e0c[] __asm__("_DAT_10026e0c");
extern char grim_def_DAT_10026e10[] __asm__("_DAT_10026e10");
extern char grim_def_DAT_10026e18[] __asm__("_DAT_10026e18");
extern char grim_def_DAT_10026e28[] __asm__("_DAT_10026e28");
extern char grim_def_DAT_10026e2c[] __asm__("_DAT_10026e2c");
extern char grim_def_DAT_10026e34[] __asm__("_DAT_10026e34");
extern char grim_def_DAT_10026e3c[] __asm__("_DAT_10026e3c");
extern grim_span_10026d94 grim_def_PTR_DAT_10026d94 __asm__("_PTR_DAT_10026d94");
extern void *grim_def_g_pCheckcond_opts __asm__("_g_pCheckcond_opts");
extern void *grim_def_g_pInclinenumber_pragmas[8] __asm__("_g_pInclinenumber_pragmas");
extern char grim_def_s__else_10026ecc[8] __asm__("_s__else_10026ecc");
extern char grim_def_s__end_10026f00[8] __asm__("_s__end_10026f00");
extern char grim_def_s__if_10026eec[4] __asm__("_s__if_10026eec");
extern char grim_def_s_ambiguous_syntax__decimal_point_x_10026e5c[56] __asm__("_s_ambiguous_syntax__decimal_point_x_10026e5c");
extern char grim_def_s_debug_10026bb4[] __asm__("_s_debug_10026bb4");
extern char grim_def_s_endinput_10026dc8[] __asm__("_s_endinput_10026dc8");
extern char grim_def_s_function_10026e1c[] __asm__("_s_function_10026e1c");
extern char grim_def_s_ifnot_10026dc0[] __asm__("_s_ifnot_10026dc0");
extern char grim_def_s_input_ends_inside_a__if_10026e44[24] __asm__("_s_input_ends_inside_a__if_10026e44");
extern char grim_def_s_invalid__if_condition_10026f08[24] __asm__("_s_invalid__if_condition_10026f08");
extern char grim_def_s_invalid_pragma_format_10026e94[24] __asm__("_s_invalid_pragma_format_10026e94");
extern char grim_def_s_nil_100266f8[] __asm__("_s_nil_100266f8");
extern char grim_def_s_nodebug_10026dd4[] __asm__("_s_nodebug_10026dd4");
extern char grim_def_s_pragma_too_long_10026f20[16] __asm__("_s_pragma_too_long_10026f20");
extern char grim_def_s_too_many_nested__ifs_10026ed4[24] __asm__("_s_too_many_nested__ifs_10026ed4");
extern char grim_def_s_unknown_pragma_10026eac[16] __asm__("_s_unknown_pragma_10026eac");
extern char grim_def_s_unmatched__else_10026ebc[16] __asm__("_s_unmatched__else_10026ebc");
extern char grim_def_s_unmatched__end_10026ef0[16] __asm__("_s_unmatched__end_10026ef0");
/* 0x10026d14, 124 bytes */ GRIM_DATA("10026d14") grim_span_10026d14 grim_def_DAT_10026d14 __asm__("_DAT_10026d14") = {
    { 0x14, 0x01 },
    (void *)&grim_def_DAT_10026e3c,
    { 0x09, 0x01 },
    (void *)&grim_def_DAT_10026e34,
    { 0x06, 0x01 },
    (void *)&grim_def_DAT_10026e2c,
    { 0x07, 0x01 },
    (void *)&grim_def_DAT_10026e28,
    { 0x0c, 0x01 },
    (void *)&grim_def_s_function_10026e1c,
    { 0x0f, 0x01 },
    (void *)&grim_def_DAT_10026e18,
    { 0x04, 0x01 },
    (void *)&grim_def_DAT_10026e10,
    { 0x0e, 0x01 },
    (void *)&grim_def_s_nil_100266f8,
    { 0x03, 0x01 },
    (void *)&grim_def_DAT_10026e0c,
    { 0x1c, 0x01 },
    (void *)&grim_def_DAT_10026e08,
    { 0x15, 0x01 },
    (void *)&grim_def_DAT_10026e00,
    { 0x0a, 0x01 },
    (void *)&grim_def_DAT_10026df8,
    { 0x0d, 0x01 },
    (void *)&grim_def_DAT_10026df0,
    { 0x05, 0x01 },
    (void *)&grim_def_DAT_10026de8,
    { 0x0b, 0x01 },
    (void *)&grim_def_DAT_10026de0,
    { 0x08, 0x01 }
};
/* 0x10026d90, 4 bytes */ GRIM_DATA("10026d90") void *grim_def_g_pCheckcond_opts __asm__("_g_pCheckcond_opts") = (void *)&grim_def_s_nil_100266f8;
/* 0x10026d94, 12 bytes */ GRIM_DATA("10026d94") grim_span_10026d94 grim_def_PTR_DAT_10026d94 __asm__("_PTR_DAT_10026d94") = {
    (void *)&grim_def_DAT_10026ddc,
    {0}
};
/* 0x10026da0, 32 bytes */ GRIM_DATA("10026da0") void *grim_def_g_pInclinenumber_pragmas[8] __asm__("_g_pInclinenumber_pragmas") = {
    (void *)&grim_def_s_debug_10026bb4, (void *)&grim_def_s_nodebug_10026dd4, (void *)&grim_def_s_endinput_10026dc8, (void *)&grim_def_DAT_10026e28,
    (void *)&grim_def_s_ifnot_10026dc0, (void *)&grim_def_DAT_10026e18, (void *)&grim_def_DAT_10026e34, 0
};
/* 0x10026e44, 24 bytes */ GRIM_DATA("10026e44") char grim_def_s_input_ends_inside_a__if_10026e44[24] __asm__("_s_input_ends_inside_a__if_10026e44") = "input ends inside a $if";
/* 0x10026e5c, 56 bytes */ /* loose */ char grim_def_s_ambiguous_syntax__decimal_point_x_10026e5c[56] __asm__("_s_ambiguous_syntax__decimal_point_x_10026e5c") = "ambiguous syntax (decimal point x string concatenation)";
/* 0x10026e94, 24 bytes */ /* loose */ char grim_def_s_invalid_pragma_format_10026e94[24] __asm__("_s_invalid_pragma_format_10026e94") = "invalid pragma format";
/* 0x10026eac, 16 bytes */ /* loose */ char grim_def_s_unknown_pragma_10026eac[16] __asm__("_s_unknown_pragma_10026eac") = "unknown pragma";
/* 0x10026ebc, 16 bytes */ /* loose */ char grim_def_s_unmatched__else_10026ebc[16] __asm__("_s_unmatched__else_10026ebc") = "unmatched $else";
/* 0x10026ecc, 8 bytes */ /* loose */ char grim_def_s__else_10026ecc[8] __asm__("_s__else_10026ecc") = "$else";
/* 0x10026ed4, 24 bytes */ /* loose */ char grim_def_s_too_many_nested__ifs_10026ed4[24] __asm__("_s_too_many_nested__ifs_10026ed4") = "too many nested $ifs";
/* 0x10026eec, 4 bytes */ /* loose */ char grim_def_s__if_10026eec[4] __asm__("_s__if_10026eec") = "$if";
/* 0x10026ef0, 16 bytes */ /* loose */ char grim_def_s_unmatched__end_10026ef0[16] __asm__("_s_unmatched__end_10026ef0") = "unmatched $end";
/* 0x10026f00, 8 bytes */ /* loose */ char grim_def_s__end_10026f00[8] __asm__("_s__end_10026f00") = "$end";
/* 0x10026f08, 24 bytes */ /* loose */ char grim_def_s_invalid__if_condition_10026f08[24] __asm__("_s_invalid__if_condition_10026f08") = "invalid $if condition";
/* 0x10026f20, 16 bytes */ /* loose */ char grim_def_s_pragma_too_long_10026f20[16] __asm__("_s_pragma_too_long_10026f20") = "pragma too long";
