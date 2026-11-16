/* GRIMFANDANGO.EXE :: rdcolormap.c
 * functions 0x00404380 .. 0x00404b30 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00404380  rdColormap_SetCurrent ---- */
uint __cdecl rdColormap_SetCurrent(uint colormap)

{
  if ((g_dwRdColormap_pCurMap != colormap) &&
     (g_dwRdColormap_pCurMap = colormap, 0 < g_nRdroid_curAcceleration)) {
    std3D_SetCurrentPalette((void *)(colormap + 0x30),0x5a);
  }
  return 1;
}

/* ---- 0x004043c0  rdColormap_Load ---- */
/* RDroid/Engine/Rdcolormap.c: allocates a 0x350-byte colormap and loads it from the named .CMP file
    */

rdColormap * __cdecl rdColormap_Load(char *name)

{
  rdColormap *cmp;
  int iVar1;
  rdColormap *prVar2;
  
  cmp = (rdColormap *)
        (*g_pRdroid_HS->pAlloc)(0x350,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,DAT_004ddad8 + 4);
  if (cmp != (rdColormap *)0x0) {
    prVar2 = cmp;
    for (iVar1 = 0xd4; iVar1 != 0; iVar1 = iVar1 + -1) {
      prVar2->aName[0] = '\0';
      prVar2->aName[1] = '\0';
      prVar2->aName[2] = '\0';
      prVar2->aName[3] = '\0';
      prVar2 = (rdColormap *)(prVar2->aName + 4);
    }
    iVar1 = rdColormap_LoadEntry(name,cmp);
    if (iVar1 != 0) {
      return cmp;
    }
  }
  rdColormap_Free((uint)cmp);
  return (rdColormap *)0x0;
}

/* ---- 0x00404420  rdColormap_LoadEntry ---- */
/* Reads the CMP header (flags, tint), the 768-byte palette, the 0x10000-byte light-level table and
   optional 0x8000-byte transparency table. Falls back to the grey ramp when the magic is wrong. */

