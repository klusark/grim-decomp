/* GRIMFANDANGO.EXE :: rdcache.c
 * functions 0x00406650 .. 0x00408af0 (14 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00406650  rdCache_AdvanceFrame ---- */
/* Original name rdCache_AdvanceFrame (the remaster's GrimFandango (Linux): the cache call of
   rdAdvanceFrame, same body (hardware: start the scene)); was rdCache_BeginScene3D. */

void __cdecl rdCache_AdvanceFrame(void)

{
  if (0 < g_nRdroid_curAcceleration) {
    std3D_StartScene();
    return;
  }
  return;
}

/* ---- 0x00406660  rdCache_FinishFrame ---- */
/* Original name rdCache_FinishFrame (the remaster's GrimFandango (Linux): same body (if
   rdroid_curAcceleration > 0: std3D_EndScene); called by rdFinishFrame in both builds); was
   rdCache_EndScene3D. */

void __cdecl rdCache_FinishFrame(void)

{
  if (0 < g_nRdroid_curAcceleration) {
    std3D_EndScene();
    return;
  }
  return;
}

/* ---- 0x00406670  rdCache_Reset ---- */
/* Empties the 1024-entry mesh list (0x78 bytes each at g_RdCacheMeshes) and the vertex/uv/colour
   pools */

void __cdecl rdCache_Reset(void)

{
  g_dwRdCache_numProcFaces = 0;
  g_dwNumUsedVertices = 0;
  g_dwNumUsedTexVertices = 0;
  g_dwNumUsedIntensities = 0;
  return;
}

/* ---- 0x00406690  rdCache_ClearFrameCounters ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name rdCache_ClearFrameCounters (the remaster's GrimFandango (Linux): clears
   rdCache_drawnFaces); was rdCache_ClearStats. */

void __cdecl rdCache_ClearFrameCounters(void)

{
  _g_dwRdCache_drawnFaces = 0;
  return;
}

/* ---- 0x004066a0  rdCache_GetProcEntry ---- */
/* Returns the next free cached-mesh record, flushing first when the list or a 0x8000-entry pool is
   full Original name rdCache_GetProcEntry (the remaster's GrimFandango (Linux): aligned call in
   rdModel3_DrawFace, rdSprite_Draw); was rdCache_AllocMesh. */

ProcEntry * __cdecl rdCache_GetProcEntry(void)

{
  ProcEntry *pPVar1;
  uint uVar2;
  
  if (0x3ff < g_dwRdCache_numProcFaces) {
    rdCache_Flush();
  }
  uVar2 = g_dwRdCache_numProcFaces;
  if (0x8000 - g_dwNumUsedVertices < 0x20) {
    return (ProcEntry *)0x0;
  }
  if (0x8000 - g_dwNumUsedTexVertices < 0x20) {
    return (ProcEntry *)0x0;
  }
  if (0x8000 - g_dwNumUsedIntensities < 0x20) {
    return (ProcEntry *)0x0;
  }
  pPVar1 = g_bRdCache_aProcFaces + g_dwRdCache_numProcFaces;
  g_bRdCache_aProcFaces[g_dwRdCache_numProcFaces].pVertices =
       (float *)(&g_aRdCache_Vertices + g_dwNumUsedVertices * 0xc);
  g_bRdCache_aProcFaces[uVar2].pTexVertices = (float *)(&DAT_0068bfb0 + g_dwNumUsedTexVertices * 8);
  g_bRdCache_aProcFaces[uVar2].pIntensities =
       (float *)(&g_aRdCache_Intensities + g_dwNumUsedIntensities * 4);
  g_bRdCache_aProcFaces[uVar2].pRedIntensities =
       (float *)(&g_aRdCache_Intensities + g_dwNumUsedIntensities * 4);
  g_bRdCache_aProcFaces[uVar2].pGreenIntensities =
       (float *)(&g_aGreenIntensities + g_dwNumUsedIntensities * 4);
  g_bRdCache_aProcFaces[uVar2].pBlueIntensities =
       (float *)(&g_aBlueIntensities + g_dwNumUsedIntensities * 4);
  return pPVar1;
}

/* ---- 0x00406770  rdCache_Flush ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Sorts (sort mode 2) and draws every cached mesh with the software or 3D path chosen by the
   occlusion/zbuffer modes */

void __cdecl rdCache_Flush(void)

{
  ProcEntry *pPVar1;
  uint uVar2;
  
  if (g_dwRdCache_numProcFaces != 0) {
    if (g_nRdroid_curSortingMethod == 2) {
      qsort(g_bRdCache_aProcFaces,g_dwRdCache_numProcFaces,0x78,rdCache_ProcFaceCompare);
    }
    if (g_nRdroid_curAcceleration < 1) {
      if (g_nRdroid_curOcclusionMethod == 0) {
        if (g_nRdroid_curZBufferMethod == 0) {
          uVar2 = 0;
          pPVar1 = g_bRdCache_aProcFaces;
          if (g_dwRdCache_numProcFaces != 0) {
            do {
              if ((pPVar1->dwExtraData & 1) == 0) {
                rdCache_DrawFaceN(pPVar1);
              }
              else {
                rdCache_DrawFaceUser(pPVar1);
              }
              pPVar1 = pPVar1 + 1;
              uVar2 = uVar2 + 1;
            } while (uVar2 < g_dwRdCache_numProcFaces);
          }
        }
        else if (g_nRdroid_curZBufferMethod == 2) {
          uVar2 = 0;
          pPVar1 = g_bRdCache_aProcFaces;
          if (g_dwRdCache_numProcFaces != 0) {
            do {
              if ((pPVar1->dwExtraData & 1) == 0) {
                rdCache_DrawFaceZ(pPVar1);
              }
              else {
                rdCache_DrawFaceUser(pPVar1);
              }
              pPVar1 = pPVar1 + 1;
              uVar2 = uVar2 + 1;
            } while (uVar2 < g_dwRdCache_numProcFaces);
          }
        }
      }
      else if (g_nRdroid_curOcclusionMethod == 1) {
        rdActive_AdvanceFrame();
        rdActive_DrawScene();
      }
    }
    else {
      rdCache_SendFaceListToHardware();
    }
    _g_dwRdCache_drawnFaces = _g_dwRdCache_drawnFaces + g_dwRdCache_numProcFaces;
    rdCache_Reset();
  }
  return;
}

/* ---- 0x00406860  rdCache_AddProcFace ---- */
/* Appends a mesh to the cache list and computes its screen bounds / depth Original name
   rdCache_AddProcFace (the remaster's GrimFandango (Linux): aligned call in rdModel3_DrawFace,
   rdSprite_Draw); was rdCache_AddMesh. */

int __cdecl rdCache_AddProcFace(void *mesh,uint vertexCount,byte flags)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  float fVar7;
  uint uVar8;
  longlong lVar9;
  #define local_10 (*(float (*)[3])(_frame + (0x20 - 0x10)))
  
  uVar6 = g_dwRdCache_numProcFaces;
  if (0x3ff < g_dwRdCache_numProcFaces) {
    return 0;
  }
  pfVar3 = g_bRdCache_aProcFaces[g_dwRdCache_numProcFaces].pVertices;
  g_bRdCache_aProcFaces[g_dwRdCache_numProcFaces].dwExtraData = (uint)mesh;
  g_bRdCache_aProcFaces[uVar6].dwNumVertices = vertexCount;
  g_bRdCache_aProcFaces[uVar6].dwUserData = g_dwRdroid_curProcFaceUserData;
  local_10[1] = *pfVar3;
  fVar1 = pfVar3[1];
  g_bRdCache_aProcFaces[uVar6].dwMaxYVertex = 0;
  g_bRdCache_aProcFaces[uVar6].dwMinYVertex = 0;
  fVar2 = pfVar3[2];
  uVar8 = 1;
  g_bRdCache_aProcFaces[uVar6].flMaxZ = fVar2;
  g_bRdCache_aProcFaces[uVar6].flMinZ = fVar2;
  local_10[0] = fVar1;
  local_10[2] = local_10[1];
  if (1 < vertexCount) {
    do {
      fVar2 = pfVar3[3];
      fVar4 = pfVar3[4];
      fVar5 = pfVar3[5];
      fVar7 = fVar2;
      if ((local_10[2] <= fVar2) && (fVar7 = local_10[2], local_10[1] <= fVar2)) {
        local_10[1] = fVar2;
      }
      local_10[2] = fVar7;
      if (fVar1 <= fVar4) {
        if (local_10[0] < fVar4) {
          g_bRdCache_aProcFaces[uVar6].dwMaxYVertex = uVar8;
          local_10[0] = fVar4;
        }
      }
      else {
        g_bRdCache_aProcFaces[uVar6].dwMinYVertex = uVar8;
        fVar1 = fVar4;
      }
      if (g_bRdCache_aProcFaces[uVar6].flMinZ <= fVar5) {
        if (g_bRdCache_aProcFaces[uVar6].flMaxZ < fVar5) {
          g_bRdCache_aProcFaces[uVar6].flMaxZ = fVar5;
        }
      }
      else {
        g_bRdCache_aProcFaces[uVar6].flMinZ = fVar5;
      }
      uVar8 = uVar8 + 1;
      pfVar3 = pfVar3 + 3;
    } while (uVar8 < vertexCount);
  }
  if (local_10[2] < local_10[1]) {
    if (fVar1 < local_10[0]) {
      lVar9 = FTOL((float10)ROUND(local_10[2]));
      g_bRdCache_aProcFaces[uVar6].dwMinX = (uint)lVar9;
      lVar9 = FTOL((float10)ROUND(local_10[1]));
      g_bRdCache_aProcFaces[uVar6].dwMaxX = (uint)lVar9;
      lVar9 = FTOL((float10)ROUND(fVar1));
      g_bRdCache_aProcFaces[uVar6].dwMinY = (uint)lVar9;
      lVar9 = FTOL((float10)ROUND(local_10[0]));
      g_bRdCache_aProcFaces[uVar6].dwMaxY = (uint)lVar9;
      if ((flags & 1) != 0) {
        g_dwNumUsedVertices = g_dwNumUsedVertices + vertexCount;
      }
      if ((flags & 2) != 0) {
        g_dwNumUsedTexVertices = g_dwNumUsedTexVertices + vertexCount;
      }
      if ((flags & 4) != 0) {
        g_dwNumUsedIntensities = g_dwNumUsedIntensities + vertexCount;
      }
      g_bRdCache_aProcFaces[uVar6].dwColormap = g_dwRdColormap_pIdentityMap;
      g_dwRdCache_numProcFaces = g_dwRdCache_numProcFaces + 1;
      if (g_bRdCache_aProcFaces[uVar6].dwMinX < (uint)g_nRdCache_ulcExtent) {
        g_nRdCache_ulcExtent = g_bRdCache_aProcFaces[uVar6].dwMinX;
      }
      if ((uint)g_nRdCache_lrcExtent < g_bRdCache_aProcFaces[uVar6].dwMaxX) {
        g_nRdCache_lrcExtent = g_bRdCache_aProcFaces[uVar6].dwMaxX;
      }
      if (g_bRdCache_aProcFaces[uVar6].dwMinY < (uint)g_nDrawBoxMinY) {
        g_nDrawBoxMinY = g_bRdCache_aProcFaces[uVar6].dwMinY;
      }
      if ((uint)g_nDrawBoxMaxY < g_bRdCache_aProcFaces[uVar6].dwMaxY) {
        g_nDrawBoxMaxY = g_bRdCache_aProcFaces[uVar6].dwMaxY;
      }
      return 1;
    }
    return 0;
  }
  return 0;
}
#undef local_10


