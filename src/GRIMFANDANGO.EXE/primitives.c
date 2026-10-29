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
    PrimitiveList_Draw(&DAT_008ca0a0,*(int *)((int)g_pRdCurrentCamera + 4),layerMask);
  }
  return;
}

/* ---- 0x004895d0  Primitives_Hide ---- */
/* Invalidates every primitive and stops drawing them (movie playback) */

void Primitives_Hide(void)

{
  PrimitiveList_Invalidate(&DAT_008ca0a0,3);
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
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  pcVar2 = param_1;
  local_4 = 0;
  for (puVar1 = DAT_008ca0a0; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    local_4 = local_4 + 1;
  }
  (*param_1)(&local_4,4);
  for (puVar1 = DAT_008ca0a0; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
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
  int iVar2;
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
  
  ((code *)PrimitiveList_Clear)();
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
    iVar2 = PrimitiveList_Append(&DAT_008ca0a0,(int)param_1,iStack_24);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 8) = uStack_20;
      *(undefined4 *)(iVar2 + 0x14) = uStack_10;
      *(undefined4 *)(iVar2 + 0x18) = uStack_c;
      *(undefined4 *)(iVar2 + 0x1c) = uStack_8;
      *(undefined4 *)(iVar2 + 0x20) = uStack_4;
      *(undefined4 *)(iVar2 + 0x24) = uStack_1c;
      *(undefined4 *)(iVar2 + 0x28) = uStack_18;
      *(undefined4 *)(iVar2 + 0x2c) = uStack_14;
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
  if (DAT_008ca0a8 != 0) {
    DAT_008ca0a8 = 0;
  }
  return;
}

/* ---- 0x004897f0  FUN_004897f0 ---- */
undefined4 FUN_004897f0(void)

{
  if (DAT_008ca0ac != 0) {
    return 1;
  }
  Lua_OpenEngineLib(&PTR_s_DrawLine_004e8398,DAT_004e83c8);
  DAT_008ca0ac = 1;
  return 0;
}

/* ---- 0x00489820  FUN_00489820 ---- */
void FUN_00489820(void)

{
  ((code *)PrimitiveList_Clear)();
  DAT_008ca0ac = 0;
  return;
}

/* ---- 0x0048a4b0  Primitive_Construct ---- */
/* 0x30-byte primitive {next, prev, type (0 line, 1 rect, 2 polyline segment), id, layer, x1, y1,
   x2, y2, color, ?, filled} */

undefined4 * __thiscall Primitive_Construct(void *this,int a1,int a2)

{
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)((int)this + 0x20) = 0;
  *(int *)((int)this + 8) = a2;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(int *)((int)this + 0xc) = a1;
  *(undefined4 *)((int)this + 0x24) = 0;
  *(undefined4 *)((int)this + 0x28) = 0xffffffff;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0x18) = 0;
  *(undefined4 *)((int)this + 0x1c) = 0;
  *(undefined4 *)((int)this + 0x20) = *(undefined4 *)((int)this + 0x18);
  *(undefined4 *)((int)this + 0x10) = 2;
  return this;
}

