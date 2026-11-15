/* GRIMFANDANGO.EXE :: rdthing.c
 * functions 0x0040cf20 .. 0x00471e00 (10 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0040cf20  rdModel3_Draw ---- */
/* Rdthing.c: frustum-tests the model's bounding sphere, picks the geometry set, updates the puppet
   and draws the node hierarchy Original name rdModel3_Draw (the remaster's GrimFandango (Linux):
   same body (bounding-sphere frustum test, geometry set, puppet update, node hierarchy; counts
   rdModel3_numDrawnModels); called by rdThing_Draw's model case); was rdThing_Draw. */

int __cdecl rdModel3_Draw(rdThing *thing,float *position)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  rdLight *prVar1;
  float fVar2;
  float fVar3;
  rdCamera *prVar4;
  int iVar5;
  float *pfVar6;
  uint uVar7;
  rdLight **pprVar8;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
  g_pCurThing = thing;
  g_pCurModel3 = thing->pModel;
  rdMatrix_TransformPoint34(local_c,g_pCurModel3->aInsertOffset,position);
  rdMatrix_TransformPoint34Acc(local_c,g_pRdCamera_CurCamera->aView);
  if (thing->nFrustumCull == 0) {
    g_dwThingFrustrumCull = 1;
  }
  else {
    g_dwThingFrustrumCull =
         rdClip_SphereInFrustrum
                   (&g_pRdCamera_CurCamera->pFrustum->nClipFar,local_c,g_pCurModel3->flRadius);
  }
  if (g_dwThingFrustrumCull != 2) {
    g_dwThingFrustrumCull = 1;
    if (thing->nCurGeoset == -1) {
      iVar5 = g_pCurModel3->nCurGeoset;
    }
    else {
      iVar5 = g_pCurThing->nCurGeoset;
    }
    g_dwCurGeo = (uint)(g_pCurModel3->aGeosets + iVar5);
    rdPuppet_UpdateFrame(g_pCurThing,position);
    prVar4 = g_pRdCamera_CurCamera;
    g_dwCurTextureMode = g_pCurThing->nGeometryMode;
    if (g_nRdroid_curGeometryMode <= (int)g_dwCurTextureMode) {
      g_dwCurTextureMode = g_nRdroid_curGeometryMode;
    }
    if ((((byte)g_dwRdroid_curRenderOptions & 2) == 0) ||
       (g_pRdCamera_CurCamera->flAmbientLight < 1.0)) {
      UINT_007f30dc = g_pCurThing->nLightingMode;
      if (g_nRdroid_curLightingMode <= g_pCurThing->nLightingMode) {
        UINT_007f30dc = g_nRdroid_curLightingMode;
      }
    }
    else {
      UINT_007f30dc = 0;
    }
    UINT_007f189c = g_pCurThing->nTextureMode;
    if (g_nRdroid_curTextureMode <= (int)UINT_007f189c) {
      UINT_007f189c = g_nRdroid_curTextureMode;
    }
    if (1 < (int)UINT_007f30dc) {
      g_dwNumGeoLights = 0;
      uVar7 = 0;
      if (g_pRdCamera_CurCamera->dwNumLights != 0) {
        pfVar6 = g_pRdCamera_CurCamera->aLightPositions + 1;
        pprVar8 = g_pRdCamera_CurCamera->aLights;
        do {
          prVar1 = *pprVar8;
          if (prVar1->nActive != 0) {
            if (prVar1->nType < 2) {
              fVar2 = 0.0;
            }
            else {
              fVar2 = (position[0xb] - pfVar6[1]) * (position[0xb] - pfVar6[1]) +
                      (position[10] - *pfVar6) * (position[10] - *pfVar6) +
                      (position[9] - pfVar6[-1]) * (position[9] - pfVar6[-1]);
            }
            fVar3 = prVar1->flFalloffMin + g_pCurModel3->flRadius;
            if (fVar2 < fVar3 * fVar3) {
              (&g_apGeoLights)[g_dwNumGeoLights] = (uint)prVar1;
              g_dwNumGeoLights = g_dwNumGeoLights + 1;
            }
          }
          uVar7 = uVar7 + 1;
          pprVar8 = pprVar8 + 1;
          pfVar6 = pfVar6 + 3;
        } while (uVar7 < prVar4->dwNumLights);
      }
    }
    rdModel3_DrawHNode((int)g_pCurModel3->pHierarchyNodes);
    g_dwRdModel3_numDrawnModels = g_dwRdModel3_numDrawnModels + 1;
    return 1;
  }
  return 0;
}
#undef local_c


/* ---- 0x00471a40  rdThing_New ---- */
uint __cdecl rdThing_New(uint param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  
  puVar1 = (undefined4 *)
           (*g_pRdroid_HS->pAlloc)
                     (0x4c,s_C__grimjedi_Libs_RDroid_Engine_R_004dde14,DAT_004dde0c + 3);
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  uVar2 = rdThing_NewEntry(puVar1,param_1);
  return -(uint)(uVar2 != 0) & (uint)puVar1;
}