int __cdecl rdColormap_LoadEntry(char *name,rdColormap *cmp)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  uint *puVar6;
  ushort *table;
  byte *pbVar7;
  int iVar8;
  uint uVar9;
  #define acStack_40 (*(char (*)[8])(_frame + (0x50 - 0x40)))
  #define uStack_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define fStack_34 (*(float *)(_frame + (0x50 - 0x34)))
  #define fStack_30 (*(float *)(_frame + (0x50 - 0x30)))
  #define fStack_2c (*(float *)(_frame + (0x50 - 0x2c)))
  
  iVar5 = (*g_pRdroid_HS->pFopen)(name,s_rb_004ddb18);
  if (iVar5 == 0) {
    return 0;
  }
  uVar9 = 0x1f;
  puVar6 = (uint *)stdFileFromPath(name);
  strncpy((uint *)cmp,puVar6,uVar9);
  cmp->aName[0x1f] = '\0';
  (*g_pRdroid_HS->pFread)(iVar5,acStack_40,0x40);
  cmp->aTint[0] = fStack_34;
  cmp->dwFlags = uStack_38;
  cmp->aTint[1] = fStack_30;
  cmp->aTint[2] = fStack_2c;
  uVar9 = strncmp(acStack_40,s_CMP_004ddb10,4);
  if (uVar9 != 0) {
    (*g_pRdroid_HS->pFclose)(iVar5);
    rdColormap_BuildGrayRamp(cmp);
    return 1;
  }
  pbVar7 = cmp->aPalette;
  (*g_pRdroid_HS->pFread)(iVar5,pbVar7,0x300);
  bVar1 = *pbVar7;
  bVar2 = cmp->aPalette[1];
  bVar3 = cmp->aPalette[2];
  iVar8 = 0xfe;
  do {
    bVar4 = *pbVar7;
    if (bVar4 == bVar1) {
      if (bVar4 < 0xf7) {
        bVar4 = bVar4 + 8;
      }
      else {
        bVar4 = bVar4 - 8;
      }
      *pbVar7 = bVar4;
    }
    bVar4 = cmp->aPalette[1];
    if (bVar4 == bVar2) {
      if (bVar4 < 0xf7) {
        bVar4 = bVar4 + 8;
      }
      else {
        bVar4 = bVar4 - 8;
      }
      cmp->aPalette[1] = bVar4;
    }
    bVar4 = cmp->aPalette[2];
    if (bVar4 == bVar3) {
      if (bVar4 < 0xf7) {
        bVar4 = bVar4 + 8;
      }
      else {
        bVar4 = bVar4 - 8;
      }
      cmp->aPalette[2] = bVar4;
    }
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  if ((cmp->dwFlags & 4) == 0) {
    cmp->pRGB16 = (ushort *)0x0;
  }
  else {
    table = (ushort *)
            (*g_pRdroid_HS->pAlloc)
                      (0x8000,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,DAT_004ddadc + 0x4b);
    cmp->pRGB16 = table;
    if (table == (ushort *)0x0) goto LAB_00404659;
    rdColormap_BuildRGB16(table,(ushort *)pbVar7,0,0,0,((unsigned)(uintptr_t)&g_dwRdColormap_colorInfo));
  }
  if ((cmp->dwFlags & 1) != 0) {
    pbVar7 = (byte *)(*g_pRdroid_HS->pAlloc)
                               (0x10100,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,
                                DAT_004ddadc + 0x68);
    cmp->pLightLevelsAlloc = pbVar7;
    if (pbVar7 == (byte *)0x0) {
LAB_00404659:
      (*g_pRdroid_HS->pFclose)(iVar5);
      rdColormap_BuildGrayRamp(cmp);
      return 1;
    }
    cmp->pLightLevels = pbVar7;
    if (((uint)pbVar7 & 0xff) != 0) {
      cmp->pLightLevels = pbVar7 + (0x100 - ((uint)pbVar7 & 0xff));
    }
    (*g_pRdroid_HS->pFread)(iVar5,cmp->pLightLevels,0x10000);
    if ((cmp->dwFlags & 4) == 0) {
      *(undefined4 *)&cmp->field_0x34c = 0;
      cmp->pTransparency = (byte *)0x0;
      cmp->pTransparencyAlloc = (byte *)0x0;
    }
    else {
      iVar8 = (*g_pRdroid_HS->pAlloc)
                        (0x10000,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,DAT_004ddadc + 0x76);
      *(int *)&cmp->field_0x34c = iVar8;
      if (iVar8 == 0) goto LAB_00404659;
      if (UINT_004ddaac == 5) {
        (*g_pRdroid_HS->pFseek)(iVar5,0x10000,1);
        (*g_pRdroid_HS->pFread)(iVar5,*(undefined4 *)&cmp->field_0x34c,0x10000);
        cmp->pTransparency = (byte *)0x0;
        cmp->pTransparencyAlloc = (byte *)0x0;
      }
      else {
        (*g_pRdroid_HS->pFread)(iVar5,iVar8,0x10000);
        (*g_pRdroid_HS->pFseek)(iVar5,0x10000,1);
        cmp->pTransparency = (byte *)0x0;
        cmp->pTransparencyAlloc = (byte *)0x0;
      }
    }
  }
  (*g_pRdroid_HS->pFclose)(iVar5);
  return 1;
}
#undef acStack_40
#undef fStack_2c
#undef fStack_30
#undef fStack_34
#undef uStack_38


/* ---- 0x00404730  rdColormap_Free ---- */
void __cdecl rdColormap_Free(uint colormap)

{
  rdColormap_FreeEntry(colormap);
  (*g_pRdroid_HS->pFree)(colormap);
  return;
}

