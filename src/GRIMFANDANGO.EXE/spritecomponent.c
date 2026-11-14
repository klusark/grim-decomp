/* GRIMFANDANGO.EXE :: spritecomponent.c
 * functions 0x00498280 .. 0x004986e0 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00498280  SpriteRequester ---- */
/* Costume tag handler for 'Sprite' (registered by sputCostume_Startup through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 1, builds a sprite key; asks for a .mat file ('Select
   mat file for sprite') and creates the polyline. Original name SpriteRequester (the remaster's
   GrimFandango (Linux): strings: 'Select mat file for sprite...'); was SpriteComponent_Create. */

uint __cdecl SpriteRequester(uint param_1,int param_2,int param_3,float param_4,char *param_5)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  uint uVar2;
  undefined *puVar3;
  uint *puVar4;
  char *pcVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  undefined4 *puVar10;
  char *pcVar11;
  int *piVar12;
  #define local_50 (*(float (*)[3])(_frame + (0x60 - 0x50)))
  #define local_44 (*(float *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(float (*)[3])(_frame + (0x60 - 0x40)))
  #define local_34 (*(uint *)(_frame + (0x60 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x60 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x60 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x60 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x60 - 0x24)))
  #define local_20 (*(undefined1 *)(_frame + (0x60 - 0x20)))
  #define local_1f (*(undefined4 *)(_frame + (0x60 - 0x1f)))
  #define local_1 (*(undefined1 *)(_frame + (0x60 - 0x1)))
  
  local_20 = DAT_004f5a98;
  puVar10 = &local_1f;
  for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  *(undefined2 *)puVar10 = 0;
  *(undefined1 *)((int)puVar10 + 2) = 0;
  local_34 = 1;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_40[0] = 0.0;
  local_40[1] = 0.0;
  local_40[2] = 0.0;
  if ((param_3 != 0) && (param_4 == 216341.2)) {
    if (param_5 == (char *)0x0) {
      if (g_bMaterialPath != '\0') {
        grimPlat_SetDefaultOpenPath(((unsigned)(uintptr_t)&g_bMaterialPath));
      }
      iVar7 = grimPlat_OpenFileRequest
                        (s_Select_mat_file_for_sprite____004ea834,s_Material_files____mat__004ea5a4)
      ;
      if (iVar7 == 0) {
        return 0;
      }
      uVar2 = 0x7f;
      puVar4 = (uint *)grimPlat_GetDefaultOpenPath();
      strncpy((uint *)&g_bMaterialPath,puVar4,uVar2);
      DAT_008ca9b7 = 0;
      pcVar5 = stdFnames_FindMedName(g_szGrimlib_aFilename);
      param_5 = pcVar5;
    }
    else {
      strncpy((uint *)&local_20,(uint *)param_5,0x1f);
      local_1 = 0;
      pcVar5 = &local_20;
      strtok(&local_20,&DAT_004ea52c);
      uVar2 = strtok((byte *)0x0,&DAT_004ea52c);
      if (uVar2 != 0) {
        puVar3 = atoi(uVar2);
        local_44 = (float)(int)puVar3 * 0.01;
        uVar2 = strtok((byte *)0x0,&DAT_004ea52c);
        puVar3 = atoi(uVar2);
        local_50[2] = (float)(int)puVar3 * 0.01;
        uVar2 = strtok((byte *)0x0,&DAT_004ea52c);
        puVar3 = atoi(uVar2);
        local_50[0] = (float)(int)puVar3 * 0.01;
        uVar2 = strtok((byte *)0x0,&DAT_004ea52c);
        puVar3 = atoi(uVar2);
        local_50[1] = (float)(int)puVar3 * 0.01;
        uVar2 = strtok((byte *)0x0,&DAT_004ea52c);
        puVar3 = atoi(uVar2);
        param_4 = (float)(int)puVar3 * 0.01;
      }
    }
    piVar6 = (int *)(*g_pSputCosHS->pAlloc)(0x24,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x1026)
    ;
    if (piVar6 != (int *)0x0) {
      piVar12 = piVar6;
      for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
        *piVar12 = 0;
        piVar12 = piVar12 + 1;
      }
      local_40[0] = local_50[0];
      local_40[1] = local_50[1];
      local_40[2] = param_4;
      iVar7 = rdSprite_New(0,(uint)pcVar5,(uint)pcVar5,PUN(uint,(float)local_44),PUN(uint,(float)local_50[2]),5,0,1,0,
                           (uint)local_40);
      *piVar6 = iVar7;
      uVar2 = 0xffffffff;
      do {
        pcVar11 = pcVar5;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar11 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar11;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      piVar9 = (int *)(pcVar11 + -uVar2);
      piVar12 = piVar6;
      for (uVar8 = uVar2 >> 2; piVar12 = piVar12 + 1, uVar8 != 0; uVar8 = uVar8 - 1) {
        *piVar12 = *piVar9;
        piVar9 = piVar9 + 1;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(char *)piVar12 = (char)*piVar9;
        piVar9 = (int *)((int)piVar9 + 1);
        piVar12 = (int *)((int)piVar12 + 1);
      }
      local_34 = *(int *)(*(int *)(*piVar6 + 0x7c) + 0x60) + 1;
      local_30 = 0;
      local_2c = 0;
      iVar7 = Cos_RegisterComponent
                        (param_1,(int)param_5,(int)piVar6,param_2,param_3,0x4853454d,(int)&local_34)
      ;
      if (iVar7 != 0) {
        return 1;
      }
      if (local_30 != 0) {
        (*g_pSputCosHS->pFree)(local_30);
        return 0;
      }
    }
  }
  return 0;
}
#undef local_1
#undef local_1f
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_40
#undef local_44
#undef local_50


