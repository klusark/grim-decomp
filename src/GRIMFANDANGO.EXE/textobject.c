/* GRIMFANDANGO.EXE :: textobject.c
 * functions 0x0048c470 .. 0x0048cba0 (4 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048c470  sputText_AddToQueue ---- */
/* Links a new text object into g_pTextQueue with its lifetime (ms, -1 = until killed) and flags (1
   keep, 2 hidden, 4 speech, 8 always draw) Original name sputText_AddToQueue (the remaster's
   GrimFandango (Linux): aligned call in sputActor_SayLine, sputText_MakeTextObjectL,
   sputText_PrintLineL); was TextObject_Activate. */

void __cdecl sputText_AddToQueue(TextObject *obj,int durationMs,int flags)

{
  int *piVar1;
  int iVar2;
  
  if (obj != (TextObject *)0x0) {
    obj->nDuration = durationMs;
    iVar2 = (obj->ctx).nX;
    obj->dwFlags = flags;
    piVar1 = (obj->ctx).pFont;
    obj->nX = iVar2;
    iVar2 = (obj->ctx).nY - *(int *)(*piVar1 + 8);
    obj->nY = iVar2;
    (obj->ctx).nY = iVar2;
    obj->pNext = g_pTextQueue;
    if (g_pTextQueue != (TextObject *)0x0) {
      g_pTextQueue->pPrev = obj;
    }
    g_pTextQueue = obj;
  }
  return;
}

/* ---- 0x0048c7e0  TextObject_New ---- */
TextObject * __cdecl TextObject_New(TextContext *ctx,char *text,int durationMs,int flags)

{
  int *piVar1;
  int *piVar2;
  TextObject *pTVar3;
  int iVar4;
  TextContext *pTVar5;
  TextContext *pTVar6;
  
  pTVar3 = (TextObject *)Memory_AllocFixed(g_pTextEventPool);
  if (pTVar3 != (TextObject *)0x0) {
    pTVar3->pNext = (TextObject *)0x0;
    pTVar3->pPrev = (TextObject *)0x0;
    strncpy(pTVar3->aText,text,0x1ff);
    pTVar3->aText[0x1ff] = '\0';
    pTVar3->nX = ctx->nX;
    pTVar3->nY = ctx->nY;
    pTVar5 = ctx;
    pTVar6 = &pTVar3->ctx;
    for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined4 *)pTVar6 = *(undefined4 *)pTVar5;
      pTVar5 = (TextContext *)&pTVar5->pClipRect;
      pTVar6 = (TextContext *)&pTVar6->pClipRect;
    }
    if (g_hEmergencyFont != (void *)0x0) {
      (pTVar3->ctx).pFont = g_hEmergencyFont;
    }
    piVar1 = pTVar3->aRect;
    (pTVar3->ctx).pColormap = g_abSputRender_colorMap;
    (pTVar3->ctx).pClipRect = piVar1;
    piVar2 = ctx->pClipRect;
    if (piVar2 != (int *)0x0) {
      *piVar1 = *piVar2;
      pTVar3->aRect[1] = piVar2[1];
      pTVar3->aRect[2] = piVar2[2];
      pTVar3->aRect[3] = piVar2[3];
      pTVar3->pActor = (Actor *)0x0;
      pTVar3->nSerial = (int)pTVar3;
      return pTVar3;
    }
    *piVar1 = 0;
    pTVar3->aRect[1] = 0;
    pTVar3->aRect[2] = UINT_008a94bc;
    pTVar3->aRect[3] = UINT_008a94c0;
    pTVar3->pActor = (Actor *)0x0;
    pTVar3->nSerial = (int)pTVar3;
  }
  return pTVar3;
}

/* ---- 0x0048c9f0  TextObject_Draw ---- */
void __cdecl TextObject_Draw(TextObject *obj,int invalidate)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  #define local_10 (*(uint *)(_frame + (0x20 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  if (obj != (TextObject *)0x0) {
    local_10 = obj->nX;
    piVar1 = (obj->ctx).pFont;
    (obj->ctx).nX = local_10;
    iVar5 = *(int *)(*piVar1 + 8) + obj->nY;
    (obj->ctx).nY = iVar5;
    local_c = iVar5 - *(int *)(*piVar1 + 8);
    local_8 = Text_GetStringWidth(&obj->ctx,obj->aText);
    local_4 = Text_GetStringHeight(&obj->ctx,obj->aText);
    if (((obj->ctx).dwFlags & 1) != 0) {
      local_10 = local_10 - (int)local_8 / 2;
    }
    uVar2 = (obj->ctx).dwFgColor;
    g_abSputRender_colorMap[0] =
         (ushort)((uVar2 >> 10 & 0x3f | ((int)uVar2 >> 3) << 6) << 5) |
         (ushort)(uVar2 >> 0x13) & 0x1f;
    uVar3 = (obj->ctx).dwBgColor;
    g_abSputRender_colorMap[1] =
         (ushort)((uVar3 >> 10 & 0x3f | ((int)uVar3 >> 3) << 6) << 5) |
         (ushort)(uVar3 >> 0x13) & 0x1f;
    uVar4 = (obj->ctx).dwFxColor;
    g_abSputRender_colorMap[2] =
         (ushort)((uVar4 >> 10 & 0x3f | ((int)uVar4 >> 3) << 6) << 5) |
         (ushort)(uVar4 >> 0x13) & 0x1f;
    sputRender_ColorCorrect(g_abSputRender_colorMap,3);
    (obj->ctx).dwFgColor = 0;
    (obj->ctx).dwBgColor = 1;
    (obj->ctx).dwFxColor = 2;
    Text_DrawFormatted(&obj->ctx,obj->aText);
    (obj->ctx).nX = obj->nX;
    (obj->ctx).nY = *(int *)(*(int *)(obj->ctx).pFont + 8) + obj->nY;
    if (invalidate != 0) {
      sputRender_MarkDirtyRect((int *)&local_10,0);
    }
    (obj->ctx).dwFxColor = uVar4;
    (obj->ctx).dwBgColor = uVar3;
    (obj->ctx).dwFgColor = uVar2;
  }
  return;
}
#undef local_10
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0048cba0  sputText_FindSerialNumber ---- */
/* Original name sputText_FindSerialNumber (the remaster's GrimFandango (Linux): the text object of
   the text queue with the serial number; called by sputActor_Restore and sputLua_RestoreIndirector
   in both builds (the remaster also compares a second field)); was TextObject_FindBySelf. */

TextObject * __cdecl sputText_FindSerialNumber(int serial)

{
  TextObject *pTVar1;
  
  pTVar1 = g_pTextQueue;
  while( true ) {
    if (pTVar1 == (TextObject *)0x0) {
      return (TextObject *)0x0;
    }
    if (pTVar1->nSerial == serial) break;
    pTVar1 = pTVar1->pNext;
  }
  return pTVar1;
}
