/* GRIMFANDANGO.EXE :: set.c
 * functions 0x004824c0 .. 0x004a7150 (30 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004824c0  Res_NumRefs ---- */
/* Original name Res_NumRefs (the remaster's GrimFandango (Linux): aligned call in sputRoom_Save);
   was Set_GetRefCount. */

int Res_NumRefs(void *param_1)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  
  iVar3 = 0;
  pvVar2 = Res_FindByData(param_1);
  if (pvVar2 != (void *)0x0) {
    for (iVar1 = *(int *)((int)pvVar2 + 0x24); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x30)) {
      iVar3 = iVar3 + 1;
    }
  }
  return iVar3;
}

/* ---- 0x00482670  grimlib_MakeCurrentSet ---- */
/* Lua MakeCurrentSet (NULL unloads the current set) Original name grimlib_MakeCurrentSet (the
   remaster's GrimFandango (Linux): aligned call in sputLua_MakeCurrentSetL, body similarity); was
   Set_MakeCurrent. */

void __cdecl grimlib_MakeCurrentSet(char *name)

{
  void *set;
  void *pvVar1;
  
  if (name == (char *)0x0) {
    sputRoom_SetCurrentRoom((void *)0x0,0);
    return;
  }
  set = sputResource_Alloc(0x20544553,name);
  if ((set != (void *)0x0) && (*(int *)((int)set + 0x80) != 0)) {
    pvVar1 = sputRoom_GetCurrentRoom();
    if (set != pvVar1) {
      sputRoom_SetCurrentRoom(set,(int)name);
      Set_ActivateSectors(set);
      sputRender_SyncCamera(set,*(int *)((int)set + 0xb4));
    }
  }
  return;
}

/* ---- 0x00482820  grimlib_MakeCurrentSetup ---- */
/* Changes the camera setup of the current set: resets the set's sound parameters
   (Set_SetSoundParams: min 20, max 127, scale 8.0, pan scale 1.5, near 0.8), runs the camera change
   handler and moves every positioned sound again (PositionedSounds_UpdateAll). Original name
   grimlib_MakeCurrentSetup (the remaster's GrimFandango (Linux): aligned call in grimlib_NextSetup,
   grimlib_PreviousSetup, sputLua_MakeCurrentSetupL); was Set_ChangeSetup. */

void * grimlib_MakeCurrentSetup(uint param_1)

{
  uint uVar1;
  void *pvVar2;
  void *pvVar3;
  
  pvVar2 = sputRoom_GetCurrentRoom();
  uVar1 = *(uint *)((int)pvVar2 + 0xb0);
  pvVar3 = pvVar2;
  if (uVar1 <= param_1) {
    pvVar3 = (void *)(param_1 / uVar1);
    param_1 = param_1 % uVar1;
  }
  uVar1 = *(uint *)((int)pvVar2 + 0xb4);
  if (param_1 != uVar1) {
    *(uint *)((int)pvVar2 + 0xb4) = param_1;
    sputRoom_SetSoundParameters(pvVar2,0x41000000,0x14,0x7f,0x3fc00000,0x3f4ccccd);
    sputLua_CameraChange(uVar1,param_1);
    pvVar3 = (void *)((code *)sputRoom_RelocateSounds)();
  }
  return pvVar3;
}

/* ---- 0x00483aa0  sputRender_SyncCamera ---- */
/* Selects the setup's colormap, binds the rdCamera (setup+0x48) to the canvas, sets zoom 1.0 and
   updates it from the camera frame at setup+0x50 (300-byte setup records start at set+0xac)
   Original name sputRender_SyncCamera (the remaster's GrimFandango (Linux): the only unmatched
   caller of rdCamera_SetCanvas; the only unmatched caller of rdCamera_SetCurrent; 2 matched
   neighbours agree, 0 disagree); was Set_ApplySetupCamera. */

void __cdecl sputRender_SyncCamera(void *set,int setupIdx)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)((int)set + 0xac) + setupIdx * 300;
  iVar2 = *(int *)((int)set + 0x88);
  iVar3 = *(int *)((int)set + 0x80);
  if (*(int *)(iVar3 + iVar2 * 0x34) == 0) {
    (*g_pStd_HS->pAssertFail)(s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f)
    ;
  }
  rdroid_SetColormap(*(undefined4 *)(iVar3 + iVar2 * 0x34 + 4));
  rdCamera_SetCurrent(*(undefined4 *)(iVar1 + 0x48));
  if (g_pSputRender_Canvas != (void *)0x0) {
    rdCamera_SetCanvas(*(void **)(iVar1 + 0x48),g_pSputRender_Canvas);
  }
  rdCamera_SetAspectRatio(*(void **)(iVar1 + 0x48),1.0);
  rdCamera_Update((float *)(iVar1 + 0x50));
  return;
}

/* ---- 0x00483b50  sputRender_UseSetup ---- */
/* Makes setupIdx current: applies its camera, copies its frame into the camera actor, blits the
   background bitmap into g_pSputRender_CleanBuffer and the depth bitmap into
   g_pSputRender_CleanZBuffer (clearing it when absent), draws the object states and invalidates the
   view Original name sputRender_UseSetup (the remaster's GrimFandango (Linux): aligned call in
   sputRender_SetDisplay, sputRender_SetGamma, sputRender_Update); was Set_SwitchSetup. */

