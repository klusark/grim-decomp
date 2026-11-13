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
  WalkPlane *this;
  Puck *pPVar2;
  uint color;
  
  this = g_pWalkPlane_wp_head;
  do {
    if (this == (WalkPlane *)0x0) {
      return;
    }
    uVar1 = this->dwType;
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
    pPVar2 = g_dwPuck_p_head;
    if ((uVar1 & 0x8000) != 0) {
      color = (uint)PIECE(UINT_008c97c8,2,2);
    }
    for (; pPVar2 != (Puck *)0x0; pPVar2 = pPVar2->pNext) {
      if (this == pPVar2->pSector) {
        color = UINT_008c97e8 & 0xffff;
        break;
      }
    }
    WalkPlane_Draw(this,color);
    this = this->pNext;
  } while( true );
}

/* ---- 0x0049c750  sputLua_CollisionHandler ---- */
/* Tests a segment against a sector's edges, returning the entry/exit points Original name
   sputLua_CollisionHandler (the remaster's GrimFandango (Linux): strings: 'collisionHandler'); was
   Sector_IntersectSegment. */

void __cdecl sputLua_CollisionHandler(int self,int other,float *a,float *b,float *c)

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
      iVar4 = self;
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
    lua_pushusertag((char *)((self - (int)g_pActors) / 0xa8),0x52544341);
    lua_pushusertag((char *)((other - (int)g_pActors) / 0xa8),0x52544341);
    lua_pushnumber(*a);
    lua_pushnumber(a[1]);
    lua_pushnumber(a[2]);
    lua_pushnumber(*b);
    lua_pushnumber(b[1]);
    lua_pushnumber(b[2]);
    lua_pushnumber(*c);
    lua_pushnumber(c[1]);
    lua_pushnumber(c[2]);
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
   SetFile_Parse); was SetFile_ParseSections. */

undefined4 sputRoom_LoadRoomEntry(uint param_1)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  #define local_20 (*(char (*)[32])(_frame + (0x30 - 0x20)))
  
  iVar1 = ((code *)stdConffile_Open)(param_1);
  if (iVar1 == 0) {
    return 0;
  }
  uVar2 = stdConffile_ReadLine();
  if (uVar2 != 0) {
    do {
      iVar1 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ec740,local_20);
      if (iVar1 == 1) {
        iVar1 = Set_IsHandleValid(local_20);
        if (iVar1 == 0) {
          stdConffile_Close();
          return 0;
        }
      }
      uVar2 = stdConffile_ReadLine();
    } while (uVar2 != 0);
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
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  #define local_100 (*(char (*)[256])(_frame + (0x110 - 0x100)))
  
  uVar3 = g_dwLoadingRoom;
  piVar1 = (int *)(g_dwLoadingRoom + 0x80);
  if (*piVar1 != 0) {
    (*g_pSputRoomHS->pAssertFail)
              (s_pRoom__apColormaps____NULL_004ec88c,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,
               0x91d);
  }
  uVar4 = stdConffile_ReadLine();
  if (uVar4 == 0) {
    return 1;
  }
  do {
    if (*(char *)g_dwStdConffile_aLine != '\0') {
      local_100[0] = '\0';
      iVar5 = sscanf((char *)g_dwStdConffile_aLine,s_section___s_004ec7e0,local_100);
      if (iVar5 == 0) {
        piVar2 = (int *)(uVar3 + 0x84);
        iVar5 = sscanf((char *)g_dwStdConffile_aLine,s_numcolormaps__d_004ec878,piVar2);
        if (iVar5 == 1) {
          if (*piVar2 == 0) goto LAB_004a5c4e;
          puVar6 = (undefined4 *)
                   (*g_pSputRoomHS->pAlloc)
                             (*piVar2 * 0x34,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x935);
          iVar5 = *piVar2;
          *piVar1 = (int)puVar6;
          for (uVar4 = iVar5 * 0xd & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
            *puVar6 = 0;
            puVar6 = puVar6 + 1;
          }
          for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
            *(undefined1 *)puVar6 = 0;
            puVar6 = (undefined4 *)((int)puVar6 + 1);
          }
        }
        if (*piVar1 != 0) {
          sscanf((char *)g_dwStdConffile_aLine,s_colormap__s_004ec868,uVar3 + 0x8c);
        }
      }
      else {
        iVar5 = Set_IsHandleValid(local_100);
        if (iVar5 == 0) {
          return 0;
        }
      }
    }
LAB_004a5c4e:
    uVar4 = stdConffile_ReadLine();
    if (uVar4 == 0) {
      return 1;
    }
  } while( true );
}
#undef local_100


/* ---- 0x004a5c90  sputRoom_ParseSectors ---- */
/* Section handler 'sectors' registered by sputRoom_Start: runs ParseCollection for the set being
   parsed. Original name sputRoom_ParseSectors (the remaster's GrimFandango (Linux): the only
   unmatched caller of ParseCollection; 1 matched neighbours agree, 0 disagree); was
   SetFile_SectorsSectionHandler. */

undefined4 sputRoom_ParseSectors(void)

{
  char *pcVar1;
  
  pcVar1 = (char *)ParseCollection(g_dwLoadingRoom);
  if (pcVar1 != (char *)0x0) {
    Set_IsHandleValid(pcVar1);
  }
  return 1;
}

/* ---- 0x004a61c0  WalkPlane_BuildCache ---- */
/* Original name WalkPlane_BuildCache (the remaster's GrimFandango (Linux): the same cache of all
   planes and vertices before the shrink (count planes and vertices of wp_head, allocate and copy);
   the free at its start is WalkPlane::DestroyCache, inlined in the remaster); was
   SectorList_SaveForShrink. */

void WalkPlane_BuildCache(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  WalkVertex *pWVar2;
  WalkPlane *pWVar3;
  WalkVertex **ppWVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  WalkPlane_DestroyCache();
  g_nVertexCacheSize = 0;
  g_nWalkPlaneCacheSize = 0;
  for (pWVar3 = g_pWalkPlane_wp_head; pWVar3 != (WalkPlane *)0x0; pWVar3 = pWVar3->pNext) {
    g_nVertexCacheSize = g_nVertexCacheSize + pWVar3->nNumVerts;
    g_nWalkPlaneCacheSize = g_nWalkPlaneCacheSize + 1;
  }
  g_pVertexCache = Plat_Alloc(g_nVertexCacheSize * 0x14);
  local_4 = 0;
  for (pWVar3 = g_pWalkPlane_wp_head; pWVar3 != (WalkPlane *)0x0; pWVar3 = pWVar3->pNext) {
    iVar5 = 0;
    if (0 < pWVar3->nNumVerts) {
      iVar7 = local_4 * 0x14;
      ppWVar4 = pWVar3->aVerts;
      do {
        pWVar2 = *ppWVar4;
        piVar1 = (int *)((int)(g_pVertexCache->vert).aPos + iVar7 + -4);
        *piVar1 = pWVar2->nRefs;
        piVar1[1] = PUN(int,(float)pWVar2->aPos[0]);
        piVar1[2] = PUN(int,(float)pWVar2->aPos[1]);
        piVar1[3] = PUN(int,(float)pWVar2->aPos[2]);
        *(int *)((int)(g_pVertexCache->vert).aPos + iVar7 + -8) = (int)((WalkVertex *)((char *)*ppWVar4 - ((unsigned)(uintptr_t)&g_aWalkPlane_vert_db))) >> 4;
        local_4 = local_4 + 1;
        iVar5 = iVar5 + 1;
        iVar7 = iVar7 + 0x14;
        ppWVar4 = ppWVar4 + 1;
      } while (iVar5 < pWVar3->nNumVerts);
    }
  }
  g_pWalkPlaneCache = Plat_Alloc(g_nWalkPlaneCacheSize * 0x34);
  if (g_pWalkPlane_wp_head != (WalkPlane *)0x0) {
    iVar5 = 0;
    pWVar3 = g_pWalkPlane_wp_head;
    do {
      iVar7 = 0;
      *(WalkPlane **)((int)g_pWalkPlaneCache->aVertIdx + iVar5 + -8) = pWVar3;
      *(int *)((int)g_pWalkPlaneCache->aVertIdx + iVar5 + -4) = pWVar3->nNumVerts;
      *(int *)((int)g_pWalkPlaneCache->aVertIdx + iVar5 + 0x28) = pWVar3->nVisible;
      if (0 < pWVar3->nNumVerts) {
        iVar6 = iVar5 + 8;
        ppWVar4 = pWVar3->aVerts;
        do {
          pWVar2 = *ppWVar4;
          ppWVar4 = ppWVar4 + 1;
          *(int *)((int)g_pWalkPlaneCache->aVertIdx + iVar6 + -8) = (int)((WalkVertex *)((char *)pWVar2 - ((unsigned)(uintptr_t)&g_aWalkPlane_vert_db))) >> 4;
          iVar7 = iVar7 + 1;
          iVar6 = iVar6 + 4;
        } while (iVar7 < pWVar3->nNumVerts);
      }
      pWVar3 = pWVar3->pNext;
      iVar5 = iVar5 + 0x34;
    } while (pWVar3 != (WalkPlane *)0x0);
  }
  g_dwWpCacheBuilt = 1;
  return;
}
#undef local_4


/* ---- 0x004a6330  WalkPlane_DestroyCache ---- */
/* Original name WalkPlane_DestroyCache (the remaster's GrimFandango (Linux): same body (clear the
   cache-built flag, free the vertex and plane caches, zero both sizes)); was
   SectorList_FreeShrinkSave. */

void WalkPlane_DestroyCache(void)

{
  g_dwWpCacheBuilt = 0;
  if (g_pVertexCache != (WalkVertexCache *)0x0) {
    Plat_Free(g_pVertexCache);
  }
  if (g_pWalkPlaneCache != (WalkPlaneCache *)0x0) {
    Plat_Free(g_pWalkPlaneCache);
  }
  g_pVertexCache = (WalkVertexCache *)0x0;
  g_pWalkPlaneCache = (WalkPlaneCache *)0x0;
  g_nWalkPlaneCacheSize = 0;
  g_nVertexCacheSize = 0;
  return;
}

/* ---- 0x004a6380  WalkPlane_RestoreCache ---- */
/* Original name WalkPlane_RestoreCache (the remaster's GrimFandango (Linux): same body (if the
   cache is built: release the planes' vertices, copy the cached planes and vertices back)); was
   SectorList_RestoreAfterShrink. */

void WalkPlane_RestoreCache(void)

