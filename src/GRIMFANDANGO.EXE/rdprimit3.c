/* GRIMFANDANGO.EXE :: rdprimit3.c
 * functions 0x00409d50 .. 0x0040e500 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00409d50  rdCache_InsertFace ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name rdCache_InsertFace (the remaster's GrimFandango (Linux): same body (the vertices
   through the current camera, their centre, a new proc face of the material, the face normal from a
   cross product, rdCache_AddProcFace)); was rdPrimit3_DrawPolygon. */

void * __cdecl rdCache_InsertFace(float *verts,int count,void *material)

{
  unsigned char _frame[0x340] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  uint vertexCount;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  float *out;
  undefined4 *puVar5;
  undefined4 *puVar6;
  #define local_330 (*(float (*)[3])(_frame + (0x340 - 0x330)))
  #define fStack_324 (*(float *)(_frame + (0x340 - 0x324)))
  #define fStack_320 (*(float *)(_frame + (0x340 - 0x320)))
  #define fStack_31c (*(float *)(_frame + (0x340 - 0x31c)))
  #define fStack_318 (*(float *)(_frame + (0x340 - 0x318)))
  #define fStack_314 (*(float *)(_frame + (0x340 - 0x314)))
  #define fStack_310 (*(float *)(_frame + (0x340 - 0x310)))
  #define fStack_30c (*(float *)(_frame + (0x340 - 0x30c)))
  #define fStack_308 (*(float *)(_frame + (0x340 - 0x308)))
  #define fStack_304 (*(float *)(_frame + (0x340 - 0x304)))
  #define local_300 (*(float *)(_frame + (0x340 - 0x300)))
  #define local_2fc (*(float (*)[2])(_frame + (0x340 - 0x2fc)))
  #define fStack_2f4 (*(float *)(_frame + (0x340 - 0x2f4)))
  #define fStack_2f0 (*(float *)(_frame + (0x340 - 0x2f0)))
  #define fStack_2ec (*(float *)(_frame + (0x340 - 0x2ec)))
  #define fStack_2e8 (*(float *)(_frame + (0x340 - 0x2e8)))
  #define fStack_2e4 (*(float *)(_frame + (0x340 - 0x2e4)))
  #define fStack_2e0 (*(float *)(_frame + (0x340 - 0x2e0)))
  #define local_180 (*(undefined4 (*)[96])(_frame + (0x340 - 0x180)))
  
  local_330[2] = 0.0;
  local_330[1] = 0.0;
  local_330[0] = 0.0;
  if (0 < count) {
    iVar4 = count;
    out = &local_300;
    do {
      rdMatrix_TransformPoint34
                (out,(float *)(((int)verts - (int)&local_300) + (int)out),
                 (float *)((int)g_pRdCamera_CurCamera + 8));
      local_330[0] = local_330[0] + *out;
      iVar4 = iVar4 + -1;
      local_330[1] = out[1] + local_330[1];
      local_330[2] = out[2] + local_330[2];
      out = out + 3;
    } while (iVar4 != 0);
  }
  fVar1 = (float)count;
  vertexCount = rdClip_Face3S(*(int **)((int)g_pRdCamera_CurCamera + 0x48),&local_300,count);
  if ((int)vertexCount < 3) {
    return (void *)0x0;
  }
  (**(code **)((int)g_pRdCamera_CurCamera + 0x50))(local_180,&local_300,vertexCount);
  pbVar2 = rdCache_GetProcEntry();
  pbVar2[0] = 0;
  pbVar2[1] = 0;
  pbVar2[2] = 0;
  pbVar2[3] = 0;
  pbVar2[0x44] = 0;
  pbVar2[0x45] = 0;
  pbVar2[0x46] = 0;
  pbVar2[0x47] = 0;
  pbVar2[0x48] = 0;
  pbVar2[0x49] = 0;
  pbVar2[0x4a] = 0;
  pbVar2[0x4b] = 0;
  pbVar2[0x3c] = 0;
  pbVar2[0x3d] = 0;
  pbVar2[0x3e] = 0;
  pbVar2[0x3f] = 0;
  pbVar2[4] = 1;
  pbVar2[5] = 0;
  pbVar2[6] = 0;
  pbVar2[7] = 0;
  pbVar2[0xc] = 1;
  pbVar2[0xd] = 0;
  pbVar2[0xe] = 0;
  pbVar2[0xf] = 0;
  pbVar2[8] = 3;
  pbVar2[9] = 0;
  pbVar2[10] = 0;
  pbVar2[0xb] = 0;
  *(uint *)(pbVar2 + 0x1c) = vertexCount;
  puVar5 = local_180;
  puVar6 = *(undefined4 **)(pbVar2 + 0x20);
  for (uVar3 = vertexCount * 3 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
    puVar6 = (undefined4 *)((int)puVar6 + 1);
  }
  pbVar2[0x3c] = 0xff;
  pbVar2[0x3d] = 0xff;
  pbVar2[0x3e] = 0xff;
  pbVar2[0x3f] = 0xff;
  *(void **)(pbVar2 + 0x38) = material;
  fStack_324 = fStack_2f4 - local_300;
  fStack_320 = fStack_2f0 - local_2fc[0];
  fStack_31c = fStack_2ec - local_2fc[1];
  fStack_30c = fStack_2e8 - fStack_2f4;
  fStack_308 = fStack_2e4 - fStack_2f0;
  fStack_304 = fStack_2e0 - fStack_2ec;
  rdVector_Cross3(&fStack_318,&fStack_324,&fStack_30c);
  *(uint *)(pbVar2 + 0x50) =
       (uint)(0.0 < fStack_310 * (local_330[2] / fVar1) +
                    fStack_314 * (local_330[1] / fVar1) + fStack_318 * (local_330[0] / fVar1));
  rdCache_AddProcFace((void *)0x0,vertexCount,1);
  return pbVar2;
}
#undef fStack_2e0
#undef fStack_2e4
#undef fStack_2e8
#undef fStack_2ec
#undef fStack_2f0
#undef fStack_2f4
#undef fStack_304
#undef fStack_308
#undef fStack_30c
#undef fStack_310
#undef fStack_314
#undef fStack_318
#undef fStack_31c
#undef fStack_320
#undef fStack_324
#undef local_180
#undef local_2fc
#undef local_300
#undef local_330

