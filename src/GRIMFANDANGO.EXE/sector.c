/* GRIMFANDANGO.EXE :: sector.c
 * functions 0x00485dc0 .. 0x004a9d00 (31 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00485dc0  Sector_DrawAllDebug ---- */
/* Outlines every sector of the current set, colour-coded by type bits 0x1000-0x8000 and highlighted
   when an actor stands in it */

void __cdecl Sector_DrawAllDebug(void)

{
  uint uVar1;
  void *this;
  int iVar2;
  uint a1;
  
  this = g_pSectorList;
  do {
    if (this == (void *)0x0) {
      return;
    }
    uVar1 = *(uint *)((int)this + 0x24);
    a1 = DAT_008c97e4 & 0xffff;
    if ((uVar1 & 0x1000) != 0) {
      a1 = (uint)DAT_008c97c6;
    }
    if ((uVar1 & 0x2000) != 0) {
      a1 = DAT_008c97d0 & 0xffff;
    }
    if ((uVar1 & 0x4000) != 0) {
      a1 = (uint)PIECE(DAT_008c97cc,2,2);
    }
    iVar2 = DAT_008d086c;
    if ((uVar1 & 0x8000) != 0) {
      a1 = (uint)PIECE(DAT_008c97c8,2,2);
    }
    for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x58)) {
      if (this == *(void **)(iVar2 + 0x5c)) {
        a1 = DAT_008c97e8 & 0xffff;
        break;
      }
    }
    Sector_DrawOutline(this,a1);
    this = *(void **)((int)this + 0x70);
  } while( true );
}

/* ---- 0x0049c750  Sector_IntersectSegment ---- */
/* Tests a segment against a sector's edges, returning the entry/exit points */

void Sector_IntersectSegment
               (int param_1,int param_2,undefined4 *param_3,undefined4 *param_4,undefined4 *param_5)

{
  bool bVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  bVar1 = false;
  bVar2 = false;
  lua_beginblock();
  uVar3 = lua_getref(g_nLuaSystemTableRef);
  lua_pushobject(uVar3);
  lua_pushstring(s_collisionHandler_004ec3fc);
  iVar4 = lua_gettable();
  iVar5 = lua_istable(iVar4);
  if (iVar5 == 0) {
    iVar5 = lua_isfunction(iVar4);
    if (iVar5 == 0) {
      lua_isnil(iVar4);
      iVar5 = param_1;
    }
    else {
      bVar2 = false;
      bVar1 = true;
      iVar5 = iVar4;
    }
  }
  else {
    lua_pushobject();
    lua_pushstring(s_collisionHandler_004ec3fc);
    iVar5 = lua_gettable();
    iVar6 = lua_isfunction(iVar5);
    if (iVar6 != 0) {
      bVar1 = true;
      bVar2 = true;
    }
  }
  if (bVar1) {
    if (bVar2) {
      lua_pushobject(iVar4);
    }
    lua_pushusertag((param_1 - (int)g_pActorTable) / 0xa8,0x52544341);
    lua_pushusertag((param_2 - (int)g_pActorTable) / 0xa8,0x52544341);
    lua_pushnumber(*param_3);
    lua_pushnumber(param_3[1]);
    lua_pushnumber(param_3[2]);
    lua_pushnumber(*param_4);
    lua_pushnumber(param_4[1]);
    lua_pushnumber(param_4[2]);
    lua_pushnumber(*param_5);
    lua_pushnumber(param_5[1]);
    lua_pushnumber(param_5[2]);
    lua_callfunction(iVar5);
  }
  lua_endblock();
  return;
}

/* ---- 0x004a61c0  SectorList_SaveForShrink ---- */
void SectorList_SaveForShrink(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  void *pvVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  SectorList_FreeShrinkSave();
  DAT_008cf270 = 0;
  DAT_008cf278 = 0;
  for (pvVar4 = g_pSectorList; pvVar4 != (void *)0x0; pvVar4 = *(void **)((int)pvVar4 + 0x70)) {
    DAT_008cf270 = DAT_008cf270 + *(int *)((int)pvVar4 + 0x34);
    DAT_008cf278 = DAT_008cf278 + 1;
  }
  DAT_008cf274 = Plat_Alloc(DAT_008cf270 * 0x14);
  local_4 = 0;
  for (pvVar4 = g_pSectorList; pvVar4 != (void *)0x0; pvVar4 = *(void **)((int)pvVar4 + 0x70)) {
    iVar6 = 0;
    if (0 < *(int *)((int)pvVar4 + 0x34)) {
      iVar8 = local_4 * 0x14;
      piVar5 = (int *)((int)pvVar4 + 0x38);
      do {
        puVar2 = (undefined4 *)*piVar5;
        puVar1 = (undefined4 *)((int)DAT_008cf274 + iVar8 + 4);
        *puVar1 = *puVar2;
        puVar1[1] = puVar2[1];
        puVar1[2] = puVar2[2];
        puVar1[3] = puVar2[3];
        *(int *)((int)DAT_008cf274 + iVar8) = *piVar5 + -0x8cb0b0 >> 4;
        local_4 = local_4 + 1;
        iVar6 = iVar6 + 1;
        iVar8 = iVar8 + 0x14;
        piVar5 = piVar5 + 1;
      } while (iVar6 < *(int *)((int)pvVar4 + 0x34));
    }
  }
  DAT_008cf27c = Plat_Alloc(DAT_008cf278 * 0x34);
  if (g_pSectorList != (void *)0x0) {
    iVar6 = 0;
    pvVar4 = g_pSectorList;
    do {
      iVar8 = 0;
      *(void **)((int)DAT_008cf27c + iVar6) = pvVar4;
      *(undefined4 *)((int)DAT_008cf27c + iVar6 + 4) = *(undefined4 *)((int)pvVar4 + 0x34);
      *(undefined4 *)((int)DAT_008cf27c + iVar6 + 0x30) = *(undefined4 *)((int)pvVar4 + 0x28);
      if (0 < *(int *)((int)pvVar4 + 0x34)) {
        iVar7 = iVar6 + 8;
        piVar5 = (int *)((int)pvVar4 + 0x38);
        do {
          iVar3 = *piVar5;
          piVar5 = piVar5 + 1;
          *(int *)((int)DAT_008cf27c + iVar7) = iVar3 + -0x8cb0b0 >> 4;
          iVar8 = iVar8 + 1;
          iVar7 = iVar7 + 4;
        } while (iVar8 < *(int *)((int)pvVar4 + 0x34));
      }
      pvVar4 = *(void **)((int)pvVar4 + 0x70);
      iVar6 = iVar6 + 0x34;
    } while (pvVar4 != (void *)0x0);
  }
  DAT_008d0868 = 1;
  return;
}
#undef local_4


/* ---- 0x004a6330  SectorList_FreeShrinkSave ---- */
void SectorList_FreeShrinkSave(void)

{
  DAT_008d0868 = 0;
  if (DAT_008cf274 != (void *)0x0) {
    Plat_Free(DAT_008cf274);
  }
  if (DAT_008cf27c != (void *)0x0) {
    Plat_Free(DAT_008cf27c);
  }
  DAT_008cf274 = (void *)0x0;
  DAT_008cf27c = (void *)0x0;
  DAT_008cf278 = 0;
  DAT_008cf270 = 0;
  return;
}

/* ---- 0x004a6380  SectorList_RestoreAfterShrink ---- */
void SectorList_RestoreAfterShrink(void)

{
  int iVar1;
  void *pvVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  
  pvVar2 = g_pSectorList;
  piVar3 = DAT_008cf274;
  iVar7 = DAT_008cf270;
  if (DAT_008d0868 != 0) {
    for (; DAT_008cf270 = iVar7, DAT_008cf274 = piVar3, pvVar2 != (void *)0x0;
        pvVar2 = *(void **)((int)pvVar2 + 0x70)) {
      iVar7 = 0;
      if (0 < *(int *)((int)pvVar2 + 0x34)) {
        puVar6 = (undefined4 *)((int)pvVar2 + 0x38);
        do {
          SectorVertexPool_Release(*puVar6);
          iVar7 = iVar7 + 1;
          puVar6 = puVar6 + 1;
        } while (iVar7 < *(int *)((int)pvVar2 + 0x34));
      }
      piVar3 = DAT_008cf274;
      iVar7 = DAT_008cf270;
    }
    if (0 < iVar7) {
      do {
        iVar8 = *piVar3;
        iVar7 = iVar7 + -1;
        (&DAT_008cb0b0)[iVar8 * 4] = piVar3[1];
        (&DAT_008cb0b4)[iVar8 * 4] = piVar3[2];
        (&DAT_008cb0b8)[iVar8 * 4] = piVar3[3];
        (&DAT_008cb0bc)[iVar8 * 4] = piVar3[4];
        piVar3 = piVar3 + 5;
      } while (iVar7 != 0);
    }
    iVar7 = 0;
    if (0 < DAT_008cf278) {
      iVar8 = 0;
      do {
        iVar1 = *(int *)(DAT_008cf27c + iVar8);
        iVar5 = *(int *)(DAT_008cf27c + 4 + iVar8);
        iVar4 = 0;
        *(int *)(iVar1 + 0x34) = iVar5;
        if (0 < iVar5) {
          iVar5 = iVar8 + 8;
          puVar6 = (undefined4 *)(iVar1 + 0x38);
          do {
            iVar5 = iVar5 + 4;
            iVar4 = iVar4 + 1;
            *puVar6 = &DAT_008cb0b0 + *(int *)(DAT_008cf27c + -4 + iVar5) * 4;
            puVar6 = puVar6 + 1;
          } while (iVar4 < *(int *)(iVar1 + 0x34));
        }
        iVar7 = iVar7 + 1;
        puVar6 = (undefined4 *)(DAT_008cf27c + 0x30 + iVar8);
        iVar8 = iVar8 + 0x34;
        *(undefined4 *)(iVar1 + 0x28) = *puVar6;
      } while (iVar7 < DAT_008cf278);
    }
    DAT_008cf26c = 0;
    piVar3 = &DAT_008cb0b0;
    do {
      if (0 < *piVar3) {
        DAT_008cf26c = DAT_008cf26c + 1;
      }
      piVar3 = piVar3 + 4;
    } while ((int)piVar3 < IMG_ADDR(0x008cf0b0));
  }
  return;
}

/* ---- 0x004a6490  Sector_Construct ---- */
/* Sector_Construct(sector, vertices, count, group name): vertices go through
   SectorVertexPool_GetOrAdd (welded to an earlier vertex closer than 1e-4); Newell normal
   (+0x60..+0x68) normalized with Vec3_Normalize; the two axes (+0x7c, +0x80) are chosen by the
   largest component compared as it is (not abs): x -> (2,1), y -> (0,2), else (1,0). Default height
   +0x30 = 0.005. The sector is pushed on the head of its group's chain (+0x70 next) and
   DAT_008cf280 = newest: searches start with the last sector that was loaded. */

