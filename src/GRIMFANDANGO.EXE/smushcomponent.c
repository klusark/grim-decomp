/* GRIMFANDANGO.EXE :: smushcomponent.c
 * functions 0x00498140 .. 0x00498190 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00498140  SmushFreer ---- */
/* Costume tag handler for 'Smush Movie' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 2, frees the key data. Original name SmushFreer (the
   remaster's GrimFandango (Linux): the same handler slot (freer) of the same costume tag
   registration in sputCostume_Startup); was SmushComponent_Destroy. */

uint __cdecl SmushFreer(uint param_1,uint param_2,uint param_3)

{
  (*g_pSputCosHS->pFree)(param_3);
  return 1;
}

/* ---- 0x00498160  SmushChanger ---- */
/* Costume tag handler for 'Smush Movie' (registered by sputCostume_Startup through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, blits the current movie frame to the back buffer
   when the key is 0. Original name SmushChanger (the remaster's GrimFandango (Linux): the only
   unmatched caller of Engine_BlitToBackBuffer; 1 matched neighbours agree, 0 disagree); was
   SmushComponent_OnKey. */

void __cdecl SmushChanger(uint param_1,uint param_2,uint param_3,int param_4)

{
  if (param_4 == 0) {
    grimlib_PlayMovie(param_2,0,0,0xffffffff,0xffffffff);
  }
  return;
}

/* ---- 0x00498190  SmushRequester ---- */
/* Costume tag handler for 'Smush Movie' (registered by sputCostume_Startup through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, asks for a .snm file ('Select smush file') in the
   editor and stores its name. Original name SmushRequester (the remaster's GrimFandango (Linux):
   strings: 'Select smush file...' | 'Smush files (*.snm)'); was SmushComponent_Create. */

int __cdecl SmushRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5)

{
  char cVar1;
  int iVar2;
  uint *puVar3;
  char *pcVar4;
  char *pcVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  uint uVar9;
  
  pcVar4 = param_5;
  if (param_5 == (char *)0x0) {
    if (g_bSmushPath != '\0') {
      grimPlat_SetDefaultOpenPath(((unsigned)(uintptr_t)&g_bSmushPath));
    }
    iVar2 = grimPlat_OpenFileRequest(s_Select_smush_file____004ea7ec,s_Smush_files____snm__004ea804)
    ;
    if (iVar2 == 0) {
      return 0;
    }
    uVar9 = 0x7f;
    puVar3 = (uint *)grimPlat_GetDefaultOpenPath();
    strncpy((uint *)&g_bSmushPath,puVar3,uVar9);
    DAT_008cab37 = 0;
    pcVar4 = stdFnames_FindMedName(g_szGrimlib_aFilename);
  }
  uVar9 = 0xffffffff;
  pcVar7 = pcVar4;
  do {
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  pcVar5 = (char *)(*g_pSputCosHS->pAlloc)(~uVar9,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xfe2)
  ;
  uVar9 = 0xffffffff;
  pcVar7 = pcVar4;
  do {
    pcVar8 = pcVar7;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  uVar9 = ~uVar9;
  pcVar7 = pcVar8 + -uVar9;
  pcVar8 = pcVar5;
  for (uVar6 = uVar9 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  if (param_5 != (char *)0x0) {
    pcVar4 = param_5;
  }
  iVar2 = Cos_RegisterComponent(param_1,(int)pcVar4,(int)pcVar5,param_2,param_3,param_4,((unsigned)(uintptr_t)&DAT_004ea040));
  return (uint)(iVar2 != 0);
}
