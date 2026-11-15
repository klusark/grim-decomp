/* GRIMFANDANGO.EXE :: rdcolormap.c
 * functions 0x00404380 .. 0x00404b30 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00404380  rdColormap_SetCurrent ---- */
uint __cdecl rdColormap_SetCurrent(uint param_1)

{
  if ((g_dwRdColormap_pCurMap != param_1) &&
     (g_dwRdColormap_pCurMap = param_1, 0 < g_nRdroid_curAcceleration)) {
    std3D_SetCurrentPalette((void *)(param_1 + 0x30),0x5a);
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
  ushort *puVar7;
  byte *pbVar8;
  int iVar9;
  uint uVar10;
  #define acStack_40 (*(char (*)[8])(_frame + (0x50 - 0x40)))
  #define uStack_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define fStack_34 (*(float *)(_frame + (0x50 - 0x34)))
  #define fStack_30 (*(float *)(_frame + (0x50 - 0x30)))
  #define fStack_2c (*(float *)(_frame + (0x50 - 0x2c)))
  
  iVar5 = (*g_pRdroid_HS->pFopen)(name,&DAT_004ddb18);
  if (iVar5 == 0) {
    return 0;
  }
  uVar10 = 0x1f;
  puVar6 = (uint *)stdFileFromPath(name);
  strncpy((uint *)cmp,puVar6,uVar10);
  cmp->aName[0x1f] = '\0';
  (*g_pRdroid_HS->pFread)(iVar5,acStack_40,0x40);
  cmp->aTint[0] = fStack_34;
  cmp->dwFlags = uStack_38;
  cmp->aTint[1] = fStack_30;
  cmp->aTint[2] = fStack_2c;
  uVar10 = strncmp(acStack_40,&DAT_004ddb10,4);
  if (uVar10 != 0) {
    (*g_pRdroid_HS->pFclose)(iVar5);
    rdColormap_BuildGrayRamp(cmp);
    return 1;
  }
  pbVar8 = cmp->aPalette;
  (*g_pRdroid_HS->pFread)(iVar5,pbVar8,0x300);
  bVar1 = *pbVar8;
  bVar2 = cmp->aPalette[1];
  bVar3 = cmp->aPalette[2];
  iVar9 = 0xfe;
  do {
    bVar4 = *pbVar8;
    if (bVar4 == bVar1) {
      if (bVar4 < 0xf7) {
        bVar4 = bVar4 + 8;
      }
      else {
        bVar4 = bVar4 - 8;
      }
      *pbVar8 = bVar4;
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
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  if ((cmp->dwFlags & 4) == 0) {
    cmp->pRGB16 = (ushort *)0x0;
  }
  else {
    puVar7 = (ushort *)
             (*g_pRdroid_HS->pAlloc)
                       (0x8000,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,DAT_004ddadc + 0x4b);
    cmp->pRGB16 = puVar7;
    if (puVar7 == (ushort *)0x0) goto LAB_00404659;
    rdColormap_BuildRGB16(puVar7,(ushort *)pbVar8,0,0,0,((unsigned)(uintptr_t)&g_dwRdColormap_colorInfo));
  }
  if ((cmp->dwFlags & 1) != 0) {
    pbVar8 = (byte *)(*g_pRdroid_HS->pAlloc)
                               (0x10100,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,
                                DAT_004ddadc + 0x68);
    cmp->pLightLevelsAlloc = pbVar8;
    if (pbVar8 == (byte *)0x0) {
LAB_00404659:
      (*g_pRdroid_HS->pFclose)(iVar5);
      rdColormap_BuildGrayRamp(cmp);
      return 1;
    }
    cmp->pLightLevels = pbVar8;
    if (((uint)pbVar8 & 0xff) != 0) {
      cmp->pLightLevels = pbVar8 + (0x100 - ((uint)pbVar8 & 0xff));
    }
    (*g_pRdroid_HS->pFread)(iVar5,cmp->pLightLevels,0x10000);
    if ((cmp->dwFlags & 4) == 0) {
      *(undefined4 *)&cmp->field_0x34c = 0;
      cmp->pTransparency = (byte *)0x0;
      cmp->pTransparencyAlloc = (byte *)0x0;
    }
    else {
      iVar9 = (*g_pRdroid_HS->pAlloc)
                        (0x10000,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,DAT_004ddadc + 0x76);
      *(int *)&cmp->field_0x34c = iVar9;
      if (iVar9 == 0) goto LAB_00404659;
      if (UINT_004ddaac == 5) {
        (*g_pRdroid_HS->pFseek)(iVar5,0x10000,1);
        (*g_pRdroid_HS->pFread)(iVar5,*(undefined4 *)&cmp->field_0x34c,0x10000);
        cmp->pTransparency = (byte *)0x0;
        cmp->pTransparencyAlloc = (byte *)0x0;
      }
      else {
        (*g_pRdroid_HS->pFread)(iVar5,iVar9,0x10000);
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
void __cdecl rdColormap_Free(uint param_1)

{
  rdColormap_FreeEntry(param_1);
  (*g_pRdroid_HS->pFree)(param_1);
  return;
}

/* ---- 0x00404750  rdColormap_FreeEntry ---- */
void __cdecl rdColormap_FreeEntry(int param_1)

{
  if (*(int *)(param_1 + 0x334) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(param_1 + 0x334));
    *(undefined4 *)(param_1 + 0x334) = 0;
  }
  if (*(int *)(param_1 + 0x348) != 0) {
    (*g_pRdroid_HS->pFree)(*(int *)(param_1 + 0x348));
    *(undefined4 *)(param_1 + 0x348) = 0;
  }
  if ((*(byte *)(param_1 + 0x20) & 1) != 0) {
    if (*(int *)(param_1 + 0x33c) != 0) {
      (*g_pRdroid_HS->pFree)(*(int *)(param_1 + 0x33c));
      *(undefined4 *)(param_1 + 0x33c) = 0;
    }
    if (*(int *)(param_1 + 0x34c) != 0) {
      (*g_pRdroid_HS->pFree)(*(int *)(param_1 + 0x34c));
      *(undefined4 *)(param_1 + 0x34c) = 0;
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
rdColormap_BuildRGB16
          (undefined2 *param_1,ushort *param_2,uint param_3,uint param_4,uint param_5,int param_6)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
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
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar6 = param_3 & 0xff;
  uVar8 = 0;
  local_10 = 8;
  puVar7 = param_2;
  puVar12 = param_1;
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
                       (ushort)(byte)((byte)uVar4 >> (*(byte *)(param_6 + 0x20) & 0x1f))) <<
              ((byte)*(undefined4 *)(param_6 + 0x14) & 0x1f);
      unaff_EBX = CONCAT22((short)(uVar9 >> 0x10),
                           (ushort)(byte)((byte)uVar5 >> (*(byte *)(param_6 + 0x28) & 0x1f))) <<
                  ((byte)*(undefined4 *)(param_6 + 0x1c) & 0x1f);
      uVar8 = CONCAT22((short)(uVar8 >> 0x10),(ushort)(bVar2 >> (*(byte *)(param_6 + 0x24) & 0x1f)))
              << ((byte)*(undefined4 *)(param_6 + 0x18) & 0x1f) | uVar9 | unaff_EBX;
      iVar10 = iVar10 + -1;
      *puVar13 = (short)uVar8;
      puVar13 = puVar13 + 0x100;
    } while (iVar10 != 0);
    puVar12 = puVar12 + 1;
    local_10 = local_10 - 1;
  } while (local_10 != 0);
  param_3 = 0xf8;
  puVar7 = param_2 + 0xc;
  param_2 = param_1 + 0x3f08;
  do {
    pbVar1 = (byte *)((int)puVar7 + 1);
    fVar14 = (float10)PUN(float,(byte)*puVar7);
    puVar7 = (ushort *)((int)puVar7 + 3);
    param_1 = (undefined2 *)0x40;
    fVar15 = ((float10)uVar6 - fVar14) * (float10)0.015625f;
    fVar16 = ((float10)(param_4 & 0xff) - (float10)*pbVar1) * (float10)0.015625f;
    puVar11 = param_2;
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
      param_1 = (undefined2 *)((int)param_1 + -1);
      *puVar11 = (ushort)(((int)lVar18 >> ((byte)*(undefined4 *)(param_6 + 0x24) & 0x1f)) <<
                         ((byte)*(undefined4 *)(param_6 + 0x18) & 0x1f)) |
                 (ushort)(((int)lVar19 >> ((byte)*(undefined4 *)(param_6 + 0x28) & 0x1f)) <<
                         ((byte)*(undefined4 *)(param_6 + 0x1c) & 0x1f)) |
                 (ushort)(((int)lVar17 >> ((byte)*(undefined4 *)(param_6 + 0x20) & 0x1f)) <<
                         ((byte)*(undefined4 *)(param_6 + 0x14) & 0x1f));
      puVar11 = puVar11 + -0x100;
      fVar16 = extraout_ST1_00;
    } while (param_1 != (undefined2 *)0x0);
    param_2 = param_2 + 1;
    param_3 = param_3 - 1;
  } while (param_3 != 0);
  return CONCAT44((int)((ulonglong)lVar19 >> 0x20),1);
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c

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

int __cdecl rdColormap_Size(int param_1)

{
  int iVar1;
  
  iVar1 = 0x350;
  if (*(int *)(param_1 + 0x334) != 0) {
    iVar1 = 0x4450;
  }
  if (*(int *)(param_1 + 0x33c) != 0) {
    iVar1 = iVar1 + 0x10100;
  }
  if (*(int *)(param_1 + 0x348) != 0) {
    iVar1 = iVar1 + 0x8000;
  }
  if (*(int *)(param_1 + 0x34c) != 0) {
    iVar1 = iVar1 + 0x10000;
  }
  return iVar1;
}
