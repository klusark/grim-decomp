/* GRIMFANDANGO.EXE :: sector.c
 * functions 0x00485dc0 .. 0x004a9d00 (33 functions)
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
  uint uVar2;
  uint color;
  
  this = g_pWalkPlane_wp_head;
  do {
    if (this == (void *)0x0) {
      return;
    }
    uVar1 = *(uint *)((int)this + 0x24);
    color = UINT_008c97e4 & 0xffff;
    if ((uVar1 & 0x1000) != 0) {
      color = (uint)DAT_008c97c6;
    }
    if ((uVar1 & 0x2000) != 0) {
      color = UINT_008c97d0 & 0xffff;
    }
    if ((uVar1 & 0x4000) != 0) {
      color = (uint)PIECE(UINT_008c97cc,2,2);
    }
    uVar2 = UINT_008d086c;
    if ((uVar1 & 0x8000) != 0) {
      color = (uint)PIECE(UINT_008c97c8,2,2);
    }
    for (; uVar2 != 0; uVar2 = *(uint *)(uVar2 + 0x58)) {
      if (this == *(void **)(uVar2 + 0x5c)) {
        color = UINT_008c97e8 & 0xffff;
        break;
      }
    }
    Sector_DrawOutline(this,color);
    this = *(void **)((int)this + 0x70);
  } while( true );
}

/* ---- 0x0049c750  sputLua_CollisionHandler ---- */
/* Tests a segment against a sector's edges, returning the entry/exit points Original name
   sputLua_CollisionHandler (the remaster's GrimFandango (Linux): strings: 'collisionHandler'); was
   Sector_IntersectSegment. */

void sputLua_CollisionHandler(int param_1,int param_2,float *param_3,float *param_4,float *param_5)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  bVar1 = false;
  bVar2 = false;
  lua_beginblock();
  iVar3 = lua_getref(g_nLrSystemTable);
  lua_pushobject(iVar3);
  lua_pushstring(s_collisionHandler_004ec3fc);
  iVar3 = lua_gettable();
  iVar4 = lua_istable(iVar3);
  if (iVar4 == 0) {
    iVar4 = lua_isfunction(iVar3);
    if (iVar4 == 0) {
      lua_isnil(iVar3);
      iVar4 = param_1;
    }
    else {
      bVar2 = false;
      bVar1 = true;
      iVar4 = iVar3;
    }
  }
  else {
    lua_pushobject(iVar3);
    lua_pushstring(s_collisionHandler_004ec3fc);
    iVar4 = lua_gettable();
    iVar5 = lua_isfunction(iVar4);
    if (iVar5 != 0) {
      bVar1 = true;
      bVar2 = true;
    }
  }
  if (bVar1) {
    if (bVar2) {
      lua_pushobject(iVar3);
    }
    lua_pushusertag((char *)((param_1 - (int)g_pActors) / 0xa8),0x52544341);
    lua_pushusertag((char *)((param_2 - (int)g_pActors) / 0xa8),0x52544341);
    lua_pushnumber(*param_3);
    lua_pushnumber(param_3[1]);
    lua_pushnumber(param_3[2]);
    lua_pushnumber(*param_4);
    lua_pushnumber(param_4[1]);
    lua_pushnumber(param_4[2]);
    lua_pushnumber(*param_5);
    lua_pushnumber(param_5[1]);
    lua_pushnumber(param_5[2]);
    lua_callfunction(iVar4);
  }
  lua_endblock();
  return;
}
#undef local_4


/* ---- 0x004a4b00  SetFile_Parse ---- */
/* Remembers the set being parsed (g_dwLoadingRoom), stores its base file name (+0, 0x7f chars) and
   parses the sections with SetFile_ParseSections. Earlier taken for sputRoom_LoadRoom (the
   remaster's GrimFandango (Linux): the only unmatched caller of SetFile_ParseSections; 1 matched
   neighbours agree, 0 disagree); was SetFile_Parse. Named SetFile_Parse (not in the remaster: gcc
   inlined it into sputRoom_LoadRoom; the earlier hand-made name, back from the orig-names guess
   sputRoom_LoadRoom, which is 0x4a49a0); was sputRoom_LoadRoom. */

int SetFile_Parse(char *param_1,uint param_2)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0x7f;
  g_dwLoadingRoom = param_2;
  pcVar1 = stdFnames_FindMedName(param_1);
  strncpy(param_2,pcVar1,uVar3);
  *(undefined1 *)(param_2 + 0x7f) = 0;
  iVar2 = sputRoom_LoadRoomEntry(param_1);
  return iVar2 != 0;
}

/* ---- 0x004a5550  sputRoom_LoadRoomEntry ---- */
/* Opens the .set file with stdConffile and calls Set_IsHandleValid (the registered section handler
   dispatcher) for every 'section: <name>' line; returns 0 if a handler rejects its section.
   Original name sputRoom_LoadRoomEntry (the remaster's GrimFandango (Linux): aligned call in
   sputRoom_LoadRoom); was SetFile_ParseSections. */

undefined4 sputRoom_LoadRoomEntry(undefined4 param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define local_20 (*(undefined1 (*)[32])(_frame + (0x30 - 0x20)))
  
  iVar1 = ((code *)stdConffile_Open)(param_1);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = stdConffile_ReadLine();
  if (iVar1 != 0) {
    do {
      iVar1 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ec740,local_20);
      if (iVar1 == 1) {
        iVar1 = Set_IsHandleValid(local_20);
        if (iVar1 == 0) {
          stdConffile_Close();
          return 0;
        }
      }
      iVar1 = stdConffile_ReadLine();
    } while (iVar1 != 0);
    stdConffile_Close();
    return 1;
  }
  stdConffile_Close();
  return 1;
}
#undef local_20


/* ---- 0x004a5b40  sputRoom_ParseColormaps ---- */
/* Section handler 'colormaps' registered by sputRoom_Start: reads 'numcolormaps' and the colormap
   names (0x34-byte entries at set+0x80). Original name sputRoom_ParseColormaps (the remaster's
   GrimFandango (Linux): strings: ' colormap %s' | ' numcolormaps %d\n'); was
   SetFile_ParseColormaps. */

undefined4 sputRoom_ParseColormaps(void)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  #define local_100 (*(undefined1 (*)[256])(_frame + (0x110 - 0x100)))
  
  uVar3 = g_dwLoadingRoom;
  piVar1 = (int *)(g_dwLoadingRoom + 0x80);
  if (*piVar1 != 0) {
    (*g_pSputRoomHS->pAssertFail)
              (s_pRoom__apColormaps____NULL_004ec88c,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,
               0x91d);
  }
  iVar4 = stdConffile_ReadLine();
  if (iVar4 == 0) {
    return 1;
  }
  do {
    if (*(char *)g_dwStdConffile_aLine != '\0') {
      local_100[0] = 0;
      iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ec7e0,local_100);
      if (iVar4 == 0) {
        piVar2 = (int *)(uVar3 + 0x84);
        iVar4 = sscanf((char *)g_dwStdConffile_aLine,s_numcolormaps__d_004ec878,piVar2);
        if (iVar4 == 1) {
          if (*piVar2 == 0) goto LAB_004a5c4e;
          puVar5 = (undefined4 *)
                   (*g_pSputRoomHS->pAlloc)
                             (*piVar2 * 0x34,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x935);
          iVar4 = *piVar2;
          *piVar1 = (int)puVar5;
          for (uVar6 = iVar4 * 0xd & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1) {
            *puVar5 = 0;
            puVar5 = puVar5 + 1;
          }
          for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
            *(undefined1 *)puVar5 = 0;
            puVar5 = (undefined4 *)((int)puVar5 + 1);
          }
        }
        if (*piVar1 != 0) {
          sscanf((char *)g_dwStdConffile_aLine,s_colormap__s_004ec868,uVar3 + 0x8c);
        }
      }
      else {
        iVar4 = Set_IsHandleValid(local_100);
        if (iVar4 == 0) {
          return 0;
        }
      }
    }
LAB_004a5c4e:
    iVar4 = stdConffile_ReadLine();
    if (iVar4 == 0) {
      return 1;
    }
  } while( true );
}
#undef local_100


/* ---- 0x004a5c90  sputRoom_ParseSectors ---- */
/* Section handler 'sectors' registered by sputRoom_Start: runs SetFile_ParseSectors for the set
   being parsed. Original name sputRoom_ParseSectors (the remaster's GrimFandango (Linux): the only
   unmatched caller of SetFile_ParseSectors; 1 matched neighbours agree, 0 disagree); was
   SetFile_SectorsSectionHandler. */

undefined4 sputRoom_ParseSectors(void)

