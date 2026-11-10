/* GRIMFANDANGO.EXE :: costume.c
 * functions 0x00493410 .. 0x00496020 (17 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00493410  FadeInChore ---- */
/* Cos_StartChoreFaded(inst, chore, ms): play the chore, advance it 70 ms, fade its keyframes in
   over ms (130 for the move chores). Original name FadeInChore (the remaster's GrimFandango
   (Linux): the only unmatched caller of Chore_FadeIn; 1 matched neighbours agree, 0 disagree); was
   Cos_StartChoreFaded. */

void FadeInChore(void *param_1,uint param_2,int param_3)

{
  Cos_InstPlayChore((int)param_1,param_2,1,0);
  Cos_InstUpdateChore((int)param_1,param_2,0x46);
  sputCostume_FadeKeysIn(param_1,param_2,param_3);
  return;
}

/* ---- 0x00493450  FadeOutChore ---- */
/* Cos_StopChoreFaded(inst, chore, ms): fade the chore's keyframes out over ms, then stop the chore
   (chore -1: all). Original name FadeOutChore (the remaster's GrimFandango (Linux): the only
   unmatched callee of sputActor_SetWalkChore; the only unmatched caller of Chore_FadeOut; 2 matched
   neighbours agree, 0 disagree); was Cos_StopChoreFaded. */

undefined * __cdecl FadeOutChore(void *param_1,int param_2,int param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  
  if (param_2 == -1) {
    puVar1 = (undefined *)Cos_InstCountChores((int)param_1);
    iVar3 = 0;
    if (0 < (int)puVar1) {
      do {
        puVar2 = FadeOutChore(param_1,iVar3,param_3);
        iVar3 = iVar3 + 1;
      } while (iVar3 < (int)puVar1);
      return puVar2;
    }
  }
  else {
    sputCostume_FadeKeysOut(param_1,param_2,param_3);
    puVar1 = (undefined *)Cos_InstStopChore((int)param_1,param_2);
  }
  return puVar1;
}

/* ---- 0x00494d10  sputCostume_PrintCostumeInfo ---- */
/* Original name sputCostume_PrintCostumeInfo (the remaster's GrimFandango (Linux): the only
   unmatched callee of Lua_PrintActorCostumes; 1 matched neighbours agree, 0 disagree); was
   Costume_PrintList. */

void __cdecl sputCostume_PrintCostumeInfo(void *costume)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  piVar6 = costume;
  if (costume != (void *)0x0) {
    do {
      iVar3 = Cos_InstCountChores(*piVar6);
      uVar5 = 0;
      if (0 < iVar3) {
        do {
          Cos_InstChoreStatus(*piVar6,uVar5);
          uVar5 = uVar5 + 1;
        } while ((int)uVar5 < iVar3);
      }
      piVar1 = piVar6 + 0x2c;
      piVar6 = (int *)*piVar1;
    } while ((int *)*piVar1 != (int *)0x0);
    for (iVar3 = *(int *)((int)costume + 8); iVar3 != 0; iVar3 = *(int *)(iVar3 + 400)) {
      if (*(int *)(iVar3 + 0x38) != 0) {
        uVar5 = 0;
        iVar2 = *(int *)(*(int *)(iVar3 + 0x40) + 4);
        if (*(int *)(iVar2 + 0x54) != 0) {
          iVar4 = 0;
          do {
            String_ContainsSubstring(*(int *)(iVar2 + 0x58) + iVar4,s_skirt_004ea1a8);
            uVar5 = uVar5 + 1;
            iVar4 = iVar4 + 0xb8;
          } while (uVar5 < *(uint *)(iVar2 + 0x54));
        }
      }
    }
  }
  return;
}
#undef local_4


/* ---- 0x00494dc0  Costume_FreeList ---- */
void __cdecl Costume_FreeList(void *list,int free)