{
  int iVar1;
  WalkPlane *pWVar2;
  WalkVertexCache *pWVar3;
  WalkVertex *pWVar4;
  int iVar5;
  int iVar6;
  WalkVertex **ppWVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  
  pWVar2 = g_pWalkPlane_wp_head;
  pWVar3 = g_pVertexCache;
  iVar9 = g_nVertexCacheSize;
  if (g_dwWpCacheBuilt != 0) {
    for (; g_nVertexCacheSize = iVar9, g_pVertexCache = pWVar3, pWVar2 != (WalkPlane *)0x0;
        pWVar2 = pWVar2->pNext) {
      iVar9 = 0;
      if (0 < pWVar2->nNumVerts) {
        ppWVar7 = pWVar2->aVerts;
        do {
          WalkPlane_RemoveVertex(*ppWVar7);
          iVar9 = iVar9 + 1;
          ppWVar7 = ppWVar7 + 1;
        } while (iVar9 < pWVar2->nNumVerts);
      }
      pWVar3 = g_pVertexCache;
      iVar9 = g_nVertexCacheSize;
    }
    if (0 < iVar9) {
      do {
        iVar10 = pWVar3->nIndex;
        iVar9 = iVar9 + -1;
        g_aWalkPlane_vert_db[iVar10].nRefs = (pWVar3->vert).nRefs;
        g_aWalkPlane_vert_db[iVar10].aPos[0] = (pWVar3->vert).aPos[0];
        g_aWalkPlane_vert_db[iVar10].aPos[1] = (pWVar3->vert).aPos[1];
        g_aWalkPlane_vert_db[iVar10].aPos[2] = (pWVar3->vert).aPos[2];
        pWVar3 = pWVar3 + 1;
      } while (iVar9 != 0);
    }
    iVar9 = 0;
    if (0 < g_nWalkPlaneCacheSize) {
      iVar10 = 0;
      do {
        iVar1 = *(int *)((int)g_pWalkPlaneCache->aVertIdx + iVar10 + -8);
        iVar6 = *(int *)((int)g_pWalkPlaneCache->aVertIdx + iVar10 + -4);
        iVar5 = 0;
        *(int *)(iVar1 + 0x34) = iVar6;
        if (0 < iVar6) {
          iVar6 = iVar10 + 8;
          puVar8 = (undefined4 *)(iVar1 + 0x38);
          do {
            iVar5 = iVar5 + 1;
            *puVar8 = g_aWalkPlane_vert_db + *(int *)((int)g_pWalkPlaneCache->aVertIdx + iVar6 + -8)
            ;
            iVar6 = iVar6 + 4;
            puVar8 = puVar8 + 1;
          } while (iVar5 < *(int *)(iVar1 + 0x34));
        }
        iVar9 = iVar9 + 1;
        iVar6 = iVar10 + 0x28;
        iVar10 = iVar10 + 0x34;
        *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)((int)g_pWalkPlaneCache->aVertIdx + iVar6);
      } while (iVar9 < g_nWalkPlaneCacheSize);
    }
    g_dwWalkPlane_tot_verts = 0;
    pWVar4 = g_aWalkPlane_vert_db;
    do {
      if (0 < pWVar4->nRefs) {
        g_dwWalkPlane_tot_verts = g_dwWalkPlane_tot_verts + 1;
      }
      pWVar4 = pWVar4 + 1;
    } while ((int)pWVar4 < ((unsigned)(uintptr_t)&g_dwWorkingPath));
  }
  return;
}

/* ---- 0x004a6490  WalkPlane_Construct ---- */
/* Sector_Construct(sector, vertices, count, group name): vertices go through
   SectorVertexPool_GetOrAdd (welded to an earlier vertex closer than 1e-4); Newell normal
   (+0x60..+0x68) normalized with Vec3_Normalize; the two axes (+0x7c, +0x80) are chosen by the
   largest component compared as it is (not abs): x -> (2,1), y -> (0,2), else (1,0). Default height
   +0x30 = 0.005. The sector is pushed on the head of its group's chain (+0x70 next) and
   DAT_008cf280 = newest: searches start with the last sector that was loaded. Original name
   WalkPlane_Construct (the remaster's GrimFandango (Linux): WalkPlane.cpp constructor (vertices,
   count, name): the same field initialisation (+0x28 / +0x2c = 1, +0x30 = 0.005f, the vertices
   through the vertex database) as the remaster's first WalkPlane::WalkPlane; its second one is a
   copy constructor v1.01 does not have); was Sector_Construct. */

WalkPlane * __thiscall WalkPlane_Construct(WalkPlane *this,int a1,int a2,int a3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *pfVar1;
  float fVar2;
  char cVar3;
  byte bVar4;
  WalkVertex *pWVar5;
  WalkVertex *pWVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  byte *pbVar11;
  char *pcVar12;
  WalkVertex **ppWVar13;
  WalkVertex **ppWVar14;
  byte *pbVar15;
  byte *pbVar16;
  char *pcVar17;
  bool bVar18;
  #define local_2 (*(undefined1 (*)[2])(_frame + (0x20 - 0x2)))
  
  if (a3 == 0) {
    a3 = (int)local_2;
  }
  ppWVar14 = this->aVerts;
  this->nVisible = 1;
  this->nActive = 1;
  this->pNext = (WalkPlane *)0x0;
  this->pPrev = (WalkPlane *)0x0;
  this->nId = 0;
  this->dwType = 0;
  this->nNumVerts = a2;
  this->aName[0] = '\0';
  this->flHeight = 0.005;
  ppWVar13 = ppWVar14;
  for (iVar8 = 10; iVar8 != 0; iVar8 = iVar8 + -1) {
    *ppWVar13 = (WalkVertex *)0x0;
    ppWVar13 = ppWVar13 + 1;
  }
  if (0 < a2) {
    do {
      pWVar6 = (WalkVertex *)WalkPlane_AddVertex(this,a1);
      *ppWVar14 = pWVar6;
      ppWVar14 = ppWVar14 + 1;
      a1 = a1 + 0xc;
      a2 = a2 + -1;
    } while (a2 != 0);
  }
  pfVar1 = this->aNormal;
  *pfVar1 = 0.0;
  this->aNormal[1] = 0.0;
  this->aNormal[2] = 0.0;
  a1 = this->nNumVerts;
  if (0 < a1) {
    a2 = (int)this->aVerts;
    pWVar6 = this->aVerts[a1 + -1];
    do {
      pWVar5 = *(WalkVertex **)a2;
      a2 = a2 + 4;
      a1 = a1 + -1;
      *pfVar1 = (pWVar6->aPos[1] - pWVar5->aPos[1]) * (pWVar6->aPos[2] + pWVar5->aPos[2]) + *pfVar1;
      this->aNormal[1] =
           (pWVar6->aPos[2] - pWVar5->aPos[2]) * (pWVar5->aPos[0] + pWVar6->aPos[0]) +
           this->aNormal[1];
      this->aNormal[2] =
           (pWVar6->aPos[1] + pWVar5->aPos[1]) * (pWVar6->aPos[0] - pWVar5->aPos[0]) +
           this->aNormal[2];
      pWVar6 = pWVar5;
    } while (a1 != 0);
  }
  pfVar1 = this->aNormal;
  rdVector_Normalize3Acc(pfVar1);
  if (*pfVar1 <= this->aNormal[1]) {
    fVar2 = this->aNormal[1];
  }
  else {
    fVar2 = *pfVar1;
  }
  if (fVar2 <= this->aNormal[2]) {
    fVar2 = this->aNormal[2];
  }
  else if (*pfVar1 <= this->aNormal[1]) {
    fVar2 = this->aNormal[1];
  }
  else {
    fVar2 = *pfVar1;
  }
  if (fVar2 == *pfVar1) {
    this->nAxisU = 2;
    this->nAxisV = 1;
  }
  else if (fVar2 == this->aNormal[1]) {
    this->nAxisU = 0;
    this->nAxisV = 2;
  }
  else {
    this->nAxisU = 1;
    this->nAxisV = 0;
  }
  iVar8 = 0;
  pbVar15 = &DAT_008cf28c;
  pbVar11 = (byte *)a3;
  pbVar16 = pbVar15;
LAB_004a6636:
  do {
    bVar4 = *pbVar15;
    bVar18 = bVar4 < *pbVar11;
    if (bVar4 == *pbVar11) {
      if (bVar4 != 0) {
        bVar4 = pbVar15[1];
        bVar18 = bVar4 < pbVar11[1];
        if (bVar4 != pbVar11[1]) goto LAB_004a665a;
        pbVar15 = pbVar15 + 2;
        pbVar11 = pbVar11 + 2;
        if (bVar4 != 0) goto LAB_004a6636;
      }
      iVar7 = 0;
    }
    else {
LAB_004a665a:
      iVar7 = (1 - (uint)bVar18) - (uint)(bVar18 != 0);
    }
    if ((iVar7 == 0) || (*pbVar16 == 0)) {
      if ((&DAT_008cf28c)[iVar8 * 0x28] == '\0') {
        uVar9 = 0xffffffff;
        goto code_r0x004a6694;
      }
      break;
    }
    pbVar15 = pbVar16 + 0x28;
    iVar8 = iVar8 + 1;
    pbVar11 = (byte *)a3;
    pbVar16 = pbVar15;
  } while ((int)pbVar15 < ((unsigned)(uintptr_t)&g_dwPuck_p_head));
  goto LAB_004a66ac;
  while( true ) {
    uVar9 = uVar9 - 1;
    pcVar12 = (char *)(a3 + 1);
    cVar3 = *(char *)a3;
    a3 = (int)pcVar12;
    if (cVar3 == '\0') break;
code_r0x004a6694:
    pcVar12 = (char *)a3;
    if (uVar9 == 0) break;
  }
  uVar9 = ~uVar9;
  pcVar12 = pcVar12 + -uVar9;
  pcVar17 = &DAT_008cf28c + iVar8 * 0x28;
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar12;
    pcVar12 = pcVar12 + 4;
    pcVar17 = pcVar17 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar17 = *pcVar12;
    pcVar12 = pcVar12 + 1;
    pcVar17 = pcVar17 + 1;
  }
LAB_004a66ac:
  this->pNext = (WalkPlane *)(&g_dwWalkPlane_Collection)[iVar8 * 10];
  if ((&g_dwWalkPlane_Collection)[iVar8 * 10] != 0) {
    *(WalkPlane **)((&g_dwWalkPlane_Collection)[iVar8 * 10] + 0x6c) = this;
  }
  (&g_dwWalkPlane_Collection)[iVar8 * 10] = (uint)this;
  g_pWalkPlane_wp_head = this;
  return this;
}
#undef local_2


/* ---- 0x004a66e0  WalkPlane_Destruct ---- */
/* __fastcall: unlinks a sector from g_pWalkPlane_wp_head and the per-type sector lists and releases
   its vertex pool entries. Original name WalkPlane_Destruct (the remaster's GrimFandango (Linux):
   same body (unlink from wp_head and the Collection lists, release the vertices, unlink from the
   neighbours)); was Sector_Unlink. */

