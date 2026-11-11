/* GRIMFANDANGO.EXE :: rdprimitive.c
 * functions 0x00471ee0 .. 0x00472bd0 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00471ee0  rdPolyline_Draw ---- */
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
  #define local_9c (*(float *)(_frame + (0xc0 - 0x9c)))
  #define local_94 (*(float (*)[2])(_frame + (0xc0 - 0x94)))
  #define local_88 (*(float (*)[3])(_frame + (0xc0 - 0x88)))
  #define local_7c (*(float *)(_frame + (0xc0 - 0x7c)))
  #define local_78 (*(float (*)[9])(_frame + (0xc0 - 0x78)))
  #define local_54 (*(float (*)[3])(_frame + (0xc0 - 0x54)))
  #define local_48 (*(float *)(_frame + (0xc0 - 0x48)))
  #define local_40 (*(float *)(_frame + (0xc0 - 0x40)))
  #define local_38 (*(float (*)[3])(_frame + (0xc0 - 0x38)))
  #define local_2c (*(undefined1 (*)[12])(_frame + (0xc0 - 0x2c)))
  #define local_20 (*(uint *)(_frame + (0xc0 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0xc0 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0xc0 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0xc0 - 0x14)))
  
  iVar1 = *(int *)(param_1 + 4);
  local_20 = (uint)&DAT_007f4e80;
  local_18 = 0;
  local_14 = 0;
  rdMatrix_Multiply34(local_78,(float *)((int)g_pRdCamera_CurCamera + 8),param_2);
  local_38[0] = 0.0;
  local_38[1] = *(float *)(iVar1 + 0x20);
  local_38[2] = 0.0;
  rdMatrix_TransformPoint34(local_88 + 1,local_38,local_78);
  *(float *)&DAT_007f4e84 = local_88[2] - -0.001;
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
  rdPolyline_DrawFace(param_1,iVar1 + 0x84,&DAT_007f4e80,local_2c);
  *(float *)&DAT_007f4e84 = local_54[1] - -0.001;
  *(float *)&DAT_007f4e80 = local_54[0] - *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4e88 = local_54[2] - *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4e8c = local_54[0] + *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4e94 = local_54[2] - *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4e98 = local_54[0] + *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4ea0 = local_54[2] + *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4ea4 = local_54[0] - *(float *)(iVar1 + 0x24);
  *(float *)&DAT_007f4eac = local_54[2] + *(float *)(iVar1 + 0x24);
  local_1c = *(uint *)(iVar1 + 0xd4);
  *(float *)&DAT_007f4e90 = *(float *)&DAT_007f4e84;
  *(float *)&DAT_007f4e9c = *(float *)&DAT_007f4e84;
  *(float *)&DAT_007f4ea8 = *(float *)&DAT_007f4e84;
  rdPolyline_DrawFace(param_1,iVar1 + 0x84,&DAT_007f4e80,local_2c);
  local_94[1] = local_88[1] - local_54[0];
  fVar2 = local_7c - local_54[2];
  fVar3 = SQRT(fVar2 * fVar2 + local_94[1] * local_94[1]);
  local_9c = stdMath_ArcSin3(-local_94[1] / fVar3);
  if (fVar2 < 0.0) {
    if (local_94[1] <= 0.0) {
      local_9c = -(local_9c - -180.0);
    }
    else {
      local_9c = 180.0 - local_9c;
    }
  }
  stdMath_SinCos(local_9c,local_88,local_94);
  *(float *)&DAT_007f4e84 = local_88[2];
  *(float *)&DAT_007f4e80 = (*(float *)(iVar1 + 0x28) * local_94[0] - local_88[0] * fVar3) + local_54[0];
  *(float *)&DAT_007f4e88 = *(float *)(iVar1 + 0x28) * local_88[0] + local_94[0] * fVar3 + local_54[2];
  *(float *)&DAT_007f4e8c = (-*(float *)(iVar1 + 0x28) * local_94[0] - local_88[0] * fVar3) + local_54[0];
  local_94[1] = 0.0;
  *(float *)&DAT_007f4e94 = -*(float *)(iVar1 + 0x28) * local_88[0] + local_94[0] * fVar3 + local_54[2];
  *(float *)&DAT_007f4e98 = (-*(float *)(iVar1 + 0x24) * local_94[0] - 0.0) + local_54[0];
  *(float *)&DAT_007f4ea0 = -*(float *)(iVar1 + 0x24) * local_88[0] + 0.0 + local_54[2];
  *(float *)&DAT_007f4e90 = local_88[2];
  *(float *)&DAT_007f4e9c = local_54[1];
  *(float *)&DAT_007f4ea4 = (*(float *)(iVar1 + 0x24) * local_94[0] - 0.0) + local_54[0];
  *(float *)&DAT_007f4eac = *(float *)(iVar1 + 0x24) * local_88[0] + 0.0 + local_54[2];
  *(float *)&DAT_007f4ea8 = local_54[1];
  local_1c = *(uint *)(iVar1 + 0xd0);
  rdPolyline_DrawFace(param_1,iVar1 + 0x38,&DAT_007f4e80,local_2c);
  return 1;
}
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_2c
#undef local_38
#undef local_40
#undef local_48
#undef local_54
#undef local_78
#undef local_7c
#undef local_88
#undef local_94
#undef local_9c
#undef local_a0
#undef local_b0


