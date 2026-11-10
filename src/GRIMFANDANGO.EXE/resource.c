/* GRIMFANDANGO.EXE :: resource.c
 * functions 0x00480010 .. 0x0048e1b0 (21 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00480010  Res_SysInitialize ---- */
/* Registers the resource file io as a LecShare module and fills the caller's vtable Original name
   Res_SysInitialize (the remaster's GrimFandango (Linux): the only unmatched callee of
   sputResource_Initialize; 1 matched neighbours agree, 0 disagree); was
   Resource_RegisterFilioModule. */

undefined4 Res_SysInitialize(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  g_dwResHS = param_1;
  g_dwLowLevelHS = param_1;
  uVar1 = 1;
  if (g_dwResSysInitialized == 0) {
    g_dwResSysInitialized = 1;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = Res_SysInitialize;
      param_2[1] = Res_SysTerminate;
      param_2[2] = Res_SysStartup;
      param_2[3] = Res_SysShutdown;
      param_2[4] = Res_SysSave;
      param_2[5] = Res_SysLoad;
      param_2[6] = 0;
      param_2[7] = 0;
    }
    g_dwResNodePool = 0;
    g_dwResTypePool = 0;
    g_dwResFilePool = 0;
    g_pResFileList = (int *)0x0;
    g_dwResTypeList = 0;
    g_dwOldestResNode = 0;
    g_pNewestResNode = (int *)0x0;
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00480020  FUN_00480020 ---- */
undefined4 __fastcall FUN_00480020(uint param_1,int param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  g_dwLowLevelHS = param_1;
  if (param_2 == 0) {
    g_dwResSysInitialized = 1;
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = Res_SysInitialize;
      param_4[1] = Res_SysTerminate;
      param_4[2] = Res_SysStartup;
      param_4[3] = Res_SysShutdown;
      param_4[4] = Res_SysSave;
      param_4[5] = Res_SysLoad;
      param_4[6] = 0;
      param_4[7] = 0;
    }
    g_dwResNodePool = 0;
    g_dwResTypePool = 0;
    g_dwResFilePool = 0;
    g_pResFileList = (int *)0x0;
    g_dwResTypeList = 0;
    g_dwOldestResNode = 0;
    g_pNewestResNode = (int *)0x0;
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x004800a0  Res_SysTerminate ---- */
/* Module interface slot 1 (Resource_Filio): called by Engine_ResetSubsystems / when registration
   fails; drops the service table pointer and clears the initialised flag. Original name
   Res_SysTerminate (the remaster's GrimFandango (Linux): aligned call in Res_SysInitialize); was
   Resource_Filio_Terminate. */

void Res_SysTerminate(void)

{
  g_dwResSysInitialized = 0;
  return;
}

/* ---- 0x004800b0  Res_SysStartup ---- */
/* Module interface slot 2 (Resource_Filio): called by Engine_InitSubsystems, returns 0 on success
   (non-zero makes the whole start-up unwind). Pools for the LAB archive records are created in
   _Start. Original name Res_SysStartup (the remaster's GrimFandango (Linux): aligned call in
   Res_SysInitialize); was Resource_Filio_Start. */

undefined4 Res_SysStartup(void)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if ((g_dwResSysInitialized != 0) && (g_dwResSysStarted == 0)) {
    g_dwResSysStarted = 1;
    g_dwResTypePool = Memory_AllocatePool(0x10,0x20,8);
    g_dwResFilePool = Memory_AllocatePool(0x120,0x20,8);
    g_dwResNodePool = Memory_AllocatePool(0x120,0x200,0x200);
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00480140  Res_SysShutdown ---- */
/* Module interface slot 3 (Resource_Filio): called by Engine_ShutdownSubsystems in reverse order;
   releases what _Start created. Original name Res_SysShutdown (the remaster's GrimFandango (Linux):
   aligned call in Res_SysInitialize); was Resource_Filio_Stop. */

void Res_SysShutdown(void)

{
  if (g_dwResSysStarted != 0) {
    Res_FileCloseAll();
    Res_FreeAll();
    if (g_dwResTypePool != 0) {
      Memory_FreePool(g_dwResTypePool);
    }
    if (g_dwResFilePool != 0) {
      Memory_FreePool(g_dwResFilePool);
    }
    if (g_dwResNodePool != 0) {
      Memory_FreePool(g_dwResNodePool);
    }
  }
  g_dwResSysStarted = 0;
  return;
}

/* ---- 0x00482260  Res_SysSave ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Module interface slot 4 (Resource_Filio): save-game writer, calls the SaveGame_Write callback it
   is handed for every field. Original name Res_SysSave (the remaster's GrimFandango (Linux):
   strings: 'TEMP'); was Resource_Filio_SaveState. */

undefined4 Res_SysSave(code *param_1)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  char cVar1;
  code *pcVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  char *pcVar6;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  pcVar2 = param_1;
  for (piVar5 = g_pNewestResNode; param_1 = pcVar2, piVar5 != (int *)0x0; piVar5 = (int *)*piVar5) {
    if (((piVar5[9] != 0) && (iVar3 = String_ContainsSubstring(piVar5[2],&DAT_004e7b14), iVar3 == 0)
        ) || ((*(byte *)(piVar5 + 7) & 8) != 0)) {
      local_4 = local_4 + 1;
    }
    pcVar2 = param_1;
  }
  iVar3 = (*pcVar2)(&local_4,4);
  if (iVar3 != 0) {
    return 1;
  }
  local_4 = 0;
  piVar5 = g_pNewestResNode;
  if (g_pNewestResNode == (int *)0x0) {
    return 0;
  }
  do {
    if (((piVar5[9] != 0) && (iVar3 = String_ContainsSubstring(piVar5[2],&DAT_004e7b14), iVar3 == 0)
        ) || ((*(byte *)(piVar5 + 7) & 8) != 0)) {
      uVar4 = 0xffffffff;
      pcVar6 = (char *)piVar5[2];
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      param_1 = (code *)(~uVar4 - 1);
      iVar3 = (*pcVar2)(&param_1,4);
      if (((iVar3 != 0) || (iVar3 = (*pcVar2)(piVar5[2],param_1), iVar3 != 0)) ||
         (iVar3 = (*pcVar2)(piVar5 + 4,4), iVar3 != 0)) {
        return 1;
      }
      piVar5[6] = piVar5[5];
      iVar3 = (*pcVar2)(piVar5 + 6,4);
      if (iVar3 != 0) {
        return 1;
      }
      local_4 = local_4 + 1;
    }
    piVar5 = (int *)*piVar5;
    if (piVar5 == (int *)0x0) {
      return 0;
    }
  } while( true );
}
#undef local_4

#endif


/* ---- 0x00482380  Res_SysLoad ---- */
/* Module interface slot 5 (Resource_Filio): save-game reader, calls the SaveGame_Read callback it
   is handed; returns non-zero on a short read. Original name Res_SysLoad (the remaster's
   GrimFandango (Linux): aligned call in Res_SysInitialize); was Resource_Filio_RestoreState. */

undefined4 Res_SysLoad(code *param_1)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int iVar2;
  void *pvVar3;
  #define iStack_110 (*(int *)(_frame + (0x120 - 0x110)))
  #define local_10c (*(int *)(_frame + (0x120 - 0x10c)))
  #define iStack_108 (*(int *)(_frame + (0x120 - 0x108)))
  #define iStack_104 (*(int *)(_frame + (0x120 - 0x104)))
  #define acStack_100 (*(char (*)[256])(_frame + (0x120 - 0x100)))
  
  iVar1 = (*param_1)(&local_10c,4);
  if (iVar1 != 0) {
    return 1;
  }
  iVar1 = 0;
  if (local_10c < 1) {
    return 0;
  }
  while( true ) {
    iVar2 = (*param_1)(&iStack_110,4);
    if ((iVar2 != 0) || (0xff < iStack_110)) {
      return 1;
    }
    iVar2 = (*param_1)(acStack_100,iStack_110);
    if (iVar2 != 0) {
      return 1;
    }
    acStack_100[iStack_110] = '\0';
    iVar2 = (*param_1)(&iStack_108,4);
    if (iVar2 != 0) break;
    pvVar3 = res_Load(iStack_108,acStack_100,&iStack_104);
    if (iStack_104 == 0) {
      return 1;
    }
    iVar2 = (*param_1)((int)pvVar3 + 0x18,4);
    if (iVar2 != 0) {
      return 1;
    }
    iVar1 = iVar1 + 1;
    if (local_10c <= iVar1) {
      return 0;
    }
  }
  return 1;
}
#undef acStack_100
#undef iStack_104
#undef iStack_108
#undef iStack_110
#undef local_10c


/* ---- 0x0048d340  Resource_SetNoPurge ---- */
void __cdecl Resource_SetNoPurge(int noPurge)

{
  g_nStopPurge = noPurge;
  return;
}

/* ---- 0x0048d350  sputResource_Alloc ---- */
/* sputresource.cpp: Res_Load plus the memory budget check that frees unreferenced resources above
   g_nMaxRealMemoryUsage Original name sputResource_Alloc (the remaster's GrimFandango (Linux): the
   only unmatched callee of Lua_LoadCostume; 11 matched neighbours agree, 1 disagree); was
   Resource_Load. */

void * __cdecl sputResource_Alloc(int fourcc,char *name)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *data;
  int iVar1;
  #define local_34 (*(uint *)(_frame + (0x50 - 0x34)))
  
  data = Res_Load(fourcc,name);
  if (data != (void *)0x0) {
    iVar1 = daTotalAllocated();
    if ((g_nMaxRealMemoryUsage < iVar1) && (g_nStopPurge == 0)) {
      daTotalAllocated();
      local_34 = 0;
      Res_SetReference(&local_34,data,s_C__grimsrc_libs_grimlib_Main_spu_004e9c30,0xfb);
      Res_SysPurgeBySize(g_dwPurgeAmount,(uint *)&name);
      daTotalAllocated();
      Res_RemoveReference(&local_34);
    }
  }
  return data;
}
#undef local_34