/* ---- 0x0048a500  FUN_0048a500 ---- */
void __fastcall FUN_0048a500(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

/* ---- 0x0048a560  Primitive_AddLine ---- */
undefined4 __stdcall Primitive_AddLine(int a1,int a2,int a3,int a4,int a5,int a6)

{
  int iVar1;
  void *in_ECX;
  
  iVar1 = g_nNextPrimitiveId;
  g_nNextPrimitiveId = g_nNextPrimitiveId + 1;
  iVar1 = PrimitiveList_Append(in_ECX,iVar1,a6);
  *(int *)(iVar1 + 0x14) = a1;
  *(int *)(iVar1 + 0x18) = a2;
  *(int *)(iVar1 + 0x1c) = a3;
  *(int *)(iVar1 + 0x20) = a4;
  *(int *)(iVar1 + 0x24) = a5;
  return *(undefined4 *)(iVar1 + 0xc);
}

/* ---- 0x0048a5b0  Primitive_AddRect ---- */
undefined4 __stdcall Primitive_AddRect(int a1,int a2,int a3,int a4,int a5,int a6,int a7)

{
  int iVar1;
  void *in_ECX;
  
  iVar1 = g_nNextPrimitiveId;
  g_nNextPrimitiveId = g_nNextPrimitiveId + 1;
  iVar1 = PrimitiveList_Append(in_ECX,iVar1,a7);
  *(undefined4 *)(iVar1 + 8) = 1;
  *(int *)(iVar1 + 0x14) = a1;
  *(int *)(iVar1 + 0x18) = a2;
  *(int *)(iVar1 + 0x1c) = a3;
  *(int *)(iVar1 + 0x20) = a4;
  *(int *)(iVar1 + 0x24) = a5;
  *(int *)(iVar1 + 0x2c) = a6;
  return *(undefined4 *)(iVar1 + 0xc);
}

/* ---- 0x0048a600  Primitive_AddPolyline ---- */
int __stdcall Primitive_AddPolyline(int a1,int a2,int a3,int a4)

{
  undefined4 *puVar1;
  int a1_00;
  int iVar2;
  void *in_ECX;
  undefined4 *puVar3;
  int iVar4;
  
  a1_00 = g_nNextPrimitiveId;
  g_nNextPrimitiveId = g_nNextPrimitiveId + 1;
  iVar4 = a1 + -1;
  if (0 < iVar4) {
    puVar3 = (undefined4 *)(a2 + 4);
    do {
      iVar2 = PrimitiveList_Append(in_ECX,a1_00,a4);
      *(undefined4 *)(iVar2 + 8) = 2;
      *(undefined4 *)(iVar2 + 0x14) = puVar3[-1];
      *(undefined4 *)(iVar2 + 0x18) = *puVar3;
      *(undefined4 *)(iVar2 + 0x1c) = puVar3[1];
      puVar1 = puVar3 + 2;
      puVar3 = puVar3 + 2;
      *(undefined4 *)(iVar2 + 0x20) = *puVar1;
      iVar4 = iVar4 + -1;
      *(int *)(iVar2 + 0x24) = a3;
    } while (iVar4 != 0);
  }
  return a1_00;
}

/* ---- 0x0048a740  Primitive_Kill ---- */
undefined4 __thiscall Primitive_Kill(void *this,int a1)

{
  int *piVar1;
  int *p;
  undefined4 in_EAX;
  undefined4 extraout_EAX;
  
  p = *(int **)this;
  while (p != (int *)0x0) {
    if (p[3] == a1) {
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
      in_EAX = extraout_EAX;
    }
    else {
      p = (int *)*p;
    }
  }
  return in_EAX;
}

/* ---- 0x0048a7b0  Primitive_SetColor ---- */
undefined4 __stdcall Primitive_SetColor(int a1,int a2)

{
  int a2_00;
  
  for (a2_00 = PrimitiveList_FindById(a1,0); a2_00 != 0; a2_00 = PrimitiveList_FindById(a1,a2_00)) {
    *(int *)(a2_00 + 0x24) = a2;
  }
  return 0;
}

/* ---- 0x0048a7e0  Primitive_SetLayer ---- */
undefined4 __stdcall Primitive_SetLayer(int a1,int a2)

{
  int a1_00;
  
  for (a1_00 = PrimitiveList_FindById(a1,0); a1_00 != 0; a1_00 = PrimitiveList_FindById(a1,a1_00)) {
    Primitive_Invalidate(a1_00);
    if ((a2 != 2) && (a2 != 1)) {
      a2 = 2;
    }
    *(int *)(a1_00 + 0x10) = a2;
  }
  return 0;
}

/* ---- 0x0048a830  Primitive_Offset ---- */
undefined4 __stdcall Primitive_Offset(int a1,int a2,int a3)

{
  int a1_00;
  
  for (a1_00 = PrimitiveList_FindById(a1,0); a1_00 != 0; a1_00 = PrimitiveList_FindById(a1,a1_00)) {
    Primitive_Invalidate(a1_00);
    *(int *)(a1_00 + 0x14) = *(int *)(a1_00 + 0x14) + a2;
    *(int *)(a1_00 + 0x20) = *(int *)(a1_00 + 0x20) + a3;
    *(int *)(a1_00 + 0x18) = *(int *)(a1_00 + 0x18) + a3;
    *(int *)(a1_00 + 0x1c) = *(int *)(a1_00 + 0x1c) + a2;
  }
  return 0;
}

/* ---- 0x0048a8a0  Primitive_MoveTo ---- */
undefined4 __stdcall Primitive_MoveTo(int a1,int a2,int a3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0;
  iVar1 = PrimitiveList_FindById(a1,0);
  if (iVar1 != 0) {
    Primitive_Invalidate(iVar1);
    if (a2 != -1) {
      iVar3 = a2 - *(int *)(iVar1 + 0x14);
      *(int *)(iVar1 + 0x14) = a2;
    }
    if (a3 != -1) {
      iVar2 = a3 - *(int *)(iVar1 + 0x18);
      *(int *)(iVar1 + 0x18) = a3;
    }
    *(int *)(iVar1 + 0x20) = *(int *)(iVar1 + 0x20) + iVar2;
    *(int *)(iVar1 + 0x1c) = *(int *)(iVar1 + 0x1c) + iVar3;
    for (iVar1 = PrimitiveList_FindById(a1,iVar1); iVar1 != 0;
        iVar1 = PrimitiveList_FindById(a1,iVar1)) {
      Primitive_Invalidate(iVar1);
      *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + iVar3;
      *(int *)(iVar1 + 0x18) = *(int *)(iVar1 + 0x18) + iVar2;
      *(int *)(iVar1 + 0x1c) = *(int *)(iVar1 + 0x1c) + iVar3;
      *(int *)(iVar1 + 0x20) = *(int *)(iVar1 + 0x20) + iVar2;
    }
  }
  return 0;
}

/* ---- 0x0048a960  Primitive_SetEnd ---- */
int __stdcall Primitive_SetEnd(int a1,int a2,int a3)

{
  int a1_00;
  int iVar1;
  
  a1_00 = PrimitiveList_FindById(a1,0);
  iVar1 = 0;
  if (a1_00 != 0) {
    Primitive_Invalidate(a1_00);
    if (a2 != -1) {
      *(int *)(a1_00 + 0x1c) = a2;
    }
    iVar1 = a3;
    if (a3 != -1) {
      *(int *)(a1_00 + 0x20) = a3;
    }
  }
  return iVar1;
}

/* ---- 0x0048a9a0  Primitive_SetSize ---- */
int __stdcall Primitive_SetSize(int a1,int a2,int a3)

{
  int a1_00;
  int iVar1;
  
  a1_00 = PrimitiveList_FindById(a1,0);
  iVar1 = 0;
  if (a1_00 != 0) {
    Primitive_Invalidate(a1_00);
    if (a2 != -1) {
      *(int *)(a1_00 + 0x1c) = *(int *)(a1_00 + 0x14) + a2;
    }
    iVar1 = a3;
    if (a3 != -1) {
      *(int *)(a1_00 + 0x20) = *(int *)(a1_00 + 0x18) + a3;
    }
  }
  return iVar1;
}

/* ---- 0x0048aa20  Primitive_Draw ---- */
int __stdcall Primitive_Draw(int a1,int a2)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  undefined4 extraout_EAX_01;
  int iVar3;
  int y1;
  #define local_10 (*(int *)(_frame + (0x20 - 0x10)))
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  
  iVar1 = *(int *)(a1 + 8);
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      if (*(int *)(a1 + 0x2c) == 0) {
        rdPrimit2_DrawRect((void *)a2,*(int *)(a1 + 0x14),*(int *)(a1 + 0x18),*(int *)(a1 + 0x1c),
                           *(int *)(a1 + 0x20),*(int *)(a1 + 0x24),*(int *)(a1 + 0x28));
        return extraout_EAX;
      }
      local_10 = *(int *)(a1 + 0x14);
      iVar1 = *(int *)(a1 + 0x1c);
      local_8 = local_10;
      if (iVar1 <= local_10) {
        local_8 = iVar1;
      }
      iVar2 = *(int *)(a1 + 0x18);
      iVar3 = *(int *)(a1 + 0x20);
      y1 = iVar2;
      if (iVar3 <= iVar2) {
        y1 = iVar3;
      }
      if (local_10 <= iVar1) {
        local_10 = iVar1;
      }
      if (iVar3 < iVar2) {
        iVar3 = iVar2;
      }
      if (iVar3 < y1) {
        return iVar2;
      }
      do {
        rdPrimit2_DrawLine((void *)a2,local_8,y1,local_10,y1,*(int *)(a1 + 0x24),*(int *)(a1 + 0x28)
                          );
        y1 = y1 + 1;
      } while (y1 <= iVar3);
      return extraout_EAX_00;
    }
    if (iVar1 + -2 != 0) {
      return iVar1 + -2;
    }
  }
  rdPrimit2_DrawLine((void *)a2,*(int *)(a1 + 0x14),*(int *)(a1 + 0x18),*(int *)(a1 + 0x1c),
                     *(int *)(a1 + 0x20),*(int *)(a1 + 0x24),*(int *)(a1 + 0x28));
  return extraout_EAX_01;
}
#undef local_10
#undef local_8


/* ---- 0x0048ab50  Primitive_Invalidate ---- */
/* Marks the primitive's bounding rectangle dirty on the last buffer */

undefined4 __stdcall Primitive_Invalidate(int a1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 extraout_EAX;
  #define local_10 (*(int *)(_frame + (0x20 - 0x10)))
  #define local_c (*(int *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(int *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(int *)(_frame + (0x20 - 0x4)))
  
  iVar3 = *(int *)(a1 + 0x14);
  iVar1 = *(int *)(a1 + 0x1c);
  local_10 = iVar3;
  if (iVar1 <= iVar3) {
    local_10 = iVar1;
  }
  iVar4 = *(int *)(a1 + 0x18);
  iVar2 = *(int *)(a1 + 0x20);
  local_c = iVar4;
  if (iVar2 <= iVar4) {
    local_c = iVar2;
  }
  if (iVar3 <= iVar1) {
    iVar3 = iVar1;
  }
  local_8 = (iVar3 - local_10) + 1;
  if (iVar4 <= iVar2) {
    iVar4 = iVar2;
  }
  local_4 = (iVar4 - local_c) + 1;
  Render_InvalidateRectLastBuffer(&local_10,0);
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
