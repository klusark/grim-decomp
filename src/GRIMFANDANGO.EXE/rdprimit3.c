/* GRIMFANDANGO.EXE :: rdprimit3.c
 * functions 0x00409d50 .. 0x0040e500 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00409d50  rdPrimit3_DrawPolygon ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void * __cdecl rdPrimit3_DrawPolygon(float *verts,int count,void *material)

{
  unsigned char _frame[0x340] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  uint vertexCount;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  float *out;
  undefined4 *puVar5;
  undefined4 *puVar6;
  #define local_330 (*(uint *)(_frame + (0x340 - 0x330)))
  #define local_32c (*(uint *)(_frame + (0x340 - 0x32c)))
  #define local_328 (*(uint *)(_frame + (0x340 - 0x328)))
  #define fStack_324 (*(float *)(_frame + (0x340 - 0x324)))
  #define fStack_320 (*(float *)(_frame + (0x340 - 0x320)))
  #define fStack_31c (*(float *)(_frame + (0x340 - 0x31c)))
  #define fStack_318 (*(float *)(_frame + (0x340 - 0x318)))
  #define fStack_314 (*(float *)(_frame + (0x340 - 0x314)))
  #define fStack_310 (*(float *)(_frame + (0x340 - 0x310)))
  #define fStack_30c (*(float *)(_frame + (0x340 - 0x30c)))
  #define fStack_308 (*(float *)(_frame + (0x340 - 0x308)))
  #define fStack_304 (*(float *)(_frame + (0x340 - 0x304)))
  #define local_300 (*(uint *)(_frame + (0x340 - 0x300)))
  #define local_2fc (*(uint *)(_frame + (0x340 - 0x2fc)))
  #define local_2f8 (*(uint *)(_frame + (0x340 - 0x2f8)))
  #define fStack_2f4 (*(float *)(_frame + (0x340 - 0x2f4)))
  #define fStack_2f0 (*(float *)(_frame + (0x340 - 0x2f0)))
  #define fStack_2ec (*(float *)(_frame + (0x340 - 0x2ec)))
  #define fStack_2e8 (*(float *)(_frame + (0x340 - 0x2e8)))
  #define fStack_2e4 (*(float *)(_frame + (0x340 - 0x2e4)))
  #define fStack_2e0 (*(float *)(_frame + (0x340 - 0x2e0)))
  #define local_180 (*(undefined4 (*)[96])(_frame + (0x340 - 0x180)))
  
  local_328 = 0;
  local_32c = 0;
  local_330 = 0;
  if (0 < count) {
    iVar4 = count;
    out = (float *)&local_300;
    do {
      Vec3_Sub(out,(float *)(((int)verts - (int)&local_300) + (int)out),
               (float *)((int)g_pRdCurrentCamera + 8));
      local_330 = (uint)((float)local_330 + *out);
      iVar4 = iVar4 + -1;
      local_32c = (uint)(out[1] + (float)local_32c);
      local_328 = (uint)(out[2] + (float)local_328);
      out = out + 3;
    } while (iVar4 != 0);
  }
  fVar1 = (float)count;
  vertexCount = rdClip_Face3_Pos_2(*(undefined4 *)((int)g_pRdCurrentCamera + 0x48),&local_300,count)
  ;
  if ((int)vertexCount < 3) {
    return (void *)0x0;
  }
  (**(code **)((int)g_pRdCurrentCamera + 0x50))(local_180,&local_300,vertexCount);
  puVar2 = (undefined4 *)rdCache_AllocMesh();
  *puVar2 = 0;
  puVar2[0x11] = 0;
  puVar2[0x12] = 0;
  puVar2[0xf] = 0;
  puVar2[1] = 1;
  puVar2[3] = 1;
  puVar2[2] = 3;
  puVar2[7] = vertexCount;
  puVar5 = local_180;
  puVar6 = (undefined4 *)puVar2[8];
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
  puVar2[0xf] = 0xffffffff;
  puVar2[0xe] = material;
  fStack_324 = fStack_2f4 - (float)local_300;
  fStack_320 = fStack_2f0 - (float)local_2fc;
  fStack_31c = fStack_2ec - (float)local_2f8;
  fStack_30c = fStack_2e8 - fStack_2f4;
  fStack_308 = fStack_2e4 - fStack_2f0;
  fStack_304 = fStack_2e0 - fStack_2ec;
  Vec3_Cross(&fStack_318,&fStack_324,&fStack_30c);
  puVar2[0x14] = (uint)(0.0 < fStack_310 * ((float)local_328 / fVar1) +
                              fStack_314 * ((float)local_32c / fVar1) +
                              fStack_318 * ((float)local_330 / fVar1));
  rdCache_AddMesh((void *)0x0,vertexCount,1);
  return puVar2;
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
#undef local_2f8
#undef local_2fc
#undef local_300
#undef local_328
#undef local_32c
#undef local_330

#endif


/* ---- 0x0040dcc0  rdPrimit3_DrawLine ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Clips a world-space segment against the camera frustum, projects it and draws it with
   rdCanvas_DrawLine */