/* ---- 0x00471a80  rdThing_NewEntry ---- */
/* Default thing: geometry mode 4, lighting 3, texture 2, no model, both sprite indices -1 Original
   name rdThing_NewEntry (the remaster's GrimFandango (Linux): same body (the same field defaults 4
   / 3 / 2, 4 / 3 / 2, 1, -1 / -1, the owner at +0x48)); was rdThing_Init. */

uint __cdecl rdThing_NewEntry(undefined4 *param_1,uint param_2)

{
  param_1[0xd] = 0xffffffff;
  param_1[0xc] = 0xffffffff;
  param_1[1] = 0;
  param_1[4] = 2;
  param_1[0x10] = 2;
  *param_1 = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[2] = 4;
  param_1[3] = 3;
  param_1[0xe] = 4;
  param_1[0xf] = 3;
  param_1[0x11] = 1;
  param_1[8] = 0;
  param_1[10] = 0;
  param_1[0x12] = param_2;
  param_1[0xb] = 0;
  return 1;
}

/* ---- 0x00471af0  rdThing_Free ---- */
void __cdecl rdThing_Free(int param_1)

{
  if (param_1 != 0) {
    rdThing_FreeEntry((int *)param_1);
    (*g_pRdroid_HS->pFree)(param_1);
  }
  return;
}

/* ---- 0x00471b10  rdThing_FreeEntry ---- */
/* Type 1 (model) things free their puppet buffers */

void __cdecl rdThing_FreeEntry(int *param_1)

{
  int track;
  int iVar1;
  
  if (*param_1 == 1) {
    if (param_1[8] != 0) {
      (*g_pRdroid_HS->pFree)(param_1[8]);
      param_1[8] = 0;
    }
    if (param_1[9] != 0) {
      (*g_pRdroid_HS->pFree)(param_1[9]);
      param_1[9] = 0;
    }
    if (param_1[0xb] != 0) {
      (*g_pRdroid_HS->pFree)(param_1[0xb]);
      param_1[0xb] = 0;
    }
    if (param_1[10] != 0) {
      (*g_pRdroid_HS->pFree)(param_1[10]);
      param_1[10] = 0;
    }
    if (param_1[5] != 0) {
      track = 0;
      iVar1 = 0;
      do {
        if (*(int *)(iVar1 + 8 + param_1[5]) != 0) {
          rdPuppet_RemoveTrack((void *)param_1[5],track);
        }
        iVar1 = iVar1 + 0x134;
        track = track + 1;
      } while (iVar1 < 0x738);
    }
  }
  if (param_1[5] != 0) {
    rdCanvas_Free(param_1[5]);
    param_1[5] = 0;
  }
  return;
}

/* ---- 0x00471bd0  rdThing_SetModel3 ---- */
/* Original name rdThing_SetModel3 (the remaster's GrimFandango (Linux): aligned call in
   ThingInstancer); was rdThing_SetModel. */

void __cdecl rdThing_SetModel3(rdThing *thing,rdModel3 *model)

{
  float *pfVar1;
  int *piVar2;
  void *pvVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  
  thing->nType = 1;
  thing->pModel = model;
  thing->nCurGeoset = -1;
  pfVar1 = (float *)(*g_pRdroid_HS->pAlloc)
                              (model->nNumHierarchyNodes * 0x30,
                               s_C__grimjedi_Libs_RDroid_Engine_R_004dde14,DAT_004dde10 + 0xd);
  thing->pHierarchyMatrices = pfVar1;
  pfVar1 = (float *)(*g_pRdroid_HS->pAlloc)
                              (model->nNumHierarchyNodes * 0xc,
                               s_C__grimjedi_Libs_RDroid_Engine_R_004dde14,DAT_004dde10 + 0x10);
  thing->pHierarchyRot = pfVar1;
  for (uVar4 = model->nNumHierarchyNodes * 3 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pfVar1 = 0.0;
    pfVar1 = pfVar1 + 1;
  }
  for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined1 *)pfVar1 = 0;
    pfVar1 = (float *)((int)pfVar1 + 1);
  }
  if ((thing->pHierarchyMatrices != (float *)0x0) && (thing->pHierarchyRot != (float *)0x0)) {
    piVar2 = (int *)(*g_pRdroid_HS->pAlloc)
                              (model->nNumHierarchyNodes << 2,
                               s_C__grimjedi_Libs_RDroid_Engine_R_004dde14,DAT_004dde10 + 0x1a);
    thing->pHierarchyFlags = piVar2;
    if (piVar2 != (int *)0x0) {
      for (uVar4 = model->nNumHierarchyNodes & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
        *piVar2 = 0;
        piVar2 = piVar2 + 1;
      }
      for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
        *(undefined1 *)piVar2 = 0;
        piVar2 = (int *)((int)piVar2 + 1);
      }
      pvVar3 = (void *)(*g_pRdroid_HS->pAlloc)
                                 (model->nNumHierarchyNodes << 2,
                                  s_C__grimjedi_Libs_RDroid_Engine_R_004dde14,DAT_004dde10 + 0x23);
      thing->pHierarchyExtra = pvVar3;
      if (pvVar3 != (void *)0x0) {
        iVar5 = 0;
        if (0 < model->nNumHierarchyNodes) {
          do {
            iVar5 = iVar5 + 1;
            *(undefined4 *)((int)thing->pHierarchyExtra + iVar5 * 4 + -4) = 1;
          } while (iVar5 < model->nNumHierarchyNodes);
        }
        uVar4 = 0;
        if (model->nNumHierarchyNodes != 0) {
          puVar6 = (uint *)((int)model->pHierarchyNodes + 0x7c);
          do {
            rdMatrix_Build34((float *)(puVar6 + 3),puVar6,(float *)(puVar6 + -3));
            puVar6 = puVar6 + 0x2e;
            uVar4 = uVar4 + 1;
          } while (uVar4 < (uint)model->nNumHierarchyNodes);
        }
        return;
      }
    }
  }
  return;
}

