/* GRIMFANDANGO.EXE :: rdprimitive.c
 * functions 0x00471ee0 .. 0x00472bd0 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00471ee0  rdPolyline_Draw ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Variable defined which should be unmapped: local_b0 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 rdPolyline_Draw(int param_1,float *param_2)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float fVar3;
  #define local_b0 (*(uint *)(_frame + (0xc0 - 0xb0)))
  #define local_a0 (*(uint *)(_frame + (0xc0 - 0xa0)))
  #define local_9c (*(uint *)(_frame + (0xc0 - 0x9c)))
  #define local_94 (*(uint *)(_frame + (0xc0 - 0x94)))
  #define local_90 (*(uint *)(_frame + (0xc0 - 0x90)))
  #define local_88 (*(uint *)(_frame + (0xc0 - 0x88)))
  #define local_84 (*(uint *)(_frame + (0xc0 - 0x84)))
  #define local_80 (*(uint *)(_frame + (0xc0 - 0x80)))
  #define local_7c (*(uint *)(_frame + (0xc0 - 0x7c)))
  #define local_78 (*(float (*)[9])(_frame + (0xc0 - 0x78)))
  #define local_54 (*(uint *)(_frame + (0xc0 - 0x54)))
  #define local_50 (*(uint *)(_frame + (0xc0 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0xc0 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0xc0 - 0x48)))
  #define local_40 (*(uint *)(_frame + (0xc0 - 0x40)))
  #define local_38 (*(uint *)(_frame + (0xc0 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0xc0 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0xc0 - 0x30)))
  #define local_2c (*(undefined1 (*)[12])(_frame + (0xc0 - 0x2c)))
  #define local_20 (*(uint *)(_frame + (0xc0 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0xc0 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0xc0 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0xc0 - 0x14)))
  
  iVar1 = *(int *)(param_1 + 4);
  local_20 = (uint)&DAT_007f4e80;
  local_18 = 0;
  local_14 = 0;
  Matrix_Mul34(local_78,(float *)((int)g_pRdCurrentCamera + 8),param_2);
  local_38 = 0;
  local_34 = *(uint *)(iVar1 + 0x20);
  local_30 = 0;
  Vec3_Sub((float *)&local_84,(float *)&local_38,local_78);
  _DAT_007f4e84 = PUN(float,local_80) - -0.001;
  _DAT_007f4e80 = PUN(float,local_84) - *(float *)(iVar1 + 0x28);
  _DAT_007f4e88 = PUN(float,local_7c) - *(float *)(iVar1 + 0x28);
  _DAT_007f4e8c = PUN(float,local_84) + *(float *)(iVar1 + 0x28);
  _DAT_007f4e94 = PUN(float,local_7c) - *(float *)(iVar1 + 0x28);
  _DAT_007f4e98 = PUN(float,local_84) + *(float *)(iVar1 + 0x28);
  _DAT_007f4ea0 = PUN(float,local_7c) + *(float *)(iVar1 + 0x28);
  _DAT_007f4ea4 = PUN(float,local_84) - *(float *)(iVar1 + 0x28);
  _DAT_007f4eac = PUN(float,local_7c) + *(float *)(iVar1 + 0x28);
  local_1c = *(uint *)(iVar1 + 0xd4);
  _DAT_007f4e90 = _DAT_007f4e84;
  _DAT_007f4e9c = _DAT_007f4e84;
  _DAT_007f4ea8 = _DAT_007f4e84;
  rdPolyline_DrawFace(param_1,iVar1 + 0x84,&DAT_007f4e80,local_2c);
  _DAT_007f4e84 = PUN(float,local_50) - -0.001;
  _DAT_007f4e80 = PUN(float,local_54) - *(float *)(iVar1 + 0x24);
  _DAT_007f4e88 = PUN(float,local_4c) - *(float *)(iVar1 + 0x24);
  _DAT_007f4e8c = PUN(float,local_54) + *(float *)(iVar1 + 0x24);
  _DAT_007f4e94 = PUN(float,local_4c) - *(float *)(iVar1 + 0x24);
  _DAT_007f4e98 = PUN(float,local_54) + *(float *)(iVar1 + 0x24);
  _DAT_007f4ea0 = PUN(float,local_4c) + *(float *)(iVar1 + 0x24);
  _DAT_007f4ea4 = PUN(float,local_54) - *(float *)(iVar1 + 0x24);
  _DAT_007f4eac = PUN(float,local_4c) + *(float *)(iVar1 + 0x24);
  local_1c = *(uint *)(iVar1 + 0xd4);
  _DAT_007f4e90 = _DAT_007f4e84;
  _DAT_007f4e9c = _DAT_007f4e84;
  _DAT_007f4ea8 = _DAT_007f4e84;
  rdPolyline_DrawFace(param_1,iVar1 + 0x84,&DAT_007f4e80,local_2c);
  local_90 = PUN(uint,(float)(PUN(float,local_84) - PUN(float,local_54)));
  fVar2 = PUN(float,local_7c) - PUN(float,local_4c);
  fVar3 = SQRT(fVar2 * fVar2 + PUN(float,local_90) * PUN(float,local_90));
  local_9c = PUN(uint,(float)Math_AsinDegreesSeries(-PUN(float,local_90) / fVar3));
  if (fVar2 < 0.0) {
    if (PUN(float,local_90) <= 0.0) {
      local_9c = PUN(uint,(float)-(PUN(float,local_9c) - -180.0));
    }
    else {
      local_9c = PUN(uint,(float)(180.0 - PUN(float,local_9c)));
    }
  }
  Math_SinCosTable(local_9c,&local_88,&local_94);
  local_48 = PUN(uint,(float)-*(float *)(iVar1 + 0x24));
  local_40 = *(uint *)(iVar1 + 0x24);
  _DAT_007f4e84 = PUN(float,local_80);
  _DAT_007f4e80 =
       (*(float *)(iVar1 + 0x28) * PUN(float,local_94) - PUN(float,local_88) * fVar3) + PUN(float,local_54);
  _DAT_007f4e88 =
       *(float *)(iVar1 + 0x28) * PUN(float,local_88) + PUN(float,local_94) * fVar3 + PUN(float,local_4c);
  _DAT_007f4e8c =
       (-*(float *)(iVar1 + 0x28) * PUN(float,local_94) - PUN(float,local_88) * fVar3) + PUN(float,local_54);
  local_90 = 0;
  _DAT_007f4e94 =
       -*(float *)(iVar1 + 0x28) * PUN(float,local_88) + PUN(float,local_94) * fVar3 + PUN(float,local_4c);
  _DAT_007f4e98 = (PUN(float,local_48) * PUN(float,local_94) - 0.0) + PUN(float,local_54);
  _DAT_007f4ea0 = PUN(float,local_48) * PUN(float,local_88) + 0.0 + PUN(float,local_4c);
  _DAT_007f4e90 = PUN(float,local_80);
  _DAT_007f4e9c = PUN(float,local_50);
  _DAT_007f4ea4 = (PUN(float,local_40) * PUN(float,local_94) - 0.0) + PUN(float,local_54);
  _DAT_007f4eac = PUN(float,local_40) * PUN(float,local_88) + 0.0 + PUN(float,local_4c);
  _DAT_007f4ea8 = PUN(float,local_50);
  local_1c = *(uint *)(iVar1 + 0xd0);
  rdPolyline_DrawFace(param_1,iVar1 + 0x38,&DAT_007f4e80,local_2c);
  return 1;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_40
#undef local_48
#undef local_4c
#undef local_50
#undef local_54
#undef local_78
#undef local_7c
#undef local_80
#undef local_84
#undef local_88
#undef local_90
#undef local_94
#undef local_9c
#undef local_a0
#undef local_b0

#endif


/* ---- 0x00472360  rdPolyline_DrawFace ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Allocates a cache mesh for one polyline face, clips and adds it */