/* ---- 0x00472360  rdPolyline_DrawFace ---- */
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
  
  iVar3 = rdCache_GetProcEntry();
  if (iVar3 != 0) {
    local_20 = (uint)&DAT_007f4d00;
    local_4 = *(uint *)(iVar3 + 0x20);
    local_1c = *(uint *)(iVar3 + 0x24);
    local_18 = *(uint *)(iVar3 + 0x28);
    *param_4 = *(undefined4 *)(param_2 + 0x14);
    param_4[1] = *(undefined4 *)(param_2 + 0x18);
    param_4[2] = *(undefined4 *)(param_2 + 0x1c);
    iVar1 = *(int *)(param_2 + 8);
    iVar8 = g_nRdroid_curGeometryMode;
    if (iVar1 <= g_nRdroid_curGeometryMode) {
      iVar8 = iVar1;
    }
    iVar6 = *(int *)(param_1 + 0x38);
    if ((iVar8 < *(int *)(param_1 + 0x38)) && (iVar6 = iVar1, g_nRdroid_curGeometryMode < iVar1)) {
      iVar6 = g_nRdroid_curGeometryMode;
    }
    *(int *)(iVar3 + 8) = iVar6;
    if ((((byte)g_dwRdroid_curRenderOptions & 2) == 0) ||
       (*(float *)((int)g_pRdCamera_CurCamera + 0x54) < 1.0)) {
      iVar1 = *(int *)(param_2 + 0xc);
      iVar8 = g_nRdroid_curLightingMode;
      if (iVar1 <= g_nRdroid_curLightingMode) {
        iVar8 = iVar1;
      }
      iVar4 = *(int *)(param_1 + 0x3c);
      if ((iVar8 < iVar4) && (iVar4 = iVar1, g_nRdroid_curLightingMode < iVar1)) {
        iVar4 = g_nRdroid_curLightingMode;
      }
      *(int *)(iVar3 + 0xc) = iVar4;
    }
    else {
      *(undefined4 *)(iVar3 + 0xc) = 0;
    }
    iVar1 = *(int *)(param_2 + 0x10);
    iVar8 = g_nRdroid_curTextureMode;
    if (iVar1 <= g_nRdroid_curTextureMode) {
      iVar8 = iVar1;
    }
    iVar4 = *(int *)(param_1 + 0x40);
    if ((iVar8 < *(int *)(param_1 + 0x40)) && (iVar4 = iVar1, g_nRdroid_curTextureMode < iVar1)) {
      iVar4 = g_nRdroid_curTextureMode;
    }
    *(int *)(iVar3 + 0x10) = iVar4;
    rdPrimit3_ClipFace(*(undefined4 *)((int)g_pRdCamera_CurCamera + 0x48),iVar6,
                       *(undefined4 *)(iVar3 + 0xc),iVar4,param_4,&local_2c,param_2 + 0x28);
    if (2 < local_2c) {
      (**(code **)((int)g_pRdCamera_CurCamera + 0x50))(local_4,local_20,local_2c);
      if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
        *(undefined4 *)(iVar3 + 0x40) = 0;
      }
      else {
        *(undefined4 *)(iVar3 + 0x40) = *(undefined4 *)((int)g_pRdCamera_CurCamera + 0x54);
      }
      iVar1 = *(int *)(iVar3 + 0xc);
      if (iVar1 != 0) {
        bVar9 = g_dwRdColormap_pIdentityMap != g_dwRdColormap_pCurMap;
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
/* replaced by the hand-written version in build/overrides.c */
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
  rdMatrix_TransformPoint34
            (local_3c,(float *)((int)sprite + 0x24),(float *)((int)g_pRdCamera_CurCamera + 8));
  if ((g_bRdroid_curCullFlags & 2) == 0) {
    iVar2 = *(int *)((int)thing + 0x44);
  }
  else {
    iVar2 = rdClip_SphereInFrustrum
                      (*(undefined4 *)((int)g_pRdCamera_CurCamera + 0x48),local_3c,PUN(float,*(undefined4 *)(iVar1 + 0x3c)));
  }
  if (iVar2 == 2) {
    return 0;
  }
  rdMatrix_Multiply34(local_30,(float *)((int)g_pRdCamera_CurCamera + 8),sprite);
  if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
    sprite = (void *)0x0;
  }
  else {
    sprite = *(void **)((int)g_pRdCamera_CurCamera + 0x54);
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
  rdMatrix_TransformPointLst34
            (local_30,*(float **)(iVar1 + 0x28),(float *)&UINT_007f5180,*(int *)(iVar1 + 0x24));
  local_40 = 0;
  if (*(int *)(iVar1 + 0x24) != 0) {
    puVar3 = &UINT_007f5184;
    do {
      iVar2 = rdCache_GetProcEntry();
      if (iVar2 == 0) {
        return 0;
      }
      *(float *)&DAT_007f5000 = PUN(float,puVar3[-1]) - *(float *)(iVar1 + 0x34);
      _DAT_007f5004 = *puVar3;
      *(float *)&DAT_007f5008 = PUN(float,puVar3[1]) - *(float *)(iVar1 + 0x34);
      _DAT_007f5010 = *puVar3;
      *(float *)&DAT_007f500c = PUN(float,puVar3[-1]) + *(float *)(iVar1 + 0x34);
      _DAT_007f501c = *puVar3;
      *(float *)&DAT_007f5014 = PUN(float,puVar3[1]) - *(float *)(iVar1 + 0x34);
      _DAT_007f5028 = *puVar3;
      *(float *)&DAT_007f5018 = PUN(float,puVar3[-1]) + *(float *)(iVar1 + 0x34);
      *(float *)&DAT_007f5020 = PUN(float,puVar3[1]) + *(float *)(iVar1 + 0x34);
      *(float *)&DAT_007f5024 = PUN(float,puVar3[-1]) - *(float *)(iVar1 + 0x34);
      *(float *)&DAT_007f502c = PUN(float,puVar3[1]) + *(float *)(iVar1 + 0x34);
      vertexCount = rdClip_Face3S(*(undefined4 *)((int)g_pRdCamera_CurCamera + 0x48),&DAT_007f5000,4
                                 );
      if (2 < vertexCount) {
        (**(code **)((int)g_pRdCamera_CurCamera + 0x50))
                  (*(undefined4 *)(iVar2 + 0x20),&DAT_007f5000,vertexCount);
        *(void **)(iVar2 + 0xc) = thing;
        *(void **)(iVar2 + 0x40) = sprite;
        *(undefined4 *)(iVar2 + 8) = 3;
        *(undefined4 *)(iVar2 + 4) = 0;
        *(undefined4 *)(iVar2 + 0x38) = *(undefined4 *)(iVar1 + 0x38);
        *(undefined4 *)(iVar2 + 0x3c) = *(undefined4 *)(*(int *)(iVar1 + 0x2c) + local_40 * 4);
        *(undefined4 *)(iVar2 + 0x50) = 0;
        rdCache_AddProcFace((void *)0x0,vertexCount,1);
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


/* ---- 0x004728a0  rdSprite_New ---- */
/* Allocates a 0xb8-byte polyline (RDroid Primitiv*.c) and initialises it Original name rdSprite_New
   (the remaster's GrimFandango (Linux): the only unmatched caller of rdPolyline_Init; 2 matched
   neighbours agree, 0 disagree); was rdPolyline_New. */

int rdSprite_New(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                undefined4 param_9,undefined4 param_10)

{
  int iVar1;
  
  iVar1 = (*g_pRdroid_HS->pAlloc)(0xb8,s_C__grimjedi_Libs_RDroid_Primitiv_004dde64,DAT_004dde5c + 4)
  ;
  if (iVar1 == 0) {
    return 0;
  }
  rdSprite_NewEntry(iVar1,param_2,param_1,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                    param_10);
  return iVar1;
}

/* ---- 0x00472910  rdSprite_NewEntry ---- */
/* Copies the 31-char name and builds the vertex ring for the given radius/segment counts Original
   name rdSprite_NewEntry (the remaster's GrimFandango (Linux): the only unmatched caller of
   rdMaterial_Load; 1 matched neighbours agree, 0 disagree); was rdPolyline_Init. */

undefined4
rdSprite_NewEntry(int param_1,int param_2,undefined4 param_3,char *param_4,undefined4 param_5,
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
  iVar4 = (*g_pRdroid_HS->pAlloc)
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
    iVar4 = (*g_pRdroid_HS->pAlloc)
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
               (*g_pRdroid_HS->pAlloc)
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

/* ---- 0x00472b50  rdSprite_Free ---- */
void rdSprite_Free(int param_1)

{
  if (param_1 != 0) {
    rdSprite_FreeEntry(param_1);
    (*g_pRdroid_HS->pFree)(param_1);
  }
  return;
}

/* ---- 0x00472b70  rdSprite_FreeEntry ---- */
/* Original name rdSprite_FreeEntry (the remaster's GrimFandango (Linux): same body (frees the +0xa8
   and +0x74 arrays through rdroid_pHS)); was rdSprite_FreeContents. */

void rdSprite_FreeEntry(int param_1)

{
  if (*(int *)(param_1 + 0xa8) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(param_1 + 0xa8));
    *(undefined4 *)(param_1 + 0xa8) = 0;
  }
  if (*(int *)(param_1 + 0x74) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(param_1 + 0x74));
    *(undefined4 *)(param_1 + 0x74) = 0;
  }
  if (*(int *)(param_1 + 0x78) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(param_1 + 0x78));
    *(undefined4 *)(param_1 + 0x78) = 0;
  }
  return;
}

/* ---- 0x00472bd0  rdSprite_Draw ---- */
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
  #define local_78 (*(float (*)[2])(_frame + (0x90 - 0x78)))
  #define local_70 (*(float *)(_frame + (0x90 - 0x70)))
  #define local_6c (*(float (*)[2])(_frame + (0x90 - 0x6c)))
  #define local_64 (*(float *)(_frame + (0x90 - 0x64)))
  #define local_60 (*(float (*)[2])(_frame + (0x90 - 0x60)))
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
  rdMatrix_TransformPoint34(&local_64,param_2 + 9,(float *)((int)g_pRdCamera_CurCamera + 8));
  rdMatrix_TransformVector34(&local_70,(float *)(iVar1 + 0xac),param_2);
  rdMatrix_TransformVector34Acc(&local_70,(float *)((int)g_pRdCamera_CurCamera + 8));
  if (0.0 <= local_70) {
    local_78[0] = -*(float *)(iVar1 + 0x54);
  }
  else {
    local_78[0] = *(float *)(iVar1 + 0x54);
  }
  if ((g_bRdroid_curCullFlags & 2) == 0) {
    iVar4 = *(int *)(param_1 + 0x44);
  }
  else {
    iVar4 = rdClip_SphereInFrustrum
                      (*(undefined4 *)((int)g_pRdCamera_CurCamera + 0x48),&local_64,PUN(float,*(undefined4 *)(iVar1 + 0x24)));
  }
  if ((iVar4 != 2) && (iVar4 = rdCache_GetProcEntry(), iVar4 != 0)) {
    *(float *)&DAT_007f5f0c = local_6c[0] + local_60[0];
    *(float *)&DAT_007f5f10 = local_6c[1] + local_60[1];
    *(float *)&DAT_007f5f08 = local_64 + (local_70 - local_78[0]);
    *(float *)&DAT_007f5f14 = local_64 + local_78[0] + local_70;
    *(float *)&DAT_007f5f20 = local_64 + local_78[0] + local_70;
    *(float *)&DAT_007f5f28 = local_60[1] + *(float *)(iVar1 + 0x58) + *(float *)(iVar1 + 0x58) + local_6c[1];
    *(float *)&DAT_007f5f2c = local_64 + (local_70 - local_78[0]);
    *(float *)&DAT_007f5f34 = local_60[1] + *(float *)(iVar1 + 0x58) + *(float *)(iVar1 + 0x58) + local_6c[1];
    local_2c = *(uint *)(iVar1 + 0x70);
    local_28 = *(uint *)(iVar1 + 0x74);
    local_24 = *(uint *)(iVar1 + 0x78);
    local_20 = (uint)&DAT_007f5f08;
    local_1c = *(uint *)(iVar1 + 0xa8);
    local_18 = 0;
    local_14 = 0;
    local_4c = (uint)&g_aRdSprite_FaceVerts;
    local_30 = *(uint *)(iVar4 + 0x20);
    local_48 = *(uint *)(iVar4 + 0x24);
    local_44 = *(uint *)(iVar4 + 0x28);
    iVar2 = *(int *)(iVar1 + 100);
    iVar9 = g_nRdroid_curGeometryMode;
    if (iVar2 <= g_nRdroid_curGeometryMode) {
      iVar9 = iVar2;
    }
    iVar7 = *(int *)(param_1 + 0x38);
    if ((iVar9 < *(int *)(param_1 + 0x38)) && (iVar7 = iVar2, g_nRdroid_curGeometryMode < iVar2)) {
      iVar7 = g_nRdroid_curGeometryMode;
    }
    *(float *)&DAT_007f5f18 = *(float *)&DAT_007f5f0c;
    *(float *)&DAT_007f5f1c = *(float *)&DAT_007f5f10;
    *(float *)&DAT_007f5f24 = *(float *)&DAT_007f5f0c;
    *(float *)&DAT_007f5f30 = *(float *)&DAT_007f5f0c;
    *(int *)(iVar4 + 8) = iVar7;
    if ((((byte)g_dwRdroid_curRenderOptions & 2) == 0) ||
       (*(float *)((int)g_pRdCamera_CurCamera + 0x54) < 1.0)) {
      iVar2 = *(int *)(iVar1 + 0x68);
      iVar9 = g_nRdroid_curLightingMode;
      if (iVar2 <= g_nRdroid_curLightingMode) {
        iVar9 = iVar2;
      }
      iVar5 = *(int *)(param_1 + 0x3c);
      if ((iVar9 < iVar5) && (iVar5 = iVar2, g_nRdroid_curLightingMode < iVar2)) {
        iVar5 = g_nRdroid_curLightingMode;
      }
      *(int *)(iVar4 + 0xc) = iVar5;
    }
    else {
      *(undefined4 *)(iVar4 + 0xc) = 0;
    }
    iVar2 = *(int *)(iVar1 + 0x6c);
    iVar9 = g_nRdroid_curTextureMode;
    if (iVar2 <= g_nRdroid_curTextureMode) {
      iVar9 = iVar2;
    }
    iVar5 = *(int *)(param_1 + 0x40);
    if ((iVar9 < *(int *)(param_1 + 0x40)) && (iVar5 = iVar2, g_nRdroid_curTextureMode < iVar2)) {
      iVar5 = g_nRdroid_curTextureMode;
    }
    *(int *)(iVar4 + 0x10) = iVar5;
    rdPrimit3_ClipFace(*(undefined4 *)((int)g_pRdCamera_CurCamera + 0x48),iVar7,
                       *(undefined4 *)(iVar4 + 0xc),iVar5,&local_2c,&local_58,iVar1 + 0x84);
    if (2 < local_58) {
      (**(code **)((int)g_pRdCamera_CurCamera + 0x50))(local_30,local_4c,local_58);
      if (((byte)g_dwRdroid_curRenderOptions & 2) == 0) {
        *(undefined4 *)(iVar4 + 0x40) = 0;
      }
      else {
        *(undefined4 *)(iVar4 + 0x40) = *(undefined4 *)((int)g_pRdCamera_CurCamera + 0x54);
      }
      iVar2 = *(int *)(iVar4 + 0xc);
      if (iVar2 != 0) {
        bVar10 = g_dwRdColormap_pIdentityMap == g_dwRdColormap_pCurMap;
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
      *(uint *)(iVar4 + 0x50) = (uint)(local_78[0] < 0.0);
      *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(iVar1 + 0x60);
      *(undefined4 *)(iVar4 + 0x48) = *(undefined4 *)(iVar1 + 0x8c);
      *(undefined4 *)(iVar4 + 0x38) = *(undefined4 *)(iVar1 + 0x7c);
      rdCache_AddProcFace((void *)0x0,local_58,flags);
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
#undef local_60
#undef local_64
#undef local_6c
#undef local_70
#undef local_78
#undef local_7c

