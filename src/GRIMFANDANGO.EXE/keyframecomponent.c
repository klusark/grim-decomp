/* GRIMFANDANGO.EXE :: keyframecomponent.c
 * functions 0x004980e0 .. 0x004988a0 (11 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004980e0  KeyframeComponent_Stop ---- */
/* Stops the puppet track (6 slots of 0x134 bytes at puppet+8) playing this keyframe unless it is
   flagged persistent */

undefined4 KeyframeComponent_Stop(int *param_1)

{
  void *puppet;
  int track;
  int *piVar1;
  
  puppet = *(void **)(*(int *)(*param_1 + 0x40) + 0x14);
  if (param_1[1] == 0) {
    return 0;
  }
  track = 0;
  piVar1 = (int *)((int)puppet + 0x130);
  do {
    if (*piVar1 == param_1[2]) {
      if ((*(byte *)((int)puppet + track * 0x134 + 8) & 8) == 0) {
        rdPuppet_StopTrack(puppet,track);
      }
      return 1;
    }
    track = track + 1;
    piVar1 = piVar1 + 0x4d;
  } while (track < 6);
  return 1;
}

/* ---- 0x00498140  FUN_00498140 ---- */
undefined4 FUN_00498140(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}

/* ---- 0x00498160  FUN_00498160 ---- */
void FUN_00498160(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  if (param_4 == 0) {
    Engine_BlitToBackBuffer(param_2,0,0,0xffffffff,0xffffffff);
  }
  return;
}

/* ---- 0x00498180  FUN_00498180 ---- */
undefined4 FUN_00498180(void)

{
  return 1;
}

/* ---- 0x00498190  FUN_00498190 ---- */
bool FUN_00498190(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 char *param_5)

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
  iVar2 = Cos_RegisterComponent(param_1,pcVar4,pcVar5,param_2,param_3,param_4,&DAT_004ea040);
  return iVar2 != 0;
}

