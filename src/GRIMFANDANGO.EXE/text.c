/* GRIMFANDANGO.EXE :: text.c
 * functions 0x0048c050 .. 0x004ab710 (20 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048c050  GetTextParamsFromTable ---- */
/* Reads x, y, font, width, height, fgcolor, bgcolor, fxcolor, center/ljustify/rjustify keys from a
   Lua table into a text context (and textObj x/y if given). Returns the 'duration' key in ms, or
   -1. Only PrintLine uses the return; MakeTextObject and ChangeTextObject ignore it. Original name
   GetTextParamsFromTable (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_SetSayLineDefaults); was Text_ParseLuaTable. */

int __cdecl GetTextParamsFromTable(TextContext *ctx,void *table,TextObject *textObj)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  uint uVar5;
  longlong lVar6;
  float fVar7;
  uint local_8;
  uint local_4;
  
  piVar1 = ctx->pClipRect;
  lua_pushobject((int)table);
  iVar2 = lua_getref(g_dwLrX);
  lua_pushobject(iVar2);
  iVar2 = lua_gettable();
  if (iVar2 != 0) {
    iVar3 = lua_isnumber(iVar2);
    if (iVar3 != 0) {
      fVar7 = lua_getnumber(iVar2);
      lVar6 = FTOL((float10)fVar7);
      ctx->nX = (int)lVar6;
      if (textObj != (TextObject *)0x0) {
        fVar7 = lua_getnumber(iVar2);
        lVar6 = FTOL((float10)fVar7);
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
      fVar7 = lua_getnumber(iVar2);
      lVar6 = FTOL((float10)fVar7);
      ctx->nY = (int)lVar6 + *(int *)(*(int *)ctx->pFont + 8);
      if (textObj != (TextObject *)0x0) {
        fVar7 = lua_getnumber(iVar2);
        lVar6 = FTOL((float10)fVar7);
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
      fVar7 = lua_getnumber(iVar2);
      lVar6 = FTOL((float10)fVar7);
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
      fVar7 = lua_getnumber(iVar2);
      lVar6 = FTOL((float10)fVar7);
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
      fVar7 = lua_getnumber(iVar2);
      lVar6 = FTOL((float10)fVar7);
      return (int)lVar6;
    }
  }
  return -1;
}

/* ---- 0x0048c8d0  sputText_ExtractSayLineData ---- */
/* Splits a '/id/text' dialogue line: copies the id into outId and returns the text according to
   g_nTranslationType (translated, id only, or raw) Original name sputText_ExtractSayLineData (the
   remaster's GrimFandango (Linux): splits '/id/text' (PolyglotGetString, translationType)); was
   Text_ParseLineId. */

char * __cdecl sputText_ExtractSayLineData(char *line,char *outId)

{
  uint *puVar1;
  uint *puVar2;
  
  if (outId != (char *)0x0) {
    *outId = '\0';
  }
  puVar1 = (uint *)PolyglotGetString(line);
  puVar2 = puVar1;
  if (((outId != (char *)0x0) && (line != (char *)0x0)) && (*line == '/')) {
    puVar2 = strchr((uint *)(line + 1),'/');
    if (puVar2 != (uint *)0x0) {
      strncpy((uint *)outId,(uint *)(line + 1),(int)puVar2 + (-1 - (int)line));
      ((char *)((int)puVar2 + (int)outId))[-1 - (int)line] = '\0';
    }
  }
  if (g_nTranslationType != 1) {
    outId = (char *)puVar1;
    if (g_nTranslationType == 2) {
      outId = line;
    }
    return outId;
  }
  return (char *)((int)puVar2 + 1);
}

/* ---- 0x00494740  sputActor_GetActorTextRate ---- */
/* Original name sputActor_GetActorTextRate (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_GetTextSpeed; 1 matched neighbours agree, 0 disagree); was Text_GetSpeed. */

int __cdecl sputActor_GetActorTextRate(void)

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

void * __cdecl Text_GetSystemFont(void)

{
  return g_pDefaultFont;
}

/* ---- 0x004aa940  Text_LoadNativeFont ---- */
/* Original name Text_LoadNativeFont (the remaster's GrimFandango (Linux): both callers agree
   (sputResource_FontHandler, sputText_SetEmergencyFontL); the remaster rewrote the body for its
   native fonts); was Font_LoadFile. */

int __cdecl Text_LoadNativeFont(char *filename,void **outFont)

{
  uint text;
  uint uVar1;
  
  uVar1 = 1;
  text = (*g_pTextHS->pFopen)(filename,&DAT_004ddb18);
  if (text != 0) {
    uVar1 = Text_BuildLineTable(text,(int *)outFont);
    (*g_pTextHS->pFclose)(text);
  }
  return uVar1;
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
  int font;
  uint uVar2;
  
  pvVar1 = ctx->pFont;
  if (pvVar1 == (void *)0x0) {
    (*g_pTextHS->pAssertFail)(s_hFont_004ed078,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x270);
  }
  font = (*g_pTextHS->pHLock)(pvVar1);
  uVar2 = Font_GlyphWidth((int)ctx,font,ch);
  (*g_pTextHS->pHUnlock)(pvVar1);
  return uVar2;
}

/* ---- 0x004aaa80  Text_GetStringWidth ---- */
/* Widest laid-out line of the text Original name Text_GetStringWidth (the remaster's GrimFandango
   (Linux): aligned call in sputText_ChangeTextObjectL, sputText_GetTextObjectDimensionsL,
   sputText_MakeTextObjectL); was Text_MeasureWidth. */

int __cdecl Text_GetStringWidth(TextContext *ctx,char *text)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  FontData *font;
  int iVar2;
  uint uVar3;
  TextContext *pTVar4;
  TextContext *pTVar5;
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(TextContext *)(_frame + (0x50 - 0x30)))
  
  uVar3 = 0;
  pTVar4 = ctx;
  pTVar5 = &local_30;
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    pTVar5->pUnused = pTVar4->pUnused;
    pTVar4 = (TextContext *)&pTVar4->pClipRect;
    pTVar5 = (TextContext *)&pTVar5->pClipRect;
  }
  pvVar1 = ctx->pFont;
  local_34 = 0;
  if (pvVar1 == (void *)0x0) {
    (*g_pTextHS->pAssertFail)(s_hFont_004ed078,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x28d);
  }
  font = (FontData *)(*g_pTextHS->pHLock)(pvVar1);
  do {
    text = text_FindNextBreak(&local_30,font,text,(int *)&local_34,(uint *)0x0,1);
    if ((int)uVar3 <= (int)local_34) {
      uVar3 = local_34;
    }
  } while (text != (char *)0x0);
  (*g_pTextHS->pHUnlock)(pvVar1);
  return uVar3;
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
  FontData *font;
  int iVar2;
  TextContext *pTVar3;
  TextContext *pTVar4;
  #define local_30 (*(TextContext *)(_frame + (0x40 - 0x30)))
  
  pvVar1 = ctx->pFont;
  pTVar3 = ctx;
  pTVar4 = &local_30;
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    pTVar4->pUnused = pTVar3->pUnused;
    pTVar3 = (TextContext *)&pTVar3->pClipRect;
    pTVar4 = (TextContext *)&pTVar4->pClipRect;
  }
  iVar2 = 0;
  if (pvVar1 == (void *)0x0) {
    (*g_pTextHS->pAssertFail)(s_hFont_004ed078,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x2b0);
  }
  font = (FontData *)(*g_pTextHS->pHLock)(pvVar1);
  do {
    text = text_FindNextBreak(&local_30,font,text,(int *)0x0,(uint *)0x0,1);
    iVar2 = iVar2 + (*(int *)(*(int *)ctx->pFont + 4) * ctx->nScaleY + 0xffffU >> 0x10);
  } while (text != (char *)0x0);
  (*g_pTextHS->pHUnlock)(pvVar1);
  return iVar2;
}
#undef local_30