#endif


/* ---- 0x0040dcc0  rdPrimit3_DrawLine ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Clips a world-space segment against the camera frustum, projects it and draws it with
   rdCanvas_DrawLine */

undefined4 __cdecl
rdPrimit3_DrawLine(float *a,float *b,int *outA,int *outB,int *clipA,int *clipB,uint color,
                  uint pattern)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  #define local_30 (*(undefined1 (*)[8])(_frame + (0x40 - 0x30)))
  #define iStack_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define auStack_24 (*(undefined1 (*)[8])(_frame + (0x40 - 0x24)))
  #define iStack_1c (*(int *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  rdMatrix_TransformPoint34(local_18,a,(float *)((int)g_pRdCamera_CurCamera + 8));
  rdMatrix_TransformPoint34(local_c,b,(float *)((int)g_pRdCamera_CurCamera + 8));
  iVar1 = rdClip_Line3(*(void **)((int)g_pRdCamera_CurCamera + 0x48),local_18,local_c,clipA,clipB);
  if (iVar1 != 0) {
    (**(code **)((int)g_pRdCamera_CurCamera + 0x4c))(local_30,local_18);
    (**(code **)((int)g_pRdCamera_CurCamera + 0x4c))(auStack_24,local_c);
    lVar2 = _ftol((double)CONCAT44(unaff_ESI,unaff_EBX));
    lVar3 = _ftol((double)CONCAT44(unaff_ESI,unaff_EBX));
    if (outA != (int *)0x0) {
      *outA = (int)lVar2;
      outA[1] = (int)lVar3;
      outA[2] = iStack_28;
    }
    lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EBX));
    lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EBX));
    if (outB != (int *)0x0) {
      *outB = (int)lVar4;
      outB[1] = (int)lVar5;
      outB[2] = iStack_1c;
    }
    rdCanvas_DrawLine(*(void **)((int)g_pRdCamera_CurCamera + 4),(int)lVar2,(int)lVar3,(int)lVar4,
                      (int)lVar5,(ushort)color,pattern);
    return 1;
  }
  return 0;
}
#undef auStack_24
#undef iStack_1c
#undef iStack_28
#undef local_18
#undef local_30
#undef local_c

