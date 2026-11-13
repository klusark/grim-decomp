/* GRIMFANDANGO.EXE :: objstate.c
 * functions 0x004a5d50 .. 0x004aa720 (19 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004a5d50  sputRoom_AddObjectState ---- */
/* Lua NewObjectState (userdata tag 'STAT'): record {?, type, setupIdx, ...} linked into setup+0x128
   Original name sputRoom_AddObjectState (the remaster's GrimFandango (Linux): aligned call in
   sputLua_NewObjectState, sputRoom_Restore); was ObjectState_Create. */

void * __cdecl sputRoom_AddObjectState(int setupIdx,int type,char *bitmap,char *zbitmap,int visible)

{
  int iVar1;
  void *pvVar2;
  
  pvVar2 = sputRoom_GetCurrentRoom();
  iVar1 = *(int *)((int)pvVar2 + 0xac) + setupIdx * 300;
  pvVar2 = Plat_Alloc(0xfc);
  if (pvVar2 == (void *)0x0) {
    pvVar2 = (void *)0x0;
  }
  else {
    pvVar2 = ObjectState_Construct(pvVar2,*(int *)(iVar1 + 0x128),bitmap,zbitmap,type);
  }
  *(void **)(iVar1 + 0x128) = pvVar2;
  if (pvVar2 == (void *)0x0) {
    return (void *)0x0;
  }
  Mem_CheckAlloc(pvVar2,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x992);
  ObjectState_LoadResources(*(int *)(iVar1 + 0x128));
  *(int *)(*(int *)(iVar1 + 0x128) + 8) = setupIdx;
  if (visible < 0) {
    visible = (int)(type == 3);
  }
  ObjectState_SetCopyMode(*(void **)(iVar1 + 0x128),visible);
  pvVar2 = *(void **)(iVar1 + 0x128);
  return pvVar2;
}

/* ---- 0x004a5e50  sputRoom_RemoveObjectState ---- */
/* Original name sputRoom_RemoveObjectState (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_FreeObjectState; 1 matched neighbours agree, 1 disagree); was ObjectState_Free. */