void rdPolyline_DrawFace(int param_1,int param_2,undefined4 param_3,undefined4 *param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  byte flags;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  bool bVar9;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  iVar3 = rdCache_AllocMesh();
  if (iVar3 != 0) {
    local_20 = (uint)&DAT_007f4d00;
    local_4 = *(uint *)(iVar3 + 0x20);
    local_1c = *(uint *)(iVar3 + 0x24);
    local_18 = *(uint *)(iVar3 + 0x28);
    *param_4 = *(undefined4 *)(param_2 + 0x14);
    param_4[1] = *(undefined4 *)(param_2 + 0x18);
    param_4[2] = *(undefined4 *)(param_2 + 0x1c);
    iVar1 = *(int *)(param_2 + 8);
    iVar8 = g_nRdroidGeometryMode;
    if (iVar1 <= g_nRdroidGeometryMode) {
      iVar8 = iVar1;
    }
    iVar6 = *(int *)(param_1 + 0x38);
    if ((iVar8 < *(int *)(param_1 + 0x38)) && (iVar6 = iVar1, g_nRdroidGeometryMode < iVar1)) {
      iVar6 = g_nRdroidGeometryMode;
    }
    *(int *)(iVar3 + 8) = iVar6;
    if ((((byte)g_dwRdroidFlags & 2) == 0) || (*(float *)((int)g_pRdCurrentCamera + 0x54) < 1.0)) {
      iVar1 = *(int *)(param_2 + 0xc);
      iVar8 = g_nRdroidLightingMode;
      if (iVar1 <= g_nRdroidLightingMode) {
        iVar8 = iVar1;
      }
      iVar4 = *(int *)(param_1 + 0x3c);
      if ((iVar8 < iVar4) && (iVar4 = iVar1, g_nRdroidLightingMode < iVar1)) {
        iVar4 = g_nRdroidLightingMode;
      }
      *(int *)(iVar3 + 0xc) = iVar4;
    }
    else {
      *(undefined4 *)(iVar3 + 0xc) = 0;
    }
    iVar1 = *(int *)(param_2 + 0x10);
    iVar8 = g_nRdroidTextureMode;
    if (iVar1 <= g_nRdroidTextureMode) {
      iVar8 = iVar1;
    }
    iVar4 = *(int *)(param_1 + 0x40);
    if ((iVar8 < *(int *)(param_1 + 0x40)) && (iVar4 = iVar1, g_nRdroidTextureMode < iVar1)) {
      iVar4 = g_nRdroidTextureMode;
    }
    *(int *)(iVar3 + 0x10) = iVar4;
    rdPrimit3_ClipFace(*(undefined4 *)((int)g_pRdCurrentCamera + 0x48),iVar6,
                       *(undefined4 *)(iVar3 + 0xc),iVar4,param_4,&local_2c,param_2 + 0x28);
    if (2 < local_2c) {
      (**(code **)((int)g_pRdCurrentCamera + 0x50))(local_4,local_20,local_2c);
      if (((byte)g_dwRdroidFlags & 2) == 0) {
        *(undefined4 *)(iVar3 + 0x40) = 0;
      }
      else {
        *(undefined4 *)(iVar3 + 0x40) = *(undefined4 *)((int)g_pRdCurrentCamera + 0x54);
      }
      iVar1 = *(int *)(iVar3 + 0xc);
      if (iVar1 != 0) {
        bVar9 = UINT_004f5ec0 != UINT_004f5ec4;
        if (*(float *)(iVar3 + 0x40) < 1.0) {
          if (iVar1 == 2) {
            if ((*(float *)(iVar3 + 0x44) < 1.0) || (bVar9)) {
              if (*(float *)(iVar3 + 0x44) <= 0.0) {
                *(undefined4 *)(iVar3 + 0xc) = 1;
              }
            }
            else {
              *(undefined4 *)(iVar3 + 0xc) = 0;
            }
          }
          else if (iVar1 == 3) {
            pfVar7 = *(float **)(iVar3 + 0x28);
            fVar2 = *pfVar7;
            uVar5 = 1;
            if (1 < local_2c) {
              do {
                pfVar7 = pfVar7 + 1;
                if (*pfVar7 != fVar2) break;
                uVar5 = uVar5 + 1;
              } while (uVar5 < local_2c);
            }
            if (uVar5 == local_2c) {
              if (fVar2 == 1.0) {
                if (bVar9) {
                  *(undefined4 *)(iVar3 + 0xc) = 2;
                  *(undefined4 *)(iVar3 + 0x44) = 0x3f800000;
                }
                else {
                  *(undefined4 *)(iVar3 + 0xc) = 0;
                }
              }
              else if (fVar2 == 0.0) {
                *(undefined4 *)(iVar3 + 0xc) = 1;
                *(undefined4 *)(iVar3 + 0x44) = 0;
              }
              else {
                *(undefined4 *)(iVar3 + 0xc) = 2;
                *(float *)(iVar3 + 0x44) = fVar2;
              }
            }
          }
        }
        else if (bVar9) {
          *(undefined4 *)(iVar3 + 0xc) = 2;
          *(undefined4 *)(iVar3 + 0x44) = 0x3f800000;
        }
        else {
          *(undefined4 *)(iVar3 + 0xc) = 0;
        }
      }
      flags = 1;
      if (3 < *(int *)(iVar3 + 8)) {
        flags = 3;
      }
      if (2 < *(int *)(iVar3 + 0xc)) {
        flags = flags | 4;
      }
      *(undefined4 *)(iVar3 + 0x3c) = *(undefined4 *)(param_1 + 0x30);
      *(undefined4 *)(iVar3 + 0x50) = 0;
      *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(param_2 + 4);
      *(undefined4 *)(iVar3 + 0x48) = *(undefined4 *)(param_2 + 0x30);
      *(undefined4 *)(iVar3 + 0x38) = *(undefined4 *)(param_2 + 0x20);
      rdCache_AddMesh((void *)0x0,local_2c,flags);
    }
  }
  return;
}
#undef local_18
#undef local_1c
#undef local_20
#undef local_2c
#undef local_4

