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

uint __cdecl rdMaterial_RegisterLoader(uint param_1)

{
  uint uVar1;
  
  uVar1 = g_dwMaterialsLoader;
  g_dwMaterialsLoader = param_1;
  return uVar1;
}

/* ---- 0x00417ea0  rdMaterial_RegisterUnloader ---- */
/* Original name rdMaterial_RegisterUnloader (the remaster's GrimFandango (Linux): swaps
   pMaterialsUnloader); was rdMaterial_SetFreeHook. */

uint __cdecl rdMaterial_RegisterUnloader(uint param_1)

{
  uint uVar1;
  
  uVar1 = g_dwMaterialsUnloader;
  g_dwMaterialsUnloader = param_1;
  return uVar1;
}

/* ---- 0x00417eb0  rdMaterial_Load ---- */
rdMaterial * __cdecl rdMaterial_Load(char *name,int a,int b)

{
  rdMaterial *prVar1;
  int iVar2;
  
  if (g_dwMaterialsLoader != 0) {
    prVar1 = (rdMaterial *)(*(code_std *)g_dwMaterialsLoader)(name,a,b);
    return prVar1;
  }
  prVar1 = (rdMaterial *)
           (*g_pRdroid_HS->pAlloc)
                     (0xb0,s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84,DAT_004ddd7c + 10);
  if (prVar1 != (rdMaterial *)0x0) {
    iVar2 = rdMaterial_LoadEntry(name,prVar1,a,b);
    if (iVar2 != 0) {
      return prVar1;
    }
  }
  rdMaterial_Free((uint)prVar1);
  return (rdMaterial *)0x0;
}

/* ---- 0x00417f30  rdMaterial_LoadEntry ---- */
/* Reads a 'MAT ' material file: header, colour table, per-cel texture surfaces (type 2 colour-keyed
   / type 0 solid) Original name rdMaterial_LoadEntry (the remaster's GrimFandango (Linux): strings:
   'MAT '); was rdMaterial_LoadFile. */

int __cdecl rdMaterial_LoadEntry(char *filename,rdMaterial *material,int a,int b)

