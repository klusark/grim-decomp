/* GRIMFANDANGO.EXE :: text.c
 * functions 0x0048c050 .. 0x004ab710 (20 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048c050  Text_ParseLuaTable ---- */
/* Reads x, y, font, width, height, fgcolor, bgcolor, ... keys from a Lua table into a text context
    */

int __cdecl Text_ParseLuaTable(void *ctx,void *table,void *textObj)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  iVar3 = *(int *)((int)ctx + 4);
  lua_pushobject((int)table);
  iVar1 = lua_getref(UINT_008ca0dc);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  if (iVar1 != 0) {
    iVar2 = lua_isnumber(iVar1);
    if (iVar2 != 0) {
      lVar4 = FTOL(lua_getnumber(iVar1));
      *(int *)((int)ctx + 0xc) = (int)lVar4;
      if (textObj != (void *)0x0) {
        lVar4 = FTOL(lua_getnumber(iVar1));
        *(int *)((int)textObj + 0x238) = (int)lVar4;
      }
    }
  }
  lua_pushobject((int)table);
  iVar1 = lua_getref(UINT_008ca0e0);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  if (iVar1 != 0) {
    iVar2 = lua_isnumber(iVar1);
    if (iVar2 != 0) {
      lVar4 = FTOL(lua_getnumber(iVar1));
      *(int *)((int)ctx + 0x10) = (int)lVar4 + *(int *)(**(int **)((int)ctx + 8) + 8);
      if (textObj != (void *)0x0) {
        lVar4 = FTOL(lua_getnumber(iVar1));
        *(int *)((int)textObj + 0x23c) = (int)lVar4;
      }
    }
  }
  lua_pushobject((int)table);
  iVar1 = lua_getref(UINT_008ca104);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  if (iVar1 != 0) {
    iVar2 = lua_isuserdata(iVar1);
    if (iVar2 != 0) {
      iVar2 = lua_tag(iVar1);
      if ((iVar2 == 0x544e4f46) && (g_pOverrideFont == (void *)0x0)) {
        iVar1 = lua_getuserdata(iVar1);
        *(int *)((int)ctx + 8) = iVar1;
      }
    }
  }
  lua_pushobject((int)table);
  iVar1 = lua_getref(UINT_008ca0f8);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  if (iVar1 != 0) {
    iVar2 = lua_isnumber(iVar1);
    if ((iVar2 != 0) && (iVar3 != 0)) {
      lVar4 = FTOL(lua_getnumber(iVar1));
      *(int *)(iVar3 + 8) = (int)lVar4;
    }
  }
  lua_pushobject((int)table);
  iVar1 = lua_getref(UINT_008ca0d8);
  lua_pushobject(iVar1);
  iVar1 = lua_gettable();
  if (iVar1 != 0) {
    iVar2 = lua_isnumber(iVar1);
    if ((iVar2 != 0) && (iVar3 != 0)) {
      lVar4 = FTOL(lua_getnumber(iVar1));
      *(int *)(iVar3 + 0xc) = (int)lVar4;
    }
  }
  lua_pushobject((int)table);
  iVar3 = lua_getref(UINT_008ca110);
  lua_pushobject(iVar3);
  iVar3 = lua_gettable();
  if (iVar3 != 0) {
    iVar1 = lua_isuserdata(iVar3);
    if (iVar1 != 0) {
      iVar1 = lua_tag(iVar3);
      if (iVar1 == 0x524c4f43) {
        iVar3 = lua_getuserdata(iVar3);
        *(int *)((int)ctx + 0x14) = iVar3;
      }
    }
  }
  lua_pushobject((int)table);
  iVar3 = lua_getref(UINT_008ca0fc);
  lua_pushobject(iVar3);
  iVar3 = lua_gettable();
  if (iVar3 != 0) {
    iVar1 = lua_isuserdata(iVar3);
    if (iVar1 != 0) {
      iVar1 = lua_tag(iVar3);
      if (iVar1 == 0x524c4f43) {
        iVar3 = lua_getuserdata(iVar3);
        *(int *)((int)ctx + 0x18) = iVar3;
      }
    }
  }
  lua_pushobject((int)table);
  iVar3 = lua_getref(UINT_008ca0f0);
  lua_pushobject(iVar3);
  iVar3 = lua_gettable();
  if (iVar3 != 0) {
    iVar1 = lua_isuserdata(iVar3);
    if (iVar1 != 0) {
      iVar1 = lua_tag(iVar3);
      if (iVar1 == 0x524c4f43) {
        iVar3 = lua_getuserdata(iVar3);
        *(int *)((int)ctx + 0x1c) = iVar3;
      }
    }
  }
  lua_pushobject((int)table);
  iVar3 = lua_getref(UINT_008ca0f4);
  lua_pushobject(iVar3);
  iVar3 = lua_gettable();
  if (iVar3 != 0) {
    iVar3 = lua_isnil(iVar3);
    if (iVar3 == 0) {
      *(undefined4 *)((int)ctx + 0x28) = 5;
    }
  }
  lua_pushobject((int)table);
  iVar3 = lua_getref(UINT_008ca108);
  lua_pushobject(iVar3);
  iVar3 = lua_gettable();
  if (iVar3 != 0) {
    iVar3 = lua_isnil(iVar3);
    if (iVar3 == 0) {
      *(undefined4 *)((int)ctx + 0x28) = 4;
    }
  }
  lua_pushobject((int)table);
  iVar3 = lua_getref(UINT_008ca10c);
  lua_pushobject(iVar3);
  iVar3 = lua_gettable();
  if (iVar3 != 0) {
    iVar3 = lua_isnil(iVar3);
    if (iVar3 == 0) {
      *(undefined4 *)((int)ctx + 0x28) = 6;
    }
  }
  lua_pushobject((int)table);
  iVar3 = lua_getref(UINT_008ca0ec);
  lua_pushobject(iVar3);
  iVar3 = lua_gettable();
  if (iVar3 != 0) {
    iVar1 = lua_isnumber(iVar3);
    if (iVar1 != 0) {
      lVar4 = FTOL(lua_getnumber(iVar3));
      return (int)lVar4;
    }
  }
  return -1;
}
#undef local_4
#undef local_8


