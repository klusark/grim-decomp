/* GRIMFANDANGO.EXE :: keyframecomponent.c
 * functions 0x00497890 .. 0x004980e0 (7 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00497890  KeyframeComponent_OnKey ---- */
/* Costume tag handler for 'RDroid Keyframe (KEY)' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, applies a keyframe key to the actor's puppet: finds
   or adds the track (rdPuppet_AddTrack) and plays/loops/stops/fades it according to the key type
   0..14. */

void KeyframeComponent_OnKey
               (undefined4 param_1,int *param_2,undefined4 param_3,int param_4,uint param_5,
               undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  void *puppet;
  void *data;
  float fVar1;
  bool bVar2;
  undefined4 *puVar3;
  uint track;
  
  puppet = *(void **)(*(int *)(*param_2 + 0x40) + 0x14);
  if (param_2[1] == 0) {
    (*g_pSvcMain->pAssertFail)
              (s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3);
  }
  data = (void *)param_2[2];
  bVar2 = false;
  track = 0;
  puVar3 = (undefined4 *)((int)puppet + 0x130);
  do {
    if ((void *)*puVar3 == data) break;
    track = track + 1;
    puVar3 = puVar3 + 0x4d;
  } while ((int)track < 6);
  if (*(uint *)(&DAT_004e9f60 + param_4 * 4) < 8) {
    if (track == 6) {
      track = rdPuppet_AddTrack(puppet,(uint)data,param_2[0xf],param_2[0xe]);
      if ((int)track < 0) {
        return;
      }
      *(int *)(*(int *)(*param_2 + 0x40) + 0x48) = *param_2;
      ResRef_Add((void *)(*param_2 + 0x54 + track * 0x34),data,
                 s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xe3a);
      *(undefined4 *)(*param_2 + 0x18c) = param_8;
      rdPuppet_SetTrackUserData(puppet,track,KeyframeComponent_TrackCallback);
      bVar2 = true;
      goto LAB_00497960;
    }
  }
  else {
LAB_00497960:
    if (track == 6) {
      return;
    }
  }
  switch(*(undefined4 *)(&DAT_004e9f60 + param_4 * 4)) {
  case 0:
    if (bVar2) {
      rdPuppet_AdvanceTrack(puppet,track,(float)param_5 * 0.001);
    }
    rdPuppet_ClearTrackNodes(puppet,track);
    rdPuppet_SetTrackFlags(puppet,track,0x20);
    rdPuppet_PlayTrack(puppet,track);
    return;
  case 1:
    if (bVar2) {
      rdPuppet_AdvanceTrack(puppet,track,(float)param_5 * 0.001);
    }
    if ((*(byte *)((int)puppet + track * 0x134 + 8) & 0xc) == 0) {
      rdPuppet_PlayTrack(puppet,track);
      return;
    }
    break;
  case 2:
    if (bVar2) {
      rdPuppet_AdvanceTrack(puppet,track,(float)param_5 * 0.001);
    }
    rdPuppet_ClearTrackNodes(puppet,track);
    rdPuppet_SetTrackFlags(puppet,track,0x40);
    rdPuppet_PlayTrack(puppet,track);
    return;
  case 3:
    if (bVar2) {
      rdPuppet_AdvanceTrack(puppet,track,(float)param_5 * 0.001);
    }
    rdPuppet_ClearTrackNodes(puppet,track);
    rdPuppet_SetTrackFlags(puppet,track,0x80);
    rdPuppet_PlayTrack(puppet,track);
    return;
  case 4:
    rdPuppet_FadeInTrack(puppet,track,1.0);
    if (bVar2) {
      fVar1 = (float)param_5;
LAB_00497bc4:
      rdPuppet_AdvanceTrack(puppet,track,fVar1 * 0.001);
      return;
    }
    break;
  case 5:
    rdPuppet_FadeInTrack(puppet,track,0.5);
    if (bVar2) {
      fVar1 = (float)param_5;
      goto LAB_00497bc4;
    }
    break;
  case 6:
    rdPuppet_FadeInTrack(puppet,track,0.25);
    if (bVar2) {
      fVar1 = (float)param_5;
      goto LAB_00497bc4;
    }
    break;
  case 7:
    rdPuppet_FadeInTrack(puppet,track,0.125);
    if (bVar2) {
      fVar1 = (float)param_5;
      goto LAB_00497bc4;
    }
    break;
  case 8:
    if ((*(byte *)((int)puppet + track * 0x134 + 8) & 8) == 0) {
      rdPuppet_StopTrack(puppet,track);
      return;
    }
    break;
  case 9:
    rdPuppet_SetTrackFlags(puppet,track,0x10);
    return;
  case 10:
    *(uint *)((int)puppet + track * 0x134 + 8) =
         *(uint *)((int)puppet + track * 0x134 + 8) & 0xffffffef | 2;
    if (bVar2) {
      fVar1 = (float)param_5;
      goto LAB_00497bc4;
    }
    break;
  case 0xb:
    rdPuppet_FadeOutTrack(puppet,track,1.0);
    return;
  case 0xc:
    rdPuppet_FadeOutTrack(puppet,track,0.5);
    return;
  case 0xd:
    rdPuppet_FadeOutTrack(puppet,track,0.25);
    return;
  case 0xe:
    rdPuppet_FadeOutTrack(puppet,track,0.125);
  }
  return;
}

