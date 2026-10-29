/* GRIMFANDANGO.EXE :: primitives.c
 * functions 0x00489550 .. 0x0048abc0 (23 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00489550  Primitives_DrawAll ---- */
void __cdecl Primitives_DrawAll(uint layerMask)

{
  if (g_nPrimitivesHidden == 0) {
    PrimitiveList_Draw(&UINT_008ca0a0,*(void **)((int)g_pRdCurrentCamera + 4),layerMask);
  }
  return;
}

/* ---- 0x004895d0  Primitives_Hide ---- */
/* Invalidates every primitive and stops drawing them (movie playback) */

void Primitives_Hide(void)

{
  PrimitiveList_Invalidate(&UINT_008ca0a0,3);
  g_nPrimitivesHidden = 1;
  return;
}

/* ---- 0x004895f0  Primitives_Show ---- */
void Primitives_Show(void)

{
  g_nPrimitivesHidden = 0;
  return;
}

/* ---- 0x00489600  FUN_00489600 ---- */
undefined4 FUN_00489600(code *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  code *pcVar2;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  pcVar2 = param_1;
  local_4 = 0;
  for (puVar1 = (undefined4 *)UINT_008ca0a0; puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    local_4 = local_4 + 1;
  }
  (*param_1)(&local_4,4);
  for (puVar1 = (undefined4 *)UINT_008ca0a0; puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    param_1 = (code *)puVar1[2];
    (*pcVar2)(&param_1,4);
    (*pcVar2)(puVar1 + 3,4);
    (*pcVar2)(puVar1 + 4,4);
    (*pcVar2)(puVar1 + 5,8);
    (*pcVar2)(puVar1 + 7,8);
    (*pcVar2)(puVar1 + 9,4);
    (*pcVar2)(puVar1 + 10,4);
    (*pcVar2)(puVar1 + 0xb,4);
  }
  return 0;
}
#undef local_4


/* ---- 0x004896b0  FUN_004896b0 ---- */
undefined4 FUN_004896b0(code *param_1)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  code *pcVar1;
  void *pvVar2;
  #define local_28 (*(int *)(_frame + (0x40 - 0x28)))
  #define iStack_24 (*(int *)(_frame + (0x40 - 0x24)))
  #define uStack_20 (*(undefined4 *)(_frame + (0x40 - 0x20)))
  #define uStack_1c (*(undefined4 *)(_frame + (0x40 - 0x1c)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x40 - 0x18)))
  #define uStack_14 (*(undefined4 *)(_frame + (0x40 - 0x14)))
  #define uStack_10 (*(undefined4 *)(_frame + (0x40 - 0x10)))
  #define uStack_c (*(undefined4 *)(_frame + (0x40 - 0xc)))
  #define uStack_8 (*(undefined4 *)(_frame + (0x40 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x40 - 0x4)))
  
  PrimitiveList_Clear((int *)&UINT_008ca0a0);
  pcVar1 = param_1;
  (*param_1)(&local_28,4);
  while (local_28 != 0) {
    local_28 = local_28 + -1;
    uStack_10 = 0;
    uStack_c = 0;
    uStack_8 = 0;
    uStack_4 = 0;
    (*pcVar1)(&uStack_20,4);
    (*pcVar1)(&param_1,4);
    (*pcVar1)(&iStack_24,4);
    (*pcVar1)(&uStack_10,8);
    (*pcVar1)(&uStack_8,8);
    (*pcVar1)(&uStack_1c,4);
    (*pcVar1)(&uStack_18,4);
    (*pcVar1)(&uStack_14,4);
    pvVar2 = PrimitiveList_Append(&UINT_008ca0a0,(int)param_1,iStack_24);
    if (pvVar2 != (void *)0x0) {
      *(undefined4 *)((int)pvVar2 + 8) = uStack_20;
      *(undefined4 *)((int)pvVar2 + 0x14) = uStack_10;
      *(undefined4 *)((int)pvVar2 + 0x18) = uStack_c;
      *(undefined4 *)((int)pvVar2 + 0x1c) = uStack_8;
      *(undefined4 *)((int)pvVar2 + 0x20) = uStack_4;
      *(undefined4 *)((int)pvVar2 + 0x24) = uStack_1c;
      *(undefined4 *)((int)pvVar2 + 0x28) = uStack_18;
      *(undefined4 *)((int)pvVar2 + 0x2c) = uStack_14;
    }
    g_nNextPrimitiveId = (int)(param_1 + 1);
  }
  return 0;
}
#undef iStack_24
#undef local_28
#undef uStack_10
#undef uStack_14
#undef uStack_18
#undef uStack_1c
#undef uStack_20
#undef uStack_4
#undef uStack_8
#undef uStack_c


