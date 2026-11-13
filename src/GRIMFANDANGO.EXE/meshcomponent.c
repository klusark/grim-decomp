/* GRIMFANDANGO.EXE :: meshcomponent.c
 * functions 0x00496d40 .. 0x00497180 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00496d40  MeshChanger ---- */
/* Costume tag handler for 'RDroid Thing Mesh' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, shows or hides the mesh according to the key value
   (table DAT_004e9f38). Original name MeshChanger (the remaster's GrimFandango (Linux): the same
   handler slot (changer) of the same costume tag registration in sputCostume_Startup); was
   MeshComponent_OnKey. */

void __cdecl MeshChanger(uint param_1,int *param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(&DAT_004e9f38 + param_4 * 4);
  iVar2 = *(int *)(*param_2 + 0x40);
  param_2[2] = (uint)(iVar1 != 0);
  *(uint *)(*(int *)(iVar2 + 0x2c) + param_2[1] * 4) = (uint)(iVar1 != 0);
  return;
}

/* ---- 0x00496d70  MeshInstancer ---- */
/* Costume tag handler, slot 5 of the 'RDroid Thing Mesh' tag: per-instance data of a mesh
   component. (Was named SpriteComponent_NewInstance.) Original name MeshInstancer (the remaster's
   GrimFandango (Linux): the same handler slot (instancer) of the same costume tag registration in
   sputCostume_Startup); was MeshComponent_NewInstance. */

int * __cdecl MeshInstancer(int inst,int component,int create)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int *piVar3;
  #define auStack_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  if (create == 0) {
    iVar2 = Cos_InstGetInstanceData(inst,component,(int *)0x0);
    (*g_pSputCosHS->pFree)(iVar2);
    return (int *)0x0;
  }
  piVar3 = (int *)(*g_pSputCosHS->pAlloc)(0xc,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xb54);
  piVar1 = piVar3 + 1;
  Cos_InstComponentInfo(inst,component,(int)auStack_4,(int)piVar1,(int)&create);
  *piVar1 = *piVar1 >> 0x10;
  iVar2 = Cos_InstGetInstanceData(inst,create,(int *)0x0);
  *piVar3 = iVar2;
  piVar3[2] = 1;
  return piVar3;
}
#undef auStack_4


/* ---- 0x00496e10  MeshStopper ---- */
/* Costume tag handler for 'RDroid Thing Mesh' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 3, sets the visible flag (+8) to 1 again. Original name
   MeshStopper (the remaster's GrimFandango (Linux): the same handler slot (stopper) of the same
   costume tag registration in sputCostume_Startup); was MeshComponent_Stop. */

void __cdecl MeshStopper(int param_1)

{
  *(undefined4 *)(param_1 + 8) = 1;
  return;
}

/* ---- 0x00496e20  MeshRequester ---- */
/* Registers a MODL/MMDL component attached to a mesh node ('Mesh N: name'); with no node name the
   editor shows 'Select mesh node to add' Original name MeshRequester (the remaster's GrimFandango
   (Linux): strings: 'Mesh %d (%s)' | 'Select mesh node to add...'); was MeshComponent_Create. */