undefined4
rdPrimit3_DrawLine(float *param_1,float *param_2,int *param_3,int *param_4,int *param_5,int *param_6
                  ,ushort param_7,uint param_8)

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
  
  Vec3_Sub(local_18,param_1,(float *)((int)g_pRdCurrentCamera + 8));
  Vec3_Sub(local_c,param_2,(float *)((int)g_pRdCurrentCamera + 8));
  iVar1 = rdClip_Line3(*(void **)((int)g_pRdCurrentCamera + 0x48),local_18,local_c,param_5,param_6);
  if (iVar1 != 0) {
    (**(code **)((int)g_pRdCurrentCamera + 0x4c))(local_30,local_18);
    (**(code **)((int)g_pRdCurrentCamera + 0x4c))(auStack_24,local_c);
    lVar2 = _ftol((double)CONCAT44(unaff_ESI,unaff_EBX));
    lVar3 = _ftol((double)CONCAT44(unaff_ESI,unaff_EBX));
    if (param_3 != (int *)0x0) {
      *param_3 = (int)lVar2;
      param_3[1] = (int)lVar3;
      param_3[2] = iStack_28;
    }
    lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EBX));
    lVar5 = _ftol((double)CONCAT44(unaff_ESI,unaff_EBX));
    if (param_4 != (int *)0x0) {
      *param_4 = (int)lVar4;
      param_4[1] = (int)lVar5;
      param_4[2] = iStack_1c;
    }
    rdCanvas_DrawLine(*(void **)((int)g_pRdCurrentCamera + 4),(int)lVar2,(int)lVar3,(int)lVar4,
                      (int)lVar5,param_7,param_8);
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
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Projects a world-space point with a radius and draws it as a 2D point */

void rdPrimit3_DrawPoint(float *param_1,float param_2,undefined4 param_3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  longlong lVar1;
  float fVar2;
  #define local_30 (*(uint *)(_frame + (0x40 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define afStack_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  Vec3_Sub((float *)&local_30,param_1,(float *)((int)g_pRdCurrentCamera + 8));
  local_24 = (uint)((float)local_30 + param_2);
  local_20 = local_2c;
  local_1c = local_28;
  if (0.0 < (float)local_2c) {
    (**(code **)((int)g_pRdCurrentCamera + 0x4c))(local_18,&local_30);
    (**(code **)((int)g_pRdCurrentCamera + 0x4c))(afStack_c,&local_24);
    fVar2 = afStack_c[0] - local_18[0];
    lVar1 = _ftol((double)CONCAT44(param_3,fVar2));
    lVar1 = _ftol((double)CONCAT44(fVar2,(int)lVar1));
    ((code *)rdCanvas_DrawPoint)(*(undefined4 *)((int)g_pRdCurrentCamera + 4),(int)lVar1);
  }
  return;
}
#undef afStack_c
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30

#endif


/* ---- 0x0040deb0  rdPrimit3_ClipFace ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Clips one face against the frustum; the switch selects the vertex attribute set from the
   geometry/lighting modes */

