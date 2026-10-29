/* GRIMFANDANGO.EXE :: rdcamera.c
 * functions 0x00409f50 .. 0x0040dc30 (24 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00409f50  rdCamera_New ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * rdCamera_New(float fov,int type,float aspectX,float aspectY,float zoom)

{
  void *camera;
  int iVar1;
  
  camera = (void *)(*g_pSvcRdroid->pAlloc)
                             (0x464,s_C__grimjedi_Libs_RDroid_Engine_R_004ddb44,DAT_004ddb3c + 3);
  if (camera == (void *)0x0) {
    return (void *)0x0;
  }
  iVar1 = rdCamera_Init(camera,fov,type,(int)aspectX,(int)aspectY,zoom);
  return (void *)(-(uint)(iVar1 != 0) & (uint)camera);
}

/* ---- 0x00409fb0  rdCamera_Init ---- */
/* Allocates the 0x34-byte projection block (camera+0x48), clamps the FOV to 5..179 and selects
   perspective projection */

int __cdecl rdCamera_Init(void *camera,float fov,int a,int b,int c,float zoom)

{
  int *piVar1;
  
  piVar1 = (int *)(*g_pSvcRdroid->pAlloc)
                            (0x34,s_C__grimjedi_Libs_RDroid_Engine_R_004ddb44,DAT_004ddb40 + 1);
  *(int **)((int)camera + 0x48) = piVar1;
  if (piVar1 != (int *)0x0) {
    if (fov < 5.0) {
      fov = 5.0;
    }
    else if (179.0 < fov) {
      fov = 179.0;
    }
    *(float *)((int)camera + 0x38) = fov;
    *piVar1 = a;
    *(int *)(*(int *)((int)camera + 0x48) + 4) = b;
    *(int *)(*(int *)((int)camera + 0x48) + 8) = c;
    *(float *)((int)camera + 0x40) = zoom;
    *(undefined4 *)((int)camera + 0x44) = 0x3f800000;
    *(undefined4 *)((int)camera + 4) = 0;
    *(undefined4 *)((int)camera + 0x54) = 0;
    *(undefined4 *)((int)camera + 0x58) = 0;
    *(undefined4 *)((int)camera + 0x45c) = 0x3e4ccccd;
    *(undefined4 *)((int)camera + 0x460) = 0x3dcccccd;
    rdCamera_SetProjectType(camera,1);
    return 1;
  }
  return 0;
}

/* ---- 0x0040a080  FUN_0040a080 ---- */
void FUN_0040a080(int param_1)

{
  if (param_1 != 0) {
    FUN_0040a0a0(param_1);
    (*g_pSvcRdroid->pFree)(param_1);
  }
  return;
}

/* ---- 0x0040a0a0  FUN_0040a0a0 ---- */
void FUN_0040a0a0(int param_1)

{
  if (*(int *)(param_1 + 0x48) != 0) {
    (*g_pSvcRdroid->pFree)(*(int *)(param_1 + 0x48));
  }
  return;
}

/* ---- 0x0040a0c0  rdCamera_SetCanvas ---- */
void __cdecl rdCamera_SetCanvas(void *camera,void *canvas)

{
  *(void **)((int)camera + 4) = canvas;
  rdCamera_BuildProjection(camera);
  return;
}

/* ---- 0x0040a0e0  rdCamera_SetCurrent ---- */
undefined4 rdCamera_SetCurrent(void *param_1)

{
  if (g_pRdCurrentCamera != param_1) {
    g_pRdCurrentCamera = param_1;
  }
  return 1;
}

/* ---- 0x0040a100  rdCamera_SetFov ---- */
void __cdecl rdCamera_SetFov(void *camera,float fov)

{
  if (fov < 5.0) {
    fov = 5.0;
  }
  else if (179.0 < fov) {
    fov = 179.0;
  }
  *(float *)((int)camera + 0x38) = fov;
  rdCamera_BuildProjection(camera);
  return;
}

/* ---- 0x0040a150  rdCamera_SetProjectType ---- */
/* 0 orthographic, 1 perspective; installs the project/unproject function pointers (+0x4c/+0x50) and
   rebuilds the frustum */

