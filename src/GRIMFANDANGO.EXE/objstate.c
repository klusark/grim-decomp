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

ObjectState * __cdecl
sputRoom_AddObjectState(int setupIdx,int type,char *bitmap,char *zbitmap,int visible)

{
  Setup *pSVar1;
  Set *pSVar2;
  ObjectState *pOVar3;
  
  pSVar2 = sputRoom_GetCurrentRoom();
  pSVar1 = pSVar2->pSetups;
  pOVar3 = Plat_Alloc(0xfc);
  if (pOVar3 == (ObjectState *)0x0) {
    pOVar3 = (ObjectState *)0x0;
  }
  else {
    pOVar3 = ObjectState_Construct
                       (pOVar3,pSVar1[setupIdx].pObjectStates,bitmap,zbitmap,type);
  }
  pSVar1[setupIdx].pObjectStates = pOVar3;
  if (pOVar3 == (ObjectState *)0x0) {
    return (ObjectState *)0x0;
  }
  Mem_CheckAlloc(pOVar3,s_C__grimsrc_libs_grimlib_Engine_s_004ec5e0,0x992);
  ObjectState_LoadResources(pSVar1[setupIdx].pObjectStates);
  (pSVar1[setupIdx].pObjectStates)->nState = setupIdx;
  if (visible < 0) {
    visible = (int)(type == 3);
  }
  ObjectState_SetCopyMode(pSVar1[setupIdx].pObjectStates,visible);
  pOVar3 = pSVar1[setupIdx].pObjectStates;
  return pOVar3;
}

/* ---- 0x004a5e50  sputRoom_RemoveObjectState ---- */
/* Original name sputRoom_RemoveObjectState (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_FreeObjectState; 1 matched neighbours agree, 1 disagree); was ObjectState_Free. */

void __cdecl sputRoom_RemoveObjectState(ObjectState *state)

{
  int iVar1;
  Setup *pSVar2;
  Set *pSVar3;
  ObjectState *pOVar4;
  
  if (state != (ObjectState *)0x0) {
    iVar1 = state->nState;
    pSVar3 = sputRoom_GetCurrentRoom();
    pSVar2 = pSVar3->pSetups;
    pOVar4 = pSVar2[iVar1].pObjectStates;
    if (pOVar4 == state) {
      pOVar4 = state->pNext;
    }
    ObjectState_Destruct(state);
    Plat_Free(state);
    pSVar2[iVar1].pObjectStates = pOVar4;
  }
  return;
}

/* ---- 0x004aa070  ObjectStateImage_Construct ---- */
/* Original name ObjectStateImage_Construct (the remaster's GrimFandango (Linux): same body (the
   record cleared, +0x6c = -1)); was StateImage_Construct. */

undefined4 * __fastcall ObjectStateImage_Construct(ObjectStateImage *image)

{
  int iVar1;
  ResRef *pRVar2;
  
  image->aName[0] = '\0';
  image->aName[1] = '\0';
  image->aName[2] = '\0';
  image->aName[3] = '\0';
  pRVar2 = &image->ref;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    pRVar2->nValid = 0;
    pRVar2 = (ResRef *)&pRVar2->pData;
  }
  image->pClean = (VBuffer *)0x0;
  image->nDrawn = 0;
  image->nFrame = -1;
  image->nMemUsage = 0x74;
  return &image->nMemUsage;
}

/* ---- 0x004aa0b0  ObjectStateImage_Clear ---- */
/* ObjectState.cpp: C++ image member (0x74 bytes: +4 rect, +0x14 name, +0x34 ResRef, +0x68 surface,
   +0x6c frame, +0x70 drawn). Drops the bitmap reference and surface Original name
   ObjectStateImage_Clear (the remaster's GrimFandango (Linux): same body (release the bitmap
   reference +0x34, free the VBuffer +0x68, frame -1, empty name); SetFile and Load inline it in the
   remaster); was StateImage_Release. */

void __fastcall ObjectStateImage_Clear(ObjectStateImage *image)