/* ---- 0x00471d40  rdThing_SetCamera ---- */
/* Thing type 2 pointing at a sprite */

uint __cdecl rdThing_SetCamera(undefined4 *param_1,uint param_2)

{
  *param_1 = 2;
  param_1[1] = param_2;
  return 1;
}

/* ---- 0x00471d60  rdThing_SetPolyline ---- */
/* Thing type 4 pointing at a polyline */

uint __cdecl rdThing_SetPolyline(undefined4 *param_1,uint param_2)

{
  *param_1 = 4;
  param_1[1] = param_2;
  param_1[0xc] = 0xffffffff;
  return 1;
}

/* ---- 0x00471d80  rdThing_Draw ---- */
/* Original name rdThing_Draw (the remaster's GrimFandango (Linux): same switch on the thing type (1
   model, 4 sprite, 5 particles, 6 polyline) under rdroid_curGeometryMode != 0; rdThing.c); was
   rdThing_DrawAlt. */

int __cdecl rdThing_Draw(rdThing *thing,float *frame)

{
  uint uVar1;
  int iVar2;
  
  if (g_nRdroid_curGeometryMode != 0) {
    switch(thing->nType) {
    case 0:
    case 2:
    case 3:
      return 0;
    case 1:
      iVar2 = rdModel3_Draw(thing,frame);
      return iVar2;
    case 4:
      uVar1 = rdSprite_Draw((int)thing,frame);
      return uVar1;
    case 5:
      iVar2 = rdSprite_DrawThing(thing,frame);
      return iVar2;
    case 6:
      thing = (rdThing *)rdPolyline_Draw((int)thing,frame);
    }
    return (int)thing;
  }
  return 0;
}

/* ---- 0x00471e00  rdThing_AccumulateMatrices ---- */
/* Node matrix = node pivot/offset transform times the parent's matrix Original name
   rdThing_AccumulateMatrices (the remaster's GrimFandango (Linux): same recursive body
   (BuildTranslate34 of the pivot, PostMultiply34, PostTranslate34 by the negated parent pivot,
   Multiply34 into the node matrix, recurse into the children not yet done)); was
   rdThing_BuildNodeMatrix. */

void __cdecl rdThing_AccumulateMatrices(int param_1,int param_2,float *param_3)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  #define local_3c (*(float (*)[3])(_frame + (0x50 - 0x3c)))
  #define local_30 (*(float (*)[12])(_frame + (0x50 - 0x30)))
  
  rdMatrix_BuildTranslate34(local_30,(float *)(param_2 + 100));
  rdMatrix_PostMultiply34
            (local_30,(float *)(*(int *)(param_2 + 0x44) * 0x30 + *(int *)(param_1 + 0x20)));
  iVar2 = *(int *)(param_2 + 0x54);
  if (iVar2 != 0) {
    local_3c[0] = -*(float *)(iVar2 + 100);
    local_3c[1] = -*(float *)(iVar2 + 0x68);
    local_3c[2] = -*(float *)(iVar2 + 0x6c);
    rdMatrix_PostTranslate34((int)local_30,local_3c);
  }
  rdMatrix_Multiply34((float *)(*(int *)(param_2 + 0x44) * 0x30 + *(int *)(param_1 + 0x20)),param_3,
                      local_30);
  if (*(int *)(param_2 + 0x58) != 0) {
    iVar2 = *(int *)(param_2 + 0x5c);
    uVar1 = 0;
    if (*(int *)(param_2 + 0x58) != 0) {
      do {
        if (*(int *)(*(int *)(param_1 + 0x28) + *(int *)(iVar2 + 0x44) * 4) == 0) {
          rdThing_AccumulateMatrices
                    (param_1,iVar2,
                     (float *)(*(int *)(param_2 + 0x44) * 0x30 + *(int *)(param_1 + 0x20)));
        }
        iVar2 = *(int *)(iVar2 + 0x60);
        uVar1 = uVar1 + 1;
      } while (uVar1 < *(uint *)(param_2 + 0x58));
    }
  }
  return;
}
#undef local_30
#undef local_3c