void __cdecl sputRender_UseSetup(void *set,int setupIdx)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *pvVar2;
  float *pfVar3;
  int *piVar4;
  int iVar5;
  float *pfVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (set != (void *)0x0) {
    iVar1 = *(int *)((int)set + 0xac) + setupIdx * 300;
    CacheRect_FreeAll();
    sputRender_SyncCamera(set,setupIdx);
    g_dwRenderFlags = g_dwRenderFlags & 0xfffffffc;
    g_pSputRender_Camera = (float *)(iVar1 + 0x20);
    pvVar2 = (void *)sputActor_ActorDeref(g_nCamActorIndex);
    pfVar3 = sputActor_GetOrientMatrix(pvVar2);
    pfVar6 = (float *)(iVar1 + 0x50);
    for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
      *pfVar3 = *pfVar6;
      pfVar6 = pfVar6 + 1;
      pfVar3 = pfVar3 + 1;
    }
    piVar4 = sputRoom_GetSetupBackground(set,setupIdx);
    if (piVar4 != (int *)0x0) {
      if (*piVar4 == 2) {
        sputRender_Decompress(piVar4);
        piVar4 = g_pSputRender_DecompressionBuffer;
      }
      Surface_Blit(g_pSputRender_CleanBuffer,piVar4,0,0,(int *)0x0,0);
    }
    piVar4 = sputRoom_GetSetupZBackground(set,setupIdx);
    if (piVar4 == (int *)0x0) {
      puVar7 = *(undefined4 **)((int)g_pSputRender_CleanZBuffer + 0x5c);
      for (iVar5 = 0x25800; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
      g_dwRenderFlags = g_dwRenderFlags | 2;
    }
    else if (*piVar4 == 2) {
      puVar7 = (undefined4 *)((int)g_pSputRender_CleanZBuffer + 0xc);
      puVar8 = (undefined4 *)((int)g_pSputRender_DecompressionBuffer + 0xc);
      for (iVar5 = 0x13; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      if (*(int *)((int)g_pSputRender_CleanZBuffer + 8) == 0) {
        stdDisplay_VBufferDeCompressTo(piVar4,g_pSputRender_CleanZBuffer);
      }
      else {
        stdDisplay_VBufferDeCompressTo(piVar4,g_pSputRender_DecompressionBuffer);
        Surface_Blit(g_pSputRender_CleanZBuffer,g_pSputRender_DecompressionBuffer,0,0,(int *)0x0,0);
      }
    }
    else {
      Surface_Blit(g_pSputRender_CleanZBuffer,piVar4,0,0,(int *)0x0,0);
    }
    for (pvVar2 = *(void **)(iVar1 + 0x128); pvVar2 != (void *)0x0;
        pvVar2 = *(void **)((int)pvVar2 + 0xf8)) {
      ObjectState_LoadImages((int)pvVar2);
      ObjectState_CaptureBackground(pvVar2,g_pSputRender_CleanBuffer,g_pSputRender_CleanZBuffer);
    }
    local_10 = *(uint *)((int)g_pSputRender_Canvas + 0x18);
    local_c = *(uint *)((int)g_pSputRender_Canvas + 0x1c);
    local_8 = (*(int *)((int)g_pSputRender_Canvas + 0x20) -
              *(int *)((int)g_pSputRender_Canvas + 0x18)) + 1;
    local_4 = (*(int *)((int)g_pSputRender_Canvas + 0x24) -
              *(int *)((int)g_pSputRender_Canvas + 0x1c)) + 1;
    MarkDirtyRect((int *)&local_10,1);
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00485780  Set_DrawDebugLights ---- */
/* Debug overlay of every light in the set: point/omni lights as a line and circle, spot lights as a
   cone frustum */

void Set_DrawDebugLights(int param_1)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float *pfVar2;
  float *vec;
  #define local_74 (*(uint *)(_frame + (0x90 - 0x74)))
  #define local_70 (*(uint *)(_frame + (0x90 - 0x70)))
  #define local_6c (*(uint *)(_frame + (0x90 - 0x6c)))
  #define local_68 (*(uint *)(_frame + (0x90 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0x90 - 0x64)))
  #define local_60 (*(float *)(_frame + (0x90 - 0x60)))
  #define local_5c (*(float *)(_frame + (0x90 - 0x5c)))
  #define local_58 (*(float (*)[3])(_frame + (0x90 - 0x58)))
  #define local_4c (*(float *)(_frame + (0x90 - 0x4c)))
  #define local_48 (*(float *)(_frame + (0x90 - 0x48)))
  #define local_44 (*(float (*)[2])(_frame + (0x90 - 0x44)))
  #define local_3c (*(float *)(_frame + (0x90 - 0x3c)))
  #define local_38 (*(float (*)[2])(_frame + (0x90 - 0x38)))
  #define local_30 (*(float (*)[12])(_frame + (0x90 - 0x30)))
  
  local_70 = 0;
  if (*(int *)(param_1 + 0xb8) != 0) {
    pfVar2 = (float *)(param_1 + 0x11c);
    do {
      if (PUN(int,(float)pfVar2[-0xc]) < 3) {
        local_6c = PUN(uint,(float)pfVar2[-0x10]);
        local_68 = PUN(uint,(float)pfVar2[-0xf]);
        local_64 = 0;
        rdPrimit3_DrawLine(pfVar2 + -0x10,(float *)&local_6c,(int *)0x0,(int *)0x0,(int *)0x0,
                           (int *)0x0,(uint)PIECE(UINT_008c97c8,2,2),0xffffffff);
        rdPrimit3_DrawPoint(pfVar2 + -0x10,*pfVar2,0x41980000,(uint)PIECE(UINT_008c97c8,2,2),0xffffffff);
      }
      else {
        local_68 = PUN(uint,(float)(pfVar2[-9] + pfVar2[-0xf]));
        local_64 = PUN(uint,(float)(pfVar2[-8] + pfVar2[-0xe]));
        local_6c = PUN(uint,(float)(pfVar2[-10] + pfVar2[-0x10]));
        rdMatrix_LookAt(local_30,pfVar2 + -0x10,&local_6c,0);
        local_5c = pfVar2[-7] * 0.1;
        vec = &local_60;
        local_60 = (1.0 - pfVar2[-2]) * local_5c;
        local_48 = -local_60;
        iVar1 = 4;
        local_58[0] = local_60;
        local_58[1] = local_60;
        local_58[2] = local_5c;
        local_44[0] = local_5c;
        local_44[1] = local_48;
        local_3c = local_48;
        local_38[0] = local_5c;
        local_38[1] = local_60;
        do {
          Vec3_Rotate3x3(vec,local_30);
          rdPrimit3_DrawLine(pfVar2 + -0x10,vec,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                             (uint)PIECE(UINT_008c97cc,2,2),0xffffffff);
          vec = vec + 3;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
        rdPrimit3_DrawLine(&local_60,local_58 + 1,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                           (uint)PIECE(UINT_008c97cc,2,2),0xffffffff);
        rdPrimit3_DrawLine(local_58 + 1,&local_48,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                           (uint)PIECE(UINT_008c97cc,2,2),0xffffffff);
        rdPrimit3_DrawLine(&local_48,&local_3c,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                           (uint)PIECE(UINT_008c97cc,2,2),0xffffffff);
        rdPrimit3_DrawLine(&local_3c,&local_60,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,
                           (uint)PIECE(UINT_008c97cc,2,2),0xffffffff);
      }
      local_70 = local_70 + 1;
      pfVar2 = pfVar2 + 0x1a;
    } while (local_70 < *(uint *)(param_1 + 0xb8));
  }
  return;
}
#undef local_30
#undef local_38
#undef local_3c
#undef local_44
#undef local_48
#undef local_4c
#undef local_58
#undef local_5c
#undef local_60
#undef local_64
#undef local_68
#undef local_6c
#undef local_70
#undef local_74


/* ---- 0x004859c0  Set_DrawDebugCameras ---- */
void __cdecl Set_DrawDebugCameras(void *set,uint setupIdx)

{
  int iVar1;
  uint uVar2;
  
  if (setupIdx == 0xffffffff) {
    uVar2 = 0;
    iVar1 = *(int *)((int)set + 0xac);
    if (*(int *)((int)set + 0xb0) != 0) {
      do {
        if (uVar2 != *(uint *)((int)set + 0xb4)) {
          Setup_DrawDebugCamera(iVar1);
        }
        uVar2 = uVar2 + 1;
        iVar1 = iVar1 + 300;
      } while (uVar2 < *(uint *)((int)set + 0xb0));
      return;
    }
  }
  else {
    ((code *)Setup_DrawDebugCamera)(*(int *)((int)set + 0xac) + (setupIdx % *(uint *)((int)set + 0xb0)) * 300)
    ;
  }
  return;
}

/* ---- 0x004a4010  sputRoom_SetSoundParameters ---- */
/* Original name sputRoom_SetSoundParameters (the remaster's GrimFandango (Linux): aligned call in
   grimlib_MakeCurrentSetup, sputLua_SetSoundParametersL, sputRoom_SetCurrentRoom); was
   Set_SetSoundParams. */

void sputRoom_SetSoundParameters
               (int param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4,
               undefined4 param_5,undefined4 param_6)

{
  *(undefined1 *)(param_1 + 0x1af8) = param_3;
  *(undefined4 *)(param_1 + 0x1afc) = param_2;
  *(undefined1 *)(param_1 + 0x1af9) = param_4;
  *(undefined4 *)(param_1 + 0x1b00) = param_5;
  *(undefined4 *)(param_1 + 0x1b04) = param_6;
  return;
}

/* ---- 0x004a4050  sputRoom_GetSoundParameters ---- */
/* Fills the default 3D sound parameters (min distance, volume, pan...) from the set Original name
   sputRoom_GetSoundParameters (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_GetSoundParameters; 3 matched neighbours agree, 0 disagree); was Set_GetSoundParams. */

void __cdecl
sputRoom_GetSoundParameters(void *set,float *minVol,char *maxVol,char *c,float *d,float *e)

{
  *minVol = *(float *)((int)set + 0x1afc);
  *maxVol = *(char *)((int)set + 0x1af8);
  *c = *(char *)((int)set + 0x1af9);
  *d = *(float *)((int)set + 0x1b00);
  *e = *(float *)((int)set + 0x1b04);
  return;
}

/* ---- 0x004a40f0  sputRoom_SetCurrentRoom ---- */
/* Releases the previous set's resources (unless locked), references the new one, loads its
   resources and resets the sound parameters Original name sputRoom_SetCurrentRoom (the remaster's
   GrimFandango (Linux): the only unmatched caller of Set_LoadResources; 4 matched neighbours agree,
   1 disagree); was Set_SetCurrent. */

void __cdecl sputRoom_SetCurrentRoom(void *set,int param_2)

{
  if ((g_dwSputRoom_pCurrentRoom == 0) || (g_pCurrentSet != set)) {
    if (g_dwSputRoom_pCurrentRoom != 0) {
      sputRoom_UnReference(g_pCurrentSet);
      Res_RemoveReference(&g_dwSputRoom_pCurrentRoom);
      g_szSputRoom_CurrentRoomName[0] = '\0';
    }
    if (set != (void *)0x0) {
      Res_SetReference(&g_dwSputRoom_pCurrentRoom,set,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,
                       0x15d);
      if (g_dwSputRoom_pCurrentRoom == 0) {
        (*g_pStd_HS->pAssertFail)(s_Bad_room_Reference_004ec62c,s_main_sputResource_h_004e80a8,0xa4)
        ;
      }
      sputRoom_LoadResources(g_pCurrentSet);
      strncpy(g_szSputRoom_CurrentRoomName,set,0x20);
      sputRoom_SetSoundParameters(set,0x41000000,0x14,0x7f,0x3fc00000,0x3f4ccccd);
    }
  }
  return;
}

/* ---- 0x004a41b0  sputRoom_GetCurrentRoom ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name sputRoom_GetCurrentRoom (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetAmbientLight; 18 matched neighbours agree, 0 disagree); was Set_GetCurrent. */

void * sputRoom_GetCurrentRoom(void)

{
  return (void *)(-(uint)(g_dwSputRoom_pCurrentRoom != 0) & (uint)g_pCurrentSet);
}

/* ---- 0x004a41d0  sputRoom_GetCurrentRoomName ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Original name sputRoom_GetCurrentRoomName (the remaster's GrimFandango (Linux): aligned call in
   sputLua_GetCurrentSetupL, sputText_CreateActorText); was Set_GetCurrentName. */

char * sputRoom_GetCurrentRoomName(void)

{
  return g_szSputRoom_CurrentRoomName;
}

/* ---- 0x004a41e0  sputRoom_Save ---- */
/* Writes every referenced set (current setup, lock, object states per setup), the current set, its
   sound parameters and the sector states Original name sputRoom_Save (the remaster's GrimFandango
   (Linux): aligned call in sputRoom_Initialize); was Set_SaveState. */

int __cdecl sputRoom_Save(void *writeFn)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  code *pcVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define pvStack_c (*(void **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x30 - 0x4)))
  
  local_8 = 0;
  Res_GetFirstType(&local_14,&local_10,0x20544553);
  pcVar2 = writeFn;
  while (writeFn = pcVar2, local_14 != 0) {
    iVar4 = Res_NumRefs(local_10);
    if (0 < iVar4) {
      local_8 = local_8 + 1;
    }
    Res_GetNextType(&local_14,&local_10,0x20544553);
    pcVar2 = writeFn;
  }
  iVar4 = (*pcVar2)(&local_8,4);
  if (iVar4 == 0) {
    Res_GetFirstType(&local_14,&local_10,0x20544553);
    uVar3 = local_10;
    do {
      if (local_14 == 0) {
        pvStack_c = sputRoom_GetCurrentRoom();
        (*pcVar2)(&pvStack_c,4);
        if (pvStack_c != (void *)0x0) {
          (*pcVar2)((int)pvStack_c + 0x1af8,1);
          (*pcVar2)((int)pvStack_c + 0x1af9,1);
          (*pcVar2)((int)pvStack_c + 0x1afc,4);
          (*pcVar2)((int)pvStack_c + 0x1b00,4);
          (*pcVar2)((int)pvStack_c + 0x1b04,4);
          for (pvVar1 = g_pWalkPlane_wp_head; pvVar1 != (void *)0x0;
              pvVar1 = *(void **)((int)pvVar1 + 0x70)) {
            writeFn = *(void **)((int)pvVar1 + 0x20);
            (*pcVar2)(&writeFn,4);
            writeFn = *(void **)((int)pvVar1 + 0x28);
            (*pcVar2)(&writeFn,4);
            writeFn = *(void **)((int)pvVar1 + 0x24);
            (*pcVar2)(&writeFn,4);
            writeFn = *(void **)((int)pvVar1 + 0x2c);
            (*pcVar2)(&writeFn,4);
            iStack_4 = *(int *)((int)pvVar1 + 0x30);
            (*pcVar2)(&iStack_4,4);
          }
        }
        return 0;
      }
      iVar5 = 0;
      local_10 = uVar3;
      iVar4 = Res_NumRefs(uVar3);
      if (iVar4 != 0) {
        (*pcVar2)(&local_10,4);
        (*pcVar2)(uVar3 + 0xb4,4);
        (*pcVar2)(uVar3 + 0x1ac0,4);
        iStack_4 = 0;
        if (0 < *(int *)(uVar3 + 0xb0)) {
          do {
            iVar6 = iVar5 + *(int *)(uVar3 + 0xac);
            writeFn = (void *)0x0;
            for (iVar4 = *(int *)(iVar6 + 0x128); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0xf8)) {
              writeFn = (void *)((int)writeFn + 1);
            }
            iVar4 = (*pcVar2)(&writeFn,4);
            if (iVar4 != 0) {
              return 1;
            }
            for (iVar4 = *(int *)(iVar6 + 0x128); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0xf8)) {
              (*pcVar2)(iVar4 + 4,4);
              (*pcVar2)(iVar4 + 0x20,0x20);
              (*pcVar2)(iVar4 + 0x94,0x20);
              (*pcVar2)(iVar4 + 0x7c,4);
              if (*(int *)(iVar4 + 0x40) == 0) {
                (*g_pStd_HS->pAssertFail)
                          (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
              }
              (*pcVar2)(*(int *)(iVar4 + 0x44) + 0x68,4);
              (*pcVar2)(iVar4 + 0xec,4);
            }
            iStack_4 = iStack_4 + 1;
            iVar5 = iVar5 + 300;
          } while (iStack_4 < *(int *)(uVar3 + 0xb0));
        }
      }
      Res_GetNextType(&local_14,&local_10,0x20544553);
      uVar3 = local_10;
    } while( true );
  }
  return 1;
}
#undef iStack_4
#undef local_10
#undef local_14
#undef local_8
#undef pvStack_c