/* ---- 0x004aabb0  Text_DrawFormatted ---- */
/* Formats into a 1000-byte buffer and draws it with the default font */

uint __cdecl Text_DrawFormatted(TextContext *ctx,char *fmt,...)

{
  unsigned char _frame[0x400];  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  uint uVar2;
  void *font;
  #define local_3ec (*(char (*)[1004])(_frame + (0x400 - 0x3ec)))
  
  if (fmt == (char *)0x0) {
    return 0;
  }
  uVar2 = vsprintf((uint)local_3ec,(uint)fmt,(uint)&STACK0X(0x0000000c));
  pvVar1 = ctx->pFont;
  if (pvVar1 == (void *)0x0) {
    (*g_pTextHS->pAssertFail)(s_hFont_004ed078,s_C__grimsrc_libs_grimlib_Temp_Tex_004ed054,0x2fa);
  }
  font = (void *)(*g_pTextHS->pHLock)(pvVar1);
  Text_DrawString(ctx,font,local_3ec);
  (*g_pTextHS->pHUnlock)(pvVar1);
  return uVar2;
}
#undef local_3ec


/* ---- 0x004aac40  Text_WrapLines ---- */
/* Builds the default font from the packed glyph table at g_BuiltinFontData */

uint __cdecl Text_WrapLines(uint *defaultFont)

