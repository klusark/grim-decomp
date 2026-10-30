/* LUA.DLL :: lparser.c
 * functions 0x1000a6f0 .. 0x1000c100 (48 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000a6f0  luaY_error ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* lua.stx: 'last token read: %50s' error */

void __cdecl luaY_error(char *msg,char *token)

{
  if (*token == '\0') {
    token = s__eof__10027b00;
  }
  luaL_verror(s___100s__last_token_read_____50s__10027ac4,msg,token,
              *(undefined4 *)(PTR_1002bf6c[0x10] + 8),
              *(int *)(*(int *)PTR_1002bf6c[0xe] + 0x18) + 0x18);
  return;
}
#endif


/* ---- 0x1000a730  lparser__a730 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__a730(char *msg)

{
  char *token;
  
  token = (char *)((code *)luaX_save)();
  luaY_error(msg,token);
  return;
}
#endif


/* ---- 0x1000a750  luaY_code_word ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl luaY_code_word(uint param_1)

{
  if ((lua_debug != 0) && (param_1 != *(uint *)(PTR_1002bf6c[0x10] + 0x10))) {
    luaY_code_opcode_arg('|',0,param_1,0);
    *(uint *)(PTR_1002bf6c[0x10] + 0x10) = param_1;
  }
  return;
}

/* ---- 0x1000a790  luaY_code_opcode_arg ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl luaY_code_opcode_arg(char param_1,int param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  luaY_code_byte(3);
  iVar1 = PTR_1002bf6c[0xf];
  iVar2 = lparser__a810(*(int *)(iVar1 + 4),param_1,param_2,param_3,param_4);
  *(int *)(iVar1 + 4) = *(int *)(iVar1 + 4) + iVar2;
  return;
}

/* ---- 0x1000a7d0  luaY_code_byte ---- */
/* lua.stx: code size overflow */

void __cdecl luaY_code_byte(int param_1)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = (int *)PTR_1002bf6c[0xf];
  if (piVar1[0x27] < piVar1[1] + param_1) {
    uVar2 = luaM_growaux((undefined4 *)(*piVar1 + 0x10),piVar1[0x27],1,
                         (byte *)s_code_size_overflow_10027b08,0x7ffffffd);
    piVar1[0x27] = uVar2;
  }
  return;
}

/* ---- 0x1000a810  lparser__a810 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

undefined4 __cdecl lparser__a810(int param_1,char param_2,int param_3,uint param_4,int param_5)

{
  int iVar1;
  char cVar2;
  
  iVar1 = *(int *)(*(int *)PTR_1002bf6c[0xf] + 0x10);
  lparser__a8b0(param_5);
  cVar2 = (char)param_4;
  if ((int)param_4 < param_3) {
    *(char *)(iVar1 + param_1) = cVar2 + param_2 + '\x01';
    return 1;
  }
  if ((int)param_4 < 0x100) {
    *(char *)(iVar1 + param_1) = param_2;
    *(char *)(iVar1 + 1 + param_1) = cVar2;
    return 2;
  }
  if (param_4 < 0xffff) {
    *(char *)(iVar1 + param_1) = (char)param_3 + param_2 + '\x01';
    *(char *)(iVar1 + 1 + param_1) = cVar2;
    *(char *)(iVar1 + 2 + param_1) = (char)(param_4 >> 8);
    return 3;
  }
  lparser__a730(s_code_too_long__limit_64K__10027b1c);
  return 0;
}

/* ---- 0x1000a8b0  lparser__a8b0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__a8b0(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = PTR_1002bf6c[0xf];
  iVar2 = *(int *)(iVar1 + 0x88) + param_1;
  *(int *)(iVar1 + 0x88) = iVar2;
  if (*(int *)(iVar1 + 0x8c) < iVar2) {
    if (0xff < iVar2) {
      lparser__a730(s_function_expression_too_complex_10027b38);
    }
    *(undefined4 *)(iVar1 + 0x8c) = *(undefined4 *)(iVar1 + 0x88);
  }
  return;
}

/* ---- 0x1000a900  luaY_parser ---- */
int __cdecl luaY_parser(int param_1)