/* ---- 0x004a44e0  sputRoom_Restore ---- */
/* Source: Engine/sputRoom.cpp (lines 528-535, from __FILE__/__LINE__ passed to the allocator)
   Original name sputRoom_Restore (the remaster's GrimFandango (Linux): the only unmatched caller of
   ObjectState_SendToBack; 4 matched neighbours agree, 0 disagree); was Set_RestoreState. */

int __cdecl sputRoom_Restore(void *readFn)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  int iVar3;
  void *pvVar4;
  void *pvVar5;
  int iVar6;
  #define uStack_74 (*(uint *)(_frame + (0x90 - 0x74)))
  #define iStack_70 (*(int *)(_frame + (0x90 - 0x70)))
  #define iStack_6c (*(int *)(_frame + (0x90 - 0x6c)))
  #define iStack_68 (*(int *)(_frame + (0x90 - 0x68)))
  #define fStack_64 (*(float *)(_frame + (0x90 - 0x64)))
  #define local_60 (*(int *)(_frame + (0x90 - 0x60)))
  #define pvStack_5c (*(void **)(_frame + (0x90 - 0x5c)))
  #define iStack_58 (*(int *)(_frame + (0x90 - 0x58)))
  #define iStack_54 (*(int *)(_frame + (0x90 - 0x54)))
  #define iStack_50 (*(int *)(_frame + (0x90 - 0x50)))
  #define uStack_4c (*(undefined4 *)(_frame + (0x90 - 0x4c)))
  #define iStack_48 (*(int *)(_frame + (0x90 - 0x48)))
  #define pvStack_44 (*(void **)(_frame + (0x90 - 0x44)))
  #define acStack_40 (*(char (*)[32])(_frame + (0x90 - 0x40)))
  #define acStack_20 (*(char (*)[32])(_frame + (0x90 - 0x20)))
  
  iVar3 = (*(code *)readFn)(&local_60,4);
  if (iVar3 != 0) {
    return 1;
  }
  fStack_64 = 0.0;
  if (0 < local_60) {
    do {
      (*(code *)readFn)(&pvStack_5c,4);
      pvVar4 = Res_HandleFromSerialNumber(pvStack_5c);
      if (pvVar4 == (void *)0x0) {
        return 1;
      }
      (*(code *)readFn)((int)pvVar4 + 0xb4,4);
      if (g_dwSputRoom_pCurrentRoom != 0) {
        Res_RemoveReference(&g_dwSputRoom_pCurrentRoom);
      }
      Res_SetReference(&g_dwSputRoom_pCurrentRoom,pvVar4,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0
                       ,0x210);
      if (g_dwSputRoom_pCurrentRoom == 0) {
        (*g_pStd_HS->pAssertFail)(s_Bad_room_Reference_004ec62c,s_main_sputResource_h_004e80a8,0xa4)
        ;
      }
      sputRoom_LoadResources(g_pCurrentSet);
      strncpy(g_szSputRoom_CurrentRoomName,pvVar4,0x20);
      (*(code *)readFn)(&iStack_58,4);
      if (iStack_58 != 0) {
        Res_SetReference((void *)((int)pvVar4 + 0x1ac0),pvVar4,
                         s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x217);
      }
      iStack_70 = 0;
      if (0 < *(int *)((int)pvVar4 + 0xb0)) {
        iStack_6c = 0;
        do {
          iVar3 = iStack_6c + *(int *)((int)pvVar4 + 0xac);
          (*(code *)readFn)(&uStack_74,4);
          iStack_68 = 0;
          if (0 < (int)uStack_74) {
            do {
              (*(code *)readFn)(&iStack_50,4);
              (*(code *)readFn)(acStack_20,0x20);
              (*(code *)readFn)(acStack_40,0x20);
              (*(code *)readFn)(&iStack_54,4);
              (*(code *)readFn)(&uStack_4c,4);
              (*(code *)readFn)(&iStack_48,4);
              sputRoom_AddObjectState(iStack_70,iStack_50,acStack_20,acStack_40,iStack_54);
              iVar6 = *(int *)(iVar3 + 0x128);
              iVar1 = *(int *)(iVar6 + 0x40);
              if (iVar1 != 0) {
                if (iVar1 == 0) {
                  (*g_pStd_HS->pAssertFail)
                            (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
                }
                *(undefined4 *)(*(int *)(iVar6 + 0x44) + 0x68) = uStack_4c;
              }
              iVar6 = *(int *)(iVar3 + 0x128);
              iVar1 = *(int *)(iVar6 + 0xb4);
              if (iVar1 != 0) {
                if (iVar1 == 0) {
                  (*g_pStd_HS->pAssertFail)
                            (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
                }
                *(int *)(*(int *)(iVar6 + 0xb8) + 0x68) = iStack_48;
              }
              iStack_68 = iStack_68 + 1;
            } while (iStack_68 < (int)uStack_74);
          }
          iVar6 = 0;
          if (0 < (int)uStack_74) {
            do {
              pvVar5 = ObjectState_MoveToBack(*(void **)(iVar3 + 0x128),*(void **)(iVar3 + 0x128));
              *(void **)(iVar3 + 0x128) = pvVar5;
              iVar6 = iVar6 + 1;
            } while (iVar6 < (int)uStack_74);
          }
          iStack_70 = iStack_70 + 1;
          iStack_6c = iStack_6c + 300;
        } while (iStack_70 < *(int *)((int)pvVar4 + 0xb0));
      }
      fStack_64 = PUN(float,(PUN(int,(float)fStack_64) + 1));
    } while (PUN(int,(float)fStack_64) < local_60);
  }
  (*(code *)readFn)(&pvStack_44,4);
  pvVar4 = Res_HandleFromSerialNumber(pvStack_44);
  sputRoom_SetCurrentRoom(pvVar4,(int)pvVar4);
  if (pvVar4 != (void *)0x0) {
    grimlib_MakeCurrentSetup(*(undefined4 *)((int)pvVar4 + 0xb4));
    Set_ActivateSectors(pvVar4);
    (*(code *)readFn)((int)pvVar4 + 0x1af8,1);
    (*(code *)readFn)((int)pvVar4 + 0x1af9,1);
    (*(code *)readFn)((int)pvVar4 + 0x1afc,4);
    (*(code *)readFn)((int)pvVar4 + 0x1b00,4);
    (*(code *)readFn)((int)pvVar4 + 0x1b04,4);
    for (pvVar4 = g_pWalkPlane_wp_head; pvVar4 != (void *)0x0;
        pvVar4 = *(void **)((int)pvVar4 + 0x70)) {
      (*(code *)readFn)(&iStack_48,4);
      if (iStack_48 == *(int *)((int)pvVar4 + 0x20)) {
        (*(code *)readFn)(&uStack_74,4);
        *(uint *)((int)pvVar4 + 0x28) = uStack_74;
        (*(code *)readFn)(&uStack_74,4);
        Sector_SetSavedType(pvVar4,uStack_74);
        (*(code *)readFn)(&uStack_74,4);
        *(uint *)((int)pvVar4 + 0x2c) = uStack_74;
        (*(code *)readFn)(&fStack_64,4);
        fVar2 = fStack_64;
        if (fStack_64 == 0.0) {
          fVar2 = 0.005;
        }
        *(float *)((int)pvVar4 + 0x30) = fVar2;
      }
    }
  }
  return 0;
}
#undef acStack_20
#undef acStack_40
#undef fStack_64
#undef iStack_48
#undef iStack_50
#undef iStack_54
#undef iStack_58
#undef iStack_68
#undef iStack_6c
#undef iStack_70
#undef local_60
#undef pvStack_44
#undef pvStack_5c
#undef uStack_4c
#undef uStack_74


/* ---- 0x004a49a0  sputResource_SetHandler ---- */
/* Resource type 'SET ' loader (ResType_SetHandler op 1): allocates the 0x1b08-byte set record,
   initialises it, parses the .set file, links it to the set-name entry and re-attaches the walkers
   of the actors already in that set. Original name sputResource_SetHandler (the remaster's
   GrimFandango (Linux): the only unmatched caller of SetFile_Parse; 1 matched neighbours agree, 0
   disagree); was Set_LoadFile. */

undefined4 * sputResource_SetHandler(char *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  void *pvVar3;
  int iVar4;
  undefined4 *puVar5;
  
  puVar2 = (undefined4 *)
           (*g_pSputRoomHS->pAlloc)(0x1b08,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x306);
  if (puVar2 != (undefined4 *)0x0) {
    puVar5 = puVar2;
    for (iVar4 = 0x6c2; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    Set_InitRecord(puVar2);
    iVar4 = sputRoom_LoadRoom(param_1,puVar2);
    if (iVar4 != 0) {
      pvVar3 = (void *)Set_FindNameInList(param_1);
      if (pvVar3 == (void *)0x0) {
        pvVar3 = Set_NormalizeName(param_1);
      }
      puVar2[0x6af] = pvVar3;
      for (piVar1 = *(int **)((int)pvVar3 + 0x80); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[2])
      {
        iVar4 = *(int *)((int)g_pActors + *piVar1 * 0xa8 + 0xa4);
        if (((iVar4 != 0) && (*(void **)(iVar4 + 0x1b4) != (void *)0x0)) &&
           (*(int *)(iVar4 + 0x1b8) != 0)) {
          Puck_Validate(*(void **)(iVar4 + 0x1b4));
        }
      }
      return puVar2;
    }
  }
  Set_Free(puVar2);
  return (undefined4 *)0x0;
}

/* ---- 0x004a4a70  Set_InitRecord ---- */
/* Zeroes a 0x1b08-byte set record and fills the defaults (empty names, size field +0x1af4). */

void Set_InitRecord(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0x6c2; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[0x2e] = 0;
  param_1[0x2c] = 0;
  param_1[0x2b] = 0;
  param_1[0x2d] = 0;
  param_1[0x22] = 0;
  param_1[0x21] = 1;
  param_1[0x20] = 0;
  *(undefined1 *)(param_1 + 0x23) = 0;
  strncpy(param_1 + 0x23,&DAT_004ec60c,0x1f);
  *(undefined1 *)((int)param_1 + 0xab) = 0;
  strncpy(param_1,&DAT_004f5a98,0x1f);
  *(undefined1 *)((int)param_1 + 0x1f) = 0;
  param_1[0x6bd] = 0x1b08;
  return;
}

/* ---- 0x004a4b40  sputRoom_UnReference ---- */
/* Drops the colormap, background, depth and object state references of an unlocked set Original
   name sputRoom_UnReference (the remaster's GrimFandango (Linux): aligned call in
   sputRoom_SetCurrentRoom); was Set_ReleaseResources. */

void __cdecl sputRoom_UnReference(void *set)

{
  int iVar1;
  int iVar2;
  void *p;
  int iVar3;
  int iVar4;
  
  if (*(int *)((int)set + 0x1ac0) == 0) {
    if ((*(int *)((int)set + 0x80) != 0) && (iVar3 = 0, 0 < *(int *)((int)set + 0x84))) {
      iVar4 = 0;
      do {
        Res_RemoveReference((void *)(*(int *)((int)set + 0x80) + iVar4));
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + 0x34;
      } while (iVar3 < *(int *)((int)set + 0x84));
    }
    iVar3 = 0;
    if (0 < *(int *)((int)set + 0xb0)) {
      iVar4 = 0;
      do {
        Res_RemoveReference((void *)(*(int *)((int)set + 0xac) + 0xc0 + iVar4));
        Res_RemoveReference((void *)(*(int *)((int)set + 0xac) + 0xf4 + iVar4));
        iVar1 = *(int *)((int)set + 0xac);
        iVar2 = *(int *)(iVar4 + 0x128 + iVar1);
        while (iVar2 != 0) {
          p = *(void **)(iVar4 + 0x128 + iVar1);
          *(undefined4 *)(iVar4 + 0x128 + iVar1) = *(undefined4 *)((int)p + 0xf8);
          ObjectState_UnloadBitmaps((int)p);
          if (p != (void *)0x0) {
            ObjectState_Destruct((int)p);
            Plat_Free(p);
          }
          iVar1 = *(int *)((int)set + 0xac);
          iVar2 = *(int *)(iVar4 + 0x128 + iVar1);
        }
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + 300;
      } while (iVar3 < *(int *)((int)set + 0xb0));
    }
  }
  return;
}

/* ---- 0x004a4c40  Set_Free ---- */
/* Resource type 'SET ' free handler: Set_FreeContents, then frees the set record. */

void Set_Free(undefined4 param_1)

{
  Set_FreeContents(param_1);
  (*g_pSputRoomHS->pFree)(param_1);
  return;
}

/* ---- 0x004a4c60  Set_FreeContents ---- */
/* Releases a set's resources, colormap array, setups and sectors and removes its actor list
   (killing the shadows of the actors in it). */

void Set_FreeContents(char *param_1)

{
  int iVar1;
  int *piVar2;
  
  sputRoom_UnReference(param_1);
  if (*(int *)(param_1 + 0x80) != 0) {
    (*g_pSputRoomHS->pFree)(*(int *)(param_1 + 0x80));
  }
  Set_FreeSetups(param_1);
  Set_FreeSectors(param_1);
  iVar1 = *(int *)(param_1 + 0x1abc);
  if (iVar1 != 0) {
    piVar2 = *(int **)(iVar1 + 0x80);
    while (piVar2 != (int *)0x0) {
      sputActor_ResetShadows((void *)((int)g_pActors + *piVar2 * 0xa8));
      sputRoom_RemoveActor(param_1,(void *)((int)g_pActors + **(int **)(iVar1 + 0x80) * 0xa8));
      piVar2 = *(int **)(iVar1 + 0x80);
    }
    SetActorList_Free(iVar1);
    param_1[0x1abc] = '\0';
    param_1[0x1abd] = '\0';
    param_1[0x1abe] = '\0';
    param_1[0x1abf] = '\0';
  }
  return;
}

/* ---- 0x004a4d10  Set_FreeSetups ---- */
/* Frees every setup (300-byte records at set+0xac, count at +0xb0) and the array. */

void Set_FreeSetups(int param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (*(int *)(param_1 + 0xb0) != 0) {
    iVar1 = 0;
    do {
      Set_FreeSetup(param_1,*(int *)(param_1 + 0xac) + iVar1);
      uVar2 = uVar2 + 1;
      iVar1 = iVar1 + 300;
    } while (uVar2 < *(uint *)(param_1 + 0xb0));
    if ((*(uint *)(param_1 + 0xb0) != 0) && (*(int *)(param_1 + 0xac) != 0)) {
      (*g_pSputRoomHS->pFree)(*(int *)(param_1 + 0xac));
    }
  }
  *(undefined4 *)(param_1 + 0xac) = 0;
  *(undefined4 *)(param_1 + 0xb0) = 0;
  return;
}

/* ---- 0x004a4d80  Set_FreeSetup ---- */
/* Frees one setup: camera (rdCamera_Free), rdThing, and clears the pointer fields. */

void Set_FreeSetup(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0x48) != 0) {
    rdCamera_Free(*(int *)(param_2 + 0x48));
    *(undefined4 *)(param_2 + 0x48) = 0;
  }
  if (*(int *)(param_2 + 0x4c) != 0) {
    rdThing_Free(*(int *)(param_2 + 0x4c));
    *(undefined4 *)(param_2 + 0x4c) = 0;
  }
  *(undefined4 *)(param_2 + 0x128) = 0;
  return;
}

