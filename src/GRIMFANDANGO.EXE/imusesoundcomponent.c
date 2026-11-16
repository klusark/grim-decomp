/* GRIMFANDANGO.EXE :: imusesoundcomponent.c
 * functions 0x004971a0 .. 0x00497660 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004971a0  SoundChanger ---- */
/* Costume tag handler for 'iMuse Streamed / Resident Sound FX' (registered by sputCostume_Startup
   through Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, starts the sound (SoundStartVoiceStream for
   streamed, SoundsLoadStartSound + positional parameters from the current set for resident sounds)
   unless it already plays. Original name SoundChanger (the remaster's GrimFandango (Linux): the
   only unmatched caller of Set_GetSoundParams; 2 matched neighbours agree, 0 disagree); was
   ImuseSoundComponent_OnKey. */

void __cdecl
SoundChanger(int tag,int snd,undefined4 param_3,int slot,uint value1,uint value2,uint value3,
            uint inst)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Actor *pAVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  Set *set;
  uint sound;
  uint minVol;
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  iVar5 = Cos_InstGetUserData(inst);
  iVar3 = slot;
  iVar2 = snd;
  pAVar1 = g_pActors;
  if ((*(int *)(&g_aSoundCommands + slot * 4) == 0) &&
     (iVar6 = SoundsIsSoundPlaying(snd), iVar6 == 0)) {
    if (tag != 0x736c6d69) {
      if (tag != 0x73736d69) {
        return;
      }
      SoundStartVoiceStream(iVar2,(uint)*(byte *)(iVar2 + 0x20),(int)*(char *)(iVar2 + 0x21));
      SoundsSetParam(iVar2,0x400,1);
      SoundsSetParam(iVar2,0x500,*(uint *)(iVar2 + 0x24));
      return;
    }
    set = sputRoom_GetCurrentRoom();
    sound = SoundsLoadStartSound(iVar2,*(int *)(iVar2 + 0x24),1);
    if (set == (Set *)0x0) {
      return;
    }
    sputRoom_GetSoundParameters
              (set,(float *)&snd,(char *)&inst,(char *)&tag,&local_4,(float *)&slot);
    bVar4 = *(byte *)(iVar2 + 0x20);
    if ((byte)tag < *(byte *)(iVar2 + 0x20)) {
      bVar4 = (byte)tag;
    }
    minVol = inst & 0xff;
    if ((int)(inst & 0xff) <= (int)*(uint *)(iVar2 + 0x28)) {
      minVol = *(uint *)(iVar2 + 0x28);
    }
    sputRoom_SetSoundPosition(sound,(undefined **)pAVar1[iVar5].aPos,minVol,(uint)bVar4,snd,slot);
    return;
  }
  if (*(int *)(&g_aSoundCommands + iVar3 * 4) == 1) {
    if (tag == 0x736c6d69) {
      SoundsStopSound(iVar2);
      return;
    }
    if (tag == 0x73736d69) {
      SoundStopVoiceStream();
      return;
    }
  }
  else if (*(int *)(&g_aSoundCommands + iVar3 * 4) == 2) {
    iMUSE_SetHook(iVar2,0x80);
  }
  return;
}
#undef local_4


/* ---- 0x00497320  SoundAdjuster ---- */
/* Costume tag handler for 'iMuse Streamed / Resident Sound FX' (registered by sputCostume_Startup
   through Cos_NewStateBasedTag/Cos_NewIntTag): slot 4, editor dialog for Maximum Volume / Priority
   / Minimum Volume. Original name SoundAdjuster (the remaster's GrimFandango (Linux): strings:
   '%s,%d,%d,%d,%d'); was ImuseSoundComponent_EditKey. */

uint __cdecl SoundAdjuster(int *comp,uint text)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char cVar7;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint (*)[8])(_frame + (0x40 - 0x20)))
  
  iVar1 = *comp;
  local_30 = (uint)s_Maximum_Volume_004ea6a8;
  local_2c = (uint)s_Pan_004ea6a4;
  local_28 = (uint)s_Priority_004ea698;
  local_24 = (uint)s_Minimum_Volume_004ea688;
  local_40 = (uint)*(byte *)(iVar1 + 0x20);
  local_3c = (uint)*(char *)(iVar1 + 0x21);
  local_38 = *(uint *)(iVar1 + 0x24);
  local_34 = *(uint *)(iVar1 + 0x28);
  iVar2 = grimPlat_SpinDialog(text,(int)&local_30,&local_40,4);
  if ((iVar2 != 0) && ((int)local_34 <= (int)local_40)) {
    puVar3 = (uint *)strtok((byte *)text,(byte *)s___004ea52c);
    if ((int)local_40 < 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = local_40;
      if (0x7f < (int)local_40) {
        uVar5 = 0x7f;
      }
    }
    *(char *)(iVar1 + 0x20) = (char)uVar5;
    if ((int)local_3c < 0) {
      cVar7 = '\0';
    }
    else if ((int)local_3c < 0x80) {
      cVar7 = (char)local_3c;
    }
    else {
      cVar7 = '\x7f';
    }
    *(char *)(iVar1 + 0x21) = cVar7;
    if ((int)local_38 < 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = local_38;
      if (0x7f < (int)local_38) {
        uVar6 = 0x7f;
      }
    }
    *(uint *)(iVar1 + 0x24) = uVar6;
    if ((int)local_34 < 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = local_34;
      if (0x7f < (int)local_34) {
        uVar4 = 0x7f;
      }
    }
    *(uint *)(iVar1 + 0x28) = uVar4;
    sprintf((char *)local_20,s__s__d__d__d__d_004ea678,puVar3,uVar5 & 0xff,(int)cVar7,uVar6,uVar4);
    strncpy(puVar3,local_20,0x1f);
    *(undefined1 *)((int)puVar3 + 0x1f) = 0;
    return 1;
  }
  return 0;
}
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30