{
  unsigned char _frame[0x8e0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  #define local_8c4 (*(undefined1 (*)[84])(_frame + (0x8e0 - 0x8c4)))
  #define local_870 (*(undefined1 (*)[2160])(_frame + (0x8e0 - 0x870)))
  
                    /* 0xa900  4  luaY_parser */
  PTR_1002bf6c[0xe] = (int)local_870;
  PTR_1002bf6c[0xf] = PTR_1002bf6c[0xe];
  PTR_1002bf6c[0x10] = (int)local_8c4;
  luaX_setinput(param_1);
  uVar1 = luaS_new(*(byte **)(param_1 + 0x10));
  lparser__a980(uVar1);
  iVar2 = yyparse();
  if (iVar2 != 0) {
    lua_error((byte *)s_parse_error_10027b58);
  }
  iVar2 = luaY_syntaxerror();
  return iVar2;
}
#undef local_870
#undef local_8c4


/* ---- 0x1000a980  lparser__a980 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__a980(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = luaF_newclosure();
  puVar1 = (undefined4 *)PTR_1002bf6c[0xf];
  puVar1[0x22] = 0;
  puVar1[0x23] = 0;
  puVar1[0x24] = 0;
  puVar1[0x25] = 0;
  *puVar1 = puVar2;
  puVar2[6] = param_1;
  puVar1[1] = 0;
  puVar1[0x27] = 0;
  puVar2[4] = 0;
  puVar1[0x29] = 0;
  if (lua_debug == 0) {
    puVar1[0x28] = 0xffffffff;
  }
  else {
    puVar1[0x26] = 0;
    puVar1[0x28] = 0;
  }
  lparser__aa10(0);
  lparser__aa10(0);
  *(undefined4 *)(PTR_1002bf6c[0x10] + 0x10) = 0;
  return;
}

/* ---- 0x1000aa10  lparser__aa10 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__aa10(undefined1 param_1)

{
  luaY_code_byte(1);
  *(undefined1 *)(((int *)PTR_1002bf6c[0xf])[1] + *(int *)(*(int *)PTR_1002bf6c[0xf] + 0x10)) =
       param_1;
  *(int *)(PTR_1002bf6c[0xf] + 4) = *(int *)(PTR_1002bf6c[0xf] + 4) + 1;
  return;
}

/* ---- 0x1000aa40  luaY_syntaxerror ---- */
/* lua.stx: lua.stx error reporting */

int luaY_syntaxerror(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)PTR_1002bf6c[0xf];
  lparser__ab20(0);
  **(undefined1 **)(iVar1 + 0x10) = *(undefined1 *)(PTR_1002bf6c[0xf] + 0x8c);
  uVar2 = (**(code **)(DAT_1002beb8 + 0x28))
                    (*(undefined4 *)(iVar1 + 0x10),*(undefined4 *)(PTR_1002bf6c[0xf] + 4),
                     s_lua_stx_10027b64,0x25c);
  *(undefined4 *)(iVar1 + 0x10) = uVar2;
  uVar2 = (**(code **)(DAT_1002beb8 + 0x28))
                    (*(undefined4 *)(iVar1 + 8),*(int *)(iVar1 + 0xc) << 3,s_lua_stx_10027b64,0x25d)
  ;
  *(undefined4 *)(iVar1 + 8) = uVar2;
  if (*(int *)(PTR_1002bf6c[0xf] + 0xa0) != -1) {
    luaY_growvector(0,0xffffffff);
    uVar2 = (**(code **)(DAT_1002beb8 + 0x28))
                      (*(undefined4 *)(iVar1 + 0x1c),*(int *)(PTR_1002bf6c[0xf] + 0x98) << 3,
                       s_lua_stx_10027b64,0x260);
    *(undefined4 *)(iVar1 + 0x1c) = uVar2;
  }
  PTR_1002bf6c[0xf] = PTR_1002bf6c[0xf] + -0x168;
  return iVar1;
}

/* ---- 0x1000ab20  lparser__ab20 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__ab20(undefined1 param_1)

{
  lparser__ab30(param_1,0);
  return;
}

/* ---- 0x1000ab30  lparser__ab30 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__ab30(undefined1 param_1,int param_2)

{
  lparser__a8b0(param_2);
  lparser__aa10(param_1);
  return;
}

/* ---- 0x1000ab50  luaY_growvector ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl luaY_growvector(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = (int *)PTR_1002bf6c[0xf];
  uVar2 = piVar1[0x28];
  if (uVar2 != 0xffffffff) {
    if ((int)uVar2 <= piVar1[0x26]) {
      uVar2 = luaM_growaux((undefined4 *)(*piVar1 + 0x1c),uVar2,8,&DAT_1002bedc,0xfffe);
      piVar1[0x28] = uVar2;
    }
    *(undefined4 *)(*(int *)(*piVar1 + 0x1c) + piVar1[0x26] * 8) = param_1;
    *(undefined4 *)(*(int *)(*piVar1 + 0x1c) + 4 + piVar1[0x26] * 8) = param_2;
    piVar1[0x26] = piVar1[0x26] + 1;
  }
  return;
}

/* ---- 0x1000abd0  yyparse ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* lua.stx: generated LALR parser from lua.stx */

undefined4 yyparse(void)

