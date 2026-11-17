/* GRIMFANDANGO.EXE :: sputtext.c
 * functions 0x0048acc0 .. 0x0048cd80 (6 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x0048acc0  sputText_Initialize ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Subsystem init entry registered through EngineModule_Init; fills the module's 8-entry interface
   {init, shutdown, save, restore, ...} */

uint __cdecl sputText_Initialize(GrimServices *svc,undefined4 *iface)

{
  int iVar1;
  
  _g_pSputtextHS = svc;
  *iface = sputText_Initialize;
  iface[1] = sputText_Terminate;
  iface[2] = sputText_Startup;
  iface[3] = sputText_Shutdown;
  iface[4] = sputText_Save;
  iface[5] = sputText_Restore;
  iface[6] = 0;
  iface[7] = 0;
  iVar1 = Graph_SysInitialize(svc,&g_aGraphMS);
  if (iVar1 == 0) {
    iVar1 = Text_SysInitialize(svc,&g_aTextMS);
    if (iVar1 == 0) {
      g_dwSputtextInitialize = 1;
      return 0;
    }
  }
  return 1;
}

/* ---- 0x0048c4d0  sputText_Terminate ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Module interface slot 1 (sputText): called by Engine_ResetSubsystems / when registration fails;
   drops the service table pointer and clears the initialised flag. */

void __cdecl sputText_Terminate(void)

{
  _g_pSputtextHS = 0;
  (*g_aGraphMS.pfnTerminate)();
  (*g_aTextMS.pfnTerminate)();
  if (g_dwSputtextInitialize != 0) {
    g_dwSputtextInitialize = 0;
  }
  return;
}

/* ---- 0x0048c500  sputText_Startup ---- */
/* Module interface slot 2 (sputText): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). _Start registers the text Lua API table and the
   field-name refs (fgcolor, justify, ...), creates the 0x260-byte text object pool. */

uint __cdecl sputText_Startup(void)

{
  undefined uVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  
  if (g_dwSputtextStartup == 0) {
    uVar1 = (*g_aGraphMS.pfnStartup)();
    if (((uint)(byte)(uVar1)) == 0) {
      uVar1 = (*g_aTextMS.pfnStartup)();
      if (((uint)(byte)(uVar1)) == 0) {
        g_PrintLineTextCtx.pFont = Text_GetSystemFont();
        g_SubtitleTextCtx.pFont = g_PrintLineTextCtx.pFont;
        g_TextObjectCtx.pFont = g_PrintLineTextCtx.pFont;
        g_hFont = (uint)g_PrintLineTextCtx.pFont;
        sputLua_RegisterFunctions((int *)&g_pTextFunctionsToRegister,UINT_004e85d8);
        lua_pushstring(s_x_004e8454);
        g_dwLrX = lua_ref(1);
        lua_pushstring(s_y_004e8450);
        g_dwLrY = lua_ref(1);
        lua_pushstring(s_font_004e87c0);
        g_dwLrFont = lua_ref(1);
        lua_pushstring(s_width_004e8440);
        g_dwLrWidth = lua_ref(1);
        lua_pushstring(s_height_004e8438);
        g_dwLrHeight = lua_ref(1);
        lua_pushstring(s_fgcolor_004e87b8);
        g_dwLrFGColor = lua_ref(1);
        lua_pushstring(s_bgcolor_004e87b0);
        g_dwLrBGColor = lua_ref(1);
        lua_pushstring(s_fxcolor_004e87a8);
        g_dwLrFXColor = lua_ref(1);
        lua_pushstring(s_hicolor_004e87a0);
        g_dwLrHiColor = lua_ref(1);
        lua_pushstring(s_duration_004e8794);
        g_dwLrDuration = lua_ref(1);
        lua_pushstring(s_center_004e878c);
        g_dwLrCenter = lua_ref(1);
        lua_pushstring(s_ljustify_004e8780);
        g_dwLrLJustify = lua_ref(1);
        lua_pushstring(s_rjustify_004e8774);
        g_dwLrRJustify = lua_ref(1);
        lua_pushstring(s_volume_004e876c);
        g_dwLrVolume = lua_ref(1);
        lua_pushstring(s_pan_004e8768);
        g_dwLrPan = lua_ref(1);
        lua_pushstring(s_background_004e875c);
        g_dwLrBackground = lua_ref(1);
        g_pTextEventPool = Memory_AllocatePool(0x260,(void *)0x10,(void *)0x8);
        g_dwSputtextStartup = 1;
        return 0;
      }
    }
  }
  return 1;
}

