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
/* Initialises the global primitive list (UINT_008ca0a0). */

void PrimitiveList_InitGlobal(void)

{
  PrimitiveList_Init(&UINT_008ca0a0);
  return;
}

/* ---- 0x00489530  PrimitiveList_RegisterAtExit ---- */
/* Registers PrimitiveList_AtExitClear with atexit (static destructor). */

void PrimitiveList_RegisterAtExit(void)

{
  atexit(PrimitiveList_AtExitClear);
  return;
}

/* ---- 0x00489540  PrimitiveList_AtExitClear ---- */
/* atexit handler: clears the global primitive list. */

void PrimitiveList_AtExitClear(void)

{
  PrimitiveList_Clear((int *)&UINT_008ca0a0);
  return;
}

/* ---- 0x0048a500  PrimitiveList_Init ---- */
/* __fastcall: clears the head and tail of a primitive list. */

void __fastcall PrimitiveList_Init(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

/* ---- 0x0048a520  PrimitiveList_Clear ---- */
void __fastcall PrimitiveList_Clear(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  while (iVar1 != 0) {
    iVar1 = *(int *)*param_1;
    ((code *)Primitive_Invalidate)(*param_1);
    Plat_Free((void *)*param_1);
    *param_1 = iVar1;
  }
  param_1[1] = 0;
  return;
}

/* ---- 0x0048a670  PrimitiveList_Append ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
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
  undefined4 *prim;
  undefined *in_EAX;
  
  for (prim = *(undefined4 **)this; prim != (undefined4 *)0x0; prim = (undefined4 *)*prim) {
    if ((prim[4] & a1) != 0) {
      in_EAX = (undefined *)Primitive_Invalidate(this,prim);
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
