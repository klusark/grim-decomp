/* GRIMFANDANGO.EXE :: rdlight.c
 * functions 0x00451460 .. 0x00451800 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00451460  rdLight_NewEntry ---- */
/* Defaults: type 2, on, white (0xffffff), intensity 1.0 Original name rdLight_NewEntry (the
   remaster's GrimFandango (Linux): aligned call in sputRoom_ParseLights); was rdLight_Init. */

uint __cdecl rdLight_NewEntry(rdLight *light)

{
  light->nType = 2;
  light->nActive = 1;
  light->aDirection[0] = 0.0f;
  light->aDirection[1] = 0.0f;
  light->aDirection[2] = 0.0f;
  light->flIntensity = 1.0f;
  light->dwColor = 0xffffff;
  light->flInnerAngle = 0.0f;
  light->flCosInner = 0.0f;
  light->flOuterAngle = 0.0f;
  light->flCosOuter = 0.0f;
  return 1;
}

/* ---- 0x004514a0  rdLight_SetAngles ---- */
/* inner (umbra, degrees) -> +0x20, cos +0x24; outer (penumbra) -> +0x28, cos +0x2c; +0x30 =
   1/(cosInner - cosOuter) only when positive, else left as is (0 from the set load memset => hard
   edge at the penumbra). Called by Set_LoadResources with the raw set values (half angles, not
   halved). */

void __cdecl rdLight_SetAngles(rdLight *light,float inner,float outer)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  light->flInnerAngle = inner;
  light->flOuterAngle = outer;
  stdMath_SinCos(inner,(float *)&local_4,&light->flCosInner);
  stdMath_SinCos(outer,(float *)&local_4,&light->flCosOuter);
  fVar1 = light->flCosInner - light->flCosOuter;
  if (0.0f < fVar1) {
    light->flConeScale = 1.0f / fVar1;
  }
  return;
}
#undef local_4


/* ---- 0x00451510  rdLight_CalcVertexIntensities ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Accumulates the intensity of every light (type, radius, direction) at each vertex position */

float __cdecl
rdLight_CalcVertexIntensities
          (int *lights,float *lpos,int ldir,uint nlights,int *normals,uint verts,float *base,
          float *out,uint nverts,float k)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  float fVar8;
  uint local_2c;
  #define local_28 (*(float (*)[3])(_frame + (0x40 - 0x28)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  uint local_18;
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  local_28[0] = 0.0f;
  if (nverts != 0) {
    local_2c = verts;
    iVar5 = verts - (int)normals;
    iVar4 = (int)base - (int)out;
    pfVar7 = (float *)(normals + 2);
    local_1c = nverts;
    do {
      local_28[1] = 0.0f;
      *out = *(float *)(iVar4 + (int)out);
      if (nlights != 0) {
        normals = lights;
        base = lpos;
        pfVar6 = (float *)(ldir + 8);
        do {
          iVar2 = *normals;
          if (*(int *)(iVar2 + 4) < 2) {
            fVar3 = 0.0f;
          }
          else {
            local_c[0] = *base - *(float *)local_2c;
            local_c[1] = *(float *)(((int)lpos - ldir) + -4 + (int)pfVar6) -
                         *(float *)(iVar5 + -4 + (int)pfVar7);
            local_c[2] = *(float *)(((int)lpos - ldir) + (int)pfVar6) -
                         *(float *)(iVar5 + (int)pfVar7);
            fVar3 = local_c[2] * local_c[2] + local_c[1] * local_c[1] + local_c[0] * local_c[0];
          }
          if (fVar3 < *(float *)(iVar2 + 0x34) * *(float *)(iVar2 + 0x34)) {
            switch(*(undefined4 *)(iVar2 + 4)) {
            case 0:
            case 1:
              fVar3 = *pfVar6 * *pfVar7 + pfVar6[-1] * pfVar7[-1] + pfVar6[-2] * pfVar7[-2];
              if (0.0f < fVar3) {
                fVar3 = *(float *)(iVar2 + 0x18) * fVar3;
LAB_0045173f:
                *out = fVar3 + *out;
              }
              break;
            case 2:
              fVar8 = rdVector_Normalize3Acc(local_c);
              fVar3 = *pfVar7 * local_c[2] + pfVar7[-1] * local_c[1] + pfVar7[-2] * local_c[0];
              if (0.0f < fVar3) {
                fVar3 = (*(float *)(iVar2 + 0x18) - fVar8 * k) * fVar3;
                goto LAB_0045173f;
              }
              break;
            case 3:
              fVar8 = rdVector_Normalize3Acc(local_c);
              fVar3 = *pfVar6 * local_c[2] + pfVar6[-2] * local_c[0] + pfVar6[-1] * local_c[1];
              if (*(float *)(iVar2 + 0x2c) < fVar3) {
                fVar1 = *(float *)(iVar2 + 0x18);
                if (fVar3 < *(float *)(iVar2 + 0x24)) {
                  fVar1 = (1.0f - (*(float *)(iVar2 + 0x24) - fVar3) * *(float *)(iVar2 + 0x30)) *
                          fVar1;
                }
                fVar3 = (fVar1 - fVar8 * k) *
                        (*pfVar7 * *pfVar6 + pfVar6[-2] * pfVar7[-2] + pfVar6[-1] * pfVar7[-1]);
                goto LAB_0045173f;
              }
            }
          }
          if (1.0f < *out) {
            *out = 1.0f;
          }
          if (*out == 1.0f) break;
          normals = normals + 1;
          local_28[1] = (float)(PUN(int,(float)local_28[1]) + 1);
          base = base + 3;
          pfVar6 = pfVar6 + 3;
        } while (PUN(uint,(float)local_28[1]) < nlights);
      }
      pfVar7 = pfVar7 + 3;
      local_28[0] = local_28[0] + *out;
      local_2c = local_2c + 0xc;
      out = out + 1;
      local_1c = local_1c - 1;
    } while (local_1c != 0);
  }
  return local_28[0] / (float)nverts;
}
#undef local_1c
#undef local_28
#undef local_c

