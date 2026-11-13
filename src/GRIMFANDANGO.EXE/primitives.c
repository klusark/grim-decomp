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

void * __thiscall PrimitiveObject_Construct(void *this,int id,int unused)

{
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(int *)((int)this + 8) = unused;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(int *)((int)this + 0xc) = id;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined4 *)((int)this + 0x28) = 0xffffffff;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)((int)this + 0x20) = *(undefined4 *)((int)this + 0x18);
  *(undefined4 *)((int)this + 0x10) = 2;
  return this;
}

/* ---- 0x0048a560  PrimitiveQueue_addLine ---- */
/* Original name PrimitiveQueue_addLine (the remaster's GrimFandango (Linux): same body (id =
   nextId++, new primitive, the two end points and the colour, returns the id)); was
   Primitive_AddLine. */

int __thiscall PrimitiveQueue_addLine(void *this,int x1,int y1,int x2,int y2,int color,int layer)

{
  int id;
  void *pvVar1;
  
  id = g_nPrimitiveQueue_nextId;
  g_nPrimitiveQueue_nextId = g_nPrimitiveQueue_nextId + 1;
  pvVar1 = PrimitiveQueue_addObject(this,id,layer);
  *(int *)((int)pvVar1 + 0x14) = x1;
  *(int *)((int)pvVar1 + 0x18) = y1;
  *(int *)((int)pvVar1 + 0x1c) = x2;
  *(int *)((int)pvVar1 + 0x20) = y2;
  *(int *)((int)pvVar1 + 0x24) = color;
  return *(int *)((int)pvVar1 + 0xc);
}

/* ---- 0x0048a5b0  PrimitiveQueue_addRect ---- */
/* Original name PrimitiveQueue_addRect (the remaster's GrimFandango (Linux): the rectangle
   counterpart of PrimitiveQueue_addLine (id = nextId++, new primitive, rectangle and colour)); was
   Primitive_AddRect. */

int __thiscall
PrimitiveQueue_addRect(void *this,int x1,int y1,int x2,int y2,int color,int filled,int layer)

{
  int id;
  void *pvVar1;
  
  id = g_nPrimitiveQueue_nextId;
  g_nPrimitiveQueue_nextId = g_nPrimitiveQueue_nextId + 1;
  pvVar1 = PrimitiveQueue_addObject(this,id,layer);
  *(undefined4 *)((int)pvVar1 + 8) = 1;
  *(int *)((int)pvVar1 + 0x14) = x1;
  *(int *)((int)pvVar1 + 0x18) = y1;
  *(int *)((int)pvVar1 + 0x1c) = x2;
  *(int *)((int)pvVar1 + 0x20) = y2;
  *(int *)((int)pvVar1 + 0x24) = color;
  *(int *)((int)pvVar1 + 0x2c) = filled;
  return *(int *)((int)pvVar1 + 0xc);
}

/* ---- 0x0048a600  PrimitiveQueue_addPolygon ---- */
/* Original name PrimitiveQueue_addPolygon (the remaster's GrimFandango (Linux): the polygon
   counterpart of PrimitiveQueue_addLine (id = nextId++, the points); called by
   sputPrimitive_DrawPolygon in both builds); was Primitive_AddPolyline. */

int __thiscall PrimitiveQueue_addPolygon(void *this,int count,int *points,int color,int layer)

{
  int *piVar1;
  int id;
  void *pvVar2;
  int *piVar3;
  int iVar4;
  
  id = g_nPrimitiveQueue_nextId;
  g_nPrimitiveQueue_nextId = g_nPrimitiveQueue_nextId + 1;
  iVar4 = count + -1;
  if (0 < iVar4) {
    piVar3 = points + 1;
    do {
      pvVar2 = PrimitiveQueue_addObject(this,id,layer);
      *(undefined4 *)((int)pvVar2 + 8) = 2;
      *(int *)((int)pvVar2 + 0x14) = piVar3[-1];
      *(int *)((int)pvVar2 + 0x18) = *piVar3;
      *(int *)((int)pvVar2 + 0x1c) = piVar3[1];
      piVar1 = piVar3 + 2;
      piVar3 = piVar3 + 2;
      *(int *)((int)pvVar2 + 0x20) = *piVar1;
      iVar4 = iVar4 + -1;
      *(int *)((int)pvVar2 + 0x24) = color;
    } while (iVar4 != 0);
  }
  return id;
}

/* ---- 0x0048a740  PrimitiveQueue_deletePrimitive ---- */
/* Original name PrimitiveQueue_deletePrimitive (the remaster's GrimFandango (Linux): same body
   (unlink the primitive with the id, fix the tail, mark dirty and free)); was Primitive_Kill. */

void __thiscall PrimitiveQueue_deletePrimitive(void *this,int id)