/* ---- 0x00404750  rdColormap_FreeEntry ---- */
void __cdecl rdColormap_FreeEntry(int colormap)

{
  if (*(int *)(colormap + 0x334) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(colormap + 0x334));
    *(undefined4 *)(colormap + 0x334) = 0;
  }
  if (*(int *)(colormap + 0x348) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(colormap + 0x348));
    *(undefined4 *)(colormap + 0x348) = 0;
  }
  if ((*(byte *)(colormap + 0x20) & 1) != 0) {
    if (*(int *)(colormap + 0x33c) != 0) {
      (*g_pRdroid_HS->pFree)(*(int *)(colormap + 0x33c));
      *(undefined4 *)(colormap + 0x33c) = 0;
    }
    if (*(int *)(colormap + 0x34c) != 0) {
      (*g_pRdroid_HS->pFree)(*(int *)(colormap + 0x34c));
      *(undefined4 *)(colormap + 0x34c) = 0;
    }
  }
  return;
}

/* ---- 0x004047e0  rdColormap_BuildRGB16 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Converts the 256-entry palette into 16-bit pixel values for 64 light levels using the
   pixel-format shifts Original name rdColormap_BuildRGB16 (the remaster's GrimFandango (Linux):
   aligned call in rdColormap_LoadEntry, sputResource_ColormapHandler); was
   rdColormap_Build16bitTables. */

undefined8 __cdecl
rdColormap_BuildRGB16(undefined2 *table,ushort *palette,uint r,uint g,uint b,int fmt)

{
  byte *pbVar1;
  byte bVar2;
  float10 fVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  ushort *puVar7;
  uint uVar8;
  uint unaff_EBX;
  uint uVar9;
  int iVar10;
  ushort *puVar11;
  undefined2 *puVar12;
  undefined2 *puVar13;
  float10 fVar14;
  float10 fVar15;
  float10 fVar16;
  float10 extraout_ST0;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  longlong lVar17;
  longlong lVar18;
  longlong lVar19;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  uVar6 = r & 0xff;
  uVar8 = 0;
  local_10 = 8;
  puVar7 = palette;
  puVar12 = table;
  do {
    uVar4 = *puVar7;
    bVar2 = *(byte *)((int)puVar7 + 1);
    uVar8 = CONCAT31((int3)(uVar8 >> 8),bVar2);
    iVar10 = 0x40;
    uVar5 = puVar7[1];
    puVar7 = (ushort *)((int)puVar7 + 3);
    puVar13 = puVar12;
    do {
      uVar9 = CONCAT22((short)(unaff_EBX >> 0x10),
                       (ushort)(byte)((byte)uVar4 >> (*(byte *)(fmt + 0x20) & 0x1f))) <<
              ((byte)*(undefined4 *)(fmt + 0x14) & 0x1f);
      unaff_EBX = CONCAT22((short)(uVar9 >> 0x10),
                           (ushort)(byte)((byte)uVar5 >> (*(byte *)(fmt + 0x28) & 0x1f))) <<
                  ((byte)*(undefined4 *)(fmt + 0x1c) & 0x1f);
      uVar8 = CONCAT22((short)(uVar8 >> 0x10),(ushort)(bVar2 >> (*(byte *)(fmt + 0x24) & 0x1f))) <<
              ((byte)*(undefined4 *)(fmt + 0x18) & 0x1f) | uVar9 | unaff_EBX;
      iVar10 = iVar10 + -1;
      *puVar13 = (short)uVar8;
      puVar13 = puVar13 + 0x100;
    } while (iVar10 != 0);
    puVar12 = puVar12 + 1;
    local_10 = local_10 - 1;
  } while (local_10 != 0);
  r = 0xf8;
  puVar7 = palette + 0xc;
  palette = table + 0x3f08;
  do {
    pbVar1 = (byte *)((int)puVar7 + 1);
    fVar14 = (float10)PUN(float,(byte)*puVar7);
    puVar7 = (ushort *)((int)puVar7 + 3);
    table = (undefined2 *)0x40;
    fVar15 = ((float10)uVar6 - fVar14) * (float10)0.015625f;
    fVar16 = ((float10)(g & 0xff) - (float10)*pbVar1) * (float10)0.015625f;
    puVar11 = palette;
    do {
      if (fVar15 + fVar14 <= (float10)0.0f) {
        fVar3 = (float10)0.5;
      }
      else {
        fVar3 = (float10)-0.5;
      }
      lVar17 = FTOL((fVar15 + fVar14) - fVar3);
      if (fVar15 <= (float10)0.0f) {
        fVar14 = (float10)0.5;
      }
      else {
        fVar14 = (float10)-0.5;
      }
      lVar18 = FTOL(fVar15 - fVar14);
      if (extraout_ST0 <= (float10)0.0f) {
        fVar3 = (float10)0.5;
      }
      else {
        fVar3 = (float10)-0.5;
      }
      fVar15 = extraout_ST1;
      fVar14 = fVar16;
      lVar19 = FTOL(extraout_ST0 - fVar3);
      table = (undefined2 *)((int)table + -1);
      *puVar11 = (ushort)(((int)lVar18 >> ((byte)*(undefined4 *)(fmt + 0x24) & 0x1f)) <<
                         ((byte)*(undefined4 *)(fmt + 0x18) & 0x1f)) |
                 (ushort)(((int)lVar19 >> ((byte)*(undefined4 *)(fmt + 0x28) & 0x1f)) <<
                         ((byte)*(undefined4 *)(fmt + 0x1c) & 0x1f)) |
                 (ushort)(((int)lVar17 >> ((byte)*(undefined4 *)(fmt + 0x20) & 0x1f)) <<
                         ((byte)*(undefined4 *)(fmt + 0x14) & 0x1f));
      puVar11 = puVar11 + -0x100;
      fVar16 = extraout_ST1_00;
    } while (table != (undefined2 *)0x0);
    palette = palette + 1;
    r = r - 1;
  } while (r != 0);
  return CONCAT44((int)((ulonglong)lVar19 >> 0x20),1);
}
#endif