/* ---- 0x00497cb0  KeyframeComponent_TrackCallback ---- */
/* Track user-data callback installed by KeyframeComponent_OnKey (rdPuppet_SetTrackUserData):
   forwards track markers of the playing animation to Lua_CallCostumeMarkerHandler for the actor and
   drops the keyframe ResRef when the track ends. */

void KeyframeComponent_TrackCallback(int param_1,int param_2,uint param_3)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = Cos_InstGetUserData(*(int *)(param_1 + 0x18c));
    Lua_CallCostumeMarkerHandler((void *)((int)g_pActorTable + iVar1 * 0xa8),param_3);
    if (param_3 == 0) {
      ResRef_Remove((void *)(param_1 + 0x54 + param_2 * 0x34));
    }
  }
  return;
}

/* ---- 0x00497d10  KeyframeComponent_NewInstance ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Costume tag handler for 'RDroid Keyframe (KEY)' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 5, instance data for a keyframe component (ResRef to
   the animation, 'Bad keyframe Reference' assertion); with param 0 it frees it. */

int * KeyframeComponent_NewInstance(int param_1,int *param_2,int param_3)

{
  void *data;
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  iVar1 = param_1;
  if (param_3 == 0) {
    iVar1 = Cos_InstGetInstanceData(param_1,(int)param_2,(int *)0x0);
    ResRef_Remove((void *)(iVar1 + 4));
    (*g_pSvcCostume->pFree)(iVar1);
    return (int *)0x0;
  }
  Cos_InstComponentInfo(param_1,(int)param_2,(int)&param_3,(int)&param_2,(int)&param_1);
  piVar4 = param_2;
  if (*param_2 == 0) {
    (*g_pSvcMain->pAssertFail)
              (s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3);
  }
  data = (void *)piVar4[1];
  piVar2 = (int *)(*g_pSvcCostume->pAlloc)(0x40,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xed8);
  piVar4 = piVar2;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar4 = 0;
    piVar4 = piVar4 + 1;
  }
  ResRef_Add(piVar2 + 1,data,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xeda);
  piVar2[0xe] = param_2[0xd];
  piVar2[0xf] = param_2[0xe];
  iVar1 = Cos_InstGetInstanceData(iVar1,param_1,(int *)0x0);
  *piVar2 = iVar1;
  return piVar2;
}
#endif


/* ---- 0x00497e10  KeyframeComponent_Create ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Costume tag handler for 'RDroid Keyframe (KEY)' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, builds a key from 'name priority tagged' text or
   asks for a .key file and loads it as a Keyframe resource. */