/* ---- 0x0048d3e0  sputResource_CloseResources ---- */
/* Lua DetachFromResources: closes the LAB files so the CD can be swapped Original name
   sputResource_CloseResources (the remaster's GrimFandango (Linux): aligned call in
   sputLua_AttachToResourcesL, sputLua_DetachFromResourcesL, sputLua_SearchForFileOrSwapCDsL); was
   Resource_CloseArchives. */

undefined4 sputResource_CloseResources(void)

{
  Res_FileCloseAll();
  return 1;
}

/* ---- 0x0048d3f0  grimlib_FindResources ---- */
/* Lua AttachToResources: reopens the game's LAB files Original name grimlib_FindResources (the
   remaster's GrimFandango (Linux): aligned call in sputLua_AttachToResourcesL,
   sputLua_SearchForFileOrSwapCDsL); was Resource_OpenArchives. */

undefined4 grimlib_FindResources(void)

{
  unsigned char _frame[0x110] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  #define acStack_100 (*(char (*)[128])(_frame + (0x110 - 0x100)))
  #define local_80 (*(char (*)[128])(_frame + (0x110 - 0x80)))
  
  GetCurrentDirectoryA(0x80,(int)local_80);
  wuRegistry_GetStr(s_GrimDataDir_004dd94c,acStack_100,0x80,&DAT_004f5a98);
  iVar1 = _stricmp(local_80,acStack_100);
  if (iVar1 != 0) {
    AddResourcePath(acStack_100);
  }
  if (g_szExtraDataDir[0] != '\0') {
    iVar1 = _stricmp(g_szExtraDataDir,acStack_100);
    if (iVar1 != 0) {
      AddResourcePath(g_szExtraDataDir);
    }
  }
  iVar1 = _stricmp(local_80,g_szExtraDataDir);
  if (iVar1 != 0) {
    AddResourcePath(local_80);
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
int Resource_OpenLog(char *param_1)

{
  int iVar1;
  
  iVar1 = Res_OpenLog(param_1);
  return iVar1 == 1;
}

/* ---- 0x0048d570  AddResourcePath ---- */
/* Opens every *.lab in the directory, then the required archives listed in g_ppRequiredLabs in
   priority order Original name AddResourcePath (the remaster's GrimFandango (Linux): same sequence:
   strip the trailing separator, stdFileUtil_NewFind(dir, 3, ext), FindNext loop opening each
   archive and moving it to the front, DisposeFind, then the fixed list); was
   Resource_OpenArchivesInDir. */

int __cdecl AddResourcePath(char *dir)

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
    iVar5 = Res_FileOpen(local_18c);
    if (iVar5 != 0) {
      Res_FileMoveToFront(local_18c);
    }
    iVar5 = strrchr(local_18c,0x5c);
    *(undefined1 *)(iVar5 + 1) = 0;
    iVar5 = stdFileUtil_FindNext(find,local_10c);
  }
  stdFileUtil_DisposeFind(find);
  iVar5 = Res_FileOpen(local_18c);
  if (iVar5 == 0) {
    return 0;
  }
  Res_FileMoveToFront(local_18c);
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
      iVar5 = Res_FileOpen(local_18c);
      if (iVar5 != 0) {
        Res_FileMoveToFront(local_18c);
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


/* ---- 0x0048d810  Resource_CountCostumeRefs ---- */
/* Callback given to Cos_RegisterSaveVerify: Res_CountChildren for 'COST' resources (checks the
   costumes referenced by a save). */

void Resource_CountCostumeRefs(undefined4 param_1)

{
  Res_CountChildren(0x54534f43,param_1);
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
    iVar1 = Res_SysRegisterHandler(*puVar2,(void *)puVar2[1]);
    if (iVar1 != 1) {
      return 0;
    }
    puVar2 = puVar2 + 2;
  } while (puVar2 < s_DEBUG_Loops__004e9a98);
  return 1;
}

/* ---- 0x0048d8a0  sputResource_SetMemoryUsage ---- */
/* Lua SetMemoryUsage Original name sputResource_SetMemoryUsage (the remaster's GrimFandango
   (Linux): sets MaxRealMemoryUsage and PurgeAmount when non-zero); was Resource_SetMemoryUsage. */

void __cdecl sputResource_SetMemoryUsage(int budget,int b)

{
  if (budget != 0) {
    g_nMaxRealMemoryUsage = budget;
  }
  if (b != 0) {
    g_dwPurgeAmount = b;
  }
  return;
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
  Res_GetFirstType(local_4,&local_c,0x444e4b42);
  name = (char *)local_c;
  while (name != (char *)0x0) {
    local_c = (uint)name;
    if (*(int *)(name + 0x20) == 0) {
      pvVar3 = stdLoadImageData(name,0,0);
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
          stdDisplay_VBufferLock(pvVar3);
          iVar5 = 0;
          if (0 < *(int *)((int)pvVar3 + 0x10)) {
            do {
              sputRender_ColorCorrect
                        ((ushort *)
                         (iVar5 * *(int *)((int)pvVar3 + 0x18) + *(int *)((int)pvVar3 + 0x5c)),
                         *(uint *)((int)pvVar3 + 0xc));
              iVar5 = iVar5 + 1;
            } while (iVar5 < *(int *)((int)pvVar3 + 0x10));
          }
          stdDisplay_VBufferUnlock(pvVar3);
          iVar4 = iVar4 + 1;
        } while (iVar4 < *(int *)(name + 100));
      }
    }
    pixels = (ushort *)(name + 0x74);
    pixels[0] = 0xf81f;
    pixels[1] = 0;
    sputRender_ColorCorrect(pixels,1);
    iVar4 = 0;
    if (0 < *(int *)(name + 100)) {
      do {
        *(undefined4 *)(*(int *)(*(int *)(name + 0x78) + iVar4 * 4) + 0x60) = 0xf81f;
        sputRender_ColorCorrect((ushort *)(*(int *)(*(int *)(name + 0x78) + iVar4 * 4) + 0x60),1);
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(name + 100));
    }
    local_8 = local_8 + *(int *)(name + 100);
    Res_GetNextType(local_4,&local_c,0x444e4b42);
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
  Res_GetFirstType(local_3c,&local_40,0x50414d43);
  while (local_40 != 0) {
    puVar1 = (undefined4 *)(local_40 + 0x348);
    rdColormap_BuildRGB16((undefined2 *)*puVar1,(ushort *)(local_40 + 0x30),0,0,0,(int)&local_38);
    sputRender_ColorCorrect((ushort *)*puVar1,0x4000);
    Res_GetNextType(local_3c,&local_40,0x50414d43);
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


/* ---- 0x0048e170  sputResource_MatLoader ---- */
/* rdMaterial load hook (rdMaterial_SetLoadHook): loads the 'MAT ' resource and counts a reference
   (+0x24), locking it on the first one. Original name sputResource_MatLoader (the remaster's
   GrimFandango (Linux): aligned call in sputResource_Startup); was Resource_MaterialLoadHook. */

void * sputResource_MatLoader(char *param_1)

{
  void *data;
  
  data = sputResource_Alloc(0x2054414d,param_1);
  if ((data != (void *)0x0) && (*(int *)((int)data + 0x24) == 0)) {
    Res_SetPurgable(data,0);
  }
  *(int *)((int)data + 0x24) = *(int *)((int)data + 0x24) + 1;
  return data;
}

/* ---- 0x0048e1b0  sputResource_MatUnloader ---- */
/* rdMaterial free hook (rdMaterial_SetFreeHook): drops a reference and unlocks the resource when
   the count reaches 0. Original name sputResource_MatUnloader (the remaster's GrimFandango (Linux):
   aligned call in sputResource_Startup); was Resource_MaterialFreeHook. */

void sputResource_MatUnloader(void *param_1)

{
  if (*(int *)((int)param_1 + 0x24) != 0) {
    *(int *)((int)param_1 + 0x24) = *(int *)((int)param_1 + 0x24) + -1;
  }
  if ((param_1 != (void *)0x0) && (*(int *)((int)param_1 + 0x24) == 0)) {
    Res_SetPurgable(param_1,1);
  }
  return;
}
