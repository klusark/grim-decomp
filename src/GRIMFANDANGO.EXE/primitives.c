/* GRIMFANDANGO.EXE :: primitives.c
 * functions 0x00489550 .. 0x0048abc0 (17 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00489550  sputPrimitive_Update ---- */
/* Original name sputPrimitive_Update (the remaster's GrimFandango (Linux): aligned call in
   sputRender_Update); was Primitives_DrawAll. */

void __cdecl sputPrimitive_Update(uint layerMask)

{
  if (g_nSputPrimitive_Paused == 0) {
    PrimitiveQueue_draw(&g_dwPrimitiveQ,*(void **)((int)g_pRdCamera_CurCamera + 4),layerMask);
  }
  return;
}

/* ---- 0x004895d0  sputPrimitive_Pause ---- */
/* Invalidates every primitive and stops drawing them (movie playback) Original name
   sputPrimitive_Pause (the remaster's GrimFandango (Linux): aligned call in sputRender_Dim); was
   Primitives_Hide. */

void __cdecl sputPrimitive_Pause(void)

{
  PrimitiveQueue_markAllDirty(&g_dwPrimitiveQ,3);
  g_nSputPrimitive_Paused = 1;
  return;
}

/* ---- 0x004895f0  sputPrimitive_Resume ---- */
/* Original name sputPrimitive_Resume (the remaster's GrimFandango (Linux): aligned call in
   sputRender_Dim); was Primitives_Show. */

void __cdecl sputPrimitive_Resume(void)

{
  g_nSputPrimitive_Paused = 0;
  return;
}

/* ---- 0x0048a4b0  PrimitiveObject_Construct ---- */
/* 0x30-byte primitive {next, prev, type (0 line, 1 rect, 2 polyline segment), id, layer, x1, y1,
   x2, y2, color, ?, filled} Original name PrimitiveObject_Construct (the remaster's GrimFandango
   (Linux): same body (links 0, id at +0xc, +8 = the second argument, colour 0, +0x28 / +0x30 = -1,
   rectangle 0)); was Primitive_Construct. */

Primitive * __thiscall PrimitiveObject_Construct(Primitive *this,int id,int type)

{
  this->nX1 = 0;
  this->nY1 = 0;
  this->nX2 = 0;
  this->nY2 = 0;
  this->nType = type;
  this->pNext = (Primitive *)0x0;
  this->pPrev = (Primitive *)0x0;
  this->nId = id;
  this->nColor = 0;
  this->nPattern = -1;
  this->nX1 = 0;
  this->nY1 = 0;
  this->nX2 = 0;
  this->nY2 = this->nY1;
  this->nLayer = 2;
  return this;
}

/* ---- 0x0048a560  PrimitiveQueue_addLine ---- */
/* Original name PrimitiveQueue_addLine (the remaster's GrimFandango (Linux): same body (id =
   nextId++, new primitive, the two end points and the colour, returns the id)); was
   Primitive_AddLine. */

int __thiscall PrimitiveQueue_addLine(void *this,int x1,int y1,int x2,int y2,int color,int layer)

{
  int id;
  Primitive *pPVar1;
  
  id = g_nPrimitiveQueue_nextId;
  g_nPrimitiveQueue_nextId = g_nPrimitiveQueue_nextId + 1;
  pPVar1 = PrimitiveQueue_addObject(this,id,layer);
  pPVar1->nX1 = x1;
  pPVar1->nY1 = y1;
  pPVar1->nX2 = x2;
  pPVar1->nY2 = y2;
  pPVar1->nColor = color;
  return pPVar1->nId;
}

/* ---- 0x0048a5b0  PrimitiveQueue_addRect ---- */
/* Original name PrimitiveQueue_addRect (the remaster's GrimFandango (Linux): the rectangle
   counterpart of PrimitiveQueue_addLine (id = nextId++, new primitive, rectangle and colour)); was
   Primitive_AddRect. */

int __thiscall
PrimitiveQueue_addRect(void *this,int x1,int y1,int x2,int y2,int color,int filled,int layer)

