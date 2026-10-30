/* GRIMFANDANGO.EXE :: primitives.c
 * functions 0x00489550 .. 0x0048abc0 (17 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00489550  Primitives_DrawAll ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void __cdecl Primitives_DrawAll(uint layerMask)

{
  if (g_nPrimitivesHidden == 0) {
    PrimitiveList_Draw(&UINT_008ca0a0,*(void **)((int)g_pRdCurrentCamera + 4),layerMask);
  }
  return;
}
#endif


/* ---- 0x004895d0  Primitives_Hide ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Invalidates every primitive and stops drawing them (movie playback) */

void Primitives_Hide(void)

{
  PrimitiveList_Invalidate(&UINT_008ca0a0,3);
  g_nPrimitivesHidden = 1;
  return;
}
#endif


/* ---- 0x004895f0  Primitives_Show ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void Primitives_Show(void)

{
  g_nPrimitivesHidden = 0;
  return;
}
#endif


/* ---- 0x0048a4b0  Primitive_Construct ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
#endif


/* ---- 0x0048a560  Primitive_AddLine ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
int __thiscall Primitive_AddLine(void *this,int x1,int y1,int x2,int y2,int color,int layer)

{
  int id;
  void *pvVar1;
  
  id = g_nNextPrimitiveId;
  g_nNextPrimitiveId = g_nNextPrimitiveId + 1;
  pvVar1 = PrimitiveList_Append(this,id,layer);
  *(int *)((int)pvVar1 + 0x14) = x1;
  *(int *)((int)pvVar1 + 0x18) = y1;
  *(int *)((int)pvVar1 + 0x1c) = x2;
  *(int *)((int)pvVar1 + 0x20) = y2;
  *(int *)((int)pvVar1 + 0x24) = color;
  return *(int *)((int)pvVar1 + 0xc);
}
#endif


/* ---- 0x0048a5b0  Primitive_AddRect ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
int __thiscall
Primitive_AddRect(void *this,int x1,int y1,int x2,int y2,int color,int filled,int layer)

{
  int id;
  void *pvVar1;
  
  id = g_nNextPrimitiveId;
  g_nNextPrimitiveId = g_nNextPrimitiveId + 1;
  pvVar1 = PrimitiveList_Append(this,id,layer);
  *(undefined4 *)((int)pvVar1 + 8) = 1;
  *(int *)((int)pvVar1 + 0x14) = x1;
  *(int *)((int)pvVar1 + 0x18) = y1;
  *(int *)((int)pvVar1 + 0x1c) = x2;
  *(int *)((int)pvVar1 + 0x20) = y2;
  *(int *)((int)pvVar1 + 0x24) = color;
  *(int *)((int)pvVar1 + 0x2c) = filled;
  return *(int *)((int)pvVar1 + 0xc);
}
#endif


/* ---- 0x0048a600  Primitive_AddPolyline ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
int __thiscall Primitive_AddPolyline(void *this,int count,int *points,int color,int layer)

{
  int *piVar1;
  int id;
  void *pvVar2;
  int *piVar3;
  int iVar4;
  
  id = g_nNextPrimitiveId;
  g_nNextPrimitiveId = g_nNextPrimitiveId + 1;
  iVar4 = count + -1;
  if (0 < iVar4) {
    piVar3 = points + 1;
    do {
      pvVar2 = PrimitiveList_Append(this,id,layer);
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
#endif


/* ---- 0x0048a740  Primitive_Kill ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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
#endif


/* ---- 0x0048a7b0  Primitive_SetColor ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
undefined * __stdcall Primitive_SetColor(int a1,int a2)

{
  void *after;
  void *in_ECX;
  
  for (after = PrimitiveList_FindById(in_ECX,a1,(void *)0x0); after != (void *)0x0;
      after = PrimitiveList_FindById(in_ECX,a1,after)) {
    *(int *)((int)after + 0x24) = a2;
  }
  return (undefined *)0x0;
}
#endif


/* ---- 0x0048a7e0  Primitive_SetLayer ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
undefined * __stdcall Primitive_SetLayer(int a1,int a2)

{
  void *after;
  void *in_ECX;
  
  for (after = PrimitiveList_FindById(in_ECX,a1,(void *)0x0); after != (void *)0x0;
      after = PrimitiveList_FindById(in_ECX,a1,after)) {
    Primitive_Invalidate((int)after);
    if ((a2 != 2) && (a2 != 1)) {
      a2 = 2;
    }
    *(int *)((int)after + 0x10) = a2;
  }
  return (undefined *)0x0;
}
#endif


/* ---- 0x0048a830  Primitive_Offset ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
undefined * __stdcall Primitive_Offset(int a1,int a2,int a3)

{
  void *after;
  void *in_ECX;
  
  for (after = PrimitiveList_FindById(in_ECX,a1,(void *)0x0); after != (void *)0x0;
      after = PrimitiveList_FindById(in_ECX,a1,after)) {
    Primitive_Invalidate((int)after);
    *(int *)((int)after + 0x14) = *(int *)((int)after + 0x14) + a2;
    *(int *)((int)after + 0x20) = *(int *)((int)after + 0x20) + a3;
    *(int *)((int)after + 0x18) = *(int *)((int)after + 0x18) + a3;
    *(int *)((int)after + 0x1c) = *(int *)((int)after + 0x1c) + a2;
  }
  return (undefined *)0x0;
}
#endif


/* ---- 0x0048a8a0  Primitive_MoveTo ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
undefined * __stdcall Primitive_MoveTo(int a1,int a2,int a3)

{
  void *pvVar1;
  void *in_ECX;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0;
  pvVar1 = PrimitiveList_FindById(in_ECX,a1,(void *)0x0);
  if (pvVar1 != (void *)0x0) {
    Primitive_Invalidate((int)pvVar1);
    if (a2 != -1) {
      iVar3 = a2 - *(int *)((int)pvVar1 + 0x14);
      *(int *)((int)pvVar1 + 0x14) = a2;
    }
    if (a3 != -1) {
      iVar2 = a3 - *(int *)((int)pvVar1 + 0x18);
      *(int *)((int)pvVar1 + 0x18) = a3;
    }
    *(int *)((int)pvVar1 + 0x20) = *(int *)((int)pvVar1 + 0x20) + iVar2;
    *(int *)((int)pvVar1 + 0x1c) = *(int *)((int)pvVar1 + 0x1c) + iVar3;
    for (pvVar1 = PrimitiveList_FindById(in_ECX,a1,pvVar1); pvVar1 != (void *)0x0;
        pvVar1 = PrimitiveList_FindById(in_ECX,a1,pvVar1)) {
      Primitive_Invalidate((int)pvVar1);
      *(int *)((int)pvVar1 + 0x14) = *(int *)((int)pvVar1 + 0x14) + iVar3;
      *(int *)((int)pvVar1 + 0x18) = *(int *)((int)pvVar1 + 0x18) + iVar2;
      *(int *)((int)pvVar1 + 0x1c) = *(int *)((int)pvVar1 + 0x1c) + iVar3;
      *(int *)((int)pvVar1 + 0x20) = *(int *)((int)pvVar1 + 0x20) + iVar2;
    }
  }
  return (undefined *)0x0;
}
#endif


/* ---- 0x0048a960  Primitive_SetEnd ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
undefined * __stdcall Primitive_SetEnd(int a1,int a2,int a3)

{
  void *a1_00;
  undefined *puVar1;
  void *in_ECX;
  
  a1_00 = PrimitiveList_FindById(in_ECX,a1,(void *)0x0);
  puVar1 = (undefined *)0x0;
  if (a1_00 != (void *)0x0) {
    Primitive_Invalidate((int)a1_00);
    if (a2 != -1) {
      *(int *)((int)a1_00 + 0x1c) = a2;
    }
    puVar1 = (undefined *)a3;
    if (a3 != -1) {
      *(int *)((int)a1_00 + 0x20) = a3;
    }
  }
  return puVar1;
}
#endif


/* ---- 0x0048a9a0  Primitive_SetSize ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
undefined * __stdcall Primitive_SetSize(int a1,int a2,int a3)

{
  void *a1_00;
  undefined *puVar1;
  void *in_ECX;
  
  a1_00 = PrimitiveList_FindById(in_ECX,a1,(void *)0x0);
  puVar1 = (undefined *)0x0;
  if (a1_00 != (void *)0x0) {
    Primitive_Invalidate((int)a1_00);
    if (a2 != -1) {
      *(int *)((int)a1_00 + 0x1c) = *(int *)((int)a1_00 + 0x14) + a2;
    }
    puVar1 = (undefined *)a3;
    if (a3 != -1) {
      *(int *)((int)a1_00 + 0x20) = *(int *)((int)a1_00 + 0x18) + a3;
    }
  }
  return puVar1;
}
#endif


/* ---- 0x0048aa20  Primitive_Draw ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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

#endif


/* ---- 0x0048ab50  Primitive_Invalidate ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
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

#endif


/* ---- 0x0048abc0  Primitive_ResetIds ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void Primitive_ResetIds(void)

{
  g_nNextPrimitiveId = 1;
  return;
}
#endif