/* ---- 0x0048c6f0  sputText_Shutdown ---- */
/* Module interface slot 3 (sputText): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name sputText_Shutdown (the remaster's GrimFandango
   (Linux): the module's shutdown slot: graphMS / textMS shutdown, lua_unref of every lr*
   reference); was sputText_Stop. */

void __cdecl sputText_Shutdown(void)

{
  (*g_aGraphMS.pfnShutdown)();
  (*g_aTextMS.pfnShutdown)();
  lua_unref(g_dwLrX);
  lua_unref(g_dwLrY);
  lua_unref(g_dwLrFont);
  lua_unref(g_dwLrWidth);
  lua_unref(g_dwLrHeight);
  lua_unref(g_dwLrFGColor);
  lua_unref(g_dwLrBGColor);
  lua_unref(g_dwLrFXColor);
  lua_unref(g_dwLrHiColor);
  lua_unref(g_dwLrDuration);
  lua_unref(g_dwLrCenter);
  lua_unref(g_dwLrLJustify);
  lua_unref(g_dwLrRJustify);
  lua_unref(g_dwLrVolume);
  lua_unref(g_dwLrPan);
  lua_unref(g_dwLrBackground);
  if (g_pTextEventPool != (void **)0x0) {
    Memory_FreePool(g_pTextEventPool);
    g_pTextEventPool = (void **)0x0;
  }
  g_dwSputtextStartup = 0;
  return;
}

/* ---- 0x0048cbc0  sputText_Save ---- */
/* Module interface slot 4 (sputText): save-game writer, calls the SaveGame_Write callback it is
   handed for every field. Original name sputText_Save (the remaster's GrimFandango (Linux): aligned
   call in sputText_Initialize); was sputText_SaveState. */

uint __cdecl sputText_Save(code *write)

{
  TextObject *pTVar1;
  undefined uVar2;
  undefined3 extraout_var;
  uint local_4;
  
  local_4 = 0;
  for (pTVar1 = g_pTextQueue; pTVar1 != (TextObject *)0x0; pTVar1 = pTVar1->pNext) {
    local_4 = local_4 + 1;
  }
  uVar2 = (*write)(&local_4,4);
  pTVar1 = g_pTextQueue;
  if (((uint)(byte)(uVar2)) != 0) {
    return 1;
  }
  for (; pTVar1 != (TextObject *)0x0; pTVar1 = pTVar1->pNext) {
    pTVar1->nSerial = (int)pTVar1;
    (*write)(pTVar1->aText,0x200);
    (*write)(&pTVar1->ctx,4);
    (*write)(&(pTVar1->ctx).pClipRect,4);
    (*write)(&(pTVar1->ctx).pFont,4);
    (*write)(&(pTVar1->ctx).nX,4);
    (*write)(&(pTVar1->ctx).nY,4);
    (*write)(&(pTVar1->ctx).dwFgColor,4);
    (*write)(&(pTVar1->ctx).dwBgColor,4);
    (*write)(&(pTVar1->ctx).dwFxColor,4);
    (*write)(&(pTVar1->ctx).nScaleX,4);
    (*write)(&(pTVar1->ctx).nScaleY,4);
    (*write)(&(pTVar1->ctx).dwFlags,4);
    (*write)(&pTVar1->nX,4);
    (*write)(&pTVar1->nY,4);
    (*write)(pTVar1->aRect,4);
    (*write)(pTVar1->aRect + 1,4);
    (*write)(pTVar1->aRect + 2,4);
    (*write)(pTVar1->aRect + 3,4);
    (*write)(&pTVar1->nDuration,4);
    (*write)(&pTVar1->pActor,4);
    (*write)(&pTVar1->dwFlags,4);
    (*write)(&pTVar1->nSerial,4);
  }
  (*write)(((unsigned)(uintptr_t)((unsigned char *)&g_PrintLineTextCtx + 0x8)),4);
  (*write)(((unsigned)(uintptr_t)((unsigned char *)&g_SubtitleTextCtx + 0x8)),4);
  (*write)(((unsigned)(uintptr_t)((unsigned char *)&g_TextObjectCtx + 0x8)),4);
  return 0;
}

