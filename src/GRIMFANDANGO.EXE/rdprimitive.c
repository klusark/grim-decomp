/* GRIMFANDANGO.EXE :: rdprimitive.c
 * functions 0x00471ee0 .. 0x00472bd0 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00471ee0  rdPolyline_Draw ---- */
/* WARNING: Variable defined which should be unmapped: local_b0 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl rdPolyline_Draw(int thing,float *b)

{
  unsigned char _frame[0xb0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float fVar3;
  uint local_b0;
  uint local_a0;
  float local_9c;
  #define local_94 (*(float (*)[2])(_frame + (0xb0 - 0x94)))
  #define local_88 (*(float (*)[3])(_frame + (0xb0 - 0x88)))
  #define local_7c (*(float *)(_frame + (0xb0 - 0x7c)))
  #define local_78 (*(float (*)[12])(_frame + (0xb0 - 0x78)))
  float local_48;
  float local_40;
  #define local_38 (*(float (*)[3])(_frame + (0xb0 - 0x38)))
  #define local_2c (*(undefined4 (*)[3])(_frame + (0xb0 - 0x2c)))
  #define local_20 (*(uint *)(_frame + (0xb0 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0xb0 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0xb0 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0xb0 - 0x14)))
  
  iVar1 = *(int *)(thing + 4);
  local_20 = (uint)&DAT_007f4e80;
  local_18 = 0;
  local_14 = 0;
  rdMatrix_Multiply34(local_78,g_pRdCamera_CurCamera->aView,b);
  local_38[0] = 0.0f;
  local_38[1] = *(float *)(iVar1 + 0x20);
  local_38[2] = 0.0f;
  rdMatrix_TransformPoint34(local_88 + 1,local_38,local_78);
  *(float *)&DAT_007f4e84 = local_88[2] - -0.001f;
  *(float *)&DAT_007f4e80 = local_88[1] - *(float *)(iVar1 + 0x28);
  *(float *)&DAT_007f4e88 = local_7c - *(float *)(iVar1 + 0x28);
  *(float *)&DAT_007f4e8c = local_88[1] + *(float *)(iVar1 + 0x28);
  *(float *)&DAT_007f4e94 = local_7c - *(float *)(iVar1 + 0x28);
  *(float *)&DAT_007f4e98 = local_88[1] + *(float *)(iVar1 + 0x28);
  *(float *)&DAT_007f4ea0 = local_7c + *(float *)(iVar1 + 0x28);
  *(float *)&DAT_007f4ea4 = local_88[1] - *(float *)(iVar1 + 0x28);
  *(float *)&DAT_007f4eac = local_7c + *(float *)(iVar1 + 0x28);
  local_1c = *(uint *)(iVar1 + 0xd4);
  *(float *)&DAT_007f4e90 = *(float *)&DAT_007f4e84;
  *(float *)&DAT_007f4e9c = *(float *)&DAT_007f4e84;
  *(float *)&DAT_007f4ea8 = *(float *)&DAT_007f4e84;
  rdPolyline_DrawFace(thing,iVar1 + 0x84,((unsigned)(uintptr_t)&DAT_007f4e80),local_2c);
  *(float *)&DAT_007f4e84 = local_78[10] - -0.001f;
  *(float *)&DAT_007f4e80 = local_78[9] - *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4e88 = local_78[0xb] - *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4e8c = local_78[9] + *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4e94 = local_78[0xb] - *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4e98 = local_78[9] + *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4ea0 = local_78[0xb] + *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4ea4 = local_78[9] - *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4eac = local_78[0xb] + *(float *)(iVar1 + 0x24);
  local_1c = *(uint *)(iVar1 + 0xd4);
  *(float *)&DAT_007f4e90 = *(float *)&DAT_007f4e84;
  *(float *)&DAT_007f4e9c = *(float *)&DAT_007f4e84;
  *(float *)&DAT_007f4ea8 = *(float *)&DAT_007f4e84;
  rdPolyline_DrawFace(thing,iVar1 + 0x84,((unsigned)(uintptr_t)&DAT_007f4e80),local_2c);
  local_94[1] = local_88[1] - local_78[9];
  fVar2 = local_7c - local_78[0xb];
  fVar3 = SQRT(fVar2 * fVar2 + local_94[1] * local_94[1]);
  local_9c = stdMath_ArcSin3(-local_94[1] / fVar3);
  if (fVar2 < 0.0f) {
    if (local_94[1] <= 0.0f) {
      local_9c = -(local_9c - -180.0f);
    }
    else {
      local_9c = 180.0f - local_9c;
    }
  }
  stdMath_SinCos(local_9c,local_88,local_94);
  *(float *)&DAT_007f4e84 = local_88[2];
  *(float *)&DAT_007f4e80 = (*(float *)(iVar1 + 0x28) * local_94[0] - local_88[0] * fVar3) + local_78[9];
  *(float *)&DAT_007f4e88 = *(float *)(iVar1 + 0x28) * local_88[0] + local_94[0] * fVar3 + local_78[0xb];
  *(float *)&DAT_007f4e8c = (-*(float *)(iVar1 + 0x28) * local_94[0] - local_88[0] * fVar3) + local_78[9];
  local_94[1] = 0.0f;
  *(float *)&DAT_007f4e94 = -*(float *)(iVar1 + 0x28) * local_88[0] + local_94[0] * fVar3 + local_78[0xb];
  *(float *)&DAT_007f4e98 = (-*(float *)(iVar1 + 0x24) * local_94[0] - 0.0f) + local_78[9];
  *(float *)&DAT_007f4ea0 = -*(float *)(iVar1 + 0x24) * local_88[0] + 0.0f + local_78[0xb];
  *(float *)&DAT_007f4e90 = local_88[2];
  *(float *)&DAT_007f4e9c = local_78[10];
  *(float *)&DAT_007f4ea4 = (*(float *)(iVar1 + 0x24) * local_94[0] - 0.0f) + local_78[9];
  *(float *)&DAT_007f4eac = *(float *)(iVar1 + 0x24) * local_88[0] + 0.0f + local_78[0xb];
  *(float *)&DAT_007f4ea8 = local_78[10];
  local_1c = *(uint *)(iVar1 + 0xd0);
  rdPolyline_DrawFace(thing,iVar1 + 0x38,((unsigned)(uintptr_t)&DAT_007f4e80),local_2c);
  return 1;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_2c
#undef local_38
#undef local_78
#undef local_7c
#undef local_88
#undef local_94


/* ---- 0x00472360  rdPolyline_DrawFace ---- */
/* Allocates a cache mesh for one polyline face, clips and adds it */