/* ---- 0x00498280  FUN_00498280 ---- */
undefined4
FUN_00498280(undefined4 param_1,undefined4 param_2,int param_3,float param_4,char *param_5)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  undefined4 *puVar9;
  char *pcVar10;
  int *piVar11;
  #define local_50 (*(float *)(_frame + (0x60 - 0x50)))
  #define local_4c (*(float *)(_frame + (0x60 - 0x4c)))
  #define local_48 (*(float *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(float *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(float *)(_frame + (0x60 - 0x40)))
  #define local_3c (*(float *)(_frame + (0x60 - 0x3c)))
  #define local_38 (*(float *)(_frame + (0x60 - 0x38)))
  #define local_34 (*(int *)(_frame + (0x60 - 0x34)))
  #define local_30 (*(int *)(_frame + (0x60 - 0x30)))
  #define local_2c (*(undefined4 *)(_frame + (0x60 - 0x2c)))
  #define local_28 (*(undefined4 *)(_frame + (0x60 - 0x28)))
  #define local_24 (*(undefined4 *)(_frame + (0x60 - 0x24)))
  #define local_20 (*(char *)(_frame + (0x60 - 0x20)))
  #define local_1f (*(undefined4 *)(_frame + (0x60 - 0x1f)))
  #define local_1 (*(undefined1 *)(_frame + (0x60 - 0x1)))
  
  local_20 = DAT_004f5a98;
  puVar9 = &local_1f;
  for (iVar5 = 7; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  *(undefined2 *)puVar9 = 0;
  *(undefined1 *)((int)puVar9 + 2) = 0;
  local_34 = 1;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_40 = 0.0;
  local_3c = 0.0;
  local_38 = 0.0;
  if ((param_3 != 0) && (param_4 == 216341.2)) {
    if (param_5 == (char *)0x0) {
      if (DAT_008ca938 != '\0') {
        Plat_SetDialogDirectory(&DAT_008ca938);
      }
      iVar5 = Plat_OpenFileDialog(s_Select_mat_file_for_sprite____004ea834,
                                  s_Material_files____mat__004ea5a4);
      if (iVar5 == 0) {
        return 0;
      }
      uVar2 = ((code *)Plat_GetDialogFileName)(0x7f);
      ((code *)strncpy)(&DAT_008ca938,uVar2);
      DAT_008ca9b7 = 0;
      pcVar3 = Str_Basename(g_szDialogFileName);
      param_5 = pcVar3;
    }
    else {
      strncpy(&local_20,param_5,0x1f);
      local_1 = 0;
      pcVar3 = &local_20;
      strtok(&local_20,&DAT_004ea52c);
      iVar5 = strtok(0,&DAT_004ea52c);
      if (iVar5 != 0) {
        iVar5 = atoi(iVar5);
        local_44 = (float)iVar5 * 0.01;
        uVar2 = strtok(0,&DAT_004ea52c);
        iVar5 = atoi(uVar2);
        local_48 = (float)iVar5 * 0.01;
        uVar2 = strtok(0,&DAT_004ea52c);
        iVar5 = atoi(uVar2);
        local_50 = (float)iVar5 * 0.01;
        uVar2 = strtok(0,&DAT_004ea52c);
        iVar5 = atoi(uVar2);
        local_4c = (float)iVar5 * 0.01;
        uVar2 = strtok(0,&DAT_004ea52c);
        iVar5 = atoi(uVar2);
        param_4 = (float)iVar5 * 0.01;
      }
    }
    piVar4 = (int *)(*g_pSvcCostume->pAlloc)
                              (0x24,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x1026);
    if (piVar4 != (int *)0x0) {
      piVar11 = piVar4;
      for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1) {
        *piVar11 = 0;
        piVar11 = piVar11 + 1;
      }
      local_40 = local_50;
      local_3c = local_4c;
      local_38 = param_4;
      iVar5 = rdPolyline_New(0,pcVar3,pcVar3,local_44,local_48,5,0,1,0,&local_40);
      *piVar4 = iVar5;
      uVar6 = 0xffffffff;
      do {
        pcVar10 = pcVar3;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar10 = pcVar3 + 1;
        cVar1 = *pcVar3;
        pcVar3 = pcVar10;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      piVar8 = (int *)(pcVar10 + -uVar6);
      piVar11 = piVar4;
      for (uVar7 = uVar6 >> 2; piVar11 = piVar11 + 1, uVar7 != 0; uVar7 = uVar7 - 1) {
        *piVar11 = *piVar8;
        piVar8 = piVar8 + 1;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(char *)piVar11 = (char)*piVar8;
        piVar8 = (int *)((int)piVar8 + 1);
        piVar11 = (int *)((int)piVar11 + 1);
      }
      local_34 = *(int *)(*(int *)(*piVar4 + 0x7c) + 0x60) + 1;
      local_30 = 0;
      local_2c = 0;
      iVar5 = Cos_RegisterComponent(param_1,param_5,piVar4,param_2,param_3,0x4853454d,&local_34);
      if (iVar5 != 0) {
        return 1;
      }
      if (local_30 != 0) {
        (*g_pSvcCostume->pFree)(local_30);
        return 0;
      }
    }
  }
  return 0;
}
#undef local_1
#undef local_1f
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_44
#undef local_48
#undef local_4c
#undef local_50


/* ---- 0x00498550  FUN_00498550 ---- */
void FUN_00498550(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  if (param_4 == 0) {
    *(undefined4 *)(param_2 + 0x38) = 0;
    return;
  }
  *(undefined4 *)(param_2 + 0x38) = 1;
  *(int *)(*(int *)(*(int *)(param_2 + 0x34) + 0x7c) + 100) = param_4 + -1;
  return;
}

/* ---- 0x00498580  KeyframeComponent_Destroy ---- */
undefined4 KeyframeComponent_Destroy(undefined4 param_1,undefined4 param_2,int *param_3)

{
  rdMaterial_Free(*(undefined4 *)(*param_3 + 0x7c));
  rdSprite_Free(*param_3);
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}

