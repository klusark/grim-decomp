/* GRIMFANDANGO.EXE :: text.c
 * functions 0x0048c050 .. 0x004ab710 (20 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048c050  GetTextParamsFromTable ---- */
/* Reads x, y, font, width, height, fgcolor, bgcolor, ... keys from a Lua table into a text context
   Original name GetTextParamsFromTable (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetSayLineDefaults; 5 matched neighbours agree, 0 disagree); was
   Text_ParseLuaTable. */

int __cdecl GetTextParamsFromTable(TextContext *ctx,void *table,TextObject *textObj)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  uint uVar5;
  longlong lVar6;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  piVar1 = ctx->pClipRect;
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrX);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar3 = lua_isnumber(iVar2);
    if (iVar3 != 0) {
      lVar6 = (longlong)lua_getnumber(iVar2);
      ctx->nX = (int)lVar6;
      if (textObj != (TextObject *)0x0) {
        lVar6 = (longlong)lua_getnumber(iVar2);
        textObj->nX = (int)lVar6;
      }
    }
  }
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrY);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar3 = lua_isnumber(iVar2);
    if (iVar3 != 0) {
      lVar6 = (longlong)lua_getnumber(iVar2);
      ctx->nY = (int)lVar6 + *(int *)(*(int *)ctx->pFont + 8);
      if (textObj != (TextObject *)0x0) {
        lVar6 = (longlong)lua_getnumber(iVar2);
        textObj->nY = (int)lVar6;
      }
    }
  }
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrFont);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar3 = lua_isuserdata(iVar2);
    if (iVar3 != 0) {
      iVar3 = lua_tag(iVar2);
      if ((iVar3 == 0x544e4f46) && (g_hEmergencyFont == (void *)0x0)) {
        pvVar4 = (void *)lua_getuserdata(iVar2);
        ctx->pFont = pvVar4;
      }
    }
  }
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrWidth);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar3 = lua_isnumber(iVar2);
    if ((iVar3 != 0) && (piVar1 != (int *)0x0)) {
      lVar6 = (longlong)lua_getnumber(iVar2);
      piVar1[2] = (int)lVar6;
    }
  }
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrHeight);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar3 = lua_isnumber(iVar2);
    if ((iVar3 != 0) && (piVar1 != (int *)0x0)) {
      lVar6 = (longlong)lua_getnumber(iVar2);
      piVar1[3] = (int)lVar6;
    }
  }
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrFGColor);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar3 = lua_isuserdata(iVar2);
    if (iVar3 != 0) {
      iVar3 = lua_tag(iVar2);
      if (iVar3 == 0x524c4f43) {
        uVar5 = lua_getuserdata(iVar2);
        ctx->dwFgColor = uVar5;
      }
    }
  }
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrBGColor);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar3 = lua_isuserdata(iVar2);
    if (iVar3 != 0) {
      iVar3 = lua_tag(iVar2);
      if (iVar3 == 0x524c4f43) {
        uVar5 = lua_getuserdata(iVar2);
        ctx->dwBgColor = uVar5;
      }
    }
  }
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrFXColor);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar3 = lua_isuserdata(iVar2);
    if (iVar3 != 0) {
      iVar3 = lua_tag(iVar2);
      if (iVar3 == 0x524c4f43) {
        uVar5 = lua_getuserdata(iVar2);
        ctx->dwFxColor = uVar5;
      }
    }
  }
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrCenter);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar2 = lua_isnil(iVar2);
    if (iVar2 == 0) {
      ctx->dwFlags = 5;
    }
  }
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrLJustify);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar2 = lua_isnil(iVar2);
    if (iVar2 == 0) {
      ctx->dwFlags = 4;
    }
  }
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrRJustify);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar2 = lua_isnil(iVar2);
    if (iVar2 == 0) {
      ctx->dwFlags = 6;
    }
  }
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrDuration);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar3 = lua_isnumber(iVar2);
    if (iVar3 != 0) {
      lVar6 = (longlong)lua_getnumber(iVar2);
      return (int)lVar6;
    }
  }
  return -1;
}
#undef local_4
#undef local_8


