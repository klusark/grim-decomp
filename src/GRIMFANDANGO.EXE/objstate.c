/* GRIMFANDANGO.EXE :: objstate.c
 * functions 0x004a5d50 .. 0x004aa720 (19 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a5d50  ObjectState_Create ---- */
/* Lua NewObjectState (userdata tag 'STAT'): record {?, type, setupIdx, ...} linked into setup+0x128
    */

void * __cdecl ObjectState_Create(int setupIdx,int type,char *bitmap,char *zbitmap,int visible)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *pvVar2;
  undefined4 *p;
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_c (*(undefined4 *)(_frame + (0x20 - 0xc)))
  #define pcStack_8 (*(code **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  pcStack_8 = FUN_004d607b;
  *unaff_FS_OFFSET = &local_c;
  pvVar2 = Set_GetCurrent();
  iVar1 = *(int *)((int)pvVar2 + 0xac) + setupIdx * 300;
  pvVar2 = Plat_Alloc(0xfc);
  local_4 = 0;
  if (pvVar2 == (void *)0x0) {
    p = (undefined4 *)0x0;
  }
  else {
    p = ObjectState_Construct(pvVar2,*(int *)(iVar1 + 0x128),(int)bitmap,(int)zbitmap,type);
  }
  local_4 = 0xffffffff;
  *(undefined4 **)(iVar1 + 0x128) = p;
  if (p == (undefined4 *)0x0) {
    *unaff_FS_OFFSET = local_c;
    return (void *)0x0;
  }
  Mem_CheckAlloc(p,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x992);
  ((code *)ObjectState_LoadImages)();
  *(int *)(*(int *)(iVar1 + 0x128) + 8) = setupIdx;
  if (visible < 0) {
    visible = (int)(type == 3);
  }
  ObjectState_SetFrame(*(void **)(iVar1 + 0x128),visible);
  pvVar2 = *(void **)(iVar1 + 0x128);
  *unaff_FS_OFFSET = local_c;
  return pvVar2;
}
#undef local_4
#undef local_c
#undef pcStack_8


/* ---- 0x004a5e50  ObjectState_Free ---- */
void __cdecl ObjectState_Free(void *state)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  
  if (state != (void *)0x0) {
    iVar1 = *(int *)((int)state + 8);
    pvVar3 = Set_GetCurrent();
    iVar2 = *(int *)((int)pvVar3 + 0xac);
    pvVar3 = *(void **)(iVar2 + 0x128 + iVar1 * 300);
    if (pvVar3 == state) {
      pvVar3 = *(void **)((int)state + 0xf8);
    }
    ((code *)ObjectState_Destruct)();
    Plat_Free(state);
    *(void **)(iVar2 + iVar1 * 300 + 0x128) = pvVar3;
  }
  return;
}

/* ---- 0x004aa070  StateImage_Construct ---- */
undefined4 * __fastcall StateImage_Construct(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  param_1[5] = 0;
  puVar2 = param_1 + 0xd;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[0x1a] = 0;
  param_1[0x1c] = 0;
  param_1[0x1b] = 0xffffffff;
  *param_1 = 0x74;
  return param_1;
}

/* ---- 0x004aa0b0  StateImage_Release ---- */
/* ObjectState.cpp: C++ image member (0x74 bytes: +4 rect, +0x14 name, +0x34 ResRef, +0x68 surface,
   +0x6c frame, +0x70 drawn). Drops the bitmap reference and surface */

void __fastcall StateImage_Release(int param_1)