{
  unsigned char _frame[0x440] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  void *pvVar2;
  VBuffer *surface;
  uint *puVar3;
  int iVar4;
  int iVar5;
  void **ppvVar6;
  byte *pbVar7;
  byte *pbVar8;
  int *piVar9;
  rdMaterial *prVar10;
  int *piVar11;
  byte *pbVar12;
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
  #define VStack_3d8 (*(VBufferFormat *)(_frame + (0x440 - 0x3d8)))
  #define acStack_38c (*(char (*)[4])(_frame + (0x440 - 0x38c)))
  #define iStack_388 (*(int *)(_frame + (0x440 - 0x388)))
  #define uStack_384 (*(uint *)(_frame + (0x440 - 0x384)))
  #define iStack_380 (*(int *)(_frame + (0x440 - 0x380)))
  #define iStack_37c (*(int *)(_frame + (0x440 - 0x37c)))
  #define aiStack_378 (*(int (*)[14])(_frame + (0x440 - 0x378)))
  #define aiStack_340 (*(int (*)[16])(_frame + (0x440 - 0x340)))
  #define auStack_300 (*(undefined1 (*)[768])(_frame + (0x440 - 0x300)))
  
  prVar10 = material;
  for (iVar4 = 0x2c; iVar4 != 0; iVar4 = iVar4 + -1) {
    prVar10->dwType = 0;
    prVar10 = (rdMaterial *)prVar10->aName;
  }
  iVar4 = (*g_pRdroid_HS->pFopen)(filename,&DAT_004ddb18);
  if (iVar4 == 0) {
    return 0;
  }
  (*g_pRdroid_HS->pFread)(iVar4,acStack_38c,0x4c);
  uVar1 = strncmp(acStack_38c,&DAT_004dddb0,4);
  if ((uVar1 == 0) && (iStack_388 == 0x32)) {
    material->nNumTextures = iStack_37c;
    material->dwType = uStack_384;
    material->nNumCels = iStack_380;
    material->nCurCel = 0;
    uStack_428 = 0;
    piVar9 = aiStack_378;
    piVar11 = (int *)&material->field_0x28;
    for (iVar5 = 0xe; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar11 = *piVar9;
      piVar9 = piVar9 + 1;
      piVar11 = piVar11 + 1;
    }
    if (iStack_380 != 0) {
      piVar9 = aiStack_340;
      ppvVar6 = material->aCels;
      do {
        pvVar2 = (void *)(*g_pRdroid_HS->pAlloc)
                                   (0x20,s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84,
                                    DAT_004ddd80 + 0x4c);
        *ppvVar6 = pvVar2;
        if (pvVar2 == (void *)0x0) goto LAB_0041833a;
        (*g_pRdroid_HS->pFread)(iVar4,&uStack_400,0x18);
        *(uint *)*ppvVar6 = uStack_400;
        *(undefined4 *)((int)*ppvVar6 + 4) = uStack_3fc;
        *(undefined4 *)((int)*ppvVar6 + 8) = uStack_3f8;
        *(undefined4 *)((int)*ppvVar6 + 0xc) = uStack_3f4;
        *(undefined4 *)((int)*ppvVar6 + 0x10) = uStack_3f0;
        *(undefined4 *)((int)*ppvVar6 + 0x14) = uStack_3ec;
        if ((uStack_400 & 8) != 0) {
          (*g_pRdroid_HS->pFread)(iVar4,auStack_3e8,0x10);
          *(undefined4 *)((int)*ppvVar6 + 0x18) = auStack_3e8[0];
          *piVar9 = iStack_3dc;
        }
        uStack_428 = uStack_428 + 1;
        ppvVar6 = ppvVar6 + 1;
        piVar9 = piVar9 + 1;
      } while (uStack_428 < (uint)material->nNumCels);
    }
    *(undefined4 *)&material->field_0xac = 0;
    if (material->nNumTextures != 0) {
      iVar5 = (*g_pRdroid_HS->pAlloc)
                        (material->nNumTextures * 0x4ec,s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84,
                         DAT_004ddd80 + 0x7e);
      *(int *)&material->field_0xac = iVar5;
      if (iVar5 == 0) goto LAB_0041833a;
    }
    uStack_428 = 0;
    if (material->nNumTextures != 0) {
      iStack_420 = 0;
      do {
        (*g_pRdroid_HS->pFread)(iVar4,&uStack_418,0x18);
        pbVar8 = (byte *)(iStack_420 + *(int *)&material->field_0xac);
        *(undefined4 *)pbVar8 = uStack_410;
        *(undefined4 *)(pbVar8 + 4) = uStack_40c;
        iVar5 = stdCalcBitPos(uStack_418);
        *(int *)(pbVar8 + 0xc) = iVar5;
        *(uint *)(pbVar8 + 0x10) = uStack_418 - 1;
        uVar1 = 0;
        *(uint *)(pbVar8 + 0x14) = uStack_414 - 1;
        *(undefined4 *)(pbVar8 + 0x18) = uStack_404;
        *(undefined4 *)(pbVar8 + 8) = uStack_408;
        VStack_3d8.nWidth = uStack_418;
        VStack_3d8.nHeight = uStack_414;
        VStack_3d8.colorFormat.nColorMode = *(int *)&material->field_0x28;
        VStack_3d8.colorFormat.nBpp = *(int *)&material->field_0x2c;
        if (*(int *)(pbVar8 + 0x18) != 0) {
          pbVar12 = pbVar8 + 0x1c;
          pbVar7 = pbVar8 + 0xb8;
          do {
            pbVar7[-0xffffffff00000014] = 0;
            pbVar7[-0xffffffff00000013] = 0;
            pbVar7[-0xffffffff00000012] = 0;
            pbVar7[-0xffffffff00000011] = 0;
            pbVar7[0] = 0;
            pbVar7[1] = 0;
            pbVar7[2] = 0;
            pbVar7[3] = 0;
            pbVar7[0x24c] = 0;
            pbVar7[0x24d] = 0;
            pbVar7[0x24e] = 0;
            pbVar7[0x24f] = 0;
            pbVar7[0x260] = 0;
            pbVar7[0x261] = 0;
            pbVar7[0x262] = 0;
            pbVar7[0x263] = 0;
            surface = stdDisplay_VBufferNew(&VStack_3d8,a,b,0);
            *(VBuffer **)pbVar12 = surface;
            if (surface == (VBuffer *)0x0) goto LAB_0041833a;
            if ((*pbVar8 & 1) != 0) {
              stdDisplay_VBufferSetColorKey(surface,*(int *)(pbVar8 + 8));
            }
            stdDisplay_VBufferLock(*(VBuffer **)pbVar12);
            (*g_pRdroid_HS->pFread)
                      (iVar4,*(undefined4 *)(*(int *)pbVar12 + 0x5c),
                       *(undefined4 *)(*(int *)pbVar12 + 0x14));
            stdDisplay_VBufferUnlock(*(VBuffer **)pbVar12);
            VStack_3d8.nWidth = (uint)VStack_3d8.nWidth >> 1;
            VStack_3d8.nHeight = (uint)VStack_3d8.nHeight >> 1;
            uVar1 = uVar1 + 1;
            pbVar12 = pbVar12 + 4;
            pbVar7 = pbVar7 + 0x98;
          } while (uVar1 < *(uint *)(pbVar8 + 0x18));
        }
        uStack_428 = uStack_428 + 1;
        iStack_420 = iStack_420 + 0x4ec;
      } while (uStack_428 < (uint)material->nNumTextures);
    }
    uVar1 = 0;
    if (material->nNumCels != 0) {
      piVar9 = aiStack_340;
      ppvVar6 = material->aCels;
      do {
        if ((*(byte *)*ppvVar6 & 8) != 0) {
          *(int *)((int)*ppvVar6 + 0x1c) = *(int *)&material->field_0xac + *piVar9 * 0x4ec;
        }
        uVar1 = uVar1 + 1;
        piVar9 = piVar9 + 1;
        ppvVar6 = ppvVar6 + 1;
      } while (uVar1 < (uint)material->nNumCels);
    }
    if ((material->dwType & 1) != 0) {
      (*g_pRdroid_HS->pFread)(iVar4,auStack_300,0x300);
    }
    uVar1 = 0x1f;
    puVar3 = (uint *)stdFileFromPath(filename);
    strncpy((uint *)material->aName,puVar3,uVar1);
    material->aName[0x1f] = '\0';
    (*g_pRdroid_HS->pFclose)(iVar4);
    return 1;
  }
LAB_0041833a:
  (*g_pRdroid_HS->pFclose)(iVar4);
  return 0;
}
#undef VStack_3d8
#undef acStack_38c
#undef aiStack_340
#undef aiStack_378
#undef auStack_300
#undef auStack_3e8
#undef iStack_37c
#undef iStack_380
#undef iStack_388
#undef iStack_3dc
#undef iStack_420
#undef uStack_384
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
void __cdecl rdMaterial_Free(uint param_1)