{
  int *piVar1;
  int *prim;
  
  prim = *(int **)this;
  while (prim != (int *)0x0) {
    if (prim[3] == id) {
      if ((int *)prim[1] != (int *)0x0) {
        *(int *)prim[1] = *prim;
      }
      if (*prim != 0) {
        *(int *)(*prim + 4) = prim[1];
      }
      if (*(int **)((int)this + 4) == prim) {
        *(int *)((int)this + 4) = prim[1];
      }
      if (prim == *(int **)this) {
        *(int *)this = **(int **)this;
      }
      piVar1 = (int *)*prim;
      PrimitiveQueue_markDirty(this,prim);
      Plat_Free(prim);
      prim = piVar1;
    }
    else {
      prim = (int *)*prim;
    }
  }
  return;
}

/* ---- 0x0048a7b0  PrimitiveQueue_changeColor ---- */
/* Original name PrimitiveQueue_changeColor (the remaster's GrimFandango (Linux): the colour store
   at +0x24 for every primitive with the id in both builds); was Primitive_SetColor. */

int __thiscall PrimitiveQueue_changeColor(void *this,int id,int color)

{
  void *after;
  
  for (after = PrimitiveQueue_findPrimitive(this,id,(void *)0x0); after != (void *)0x0;
      after = PrimitiveQueue_findPrimitive(this,id,after)) {
    *(int *)((int)after + 0x24) = color;
  }
  return 0;
}

/* ---- 0x0048a7e0  PrimitiveQueue_changeLayer ---- */
/* Original name PrimitiveQueue_changeLayer (the remaster's GrimFandango (Linux): same body (for
   every primitive with the id: mark dirty, layer 1 or 2 at +0x10)); was Primitive_SetLayer. */

int __thiscall PrimitiveQueue_changeLayer(void *this,int id,int layer)

{
  void *prim;
  
  for (prim = PrimitiveQueue_findPrimitive(this,id,(void *)0x0); prim != (void *)0x0;
      prim = PrimitiveQueue_findPrimitive(this,id,prim)) {
    PrimitiveQueue_markDirty(this,prim);
    if ((layer != 2) && (layer != 1)) {
      layer = 2;
    }
    *(int *)((int)prim + 0x10) = layer;
  }
  return 0;
}

/* ---- 0x0048a830  PrimitiveQueue_move ---- */
/* Original name PrimitiveQueue_move (the remaster's GrimFandango (Linux): same body (for every
   primitive with the id: mark dirty, add dx / dy to both corners)); was Primitive_Offset. */

int __thiscall PrimitiveQueue_move(void *this,int id,int dx,int dy)

{
  void *prim;
  
  for (prim = PrimitiveQueue_findPrimitive(this,id,(void *)0x0); prim != (void *)0x0;
      prim = PrimitiveQueue_findPrimitive(this,id,prim)) {
    PrimitiveQueue_markDirty(this,prim);
    *(int *)((int)prim + 0x14) = *(int *)((int)prim + 0x14) + dx;
    *(int *)((int)prim + 0x20) = *(int *)((int)prim + 0x20) + dy;
    *(int *)((int)prim + 0x18) = *(int *)((int)prim + 0x18) + dy;
    *(int *)((int)prim + 0x1c) = *(int *)((int)prim + 0x1c) + dx;
  }
  return 0;
}

/* ---- 0x0048a8a0  PrimitiveQueue_moveTo ---- */
/* Original name PrimitiveQueue_moveTo (the remaster's GrimFandango (Linux): the absolute
   counterpart of PrimitiveQueue_move; called by sputPrimitive_ChangePrimitive in both builds); was
   Primitive_MoveTo. */

int __thiscall PrimitiveQueue_moveTo(void *this,int id,int x,int y)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0;
  pvVar1 = PrimitiveQueue_findPrimitive(this,id,(void *)0x0);
  if (pvVar1 != (void *)0x0) {
    PrimitiveQueue_markDirty(this,pvVar1);
    if (x != -1) {
      iVar3 = x - *(int *)((int)pvVar1 + 0x14);
      *(int *)((int)pvVar1 + 0x14) = x;
    }
    if (y != -1) {
      iVar2 = y - *(int *)((int)pvVar1 + 0x18);
      *(int *)((int)pvVar1 + 0x18) = y;
    }
    *(int *)((int)pvVar1 + 0x20) = *(int *)((int)pvVar1 + 0x20) + iVar2;
    *(int *)((int)pvVar1 + 0x1c) = *(int *)((int)pvVar1 + 0x1c) + iVar3;
    for (pvVar1 = PrimitiveQueue_findPrimitive(this,id,pvVar1); pvVar1 != (void *)0x0;
        pvVar1 = PrimitiveQueue_findPrimitive(this,id,pvVar1)) {
      PrimitiveQueue_markDirty(this,pvVar1);
      *(int *)((int)pvVar1 + 0x14) = *(int *)((int)pvVar1 + 0x14) + iVar3;
      *(int *)((int)pvVar1 + 0x18) = *(int *)((int)pvVar1 + 0x18) + iVar2;
      *(int *)((int)pvVar1 + 0x1c) = *(int *)((int)pvVar1 + 0x1c) + iVar3;
      *(int *)((int)pvVar1 + 0x20) = *(int *)((int)pvVar1 + 0x20) + iVar2;
    }
  }
  return 0;
}