#endif


/* ---- 0x0040dde0  rdPrimit3_DrawPoint ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Projects a world-space point with a radius and draws it as a 2D point */

void __cdecl rdPrimit3_DrawPoint(float *world,float radius,uint a3,uint a4,uint a5)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  longlong lVar2;
  float fVar3;
  #define local_30 (*(float *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(float (*)[2])(_frame + (0x40 - 0x2c)))
  #define local_24 (*(float (*)[3])(_frame + (0x40 - 0x24)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define afStack_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  rdMatrix_TransformPoint34(&local_30,world,(float *)((int)g_pRdCamera_CurCamera + 8));
  local_24[0] = local_30 + radius;
  local_24[1] = local_2c[0];
  local_24[2] = local_2c[1];
  if (0.0 < local_2c[0]) {
    (**(code **)((int)g_pRdCamera_CurCamera + 0x4c))(local_18,&local_30);
    (**(code **)((int)g_pRdCamera_CurCamera + 0x4c))(afStack_c,local_24);
    fVar3 = afStack_c[0] - local_18[0];
    lVar2 = _ftol((double)CONCAT44(a3,fVar3));
    iVar1 = (int)lVar2;
    lVar2 = _ftol((double)CONCAT44(fVar3,iVar1));
    rdCanvas_DrawPoint(*(void **)((int)g_pRdCamera_CurCamera + 4),(int)lVar2,iVar1,PUN(uint,(float)fVar3),
                       PUN(float,a3),a4,a5);
  }
  return;
}
#undef afStack_c
#undef local_18
#undef local_24
#undef local_2c
#undef local_30

#endif


/* ---- 0x0040deb0  rdPrimit3_ClipFace ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Clips one face against the frustum; the switch selects the vertex attribute set from the
   geometry/lighting modes */

