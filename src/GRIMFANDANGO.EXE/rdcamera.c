/* GRIMFANDANGO.EXE :: rdcamera.c
 * functions 0x00409f50 .. 0x0040dc30 (24 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00409f50  rdCamera_New ---- */
rdCamera * __cdecl rdCamera_New(float fov,int type,float aspectX,float aspectY,float zoom)

{
  rdCamera *camera;
  int iVar1;
  
  camera = (rdCamera *)
           (*g_pRdroid_HS->pAlloc)
                     (0x464,s_C__grimjedi_Libs_RDroid_Engine_R_004ddb44,DAT_004ddb3c + 3);
  if (camera == (rdCamera *)0x0) {
    return (rdCamera *)0x0;
  }
  iVar1 = rdCamera_NewEntry(camera,fov,type,aspectX,aspectY,zoom);
  return (rdCamera *)(-(uint)(iVar1 != 0) & (uint)camera);
}

/* ---- 0x00409fb0  rdCamera_NewEntry ---- */
/* Allocates the 0x34-byte projection block (camera+0x48), clamps the FOV to 5..179 and selects
   perspective projection Original name rdCamera_NewEntry (the remaster's GrimFandango (Linux): same
   parameters (camera, fov, projection type, aspect x / y, zoom) and body (allocates the 0x34-byte
   projection record in Rdcamera.c, fov clamped to >= 5)); was rdCamera_Init. */

int __cdecl
rdCamera_NewEntry(rdCamera *camera,float fov,int projType,float aspectX,float aspectY,float zoom)

{
  rdClipFrustum *prVar1;
  
  prVar1 = (rdClipFrustum *)
           (*g_pRdroid_HS->pAlloc)
                     (0x34,s_C__grimjedi_Libs_RDroid_Engine_R_004ddb44,DAT_004ddb40 + 1);
  camera->pFrustum = prVar1;
  if (prVar1 != (rdClipFrustum *)0x0) {
    if (fov < 5.0) {
      fov = 5.0;
    }
    else if (179.0 < fov) {
      fov = 179.0;
    }
    camera->flFov = fov;
    prVar1->nClipFar = projType;
    camera->pFrustum->flZNear = aspectX;
    camera->pFrustum->flZFar = aspectY;
    camera->flAspect = zoom;
    camera->flOrthoScale = 1.0;
    camera->pCanvas = (rdCanvas *)0x0;
    camera->flAmbientLight = 0.0;
    camera->dwNumLights = 0;
    camera->flAttenuationMin = 0.2;
    camera->flAttenuationMax = 0.1;
    rdCamera_SetProjectType(camera,1);
    return 1;
  }
  return 0;
}

/* ---- 0x0040a080  rdCamera_Free ---- */
/* Frees a camera: its projection block and the camera itself. */

void __cdecl rdCamera_Free(int param_1)

{
  if (param_1 != 0) {
    rdCamera_FreeEntry(param_1);
    (*g_pRdroid_HS->pFree)(param_1);
  }
  return;
}

/* ---- 0x0040a0a0  rdCamera_FreeEntry ---- */
/* Frees the 0x34-byte projection block (camera+0x48) allocated by rdCamera_Init. Original name
   rdCamera_FreeEntry (the remaster's GrimFandango (Linux): same body (frees the projection record
   at +0x48)); was rdCamera_FreeProjection. */

void __cdecl rdCamera_FreeEntry(int param_1)

{
  if (*(int *)(param_1 + 0x48) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(param_1 + 0x48));
  }
  return;
}

/* ---- 0x0040a0c0  rdCamera_SetCanvas ---- */
void __cdecl rdCamera_SetCanvas(rdCamera *camera,void *canvas)

{
  camera->pCanvas = canvas;
  rdCamera_BuildFOV(&camera->nProjectType);
  return;
}

/* ---- 0x0040a0e0  rdCamera_SetCurrent ---- */
uint __cdecl rdCamera_SetCurrent(void *param_1)