{
  int id;
  Primitive *pPVar1;
  
  id = g_nPrimitiveQueue_nextId;
  g_nPrimitiveQueue_nextId = g_nPrimitiveQueue_nextId + 1;
  pPVar1 = PrimitiveQueue_addObject(this,id,layer);
  pPVar1->nType = 1;
  pPVar1->nX1 = x1;
  pPVar1->nY1 = y1;
  pPVar1->nX2 = x2;
  pPVar1->nY2 = y2;
  pPVar1->nColor = color;
  pPVar1->nFilled = filled;
  return pPVar1->nId;
}

/* ---- 0x0048a600  PrimitiveQueue_addPolygon ---- */
/* Original name PrimitiveQueue_addPolygon (the remaster's GrimFandango (Linux): the polygon
   counterpart of PrimitiveQueue_addLine (id = nextId++, the points); called by
   sputPrimitive_DrawPolygon in both builds); was Primitive_AddPolyline. */

int __thiscall PrimitiveQueue_addPolygon(void *this,int count,int *points,int color,int layer)

{
  int *piVar1;
  int id;
  Primitive *pPVar2;
  int *piVar3;
  int iVar4;
  
  id = g_nPrimitiveQueue_nextId;
  g_nPrimitiveQueue_nextId = g_nPrimitiveQueue_nextId + 1;
  iVar4 = count + -1;
  if (0 < iVar4) {
    piVar3 = points + 1;
    do {
      pPVar2 = PrimitiveQueue_addObject(this,id,layer);
      pPVar2->nType = 2;
      pPVar2->nX1 = piVar3[-1];
      pPVar2->nY1 = *piVar3;
      pPVar2->nX2 = piVar3[1];
      piVar1 = piVar3 + 2;
      piVar3 = piVar3 + 2;
      pPVar2->nY2 = *piVar1;
      iVar4 = iVar4 + -1;
      pPVar2->nColor = color;
    } while (iVar4 != 0);
  }
  return id;
}

/* ---- 0x0048a740  PrimitiveQueue_deletePrimitive ---- */
/* Original name PrimitiveQueue_deletePrimitive (the remaster's GrimFandango (Linux): same body
   (unlink the primitive with the id, fix the tail, mark dirty and free)); was Primitive_Kill. */

void __thiscall PrimitiveQueue_deletePrimitive(void *this,int id)

{
  Primitive *pPVar1;
  Primitive *prim;
  
  prim = *(Primitive **)this;
  while (prim != (Primitive *)0x0) {
    if (prim->nId == id) {
      if (prim->pPrev != (Primitive *)0x0) {
        prim->pPrev->pNext = prim->pNext;
      }
      if (prim->pNext != (Primitive *)0x0) {
        prim->pNext->pPrev = prim->pPrev;
      }
      if (*(Primitive **)((int)this + 4) == prim) {
        *(Primitive **)((int)this + 4) = prim->pPrev;
      }
      if (prim == *(Primitive **)this) {
        *(Primitive **)this = (*(Primitive **)this)->pNext;
      }
      pPVar1 = prim->pNext;
      PrimitiveQueue_markDirty(this,prim);
      Plat_Free(prim);
      prim = pPVar1;
    }
    else {
      prim = prim->pNext;
    }
  }
  return;
}

/* ---- 0x0048a7b0  PrimitiveQueue_changeColor ---- */
/* Original name PrimitiveQueue_changeColor (the remaster's GrimFandango (Linux): the colour store
   at +0x24 for every primitive with the id in both builds); was Primitive_SetColor. */

int __thiscall PrimitiveQueue_changeColor(void *this,int id,int color)

{
  Primitive *after;
  
  for (after = PrimitiveQueue_findPrimitive(this,id,(Primitive *)0x0); after != (Primitive *)0x0;
      after = PrimitiveQueue_findPrimitive(this,id,after)) {
    after->nColor = color;
  }
  return 0;
}

/* ---- 0x0048a7e0  PrimitiveQueue_changeLayer ---- */
/* Original name PrimitiveQueue_changeLayer (the remaster's GrimFandango (Linux): same body (for
   every primitive with the id: mark dirty, layer 1 or 2 at +0x10)); was Primitive_SetLayer. */

int __thiscall PrimitiveQueue_changeLayer(void *this,int id,int layer)