void __cdecl rdPolyline_DrawFace(int thing,int polyline,uint param_3,undefined4 *outUv)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  byte flags;
  ProcEntry *pPVar3;
  int iVar4;
  uint texMode;
  uint uVar5;
  uint geoMode;
  float *pfVar6;
  int iVar7;
  uint uVar8;
  bool bVar9;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  pPVar3 = rdCache_GetProcEntry();
  if (pPVar3 != (ProcEntry *)0x0) {
    local_20 = (uint)&DAT_007f4d00;
    local_4 = (uint)pPVar3->pVertices;
    local_1c = (uint)pPVar3->pTexVertices;
    local_18 = (uint)pPVar3->pIntensities;
    *outUv = *(undefined4 *)(polyline + 0x14);
    outUv[1] = *(undefined4 *)(polyline + 0x18);
    outUv[2] = *(undefined4 *)(polyline + 0x1c);
    uVar5 = *(uint *)(polyline + 8);
    uVar8 = g_nRdroid_curGeometryMode;
    if ((int)uVar5 <= g_nRdroid_curGeometryMode) {
      uVar8 = uVar5;
    }
    geoMode = *(uint *)(thing + 0x38);
    if (((int)uVar8 < (int)*(uint *)(thing + 0x38)) &&
       (geoMode = uVar5, g_nRdroid_curGeometryMode < (int)uVar5)) {
      geoMode = g_nRdroid_curGeometryMode;
    }
    pPVar3->nGeometryMode = geoMode;
    if ((((byte)g_dwRdroid_curRenderOptions & 2) == 0) ||
       (g_pRdCamera_CurCamera->flAmbientLight < 1.0f)) {
      iVar1 = *(int *)(polyline + 0xc);
      iVar7 = g_nRdroid_curLightingMode;
      if (iVar1 <= g_nRdroid_curLightingMode) {
        iVar7 = iVar1;
      }
      iVar4 = *(int *)(thing + 0x3c);
      if ((iVar7 < iVar4) && (iVar4 = iVar1, g_nRdroid_curLightingMode < iVar1)) {
        iVar4 = g_nRdroid_curLightingMode;
      }
      pPVar3->nLightingMode = iVar4;
    }
    else {
      pPVar3->nLightingMode = 0;
    }
    uVar5 = *(uint *)(polyline + 0x10);
    uVar8 = g_nRdroid_curTextureMode;
    if ((int)uVar5 <= g_nRdroid_curTextureMode) {
      uVar8 = uVar5;
    }
    texMode = *(uint *)(thing + 0x40);
    if (((int)uVar8 < (int)*(uint *)(thing + 0x40)) &&
       (texMode = uVar5, g_nRdroid_curTextureMode < (int)uVar5)) {
      texMode = g_nRdroid_curTextureMode;
    }
    pPVar3->nTextureMode = texMode;
    rdPrimit3_ClipFace((uint)g_pRdCamera_CurCamera->pFrustum,geoMode,pPVar3->nLightingMode,texMode,
                       outUv,&local_2c,(float *)(polyline + 0x28));
    if (2 < local_2c) {
      (*g_pRdCamera_CurCamera->pfnProjectLst)(local_4,local_20,local_2c);
      if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
        pPVar3->flAlpha = 0.0f;
      }
      else {
        pPVar3->flAlpha = g_pRdCamera_CurCamera->flAmbientLight;
      }
      iVar1 = pPVar3->nLightingMode;
      if (iVar1 != 0) {
        bVar9 = g_dwRdColormap_pIdentityMap != g_dwRdColormap_pCurMap;
        if (pPVar3->flAlpha < 1.0f) {
          if (iVar1 == 2) {
            if ((pPVar3->flLightIndex < 1.0f) || (bVar9)) {
              if (pPVar3->flLightIndex <= 0.0f) {
                pPVar3->nLightingMode = 1;
              }
            }
            else {
              pPVar3->nLightingMode = 0;
            }
          }
          else if (iVar1 == 3) {
            pfVar6 = pPVar3->pIntensities;
            fVar2 = *pfVar6;
            uVar5 = 1;
            if (1 < local_2c) {
              do {
                pfVar6 = pfVar6 + 1;
                if (*pfVar6 != fVar2) break;
                uVar5 = uVar5 + 1;
              } while (uVar5 < local_2c);
            }
            if (uVar5 == local_2c) {
              if (fVar2 == 1.0f) {
                if (bVar9) {
                  pPVar3->nLightingMode = 2;
                  pPVar3->flLightIndex = 1.0f;
                }
                else {
                  pPVar3->nLightingMode = 0;
                }
              }
              else if (fVar2 == 0.0f) {
                pPVar3->nLightingMode = 1;
                pPVar3->flLightIndex = 0.0f;
              }
              else {
                pPVar3->nLightingMode = 2;
                pPVar3->flLightIndex = fVar2;
              }
            }
          }
        }
        else if (bVar9) {
          pPVar3->nLightingMode = 2;
          pPVar3->flLightIndex = 1.0f;
        }
        else {
          pPVar3->nLightingMode = 0;
        }
      }
      flags = 1;
      if (3 < pPVar3->nGeometryMode) {
        flags = 3;
      }
      if (2 < pPVar3->nLightingMode) {
        flags = flags | 4;
      }
      pPVar3->nCel = *(int *)(thing + 0x30);
      pPVar3->nBackFacing = 0;
      pPVar3->dwFlags = *(uint *)(polyline + 4);
      pPVar3->flLight = *(float *)(polyline + 0x30);
      pPVar3->pMaterial = *(rdMaterial **)(polyline + 0x20);
      rdCache_AddProcFace((void *)0x0,local_2c,flags);
    }
  }
  return;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_2c