/* ---- 0x004897d0  FUN_004897d0 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004897d0(void)

{
  _DAT_008ca0b0 = 0;
  if (UINT_008ca0a8 != 0) {
    UINT_008ca0a8 = 0;
  }
  return;
}

/* ---- 0x004897f0  FUN_004897f0 ---- */
undefined4 FUN_004897f0(void)

{
  if (UINT_008ca0ac != 0) {
    return 1;
  }
  Lua_OpenEngineLib(&PTR_s_DrawLine_004e8398,UINT_004e83c8);
  UINT_008ca0ac = 1;
  return 0;
}

/* ---- 0x00489820  FUN_00489820 ---- */
void FUN_00489820(void)

{
  PrimitiveList_Clear((int *)&UINT_008ca0a0);
  UINT_008ca0ac = 0;
  return;
}

/* ---- 0x0048a4b0  Primitive_Construct ---- */
/* 0x30-byte primitive {next, prev, type (0 line, 1 rect, 2 polyline segment), id, layer, x1, y1,
   x2, y2, color, ?, filled} */

void __thiscall Primitive_Construct(void *this,int id,int unused)

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
  return;
}

/* ---- 0x0048a500  FUN_0048a500 ---- */
void __fastcall FUN_0048a500(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

/* ---- 0x0048a560  Primitive_AddLine ---- */
int __stdcall Primitive_AddLine(int x1,int y1,int x2,int y2,int color,int layer)

{
  int id;
  void *pvVar1;
  void *in_ECX;
  
  id = g_nNextPrimitiveId;
  g_nNextPrimitiveId = g_nNextPrimitiveId + 1;
  pvVar1 = PrimitiveList_Append(in_ECX,id,layer);
  *(int *)((int)pvVar1 + 0x14) = x1;
  *(int *)((int)pvVar1 + 0x18) = y1;
  *(int *)((int)pvVar1 + 0x1c) = x2;
  *(int *)((int)pvVar1 + 0x20) = y2;
  *(int *)((int)pvVar1 + 0x24) = color;
  return *(int *)((int)pvVar1 + 0xc);
}

/* ---- 0x0048a5b0  Primitive_AddRect ---- */
int __stdcall Primitive_AddRect(int x1,int y1,int x2,int y2,int color,int filled,int layer)

{
  int id;
  void *pvVar1;
  void *in_ECX;
  
  id = g_nNextPrimitiveId;
  g_nNextPrimitiveId = g_nNextPrimitiveId + 1;
  pvVar1 = PrimitiveList_Append(in_ECX,id,layer);
  *(undefined4 *)((int)pvVar1 + 8) = 1;
  *(int *)((int)pvVar1 + 0x14) = x1;
  *(int *)((int)pvVar1 + 0x18) = y1;
  *(int *)((int)pvVar1 + 0x1c) = x2;
  *(int *)((int)pvVar1 + 0x20) = y2;
  *(int *)((int)pvVar1 + 0x24) = color;
  *(int *)((int)pvVar1 + 0x2c) = filled;
  return *(int *)((int)pvVar1 + 0xc);
}

/* ---- 0x0048a600  Primitive_AddPolyline ---- */
int __stdcall Primitive_AddPolyline(int count,int *points,int color,int layer)

{
  int *piVar1;
  int id;
  void *pvVar2;
  void *in_ECX;
  int *piVar3;
  int iVar4;
  
  id = g_nNextPrimitiveId;
  g_nNextPrimitiveId = g_nNextPrimitiveId + 1;
  iVar4 = count + -1;
  if (0 < iVar4) {
    piVar3 = points + 1;
    do {
      pvVar2 = PrimitiveList_Append(in_ECX,id,layer);
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

/* ---- 0x0048a740  Primitive_Kill ---- */
void __thiscall Primitive_Kill(void *this,int id)

{
  int *piVar1;
  int *p;
  
  p = *(int **)this;
  while (p != (int *)0x0) {
    if (p[3] == id) {
      if ((int *)p[1] != (int *)0x0) {
        *(int *)p[1] = *p;
      }
      if (*p != 0) {
        *(int *)(*p + 4) = p[1];
      }
      if (*(int **)((int)this + 4) == p) {
        *(int *)((int)this + 4) = p[1];
      }
      if (p == *(int **)this) {
        *(int *)this = **(int **)this;
      }
      piVar1 = (int *)*p;
      Primitive_Invalidate((int)p);
      Plat_Free(p);
      p = piVar1;
    }
    else {
      p = (int *)*p;
    }
  }
  return;
}

/* ---- 0x0048a7b0  Primitive_SetColor ---- */
undefined * __stdcall Primitive_SetColor(int a1,int a2)

{
  undefined *a2_00;
  
  for (a2_00 = PrimitiveList_FindById(a1,0); a2_00 != (undefined *)0x0;
      a2_00 = PrimitiveList_FindById(a1,(int)a2_00)) {
    *(int *)(a2_00 + 0x24) = a2;
  }
  return (undefined *)0x0;
}

/* ---- 0x0048a7e0  Primitive_SetLayer ---- */
undefined * __stdcall Primitive_SetLayer(int a1,int a2)

{
  undefined *a1_00;
  
  for (a1_00 = PrimitiveList_FindById(a1,0); a1_00 != (undefined *)0x0;
      a1_00 = PrimitiveList_FindById(a1,(int)a1_00)) {
    Primitive_Invalidate((int)a1_00);
    if ((a2 != 2) && (a2 != 1)) {
      a2 = 2;
    }
    *(int *)(a1_00 + 0x10) = a2;
  }
  return (undefined *)0x0;
}

/* ---- 0x0048a830  Primitive_Offset ---- */
undefined * __stdcall Primitive_Offset(int a1,int a2,int a3)

{
  undefined *a1_00;
  
  for (a1_00 = PrimitiveList_FindById(a1,0); a1_00 != (undefined *)0x0;
      a1_00 = PrimitiveList_FindById(a1,(int)a1_00)) {
    Primitive_Invalidate((int)a1_00);
    *(int *)(a1_00 + 0x14) = *(int *)(a1_00 + 0x14) + a2;
    *(int *)(a1_00 + 0x20) = *(int *)(a1_00 + 0x20) + a3;
    *(int *)(a1_00 + 0x18) = *(int *)(a1_00 + 0x18) + a3;
    *(int *)(a1_00 + 0x1c) = *(int *)(a1_00 + 0x1c) + a2;
  }
  return (undefined *)0x0;
}

/* ---- 0x0048a8a0  Primitive_MoveTo ---- */
undefined * __stdcall Primitive_MoveTo(int a1,int a2,int a3)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0;
  puVar1 = PrimitiveList_FindById(a1,0);
  if (puVar1 != (undefined *)0x0) {
    Primitive_Invalidate((int)puVar1);
    if (a2 != -1) {
      iVar3 = a2 - *(int *)(puVar1 + 0x14);
      *(int *)(puVar1 + 0x14) = a2;
    }
    if (a3 != -1) {
      iVar2 = a3 - *(int *)(puVar1 + 0x18);
      *(int *)(puVar1 + 0x18) = a3;
    }
    *(int *)(puVar1 + 0x20) = *(int *)(puVar1 + 0x20) + iVar2;
    *(int *)(puVar1 + 0x1c) = *(int *)(puVar1 + 0x1c) + iVar3;
    for (puVar1 = PrimitiveList_FindById(a1,(int)puVar1); puVar1 != (undefined *)0x0;
        puVar1 = PrimitiveList_FindById(a1,(int)puVar1)) {
      Primitive_Invalidate((int)puVar1);
      *(int *)(puVar1 + 0x14) = *(int *)(puVar1 + 0x14) + iVar3;
      *(int *)(puVar1 + 0x18) = *(int *)(puVar1 + 0x18) + iVar2;
      *(int *)(puVar1 + 0x1c) = *(int *)(puVar1 + 0x1c) + iVar3;
      *(int *)(puVar1 + 0x20) = *(int *)(puVar1 + 0x20) + iVar2;
    }
  }
  return (undefined *)0x0;
}

/* ---- 0x0048a960  Primitive_SetEnd ---- */
undefined * __stdcall Primitive_SetEnd(int a1,int a2,int a3)

{
  undefined *a1_00;
  undefined *puVar1;
  
  a1_00 = PrimitiveList_FindById(a1,0);
  puVar1 = (undefined *)0x0;
  if (a1_00 != (undefined *)0x0) {
    Primitive_Invalidate((int)a1_00);
    if (a2 != -1) {
      *(int *)(a1_00 + 0x1c) = a2;
    }
    puVar1 = (undefined *)a3;
    if (a3 != -1) {
      *(int *)(a1_00 + 0x20) = a3;
    }
  }
  return puVar1;
}

/* ---- 0x0048a9a0  Primitive_SetSize ---- */
undefined * __stdcall Primitive_SetSize(int a1,int a2,int a3)

{
  undefined *a1_00;
  undefined *puVar1;
  
  a1_00 = PrimitiveList_FindById(a1,0);
  puVar1 = (undefined *)0x0;
  if (a1_00 != (undefined *)0x0) {
    Primitive_Invalidate((int)a1_00);
    if (a2 != -1) {
      *(int *)(a1_00 + 0x1c) = *(int *)(a1_00 + 0x14) + a2;
    }
    puVar1 = (undefined *)a3;
    if (a3 != -1) {
      *(int *)(a1_00 + 0x20) = *(int *)(a1_00 + 0x18) + a3;
    }
  }
  return puVar1;
}

/* ---- 0x0048aa20  Primitive_Draw ---- */
void __stdcall Primitive_Draw(void *prim,void *canvas)

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
        rdPrimit2_DrawRect(canvas,*(int *)((int)prim + 0x14),*(int *)((int)prim + 0x18),
                           *(int *)((int)prim + 0x1c),*(int *)((int)prim + 0x20),
                           *(int *)((int)prim + 0x24),*(int *)((int)prim + 0x28));
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


/* ---- 0x0048ab50  Primitive_Invalidate ---- */
/* Marks the primitive's bounding rectangle dirty on the last buffer */

undefined * __stdcall Primitive_Invalidate(int a1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined *extraout_EAX;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar3 = *(uint *)(a1 + 0x14);
  uVar1 = *(uint *)(a1 + 0x1c);
  local_10 = uVar3;
  if ((int)uVar1 <= (int)uVar3) {
    local_10 = uVar1;
  }
  uVar4 = *(uint *)(a1 + 0x18);
  uVar2 = *(uint *)(a1 + 0x20);
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
  Render_InvalidateRectLastBuffer((int *)&local_10,0);
  return extraout_EAX;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0048abc0  Primitive_ResetIds ---- */
void Primitive_ResetIds(void)

{
  g_nNextPrimitiveId = 1;
  return;
}
