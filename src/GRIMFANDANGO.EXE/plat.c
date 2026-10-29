/* GRIMFANDANGO.EXE :: plat.c
 * functions 0x00477f00 .. 0x00488820 (13 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00477f00  Plat_ReturnTrue ---- */
/* Always returns 1; placeholder platform check called from several init paths */

undefined4 Plat_ReturnTrue(void)

{
  return 1;
}

/* ---- 0x00477f10  FUN_00477f10 ---- */
void FUN_00477f10(undefined4 param_1,char *param_2,undefined4 param_3)

{
  unsigned char _frame[0x210] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  #define auStack_200 (*(undefined1 (*)[512])(_frame + (0x210 - 0x200)))
  
  iVar5 = 0;
  bVar3 = false;
  if (DAT_00805fd4 != 0) {
    DebugBreak();
    exit(1);
  }
  DAT_00805fd4 = 1;
  iVar4 = 0;
  cVar2 = *param_2;
  while (cVar2 != '\0') {
    if (cVar2 == '\\') {
      bVar3 = true;
      iVar5 = iVar4;
    }
    iVar1 = iVar4 + 1;
    iVar4 = iVar4 + 1;
    cVar2 = param_2[iVar1];
  }
  if (bVar3) {
    iVar5 = iVar5 + 1;
  }
  ((code *)_vsnprintf)(auStack_200,0x200,s__s__d____s_004dee38,param_2 + iVar5,param_3,param_1);
  iVar5 = fopen(s_assert_txt_004dee28,&DAT_004dee34);
  if (iVar5 != 0) {
    fprintf(iVar5,auStack_200);
    fclose(iVar5);
  }
  MessageBoxA(0,(int)auStack_200,IMG_ADDR(0x004dee18),0x2000);
  DebugBreak();
  exit(1);
  return;
}
#undef auStack_200


/* ---- 0x00478150  Plat_GetPhysicalMemory ---- */
/* Lua GetPhysicalBytes */

undefined4 Plat_GetPhysicalMemory(void)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  #define local_20 (*(undefined4 (*)[2])(_frame + (0x30 - 0x20)))
  #define local_18 (*(undefined4 *)(_frame + (0x30 - 0x18)))
  
  local_20[0] = 0x20;
  GlobalMemoryStatus((int)local_20);
  return local_18;
}
#undef local_18
#undef local_20


/* ---- 0x00487650  Plat_MessageBox ---- */
/* Win95/grimplat.cpp: MessageBoxA on the game window; returns the IDxxx button code (2 = cancel, 7
   = no) */

int __cdecl Plat_MessageBox(char *text,char *caption,uint flags)

{
  int iVar1;
  
  DAT_004e814c = 0;
  Display_SuspendForDialog();
  iVar1 = Win_GetMainHwnd();
  iVar1 = MessageBoxA(iVar1,(int)caption,(int)text,flags);
  Display_ResumeAfterDialog();
  DAT_004e814c = 1;
  return iVar1;
}

/* ---- 0x00487690  Plat_SetDialogDirectory ---- */
void Plat_SetDialogDirectory(undefined4 param_1)

{
  strncpy(g_szDialogOpenDir,param_1,0x103);
  g_szDialogOpenDir[0x103] = '\0';
  return;
}

/* ---- 0x004876b0  Plat_GetDialogFileName ---- */
char * Plat_GetDialogFileName(void)

{
  return g_szDialogOpenDir;
}

/* ---- 0x004876c0  Plat_OpenFileDialog ---- */
int __cdecl Plat_OpenFileDialog(char *title,char *filter)

