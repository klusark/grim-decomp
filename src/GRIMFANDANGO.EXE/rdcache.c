/* GRIMFANDANGO.EXE :: rdcache.c
 * functions 0x00406650 .. 0x00408af0 (14 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00406650  rdCache_BeginScene3D ---- */
void rdCache_BeginScene3D(void)

{
  if (0 < g_nRdroid3DAccel) {
    D3D_BeginScene();
    return;
  }
  return;
}

/* ---- 0x00406660  rdCache_EndScene3D ---- */
void rdCache_EndScene3D(void)

{
  if (0 < g_nRdroid3DAccel) {
    D3D_EndScene();
    return;
  }
  return;
}

/* ---- 0x00406670  rdCache_Reset ---- */
/* Empties the 1024-entry mesh list (0x78 bytes each at g_RdCacheMeshes) and the vertex/uv/colour
   pools */

void rdCache_Reset(void)

{
  g_dwRdCacheMeshCount = 0;
  UINT_007f0fbc = 0;
  UINT_007f0fc0 = 0;
  UINT_007f0fc4 = 0;
  return;
}

/* ---- 0x00406690  rdCache_ClearStats ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void rdCache_ClearStats(void)

{
  _DAT_007f0fb8 = 0;
  return;
}

/* ---- 0x004066a0  rdCache_AllocMesh ---- */
/* Returns the next free cached-mesh record, flushing first when the list or a 0x8000-entry pool is
   full */

undefined1 * rdCache_AllocMesh(void)

{
  int iVar1;
  uint uVar2;
  
  if (0x3ff < g_dwRdCacheMeshCount) {
    rdCache_Flush();
  }
  uVar2 = g_dwRdCacheMeshCount;
  if (0x8000 - UINT_007f0fbc < 0x20) {
    return (undefined1 *)0x0;
  }
  if (0x8000 - UINT_007f0fc0 < 0x20) {
    return (undefined1 *)0x0;
  }
  if (0x8000 - UINT_007f0fc4 < 0x20) {
    return (undefined1 *)0x0;
  }
  iVar1 = g_dwRdCacheMeshCount * 0x78;
  (&UINT_008ddfe0)[g_dwRdCacheMeshCount * 0x1e] = (uint)(&DAT_0062bfa8 + UINT_007f0fbc * 0xc);
  *(undefined **)(&DAT_008ddfe4 + iVar1) = &DAT_0068bfb0 + UINT_007f0fc0 * 8;
  (&UINT_008ddfe8)[uVar2 * 0x1e] = (uint)(&DAT_0060bfa8 + UINT_007f0fc4 * 4);
  (&UINT_008ddfec)[uVar2 * 0x1e] = (uint)(&DAT_0060bfa8 + UINT_007f0fc4 * 4);
  (&UINT_008ddff0)[uVar2 * 0x1e] = (uint)(&DAT_005e6fa0 + UINT_007f0fc4 * 4);
  (&UINT_008ddff4)[uVar2 * 0x1e] = (uint)(&DAT_006d0fb0 + UINT_007f0fc4 * 4);
  return &DAT_008ddfc0 + iVar1;
}

/* ---- 0x00406770  rdCache_Flush ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Sorts (sort mode 2) and draws every cached mesh with the software or 3D path chosen by the
   occlusion/zbuffer modes */

void rdCache_Flush(void)

{
  byte *pbVar1;
  uint uVar2;
  
  if (g_dwRdCacheMeshCount != 0) {
    if (g_nRdroidSortMode == 2) {
      qsort(&DAT_008ddfc0,g_dwRdCacheMeshCount,0x78,FUN_00409d20);
    }
    if (g_nRdroid3DAccel < 1) {
      if (g_nRdroidOcclusionMode == 0) {
        if (g_nRdroidZBufferMode == 0) {
          uVar2 = 0;
          pbVar1 = &DAT_008ddfc0;
          if (g_dwRdCacheMeshCount != 0) {
            do {
              if ((*pbVar1 & 1) == 0) {
                rdCache_DrawMesh(pbVar1);
              }
              else {
                ((code *)rdModel_ComputeMeshLighting)();
              }
              pbVar1 = pbVar1 + 0x78;
              uVar2 = uVar2 + 1;
            } while (uVar2 < g_dwRdCacheMeshCount);
          }
        }
        else if (g_nRdroidZBufferMode == 2) {
          uVar2 = 0;
          pbVar1 = &DAT_008ddfc0;
          if (g_dwRdCacheMeshCount != 0) {
            do {
              if ((*pbVar1 & 1) == 0) {
                rdCache_DrawMeshZ(pbVar1);
              }
              else {
                ((code *)rdModel_ComputeMeshLighting)();
              }
              pbVar1 = pbVar1 + 0x78;
              uVar2 = uVar2 + 1;
            } while (uVar2 < g_dwRdCacheMeshCount);
          }
        }
      }
      else if (g_nRdroidOcclusionMode == 1) {
        rdCanvas_InitEdgeTables();
        rdCanvas_ScanConvert();
      }
    }
    else {
      rdCache_DrawMeshList3D();
    }
    _DAT_007f0fb8 = _DAT_007f0fb8 + g_dwRdCacheMeshCount;
    rdCache_Reset();
  }
  return;
}

/* ---- 0x00406860  rdCache_AddMesh ---- */
/* Appends a mesh to the cache list and computes its screen bounds / depth */

int __cdecl rdCache_AddMesh(void *mesh,uint vertexCount,byte flags)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  float fVar5;
  float fVar6;
  uint uVar7;
  float fVar8;
  uint uVar9;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar10;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  uVar7 = g_dwRdCacheMeshCount;
  if (0x3ff < g_dwRdCacheMeshCount) {
    return 0;
  }
  iVar1 = g_dwRdCacheMeshCount * 0x78;
  pfVar4 = (float *)(&UINT_008ddfe0)[g_dwRdCacheMeshCount * 0x1e];
  *(void **)(&DAT_008ddfc0 + iVar1) = mesh;
  (&UINT_008ddfdc)[uVar7 * 0x1e] = vertexCount;
  *(uint *)(&DAT_008de034 + iVar1) = UINT_00900054;
  local_c = (uint)*pfVar4;
  fVar2 = pfVar4[1];
  *(undefined4 *)(&DAT_008de030 + iVar1) = 0;
  *(undefined4 *)(&DAT_008de02c + iVar1) = 0;
  fVar3 = pfVar4[2];
  uVar9 = 1;
  *(float *)(&DAT_008de028 + iVar1) = fVar3;
  *(float *)(&DAT_008de024 + iVar1) = fVar3;
  local_10 = (uint)fVar2;
  local_8 = local_c;
  if (1 < vertexCount) {
    do {
      fVar3 = pfVar4[3];
      fVar5 = pfVar4[4];
      fVar6 = pfVar4[5];
      fVar8 = fVar3;
      if (((float)local_8 <= fVar3) && (fVar8 = (float)local_8, (float)local_c <= fVar3)) {
        local_c = (uint)fVar3;
      }
      local_8 = (uint)fVar8;
      if (fVar2 <= fVar5) {
        if ((float)local_10 < fVar5) {
          *(uint *)(&DAT_008de030 + iVar1) = uVar9;
          local_10 = (uint)fVar5;
        }
      }
      else {
        *(uint *)(&DAT_008de02c + iVar1) = uVar9;
        fVar2 = fVar5;
      }
      if (*(float *)(&DAT_008de024 + iVar1) <= fVar6) {
        if (*(float *)(&DAT_008de028 + iVar1) < fVar6) {
          *(float *)(&DAT_008de028 + iVar1) = fVar6;
        }
      }
      else {
        *(float *)(&DAT_008de024 + iVar1) = fVar6;
      }
      uVar9 = uVar9 + 1;
      pfVar4 = pfVar4 + 3;
    } while (uVar9 < vertexCount);
  }
  if ((float)local_8 < (float)local_c) {
    if (fVar2 < (float)local_10) {
      lVar10 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      *(int *)(&DAT_008de014 + iVar1) = (int)lVar10;
      lVar10 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      *(int *)(&DAT_008de018 + iVar1) = (int)lVar10;
      lVar10 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      *(int *)(&DAT_008de01c + iVar1) = (int)lVar10;
      lVar10 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      *(int *)(&DAT_008de020 + iVar1) = (int)lVar10;
      if ((flags & 1) != 0) {
        UINT_007f0fbc = UINT_007f0fbc + vertexCount;
      }
      if ((flags & 2) != 0) {
        UINT_007f0fc0 = UINT_007f0fc0 + vertexCount;
      }
      if ((flags & 4) != 0) {
        UINT_007f0fc4 = UINT_007f0fc4 + vertexCount;
      }
      (&UINT_008de00c)[uVar7 * 0x1e] = UINT_004f5ec0;
      g_dwRdCacheMeshCount = g_dwRdCacheMeshCount + 1;
      if (*(uint *)(&DAT_008de014 + iVar1) < (uint)g_nDrawBoxMinX) {
        g_nDrawBoxMinX = *(uint *)(&DAT_008de014 + iVar1);
      }
      if ((uint)g_nDrawBoxMaxX < *(uint *)(&DAT_008de018 + iVar1)) {
        g_nDrawBoxMaxX = *(uint *)(&DAT_008de018 + iVar1);
      }
      if (*(uint *)(&DAT_008de01c + iVar1) < (uint)g_nDrawBoxMinY) {
        g_nDrawBoxMinY = *(uint *)(&DAT_008de01c + iVar1);
      }
      if ((uint)g_nDrawBoxMaxY < *(uint *)(&DAT_008de020 + iVar1)) {
        g_nDrawBoxMaxY = *(uint *)(&DAT_008de020 + iVar1);
      }
      return 1;
    }
    return 0;
  }
  return 0;
}
#undef local_10
#undef local_8
#undef local_c


