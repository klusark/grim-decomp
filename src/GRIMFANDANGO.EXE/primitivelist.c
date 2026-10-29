/* GRIMFANDANGO.EXE :: primitivelist.c
 * functions 0x0048a520 .. 0x0048abd0 (5 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048a520  PrimitiveList_Clear ---- */
void __fastcall PrimitiveList_Clear(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  while (iVar1 != 0) {
    iVar1 = *(int *)*param_1;
    Primitive_Invalidate(*param_1);
    Plat_Free((void *)*param_1);
    *param_1 = iVar1;
  }
  param_1[1] = 0;
  return;
}

/* ---- 0x0048a670  PrimitiveList_Append ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
void * __thiscall PrimitiveList_Append(void *this,int id,int layer)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  undefined4 uVar2;
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define pcStack_8 (*(code **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0xffffffff;
  pcStack_8 = FUN_004d6046;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_c;
  if (*(int *)((int)this + 4) == 0) {
    pvVar1 = Plat_Alloc(0x30);
    local_4 = 0;
    if (pvVar1 == (void *)0x0) {
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)this = 0;
    }
    else {
      Primitive_Construct(pvVar1,id,0);
      *(undefined4 *)((int)this + 4) = extraout_EAX;
      *(undefined4 *)this = extraout_EAX;
    }
  }
  else {
    pvVar1 = Plat_Alloc(0x30);
    local_4 = 1;
    if (pvVar1 == (void *)0x0) {
      uVar2 = 0;
    }
    else {
      Primitive_Construct(pvVar1,id,0);
      uVar2 = extraout_EAX_00;
    }
    **(undefined4 **)((int)this + 4) = uVar2;
    *(int **)(**(int **)((int)this + 4) + 4) = *(int **)((int)this + 4);
    *(undefined4 *)((int)this + 4) = **(undefined4 **)((int)this + 4);
  }
  if ((layer != 2) && (layer != 1)) {
    layer = 2;
  }
  *(int *)(*(int *)((int)this + 4) + 0x10) = layer;
  pvVar1 = *(void **)((int)this + 4);
  *unaff_FS_OFFSET = local_c;
  return pvVar1;
}
#undef local_10
#undef local_4
#undef local_c
#undef pcStack_8

#endif


/* ---- 0x0048a9f0  PrimitiveList_Draw ---- */
void __thiscall PrimitiveList_Draw(void *this,void *canvas,uint layerMask)

{
  undefined4 *prim;
  
  for (prim = *(undefined4 **)this; prim != (undefined4 *)0x0; prim = (undefined4 *)*prim) {
    if ((prim[4] & layerMask) != 0) {
      Primitive_Draw(prim,canvas);
    }
  }
  return;
}

/* ---- 0x0048ab20  PrimitiveList_Invalidate ---- */
undefined * __thiscall PrimitiveList_Invalidate(void *this,int a1)

{
  undefined4 *a1_00;
  undefined *in_EAX;
  
  for (a1_00 = *(undefined4 **)this; a1_00 != (undefined4 *)0x0; a1_00 = (undefined4 *)*a1_00) {
    if ((a1_00[4] & a1) != 0) {
      in_EAX = Primitive_Invalidate((int)a1_00);
    }
  }
  return in_EAX;
}

/* ---- 0x0048abd0  PrimitiveList_FindById ---- */
void * __thiscall PrimitiveList_FindById(void *this,int id,void *after)

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