undefined1 * __thiscall Sector_Construct(void *this,int a1,int a2,int a3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *pfVar1;
  float fVar2;
  char cVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  char *pcVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  byte *pbVar14;
  byte *pbVar15;
  char *pcVar16;
  bool bVar17;
  #define local_2 (*(undefined1 (*)[2])(_frame + (0x20 - 0x2)))
  
  if (a3 == 0) {
    a3 = (int)local_2;
  }
  puVar13 = (undefined4 *)((int)this + 0x38);
  *(undefined4 *)((int)this + 0x28) = 1;
  *(undefined4 *)((int)this + 0x2c) = 1;
  *(undefined4 *)((int)this + 0x70) = 0;
  *(undefined4 *)((int)this + 0x6c) = 0;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(int *)((int)this + 0x34) = a2;
  *(undefined1 *)this = 0;
  *(undefined4 *)((int)this + 0x30) = 0x3ba3d70a;
  puVar12 = puVar13;
  for (iVar7 = 10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  if (0 < a2) {
    do {
      uVar5 = SectorVertexPool_GetOrAdd(this,a1);
      *puVar13 = uVar5;
      puVar13 = puVar13 + 1;
      a1 = a1 + 0xc;
      a2 = a2 + -1;
    } while (a2 != 0);
  }
  pfVar1 = (float *)((int)this + 0x60);
  *pfVar1 = 0.0;
  *(undefined4 *)((int)this + 100) = 0;
  *(undefined4 *)((int)this + 0x68) = 0;
  a1 = *(int *)((int)this + 0x34);
  if (0 < a1) {
    a2 = (int)this + 0x38;
    iVar7 = *(int *)((int)this + a1 * 4 + 0x34);
    do {
      iVar6 = *(int *)a2;
      a2 = a2 + 4;
      a1 = a1 + -1;
      *pfVar1 = (*(float *)(iVar7 + 8) - *(float *)(iVar6 + 8)) *
                (*(float *)(iVar7 + 0xc) + *(float *)(iVar6 + 0xc)) + *pfVar1;
      *(float *)((int)this + 100) =
           (*(float *)(iVar7 + 0xc) - *(float *)(iVar6 + 0xc)) *
           (*(float *)(iVar6 + 4) + *(float *)(iVar7 + 4)) + *(float *)((int)this + 100);
      *(float *)((int)this + 0x68) =
           (*(float *)(iVar7 + 8) + *(float *)(iVar6 + 8)) *
           (*(float *)(iVar7 + 4) - *(float *)(iVar6 + 4)) + *(float *)((int)this + 0x68);
      iVar7 = iVar6;
    } while (a1 != 0);
  }
  pfVar1 = (float *)((int)this + 0x60);
  Vec3_Normalize(pfVar1);
  if (*pfVar1 <= *(float *)((int)this + 100)) {
    fVar2 = *(float *)((int)this + 100);
  }
  else {
    fVar2 = *pfVar1;
  }
  if (fVar2 <= *(float *)((int)this + 0x68)) {
    fVar2 = *(float *)((int)this + 0x68);
  }
  else if (*pfVar1 <= *(float *)((int)this + 100)) {
    fVar2 = *(float *)((int)this + 100);
  }
  else {
    fVar2 = *pfVar1;
  }
  if (fVar2 == *pfVar1) {
    *(undefined4 *)((int)this + 0x7c) = 2;
    *(undefined4 *)((int)this + 0x80) = 1;
  }
  else if (fVar2 == *(float *)((int)this + 100)) {
    *(undefined4 *)((int)this + 0x7c) = 0;
    *(undefined4 *)((int)this + 0x80) = 2;
  }
  else {
    *(undefined4 *)((int)this + 0x7c) = 1;
    *(undefined4 *)((int)this + 0x80) = 0;
  }
  iVar7 = 0;
  pbVar14 = &DAT_008cf28c;
  pbVar10 = (byte *)a3;
  pbVar15 = pbVar14;
LAB_004a6636:
  do {
    bVar4 = *pbVar14;
    bVar17 = bVar4 < *pbVar10;
    if (bVar4 == *pbVar10) {
      if (bVar4 != 0) {
        bVar4 = pbVar14[1];
        bVar17 = bVar4 < pbVar10[1];
        if (bVar4 != pbVar10[1]) goto LAB_004a665a;
        pbVar14 = pbVar14 + 2;
        pbVar10 = pbVar10 + 2;
        if (bVar4 != 0) goto LAB_004a6636;
      }
      iVar6 = 0;
    }
    else {
LAB_004a665a:
      iVar6 = (1 - (uint)bVar17) - (uint)(bVar17 != 0);
    }
    if ((iVar6 == 0) || (*pbVar15 == 0)) {
      if ((&DAT_008cf28c)[iVar7 * 0x28] == '\0') {
        uVar8 = 0xffffffff;
        goto code_r0x004a6694;
      }
      break;
    }
    pbVar14 = pbVar15 + 0x28;
    iVar7 = iVar7 + 1;
    pbVar10 = (byte *)a3;
    pbVar15 = pbVar14;
  } while ((int)pbVar14 < IMG_ADDR(0x008d086c));
  goto LAB_004a66ac;
  while( true ) {
    uVar8 = uVar8 - 1;
    pcVar11 = (char *)(a3 + 1);
    cVar3 = *(char *)a3;
    a3 = (int)pcVar11;
    if (cVar3 == '\0') break;
code_r0x004a6694:
    pcVar11 = (char *)a3;
    if (uVar8 == 0) break;
  }
  uVar8 = ~uVar8;
  pcVar11 = pcVar11 + -uVar8;
  pcVar16 = &DAT_008cf28c + iVar7 * 0x28;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar16 = *(undefined4 *)pcVar11;
    pcVar11 = pcVar11 + 4;
    pcVar16 = pcVar16 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar16 = *pcVar11;
    pcVar11 = pcVar11 + 1;
    pcVar16 = pcVar16 + 1;
  }
LAB_004a66ac:
  *(undefined4 *)((int)this + 0x70) = (&DAT_008cf288)[iVar7 * 10];
  if ((&DAT_008cf288)[iVar7 * 10] != 0) {
    *(void **)((&DAT_008cf288)[iVar7 * 10] + 0x6c) = this;
  }
  (&DAT_008cf288)[iVar7 * 10] = this;
  g_pSectorList = this;
  return this;
}
#undef local_2


/* ---- 0x004a66e0  FUN_004a66e0 ---- */
void __fastcall FUN_004a66e0(void *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (param_1 == g_pSectorList) {
    g_pSectorList = *(void **)((int)param_1 + 0x70);
  }
  iVar2 = 0;
  piVar1 = &DAT_008cf288;
  do {
    if ((void *)*piVar1 == param_1) {
      (&DAT_008cf288)[iVar2 * 10] = *(undefined4 *)((int)param_1 + 0x70);
      break;
    }
    piVar1 = piVar1 + 10;
    iVar2 = iVar2 + 1;
  } while ((int)piVar1 < IMG_ADDR(0x008d0868));
  iVar2 = 0;
  if (0 < *(int *)((int)param_1 + 0x34)) {
    puVar3 = (undefined4 *)((int)param_1 + 0x38);
    do {
      SectorVertexPool_Release(*puVar3);
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar2 < *(int *)((int)param_1 + 0x34));
  }
  if (*(int *)((int)param_1 + 0x6c) != 0) {
    *(undefined4 *)(*(int *)((int)param_1 + 0x6c) + 0x70) = *(undefined4 *)((int)param_1 + 0x70);
  }
  if (*(int *)((int)param_1 + 0x70) != 0) {
    *(undefined4 *)(*(int *)((int)param_1 + 0x70) + 0x6c) = *(undefined4 *)((int)param_1 + 0x6c);
  }
  return;
}

/* ---- 0x004a6760  Sector_SetName ---- */
uint __thiscall Sector_SetName(void *this,int a1)

{
  char cVar1;
  uint in_EAX;
  uint uVar2;
  char *pcVar3;
  
  if (a1 != 0) {
    uVar2 = 0xffffffff;
    do {
      pcVar3 = (char *)a1;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar3 = (char *)(a1 + 1);
      cVar1 = *(char *)a1;
      a1 = (int)pcVar3;
    } while (cVar1 != '\0');
    in_EAX = ~uVar2;
    pcVar3 = pcVar3 + -in_EAX;
    for (uVar2 = in_EAX >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined4 *)this = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      this = (char *)((int)this + 4);
    }
    for (uVar2 = in_EAX & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(char *)this = *pcVar3;
      pcVar3 = pcVar3 + 1;
      this = (char *)((int)this + 1);
    }
  }
  return in_EAX;
}

/* ---- 0x004a6790  Sector_SetType ---- */
/* Stores the type bits (+0x24); 0x1000 sets a small shrink tolerance, 0x100 (edge sector) needs 4
   vertices and picks the long axis (+0x78) */

int __thiscall Sector_SetType(void *this,int a1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  undefined2 extraout_var;
  int iVar10;
  float10 fVar11;
  #define local_18 (*(float *)(_frame + (0x30 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x30 - 0x10)))
  #define local_c (*(float *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  *(int *)((int)this + 0x24) = a1;
  *(undefined4 *)((int)this + 0x30) = 0x461c3c00;
  if ((a1 & 0x1000U) != 0) {
    *(undefined4 *)((int)this + 0x30) = 0x3ba3d70a;
  }
  if ((a1 & 0x100U) != 0) {
    if (*(int *)((int)this + 0x34) != 4) {
      *(undefined4 *)((int)this + 0x24) = 0x1000;
      return a1;
    }
    iVar10 = *(int *)((int)this + 0x3c);
    iVar5 = *(int *)((int)this + 0x38);
    iVar6 = *(int *)((int)this + 0x44);
    iVar7 = *(int *)((int)this + 0x40);
    local_c = *(float *)(iVar10 + 4) - *(float *)(iVar5 + 4);
    local_8 = *(float *)(iVar10 + 8) - *(float *)(iVar5 + 8);
    local_4 = *(float *)(iVar10 + 0xc) - *(float *)(iVar5 + 0xc);
    local_18 = *(float *)(iVar6 + 4) - *(float *)(iVar7 + 4);
    local_14 = *(float *)(iVar6 + 8) - *(float *)(iVar7 + 8);
    local_10 = *(float *)(iVar6 + 0xc) - *(float *)(iVar7 + 0xc);
    fVar11 = (float10)((code *)Vec3_Normalize)(&local_c);
    fVar1 = (float)fVar11;
    fVar11 = (float10)((code *)Vec3_Normalize)(&local_18);
    fVar8 = local_10 * local_4 + local_14 * local_8 + local_18 * local_c;
    fVar2 = (float)fVar11;
    if (fVar8 < 0.0) {
      fVar8 = -fVar8;
    }
    iVar10 = *(int *)((int)this + 0x40);
    iVar5 = *(int *)((int)this + 0x3c);
    local_c = *(float *)(iVar10 + 4) - *(float *)(iVar5 + 4);
    iVar6 = *(int *)((int)this + 0x38);
    iVar7 = *(int *)((int)this + 0x44);
    local_8 = *(float *)(iVar10 + 8) - *(float *)(iVar5 + 8);
    local_4 = *(float *)(iVar10 + 0xc) - *(float *)(iVar5 + 0xc);
    local_18 = *(float *)(iVar6 + 4) - *(float *)(iVar7 + 4);
    local_14 = *(float *)(iVar6 + 8) - *(float *)(iVar7 + 8);
    local_10 = *(float *)(iVar6 + 0xc) - *(float *)(iVar7 + 0xc);
    fVar11 = (float10)((code *)Vec3_Normalize)(&local_c);
    fVar3 = (float)fVar11;
    fVar11 = (float10)((code *)Vec3_Normalize)(&local_18);
    fVar9 = local_10 * local_4 + local_14 * local_8 + local_18 * local_c;
    fVar4 = (float)fVar11;
    if (fVar9 < 0.0) {
      fVar9 = -fVar9;
    }
    if (fVar9 < fVar8) {
      iVar10 = CONCAT22(extraout_var,
                        (ushort)(fVar1 < fVar2) << 8 | (ushort)(ISNAN(fVar1) || ISNAN(fVar2)) << 10 |
                        (ushort)(fVar1 == fVar2) << 0xe);
      if (fVar1 < fVar2) {
        *(undefined4 *)((int)this + 0x78) = 0;
        return iVar10;
      }
      *(undefined4 *)((int)this + 0x78) = 2;
      return iVar10;
    }
    a1 = CONCAT22(extraout_var,
                  (ushort)(fVar3 < fVar4) << 8 | (ushort)(ISNAN(fVar3) || ISNAN(fVar4)) << 10 |
                  (ushort)(fVar3 == fVar4) << 0xe);
    if (fVar3 < fVar4) {
      *(undefined4 *)((int)this + 0x78) = 1;
      return a1;
    }
    *(undefined4 *)((int)this + 0x78) = 3;
  }
  return a1;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a6980  Sector_ContainsPoint ---- */
/* __stdcall Sector_ContainsPoint(sector, point, checkActive). With checkActive, an inactive sector (+0x28 or
   +0x2c zero) contains nothing. 1) distance from the plane (normal at +0x60..+0x68, vertex[1]): a
   distance <= 1e-5 counts as 0, then |d| <= height (+0x30; 0.005 for walk sectors, or when the file
   says 0). 2) each edge prev->cur on the two axes +0x7c / +0x80: v =
   (p[a]-prev[a])*(cur[b]-prev[b]) - (p[b]-prev[b])*(cur[a]-prev[a]) + 1e-5, |v| <= 1e-5 -> 0, v < 0
   = outside. So a point up to 2e-5 (cross-product units, i.e. 2e-5 / edge length) outside an edge
   is inside. */

undefined4 Sector_ContainsPoint(int a1,int a2)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int in_ECX;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  
  if (a2 != 0) {
    if (*(int *)(in_ECX + 0x2c) == 0) {
      return 0;
    }
    if (*(int *)(in_ECX + 0x28) == 0) {
      return 0;
    }
  }
  iVar1 = *(int *)(in_ECX + 0x3c);
  fVar2 = (*(float *)(a1 + 4) - *(float *)(iVar1 + 8)) * *(float *)(in_ECX + 100) +
          (*(float *)(a1 + 8) - *(float *)(iVar1 + 0xc)) * *(float *)(in_ECX + 0x68) +
          (*(float *)a1 - *(float *)(iVar1 + 4)) * *(float *)(in_ECX + 0x60);
  fVar3 = fVar2;
  if (fVar2 < 0.0) {
    fVar3 = -fVar2;
  }
  fVar4 = fVar2;
  if (fVar3 <= 1e-05) {
    fVar4 = 0.0;
  }
  if (0.0 <= fVar4) {
    fVar3 = fVar2;
    if (fVar2 < 0.0) {
      fVar3 = -fVar2;
    }
    if (fVar3 <= 1e-05) {
      fVar2 = 0.0;
    }
  }
  else {
    fVar3 = fVar2;
    if (fVar2 < 0.0) {
      fVar3 = -fVar2;
    }
    if (fVar3 <= 1e-05) {
      fVar2 = 0.0;
    }
    fVar2 = -fVar2;
  }
  if (fVar2 <= *(float *)(in_ECX + 0x30)) {
    iVar1 = *(int *)(in_ECX + 0x34);
    iVar8 = 0;
    if (iVar1 < 1) {
      return 1;
    }
    iVar7 = *(int *)(in_ECX + 0x80) * 4;
    iVar9 = *(int *)(in_ECX + 0x7c) * 4;
    piVar10 = (int *)(in_ECX + 0x38);
    iVar5 = *(int *)(in_ECX + 0x34 + iVar1 * 4) + 4;
    while( true ) {
      iVar6 = *piVar10 + 4;
      fVar2 = ((*(float *)(a1 + iVar9) - *(float *)(iVar5 + iVar9)) *
               (*(float *)(iVar6 + iVar7) - *(float *)(iVar5 + iVar7)) +
              (*(float *)(a1 + iVar7) - *(float *)(iVar5 + iVar7)) *
              -(*(float *)(iVar6 + iVar9) - *(float *)(iVar5 + iVar9))) - -1e-05;
      fVar3 = fVar2;
      if (fVar2 < 0.0) {
        fVar3 = -fVar2;
      }
      if (fVar3 <= 1e-05) {
        fVar2 = 0.0;
      }
      if (fVar2 < 0.0) break;
      iVar8 = iVar8 + 1;
      piVar10 = piVar10 + 1;
      iVar5 = iVar6;
      if (iVar1 <= iVar8) {
        return 1;
      }
    }
    return 0;
  }
  return 0;
}