{
  if ((image->ref).nValid != 0) {
    Res_RemoveReference(&image->ref);
  }
  if (image->pClean != (VBuffer *)0x0) {
    stdDisplay_VBufferFree(image->pClean);
    image->pClean = (VBuffer *)0x0;
  }
  image->nFrame = -1;
  image->aName[0] = '\0';
  image->nDrawn = 0;
  return;
}

/* ---- 0x004aa100  ObjectStateImage_SetFile ---- */
/* Original name ObjectStateImage_SetFile (the remaster's GrimFandango (Linux): same body (Clear,
   then strncpy of the file name, 0x20 chars, to +0x14)); was StateImage_Init. */

void __thiscall ObjectStateImage_SetFile(ObjectStateImage *this,char *name)

{
  ObjectStateImage_Clear(this);
  if (name != (char *)0x0) {
    strncpy((uint *)this->aName,(uint *)name,0x20);
  }
  return;
}

/* ---- 0x004aa130  ObjectStateImage_Load ---- */
/* Loads (or releases) the BKND bitmap named in the image and takes its position and size Original
   name ObjectStateImage_Load (the remaster's GrimFandango (Linux): same body (unload, or load the
   named bitmap into +0x34 when not loaded yet)); was StateImage_Load. */

void __thiscall ObjectStateImage_Load(ObjectStateImage *this,int load)

{
  stdBitmap *bitmap;
  int iVar1;
  
  if ((load == 0) || (this->aName[0] == '\0')) {
    if ((this->ref).nValid != 0) {
      Res_RemoveReference(&this->ref);
    }
    if (this->pClean != (VBuffer *)0x0) {
      stdDisplay_VBufferFree(this->pClean);
      this->pClean = (VBuffer *)0x0;
    }
  }
  else if ((this->ref).nValid == 0) {
    bitmap = sputResource_Alloc(0x444e4b42,this->aName);
    if (bitmap != (stdBitmap *)0x0) {
      Res_SetReference(&this->ref,bitmap,s_C__grimsrc_libs_grimlib_Engine_O_004ec9d0,0x3d);
      this->nX = bitmap->nX;
      this->nY = bitmap->nY;
      this->nWidth = ((*bitmap->ppFrames)->format).nWidth;
      this->nHeight = ((*bitmap->ppFrames)->format).nHeight;
      bitmap->nCurFrame = this->nFrame;
      iVar1 = stdBitmap_MemUsage(bitmap);
      this->nMemUsage = this->nMemUsage + iVar1;
      return;
    }
  }
  return;
}

/* ---- 0x004aa1f0  ObjectStateImage_VBuffer ---- */
/* Original name ObjectStateImage_VBuffer (the remaster's GrimFandango (Linux): same body (the
   current frame's VBuffer of the bitmap, "Bad Bitmap Reference" assert of sputResource.h, or the
   clean copy at +0x68)); was StateImage_GetFrameSurface. */

undefined4 __fastcall ObjectStateImage_VBuffer(ObjectStateImage *image)