/* ---- 0x0048c8d0  Text_ParseLineId ---- */
/* Splits a '/id/text' dialogue line: copies the id into outId and returns the text according to
   g_nTranslationMode (translated, id only, or raw) */

char * __cdecl Text_ParseLineId(char *line,char *outId)

{
  char *pcVar1;
  char *pcVar2;
  
  if (outId != (char *)0x0) {
    *outId = '\0';
  }
  pcVar1 = Polyglot_Lookup(line);
  pcVar2 = pcVar1;
  if (((outId != (char *)0x0) && (line != (char *)0x0)) && (*line == '/')) {
    pcVar2 = (char *)strchr(line + 1,0x2f);
    if (pcVar2 != (char *)0x0) {
      strncpy(outId,line + 1,pcVar2 + (-1 - (int)line));
      (pcVar2 + (int)outId)[-1 - (int)line] = '\0';
    }
  }
  if (g_nTranslationMode != 1) {
    outId = pcVar1;
    if (g_nTranslationMode == 2) {
      outId = line;
    }
    return outId;
  }
  return pcVar2 + 1;
}

/* ---- 0x00494740  Text_GetSpeed ---- */
int Text_GetSpeed(void)

{
  return g_nTextSpeed;
}

/* ---- 0x00494750  Text_SetSpeed ---- */
void __cdecl Text_SetSpeed(int speed)

{
  if (speed < 1) {
    g_nTextSpeed = 1;
    return;
  }
  if (10 < speed) {
    speed = 10;
  }
  g_nTextSpeed = speed;
  return;
}

/* ---- 0x004aa930  Text_GetDefaultFont ---- */
void * Text_GetDefaultFont(void)

{
  return g_pDefaultFont;
}

/* ---- 0x004aa940  Font_LoadFile ---- */
int __cdecl Font_LoadFile(char *filename,void **outFont)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 1;
  iVar1 = (*g_pSvcText->pFopen)(filename,&DAT_004ddb18);
  if (iVar1 != 0) {
    iVar2 = Text_BuildLineTable(iVar1,outFont);
    (*g_pSvcText->pFclose)(iVar1);
  }
  return iVar2;
}

/* ---- 0x004aa990  Font_Free ---- */
void __cdecl Font_Free(void *font)

{
  if ((font != (void *)0x0) && (font != g_pDefaultFont)) {
    (*g_pSvcText->pHFree)(font);
  }
  return;
}

/* ---- 0x004aa9b0  Text_NextChar ---- */
/* Text.c: returns the next character of the text cursor (asserts *ppText) */

int __cdecl Text_NextChar(char **pText)

{
  uint uVar1;
  char *pcVar2;
  
  if (*pText == (char *)0x0) {
    (*g_pSvcText->pAssertFail)
              (s__ppText______void___0__004ed03c,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x1fc);
  }
  uVar1 = (uint)(byte)**pText;
  pcVar2 = (char *)(-(uint)(uVar1 != 0) & (uint)(*pText + 1));
  *pText = pcVar2;
  if ((uVar1 == 0) && (pcVar2 != (char *)0x0)) {
    (*g_pSvcText->pAssertFail)
              (s_c_____0______c______0______ppTex_004ed008,
               s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x20a);
  }
  return uVar1;
}

/* ---- 0x004aaa20  Text_CharWidth ---- */
/* Source: Temp/Text.c (line 624, from __FILE__/__LINE__ passed to the allocator) */

int __cdecl Text_CharWidth(void *ctx,int ch)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = *(int *)((int)ctx + 8);
  if (iVar1 == 0) {
    (*g_pSvcText->pAssertFail)(s_hFont_004ed078,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x270);
  }
  uVar2 = (*g_pSvcText->pHLock)(iVar1);
  iVar3 = Font_GlyphWidth(ctx,uVar2,ch);
  (*g_pSvcText->pHUnlock)(iVar1);
  return iVar3;
}