/* ---- 0x004985c0  FUN_004985c0 ---- */
undefined4 * FUN_004985c0(int param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = param_1;
  if (param_3 == 0) {
    iVar1 = Cos_InstGetInstanceData(param_1,param_2,0);
    iVar2 = *(int *)(iVar1 + 0x50) + -1;
    *(int *)(iVar1 + 0x50) = iVar2;
    if (iVar2 == 0) {
      rdThing_Free(*(undefined4 *)(iVar1 + 0x40));
      (*g_pSvcCostume->pFree)(iVar1);
    }
    return (undefined4 *)0x0;
  }
  Cos_InstComponentInfo(param_1,param_2,&param_3,&param_2,&param_1);
  puVar3 = (undefined4 *)
           (*g_pSvcCostume->pAlloc)(0x194,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x1070);
  puVar4 = puVar3;
  for (iVar2 = 0x65; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar3[0xd] = *param_2;
  iVar2 = rdThing_New(0);
  puVar3[0x10] = iVar2;
  *(undefined4 *)(iVar2 + 0x30) = 0;
  rdThing_SetPolyline(puVar3[0x10],*param_2);
  if (-1 < param_1) {
    puVar4 = (undefined4 *)Cos_InstGetInstanceData(iVar1,param_1,0);
    puVar3[0x11] = *puVar4;
    puVar3[0x12] = puVar4[1];
    puVar3[0x14] = puVar3[0x14] + 1;
    puVar3[0xe] = 0;
    return puVar3;
  }
  puVar3[0x11] = 0;
  puVar3[0x14] = puVar3[0x14] + 1;
  puVar3[0x12] = 0xffffffff;
  puVar3[0xe] = 1;
  return puVar3;
}

/* ---- 0x004986e0  FUN_004986e0 ---- */
undefined4 FUN_004986e0(undefined4 *param_1,undefined4 param_2)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  #define local_48 (*(int *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(int *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(int *)(_frame + (0x60 - 0x40)))
  #define local_3c (*(int *)(_frame + (0x60 - 0x3c)))
  #define local_38 (*(int *)(_frame + (0x60 - 0x38)))
  #define local_34 (*(char **)(_frame + (0x60 - 0x34)))
  #define local_30 (*(char **)(_frame + (0x60 - 0x30)))
  #define local_2c (*(undefined **)(_frame + (0x60 - 0x2c)))
  #define local_28 (*(undefined **)(_frame + (0x60 - 0x28)))
  #define local_24 (*(undefined **)(_frame + (0x60 - 0x24)))
  #define local_20 (*(undefined1 (*)[32])(_frame + (0x60 - 0x20)))
  
  local_34 = s_Width_004ea87c;
  local_30 = s_Height_004ea874;
  piVar1 = (int *)*param_1;
  local_2c = &DAT_004ea870;
  local_28 = &DAT_004ea86c;
  local_24 = &DAT_004ea868;
  local_48 = _ftol();
  local_44 = _ftol();
  local_40 = _ftol();
  local_3c = _ftol();
  local_38 = _ftol();
  iVar2 = Plat_PromptDialog(param_2,&local_34,&local_48,5);
  if (iVar2 != 0) {
    *(float *)(*piVar1 + 0x4c) = (float)local_48 * 0.01;
    *(float *)(*piVar1 + 0x50) = (float)local_44 * 0.01;
    *(float *)(*piVar1 + 0x54) = *(float *)(*piVar1 + 0x4c) * 0.5;
    *(float *)(*piVar1 + 0x58) = *(float *)(*piVar1 + 0x50) * 0.5;
    *(float *)(*piVar1 + 0xac) = (float)local_40 * 0.01;
    *(float *)(*piVar1 + 0xb0) = (float)local_3c * 0.01;
    *(float *)(*piVar1 + 0xb4) = (float)local_38 * 0.01;
    iVar2 = strtok(param_2,&DAT_004ea52c);
    ((code *)sprintf)(local_20,s__s__d__d__d__d__d_004ea854,iVar2,local_48,local_44,local_40,local_3c,local_38
           );
    strncpy(iVar2,local_20,0x1f);
    *(undefined1 *)(iVar2 + 0x1f) = 0;
    return 1;
  }
  return 0;
}
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_44
#undef local_48


/* ---- 0x004988a0  FUN_004988a0 ---- */
void FUN_004988a0(void)

{
  Config_SetPath(s_KeyframePath_004ea27c,&DAT_008ca7b8);
  Config_SetPath(s_BitmapPath_004ea1f8,&DAT_008ca838);
  Config_SetPath(s_ColormapPath_004ea260,&DAT_008ca8b8);
  Config_SetPath(s_MaterialPath_004ea244,&DAT_008ca938);
  Config_SetPath(s_ModelPath_004ea230,&DAT_008ca9b8);
  Config_SetPath(s_SoundPath_004ea220,&DAT_008caa38);
  Config_SetPath(s_SmushPath_004ea20c,&DAT_008caab8);
  if (g_pCostumePool != (void **)0x0) {
    Pool_Destroy(g_pCostumePool);
    g_pCostumePool = (void **)0x0;
  }
  DAT_008ca7ac = Cos_RegisterInstanceHook(DAT_008ca7ac);
  DAT_008ca7b0 = Cos_RegisterSaveHook(DAT_008ca7b0);
  if (DAT_008ca7a4 != 0) {
    (*g_pSvcCostume->pFree)(DAT_008ca7a4);
  }
  (*DAT_008ca77c)();
  DAT_008ca79c = 0;
  return;
}
