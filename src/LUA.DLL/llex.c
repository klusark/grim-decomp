/* LUA.DLL :: llex.c
 * functions 0x10005c00 .. 0x10007300 (33 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x10005c00  luaX_init ---- */
/* llex.c: interns the reserved words */

void luaX_init(void)

{
  undefined *puVar1;
  int iVar2;
  undefined **ppuVar3;
  
  ppuVar3 = (undefined **)&DAT_10026d14;
  do {
    iVar2 = luaS_new(ppuVar3[-1]);
    puVar1 = *ppuVar3;
    ppuVar3 = ppuVar3 + 2;
    *(undefined **)(iVar2 + 4) = puVar1;
  } while (ppuVar3 < &PTR_DAT_10026d94);
  return;
}

/* ---- 0x10005c30  luaX_setinput ---- */
/* Unidentified function of llex.c (lexer) */

void __cdecl luaX_setinput(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)PTR_1002bf6c[0x10];
  puVar1[3] = 0;
  puVar1[2] = 0;
  puVar1[5] = 0;
  puVar1[8] = 0;
  *puVar1 = 10;
  puVar1[6] = 1;
  puVar1[1] = param_1;
  llex__5c70((int)puVar1);
  luaL_resetbuffer();
  return;
}

/* ---- 0x10005c70  llex__5c70 ---- */
/* Unidentified function of llex.c (lexer) */

void __cdecl llex__5c70(int param_1)

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

/* ---- 0x10005cf0  luaX_save ---- */
/* save_and_next: appends the current char to the token buffer */

void luaX_save(void)

{
  luaL_addchar(0);
  lbuiltin__2da0();
  return;
}

/* ---- 0x10005d00  luaX_lex ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* llex.c: main tokenizer; numbers are returned through the float out-parameter */

uint __cdecl luaX_lex(float *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint *puVar2;
  double dVar3;
  uint uVar4;
  uint uVar5;
  float fVar6;
  int *piVar7;
  uint uVar8;
  longlong lVar9;
  undefined1 uVar10;
  #define local_10 (*(double *)(_frame + (0x20 - 0x10)))
  #define local_8 (*(double *)(_frame + (0x20 - 0x8)))
  
  puVar2 = (uint *)PTR_1002bf6c[0x10];
  luaL_resetbuffer();
  if (lua_debug != 0) {
    luaY_code_word(puVar2[3]);
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
      fVar6 = PUN(float,luaS_new(DAT_1002befc));
      if ((int)*(uint *)((int)fVar6 + 4) < 0x100) {
        *param_1 = fVar6;
        return 0x112;
      }
      return *(uint *)((int)fVar6 + 4);
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
      luaX_pragma(puVar2);
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
          lparser__a730();
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
      uVar4 = tolower(*puVar2);
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
        uVar4 = llex__6cb0(puVar2,param_1);
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
        luaY_error();
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
    fVar6 = PUN(float,luaS_new(DAT_1002befc + 1));
    *param_1 = fVar6;
    *(undefined1 *)(DAT_1002bf4c + -1 + DAT_1002bf40) = uVar10;
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
    luaX_pragma(puVar2);
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


/* ---- 0x10006890  luaX_pragma ---- */
/* llex.c: handles the $debug / $nodebug / $if pragmas */

void __cdecl luaX_pragma(uint *param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
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
  llex__6bb0(param_1,(int)local_18);
  iVar4 = luaO_findstring(local_18,&PTR_s_debug_10026da0);
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
  default:
    luaY_error();
    break;
  case 4:
    uVar5 = 1;
  case 5:
    if (param_1[5] == 4) {
      luaY_error();
    }
    llex__6bb0(param_1,(int)local_18);
    uVar3 = param_1[5];
    param_1[5] = uVar3 + 1;
    param_1[(uVar3 + 3) * 3] = 0;
    uVar3 = luaX_error(local_18);
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
      luaY_error();
    }
    param_1[(param_1[5] + 2) * 3] = 1;
    uVar2 = param_1[5];
    if ((param_1[uVar2 * 3 + 5] == 0) && (param_1[uVar2 * 3 + 7] == 0)) {
      param_1[uVar2 * 3 + 8] = 0;
    }
    else {
      param_1[uVar2 * 3 + 8] = 1;
    }
  }
  luaX_inclinenumber(param_1);
  if (*param_1 != 10) {
    if (*param_1 != 0xffffffff) {
      luaY_error();
    }
    llex__6c30(param_1);
    return;
  }
  luaX_pragma(param_1);
  llex__6c30(param_1);
  return;
}
#undef local_18


/* ---- 0x10006b10  luaX_inclinenumber ---- */
/* Unidentified function of llex.c (lexer) */

void __cdecl luaX_inclinenumber(uint *param_1)

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

/* ---- 0x10006b60  luaX_error ---- */
/* Unidentified function of llex.c (lexer) */