/* ---- 0x004a4fe0  sputRoom_LoadResources ---- */
/* Loads colormaps (set+0x80, 0x34 each), each setup's background/depth bitmaps, creates the
   rdCamera (setup+0x48) and rdThing (+0x4c), builds the camera basis and adds the set's lights
   Original name sputRoom_LoadResources (the remaster's GrimFandango (Linux): strings:
   'dfltcmp.cmp'); was Set_LoadResources. */

int __cdecl sputRoom_LoadResources(void *set)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  void *pvVar2;
  int iVar3;
  void *pvVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int *ref;
  int iVar8;
  int *piVar9;
  float *pfVar10;
  char *pcVar11;
  char *pcVar12;
  int *piVar13;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pvVar2 = set;
  *(undefined4 *)((int)set + 0x1af4) = 0x1b08;
  iVar5 = *(int *)((int)set + 0xac);
  SoundsFloodMusicBuffer();
  uVar7 = 0;
  if (*(int *)((int)set + 0x84) != 0) {
    iVar8 = 0;
    do {
      if (*(int *)(iVar8 + *(int *)((int)set + 0x80)) == 0) {
        iVar3 = _stricmp((char *)((int)set + 0x8c),&DAT_004ec60c);
        if (iVar3 != 0) {
          pvVar4 = sputResource_Alloc(0x50414d43,(char *)((int)set + 0x8c));
          Res_SetReference((void *)(iVar8 + *(int *)((int)set + 0x80)),pvVar4,
                           s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x6dc);
        }
        if (*(int *)(iVar8 + *(int *)((int)set + 0x80)) == 0) {
          pvVar4 = sputResource_Alloc(0x50414d43,s_dfltcmp_cmp_004ec710);
          Res_SetReference((void *)(iVar8 + *(int *)((int)set + 0x80)),pvVar4,
                           s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x6e3);
          if (*(int *)(iVar8 + *(int *)((int)set + 0x80)) == 0) {
            return 0;
          }
        }
      }
      else {
        Res_Touch(*(void **)(iVar8 + *(int *)((int)set + 0x80) + 4));
      }
      uVar7 = uVar7 + 1;
      iVar8 = iVar8 + 0x34;
    } while (uVar7 < *(uint *)((int)set + 0x84));
  }
  local_4 = 0;
  if (*(int *)((int)set + 0xb0) == 0) {
    return 1;
  }
  ref = (int *)(iVar5 + 0xc0);
  do {
    if (g_nSkipSetupBitmaps == 0) {
      if (*ref == 0) {
        iVar5 = _stricmp(ref + -0x10,&DAT_004ec60c);
        if (iVar5 != 0) {
          pvVar4 = sputResource_Alloc(0x444e4b42,(char *)(ref + -0x10));
          Res_SetReference(ref,pvVar4,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x702);
        }
        if (*ref == 0) {
          pvVar4 = sputResource_Alloc(0x444e4b42,s_dfltroom_bm_004ec5d4);
          Res_SetReference(ref,pvVar4,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x708);
          if (*ref == 0) {
            return 0;
          }
          uVar7 = 0xffffffff;
          pcVar11 = &DAT_004ec60c;
          do {
            pcVar12 = pcVar11;
            if (uVar7 == 0) break;
            uVar7 = uVar7 - 1;
            pcVar12 = pcVar11 + 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar12;
          } while (cVar1 != '\0');
          uVar7 = ~uVar7;
          piVar9 = (int *)(pcVar12 + -uVar7);
          piVar13 = ref + -0x10;
          for (uVar6 = uVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
            *piVar13 = *piVar9;
            piVar9 = piVar9 + 1;
            piVar13 = piVar13 + 1;
          }
          for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(char *)piVar13 = (char)*piVar9;
            piVar9 = (int *)((int)piVar9 + 1);
            piVar13 = (int *)((int)piVar13 + 1);
          }
          *(undefined1 *)(ref + -8) = 0;
          goto LAB_004a51bd;
        }
      }
      else {
        Res_Touch((void *)ref[1]);
LAB_004a51bd:
        if (*ref == 0) {
          (*g_pStd_HS->pAssertFail)
                    (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
        }
      }
      stdBitmap_ConvertToDisplay((void *)ref[1]);
      if ((char)ref[-8] != '\0') {
        piVar9 = ref + 0xd;
        if ((ref[0xd] == 0) &&
           (pvVar4 = sputResource_Alloc(0x4655425a,(char *)(ref + -8)), pvVar4 != (void *)0x0)) {
          Res_SetReference(piVar9,pvVar4,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x720);
        }
        if ((*piVar9 != 0) && (Res_Touch((void *)ref[0xe]), *piVar9 == 0)) {
          (*g_pStd_HS->pAssertFail)
                    (s_Bad_ZBuffer_Reference_004ec614,s_main_sputResource_h_004e80a8,0x95);
        }
      }
    }
    if (ref[-0x1e] == 0) {
      pvVar4 = rdCamera_New(PUN(float,ref[-0x21]),1,PUN(float,ref[-0x20]),PUN(float,ref[-0x1f]),1.0);
      ref[-0x1e] = (int)pvVar4;
      if (pvVar4 == (void *)0x0) {
        return 0;
      }
      iVar5 = rdThing_New(0);
      ref[-0x1d] = iVar5;
      rdThing_SetCamera(iVar5,ref[-0x1e]);
      rdMatrix_LookAt(ref + -0x1c,ref + -0x28,ref + -0x25,ref[-0x22]);
      set = (void *)0x0;
      if (*(int *)((int)pvVar2 + 0xb8) != 0) {
        pvVar4 = (void *)((int)pvVar2 + 0xe8);
        pfVar10 = (float *)((int)pvVar2 + 0x108);
        do {
          rdLight_SetAngles(pfVar10 + -8,*pfVar10,pfVar10[2]);
          rdCamera_AddLight((void *)ref[-0x1e],pvVar4,(float *)((int)pvVar4 + -0xc));
          set = (void *)((int)set + 1);
          pfVar10 = pfVar10 + 0x1a;
          pvVar4 = (void *)((int)pvVar4 + 0x68);
        } while (set < *(void **)((int)pvVar2 + 0xb8));
      }
    }
    local_4 = local_4 + 1;
    ref = ref + 0x4b;
    if (*(uint *)((int)pvVar2 + 0xb0) <= local_4) {
      return 1;
    }
  } while( true );
}
#undef local_4
#undef local_8


