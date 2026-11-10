/* GRIMFANDANGO.EXE :: rdmaterial.c
 * functions 0x00417e90 .. 0x004184a0 (7 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00417e90  rdMaterial_RegisterLoader ---- */
/* Installs the engine's material loader callback and returns the previous one Original name
   rdMaterial_RegisterLoader (the remaster's GrimFandango (Linux): swaps pMaterialsLoader); was
   rdMaterial_SetLoadHook. */

uint rdMaterial_RegisterLoader(uint param_1)

{
  uint uVar1;
  
  uVar1 = g_dwMaterialsLoader;
  g_dwMaterialsLoader = param_1;
  return uVar1;
}

/* ---- 0x00417ea0  rdMaterial_RegisterUnloader ---- */
/* Original name rdMaterial_RegisterUnloader (the remaster's GrimFandango (Linux): swaps
   pMaterialsUnloader); was rdMaterial_SetFreeHook. */

uint rdMaterial_RegisterUnloader(uint param_1)

{
  uint uVar1;
  
  uVar1 = g_dwMaterialsUnloader;
  g_dwMaterialsUnloader = param_1;
  return uVar1;
}

/* ---- 0x00417eb0  rdMaterial_Load ---- */
void * __cdecl rdMaterial_Load(char *name,int a,int b)

{
  void *pvVar1;
  int iVar2;
  
  if (g_dwMaterialsLoader != 0) {
    pvVar1 = (void *)(*(code_std *)g_dwMaterialsLoader)(name,a,b);
    return pvVar1;
  }
  pvVar1 = (void *)(*g_pRdroid_HS->pAlloc)
                             (0xb0,s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84,DAT_004ddd7c + 10);
  if (pvVar1 != (void *)0x0) {
    iVar2 = rdMaterial_LoadEntry(name,pvVar1,a,b);
    if (iVar2 != 0) {
      return pvVar1;
    }
  }
  rdMaterial_Free(pvVar1);
  return (void *)0x0;
}

/* ---- 0x00417f30  rdMaterial_LoadEntry ---- */
/* Reads a 'MAT ' material file: header, colour table, per-cel texture surfaces (type 2 colour-keyed
   / type 0 solid) Original name rdMaterial_LoadEntry (the remaster's GrimFandango (Linux): strings:
   'MAT '); was rdMaterial_LoadFile. */

int __cdecl rdMaterial_LoadEntry(char *filename,void *material,int a,int b)

