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

void __cdecl luaY_codedebugline(uint line)

{
  if ((lua_debug != 0) && (line != *(uint *)((int)g_pLuaState->pLexState + 0x10))) {
    code_oparg('|',0,line,0);
    *(uint *)((int)g_pLuaState->pLexState + 0x10) = line;
  }
  return;
}

/* ---- 0x1000a790  code_oparg ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_oparg (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: check_pc(3), pc +=
   code_oparg_at(pc, ...)); was luaY_code_opcode_arg. */

void __cdecl code_oparg(char op,int builtin,uint arg,int delta)

{
  FuncState *pFVar1;
  int iVar2;
  
  check_pc(3);
  pFVar1 = g_pLuaState->pCurrState;
  iVar2 = code_oparg_at(pFVar1->nPc,op,builtin,arg,delta);
  pFVar1->nPc = pFVar1->nPc + iVar2;
  return;
}

/* ---- 0x1000a7d0  check_pc ---- */
/* lua.stx: code size overflow Named check_pc (not in the remaster, gcc inlined it there): Lua 3.1
   source name (lua.stx: grows f->code for n more bytes, 'code size overflow'); was luaY_code_byte.
    */

void __cdecl check_pc(int n)

{
  FuncState *pFVar1;
  uint uVar2;
  
  pFVar1 = g_pLuaState->pCurrState;
  if (pFVar1->nMaxCode < pFVar1->nPc + n) {
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

undefined4 __cdecl code_oparg_at(int pc,char op,int builtin,uint arg,int delta)

{
  byte *pbVar1;
  byte bVar2;
  
  pbVar1 = g_pLuaState->pCurrState->pF->pCode;
  deltastack(delta);
  bVar2 = (byte)arg;
  if ((int)arg < builtin) {
    pbVar1[pc] = bVar2 + op + 1;
    return 1;
  }
  if ((int)arg < 0x100) {
    pbVar1[pc] = op;
    pbVar1[pc + 1] = bVar2;
    return 2;
  }
  if (arg < 0xffff) {
    pbVar1[pc] = (char)builtin + op + 1;
    pbVar1[pc + 1] = bVar2;
    pbVar1[pc + 2] = (byte)(arg >> 8);
    return 3;
  }
  luaY_error(s_code_too_long__limit_64K__10027b1c);
  return 0;
}

/* ---- 0x1000a8b0  deltastack ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named deltastack (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: stacksize += delta,
   'function/expression too complex'); was lparser__a8b0. */

void __cdecl deltastack(int delta)

{
  FuncState *pFVar1;
  int iVar2;
  
  pFVar1 = g_pLuaState->pCurrState;
  iVar2 = pFVar1->nStackSize + delta;
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
int __cdecl luaY_parser(int z)

{
  unsigned char _frame[0x8e0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  TaggedString *filename;
  int iVar1;
  #define local_8c4 (*(undefined1 (*)[84])(_frame + (0x8e0 - 0x8c4)))
  #define local_870 (*(FuncState (*)[6])(_frame + (0x8e0 - 0x870)))
  
                    /* 0xa900  4  luaY_parser */
  g_pLuaState->pMainState = local_870;
  g_pLuaState->pCurrState = g_pLuaState->pMainState;
  g_pLuaState->pLexState = local_8c4;
  luaX_setinput(z);
  filename = luaS_new(*(char **)(z + 0x10));
  init_state(filename);
  iVar1 = luaY_parse();
  if (iVar1 != 0) {
    lua_error((byte *)s_parse_error_10027b58);
  }
  iVar1 = close_func();
  return iVar1;
}
#undef local_870
#undef local_8c4


/* ---- 0x1000a980  init_state ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named init_state (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: a new prototype and a fresh
   FuncState, locvars only with lua_debug); was lparser__a980. */

void __cdecl init_state(TaggedString *filename)

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
  pTVar2->pFileName = filename;
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

void __cdecl code_byte(byte c)

{
  int *piVar1;
  
  check_pc(1);
  g_pLuaState->pCurrState->pF->pCode[g_pLuaState->pCurrState->nPc] = c;
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
    luaI_registerlocalvar((TaggedString *)0x0,-1);
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

void __cdecl code_neutralop(undefined1 op)

{
  code_opcode(op,0);
  return;
}

/* ---- 0x1000ab30  code_opcode ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_opcode (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: deltastack(delta), code_byte(op));
   was lparser__ab30. */

void __cdecl code_opcode(byte op,int delta)

{
  deltastack(delta);
  code_byte(op);
  return;
}

/* ---- 0x1000ab50  luaI_registerlocalvar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named luaI_registerlocalvar
   (not in the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: appends {varname,
   line} to f->locvars when debug info is on); was luaY_growvector. */

void __cdecl luaI_registerlocalvar(TaggedString *varname,int line)

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
    pFVar1->pF->pLocvars[pFVar1->nVars].pVarname = varname;
    pFVar1->pF->pLocvars[pFVar1->nVars].nLine = line;
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
  unsigned char _frame[0xbe0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  short sVar2;
  FuncState *pFVar3;
  FuncState *pFVar4;
  int iVar5;
  TaggedString *pTaggedString;
  uint uVar6;
  uint uVar7;
  int *pfVar9;
  int fVar9;
  int iVar8;
  byte *pbVar9;
  int iVar10;
  byte *pbVar11;
  uint local_be0;
  int local_bdc;
  short *local_bd8;
  int local_bd4;
  #define local_bd0 (*(int *)(_frame + (0xbe0 - 0xbd0)))
  #define local_bcc (*(int *)(_frame + (0xbe0 - 0xbcc)))
  #define local_bc8 (*(int *)(_frame + (0xbe0 - 0xbc8)))
  #define local_bc4 (*(int *)(_frame + (0xbe0 - 0xbc4)))
  #define local_bc0 (*(uint *)(_frame + (0xbe0 - 0xbc0)))
  #define local_bbc (*(FuncState **)(_frame + (0xbe0 - 0xbbc)))
  #define local_bb8 (*(short (*)[499])(_frame + (0xbe0 - 0xbb8)))
  #define local_7d2 (*(short *)(_frame + (0xbe0 - 0x7d2)))
  #define local_7d0 (*(int *)(_frame + (0xbe0 - 0x7d0)))
  int afStack_7cc [499];
  int fVar3;
  int fVar4;
  
  local_bd8 = local_bb8;
  iVar8 = 0;
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
  sVar2 = g_wYypact[iVar8];
  if (sVar2 == -0x8000) {
LAB_1000b4fe:
    local_bd4 = (int)g_wYydefact[iVar8];
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
        if (((g_wYypact[iVar8] != -0x8000) && (iVar8 = g_wYypact[iVar8] + 1, -1 < iVar8)) &&
           ((iVar8 < 0x107 && (g_aYycheck[iVar8] == 1)))) {
          local_bd4 = (int)g_aYytable[iVar8];
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
        iVar8 = (int)local_bd8[-1];
        pfVar9 = pfVar9 + -1;
        local_bd8 = local_bd8 + -1;
      } while( true );
    }
LAB_1000acaa:
    iVar8 = (int)g_aYyr2[local_bd4];
    if (0 < iVar8) {
      fVar9 = pfVar9[1 - iVar8];
    }
    local_bcc = iVar8;
    switch(local_bd4) {
    case 6:
      codeIf(pfVar9[-5],pfVar9[-2]);
      break;
    case 8:
      pFVar3 = g_pLuaState->pCurrState;
      uVar6 = pfVar9[-3] - pfVar9[-4];
      local_bc8 = pfVar9[-4] + 2;
      local_bc0 = uVar6;
      local_bbc = pFVar3;
      check_pc(uVar6);
      pFVar4 = local_bbc;
      pbVar11 = pFVar3->pF->pCode;
      pbVar9 = pbVar11 + pfVar9[-4];
      pbVar11 = pbVar11 + pFVar3->nPc;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar11 = *(undefined4 *)pbVar9;
        pbVar9 = pbVar9 + 4;
        pbVar11 = pbVar11 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar11 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        pbVar11 = pbVar11 + 1;
      }
      pbVar11 = local_bbc->pF->pCode;
      memcpy((undefined4 *)(pbVar11 + pfVar9[-4]),(undefined4 *)(pbVar11 + pfVar9[-3]),
             local_bbc->nPc - pfVar9[-4]);
      iVar8 = fix_jump(pfVar9[-4],'m',pFVar4->nPc - local_bc0);
      fix_upjmp('q',local_bc8 + iVar8);
      iVar8 = local_bcc;
      break;
    case 9:
      fix_upjmp('s',pfVar9[-3]);
      deltastack(-1);
      break;
    case 10:
      iVar8 = 0;
      adjust_mult_assign(pfVar9[-2],*pfVar9);
      fVar3 = pfVar9[-2];
      while (fVar3 = fVar3 + -1, -1 < fVar3) {
        iVar8 = lua_codestore(fVar3,iVar8);
      }
      adjuststack(iVar8);
      iVar8 = local_bcc;
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
      pTaggedString = luaS_new(s_self_10027ba0);
      add_localvar(pTaggedString);
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
      uVar7 = string_constant(*pfVar9,(int *)g_pLuaState->pCurrState);
      code_oparg('3',8,uVar7,iVar5);
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
      uVar7 = *pfVar9 >> 0x1f;
      fVar9 = (*pfVar9 ^ uVar7) - uVar7;
      break;
    case 0x52:
      if (0 < *pfVar9 * pfVar9[-2]) {
        luaY_error(s_invalid_constructor_syntax_10027b84);
      }
      uVar7 = *pfVar9 >> 0x1f;
      uVar6 = pfVar9[-2] >> 0x1f;
      fVar9 = ((*pfVar9 ^ uVar7) - uVar7) + ((pfVar9[-2] ^ uVar6) - uVar6);
      break;
    case 0x58:
      uVar7 = pfVar9[-1] >> 0x1f;
      flush_record(((pfVar9[-1] ^ uVar7) - uVar7 & 0x1f ^ uVar7) - uVar7);
      fVar9 = -pfVar9[-1];
      break;
    case 0x59:
      fVar4 = pfVar9[-1];
      uVar7 = fVar4 >> 0x1f;
      flush_list((int)(fVar4 + (uVar7 & 0x3f)) >> 6,((fVar4 ^ uVar7) - uVar7 & 0x3f ^ uVar7) - uVar7
                );
    case 0x21:
      fVar9 = pfVar9[-1];
      break;
    case 0x5b:
      fVar9 = pfVar9[-2] + 1;
      uVar7 = fVar9 >> 0x1f;
      if (((fVar9 ^ uVar7) - uVar7 & 0x1f ^ uVar7) == uVar7) {
        flush_record(0x20);
      }
      break;
    case 0x60:
      fVar9 = pfVar9[-2] + 1;
      uVar7 = fVar9 >> 0x1f;
      if (((fVar9 ^ uVar7) - uVar7 & 0x3f ^ uVar7) == uVar7) {
        flush_list(((int)(fVar9 + (uVar7 & 0x3f)) >> 6) - 1,0x40);
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
      store_localvar((TaggedString *)*pfVar9,0);
    case 0x46:
    case 0x5a:
    case 0x5f:
      fVar9 = 1;
      break;
    case 100:
      store_localvar((TaggedString *)*pfVar9,pfVar9[-2]);
      fVar9 = pfVar9[-2] + 1;
    }
    local_bd8 = local_bd8 + -iVar8;
    pfVar9 = pfVar9 + (1 - iVar8);
    *pfVar9 = fVar9;
    iVar8 = (int)g_wYypact[g_aYyr1[local_bd4] + 0x87] + (int)*local_bd8;
    if (((iVar8 < 0) || (0x106 < iVar8)) || (g_aYycheck[iVar8] != *local_bd8)) {
      local_bd4 = (int)g_wYydefact[g_aYyr1[local_bd4] + 0x87];
    }
    else {
      local_bd4 = (int)g_aYytable[iVar8];
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
    iVar10 = sVar2 + iVar5;
    if (((iVar10 < 0) || (0x106 < iVar10)) || (g_aYycheck[iVar10] != iVar5)) goto LAB_1000b4fe;
    local_bd4 = (int)g_aYytable[iVar10];
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
  iVar8 = local_bd4;
  if (&local_7d2 <= local_bd8) goto LAB_1000b47d;
  goto LAB_1000ac11;
}
#undef local_7d0
#undef local_7d2
#undef local_bb8
#undef local_bbc
#undef local_bc0
#undef local_bc4
#undef local_bc8
#undef local_bcc
#undef local_bd0


/* ---- 0x1000b770  fix_opcode ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named fix_opcode (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: rewrites the op at pc, moving the
   code when the argument shrinks); was lparser__b770. */

int __cdecl fix_opcode(int pc,char op,int builtin,uint arg)

{
  FuncState *pFVar1;
  byte *pbVar2;
  int iVar3;
  
  pFVar1 = g_pLuaState->pCurrState;
  if ((int)arg < builtin) {
    pbVar2 = pFVar1->pF->pCode;
    memcpy((undefined4 *)(pbVar2 + pc + 1),(undefined4 *)(pbVar2 + pc + 2),(pFVar1->nPc - pc) - 2);
    iVar3 = pFVar1->nPc + -1;
  }
  else {
    if ((int)arg < 0x100) goto LAB_1000b7e3;
    check_pc(1);
    pbVar2 = pFVar1->pF->pCode + pc;
    memcpy((undefined4 *)(pbVar2 + 1),(undefined4 *)pbVar2,pFVar1->nPc - pc);
    iVar3 = pFVar1->nPc + 1;
  }
  pFVar1->nPc = iVar3;
LAB_1000b7e3:
  iVar3 = code_oparg_at(pc,op,builtin,arg,0);
  return iVar3 + -2;
}

/* ---- 0x1000b800  code_pop ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_pop (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: code_opcode(op, -1)); was
   lparser__b800. */

void __cdecl code_pop(undefined1 op)

{
  code_opcode(op,-1);
  return;
}

/* ---- 0x1000b810  string_constant ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named string_constant (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx static string_constant: reuses
   the string's constindex when consts[i] is that string, else next_constant and stores it); was
   luaY_string_constant. */

uint __cdecl string_constant(int s,int *state)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *state;
  uVar2 = *(uint *)(s + 8);
  if (((*(uint *)(iVar1 + 0xc) <= uVar2) || (*(int *)(*(int *)(iVar1 + 8) + uVar2 * 8) != -2)) ||
     (*(int *)(*(int *)(iVar1 + 8) + uVar2 * 8 + 4) != s)) {
    uVar2 = next_constant(state);
    *(undefined4 *)(*(int *)(iVar1 + 8) + uVar2 * 8) = 0xfffffffe;
    *(int *)(*(int *)(iVar1 + 8) + 4 + uVar2 * 8) = s;
    *(uint *)(s + 8) = uVar2;
  }
  return uVar2;
}

/* ---- 0x1000b860  next_constant ---- */
/* lua.stx: constant table overflow Named next_constant (not in the remaster, gcc inlined it there):
   Lua 3.1 source name (lua.stx static next_constant: luaM_growvector of consts, error "constant
   table overflow"); was luaY_next_constant. */

int __cdecl next_constant(int *state)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *state;
  if ((uint)state[0x29] <= *(uint *)(iVar1 + 0xc)) {
    uVar3 = luaM_growaux((undefined4 *)(iVar1 + 8),state[0x29],8,
                         (byte *)s_constant_table_overflow_10027ba8,0xfffe);
    state[0x29] = uVar3;
  }
  iVar2 = *(int *)(iVar1 + 0xc);
  *(int *)(iVar1 + 0xc) = iVar2 + 1;
  return iVar2;
}

/* ---- 0x1000b8a0  code_string ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_string (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: code_constant(string_constant(s,
   fs))); was lparser__b8a0. */

void __cdecl code_string(int s)

{
  uint c;
  
  c = string_constant(s,(int *)g_pLuaState->pCurrState);
  code_constant(c);
  return;
}

/* ---- 0x1000b8c0  code_constant ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_constant (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: code_oparg(PUSHCONSTANT, 8, c,
   1)); was lparser__b8c0. */

void __cdecl code_constant(uint c)

{
  code_oparg('\b',8,c,1);
  return;
}

/* ---- 0x1000b8e0  code_number ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_number (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx static code_number: PUSHNUMBER for
   an integer in 0..65534 (code_oparg), else code_constant(real_constant(f))); was luaY_code_number.
    */

void __cdecl code_number(float f)

{
  uint c;
  longlong lVar1;
  
  if ((0.0f <= f) && (f <= 65534.0f)) {
    lVar1 = FTOL((float10)f);
    if ((float)(int)(uint)lVar1 == f) {
      code_oparg('\x03',3,(uint)lVar1,1);
      return;
    }
  }
  c = real_constant(f);
  code_constant(c);
  return;
}

/* ---- 0x1000b950  real_constant ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named real_constant (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx static real_constant: searches
   the last 20 constants for the number (LOOKBACKNUMS), else next_constant); was luaY_real_constant.
    */

int __cdecl real_constant(float r)

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
      if ((pTVar3->nTtype == -1) && (PUN(float,pTVar3->dwValue) == r)) {
        return iVar2;
      }
      iVar2 = iVar2 + -1;
      pTVar3 = pTVar3 + -1;
    } while (iVar4 <= iVar2);
  }
  iVar2 = next_constant((int *)g_pLuaState->pCurrState);
  pTVar3 = g_pLuaState->pCurrState->pF->pConsts;
  pTVar3[iVar2].nTtype = -1;
  pTVar3[iVar2].dwValue = PUN(uint,(float)(r));
  return iVar2;
}

/* ---- 0x1000b9c0  flush_record ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named flush_record (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: SETMAP n-1 with delta -2n); was
   lparser__b9c0. */

void __cdecl flush_record(int n)

{
  if (0 < n) {
    code_oparg('Y',1,n - 1,n * -2);
  }
  return;
}

/* ---- 0x1000b9e0  flush_list ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named flush_list (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: SETLIST m with delta -n, then the
   count byte); was lparser__b9e0. */

void __cdecl flush_list(uint m,int n)

{
  if (n != 0) {
    code_oparg('V',1,m,-n);
    code_byte((byte)n);
  }
  return;
}

/* ---- 0x1000ba10  luaI_unregisterlocalvar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named luaI_unregisterlocalvar
   (not in the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx:
   luaI_registerlocalvar(NULL, line)); was lparser__ba10. */

void __cdecl luaI_unregisterlocalvar(int line)

{
  luaI_registerlocalvar((TaggedString *)0x0,line);
  return;
}

/* ---- 0x1000ba20  store_localvar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named store_localvar (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: 'too many local variables',
   localvar[nlocalvar+n] = name, luaI_registerlocalvar); was lparser__ba20. */

void __cdecl store_localvar(TaggedString *name,int n)

{
  int iVar1;
  
  iVar1 = g_pLuaState->pCurrState->nLocalVar + n;
  if (iVar1 < 0x20) {
    g_pLuaState->pCurrState->aLocalVar[iVar1] = name;
  }
  else {
    luaY_error(s_too_many_local_variables__limit__10027bc0);
  }
  luaI_registerlocalvar(name,*(int *)((int)g_pLuaState->pLexState + 8));
  return;
}

/* ---- 0x1000ba70  add_localvar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named add_localvar (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: store_localvar(name, 0),
   nlocalvar++); was lparser__ba70. */

void __cdecl add_localvar(TaggedString *pTaggedString)

{
  int *piVar1;
  
  store_localvar(pTaggedString,0);
  piVar1 = &g_pLuaState->pCurrState->nLocalVar;
  *piVar1 = *piVar1 + 1;
  return;
}

/* ---- 0x1000ba90  add_varbuffer ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Original name add_varbuffer
   (the remaster's libLua.so: static add_varbuffer: string 'variable buffer overflow (limit=32)');
   was lparser__ba90. */

void __cdecl add_varbuffer(int var,int n)

{
  int iVar1;
  
  if (0x1f < n) {
    luaY_error(s_variable_buffer_overflow__limit__10027be4);
  }
  iVar1 = var2store(var);
  g_pLuaState->pCurrState->aUpvalues[n + -0x20] = iVar1;
  return;
}

/* ---- 0x1000bad0  var2store ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named var2store (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: a dotted variable codes its
   constant and becomes 0, used by add_varbuffer); was lparser__bad0. */

int __cdecl var2store(int var)

{
  if (var < 0) {
    code_constant(-var - 1);
    var = 0;
  }
  return var;
}

/* ---- 0x1000baf0  singlevar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named singlevar (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: local, global or 'cannot access a
   variable in outer scope'); was lparser__baf0. */

int __cdecl singlevar(int n,int *st)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = aux_localname(n,(int)st);
  if (iVar2 != -1) {
    return iVar2 + 1;
  }
  iVar2 = 1;
  piVar1 = st;
  if (0 < ((int)st - (int)g_pLuaState->pMainState) / 0x168) {
    do {
      iVar3 = aux_localname(n,(int)(piVar1 + -0x5a));
      if (-1 < iVar3) {
        luaY_syntaxerror(s_cannot_access_a_variable_in_oute_10027c08,(char *)(n + 0x18));
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + -0x5a;
    } while (iVar2 <= ((int)st - (int)g_pLuaState->pMainState) / 0x168);
  }
  iVar2 = string_constant(n,st);
  return iVar2 + 0x21;
}

/* ---- 0x1000bba0  aux_localname ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named aux_localname (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: the index of a local name in a
   FuncState or -1); was lparser__bba0. */

int __cdecl aux_localname(int n,int st)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *(int *)(st + 0x90) + -1;
  if (-1 < iVar1) {
    piVar2 = (int *)(st + 8 + iVar1 * 4);
    do {
      if (n == *piVar2) {
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

void __cdecl pushupvalue(int n)

{
  int iVar1;
  uint arg;
  
  if (g_pLuaState->pCurrState == g_pLuaState->pMainState) {
    luaY_error(s_cannot_access_upvalue_in_main_10027c5c);
  }
  iVar1 = aux_localname(n,(int)g_pLuaState->pCurrState);
  if (-1 < iVar1) {
    luaY_syntaxerror(s_cannot_access_an_upvalue_in_curr_10027c30,(char *)(n + 0x18));
  }
  arg = indexupvalue(n);
  code_oparg('\x12',2,arg,1);
  return;
}

/* ---- 0x1000bc40  indexupvalue ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named indexupvalue (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: index of an upvalue, added if
   new); was lparser__bc40. */

int __cdecl indexupvalue(int n)

{
  FuncState *pFVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar3 = singlevar(n,(int *)(g_pLuaState->pCurrState + -1));
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

void __cdecl adjuststack(int n)

{
  if (0 < n) {
    code_oparg('~',2,n - 1,-n);
    return;
  }
  if (n < 0) {
    code_oparg('\x01',1,-n - 1,-n);
  }
  return;
}

/* ---- 0x1000bd00  adjust_functioncall ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named adjust_functioncall (not
   in the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: fixes the result count of a
   call); was lparser__bd00. */

int __cdecl adjust_functioncall(int exp,uint nresults)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  
  if (exp < 1) {
    return -exp;
  }
  pbVar3 = g_pLuaState->pCurrState->pF->pCode + exp;
  bVar1 = *pbVar3;
  bVar2 = pbVar3[-1];
  iVar4 = fix_opcode(exp + -2,'x',2,nresults);
  g_pLuaState->pCurrState->pF->pCode[exp + iVar4] = bVar2;
  if (nresults != 0xff) {
    deltastack(nresults);
  }
  deltastack(-1 - (uint)bVar2);
  return bVar1 + nresults;
}

/* ---- 0x1000bd80  adjust_mult_assign ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named adjust_mult_assign (not
   in the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: adjust_functioncall /
   adjuststack for vars = exps); was lparser__bd80. */

void __cdecl adjust_mult_assign(int vars,int exps)

{
  int n;
  
  if (exps < 1) {
    adjuststack(-(exps + vars));
    return;
  }
  n = (uint)g_pLuaState->pCurrState->pF->pCode[exps] - vars;
  if (n < 0) {
    adjust_functioncall(exps,-n);
    return;
  }
  adjust_functioncall(exps,0);
  adjuststack(n);
  return;
}

/* ---- 0x1000bde0  code_args ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_args (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: nlocalvar += nparams, VARARGS when
   dots); was lparser__bde0. */

void __cdecl code_args(int nparams,int dots)

{
  FuncState *pFVar1;
  int delta;
  TaggedString *pTaggedString;
  
  g_pLuaState->pCurrState->nLocalVar = g_pLuaState->pCurrState->nLocalVar + nparams;
  pFVar1 = g_pLuaState->pCurrState;
  delta = pFVar1->nLocalVar;
  if (dots == 0) {
    pFVar1->pF->pCode[1] = (byte)delta;
    deltastack(delta);
    return;
  }
  pFVar1->pF->pCode[1] = (byte)delta + 0x40;
  deltastack(delta + 1);
  pTaggedString = luaS_new(s_arg_10027cb0);
  add_localvar(pTaggedString);
  return;
}

/* ---- 0x1000be60  lua_pushvar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named lua_pushvar (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: PUSHLOCAL / GETGLOBAL / GETTABLE /
   GETDOTTED by vardesc); was lparser__be60. */

void __cdecl lua_pushvar(int number)

{
  if (0x20 < number) {
    code_oparg('\x1e',8,number - 0x21,1);
    return;
  }
  if ((0 < number) && (number < 0x21)) {
    code_oparg('\x15',8,number - 1,1);
    return;
  }
  if (-1 < number) {
    code_pop(0x28);
    return;
  }
  ((code *)code_oparg)(')',8,-number - 1,0);
  return;
}

/* ---- 0x1000bec0  storevar ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named storevar (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: SETLOCAL / SETGLOBAL / SETTABLE0
   by vardesc); was lparser__bec0. */

void __cdecl storevar(int number)

{
  if (number == 0) {
    code_opcode(0x54,-3);
    return;
  }
  if (0x20 < number) {
    code_oparg('J',8,number - 0x21,-1);
    return;
  }
  code_oparg('A',8,number - 1,-1);
  return;
}

/* ---- 0x1000bf00  lua_codestore ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named lua_codestore (not in
   the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: the store of assignment i,
   SETTABLE when left items are on the stack); was lparser__bf00. */

int __cdecl lua_codestore(int i,int left)

{
  int number;
  
  number = g_pLuaState->pCurrState->aUpvalues[i + -0x20];
  if ((number == 0) && (i + left != 0)) {
    code_oparg('U',0,i + left,-1);
    return left + 2;
  }
  storevar(number);
  return left;
}

/* ---- 0x1000bf50  fix_jump ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named fix_jump (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: fix_opcode(pc, op, 0, n - pc -
   2)); was lparser__bf50. */

int __cdecl fix_jump(int pc,char op,int n)

{
  int iVar1;
  
  iVar1 = fix_opcode(pc,op,0,(n - pc) - 2);
  return iVar1;
}

/* ---- 0x1000bf70  fix_upjmp ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named fix_upjmp (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: a backward jump to pos); was
   lparser__bf70. */

void __cdecl fix_upjmp(char op,int pos)

{
  int iVar1;
  uint arg;
  
  iVar1 = g_pLuaState->pCurrState->nPc - pos;
  arg = iVar1 + 2;
  if (0xff < (int)arg) {
    arg = iVar1 + 3;
  }
  code_oparg(op,0,arg,0);
  return;
}

/* ---- 0x1000bfa0  codeIf ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named codeIf (not in the
   remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: fix_jump of the then part and of
   the jump over the else part); was lparser__bfa0. */

void __cdecl codeIf(int thenAdd,int elseAdd)

{
  int iVar1;
  
  iVar1 = g_pLuaState->pCurrState->nPc;
  if (iVar1 == elseAdd + 2) {
    g_pLuaState->pCurrState->nPc = iVar1 + -2;
    fix_jump(thenAdd,'o',g_pLuaState->pCurrState->nPc);
    return;
  }
  iVar1 = fix_jump(elseAdd,'m',iVar1);
  fix_jump(thenAdd,'o',elseAdd + 2 + iVar1);
  return;
}

/* ---- 0x1000c000  code_shortcircuit ---- */
/* Unidentified function of lua.stx (yacc parser) and code generation Named code_shortcircuit (not
   in the remaster, gcc inlined it there): Lua 3.1 source name (lua.stx: fix_jump(pc, jmp, pc of the
   end)); was lparser__c000. */

void __cdecl code_shortcircuit(int pc,char jmp)

{
  fix_jump(pc,jmp,g_pLuaState->pCurrState->nPc);
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
  uint arg;
  uint c;
  int iVar1;
  uint uVar2;
  
  arg = g_pLuaState->pCurrState[1].nUpvalues;
  c = next_constant((int *)g_pLuaState->pCurrState);
  g_pLuaState->pCurrState->pF->pConsts[c].nTtype = -4;
  g_pLuaState->pCurrState->pF->pConsts[c].dwValue = (uint)g_pLuaState->pCurrState[1].pF;
  if (arg != 0) {
    if (0 < (int)arg) {
      iVar1 = 0x290;
      uVar2 = arg;
      do {
        lua_pushvar(*(int *)((int)g_pLuaState->pCurrState->aLocalVar + iVar1 + -8));
        iVar1 = iVar1 + 4;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    code_constant(c);
    code_oparg('u',2,arg,-arg);
    return;
  }
  code_constant(c);
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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern short grim_def_g_aYycheck[263] __asm__("_g_aYycheck");
extern short grim_def_g_aYyr1[103] __asm__("_g_aYyr1");
extern short grim_def_g_aYyr2[103] __asm__("_g_aYyr2");
extern short grim_def_g_aYytable[263] __asm__("_g_aYytable");
extern signed char grim_def_g_aYytranslate[285] __asm__("_g_aYytranslate");
extern short grim_def_g_wYydefact[184] __asm__("_g_wYydefact");
extern short grim_def_g_wYypact[184] __asm__("_g_wYypact");
extern char grim_def_s___100s__last_token_read_____50s__10027ac4[60] __asm__("_s___100s__last_token_read_____50s__10027ac4");
extern char grim_def_s__eof__10027b00[8] __asm__("_s__eof__10027b00");
extern char grim_def_s_arg_10027cb0[4] __asm__("_s_arg_10027cb0");
extern char grim_def_s_cannot_access_a_variable_in_oute_10027c08[40] __asm__("_s_cannot_access_a_variable_in_oute_10027c08");
extern char grim_def_s_cannot_access_an_upvalue_in_curr_10027c30[44] __asm__("_s_cannot_access_an_upvalue_in_curr_10027c30");
extern char grim_def_s_cannot_access_upvalue_in_main_10027c5c[32] __asm__("_s_cannot_access_upvalue_in_main_10027c5c");
extern char grim_def_s_code_size_overflow_10027b08[20] __asm__("_s_code_size_overflow_10027b08");
extern char grim_def_s_code_too_long__limit_64K__10027b1c[28] __asm__("_s_code_too_long__limit_64K__10027b1c");
extern char grim_def_s_constant_table_overflow_10027ba8[24] __asm__("_s_constant_table_overflow_10027ba8");
extern char grim_def_s_function_expression_too_complex_10027b38[32] __asm__("_s_function_expression_too_complex_10027b38");
extern char grim_def_s_invalid_constructor_syntax_10027b84[28] __asm__("_s_invalid_constructor_syntax_10027b84");
extern char grim_def_s_lua_stx_10027b64[8] __asm__("_s_lua_stx_10027b64");
extern char grim_def_s_parse_error_10027b58[12] __asm__("_s_parse_error_10027b58");
extern char grim_def_s_parser_stack_overflow_10027b6c[24] __asm__("_s_parser_stack_overflow_10027b6c");
extern char grim_def_s_self_10027ba0[8] __asm__("_s_self_10027ba0");
extern char grim_def_s_too_many_local_variables__limit__10027bc0[36] __asm__("_s_too_many_local_variables__limit__10027bc0");
extern char grim_def_s_too_many_nested_functions__limit_10027cb4[36] __asm__("_s_too_many_nested_functions__limit_10027cb4");
extern char grim_def_s_too_many_upvalues_in_a_single_fu_10027c7c[52] __asm__("_s_too_many_upvalues_in_a_single_fu_10027c7c");
extern char grim_def_s_variable_buffer_overflow__limit__10027be4[36] __asm__("_s_variable_buffer_overflow__limit__10027be4");
/* 0x10023188, 288 bytes */ GRIM_DATA("10023188") signed char grim_def_g_aYytranslate[285] __asm__("_g_aYytranslate") = {
    0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 43, 2, 2, 41, 42, 32, 30, 48, 31, 39, 33,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 40, 37, 26, 38, 25, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 44, 2, 45, 36, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 46, 2, 47, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 27, 28, 29, 34, 35
};
/* 0x100232a5, 3 bytes: the rest of grim_def_g_aYytranslate's span */ GRIM_DATA("10023188") static unsigned char g_aYytranslate__tail[3] __attribute__((used)) = {0};
/* 0x100232a8, 208 bytes */ GRIM_DATA("100232a8") short grim_def_g_aYyr1[103] __asm__("_g_aYyr1") = {
    0, 49, 50, 50, 51, 51, 52, 52, 52, 52, 52, 52, 52, 52, 54, 53,
    55, 55, 55, 56, 57, 58, 59, 59, 59, 60, 60, 61, 62, 63, 64, 65,
    66, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67,
    67, 67, 67, 67, 67, 68, 67, 67, 67, 69, 70, 70, 70, 71, 71, 71,
    72, 73, 74, 75, 75, 76, 76, 76, 77, 77, 78, 79, 78, 80, 80, 80,
    80, 81, 81, 82, 82, 82, 83, 83, 84, 85, 86, 86, 87, 88, 88, 89,
    89, 90, 90, 91, 91, 92, 92
};
/* 0x10023376, 2 bytes: the rest of grim_def_g_aYyr1's span */ GRIM_DATA("100232a8") static unsigned char g_aYyr1__tail[2] __attribute__((used)) = {0};
/* 0x10023378, 208 bytes */ GRIM_DATA("10023378") short grim_def_g_aYyr2[103] __asm__("_g_aYyr2") = {
    0, 2, 0, 3, 0, 1, 7, 3, 6, 5, 3, 1, 3, 3, 0, 2,
    1, 3, 3, 1, 1, 5, 0, 2, 6, 0, 3, 0, 0, 1, 1, 2,
    1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2,
    1, 1, 1, 1, 1, 0, 3, 4, 4, 1, 1, 2, 1, 1, 4, 3,
    1, 4, 2, 1, 3, 3, 1, 1, 0, 1, 1, 0, 4, 0, 1, 1,
    3, 1, 3, 0, 1, 1, 0, 1, 2, 2, 1, 3, 3, 3, 1, 1,
    3, 1, 3, 1, 3, 0, 2
};
/* 0x10023446, 2 bytes: the rest of grim_def_g_aYyr2's span */ GRIM_DATA("10023378") static unsigned char g_aYyr2__tail[2] __attribute__((used)) = {0};
/* 0x10023448, 368 bytes */ GRIM_DATA("10023448") short grim_def_g_wYydefact[184] __asm__("_g_wYydefact") = {
    2, 25, 0, 27, 14, 27, 72, 0, 0, 64, 0, 4, 1, 67, 57, 58,
    61, 11, 0, 0, 52, 53, 50, 51, 0, 0, 0, 28, 0, 28, 32, 48,
    58, 49, 60, 0, 0, 2, 14, 0, 74, 4, 73, 99, 101, 0, 0, 19,
    59, 5, 3, 0, 0, 0, 71, 72, 70, 66, 0, 0, 0, 46, 47, 32,
    30, 83, 14, 28, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 29, 31, 0, 7, 15, 0, 26, 75, 0, 0, 12, 77, 13, 0, 0,
    63, 68, 0, 0, 10, 58, 54, 33, 64, 0, 94, 95, 0, 81, 84, 85,
    86, 90, 0, 86, 28, 0, 0, 34, 37, 36, 35, 38, 39, 45, 40, 41,
    42, 43, 44, 14, 0, 0, 102, 100, 78, 0, 79, 20, 17, 18, 62, 69,
    0, 65, 83, 87, 88, 0, 87, 89, 22, 55, 56, 0, 9, 76, 2, 0,
    93, 82, 91, 92, 96, 14, 0, 0, 8, 0, 80, 23, 0, 6, 21, 14,
    28, 22, 24
};
/* 0x10023610, 368 bytes */ GRIM_DATA("10023610") short grim_def_g_wYypact[184] __asm__("_g_wYypact") = {
    (short)0x8000, 147, 94, (short)0x8000, (short)0x8000, (short)0x8000, 94, 19, 34, (short)0x8000, 39, -19, (short)0x8000, 2, (short)0x8000, -29,
    (short)0x8000, -10, -6, -27, (short)0x8000, (short)0x8000, (short)0x8000, (short)0x8000, 94, 94, 94, (short)0x8000, 14, 196, (short)0x8000, 4,
    (short)0x8000, (short)0x8000, (short)0x8000, 94, 49, (short)0x8000, (short)0x8000, 196, 212, -19, 18, (short)0x8000, -22, 38, 21, 40,
    (short)0x8000, (short)0x8000, (short)0x8000, 68, 71, 94, (short)0x8000, 94, (short)0x8000, (short)0x8000, 94, 9, 38, 57, 57, 62,
    (short)0x8000, 76, (short)0x8000, (short)0x8000, (short)0x8000, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94,
    94, (short)0x8000, (short)0x8000, 96, (short)0x8000, (short)0x8000, 106, (short)0x8000, (short)0x8000, 94, 102, (short)0x8000, -4, (short)0x8000, 109, 109,
    (short)0x8000, (short)0x8000, 146, 91, 18, -21, (short)0x8000, (short)0x8000, 98, 94, (short)0x8000, 196, 92, 105, (short)0x8000, (short)0x8000,
    90, (short)0x8000, 107, 95, (short)0x8000, 94, 94, 53, 53, 53, 53, 53, 53, 69, 23, 23,
    57, 57, 57, (short)0x8000, 94, 94, 18, (short)0x8000, (short)0x8000, 104, 112, (short)0x8000, (short)0x8000, (short)0x8000, (short)0x8000, (short)0x8000,
    171, (short)0x8000, 76, -7, (short)0x8000, 94, 94, (short)0x8000, 101, 226, 226, 136, 196, 212, (short)0x8000, 30,
    (short)0x8000, (short)0x8000, (short)0x8000, 196, 196, (short)0x8000, 94, 137, (short)0x8000, 140, (short)0x8000, (short)0x8000, 148, (short)0x8000, (short)0x8000, (short)0x8000,
    (short)0x8000, 101, (short)0x8000, 155, 165, (short)0x8000
};
/* 0x100237d8, 528 bytes */ GRIM_DATA("100237d8") short grim_def_g_aYytable[263] __asm__("_g_aYytable") = {
    29, 179, 64, 83, 86, 40, 14, 15, 100, -97, -60, 58, 139, 136, 54, 43,
    89, -98, 49, -97, 66, 59, 61, 62, -57, 63, 90, -98, 9, -60, -60, -60,
    116, 29, -60, 55, -60, 105, 43, 134, 27, 51, 52, -57, -57, -57, 53, 170,
    -57, 135, -57, 98, 10, 9, 40, 78, 79, 40, 48, 80, 94, 95, 84, 107,
    14, 101, 88, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 92,
    20, -16, 75, 76, 77, 78, 79, 96, 40, 80, 97, 152, 21, 80, 22, 104,
    23, 155, 20, 76, 77, 78, 79, 144, 103, 80, 131, 24, 165, 166, 21, 25,
    22, 9, 23, 153, 154, 26, 132, 10, 105, 135, 27, 140, 141, 24, 117, 118,
    139, 25, 156, 171, 157, 143, 172, 26, -20, 10, 147, 145, 27, 176, 146, 150,
    107, 149, 158, 163, 164, 168, 173, 177, 2, 174, 175, 180, 3, 4, 5, 169,
    159, 6, 7, 8, 29, 181, 9, 67, 68, 69, 70, 71, 72, 73, 74, 75,
    76, 77, 78, 79, 87, 102, 80, 38, 178, 47, 56, 17, 99, 161, 10, 142,
    67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 162, 138, 80,
    151, 0, 0, 0, 0, 0, 0, 0, 160, 67, 68, 69, 70, 71, 72, 73,
    74, 75, 76, 77, 78, 79, 0, 0, 80, -32, -32, -32, -32, -32, -32, -32,
    -32, -32, -32, -32, -32, -32, 0, 0, -32, 69, 70, 71, 72, 73, 74, 75,
    76, 77, 78, 79, 0, 0, 80
};
/* 0x100239e6, 2 bytes: the rest of grim_def_g_aYytable's span */ GRIM_DATA("100237d8") static unsigned char g_aYytable__tail[2] __attribute__((used)) = {0};
/* 0x100239e8, 580 bytes */ GRIM_DATA("100239e8") short grim_def_g_aYycheck[263] __asm__("_g_aYycheck") = {
    2, 0, 27, 35, 38, 6, 1, 1, 58, 38, 20, 38, 19, 17, 20, 19,
    38, 38, 37, 48, 6, 48, 24, 25, 20, 26, 48, 48, 19, 39, 40, 41,
    66, 35, 44, 41, 46, 44, 19, 89, 46, 39, 40, 39, 40, 41, 44, 17,
    44, 19, 46, 53, 43, 19, 55, 32, 33, 58, 19, 36, 39, 40, 13, 65,
    59, 59, 48, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 41,
    4, 41, 29, 30, 31, 32, 33, 19, 89, 36, 19, 116, 16, 36, 18, 19,
    20, 131, 4, 30, 31, 32, 33, 105, 42, 36, 10, 31, 7, 8, 16, 35,
    18, 19, 20, 117, 118, 41, 12, 43, 44, 19, 46, 94, 95, 31, 67, 68,
    19, 35, 132, 165, 133, 42, 166, 41, 38, 43, 48, 47, 46, 175, 37, 48,
    146, 38, 42, 149, 150, 13, 13, 176, 5, 13, 6, 0, 9, 10, 11, 158,
    48, 14, 15, 16, 166, 0, 19, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 41, 60, 36, 5, 177, 8, 18, 1, 55, 146, 43, 45,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 147, 92, 36,
    115, -1, -1, -1, -1, -1, -1, -1, 45, 21, 22, 23, 24, 25, 26, 27,
    28, 29, 30, 31, 32, 33, -1, -1, 36, 21, 22, 23, 24, 25, 26, 27,
    28, 29, 30, 31, 32, 33, -1, -1, 36, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, -1, -1, 36
};
/* 0x10023bf6, 54 bytes: the rest of grim_def_g_aYycheck's span */ GRIM_DATA("100239e8") static unsigned char g_aYycheck__tail[54] __attribute__((used)) = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7f, 0x47, 0xb7, 0x6d, 0xdb, 0xb6, 0x6d, 0xdb,
    0xf6, 0x3f, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0xe6, 0x3f, 0x46, 0x0a, 0xbf, 0x17, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x48, 0xe1, 0xf7, 0x3a, 0x00, 0x00, 0x00, 0xcf, 0x00, 0x00,
    0x00, 0x4f, 0x00, 0x00, 0x80, 0xbf
};
/* 0x10027ac4, 60 bytes */ /* loose */ char grim_def_s___100s__last_token_read_____50s__10027ac4[60] __asm__("_s___100s__last_token_read_____50s__10027ac4") = "%.100s;\n  last token read: \"%.50s\" at line %d in file %.50s";
/* 0x10027b00, 8 bytes */ /* loose */ char grim_def_s__eof__10027b00[8] __asm__("_s__eof__10027b00") = "<eof>";
/* 0x10027b08, 20 bytes */ /* loose */ char grim_def_s_code_size_overflow_10027b08[20] __asm__("_s_code_size_overflow_10027b08") = "code size overflow";
/* 0x10027b1c, 28 bytes */ /* loose */ char grim_def_s_code_too_long__limit_64K__10027b1c[28] __asm__("_s_code_too_long__limit_64K__10027b1c") = "code too long (limit=64K)";
/* 0x10027b38, 32 bytes */ /* loose */ char grim_def_s_function_expression_too_complex_10027b38[32] __asm__("_s_function_expression_too_complex_10027b38") = "function/expression too complex";
/* 0x10027b58, 12 bytes */ /* loose */ char grim_def_s_parse_error_10027b58[12] __asm__("_s_parse_error_10027b58") = "parse error";
/* 0x10027b64, 8 bytes */ /* loose */ char grim_def_s_lua_stx_10027b64[8] __asm__("_s_lua_stx_10027b64") = "lua.stx";
/* 0x10027b6c, 24 bytes */ /* loose */ char grim_def_s_parser_stack_overflow_10027b6c[24] __asm__("_s_parser_stack_overflow_10027b6c") = "parser stack overflow";
/* 0x10027b84, 28 bytes */ /* loose */ char grim_def_s_invalid_constructor_syntax_10027b84[28] __asm__("_s_invalid_constructor_syntax_10027b84") = "invalid constructor syntax";
/* 0x10027ba0, 8 bytes */ /* loose */ char grim_def_s_self_10027ba0[8] __asm__("_s_self_10027ba0") = "self";
/* 0x10027ba8, 24 bytes */ /* loose */ char grim_def_s_constant_table_overflow_10027ba8[24] __asm__("_s_constant_table_overflow_10027ba8") = "constant table overflow";
/* 0x10027bc0, 36 bytes */ /* loose */ char grim_def_s_too_many_local_variables__limit__10027bc0[36] __asm__("_s_too_many_local_variables__limit__10027bc0") = "too many local variables (limit=32)";
/* 0x10027be4, 36 bytes */ /* loose */ char grim_def_s_variable_buffer_overflow__limit__10027be4[36] __asm__("_s_variable_buffer_overflow__limit__10027be4") = "variable buffer overflow (limit=32)";
/* 0x10027c08, 40 bytes */ /* loose */ char grim_def_s_cannot_access_a_variable_in_oute_10027c08[40] __asm__("_s_cannot_access_a_variable_in_oute_10027c08") = "cannot access a variable in outer scope";
/* 0x10027c30, 44 bytes */ /* loose */ char grim_def_s_cannot_access_an_upvalue_in_curr_10027c30[44] __asm__("_s_cannot_access_an_upvalue_in_curr_10027c30") = "cannot access an upvalue in current scope";
/* 0x10027c5c, 32 bytes */ /* loose */ char grim_def_s_cannot_access_upvalue_in_main_10027c5c[32] __asm__("_s_cannot_access_upvalue_in_main_10027c5c") = "cannot access upvalue in main";
/* 0x10027c7c, 52 bytes */ /* loose */ char grim_def_s_too_many_upvalues_in_a_single_fu_10027c7c[52] __asm__("_s_too_many_upvalues_in_a_single_fu_10027c7c") = "too many upvalues in a single function (limit=16)";
/* 0x10027cb0, 4 bytes */ /* loose */ char grim_def_s_arg_10027cb0[4] __asm__("_s_arg_10027cb0") = "arg";
/* 0x10027cb4, 36 bytes */ /* loose */ char grim_def_s_too_many_nested_functions__limit_10027cb4[36] __asm__("_s_too_many_nested_functions__limit_10027cb4") = "too many nested functions (limit=6)";