void __fastcall WalkPlane_Destruct(WalkPlane *plane)

{
  uint *puVar1;
  int iVar2;
  WalkVertex **ppWVar3;
  
  if (plane == g_pWalkPlane_wp_head) {
    g_pWalkPlane_wp_head = plane->pNext;
  }
  iVar2 = 0;
  puVar1 = &g_dwWalkPlane_Collection;
  do {
    if ((WalkPlane *)*puVar1 == plane) {
      (&g_dwWalkPlane_Collection)[iVar2 * 10] = (uint)plane->pNext;
      break;
    }
    puVar1 = puVar1 + 10;
    iVar2 = iVar2 + 1;
  } while ((int)puVar1 < ((unsigned)(uintptr_t)&g_dwWpCacheBuilt));
  iVar2 = 0;
  if (0 < plane->nNumVerts) {
    ppWVar3 = plane->aVerts;
    do {
      WalkPlane_RemoveVertex(*ppWVar3);
      iVar2 = iVar2 + 1;
      ppWVar3 = ppWVar3 + 1;
    } while (iVar2 < plane->nNumVerts);
  }
  if (plane->pPrev != (WalkPlane *)0x0) {
    plane->pPrev->pNext = plane->pNext;
  }
  if (plane->pNext != (WalkPlane *)0x0) {
    plane->pNext->pPrev = plane->pPrev;
  }
  return;
}

/* ---- 0x004a6760  WalkPlane_SetName ---- */
/* Original name WalkPlane_SetName (the remaster's GrimFandango (Linux): same body (strcpy of a
   non-null name into the record)); was Sector_SetName. */

void __thiscall WalkPlane_SetName(WalkPlane *this,char *name)

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
      *(undefined4 *)this->aName = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      this = (WalkPlane *)(this->aName + 4);
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      this->aName[0] = *pcVar4;
      pcVar4 = pcVar4 + 1;
      this = (WalkPlane *)(this->aName + 1);
    }
  }
  return;
}

/* ---- 0x004a6790  WalkPlane_SetType ---- */
/* Stores the type bits (+0x24); 0x1000 sets a small shrink tolerance, 0x100 (edge sector) needs 4
   vertices and picks the long axis (+0x78) Original name WalkPlane_SetType (the remaster's
   GrimFandango (Linux): same body (type at +0x24, the 0.005f / 9999 tolerance by bit 0x1000, the
   0x100 case for 4-vertex planes)); was Sector_SetSavedType. */

void __thiscall WalkPlane_SetType(WalkPlane *this,uint type)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  WalkVertex *pWVar1;
  WalkVertex *pWVar2;
  WalkVertex *pWVar3;
  WalkVertex *pWVar4;
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
  
  this->dwType = type;
  this->flHeight = 9999.0;
  if ((type & 0x1000) != 0) {
    this->flHeight = 0.005;
  }
  if ((type & 0x100) != 0) {
    if (this->nNumVerts != 4) {
      this->dwType = 0x1000;
      return;
    }
    pWVar1 = this->aVerts[1];
    pWVar2 = this->aVerts[0];
    pWVar3 = this->aVerts[3];
    pWVar4 = this->aVerts[2];
    local_c = pWVar1->aPos[0] - pWVar2->aPos[0];
    local_8 = pWVar1->aPos[1] - pWVar2->aPos[1];
    local_4 = pWVar1->aPos[2] - pWVar2->aPos[2];
    local_18 = pWVar3->aPos[0] - pWVar4->aPos[0];
    local_14 = pWVar3->aPos[1] - pWVar4->aPos[1];
    local_10 = pWVar3->aPos[2] - pWVar4->aPos[2];
    fVar7 = rdVector_Normalize3Acc(&local_c);
    fVar8 = rdVector_Normalize3Acc(&local_18);
    fVar5 = local_10 * local_4 + local_14 * local_8 + local_18 * local_c;
    if (fVar5 < 0.0) {
      fVar5 = -fVar5;
    }
    pWVar1 = this->aVerts[2];
    pWVar2 = this->aVerts[1];
    local_c = pWVar1->aPos[0] - pWVar2->aPos[0];
    pWVar3 = this->aVerts[0];
    pWVar4 = this->aVerts[3];
    local_8 = pWVar1->aPos[1] - pWVar2->aPos[1];
    local_4 = pWVar1->aPos[2] - pWVar2->aPos[2];
    local_18 = pWVar3->aPos[0] - pWVar4->aPos[0];
    local_14 = pWVar3->aPos[1] - pWVar4->aPos[1];
    local_10 = pWVar3->aPos[2] - pWVar4->aPos[2];
    fVar9 = rdVector_Normalize3Acc(&local_c);
    fVar10 = rdVector_Normalize3Acc(&local_18);
    fVar6 = local_10 * local_4 + local_14 * local_8 + local_18 * local_c;
    if (fVar6 < 0.0) {
      fVar6 = -fVar6;
    }
    if (fVar6 < fVar5) {
      if (fVar7 < fVar8) {
        this->nLongEdge = 0;
        return;
      }
      this->nLongEdge = 2;
      return;
    }
    if (fVar9 < fVar10) {
      this->nLongEdge = 1;
      return;
    }
    this->nLongEdge = 3;
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


/* ---- 0x004a6980  WalkPlane_Within ---- */
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
   Original name WalkPlane_Within (the remaster's GrimFandango (Linux): same body (optional active /
   visible check, the plane distance test against the first vertex, then the edge tests)); was
   Sector_ContainsPoint. */

int __thiscall WalkPlane_Within(WalkPlane *this,float *point,int checkActive)

{
  WalkVertex *pWVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  float *pfVar9;
  int iVar10;
  WalkVertex **ppWVar11;
  
  if (checkActive != 0) {
    if (this->nActive == 0) {
      return 0;
    }
    if (this->nVisible == 0) {
      return 0;
    }
  }
  pWVar1 = this->aVerts[1];
  fVar5 = (point[1] - pWVar1->aPos[1]) * this->aNormal[1] +
          (point[2] - pWVar1->aPos[2]) * this->aNormal[2] +
          (*point - pWVar1->aPos[0]) * this->aNormal[0];
  fVar6 = fVar5;
  if (fVar5 < 0.0) {
    fVar6 = -fVar5;
  }
  fVar7 = fVar5;
  if (fVar6 <= 1e-05) {
    fVar7 = 0.0;
  }
  if (0.0 <= fVar7) {
    fVar6 = fVar5;
    if (fVar5 < 0.0) {
      fVar6 = -fVar5;
    }
    if (fVar6 <= 1e-05) {
      fVar5 = 0.0;
    }
  }
  else {
    fVar6 = fVar5;
    if (fVar5 < 0.0) {
      fVar6 = -fVar5;
    }
    if (fVar6 <= 1e-05) {
      fVar5 = 0.0;
    }
    fVar5 = -fVar5;
  }
  if (fVar5 <= this->flHeight) {
    iVar2 = this->nNumVerts;
    iVar10 = 0;
    if (iVar2 < 1) {
      return 1;
    }
    iVar3 = this->nAxisV;
    iVar4 = this->nAxisU;
    ppWVar11 = this->aVerts;
    pfVar8 = this->aVerts[iVar2 + -1]->aPos;
    while( true ) {
      pfVar9 = (*ppWVar11)->aPos;
      fVar5 = ((point[iVar4] - pfVar8[iVar4]) * (pfVar9[iVar3] - pfVar8[iVar3]) +
              (point[iVar3] - pfVar8[iVar3]) * -(pfVar9[iVar4] - pfVar8[iVar4])) - -1e-05;
      fVar6 = fVar5;
      if (fVar5 < 0.0) {
        fVar6 = -fVar5;
      }
      if (fVar6 <= 1e-05) {
        fVar5 = 0.0;
      }
      if (fVar5 < 0.0) break;
      iVar10 = iVar10 + 1;
      ppWVar11 = ppWVar11 + 1;
      pfVar8 = pfVar9;
      if (iVar2 <= iVar10) {
        return 1;
      }
    }
    return 0;
  }
  return 0;
}
#endif


/* ---- 0x004a6b30  WalkPlane_ClosestPoint ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Original name WalkPlane_ClosestPoint (the remaster's GrimFandango (Linux): same body (projects
   the point onto the plane, then clamps it to the nearest edge); the remaster inlined Project at
   its start); was Sector_ClampPoint. */

