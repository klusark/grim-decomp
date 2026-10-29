/* GRIMFANDANGO.EXE :: rdcolormap.c
 * functions 0x00404380 .. 0x00404b30 (8 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00404380  rdColormap_SetCurrent ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
undefined4 rdColormap_SetCurrent(uint param_1)

{
  if ((UINT_004f5ec4 != param_1) && (UINT_004f5ec4 = param_1, 0 < g_nRdroid3DAccel)) {
    Display_SetPalette3D((void *)(param_1 + 0x30),0x5a);
  }
  return 1;
}
#endif


/* ---- 0x004043c0  rdColormap_Load ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* RDroid/Engine/Rdcolormap.c: allocates a 0x350-byte colormap and loads it from the named .CMP file
    */

void * __cdecl rdColormap_Load(char *name)

{
  undefined4 *cmp;
  int iVar1;
  undefined4 *puVar2;
  
  cmp = (undefined4 *)
        (*g_pSvcRdroid->pAlloc)(0x350,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,DAT_004ddad8 + 4);
  if (cmp != (undefined4 *)0x0) {
    puVar2 = cmp;
    for (iVar1 = 0xd4; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    iVar1 = rdColormap_LoadEntry(name,cmp);
    if (iVar1 != 0) {
      return cmp;
    }
  }
  rdColormap_Free(cmp);
  return (void *)0x0;
}
#endif


/* ---- 0x00404420  rdColormap_LoadEntry ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Reads the CMP header (flags, tint), the 768-byte palette, the 0x10000-byte light-level table and
   optional 0x8000-byte transparency table. Falls back to the grey ramp when the magic is wrong. */

int __cdecl rdColormap_LoadEntry(char *name,void *cmp)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort *puVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  undefined2 *puVar10;
  uint uVar11;
  undefined4 uVar12;
  #define auStack_40 (*(undefined1 (*)[8])(_frame + (0x50 - 0x40)))
  #define uStack_38 (*(undefined4 *)(_frame + (0x50 - 0x38)))
  #define uStack_34 (*(undefined4 *)(_frame + (0x50 - 0x34)))
  #define uStack_30 (*(undefined4 *)(_frame + (0x50 - 0x30)))
  #define uStack_2c (*(undefined4 *)(_frame + (0x50 - 0x2c)))
  
  iVar7 = (*g_pSvcRdroid->pFopen)(name,&DAT_004ddb18);
  if (iVar7 == 0) {
    return 0;
  }
  uVar12 = 0x1f;
  pcVar8 = Str_FileNameFromPath(name);
  strncpy(cmp,pcVar8,uVar12);
  *(undefined1 *)((int)cmp + 0x1f) = 0;
  (*g_pSvcRdroid->pFread)(iVar7,auStack_40,0x40);
  *(undefined4 *)((int)cmp + 0x24) = uStack_34;
  *(undefined4 *)((int)cmp + 0x20) = uStack_38;
  *(undefined4 *)((int)cmp + 0x28) = uStack_30;
  *(undefined4 *)((int)cmp + 0x2c) = uStack_2c;
  iVar9 = strncmp(auStack_40,&DAT_004ddb10,4);
  if (iVar9 != 0) {
    (*g_pSvcRdroid->pFclose)(iVar7);
    rdColormap_BuildGreyRamp(cmp);
    return 1;
  }
  puVar1 = (ushort *)((int)cmp + 0x30);
  (*g_pSvcRdroid->pFread)(iVar7,puVar1,0x300);
  bVar2 = *(byte *)puVar1;
  bVar3 = *(byte *)((int)cmp + 0x31);
  bVar4 = *(byte *)((int)cmp + 0x32);
  iVar9 = 0xfe;
  do {
    bVar5 = *(byte *)puVar1;
    if (bVar5 == bVar2) {
      if (bVar5 < 0xf7) {
        cVar6 = bVar5 + 8;
      }
      else {
        cVar6 = bVar5 - 8;
      }
      *(char *)puVar1 = cVar6;
    }
    bVar5 = *(byte *)((int)cmp + 0x31);
    if (bVar5 == bVar3) {
      if (bVar5 < 0xf7) {
        cVar6 = bVar5 + 8;
      }
      else {
        cVar6 = bVar5 - 8;
      }
      *(char *)((int)cmp + 0x31) = cVar6;
    }
    bVar5 = *(byte *)((int)cmp + 0x32);
    if (bVar5 == bVar4) {
      if (bVar5 < 0xf7) {
        cVar6 = bVar5 + 8;
      }
      else {
        cVar6 = bVar5 - 8;
      }
      *(char *)((int)cmp + 0x32) = cVar6;
    }
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  if ((*(byte *)((int)cmp + 0x20) & 4) == 0) {
    *(undefined4 *)((int)cmp + 0x348) = 0;
  }
  else {
    puVar10 = (undefined2 *)
              (*g_pSvcRdroid->pAlloc)
                        (0x8000,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,DAT_004ddadc + 0x4b);
    *(undefined2 **)((int)cmp + 0x348) = puVar10;
    if (puVar10 == (undefined2 *)0x0) goto LAB_00404659;
    rdColormap_Build16bitTables(puVar10,puVar1,0,0,0,IMG_ADDR(0x004ddaa0));
  }
  if ((*(byte *)((int)cmp + 0x20) & 1) != 0) {
    uVar11 = (*g_pSvcRdroid->pAlloc)
                       (0x10100,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,DAT_004ddadc + 0x68);
    *(uint *)((int)cmp + 0x33c) = uVar11;
    if (uVar11 == 0) {
LAB_00404659:
      (*g_pSvcRdroid->pFclose)(iVar7);
      rdColormap_BuildGreyRamp(cmp);
      return 1;
    }
    *(uint *)((int)cmp + 0x338) = uVar11;
    if ((uVar11 & 0xff) != 0) {
      *(uint *)((int)cmp + 0x338) = (uVar11 - (uVar11 & 0xff)) + 0x100;
    }
    (*g_pSvcRdroid->pFread)(iVar7,*(undefined4 *)((int)cmp + 0x338),0x10000);
    if ((*(byte *)((int)cmp + 0x20) & 4) == 0) {
      *(undefined4 *)((int)cmp + 0x34c) = 0;
      *(undefined4 *)((int)cmp + 0x340) = 0;
      *(undefined4 *)((int)cmp + 0x344) = 0;
    }
    else {
      iVar9 = (*g_pSvcRdroid->pAlloc)
                        (0x10000,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,DAT_004ddadc + 0x76);
      *(int *)((int)cmp + 0x34c) = iVar9;
      if (iVar9 == 0) goto LAB_00404659;
      if (UINT_004ddaac == 5) {
        (*g_pSvcRdroid->pFseek)(iVar7,0x10000,1);
        (*g_pSvcRdroid->pFread)(iVar7,*(undefined4 *)((int)cmp + 0x34c),0x10000);
        *(undefined4 *)((int)cmp + 0x340) = 0;
        *(undefined4 *)((int)cmp + 0x344) = 0;
      }
      else {
        (*g_pSvcRdroid->pFread)(iVar7,iVar9,0x10000);
        (*g_pSvcRdroid->pFseek)(iVar7,0x10000,1);
        *(undefined4 *)((int)cmp + 0x340) = 0;
        *(undefined4 *)((int)cmp + 0x344) = 0;
      }
    }
  }
  (*g_pSvcRdroid->pFclose)(iVar7);
  return 1;
}
#undef auStack_40
#undef uStack_2c
#undef uStack_30
#undef uStack_34
#undef uStack_38

#endif


/* ---- 0x00404730  rdColormap_Free ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void rdColormap_Free(undefined4 param_1)

{
  rdColormap_FreeEntry(param_1);
  (*g_pSvcRdroid->pFree)(param_1);
  return;
}
#endif


/* ---- 0x00404750  rdColormap_FreeEntry ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void rdColormap_FreeEntry(int param_1)

{
  if (*(int *)(param_1 + 0x334) != 0) {
    (*g_pSvcRdroid->pFree)(*(int *)(param_1 + 0x334));
    *(undefined4 *)(param_1 + 0x334) = 0;
  }
  if (*(int *)(param_1 + 0x348) != 0) {
    (*g_pSvcRdroid->pFree)(*(int *)(param_1 + 0x348));
    *(undefined4 *)(param_1 + 0x348) = 0;
  }
  if ((*(byte *)(param_1 + 0x20) & 1) != 0) {
    if (*(int *)(param_1 + 0x33c) != 0) {
      (*g_pSvcRdroid->pFree)(*(int *)(param_1 + 0x33c));
      *(undefined4 *)(param_1 + 0x33c) = 0;
    }
    if (*(int *)(param_1 + 0x34c) != 0) {
      (*g_pSvcRdroid->pFree)(*(int *)(param_1 + 0x34c));
      *(undefined4 *)(param_1 + 0x34c) = 0;
    }
  }
  return;
}
#endif


/* ---- 0x004047e0  rdColormap_Build16bitTables ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Converts the 256-entry palette into 16-bit pixel values for 64 light levels using the
   pixel-format shifts */

undefined8 __cdecl
rdColormap_Build16bitTables
          (undefined2 *param_1,ushort *param_2,uint param_3,uint param_4,uint param_5,int param_6)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  uint unaff_EBX;
  uint uVar5;
  int iVar6;
  ushort *puVar7;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined2 *puVar8;
  undefined2 *puVar9;
  longlong lVar10;
  longlong lVar11;
  longlong lVar12;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar4 = 0;
  local_10 = 8;
  puVar8 = param_1;
  do {
    uVar2 = *param_2;
    bVar1 = *(byte *)((int)param_2 + 1);
    uVar4 = CONCAT31((int3)(uVar4 >> 8),bVar1);
    iVar6 = 0x40;
    uVar3 = param_2[1];
    param_2 = (ushort *)((int)param_2 + 3);
    puVar9 = puVar8;
    do {
      uVar5 = CONCAT22((short)(unaff_EBX >> 0x10),
                       (ushort)(byte)((byte)uVar2 >> (*(byte *)(param_6 + 0x20) & 0x1f))) <<
              ((byte)*(undefined4 *)(param_6 + 0x14) & 0x1f);
      unaff_EBX = CONCAT22((short)(uVar5 >> 0x10),
                           (ushort)(byte)((byte)uVar3 >> (*(byte *)(param_6 + 0x28) & 0x1f))) <<
                  ((byte)*(undefined4 *)(param_6 + 0x1c) & 0x1f);
      uVar4 = CONCAT22((short)(uVar4 >> 0x10),(ushort)(bVar1 >> (*(byte *)(param_6 + 0x24) & 0x1f)))
              << ((byte)*(undefined4 *)(param_6 + 0x18) & 0x1f) | uVar5 | unaff_EBX;
      iVar6 = iVar6 + -1;
      *puVar9 = (short)uVar4;
      puVar9 = puVar9 + 0x100;
    } while (iVar6 != 0);
    puVar8 = puVar8 + 1;
    local_10 = local_10 - 1;
  } while (local_10 != 0);
  param_2 = param_1 + 0x3f08;
  param_3 = 0xf8;
  do {
    param_1 = (undefined2 *)0x40;
    puVar7 = param_2;
    do {
      lVar10 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      lVar11 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      lVar12 = _ftol((double)CONCAT44(unaff_ESI,unaff_EDI));
      param_1 = (undefined2 *)((int)param_1 + -1);
      *puVar7 = (ushort)(((int)lVar11 >> ((byte)*(undefined4 *)(param_6 + 0x24) & 0x1f)) <<
                        ((byte)*(undefined4 *)(param_6 + 0x18) & 0x1f)) |
                (ushort)(((int)lVar12 >> ((byte)*(undefined4 *)(param_6 + 0x28) & 0x1f)) <<
                        ((byte)*(undefined4 *)(param_6 + 0x1c) & 0x1f)) |
                (ushort)(((int)lVar10 >> ((byte)*(undefined4 *)(param_6 + 0x20) & 0x1f)) <<
                        ((byte)*(undefined4 *)(param_6 + 0x14) & 0x1f));
      puVar7 = puVar7 + -0x100;
    } while (param_1 != (undefined2 *)0x0);
    param_2 = param_2 + 1;
    param_3 = param_3 - 1;
  } while (param_3 != 0);
  return CONCAT44((int)((ulonglong)lVar12 >> 0x20),1);
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x00404a40  rdColormap_BuildGreyRamp ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Fills the colormap with the synthetic GREYRAMP.CMP palette and 64 light levels */

undefined4 rdColormap_BuildGreyRamp(undefined4 *param_1)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  
  *param_1 = 0;
  strncpy(param_1,s_GREYRAMP_CMP_004ddb20,0x1f);
  *(undefined1 *)((int)param_1 + 0x1f) = 0;
  param_1[8] = 0;
  param_1[9] = 0x3f800000;
  param_1[10] = 0x3f800000;
  param_1[0xb] = 0x3f800000;
  uVar3 = (*g_pSvcRdroid->pAlloc)
                    (0x4100,s_C__grimjedi_Libs_RDroid_Engine_R_004ddae4,DAT_004ddae0 + 0x10);
  param_1[0xcd] = uVar3;
  if (uVar3 == 0) {
    return 0;
  }
  param_1[0xcc] = uVar3;
  if ((uVar3 & 0xff) != 0) {
    param_1[0xcc] = (uVar3 - (uVar3 & 0xff)) + 0x100;
  }
  iVar1 = (int)param_1 + 0x31;
  uVar3 = 0;
  do {
    pcVar2 = (char *)(uVar3 + iVar1);
    uVar6 = 0;
    cVar4 = (char)uVar3;
    pcVar2[(int)param_1 + (0x30 - iVar1)] = cVar4;
    *pcVar2 = cVar4;
    pcVar2[(int)param_1 + (0x32 - iVar1)] = cVar4;
    uVar5 = 0;
    do {
      *(char *)(uVar3 + param_1[0xcc] + uVar5) = (char)(uVar6 >> 6) * cVar4;
      uVar5 = uVar5 + 0x100;
      uVar6 = uVar6 + 1;
    } while (uVar5 < 0x4000);
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x100);
  return 1;
}
#endif


/* ---- 0x00404b30  FUN_00404b30 ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
int FUN_00404b30(int param_1)

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
#endif

