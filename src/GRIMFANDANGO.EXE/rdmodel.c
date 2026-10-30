/* GRIMFANDANGO.EXE :: rdmodel.c
 * functions 0x00409580 .. 0x0040d880 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00409580  rdModel_ComputeMeshLighting ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
  #define local_8 (*(float (*)[2])(_frame + (0x20 - 0x8)))
  
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
    local_8[0] = 0.0;
  }
  else {
    local_8[0] = *(float *)(iVar5 + 0x40);
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
      if (local_8[0] < fVar1) {
        if (*(float *)(iVar5 + 0x48) < 0.0) {
          local_8[0] = 0.0;
        }
        else if (1.0 < *(float *)(iVar5 + 0x48)) {
          local_8[0] = 1.0;
        }
        else {
          local_8[0] = *(float *)(iVar5 + 0x48);
        }
      }
      *(float *)(iVar5 + 0x44) = local_8[0] * 63.0;
      (**(code **)(iVar5 + 0x14))(iVar5,param_1,local_8[0] * 63.0);
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
      *(float *)(iVar5 + 0x44) = local_8[0] * 63.0;
      (**(code **)(iVar5 + 0x14))(iVar5,param_1,local_8[0] * 63.0);
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
        if (local_8[0] < fVar1) {
          if (*(float *)(iVar5 + 0x48) < 0.0) {
            local_8[0] = 0.0;
          }
          else if (1.0 < *(float *)(iVar5 + 0x48)) {
            local_8[0] = 1.0;
          }
          else {
            local_8[0] = *(float *)(iVar5 + 0x48);
          }
        }
        *(float *)(iVar5 + 0x44) = local_8[0] * 63.0;
        (**(code **)(iVar5 + 0x14))(iVar5,param_1,local_8[0] * 63.0);
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
        *(float *)(iVar5 + 0x44) = local_8[0] * 63.0;
        (**(code **)(iVar5 + 0x14))(iVar5,param_1,local_8[0] * 63.0);
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
        if (local_8[0] < fVar1) {
          if (*(float *)(iVar5 + 0x48) < 0.0) {
            local_8[0] = 0.0;
          }
          else if (1.0 < *(float *)(iVar5 + 0x48)) {
            local_8[0] = 1.0;
          }
          else {
            local_8[0] = *(float *)(iVar5 + 0x48);
          }
        }
        *(float *)(iVar5 + 0x44) = local_8[0] * 63.0;
        (**(code **)(iVar5 + 0x14))(iVar5,param_1,local_8[0] * 63.0);
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
        *(float *)(iVar5 + 0x44) = local_8[0] * 63.0;
        (**(code **)(iVar5 + 0x14))(iVar5,param_1,local_8[0] * 63.0);
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

#endif


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
      *(undefined4 *)(*(int *)(UINT_007f0fd0 + 4) + 0x28 + *(int *)(param_1 + 0x4c) * 0x7c) = 6;
      *(undefined4 *)(*(int *)(UINT_007f0fd0 + 4) + 0x5c + *(int *)(param_1 + 0x4c) * 0x7c) =
           *(undefined4 *)(*(int *)(UINT_007f0fd0 + 4) + 0x5c + *(int *)(iVar3 + 0x4c) * 0x7c);
    }
    rdModel_DrawMesh((void *)(*(int *)(UINT_007f0fd0 + 4) + *(int *)(param_1 + 0x4c) * 0x7c),
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
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
  uint uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  void *pvVar9;
  uint uVar10;
  void *pvVar11;
  int iVar12;
  float fVar13;
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
  
  PTR_007f30a0 = mesh;
  if (*(int *)((int)mesh + 0x24) != 0) {
    a = matrix + 9;
    Vec3_Sub(local_48,a,(float *)((int)g_pRdCurrentCamera + 8));
    if (UINT_007f30a4 == 0) {
      UINT_007f1898 = 0;
    }
    else if ((DAT_00900068 & 1) == 0) {
      UINT_007f1898 = 1;
    }
    else {
      UINT_007f1898 =
           Frustum_TestSphere(*(undefined4 *)((int)g_pRdCurrentCamera + 0x48),local_48,
                              *(undefined4 *)((int)PTR_007f30a0 + 0x60));
    }
    if ((UINT_007f1898 != 2) &&
       ((UINT_007f3204 == 0 ||
        (-*(float *)((int)PTR_007f30a0 + 0x60) <=
         (*a - _DAT_007f3208) * _DAT_004ddb70 +
         (matrix[0xb] - _DAT_007f3210) * _DAT_004ddb78 +
         (matrix[10] - _DAT_007f320c) * _DAT_004ddb74)))) {
      Matrix_Mul34(local_30,(float *)((int)g_pRdCurrentCamera + 8),matrix);
      Matrix_TransformPoints
                (local_30,*(float **)((int)PTR_007f30a0 + 0x30),(float *)&DAT_007f18a0,
                 *(int *)((int)PTR_007f30a0 + 0x48));
      Matrix_Transpose(local_84,matrix);
      UINT_007f31e8 = *(uint *)((int)PTR_007f30a0 + 0x24);
      if ((int)UINT_007f1494 <= (int)UINT_007f31e8) {
        UINT_007f31e8 = UINT_007f1494;
      }
      UINT_007f30d8 = *(uint *)((int)PTR_007f30a0 + 0x2c);
      if ((int)UINT_007f189c <= (int)UINT_007f30d8) {
        UINT_007f30d8 = UINT_007f189c;
      }
      UINT_007f31e4 = *(uint *)((int)PTR_007f30a0 + 0x28);
      if (UINT_007f31e4 == 6) {
        UINT_007f31e4 = 6;
      }
      else if ((int)UINT_007f30dc <= (int)UINT_007f31e4) {
        UINT_007f31e4 = UINT_007f30dc;
      }
      _DAT_007f30b4 = &DAT_007f18a0;
      _DAT_007f30b8 = *(undefined4 *)((int)PTR_007f30a0 + 0x34);
      _DAT_007f30bc = *(undefined4 *)((int)PTR_007f30a0 + 0x3c);
      _DAT_007f30c0 = 0;
      UINT_007f1474 = (uint)&DAT_007f0fe8;
      switch(UINT_007f31e4) {
      case 2:
        uVar10 = 0;
        UINT_007f31fc = 0;
        local_a8 = 0;
        if (UINT_007f31f8 != 0) {
          local_ac = (uint)&UINT_007f1498;
          pvVar9 = g_pRdCurrentCamera;
          pvVar11 = PTR_007f30a0;
          do {
            piVar3 = *(int **)local_ac;
            if ((piVar3[2] != 0) &&
               (iVar12 = *piVar3,
               fVar13 = *(float *)((int)pvVar9 + iVar12 * 0xc + 0x160) - matrix[10],
               fVar4 = *(float *)((int)pvVar9 + (iVar12 + 0x1d) * 0xc) - *a,
               fVar5 = *(float *)((int)pvVar9 + iVar12 * 0xc + 0x164) - matrix[0xb],
               SQRT(fVar5 * fVar5 + fVar13 * fVar13 + fVar4 * fVar4) <
               (float)piVar3[0xd] + *(float *)((int)pvVar11 + 0x60))) {
              (&UINT_007f30e0)[uVar10] = (uint)piVar3;
              Vec3_Sub((float *)(&DAT_007f1598 + uVar10 * 0xc),
                       (float *)((int)pvVar9 + (*piVar3 + 0x1d) * 0xc),local_84);
              if (piVar3[1] != 2) {
                local_60 = 0;
                local_5c = 0;
                local_34 = local_58;
                local_58 = 0;
                local_a0[0] = -(float)piVar3[3];
                local_a0[1] = -(float)piVar3[4];
                local_a0[2] = -(float)piVar3[5];
                Vec3_Sub((float *)(&DAT_007f1168 + UINT_007f31fc * 0xc),local_a0,local_84);
                local_58 = local_34;
              }
              uVar10 = UINT_007f31fc + 1;
              pvVar9 = g_pRdCurrentCamera;
              pvVar11 = PTR_007f30a0;
              UINT_007f31fc = uVar10;
            }
            local_a8 = local_a8 + 1;
            local_ac = local_ac + 4;
          } while (local_a8 < UINT_007f31f8);
        }
        break;
      case 3:
        uVar10 = 0;
        UINT_007f31fc = 0;
        local_a8 = 0;
        pvVar9 = g_pRdCurrentCamera;
        pvVar11 = PTR_007f30a0;
        if (UINT_007f31f8 != 0) {
          local_ac = (uint)&UINT_007f1498;
          do {
            piVar3 = *(int **)local_ac;
            if (piVar3[2] != 0) {
              iVar12 = *piVar3;
              fVar13 = *(float *)((int)pvVar9 + (iVar12 + 0x1d) * 0xc) - *a;
              fVar5 = *(float *)((int)pvVar9 + iVar12 * 0xc + 0x160) - matrix[10];
              fVar4 = *(float *)((int)pvVar9 + iVar12 * 0xc + 0x164) - matrix[0xb];
              if (piVar3[1] < 2) {
                fVar13 = 0.0;
              }
              else {
                fVar13 = fVar4 * fVar4 + fVar5 * fVar5 + fVar13 * fVar13;
              }
              fVar4 = (float)piVar3[0xd] + *(float *)((int)pvVar11 + 0x60);
              if (fVar13 < fVar4 * fVar4) {
                (&UINT_007f30e0)[uVar10] = (uint)piVar3;
                Vec3_Sub((float *)(&DAT_007f1598 + uVar10 * 0xc),
                         (float *)((int)pvVar9 + (*piVar3 + 0x1d) * 0xc),local_84);
                uVar6 = local_58;
                if (piVar3[1] != 2) {
                  local_60 = 0;
                  local_5c = 0;
                  local_58 = 0;
                  local_a0[0] = -(float)piVar3[3];
                  local_a0[1] = -(float)piVar3[4];
                  local_a0[2] = -(float)piVar3[5];
                  Vec3_Sub((float *)(&DAT_007f1168 + UINT_007f31fc * 0xc),local_a0,local_84);
                }
                uVar10 = UINT_007f31fc + 1;
                pvVar9 = g_pRdCurrentCamera;
                pvVar11 = PTR_007f30a0;
                UINT_007f31fc = uVar10;
                local_58 = uVar6;
              }
            }
            local_a8 = local_a8 + 1;
            local_ac = local_ac + 4;
          } while (local_a8 < UINT_007f31f8);
        }
        fVar13 = rdLight_CalcVertexIntensities
                           ((int *)&UINT_007f30e0,(float *)&DAT_007f1598,IMG_ADDR(0x007f1168),uVar10,
                            *(int **)((int)pvVar11 + 0x44),*(uint *)((int)pvVar11 + 0x30),
                            *(float **)((int)pvVar11 + 0x38),*(float **)((int)pvVar11 + 0x3c),
                            *(uint *)((int)pvVar11 + 0x48),*(float *)((int)pvVar9 + 0x45c));
        *(float *)((int)mesh + 0x5c) = fVar13;
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
      local_54[0] = (float)UINT_008ddf84;
      local_54[1] = (float)UINT_008ddf88;
      local_54[2] = (float)UINT_008ddf8c;
      Vec3_Sub((float *)&DAT_007f0fd8,local_54,local_84);
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


/* ---- 0x0040d880  rdModel_AddMeshToCache ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 rdModel_AddMeshToCache(int param_1,int param_2)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  byte flags;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  bool bVar6;
  float fVar7;
  #define local_24 (*(float *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(float (*)[2])(_frame + (0x40 - 0x20)))
  #define local_18 (*(float (*)[3])(_frame + (0x40 - 0x18)))
  #define local_c (*(float (*)[3])(_frame + (0x40 - 0xc)))
  
  iVar2 = rdCache_AllocMesh();
  if (iVar2 == 0) {
    return 0;
  }
  uVar3 = *(uint *)(param_1 + 8);
  if ((int)UINT_007f31e8 < (int)*(uint *)(param_1 + 8)) {
    uVar3 = UINT_007f31e8;
  }
  *(uint *)(iVar2 + 8) = uVar3;
  uVar3 = *(uint *)(param_1 + 0xc);
  if ((int)UINT_007f31e4 < (int)*(uint *)(param_1 + 0xc)) {
    uVar3 = UINT_007f31e4;
  }
  *(uint *)(iVar2 + 0xc) = uVar3;
  uVar3 = *(uint *)(param_1 + 0x10);
  if ((int)UINT_007f30d8 < (int)*(uint *)(param_1 + 0x10)) {
    uVar3 = UINT_007f30d8;
  }
  *(uint *)(iVar2 + 0x10) = uVar3;
  if ((*(byte *)(param_1 + 4) & 0x10) != 0) {
    *(undefined4 *)(iVar2 + 0xc) = 1;
  }
  UINT_007f1490 = *(uint *)(iVar2 + 0x20);
  UINT_007f1478 = *(uint *)(iVar2 + 0x24);
  UINT_007f147c = *(uint *)(iVar2 + 0x28);
  _DAT_007f30a8 = *(undefined4 *)(param_1 + 0x14);
  _DAT_007f30ac = *(undefined4 *)(param_1 + 0x18);
  _DAT_007f30b0 = *(undefined4 *)(param_1 + 0x1c);
  if (UINT_007f1898 == 0) {
    rdPrimit3_CopyFaceVerts
              (*(undefined4 *)(iVar2 + 8),*(undefined4 *)(iVar2 + 0xc),*(undefined4 *)(iVar2 + 0x10)
               ,&DAT_007f30a8,&UINT_007f1468,param_1 + 0x28);
  }
  else {
    ((code *)rdPrimit3_ClipFace)(*(undefined4 *)((int)g_pRdCurrentCamera + 0x48));
  }
  if (UINT_007f1468 < 3) {
    return 0;
  }
  if (UINT_007f3204 != 0) {
    Vec3_Copy(local_c,(float *)&DAT_004ddb70,(float *)((int)g_pRdCurrentCamera + 8));
    Vec3_Sub(local_18,(float *)&DAT_007f3208,(float *)((int)g_pRdCurrentCamera + 8));
    uVar3 = Polygon_ClipToPlane(local_c,local_18,UINT_007f1474,UINT_007f1478,UINT_007f147c,
                                UINT_007f1468);
    if ((int)uVar3 < 2) {
      return 0;
    }
    UINT_007f1468 = uVar3;
    *(uint *)(iVar2 + 0x1c) = uVar3;
  }
  if (*(int *)(iVar2 + 0xc) == 2) {
    if (param_2 == 0) {
      fVar7 = *(float *)((int)g_pRdCurrentCamera + 0x45c);
      iVar5 = *(int *)((int)PTR_007f30a0 + 0x30);
      pfVar4 = (float *)(param_1 + 0x40);
    }
    else {
      local_24 = -*(float *)(param_1 + 0x40);
      local_20[0] = -*(float *)(param_1 + 0x44);
      local_20[1] = -*(float *)(param_1 + 0x48);
      fVar7 = *(float *)((int)g_pRdCurrentCamera + 0x45c);
      iVar5 = *(int *)((int)PTR_007f30a0 + 0x30);
      pfVar4 = &local_24;
    }
    fVar7 = rdKeyframe_InterpolateNode
                      ((int *)&UINT_007f30e0,IMG_ADDR(0x007f1598),IMG_ADDR(0x007f1168),UINT_007f31fc,param_1,pfVar4,iVar5,
                       fVar7);
    *(float *)(iVar2 + 0x44) = fVar7;
  }
  (**(code **)((int)g_pRdCurrentCamera + 0x50))(UINT_007f1490,UINT_007f1474,UINT_007f1468);
  if (((byte)g_dwRdroidFlags & 2) == 0) {
    *(undefined4 *)(iVar2 + 0x40) = 0;
  }
  else {
    *(undefined4 *)(iVar2 + 0x40) = *(undefined4 *)((int)g_pRdCurrentCamera + 0x54);
  }
  iVar5 = *(int *)(param_1 + 0x24);
  if ((iVar5 == -1) && (*(int *)(param_1 + 0x20) != 0)) {
    iVar5 = *(int *)(*(int *)(param_1 + 0x20) + 100);
  }
  *(int *)(iVar2 + 0x3c) = iVar5;
  bVar6 = UINT_004f5ec0 != UINT_004f5ec4;
  if (*(float *)(iVar2 + 0x40) < 1.0) {
    if (*(int *)(iVar2 + 0xc) == 2) {
      if ((*(float *)(iVar2 + 0x44) < 1.0) || (bVar6)) {
        if (*(float *)(iVar2 + 0x44) <= 0.0) {
          *(undefined4 *)(iVar2 + 0xc) = 1;
        }
      }
      else {
        *(undefined4 *)(iVar2 + 0xc) = 0;
      }
      goto LAB_0040dbd3;
    }
    if (*(int *)(iVar2 + 0xc) != 3) goto LAB_0040dbd3;
    pfVar4 = *(float **)(iVar2 + 0x28);
    fVar7 = *pfVar4;
    uVar3 = 1;
    if (1 < UINT_007f1468) {
      do {
        pfVar4 = pfVar4 + 1;
        fVar1 = *pfVar4 - fVar7;
        if (fVar1 < 0.0) {
          fVar1 = -fVar1;
        }
      } while ((fVar1 <= 0.015625) && (uVar3 = uVar3 + 1, uVar3 < UINT_007f1468));
    }
    if (uVar3 != UINT_007f1468) goto LAB_0040dbd3;
    if (fVar7 != 1.0) {
      if (fVar7 == 0.0) {
        *(undefined4 *)(iVar2 + 0xc) = 1;
        *(undefined4 *)(iVar2 + 0x44) = 0;
      }
      else {
        *(undefined4 *)(iVar2 + 0xc) = 2;
        *(float *)(iVar2 + 0x44) = fVar7;
      }
      goto LAB_0040dbd3;
    }
    if (!bVar6) {
      *(undefined4 *)(iVar2 + 0xc) = 0;
      goto LAB_0040dbd3;
    }
  }
  else if (!bVar6) {
    *(undefined4 *)(iVar2 + 0xc) = 0;
    goto LAB_0040dbd3;
  }
  *(undefined4 *)(iVar2 + 0xc) = 2;
  *(undefined4 *)(iVar2 + 0x44) = 0x3f800000;
LAB_0040dbd3:
  flags = 1;
  if (3 < *(int *)(iVar2 + 8)) {
    flags = 3;
  }
  if (2 < *(int *)(iVar2 + 0xc)) {
    flags = flags | 4;
  }
  *(int *)(iVar2 + 0x50) = param_2;
  *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(iVar2 + 0x48) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(iVar2 + 0x38) = *(undefined4 *)(param_1 + 0x20);
  rdCache_AddMesh((void *)0x0,UINT_007f1468,flags);
  return 1;
}
#undef local_18
#undef local_20
#undef local_24
#undef local_c

#endif

