/* GRIMFANDANGO.EXE :: imusesoundcomponent.c
 * functions 0x004971a0 .. 0x00497660 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004971a0  ImuseSoundComponent_OnKey ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Costume tag handler for 'iMuse Streamed / Resident Sound FX' (registered by sputCostume_Start
   through Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, starts the sound (SoundStartVoiceStream for
   streamed, SoundsLoadStartSound + positional parameters from the current set for resident sounds)
   unless it already plays. */

void __cdecl
ImuseSoundComponent_OnKey
          (int param_1,float param_2,undefined4 param_3,float param_4,uint param_5,uint param_6,
          uint param_7,uint param_8)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  float fVar2;
  float fVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  void *set;
  uint uVar7;
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  iVar5 = Cos_InstGetUserData(param_8);
  fVar3 = param_4;
  fVar2 = param_2;
  pvVar1 = g_pActorTable;
  if ((*(int *)(&DAT_004e9ff8 + (int)param_4 * 4) == 0) &&
     (iVar6 = SoundsIsSoundPlaying((int)param_2), iVar6 == 0)) {
    if (param_1 != 0x736c6d69) {
      if (param_1 != 0x73736d69) {
        return;
      }
      SoundStartVoiceStream
                ((int)fVar2,(uint)*(byte *)((int)fVar2 + 0x20),(int)*(char *)((int)fVar2 + 0x21));
      SoundsSetParam((int)fVar2,0x400,1);
      SoundsSetParam((int)fVar2,0x500,*(uint *)((int)fVar2 + 0x24));
      return;
    }
    set = Set_GetCurrent();
    iVar6 = SoundsLoadStartSound((int)fVar2,*(int *)((int)fVar2 + 0x24),1);
    if (set == (void *)0x0) {
      return;
    }
    Set_GetSoundParams(set,&param_2,(char *)&param_8,(char *)&param_1,&local_4,&param_4);
    bVar4 = *(byte *)((int)fVar2 + 0x20);
    if ((byte)param_1 < *(byte *)((int)fVar2 + 0x20)) {
      bVar4 = (byte)param_1;
    }
    uVar7 = param_8 & 0xff;
    if ((int)(param_8 & 0xff) <= (int)*(uint *)((int)fVar2 + 0x28)) {
      uVar7 = *(uint *)((int)fVar2 + 0x28);
    }
    Sound_SetPosition(iVar6,(int)pvVar1 + iVar5 * 0xa8 + 0xc,uVar7,bVar4,param_2,param_4);
    return;
  }
  if (*(int *)(&DAT_004e9ff8 + (int)fVar3 * 4) == 1) {
    if (param_1 == 0x736c6d69) {
      SoundsStopSound((int)fVar2);
      return;
    }
    if (param_1 == 0x73736d69) {
      SoundStopVoiceStream();
      return;
    }
  }
  else if (*(int *)(&DAT_004e9ff8 + (int)fVar3 * 4) == 2) {
    iMUSE_SetHook((int)fVar2,0x80);
  }
  return;
}
#undef local_4

#endif


/* ---- 0x00497320  ImuseSoundComponent_EditKey ---- */
/* Costume tag handler for 'iMuse Streamed / Resident Sound FX' (registered by sputCostume_Start
   through Cos_NewStateBasedTag/Cos_NewIntTag): slot 4, editor dialog for Maximum Volume / Priority
   / Minimum Volume. */