#undef local_4


/* ---- 0x00472640  rdSprite_DrawThing ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Billboard: builds a camera-facing matrix for the thing position and draws the sprite */

int __cdecl rdSprite_DrawThing(rdThing *thing,void *sprite)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  rdModel3 *prVar1;
  uint uVar2;
  ProcEntry *pPVar3;
  uint *puVar4;
  uint local_40;
  #define local_3c (*(float (*)[3])(_frame + (0x50 - 0x3c)))
  #define local_30 (*(float (*)[12])(_frame + (0x50 - 0x30)))
  
  prVar1 = thing->pModel;
  rdMatrix_TransformPoint34(local_3c,(float *)((int)sprite + 0x24),g_pRdCamera_CurCamera->aView);
  if ((g_bRdroid_curCullFlags & 2) == 0) {
    uVar2 = thing->nFrustumCull;
  }
  else {
    uVar2 = rdClip_SphereInFrustrum
                      (&g_pRdCamera_CurCamera->pFrustum->nClipFar,local_3c,
                       (float)prVar1->aGeosets[3].dwMeshes);
  }
  if (uVar2 == 2) {
    return 0;
  }
  rdMatrix_Multiply34(local_30,g_pRdCamera_CurCamera->aView,sprite);
  if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
    sprite = (void *)0x0;
  }
  else {
    sprite = PUN(void *,(float)g_pRdCamera_CurCamera->flAmbientLight);
  }
  if (PUN(float,sprite) < 1.0f) {
    if (0.0f < PUN(float,sprite)) {
      thing = *(rdThing **)&prVar1->field_0x20;
    }
    else {
      thing = (rdThing *)0x1;
    }
  }
  else {
    thing = (rdThing *)0x0;
  }
  if ((int)*(rdThing **)&prVar1->field_0x20 <= (int)thing) {
    thing = *(rdThing **)&prVar1->field_0x20;
  }
  rdMatrix_TransformPointLst34
            (local_30,(float *)prVar1->aGeosets[0].pMeshes,(float *)&UINT_007f5180,
             prVar1->aGeosets[0].dwMeshes);
  local_40 = 0;
  if (prVar1->aGeosets[0].dwMeshes != 0) {
    puVar4 = &UINT_007f5184;
    do {
      pPVar3 = rdCache_GetProcEntry();
      if (pPVar3 == (ProcEntry *)0x0) {
        return 0;
      }
      *(float *)&DAT_007f5000 = PUN(float,puVar4[-1]) - (float)prVar1->aGeosets[2].dwMeshes;
      _DAT_007f5004 = PUN(float,*puVar4);
      *(float *)&DAT_007f5008 = PUN(float,puVar4[1]) - (float)prVar1->aGeosets[2].dwMeshes;
      FLOAT_007f5010 = PUN(float,*puVar4);
      *(float *)&DAT_007f500c = PUN(float,puVar4[-1]) + (float)prVar1->aGeosets[2].dwMeshes;
      FLOAT_007f501c = PUN(float,*puVar4);
      *(float *)&DAT_007f5014 = PUN(float,puVar4[1]) - (float)prVar1->aGeosets[2].dwMeshes;
      FLOAT_007f5028 = PUN(float,*puVar4);
      *(float *)&DAT_007f5018 = PUN(float,puVar4[-1]) + (float)prVar1->aGeosets[2].dwMeshes;
      *(float *)&DAT_007f5020 = PUN(float,puVar4[1]) + (float)prVar1->aGeosets[2].dwMeshes;
      *(float *)&DAT_007f5024 = PUN(float,puVar4[-1]) - (float)prVar1->aGeosets[2].dwMeshes;
      *(float *)&DAT_007f502c = PUN(float,puVar4[1]) + (float)prVar1->aGeosets[2].dwMeshes;
      uVar2 = rdClip_Face3S(&g_pRdCamera_CurCamera->pFrustum->nClipFar,(float *)&DAT_007f5000,4);
      if (2 < uVar2) {
        (*g_pRdCamera_CurCamera->pfnProjectLst)(pPVar3->pVertices,&DAT_007f5000,uVar2);
        pPVar3->nLightingMode = (int)thing;
        pPVar3->flAlpha = PUN(float,sprite);
        pPVar3->nGeometryMode = 3;
        pPVar3->dwFlags = 0;
        pPVar3->pMaterial = (rdMaterial *)prVar1->aGeosets[2].pMeshes;
        pPVar3->nCel = *(int *)(prVar1->aGeosets[1].dwMeshes + local_40 * 4);
        pPVar3->nBackFacing = 0;
        rdCache_AddProcFace((void *)0x0,uVar2,1);
      }
      local_40 = local_40 + 1;
      puVar4 = puVar4 + 3;
    } while (local_40 < prVar1->aGeosets[0].dwMeshes);
  }
  return 1;
}
#undef local_30
#undef local_3c


