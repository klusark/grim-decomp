/* GRIMFANDANGO.EXE :: polyglot.c
 * functions 0x00483720 .. 0x004838e0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00483720  PolyglotConfigure ---- */
/* polyglot.c: loads the language table (text id -> translated string) Original name
   PolyglotConfigure (the remaster's GrimFandango (Linux): the table load Main_Startup calls after
   PolyglotInitialize, same body (reads the .tab file through the polyglot pHS)); was
   Polyglot_LoadTable. */

void __cdecl PolyglotConfigure(undefined *filename)

{
  int iVar1;
  int iVar2;
  char *s;
  undefined *puVar3;
  uint *puVar4;
  uint *s_00;
  
  g_pTabFilename = filename;
  iVar1 = (*g_pPolyglot_HS->pFopen)(filename,s_rb_004ddb18);
  if (iVar1 != 0) {
    (*g_pPolyglot_HS->pFread)(iVar1,&filename,4);
    (*g_pPolyglot_HS->pFseek)(iVar1,0,2);
    iVar2 = (*g_pPolyglot_HS->pFtell)(iVar1);
    (*g_pPolyglot_HS->pFseek)(iVar1,0,0);
    g_pLanguageMalloc =
         (char *)(*g_pPolyglot_HS->pAlloc)(iVar2,s_C__grimsrc_libs_grimlib_Engine_p_004e8038,0x8f);
    (*g_pPolyglot_HS->pFread)(iVar1,g_pLanguageMalloc,iVar2);
    (*g_pPolyglot_HS->pFclose)(iVar1);
    s = g_pLanguageMalloc;
    if (filename == (undefined *)0x454e4352) {
      iVar2 = iVar2 + -4;
      iVar1 = 0;
      if (0 < iVar2) {
        do {
          g_pLanguageMalloc[iVar1] = g_pLanguageMalloc[iVar1 + 4] ^ 0xdd;
          iVar1 = iVar1 + 1;
          s = g_pLanguageMalloc;
        } while (iVar1 < iVar2);
      }
    }
    do {
      puVar3 = Str_FindChar(s,0xd);
      g_dwLineCount = g_dwLineCount + 1;
      s = puVar3 + 2;
    } while (puVar3 + 2 < g_pLanguageMalloc + iVar2 + -1);
    g_dwLanguageLine =
         (*g_pPolyglot_HS->pAlloc)
                   (g_dwLineCount * 4,s_C__grimsrc_libs_grimlib_Engine_p_004e8038,0xa2);
    iVar1 = 0;
    s_00 = (uint *)g_pLanguageMalloc;
    do {
      puVar3 = Str_FindChar((char *)s_00,0xd);
      *puVar3 = 0;
      puVar4 = strchr(s_00,'\t');
      if (puVar4 != (uint *)0x0) {
        *(undefined1 *)puVar4 = 0;
      }
      _strupr((char *)s_00);
      *(uint **)(g_dwLanguageLine + iVar1) = s_00;
      s_00 = (uint *)(puVar3 + 2);
      iVar1 = iVar1 + 4;
    } while (s_00 < g_pLanguageMalloc + iVar2 + -1);
    qsort((void *)g_dwLanguageLine,g_dwLineCount,4,Str_ComparePtrs);
  }
  return;
}

/* ---- 0x004838e0  PolyglotGetString ---- */
/* Binary search of the language table for a /xxxx/ text id Original name PolyglotGetString (the
   remaster's GrimFandango (Linux): aligned call in sputText_ExtractSayLineData); was
   Polyglot_Lookup. */

char * __cdecl PolyglotGetString(char *textId)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  char *pcVar2;
  uint *puVar3;
  uint *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  char *pcVar9;
  #define local_104 (*(uint *)(_frame + (0x120 - 0x104)))
  #define local_100 (*(uint (*)[64])(_frame + (0x120 - 0x100)))
  
  local_104 = (uint)local_100;
  if (textId == (char *)0x0) {
    return (char *)0x0;
  }
  if ((*textId != '\0') && (*textId == '/')) {
    puVar3 = strchr((uint *)(textId + 1),'/');
    if (g_pLanguageMalloc == (char *)0x0) {
      return (char *)((int)puVar3 + 1);
    }
    uVar6 = 0xffffffff;
    puVar4 = (uint *)(textId + 1);
    do {
      puVar8 = puVar4;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      puVar8 = (uint *)((int)puVar4 + 1);
      uVar7 = *puVar4;
      puVar4 = puVar8;
    } while ((char)uVar7 != '\0');
    uVar6 = ~uVar6;
    puVar4 = (uint *)((int)puVar8 - uVar6);
    puVar8 = local_100;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar8 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar8 = puVar8 + 1;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(char *)puVar8 = (char)*puVar4;
      puVar4 = (uint *)((int)puVar4 + 1);
      puVar8 = (uint *)((int)puVar8 + 1);
    }
    puVar4 = strchr(local_100,'/');
    if (puVar4 != (uint *)0x0) {
      *(undefined1 *)puVar4 = 0;
    }
    _strupr((char *)local_100);
    puVar5 = bsearch(&local_104,(void *)g_dwLanguageLine,g_dwLineCount,4,Str_ComparePtrs);
    if (puVar5 == (undefined4 *)0x0) {
      return (char *)((int)puVar3 + 1);
    }
    pcVar2 = (char *)*puVar5;
    uVar6 = 0xffffffff;
    pcVar9 = pcVar2;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar1 != '\0');
    if (pcVar2[~uVar6] != '\0') {
      return pcVar2 + ~uVar6;
    }
  }
  return textId;
}
#undef local_100
#undef local_104



/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char grim_def_DAT_004e8028[] __asm__("_DAT_004e8028");
extern unsigned int grim_def_g_dwLineCount __asm__("_g_dwLineCount");
extern void *grim_def_g_pTabFilename __asm__("_g_pTabFilename");
extern char grim_def_s_C__grimsrc_libs_grimlib_Engine_p_004e8038[44] __asm__("_s_C__grimsrc_libs_grimlib_Engine_p_004e8038");
static unsigned char grim_anchor_004e8024[0] __attribute__((section(".data$grim_004e8024"), aligned(16), used));
static unsigned char grim_pad_004e8024[4] __attribute__((section(".data$grim_004e8024_"), aligned(4), used));
/* 0x004e8024, 4 bytes */ GRIM_DATA("004e8024z") void *grim_def_g_pTabFilename __asm__("_g_pTabFilename") = (void *)&grim_def_DAT_004e8028;
/* 0x004e8038, 44 bytes */ GRIM_DATA("004e8038") char grim_def_s_C__grimsrc_libs_grimlib_Engine_p_004e8038[44] __asm__("_s_C__grimsrc_libs_grimlib_Engine_p_004e8038") = "C:\\grimsrc\\libs\\grimlib\\Engine\\polyglot.c";
static unsigned char grim_anchor_008a8ca4[0] __attribute__((section(".data$grim_008a8ca4"), aligned(16), used));
static unsigned char grim_pad_008a8ca4[4] __attribute__((section(".data$grim_008a8ca4_"), aligned(4), used));
/* 0x008a8ca4, 4 bytes */ GRIM_DATA("008a8ca4z") unsigned int grim_def_g_dwLineCount __asm__("_g_dwLineCount") = 0x0;
