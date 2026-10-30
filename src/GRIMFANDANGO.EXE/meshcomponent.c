/* GRIMFANDANGO.EXE :: meshcomponent.c
 * functions 0x00496d40 .. 0x00497180 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00496d40  MeshComponent_OnKey ---- */
/* Costume tag handler for 'RDroid Thing Mesh' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, shows or hides the mesh according to the key value
   (table DAT_004e9f38). */

void MeshComponent_OnKey(undefined4 param_1,int *param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(&DAT_004e9f38 + param_4 * 4);
  iVar2 = *(int *)(*param_2 + 0x40);
  param_2[2] = (uint)(iVar1 != 0);
  *(uint *)(*(int *)(iVar2 + 0x2c) + param_2[1] * 4) = (uint)(iVar1 != 0);
  return;
}

/* ---- 0x00496d70  MeshComponent_NewInstance ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Costume tag handler, slot 5 of the 'RDroid Thing Mesh' tag: per-instance data of a mesh
   component. (Was named SpriteComponent_NewInstance.) */

int * __cdecl MeshComponent_NewInstance(int inst,int component,int create)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int *piVar3;
  #define auStack_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  if (create == 0) {
    iVar2 = Cos_InstGetInstanceData(inst,component,(int *)0x0);
    (*g_pSvcCostume->pFree)(iVar2);
    return (int *)0x0;
  }
  piVar3 = (int *)(*g_pSvcCostume->pAlloc)(0xc,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xb54);
  piVar1 = piVar3 + 1;
  Cos_InstComponentInfo(inst,component,(int)auStack_4,(int)piVar1,(int)&create);
  *piVar1 = *piVar1 >> 0x10;
  iVar2 = Cos_InstGetInstanceData(inst,create,(int *)0x0);
  *piVar3 = iVar2;
  piVar3[2] = 1;
  return piVar3;
}
#undef auStack_4

#endif


/* ---- 0x00496e10  MeshComponent_Stop ---- */
/* Costume tag handler for 'RDroid Thing Mesh' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 3, sets the visible flag (+8) to 1 again. */

void MeshComponent_Stop(int param_1)

{
  *(undefined4 *)(param_1 + 8) = 1;
  return;
}

/* ---- 0x00496e20  MeshComponent_Create ---- */
/* Registers a MODL/MMDL component attached to a mesh node ('Mesh N: name'); with no node name the
   editor shows 'Select mesh node to add' */