/* ---- 0x00497460  SoundRequester ---- */
/* Costume tag handler for 'iMuse Streamed / Resident Sound FX' (registered by sputCostume_Startup
   through Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, builds a sound key or asks for an
   .imu/.imc/.wvc file. Original name SoundRequester (the remaster's GrimFandango (Linux): strings:
   'Select sound file to add...' | 'Sound files (*.imu, *.imc, *.wvc, *.wav)'); was
   ImuseSoundComponent_Create. */

int __cdecl SoundRequester(uint cosInst,int tag,int parent,int type,char *name)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  undefined1 uVar5;
  undefined *puVar6;
  char *pcVar7;
  undefined1 local_25;
  uint local_24;
  #define local_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  local_20[0] = DAT_004f5a98;
  uVar5 = 0x7f;
  pcVar7 = local_20 + 1;
  for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1) {
    pcVar7[0] = '\0';
    pcVar7[1] = '\0';
    pcVar7[2] = '\0';
    pcVar7[3] = '\0';
    pcVar7 = pcVar7 + 4;
  }
  pcVar7[0] = '\0';
  pcVar7[1] = '\0';
  pcVar7[2] = '\0';
  local_25 = 0x40;
  puVar6 = (undefined *)0x64;
  local_24 = 1;
  if (parent != 0) {
    return 0;
  }
  if (name == (char *)0x0) {
    if (g_bSoundPath != '\0') {
      grimPlat_SetDefaultOpenPath(((unsigned)(uintptr_t)&g_bSoundPath));
    }
    iVar4 = grimPlat_OpenFileRequest
                      (s_Select_sound_file_to_add____004ea6b8,
                       s_Sound_files____imu____imc____wvc_004ea6d4);
    if (iVar4 == 0) {
      return 0;
    }
    uVar1 = 0x7f;
    puVar2 = (uint *)grimPlat_GetDefaultOpenPath();
    strncpy((uint *)&g_bSoundPath,puVar2,uVar1);
    DAT_008caab7 = 0;
    name = stdFnames_FindMedName(g_szGrimlib_aFilename);
  }
  else {
    strncpy((uint *)local_20,(uint *)name,0x1f);
    local_20[0x1f] = '\0';
    strtok((byte *)local_20,(byte *)s___004ea52c);
    uVar1 = strtok((byte *)0x0,(byte *)s___004ea52c);
    if (uVar1 != 0) {
      puVar6 = atoi(uVar1);
      uVar5 = SUB41(puVar6,0);
      uVar1 = strtok((byte *)0x0,(byte *)s___004ea52c);
      puVar6 = atoi(uVar1);
      local_25 = SUB41(puVar6,0);
      uVar1 = strtok((byte *)0x0,(byte *)s___004ea52c);
      puVar6 = atoi(uVar1);
      uVar1 = strtok((byte *)0x0,(byte *)s___004ea52c);
      local_24 = (uint)atoi(uVar1);
    }
  }
  puVar2 = (uint *)(*g_pSputCosHS->pAlloc)(0x2c,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xcee);
  if (puVar2 == (uint *)0x0) {
    return 0;
  }
  puVar3 = (uint *)local_20;
  if (local_20[0] == '\0') {
    puVar3 = (uint *)name;
  }
  strncpy(puVar2,puVar3,0x1f);
  *(undefined1 *)((int)puVar2 + 0x21) = local_25;
  puVar2[10] = local_24;
  *(undefined1 *)((int)puVar2 + 0x1f) = 0;
  *(undefined1 *)(puVar2 + 8) = uVar5;
  puVar2[9] = (uint)puVar6;
  iVar4 = Cos_RegisterComponent(cosInst,(int)name,(int)puVar2,tag,0,type,((unsigned)(uintptr_t)&DAT_004ea018));
  return (uint)(iVar4 != 0);
}
#undef local_20