{
  unsigned char _frame[0x440] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *surface;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  byte *pbVar6;
  byte *pbVar7;
  int *piVar8;
  undefined4 *puVar9;
  int *piVar10;
  byte *pbVar11;
  undefined4 uVar12;
  #define uStack_428 (*(uint *)(_frame + (0x440 - 0x428)))
  #define iStack_420 (*(int *)(_frame + (0x440 - 0x420)))
  #define uStack_418 (*(uint *)(_frame + (0x440 - 0x418)))
  #define uStack_414 (*(uint *)(_frame + (0x440 - 0x414)))
  #define uStack_410 (*(undefined4 *)(_frame + (0x440 - 0x410)))
  #define uStack_40c (*(undefined4 *)(_frame + (0x440 - 0x40c)))
  #define uStack_408 (*(undefined4 *)(_frame + (0x440 - 0x408)))
  #define uStack_404 (*(undefined4 *)(_frame + (0x440 - 0x404)))
  #define uStack_400 (*(uint *)(_frame + (0x440 - 0x400)))
  #define uStack_3fc (*(undefined4 *)(_frame + (0x440 - 0x3fc)))
  #define uStack_3f8 (*(undefined4 *)(_frame + (0x440 - 0x3f8)))
  #define uStack_3f4 (*(undefined4 *)(_frame + (0x440 - 0x3f4)))
  #define uStack_3f0 (*(undefined4 *)(_frame + (0x440 - 0x3f0)))
  #define uStack_3ec (*(undefined4 *)(_frame + (0x440 - 0x3ec)))
  #define auStack_3e8 (*(undefined4 (*)[3])(_frame + (0x440 - 0x3e8)))
  #define iStack_3dc (*(int *)(_frame + (0x440 - 0x3dc)))
  #define uStack_3d8 (*(uint *)(_frame + (0x440 - 0x3d8)))
  #define uStack_3d4 (*(uint *)(_frame + (0x440 - 0x3d4)))
  #define uStack_3c4 (*(undefined4 *)(_frame + (0x440 - 0x3c4)))
  #define uStack_3c0 (*(undefined4 *)(_frame + (0x440 - 0x3c0)))
  #define auStack_38c (*(undefined1 (*)[4])(_frame + (0x440 - 0x38c)))
  #define iStack_388 (*(int *)(_frame + (0x440 - 0x388)))
  #define uStack_384 (*(undefined4 *)(_frame + (0x440 - 0x384)))
  #define iStack_380 (*(int *)(_frame + (0x440 - 0x380)))
  #define uStack_37c (*(undefined4 *)(_frame + (0x440 - 0x37c)))
  #define auStack_378 (*(undefined4 (*)[14])(_frame + (0x440 - 0x378)))
  #define aiStack_340 (*(int (*)[16])(_frame + (0x440 - 0x340)))
  #define auStack_300 (*(undefined1 (*)[768])(_frame + (0x440 - 0x300)))
  
  puVar5 = material;
  for (iVar3 = 0x2c; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  iVar3 = (*g_pRdroid_HS->pFopen)(filename,&DAT_004ddb18);
  if (iVar3 == 0) {
    return 0;
  }
  (*g_pRdroid_HS->pFread)(iVar3,auStack_38c,0x4c);
  iVar1 = strncmp(auStack_38c,&DAT_004dddb0,4);
  if ((iVar1 == 0) && (iStack_388 == 0x32)) {
    *(undefined4 *)((int)material + 0xa8) = uStack_37c;
    *(undefined4 *)material = uStack_384;
    *(int *)((int)material + 0x60) = iStack_380;
    *(undefined4 *)((int)material + 100) = 0;
    uStack_428 = 0;
    puVar5 = auStack_378;
    puVar9 = (undefined4 *)((int)material + 0x28);
    for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar9 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar9 = puVar9 + 1;
    }
    if (iStack_380 != 0) {
      piVar10 = aiStack_340;
      piVar8 = (int *)((int)material + 0x68);
      do {
        iVar1 = (*g_pRdroid_HS->pAlloc)
                          (0x20,s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84,DAT_004ddd80 + 0x4c);
        *piVar8 = iVar1;
        if (iVar1 == 0) goto LAB_0041833a;
        (*g_pRdroid_HS->pFread)(iVar3,&uStack_400,0x18);
        *(uint *)*piVar8 = uStack_400;
        *(undefined4 *)(*piVar8 + 4) = uStack_3fc;
        *(undefined4 *)(*piVar8 + 8) = uStack_3f8;
        *(undefined4 *)(*piVar8 + 0xc) = uStack_3f4;
        *(undefined4 *)(*piVar8 + 0x10) = uStack_3f0;
        *(undefined4 *)(*piVar8 + 0x14) = uStack_3ec;
        if ((uStack_400 & 8) != 0) {
          (*g_pRdroid_HS->pFread)(iVar3,auStack_3e8,0x10);
          *(undefined4 *)(*piVar8 + 0x18) = auStack_3e8[0];
          *piVar10 = iStack_3dc;
        }
        uStack_428 = uStack_428 + 1;
        piVar8 = piVar8 + 1;
        piVar10 = piVar10 + 1;
      } while (uStack_428 < *(uint *)((int)material + 0x60));
    }
    *(undefined4 *)((int)material + 0xac) = 0;
    if (*(int *)((int)material + 0xa8) != 0) {
      iVar1 = (*g_pRdroid_HS->pAlloc)
                        (*(int *)((int)material + 0xa8) * 0x4ec,
                         s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84,DAT_004ddd80 + 0x7e);
      *(int *)((int)material + 0xac) = iVar1;
      if (iVar1 == 0) goto LAB_0041833a;
    }
    uStack_428 = 0;
    if (*(int *)((int)material + 0xa8) != 0) {
      iStack_420 = 0;
      do {
        (*g_pRdroid_HS->pFread)(iVar3,&uStack_418,0x18);
        pbVar7 = (byte *)(iStack_420 + *(int *)((int)material + 0xac));
        *(undefined4 *)pbVar7 = uStack_410;
        *(undefined4 *)(pbVar7 + 4) = uStack_40c;
        iVar1 = stdCalcBitPos(uStack_418);
        *(int *)(pbVar7 + 0xc) = iVar1;
        *(uint *)(pbVar7 + 0x10) = uStack_418 - 1;
        uVar4 = 0;
        *(uint *)(pbVar7 + 0x14) = uStack_414 - 1;
        *(undefined4 *)(pbVar7 + 0x18) = uStack_404;
        *(undefined4 *)(pbVar7 + 8) = uStack_408;
        uStack_3d8 = uStack_418;
        uStack_3d4 = uStack_414;
        uStack_3c4 = *(undefined4 *)((int)material + 0x28);
        uStack_3c0 = *(undefined4 *)((int)material + 0x2c);
        if (*(int *)(pbVar7 + 0x18) != 0) {
          pbVar11 = pbVar7 + 0x1c;
          pbVar6 = pbVar7 + 0xb8;
          do {
            pbVar6[-0xffffffff00000014] = 0;
            pbVar6[-0xffffffff00000013] = 0;
            pbVar6[-0xffffffff00000012] = 0;
            pbVar6[-0xffffffff00000011] = 0;
            pbVar6[0] = 0;
            pbVar6[1] = 0;
            pbVar6[2] = 0;
            pbVar6[3] = 0;
            pbVar6[0x24c] = 0;
            pbVar6[0x24d] = 0;
            pbVar6[0x24e] = 0;
            pbVar6[0x24f] = 0;
            pbVar6[0x260] = 0;
            pbVar6[0x261] = 0;
            pbVar6[0x262] = 0;
            pbVar6[0x263] = 0;
            surface = stdDisplay_VBufferNew(&uStack_3d8,a,b,0);
            *(void **)pbVar11 = surface;
            if (surface == (void *)0x0) goto LAB_0041833a;
            if ((*pbVar7 & 1) != 0) {
              stdDisplay_VBufferSetColorKey(surface,*(int *)(pbVar7 + 8));
            }
            stdDisplay_VBufferLock(*(void **)pbVar11);
            (*g_pRdroid_HS->pFread)
                      (iVar3,*(undefined4 *)(*(int *)pbVar11 + 0x5c),
                       *(undefined4 *)(*(int *)pbVar11 + 0x14));
            stdDisplay_VBufferUnlock(*(void **)pbVar11);
            uStack_3d8 = uStack_3d8 >> 1;
            uStack_3d4 = uStack_3d4 >> 1;
            uVar4 = uVar4 + 1;
            pbVar11 = pbVar11 + 4;
            pbVar6 = pbVar6 + 0x98;
          } while (uVar4 < *(uint *)(pbVar7 + 0x18));
        }
        uStack_428 = uStack_428 + 1;
        iStack_420 = iStack_420 + 0x4ec;
      } while (uStack_428 < *(uint *)((int)material + 0xa8));
    }
    uVar4 = 0;
    if (*(int *)((int)material + 0x60) != 0) {
      piVar8 = aiStack_340;
      puVar5 = (undefined4 *)((int)material + 0x68);
      do {
        if ((*(byte *)*puVar5 & 8) != 0) {
          *(int *)((byte *)*puVar5 + 0x1c) = *(int *)((int)material + 0xac) + *piVar8 * 0x4ec;
        }
        uVar4 = uVar4 + 1;
        piVar8 = piVar8 + 1;
        puVar5 = puVar5 + 1;
      } while (uVar4 < *(uint *)((int)material + 0x60));
    }
    if ((*(byte *)material & 1) != 0) {
      (*g_pRdroid_HS->pFread)(iVar3,auStack_300,0x300);
    }
    uVar12 = 0x1f;
    pcVar2 = stdFileFromPath(filename);
    strncpy((int)material + 4,pcVar2,uVar12);
    *(undefined1 *)((int)material + 0x23) = 0;
    (*g_pRdroid_HS->pFclose)(iVar3);
    return 1;
  }
LAB_0041833a:
  (*g_pRdroid_HS->pFclose)(iVar3);
  return 0;
}
#undef aiStack_340
#undef auStack_300
#undef auStack_378
#undef auStack_38c
#undef auStack_3e8
#undef iStack_380
#undef iStack_388
#undef iStack_3dc
#undef iStack_420
#undef uStack_37c
#undef uStack_384
#undef uStack_3c0
#undef uStack_3c4
#undef uStack_3d4
#undef uStack_3d8
#undef uStack_3ec
#undef uStack_3f0
#undef uStack_3f4
#undef uStack_3f8
#undef uStack_3fc
#undef uStack_400
#undef uStack_404
#undef uStack_408
#undef uStack_40c
#undef uStack_410
#undef uStack_414
#undef uStack_418
#undef uStack_428