{
  unsigned char _frame[0xbf0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  short sVar1;
  int *piVar2;
  float fVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  float *pfVar9;
  float fVar10;
  int iVar11;
  undefined4 *puVar12;
  int iVar13;
  undefined4 *puVar14;
  #define local_be0 (*(uint *)(_frame + (0xbf0 - 0xbe0)))
  #define local_bdc (*(int *)(_frame + (0xbf0 - 0xbdc)))
  #define local_bd8 (*(short **)(_frame + (0xbf0 - 0xbd8)))
  #define local_bd4 (*(int *)(_frame + (0xbf0 - 0xbd4)))
  #define local_bd0 (*(float *)(_frame + (0xbf0 - 0xbd0)))
  #define local_bcc (*(int *)(_frame + (0xbf0 - 0xbcc)))
  #define local_bc8 (*(float *)(_frame + (0xbf0 - 0xbc8)))
  #define local_bc4 (*(int *)(_frame + (0xbf0 - 0xbc4)))
  #define local_bc0 (*(uint *)(_frame + (0xbf0 - 0xbc0)))
  #define local_bbc (*(int **)(_frame + (0xbf0 - 0xbbc)))
  #define local_bb8 (*(short (*)[499])(_frame + (0xbf0 - 0xbb8)))
  #define local_7d2 (*(short *)(_frame + (0xbf0 - 0x7d2)))
  #define local_7d0 (*(float *)(_frame + (0xbf0 - 0x7d0)))
  #define afStack_7cc (*(float (*)[499])(_frame + (0xbf0 - 0x7cc)))
  
  local_bd8 = local_bb8;
  iVar11 = 0;
  local_bdc = 0;
  local_bc4 = 0;
  local_be0 = 0xfffffffe;
  pfVar9 = &local_7d0;
  local_bb8[0] = 0;
  fVar10 = local_bc8;
  if (&local_7d2 <= local_bd8) {
LAB_1000b47d:
    lparser__a730(s_parser_stack_overflow_10027b6c);
    return 2;
  }
LAB_1000ac11:
  sVar1 = (&DAT_10023610)[iVar11];
  if (sVar1 == -0x8000) {
LAB_1000b4fe:
    local_bd4 = (int)(short)(&DAT_10023448)[iVar11];
    if (local_bd4 == 0) {
LAB_1000b512:
      if (local_bdc == 0) {
        local_bc4 = local_bc4 + 1;
        lparser__a730(s_parse_error_10027b58);
      }
      if (local_bdc == 3) {
        if (local_be0 == 0) {
          return 1;
        }
        local_be0 = 0xfffffffe;
      }
      local_bdc = 3;
      do {
        if ((((short)(&DAT_10023610)[iVar11] != -0x8000) &&
            (iVar11 = (short)(&DAT_10023610)[iVar11] + 1, -1 < iVar11)) &&
           ((iVar11 < 0x107 && (*(short *)(&DAT_100239e8 + iVar11 * 2) == 1)))) {
          local_bd4 = (int)*(short *)(&DAT_100237d8 + iVar11 * 2);
          if (local_bd4 < 0) {
            if (local_bd4 != -0x8000) {
              local_bd4 = -local_bd4;
              break;
            }
          }
          else if (local_bd4 != 0) goto LAB_1000b5bf;
        }
        if (local_bd8 == local_bb8) {
          return 1;
        }
        iVar11 = (int)local_bd8[-1];
        pfVar9 = pfVar9 + -1;
        local_bd8 = local_bd8 + -1;
      } while( true );
    }
LAB_1000acaa:
    iVar11 = (int)*(short *)(&DAT_10023378 + local_bd4 * 2);
    if (0 < iVar11) {
      fVar10 = pfVar9[1 - iVar11];
    }
    local_bcc = iVar11;
    switch(local_bd4) {
    case 6:
      lparser__bfa0(PUN(int,(float)pfVar9[-5]),PUN(int,(float)pfVar9[-2]));
      break;
    case 8:
      piVar2 = (int *)PTR_1002bf6c[0xf];
      uVar7 = PUN(int,(float)pfVar9[-3]) - PUN(int,(float)pfVar9[-4]);
      local_bc8 = PUN(float,(PUN(int,(float)pfVar9[-4]) + 2));
      local_bc0 = uVar7;
      local_bbc = piVar2;
      luaY_code_byte(uVar7);
      piVar4 = local_bbc;
      puVar12 = (undefined4 *)(PUN(int,(float)pfVar9[-4]) + *(int *)(*piVar2 + 0x10));
      puVar14 = (undefined4 *)(piVar2[1] + *(int *)(*piVar2 + 0x10));
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *puVar14 = *puVar12;
        puVar12 = puVar12 + 1;
        puVar14 = puVar14 + 1;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar12;
        puVar12 = (undefined4 *)((int)puVar12 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      memcpy((undefined4 *)(*(int *)(*local_bbc + 0x10) + PUN(int,(float)pfVar9[-4])),
             (undefined4 *)(PUN(int,(float)pfVar9[-3]) + *(int *)(*local_bbc + 0x10)),
             local_bbc[1] - PUN(int,(float)pfVar9[-4]));
      iVar11 = lparser__bf50(PUN(int,(float)pfVar9[-4]),'m',piVar4[1] - local_bc0);
      lparser__bf70('q',PUN(int,(float)local_bc8) + iVar11);
      iVar11 = local_bcc;
      break;
    case 9:
      lparser__bf70('s',PUN(int,(float)pfVar9[-3]));
      lparser__a8b0(-1);
      break;
    case 10:
      iVar11 = 0;
      lparser__bd80(PUN(int,(float)pfVar9[-2]),PUN(int,(float)*pfVar9));
      fVar3 = pfVar9[-2];
      while (fVar3 = PUN(float,(PUN(int,(float)fVar3) + -1)), -1 < PUN(int,(float)fVar3)) {
        iVar11 = lparser__bf00(PUN(int,(float)fVar3),iVar11);
      }
      lparser__bcc0(iVar11);
      iVar11 = local_bcc;
      break;
    case 0xb:
      lparser__bd00(PUN(int,(float)*pfVar9),0);
      break;
    case 0xc:
      *(int *)(PTR_1002bf6c[0xf] + 0x90) = *(int *)(PTR_1002bf6c[0xf] + 0x90) + PUN(int,(float)pfVar9[-1]);
      lparser__bd80(PUN(int,(float)pfVar9[-1]),PUN(int,(float)*pfVar9));
      break;
    case 0xd:
      lparser__bec0(PUN(int,(float)pfVar9[-1]));
      break;
    case 0xe:
      fVar10 = *(float *)(PTR_1002bf6c[0xf] + 0x90);
      break;
    case 0xf:
      lparser__bcc0(*(int *)(PTR_1002bf6c[0xf] + 0x90) - PUN(int,(float)pfVar9[-1]));
      if (PUN(int,(float)pfVar9[-1]) < *(int *)(PTR_1002bf6c[0xf] + 0x90)) {
        do {
          lparser__ba10(*(undefined4 *)(PTR_1002bf6c[0x10] + 8));
          *(int *)(PTR_1002bf6c[0xf] + 0x90) = *(int *)(PTR_1002bf6c[0xf] + 0x90) + -1;
        } while (PUN(int,(float)pfVar9[-1]) < *(int *)(PTR_1002bf6c[0xf] + 0x90));
      }
      break;
    case 0x10:
      fVar10 = *pfVar9;
      lparser__c100();
      break;
    case 0x11:
      fVar10 = 0.0;
      lparser__c100();
      break;
    case 0x12:
      fVar10 = 0.0;
      lparser__c100();
      uVar6 = luaS_new(&DAT_10027ba0);
      lparser__ba70(uVar6);
      break;
    case 0x13:
      lparser__be60(PUN(int,(float)*pfVar9));
      break;
    case 0x14:
      lparser__b8a0(PUN(int,(float)*pfVar9));
      break;
    case 0x15:
      luaY_syntaxerror();
      lparser__c060();
      break;
    case 0x18:
      lparser__bfa0(PUN(int,(float)pfVar9[-4]),PUN(int,(float)pfVar9[-1]));
      break;
    case 0x1a:
      lparser__bd00(PUN(int,(float)pfVar9[-1]),0xff);
      lparser__c020();
      break;
    case 0x1b:
      fVar10 = *(float *)(PTR_1002bf6c[0xf] + 4);
      break;
    case 0x1c:
      fVar10 = *(float *)(PTR_1002bf6c[0xf] + 4);
      luaY_code_byte(2);
      *(int *)(PTR_1002bf6c[0xf] + 4) = *(int *)(PTR_1002bf6c[0xf] + 4) + 2;
      break;
    case 0x1d:
      fVar10 = *pfVar9;
      lparser__a8b0(-1);
      break;
    case 0x1e:
      fVar10 = *pfVar9;
      lparser__a8b0(1);
      break;
    case 0x1f:
    case 0x30:
    case 0x3c:
    case 0x3d:
    case 0x49:
    case 0x54:
    case 0x55:
    case 0x66:
switchD_1000acd8_caseD_1f:
      fVar10 = *pfVar9;
      break;
    case 0x20:
      lparser__bd00(PUN(int,(float)*pfVar9),1);
      break;
    case 0x22:
      lparser__b800(0x5b);
      fVar10 = 0.0;
      break;
    case 0x23:
      lparser__b800(0x5d);
      fVar10 = 0.0;
      break;
    case 0x24:
      lparser__b800(0x5f);
      fVar10 = 0.0;
      break;
    case 0x25:
      lparser__b800(0x5c);
      fVar10 = 0.0;
      break;
    case 0x26:
      lparser__b800(0x5e);
      fVar10 = 0.0;
      break;
    case 0x27:
      lparser__b800(0x60);
      fVar10 = 0.0;
      break;
    case 0x28:
      lparser__b800(0x61);
      fVar10 = 0.0;
      break;
    case 0x29:
      lparser__b800(0x62);
      fVar10 = 0.0;
      break;
    case 0x2a:
      lparser__b800(99);
      fVar10 = 0.0;
      break;
    case 0x2b:
      lparser__b800(100);
      fVar10 = 0.0;
      break;
    case 0x2c:
      lparser__b800(0x65);
      fVar10 = 0.0;
      break;
    case 0x2d:
      lparser__b800(0x66);
      fVar10 = 0.0;
      break;
    case 0x2e:
      lparser__ab20(0x67);
      fVar10 = 0.0;
      break;
    case 0x2f:
      lparser__ab20(0x68);
      fVar10 = 0.0;
      break;
    case 0x31:
    case 0x36:
    case 0x3e:
    case 0x43:
    case 0x48:
    case 0x53:
    case 0x65:
      fVar10 = 0.0;
      break;
    case 0x32:
      luaY_code_number(*pfVar9);
      fVar10 = 0.0;
      break;
    case 0x33:
      lparser__b8a0(PUN(int,(float)*pfVar9));
      fVar10 = 0.0;
      break;
    case 0x34:
      lparser__bcc0(-1);
      fVar10 = 0.0;
      break;
    case 0x35:
      lparser__c100();
      break;
    case 0x37:
      lparser__c000(PUN(int,(float)pfVar9[-1]),'k');
      fVar10 = 0.0;
      break;
    case 0x38:
      lparser__c000(PUN(int,(float)pfVar9[-1]),'i');
      fVar10 = 0.0;
      break;
    case 0x39:
      lparser__bd00(PUN(int,(float)*pfVar9),1);
      break;
    case 0x3a:
      lparser__be60(PUN(int,(float)*pfVar9));
      fVar10 = 0.0;
      break;
    case 0x3b:
      lparser__bbd0(PUN(int,(float)*pfVar9));
      fVar10 = 0.0;
      break;
    case 0x3f:
      iVar5 = luaY_string_constant(PUN(int,(float)*pfVar9),(int *)PTR_1002bf6c[0xf]);
      fVar10 = PUN(float,(-1 - iVar5));
      break;
    case 0x40:
      fVar10 = PUN(float,lparser__baf0(PUN(int,(float)*pfVar9),(int *)PTR_1002bf6c[0xf]));
      break;
    case 0x41:
      lparser__b770(PUN(int,(float)pfVar9[-2]),'=',2,PUN(uint,(float)pfVar9[-1]));
      break;
    case 0x42:
      lparser__aa10(0);
      lparser__aa10(*(char *)(pfVar9 + -1) + *(char *)pfVar9);
      fVar10 = *(float *)(PTR_1002bf6c[0xf] + 4);
      lparser__aa10(0);
      break;
    case 0x44:
      iVar5 = 1;
      uVar8 = luaY_string_constant(PUN(int,(float)*pfVar9),(int *)PTR_1002bf6c[0xf]);
      luaY_code_opcode_arg('3',8,uVar8,iVar5);
      fVar10 = 1.4013e-45;
      break;
    case 0x45:
      fVar10 = PUN(float,lparser__bd00(PUN(int,(float)pfVar9[-1]),1));
      break;
    case 0x47:
      lparser__b8a0(PUN(int,(float)*pfVar9));
      fVar10 = 1.4013e-45;
      break;
    case 0x4a:
      fVar10 = *pfVar9;
      if (fVar10 == 0.0) {
        fVar10 = -NAN;
      }
      break;
    case 0x4b:
      fVar10 = PUN(float,lparser__bd00(PUN(int,(float)pfVar9[-1]),1));
      break;
    case 0x4c:
      if (*pfVar9 != 0.0) {
        *(char *)(*(int *)(*(int *)PTR_1002bf6c[0xf] + 0x10) + PUN(int,(float)*pfVar9)) =
             *(char *)(pfVar9 + -1);
        goto switchD_1000acd8_caseD_1f;
      }
      fVar10 = PUN(float,(-1 - PUN(int,(float)pfVar9[-1])));
      break;
    case 0x4d:
      lparser__bde0(0,0);
      break;
    case 0x4e:
      lparser__bde0(0,1);
      break;
    case 0x4f:
      lparser__bde0(PUN(int,(float)*pfVar9),0);
      break;
    case 0x50:
      lparser__bde0(PUN(int,(float)pfVar9[-2]),1);
      break;
    case 0x51:
      uVar8 = PUN(int,(float)*pfVar9) >> 0x1f;
      fVar10 = PUN(float,((PUN(uint,(float)*pfVar9) ^ uVar8) - uVar8));
      break;
    case 0x52:
      if (0 < PUN(int,(float)*pfVar9) * PUN(int,(float)pfVar9[-2])) {
        lparser__a730(s_invalid_constructor_syntax_10027b84);
      }
      uVar8 = PUN(int,(float)*pfVar9) >> 0x1f;
      uVar7 = PUN(int,(float)pfVar9[-2]) >> 0x1f;
      fVar10 = PUN(float,(((PUN(uint,(float)*pfVar9) ^ uVar8) - uVar8) + ((PUN(uint,(float)pfVar9[-2]) ^ uVar7) - uVar7)));
      break;
    case 0x58:
      uVar8 = PUN(int,(float)pfVar9[-1]) >> 0x1f;
      lparser__b9c0(((PUN(uint,(float)pfVar9[-1]) ^ uVar8) - uVar8 & 0x1f ^ uVar8) - uVar8);
      fVar10 = PUN(float,-PUN(int,(float)pfVar9[-1]));
      break;
    case 0x59:
      fVar10 = pfVar9[-1];
      uVar8 = PUN(int,(float)fVar10) >> 0x1f;
      lparser__b9e0((int)(PUN(int,(float)fVar10) + (uVar8 & 0x3f)) >> 6,
                    ((PUN(uint,(float)fVar10) ^ uVar8) - uVar8 & 0x3f ^ uVar8) - uVar8);
    case 0x21:
      fVar10 = pfVar9[-1];
      break;
    case 0x5b:
      fVar10 = PUN(float,(PUN(int,(float)pfVar9[-2]) + 1));
      uVar8 = PUN(int,(float)fVar10) >> 0x1f;
      if (((PUN(uint,(float)fVar10) ^ uVar8) - uVar8 & 0x1f ^ uVar8) == uVar8) {
        lparser__b9c0(0x20);
      }
      break;
    case 0x60:
      fVar10 = PUN(float,(PUN(int,(float)pfVar9[-2]) + 1));
      uVar8 = PUN(int,(float)fVar10) >> 0x1f;
      if (((PUN(uint,(float)fVar10) ^ uVar8) - uVar8 & 0x3f ^ uVar8) == uVar8) {
        lparser__b9e0(((int)(PUN(int,(float)fVar10) + (uVar8 & 0x3f)) >> 6) - 1,0x40);
      }
      break;
    case 0x61:
      fVar10 = 1.4013e-45;
      lparser__ba90(PUN(int,(float)*pfVar9),0);
      break;
    case 0x62:
      lparser__ba90(PUN(int,(float)*pfVar9),PUN(int,(float)pfVar9[-2]));
      fVar10 = PUN(float,(PUN(int,(float)pfVar9[-2]) + 1));
      break;
    case 99:
      lparser__ba20(*pfVar9,0);
    case 0x46:
    case 0x5a:
    case 0x5f:
      fVar10 = 1.4013e-45;
      break;
    case 100:
      lparser__ba20(*pfVar9,PUN(int,(float)pfVar9[-2]));
      fVar10 = PUN(float,(PUN(int,(float)pfVar9[-2]) + 1));
    }
    local_bd8 = local_bd8 + -iVar11;
    pfVar9 = pfVar9 + (1 - iVar11);
    *pfVar9 = fVar10;
    iVar11 = (int)*(short *)(&DAT_1002371e + *(short *)(&DAT_100232a8 + local_bd4 * 2) * 2) +
             (int)*local_bd8;
    if (((iVar11 < 0) || (0x106 < iVar11)) || (*(short *)(&DAT_100239e8 + iVar11 * 2) != *local_bd8)
       ) {
      local_bd4 = (int)*(short *)(&DAT_10023556 + *(short *)(&DAT_100232a8 + local_bd4 * 2) * 2);
    }
    else {
      local_bd4 = (int)*(short *)(&DAT_100237d8 + iVar11 * 2);
    }
  }
  else {
    if (local_be0 == 0xfffffffe) {
      local_be0 = luaX_lex(&local_bd0);
    }
    if ((int)local_be0 < 1) {
      iVar5 = 0;
      local_be0 = 0;
    }
    else if (local_be0 < 0x11d) {
      iVar5 = (int)(char)(&DAT_10023188)[local_be0];
    }
    else {
      iVar5 = 0x5d;
    }
    iVar13 = sVar1 + iVar5;
    if (((iVar13 < 0) || (0x106 < iVar13)) || (*(short *)(&DAT_100239e8 + iVar13 * 2) != iVar5))
    goto LAB_1000b4fe;
    local_bd4 = (int)*(short *)(&DAT_100237d8 + iVar13 * 2);
    if (local_bd4 < 0) {
      if (local_bd4 == -0x8000) goto LAB_1000b512;
      local_bd4 = -local_bd4;
      goto LAB_1000acaa;
    }
    if (local_bd4 == 0) goto LAB_1000b512;
    if (local_bd4 == 0xb5) {
      return 0;
    }
    if (local_be0 != 0) {
      local_be0 = 0xfffffffe;
    }
    pfVar9 = pfVar9 + 1;
    *pfVar9 = local_bd0;
    if (local_bdc != 0) {
      local_bdc = local_bdc + -1;
    }
  }
  goto LAB_1000b464;
LAB_1000b5bf:
  if (local_bd4 == 0xb5) {
    return 0;
  }
  pfVar9 = pfVar9 + 1;
  *pfVar9 = local_bd0;
LAB_1000b464:
  local_bd8 = local_bd8 + 1;
  *local_bd8 = (short)local_bd4;
  iVar11 = local_bd4;
  if (&local_7d2 <= local_bd8) goto LAB_1000b47d;
  goto LAB_1000ac11;
}
#undef afStack_7cc
#undef local_7d0
#undef local_7d2
#undef local_bb8
#undef local_bbc
#undef local_bc0
#undef local_bc4
#undef local_bc8
#undef local_bcc
#undef local_bd0
#undef local_bd4
#undef local_bd8
#undef local_bdc
#undef local_be0

#endif


/* ---- 0x1000b770  lparser__b770 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

int __cdecl lparser__b770(int param_1,char param_2,int param_3,uint param_4)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)PTR_1002bf6c[0xf];
  if ((int)param_4 < param_3) {
    iVar3 = *(int *)(*piVar2 + 0x10) + param_1;
    memcpy((undefined4 *)(iVar3 + 1),(undefined4 *)(iVar3 + 2),(piVar2[1] - param_1) - 2);
    iVar3 = piVar2[1] + -1;
  }
  else {
    if ((int)param_4 < 0x100) goto LAB_1000b7e3;
    luaY_code_byte(1);
    puVar1 = (undefined4 *)(*(int *)(*piVar2 + 0x10) + param_1);
    memcpy((undefined4 *)((int)puVar1 + 1),puVar1,piVar2[1] - param_1);
    iVar3 = piVar2[1] + 1;
  }
  piVar2[1] = iVar3;
LAB_1000b7e3:
  iVar3 = lparser__a810(param_1,param_2,param_3,param_4,0);
  return iVar3 + -2;
}

/* ---- 0x1000b800  lparser__b800 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__b800(undefined1 param_1)

{
  lparser__ab30(param_1,-1);
  return;
}

/* ---- 0x1000b810  luaY_string_constant ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

uint __cdecl luaY_string_constant(int param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *param_2;
  uVar2 = *(uint *)(param_1 + 8);
  if (((*(uint *)(iVar1 + 0xc) <= uVar2) || (*(int *)(*(int *)(iVar1 + 8) + uVar2 * 8) != -2)) ||
     (*(int *)(*(int *)(iVar1 + 8) + uVar2 * 8 + 4) != param_1)) {
    uVar2 = luaY_next_constant(param_2);
    *(undefined4 *)(*(int *)(iVar1 + 8) + uVar2 * 8) = 0xfffffffe;
    *(int *)(*(int *)(iVar1 + 8) + 4 + uVar2 * 8) = param_1;
    *(uint *)(param_1 + 8) = uVar2;
  }
  return uVar2;
}

/* ---- 0x1000b860  luaY_next_constant ---- */
/* lua.stx: constant table overflow */

int __cdecl luaY_next_constant(int *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *param_1;
  if ((uint)param_1[0x29] <= *(uint *)(iVar1 + 0xc)) {
    uVar3 = luaM_growaux((undefined4 *)(iVar1 + 8),param_1[0x29],8,
                         (byte *)s_constant_table_overflow_10027ba8,0xfffe);
    param_1[0x29] = uVar3;
  }
  iVar2 = *(int *)(iVar1 + 0xc);
  *(int *)(iVar1 + 0xc) = iVar2 + 1;
  return iVar2;
}

/* ---- 0x1000b8a0  lparser__b8a0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__b8a0(int param_1)

{
  uint uVar1;
  
  uVar1 = luaY_string_constant(param_1,(int *)PTR_1002bf6c[0xf]);
  lparser__b8c0(uVar1);
  return;
}

/* ---- 0x1000b8c0  lparser__b8c0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__b8c0(uint param_1)

{
  luaY_code_opcode_arg('\b',8,param_1,1);
  return;
}

/* ---- 0x1000b8e0  luaY_code_number ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl luaY_code_number(float param_1)

{
  uint uVar1;
  longlong lVar2;
  
  if ((0.0 <= param_1) && (param_1 <= 65534.0)) {
    lVar2 = _ftol();
    if ((float)(int)(uint)lVar2 == param_1) {
      luaY_code_opcode_arg('\x03',3,(uint)lVar2,1);
      return;
    }
  }
  uVar1 = luaY_real_constant(param_1);
  lparser__b8c0(uVar1);
  return;
}
#endif


/* ---- 0x1000b950  luaY_real_constant ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of lua.stx (yacc parser) and code generation */

int __cdecl luaY_real_constant(float param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar1 = *(int *)PTR_1002bf6c[0xf];
  iVar2 = *(int *)(iVar1 + 0xc);
  if (iVar2 < 0x14) {
    iVar4 = 0;
  }
  else {
    iVar4 = iVar2 + -0x14;
  }
  iVar2 = iVar2 + -1;
  if (iVar4 <= iVar2) {
    piVar3 = (int *)(*(int *)(iVar1 + 8) + iVar2 * 8);
    do {
      if ((*piVar3 == -1) && (PUN(float,piVar3[1]) == param_1)) {
        return iVar2;
      }
      iVar2 = iVar2 + -1;
      piVar3 = piVar3 + -2;
    } while (iVar4 <= iVar2);
  }
  iVar2 = luaY_next_constant((int *)PTR_1002bf6c[0xf]);
  iVar1 = *(int *)(*(int *)PTR_1002bf6c[0xf] + 8);
  *(undefined4 *)(iVar1 + iVar2 * 8) = 0xffffffff;
  *(float *)(iVar1 + 4 + iVar2 * 8) = param_1;
  return iVar2;
}
#endif


/* ---- 0x1000b9c0  lparser__b9c0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__b9c0(int param_1)

{
  if (0 < param_1) {
    luaY_code_opcode_arg('Y',1,param_1 - 1,param_1 * -2);
  }
  return;
}

/* ---- 0x1000b9e0  lparser__b9e0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__b9e0(uint param_1,int param_2)

{
  if (param_2 != 0) {
    luaY_code_opcode_arg('V',1,param_1,-param_2);
    lparser__aa10((char)param_2);
  }
  return;
}

/* ---- 0x1000ba10  lparser__ba10 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__ba10(undefined4 param_1)

{
  luaY_growvector(0,param_1);
  return;
}

/* ---- 0x1000ba20  lparser__ba20 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__ba20(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(PTR_1002bf6c[0xf] + 0x90) + param_2;
  if (iVar1 < 0x20) {
    *(undefined4 *)(PTR_1002bf6c[0xf] + 8 + iVar1 * 4) = param_1;
  }
  else {
    lparser__a730(s_too_many_local_variables__limit__10027bc0);
  }
  luaY_growvector(param_1,*(undefined4 *)(PTR_1002bf6c[0x10] + 8));
  return;
}

/* ---- 0x1000ba70  lparser__ba70 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__ba70(undefined4 param_1)

{
  lparser__ba20(param_1,0);
  *(int *)(PTR_1002bf6c[0xf] + 0x90) = *(int *)(PTR_1002bf6c[0xf] + 0x90) + 1;
  return;
}

/* ---- 0x1000ba90  lparser__ba90 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__ba90(int param_1,int param_2)

{
  int iVar1;
  
  if (0x1f < param_2) {
    lparser__a730(s_variable_buffer_overflow__limit__10027be4);
  }
  iVar1 = lparser__bad0(param_1);
  *(int *)(PTR_1002bf6c[0xf] + 0xa8 + param_2 * 4) = iVar1;
  return;
}

/* ---- 0x1000bad0  lparser__bad0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

int __cdecl lparser__bad0(int param_1)

{
  if (param_1 < 0) {
    lparser__b8c0(-param_1 - 1);
    param_1 = 0;
  }
  return param_1;
}

/* ---- 0x1000baf0  lparser__baf0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

int __cdecl lparser__baf0(int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = lparser__bba0(param_1,(int)param_2);
  if (iVar2 != -1) {
    return iVar2 + 1;
  }
  iVar2 = 1;
  piVar1 = param_2;
  if (0 < ((int)param_2 - PTR_1002bf6c[0xe]) / 0x168) {
    do {
      iVar3 = lparser__bba0(param_1,(int)(piVar1 + -0x5a));
      if (-1 < iVar3) {
        luaY_error(s_cannot_access_a_variable_in_oute_10027c08,(char *)(param_1 + 0x18));
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + -0x5a;
    } while (iVar2 <= ((int)param_2 - PTR_1002bf6c[0xe]) / 0x168);
  }
  iVar2 = luaY_string_constant(param_1,param_2);
  return iVar2 + 0x21;
}

/* ---- 0x1000bba0  lparser__bba0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

int __cdecl lparser__bba0(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *(int *)(param_2 + 0x90) + -1;
  if (-1 < iVar1) {
    piVar2 = (int *)(param_2 + 8 + iVar1 * 4);
    do {
      if (param_1 == *piVar2) {
        return iVar1;
      }
      iVar1 = iVar1 + -1;
      piVar2 = piVar2 + -1;
    } while (-1 < iVar1);
  }
  return -1;
}

/* ---- 0x1000bbd0  lparser__bbd0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__bbd0(int param_1)

{
  int iVar1;
  uint uVar2;
  
  if (PTR_1002bf6c[0xf] == PTR_1002bf6c[0xe]) {
    lparser__a730(s_cannot_access_upvalue_in_main_10027c5c);
  }
  iVar1 = lparser__bba0(param_1,PTR_1002bf6c[0xf]);
  if (-1 < iVar1) {
    luaY_error(s_cannot_access_an_upvalue_in_curr_10027c30,(char *)(param_1 + 0x18));
  }
  uVar2 = lparser__bc40(param_1);
  luaY_code_opcode_arg('\x12',2,uVar2,1);
  return;
}

/* ---- 0x1000bc40  lparser__bc40 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

int __cdecl lparser__bc40(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar3 = lparser__baf0(param_1,(int *)(PTR_1002bf6c[0xf] + -0x168));
  iVar5 = 0;
  iVar1 = PTR_1002bf6c[0xf];
  iVar2 = *(int *)(iVar1 + 0x94);
  if (0 < iVar2) {
    piVar4 = (int *)(iVar1 + 0x128);
    do {
      if (*piVar4 == iVar3) {
        return iVar5;
      }
      iVar5 = iVar5 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar5 < iVar2);
  }
  *(int *)(iVar1 + 0x94) = iVar2 + 1;
  if (0x10 < *(int *)(PTR_1002bf6c[0xf] + 0x94)) {
    lparser__a730(s_too_many_upvalues_in_a_single_fu_10027c7c);
  }
  *(int *)(PTR_1002bf6c[0xf] + 0x128 + iVar5 * 4) = iVar3;
  return iVar5;
}

/* ---- 0x1000bcc0  lparser__bcc0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__bcc0(int param_1)

{
  if (0 < param_1) {
    luaY_code_opcode_arg('~',2,param_1 - 1,-param_1);
    return;
  }
  if (param_1 < 0) {
    luaY_code_opcode_arg('\x01',1,-param_1 - 1,-param_1);
  }
  return;
}

/* ---- 0x1000bd00  lparser__bd00 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

int __cdecl lparser__bd00(int param_1,uint param_2)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  
  if (param_1 < 1) {
    return -param_1;
  }
  pbVar3 = (byte *)(*(int *)(*(int *)PTR_1002bf6c[0xf] + 0x10) + param_1);
  bVar1 = *pbVar3;
  bVar2 = pbVar3[-1];
  iVar4 = lparser__b770(param_1 + -2,'x',2,param_2);
  *(byte *)(*(int *)(*(int *)PTR_1002bf6c[0xf] + 0x10) + param_1 + iVar4) = bVar2;
  if (param_2 != 0xff) {
    lparser__a8b0(param_2);
  }
  lparser__a8b0(-1 - (uint)bVar2);
  return bVar1 + param_2;
}

/* ---- 0x1000bd80  lparser__bd80 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__bd80(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 < 1) {
    lparser__bcc0(-(param_2 + param_1));
    return;
  }
  iVar1 = (uint)*(byte *)(*(int *)(*(int *)PTR_1002bf6c[0xf] + 0x10) + param_2) - param_1;
  if (iVar1 < 0) {
    lparser__bd00(param_2,-iVar1);
    return;
  }
  lparser__bd00(param_2,0);
  lparser__bcc0(iVar1);
  return;
}

/* ---- 0x1000bde0  lparser__bde0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__bde0(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  *(int *)(PTR_1002bf6c[0xf] + 0x90) = *(int *)(PTR_1002bf6c[0xf] + 0x90) + param_1;
  piVar1 = (int *)PTR_1002bf6c[0xf];
  iVar2 = piVar1[0x24];
  if (param_2 == 0) {
    *(char *)(*(int *)(*piVar1 + 0x10) + 1) = (char)iVar2;
    lparser__a8b0(iVar2);
    return;
  }
  *(char *)(*(int *)(*piVar1 + 0x10) + 1) = (char)iVar2 + '@';
  lparser__a8b0(iVar2 + 1);
  uVar3 = luaS_new(&DAT_10027cb0);
  lparser__ba70(uVar3);
  return;
}

/* ---- 0x1000be60  lparser__be60 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__be60(int param_1)

{
  if (0x20 < param_1) {
    luaY_code_opcode_arg('\x1e',8,param_1 - 0x21,1);
    return;
  }
  if ((0 < param_1) && (param_1 < 0x21)) {
    luaY_code_opcode_arg('\x15',8,param_1 - 1,1);
    return;
  }
  if (-1 < param_1) {
    lparser__b800(0x28);
    return;
  }
  ((code *)luaY_code_opcode_arg)(')',8,-param_1 - 1,0);
  return;
}
#endif


/* ---- 0x1000bec0  lparser__bec0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__bec0(int param_1)

{
  if (param_1 == 0) {
    lparser__ab30(0x54,-3);
    return;
  }
  if (0x20 < param_1) {
    luaY_code_opcode_arg('J',8,param_1 - 0x21,-1);
    return;
  }
  luaY_code_opcode_arg('A',8,param_1 - 1,-1);
  return;
}

/* ---- 0x1000bf00  lparser__bf00 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

int __cdecl lparser__bf00(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(PTR_1002bf6c[0xf] + 0xa8 + param_1 * 4);
  if ((iVar1 == 0) && (param_1 + param_2 != 0)) {
    luaY_code_opcode_arg('U',0,param_1 + param_2,-1);
    return param_2 + 2;
  }
  lparser__bec0(iVar1);
  return param_2;
}

/* ---- 0x1000bf50  lparser__bf50 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

int __cdecl lparser__bf50(int param_1,char param_2,int param_3)

{
  int iVar1;
  
  iVar1 = lparser__b770(param_1,param_2,0,(param_3 - param_1) - 2);
  return iVar1;
}

/* ---- 0x1000bf70  lparser__bf70 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__bf70(char param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(PTR_1002bf6c[0xf] + 4) - param_2;
  uVar2 = iVar1 + 2;
  if (0xff < (int)uVar2) {
    uVar2 = iVar1 + 3;
  }
  luaY_code_opcode_arg(param_1,0,uVar2,0);
  return;
}

/* ---- 0x1000bfa0  lparser__bfa0 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__bfa0(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(PTR_1002bf6c[0xf] + 4);
  if (iVar1 == param_2 + 2) {
    *(int *)(PTR_1002bf6c[0xf] + 4) = iVar1 + -2;
    lparser__bf50(param_1,'o',*(int *)(PTR_1002bf6c[0xf] + 4));
    return;
  }
  iVar1 = lparser__bf50(param_2,'m',iVar1);
  lparser__bf50(param_1,'o',param_2 + 2 + iVar1);
  return;
}

/* ---- 0x1000c000  lparser__c000 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void __cdecl lparser__c000(int param_1,char param_2)

{
  lparser__bf50(param_1,param_2,*(int *)(PTR_1002bf6c[0xf] + 4));
  return;
}

/* ---- 0x1000c020  lparser__c020 ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/LUA.DLL/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Unidentified function of lua.stx (yacc parser) and code generation */

void lparser__c020(void)

{
  ((code *)luaY_code_opcode_arg)('{',0,*(uint *)(PTR_1002bf6c[0xf] + 0x90),0);
  *(undefined4 *)(PTR_1002bf6c[0xf] + 0x88) = *(undefined4 *)(PTR_1002bf6c[0xf] + 0x90);
  return;
}
#endif


/* ---- 0x1000c060  lparser__c060 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void lparser__c060(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar1 = ((int *)PTR_1002bf6c[0xf])[0x7f];
  uVar2 = luaY_next_constant((int *)PTR_1002bf6c[0xf]);
  *(undefined4 *)(*(int *)(*(int *)PTR_1002bf6c[0xf] + 8) + uVar2 * 8) = 0xfffffffc;
  *(int *)(*(int *)(*(int *)PTR_1002bf6c[0xf] + 8) + 4 + uVar2 * 8) =
       ((int *)PTR_1002bf6c[0xf])[0x5a];
  if (uVar1 != 0) {
    if (0 < (int)uVar1) {
      iVar3 = 0x290;
      uVar4 = uVar1;
      do {
        lparser__be60(*(int *)(PTR_1002bf6c[0xf] + iVar3));
        iVar3 = iVar3 + 4;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
    lparser__b8c0(uVar2);
    luaY_code_opcode_arg('u',2,uVar1,-uVar1);
    return;
  }
  lparser__b8c0(uVar2);
  return;
}

/* ---- 0x1000c100  lparser__c100 ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation */

void lparser__c100(void)

{
  if (4 < (PTR_1002bf6c[0xf] - PTR_1002bf6c[0xe]) / 0x168) {
    lparser__a730(s_too_many_nested_functions__limit_10027cb4);
  }
  PTR_1002bf6c[0xf] = PTR_1002bf6c[0xf] + 0x168;
  lparser__a980(*(undefined4 *)(*(int *)PTR_1002bf6c[0xe] + 0x18));
  luaY_code_word(*(uint *)(PTR_1002bf6c[0x10] + 8));
  *(undefined4 *)(*(int *)PTR_1002bf6c[0xf] + 0x14) = *(undefined4 *)(PTR_1002bf6c[0x10] + 8);
  return;
}