/* ---- 0x0048cd80  sputText_Restore ---- */
/* Module interface slot 5 (sputText): save-game reader, calls the SaveGame_Read callback it is
   handed; returns non-zero on a short read. Original name sputText_Restore (the remaster's
   GrimFandango (Linux): the module's restore slot: empties textQueue, reads the text events into
   pTextEventPool); was sputText_RestoreState. */

uint __cdecl sputText_Restore(code *read)

{
  TextContext *pTVar1;
  void **ppvVar2;
  code *pcVar3;
  undefined uVar4;
  undefined3 extraout_var;
  TextObject *pTVar5;
  void *pvVar6;
  int local_4;
  
  pcVar3 = read;
  while (g_pTextQueue != (TextObject *)0x0) {
    List_Unlink(g_pTextQueue);
  }
  uVar4 = (*read)(&local_4,4);
  if (((uint)(byte)(uVar4)) == 0) {
    read = (code *)0x0;
    if (0 < local_4) {
      do {
        pTVar5 = (TextObject *)Memory_AllocFixed((int *)g_pTextEventPool);
        (*pcVar3)(pTVar5->aText,0x200);
        pTVar1 = &pTVar5->ctx;
        (*pcVar3)(pTVar1,4);
        (*pcVar3)(&(pTVar5->ctx).pClipRect,4);
        ppvVar2 = &(pTVar5->ctx).pFont;
        (*pcVar3)(ppvVar2,4);
        (*pcVar3)(&(pTVar5->ctx).nX,4);
        (*pcVar3)(&(pTVar5->ctx).nY,4);
        (*pcVar3)(&(pTVar5->ctx).dwFgColor,4);
        (*pcVar3)(&(pTVar5->ctx).dwBgColor,4);
        (*pcVar3)(&(pTVar5->ctx).dwFxColor,4);
        (*pcVar3)(&(pTVar5->ctx).nScaleX,4);
        (*pcVar3)(&(pTVar5->ctx).nScaleY,4);
        (*pcVar3)(&(pTVar5->ctx).dwFlags,4);
        (*pcVar3)(&pTVar5->nX,4);
        (*pcVar3)(&pTVar5->nY,4);
        (*pcVar3)(pTVar5->aRect,4);
        (*pcVar3)(pTVar5->aRect + 1,4);
        (*pcVar3)(pTVar5->aRect + 2,4);
        (*pcVar3)(pTVar5->aRect + 3,4);
        (*pcVar3)(&pTVar5->nDuration,4);
        (*pcVar3)(&pTVar5->pActor,4);
        (*pcVar3)(&pTVar5->dwFlags,4);
        (*pcVar3)(&pTVar5->nSerial,4);
        pvVar6 = Res_HandleFromSerialNumber(*ppvVar2);
        *ppvVar2 = pvVar6;
        if (pTVar1->pUnused != (void *)0x0) {
          pTVar1->pUnused = &UINT_008a94b8;
        }
        if ((pTVar5->ctx).pClipRect != (int *)0x0) {
          (pTVar5->ctx).pClipRect = pTVar5->aRect;
        }
        (pTVar5->ctx).pColormap = g_abSputRender_colorMap;
        pTVar5->pPrev = (TextObject *)0x0;
        pTVar5->pNext = g_pTextQueue;
        if (g_pTextQueue != (TextObject *)0x0) {
          g_pTextQueue->pPrev = pTVar5;
        }
        read = read + 1;
        g_pTextQueue = pTVar5;
      } while ((int)read < local_4);
    }
    (*pcVar3)(((unsigned)(uintptr_t)((unsigned char *)&g_PrintLineTextCtx + 0x8)),4);
    (*pcVar3)(((unsigned)(uintptr_t)((unsigned char *)&g_SubtitleTextCtx + 0x8)),4);
    (*pcVar3)(((unsigned)(uintptr_t)((unsigned char *)&g_TextObjectCtx + 0x8)),4);
    g_hFont = (uint)Text_GetSystemFont();
    g_PrintLineTextCtx.pFont = Res_HandleFromSerialNumber(g_PrintLineTextCtx.pFont);
    g_SubtitleTextCtx.pFont = Res_HandleFromSerialNumber(g_SubtitleTextCtx.pFont);
    g_TextObjectCtx.pFont = Res_HandleFromSerialNumber(g_TextObjectCtx.pFont);
    if (g_PrintLineTextCtx.pFont == (void *)0x0) {
      g_PrintLineTextCtx.pFont = (void *)g_hFont;
    }
    if (g_SubtitleTextCtx.pFont == (void *)0x0) {
      g_SubtitleTextCtx.pFont = (void *)g_hFont;
    }
    if (g_TextObjectCtx.pFont == (void *)0x0) {
      g_TextObjectCtx.pFont = (void *)g_hFont;
    }
    return 0;
  }
  return 1;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern char f_sputText_BlastText[] __asm__("_sputText_BlastText");
extern char f_sputText_ChangeTextObjectL[] __asm__("_sputText_ChangeTextObjectL");
extern char f_sputText_ExpireTextQueueL[] __asm__("_sputText_ExpireTextQueueL");
extern char f_sputText_GetActorTalkColorL[] __asm__("_sputText_GetActorTalkColorL");
extern char f_sputText_GetColorComponentsL[] __asm__("_sputText_GetColorComponentsL");
extern char f_sputText_GetFontDimensionsL[] __asm__("_sputText_GetFontDimensionsL");
extern char f_sputText_GetTextCharPositionL[] __asm__("_sputText_GetTextCharPositionL");
extern char f_sputText_GetTextObjectDimensionsL[] __asm__("_sputText_GetTextObjectDimensionsL");
extern char f_sputText_GetTranslationModeL[] __asm__("_sputText_GetTranslationModeL");
extern char f_sputText_IsMessageGoingL[] __asm__("_sputText_IsMessageGoingL");
extern char f_sputText_KillTextObjectL[] __asm__("_sputText_KillTextObjectL");
extern char f_sputText_LocalizeStringL[] __asm__("_sputText_LocalizeStringL");
extern char f_sputText_MakeColorL[] __asm__("_sputText_MakeColorL");
extern char f_sputText_MakeTextObjectL[] __asm__("_sputText_MakeTextObjectL");
extern char f_sputText_PrintLineL[] __asm__("_sputText_PrintLineL");
extern char f_sputText_PurgeTextQueueL[] __asm__("_sputText_PurgeTextQueueL");
extern char f_sputText_SayLineL[] __asm__("_sputText_SayLineL");
extern char f_sputText_SetActorTalkColorL[] __asm__("_sputText_SetActorTalkColorL");
extern char f_sputText_SetEmergencyFontL[] __asm__("_sputText_SetEmergencyFontL");
extern char f_sputText_SetOffscreenTextPosL[] __asm__("_sputText_SetOffscreenTextPosL");
extern char f_sputText_SetSayLineDefaultsL[] __asm__("_sputText_SetSayLineDefaultsL");
extern char f_sputText_SetTranslationModeL[] __asm__("_sputText_SetTranslationModeL");
extern unsigned int grim_def_UINT_004e85d8 __asm__("_UINT_004e85d8");
extern SysModuleIface grim_def_g_aGraphMS __asm__("_g_aGraphMS");
extern SysModuleIface grim_def_g_aTextMS __asm__("_g_aTextMS");
extern unsigned int grim_def_g_dwLrHiColor __asm__("_g_dwLrHiColor");
extern unsigned int grim_def_g_dwSputtextInitialize __asm__("_g_dwSputtextInitialize");
extern unsigned int grim_def_g_dwSputtextStartup __asm__("_g_dwSputtextStartup");
extern unsigned int grim_def_g_hFont __asm__("_g_hFont");
extern unsigned char grim_def_g_pSputtextHS[4] __asm__("_g_pSputtextHS");
extern void *grim_def_g_pTextFunctionsToRegister[44] __asm__("_g_pTextFunctionsToRegister");
extern char grim_def_s_BlastText_004e8688[] __asm__("_s_BlastText_004e8688");
extern char grim_def_s_ChangeTextObject_004e86a4[] __asm__("_s_ChangeTextObject_004e86a4");
extern char grim_def_s_ExpireText_004e867c[] __asm__("_s_ExpireText_004e867c");
extern char grim_def_s_GetActorTalkColor_004e8708[] __asm__("_s_GetActorTalkColor_004e8708");
extern char grim_def_s_GetColorComponents_004e8650[] __asm__("_s_GetColorComponents_004e8650");
extern char grim_def_s_GetFontDimensions_004e86b8[] __asm__("_s_GetFontDimensions_004e86b8");
extern char grim_def_s_GetTextCharPosition_004e8614[] __asm__("_s_GetTextCharPosition_004e8614");
extern char grim_def_s_GetTextObjectDimensions_004e86cc[] __asm__("_s_GetTextObjectDimensions_004e86cc");
extern char grim_def_s_GetTranslationMode_004e8628[] __asm__("_s_GetTranslationMode_004e8628");
extern char grim_def_s_IsMessageGoing_004e8744[] __asm__("_s_IsMessageGoing_004e8744");
extern char grim_def_s_KillTextObject_004e8694[] __asm__("_s_KillTextObject_004e8694");
extern char grim_def_s_LocalizeString_004e8604[] __asm__("_s_LocalizeString_004e8604");
extern char grim_def_s_MakeColor_004e8664[] __asm__("_s_MakeColor_004e8664");
extern char grim_def_s_MakeTextObject_004e86e4[] __asm__("_s_MakeTextObject_004e86e4");
extern char grim_def_s_PrintLine_004e86f4[] __asm__("_s_PrintLine_004e86f4");
extern char grim_def_s_PurgeText_004e8670[] __asm__("_s_PurgeText_004e8670");
extern char grim_def_s_SayLine_004e8700[] __asm__("_s_SayLine_004e8700");
extern char grim_def_s_SetActorTalkColor_004e871c[] __asm__("_s_SetActorTalkColor_004e871c");
extern char grim_def_s_SetEmergencyFont_004e85f0[] __asm__("_s_SetEmergencyFont_004e85f0");
extern char grim_def_s_SetOffscreenTextPos_004e85dc[] __asm__("_s_SetOffscreenTextPos_004e85dc");
extern char grim_def_s_SetSayLineDefaults_004e8730[] __asm__("_s_SetSayLineDefaults_004e8730");
extern char grim_def_s_SetTranslationMode_004e863c[] __asm__("_s_SetTranslationMode_004e863c");
extern char grim_def_s_background_004e875c[12] __asm__("_s_background_004e875c");
extern char grim_def_s_bgcolor_004e87b0[8] __asm__("_s_bgcolor_004e87b0");
extern char grim_def_s_center_004e878c[8] __asm__("_s_center_004e878c");
extern char grim_def_s_duration_004e8794[12] __asm__("_s_duration_004e8794");
extern char grim_def_s_fgcolor_004e87b8[8] __asm__("_s_fgcolor_004e87b8");
extern char grim_def_s_font_004e87c0[8] __asm__("_s_font_004e87c0");
extern char grim_def_s_fxcolor_004e87a8[8] __asm__("_s_fxcolor_004e87a8");
extern char grim_def_s_height_004e8438[8] __asm__("_s_height_004e8438");
extern char grim_def_s_hicolor_004e87a0[8] __asm__("_s_hicolor_004e87a0");
extern char grim_def_s_ljustify_004e8780[12] __asm__("_s_ljustify_004e8780");
extern char grim_def_s_pan_004e8768[4] __asm__("_s_pan_004e8768");
extern char grim_def_s_rjustify_004e8774[12] __asm__("_s_rjustify_004e8774");
extern char grim_def_s_volume_004e876c[8] __asm__("_s_volume_004e876c");
extern char grim_def_s_width_004e8440[8] __asm__("_s_width_004e8440");
/* 0x004e8438, 8 bytes */ /* loose */ char grim_def_s_height_004e8438[8] __asm__("_s_height_004e8438") = "height";
/* 0x004e8440, 8 bytes */ /* loose */ char grim_def_s_width_004e8440[8] __asm__("_s_width_004e8440") = "width";
/* 0x004e8528, 176 bytes */ GRIM_DATA("004e8528") void *grim_def_g_pTextFunctionsToRegister[44] __asm__("_g_pTextFunctionsToRegister") = {
    (void *)&grim_def_s_IsMessageGoing_004e8744, (void *)f_sputText_IsMessageGoingL, (void *)&grim_def_s_SetSayLineDefaults_004e8730, (void *)f_sputText_SetSayLineDefaultsL,
    (void *)&grim_def_s_SetActorTalkColor_004e871c, (void *)f_sputText_SetActorTalkColorL, (void *)&grim_def_s_GetActorTalkColor_004e8708, (void *)f_sputText_GetActorTalkColorL,
    (void *)&grim_def_s_SayLine_004e8700, (void *)f_sputText_SayLineL, (void *)&grim_def_s_PrintLine_004e86f4, (void *)f_sputText_PrintLineL,
    (void *)&grim_def_s_MakeTextObject_004e86e4, (void *)f_sputText_MakeTextObjectL, (void *)&grim_def_s_GetTextObjectDimensions_004e86cc, (void *)f_sputText_GetTextObjectDimensionsL,
    (void *)&grim_def_s_GetFontDimensions_004e86b8, (void *)f_sputText_GetFontDimensionsL, (void *)&grim_def_s_ChangeTextObject_004e86a4, (void *)f_sputText_ChangeTextObjectL,
    (void *)&grim_def_s_KillTextObject_004e8694, (void *)f_sputText_KillTextObjectL, (void *)&grim_def_s_BlastText_004e8688, (void *)f_sputText_BlastText,
    (void *)&grim_def_s_ExpireText_004e867c, (void *)f_sputText_ExpireTextQueueL, (void *)&grim_def_s_PurgeText_004e8670, (void *)f_sputText_PurgeTextQueueL,
    (void *)&grim_def_s_MakeColor_004e8664, (void *)f_sputText_MakeColorL, (void *)&grim_def_s_GetColorComponents_004e8650, (void *)f_sputText_GetColorComponentsL,
    (void *)&grim_def_s_SetTranslationMode_004e863c, (void *)f_sputText_SetTranslationModeL, (void *)&grim_def_s_GetTranslationMode_004e8628, (void *)f_sputText_GetTranslationModeL,
    (void *)&grim_def_s_GetTextCharPosition_004e8614, (void *)f_sputText_GetTextCharPositionL, (void *)&grim_def_s_LocalizeString_004e8604, (void *)f_sputText_LocalizeStringL,
    (void *)&grim_def_s_SetEmergencyFont_004e85f0, (void *)f_sputText_SetEmergencyFontL, (void *)&grim_def_s_SetOffscreenTextPos_004e85dc, (void *)f_sputText_SetOffscreenTextPosL
};
/* 0x004e85d8, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004e85d8 __asm__("_UINT_004e85d8") = 0x16;
/* 0x004e875c, 12 bytes */ /* loose */ char grim_def_s_background_004e875c[12] __asm__("_s_background_004e875c") = "background";
/* 0x004e8768, 4 bytes */ /* loose */ char grim_def_s_pan_004e8768[4] __asm__("_s_pan_004e8768") = "pan";
/* 0x004e876c, 8 bytes */ /* loose */ char grim_def_s_volume_004e876c[8] __asm__("_s_volume_004e876c") = "volume";
/* 0x004e8774, 12 bytes */ /* loose */ char grim_def_s_rjustify_004e8774[12] __asm__("_s_rjustify_004e8774") = "rjustify";
/* 0x004e8780, 12 bytes */ /* loose */ char grim_def_s_ljustify_004e8780[12] __asm__("_s_ljustify_004e8780") = "ljustify";
/* 0x004e878c, 8 bytes */ /* loose */ char grim_def_s_center_004e878c[8] __asm__("_s_center_004e878c") = "center";
/* 0x004e8794, 12 bytes */ /* loose */ char grim_def_s_duration_004e8794[12] __asm__("_s_duration_004e8794") = "duration";
/* 0x004e87a0, 8 bytes */ /* loose */ char grim_def_s_hicolor_004e87a0[8] __asm__("_s_hicolor_004e87a0") = "hicolor";
/* 0x004e87a8, 8 bytes */ /* loose */ char grim_def_s_fxcolor_004e87a8[8] __asm__("_s_fxcolor_004e87a8") = "fxcolor";
/* 0x004e87b0, 8 bytes */ /* loose */ char grim_def_s_bgcolor_004e87b0[8] __asm__("_s_bgcolor_004e87b0") = "bgcolor";
/* 0x004e87b8, 8 bytes */ /* loose */ char grim_def_s_fgcolor_004e87b8[8] __asm__("_s_fgcolor_004e87b8") = "fgcolor";
/* 0x004e87c0, 8 bytes */ /* loose */ char grim_def_s_font_004e87c0[8] __asm__("_s_font_004e87c0") = "font";
static unsigned char grim_anchor_008ca0b8[0] __attribute__((section(".data$grim_008ca0b8"), aligned(16), used));
static unsigned char grim_pad_008ca0b8[8] __attribute__((section(".data$grim_008ca0b8_"), aligned(4), used));
/* 0x008ca0b8, 32 bytes */ GRIM_DATA("008ca0b8z") SysModuleIface grim_def_g_aTextMS __asm__("_g_aTextMS") = {0};
/* 0x008ca0e8, 4 bytes */ /* loose */ unsigned int grim_def_g_dwLrHiColor __asm__("_g_dwLrHiColor") = 0x0;
static unsigned char grim_anchor_008ca118[0] __attribute__((section(".data$grim_008ca118"), aligned(16), used));
static unsigned char grim_pad_008ca118[8] __attribute__((section(".data$grim_008ca118_"), aligned(4), used));
/* 0x008ca118, 32 bytes */ GRIM_DATA("008ca118z") SysModuleIface grim_def_g_aGraphMS __asm__("_g_aGraphMS") = {0};
/* 0x008ca138, 4 bytes */ /* loose */ unsigned int grim_def_g_dwSputtextInitialize __asm__("_g_dwSputtextInitialize") = 0x0;
/* 0x008ca13c, 4 bytes */ /* loose */ unsigned int grim_def_g_dwSputtextStartup __asm__("_g_dwSputtextStartup") = 0x0;
/* 0x008ca144, 4 bytes */ /* loose */ unsigned char grim_def_g_pSputtextHS[4] __asm__("_g_pSputtextHS") = {0};
static unsigned char grim_anchor_008ca148[0] __attribute__((section(".data$grim_008ca148"), aligned(16), used));
static unsigned char grim_pad_008ca148[8] __attribute__((section(".data$grim_008ca148_"), aligned(4), used));
/* 0x008ca148, 4 bytes */ GRIM_DATA("008ca148z") unsigned int grim_def_g_hFont __asm__("_g_hFont") = 0x0;
