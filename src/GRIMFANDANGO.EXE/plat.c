/* GRIMFANDANGO.EXE :: plat.c
 * functions 0x00477f00 .. 0x00488820 (15 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00477f00  Plat_ReturnTrue ---- */
/* Always returns 1; placeholder platform check called from several init paths */

uint __cdecl Plat_ReturnTrue(void)

{
  return 1;
}

/* ---- 0x00478150  stdPlatform_GetPhysicalRam ---- */
/* Lua GetPhysicalBytes Original name stdPlatform_GetPhysicalRam (the remaster's GrimFandango
   (Linux): the only unmatched callee of Lua_GetPhysicalBytes; 1 matched neighbours agree, 0
   disagree); was Plat_GetPhysicalMemory. */

uint __cdecl stdPlatform_GetPhysicalRam(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_20 (*(uint *)(_frame + (0x30 - 0x20)))
  #define local_18 (*(uint *)(_frame + (0x30 - 0x18)))
  
  local_20 = 0x20;
  GlobalMemoryStatus((int)&local_20);
  return local_18;
}
#undef local_18
#undef local_20


/* ---- 0x00487650  grimPlat_QueryDialog ---- */
/* Win95/grimplat.cpp: MessageBoxA on the game window; returns the IDxxx button code (2 = cancel, 7
   = no) Original name grimPlat_QueryDialog (the remaster's GrimFandango (Linux): the only unmatched
   callee of Lua_QueryDialog; 3 matched neighbours agree, 0 disagree); was Plat_MessageBox. */

int __cdecl grimPlat_QueryDialog(char *text,char *caption,uint flags)

{
  void *a1;
  int iVar1;
  
  UINT_004e814c = 0;
  Display_SuspendForDialog();
  a1 = Win_GetMainHwnd();
  iVar1 = MessageBoxA((int)a1,(int)caption,(int)text,flags);
  Display_ResumeAfterDialog();
  UINT_004e814c = 1;
  return iVar1;
}

/* ---- 0x00487690  grimPlat_SetDefaultOpenPath ---- */
/* Original name grimPlat_SetDefaultOpenPath (the remaster's GrimFandango (Linux): aligned call in
   BitmapRequester, ColormapRequester, MaterialRequester); was Plat_SetDialogDirectory. */

void __cdecl grimPlat_SetDefaultOpenPath(uint param_1)

{
  strncpy(g_szDialogOpenDir,param_1,0x103);
  g_szDialogOpenDir[0x103] = '\0';
  return;
}

/* ---- 0x004876b0  grimPlat_GetDefaultOpenPath ---- */
/* Original name grimPlat_GetDefaultOpenPath (the remaster's GrimFandango (Linux): aligned call in
   BitmapRequester, ColormapRequester, MaterialRequester); was Plat_GetDialogFileName. */

char * __cdecl grimPlat_GetDefaultOpenPath(void)

{
  return g_szDialogOpenDir;
}

/* ---- 0x004876c0  grimPlat_OpenFileRequest ---- */
/* Original name grimPlat_OpenFileRequest (the remaster's GrimFandango (Linux): aligned call in
   BitmapRequester, ColormapRequester, MaterialRequester); was Plat_OpenFileDialog. */

int __cdecl grimPlat_OpenFileRequest(char *title,char *filter)