/* ---- 0x00404a40  rdColormap_BuildGrayRamp ---- */
/* Fills the colormap with the synthetic GREYRAMP.CMP palette and 64 light levels Original name
   rdColormap_BuildGrayRamp (the remaster's GrimFandango (Linux): same body (name "GREYRAMP.CMP",
   the tint 1.0 / 1.0 / 1.0, the ramp)); was rdColormap_BuildGreyRamp. */

uint __cdecl rdColormap_BuildGrayRamp(rdColormap *colormap)

{
  byte *pbVar1;
  byte *pbVar2;
  uint uVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  
  colormap->aName[0] = '\0';
  colormap->aName[1] = '\0';
  colormap->aName[2] = '\0';
  colormap->aName[3] = '\0';
  strncpy((uint *)colormap,(uint *)s_GREYRAMP_CMP_004ddb20,0x1f);
  colormap->aName[0x1f] = '\0';
  colormap->dwFlags = 0;
  colormap->aTint[0] = 1.0f;
  colormap->aTint[1] = 1.0f;
  colormap->aTint[2] = 1.0f;
  uVar3 = (*g_pRdroid_HS->pAlloc)
                    (0x4100,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,DAT_004ddae0 + 0x10);
  *(uint *)&colormap->field_0x334 = uVar3;
  if (uVar3 == 0) {
    return 0;
  }
  *(uint *)&colormap->field_0x330 = uVar3;
  if ((uVar3 & 0xff) != 0) {
    *(uint *)&colormap->field_0x330 = (uVar3 - (uVar3 & 0xff)) + 0x100;
  }
  pbVar1 = colormap->aPalette + 1;
  uVar3 = 0;
  do {
    pbVar2 = pbVar1 + uVar3;
    uVar6 = 0;
    bVar4 = (byte)uVar3;
    pbVar2[(int)colormap + (0x30 - (int)pbVar1)] = bVar4;
    *pbVar2 = bVar4;
    pbVar2[(int)colormap + (0x32 - (int)pbVar1)] = bVar4;
    uVar5 = 0;
    do {
      *(byte *)(uVar3 + *(int *)&colormap->field_0x330 + uVar5) = (char)(uVar6 >> 6) * bVar4;
      uVar5 = uVar5 + 0x100;
      uVar6 = uVar6 + 1;
    } while (uVar5 < 0x4000);
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x100);
  return 1;
}