{
  if (*(int *)(param_1 + 0x34) != 0) {
    ResRef_Remove((void *)(param_1 + 0x34));
  }
  if (*(void **)(param_1 + 0x68) != (void *)0x0) {
    Surface_Free(*(void **)(param_1 + 0x68));
    *(undefined4 *)(param_1 + 0x68) = 0;
  }
  *(undefined4 *)(param_1 + 0x6c) = 0xffffffff;
  *(undefined1 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  return;
}

/* ---- 0x004aa100  StateImage_Init ---- */
undefined4 __thiscall StateImage_Init(void *this,int a1)

{
  undefined4 uVar1;
  
  ((code *)StateImage_Release)();
  uVar1 = 0;
  if (a1 != 0) {
    uVar1 = strncpy((int)this + 0x14,a1,0x20);
  }
  return uVar1;
}

/* ---- 0x004aa130  StateImage_Load ---- */
/* Loads (or releases) the BKND bitmap named in the image and takes its position and size */

int __thiscall StateImage_Load(void *this,int a1)

{
  void *data;
  int iVar1;
  char *extraout_EAX;
  char *name;
  
  if ((a1 == 0) || (name = (char *)((int)this + 0x14), *(char *)((int)this + 0x14) == '\0')) {
    if (*(int *)((int)this + 0x34) != 0) {
      ResRef_Remove((void *)((int)this + 0x34));
    }
    name = (char *)0x0;
    if (*(void **)((int)this + 0x68) != (void *)0x0) {
      Surface_Free(*(void **)((int)this + 0x68));
      *(undefined4 *)((int)this + 0x68) = 0;
      name = extraout_EAX;
    }
  }
  else if (*(int *)((int)this + 0x34) == 0) {
    data = Resource_Load(0x444e4b42,name);
    name = (char *)0x0;
    if (data != (void *)0x0) {
      ResRef_Add((void *)((int)this + 0x34),data,s_C__grimsrc_libs_grimlib_Engine_O_004ec9d0,0x3d);
      *(undefined4 *)((int)this + 4) = *(undefined4 *)((int)data + 0x6c);
      *(undefined4 *)((int)this + 8) = *(undefined4 *)((int)data + 0x70);
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(**(int **)((int)data + 0x78) + 0xc);
      *(undefined4 *)((int)this + 0x10) = *(undefined4 *)(**(int **)((int)data + 0x78) + 0x10);
      *(undefined4 *)((int)data + 0x68) = *(undefined4 *)((int)this + 0x6c);
      iVar1 = stdBitmap_GetSize(data);
      *(int *)this = *(int *)this + iVar1;
      return iVar1;
    }
  }
  return (int)name;
}

/* ---- 0x004aa1f0  StateImage_GetFrameSurface ---- */
undefined4 __fastcall StateImage_GetFrameSurface(int param_1)

{
  if (-1 < *(int *)(param_1 + 0x6c)) {
    if (*(int *)(param_1 + 0x34) == 0) {
      (*g_pSvcMain->pAssertFail)
                (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
    }
    if (*(int *)(*(int *)(param_1 + 0x38) + 100) <= *(int *)(param_1 + 0x6c)) {
      if (*(int *)(param_1 + 0x34) == 0) {
        (*g_pSvcMain->pAssertFail)
                  (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
      }
      *(int *)(param_1 + 0x6c) = *(int *)(*(int *)(param_1 + 0x38) + 100) + -1;
    }
    if (*(int *)(param_1 + 0x34) == 0) {
      (*g_pSvcMain->pAssertFail)
                (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
    }
    return *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x38) + 0x78) + *(int *)(param_1 + 0x6c) * 4)
    ;
  }
  return *(undefined4 *)(param_1 + 0x68);
}

/* ---- 0x004aa290  StateImage_CaptureFrom ---- */
/* Copies the image rectangle out of a surface into a private surface */

int __thiscall StateImage_CaptureFrom(void *this,int a1)

{
  void *dst;
  int iVar1;
  
  if (*(void **)((int)this + 0x68) != (void *)0x0) {
    Surface_Free(*(void **)((int)this + 0x68));
  }
  iVar1 = 0;
  if (*(int *)((int)this + 0x34) != 0) {
    if (*(int *)((int)this + 0x34) == 0) {
      (*g_pSvcMain->pAssertFail)
                (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
    }
    dst = Surface_Create((void *)(**(int **)(*(int *)((int)this + 0x38) + 0x78) + 0xc),0,0,0);
    *(void **)((int)this + 0x68) = dst;
    iVar1 = 0;
    if (dst != (void *)0x0) {
      iVar1 = Surface_Blit(dst,(void *)a1,0,0,(int *)((int)this + 4),0);
    }
  }
  return iVar1;
}

/* ---- 0x004aa310  StateImage_Draw ---- */
int __thiscall StateImage_Draw(void *this,int a1)

{
  undefined4 in_EAX;
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  void *src;
  int iVar4;
  int extraout_EAX;
  int iVar5;
  int iVar6;
  
  iVar4 = CONCAT31((int3)((uint)in_EAX >> 8),*(char *)((int)this + 0x14));
  if ((*(char *)((int)this + 0x14) != '\0') && (a1 != 0)) {
    iVar5 = *(int *)((int)this + 0x70);
    iVar4 = 0;
    if (*(int *)((int)this + 0x34) != 0) {
      if (*(int *)((int)this + 0x34) == 0) {
        (*g_pSvcMain->pAssertFail)
                  (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
      }
      iVar6 = *(int *)((int)this + 0x38);
      iVar4 = *(int *)(iVar6 + 0x68);
      *(int *)((int)this + 0x6c) = iVar4;
      if (iVar4 == -1) {
        iVar5 = 0;
      }
      iVar1 = ((code *)StateImage_GetFrameSurface)();
      iVar4 = 0;
      if (iVar1 != 0) {
        piVar2 = (int *)((code *)StateImage_GetFrameSurface)();
        iVar4 = iVar5;
        if (*piVar2 == 2) {
          uVar3 = ((code *)StateImage_GetFrameSurface)();
          Render_ConvertBackground(uVar3);
          iVar1 = *(int *)(iVar6 + 0x70);
          iVar6 = *(int *)(iVar6 + 0x6c);
          piVar2 = (int *)0x0;
          src = g_pTempSurface;
        }
        else {
          iVar1 = *(int *)(iVar6 + 0x70);
          iVar6 = *(int *)(iVar6 + 0x6c);
          piVar2 = (int *)0x0;
          src = (void *)((code *)StateImage_GetFrameSurface)();
        }
        iVar4 = Surface_Blit((void *)a1,src,iVar6,iVar1,piVar2,iVar4);
        if (iVar5 != 0) {
          Render_InvalidateRectLastBuffer((int *)((int)this + 4),1);
          iVar4 = extraout_EAX;
        }
      }
    }
  }
  return iVar4;
}

/* ---- 0x004aa3e0  StateImage_IsCurrentFrame ---- */
bool __fastcall StateImage_IsCurrentFrame(int param_1)

{
  if (*(char *)(param_1 + 0x14) == '\0') {
    return true;
  }
  if (*(int *)(param_1 + 0x34) == 0) {
    return false;
  }
  return *(int *)(*(int *)(param_1 + 0x38) + 0x68) == *(int *)(param_1 + 0x6c);
}

/* ---- 0x004aa410  ObjectState_Construct ---- */
/* ObjectState.cpp constructor: builds the bitmap and depth StateImages */

undefined4 * __thiscall ObjectState_Construct(void *this,int a1,int a2,int a3,int a4)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_c (*(undefined4 *)(_frame + (0x20 - 0xc)))
  #define pcStack_8 (*(code **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0xffffffff;
  pcStack_8 = FUN_004d60e9;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  ((code *)StateImage_Construct)();
  local_4 = 0;
  ((code *)StateImage_Construct)();
  local_4 = CONCAT31(PIECE(local_4,1,3),1);
  *(undefined4 *)((int)this + 8) = 0xffffffff;
  *(int *)((int)this + 4) = a4;
  StateImage_Init((void *)((int)this + 0xc),a2);
  StateImage_Init((void *)((int)this + 0x80),a3);
  *(undefined4 *)((int)this + 0xf8) = 0;
  *(undefined4 *)((int)this + 0xf4) = 0;
  if (a1 != 0) {
    *(void **)(a1 + 0xf4) = this;
    *(int *)((int)this + 0xf8) = a1;
  }
  *(undefined4 *)this = 0xfc;
  *unaff_FS_OFFSET = local_c;
  return this;
}
#undef local_4
#undef local_c
#undef pcStack_8


/* ---- 0x004aa4c0  ObjectState_Destruct ---- */
void __fastcall ObjectState_Destruct(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *unaff_FS_OFFSET = (undefined4 *)TEB_BASE();
  #define local_c (*(undefined4 *)(_frame + (0x20 - 0xc)))
  #define pcStack_8 (*(code **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  local_c = *unaff_FS_OFFSET;
  pcStack_8 = FUN_004d610b;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 0;
  if (*(int *)(param_1 + 0xf4) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0xf8) = *(undefined4 *)(param_1 + 0xf8);
  }
  if (*(int *)(param_1 + 0xf8) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xf8) + 0xf4) = *(undefined4 *)(param_1 + 0xf4);
  }
  ((code *)StateImage_Release)();
  local_4 = 0xffffffff;
  ((code *)StateImage_Release)();
  *unaff_FS_OFFSET = local_c;
  return;
}
#undef local_4
#undef local_c
#undef pcStack_8


