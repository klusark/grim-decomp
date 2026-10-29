/* GRIMFANDANGO.EXE :: resource.c
 * functions 0x00480010 .. 0x0048e1e0 (23 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00480010  Resource_RegisterFilioModule ---- */
/* Registers the resource file io as a LecShare module and fills the caller's vtable */

undefined4 Resource_RegisterFilioModule(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  UINT_008a856c = param_1;
  UINT_008a8570 = param_1;
  uVar1 = 1;
  if (UINT_008a85b8 == 0) {
    UINT_008a85b8 = 1;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = Resource_RegisterFilioModule;
      param_2[1] = FUN_004800a0;
      param_2[2] = FUN_004800b0;
      param_2[3] = FUN_00480140;
      param_2[4] = FUN_00482260;
      param_2[5] = FUN_00482380;
      param_2[6] = 0;
      param_2[7] = 0;
    }
    UINT_008a85d0 = 0;
    UINT_008a85c8 = 0;
    UINT_008a85c0 = 0;
    PTR_008a85c4 = (int *)0x0;
    UINT_008a85cc = 0;
    UINT_008a85d8 = 0;
    PTR_008a85d4 = (int *)0x0;
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00480020  FUN_00480020 ---- */
undefined4 __fastcall FUN_00480020(uint param_1,int param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  UINT_008a8570 = param_1;
  if (param_2 == 0) {
    UINT_008a85b8 = 1;
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = Resource_RegisterFilioModule;
      param_4[1] = FUN_004800a0;
      param_4[2] = FUN_004800b0;
      param_4[3] = FUN_00480140;
      param_4[4] = FUN_00482260;
      param_4[5] = FUN_00482380;
      param_4[6] = 0;
      param_4[7] = 0;
    }
    UINT_008a85d0 = 0;
    UINT_008a85c8 = 0;
    UINT_008a85c0 = 0;
    PTR_008a85c4 = (int *)0x0;
    UINT_008a85cc = 0;
    UINT_008a85d8 = 0;
    PTR_008a85d4 = (int *)0x0;
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x004800a0  FUN_004800a0 ---- */
void FUN_004800a0(void)

{
  UINT_008a85b8 = 0;
  return;
}

/* ---- 0x004800b0  FUN_004800b0 ---- */
undefined4 FUN_004800b0(void)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if ((UINT_008a85b8 != 0) && (UINT_008a85bc == 0)) {
    UINT_008a85bc = 1;
    UINT_008a85c8 = Pool_Create(0x10,0x20,8);
    UINT_008a85c0 = Pool_Create(0x120,0x20,8);
    UINT_008a85d0 = Pool_Create(0x120,0x200,0x200);
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x0048d340  Resource_SetNoPurge ---- */
void __cdecl Resource_SetNoPurge(int noPurge)

{
  g_nResNoPurge = noPurge;
  return;
}

/* ---- 0x0048d350  Resource_Load ---- */
/* sputresource.cpp: Res_Load plus the memory budget check that frees unreferenced resources above
   g_nResMemoryBudget */

void * __cdecl Resource_Load(int fourcc,char *name)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *data;
  int iVar1;
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  
  data = Res_Load(fourcc,name);
  if (data != (void *)0x0) {
    iVar1 = Res_GetMemoryUsed();
    if ((g_nResMemoryBudget < iVar1) && (g_nResNoPurge == 0)) {
      Res_GetMemoryUsed();
      local_34 = 0;
      ResRef_Add(&local_34,data,s_C__grimsrc_libs_grimlib_Main_spu_004e9c30,0xfb);
      Res_FreeUnreferenced(UINT_004e9a30,(uint *)&name);
      Res_GetMemoryUsed();
      ResRef_Remove(&local_34);
    }
  }
  return data;
}
#undef local_34


/* ---- 0x0048d3e0  Resource_CloseArchives ---- */
/* Lua DetachFromResources: closes the LAB files so the CD can be swapped */

undefined4 Resource_CloseArchives(void)

{
  Lab_CloseAll();
  return 1;
}

/* ---- 0x0048d3f0  Resource_OpenArchives ---- */
/* Lua AttachToResources: reopens the game's LAB files */

undefined4 Resource_OpenArchives(void)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define acStack_100 (*(char (*)[128])(_frame + (0x110 - 0x100)))
  #define local_80 (*(char (*)[128])(_frame + (0x110 - 0x80)))
  
  GetCurrentDirectoryA(0x80,(int)local_80);
  Reg_GetString(s_GrimDataDir_004dd94c,acStack_100,0x80,&DAT_004f5a98);
  iVar1 = _stricmp(local_80,acStack_100);
  if (iVar1 != 0) {
    Resource_OpenArchivesInDir(acStack_100);
  }
  if (g_szExtraDataDir[0] != '\0') {
    iVar1 = _stricmp(g_szExtraDataDir,acStack_100);
    if (iVar1 != 0) {
      Resource_OpenArchivesInDir(g_szExtraDataDir);
    }
  }
  iVar1 = _stricmp(local_80,g_szExtraDataDir);
  if (iVar1 != 0) {
    Resource_OpenArchivesInDir(local_80);
  }
  return 1;
}
#undef acStack_100
#undef local_80


/* ---- 0x0048d4b0  Resource_SetExtraDataDir ---- */
int __cdecl Resource_SetExtraDataDir(char *dir)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  uVar2 = 0xffffffff;
  do {
    pcVar4 = dir;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar4 = dir + 1;
    cVar1 = *dir;
    dir = pcVar4;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar4 + -uVar2;
  pcVar5 = g_szExtraDataDir;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  return 1;
}

/* ---- 0x0048d550  Resource_OpenLog ---- */
bool Resource_OpenLog(char *param_1)

{
  int iVar1;
  
  iVar1 = Res_OpenLog(param_1);
  return iVar1 == 1;
}

/* ---- 0x0048d570  Resource_OpenArchivesInDir ---- */
/* Opens every *.lab in the directory, then the required archives listed in g_ppRequiredLabs in
   priority order */

int __cdecl Resource_OpenArchivesInDir(char *dir)

{
  unsigned char _frame[0x1a0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  undefined1 *puVar2;
  void *find;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char ***pppcVar7;
  char *pcVar8;
  char *pcVar9;
  char **ppcVar10;
  char **ppcVar11;
  char *pcVar12;
  #define local_18c (*(char (*)[128])(_frame + (0x1a0 - 0x18c)))
  #define local_10c (*(char (*)[268])(_frame + (0x1a0 - 0x10c)))
  
  uVar3 = 0xffffffff;
  do {
    pcVar8 = dir;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = dir + 1;
    cVar1 = *dir;
    dir = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar8 = pcVar8 + -uVar3;
  pcVar12 = local_18c;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar12 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar12 = pcVar12 + 1;
  }
  puVar2 = (undefined1 *)strrchr(local_18c,0x5c);
  if ((puVar2 != (undefined1 *)0x0) && (puVar2[1] == '\0')) {
    *puVar2 = 0;
  }
  find = stdFileUtil_NewFind(local_18c,3,&DAT_004e9c64);
  uVar3 = 0xffffffff;
  pcVar8 = &DAT_004e9c60;
  do {
    pcVar12 = pcVar8;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar12 = pcVar8 + 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar12;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar5 = -1;
  pcVar8 = local_18c;
  do {
    pcVar9 = pcVar8;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar9 = pcVar8 + 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar9;
  } while (cVar1 != '\0');
  pcVar8 = pcVar12 + -uVar3;
  pcVar12 = pcVar9 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar12 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar12 = pcVar12 + 1;
  }
  iVar5 = stdFileUtil_FindNext(find,local_10c);
  while (iVar5 != 0) {
    uVar3 = 0xffffffff;
    pcVar8 = local_10c;
    do {
      pcVar12 = pcVar8;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar12 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar12;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    iVar5 = -1;
    pcVar8 = local_18c;
    do {
      pcVar9 = pcVar8;
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pcVar9 = pcVar8 + 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar9;
    } while (cVar1 != '\0');
    pcVar8 = pcVar12 + -uVar3;
    pcVar12 = pcVar9 + -1;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar12 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar12 = pcVar12 + 1;
    }
    iVar5 = Lab_OpenByName(local_18c);
    if (iVar5 != 0) {
      Lab_MoveToFront(local_18c);
    }
    iVar5 = strrchr(local_18c,0x5c);
    *(undefined1 *)(iVar5 + 1) = 0;
    iVar5 = stdFileUtil_FindNext(find,local_10c);
  }
  stdFileUtil_DisposeFind(find);
  iVar5 = Lab_OpenByName(local_18c);
  if (iVar5 == 0) {
    return 0;
  }
  Lab_MoveToFront(local_18c);
  uVar3 = 0;
  if (g_nRequiredLabCount != 0) {
    pppcVar7 = &g_ppRequiredLabs;
    do {
      uVar4 = 0xffffffff;
      ppcVar10 = *pppcVar7;
      do {
        ppcVar11 = ppcVar10;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        ppcVar11 = (char **)((int)ppcVar10 + 1);
        cVar1 = *(char *)ppcVar10;
        ppcVar10 = ppcVar11;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar5 = -1;
      pcVar8 = local_18c;
      do {
        pcVar12 = pcVar8;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar12 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar12;
      } while (cVar1 != '\0');
      pcVar8 = (char *)((int)ppcVar11 - uVar4);
      pcVar12 = pcVar12 + -1;
      for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar12 = pcVar12 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar12 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar12 = pcVar12 + 1;
      }
      iVar5 = Lab_OpenByName(local_18c);
      if (iVar5 != 0) {
        Lab_MoveToFront(local_18c);
      }
      puVar2 = (undefined1 *)strrchr(local_18c,0x5c);
      *puVar2 = 0;
      iVar5 = strrchr(local_18c,0x5c);
      *(undefined1 *)(iVar5 + 1) = 0;
      uVar3 = uVar3 + 1;
      pppcVar7 = pppcVar7 + 1;
    } while (uVar3 < (uint)g_nRequiredLabCount);
  }
  return 1;
}
#undef local_10c
#undef local_18c


/* ---- 0x0048d770  FUN_0048d770 ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048d770(void)

{
  (*(code *)UINT_008ca1dc)();
  UINT_008ca1d0 = 0;
  _DAT_008ca1f8 = 0;
  return;
}

/* ---- 0x0048d790  FUN_0048d790 ---- */
bool FUN_0048d790(void)

{
  int iVar1;
  
  if (UINT_008ca1fc != 0) {
    return true;
  }
  iVar1 = (*(code *)UINT_008ca1e0)();
  if (iVar1 == 0) {
    UINT_008ca1fc = Resource_RegisterTypes();
  }
  Res_InstallFileServices((GrimServices *)UINT_008ca1d0);
  UINT_008ca200 = rdMaterial_SetLoadHook(FUN_0048e170);
  UINT_008ca204 = rdMaterial_SetFreeHook(FUN_0048e1b0);
  UINT_008a85e8 = (uint)SoundsPeriodic;
  Cos_RegisterSaveVerify(FUN_0048d810);
  return UINT_008ca1fc == 0;
}

/* ---- 0x0048d810  FUN_0048d810 ---- */
void FUN_0048d810(undefined4 param_1)

{
  Res_CountChildren(0x54534f43,param_1);
  return;
}

/* ---- 0x0048d830  FUN_0048d830 ---- */
void FUN_0048d830(void)

{
  (*(code *)UINT_008ca1e4)();
  rdMaterial_SetLoadHook(UINT_008ca200);
  rdMaterial_SetFreeHook(UINT_008ca204);
  Res_RestoreFileServices((GrimServices *)UINT_008ca1d0);
  UINT_008ca1fc = 0;
  return;
}

/* ---- 0x0048d870  Resource_RegisterTypes ---- */
/* Registers the {fourcc, handler} pairs of g_ResTypeTable (BKND, COST, CMAP, SET , FONT, ...) */

undefined4 Resource_RegisterTypes(void)

{
  int iVar1;
  uint *puVar2;
  
  puVar2 = &g_ResTypeTable;
  do {
    iVar1 = ResType_Register(*puVar2,(void *)puVar2[1]);
    if (iVar1 != 1) {
      return 0;
    }
    puVar2 = puVar2 + 2;
  } while (puVar2 < s_DEBUG_Loops__004e9a98);
  return 1;
}

/* ---- 0x0048d8a0  Resource_SetMemoryUsage ---- */
/* Lua SetMemoryUsage */

void __cdecl Resource_SetMemoryUsage(int budget,int b)

{
  if (budget != 0) {
    g_nResMemoryBudget = budget;
  }
  if (b != 0) {
    UINT_004e9a30 = b;
  }
  return;
}

/* ---- 0x0048d8c0  FUN_0048d8c0 ---- */
void * FUN_0048d8c0(int *param_1)

{
  int iVar1;
  void *pvVar2;
  
  if (param_1[2] == 0x53594e43) {
    iVar1 = *param_1;
    if (iVar1 == 1) {
      pvVar2 = (void *)grimSound_LipSyncLoad(param_1[1]);
      if (pvVar2 != (void *)0x0) {
        pvVar2 = Res_Register(param_1[2],(char *)param_1[1],pvVar2);
        return pvVar2;
      }
    }
    else {
      if (iVar1 == 2) {
        grimSound_LipSyncFree(param_1[3]);
        return (void *)0x1;
      }
      if (iVar1 == 3) {
        param_1[4] = *(int *)(param_1[3] + 0x20) + 0x28;
        return (void *)0x1;
      }
    }
  }
  return (void *)0x0;
}

/* ---- 0x0048df50  Resource_ReloadBitmaps ---- */
/* After a display mode change: reloads every BKND frame from disk and remaps it to the new pixel
   format */

void Resource_ReloadBitmaps(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ushort *pixels;
  int iVar1;
  undefined4 uVar2;
  char *name;
  void *pvVar3;
  int iVar4;
  int iVar5;
  #define local_c (*(uint *)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(undefined1 (*)[4])(_frame + (0x20 - 0x4)))
  
  local_8 = 0;
  Res_FindByHandleOrNull(local_4,&local_c,0x444e4b42);
  name = (char *)local_c;
  while (name != (char *)0x0) {
    local_c = (uint)name;
    if (*(int *)(name + 0x20) == 0) {
      pvVar3 = stdBitmap_LoadFile(name,0,0);
      if (pvVar3 != (void *)0x0) {
        iVar4 = 0;
        if (0 < *(int *)(name + 100)) {
          do {
            iVar5 = iVar4 * 4;
            uVar2 = *(undefined4 *)(*(int *)(name + 0x78) + iVar4 * 4);
            iVar1 = iVar4 * 4;
            iVar4 = iVar4 + 1;
            *(undefined4 *)(*(int *)(name + 0x78) + iVar1) =
                 *(undefined4 *)(*(int *)((int)pvVar3 + 0x78) + iVar5);
            *(undefined4 *)(*(int *)((int)pvVar3 + 0x78) + -4 + iVar4 * 4) = uVar2;
          } while (iVar4 < *(int *)(name + 100));
        }
        stdBitmap_Free(pvVar3);
      }
      iVar4 = 0;
      if (0 < *(int *)(name + 100)) {
        do {
          pvVar3 = *(void **)(*(int *)(name + 0x78) + iVar4 * 4);
          Surface_Lock(pvVar3);
          iVar5 = 0;
          if (0 < *(int *)((int)pvVar3 + 0x10)) {
            do {
              Render_RemapPixels((ushort *)
                                 (iVar5 * *(int *)((int)pvVar3 + 0x18) +
                                 *(int *)((int)pvVar3 + 0x5c)),*(uint *)((int)pvVar3 + 0xc));
              iVar5 = iVar5 + 1;
            } while (iVar5 < *(int *)((int)pvVar3 + 0x10));
          }
          Surface_Unlock(pvVar3);
          iVar4 = iVar4 + 1;
        } while (iVar4 < *(int *)(name + 100));
      }
    }
    pixels = (ushort *)(name + 0x74);
    pixels[0] = 0xf81f;
    pixels[1] = 0;
    Render_RemapPixels(pixels,1);
    iVar4 = 0;
    if (0 < *(int *)(name + 100)) {
      do {
        *(undefined4 *)(*(int *)(*(int *)(name + 0x78) + iVar4 * 4) + 0x60) = 0xf81f;
        Render_RemapPixels((ushort *)(*(int *)(*(int *)(name + 0x78) + iVar4 * 4) + 0x60),1);
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(name + 100));
    }
    local_8 = local_8 + *(int *)(name + 100);
    Res_NextInList(local_4,&local_c,0x444e4b42);
    name = (char *)local_c;
  }
  return;
}
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0048e0a0  Resource_RebuildColormaps ---- */
/* Rebuilds the 16-bit tables of every loaded CMAP for the current pixel format */

void Resource_RebuildColormaps(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  #define local_40 (*(uint *)(_frame + (0x50 - 0x40)))
  #define local_3c (*(undefined1 (*)[4])(_frame + (0x50 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x50 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x50 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x50 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x50 - 0x28)))
  #define local_24 (*(uint *)(_frame + (0x50 - 0x24)))
  #define local_20 (*(uint *)(_frame + (0x50 - 0x20)))
  #define local_1c (*(uint *)(_frame + (0x50 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x50 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x50 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x50 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x50 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x50 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x50 - 0x4)))
  
  local_30 = 5;
  local_28 = 5;
  local_20 = 5;
  local_18 = 3;
  local_10 = 3;
  local_38 = 1;
  local_34 = 0x10;
  local_2c = 6;
  local_24 = 0xb;
  local_1c = 0;
  local_14 = 2;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  Res_FindByHandleOrNull(local_3c,&local_40,0x50414d43);
  while (local_40 != 0) {
    puVar1 = (undefined4 *)(local_40 + 0x348);
    ((code *)rdColormap_Build16bitTables)(*puVar1,local_40 + 0x30,0,0,0,&local_38);
    Render_RemapPixels((ushort *)*puVar1,0x4000);
    Res_NextInList(local_3c,&local_40,0x50414d43);
  }
  return;
}
#undef local_10
#undef local_14
#undef local_18
#undef local_1c
#undef local_20
#undef local_24
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_4
#undef local_40
#undef local_8
#undef local_c


/* ---- 0x0048e170  FUN_0048e170 ---- */
void * FUN_0048e170(char *param_1)

{
  void *data;
  
  data = Resource_Load(0x2054414d,param_1);
  if ((data != (void *)0x0) && (*(int *)((int)data + 0x24) == 0)) {
    Res_SetLocked(data,0);
  }
  *(int *)((int)data + 0x24) = *(int *)((int)data + 0x24) + 1;
  return data;
}

/* ---- 0x0048e1b0  FUN_0048e1b0 ---- */
void FUN_0048e1b0(void *param_1)

{
  if (*(int *)((int)param_1 + 0x24) != 0) {
    *(int *)((int)param_1 + 0x24) = *(int *)((int)param_1 + 0x24) + -1;
  }
  if ((param_1 != (void *)0x0) && (*(int *)((int)param_1 + 0x24) == 0)) {
    Res_SetLocked(param_1,1);
  }
  return;
}

/* ---- 0x0048e1e0  FUN_0048e1e0 ---- */
undefined4 FUN_0048e1e0(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = *param_1;
  if (iVar1 != 1) {
    if (iVar1 == 2) {
      puVar2 = (undefined4 *)param_1[3];
      (**(code **)(UINT_008ca1d0 + 0x24))(*puVar2);
      (**(code **)(UINT_008ca1d0 + 0x24))(puVar2);
    }
    else if (iVar1 == 3) {
      param_1[4] = *(int *)(param_1[3] + 4);
      return 1;
    }
  }
  return 1;
}
