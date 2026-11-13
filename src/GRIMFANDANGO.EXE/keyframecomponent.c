/* GRIMFANDANGO.EXE :: keyframecomponent.c
 * functions 0x00497890 .. 0x004980e0 (7 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00497890  KeyframeChanger ---- */
/* Costume tag handler for 'RDroid Keyframe (KEY)' (registered by sputCostume_Startup through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, applies a keyframe key to the actor's puppet: finds
   or adds the track (rdPuppet_AddTrack) and plays/loops/stops/fades it according to the key type
   0..14. Original name KeyframeChanger (the remaster's GrimFandango (Linux): the only unmatched
   caller of rdPuppet_PlayTrack; 5 matched neighbours agree, 0 disagree); was
   KeyframeComponent_OnKey. */

void __cdecl
KeyframeChanger(uint param_1,int *param_2,uint param_3,int param_4,uint param_5,uint param_6,
               uint param_7,uint param_8)

{
  void *puppet;
  void *data;
  float fVar1;
  bool bVar2;
  undefined4 *puVar3;
  uint track;
  
  puppet = *(void **)(*(int *)(*param_2 + 0x40) + 0x14);
  if (param_2[1] == 0) {
    (*g_pStd_HS->pAssertFail)(s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3)
    ;
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
  if (*(uint *)(&g_aKeyCommands + param_4 * 4) < 8) {
    if (track == 6) {
      track = rdPuppet_AddTrack(puppet,(uint)data,param_2[0xf],param_2[0xe]);
      if ((int)track < 0) {
        return;
      }
      *(int *)(*(int *)(*param_2 + 0x40) + 0x48) = *param_2;
      Res_SetReference((void *)(*param_2 + 0x54 + track * 0x34),data,
                       s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xe3a);
      *(uint *)(*param_2 + 0x18c) = param_8;
      rdPuppet_SetCallback((int)puppet,track,((unsigned)(uintptr_t)sputCostume_PuppetHook));
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
  switch(*(undefined4 *)(&g_aKeyCommands + param_4 * 4)) {
  case 0:
    if (bVar2) {
      rdPuppet_AdvanceTrack(puppet,track,(float)param_5 * 0.001);
    }
    rdPuppet_ResetTrack((int)puppet,track);
    rdPuppet_SetStatus((int)puppet,track,0x20);
    rdPuppet_PlayTrack((int)puppet,track);
    return;
  case 1:
    if (bVar2) {
      rdPuppet_AdvanceTrack(puppet,track,(float)param_5 * 0.001);
    }
    if ((*(byte *)((int)puppet + track * 0x134 + 8) & 0xc) == 0) {
      rdPuppet_PlayTrack((int)puppet,track);
      return;
    }
    break;
  case 2:
    if (bVar2) {
      rdPuppet_AdvanceTrack(puppet,track,(float)param_5 * 0.001);
    }
    rdPuppet_ResetTrack((int)puppet,track);
    rdPuppet_SetStatus((int)puppet,track,0x40);
    rdPuppet_PlayTrack((int)puppet,track);
    return;
  case 3:
    if (bVar2) {
      rdPuppet_AdvanceTrack(puppet,track,(float)param_5 * 0.001);
    }
    rdPuppet_ResetTrack((int)puppet,track);
    rdPuppet_SetStatus((int)puppet,track,0x80);
    rdPuppet_PlayTrack((int)puppet,track);
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
      rdPuppet_RemoveTrack(puppet,track);
      return;
    }
    break;
  case 9:
    rdPuppet_SetStatus((int)puppet,track,0x10);
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

/* ---- 0x00497cb0  sputCostume_PuppetHook ---- */
/* Track user-data callback installed by KeyframeComponent_OnKey (rdPuppet_SetCallback): forwards
   track markers of the playing animation to Lua_CallCostumeMarkerHandler for the actor and drops
   the keyframe ResRef when the track ends. Original name sputCostume_PuppetHook (the remaster's
   GrimFandango (Linux): the only unmatched caller of Lua_CallCostumeMarkerHandler; 1 matched
   neighbours agree, 0 disagree); was KeyframeComponent_TrackCallback. */

void __cdecl sputCostume_PuppetHook(int param_1,int param_2,uint param_3)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = Cos_InstGetUserData(*(int *)(param_1 + 0x18c));
    sputLua_DoCostumeMarkerCallback(g_pActors + iVar1,param_3);
    if (param_3 == 0) {
      Res_RemoveReference((void *)(param_1 + 0x54 + param_2 * 0x34));
    }
  }
  return;
}

/* ---- 0x00497d10  KeyframeInstancer ---- */
/* Costume tag handler for 'RDroid Keyframe (KEY)' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 5, instance data for a keyframe component (ResRef to
   the animation, 'Bad keyframe Reference' assertion); with param 0 it frees it. Original name
   KeyframeInstancer (the remaster's GrimFandango (Linux): the same handler slot (instancer) of the
   same costume tag registration in sputCostume_Startup); was KeyframeComponent_NewInstance. */

int * __cdecl KeyframeInstancer(int inst,int component,int create)

{
  void *data;
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  iVar1 = inst;
  if (create == 0) {
    iVar1 = Cos_InstGetInstanceData(inst,component,(int *)0x0);
    Res_RemoveReference((void *)(iVar1 + 4));
    (*g_pSputCosHS->pFree)(iVar1);
    return (int *)0x0;
  }
  Cos_InstComponentInfo(inst,component,(int)&create,(int)&component,(int)&inst);
  iVar3 = component;
  if (*(int *)component == 0) {
    (*g_pStd_HS->pAssertFail)(s_Bad_keyframe_Reference_004ea1e0,s_main_sputResource_h_004e80a8,0xb3)
    ;
  }
  data = *(void **)(iVar3 + 4);
  piVar2 = (int *)(*g_pSputCosHS->pAlloc)(0x40,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xed8);
  piVar4 = piVar2;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar4 = 0;
    piVar4 = piVar4 + 1;
  }
  Res_SetReference(piVar2 + 1,data,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xeda);
  piVar2[0xe] = *(int *)(component + 0x34);
  piVar2[0xf] = *(int *)(component + 0x38);
  iVar1 = Cos_InstGetInstanceData(iVar1,inst,(int *)0x0);
  *piVar2 = iVar1;
  return piVar2;
}

/* ---- 0x00497e10  KeyframeRequester ---- */
/* Costume tag handler for 'RDroid Keyframe (KEY)' (registered by sputCostume_Startup through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, builds a key from 'name priority tagged' text or
   asks for a .key file and loads it as a Keyframe resource. */

int __cdecl KeyframeRequester(uint param_1,int param_2,int param_3,int param_4,uint param_5)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char *name;
  void *data;
  uint uVar1;
  uint *puVar2;
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
      return 0;
    }
    if (param_5 == 0) {
      if (g_bKeyframePath != '\0') {
        grimPlat_SetDefaultOpenPath(((unsigned)(uintptr_t)&g_bKeyframePath));
      }
      iVar3 = grimPlat_OpenFileRequest
                        (s_Select_keyframe_file_to_add____004ea76c,s_Keyframe_files____key__004ea78c
                        );
      if (iVar3 == 0) {
        return 0;
      }
      uVar1 = 0x7f;
      puVar2 = (uint *)grimPlat_GetDefaultOpenPath();
      strncpy((uint *)&g_bKeyframePath,puVar2,uVar1);
      DAT_008ca837 = 0;
      local_24 = (uint)stdFnames_FindMedName(g_szGrimlib_aFilename);
      data = sputResource_Alloc(0x4659454b,g_szGrimlib_aFilename);
    }
    else {
      strncpy((uint *)&local_20,(uint *)param_5,0x1f);
      local_1 = 0;
      name = (char *)strtok(&local_20,&DAT_004ea52c);
      data = sputResource_Alloc(0x4659454b,name);
      uVar1 = strtok((byte *)0x0,&DAT_004ea52c);
      if (uVar1 != 0) {
        local_2c = (uint)atoi(uVar1);
        uVar1 = strtok((byte *)0x0,&DAT_004ea52c);
        local_28 = (uint)atoi(uVar1);
      }
    }
    if (data != (void *)0x0) {
      ref = (undefined4 *)
            (*g_pSputCosHS->pAlloc)(0x3c,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xf27);
      puVar4 = ref;
      for (iVar3 = 0xf; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
      }
      Res_SetReference(ref,data,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xf29);
      ref[0xe] = local_2c;
      ref[0xd] = local_28;
      if (param_5 == 0) {
        param_5 = local_24;
      }
      iVar3 = Cos_RegisterComponent(param_1,param_5,(int)ref,param_2,param_3,param_4,((unsigned)(uintptr_t)&DAT_004e9fe0));
      return (uint)(iVar3 != 0);
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


/* ---- 0x00498000  KeyframeAdjuster ---- */
/* Costume tag handler for 'RDroid Keyframe (KEY)' (registered by sputCostume_Startup through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 4, editor dialog for the Normal/Tagged priority of a
   keyframe key. */

uint __cdecl KeyframeAdjuster(int *param_1,uint param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint *puVar3;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint (*)[8])(_frame + (0x40 - 0x20)))
  
  local_28 = (uint)s_Tagged_Priority_004ea7dc;
  local_24 = (uint)s_Normal_Priority_004ea7cc;
  iVar1 = *param_1;
  local_30 = *(uint *)(iVar1 + 0x34);
  local_2c = *(uint *)(iVar1 + 0x38);
  iVar2 = grimPlat_SpinDialog(param_2,(int)&local_28,&local_30,2);
  if (iVar2 != 0) {
    puVar3 = (uint *)strtok((byte *)param_2,&DAT_004ea52c);
    *(uint *)(iVar1 + 0x34) = local_30;
    *(uint *)(iVar1 + 0x38) = local_2c;
    sprintf((char *)local_20,s__s__d__d_004ea7c0,puVar3,local_2c,local_30);
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


/* ---- 0x004980b0  KeyframeFreer ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Costume tag handler, slot 2 of the 'RDroid Keyframe (KEY)' tag: frees the key data. (Was named
   BitmapComponent_Destroy.) Original name KeyframeFreer (the remaster's GrimFandango (Linux): the
   same handler slot (freer) of the same costume tag registration in sputCostume_Startup); was
   KeyframeComponent_Destroy. */

undefined4 KeyframeFreer(undefined4 param_1,undefined4 param_2,void *param_3)

{
  Res_RemoveReference(param_3);
  (*g_pSputCosHS->pFree)(param_3);
  return 1;
}

/* ---- 0x004980e0  KeyframeStopper ---- */
/* Stops the puppet track (6 slots of 0x134 bytes at puppet+8) playing this keyframe unless it is
   flagged persistent Original name KeyframeStopper (the remaster's GrimFandango (Linux): the same
   handler slot (stopper) of the same costume tag registration in sputCostume_Startup); was
   KeyframeComponent_Stop. */

uint __cdecl KeyframeStopper(int *param_1)

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
        rdPuppet_RemoveTrack(puppet,track);
      }
      return 1;
    }
    track = track + 1;
    piVar1 = piVar1 + 0x4d;
  } while (track < 6);
  return 1;
}