/* ---- 0x0048c8d0  sputText_ExtractSayLineData ---- */
/* Splits a '/id/text' dialogue line: copies the id into outId and returns the text according to
   g_nTranslationType (translated, id only, or raw) Original name sputText_ExtractSayLineData (the
   remaster's GrimFandango (Linux): splits '/id/text' (PolyglotGetString, translationType)); was
   Text_ParseLineId. */

char * __cdecl sputText_ExtractSayLineData(char *line,char *outId)

{
  char *pcVar1;
  char *pcVar2;
  
  if (outId != (char *)0x0) {
    *outId = '\0';
  }
  pcVar1 = PolyglotGetString(line);
  pcVar2 = pcVar1;
  if (((outId != (char *)0x0) && (line != (char *)0x0)) && (*line == '/')) {
    pcVar2 = (char *)strchr(line + 1,0x2f);
    if (pcVar2 != (char *)0x0) {
      strncpy(outId,line + 1,pcVar2 + (-1 - (int)line));
      (pcVar2 + (int)outId)[-1 - (int)line] = '\0';
    }
  }
  if (g_nTranslationType != 1) {
    outId = pcVar1;
    if (g_nTranslationType == 2) {
      outId = line;
    }
    return outId;
  }
  return pcVar2 + 1;
}

/* ---- 0x00494740  sputActor_GetActorTextRate ---- */
/* Original name sputActor_GetActorTextRate (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_GetTextSpeed; 1 matched neighbours agree, 0 disagree); was Text_GetSpeed. */

int sputActor_GetActorTextRate(void)

{
  return g_nTextRate;
}

/* ---- 0x00494750  sputActor_SetActorTextRate ---- */
/* Original name sputActor_SetActorTextRate (the remaster's GrimFandango (Linux): aligned call in
   sputLua_SetTextSpeed); was Text_SetSpeed. */

void __cdecl sputActor_SetActorTextRate(int speed)

{
  if (speed < 1) {
    g_nTextRate = 1;
    return;
  }
  if (10 < speed) {
    speed = 10;
  }
  g_nTextRate = speed;
  return;
}

/* ---- 0x004aa930  Text_GetSystemFont ---- */
/* Original name Text_GetSystemFont (the remaster's GrimFandango (Linux): aligned call in
   sputText_Restore, sputText_Startup); was Text_GetDefaultFont. */

void * Text_GetSystemFont(void)

{
  return g_pDefaultFont;
}

/* ---- 0x004aa940  Text_LoadNativeFont ---- */
/* Original name Text_LoadNativeFont (the remaster's GrimFandango (Linux): both callers agree
   (sputResource_FontHandler, sputText_SetEmergencyFontL); the remaster rewrote the body for its
   native fonts); was Font_LoadFile. */

int __cdecl Text_LoadNativeFont(char *filename,void **outFont)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 1;
  iVar1 = (*g_pTextHS->pFopen)(filename,&DAT_004ddb18);
  if (iVar1 != 0) {
    iVar2 = Text_BuildLineTable(iVar1,outFont);
    (*g_pTextHS->pFclose)(iVar1);
  }
  return iVar2;
}

/* ---- 0x004aa990  Text_FreeFont ---- */
/* Original name Text_FreeFont (the remaster's GrimFandango (Linux): aligned call in
   sputText_SetEmergencyFontL); was Font_Free. */

void __cdecl Text_FreeFont(void *font)

{
  if ((font != (void *)0x0) && (font != g_pDefaultFont)) {
    (*g_pTextHS->pHFree)(font);
  }
  return;
}

/* ---- 0x004aa9b0  Text_NextChar ---- */
/* Returns the next character and advances; the pointer becomes NULL at the end of the string */

int __cdecl Text_NextChar(char **pText)

{
  char cVar1;
  char *pcVar2;
  
  if (*pText == (char *)0x0) {
    (*g_pTextHS->pAssertFail)
              (s__ppText______void___0__004ed03c,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x1fc);
  }
  cVar1 = **pText;
  pcVar2 = (char *)(-(uint)(cVar1 != '\0') & (uint)(*pText + 1));
  *pText = pcVar2;
  if ((cVar1 == '\0') && (pcVar2 != (char *)0x0)) {
    (*g_pTextHS->pAssertFail)
              (s_c_____0______c______0______ppTex_004ed008,
               s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x20a);
  }
  return cVar1;
}