{
  unsigned char _frame[0x160] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  char **ppcVar2;
  #define local_150 (*(char *(*)[6])(_frame + (0x160 - 0x150)))
  #define local_138 (*(undefined4 *)(_frame + (0x160 - 0x138)))
  #define local_134 (*(undefined1 **)(_frame + (0x160 - 0x134)))
  #define local_130 (*(undefined4 *)(_frame + (0x160 - 0x130)))
  #define local_124 (*(uint *)(_frame + (0x160 - 0x124)))
  #define local_120 (*(char **)(_frame + (0x160 - 0x120)))
  #define local_11c (*(undefined4 *)(_frame + (0x160 - 0x11c)))
  #define local_118 (*(uint *)(_frame + (0x160 - 0x118)))
  #define local_104 (*(undefined1 (*)[260])(_frame + (0x160 - 0x104)))
  
  ppcVar2 = local_150;
  for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (char *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  DAT_004e814c = 0;
  local_104[0] = 0;
  local_150[0] = (char *)0x4c;
  local_150[1] = (char *)Win_GetMainHwnd();
  local_150[3] = filter;
  local_134 = local_104;
  local_124 = -(uint)(g_szDialogOpenDir[0] != '\0') & 0x8c9858;
  local_138 = 1;
  local_130 = 0x104;
  local_120 = title;
  local_11c = 0x100c;
  iVar1 = GetOpenFileNameA((int)local_150);
  if (iVar1 != 0) {
    strncpy(g_szDialogOpenDir,local_134,0x103);
    g_szDialogOpenDir[0x103] = '\0';
    if (((ushort)local_118 != 0) && ((ushort)local_118 < 0x104)) {
      *(undefined1 *)((int)&DAT_008c9854 + (local_118 & 0xffff) + 3) = 0;
    }
    strncpy(g_szDialogFileName,local_134,0x7f);
    g_szDialogFileName[0x7f] = '\0';
    DAT_004e814c = 1;
    return 1;
  }
  DAT_004e814c = 1;
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
#undef local_150


/* ---- 0x004877d0  Plat_SaveFileDialog ---- */
int __cdecl Plat_SaveFileDialog(char *title,char *filter)

{
  unsigned char _frame[0x160] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  char **ppcVar2;
  #define local_150 (*(char *(*)[6])(_frame + (0x160 - 0x150)))
  #define local_138 (*(undefined4 *)(_frame + (0x160 - 0x138)))
  #define local_134 (*(undefined1 **)(_frame + (0x160 - 0x134)))
  #define local_130 (*(undefined4 *)(_frame + (0x160 - 0x130)))
  #define local_124 (*(uint *)(_frame + (0x160 - 0x124)))
  #define local_120 (*(char **)(_frame + (0x160 - 0x120)))
  #define local_11c (*(undefined4 *)(_frame + (0x160 - 0x11c)))
  #define local_118 (*(uint *)(_frame + (0x160 - 0x118)))
  #define local_104 (*(undefined1 (*)[260])(_frame + (0x160 - 0x104)))
  
  ppcVar2 = local_150;
  for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppcVar2 = (char *)0x0;
    ppcVar2 = ppcVar2 + 1;
  }
  local_104[0] = 0;
  local_150[0] = (char *)0x4c;
  local_150[1] = (char *)Win_GetMainHwnd();
  local_150[3] = filter;
  local_134 = local_104;
  local_124 = -(uint)(g_szDialogSaveDir[0] != '\0') & 0x8c9960;
  local_138 = 1;
  local_130 = 0x104;
  local_120 = title;
  local_11c = 0x880e;
  iVar1 = GetSaveFileNameA((int)local_150);
  if (iVar1 != 0) {
    strncpy(g_szDialogSaveDir,local_134,0x103);
    g_szDialogSaveDir[0x103] = '\0';
    if (((ushort)local_118 != 0) && ((ushort)local_118 < 0x104)) {
      (&DAT_008c995f)[local_118 & 0xffff] = 0;
    }
    strncpy(g_szDialogFileName,local_134,0x7f);
    g_szDialogFileName[0x7f] = '\0';
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
#undef local_150


/* ---- 0x004878c0  Plat_PromptDialog ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Editor prompt dialog with labelled numeric fields */

bool Plat_PromptDialog(int param_1,int param_2,undefined4 *param_3,int param_4)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 *puVar10;
  int *piVar11;
  undefined4 *puVar12;
  int iVar13;
  int iVar14;
  undefined4 *puVar15;
  code *a4;
  int iVar16;
  #define local_20 (*(undefined1 (*)[32])(_frame + (0x30 - 0x20)))
  
  if (((param_2 != 0) && (param_3 != (undefined4 *)0x0)) && (0 < param_4)) {
    DAT_008c9850 = param_3;
    DAT_004e814c = 0;
    _DAT_008c9848 = param_1;
    _DAT_008c984c = param_2;
    DAT_008c9854 = param_4;
    iVar9 = (param_4 + 1) * 0xc;
    puVar2 = (undefined4 *)malloc(iVar9);
    piVar3 = (int *)malloc(iVar9);
    uVar4 = Dlg_MakeDialogTemplate
                      (0x90c80884,(param_4 + 1) * 3 + -1,0,0,0x8a,param_4 * 0x14 + 0x19,param_1,
                       s_MS_Sans_Serif_004e8184,8,piVar3);
    *puVar2 = uVar4;
    iVar9 = *piVar3;
    iVar13 = 0;
    param_1 = 1;
    if (0 < param_4) {
      piVar11 = piVar3 + 1;
      puVar5 = puVar2 + 1;
      param_2 = param_2 - (int)param_3;
      do {
        iVar16 = iVar13 * 0x14 + 5;
        uVar4 = Dlg_MakeItemTemplate
                          (0x50000082,5,iVar16,0x32,0xe,iVar13 + 0x41e,
                           *(undefined4 *)(param_2 + (int)param_3),s_STATIC_004e817c,piVar11);
        *puVar5 = uVar4;
        iVar14 = *piVar11;
        ((code *)sprintf)(local_20,&DAT_004ddc18,*param_3);
        uVar4 = Dlg_MakeItemTemplate
                          (0x50810003,0x41,iVar16,0x32,0xe,iVar13 + 0x3ec,local_20,&DAT_004e8174,
                           piVar11 + 1);
        puVar5[1] = uVar4;
        iVar1 = piVar11[1];
        uVar4 = Dlg_MakeItemTemplate
                          (0x500000b6,0x55,iVar16,0x32,0xe,iVar13 + 0x450,0,
                           s_msctls_updown32_004e8164,piVar11 + 2);
        puVar5[2] = uVar4;
        iVar9 = iVar9 + iVar14 + iVar1 + piVar11[2];
        param_1 = param_1 + 3;
        puVar5 = puVar5 + 3;
        piVar11 = piVar11 + 3;
        iVar13 = iVar13 + 1;
        param_3 = param_3 + 1;
      } while (iVar13 < param_4);
    }
    iVar13 = iVar13 * 0x14 + 5;
    uVar4 = Dlg_MakeItemTemplate
                      (0x50010001,5,iVar13,0x32,0xe,1,&DAT_004e8158,s_BUTTON_004e815c,
                       piVar3 + param_1);
    puVar2[param_1] = uVar4;
    iVar16 = piVar3[param_1];
    iVar14 = param_1 + 1;
    uVar4 = Dlg_MakeItemTemplate
                      (0x50010000,0x41,iVar13,0x32,0xe,2,s_Cancel_004e8150,s_BUTTON_004e815c,
                       piVar3 + iVar14);
    puVar2[iVar14] = uVar4;
    param_1 = param_1 + 2;
    puVar5 = (undefined4 *)malloc(iVar9 + iVar16 + piVar3[iVar14]);
    if (0 < param_1) {
      puVar6 = puVar5;
      puVar10 = puVar2;
      do {
        uVar8 = *(uint *)(((int)piVar3 - (int)puVar2) + (int)puVar10);
        puVar12 = (undefined4 *)*puVar10;
        puVar15 = puVar6;
        for (uVar7 = uVar8 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *puVar15 = *puVar12;
          puVar12 = puVar12 + 1;
          puVar15 = puVar15 + 1;
        }
        for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined1 *)puVar15 = *(undefined1 *)puVar12;
          puVar12 = (undefined4 *)((int)puVar12 + 1);
          puVar15 = (undefined4 *)((int)puVar15 + 1);
        }
        puVar6 = (undefined4 *)((int)puVar6 + *(int *)(((int)piVar3 - (int)puVar2) + (int)puVar10));
        free(*puVar10);
        puVar10 = puVar10 + 1;
        param_1 = param_1 + -1;
      } while (param_1 != 0);
    }
    iVar16 = 0;
    a4 = FUN_00488370;
    iVar9 = Win_GetMainHwnd();
    puVar6 = puVar5;
    iVar13 = Win_GetInstance();
    iVar9 = DialogBoxIndirectParamA(iVar13,(int)puVar6,iVar9,(int)a4,iVar16);
    free(puVar5);
    free(puVar2);
    free(piVar3);
    DAT_004e814c = 1;
    return iVar9 == 1;
  }
  return false;
}
#undef local_20


