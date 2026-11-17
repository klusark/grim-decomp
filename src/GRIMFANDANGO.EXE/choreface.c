/* GRIMFANDANGO.EXE :: choreface.c
 * functions 0x00402120 .. 0x00402290 (3 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00402120  ChoreFace_Toggle ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Loads/unloads choreface.dll (the chore editor UI) and shows/hides it */

int __cdecl ChoreFace_Toggle(int show)

{
  int iVar1;
  void *pvVar2;
  
  if (show == 0) {
    if (UINT_004f5a6c == 0) {
      return 1;
    }
    iVar1 = (*(code *)UINT_004f5a74)();
    if (iVar1 != 0) {
      (*(code *)UINT_004f4d9c)();
      (*(code *)UINT_004f4d94)();
      UINT_004f5a70 = 0;
      UINT_004f5a74 = 0;
      UINT_004f5a78 = 0;
      _DAT_004f5a7c = (code *)0x0;
      FreeLibrary(UINT_004f4530);
      UINT_004f4530 = 0;
      UINT_004f5a6c = 0;
      return 1;
    }
    return 0;
  }
  if (UINT_004f5a6c == 0) {
    UINT_004f4530 = LoadLibraryA(((unsigned)(uintptr_t)&DAT_004dd728));
    if (UINT_004f4530 == 0) {
      return 0;
    }
    UINT_004f5a70 = GetProcAddress(UINT_004f4530,((unsigned)(uintptr_t)&s__ShowChoreFace_004dd718));
    UINT_004f5a74 = GetProcAddress(UINT_004f4530,((unsigned)(uintptr_t)&s__HideChoreFace_004dd708));
    UINT_004f5a78 = GetProcAddress(UINT_004f4530,((unsigned)(uintptr_t)&s__RegisterCommandCallback_004dd6ec));
    _DAT_004f5a7c = (code *)GetProcAddress(UINT_004f4530,((unsigned)(uintptr_t)&s__choreface_Initialize_004dd6d4));
    if ((((UINT_004f5a70 != 0) && (UINT_004f5a74 != 0)) && (UINT_004f5a78 != 0)) &&
       (_DAT_004f5a7c != (code *)0x0)) {
      iVar1 = (*_DAT_004f5a7c)(PTR_g_aHs_004dd040,&DAT_004f4d90);
      if (iVar1 == 0) {
        iVar1 = (*(code *)UINT_004f4d98)();
        if (iVar1 == 0) {
          _DAT_004f5a80 = (*(code *)UINT_004f5a78)(ChoreFace_OnCommand);
          UINT_004f5a6c = 1;
          goto LAB_004021fb;
        }
      }
    }
    FreeLibrary(UINT_004f4530);
    UINT_004f4530 = 0;
    return 0;
  }
LAB_004021fb:
  pvVar2 = Win_GetMainHwnd();
  (*(code *)UINT_004f5a70)(pvVar2);
  return 1;
}

/* ---- 0x00402200  ChoreFace_CallSavedHook ---- */
/* Calls the function pointer ChoreFace_Toggle saves (UINT_004f5a70) and returns 1. Nothing
   references it (dead code); was FUN_00402200. */

uint __cdecl ChoreFace_CallSavedHook(void)

{
  (*(code *)UINT_004f5a70)();
  return 1;
}

/* ---- 0x00402290  ChoreFace_OnCommand ---- */
/* Callback handed to choreface.dll (UINT_004f5a78): 1 = frame update, 2/3 = pause/unpause, 4/5 =
   pop/push the selected actor costume (forces windowed mode while editing), >=7 sets
   g_fixedFrameMs. */

void __cdecl ChoreFace_OnCommand(uint flags,int command)

