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
  uint uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  char *pcVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  undefined4 *puVar10;
  char *pcVar11;
  int *piVar12;
  #define local_50 (*(uint *)(_frame + (0x60 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0x60 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x60 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x60 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x60 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x60 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x60 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x60 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x60 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x60 - 0x24)))
  #define local_20 (*(char *)(_frame + (0x60 - 0x20)))
  #define local_1f (*(undefined4 *)(_frame + (0x60 - 0x1f)))
  #define local_1 (*(undefined1 *)(_frame + (0x60 - 0x1)))
  
  local_20 = DAT_004f5a98;
  puVar10 = &local_1f;
  for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  *(undefined2 *)puVar10 = 0;
  *(undefined1 *)((int)puVar10 + 2) = 0;
  local_34 = 1;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if ((param_3 != 0) && (param_4 == 216341.2)) {
    if (param_5 == (char *)0x0) {
      if (DAT_008ca938 != '\0') {
        Plat_SetDialogDirectory(&DAT_008ca938);
      }
      iVar7 = Plat_OpenFileDialog(s_Select_mat_file_for_sprite____004ea834,
                                  s_Material_files____mat__004ea5a4);
      if (iVar7 == 0) {
        return 0;
      }
      uVar4 = ((code *)Plat_GetDialogFileName)(0x7f);
      ((code *)strncpy)(&DAT_008ca938,uVar4);
      DAT_008ca9b7 = 0;
      pcVar5 = Str_Basename(g_szDialogFileName);
      param_5 = pcVar5;
    }
    else {
      strncpy(&local_20,param_5,0x1f);
      local_1 = 0;
      pcVar5 = &local_20;
      strtok(&local_20,&DAT_004ea52c);
      uVar2 = strtok(0,&DAT_004ea52c);
      if (uVar2 != 0) {
        puVar3 = atoi(uVar2);
        local_44 = (uint)((float)(int)puVar3 * 0.01);
        uVar2 = strtok(0,&DAT_004ea52c);
        puVar3 = atoi(uVar2);
        local_48 = (uint)((float)(int)puVar3 * 0.01);
        uVar2 = strtok(0,&DAT_004ea52c);
        puVar3 = atoi(uVar2);
        local_50 = (uint)((float)(int)puVar3 * 0.01);
        uVar2 = strtok(0,&DAT_004ea52c);
        puVar3 = atoi(uVar2);
        local_4c = (uint)((float)(int)puVar3 * 0.01);
        uVar2 = strtok(0,&DAT_004ea52c);
        puVar3 = atoi(uVar2);
        param_4 = (float)(int)puVar3 * 0.01;
      }
    }
    piVar6 = (int *)(*g_pSvcCostume->pAlloc)
                              (0x24,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x1026);
    if (piVar6 != (int *)0x0) {
      piVar12 = piVar6;
      for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
        *piVar12 = 0;
        piVar12 = piVar12 + 1;
      }
      local_40 = local_50;
      local_3c = local_4c;
      local_38 = (uint)param_4;
      iVar7 = rdPolyline_New(0,pcVar5,pcVar5,local_44,local_48,5,0,1,0,&local_40);
      *piVar6 = iVar7;
      uVar2 = 0xffffffff;
      do {
        pcVar11 = pcVar5;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar11 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar11;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      piVar9 = (int *)(pcVar11 + -uVar2);
      piVar12 = piVar6;
      for (uVar8 = uVar2 >> 2; piVar12 = piVar12 + 1, uVar8 != 0; uVar8 = uVar8 - 1) {
        *piVar12 = *piVar9;
        piVar9 = piVar9 + 1;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(char *)piVar12 = (char)*piVar9;
        piVar9 = (int *)((int)piVar9 + 1);
        piVar12 = (int *)((int)piVar12 + 1);
      }
      local_34 = *(int *)(*(int *)(*piVar6 + 0x7c) + 0x60) + 1;
      local_30 = 0;
      local_2c = 0;
      iVar7 = Cos_RegisterComponent(param_1,param_5,piVar6,param_2,param_3,0x4853454d,&local_34);
      if (iVar7 != 0) {
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
  #define local_48 (*(uint *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x60 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x60 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x60 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x60 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x60 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x60 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x60 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x60 - 0x24)))
  #define local_20 (*(char (*)[32])(_frame + (0x60 - 0x20)))
  
  local_34 = (uint)s_Width_004ea87c;
  local_30 = (uint)s_Height_004ea874;
  piVar1 = (int *)*param_1;
  local_2c = (uint)&DAT_004ea870;
  local_28 = (uint)&DAT_004ea86c;
  local_24 = (uint)&DAT_004ea868;
  local_48 = _ftol();
  local_44 = _ftol();
  local_40 = _ftol();
  local_3c = _ftol();
  local_38 = _ftol();
  iVar2 = Plat_PromptDialog(param_2,&local_34,&local_48,5);
  if (iVar2 != 0) {
    *(float *)(*piVar1 + 0x4c) = (float)(int)local_48 * 0.01;
    *(float *)(*piVar1 + 0x50) = (float)(int)local_44 * 0.01;
    *(float *)(*piVar1 + 0x54) = *(float *)(*piVar1 + 0x4c) * 0.5;
    *(float *)(*piVar1 + 0x58) = *(float *)(*piVar1 + 0x50) * 0.5;
    *(float *)(*piVar1 + 0xac) = (float)(int)local_40 * 0.01;
    *(float *)(*piVar1 + 0xb0) = (float)(int)local_3c * 0.01;
    *(float *)(*piVar1 + 0xb4) = (float)(int)local_38 * 0.01;
    iVar2 = strtok(param_2,&DAT_004ea52c);
    sprintf(local_20,s__s__d__d__d__d__d_004ea854,iVar2,local_48,local_44,local_40,local_3c,local_38
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
  UINT_008ca7ac = Cos_RegisterInstanceHook(UINT_008ca7ac);
  UINT_008ca7b0 = Cos_RegisterSaveHook(UINT_008ca7b0);
  if (UINT_008ca7a4 != 0) {
    (*g_pSvcCostume->pFree)(UINT_008ca7a4);
  }
  (*(code *)UINT_008ca77c)();
  UINT_008ca79c = 0;
  return;
}