{
  int iVar1;
  
  iVar1 = ParseCollection(g_dwLoadingRoom);
  if (iVar1 != 0) {
    Set_IsHandleValid(iVar1);
  }
  return 1;
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
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  SectorList_FreeShrinkSave();
  g_nShrinkVertexCount = 0;
  g_nShrinkSectorCount = 0;
  for (pvVar4 = g_pWalkPlane_wp_head; pvVar4 != (void *)0x0; pvVar4 = *(void **)((int)pvVar4 + 0x70)
      ) {
    g_nShrinkVertexCount = g_nShrinkVertexCount + *(int *)((int)pvVar4 + 0x34);
    g_nShrinkSectorCount = g_nShrinkSectorCount + 1;
  }
  g_pShrinkVertexSave = Plat_Alloc(g_nShrinkVertexCount * 0x14);
  local_4 = 0;
  for (pvVar4 = g_pWalkPlane_wp_head; pvVar4 != (void *)0x0; pvVar4 = *(void **)((int)pvVar4 + 0x70)
      ) {
    iVar6 = 0;
    if (0 < *(int *)((int)pvVar4 + 0x34)) {
      iVar8 = local_4 * 0x14;
      piVar5 = (int *)((int)pvVar4 + 0x38);
      do {
        puVar2 = (undefined4 *)*piVar5;
        puVar1 = (undefined4 *)((int)g_pShrinkVertexSave + iVar8 + 4);
        *puVar1 = *puVar2;
        puVar1[1] = puVar2[1];
        puVar1[2] = puVar2[2];
        puVar1[3] = puVar2[3];
        *(int *)((int)g_pShrinkVertexSave + iVar8) = *piVar5 - (int)IMG_ADDR(0x008cb0b0) >> 4;
        local_4 = local_4 + 1;
        iVar6 = iVar6 + 1;
        iVar8 = iVar8 + 0x14;
        piVar5 = piVar5 + 1;
      } while (iVar6 < *(int *)((int)pvVar4 + 0x34));
    }
  }
  g_pShrinkSectorSave = Plat_Alloc(g_nShrinkSectorCount * 0x34);
  if (g_pWalkPlane_wp_head != (void *)0x0) {
    iVar6 = 0;
    pvVar4 = g_pWalkPlane_wp_head;
    do {
      iVar8 = 0;
      *(void **)((int)g_pShrinkSectorSave + iVar6) = pvVar4;
      *(undefined4 *)((int)g_pShrinkSectorSave + iVar6 + 4) = *(undefined4 *)((int)pvVar4 + 0x34);
      *(undefined4 *)((int)g_pShrinkSectorSave + iVar6 + 0x30) = *(undefined4 *)((int)pvVar4 + 0x28)
      ;
      if (0 < *(int *)((int)pvVar4 + 0x34)) {
        iVar7 = iVar6 + 8;
        piVar5 = (int *)((int)pvVar4 + 0x38);
        do {
          iVar3 = *piVar5;
          piVar5 = piVar5 + 1;
          *(int *)((int)g_pShrinkSectorSave + iVar7) = iVar3 - (int)IMG_ADDR(0x008cb0b0) >> 4;
          iVar8 = iVar8 + 1;
          iVar7 = iVar7 + 4;
        } while (iVar8 < *(int *)((int)pvVar4 + 0x34));
      }
      pvVar4 = *(void **)((int)pvVar4 + 0x70);
      iVar6 = iVar6 + 0x34;
    } while (pvVar4 != (void *)0x0);
  }
  UINT_008d0868 = 1;
  return;
}
#undef local_4


/* ---- 0x004a6330  SectorList_FreeShrinkSave ---- */
void SectorList_FreeShrinkSave(void)

{
  UINT_008d0868 = 0;
  if (g_pShrinkVertexSave != (void *)0x0) {
    Plat_Free(g_pShrinkVertexSave);
  }
  if (g_pShrinkSectorSave != (void *)0x0) {
    Plat_Free(g_pShrinkSectorSave);
  }
  g_pShrinkVertexSave = (void *)0x0;
  g_pShrinkSectorSave = (void *)0x0;
  g_nShrinkSectorCount = 0;
  g_nShrinkVertexCount = 0;
  return;
}

/* ---- 0x004a6380  SectorList_RestoreAfterShrink ---- */
void SectorList_RestoreAfterShrink(void)

{
  int iVar1;
  void *pvVar2;
  int *piVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  
  pvVar2 = g_pWalkPlane_wp_head;
  piVar3 = g_pShrinkVertexSave;
  iVar8 = g_nShrinkVertexCount;
  if (UINT_008d0868 != 0) {
    for (; g_nShrinkVertexCount = iVar8, g_pShrinkVertexSave = piVar3, pvVar2 != (void *)0x0;
        pvVar2 = *(void **)((int)pvVar2 + 0x70)) {
      iVar8 = 0;
      if (0 < *(int *)((int)pvVar2 + 0x34)) {
        puVar7 = (undefined4 *)((int)pvVar2 + 0x38);
        do {
          SectorVertexPool_Release(*puVar7);
          iVar8 = iVar8 + 1;
          puVar7 = puVar7 + 1;
        } while (iVar8 < *(int *)((int)pvVar2 + 0x34));
      }
      piVar3 = g_pShrinkVertexSave;
      iVar8 = g_nShrinkVertexCount;
    }
    if (0 < iVar8) {
      do {
        iVar9 = *piVar3;
        iVar8 = iVar8 + -1;
        (&FLOAT_008cb0b0)[iVar9 * 4] = PUN(float,piVar3[1]);
        (&UINT_008cb0b4)[iVar9 * 4] = piVar3[2];
        (&UINT_008cb0b8)[iVar9 * 4] = piVar3[3];
        (&UINT_008cb0bc)[iVar9 * 4] = piVar3[4];
        piVar3 = piVar3 + 5;
      } while (iVar8 != 0);
    }
    iVar8 = 0;
    if (0 < g_nShrinkSectorCount) {
      iVar9 = 0;
      do {
        iVar1 = *(int *)((int)g_pShrinkSectorSave + iVar9);
        iVar6 = *(int *)((int)g_pShrinkSectorSave + iVar9 + 4);
        iVar5 = 0;
        *(int *)(iVar1 + 0x34) = iVar6;
        if (0 < iVar6) {
          iVar6 = iVar9 + 8;
          puVar7 = (undefined4 *)(iVar1 + 0x38);
          do {
            iVar5 = iVar5 + 1;
            *puVar7 = &FLOAT_008cb0b0 + *(int *)((int)g_pShrinkSectorSave + iVar6) * 4;
            iVar6 = iVar6 + 4;
            puVar7 = puVar7 + 1;
          } while (iVar5 < *(int *)(iVar1 + 0x34));
        }
        iVar8 = iVar8 + 1;
        iVar6 = iVar9 + 0x30;
        iVar9 = iVar9 + 0x34;
        *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)((int)g_pShrinkSectorSave + iVar6);
      } while (iVar8 < g_nShrinkSectorCount);
    }
    UINT_008cf26c = 0;
    pfVar4 = &FLOAT_008cb0b0;
    do {
      if (0 < PUN(int,(float)*pfVar4)) {
        UINT_008cf26c = UINT_008cf26c + 1;
      }
      pfVar4 = pfVar4 + 4;
    } while ((int)pfVar4 < IMG_ADDR(0x008cf0b0));
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
  rdVector_Normalize3Acc(pfVar1);
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
  *(uint *)((int)this + 0x70) = (&UINT_008cf288)[iVar7 * 10];
  if ((&UINT_008cf288)[iVar7 * 10] != 0) {
    *(void **)((&UINT_008cf288)[iVar7 * 10] + 0x6c) = this;
  }
  (&UINT_008cf288)[iVar7 * 10] = (uint)this;
  g_pWalkPlane_wp_head = this;
  return this;
}
#undef local_2


/* ---- 0x004a66e0  Sector_Unlink ---- */
/* __fastcall: unlinks a sector from g_pWalkPlane_wp_head and the per-type sector lists and releases
   its vertex pool entries. */

void __fastcall Sector_Unlink(void *param_1)

{
  uint *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (param_1 == g_pWalkPlane_wp_head) {
    g_pWalkPlane_wp_head = *(void **)((int)param_1 + 0x70);
  }
  iVar2 = 0;
  puVar1 = &UINT_008cf288;
  do {
    if ((void *)*puVar1 == param_1) {
      (&UINT_008cf288)[iVar2 * 10] = *(uint *)((int)param_1 + 0x70);
      break;
    }
    puVar1 = puVar1 + 10;
    iVar2 = iVar2 + 1;
  } while ((int)puVar1 < IMG_ADDR(0x008d0868));
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
void __thiscall Sector_SetName(void *this,char *name)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  
  if (name != (char *)0x0) {
    uVar2 = 0xffffffff;
    do {
      pcVar4 = name;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar4 = name + 1;
      cVar1 = *name;
      name = pcVar4;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    pcVar4 = pcVar4 + -uVar2;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)this = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      this = (char *)((int)this + 4);
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(char *)this = *pcVar4;
      pcVar4 = pcVar4 + 1;
      this = (char *)((int)this + 1);
    }
  }
  return;
}

/* ---- 0x004a6790  Sector_SetSavedType ---- */
/* Stores the type bits (+0x24); 0x1000 sets a small shrink tolerance, 0x100 (edge sector) needs 4
   vertices and picks the long axis (+0x78) */