undefined4 MeshComponent_Create(uint param_1,int param_2,int *param_3,int param_4,char *param_5)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  bool bVar2;
  char *buf;
  int iVar3;
  undefined *puVar4;
  char **items;
  int iVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  char **ppcVar9;
  uint uVar10;
  char *pcVar11;
  undefined *puVar12;
  #define uStack_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_8 = 1;
  if ((param_3 == (int *)0x0) || ((param_4 != 0x4c444f4d && (param_4 != 0x4c444d4d)))) {
    return 0;
  }
  if (*param_3 == 0) {
    (*g_pSvcMain->pAssertFail)(s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
  }
  iVar6 = param_3[1];
  buf = (char *)(*g_pSvcCostume->pAlloc)(0x2d,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xb94);
  if (param_5 == (char *)0x0) {
    items = (char **)(*g_pSvcCostume->pAlloc)
                               (*(int *)(iVar6 + 0x54) << 2,
                                s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xbb1);
    uStack_c = 0;
    if (*(int *)(iVar6 + 0x54) != 0) {
      iVar3 = 0;
      ppcVar9 = items;
      do {
        pcVar8 = (char *)(*g_pSvcCostume->pAlloc)
                                   (0x2a,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,2999);
        *ppcVar9 = pcVar8;
        iVar5 = 1;
        if (0 < *(int *)(iVar3 + 0x50 + *(int *)(iVar6 + 0x58))) {
          do {
            *pcVar8 = '\t';
            pcVar8 = pcVar8 + 1;
            bVar2 = iVar5 < *(int *)(iVar3 + 0x50 + *(int *)(iVar6 + 0x58));
            iVar5 = iVar5 + 1;
          } while (bVar2);
        }
        strncpy(pcVar8,iVar3 + *(int *)(iVar6 + 0x58),
                0x1f - *(int *)(iVar3 + 0x50 + *(int *)(iVar6 + 0x58)));
        ppcVar9 = ppcVar9 + 1;
        iVar5 = iVar3 + 0x50;
        iVar3 = iVar3 + 0xb8;
        uStack_c = uStack_c + 1;
        pcVar8[0x1f - *(int *)(iVar5 + *(int *)(iVar6 + 0x58))] = '\0';
      } while (uStack_c < *(uint *)(iVar6 + 0x54));
    }
    puVar4 = (undefined *)
             Plat_TreeSelectDialog
                       (s_Select_mesh_node_to_add____004ea65c,items,*(int *)(iVar6 + 0x54),
                        (int *)&local_8);
    if (((local_8 != 0) && (-1 < (int)puVar4)) &&
       (puVar12 = puVar4 + 1, puVar12 < *(undefined **)(iVar6 + 0x54))) {
      iStack_4 = (int)puVar4 * 0xb8;
      iVar3 = (int)puVar12 * 0xb8;
      do {
        iVar5 = *(int *)(iVar6 + 0x58);
        if (*(int *)(iVar3 + 0x50 + iVar5) <= *(int *)(iStack_4 + 0x50 + iVar5)) break;
        sprintf(buf,s_Mesh__d___s__004ea64c,puVar12,iVar3 + iVar5);
        MeshComponent_Create(param_1,param_2,param_3,param_4,buf);
        puVar12 = puVar12 + 1;
        iVar3 = iVar3 + 0xb8;
      } while (puVar12 < *(undefined **)(iVar6 + 0x54));
    }
    uVar7 = 0;
    ppcVar9 = items;
    if (*(int *)(iVar6 + 0x54) != 0) {
      do {
        (*g_pSvcCostume->pFree)(*ppcVar9);
        uVar7 = uVar7 + 1;
        ppcVar9 = ppcVar9 + 1;
      } while (uVar7 < *(uint *)(iVar6 + 0x54));
    }
    (*g_pSvcCostume->pFree)(items);
    if ((int)puVar4 < 0) goto LAB_004970d4;
    sprintf(buf,s_Mesh__d___s__004ea64c,puVar4,*(int *)(iVar6 + 0x58) + (int)puVar4 * 0xb8);
  }
  else {
    uVar7 = 0xffffffff;
    pcVar8 = param_5;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar1 != '\0');
    iVar3 = isdigit((int)*param_5);
    pcVar8 = param_5;
    for (uVar10 = 0; (iVar3 == 0 && (uVar10 <= ~uVar7 - 1)); uVar10 = uVar10 + 1) {
      pcVar11 = pcVar8 + 1;
      pcVar8 = pcVar8 + 1;
      iVar3 = isdigit((int)*pcVar11);
    }
    iVar3 = isdigit((int)*pcVar8);
    if (iVar3 == 0) {
LAB_004970d4:
      (*g_pSvcCostume->pFree)(buf);
      return 0;
    }
    puVar4 = atoi((uint)pcVar8);
    if ((-1 < (int)puVar4) && ((int)puVar4 < *(int *)(iVar6 + 0x54))) {
      uVar7 = 0xffffffff;
      do {
        pcVar8 = param_5;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar8 = param_5 + 1;
        cVar1 = *param_5;
        param_5 = pcVar8;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      pcVar8 = pcVar8 + -uVar7;
      pcVar11 = buf;
      for (uVar10 = uVar7 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar11 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar11 = pcVar11 + 1;
      }
    }
  }
  iVar6 = Cos_RegisterComponent
                    (param_1,(int)buf,(int)puVar4 << 0x10 | (uint)param_3 & 0xffff,param_2,
                     (int)param_3,param_4,IMG_ADDR(0x004e9f48));
  if (iVar6 == 0) {
    (*g_pSvcCostume->pFree)();
    return 0;
  }
  (*g_pSvcCostume->pFree)(buf);
  return 1;
}
#undef iStack_4
#undef local_8
#undef uStack_c


/* ---- 0x00497180  FUN_00497180 ---- */
int FUN_00497180(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = strchr(param_2,0x29);
  return iVar1 == 0;
}