void __cdecl sputRoom_RemoveObjectState(void *state)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  
  if (state != (void *)0x0) {
    iVar1 = *(int *)((int)state + 8);
    pvVar3 = sputRoom_GetCurrentRoom();
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

/* ---- 0x004aa070  ObjectStateImage_Construct ---- */
/* Original name ObjectStateImage_Construct (the remaster's GrimFandango (Linux): same body (the
   record cleared, +0x6c = -1)); was StateImage_Construct. */

undefined4 * __fastcall ObjectStateImage_Construct(undefined4 *param_1)

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

/* ---- 0x004aa0b0  ObjectStateImage_Clear ---- */
/* ObjectState.cpp: C++ image member (0x74 bytes: +4 rect, +0x14 name, +0x34 ResRef, +0x68 surface,
   +0x6c frame, +0x70 drawn). Drops the bitmap reference and surface Original name
   ObjectStateImage_Clear (the remaster's GrimFandango (Linux): same body (release the bitmap
   reference +0x34, free the VBuffer +0x68, frame -1, empty name); SetFile and Load inline it in the
   remaster); was StateImage_Release. */

void __fastcall ObjectStateImage_Clear(int param_1)

{
  if (*(int *)(param_1 + 0x34) != 0) {
    Res_RemoveReference((void *)(param_1 + 0x34));
  }
  if (*(void **)(param_1 + 0x68) != (void *)0x0) {
    stdDisplay_VBufferFree(*(void **)(param_1 + 0x68));
    *(undefined4 *)(param_1 + 0x68) = 0;
  }
  *(undefined4 *)(param_1 + 0x6c) = 0xffffffff;
  *(undefined1 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  return;
}

/* ---- 0x004aa100  ObjectStateImage_SetFile ---- */
/* Original name ObjectStateImage_SetFile (the remaster's GrimFandango (Linux): same body (Clear,
   then strncpy of the file name, 0x20 chars, to +0x14)); was StateImage_Init. */

void __thiscall ObjectStateImage_SetFile(void *this,char *name)

{
  ObjectStateImage_Clear((int)this);
  if (name != (char *)0x0) {
    strncpy((int)this + 0x14,name,0x20);
  }
  return;
}

/* ---- 0x004aa130  ObjectStateImage_Load ---- */
/* Loads (or releases) the BKND bitmap named in the image and takes its position and size Original
   name ObjectStateImage_Load (the remaster's GrimFandango (Linux): same body (unload, or load the
   named bitmap into +0x34 when not loaded yet)); was StateImage_Load. */

void __thiscall ObjectStateImage_Load(void *this,int load)

{
  void *data;
  int iVar1;
  
  if ((load == 0) || (*(char *)((int)this + 0x14) == '\0')) {
    if (*(int *)((int)this + 0x34) != 0) {
      Res_RemoveReference((void *)((int)this + 0x34));
    }
    if (*(void **)((int)this + 0x68) != (void *)0x0) {
      stdDisplay_VBufferFree(*(void **)((int)this + 0x68));
      *(undefined4 *)((int)this + 0x68) = 0;
    }
  }
  else if (*(int *)((int)this + 0x34) == 0) {
    data = sputResource_Alloc(0x444e4b42,(char *)((int)this + 0x14));
    if (data != (void *)0x0) {
      Res_SetReference((void *)((int)this + 0x34),data,s_C__grimsrc_libs_grimlib_Engine_O_004ec9d0,
                       0x3d);
      *(undefined4 *)((int)this + 4) = *(undefined4 *)((int)data + 0x6c);
      *(undefined4 *)((int)this + 8) = *(undefined4 *)((int)data + 0x70);
      *(undefined4 *)((int)this + 0xc) = *(undefined4 *)(**(int **)((int)data + 0x78) + 0xc);
      *(undefined4 *)((int)this + 0x10) = *(undefined4 *)(**(int **)((int)data + 0x78) + 0x10);
      *(undefined4 *)((int)data + 0x68) = *(undefined4 *)((int)this + 0x6c);
      iVar1 = stdBitmap_MemUsage(data);
      *(int *)this = *(int *)this + iVar1;
      return;
    }
  }
  return;
}

/* ---- 0x004aa1f0  ObjectStateImage_VBuffer ---- */
/* Original name ObjectStateImage_VBuffer (the remaster's GrimFandango (Linux): same body (the
   current frame's VBuffer of the bitmap, "Bad Bitmap Reference" assert of sputResource.h, or the
   clean copy at +0x68)); was StateImage_GetFrameSurface. */

undefined4 __fastcall ObjectStateImage_VBuffer(int param_1)

{
  if (-1 < *(int *)(param_1 + 0x6c)) {
    if (*(int *)(param_1 + 0x34) == 0) {
      (*g_pStd_HS->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90)
      ;
    }
    if (*(int *)(*(int *)(param_1 + 0x38) + 100) <= *(int *)(param_1 + 0x6c)) {
      if (*(int *)(param_1 + 0x34) == 0) {
        (*g_pStd_HS->pAssertFail)
                  (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
      }
      *(int *)(param_1 + 0x6c) = *(int *)(*(int *)(param_1 + 0x38) + 100) + -1;
    }
    if (*(int *)(param_1 + 0x34) == 0) {
      (*g_pStd_HS->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90)
      ;
    }
    return *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x38) + 0x78) + *(int *)(param_1 + 0x6c) * 4)
    ;
  }
  return *(undefined4 *)(param_1 + 0x68);
}

/* ---- 0x004aa290  ObjectStateImage_SetClean ---- */
/* Copies the image rectangle out of a surface into a private surface Original name
   ObjectStateImage_SetClean (the remaster's GrimFandango (Linux): same body (free +0x68, a new
   VBuffer of the bitmap's format, copy the rectangle of the given buffer into it)); was
   StateImage_CaptureFrom. */

void __thiscall ObjectStateImage_SetClean(void *this,void *surface)

{
  void *dst;
  
  if (*(void **)((int)this + 0x68) != (void *)0x0) {
    stdDisplay_VBufferFree(*(void **)((int)this + 0x68));
  }
  if (*(int *)((int)this + 0x34) != 0) {
    if (*(int *)((int)this + 0x34) == 0) {
      (*g_pStd_HS->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90)
      ;
    }
    dst = stdDisplay_VBufferNew((void *)(**(int **)(*(int *)((int)this + 0x38) + 0x78) + 0xc),0,0,0)
    ;
    *(void **)((int)this + 0x68) = dst;
    if (dst != (void *)0x0) {
      Surface_Blit(dst,surface,0,0,(int *)((int)this + 4),0);
    }
  }
  return;
}