void __cdecl
rdPrimit3_ClipFace(uint param_1,uint param_2,int param_3,uint param_4,uint *param_5,uint *param_6,
                  float *param_7)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint extraout_EAX;
  uint extraout_EAX_00;
  uint uVar7;
  uint extraout_EAX_01;
  undefined4 *puVar8;
  int iVar9;
  undefined4 *puVar10;
  
  puVar6 = param_6;
  puVar5 = param_5;
  switch(param_2) {
  case 0:
    uVar7 = 0;
    if (*param_5 != 0) {
      iVar9 = 0;
      do {
        puVar8 = (undefined4 *)(param_5[3] + *(int *)(param_5[1] + uVar7 * 4) * 0xc);
        puVar10 = (undefined4 *)(iVar9 + param_6[3]);
        uVar7 = uVar7 + 1;
        iVar9 = iVar9 + 0xc;
        *puVar10 = *puVar8;
        puVar10[1] = puVar8[1];
        puVar10[2] = puVar8[2];
      } while (uVar7 < *param_5);
    }
    break;
  case 1:
  case 2:
    uVar7 = 0;
    if (*param_5 != 0) {
      iVar9 = 0;
      do {
        puVar8 = (undefined4 *)(param_5[3] + *(int *)(param_5[1] + uVar7 * 4) * 0xc);
        puVar10 = (undefined4 *)(iVar9 + param_6[3]);
        uVar7 = uVar7 + 1;
        iVar9 = iVar9 + 0xc;
        *puVar10 = *puVar8;
        puVar10[1] = puVar8[1];
        puVar10[2] = puVar8[2];
      } while (uVar7 < *param_5);
    }
    if (*(int *)g_pRdCamera_CurCamera != 1) {
      uVar7 = rdClip_Face3WOrtho((int *)param_1,(float *)param_6[3],*param_5);
      *param_6 = uVar7;
      return;
    }
    uVar7 = rdClip_Face3W((int *)param_1,(float *)param_6[3],*param_5);
    *param_6 = uVar7;
    return;
  case 3:
    switch(param_3) {
    case 0:
    case 1:
      uVar7 = 0;
      if (*param_5 != 0) {
        iVar9 = 0;
        do {
          puVar8 = (undefined4 *)(param_5[3] + *(int *)(param_5[1] + uVar7 * 4) * 0xc);
          puVar10 = (undefined4 *)(iVar9 + param_6[3]);
          uVar7 = uVar7 + 1;
          iVar9 = iVar9 + 0xc;
          *puVar10 = *puVar8;
          puVar10[1] = puVar8[1];
          puVar10[2] = puVar8[2];
        } while (uVar7 < *param_5);
      }
      break;
    case 2:
      uVar7 = 0;
      if (*param_5 != 0) {
        iVar9 = 0;
        do {
          puVar8 = (undefined4 *)(param_5[3] + *(int *)(param_5[1] + uVar7 * 4) * 0xc);
          puVar10 = (undefined4 *)(iVar9 + param_6[3]);
          uVar7 = uVar7 + 1;
          iVar9 = iVar9 + 0xc;
          *puVar10 = *puVar8;
          puVar10[1] = puVar8[1];
          puVar10[2] = puVar8[2];
        } while (uVar7 < *param_5);
      }
      break;
    case 3:
      if (param_5[6] == 0) {
        uVar7 = 0;
        if (*param_5 != 0) {
          iVar9 = 0;
          do {
            puVar8 = (undefined4 *)(param_5[3] + *(int *)(param_5[1] + uVar7 * 4) * 0xc);
            puVar10 = (undefined4 *)(iVar9 + param_6[3]);
            *puVar10 = *puVar8;
            puVar10[1] = puVar8[1];
            puVar10[2] = puVar8[2];
            iVar3 = *(int *)(param_5[1] + uVar7 * 4);
            pfVar1 = (float *)(param_5[5] + iVar3 * 4);
            if (*(float *)(param_5[5] + iVar3 * 4) < 0.0) {
              fVar2 = 0.0;
            }
            else if (1.0 < *pfVar1) {
              fVar2 = 1.0;
            }
            else {
              fVar2 = *pfVar1;
            }
            uVar7 = uVar7 + 1;
            iVar9 = iVar9 + 0xc;
            *(float *)((param_6[5] - 4) + uVar7 * 4) = fVar2;
          } while (uVar7 < *param_5);
        }
      }
      else {
        uVar7 = 0;
        if (*param_5 != 0) {
          iVar9 = 0;
          do {
            puVar8 = (undefined4 *)(param_5[3] + *(int *)(param_5[1] + uVar7 * 4) * 0xc);
            puVar10 = (undefined4 *)(iVar9 + param_6[3]);
            *puVar10 = *puVar8;
            puVar10[1] = puVar8[1];
            puVar10[2] = puVar8[2];
            fVar2 = *(float *)(param_5[5] + *(int *)(param_5[1] + uVar7 * 4) * 4) +
                    *(float *)(param_5[6] + uVar7 * 4);
            if (fVar2 < 0.0) {
              fVar2 = 0.0;
            }
            else if (1.0 < fVar2) {
              fVar2 = 1.0;
            }
            uVar7 = uVar7 + 1;
            iVar9 = iVar9 + 0xc;
            *(float *)((param_6[5] - 4) + uVar7 * 4) = fVar2;
          } while (uVar7 < *param_5);
        }
      }
      if (*(int *)g_pRdCamera_CurCamera != 1) {
        uVar7 = rdClip_Face3GSOrtho((int *)param_1,(float *)param_6[3],(float *)param_6[5],*param_5)
        ;
        *param_6 = uVar7;
        return;
      }
      rdClip_Face3GS((int *)param_1,(float *)param_6[3],(float *)param_6[5],(float *)*param_5);
      *param_6 = extraout_EAX;
      return;
    default:
      goto switchD_0040dec1_default;
    }
    break;
  case 4:
    if (-1 < param_3) {
      if (param_3 < 3) {
        uVar7 = 0;
        if (*param_5 != 0) {
          param_5 = (uint *)0x0;
          do {
            puVar8 = (undefined4 *)(puVar5[3] + *(int *)(puVar5[1] + uVar7 * 4) * 0xc);
            puVar10 = (undefined4 *)((int)param_5 + param_6[3]);
            *puVar10 = *puVar8;
            puVar10[1] = puVar8[1];
            puVar10[2] = puVar8[2];
            uVar4 = puVar5[4];
            iVar9 = *(int *)(puVar5[2] + uVar7 * 4);
            puVar8 = (undefined4 *)(uVar7 * 8 + param_6[4]);
            *puVar8 = *(undefined4 *)(uVar4 + iVar9 * 8);
            puVar8[1] = *(undefined4 *)(uVar4 + 4 + iVar9 * 8);
            pfVar1 = (float *)(param_6[4] + uVar7 * 8);
            *pfVar1 = *param_7 + *pfVar1;
            iVar9 = uVar7 * 8;
            iVar3 = uVar7 * 8;
            uVar7 = uVar7 + 1;
            param_5 = param_5 + 3;
            *(float *)(param_6[4] + 4 + iVar3) = *(float *)(param_6[4] + 4 + iVar9) + param_7[1];
          } while (uVar7 < *puVar5);
        }
        if (*(int *)g_pRdCamera_CurCamera == 1) {
          rdClip_Face3T((int *)param_1,(float *)param_6[3],(float *)param_6[4],(float *)*puVar5);
          *param_6 = extraout_EAX_01;
          return;
        }
        uVar7 = rdClip_Face3TOrtho((int *)param_1,(float *)param_6[3],(float *)param_6[4],*puVar5);
        *param_6 = uVar7;
      }
      else if (param_3 == 3) {
        if (param_5[6] == 0) {
          uVar7 = *param_5;
          param_5 = (uint *)0x0;
          if (uVar7 != 0) {
            param_6 = (uint *)0x0;
            do {
              puVar8 = (undefined4 *)(puVar5[3] + *(int *)(puVar5[1] + (int)param_5 * 4) * 0xc);
              puVar10 = (undefined4 *)((int)param_6 + puVar6[3]);
              *puVar10 = *puVar8;
              puVar10[1] = puVar8[1];
              puVar10[2] = puVar8[2];
              uVar7 = puVar6[4];
              iVar9 = (int)param_5 * 8;
              iVar3 = *(int *)(puVar5[2] + (int)param_5 * 4);
              uVar4 = puVar5[4];
              *(undefined4 *)(iVar9 + uVar7) = *(undefined4 *)(uVar4 + iVar3 * 8);
              ((undefined4 *)(iVar9 + uVar7))[1] = *(undefined4 *)(uVar4 + 4 + iVar3 * 8);
              *(float *)(puVar6[4] + iVar9) = *param_7 + *(float *)(puVar6[4] + iVar9);
              *(float *)(iVar9 + 4 + puVar6[4]) = *(float *)(iVar9 + 4 + puVar6[4]) + param_7[1];
              iVar9 = *(int *)(puVar5[1] + (int)param_5 * 4);
              pfVar1 = (float *)(puVar5[5] + iVar9 * 4);
              if (*(float *)(puVar5[5] + iVar9 * 4) < 0.0) {
                fVar2 = 0.0;
              }
              else if (1.0 < *pfVar1) {
                fVar2 = 1.0;
              }
              else {
                fVar2 = *pfVar1;
              }
              param_6 = param_6 + 3;
              *(float *)(puVar6[5] + (int)param_5 * 4) = fVar2;
              param_5 = (uint *)((int)param_5 + 1);
            } while (param_5 < (uint *)*puVar5);
          }
        }
        else {
          uVar7 = *param_5;
          param_5 = (uint *)0x0;
          if (uVar7 != 0) {
            param_6 = (uint *)0x0;
            do {
              puVar8 = (undefined4 *)(puVar5[3] + *(int *)(puVar5[1] + (int)param_5 * 4) * 0xc);
              puVar10 = (undefined4 *)((int)param_6 + puVar6[3]);
              *puVar10 = *puVar8;
              puVar10[1] = puVar8[1];
              puVar10[2] = puVar8[2];
              uVar7 = puVar6[4];
              iVar9 = (int)param_5 * 8;
              iVar3 = *(int *)(puVar5[2] + (int)param_5 * 4);
              uVar4 = puVar5[4];
              *(undefined4 *)(iVar9 + uVar7) = *(undefined4 *)(uVar4 + iVar3 * 8);
              ((undefined4 *)(iVar9 + uVar7))[1] = *(undefined4 *)(uVar4 + 4 + iVar3 * 8);
              *(float *)(puVar6[4] + iVar9) = *param_7 + *(float *)(puVar6[4] + iVar9);
              *(float *)(iVar9 + 4 + puVar6[4]) = *(float *)(iVar9 + 4 + puVar6[4]) + param_7[1];
              fVar2 = *(float *)(puVar5[5] + *(int *)(puVar5[1] + (int)param_5 * 4) * 4) +
                      *(float *)(puVar5[6] + (int)param_5 * 4);
              if (fVar2 < 0.0) {
                fVar2 = 0.0;
              }
              else if (1.0 < fVar2) {
                fVar2 = 1.0;
              }
              param_6 = param_6 + 3;
              *(float *)(puVar6[5] + (int)param_5 * 4) = fVar2;
              param_5 = (uint *)((int)param_5 + 1);
            } while (param_5 < (uint *)*puVar5);
          }
        }
        if (*(int *)g_pRdCamera_CurCamera != 1) {
          uVar7 = rdClip_Face3GTOrtho((int *)param_1,(float *)puVar6[3],(uint *)puVar6[4],
                                      (uint *)puVar6[5],*puVar5);
          *puVar6 = uVar7;
          return;
        }
        rdClip_Face3GT((int *)param_1,(float *)puVar6[3],(float *)puVar6[4],(uint *)puVar6[5],
                       (float *)*puVar5);
        *puVar6 = extraout_EAX_00;
        return;
      }
    }
  default:
switchD_0040dec1_default:
    return;
  }
  if (*(int *)g_pRdCamera_CurCamera != 1) {
    uVar7 = rdClip_Face3SOrtho((int *)param_1,(float *)param_6[3],*param_5);
    *param_6 = uVar7;
    return;
  }
  uVar7 = rdClip_Face3S((int *)param_1,(float *)param_6[3],*param_5);
  *param_6 = uVar7;
  return;
}
#endif