{
  switch(command) {
  case 0:
    goto switchD_00402299_caseD_0;
  case 1:
    Main_Service();
    return;
  case 2:
    grimlib_SetPause(1);
    return;
  case 3:
    grimlib_SetPause(0);
    return;
  case 4:
    if (g_bWindowedMode != UINT_004dd388) {
      g_bWindowedMode = UINT_004dd388;
      Display_InitFromConfig();
    }
    grimlib_RestoreSelectedActorCostume();
    return;
  case 5:
    UINT_004dd388 = g_bWindowedMode;
    if (g_bWindowedMode != 0) {
      g_bWindowedMode = 0;
      Display_InitFromConfig();
    }
switchD_00402299_caseD_0:
    grimlib_OverrideSelectedActorCostume(flags);
    return;
  case 6:
    return;
  default:
    g_fixedFrameMs = command + -7;
    return;
  }
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_004dd728[16] __asm__("_DAT_004dd728");
extern unsigned char grim_def_DAT_004f4d90[4] __asm__("_DAT_004f4d90");
extern unsigned char grim_def_DAT_004f5a7c[4] __asm__("_DAT_004f5a7c");
extern unsigned char grim_def_DAT_004f5a80[4] __asm__("_DAT_004f5a80");
extern void *grim_def_PTR_g_aHs_004dd040[2] __asm__("_PTR_g_aHs_004dd040");
extern unsigned int grim_def_UINT_004dd388 __asm__("_UINT_004dd388");
extern unsigned char grim_def_UINT_004f4530[8] __asm__("_UINT_004f4530");
extern unsigned int grim_def_UINT_004f4d94 __asm__("_UINT_004f4d94");
extern unsigned int grim_def_UINT_004f4d98 __asm__("_UINT_004f4d98");
extern unsigned char grim_def_UINT_004f4d9c[20] __asm__("_UINT_004f4d9c");
extern unsigned int grim_def_UINT_004f5a6c __asm__("_UINT_004f5a6c");
extern unsigned int grim_def_UINT_004f5a70 __asm__("_UINT_004f5a70");
extern unsigned int grim_def_UINT_004f5a74 __asm__("_UINT_004f5a74");
extern unsigned int grim_def_UINT_004f5a78 __asm__("_UINT_004f5a78");
extern char grim_def_g_aHs[] __asm__("_g_aHs");
extern char grim_def_s__HideChoreFace_004dd708[16] __asm__("_s__HideChoreFace_004dd708");
extern char grim_def_s__RegisterCommandCallback_004dd6ec[28] __asm__("_s__RegisterCommandCallback_004dd6ec");
extern char grim_def_s__ShowChoreFace_004dd718[16] __asm__("_s__ShowChoreFace_004dd718");
extern char grim_def_s__choreface_Initialize_004dd6d4[24] __asm__("_s__choreface_Initialize_004dd6d4");
/* 0x004dd040, 8 bytes */ GRIM_DATA("004dd040") void *grim_def_PTR_g_aHs_004dd040[2] __asm__("_PTR_g_aHs_004dd040") = {
    (void *)&grim_def_g_aHs, 0
};
/* 0x004dd388, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004dd388 __asm__("_UINT_004dd388") = 0x1;
/* 0x004dd6d4, 24 bytes */ /* loose */ char grim_def_s__choreface_Initialize_004dd6d4[24] __asm__("_s__choreface_Initialize_004dd6d4") = "_choreface_Initialize";
/* 0x004dd6ec, 28 bytes */ /* loose */ char grim_def_s__RegisterCommandCallback_004dd6ec[28] __asm__("_s__RegisterCommandCallback_004dd6ec") = "_RegisterCommandCallback";
/* 0x004dd708, 16 bytes */ /* loose */ char grim_def_s__HideChoreFace_004dd708[16] __asm__("_s__HideChoreFace_004dd708") = "_HideChoreFace";
/* 0x004dd718, 16 bytes */ /* loose */ char grim_def_s__ShowChoreFace_004dd718[16] __asm__("_s__ShowChoreFace_004dd718") = "_ShowChoreFace";
/* 0x004dd728, 16 bytes */ /* loose */ unsigned char grim_def_DAT_004dd728[16] __asm__("_DAT_004dd728") = { 0x63, 0x68, 0x6f, 0x72, 0x65, 0x66, 0x61, 0x63, 0x65, 0x2e, 0x64, 0x6c, 0x6c };
/* 0x004f4530, 8 bytes */ GRIM_DATA("004f4530") unsigned char grim_def_UINT_004f4530[8] __asm__("_UINT_004f4530") = {0};
/* 0x004f4d90, 4 bytes */ GRIM_DATA("004f4d90") unsigned char grim_def_DAT_004f4d90[4] __asm__("_DAT_004f4d90") = {0};
/* 0x004f4d94, 4 bytes */ GRIM_DATA("004f4d94") unsigned int grim_def_UINT_004f4d94 __asm__("_UINT_004f4d94") = 0x0;
/* 0x004f4d98, 4 bytes */ GRIM_DATA("004f4d98") unsigned int grim_def_UINT_004f4d98 __asm__("_UINT_004f4d98") = 0x0;
/* 0x004f4d9c, 20 bytes */ GRIM_DATA("004f4d9c") unsigned char grim_def_UINT_004f4d9c[20] __asm__("_UINT_004f4d9c") = {0};
/* 0x004f5a6c, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a6c __asm__("_UINT_004f5a6c") = 0x0;
/* 0x004f5a70, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a70 __asm__("_UINT_004f5a70") = 0x0;
/* 0x004f5a74, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a74 __asm__("_UINT_004f5a74") = 0x0;
/* 0x004f5a78, 4 bytes */ /* loose */ unsigned int grim_def_UINT_004f5a78 __asm__("_UINT_004f5a78") = 0x0;
/* 0x004f5a7c, 4 bytes */ /* loose */ unsigned char grim_def_DAT_004f5a7c[4] __asm__("_DAT_004f5a7c") = {0};
/* 0x004f5a80, 4 bytes */ /* loose */ unsigned char grim_def_DAT_004f5a80[4] __asm__("_DAT_004f5a80") = {0};