{
  unsigned char _frame[0x160] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint *puVar2;
  #define local_150 (*(uint *)(_frame + (0x160 - 0x150)))
  #define local_14c (*(uint *)(_frame + (0x160 - 0x14c)))
  #define local_144 (*(uint *)(_frame + (0x160 - 0x144)))
  #define local_138 (*(uint *)(_frame + (0x160 - 0x138)))
  #define local_134 (*(uint *)(_frame + (0x160 - 0x134)))
  #define local_130 (*(uint *)(_frame + (0x160 - 0x130)))
  #define local_124 (*(uint *)(_frame + (0x160 - 0x124)))
  #define local_120 (*(uint *)(_frame + (0x160 - 0x120)))
  #define local_11c (*(uint *)(_frame + (0x160 - 0x11c)))
  #define local_118 (*(uint *)(_frame + (0x160 - 0x118)))
  #define local_104 (*(undefined1 (*)[260])(_frame + (0x160 - 0x104)))
  
  puVar2 = &local_150;
  for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  UINT_004e814c = 0;
  local_104[0] = 0;
  local_150 = 0x4c;
  local_14c = (uint)Win_GetMainHwnd();
  local_144 = (uint)filter;
  local_134 = (uint)local_104;
  local_124 = -(uint)(g_szDialogOpenDir[0] != '\0') & 0x8c9858;
  local_138 = 1;
  local_130 = 0x104;
  local_120 = (uint)title;
  local_11c = 0x100c;
  iVar1 = GetOpenFileNameA((int)&local_150);
  if (iVar1 != 0) {
    strncpy(g_szDialogOpenDir,local_134,0x103);
    g_szDialogOpenDir[0x103] = '\0';
    if (((ushort)local_118 != 0) && ((ushort)local_118 < 0x104)) {
      *(undefined1 *)((int)&UINT_008c9854 + (local_118 & 0xffff) + 3) = 0;
    }
    strncpy(g_szGrimlib_aFilename,local_134,0x7f);
    g_szGrimlib_aFilename[0x7f] = '\0';
    UINT_004e814c = 1;
    return 1;
  }
  UINT_004e814c = 1;
  return 0;
}
#undef local_104
#undef local_118
#undef local_11c
#undef local_120
#undef local_124
#undef local_130
#undef local_134
#undef local_138
#undef local_144
#undef local_14c
#undef local_150


/* ---- 0x004877d0  grimPlat_SaveFileRequest ---- */
/* Original name grimPlat_SaveFileRequest (the remaster's GrimFandango (Linux): the save-file
   request of sputCostume_SaveHook ("Name chore list file...", "Script files (*.lua, *.def)"); the
   remaster's is a stub); was Plat_SaveFileDialog. */

int __cdecl grimPlat_SaveFileRequest(char *title,char *filter)

{
  unsigned char _frame[0x160] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint *puVar2;
  #define local_150 (*(uint *)(_frame + (0x160 - 0x150)))
  #define local_14c (*(uint *)(_frame + (0x160 - 0x14c)))
  #define local_144 (*(uint *)(_frame + (0x160 - 0x144)))
  #define local_138 (*(uint *)(_frame + (0x160 - 0x138)))
  #define local_134 (*(uint *)(_frame + (0x160 - 0x134)))
  #define local_130 (*(uint *)(_frame + (0x160 - 0x130)))
  #define local_124 (*(uint *)(_frame + (0x160 - 0x124)))
  #define local_120 (*(uint *)(_frame + (0x160 - 0x120)))
  #define local_11c (*(uint *)(_frame + (0x160 - 0x11c)))
  #define local_118 (*(uint *)(_frame + (0x160 - 0x118)))
  #define local_104 (*(undefined1 (*)[260])(_frame + (0x160 - 0x104)))
  
  puVar2 = &local_150;
  for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  local_104[0] = 0;
  local_150 = 0x4c;
  local_14c = (uint)Win_GetMainHwnd();
  local_144 = (uint)filter;
  local_134 = (uint)local_104;
  local_124 = -(uint)(g_szDialogSaveDir[0] != '\0') & 0x8c9960;
  local_138 = 1;
  local_130 = 0x104;
  local_120 = (uint)title;
  local_11c = 0x880e;
  iVar1 = GetSaveFileNameA((int)&local_150);
  if (iVar1 != 0) {
    strncpy(g_szDialogSaveDir,local_134,0x103);
    g_szDialogSaveDir[0x103] = '\0';
    if (((ushort)local_118 != 0) && ((ushort)local_118 < 0x104)) {
      (&DAT_008c995f)[local_118 & 0xffff] = 0;
    }
    strncpy(g_szGrimlib_aFilename,local_134,0x7f);
    g_szGrimlib_aFilename[0x7f] = '\0';
    return 1;
  }
  return 0;
}
#undef local_104
#undef local_118
#undef local_11c
#undef local_120
#undef local_124
#undef local_130
#undef local_134
#undef local_138
#undef local_144
#undef local_14c
#undef local_150


/* ---- 0x004878c0  grimPlat_SpinDialog ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Editor prompt dialog with labelled numeric fields Original name grimPlat_SpinDialog (the
   remaster's GrimFandango (Linux): aligned call in KeyframeAdjuster, SoundAdjuster, ThingAdjuster);
   was Plat_PromptDialog. */