/* ---- 0x004aa540  ObjectState_LoadImages ---- */
void __fastcall ObjectState_LoadImages(int param_1)

{
  StateImage_Load((void *)(param_1 + 0xc),1);
  StateImage_Load((void *)(param_1 + 0x80),1);
  return;
}

/* ---- 0x004aa560  ObjectState_UnloadBitmaps ---- */
void __fastcall ObjectState_UnloadBitmaps(int param_1)

{
  StateImage_Load((void *)(param_1 + 0xc),0);
  StateImage_Load((void *)(param_1 + 0x80),0);
  return;
}

/* ---- 0x004aa580  ObjectState_CaptureBackground ---- */
/* Type 3 states keep a copy of the background and depth under them */

int __thiscall ObjectState_CaptureBackground(void *this,int a1,int a2)

{
  int in_EAX;
  
  if (*(int *)((int)this + 4) == 3) {
    StateImage_CaptureFrom((void *)((int)this + 0xc),a1);
    *(undefined4 *)((int)this + 0x78) = 0xffffffff;
    in_EAX = StateImage_CaptureFrom((void *)((int)this + 0x80),a2);
    *(undefined4 *)((int)this + 0xec) = 0xffffffff;
  }
  return in_EAX;
}

/* ---- 0x004aa5c0  ObjectState_Draw ---- */
/* Draws the state when its type matches; type 3 only when the frame changed, invalidating its
   rectangle */