/* ---- 0x004aa310  ObjectStateImage_Draw ---- */
/* Original name ObjectStateImage_Draw (the remaster's GrimFandango (Linux): the image draw
   ObjectState_Update calls in both builds (the frame, the copy into the destination, the dirty
   rectangle); the remaster split the set-up into SetupDraw); was StateImage_Draw. */

void __thiscall ObjectStateImage_Draw(void *this,void *dst)

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
        (*g_pStd_HS->pAssertFail)
                  (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
      }
      iVar5 = *(int *)((int)this + 0x38);
      iVar1 = *(int *)(iVar5 + 0x68);
      *(int *)((int)this + 0x6c) = iVar1;
      if (iVar1 == -1) {
        iVar4 = 0;
      }
      iVar1 = ObjectStateImage_VBuffer((int)this);
      if (iVar1 != 0) {
        piVar2 = (int *)ObjectStateImage_VBuffer((int)this);
        iVar1 = iVar4;
        if (*piVar2 == 2) {
          uVar3 = ObjectStateImage_VBuffer((int)this);
          sputRender_Decompress(uVar3);
          y = *(int *)(iVar5 + 0x70);
          iVar5 = *(int *)(iVar5 + 0x6c);
          piVar2 = (int *)0x0;
          src = g_pSputRender_DecompressionBuffer;
        }
        else {
          y = *(int *)(iVar5 + 0x70);
          iVar5 = *(int *)(iVar5 + 0x6c);
          piVar2 = (int *)0x0;
          src = (void *)ObjectStateImage_VBuffer((int)this);
        }
        Surface_Blit(dst,src,iVar5,y,piVar2,iVar1);
        if (iVar4 != 0) {
          sputRender_MarkDirtyRect((int *)((int)this + 4),1);
        }
      }
    }
  }
  return;
}

/* ---- 0x004aa3e0  ObjectStateImage_InSync ---- */
/* Original name ObjectStateImage_InSync (the remaster's GrimFandango (Linux): same body (the
   bitmap's current frame +0x68 equals the drawn frame +0x6c)); was StateImage_IsCurrentFrame. */

int __fastcall ObjectStateImage_InSync(int param_1)

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
/* ObjectState record (0xfc bytes): +4 type, +8 setupIdx, +0xc bitmap StateImage, +0x80 depth
   StateImage, +0xf4 prev, +0xf8 next */

void * __thiscall
ObjectState_Construct(void *this,int type,char *bitmapName,char *zbufName,int setupIdx)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  
  ObjectStateImage_Construct((undefined4 *)((int)this + 0xc));
  ObjectStateImage_Construct((undefined4 *)((int)this + 0x80));
  *(undefined4 *)((int)this + 8) = 0xffffffff;
  *(int *)((int)this + 4) = setupIdx;
  ObjectStateImage_SetFile((undefined4 *)((int)this + 0xc),bitmapName);
  ObjectStateImage_SetFile((undefined4 *)((int)this + 0x80),zbufName);
  *(undefined4 *)((int)this + 0xf8) = 0;
  *(undefined4 *)((int)this + 0xf4) = 0;
  if (type != 0) {
    *(void **)(type + 0xf4) = this;
    *(int *)((int)this + 0xf8) = type;
  }
  *(undefined4 *)this = 0xfc;
  return this;
}
#undef local_10


/* ---- 0x004aa4c0  ObjectState_Destruct ---- */
void __fastcall ObjectState_Destruct(int param_1)

{
  
  if (*(int *)(param_1 + 0xf4) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0xf8) = *(undefined4 *)(param_1 + 0xf8);
  }
  if (*(int *)(param_1 + 0xf8) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0xf8) + 0xf4) = *(undefined4 *)(param_1 + 0xf4);
  }
  ObjectStateImage_Clear(param_1 + 0x80);
  ObjectStateImage_Clear(param_1 + 0xc);
  return;
}

/* ---- 0x004aa540  ObjectState_LoadResources ---- */
/* Original name ObjectState_LoadResources (the remaster's GrimFandango (Linux): same body
   (ObjectStateImage_Load(1) of the image +0xc and the z image +0x80)); was ObjectState_LoadImages.
    */

void __fastcall ObjectState_LoadResources(int param_1)

{
  ObjectStateImage_Load((void *)(param_1 + 0xc),1);
  ObjectStateImage_Load((void *)(param_1 + 0x80),1);
  return;
}