/* ---- 0x00406aa0  rdCache_DrawMeshList3D ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Direct3D path: uploads the material textures (rdMaterial_EnsureTexture) and batches the cached
   meshes into execute buffers */

undefined4 rdCache_DrawMeshList3D(void)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  uint *material;
  int iVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  uint uVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  undefined4 unaff_ESI;
  undefined1 *puVar14;
  undefined4 unaff_EDI;
  uint uVar15;
  longlong lVar16;
  longlong lVar17;
  #define local_7c (*(uint *)(_frame + (0x90 - 0x7c)))
  #define local_78 (*(uint *)(_frame + (0x90 - 0x78)))
  #define local_74 (*(uint *)(_frame + (0x90 - 0x74)))
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
  #define local_20 (*(uint *)(_frame + (0x90 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x90 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x90 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x90 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x90 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x90 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x90 - 0x8)))
  
  bVar5 = false;
  bVar6 = false;
  bVar8 = false;
  bVar7 = false;
  local_4c = 0;
  local_44 = 0x33;
  if (g_nRdroidZBufferMode == 1) {
    local_44 = 0x1033;
  }
  else if (g_nRdroidZBufferMode == 2) {
    local_44 = 0x1833;
  }
  else if (g_nRdroidZBufferMode == 3) {
    local_44 = 0x833;
  }
  if (((0.0 < _DAT_0090002c) || (0.0 < _DAT_00900030)) || (0.0 < _DAT_00900034)) {
    bVar5 = true;
    bVar8 = true;
    local_20 = (uint)(_DAT_0090002c * 0.5);
  }
  if (((UINT_00900020 != 0) || (UINT_00900024 != 0)) || (UINT_00900028 != 0)) {
    bVar6 = true;
    bVar7 = true;
  }
  if (((bVar5) || (bVar6)) || (UINT_0090004c == 1)) {
    local_44 = local_44 | 0x8000;
  }
  rdCache_Begin3DBatch();
  puVar14 = &DAT_008ddfc0;
  local_64 = 0;
  if (g_dwRdCacheMeshCount == 0) {
    rdCache_Flush3DBatch();
    return 1;
  }
  do {
    uVar15 = local_28;
    if (((byte)g_dwRdroidFlags & 2) == 0) {
      local_c = 0;
    }
    else {
      local_c = *(uint *)(puVar14 + 0x40);
    }
    local_30 = local_44;
    if (UINT_00806940 <= UINT_0068bfa8 + *(int *)(puVar14 + 0x1c)) {
      rdCache_Flush3DBatch();
      rdCache_Begin3DBatch();
    }
    uVar9 = UINT_0068bfa8;
    local_8 = *(uint *)(puVar14 + 8);
    if (g_nRdroidGeometryMode <= (int)local_8) {
      local_8 = g_nRdroidGeometryMode;
    }
    local_34 = *(uint *)(puVar14 + 0xc);
    if (g_nRdroidLightingMode <= (int)local_34) {
      local_34 = g_nRdroidLightingMode;
    }
    if ((puVar14[4] & 2) == 0) {
      iVar11 = 0xff;
      local_24 = 0xff;
    }
    else {
      iVar11 = 200;
      local_30 = local_44 | 0x200;
      local_24 = 200;
    }
    if (((iVar11 != 0xff) && (*(int *)((int)g_pD3dDriver + 0x18) == 0)) &&
       (*(int *)((int)g_pD3dDriver + 0x14) == 0)) {
      local_24 = 0xff;
      local_4c = 1;
    }
    local_20 = *(uint *)(puVar14 + 0x38);
    if (local_20 != 0) {
      iVar11 = *(int *)(puVar14 + 0x3c);
      if (iVar11 == -1) {
        iVar11 = *(int *)(local_20 + 100);
        if (iVar11 < 0) {
LAB_00406cbf:
          iVar11 = 0;
        }
        else {
          iVar12 = *(int *)(local_20 + 0x60) + -1;
          if (iVar12 < iVar11) {
            iVar11 = iVar12;
          }
        }
      }
      else {
        if (iVar11 < 0) goto LAB_00406cbf;
        iVar12 = *(int *)(local_20 + 0x60) + -1;
        if (iVar12 < iVar11) {
          iVar11 = iVar12;
        }
      }
      local_2c = *(undefined4 *)(local_20 + 0x68 + iVar11 * 4);
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
          uVar15 = 0;
          local_28 = uVar15;
        }
        else if (uVar13 == 2) {
          if (_DAT_004dda94 < *(float *)(puVar14 + 100)) {
LAB_00406d8d:
            uVar15 = 1;
            local_28 = uVar15;
          }
          else {
            uVar15 = 0;
            local_28 = uVar15;
          }
        }
        else if (uVar13 == 3) {
          if (_DAT_004dda90 < *(float *)(puVar14 + 100)) {
            if (*(float *)(puVar14 + 100) <= _DAT_004dda94) goto LAB_00406d8d;
            uVar15 = 2;
            local_28 = uVar15;
          }
          else {
            uVar15 = 0;
            local_28 = uVar15;
          }
        }
        else if (uVar13 == 4) {
          if (_DAT_004dda90 < *(float *)(puVar14 + 100)) {
            if (*(float *)(puVar14 + 100) <= _DAT_004dda94) goto LAB_00406d8d;
            if (_DAT_004dda98 < *(float *)(puVar14 + 100)) {
              uVar15 = 3;
              local_28 = uVar15;
            }
            else {
              uVar15 = 2;
              local_28 = uVar15;
            }
          }
          else {
            uVar15 = 0;
            local_28 = uVar15;
          }
        }
        if (((*material & 1) != 0) && (*(int *)((int)g_pD3dDriver + 0x10) != 0)) {
          local_30 = local_30 | 0x400;
        }
        if (material[uVar15 * 0x26 + 0x29] == 0) {
          Display_SetPalette3D((void *)(*(int *)(puVar14 + 0x4c) + 0x30),0x5a);
        }
        iVar11 = rdMaterial_EnsureTexture((void *)local_20,material,uVar15,local_4c);
        if (iVar11 == 0) {
          rdCache_Flush3DBatch();
          rdCache_Begin3DBatch();
          D3D_ResetTextures();
          iVar11 = rdMaterial_EnsureTexture((void *)local_20,material,uVar15,local_4c);
          if (iVar11 == 0) {
            return 0;
          }
        }
        if (local_4c == 0) {
          iVar11 = uVar15 * 0x26 + 0xb;
        }
        else {
          iVar11 = uVar15 * 0x26 + 0xa3;
        }
        local_40 = (uint)(material + iVar11);
        D3D_ClampTextureSize
                  (*(undefined4 *)(material[uVar15 + 7] + 0xc),
                   *(undefined4 *)(material[uVar15 + 7] + 0x10),&local_38,&local_3c);
        local_7c = (uint)(float)(local_38 << ((byte)uVar15 & 0x1f));
        local_78 = (uint)(float)(local_3c << ((byte)uVar15 & 0x1f));
      }
      if (local_8 == 3) {
        fVar3 = (float)local_c;
        if (local_34 == 1) {
          if (*(float *)(puVar14 + 0x48) < 0.0) {
            fVar1 = 0.0;
          }
          else if (1.0 < *(float *)(puVar14 + 0x48)) {
            fVar1 = 1.0;
          }
          else {
            fVar1 = *(float *)(puVar14 + 0x48);
          }
          if ((float)local_c < fVar1) {
            if (*(float *)(puVar14 + 0x48) < 0.0) {
LAB_00407a17:
              fVar3 = 0.0;
            }
            else if (1.0 < *(float *)(puVar14 + 0x48)) {
LAB_00407a0f:
              fVar3 = 1.0;
            }
            else {
              fVar3 = *(float *)(puVar14 + 0x48);
            }
          }
LAB_00407a22:
          *(float *)(puVar14 + 0x44) = fVar3 * 63.0;
        }
        else {
          if (local_34 == 2) {
            fVar1 = *(float *)(puVar14 + 0x48) + *(float *)(puVar14 + 0x44);
            if (fVar1 < 0.0) {
              fVar4 = 0.0;
            }
            else {
              fVar4 = fVar1;
              if (1.0 < fVar1) {
                fVar4 = 1.0;
              }
            }
            if ((float)local_c < fVar4) {
              if (fVar1 < 0.0) goto LAB_00407a17;
              fVar3 = fVar1;
              if (1.0 < fVar1) goto LAB_00407a0f;
            }
            goto LAB_00407a22;
          }
          if (local_34 == 3) {
            if (UINT_0090004c == 1) {
              uVar15 = 0;
              if (*(int *)(puVar14 + 0x1c) != 0) {
                do {
                  fVar3 = *(float *)(puVar14 + 0x48) +
                          *(float *)(*(int *)(puVar14 + 0x28) + uVar15 * 4);
                  if (fVar3 < 0.0) {
                    fVar1 = 0.0;
                  }
                  else {
                    fVar1 = fVar3;
                    if (1.0 < fVar3) {
                      fVar1 = 1.0;
                    }
                  }
                  fVar4 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar3 < 0.0) {
                      fVar4 = 0.0;
                    }
                    else {
                      fVar4 = fVar3;
                      if (1.0 < fVar3) {
                        fVar4 = 1.0;
                      }
                    }
                  }
                  *(float *)(*(int *)(puVar14 + 0x28) + uVar15 * 4) = fVar4 * 63.0;
                  fVar3 = *(float *)(puVar14 + 0x48) +
                          *(float *)(*(int *)(puVar14 + 0x2c) + uVar15 * 4);
                  if (fVar3 < 0.0) {
                    fVar1 = 0.0;
                  }
                  else {
                    fVar1 = fVar3;
                    if (1.0 < fVar3) {
                      fVar1 = 1.0;
                    }
                  }
                  fVar4 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar3 < 0.0) {
                      fVar4 = 0.0;
                    }
                    else {
                      fVar4 = fVar3;
                      if (1.0 < fVar3) {
                        fVar4 = 1.0;
                      }
                    }
                  }
                  *(float *)(*(int *)(puVar14 + 0x2c) + uVar15 * 4) = fVar4 * 63.0;
                  fVar3 = *(float *)(*(int *)(puVar14 + 0x30) + uVar15 * 4) +
                          *(float *)(puVar14 + 0x48);
                  if (fVar3 < 0.0) {
                    fVar1 = 0.0;
                  }
                  else {
                    fVar1 = fVar3;
                    if (1.0 < fVar3) {
                      fVar1 = 1.0;
                    }
                  }
                  fVar4 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar3 < 0.0) {
                      fVar4 = 0.0;
                    }
                    else {
                      fVar4 = fVar3;
                      if (1.0 < fVar3) {
                        fVar4 = 1.0;
                      }
                    }
                  }
                  *(float *)(*(int *)(puVar14 + 0x30) + uVar15 * 4) = fVar4 * 63.0;
                  fVar3 = *(float *)(puVar14 + 0x48) +
                          *(float *)(*(int *)(puVar14 + 0x34) + uVar15 * 4);
                  iVar11 = uVar15 * 4;
                  if (fVar3 < 0.0) {
                    fVar1 = 0.0;
                  }
                  else {
                    fVar1 = fVar3;
                    if (1.0 < fVar3) {
                      fVar1 = 1.0;
                    }
                  }
                  fVar4 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar3 < 0.0) {
                      fVar4 = 0.0;
                    }
                    else {
                      fVar4 = fVar3;
                      if (1.0 < fVar3) {
                        fVar4 = 1.0;
                      }
                    }
                  }
                  uVar15 = uVar15 + 1;
                  *(float *)(*(int *)(puVar14 + 0x34) + iVar11) = fVar4 * 63.0;
                } while (uVar15 < *(uint *)(puVar14 + 0x1c));
              }
            }
            else {
              uVar15 = 0;
              if (*(int *)(puVar14 + 0x1c) != 0) {
                do {
                  fVar3 = *(float *)(puVar14 + 0x48) +
                          *(float *)(*(int *)(puVar14 + 0x28) + uVar15 * 4);
                  iVar11 = uVar15 * 4;
                  if (fVar3 < 0.0) {
                    fVar1 = 0.0;
                  }
                  else {
                    fVar1 = fVar3;
                    if (1.0 < fVar3) {
                      fVar1 = 1.0;
                    }
                  }
                  fVar4 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar3 < 0.0) {
                      fVar4 = 0.0;
                    }
                    else {
                      fVar4 = fVar3;
                      if (1.0 < fVar3) {
                        fVar4 = 1.0;
                      }
                    }
                  }
                  uVar15 = uVar15 + 1;
                  *(float *)(*(int *)(puVar14 + 0x28) + iVar11) = fVar4 * 63.0;
                } while (uVar15 < *(uint *)(puVar14 + 0x1c));
              }
            }
          }
        }
        local_8 = 0;
        if (*(int *)(puVar14 + 0x1c) != 0) {
          local_20 = local_24 << 8;
          local_24 = 0;
          do {
            iVar11 = *(int *)(puVar14 + 0x20);
            *(float *)(&DAT_006f0fb8 + UINT_0068bfa8 * 0x20) =
                 ROUND(*(float *)(local_24 + *(int *)(puVar14 + 0x20)));
            local_14 = *(uint *)(local_24 + 4 + iVar11);
            iVar11 = *(int *)(puVar14 + 0x20);
            iVar12 = UINT_0068bfa8 * 0x20;
            *(float *)(&DAT_006f0fbc + iVar12) = ROUND((float)local_14);
            if (*(float *)(local_24 + 8 + iVar11) == 0.0) {
              fVar3 = 0.0;
            }
            else {
              local_14 = 0xffffffff;
              if (UINT_00900534 == 0x10) {
                local_14 = 1;
              }
              fVar3 = 1.0 / ((float)(int)local_14 + *(float *)(local_24 + 8 + iVar11));
            }
            *(float *)(&DAT_006f0fc0 + iVar12) = fVar3;
            *(float *)(&DAT_006f0fc4 + iVar12) = fVar3 * 0.03125;
            *(undefined4 *)(&DAT_006f0fcc + iVar12) = 0;
            if (local_34 == 0) {
              iVar11 = *(int *)(local_2c + 4) * 3 + *(int *)(puVar14 + 0x4c);
              local_1c = (uint)*(byte *)(iVar11 + 0x30);
              local_10 = (uint)*(byte *)(iVar11 + 0x31);
              local_18 = (uint)*(byte *)(iVar11 + 0x32);
            }
            else if (local_34 == 3) {
              if (UINT_0090004c != 1) {
                iVar11 = *(int *)(local_2c + 4) * 3 + *(int *)(puVar14 + 0x4c);
                local_14 = (uint)*(byte *)(iVar11 + 0x30);
                lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
                local_1c = (uint)lVar16;
                local_14 = (uint)*(byte *)(iVar11 + 0x31);
                lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
                local_10 = (uint)lVar16;
                local_14 = (uint)*(byte *)(iVar11 + 0x32);
                lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
                local_18 = (uint)lVar16;
              }
            }
            else {
              iVar11 = *(int *)(local_2c + 4) * 3;
              local_14 = (uint)*(byte *)(iVar11 + 0x30 + *(int *)(puVar14 + 0x4c));
              iVar11 = iVar11 + *(int *)(puVar14 + 0x4c);
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_1c = (uint)lVar16;
              local_14 = (uint)*(byte *)(iVar11 + 0x31);
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_10 = (uint)lVar16;
              local_14 = (uint)*(byte *)(iVar11 + 0x32);
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_18 = (uint)lVar16;
            }
            uVar15 = local_10;
            if (*(uint *)(puVar14 + 0x4c) != UINT_004f5ec4) {
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_1c = (uint)lVar16 & 0xff;
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              uVar15 = (uint)lVar16 & 0xff;
              local_10 = uVar15;
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_18 = (uint)lVar16 & 0xff;
            }
            local_30 = local_30 | 0x8000;
            if (bVar7) {
              if (UINT_00900020 == 0) {
                local_1c = 0;
              }
              if (UINT_00900024 == 0) {
                uVar15 = 0;
                local_10 = 0;
              }
              if (UINT_00900028 == 0) {
                local_18 = 0;
              }
            }
            if (bVar8) {
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_1c = local_1c + (int)lVar16;
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              uVar15 = uVar15 + (int)lVar16;
              local_10 = uVar15;
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_18 = local_18 + (int)lVar16;
            }
            if (_DAT_00900044 < 1.0) {
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_1c = (uint)lVar16;
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              uVar15 = (uint)lVar16;
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_18 = (uint)lVar16;
            }
            if ((int)local_1c < 0) {
              local_1c = 0;
            }
            else if (0xff < (int)local_1c) {
              local_1c = 0xff;
            }
            local_1c = local_1c & 0xff;
            if ((int)uVar15 < 0) {
              uVar15 = 0;
            }
            else if (0xff < (int)uVar15) {
              uVar15 = 0xff;
            }
            local_10 = uVar15 & 0xff;
            if ((int)local_18 < 0) {
              local_18 = 0;
            }
            else if (0xff < (int)local_18) {
              local_18 = 0xff;
            }
            local_18 = local_18 & 0xff;
            UINT_0068bfa8 = UINT_0068bfa8 + 1;
            *(uint *)(&DAT_006f0fc8 + iVar12) =
                 ((local_1c | local_20) << 8 | local_10) << 8 | local_18;
            uVar15 = *(uint *)(puVar14 + 0x1c);
            *(undefined4 *)(&DAT_006f0fd0 + iVar12) = 0;
            *(undefined4 *)(&DAT_006f0fd4 + iVar12) = 0;
            local_8 = local_8 + 1;
            local_24 = local_24 + 0xc;
          } while (local_8 < uVar15);
        }
        uVar15 = *(uint *)(puVar14 + 0x1c);
        if (uVar15 < 4) {
          iVar11 = UINT_006f0fb0 * 0x14;
          *(uint *)(&DAT_00606fa8 + iVar11) = uVar9;
          *(uint *)(&DAT_00606fa4 + iVar11) = uVar9 + 1;
          *(uint *)(&DAT_00606fa0 + iVar11) = uVar9 + 2;
          UINT_006f0fb0 = UINT_006f0fb0 + 1;
          *(uint *)(&DAT_00606fac + iVar11) = local_30;
          *(undefined4 *)(&DAT_00606fb0 + iVar11) = 0;
        }
        else {
          local_20 = uVar15 - 2;
          uVar13 = 0;
          local_34 = uVar15 - 1;
          uVar15 = 0;
          local_8 = 1;
          if (0 < (int)local_20) {
            piVar10 = (int *)(&DAT_00606fa4 + UINT_006f0fb0 * 0x14);
            UINT_006f0fb0 = UINT_006f0fb0 + local_20;
            do {
              piVar10[1] = uVar13 + uVar9;
              *piVar10 = local_8 + uVar9;
              piVar10[-1] = uVar9 + local_34;
              piVar10[2] = local_30;
              piVar10[3] = 0;
              if ((~uVar15 & 1) == 0) {
                uVar13 = local_34;
                local_34 = local_34 - 1;
              }
              else {
                uVar13 = local_8;
                local_8 = local_8 + 1;
              }
              piVar10 = piVar10 + 5;
              uVar15 = uVar15 + 1;
            } while ((int)uVar15 < (int)local_20);
          }
        }
      }
      else {
        if (local_8 != 4) goto LAB_00407e89;
        fVar3 = (float)local_c;
        if (local_34 == 1) {
          if (*(float *)(puVar14 + 0x48) < 0.0) {
            fVar1 = 0.0;
          }
          else if (1.0 < *(float *)(puVar14 + 0x48)) {
            fVar1 = 1.0;
          }
          else {
            fVar1 = *(float *)(puVar14 + 0x48);
          }
          if ((float)local_c < fVar1) {
            if (*(float *)(puVar14 + 0x48) < 0.0) {
LAB_004071ef:
              fVar3 = 0.0;
            }
            else if (1.0 < *(float *)(puVar14 + 0x48)) {
LAB_004071e7:
              fVar3 = 1.0;
            }
            else {
              fVar3 = *(float *)(puVar14 + 0x48);
            }
          }
LAB_004071fa:
          *(float *)(puVar14 + 0x44) = fVar3 * 255.0;
        }
        else {
          if (local_34 == 2) {
            fVar1 = *(float *)(puVar14 + 0x48) + *(float *)(puVar14 + 0x44);
            if (fVar1 < 0.0) {
              fVar4 = 0.0;
            }
            else {
              fVar4 = fVar1;
              if (1.0 < fVar1) {
                fVar4 = 1.0;
              }
            }
            if ((float)local_c < fVar4) {
              if (fVar1 < 0.0) goto LAB_004071ef;
              fVar3 = fVar1;
              if (1.0 < fVar1) goto LAB_004071e7;
            }
            goto LAB_004071fa;
          }
          if (local_34 == 3) {
            if (UINT_0090004c == 1) {
              uVar15 = 0;
              if (*(int *)(puVar14 + 0x1c) != 0) {
                do {
                  fVar3 = *(float *)(puVar14 + 0x48) +
                          *(float *)(*(int *)(puVar14 + 0x2c) + uVar15 * 4);
                  if (fVar3 < 0.0) {
                    fVar1 = 0.0;
                  }
                  else {
                    fVar1 = fVar3;
                    if (1.0 < fVar3) {
                      fVar1 = 1.0;
                    }
                  }
                  fVar4 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar3 < 0.0) {
                      fVar4 = 0.0;
                    }
                    else {
                      fVar4 = fVar3;
                      if (1.0 < fVar3) {
                        fVar4 = 1.0;
                      }
                    }
                  }
                  *(float *)(*(int *)(puVar14 + 0x2c) + uVar15 * 4) = fVar4 * 255.0;
                  fVar3 = *(float *)(*(int *)(puVar14 + 0x30) + uVar15 * 4) +
                          *(float *)(puVar14 + 0x48);
                  if (fVar3 < 0.0) {
                    fVar1 = 0.0;
                  }
                  else {
                    fVar1 = fVar3;
                    if (1.0 < fVar3) {
                      fVar1 = 1.0;
                    }
                  }
                  fVar4 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar3 < 0.0) {
                      fVar4 = 0.0;
                    }
                    else {
                      fVar4 = fVar3;
                      if (1.0 < fVar3) {
                        fVar4 = 1.0;
                      }
                    }
                  }
                  *(float *)(*(int *)(puVar14 + 0x30) + uVar15 * 4) = fVar4 * 255.0;
                  fVar3 = *(float *)(puVar14 + 0x48) +
                          *(float *)(*(int *)(puVar14 + 0x34) + uVar15 * 4);
                  iVar11 = uVar15 * 4;
                  if (fVar3 < 0.0) {
                    fVar1 = 0.0;
                  }
                  else {
                    fVar1 = fVar3;
                    if (1.0 < fVar3) {
                      fVar1 = 1.0;
                    }
                  }
                  fVar4 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar3 < 0.0) {
                      fVar4 = 0.0;
                    }
                    else {
                      fVar4 = fVar3;
                      if (1.0 < fVar3) {
                        fVar4 = 1.0;
                      }
                    }
                  }
                  uVar15 = uVar15 + 1;
                  *(float *)(*(int *)(puVar14 + 0x34) + iVar11) = fVar4 * 255.0;
                } while (uVar15 < *(uint *)(puVar14 + 0x1c));
              }
            }
            else {
              uVar15 = 0;
              if (*(int *)(puVar14 + 0x1c) != 0) {
                do {
                  fVar3 = *(float *)(puVar14 + 0x48) +
                          *(float *)(*(int *)(puVar14 + 0x28) + uVar15 * 4);
                  iVar11 = uVar15 * 4;
                  if (fVar3 < 0.0) {
                    fVar1 = 0.0;
                  }
                  else {
                    fVar1 = fVar3;
                    if (1.0 < fVar3) {
                      fVar1 = 1.0;
                    }
                  }
                  fVar4 = (float)local_c;
                  if ((float)local_c < fVar1) {
                    if (fVar3 < 0.0) {
                      fVar4 = 0.0;
                    }
                    else {
                      fVar4 = fVar3;
                      if (1.0 < fVar3) {
                        fVar4 = 1.0;
                      }
                    }
                  }
                  uVar15 = uVar15 + 1;
                  *(float *)(*(int *)(puVar14 + 0x28) + iVar11) = fVar4 * 255.0;
                } while (uVar15 < *(uint *)(puVar14 + 0x1c));
              }
            }
          }
        }
        local_8 = 0;
        if (*(int *)(puVar14 + 0x1c) != 0) {
          local_2c = *(uint *)(puVar14 + 0x20);
          local_20 = local_24 << 8;
          local_24 = 0;
          do {
            iVar11 = *(int *)(puVar14 + 0x20);
            *(float *)(&DAT_006f0fb8 + UINT_0068bfa8 * 0x20) =
                 ROUND(*(float *)(local_24 + local_2c));
            uVar13 = UINT_0068bfa8;
            uVar15 = *(uint *)(puVar14 + 0x20);
            *(float *)(&DAT_006f0fbc + UINT_0068bfa8 * 0x20) =
                 ROUND(*(float *)(local_24 + 4 + iVar11));
            if (*(float *)(local_24 + 8 + uVar15) == 0.0) {
              fVar3 = 0.0;
              local_2c = uVar15;
            }
            else {
              local_2c = 0xffffffff;
              if (UINT_00900534 == 0x10) {
                local_2c = 1;
              }
              *(float *)(local_24 + 8 + uVar15) =
                   (float)(int)local_2c + *(float *)(local_24 + 8 + uVar15);
              fVar3 = 1.0 / *(float *)(local_24 + 8 + *(uint *)(puVar14 + 0x20));
              uVar13 = UINT_0068bfa8;
              local_2c = *(uint *)(puVar14 + 0x20);
            }
            local_14 = uVar13 * 0x20;
            *(float *)(&DAT_006f0fc0 + local_14) = fVar3;
            *(float *)(&DAT_006f0fc4 + local_14) = fVar3;
            *(undefined4 *)(&DAT_006f0fcc + local_14) = 0;
            if (local_34 == 0) {
              local_10 = 0xff;
              uVar15 = local_10;
              local_1c = local_10;
              local_18 = local_10;
            }
            else if (local_34 == 3) {
              if (UINT_0090004c == 1) {
                lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
                local_1c = (uint)lVar16;
                lVar17 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
                local_10 = (uint)lVar17;
                lVar17 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
                local_18 = (uint)lVar17;
                uVar15 = (uint)lVar16;
              }
              else {
                lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
                local_1c = (uint)lVar16;
                uVar15 = local_1c;
                local_18 = local_1c;
                local_10 = local_1c;
              }
            }
            else {
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_1c = (uint)lVar16;
              uVar15 = local_1c;
              local_18 = local_1c;
              local_10 = local_1c;
            }
            if (*(uint *)(puVar14 + 0x4c) != UINT_004f5ec4) {
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              uVar15 = (uint)lVar16 & 0xff;
              local_1c = uVar15;
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_10 = (uint)lVar16 & 0xff;
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_18 = (uint)lVar16 & 0xff;
              local_30 = local_30 | 0x8000;
            }
            if (bVar7) {
              if (UINT_00900020 == 0) {
                uVar15 = 0;
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
            if (bVar8) {
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              uVar15 = uVar15 + (int)lVar16;
              local_1c = uVar15;
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_10 = local_10 + (int)lVar16;
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_18 = uVar13 + (int)lVar16;
            }
            if (_DAT_00900044 < 1.0) {
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              uVar15 = (uint)lVar16;
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_10 = (uint)lVar16;
              lVar16 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
              local_18 = (uint)lVar16;
            }
            if ((int)uVar15 < 0) {
              uVar15 = 0;
            }
            else if (0xff < (int)uVar15) {
              uVar15 = 0xff;
            }
            local_1c = uVar15 & 0xff;
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
            iVar2 = *(int *)(puVar14 + 0x24);
            *(uint *)(&DAT_006f0fc8 + local_14) =
                 ((local_1c | local_20) << 8 | local_10) << 8 | local_18;
            iVar11 = local_8 * 8;
            iVar12 = local_8 * 8;
            UINT_0068bfa8 = UINT_0068bfa8 + 1;
            local_8 = local_8 + 1;
            *(float *)(&DAT_006f0fd0 + local_14) = *(float *)(iVar2 + iVar11) / (float)local_7c;
            uVar15 = *(uint *)(puVar14 + 0x1c);
            *(float *)(&DAT_006f0fd4 + local_14) = *(float *)(iVar2 + iVar12 + 4) / (float)local_78;
            local_24 = local_24 + 0xc;
          } while (local_8 < uVar15);
        }
        uVar15 = *(uint *)(puVar14 + 0x1c);
        if (uVar15 < 4) {
          iVar11 = UINT_0060bfa0 * 0x14;
          *(uint *)(&DAT_006cbfb8 + iVar11) = uVar9;
          *(uint *)(&DAT_006cbfb4 + iVar11) = uVar9 + 1;
          *(uint *)(&DAT_006cbfb0 + iVar11) = uVar9 + 2;
          UINT_0060bfa0 = UINT_0060bfa0 + 1;
          *(uint *)(&DAT_006cbfbc + iVar11) = local_30;
          *(uint *)(&DAT_006cbfc0 + iVar11) = local_40;
        }
        else {
          local_20 = uVar15 - 2;
          uVar13 = 0;
          local_34 = uVar15 - 1;
          uVar15 = 0;
          local_8 = 1;
          if (0 < (int)local_20) {
            piVar10 = (int *)(&DAT_006cbfb4 + UINT_0060bfa0 * 0x14);
            UINT_0060bfa0 = UINT_0060bfa0 + local_20;
            do {
              piVar10[1] = uVar13 + uVar9;
              *piVar10 = local_8 + uVar9;
              piVar10[-1] = uVar9 + local_34;
              piVar10[2] = local_30;
              piVar10[3] = local_40;
              if ((~uVar15 & 1) == 0) {
                uVar13 = local_34;
                local_34 = local_34 - 1;
              }
              else {
                uVar13 = local_8;
                local_8 = local_8 + 1;
              }
              piVar10 = piVar10 + 5;
              uVar15 = uVar15 + 1;
            } while ((int)uVar15 < (int)local_20);
          }
        }
      }
    }