void __thiscall Sector_SetSavedType(void *this,uint type)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x40 - 0x10)))
  #define local_c (*(float *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x40 - 0x4)))
  
  *(uint *)((int)this + 0x24) = type;
  *(undefined4 *)((int)this + 0x30) = 0x461c3c00;
  if ((type & 0x1000) != 0) {
    *(undefined4 *)((int)this + 0x30) = 0x3ba3d70a;
  }
  if ((type & 0x100) != 0) {
    if (*(int *)((int)this + 0x34) != 4) {
      *(undefined4 *)((int)this + 0x24) = 0x1000;
      return;
    }
    iVar1 = *(int *)((int)this + 0x3c);
    iVar2 = *(int *)((int)this + 0x38);
    iVar3 = *(int *)((int)this + 0x44);
    iVar4 = *(int *)((int)this + 0x40);
    local_c = *(float *)(iVar1 + 4) - *(float *)(iVar2 + 4);
    local_8 = *(float *)(iVar1 + 8) - *(float *)(iVar2 + 8);
    local_4 = *(float *)(iVar1 + 0xc) - *(float *)(iVar2 + 0xc);
    local_18 = *(float *)(iVar3 + 4) - *(float *)(iVar4 + 4);
    local_14 = *(float *)(iVar3 + 8) - *(float *)(iVar4 + 8);
    local_10 = *(float *)(iVar3 + 0xc) - *(float *)(iVar4 + 0xc);
    fVar7 = rdVector_Normalize3Acc(&local_c);
    fVar8 = rdVector_Normalize3Acc(&local_18);
    fVar5 = local_10 * local_4 + local_14 * local_8 + local_18 * local_c;
    if (fVar5 < 0.0) {
      fVar5 = -fVar5;
    }
    iVar1 = *(int *)((int)this + 0x40);
    iVar2 = *(int *)((int)this + 0x3c);
    local_c = *(float *)(iVar1 + 4) - *(float *)(iVar2 + 4);
    iVar3 = *(int *)((int)this + 0x38);
    iVar4 = *(int *)((int)this + 0x44);
    local_8 = *(float *)(iVar1 + 8) - *(float *)(iVar2 + 8);
    local_4 = *(float *)(iVar1 + 0xc) - *(float *)(iVar2 + 0xc);
    local_18 = *(float *)(iVar3 + 4) - *(float *)(iVar4 + 4);
    local_14 = *(float *)(iVar3 + 8) - *(float *)(iVar4 + 8);
    local_10 = *(float *)(iVar3 + 0xc) - *(float *)(iVar4 + 0xc);
    fVar9 = rdVector_Normalize3Acc(&local_c);
    fVar10 = rdVector_Normalize3Acc(&local_18);
    fVar6 = local_10 * local_4 + local_14 * local_8 + local_18 * local_c;
    if (fVar6 < 0.0) {
      fVar6 = -fVar6;
    }
    if (fVar6 < fVar5) {
      if (fVar7 < fVar8) {
        *(undefined4 *)((int)this + 0x78) = 0;
        return;
      }
      *(undefined4 *)((int)this + 0x78) = 2;
      return;
    }
    if (fVar9 < fVar10) {
      *(undefined4 *)((int)this + 0x78) = 1;
      return;
    }
    *(undefined4 *)((int)this + 0x78) = 3;
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a6980  Sector_ContainsPoint ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Sector_ContainsPoint(sector, point, checkActive). With checkActive, an inactive sector (+0x28 or
   +0x2c zero) contains nothing. 1) distance from the plane (normal at +0x60..+0x68, vertex[1]): a
   distance <= 1e-5 counts as 0, then |d| <= height (+0x30; 0.005 for walk sectors, or when the file
   says 0). 2) each edge prev->cur on the two axes +0x7c / +0x80: v =
   (p[a]-prev[a])*(cur[b]-prev[b]) - (p[b]-prev[b])*(cur[a]-prev[a]) + 1e-5, |v| <= 1e-5 -> 0, v < 0
   = outside. So a point up to 2e-5 (cross-product units, i.e. 2e-5 / edge length) outside an edge
   is inside.
   Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
    */

