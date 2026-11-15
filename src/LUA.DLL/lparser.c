/* LUA.DLL :: lparser.c
 * functions 0x1000a6f0 .. 0x1000c100 (48 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x1000a6f0  luaY_syntaxerror ---- */
/* lua.stx: 'last token read: %50s' error Original name luaY_syntaxerror (the remaster's libLua.so:
   remaster luaY_syntaxerror(msg, token): the same '<eof>' and 'last token read' message); was
   luaY_error. */

void __cdecl luaY_syntaxerror(char *msg,char *token)

{
  if (*token == '\0') {
    token = s__eof__10027b00;
  }
  luaL_verror(s___100s__last_token_read_____50s__10027ac4,msg,token,
              *(undefined4 *)((int)g_pLuaState->pLexState + 8),
              g_pLuaState->pMainState->pF->pFileName->aStr);
  return;
}

/* ---- 0x1000a730  luaY_error ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Original name luaY_error (the
   remaster's libLua.so: remaster luaY_error(msg): luaY_syntaxerror(msg, luaX_lasttoken())); was
   lparser__a730. */

void __cdecl luaY_error(char *msg)

{
  char *token;
  
  token = (char *)luaX_lasttoken();
  luaY_syntaxerror(msg,token);
  return;
}

/* ---- 0x1000a750  luaY_codedebugline ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Original name
   luaY_codedebugline (the remaster's libLua.so: if lua_debug and the line changed: SETLINE (0x7c)
   with the line, remembered in the func state +0x10 (same body); called by luaY_lex); was
   luaY_code_word. */

void __cdecl luaY_codedebugline(uint param_1)

{
  if ((lua_debug != 0) && (param_1 != *(uint *)((int)g_pLuaState->pLexState + 0x10))) {
    code_oparg('|',0,param_1,0);
    *(uint *)((int)g_pLuaState->pLexState + 0x10) = param_1;
  }
  return;
}

/* ---- 0x1000a790  code_oparg ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_oparg (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: check_pc(3), pc +=
   code_oparg_at(pc, ...)); was luaY_code_opcode_arg. */

void __cdecl code_oparg(char param_1,int param_2,uint param_3,int param_4)

{
  FuncState *pFVar1;
  int iVar2;
  
  check_pc(3);
  pFVar1 = g_pLuaState->pCurrState;
  iVar2 = code_oparg_at(pFVar1->nPc,param_1,param_2,param_3,param_4);
  pFVar1->nPc = pFVar1->nPc + iVar2;
  return;
}

/* ---- 0x1000a7d0  check_pc ---- */
/* lua.stx: code size overflow Named check_pc (not in the remaster, gcc inlined it there): Lua 3.1
   source name (lua.stx: grows f->code for n more bytes, 'code size overflow'); was luaY_code_byte.
    */

void __cdecl check_pc(int param_1)

{
  FuncState *pFVar1;
  uint uVar2;
  
  pFVar1 = g_pLuaState->pCurrState;
  if (pFVar1->nMaxCode < pFVar1->nPc + param_1) {
    uVar2 = luaM_growaux(&pFVar1->pF->pCode,pFVar1->nMaxCode,1,(byte *)s_code_size_overflow_10027b08
                         ,0x7ffffffd);
    pFVar1->nMaxCode = uVar2;
  }
  return;
}

/* ---- 0x1000a810  code_oparg_at ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_oparg_at (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: writes op/arg in the shortest
   form at pc, deltastack); was lparser__a810. */

undefined4 __cdecl code_oparg_at(int param_1,char param_2,int param_3,uint param_4,int param_5)

{
  byte *pbVar1;
  byte bVar2;
  
  pbVar1 = g_pLuaState->pCurrState->pF->pCode;
  deltastack(param_5);
  bVar2 = (byte)param_4;
  if ((int)param_4 < param_3) {
    pbVar1[param_1] = bVar2 + param_2 + 1;
    return 1;
  }
  if ((int)param_4 < 0x100) {
    pbVar1[param_1] = param_2;
    pbVar1[param_1 + 1] = bVar2;
    return 2;
  }
  if (param_4 < 0xffff) {
    pbVar1[param_1] = (char)param_3 + param_2 + 1;
    pbVar1[param_1 + 1] = bVar2;
    pbVar1[param_1 + 2] = (byte)(param_4 >> 8);
    return 3;
  }
  luaY_error(s_code_too_long__limit_64K__10027b1c);
  return 0;
}

/* ---- 0x1000a8b0  deltastack ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named deltastack (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: stacksize += delta,
   'function/expression too complex'); was lparser__a8b0. */

void __cdecl deltastack(int param_1)

{
  FuncState *pFVar1;
  int iVar2;
  
  pFVar1 = g_pLuaState->pCurrState;
  iVar2 = pFVar1->nStackSize + param_1;
  pFVar1->nStackSize = iVar2;
  if (pFVar1->nMaxStackSize < iVar2) {
    if (0xff < iVar2) {
      luaY_error(s_function_expression_too_complex_10027b38);
    }
    pFVar1->nMaxStackSize = pFVar1->nStackSize;
  }
  return;
}

/* ---- 0x1000a900  luaY_parser ---- */
int __cdecl luaY_parser(int param_1)