/* ---- 0x00418360  rdMaterial_Free ---- */
void rdMaterial_Free(undefined4 param_1)

{
  if (g_dwMaterialsUnloader != 0) {
    (*(code_std *)g_dwMaterialsUnloader)(param_1);
    return;
  }
  rdMaterial_FreeContents(param_1);
  (*g_pRdroid_HS->pFree)(param_1);
  return;
}

/* ---- 0x004183a0  rdMaterial_FreeContents ---- */
/* Frees the cel bitmaps, their mip surfaces and Direct3D textures */

void rdMaterial_FreeContents(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar3 = 0;
  if (*(int *)(param_1 + 0x60) != 0) {
    puVar1 = (undefined4 *)(param_1 + 0x68);
    do {
      (*g_pRdroid_HS->pFree)(*puVar1);
      uVar3 = uVar3 + 1;
      puVar1 = puVar1 + 1;
    } while (uVar3 < *(uint *)(param_1 + 0x60));
  }
  local_4 = 0;
  if (*(int *)(param_1 + 0xa8) != 0) {
    puVar2 = (uint *)(*(int *)(param_1 + 0xac) + 0x18);
    do {
      uVar3 = 0;
      if (*puVar2 != 0) {
        puVar4 = puVar2 + 6;
        local_8 = (uint)puVar2;
        do {
          local_8 = local_8 + 4;
          stdDisplay_VBufferFree(*(void **)local_8);
          if (puVar4[0x1d] != 0) {
            (**(code_std **)(*(int *)*puVar4 + 8))((int *)*puVar4);
            (**(code_std **)(*(int *)puVar4[-1] + 8))((int *)puVar4[-1]);
            puVar4[0x1d] = 0;
            puVar4[0x22] = 0;
            D3D_UnlinkTexture(puVar4 + -1);
          }
          uVar3 = uVar3 + 1;
          puVar4 = puVar4 + 0x26;
        } while (uVar3 < *puVar2);
      }
      puVar2 = puVar2 + 0x13b;
      local_4 = local_4 + 1;
    } while (local_4 < *(uint *)(param_1 + 0xa8));
  }
  if (*(int *)(param_1 + 0xac) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(param_1 + 0xac));
  }
  return;
}
#undef local_4
#undef local_8