void rdPrimit3_ClipFace(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                       uint *param_5,undefined4 *param_6,float *param_7)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  
  puVar9 = param_6;
  puVar6 = param_5;
  switch(param_2) {
  case 0:
    uVar8 = 0;
    if (*param_5 != 0) {
      iVar10 = 0;
      do {
        puVar9 = (undefined4 *)(param_5[3] + *(int *)(param_5[1] + uVar8 * 4) * 0xc);
        puVar12 = (undefined4 *)(iVar10 + param_6[3]);
        uVar8 = uVar8 + 1;
        iVar10 = iVar10 + 0xc;
        *puVar12 = *puVar9;
        puVar12[1] = puVar9[1];
        puVar12[2] = puVar9[2];
      } while (uVar8 < *param_5);
    }
    break;
  case 1:
  case 2:
    uVar8 = 0;
    if (*param_5 != 0) {
      iVar10 = 0;
      do {
        puVar9 = (undefined4 *)(param_5[3] + *(int *)(param_5[1] + uVar8 * 4) * 0xc);
        puVar12 = (undefined4 *)(iVar10 + param_6[3]);
        uVar8 = uVar8 + 1;
        iVar10 = iVar10 + 0xc;
        *puVar12 = *puVar9;
        puVar12[1] = puVar9[1];
        puVar12[2] = puVar9[2];
      } while (uVar8 < *param_5);
    }
    if (*(int *)g_pRdCurrentCamera != 1) {
      uVar7 = rdClip_Face3_PosB(param_1,param_6[3],*param_5);
      *param_6 = uVar7;
      return;
    }
    uVar7 = ((code *)rdClip_Face3_Pos)();
    *param_6 = uVar7;
    return;
  case 3:
    switch(param_3) {
    case 0:
    case 1:
      uVar8 = 0;
      if (*param_5 != 0) {
        iVar10 = 0;
        do {
          puVar9 = (undefined4 *)(param_5[3] + *(int *)(param_5[1] + uVar8 * 4) * 0xc);
          puVar12 = (undefined4 *)(iVar10 + param_6[3]);
          uVar8 = uVar8 + 1;
          iVar10 = iVar10 + 0xc;
          *puVar12 = *puVar9;
          puVar12[1] = puVar9[1];
          puVar12[2] = puVar9[2];
        } while (uVar8 < *param_5);
      }
      break;
    case 2:
      uVar8 = 0;
      if (*param_5 != 0) {
        iVar10 = 0;
        do {
          puVar9 = (undefined4 *)(param_5[3] + *(int *)(param_5[1] + uVar8 * 4) * 0xc);
          puVar12 = (undefined4 *)(iVar10 + param_6[3]);
          uVar8 = uVar8 + 1;
          iVar10 = iVar10 + 0xc;
          *puVar12 = *puVar9;
          puVar12[1] = puVar9[1];
          puVar12[2] = puVar9[2];
        } while (uVar8 < *param_5);
      }
      break;
    case 3:
      if (param_5[6] == 0) {
        uVar8 = 0;
        if (*param_5 != 0) {
          iVar10 = 0;
          do {
            puVar9 = (undefined4 *)(param_5[3] + *(int *)(param_5[1] + uVar8 * 4) * 0xc);
            puVar12 = (undefined4 *)(iVar10 + param_6[3]);
            *puVar12 = *puVar9;
            puVar12[1] = puVar9[1];
            puVar12[2] = puVar9[2];
            iVar3 = *(int *)(param_5[1] + uVar8 * 4);
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
            uVar8 = uVar8 + 1;
            iVar10 = iVar10 + 0xc;
            *(float *)(param_6[5] + -4 + uVar8 * 4) = fVar2;
          } while (uVar8 < *param_5);
        }
      }
      else {
        uVar8 = 0;
        if (*param_5 != 0) {
          iVar10 = 0;
          do {
            puVar9 = (undefined4 *)(param_5[3] + *(int *)(param_5[1] + uVar8 * 4) * 0xc);
            puVar12 = (undefined4 *)(iVar10 + param_6[3]);
            *puVar12 = *puVar9;
            puVar12[1] = puVar9[1];
            puVar12[2] = puVar9[2];
            fVar2 = *(float *)(param_5[5] + *(int *)(param_5[1] + uVar8 * 4) * 4) +
                    *(float *)(param_5[6] + uVar8 * 4);
            if (fVar2 < 0.0) {
              fVar2 = 0.0;
            }
            else if (1.0 < fVar2) {
              fVar2 = 1.0;
            }
            uVar8 = uVar8 + 1;
            iVar10 = iVar10 + 0xc;
            *(float *)(param_6[5] + -4 + uVar8 * 4) = fVar2;
          } while (uVar8 < *param_5);
        }
      }
      if (*(int *)g_pRdCurrentCamera != 1) {
        uVar7 = rdClip_Face3_PosUv(param_1,param_6[3],param_6[5],*param_5);
        *param_6 = uVar7;
        return;
      }
      uVar7 = rdClip_Face3_PosUvLit(param_1,param_6[3],param_6[5],*param_5);
      *param_6 = uVar7;
      return;
    default:
      goto switchD_0040dec1_default;
    }
    break;
  case 4:
    if (-1 < param_3) {
      if (param_3 < 3) {
        uVar8 = 0;
        if (*param_5 != 0) {
          param_5 = (uint *)0x0;
          do {
            puVar9 = (undefined4 *)(puVar6[3] + *(int *)(puVar6[1] + uVar8 * 4) * 0xc);
            puVar12 = (undefined4 *)((int)param_5 + param_6[3]);
            *puVar12 = *puVar9;
            puVar12[1] = puVar9[1];
            puVar12[2] = puVar9[2];
            uVar5 = puVar6[4];
            iVar10 = *(int *)(puVar6[2] + uVar8 * 4);
            puVar9 = (undefined4 *)(uVar8 * 8 + param_6[4]);
            *puVar9 = *(undefined4 *)(uVar5 + iVar10 * 8);
            puVar9[1] = *(undefined4 *)(uVar5 + 4 + iVar10 * 8);
            pfVar1 = (float *)(param_6[4] + uVar8 * 8);
            *pfVar1 = *param_7 + *pfVar1;
            iVar10 = uVar8 * 8;
            iVar3 = uVar8 * 8;
            uVar8 = uVar8 + 1;
            param_5 = (uint *)((int)param_5 + 0xc);
            *(float *)(param_6[4] + 4 + iVar3) = *(float *)(param_6[4] + 4 + iVar10) + param_7[1];
          } while (uVar8 < *puVar6);
        }
        if (*(int *)g_pRdCurrentCamera == 1) {
          uVar7 = rdClip_Face3_PosUvLit_2(param_1,param_6[3],param_6[4],*puVar6);
          *param_6 = uVar7;
          return;
        }
        uVar7 = rdClip_Face3_PosUvFlags(param_1,param_6[3],param_6[4],*puVar6);
        *param_6 = uVar7;
      }
      else if (param_3 == 3) {
        if (param_5[6] == 0) {
          uVar8 = *param_5;
          param_5 = (uint *)0x0;
          if (uVar8 != 0) {
            param_6 = (undefined4 *)0x0;
            do {
              puVar12 = (undefined4 *)(puVar6[3] + *(int *)(puVar6[1] + (int)param_5 * 4) * 0xc);
              puVar11 = (undefined4 *)((int)param_6 + puVar9[3]);
              *puVar11 = *puVar12;
              puVar11[1] = puVar12[1];
              puVar11[2] = puVar12[2];
              iVar3 = puVar9[4];
              iVar10 = (int)param_5 * 8;
              iVar4 = *(int *)(puVar6[2] + (int)param_5 * 4);
              uVar8 = puVar6[4];
              *(undefined4 *)(iVar10 + iVar3) = *(undefined4 *)(uVar8 + iVar4 * 8);
              ((undefined4 *)(iVar10 + iVar3))[1] = *(undefined4 *)(uVar8 + 4 + iVar4 * 8);
              *(float *)(puVar9[4] + iVar10) = *param_7 + *(float *)(puVar9[4] + iVar10);
              *(float *)(iVar10 + 4 + puVar9[4]) = *(float *)(iVar10 + 4 + puVar9[4]) + param_7[1];
              iVar10 = *(int *)(puVar6[1] + (int)param_5 * 4);
              pfVar1 = (float *)(puVar6[5] + iVar10 * 4);
              if (*(float *)(puVar6[5] + iVar10 * 4) < 0.0) {
                fVar2 = 0.0;
              }
              else if (1.0 < *pfVar1) {
                fVar2 = 1.0;
              }
              else {
                fVar2 = *pfVar1;
              }
              param_6 = (undefined4 *)((int)param_6 + 0xc);
              *(float *)(puVar9[5] + (int)param_5 * 4) = fVar2;
              param_5 = (uint *)((int)param_5 + 1);
            } while (param_5 < *puVar6);
          }
        }
        else {
          uVar8 = *param_5;
          param_5 = (uint *)0x0;
          if (uVar8 != 0) {
            param_6 = (undefined4 *)0x0;
            do {
              puVar12 = (undefined4 *)(puVar6[3] + *(int *)(puVar6[1] + (int)param_5 * 4) * 0xc);
              puVar11 = (undefined4 *)((int)param_6 + puVar9[3]);
              *puVar11 = *puVar12;
              puVar11[1] = puVar12[1];
              puVar11[2] = puVar12[2];
              iVar3 = puVar9[4];
              iVar10 = (int)param_5 * 8;
              iVar4 = *(int *)(puVar6[2] + (int)param_5 * 4);
              uVar8 = puVar6[4];
              *(undefined4 *)(iVar10 + iVar3) = *(undefined4 *)(uVar8 + iVar4 * 8);
              ((undefined4 *)(iVar10 + iVar3))[1] = *(undefined4 *)(uVar8 + 4 + iVar4 * 8);
              *(float *)(puVar9[4] + iVar10) = *param_7 + *(float *)(puVar9[4] + iVar10);
              *(float *)(iVar10 + 4 + puVar9[4]) = *(float *)(iVar10 + 4 + puVar9[4]) + param_7[1];
              fVar2 = *(float *)(puVar6[5] + *(int *)(puVar6[1] + (int)param_5 * 4) * 4) +
                      *(float *)(puVar6[6] + (int)param_5 * 4);
              if (fVar2 < 0.0) {
                fVar2 = 0.0;
              }
              else if (1.0 < fVar2) {
                fVar2 = 1.0;
              }
              param_6 = (undefined4 *)((int)param_6 + 0xc);
              *(float *)(puVar9[5] + (int)param_5 * 4) = fVar2;
              param_5 = (uint *)((int)param_5 + 1);
            } while (param_5 < *puVar6);
          }
        }
        if (*(int *)g_pRdCurrentCamera != 1) {
          uVar7 = rdClip_Face3_PosUvLitFlags(param_1,puVar9[3],puVar9[4],puVar9[5],*puVar6);
          *puVar9 = uVar7;
          return;
        }
        uVar7 = rdClip_Face3_PosUvLitColor(param_1,puVar9[3],puVar9[4],puVar9[5],*puVar6);
        *puVar9 = uVar7;
        return;
      }
    }
  default:
switchD_0040dec1_default:
    return;
  }
  if (*(int *)g_pRdCurrentCamera != 1) {
    uVar7 = rdClip_Face3_PosB_2(param_1,param_6[3],*param_5);
    *param_6 = uVar7;
    return;
  }
  uVar7 = ((code *)rdClip_Face3_Pos_2)();
  *param_6 = uVar7;
  return;
}
#endif


/* ---- 0x0040e500  rdPrimit3_CopyFaceVerts ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Copies the face's vertex attributes (position, uv, intensity) into the cache pools without
   clipping */

void rdPrimit3_CopyFaceVerts
               (undefined4 param_1,int param_2,undefined4 param_3,uint *param_4,uint *param_5,
               float *param_6)

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
            param_4 = (uint *)((int)param_4 + 0xc);
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
              param_4 = (uint *)((int)param_4 + 0xc);
              *(float *)(puVar8[5] + (int)param_5 * 4) = fVar3;
              param_5 = (uint *)((int)param_5 + 1);
            } while (param_5 < *puVar7);
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
              param_4 = (uint *)((int)param_4 + 0xc);
              *(float *)(puVar8[5] + (int)param_5 * 4) = fVar3;
              param_5 = (uint *)((int)param_5 + 1);
            } while (param_5 < *puVar7);
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