uint __cdecl luaX_error(byte *param_1)

{
  bool bVar1;
  uint uVar2;
  undefined3 extraout_var;
  
  uVar2 = luaO_findstring(param_1,&PTR_DAT_10026d90);
  if ((int)uVar2 < 0) {
    uVar2 = FUN_1000f5c0((uint)*param_1);
    if ((uVar2 == 0) && (*param_1 != 0x5f)) {
      luaY_error();
      return 0;
    }
    bVar1 = lstring__9550(param_1);
    uVar2 = ((uint)(bVar1));
  }
  return uVar2;
}

/* ---- 0x10006bb0  llex__6bb0 ---- */
/* Unidentified function of llex.c (lexer) */

void __cdecl llex__6bb0(uint *param_1,int param_2)

{
  byte bVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = 0;
  luaX_inclinenumber(param_1);
  while( true ) {
    uVar3 = FUN_1000f650(*param_1);
    if ((uVar3 == 0) && (*param_1 != 0x5f)) break;
    if (0x13 < iVar4) {
      *(undefined1 *)(param_2 + 0x14) = 0;
      luaY_error();
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

/* ---- 0x10006c30  llex__6c30 ---- */
/* Unidentified function of llex.c (lexer) */

void __cdecl llex__6c30(uint *param_1)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = param_1[param_1[5] * 3 + 8];
  while (uVar2 != 0) {
    if (*param_1 == 10) {
      luaX_pragma(param_1);
    }
    else if (*param_1 == 0xffffffff) {
      luaY_error();
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

/* ---- 0x10006cb0  llex__6cb0 ---- */
/* Unidentified function of llex.c (lexer) */

undefined4 __cdecl llex__6cb0(uint *param_1,undefined4 *param_2)

{
  byte bVar1;
  int *piVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar5 = 0;
LAB_10006cb8:
  uVar3 = *param_1;
  switch(uVar3) {
  default:
    goto LAB_10006d66;
  case 10:
    luaL_addchar(10);
    luaX_pragma(param_1);
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
    *(undefined1 *)(DAT_1002bf4c + -2 + DAT_1002bf40) = 0;
    uVar4 = luaS_new((byte *)(DAT_1002befc + 2));
    *param_2 = uVar4;
    *(undefined1 *)(DAT_1002bf4c + -2 + DAT_1002bf40) = 0x5d;
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

/* ---- 0x10006ea0  FUN_10006ea0 ---- */
void FUN_10006ea0(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define uStack_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  uStack_4 = luaL_check_number(1);
  if (uStack_4 < 0.0) {
    uStack_4 = -uStack_4;
  }
  lua_pushnumber(uStack_4);
  return;
}
#undef uStack_4


/* ---- 0x10006ee0  FUN_10006ee0 ---- */
void FUN_10006ee0(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = (float10)fsin((float10)fVar2 * (float10)0.017453292519943295);
  lua_pushnumber((float)fVar1);
  return;
}

/* ---- 0x10006f00  FUN_10006f00 ---- */
void FUN_10006f00(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = (float10)fcos((float10)fVar2 * (float10)0.017453292519943295);
  lua_pushnumber((float)fVar1);
  return;
}

/* ---- 0x10006f20  FUN_10006f20 ---- */
void FUN_10006f20(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = (float10)fptan((float10)fVar2 * (float10)0.017453292519943295);
  lua_pushnumber((float)fVar1);
  return;
}

/* ---- 0x10006f50  FUN_10006f50 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void FUN_10006f50(void)

{
  float fVar1;
  
  luaL_check_number(1);
  fVar1 = _CIsqrt();
  lua_pushnumber(fVar1 * 57.29578);
  return;
}
#endif


/* ---- 0x10006f80  FUN_10006f80 ---- */
void FUN_10006f80(void)

{
  float fVar1;
  
  luaL_check_number(1);
  fVar1 = FUN_10011e20();
  lua_pushnumber(fVar1 * 57.29578);
  return;
}

/* ---- 0x10006fb0  FUN_10006fb0 ---- */
void FUN_10006fb0(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = (float10)fpatan((float10)fVar2,(float10)1);
  lua_pushnumber((float)(fVar1 * (float10)57.29577951308232));
  return;
}

/* ---- 0x10006fe0  FUN_10006fe0 ---- */
void FUN_10006fe0(void)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  
  fVar2 = luaL_check_number(1);
  fVar3 = luaL_check_number(2);
  fVar1 = (float10)fpatan((float10)fVar2,(float10)fVar3);
  lua_pushnumber((float)(fVar1 * (float10)57.29577951308232));
  return;
}

/* ---- 0x10007020  FUN_10007020 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void FUN_10007020(void)

{
  float fVar1;
  
  fVar1 = luaL_check_number(1);
  fVar1 = floor(SUB84((double)fVar1,0),(uint)((ulonglong)(double)fVar1 >> 0x20));
  lua_pushnumber(fVar1);
  return;
}
#endif


/* ---- 0x10007050  FUN_10007050 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void FUN_10007050(void)

{
  float fVar1;
  
  fVar1 = luaL_check_number(1);
  fVar1 = ceil(SUB84((double)fVar1,0),(uint)((ulonglong)(double)fVar1 >> 0x20));
  lua_pushnumber(fVar1);
  return;
}
#endif


/* ---- 0x10007080  FUN_10007080 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void FUN_10007080(void)

{
  undefined4 extraout_ECX;
  float n;
  
  luaL_check_number(1);
  luaL_check_number(2);
  n = FUN_100120fa(extraout_ECX);
  lua_pushnumber(n);
  return;
}
#endif


/* ---- 0x100070c0  FUN_100070c0 ---- */
void FUN_100070c0(void)

{
  float fVar1;
  
  fVar1 = luaL_check_number(1);
  lua_pushnumber(SQRT(fVar1));
  return;
}

/* ---- 0x100070e0  FUN_100070e0 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void FUN_100070e0(void)

{
  float n;
  
  luaL_check_number(1);
  luaL_check_number(2);
  n = _CIpow();
  lua_pushnumber(n);
  return;
}
#endif


/* ---- 0x10007120  FUN_10007120 ---- */
void FUN_10007120(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = (float10)log2((float10)fVar2);
  lua_pushnumber((float)((float10)0.6931471805599453 * fVar1));
  return;
}

/* ---- 0x10007140  FUN_10007140 ---- */
void FUN_10007140(void)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = luaL_check_number(1);
  fVar1 = (float10)log2((float10)fVar2);
  lua_pushnumber((float)((float10)0.3010299956639812 * fVar1));
  return;
}

/* ---- 0x10007160  FUN_10007160 ---- */
void FUN_10007160(void)

{
  float10 fVar1;
  float10 fVar2;
  float fVar3;
  
  fVar3 = luaL_check_number(1);
  fVar1 = ROUND((float10)1.4426950408889634 * (float10)fVar3);
  fVar2 = (float10)f2xm1((float10)1.4426950408889634 * (float10)fVar3 - fVar1);
  fVar1 = (float10)fscale((float10)1 + fVar2,fVar1);
  lua_pushnumber((float)fVar1);
  return;
}

/* ---- 0x10007190  FUN_10007190 ---- */
void FUN_10007190(void)

{
  float fVar1;
  
  fVar1 = luaL_check_number(1);
  lua_pushnumber(fVar1 * 57.29578);
  return;
}

/* ---- 0x100071b0  FUN_100071b0 ---- */
void FUN_100071b0(void)

{
  float fVar1;
  
  fVar1 = luaL_check_number(1);
  lua_pushnumber(fVar1 * 0.017453292);
  return;
}

/* ---- 0x100071d0  FUN_100071d0 ---- */
void FUN_100071d0(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  #define fStack_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  fStack_4 = luaL_check_number(1);
  iVar2 = 2;
  iVar1 = lua_lua2C(2);
  while (iVar1 != 0) {
    fVar3 = luaL_check_number(iVar2);
    if (fVar3 < fStack_4) {
      fStack_4 = fVar3;
    }
    iVar2 = iVar2 + 1;
    iVar1 = lua_lua2C(iVar2);
  }
  lua_pushnumber(fStack_4);
  return;
}
#undef fStack_4


/* ---- 0x10007230  FUN_10007230 ---- */
void FUN_10007230(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  #define fStack_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  fStack_4 = luaL_check_number(1);
  iVar2 = 2;
  iVar1 = lua_lua2C(2);
  while (iVar1 != 0) {
    fVar3 = luaL_check_number(iVar2);
    if (fStack_4 < fVar3) {
      fStack_4 = fVar3;
    }
    iVar2 = iVar2 + 1;
    iVar1 = lua_lua2C(iVar2);
  }
  lua_pushnumber(fStack_4);
  return;
}
#undef fStack_4


/* ---- 0x10007290  FUN_10007290 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void FUN_10007290(void)

{
  uint uVar1;
  longlong lVar2;
  float fVar3;
  
  uVar1 = FUN_10012360();
  fVar3 = luaL_opt_number(1,0.0);
  if (fVar3 == 0.0) {
    lua_pushnumber((float)((int)uVar1 % 0x7fff) * 3.051851e-05);
    return;
  }
  lVar2 = _ftol();
  lua_pushnumber((float)((int)lVar2 + 1));
  return;
}
#endif


/* ---- 0x10007300  FUN_10007300 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void FUN_10007300(void)

{
  longlong lVar1;
  
  luaL_check_number(1);
  lVar1 = _ftol();
  FUN_10012350((int)lVar1);
  return;
}
#endif