int __cdecl grimPlat_SpinDialog(int param_1,int param_2,uint *param_3,uint param_4)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  short sVar2;
  undefined4 *puVar3;
  uint *puVar4;
  uint *puVar5;
  uint *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  void *a3;
  int iVar9;
  uint uVar10;
  uint uVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  int iVar14;
  undefined4 *puVar15;
  ushort uVar16;
  code *a4;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(char (*)[32])(_frame + (0x40 - 0x20)))
  
  if (((param_2 != 0) && (param_3 != (uint *)0x0)) && (0 < (int)param_4)) {
    UINT_008c9850 = (uint)param_3;
    UINT_004e814c = 0;
    _DAT_008c9848 = param_1;
    _DAT_008c984c = param_2;
    UINT_008c9854 = param_4;
    uVar11 = (param_4 + 1) * 0xc;
    puVar3 = (undefined4 *)malloc(uVar11);
    puVar4 = (uint *)malloc(uVar11);
    puVar5 = Dlg_MakeDialogTemplate
                       ((uint *)0x90c80884,(short)(param_4 + 1) * 3 - 1,0,0,0x8a,
                        (short)param_4 * 0x14 + 0x19,param_1,((unsigned)(uintptr_t)&s_MS_Sans_Serif_004e8184),8,puVar4);
    *puVar3 = puVar5;
    uVar11 = *puVar4;
    iVar14 = 0;
    param_1 = 1;
    if (0 < (int)param_4) {
      puVar5 = puVar4 + 1;
      puVar7 = puVar3 + 1;
      iVar9 = param_2 - (int)param_3;
      do {
        sVar2 = (short)iVar14;
        uVar16 = sVar2 * 0x14 + 5;
        puVar6 = Dlg_MakeItemTemplate
                           (0x50000082,5,uVar16,0x32,0xe,sVar2 + 0x41e,
                            *(int *)(iVar9 + (int)param_3),((unsigned)(uintptr_t)&s_STATIC_004e817c),puVar5);
        *puVar7 = puVar6;
        uVar10 = *puVar5;
        sprintf(local_20,&DAT_004ddc18,*param_3);
        puVar6 = Dlg_MakeItemTemplate
                           (0x50810003,0x41,uVar16,0x32,0xe,sVar2 + 0x3ec,(int)local_20,((unsigned)(uintptr_t)&DAT_004e8174),
                            puVar5 + 1);
        puVar7[1] = puVar6;
        uVar1 = puVar5[1];
        puVar6 = Dlg_MakeItemTemplate
                           (0x500000b6,0x55,uVar16,0x32,0xe,sVar2 + 0x450,0,((unsigned)(uintptr_t)&s_msctls_updown32_004e8164),puVar5 + 2);
        puVar7[2] = puVar6;
        uVar11 = uVar11 + uVar10 + uVar1 + puVar5[2];
        param_1 = param_1 + 3;
        puVar7 = puVar7 + 3;
        puVar5 = puVar5 + 3;
        iVar14 = iVar14 + 1;
        param_3 = param_3 + 1;
      } while (iVar14 < (int)param_4);
    }
    uVar16 = (short)iVar14 * 0x14 + 5;
    puVar5 = Dlg_MakeItemTemplate(0x50010001,5,uVar16,0x32,0xe,1,((unsigned)(uintptr_t)&DAT_004e8158),((unsigned)(uintptr_t)&s_BUTTON_004e815c),puVar4 + param_1)
    ;
    puVar3[param_1] = puVar5;
    uVar10 = puVar4[param_1];
    iVar14 = param_1 + 1;
    puVar5 = Dlg_MakeItemTemplate
                       (0x50010000,0x41,uVar16,0x32,0xe,2,((unsigned)(uintptr_t)&s_Cancel_004e8150),((unsigned)(uintptr_t)&s_BUTTON_004e815c),puVar4 + iVar14);
    puVar3[iVar14] = puVar5;
    param_1 = param_1 + 2;
    puVar7 = (undefined4 *)malloc(uVar11 + uVar10 + puVar4[iVar14]);
    if (0 < param_1) {
      puVar8 = puVar7;
      puVar12 = puVar3;
      do {
        uVar11 = *(uint *)(((int)puVar4 - (int)puVar3) + (int)puVar12);
        puVar13 = (undefined4 *)*puVar12;
        puVar15 = puVar8;
        for (uVar10 = uVar11 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *puVar15 = *puVar13;
          puVar13 = puVar13 + 1;
          puVar15 = puVar15 + 1;
        }
        for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
          *(undefined1 *)puVar15 = *(undefined1 *)puVar13;
          puVar13 = (undefined4 *)((int)puVar13 + 1);
          puVar15 = (undefined4 *)((int)puVar15 + 1);
        }
        puVar8 = (undefined4 *)((int)puVar8 + *(int *)(((int)puVar4 - (int)puVar3) + (int)puVar12));
        free(*puVar12);
        puVar12 = puVar12 + 1;
        param_1 = param_1 + -1;
      } while (param_1 != 0);
    }
    iVar14 = 0;
    a4 = Plat_PromptDialogProc;
    a3 = Win_GetMainHwnd();
    puVar8 = puVar7;
    uVar11 = Win_GetInstance();
    iVar14 = DialogBoxIndirectParamA(uVar11,(int)puVar8,(int)a3,(int)a4,iVar14);
    free(puVar7);
    free(puVar3);
    free(puVar4);
    UINT_004e814c = 1;
    return (uint)(iVar14 == 1);
  }
  return 0;
}
#undef local_20
#undef local_24
#undef local_28
#undef local_2c