/* ---- 0x00406aa0  rdCache_SendFaceListToHardware ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Direct3D path: uploads the material textures (rdMaterial_EnsureTexture) and batches the cached
   meshes into execute buffers Original name rdCache_SendFaceListToHardware (the remaster's
   GrimFandango (Linux): aligned call in rdCache_Flush); was rdCache_DrawMeshList3D. */

uint __cdecl rdCache_SendFaceListToHardware(void)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  uint *material;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  uint uVar10;
  int *piVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  ProcEntry *pPVar15;
  uint uVar16;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  longlong lVar17;
  longlong lVar18;
  #define local_7c (*(float (*)[3])(_frame + (0x90 - 0x7c)))
  #define local_70 (*(uint *)(_frame + (0x90 - 0x70)))
  #define local_6c (*(uint *)(_frame + (0x90 - 0x6c)))
  #define local_68 (*(uint *)(_frame + (0x90 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0x90 - 0x64)))
  #define local_60 (*(uint *)(_frame + (0x90 - 0x60)))
  #define local_5c (*(uint *)(_frame + (0x90 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0x90 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x90 - 0x54)))
  #define local_50 (*(uint *)(_frame + (0x90 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0x90 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x90 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x90 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x90 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x90 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x90 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x90 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x90 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x90 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x90 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x90 - 0x24)))
  #define local_20 (*(float *)(_frame + (0x90 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x90 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x90 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x90 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x90 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x90 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x90 - 0x8)))
  
  bVar6 = false;
  bVar7 = false;
  bVar9 = false;
  bVar8 = false;
  local_4c = 0;
  local_44 = 0x33;
  if (g_nRdroid_curZBufferMethod == 1) {
    local_44 = 0x1033;
  }
  else if (g_nRdroid_curZBufferMethod == 2) {
    local_44 = 0x1833;
  }
  else if (g_nRdroid_curZBufferMethod == 3) {
    local_44 = 0x833;
  }
  if (((0.0f < _DAT_0090002c) || (0.0f < _DAT_00900030)) || (0.0f < _DAT_00900034)) {
    bVar6 = true;
    bVar9 = true;
    local_58 = PUN(uint,(float)(_DAT_0090002c - (_DAT_00900034 * 0.5f + _DAT_00900030 * 0.5f)));
    local_20 = _DAT_0090002c * 0.5f;
    local_60 = PUN(uint,(float)(_DAT_00900030 - (local_20 + _DAT_00900034 * 0.5f)));
    local_5c = PUN(uint,(float)(_DAT_00900034 - (local_20 + _DAT_00900030 * 0.5f)));
  }
  if (((g_dwRdroid_curColorEffects != 0) || (UINT_00900024 != 0)) || (UINT_00900028 != 0)) {
    bVar7 = true;
    bVar8 = true;
  }
  if (((bVar6) || (bVar7)) || (g_dwRdroid_curVertexColorMode == 1)) {
    local_44 = local_44 | 0x8000;
  }
  std3D_ResetRenderList();
  pPVar15 = g_bRdCache_aProcFaces;
  local_64 = 0;
  if (g_dwRdCache_numProcFaces == 0) {
    rdCache_DrawRenderList();
    return 1;
  }
  do {
    uVar16 = local_28;
    if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
      local_c = 0;
    }
    else {
      local_c = PUN(uint,(float)pPVar15->flAlpha);
    }
    local_30 = local_44;
    if (g_dwStd3D_maxVertices <= g_dwTotalVerts + pPVar15->dwNumVertices) {
      rdCache_DrawRenderList();
      std3D_ResetRenderList();
    }
    uVar10 = g_dwTotalVerts;
    local_8 = pPVar15->nGeometryMode;
    if (g_nRdroid_curGeometryMode <= (int)local_8) {
      local_8 = g_nRdroid_curGeometryMode;
    }
    local_34 = pPVar15->nLightingMode;
    if (g_nRdroid_curLightingMode <= (int)local_34) {
      local_34 = g_nRdroid_curLightingMode;
    }
    if ((pPVar15->dwFlags & 2) == 0) {
      iVar12 = 0xff;
      local_24 = 0xff;
    }
    else {
      iVar12 = 200;
      local_30 = local_44 | 0x200;
      local_24 = 200;
    }
    if (((iVar12 != 0xff) && (g_pStd3D_CurDevice->nUnknown18 == 0)) &&
       (g_pStd3D_CurDevice->nUnknown14 == 0)) {
      local_24 = 0xff;
      local_4c = 1;
    }
    local_20 = (float)pPVar15->pMaterial;
    if (PUN(rdMaterial *,(float)local_20) != (rdMaterial *)0x0) {
      iVar12 = pPVar15->nCel;
      if (iVar12 == -1) {
        iVar12 = (PUN(rdMaterial *,(float)local_20))->nCurCel;
        if (iVar12 < 0) {
LAB_00406cbf:
          iVar12 = 0;
        }
        else {
          iVar14 = (PUN(rdMaterial *,(float)local_20))->nNumCels + -1;
          if (iVar14 < iVar12) {
            iVar12 = iVar14;
          }
        }
      }
      else {
        if (iVar12 < 0) goto LAB_00406cbf;
        iVar14 = (PUN(rdMaterial *,(float)local_20))->nNumCels + -1;
        if (iVar14 < iVar12) {
          iVar12 = iVar14;
        }
      }
      local_2c = (uint)(PUN(rdMaterial *,(float)local_20))->aCels[iVar12];
      if ((local_8 == 4) && ((*(byte *)local_2c & 8) == 0)) {
        local_8 = 3;
      }
      if (((byte *)local_2c == (byte *)0x0) || ((*(byte *)local_2c & 8) == 0)) {
        local_40 = 0;
      }
      else {
        material = *(uint **)(local_2c + 0x1c);
        uVar13 = material[6];
        if (uVar13 == 1) {
          uVar16 = 0;
          local_28 = uVar16;
        }
        else if (uVar13 == 2) {
          if (_g_aRdroid_MipDistances < pPVar15->flMinZ) {
LAB_00406d8d:
            uVar16 = 1;
            local_28 = uVar16;
          }
          else {
            uVar16 = 0;
            local_28 = uVar16;
          }
        }
        else if (uVar13 == 3) {
          if (FLOAT_004dda90 < pPVar15->flMinZ) {
            if (pPVar15->flMinZ <= _g_aRdroid_MipDistances) goto LAB_00406d8d;
            uVar16 = 2;
            local_28 = uVar16;
          }
          else {
            uVar16 = 0;
            local_28 = uVar16;
          }
        }
        else if (uVar13 == 4) {
          if (FLOAT_004dda90 < pPVar15->flMinZ) {
            if (pPVar15->flMinZ <= _g_aRdroid_MipDistances) goto LAB_00406d8d;
            if (FLOAT_004dda98 < pPVar15->flMinZ) {
              uVar16 = 3;
              local_28 = uVar16;
            }
            else {
              uVar16 = 2;
              local_28 = uVar16;
            }
          }
          else {
            uVar16 = 0;
            local_28 = uVar16;
          }
        }
        if (((*material & 1) != 0) && (g_pStd3D_CurDevice->nPalettedTextures != 0)) {
          local_30 = local_30 | 0x400;
        }
        if (material[uVar16 * 0x26 + 0x29] == 0) {
          std3D_SetCurrentPalette((void *)(pPVar15->dwColormap + 0x30),0x5a);
        }
        iVar12 = rdMaterial_AddToTextureCache(PUN(void *,(float)local_20),material,uVar16,local_4c);
        if (iVar12 == 0) {
          rdCache_DrawRenderList();
          std3D_ResetRenderList();
          std3D_PurgeTextureCache();
          iVar12 = rdMaterial_AddToTextureCache(PUN(void *,(float)local_20),material,uVar16,local_4c);
          if (iVar12 == 0) {
            return 0;
          }
        }
        if (local_4c == 0) {
          iVar12 = uVar16 * 0x26 + 0xb;
        }
        else {
          iVar12 = uVar16 * 0x26 + 0xa3;
        }
        local_40 = (uint)(material + iVar12);
        std3D_GetValidDimensions
                  (*(uint *)(material[uVar16 + 7] + 0xc),*(uint *)(material[uVar16 + 7] + 0x10),
                   &local_38,&local_3c);
        local_7c[0] = (float)(local_38 << ((byte)uVar16 & 0x1f));
        local_7c[1] = (float)(local_3c << ((byte)uVar16 & 0x1f));
      }
      if (local_8 == 3) {
        fVar4 = (float)local_c;
        if (local_34 == 1) {
          if (pPVar15->flLight < 0.0f) {
            fVar1 = 0.0f;
          }
          else if (1.0f < pPVar15->flLight) {
            fVar1 = 1.0f;
          }
          else {
            fVar1 = pPVar15->flLight;
          }
          if ((float)local_c < fVar1) {
            if (pPVar15->flLight < 0.0f) {
LAB_00407a17:
              fVar4 = 0.0f;
            }
            else if (1.0f < pPVar15->flLight) {
LAB_00407a0f:
              fVar4 = 1.0f;
            }
            else {
              fVar4 = pPVar15->flLight;
            }
          }
LAB_00407a22:
          pPVar15->flLightIndex = fVar4 * 63.0f;
        }
        else {
          if (local_34 == 2) {
            fVar1 = pPVar15->flLight + pPVar15->flLightIndex;
            if (fVar1 < 0.0f) {
              fVar5 = 0.0f;
            }
            else {
              fVar5 = fVar1;
              if (1.0f < fVar1) {
                fVar5 = 1.0f;
              }
            }
            if ((float)local_c < fVar5) {
              if (fVar1 < 0.0f) goto LAB_00407a17;
              fVar4 = fVar1;
              if (1.0f < fVar1) goto LAB_00407a0f;
            }
            goto LAB_00407a22;
          }
          if (local_34 == 3) {
            if (g_dwRdroid_curVertexColorMode == 1) {
              uVar16 = 0;
              if (pPVar15->dwNumVertices != 0) {
                do {
                  fVar4 = pPVar15->flLight + pPVar15->pIntensities[uVar16];
                  if (fVar4 < 0.0f) {
                    fVar1 = 0.0f;
                  }
                  else {
                    fVar1 = fVar4;
                    if (1.0f < fVar4) {
                      fVar1 = 1.0f;
                    }
                  }
                  fVar5 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar4 < 0.0f) {
                      fVar5 = 0.0f;
                    }
                    else {
                      fVar5 = fVar4;
                      if (1.0f < fVar4) {
                        fVar5 = 1.0f;
                      }
                    }
                  }
                  pPVar15->pIntensities[uVar16] = fVar5 * 63.0f;
                  fVar4 = pPVar15->flLight + pPVar15->pRedIntensities[uVar16];
                  if (fVar4 < 0.0f) {
                    fVar1 = 0.0f;
                  }
                  else {
                    fVar1 = fVar4;
                    if (1.0f < fVar4) {
                      fVar1 = 1.0f;
                    }
                  }
                  fVar5 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar4 < 0.0f) {
                      fVar5 = 0.0f;
                    }
                    else {
                      fVar5 = fVar4;
                      if (1.0f < fVar4) {
                        fVar5 = 1.0f;
                      }
                    }
                  }
                  pPVar15->pRedIntensities[uVar16] = fVar5 * 63.0f;
                  fVar4 = pPVar15->pGreenIntensities[uVar16] + pPVar15->flLight;
                  if (fVar4 < 0.0f) {
                    fVar1 = 0.0f;
                  }
                  else {
                    fVar1 = fVar4;
                    if (1.0f < fVar4) {
                      fVar1 = 1.0f;
                    }
                  }
                  fVar5 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar4 < 0.0f) {
                      fVar5 = 0.0f;
                    }
                    else {
                      fVar5 = fVar4;
                      if (1.0f < fVar4) {
                        fVar5 = 1.0f;
                      }
                    }
                  }
                  pPVar15->pGreenIntensities[uVar16] = fVar5 * 63.0f;
                  fVar4 = pPVar15->flLight + pPVar15->pBlueIntensities[uVar16];
                  pfVar2 = pPVar15->pBlueIntensities + uVar16;
                  if (fVar4 < 0.0f) {
                    fVar1 = 0.0f;
                  }
                  else {
                    fVar1 = fVar4;
                    if (1.0f < fVar4) {
                      fVar1 = 1.0f;
                    }
                  }
                  fVar5 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar4 < 0.0f) {
                      fVar5 = 0.0f;
                    }
                    else {
                      fVar5 = fVar4;
                      if (1.0f < fVar4) {
                        fVar5 = 1.0f;
                      }
                    }
                  }
                  uVar16 = uVar16 + 1;
                  *pfVar2 = fVar5 * 63.0f;
                } while (uVar16 < pPVar15->dwNumVertices);
              }
            }
            else {
              uVar16 = 0;
              if (pPVar15->dwNumVertices != 0) {
                do {
                  fVar4 = pPVar15->flLight + pPVar15->pIntensities[uVar16];
                  pfVar2 = pPVar15->pIntensities + uVar16;
                  if (fVar4 < 0.0f) {
                    fVar1 = 0.0f;
                  }
                  else {
                    fVar1 = fVar4;
                    if (1.0f < fVar4) {
                      fVar1 = 1.0f;
                    }
                  }
                  fVar5 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar4 < 0.0f) {
                      fVar5 = 0.0f;
                    }
                    else {
                      fVar5 = fVar4;
                      if (1.0f < fVar4) {
                        fVar5 = 1.0f;
                      }
                    }
                  }
                  uVar16 = uVar16 + 1;
                  *pfVar2 = fVar5 * 63.0f;
                } while (uVar16 < pPVar15->dwNumVertices);
              }
            }
          }
        }
        local_8 = 0;
        if (pPVar15->dwNumVertices != 0) {
          local_20 = (float)(local_24 << 8);
          local_24 = 0;
          do {
            pfVar2 = pPVar15->pVertices;
            *(float *)(&g_aHWVertices + g_dwTotalVerts * 0x20) =
                 ROUND(*(float *)(local_24 + (int)pPVar15->pVertices));
            local_14 = *(uint *)(local_24 + 4 + (int)pfVar2);
            pfVar2 = pPVar15->pVertices;
            iVar12 = g_dwTotalVerts * 0x20;
            *(float *)(&DAT_006f0fbc + iVar12) = ROUND((float)local_14);
            if (*(float *)(local_24 + 8 + (int)pfVar2) == 0.0f) {
              fVar4 = 0.0f;
            }
            else {
              local_14 = 0xffffffff;
              if (UINT_00900534 == 0x10) {
                local_14 = 1;
              }
              fVar4 = 1.0f / ((float)(int)local_14 + *(float *)(local_24 + 8 + (int)pfVar2));
            }
            *(float *)(&DAT_006f0fc0 + iVar12) = fVar4;
            *(float *)(&DAT_006f0fc4 + iVar12) = fVar4 * 0.03125f;
            *(undefined4 *)(&DAT_006f0fcc + iVar12) = 0;
            if (local_34 == 0) {
              iVar14 = *(int *)(local_2c + 4) * 3 + pPVar15->dwColormap;
              local_1c = (uint)*(byte *)(iVar14 + 0x30);
              local_10 = (uint)*(byte *)(iVar14 + 0x31);
              local_18 = (uint)*(byte *)(iVar14 + 0x32);
            }
            else if (local_34 == 3) {
              if (g_dwRdroid_curVertexColorMode != 1) {
                iVar14 = *(int *)(local_2c + 4) * 3 + pPVar15->dwColormap;
                local_14 = (uint)*(byte *)(iVar14 + 0x30);
                lVar17 = FTOL((float10)local_14 *
                               (float10)pPVar15->pIntensities[local_8] * (float10)0.015625f);
                local_1c = (uint)lVar17;
                local_14 = (uint)*(byte *)(iVar14 + 0x31);
                lVar17 = FTOL((float10)local_14 * extraout_ST0_01);
                local_10 = (uint)lVar17;
                local_14 = (uint)*(byte *)(iVar14 + 0x32);
                lVar17 = FTOL((float10)local_14 * extraout_ST0_02);
                local_18 = (uint)lVar17;
              }
            }
            else {
              iVar14 = *(int *)(local_2c + 4) * 3;
              local_14 = (uint)*(byte *)(iVar14 + 0x30 + pPVar15->dwColormap);
              iVar14 = iVar14 + pPVar15->dwColormap;
              lVar17 = FTOL((float10)local_14 * (float10)pPVar15->flLightIndex * (float10)0.015625f)
              ;
              local_1c = (uint)lVar17;
              local_14 = (uint)*(byte *)(iVar14 + 0x31);
              lVar17 = FTOL((float10)local_14 * extraout_ST0);
              local_10 = (uint)lVar17;
              local_14 = (uint)*(byte *)(iVar14 + 0x32);
              lVar17 = FTOL((float10)local_14 * extraout_ST0_00);
              local_18 = (uint)lVar17;
            }
            uVar16 = pPVar15->dwColormap;
            uVar13 = local_10;
            if (uVar16 != g_dwRdColormap_pCurMap) {
              lVar17 = FTOL((float10)(int)local_1c * (float10)*(float *)(uVar16 + 0x24));
              local_1c = (uint)lVar17 & 0xff;
              lVar17 = FTOL((float10)(int)local_10 * (float10)*(float *)(uVar16 + 0x28));
              uVar13 = (uint)lVar17 & 0xff;
              local_10 = uVar13;
              lVar17 = FTOL((float10)(int)local_18 *
                             (float10)*(float *)(pPVar15->dwColormap + 0x2c));
              local_18 = (uint)lVar17 & 0xff;
            }
            local_30 = local_30 | 0x8000;
            if (bVar8) {
              if (g_dwRdroid_curColorEffects == 0) {
                local_1c = 0;
              }
              if (UINT_00900024 == 0) {
                uVar13 = 0;
                local_10 = 0;
              }
              if (UINT_00900028 == 0) {
                local_18 = 0;
              }
            }
            if (bVar9) {
              lVar17 = FTOL((float10)(int)local_1c * (float10)(float)local_58);
              local_1c = local_1c + (int)lVar17;
              lVar17 = FTOL((float10)(int)local_10 * (float10)(float)local_60);
              uVar13 = uVar13 + (int)lVar17;
              local_10 = uVar13;
              lVar17 = FTOL((float10)(int)local_18 * (float10)(float)local_5c);
              local_18 = local_18 + (int)lVar17;
            }
            if (FLOAT_00900044 < 1.0f) {
              lVar17 = FTOL((float10)(int)local_1c * (float10)FLOAT_00900044);
              local_1c = (uint)lVar17;
              lVar17 = FTOL((float10)(int)local_10 * (float10)FLOAT_00900044);
              uVar13 = (uint)lVar17;
              lVar17 = FTOL((float10)(int)local_18 * (float10)FLOAT_00900044);
              local_18 = (uint)lVar17;
            }
            if ((int)local_1c < 0) {
              local_1c = 0;
            }
            else if (0xff < (int)local_1c) {
              local_1c = 0xff;
            }
            local_1c = local_1c & 0xff;
            if ((int)uVar13 < 0) {
              uVar13 = 0;
            }
            else if (0xff < (int)uVar13) {
              uVar13 = 0xff;
            }
            local_10 = uVar13 & 0xff;
            if ((int)local_18 < 0) {
              local_18 = 0;
            }
            else if (0xff < (int)local_18) {
              local_18 = 0xff;
            }
            local_18 = local_18 & 0xff;
            g_dwTotalVerts = g_dwTotalVerts + 1;
            *(uint *)(&DAT_006f0fc8 + iVar12) =
                 ((local_1c | PUN(uint,(float)local_20)) << 8 | local_10) << 8 | local_18;
            uVar16 = pPVar15->dwNumVertices;
            *(undefined4 *)(&DAT_006f0fd0 + iVar12) = 0;
            *(undefined4 *)(&DAT_006f0fd4 + iVar12) = 0;
            local_8 = local_8 + 1;
            local_24 = local_24 + 0xc;
          } while (local_8 < uVar16);
        }
        uVar16 = pPVar15->dwNumVertices;
        if (uVar16 < 4) {
          iVar12 = g_dwTotalSolidTris * 0x14;
          *(uint *)(&DAT_00606fa8 + iVar12) = uVar10;
          *(uint *)(&DAT_00606fa4 + iVar12) = uVar10 + 1;
          *(uint *)(&g_aHWSolidTris + iVar12) = uVar10 + 2;
          g_dwTotalSolidTris = g_dwTotalSolidTris + 1;
          *(uint *)(&DAT_00606fac + iVar12) = local_30;
          *(undefined4 *)(&DAT_00606fb0 + iVar12) = 0;
        }
        else {
          local_20 = (float)(uVar16 - 2);
          uVar13 = 0;
          local_34 = uVar16 - 1;
          uVar16 = 0;
          local_8 = 1;
          if (0 < PUN(int,(float)local_20)) {
            piVar11 = (int *)(&DAT_00606fa4 + g_dwTotalSolidTris * 0x14);
            g_dwTotalSolidTris = g_dwTotalSolidTris + PUN(int,(float)local_20);
            do {
              piVar11[1] = uVar13 + uVar10;
              *piVar11 = local_8 + uVar10;
              piVar11[-1] = uVar10 + local_34;
              piVar11[2] = local_30;
              piVar11[3] = 0;
              if ((~uVar16 & 1) == 0) {
                uVar13 = local_34;
                local_34 = local_34 - 1;
              }
              else {
                uVar13 = local_8;
                local_8 = local_8 + 1;
              }
              piVar11 = piVar11 + 5;
              uVar16 = uVar16 + 1;
            } while ((int)uVar16 < PUN(int,(float)local_20));
          }
        }
      }
      else {
        if (local_8 != 4) goto LAB_00407e89;
        fVar4 = (float)local_c;
        if (local_34 == 1) {
          if (pPVar15->flLight < 0.0f) {
            fVar1 = 0.0f;
          }
          else if (1.0f < pPVar15->flLight) {
            fVar1 = 1.0f;
          }
          else {
            fVar1 = pPVar15->flLight;
          }
          if ((float)local_c < fVar1) {
            if (pPVar15->flLight < 0.0f) {
LAB_004071ef:
              fVar4 = 0.0f;
            }
            else if (1.0f < pPVar15->flLight) {
LAB_004071e7:
              fVar4 = 1.0f;
            }
            else {
              fVar4 = pPVar15->flLight;
            }
          }
LAB_004071fa:
          pPVar15->flLightIndex = fVar4 * 255.0;
        }
        else {
          if (local_34 == 2) {
            fVar1 = pPVar15->flLight + pPVar15->flLightIndex;
            if (fVar1 < 0.0f) {
              fVar5 = 0.0f;
            }
            else {
              fVar5 = fVar1;
              if (1.0f < fVar1) {
                fVar5 = 1.0f;
              }
            }
            if ((float)local_c < fVar5) {
              if (fVar1 < 0.0f) goto LAB_004071ef;
              fVar4 = fVar1;
              if (1.0f < fVar1) goto LAB_004071e7;
            }
            goto LAB_004071fa;
          }
          if (local_34 == 3) {
            if (g_dwRdroid_curVertexColorMode == 1) {
              uVar16 = 0;
              if (pPVar15->dwNumVertices != 0) {
                do {
                  fVar4 = pPVar15->flLight + pPVar15->pRedIntensities[uVar16];
                  if (fVar4 < 0.0f) {
                    fVar1 = 0.0f;
                  }
                  else {
                    fVar1 = fVar4;
                    if (1.0f < fVar4) {
                      fVar1 = 1.0f;
                    }
                  }
                  fVar5 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar4 < 0.0f) {
                      fVar5 = 0.0f;
                    }
                    else {
                      fVar5 = fVar4;
                      if (1.0f < fVar4) {
                        fVar5 = 1.0f;
                      }
                    }
                  }
                  pPVar15->pRedIntensities[uVar16] = fVar5 * 255.0;
                  fVar4 = pPVar15->pGreenIntensities[uVar16] + pPVar15->flLight;
                  if (fVar4 < 0.0f) {
                    fVar1 = 0.0f;
                  }
                  else {
                    fVar1 = fVar4;
                    if (1.0f < fVar4) {
                      fVar1 = 1.0f;
                    }
                  }
                  fVar5 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar4 < 0.0f) {
                      fVar5 = 0.0f;
                    }
                    else {
                      fVar5 = fVar4;
                      if (1.0f < fVar4) {
                        fVar5 = 1.0f;
                      }
                    }
                  }
                  pPVar15->pGreenIntensities[uVar16] = fVar5 * 255.0;
                  fVar4 = pPVar15->flLight + pPVar15->pBlueIntensities[uVar16];
                  pfVar2 = pPVar15->pBlueIntensities + uVar16;
                  if (fVar4 < 0.0f) {
                    fVar1 = 0.0f;
                  }
                  else {
                    fVar1 = fVar4;
                    if (1.0f < fVar4) {
                      fVar1 = 1.0f;
                    }
                  }
                  fVar5 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar4 < 0.0f) {
                      fVar5 = 0.0f;
                    }
                    else {
                      fVar5 = fVar4;
                      if (1.0f < fVar4) {
                        fVar5 = 1.0f;
                      }
                    }
                  }
                  uVar16 = uVar16 + 1;
                  *pfVar2 = fVar5 * 255.0;
                } while (uVar16 < pPVar15->dwNumVertices);
              }
            }
            else {
              uVar16 = 0;
              if (pPVar15->dwNumVertices != 0) {
                do {
                  fVar4 = pPVar15->flLight + pPVar15->pIntensities[uVar16];
                  pfVar2 = pPVar15->pIntensities + uVar16;
                  if (fVar4 < 0.0f) {
                    fVar1 = 0.0f;
                  }
                  else {
                    fVar1 = fVar4;
                    if (1.0f < fVar4) {
                      fVar1 = 1.0f;
                    }
                  }
                  fVar5 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar4 < 0.0f) {
                      fVar5 = 0.0f;
                    }
                    else {
                      fVar5 = fVar4;
                      if (1.0f < fVar4) {
                        fVar5 = 1.0f;
                      }
                    }
                  }
                  uVar16 = uVar16 + 1;
                  *pfVar2 = fVar5 * 255.0;
                } while (uVar16 < pPVar15->dwNumVertices);
              }
            }
          }
        }
        local_8 = 0;
        if (pPVar15->dwNumVertices != 0) {
          local_2c = (uint)pPVar15->pVertices;
          local_20 = (float)(local_24 << 8);
          local_24 = 0;
          do {
            uVar13 = local_8;
            pfVar2 = pPVar15->pVertices;
            *(float *)(&g_aHWVertices + g_dwTotalVerts * 0x20) =
                 ROUND(*(float *)(local_24 + local_2c));
            uVar16 = g_dwTotalVerts;
            pfVar3 = pPVar15->pVertices;
            *(float *)(&DAT_006f0fbc + g_dwTotalVerts * 0x20) =
                 ROUND(*(float *)(local_24 + 4 + (int)pfVar2));
            if (*(float *)(local_24 + 8 + (int)pfVar3) == 0.0f) {
              fVar4 = 0.0f;
              local_2c = (uint)pfVar3;
            }
            else {
              local_2c = 0xffffffff;
              if (UINT_00900534 == 0x10) {
                local_2c = 1;
              }
              *(float *)(local_24 + 8 + (int)pfVar3) =
                   (float)(int)local_2c + *(float *)(local_24 + 8 + (int)pfVar3);
              fVar4 = 1.0f / *(float *)(local_24 + 8 + (int)pPVar15->pVertices);
              uVar16 = g_dwTotalVerts;
              local_2c = (uint)pPVar15->pVertices;
            }
            local_14 = uVar16 * 0x20;
            *(float *)(&DAT_006f0fc0 + local_14) = fVar4;
            *(float *)(&DAT_006f0fc4 + local_14) = fVar4;
            *(undefined4 *)(&DAT_006f0fcc + local_14) = 0;
            if (local_34 == 0) {
              local_10 = 0xff;
              uVar16 = local_10;
              local_1c = local_10;
              local_18 = local_10;
            }
            else if (local_34 == 3) {
              if (g_dwRdroid_curVertexColorMode == 1) {
                lVar17 = FTOL((float10)pPVar15->pRedIntensities[local_8]);
                local_1c = (uint)lVar17;
                lVar18 = FTOL((float10)pPVar15->pGreenIntensities[uVar13]);
                local_10 = (uint)lVar18;
                lVar18 = FTOL((float10)pPVar15->pBlueIntensities[uVar13]);
                local_18 = (uint)lVar18;
                uVar16 = (uint)lVar17;
              }
              else {
                lVar17 = FTOL((float10)pPVar15->pIntensities[local_8]);
                local_1c = (uint)lVar17;
                uVar16 = local_1c;
                local_18 = local_1c;
                local_10 = local_1c;
              }
            }
            else {
              lVar17 = FTOL((float10)pPVar15->flLightIndex);
              local_1c = (uint)lVar17;
              uVar16 = local_1c;
              local_18 = local_1c;
              local_10 = local_1c;
            }
            uVar13 = pPVar15->dwColormap;
            if (uVar13 != g_dwRdColormap_pCurMap) {
              lVar17 = FTOL((float10)(int)local_1c * (float10)*(float *)(uVar13 + 0x24));
              uVar16 = (uint)lVar17 & 0xff;
              local_1c = uVar16;
              lVar17 = FTOL((float10)(int)local_10 * (float10)*(float *)(uVar13 + 0x28));
              local_10 = (uint)lVar17 & 0xff;
              lVar17 = FTOL((float10)(int)local_18 * (float10)*(float *)(uVar13 + 0x2c));
              local_18 = (uint)lVar17 & 0xff;
              local_30 = local_30 | 0x8000;
            }
            if (bVar8) {
              if (g_dwRdroid_curColorEffects == 0) {
                uVar16 = 0;
                local_1c = 0;
              }
              if (UINT_00900024 == 0) {
                local_10 = 0;
              }
              if (UINT_00900028 == 0) {
                local_18 = 0;
              }
            }
            uVar13 = local_18;
            if (bVar9) {
              lVar17 = FTOL((float10)(int)local_1c * (float10)(float)local_58);
              uVar16 = uVar16 + (int)lVar17;
              local_1c = uVar16;
              lVar17 = FTOL((float10)(int)local_10 * (float10)(float)local_60);
              local_10 = local_10 + (int)lVar17;
              lVar17 = FTOL((float10)(int)local_18 * (float10)(float)local_5c);
              local_18 = uVar13 + (int)lVar17;
            }
            if (FLOAT_00900044 < 1.0f) {
              lVar17 = FTOL((float10)(int)local_1c * (float10)FLOAT_00900044);
              uVar16 = (uint)lVar17;
              lVar17 = FTOL((float10)(int)local_10 * (float10)FLOAT_00900044);
              local_10 = (uint)lVar17;
              lVar17 = FTOL((float10)(int)local_18 * (float10)FLOAT_00900044);
              local_18 = (uint)lVar17;
            }
            if ((int)uVar16 < 0) {
              uVar16 = 0;
            }
            else if (0xff < (int)uVar16) {
              uVar16 = 0xff;
            }
            local_1c = uVar16 & 0xff;
            if ((int)local_10 < 0) {
              local_10 = 0;
            }
            else if (0xff < (int)local_10) {
              local_10 = 0xff;
            }
            local_10 = local_10 & 0xff;
            if ((int)local_18 < 0) {
              local_18 = 0;
            }
            else if (0xff < (int)local_18) {
              local_18 = 0xff;
            }
            local_18 = local_18 & 0xff;
            pfVar2 = pPVar15->pTexVertices;
            *(uint *)(&DAT_006f0fc8 + local_14) =
                 ((local_1c | PUN(uint,(float)local_20)) << 8 | local_10) << 8 | local_18;
            g_dwTotalVerts = g_dwTotalVerts + 1;
            uVar13 = local_8 + 1;
            *(float *)(&DAT_006f0fd0 + local_14) = pfVar2[local_8 * 2] / local_7c[0];
            uVar16 = pPVar15->dwNumVertices;
            *(float *)(&DAT_006f0fd4 + local_14) = pfVar2[local_8 * 2 + 1] / local_7c[1];
            local_24 = local_24 + 0xc;
            local_8 = uVar13;
          } while (uVar13 < uVar16);
        }
        uVar16 = pPVar15->dwNumVertices;
        if (uVar16 < 4) {
          iVar12 = g_dwTotalNormalTris * 0x14;
          *(uint *)(&DAT_006cbfb8 + iVar12) = uVar10;
          *(uint *)(&DAT_006cbfb4 + iVar12) = uVar10 + 1;
          *(uint *)(&g_aHWNormalTris + iVar12) = uVar10 + 2;
          g_dwTotalNormalTris = g_dwTotalNormalTris + 1;
          *(uint *)(&DAT_006cbfbc + iVar12) = local_30;
          *(uint *)(&DAT_006cbfc0 + iVar12) = local_40;
        }
        else {
          local_20 = (float)(uVar16 - 2);
          uVar13 = 0;
          local_34 = uVar16 - 1;
          uVar16 = 0;
          local_8 = 1;
          if (0 < PUN(int,(float)local_20)) {
            piVar11 = (int *)(&DAT_006cbfb4 + g_dwTotalNormalTris * 0x14);
            g_dwTotalNormalTris = g_dwTotalNormalTris + PUN(int,(float)local_20);
            do {
              piVar11[1] = uVar13 + uVar10;
              *piVar11 = local_8 + uVar10;
              piVar11[-1] = uVar10 + local_34;
              piVar11[2] = local_30;
              piVar11[3] = local_40;
              if ((~uVar16 & 1) == 0) {
                uVar13 = local_34;
                local_34 = local_34 - 1;
              }
              else {
                uVar13 = local_8;
                local_8 = local_8 + 1;
              }
              piVar11 = piVar11 + 5;
              uVar16 = uVar16 + 1;
            } while ((int)uVar16 < PUN(int,(float)local_20));
          }
        }
      }
    }