#endif


/* ---- 0x00472640  rdSprite_DrawThing ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Billboard: builds a camera-facing matrix for the thing position and draws the sprite */

int __cdecl rdSprite_DrawThing(void *thing,void *sprite)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  uint vertexCount;
  uint *puVar3;
  #define local_40 (*(uint *)(_frame + (0x50 - 0x40)))
  #define local_3c (*(float (*)[3])(_frame + (0x50 - 0x3c)))
  #define local_30 (*(float (*)[12])(_frame + (0x50 - 0x30)))
  
  iVar1 = *(int *)((int)thing + 4);
  Vec3_Sub(local_3c,(float *)((int)sprite + 0x24),(float *)((int)g_pRdCurrentCamera + 8));
  if ((DAT_00900068 & 2) == 0) {
    iVar2 = *(int *)((int)thing + 0x44);
  }
  else {
    iVar2 = Frustum_TestSphere(*(undefined4 *)((int)g_pRdCurrentCamera + 0x48),local_3c,
                               *(undefined4 *)(iVar1 + 0x3c));
  }
  if (iVar2 == 2) {
    return 0;
  }
  Matrix_Mul34(local_30,(float *)((int)g_pRdCurrentCamera + 8),sprite);
  if (((byte)g_dwRdroidFlags & 2) == 0) {
    sprite = (void *)0x0;
  }
  else {
    sprite = *(void **)((int)g_pRdCurrentCamera + 0x54);
  }
  if (PUN(float,sprite) < 1.0) {
    if (0.0 < PUN(float,sprite)) {
      thing = *(void **)(iVar1 + 0x20);
    }
    else {
      thing = (void *)0x1;
    }
  }
  else {
    thing = (void *)0x0;
  }
  if ((int)*(void **)(iVar1 + 0x20) <= (int)thing) {
    thing = *(void **)(iVar1 + 0x20);
  }
  Matrix_TransformPoints
            (local_30,*(float **)(iVar1 + 0x28),(float *)&UINT_007f5180,*(int *)(iVar1 + 0x24));
  local_40 = 0;
  if (*(int *)(iVar1 + 0x24) != 0) {
    puVar3 = &UINT_007f5184;
    do {
      iVar2 = rdCache_AllocMesh();
      if (iVar2 == 0) {
        return 0;
      }
      _DAT_007f5000 = PUN(float,puVar3[-1]) - *(float *)(iVar1 + 0x34);
      _DAT_007f5004 = *puVar3;
      _DAT_007f5008 = PUN(float,puVar3[1]) - *(float *)(iVar1 + 0x34);
      _DAT_007f5010 = *puVar3;
      _DAT_007f500c = PUN(float,puVar3[-1]) + *(float *)(iVar1 + 0x34);
      _DAT_007f501c = *puVar3;
      _DAT_007f5014 = PUN(float,puVar3[1]) - *(float *)(iVar1 + 0x34);
      _DAT_007f5028 = *puVar3;
      _DAT_007f5018 = PUN(float,puVar3[-1]) + *(float *)(iVar1 + 0x34);
      _DAT_007f5020 = PUN(float,puVar3[1]) + *(float *)(iVar1 + 0x34);
      _DAT_007f5024 = PUN(float,puVar3[-1]) - *(float *)(iVar1 + 0x34);
      _DAT_007f502c = PUN(float,puVar3[1]) + *(float *)(iVar1 + 0x34);
      vertexCount = rdClip_Face3_Pos_2(*(undefined4 *)((int)g_pRdCurrentCamera + 0x48),&DAT_007f5000
                                       ,4);
      if (2 < vertexCount) {
        (**(code **)((int)g_pRdCurrentCamera + 0x50))
                  (*(undefined4 *)(iVar2 + 0x20),&DAT_007f5000,vertexCount);
        *(void **)(iVar2 + 0xc) = thing;
        *(void **)(iVar2 + 0x40) = sprite;
        *(undefined4 *)(iVar2 + 8) = 3;
        *(undefined4 *)(iVar2 + 4) = 0;
        *(undefined4 *)(iVar2 + 0x38) = *(undefined4 *)(iVar1 + 0x38);
        *(undefined4 *)(iVar2 + 0x3c) = *(undefined4 *)(*(int *)(iVar1 + 0x2c) + local_40 * 4);
        *(undefined4 *)(iVar2 + 0x50) = 0;
        rdCache_AddMesh((void *)0x0,vertexCount,1);
      }
      local_40 = local_40 + 1;
      puVar3 = puVar3 + 3;
    } while (local_40 < *(uint *)(iVar1 + 0x24));
  }
  return 1;
}
#undef local_30
#undef local_3c
#undef local_40