/* ---- 0x00487c10  grimPlat_TreeDialog ---- */
/* Editor 'Tree Select' dialog; returns the chosen index or -1 Original name grimPlat_TreeDialog
   (the remaster's GrimFandango (Linux): aligned call in MeshRequester); was Plat_TreeSelectDialog.
    */

int __cdecl grimPlat_TreeDialog(char *title,char **items,int count,int *recursive)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  void *a3;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  code *a4;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  iVar4 = 0;
  if ((items != (char **)0x0) && (0 < count)) {
    UINT_004e8140 = count;
    UINT_004e814c = 0;
    UINT_004e8138 = (uint)title;
    UINT_004e813c = (uint)items;
    UINT_004e8144 = 0xffffffff;
    UINT_004e8148 = 0;
    local_14 = (uint)Dlg_MakeDialogTemplate
                               ((uint *)0x90c80884,4,0,0,0x12f,0x9a,((unsigned)(uintptr_t)&s_Tree_Select_004e81b0),((unsigned)(uintptr_t)&s_MS_Sans_Serif_004e8184),8,&local_28);
    local_10 = (uint)Dlg_MakeItemTemplate(0x50b10037,5,5,0xf0,0x91,0x3ea,0,((unsigned)(uintptr_t)&s_SysTreeView32_004e81a0),&local_24);
    local_c = (uint)Dlg_MakeItemTemplate(0x50010001,0xfa,5,0x32,0xe,1,((unsigned)(uintptr_t)&DAT_004e8158),((unsigned)(uintptr_t)&s_BUTTON_004e815c),&local_20);
    local_8 = (uint)Dlg_MakeItemTemplate
                              (0x50010000,0xfa,0x19,0x32,0xe,2,((unsigned)(uintptr_t)&s_Cancel_004e8150),((unsigned)(uintptr_t)&s_BUTTON_004e815c),&local_1c);
    uVar5 = local_28 + local_24 + local_20 + local_1c;
    items = (char **)0x4;
    if (*recursive != 0) {
      local_4 = (uint)Dlg_MakeItemTemplate
                                (0x50010003,0xfa,0x2d,0x32,0xe,0x3eb,((unsigned)(uintptr_t)&s_Recursive_004e8194),((unsigned)(uintptr_t)&s_BUTTON_004e815c),&local_18);
      uVar5 = uVar5 + local_18;
      items = (char **)0x5;
    }
    puVar1 = (undefined4 *)malloc(uVar5);
    puVar3 = puVar1;
    if (items != (char **)0x0) {
      do {
        uVar5 = (&local_28)[iVar4];
        puVar6 = (undefined4 *)(&local_14)[iVar4];
        puVar7 = puVar3;
        for (uVar2 = uVar5 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
          *puVar7 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar7 = puVar7 + 1;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
          puVar6 = (undefined4 *)((int)puVar6 + 1);
          puVar7 = (undefined4 *)((int)puVar7 + 1);
        }
        puVar3 = (undefined4 *)((int)puVar3 + (&local_28)[iVar4]);
        free((&local_14)[iVar4]);
        iVar4 = iVar4 + 1;
      } while (iVar4 < (int)items);
    }
    iVar4 = 0;
    a4 = Plat_TreeSelectDialogProc;
    a3 = Win_GetMainHwnd();
    puVar3 = puVar1;
    uVar5 = Win_GetInstance();
    iVar4 = DialogBoxIndirectParamA(uVar5,(int)puVar3,(int)a3,(int)a4,iVar4);
    free(puVar1);
    UINT_004e814c = 1;
    if (iVar4 == 1) {
      *recursive = UINT_004e8148;
      return UINT_004e8144;
    }
    *recursive = 0;
  }
  return -1;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00487e30  grimPlat_InputDialog ---- */
