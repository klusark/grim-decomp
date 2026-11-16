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

uint __cdecl SmushFreer(uint tag,uint inst,uint data)

{
  (*g_pSputCosHS->pFree)(data);
  return 1;
}

/* ---- 0x00498160  SmushChanger ---- */
/* Costume tag handler for 'Smush Movie' (registered by sputCostume_Startup through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, blits the current movie frame to the back buffer
   when the key is 0. Original name SmushChanger (the remaster's GrimFandango (Linux): the only
   unmatched caller of Engine_BlitToBackBuffer; 1 matched neighbours agree, 0 disagree); was
   SmushComponent_OnKey. */

void __cdecl SmushChanger(uint cosInst,uint name,uint tag,int loop)

{
  if (loop == 0) {
    grimlib_PlayMovie(name,0,0,0xffffffff,0xffffffff);
  }
  return;
}

/* ---- 0x00498190  SmushRequester ---- */
/* Costume tag handler for 'Smush Movie' (registered by sputCostume_Startup through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, asks for a .snm file ('Select smush file') in the
   editor and stores its name. Original name SmushRequester (the remaster's GrimFandango (Linux):
   strings: 'Select smush file...' | 'Smush files (*.snm)'); was SmushComponent_Create. */

int __cdecl SmushRequester(uint cosInst,int tag,int parent,int type,char *name)

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
  
  pcVar4 = name;
  if (name == (char *)0x0) {
    if (g_bSmushPath[0] != '\0') {
      grimPlat_SetDefaultOpenPath(((unsigned)(uintptr_t)&g_bSmushPath));
    }
    iVar2 = grimPlat_OpenFileRequest(s_Select_smush_file____004ea7ec,s_Smush_files____snm__004ea804)
    ;
    if (iVar2 == 0) {
      return 0;
    }
    uVar9 = 0x7f;
    puVar3 = (uint *)grimPlat_GetDefaultOpenPath();
    strncpy((uint *)g_bSmushPath,puVar3,uVar9);
    g_bSmushPath[0x7f] = '\0';
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
  if (name != (char *)0x0) {
    pcVar4 = name;
  }
  iVar2 = Cos_RegisterComponent(cosInst,(int)pcVar4,(int)pcVar5,tag,parent,type,((unsigned)(uintptr_t)&DAT_004ea040));
  return (uint)(iVar2 != 0);
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
typedef struct __attribute__((packed)) { unsigned char b0[4]; void *p4; void *p8; unsigned char bc[12]; } grim_span_004ea040;
extern char grim_def_DAT_004ea030[] __asm__("_DAT_004ea030");
extern char grim_def_DAT_004ea038[] __asm__("_DAT_004ea038");
extern grim_span_004ea040 grim_def_DAT_004ea040 __asm__("_DAT_004ea040");
extern char grim_def_s_Select_smush_file____004ea7ec[24] __asm__("_s_Select_smush_file____004ea7ec");
extern char grim_def_s_Smush_files____snm__004ea804[48] __asm__("_s_Smush_files____snm__004ea804");
/* 0x004ea040, 24 bytes */ GRIM_DATA("004ea040") grim_span_004ea040 grim_def_DAT_004ea040 __asm__("_DAT_004ea040") = {
    { 0x02 },
    (void *)&grim_def_DAT_004ea030,
    (void *)&grim_def_DAT_004ea038,
    {0}
};
/* 0x004ea7ec, 24 bytes */ /* loose */ char grim_def_s_Select_smush_file____004ea7ec[24] __asm__("_s_Select_smush_file____004ea7ec") = "Select smush file...";
static unsigned char grim_anchor_004ea804[0] __attribute__((section(".data$grim_004ea804"), aligned(16), used));
static unsigned char grim_pad_004ea804[4] __attribute__((section(".data$grim_004ea804_"), aligned(4), used));
/* 0x004ea804, 48 bytes */ GRIM_DATA("004ea804z") char grim_def_s_Smush_files____snm__004ea804[48] __asm__("_s_Smush_files____snm__004ea804") = "Smush files (*.snm)\000*.snm\000All Files (*.*)\000*.*";