LAB_00407e89:
    pPVar15 = pPVar15 + 1;
    local_64 = local_64 + 1;
    if (g_dwRdCache_numProcFaces <= local_64) {
      rdCache_DrawRenderList();
      return 1;
    }
  } while( true );
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_44
#undef local_48
#undef local_4c
#undef local_50
#undef local_54
#undef local_58
#undef local_5c
#undef local_60
#undef local_64
#undef local_68
#undef local_6c
#undef local_70
#undef local_7c
#undef local_8
#undef local_c

#endif


/* ---- 0x00407ed0  std3D_ResetRenderList ---- */
/* Original name std3D_ResetRenderList (the remaster's GrimFandango (Linux): aligned call in
   rdCache_SendFaceListToHardware); was rdCache_Begin3DBatch. */

void __cdecl std3D_ResetRenderList(void)

{
  D3D_BeginExecuteBuffer();
  g_dwTotalNormalTris = 0;
  g_dwTotalSolidTris = 0;
  g_dwTotalVerts = 0;
  return;
}

/* ---- 0x00407ef0  rdCache_DrawRenderList ---- */
/* Original name rdCache_DrawRenderList (the remaster's GrimFandango (Linux): aligned call in
   rdCache_SendFaceListToHardware); was rdCache_Flush3DBatch. */