int __thiscall WalkPlane_ClosestPoint(WalkPlane *this,int a1)

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
  
  WalkPlane_Project(this,a1);
  iVar7 = this->nNumVerts;
  iVar9 = 0;
  if (0 < iVar7) {
    local_10 = (uint)this->aVerts;
    pfVar8 = this->aVerts[iVar7 + -1]->aPos;
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
          if ((iVar9 != this->nNumVerts + -1) || (fVar2 <= 1.0)) {
            if (0.0 <= fVar2) {
              WalkPlane_Project(this,a1);
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
      iVar7 = this->nNumVerts;
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

float __thiscall WalkPlane_Intersection(WalkPlane *this,int a1,int a2,int a3)

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
  this->nHitEdge = -1;
  iVar8 = WalkPlane_Within(this,(float *)a2,1);
  if (iVar8 == 0) {
    local_28 = 0;
    *(undefined4 *)a3 = *(undefined4 *)a2;
    *(undefined4 *)(a3 + 4) = *(undefined4 *)(a2 + 4);
    *(undefined4 *)(a3 + 8) = *(undefined4 *)(a2 + 8);
    if (0 < this->nNumVerts) {
      local_24 = (uint)this->aVerts;
      pfVar10 = this->aVerts[this->nNumVerts + -1]->aPos;
      do {
        iVar8 = this->nAxisU;
        iVar1 = this->nAxisV;
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
            *(float *)(a3 + this->nAxisU * 4) =
                 fVar7 * (fVar13 / fVar6) + *(float *)(a3 + this->nAxisU * 4);
            local_c = *pfVar10 - *pfVar11;
            local_8 = pfVar10[1] - *(float *)(iVar2 + 8);
            local_4 = pfVar10[2] - *(float *)(iVar2 + 0xc);
            this->nHitEdge = local_28;
            local_1c = (uint)pfVar10;
          }
        }
        local_28 = local_28 + 1;
        local_24 = local_24 + 4;
        pfVar10 = pfVar11;
      } while ((int)local_28 < this->nNumVerts);
    }
    WalkPlane_Project(this,a3);
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

void __thiscall WalkPlane_SnapTo(WalkPlane *this,float *pos)

{
  WalkVertex *pWVar1;
  float fVar2;
  
  pWVar1 = this->aVerts[0];
  fVar2 = (pos[1] - pWVar1->aPos[1]) * this->aNormal[1] +
          (pos[2] - pWVar1->aPos[2]) * this->aNormal[2] +
          (*pos - pWVar1->aPos[0]) * this->aNormal[0];
  *pos = *pos - fVar2 * this->aNormal[0];
  pos[1] = pos[1] - fVar2 * this->aNormal[1];
  pos[2] = pos[2] - fVar2 * this->aNormal[2];
  return;
}

/* ---- 0x004a7000  WalkPlane_Project ---- */
/* Original name WalkPlane_Project (the remaster's GrimFandango (Linux): same body (solves the plane
   equation for the axis the two dominant-axis fields at +0x7c / +0x80 leave out)); was
   Sector_FixPlaneCoordinate. */

int __thiscall WalkPlane_Project(WalkPlane *this,int a1)

{
  WalkVertex *pWVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  pWVar1 = this->aVerts[0];
  iVar2 = this->nAxisU;
  if ((iVar2 == 1) && (this->nAxisV == 0)) {
    iVar4 = 2;
  }
  else if (((iVar2 != 0) || (iVar4 = 1, this->nAxisV != 2)) &&
          ((iVar4 = a1, iVar2 == 2 && (this->nAxisV == 1)))) {
    iVar4 = 0;
  }
  iVar3 = this->nAxisV;
  *(float *)(a1 + iVar4 * 4) =
       (this->aNormal[iVar2] * *(float *)(a1 + iVar2 * 4) +
        this->aNormal[iVar3] * *(float *)(a1 + iVar3 * 4) +
       -(this->aNormal[2] * pWVar1->aPos[2] +
        this->aNormal[0] * pWVar1->aPos[0] + this->aNormal[1] * pWVar1->aPos[1])) /
       -this->aNormal[iVar4];
  return iVar3;
}

/* ---- 0x004a70a0  WalkPlane_Draw ---- */
/* Original name WalkPlane_Draw (the remaster's GrimFandango (Linux): same body (if visible:
   rdPrimit3_DrawLine along every edge in the colour)); was Sector_DrawOutline. */

void __thiscall WalkPlane_Draw(WalkPlane *this,int color)

{
  WalkVertex *pWVar1;
  float *a;
  WalkVertex **ppWVar2;
  int iVar3;
  
  if (this->nVisible != 0) {
    iVar3 = 0;
    if (0 < this->nNumVerts) {
      ppWVar2 = this->aVerts;
      a = this->aVerts[this->nNumVerts + -1]->aPos;
      do {
        pWVar1 = *ppWVar2;
        rdPrimit3_DrawLine(a,pWVar1->aPos,(int *)0x0,(int *)0x0,(int *)0x0,(int *)0x0,color,
                           0xffffffff);
        iVar3 = iVar3 + 1;
        ppWVar2 = ppWVar2 + 1;
        a = pWVar1->aPos;
      } while (iVar3 < this->nNumVerts);
    }
  }
  return;
}

/* ---- 0x004a71e0  WalkPlane_PlaneAt ---- */
/* Original name WalkPlane_PlaneAt (the remaster's GrimFandango (Linux): same body (the first plane
   of wp_head with a type bit of the mask that contains the point)); was SectorList_FindByPoint. */

WalkPlane * __cdecl WalkPlane_PlaneAt(float *point,uint mask)

{
  WalkPlane **ppWVar1;
  int iVar2;
  WalkPlane *this;
  
  this = g_pWalkPlane_wp_head;
  if (g_pWalkPlane_wp_head == (WalkPlane *)0x0) {
    return (WalkPlane *)0x0;
  }
  while (((this->dwType & mask) == 0 ||
         (iVar2 = WalkPlane_Within(this,point,1), iVar2 == 0))) {
    ppWVar1 = &this->pNext;
    this = *ppWVar1;
    if (*ppWVar1 == (WalkPlane *)0x0) {
      return (WalkPlane *)0x0;
    }
  }
  return this;
}

/* ---- 0x004a7230  WalkPlane_PlaneNamed ---- */
/* Original name WalkPlane_PlaneNamed (the remaster's GrimFandango (Linux): WalkPlane::PlaneNamed in
   the remaster (a C++ method there); the only unmatched callee of Actor_SetShadowPlane; 7 matched
   neighbours agree, 0 disagree); was Sector_FindByName. */

WalkPlane * __cdecl WalkPlane_PlaneNamed(char *name)

{
  byte bVar1;
  WalkPlane *pWVar2;
  WalkPlane *pWVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  
  pWVar2 = g_pWalkPlane_wp_head;
  do {
    pWVar3 = pWVar2;
    pbVar5 = (byte *)name;
    if (pWVar2 == (WalkPlane *)0x0) {
      return (WalkPlane *)0x0;
    }
    do {
      bVar1 = pWVar3->aName[0];
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_004a726e:
        iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_004a7273;
      }
      if (bVar1 == 0) break;
      bVar1 = pWVar3->aName[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_004a726e;
      pWVar3 = (WalkPlane *)(pWVar3->aName + 2);
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_004a7273:
    if (iVar4 == 0) {
      return pWVar2;
    }
    pWVar2 = pWVar2->pNext;
  } while( true );
}

/* ---- 0x004a7290  WalkPlane_PlaneNumbered ---- */
/* Original name WalkPlane_PlaneNumbered (the remaster's GrimFandango (Linux): same body (the plane
   of wp_head whose number at +0x20 is the id)); was Sector_FindById. */

WalkPlane * __cdecl WalkPlane_PlaneNumbered(int id)

{
  WalkPlane *pWVar1;
  
  for (pWVar1 = g_pWalkPlane_wp_head; (pWVar1 != (WalkPlane *)0x0 && (pWVar1->nId != id));
      pWVar1 = pWVar1->pNext) {
  }
  return pWVar1;
}

/* ---- 0x004a72b0  WalkPlane_PlaneClosest ---- */
/* SectorList_FindNearestPoint(point, mask): the sector with the mask that contains the point
   (SectorList_FindByPoint), else the active sector whose Sector_ClampPoint of the point is nearest.
   Used by Lua GetShrinkPos, which then clamps the point in it (so (x, y) stay and only the height
   is made right when the point is inside). Original name WalkPlane_PlaneClosest (the remaster's
   GrimFandango (Linux): same body (the plane containing the point, else the plane whose clamped
   point is nearest; FLT_MAX start)); was SectorList_FindNearestPoint. */

WalkPlane * __cdecl WalkPlane_PlaneClosest(float *point,uint mask)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  WalkPlane *this;
  WalkPlane *pWVar2;
  WalkPlane *pWVar3;
  #define local_10 (*(float *)(_frame + (0x20 - 0x10)))
  #define local_c (*(float *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(float *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(float *)(_frame + (0x20 - 0x4)))
  
  local_10 = 3.4028235e+38;
  pWVar3 = WalkPlane_PlaneAt(point,mask);
  pWVar2 = (WalkPlane *)0x0;
  this = g_pWalkPlane_wp_head;
  if (pWVar3 == (WalkPlane *)0x0) {
    for (; pWVar3 = pWVar2, this != (WalkPlane *)0x0; this = this->pNext) {
      if ((((this->dwType & mask) != 0) && (this->nActive != 0)) && (this->nVisible != 0)) {
        local_c = *point;
        local_8 = point[1];
        local_4 = point[2];
        WalkPlane_ClosestPoint(this,(int)&local_c);
        fVar1 = (local_c - *point) * (local_c - *point) +
                (local_4 - point[2]) * (local_4 - point[2]) +
                (local_8 - point[1]) * (local_8 - point[1]);
        if (fVar1 < local_10) {
          pWVar3 = this;
          local_10 = fVar1;
        }
      }
      pWVar2 = pWVar3;
    }
  }
  return pWVar3;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x004a7390  WalkPlane_JumpOut ---- */
/* Original name WalkPlane_JumpOut (the remaster's GrimFandango (Linux): WalkPlane::JumpOut in the
   remaster (a C++ method there); the only unmatched callee of Actor_PushSectorOppositeEdge; 1
   matched neighbours agree, 1 disagree); was Sector_MoveWalkerToOppositeEdge. */

void __thiscall WalkPlane_JumpOut(WalkPlane *this,float *walker)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  WalkVertex *pWVar1;
  WalkVertex *pWVar2;
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
  
  if (this->nNumVerts == 4) {
    local_18 = *walker;
    local_14 = walker[1];
    local_10 = walker[2];
    local_24 = walker[6] * -10.0 + local_18;
    local_20 = walker[7] * -10.0 + local_14;
    local_1c = walker[8] * -10.0 + local_10;
    WalkPlane_Intersection(this,(int)&local_18,(int)&local_24,(int)&local_c);
    iVar7 = this->nHitEdge;
    if (iVar7 != -1) {
      pWVar1 = this->aVerts[iVar7];
      uVar6 = iVar7 - 1;
      if (0x7fffffff < uVar6) {
        uVar6 = this->nNumVerts - 1;
      }
      fVar3 = this->aVerts[uVar6]->aPos[0] - pWVar1->aPos[0];
      fVar5 = fVar3;
      if (fVar3 < 0.0) {
        fVar5 = -fVar3;
      }
      fVar4 = fVar3;
      if (fVar5 <= 1e-05) {
        fVar4 = 0.0;
      }
      if (fVar4 == 0.0) {
        fVar3 = (local_8 - pWVar1->aPos[1]) / (this->aVerts[uVar6]->aPos[1] - pWVar1->aPos[1]);
      }
      else {
        fVar3 = (local_c - pWVar1->aPos[0]) / fVar3;
      }
      fVar3 = 1.0 - fVar3;
      iVar7 = (iVar7 + 2) % this->nNumVerts;
      this->nHitEdge = iVar7;
      pWVar1 = this->aVerts[iVar7];
      uVar6 = iVar7 - 1;
      if (0x7fffffff < uVar6) {
        uVar6 = this->nNumVerts - 1;
      }
      pWVar2 = this->aVerts[uVar6];
      local_c = (pWVar2->aPos[0] - pWVar1->aPos[0]) * fVar3 + pWVar1->aPos[0];
      local_8 = (pWVar2->aPos[1] - pWVar1->aPos[1]) * fVar3 + pWVar1->aPos[1];
      local_4 = (pWVar2->aPos[2] - pWVar1->aPos[2]) * fVar3 + pWVar1->aPos[2];
      Puck_SetPos((Puck *)walker,&local_c);
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


/* ---- 0x004a7520  WalkPlane_GetConstraintVector ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* For a 4-vertex edge sector: direction along the edge the walker should follow (g_vEdgeFollowDir),
   stepping the current edge index when the walker reaches a corner Original name
   WalkPlane_GetConstraintVector (the remaster's GrimFandango (Linux): same body (the walker's
   position and the +0x40 turn sign as +-100 steps along the blocking edge)); was
   Sector_EdgeFollowDirection. */

float * __thiscall WalkPlane_GetConstraintVector(WalkPlane *this,float *walker)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  WalkVertex *pWVar2;
  int iVar3;
  WalkVertex *pWVar4;
  float fVar5;
  float fVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  float fVar13;
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
    fVar13 = 100.0;
  }
  else {
    fVar13 = -100.0;
  }
  if (walker[0x10] <= 0.0) {
    fVar5 = 100.0;
  }
  else {
    fVar5 = -100.0;
  }
  if (walker[0x10] <= 0.0) {
    fVar6 = 100.0;
  }
  else {
    fVar6 = -100.0;
  }
  local_30 = walker[6] * fVar13 + local_18;
  local_2c = walker[7] * fVar5 + local_14;
  local_28 = walker[8] * fVar6 + local_10;
  WalkPlane_Intersection(this,(int)&local_18,(int)&local_30,((unsigned)(uintptr_t)&g_vEdgeFollowDir));
  iVar1 = this->nHitEdge;
  if (iVar1 != -1) {
    pWVar2 = this->aVerts[iVar1];
    fVar6 = pWVar2->aPos[0] - g_vEdgeFollowDir;
    fVar13 = pWVar2->aPos[1] - *(float *)&DAT_008cf264;
    fVar5 = pWVar2->aPos[2] - *(float *)&DAT_008cf268;
    if (0.0025 <= fVar5 * fVar5 + fVar13 * fVar13 + fVar6 * fVar6) {
      uVar11 = iVar1 - 1;
      uVar10 = uVar11;
      uVar9 = uVar11;
      uVar12 = uVar11;
      uVar7 = uVar11;
      uVar8 = uVar11;
      local_38 = uVar11;
      if ((int)uVar11 < 0) {
        uVar10 = this->nNumVerts - 1;
        uVar9 = this->nNumVerts - 1;
        uVar12 = this->nNumVerts - 1;
        uVar7 = this->nNumVerts - 1;
        uVar8 = this->nNumVerts - 1;
        local_38 = this->nNumVerts - 1;
      }
      if ((this->aVerts[local_38]->aPos[2] - *(float *)&DAT_008cf268) *
          (this->aVerts[uVar10]->aPos[2] - *(float *)&DAT_008cf268) +
          (this->aVerts[uVar12]->aPos[1] - *(float *)&DAT_008cf264) *
          (this->aVerts[uVar9]->aPos[1] - *(float *)&DAT_008cf264) +
          (this->aVerts[uVar8]->aPos[0] - g_vEdgeFollowDir) *
          (this->aVerts[uVar7]->aPos[0] - g_vEdgeFollowDir) < 0.0025) {
        uVar9 = uVar11;
        if ((int)uVar11 < 0) {
          uVar9 = this->nNumVerts - 1;
        }
        local_24 = this->aVerts[uVar9]->aPos[0] - pWVar2->aPos[0];
        uVar9 = uVar11;
        if ((int)uVar11 < 0) {
          uVar9 = this->nNumVerts - 1;
        }
        local_20 = this->aVerts[uVar9]->aPos[1] - this->aVerts[this->nHitEdge]->aPos[1];
        if (0x7fffffff < uVar11) {
          uVar11 = this->nNumVerts - 1;
        }
        local_1c = this->aVerts[uVar11]->aPos[2] - this->aVerts[this->nHitEdge]->aPos[2];
        rdVector_Normalize3Acc(&local_24);
        fVar13 = rdVector_Dot3(&local_24,walker + 6);
        fVar13 = stdMath_ArcSin3(fVar13);
        if ((90.0 - fVar13 < 1.0) || (179.0 < 90.0 - fVar13)) {
          uVar9 = this->nHitEdge - 1;
          if (0x7fffffff < uVar9) {
            uVar9 = this->nNumVerts - 1;
          }
          this->nHitEdge = uVar9;
        }
      }
    }
    else {
      uVar9 = iVar1 - 1;
      uVar12 = uVar9;
      if ((int)uVar9 < 0) {
        uVar12 = this->nNumVerts - 1;
      }
      local_24 = this->aVerts[uVar12]->aPos[0] - pWVar2->aPos[0];
      uVar12 = uVar9;
      if ((int)uVar9 < 0) {
        uVar12 = this->nNumVerts - 1;
      }
      local_20 = this->aVerts[uVar12]->aPos[1] - this->aVerts[iVar1]->aPos[1];
      if (0x7fffffff < uVar9) {
        uVar9 = this->nNumVerts - 1;
      }
      local_1c = this->aVerts[uVar9]->aPos[2] - this->aVerts[iVar1]->aPos[2];
      rdVector_Normalize3Acc(&local_24);
      fVar13 = rdVector_Dot3(&local_24,walker + 6);
      fVar13 = stdMath_ArcSin3(fVar13);
      if (90.0 - fVar13 < 1.0) {
        this->nHitEdge = (this->nHitEdge + 1) % this->nNumVerts;
      }
      else if (179.0 < 90.0 - fVar13) {
        this->nHitEdge = (this->nHitEdge + 1) % this->nNumVerts;
      }
    }
    iVar1 = this->nHitEdge;
    pWVar2 = this->aVerts[iVar1];
    uVar9 = iVar1 - 1;
    if (0x7fffffff < uVar9) {
      uVar9 = this->nNumVerts - 1;
    }
    fVar13 = this->aVerts[uVar9]->aPos[0] - pWVar2->aPos[0];
    fVar5 = fVar13;
    if (fVar13 < 0.0) {
      fVar5 = -fVar13;
    }
    fVar6 = fVar13;
    if (fVar5 <= 1e-05) {
      fVar6 = 0.0;
    }
    if (fVar6 == 0.0) {
      fVar13 = (*(float *)&DAT_008cf264 - pWVar2->aPos[1]) / (this->aVerts[uVar9]->aPos[1] - pWVar2->aPos[1]);
    }
    else {
      fVar13 = (g_vEdgeFollowDir - pWVar2->aPos[0]) / fVar13;
    }
    if (fVar13 < 0.15) {
      fVar13 = 0.15;
    }
    if (0.85 < fVar13) {
      fVar13 = 0.85;
    }
    iVar3 = this->nNumVerts;
    pWVar2 = this->aVerts[(iVar1 + 1) % iVar3];
    pWVar4 = this->aVerts[(iVar3 + -2 + iVar1) % iVar3];
    local_8 = (pWVar4->aPos[1] - pWVar2->aPos[1]) * fVar13 + pWVar2->aPos[1];
    local_4 = (pWVar4->aPos[2] - pWVar2->aPos[2]) * fVar13 + pWVar2->aPos[2];
    g_vEdgeFollowDir =
         ((pWVar4->aPos[0] - pWVar2->aPos[0]) * fVar13 + pWVar2->aPos[0]) - g_vEdgeFollowDir;
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


/* ---- 0x004a7a90  WalkPlane_AllActive ---- */
/* Original name WalkPlane_AllActive (the remaster's GrimFandango (Linux): same body (+0x2c = 1 for
   every plane of wp_head)); was SectorList_ResetFree. */

void WalkPlane_AllActive(void)

{
  WalkPlane *pWVar1;
  
  for (pWVar1 = g_pWalkPlane_wp_head; pWVar1 != (WalkPlane *)0x0; pWVar1 = pWVar1->pNext) {
    pWVar1->nActive = 1;
  }
  return;
}

/* ---- 0x004a7ab0  WalkPlane_AddVertex ---- */
/* Source: Engine/WalkPlane.cpp (line 974, from __FILE__/__LINE__ passed to the allocator) Original
   name WalkPlane_AddVertex (the remaster's GrimFandango (Linux): same body (assert "tot_verts <
   MAX_DB_VERTS - 2", WalkPlane.cpp; find an equal vertex in vert_db or take a free one, count the
   references)); was SectorVertexPool_GetOrAdd. */

WalkVertex * WalkPlane_AddVertex(undefined4 param_1,float *param_2)

{
  WalkVertex *pWVar1;
  float *pfVar2;
  int iVar3;
  WalkVertex *pWVar4;
  
  pWVar4 = (WalkVertex *)0x0;
  if (0x3fd < (int)g_dwWalkPlane_tot_verts) {
    (*g_pStd_HS->pAssertFail)
              (s_tot_verts___MAX_DB_VERTS___2_004ec8a8,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,
               0x3ce);
  }
  iVar3 = 0;
  pfVar2 = g_aWalkPlane_vert_db[0].aPos;
  do {
    if (((float)((WalkVertex *)(pfVar2 + -1))->nRefs != 0.0) &&
       ((param_2[2] - pfVar2[2]) * (param_2[2] - pfVar2[2]) +
        (param_2[1] - pfVar2[1]) * (param_2[1] - pfVar2[1]) +
        (*param_2 - *pfVar2) * (*param_2 - *pfVar2) < 1e-08)) {
      pWVar4 = g_aWalkPlane_vert_db + iVar3;
      pWVar4->nRefs = pWVar4->nRefs + 1;
      return pWVar4;
    }
    pfVar2 = pfVar2 + 4;
    iVar3 = iVar3 + 1;
  } while ((int)pfVar2 < ((unsigned)(uintptr_t)&UINT_008cf0b4));
  iVar3 = 0;
  pWVar1 = g_aWalkPlane_vert_db;
  do {
    if (pWVar1->nRefs < 1) {
      pWVar4 = g_aWalkPlane_vert_db + iVar3;
      break;
    }
    pWVar1 = pWVar1 + 1;
    iVar3 = iVar3 + 1;
  } while ((int)pWVar1 < ((unsigned)(uintptr_t)&g_dwWorkingPath));
  pWVar4->nRefs = 1;
  g_dwWalkPlane_tot_verts = g_dwWalkPlane_tot_verts + 1;
  pWVar4->aPos[0] = *param_2;
  pWVar4->aPos[1] = param_2[1];
  pWVar4->aPos[2] = param_2[2];
  return pWVar4;
}

/* ---- 0x004a7ba0  WalkPlane_RemoveVertex ---- */
/* Original name WalkPlane_RemoveVertex (the remaster's GrimFandango (Linux): same body (decrement
   the reference count, tot_verts - 1 when it reaches 0)); was SectorVertexPool_Release. */

void WalkPlane_RemoveVertex(int *param_1)

{
  int iVar1;
  
  if ((0 < *param_1) && (iVar1 = *param_1 + -1, *param_1 = iVar1, iVar1 == 0)) {
    g_dwWalkPlane_tot_verts = g_dwWalkPlane_tot_verts - 1;
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
  uint uVar3;
  int iVar4;
  WalkPlane *pWVar5;
  byte *pbVar6;
  int iVar7;
  undefined *puVar8;
  uint uVar9;
  char *pcVar10;
  byte *pbVar11;
  char *pcVar12;
  bool bVar13;
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
  uVar3 = stdConffile_ReadLine();
  do {
    if (uVar3 == 0) {
      if (2 < (int)local_1fc) {
        pWVar5 = Plat_Alloc(0x84);
        if (pWVar5 == (WalkPlane *)0x0) {
          pWVar5 = (WalkPlane *)0x0;
        }
        else {
          pWVar5 = WalkPlane_Construct(pWVar5,(int)local_184,local_1fc,param_1);
        }
        if (pWVar5 != (WalkPlane *)0x0) {
          Mem_CheckAlloc(pWVar5,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,0x4a0);
          WalkPlane_SetName(pWVar5,(char *)local_1b4);
          pWVar5->nId = local_1ec;
          pWVar5->nVisible = local_1f0;
          WalkPlane_SetType(pWVar5,local_200);
        }
      }
      puVar8 = (undefined *)0x0;
LAB_004a8147:
      return puVar8;
    }
    uVar3 = 0xffffffff;
    pcVar10 = (char *)g_dwStdConffile_aLine;
    do {
      pcVar12 = pcVar10;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar12 = pcVar10 + 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar12;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar10 = pcVar12 + -uVar3;
    pcVar12 = local_10c;
    for (uVar9 = uVar3 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar12 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar12 = pcVar12 + 1;
    }
    iVar4 = sscanf(local_10c,s_section___s_004ddd64,&DAT_008cf218);
    if (iVar4 == 1) {
      if (2 < (int)local_1fc) {
        pWVar5 = Plat_Alloc(0x84);
        if (pWVar5 == (WalkPlane *)0x0) {
          pWVar5 = (WalkPlane *)0x0;
        }
        else {
          pWVar5 = WalkPlane_Construct(pWVar5,(int)local_184,local_1fc,param_1);
        }
        if (pWVar5 != (WalkPlane *)0x0) {
          Mem_CheckAlloc(pWVar5,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,0x42e);
          WalkPlane_SetName(pWVar5,(char *)local_1b4);
          pWVar5->nId = local_1ec;
          pWVar5->nVisible = local_1f0;
          WalkPlane_SetType(pWVar5,local_200);
        }
      }
      puVar8 = &DAT_008cf218;
      goto LAB_004a8147;
    }
    iVar4 = String_ContainsSubstring(local_10c,s_numsectors_004ec9a8);
    if (iVar4 == 0) {
      iVar4 = sscanf(local_10c,s_sector__s_004ec99c,local_1e4);
      if (iVar4 == 1) {
        if (2 < (int)local_1fc) {
          pWVar5 = Plat_Alloc(0x84);
          if (pWVar5 == (WalkPlane *)0x0) {
            pWVar5 = (WalkPlane *)0x0;
          }
          else {
            pWVar5 = WalkPlane_Construct(pWVar5,(int)local_184,local_1fc,param_1);
          }
          if (pWVar5 != (WalkPlane *)0x0) {
            Mem_CheckAlloc(pWVar5,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,0x445);
            WalkPlane_SetName(pWVar5,(char *)local_1b4);
            pWVar5->nVisible = local_1f0;
            pWVar5->nId = local_1ec;
            WalkPlane_SetType(pWVar5,local_200);
            if (local_1f4 != 12345.0) {
              if (local_200 == 0x1000) {
                local_1f4 = 0.005;
              }
              if (local_1f4 == 0.0) {
                local_1f4 = 0.005;
              }
              pWVar5->flHeight = local_1f4;
            }
          }
        }
        uVar3 = 0xffffffff;
        pbVar6 = local_1e4;
        do {
          pbVar11 = pbVar6;
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          pbVar11 = pbVar6 + 1;
          bVar2 = *pbVar6;
          pbVar6 = pbVar11;
        } while (bVar2 != 0);
        uVar3 = ~uVar3;
        local_1b4[0] = 0;
        local_1f4 = 12345.0;
        pbVar6 = pbVar11 + -uVar3;
        pbVar11 = local_1b4;
        for (uVar9 = uVar3 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined4 *)pbVar11 = *(undefined4 *)pbVar6;
          pbVar6 = pbVar6 + 4;
          pbVar11 = pbVar11 + 4;
        }
        local_1ec = 0;
        local_200 = 0;
        local_1f0 = 0;
        local_1fc = 0;
        local_1f8 = 0;
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pbVar11 = *pbVar6;
          pbVar6 = pbVar6 + 1;
          pbVar11 = pbVar11 + 1;
        }
      }
      else {
        iVar4 = sscanf(local_10c,s_id__i_004ec994,&local_1e8);
        if (iVar4 == 1) {
          local_1ec = local_1e8;
        }
        else {
          iVar4 = sscanf(local_10c,s_type__s_004ec7b8,local_1e4);
          if (iVar4 == 1) {
            pbVar11 = &DAT_004ec98c;
            pbVar6 = local_1e4;
            do {
              bVar2 = *pbVar6;
              bVar13 = bVar2 < *pbVar11;
              if (bVar2 != *pbVar11) {
LAB_004a7e39:
                iVar4 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
                goto LAB_004a7e3e;
              }
              if (bVar2 == 0) break;
              bVar2 = pbVar6[1];
              bVar13 = bVar2 < pbVar11[1];
              if (bVar2 != pbVar11[1]) goto LAB_004a7e39;
              pbVar6 = pbVar6 + 2;
              pbVar11 = pbVar11 + 2;
            } while (bVar2 != 0);
            iVar4 = 0;
LAB_004a7e3e:
            if (iVar4 == 0) {
              local_200 = 0x1000;
            }
            else {
              pbVar11 = &DAT_004ec984;
              pbVar6 = local_1e4;
              do {
                bVar2 = *pbVar6;
                bVar13 = bVar2 < *pbVar11;
                if (bVar2 != *pbVar11) {
LAB_004a7e7c:
                  iVar4 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
                  goto LAB_004a7e81;
                }
                if (bVar2 == 0) break;
                bVar2 = pbVar6[1];
                bVar13 = bVar2 < pbVar11[1];
                if (bVar2 != pbVar11[1]) goto LAB_004a7e7c;
                pbVar6 = pbVar6 + 2;
                pbVar11 = pbVar11 + 2;
              } while (bVar2 != 0);
              iVar4 = 0;
LAB_004a7e81:
              if (iVar4 == 0) {
                local_200 = 0x1100;
              }
              else {
                pbVar11 = &DAT_004ec97c;
                pbVar6 = local_1e4;
                do {
                  bVar2 = *pbVar6;
                  bVar13 = bVar2 < *pbVar11;
                  if (bVar2 != *pbVar11) {
LAB_004a7ebf:
                    iVar4 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
                    goto LAB_004a7ec4;
                  }
                  if (bVar2 == 0) break;
                  bVar2 = pbVar6[1];
                  bVar13 = bVar2 < pbVar11[1];
                  if (bVar2 != pbVar11[1]) goto LAB_004a7ebf;
                  pbVar6 = pbVar6 + 2;
                  pbVar11 = pbVar11 + 2;
                } while (bVar2 != 0);
                iVar4 = 0;
LAB_004a7ec4:
                if (iVar4 == 0) {
                  local_200 = 0x2000;
                }
                else {
                  pbVar11 = &DAT_004ec974;
                  pbVar6 = local_1e4;
                  do {
                    bVar2 = *pbVar6;
                    bVar13 = bVar2 < *pbVar11;
                    if (bVar2 != *pbVar11) {
LAB_004a7f02:
                      iVar4 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
                      goto LAB_004a7f07;
                    }
                    if (bVar2 == 0) break;
                    bVar2 = pbVar6[1];
                    bVar13 = bVar2 < pbVar11[1];
                    if (bVar2 != pbVar11[1]) goto LAB_004a7f02;
                    pbVar6 = pbVar6 + 2;
                    pbVar11 = pbVar11 + 2;
                  } while (bVar2 != 0);
                  iVar4 = 0;
LAB_004a7f07:
                  if (iVar4 == 0) {
                    local_200 = 0x4000;
                  }
                  else {
                    pbVar11 = &DAT_004ec968;
                    pbVar6 = local_1e4;
                    do {
                      bVar2 = *pbVar6;
                      bVar13 = bVar2 < *pbVar11;
                      if (bVar2 != *pbVar11) {
LAB_004a7f45:
                        iVar4 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
                        goto LAB_004a7f4a;
                      }
                      if (bVar2 == 0) break;
                      bVar2 = pbVar6[1];
                      bVar13 = bVar2 < pbVar11[1];
                      if (bVar2 != pbVar11[1]) goto LAB_004a7f45;
                      pbVar6 = pbVar6 + 2;
                      pbVar11 = pbVar11 + 2;
                    } while (bVar2 != 0);
                    iVar4 = 0;
LAB_004a7f4a:
                    if (iVar4 == 0) {
                      local_200 = 0x8000;
                    }
                  }
                }
              }
            }
          }
          else {
            iVar4 = sscanf(local_10c,s_default_visibility__s_004ec950,local_1e4);
            if (iVar4 == 1) {
              pbVar11 = &DAT_004ec944;
              pbVar6 = local_1e4;
              do {
                bVar2 = *pbVar6;
                bVar13 = bVar2 < *pbVar11;
                if (bVar2 != *pbVar11) {
LAB_004a7fb9:
                  local_1f0 = (uint)(1 - bVar13 != (uint)(bVar13 != 0));
                  goto LAB_004a80a5;
                }
                if (bVar2 == 0) break;
                bVar2 = pbVar6[1];
                bVar13 = bVar2 < pbVar11[1];
                if (bVar2 != pbVar11[1]) goto LAB_004a7fb9;
                pbVar6 = pbVar6 + 2;
                pbVar11 = pbVar11 + 2;
              } while (bVar2 != 0);
              local_1f0 = 0;
            }
            else {
              iVar4 = sscanf(local_10c,s_height__f_004ec938,&local_1f4);
              if (iVar4 != 1) {
                iVar4 = sscanf(local_10c,s_numvertices__d_004ec928,&local_1e8);
                if (iVar4 == 1) {
                  local_1fc = local_1e8;
                }
                else {
                  iVar4 = sscanf(local_10c,s_numgates__s_004ec918,local_1e4);
                  if (iVar4 != 1) {
                    iVar4 = local_1f8 * 0xc;
                    iVar7 = sscanf(local_10c,s_vertices___f__f__f_004ec904,local_184 + iVar4,
                                   auStack_180 + iVar4,auStack_17c + iVar4);
                    if ((iVar7 == 3) ||
                       (((int)local_1f8 < (int)local_1fc &&
                        (iVar4 = sscanf(local_10c,s__f__f__f_004ec8f8,local_184 + iVar4,
                                        auStack_180 + iVar4,auStack_17c + iVar4), iVar4 == 3)))) {
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
    uVar3 = stdConffile_ReadLine();
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


/* ---- 0x004a8cb0  WalkPlane_ClipPoly ---- */
/* Sutherland-Hodgman clip of a polygon against the sector's edges in its projection plane; returns
   the vertex count Original name WalkPlane_ClipPoly (the remaster's GrimFandango (Linux): same
   parameters (vertices, count, out) and body (copy the polygon, clip it against every edge of the
   plane)); was Sector_ClipPolygon. */

int __thiscall WalkPlane_ClipPoly(WalkPlane *this,float *verts,int count,float *out)

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
  undefined4 *puVar14;
  int iVar15;
  undefined1 *puVar16;
  float *pfVar17;
  float *pfVar18;
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
    pfVar18 = &local_120;
    for (uVar13 = count * 3 & 0x3fffffff; uVar13 != 0; uVar13 = uVar13 - 1) {
      *pfVar18 = *verts;
      verts = verts + 1;
      pfVar18 = pfVar18 + 1;
    }
  }
  local_128 = 0;
  local_140 = (uint)&local_120;
  if (0 < this->nNumVerts) {
    local_12c = (uint)this->aVerts;
    puVar11 = local_90;
    pfVar18 = this->aVerts[this->nNumVerts + -1]->aPos;
    do {
      puVar16 = puVar11;
      iVar12 = this->nAxisV;
      iVar1 = this->nAxisU;
      pfVar17 = (float *)(*(int *)local_12c + 4);
      local_150 = 0;
      fVar2 = -(pfVar17[iVar1] - pfVar18[iVar1]);
      fVar3 = pfVar17[iVar12] - pfVar18[iVar12];
      local_148 = (local_140 - 0xc) + count * 0xc;
      if (0 < count) {
        iVar15 = 0;
        puVar10 = (undefined4 *)local_140;
        local_14c = (uint)puVar16;
        local_144 = count;
        local_138 = (*(float *)(local_148 + iVar1 * 4) - pfVar18[iVar1]) * fVar3 +
                    (*(float *)(local_148 + iVar12 * 4) - pfVar18[iVar12]) * fVar2;
        do {
          puVar14 = puVar10;
          iVar12 = this->nAxisV;
          iVar1 = this->nAxisU;
          fVar4 = (PUN(float,puVar14[iVar12]) - pfVar18[iVar12]) * fVar2 +
                  (PUN(float,puVar14[iVar1]) - pfVar18[iVar1]) * fVar3;
          if ((local_138 <= 0.0) || (fVar4 <= 0.0)) {
            if ((local_138 <= 0.0) || (0.0 <= fVar4)) {
              if ((local_138 < 0.0) && (0.0 < fVar4)) {
                fVar9 = PUN(float,puVar14[iVar12]) - *(float *)(local_148 + iVar12 * 4);
                fVar8 = PUN(float,puVar14[iVar1]) - *(float *)(local_148 + iVar1 * 4);
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
                  *(float *)(puVar16 + (this->nAxisV + iVar15) * 4) =
                       fVar9 * (fVar4 / fVar5) + PUN(float,puVar14[iVar12]);
                  iVar12 = this->nAxisU + iVar15;
                  iVar15 = iVar15 + 3;
                  local_14c = local_14c + 0xc;
                  *(float *)(puVar16 + iVar12 * 4) =
                       fVar8 * (fVar4 / fVar5) + PUN(float,puVar14[this->nAxisU]);
                }
                goto LAB_004a903f;
              }
            }
            else {
              fVar9 = PUN(float,puVar14[iVar12]) - *(float *)(local_148 + iVar12 * 4);
              fVar8 = PUN(float,puVar14[iVar1]) - *(float *)(local_148 + iVar1 * 4);
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
                *(float *)(puVar16 + (this->nAxisV + iVar15) * 4) =
                     fVar9 * (fVar4 / fVar5) + PUN(float,puVar14[iVar12]);
                iVar12 = this->nAxisU + iVar15;
                iVar15 = iVar15 + 3;
                local_14c = local_14c + 0xc;
                *(float *)(puVar16 + iVar12 * 4) =
                     fVar8 * (fVar4 / fVar5) + PUN(float,puVar14[this->nAxisU]);
              }
            }
          }
          else {
LAB_004a903f:
            iVar15 = iVar15 + 3;
            *(undefined4 *)local_14c = *puVar14;
            *(undefined4 *)(local_14c + 4) = puVar14[1];
            local_150 = local_150 + 1;
            *(undefined4 *)(local_14c + 8) = puVar14[2];
            local_14c = local_14c + 0xc;
          }
          local_144 = local_144 - 1;
          puVar10 = puVar14 + 3;
          local_148 = (uint)puVar14;
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
      pfVar18 = pfVar17;
      local_140 = (uint)puVar16;
    } while ((int)local_128 < this->nNumVerts);
  }
  if (0 < count) {
    iVar12 = local_140 - (int)out;
    do {
      pfVar18 = (float *)(iVar12 + (int)out);
      *out = *pfVar18;
      out[1] = pfVar18[1];
      out[2] = pfVar18[2];
      WalkPlane_Project(this,(int)out);
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


/* ---- 0x004a9070  WalkPlane_DistToEdge ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Source: Engine/WalkPlane.cpp (line 1736, from __FILE__/__LINE__ passed to the allocator) Original
   name WalkPlane_DistToEdge (the remaster's GrimFandango (Linux): same body (assert "edge_index <
   num_verts", WalkPlane.cpp; the distance of the point to the edge)); was Sector_EdgeDistance. */

float __thiscall WalkPlane_DistToEdge(WalkPlane *this,int edge,float *point)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  WalkVertex *pWVar1;
  WalkVertex *pWVar2;
  float10 extraout_ST0;
  float fVar3;
  #define fStack_38 (*(float *)(_frame + (0x50 - 0x38)))
  #define fStack_34 (*(float *)(_frame + (0x50 - 0x34)))
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
  
  if (this->nNumVerts <= edge) {
    (*g_pStd_HS->pAssertFail)
              (s_edge_index___num_verts_004ec9b8,s_C__grimsrc_libs_grimlib_Engine_W_004ec8c8,0x6c8);
  }
  pWVar1 = this->aVerts[edge];
  pWVar2 = this->aVerts[(edge + 1) % this->nNumVerts];
  local_30 = pWVar2->aPos[0] - pWVar1->aPos[0];
  fStack_2c = pWVar2->aPos[1] - pWVar1->aPos[1];
  fStack_28 = pWVar2->aPos[2] - pWVar1->aPos[2];
  fStack_24 = *point - pWVar1->aPos[0];
  fStack_20 = point[1] - pWVar1->aPos[1];
  fStack_1c = point[2] - pWVar1->aPos[2];
  rdVector_Normalize3(&local_c,&local_30);
  rdVector_Normalize3(&fStack_18,&fStack_24);
  fVar3 = stdMath_ArcSin3(fStack_10 * fStack_4 + fStack_14 * fStack_8 + fStack_18 * local_c);
  stdMath_SinCos(90.0 - fVar3,&fStack_38,&fStack_34);
  return fStack_38 * (float)extraout_ST0;
}
#undef fStack_10
#undef fStack_14
#undef fStack_18
#undef fStack_1c
#undef fStack_20
#undef fStack_24
#undef fStack_28
#undef fStack_2c
#undef fStack_34
#undef fStack_38
#undef fStack_4
#undef fStack_8
#undef local_30
#undef local_c

#endif


/* ---- 0x004a9180  WalkPlane_RemoveShortEdge ---- */
/* Sector_CollapseShortestEdge: for a sector of 4 or more vertices, finds the shortest edge a -
   (a+1) and replaces its two ends by the point where the line of the edge before it (a-1 -> a)
   meets the line of the edge after it ((a+1) -> (a+2)), computed on the two dominant axes (+0x7c,
   +0x80) with Sector_FixPlaneCoordinate for the third; fails (0) when those lines are parallel
   (|cross| <= 1e-5). The new vertex goes through SectorVertexPool_GetOrAdd. Original name
   WalkPlane_RemoveShortEdge (the remaster's GrimFandango (Linux): same body (for more than 3
   vertices: find the shortest edge from FLT_MAX and merge its vertices)); was
   Sector_CollapseShortestEdge. */

undefined4 __fastcall WalkPlane_RemoveShortEdge(WalkPlane *plane)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float *pfVar1;
  WalkVertex *pWVar2;
  WalkVertex *pWVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float *pfVar11;
  uint *puVar12;
  int iVar13;
  WalkVertex **ppWVar14;
  int iVar15;
  int iVar16;
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
  iVar16 = plane->nNumVerts;
  if (3 < iVar16) {
    iVar15 = 0;
    if (0 < iVar16) {
      ppWVar14 = plane->aVerts;
      pfVar11 = plane->aVerts[iVar16 + -1]->aPos;
      do {
        pWVar2 = *ppWVar14;
        fVar7 = pfVar11[1] - pWVar2->aPos[1];
        fVar5 = pfVar11[2] - pWVar2->aPos[2];
        fVar6 = *pfVar11 - pWVar2->aPos[0];
        fVar5 = fVar6 * fVar6 + fVar5 * fVar5 + fVar7 * fVar7;
        if (fVar5 < local_50) {
          local_4c = (iVar16 + -1 + iVar15) % iVar16;
          local_50 = fVar5;
        }
        iVar15 = iVar15 + 1;
        ppWVar14 = ppWVar14 + 1;
        pfVar11 = pWVar2->aPos;
      } while (iVar15 < iVar16);
    }
    pWVar2 = plane->aVerts[(int)(iVar16 + -1 + local_4c) % iVar16];
    iVar15 = local_4c + 2;
    pWVar3 = plane->aVerts[iVar15 % iVar16];
    local_40 = PUN(uint,(float)pWVar3->aPos[0]);
    iVar4 = plane->nAxisU;
    local_3c = PUN(uint,(float)pWVar3->aPos[1]);
    iVar13 = plane->nAxisV;
    local_38 = PUN(uint,(float)pWVar3->aPos[2]);
    local_34 = -(plane->aVerts[local_4c]->aPos[iVar4] - pWVar2->aPos[iVar4]);
    local_30 = plane->aVerts[local_4c]->aPos[iVar13] - pWVar2->aPos[iVar13];
    pfVar11 = (float *)(&local_40 + iVar4);
    pfVar1 = (float *)(&local_40 + iVar13);
    fVar5 = (*pfVar1 - pWVar2->aPos[iVar13]) * local_34 +
            (*pfVar11 - pWVar2->aPos[iVar4]) * local_30;
    fVar6 = fVar5;
    if (fVar5 < 0.0) {
      fVar6 = -fVar5;
    }
    fVar7 = fVar5;
    if (fVar6 <= 1e-05) {
      fVar7 = 0.0;
    }
    if (fVar7 != 0.0) {
      fVar6 = *pfVar1 - plane->aVerts[(int)(local_4c + 1) % iVar16]->aPos[iVar13];
      fVar10 = *pfVar11 - plane->aVerts[(int)(local_4c + 1) % iVar16]->aPos[iVar4];
      fVar7 = -(fVar6 * local_34) - fVar10 * local_30;
      fVar9 = fVar7;
      if (fVar7 < 0.0) {
        fVar9 = -fVar7;
      }
      fVar8 = fVar7;
      if (fVar9 <= 1e-05) {
        fVar8 = 0.0;
      }
      if (fVar8 != 0.0) {
        *pfVar1 = fVar6 * (fVar5 / fVar7) + *pfVar1;
        *pfVar11 = fVar10 * (fVar5 / fVar7) + *pfVar11;
        WalkPlane_Project(plane,(int)&local_40);
        local_28 = WalkPlane_AddVertex(0,&local_40);
        iVar4 = plane->nNumVerts;
        iVar16 = iVar4 + -2;
        if (0 < iVar16) {
          puVar12 = &local_24;
          do {
            iVar13 = iVar15 % iVar4;
            iVar15 = iVar15 + 1;
            iVar16 = iVar16 + -1;
            *puVar12 = (uint)plane->aVerts[iVar13];
            puVar12 = puVar12 + 1;
          } while (iVar16 != 0);
        }
        WalkPlane_RemoveVertex(plane->aVerts[local_4c]);
        WalkPlane_RemoveVertex(plane->aVerts[(int)(local_4c + 1) % plane->nNumVerts]);
        iVar15 = plane->nNumVerts + -1;
        iVar16 = 0;
        plane->nNumVerts = iVar15;
        if (0 < iVar15) {
          puVar12 = &local_28;
          ppWVar14 = plane->aVerts;
          do {
            iVar16 = iVar16 + 1;
            *ppWVar14 = (WalkVertex *)*puVar12;
            puVar12 = puVar12 + 1;
            ppWVar14 = ppWVar14 + 1;
          } while (iVar16 < plane->nNumVerts);
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
/* SectorList_ShrinkWalkSectors(radius), called by Lua ShrinkBoxes after WalkPlane_BuildCache. For
   every active walk sector (type & 0x1000, flag +0x28): for each vertex take the bisector of the
   directions to its neighbours, move it inward by radius / sin(half angle) (Math_SinCosTable,
   Math_AsinDegreesSeries); the move is valid when the new point is inside the sector
   (WalkPlane_Within) and at least radius - 0.001 from the line of every edge
   (WalkPlane_DistToEdge). Not valid: WalkPlane_RemoveShortEdge and retry; cannot collapse: the
   sector is switched off (+0x28 = 0). The shifts are summed per pool vertex (shared by the sectors)
   and the pool vertex moves by the mean, so all sectors that share it move together. Undone by
   WalkPlane_RestoreCache. Original name ShrinkBoxes (the remaster's GrimFandango (Linux): the only
   unmatched callee of Lua_TEST; 3 matched neighbours agree, 0 disagree); was
   SectorList_ShrinkWalkSectors. */

void __cdecl ShrinkBoxes(float radius)

{
  unsigned char _frame[0x30];  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  WalkVertex *pWVar3;
  bool bVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  int *piVar9;
  WalkPlane *this;
  WalkVertex **ppWVar10;
  undefined4 *puVar11;
  float fVar12;
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
    puVar11 = (undefined4 *)&STACK0X(0x000010b8);
    for (iVar6 = 0xc00; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar11 = 0;
      puVar11 = puVar11 + 1;
    }
    puVar11 = (undefined4 *)&STACK0X(0x000000b8);
    for (iVar6 = 0x400; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar11 = 0;
      puVar11 = puVar11 + 1;
    }
    this = g_pWalkPlane_wp_head;
    if (g_pWalkPlane_wp_head != (WalkPlane *)0x0) {
LAB_004a9d53:
      if (((this->dwType & 0x1000) != 0) && (this->nVisible != 0)) {
LAB_004a9d6a:
        pWVar3 = this->aVerts[0];
        puVar11 = (undefined4 *)&STACK0X(0x00000040);
        for (iVar6 = 0x1e; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar11 = 0;
          puVar11 = puVar11 + 1;
        }
        pfStack00000020 = (float *)&STACK0X(0x00000044);
        iStack0000000c = 0;
        pfVar7 = this->aVerts[this->nNumVerts + -1]->aPos;
        pfVar5 = pWVar3->aPos;
        do {
          if (this->nNumVerts <= iStack0000000c) {
            iVar6 = this->nNumVerts;
            if (0 < iVar6) {
              ppWVar10 = this->aVerts;
              pfVar7 = (float *)&STACK0X(0x00000044);
              do {
                pWVar3 = *ppWVar10;
                ppWVar10 = ppWVar10 + 1;
                iVar8 = ((int)((WalkVertex *)((char *)pWVar3 - ((unsigned)(uintptr_t)&g_aWalkPlane_vert_db))) >> 4) * 0xc;
                *(float *)(&STACK0X(0x000010b8) + iVar8) =
                     pfVar7[-1] + *(float *)(&STACK0X(0x000010b8) + iVar8);
                *(float *)(&STACK0X(0x000010bc) + iVar8) =
                     *(float *)(&STACK0X(0x000010bc) + iVar8) + *pfVar7;
                *(float *)(&STACK0X(0x000010c0) + iVar8) =
                     pfVar7[1] + *(float *)(&STACK0X(0x000010c0) + iVar8);
                iVar6 = iVar6 + -1;
                *(int *)(&STACK0X(0x000000b8) + ((int)((WalkVertex *)((char *)pWVar3 - ((unsigned)(uintptr_t)&g_aWalkPlane_vert_db))) >> 4) * 4) =
                     *(int *)(&STACK0X(0x000000b8) + ((int)((WalkVertex *)((char *)pWVar3 - ((unsigned)(uintptr_t)&g_aWalkPlane_vert_db))) >> 4) * 4) + 1;
                pfVar7 = pfVar7 + 3;
              } while (iVar6 != 0);
            }
            break;
          }
          iStack0000000c = iStack0000000c + 1;
          local_4 = *pfVar7 - *pfVar5;
          pWVar3 = this->aVerts[iStack0000000c % this->nNumVerts];
          fVar1 = pfVar7[1];
          fVar2 = pfVar5[1];
          fVar12 = pfVar7[2];
          fVar13 = pfVar5[2];
          rdVector_Normalize3Acc(&local_4);
          in_stack_00000014 = pWVar3->aPos[0] - *pfVar5;
          in_stack_00000018 = pWVar3->aPos[1] - pfVar5[1];
          in_stack_0000001c = pWVar3->aPos[2] - pfVar5[2];
          rdVector_Normalize3Acc(&STACK0X(0x00000014));
          local_4 = in_stack_00000014 + local_4;
          fVar1 = in_stack_00000018 + (fVar1 - fVar2);
          fVar2 = in_stack_0000001c + (fVar12 - fVar13);
          rdVector_Normalize3Acc(&local_4);
          fVar12 = stdMath_ArcSin3(in_stack_0000001c * fVar2 +
                                   in_stack_00000018 * fVar1 + in_stack_00000014 * local_4);
          stdMath_SinCos(90.0 - fVar12,&STACK0X(0x00000024),(float *)&STACK0X(0x00000034));
          fVar12 = fVar2 / in_stack_00000024;
          bVar4 = true;
          in_stack_00000028 = fVar12 * local_4 + *pfVar5;
          in_stack_0000002c = fVar12 * fVar1 + pfVar5[1];
          in_stack_00000030 = fVar12 * fVar2 + pfVar5[2];
          iVar6 = WalkPlane_Within(this,&STACK0X(0x00000028),1);
          if (iVar6 == 0) {
LAB_004a9f32:
            bVar4 = false;
          }
          else {
            iStack00000010 = 0;
            if (0 < this->nNumVerts) {
              in_stack_00000038 = (double)(fVar2 - 0.001);
              do {
                fVar13 = WalkPlane_DistToEdge(this,iStack00000010,&STACK0X(0x00000028));
                if (fVar13 < (float)in_stack_00000038) goto LAB_004a9f32;
                iStack00000010 = iStack00000010 + 1;
              } while (iStack00000010 < this->nNumVerts);
            }
          }
          if (!bVar4) goto LAB_004a9f7e;
          pfStack00000020[-1] = fVar12 * local_4;
          *pfStack00000020 = fVar12 * fVar1;
          pfStack00000020[1] = fVar12 * fVar2;
          pfStack00000020 = pfStack00000020 + 3;
          pfVar7 = pfVar5;
          pfVar5 = pWVar3->aPos;
        } while( true );
      }
      goto LAB_004a9ffa;
    }
LAB_004aa005:
    piVar9 = (int *)&STACK0X(0x000000b8);
    pfVar5 = g_aWalkPlane_vert_db[0].aPos + 1;
    pfVar7 = (float *)&STACK0X(0x000010bc);
    do {
      if (*piVar9 != 0) {
        fVar12 = 1.0 / (float)*piVar9;
        fVar1 = *pfVar7;
        fVar2 = pfVar7[1];
        pfVar5[-1] = pfVar7[-1] * fVar12 + pfVar5[-1];
        *pfVar5 = fVar1 * fVar12 + *pfVar5;
        pfVar5[1] = fVar2 * fVar12 + pfVar5[1];
      }
      pfVar5 = pfVar5 + 4;
      piVar9 = piVar9 + 1;
      pfVar7 = pfVar7 + 3;
    } while ((int)pfVar5 < ((unsigned)(uintptr_t)&UINT_008cf0b8));
  }
  return;
LAB_004a9f7e:
  iVar6 = WalkPlane_RemoveShortEdge(this);
  if (iVar6 == 0) goto code_r0x004a9f8d;
  goto LAB_004a9d6a;
code_r0x004a9f8d:
  this->nVisible = 0;
LAB_004a9ffa:
  this = this->pNext;
  if (this == (WalkPlane *)0x0) goto LAB_004aa005;
  goto LAB_004a9d53;
}
#undef local_18
#undef local_4
#undef local_8

#endif