#endif


/* ---- 0x004728a0  rdPolyline_New ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Allocates a 0xb8-byte polyline (RDroid Primitiv*.c) and initialises it */

int rdPolyline_New(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                  undefined4 param_9,undefined4 param_10)

{
  int iVar1;
  
  iVar1 = (*g_pSvcRdroid->pAlloc)(0xb8,s_C__grimjedi_Libs_RDroid_Primitiv_004dde64,DAT_004dde5c + 4)
  ;
  if (iVar1 == 0) {
    return 0;
  }
  rdPolyline_Init(iVar1,param_2,param_1,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                  param_10);
  return iVar1;
}
#endif


/* ---- 0x00472910  rdPolyline_Init ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Copies the 31-char name and builds the vertex ring for the given radius/segment counts */

undefined4
rdPolyline_Init(int param_1,int param_2,undefined4 param_3,char *param_4,undefined4 param_5,
               undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
               undefined4 param_10,undefined4 *param_11)

{
  float fVar1;
  float fVar2;
  void *pvVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  if (param_2 != 0) {
    strncpy(param_1,param_2,0x1f);
    *(undefined1 *)(param_1 + 0x1f) = 0;
  }
  *(undefined4 *)(param_1 + 0x4c) = param_5;
  *(undefined4 *)(param_1 + 0x20) = param_3;
  *(undefined4 *)(param_1 + 0x50) = param_6;
  *(undefined4 *)(param_1 + 0xac) = *param_11;
  *(undefined4 *)(param_1 + 0xb0) = param_11[1];
  *(undefined4 *)(param_1 + 0xb4) = param_11[2];
  *(undefined4 *)(param_1 + 0x68) = param_8;
  *(undefined4 *)(param_1 + 100) = param_7;
  *(undefined4 *)(param_1 + 0x60) = 1;
  *(undefined4 *)(param_1 + 0x6c) = param_9;
  *(undefined4 *)(param_1 + 0x8c) = param_10;
  pvVar3 = rdMaterial_Load(param_4,0,0);
  *(void **)(param_1 + 0x7c) = pvVar3;
  if (pvVar3 == (void *)0x0) {
    return 0;
  }
  *(undefined4 *)(param_1 + 0x70) = 4;
  iVar4 = (*g_pSvcRdroid->pAlloc)
                    (0x10,s_C__grimjedi_Libs_RDroid_Primitiv_004dde64,DAT_004dde60 + 0x2a);
  *(int *)(param_1 + 0x74) = iVar4;
  if (iVar4 != 0) {
    if (*(int *)(param_1 + 100) < 4) {
      uVar5 = 0;
      if (*(int *)(param_1 + 0x70) != 0) {
        do {
          *(uint *)(*(int *)(param_1 + 0x74) + uVar5 * 4) = uVar5;
          uVar5 = uVar5 + 1;
        } while (uVar5 < *(uint *)(param_1 + 0x70));
      }
LAB_00472af2:
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x4c) * 0.5;
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x50) * 0.5;
      *(undefined4 *)(param_1 + 0x84) = 0;
      *(undefined4 *)(param_1 + 0x88) = 0;
      *(float *)(param_1 + 0x24) =
           SQRT(*(float *)(param_1 + 0x58) * *(float *)(param_1 + 0x58) +
                *(float *)(param_1 + 0x54) * *(float *)(param_1 + 0x54));
      return 1;
    }
    iVar4 = (*g_pSvcRdroid->pAlloc)
                      (*(int *)(param_1 + 0x70) << 2,s_C__grimjedi_Libs_RDroid_Primitiv_004dde64,
                       DAT_004dde60 + 0x31);
    *(int *)(param_1 + 0x78) = iVar4;
    if (iVar4 != 0) {
      uVar5 = 0;
      if (*(int *)(param_1 + 0x70) != 0) {
        do {
          *(uint *)(*(int *)(param_1 + 0x74) + uVar5 * 4) = uVar5;
          *(uint *)(*(int *)(param_1 + 0x78) + uVar5 * 4) = uVar5;
          uVar5 = uVar5 + 1;
        } while (uVar5 < *(uint *)(param_1 + 0x70));
      }
      puVar6 = (undefined4 *)
               (*g_pSvcRdroid->pAlloc)
                         (*(int *)(param_1 + 0x70) << 3,s_C__grimjedi_Libs_RDroid_Primitiv_004dde64,
                          DAT_004dde60 + 0x3d);
      *(undefined4 **)(param_1 + 0xa8) = puVar6;
      if (puVar6 != (undefined4 *)0x0) {
        iVar4 = *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x7c) + 0x68) + 0x1c) + 0x1c);
        uVar5 = *(uint *)(iVar4 + 0x10);
        fVar1 = (float)*(uint *)(iVar4 + 0xc) - 0.5;
        *puVar6 = 0x3f000000;
        fVar2 = (float)uVar5 - 0.5;
        *(float *)(*(int *)(param_1 + 0xa8) + 4) = fVar2;
        *(float *)(*(int *)(param_1 + 0xa8) + 8) = fVar1;
        *(float *)(*(int *)(param_1 + 0xa8) + 0xc) = fVar2;
        *(float *)(*(int *)(param_1 + 0xa8) + 0x10) = fVar1;
        *(undefined4 *)(*(int *)(param_1 + 0xa8) + 0x14) = 0x3f000000;
        *(undefined4 *)(*(int *)(param_1 + 0xa8) + 0x18) = 0x3f000000;
        *(undefined4 *)(*(int *)(param_1 + 0xa8) + 0x1c) = 0x3f000000;
        goto LAB_00472af2;
      }
    }
  }
  return 0;
}
#endif