{
  int *piVar1;
  
  while (list != (int *)0x0) {
    piVar1 = *(int **)((int)list + 0xb0);
    if (free != 0) {
      Cos_FreeCosInstance(*(int *)list);
    }
    if (*(int *)((int)list + 0x7c) != 0) {
      Res_RemoveReference((int *)((int)list + 0x7c));
    }
    Pool_Free(list);
    list = piVar1;
  }
  return;
}

/* ---- 0x00494e10  sputCostume_PopCostume ---- */
/* Original name sputCostume_PopCostume (the remaster's GrimFandango (Linux): the only unmatched
   callee of Actor_PopCostume; 1 matched neighbours agree, 0 disagree); was Costume_Pop. */

void * __cdecl sputCostume_PopCostume(void *list,int free)

{
  void *pvVar1;
  
  pvVar1 = (void *)0x0;
  if (list != (void *)0x0) {
    pvVar1 = *(void **)((int)list + 0xb0);
    *(undefined4 *)((int)list + 0xb0) = 0;
    Cos_InstStopChores(*(uint *)list);
    Costume_FreeList(list,free);
  }
  return pvVar1;
}

/* ---- 0x00494e50  Costume_ReplaceTop ---- */
void * __cdecl Costume_ReplaceTop(void *list,void *costumeRes,int flags)

{
  void *pvVar1;
  
  pvVar1 = sputCostume_PopCostume(list,1);
  pvVar1 = Costume_Push(pvVar1,costumeRes,flags);
  return pvVar1;
}

/* ---- 0x00494e80  Costume_Push ---- */
/* Source: Engine/sputCostume.cpp (line 1146, from __FILE__/__LINE__ passed to the allocator) */

void * __cdecl Costume_Push(void *list,void *costumeRes,int flags)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int iVar2;
  void *pvVar3;
  uint uVar4;
  uint uVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  piVar1 = (int *)Costume_AllocRecord();
  piVar1[0x2c] = (int)list;
  if (flags == 0) {
    if (list == (void *)0x0) {
      uVar4 = 0;
    }
    else {
      uVar4 = *(uint *)list;
    }
    iVar2 = Cos_CreateCosInstance(costumeRes,uVar4);
    *piVar1 = iVar2;
    Res_SetReference(piVar1 + 0x1f,costumeRes,s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0,0x47a);
  }
  else {
    *piVar1 = flags;
  }
  pvVar3 = Costume_GetMainModel((void *)*piVar1);
  piVar1[1] = (int)pvVar3;
  if (((pvVar3 != (void *)0x0) && (list != (void *)0x0)) && (*(void **)((int)list + 4) == pvVar3)) {
    piVar1[3] = *(int *)((int)list + 0xc);
    piVar1[4] = *(int *)((int)list + 0x10);
    piVar1[5] = *(int *)((int)list + 0x14);
    piVar1[6] = *(int *)((int)list + 0x18);
    piVar1[7] = *(int *)((int)list + 0x1c);
    piVar1[8] = *(int *)((int)list + 0x20);
    piVar1[9] = *(int *)((int)list + 0x24);
    piVar1[2] = *(int *)((int)list + 8);
  }
  uVar4 = Cos_InstCountComponents(*piVar1);
  uVar5 = 0;
  if (uVar4 != 0) {
    do {
      iVar2 = Cos_InstGetInstanceData(*piVar1,uVar5,(int *)&local_4);
      if ((((local_4 == 0x4c444d4d) || (local_4 == 0x4c444f4d)) || (local_4 == 0x74727073)) &&
         (*(int *)(iVar2 + 0x50) == 1)) {
        *(int *)(iVar2 + 400) = piVar1[2];
        piVar1[2] = iVar2;
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < uVar4);
  }
  return piVar1;
}
#undef local_4


/* ---- 0x00494f90  Costume_AllocRecord ---- */
undefined4 Costume_AllocRecord(void)