int __cdecl rdCamera_SetProjectType(void *camera,int type)

{
  *(int *)camera = type;
  if (type == 0) {
    if (*(int *)((int)camera + 0x40) == 0x3f800000) {
      *(code **)((int)camera + 0x4c) = FUN_0040a530;
      *(code **)((int)camera + 0x50) = FUN_0040a570;
    }
    else {
      *(code **)((int)camera + 0x4c) = FUN_0040a470;
      *(code **)((int)camera + 0x50) = FUN_0040a4b0;
    }
  }
  else if (type == 1) {
    if (*(int *)((int)camera + 0x40) == 0x3f800000) {
      *(code **)((int)camera + 0x4c) = FUN_0040a6a0;
      *(code **)((int)camera + 0x50) = FUN_0040a6e0;
    }
    else {
      *(code **)((int)camera + 0x4c) = FUN_0040a5e0;
      *(code **)((int)camera + 0x50) = FUN_0040a620;
    }
  }
  if (*(int *)((int)camera + 4) != 0) {
    rdCamera_BuildProjection(camera);
  }
  return 1;
}

/* ---- 0x0040a1d0  rdCamera_SetZoom ---- */
void __cdecl rdCamera_SetZoom(void *camera,float zoom)

{
  *(float *)((int)camera + 0x40) = zoom;
  if (*(int *)camera == 0) {
    if (zoom == 1.0) {
      *(code **)((int)camera + 0x4c) = FUN_0040a530;
      *(code **)((int)camera + 0x50) = FUN_0040a570;
      rdCamera_BuildProjection(camera);
      return;
    }
    *(code **)((int)camera + 0x4c) = FUN_0040a470;
    *(code **)((int)camera + 0x50) = FUN_0040a4b0;
  }
  else if (*(int *)camera == 1) {
    if (zoom == 1.0) {
      *(code **)((int)camera + 0x4c) = FUN_0040a6a0;
      *(code **)((int)camera + 0x50) = FUN_0040a6e0;
      rdCamera_BuildProjection(camera);
      return;
    }
    *(code **)((int)camera + 0x4c) = FUN_0040a5e0;
    *(code **)((int)camera + 0x50) = FUN_0040a620;
    rdCamera_BuildProjection(camera);
    return;
  }
  rdCamera_BuildProjection(camera);
  return;
}

/* ---- 0x0040a280  rdCamera_BuildProjection ---- */
/* Computes the projection scale from FOV and canvas size and the frustum planes */

undefined4 rdCamera_BuildProjection(int *param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float10 fVar4;
  
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
    fVar4 = (float10)Math_SinDeg((float)param_1[0xe] * 0.5);
    param_1[0xf] = (int)(fVar2 / (float)fVar4);
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

/* ---- 0x0040a430  rdCamera_SetFrame ---- */
void __cdecl rdCamera_SetFrame(float *frame)

{
  int iVar1;
  float *pfVar2;
  
  Matrix_Transpose((float *)((int)g_pRdCurrentCamera + 8),frame);
  pfVar2 = (float *)&DAT_008ddf60;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar2 = *frame;
    frame = frame + 1;
    pfVar2 = pfVar2 + 1;
  }
  Matrix_ToAngles(&DAT_008ddf60,&DAT_008ddf50);
  return;
}

/* ---- 0x0040a470  FUN_0040a470 ---- */
void FUN_0040a470(float *param_1,float *param_2)

{
  int iVar1;
  
  iVar1 = *(int *)((int)g_pRdCurrentCamera + 4);
  *param_1 = *(float *)((int)g_pRdCurrentCamera + 0x44) * *param_2 + *(float *)(iVar1 + 8);
  param_1[1] = -(param_2[2] * *(float *)((int)g_pRdCurrentCamera + 0x44)) *
               *(float *)((int)g_pRdCurrentCamera + 0x40) + *(float *)(iVar1 + 0xc);
  param_1[2] = param_2[1];
  return;
}

