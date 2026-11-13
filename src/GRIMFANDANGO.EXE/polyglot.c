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

void PolyglotConfigure(undefined *param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined *puVar4;
  undefined1 *puVar5;
  
  g_pTabFilename = param_1;
  iVar1 = (*g_pPolyglot_HS->pFopen)(param_1,&DAT_004ddb18);
  if (iVar1 != 0) {
    (*g_pPolyglot_HS->pFread)(iVar1,&param_1,4);
    (*g_pPolyglot_HS->pFseek)(iVar1,0,2);
    iVar2 = (*g_pPolyglot_HS->pFtell)(iVar1);
    (*g_pPolyglot_HS->pFseek)(iVar1,0,0);
    g_pLanguageMalloc =
         (char *)(*g_pPolyglot_HS->pAlloc)(iVar2,s_C__grimsrc_libs_grimlib_Engine_p_004e8038,0x8f);
    (*g_pPolyglot_HS->pFread)(iVar1,g_pLanguageMalloc,iVar2);
    (*g_pPolyglot_HS->pFclose)(iVar1);
    pcVar3 = g_pLanguageMalloc;
    if (param_1 == (undefined *)0x454e4352) {
      iVar2 = iVar2 + -4;
      iVar1 = 0;
      if (0 < iVar2) {
        do {
          g_pLanguageMalloc[iVar1] = g_pLanguageMalloc[iVar1 + 4] ^ 0xdd;
          iVar1 = iVar1 + 1;
          pcVar3 = g_pLanguageMalloc;
        } while (iVar1 < iVar2);
      }
    }
    do {
      puVar4 = Str_FindChar(pcVar3,0xd);
      g_dwLineCount = g_dwLineCount + 1;
      pcVar3 = puVar4 + 2;
    } while (puVar4 + 2 < g_pLanguageMalloc + iVar2 + -1);
    g_dwLanguageLine =
         (*g_pPolyglot_HS->pAlloc)
                   (g_dwLineCount * 4,s_C__grimsrc_libs_grimlib_Engine_p_004e8038,0xa2);
    iVar1 = 0;
    pcVar3 = g_pLanguageMalloc;
    do {
      puVar4 = Str_FindChar(pcVar3,0xd);
      *puVar4 = 0;
      puVar5 = (undefined1 *)strchr(pcVar3,9);
      if (puVar5 != (undefined1 *)0x0) {
        *puVar5 = 0;
      }
      _strupr(pcVar3);
      *(char **)(g_dwLanguageLine + iVar1) = pcVar3;
      pcVar3 = puVar4 + 2;
      iVar1 = iVar1 + 4;
    } while (pcVar3 < g_pLanguageMalloc + iVar2 + -1);
    qsort(g_dwLanguageLine,g_dwLineCount,4,Str_ComparePtrs);
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
  int iVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  #define local_104 (*(uint *)(_frame + (0x120 - 0x104)))
  #define local_100 (*(char (*)[256])(_frame + (0x120 - 0x100)))
  
  local_104 = (uint)local_100;
  if (textId == (char *)0x0) {
    return (char *)0x0;
  }
  if ((*textId != '\0') && (*textId == '/')) {
    iVar2 = strchr(textId + 1,0x2f);
    if (g_pLanguageMalloc == (char *)0x0) {
      return (char *)(iVar2 + 1);
    }
    uVar5 = 0xffffffff;
    pcVar7 = textId + 1;
    do {
      pcVar8 = pcVar7;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar7 = pcVar8 + -uVar5;
    pcVar8 = local_100;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
    puVar3 = (undefined1 *)strchr(local_100,0x2f);
    if (puVar3 != (undefined1 *)0x0) {
      *puVar3 = 0;
    }
    _strupr(local_100);
    puVar4 = (undefined4 *)bsearch(&local_104,g_dwLanguageLine,g_dwLineCount,4,Str_ComparePtrs);
    if (puVar4 == (undefined4 *)0x0) {
      return (char *)(iVar2 + 1);
    }
    pcVar7 = (char *)*puVar4;
    uVar5 = 0xffffffff;
    pcVar8 = pcVar7;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar1 != '\0');
    if (pcVar7[~uVar5] != '\0') {
      return pcVar7 + ~uVar5;
    }
  }
  return textId;
}
#undef local_100
#undef local_104