/* ---- 0x00487c10  Plat_TreeSelectDialog ---- */
/* WARNING: Type propagation algorithm not settling */
/* Editor 'Tree Select' dialog; returns the chosen index or -1 */

int __cdecl Plat_TreeSelectDialog(char *title,char **items,int count,int *recursive)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  code *a4;
  int a5;
  #define local_28 (*(uint (*)[4])(_frame + (0x40 - 0x28)))
  #define local_18 (*(int *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(undefined4 (*)[4])(_frame + (0x40 - 0x14)))
  #define local_4 (*(undefined4 *)(_frame + (0x40 - 0x4)))
  
  iVar5 = 0;
  if ((items != (char **)0x0) && (0 < count)) {
    DAT_004e8140 = count;
    DAT_004e814c = 0;
    DAT_004e8138 = title;
    DAT_004e813c = items;
    DAT_004e8144 = -1;
    DAT_004e8148 = 0;
    local_14[0] = Dlg_MakeDialogTemplate
                            (0x90c80884,4,0,0,0x12f,0x9a,s_Tree_Select_004e81b0,
                             s_MS_Sans_Serif_004e8184,8,local_28);
    local_14[1] = Dlg_MakeItemTemplate
                            (0x50b10037,5,5,0xf0,0x91,0x3ea,0,s_SysTreeView32_004e81a0,local_28 + 1)
    ;
    local_14[2] = Dlg_MakeItemTemplate
                            (0x50010001,0xfa,5,0x32,0xe,1,&DAT_004e8158,s_BUTTON_004e815c,
                             local_28 + 2);
    local_14[3] = Dlg_MakeItemTemplate
                            (0x50010000,0xfa,0x19,0x32,0xe,2,s_Cancel_004e8150,s_BUTTON_004e815c,
                             local_28 + 3);
    iVar6 = local_28[0] + local_28[1] + local_28[2] + local_28[3];
    items = (char **)0x4;
    if (*recursive != 0) {
      local_4 = Dlg_MakeItemTemplate
                          (0x50010003,0xfa,0x2d,0x32,0xe,0x3eb,s_Recursive_004e8194,
                           s_BUTTON_004e815c,&local_18);
      iVar6 = iVar6 + local_18;
      items = (char **)0x5;
    }
    puVar1 = (undefined4 *)malloc(iVar6);
    puVar4 = puVar1;
    if (items != (char **)0x0) {
      do {
        uVar3 = local_28[iVar5];
        puVar7 = (undefined4 *)local_14[iVar5];
        puVar8 = puVar4;
        for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
          *puVar8 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar8 = puVar8 + 1;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
          puVar7 = (undefined4 *)((int)puVar7 + 1);
          puVar8 = (undefined4 *)((int)puVar8 + 1);
        }
        puVar4 = (undefined4 *)((int)puVar4 + local_28[iVar5]);
        free(local_14[iVar5]);
        iVar5 = iVar5 + 1;
      } while (iVar5 < (int)items);
    }
    a5 = 0;
    a4 = FUN_00488460;
    iVar5 = Win_GetMainHwnd();
    puVar4 = puVar1;
    iVar6 = Win_GetInstance();
    iVar5 = DialogBoxIndirectParamA(iVar6,(int)puVar4,iVar5,(int)a4,a5);
    free(puVar1);
    DAT_004e814c = 1;
    if (iVar5 == 1) {
      *recursive = DAT_004e8148;
      return DAT_004e8144;
    }
    *recursive = 0;
  }
  return -1;
}
#undef local_14
#undef local_18
#undef local_28
#undef local_4