{
  unsigned char _frame[0x450] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  undefined2 *puVar8;
  uint uVar9;
  FontData *pFVar10;
  char *pcVar11;
  undefined4 *puVar12;
  uint local_444;
  #define local_43e (*(undefined1 *)(_frame + (0x450 - 0x43e)))
  #define local_43d (*(undefined1 *)(_frame + (0x450 - 0x43d)))
  #define local_43c (*(uint *)(_frame + (0x450 - 0x43c)))
  #define uStack_438 (*(uint *)(_frame + (0x450 - 0x438)))
  #define iStack_434 (*(int *)(_frame + (0x450 - 0x434)))
  FontData header;
  uint aGlyphOffsets [256];
  
  pFVar10 = &header;
  for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined4 *)pFVar10 = 0;
    pFVar10 = (FontData *)&pFVar10->field_0x4;
  }
  PIECE(header,4,4) = UINT_004eca00 >> 0x10 & 0xff;
  local_43e = 0;
  PIECE(header,8,4) = PIECE(header,4,4) - 1;
  uVar3 = UINT_004eca00 & 0xffff;
  local_43d = 0xff;
  PIECE(header,12,4) = 0;
  PIECE(header,16,4) = 1;
  header.nFirstChar = 0;
  header.nLastChar = uVar3;
  if (uVar3 != 0) {
    puVar7 = g_adwTextWrapTable;
    puVar4 = aGlyphOffsets;
    for (uVar6 = uVar3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar4 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  header.nGlyphOffset = uVar3 * 2 + 0x30;
  local_43c = uVar3 * 0x5c;
  iVar5 = header.nGlyphOffset + local_43c;
  header.nCharMapOffset = 0x30;
  header.nBitmapOffset = iVar5;
  if (uVar3 != 0) {
    puVar7 = aGlyphOffsets;
    uVar6 = uVar3;
    do {
      uVar9 = *puVar7;
      if (uVar9 != 0) {
        iVar5 = iVar5 + (uint)*(byte *)((int)&UINT_004eca00 + uVar9 + 1) *
                        (uint)*(byte *)((int)&UINT_004eca00 + uVar9);
      }
      puVar7 = puVar7 + 1;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
  uStack_438 = (*g_pTextHS->pHAlloc)(iVar5);
  if (uStack_438 != 0) {
    puVar4 = (uint *)(*g_pTextHS->pHLock)(uStack_438);
    pFVar10 = &header;
    puVar7 = puVar4;
    for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *(uint *)pFVar10;
      pFVar10 = (FontData *)&pFVar10->field_0x4;
      puVar7 = puVar7 + 1;
    }
    *puVar4 = uStack_438;
    puVar8 = (undefined2 *)(puVar4[9] + (int)puVar4);
    iVar5 = 0;
    if (uVar3 != 0) {
      do {
        *puVar8 = (short)iVar5;
        iVar5 = iVar5 + 1;
        puVar8 = puVar8 + 1;
      } while (iVar5 < (int)uVar3);
    }
    uVar6 = puVar4[10];
    puVar12 = (undefined4 *)(uVar6 + (int)puVar4);
    for (uVar9 = local_43c >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *puVar12 = 0;
      puVar12 = puVar12 + 1;
    }
    iVar5 = 0;
    for (uVar9 = local_43c & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined1 *)puVar12 = 0;
      puVar12 = (undefined4 *)((int)puVar12 + 1);
    }
    iStack_434 = puVar4[0xb] + (int)puVar4;
    if (uVar3 != 0) {
      local_444 = (uint)aGlyphOffsets;
      pcVar11 = (char *)((int)(uVar6 + (int)puVar4) + 6);
      local_43c = uVar3;
      do {
        iVar2 = *(int *)local_444;
        if (iVar2 != 0) {
          *(uint *)(pcVar11 + 6) = (uint)*(byte *)((int)&UINT_004eca00 + iVar2);
          *(uint *)(pcVar11 + 10) = (uint)*(byte *)((int)&UINT_004eca00 + iVar2 + 1);
          cVar1 = *(char *)((int)&UINT_004eca00 + iVar2 + 2);
          pcVar11[-1] = cVar1;
          pcVar11[-2] = pcVar11[6] + cVar1;
          cVar1 = *(char *)((int)&UINT_004eca00 + iVar2 + 3);
          uVar3 = puVar4[2];
          pcVar11[0xe] = '\x01';
          pcVar11[0xf] = '\0';
          pcVar11[0x10] = '\0';
          pcVar11[0x11] = '\0';
          *pcVar11 = cVar1 - (char)uVar3;
          *(int *)(pcVar11 + -6) = iVar5;
          *(int *)(pcVar11 + 2) = iVar5 + iStack_434;
          uVar3 = (int)*pcVar11;
          if ((int)puVar4[5] < (int)*pcVar11) {
            uVar3 = puVar4[5];
          }
          puVar4[5] = uVar3;
          uVar3 = *(int *)(pcVar11 + 10) + (int)*pcVar11;
          if ((uint)(*(int *)(pcVar11 + 10) + (int)*pcVar11) < puVar4[6]) {
            uVar3 = puVar4[6];
          }
          puVar4[6] = uVar3;
          Text_CopyRunes((byte *)((int)g_adwTextWrapTable + iVar2),(undefined4 *)(pcVar11 + 2),1,
                         (int)&local_43e);
          iVar5 = iVar5 + *(int *)(pcVar11 + 6) * *(int *)(pcVar11 + 10);
        }
        local_444 = local_444 + 4;
        pcVar11 = pcVar11 + 0x5c;
        local_43c = local_43c - 1;
      } while (local_43c != 0);
    }
    uVar3 = uStack_438;
    (*g_pTextHS->pHUnlock)(uStack_438);
    *defaultFont = uVar3;
    return 0;
  }
  *defaultFont = 0;
  return 1;
}
#undef iStack_434
#undef local_43c
#undef local_43d
#undef local_43e
#undef uStack_438


/* ---- 0x004aae90  Text_CopyRunes ---- */
void __cdecl Text_CopyRunes(byte *dst,undefined4 *src,int count,int stride)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  uint local_8;
  uint local_4;
  
  puVar1 = src;
  puVar6 = (undefined1 *)*src;
  iVar3 = -1;
  src = (undefined4 *)0x0;
  pbVar4 = dst;
  if (puVar1[2] != 0) {
    do {
      uVar2 = 0;
      puVar5 = puVar6;
      if (puVar1[1] != 0) {
        do {
          if (iVar3 < 0) {
            pbVar4 = (byte *)(uint)*dst;
            dst = dst + 1;
            iVar3 = 8 - count;
          }
          puVar6 = puVar5 + 1;
          *puVar5 = *(undefined1 *)
                     (((int)pbVar4 >> ((byte)iVar3 & 0x1f) & 0xff >> ((byte)(8 - count) & 0x1f)) +
                     stride);
          iVar3 = iVar3 - count;
          uVar2 = uVar2 + 1;
          puVar5 = puVar6;
        } while (uVar2 < (uint)puVar1[1]);
      }
      src = (undefined4 *)((int)src + 1);
    } while (src < (undefined4 *)puVar1[2]);
  }
  return;
}