/* ---- 0x004aa560  ObjectState_UnLoadResources ---- */
/* Original name ObjectState_UnLoadResources (the remaster's GrimFandango (Linux): the unload
   counterpart (ObjectStateImage_Load(0) of both images; the remaster inlined it)); was
   ObjectState_UnloadBitmaps. */

void __fastcall ObjectState_UnLoadResources(int param_1)

{
  ObjectStateImage_Load((void *)(param_1 + 0xc),0);
  ObjectStateImage_Load((void *)(param_1 + 0x80),0);
  return;
}

/* ---- 0x004aa580  ObjectState_Reset ---- */
/* Type 3 states keep a copy of the background and depth under them Original name ObjectState_Reset
   (the remaster's GrimFandango (Linux): same body (for type 3: SetClean of both images from the
   background and the z buffer, frames -1); called by sputRender_UseSetup in both builds); was
   ObjectState_CaptureBackground. */

void __thiscall ObjectState_Reset(void *this,void *bg,void *zbuf)

{
  if (*(int *)((int)this + 4) == 3) {
    ObjectStateImage_SetClean((void *)((int)this + 0xc),bg);
    *(undefined4 *)((int)this + 0x78) = 0xffffffff;
    ObjectStateImage_SetClean((void *)((int)this + 0x80),zbuf);
    *(undefined4 *)((int)this + 0xec) = 0xffffffff;
  }
  return;
}

/* ---- 0x004aa5c0  ObjectState_Update ---- */
/* Draws the state when its type matches; type 3 only when the frame changed, invalidating its
   rectangle Original name ObjectState_Update (the remaster's GrimFandango (Linux): same parameters
   (type, buffer, z buffer) and body (for the matching type 3 state not in sync: draw the image and
   the z image, mark dirty); called by sputRender_Update in both builds); was ObjectState_Draw. */

void __thiscall ObjectState_Update(void *this,int type,void *dst,void *zdst)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  
  if (*(int *)((int)this + 4) == type) {
    if (*(int *)((int)this + 4) == 3) {
      iVar2 = 0;
      bVar1 = ObjectStateImage_InSync((int)this + 0xc);
      if (((uint)(bVar1)) == 0) {
        ObjectStateImage_Draw((void *)((int)this + 0xc),dst);
        if ((*(int *)((int)this + 0xb4) != 0) && (zdst != (void *)0x0)) {
          if (*(int *)((int)this + 0xb4) == 0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
          }
          *(undefined4 *)(*(int *)((int)this + 0xb8) + 0x68) = *(undefined4 *)((int)this + 0x78);
          ObjectStateImage_Draw((void *)((int)this + 0x80),zdst);
          iVar2 = 1;
        }
        MarkDirtyRect((int *)((int)this + 0x10),iVar2);
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
        MarkDirtyRect((int *)((int)this + 0x10),1);
      }
      ObjectStateImage_Draw((void *)((int)this + 0xc),dst);
      ObjectStateImage_Draw((void *)((int)this + 0x80),zdst);
    }
  }
  return;
}

/* ---- 0x004aa6b0  ObjectState_SetCopyMode ---- */
/* Stores the frame index into both StateImages Original name ObjectState_SetCopyMode (the
   remaster's GrimFandango (Linux): same body (the value into +0x7c and +0xf0); called by
   sputRoom_AddObjectState in both builds); was ObjectState_SetFrame. */

int __thiscall ObjectState_SetCopyMode(void *this,int a1)

{
  *(int *)((int)this + 0x7c) = a1;
  *(int *)((int)this + 0xf0) = a1;
  return a1;
}

/* ---- 0x004aa6c0  ObjectState_MoveToBack ---- */
/* Returns the new head of the setup's object state list Original name ObjectState_MoveToBack (the
   remaster's GrimFandango (Linux): ObjectState::MoveToBack in the remaster (a C++ method there);
   the only unmatched callee of Lua_SendObjectToBack; 1 matched neighbours agree, 0 disagree); was
   ObjectState_SendToBack. */

void * __thiscall ObjectState_MoveToBack(void *this,void *list)

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

/* ---- 0x004aa720  ObjectState_MoveToFront ---- */
/* Original name ObjectState_MoveToFront (the remaster's GrimFandango (Linux):
   ObjectState::MoveToFront in the remaster (a C++ method there); the only unmatched callee of
   Lua_SendObjectToFront; 1 matched neighbours agree, 0 disagree); was ObjectState_SendToFront. */

void * __thiscall ObjectState_MoveToFront(void *this,void *list)

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