/* ---- 0x004aaa20  Text_GetCharKernedWidth ---- */
/* Source: Temp/Text.c (line 624, from __FILE__/__LINE__ passed to the allocator) Original name
   Text_GetCharKernedWidth (the remaster's GrimFandango (Linux): aligned call in
   sputText_GetTextCharPositionL); was Text_CharWidth. */

int __cdecl Text_GetCharKernedWidth(TextContext *ctx,int ch)

{
  void *pvVar1;
  undefined4 uVar2;
  int iVar3;
  
  pvVar1 = ctx->pFont;
  if (pvVar1 == (void *)0x0) {
    (*g_pTextHS->pAssertFail)(s_hFont_004ed078,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x270);
  }
  uVar2 = (*g_pTextHS->pHLock)(pvVar1);
  iVar3 = Font_GlyphWidth(ctx,uVar2,ch);
  (*g_pTextHS->pHUnlock)(pvVar1);
  return iVar3;
}

/* ---- 0x004aaa80  Text_GetStringWidth ---- */
/* Widest laid-out line of the text Original name Text_GetStringWidth (the remaster's GrimFandango
   (Linux): aligned call in sputText_ChangeTextObjectL, sputText_GetTextObjectDimensionsL,
   sputText_MakeTextObjectL); was Text_MeasureWidth. */

int __cdecl Text_GetStringWidth(TextContext *ctx,char *text)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  TextContext *pTVar5;
  undefined4 *puVar6;
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(undefined4 (*)[12])(_frame + (0x50 - 0x30)))
  
  uVar4 = 0;
  pTVar5 = ctx;
  puVar6 = local_30;
  for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = pTVar5->pUnused;
    pTVar5 = (TextContext *)&pTVar5->pClipRect;
    puVar6 = puVar6 + 1;
  }
  pvVar1 = ctx->pFont;
  local_34 = 0;
  if (pvVar1 == (void *)0x0) {
    (*g_pTextHS->pAssertFail)(s_hFont_004ed078,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x28d);
  }
  uVar2 = (*g_pTextHS->pHLock)(pvVar1);
  do {
    text = (char *)text_FindNextBreak(local_30,uVar2,text,&local_34,0,1);
    if ((int)uVar4 <= (int)local_34) {
      uVar4 = local_34;
    }
  } while (text != (char *)0x0);
  (*g_pTextHS->pHUnlock)(pvVar1);
  return uVar4;
}
#undef local_30
#undef local_34


/* ---- 0x004aab10  Text_GetStringHeight ---- */
/* Source: Temp/Text.c (line 688, from __FILE__/__LINE__ passed to the allocator) Original name
   Text_GetStringHeight (the remaster's GrimFandango (Linux): aligned call in
   sputText_ChangeTextObjectL, sputText_GetTextObjectDimensionsL, sputText_MakeTextObjectL); was
   Text_MeasureHeight. */

int __cdecl Text_GetStringHeight(TextContext *ctx,char *text)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  undefined4 uVar2;
  int iVar3;
  TextContext *pTVar4;
  undefined4 *puVar5;
  #define local_30 (*(undefined4 (*)[12])(_frame + (0x40 - 0x30)))
  
  pvVar1 = ctx->pFont;
  pTVar4 = ctx;
  puVar5 = local_30;
  for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = pTVar4->pUnused;
    pTVar4 = (TextContext *)&pTVar4->pClipRect;
    puVar5 = puVar5 + 1;
  }
  iVar3 = 0;
  if (pvVar1 == (void *)0x0) {
    (*g_pTextHS->pAssertFail)(s_hFont_004ed078,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x2b0);
  }
  uVar2 = (*g_pTextHS->pHLock)(pvVar1);
  do {
    text = (char *)text_FindNextBreak(local_30,uVar2,text,0,0,1);
    iVar3 = iVar3 + (*(int *)(*(int *)ctx->pFont + 4) * ctx->nScaleY + 0xffffU >> 0x10);
  } while (text != (char *)0x0);
  (*g_pTextHS->pHUnlock)(pvVar1);
  return iVar3;
}
#undef local_30


