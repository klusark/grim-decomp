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

uint __cdecl rdMaterial_RegisterLoader(uint loader)

{
  uint uVar1;
  
  uVar1 = g_dwMaterialsLoader;
  g_dwMaterialsLoader = loader;
  return uVar1;
}

/* ---- 0x00417ea0  rdMaterial_RegisterUnloader ---- */
/* Original name rdMaterial_RegisterUnloader (the remaster's GrimFandango (Linux): swaps
   pMaterialsUnloader); was rdMaterial_SetFreeHook. */

uint __cdecl rdMaterial_RegisterUnloader(uint unloader)

{
  uint uVar1;
  
  uVar1 = g_dwMaterialsUnloader;
  g_dwMaterialsUnloader = unloader;
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
  unsigned char _frame[0x3f0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  void *pvVar2;
  VBuffer *surface;
  int iVar3;
  int iVar4;
  void **ppvVar5;
  uint *puVar6;
  ColorFormat *pCVar7;
  uint *puVar8;
  int *piVar9;
  rdMaterial *prVar10;
  uint *puVar11;
  uint uStack_428;
  int iStack_420;
  MatTextureHeader texHeader;
  MatCelHeader cel;
  MatCelColor celColor;
  #define VStack_3d8 (*(VBufferFormat *)(_frame + (0x3f0 - 0x3d8)))
  MatHeader header;
  #define aiStack_340 (*(int (*)[16])(_frame + (0x3f0 - 0x340)))
  #define auStack_300 (*(undefined1 (*)[768])(_frame + (0x3f0 - 0x300)))
  
  prVar10 = material;
  for (iVar3 = 0x2c; iVar3 != 0; iVar3 = iVar3 + -1) {
    prVar10->dwType = 0;
    prVar10 = (rdMaterial *)prVar10->aName;
  }
  iVar3 = (*g_pRdroid_HS->pFopen)(filename,s_rb_004ddb18);
  if (iVar3 == 0) {
    return 0;
  }
  (*g_pRdroid_HS->pFread)(iVar3,&header,0x4c);
  uVar1 = strncmp(header.aMagic,s_MAT_004dddb0,4);
  if ((uVar1 == 0) && (header.nVersion == 0x32)) {
    material->nNumTextures = header.nTextures;
    material->dwType = header.dwType;
    material->nNumCels = header.nCels;
    material->nCurCel = 0;
    uStack_428 = 0;
    pCVar7 = &header.colorFormat;
    piVar9 = (int *)&material->field_0x28;
    for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1) {
      *piVar9 = pCVar7->nColorMode;
      pCVar7 = (ColorFormat *)&pCVar7->nBpp;
      piVar9 = piVar9 + 1;
    }
    if (header.nCels != 0) {
      piVar9 = aiStack_340;
      ppvVar5 = material->aCels;
      do {
        pvVar2 = (void *)(*g_pRdroid_HS->pAlloc)
                                   (0x20,s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84,
                                    DAT_004ddd80 + 0x4c);
        *ppvVar5 = pvVar2;
        if (pvVar2 == (void *)0x0) goto LAB_0041833a;
        (*g_pRdroid_HS->pFread)(iVar3,&cel,0x18);
        *(uint *)*ppvVar5 = cel.dwType;
        *(uint *)((int)*ppvVar5 + 4) = cel.dwUnknown4;
        *(uint *)((int)*ppvVar5 + 8) = cel.dwUnknown8;
        *(uint *)((int)*ppvVar5 + 0xc) = cel.dwUnknownC;
        *(uint *)((int)*ppvVar5 + 0x10) = cel.dwUnknown10;
        *(uint *)((int)*ppvVar5 + 0x14) = cel.dwUnknown14;
        if ((cel.dwType & 8) != 0) {
          (*g_pRdroid_HS->pFread)(iVar3,&celColor,0x10);
          *(uint *)((int)*ppvVar5 + 0x18) = celColor.dwColor;
          *piVar9 = celColor.nTexture;
        }
        uStack_428 = uStack_428 + 1;
        ppvVar5 = ppvVar5 + 1;
        piVar9 = piVar9 + 1;
      } while (uStack_428 < (uint)material->nNumCels);
    }
    *(undefined4 *)&material->field_0xac = 0;
    if (material->nNumTextures != 0) {
      iVar4 = (*g_pRdroid_HS->pAlloc)
                        (material->nNumTextures * 0x4ec,s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84,
                         DAT_004ddd80 + 0x7e);
      *(int *)&material->field_0xac = iVar4;
      if (iVar4 == 0) goto LAB_0041833a;
    }
    uStack_428 = 0;
    if (material->nNumTextures != 0) {
      iStack_420 = 0;
      do {
        (*g_pRdroid_HS->pFread)(iVar3,&texHeader,0x18);
        puVar8 = (uint *)(iStack_420 + *(int *)&material->field_0xac);
        *puVar8 = texHeader.dwUnknown8;
        puVar8[1] = texHeader.dwUnknownC;
        uVar1 = stdCalcBitPos(texHeader.nWidth);
        puVar8[3] = uVar1;
        puVar8[4] = texHeader.nWidth - 1;
        uVar1 = 0;
        puVar8[5] = texHeader.nHeight - 1;
        puVar8[6] = texHeader.nMipmaps;
        puVar8[2] = texHeader.dwUnknown10;
        VStack_3d8.nWidth = texHeader.nWidth;
        VStack_3d8.nHeight = texHeader.nHeight;
        VStack_3d8.colorFormat.nColorMode = *(int *)&material->field_0x28;
        VStack_3d8.colorFormat.nBpp = *(int *)&material->field_0x2c;
        if (puVar8[6] != 0) {
          puVar11 = puVar8 + 7;
          puVar6 = puVar8 + 0x2e;
          do {
            puVar6[-5] = 0;
            *puVar6 = 0;
            puVar6[0x93] = 0;
            puVar6[0x98] = 0;
            surface = stdDisplay_VBufferNew(&VStack_3d8,a,b,0);
            *puVar11 = (uint)surface;
            if (surface == (VBuffer *)0x0) goto LAB_0041833a;
            if ((*puVar8 & 1) != 0) {
              stdDisplay_VBufferSetColorKey(surface,puVar8[2]);
            }
            stdDisplay_VBufferLock((VBuffer *)*puVar11);
            (*g_pRdroid_HS->pFread)
                      (iVar3,*(undefined4 *)(*puVar11 + 0x5c),*(undefined4 *)(*puVar11 + 0x14));
            stdDisplay_VBufferUnlock((VBuffer *)*puVar11);
            VStack_3d8.nWidth = (uint)VStack_3d8.nWidth >> 1;
            VStack_3d8.nHeight = (uint)VStack_3d8.nHeight >> 1;
            uVar1 = uVar1 + 1;
            puVar11 = puVar11 + 1;
            puVar6 = puVar6 + 0x26;
          } while (uVar1 < puVar8[6]);
        }
        uStack_428 = uStack_428 + 1;
        iStack_420 = iStack_420 + 0x4ec;
      } while (uStack_428 < (uint)material->nNumTextures);
    }
    uVar1 = 0;
    if (material->nNumCels != 0) {
      piVar9 = aiStack_340;
      ppvVar5 = material->aCels;
      do {
        if ((*(byte *)*ppvVar5 & 8) != 0) {
          *(int *)((int)*ppvVar5 + 0x1c) = *(int *)&material->field_0xac + *piVar9 * 0x4ec;
        }
        uVar1 = uVar1 + 1;
        piVar9 = piVar9 + 1;
        ppvVar5 = ppvVar5 + 1;
      } while (uVar1 < (uint)material->nNumCels);
    }
    if ((material->dwType & 1) != 0) {
      (*g_pRdroid_HS->pFread)(iVar3,auStack_300,0x300);
    }
    uVar1 = 0x1f;
    puVar8 = (uint *)stdFileFromPath(filename);
    strncpy((uint *)material->aName,puVar8,uVar1);
    material->aName[0x1f] = '\0';
    (*g_pRdroid_HS->pFclose)(iVar3);
    return 1;
  }
LAB_0041833a:
  (*g_pRdroid_HS->pFclose)(iVar3);
  return 0;
}
#undef VStack_3d8
#undef aiStack_340
#undef auStack_300


