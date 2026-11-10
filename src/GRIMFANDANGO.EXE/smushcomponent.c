/* GRIMFANDANGO.EXE :: smushcomponent.c
 * functions 0x00498140 .. 0x00498190 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00498140  SmushComponent_Destroy ---- */
/* Costume tag handler for 'Smush Movie' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 2, frees the key data. */

undefined4 SmushComponent_Destroy(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}

/* ---- 0x00498160  SmushChanger ---- */
/* Costume tag handler for 'Smush Movie' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, blits the current movie frame to the back buffer
   when the key is 0. Original name SmushChanger (the remaster's GrimFandango (Linux): the only
   unmatched caller of Engine_BlitToBackBuffer; 1 matched neighbours agree, 0 disagree); was
   SmushComponent_OnKey. */

void SmushChanger(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  if (param_4 == 0) {
    grimlib_PlayMovie(param_2,0,0,0xffffffff,0xffffffff);
  }
  return;
}

/* ---- 0x00498190  SmushRequester ---- */
/* Costume tag handler for 'Smush Movie' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, asks for a .snm file ('Select smush file') in the
   editor and stores its name. Original name SmushRequester (the remaster's GrimFandango (Linux):
   strings: 'Select smush file...' | 'Smush files (*.snm)'); was SmushComponent_Create. */

int SmushRequester(uint param_1,int param_2,int param_3,int param_4,char *param_5)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  
  pcVar4 = param_5;
  if (param_5 == (char *)0x0) {
    if (DAT_008caab8 != '\0') {
      Plat_SetDialogDirectory(&DAT_008caab8);
    }
    iVar2 = Plat_OpenFileDialog(s_Select_smush_file____004ea7ec,s_Smush_files____snm__004ea804);
    if (iVar2 == 0) {
      return false;
    }
    uVar3 = ((code *)Plat_GetDialogFileName)(0x7f);
    ((code *)strncpy)(&DAT_008caab8,uVar3);
    DAT_008cab37 = 0;
    pcVar4 = Str_Basename(g_szDialogFileName);
  }
  uVar6 = 0xffffffff;
  pcVar8 = pcVar4;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  pcVar5 = (char *)(*g_pSvcCostume->pAlloc)
                             (~uVar6,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xfe2);
  uVar6 = 0xffffffff;
  pcVar8 = pcVar4;
  do {
    pcVar9 = pcVar8;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar9 = pcVar8 + 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar9;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar8 = pcVar9 + -uVar6;
  pcVar9 = pcVar5;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar9 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar9 = pcVar9 + 1;
  }
  if (param_5 != (char *)0x0) {
    pcVar4 = param_5;
  }
  iVar2 = Cos_RegisterComponent(param_1,(int)pcVar4,(int)pcVar5,param_2,param_3,param_4,IMG_ADDR(0x004ea040));
  return iVar2 != 0;
}