int __thiscall Sector_ContainsPoint(void *this,float *point,int checkActive)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  
  if (checkActive != 0) {
    if (*(int *)((int)this + 0x2c) == 0) {
      return 0;
    }
    if (*(int *)((int)this + 0x28) == 0) {
      return 0;
    }
  }
  iVar1 = *(int *)((int)this + 0x3c);
  fVar2 = (point[1] - *(float *)(iVar1 + 8)) * *(float *)((int)this + 100) +
          (point[2] - *(float *)(iVar1 + 0xc)) * *(float *)((int)this + 0x68) +
          (*point - *(float *)(iVar1 + 4)) * *(float *)((int)this + 0x60);
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
  if (fVar2 <= *(float *)((int)this + 0x30)) {
    iVar1 = *(int *)((int)this + 0x34);
    iVar8 = 0;
    if (iVar1 < 1) {
      return 1;
    }
    iVar7 = *(int *)((int)this + 0x80) * 4;
    iVar9 = *(int *)((int)this + 0x7c) * 4;
    piVar10 = (int *)((int)this + 0x38);
    iVar5 = *(int *)((int)this + iVar1 * 4 + 0x34) + 4;
    while( true ) {
      iVar6 = *piVar10 + 4;
      fVar2 = ((point[*(int *)((int)this + 0x7c)] - *(float *)(iVar5 + iVar9)) *
               (*(float *)(iVar6 + iVar7) - *(float *)(iVar5 + iVar7)) +
              (point[*(int *)((int)this + 0x80)] - *(float *)(iVar5 + iVar7)) *
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
#endif


/* ---- 0x004a6b30  Sector_ClampPoint ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
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
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  Sector_FixPlaneCoordinate(this,a1);
  iVar7 = *(int *)((int)this + 0x34);
  iVar9 = 0;
  if (0 < iVar7) {
    local_10 = (int)this + 0x38;
    pfVar8 = (float *)(*(int *)((int)this + iVar7 * 4 + 0x34) + 4);
    do {
      iVar7 = *(int *)local_10;
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
      local_10 = local_10 + 4;
      pfVar8 = pfVar10;
    } while (iVar9 < iVar7);
  }
  return iVar7;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c

#endif


/* ---- 0x004a6d10  WalkPlane_Intersection ---- */
/* WARNING: Variable defined which should be unmapped: local_3c */
/* Original name WalkPlane_Intersection (the remaster's GrimFandango (Linux):
   WalkPlane::Intersection in the remaster (a C++ method there); the only unmatched callee of
   Sector_MoveWalkerToOppositeEdge; 3 matched neighbours agree, 1 disagree); was
   Sector_FindExitPoint. */

float __thiscall WalkPlane_Intersection(void *this,int a1,int a2,int a3)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  float *pfVar11;
  int iVar12;
  float fVar13;
  #define local_3c (*(uint *)(_frame + (0x50 - 0x3c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(float *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(float *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(float *)(_frame + (0x50 - 0x10)))
  #define local_c (*(float *)(_frame + (0x50 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x50 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x50 - 0x4)))
  
  local_1c = 0;
  *(undefined4 *)((int)this + 0x74) = 0xffffffff;
  iVar8 = Sector_ContainsPoint(this,(float *)a2,1);
  if (iVar8 == 0) {
    local_28 = 0;
    *(undefined4 *)a3 = *(undefined4 *)a2;
    *(undefined4 *)(a3 + 4) = *(undefined4 *)(a2 + 4);
    *(undefined4 *)(a3 + 8) = *(undefined4 *)(a2 + 8);
    if (0 < *(int *)((int)this + 0x34)) {
      local_24 = (int)this + 0x38;
      pfVar10 = (float *)(*(int *)((int)this + *(int *)((int)this + 0x34) * 4 + 0x34) + 4);
      do {
        iVar8 = *(int *)((int)this + 0x7c);
        iVar1 = *(int *)((int)this + 0x80);
        iVar2 = *(int *)local_24;
        pfVar11 = (float *)(iVar2 + 4);
        iVar12 = iVar8 * 4;
        iVar9 = iVar1 * 4;
        local_14 = pfVar11[iVar1] - pfVar10[iVar1];
        local_18 = -(pfVar11[iVar8] - pfVar10[iVar8]);
        fVar13 = (*(float *)(a3 + iVar9) - pfVar10[iVar1]) * local_18 +
                 (*(float *)(a3 + iVar12) - pfVar10[iVar8]) * local_14;
        fVar3 = fVar13;
        if (fVar13 < 0.0) {
          fVar3 = -fVar13;
        }
        fVar4 = fVar13;
        if (fVar3 <= 1e-05) {
          fVar4 = 0.0;
        }
        if (fVar4 < 0.0) {
          fVar3 = *(float *)(a3 + iVar9) - *(float *)(a1 + iVar9);
          fVar7 = *(float *)(a3 + iVar12) - *(float *)(a1 + iVar12);
          fVar6 = -(fVar3 * local_18) - fVar7 * local_14;
          fVar4 = fVar6;
          if (fVar6 < 0.0) {
            fVar4 = -fVar6;
          }
          fVar5 = fVar6;
          if (fVar4 <= 1e-05) {
            fVar5 = 0.0;
          }
          if (fVar5 != 0.0) {
            *(float *)(a3 + iVar9) = fVar3 * (fVar13 / fVar6) + *(float *)(a3 + iVar9);
            *(float *)(a3 + *(int *)((int)this + 0x7c) * 4) =
                 fVar7 * (fVar13 / fVar6) + *(float *)(a3 + *(int *)((int)this + 0x7c) * 4);
            local_c = *pfVar10 - *pfVar11;
            local_8 = pfVar10[1] - *(float *)(iVar2 + 8);
            local_4 = pfVar10[2] - *(float *)(iVar2 + 0xc);
            *(uint *)((int)this + 0x74) = local_28;
            local_1c = (uint)pfVar10;
          }
        }
        local_28 = local_28 + 1;
        local_24 = local_24 + 4;
        pfVar10 = pfVar11;
      } while ((int)local_28 < *(int *)((int)this + 0x34));
    }
    Sector_FixPlaneCoordinate(this,a3);
    if (local_1c != 0) {
      local_18 = *(float *)a1 - *(float *)a2;
      local_14 = *(float *)(a1 + 4) - *(float *)(a2 + 4);
      local_10 = *(float *)(a1 + 8) - *(float *)(a2 + 8);
      rdVector_Normalize3Acc(&local_c);
      rdVector_Normalize3Acc(&local_18);
      fVar13 = rdVector_Dot3(&local_c,&local_18);
      fVar13 = stdMath_ArcSin3(fVar13);
      if (fVar13 <= 0.0) {
        return -90.2 - fVar13;
      }
      return 90.2 - fVar13;
    }
    WalkPlane_SnapTo(this,(float *)a3);
  }
  return 0.0;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_3c
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a6fa0  WalkPlane_SnapTo ---- */
/* Lua SnapToPlane: projects the point onto the plane of the sector found by Sector_FindByName
   Original name WalkPlane_SnapTo (the remaster's GrimFandango (Linux): WalkPlane::SnapTo in the
   remaster (a C++ method there); the only unmatched callee of Lua_SnapToPlane; 1 matched neighbours
   agree, 0 disagree); was Sector_SnapToPlane. */

void __thiscall WalkPlane_SnapTo(void *this,float *pos)

{
  int iVar1;
  float fVar2;
  
  iVar1 = *(int *)((int)this + 0x38);
  fVar2 = (pos[1] - *(float *)(iVar1 + 8)) * *(float *)((int)this + 100) +
          (pos[2] - *(float *)(iVar1 + 0xc)) * *(float *)((int)this + 0x68) +
          (*pos - *(float *)(iVar1 + 4)) * *(float *)((int)this + 0x60);
  *pos = *pos - fVar2 * *(float *)((int)this + 0x60);
  pos[1] = pos[1] - fVar2 * *(float *)((int)this + 100);
  pos[2] = pos[2] - fVar2 * *(float *)((int)this + 0x68);
  return;
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
void __thiscall Sector_DrawOutline(void *this,int color)

{
  int iVar1;
  float *a;
  int *piVar2;
  int iVar3;
  
  if (*(int *)((int)this + 0x28) != 0) {
    iVar3 = 0;
    if (0 < *(int *)((int)this + 0x34)) {
      piVar2 = (int *)((int)this + 0x38);
      a = (float *)(*(int *)((int)this + *(int *)((int)this + 0x34) * 4 + 0x34) + 4);
      do {
        iVar1 = *piVar2;
        rdPrimit3_DrawLine(a,(float *)(iVar1 + 4),(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,color,
                           0xffffffff);
        iVar3 = iVar3 + 1;
        piVar2 = piVar2 + 1;
        a = (float *)(iVar1 + 4);
      } while (iVar3 < *(int *)((int)this + 0x34));
    }
  }
  return;
}

/* ---- 0x004a71e0  SectorList_FindByPoint ---- */
void * SectorList_FindByPoint(float *param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  void *this;
  
  this = g_pWalkPlane_wp_head;
  if (g_pWalkPlane_wp_head == (void *)0x0) {
    return (void *)0x0;
  }
  while (((*(uint *)((int)this + 0x24) & param_2) == 0 ||
         (iVar2 = Sector_ContainsPoint(this,param_1,1), iVar2 == 0))) {
    piVar1 = (int *)((int)this + 0x70);
    this = (void *)*piVar1;
    if ((void *)*piVar1 == (void *)0x0) {
      return (void *)0x0;
    }
  }
  return this;
}

/* ---- 0x004a7230  WalkPlane_PlaneNamed ---- */
/* Original name WalkPlane_PlaneNamed (the remaster's GrimFandango (Linux): WalkPlane::PlaneNamed in
   the remaster (a C++ method there); the only unmatched callee of Actor_SetShadowPlane; 7 matched
   neighbours agree, 0 disagree); was Sector_FindByName. */

void * __cdecl WalkPlane_PlaneNamed(char *name)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  
  pbVar2 = g_pWalkPlane_wp_head;
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
  
  for (pvVar1 = g_pWalkPlane_wp_head;
      (pvVar1 != (void *)0x0 && (*(int *)((int)pvVar1 + 0x20) != id));
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
  this = g_pWalkPlane_wp_head;
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


/* ---- 0x004a7390  WalkPlane_JumpOut ---- */
/* Original name WalkPlane_JumpOut (the remaster's GrimFandango (Linux): WalkPlane::JumpOut in the
   remaster (a C++ method there); the only unmatched callee of Actor_PushSectorOppositeEdge; 1
   matched neighbours agree, 1 disagree); was Sector_MoveWalkerToOppositeEdge. */

void __thiscall WalkPlane_JumpOut(void *this,float *walker)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
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
    local_18 = *walker;
    local_14 = walker[1];
    local_10 = walker[2];
    local_24 = walker[6] * -10.0 + local_18;
    local_20 = walker[7] * -10.0 + local_14;
    local_1c = walker[8] * -10.0 + local_10;
    WalkPlane_Intersection(this,(int)&local_18,(int)&local_24,(int)&local_c);
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
      Puck_SetPos(walker,&local_c);
    }
  }
  return;
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

float * __thiscall Sector_EdgeFollowDirection(void *this,float *walker)

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
  float fVar12;
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
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
  
  local_18 = *walker;
  local_14 = walker[1];
  local_10 = walker[2];
  if (walker[0x10] <= 0.0) {
    fVar12 = 100.0;
  }
  else {
    fVar12 = -100.0;
  }
  if (walker[0x10] <= 0.0) {
    fVar4 = 100.0;
  }
  else {
    fVar4 = -100.0;
  }
  if (walker[0x10] <= 0.0) {
    fVar5 = 100.0;
  }
  else {
    fVar5 = -100.0;
  }
  local_30 = walker[6] * fVar12 + local_18;
  local_2c = walker[7] * fVar4 + local_14;
  local_28 = walker[8] * fVar5 + local_10;
  WalkPlane_Intersection(this,(int)&local_18,(int)&local_30,IMG_ADDR(0x008cf260));
  iVar1 = *(int *)((int)this + 0x74);
  if (iVar1 != -1) {
    iVar2 = *(int *)((int)this + iVar1 * 4 + 0x38);
    fVar5 = *(float *)(iVar2 + 4) - g_vEdgeFollowDir;
    fVar12 = *(float *)(iVar2 + 8) - *(float *)&DAT_008cf264;
    fVar4 = *(float *)(iVar2 + 0xc) - *(float *)&DAT_008cf268;
    if (0.0025 <= fVar4 * fVar4 + fVar12 * fVar12 + fVar5 * fVar5) {
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
      if ((*(float *)(*(int *)((int)this + local_38 * 4 + 0x38) + 0xc) - *(float *)&DAT_008cf268) *
          (*(float *)(*(int *)((int)this + uVar9 * 4 + 0x38) + 0xc) - *(float *)&DAT_008cf268) +
          (*(float *)(*(int *)((int)this + uVar11 * 4 + 0x38) + 8) - *(float *)&DAT_008cf264) *
          (*(float *)(*(int *)((int)this + uVar8 * 4 + 0x38) + 8) - *(float *)&DAT_008cf264) +
          (*(float *)(*(int *)((int)this + uVar7 * 4 + 0x38) + 4) - g_vEdgeFollowDir) *
          (*(float *)(*(int *)((int)this + uVar6 * 4 + 0x38) + 4) - g_vEdgeFollowDir) < 0.0025) {
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
        rdVector_Normalize3Acc(&local_24);
        fVar12 = rdVector_Dot3(&local_24,walker + 6);
        fVar12 = stdMath_ArcSin3(fVar12);
        if ((90.0 - fVar12 < 1.0) || (179.0 < 90.0 - fVar12)) {
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
      rdVector_Normalize3Acc(&local_24);
      fVar12 = rdVector_Dot3(&local_24,walker + 6);
      fVar12 = stdMath_ArcSin3(fVar12);
      if (90.0 - fVar12 < 1.0) {
        *(int *)((int)this + 0x74) = (*(int *)((int)this + 0x74) + 1) % *(int *)((int)this + 0x34);
      }
      else if (179.0 < 90.0 - fVar12) {
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
    fVar12 = *(float *)(iVar3 + 4) - *(float *)(iVar2 + 4);
    fVar4 = fVar12;
    if (fVar12 < 0.0) {
      fVar4 = -fVar12;
    }
    fVar5 = fVar12;
    if (fVar4 <= 1e-05) {
      fVar5 = 0.0;
    }
    if (fVar5 == 0.0) {
      fVar12 = (*(float *)&DAT_008cf264 - *(float *)(iVar2 + 8)) /
               (*(float *)(iVar3 + 8) - *(float *)(iVar2 + 8));
    }
    else {
      fVar12 = (g_vEdgeFollowDir - *(float *)(iVar2 + 4)) / fVar12;
    }
    if (fVar12 < 0.15) {
      fVar12 = 0.15;
    }
    if (0.85 < fVar12) {
      fVar12 = 0.85;
    }
    iVar2 = *(int *)((int)this + 0x34);
    iVar3 = *(int *)((int)this + ((iVar1 + 1) % iVar2) * 4 + 0x38);
    iVar1 = *(int *)((int)this + ((iVar2 + -2 + iVar1) % iVar2) * 4 + 0x38);
    local_8 = (*(float *)(iVar1 + 8) - *(float *)(iVar3 + 8)) * fVar12 + *(float *)(iVar3 + 8);
    local_4 = (*(float *)(iVar1 + 0xc) - *(float *)(iVar3 + 0xc)) * fVar12 + *(float *)(iVar3 + 0xc)
    ;
    g_vEdgeFollowDir =
         ((*(float *)(iVar1 + 4) - *(float *)(iVar3 + 4)) * fVar12 + *(float *)(iVar3 + 4)) -
         g_vEdgeFollowDir;
    *(float *)&DAT_008cf264 = local_8 - *(float *)&DAT_008cf264;
    *(float *)&DAT_008cf268 = local_4 - *(float *)&DAT_008cf268;
    rdVector_Normalize3Acc(&g_vEdgeFollowDir);
    if (walker[0x10] < 0.0) {
      g_vEdgeFollowDir = g_vEdgeFollowDir * -1.0;
      *(float *)&DAT_008cf264 = *(float *)&DAT_008cf264 * -1.0;
      *(float *)&DAT_008cf268 = *(float *)&DAT_008cf268 * -1.0;
    }
    return &g_vEdgeFollowDir;
  }
  return (float *)0x0;
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
#undef local_34
#undef local_38
#undef local_4
#undef local_8


/* ---- 0x004a7a90  SectorList_ResetFree ---- */
void SectorList_ResetFree(void)

{
  void *pvVar1;
  
  for (pvVar1 = g_pWalkPlane_wp_head; pvVar1 != (void *)0x0; pvVar1 = *(void **)((int)pvVar1 + 0x70)
      ) {
    *(undefined4 *)((int)pvVar1 + 0x2c) = 1;
  }
  return;
}

/* ---- 0x004a7ab0  SectorVertexPool_GetOrAdd ---- */
/* Source: Engine/WalkPlane.cpp (line 974, from __FILE__/__LINE__ passed to the allocator) */

float * SectorVertexPool_GetOrAdd(undefined4 param_1,float *param_2)

{
  float *pfVar1;
  uint *puVar2;
  int iVar3;
  float *pfVar4;
  
  pfVar4 = (float *)0x0;
  if (0x3fd < (int)UINT_008cf26c) {
    (*g_pStd_HS->pAssertFail)
              (s_tot_verts___MAX_DB_VERTS___2_004ec8a8,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,
               0x3ce);
  }
  iVar3 = 0;
  puVar2 = &UINT_008cb0b4;
  do {
    if ((PUN(float,puVar2[-1]) != 0.0) &&
       ((param_2[2] - PUN(float,puVar2[2])) * (param_2[2] - PUN(float,puVar2[2])) +
        (param_2[1] - PUN(float,puVar2[1])) * (param_2[1] - PUN(float,puVar2[1])) +
        (*param_2 - PUN(float,*puVar2)) * (*param_2 - PUN(float,*puVar2)) < 1e-08)) {
      pfVar4 = &FLOAT_008cb0b0 + iVar3 * 4;
      *pfVar4 = PUN(float,(PUN(int,(float)*pfVar4) + 1));
      return pfVar4;
    }
    puVar2 = puVar2 + 4;
    iVar3 = iVar3 + 1;
  } while ((int)puVar2 < IMG_ADDR(0x008cf0b4));
  iVar3 = 0;
  pfVar1 = &FLOAT_008cb0b0;
  do {
    if (PUN(int,(float)*pfVar1) < 1) {
      pfVar4 = &FLOAT_008cb0b0 + iVar3 * 4;
      break;
    }
    pfVar1 = pfVar1 + 4;
    iVar3 = iVar3 + 1;
  } while ((int)pfVar1 < IMG_ADDR(0x008cf0b0));
  *pfVar4 = 1.4013e-45;
  UINT_008cf26c = UINT_008cf26c + 1;
  pfVar4[1] = *param_2;
  pfVar4[2] = param_2[1];
  pfVar4[3] = param_2[2];
  return pfVar4;
}

/* ---- 0x004a7ba0  SectorVertexPool_Release ---- */
void SectorVertexPool_Release(int *param_1)

{
  int iVar1;
  
  if ((0 < *param_1) && (iVar1 = *param_1 + -1, *param_1 = iVar1, iVar1 == 0)) {
    UINT_008cf26c = UINT_008cf26c - 1;
  }
  return;
}

/* ---- 0x004a7bc0  ParseCollection ---- */
/* Source: Engine/WalkPlane.cpp (lines 1070-1184, from __FILE__/__LINE__ passed to the allocator)
   Original name ParseCollection (the remaster's GrimFandango (Linux): the only unpaired callee of
   sputRoom_ParseSectors on both sides; same parser (section:, numsectors, sector, id, type, default
   visibility, height, numvertices, numgates, vertices:); WalkPlane.cpp); was SetFile_ParseSectors.
    */

undefined * ParseCollection(int param_1)

{
  unsigned char _frame[0x210] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  byte bVar2;
  int iVar3;
  void *pvVar4;
  undefined1 *puVar5;
  byte *pbVar6;
  int iVar7;
  undefined *puVar8;
  uint uVar9;
  uint uVar10;
  char *pcVar11;
  byte *pbVar12;
  char *pcVar13;
  bool bVar14;
  #define local_200 (*(uint *)(_frame + (0x210 - 0x200)))
  #define local_1fc (*(uint *)(_frame + (0x210 - 0x1fc)))
  #define local_1f8 (*(uint *)(_frame + (0x210 - 0x1f8)))
  #define local_1f4 (*(float *)(_frame + (0x210 - 0x1f4)))
  #define local_1f0 (*(uint *)(_frame + (0x210 - 0x1f0)))
  #define local_1ec (*(uint *)(_frame + (0x210 - 0x1ec)))
  #define local_1e8 (*(uint *)(_frame + (0x210 - 0x1e8)))
  #define local_1e4 (*(byte (*)[48])(_frame + (0x210 - 0x1e4)))
  #define local_1b4 (*(byte (*)[48])(_frame + (0x210 - 0x1b4)))
  #define local_184 (*(undefined1 (*)[4])(_frame + (0x210 - 0x184)))
  #define auStack_180 (*(undefined1 (*)[4])(_frame + (0x210 - 0x180)))
  #define auStack_17c (*(undefined1 (*)[112])(_frame + (0x210 - 0x17c)))
  #define local_10c (*(char (*)[256])(_frame + (0x210 - 0x10c)))
  
  local_1fc = 0;
  local_1ec = 0;
  local_200 = 0;
  local_1f0 = 0;
  local_1f8 = 0;
  local_1f4 = 12345.0;
  local_1b4[0] = 0;
  DAT_008cf218 = 0;
  iVar3 = stdConffile_ReadLine();
  do {
    if (iVar3 == 0) {
      if (2 < (int)local_1fc) {
        pvVar4 = Plat_Alloc(0x84);
        if (pvVar4 == (void *)0x0) {
          puVar5 = (undefined1 *)0x0;
        }
        else {
          puVar5 = Sector_Construct(pvVar4,(int)local_184,local_1fc,param_1);
        }
        if (puVar5 != (undefined1 *)0x0) {
          Mem_CheckAlloc(puVar5,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,0x4a0);
          Sector_SetName(puVar5,(char *)local_1b4);
          *(uint *)(puVar5 + 0x20) = local_1ec;
          *(uint *)(puVar5 + 0x28) = local_1f0;
          Sector_SetSavedType(puVar5,local_200);
        }
      }
      puVar8 = (undefined *)0x0;
LAB_004a8147:
      return puVar8;
    }
    uVar9 = 0xffffffff;
    pcVar11 = (char *)g_dwStdConffile_aLine;
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
    iVar3 = sscanf(local_10c,s_section___s_004ddd64,&DAT_008cf218);
    if (iVar3 == 1) {
      if (2 < (int)local_1fc) {
        pvVar4 = Plat_Alloc(0x84);
        if (pvVar4 == (void *)0x0) {
          puVar5 = (undefined1 *)0x0;
        }
        else {
          puVar5 = Sector_Construct(pvVar4,(int)local_184,local_1fc,param_1);
        }
        if (puVar5 != (undefined1 *)0x0) {
          Mem_CheckAlloc(puVar5,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,0x42e);
          Sector_SetName(puVar5,(char *)local_1b4);
          *(uint *)(puVar5 + 0x20) = local_1ec;
          *(uint *)(puVar5 + 0x28) = local_1f0;
          Sector_SetSavedType(puVar5,local_200);
        }
      }
      puVar8 = &DAT_008cf218;
      goto LAB_004a8147;
    }
    iVar3 = String_ContainsSubstring(local_10c,s_numsectors_004ec9a8);
    if (iVar3 == 0) {
      iVar3 = sscanf(local_10c,s_sector__s_004ec99c,local_1e4);
      if (iVar3 == 1) {
        if (2 < (int)local_1fc) {
          pvVar4 = Plat_Alloc(0x84);
          if (pvVar4 == (void *)0x0) {
            puVar5 = (undefined1 *)0x0;
          }
          else {
            puVar5 = Sector_Construct(pvVar4,(int)local_184,local_1fc,param_1);
          }
          if (puVar5 != (undefined1 *)0x0) {
            Mem_CheckAlloc(puVar5,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,0x445);
            Sector_SetName(puVar5,(char *)local_1b4);
            *(uint *)(puVar5 + 0x28) = local_1f0;
            *(uint *)(puVar5 + 0x20) = local_1ec;
            Sector_SetSavedType(puVar5,local_200);
            if (local_1f4 != 12345.0) {
              if (local_200 == 0x1000) {
                local_1f4 = 0.005;
              }
              if (local_1f4 == 0.0) {
                local_1f4 = 0.005;
              }
              *(float *)(puVar5 + 0x30) = local_1f4;
            }
          }
        }
        uVar9 = 0xffffffff;
        pbVar6 = local_1e4;
        do {
          pbVar12 = pbVar6;
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          pbVar12 = pbVar6 + 1;
          bVar2 = *pbVar6;
          pbVar6 = pbVar12;
        } while (bVar2 != 0);
        uVar9 = ~uVar9;
        local_1b4[0] = 0;
        local_1f4 = 12345.0;
        pbVar6 = pbVar12 + -uVar9;
        pbVar12 = local_1b4;
        for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pbVar12 = *(undefined4 *)pbVar6;
          pbVar6 = pbVar6 + 4;
          pbVar12 = pbVar12 + 4;
        }
        local_1ec = 0;
        local_200 = 0;
        local_1f0 = 0;
        local_1fc = 0;
        local_1f8 = 0;
        for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *pbVar12 = *pbVar6;
          pbVar6 = pbVar6 + 1;
          pbVar12 = pbVar12 + 1;
        }
      }
      else {
        iVar3 = sscanf(local_10c,s_id__i_004ec994,&local_1e8);
        if (iVar3 == 1) {
          local_1ec = local_1e8;
        }
        else {
          iVar3 = sscanf(local_10c,s_type__s_004ec7b8,local_1e4);
          if (iVar3 == 1) {
            pbVar12 = &DAT_004ec98c;
            pbVar6 = local_1e4;
            do {
              bVar2 = *pbVar6;
              bVar14 = bVar2 < *pbVar12;
              if (bVar2 != *pbVar12) {
LAB_004a7e39:
                iVar3 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                goto LAB_004a7e3e;
              }
              if (bVar2 == 0) break;
              bVar2 = pbVar6[1];
              bVar14 = bVar2 < pbVar12[1];
              if (bVar2 != pbVar12[1]) goto LAB_004a7e39;
              pbVar6 = pbVar6 + 2;
              pbVar12 = pbVar12 + 2;
            } while (bVar2 != 0);
            iVar3 = 0;
LAB_004a7e3e:
            if (iVar3 == 0) {
              local_200 = 0x1000;
            }
            else {
              pbVar12 = &DAT_004ec984;
              pbVar6 = local_1e4;
              do {
                bVar2 = *pbVar6;
                bVar14 = bVar2 < *pbVar12;
                if (bVar2 != *pbVar12) {
LAB_004a7e7c:
                  iVar3 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                  goto LAB_004a7e81;
                }
                if (bVar2 == 0) break;
                bVar2 = pbVar6[1];
                bVar14 = bVar2 < pbVar12[1];
                if (bVar2 != pbVar12[1]) goto LAB_004a7e7c;
                pbVar6 = pbVar6 + 2;
                pbVar12 = pbVar12 + 2;
              } while (bVar2 != 0);
              iVar3 = 0;
LAB_004a7e81:
              if (iVar3 == 0) {
                local_200 = 0x1100;
              }
              else {
                pbVar12 = &DAT_004ec97c;
                pbVar6 = local_1e4;
                do {
                  bVar2 = *pbVar6;
                  bVar14 = bVar2 < *pbVar12;
                  if (bVar2 != *pbVar12) {
LAB_004a7ebf:
                    iVar3 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                    goto LAB_004a7ec4;
                  }
                  if (bVar2 == 0) break;
                  bVar2 = pbVar6[1];
                  bVar14 = bVar2 < pbVar12[1];
                  if (bVar2 != pbVar12[1]) goto LAB_004a7ebf;
                  pbVar6 = pbVar6 + 2;
                  pbVar12 = pbVar12 + 2;
                } while (bVar2 != 0);
                iVar3 = 0;
LAB_004a7ec4:
                if (iVar3 == 0) {
                  local_200 = 0x2000;
                }
                else {
                  pbVar12 = &DAT_004ec974;
                  pbVar6 = local_1e4;
                  do {
                    bVar2 = *pbVar6;
                    bVar14 = bVar2 < *pbVar12;
                    if (bVar2 != *pbVar12) {
LAB_004a7f02:
                      iVar3 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                      goto LAB_004a7f07;
                    }
                    if (bVar2 == 0) break;
                    bVar2 = pbVar6[1];
                    bVar14 = bVar2 < pbVar12[1];
                    if (bVar2 != pbVar12[1]) goto LAB_004a7f02;
                    pbVar6 = pbVar6 + 2;
                    pbVar12 = pbVar12 + 2;
                  } while (bVar2 != 0);
                  iVar3 = 0;
LAB_004a7f07:
                  if (iVar3 == 0) {
                    local_200 = 0x4000;
                  }
                  else {
                    pbVar12 = &DAT_004ec968;
                    pbVar6 = local_1e4;
                    do {
                      bVar2 = *pbVar6;
                      bVar14 = bVar2 < *pbVar12;
                      if (bVar2 != *pbVar12) {
LAB_004a7f45:
                        iVar3 = (1 - (uint)bVar14) - (uint)(bVar14 != 0);
                        goto LAB_004a7f4a;
                      }
                      if (bVar2 == 0) break;
                      bVar2 = pbVar6[1];
                      bVar14 = bVar2 < pbVar12[1];
                      if (bVar2 != pbVar12[1]) goto LAB_004a7f45;
                      pbVar6 = pbVar6 + 2;
                      pbVar12 = pbVar12 + 2;
                    } while (bVar2 != 0);
                    iVar3 = 0;
LAB_004a7f4a:
                    if (iVar3 == 0) {
                      local_200 = 0x8000;
                    }
                  }
                }
              }
            }
          }
          else {
            iVar3 = sscanf(local_10c,s_default_visibility__s_004ec950,local_1e4);
            if (iVar3 == 1) {
              pbVar12 = &DAT_004ec944;
              pbVar6 = local_1e4;
              do {
                bVar2 = *pbVar6;
                bVar14 = bVar2 < *pbVar12;
                if (bVar2 != *pbVar12) {
LAB_004a7fb9:
                  local_1f0 = (uint)(1 - bVar14 != (uint)(bVar14 != 0));
                  goto LAB_004a80a5;
                }
                if (bVar2 == 0) break;
                bVar2 = pbVar6[1];
                bVar14 = bVar2 < pbVar12[1];
                if (bVar2 != pbVar12[1]) goto LAB_004a7fb9;
                pbVar6 = pbVar6 + 2;
                pbVar12 = pbVar12 + 2;
              } while (bVar2 != 0);
              local_1f0 = 0;
            }
            else {
              iVar3 = sscanf(local_10c,s_height__f_004ec938,&local_1f4);
              if (iVar3 != 1) {
                iVar3 = sscanf(local_10c,s_numvertices__d_004ec928,&local_1e8);
                if (iVar3 == 1) {
                  local_1fc = local_1e8;
                }
                else {
                  iVar3 = sscanf(local_10c,s_numgates__s_004ec918,local_1e4);
                  if (iVar3 != 1) {
                    iVar3 = local_1f8 * 0xc;
                    iVar7 = sscanf(local_10c,s_vertices___f__f__f_004ec904,local_184 + iVar3,
                                   auStack_180 + iVar3,auStack_17c + iVar3);
                    if ((iVar7 == 3) ||
                       (((int)local_1f8 < (int)local_1fc &&
                        (iVar3 = sscanf(local_10c,s__f__f__f_004ec8f8,local_184 + iVar3,
                                        auStack_180 + iVar3,auStack_17c + iVar3), iVar3 == 3)))) {
                      local_1f8 = local_1f8 + 1;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
LAB_004a80a5:
    iVar3 = stdConffile_ReadLine();
  } while( true );
}
#undef auStack_17c
#undef auStack_180
#undef local_10c
#undef local_184
#undef local_1b4
#undef local_1e4
#undef local_1e8
#undef local_1ec
#undef local_1f0
#undef local_1f4
#undef local_1f8
#undef local_1fc
#undef local_200


/* ---- 0x004a8cb0  Sector_ClipPolygon ---- */
/* Sutherland-Hodgman clip of a polygon against the sector's edges in its projection plane; returns
   the vertex count */

int __thiscall Sector_ClipPolygon(void *this,float *verts,int count,float *out)

{
  unsigned char _frame[0x160] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 *puVar10;
  undefined1 *puVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  undefined4 *puVar15;
  int iVar16;
  undefined1 *puVar17;
  int iVar18;
  float *pfVar19;
  int iVar20;
  int iVar21;
  #define local_150 (*(uint *)(_frame + (0x160 - 0x150)))
  #define local_14c (*(uint *)(_frame + (0x160 - 0x14c)))
  #define local_148 (*(uint *)(_frame + (0x160 - 0x148)))
  #define local_144 (*(uint *)(_frame + (0x160 - 0x144)))
  #define local_140 (*(uint *)(_frame + (0x160 - 0x140)))
  #define local_13c (*(uint *)(_frame + (0x160 - 0x13c)))
  #define local_138 (*(float *)(_frame + (0x160 - 0x138)))
  #define local_134 (*(uint *)(_frame + (0x160 - 0x134)))
  #define local_130 (*(uint *)(_frame + (0x160 - 0x130)))
  #define local_12c (*(uint *)(_frame + (0x160 - 0x12c)))
  #define local_128 (*(uint *)(_frame + (0x160 - 0x128)))
  #define local_124 (*(uint *)(_frame + (0x160 - 0x124)))
  #define local_120 (*(float *)(_frame + (0x160 - 0x120)))
  #define local_11c (*(uint *)(_frame + (0x160 - 0x11c)))
  #define local_118 (*(uint *)(_frame + (0x160 - 0x118)))
  #define local_90 (*(undefined1 (*)[12])(_frame + (0x160 - 0x90)))
  #define local_84 (*(uint *)(_frame + (0x160 - 0x84)))
  #define local_80 (*(uint *)(_frame + (0x160 - 0x80)))
  #define local_7c (*(uint *)(_frame + (0x160 - 0x7c)))
  
  if (0 < count) {
    pfVar19 = &local_120;
    for (uVar13 = count * 3 & 0x3fffffff; uVar13 != 0; uVar13 = uVar13 - 1) {
      *pfVar19 = *verts;
      verts = verts + 1;
      pfVar19 = pfVar19 + 1;
    }
  }
  local_128 = 0;
  local_140 = (uint)&local_120;
  if (0 < *(int *)((int)this + 0x34)) {
    local_12c = (int)this + 0x38;
    puVar11 = local_90;
    iVar21 = *(int *)((int)this + *(int *)((int)this + 0x34) * 4 + 0x34) + 4;
    do {
      puVar17 = puVar11;
      iVar14 = *(int *)((int)this + 0x80) * 4;
      iVar18 = *(int *)local_12c + 4;
      iVar12 = *(int *)((int)this + 0x7c) * 4;
      local_150 = 0;
      fVar2 = -(*(float *)(iVar18 + iVar12) - *(float *)(iVar21 + iVar12));
      fVar3 = *(float *)(iVar18 + iVar14) - *(float *)(iVar21 + iVar14);
      local_148 = (local_140 - 0xc) + count * 0xc;
      if (0 < count) {
        iVar16 = 0;
        puVar10 = (undefined4 *)local_140;
        local_14c = (uint)puVar17;
        local_144 = count;
        local_138 = (*(float *)(local_148 + iVar12) - *(float *)(iVar21 + iVar12)) * fVar3 +
                    (*(float *)(local_148 + iVar14) - *(float *)(iVar21 + iVar14)) * fVar2;
        do {
          puVar15 = puVar10;
          iVar14 = *(int *)((int)this + 0x80);
          iVar1 = *(int *)((int)this + 0x7c);
          iVar20 = iVar1 * 4;
          iVar12 = iVar14 * 4;
          fVar4 = (PUN(float,puVar15[iVar14]) - *(float *)(iVar21 + iVar12)) * fVar2 +
                  (PUN(float,puVar15[iVar1]) - *(float *)(iVar21 + iVar20)) * fVar3;
          if ((local_138 <= 0.0) || (fVar4 <= 0.0)) {
            if ((local_138 <= 0.0) || (0.0 <= fVar4)) {
              if ((local_138 < 0.0) && (0.0 < fVar4)) {
                fVar9 = PUN(float,puVar15[iVar14]) - *(float *)(local_148 + iVar12);
                fVar8 = PUN(float,puVar15[iVar1]) - *(float *)(local_148 + iVar20);
                fVar5 = -(fVar9 * fVar2) - fVar8 * fVar3;
                fVar7 = fVar5;
                if (fVar5 < 0.0) {
                  fVar7 = -fVar5;
                }
                fVar6 = fVar5;
                if (fVar7 <= 1e-05) {
                  fVar6 = 0.0;
                }
                if (fVar6 != 0.0) {
                  local_150 = local_150 + 1;
                  *(float *)(puVar17 + (*(int *)((int)this + 0x80) + iVar16) * 4) =
                       fVar9 * (fVar4 / fVar5) + PUN(float,puVar15[iVar14]);
                  iVar12 = *(int *)((int)this + 0x7c) + iVar16;
                  iVar16 = iVar16 + 3;
                  local_14c = local_14c + 0xc;
                  *(float *)(puVar17 + iVar12 * 4) =
                       fVar8 * (fVar4 / fVar5) + PUN(float,puVar15[*(int *)((int)this + 0x7c)]);
                }
                goto LAB_004a903f;
              }
            }
            else {
              fVar9 = PUN(float,puVar15[iVar14]) - *(float *)(local_148 + iVar12);
              fVar8 = PUN(float,puVar15[iVar1]) - *(float *)(local_148 + iVar20);
              fVar5 = -(fVar9 * fVar2) - fVar8 * fVar3;
              fVar7 = fVar5;
              if (fVar5 < 0.0) {
                fVar7 = -fVar5;
              }
              fVar6 = fVar5;
              if (fVar7 <= 1e-05) {
                fVar6 = 0.0;
              }
              if (fVar6 != 0.0) {
                local_150 = local_150 + 1;
                *(float *)(puVar17 + (*(int *)((int)this + 0x80) + iVar16) * 4) =
                     fVar9 * (fVar4 / fVar5) + PUN(float,puVar15[iVar14]);
                iVar12 = *(int *)((int)this + 0x7c) + iVar16;
                iVar16 = iVar16 + 3;
                local_14c = local_14c + 0xc;
                *(float *)(puVar17 + iVar12 * 4) =
                     fVar8 * (fVar4 / fVar5) + PUN(float,puVar15[*(int *)((int)this + 0x7c)]);
              }
            }
          }
          else {
LAB_004a903f:
            iVar16 = iVar16 + 3;
            *(undefined4 *)local_14c = *puVar15;
            *(undefined4 *)(local_14c + 4) = puVar15[1];
            local_150 = local_150 + 1;
            *(undefined4 *)(local_14c + 8) = puVar15[2];
            local_14c = local_14c + 0xc;
          }
          local_144 = local_144 - 1;
          puVar10 = puVar15 + 3;
          local_148 = (uint)puVar15;
          local_138 = fVar4;
        } while (local_144 != 0);
      }
      if ((int)local_150 < 2) {
        return 0;
      }
      local_128 = local_128 + 1;
      local_12c = local_12c + 4;
      count = local_150;
      puVar11 = (undefined1 *)local_140;
      iVar21 = iVar18;
      local_140 = (uint)puVar17;
    } while ((int)local_128 < *(int *)((int)this + 0x34));
  }
  if (0 < count) {
    iVar21 = local_140 - (int)out;
    do {
      pfVar19 = (float *)(iVar21 + (int)out);
      *out = *pfVar19;
      out[1] = pfVar19[1];
      out[2] = pfVar19[2];
      Sector_FixPlaneCoordinate(this,(int)out);
      out = out + 3;
      count = count - 1;
    } while (count != 0);
  }
  return local_150;
}
#undef local_118
#undef local_11c
#undef local_120
#undef local_124
#undef local_128
#undef local_12c
#undef local_130
#undef local_134
#undef local_138
#undef local_13c
#undef local_140
#undef local_144
#undef local_148
#undef local_14c
#undef local_150
#undef local_7c
#undef local_80
#undef local_84
#undef local_90


/* ---- 0x004a9070  Sector_EdgeDistance ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Source: Engine/WalkPlane.cpp (line 1736, from __FILE__/__LINE__ passed to the allocator) */

float __thiscall Sector_EdgeDistance(void *this,int edge,float *point)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  float10 extraout_ST0;
  float fVar3;
  #define fStack_38 (*(float *)(_frame + (0x50 - 0x38)))
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
  
  if (*(int *)((int)this + 0x34) <= edge) {
    (*g_pStd_HS->pAssertFail)
              (s_edge_index___num_verts_004ec9b8,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,0x6c8);
  }
  iVar1 = *(int *)((int)this + edge * 4 + 0x38);
  iVar2 = *(int *)((int)this + ((edge + 1) % *(int *)((int)this + 0x34)) * 4 + 0x38);
  local_30 = *(float *)(iVar2 + 4) - *(float *)(iVar1 + 4);
  fStack_2c = *(float *)(iVar2 + 8) - *(float *)(iVar1 + 8);
  fStack_28 = *(float *)(iVar2 + 0xc) - *(float *)(iVar1 + 0xc);
  fStack_24 = *point - *(float *)(iVar1 + 4);
  fStack_20 = point[1] - *(float *)(iVar1 + 8);
  fStack_1c = point[2] - *(float *)(iVar1 + 0xc);
  Vec3_NormalizeTo(&local_c,&local_30);
  Vec3_NormalizeTo(&fStack_18,&fStack_24);
  fVar3 = stdMath_ArcSin3(fStack_10 * fStack_4 + fStack_14 * fStack_8 + fStack_18 * local_c);
  stdMath_SinCos(90.0 - fVar3,&fStack_38,auStack_34);
  return fStack_38 * (float)extraout_ST0;
}
#undef auStack_34
#undef fStack_10
#undef fStack_14
#undef fStack_18
#undef fStack_1c
#undef fStack_20
#undef fStack_24
#undef fStack_28
#undef fStack_2c
#undef fStack_38
#undef fStack_4
#undef fStack_8
#undef local_30
#undef local_c

#endif


/* ---- 0x004a9180  Sector_CollapseShortestEdge ---- */
/* Sector_CollapseShortestEdge: for a sector of 4 or more vertices, finds the shortest edge a -
   (a+1) and replaces its two ends by the point where the line of the edge before it (a-1 -> a)
   meets the line of the edge after it ((a+1) -> (a+2)), computed on the two dominant axes (+0x7c,
   +0x80) with Sector_FixPlaneCoordinate for the third; fails (0) when those lines are parallel
   (|cross| <= 1e-5). The new vertex goes through SectorVertexPool_GetOrAdd. */

undefined4 __fastcall Sector_CollapseShortestEdge(void *param_1)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
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
  uint *puVar11;
  int iVar12;
  uint *puVar13;
  int iVar14;
  int iVar15;
  int *piVar16;
  int iVar17;
  #define local_54 (*(uint *)(_frame + (0x70 - 0x54)))
  #define local_50 (*(float *)(_frame + (0x70 - 0x50)))
  #define local_4c (*(uint *)(_frame + (0x70 - 0x4c)))
  #define local_48 (*(uint *)(_frame + (0x70 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x70 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x70 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x70 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x70 - 0x38)))
  #define local_34 (*(float *)(_frame + (0x70 - 0x34)))
  #define local_30 (*(float *)(_frame + (0x70 - 0x30)))
  #define local_28 (*(uint *)(_frame + (0x70 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x70 - 0x24)))
  
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
    iVar15 = *(int *)((int)param_1 + ((int)(iVar12 + -1 + local_4c) % iVar12) * 4 + 0x38) + 4;
    iVar9 = *(int *)((int)param_1 + ((int)(local_4c + 1) % iVar12) * 4 + 0x38) + 4;
    iVar14 = local_4c + 2;
    iVar12 = *(int *)((int)param_1 + (iVar14 % iVar12) * 4 + 0x38);
    local_40 = *(uint *)(iVar12 + 4);
    local_3c = *(uint *)(iVar12 + 8);
    iVar10 = *(int *)((int)param_1 + 0x7c) * 4;
    local_38 = *(uint *)(iVar12 + 0xc);
    iVar12 = *(int *)((int)param_1 + 0x80) * 4;
    local_34 = -(*(float *)(iVar17 + iVar10) - *(float *)(iVar15 + iVar10));
    local_30 = *(float *)(iVar17 + iVar12) - *(float *)(iVar15 + iVar12);
    pfVar8 = (float *)(&local_40 + *(int *)((int)param_1 + 0x7c));
    pfVar1 = (float *)(&local_40 + *(int *)((int)param_1 + 0x80));
    fVar2 = (*pfVar1 - *(float *)(iVar15 + iVar12)) * local_34 +
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
      fVar4 = -(fVar3 * local_34) - fVar7 * local_30;
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
        Sector_FixPlaneCoordinate(param_1,(int)&local_40);
        local_28 = SectorVertexPool_GetOrAdd(0,&local_40);
        iVar9 = *(int *)((int)param_1 + 0x34);
        iVar12 = iVar9 + -2;
        if (0 < iVar12) {
          puVar13 = &local_24;
          do {
            iVar10 = iVar14 % iVar9;
            iVar14 = iVar14 + 1;
            iVar12 = iVar12 + -1;
            *puVar13 = *(uint *)((int)param_1 + iVar10 * 4 + 0x38);
            puVar13 = puVar13 + 1;
          } while (iVar12 != 0);
        }
        SectorVertexPool_Release(*(undefined4 *)((int)param_1 + local_4c * 4 + 0x38));
        SectorVertexPool_Release
                  (*(undefined4 *)
                    ((int)param_1 + ((int)(local_4c + 1) % *(int *)((int)param_1 + 0x34)) * 4 + 0x38
                    ));
        iVar14 = *(int *)((int)param_1 + 0x34) + -1;
        iVar12 = 0;
        *(int *)((int)param_1 + 0x34) = iVar14;
        if (0 < iVar14) {
          puVar11 = &local_28;
          puVar13 = (uint *)((int)param_1 + 0x38);
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
#undef local_24
#undef local_28
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_44
#undef local_48
#undef local_4c
#undef local_50
#undef local_54


/* ---- 0x004a9d00  ShrinkBoxes ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Variable defined which should be unmapped: local_18 */
/* WARNING: Variable defined which should be unmapped: local_4 */
/* SectorList_ShrinkWalkSectors(radius), called by Lua ShrinkBoxes after SectorList_SaveForShrink.
   For every active walk sector (type & 0x1000, flag +0x28): for each vertex take the bisector of
   the directions to its neighbours, move it inward by radius / sin(half angle) (Math_SinCosTable,
   Math_AsinDegreesSeries); the move is valid when the new point is inside the sector
   (Sector_ContainsPoint) and at least radius - 0.001 from the line of every edge
   (Sector_EdgeDistance). Not valid: Sector_CollapseShortestEdge and retry; cannot collapse: the
   sector is switched off (+0x28 = 0). The shifts are summed per pool vertex (shared by the sectors)
   and the pool vertex moves by the mean, so all sectors that share it move together. Undone by
   SectorList_RestoreAfterShrink. Original name ShrinkBoxes (the remaster's GrimFandango (Linux):
   the only unmatched callee of Lua_TEST; 3 matched neighbours agree, 0 disagree); was
   SectorList_ShrinkWalkSectors. */

void __cdecl ShrinkBoxes(float radius)

{
  unsigned char _frame[0x30];  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  int *piVar10;
  void *this;
  float *pfVar11;
  undefined4 *puVar12;
  float fVar13;
  uint local_res0;
  int iStack0000000c;
  int iStack00000010;
  float in_stack_00000014;
  float in_stack_00000018;
  float in_stack_0000001c;
  float *pfStack00000020;
  float in_stack_00000024;
  float in_stack_00000028;
  float in_stack_0000002c;
  float in_stack_00000030;
  double in_stack_00000038;
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x30 - 0x4)))
  
  FUN_004addf0();
  if (0.0 <= radius) {
    puVar12 = (undefined4 *)&STACK0X(0x000010b8);
    for (iVar6 = 0xc00; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar12 = 0;
      puVar12 = puVar12 + 1;
    }
    puVar12 = (undefined4 *)&STACK0X(0x000000b8);
    for (iVar6 = 0x400; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar12 = 0;
      puVar12 = puVar12 + 1;
    }
    this = g_pWalkPlane_wp_head;
    if (g_pWalkPlane_wp_head != (void *)0x0) {
LAB_004a9d53:
      if (((*(uint *)((int)this + 0x24) & 0x1000) != 0) && (*(int *)((int)this + 0x28) != 0)) {
LAB_004a9d6a:
        iVar6 = *(int *)((int)this + 0x38);
        puVar12 = (undefined4 *)&STACK0X(0x00000040);
        for (iVar7 = 0x1e; iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar12 = 0;
          puVar12 = puVar12 + 1;
        }
        pfStack00000020 = (float *)&STACK0X(0x00000044);
        iStack0000000c = 0;
        pfVar8 = (float *)(*(int *)((int)this + *(int *)((int)this + 0x34) * 4 + 0x34) + 4);
        pfVar11 = (float *)(iVar6 + 4);
        do {
          if (*(int *)((int)this + 0x34) <= iStack0000000c) {
            iVar6 = *(int *)((int)this + 0x34);
            if (0 < iVar6) {
              piVar10 = (int *)((int)this + 0x38);
              pfVar8 = (float *)&STACK0X(0x00000044);
              do {
                iVar7 = *piVar10;
                piVar10 = piVar10 + 1;
                iVar7 = iVar7 - (int)IMG_ADDR(0x008cb0b0) >> 4;
                iVar9 = iVar7 * 0xc;
                *(float *)(&STACK0X(0x000010b8) + iVar9) =
                     pfVar8[-1] + *(float *)(&STACK0X(0x000010b8) + iVar9);
                *(float *)(&STACK0X(0x000010bc) + iVar9) =
                     *(float *)(&STACK0X(0x000010bc) + iVar9) + *pfVar8;
                *(float *)(&STACK0X(0x000010c0) + iVar9) =
                     pfVar8[1] + *(float *)(&STACK0X(0x000010c0) + iVar9);
                iVar6 = iVar6 + -1;
                *(int *)(&STACK0X(0x000000b8) + iVar7 * 4) = *(int *)(&STACK0X(0x000000b8) + iVar7 * 4) + 1;
                pfVar8 = pfVar8 + 3;
              } while (iVar6 != 0);
            }
            break;
          }
          iStack0000000c = iStack0000000c + 1;
          local_4 = *pfVar8 - *pfVar11;
          iVar6 = *(int *)((int)this + (iStack0000000c % *(int *)((int)this + 0x34)) * 4 + 0x38);
          fVar1 = pfVar8[1];
          fVar2 = pfVar11[1];
          fVar3 = pfVar8[2];
          fVar13 = pfVar11[2];
          rdVector_Normalize3Acc(&local_4);
          in_stack_00000014 = *(float *)(iVar6 + 4) - *pfVar11;
          in_stack_00000018 = *(float *)(iVar6 + 8) - pfVar11[1];
          in_stack_0000001c = *(float *)(iVar6 + 0xc) - pfVar11[2];
          rdVector_Normalize3Acc(&STACK0X(0x00000014));
          local_4 = in_stack_00000014 + local_4;
          fVar1 = in_stack_00000018 + (fVar1 - fVar2);
          fVar2 = in_stack_0000001c + (fVar3 - fVar13);
          rdVector_Normalize3Acc(&local_4);
          stdMath_ArcSin3(in_stack_0000001c * fVar2 +
                          in_stack_00000018 * fVar1 + in_stack_00000014 * local_4);
          ((code *)stdMath_SinCos)();
          fVar3 = fVar2 / in_stack_00000024;
          bVar4 = true;
          in_stack_00000028 = fVar3 * local_4 + *pfVar11;
          in_stack_0000002c = fVar3 * fVar1 + pfVar11[1];
          in_stack_00000030 = fVar3 * fVar2 + pfVar11[2];
          iVar7 = Sector_ContainsPoint(this,&STACK0X(0x00000028),1);
          if (iVar7 == 0) {
LAB_004a9f32:
            bVar4 = false;
          }
          else {
            iStack00000010 = 0;
            if (0 < *(int *)((int)this + 0x34)) {
              in_stack_00000038 = (double)(fVar2 - 0.001);
              do {
                fVar13 = Sector_EdgeDistance(this,iStack00000010,&STACK0X(0x00000028));
                if (fVar13 < (float)in_stack_00000038) goto LAB_004a9f32;
                iStack00000010 = iStack00000010 + 1;
              } while (iStack00000010 < *(int *)((int)this + 0x34));
            }
          }
          if (!bVar4) goto LAB_004a9f7e;
          pfStack00000020[-1] = fVar3 * local_4;
          *pfStack00000020 = fVar3 * fVar1;
          pfStack00000020[1] = fVar3 * fVar2;
          pfStack00000020 = pfStack00000020 + 3;
          pfVar8 = pfVar11;
          pfVar11 = (float *)(iVar6 + 4);
        } while( true );
      }
      goto LAB_004a9ffa;
    }
LAB_004aa005:
    piVar10 = (int *)&STACK0X(0x000000b8);
    puVar5 = &UINT_008cb0b8;
    pfVar8 = (float *)&STACK0X(0x000010bc);
    do {
      if (*piVar10 != 0) {
        fVar3 = 1.0 / (float)*piVar10;
        fVar1 = *pfVar8;
        fVar2 = pfVar8[1];
        puVar5[-1] = PUN(uint,(float)(pfVar8[-1] * fVar3 + (float)puVar5[-1]));
        *puVar5 = PUN(uint,(float)(fVar1 * fVar3 + (float)*puVar5));
        puVar5[1] = PUN(uint,(float)(fVar2 * fVar3 + (float)puVar5[1]));
      }
      puVar5 = puVar5 + 4;
      piVar10 = piVar10 + 1;
      pfVar8 = pfVar8 + 3;
    } while ((int)puVar5 < IMG_ADDR(0x008cf0b8));
  }
  return;
LAB_004a9f7e:
  iVar6 = Sector_CollapseShortestEdge(this);
  if (iVar6 == 0) goto code_r0x004a9f8d;
  goto LAB_004a9d6a;
code_r0x004a9f8d:
  *(undefined4 *)((int)this + 0x28) = 0;
LAB_004a9ffa:
  this = *(void **)((int)this + 0x70);
  if (this == (void *)0x0) goto LAB_004aa005;
  goto LAB_004a9d53;
}
#undef local_18
#undef local_4
#undef local_8

#endif