/* ---- 0x00418360  rdMaterial_Free ---- */
void __cdecl rdMaterial_Free(uint material)

{
  if (g_dwMaterialsUnloader != 0) {
    (*(code_std *)g_dwMaterialsUnloader)(material);
    return;
  }
  rdMaterial_FreeEntry(material);
  (*g_pRdroid_HS->pFree)(material);
  return;
}

/* ---- 0x004183a0  rdMaterial_FreeEntry ---- */
/* Frees the cel bitmaps, their mip surfaces and Direct3D textures Original name
   rdMaterial_FreeEntry (the remaster's GrimFandango (Linux): same body (frees the +0x68 colormap
   entries, the texture VBuffers of every cel, then the +0xac array); called by the material
   resource handler's free message in both builds); was rdMaterial_FreeContents. */

void __cdecl rdMaterial_FreeEntry(int material)

{
  undefined4 *puVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  uint local_8;
  uint local_4;
  
  uVar3 = 0;
  if (*(int *)(material + 0x60) != 0) {
    puVar1 = (undefined4 *)(material + 0x68);
    do {
      (*g_pRdroid_HS->pFree)(*puVar1);
      uVar3 = uVar3 + 1;
      puVar1 = puVar1 + 1;
    } while (uVar3 < *(uint *)(material + 0x60));
  }
  local_4 = 0;
  if (*(int *)(material + 0xa8) != 0) {
    puVar2 = (uint *)(*(int *)(material + 0xac) + 0x18);
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
    } while (local_4 < *(uint *)(material + 0xa8));
  }
  if (*(int *)(material + 0xac) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(material + 0xac));
  }
  return;
}

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


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_004ddd7c[4] __asm__("_DAT_004ddd7c");
extern unsigned char grim_def_DAT_004ddd80[4] __asm__("_DAT_004ddd80");
extern unsigned int grim_def_g_dwMaterialsLoader __asm__("_g_dwMaterialsLoader");
extern unsigned int grim_def_g_dwMaterialsUnloader __asm__("_g_dwMaterialsUnloader");
extern char grim_def_s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84[44] __asm__("_s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84");
extern char grim_def_s_MAT_004dddb0[40] __asm__("_s_MAT_004dddb0");
/* 0x004ddd7c, 4 bytes */ GRIM_DATA("004ddd7c") unsigned char grim_def_DAT_004ddd7c[4] __asm__("_DAT_004ddd7c") = { 0x7b };
/* 0x004ddd80, 4 bytes */ GRIM_DATA("004ddd80") unsigned char grim_def_DAT_004ddd80[4] __asm__("_DAT_004ddd80") = { 0xad };
/* 0x004ddd84, 44 bytes */ GRIM_DATA("004ddd84") char grim_def_s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84[44] __asm__("_s_C__grimjedi_Libs_RDroid_Engine_R_004ddd84") = "C:\\grimjedi\\Libs\\RDroid\\Engine\\Rdmaterial.c";
/* 0x004dddb0, 40 bytes */ GRIM_DATA("004dddb0") char grim_def_s_MAT_004dddb0[40] __asm__("_s_MAT_004dddb0") = "MAT \000\000\000\0009\000\000\000\000\000\000\000\002\000\000\000\001\000\000\000\000\000\000\000\002\000\000\000\001";
/* 0x007f4238, 4 bytes */ /* loose */ unsigned int grim_def_g_dwMaterialsLoader __asm__("_g_dwMaterialsLoader") = 0x0;
/* 0x007f423c, 4 bytes */ /* loose */ unsigned int grim_def_g_dwMaterialsUnloader __asm__("_g_dwMaterialsUnloader") = 0x0;