{
  if (g_pRdCamera_CurCamera != param_1) {
    g_pRdCamera_CurCamera = param_1;
  }
  return 1;
}

/* ---- 0x0040a100  rdCamera_SetFOV ---- */
/* Original name rdCamera_SetFOV (the remaster's GrimFandango (Linux): the remaster's name differs
   only in case; called by sputControl_StandardHandler in both builds (the same FOV store)); was
   rdCamera_SetFov. */

void __cdecl rdCamera_SetFOV(rdCamera *camera,float fov)

{
  if (fov < 5.0) {
    fov = 5.0;
  }
  else if (179.0 < fov) {
    fov = 179.0;
  }
  camera->flFov = fov;
  rdCamera_BuildFOV(&camera->nProjectType);
  return;
}

/* ---- 0x0040a150  rdCamera_SetProjectType ---- */
/* 0 orthographic, 1 perspective; installs the project/unproject function pointers (+0x4c/+0x50) and
   rebuilds the frustum */

int __cdecl rdCamera_SetProjectType(rdCamera *camera,int type)

{
  camera->nProjectType = type;
  if (type == 0) {
    if (camera->flAspect == 1.0) {
      camera->pfnProject = rdCamera_OrthoProjectSquare;
      camera->pfnProjectLst = rdCamera_OrthoProjectSquareLst;
    }
    else {
      camera->pfnProject = rdCamera_OrthoProject;
      camera->pfnProjectLst = rdCamera_OrthoProjectLst;
    }
  }
  else if (type == 1) {
    if (camera->flAspect == 1.0) {
      camera->pfnProject = rdCamera_PerspProjectSquare;
      camera->pfnProjectLst = rdCamera_PerspProjectSquareLst;
    }
    else {
      camera->pfnProject = rdCamera_PerspProject;
      camera->pfnProjectLst = rdCamera_PerspProjectLst;
    }
  }
  if (camera->pCanvas != (rdCanvas *)0x0) {
    rdCamera_BuildFOV(&camera->nProjectType);
  }
  return 1;
}

/* ---- 0x0040a1d0  rdCamera_SetAspectRatio ---- */
/* Original name rdCamera_SetAspectRatio (the remaster's GrimFandango (Linux): aligned call in
   sputRender_SyncCamera); was rdCamera_SetZoom. */

void __cdecl rdCamera_SetAspectRatio(rdCamera *camera,float zoom)

{
  camera->flAspect = zoom;
  if (camera->nProjectType == 0) {
    if (zoom == 1.0) {
      camera->pfnProject = rdCamera_OrthoProjectSquare;
      camera->pfnProjectLst = rdCamera_OrthoProjectSquareLst;
      rdCamera_BuildFOV(&camera->nProjectType);
      return;
    }
    camera->pfnProject = rdCamera_OrthoProject;
    camera->pfnProjectLst = rdCamera_OrthoProjectLst;
  }
  else if (camera->nProjectType == 1) {
    if (zoom == 1.0) {
      camera->pfnProject = rdCamera_PerspProjectSquare;
      camera->pfnProjectLst = rdCamera_PerspProjectSquareLst;
      rdCamera_BuildFOV(&camera->nProjectType);
      return;
    }
    camera->pfnProject = rdCamera_PerspProject;
    camera->pfnProjectLst = rdCamera_PerspProjectLst;
    rdCamera_BuildFOV(&camera->nProjectType);
    return;
  }
  rdCamera_BuildFOV(&camera->nProjectType);
  return;
}

/* ---- 0x0040a280  rdCamera_BuildFOV ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_14 */
/* Computes the projection scale from FOV and canvas size and the frustum planes Original name
   rdCamera_BuildFOV (the remaster's GrimFandango (Linux): the only unmatched callee of
   rdCamera_SetCanvas; the only unmatched callee of rdCamera_SetProjectType; 2 matched neighbours
   agree, 0 disagree); was rdCamera_BuildProjection. */