LAB_00407e89:
    puVar14 = puVar14 + 0x78;
    local_64 = local_64 + 1;
    if (g_dwRdCacheMeshCount <= local_64) {
      rdCache_Flush3DBatch();
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
#undef local_74
#undef local_78
#undef local_7c
#undef local_8
#undef local_c


/* ---- 0x00407ed0  rdCache_Begin3DBatch ---- */
void rdCache_Begin3DBatch(void)

{
  D3D_BeginExecuteBuffer();
  UINT_0060bfa0 = 0;
  UINT_006f0fb0 = 0;
  UINT_0068bfa8 = 0;
  return;
}

/* ---- 0x00407ef0  rdCache_Flush3DBatch ---- */
void rdCache_Flush3DBatch(void)

{
  int iVar1;
  
  if (UINT_0068bfa8 != 0) {
    iVar1 = D3D_AddVertices(&DAT_006f0fb8,UINT_0068bfa8);
    if (iVar1 == 0) {
      D3D_ExecuteBuffer();
      D3D_AddVertices(&DAT_006f0fb8,UINT_0068bfa8);
    }
    D3D_BeginInstructions();
    if (g_nRdroidZBufferMode == 2) {
      qsort(&DAT_006cbfb0,UINT_0060bfa0,0x14,FUN_00407f90);
    }
    if (UINT_006f0fb0 != 0) {
      D3D_AddTriangles(&DAT_00606fa0,UINT_006f0fb0);
    }
    if (UINT_0060bfa0 != 0) {
      D3D_AddTriangles(&DAT_006cbfb0,UINT_0060bfa0);
    }
    D3D_ExecuteBuffer();
    return;
  }
  return;
}

/* ---- 0x00407f90  FUN_00407f90 ---- */
int FUN_00407f90(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x7c);
  if (iVar1 == *(int *)(*(int *)(param_2 + 0x10) + 0x7c)) {
    return (*(int *)(param_1 + 0x10) - *(int *)(param_2 + 0x10)) / 0x98;
  }
  return (-(uint)(iVar1 != 0) & 2) - 1;
}

