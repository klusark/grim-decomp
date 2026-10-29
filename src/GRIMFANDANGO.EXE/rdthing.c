/* GRIMFANDANGO.EXE :: rdthing.c
 * functions 0x0040cf20 .. 0x00471e00 (10 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0040cf20  rdThing_DrawModel ---- */
/* Model branch of rdThing_Draw: frustum-tests the bounding sphere, picks the geometry set, updates
   the puppet and draws the node hierarchy */

int __cdecl rdThing_DrawModel(void *thing,float *position)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  void *pvVar3;
  int iVar4;
  float *pfVar5;
  uint uVar6;
  int *piVar7;
  #define local_c (*(float (*)[3])(_frame + (0x20 - 0xc)))
  
  g_pRdCurrentThing = thing;
  g_pRdCurrentModel = *(void **)((int)thing + 4);
  Vec3_Sub(local_c,(float *)((int)g_pRdCurrentModel + 0x78),position);
  Vec3_Rotate3x3(local_c,(float *)((int)g_pRdCurrentCamera + 8));
  if (*(int *)((int)thing + 0x44) == 0) {
    DAT_007f30a4 = 1;
  }
  else {
    DAT_007f30a4 = Frustum_TestSphere(*(undefined4 *)((int)g_pRdCurrentCamera + 0x48),local_c,
                                      *(undefined4 *)((int)g_pRdCurrentModel + 0x5c));
  }
  if (DAT_007f30a4 != 2) {
    DAT_007f30a4 = 1;
    if (*(int *)((int)thing + 0x34) == -1) {
      iVar4 = *(int *)((int)g_pRdCurrentModel + 0x50);
    }
    else {
      iVar4 = *(int *)((int)g_pRdCurrentThing + 0x34);
    }
    DAT_007f0fd0 = (int)g_pRdCurrentModel + iVar4 * 8 + 0x24;
    rdPuppet_UpdateFrame(g_pRdCurrentThing,position);
    pvVar3 = g_pRdCurrentCamera;
    DAT_007f1494 = *(int *)((int)g_pRdCurrentThing + 0x38);
    if (g_nRdroidGeometryMode <= DAT_007f1494) {
      DAT_007f1494 = g_nRdroidGeometryMode;
    }
    if ((((byte)g_dwRdroidFlags & 2) == 0) || (*(float *)((int)g_pRdCurrentCamera + 0x54) < 1.0)) {
      DAT_007f30dc = *(int *)((int)g_pRdCurrentThing + 0x3c);
      if (g_nRdroidLightingMode <= *(int *)((int)g_pRdCurrentThing + 0x3c)) {
        DAT_007f30dc = g_nRdroidLightingMode;
      }
    }
    else {
      DAT_007f30dc = 0;
    }
    DAT_007f189c = *(int *)((int)g_pRdCurrentThing + 0x40);
    if (g_nRdroidTextureMode <= DAT_007f189c) {
      DAT_007f189c = g_nRdroidTextureMode;
    }
    if (1 < DAT_007f30dc) {
      DAT_007f31f8 = 0;
      uVar6 = 0;
      if (*(int *)((int)g_pRdCurrentCamera + 0x58) != 0) {
        pfVar5 = (float *)((int)g_pRdCurrentCamera + 0x160);
        piVar7 = (int *)((int)g_pRdCurrentCamera + 0x5c);
        do {
          iVar4 = *piVar7;
          if (*(int *)(iVar4 + 8) != 0) {
            if (*(int *)(iVar4 + 4) < 2) {
              fVar1 = 0.0;
            }
            else {
              fVar1 = (position[0xb] - pfVar5[1]) * (position[0xb] - pfVar5[1]) +
                      (position[10] - *pfVar5) * (position[10] - *pfVar5) +
                      (position[9] - pfVar5[-1]) * (position[9] - pfVar5[-1]);
            }
            fVar2 = *(float *)(iVar4 + 0x34) + *(float *)((int)g_pRdCurrentModel + 0x5c);
            if (fVar1 < fVar2 * fVar2) {
              (&DAT_007f1498)[DAT_007f31f8] = iVar4;
              DAT_007f31f8 = DAT_007f31f8 + 1;
            }
          }
          uVar6 = uVar6 + 1;
          piVar7 = piVar7 + 1;
          pfVar5 = pfVar5 + 3;
        } while (uVar6 < *(uint *)((int)pvVar3 + 0x58));
      }
    }
    rdModel_DrawNode(*(undefined4 *)((int)g_pRdCurrentModel + 0x58));
    DAT_007f31ec = DAT_007f31ec + 1;
    return 1;
  }
  return 0;
}
#undef local_c


