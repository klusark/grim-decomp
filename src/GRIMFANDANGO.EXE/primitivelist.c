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
undefined4 __thiscall PrimitiveList_Append(void *this,int a1,int a2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 uVar1;
  void *pvVar2;
  undefined4 *puVar3;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_c (*(undefined4 *)(_frame + (0x20 - 0xc)))
  #define pcStack_8 (*(code **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0xffffffff;
  pcStack_8 = FUN_004d6046;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  if (*(int *)((int)this + 4) == 0) {
    pvVar2 = Plat_Alloc(0x30);
    local_4 = 0;
    if (pvVar2 == (void *)0x0) {
      *(undefined4 *)((int)this + 4) = 0;
      *(undefined4 *)this = 0;
    }
    else {
      puVar3 = Primitive_Construct(pvVar2,a1,0);
      *(undefined4 **)((int)this + 4) = puVar3;
      *(undefined4 **)this = puVar3;
    }
  }
  else {
    pvVar2 = Plat_Alloc(0x30);
    local_4 = 1;
    if (pvVar2 == (void *)0x0) {
      puVar3 = (undefined4 *)0x0;
    }
    else {
      puVar3 = Primitive_Construct(pvVar2,a1,0);
    }
    **(undefined4 **)((int)this + 4) = puVar3;
    *(int **)(**(int **)((int)this + 4) + 4) = *(int **)((int)this + 4);
    *(undefined4 *)((int)this + 4) = **(undefined4 **)((int)this + 4);
  }
  if ((a2 != 2) && (a2 != 1)) {
    a2 = 2;
  }
  *(int *)(*(int *)((int)this + 4) + 0x10) = a2;
  uVar1 = *(undefined4 *)((int)this + 4);
  *unaff_FS_OFFSET = local_c;
  return uVar1;
}
#undef local_4
#undef local_c
#undef pcStack_8


/* ---- 0x0048a9f0  PrimitiveList_Draw ---- */
undefined4 __thiscall PrimitiveList_Draw(void *this,int a1,int a2)

{
  undefined4 *a1_00;
  undefined4 in_EAX;
  
  for (a1_00 = *(undefined4 **)this; a1_00 != (undefined4 *)0x0; a1_00 = (undefined4 *)*a1_00) {
    if ((a1_00[4] & a2) != 0) {
      in_EAX = Primitive_Draw((int)a1_00,a1);
    }
  }
  return in_EAX;
}

/* ---- 0x0048ab20  PrimitiveList_Invalidate ---- */
undefined4 __thiscall PrimitiveList_Invalidate(void *this,int a1)

{
  undefined4 *a1_00;
  undefined4 in_EAX;
  
  for (a1_00 = *(undefined4 **)this; a1_00 != (undefined4 *)0x0; a1_00 = (undefined4 *)*a1_00) {
    if ((a1_00[4] & a1) != 0) {
      in_EAX = Primitive_Invalidate((int)a1_00);
    }
  }
  return in_EAX;
}

/* ---- 0x0048abd0  PrimitiveList_FindById ---- */
undefined4 __stdcall PrimitiveList_FindById(int a1,int a2)

{
  undefined4 *puVar1;
  undefined4 *in_ECX;
  
  if (a2 == 0) {
    puVar1 = (undefined4 *)*in_ECX;
  }
  else {
    puVar1 = *(undefined4 **)a2;
  }
  for (; (puVar1 != (undefined4 *)0x0 && (puVar1[3] != a1)); puVar1 = (undefined4 *)*puVar1) {
  }
  return puVar1;
}