/* ---- 0x00404b30  rdColormap_Size ---- */
/* Original name rdColormap_Size (the remaster's GrimFandango (Linux): same body (0x350 + 0x4100 /
   0x10100 / 0x8000 / 0x10000 by the table flags); sputResource_ColormapHandler's size query); was
   FUN_00404b30. */

int __cdecl rdColormap_Size(int colormap)

{
  int iVar1;
  
  iVar1 = 0x350;
  if (*(int *)(colormap + 0x334) != 0) {
    iVar1 = 0x4450;
  }
  if (*(int *)(colormap + 0x33c) != 0) {
    iVar1 = iVar1 + 0x10100;
  }
  if (*(int *)(colormap + 0x348) != 0) {
    iVar1 = iVar1 + 0x8000;
  }
  if (*(int *)(colormap + 0x34c) != 0) {
    iVar1 = iVar1 + 0x10000;
  }
  return iVar1;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_004ddad8[4] __asm__("_DAT_004ddad8");
extern unsigned char grim_def_DAT_004ddadc[4] __asm__("_DAT_004ddadc");
extern unsigned char grim_def_DAT_004ddae0[4] __asm__("_DAT_004ddae0");
extern unsigned char grim_def_UINT_004ddaac[8] __asm__("_UINT_004ddaac");
extern char grim_def_s_CMP_004ddb10[8] __asm__("_s_CMP_004ddb10");
extern char grim_def_s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4[44] __asm__("_s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4");
extern char grim_def_s_GREYRAMP_CMP_004ddb20[16] __asm__("_s_GREYRAMP_CMP_004ddb20");
/* 0x004ddaac, 8 bytes */ GRIM_DATA("004ddaac") unsigned char grim_def_UINT_004ddaac[8] __asm__("_UINT_004ddaac") = { 0x06, 0x00, 0x00, 0x00, 0x05 };
/* 0x004ddad8, 4 bytes */ GRIM_DATA("004ddad8") unsigned char grim_def_DAT_004ddad8[4] __asm__("_DAT_004ddad8") = { 0x99 };
/* 0x004ddadc, 4 bytes */ GRIM_DATA("004ddadc") unsigned char grim_def_DAT_004ddadc[4] __asm__("_DAT_004ddadc") = { 0xc6 };
/* 0x004ddae0, 4 bytes */ GRIM_DATA("004ddae0") unsigned char grim_def_DAT_004ddae0[4] __asm__("_DAT_004ddae0") = { 0x14, 0x03 };
/* 0x004ddae4, 44 bytes */ GRIM_DATA("004ddae4") char grim_def_s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4[44] __asm__("_s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4") = "C:\\grimjedi\\Libs\\RDroid\\Engine\\Rdcolormap.c";
/* 0x004ddb10, 8 bytes */ GRIM_DATA("004ddb10") char grim_def_s_CMP_004ddb10[8] __asm__("_s_CMP_004ddb10") = "CMP ";
/* 0x004ddb20, 16 bytes */ GRIM_DATA("004ddb20") char grim_def_s_GREYRAMP_CMP_004ddb20[16] __asm__("_s_GREYRAMP_CMP_004ddb20") = "GREYRAMP.CMP";
