/* GRIMFANDANGO.EXE :: setup.c
 * functions 0x00485a40 .. 0x004a3ef0 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00485a40  Setup_DrawDebugCamera ---- */
/* Draws the three axis lines at the setup's interest point and the camera actor's costume at its
   position */

void __cdecl Setup_DrawDebugCamera(int setup)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Actor *pAVar1;
  uint matrix;
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  local_18[1] = *(float *)(setup + 0x30);
  local_18[2] = *(float *)(setup + 0x34);
  local_c[0] = *(float *)(setup + 0x2c) - -1.0f;
  local_18[0] = *(float *)(setup + 0x2c) - 1.0f;
  local_c[1] = local_18[1];
  local_c[2] = local_18[2];
  rdPrimit3_DrawLine(local_c,local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                     UINT_008c97cc & 0xffff,0xffffffff);
  local_18[0] = *(float *)(setup + 0x2c);
  local_18[2] = *(float *)(setup + 0x34);
  local_c[1] = *(float *)(setup + 0x30) - -1.0f;
  local_18[1] = *(float *)(setup + 0x30) - 1.0f;
  local_c[0] = local_18[0];
  local_c[2] = local_18[2];
  rdPrimit3_DrawLine(local_c,local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                     UINT_008c97cc & 0xffff,0xffffffff);
  local_18[0] = *(float *)(setup + 0x2c);
  local_18[1] = *(float *)(setup + 0x30);
  local_c[2] = *(float *)(setup + 0x34) - -1.0f;
  local_18[2] = *(float *)(setup + 0x34) - 1.0f;
  local_c[0] = local_18[0];
  local_c[1] = local_18[1];
  rdPrimit3_DrawLine(local_c,local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                     UINT_008c97cc & 0xffff,0xffffffff);
  pAVar1 = sputActor_ActorDeref(g_nCamActorIndex);
  if (pAVar1->pCostumes != (CostumeNode *)0x0) {
    matrix = setup + 0x50;
    pAVar1 = sputActor_ActorDeref(g_nCamActorIndex);
    sputCostume_Draw3D((uint)pAVar1->pCostumes,matrix);
  }
  return;
}
#undef local_18
#undef local_c


/* ---- 0x004a3db0  sputRoom_GetSetupBackground ---- */
/* sputRoom.cpp: loads the setup's BKND bitmap (name at setup+0x80, ResRef at +0xc0, dfltroom.bm
   when missing) and returns the current frame surface Original name sputRoom_GetSetupBackground
   (the remaster's GrimFandango (Linux): aligned call in sputRender_UseSetup); was
   Setup_GetBackgroundBitmap. */

void * __cdecl sputRoom_GetSetupBackground(Set *set,int setupIdx)

{
  ResRef *ref;
  char cVar1;
  Setup *pSVar2;
  int iVar3;
  stdBitmap *pvVar4;
  void *pvVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  
  pSVar2 = set->pSetups;
  ref = &pSVar2[setupIdx].background;
  if (pSVar2[setupIdx].background.nValid == 0) {
    iVar3 = _stricmp(&pSVar2[setupIdx].field_0x80,&DAT_004ec60c);
    if (iVar3 != 0) {
      pvVar4 = sputResource_Alloc(0x444e4b42,&pSVar2[setupIdx].field_0x80);
      if (pvVar4 != (stdBitmap *)0x0) {
        Res_SetReference(ref,pvVar4,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0xa2);
      }
    }
    if (ref->nValid != 0) goto LAB_004a3eb6;
    pvVar5 = sputResource_Alloc(0x444e4b42,s_dfltroom_bm_004ec5d4);
    Res_SetReference(ref,pvVar5,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0xaa);
    if (ref->nValid == 0) {
      return (void *)0x0;
    }
    uVar6 = 0xffffffff;
    pcVar8 = &DAT_004ec60c;
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
    pcVar9 = &pSVar2[setupIdx].field_0x80;
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
    pSVar2[setupIdx].field_0xa0 = 0;
  }
  else {
    Res_Touch(pSVar2[setupIdx].background.pData);
  }
  if (ref->nValid == 0) {
    (*g_pStd_HS->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
  }
LAB_004a3eb6:
  pvVar5 = pSVar2[setupIdx].background.pData;
  if (ref->nValid == 0) {
    (*g_pStd_HS->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
  }
  return *(void **)(*(int *)((int)pvVar5 + 0x78) +
                   *(int *)((int)pSVar2[setupIdx].background.pData + 0x68) * 4);
}

/* ---- 0x004a3ef0  sputRoom_GetSetupZBackground ---- */
/* Loads the setup's ZBUF depth bitmap (name at setup+0xa0, ResRef at +0xf4) Original name
   sputRoom_GetSetupZBackground (the remaster's GrimFandango (Linux): aligned call in
   sputRender_UseSetup); was Setup_GetZBufferBitmap. */

void * __cdecl sputRoom_GetSetupZBackground(Set *set,int setupIdx)

{
  ResRef *ref;
  byte bVar1;
  Setup *pSVar2;
  byte *pbVar3;
  int iVar4;
  void *data;
  byte *pbVar5;
  bool bVar6;
  
  pSVar2 = set->pSetups;
  ref = &pSVar2[setupIdx].zBackground;
  if (pSVar2[setupIdx].zBackground.nValid == 0) {
    if (pSVar2[setupIdx].field_0xa0 != '\0') {
      pbVar5 = &DAT_004ec60c;
      pbVar3 = &pSVar2[setupIdx].field_0xa0;
      do {
        bVar1 = *pbVar3;
        bVar6 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_004a3f61:
          iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
          goto LAB_004a3f66;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar6 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_004a3f61;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_004a3f66:
      if (iVar4 != 0) {
        data = sputResource_Alloc(0x4655425a,&pSVar2[setupIdx].field_0xa0);
        if (data != (void *)0x0) {
          Res_SetReference(ref,data,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0xcf);
        }
      }
    }
  }
  else {
    if (ref->nValid == 0) {
      (*g_pStd_HS->pAssertFail)
                (s_Bad_ZBuffer_Reference_004ec614,s_main_sputResource_h_004e80a8,0x95);
    }
    Res_Touch(pSVar2[setupIdx].zBackground.pData);
  }
  if (ref->nValid == 0) {
    return (void *)0x0;
  }
  return pSVar2[setupIdx].zBackground.pData;
}
