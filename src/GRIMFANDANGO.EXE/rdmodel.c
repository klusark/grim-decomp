/* GRIMFANDANGO.EXE :: rdmodel.c
 * functions 0x00409580 .. 0x0040d880 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00409580  rdModel_ComputeMeshLighting ---- */
/* Rdcamera.c: picks the light level of a mesh from the current geometry/lighting/texture modes
   (gouraud, flat, per-vertex) and hands it to the mesh draw callback at +0x14 */

undefined4 rdModel_ComputeMeshLighting(byte *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  #define local_8 (*(float *)(_frame + (0x20 - 0x8)))
  
  iVar5 = (int)param_1;
  iVar8 = *(int *)((int)param_1 + 8);
  if (g_nRdroidGeometryMode <= *(int *)((int)param_1 + 8)) {
    iVar8 = g_nRdroidGeometryMode;
  }
  iVar11 = *(int *)((int)param_1 + 0xc);
  if (g_nRdroidLightingMode <= *(int *)((int)param_1 + 0xc)) {
    iVar11 = g_nRdroidLightingMode;
  }
  iVar9 = *(int *)((int)param_1 + 0x10);
  if (g_nRdroidTextureMode <= *(int *)((int)param_1 + 0x10)) {
    iVar9 = g_nRdroidTextureMode;
  }
  if (iVar8 == 0) {
    return 0;
  }
  iVar2 = *(int *)((int)param_1 + 0x38);
  if (iVar2 == 0) {
    param_1 = (byte *)0x0;
  }
  else {
    iVar6 = *(int *)((int)param_1 + 0x3c);
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
  if (((byte)g_dwRdroidFlags & 2) == 0) {
    local_8 = 0.0;
  }
  else {
    local_8 = *(float *)(iVar5 + 0x40);
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
      if (*(float *)(iVar5 + 0x48) < 0.0) {
        fVar1 = 0.0;
      }
      else if (1.0 < *(float *)(iVar5 + 0x48)) {
        fVar1 = 1.0;
      }
      else {
        fVar1 = *(float *)(iVar5 + 0x48);
      }
      if (local_8 < fVar1) {
        if (*(float *)(iVar5 + 0x48) < 0.0) {
          local_8 = 0.0;
        }
        else if (1.0 < *(float *)(iVar5 + 0x48)) {
          local_8 = 1.0;
        }
        else {
          local_8 = *(float *)(iVar5 + 0x48);
        }
      }
      *(float *)(iVar5 + 0x44) = local_8 * 63.0;
      (**(code **)(iVar5 + 0x14))(iVar5,param_1,local_8 * 63.0);
      return 1;
    case 2:
      fVar1 = *(float *)(iVar5 + 0x48) + *(float *)(iVar5 + 0x44);
      if (fVar1 < 0.0) {
        fVar3 = 0.0;
      }
      else {
        fVar3 = fVar1;
        if (1.0 < fVar1) {
          fVar3 = 1.0;
        }
      }
      if (local_8 < fVar3) {
        if (fVar1 < 0.0) {
          local_8 = 0.0;
        }
        else {
          local_8 = fVar1;
          if (1.0 < fVar1) {
            local_8 = 1.0;
          }
        }
      }
      *(float *)(iVar5 + 0x44) = local_8 * 63.0;
      (**(code **)(iVar5 + 0x14))(iVar5,param_1,local_8 * 63.0);
      return 1;
    case 3:
      uVar7 = 0;
      if (*(int *)(iVar5 + 0x1c) != 0) {
        do {
          fVar1 = *(float *)(iVar5 + 0x48) + *(float *)(*(int *)(iVar5 + 0x28) + uVar7 * 4);
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
          fVar4 = local_8;
          if (local_8 < fVar3) {
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
          *(float *)(*(int *)(iVar5 + 0x28) + iVar8) = fVar4 * 63.0;
        } while (uVar7 < *(uint *)(iVar5 + 0x1c));
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
        if (*(float *)(iVar5 + 0x48) < 0.0) {
          fVar1 = 0.0;
        }
        else if (1.0 < *(float *)(iVar5 + 0x48)) {
          fVar1 = 1.0;
        }
        else {
          fVar1 = *(float *)(iVar5 + 0x48);
        }
        if (local_8 < fVar1) {
          if (*(float *)(iVar5 + 0x48) < 0.0) {
            local_8 = 0.0;
          }
          else if (1.0 < *(float *)(iVar5 + 0x48)) {
            local_8 = 1.0;
          }
          else {
            local_8 = *(float *)(iVar5 + 0x48);
          }
        }
        *(float *)(iVar5 + 0x44) = local_8 * 63.0;
        (**(code **)(iVar5 + 0x14))(iVar5,param_1,local_8 * 63.0);
        return 1;
      case 2:
        fVar1 = *(float *)(iVar5 + 0x48) + *(float *)(iVar5 + 0x44);
        if (fVar1 < 0.0) {
          fVar3 = 0.0;
        }
        else {
          fVar3 = fVar1;
          if (1.0 < fVar1) {
            fVar3 = 1.0;
          }
        }
        if (local_8 < fVar3) {
          if (fVar1 < 0.0) {
            local_8 = 0.0;
          }
          else {
            local_8 = fVar1;
            if (1.0 < fVar1) {
              local_8 = 1.0;
            }
          }
        }
        *(float *)(iVar5 + 0x44) = local_8 * 63.0;
        (**(code **)(iVar5 + 0x14))(iVar5,param_1,local_8 * 63.0);
        return 1;
      case 3:
        uVar7 = 0;
        if (*(int *)(iVar5 + 0x1c) != 0) {
          do {
            fVar1 = *(float *)(iVar5 + 0x48) + *(float *)(*(int *)(iVar5 + 0x28) + uVar7 * 4);
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
            fVar4 = local_8;
            if (local_8 < fVar3) {
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
            *(float *)(*(int *)(iVar5 + 0x28) + iVar8) = fVar4 * 63.0;
          } while (uVar7 < *(uint *)(iVar5 + 0x1c));
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
        if (*(float *)(iVar5 + 0x48) < 0.0) {
          fVar1 = 0.0;
        }
        else if (1.0 < *(float *)(iVar5 + 0x48)) {
          fVar1 = 1.0;
        }
        else {
          fVar1 = *(float *)(iVar5 + 0x48);
        }
        if (local_8 < fVar1) {
          if (*(float *)(iVar5 + 0x48) < 0.0) {
            local_8 = 0.0;
          }
          else if (1.0 < *(float *)(iVar5 + 0x48)) {
            local_8 = 1.0;
          }
          else {
            local_8 = *(float *)(iVar5 + 0x48);
          }
        }
        *(float *)(iVar5 + 0x44) = local_8 * 63.0;
        (**(code **)(iVar5 + 0x14))(iVar5,param_1,local_8 * 63.0);
        return 1;
      case 2:
        fVar1 = *(float *)(iVar5 + 0x48) + *(float *)(iVar5 + 0x44);
        if (fVar1 < 0.0) {
          fVar3 = 0.0;
        }
        else {
          fVar3 = fVar1;
          if (1.0 < fVar1) {
            fVar3 = 1.0;
          }
        }
        if (local_8 < fVar3) {
          if (fVar1 < 0.0) {
            local_8 = 0.0;
          }
          else {
            local_8 = fVar1;
            if (1.0 < fVar1) {
              local_8 = 1.0;
            }
          }
        }
        *(float *)(iVar5 + 0x44) = local_8 * 63.0;
        (**(code **)(iVar5 + 0x14))(iVar5,param_1,local_8 * 63.0);
        return 1;
      case 3:
        uVar7 = 0;
        if (*(int *)(iVar5 + 0x1c) != 0) {
          do {
            fVar1 = *(float *)(iVar5 + 0x48) + *(float *)(*(int *)(iVar5 + 0x28) + uVar7 * 4);
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
            fVar4 = local_8;
            if (local_8 < fVar3) {
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
            *(float *)(*(int *)(iVar5 + 0x28) + iVar8) = fVar4 * 63.0;
          } while (uVar7 < *(uint *)(iVar5 + 0x1c));
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
  (**(code **)(iVar5 + 0x14))(iVar5,param_1,0);
switchD_00409661_default:
  return 1;
}
#undef local_8


/* ---- 0x00409d20  FUN_00409d20 ---- */
undefined4 FUN_00409d20(int param_1,int param_2)

{
  if (*(float *)(param_1 + 100) == *(float *)(param_2 + 100)) {
    return 0;
  }
  if (*(float *)(param_1 + 100) < *(float *)(param_2 + 100)) {
    return 1;
  }
  return 0xffffffff;
}

/* ---- 0x0040d140  rdModel_DrawNode ---- */
/* Recursive hierarchy walk (+0x58 child count, +0x5c first child, +0x60 sibling) drawing each
   node's mesh */

void rdModel_DrawNode(int param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  if ((*(int *)(param_1 + 0x4c) != -1) &&
     (*(int *)(*(int *)((int)g_pRdCurrentThing + 0x2c) + *(int *)(param_1 + 0x44) * 4) != 0)) {
    if ((*(byte *)(param_1 + 0x40) & 2) != 0) {
      iVar3 = *(int *)(param_1 + 0x54);
      bVar1 = *(byte *)(iVar3 + 0x40);
      while ((bVar1 & 2) != 0) {
        iVar3 = *(int *)(iVar3 + 0x54);
        bVar1 = *(byte *)(iVar3 + 0x40);
      }
      *(undefined4 *)(*(int *)(DAT_007f0fd0 + 4) + 0x28 + *(int *)(param_1 + 0x4c) * 0x7c) = 6;
      *(undefined4 *)(*(int *)(DAT_007f0fd0 + 4) + 0x5c + *(int *)(param_1 + 0x4c) * 0x7c) =
           *(undefined4 *)(*(int *)(DAT_007f0fd0 + 4) + 0x5c + *(int *)(iVar3 + 0x4c) * 0x7c);
    }
    rdModel_DrawMesh((void *)(*(int *)(DAT_007f0fd0 + 4) + *(int *)(param_1 + 0x4c) * 0x7c),
                     (float *)(*(int *)((int)g_pRdCurrentThing + 0x20) +
                              *(int *)(param_1 + 0x44) * 0x30));
  }
  if (*(int *)(param_1 + 0x58) != 0) {
    iVar3 = *(int *)(param_1 + 0x5c);
    uVar2 = 0;
    if (*(int *)(param_1 + 0x58) != 0) {
      do {
        if (*(int *)(*(int *)((int)g_pRdCurrentThing + 0x28) + *(int *)(iVar3 + 0x44) * 4) == 0) {
          rdModel_DrawNode(iVar3);
        }
        iVar3 = *(int *)(iVar3 + 0x60);
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(param_1 + 0x58));
    }
  }
  return;
}

/* ---- 0x0040d230  rdModel_DrawMesh ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl rdModel_DrawMesh(void *mesh,float *matrix)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *a;
  int iVar1;
  int iVar2;
  int *piVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  void *pvVar9;
  uint uVar10;
  void *pvVar11;
  int iVar12;
  float10 fVar13;
  #define local_ac (*(int **)(_frame + (0xc0 - 0xac)))
  #define local_a8 (*(uint *)(_frame + (0xc0 - 0xa8)))
  #define local_a0 (*(float *)(_frame + (0xc0 - 0xa0)))
  #define local_9c (*(float *)(_frame + (0xc0 - 0x9c)))
  #define local_98 (*(float *)(_frame + (0xc0 - 0x98)))
  #define local_90 (*(float *)(_frame + (0xc0 - 0x90)))
  #define local_8c (*(float *)(_frame + (0xc0 - 0x8c)))
  #define local_88 (*(float *)(_frame + (0xc0 - 0x88)))
  #define local_84 (*(float (*)[9])(_frame + (0xc0 - 0x84)))
  #define local_60 (*(undefined4 *)(_frame + (0xc0 - 0x60)))
  #define local_5c (*(undefined4 *)(_frame + (0xc0 - 0x5c)))
  #define local_58 (*(undefined4 *)(_frame + (0xc0 - 0x58)))
  #define local_54 (*(float *)(_frame + (0xc0 - 0x54)))
  #define local_50 (*(undefined4 *)(_frame + (0xc0 - 0x50)))
  #define local_4c (*(undefined4 *)(_frame + (0xc0 - 0x4c)))
  #define local_48 (*(float (*)[5])(_frame + (0xc0 - 0x48)))
  #define local_34 (*(undefined4 *)(_frame + (0xc0 - 0x34)))
  #define local_30 (*(float (*)[12])(_frame + (0xc0 - 0x30)))
  
  PTR_007f30a0 = mesh;
  if (*(int *)((int)mesh + 0x24) != 0) {
    a = matrix + 9;
    Vec3_Sub(local_48,a,(float *)((int)g_pRdCurrentCamera + 8));
    if (DAT_007f30a4 == 0) {
      DAT_007f1898 = 0;
    }
    else if ((DAT_00900068 & 1) == 0) {
      DAT_007f1898 = 1;
    }
    else {
      DAT_007f1898 = Frustum_TestSphere(*(undefined4 *)((int)g_pRdCurrentCamera + 0x48),local_48,
                                        *(undefined4 *)((int)PTR_007f30a0 + 0x60));
    }
    if ((DAT_007f1898 != 2) &&
       ((DAT_007f3204 == 0 ||
        (-*(float *)((int)PTR_007f30a0 + 0x60) <=
         (*a - _DAT_007f3208) * _DAT_004ddb70 +
         (matrix[0xb] - _DAT_007f3210) * _DAT_004ddb78 +
         (matrix[10] - _DAT_007f320c) * _DAT_004ddb74)))) {
      Matrix_Mul34(local_30,(float *)((int)g_pRdCurrentCamera + 8),matrix);
      Matrix_TransformPoints
                (local_30,*(float **)((int)PTR_007f30a0 + 0x30),(float *)&DAT_007f18a0,
                 *(int *)((int)PTR_007f30a0 + 0x48));
      Matrix_Transpose(local_84,matrix);
      DAT_007f31e8 = *(int *)((int)PTR_007f30a0 + 0x24);
      if (DAT_007f1494 <= DAT_007f31e8) {
        DAT_007f31e8 = DAT_007f1494;
      }
      DAT_007f30d8 = *(int *)((int)PTR_007f30a0 + 0x2c);
      if (DAT_007f189c <= DAT_007f30d8) {
        DAT_007f30d8 = DAT_007f189c;
      }
      DAT_007f31e4 = *(int *)((int)PTR_007f30a0 + 0x28);
      if (DAT_007f31e4 == 6) {
        DAT_007f31e4 = 6;
      }
      else if (DAT_007f30dc <= DAT_007f31e4) {
        DAT_007f31e4 = DAT_007f30dc;
      }
      _DAT_007f30b4 = &DAT_007f18a0;
      _DAT_007f30b8 = *(undefined4 *)((int)PTR_007f30a0 + 0x34);
      _DAT_007f30bc = *(undefined4 *)((int)PTR_007f30a0 + 0x3c);
      _DAT_007f30c0 = 0;
      DAT_007f1474 = &DAT_007f0fe8;
      switch(DAT_007f31e4) {
      case 2:
        iVar12 = 0;
        DAT_007f31fc = 0;
        local_a8 = 0;
        if (DAT_007f31f8 != 0) {
          local_ac = &DAT_007f1498;
          pvVar9 = g_pRdCurrentCamera;
          pvVar11 = PTR_007f30a0;
          do {
            piVar3 = (int *)*local_ac;
            if (piVar3[2] != 0) {
              iVar1 = *piVar3;
              local_90 = *(float *)((int)pvVar9 + iVar1 * 0xc + 0x160) - matrix[10];
              fVar4 = *(float *)((int)pvVar9 + (iVar1 + 0x1d) * 0xc) - *a;
              local_8c = *(float *)((int)pvVar9 + iVar1 * 0xc + 0x164) - matrix[0xb];
              local_88 = SQRT(local_8c * local_8c + local_90 * local_90 + fVar4 * fVar4);
              if (local_88 < (float)piVar3[0xd] + *(float *)((int)pvVar11 + 0x60)) {
                (&DAT_007f30e0)[iVar12] = piVar3;
                Vec3_Sub((float *)(&DAT_007f1598 + iVar12 * 0xc),
                         (float *)((int)pvVar9 + (*piVar3 + 0x1d) * 0xc),local_84);
                if (piVar3[1] != 2) {
                  local_60 = 0;
                  local_5c = 0;
                  local_34 = local_58;
                  local_58 = 0;
                  local_a0 = -(float)piVar3[3];
                  local_9c = -(float)piVar3[4];
                  local_98 = -(float)piVar3[5];
                  Vec3_Sub((float *)(&DAT_007f1168 + DAT_007f31fc * 0xc),&local_a0,local_84);
                  local_58 = local_34;
                }
                iVar12 = DAT_007f31fc + 1;
                pvVar9 = g_pRdCurrentCamera;
                pvVar11 = PTR_007f30a0;
                DAT_007f31fc = iVar12;
              }
            }
            local_a8 = local_a8 + 1;
            local_ac = local_ac + 1;
          } while (local_a8 < DAT_007f31f8);
        }
        break;
      case 3:
        iVar12 = 0;
        DAT_007f31fc = 0;
        local_a8 = 0;
        pvVar9 = g_pRdCurrentCamera;
        pvVar11 = PTR_007f30a0;
        if (DAT_007f31f8 != 0) {
          local_ac = &DAT_007f1498;
          do {
            piVar3 = (int *)*local_ac;
            if (piVar3[2] != 0) {
              iVar1 = *piVar3;
              fVar4 = *(float *)((int)pvVar9 + (iVar1 + 0x1d) * 0xc) - *a;
              fVar6 = *(float *)((int)pvVar9 + iVar1 * 0xc + 0x160) - matrix[10];
              fVar5 = *(float *)((int)pvVar9 + iVar1 * 0xc + 0x164) - matrix[0xb];
              if (piVar3[1] < 2) {
                fVar4 = 0.0;
              }
              else {
                fVar4 = fVar5 * fVar5 + fVar6 * fVar6 + fVar4 * fVar4;
              }
              fVar5 = (float)piVar3[0xd] + *(float *)((int)pvVar11 + 0x60);
              if (fVar4 < fVar5 * fVar5) {
                (&DAT_007f30e0)[iVar12] = piVar3;
                Vec3_Sub((float *)(&DAT_007f1598 + iVar12 * 0xc),
                         (float *)((int)pvVar9 + (*piVar3 + 0x1d) * 0xc),local_84);
                uVar7 = local_58;
                if (piVar3[1] != 2) {
                  local_60 = 0;
                  local_5c = 0;
                  local_58 = 0;
                  local_a0 = -(float)piVar3[3];
                  local_9c = -(float)piVar3[4];
                  local_98 = -(float)piVar3[5];
                  Vec3_Sub((float *)(&DAT_007f1168 + DAT_007f31fc * 0xc),&local_a0,local_84);
                }
                iVar12 = DAT_007f31fc + 1;
                pvVar9 = g_pRdCurrentCamera;
                pvVar11 = PTR_007f30a0;
                DAT_007f31fc = iVar12;
                local_58 = uVar7;
              }
            }
            local_a8 = local_a8 + 1;
            local_ac = local_ac + 1;
          } while (local_a8 < DAT_007f31f8);
        }
        fVar13 = (float10)rdKeyframe_Interpolate
                                    (&DAT_007f30e0,&DAT_007f1598,&DAT_007f1168,iVar12,
                                     *(undefined4 *)((int)pvVar11 + 0x44),
                                     *(undefined4 *)((int)pvVar11 + 0x30),
                                     *(undefined4 *)((int)pvVar11 + 0x38),
                                     *(undefined4 *)((int)pvVar11 + 0x3c),
                                     *(undefined4 *)((int)pvVar11 + 0x48),
                                     *(undefined4 *)((int)pvVar9 + 0x45c));
        *(float *)((int)mesh + 0x5c) = (float)fVar13;
        break;
      case 6:
        uVar10 = 0;
        if (*(int *)((int)mesh + 0x50) != 0) {
          puVar8 = (undefined4 *)(*(int *)((int)mesh + 0x40) + 0x30);
          do {
            *puVar8 = *(undefined4 *)((int)mesh + 0x5c);
            puVar8 = puVar8 + 0x13;
            uVar10 = uVar10 + 1;
          } while (uVar10 < *(uint *)((int)mesh + 0x50));
        }
      }
      local_54 = DAT_008ddf84;
      local_50 = DAT_008ddf88;
      local_4c = DAT_008ddf8c;
      Vec3_Sub((float *)&DAT_007f0fd8,&local_54,local_84);
      iVar12 = *(int *)((int)mesh + 0x40);
      uVar10 = 0;
      if (*(int *)((int)mesh + 0x50) != 0) {
        do {
          iVar1 = *(int *)((int)PTR_007f30a0 + 0x30);
          iVar2 = **(int **)(iVar12 + 0x18);
          if (*(float *)(iVar12 + 0x44) * (_DAT_007f0fdc - *(float *)(iVar1 + iVar2 * 0xc + 4)) +
              (_DAT_007f0fd8 - *(float *)(iVar1 + iVar2 * 0xc)) * *(float *)(iVar12 + 0x40) +
              *(float *)(iVar12 + 0x48) * (_DAT_007f0fe0 - *(float *)(iVar1 + 8 + iVar2 * 0xc)) <=
              0.0) {
            uVar7 = 1;
            if (((*(byte *)(iVar12 + 4) & 1) != 0) || (((byte)g_dwRdroidFlags & 1) == 0))
            goto LAB_0040d640;
          }
          else {
            uVar7 = 0;
LAB_0040d640:
            rdModel_AddMeshToCache(iVar12,uVar7);
          }
          iVar12 = iVar12 + 0x4c;
          uVar10 = uVar10 + 1;
        } while (uVar10 < *(uint *)((int)mesh + 0x50));
      }
    }
  }
  return;
}
#undef local_30
#undef local_34
#undef local_48
#undef local_4c
#undef local_50
#undef local_54
#undef local_58
#undef local_5c
#undef local_60
#undef local_84
#undef local_88
#undef local_8c
#undef local_90
#undef local_98
#undef local_9c
#undef local_a0
#undef local_a8
#undef local_ac


/* ---- 0x0040d880  rdModel_AddMeshToCache ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 rdModel_AddMeshToCache(int param_1,int param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  byte flags;
  int iVar3;
  uint uVar4;
  float *pfVar5;
  int iVar6;
  bool bVar7;
  float10 fVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  #define local_24 (*(float *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(float *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(float *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  iVar3 = rdCache_AllocMesh();
  if (iVar3 == 0) {
    return 0;
  }
  iVar6 = *(int *)(param_1 + 8);
  if (DAT_007f31e8 < *(int *)(param_1 + 8)) {
    iVar6 = DAT_007f31e8;
  }
  *(int *)(iVar3 + 8) = iVar6;
  iVar6 = *(int *)(param_1 + 0xc);
  if (DAT_007f31e4 < *(int *)(param_1 + 0xc)) {
    iVar6 = DAT_007f31e4;
  }
  *(int *)(iVar3 + 0xc) = iVar6;
  iVar6 = *(int *)(param_1 + 0x10);
  if (DAT_007f30d8 < *(int *)(param_1 + 0x10)) {
    iVar6 = DAT_007f30d8;
  }
  *(int *)(iVar3 + 0x10) = iVar6;
  if ((*(byte *)(param_1 + 4) & 0x10) != 0) {
    *(undefined4 *)(iVar3 + 0xc) = 1;
  }
  DAT_007f1490 = *(undefined4 *)(iVar3 + 0x20);
  DAT_007f1478 = *(undefined4 *)(iVar3 + 0x24);
  DAT_007f147c = *(undefined4 *)(iVar3 + 0x28);
  _DAT_007f30a8 = *(undefined4 *)(param_1 + 0x14);
  _DAT_007f30ac = *(undefined4 *)(param_1 + 0x18);
  _DAT_007f30b0 = *(undefined4 *)(param_1 + 0x1c);
  if (DAT_007f1898 == 0) {
    rdPrimit3_CopyFaceVerts
              (*(undefined4 *)(iVar3 + 8),*(undefined4 *)(iVar3 + 0xc),*(undefined4 *)(iVar3 + 0x10)
               ,&DAT_007f30a8,&DAT_007f1468,param_1 + 0x28);
  }
  else {
    ((code *)rdPrimit3_ClipFace)(*(undefined4 *)((int)g_pRdCurrentCamera + 0x48));
  }
  if (DAT_007f1468 < 3) {
    return 0;
  }
  if (DAT_007f3204 != 0) {
    Vec3_Copy(local_c,(float *)&DAT_004ddb70);
    Vec3_Sub(local_18,(float *)&DAT_007f3208,(float *)((int)g_pRdCurrentCamera + 8));
    uVar4 = Polygon_ClipToPlane(local_c,local_18,DAT_007f1474,DAT_007f1478,DAT_007f147c,DAT_007f1468
                               );
    if ((int)uVar4 < 2) {
      return 0;
    }
    DAT_007f1468 = uVar4;
    *(uint *)(iVar3 + 0x1c) = uVar4;
  }
  if (*(int *)(iVar3 + 0xc) == 2) {
    if (param_2 == 0) {
      uVar10 = *(undefined4 *)((int)g_pRdCurrentCamera + 0x45c);
      uVar9 = *(undefined4 *)((int)PTR_007f30a0 + 0x30);
      pfVar5 = (float *)(param_1 + 0x40);
    }
    else {
      local_24 = -*(float *)(param_1 + 0x40);
      local_20 = -*(float *)(param_1 + 0x44);
      local_1c = -*(float *)(param_1 + 0x48);
      uVar10 = *(undefined4 *)((int)g_pRdCurrentCamera + 0x45c);
      uVar9 = *(undefined4 *)((int)PTR_007f30a0 + 0x30);
      pfVar5 = &local_24;
    }
    fVar8 = (float10)rdKeyframe_InterpolateNode
                               (&DAT_007f30e0,&DAT_007f1598,&DAT_007f1168,DAT_007f31fc,param_1,
                                pfVar5,uVar9,uVar10);
    *(float *)(iVar3 + 0x44) = (float)fVar8;
  }
  (**(code **)((int)g_pRdCurrentCamera + 0x50))(DAT_007f1490,DAT_007f1474,DAT_007f1468);
  if (((byte)g_dwRdroidFlags & 2) == 0) {
    *(undefined4 *)(iVar3 + 0x40) = 0;
  }
  else {
    *(undefined4 *)(iVar3 + 0x40) = *(undefined4 *)((int)g_pRdCurrentCamera + 0x54);
  }
  iVar6 = *(int *)(param_1 + 0x24);
  if ((iVar6 == -1) && (*(int *)(param_1 + 0x20) != 0)) {
    iVar6 = *(int *)(*(int *)(param_1 + 0x20) + 100);
  }
  *(int *)(iVar3 + 0x3c) = iVar6;
  bVar7 = DAT_004f5ec0 != DAT_004f5ec4;
  if (*(float *)(iVar3 + 0x40) < 1.0) {
    if (*(int *)(iVar3 + 0xc) == 2) {
      if ((*(float *)(iVar3 + 0x44) < 1.0) || (bVar7)) {
        if (*(float *)(iVar3 + 0x44) <= 0.0) {
          *(undefined4 *)(iVar3 + 0xc) = 1;
        }
      }
      else {
        *(undefined4 *)(iVar3 + 0xc) = 0;
      }
      goto LAB_0040dbd3;
    }
    if (*(int *)(iVar3 + 0xc) != 3) goto LAB_0040dbd3;
    pfVar5 = *(float **)(iVar3 + 0x28);
    fVar1 = *pfVar5;
    uVar4 = 1;
    if (1 < DAT_007f1468) {
      do {
        pfVar5 = pfVar5 + 1;
        fVar2 = *pfVar5 - fVar1;
        if (fVar2 < 0.0) {
          fVar2 = -fVar2;
        }
      } while ((fVar2 <= 0.015625) && (uVar4 = uVar4 + 1, uVar4 < DAT_007f1468));
    }
    if (uVar4 != DAT_007f1468) goto LAB_0040dbd3;
    if (fVar1 != 1.0) {
      if (fVar1 == 0.0) {
        *(undefined4 *)(iVar3 + 0xc) = 1;
        *(undefined4 *)(iVar3 + 0x44) = 0;
      }
      else {
        *(undefined4 *)(iVar3 + 0xc) = 2;
        *(float *)(iVar3 + 0x44) = fVar1;
      }
      goto LAB_0040dbd3;
    }
    if (!bVar7) {
      *(undefined4 *)(iVar3 + 0xc) = 0;
      goto LAB_0040dbd3;
    }
  }
  else if (!bVar7) {
    *(undefined4 *)(iVar3 + 0xc) = 0;
    goto LAB_0040dbd3;
  }
  *(undefined4 *)(iVar3 + 0xc) = 2;
  *(undefined4 *)(iVar3 + 0x44) = 0x3f800000;
LAB_0040dbd3:
  flags = 1;
  if (3 < *(int *)(iVar3 + 8)) {
    flags = 3;
  }
  if (2 < *(int *)(iVar3 + 0xc)) {
    flags = flags | 4;
  }
  *(int *)(iVar3 + 0x50) = param_2;
  *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(iVar3 + 0x48) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(iVar3 + 0x38) = *(undefined4 *)(param_1 + 0x20);
  rdCache_AddMesh((void *)0x0,DAT_007f1468,flags);
  return 1;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_c