/* ---- 0x004aaf30  Text_BuildLineTable ---- */
/* Reads a .LAF font: header (data size, ..., first/last char), the char index table, 0x5c-byte
   glyph records {dataOffset, advance, xoff, yoff, ?, dataPtr, width, height} and the glyph bitmaps
    */

uint __cdecl Text_BuildLineTable(uint text,int *outFont)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  char *pcVar7;
  int *piVar8;
  undefined2 uStack_42;
  int local_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  #define aiStack_30 (*(int (*)[4])(_frame + (0x40 - 0x30)))
  #define iStack_20 (*(int *)(_frame + (0x40 - 0x20)))
  #define iStack_14 (*(int *)(_frame + (0x40 - 0x14)))
  #define iStack_10 (*(int *)(_frame + (0x40 - 0x10)))
  
  uVar1 = text;
  (*g_pTextHS->pFread)(text,&local_40,4);
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
        (*g_pTextHS->pFread)(uVar1,&text,1);
        pcVar7[-2] = (char)text;
        (*g_pTextHS->pFread)(uVar1,&text,1);
        pcVar7[-1] = (char)text;
        (*g_pTextHS->pFread)(uVar1,&text,1);
        *pcVar7 = (char)text;
        (*g_pTextHS->pFread)(uVar1,&text,1);
        pcVar7[1] = (char)text;
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
    *outFont = iVar5;
    return 0;
  }
  *outFont = 0;
  return 1;
}
#undef aiStack_30
#undef iStack_10
#undef iStack_14
#undef iStack_20