/* ---- 0x004aaa80  Text_MeasureWidth ---- */
/* Widest laid-out line of the text */

int __cdecl Text_MeasureWidth(void *ctx,char *text)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(undefined4 (*)[12])(_frame + (0x50 - 0x30)))
  
  uVar3 = 0;
  puVar4 = ctx;
  puVar5 = local_30;
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  iVar2 = *(int *)((int)ctx + 8);
  local_34 = 0;
  if (iVar2 == 0) {
    (*g_pSvcText->pAssertFail)(s_hFont_004ed078,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x28d);
  }
  uVar1 = (*g_pSvcText->pHLock)(iVar2);
  do {
    text = (char *)Text_LayoutString(local_30,uVar1,text,&local_34,0,1);
    if ((int)uVar3 <= (int)local_34) {
      uVar3 = local_34;
    }
  } while (text != (char *)0x0);
  (*g_pSvcText->pHUnlock)(iVar2);
  return uVar3;
}
#undef local_30
#undef local_34


/* ---- 0x004aab10  Text_MeasureHeight ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Source: Temp/Text.c (line 688, from __FILE__/__LINE__ passed to the allocator) */

int Text_MeasureHeight(void *ctx,char *text)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  #define local_30 (*(undefined4 (*)[12])(_frame + (0x40 - 0x30)))
  
  iVar1 = *(int *)((int)ctx + 8);
  puVar4 = ctx;
  puVar5 = local_30;
  for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  iVar3 = 0;
  if (iVar1 == 0) {
    (*g_pSvcText->pAssertFail)(s_hFont_004ed078,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x2b0);
  }
  uVar2 = (*g_pSvcText->pHLock)(iVar1);
  do {
    text = (char *)Text_LayoutString(local_30,uVar2,text,0,0,1);
    iVar3 = iVar3 + (*(int *)(**(int **)((int)ctx + 8) + 4) * *(int *)((int)ctx + 0x24) + 0xffffU >>
                    0x10);
  } while (text != (char *)0x0);
  (*g_pSvcText->pHUnlock)(iVar1);
  return iVar3;
}
#undef local_30


/* ---- 0x004aabb0  Text_DrawFormatted ---- */
/* Formats into a 1000-byte buffer and draws it with the default font */

undefined4 Text_DrawFormatted(void *param_1,int param_2)

{
  unsigned char _frame[0x400];  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 uVar2;
  void *font;
  #define local_3ec (*(char (*)[1004])(_frame + (0x400 - 0x3ec)))
  
  if (param_2 == 0) {
    return 0;
  }
  uVar2 = vsprintf(local_3ec,param_2,&STACK0X(0x0000000c));
  iVar1 = *(int *)((int)param_1 + 8);
  if (iVar1 == 0) {
    (*g_pSvcText->pAssertFail)(s_hFont_004ed078,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x2fa);
  }
  font = (void *)(*g_pSvcText->pHLock)(iVar1);
  Text_DrawString(param_1,font,local_3ec);
  (*g_pSvcText->pHUnlock)(iVar1);
  return uVar2;
}
#undef local_3ec


/* ---- 0x004aac40  Text_WrapLines ---- */
/* Splits a text object's string into lines at the wrap width */

undefined4 Text_WrapLines(uint *param_1)

