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

void __cdecl luaX_setinput(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)g_pLuaState[0x10];
  puVar1[3] = 0;
  puVar1[2] = 0;
  puVar1[5] = 0;
  puVar1[8] = 0;
  *puVar1 = 10;
  puVar1[6] = 1;
  puVar1[1] = param_1;
  firstline((int)puVar1);
  luaL_resetbuffer();
  return;
}

/* ---- 0x10005c70  firstline ---- */
/* Named firstline (not in the remaster, gcc inlined it there): Lua 3.1 source name (llex.c: skips a
   first line starting with '#', called by luaX_setinput); was llex__5c70. */

void __cdecl firstline(int param_1)

{
  int *piVar1;
  uint uVar2;
  
  **(int **)(param_1 + 4) = **(int **)(param_1 + 4) + -1;
  piVar1 = *(int **)(param_1 + 4);
  if (*piVar1 < 0) {
    uVar2 = (*(code *)piVar1[2])(piVar1);
  }
  else {
    uVar2 = (uint)*(byte *)piVar1[1];
    piVar1[1] = (int)((byte *)piVar1[1] + 1);
  }
  if (uVar2 == 0x23) {
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
    do {
      **(int **)(param_1 + 4) = **(int **)(param_1 + 4) + -1;
      piVar1 = *(int **)(param_1 + 4);
      if (*piVar1 < 0) {
        uVar2 = (*(code *)piVar1[2])(piVar1);
      }
      else {
        uVar2 = (uint)*(byte *)piVar1[1];
        piVar1[1] = (int)((byte *)piVar1[1] + 1);
      }
    } while ((uVar2 != 10) && (uVar2 != 0xffffffff));
  }
  **(int **)(param_1 + 4) = **(int **)(param_1 + 4) + 1;
  *(int *)(*(int *)(param_1 + 4) + 4) = *(int *)(*(int *)(param_1 + 4) + 4) + -1;
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* llex.c: main tokenizer; numbers are returned through the float out-parameter Original name
   luaY_lex (the remaster's libLua.so: string 'ambiguous syntax (decimal point x string
   concatenation)' (the bison yylex renamed luaY_lex)); was luaX_lex. */

uint __cdecl luaY_lex(float *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint *puVar2;
  double dVar3;
  uint uVar4;
  uint uVar5;
  TaggedString *pTVar6;
  int *piVar7;
  uint uVar8;
  longlong lVar9;
  undefined1 uVar10;
  #define local_10 (*(double *)(_frame + (0x20 - 0x10)))
  #define local_8 (*(double *)(_frame + (0x20 - 0x8)))
  
  puVar2 = (uint *)g_pLuaState[0x10];
  luaL_resetbuffer();
  if (lua_debug != 0) {
    luaY_codedebugline(puVar2[3]);
  }
  puVar2[3] = puVar2[2];
  do {
    switch(*puVar2) {
    default:
      if ((*puVar2 != 0x5f) && (uVar4 = FUN_1000f5c0(*puVar2), uVar4 == 0)) {
        uVar4 = *puVar2;
        luaL_addchar((char)uVar4);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar5 = (*(code *)piVar7[2])(piVar7);
          *puVar2 = uVar5;
          return uVar4;
        }
        bVar1 = *(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
        *puVar2 = (uint)bVar1;
        return uVar4;
      }
      do {
        luaL_addchar((char)*puVar2);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar4 = (*(code *)piVar7[2])(piVar7);
        }
        else {
          uVar4 = (uint)*(byte *)piVar7[1];
          piVar7[1] = (int)((byte *)piVar7[1] + 1);
        }
        *puVar2 = uVar4;
        uVar4 = FUN_1000f650(uVar4);
      } while ((uVar4 != 0) || (*puVar2 == 0x5f));
      luaL_addchar(0);
      pTVar6 = luaS_new(g_dwLState_Mbuffbase);
      if (pTVar6->nMarked < 0x100) {
        *param_1 = PUN(float,pTVar6);
        return 0x112;
      }
      return pTVar6->nMarked;
    case 9:
    case 0xd:
    case 0x20:
      *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
      piVar7 = (int *)puVar2[1];
      if (*piVar7 < 0) {
        uVar4 = (*(code *)piVar7[2])(piVar7);
        *puVar2 = uVar4;
      }
      else {
        bVar1 = *(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
        *puVar2 = (uint)bVar1;
      }
      break;
    case 10:
      inclinenumber(puVar2);
      puVar2[3] = puVar2[2];
      break;
    case 0x22:
    case 0x27:
      uVar4 = *puVar2;
      uVar10 = (undefined1)uVar4;
      luaL_addchar(uVar10);
      *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
      piVar7 = (int *)puVar2[1];
      if (*piVar7 < 0) {
        uVar5 = (*(code *)piVar7[2])(piVar7);
      }
      else {
        uVar5 = (uint)*(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
      }
      *puVar2 = uVar5;
      goto joined_r0x100060f4;
    case 0x2d:
      luaL_addchar((char)*puVar2);
      *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
      piVar7 = (int *)puVar2[1];
      if (*piVar7 < 0) {
        uVar4 = (*(code *)piVar7[2])(piVar7);
      }
      else {
        uVar4 = (uint)*(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
      }
      *puVar2 = uVar4;
      if (uVar4 != 0x2d) {
        return 0x2d;
      }
      do {
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar4 = (*(code *)piVar7[2])(piVar7);
        }
        else {
          uVar4 = (uint)*(byte *)piVar7[1];
          piVar7[1] = (int)((byte *)piVar7[1] + 1);
        }
        *puVar2 = uVar4;
      } while ((uVar4 != 10) && (uVar4 != 0xffffffff));
      luaL_resetbuffer();
      break;
    case 0x2e:
      luaL_addchar((char)*puVar2);
      *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
      piVar7 = (int *)puVar2[1];
      if (*piVar7 < 0) {
        uVar4 = (*(code *)piVar7[2])(piVar7);
      }
      else {
        uVar4 = (uint)*(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
      }
      *puVar2 = uVar4;
      if (uVar4 == 0x2e) {
        luaL_addchar(0x2e);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar4 = (*(code *)piVar7[2])(piVar7);
        }
        else {
          uVar4 = (uint)*(byte *)piVar7[1];
          piVar7[1] = (int)((byte *)piVar7[1] + 1);
        }
        *puVar2 = uVar4;
        if (uVar4 != 0x2e) {
          return 0x11a;
        }
        luaL_addchar(0x2e);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar4 = (*(code *)piVar7[2])(piVar7);
          *puVar2 = uVar4;
          return 0x110;
        }
        bVar1 = *(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
        *puVar2 = (uint)bVar1;
        return 0x110;
      }
      uVar4 = FUN_1000f5f0(uVar4);
      if (uVar4 == 0) {
        return 0x2e;
      }
      local_8 = 0.0;
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
      local_8 = 0.0;
      do {
        local_8 = (double)(int)(*puVar2 - 0x30) - local_8 * -10.0;
        luaL_addchar((char)*puVar2);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar4 = (*(code *)piVar7[2])(piVar7);
        }
        else {
          uVar4 = (uint)*(byte *)piVar7[1];
          piVar7[1] = (int)((byte *)piVar7[1] + 1);
        }
        *puVar2 = uVar4;
        uVar4 = FUN_1000f5f0(uVar4);
      } while (uVar4 != 0);
      if (*puVar2 == 0x2e) {
        luaL_addchar(0x2e);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar4 = (*(code *)piVar7[2])(piVar7);
        }
        else {
          uVar4 = (uint)*(byte *)piVar7[1];
          piVar7[1] = (int)((byte *)piVar7[1] + 1);
        }
        *puVar2 = uVar4;
        if (uVar4 == 0x2e) {
          luaL_addchar(0);
          luaY_error(s_ambiguous_syntax__decimal_point_x_10026e5c);
        }
      }
LAB_10006398:
      local_10 = 0.1;
      for (uVar4 = FUN_1000f5f0(*puVar2); uVar4 != 0; uVar4 = FUN_1000f5f0(uVar4)) {
        local_8 = (double)(int)(*puVar2 - 0x30) * local_10 + local_8;
        local_10 = local_10 * 0.1;
        luaL_addchar((char)*puVar2);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar4 = (*(code *)piVar7[2])(piVar7);
        }
        else {
          uVar4 = (uint)*(byte *)piVar7[1];
          piVar7[1] = (int)((byte *)piVar7[1] + 1);
        }
        *puVar2 = uVar4;
      }
      uVar4 = toupper(*puVar2);
      if (uVar4 != 0x45) {
LAB_10006563:
        *param_1 = (float)local_8;
        return 0x111;
      }
      luaL_addchar((char)*puVar2);
      *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
      piVar7 = (int *)puVar2[1];
      if (*piVar7 < 0) {
        uVar4 = (*(code *)piVar7[2])(piVar7);
      }
      else {
        uVar4 = (uint)*(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
      }
      *puVar2 = uVar4;
      if ((uVar4 == 0x2b) || (uVar4 == 0x2d)) {
        luaL_addchar((char)uVar4);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar5 = (*(code *)piVar7[2])(piVar7);
        }
        else {
          uVar5 = (uint)*(byte *)piVar7[1];
          piVar7[1] = (int)((byte *)piVar7[1] + 1);
        }
        *puVar2 = uVar5;
      }
      uVar5 = FUN_1000f5f0(*puVar2);
      if (uVar5 != 0) {
        do {
          uVar5 = *puVar2;
          lVar9 = _ftol();
          uVar8 = (uint)lVar9;
          luaL_addchar((char)uVar5);
          *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
          piVar7 = (int *)puVar2[1];
          if (*piVar7 < 0) {
            uVar5 = (*(code *)piVar7[2])(piVar7);
          }
          else {
            uVar5 = (uint)*(byte *)piVar7[1];
            piVar7[1] = (int)((byte *)piVar7[1] + 1);
          }
          *puVar2 = uVar5;
          uVar5 = FUN_1000f5f0(uVar5);
        } while (uVar5 != 0);
        if (uVar4 == 0x2d) {
          dVar3 = 0.1;
        }
        else {
          dVar3 = 10.0;
        }
        for (; 0 < (int)uVar8; uVar8 = (int)uVar8 >> 1) {
          if ((uVar8 & 1) != 0) {
            local_8 = dVar3 * local_8;
          }
          dVar3 = dVar3 * dVar3;
        }
        goto LAB_10006563;
      }
      goto LAB_100064b9;
    case 0x3c:
      luaL_addchar((char)*puVar2);
      *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
      piVar7 = (int *)puVar2[1];
      if (*piVar7 < 0) {
        uVar4 = (*(code *)piVar7[2])(piVar7);
      }
      else {
        uVar4 = (uint)*(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
      }
      *puVar2 = uVar4;
      if (uVar4 == 0x3d) {
        luaL_addchar(0x3d);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar4 = (*(code *)piVar7[2])(piVar7);
          *puVar2 = uVar4;
          return 0x118;
        }
        bVar1 = *(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
        *puVar2 = (uint)bVar1;
        return 0x118;
      }
      return 0x3c;
    case 0x3d:
      luaL_addchar((char)*puVar2);
      *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
      piVar7 = (int *)puVar2[1];
      if (*piVar7 < 0) {
        uVar4 = (*(code *)piVar7[2])(piVar7);
      }
      else {
        uVar4 = (uint)*(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
      }
      *puVar2 = uVar4;
      if (uVar4 == 0x3d) {
        luaL_addchar(0x3d);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar4 = (*(code *)piVar7[2])(piVar7);
          *puVar2 = uVar4;
          return 0x116;
        }
        bVar1 = *(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
        *puVar2 = (uint)bVar1;
        return 0x116;
      }
      return 0x3d;
    case 0x3e:
      luaL_addchar((char)*puVar2);
      *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
      piVar7 = (int *)puVar2[1];
      if (*piVar7 < 0) {
        uVar4 = (*(code *)piVar7[2])(piVar7);
      }
      else {
        uVar4 = (uint)*(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
      }
      *puVar2 = uVar4;
      if (uVar4 == 0x3d) {
        luaL_addchar(0x3d);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar4 = (*(code *)piVar7[2])(piVar7);
          *puVar2 = uVar4;
          return 0x119;
        }
        bVar1 = *(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
        *puVar2 = (uint)bVar1;
        return 0x119;
      }
      return 0x3e;
    case 0x5b:
      luaL_addchar((char)*puVar2);
      *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
      piVar7 = (int *)puVar2[1];
      if (*piVar7 < 0) {
        uVar4 = (*(code *)piVar7[2])(piVar7);
      }
      else {
        uVar4 = (uint)*(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
      }
      *puVar2 = uVar4;
      if (uVar4 == 0x5b) {
        luaL_addchar(0x5b);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar4 = (*(code *)piVar7[2])(piVar7);
        }
        else {
          uVar4 = (uint)*(byte *)piVar7[1];
          piVar7[1] = (int)((byte *)piVar7[1] + 1);
        }
        *puVar2 = uVar4;
        uVar4 = read_long_string(puVar2,param_1);
        return uVar4;
      }
      return 0x5b;
    case 0x7e:
      luaL_addchar((char)*puVar2);
      *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
      piVar7 = (int *)puVar2[1];
      if (*piVar7 < 0) {
        uVar4 = (*(code *)piVar7[2])(piVar7);
      }
      else {
        uVar4 = (uint)*(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
      }
      *puVar2 = uVar4;
      if (uVar4 == 0x3d) {
        luaL_addchar(0x3d);
        *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
        piVar7 = (int *)puVar2[1];
        if (*piVar7 < 0) {
          uVar4 = (*(code *)piVar7[2])(piVar7);
          *puVar2 = uVar4;
          return 0x117;
        }
        bVar1 = *(byte *)piVar7[1];
        piVar7[1] = (int)((byte *)piVar7[1] + 1);
        *puVar2 = (uint)bVar1;
        return 0x117;
      }
      return 0x7e;
    case 0xffffffff:
      luaL_addchar(0);
      if (0 < (int)puVar2[5]) {
        luaY_syntaxerror(s_input_ends_inside_a__if_10026e44,&DAT_1002bedc);
      }
      return 0;
    }
  } while( true );
joined_r0x100060f4:
  if (uVar5 == uVar4) {
    *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
    piVar7 = (int *)puVar2[1];
    if (*piVar7 < 0) {
      uVar4 = (*(code *)piVar7[2])(piVar7);
    }
    else {
      uVar4 = (uint)*(byte *)piVar7[1];
      piVar7[1] = (int)((byte *)piVar7[1] + 1);
    }
    *puVar2 = uVar4;
    luaL_addchar(0);
    pTVar6 = luaS_new(g_dwLState_Mbuffbase + 1);
    *param_1 = PUN(float,pTVar6);
    *(undefined1 *)(g_dwLState_Mbuffnext + -1 + g_dwLState_Mbuffer) = uVar10;
    return 0x113;
  }
  uVar5 = *puVar2;
  if ((uVar5 == 0xffffffff) || (uVar5 == 10)) {
LAB_100064b9:
    luaL_addchar(0);
    return 0x102;
  }
  if (uVar5 != 0x5c) {
    luaL_addchar((char)uVar5);
    *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
    piVar7 = (int *)puVar2[1];
    if (*piVar7 < 0) goto LAB_10006238;
    uVar5 = (uint)*(byte *)piVar7[1];
    piVar7[1] = (int)((byte *)piVar7[1] + 1);
    goto LAB_1000623f;
  }
  *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
  piVar7 = (int *)puVar2[1];
  if (*piVar7 < 0) {
    uVar5 = (*(code *)piVar7[2])(piVar7);
  }
  else {
    uVar5 = (uint)*(byte *)piVar7[1];
    piVar7[1] = (int)((byte *)piVar7[1] + 1);
  }
  *puVar2 = uVar5;
  switch(uVar5) {
  case 10:
    luaL_addchar(10);
    inclinenumber(puVar2);
    goto LAB_10006241;
  default:
    luaL_addchar((char)uVar5);
    *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
    piVar7 = (int *)puVar2[1];
    if (*piVar7 < 0) {
LAB_10006238:
      uVar5 = (*(code *)piVar7[2])(piVar7);
    }
    else {
      uVar5 = (uint)*(byte *)piVar7[1];
      piVar7[1] = (int)((byte *)piVar7[1] + 1);
    }
    break;
  case 0x6e:
    luaL_addchar(10);
    *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
    piVar7 = (int *)puVar2[1];
    if (*piVar7 < 0) goto LAB_10006238;
    uVar5 = (uint)*(byte *)piVar7[1];
    piVar7[1] = (int)((byte *)piVar7[1] + 1);
    break;
  case 0x72:
    luaL_addchar(0xd);
    *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
    piVar7 = (int *)puVar2[1];
    if (*piVar7 < 0) goto LAB_10006238;
    uVar5 = (uint)*(byte *)piVar7[1];
    piVar7[1] = (int)((byte *)piVar7[1] + 1);
    break;
  case 0x74:
    luaL_addchar(9);
    *(int *)puVar2[1] = *(int *)puVar2[1] + -1;
    piVar7 = (int *)puVar2[1];
    if (*piVar7 < 0) goto LAB_10006238;
    uVar5 = (uint)*(byte *)piVar7[1];
    piVar7[1] = (int)((byte *)piVar7[1] + 1);
  }
LAB_1000623f:
  *puVar2 = uVar5;
LAB_10006241:
  uVar5 = *puVar2;
  goto joined_r0x100060f4;
}
#undef local_10
#undef local_8

#endif


/* ---- 0x10006890  inclinenumber ---- */
/* llex.c: handles the $debug / $nodebug / $if pragmas Original name inclinenumber (the remaster's
   libLua.so: static inclinenumber(LexState*): the pragma strings ('unknown pragma', 'too many
   nested $ifs', 'unmatched $else'); the remaster's static table inclinenumber::pragmas); was
   luaX_pragma. */

void __cdecl inclinenumber(uint *param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *msg;
  byte *token;
  #define local_18 (*(byte (*)[24])(_frame + (0x30 - 0x18)))
  
  *(int *)param_1[1] = *(int *)param_1[1] + -1;
  piVar1 = (int *)param_1[1];
  if (*piVar1 < 0) {
    uVar2 = (*(code *)piVar1[2])(piVar1);
  }
  else {
    uVar2 = (uint)*(byte *)piVar1[1];
    piVar1[1] = (int)((byte *)piVar1[1] + 1);
  }
  *param_1 = uVar2;
  param_1[2] = param_1[2] + 1;
  if (uVar2 != 0x24) {
    return;
  }
  uVar5 = 0;
  uVar2 = param_1[param_1[5] * 3 + 8];
  *(int *)param_1[1] = *(int *)param_1[1] + -1;
  piVar1 = (int *)param_1[1];
  if (*piVar1 < 0) {
    uVar3 = (*(code *)piVar1[2])(piVar1);
  }
  else {
    uVar3 = (uint)*(byte *)piVar1[1];
    piVar1[1] = (int)((byte *)piVar1[1] + 1);
  }
  *param_1 = uVar3;
  readname(param_1,(int)local_18);
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
      *param_1 = 0xffffffff;
      param_1[5] = 0;
    }
    break;
  case 3:
    uVar2 = param_1[5];
    param_1[5] = uVar2 - 1;
    if (uVar2 != 0) break;
    token = &DAT_10026f00;
    msg = s_unmatched__end_10026ef0;
    goto LAB_10006a8e;
  case 4:
    uVar5 = 1;
  case 5:
    if (param_1[5] == 4) {
      luaY_syntaxerror(s_too_many_nested__ifs_10026ed4,&DAT_10026eec);
    }
    readname(param_1,(int)local_18);
    uVar3 = param_1[5];
    param_1[5] = uVar3 + 1;
    param_1[(uVar3 + 3) * 3] = 0;
    uVar3 = checkcond(local_18);
    if (uVar3 != 0) {
      uVar5 = (uint)(uVar5 == 0);
    }
    param_1[param_1[5] * 3 + 7] = uVar5;
    if ((uVar2 == 0) && (param_1[param_1[5] * 3 + 7] != 0)) {
      param_1[param_1[5] * 3 + 8] = 0;
    }
    else {
      param_1[param_1[5] * 3 + 8] = 1;
    }
    break;
  case 6:
    if (param_1[(param_1[5] + 2) * 3] != 0) {
      luaY_syntaxerror(s_unmatched__else_10026ebc,s__else_10026ecc);
    }
    param_1[(param_1[5] + 2) * 3] = 1;
    uVar2 = param_1[5];
    if ((param_1[uVar2 * 3 + 5] == 0) && (param_1[uVar2 * 3 + 7] == 0)) {
      param_1[uVar2 * 3 + 8] = 0;
    }
    else {
      param_1[uVar2 * 3 + 8] = 1;
    }
    break;
  default:
    token = local_18;
    msg = s_unknown_pragma_10026eac;
LAB_10006a8e:
    luaY_syntaxerror(msg,(char *)token);
  }
  skipspace(param_1);
  if (*param_1 != 10) {
    if (*param_1 != 0xffffffff) {
      luaY_syntaxerror(s_invalid_pragma_format_10026e94,(char *)local_18);
    }
    ifskip(param_1);
    return;
  }
  inclinenumber(param_1);
  ifskip(param_1);
  return;
}
#undef local_18


/* ---- 0x10006b10  skipspace ---- */
/* Original name skipspace (the remaster's libLua.so: static skipspace(LexState*): skips blanks,
   tabs and CRs); was luaX_inclinenumber. */

void __cdecl skipspace(uint *param_1)

{
  byte bVar1;
  int *piVar2;
  uint uVar3;
  
  while (((uVar3 = *param_1, uVar3 == 0x20 || (uVar3 == 9)) || (uVar3 == 0xd))) {
    *(int *)param_1[1] = *(int *)param_1[1] + -1;
    piVar2 = (int *)param_1[1];
    if (*piVar2 < 0) {
      uVar3 = (*(code *)piVar2[2])(piVar2);
      *param_1 = uVar3;
    }
    else {
      bVar1 = *(byte *)piVar2[1];
      piVar2[1] = (int)((byte *)piVar2[1] + 1);
      *param_1 = (uint)bVar1;
    }
  }
  return;
}

/* ---- 0x10006b60  checkcond ---- */
/* Original name checkcond (the remaster's libLua.so: the remaster's static table checkcond::opts;
   string 'invalid $if condition'); was luaX_error. */

uint __cdecl checkcond(byte *param_1)

{
  uint uVar1;
  
  uVar1 = luaO_findstring(param_1,&g_pCheckcond_opts);
  if ((int)uVar1 < 0) {
    uVar1 = FUN_1000f5c0((uint)*param_1);
    if ((uVar1 == 0) && (*param_1 != 0x5f)) {
      luaY_syntaxerror(s_invalid__if_condition_10026f08,(char *)param_1);
      return 0;
    }
    uVar1 = luaS_globaldefined((char *)param_1);
  }
  return uVar1;
}

/* ---- 0x10006bb0  readname ---- */
/* Original name readname (the remaster's libLua.so: static readname(LexState*, char*): string
   'pragma too long'); was llex__6bb0. */

void __cdecl readname(uint *param_1,int param_2)

{
  byte bVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = 0;
  skipspace(param_1);
  while( true ) {
    uVar3 = FUN_1000f650(*param_1);
    if ((uVar3 == 0) && (*param_1 != 0x5f)) break;
    if (0x13 < iVar4) {
      *(undefined1 *)(param_2 + 0x14) = 0;
      luaY_syntaxerror(s_pragma_too_long_10026f20,(char *)param_2);
    }
    *(char *)(iVar4 + param_2) = (char)*param_1;
    iVar4 = iVar4 + 1;
    *(int *)param_1[1] = *(int *)param_1[1] + -1;
    piVar2 = (int *)param_1[1];
    if (*piVar2 < 0) {
      uVar3 = (*(code *)piVar2[2])(piVar2);
      *param_1 = uVar3;
    }
    else {
      bVar1 = *(byte *)piVar2[1];
      piVar2[1] = (int)((byte *)piVar2[1] + 1);
      *param_1 = (uint)bVar1;
    }
  }
  *(undefined1 *)(iVar4 + param_2) = 0;
  return;
}

/* ---- 0x10006c30  ifskip ---- */
/* Named ifskip (not in the remaster, gcc inlined it there): Lua 3.1 source name (llex.c: skips
   input while the $if level is false, 'input ends inside a $if'); was llex__6c30. */

void __cdecl ifskip(uint *param_1)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = param_1[param_1[5] * 3 + 8];
  while (uVar2 != 0) {
    if (*param_1 == 10) {
      inclinenumber(param_1);
    }
    else if (*param_1 == 0xffffffff) {
      luaY_syntaxerror(s_input_ends_inside_a__if_10026e44,&DAT_1002bedc);
    }
    else {
      *(int *)param_1[1] = *(int *)param_1[1] + -1;
      piVar1 = (int *)param_1[1];
      if (*piVar1 < 0) {
        uVar2 = (*(code *)piVar1[2])(piVar1);
      }
      else {
        uVar2 = (uint)*(byte *)piVar1[1];
        piVar1[1] = (int)((byte *)piVar1[1] + 1);
      }
      *param_1 = uVar2;
    }
    uVar2 = param_1[param_1[5] * 3 + 8];
  }
  return;
}

/* ---- 0x10006cb0  read_long_string ---- */
/* Named read_long_string (not in the remaster, gcc inlined it there): Lua 3.1 source name (llex.c:
   [[ ... ]] strings with nesting, called by luaY_lex); was llex__6cb0. */

undefined4 __cdecl read_long_string(uint *param_1,undefined4 *param_2)

{
  byte bVar1;
  int *piVar2;
  uint uVar3;
  TaggedString *pTVar4;
  int iVar5;
  
  iVar5 = 0;
LAB_10006cb8:
  uVar3 = *param_1;
  switch(uVar3) {
  default:
    goto LAB_10006d66;
  case 10:
    luaL_addchar(10);
    inclinenumber(param_1);
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
  *(int *)param_1[1] = *(int *)param_1[1] + -1;
  piVar2 = (int *)param_1[1];
  if (*piVar2 < 0) {
    uVar3 = (*(code *)piVar2[2])(piVar2);
  }
  else {
    uVar3 = (uint)*(byte *)piVar2[1];
    piVar2[1] = (int)((byte *)piVar2[1] + 1);
  }
  *param_1 = uVar3;
  if (uVar3 != 0x5d) goto LAB_10006cb8;
  if (iVar5 == 0) {
    luaL_addchar(0x5d);
    *(int *)param_1[1] = *(int *)param_1[1] + -1;
    piVar2 = (int *)param_1[1];
    if (*piVar2 < 0) {
      uVar3 = (*(code *)piVar2[2])(piVar2);
    }
    else {
      uVar3 = (uint)*(byte *)piVar2[1];
      piVar2[1] = (int)((byte *)piVar2[1] + 1);
    }
    *param_1 = uVar3;
    *(undefined1 *)(g_dwLState_Mbuffnext + -2 + g_dwLState_Mbuffer) = 0;
    pTVar4 = luaS_new((char *)(g_dwLState_Mbuffbase + 2));
    *param_2 = pTVar4;
    *(undefined1 *)(g_dwLState_Mbuffnext + -2 + g_dwLState_Mbuffer) = 0x5d;
    return 0x113;
  }
  iVar5 = iVar5 + -1;
  uVar3 = 0x5d;
LAB_10006d66:
  luaL_addchar((char)uVar3);
  *(int *)param_1[1] = *(int *)param_1[1] + -1;
  piVar2 = (int *)param_1[1];
  if (*piVar2 < 0) {
    uVar3 = (*(code *)piVar2[2])(piVar2);
    *param_1 = uVar3;
  }
  else {
    bVar1 = *(byte *)piVar2[1];
    piVar2[1] = (int)((byte *)piVar2[1] + 1);
    *param_1 = (uint)bVar1;
  }
  goto LAB_10006cb8;
switchD_10006cce_caseD_5b:
  luaL_addchar((char)uVar3);
  *(int *)param_1[1] = *(int *)param_1[1] + -1;
  piVar2 = (int *)param_1[1];
  if (*piVar2 < 0) {
    uVar3 = (*(code *)piVar2[2])(piVar2);
  }
  else {
    uVar3 = (uint)*(byte *)piVar2[1];
    piVar2[1] = (int)((byte *)piVar2[1] + 1);
  }
  *param_1 = uVar3;
  if (uVar3 != 0x5b) goto LAB_10006cb8;
  iVar5 = iVar5 + 1;
  uVar3 = 0x5b;
  goto LAB_10006d66;
}