/* ---- 0x004a54a0  Set_RegisterHandle ---- */
/* Adds a set to the 32-entry handle table at g_SetHandles (0x24 bytes each) if not already present
    */

int __cdecl Set_RegisterHandle(char *name,void *fn)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = Set_FindHandle(name);
  if (uVar1 == 0xffffffff) {
    if (0x1f < (int)UINT_008cb0a4) {
      return 0;
    }
    uVar1 = UINT_008cb0a4;
    UINT_008cb0a4 = UINT_008cb0a4 + 1;
  }
  iVar2 = uVar1 * 0x24;
  strncpy(&DAT_008cac08 + iVar2,name,0x1f);
  (&DAT_008cac27)[iVar2] = 0;
  *(void **)(&DAT_008cac28 + iVar2) = fn;
  return 1;
}

/* ---- 0x004a5500  Set_FindHandle ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int Set_FindHandle(char *name)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  
  iVar2 = 0;
  if ((int)UINT_008cb0a4 < 1) {
    return -1;
  }
  puVar3 = &DAT_008cac08;
  do {
    iVar1 = _stricmp(puVar3,name);
    if (iVar1 == 0) {
      return iVar2;
    }
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 0x24;
  } while (iVar2 < (int)UINT_008cb0a4);
  return -1;
}

/* ---- 0x004a55d0  Set_IsHandleValid ---- */
int Set_IsHandleValid(char *param_1)