{
  if (g_dwMaterialsUnloader != 0) {
    (*(code_std *)g_dwMaterialsUnloader)(param_1);
    return;
  }
  rdMaterial_FreeEntry(param_1);
  (*g_pRdroid_HS->pFree)(param_1);
  return;
}

/* ---- 0x004183a0  rdMaterial_FreeEntry ---- */
/* Frees the cel bitmaps, their mip surfaces and Direct3D textures Original name
   rdMaterial_FreeEntry (the remaster's GrimFandango (Linux): same body (frees the +0x68 colormap
   entries, the texture VBuffers of every cel, then the +0xac array); called by the material
   resource handler's free message in both builds); was rdMaterial_FreeContents. */

void __cdecl rdMaterial_FreeEntry(int param_1)

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
          stdDisplay_VBufferFree(*(VBuffer **)local_8);
          if (puVar4[0x1d] != 0) {
            (**(code_std **)(*(int *)*puVar4 + 8))((int *)*puVar4);
            (**(code_std **)(*(int *)puVar4[-1] + 8))((int *)puVar4[-1]);
            puVar4[0x1d] = 0;
            puVar4[0x22] = 0;
            D3D_UnlinkTexture((Std3DTexture *)(puVar4 + -1));
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
      std3D_UpdateFrameCount((Std3DTexture *)(material + cel * 0x26 + 0xb));
      return 1;
    }
    iVar1 = std3D_AddToTextureCache
                      ((VBuffer *)material[cel + 7],(Std3DTexture *)(material + cel * 0x26 + 0xb),
                       *material & 1,0);
    if (iVar1 == 0) {
      return 0;
    }
  }
  else if (material[cel * 0x26 + 0xc1] == 0) {
    iVar1 = std3D_AddToTextureCache
                      ((VBuffer *)material[cel + 7],(Std3DTexture *)(material + cel * 0x26 + 0xa3),
                       *material & 1,alt);
    if (iVar1 == 0) {
      return 0;
    }
  }
  else {
    std3D_UpdateFrameCount((Std3DTexture *)(material + cel * 0x26 + 0xa3));
  }
  return 1;
}