/* Lua InputDialog: modal text entry dialog Original name grimPlat_InputDialog (the remaster's
   GrimFandango (Linux): the only unmatched callee of Lua_InputDialog; 3 matched neighbours agree, 0
   disagree); was Plat_InputDialog. */

int __cdecl grimPlat_InputDialog(char *title,char *prompt,char *buf,int bufSize,char *defaultText)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  undefined4 *puVar2;
  void *a3;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  code *a4;
  #define local_28 (*(uint *)(_frame + (0x40 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x40 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x40 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x40 - 0x4)))
  
  iVar5 = 0;
  if ((buf != (char *)0x0) && (1 < bufSize)) {
    UINT_008c9838 = (uint)buf;
    UINT_008c9830 = (uint)title;
    UINT_008c983c = bufSize;
    UINT_004e814c = 0;
    UINT_008c9834 = (uint)prompt;
    UINT_008c9840 = (uint)defaultText;
    local_14 = (uint)Dlg_MakeDialogTemplate
                               ((uint *)0x90c80884,4,0,0,0x12f,0x36,((unsigned)(uintptr_t)&s_Input_004e81bc),((unsigned)(uintptr_t)&s_MS_Sans_Serif_004e8184),8,&local_28);
    local_10 = (uint)Dlg_MakeItemTemplate(0x5000008b,5,7,0xf0,0xe,0x3e9,0,((unsigned)(uintptr_t)&s_STATIC_004e817c),&local_24);
    local_c = (uint)Dlg_MakeItemTemplate(0x50810080,5,0x19,0xf0,0xe,1000,0,((unsigned)(uintptr_t)&DAT_004e8174),&local_20);
    local_8 = (uint)Dlg_MakeItemTemplate(0x50010001,0xfa,5,0x32,0xe,1,((unsigned)(uintptr_t)&DAT_004e8158),((unsigned)(uintptr_t)&s_BUTTON_004e815c),&local_1c);
    local_4 = (uint)Dlg_MakeItemTemplate
                              (0x50010000,0xfa,0x19,0x32,0xe,2,((unsigned)(uintptr_t)&s_Cancel_004e8150),((unsigned)(uintptr_t)&s_BUTTON_004e815c),&local_18);
    puVar2 = (undefined4 *)malloc(local_18 + local_28 + local_24 + local_20 + local_1c);
    puVar6 = puVar2;
    do {
      uVar4 = *(uint *)((int)&local_28 + iVar5);
      puVar1 = *(undefined4 **)((int)&local_14 + iVar5);
      puVar7 = puVar1;
      puVar8 = puVar6;
      for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      puVar6 = (undefined4 *)((int)puVar6 + *(int *)((int)&local_28 + iVar5));
      free(puVar1);
      iVar5 = iVar5 + 4;
    } while (iVar5 < 0x14);
    Display_SuspendForDialog();
    iVar5 = 0;
    a4 = Plat_InputDialogProc;
    a3 = Win_GetMainHwnd();
    puVar6 = puVar2;
    uVar4 = Win_GetInstance();
    iVar5 = DialogBoxIndirectParamA(uVar4,(int)puVar6,(int)a3,(int)a4,iVar5);
    Display_ResumeAfterDialog();
    free(puVar2);
    UINT_004e814c = 1;
    return (uint)(iVar5 == 1);
  }
  return 0;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x00488370  Plat_PromptDialogProc ---- */