/* ---- 0x00407fd0  rdCache_DrawMesh ---- */
/* Software path without z-buffer: clamps the mesh modes to the global limits and calls the
   rasterizer entry for each face */

int __cdecl rdCache_DrawMesh(void *mesh)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  void *pvVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pvVar5 = mesh;
  iVar8 = *(int *)((int)mesh + 8);
  if (g_nRdroidGeometryMode <= *(int *)((int)mesh + 8)) {
    iVar8 = g_nRdroidGeometryMode;
  }
  iVar9 = *(int *)((int)mesh + 0xc);
  if (g_nRdroidLightingMode <= *(int *)((int)mesh + 0xc)) {
    iVar9 = g_nRdroidLightingMode;
  }
  mesh = *(void **)((int)mesh + 0x10);
  if (g_nRdroidTextureMode <= (int)mesh) {
    mesh = (void *)g_nRdroidTextureMode;
  }
  if (iVar8 == 0) {
    return 0;
  }
  iVar2 = *(int *)((int)pvVar5 + 0x38);
  if (iVar2 == 0) {
    pbVar11 = (byte *)0x0;
    goto LAB_00408067;
  }
  iVar6 = *(int *)((int)pvVar5 + 0x3c);
  if (iVar6 == -1) {
    iVar6 = *(int *)(iVar2 + 100);
    if (iVar6 < 0) {
LAB_0040804e:
      iVar6 = 0;
    }
    else {
      iVar10 = *(int *)(iVar2 + 0x60) + -1;
      if (iVar10 < iVar6) {
        iVar6 = iVar10;
      }
    }
  }
  else {
    if (iVar6 < 0) goto LAB_0040804e;
    iVar10 = *(int *)(iVar2 + 0x60) + -1;
    if (iVar10 < iVar6) {
      iVar6 = iVar10;
    }
  }
  pbVar11 = *(byte **)(iVar2 + 0x68 + iVar6 * 4);
  if ((iVar8 == 4) && ((*pbVar11 & 8) == 0)) {
    iVar8 = 3;
  }
