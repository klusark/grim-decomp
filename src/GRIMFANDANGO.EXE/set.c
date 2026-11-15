/* GRIMFANDANGO.EXE :: set.c
 * functions 0x004824c0 .. 0x004a7150 (30 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004824c0  Res_NumRefs ---- */
/* Original name Res_NumRefs (the remaster's GrimFandango (Linux): aligned call in sputRoom_Save);
   was Set_GetRefCount. */

int __cdecl Res_NumRefs(void *param_1)

{
  ResRef *pRVar1;
  Resource *pRVar2;
  int iVar3;
  
  iVar3 = 0;
  pRVar2 = Res_FindByData(param_1);
  if (pRVar2 != (Resource *)0x0) {
    for (pRVar1 = pRVar2->pRefs; pRVar1 != (ResRef *)0x0; pRVar1 = pRVar1->pNext) {
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
  Set *set;
  Set *pSVar1;
  
  if (name == (char *)0x0) {
    sputRoom_SetCurrentRoom((Set *)0x0,0);
    return;
  }
  set = sputResource_Alloc(0x20544553,name);
  if ((set != (Set *)0x0) && (set->pColormaps != (ResRef *)0x0)) {
    pSVar1 = sputRoom_GetCurrentRoom();
    if (set != pSVar1) {
      sputRoom_SetCurrentRoom(set,(int)name);
      WalkPlane_SetCollection(set);
      sputRender_SyncCamera(set,set->nCurSetup);
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

void * __cdecl grimlib_MakeCurrentSetup(uint setup)

{
  uint uVar1;
  Set *pSVar2;
  Set *pSVar3;
  
  pSVar2 = sputRoom_GetCurrentRoom();
  uVar1 = pSVar2->nSetups;
  pSVar3 = pSVar2;
  if (uVar1 <= setup) {
    pSVar3 = (Set *)(setup / uVar1);
    setup = setup % uVar1;
  }
  uVar1 = pSVar2->nCurSetup;
  if (setup != uVar1) {
    pSVar2->nCurSetup = setup;
    sputRoom_SetSoundParameters((int)pSVar2,0x41000000,0x14,0x7f,0x3fc00000,0x3f4ccccd);
    sputLua_CameraChange(uVar1,setup);
    pSVar3 = (Set *)((code *)sputRoom_RelocateSounds)();
  }
  return pSVar3;
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
  rdroid_SetColormap(*(uint *)(iVar3 + iVar2 * 0x34 + 4));
  rdCamera_SetCurrent(*(void **)(iVar1 + 0x48));
  if (g_pSputRender_Canvas != (void *)0x0) {
    rdCamera_SetCanvas(*(rdCamera **)(iVar1 + 0x48),g_pSputRender_Canvas);
  }
  rdCamera_SetAspectRatio(*(rdCamera **)(iVar1 + 0x48),1.0);
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
  ObjectState *state;
  Actor *actor;
  float *pfVar2;
  VBuffer *pVVar3;
  int iVar4;
  float *pfVar5;
  VBufferFormat *pVVar6;
  VBufferFormat *pVVar7;
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
    actor = sputActor_ActorDeref(g_nCamActorIndex);
    pfVar2 = sputActor_GetOrientMatrix(actor);
    pfVar5 = (float *)(iVar1 + 0x50);
    for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar2 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar2 = pfVar2 + 1;
    }
    pVVar3 = sputRoom_GetSetupBackground(set,setupIdx);
    if (pVVar3 != (VBuffer *)0x0) {
      if (pVVar3->nType == 2) {
        sputRender_Decompress(pVVar3);
        pVVar3 = g_pSputRender_DecompressionBuffer;
      }
      Surface_Blit(g_pSputRender_CleanBuffer,pVVar3,0,0,(int *)0x0,0);
    }
    pVVar3 = sputRoom_GetSetupZBackground(set,setupIdx);
    if (pVVar3 == (VBuffer *)0x0) {
      puVar8 = g_pSputRender_CleanZBuffer->pPixels;
      for (iVar4 = 0x25800; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar8 = 0;
        puVar8 = puVar8 + 1;
      }
      g_dwRenderFlags = g_dwRenderFlags | 2;
    }
    else if (pVVar3->nType == 2) {
      pVVar6 = &g_pSputRender_CleanZBuffer->format;
      pVVar7 = &g_pSputRender_DecompressionBuffer->format;
      for (iVar4 = 0x13; iVar4 != 0; iVar4 = iVar4 + -1) {
        pVVar7->nWidth = pVVar6->nWidth;
        pVVar6 = (VBufferFormat *)&pVVar6->nHeight;
        pVVar7 = (VBufferFormat *)&pVVar7->nHeight;
      }
      if (g_pSputRender_CleanZBuffer->nVideoMemory == 0) {
        stdDisplay_VBufferDeCompressTo(pVVar3,g_pSputRender_CleanZBuffer);
      }
      else {
        stdDisplay_VBufferDeCompressTo(pVVar3,g_pSputRender_DecompressionBuffer);
        Surface_Blit(g_pSputRender_CleanZBuffer,g_pSputRender_DecompressionBuffer,0,0,(int *)0x0,0);
      }
    }
    else {
      Surface_Blit(g_pSputRender_CleanZBuffer,pVVar3,0,0,(int *)0x0,0);
    }
    for (state = *(ObjectState **)(iVar1 + 0x128); state != (ObjectState *)0x0; state = state->pNext
        ) {
      ObjectState_LoadResources(state);
      ObjectState_Reset(state,g_pSputRender_CleanBuffer,g_pSputRender_CleanZBuffer);
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

void __cdecl Set_DrawDebugLights(int param_1)

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
        rdMatrix_LookAt(local_30,pfVar2 + -0x10,(float *)&local_6c,0);
        local_5c = pfVar2[-7] * 0.1f;
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
          rdMatrix_TransformPoint34Acc(vec,local_30);
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

void __cdecl
sputRoom_SetSoundParameters
          (int param_1,uint param_2,byte param_3,byte param_4,uint param_5,uint param_6)

{
  *(byte *)(param_1 + 0x1af8) = param_3;
  *(uint *)(param_1 + 0x1afc) = param_2;
  *(byte *)(param_1 + 0x1af9) = param_4;
  *(uint *)(param_1 + 0x1b00) = param_5;
  *(uint *)(param_1 + 0x1b04) = param_6;
  return;
}

/* ---- 0x004a4050  sputRoom_GetSoundParameters ---- */
/* Fills the default 3D sound parameters (min distance, volume, pan...) from the set Original name
   sputRoom_GetSoundParameters (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_GetSoundParameters; 3 matched neighbours agree, 0 disagree); was Set_GetSoundParams. */

void __cdecl
sputRoom_GetSoundParameters(Set *set,float *minVol,char *maxVol,char *c,float *d,float *e)

{
  *minVol = set->flSoundMinVolume;
  *maxVol = set->cSoundMaxVolume;
  *c = set->cSound1af9;
  *d = set->flSoundPanScale;
  *e = set->flSound1b04;
  return;
}

/* ---- 0x004a40f0  sputRoom_SetCurrentRoom ---- */
/* Releases the previous set's resources (unless locked), references the new one, loads its
   resources and resets the sound parameters Original name sputRoom_SetCurrentRoom (the remaster's
   GrimFandango (Linux): the only unmatched caller of Set_LoadResources; 4 matched neighbours agree,
   1 disagree); was Set_SetCurrent. */

void __cdecl sputRoom_SetCurrentRoom(Set *set,int param_2)

{
  if ((g_dwSputRoom_pCurrentRoom == 0) || (g_pCurrentSet != set)) {
    if (g_dwSputRoom_pCurrentRoom != 0) {
      sputRoom_UnReference(g_pCurrentSet);
      Res_RemoveReference((ResRef *)&g_dwSputRoom_pCurrentRoom);
      g_szSputRoom_CurrentRoomName[0] = '\0';
    }
    if (set != (Set *)0x0) {
      Res_SetReference((ResRef *)&g_dwSputRoom_pCurrentRoom,set,
                       s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x15d);
      if (g_dwSputRoom_pCurrentRoom == 0) {
        (*g_pStd_HS->pAssertFail)(s_Bad_room_Reference_004ec62c,s_main_sputResource_h_004e80a8,0xa4)
        ;
      }
      sputRoom_LoadResources(g_pCurrentSet);
      strncpy((uint *)g_szSputRoom_CurrentRoomName,(uint *)set,0x20);
      sputRoom_SetSoundParameters((int)set,0x41000000,0x14,0x7f,0x3fc00000,0x3f4ccccd);
    }
  }
  return;
}

/* ---- 0x004a41b0  sputRoom_GetCurrentRoom ---- */
/* Original name sputRoom_GetCurrentRoom (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_SetAmbientLight; 18 matched neighbours agree, 0 disagree); was Set_GetCurrent. */

Set * __cdecl sputRoom_GetCurrentRoom(void)

{
  return (Set *)(-(uint)(g_dwSputRoom_pCurrentRoom != 0) & (uint)g_pCurrentSet);
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
  WalkPlane *pWVar1;
  code *pcVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define pSStack_c (*(Set **)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define fStack_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  local_8 = 0;
  Res_GetFirstType((int *)&local_14,(int *)&local_10,0x20544553);
  pcVar2 = writeFn;
  while (writeFn = pcVar2, local_14 != 0) {
    iVar4 = Res_NumRefs((void *)local_10);
    if (0 < iVar4) {
      local_8 = local_8 + 1;
    }
    Res_GetNextType((int *)&local_14,(int *)&local_10,0x20544553);
    pcVar2 = writeFn;
  }
  iVar4 = (*pcVar2)(&local_8,4);
  if (iVar4 == 0) {
    Res_GetFirstType((int *)&local_14,(int *)&local_10,0x20544553);
    pvVar3 = (void *)local_10;
    do {
      if (local_14 == 0) {
        pSStack_c = sputRoom_GetCurrentRoom();
        (*pcVar2)(&pSStack_c,4);
        if (pSStack_c != (Set *)0x0) {
          (*pcVar2)(&pSStack_c->cSoundMaxVolume,1);
          (*pcVar2)(&pSStack_c->cSound1af9,1);
          (*pcVar2)(&pSStack_c->flSoundMinVolume,4);
          (*pcVar2)(&pSStack_c->flSoundPanScale,4);
          (*pcVar2)(&pSStack_c->flSound1b04,4);
          for (pWVar1 = g_pWalkPlane_wp_head; pWVar1 != (WalkPlane *)0x0; pWVar1 = pWVar1->pNext) {
            writeFn = (void *)pWVar1->nId;
            (*pcVar2)(&writeFn,4);
            writeFn = (void *)pWVar1->nVisible;
            (*pcVar2)(&writeFn,4);
            writeFn = (void *)pWVar1->dwType;
            (*pcVar2)(&writeFn,4);
            writeFn = (void *)pWVar1->nActive;
            (*pcVar2)(&writeFn,4);
            fStack_4 = pWVar1->flHeight;
            (*pcVar2)(&fStack_4,4);
          }
        }
        return 0;
      }
      iVar5 = 0;
      local_10 = (uint)pvVar3;
      iVar4 = Res_NumRefs(pvVar3);
      if (iVar4 != 0) {
        (*pcVar2)(&local_10,4);
        (*pcVar2)((int)pvVar3 + 0xb4,4);
        (*pcVar2)((int)pvVar3 + 0x1ac0,4);
        fStack_4 = 0.0;
        if (0 < *(int *)((int)pvVar3 + 0xb0)) {
          do {
            iVar6 = iVar5 + *(int *)((int)pvVar3 + 0xac);
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
            fStack_4 = PUN(float,(PUN(int,(float)fStack_4) + 1));
            iVar5 = iVar5 + 300;
          } while (PUN(int,(float)fStack_4) < *(int *)((int)pvVar3 + 0xb0));
        }
      }
      Res_GetNextType((int *)&local_14,(int *)&local_10,0x20544553);
      pvVar3 = (void *)local_10;
    } while( true );
  }
  return 1;
}
#undef fStack_4
#undef local_10
#undef local_14
#undef local_8
#undef pSStack_c


/* ---- 0x004a44e0  sputRoom_Restore ---- */
/* Source: Engine/sputRoom.cpp (lines 528-535, from __FILE__/__LINE__ passed to the allocator)
   Original name sputRoom_Restore (the remaster's GrimFandango (Linux): the only unmatched caller of
   ObjectState_SendToBack; 4 matched neighbours agree, 0 disagree); was Set_RestoreState. */

int __cdecl sputRoom_Restore(void *readFn)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  WalkPlane *this;
  float fVar2;
  int iVar3;
  uint *data;
  void *pvVar4;
  Set *set;
  int iVar5;
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
      data = Res_HandleFromSerialNumber(pvStack_5c);
      if (data == (uint *)0x0) {
        return 1;
      }
      (*(code *)readFn)(data + 0x2d,4);
      if (g_dwSputRoom_pCurrentRoom != 0) {
        Res_RemoveReference((ResRef *)&g_dwSputRoom_pCurrentRoom);
      }
      Res_SetReference((ResRef *)&g_dwSputRoom_pCurrentRoom,data,
                       s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x210);
      if (g_dwSputRoom_pCurrentRoom == 0) {
        (*g_pStd_HS->pAssertFail)(s_Bad_room_Reference_004ec62c,s_main_sputResource_h_004e80a8,0xa4)
        ;
      }
      sputRoom_LoadResources(g_pCurrentSet);
      strncpy((uint *)g_szSputRoom_CurrentRoomName,data,0x20);
      (*(code *)readFn)(&iStack_58,4);
      if (iStack_58 != 0) {
        Res_SetReference((ResRef *)(data + 0x6b0),data,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,
                         0x217);
      }
      iStack_70 = 0;
      if (0 < (int)data[0x2c]) {
        iStack_6c = 0;
        do {
          iVar3 = iStack_6c + data[0x2b];
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
              iVar5 = *(int *)(iVar3 + 0x128);
              iVar1 = *(int *)(iVar5 + 0x40);
              if (iVar1 != 0) {
                if (iVar1 == 0) {
                  (*g_pStd_HS->pAssertFail)
                            (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
                }
                *(undefined4 *)(*(int *)(iVar5 + 0x44) + 0x68) = uStack_4c;
              }
              iVar5 = *(int *)(iVar3 + 0x128);
              iVar1 = *(int *)(iVar5 + 0xb4);
              if (iVar1 != 0) {
                if (iVar1 == 0) {
                  (*g_pStd_HS->pAssertFail)
                            (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
                }
                *(int *)(*(int *)(iVar5 + 0xb8) + 0x68) = iStack_48;
              }
              iStack_68 = iStack_68 + 1;
            } while (iStack_68 < (int)uStack_74);
          }
          iVar5 = 0;
          if (0 < (int)uStack_74) {
            do {
              pvVar4 = ObjectState_MoveToBack
                                 (*(ObjectState **)(iVar3 + 0x128),*(ObjectState **)(iVar3 + 0x128))
              ;
              *(void **)(iVar3 + 0x128) = pvVar4;
              iVar5 = iVar5 + 1;
            } while (iVar5 < (int)uStack_74);
          }
          iStack_70 = iStack_70 + 1;
          iStack_6c = iStack_6c + 300;
        } while (iStack_70 < (int)data[0x2c]);
      }
      fStack_64 = PUN(float,(PUN(int,(float)fStack_64) + 1));
    } while (PUN(int,(float)fStack_64) < local_60);
  }
  (*(code *)readFn)(&pvStack_44,4);
  set = Res_HandleFromSerialNumber(pvStack_44);
  sputRoom_SetCurrentRoom(set,(int)set);
  if (set != (Set *)0x0) {
    grimlib_MakeCurrentSetup(set->nCurSetup);
    WalkPlane_SetCollection(set);
    (*(code *)readFn)(&set->cSoundMaxVolume,1);
    (*(code *)readFn)(&set->cSound1af9,1);
    (*(code *)readFn)(&set->flSoundMinVolume,4);
    (*(code *)readFn)(&set->flSoundPanScale,4);
    (*(code *)readFn)(&set->flSound1b04,4);
    for (this = g_pWalkPlane_wp_head; this != (WalkPlane *)0x0; this = this->pNext) {
      (*(code *)readFn)(&iStack_48,4);
      if (iStack_48 == this->nId) {
        (*(code *)readFn)(&uStack_74,4);
        this->nVisible = uStack_74;
        (*(code *)readFn)(&uStack_74,4);
        WalkPlane_SetType(this,uStack_74);
        (*(code *)readFn)(&uStack_74,4);
        this->nActive = uStack_74;
        (*(code *)readFn)(&fStack_64,4);
        fVar2 = fStack_64;
        if (fStack_64 == 0.0) {
          fVar2 = 0.005f;
        }
        this->flHeight = fVar2;
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


/* ---- 0x004a49a0  sputRoom_LoadRoom ---- */
/* Resource type 'SET ' loader (ResType_SetHandler op 1): allocates the 0x1b08-byte set record,
   initialises it, parses the .set file, links it to the set-name entry and re-attaches the walkers
   of the actors already in that set. Earlier taken for sputResource_SetHandler (the remaster's
   GrimFandango (Linux): the only unmatched caller of SetFile_Parse; 1 matched neighbours agree, 0
   disagree); was Set_LoadFile. Original name sputRoom_LoadRoom (the remaster's GrimFandango
   (Linux): same body (alloc the set record, LoadRoomEntry, look the name up in the set list, Puck
   validate, free on failure); sputResource_SetHandler's call); was sputResource_SetHandler. */

Set * __cdecl sputRoom_LoadRoom(char *param_1)

{
  int *piVar1;
  ActorExtra *pAVar2;
  Set *set;
  void *pvVar3;
  int iVar4;
  Set *pSVar5;
  
  set = (Set *)(*g_pSputRoomHS->pAlloc)(0x1b08,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x306);
  if (set != (Set *)0x0) {
    pSVar5 = set;
    for (iVar4 = 0x6c2; iVar4 != 0; iVar4 = iVar4 + -1) {
      pSVar5->aName[0] = '\0';
      pSVar5->aName[1] = '\0';
      pSVar5->aName[2] = '\0';
      pSVar5->aName[3] = '\0';
      pSVar5 = (Set *)(pSVar5->aName + 4);
    }
    Set_InitRecord(set);
    iVar4 = SetFile_Parse(param_1,(uint)set);
    if (iVar4 != 0) {
      pvVar3 = Set_FindNameInList((int)param_1);
      if (pvVar3 == (void *)0x0) {
        pvVar3 = Set_NormalizeName(param_1);
      }
      *(void **)&set->field_0x1abc = pvVar3;
      for (piVar1 = *(int **)((int)pvVar3 + 0x80); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[2])
      {
        pAVar2 = g_pActors[*piVar1].pExtra;
        if (((pAVar2 != (ActorExtra *)0x0) && (pAVar2->pPuck != (Puck *)0x0)) &&
           (pAVar2->nFollowBoxes != 0)) {
          Puck_Validate(pAVar2->pPuck);
        }
      }
      return set;
    }
  }
  sputRoom_FreeRoom((uint)set);
  return (Set *)0x0;
}

/* ---- 0x004a4a70  Set_InitRecord ---- */
/* Zeroes a 0x1b08-byte set record and fills the defaults (empty names, size field +0x1af4). */

void __cdecl Set_InitRecord(Set *set)

{
  int iVar1;
  Set *pSVar2;
  
  pSVar2 = set;
  for (iVar1 = 0x6c2; iVar1 != 0; iVar1 = iVar1 + -1) {
    pSVar2->aName[0] = '\0';
    pSVar2->aName[1] = '\0';
    pSVar2->aName[2] = '\0';
    pSVar2->aName[3] = '\0';
    pSVar2 = (Set *)(pSVar2->aName + 4);
  }
  set->nLights = 0;
  set->nSetups = 0;
  set->pSetups = (Setup *)0x0;
  set->nCurSetup = 0;
  set->nCurColormap = 0;
  set->nColormaps = 1;
  set->pColormaps = (ResRef *)0x0;
  set->aColormapName[0] = '\0';
  strncpy((uint *)set->aColormapName,(uint *)&DAT_004ec60c,0x1f);
  set->aColormapName[0x1f] = '\0';
  strncpy((uint *)set,(uint *)&DAT_004f5a98,0x1f);
  set->aName[0x1f] = '\0';
  set->dwSize = 0x1b08;
  return;
}

/* ---- 0x004a4b40  sputRoom_UnReference ---- */
/* Drops the colormap, background, depth and object state references of an unlocked set Original
   name sputRoom_UnReference (the remaster's GrimFandango (Linux): aligned call in
   sputRoom_SetCurrentRoom); was Set_ReleaseResources. */

void __cdecl sputRoom_UnReference(Set *set)

{
  Setup *pSVar1;
  int iVar2;
  ObjectState *state;
  int iVar3;
  int iVar4;
  
  if (set->nLocked == 0) {
    if ((set->pColormaps != (ResRef *)0x0) && (iVar3 = 0, 0 < set->nColormaps)) {
      iVar4 = 0;
      do {
        Res_RemoveReference((ResRef *)(set->pColormaps->aTag + iVar4 + -8));
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + 0x34;
      } while (iVar3 < set->nColormaps);
    }
    iVar3 = 0;
    if (0 < set->nSetups) {
      iVar4 = 0;
      do {
        Res_RemoveReference((ResRef *)((set->pSetups->background).aTag + iVar4 + -8));
        Res_RemoveReference((ResRef *)((set->pSetups->zBackground).aTag + iVar4 + -8));
        pSVar1 = set->pSetups;
        iVar2 = *(int *)((int)(&pSVar1->zBackground + 1) + iVar4);
        while (iVar2 != 0) {
          state = *(ObjectState **)((int)(&pSVar1->zBackground + 1) + iVar4);
          *(ObjectState **)((int)(&pSVar1->zBackground + 1) + iVar4) = state->pNext;
          ObjectState_UnLoadResources(state);
          if (state != (ObjectState *)0x0) {
            ObjectState_Destruct(state);
            Plat_Free(state);
          }
          pSVar1 = set->pSetups;
          iVar2 = *(int *)((int)(&pSVar1->zBackground + 1) + iVar4);
        }
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + 300;
      } while (iVar3 < set->nSetups);
    }
  }
  return;
}

/* ---- 0x004a4c40  sputRoom_FreeRoom ---- */
/* Resource type 'SET ' free handler: Set_FreeContents, then frees the set record. Original name
   sputRoom_FreeRoom (the remaster's GrimFandango (Linux): same body (free the contents, then the
   record); the free call of sputResource_SetHandler); was Set_Free. */

void __cdecl sputRoom_FreeRoom(uint param_1)

{
  sputRoom_FreeRoomEntry((char *)param_1);
  (*g_pSputRoomHS->pFree)(param_1);
  return;
}

/* ---- 0x004a4c60  sputRoom_FreeRoomEntry ---- */
/* Releases a set's resources, colormap array, setups and sectors and removes its actor list
   (killing the shadows of the actors in it). Original name sputRoom_FreeRoomEntry (the remaster's
   GrimFandango (Linux): sputRoom_FreeRoom's only callee; callees sputRoom_UnReference,
   sputActor_ResetShadows, sputRoom_RemoveActor agree); was Set_FreeContents. */

void __cdecl sputRoom_FreeRoomEntry(char *param_1)

{
  void *pvVar1;
  int *piVar2;
  
  sputRoom_UnReference((Set *)param_1);
  if (*(int *)(param_1 + 0x80) != 0) {
    (*g_pSputRoomHS->pFree)(*(int *)(param_1 + 0x80));
  }
  Set_FreeSetups((int)param_1);
  WalkPlane_KillCollection(param_1);
  pvVar1 = *(void **)(param_1 + 0x1abc);
  if (pvVar1 != (void *)0x0) {
    piVar2 = *(int **)((int)pvVar1 + 0x80);
    while (piVar2 != (int *)0x0) {
      sputActor_ResetShadows(g_pActors + *piVar2);
      sputRoom_RemoveActor(param_1,g_pActors + **(int **)((int)pvVar1 + 0x80));
      piVar2 = *(int **)((int)pvVar1 + 0x80);
    }
    SetActorList_Free(pvVar1);
    param_1[0x1abc] = '\0';
    param_1[0x1abd] = '\0';
    param_1[0x1abe] = '\0';
    param_1[0x1abf] = '\0';
  }
  return;
}

/* ---- 0x004a4d10  Set_FreeSetups ---- */
/* Frees every setup (300-byte records at set+0xac, count at +0xb0) and the array. */

void __cdecl Set_FreeSetups(int param_1)

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

void __cdecl Set_FreeSetup(uint param_1,int param_2)

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
/* WARNING: Type propagation algorithm not settling */
/* Loads colormaps (set+0x80, 0x34 each), each setup's background/depth bitmaps, creates the
   rdCamera (setup+0x48) and rdThing (+0x4c), builds the camera basis and adds the set's lights
   Original name sputRoom_LoadResources (the remaster's GrimFandango (Linux): strings:
   'dfltcmp.cmp'); was Set_LoadResources. */

int __cdecl sputRoom_LoadResources(Set *set)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ResRef *ref;
  char cVar1;
  Setup *pSVar2;
  SetLight *pSVar3;
  Set *pSVar4;
  int iVar5;
  void *pvVar6;
  rdCamera *prVar7;
  undefined4 *puVar8;
  uint uVar9;
  uint uVar10;
  ResRef *ref_00;
  int iVar11;
  int *piVar12;
  float *pfVar13;
  char *pcVar14;
  char *pcVar15;
  ResRef **ppRVar16;
  rdLight *light;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pSVar4 = set;
  set->dwSize = 0x1b08;
  pSVar2 = set->pSetups;
  SoundsFloodMusicBuffer();
  uVar10 = 0;
  if (set->nColormaps != 0) {
    iVar11 = 0;
    do {
      if (*(int *)(set->pColormaps->aTag + iVar11 + -8) == 0) {
        iVar5 = _stricmp((byte *)set->aColormapName,&DAT_004ec60c);
        if (iVar5 != 0) {
          pvVar6 = sputResource_Alloc(0x50414d43,set->aColormapName);
          Res_SetReference((ResRef *)(set->pColormaps->aTag + iVar11 + -8),pvVar6,
                           s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x6dc);
        }
        if (*(int *)(set->pColormaps->aTag + iVar11 + -8) == 0) {
          pvVar6 = sputResource_Alloc(0x50414d43,s_dfltcmp_cmp_004ec710);
          Res_SetReference((ResRef *)(set->pColormaps->aTag + iVar11 + -8),pvVar6,
                           s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x6e3);
          if (*(int *)(set->pColormaps->aTag + iVar11 + -8) == 0) {
            return 0;
          }
        }
      }
      else {
        Res_Touch(*(void **)(set->pColormaps->aTag + iVar11 + -4));
      }
      uVar10 = uVar10 + 1;
      iVar11 = iVar11 + 0x34;
    } while (uVar10 < (uint)set->nColormaps);
  }
  local_4 = 0;
  if (set->nSetups == 0) {
    return 1;
  }
  ref_00 = &pSVar2->background;
  do {
    if (g_nSkipSetupBitmaps == 0) {
      if (ref_00->nValid == 0) {
        iVar11 = _stricmp((byte *)&ref_00[-2].nLine,&DAT_004ec60c);
        if (iVar11 != 0) {
          pvVar6 = sputResource_Alloc(0x444e4b42,(char *)&ref_00[-2].nLine);
          Res_SetReference(ref_00,pvVar6,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x702);
        }
        if (ref_00->nValid == 0) {
          pvVar6 = sputResource_Alloc(0x444e4b42,s_dfltroom_bm_004ec5d4);
          Res_SetReference(ref_00,pvVar6,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x708);
          if (ref_00->nValid == 0) {
            return 0;
          }
          uVar10 = 0xffffffff;
          pcVar14 = &DAT_004ec60c;
          do {
            pcVar15 = pcVar14;
            if (uVar10 == 0) break;
            uVar10 = uVar10 - 1;
            pcVar15 = pcVar14 + 1;
            cVar1 = *pcVar14;
            pcVar14 = pcVar15;
          } while (cVar1 != '\0');
          uVar10 = ~uVar10;
          piVar12 = (int *)(pcVar15 + -uVar10);
          ppRVar16 = (ResRef **)&ref_00[-2].nLine;
          for (uVar9 = uVar10 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
            *ppRVar16 = (ResRef *)*piVar12;
            piVar12 = piVar12 + 1;
            ppRVar16 = ppRVar16 + 1;
          }
          for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(char *)ppRVar16 = (char)*piVar12;
            piVar12 = (int *)((int)piVar12 + 1);
            ppRVar16 = (ResRef **)((int)ppRVar16 + 1);
          }
          ref_00[-1].aTag[0xc] = '\0';
          goto LAB_004a51bd;
        }
      }
      else {
        Res_Touch(ref_00->pData);
LAB_004a51bd:
        if (ref_00->nValid == 0) {
          (*g_pStd_HS->pAssertFail)
                    (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
        }
      }
      stdBitmap_MemUsage(ref_00->pData);
      if (ref_00[-1].aTag[0xc] != '\0') {
        ref = ref_00 + 1;
        if ((ref_00[1].nValid == 0) &&
           (pvVar6 = sputResource_Alloc(0x4655425a,ref_00[-1].aTag + 0xc), pvVar6 != (void *)0x0)) {
          Res_SetReference(ref,pvVar6,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x720);
        }
        if ((ref->nValid != 0) && (((code *)Res_Touch)(ref_00[1].pData), ref->nValid == 0)) {
          (*g_pStd_HS->pAssertFail)
                    (s_Bad_ZBuffer_Reference_004ec614,s_main_sputResource_h_004e80a8,0x95);
        }
      }
    }
    if (*(int *)(ref_00[-3].aTag + 0x1c) == 0) {
      prVar7 = rdCamera_New(*(float *)(ref_00[-3].aTag + 0x10),1,*(float *)(ref_00[-3].aTag + 0x14),
                            *(float *)(ref_00[-3].aTag + 0x18),1.0);
      *(rdCamera **)(ref_00[-3].aTag + 0x1c) = prVar7;
      if (prVar7 == (rdCamera *)0x0) {
        return 0;
      }
      puVar8 = (undefined4 *)rdThing_New(0);
      uVar10 = *(uint *)(ref_00[-3].aTag + 0x1c);
      ref_00[-3].nLine = (int)puVar8;
      rdThing_SetCamera(puVar8,uVar10);
      rdMatrix_LookAt((float *)&ref_00[-3].pPrev,(float *)&ref_00[-4].pNext,(float *)ref_00[-3].aTag
                      ,*(uint *)(ref_00[-3].aTag + 0xc));
      set = (Set *)0x0;
      if (pSVar4->nLights != 0) {
        pSVar3 = pSVar4->aLights;
        pfVar13 = &pSVar4->aLights[0].light.flInnerAngle;
        do {
          light = &pSVar3->light;
          rdLight_SetAngles((rdLight *)(pfVar13 + -8),*pfVar13,pfVar13[2]);
          rdCamera_AddLight(*(rdCamera **)(ref_00[-3].aTag + 0x1c),light,
                            (float *)((int)(light + -1) + 0x30));
          set = (Set *)(set->aName + 1);
          pfVar13 = pfVar13 + 0x1a;
          pSVar3 = (SetLight *)(light + 1);
        } while (set < (Set *)pSVar4->nLights);
      }
    }
    local_4 = local_4 + 1;
    ref_00 = (ResRef *)&ref_00[5].nLine;
    if ((uint)pSVar4->nSetups <= local_4) {
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
  strncpy((uint *)(&DAT_008cac08 + iVar2),(uint *)name,0x1f);
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
  byte *pbVar3;
  
  iVar2 = 0;
  if ((int)UINT_008cb0a4 < 1) {
    return -1;
  }
  pbVar3 = &DAT_008cac08;
  do {
    iVar1 = _stricmp(pbVar3,(byte *)name);
    if (iVar1 == 0) {
      return iVar2;
    }
    iVar2 = iVar2 + 1;
    pbVar3 = pbVar3 + 0x24;
  } while (iVar2 < (int)UINT_008cb0a4);
  return -1;
}

/* ---- 0x004a55d0  Set_IsHandleValid ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int Set_IsHandleValid(char *param_1)

{
  int iVar1;
  
  iVar1 = Set_FindHandle(param_1);
  if (iVar1 == -1) {
    return 1;
  }
  iVar1 = (**(code **)(&DAT_008cac28 + iVar1 * 0x24))();
  return (uint)(iVar1 != 0);
}

/* ---- 0x004a60a0  GetRoomActors ---- */
/* Returns the {actorIndex, ?, next} list of actors placed in the named set Original name
   GetRoomActors (the remaster's GrimFandango (Linux): same role and slot (the actor list of the
   named set, or 0); called by sputLua_GetVisibleThingsL in both builds; the remaster inlined
   Set_FindNameInList); was Set_GetActorListByName. */

void * __cdecl GetRoomActors(char *setName)

{
  void *pvVar1;
  
  pvVar1 = Set_FindNameInList((int)setName);
  if (pvVar1 != (void *)0x0) {
    return *(void **)((int)pvVar1 + 0x80);
  }
  return (void *)0x0;
}

/* ---- 0x004a60c0  Set_FindNameInList ---- */
/* Case-insensitive lookup in the linked set-name list */

void * __cdecl Set_FindNameInList(int param_1)

{
  int iVar1;
  byte *pbVar2;
  
  if ((param_1 != 0) && (pbVar2 = g_pRoomList, g_pRoomList != (void *)0x0)) {
    do {
      iVar1 = _stricmp(pbVar2,(byte *)param_1);
      if (iVar1 == 0) {
        return pbVar2;
      }
      pbVar2 = *(byte **)(pbVar2 + 0x84);
    } while (pbVar2 != (byte *)0x0);
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

/* ---- 0x004a7100  WalkPlane_KillCollection ---- */
/* Deactivates the set's sectors and frees every sector in g_pWalkPlane_wp_head (Sector_Unlink +
   Plat_Free), then restores the previous list head. Original name WalkPlane_KillCollection (the
   remaster's GrimFandango (Linux): same body (select the named collection like SetCollection,
   unlink and free all its planes, restore the previous wp_head)); was Set_FreeSectors. */

void __cdecl WalkPlane_KillCollection(void *param_1)

{
  WalkPlane *plane;
  WalkPlane *pWVar1;
  
  pWVar1 = g_pWalkPlane_wp_head;
  WalkPlane_SetCollection(param_1);
  plane = g_pWalkPlane_wp_head;
  if (pWVar1 == g_pWalkPlane_wp_head) {
    pWVar1 = (WalkPlane *)0x0;
  }
  while (plane != (WalkPlane *)0x0) {
    g_pWalkPlane_wp_head = plane;
    WalkPlane_Destruct(plane);
    Plat_Free(plane);
    plane = g_pWalkPlane_wp_head;
  }
  g_pWalkPlane_wp_head = pWVar1;
  return;
}

/* ---- 0x004a7150  WalkPlane_SetCollection ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Points g_pWalkPlane_wp_head at the sector list cached for the named set (table of 0x28-byte
   {list, name} entries) Original name WalkPlane_SetCollection (the remaster's GrimFandango (Linux):
   same body (find the collection name among 0x8c slots of 0x28 bytes, wp_head = its list)); was
   Set_ActivateSectors. */

void __cdecl WalkPlane_SetCollection(void *set)

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
    if (((unsigned)(uintptr_t)&DAT_008d086b) < (int)pbVar5) {
LAB_004a719c:
      if (0x8b < iVar3) {
        g_pWalkPlane_wp_head = (WalkPlane *)0x0;
        _DAT_008cf284 = (undefined1 *)0x0;
        return;
      }
      g_pWalkPlane_wp_head = (WalkPlane *)(&g_dwWalkPlane_Collection)[iVar3 * 10];
      _DAT_008cf284 = &DAT_008cf28c + iVar3 * 0x28;
      return;
    }
  } while( true );
}