/* ---- 0x004728a0  rdSprite_New ---- */
/* Allocates a 0xb8-byte polyline (RDroid Primitiv*.c) and initialises it Original name rdSprite_New
   (the remaster's GrimFandango (Linux): the only unmatched caller of rdPolyline_Init; 2 matched
   neighbours agree, 0 disagree); was rdPolyline_New. */

int __cdecl
rdSprite_New(uint type,uint name,uint material,uint width,uint height,uint geoMode,uint lightMode,
            uint texMode,uint extraLight,uint offset)

{
  int sprite;
  
  sprite = (*g_pRdroid_HS->pAlloc)
                     (0xb8,s_C__grimjedi_Libs_RDroid_Primitiv_004dde64,DAT_004dde5c + 4);
  if (sprite == 0) {
    return 0;
  }
  rdSprite_NewEntry(sprite,name,type,(char *)material,width,height,geoMode,lightMode,texMode,
                    extraLight,(undefined4 *)offset);
  return sprite;
}

/* ---- 0x00472910  rdSprite_NewEntry ---- */
/* Copies the 31-char name and builds the vertex ring for the given radius/segment counts Original
   name rdSprite_NewEntry (the remaster's GrimFandango (Linux): the only unmatched caller of
   rdMaterial_Load; 1 matched neighbours agree, 0 disagree); was rdPolyline_Init. */