{
  Primitive *prim;
  
  for (prim = PrimitiveQueue_findPrimitive(this,id,(Primitive *)0x0); prim != (Primitive *)0x0;
      prim = PrimitiveQueue_findPrimitive(this,id,prim)) {
    PrimitiveQueue_markDirty(this,prim);
    if ((layer != 2) && (layer != 1)) {
      layer = 2;
    }
    prim->nLayer = layer;
  }
  return 0;
}

/* ---- 0x0048a830  PrimitiveQueue_move ---- */
/* Original name PrimitiveQueue_move (the remaster's GrimFandango (Linux): same body (for every
   primitive with the id: mark dirty, add dx / dy to both corners)); was Primitive_Offset. */

int __thiscall PrimitiveQueue_move(void *this,int id,int dx,int dy)

{
  Primitive *prim;
  
  for (prim = PrimitiveQueue_findPrimitive(this,id,(Primitive *)0x0); prim != (Primitive *)0x0;
      prim = PrimitiveQueue_findPrimitive(this,id,prim)) {
    PrimitiveQueue_markDirty(this,prim);
    prim->nX1 = prim->nX1 + dx;
    prim->nY2 = prim->nY2 + dy;
    prim->nY1 = prim->nY1 + dy;
    prim->nX2 = prim->nX2 + dx;
  }
  return 0;
}

/* ---- 0x0048a8a0  PrimitiveQueue_moveTo ---- */
/* Original name PrimitiveQueue_moveTo (the remaster's GrimFandango (Linux): the absolute
   counterpart of PrimitiveQueue_move; called by sputPrimitive_ChangePrimitive in both builds); was
   Primitive_MoveTo. */

int __thiscall PrimitiveQueue_moveTo(void *this,int id,int x,int y)

{
  Primitive *pPVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0;
  pPVar1 = PrimitiveQueue_findPrimitive(this,id,(Primitive *)0x0);
  if (pPVar1 != (Primitive *)0x0) {
    PrimitiveQueue_markDirty(this,pPVar1);
    if (x != -1) {
      iVar3 = x - pPVar1->nX1;
      pPVar1->nX1 = x;
    }
    if (y != -1) {
      iVar2 = y - pPVar1->nY1;
      pPVar1->nY1 = y;
    }
    pPVar1->nY2 = pPVar1->nY2 + iVar2;
    pPVar1->nX2 = pPVar1->nX2 + iVar3;
    for (pPVar1 = PrimitiveQueue_findPrimitive(this,id,pPVar1); pPVar1 != (Primitive *)0x0;
        pPVar1 = PrimitiveQueue_findPrimitive(this,id,pPVar1)) {
      PrimitiveQueue_markDirty(this,pPVar1);
      pPVar1->nX1 = pPVar1->nX1 + iVar3;
      pPVar1->nY1 = pPVar1->nY1 + iVar2;
      pPVar1->nX2 = pPVar1->nX2 + iVar3;
      pPVar1->nY2 = pPVar1->nY2 + iVar2;
    }
  }
  return 0;
}

/* ---- 0x0048a960  PrimitiveQueue_moveEndpoint ---- */
/* Original name PrimitiveQueue_moveEndpoint (the remaster's GrimFandango (Linux): same body (the
   first primitive with the id: mark dirty, the second point unless -1)); was Primitive_SetEnd. */

int __thiscall PrimitiveQueue_moveEndpoint(void *this,int id,int x,int y)

{
  Primitive *prim;
  int iVar1;
  
  prim = PrimitiveQueue_findPrimitive(this,id,(Primitive *)0x0);
  iVar1 = 0;
  if (prim != (Primitive *)0x0) {
    PrimitiveQueue_markDirty(this,prim);
    if (x != -1) {
      prim->nX2 = x;
    }
    iVar1 = y;
    if (y != -1) {
      prim->nY2 = y;
    }
  }
  return iVar1;
}

/* ---- 0x0048a9a0  PrimitiveQueue_changeDimensions ---- */
/* Original name PrimitiveQueue_changeDimensions (the remaster's GrimFandango (Linux): same body
   (the first primitive with the id: mark dirty, the second corner = the first + width / height
   unless -1)); was Primitive_SetSize. */