void __cdecl rdCache_DrawRenderList(void)

{
  int iVar1;
  
  if (g_dwTotalVerts != 0) {
    iVar1 = std3D_AddRenderListVertices(&g_aHWVertices,g_dwTotalVerts);
    if (iVar1 == 0) {
      std3D_DrawRenderList();
      std3D_AddRenderListVertices(&g_aHWVertices,g_dwTotalVerts);
    }
    std3D_RenderListVerticesFinish();
    if (g_nRdroid_curZBufferMethod == 2) {
      qsort(&g_aHWNormalTris,g_dwTotalNormalTris,0x14,rdCache_TriCompare);
    }
    if (g_dwTotalSolidTris != 0) {
      std3D_AddRenderListTris(&g_aHWSolidTris,g_dwTotalSolidTris);
    }
    if (g_dwTotalNormalTris != 0) {
      std3D_AddRenderListTris(&g_aHWNormalTris,g_dwTotalNormalTris);
    }
    std3D_DrawRenderList();
    return;
  }
  return;
}

/* ---- 0x00407f90  rdCache_TriCompare ---- */
/* qsort comparator of rdCache_Flush3DBatch: orders entries by material, then by their position in
   the list. Original name rdCache_TriCompare (the remaster's GrimFandango (Linux): aligned call in
   rdCache_DrawRenderList); was rdCache_CompareBatchEntries. */