uint __cdecl rdCamera_BuildFOV(int *param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float fVar3;
  float10 fVar4;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x30 - 0x4)))
  
  iVar1 = param_1[1];
  if (iVar1 == 0) {
    return 0;
  }
  if (*param_1 == 0) {
    fVar2 = (float)(*(int *)(iVar1 + 0x20) - *(int *)(iVar1 + 0x18)) * 0.5;
    fVar3 = (float)(*(int *)(iVar1 + 0x24) - *(int *)(iVar1 + 0x1c)) * 0.5;
    *(float *)(param_1[0x12] + 0xc) = -(fVar2 / (float)param_1[0x11]);
    *(float *)(param_1[0x12] + 0x10) = (fVar3 / (float)param_1[0x11]) / (float)param_1[0x10];
    *(float *)(param_1[0x12] + 0x14) = fVar2 / (float)param_1[0x11];
    *(float *)(param_1[0x12] + 0x18) = -(fVar3 / (float)param_1[0x11]) / (float)param_1[0x10];
    param_1[0xf] = 0;
    *(undefined4 *)(param_1[0x12] + 0x1c) = 0;
    *(undefined4 *)(param_1[0x12] + 0x20) = 0;
    *(undefined4 *)(param_1[0x12] + 0x24) = 0;
    *(undefined4 *)(param_1[0x12] + 0x28) = 0;
  }
  else if (*param_1 == 1) {
    fVar2 = (float)(*(int *)(iVar1 + 0x20) - *(int *)(iVar1 + 0x18)) * 0.5;
    fVar3 = (float)(*(int *)(iVar1 + 0x24) - *(int *)(iVar1 + 0x1c)) * 0.5;
    fVar4 = (float10)stdMath_Tan((float)param_1[0xe] * 0.5);
    param_1[0xf] = PUN(int,(float)(fVar2 / (float)fVar4));
    *(float *)(param_1[0x12] + 0x1c) = (fVar3 / (fVar2 / (float)fVar4)) / (float)param_1[0x10];
    *(float *)(param_1[0x12] + 0x24) = -fVar2 / (float)param_1[0xf];
    *(float *)(param_1[0x12] + 0x20) = (-fVar3 / (float)param_1[0xf]) / (float)param_1[0x10];
    *(float *)(param_1[0x12] + 0x28) = fVar2 / (float)param_1[0xf];
    *(float *)(param_1[0x12] + 0x2c) = ((fVar3 - -1.0) / (float)param_1[0xf]) / (float)param_1[0x10]
    ;
    *(float *)(param_1[0x12] + 0x30) = -(fVar2 - -1.0) / (float)param_1[0xf];
    return 1;
  }
  return 1;
}
#undef local_14
#undef local_4
#undef local_8

#endif


/* ---- 0x0040a430  rdCamera_Update ---- */
/* Original name rdCamera_Update (the remaster's GrimFandango (Linux): aligned call in
   sputLua_SetCameraInterestL, sputLua_SetCameraPositionL, sputRender_SyncCamera); was
   rdCamera_SetFrame. */

void __cdecl rdCamera_Update(float *frame)

{
  int iVar1;
  float *pfVar2;
  
  rdMatrix_InvertOrtho34(g_pRdCamera_CurCamera->aView,frame);
  pfVar2 = (float *)&UINT_008ddf60;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar2 = *frame;
    frame = frame + 1;
    pfVar2 = pfVar2 + 1;
  }
  rdMatrix_ExtractAngles34((float *)&UINT_008ddf60,(float *)&g_aRdCamera_camPYR);
  return;
}

/* ---- 0x0040a470  rdCamera_OrthoProject ---- */
/* Projects one camera-space point orthographically with the aspect ratio. Selected by
   rdCamera_SetProjectType/rdCamera_SetAspectRatio (camera type 0 orthographic, 1 perspective;
   'Square' when the pixel aspect (+0x40) is 1.0). */