/* ---- 0x0048a960  PrimitiveQueue_moveEndpoint ---- */
/* Original name PrimitiveQueue_moveEndpoint (the remaster's GrimFandango (Linux): same body (the
   first primitive with the id: mark dirty, the second point unless -1)); was Primitive_SetEnd. */

int __thiscall PrimitiveQueue_moveEndpoint(void *this,int id,int x,int y)

{
  void *prim;
  int iVar1;
  
  prim = PrimitiveQueue_findPrimitive(this,id,(void *)0x0);
  iVar1 = 0;
  if (prim != (void *)0x0) {
    PrimitiveQueue_markDirty(this,prim);
    if (x != -1) {
      *(int *)((int)prim + 0x1c) = x;
    }
    iVar1 = y;
    if (y != -1) {
      *(int *)((int)prim + 0x20) = y;
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
  void *prim;
  int iVar1;
  
  prim = PrimitiveQueue_findPrimitive(this,id,(void *)0x0);
  iVar1 = 0;
  if (prim != (void *)0x0) {
    PrimitiveQueue_markDirty(this,prim);
    if (w != -1) {
      *(int *)((int)prim + 0x1c) = *(int *)((int)prim + 0x14) + w;
    }
    iVar1 = h;
    if (h != -1) {
      *(int *)((int)prim + 0x20) = *(int *)((int)prim + 0x18) + h;
    }
  }
  return iVar1;
}

/* ---- 0x0048aa20  PrimitiveQueue_drawPrimitive ---- */
/* Original name PrimitiveQueue_drawPrimitive (the remaster's GrimFandango (Linux): the
   per-primitive draw PrimitiveQueue_draw calls in both builds); was Primitive_Draw. */

void __stdcall PrimitiveQueue_drawPrimitive(void *prim,void *canvas)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  int iVar3;
  int y1;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  
  iVar1 = *(int *)((int)prim + 8);
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      if (*(int *)((int)prim + 0x2c) == 0) {
        rdPrimit2_DrawRectangle
                  (canvas,*(int *)((int)prim + 0x14),*(int *)((int)prim + 0x18),
                   *(int *)((int)prim + 0x1c),*(int *)((int)prim + 0x20),*(int *)((int)prim + 0x24),
                   *(int *)((int)prim + 0x28));
        return;
      }
      local_10 = *(uint *)((int)prim + 0x14);
      uVar2 = *(uint *)((int)prim + 0x1c);
      local_8 = local_10;
      if ((int)uVar2 <= (int)local_10) {
        local_8 = uVar2;
      }
      iVar1 = *(int *)((int)prim + 0x18);
      iVar3 = *(int *)((int)prim + 0x20);
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
        rdPrimit2_DrawLine(canvas,local_8,y1,local_10,y1,*(int *)((int)prim + 0x24),
                           *(int *)((int)prim + 0x28));
        y1 = y1 + 1;
      } while (y1 <= iVar3);
      return;
    }
    if (iVar1 != 2) {
      return;
    }
  }
  rdPrimit2_DrawLine(canvas,*(int *)((int)prim + 0x14),*(int *)((int)prim + 0x18),
                     *(int *)((int)prim + 0x1c),*(int *)((int)prim + 0x20),
                     *(int *)((int)prim + 0x24),*(int *)((int)prim + 0x28));
  return;
}
#undef local_10
#undef local_8


/* ---- 0x0048ab50  PrimitiveQueue_markDirty ---- */
/* Marks the primitive's bounding rectangle dirty on the last buffer Original name
   PrimitiveQueue_markDirty (the remaster's GrimFandango (Linux): same body as the remaster's
   markDirty(PrimitiveObject *) (the primitive's rectangle, normalised, to
   sputRender_MarkDirtyRect)); was Primitive_Invalidate. */

int __thiscall PrimitiveQueue_markDirty(void *this,void *prim)

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
  
  uVar3 = *(uint *)((int)prim + 0x14);
  uVar1 = *(uint *)((int)prim + 0x1c);
  local_10 = uVar3;
  if ((int)uVar1 <= (int)uVar3) {
    local_10 = uVar1;
  }
  uVar4 = *(uint *)((int)prim + 0x18);
  uVar2 = *(uint *)((int)prim + 0x20);
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