uint __cdecl MeshRequester(uint param_1,int param_2,int *param_3,int param_4,char *param_5)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  bool bVar2;
  char *buf;
  uint uVar3;
  undefined *puVar4;
  char **items;
  uint *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  char **ppcVar10;
  int iVar11;
  uint uVar12;
  char *pcVar13;
  undefined *puVar14;
  #define uStack_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define iStack_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  local_8 = 1;
  if ((param_3 == (int *)0x0) || ((param_4 != 0x4c444f4d && (param_4 != 0x4c444d4d)))) {
    return 0;
  }
  if (*param_3 == 0) {
    (*g_pStd_HS->pAssertFail)(s_Bad_model_Reference_004e9e08,s_main_sputResource_h_004e80a8,0xae);
  }
  iVar7 = param_3[1];
  buf = (char *)(*g_pSputCosHS->pAlloc)(0x2d,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xb94);
  if (param_5 == (char *)0x0) {
    items = (char **)(*g_pSputCosHS->pAlloc)
                               (*(int *)(iVar7 + 0x54) << 2,
                                s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0xbb1);
    uStack_c = 0;
    if (*(int *)(iVar7 + 0x54) != 0) {
      iVar11 = 0;
      ppcVar10 = items;
      do {
        puVar5 = (uint *)(*g_pSputCosHS->pAlloc)
                                   (0x2a,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,2999);
        *ppcVar10 = (char *)puVar5;
        iVar6 = 1;
        if (0 < *(int *)(iVar11 + 0x50 + *(int *)(iVar7 + 0x58))) {
          do {
            *(char *)puVar5 = '\t';
            puVar5 = (uint *)((int)puVar5 + 1);
            bVar2 = iVar6 < *(int *)(iVar11 + 0x50 + *(int *)(iVar7 + 0x58));
            iVar6 = iVar6 + 1;
          } while (bVar2);
        }
        strncpy(puVar5,(uint *)(iVar11 + *(int *)(iVar7 + 0x58)),
                0x1f - *(int *)(iVar11 + 0x50 + *(int *)(iVar7 + 0x58)));
        ppcVar10 = ppcVar10 + 1;
        iVar6 = iVar11 + 0x50;
        iVar11 = iVar11 + 0xb8;
        uStack_c = uStack_c + 1;
        *(undefined1 *)((int)puVar5 + (0x1f - *(int *)(iVar6 + *(int *)(iVar7 + 0x58)))) = 0;
      } while (uStack_c < *(uint *)(iVar7 + 0x54));
    }
    puVar4 = (undefined *)
             grimPlat_TreeDialog(s_Select_mesh_node_to_add____004ea65c,items,*(int *)(iVar7 + 0x54),
                                 (int *)&local_8);
    if (((local_8 != 0) && (-1 < (int)puVar4)) &&
       (puVar14 = puVar4 + 1, puVar14 < *(undefined **)(iVar7 + 0x54))) {
      iStack_4 = (int)puVar4 * 0xb8;
      iVar11 = (int)puVar14 * 0xb8;
      do {
        iVar6 = *(int *)(iVar7 + 0x58);
        if (*(int *)(iVar11 + 0x50 + iVar6) <= *(int *)(iStack_4 + 0x50 + iVar6)) break;
        sprintf(buf,s_Mesh__d___s__004ea64c,puVar14,iVar11 + iVar6);
        MeshRequester(param_1,param_2,param_3,param_4,buf);
        puVar14 = puVar14 + 1;
        iVar11 = iVar11 + 0xb8;
      } while (puVar14 < *(undefined **)(iVar7 + 0x54));
    }
    uVar8 = 0;
    ppcVar10 = items;
    if (*(int *)(iVar7 + 0x54) != 0) {
      do {
        (*g_pSputCosHS->pFree)(*ppcVar10);
        uVar8 = uVar8 + 1;
        ppcVar10 = ppcVar10 + 1;
      } while (uVar8 < *(uint *)(iVar7 + 0x54));
    }
    (*g_pSputCosHS->pFree)(items);
    if ((int)puVar4 < 0) goto LAB_004970d4;
    sprintf(buf,s_Mesh__d___s__004ea64c,puVar4,*(int *)(iVar7 + 0x58) + (int)puVar4 * 0xb8);
  }
  else {
    uVar8 = 0xffffffff;
    pcVar9 = param_5;
    do {
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar1 != '\0');
    uVar3 = isdigit((int)*param_5);
    pcVar9 = param_5;
    for (uVar12 = 0; (uVar3 == 0 && (uVar12 <= ~uVar8 - 1)); uVar12 = uVar12 + 1) {
      pcVar13 = pcVar9 + 1;
      pcVar9 = pcVar9 + 1;
      uVar3 = isdigit((int)*pcVar13);
    }
    uVar8 = isdigit((int)*pcVar9);
    if (uVar8 == 0) {
LAB_004970d4:
      (*g_pSputCosHS->pFree)(buf);
      return 0;
    }
    puVar4 = atoi((uint)pcVar9);
    if ((-1 < (int)puVar4) && ((int)puVar4 < *(int *)(iVar7 + 0x54))) {
      uVar8 = 0xffffffff;
      do {
        pcVar9 = param_5;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar9 = param_5 + 1;
        cVar1 = *param_5;
        param_5 = pcVar9;
      } while (cVar1 != '\0');
      uVar8 = ~uVar8;
      pcVar9 = pcVar9 + -uVar8;
      pcVar13 = buf;
      for (uVar12 = uVar8 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar13 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar13 = pcVar13 + 1;
      }
    }
  }
  iVar7 = Cos_RegisterComponent
                    (param_1,(int)buf,(int)puVar4 << 0x10 | (uint)param_3 & 0xffff,param_2,
                     (int)param_3,param_4,((unsigned)(uintptr_t)&DAT_004e9f48));
  if (iVar7 == 0) {
    (*g_pSputCosHS->pFree)();
    return 0;
  }
  (*g_pSputCosHS->pFree)(buf);
  return 1;
}
#undef iStack_4
#undef local_8
#undef uStack_c


/* ---- 0x00497180  MeshAdjuster ---- */
/* Original name MeshAdjuster (the remaster's GrimFandango (Linux): the same handler slot (adjuster)
   of the same costume tag registration in sputCostume_Startup); was FUN_00497180. */

int __cdecl MeshAdjuster(uint param_1,uint param_2)

{
  uint *puVar1;
  
  puVar1 = strchr((uint *)param_2,')');
  return (uint)(puVar1 == (uint *)0x0);
}