{
  undefined4 uVar1;
  
  uVar1 = Pool_Alloc(g_pCostumePool);
  Costume_InitRecord(uVar1);
  return uVar1;
}

/* ---- 0x00494fb0  Costume_InitRecord ---- */
/* 0xb4-byte costume record: [0] CHORE.DLL instance, [1] costume resource, [2] component list, [3-5]
   head joints, [6-8] head limits, [9] look rate, [10-13] walk/left/right/rest chores, [14-29] talk
   chores, [30] mumble chore, [44] next */

void Costume_InitRecord(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  *param_1 = 0;
  param_1[3] = 0xffffffff;
  param_1[4] = 0xffffffff;
  param_1[5] = 0xffffffff;
  param_1[7] = 0x41f00000;
  param_1[8] = 0x42b40000;
  param_1[9] = 0xbeb33333;
  param_1[6] = 0x43b40000;
  param_1[10] = 0xffffffff;
  param_1[0xb] = 0xffffffff;
  param_1[0xc] = 0xffffffff;
  param_1[0xd] = 0xffffffff;
  param_1[0x1e] = 0xffffffff;
  puVar2 = param_1 + 0xe;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0xffffffff;
    puVar2 = puVar2 + 1;
  }
  puVar2 = param_1 + 0x1f;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[2] = 0;
  param_1[0x2c] = 0;
  return;
}

/* ---- 0x00495020  Costume_GetMainModel ---- */
/* rdThing of the first MMDL component */

void * __cdecl Costume_GetMainModel(void *cosInst)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pvVar1 = cosInst;
  uVar2 = Cos_InstCountComponents((int)cosInst);
  uVar4 = 0;
  if (uVar2 == 0) {
    return (void *)0x0;
  }
  do {
    iVar3 = Cos_InstGetInstanceData((int)pvVar1,uVar4,(int *)&cosInst);
    if (cosInst == (void *)0x4c444d4d) {
      return *(void **)(iVar3 + 0x40);
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < uVar2);
  return (void *)0x0;
}
#undef local_4


/* ---- 0x00495510  Costume_ApplyScale ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Scales every model radius by actor+0x30 and stores the reciprocal so the second call undoes it */

void __cdecl Costume_ApplyScale(void *actor,void *componentList)

{
  float *pfVar1;
  float *pfVar2;
  int *piVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  
  for (; componentList != (void *)0x0; componentList = *(void **)((int)componentList + 400)) {
    if (*(int *)((int)actor + 0x30) != 0x3f800000) {
      piVar3 = *(int **)((int)componentList + 0x40);
      iVar4 = piVar3[1];
      *(float *)(iVar4 + 0x5c) = *(float *)(iVar4 + 0x5c) * *(float *)((int)actor + 0x30);
      if (*piVar3 == 1) {
        iVar7 = *(int *)(iVar4 + 0x50);
        uVar8 = 0;
        if (*(int *)(iVar4 + 0x24 + iVar7 * 8) != 0) {
          iVar9 = 0;
          do {
            iVar7 = *(int *)(iVar4 + 0x28 + iVar7 * 8);
            uVar8 = uVar8 + 1;
            pfVar1 = (float *)(iVar7 + 0x60 + iVar9);
            pfVar2 = (float *)(iVar7 + 0x60 + iVar9);
            iVar9 = iVar9 + 0x7c;
            *pfVar2 = *(float *)((int)actor + 0x30) * *pfVar1;
            iVar7 = *(int *)(iVar4 + 0x50);
          } while (uVar8 < *(uint *)(iVar4 + 0x24 + iVar7 * 8));
        }
      }
      fVar5 = 1.0 / *(float *)((int)actor + 0x30);
      fVar6 = 1.0 - fVar5;
      *(float *)((int)actor + 0x30) = fVar5;
      fVar5 = fVar6;
      if (fVar6 < 0.0) {
        fVar5 = -fVar6;
      }
      if (fVar5 <= 1e-05) {
        fVar6 = 0.0;
      }
      if (fVar6 == 0.0) {
        *(undefined4 *)((int)actor + 0x30) = 0x3f800000;
      }
    }
  }
  return;
}
#endif