bool KeyframeComponent_Create(uint param_1,int param_2,int param_3,int param_4,uint param_5)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *name;
  void *data;
  uint uVar1;
  undefined4 uVar2;
  undefined4 *ref;
  int iVar3;
  undefined4 *puVar4;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(undefined1 *)(_frame + (0x40 - 0x20)))
  #define local_1f (*(undefined4 *)(_frame + (0x40 - 0x1f)))
  #define local_1 (*(undefined1 *)(_frame + (0x40 - 0x1)))
  
  local_20 = DAT_004f5a98;
  local_24 = 0;
  puVar4 = &local_1f;
  for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined2 *)puVar4 = 0;
  *(undefined1 *)((int)puVar4 + 2) = 0;
  local_2c = 1;
  local_28 = 5;
  if ((param_4 == 0x4c444f4d) || (param_4 == 0x4c444d4d)) {
    if (param_3 == 0) {
      return false;
    }
    if (param_5 == 0) {
      if (DAT_008ca7b8 != '\0') {
        Plat_SetDialogDirectory(&DAT_008ca7b8);
      }
      iVar3 = Plat_OpenFileDialog(s_Select_keyframe_file_to_add____004ea76c,
                                  s_Keyframe_files____key__004ea78c);
      if (iVar3 == 0) {
        return false;
      }
      uVar2 = ((code *)Plat_GetDialogFileName)(0x7f);
      ((code *)strncpy)(&DAT_008ca7b8,uVar2);
      DAT_008ca837 = 0;
      local_24 = (uint)Str_Basename(g_szDialogFileName);
      data = Resource_Load(0x4659454b,g_szDialogFileName);
    }
    else {
      strncpy(&local_20,param_5,0x1f);
      local_1 = 0;
      name = (char *)strtok(&local_20,&DAT_004ea52c);
      data = Resource_Load(0x4659454b,name);
      uVar1 = strtok(0,&DAT_004ea52c);
      if (uVar1 != 0) {
        local_2c = (uint)atoi(uVar1);
        uVar1 = strtok(0,&DAT_004ea52c);
        local_28 = (uint)atoi(uVar1);
      }
    }
    if (data != (void *)0x0) {
      ref = (undefined4 *)
            (*g_pSvcCostume->pAlloc)(0x3c,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xf27);
      puVar4 = ref;
      for (iVar3 = 0xf; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
      ResRef_Add(ref,data,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xf29);
      ref[0xe] = local_2c;
      ref[0xd] = local_28;
      if (param_5 == 0) {
        param_5 = local_24;
      }
      iVar3 = Cos_RegisterComponent(param_1,param_5,(int)ref,param_2,param_3,param_4,IMG_ADDR(0x004e9fe0));
      return iVar3 != 0;
    }
  }
  return false;
}
#undef local_1
#undef local_1f
#undef local_20
#undef local_24
#undef local_28
#undef local_2c

#endif


/* ---- 0x00498000  KeyframeComponent_EditKey ---- */
/* Costume tag handler for 'RDroid Keyframe (KEY)' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 4, editor dialog for the Normal/Tagged priority of a
   keyframe key. */

undefined4 KeyframeComponent_EditKey(int *param_1,undefined4 param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(char (*)[32])(_frame + (0x40 - 0x20)))
  
  local_28 = (uint)s_Tagged_Priority_004ea7dc;
  local_24 = (uint)s_Normal_Priority_004ea7cc;
  iVar1 = *param_1;
  local_30 = *(uint *)(iVar1 + 0x34);
  local_2c = *(uint *)(iVar1 + 0x38);
  iVar2 = Plat_PromptDialog(param_2,&local_28,&local_30,2);
  if (iVar2 != 0) {
    iVar2 = strtok(param_2,&DAT_004ea52c);
    *(uint *)(iVar1 + 0x34) = local_30;
    *(uint *)(iVar1 + 0x38) = local_2c;
    sprintf(local_20,s__s__d__d_004ea7c0,iVar2,local_2c,local_30);
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


/* ---- 0x004980b0  KeyframeComponent_Destroy ---- */
/* Costume tag handler, slot 2 of the 'RDroid Keyframe (KEY)' tag: frees the key data. (Was named
   BitmapComponent_Destroy.) */

undefined4 KeyframeComponent_Destroy(undefined4 param_1,undefined4 param_2,void *param_3)

{
  ResRef_Remove(param_3);
  (*g_pSvcCostume->pFree)(param_3);
  return 1;
}

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