/* ---- 0x00498550  SpriteChanger ---- */
/* Costume tag handler for 'Sprite' (registered by sputCostume_Start through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 0, shows (key>0, selects frame key-1) or hides the
   sprite. Original name SpriteChanger (the remaster's GrimFandango (Linux): the same handler slot
   (changer) of the same costume tag registration in sputCostume_Startup); was
   SpriteComponent_OnKey. */

void __cdecl SpriteChanger(uint param_1,int param_2,uint param_3,int param_4)

{
  if (param_4 == 0) {
    *(undefined4 *)(param_2 + 0x38) = 0;
    return;
  }
  *(undefined4 *)(param_2 + 0x38) = 1;
  *(int *)(*(int *)(*(int *)(param_2 + 0x34) + 0x7c) + 100) = param_4 + -1;
  return;
}

/* ---- 0x00498580  SpriteFreer ---- */
/* Costume tag handler, slot 2 of the 'Sprite' tag: frees the key data. (Was named KeyframeFreer.)
   Original name SpriteFreer (the remaster's GrimFandango (Linux): the only unmatched caller of
   rdMaterial_Free; the only unmatched caller of rdSprite_Free; 2 matched neighbours agree, 0
   disagree); was SpriteComponent_Destroy. */

uint __cdecl SpriteFreer(uint param_1,uint param_2,int *param_3)

{
  rdMaterial_Free(*(uint *)(*param_3 + 0x7c));
  rdSprite_Free(*param_3);
  (*g_pSputCosHS->pFree)(param_3);
  return 1;
}

/* ---- 0x004985c0  SpriteInstancer ---- */
/* Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
   Original name SpriteInstancer (the remaster's GrimFandango (Linux): the only unmatched caller of
   rdThing_New; 2 matched neighbours agree, 1 disagree); was FUN_004985c0. */