{
  if (-1 < image->nFrame) {
    if ((image->ref).nValid == 0) {
      (*g_pStd_HS->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90)
      ;
    }
    if (*(int *)((int)(image->ref).pData + 100) <= image->nFrame) {
      if ((image->ref).nValid == 0) {
        (*g_pStd_HS->pAssertFail)
                  (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
      }
      image->nFrame = *(int *)((int)(image->ref).pData + 100) + -1;
    }
    if ((image->ref).nValid == 0) {
      (*g_pStd_HS->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90)
      ;
    }
    return *(undefined4 *)(*(int *)((int)(image->ref).pData + 0x78) + image->nFrame * 4);
  }
  return image->pClean;
}

/* ---- 0x004aa290  ObjectStateImage_SetClean ---- */
/* Copies the image rectangle out of a surface into a private surface Original name
   ObjectStateImage_SetClean (the remaster's GrimFandango (Linux): same body (free +0x68, a new
   VBuffer of the bitmap's format, copy the rectangle of the given buffer into it)); was
   StateImage_CaptureFrom. */

void __thiscall ObjectStateImage_SetClean(ObjectStateImage *this,void *surface)

{
  int iVar1;
  VBuffer *dst;
  
  if (this->pClean != (VBuffer *)0x0) {
    stdDisplay_VBufferFree(this->pClean);
  }
  iVar1 = (this->ref).nValid;
  if (iVar1 != 0) {
    if (iVar1 == 0) {
      (*g_pStd_HS->pAssertFail)(s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90)
      ;
    }
    dst = stdDisplay_VBufferNew
                    ((VBufferFormat *)(**(int **)((int)(this->ref).pData + 0x78) + 0xc),0,0,0);
    this->pClean = dst;
    if (dst != (VBuffer *)0x0) {
      Surface_Blit(dst,surface,0,0,&this->nX,0);
    }
  }
  return;
}

/* ---- 0x004aa310  ObjectStateImage_Draw ---- */
/* Original name ObjectStateImage_Draw (the remaster's GrimFandango (Linux): the image draw
   ObjectState_Update calls in both builds (the frame, the copy into the destination, the dirty
   rectangle); the remaster split the set-up into SetupDraw); was StateImage_Draw. */

void __thiscall ObjectStateImage_Draw(ObjectStateImage *this,void *dst)

{
  void *pvVar1;
  int iVar2;
  int *piVar3;
  VBuffer *pVVar4;
  int iVar5;
  int x;
  int y;
  
  if ((this->aName[0] != '\0') && (dst != (void *)0x0)) {
    iVar2 = (this->ref).nValid;
    iVar5 = this->nDrawn;
    if (iVar2 != 0) {
      if (iVar2 == 0) {
        (*g_pStd_HS->pAssertFail)
                  (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
      }
      pvVar1 = (this->ref).pData;
      iVar2 = *(int *)((int)pvVar1 + 0x68);
      this->nFrame = iVar2;
      if (iVar2 == -1) {
        iVar5 = 0;
      }
      iVar2 = ObjectStateImage_VBuffer(this);
      if (iVar2 != 0) {
        piVar3 = (int *)ObjectStateImage_VBuffer(this);
        iVar2 = iVar5;
        if (*piVar3 == 2) {
          pVVar4 = (VBuffer *)ObjectStateImage_VBuffer(this);
          sputRender_Decompress(pVVar4);
          y = *(int *)((int)pvVar1 + 0x70);
          x = *(int *)((int)pvVar1 + 0x6c);
          piVar3 = (int *)0x0;
          pVVar4 = g_pSputRender_DecompressionBuffer;
        }
        else {
          y = *(int *)((int)pvVar1 + 0x70);
          x = *(int *)((int)pvVar1 + 0x6c);
          piVar3 = (int *)0x0;
          pVVar4 = (VBuffer *)ObjectStateImage_VBuffer(this);
        }
        Surface_Blit(dst,pVVar4,x,y,piVar3,iVar2);
        if (iVar5 != 0) {
          sputRender_MarkDirtyRect(&this->nX,1);
        }
      }
    }
  }
  return;
}

/* ---- 0x004aa3e0  ObjectStateImage_InSync ---- */
/* Original name ObjectStateImage_InSync (the remaster's GrimFandango (Linux): same body (the
   bitmap's current frame +0x68 equals the drawn frame +0x6c)); was StateImage_IsCurrentFrame. */

int __fastcall ObjectStateImage_InSync(ObjectStateImage *image)

{
  if (image->aName[0] == '\0') {
    return true;
  }
  if ((image->ref).nValid == 0) {
    return false;
  }
  return *(int *)((int)(image->ref).pData + 0x68) == image->nFrame;
}

/* ---- 0x004aa410  ObjectState_Construct ---- */
/* ObjectState record (0xfc bytes): +4 type, +8 setupIdx, +0xc bitmap StateImage, +0x80 depth
   StateImage, +0xf4 prev, +0xf8 next */

ObjectState * __thiscall
ObjectState_Construct
          (ObjectState *this,ObjectState *next,char *bitmapName,char *zbufName,int setupIdx)

{
  uint local_10;
  
  ObjectStateImage_Construct(&this->image);
  ObjectStateImage_Construct(&this->zImage);
  this->nState = -1;
  this->nSetup = setupIdx;
  ObjectStateImage_SetFile(&this->image,bitmapName);
  ObjectStateImage_SetFile(&this->zImage,zbufName);
  this->pNext = (ObjectState *)0x0;
  this->pPrev = (ObjectState *)0x0;
  if (next != (ObjectState *)0x0) {
    next->pPrev = this;
    this->pNext = next;
  }
  this->nSize = 0xfc;
  return this;
}

/* ---- 0x004aa4c0  ObjectState_Destruct ---- */
void __fastcall ObjectState_Destruct(ObjectState *state)

{
  
  if (state->pPrev != (ObjectState *)0x0) {
    state->pPrev->pNext = state->pNext;
  }
  if (state->pNext != (ObjectState *)0x0) {
    state->pNext->pPrev = state->pPrev;
  }
  ObjectStateImage_Clear(&state->zImage);
  ObjectStateImage_Clear(&state->image);
  return;
}

/* ---- 0x004aa540  ObjectState_LoadResources ---- */
/* Original name ObjectState_LoadResources (the remaster's GrimFandango (Linux): same body
   (ObjectStateImage_Load(1) of the image +0xc and the z image +0x80)); was ObjectState_LoadImages.
    */

void __fastcall ObjectState_LoadResources(ObjectState *state)

{
  ObjectStateImage_Load(&state->image,1);
  ObjectStateImage_Load(&state->zImage,1);
  return;
}

/* ---- 0x004aa560  ObjectState_UnLoadResources ---- */
/* Original name ObjectState_UnLoadResources (the remaster's GrimFandango (Linux): the unload
   counterpart (ObjectStateImage_Load(0) of both images; the remaster inlined it)); was
   ObjectState_UnloadBitmaps. */

void __fastcall ObjectState_UnLoadResources(ObjectState *state)

{
  ObjectStateImage_Load(&state->image,0);
  ObjectStateImage_Load(&state->zImage,0);
  return;
}

/* ---- 0x004aa580  ObjectState_Reset ---- */
/* Type 3 states keep a copy of the background and depth under them Original name ObjectState_Reset
   (the remaster's GrimFandango (Linux): same body (for type 3: SetClean of both images from the
   background and the z buffer, frames -1); called by sputRender_UseSetup in both builds); was
   ObjectState_CaptureBackground. */

void __thiscall ObjectState_Reset(ObjectState *this,void *bg,void *zbuf)

{
  if (this->nSetup == 3) {
    ObjectStateImage_SetClean(&this->image,bg);
    (this->image).nFrame = -1;
    ObjectStateImage_SetClean(&this->zImage,zbuf);
    (this->zImage).nFrame = -1;
  }
  return;
}

/* ---- 0x004aa5c0  ObjectState_Update ---- */
/* Draws the state when its type matches; type 3 only when the frame changed, invalidating its
   rectangle Original name ObjectState_Update (the remaster's GrimFandango (Linux): same parameters
   (type, buffer, z buffer) and body (for the matching type 3 state not in sync: draw the image and
   the z image, mark dirty); called by sputRender_Update in both builds); was ObjectState_Draw. */

void __thiscall ObjectState_Update(ObjectState *this,int type,void *dst,void *zdst)

{
  int iVar1;
  bool bVar2;
  undefined3 extraout_var;
  int iVar3;
  
  if (this->nSetup == type) {
    if (this->nSetup == 3) {
      iVar3 = 0;
      bVar2 = ObjectStateImage_InSync(&this->image);
      if (((uint)(byte)(bVar2)) == 0) {
        ObjectStateImage_Draw(&this->image,dst);
        iVar1 = (this->zImage).ref.nValid;
        if ((iVar1 != 0) && (zdst != (void *)0x0)) {
          if (iVar1 == 0) {
            (*g_pStd_HS->pAssertFail)
                      (s_Bad_Bitmap_Reference_004e8114,s_main_sputResource_h_004e80a8,0x90);
          }
          *(int *)((int)(this->zImage).ref.pData + 0x68) = (this->image).nFrame;
          ObjectStateImage_Draw(&this->zImage,zdst);
          iVar3 = 1;
        }
        MarkDirtyRect(&(this->image).nX,iVar3);
        return;
      }
    }
    else {
      if ((this->image).ref.nValid == 0) {
        iVar3 = -1;
      }
      else {
        iVar3 = *(int *)((int)(this->image).ref.pData + 0x68);
      }
      if ((iVar3 == -1) && ((this->image).nFrame != -1)) {
        MarkDirtyRect(&(this->image).nX,1);
      }
      ObjectStateImage_Draw(&this->image,dst);
      ObjectStateImage_Draw(&this->zImage,zdst);
    }
  }
  return;
}

/* ---- 0x004aa6b0  ObjectState_SetCopyMode ---- */
/* Stores the frame index into both StateImages Original name ObjectState_SetCopyMode (the
   remaster's GrimFandango (Linux): same body (the value into +0x7c and +0xf0); called by
   sputRoom_AddObjectState in both builds); was ObjectState_SetFrame. */

int __thiscall ObjectState_SetCopyMode(ObjectState *this,int a1)

{
  (this->image).nDrawn = a1;
  (this->zImage).nDrawn = a1;
  return a1;
}

/* ---- 0x004aa6c0  ObjectState_MoveToBack ---- */
/* Returns the new head of the setup's object state list Original name ObjectState_MoveToBack (the
   remaster's GrimFandango (Linux): ObjectState::MoveToBack in the remaster (a C++ method there);
   the only unmatched callee of Lua_SendObjectToBack; 1 matched neighbours agree, 0 disagree); was
   ObjectState_SendToBack. */

void * __thiscall ObjectState_MoveToBack(ObjectState *this,ObjectState *list)

{
  if (list != this) {
    if (this->pPrev != (ObjectState *)0x0) {
      this->pPrev->pNext = this->pNext;
    }
    if (this->pNext != (ObjectState *)0x0) {
      this->pNext->pPrev = this->pPrev;
    }
    list->pPrev = this;
    this->pPrev = (ObjectState *)0x0;
    this->pNext = list;
  }
  return this;
}

/* ---- 0x004aa720  ObjectState_MoveToFront ---- */
/* Original name ObjectState_MoveToFront (the remaster's GrimFandango (Linux):
   ObjectState::MoveToFront in the remaster (a C++ method there); the only unmatched callee of
   Lua_SendObjectToFront; 1 matched neighbours agree, 0 disagree); was ObjectState_SendToFront. */

void * __thiscall ObjectState_MoveToFront(ObjectState *this,ObjectState *list)

{
  ObjectState *pOVar1;
  ObjectState *pOVar2;
  ObjectState *pOVar3;
  
  pOVar3 = list;
  if (this == list) {
    if (list->pNext == (ObjectState *)0x0) {
      return list;
    }
    pOVar3 = this->pNext;
    pOVar3->pPrev = (ObjectState *)0x0;
  }
  pOVar2 = list->pNext;
  while (pOVar1 = pOVar2, pOVar1 != (ObjectState *)0x0) {
    list = pOVar1;
    pOVar2 = pOVar1->pNext;
  }
  if (this->pNext != (ObjectState *)0x0) {
    this->pNext->pPrev = this->pPrev;
  }
  if (this->pPrev != (ObjectState *)0x0) {
    this->pPrev->pNext = this->pNext;
  }
  list->pNext = this;
  this->pPrev = list;
  this->pNext = (ObjectState *)0x0;
  return pOVar3;
}