int __cdecl rdCache_TriCompare(int a,int b)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(a + 0x10) + 0x7c);
  if (iVar1 == *(int *)(*(int *)(b + 0x10) + 0x7c)) {
    return (*(int *)(a + 0x10) - *(int *)(b + 0x10)) / 0x98;
  }
  return (-(uint)(iVar1 != 0) & 2) - 1;
}

/* ---- 0x00407fd0  rdCache_DrawFaceN ---- */
/* Software path without z-buffer: clamps the mesh modes to the global limits and calls the
   rasterizer entry for each face Original name rdCache_DrawFaceN (the remaster's GrimFandango
   (Linux): aligned call in rdCache_Flush); was rdCache_DrawMesh. */

int __cdecl rdCache_DrawFaceN(ProcEntry *face)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *pfVar1;
  float fVar2;
  rdMaterial *prVar3;
  float fVar4;
  float fVar5;
  ProcEntry *poly;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte *mat;
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  poly = face;
  iVar8 = face->nGeometryMode;
  if (g_nRdroid_curGeometryMode <= face->nGeometryMode) {
    iVar8 = g_nRdroid_curGeometryMode;
  }
  iVar9 = face->nLightingMode;
  if (g_nRdroid_curLightingMode <= face->nLightingMode) {
    iVar9 = g_nRdroid_curLightingMode;
  }
  face = (ProcEntry *)face->nTextureMode;
  if (g_nRdroid_curTextureMode <= (int)face) {
    face = (ProcEntry *)g_nRdroid_curTextureMode;
  }
  if (iVar8 == 0) {
    return 0;
  }
  prVar3 = poly->pMaterial;
  if (prVar3 == (rdMaterial *)0x0) {
    mat = (byte *)0x0;
    goto LAB_00408067;
  }
  iVar6 = poly->nCel;
  if (iVar6 == -1) {
    iVar6 = prVar3->nCurCel;
    if (iVar6 < 0) {
LAB_0040804e:
      iVar6 = 0;
    }
    else {
      iVar10 = prVar3->nNumCels + -1;
      if (iVar10 < iVar6) {
        iVar6 = iVar10;
      }
    }
  }
  else {
    if (iVar6 < 0) goto LAB_0040804e;
    iVar10 = prVar3->nNumCels + -1;
    if (iVar10 < iVar6) {
      iVar6 = iVar10;
    }
  }
  mat = prVar3->aCels[iVar6];
  if ((iVar8 == 4) && ((*mat & 8) == 0)) {
    iVar8 = 3;
  }