#endif


/* ---- 0x00451800  rdLight_CalcFaceIntensity ---- */
/* Flat per-face light level (face light mode 2), called from rdModel_AddMeshToCache. Sums (I -
   k*dist) * dot(faceNormal, L) for every enabled light within cull range (+0x34) of the face's
   FIRST vertex, treating every light as omni (uses the light position even for direct/spot). Normal
   is negated for back faces. Starts at 0, returns as soon as the sum >= 1. */

float __cdecl
rdLight_CalcFaceIntensity
          (int *lights,int verts,uint numLights,uint numMeshLights,int face,float *normal,
          int vertices,float scale)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  float fVar3;
  uint uVar4;
  float *pfVar5;
  float fVar6;
  float local_10;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
  uVar4 = 0;
  local_10 = 0.0f;
  if (numMeshLights != 0) {
    pfVar5 = (float *)(verts + 8);
    do {
      iVar1 = *lights;
      if (*(int *)(iVar1 + 8) != 0) {
        piVar2 = *(int **)(face + 0x18);
        local_c[0] = pfVar5[-2] - *(float *)(vertices + *piVar2 * 0xc);
        local_c[1] = pfVar5[-1] - *(float *)(vertices + 4 + *piVar2 * 0xc);
        local_c[2] = *pfVar5 - *(float *)(vertices + 8 + *piVar2 * 0xc);
        if (local_c[2] * local_c[2] + local_c[1] * local_c[1] + local_c[0] * local_c[0] <
            *(float *)(iVar1 + 0x34) * *(float *)(iVar1 + 0x34)) {
          fVar6 = rdVector_Normalize3Acc(local_c);
          fVar3 = local_c[0] * *normal + normal[1] * local_c[1] + normal[2] * local_c[2];
          if (0.0f < fVar3) {
            local_10 = (*(float *)(iVar1 + 0x18) - fVar6 * scale) * fVar3 + local_10;
          }
        }
      }
      if (1.0f <= local_10) {
        return local_10;
      }
      uVar4 = uVar4 + 1;
      lights = lights + 1;
      pfVar5 = pfVar5 + 3;
    } while (uVar4 < numMeshLights);
  }
  return local_10;
}
#undef local_c