/* ---- 0x004a6b30  Sector_ClampPoint ---- */
int __thiscall Sector_ClampPoint(void *this,int a1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  float *pfVar10;
  #define local_10 (*(int **)(_frame + (0x20 - 0x10)))
  
  Sector_FixPlaneCoordinate(this,a1);
  iVar7 = *(int *)((int)this + 0x34);
  iVar9 = 0;
  if (0 < iVar7) {
    local_10 = (int *)((int)this + 0x38);
    pfVar8 = (float *)(*(int *)((int)this + iVar7 * 4 + 0x34) + 4);
    do {
      iVar7 = *local_10;
      pfVar10 = (float *)(iVar7 + 4);
      fVar2 = *pfVar10 - *pfVar8;
      fVar1 = -(*(float *)(iVar7 + 8) - pfVar8[1]);
      fVar3 = (*(float *)(a1 + 4) - pfVar8[1]) * fVar2 + (*(float *)a1 - *pfVar8) * fVar1;
      if (fVar3 < 0.0) {
        fVar4 = -(fVar1 * fVar1) - fVar2 * fVar2;
        fVar6 = fVar4;
        if (fVar4 < 0.0) {
          fVar6 = -fVar4;
        }
        fVar5 = fVar4;
        if (fVar6 <= 1e-05) {
          fVar5 = 0.0;
        }
        if (fVar5 != 0.0) {
          fVar3 = fVar3 / fVar4;
          fVar4 = fVar3 * fVar1 + *(float *)a1;
          fVar1 = fVar3 * fVar2 + *(float *)(a1 + 4);
          *(float *)a1 = fVar4;
          *(float *)(a1 + 4) = fVar1;
          fVar2 = *pfVar10 - *pfVar8;
          fVar6 = *(float *)(iVar7 + 8) - pfVar8[1];
          fVar3 = fVar2;
          if (fVar2 < 0.0) {
            fVar3 = -fVar2;
          }
          fVar5 = fVar6;
          if (fVar6 < 0.0) {
            fVar5 = -fVar6;
          }
          if (fVar3 <= fVar5) {
            fVar2 = (fVar1 - pfVar8[1]) / fVar6;
          }
          else {
            fVar2 = (fVar4 - *pfVar8) / fVar2;
          }
          if ((iVar9 != *(int *)((int)this + 0x34) + -1) || (fVar2 <= 1.0)) {
            if (0.0 <= fVar2) {
              Sector_FixPlaneCoordinate(this,a1);
            }
            else {
              *(float *)a1 = *pfVar8;
              *(float *)(a1 + 4) = pfVar8[1];
              *(float *)(a1 + 8) = pfVar8[2];
            }
          }
          else {
            *(float *)a1 = *pfVar10;
            *(undefined4 *)(a1 + 4) = *(undefined4 *)(iVar7 + 8);
            *(undefined4 *)(a1 + 8) = *(undefined4 *)(iVar7 + 0xc);
          }
        }
      }
      iVar7 = *(int *)((int)this + 0x34);
      iVar9 = iVar9 + 1;
      local_10 = local_10 + 1;
      pfVar8 = pfVar10;
    } while (iVar9 < iVar7);
  }
  return iVar7;
}
#undef local_10


/* ---- 0x004a6d10  Sector_FindExitPoint ---- */
undefined4 __thiscall Sector_FindExitPoint(void *this,int a1,int a2,int a3)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int iVar9;
  undefined2 extraout_var;
  undefined4 uVar10;
  int iVar11;
  float *pfVar12;
  float *pfVar13;
  int iVar14;
  float10 fVar15;
  float fVar16;
  #define local_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(int **)(_frame + (0x40 - 0x24)))
  #define local_1c (*(float **)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x40 - 0x4)))
  
  local_1c = (float *)0x0;
  *(undefined4 *)((int)this + 0x74) = 0xffffffff;
  iVar9 = Sector_ContainsPoint(a2,1);
  if (iVar9 == 0) {
    local_28 = 0;
    *(undefined4 *)a3 = *(undefined4 *)a2;
    *(undefined4 *)(a3 + 4) = *(undefined4 *)(a2 + 4);
    *(undefined4 *)(a3 + 8) = *(undefined4 *)(a2 + 8);
    if (0 < *(int *)((int)this + 0x34)) {
      local_24 = (int *)((int)this + 0x38);
      pfVar12 = (float *)(*(int *)((int)this + *(int *)((int)this + 0x34) * 4 + 0x34) + 4);
      do {
        iVar9 = *(int *)((int)this + 0x7c);
        iVar1 = *(int *)((int)this + 0x80);
        iVar2 = *local_24;
        pfVar13 = (float *)(iVar2 + 4);
        iVar14 = iVar9 * 4;
        iVar11 = iVar1 * 4;
        local_14 = pfVar13[iVar1] - pfVar12[iVar1];
        local_18 = -(pfVar13[iVar9] - pfVar12[iVar9]);
        fVar16 = (*(float *)(a3 + iVar11) - pfVar12[iVar1]) * local_18 +
                 (*(float *)(a3 + iVar14) - pfVar12[iVar9]) * local_14;
        fVar4 = fVar16;
        if (fVar16 < 0.0) {
          fVar4 = -fVar16;
        }
        fVar5 = fVar16;
        if (fVar4 <= 1e-05) {
          fVar5 = 0.0;
        }
        if (fVar5 < 0.0) {
          fVar4 = *(float *)(a3 + iVar11) - *(float *)(a1 + iVar11);
          fVar8 = *(float *)(a3 + iVar14) - *(float *)(a1 + iVar14);
          fVar7 = -(fVar4 * local_18) - fVar8 * local_14;
          fVar5 = fVar7;
          if (fVar7 < 0.0) {
            fVar5 = -fVar7;
          }
          fVar6 = fVar7;
          if (fVar5 <= 1e-05) {
            fVar6 = 0.0;
          }
          if (fVar6 != 0.0) {
            *(float *)(a3 + iVar11) = fVar4 * (fVar16 / fVar7) + *(float *)(a3 + iVar11);
            *(float *)(a3 + *(int *)((int)this + 0x7c) * 4) =
                 fVar8 * (fVar16 / fVar7) + *(float *)(a3 + *(int *)((int)this + 0x7c) * 4);
            local_c = *pfVar12 - *pfVar13;
            local_8 = pfVar12[1] - *(float *)(iVar2 + 8);
            local_4 = pfVar12[2] - *(float *)(iVar2 + 0xc);
            *(int *)((int)this + 0x74) = local_28;
            local_1c = pfVar12;
          }
        }
        local_28 = local_28 + 1;
        local_24 = local_24 + 1;
        pfVar12 = pfVar13;
      } while (local_28 < *(int *)((int)this + 0x34));
    }
    Sector_FixPlaneCoordinate(this,a3);
    if (local_1c != (float *)0x0) {
      local_18 = *(float *)a1 - *(float *)a2;
      local_14 = *(float *)(a1 + 4) - *(float *)(a2 + 4);
      local_10 = *(float *)(a1 + 8) - *(float *)(a2 + 8);
      Vec3_Normalize(&local_c);
      Vec3_Normalize(&local_18);
      fVar16 = Vec3_Dot2(&local_c,&local_18);
      fVar15 = (float10)Math_AsinDegreesSeries(fVar16);
      fVar3 = (float10)0.0;
      uVar10 = CONCAT22(extraout_var,
                        (ushort)(fVar15 < fVar3) << 8 | (ushort)(ISNAN(fVar15) || ISNAN(fVar3)) << 10 |
                        (ushort)(fVar15 == fVar3) << 0xe);
      if (fVar15 < fVar3 || (fVar15 == fVar3) != 0) {
        return uVar10;
      }
      return uVar10;
    }
    iVar9 = Sector_SnapToPlane(this,a3);
  }
  return iVar9;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_24
#undef local_28
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a6fa0  Sector_SnapToPlane ---- */
/* Lua SnapToPlane: projects the point onto the plane of the sector found by Sector_FindByName */

int __thiscall Sector_SnapToPlane(void *this,int a1)

{
  int iVar1;
  float fVar2;
  
  iVar1 = *(int *)((int)this + 0x38);
  fVar2 = (*(float *)(a1 + 4) - *(float *)(iVar1 + 8)) * *(float *)((int)this + 100) +
          (*(float *)(a1 + 8) - *(float *)(iVar1 + 0xc)) * *(float *)((int)this + 0x68) +
          (*(float *)a1 - *(float *)(iVar1 + 4)) * *(float *)((int)this + 0x60);
  *(float *)a1 = *(float *)a1 - fVar2 * *(float *)((int)this + 0x60);
  *(float *)(a1 + 4) = *(float *)(a1 + 4) - fVar2 * *(float *)((int)this + 100);
  *(float *)(a1 + 8) = *(float *)(a1 + 8) - fVar2 * *(float *)((int)this + 0x68);
  return a1;
}