/* Dialog procedure of grimPlat_SpinDialog: fills integer edit fields on WM_INITDIALOG, reads them
   back on OK. */

undefined * __stdcall Plat_PromptDialogProc(int a1,int a2,int a3,int a4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (a2 == 0x110) {
    if (0 < (int)UINT_008c9854) {
      iVar2 = 0;
      iVar3 = 0x450;
      do {
        SetDlgItemInt(a1,iVar3 + -100,*(int *)(UINT_008c9850 + iVar2),1);
        SendDlgItemMessageA(a1,iVar3,0x465,0,0x7f);
        iVar2 = iVar2 + 4;
        iVar1 = iVar3 + -0x44f;
        iVar3 = iVar3 + 1;
      } while (iVar1 < (int)UINT_008c9854);
    }
  }
  else if (a2 == 0x111) {
    if ((a3 & 0xffffU) == 1) {
      iVar3 = 0;
      if (0 < (int)UINT_008c9854) {
        do {
          iVar2 = GetDlgItemInt(a1,iVar3 + 0x3ec,0,1);
          iVar3 = iVar3 + 1;
          *(int *)((UINT_008c9850 - 4) + iVar3 * 4) = iVar2;
        } while (iVar3 < (int)UINT_008c9854);
      }
      EndDialog(a1,1);
      return (undefined *)0x1;
    }
    if ((a3 & 0xffffU) == 2) {
      EndDialog(a1,2);
      return (undefined *)0x1;
    }
  }
  return (undefined *)0x0;
}

/* ---- 0x00488460  Plat_TreeSelectDialogProc ---- */
/* Dialog procedure of grimPlat_TreeDialog: fills the tree control on WM_INITDIALOG; on OK warns
   when nothing is picked. */

undefined * __stdcall Plat_TreeSelectDialogProc(int a1,int a2,int a3,int a4)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  int iVar2;
  int a1_00;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  #define local_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define local_54 (*(uint *)(_frame + (0x70 - 0x54)))
  #define local_48 (*(uint *)(_frame + (0x70 - 0x48)))
  #define local_44 (*(uint *)(_frame + (0x70 - 0x44)))
  #define local_30 (*(uint *)(_frame + (0x70 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x70 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x70 - 0x28)))
  #define local_18 (*(uint *)(_frame + (0x70 - 0x18)))
  
  if (a2 == 0x110) {
    uVar5 = 0;
    UINT_008c9828 = 0;
    puVar6 = (undefined4 *)UINT_004e813c;
    uVar8 = UINT_004e8140;
    if (0 < (int)UINT_004e8140) {
      do {
        uVar4 = 0xffffffff;
        pcVar9 = (char *)*puVar6;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar9 + 1;
        } while (cVar1 != '\0');
        if (uVar5 <= ~uVar4) {
          uVar5 = 0xffffffff;
          pcVar9 = (char *)*puVar6;
          do {
            if (uVar5 == 0) break;
            uVar5 = uVar5 - 1;
            cVar1 = *pcVar9;
            pcVar9 = pcVar9 + 1;
          } while (cVar1 != '\0');
          uVar5 = ~uVar5;
          UINT_008c9828 = uVar5;
        }
        uVar8 = uVar8 - 1;
        puVar6 = puVar6 + 1;
      } while (uVar8 != 0);
    }
    UINT_008c982c = (uint)malloc(uVar5);
    if (UINT_004e8138 != 0) {
      SendMessageA(a1,0xc,0,UINT_004e8138);
    }
    a1_00 = GetDlgItem(a1,0x3ea);
    iVar7 = 0;
    local_30 = 0xffff0000;
    local_2c = 0xffff0002;
    iVar2 = 0;
    if (0 < (int)UINT_004e8140) {
      do {
        iVar3 = strpbrk_or_strspn(*(undefined4 *)(UINT_004e813c + iVar7 * 4),&DAT_004e81c4);
        if (iVar2 < iVar3) {
          local_30 = a1;
        }
        if (iVar3 < iVar2) {
          iVar2 = iVar2 - iVar3;
          do {
            local_30 = SendMessageA(a1_00,0x110a,3,local_30);
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
        }
        local_18 = *(int *)(UINT_004e813c + iVar7 * 4) + iVar3;
        local_28 = 1;
        a1 = SendMessageA(a1_00,0x1100,0,(int)&local_30);
        iVar7 = iVar7 + 1;
        iVar2 = iVar3;
      } while (iVar7 < (int)UINT_004e8140);
    }
    SetFocus(a1_00);
  }
  else if (a2 == 0x111) {
    if ((a3 & 0xffffU) == 1) {
      iVar2 = GetDlgItem(a1,0x3ea);
      local_54 = SendMessageA(iVar2,0x110a,9,0);
      if (local_54 == 0) {
        grimPlat_QueryDialog(s_Not_so_fast__004e81c8,s_No_item_was_picked__004e81d8,0);
        return (undefined *)0x1;
      }
      local_48 = UINT_008c982c;
      local_44 = UINT_008c9828;
      local_58 = 0x11;
      SendMessageA(iVar2,0x110c,0,(int)&local_58);
      uVar8 = 0;
      if (0 < (int)UINT_004e8140) {
        do {
          iVar2 = String_ContainsSubstring(*(undefined4 *)(UINT_004e813c + uVar8 * 4),UINT_008c982c)
          ;
          if (iVar2 != 0) break;
          uVar8 = uVar8 + 1;
        } while ((int)uVar8 < (int)UINT_004e8140);
      }
      UINT_004e8144 = uVar8;
      iVar2 = GetDlgItem(a1,0x3eb);
      if (iVar2 != 0) {
        iVar2 = SendMessageA(iVar2,0xf0,0,0);
        UINT_004e8148 = (uint)(iVar2 == 1);
      }
      free(UINT_008c982c);
      EndDialog(a1,1);
      return (undefined *)0x1;
    }
    if ((a3 & 0xffffU) == 2) {
      free(UINT_008c982c);
      EndDialog(a1,2);
      return (undefined *)0x1;
    }
  }
  return (undefined *)0x0;
}
#undef local_18
#undef local_28
#undef local_2c
#undef local_30
#undef local_44
#undef local_48
#undef local_54
#undef local_58