int __thiscall PrimitiveQueue_changeDimensions(void *this,int id,int w,int h)

{
  Primitive *prim;
  int iVar1;
  
  prim = PrimitiveQueue_findPrimitive(this,id,(Primitive *)0x0);
  iVar1 = 0;
  if (prim != (Primitive *)0x0) {
    PrimitiveQueue_markDirty(this,prim);
    if (w != -1) {
      prim->nX2 = prim->nX1 + w;
    }
    iVar1 = h;
    if (h != -1) {
      prim->nY2 = prim->nY1 + h;
    }
  }
  return iVar1;
}

/* ---- 0x0048aa20  PrimitiveQueue_drawPrimitive ---- */
/* Original name PrimitiveQueue_drawPrimitive (the remaster's GrimFandango (Linux): the
   per-primitive draw PrimitiveQueue_draw calls in both builds); was Primitive_Draw. */

void __stdcall PrimitiveQueue_drawPrimitive(Primitive *prim,void *canvas)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  int iVar3;
  int y1;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  iVar1 = prim->nType;
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      if (prim->nFilled == 0) {
        rdPrimit2_DrawRectangle
                  (canvas,prim->nX1,prim->nY1,prim->nX2,prim->nY2,prim->nColor,prim->nPattern);
        return;
      }
      local_10 = prim->nX1;
      uVar2 = prim->nX2;
      local_8 = local_10;
      if ((int)uVar2 <= (int)local_10) {
        local_8 = uVar2;
      }
      iVar1 = prim->nY1;
      iVar3 = prim->nY2;
      y1 = iVar1;
      if (iVar3 <= iVar1) {
        y1 = iVar3;
      }
      if ((int)local_10 <= (int)uVar2) {
        local_10 = uVar2;
      }
      if (iVar3 < iVar1) {
        iVar3 = iVar1;
      }
      if (iVar3 < y1) {
        return;
      }
      do {
        rdPrimit2_DrawLine(canvas,local_8,y1,local_10,y1,prim->nColor,prim->nPattern);
        y1 = y1 + 1;
      } while (y1 <= iVar3);
      return;
    }
    if (iVar1 != 2) {
      return;
    }
  }
  rdPrimit2_DrawLine(canvas,prim->nX1,prim->nY1,prim->nX2,prim->nY2,prim->nColor,prim->nPattern);
  return;
}
#undef local_10
#undef local_8


/* ---- 0x0048ab50  PrimitiveQueue_markDirty ---- */
/* Marks the primitive's bounding rectangle dirty on the last buffer Original name
   PrimitiveQueue_markDirty (the remaster's GrimFandango (Linux): same body as the remaster's
   markDirty(PrimitiveObject *) (the primitive's rectangle, normalised, to
   sputRender_MarkDirtyRect)); was Primitive_Invalidate. */

int __thiscall PrimitiveQueue_markDirty(void *this,Primitive *prim)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int extraout_EAX;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar3 = prim->nX1;
  uVar1 = prim->nX2;
  local_10 = uVar3;
  if ((int)uVar1 <= (int)uVar3) {
    local_10 = uVar1;
  }
  uVar4 = prim->nY1;
  uVar2 = prim->nY2;
  local_c = uVar4;
  if ((int)uVar2 <= (int)uVar4) {
    local_c = uVar2;
  }
  if ((int)uVar3 <= (int)uVar1) {
    uVar3 = uVar1;
  }
  local_8 = (uVar3 - local_10) + 1;
  if ((int)uVar4 <= (int)uVar2) {
    uVar4 = uVar2;
  }
  local_4 = (uVar4 - local_c) + 1;
  sputRender_MarkDirtyRect((int *)&local_10,0);
  return extraout_EAX;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0048abc0  PrimitiveQueue_resetId ---- */
/* Original name PrimitiveQueue_resetId (the remaster's GrimFandango (Linux): same body (nextId =
   1)); was Primitive_ResetIds. */

void __cdecl PrimitiveQueue_resetId(void)

{
  g_nPrimitiveQueue_nextId = 1;
  return;
}