uint __cdecl
rdSprite_NewEntry(int sprite,int name,uint type,char *material,uint width,uint height,uint geoMode,
                 uint lightMode,uint texMode,uint extraLight,undefined4 *offset)

{
  float fVar1;
  float fVar2;
  rdMaterial *prVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  if (name != 0) {
    strncpy((uint *)sprite,(uint *)name,0x1f);
    *(undefined1 *)(sprite + 0x1f) = 0;
  }
  *(uint *)(sprite + 0x4c) = width;
  *(uint *)(sprite + 0x20) = type;
  *(uint *)(sprite + 0x50) = height;
  *(undefined4 *)(sprite + 0xac) = *offset;
  *(undefined4 *)(sprite + 0xb0) = offset[1];
  *(undefined4 *)(sprite + 0xb4) = offset[2];
  *(uint *)(sprite + 0x68) = lightMode;
  *(uint *)(sprite + 100) = geoMode;
  *(undefined4 *)(sprite + 0x60) = 1;
  *(uint *)(sprite + 0x6c) = texMode;
  *(uint *)(sprite + 0x8c) = extraLight;
  prVar3 = rdMaterial_Load(material,0,0);
  *(rdMaterial **)(sprite + 0x7c) = prVar3;
  if (prVar3 == (rdMaterial *)0x0) {
    return 0;
  }
  *(undefined4 *)(sprite + 0x70) = 4;
  iVar4 = (*g_pRdroid_HS->pAlloc)
                    (0x10,s_C__grimjedi_Libs_RDroid_Primitiv_004dde64,DAT_004dde60 + 0x2a);
  *(int *)(sprite + 0x74) = iVar4;
  if (iVar4 != 0) {
    if (*(int *)(sprite + 100) < 4) {
      uVar5 = 0;
      if (*(int *)(sprite + 0x70) != 0) {
        do {
          *(uint *)(*(int *)(sprite + 0x74) + uVar5 * 4) = uVar5;
          uVar5 = uVar5 + 1;
        } while (uVar5 < *(uint *)(sprite + 0x70));
      }
LAB_00472af2:
      *(float *)(sprite + 0x54) = *(float *)(sprite + 0x4c) * 0.5f;
      *(float *)(sprite + 0x58) = *(float *)(sprite + 0x50) * 0.5f;
      *(undefined4 *)(sprite + 0x84) = 0;
      *(undefined4 *)(sprite + 0x88) = 0;
      *(float *)(sprite + 0x24) =
           SQRT(*(float *)(sprite + 0x58) * *(float *)(sprite + 0x58) +
                *(float *)(sprite + 0x54) * *(float *)(sprite + 0x54));
      return 1;
    }
    iVar4 = (*g_pRdroid_HS->pAlloc)
                      (*(int *)(sprite + 0x70) << 2,s_C__grimjedi_Libs_RDroid_Primitiv_004dde64,
                       DAT_004dde60 + 0x31);
    *(int *)(sprite + 0x78) = iVar4;
    if (iVar4 != 0) {
      uVar5 = 0;
      if (*(int *)(sprite + 0x70) != 0) {
        do {
          *(uint *)(*(int *)(sprite + 0x74) + uVar5 * 4) = uVar5;
          *(uint *)(*(int *)(sprite + 0x78) + uVar5 * 4) = uVar5;
          uVar5 = uVar5 + 1;
        } while (uVar5 < *(uint *)(sprite + 0x70));
      }
      puVar6 = (undefined4 *)
               (*g_pRdroid_HS->pAlloc)
                         (*(int *)(sprite + 0x70) << 3,s_C__grimjedi_Libs_RDroid_Primitiv_004dde64,
                          DAT_004dde60 + 0x3d);
      *(undefined4 **)(sprite + 0xa8) = puVar6;
      if (puVar6 != (undefined4 *)0x0) {
        iVar4 = *(int *)(*(int *)(*(int *)(*(int *)(sprite + 0x7c) + 0x68) + 0x1c) + 0x1c);
        uVar5 = *(uint *)(iVar4 + 0x10);
        fVar1 = (float)*(uint *)(iVar4 + 0xc) - 0.5f;
        *puVar6 = 0x3f000000;
        fVar2 = (float)uVar5 - 0.5f;
        *(float *)(*(int *)(sprite + 0xa8) + 4) = fVar2;
        *(float *)(*(int *)(sprite + 0xa8) + 8) = fVar1;
        *(float *)(*(int *)(sprite + 0xa8) + 0xc) = fVar2;
        *(float *)(*(int *)(sprite + 0xa8) + 0x10) = fVar1;
        *(undefined4 *)(*(int *)(sprite + 0xa8) + 0x14) = 0x3f000000;
        *(undefined4 *)(*(int *)(sprite + 0xa8) + 0x18) = 0x3f000000;
        *(undefined4 *)(*(int *)(sprite + 0xa8) + 0x1c) = 0x3f000000;
        goto LAB_00472af2;
      }
    }
  }
  return 0;
}