/* ---- 0x00487e30  Plat_InputDialog ---- */
/* WARNING: Type propagation algorithm not settling */
/* Lua InputDialog: modal text entry dialog */

int __cdecl Plat_InputDialog(char *title,char *prompt,char *buf,int bufSize,char *defaultText)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  undefined4 *puVar2;
  int a1;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  code *a4;
  int a5;
  #define local_28 (*(uint (*)[5])(_frame + (0x40 - 0x28)))
  #define local_14 (*(undefined4 (*)[5])(_frame + (0x40 - 0x14)))
  
  iVar5 = 0;
  if ((buf != (char *)0x0) && (1 < bufSize)) {
    DAT_008c9838 = buf;
    DAT_008c9830 = title;
    DAT_008c983c = bufSize;
    DAT_004e814c = 0;
    DAT_008c9834 = prompt;
    DAT_008c9840 = defaultText;
    local_14[0] = Dlg_MakeDialogTemplate
                            (0x90c80884,4,0,0,0x12f,0x36,s_Input_004e81bc,s_MS_Sans_Serif_004e8184,8
                             ,local_28);
    local_14[1] = Dlg_MakeItemTemplate
                            (0x5000008b,5,7,0xf0,0xe,0x3e9,0,s_STATIC_004e817c,local_28 + 1);
    local_14[2] = Dlg_MakeItemTemplate(0x50810080,5,0x19,0xf0,0xe,1000,0,&DAT_004e8174,local_28 + 2)
    ;
    local_14[3] = Dlg_MakeItemTemplate
                            (0x50010001,0xfa,5,0x32,0xe,1,&DAT_004e8158,s_BUTTON_004e815c,
                             local_28 + 3);
    local_14[4] = Dlg_MakeItemTemplate
                            (0x50010000,0xfa,0x19,0x32,0xe,2,s_Cancel_004e8150,s_BUTTON_004e815c,
                             local_28 + 4);
    puVar2 = (undefined4 *)
             malloc(local_28[4] + local_28[0] + local_28[1] + local_28[2] + local_28[3]);
    puVar6 = puVar2;
    do {
      uVar4 = *(uint *)((int)local_28 + iVar5);
      puVar1 = *(undefined4 **)((int)local_14 + iVar5);
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
      puVar6 = (undefined4 *)((int)puVar6 + *(int *)((int)local_28 + iVar5));
      free(puVar1);
      iVar5 = iVar5 + 4;
    } while (iVar5 < 0x14);
    Display_SuspendForDialog();
    a5 = 0;
    a4 = FUN_004886f0;
    iVar5 = Win_GetMainHwnd();
    puVar6 = puVar2;
    a1 = Win_GetInstance();
    iVar5 = DialogBoxIndirectParamA(a1,(int)puVar6,iVar5,(int)a4,a5);
    Display_ResumeAfterDialog();
    free(puVar2);
    DAT_004e814c = 1;
    return (uint)(iVar5 == 1);
  }
  return 0;
}
#undef local_14
#undef local_28


/* ---- 0x00488800  Plat_Alloc ---- */
/* Win95/grimplat.cpp: allocation through the module service table (file/line = grimplat.cpp:1182)
    */

void * __cdecl Plat_Alloc(uint size)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*g_pSvcMain->pAlloc)(size,s_C__grimsrc_libs_grimlib_Win95_gr_004e81ec,0x49e);
  return pvVar1;
}

/* ---- 0x00488820  Plat_Free ---- */
void __cdecl Plat_Free(void *p)

{
  (*g_pSvcMain->pFree)(p);
  return;
}