/* ---- 0x004886f0  Plat_InputDialogProc ---- */
/* Dialog procedure of grimPlat_InputDialog: title/prompt/default text on WM_INITDIALOG, copies the
   edit text into the caller buffer on OK. */

undefined * __stdcall Plat_InputDialogProc(int a1,int a2,int a3,int a4)

{
  undefined1 *puVar1;
  int a1_00;
  
  if (a2 == 0x110) {
    if (UINT_008c9830 != 0) {
      SendMessageA(a1,0xc,0,UINT_008c9830);
    }
    puVar1 = (undefined1 *)UINT_008c9834;
    if (UINT_008c9834 == 0) {
      puVar1 = &DAT_004f5a98;
    }
    SetDlgItemTextA(a1,0x3e9,(int)puVar1);
    if (1 < (int)UINT_008c983c) {
      SendDlgItemMessageA(a1,1000,0xc5,UINT_008c983c - 1,0);
    }
    puVar1 = (undefined1 *)UINT_008c9840;
    if (UINT_008c9840 == 0) {
      puVar1 = &DAT_004f5a98;
    }
    SetDlgItemTextA(a1,1000,(int)puVar1);
    SendDlgItemMessageA(a1,1000,0xb1,0,-1);
    a1_00 = GetDlgItem(a1,1000);
    SetFocus(a1_00);
  }
  else if (a2 == 0x111) {
    if ((a3 & 0xffffU) == 1) {
      GetDlgItemTextA(a1,1000,UINT_008c9838,UINT_008c983c - 1);
      EndDialog(a1,1);
      return (undefined *)0x1;
    }
    if ((a3 & 0xffffU) == 2) {
      EndDialog(a1,2);
      return (undefined *)0x1;
    }
  }
  return (undefined *)0x0;
}

/* ---- 0x00488800  Plat_Alloc ---- */
/* Win95/grimplat.cpp: allocation through the module service table (file/line = grimplat.cpp:1182)
    */

void * __cdecl Plat_Alloc(uint size)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*g_pStd_HS->pAlloc)(size,s_C__grimsrc_libs_grimlib_Win95_gr_004e81ec,0x49e);
  return pvVar1;
}

/* ---- 0x00488820  Plat_Free ---- */
void __cdecl Plat_Free(void *p)

{
  (*g_pStd_HS->pFree)(p);
  return;
}