/* ---- 0x0040a4b0  FUN_0040a4b0 ---- */
void FUN_0040a4b0(float *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar3 = *(float *)((int)g_pRdCurrentCamera + 0x44);
  fVar1 = *(float *)((int)g_pRdCurrentCamera + 0x40);
  fVar2 = *(float *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0xc);
  fVar4 = *(float *)(*(int *)((int)g_pRdCurrentCamera + 4) + 8);
  for (; param_3 != 0; param_3 = param_3 + -1) {
    *param_1 = fVar3 * *param_2 + fVar4;
    param_1[1] = fVar2 - param_2[2] * fVar1 * fVar3;
    param_1[2] = param_2[1];
    param_2 = param_2 + 3;
    param_1 = param_1 + 3;
  }
  return;
}

/* ---- 0x0040a530  FUN_0040a530 ---- */
void FUN_0040a530(float *param_1,float *param_2)

{
  int iVar1;
  
  iVar1 = *(int *)((int)g_pRdCurrentCamera + 4);
  *param_1 = *(float *)((int)g_pRdCurrentCamera + 0x44) * *param_2 + *(float *)(iVar1 + 8);
  param_1[1] = *(float *)(iVar1 + 0xc) - param_2[2] * *(float *)((int)g_pRdCurrentCamera + 0x44);
  param_1[2] = param_2[1];
  return;
}

/* ---- 0x0040a570  FUN_0040a570 ---- */
void FUN_0040a570(float *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = *(float *)((int)g_pRdCurrentCamera + 0x44);
  fVar2 = *(float *)(*(int *)((int)g_pRdCurrentCamera + 4) + 8);
  fVar3 = *(float *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0xc);
  for (; param_3 != 0; param_3 = param_3 + -1) {
    *param_1 = fVar1 * *param_2 + fVar2;
    param_1[1] = fVar3 - param_2[2] * fVar1;
    param_1[2] = param_2[1];
    param_1 = param_1 + 3;
    param_2 = param_2 + 3;
  }
  return;
}

/* ---- 0x0040a5e0  FUN_0040a5e0 ---- */
void FUN_0040a5e0(float *param_1,float *param_2)

{
  float fVar1;
  int iVar2;
  float fVar3;
  
  fVar3 = *(float *)((int)g_pRdCurrentCamera + 0x3c) / param_2[1];
  iVar2 = *(int *)((int)g_pRdCurrentCamera + 4);
  fVar1 = *(float *)((int)g_pRdCurrentCamera + 0x40);
  *param_1 = fVar3 * *param_2 + *(float *)(iVar2 + 8);
  param_1[1] = *(float *)(iVar2 + 0xc) - param_2[2] * fVar1 * fVar3;
  param_1[2] = param_2[1];
  return;
}

/* ---- 0x0040a620  FUN_0040a620 ---- */
void FUN_0040a620(float *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar2 = *(float *)(*(int *)((int)g_pRdCurrentCamera + 4) + 8);
  fVar3 = *(float *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0xc);
  for (; param_3 != 0; param_3 = param_3 + -1) {
    fVar4 = *(float *)((int)g_pRdCurrentCamera + 0x3c) / param_2[1];
    fVar1 = *(float *)((int)g_pRdCurrentCamera + 0x40);
    *param_1 = fVar4 * *param_2 + fVar2;
    param_1[1] = fVar3 - param_2[2] * fVar1 * fVar4;
    param_1[2] = param_2[1];
    param_1 = param_1 + 3;
    param_2 = param_2 + 3;
  }
  return;
}

/* ---- 0x0040a6a0  FUN_0040a6a0 ---- */
void FUN_0040a6a0(float *param_1,float *param_2)

{
  int iVar1;
  float fVar2;
  
  fVar2 = *(float *)((int)g_pRdCurrentCamera + 0x3c) / param_2[1];
  iVar1 = *(int *)((int)g_pRdCurrentCamera + 4);
  *param_1 = fVar2 * *param_2 + *(float *)(iVar1 + 8);
  param_1[1] = *(float *)(iVar1 + 0xc) - param_2[2] * fVar2;
  param_1[2] = param_2[1];
  return;
}