/* ---- 0x004ab210  text_FindNextBreak ---- */
/* Advances through the string computing glyph positions for the given width (ctx at +0x208)
   Original name text_FindNextBreak (the remaster's GrimFandango (Linux): aligned call in
   Text_GetStringHeight, Text_GetStringWidth); was Text_LayoutString. */

char * __cdecl
text_FindNextBreak(TextContext *context,FontData *font,char *text,int *outWidth,uint *outBreak,
                  int maxWidth)

{
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
  TextContext *pTVar6;
  int iVar7;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  int ch;
  
  local_c = (uint)text;
  ctx = context;
  uVar1 = context->dwFlags;
  iVar7 = *context->pClipRect;
  local_10 = context->nX - iVar7;
  uVar4 = (context->pClipRect[2] + iVar7) - context->nX;
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
  iVar7 = 0;
  uVar4 = 0;
  local_14 = 0;
  context = (TextContext *)0x0;
  local_18 = 0;
  local_1c = 0;
  cVar3 = Text_NextChar(&text);
  ch = ((uint)(byte)(cVar3));
  pTVar6 = context;
  do {
    context = pTVar6;
    pcVar2 = text;
    if (ch == 0) {
LAB_004ab425:
      text = pcVar2;
      if (ch == 0) {
        pTVar6 = (TextContext *)((int)&context->pUnused + uVar4 + local_14);
        if (((int)local_10 < (int)pTVar6) && ((uVar1 & 4) != 0)) {
          text = (char *)local_c;
          if (local_1c == 0) {
            local_1c = iVar7 + local_18;
            text = (char *)0x0;
            context = pTVar6;
          }
        }
        else {
          local_1c = local_1c + iVar7 + local_18;
          text = (char *)0x0;
          context = pTVar6;
        }
      }
      if (maxWidth != 0) {
        if (text == (char *)0x0) {
          if ((uVar1 & 1) == 0) {
            pTVar6 = context;
            if ((uVar1 & 2) != 0) {
              pTVar6 = (TextContext *)-(int)context;
            }
            ctx->nX = (int)&pTVar6->pUnused + ctx->nX;
          }
          else {
            ctx->nX = (int)context / 2 + ctx->nX;
          }
        }
        else {
          ctx->nY = (ctx->nScaleY * *(int *)(*(int *)ctx->pFont + 4) + 0xffffU >> 0x10) + ctx->nY;
        }
      }
      if (outBreak != (uint *)0x0) {
        *outBreak = local_1c;
      }
      if (outWidth != (int *)0x0) {
        *outWidth = (int)context;
      }
      return text;
    }
    if (((ch == 0x20) || (ch == 0xfe)) && ((uVar1 & 4) != 0)) {
      context = (TextContext *)((int)&pTVar6->pUnused + uVar4 + local_14);
      if ((int)local_10 < (int)context) {
        context = pTVar6;
        pcVar2 = (char *)local_c;
        if (local_1c == 0) {
          local_1c = iVar7 + local_18;
          context = (TextContext *)((int)&pTVar6->pUnused + uVar4 + local_14);
          pcVar2 = text;
        }
      }
      else {
        local_1c = local_1c + iVar7 + local_18;
        uVar4 = Font_GlyphAdvance(ctx,font,ch);
        local_14 = 0;
        local_18 = 0;
        iVar7 = 1;
        local_c = (uint)text;
        cVar3 = Text_NextChar(&text);
        ch = ((uint)(byte)(cVar3));
        if (ch != 0) {
          do {
            if ((ch != 0x20) && (ch != 0xfe)) break;
            uVar5 = Font_GlyphAdvance(ctx,font,ch);
            uVar4 = uVar4 + uVar5;
            iVar7 = iVar7 + 1;
            local_c = (uint)text;
            cVar3 = Text_NextChar(&text);
            ch = ((uint)(byte)(cVar3));
          } while (ch != 0);
          if (ch != 0) goto LAB_004ab344;
        }
        local_1c = local_1c + iVar7;
        context = (TextContext *)((int)&context->pUnused + uVar4);
        pcVar2 = text;
      }
      goto LAB_004ab425;
    }
LAB_004ab344:
    if ((ch == 0xd) || (ch == 10)) {
      pTVar6 = (TextContext *)((int)&context->pUnused + uVar4 + local_14);
      if (((int)local_10 < (int)pTVar6) && ((uVar1 & 4) != 0)) {
        text = (char *)local_c;
        pcVar2 = text;
      }
      else {
        local_1c = local_1c + iVar7 + local_18;
        context = pTVar6;
        pcVar2 = text;
        if ((ch == 0xd) && (*text == '\n')) {
          pcVar2 = text + 1;
        }
      }
      goto LAB_004ab425;
    }
    uVar5 = Font_GlyphAdvance(ctx,font,ch);
    local_14 = local_14 + uVar5;
    local_18 = local_18 + 1;
    cVar3 = Text_NextChar(&text);
    ch = ((uint)(byte)(cVar3));
    pTVar6 = context;
  } while( true );
}