{
  int iVar1;
  
  iVar1 = Set_FindHandle(param_1);
  if (iVar1 == -1) {
    return true;
  }
  iVar1 = (**(code **)(&DAT_008cac28 + iVar1 * 0x24))();
  return iVar1 != 0;
}

/* ---- 0x004a60a0  Set_GetActorListByName ---- */
/* Returns the {actorIndex, ?, next} list of actors placed in the named set */

void * __cdecl Set_GetActorListByName(char *setName)

{
  int iVar1;
  
  iVar1 = Set_FindNameInList(setName);
  if (iVar1 != 0) {
    return *(void **)(iVar1 + 0x80);
  }
  return (void *)0x0;
}

/* ---- 0x004a60c0  Set_FindNameInList ---- */
/* Case-insensitive lookup in the linked set-name list */

void * Set_FindNameInList(int param_1)

{
  int iVar1;
  void *pvVar2;
  
  if ((param_1 != 0) && (pvVar2 = g_pRoomList, g_pRoomList != (void *)0x0)) {
    do {
      iVar1 = _stricmp(pvVar2,param_1);
      if (iVar1 == 0) {
        return pvVar2;
      }
      pvVar2 = *(void **)((int)pvVar2 + 0x84);
    } while (pvVar2 != (void *)0x0);
    return (void *)0x0;
  }
  return (void *)0x0;
}

