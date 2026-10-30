/* GRIMFANDANGO.EXE :: objstate.c
 * functions 0x004a5d50 .. 0x004aa720 (19 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a5d50  ObjectState_Create ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* Lua NewObjectState (userdata tag 'STAT'): record {?, type, setupIdx, ...} linked into setup+0x128
    */

void * __cdecl ObjectState_Create(int setupIdx,int type,char *bitmap,char *zbitmap,int visible)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void *pvVar2;
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define pcStack_8 (*(code **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  pcStack_8 = FUN_004d607b;
  *unaff_FS_OFFSET = (uint)&local_c;
  pvVar2 = Set_GetCurrent();
  iVar1 = *(int *)((int)pvVar2 + 0xac) + setupIdx * 300;
  pvVar2 = Plat_Alloc(0xfc);
  local_4 = 0;
  if (pvVar2 == (void *)0x0) {
    pvVar2 = (void *)0x0;
  }
  else {
    pvVar2 = ObjectState_Construct(pvVar2,*(int *)(iVar1 + 0x128),bitmap,zbitmap,type);
  }
  local_4 = 0xffffffff;
  *(void **)(iVar1 + 0x128) = pvVar2;
  if (pvVar2 == (void *)0x0) {
    *unaff_FS_OFFSET = local_c;
    return (void *)0x0;
  }
  Mem_CheckAlloc(pvVar2,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x992);
  ObjectState_LoadImages(*(int *)(iVar1 + 0x128));
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

#endif


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
    ObjectState_Destruct((int)state);
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
void __thiscall StateImage_Init(void *this,char *name)

{
  StateImage_Release((int)this);
  if (name != (char *)0x0) {
    strncpy((int)this + 0x14,name,0x20);
  }
  return;
}

/* ---- 0x004aa130  StateImage_Load ---- */
/* Loads (or releases) the BKND bitmap named in the image and takes its position and size */

void __thiscall StateImage_Load(void *this,int load)

{
  void *data;
  int iVar1;
  
  if ((load == 0) || (*(char *)((int)this + 0x14) == '\0')) {
    if (*(int *)((int)this + 0x34) != 0) {
      ResRef_Remove((void *)((int)this + 0x34));
    }
    if (*(void **)((int)this + 0x68) != (void *)0x0) {
      Surface_Free(*(void **)((int)this + 0x68));
      *(undefined4 *)((int)this + 0x68) = 0;
    }
  }
  else if (*(int *)((int)this + 0x34) == 0) {
    data = Resource_Load(0x444e4b42,(char *)((int)this + 0x14));
    if (data != (void *)0x0) {
      ResRef_Add((void *)((int)this + 0x34),data,s_C__grimsrc_libs_grimlib_Engine_O_004ec9d0,0x3d);
      *(undefined4 *)((int)this + 4) = *(undefined4 *)((int)data + 0x6c);
      *(undefined4 *)((int)this + 8) = *(undefined4 *)((int)data + 0x70);
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(**(int **)((int)data + 0x78) + 0xc);
      *(undefined4 *)((int)this + 0x10) = *(undefined4 *)(**(int **)((int)data + 0x78) + 0x10);
      *(undefined4 *)((int)data + 0x68) = *(undefined4 *)((int)this + 0x6c);
      iVar1 = stdBitmap_ConvertToDisplay(data);
      *(int *)this = *(int *)this + iVar1;
      return;
    }
  }
  return;
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

void __thiscall StateImage_CaptureFrom(void *this,void *surface)

{
  void *dst;
  
  if (*(void **)((int)this + 0x68) != (void *)0x0) {
    Surface_Free(*(void **)((int)this + 0x68));
  }
  if (*(int *)((int)this + 0x34) != 0) {
    if (*(int *)((int)this + 0x34) == 0) {
      (*g_pSvcMain->pAssertFail)
                (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
    }
    dst = Surface_Create((void *)(**(int **)(*(int *)((int)this + 0x38) + 0x78) + 0xc),0,0,0);
    *(void **)((int)this + 0x68) = dst;
    if (dst != (void *)0x0) {
      Surface_Blit(dst,surface,0,0,(int *)((int)this + 4),0);
    }
  }
  return;
}

/* ---- 0x004aa310  StateImage_Draw ---- */
void __thiscall StateImage_Draw(void *this,void *dst)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  void *src;
  int iVar4;
  int iVar5;
  int y;
  
  if ((*(char *)((int)this + 0x14) != '\0') && (dst != (void *)0x0)) {
    iVar4 = *(int *)((int)this + 0x70);
    if (*(int *)((int)this + 0x34) != 0) {
      if (*(int *)((int)this + 0x34) == 0) {
        (*g_pSvcMain->pAssertFail)
                  (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
      }
      iVar5 = *(int *)((int)this + 0x38);
      iVar1 = *(int *)(iVar5 + 0x68);
      *(int *)((int)this + 0x6c) = iVar1;
      if (iVar1 == -1) {
        iVar4 = 0;
      }
      iVar1 = StateImage_GetFrameSurface((int)this);
      if (iVar1 != 0) {
        piVar2 = (int *)StateImage_GetFrameSurface((int)this);
        iVar1 = iVar4;
        if (*piVar2 == 2) {
          uVar3 = StateImage_GetFrameSurface((int)this);
          Render_ConvertBackground(uVar3);
          y = *(int *)(iVar5 + 0x70);
          iVar5 = *(int *)(iVar5 + 0x6c);
          piVar2 = (int *)0x0;
          src = g_pTempSurface;
        }
        else {
          y = *(int *)(iVar5 + 0x70);
          iVar5 = *(int *)(iVar5 + 0x6c);
          piVar2 = (int *)0x0;
          src = (void *)StateImage_GetFrameSurface((int)this);
        }
        Surface_Blit(dst,src,iVar5,y,piVar2,iVar1);
        if (iVar4 != 0) {
          Render_InvalidateRectLastBuffer((int *)((int)this + 4),1);
        }
      }
    }
  }
  return;
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
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
/* ObjectState record (0xfc bytes): +4 type, +8 setupIdx, +0xc bitmap StateImage, +0x80 depth
   StateImage, +0xf4 prev, +0xf8 next */

void * __thiscall
ObjectState_Construct(void *this,int type,char *bitmapName,char *zbufName,int setupIdx)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define pcStack_8 (*(code **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0xffffffff;
  pcStack_8 = FUN_004d60e9;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (uint)&local_c;
  StateImage_Construct((undefined4 *)((int)this + 0xc));
  local_4 = 0;
  StateImage_Construct((undefined4 *)((int)this + 0x80));
  local_4 = CONCAT31(PIECE(local_4,1,3),1);
  *(undefined4 *)((int)this + 8) = 0xffffffff;
  *(int *)((int)this + 4) = setupIdx;
  StateImage_Init((undefined4 *)((int)this + 0xc),bitmapName);
  StateImage_Init((undefined4 *)((int)this + 0x80),zbufName);
  *(undefined4 *)((int)this + 0xf8) = 0;
  *(undefined4 *)((int)this + 0xf4) = 0;
  if (type != 0) {
    *(void **)(type + 0xf4) = this;
    *(int *)((int)this + 0xf8) = type;
  }
  *(undefined4 *)this = 0xfc;
  *unaff_FS_OFFSET = local_c;
  return this;
}
#undef local_10
#undef local_4
#undef local_c
#undef pcStack_8

#endif


/* ---- 0x004aa4c0  ObjectState_Destruct ---- */
/* NOT COMPILED: the build uses the original machine code of this function (src/GRIMFANDANGO.EXE/asm_funcs.s, tools/gen_asm.py); this C text is only for reading */
#if 0
void __fastcall ObjectState_Destruct(int param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint *unaff_FS_OFFSET = (uint *)TEB_BASE();
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define pcStack_8 (*(code **)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_c = *unaff_FS_OFFSET;
  pcStack_8 = FUN_004d610b;
  *unaff_FS_OFFSET = (uint)&local_c;
  local_4 = 0;
  if (*(int *)(param_1 + 0xf4) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0xf8) = *(undefined4 *)(param_1 + 0xf8);
  }
  if (*(int *)(param_1 + 0xf8) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xf8) + 0xf4) = *(undefined4 *)(param_1 + 0xf4);
  }
  StateImage_Release(param_1 + 0x80);
  local_4 = 0xffffffff;
  StateImage_Release(param_1 + 0xc);
  *unaff_FS_OFFSET = local_c;
  return;
}
#undef local_4
#undef local_c
#undef pcStack_8

#endif


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

void __thiscall ObjectState_CaptureBackground(void *this,void *bg,void *zbuf)

{
  if (*(int *)((int)this + 4) == 3) {
    StateImage_CaptureFrom((void *)((int)this + 0xc),bg);
    *(undefined4 *)((int)this + 0x78) = 0xffffffff;
    StateImage_CaptureFrom((void *)((int)this + 0x80),zbuf);
    *(undefined4 *)((int)this + 0xec) = 0xffffffff;
  }
  return;
}

/* ---- 0x004aa5c0  ObjectState_Draw ---- */
/* Draws the state when its type matches; type 3 only when the frame changed, invalidating its
   rectangle */

void __thiscall ObjectState_Draw(void *this,int type,void *dst,void *zdst)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  
  if (*(int *)((int)this + 4) == type) {
    if (*(int *)((int)this + 4) == 3) {
      iVar2 = 0;
      bVar1 = StateImage_IsCurrentFrame((int)this + 0xc);
      if (((uint)(bVar1)) == 0) {
        StateImage_Draw((void *)((int)this + 0xc),dst);
        if ((*(int *)((int)this + 0xb4) != 0) && (zdst != (void *)0x0)) {
          if (*(int *)((int)this + 0xb4) == 0) {
            (*g_pSvcMain->pAssertFail)
                      (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
          }
          *(undefined4 *)(*(int *)((int)this + 0xb8) + 0x68) = *(undefined4 *)((int)this + 0x78);
          StateImage_Draw((void *)((int)this + 0x80),zdst);
          iVar2 = 1;
        }
        Render_InvalidateRect((int *)((int)this + 0x10),iVar2);
        return;
      }
    }
    else {
      if (*(int *)((int)this + 0x40) == 0) {
        iVar2 = -1;
      }
      else {
        iVar2 = *(int *)(*(int *)((int)this + 0x44) + 0x68);
      }
      if ((iVar2 == -1) && (*(int *)((int)this + 0x78) != -1)) {
        Render_InvalidateRect((int *)((int)this + 0x10),1);
      }
      StateImage_Draw((void *)((int)this + 0xc),dst);
      StateImage_Draw((void *)((int)this + 0x80),zdst);
    }
  }
  return;
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

void * __thiscall ObjectState_SendToBack(void *this,void *list)

{
  if (list != this) {
    if (*(int *)((int)this + 0xf4) != 0) {
      *(undefined4 *)(*(int *)((int)this + 0xf4) + 0xf8) = *(undefined4 *)((int)this + 0xf8);
    }
    if (*(int *)((int)this + 0xf8) != 0) {
      *(undefined4 *)(*(int *)((int)this + 0xf8) + 0xf4) = *(undefined4 *)((int)this + 0xf4);
    }
    *(void **)((int)list + 0xf4) = this;
    *(undefined4 *)((int)this + 0xf4) = 0;
    *(void **)((int)this + 0xf8) = list;
  }
  return this;
}

/* ---- 0x004aa720  ObjectState_SendToFront ---- */
void * __thiscall ObjectState_SendToFront(void *this,void *list)

{
  void *pvVar1;
  void *pvVar2;
  void *pvVar3;
  
  pvVar3 = list;
  if (this == list) {
    if (*(int *)((int)list + 0xf8) == 0) {
      return list;
    }
    pvVar3 = *(void **)((int)this + 0xf8);
    *(undefined4 *)((int)pvVar3 + 0xf4) = 0;
  }
  pvVar2 = *(void **)((int)list + 0xf8);
  while (pvVar1 = pvVar2, pvVar1 != (void *)0x0) {
    list = pvVar1;
    pvVar2 = *(void **)((int)pvVar1 + 0xf8);
  }
  if (*(int *)((int)this + 0xf8) != 0) {
    *(undefined4 *)(*(int *)((int)this + 0xf8) + 0xf4) = *(undefined4 *)((int)this + 0xf4);
  }
  if (*(int *)((int)this + 0xf4) != 0) {
    *(undefined4 *)(*(int *)((int)this + 0xf4) + 0xf8) = *(undefined4 *)((int)this + 0xf8);
  }
  *(void **)((int)list + 0xf8) = this;
  *(void **)((int)this + 0xf4) = list;
  *(undefined4 *)((int)this + 0xf8) = 0;
  return pvVar3;
}
