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
  atexit(PrimitiveList_AtExitClear);
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

void __fastcall PrimitiveQueue_Construct(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

/* ---- 0x0048a520  PrimitiveQueue_purge ---- */
/* Original name PrimitiveQueue_purge (the remaster's GrimFandango (Linux): same body (free every
   primitive after marking its rectangle dirty, tail 0); called by sputPrimitive_PurgeQueue /
   _Restore / _Shutdown and the at-exit destructor of the queue in both builds); was
   PrimitiveList_Clear. */

void __fastcall PrimitiveQueue_purge(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  while (iVar1 != 0) {
    iVar1 = *(int *)*param_1;
    PrimitiveQueue_markDirty(param_1,(int *)*param_1);
    Plat_Free((void *)*param_1);
    *param_1 = iVar1;
  }
  param_1[1] = 0;
  return;
}

/* ---- 0x0048a670  PrimitiveQueue_addObject ---- */
/* Original name PrimitiveQueue_addObject (the remaster's GrimFandango (Linux): same body (new
   primitive record (id, layer) linked at the tail)); was PrimitiveList_Append. */

void * __thiscall PrimitiveQueue_addObject(void *this,int id,int layer)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  
  if (*(int *)((int)this + 4) == 0) {
    pvVar1 = Plat_Alloc(0x30);
    if (pvVar1 == (void *)0x0) {
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)this = 0;
    }
    else {
      pvVar1 = PrimitiveObject_Construct(pvVar1,id,0);
      *(void **)((int)this + 4) = pvVar1;
      *(void **)this = pvVar1;
    }
  }
  else {
    pvVar1 = Plat_Alloc(0x30);
    if (pvVar1 == (void *)0x0) {
      pvVar1 = (void *)0x0;
    }
    else {
      pvVar1 = PrimitiveObject_Construct(pvVar1,id,0);
    }
    **(undefined4 **)((int)this + 4) = pvVar1;
    *(int **)(**(int **)((int)this + 4) + 4) = *(int **)((int)this + 4);
    *(undefined4 *)((int)this + 4) = **(undefined4 **)((int)this + 4);
  }
  if ((layer != 2) && (layer != 1)) {
    layer = 2;
  }
  *(int *)(*(int *)((int)this + 4) + 0x10) = layer;
  pvVar1 = *(void **)((int)this + 4);
  return pvVar1;
}
#undef local_10


/* ---- 0x0048a9f0  PrimitiveQueue_draw ---- */
/* Original name PrimitiveQueue_draw (the remaster's GrimFandango (Linux): same body (drawPrimitive
   for every primitive whose layer +0x10 is in the mask)); was PrimitiveList_Draw. */

void __thiscall PrimitiveQueue_draw(void *this,void *canvas,uint layerMask)

{
  undefined4 *prim;
  
  for (prim = *(undefined4 **)this; prim != (undefined4 *)0x0; prim = (undefined4 *)*prim) {
    if ((prim[4] & layerMask) != 0) {
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
  undefined4 *prim;
  undefined *in_EAX;
  
  for (prim = *(undefined4 **)this; prim != (undefined4 *)0x0; prim = (undefined4 *)*prim) {
    if ((prim[4] & a1) != 0) {
      in_EAX = (undefined *)PrimitiveQueue_markDirty(this,prim);
    }
  }
  return in_EAX;
}

/* ---- 0x0048abd0  PrimitiveQueue_findPrimitive ---- */
/* Original name PrimitiveQueue_findPrimitive (the remaster's GrimFandango (Linux): same body (the
   next primitive with the id after the given one, or from the head)); was PrimitiveList_FindById.
    */

void * __thiscall PrimitiveQueue_findPrimitive(void *this,int id,void *after)

{
  undefined4 *puVar1;
  
  if (after == (void *)0x0) {
    puVar1 = *(undefined4 **)this;
  }
  else {
    puVar1 = *(undefined4 **)after;
  }
  for (; (puVar1 != (undefined4 *)0x0 && (puVar1[3] != id)); puVar1 = (undefined4 *)*puVar1) {
  }
  return puVar1;
}