/* ---- 0x004955e0  Costume_ApplyComponentState ---- */
/* Walks the CHORE.DLL components of a costume instance: 'MAT ' swaps the material index of the
   mesh, 'cmap' installs the colormap override */

void __cdecl Costume_ApplyComponentState(void *cosInst)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pvVar2 = cosInst;
  iVar3 = Cos_InstCountComponents((int)cosInst);
  iVar6 = 0;
  if (0 < iVar3) {
    do {
      piVar4 = (int *)Cos_InstGetInstanceData((int)pvVar2,iVar6,(int *)&cosInst);
      if (cosInst == (void *)0x2054414d) {
        iVar1 = *(int *)(*(int *)(*(int *)(*(int *)(*piVar4 + 0x40) + 4) + 0x48) + piVar4[1] * 4);
        uVar5 = *(uint *)(iVar1 + 100) ^ piVar4[2];
        *(uint *)(iVar1 + 100) = uVar5;
        uVar5 = piVar4[2] ^ uVar5;
        piVar4[2] = uVar5;
        *(uint *)(iVar1 + 100) = *(uint *)(iVar1 + 100) ^ uVar5;
      }
      else if ((cosInst != (void *)0x4853454d) && (cosInst == (void *)0x70616d63)) {
        if (piVar4[1] == 0) {
          (*g_pStd_HS->pAssertFail)
                    (s_Bad_Colormap_Reference_004e8090,s_main_sputResource_h_004e80a8,0x9f);
        }
        *(int *)(*piVar4 + 0x4c) = piVar4[2];
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < iVar3);
  }
  return;
}
#undef local_4


/* ---- 0x004956a0  Costume_UpdateAttachedFrame ---- */
/* Recursively positions a model hung on a parent model's node */

void __cdecl Costume_UpdateAttachedFrame(void *component,float *frame)

{
  void *model;
  
  model = *(void **)((int)component + 0x40);
  if (*(void **)((int)component + 0x44) != (void *)0x0) {
    Costume_UpdateAttachedFrame(*(void **)((int)component + 0x44),frame);
    rdPuppet_UpdateFrame
              (model,(float *)(*(int *)((int)component + 0x48) * 0x30 +
                              *(int *)(*(int *)(*(int *)((int)component + 0x44) + 0x40) + 0x20)));
    return;
  }
  rdPuppet_UpdateFrame(model,frame);
  return;
}

/* ---- 0x004956f0  Costume_TouchComponents ---- */
void Costume_TouchComponents(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  sputRoom_GetCurrentRoom();
  iVar1 = Cos_InstCountComponents(param_1);
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      Cos_InstGetInstanceData(param_1,iVar2,&local_4);
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return;
}
#undef local_4


/* ---- 0x00495730  sputCostume_Update ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name sputCostume_Update (the remaster's GrimFandango (Linux): the only unmatched caller
   of rdPuppet_Advance; 1 matched neighbours agree, 0 disagree); was Costume_UpdateAll. */

void __cdecl sputCostume_Update(void *costumeList,float dt)

{
  int iVar1;
  void *puppet;
  undefined4 unaff_ESI;
  int *piVar2;
  undefined4 unaff_EDI;
  ulonglong uVar3;
  
  uVar3 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
  if (costumeList != (void *)0x0) {
    iVar1 = *(int *)((int)costumeList + 4);
    piVar2 = costumeList;
    do {
      if (piVar2[1] != iVar1) break;
      Cos_InstUpdateChores(*piVar2,(int)uVar3);
      piVar2 = (int *)piVar2[0x2c];
    } while (piVar2 != (int *)0x0);
    for (iVar1 = *(int *)((int)costumeList + 8); iVar1 != 0; iVar1 = *(int *)(iVar1 + 400)) {
      puppet = *(void **)(*(int *)(iVar1 + 0x40) + 0x14);
      if (puppet != (void *)0x0) {
        rdPuppet_UpdateTracks(puppet,(float)(uVar3 & 0xffffffff) * 0.001);
      }
    }
  }
  return;
}
#endif


