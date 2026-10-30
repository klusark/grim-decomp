/* GRIMFANDANGO.EXE :: polyglot.c
 * functions 0x00483720 .. 0x004838e0 (2 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00483720  Polyglot_LoadTable ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* polyglot.c: loads the language table (text id -> translated string) */

void Polyglot_LoadTable(undefined *param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined *puVar4;
  undefined1 *puVar5;
  
  PTR_s_language_tab_004e8024 = param_1;
  iVar1 = (*g_pSvcIMuseModule->pFopen)(param_1,&DAT_004ddb18);
  if (iVar1 != 0) {
    (*g_pSvcIMuseModule->pFread)(iVar1,&param_1,4);
    (*g_pSvcIMuseModule->pFseek)(iVar1,0,2);
    iVar2 = (*g_pSvcIMuseModule->pFtell)(iVar1);
    (*g_pSvcIMuseModule->pFseek)(iVar1,0,0);
    g_pPolyglotText =
         (char *)(*g_pSvcIMuseModule->pAlloc)
                           (iVar2,s_C__grimsrc_libs_grimlib_Engine_p_004e8038,0x8f);
    (*g_pSvcIMuseModule->pFread)(iVar1,g_pPolyglotText,iVar2);
    (*g_pSvcIMuseModule->pFclose)(iVar1);
    pcVar3 = g_pPolyglotText;
    if (param_1 == (undefined *)0x454e4352) {
      iVar2 = iVar2 + -4;
      iVar1 = 0;
      if (0 < iVar2) {
        do {
          g_pPolyglotText[iVar1] = g_pPolyglotText[iVar1 + 4] ^ 0xdd;
          iVar1 = iVar1 + 1;
          pcVar3 = g_pPolyglotText;
        } while (iVar1 < iVar2);
      }
    }
    do {
      puVar4 = Str_FindChar(pcVar3,0xd);
      UINT_008a8ca4 = UINT_008a8ca4 + 1;
      pcVar3 = puVar4 + 2;
    } while (puVar4 + 2 < g_pPolyglotText + iVar2 + -1);
    UINT_008a8c9c =
         (*g_pSvcIMuseModule->pAlloc)
                   (UINT_008a8ca4 * 4,s_C__grimsrc_libs_grimlib_Engine_p_004e8038,0xa2);
    iVar1 = 0;
    pcVar3 = g_pPolyglotText;
    do {
      puVar4 = Str_FindChar(pcVar3,0xd);
      *puVar4 = 0;
      puVar5 = (undefined1 *)strchr(pcVar3,9);
      if (puVar5 != (undefined1 *)0x0) {
        *puVar5 = 0;
      }
      _strupr(pcVar3);
      *(char **)(UINT_008a8c9c + iVar1) = pcVar3;
      pcVar3 = puVar4 + 2;
      iVar1 = iVar1 + 4;
    } while (pcVar3 < g_pPolyglotText + iVar2 + -1);
    qsort(UINT_008a8c9c,UINT_008a8ca4,4,FUN_00403ae0);
  }
  return;
}
#endif


/* ---- 0x004838e0  Polyglot_Lookup ---- */
/* Binary search of the language table for a /xxxx/ text id */

char * __cdecl Polyglot_Lookup(char *textId)

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
    if (g_pPolyglotText == (char *)0x0) {
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
    puVar4 = (undefined4 *)bsearch(&local_104,UINT_008a8c9c,UINT_008a8ca4,4,FUN_00403ae0);
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

