/* GRIMFANDANGO.EXE :: primitivelist.c
 * functions 0x00489510 .. 0x0048abd0 (10 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00489510  PrimitiveList_StaticConstruct ---- */
/* Static constructor of the global primitive list (init + atexit registration). */

void PrimitiveList_StaticConstruct(void)

{
  PrimitiveList_InitGlobal();
  PrimitiveList_RegisterAtExit();
  return;
}

/* ---- 0x00489520  PrimitiveList_InitGlobal ---- */
/* Initialises the global primitive list (g_dwPrimitiveQ). */

void PrimitiveList_InitGlobal(void)

{
  PrimitiveQueue_Construct(&g_dwPrimitiveQ);
  return;
}

/* ---- 0x00489530  PrimitiveList_RegisterAtExit ---- */
/* Registers PrimitiveList_AtExitClear with atexit (static destructor). */

void __cdecl PrimitiveList_RegisterAtExit(void)

{
  atexit(((unsigned)(uintptr_t)PrimitiveList_AtExitClear));
  return;
}

/* ---- 0x00489540  PrimitiveList_AtExitClear ---- */
/* atexit handler: clears the global primitive list. */

void __cdecl PrimitiveList_AtExitClear(void)

{
  PrimitiveQueue_purge((int *)&g_dwPrimitiveQ);
  return;
}

/* ---- 0x0048a500  PrimitiveQueue_Construct ---- */
/* __fastcall: clears the head and tail of a primitive list. Original name PrimitiveQueue_Construct
   (the remaster's GrimFandango (Linux): same body (head and tail 0)); was PrimitiveList_Init. */

void __fastcall PrimitiveQueue_Construct(undefined4 *primitiveQ)

{
  *primitiveQ = 0;
  primitiveQ[1] = 0;
  return;
}

/* ---- 0x0048a520  PrimitiveQueue_purge ---- */
/* Original name PrimitiveQueue_purge (the remaster's GrimFandango (Linux): same body (free every
   primitive after marking its rectangle dirty, tail 0); called by sputPrimitive_PurgeQueue /
   _Restore / _Shutdown and the at-exit destructor of the queue in both builds); was
   PrimitiveList_Clear. */

void __fastcall PrimitiveQueue_purge(int *primitiveQ)

{
  Primitive *pPVar1;
  
  pPVar1 = (Primitive *)*primitiveQ;
  while (pPVar1 != (Primitive *)0x0) {
    pPVar1 = ((Primitive *)*primitiveQ)->pNext;
    PrimitiveQueue_markDirty(primitiveQ,(Primitive *)*primitiveQ);
    Plat_Free((void *)*primitiveQ);
    *primitiveQ = (int)pPVar1;
  }
  primitiveQ[1] = 0;
  return;
}

/* ---- 0x0048a670  PrimitiveQueue_addObject ---- */
/* Original name PrimitiveQueue_addObject (the remaster's GrimFandango (Linux): same body (new
   primitive record (id, layer) linked at the tail)); was PrimitiveList_Append. */

Primitive * __thiscall PrimitiveQueue_addObject(void *this,int id,int layer)

{
  Primitive *pPVar1;
  uint local_10;
  
  if (*(int *)((int)this + 4) == 0) {
    pPVar1 = Plat_Alloc(0x30);
    if (pPVar1 == (Primitive *)0x0) {
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)this = 0;
    }
    else {
      pPVar1 = PrimitiveObject_Construct(pPVar1,id,0);
      *(Primitive **)((int)this + 4) = pPVar1;
      *(Primitive **)this = pPVar1;
    }
  }
  else {
    pPVar1 = Plat_Alloc(0x30);
    if (pPVar1 == (Primitive *)0x0) {
      pPVar1 = (Primitive *)0x0;
    }
    else {
      pPVar1 = PrimitiveObject_Construct(pPVar1,id,0);
    }
    **(undefined4 **)((int)this + 4) = pPVar1;
    *(int **)(**(int **)((int)this + 4) + 4) = *(int **)((int)this + 4);
    *(undefined4 *)((int)this + 4) = **(undefined4 **)((int)this + 4);
  }
  if ((layer != 2) && (layer != 1)) {
    layer = 2;
  }
  *(int *)(*(int *)((int)this + 4) + 0x10) = layer;
  pPVar1 = *(Primitive **)((int)this + 4);
  return pPVar1;
}

/* ---- 0x0048a9f0  PrimitiveQueue_draw ---- */
/* Original name PrimitiveQueue_draw (the remaster's GrimFandango (Linux): same body (drawPrimitive
   for every primitive whose layer +0x10 is in the mask)); was PrimitiveList_Draw. */

void __thiscall PrimitiveQueue_draw(void *this,void *canvas,uint layerMask)

{
  Primitive *prim;
  
  for (prim = *(Primitive **)this; prim != (Primitive *)0x0; prim = prim->pNext) {
    if ((prim->nLayer & layerMask) != 0) {
      PrimitiveQueue_drawPrimitive(prim,canvas);
    }
  }
  return;
}

/* ---- 0x0048ab20  PrimitiveQueue_markAllDirty ---- */
/* Original name PrimitiveQueue_markAllDirty (the remaster's GrimFandango (Linux): same body (mark
   the rectangle of every primitive whose layer is in the mask dirty)); was
   PrimitiveList_Invalidate. */

undefined * __thiscall PrimitiveQueue_markAllDirty(void *this,int a1)

{
  Primitive *prim;
  undefined *in_EAX;
  
  for (prim = *(Primitive **)this; prim != (Primitive *)0x0; prim = prim->pNext) {
    if ((prim->nLayer & a1) != 0) {
      in_EAX = (undefined *)PrimitiveQueue_markDirty(this,prim);
    }
  }
  return in_EAX;
}

/* ---- 0x0048abd0  PrimitiveQueue_findPrimitive ---- */
/* Original name PrimitiveQueue_findPrimitive (the remaster's GrimFandango (Linux): same body (the
   next primitive with the id after the given one, or from the head)); was PrimitiveList_FindById.
    */

Primitive * __thiscall PrimitiveQueue_findPrimitive(void *this,int id,Primitive *after)

{
  Primitive *pPVar1;
  
  if (after == (Primitive *)0x0) {
    pPVar1 = *(Primitive **)this;
  }
  else {
    pPVar1 = after->pNext;
  }
  for (; (pPVar1 != (Primitive *)0x0 && (pPVar1->nId != id)); pPVar1 = pPVar1->pNext) {
  }
  return pPVar1;
}
