/* GRIMFANDANGO.EXE :: rdmodel.c
 * functions 0x00409580 .. 0x0040d880 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00409580  rdCache_DrawFaceUser ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Rdcamera.c: picks the light level of a mesh from the current geometry/lighting/texture modes
   (gouraud, flat, per-vertex) and hands it to the mesh draw callback at +0x14 Original name
   rdCache_DrawFaceUser (the remaster's GrimFandango (Linux): aligned call in rdCache_Flush); was
   rdModel_ComputeMeshLighting. */

uint __cdecl rdCache_DrawFaceUser(byte *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  #define local_8 (*(float (*)[2])(_frame + (0x20 - 0x8)))
  
  pbVar5 = param_1;
  iVar8 = *(int *)(param_1 + 8);
  if (g_nRdroid_curGeometryMode <= *(int *)(param_1 + 8)) {
    iVar8 = g_nRdroid_curGeometryMode;
  }
  iVar11 = *(int *)(param_1 + 0xc);
  if (g_nRdroid_curLightingMode <= *(int *)(param_1 + 0xc)) {
    iVar11 = g_nRdroid_curLightingMode;
  }
  iVar9 = *(int *)(param_1 + 0x10);
  if (g_nRdroid_curTextureMode <= *(int *)(param_1 + 0x10)) {
    iVar9 = g_nRdroid_curTextureMode;
  }
  if (iVar8 == 0) {
    return 0;
  }
  iVar2 = *(int *)(param_1 + 0x38);
  if (iVar2 == 0) {
    param_1 = (byte *)0x0;
  }
  else {
    iVar6 = *(int *)(param_1 + 0x3c);
    if (iVar6 == -1) {
      iVar6 = *(int *)(iVar2 + 100);
      if (iVar6 < 0) {
        iVar6 = 0;
      }
      else {
        iVar10 = *(int *)(iVar2 + 0x60) + -1;
        if (iVar10 < iVar6) {
          param_1 = *(byte **)(iVar2 + 0x68 + iVar10 * 4);
          goto LAB_0040961e;
        }
      }
      param_1 = *(byte **)(iVar2 + 0x68 + iVar6 * 4);
    }
    else {
      if (iVar6 < 0) {
        iVar6 = 0;
      }
      else {
        iVar10 = *(int *)(iVar2 + 0x60) + -1;
        if (iVar10 < iVar6) {
          iVar6 = iVar10;
        }
      }
      param_1 = *(byte **)(iVar2 + 0x68 + iVar6 * 4);
    }
LAB_0040961e:
    if ((iVar8 == 4) && ((*param_1 & 8) == 0)) {
      iVar8 = 3;
    }
  }
  if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
    local_8[0] = 0.0;
  }
  else {
    local_8[0] = *(float *)(pbVar5 + 0x40);
  }
  switch(iVar8) {
  case 1:
  case 2:
    if (iVar11 < 0) {
      return 1;
    }
    if (4 < iVar11) {
      return 1;
    }
    break;
  case 3:
    switch(iVar11) {
    case 0:
      goto switchD_004098a8_caseD_0;
    case 1:
      if (*(float *)(pbVar5 + 0x48) < 0.0) {
        fVar1 = 0.0;
      }
      else if (1.0 < *(float *)(pbVar5 + 0x48)) {
        fVar1 = 1.0;
      }
      else {
        fVar1 = *(float *)(pbVar5 + 0x48);
      }
      if (local_8[0] < fVar1) {
        if (*(float *)(pbVar5 + 0x48) < 0.0) {
          local_8[0] = 0.0;
        }
        else if (1.0 < *(float *)(pbVar5 + 0x48)) {
          local_8[0] = 1.0;
        }
        else {
          local_8[0] = *(float *)(pbVar5 + 0x48);
        }
      }
      *(float *)(pbVar5 + 0x44) = local_8[0] * 63.0;
      (**(code **)(pbVar5 + 0x14))(pbVar5,param_1,local_8[0] * 63.0);
      return 1;
    case 2:
      fVar1 = *(float *)(pbVar5 + 0x48) + *(float *)(pbVar5 + 0x44);
      if (fVar1 < 0.0) {
        fVar3 = 0.0;
      }
      else {
        fVar3 = fVar1;
        if (1.0 < fVar1) {
          fVar3 = 1.0;
        }
      }
      if (local_8[0] < fVar3) {
        if (fVar1 < 0.0) {
          local_8[0] = 0.0;
        }
        else {
          local_8[0] = fVar1;
          if (1.0 < fVar1) {
            local_8[0] = 1.0;
          }
        }
      }
      *(float *)(pbVar5 + 0x44) = local_8[0] * 63.0;
      (**(code **)(pbVar5 + 0x14))(pbVar5,param_1,local_8[0] * 63.0);
      return 1;
    case 3:
      uVar7 = 0;
      if (*(int *)(pbVar5 + 0x1c) != 0) {
        do {
          fVar1 = *(float *)(pbVar5 + 0x48) + *(float *)(*(int *)(pbVar5 + 0x28) + uVar7 * 4);
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
          fVar4 = local_8[0];
          if (local_8[0] < fVar3) {
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
          *(float *)(*(int *)(pbVar5 + 0x28) + iVar8) = fVar4 * 63.0;
        } while (uVar7 < *(uint *)(pbVar5 + 0x1c));
      }
      break;
    default:
      goto switchD_00409661_default;
    }
    break;
  case 4:
    if (iVar9 == 0) {
      switch(iVar11) {
      case 0:
        goto switchD_004098a8_caseD_0;
      case 1:
        if (*(float *)(pbVar5 + 0x48) < 0.0) {
          fVar1 = 0.0;
        }
        else if (1.0 < *(float *)(pbVar5 + 0x48)) {
          fVar1 = 1.0;
        }
        else {
          fVar1 = *(float *)(pbVar5 + 0x48);
        }
        if (local_8[0] < fVar1) {
          if (*(float *)(pbVar5 + 0x48) < 0.0) {
            local_8[0] = 0.0;
          }
          else if (1.0 < *(float *)(pbVar5 + 0x48)) {
            local_8[0] = 1.0;
          }
          else {
            local_8[0] = *(float *)(pbVar5 + 0x48);
          }
        }
        *(float *)(pbVar5 + 0x44) = local_8[0] * 63.0;
        (**(code **)(pbVar5 + 0x14))(pbVar5,param_1,local_8[0] * 63.0);
        return 1;
      case 2:
        fVar1 = *(float *)(pbVar5 + 0x48) + *(float *)(pbVar5 + 0x44);
        if (fVar1 < 0.0) {
          fVar3 = 0.0;
        }
        else {
          fVar3 = fVar1;
          if (1.0 < fVar1) {
            fVar3 = 1.0;
          }
        }
        if (local_8[0] < fVar3) {
          if (fVar1 < 0.0) {
            local_8[0] = 0.0;
          }
          else {
            local_8[0] = fVar1;
            if (1.0 < fVar1) {
              local_8[0] = 1.0;
            }
          }
        }
        *(float *)(pbVar5 + 0x44) = local_8[0] * 63.0;
        (**(code **)(pbVar5 + 0x14))(pbVar5,param_1,local_8[0] * 63.0);
        return 1;
      case 3:
        uVar7 = 0;
        if (*(int *)(pbVar5 + 0x1c) != 0) {
          do {
            fVar1 = *(float *)(pbVar5 + 0x48) + *(float *)(*(int *)(pbVar5 + 0x28) + uVar7 * 4);
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
            fVar4 = local_8[0];
            if (local_8[0] < fVar3) {
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
            *(float *)(*(int *)(pbVar5 + 0x28) + iVar8) = fVar4 * 63.0;
          } while (uVar7 < *(uint *)(pbVar5 + 0x1c));
        }
        break;
      default:
        goto switchD_00409661_default;
      }
    }
    else {
      if (iVar9 != 1) {
        return 1;
      }
      switch(iVar11) {
      case 0:
switchD_004098a8_caseD_0:
        break;
      case 1:
        if (*(float *)(pbVar5 + 0x48) < 0.0) {
          fVar1 = 0.0;
        }
        else if (1.0 < *(float *)(pbVar5 + 0x48)) {
          fVar1 = 1.0;
        }
        else {
          fVar1 = *(float *)(pbVar5 + 0x48);
        }
        if (local_8[0] < fVar1) {
          if (*(float *)(pbVar5 + 0x48) < 0.0) {
            local_8[0] = 0.0;
          }
          else if (1.0 < *(float *)(pbVar5 + 0x48)) {
            local_8[0] = 1.0;
          }
          else {
            local_8[0] = *(float *)(pbVar5 + 0x48);
          }
        }
        *(float *)(pbVar5 + 0x44) = local_8[0] * 63.0;
        (**(code **)(pbVar5 + 0x14))(pbVar5,param_1,local_8[0] * 63.0);
        return 1;
      case 2:
        fVar1 = *(float *)(pbVar5 + 0x48) + *(float *)(pbVar5 + 0x44);
        if (fVar1 < 0.0) {
          fVar3 = 0.0;
        }
        else {
          fVar3 = fVar1;
          if (1.0 < fVar1) {
            fVar3 = 1.0;
          }
        }
        if (local_8[0] < fVar3) {
          if (fVar1 < 0.0) {
            local_8[0] = 0.0;
          }
          else {
            local_8[0] = fVar1;
            if (1.0 < fVar1) {
              local_8[0] = 1.0;
            }
          }
        }
        *(float *)(pbVar5 + 0x44) = local_8[0] * 63.0;
        (**(code **)(pbVar5 + 0x14))(pbVar5,param_1,local_8[0] * 63.0);
        return 1;
      case 3:
        uVar7 = 0;
        if (*(int *)(pbVar5 + 0x1c) != 0) {
          do {
            fVar1 = *(float *)(pbVar5 + 0x48) + *(float *)(*(int *)(pbVar5 + 0x28) + uVar7 * 4);
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
            fVar4 = local_8[0];
            if (local_8[0] < fVar3) {
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
            *(float *)(*(int *)(pbVar5 + 0x28) + iVar8) = fVar4 * 63.0;
          } while (uVar7 < *(uint *)(pbVar5 + 0x1c));
        }
        break;
      default:
        goto switchD_00409661_default;
      }
    }
    break;
  default:
    goto switchD_00409661_default;
  }
  (**(code **)(pbVar5 + 0x14))(pbVar5,param_1,0);
switchD_00409661_default:
  return 1;
}
#undef local_8

#endif


/* ---- 0x00409d20  rdCache_ProcFaceCompare ---- */
/* Original name rdCache_ProcFaceCompare (the remaster's GrimFandango (Linux): aligned call in
   rdCache_Flush); was FUN_00409d20. */

uint __cdecl rdCache_ProcFaceCompare(int param_1,int param_2)

{
  if (*(float *)(param_1 + 100) == *(float *)(param_2 + 100)) {
    return 0;
  }
  if (*(float *)(param_1 + 100) < *(float *)(param_2 + 100)) {
    return 1;
  }
  return 0xffffffff;
}

/* ---- 0x0040d140  rdModel3_DrawHNode ---- */
/* Recursive hierarchy walk (+0x58 child count, +0x5c first child, +0x60 sibling) drawing each
   node's mesh Original name rdModel3_DrawHNode (the remaster's GrimFandango (Linux): same body
   (mesh index +0x4c, geoset flag +0x40 bit 1 walks +0x54, draws the mesh, recurses over +0x58 /
   +0x5c children)); was rdModel_DrawNode. */

void __cdecl rdModel3_DrawHNode(int param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  if ((*(int *)(param_1 + 0x4c) != -1) &&
     (*(int *)(*(int *)((int)g_pCurThing + 0x2c) + *(int *)(param_1 + 0x44) * 4) != 0)) {
    if ((*(byte *)(param_1 + 0x40) & 2) != 0) {
      iVar3 = *(int *)(param_1 + 0x54);
      bVar1 = *(byte *)(iVar3 + 0x40);
      while ((bVar1 & 2) != 0) {
        iVar3 = *(int *)(iVar3 + 0x54);
        bVar1 = *(byte *)(iVar3 + 0x40);
      }
      *(undefined4 *)(*(int *)(g_dwCurGeo + 4) + 0x28 + *(int *)(param_1 + 0x4c) * 0x7c) = 6;
      *(undefined4 *)(*(int *)(g_dwCurGeo + 4) + 0x5c + *(int *)(param_1 + 0x4c) * 0x7c) =
           *(undefined4 *)(*(int *)(g_dwCurGeo + 4) + 0x5c + *(int *)(iVar3 + 0x4c) * 0x7c);
    }
    rdModel3_DrawMeshImpl
              ((void *)(*(int *)(g_dwCurGeo + 4) + *(int *)(param_1 + 0x4c) * 0x7c),
               (float *)(*(int *)((int)g_pCurThing + 0x20) + *(int *)(param_1 + 0x44) * 0x30));
  }
  if (*(int *)(param_1 + 0x58) != 0) {
    iVar3 = *(int *)(param_1 + 0x5c);
    uVar2 = 0;
    if (*(int *)(param_1 + 0x58) != 0) {
      do {
        if (*(int *)(*(int *)((int)g_pCurThing + 0x28) + *(int *)(iVar3 + 0x44) * 4) == 0) {
          rdModel3_DrawHNode(iVar3);
        }
        iVar3 = *(int *)(iVar3 + 0x60);
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(param_1 + 0x58));
    }
  }
  return;
}

/* ---- 0x0040d230  rdModel3_DrawMeshImpl ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name rdModel3_DrawMeshImpl (the remaster's GrimFandango (Linux): the only unmatched
   caller of rdLight_CalcVertexIntensities; 1 matched neighbours agree, 0 disagree); was
   rdModel_DrawMesh. */

void __cdecl rdModel3_DrawMeshImpl(void *mesh,float *matrix)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *a;
  int iVar1;
  int *piVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  void *pvVar8;
  uint uVar9;
  void *pvVar10;
  int iVar11;
  float fVar12;
  #define local_ac (*(uint *)(_frame + (0xc0 - 0xac)))
  #define local_a8 (*(uint *)(_frame + (0xc0 - 0xa8)))
  #define local_a4 (*(uint *)(_frame + (0xc0 - 0xa4)))
  #define local_a0 (*(float (*)[3])(_frame + (0xc0 - 0xa0)))
  #define local_90 (*(float (*)[3])(_frame + (0xc0 - 0x90)))
  #define local_84 (*(float (*)[9])(_frame + (0xc0 - 0x84)))
  #define local_60 (*(uint *)(_frame + (0xc0 - 0x60)))
  #define local_5c (*(uint *)(_frame + (0xc0 - 0x5c)))
  #define local_58 (*(uint *)(_frame + (0xc0 - 0x58)))
  #define local_54 (*(float (*)[3])(_frame + (0xc0 - 0x54)))
  #define local_48 (*(float (*)[5])(_frame + (0xc0 - 0x48)))
  #define local_34 (*(uint *)(_frame + (0xc0 - 0x34)))
  #define local_30 (*(float (*)[12])(_frame + (0xc0 - 0x30)))
  
  g_pCurMesh = mesh;
  if (*(int *)((int)mesh + 0x24) != 0) {
    a = matrix + 9;
    rdMatrix_TransformPoint34(local_48,a,(float *)((int)g_pRdCamera_CurCamera + 8));
    if (g_dwThingFrustrumCull == 0) {
      g_dwMeshFrustrumCull = 0;
    }
    else if ((g_bRdroid_curCullFlags & 1) == 0) {
      g_dwMeshFrustrumCull = 1;
    }
    else {
      g_dwMeshFrustrumCull =
           rdClip_SphereInFrustrum
                     (*(int **)((int)g_pRdCamera_CurCamera + 0x48),local_48,
                      *(float *)((int)g_pCurMesh + 0x60));
    }
    if ((g_dwMeshFrustrumCull != 2) &&
       ((g_dwClipPlaneActive == 0 ||
        (-*(float *)((int)g_pCurMesh + 0x60) <=
         (*a - _DAT_007f3208) * _DAT_004ddb70 +
         (matrix[0xb] - _DAT_007f3210) * _DAT_004ddb78 +
         (matrix[10] - _DAT_007f320c) * _DAT_004ddb74)))) {
      rdMatrix_Multiply34(local_30,(float *)((int)g_pRdCamera_CurCamera + 8),matrix);
      rdMatrix_TransformPointLst34
                (local_30,*(float **)((int)g_pCurMesh + 0x30),(float *)&g_aRdModel3_View,
                 *(int *)((int)g_pCurMesh + 0x48));
      rdMatrix_InvertOrtho34(local_84,matrix);
      g_dwGeometryMode = *(uint *)((int)g_pCurMesh + 0x24);
      if ((int)g_dwCurTextureMode <= (int)g_dwGeometryMode) {
        g_dwGeometryMode = g_dwCurTextureMode;
      }
      g_dwTextureMode = *(uint *)((int)g_pCurMesh + 0x2c);
      if ((int)UINT_007f189c <= (int)g_dwTextureMode) {
        g_dwTextureMode = UINT_007f189c;
      }
      g_dwLightingMode = *(uint *)((int)g_pCurMesh + 0x28);
      if (g_dwLightingMode == 6) {
        g_dwLightingMode = 6;
      }
      else if ((int)UINT_007f30dc <= (int)g_dwLightingMode) {
        g_dwLightingMode = UINT_007f30dc;
      }
      _DAT_007f30b4 = &g_aRdModel3_View;
      _DAT_007f30b8 = *(undefined4 *)((int)g_pCurMesh + 0x34);
      _DAT_007f30bc = *(undefined4 *)((int)g_pCurMesh + 0x3c);
      _DAT_007f30c0 = 0;
      UINT_007f1474 = (uint)&DAT_007f0fe8;
      switch(g_dwLightingMode) {
      case 2:
        uVar9 = 0;
        g_dwNumMeshLights = 0;
        local_a8 = 0;
        if (g_dwNumGeoLights != 0) {
          local_ac = (uint)&g_apGeoLights;
          pvVar8 = g_pRdCamera_CurCamera;
          pvVar10 = g_pCurMesh;
          do {
            piVar2 = *(int **)local_ac;
            if ((piVar2[2] != 0) &&
               (iVar11 = *piVar2,
               fVar12 = *(float *)((int)pvVar8 + iVar11 * 0xc + 0x160) - matrix[10],
               fVar3 = *(float *)((int)pvVar8 + (iVar11 + 0x1d) * 0xc) - *a,
               fVar4 = *(float *)((int)pvVar8 + iVar11 * 0xc + 0x164) - matrix[0xb],
               SQRT(fVar4 * fVar4 + fVar12 * fVar12 + fVar3 * fVar3) <
               PUN(float,piVar2[0xd]) + *(float *)((int)pvVar10 + 0x60))) {
              (&UINT_007f30e0)[uVar9] = (uint)piVar2;
              rdMatrix_TransformPoint34
                        ((float *)(&g_aLocalLightPos + uVar9 * 0xc),
                         (float *)((int)pvVar8 + (*piVar2 + 0x1d) * 0xc),local_84);
              if (piVar2[1] != 2) {
                local_60 = 0;
                local_5c = 0;
                local_34 = local_58;
                local_58 = 0;
                local_a0[0] = -PUN(float,piVar2[3]);
                local_a0[1] = -PUN(float,piVar2[4]);
                local_a0[2] = -PUN(float,piVar2[5]);
                ((code *)rdMatrix_TransformPoint34)((float *)(&g_aLocalLightDir + g_dwNumMeshLights * 0xc),local_a0,local_84)
                ;
                local_58 = local_34;
              }
              uVar9 = g_dwNumMeshLights + 1;
              pvVar8 = g_pRdCamera_CurCamera;
              pvVar10 = g_pCurMesh;
              g_dwNumMeshLights = uVar9;
            }
            local_a8 = local_a8 + 1;
            local_ac = local_ac + 4;
          } while (local_a8 < g_dwNumGeoLights);
        }
        break;
      case 3:
        uVar9 = 0;
        g_dwNumMeshLights = 0;
        local_a8 = 0;
        pvVar8 = g_pRdCamera_CurCamera;
        pvVar10 = g_pCurMesh;
        if (g_dwNumGeoLights != 0) {
          local_ac = (uint)&g_apGeoLights;
          do {
            piVar2 = *(int **)local_ac;
            if (piVar2[2] != 0) {
              iVar11 = *piVar2;
              fVar12 = *(float *)((int)pvVar8 + (iVar11 + 0x1d) * 0xc) - *a;
              fVar4 = *(float *)((int)pvVar8 + iVar11 * 0xc + 0x160) - matrix[10];
              fVar3 = *(float *)((int)pvVar8 + iVar11 * 0xc + 0x164) - matrix[0xb];
              if (piVar2[1] < 2) {
                fVar12 = 0.0;
              }
              else {
                fVar12 = fVar3 * fVar3 + fVar4 * fVar4 + fVar12 * fVar12;
              }
              fVar3 = PUN(float,piVar2[0xd]) + *(float *)((int)pvVar10 + 0x60);
              if (fVar12 < fVar3 * fVar3) {
                (&UINT_007f30e0)[uVar9] = (uint)piVar2;
                rdMatrix_TransformPoint34
                          ((float *)(&g_aLocalLightPos + uVar9 * 0xc),
                           (float *)((int)pvVar8 + (*piVar2 + 0x1d) * 0xc),local_84);
                uVar5 = local_58;
                if (piVar2[1] != 2) {
                  local_60 = 0;
                  local_5c = 0;
                  local_58 = 0;
                  local_a0[0] = -PUN(float,piVar2[3]);
                  local_a0[1] = -PUN(float,piVar2[4]);
                  local_a0[2] = -PUN(float,piVar2[5]);
                  rdMatrix_TransformPoint34
                            ((float *)(&g_aLocalLightDir + g_dwNumMeshLights * 0xc),local_a0,
                             local_84);
                }
                uVar9 = g_dwNumMeshLights + 1;
                pvVar8 = g_pRdCamera_CurCamera;
                pvVar10 = g_pCurMesh;
                g_dwNumMeshLights = uVar9;
                local_58 = uVar5;
              }
            }
            local_a8 = local_a8 + 1;
            local_ac = local_ac + 4;
          } while (local_a8 < g_dwNumGeoLights);
        }
        fVar12 = rdLight_CalcVertexIntensities
                           ((int *)&UINT_007f30e0,(float *)&g_aLocalLightPos,((unsigned)(uintptr_t)&g_aLocalLightDir),uVar9,
                            *(int **)((int)pvVar10 + 0x44),*(uint *)((int)pvVar10 + 0x30),
                            *(float **)((int)pvVar10 + 0x38),*(float **)((int)pvVar10 + 0x3c),
                            *(uint *)((int)pvVar10 + 0x48),*(float *)((int)pvVar8 + 0x45c));
        *(float *)((int)mesh + 0x5c) = fVar12;
        break;
      case 6:
        uVar9 = 0;
        if (*(int *)((int)mesh + 0x50) != 0) {
          puVar7 = (undefined4 *)(*(int *)((int)mesh + 0x40) + 0x30);
          do {
            *puVar7 = *(undefined4 *)((int)mesh + 0x5c);
            puVar7 = puVar7 + 0x13;
            uVar9 = uVar9 + 1;
          } while (uVar9 < *(uint *)((int)mesh + 0x50));
        }
      }
      local_54[0] = (float)UINT_008ddf84;
      local_54[1] = (float)UINT_008ddf88;
      local_54[2] = (float)UINT_008ddf8c;
      rdMatrix_TransformPoint34((float *)&DAT_007f0fd8,local_54,local_84);
      iVar11 = *(int *)((int)mesh + 0x40);
      uVar9 = 0;
      if (*(int *)((int)mesh + 0x50) != 0) {
        do {
          iVar6 = *(int *)((int)g_pCurMesh + 0x30);
          iVar1 = **(int **)(iVar11 + 0x18);
          if (*(float *)(iVar11 + 0x44) * (_DAT_007f0fdc - *(float *)(iVar6 + iVar1 * 0xc + 4)) +
              (_DAT_007f0fd8 - *(float *)(iVar6 + iVar1 * 0xc)) * *(float *)(iVar11 + 0x40) +
              *(float *)(iVar11 + 0x48) * (_DAT_007f0fe0 - *(float *)(iVar6 + 8 + iVar1 * 0xc)) <=
              0.0) {
            iVar6 = 1;
            if (((*(byte *)(iVar11 + 4) & 1) != 0) || (((byte)g_dwRdroid_curRenderOptions & 1) == 0)
               ) goto LAB_0040d640;
          }
          else {
            iVar6 = 0;
LAB_0040d640:
            rdModel3_DrawFace(iVar11,iVar6);
          }
          iVar11 = iVar11 + 0x4c;
          uVar9 = uVar9 + 1;
        } while (uVar9 < *(uint *)((int)mesh + 0x50));
      }
    }
  }
  return;
}
#undef local_30
#undef local_34
#undef local_48
#undef local_54
#undef local_58
#undef local_5c
#undef local_60
#undef local_84
#undef local_90
#undef local_a0
#undef local_a4
#undef local_a8
#undef local_ac

#endif


/* ---- 0x0040d880  rdModel3_DrawFace ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Original name rdModel3_DrawFace (the remaster's GrimFandango (Linux): the only unmatched caller
   of rdLight_CalcFaceIntensity; 3 matched neighbours agree, 0 disagree); was
   rdModel_AddMeshToCache. */

uint __cdecl rdModel3_DrawFace(int param_1,int param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  byte flags;
  undefined1 *puVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  bool bVar6;
  float fVar7;
  #define local_24 (*(float *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(float (*)[2])(_frame + (0x40 - 0x20)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  puVar2 = rdCache_GetProcEntry();
  if (puVar2 == (undefined1 *)0x0) {
    return 0;
  }
  uVar3 = *(uint *)(param_1 + 8);
  if ((int)g_dwGeometryMode < (int)*(uint *)(param_1 + 8)) {
    uVar3 = g_dwGeometryMode;
  }
  *(uint *)(puVar2 + 8) = uVar3;
  uVar3 = *(uint *)(param_1 + 0xc);
  if ((int)g_dwLightingMode < (int)*(uint *)(param_1 + 0xc)) {
    uVar3 = g_dwLightingMode;
  }
  *(uint *)(puVar2 + 0xc) = uVar3;
  uVar3 = *(uint *)(param_1 + 0x10);
  if ((int)g_dwTextureMode < (int)*(uint *)(param_1 + 0x10)) {
    uVar3 = g_dwTextureMode;
  }
  *(uint *)(puVar2 + 0x10) = uVar3;
  if ((*(byte *)(param_1 + 4) & 0x10) != 0) {
    *(undefined4 *)(puVar2 + 0xc) = 1;
  }
  UINT_007f1490 = *(uint *)(puVar2 + 0x20);
  UINT_007f1478 = *(uint *)(puVar2 + 0x24);
  UINT_007f147c = *(uint *)(puVar2 + 0x28);
  _g_aVertexSrc = *(undefined4 *)(param_1 + 0x14);
  _DAT_007f30ac = *(undefined4 *)(param_1 + 0x18);
  _DAT_007f30b0 = *(undefined4 *)(param_1 + 0x1c);
  if (g_dwMeshFrustrumCull == 0) {
    rdPrimit3_NoClipFace
              (*(uint *)(puVar2 + 8),*(int *)(puVar2 + 0xc),*(uint *)(puVar2 + 0x10),
               (uint *)&g_aVertexSrc,&g_dwVertexDst,(float *)(param_1 + 0x28));
  }
  else {
    rdPrimit3_ClipFace(*(uint *)((int)g_pRdCamera_CurCamera + 0x48),*(uint *)(puVar2 + 8),
                       *(int *)(puVar2 + 0xc),*(uint *)(puVar2 + 0x10),(uint *)&g_aVertexSrc,
                       &g_dwVertexDst,(float *)(param_1 + 0x28));
  }
  if (g_dwVertexDst < 3) {
    return 0;
  }
  if (g_dwClipPlaneActive != 0) {
    rdMatrix_TransformVector34
              (local_c,(float *)&DAT_004ddb70,(float *)((int)g_pRdCamera_CurCamera + 8));
    rdMatrix_TransformPoint34
              (local_18,(float *)&DAT_007f3208,(float *)((int)g_pRdCamera_CurCamera + 8));
    uVar3 = rdClip_FaceToPlane(local_c,local_18,(float *)UINT_007f1474,(uint *)UINT_007f1478,
                               (float *)UINT_007f147c,(uint *)g_dwVertexDst);
    if ((int)uVar3 < 2) {
      return 0;
    }
    g_dwVertexDst = uVar3;
    *(uint *)(puVar2 + 0x1c) = uVar3;
  }
  if (*(int *)(puVar2 + 0xc) == 2) {
    if (param_2 == 0) {
      fVar7 = *(float *)((int)g_pRdCamera_CurCamera + 0x45c);
      iVar5 = *(int *)((int)g_pCurMesh + 0x30);
      pfVar4 = (float *)(param_1 + 0x40);
    }
    else {
      local_24 = -*(float *)(param_1 + 0x40);
      local_20[0] = -*(float *)(param_1 + 0x44);
      local_20[1] = -*(float *)(param_1 + 0x48);
      fVar7 = *(float *)((int)g_pRdCamera_CurCamera + 0x45c);
      iVar5 = *(int *)((int)g_pCurMesh + 0x30);
      pfVar4 = &local_24;
    }
    fVar7 = rdLight_CalcFaceIntensity
                      ((int *)&UINT_007f30e0,((unsigned)(uintptr_t)&g_aLocalLightPos),((unsigned)(uintptr_t)&g_aLocalLightDir),g_dwNumMeshLights,param_1,pfVar4,
                       iVar5,fVar7);
    *(float *)(puVar2 + 0x44) = fVar7;
  }
  (**(code **)((int)g_pRdCamera_CurCamera + 0x50))(UINT_007f1490,UINT_007f1474,g_dwVertexDst);
  if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
    *(undefined4 *)(puVar2 + 0x40) = 0;
  }
  else {
    *(undefined4 *)(puVar2 + 0x40) = *(undefined4 *)((int)g_pRdCamera_CurCamera + 0x54);
  }
  iVar5 = *(int *)(param_1 + 0x24);
  if ((iVar5 == -1) && (*(int *)(param_1 + 0x20) != 0)) {
    iVar5 = *(int *)(*(int *)(param_1 + 0x20) + 100);
  }
  *(int *)(puVar2 + 0x3c) = iVar5;
  bVar6 = g_dwRdColormap_pIdentityMap != g_dwRdColormap_pCurMap;
  if (*(float *)(puVar2 + 0x40) < 1.0) {
    if (*(int *)(puVar2 + 0xc) == 2) {
      if ((*(float *)(puVar2 + 0x44) < 1.0) || (bVar6)) {
        if (*(float *)(puVar2 + 0x44) <= 0.0) {
          *(undefined4 *)(puVar2 + 0xc) = 1;
        }
      }
      else {
        *(undefined4 *)(puVar2 + 0xc) = 0;
      }
      goto LAB_0040dbd3;
    }
    if (*(int *)(puVar2 + 0xc) != 3) goto LAB_0040dbd3;
    pfVar4 = *(float **)(puVar2 + 0x28);
    fVar7 = *pfVar4;
    uVar3 = 1;
    if (1 < g_dwVertexDst) {
      do {
        pfVar4 = pfVar4 + 1;
        fVar1 = *pfVar4 - fVar7;
        if (fVar1 < 0.0) {
          fVar1 = -fVar1;
        }
      } while ((fVar1 <= 0.015625) && (uVar3 = uVar3 + 1, uVar3 < g_dwVertexDst));
    }
    if (uVar3 != g_dwVertexDst) goto LAB_0040dbd3;
    if (fVar7 != 1.0) {
      if (fVar7 == 0.0) {
        *(undefined4 *)(puVar2 + 0xc) = 1;
        *(undefined4 *)(puVar2 + 0x44) = 0;
      }
      else {
        *(undefined4 *)(puVar2 + 0xc) = 2;
        *(float *)(puVar2 + 0x44) = fVar7;
      }
      goto LAB_0040dbd3;
    }
    if (!bVar6) {
      *(undefined4 *)(puVar2 + 0xc) = 0;
      goto LAB_0040dbd3;
    }
  }
  else if (!bVar6) {
    *(undefined4 *)(puVar2 + 0xc) = 0;
    goto LAB_0040dbd3;
  }
  *(undefined4 *)(puVar2 + 0xc) = 2;
  *(undefined4 *)(puVar2 + 0x44) = 0x3f800000;
LAB_0040dbd3:
  flags = 1;
  if (3 < *(int *)(puVar2 + 8)) {
    flags = 3;
  }
  if (2 < *(int *)(puVar2 + 0xc)) {
    flags = flags | 4;
  }
  *(int *)(puVar2 + 0x50) = param_2;
  *(undefined4 *)(puVar2 + 4) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(puVar2 + 0x48) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(puVar2 + 0x38) = *(undefined4 *)(param_1 + 0x20);
  rdCache_AddProcFace((void *)0x0,g_dwVertexDst,flags);
  return 1;
}
#undef local_18
#undef local_20
#undef local_24
#undef local_c

#endif