/* ---- 0x004a6100  Set_NormalizeName ---- */
/* sputRoom.cpp: strips the path and extension of a set name into a static buffer */

void * __cdecl Set_NormalizeName(char *setName)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  pcVar2 = (char *)(*g_pSputRoomHS->pAlloc)(0x88,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0xa32);
  pcVar6 = pcVar2;
  for (iVar3 = 0x22; iVar3 != 0; iVar3 = iVar3 + -1) {
    pcVar6[0] = '\0';
    pcVar6[1] = '\0';
    pcVar6[2] = '\0';
    pcVar6[3] = '\0';
    pcVar6 = pcVar6 + 4;
  }
  uVar4 = 0xffffffff;
  do {
    pcVar6 = setName;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar6 = setName + 1;
    cVar1 = *setName;
    setName = pcVar6;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar6 = pcVar6 + -uVar4;
  pcVar7 = pcVar2;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  *(void **)(pcVar2 + 0x84) = g_pRoomList;
  g_pRoomList = pcVar2;
  return pcVar2;
}

/* ---- 0x004a7100  Set_FreeSectors ---- */
/* Deactivates the set's sectors and frees every sector in g_pWalkPlane_wp_head (Sector_Unlink +
   Plat_Free), then restores the previous list head. */

void Set_FreeSectors(void *param_1)