{
  unsigned char _frame[0x8e0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  TaggedString *pTVar1;
  int iVar2;
  #define local_8c4 (*(undefined1 (*)[84])(_frame + (0x8e0 - 0x8c4)))
  #define local_870 (*(FuncState (*)[6])(_frame + (0x8e0 - 0x870)))
  
                    /* 0xa900  4  luaY_parser */
  g_pLuaState->pMainState = local_870;
  g_pLuaState->pCurrState = g_pLuaState->pMainState;
  g_pLuaState->pLexState = local_8c4;
  luaX_setinput(param_1);
  pTVar1 = luaS_new(*(char **)(param_1 + 0x10));
  init_state(pTVar1);
  iVar2 = luaY_parse();
  if (iVar2 != 0) {
    lua_error((byte *)s_parse_error_10027b58);
  }
  iVar2 = close_func();
  return iVar2;
}
#undef local_870
#undef local_8c4


/* ---- 0x1000a980  init_state ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named init_state (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: a new prototype and a fresh
   FuncState, locvars only with lua_debug); was lparser__a980. */

void __cdecl init_state(TaggedString *param_1)

{
  FuncState *pFVar1;
  TProtoFunc *pTVar2;
  
  pTVar2 = luaF_newproto();
  pFVar1 = g_pLuaState->pCurrState;
  pFVar1->nStackSize = 0;
  pFVar1->nMaxStackSize = 0;
  pFVar1->nLocalVar = 0;
  pFVar1->nUpvalues = 0;
  pFVar1->pF = pTVar2;
  pTVar2->pFileName = param_1;
  pFVar1->nPc = 0;
  pFVar1->nMaxCode = 0;
  pTVar2->pCode = (byte *)0x0;
  pFVar1->nMaxConsts = 0;
  if (lua_debug == 0) {
    pFVar1->nMaxVars = -1;
  }
  else {
    pFVar1->nVars = 0;
    pFVar1->nMaxVars = 0;
  }
  code_byte(0);
  code_byte(0);
  *(undefined4 *)((int)g_pLuaState->pLexState + 0x10) = 0;
  return;
}

/* ---- 0x1000aa10  code_byte ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_byte (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: check_pc(1), f->code[pc++] = c);
   was lparser__aa10. */

void __cdecl code_byte(byte param_1)

{
  int *piVar1;
  
  check_pc(1);
  g_pLuaState->pCurrState->pF->pCode[g_pLuaState->pCurrState->nPc] = param_1;
  piVar1 = &g_pLuaState->pCurrState->nPc;
  *piVar1 = *piVar1 + 1;
  return;
}

/* ---- 0x1000aa40  close_func ---- */
/* lua.stx: lua.stx error reporting Original name close_func (the remaster's libLua.so: remaster
   close_func (same body: shrinks code, constants and locvars with the lua.stx line numbers, pops
   the FuncState); was misnamed luaY_syntaxerror); was luaY_syntaxerror. */

int close_func(void)

{
  TProtoFunc *pTVar1;
  byte *pbVar2;
  TObject *pTVar3;
  LocVar *pLVar4;
  
  pTVar1 = g_pLuaState->pCurrState->pF;
  code_neutralop(0);
  *pTVar1->pCode = (byte)g_pLuaState->pCurrState->nMaxStackSize;
  pbVar2 = (byte *)(**(code **)(g_dwLuaHS + 0x28))
                             (pTVar1->pCode,g_pLuaState->pCurrState->nPc,s_lua_stx_10027b64,0x25c);
  pTVar1->pCode = pbVar2;
  pTVar3 = (TObject *)
           (**(code **)(g_dwLuaHS + 0x28))
                     (pTVar1->pConsts,pTVar1->nNconsts << 3,s_lua_stx_10027b64,0x25d);
  pTVar1->pConsts = pTVar3;
  if (g_pLuaState->pCurrState->nMaxVars != -1) {
    luaI_registerlocalvar(0,0xffffffff);
    pLVar4 = (LocVar *)
             (**(code **)(g_dwLuaHS + 0x28))
                       (pTVar1->pLocvars,g_pLuaState->pCurrState->nVars << 3,s_lua_stx_10027b64,
                        0x260);
    pTVar1->pLocvars = pLVar4;
  }
  g_pLuaState->pCurrState = g_pLuaState->pCurrState + -1;
  return (int)pTVar1;
}

/* ---- 0x1000ab20  code_neutralop ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_neutralop (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: code_opcode(op, 0)); was
   lparser__ab20. */

void __cdecl code_neutralop(undefined1 param_1)

{
  code_opcode(param_1,0);
  return;
}

/* ---- 0x1000ab30  code_opcode ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_opcode (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: deltastack(delta), code_byte(op));
   was lparser__ab30. */

void __cdecl code_opcode(undefined1 param_1,int param_2)

{
  deltastack(param_2);
  code_byte(param_1);
  return;
}

/* ---- 0x1000ab50  luaI_registerlocalvar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named luaI_registerlocalvar
   (not in the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: appends {varname,
   line} to f->locvars when debug info is on); was luaY_growvector. */

void __cdecl luaI_registerlocalvar(TaggedString *param_1,int param_2)

{
  FuncState *pFVar1;
  uint uVar2;
  
  pFVar1 = g_pLuaState->pCurrState;
  uVar2 = pFVar1->nMaxVars;
  if (uVar2 != 0xffffffff) {
    if ((int)uVar2 <= pFVar1->nVars) {
      uVar2 = luaM_growaux(&pFVar1->pF->pLocvars,uVar2,8,&DAT_1002bedc,0xfffe);
      pFVar1->nMaxVars = uVar2;
    }
    pFVar1->pF->pLocvars[pFVar1->nVars].pVarname = param_1;
    pFVar1->pF->pLocvars[pFVar1->nVars].nLine = param_2;
    pFVar1->nVars = pFVar1->nVars + 1;
  }
  return;
}

/* ---- 0x1000abd0  luaY_parse ---- */
/* lua.stx: generated LALR parser from lua.stx Original name luaY_parse (the remaster's libLua.so:
   strings 'parser stack overflow', 'invalid constructor syntax' (the bison yyparse, prefix luaY_));
   was yyparse. */

undefined4 luaY_parse(void)

{
  unsigned char _frame[0xbf0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  short sVar2;
  FuncState *pFVar3;
  FuncState *pFVar4;
  int iVar5;
  TaggedString *pTVar6;
  uint uVar7;
  uint uVar8;
  int *pfVar9;
  int fVar9;
  int iVar9;
  byte *pbVar10;
  int iVar11;
  byte *pbVar12;
  #define local_be0 (*(uint *)(_frame + (0xbf0 - 0xbe0)))
  #define local_bdc (*(int *)(_frame + (0xbf0 - 0xbdc)))
  #define local_bd8 (*(short **)(_frame + (0xbf0 - 0xbd8)))
  #define local_bd4 (*(int *)(_frame + (0xbf0 - 0xbd4)))
  #define local_bd0 (*(int *)(_frame + (0xbf0 - 0xbd0)))
  #define local_bcc (*(int *)(_frame + (0xbf0 - 0xbcc)))
  #define local_bc8 (*(int *)(_frame + (0xbf0 - 0xbc8)))
  #define local_bc4 (*(int *)(_frame + (0xbf0 - 0xbc4)))
  #define local_bc0 (*(uint *)(_frame + (0xbf0 - 0xbc0)))
  #define local_bbc (*(FuncState **)(_frame + (0xbf0 - 0xbbc)))
  #define local_bb8 (*(short (*)[499])(_frame + (0xbf0 - 0xbb8)))
  #define local_7d2 (*(short *)(_frame + (0xbf0 - 0x7d2)))
  #define local_7d0 (*(int *)(_frame + (0xbf0 - 0x7d0)))
  #define afStack_7cc (*(int (*)[499])(_frame + (0xbf0 - 0x7cc)))
  int fVar3;
  int fVar4;
  
  local_bd8 = local_bb8;
  iVar9 = 0;
  local_bdc = 0;
  local_bc4 = 0;
  local_be0 = 0xfffffffe;
  pfVar9 = &local_7d0;
  local_bb8[0] = 0;
  fVar9 = local_bc8;
  if (&local_7d2 <= local_bd8) {
LAB_1000b47d:
    luaY_error(s_parser_stack_overflow_10027b6c);
    return 2;
  }
LAB_1000ac11:
  sVar2 = g_wYypact[iVar9];
  if (sVar2 == -0x8000) {
LAB_1000b4fe:
    local_bd4 = (int)g_wYydefact[iVar9];
    if (local_bd4 == 0) {
LAB_1000b512:
      if (local_bdc == 0) {
        local_bc4 = local_bc4 + 1;
        luaY_error(s_parse_error_10027b58);
      }
      if (local_bdc == 3) {
        if (local_be0 == 0) {
          return 1;
        }
        local_be0 = 0xfffffffe;
      }
      local_bdc = 3;
      do {
        if (((g_wYypact[iVar9] != -0x8000) && (iVar9 = g_wYypact[iVar9] + 1, -1 < iVar9)) &&
           ((iVar9 < 0x107 && (g_aYycheck[iVar9] == 1)))) {
          local_bd4 = (int)g_aYytable[iVar9];
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
        iVar9 = (int)local_bd8[-1];
        pfVar9 = pfVar9 + -1;
        local_bd8 = local_bd8 + -1;
      } while( true );
    }
LAB_1000acaa:
    iVar9 = (int)g_aYyr2[local_bd4];
    if (0 < iVar9) {
      fVar9 = pfVar9[1 - iVar9];
    }
    local_bcc = iVar9;
    switch(local_bd4) {
    case 6:
      codeIf(pfVar9[-5],pfVar9[-2]);
      break;
    case 8:
      pFVar3 = g_pLuaState->pCurrState;
      uVar7 = pfVar9[-3] - pfVar9[-4];
      local_bc8 = pfVar9[-4] + 2;
      local_bc0 = uVar7;
      local_bbc = pFVar3;
      check_pc(uVar7);
      pFVar4 = local_bbc;
      pbVar12 = pFVar3->pF->pCode;
      pbVar10 = pbVar12 + pfVar9[-4];
      pbVar12 = pbVar12 + pFVar3->nPc;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pbVar12 = *(undefined4 *)pbVar10;
        pbVar10 = pbVar10 + 4;
        pbVar12 = pbVar12 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pbVar12 = *pbVar10;
        pbVar10 = pbVar10 + 1;
        pbVar12 = pbVar12 + 1;
      }
      pbVar12 = local_bbc->pF->pCode;
      memcpy((undefined4 *)(pbVar12 + pfVar9[-4]),(undefined4 *)(pbVar12 + pfVar9[-3]),
             local_bbc->nPc - pfVar9[-4]);
      iVar9 = fix_jump(pfVar9[-4],'m',pFVar4->nPc - local_bc0);
      fix_upjmp('q',local_bc8 + iVar9);
      iVar9 = local_bcc;
      break;
    case 9:
      fix_upjmp('s',pfVar9[-3]);
      deltastack(-1);
      break;
    case 10:
      iVar9 = 0;
      adjust_mult_assign(pfVar9[-2],*pfVar9);
      fVar3 = pfVar9[-2];
      while (fVar3 = fVar3 + -1, -1 < fVar3) {
        iVar9 = lua_codestore(fVar3,iVar9);
      }
      adjuststack(iVar9);
      iVar9 = local_bcc;
      break;
    case 0xb:
      adjust_functioncall(*pfVar9,0);
      break;
    case 0xc:
      g_pLuaState->pCurrState->nLocalVar = g_pLuaState->pCurrState->nLocalVar + pfVar9[-1];
      adjust_mult_assign(pfVar9[-1],*pfVar9);
      break;
    case 0xd:
      storevar(pfVar9[-1]);
      break;
    case 0xe:
      fVar9 = g_pLuaState->pCurrState->nLocalVar;
      break;
    case 0xf:
      adjuststack(g_pLuaState->pCurrState->nLocalVar - pfVar9[-1]);
      if (pfVar9[-1] < g_pLuaState->pCurrState->nLocalVar) {
        do {
          luaI_unregisterlocalvar(*(undefined4 *)((int)g_pLuaState->pLexState + 8));
          g_pLuaState->pCurrState->nLocalVar = g_pLuaState->pCurrState->nLocalVar + -1;
        } while (pfVar9[-1] < g_pLuaState->pCurrState->nLocalVar);
      }
      break;
    case 0x10:
      fVar9 = *pfVar9;
      init_func();
      break;
    case 0x11:
      fVar9 = 0;
      init_func();
      break;
    case 0x12:
      fVar9 = 0;
      init_func();
      pTVar6 = luaS_new(&DAT_10027ba0);
      add_localvar(pTVar6);
      break;
    case 0x13:
      lua_pushvar(*pfVar9);
      break;
    case 0x14:
      code_string(*pfVar9);
      break;
    case 0x15:
      close_func();
      func_onstack();
      break;
    case 0x18:
      codeIf(pfVar9[-4],pfVar9[-1]);
      break;
    case 0x1a:
      adjust_functioncall(pfVar9[-1],0xff);
      codereturn();
      break;
    case 0x1b:
      fVar9 = g_pLuaState->pCurrState->nPc;
      break;
    case 0x1c:
      fVar9 = g_pLuaState->pCurrState->nPc;
      check_pc(2);
      piVar1 = &g_pLuaState->pCurrState->nPc;
      *piVar1 = *piVar1 + 2;
      break;
    case 0x1d:
      fVar9 = *pfVar9;
      deltastack(-1);
      break;
    case 0x1e:
      fVar9 = *pfVar9;
      deltastack(1);
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
      fVar9 = *pfVar9;
      break;
    case 0x20:
      adjust_functioncall(*pfVar9,1);
      break;
    case 0x22:
      code_pop(0x5b);
      fVar9 = 0;
      break;
    case 0x23:
      code_pop(0x5d);
      fVar9 = 0;
      break;
    case 0x24:
      code_pop(0x5f);
      fVar9 = 0;
      break;
    case 0x25:
      code_pop(0x5c);
      fVar9 = 0;
      break;
    case 0x26:
      code_pop(0x5e);
      fVar9 = 0;
      break;
    case 0x27:
      code_pop(0x60);
      fVar9 = 0;
      break;
    case 0x28:
      code_pop(0x61);
      fVar9 = 0;
      break;
    case 0x29:
      code_pop(0x62);
      fVar9 = 0;
      break;
    case 0x2a:
      code_pop(99);
      fVar9 = 0;
      break;
    case 0x2b:
      code_pop(100);
      fVar9 = 0;
      break;
    case 0x2c:
      code_pop(0x65);
      fVar9 = 0;
      break;
    case 0x2d:
      code_pop(0x66);
      fVar9 = 0;
      break;
    case 0x2e:
      code_neutralop(0x67);
      fVar9 = 0;
      break;
    case 0x2f:
      code_neutralop(0x68);
      fVar9 = 0;
      break;
    case 0x31:
    case 0x36:
    case 0x3e:
    case 0x43:
    case 0x48:
    case 0x53:
    case 0x65:
      fVar9 = 0;
      break;
    case 0x32:
      code_number(PUN(float,PUN(float,*pfVar9)));
      fVar9 = 0;
      break;
    case 0x33:
      code_string(*pfVar9);
      fVar9 = 0;
      break;
    case 0x34:
      adjuststack(-1);
      fVar9 = 0;
      break;
    case 0x35:
      init_func();
      break;
    case 0x37:
      code_shortcircuit(pfVar9[-1],'k');
      fVar9 = 0;
      break;
    case 0x38:
      code_shortcircuit(pfVar9[-1],'i');
      fVar9 = 0;
      break;
    case 0x39:
      adjust_functioncall(*pfVar9,1);
      break;
    case 0x3a:
      lua_pushvar(*pfVar9);
      fVar9 = 0;
      break;
    case 0x3b:
      pushupvalue(*pfVar9);
      fVar9 = 0;
      break;
    case 0x3f:
      iVar5 = string_constant(*pfVar9,(int *)g_pLuaState->pCurrState);
      fVar9 = -1 - iVar5;
      break;
    case 0x40:
      fVar9 = singlevar(*pfVar9,(int *)g_pLuaState->pCurrState);
      break;
    case 0x41:
      fix_opcode(pfVar9[-2],'=',2,pfVar9[-1]);
      break;
    case 0x42:
      code_byte(0);
      code_byte(*(char *)(pfVar9 + -1) + *(char *)pfVar9);
      fVar9 = g_pLuaState->pCurrState->nPc;
      code_byte(0);
      break;
    case 0x44:
      iVar5 = 1;
      uVar8 = string_constant(*pfVar9,(int *)g_pLuaState->pCurrState);
      code_oparg('3',8,uVar8,iVar5);
      fVar9 = 1;
      break;
    case 0x45:
      fVar9 = adjust_functioncall(pfVar9[-1],1);
      break;
    case 0x47:
      code_string(*pfVar9);
      fVar9 = 1;
      break;
    case 0x4a:
      fVar9 = *pfVar9;
      if (PUN(float,fVar9) == 0.0f) {
        fVar9 = -1;
      }
      break;
    case 0x4b:
      fVar9 = adjust_functioncall(pfVar9[-1],1);
      break;
    case 0x4c:
      if (PUN(float,*pfVar9) != 0.0f) {
        g_pLuaState->pCurrState->pF->pCode[*pfVar9] = *(byte *)(pfVar9 + -1);
        goto switchD_1000acd8_caseD_1f;
      }
      fVar9 = -1 - pfVar9[-1];
      break;
    case 0x4d:
      code_args(0,0);
      break;
    case 0x4e:
      code_args(0,1);
      break;
    case 0x4f:
      code_args(*pfVar9,0);
      break;
    case 0x50:
      code_args(pfVar9[-2],1);
      break;
    case 0x51:
      uVar8 = *pfVar9 >> 0x1f;
      fVar9 = (*pfVar9 ^ uVar8) - uVar8;
      break;
    case 0x52:
      if (0 < *pfVar9 * pfVar9[-2]) {
        luaY_error(s_invalid_constructor_syntax_10027b84);
      }
      uVar8 = *pfVar9 >> 0x1f;
      uVar7 = pfVar9[-2] >> 0x1f;
      fVar9 = ((*pfVar9 ^ uVar8) - uVar8) + ((pfVar9[-2] ^ uVar7) - uVar7);
      break;
    case 0x58:
      uVar8 = pfVar9[-1] >> 0x1f;
      flush_record(((pfVar9[-1] ^ uVar8) - uVar8 & 0x1f ^ uVar8) - uVar8);
      fVar9 = -pfVar9[-1];
      break;
    case 0x59:
      fVar4 = pfVar9[-1];
      uVar8 = fVar4 >> 0x1f;
      flush_list((int)(fVar4 + (uVar8 & 0x3f)) >> 6,((fVar4 ^ uVar8) - uVar8 & 0x3f ^ uVar8) - uVar8
                );
    case 0x21:
      fVar9 = pfVar9[-1];
      break;
    case 0x5b:
      fVar9 = pfVar9[-2] + 1;
      uVar8 = fVar9 >> 0x1f;
      if (((fVar9 ^ uVar8) - uVar8 & 0x1f ^ uVar8) == uVar8) {
        flush_record(0x20);
      }
      break;
    case 0x60:
      fVar9 = pfVar9[-2] + 1;
      uVar8 = fVar9 >> 0x1f;
      if (((fVar9 ^ uVar8) - uVar8 & 0x3f ^ uVar8) == uVar8) {
        flush_list(((int)(fVar9 + (uVar8 & 0x3f)) >> 6) - 1,0x40);
      }
      break;
    case 0x61:
      fVar9 = 1;
      add_varbuffer(*pfVar9,0);
      break;
    case 0x62:
      add_varbuffer(*pfVar9,pfVar9[-2]);
      fVar9 = pfVar9[-2] + 1;
      break;
    case 99:
      store_localvar(*pfVar9,0);
    case 0x46:
    case 0x5a:
    case 0x5f:
      fVar9 = 1;
      break;
    case 100:
      store_localvar(*pfVar9,pfVar9[-2]);
      fVar9 = pfVar9[-2] + 1;
    }
    local_bd8 = local_bd8 + -iVar9;
    pfVar9 = pfVar9 + (1 - iVar9);
    *pfVar9 = fVar9;
    iVar9 = (int)g_wYypact[g_aYyr1[local_bd4] + 0x87] + (int)*local_bd8;
    if (((iVar9 < 0) || (0x106 < iVar9)) || (g_aYycheck[iVar9] != *local_bd8)) {
      local_bd4 = (int)g_wYydefact[g_aYyr1[local_bd4] + 0x87];
    }
    else {
      local_bd4 = (int)g_aYytable[iVar9];
    }
  }
  else {
    if (local_be0 == 0xfffffffe) {
      local_be0 = luaY_lex((float *)&local_bd0);
    }
    if ((int)local_be0 < 1) {
      iVar5 = 0;
      local_be0 = 0;
    }
    else if (local_be0 < 0x11d) {
      iVar5 = (int)g_aYytranslate[local_be0];
    }
    else {
      iVar5 = 0x5d;
    }
    iVar11 = sVar2 + iVar5;
    if (((iVar11 < 0) || (0x106 < iVar11)) || (g_aYycheck[iVar11] != iVar5)) goto LAB_1000b4fe;
    local_bd4 = (int)g_aYytable[iVar11];
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
  iVar9 = local_bd4;
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


/* ---- 0x1000b770  fix_opcode ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named fix_opcode (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: rewrites the op at pc, moving the
   code when the argument shrinks); was lparser__b770. */

int __cdecl fix_opcode(int param_1,char param_2,int param_3,uint param_4)

{
  FuncState *pFVar1;
  byte *pbVar2;
  int iVar3;
  
  pFVar1 = g_pLuaState->pCurrState;
  if ((int)param_4 < param_3) {
    pbVar2 = pFVar1->pF->pCode;
    memcpy((undefined4 *)(pbVar2 + param_1 + 1),(undefined4 *)(pbVar2 + param_1 + 2),
           (pFVar1->nPc - param_1) - 2);
    iVar3 = pFVar1->nPc + -1;
  }
  else {
    if ((int)param_4 < 0x100) goto LAB_1000b7e3;
    check_pc(1);
    pbVar2 = pFVar1->pF->pCode + param_1;
    memcpy((undefined4 *)(pbVar2 + 1),(undefined4 *)pbVar2,pFVar1->nPc - param_1);
    iVar3 = pFVar1->nPc + 1;
  }
  pFVar1->nPc = iVar3;
LAB_1000b7e3:
  iVar3 = code_oparg_at(param_1,param_2,param_3,param_4,0);
  return iVar3 + -2;
}

/* ---- 0x1000b800  code_pop ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_pop (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: code_opcode(op, -1)); was
   lparser__b800. */

void __cdecl code_pop(undefined1 param_1)

{
  code_opcode(param_1,-1);
  return;
}

/* ---- 0x1000b810  string_constant ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named string_constant (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx static string_constant: reuses
   the string's constindex when consts[i] is that string, else next_constant and stores it); was
   luaY_string_constant. */

uint __cdecl string_constant(int param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *param_2;
  uVar2 = *(uint *)(param_1 + 8);
  if (((*(uint *)(iVar1 + 0xc) <= uVar2) || (*(int *)(*(int *)(iVar1 + 8) + uVar2 * 8) != -2)) ||
     (*(int *)(*(int *)(iVar1 + 8) + uVar2 * 8 + 4) != param_1)) {
    uVar2 = next_constant(param_2);
    *(undefined4 *)(*(int *)(iVar1 + 8) + uVar2 * 8) = 0xfffffffe;
    *(int *)(*(int *)(iVar1 + 8) + 4 + uVar2 * 8) = param_1;
    *(uint *)(param_1 + 8) = uVar2;
  }
  return uVar2;
}

/* ---- 0x1000b860  next_constant ---- */
/* lua.stx: constant table overflow Named next_constant (not in the remaster, gcc inlined it there):
   Lua 3.1 source name (lua.stx static next_constant: luaM_growvector of consts, error "constant
   table overflow"); was luaY_next_constant. */

int __cdecl next_constant(int *param_1)

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

/* ---- 0x1000b8a0  code_string ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_string (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: code_constant(string_constant(s,
   fs))); was lparser__b8a0. */

void __cdecl code_string(int param_1)

{
  uint uVar1;
  
  uVar1 = string_constant(param_1,(int *)g_pLuaState->pCurrState);
  code_constant(uVar1);
  return;
}

/* ---- 0x1000b8c0  code_constant ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_constant (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: code_oparg(PUSHCONSTANT, 8, c,
   1)); was lparser__b8c0. */

void __cdecl code_constant(uint param_1)

{
  code_oparg('\b',8,param_1,1);
  return;
}

/* ---- 0x1000b8e0  code_number ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_number (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx static code_number: PUSHNUMBER for
   an integer in 0..65534 (code_oparg), else code_constant(real_constant(f))); was luaY_code_number.
    */

void __cdecl code_number(float param_1)

{
  uint uVar1;
  longlong lVar2;
  
  if ((0.0f <= param_1) && (param_1 <= 65534.0f)) {
    lVar2 = FTOL((float10)param_1);
    if ((float)(int)(uint)lVar2 == param_1) {
      code_oparg('\x03',3,(uint)lVar2,1);
      return;
    }
  }
  uVar1 = real_constant(param_1);
  code_constant(uVar1);
  return;
}

/* ---- 0x1000b950  real_constant ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named real_constant (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx static real_constant: searches
   the last 20 constants for the number (LOOKBACKNUMS), else next_constant); was luaY_real_constant.
    */

int __cdecl real_constant(float param_1)

{
  TProtoFunc *pTVar1;
  int iVar2;
  TObject *pTVar3;
  int iVar4;
  
  pTVar1 = g_pLuaState->pCurrState->pF;
  iVar2 = pTVar1->nNconsts;
  if (iVar2 < 0x14) {
    iVar4 = 0;
  }
  else {
    iVar4 = iVar2 + -0x14;
  }
  iVar2 = iVar2 + -1;
  if (iVar4 <= iVar2) {
    pTVar3 = pTVar1->pConsts + iVar2;
    do {
      if ((pTVar3->nTtype == -1) && (PUN(float,pTVar3->dwValue) == param_1)) {
        return iVar2;
      }
      iVar2 = iVar2 + -1;
      pTVar3 = pTVar3 + -1;
    } while (iVar4 <= iVar2);
  }
  iVar2 = next_constant((int *)g_pLuaState->pCurrState);
  pTVar3 = g_pLuaState->pCurrState->pF->pConsts;
  pTVar3[iVar2].nTtype = -1;
  pTVar3[iVar2].dwValue = PUN(uint,(float)(param_1));
  return iVar2;
}

/* ---- 0x1000b9c0  flush_record ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named flush_record (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: SETMAP n-1 with delta -2n); was
   lparser__b9c0. */

void __cdecl flush_record(int param_1)

{
  if (0 < param_1) {
    code_oparg('Y',1,param_1 - 1,param_1 * -2);
  }
  return;
}

/* ---- 0x1000b9e0  flush_list ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named flush_list (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: SETLIST m with delta -n, then the
   count byte); was lparser__b9e0. */

void __cdecl flush_list(uint param_1,int param_2)

{
  if (param_2 != 0) {
    code_oparg('V',1,param_1,-param_2);
    code_byte((char)param_2);
  }
  return;
}

/* ---- 0x1000ba10  luaI_unregisterlocalvar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named luaI_unregisterlocalvar
   (not in the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx:
   luaI_registerlocalvar(NULL, line)); was lparser__ba10. */

void __cdecl luaI_unregisterlocalvar(undefined4 param_1)

{
  luaI_registerlocalvar(0,param_1);
  return;
}

/* ---- 0x1000ba20  store_localvar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named store_localvar (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: 'too many local variables',
   localvar[nlocalvar+n] = name, luaI_registerlocalvar); was lparser__ba20. */

void __cdecl store_localvar(TaggedString *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = g_pLuaState->pCurrState->nLocalVar + param_2;
  if (iVar1 < 0x20) {
    g_pLuaState->pCurrState->aLocalVar[iVar1] = param_1;
  }
  else {
    luaY_error(s_too_many_local_variables__limit__10027bc0);
  }
  luaI_registerlocalvar(param_1,*(undefined4 *)((int)g_pLuaState->pLexState + 8));
  return;
}

/* ---- 0x1000ba70  add_localvar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named add_localvar (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: store_localvar(name, 0),
   nlocalvar++); was lparser__ba70. */

void __cdecl add_localvar(undefined4 param_1)

{
  int *piVar1;
  
  store_localvar(param_1,0);
  piVar1 = &g_pLuaState->pCurrState->nLocalVar;
  *piVar1 = *piVar1 + 1;
  return;
}

/* ---- 0x1000ba90  add_varbuffer ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Original name add_varbuffer
   (the remaster's libLua.so: static add_varbuffer: string 'variable buffer overflow (limit=32)');
   was lparser__ba90. */

void __cdecl add_varbuffer(int param_1,int param_2)

{
  int iVar1;
  
  if (0x1f < param_2) {
    luaY_error(s_variable_buffer_overflow__limit__10027be4);
  }
  iVar1 = var2store(param_1);
  g_pLuaState->pCurrState->aUpvalues[param_2 + -0x20] = iVar1;
  return;
}

/* ---- 0x1000bad0  var2store ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named var2store (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: a dotted variable codes its
   constant and becomes 0, used by add_varbuffer); was lparser__bad0. */

int __cdecl var2store(int param_1)

{
  if (param_1 < 0) {
    code_constant(-param_1 - 1);
    param_1 = 0;
  }
  return param_1;
}

/* ---- 0x1000baf0  singlevar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named singlevar (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: local, global or 'cannot access a
   variable in outer scope'); was lparser__baf0. */

int __cdecl singlevar(int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = aux_localname(param_1,(int)param_2);
  if (iVar2 != -1) {
    return iVar2 + 1;
  }
  iVar2 = 1;
  piVar1 = param_2;
  if (0 < ((int)param_2 - (int)g_pLuaState->pMainState) / 0x168) {
    do {
      iVar3 = aux_localname(param_1,(int)(piVar1 + -0x5a));
      if (-1 < iVar3) {
        luaY_syntaxerror(s_cannot_access_a_variable_in_oute_10027c08,(char *)(param_1 + 0x18));
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + -0x5a;
    } while (iVar2 <= ((int)param_2 - (int)g_pLuaState->pMainState) / 0x168);
  }
  iVar2 = string_constant(param_1,param_2);
  return iVar2 + 0x21;
}

/* ---- 0x1000bba0  aux_localname ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named aux_localname (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: the index of a local name in a
   FuncState or -1); was lparser__bba0. */

int __cdecl aux_localname(int param_1,int param_2)

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

/* ---- 0x1000bbd0  pushupvalue ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named pushupvalue (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: 'cannot access upvalue in main',
   PUSHUPVALUE indexupvalue(n)); was lparser__bbd0. */

void __cdecl pushupvalue(int param_1)

{
  int iVar1;
  uint uVar2;
  
  if (g_pLuaState->pCurrState == g_pLuaState->pMainState) {
    luaY_error(s_cannot_access_upvalue_in_main_10027c5c);
  }
  iVar1 = aux_localname(param_1,(int)g_pLuaState->pCurrState);
  if (-1 < iVar1) {
    luaY_syntaxerror(s_cannot_access_an_upvalue_in_curr_10027c30,(char *)(param_1 + 0x18));
  }
  uVar2 = indexupvalue(param_1);
  code_oparg('\x12',2,uVar2,1);
  return;
}

/* ---- 0x1000bc40  indexupvalue ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named indexupvalue (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: index of an upvalue, added if
   new); was lparser__bc40. */

int __cdecl indexupvalue(int param_1)

{
  FuncState *pFVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar3 = singlevar(param_1,(int *)(g_pLuaState->pCurrState + -1));
  iVar5 = 0;
  pFVar1 = g_pLuaState->pCurrState;
  iVar2 = pFVar1->nUpvalues;
  if (0 < iVar2) {
    piVar4 = pFVar1->aUpvalues;
    do {
      if (*piVar4 == iVar3) {
        return iVar5;
      }
      iVar5 = iVar5 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar5 < iVar2);
  }
  pFVar1->nUpvalues = iVar2 + 1;
  if (0x10 < g_pLuaState->pCurrState->nUpvalues) {
    luaY_error(s_too_many_upvalues_in_a_single_fu_10027c7c);
  }
  g_pLuaState->pCurrState->aUpvalues[iVar5] = iVar3;
  return iVar5;
}

/* ---- 0x1000bcc0  adjuststack ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named adjuststack (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: POP n or PUSHNIL -n); was
   lparser__bcc0. */

void __cdecl adjuststack(int param_1)

{
  if (0 < param_1) {
    code_oparg('~',2,param_1 - 1,-param_1);
    return;
  }
  if (param_1 < 0) {
    code_oparg('\x01',1,-param_1 - 1,-param_1);
  }
  return;
}

/* ---- 0x1000bd00  adjust_functioncall ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named adjust_functioncall (not
   in the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: fixes the result count of a
   call); was lparser__bd00. */

int __cdecl adjust_functioncall(int param_1,uint param_2)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  
  if (param_1 < 1) {
    return -param_1;
  }
  pbVar3 = g_pLuaState->pCurrState->pF->pCode + param_1;
  bVar1 = *pbVar3;
  bVar2 = pbVar3[-1];
  iVar4 = fix_opcode(param_1 + -2,'x',2,param_2);
  g_pLuaState->pCurrState->pF->pCode[param_1 + iVar4] = bVar2;
  if (param_2 != 0xff) {
    deltastack(param_2);
  }
  deltastack(-1 - (uint)bVar2);
  return bVar1 + param_2;
}

/* ---- 0x1000bd80  adjust_mult_assign ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named adjust_mult_assign (not
   in the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: adjust_functioncall /
   adjuststack for vars = exps); was lparser__bd80. */

void __cdecl adjust_mult_assign(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 < 1) {
    adjuststack(-(param_2 + param_1));
    return;
  }
  iVar1 = (uint)g_pLuaState->pCurrState->pF->pCode[param_2] - param_1;
  if (iVar1 < 0) {
    adjust_functioncall(param_2,-iVar1);
    return;
  }
  adjust_functioncall(param_2,0);
  adjuststack(iVar1);
  return;
}

/* ---- 0x1000bde0  code_args ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_args (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: nlocalvar += nparams, VARARGS when
   dots); was lparser__bde0. */

void __cdecl code_args(int param_1,int param_2)

{
  FuncState *pFVar1;
  int iVar2;
  TaggedString *pTVar3;
  
  g_pLuaState->pCurrState->nLocalVar = g_pLuaState->pCurrState->nLocalVar + param_1;
  pFVar1 = g_pLuaState->pCurrState;
  iVar2 = pFVar1->nLocalVar;
  if (param_2 == 0) {
    pFVar1->pF->pCode[1] = (byte)iVar2;
    deltastack(iVar2);
    return;
  }
  pFVar1->pF->pCode[1] = (byte)iVar2 + 0x40;
  deltastack(iVar2 + 1);
  pTVar3 = luaS_new(&DAT_10027cb0);
  add_localvar(pTVar3);
  return;
}

/* ---- 0x1000be60  lua_pushvar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named lua_pushvar (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: PUSHLOCAL / GETGLOBAL / GETTABLE /
   GETDOTTED by vardesc); was lparser__be60. */

void __cdecl lua_pushvar(int param_1)

{
  if (0x20 < param_1) {
    code_oparg('\x1e',8,param_1 - 0x21,1);
    return;
  }
  if ((0 < param_1) && (param_1 < 0x21)) {
    code_oparg('\x15',8,param_1 - 1,1);
    return;
  }
  if (-1 < param_1) {
    code_pop(0x28);
    return;
  }
  ((code *)code_oparg)(')',8,-param_1 - 1,0);
  return;
}

/* ---- 0x1000bec0  storevar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named storevar (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: SETLOCAL / SETGLOBAL / SETTABLE0
   by vardesc); was lparser__bec0. */

void __cdecl storevar(int param_1)

{
  if (param_1 == 0) {
    code_opcode(0x54,-3);
    return;
  }
  if (0x20 < param_1) {
    code_oparg('J',8,param_1 - 0x21,-1);
    return;
  }
  code_oparg('A',8,param_1 - 1,-1);
  return;
}

/* ---- 0x1000bf00  lua_codestore ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named lua_codestore (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: the store of assignment i,
   SETTABLE when left items are on the stack); was lparser__bf00. */

int __cdecl lua_codestore(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = g_pLuaState->pCurrState->aUpvalues[param_1 + -0x20];
  if ((iVar1 == 0) && (param_1 + param_2 != 0)) {
    code_oparg('U',0,param_1 + param_2,-1);
    return param_2 + 2;
  }
  storevar(iVar1);
  return param_2;
}

/* ---- 0x1000bf50  fix_jump ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named fix_jump (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: fix_opcode(pc, op, 0, n - pc -
   2)); was lparser__bf50. */

int __cdecl fix_jump(int param_1,char param_2,int param_3)

{
  int iVar1;
  
  iVar1 = fix_opcode(param_1,param_2,0,(param_3 - param_1) - 2);
  return iVar1;
}

/* ---- 0x1000bf70  fix_upjmp ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named fix_upjmp (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: a backward jump to pos); was
   lparser__bf70. */

void __cdecl fix_upjmp(char param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = g_pLuaState->pCurrState->nPc - param_2;
  uVar2 = iVar1 + 2;
  if (0xff < (int)uVar2) {
    uVar2 = iVar1 + 3;
  }
  code_oparg(param_1,0,uVar2,0);
  return;
}

/* ---- 0x1000bfa0  codeIf ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named codeIf (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: fix_jump of the then part and of
   the jump over the else part); was lparser__bfa0. */

void __cdecl codeIf(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = g_pLuaState->pCurrState->nPc;
  if (iVar1 == param_2 + 2) {
    g_pLuaState->pCurrState->nPc = iVar1 + -2;
    fix_jump(param_1,'o',g_pLuaState->pCurrState->nPc);
    return;
  }
  iVar1 = fix_jump(param_2,'m',iVar1);
  fix_jump(param_1,'o',param_2 + 2 + iVar1);
  return;
}

/* ---- 0x1000c000  code_shortcircuit ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_shortcircuit (not
   in the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: fix_jump(pc, jmp, pc of the
   end)); was lparser__c000. */

void __cdecl code_shortcircuit(int param_1,char param_2)

{
  fix_jump(param_1,param_2,g_pLuaState->pCurrState->nPc);
  return;
}

/* ---- 0x1000c020  codereturn ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named codereturn (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: RETCODE nlocalvar, stacksize =
   nlocalvar); was lparser__c020. */

void codereturn(void)

{
  ((code *)code_oparg)('{',0,g_pLuaState->pCurrState->nLocalVar,0);
  g_pLuaState->pCurrState->nStackSize = g_pLuaState->pCurrState->nLocalVar;
  return;
}

/* ---- 0x1000c060  func_onstack ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named func_onstack (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: a LUA_T_PROTO constant for the new
   function, its upvalues, CLOSURE); was lparser__c060. */

void func_onstack(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar1 = g_pLuaState->pCurrState[1].nUpvalues;
  uVar2 = next_constant((int *)g_pLuaState->pCurrState);
  g_pLuaState->pCurrState->pF->pConsts[uVar2].nTtype = -4;
  g_pLuaState->pCurrState->pF->pConsts[uVar2].dwValue = (uint)g_pLuaState->pCurrState[1].pF;
  if (uVar1 != 0) {
    if (0 < (int)uVar1) {
      iVar3 = 0x290;
      uVar4 = uVar1;
      do {
        lua_pushvar(*(int *)((int)g_pLuaState->pCurrState->aLocalVar + iVar3 + -8));
        iVar3 = iVar3 + 4;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
    code_constant(uVar2);
    code_oparg('u',2,uVar1,-uVar1);
    return;
  }
  code_constant(uVar2);
  return;
}

/* ---- 0x1000c100  init_func ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named init_func (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: 'too many nested functions', next
   FuncState, init_state, luaY_codedebugline); was lparser__c100. */

void init_func(void)

{
  if (4 < ((int)g_pLuaState->pCurrState - (int)g_pLuaState->pMainState) / 0x168) {
    luaY_error(s_too_many_nested_functions__limit_10027cb4);
  }
  g_pLuaState->pCurrState = g_pLuaState->pCurrState + 1;
  init_state(g_pLuaState->pMainState->pF->pFileName);
  luaY_codedebugline(*(uint *)((int)g_pLuaState->pLexState + 8));
  g_pLuaState->pCurrState->pF->nLineDefined = *(int *)((int)g_pLuaState->pLexState + 8);
  return;
}