LAB_00408067:
  if (((byte)g_dwRdroidFlags & 2) == 0) {
    local_4 = 0;
  }
  else {
    local_4 = *(uint *)((int)pvVar5 + 0x40);
  }
  switch(iVar8) {
  case 1:
    if ((-1 < iVar9) && (iVar9 < 5)) {
      rdRaster_DrawPoints(pvVar5,pbVar11);
      return 1;
    }
    break;
  case 2:
    if ((-1 < iVar9) && (iVar9 < 5)) {
      rdRaster_DrawWireframe(pvVar5,pbVar11);
      return 1;
    }
    break;
  case 3:
    switch(iVar9) {
    case 0:
      if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
        rdRaster_Draw16_FlatLit(pvVar5,pbVar11);
        return 1;
      }
      ((code *)rdRaster_Draw16_TexLit)();
      return 1;
    case 1:
      if (*(float *)((int)pvVar5 + 0x48) < 0.0) {
        fVar1 = 0.0;
      }
      else if (1.0 < *(float *)((int)pvVar5 + 0x48)) {
        fVar1 = 1.0;
      }
      else {
        fVar1 = *(float *)((int)pvVar5 + 0x48);
      }
      if ((float)local_4 < fVar1) {
        if (*(float *)((int)pvVar5 + 0x48) < 0.0) {
          local_4 = 0;
        }
        else if (1.0 < *(float *)((int)pvVar5 + 0x48)) {
          local_4 = 0x3f800000;
        }
        else {
          local_4 = *(uint *)((int)pvVar5 + 0x48);
        }
      }
      fVar1 = (float)local_4 * 63.0;
      *(float *)((int)pvVar5 + 0x44) = fVar1;
      if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
        rdRaster_Draw16_FlatLit_2(pvVar5,pbVar11,fVar1);
        return 1;
      }
      rdRaster_Draw16_TexLit_2(pvVar5,pbVar11,fVar1);
      return 1;
    case 2:
      fVar1 = *(float *)((int)pvVar5 + 0x48) + *(float *)((int)pvVar5 + 0x44);
      if (fVar1 < 0.0) {
        fVar3 = 0.0;
      }
      else {
        fVar3 = fVar1;
        if (1.0 < fVar1) {
          fVar3 = 1.0;
        }
      }
      if ((float)local_4 < fVar3) {
        if (fVar1 < 0.0) {
          local_4 = (uint)0.0;
        }
        else {
          local_4 = (uint)fVar1;
          if (1.0 < fVar1) {
            local_4 = (uint)1.0;
          }
        }
      }
      fVar1 = (float)local_4 * 63.0;
      *(float *)((int)pvVar5 + 0x44) = fVar1;
      if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
        rdRaster_Draw16_FlatLit_2(pvVar5,pbVar11,fVar1);
        return 1;
      }
      rdRaster_Draw16_TexLit_2(pvVar5,pbVar11,fVar1);
      return 1;
    case 3:
      uVar7 = 0;
      if (*(int *)((int)pvVar5 + 0x1c) != 0) {
        do {
          fVar1 = *(float *)((int)pvVar5 + 0x48) +
                  *(float *)(*(int *)((int)pvVar5 + 0x28) + uVar7 * 4);
          iVar8 = uVar7 * 4;
          if (fVar1 < 0.0) {
            fVar3 = 0.0;
          }
          else {
            fVar3 = fVar1;
            if (1.0 < fVar1) {
              fVar3 = 1.0;
            }
          }
          fVar4 = (float)local_4;
          if ((float)local_4 < fVar3) {
            if (fVar1 < 0.0) {
              fVar4 = 0.0;
            }
            else {
              fVar4 = fVar1;
              if (1.0 < fVar1) {
                fVar4 = 1.0;
              }
            }
          }
          uVar7 = uVar7 + 1;
          *(float *)(*(int *)((int)pvVar5 + 0x28) + iVar8) = fVar4 * 63.0;
        } while (uVar7 < *(uint *)((int)pvVar5 + 0x1c));
      }
      if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
        rdRaster_Draw_FlatLit(pvVar5,pbVar11);
        return 1;
      }
      ((code *)rdRaster_Draw16_TexLit_3)();
      return 1;
    }
    break;
  case 4:
    if (mesh == (void *)0x0) {
      switch(iVar9) {
      case 0:
        if ((**(byte **)(pbVar11 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
            rdRaster_Draw16_TexLit_4(pvVar5,pbVar11);
            return 1;
          }
          ((code *)rdRaster_Draw16_TexLit_5)();
          return 1;
        }
        if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
          rdRaster_Draw16_TexLitKey(pvVar5,pbVar11);
          return 1;
        }
        ((code *)rdRaster_Draw16_TexLitKey_2)();
        return 1;
      case 1:
        if (*(float *)((int)pvVar5 + 0x48) < 0.0) {
          fVar1 = 0.0;
        }
        else if (1.0 < *(float *)((int)pvVar5 + 0x48)) {
          fVar1 = 1.0;
        }
        else {
          fVar1 = *(float *)((int)pvVar5 + 0x48);
        }
        if ((float)local_4 < fVar1) {
          if (*(float *)((int)pvVar5 + 0x48) < 0.0) {
            local_4 = 0;
          }
          else if (1.0 < *(float *)((int)pvVar5 + 0x48)) {
            local_4 = 0x3f800000;
          }
          else {
            local_4 = *(uint *)((int)pvVar5 + 0x48);
          }
        }
        fVar1 = (float)local_4 * 63.0;
        *(float *)((int)pvVar5 + 0x44) = fVar1;
        if ((**(byte **)(pbVar11 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_2(pvVar5,pbVar11,fVar1);
            return 1;
          }
          rdRaster_Draw16_TexLit_6(pvVar5,pbVar11,fVar1);
          return 1;
        }
        if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKey(pvVar5,pbVar11,fVar1);
          return 1;
        }
        rdRaster_Draw_TexLitKey_2(pvVar5,pbVar11,fVar1);
        return 1;
      case 2:
        fVar1 = *(float *)((int)pvVar5 + 0x48) + *(float *)((int)pvVar5 + 0x44);
        if (fVar1 < 0.0) {
          fVar3 = 0.0;
        }
        else {
          fVar3 = fVar1;
          if (1.0 < fVar1) {
            fVar3 = 1.0;
          }
        }
        if ((float)local_4 < fVar3) {
          if (fVar1 < 0.0) {
            local_4 = (uint)0.0;
          }
          else {
            local_4 = (uint)fVar1;
            if (1.0 < fVar1) {
              local_4 = (uint)1.0;
            }
          }
        }
        fVar1 = (float)local_4 * 63.0;
        *(float *)((int)pvVar5 + 0x44) = fVar1;
        if ((**(byte **)(pbVar11 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_2(pvVar5,pbVar11,fVar1);
            return 1;
          }
          rdRaster_Draw16_TexLit_6(pvVar5,pbVar11,fVar1);
          return 1;
        }
        if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKey(pvVar5,pbVar11,fVar1);
          return 1;
        }
        rdRaster_Draw_TexLitKey_2(pvVar5,pbVar11,fVar1);
        return 1;
      case 3:
        uVar7 = 0;
        if (*(int *)((int)pvVar5 + 0x1c) != 0) {
          do {
            fVar1 = *(float *)((int)pvVar5 + 0x48) +
                    *(float *)(*(int *)((int)pvVar5 + 0x28) + uVar7 * 4);
            iVar8 = uVar7 * 4;
            if (fVar1 < 0.0) {
              fVar3 = 0.0;
            }
            else {
              fVar3 = fVar1;
              if (1.0 < fVar1) {
                fVar3 = 1.0;
              }
            }
            fVar4 = (float)local_4;
            if ((float)local_4 < fVar3) {
              if (fVar1 < 0.0) {
                fVar4 = 0.0;
              }
              else {
                fVar4 = fVar1;
                if (1.0 < fVar1) {
                  fVar4 = 1.0;
                }
              }
            }
            uVar7 = uVar7 + 1;
            *(float *)(*(int *)((int)pvVar5 + 0x28) + iVar8) = fVar4 * 63.0;
          } while (uVar7 < *(uint *)((int)pvVar5 + 0x1c));
        }
        if ((**(byte **)(pbVar11 + 0x1c) & 1) != 0) {
          if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
            rdRaster_Draw_TexLitKey_3(pvVar5,pbVar11);
            return 1;
          }
          ((code *)rdRaster_Draw16_TexLitKey_3)();
          return 1;
        }
        if ((*(byte *)((int)pvVar5 + 4) & 2) != 0) {
          ((code *)rdRaster_Draw16_TexLit_7)();
          return 1;
        }
        rdRaster_Draw_FlatLit_3(pvVar5,pbVar11);
      }
    }
    else if (mesh == (void *)0x1) {
      switch(iVar9) {
      case 0:
        if ((**(byte **)(pbVar11 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_4(pvVar5,pbVar11);
            return 1;
          }
          ((code *)rdRaster_Draw16_TexLit_8)();
          return 1;
        }
        if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
          rdRaster_Draw16_TexLitKey_4(pvVar5,pbVar11);
          return 1;
        }
        ((code *)rdRaster_Draw16_TexLitKey_5)();
        return 1;
      case 1:
        if (*(float *)((int)pvVar5 + 0x48) < 0.0) {
          fVar1 = 0.0;
        }
        else if (1.0 < *(float *)((int)pvVar5 + 0x48)) {
          fVar1 = 1.0;
        }
        else {
          fVar1 = *(float *)((int)pvVar5 + 0x48);
        }
        if ((float)local_4 < fVar1) {
          if (*(float *)((int)pvVar5 + 0x48) < 0.0) {
            local_4 = 0;
          }
          else if (1.0 < *(float *)((int)pvVar5 + 0x48)) {
            local_4 = 0x3f800000;
          }
          else {
            local_4 = *(uint *)((int)pvVar5 + 0x48);
          }
        }
        fVar1 = (float)local_4 * 63.0;
        *(float *)((int)pvVar5 + 0x44) = fVar1;
        if ((**(byte **)(pbVar11 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_5(pvVar5,pbVar11,fVar1);
            return 1;
          }
          rdRaster_Draw16_TexLit_9(pvVar5,pbVar11,fVar1);
          return 1;
        }
        if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKey_4(pvVar5,pbVar11,fVar1);
          return 1;
        }
        rdRaster_Draw16_TexLitKey_6(pvVar5,pbVar11,fVar1);
        return 1;
      case 2:
        fVar1 = *(float *)((int)pvVar5 + 0x48) + *(float *)((int)pvVar5 + 0x44);
        if (fVar1 < 0.0) {
          fVar3 = 0.0;
        }
        else {
          fVar3 = fVar1;
          if (1.0 < fVar1) {
            fVar3 = 1.0;
          }
        }
        if ((float)local_4 < fVar3) {
          if (fVar1 < 0.0) {
            local_4 = (uint)0.0;
          }
          else {
            local_4 = (uint)fVar1;
            if (1.0 < fVar1) {
              local_4 = (uint)1.0;
            }
          }
        }
        fVar1 = (float)local_4 * 63.0;
        *(float *)((int)pvVar5 + 0x44) = fVar1;
        if ((**(byte **)(pbVar11 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_5(pvVar5,pbVar11,fVar1);
            return 1;
          }
          rdRaster_Draw16_TexLit_9(pvVar5,pbVar11,fVar1);
          return 1;
        }
        if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKey_4(pvVar5,pbVar11,fVar1);
          return 1;
        }
        rdRaster_Draw16_TexLitKey_6(pvVar5,pbVar11,fVar1);
        return 1;
      case 3:
        uVar7 = 0;
        if (*(int *)((int)pvVar5 + 0x1c) != 0) {
          do {
            fVar1 = *(float *)((int)pvVar5 + 0x48) +
                    *(float *)(*(int *)((int)pvVar5 + 0x28) + uVar7 * 4);
            iVar8 = uVar7 * 4;
            if (fVar1 < 0.0) {
              fVar3 = 0.0;
            }
            else {
              fVar3 = fVar1;
              if (1.0 < fVar1) {
                fVar3 = 1.0;
              }
            }
            fVar4 = (float)local_4;
            if ((float)local_4 < fVar3) {
              if (fVar1 < 0.0) {
                fVar4 = 0.0;
              }
              else {
                fVar4 = fVar1;
                if (1.0 < fVar1) {
                  fVar4 = 1.0;
                }
              }
            }
            uVar7 = uVar7 + 1;
            *(float *)(*(int *)((int)pvVar5 + 0x28) + iVar8) = fVar4 * 63.0;
          } while (uVar7 < *(uint *)((int)pvVar5 + 0x1c));
        }
        if ((**(byte **)(pbVar11 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_6(pvVar5,pbVar11);
            return 1;
          }
          ((code *)rdRaster_Draw16_TexLit_10)();
          return 1;
        }
        if ((*(byte *)((int)pvVar5 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKey_5(pvVar5,pbVar11);
          return 1;
        }
        ((code *)rdRaster_Draw16_TexLitKey_7)();
        return 1;
      }
    }
  }
  return 1;
}
#undef local_4


/* ---- 0x00408800  FUN_00408800 ---- */
undefined4 FUN_00408800(void)

{
  ((code *)rdRaster_Draw16_TexLit_6)();
  return 1;
}

/* ---- 0x00408af0  rdCache_DrawMeshZ ---- */
/* Software path with z-buffer */

int __cdecl rdCache_DrawMeshZ(void *mesh)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float fVar3;
  void *pvVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  float fVar11;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pvVar4 = mesh;
  iVar7 = *(int *)((int)mesh + 8);
  if (g_nRdroidGeometryMode <= *(int *)((int)mesh + 8)) {
    iVar7 = g_nRdroidGeometryMode;
  }
  iVar8 = *(int *)((int)mesh + 0xc);
  if (g_nRdroidLightingMode <= *(int *)((int)mesh + 0xc)) {
    iVar8 = g_nRdroidLightingMode;
  }
  mesh = *(void **)((int)mesh + 0x10);
  if (g_nRdroidTextureMode <= (int)mesh) {
    mesh = (void *)g_nRdroidTextureMode;
  }
  if (iVar7 == 0) {
    return 0;
  }
  iVar1 = *(int *)((int)pvVar4 + 0x38);
  if (iVar1 == 0) {
    pbVar10 = (byte *)0x0;
  }
  else {
    iVar5 = *(int *)((int)pvVar4 + 0x3c);
    if (iVar5 == -1) {
      iVar5 = *(int *)(iVar1 + 100);
      if (iVar5 < 0) {
LAB_00408b6e:
        iVar5 = 0;
      }
      else {
        iVar9 = *(int *)(iVar1 + 0x60) + -1;
        if (iVar9 < iVar5) {
          iVar5 = iVar9;
        }
      }
    }
    else {
      if (iVar5 < 0) goto LAB_00408b6e;
      iVar9 = *(int *)(iVar1 + 0x60) + -1;
      if (iVar9 < iVar5) {
        iVar5 = iVar9;
      }
    }
    pbVar10 = *(byte **)(iVar1 + 0x68 + iVar5 * 4);
    if ((iVar7 == 4) && ((*pbVar10 & 8) == 0)) {
      iVar7 = 3;
    }
  }
  if (((byte)g_dwRdroidFlags & 2) == 0) {
    local_4 = 0;
  }
  else {
    local_4 = *(uint *)((int)pvVar4 + 0x40);
  }
  switch(iVar7) {
  case 1:
    if ((-1 < iVar8) && (iVar8 < 5)) {
      rdRaster_DrawPointsZ(pvVar4,pbVar10);
      return 1;
    }
    break;
  case 2:
    if ((-1 < iVar8) && (iVar8 < 5)) {
      rdRaster_DrawWireframeZ(pvVar4,pbVar10);
      return 1;
    }
    break;
  case 3:
    switch(iVar8) {
    case 0:
      if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
        rdRaster_Draw_FlatLitZ(pvVar4,pbVar10);
        return 1;
      }
      ((code *)rdRaster_Draw_TexLitZ)();
      return 1;
    case 1:
      fVar11 = 0.0;
      *(undefined4 *)((int)pvVar4 + 0x44) = 0;
      if ((*(byte *)((int)pvVar4 + 4) & 2) != 0) {
        ((code *)rdRaster_Draw_TexLitZ_2)();
        return 1;
      }
      break;
    case 2:
      fVar11 = *(float *)((int)pvVar4 + 0x48) + *(float *)((int)pvVar4 + 0x44);
      if (fVar11 < 0.0) {
        fVar2 = 0.0;
      }
      else {
        fVar2 = fVar11;
        if (1.0 < fVar11) {
          fVar2 = 1.0;
        }
      }
      if ((float)local_4 < fVar2) {
        if (fVar11 < 0.0) {
          local_4 = (uint)0.0;
        }
        else {
          local_4 = (uint)fVar11;
          if (1.0 < fVar11) {
            local_4 = (uint)1.0;
          }
        }
      }
      fVar11 = (float)local_4 * 63.0;
      *(float *)((int)pvVar4 + 0x44) = fVar11;
      if ((*(byte *)((int)pvVar4 + 4) & 2) != 0) {
        rdRaster_Draw_TexLitZ_2(pvVar4,pbVar10,fVar11);
        return 1;
      }
      break;
    case 3:
      uVar6 = 0;
      if (*(int *)((int)pvVar4 + 0x1c) != 0) {
        do {
          fVar11 = *(float *)(*(int *)((int)pvVar4 + 0x28) + uVar6 * 4) +
                   *(float *)((int)pvVar4 + 0x48);
          iVar7 = uVar6 * 4;
          if (fVar11 < 0.0) {
            fVar2 = 0.0;
          }
          else {
            fVar2 = fVar11;
            if (1.0 < fVar11) {
              fVar2 = 1.0;
            }
          }
          fVar3 = (float)local_4;
          if ((float)local_4 < fVar2) {
            if (fVar11 < 0.0) {
              fVar3 = 0.0;
            }
            else {
              fVar3 = fVar11;
              if (1.0 < fVar11) {
                fVar3 = 1.0;
              }
            }
          }
          uVar6 = uVar6 + 1;
          *(float *)(*(int *)((int)pvVar4 + 0x28) + iVar7) = fVar3 * 63.0;
        } while (uVar6 < *(uint *)((int)pvVar4 + 0x1c));
      }
      if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
        rdRaster_Draw_FlatLitZ_3(pvVar4,pbVar10);
        return 1;
      }
      ((code *)rdRaster_Draw_TexLitZ_3)();
      return 1;
    default:
      goto switchD_00408bad_default;
    }
    rdRaster_Draw_FlatLitZ_2(pvVar4,pbVar10,fVar11);
    return 1;
  case 4:
    if (mesh == (void *)0x0) {
      switch(iVar8) {
      case 0:
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_7(pvVar4,pbVar10);
            return 1;
          }
          ((code *)rdRaster_Draw_TexLitZ_4)();
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw(pvVar4,pbVar10);
          return 1;
        }
        ((code *)rdRaster_Draw_TexLitKeyZw_2)();
        return 1;
      case 1:
        if (*(float *)((int)pvVar4 + 0x48) < 0.0) {
          fVar11 = 0.0;
        }
        else if (1.0 < *(float *)((int)pvVar4 + 0x48)) {
          fVar11 = 1.0;
        }
        else {
          fVar11 = *(float *)((int)pvVar4 + 0x48);
        }
        if ((float)local_4 < fVar11) {
          if (*(float *)((int)pvVar4 + 0x48) < 0.0) {
            local_4 = 0;
          }
          else if (1.0 < *(float *)((int)pvVar4 + 0x48)) {
            local_4 = 0x3f800000;
          }
          else {
            local_4 = *(uint *)((int)pvVar4 + 0x48);
          }
        }
        fVar11 = (float)local_4 * 63.0;
        *(float *)((int)pvVar4 + 0x44) = fVar11;
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_8(pvVar4,pbVar10,fVar11);
            return 1;
          }
          rdRaster_Draw_TexLitZ_5(pvVar4,pbVar10,fVar11);
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw_3(pvVar4,pbVar10,fVar11);
          return 1;
        }
        rdRaster_Draw_TexLitKeyZw_4(pvVar4,pbVar10,fVar11);
        return 1;
      case 2:
        fVar11 = *(float *)((int)pvVar4 + 0x48) + *(float *)((int)pvVar4 + 0x44);
        if (fVar11 < 0.0) {
          fVar2 = 0.0;
        }
        else {
          fVar2 = fVar11;
          if (1.0 < fVar11) {
            fVar2 = 1.0;
          }
        }
        if ((float)local_4 < fVar2) {
          if (fVar11 < 0.0) {
            local_4 = (uint)0.0;
          }
          else {
            local_4 = (uint)fVar11;
            if (1.0 < fVar11) {
              local_4 = (uint)1.0;
            }
          }
        }
        fVar11 = (float)local_4 * 63.0;
        *(float *)((int)pvVar4 + 0x44) = fVar11;
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_8(pvVar4,pbVar10,fVar11);
            return 1;
          }
          rdRaster_Draw_TexLitZ_5(pvVar4,pbVar10,fVar11);
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw_3(pvVar4,pbVar10,fVar11);
          return 1;
        }
        rdRaster_Draw_TexLitKeyZw_4(pvVar4,pbVar10,fVar11);
        return 1;
      case 3:
        uVar6 = 0;
        if (*(int *)((int)pvVar4 + 0x1c) != 0) {
          do {
            fVar11 = *(float *)(*(int *)((int)pvVar4 + 0x28) + uVar6 * 4) +
                     *(float *)((int)pvVar4 + 0x48);
            iVar7 = uVar6 * 4;
            if (fVar11 < 0.0) {
              fVar2 = 0.0;
            }
            else {
              fVar2 = fVar11;
              if (1.0 < fVar11) {
                fVar2 = 1.0;
              }
            }
            fVar3 = (float)local_4;
            if ((float)local_4 < fVar2) {
              if (fVar11 < 0.0) {
                fVar3 = 0.0;
              }
              else {
                fVar3 = fVar11;
                if (1.0 < fVar11) {
                  fVar3 = 1.0;
                }
              }
            }
            uVar6 = uVar6 + 1;
            *(float *)(*(int *)((int)pvVar4 + 0x28) + iVar7) = fVar3 * 63.0;
          } while (uVar6 < *(uint *)((int)pvVar4 + 0x1c));
        }
        if ((**(byte **)(pbVar10 + 0x1c) & 1) != 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_TexLitKeyZw_5(pvVar4,pbVar10);
            return 1;
          }
          ((code *)rdRaster_Draw_TexLitKeyZw_6)();
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) != 0) {
          ((code *)rdRaster_Draw_TexLitZ_6)();
          return 1;
        }
        rdRaster_Draw_FlatLit_9(pvVar4,pbVar10);
      }
    }
    else if (mesh == (void *)0x1) {
      switch(iVar8) {
      case 0:
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_10(pvVar4,pbVar10);
            return 1;
          }
          ((code *)rdRaster_Draw_TexLitZ_7)();
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw_7(pvVar4,pbVar10);
          return 1;
        }
        ((code *)rdRaster_Draw_TexLitKeyZw_8)();
        return 1;
      case 1:
        if (*(float *)((int)pvVar4 + 0x48) < 0.0) {
          fVar11 = 0.0;
        }
        else if (1.0 < *(float *)((int)pvVar4 + 0x48)) {
          fVar11 = 1.0;
        }
        else {
          fVar11 = *(float *)((int)pvVar4 + 0x48);
        }
        if ((float)local_4 < fVar11) {
          if (*(float *)((int)pvVar4 + 0x48) < 0.0) {
            local_4 = 0;
          }
          else if (1.0 < *(float *)((int)pvVar4 + 0x48)) {
            local_4 = 0x3f800000;
          }
          else {
            local_4 = *(uint *)((int)pvVar4 + 0x48);
          }
        }
        fVar11 = (float)local_4 * 63.0;
        *(float *)((int)pvVar4 + 0x44) = fVar11;
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_11(pvVar4,pbVar10,fVar11);
            return 1;
          }
          rdRaster_Draw_TexLitZ_8(pvVar4,pbVar10,fVar11);
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw_9(pvVar4,pbVar10,fVar11);
          return 1;
        }
        rdRaster_Draw_TexLitKeyZw_10(pvVar4,pbVar10,fVar11);
        return 1;
      case 2:
        fVar11 = *(float *)((int)pvVar4 + 0x48) + *(float *)((int)pvVar4 + 0x44);
        if (fVar11 < 0.0) {
          fVar2 = 0.0;
        }
        else {
          fVar2 = fVar11;
          if (1.0 < fVar11) {
            fVar2 = 1.0;
          }
        }
        if ((float)local_4 < fVar2) {
          if (fVar11 < 0.0) {
            local_4 = (uint)0.0;
          }
          else {
            local_4 = (uint)fVar11;
            if (1.0 < fVar11) {
              local_4 = (uint)1.0;
            }
          }
        }
        fVar11 = (float)local_4 * 63.0;
        *(float *)((int)pvVar4 + 0x44) = fVar11;
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_11(pvVar4,pbVar10,fVar11);
            return 1;
          }
          rdRaster_Draw_TexLitZ_8(pvVar4,pbVar10,fVar11);
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw_9(pvVar4,pbVar10,fVar11);
          return 1;
        }
        rdRaster_Draw_TexLitKeyZw_10(pvVar4,pbVar10,fVar11);
        return 1;
      case 3:
        uVar6 = 0;
        if (*(int *)((int)pvVar4 + 0x1c) != 0) {
          do {
            fVar11 = *(float *)(*(int *)((int)pvVar4 + 0x28) + uVar6 * 4) +
                     *(float *)((int)pvVar4 + 0x48);
            iVar7 = uVar6 * 4;
            if (fVar11 < 0.0) {
              fVar2 = 0.0;
            }
            else {
              fVar2 = fVar11;
              if (1.0 < fVar11) {
                fVar2 = 1.0;
              }
            }
            fVar3 = (float)local_4;
            if ((float)local_4 < fVar2) {
              if (fVar11 < 0.0) {
                fVar3 = 0.0;
              }
              else {
                fVar3 = fVar11;
                if (1.0 < fVar11) {
                  fVar3 = 1.0;
                }
              }
            }
            uVar6 = uVar6 + 1;
            *(float *)(*(int *)((int)pvVar4 + 0x28) + iVar7) = fVar3 * 63.0;
          } while (uVar6 < *(uint *)((int)pvVar4 + 0x1c));
        }
        if ((**(byte **)(pbVar10 + 0x1c) & 1) == 0) {
          if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
            rdRaster_Draw_FlatLit_12(pvVar4,pbVar10);
            return 1;
          }
          ((code *)rdRaster_Draw_TexLitZ_9)();
          return 1;
        }
        if ((*(byte *)((int)pvVar4 + 4) & 2) == 0) {
          rdRaster_Draw_TexLitKeyZw_11(pvVar4,pbVar10);
          return 1;
        }
        ((code *)rdRaster_Draw_TexLitKeyZw_12)();
        return 1;
      }
    }
  }
switchD_00408bad_default:
  return 1;
}
#undef local_4