undefined4 __thiscall ObjectState_Draw(void *this,int a1,int a2,int a3)

{
  int iVar1;
  undefined4 extraout_EAX;
  int flag;
  
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 == a1) {
    if (iVar1 == 3) {
      flag = 0;
      iVar1 = ((code *)StateImage_IsCurrentFrame)();
      if (iVar1 == 0) {
        StateImage_Draw((void *)((int)this + 0xc),a2);
        if ((*(int *)((int)this + 0xb4) != 0) && (a3 != 0)) {
          if (*(int *)((int)this + 0xb4) == 0) {
            (*g_pSvcMain->pAssertFail)
                      (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
          }
          *(undefined4 *)(*(int *)((int)this + 0xb8) + 0x68) = *(undefined4 *)((int)this + 0x78);
          StateImage_Draw((void *)((int)this + 0x80),a3);
          flag = 1;
        }
        Render_InvalidateRect((int *)((int)this + 0x10),flag);
        return extraout_EAX;
      }
    }
    else {
      if (*(int *)((int)this + 0x40) == 0) {
        iVar1 = -1;
      }
      else {
        iVar1 = *(int *)(*(int *)((int)this + 0x44) + 0x68);
      }
      if ((iVar1 == -1) && (*(int *)((int)this + 0x78) != -1)) {
        Render_InvalidateRect((int *)((int)this + 0x10),1);
      }
      StateImage_Draw((void *)((int)this + 0xc),a2);
      iVar1 = StateImage_Draw((void *)((int)this + 0x80),a3);
    }
  }
  return iVar1;
}

/* ---- 0x004aa6b0  ObjectState_SetFrame ---- */
/* Stores the frame index into both StateImages */

int __thiscall ObjectState_SetFrame(void *this,int a1)

{
  *(int *)((int)this + 0x7c) = a1;
  *(int *)((int)this + 0xf0) = a1;
  return a1;
}

/* ---- 0x004aa6c0  ObjectState_SendToBack ---- */
/* Returns the new head of the setup's object state list */

int __thiscall ObjectState_SendToBack(void *this,int a1)

{
  if ((void *)a1 != this) {
    if (*(int *)((int)this + 0xf4) != 0) {
      *(undefined4 *)(*(int *)((int)this + 0xf4) + 0xf8) = *(undefined4 *)((int)this + 0xf8);
    }
    if (*(int *)((int)this + 0xf8) != 0) {
      *(undefined4 *)(*(int *)((int)this + 0xf8) + 0xf4) = *(undefined4 *)((int)this + 0xf4);
    }
    *(void **)(a1 + 0xf4) = this;
    *(undefined4 *)((int)this + 0xf4) = 0;
    *(int *)((int)this + 0xf8) = a1;
  }
  return (int)this;
}

/* ---- 0x004aa720  ObjectState_SendToFront ---- */
int __thiscall ObjectState_SendToFront(void *this,int a1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = a1;
  if (this == (void *)a1) {
    if (*(int *)(a1 + 0xf8) == 0) {
      return a1;
    }
    iVar3 = *(int *)((int)this + 0xf8);
    *(undefined4 *)(iVar3 + 0xf4) = 0;
  }
  iVar2 = *(int *)(a1 + 0xf8);
  while (iVar1 = iVar2, iVar1 != 0) {
    a1 = iVar1;
    iVar2 = *(int *)(iVar1 + 0xf8);
  }
  if (*(int *)((int)this + 0xf8) != 0) {
    *(undefined4 *)(*(int *)((int)this + 0xf8) + 0xf4) = *(undefined4 *)((int)this + 0xf4);
  }
  if (*(int *)((int)this + 0xf4) != 0) {
    *(undefined4 *)(*(int *)((int)this + 0xf4) + 0xf8) = *(undefined4 *)((int)this + 0xf8);
  }
  *(void **)(a1 + 0xf8) = this;
  *(int *)((int)this + 0xf4) = a1;
  *(undefined4 *)((int)this + 0xf8) = 0;
  return iVar3;
}
