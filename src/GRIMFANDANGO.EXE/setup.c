/* GRIMFANDANGO.EXE :: setup.c
 * functions 0x00485a40 .. 0x004a3ef0 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00485a40  Setup_DrawDebugCamera ---- */
/* Draws the three axis lines at the setup's interest point and the camera actor's costume at its
   position */

void Setup_DrawDebugCamera(int param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_18 (*(float (*)[3])(_frame + (0x30 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  local_18[1] = *(float *)(param_1 + 0x30);
  local_18[2] = *(float *)(param_1 + 0x34);
  local_c[0] = *(float *)(param_1 + 0x2c) - -1.0;
  local_18[0] = *(float *)(param_1 + 0x2c) - 1.0;
  local_c[1] = local_18[1];
  local_c[2] = local_18[2];
  rdPrimit3_DrawLine(local_c,local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                     UINT_008c97cc & 0xffff,0xffffffff);
  local_18[0] = *(float *)(param_1 + 0x2c);
  local_18[2] = *(float *)(param_1 + 0x34);
  local_c[1] = *(float *)(param_1 + 0x30) - -1.0;
  local_18[1] = *(float *)(param_1 + 0x30) - 1.0;
  local_c[0] = local_18[0];
  local_c[2] = local_18[2];
  rdPrimit3_DrawLine(local_c,local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                     UINT_008c97cc & 0xffff,0xffffffff);
  local_18[0] = *(float *)(param_1 + 0x2c);
  local_18[1] = *(float *)(param_1 + 0x30);
  local_c[2] = *(float *)(param_1 + 0x34) - -1.0;
  local_18[2] = *(float *)(param_1 + 0x34) - 1.0;
  local_c[0] = local_18[0];
  local_c[1] = local_18[1];
  rdPrimit3_DrawLine(local_c,local_18,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                     UINT_008c97cc & 0xffff,0xffffffff);
  iVar1 = sputActor_ActorDeref(g_nCamActorIndex);
  if (*(int *)(iVar1 + 0xa0) != 0) {
    iVar1 = ((code *)sputActor_ActorDeref)(g_nCamActorIndex,param_1 + 0x50);
    ((code *)sputCostume_Draw3D)(*(undefined4 *)(iVar1 + 0xa0));
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

void * __cdecl sputRoom_GetSetupBackground(void *set,int setupIdx)

{
  int *ref;
  int iVar1;
  char cVar2;
  int iVar3;
  void *pvVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  
  iVar1 = *(int *)((int)set + 0xac) + setupIdx * 300;
  ref = (int *)(iVar1 + 0xc0);
  if (*(int *)(iVar1 + 0xc0) == 0) {
    iVar3 = _stricmp((char *)(iVar1 + 0x80),&DAT_004ec60c);
    if (iVar3 != 0) {
      pvVar4 = sputResource_Alloc(0x444e4b42,(char *)(iVar1 + 0x80));
      if (pvVar4 != (void *)0x0) {
        Res_SetReference(ref,pvVar4,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0xa2);
      }
    }
    if (*ref != 0) goto LAB_004a3eb6;
    pvVar4 = sputResource_Alloc(0x444e4b42,s_dfltroom_bm_004ec5d4);
    Res_SetReference(ref,pvVar4,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0xaa);
    if (*ref == 0) {
      return (void *)0x0;
    }
    uVar5 = 0xffffffff;
    pcVar7 = &DAT_004ec60c;
    do {
      pcVar8 = pcVar7;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar8 = pcVar7 + 1;
      cVar2 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar2 != '\0');
    uVar5 = ~uVar5;
    pcVar7 = pcVar8 + -uVar5;
    pcVar8 = (char *)(iVar1 + 0x80);
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
    *(undefined1 *)(iVar1 + 0xa0) = 0;
  }
  else {
    Res_Touch(*(void **)(iVar1 + 0xc4));
  }
  if (*ref == 0) {
    (*g_pStd_HS->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
  }
LAB_004a3eb6:
  iVar3 = *(int *)(iVar1 + 0xc4);
  if (*ref == 0) {
    (*g_pStd_HS->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
  }
  return *(void **)(*(int *)(iVar3 + 0x78) + *(int *)(*(int *)(iVar1 + 0xc4) + 0x68) * 4);
}

/* ---- 0x004a3ef0  sputRoom_GetSetupZBackground ---- */
/* Loads the setup's ZBUF depth bitmap (name at setup+0xa0, ResRef at +0xf4) Original name
   sputRoom_GetSetupZBackground (the remaster's GrimFandango (Linux): aligned call in
   sputRender_UseSetup); was Setup_GetZBufferBitmap. */

void * __cdecl sputRoom_GetSetupZBackground(void *set,int setupIdx)

{
  int *ref;
  int iVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  void *data;
  byte *pbVar5;
  bool bVar6;
  
  iVar1 = *(int *)((int)set + 0xac) + setupIdx * 300;
  ref = (int *)(iVar1 + 0xf4);
  if (*(int *)(iVar1 + 0xf4) == 0) {
    if (*(char *)(iVar1 + 0xa0) != '\0') {
      pbVar5 = &DAT_004ec60c;
      pbVar3 = (byte *)(iVar1 + 0xa0);
      do {
        bVar2 = *pbVar3;
        bVar6 = bVar2 < *pbVar5;
        if (bVar2 != *pbVar5) {
LAB_004a3f61:
          iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
          goto LAB_004a3f66;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar3[1];
        bVar6 = bVar2 < pbVar5[1];
        if (bVar2 != pbVar5[1]) goto LAB_004a3f61;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar2 != 0);
      iVar4 = 0;
LAB_004a3f66:
      if (iVar4 != 0) {
        data = sputResource_Alloc(0x4655425a,(char *)(iVar1 + 0xa0));
        if (data != (void *)0x0) {
          Res_SetReference(ref,data,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0xcf);
        }
      }
    }
  }
  else {
    if (*ref == 0) {
      (*g_pStd_HS->pAssertFail)
                (s_Bad_ZBuffer_Reference_004ec614,s_main_sputResource_h_004e80a8,0x95);
    }
    Res_Touch(*(void **)(iVar1 + 0xf8));
  }
  if (*ref == 0) {
    return (void *)0x0;
  }
  return *(void **)(iVar1 + 0xf8);
}