uint * __cdecl SpriteInstancer(int param_1,uint *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  
  iVar1 = param_1;
  if (param_3 == 0) {
    iVar1 = Cos_InstGetInstanceData(param_1,(int)param_2,(int *)0x0);
    iVar2 = *(int *)(iVar1 + 0x50) + -1;
    *(int *)(iVar1 + 0x50) = iVar2;
    if (iVar2 == 0) {
      rdThing_Free(*(int *)(iVar1 + 0x40));
      (*g_pSputCosHS->pFree)(iVar1);
    }
    return (uint *)0x0;
  }
  Cos_InstComponentInfo(param_1,(int)param_2,(int)&param_3,(int)&param_2,(int)&param_1);
  puVar3 = (uint *)(*g_pSputCosHS->pAlloc)(0x194,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x1070)
  ;
  puVar5 = puVar3;
  for (iVar2 = 0x65; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  puVar3[0xd] = *param_2;
  uVar4 = rdThing_New(0);
  puVar3[0x10] = uVar4;
  *(undefined4 *)(uVar4 + 0x30) = 0;
  rdThing_SetPolyline((undefined4 *)puVar3[0x10],*param_2);
  if (-1 < param_1) {
    puVar5 = (uint *)Cos_InstGetInstanceData(iVar1,param_1,(int *)0x0);
    puVar3[0x11] = *puVar5;
    puVar3[0x12] = puVar5[1];
    puVar3[0x14] = puVar3[0x14] + 1;
    puVar3[0xe] = 0;
    return puVar3;
  }
  puVar3[0x11] = 0;
  puVar3[0x14] = puVar3[0x14] + 1;
  puVar3[0x12] = 0xffffffff;
  puVar3[0xe] = 1;
  return puVar3;
}

/* ---- 0x004986e0  SpriteAdjuster ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Costume tag handler for 'Sprite' (registered by sputCostume_Startup through
   Cos_NewStateBasedTag/Cos_NewIntTag): slot 4, editor dialog for the sprite's Width and Height.
   Original name SpriteAdjuster (the remaster's GrimFandango (Linux): strings: '%s,%d,%d,%d,%d,%d');
   was SpriteComponent_EditKey. */

uint __cdecl SpriteAdjuster(uint *param_1,uint param_2)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  uint *puVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  longlong lVar4;
  #define local_48 (*(uint *)(_frame + (0x60 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x60 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x60 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x60 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x60 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x60 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x60 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x60 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x60 - 0x24)))
  #define local_20 (*(uint (*)[8])(_frame + (0x60 - 0x20)))
  
  local_34 = (uint)s_Width_004ea87c;
  local_30 = (uint)s_Height_004ea874;
  piVar1 = (int *)*param_1;
  local_2c = (uint)&DAT_004ea870;
  local_28 = (uint)&DAT_004ea86c;
  local_24 = (uint)&DAT_004ea868;
  lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  local_48 = (uint)lVar4;
  lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  local_44 = (uint)lVar4;
  lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  local_40 = (uint)lVar4;
  lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  local_3c = (uint)lVar4;
  lVar4 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  local_38 = (uint)lVar4;
  iVar2 = grimPlat_SpinDialog(param_2,(int)&local_34,&local_48,5);
  if (iVar2 != 0) {
    *(float *)(*piVar1 + 0x4c) = (float)(int)local_48 * 0.01;
    *(float *)(*piVar1 + 0x50) = (float)(int)local_44 * 0.01;
    *(float *)(*piVar1 + 0x54) = *(float *)(*piVar1 + 0x4c) * 0.5;
    *(float *)(*piVar1 + 0x58) = *(float *)(*piVar1 + 0x50) * 0.5;
    *(float *)(*piVar1 + 0xac) = (float)(int)local_40 * 0.01;
    *(float *)(*piVar1 + 0xb0) = (float)(int)local_3c * 0.01;
    *(float *)(*piVar1 + 0xb4) = (float)(int)local_38 * 0.01;
    puVar3 = (uint *)strtok((byte *)param_2,&DAT_004ea52c);
    sprintf((char *)local_20,s__s__d__d__d__d__d_004ea854,puVar3,local_48,local_44,local_40,local_3c
            ,local_38);
    strncpy(puVar3,local_20,0x1f);
    *(undefined1 *)((int)puVar3 + 0x1f) = 0;
    return 1;
  }
  return 0;
}
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

#endif