/* ---- 0x004a7000  Sector_FixPlaneCoordinate ---- */
int __thiscall Sector_FixPlaneCoordinate(void *this,int a1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = *(int *)((int)this + 0x38);
  iVar2 = *(int *)((int)this + 0x7c);
  if ((iVar2 == 1) && (*(int *)((int)this + 0x80) == 0)) {
    iVar4 = 2;
  }
  else if (((iVar2 != 0) || (iVar4 = 1, *(int *)((int)this + 0x80) != 2)) &&
          ((iVar4 = a1, iVar2 == 2 && (*(int *)((int)this + 0x80) == 1)))) {
    iVar4 = 0;
  }
  iVar3 = *(int *)((int)this + 0x80);
  *(float *)(a1 + iVar4 * 4) =
       (*(float *)((int)this + iVar2 * 4 + 0x60) * *(float *)(a1 + iVar2 * 4) +
        *(float *)((int)this + iVar3 * 4 + 0x60) * *(float *)(a1 + iVar3 * 4) +
       -(*(float *)((int)this + 0x68) * *(float *)(iVar1 + 0xc) +
        *(float *)((int)this + 0x60) * *(float *)(iVar1 + 4) +
        *(float *)((int)this + 100) * *(float *)(iVar1 + 8))) /
       -*(float *)((int)this + iVar4 * 4 + 0x60);
  return iVar3;
}

/* ---- 0x004a70a0  Sector_DrawOutline ---- */
int __thiscall Sector_DrawOutline(void *this,int a1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar1 = 0;
  if (*(int *)((int)this + 0x28) != 0) {
    iVar4 = 0;
    iVar1 = *(int *)((int)this + *(int *)((int)this + 0x34) * 4 + 0x34) + 4;
    if (0 < *(int *)((int)this + 0x34)) {
      piVar3 = (int *)((int)this + 0x38);
      iVar2 = iVar1;
      do {
        iVar1 = *piVar3 + 4;
        rdPrimit3_DrawLine(iVar2,iVar1,0,0,0,0,a1,0xffffffff);
        iVar4 = iVar4 + 1;
        piVar3 = piVar3 + 1;
        iVar2 = iVar1;
      } while (iVar4 < *(int *)((int)this + 0x34));
    }
  }
  return iVar1;
}

/* ---- 0x004a7100  FUN_004a7100 ---- */
void FUN_004a7100(char *param_1)

{
  void *p;
  void *pvVar1;
  
  pvVar1 = g_pSectorList;
  SectorList_SelectForSet(param_1);
  p = g_pSectorList;
  if (pvVar1 == g_pSectorList) {
    pvVar1 = (void *)0x0;
  }
  while (p != (void *)0x0) {
    g_pSectorList = p;
    ((code *)FUN_004a66e0)();
    Plat_Free(p);
    p = g_pSectorList;
  }
  g_pSectorList = pvVar1;
  return;
}

/* ---- 0x004a7150  SectorList_SelectForSet ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Points g_pSectorList at the sector list cached for the named set (table of 0x28-byte {list, name}
   entries) */

void __cdecl SectorList_SelectForSet(char *setName)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  bool bVar7;
  
  iVar3 = 0;
  pbVar5 = &DAT_008cf28c;
  pbVar4 = (byte *)setName;
  pbVar6 = pbVar5;
LAB_004a7163:
  do {
    bVar1 = *pbVar5;
    bVar7 = bVar1 < *pbVar4;
    if (bVar1 == *pbVar4) {
      if (bVar1 != 0) {
        bVar1 = pbVar5[1];
        bVar7 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_004a7187;
        pbVar5 = pbVar5 + 2;
        pbVar4 = pbVar4 + 2;
        if (bVar1 != 0) goto LAB_004a7163;
      }
      iVar2 = 0;
    }
    else {
LAB_004a7187:
      iVar2 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
    }
    if (iVar2 == 0) goto LAB_004a719c;
    pbVar5 = pbVar6 + 0x28;
    iVar3 = iVar3 + 1;
    pbVar4 = (byte *)setName;
    pbVar6 = pbVar5;
    if (IMG_ADDR(0x008d086b) < (int)pbVar5) {
LAB_004a719c:
      if (0x8b < iVar3) {
        g_pSectorList = (void *)0x0;
        _DAT_008cf284 = (undefined1 *)0x0;
        return;
      }
      g_pSectorList = (void *)(&DAT_008cf288)[iVar3 * 10];
      _DAT_008cf284 = &DAT_008cf28c + iVar3 * 0x28;
      return;
    }
  } while( true );
}

/* ---- 0x004a71e0  SectorList_FindByPoint ---- */
void * SectorList_FindByPoint(int param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  void *pvVar3;
  
  pvVar3 = g_pSectorList;
  if (g_pSectorList == (void *)0x0) {
    return (void *)0x0;
  }
  while (((*(uint *)((int)pvVar3 + 0x24) & param_2) == 0 ||
         (iVar2 = Sector_ContainsPoint(param_1,1), iVar2 == 0))) {
    piVar1 = (int *)((int)pvVar3 + 0x70);
    pvVar3 = (void *)*piVar1;
    if ((void *)*piVar1 == (void *)0x0) {
      return (void *)0x0;
    }
  }
  return pvVar3;
}

/* ---- 0x004a7230  Sector_FindByName ---- */
void * __cdecl Sector_FindByName(char *name)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  
  pbVar2 = g_pSectorList;
  do {
    pbVar3 = pbVar2;
    pbVar5 = (byte *)name;
    if (pbVar2 == (byte *)0x0) {
      return (void *)0x0;
    }
    do {
      bVar1 = *pbVar3;
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_004a726e:
        iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_004a7273;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_004a726e;
      pbVar3 = pbVar3 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_004a7273:
    if (iVar4 == 0) {
      return pbVar2;
    }
    pbVar2 = *(byte **)(pbVar2 + 0x70);
  } while( true );
}

/* ---- 0x004a7290  Sector_FindById ---- */
void * __cdecl Sector_FindById(int id)

{
  void *pvVar1;
  
  for (pvVar1 = g_pSectorList; (pvVar1 != (void *)0x0 && (*(int *)((int)pvVar1 + 0x20) != id));
      pvVar1 = *(void **)((int)pvVar1 + 0x70)) {
  }
  return pvVar1;
}

/* ---- 0x004a72b0  SectorList_FindNearestPoint ---- */
/* SectorList_FindNearestPoint(point, mask): the sector with the mask that contains the point
   (SectorList_FindByPoint), else the active sector whose Sector_ClampPoint of the point is nearest.
   Used by Lua GetShrinkPos, which then clamps the point in it (so (x, y) stay and only the height
   is made right when the point is inside). */