/* ---- 0x0040e500  rdPrimit3_NoClipFace ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Copies the face's vertex attributes (position, uv, intensity) into the cache pools without
   clipping Original name rdPrimit3_NoClipFace (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_DrawFace); was rdPrimit3_CopyFaceVerts. */

void __cdecl
rdPrimit3_NoClipFace
          (uint param_1,int param_2,uint param_3,uint *param_4,uint *param_5,float *param_6)

{
  undefined4 *puVar1;
  float *pfVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint *puVar8;
  uint uVar9;
  int iVar10;
  undefined4 *puVar11;
  
  puVar8 = param_5;
  puVar7 = param_4;
  switch(param_1) {
  case 0:
    uVar9 = 0;
    if (*param_4 != 0) {
      iVar10 = 0;
      do {
        puVar1 = (undefined4 *)(param_4[3] + *(int *)(param_4[1] + uVar9 * 4) * 0xc);
        puVar11 = (undefined4 *)(iVar10 + param_5[3]);
        uVar9 = uVar9 + 1;
        iVar10 = iVar10 + 0xc;
        *puVar11 = *puVar1;
        puVar11[1] = puVar1[1];
        puVar11[2] = puVar1[2];
      } while (uVar9 < *param_4);
      *param_5 = *param_4;
      return;
    }
    break;
  case 1:
  case 2:
    uVar9 = 0;
    if (*param_4 != 0) {
      iVar10 = 0;
      do {
        puVar1 = (undefined4 *)(param_4[3] + *(int *)(param_4[1] + uVar9 * 4) * 0xc);
        puVar11 = (undefined4 *)(iVar10 + param_5[3]);
        uVar9 = uVar9 + 1;
        iVar10 = iVar10 + 0xc;
        *puVar11 = *puVar1;
        puVar11[1] = puVar1[1];
        puVar11[2] = puVar1[2];
      } while (uVar9 < *param_4);
      *param_5 = *param_4;
      return;
    }
    break;
  case 3:
    switch(param_2) {
    case 0:
    case 1:
      uVar9 = 0;
      if (*param_4 != 0) {
        iVar10 = 0;
        do {
          puVar1 = (undefined4 *)(param_4[3] + *(int *)(param_4[1] + uVar9 * 4) * 0xc);
          puVar11 = (undefined4 *)(iVar10 + param_5[3]);
          uVar9 = uVar9 + 1;
          iVar10 = iVar10 + 0xc;
          *puVar11 = *puVar1;
          puVar11[1] = puVar1[1];
          puVar11[2] = puVar1[2];
        } while (uVar9 < *param_4);
        goto LAB_0040e609;
      }
      break;
    case 2:
      uVar9 = 0;
      if (*param_4 != 0) {
        iVar10 = 0;
        do {
          puVar1 = (undefined4 *)(param_4[3] + *(int *)(param_4[1] + uVar9 * 4) * 0xc);
          puVar11 = (undefined4 *)(iVar10 + param_5[3]);
          uVar9 = uVar9 + 1;
          iVar10 = iVar10 + 0xc;
          *puVar11 = *puVar1;
          puVar11[1] = puVar1[1];
          puVar11[2] = puVar1[2];
        } while (uVar9 < *param_4);
      }
      break;
    case 3:
      if (param_4[6] == 0) {
        uVar9 = 0;
        if (*param_4 != 0) {
          iVar10 = 0;
          do {
            puVar1 = (undefined4 *)(param_4[3] + *(int *)(param_4[1] + uVar9 * 4) * 0xc);
            puVar11 = (undefined4 *)(iVar10 + param_5[3]);
            *puVar11 = *puVar1;
            puVar11[1] = puVar1[1];
            puVar11[2] = puVar1[2];
            iVar4 = *(int *)(param_4[1] + uVar9 * 4);
            pfVar2 = (float *)(param_4[5] + iVar4 * 4);
            if (*(float *)(param_4[5] + iVar4 * 4) < 0.0) {
              fVar3 = 0.0;
            }
            else if (1.0 < *pfVar2) {
              fVar3 = 1.0;
            }
            else {
              fVar3 = *pfVar2;
            }
            uVar9 = uVar9 + 1;
            iVar10 = iVar10 + 0xc;
            *(float *)((param_5[5] - 4) + uVar9 * 4) = fVar3;
          } while (uVar9 < *param_4);
          *param_5 = *param_4;
          return;
        }
      }
      else {
        uVar9 = 0;
        if (*param_4 != 0) {
          iVar10 = 0;
          do {
            puVar1 = (undefined4 *)(param_4[3] + *(int *)(param_4[1] + uVar9 * 4) * 0xc);
            puVar11 = (undefined4 *)(iVar10 + param_5[3]);
            *puVar11 = *puVar1;
            puVar11[1] = puVar1[1];
            puVar11[2] = puVar1[2];
            fVar3 = *(float *)(param_4[5] + *(int *)(param_4[1] + uVar9 * 4) * 4) +
                    *(float *)(param_4[6] + uVar9 * 4);
            if (fVar3 < 0.0) {
              fVar3 = 0.0;
            }
            else if (1.0 < fVar3) {
              fVar3 = 1.0;
            }
            uVar9 = uVar9 + 1;
            iVar10 = iVar10 + 0xc;
            *(float *)((param_5[5] - 4) + uVar9 * 4) = fVar3;
          } while (uVar9 < *param_4);
          *param_5 = *param_4;
          return;
        }
      }
LAB_0040e982:
      *puVar8 = *puVar7;
      return;
    default:
      goto switchD_0040e511_default;
    }
    *param_5 = *param_4;
    return;
  case 4:
    if (-1 < param_2) {
      if (param_2 < 3) {
        uVar9 = 0;
        if (*param_4 != 0) {
          param_4 = (uint *)0x0;
          do {
            puVar1 = (undefined4 *)(puVar7[3] + *(int *)(puVar7[1] + uVar9 * 4) * 0xc);
            puVar11 = (undefined4 *)((int)param_4 + param_5[3]);
            *puVar11 = *puVar1;
            puVar11[1] = puVar1[1];
            puVar11[2] = puVar1[2];
            uVar5 = puVar7[4];
            iVar10 = uVar9 * 8;
            iVar4 = *(int *)(puVar7[2] + uVar9 * 4);
            uVar6 = param_5[4];
            *(undefined4 *)(iVar10 + uVar6) = *(undefined4 *)(uVar5 + iVar4 * 8);
            ((undefined4 *)(iVar10 + uVar6))[1] = *(undefined4 *)(uVar5 + 4 + iVar4 * 8);
            uVar9 = uVar9 + 1;
            *(float *)(param_5[4] + iVar10) = *param_6 + *(float *)(param_5[4] + iVar10);
            param_4 = param_4 + 3;
            *(float *)(iVar10 + 4 + param_5[4]) = *(float *)(iVar10 + 4 + param_5[4]) + param_6[1];
          } while (uVar9 < *puVar7);
        }
        *param_5 = *puVar7;
      }
      else if (param_2 == 3) {
        if (param_4[6] == 0) {
          param_5 = (uint *)0x0;
          if (*param_4 != 0) {
            param_4 = (uint *)0x0;
            do {
              puVar1 = (undefined4 *)(puVar7[3] + *(int *)(puVar7[1] + (int)param_5 * 4) * 0xc);
              puVar11 = (undefined4 *)((int)param_4 + puVar8[3]);
              *puVar11 = *puVar1;
              puVar11[1] = puVar1[1];
              puVar11[2] = puVar1[2];
              uVar9 = puVar8[4];
              iVar10 = (int)param_5 * 8;
              iVar4 = *(int *)(puVar7[2] + (int)param_5 * 4);
              uVar5 = puVar7[4];
              *(undefined4 *)(iVar10 + uVar9) = *(undefined4 *)(uVar5 + iVar4 * 8);
              ((undefined4 *)(iVar10 + uVar9))[1] = *(undefined4 *)(uVar5 + 4 + iVar4 * 8);
              *(float *)(puVar8[4] + iVar10) = *param_6 + *(float *)(puVar8[4] + iVar10);
              *(float *)(iVar10 + 4 + puVar8[4]) = *(float *)(iVar10 + 4 + puVar8[4]) + param_6[1];
              iVar10 = *(int *)(puVar7[1] + (int)param_5 * 4);
              pfVar2 = (float *)(puVar7[5] + iVar10 * 4);
              if (*(float *)(puVar7[5] + iVar10 * 4) < 0.0) {
                fVar3 = 0.0;
              }
              else if (1.0 < *pfVar2) {
                fVar3 = 1.0;
              }
              else {
                fVar3 = *pfVar2;
              }
              param_4 = param_4 + 3;
              *(float *)(puVar8[5] + (int)param_5 * 4) = fVar3;
              param_5 = (uint *)((int)param_5 + 1);
            } while (param_5 < (uint *)*puVar7);
          }
        }
        else {
          param_5 = (uint *)0x0;
          if (*param_4 != 0) {
            param_4 = (uint *)0x0;
            do {
              puVar1 = (undefined4 *)(puVar7[3] + *(int *)(puVar7[1] + (int)param_5 * 4) * 0xc);
              puVar11 = (undefined4 *)((int)param_4 + puVar8[3]);
              *puVar11 = *puVar1;
              puVar11[1] = puVar1[1];
              puVar11[2] = puVar1[2];
              uVar9 = puVar8[4];
              iVar10 = (int)param_5 * 8;
              iVar4 = *(int *)(puVar7[2] + (int)param_5 * 4);
              uVar5 = puVar7[4];
              *(undefined4 *)(iVar10 + uVar9) = *(undefined4 *)(uVar5 + iVar4 * 8);
              ((undefined4 *)(iVar10 + uVar9))[1] = *(undefined4 *)(uVar5 + 4 + iVar4 * 8);
              *(float *)(puVar8[4] + iVar10) = *param_6 + *(float *)(puVar8[4] + iVar10);
              *(float *)(iVar10 + 4 + puVar8[4]) = *(float *)(iVar10 + 4 + puVar8[4]) + param_6[1];
              fVar3 = *(float *)(puVar7[5] + *(int *)(puVar7[1] + (int)param_5 * 4) * 4) +
                      *(float *)(puVar7[6] + (int)param_5 * 4);
              if (fVar3 < 0.0) {
                fVar3 = 0.0;
              }
              else if (1.0 < fVar3) {
                fVar3 = 1.0;
              }
              param_4 = param_4 + 3;
              *(float *)(puVar8[5] + (int)param_5 * 4) = fVar3;
              param_5 = (uint *)((int)param_5 + 1);
            } while (param_5 < (uint *)*puVar7);
            *puVar8 = *puVar7;
            return;
          }
        }
        goto LAB_0040e982;
      }
    }
  default:
switchD_0040e511_default:
    return;
  }
LAB_0040e609:
  *param_5 = *param_4;
  return;
}
#endif