/* ---- 0x00495e90  Costume_SaveChoreListFile ---- */
/* Callback given to Cos_RegisterSaveHook (costume editor): asks for a .lua/.def file name and
   writes the costume's chore list. */

undefined4 Costume_SaveChoreListFile(char *param_1,uint *param_2,undefined4 param_3)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void **ppvVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  uint uVar10;
  #define acStack_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  iVar3 = strrchr(param_1,0x5c);
  pcVar4 = param_1;
  if (iVar3 != 0) {
    pcVar4 = (char *)(iVar3 + 1);
  }
  iVar3 = Cos_GetCostumeName((int)param_2);
  iVar3 = _stricmp(pcVar4,iVar3);
  if (iVar3 == 0) {
    uVar6 = 0xffffffff;
    pcVar4 = param_1;
    do {
      pcVar9 = pcVar4;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar9 = pcVar4 + 1;
      cVar2 = *pcVar4;
      pcVar4 = pcVar9;
    } while (cVar2 != '\0');
    uVar6 = ~uVar6;
    pcVar4 = pcVar9 + -uVar6;
    pcVar9 = g_szGrimlib_aFilename;
    for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar9 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      pcVar9 = pcVar9 + 1;
    }
    pcVar4 = Str_FileExtension(g_szGrimlib_aFilename);
    sprintf(pcVar4,&DAT_004ea45c);
  }
  else {
    iVar3 = Plat_SaveFileDialog(s_Name_chore_list_file____004ea460,
                                s_Script_files____lua____def__004ea478);
    if (iVar3 == 0) {
      return 0;
    }
  }
  iVar3 = (*g_pSputCosHS->pFopen)(g_szGrimlib_aFilename,&DAT_004dd478);
  if (iVar3 != 0) {
    ppvVar1 = &g_pSputCosHS->pFprintf;
    pcVar4 = Str_Basename(param_1);
    (*(code *)*ppvVar1)(iVar3,s____Chore_numbering_for__s__004ea3d4,pcVar4);
    (*g_pSputCosHS->pFprintf)(iVar3,s_____s_004ea3cc,param_3);
    Str_CopyBasenameNoExt(acStack_20,0x20,param_1);
    iVar5 = Cos_CreateCosInstance(param_2,0);
    uVar6 = Cos_InstCountChores(iVar5);
    uVar8 = 0;
    if (uVar6 != 0) {
      do {
        ppvVar1 = &g_pSputCosHS->pFprintf;
        uVar10 = uVar8;
        iVar7 = Cos_InstChoreName(iVar5,uVar8);
        (*(code *)*ppvVar1)(iVar3,s__s__s____d_004ea3bc,acStack_20,iVar7,uVar10);
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar6);
    }
    (*g_pSputCosHS->pFclose)(iVar3);
    Cos_FreeCosInstance(iVar5);
    return 1;
  }
  grimPlat_QueryDialog(s_File_Error__004ea3f0,s_Unable_to_open_chore_list_file__C_004ea3fc,0);
  return 0;
}
#undef acStack_20


/* ---- 0x00496020  Costume_InstanceHook ---- */
/* Callback given to Cos_RegisterInstanceHook: clears the instance's user data (the actor index)
   when an instance is created or destroyed. */

undefined4 Costume_InstanceHook(int param_1,int param_2)

{
  if (param_2 != 0) {
    Cos_InstSetUserData(param_1,0);
    return 1;
  }
  Cos_InstSetUserData(param_1,0);
  return 1;
}