void __cdecl rdCamera_OrthoProject(float *param_1,float *param_2)

{
  rdCanvas *prVar1;
  
  prVar1 = g_pRdCamera_CurCamera->pCanvas;
  *param_1 = g_pRdCamera_CurCamera->flOrthoScale * *param_2 + prVar1->flCenterX;
  param_1[1] = -(param_2[2] * g_pRdCamera_CurCamera->flOrthoScale) * g_pRdCamera_CurCamera->flAspect
               + prVar1->flCenterY;
  param_1[2] = param_2[1];
  return;
}

/* ---- 0x0040a4b0  rdCamera_OrthoProjectLst ---- */
/* Projects a list of points orthographically with the aspect ratio. Selected by
   rdCamera_SetProjectType/rdCamera_SetAspectRatio (camera type 0 orthographic, 1 perspective;
   'Square' when the pixel aspect (+0x40) is 1.0). */

void __cdecl rdCamera_OrthoProjectLst(float *param_1,float *param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  fVar3 = g_pRdCamera_CurCamera->flOrthoScale;
  fVar1 = g_pRdCamera_CurCamera->flAspect;
  fVar2 = g_pRdCamera_CurCamera->pCanvas->flCenterY;
  fVar4 = g_pRdCamera_CurCamera->pCanvas->flCenterX;
  for (; param_3 != 0; param_3 = param_3 + -1) {
    *param_1 = fVar3 * *param_2 + fVar4;
    param_1[1] = fVar2 - param_2[2] * fVar1 * fVar3;
    param_1[2] = param_2[1];
    param_1 = param_1 + 3;
    param_2 = param_2 + 3;
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0040a530  rdCamera_OrthoProjectSquare ---- */
/* Projects one point orthographically, square pixels. Selected by
   rdCamera_SetProjectType/rdCamera_SetAspectRatio (camera type 0 orthographic, 1 perspective;
   'Square' when the pixel aspect (+0x40) is 1.0). */

void __cdecl rdCamera_OrthoProjectSquare(float *param_1,float *param_2)

{
  rdCanvas *prVar1;
  
  prVar1 = g_pRdCamera_CurCamera->pCanvas;
  *param_1 = g_pRdCamera_CurCamera->flOrthoScale * *param_2 + prVar1->flCenterX;
  param_1[1] = prVar1->flCenterY - param_2[2] * g_pRdCamera_CurCamera->flOrthoScale;
  param_1[2] = param_2[1];
  return;
}

/* ---- 0x0040a570  rdCamera_OrthoProjectSquareLst ---- */
/* Projects a list of points orthographically, square pixels. Selected by
   rdCamera_SetProjectType/rdCamera_SetAspectRatio (camera type 0 orthographic, 1 perspective;
   'Square' when the pixel aspect (+0x40) is 1.0). */

void __cdecl rdCamera_OrthoProjectSquareLst(float *param_1,float *param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  fVar1 = g_pRdCamera_CurCamera->flOrthoScale;
  fVar2 = g_pRdCamera_CurCamera->pCanvas->flCenterX;
  fVar3 = g_pRdCamera_CurCamera->pCanvas->flCenterY;
  for (; param_3 != 0; param_3 = param_3 + -1) {
    *param_1 = fVar1 * *param_2 + fVar2;
    param_1[1] = fVar3 - param_2[2] * fVar1;
    param_1[2] = param_2[1];
    param_1 = param_1 + 3;
    param_2 = param_2 + 3;
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0040a5e0  rdCamera_PerspProject ---- */
/* Perspective-projects one point (x*focal/y + cx, cy - z*aspect*focal/y) with the aspect ratio.
   Selected by rdCamera_SetProjectType/rdCamera_SetAspectRatio (camera type 0 orthographic, 1
   perspective; 'Square' when the pixel aspect (+0x40) is 1.0). */

void __cdecl rdCamera_PerspProject(float *param_1,float *param_2)

{
  float fVar1;
  rdCanvas *prVar2;
  float fVar3;
  
  fVar3 = g_pRdCamera_CurCamera->flFovY / param_2[1];
  prVar2 = g_pRdCamera_CurCamera->pCanvas;
  fVar1 = g_pRdCamera_CurCamera->flAspect;
  *param_1 = fVar3 * *param_2 + prVar2->flCenterX;
  param_1[1] = prVar2->flCenterY - param_2[2] * fVar1 * fVar3;
  param_1[2] = param_2[1];
  return;
}

/* ---- 0x0040a620  rdCamera_PerspProjectLst ---- */
/* Perspective-projects a list of points with the aspect ratio. Selected by
   rdCamera_SetProjectType/rdCamera_SetAspectRatio (camera type 0 orthographic, 1 perspective;
   'Square' when the pixel aspect (+0x40) is 1.0). */

void __cdecl rdCamera_PerspProjectLst(float *param_1,float *param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  fVar2 = g_pRdCamera_CurCamera->pCanvas->flCenterX;
  fVar3 = g_pRdCamera_CurCamera->pCanvas->flCenterY;
  for (; param_3 != 0; param_3 = param_3 + -1) {
    fVar4 = g_pRdCamera_CurCamera->flFovY / param_2[1];
    fVar1 = g_pRdCamera_CurCamera->flAspect;
    *param_1 = fVar4 * *param_2 + fVar2;
    param_1[1] = fVar3 - param_2[2] * fVar1 * fVar4;
    param_1[2] = param_2[1];
    param_1 = param_1 + 3;
    param_2 = param_2 + 3;
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x0040a6a0  rdCamera_PerspProjectSquare ---- */
/* Perspective-projects one point, square pixels. Selected by
   rdCamera_SetProjectType/rdCamera_SetAspectRatio (camera type 0 orthographic, 1 perspective;
   'Square' when the pixel aspect (+0x40) is 1.0). */

void __cdecl rdCamera_PerspProjectSquare(float *param_1,float *param_2)

{
  rdCanvas *prVar1;
  float fVar2;
  
  fVar2 = g_pRdCamera_CurCamera->flFovY / param_2[1];
  prVar1 = g_pRdCamera_CurCamera->pCanvas;
  *param_1 = fVar2 * *param_2 + prVar1->flCenterX;
  param_1[1] = prVar1->flCenterY - param_2[2] * fVar2;
  param_1[2] = param_2[1];
  return;
}

/* ---- 0x0040a6e0  rdCamera_PerspProjectSquareLst ---- */
/* Perspective-projects a list of points, square pixels. Selected by
   rdCamera_SetProjectType/rdCamera_SetAspectRatio (camera type 0 orthographic, 1 perspective;
   'Square' when the pixel aspect (+0x40) is 1.0). */

void __cdecl rdCamera_PerspProjectSquareLst(float *param_1,float *param_2,int param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  fVar1 = g_pRdCamera_CurCamera->pCanvas->flCenterX;
  fVar2 = g_pRdCamera_CurCamera->pCanvas->flCenterY;
  for (; param_3 != 0; param_3 = param_3 + -1) {
    fVar3 = g_pRdCamera_CurCamera->flFovY / param_2[1];
    *param_1 = fVar3 * *param_2 + fVar1;
    param_1[1] = fVar2 - param_2[2] * fVar3;
    param_1[2] = param_2[1];
    param_1 = param_1 + 3;
    param_2 = param_2 + 3;
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x0040a750  rdCamera_SetAmbientLight ---- */
/* Lua SetAmbientLight */

void __cdecl rdCamera_SetAmbientLight(rdCamera *camera,float ambient)

{
  camera->flAmbientLight = ambient;
  return;
}

/* ---- 0x0040a760  rdCamera_AddLight ---- */
/* Up to 64 lights per camera; stores the light pointer and position and precomputes the falloff
   terms */

void __cdecl rdCamera_AddLight(rdCamera *camera,rdLight *light,float *pos)

{
  float *pfVar1;
  
  if (0x40 < camera->dwNumLights) {
    return;
  }
  light->dwId = camera->dwNumLights;
  camera->aLights[camera->dwNumLights] = light;
  pfVar1 = camera->aLightPositions + camera->dwNumLights * 3;
  *pfVar1 = *pos;
  pfVar1[1] = pos[1];
  pfVar1[2] = pos[2];
  light->flFalloffMin = light->flIntensity / camera->flAttenuationMin;
  light->flFalloffMax = light->flIntensity / camera->flAttenuationMax;
  camera->dwNumLights = camera->dwNumLights + 1;
  return;
}

/* ---- 0x0040a7d0  rdCamera_AdvanceFrame ---- */
/* Original name rdCamera_AdvanceFrame (the remaster's GrimFandango (Linux): the camera call of
   rdAdvanceFrame, same body (z-buffer clear: hardware or fill)); was rdCamera_ClearCanvas. */

void __cdecl rdCamera_AdvanceFrame(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  rdCanvas *prVar1;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (((g_pRdCamera_CurCamera != (rdCamera *)0x0) &&
      (prVar1 = g_pRdCamera_CurCamera->pCanvas, (g_dwRdroid_curRenderOptions & 0x100) != 0)) &&
     ((prVar1->dwFlags & 2) != 0)) {
    if (0 < g_nRdroid_curAcceleration) {
      std3D_ClearZBuffer();
      return;
    }
    if ((prVar1->dwFlags & 1) != 0) {
      local_10 = prVar1->nX0;
      local_c = prVar1->nY0;
      local_8 = (prVar1->nX1 - prVar1->nX0) + 1;
      local_4 = (prVar1->nY1 - prVar1->nY0) + 1;
      Surface_Fill(prVar1->pZBuffer,0,(int *)&local_10);
      return;
    }
    Surface_Fill(prVar1->pZBuffer,0,(int *)0x0);
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0040a860  rdModel3_ClearFrameCounters ---- */
/* Original name rdModel3_ClearFrameCounters (the remaster's GrimFandango (Linux): the third counter
   reset of rdClearPreStatistics (clears rdModel3_numDrawnModels, counted per model in
   rdModel3_Draw)); was rdCamera_ResetStats. */

void __cdecl rdModel3_ClearFrameCounters(void)

{
  g_dwRdModel3_numDrawnModels = 0;
  return;
}

/* ---- 0x0040dc30  rdPrimit3_GetScreenCoord ---- */
/* Lua WorldToScreen; returns 0 when the point is behind the camera Original name
   rdPrimit3_GetScreenCoord (the remaster's GrimFandango (Linux): the only unmatched callee of
   Lua_WorldToScreen; 1 matched neighbours agree, 0 disagree); was rdCamera_ProjectPoint. */

int __cdecl rdPrimit3_GetScreenCoord(float *world,ScreenCoord *outScreen)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  longlong lVar2;
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define fStack_14 (*(float *)(_frame + (0x30 - 0x14)))
  #define fStack_10 (*(float *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  rdMatrix_TransformPoint34(local_c,world,g_pRdCamera_CurCamera->aView);
  iVar1 = rdClip_Point3(g_pRdCamera_CurCamera->pFrustum,local_c);
  if (iVar1 != 0) {
    (*g_pRdCamera_CurCamera->pfnProject)(&local_18,local_c);
    if (outScreen != (ScreenCoord *)0x0) {
      lVar2 = FTOL((float10)local_18);
      outScreen->nX = (int)lVar2;
      lVar2 = FTOL((float10)fStack_14);
      outScreen->nY = (int)lVar2;
      outScreen->flZ = fStack_10;
    }
    return 1;
  }
  return 0;
}
#undef fStack_10
#undef fStack_14
#undef local_18
#undef local_c