/* ---- 0x00472b50  rdSprite_Free ---- */
void __cdecl rdSprite_Free(int sprite)

{
  if (sprite != 0) {
    rdSprite_FreeEntry(sprite);
    (*g_pRdroid_HS->pFree)(sprite);
  }
  return;
}

/* ---- 0x00472b70  rdSprite_FreeEntry ---- */
/* Original name rdSprite_FreeEntry (the remaster's GrimFandango (Linux): same body (frees the +0xa8
   and +0x74 arrays through rdroid_pHS)); was rdSprite_FreeContents. */

void __cdecl rdSprite_FreeEntry(int sprite)

{
  if (*(int *)(sprite + 0xa8) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(sprite + 0xa8));
    *(undefined4 *)(sprite + 0xa8) = 0;
  }
  if (*(int *)(sprite + 0x74) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(sprite + 0x74));
    *(undefined4 *)(sprite + 0x74) = 0;
  }
  if (*(int *)(sprite + 0x78) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(sprite + 0x78));
    *(undefined4 *)(sprite + 0x78) = 0;
  }
  return;
}

/* ---- 0x00472bd0  rdSprite_Draw ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Frustum tests the sprite, builds the quad in the cache and clips it */

uint __cdecl rdSprite_Draw(int thing,float *matrix)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  uint uVar4;
  ProcEntry *pPVar5;
  int iVar6;
  uint texMode;
  byte flags;
  uint geoMode;
  float *pfVar7;
  int iVar8;
  uint uVar9;
  bool bVar10;
  uint local_7c;
  #define local_78 (*(float (*)[2])(_frame + (0x90 - 0x78)))
  #define local_70 (*(float (*)[3])(_frame + (0x90 - 0x70)))
  #define local_64 (*(float (*)[3])(_frame + (0x90 - 0x64)))
  rdProcFace face;
  uint local_30;
  rdProcVerts verts;
  
  iVar1 = *(int *)(thing + 4);
  rdMatrix_TransformPoint34(local_64,matrix + 9,g_pRdCamera_CurCamera->aView);
  rdMatrix_TransformVector34(local_70,(float *)(iVar1 + 0xac),matrix);
  rdMatrix_TransformVector34Acc(local_70,g_pRdCamera_CurCamera->aView);
  if (0.0f <= local_70[0]) {
    local_78[0] = -*(float *)(iVar1 + 0x54);
  }
  else {
    local_78[0] = *(float *)(iVar1 + 0x54);
  }
  if ((g_bRdroid_curCullFlags & 2) == 0) {
    uVar4 = *(uint *)(thing + 0x44);
  }
  else {
    uVar4 = rdClip_SphereInFrustrum
                      (&g_pRdCamera_CurCamera->pFrustum->nClipFar,local_64,*(float *)(iVar1 + 0x24))
    ;
  }
  if ((uVar4 != 2) && (pPVar5 = rdCache_GetProcEntry(), pPVar5 != (ProcEntry *)0x0)) {
    *(float *)&DAT_007f5f0c = local_70[1] + local_64[1];
    *(float *)&DAT_007f5f10 = local_70[2] + local_64[2];
    *(float *)&DAT_007f5f08 = local_64[0] + (local_70[0] - local_78[0]);
    *(float *)&DAT_007f5f14 = local_64[0] + local_78[0] + local_70[0];
    *(float *)&DAT_007f5f20 = local_64[0] + local_78[0] + local_70[0];
    *(float *)&DAT_007f5f28 = local_64[2] + *(float *)(iVar1 + 0x58) + *(float *)(iVar1 + 0x58) + local_70[2];
    *(float *)&DAT_007f5f2c = local_64[0] + (local_70[0] - local_78[0]);
    *(float *)&DAT_007f5f34 = local_64[2] + *(float *)(iVar1 + 0x58) + *(float *)(iVar1 + 0x58) + local_70[2];
    verts.dwVertices = *(uint *)(iVar1 + 0x70);
    verts.pPosIdx = *(int **)(iVar1 + 0x74);
    verts.pUvIdx = *(int **)(iVar1 + 0x78);
    verts.pVertices = (float *)&DAT_007f5f08;
    verts.pUvs = *(float **)(iVar1 + 0xa8);
    verts.pLights = (float *)0x0;
    verts.pIntensities = (float *)0x0;
    face.pVertices = (float *)&g_aRdSprite_FaceVerts;
    pfVar7 = pPVar5->pVertices;
    face.pTexVertices = pPVar5->pTexVertices;
    face.pIntensities = pPVar5->pIntensities;
    uVar4 = *(uint *)(iVar1 + 100);
    uVar9 = g_nRdroid_curGeometryMode;
    if ((int)uVar4 <= g_nRdroid_curGeometryMode) {
      uVar9 = uVar4;
    }
    geoMode = *(uint *)(thing + 0x38);
    if (((int)uVar9 < (int)*(uint *)(thing + 0x38)) &&
       (geoMode = uVar4, g_nRdroid_curGeometryMode < (int)uVar4)) {
      geoMode = g_nRdroid_curGeometryMode;
    }
    *(float *)&DAT_007f5f18 = *(float *)&DAT_007f5f0c;
    *(float *)&DAT_007f5f1c = *(float *)&DAT_007f5f10;
    *(float *)&DAT_007f5f24 = *(float *)&DAT_007f5f0c;
    *(float *)&DAT_007f5f30 = *(float *)&DAT_007f5f0c;
    pPVar5->nGeometryMode = geoMode;
    if ((((byte)g_dwRdroid_curRenderOptions & 2) == 0) ||
       (g_pRdCamera_CurCamera->flAmbientLight < 1.0f)) {
      iVar2 = *(int *)(iVar1 + 0x68);
      iVar8 = g_nRdroid_curLightingMode;
      if (iVar2 <= g_nRdroid_curLightingMode) {
        iVar8 = iVar2;
      }
      iVar6 = *(int *)(thing + 0x3c);
      if ((iVar8 < iVar6) && (iVar6 = iVar2, g_nRdroid_curLightingMode < iVar2)) {
        iVar6 = g_nRdroid_curLightingMode;
      }
      pPVar5->nLightingMode = iVar6;
    }
    else {
      pPVar5->nLightingMode = 0;
    }
    uVar4 = *(uint *)(iVar1 + 0x6c);
    uVar9 = g_nRdroid_curTextureMode;
    if ((int)uVar4 <= g_nRdroid_curTextureMode) {
      uVar9 = uVar4;
    }
    texMode = *(uint *)(thing + 0x40);
    if (((int)uVar9 < (int)*(uint *)(thing + 0x40)) &&
       (texMode = uVar4, g_nRdroid_curTextureMode < (int)uVar4)) {
      texMode = g_nRdroid_curTextureMode;
    }
    pPVar5->nTextureMode = texMode;
    rdPrimit3_ClipFace((uint)g_pRdCamera_CurCamera->pFrustum,geoMode,pPVar5->nLightingMode,texMode,
                       &verts.dwVertices,&face.dwVertices,(float *)(iVar1 + 0x84));
    if (2 < face.dwVertices) {
      (*g_pRdCamera_CurCamera->pfnProjectLst)(pfVar7,face.pVertices,face.dwVertices);
      if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
        pPVar5->flAlpha = 0.0f;
      }
      else {
        pPVar5->flAlpha = g_pRdCamera_CurCamera->flAmbientLight;
      }
      iVar2 = pPVar5->nLightingMode;
      if (iVar2 != 0) {
        bVar10 = g_dwRdColormap_pIdentityMap == g_dwRdColormap_pCurMap;
        if (pPVar5->flAlpha < 1.0f) {
          if (iVar2 == 2) {
            if ((pPVar5->flLightIndex < 1.0f) || (!bVar10)) {
              if (pPVar5->flLightIndex <= 0.0f) {
                pPVar5->nLightingMode = 1;
              }
            }
            else {
              pPVar5->nLightingMode = 0;
            }
          }
          else if (iVar2 == 3) {
            pfVar7 = pPVar5->pIntensities;
            fVar3 = *pfVar7;
            uVar4 = 1;
            if (1 < face.dwVertices) {
              do {
                pfVar7 = pfVar7 + 1;
                if (*pfVar7 != fVar3) break;
                uVar4 = uVar4 + 1;
              } while (uVar4 < face.dwVertices);
            }
            if (uVar4 == face.dwVertices) {
              if (fVar3 == 1.0f) {
                if (bVar10) {
                  pPVar5->nLightingMode = 0;
                }
                else {
                  pPVar5->nLightingMode = 2;
                  pPVar5->flLightIndex = 1.0f;
                }
              }
              else if (fVar3 == 0.0f) {
                pPVar5->nLightingMode = 1;
                pPVar5->flLightIndex = 0.0f;
              }
              else {
                pPVar5->nLightingMode = 2;
                pPVar5->flLightIndex = fVar3;
              }
            }
          }
        }
        else {
          pPVar5->nLightingMode = (-(uint)bVar10 & 0xfffffffe) + 2;
        }
      }
      flags = 1;
      if (3 < pPVar5->nGeometryMode) {
        flags = 3;
      }
      if (2 < pPVar5->nLightingMode) {
        flags = flags | 4;
      }
      pPVar5->nCel = *(int *)(thing + 0x30);
      pPVar5->nBackFacing = (uint)(local_78[0] < 0.0f);
      pPVar5->dwFlags = *(uint *)(iVar1 + 0x60);
      pPVar5->flLight = *(float *)(iVar1 + 0x8c);
      pPVar5->pMaterial = *(rdMaterial **)(iVar1 + 0x7c);
      rdCache_AddProcFace((void *)0x0,face.dwVertices,flags);
      return 1;
    }
  }
  return 0;
}
#undef local_64
#undef local_70
#undef local_78