undefined4 ImuseSoundComponent_EditKey(int *param_1,undefined4 param_2)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  char cVar6;
  #define local_40 (*(uint *)(_frame + (0x50 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x50 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(char (*)[32])(_frame + (0x50 - 0x20)))
  
  iVar1 = *param_1;
  local_30 = (uint)s_Maximum_Volume_004ea6a8;
  local_2c = (uint)&DAT_004ea6a4;
  local_28 = (uint)s_Priority_004ea698;
  local_24 = (uint)s_Minimum_Volume_004ea688;
  local_40 = (uint)*(byte *)(iVar1 + 0x20);
  local_3c = (uint)*(char *)(iVar1 + 0x21);
  local_38 = *(uint *)(iVar1 + 0x24);
  local_34 = *(uint *)(iVar1 + 0x28);
  iVar2 = Plat_PromptDialog(param_2,&local_30,&local_40,4);
  if ((iVar2 != 0) && ((int)local_34 <= (int)local_40)) {
    iVar2 = strtok(param_2,&DAT_004ea52c);
    if ((int)local_40 < 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = local_40;
      if (0x7f < (int)local_40) {
        uVar4 = 0x7f;
      }
    }
    *(char *)(iVar1 + 0x20) = (char)uVar4;
    if ((int)local_3c < 0) {
      cVar6 = '\0';
    }
    else if ((int)local_3c < 0x80) {
      cVar6 = (char)local_3c;
    }
    else {
      cVar6 = '\x7f';
    }
    *(char *)(iVar1 + 0x21) = cVar6;
    if ((int)local_38 < 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = local_38;
      if (0x7f < (int)local_38) {
        uVar5 = 0x7f;
      }
    }
    *(uint *)(iVar1 + 0x24) = uVar5;
    if ((int)local_34 < 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = local_34;
      if (0x7f < (int)local_34) {
        uVar3 = 0x7f;
      }
    }
    *(uint *)(iVar1 + 0x28) = uVar3;
    sprintf(local_20,s__s__d__d__d__d_004ea678,iVar2,uVar4 & 0xff,(int)cVar6,uVar5,uVar3);
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


/* ---- 0x00497460  ImuseSoundComponent_Create ---- */
/* Costume tag handler for 'iMuse Streamed / Resident Sound FX' (registered by sputCostume_Start
   through Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, builds a sound key or asks for an
   .imu/.imc/.wvc file. */

bool ImuseSoundComponent_Create(uint param_1,int param_2,int param_3,int param_4,char *param_5)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  undefined4 uVar2;
  char *pcVar3;
  int iVar4;
  undefined1 uVar5;
  undefined *puVar6;
  undefined4 *puVar7;
  #define local_25 (*(undefined1 *)(_frame + (0x40 - 0x25)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(char *)(_frame + (0x40 - 0x20)))
  #define local_1f (*(undefined4 *)(_frame + (0x40 - 0x1f)))
  #define local_1 (*(undefined1 *)(_frame + (0x40 - 0x1)))
  
  local_20 = DAT_004f5a98;
  uVar5 = 0x7f;
  puVar7 = &local_1f;
  for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  *(undefined2 *)puVar7 = 0;
  *(undefined1 *)((int)puVar7 + 2) = 0;
  local_25 = 0x40;
  puVar6 = (undefined *)0x64;
  local_24 = 1;
  if (param_3 != 0) {
    return false;
  }
  if (param_5 == (char *)0x0) {
    if (DAT_008caa38 != '\0') {
      Plat_SetDialogDirectory(&DAT_008caa38);
    }
    iVar4 = Plat_OpenFileDialog(s_Select_sound_file_to_add____004ea6b8,
                                s_Sound_files____imu____imc____wvc_004ea6d4);
    if (iVar4 == 0) {
      return false;
    }
    uVar2 = ((code *)Plat_GetDialogFileName)(0x7f);
    ((code *)strncpy)(&DAT_008caa38,uVar2);
    DAT_008caab7 = 0;
    param_5 = Str_Basename(g_szDialogFileName);
  }
  else {
    strncpy(&local_20,param_5,0x1f);
    local_1 = 0;
    strtok(&local_20,&DAT_004ea52c);
    uVar1 = strtok(0,&DAT_004ea52c);
    if (uVar1 != 0) {
      puVar6 = atoi(uVar1);
      uVar5 = SUB41(puVar6,0);
      uVar1 = strtok(0,&DAT_004ea52c);
      puVar6 = atoi(uVar1);
      local_25 = SUB41(puVar6,0);
      uVar1 = strtok(0,&DAT_004ea52c);
      puVar6 = atoi(uVar1);
      uVar1 = strtok(0,&DAT_004ea52c);
      local_24 = (uint)atoi(uVar1);
    }
  }
  iVar4 = (*g_pSvcCostume->pAlloc)(0x2c,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xcee);
  if (iVar4 == 0) {
    return false;
  }
  pcVar3 = &local_20;
  if (local_20 == '\0') {
    pcVar3 = param_5;
  }
  strncpy(iVar4,pcVar3,0x1f);
  *(undefined1 *)(iVar4 + 0x21) = local_25;
  *(uint *)(iVar4 + 0x28) = local_24;
  *(undefined1 *)(iVar4 + 0x1f) = 0;
  *(undefined1 *)(iVar4 + 0x20) = uVar5;
  *(undefined **)(iVar4 + 0x24) = puVar6;
  iVar4 = Cos_RegisterComponent(param_1,(int)param_5,iVar4,param_2,0,param_4,IMG_ADDR(0x004ea018));
  return iVar4 != 0;
}
#undef local_1
#undef local_1f
#undef local_20
#undef local_24
#undef local_25


/* ---- 0x00497640  ImuseSoundComponent_Destroy ---- */
/* Costume tag handler for 'iMuse Streamed / Resident Sound FX' (registered by sputCostume_Start
   through Cos_NewStateBasedTag/Cos_NewIntTag): slot 2, frees the key data. */

undefined4 ImuseSoundComponent_Destroy(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}

/* ---- 0x00497660  ImuseSoundComponent_Stop ---- */
/* Costume tag handler for 'iMuse Streamed / Resident Sound FX' (registered by sputCostume_Start
   through Cos_NewStateBasedTag/Cos_NewIntTag): slot 3, SoundsStopSound. */

undefined4 ImuseSoundComponent_Stop(int param_1)

{
  SoundsStopSound(param_1);
  return 1;
}