/* ---- 0x004184a0  rdMaterial_AddToTextureCache ---- */
/* Touches the cel's Direct3D texture or creates it (D3D_CreateTexture) on first use Original name
   rdMaterial_AddToTextureCache (the remaster's GrimFandango (Linux): aligned call in
   rdCache_SendFaceListToHardware); was rdMaterial_EnsureTexture. */

int __cdecl rdMaterial_AddToTextureCache(void *a,uint *material,int cel,int alt)

{
  int iVar1;
  
  if (alt == 0) {
    if (material[cel * 0x26 + 0x29] != 0) {
      std3D_UpdateFrameCount(material + cel * 0x26 + 0xb);
      return 1;
    }
    iVar1 = std3D_AddToTextureCache
                      ((void *)material[cel + 7],material + cel * 0x26 + 0xb,*material & 1,0);
    if (iVar1 == 0) {
      return 0;
    }
  }
  else if (material[cel * 0x26 + 0xc1] == 0) {
    iVar1 = std3D_AddToTextureCache
                      ((void *)material[cel + 7],material + cel * 0x26 + 0xa3,*material & 1,alt);
    if (iVar1 == 0) {
      return 0;
    }
  }
  else {
    std3D_UpdateFrameCount(material + cel * 0x26 + 0xa3);
  }
  return 1;
}