LAB_00408067:
  if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
    local_4 = 0.0f;
  }
  else {
    local_4 = poly->flAlpha;
  }
  switch(iVar8) {
  case 1:
    if ((-1 < iVar9) && (iVar9 < 5)) {
      rdNRaster_DrawNGonLV((int)poly,(int)mat);
      return 1;
    }
    break;
  case 2:
    if ((-1 < iVar9) && (iVar9 < 5)) {
      rdNRaster_DrawNGonLW((int)poly,(int)mat);
      return 1;
    }
    break;
  case 3:
    switch(iVar9) {
    case 0:
      if ((poly->dwFlags & 2) == 0) {
        rdNRaster_DrawNGonLS((int)poly,(int)mat);
        return 1;
      }
      rdNRaster_DrawNGonTLS((int)poly,(int)mat);
      return 1;
    case 1:
      if (poly->flLight < 0.0f) {
        fVar2 = 0.0f;
      }
      else if (1.0f < poly->flLight) {
        fVar2 = 1.0f;
      }
      else {
        fVar2 = poly->flLight;
      }
      if (local_4 < fVar2) {
        if (poly->flLight < 0.0f) {
          local_4 = 0.0f;
        }
        else if (1.0f < poly->flLight) {
          local_4 = 1.0f;
        }
        else {
          local_4 = poly->flLight;
        }
      }
      fVar2 = local_4 * 63.0f;
      poly->flLightIndex = fVar2;
      if ((poly->dwFlags & 2) == 0) {
        rdNRaster_DrawNGonFS((int)poly,(int)mat,fVar2);
        return 1;
      }
      rdNRaster_DrawNGonTFS((int)poly,(int)mat,fVar2);
      return 1;
    case 2:
      fVar2 = poly->flLight + poly->flLightIndex;
      if (fVar2 < 0.0f) {
        fVar4 = 0.0f;
      }
      else {
        fVar4 = fVar2;
        if (1.0f < fVar2) {
          fVar4 = 1.0f;
        }
      }
      if (local_4 < fVar4) {
        if (fVar2 < 0.0f) {
          local_4 = 0.0f;
        }
        else {
          local_4 = fVar2;
          if (1.0f < fVar2) {
            local_4 = 1.0f;
          }
        }
      }
      fVar2 = local_4 * 63.0f;
      poly->flLightIndex = fVar2;
      if ((poly->dwFlags & 2) == 0) {
        rdNRaster_DrawNGonFS((int)poly,(int)mat,fVar2);
        return 1;
      }
      rdNRaster_DrawNGonTFS((int)poly,(int)mat,fVar2);
      return 1;
    case 3:
      uVar7 = 0;
      if (poly->dwNumVertices != 0) {
        do {
          fVar2 = poly->flLight + poly->pIntensities[uVar7];
          pfVar1 = poly->pIntensities + uVar7;
          if (fVar2 < 0.0f) {
            fVar4 = 0.0f;
          }
          else {
            fVar4 = fVar2;
            if (1.0f < fVar2) {
              fVar4 = 1.0f;
            }
          }
          fVar5 = local_4;
          if (local_4 < fVar4) {
            if (fVar2 < 0.0f) {
              fVar5 = 0.0f;
            }
            else {
              fVar5 = fVar2;
              if (1.0f < fVar2) {
                fVar5 = 1.0f;
              }
            }
          }
          uVar7 = uVar7 + 1;
          *pfVar1 = fVar5 * 63.0f;
        } while (uVar7 < poly->dwNumVertices);
      }
      if ((poly->dwFlags & 2) == 0) {
        rdNRaster_DrawNGonGS((int)poly,(int)mat);
        return 1;
      }
      rdNRaster_DrawNGonTGS((int)poly,(int)mat);
      return 1;
    }
    break;
  case 4:
    if (face == (ProcEntry *)0x0) {
      switch(iVar9) {
      case 0:
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdNRaster_DrawNGonLAT((int)poly,(int)mat);
            return 1;
          }
          rdNRaster_DrawNGonTLAT((int)poly,(int)mat);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdNRaster_DrawNGonMLAT((int)poly,(int)mat);
          return 1;
        }
        rdNRaster_DrawNGonMTLAT((int)poly,(int)mat);
        return 1;
      case 1:
        if (poly->flLight < 0.0f) {
          fVar2 = 0.0f;
        }
        else if (1.0f < poly->flLight) {
          fVar2 = 1.0f;
        }
        else {
          fVar2 = poly->flLight;
        }
        if (local_4 < fVar2) {
          if (poly->flLight < 0.0f) {
            local_4 = 0.0f;
          }
          else if (1.0f < poly->flLight) {
            local_4 = 1.0f;
          }
          else {
            local_4 = poly->flLight;
          }
        }
        fVar2 = local_4 * 63.0f;
        poly->flLightIndex = fVar2;
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdNRaster_DrawNGonFAT((int)poly,(int)mat,fVar2);
            return 1;
          }
          rdNRaster_DrawNGonTFAT((int)poly,(int)mat,fVar2);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdNRaster_DrawNGonMFAT((int)poly,(int)mat,fVar2);
          return 1;
        }
        rdNRaster_DrawNGonMTFAT((int)poly,(int)mat,fVar2);
        return 1;
      case 2:
        fVar2 = poly->flLight + poly->flLightIndex;
        if (fVar2 < 0.0f) {
          fVar4 = 0.0f;
        }
        else {
          fVar4 = fVar2;
          if (1.0f < fVar2) {
            fVar4 = 1.0f;
          }
        }
        if (local_4 < fVar4) {
          if (fVar2 < 0.0f) {
            local_4 = 0.0f;
          }
          else {
            local_4 = fVar2;
            if (1.0f < fVar2) {
              local_4 = 1.0f;
            }
          }
        }
        fVar2 = local_4 * 63.0f;
        poly->flLightIndex = fVar2;
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdNRaster_DrawNGonFAT((int)poly,(int)mat,fVar2);
            return 1;
          }
          rdNRaster_DrawNGonTFAT((int)poly,(int)mat,fVar2);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdNRaster_DrawNGonMFAT((int)poly,(int)mat,fVar2);
          return 1;
        }
        rdNRaster_DrawNGonMTFAT((int)poly,(int)mat,fVar2);
        return 1;
      case 3:
        uVar7 = 0;
        if (poly->dwNumVertices != 0) {
          do {
            fVar2 = poly->flLight + poly->pIntensities[uVar7];
            pfVar1 = poly->pIntensities + uVar7;
            if (fVar2 < 0.0f) {
              fVar4 = 0.0f;
            }
            else {
              fVar4 = fVar2;
              if (1.0f < fVar2) {
                fVar4 = 1.0f;
              }
            }
            fVar5 = local_4;
            if (local_4 < fVar4) {
              if (fVar2 < 0.0f) {
                fVar5 = 0.0f;
              }
              else {
                fVar5 = fVar2;
                if (1.0f < fVar2) {
                  fVar5 = 1.0f;
                }
              }
            }
            uVar7 = uVar7 + 1;
            *pfVar1 = fVar5 * 63.0f;
          } while (uVar7 < poly->dwNumVertices);
        }
        if ((**(byte **)(mat + 0x1c) & 1) != 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdNRaster_DrawNGonMGAT((int)poly,(int)mat);
            return 1;
          }
          rdNRaster_DrawNGonMTGAT((int)poly,(int)mat);
          return 1;
        }
        if ((poly->dwFlags & 2) != 0) {
          rdNRaster_DrawNGonTGAT((int)poly,(int)mat);
          return 1;
        }
        rdNRaster_DrawNGonGAT((int)poly,(int)mat);
      }
    }
    else if (face == (ProcEntry *)0x1) {
      switch(iVar9) {
      case 0:
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdNRaster_DrawNGonLIT((int)poly,(int)mat);
            return 1;
          }
          rdNRaster_DrawNGonTLIT((int)poly,(int)mat);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdNRaster_DrawNGonMLIT((int)poly,(int)mat);
          return 1;
        }
        rdNRaster_DrawNGonMTLIT((int)poly,(int)mat);
        return 1;
      case 1:
        if (poly->flLight < 0.0f) {
          fVar2 = 0.0f;
        }
        else if (1.0f < poly->flLight) {
          fVar2 = 1.0f;
        }
        else {
          fVar2 = poly->flLight;
        }
        if (local_4 < fVar2) {
          if (poly->flLight < 0.0f) {
            local_4 = 0.0f;
          }
          else if (1.0f < poly->flLight) {
            local_4 = 1.0f;
          }
          else {
            local_4 = poly->flLight;
          }
        }
        fVar2 = local_4 * 63.0f;
        poly->flLightIndex = fVar2;
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdNRaster_DrawNGonFIT((int)poly,(int)mat,fVar2);
            return 1;
          }
          rdNRaster_DrawNGonTFIT((int)poly,(int)mat,fVar2);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdNRaster_DrawNGonMFIT((int)poly,(int)mat,fVar2);
          return 1;
        }
        rdNRaster_DrawNGonMTFIT((int)poly,(int)mat,fVar2);
        return 1;
      case 2:
        fVar2 = poly->flLight + poly->flLightIndex;
        if (fVar2 < 0.0f) {
          fVar4 = 0.0f;
        }
        else {
          fVar4 = fVar2;
          if (1.0f < fVar2) {
            fVar4 = 1.0f;
          }
        }
        if (local_4 < fVar4) {
          if (fVar2 < 0.0f) {
            local_4 = 0.0f;
          }
          else {
            local_4 = fVar2;
            if (1.0f < fVar2) {
              local_4 = 1.0f;
            }
          }
        }
        fVar2 = local_4 * 63.0f;
        poly->flLightIndex = fVar2;
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdNRaster_DrawNGonFIT((int)poly,(int)mat,fVar2);
            return 1;
          }
          rdNRaster_DrawNGonTFIT((int)poly,(int)mat,fVar2);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdNRaster_DrawNGonMFIT((int)poly,(int)mat,fVar2);
          return 1;
        }
        rdNRaster_DrawNGonMTFIT((int)poly,(int)mat,fVar2);
        return 1;
      case 3:
        uVar7 = 0;
        if (poly->dwNumVertices != 0) {
          do {
            fVar2 = poly->flLight + poly->pIntensities[uVar7];
            pfVar1 = poly->pIntensities + uVar7;
            if (fVar2 < 0.0f) {
              fVar4 = 0.0f;
            }
            else {
              fVar4 = fVar2;
              if (1.0f < fVar2) {
                fVar4 = 1.0f;
              }
            }
            fVar5 = local_4;
            if (local_4 < fVar4) {
              if (fVar2 < 0.0f) {
                fVar5 = 0.0f;
              }
              else {
                fVar5 = fVar2;
                if (1.0f < fVar2) {
                  fVar5 = 1.0f;
                }
              }
            }
            uVar7 = uVar7 + 1;
            *pfVar1 = fVar5 * 63.0f;
          } while (uVar7 < poly->dwNumVertices);
        }
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdNRaster_DrawNGonGIT((int)poly,(int)mat);
            return 1;
          }
          rdNRaster_DrawNGonTGIT((int)poly,(int)mat);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdNRaster_DrawNGonMGIT((int)poly,(int)mat);
          return 1;
        }
        rdNRaster_DrawNGonMTGIT((int)poly,(int)mat);
        return 1;
      }
    }
  }
  return 1;
}
#undef local_4