/* ---- 0x00472b50  rdSprite_Free ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void rdSprite_Free(int param_1)

{
  if (param_1 != 0) {
    rdSprite_FreeContents(param_1);
    (*g_pSvcRdroid->pFree)(param_1);
  }
  return;
}
#endif


/* ---- 0x00472b70  rdSprite_FreeContents ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void rdSprite_FreeContents(int param_1)

{
  if (*(int *)(param_1 + 0xa8) != 0) {
    (*g_pSvcRdroid->pFree)(*(int *)(param_1 + 0xa8));
    *(undefined4 *)(param_1 + 0xa8) = 0;
  }
  if (*(int *)(param_1 + 0x74) != 0) {
    (*g_pSvcRdroid->pFree)(*(int *)(param_1 + 0x74));
    *(undefined4 *)(param_1 + 0x74) = 0;
  }
  if (*(int *)(param_1 + 0x78) != 0) {
    (*g_pSvcRdroid->pFree)(*(int *)(param_1 + 0x78));
    *(undefined4 *)(param_1 + 0x78) = 0;
  }
  return;
}
#endif


/* ---- 0x00472bd0  rdSprite_Draw ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Frustum tests the sprite, builds the quad in the cache and clips it */

undefined4 rdSprite_Draw(int param_1,float *param_2)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  byte flags;
  uint uVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  bool bVar10;
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
  #define local_4c (*(uint *)(_frame + (0x90 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x90 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x90 - 0x44)))
  #define local_30 (*(uint *)(_frame + (0x90 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x90 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x90 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x90 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x90 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x90 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x90 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x90 - 0x14)))
  
  iVar1 = *(int *)(param_1 + 4);
  Vec3_Sub((float *)&local_64,param_2 + 9,(float *)((int)g_pRdCurrentCamera + 8));
  Vec3_Copy((float *)&local_70,(float *)(iVar1 + 0xac),param_2);
  Vec3_Transform((float *)&local_70,(float *)((int)g_pRdCurrentCamera + 8));
  if (0.0 <= PUN(float,local_70)) {
    local_78 = PUN(uint,(float)-*(float *)(iVar1 + 0x54));
  }
  else {
    local_78 = *(uint *)(iVar1 + 0x54);
  }
  if ((DAT_00900068 & 2) == 0) {
    iVar4 = *(int *)(param_1 + 0x44);
  }
  else {
    iVar4 = Frustum_TestSphere(*(undefined4 *)((int)g_pRdCurrentCamera + 0x48),&local_64,
                               *(undefined4 *)(iVar1 + 0x24));
  }
  if ((iVar4 != 2) && (iVar4 = rdCache_AllocMesh(), iVar4 != 0)) {
    _DAT_007f5f0c = PUN(float,local_6c) + PUN(float,local_60);
    _DAT_007f5f10 = PUN(float,local_68) + PUN(float,local_5c);
    _DAT_007f5f08 = PUN(float,local_64) + (PUN(float,local_70) - PUN(float,local_78));
    _DAT_007f5f14 = PUN(float,local_64) + PUN(float,local_78) + PUN(float,local_70);
    _DAT_007f5f20 = PUN(float,local_64) + PUN(float,local_78) + PUN(float,local_70);
    _DAT_007f5f28 =
         PUN(float,local_5c) + *(float *)(iVar1 + 0x58) + *(float *)(iVar1 + 0x58) + PUN(float,local_68);
    _DAT_007f5f2c = PUN(float,local_64) + (PUN(float,local_70) - PUN(float,local_78));
    _DAT_007f5f34 =
         PUN(float,local_5c) + *(float *)(iVar1 + 0x58) + *(float *)(iVar1 + 0x58) + PUN(float,local_68);
    local_2c = *(uint *)(iVar1 + 0x70);
    local_28 = *(uint *)(iVar1 + 0x74);
    local_24 = *(uint *)(iVar1 + 0x78);
    local_20 = (uint)&DAT_007f5f08;
    local_1c = *(uint *)(iVar1 + 0xa8);
    local_18 = 0;
    local_14 = 0;
    local_4c = (uint)&DAT_007f5d88;
    local_30 = *(uint *)(iVar4 + 0x20);
    local_48 = *(uint *)(iVar4 + 0x24);
    local_44 = *(uint *)(iVar4 + 0x28);
    iVar2 = *(int *)(iVar1 + 100);
    iVar9 = g_nRdroidGeometryMode;
    if (iVar2 <= g_nRdroidGeometryMode) {
      iVar9 = iVar2;
    }
    iVar7 = *(int *)(param_1 + 0x38);
    if ((iVar9 < *(int *)(param_1 + 0x38)) && (iVar7 = iVar2, g_nRdroidGeometryMode < iVar2)) {
      iVar7 = g_nRdroidGeometryMode;
    }
    _DAT_007f5f18 = _DAT_007f5f0c;
    _DAT_007f5f1c = _DAT_007f5f10;
    _DAT_007f5f24 = _DAT_007f5f0c;
    _DAT_007f5f30 = _DAT_007f5f0c;
    *(int *)(iVar4 + 8) = iVar7;
    if ((((byte)g_dwRdroidFlags & 2) == 0) || (*(float *)((int)g_pRdCurrentCamera + 0x54) < 1.0)) {
      iVar2 = *(int *)(iVar1 + 0x68);
      iVar9 = g_nRdroidLightingMode;
      if (iVar2 <= g_nRdroidLightingMode) {
        iVar9 = iVar2;
      }
      iVar5 = *(int *)(param_1 + 0x3c);
      if ((iVar9 < iVar5) && (iVar5 = iVar2, g_nRdroidLightingMode < iVar2)) {
        iVar5 = g_nRdroidLightingMode;
      }
      *(int *)(iVar4 + 0xc) = iVar5;
    }
    else {
      *(undefined4 *)(iVar4 + 0xc) = 0;
    }
    iVar2 = *(int *)(iVar1 + 0x6c);
    iVar9 = g_nRdroidTextureMode;
    if (iVar2 <= g_nRdroidTextureMode) {
      iVar9 = iVar2;
    }
    iVar5 = *(int *)(param_1 + 0x40);
    if ((iVar9 < *(int *)(param_1 + 0x40)) && (iVar5 = iVar2, g_nRdroidTextureMode < iVar2)) {
      iVar5 = g_nRdroidTextureMode;
    }
    *(int *)(iVar4 + 0x10) = iVar5;
    rdPrimit3_ClipFace(*(undefined4 *)((int)g_pRdCurrentCamera + 0x48),iVar7,
                       *(undefined4 *)(iVar4 + 0xc),iVar5,&local_2c,&local_58,iVar1 + 0x84);
    if (2 < local_58) {
      (**(code **)((int)g_pRdCurrentCamera + 0x50))(local_30,local_4c,local_58);
      if (((byte)g_dwRdroidFlags & 2) == 0) {
        *(undefined4 *)(iVar4 + 0x40) = 0;
      }
      else {
        *(undefined4 *)(iVar4 + 0x40) = *(undefined4 *)((int)g_pRdCurrentCamera + 0x54);
      }
      iVar2 = *(int *)(iVar4 + 0xc);
      if (iVar2 != 0) {
        bVar10 = UINT_004f5ec0 == UINT_004f5ec4;
        if (*(float *)(iVar4 + 0x40) < 1.0) {
          if (iVar2 == 2) {
            if ((*(float *)(iVar4 + 0x44) < 1.0) || (!bVar10)) {
              if (*(float *)(iVar4 + 0x44) <= 0.0) {
                *(undefined4 *)(iVar4 + 0xc) = 1;
              }
            }
            else {
              *(undefined4 *)(iVar4 + 0xc) = 0;
            }
          }
          else if (iVar2 == 3) {
            pfVar8 = *(float **)(iVar4 + 0x28);
            fVar3 = *pfVar8;
            uVar6 = 1;
            if (1 < local_58) {
              do {
                pfVar8 = pfVar8 + 1;
                if (*pfVar8 != fVar3) break;
                uVar6 = uVar6 + 1;
              } while (uVar6 < local_58);
            }
            if (uVar6 == local_58) {
              if (fVar3 == 1.0) {
                if (bVar10) {
                  *(undefined4 *)(iVar4 + 0xc) = 0;
                }
                else {
                  *(undefined4 *)(iVar4 + 0xc) = 2;
                  *(undefined4 *)(iVar4 + 0x44) = 0x3f800000;
                }
              }
              else if (fVar3 == 0.0) {
                *(undefined4 *)(iVar4 + 0xc) = 1;
                *(undefined4 *)(iVar4 + 0x44) = 0;
              }
              else {
                *(undefined4 *)(iVar4 + 0xc) = 2;
                *(float *)(iVar4 + 0x44) = fVar3;
              }
            }
          }
        }
        else {
          *(uint *)(iVar4 + 0xc) = (-(uint)bVar10 & 0xfffffffe) + 2;
        }
      }
      flags = 1;
      if (3 < *(int *)(iVar4 + 8)) {
        flags = 3;
      }
      if (2 < *(int *)(iVar4 + 0xc)) {
        flags = flags | 4;
      }
      *(undefined4 *)(iVar4 + 0x3c) = *(undefined4 *)(param_1 + 0x30);
      *(uint *)(iVar4 + 0x50) = (uint)(PUN(float,local_78) < 0.0);
      *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(iVar1 + 0x60);
      *(undefined4 *)(iVar4 + 0x48) = *(undefined4 *)(iVar1 + 0x8c);
      *(undefined4 *)(iVar4 + 0x38) = *(undefined4 *)(iVar1 + 0x7c);
      rdCache_AddMesh((void *)0x0,local_58,flags);
      return 1;
    }
  }
  return 0;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_44
#undef local_48
#undef local_4c
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

#endif