/* ---- 0x004ab510  Font_GlyphAdvance ---- */
uint __cdecl Font_GlyphAdvance(TextContext *ctx,FontData *font,int ch)

{
  int iVar1;
  uint uVar2;
  
  if (font->nLastChar < ch) {
    iVar1 = 0;
  }
  else {
    iVar1 = font->nGlyphOffset +
            (uint)*(ushort *)(font->nCharMapOffset + (ch - font->nFirstChar) * 2 + (int)font) * 0x5c
            + (int)font;
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
uint __cdecl Font_GlyphWidth(int ctx,int font,uint ch)

{
  int iVar1;
  
  if (*(int *)(font + 0x20) < (int)(ch & 0xff)) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(font + 0x28) +
            (uint)*(ushort *)
                   (*(int *)(font + 0x24) + ((ch & 0xff) - *(int *)(font + 0x1c)) * 2 + font) * 0x5c
            + font;
  }
  if (iVar1 != 0) {
    return (int)*(char *)(iVar1 + 4) * *(int *)(ctx + 0x20) + 0xffffU >> 0x10;
  }
  return 0;
}

/* ---- 0x004ab5d0  Text_DrawString ---- */
void __cdecl Text_DrawString(TextContext *ctx,void *font,char *text)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  TextContext *context;
  char cVar2;
  int iVar3;
  undefined3 extraout_var;
  TextContext *pTVar4;
  int ch;
  uint uVar5;
  uint local_18;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  context = ctx;
  ch = 0;
  local_10 = ctx->dwFlags;
  g_bLookup = (undefined1)ctx->dwBgColor;
  ctx->dwFlags = local_10 & 0xfffffff7;
  DAT_008d0900 = (undefined1)ctx->dwFxColor;
  DAT_008d097f = (undefined1)ctx->dwFgColor;
  if (text == (char *)0x0) {
LAB_004ab6fb:
    context->dwFlags = local_10;
    return;
  }
  uVar5 = local_10 & 1;
  local_8 = uVar5;
  do {
    local_c = (uint)text_FindNextBreak(context,font,text,(int *)&ctx,&local_14,0);
    iVar1 = context->nX;
    local_4 = context->nY;
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
    context->nX = iVar3;
    local_18 = 0;
    iVar3 = ch;
    if (0 < (int)local_14) {
      do {
        cVar2 = Text_NextChar(&text);
        ch = ((uint)(byte)(cVar2));
        if ((iVar3 != 10) || (ch != 0xd)) {
          Text_DrawChar(context,font,ch);
        }
        local_18 = local_18 + 1;
        iVar3 = ch;
        uVar5 = local_8;
      } while ((int)local_18 < (int)local_14);
    }
    if (local_c == 0) goto LAB_004ab6fb;
    context->nX = iVar1;
    context->nY = (*(int *)(*(int *)context->pFont + 4) * context->nScaleY + 0xffffU >> 0x10) +
                  local_4;
    text = (char *)local_c;
  } while( true );
}
#undef local_10
#undef local_14
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004ab710  Text_DrawChar ---- */
/* Picks the glyph blitter: 16-bit vs paletted 8-bit (flag 8), clipped vs unclipped; scaled glyphs
   are not implemented (Lua_Stub) */