void * SectorList_FindNearestPoint(float *param_1,uint param_2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  void *this;
  void *pvVar2;
  void *pvVar3;
  #define local_10 (*(float *)(_frame + (0x20 - 0x10)))
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  local_10 = 3.4028235e+38;
  pvVar3 = (void *)SectorList_FindByPoint(param_1,param_2);
  pvVar2 = (void *)0x0;
  this = g_pSectorList;
  if (pvVar3 == (void *)0x0) {
    for (; pvVar3 = pvVar2, this != (void *)0x0; this = *(void **)((int)this + 0x70)) {
      if ((((*(uint *)((int)this + 0x24) & param_2) != 0) && (*(int *)((int)this + 0x2c) != 0)) &&
         (*(int *)((int)this + 0x28) != 0)) {
        local_c = *param_1;
        local_8 = param_1[1];
        local_4 = param_1[2];
        Sector_ClampPoint(this,(int)&local_c);
        fVar1 = (local_c - *param_1) * (local_c - *param_1) +
                (local_4 - param_1[2]) * (local_4 - param_1[2]) +
                (local_8 - param_1[1]) * (local_8 - param_1[1]);
        if (fVar1 < local_10) {
          pvVar3 = this;
          local_10 = fVar1;
        }
      }
      pvVar2 = pvVar3;
    }
  }
  return pvVar3;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a7390  Sector_MoveWalkerToOppositeEdge ---- */
undefined4 __thiscall Sector_MoveWalkerToOppositeEdge(void *this,int a1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 in_EAX;
  uint uVar6;
  int iVar7;
  #define local_24 (*(float *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(float *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(float *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x40 - 0x4)))
  
  if (*(int *)((int)this + 0x34) == 4) {
    local_18 = *(float *)a1;
    local_14 = *(float *)(a1 + 4);
    local_10 = *(float *)(a1 + 8);
    local_24 = *(float *)(a1 + 0x18) * -10.0 + local_18;
    local_20 = *(float *)(a1 + 0x1c) * -10.0 + local_14;
    local_1c = *(float *)(a1 + 0x20) * -10.0 + local_10;
    in_EAX = Sector_FindExitPoint(this,(int)&local_18,(int)&local_24,(int)&local_c);
    iVar1 = *(int *)((int)this + 0x74);
    if (iVar1 != -1) {
      iVar7 = *(int *)((int)this + iVar1 * 4 + 0x38);
      uVar6 = iVar1 - 1;
      if (0x7fffffff < uVar6) {
        uVar6 = *(int *)((int)this + 0x34) - 1;
      }
      iVar2 = *(int *)((int)this + uVar6 * 4 + 0x38);
      fVar3 = *(float *)(iVar2 + 4) - *(float *)(iVar7 + 4);
      fVar5 = fVar3;
      if (fVar3 < 0.0) {
        fVar5 = -fVar3;
      }
      fVar4 = fVar3;
      if (fVar5 <= 1e-05) {
        fVar4 = 0.0;
      }
      if (fVar4 == 0.0) {
        fVar3 = (local_8 - *(float *)(iVar7 + 8)) / (*(float *)(iVar2 + 8) - *(float *)(iVar7 + 8));
      }
      else {
        fVar3 = (local_c - *(float *)(iVar7 + 4)) / fVar3;
      }
      fVar3 = 1.0 - fVar3;
      iVar7 = (iVar1 + 2) % *(int *)((int)this + 0x34);
      *(int *)((int)this + 0x74) = iVar7;
      iVar1 = *(int *)((int)this + iVar7 * 4 + 0x38);
      uVar6 = iVar7 - 1;
      if (0x7fffffff < uVar6) {
        uVar6 = *(int *)((int)this + 0x34) - 1;
      }
      iVar7 = *(int *)((int)this + uVar6 * 4 + 0x38);
      local_c = (*(float *)(iVar7 + 4) - *(float *)(iVar1 + 4)) * fVar3 + *(float *)(iVar1 + 4);
      local_8 = (*(float *)(iVar7 + 8) - *(float *)(iVar1 + 8)) * fVar3 + *(float *)(iVar1 + 8);
      local_4 = (*(float *)(iVar7 + 0xc) - *(float *)(iVar1 + 0xc)) * fVar3 +
                *(float *)(iVar1 + 0xc);
      in_EAX = Walker_SetPosition((void *)a1,(int)&local_c);
    }
  }
  return in_EAX;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a7520  Sector_EdgeFollowDirection ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* For a 4-vertex edge sector: direction along the edge the walker should follow (g_vEdgeFollowDir),
   stepping the current edge index when the walker reaches a corner */

undefined4 __thiscall Sector_EdgeFollowDirection(void *this,int a1)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  float10 fVar12;
  float fVar13;
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_30 (*(float *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(float *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(float *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(float *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(float *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(float *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x50 - 0x10)))
  #define local_8 (*(float *)(_frame + (0x50 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x50 - 0x4)))
  
  local_18 = *(float *)a1;
  local_14 = *(float *)(a1 + 4);
  local_10 = *(float *)(a1 + 8);
  if (*(float *)(a1 + 0x40) <= 0.0) {
    fVar13 = 100.0;
  }
  else {
    fVar13 = -100.0;
  }
  if (*(float *)(a1 + 0x40) <= 0.0) {
    fVar4 = 100.0;
  }
  else {
    fVar4 = -100.0;
  }
  if (*(float *)(a1 + 0x40) <= 0.0) {
    fVar5 = 100.0;
  }
  else {
    fVar5 = -100.0;
  }
  local_30 = *(float *)(a1 + 0x18) * fVar13 + local_18;
  local_2c = *(float *)(a1 + 0x1c) * fVar4 + local_14;
  local_28 = *(float *)(a1 + 0x20) * fVar5 + local_10;
  Sector_FindExitPoint(this,(int)&local_18,(int)&local_30,IMG_ADDR(0x008cf260));
  iVar1 = *(int *)((int)this + 0x74);
  if (iVar1 != -1) {
    iVar2 = *(int *)((int)this + iVar1 * 4 + 0x38);
    fVar5 = *(float *)(iVar2 + 4) - FLOAT_008cf260;
    fVar13 = *(float *)(iVar2 + 8) - _DAT_008cf264;
    fVar4 = *(float *)(iVar2 + 0xc) - _DAT_008cf268;
    if (0.0025 <= fVar4 * fVar4 + fVar13 * fVar13 + fVar5 * fVar5) {
      uVar10 = iVar1 - 1;
      uVar9 = uVar10;
      uVar8 = uVar10;
      uVar11 = uVar10;
      uVar6 = uVar10;
      uVar7 = uVar10;
      local_38 = uVar10;
      if ((int)uVar10 < 0) {
        uVar9 = *(int *)((int)this + 0x34) - 1;
        uVar8 = *(int *)((int)this + 0x34) - 1;
        uVar11 = *(int *)((int)this + 0x34) - 1;
        uVar6 = *(int *)((int)this + 0x34) - 1;
        uVar7 = *(int *)((int)this + 0x34) - 1;
        local_38 = *(int *)((int)this + 0x34) - 1;
      }
      if ((*(float *)(*(int *)((int)this + local_38 * 4 + 0x38) + 0xc) - _DAT_008cf268) *
          (*(float *)(*(int *)((int)this + uVar9 * 4 + 0x38) + 0xc) - _DAT_008cf268) +
          (*(float *)(*(int *)((int)this + uVar11 * 4 + 0x38) + 8) - _DAT_008cf264) *
          (*(float *)(*(int *)((int)this + uVar8 * 4 + 0x38) + 8) - _DAT_008cf264) +
          (*(float *)(*(int *)((int)this + uVar7 * 4 + 0x38) + 4) - FLOAT_008cf260) *
          (*(float *)(*(int *)((int)this + uVar6 * 4 + 0x38) + 4) - FLOAT_008cf260) < 0.0025) {
        uVar8 = uVar10;
        if ((int)uVar10 < 0) {
          uVar8 = *(int *)((int)this + 0x34) - 1;
        }
        local_24 = *(float *)(*(int *)((int)this + uVar8 * 4 + 0x38) + 4) - *(float *)(iVar2 + 4);
        uVar8 = uVar10;
        if ((int)uVar10 < 0) {
          uVar8 = *(int *)((int)this + 0x34) - 1;
        }
        local_20 = *(float *)(*(int *)((int)this + uVar8 * 4 + 0x38) + 8) -
                   *(float *)(*(int *)((int)this + *(int *)((int)this + 0x74) * 4 + 0x38) + 8);
        if (0x7fffffff < uVar10) {
          uVar10 = *(int *)((int)this + 0x34) - 1;
        }
        local_1c = *(float *)(*(int *)((int)this + uVar10 * 4 + 0x38) + 0xc) -
                   *(float *)(*(int *)((int)this + *(int *)((int)this + 0x74) * 4 + 0x38) + 0xc);
        Vec3_Normalize(&local_24);
        fVar13 = Vec3_Dot2(&local_24,(float *)(a1 + 0x18));
        fVar12 = (float10)Math_AsinDegreesSeries(fVar13);
        if (((float10)90.0 - fVar12 < (float10)1.0) || ((float10)179.0 < (float10)90.0 - fVar12)) {
          uVar8 = *(int *)((int)this + 0x74) - 1;
          if (0x7fffffff < uVar8) {
            uVar8 = *(int *)((int)this + 0x34) - 1;
          }
          *(uint *)((int)this + 0x74) = uVar8;
        }
      }
    }
    else {
      uVar8 = iVar1 - 1;
      uVar11 = uVar8;
      if ((int)uVar8 < 0) {
        uVar11 = *(int *)((int)this + 0x34) - 1;
      }
      local_24 = *(float *)(*(int *)((int)this + uVar11 * 4 + 0x38) + 4) - *(float *)(iVar2 + 4);
      uVar11 = uVar8;
      if ((int)uVar8 < 0) {
        uVar11 = *(int *)((int)this + 0x34) - 1;
      }
      local_20 = *(float *)(*(int *)((int)this + uVar11 * 4 + 0x38) + 8) -
                 *(float *)(*(int *)((int)this + iVar1 * 4 + 0x38) + 8);
      if (0x7fffffff < uVar8) {
        uVar8 = *(int *)((int)this + 0x34) - 1;
      }
      local_1c = *(float *)(*(int *)((int)this + uVar8 * 4 + 0x38) + 0xc) -
                 *(float *)(*(int *)((int)this + iVar1 * 4 + 0x38) + 0xc);
      Vec3_Normalize(&local_24);
      fVar13 = Vec3_Dot2(&local_24,(float *)(a1 + 0x18));
      fVar12 = (float10)Math_AsinDegreesSeries(fVar13);
      if ((float10)90.0 - fVar12 < (float10)1.0) {
        *(int *)((int)this + 0x74) = (*(int *)((int)this + 0x74) + 1) % *(int *)((int)this + 0x34);
      }
      else if ((float10)179.0 < (float10)90.0 - fVar12) {
        *(int *)((int)this + 0x74) = (*(int *)((int)this + 0x74) + 1) % *(int *)((int)this + 0x34);
      }
    }
    iVar1 = *(int *)((int)this + 0x74);
    iVar2 = *(int *)((int)this + iVar1 * 4 + 0x38);
    uVar8 = iVar1 - 1;
    if (0x7fffffff < uVar8) {
      uVar8 = *(int *)((int)this + 0x34) - 1;
    }
    iVar3 = *(int *)((int)this + uVar8 * 4 + 0x38);
    fVar13 = *(float *)(iVar3 + 4) - *(float *)(iVar2 + 4);
    fVar4 = fVar13;
    if (fVar13 < 0.0) {
      fVar4 = -fVar13;
    }
    fVar5 = fVar13;
    if (fVar4 <= 1e-05) {
      fVar5 = 0.0;
    }
    if (fVar5 == 0.0) {
      fVar13 = (_DAT_008cf264 - *(float *)(iVar2 + 8)) /
               (*(float *)(iVar3 + 8) - *(float *)(iVar2 + 8));
    }
    else {
      fVar13 = (FLOAT_008cf260 - *(float *)(iVar2 + 4)) / fVar13;
    }
    if (fVar13 < 0.15) {
      fVar13 = 0.15;
    }
    if (0.85 < fVar13) {
      fVar13 = 0.85;
    }
    iVar2 = *(int *)((int)this + 0x34);
    iVar3 = *(int *)((int)this + ((iVar1 + 1) % iVar2) * 4 + 0x38);
    iVar1 = *(int *)((int)this + ((iVar2 + -2 + iVar1) % iVar2) * 4 + 0x38);
    local_8 = (*(float *)(iVar1 + 8) - *(float *)(iVar3 + 8)) * fVar13 + *(float *)(iVar3 + 8);
    local_4 = (*(float *)(iVar1 + 0xc) - *(float *)(iVar3 + 0xc)) * fVar13 + *(float *)(iVar3 + 0xc)
    ;
    FLOAT_008cf260 =
         ((*(float *)(iVar1 + 4) - *(float *)(iVar3 + 4)) * fVar13 + *(float *)(iVar3 + 4)) -
         FLOAT_008cf260;
    _DAT_008cf264 = local_8 - _DAT_008cf264;
    _DAT_008cf268 = local_4 - _DAT_008cf268;
    Vec3_Normalize(&FLOAT_008cf260);
    if (*(float *)(a1 + 0x40) < 0.0) {
      FLOAT_008cf260 = FLOAT_008cf260 * -1.0;
      _DAT_008cf264 = _DAT_008cf264 * -1.0;
      _DAT_008cf268 = _DAT_008cf268 * -1.0;
    }
    return &FLOAT_008cf260;
  }
  return 0;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_38
#undef local_4
#undef local_8


/* ---- 0x004a7a90  SectorList_ResetFree ---- */
void SectorList_ResetFree(void)

{
  void *pvVar1;
  
  for (pvVar1 = g_pSectorList; pvVar1 != (void *)0x0; pvVar1 = *(void **)((int)pvVar1 + 0x70)) {
    *(undefined4 *)((int)pvVar1 + 0x2c) = 1;
  }
  return;
}

/* ---- 0x004a7ab0  SectorVertexPool_GetOrAdd ---- */
/* Source: Engine/WalkPlane.cpp (line 974, from __FILE__/__LINE__ passed to the allocator) */

int * SectorVertexPool_GetOrAdd(undefined4 param_1,float *param_2)

{
  int *piVar1;
  float *pfVar2;
  int iVar3;
  int *piVar4;
  
  piVar4 = (int *)0x0;
  if (0x3fd < DAT_008cf26c) {
    (*g_pSvcMain->pAssertFail)
              (s_tot_verts___MAX_DB_VERTS___2_004ec8a8,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,
               0x3ce);
  }
  iVar3 = 0;
  pfVar2 = (float *)&DAT_008cb0b4;
  do {
    if ((pfVar2[-1] != 0.0) &&
       ((param_2[2] - pfVar2[2]) * (param_2[2] - pfVar2[2]) +
        (param_2[1] - pfVar2[1]) * (param_2[1] - pfVar2[1]) +
        (*param_2 - *pfVar2) * (*param_2 - *pfVar2) < 1e-08)) {
      piVar4 = &DAT_008cb0b0 + iVar3 * 4;
      *piVar4 = *piVar4 + 1;
      return piVar4;
    }
    pfVar2 = pfVar2 + 4;
    iVar3 = iVar3 + 1;
  } while ((int)pfVar2 < IMG_ADDR(0x008cf0b4));
  iVar3 = 0;
  piVar1 = &DAT_008cb0b0;
  do {
    if (*piVar1 < 1) {
      piVar4 = &DAT_008cb0b0 + iVar3 * 4;
      break;
    }
    piVar1 = piVar1 + 4;
    iVar3 = iVar3 + 1;
  } while ((int)piVar1 < IMG_ADDR(0x008cf0b0));
  *piVar4 = 1;
  DAT_008cf26c = DAT_008cf26c + 1;
  piVar4[1] = (int)*param_2;
  piVar4[2] = (int)param_2[1];
  piVar4[3] = (int)param_2[2];
  return piVar4;
}

/* ---- 0x004a7ba0  SectorVertexPool_Release ---- */
void SectorVertexPool_Release(int *param_1)

{
  int iVar1;
  
  if ((0 < *param_1) && (iVar1 = *param_1 + -1, *param_1 = iVar1, iVar1 == 0)) {
    DAT_008cf26c = DAT_008cf26c + -1;
  }
  return;
}

/* ---- 0x004a7bc0  SetFile_ParseSectors ---- */
/* WARNING: Removing unreachable block (ram,0x004a7d43) */
/* WARNING: Removing unreachable block (ram,0x004a7d4b) */
/* WARNING: Removing unreachable block (ram,0x004a7d53) */
/* WARNING: Removing unreachable block (ram,0x004a7d6c) */
/* WARNING: Removing unreachable block (ram,0x004a7d64) */
/* WARNING: Removing unreachable block (ram,0x004a7d70) */
/* Source: Engine/WalkPlane.cpp (lines 1070-1184, from __FILE__/__LINE__ passed to the allocator) */

undefined * SetFile_ParseSectors(int param_1)

{
  unsigned char _frame[0x210] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  undefined1 *puVar6;
  byte *pbVar7;
  undefined *puVar8;
  uint uVar9;
  uint uVar10;
  char *pcVar11;
  byte *pbVar12;
  char *pcVar13;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  bool bVar14;
  #define local_200 (*(int *)(_frame + (0x210 - 0x200)))
  #define local_1fc (*(int *)(_frame + (0x210 - 0x1fc)))
  #define local_1f8 (*(int *)(_frame + (0x210 - 0x1f8)))
  #define local_1f0 (*(uint *)(_frame + (0x210 - 0x1f0)))
  #define local_1ec (*(int *)(_frame + (0x210 - 0x1ec)))
  #define local_1e8 (*(int *)(_frame + (0x210 - 0x1e8)))
  #define local_1e4 (*(byte (*)[48])(_frame + (0x210 - 0x1e4)))
  #define local_1b4 (*(byte (*)[48])(_frame + (0x210 - 0x1b4)))
  #define local_184 (*(undefined1 (*)[120])(_frame + (0x210 - 0x184)))
  #define local_10c (*(char (*)[256])(_frame + (0x210 - 0x10c)))
  #define local_c (*(undefined4 *)(_frame + (0x210 - 0xc)))
  #define pcStack_8 (*(code **)(_frame + (0x210 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x210 - 0x4)))
  
  local_4 = 0xffffffff;
  pcStack_8 = FUN_004d60ba;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_1fc = 0;
  local_1ec = 0;
  local_200 = 0;
  local_1f0 = 0;
  local_1f8 = 0;
  local_1b4[0] = 0;
  DAT_008cf218 = 0;
  iVar4 = Std_ParseCommandLine();
  iVar3 = local_1ec;
  do {
    if (iVar4 == 0) {
      if (2 < local_1fc) {
        pvVar5 = Plat_Alloc(0x84);
        local_4 = 2;
        if (pvVar5 == (void *)0x0) {
          puVar6 = (undefined1 *)0x0;
        }
        else {
          puVar6 = Sector_Construct(pvVar5,(int)local_184,local_1fc,param_1);
        }
        local_4 = 0xffffffff;
        if (puVar6 != (undefined1 *)0x0) {
          Mem_CheckAlloc(puVar6,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,0x4a0);
          Sector_SetName(puVar6,(int)local_1b4);
          *(int *)(puVar6 + 0x20) = iVar3;
          *(uint *)(puVar6 + 0x28) = local_1f0;
          Sector_SetType(puVar6,local_200);
        }
      }
      puVar8 = (undefined *)0x0;
LAB_004a8147:
      *unaff_FS_OFFSET = local_c;
      return puVar8;
    }
    uVar9 = 0xffffffff;
    pcVar11 = DAT_00900520;
    do {
      pcVar13 = pcVar11;
      if (uVar9 == 0) break;
      uVar9 = uVar9 - 1;
      pcVar13 = pcVar11 + 1;
      cVar1 = *pcVar11;
      pcVar11 = pcVar13;
    } while (cVar1 != '\0');
    uVar9 = ~uVar9;
    pcVar11 = pcVar13 + -uVar9;
    pcVar13 = local_10c;
    for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
      pcVar11 = pcVar11 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      *pcVar13 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      pcVar13 = pcVar13 + 1;
    }
    iVar4 = sscanf(local_10c,s_section___s_004ddd64);
    if (iVar4 == 1) {
      if (2 < local_1fc) {
        pvVar5 = Plat_Alloc(0x84);
        local_4 = 0;
        if (pvVar5 == (void *)0x0) {
          puVar6 = (undefined1 *)0x0;
        }
        else {
          puVar6 = Sector_Construct(pvVar5,(int)local_184,local_1fc,param_1);
        }
        local_4 = 0xffffffff;
        if (puVar6 != (undefined1 *)0x0) {
          Mem_CheckAlloc(puVar6,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,0x42e);
          Sector_SetName(puVar6,(int)local_1b4);
          *(int *)(puVar6 + 0x20) = iVar3;
          *(uint *)(puVar6 + 0x28) = local_1f0;
          Sector_SetType(puVar6,local_200);
        }
      }
      puVar8 = &DAT_008cf218;
      goto LAB_004a8147;
    }
    iVar4 = String_ContainsSubstring(local_10c,s_numsectors_004ec9a8);
    local_1ec = iVar3;
    if (iVar4 == 0) {
      iVar4 = sscanf(local_10c,s_sector__s_004ec99c);
      if (iVar4 == 1) {
        if (2 < local_1fc) {
          pvVar5 = Plat_Alloc(0x84);
          local_4 = 1;
          if (pvVar5 == (void *)0x0) {
            puVar6 = (undefined1 *)0x0;
          }
          else {
            puVar6 = Sector_Construct(pvVar5,(int)local_184,local_1fc,param_1);
          }
          local_4 = 0xffffffff;
          if (puVar6 != (undefined1 *)0x0) {
            Mem_CheckAlloc(puVar6,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,0x445);
            Sector_SetName(puVar6,(int)local_1b4);
            *(uint *)(puVar6 + 0x28) = local_1f0;
            *(int *)(puVar6 + 0x20) = iVar3;
            Sector_SetType(puVar6,local_200);
          }
        }
        uVar9 = 0xffffffff;
        pbVar7 = local_1e4;
        do {
          pbVar12 = pbVar7;
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          pbVar12 = pbVar7 + 1;
          bVar2 = *pbVar7;
          pbVar7 = pbVar12;
        } while (bVar2 != 0);
        uVar9 = ~uVar9;
        local_1b4[0] = 0;
        pbVar7 = pbVar12 + -uVar9;
        pbVar12 = local_1b4;
        for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pbVar12 = *(undefined4 *)pbVar7;
          pbVar7 = pbVar7 + 4;
          pbVar12 = pbVar12 + 4;
        }
        local_1ec = 0;
        local_200 = 0;
        local_1f0 = 0;
        local_1fc = 0;
        local_1f8 = 0;
        for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *pbVar12 = *pbVar7;
          pbVar7 = pbVar7 + 1;
          pbVar12 = pbVar12 + 1;
        }
      }
      else {
        iVar4 = sscanf(local_10c,s_id__i_004ec994);
        local_1ec = local_1e8;
        if (iVar4 != 1) {
          iVar4 = sscanf(local_10c,s_type__s_004ec7b8);
          if (iVar4 == 1) {
            pbVar12 = &DAT_004ec98c;
            pbVar7 = local_1e4;
            do {
              bVar2 = *pbVar7;
              bVar14 = bVar2 < *pbVar12;
              if (bVar2 != *pbVar12) {
LAB_004a7e39:
                iVar4 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                goto LAB_004a7e3e;
              }
              if (bVar2 == 0) break;
              bVar2 = pbVar7[1];
              bVar14 = bVar2 < pbVar12[1];
              if (bVar2 != pbVar12[1]) goto LAB_004a7e39;
              pbVar7 = pbVar7 + 2;
              pbVar12 = pbVar12 + 2;
            } while (bVar2 != 0);
            iVar4 = 0;
LAB_004a7e3e:
            if (iVar4 == 0) {
              local_200 = 0x1000;
              local_1ec = iVar3;
            }
            else {
              pbVar12 = &DAT_004ec984;
              pbVar7 = local_1e4;
              do {
                bVar2 = *pbVar7;
                bVar14 = bVar2 < *pbVar12;
                if (bVar2 != *pbVar12) {
LAB_004a7e7c:
                  iVar4 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                  goto LAB_004a7e81;
                }
                if (bVar2 == 0) break;
                bVar2 = pbVar7[1];
                bVar14 = bVar2 < pbVar12[1];
                if (bVar2 != pbVar12[1]) goto LAB_004a7e7c;
                pbVar7 = pbVar7 + 2;
                pbVar12 = pbVar12 + 2;
              } while (bVar2 != 0);
              iVar4 = 0;
LAB_004a7e81:
              if (iVar4 == 0) {
                local_200 = 0x1100;
                local_1ec = iVar3;
              }
              else {
                pbVar12 = &DAT_004ec97c;
                pbVar7 = local_1e4;
                do {
                  bVar2 = *pbVar7;
                  bVar14 = bVar2 < *pbVar12;
                  if (bVar2 != *pbVar12) {
LAB_004a7ebf:
                    iVar4 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                    goto LAB_004a7ec4;
                  }
                  if (bVar2 == 0) break;
                  bVar2 = pbVar7[1];
                  bVar14 = bVar2 < pbVar12[1];
                  if (bVar2 != pbVar12[1]) goto LAB_004a7ebf;
                  pbVar7 = pbVar7 + 2;
                  pbVar12 = pbVar12 + 2;
                } while (bVar2 != 0);
                iVar4 = 0;
LAB_004a7ec4:
                if (iVar4 == 0) {
                  local_200 = 0x2000;
                  local_1ec = iVar3;
                }
                else {
                  pbVar12 = &DAT_004ec974;
                  pbVar7 = local_1e4;
                  do {
                    bVar2 = *pbVar7;
                    bVar14 = bVar2 < *pbVar12;
                    if (bVar2 != *pbVar12) {
LAB_004a7f02:
                      iVar4 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                      goto LAB_004a7f07;
                    }
                    if (bVar2 == 0) break;
                    bVar2 = pbVar7[1];
                    bVar14 = bVar2 < pbVar12[1];
                    if (bVar2 != pbVar12[1]) goto LAB_004a7f02;
                    pbVar7 = pbVar7 + 2;
                    pbVar12 = pbVar12 + 2;
                  } while (bVar2 != 0);
                  iVar4 = 0;
LAB_004a7f07:
                  if (iVar4 == 0) {
                    local_200 = 0x4000;
                    local_1ec = iVar3;
                  }
                  else {
                    pbVar12 = &DAT_004ec968;
                    pbVar7 = local_1e4;
                    do {
                      bVar2 = *pbVar7;
                      bVar14 = bVar2 < *pbVar12;
                      if (bVar2 != *pbVar12) {
LAB_004a7f45:
                        iVar4 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                        goto LAB_004a7f4a;
                      }
                      if (bVar2 == 0) break;
                      bVar2 = pbVar7[1];
                      bVar14 = bVar2 < pbVar12[1];
                      if (bVar2 != pbVar12[1]) goto LAB_004a7f45;
                      pbVar7 = pbVar7 + 2;
                      pbVar12 = pbVar12 + 2;
                    } while (bVar2 != 0);
                    iVar4 = 0;
LAB_004a7f4a:
                    local_1ec = iVar3;
                    if (iVar4 == 0) {
                      local_200 = 0x8000;
                    }
                  }
                }
              }
            }
          }
          else {
            iVar4 = sscanf(local_10c,s_default_visibility__s_004ec950);
            if (iVar4 == 1) {
              pbVar12 = &DAT_004ec944;
              pbVar7 = local_1e4;
              do {
                bVar2 = *pbVar7;
                bVar14 = bVar2 < *pbVar12;
                if (bVar2 != *pbVar12) {
LAB_004a7fb9:
                  local_1f0 = (uint)(1 - bVar14 != (uint)(bVar14 != 0));
                  local_1ec = iVar3;
                  goto LAB_004a80a5;
                }
                if (bVar2 == 0) break;
                bVar2 = pbVar7[1];
                bVar14 = bVar2 < pbVar12[1];
                if (bVar2 != pbVar12[1]) goto LAB_004a7fb9;
                pbVar7 = pbVar7 + 2;
                pbVar12 = pbVar12 + 2;
              } while (bVar2 != 0);
              local_1f0 = 0;
              local_1ec = iVar3;
            }
            else {
              iVar4 = sscanf(local_10c,s_height__f_004ec938);
              local_1ec = iVar3;
              if (iVar4 != 1) {
                iVar4 = sscanf(local_10c,s_numvertices__d_004ec928);
                if (iVar4 == 1) {
                  local_1fc = local_1e8;
                }
                else {
                  iVar4 = sscanf(local_10c,s_numgates__s_004ec918);
                  if ((iVar4 != 1) &&
                     ((iVar4 = sscanf(local_10c,s_vertices___f__f__f_004ec904), iVar4 == 3 ||
                      ((local_1f8 < local_1fc &&
                       (iVar4 = sscanf(local_10c,s__f__f__f_004ec8f8), iVar4 == 3)))))) {
                    local_1f8 = local_1f8 + 1;
                  }
                }
              }
            }
          }
        }
      }
    }
LAB_004a80a5:
    iVar4 = Std_ParseCommandLine();
    iVar3 = local_1ec;
  } while( true );
}
#undef local_10c
#undef local_184
#undef local_1b4
#undef local_1e4
#undef local_1e8
#undef local_1ec
#undef local_1f0
#undef local_1f8
#undef local_1fc
#undef local_200
#undef local_4
#undef local_c
#undef pcStack_8


/* ---- 0x004a8cb0  Sector_ClipPolygon ---- */
/* Sutherland-Hodgman clip of a polygon against the sector's edges in its projection plane; returns
   the vertex count */

int __thiscall Sector_ClipPolygon(void *this,int a1,int a2,int a3)

{
  unsigned char _frame[0x160] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  undefined4 *puVar12;
  int iVar13;
  undefined4 *puVar14;
  int iVar15;
  undefined4 *puVar16;
  int iVar17;
  #define local_150 (*(int *)(_frame + (0x160 - 0x150)))
  #define local_14c (*(undefined4 **)(_frame + (0x160 - 0x14c)))
  #define local_148 (*(undefined4 **)(_frame + (0x160 - 0x148)))
  #define local_144 (*(int *)(_frame + (0x160 - 0x144)))
  #define local_140 (*(undefined4 **)(_frame + (0x160 - 0x140)))
  #define local_138 (*(float *)(_frame + (0x160 - 0x138)))
  #define local_12c (*(int **)(_frame + (0x160 - 0x12c)))
  #define local_128 (*(int *)(_frame + (0x160 - 0x128)))
  #define local_120 (*(undefined4 (*)[36])(_frame + (0x160 - 0x120)))
  #define local_90 (*(undefined4 (*)[36])(_frame + (0x160 - 0x90)))
  
  if (0 < a2) {
    puVar16 = local_120;
    for (uVar10 = a2 * 3 & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
      *puVar16 = *(undefined4 *)a1;
      a1 = (int)(a1 + 4);
      puVar16 = puVar16 + 1;
    }
  }
  local_128 = 0;
  local_140 = local_120;
  if (0 < *(int *)((int)this + 0x34)) {
    local_12c = (int *)((int)this + 0x38);
    puVar16 = local_90;
    iVar17 = *(int *)((int)this + *(int *)((int)this + 0x34) * 4 + 0x34) + 4;
    do {
      puVar14 = puVar16;
      iVar11 = *(int *)((int)this + 0x80) * 4;
      iVar15 = *local_12c + 4;
      iVar9 = *(int *)((int)this + 0x7c) * 4;
      local_150 = 0;
      fVar3 = -(*(float *)(iVar15 + iVar9) - *(float *)(iVar17 + iVar9));
      fVar4 = *(float *)(iVar15 + iVar11) - *(float *)(iVar17 + iVar11);
      local_148 = local_140 + a2 * 3 + -3;
      if (0 < a2) {
        iVar13 = 0;
        puVar16 = local_140;
        local_14c = puVar14;
        local_144 = a2;
        local_138 = ((float)local_148[*(int *)((int)this + 0x7c)] - *(float *)(iVar17 + iVar9)) *
                    fVar4 + ((float)local_148[*(int *)((int)this + 0x80)] -
                            *(float *)(iVar17 + iVar11)) * fVar3;
        do {
          puVar12 = puVar16;
          iVar9 = *(int *)((int)this + 0x80);
          iVar11 = *(int *)((int)this + 0x7c);
          fVar5 = ((float)puVar12[iVar9] - *(float *)(iVar17 + iVar9 * 4)) * fVar3 +
                  ((float)puVar12[iVar11] - *(float *)(iVar17 + iVar11 * 4)) * fVar4;
          if ((local_138 <= 0.0) || (fVar5 <= 0.0)) {
            if ((local_138 <= 0.0) || (0.0 <= fVar5)) {
              if ((local_138 < 0.0) && (0.0 < fVar5)) {
                fVar1 = (float)puVar12[iVar11];
                fVar2 = (float)local_148[iVar11];
                fVar6 = -(((float)puVar12[iVar9] - (float)local_148[iVar9]) * fVar3) -
                        (fVar1 - fVar2) * fVar4;
                fVar8 = fVar6;
                if (fVar6 < 0.0) {
                  fVar8 = -fVar6;
                }
                fVar7 = fVar6;
                if (fVar8 <= 1e-05) {
                  fVar7 = 0.0;
                }
                if (fVar7 != 0.0) {
                  local_150 = local_150 + 1;
                  puVar14[*(int *)((int)this + 0x80) + iVar13] =
                       ((float)puVar12[iVar9] - (float)local_148[iVar9]) * (fVar5 / fVar6) +
                       (float)puVar12[iVar9];
                  iVar9 = *(int *)((int)this + 0x7c) + iVar13;
                  iVar13 = iVar13 + 3;
                  local_14c = local_14c + 3;
                  puVar14[iVar9] =
                       (fVar1 - fVar2) * (fVar5 / fVar6) +
                       (float)puVar12[*(int *)((int)this + 0x7c)];
                }
                goto LAB_004a903f;
              }
            }
            else {
              fVar1 = (float)puVar12[iVar11];
              fVar2 = (float)local_148[iVar11];
              fVar6 = -(((float)puVar12[iVar9] - (float)local_148[iVar9]) * fVar3) -
                      (fVar1 - fVar2) * fVar4;
              fVar8 = fVar6;
              if (fVar6 < 0.0) {
                fVar8 = -fVar6;
              }
              fVar7 = fVar6;
              if (fVar8 <= 1e-05) {
                fVar7 = 0.0;
              }
              if (fVar7 != 0.0) {
                local_150 = local_150 + 1;
                puVar14[*(int *)((int)this + 0x80) + iVar13] =
                     ((float)puVar12[iVar9] - (float)local_148[iVar9]) * (fVar5 / fVar6) +
                     (float)puVar12[iVar9];
                iVar9 = *(int *)((int)this + 0x7c) + iVar13;
                iVar13 = iVar13 + 3;
                local_14c = local_14c + 3;
                puVar14[iVar9] =
                     (fVar1 - fVar2) * (fVar5 / fVar6) + (float)puVar12[*(int *)((int)this + 0x7c)];
              }
            }
          }
          else {
LAB_004a903f:
            iVar13 = iVar13 + 3;
            *local_14c = *puVar12;
            local_14c[1] = puVar12[1];
            local_150 = local_150 + 1;
            local_14c[2] = puVar12[2];
            local_14c = local_14c + 3;
          }
          local_144 = local_144 + -1;
          puVar16 = puVar12 + 3;
          local_148 = puVar12;
          local_138 = fVar5;
        } while (local_144 != 0);
      }
      if (local_150 < 2) {
        return 0;
      }
      local_128 = local_128 + 1;
      local_12c = local_12c + 1;
      a2 = local_150;
      puVar16 = local_140;
      iVar17 = iVar15;
      local_140 = puVar14;
    } while (local_128 < *(int *)((int)this + 0x34));
  }
  if (0 < a2) {
    iVar17 = (int)local_140 - a3;
    do {
      puVar16 = (undefined4 *)(iVar17 + a3);
      *(undefined4 *)a3 = *puVar16;
      *(undefined4 *)(a3 + 4) = puVar16[1];
      *(undefined4 *)(a3 + 8) = puVar16[2];
      Sector_FixPlaneCoordinate(this,a3);
      a3 = a3 + 0xc;
      a2 = a2 + -1;
    } while (a2 != 0);
  }
  return local_150;
}
#undef local_120
#undef local_128
#undef local_12c
#undef local_138
#undef local_140
#undef local_144
#undef local_148
#undef local_14c
#undef local_150
#undef local_90


/* ---- 0x004a9070  Sector_EdgeDistance ---- */
/* Source: Engine/WalkPlane.cpp (line 1736, from __FILE__/__LINE__ passed to the allocator) */

undefined4 __thiscall Sector_EdgeDistance(void *this,int a1,int a2)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  float10 fVar4;
  #define auStack_38 (*(undefined1 (*)[4])(_frame + (0x50 - 0x38)))
  #define auStack_34 (*(undefined1 (*)[4])(_frame + (0x50 - 0x34)))
  #define local_30 (*(float *)(_frame + (0x50 - 0x30)))
  #define fStack_2c (*(float *)(_frame + (0x50 - 0x2c)))
  #define fStack_28 (*(float *)(_frame + (0x50 - 0x28)))
  #define fStack_24 (*(float *)(_frame + (0x50 - 0x24)))
  #define fStack_20 (*(float *)(_frame + (0x50 - 0x20)))
  #define fStack_1c (*(float *)(_frame + (0x50 - 0x1c)))
  #define fStack_18 (*(float *)(_frame + (0x50 - 0x18)))
  #define fStack_14 (*(float *)(_frame + (0x50 - 0x14)))
  #define fStack_10 (*(float *)(_frame + (0x50 - 0x10)))
  #define local_c (*(float *)(_frame + (0x50 - 0xc)))
  #define fStack_8 (*(float *)(_frame + (0x50 - 0x8)))
  #define fStack_4 (*(float *)(_frame + (0x50 - 0x4)))
  
  if (*(int *)((int)this + 0x34) <= a1) {
    (*g_pSvcMain->pAssertFail)
              (s_edge_index___num_verts_004ec9b8,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,0x6c8);
  }
  iVar1 = *(int *)((int)this + a1 * 4 + 0x38);
  iVar2 = *(int *)((int)this + ((a1 + 1) % *(int *)((int)this + 0x34)) * 4 + 0x38);
  local_30 = *(float *)(iVar2 + 4) - *(float *)(iVar1 + 4);
  fStack_2c = *(float *)(iVar2 + 8) - *(float *)(iVar1 + 8);
  fStack_28 = *(float *)(iVar2 + 0xc) - *(float *)(iVar1 + 0xc);
  fStack_24 = *(float *)a2 - *(float *)(iVar1 + 4);
  fStack_20 = *(float *)(a2 + 4) - *(float *)(iVar1 + 8);
  fStack_1c = *(float *)(a2 + 8) - *(float *)(iVar1 + 0xc);
  Vec3_NormalizeTo(&local_c,&local_30);
  Vec3_NormalizeTo(&fStack_18,&fStack_24);
  fVar4 = (float10)Math_AsinDegreesSeries
                             (fStack_10 * fStack_4 + fStack_14 * fStack_8 + fStack_18 * local_c);
  uVar3 = ((int (*)(float, float *, float *))Math_SinCosTable)((float)((float10)90.0 - fVar4),auStack_38,auStack_34);
  return uVar3;
}
#undef auStack_34
#undef auStack_38
#undef fStack_10
#undef fStack_14
#undef fStack_18
#undef fStack_1c
#undef fStack_20
#undef fStack_24
#undef fStack_28
#undef fStack_2c
#undef fStack_4
#undef fStack_8
#undef local_30
#undef local_c


/* ---- 0x004a9180  Sector_CollapseShortestEdge ---- */
/* Sector_CollapseShortestEdge: for a sector of 4 or more vertices, finds the shortest edge a -
   (a+1) and replaces its two ends by the point where the line of the edge before it (a-1 -> a)
   meets the line of the edge after it ((a+1) -> (a+2)), computed on the two dominant axes (+0x7c,
   +0x80) with Sector_FixPlaneCoordinate for the third; fails (0) when those lines are parallel
   (|cross| <= 1e-5). The new vertex goes through SectorVertexPool_GetOrAdd. */

undefined4 __fastcall Sector_CollapseShortestEdge(void *param_1)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  int iVar12;
  undefined4 *puVar13;
  int iVar14;
  int iVar15;
  int *piVar16;
  int iVar17;
  #define local_50 (*(float *)(_frame + (0x60 - 0x50)))
  #define local_4c (*(int *)(_frame + (0x60 - 0x4c)))
  #define local_40 (*(float (*)[4])(_frame + (0x60 - 0x40)))
  #define local_30 (*(float *)(_frame + (0x60 - 0x30)))
  #define local_28 (*(undefined4 (*)[10])(_frame + (0x60 - 0x28)))
  
  local_50 = 3.4028235e+38;
  iVar12 = *(int *)((int)param_1 + 0x34);
  if (3 < iVar12) {
    iVar14 = 0;
    if (0 < iVar12) {
      piVar16 = (int *)((int)param_1 + 0x38);
      pfVar8 = (float *)(*(int *)((int)param_1 + iVar12 * 4 + 0x34) + 4);
      do {
        iVar9 = *piVar16;
        fVar4 = pfVar8[1] - *(float *)(iVar9 + 8);
        fVar2 = pfVar8[2] - *(float *)(iVar9 + 0xc);
        fVar3 = *pfVar8 - *(float *)(iVar9 + 4);
        fVar2 = fVar3 * fVar3 + fVar2 * fVar2 + fVar4 * fVar4;
        if (fVar2 < local_50) {
          local_4c = (iVar12 + -1 + iVar14) % iVar12;
          local_50 = fVar2;
        }
        iVar14 = iVar14 + 1;
        piVar16 = piVar16 + 1;
        pfVar8 = (float *)(iVar9 + 4);
      } while (iVar14 < iVar12);
    }
    iVar17 = *(int *)((int)param_1 + local_4c * 4 + 0x38) + 4;
    iVar15 = *(int *)((int)param_1 + ((iVar12 + -1 + local_4c) % iVar12) * 4 + 0x38) + 4;
    iVar9 = *(int *)((int)param_1 + ((local_4c + 1) % iVar12) * 4 + 0x38) + 4;
    iVar14 = local_4c + 2;
    iVar12 = *(int *)((int)param_1 + (iVar14 % iVar12) * 4 + 0x38);
    local_40[0] = *(float *)(iVar12 + 4);
    local_40[1] = (float)*(undefined4 *)(iVar12 + 8);
    iVar10 = *(int *)((int)param_1 + 0x7c) * 4;
    local_40[2] = (float)*(undefined4 *)(iVar12 + 0xc);
    iVar12 = *(int *)((int)param_1 + 0x80) * 4;
    local_40[3] = -(*(float *)(iVar17 + iVar10) - *(float *)(iVar15 + iVar10));
    local_30 = *(float *)(iVar17 + iVar12) - *(float *)(iVar15 + iVar12);
    pfVar8 = local_40 + *(int *)((int)param_1 + 0x7c);
    pfVar1 = local_40 + *(int *)((int)param_1 + 0x80);
    fVar2 = (*pfVar1 - *(float *)(iVar15 + iVar12)) * local_40[3] +
            (*pfVar8 - *(float *)(iVar15 + iVar10)) * local_30;
    fVar3 = fVar2;
    if (fVar2 < 0.0) {
      fVar3 = -fVar2;
    }
    fVar4 = fVar2;
    if (fVar3 <= 1e-05) {
      fVar4 = 0.0;
    }
    if (fVar4 != 0.0) {
      fVar3 = *pfVar1 - *(float *)(iVar9 + iVar12);
      fVar7 = *pfVar8 - *(float *)(iVar9 + iVar10);
      fVar4 = -(fVar3 * local_40[3]) - fVar7 * local_30;
      fVar6 = fVar4;
      if (fVar4 < 0.0) {
        fVar6 = -fVar4;
      }
      fVar5 = fVar4;
      if (fVar6 <= 1e-05) {
        fVar5 = 0.0;
      }
      if (fVar5 != 0.0) {
        *pfVar1 = fVar3 * (fVar2 / fVar4) + *pfVar1;
        *pfVar8 = fVar7 * (fVar2 / fVar4) + *pfVar8;
        Sector_FixPlaneCoordinate(param_1,(int)local_40);
        local_28[0] = SectorVertexPool_GetOrAdd(0,local_40);
        iVar9 = *(int *)((int)param_1 + 0x34);
        iVar12 = iVar9 + -2;
        if (0 < iVar12) {
          puVar13 = local_28;
          do {
            puVar13 = puVar13 + 1;
            iVar10 = iVar14 % iVar9;
            iVar14 = iVar14 + 1;
            iVar12 = iVar12 + -1;
            *puVar13 = *(undefined4 *)((int)param_1 + iVar10 * 4 + 0x38);
          } while (iVar12 != 0);
        }
        SectorVertexPool_Release(*(undefined4 *)((int)param_1 + local_4c * 4 + 0x38));
        SectorVertexPool_Release
                  (*(undefined4 *)
                    ((int)param_1 + ((local_4c + 1) % *(int *)((int)param_1 + 0x34)) * 4 + 0x38));
        iVar14 = *(int *)((int)param_1 + 0x34) + -1;
        iVar12 = 0;
        *(int *)((int)param_1 + 0x34) = iVar14;
        if (0 < iVar14) {
          puVar11 = local_28;
          puVar13 = (undefined4 *)((int)param_1 + 0x38);
          do {
            iVar12 = iVar12 + 1;
            *puVar13 = *puVar11;
            puVar11 = puVar11 + 1;
            puVar13 = puVar13 + 1;
          } while (iVar12 < *(int *)((int)param_1 + 0x34));
        }
        return 1;
      }
      return 0;
    }
  }
  return 0;
}
#undef local_28
#undef local_30
#undef local_40
#undef local_4c
#undef local_50


/* ---- 0x004a9d00  SectorList_ShrinkWalkSectors ---- */
/* SectorList_ShrinkWalkSectors(radius), called by Lua ShrinkBoxes after SectorList_SaveForShrink.
   For every active walk sector (type & 0x1000, flag +0x28): for each vertex take the bisector of
   the directions to its neighbours, move it inward by radius / sin(half angle) (Math_SinCosTable,
   Math_AsinDegreesSeries); the move is valid when the new point is inside the sector
   (Sector_ContainsPoint) and at least radius - 0.001 from the line of every edge
   (Sector_EdgeDistance). Not valid: Sector_CollapseShortestEdge and retry; cannot collapse: the
   sector is switched off (+0x28 = 0). The shifts are summed per pool vertex (shared by the sectors)
   and the pool vertex moves by the mean, so all sectors that share it move together. Undone by
   SectorList_RestoreAfterShrink. */

void SectorList_ShrinkWalkSectors(float param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  bool bVar13;
  float *pfVar14;
  int iVar15;
  float *pfVar16;
  int iVar17;
  int iVar18;
  int *piVar19;
  void *this;
  float *pfVar20;
  undefined4 *puVar21;
  float10 extraout_ST0;
  int iStack00000010;
  float in_stack_00000024;
  float in_stack_00000028;
  float in_stack_0000002c;
  float in_stack_00000030;
  double in_stack_00000038;
  
  FUN_004addf0();
  if (0.0 <= param_1) {
    puVar21 = (undefined4 *)&STACK0X(0x000010b8);
    for (iVar17 = 0xc00; iVar17 != 0; iVar17 = iVar17 + -1) {
      *puVar21 = 0;
      puVar21 = puVar21 + 1;
    }
    puVar21 = (undefined4 *)&STACK0X(0x000000b8);
    for (iVar17 = 0x400; iVar17 != 0; iVar17 = iVar17 + -1) {
      *puVar21 = 0;
      puVar21 = puVar21 + 1;
    }
    this = g_pSectorList;
    if (g_pSectorList != (void *)0x0) {
LAB_004a9d53:
      if (((*(uint *)((int)this + 0x24) & 0x1000) != 0) && (*(int *)((int)this + 0x28) != 0)) {
LAB_004a9d6a:
        iVar17 = *(int *)((int)this + 0x38);
        puVar21 = (undefined4 *)&STACK0X(0x00000040);
        for (iVar18 = 0x1e; iVar18 != 0; iVar18 = iVar18 + -1) {
          *puVar21 = 0;
          puVar21 = puVar21 + 1;
        }
        pfVar14 = (float *)&STACK0X(0x00000044);
        iVar18 = 0;
        pfVar16 = (float *)(*(int *)((int)this + *(int *)((int)this + 0x34) * 4 + 0x34) + 4);
        pfVar20 = (float *)(iVar17 + 4);
        do {
          if (*(int *)((int)this + 0x34) <= iVar18) {
            iVar17 = *(int *)((int)this + 0x34);
            if (0 < iVar17) {
              piVar19 = (int *)((int)this + 0x38);
              pfVar14 = (float *)&STACK0X(0x00000044);
              do {
                iVar18 = *piVar19;
                piVar19 = piVar19 + 1;
                iVar18 = iVar18 + -0x8cb0b0 >> 4;
                iVar15 = iVar18 * 0xc;
                *(float *)(&STACK0X(0x000010b8) + iVar15) =
                     pfVar14[-1] + *(float *)(&STACK0X(0x000010b8) + iVar15);
                *(float *)(&STACK0X(0x000010bc) + iVar15) =
                     *(float *)(&STACK0X(0x000010bc) + iVar15) + *pfVar14;
                *(float *)(&STACK0X(0x000010c0) + iVar15) =
                     pfVar14[1] + *(float *)(&STACK0X(0x000010c0) + iVar15);
                iVar17 = iVar17 + -1;
                *(int *)(&STACK0X(0x000000b8) + iVar18 * 4) =
                     *(int *)(&STACK0X(0x000000b8) + iVar18 * 4) + 1;
                pfVar14 = pfVar14 + 3;
              } while (iVar17 != 0);
            }
            break;
          }
          iVar18 = iVar18 + 1;
          fVar1 = *pfVar16;
          fVar2 = *pfVar20;
          iVar17 = *(int *)((int)this + (iVar18 % *(int *)((int)this + 0x34)) * 4 + 0x38);
          fVar3 = pfVar16[1];
          fVar4 = pfVar20[1];
          fVar5 = pfVar16[2];
          fVar6 = pfVar20[2];
          ((code *)Vec3_Normalize)();
          fVar7 = *(float *)(iVar17 + 4);
          fVar8 = *pfVar20;
          fVar9 = *(float *)(iVar17 + 8);
          fVar10 = pfVar20[1];
          fVar11 = *(float *)(iVar17 + 0xc);
          fVar12 = pfVar20[2];
          ((code *)Vec3_Normalize)();
          fVar1 = (fVar7 - fVar8) + (fVar1 - fVar2);
          fVar2 = (fVar9 - fVar10) + (fVar3 - fVar4);
          fVar3 = (fVar11 - fVar12) + (fVar5 - fVar6);
          ((code *)Vec3_Normalize)();
          ((code *)Math_AsinDegreesSeries)();
          ((code *)Math_SinCosTable)();
          fVar4 = fVar3 / in_stack_00000024;
          bVar13 = true;
          in_stack_00000028 = fVar4 * fVar1 + *pfVar20;
          in_stack_0000002c = fVar4 * fVar2 + pfVar20[1];
          in_stack_00000030 = fVar4 * fVar3 + pfVar20[2];
          iVar15 = Sector_ContainsPoint((int)&STACK0X(0x00000028),1);
          if (iVar15 == 0) {
LAB_004a9f32:
            bVar13 = false;
          }
          else {
            iStack00000010 = 0;
            if (0 < *(int *)((int)this + 0x34)) {
              in_stack_00000038 = (double)(fVar3 - 0.001);
              do {
                Sector_EdgeDistance(this,iStack00000010,(int)&STACK0X(0x00000028));
                if (extraout_ST0 < (float10)in_stack_00000038) goto LAB_004a9f32;
                iStack00000010 = iStack00000010 + 1;
              } while (iStack00000010 < *(int *)((int)this + 0x34));
            }
          }
          if (!bVar13) goto LAB_004a9f7e;
          pfVar14[-1] = fVar4 * fVar1;
          *pfVar14 = fVar4 * fVar2;
          pfVar14[1] = fVar4 * fVar3;
          pfVar14 = pfVar14 + 3;
          pfVar16 = pfVar20;
          pfVar20 = (float *)(iVar17 + 4);
        } while( true );
      }
      goto LAB_004a9ffa;
    }
LAB_004aa005:
    piVar19 = (int *)&STACK0X(0x000000b8);
    pfVar16 = (float *)&DAT_008cb0b8;
    pfVar14 = (float *)&STACK0X(0x000010bc);
    do {
      if (*piVar19 != 0) {
        fVar3 = 1.0 / (float)*piVar19;
        fVar1 = *pfVar14;
        fVar2 = pfVar14[1];
        pfVar16[-1] = pfVar14[-1] * fVar3 + pfVar16[-1];
        *pfVar16 = fVar1 * fVar3 + *pfVar16;
        pfVar16[1] = fVar2 * fVar3 + pfVar16[1];
      }
      pfVar16 = pfVar16 + 4;
      piVar19 = piVar19 + 1;
      pfVar14 = pfVar14 + 3;
    } while ((int)pfVar16 < IMG_ADDR(0x008cf0b8));
  }
  return;
LAB_004a9f7e:
  iVar17 = ((code *)Sector_CollapseShortestEdge)();
  if (iVar17 == 0) goto code_r0x004a9f8d;
  goto LAB_004a9d6a;
code_r0x004a9f8d:
  *(undefined4 *)((int)this + 0x28) = 0;
LAB_004a9ffa:
  this = *(void **)((int)this + 0x70);
  if (this == (void *)0x0) goto LAB_004aa005;
  goto LAB_004a9d53;
}