/* ---- 0x00497640  SoundFreer ---- */
/* Costume tag handler for 'iMuse Streamed / Resident Sound FX' (registered by sputCostume_Start
   through Cos_NewStateBasedTag/Cos_NewIntTag): slot 2, frees the key data. Original name SoundFreer
   (the remaster's GrimFandango (Linux): the same handler slot (freer) of the same costume tag
   registration in sputCostume_Startup); was ImuseSoundComponent_Destroy. */

uint __cdecl SoundFreer(uint tag,uint inst,uint data)

{
  (*g_pSputCosHS->pFree)(data);
  return 1;
}

/* ---- 0x00497660  SoundStopper ---- */
/* Costume tag handler for 'iMuse Streamed / Resident Sound FX' (registered by sputCostume_Start
   through Cos_NewStateBasedTag/Cos_NewIntTag): slot 3, SoundsStopSound. Original name SoundStopper
   (the remaster's GrimFandango (Linux): the same handler slot (stopper) of the same costume tag
   registration in sputCostume_Startup); was ImuseSoundComponent_Stop. */

uint __cdecl SoundStopper(int name)

{
  SoundsStopSound(name);
  return 1;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
typedef struct __attribute__((packed)) { unsigned char b0[4]; void *p4; void *p8; unsigned char bc[12]; } grim_span_004ea018;
extern char grim_def_DAT_004ea008[] __asm__("_DAT_004ea008");
extern grim_span_004ea018 grim_def_DAT_004ea018 __asm__("_DAT_004ea018");
extern unsigned char grim_def_g_aSoundCommands[16] __asm__("_g_aSoundCommands");
extern char grim_def_s_Maximum_Volume_004ea6a8[16] __asm__("_s_Maximum_Volume_004ea6a8");
extern char grim_def_s_Minimum_Volume_004ea688[16] __asm__("_s_Minimum_Volume_004ea688");
extern char grim_def_s_Pan_004ea6a4[4] __asm__("_s_Pan_004ea6a4");
extern char grim_def_s_Priority_004ea698[12] __asm__("_s_Priority_004ea698");
extern char grim_def_s_Select_sound_file_to_add____004ea6b8[28] __asm__("_s_Select_sound_file_to_add____004ea6b8");
extern char grim_def_s_Sound_files____imu____imc____wvc_004ea6d4[88] __asm__("_s_Sound_files____imu____imc____wvc_004ea6d4");
extern char grim_def_s__s__d__d__d__d_004ea678[16] __asm__("_s__s__d__d__d__d_004ea678");
/* 0x004e9ff8, 16 bytes */ GRIM_DATA("004e9ff8") unsigned char grim_def_g_aSoundCommands[16] __asm__("_g_aSoundCommands") = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02 };
/* 0x004ea018, 24 bytes */ GRIM_DATA("004ea018") grim_span_004ea018 grim_def_DAT_004ea018 __asm__("_DAT_004ea018") = {
    { 0x03 },
    (void *)&grim_def_g_aSoundCommands,
    (void *)&grim_def_DAT_004ea008,
    {0}
};
/* 0x004ea678, 16 bytes */ /* loose */ char grim_def_s__s__d__d__d__d_004ea678[16] __asm__("_s__s__d__d__d__d_004ea678") = "%s,%d,%d,%d,%d";
/* 0x004ea688, 16 bytes */ /* loose */ char grim_def_s_Minimum_Volume_004ea688[16] __asm__("_s_Minimum_Volume_004ea688") = "Minimum Volume";
/* 0x004ea698, 12 bytes */ /* loose */ char grim_def_s_Priority_004ea698[12] __asm__("_s_Priority_004ea698") = "Priority";
/* 0x004ea6a4, 4 bytes */ /* loose */ char grim_def_s_Pan_004ea6a4[4] __asm__("_s_Pan_004ea6a4") = "Pan";
/* 0x004ea6a8, 16 bytes */ /* loose */ char grim_def_s_Maximum_Volume_004ea6a8[16] __asm__("_s_Maximum_Volume_004ea6a8") = "Maximum Volume";
/* 0x004ea6b8, 28 bytes */ /* loose */ char grim_def_s_Select_sound_file_to_add____004ea6b8[28] __asm__("_s_Select_sound_file_to_add____004ea6b8") = "Select sound file to add...";
static unsigned char grim_anchor_004ea6d4[0] __attribute__((section(".data$grim_004ea6d4"), aligned(16), used));
static unsigned char grim_pad_004ea6d4[4] __attribute__((section(".data$grim_004ea6d4_"), aligned(4), used));
/* 0x004ea6d4, 88 bytes */ GRIM_DATA("004ea6d4z") char grim_def_s_Sound_files____imu____imc____wvc_004ea6d4[88] __asm__("_s_Sound_files____imu____imc____wvc_004ea6d4") = "Sound files (*.imu, *.imc, *.wvc, *.wav)\000*.imu;*.imc;*.wvc;*.wav\000All Files (*.*)\000*.*";