/* ---- 0x004aabb0  Text_DrawFormatted ---- */
/* Formats into a 1000-byte buffer and draws it with the default font */

undefined4 Text_DrawFormatted(TextContext *param_1,int param_2)

{
  unsigned char _frame[0x400];  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  undefined4 uVar2;
  void *font;
  #define local_3ec (*(char (*)[1004])(_frame + (0x400 - 0x3ec)))
  
  if (param_2 == 0) {
    return 0;
  }
  uVar2 = vsprintf(local_3ec,param_2,&STACK0X(0x0000000c));
  pvVar1 = param_1->pFont;
  if (pvVar1 == (void *)0x0) {
    (*g_pTextHS->pAssertFail)(s_hFont_004ed078,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x2fa);
  }
  font = (void *)(*g_pTextHS->pHLock)(pvVar1);
  Text_DrawString(param_1,font,local_3ec);
  (*g_pTextHS->pHUnlock)(pvVar1);
  return uVar2;
}
#undef local_3ec


/* ---- 0x004aac40  Text_WrapLines ---- */
/* Builds the default font from the packed glyph table at g_BuiltinFontData */

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
  uStack_438 = (*g_pTextHS->pHAlloc)(uVar7);
  if (uStack_438 != 0) {
    puVar5 = (uint *)(*g_pTextHS->pHLock)(uStack_438);
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
    (*g_pTextHS->pHUnlock)(uStack_438);
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
/* Reads a .LAF font: header (data size, ..., first/last char), the char index table, 0x5c-byte
   glyph records {dataOffset, advance, xoff, yoff, ?, dataPtr, width, height} and the glyph bitmaps
    */

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
  (*g_pTextHS->pFread)(param_1,&local_40,4);
  (*g_pTextHS->pFread)(uVar1,&local_40,4);
  iVar5 = local_40;
  piVar6 = aiStack_30;
  for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  iStack_34 = local_40;
  (*g_pTextHS->pFread)(uVar1,&local_40,4);
  aiStack_30[1] = local_40;
  (*g_pTextHS->pFread)(uVar1,&local_40,4);
  aiStack_30[2] = local_40;
  (*g_pTextHS->pFread)(uVar1,&local_40,4);
  aiStack_30[3] = local_40;
  (*g_pTextHS->pFread)(uVar1,&local_40,4);
  iStack_20 = local_40;
  (*g_pTextHS->pFread)(uVar1,&local_40,4);
  iVar4 = local_40;
  iStack_14 = local_40;
  (*g_pTextHS->pFread)(uVar1,&local_40,4);
  iStack_10 = local_40;
  iStack_3c = (local_40 - iVar4) + 1;
  iStack_38 = (*g_pTextHS->pHAlloc)(iVar5 + 0x30 + iStack_3c * 0x5e);
  if (iStack_38 != 0) {
    piVar2 = (int *)(*g_pTextHS->pHLock)(iStack_38);
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
        (*g_pTextHS->pFread)(uVar1,&uStack_42,2);
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
        (*g_pTextHS->pFread)(uVar1,&local_40,4);
        *(int *)(pcVar7 + -6) = local_40;
        (*g_pTextHS->pFread)(uVar1,&param_1,1);
        pcVar7[-2] = (char)param_1;
        (*g_pTextHS->pFread)(uVar1,&param_1,1);
        pcVar7[-1] = (char)param_1;
        (*g_pTextHS->pFread)(uVar1,&param_1,1);
        *pcVar7 = (char)param_1;
        (*g_pTextHS->pFread)(uVar1,&param_1,1);
        pcVar7[1] = (char)param_1;
        (*g_pTextHS->pFread)(uVar1,&local_40,4);
        *(int *)(pcVar7 + 6) = local_40;
        (*g_pTextHS->pFread)(uVar1,&local_40,4);
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
    (*g_pTextHS->pFread)(uVar1,(int)piVar2 + iVar5,iStack_34);
    iVar5 = iStack_38;
    (*g_pTextHS->pHUnlock)(iStack_38);
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


/* ---- 0x004ab210  text_FindNextBreak ---- */
/* Advances through the string computing glyph positions for the given width (ctx at +0x208)
   Original name text_FindNextBreak (the remaster's GrimFandango (Linux): aligned call in
   Text_GetStringHeight, Text_GetStringWidth); was Text_LayoutString. */

char * text_FindNextBreak(TextContext *param_1,void *param_2,char *param_3,int *param_4,
                         uint *param_5,int param_6)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  TextContext *ctx;
  char *pcVar2;
  char cVar3;
  uint uVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint uVar5;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  int iVar6;
  int iVar7;
  int iVar8;
  #define local_1c (*(uint *)(_frame + (0x30 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  local_c = (uint)param_3;
  ctx = param_1;
  uVar1 = param_1->dwFlags;
  iVar8 = *param_1->pClipRect;
  local_10 = param_1->nX - iVar8;
  uVar4 = (param_1->pClipRect[2] + iVar8) - param_1->nX;
  if ((uVar1 & 1) == 0) {
    if ((uVar1 & 2) != 0) goto LAB_004ab257;
  }
  else {
    if ((int)local_10 < (int)uVar4) {
      uVar4 = local_10;
    }
    uVar4 = uVar4 * 2;
  }
  local_10 = uVar4;
LAB_004ab257:
  iVar8 = 0;
  uVar4 = 0;
  local_14 = 0;
  param_1 = (TextContext *)0x0;
  local_18 = 0;
  local_1c = 0;
  cVar3 = Text_NextChar(&param_3);
  iVar6 = ((uint)(cVar3));
  iVar7 = (int)param_1;
  do {
    param_1 = (TextContext *)iVar7;
    pcVar2 = param_3;
    if (iVar6 == 0) {
LAB_004ab425:
      param_3 = pcVar2;
      if (iVar6 == 0) {
        iVar6 = (int)param_1 + uVar4 + local_14;
        if (((int)local_10 < iVar6) && ((uVar1 & 4) != 0)) {
          param_3 = (char *)local_c;
          if (local_1c == 0) {
            local_1c = iVar8 + local_18;
            param_3 = (char *)0x0;
            param_1 = (TextContext *)iVar6;
          }
        }
        else {
          local_1c = local_1c + iVar8 + local_18;
          param_3 = (char *)0x0;
          param_1 = (TextContext *)iVar6;
        }
      }
      if (param_6 != 0) {
        if (param_3 == (char *)0x0) {
          if ((uVar1 & 1) == 0) {
            iVar8 = (int)param_1;
            if ((uVar1 & 2) != 0) {
              iVar8 = -(int)param_1;
            }
            ctx->nX = ctx->nX + iVar8;
          }
          else {
            ctx->nX = (int)param_1 / 2 + ctx->nX;
          }
        }
        else {
          ctx->nY = (ctx->nScaleY * *(int *)(*(int *)ctx->pFont + 4) + 0xffffU >> 0x10) + ctx->nY;
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
    if (((iVar6 == 0x20) || (iVar6 == 0xfe)) && ((uVar1 & 4) != 0)) {
      param_1 = (TextContext *)(iVar7 + uVar4 + local_14);
      if ((int)local_10 < (int)param_1) {
        param_1 = (TextContext *)iVar7;
        pcVar2 = (char *)local_c;
        if (local_1c == 0) {
          local_1c = iVar8 + local_18;
          param_1 = (TextContext *)(iVar7 + uVar4 + local_14);
          pcVar2 = param_3;
        }
      }
      else {
        local_1c = local_1c + iVar8 + local_18;
        uVar4 = Font_GlyphAdvance(ctx,param_2,iVar6);
        local_14 = 0;
        local_18 = 0;
        iVar8 = 1;
        local_c = (uint)param_3;
        cVar3 = Text_NextChar(&param_3);
        iVar6 = ((uint)(cVar3));
        if (iVar6 != 0) {
          do {
            if ((iVar6 != 0x20) && (iVar6 != 0xfe)) break;
            uVar5 = Font_GlyphAdvance(ctx,param_2,iVar6);
            uVar4 = uVar4 + uVar5;
            iVar8 = iVar8 + 1;
            local_c = (uint)param_3;
            cVar3 = Text_NextChar(&param_3);
            iVar6 = ((uint)(cVar3));
          } while (iVar6 != 0);
          if (iVar6 != 0) goto LAB_004ab344;
        }
        local_1c = local_1c + iVar8;
        param_1 = (TextContext *)((int)param_1 + uVar4);
        pcVar2 = param_3;
      }
      goto LAB_004ab425;
    }
LAB_004ab344:
    if ((iVar6 == 0xd) || (iVar6 == 10)) {
      iVar7 = (int)param_1 + uVar4 + local_14;
      if (((int)local_10 < iVar7) && ((uVar1 & 4) != 0)) {
        param_3 = (char *)local_c;
        pcVar2 = param_3;
      }
      else {
        local_1c = local_1c + iVar8 + local_18;
        param_1 = (TextContext *)iVar7;
        pcVar2 = param_3;
        if ((iVar6 == 0xd) && (*param_3 == '\n')) {
          pcVar2 = param_3 + 1;
        }
      }
      goto LAB_004ab425;
    }
    uVar5 = Font_GlyphAdvance(ctx,param_2,iVar6);
    local_14 = local_14 + uVar5;
    local_18 = local_18 + 1;
    cVar3 = Text_NextChar(&param_3);
    iVar6 = ((uint)(cVar3));
    iVar7 = (int)param_1;
  } while( true );
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004ab510  Font_GlyphAdvance ---- */
uint __cdecl Font_GlyphAdvance(TextContext *ctx,void *font,int ch)

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
    return ctx->nScaleX * uVar2 + 0xffff >> 0x10;
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
void __cdecl Text_DrawString(TextContext *ctx,void *font,char *text)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  TextContext *ctx_00;
  char cVar2;
  int iVar3;
  undefined3 extraout_var;
  TextContext *pTVar4;
  int ch;
  uint uVar5;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  ctx_00 = ctx;
  ch = 0;
  local_10 = ctx->dwFlags;
  g_bLookup = (undefined1)ctx->dwBgColor;
  ctx->dwFlags = local_10 & 0xfffffff7;
  DAT_008d0900 = (undefined1)ctx->dwFxColor;
  DAT_008d097f = (undefined1)ctx->dwFgColor;
  if (text == (char *)0x0) {
LAB_004ab6fb:
    ctx_00->dwFlags = local_10;
    return;
  }
  uVar5 = local_10 & 1;
  local_8 = uVar5;
  do {
    local_c = text_FindNextBreak(ctx_00,font,text,&ctx,&local_14,0);
    iVar1 = ctx_00->nX;
    local_4 = ctx_00->nY;
    if (uVar5 == 0) {
      iVar3 = iVar1;
      pTVar4 = ctx;
      if ((local_10 & 2) != 0) goto LAB_004ab66a;
    }
    else {
      pTVar4 = (TextContext *)((int)ctx / 2);
LAB_004ab66a:
      iVar3 = iVar1 - (int)pTVar4;
    }
    ctx_00->nX = iVar3;
    local_18 = 0;
    iVar3 = ch;
    if (0 < (int)local_14) {
      do {
        cVar2 = Text_NextChar(&text);
        ch = ((uint)(cVar2));
        if ((iVar3 != 10) || (ch != 0xd)) {
          Text_DrawChar(ctx_00,font,ch);
        }
        local_18 = local_18 + 1;
        iVar3 = ch;
        uVar5 = local_8;
      } while ((int)local_18 < (int)local_14);
    }
    if (local_c == 0) goto LAB_004ab6fb;
    ctx_00->nX = iVar1;
    ctx_00->nY = (*(int *)(*(int *)ctx_00->pFont + 4) * ctx_00->nScaleY + 0xffffU >> 0x10) + local_4
    ;
    text = (char *)local_c;
  } while( true );
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c


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