/* ---- 0x00408800  rdCache_DrawNGonTFATThunk ---- */
/* Passes its stack arguments on to rdNRaster_DrawNGonTFAT and returns 1. Nothing references it
   (dead code); was FUN_00408800. */

uint __cdecl rdCache_DrawNGonTFATThunk(void)

{
  int unaff_retaddr;
  int in_stack_00000004;
  float in_stack_00000008;
  
  rdNRaster_DrawNGonTFAT(unaff_retaddr,in_stack_00000004,in_stack_00000008);
  return 1;
}

/* ---- 0x00408af0  rdCache_DrawFaceZ ---- */
/* Software path with z-buffer Original name rdCache_DrawFaceZ (the remaster's GrimFandango (Linux):
   aligned call in rdCache_Flush); was rdCache_DrawMeshZ. */

int __cdecl rdCache_DrawFaceZ(ProcEntry *face)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *pfVar1;
  rdMaterial *prVar2;
  float fVar3;
  float fVar4;
  ProcEntry *poly;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte *mat;
  float fVar10;
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  poly = face;
  iVar7 = face->nGeometryMode;
  if (g_nRdroid_curGeometryMode <= face->nGeometryMode) {
    iVar7 = g_nRdroid_curGeometryMode;
  }
  iVar8 = face->nLightingMode;
  if (g_nRdroid_curLightingMode <= face->nLightingMode) {
    iVar8 = g_nRdroid_curLightingMode;
  }
  face = (ProcEntry *)face->nTextureMode;
  if (g_nRdroid_curTextureMode <= (int)face) {
    face = (ProcEntry *)g_nRdroid_curTextureMode;
  }
  if (iVar7 == 0) {
    return 0;
  }
  prVar2 = poly->pMaterial;
  if (prVar2 == (rdMaterial *)0x0) {
    mat = (byte *)0x0;
  }
  else {
    iVar5 = poly->nCel;
    if (iVar5 == -1) {
      iVar5 = prVar2->nCurCel;
      if (iVar5 < 0) {
LAB_00408b6e:
        iVar5 = 0;
      }
      else {
        iVar9 = prVar2->nNumCels + -1;
        if (iVar9 < iVar5) {
          iVar5 = iVar9;
        }
      }
    }
    else {
      if (iVar5 < 0) goto LAB_00408b6e;
      iVar9 = prVar2->nNumCels + -1;
      if (iVar9 < iVar5) {
        iVar5 = iVar9;
      }
    }
    mat = prVar2->aCels[iVar5];
    if ((iVar7 == 4) && ((*mat & 8) == 0)) {
      iVar7 = 3;
    }
  }
  if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
    local_4 = 0.0f;
  }
  else {
    local_4 = poly->flAlpha;
  }
  switch(iVar7) {
  case 1:
    if ((-1 < iVar8) && (iVar8 < 5)) {
      rdZRaster_DrawNGonLV((int)poly,(int)mat);
      return 1;
    }
    break;
  case 2:
    if ((-1 < iVar8) && (iVar8 < 5)) {
      rdZRaster_DrawNGonLW((int)poly,(int)mat);
      return 1;
    }
    break;
  case 3:
    switch(iVar8) {
    case 0:
      if ((poly->dwFlags & 2) == 0) {
        rdZRaster_DrawNGonLS((int)poly,(int)mat);
        return 1;
      }
      rdZRaster_DrawNGonTLS((int)poly,(int)mat);
      return 1;
    case 1:
      fVar10 = 0.0f;
      poly->flLightIndex = 0.0f;
      if ((poly->dwFlags & 2) != 0) {
        rdZRaster_DrawNGonTFS((int)poly,(int)mat,0.0f);
        return 1;
      }
      break;
    case 2:
      fVar10 = poly->flLight + poly->flLightIndex;
      if (fVar10 < 0.0f) {
        fVar3 = 0.0f;
      }
      else {
        fVar3 = fVar10;
        if (1.0f < fVar10) {
          fVar3 = 1.0f;
        }
      }
      if (local_4 < fVar3) {
        if (fVar10 < 0.0f) {
          local_4 = 0.0f;
        }
        else {
          local_4 = fVar10;
          if (1.0f < fVar10) {
            local_4 = 1.0f;
          }
        }
      }
      fVar10 = local_4 * 63.0f;
      poly->flLightIndex = fVar10;
      if ((poly->dwFlags & 2) != 0) {
        rdZRaster_DrawNGonTFS((int)poly,(int)mat,fVar10);
        return 1;
      }
      break;
    case 3:
      uVar6 = 0;
      if (poly->dwNumVertices != 0) {
        do {
          fVar10 = poly->pIntensities[uVar6] + poly->flLight;
          pfVar1 = poly->pIntensities + uVar6;
          if (fVar10 < 0.0f) {
            fVar3 = 0.0f;
          }
          else {
            fVar3 = fVar10;
            if (1.0f < fVar10) {
              fVar3 = 1.0f;
            }
          }
          fVar4 = local_4;
          if (local_4 < fVar3) {
            if (fVar10 < 0.0f) {
              fVar4 = 0.0f;
            }
            else {
              fVar4 = fVar10;
              if (1.0f < fVar10) {
                fVar4 = 1.0f;
              }
            }
          }
          uVar6 = uVar6 + 1;
          *pfVar1 = fVar4 * 63.0f;
        } while (uVar6 < poly->dwNumVertices);
      }
      if ((poly->dwFlags & 2) == 0) {
        rdZRaster_DrawNGonGS((int)poly,(int)mat);
        return 1;
      }
      rdZRaster_DrawNGonTGS((int)poly,(int)mat);
      return 1;
    default:
      goto switchD_00408bad_default;
    }
    rdZRaster_DrawNGonFS((int)poly,(int)mat,fVar10);
    return 1;
  case 4:
    if (face == (ProcEntry *)0x0) {
      switch(iVar8) {
      case 0:
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdZRaster_DrawNGonLAT((int)poly,(int)mat);
            return 1;
          }
          rdZRaster_DrawNGonTLAT((int)poly,(int)mat);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdZRaster_DrawNGonMLAT((int)poly,(int)mat);
          return 1;
        }
        rdZRaster_DrawNGonMTLAT((int)poly,(int)mat);
        return 1;
      case 1:
        if (poly->flLight < 0.0f) {
          fVar10 = 0.0f;
        }
        else if (1.0f < poly->flLight) {
          fVar10 = 1.0f;
        }
        else {
          fVar10 = poly->flLight;
        }
        if (local_4 < fVar10) {
          if (poly->flLight < 0.0f) {
            local_4 = 0.0f;
          }
          else if (1.0f < poly->flLight) {
            local_4 = 1.0f;
          }
          else {
            local_4 = poly->flLight;
          }
        }
        fVar10 = local_4 * 63.0f;
        poly->flLightIndex = fVar10;
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdZRaster_DrawNGonFAT((int)poly,(int)mat,fVar10);
            return 1;
          }
          rdZRaster_DrawNGonTFAT((int)poly,(int)mat,fVar10);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdZRaster_DrawNGonMFAT((int)poly,(int)mat,fVar10);
          return 1;
        }
        rdZRaster_DrawNGonMTFAT((int)poly,(int)mat,fVar10);
        return 1;
      case 2:
        fVar10 = poly->flLight + poly->flLightIndex;
        if (fVar10 < 0.0f) {
          fVar3 = 0.0f;
        }
        else {
          fVar3 = fVar10;
          if (1.0f < fVar10) {
            fVar3 = 1.0f;
          }
        }
        if (local_4 < fVar3) {
          if (fVar10 < 0.0f) {
            local_4 = 0.0f;
          }
          else {
            local_4 = fVar10;
            if (1.0f < fVar10) {
              local_4 = 1.0f;
            }
          }
        }
        fVar10 = local_4 * 63.0f;
        poly->flLightIndex = fVar10;
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdZRaster_DrawNGonFAT((int)poly,(int)mat,fVar10);
            return 1;
          }
          rdZRaster_DrawNGonTFAT((int)poly,(int)mat,fVar10);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdZRaster_DrawNGonMFAT((int)poly,(int)mat,fVar10);
          return 1;
        }
        rdZRaster_DrawNGonMTFAT((int)poly,(int)mat,fVar10);
        return 1;
      case 3:
        uVar6 = 0;
        if (poly->dwNumVertices != 0) {
          do {
            fVar10 = poly->pIntensities[uVar6] + poly->flLight;
            pfVar1 = poly->pIntensities + uVar6;
            if (fVar10 < 0.0f) {
              fVar3 = 0.0f;
            }
            else {
              fVar3 = fVar10;
              if (1.0f < fVar10) {
                fVar3 = 1.0f;
              }
            }
            fVar4 = local_4;
            if (local_4 < fVar3) {
              if (fVar10 < 0.0f) {
                fVar4 = 0.0f;
              }
              else {
                fVar4 = fVar10;
                if (1.0f < fVar10) {
                  fVar4 = 1.0f;
                }
              }
            }
            uVar6 = uVar6 + 1;
            *pfVar1 = fVar4 * 63.0f;
          } while (uVar6 < poly->dwNumVertices);
        }
        if ((**(byte **)(mat + 0x1c) & 1) != 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdZRaster_DrawNGonMGAT((int)poly,(int)mat);
            return 1;
          }
          rdZRaster_DrawNGonMTGAT((int)poly,(int)mat);
          return 1;
        }
        if ((poly->dwFlags & 2) != 0) {
          rdZRaster_DrawNGonTGAT((int)poly,(int)mat);
          return 1;
        }
        rdZRaster_DrawNGonGAT((int)poly,(int)mat);
      }
    }
    else if (face == (ProcEntry *)0x1) {
      switch(iVar8) {
      case 0:
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdZRaster_DrawNGonLIT((int)poly,(int)mat);
            return 1;
          }
          rdZRaster_DrawNGonTLIT((int)poly,(int)mat);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdZRaster_DrawNGonMLIT((int)poly,(int)mat);
          return 1;
        }
        rdZRaster_DrawNGonMTLIT((int)poly,(int)mat);
        return 1;
      case 1:
        if (poly->flLight < 0.0f) {
          fVar10 = 0.0f;
        }
        else if (1.0f < poly->flLight) {
          fVar10 = 1.0f;
        }
        else {
          fVar10 = poly->flLight;
        }
        if (local_4 < fVar10) {
          if (poly->flLight < 0.0f) {
            local_4 = 0.0f;
          }
          else if (1.0f < poly->flLight) {
            local_4 = 1.0f;
          }
          else {
            local_4 = poly->flLight;
          }
        }
        fVar10 = local_4 * 63.0f;
        poly->flLightIndex = fVar10;
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdZRaster_DrawNGonFIT((int)poly,(int)mat,fVar10);
            return 1;
          }
          rdZRaster_DrawNGonTFIT((int)poly,(int)mat,fVar10);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdZRaster_DrawNGonMFIT((int)poly,(int)mat,fVar10);
          return 1;
        }
        rdZRaster_DrawNGonMTFIT((int)poly,(int)mat,fVar10);
        return 1;
      case 2:
        fVar10 = poly->flLight + poly->flLightIndex;
        if (fVar10 < 0.0f) {
          fVar3 = 0.0f;
        }
        else {
          fVar3 = fVar10;
          if (1.0f < fVar10) {
            fVar3 = 1.0f;
          }
        }
        if (local_4 < fVar3) {
          if (fVar10 < 0.0f) {
            local_4 = 0.0f;
          }
          else {
            local_4 = fVar10;
            if (1.0f < fVar10) {
              local_4 = 1.0f;
            }
          }
        }
        fVar10 = local_4 * 63.0f;
        poly->flLightIndex = fVar10;
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdZRaster_DrawNGonFIT((int)poly,(int)mat,fVar10);
            return 1;
          }
          rdZRaster_DrawNGonTFIT((int)poly,(int)mat,fVar10);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdZRaster_DrawNGonMFIT((int)poly,(int)mat,fVar10);
          return 1;
        }
        rdZRaster_DrawNGonMTFIT((int)poly,(int)mat,fVar10);
        return 1;
      case 3:
        uVar6 = 0;
        if (poly->dwNumVertices != 0) {
          do {
            fVar10 = poly->pIntensities[uVar6] + poly->flLight;
            pfVar1 = poly->pIntensities + uVar6;
            if (fVar10 < 0.0f) {
              fVar3 = 0.0f;
            }
            else {
              fVar3 = fVar10;
              if (1.0f < fVar10) {
                fVar3 = 1.0f;
              }
            }
            fVar4 = local_4;
            if (local_4 < fVar3) {
              if (fVar10 < 0.0f) {
                fVar4 = 0.0f;
              }
              else {
                fVar4 = fVar10;
                if (1.0f < fVar10) {
                  fVar4 = 1.0f;
                }
              }
            }
            uVar6 = uVar6 + 1;
            *pfVar1 = fVar4 * 63.0f;
          } while (uVar6 < poly->dwNumVertices);
        }
        if ((**(byte **)(mat + 0x1c) & 1) == 0) {
          if ((poly->dwFlags & 2) == 0) {
            rdZRaster_DrawNGonGIT((int)poly,(int)mat);
            return 1;
          }
          rdZRaster_DrawNGonTGIT((int)poly,(int)mat);
          return 1;
        }
        if ((poly->dwFlags & 2) == 0) {
          rdZRaster_DrawNGonMGIT((int)poly,(int)mat);
          return 1;
        }
        rdZRaster_DrawNGonMTGIT((int)poly,(int)mat);
        return 1;
      }
    }
  }
switchD_00408bad_default:
  return 1;
}
#undef local_4