/* ---- 0x0040a6e0  FUN_0040a6e0 ---- */
void FUN_0040a6e0(float *param_1,float *param_2,int param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = *(float *)(*(int *)((int)g_pRdCurrentCamera + 4) + 8);
  fVar2 = *(float *)(*(int *)((int)g_pRdCurrentCamera + 4) + 0xc);
  for (; param_3 != 0; param_3 = param_3 + -1) {
    fVar3 = *(float *)((int)g_pRdCurrentCamera + 0x3c) / param_2[1];
    *param_1 = fVar3 * *param_2 + fVar1;
    param_1[1] = fVar2 - param_2[2] * fVar3;
    param_1[2] = param_2[1];
    param_1 = param_1 + 3;
    param_2 = param_2 + 3;
  }
  return;
}

/* ---- 0x0040a750  rdCamera_SetAmbientLight ---- */
/* Lua SetAmbientLight */

void __cdecl rdCamera_SetAmbientLight(void *camera,float ambient)

{
  *(float *)((int)camera + 0x54) = ambient;
  return;
}

/* ---- 0x0040a760  rdCamera_AddLight ---- */
/* Up to 64 lights per camera; stores the light pointer and position and precomputes the falloff
   terms */

int __cdecl rdCamera_AddLight(void *camera,void *light,float *position)

{
  float *pfVar1;
  
  if (0x40 < *(uint *)((int)camera + 0x58)) {
    return 0;
  }
  *(uint *)light = *(uint *)((int)camera + 0x58);
  *(void **)((int)camera + *(int *)((int)camera + 0x58) * 4 + 0x5c) = light;
  pfVar1 = (float *)((int)camera + (*(int *)((int)camera + 0x58) + 0x1d) * 0xc);
  *pfVar1 = *position;
  pfVar1[1] = position[1];
  pfVar1[2] = position[2];
  *(float *)((int)light + 0x34) = *(float *)((int)light + 0x18) / *(float *)((int)camera + 0x45c);
  *(float *)((int)light + 0x38) = *(float *)((int)light + 0x18) / *(float *)((int)camera + 0x460);
  *(int *)((int)camera + 0x58) = *(int *)((int)camera + 0x58) + 1;
  return 1;
}

/* ---- 0x0040a7d0  rdCamera_ClearCanvas ---- */
void rdCamera_ClearCanvas(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *puVar1;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  if (((g_pRdCurrentCamera != (void *)0x0) &&
      (puVar1 = *(uint **)((int)g_pRdCurrentCamera + 4), (g_dwRdroidFlags & 0x100) != 0)) &&
     ((*puVar1 & 2) != 0)) {
    if (0 < g_nRdroid3DAccel) {
      D3D_ClearZBuffer();
      return;
    }
    if ((*puVar1 & 1) != 0) {
      local_10 = puVar1[6];
      local_c = puVar1[7];
      local_8 = (puVar1[8] - puVar1[6]) + 1;
      local_4 = (puVar1[9] - puVar1[7]) + 1;
      Surface_Fill((void *)puVar1[4],0,(int *)&local_10);
      return;
    }
    Surface_Fill((void *)puVar1[4],0,(int *)0x0);
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0040a860  rdCamera_ResetStats ---- */
void rdCamera_ResetStats(void)

{
  DAT_007f31ec = 0;
  return;
}

/* ---- 0x0040dc30  rdCamera_ProjectPoint ---- */
/* Lua WorldToScreen; returns 0 when the point is behind the camera */

int __cdecl rdCamera_ProjectPoint(float *world,float *outScreen)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  #define local_18 (*(undefined1 (*)[8])(_frame + (0x30 - 0x18)))
  #define fStack_10 (*(float *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float (*)[3])(_frame + (0x30 - 0xc)))
  
  Vec3_Sub(local_c,world,(float *)((int)g_pRdCurrentCamera + 8));
  iVar1 = rdClip_PointInFrustum(*(void **)((int)g_pRdCurrentCamera + 0x48),local_c);
  if (iVar1 != 0) {
    (**(code **)((int)g_pRdCurrentCamera + 0x4c))(local_18,local_c);
    if (outScreen != (float *)0x0) {
      fVar2 = (float)_ftol();
      *outScreen = fVar2;
      fVar2 = (float)_ftol();
      outScreen[1] = fVar2;
      outScreen[2] = fStack_10;
    }
    return 1;
  }
  return 0;
}
#undef fStack_10
#undef local_18
#undef local_c