{
  void *p;
  void *pvVar1;
  
  pvVar1 = g_pWalkPlane_wp_head;
  Set_ActivateSectors(param_1);
  p = g_pWalkPlane_wp_head;
  if (pvVar1 == g_pWalkPlane_wp_head) {
    pvVar1 = (void *)0x0;
  }
  while (p != (void *)0x0) {
    g_pWalkPlane_wp_head = p;
    Sector_Unlink(p);
    Plat_Free(p);
    p = g_pWalkPlane_wp_head;
  }
  g_pWalkPlane_wp_head = pvVar1;
  return;
}

/* ---- 0x004a7150  Set_ActivateSectors ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Points g_pWalkPlane_wp_head at the sector list cached for the named set (table of 0x28-byte
   {list, name} entries) */

void __cdecl Set_ActivateSectors(void *set)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  bool bVar7;
  
  iVar3 = 0;
  pbVar5 = &DAT_008cf28c;
  pbVar4 = set;
  pbVar6 = pbVar5;
LAB_004a7163:
  do {
    bVar1 = *pbVar5;
    bVar7 = bVar1 < *pbVar4;
    if (bVar1 == *pbVar4) {
      if (bVar1 != 0) {
        bVar1 = pbVar5[1];
        bVar7 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_004a7187;
        pbVar5 = pbVar5 + 2;
        pbVar4 = pbVar4 + 2;
        if (bVar1 != 0) goto LAB_004a7163;
      }
      iVar2 = 0;
    }
    else {
LAB_004a7187:
      iVar2 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
    }
    if (iVar2 == 0) goto LAB_004a719c;
    pbVar5 = pbVar6 + 0x28;
    iVar3 = iVar3 + 1;
    pbVar4 = set;
    pbVar6 = pbVar5;
    if (IMG_ADDR(0x008d086b) < (int)pbVar5) {
LAB_004a719c:
      if (0x8b < iVar3) {
        g_pWalkPlane_wp_head = (void *)0x0;
        _DAT_008cf284 = (undefined1 *)0x0;
        return;
      }
      g_pWalkPlane_wp_head = (void *)(&UINT_008cf288)[iVar3 * 10];
      _DAT_008cf284 = &DAT_008cf28c + iVar3 * 0x28;
      return;
    }
  } while( true );
}