/* ---- 0x00471a40  rdThing_New ---- */
uint rdThing_New(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (*g_pSvcRdroid->pAlloc)(0x4c,s_C__grimjedi_Libs_RDroid_Engine_R_004dde14,DAT_004dde0c + 3)
  ;
  if (uVar1 == 0) {
    return 0;
  }
  iVar2 = rdThing_Init(uVar1,param_1);
  return -(uint)(iVar2 != 0) & uVar1;
}

/* ---- 0x00471a80  rdThing_Init ---- */
/* Default thing: geometry mode 4, lighting 3, texture 2, no model, both sprite indices -1 */

undefined4 rdThing_Init(undefined4 *param_1,undefined4 param_2)

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
void rdThing_Free(int param_1)

{
  if (param_1 != 0) {
    rdThing_FreeEntry(param_1);
    (*g_pSvcRdroid->pFree)(param_1);
  }
  return;
}

/* ---- 0x00471b10  rdThing_FreeEntry ---- */
/* Type 1 (model) things free their puppet buffers */

void rdThing_FreeEntry(int *param_1)

{
  int track;
  int iVar1;
  
  if (*param_1 == 1) {
    if (param_1[8] != 0) {
      (*g_pSvcRdroid->pFree)(param_1[8]);
      param_1[8] = 0;
    }
    if (param_1[9] != 0) {
      (*g_pSvcRdroid->pFree)(param_1[9]);
      param_1[9] = 0;
    }
    if (param_1[0xb] != 0) {
      (*g_pSvcRdroid->pFree)(param_1[0xb]);
      param_1[0xb] = 0;
    }
    if (param_1[10] != 0) {
      (*g_pSvcRdroid->pFree)(param_1[10]);
      param_1[10] = 0;
    }
    if (param_1[5] != 0) {
      track = 0;
      iVar1 = 0;
      do {
        if (*(int *)(iVar1 + 8 + param_1[5]) != 0) {
          rdPuppet_StopTrack((void *)param_1[5],track);
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

/* ---- 0x00471bd0  rdThing_SetModel ---- */
void __cdecl rdThing_SetModel(void *thing,void *model)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  
  *(undefined4 *)thing = 1;
  *(void **)((int)thing + 4) = model;
  *(undefined4 *)((int)thing + 0x34) = 0xffffffff;
  uVar1 = (*g_pSvcRdroid->pAlloc)
                    (*(int *)((int)model + 0x54) * 0x30,s_C__grimjedi_Libs_RDroid_Engine_R_004dde14,
                     DAT_004dde10 + 0xd);
  *(undefined4 *)((int)thing + 0x20) = uVar1;
  puVar2 = (undefined4 *)
           (*g_pSvcRdroid->pAlloc)
                     (*(int *)((int)model + 0x54) * 0xc,s_C__grimjedi_Libs_RDroid_Engine_R_004dde14,
                      DAT_004dde10 + 0x10);
  *(undefined4 **)((int)thing + 0x24) = puVar2;
  for (uVar3 = *(int *)((int)model + 0x54) * 3 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined1 *)puVar2 = 0;
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  if ((*(int *)((int)thing + 0x20) != 0) && (*(int *)((int)thing + 0x24) != 0)) {
    puVar2 = (undefined4 *)
             (*g_pSvcRdroid->pAlloc)
                       (*(int *)((int)model + 0x54) << 2,s_C__grimjedi_Libs_RDroid_Engine_R_004dde14
                        ,DAT_004dde10 + 0x1a);
    *(undefined4 **)((int)thing + 0x28) = puVar2;
    if (puVar2 != (undefined4 *)0x0) {
      for (uVar3 = *(uint *)((int)model + 0x54) & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
      for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
        *(undefined1 *)puVar2 = 0;
        puVar2 = (undefined4 *)((int)puVar2 + 1);
      }
      iVar4 = (*g_pSvcRdroid->pAlloc)
                        (*(int *)((int)model + 0x54) << 2,
                         s_C__grimjedi_Libs_RDroid_Engine_R_004dde14,DAT_004dde10 + 0x23);
      *(int *)((int)thing + 0x2c) = iVar4;
      if (iVar4 != 0) {
        iVar4 = 0;
        if (0 < *(int *)((int)model + 0x54)) {
          do {
            iVar4 = iVar4 + 1;
            *(undefined4 *)(*(int *)((int)thing + 0x2c) + -4 + iVar4 * 4) = 1;
          } while (iVar4 < *(int *)((int)model + 0x54));
        }
        uVar3 = 0;
        if (*(int *)((int)model + 0x54) != 0) {
          iVar4 = *(int *)((int)model + 0x58) + 0x7c;
          do {
            Angles_ToMatrix(iVar4 + 0xc,iVar4,iVar4 + -0xc);
            iVar4 = iVar4 + 0xb8;
            uVar3 = uVar3 + 1;
          } while (uVar3 < *(uint *)((int)model + 0x54));
        }
        return;
      }
    }
  }
  return;
}

/* ---- 0x00471d40  rdThing_SetSprite ---- */
/* Thing type 2 pointing at a sprite */

undefined4 rdThing_SetSprite(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = 2;
  param_1[1] = param_2;
  return 1;
}

/* ---- 0x00471d60  rdThing_SetPolyline ---- */
/* Thing type 4 pointing at a polyline */

undefined4 rdThing_SetPolyline(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = 4;
  param_1[1] = param_2;
  param_1[0xc] = 0xffffffff;
  return 1;
}

/* ---- 0x00471d80  rdThing_Draw ---- */
int __cdecl rdThing_Draw(void *thing,float *frame)

{
  int iVar1;
  
  if (g_nRdroidGeometryMode != 0) {
    switch(*(undefined4 *)thing) {
    case 0:
    case 2:
    case 3:
      return 0;
    case 1:
      iVar1 = rdThing_DrawModel(thing,frame);
      return iVar1;
    case 4:
      iVar1 = rdSprite_Draw(thing,frame);
      return iVar1;
    case 5:
      iVar1 = rdSprite_DrawThing(thing,frame);
      return iVar1;
    case 6:
      thing = (void *)rdPolyline_Draw(thing,frame);
    }
    return (int)thing;
  }
  return 0;
}

/* ---- 0x00471e00  rdThing_BuildNodeMatrix ---- */
/* Node matrix = node pivot/offset transform times the parent's matrix */

void rdThing_BuildNodeMatrix(int param_1,int param_2,float *param_3)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  #define local_3c (*(float *)(_frame + (0x50 - 0x3c)))
  #define local_38 (*(float *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(float *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(float (*)[12])(_frame + (0x50 - 0x30)))
  
  Matrix_BuildTranslation(local_30,(float *)(param_2 + 100));
  Matrix_Multiply(local_30,*(int *)(param_2 + 0x44) * 0x30 + *(int *)(param_1 + 0x20));
  iVar2 = *(int *)(param_2 + 0x54);
  if (iVar2 != 0) {
    local_3c = -*(float *)(iVar2 + 100);
    local_38 = -*(float *)(iVar2 + 0x68);
    local_34 = -*(float *)(iVar2 + 0x6c);
    Matrix_SetTranslation(local_30,&local_3c);
  }
  Matrix_Mul34((float *)(*(int *)(param_2 + 0x44) * 0x30 + *(int *)(param_1 + 0x20)),param_3,
               local_30);
  if (*(int *)(param_2 + 0x58) != 0) {
    iVar2 = *(int *)(param_2 + 0x5c);
    uVar1 = 0;
    if (*(int *)(param_2 + 0x58) != 0) {
      do {
        if (*(int *)(*(int *)(param_1 + 0x28) + *(int *)(iVar2 + 0x44) * 4) == 0) {
          rdThing_BuildNodeMatrix
                    (param_1,iVar2,*(int *)(param_2 + 0x44) * 0x30 + *(int *)(param_1 + 0x20));
        }
        iVar2 = *(int *)(iVar2 + 0x60);
        uVar1 = uVar1 + 1;
      } while (uVar1 < *(uint *)(param_2 + 0x58));
    }
  }
  return;
}
#undef local_30
#undef local_34
#undef local_38
#undef local_3c