{
  unsigned char _frame[0x460] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  int iVar6;
  uint uVar7;
  uint *puVar8;
  undefined2 *puVar9;
  char *pcVar10;
  uint uVar11;
  uint *puVar12;
  undefined4 *puVar13;
  #define local_444 (*(uint *)(_frame + (0x460 - 0x444)))
  #define local_43e (*(undefined1 *)(_frame + (0x460 - 0x43e)))
  #define local_43d (*(undefined1 *)(_frame + (0x460 - 0x43d)))
  #define local_43c (*(uint *)(_frame + (0x460 - 0x43c)))
  #define uStack_438 (*(uint *)(_frame + (0x460 - 0x438)))
  #define iStack_434 (*(int *)(_frame + (0x460 - 0x434)))
  #define local_430 (*(uint *)(_frame + (0x460 - 0x430)))
  #define local_42c (*(uint *)(_frame + (0x460 - 0x42c)))
  #define local_428 (*(uint *)(_frame + (0x460 - 0x428)))
  #define local_424 (*(uint *)(_frame + (0x460 - 0x424)))
  #define local_420 (*(uint *)(_frame + (0x460 - 0x420)))
  #define local_414 (*(uint *)(_frame + (0x460 - 0x414)))
  #define local_410 (*(uint *)(_frame + (0x460 - 0x410)))
  #define local_40c (*(uint *)(_frame + (0x460 - 0x40c)))
  #define local_408 (*(uint *)(_frame + (0x460 - 0x408)))
  #define local_404 (*(uint *)(_frame + (0x460 - 0x404)))
  #define local_400 (*(uint *)(_frame + (0x460 - 0x400)))
  
  puVar8 = &local_430;
  for (iVar6 = 0xc; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  local_42c = UINT_004eca00 >> 0x10 & 0xff;
  local_43e = 0;
  local_428 = local_42c - 1;
  uVar4 = UINT_004eca00 & 0xffff;
  local_43d = 0xff;
  local_424 = 0;
  local_420 = 1;
  local_414 = 0;
  local_410 = uVar4;
  if (uVar4 != 0) {
    puVar8 = &UINT_004eca04;
    puVar12 = &local_400;
    for (uVar7 = uVar4; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar12 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar12 = puVar12 + 1;
    }
  }
  local_408 = uVar4 * 2 + 0x30;
  local_43c = uVar4 * 0x5c;
  uVar7 = local_408 + local_43c;
  local_40c = 0x30;
  local_404 = uVar7;
  if (uVar4 != 0) {
    puVar8 = &local_400;
    uVar11 = uVar4;
    do {
      uVar2 = *puVar8;
      if (uVar2 != 0) {
        uVar7 = uVar7 + (uint)*(byte *)((int)&UINT_004eca00 + uVar2 + 1) *
                        (uint)*(byte *)((int)&UINT_004eca00 + uVar2);
      }
      puVar8 = puVar8 + 1;
      uVar11 = uVar11 - 1;
    } while (uVar11 != 0);
  }
  uStack_438 = (*g_pSvcText->pHAlloc)(uVar7);
  if (uStack_438 != 0) {
    puVar5 = (uint *)(*g_pSvcText->pHLock)(uStack_438);
    puVar8 = &local_430;
    puVar12 = puVar5;
    for (iVar6 = 0xc; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar12 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar12 = puVar12 + 1;
    }
    *puVar5 = uStack_438;
    puVar9 = (undefined2 *)(puVar5[9] + (int)puVar5);
    iVar6 = 0;
    if (uVar4 != 0) {
      do {
        *puVar9 = (short)iVar6;
        iVar6 = iVar6 + 1;
        puVar9 = puVar9 + 1;
      } while (iVar6 < (int)uVar4);
    }
    uVar7 = puVar5[10];
    puVar13 = (undefined4 *)(uVar7 + (int)puVar5);
    for (uVar11 = local_43c >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
      *puVar13 = 0;
      puVar13 = puVar13 + 1;
    }
    iVar6 = 0;
    for (uVar11 = local_43c & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
      *(undefined1 *)puVar13 = 0;
      puVar13 = (undefined4 *)((int)puVar13 + 1);
    }
    iStack_434 = puVar5[0xb] + (int)puVar5;
    if (uVar4 != 0) {
      local_444 = (uint)&local_400;
      pcVar10 = (char *)((int)(uVar7 + (int)puVar5) + 6);
      local_43c = uVar4;
      do {
        iVar3 = *(int *)local_444;
        if (iVar3 != 0) {
          *(uint *)(pcVar10 + 6) = (uint)*(byte *)((int)&UINT_004eca00 + iVar3);
          *(uint *)(pcVar10 + 10) = (uint)*(byte *)((int)&UINT_004eca00 + iVar3 + 1);
          cVar1 = *(char *)((int)&UINT_004eca00 + iVar3 + 2);
          pcVar10[-1] = cVar1;
          pcVar10[-2] = pcVar10[6] + cVar1;
          cVar1 = *(char *)((int)&UINT_004eca00 + iVar3 + 3);
          uVar4 = puVar5[2];
          pcVar10[0xe] = '\x01';
          pcVar10[0xf] = '\0';
          pcVar10[0x10] = '\0';
          pcVar10[0x11] = '\0';
          *pcVar10 = cVar1 - (char)uVar4;
          *(int *)(pcVar10 + -6) = iVar6;
          *(int *)(pcVar10 + 2) = iVar6 + iStack_434;
          uVar4 = (int)*pcVar10;
          if ((int)puVar5[5] < (int)*pcVar10) {
            uVar4 = puVar5[5];
          }
          puVar5[5] = uVar4;
          uVar4 = *(int *)(pcVar10 + 10) + (int)*pcVar10;
          if ((uint)(*(int *)(pcVar10 + 10) + (int)*pcVar10) < puVar5[6]) {
            uVar4 = puVar5[6];
          }
          puVar5[6] = uVar4;
          Text_CopyRunes((int)&UINT_004eca04 + iVar3,pcVar10 + 2,1,&local_43e);
          iVar6 = iVar6 + *(int *)(pcVar10 + 6) * *(int *)(pcVar10 + 10);
        }
        local_444 = local_444 + 4;
        pcVar10 = pcVar10 + 0x5c;
        local_43c = local_43c - 1;
      } while (local_43c != 0);
    }
    uVar4 = uStack_438;
    (*g_pSvcText->pHUnlock)(uStack_438);
    *param_1 = uVar4;
    return 0;
  }
  *param_1 = 0;
  return 1;
}
#undef iStack_434
#undef local_400
#undef local_404
#undef local_408
#undef local_40c
#undef local_410
#undef local_414
#undef local_420
#undef local_424
#undef local_428
#undef local_42c
#undef local_430
#undef local_43c
#undef local_43d
#undef local_43e
#undef local_444
#undef uStack_438


/* ---- 0x004aae90  Text_CopyRunes ---- */
void Text_CopyRunes(byte *param_1,undefined4 *param_2,int param_3,int param_4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  puVar1 = param_2;
  puVar6 = (undefined1 *)*param_2;
  iVar3 = -1;
  param_2 = (undefined4 *)0x0;
  pbVar4 = param_1;
  if (puVar1[2] != 0) {
    do {
      uVar2 = 0;
      puVar5 = puVar6;
      if (puVar1[1] != 0) {
        do {
          if (iVar3 < 0) {
            pbVar4 = (byte *)(uint)*param_1;
            param_1 = param_1 + 1;
            iVar3 = 8 - param_3;
          }
          puVar6 = puVar5 + 1;
          *puVar5 = *(undefined1 *)
                     (((int)pbVar4 >> ((byte)iVar3 & 0x1f) & 0xff >> ((byte)(8 - param_3) & 0x1f)) +
                     param_4);
          iVar3 = iVar3 - param_3;
          uVar2 = uVar2 + 1;
          puVar5 = puVar6;
        } while (uVar2 < (uint)puVar1[1]);
      }
      param_2 = (undefined4 *)((int)param_2 + 1);
    } while (param_2 < (uint)puVar1[2]);
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004aaf30  Text_BuildLineTable ---- */
undefined4 Text_BuildLineTable(undefined4 param_1,int *param_2)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  char *pcVar7;
  int *piVar8;
  #define uStack_42 (*(undefined2 *)(_frame + (0x60 - 0x42)))
  #define local_40 (*(int *)(_frame + (0x60 - 0x40)))
  #define iStack_3c (*(int *)(_frame + (0x60 - 0x3c)))
  #define iStack_38 (*(int *)(_frame + (0x60 - 0x38)))
  #define iStack_34 (*(int *)(_frame + (0x60 - 0x34)))
  #define aiStack_30 (*(int (*)[4])(_frame + (0x60 - 0x30)))
  #define iStack_20 (*(int *)(_frame + (0x60 - 0x20)))
  #define iStack_14 (*(int *)(_frame + (0x60 - 0x14)))
  #define iStack_10 (*(int *)(_frame + (0x60 - 0x10)))
  
  uVar1 = param_1;
  (*g_pSvcText->pFread)(param_1,&local_40,4);
  (*g_pSvcText->pFread)(uVar1,&local_40,4);
  iVar5 = local_40;
  piVar6 = aiStack_30;
  for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  iStack_34 = local_40;
  (*g_pSvcText->pFread)(uVar1,&local_40,4);
  aiStack_30[1] = local_40;
  (*g_pSvcText->pFread)(uVar1,&local_40,4);
  aiStack_30[2] = local_40;
  (*g_pSvcText->pFread)(uVar1,&local_40,4);
  aiStack_30[3] = local_40;
  (*g_pSvcText->pFread)(uVar1,&local_40,4);
  iStack_20 = local_40;
  (*g_pSvcText->pFread)(uVar1,&local_40,4);
  iVar4 = local_40;
  iStack_14 = local_40;
  (*g_pSvcText->pFread)(uVar1,&local_40,4);
  iStack_10 = local_40;
  iStack_3c = (local_40 - iVar4) + 1;
  iStack_38 = (*g_pSvcText->pHAlloc)(iVar5 + 0x30 + iStack_3c * 0x5e);
  if (iStack_38 != 0) {
    piVar2 = (int *)(*g_pSvcText->pHLock)(iStack_38);
    piVar6 = aiStack_30;
    piVar8 = piVar2;
    for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar8 = *piVar6;
      piVar6 = piVar6 + 1;
      piVar8 = piVar8 + 1;
    }
    *piVar2 = iStack_38;
    piVar2[9] = 0x30;
    piVar6 = piVar2 + 0xc;
    iVar5 = iStack_3c;
    if (0 < iStack_3c) {
      do {
        (*g_pSvcText->pFread)(uVar1,&uStack_42,2);
        *(undefined2 *)piVar6 = uStack_42;
        piVar6 = (int *)((int)piVar6 + 2);
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    iVar5 = piVar2[9] + iStack_3c * 2;
    piVar2[10] = iVar5;
    if (0 < iStack_3c) {
      pcVar7 = (char *)((int)piVar2 + iVar5 + 6);
      iVar5 = iStack_3c;
      do {
        (*g_pSvcText->pFread)(uVar1,&local_40,4);
        *(int *)(pcVar7 + -6) = local_40;
        (*g_pSvcText->pFread)(uVar1,&param_1,1);
        pcVar7[-2] = (char)param_1;
        (*g_pSvcText->pFread)(uVar1,&param_1,1);
        pcVar7[-1] = (char)param_1;
        (*g_pSvcText->pFread)(uVar1,&param_1,1);
        *pcVar7 = (char)param_1;
        (*g_pSvcText->pFread)(uVar1,&param_1,1);
        pcVar7[1] = (char)param_1;
        (*g_pSvcText->pFread)(uVar1,&local_40,4);
        *(int *)(pcVar7 + 6) = local_40;
        (*g_pSvcText->pFread)(uVar1,&local_40,4);
        pcVar7[0xe] = '\x01';
        pcVar7[0xf] = '\0';
        pcVar7[0x10] = '\0';
        pcVar7[0x11] = '\0';
        *(int *)(pcVar7 + 10) = local_40;
        iVar4 = (int)*pcVar7;
        if (piVar2[5] < (int)*pcVar7) {
          iVar4 = piVar2[5];
        }
        piVar2[5] = iVar4;
        uVar3 = (int)*pcVar7 + *(int *)(pcVar7 + 10);
        if ((uint)((int)*pcVar7 + *(int *)(pcVar7 + 10)) < (uint)piVar2[6]) {
          uVar3 = piVar2[6];
        }
        pcVar7 = pcVar7 + 0x5c;
        iVar5 = iVar5 + -1;
        piVar2[6] = uVar3;
      } while (iVar5 != 0);
    }
    iVar5 = piVar2[10] + iStack_3c * 0x5c;
    piVar2[0xb] = iVar5;
    (*g_pSvcText->pFread)(uVar1,(int)piVar2 + iVar5,iStack_34);
    iVar5 = iStack_38;
    (*g_pSvcText->pHUnlock)(iStack_38);
    *param_2 = iVar5;
    return 0;
  }
  *param_2 = 0;
  return 1;
}
#undef aiStack_30
#undef iStack_10
#undef iStack_14
#undef iStack_20
#undef iStack_34
#undef iStack_38
#undef iStack_3c
#undef local_40
#undef uStack_42


/* ---- 0x004ab210  Text_LayoutString ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Advances through the string computing glyph positions for the given width (ctx at +0x208) */

char * Text_LayoutString(void *param_1,void *param_2,char *param_3,int *param_4,uint *param_5,
                        int param_6)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  void *ctx;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  local_c = (uint)param_3;
  ctx = param_1;
  uVar1 = *(uint *)((int)param_1 + 0x28);
  iVar7 = **(int **)((int)param_1 + 4);
  local_10 = *(int *)((int)param_1 + 0xc) - iVar7;
  uVar3 = ((*(int **)((int)param_1 + 4))[2] + iVar7) - *(int *)((int)param_1 + 0xc);
  if ((uVar1 & 1) == 0) {
    if ((uVar1 & 2) != 0) goto LAB_004ab257;
  }
  else {
    if ((int)local_10 < (int)uVar3) {
      uVar3 = local_10;
    }
    uVar3 = uVar3 * 2;
  }
  local_10 = uVar3;
LAB_004ab257:
  iVar7 = 0;
  uVar3 = 0;
  local_14 = 0;
  param_1 = (void *)0x0;
  local_18 = 0;
  local_1c = 0;
  iVar4 = Text_NextChar(&param_3);
  iVar6 = (int)param_1;
  do {
    param_1 = (void *)iVar6;
    pcVar2 = param_3;
    if (iVar4 == 0) {
LAB_004ab425:
      param_3 = pcVar2;
      if (iVar4 == 0) {
        iVar4 = (int)param_1 + uVar3 + local_14;
        if (((int)local_10 < iVar4) && ((uVar1 & 4) != 0)) {
          param_3 = (char *)local_c;
          if (local_1c == 0) {
            local_1c = iVar7 + local_18;
            param_3 = (char *)0x0;
            param_1 = (void *)iVar4;
          }
        }
        else {
          local_1c = local_1c + iVar7 + local_18;
          param_3 = (char *)0x0;
          param_1 = (void *)iVar4;
        }
      }
      if (param_6 != 0) {
        if (param_3 == (char *)0x0) {
          if ((uVar1 & 1) == 0) {
            iVar7 = (int)param_1;
            if ((uVar1 & 2) != 0) {
              iVar7 = -(int)param_1;
            }
            *(int *)((int)ctx + 0xc) = *(int *)((int)ctx + 0xc) + iVar7;
          }
          else {
            *(int *)((int)ctx + 0xc) = (int)param_1 / 2 + *(int *)((int)ctx + 0xc);
          }
        }
        else {
          *(uint *)((int)ctx + 0x10) =
               (*(int *)((int)ctx + 0x24) * *(int *)(**(int **)((int)ctx + 8) + 4) + 0xffffU >> 0x10
               ) + *(int *)((int)ctx + 0x10);
        }
      }
      if (param_5 != (uint *)0x0) {
        *param_5 = local_1c;
      }
      if (param_4 != (int *)0x0) {
        *param_4 = (int)param_1;
      }
      return param_3;
    }
    if (((iVar4 == 0x20) || (iVar4 == 0xfe)) && ((uVar1 & 4) != 0)) {
      param_1 = (void *)(iVar6 + uVar3 + local_14);
      if ((int)local_10 < (int)param_1) {
        param_1 = (void *)iVar6;
        pcVar2 = (char *)local_c;
        if (local_1c == 0) {
          local_1c = iVar7 + local_18;
          param_1 = (void *)(iVar6 + uVar3 + local_14);
          pcVar2 = param_3;
        }
      }
      else {
        local_1c = local_1c + iVar7 + local_18;
        uVar3 = Font_GlyphAdvance(ctx,param_2,iVar4);
        local_14 = 0;
        local_18 = 0;
        iVar7 = 1;
        local_c = (uint)param_3;
        iVar4 = Text_NextChar(&param_3);
        if (iVar4 != 0) {
          do {
            if ((iVar4 != 0x20) && (iVar4 != 0xfe)) break;
            uVar5 = Font_GlyphAdvance(ctx,param_2,iVar4);
            uVar3 = uVar3 + uVar5;
            iVar7 = iVar7 + 1;
            local_c = (uint)param_3;
            iVar4 = Text_NextChar(&param_3);
          } while (iVar4 != 0);
          if (iVar4 != 0) goto LAB_004ab344;
        }
        local_1c = local_1c + iVar7;
        param_1 = (void *)((int)param_1 + uVar3);
        pcVar2 = param_3;
      }
      goto LAB_004ab425;
    }
LAB_004ab344:
    if ((iVar4 == 0xd) || (iVar4 == 10)) {
      iVar6 = (int)param_1 + uVar3 + local_14;
      if (((int)local_10 < iVar6) && ((uVar1 & 4) != 0)) {
        param_3 = (char *)local_c;
        pcVar2 = param_3;
      }
      else {
        local_1c = local_1c + iVar7 + local_18;
        param_1 = (void *)iVar6;
        pcVar2 = param_3;
        if ((iVar4 == 0xd) && (*param_3 == '\n')) {
          pcVar2 = param_3 + 1;
        }
      }
      goto LAB_004ab425;
    }
    uVar5 = Font_GlyphAdvance(ctx,param_2,iVar4);
    local_14 = local_14 + uVar5;
    local_18 = local_18 + 1;
    iVar4 = Text_NextChar(&param_3);
    iVar6 = (int)param_1;
  } while( true );
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004ab510  Font_GlyphAdvance ---- */
uint __cdecl Font_GlyphAdvance(void *ctx,void *font,int ch)

{
  int iVar1;
  uint uVar2;
  
  if (*(int *)((int)font + 0x20) < ch) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)((int)font + 0x28) +
            (uint)*(ushort *)
                   (*(int *)((int)font + 0x24) + (ch - *(int *)((int)font + 0x1c)) * 2 + (int)font)
            * 0x5c + (int)font;
  }
  if (iVar1 != 0) {
    uVar2 = (int)*(char *)(iVar1 + 4);
    if ((uint)(int)*(char *)(iVar1 + 4) <= *(uint *)(iVar1 + 0xc)) {
      uVar2 = *(uint *)(iVar1 + 0xc);
    }
    return *(int *)((int)ctx + 0x20) * uVar2 + 0xffff >> 0x10;
  }
  return 0;
}

/* ---- 0x004ab570  Font_GlyphWidth ---- */
uint Font_GlyphWidth(int param_1,int param_2,uint param_3)

{
  if (*(int *)(param_2 + 0x20) < (int)(param_3 & 0xff)) {
    param_2 = 0;
  }
  else {
    param_2 = *(int *)(param_2 + 0x28) +
              (uint)*(ushort *)
                     (*(int *)(param_2 + 0x24) + ((param_3 & 0xff) - *(int *)(param_2 + 0x1c)) * 2 +
                     param_2) * 0x5c + param_2;
  }
  if (param_2 != 0) {
    return (int)*(char *)(param_2 + 4) * *(int *)(param_1 + 0x20) + 0xffffU >> 0x10;
  }
  return 0;
}

/* ---- 0x004ab5d0  Text_DrawString ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void __cdecl Text_DrawString(void *ctx,void *font,char *text)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *ctx_00;
  int iVar2;
  void *pvVar3;
  int ch;
  uint uVar4;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  ctx_00 = ctx;
  ch = 0;
  local_10 = *(uint *)((int)ctx + 0x28);
  DAT_008d0880 = *(undefined1 *)((int)ctx + 0x18);
  *(uint *)((int)ctx + 0x28) = local_10 & 0xfffffff7;
  DAT_008d0900 = *(undefined1 *)((int)ctx + 0x1c);
  DAT_008d097f = *(undefined1 *)((int)ctx + 0x14);
  if (text == (char *)0x0) {
LAB_004ab6fb:
    *(uint *)((int)ctx_00 + 0x28) = local_10;
    return;
  }
  uVar4 = local_10 & 1;
  local_8 = uVar4;
  do {
    local_c = Text_LayoutString(ctx_00,font,text,&ctx,&local_14,0);
    iVar1 = *(int *)((int)ctx_00 + 0xc);
    local_4 = *(uint *)((int)ctx_00 + 0x10);
    if (uVar4 == 0) {
      iVar2 = iVar1;
      pvVar3 = ctx;
      if ((local_10 & 2) != 0) goto LAB_004ab66a;
    }
    else {
      pvVar3 = (void *)((int)ctx / 2);
LAB_004ab66a:
      iVar2 = iVar1 - (int)pvVar3;
    }
    *(int *)((int)ctx_00 + 0xc) = iVar2;
    local_18 = 0;
    iVar2 = ch;
    if (0 < (int)local_14) {
      do {
        ch = Text_NextChar(&text);
        if ((iVar2 != 10) || (ch != 0xd)) {
          Text_DrawChar(ctx_00,font,ch);
        }
        local_18 = local_18 + 1;
        iVar2 = ch;
        uVar4 = local_8;
      } while ((int)local_18 < (int)local_14);
    }
    if (local_c == 0) goto LAB_004ab6fb;
    *(int *)((int)ctx_00 + 0xc) = iVar1;
    *(uint *)((int)ctx_00 + 0x10) =
         (*(int *)(**(int **)((int)ctx_00 + 8) + 4) * *(int *)((int)ctx_00 + 0x24) + 0xffffU >> 0x10
         ) + local_4;
    text = (char *)local_c;
  } while( true );
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004ab710  Text_DrawChar ---- */
/* Picks the glyph blitter: 16-bit vs paletted 8-bit (flag 8), clipped vs unclipped; scaled glyphs
   are not implemented (Lua_Stub) */

void __cdecl Text_DrawChar(void *ctx,void *font,int ch)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  void *pvVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int *piVar11;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  pvVar6 = ctx;
  local_c = 0;
  iVar1 = *(int *)((int)ctx + 0x10);
  piVar2 = *(int **)((int)ctx + 4);
  iVar3 = *(int *)((int)ctx + 0xc);
  iVar4 = *(int *)((int)ctx + 0x20);
  iVar5 = *(int *)((int)ctx + 0x24);
  if (*(int *)((int)font + 0x20) < ch) {
    piVar11 = (int *)0x0;
  }
  else {
    piVar11 = (int *)(*(int *)((int)font + 0x28) +
                      (uint)*(ushort *)
                             (*(int *)((int)font + 0x24) + (ch - *(int *)((int)font + 0x1c)) * 2 +
                             (int)font) * 0x5c + (int)font);
  }
  if (piVar11 != (int *)0x0) {
    piVar11[2] = (int)font + *piVar11 + *(int *)((int)font + 0x2c);
    if ((iVar4 == 0x10000) && (iVar5 == 0x10000)) {
      uVar9 = (uint)*(char *)((int)piVar11 + 5);
      uVar7 = piVar11[3];
      uVar8 = piVar11[4];
      uVar10 = (uint)*(char *)((int)piVar11 + 6);
    }
    else {
      uVar9 = *(char *)((int)piVar11 + 5) * iVar4 + 0xffffU >> 0x10;
      uVar10 = *(char *)((int)piVar11 + 6) * iVar5 + 0xffffU >> 0x10;
      uVar7 = piVar11[3] * iVar4 + 0xffffU >> 0x10;
      uVar8 = piVar11[4] * iVar5 + 0xffffU >> 0x10;
      local_c = 1;
    }
    local_14 = iVar1 + uVar10;
    ctx = (void *)(iVar3 + uVar9);
    if (((((int)ctx < *piVar2) || ((int)local_14 < piVar2[1])) ||
        (piVar2[2] + *piVar2 <= (int)(uVar7 + (int)ctx))) ||
       (piVar2[3] + piVar2[1] <= (int)(uVar8 + local_14))) {
      local_c = local_c | 2;
    }
    if ((*(byte *)((int)pvVar6 + 0x28) & 8) != 0) {
      local_c = local_c | 4;
    }
    switch(local_c) {
    case 0:
      Glyph_Blit16(piVar11,font,pvVar6);
      break;
    case 1:
    case 3:
      ((code *)Lua_Stub)(piVar11,font,pvVar6);
      break;
    case 2:
      Glyph_Blit16Clipped(piVar11,font,pvVar6);
      break;
    case 4:
      Glyph_Blit8(piVar11,font,pvVar6);
      break;
    case 5:
    case 7:
      ((code *)Lua_Stub)(piVar11,font,pvVar6);
      break;
    case 6:
      Glyph_Blit8Clipped(piVar11,font,pvVar6);
    }
    *(uint *)((int)pvVar6 + 0xc) =
         *(int *)((int)pvVar6 + 0xc) + ((char)piVar11[1] * iVar4 + 0xffffU >> 0x10);
  }
  return;
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c