void __cdecl Text_DrawChar(TextContext *ctx,FontData *font,int ch)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  TextContext *glyph;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int *fmt;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  glyph = ctx;
  local_c = 0;
  iVar1 = ctx->nY;
  piVar2 = ctx->pClipRect;
  iVar3 = ctx->nX;
  iVar4 = ctx->nScaleX;
  iVar5 = ctx->nScaleY;
  if (font->nLastChar < ch) {
    fmt = (int *)0x0;
  }
  else {
    fmt = (int *)(font->nGlyphOffset +
                  (uint)*(ushort *)(font->nCharMapOffset + (ch - font->nFirstChar) * 2 + (int)font)
                  * 0x5c + (int)font);
  }
  if (fmt != (int *)0x0) {
    fmt[2] = (int)(&font->field_0x0 + *fmt + font->nBitmapOffset);
    if ((iVar4 == 0x10000) && (iVar5 == 0x10000)) {
      uVar8 = (uint)*(char *)((int)fmt + 5);
      uVar6 = fmt[3];
      uVar7 = fmt[4];
      uVar9 = (uint)*(char *)((int)fmt + 6);
    }
    else {
      uVar8 = *(char *)((int)fmt + 5) * iVar4 + 0xffffU >> 0x10;
      uVar9 = *(char *)((int)fmt + 6) * iVar5 + 0xffffU >> 0x10;
      uVar6 = fmt[3] * iVar4 + 0xffffU >> 0x10;
      uVar7 = fmt[4] * iVar5 + 0xffffU >> 0x10;
      local_c = 1;
    }
    local_14 = iVar1 + uVar9;
    ctx = (TextContext *)(iVar3 + uVar8);
    if (((((int)ctx < *piVar2) || ((int)local_14 < piVar2[1])) ||
        (piVar2[2] + *piVar2 <= (int)((int)&ctx->pUnused + uVar6))) ||
       (piVar2[3] + piVar2[1] <= (int)(uVar7 + local_14))) {
      local_c = local_c | 2;
    }
    if ((glyph->dwFlags & 8) != 0) {
      local_c = local_c | 4;
    }
    switch(local_c) {
    case 0:
      Glyph_Blit16((int)fmt,(uint)font,(int *)glyph);
      break;
    case 1:
    case 3:
      Lua_Stub((char *)fmt,font,glyph);
      break;
    case 2:
      Glyph_Blit16Clipped((int)fmt,(uint)font,(int *)glyph);
      break;
    case 4:
      Glyph_Blit8((int)fmt,(int)font,(int *)glyph);
      break;
    case 5:
    case 7:
      Lua_Stub((char *)fmt,font,glyph);
      break;
    case 6:
      Glyph_Blit8Clipped((int)fmt,(int)font,(int *)glyph);
    }
    glyph->nX = glyph->nX + ((char)fmt[1] * iVar4 + 0xffffU >> 0x10);
  }
  return;
}
