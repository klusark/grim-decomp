/* GRIMFANDANGO.EXE :: res.c
 * functions 0x00480000 .. 0x0048e230 (30 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00480000  daTotalAllocated ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Total bytes held by loaded resources Original name daTotalAllocated (the remaster's GrimFandango
   (Linux): the only unmatched callee of Lua_GetMemoryUsage; the only unmatched callee of
   Lua_ResReport; 3 matched neighbours agree, 0 disagree); was Res_GetMemoryUsed. */

int daTotalAllocated(void)

{
  return g_dwStdMemory_curState;
}

/* ---- 0x00480230  Res_SysAddHandle ---- */
/* Called by type handlers after loading to create the resource record Original name
   Res_SysAddHandle (the remaster's GrimFandango (Linux): aligned call in
   sputResource_ColormapHandler, sputResource_KeyframeHandler, sputResource_MaterialHandler); was
   Res_Register. */

void * __cdecl Res_SysAddHandle(int fourcc,char *name,void *data)

{
  undefined4 *puVar1;
  Resource *pRVar2;
  int iVar3;
  void *pvVar4;
  
  pvVar4 = (void *)0x0;
  pRVar2 = Res_FindByData(data);
  if (pRVar2 == (Resource *)0x0) {
    pRVar2 = Res_CreateRecord(fourcc,name,data);
    if (pRVar2 != (Resource *)0x0) {
      if (g_dwLogFile != 0) {
        puVar1 = (undefined4 *)(g_dwResHS + 0x54);
        iVar3 = Res_GetSize(pRVar2);
        (*(code *)*puVar1)(g_dwLogFile,s_Resource____12s__allocated___8ld_004e79f4,name,iVar3);
      }
      return (void *)0x1;
    }
  }
  else {
    pvVar4 = (void *)0x4;
  }
  return pvVar4;
}

/* ---- 0x004802b0  Res_FindExternalFile ---- */
/* Original name Res_FindExternalFile (the remaster's GrimFandango (Linux): aligned call in
   sputSmush_GetMovieLength); was Res_GetFilePath. */

int __cdecl Res_FindExternalFile(char *name,char *buf,int size)

{
  unsigned char _frame[0x330] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *archive;
  uint uVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  #define local_31c (*(byte (*)[260])(_frame + (0x330 - 0x31c)))
  #define local_218 (*(LabFile *)(_frame + (0x330 - 0x218)))
  
  iVar2 = 0;
  iVar3 = 0;
  uVar1 = Res_HashName(name,(char *)local_31c);
  for (archive = g_pResFileList; archive != (int *)0x0; archive = (int *)*archive) {
    if (iVar3 != 0) goto LAB_0048030d;
    iVar3 = 0;
    if ((*(byte *)(archive + 0x45) & 2) == 0) {
      iVar3 = res_FindDirectoryEntry((int)archive,0,local_31c,uVar1,&local_218);
    }
  }
  if (iVar3 != 0) {
LAB_0048030d:
    pcVar4 = buf;
    for (uVar1 = (uint)size >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      pcVar4[0] = '\0';
      pcVar4[1] = '\0';
      pcVar4[2] = '\0';
      pcVar4[3] = '\0';
      pcVar4 = pcVar4 + 4;
    }
    for (uVar1 = size & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *pcVar4 = '\0';
      pcVar4 = pcVar4 + 1;
    }
    strncpy((uint *)buf,(uint *)local_218.aPath,size - 1);
    iVar2 = 1;
  }
  return iVar2;
}
#undef local_218
#undef local_31c


/* ---- 0x00480520  Res_Load ---- */
/* Loads (or finds) the resource and returns its data pointer; the record is moved to the front of
   the LRU list */

void * __cdecl Res_Load(int type,char *name)

{
  void *res;
  void *pvVar1;
  
  pvVar1 = (void *)0x0;
  res = res_Load(type,name,(int *)&name);
  if (res != (void *)0x0) {
    Res_MoveToFront(res);
    pvVar1 = *(void **)((int)res + 0x14);
  }
  return pvVar1;
}

/* ---- 0x00480560  Res_SetPurgable ---- */
/* Locks (flag 8) a resource against Res_FreeUnreferenced; returns the previous unlocked state
   Original name Res_SetPurgable (the remaster's GrimFandango (Linux): aligned call in
   sputResource_MatLoader, sputResource_MatUnloader, sputResource_MaterialHandler); was
   Res_SetLocked. */

uint __cdecl Res_SetPurgable(void *data,int unlock)

{
  ushort uVar1;
  Resource *pRVar2;
  uint uVar3;
  
  uVar3 = 0;
  pRVar2 = Res_FindByData(data);
  if (pRVar2 != (Resource *)0x0) {
    uVar1 = *(ushort *)&pRVar2->bFlags;
    uVar3 = ((byte)~(byte)uVar1 & 8) >> 3;
    if (unlock != 0) {
      *(ushort *)&pRVar2->bFlags = uVar1 & 0xfff7;
      return uVar3;
    }
    *(ushort *)&pRVar2->bFlags = uVar1 | 8;
  }
  return uVar3;
}

/* ---- 0x004805b0  Res_SysPurgeBySize ---- */
/* Walks the LRU list from the oldest end freeing unreferenced, unlocked resources until bytesWanted
   is reached; calls the yield hook every 5 items Original name Res_SysPurgeBySize (the remaster's
   GrimFandango (Linux): aligned call in sputResource_Alloc); was Res_FreeUnreferenced. */

int __cdecl Res_SysPurgeBySize(uint bytesWanted,uint *bytesFreed)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  Resource *pRVar1;
  bool bVar2;
  Resource *res;
  int iVar3;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  bVar2 = true;
  local_8 = 0;
  *bytesFreed = 0;
  if (bytesWanted != 0) {
    while (bVar2) {
      bVar2 = false;
      pRVar1 = (Resource *)g_dwOldestResNode;
      while (res = pRVar1, res != (Resource *)0x0) {
        if (bytesWanted <= *bytesFreed) goto LAB_0048065f;
        local_8 = local_8 + 1;
        if (((code *)g_dwRes_pPeriodicCallback != (code *)0x0) && ((int)local_8 % 5 == 0)) {
          (*(code *)g_dwRes_pPeriodicCallback)();
        }
        pRVar1 = res->pPrev;
        if ((res->pRefs == (ResRef *)0x0) && ((res->bFlags & 8) == 0)) {
          iVar3 = Res_GetSize(res);
          *bytesFreed = *bytesFreed + iVar3;
          Res_CallUnload(res);
          Res_Unlink(res);
          bVar2 = true;
        }
      }
      if (bytesWanted <= *bytesFreed) break;
    }
  }
  if (bytesWanted <= *bytesFreed) {
LAB_0048065f:
    local_4 = 1;
  }
  return local_4;
}
#undef local_4
#undef local_8


/* ---- 0x00480680  Res_Dump ---- */
/* Dumps 'Resource %12s size %7ld REFERENCED' lines for every loaded resource Original name Res_Dump
   (the remaster's GrimFandango (Linux): strings: 'REFERENCED' | 'Total: %d items, %d bytes\n' |
   'Resource %-12s,\t\tsize = %7ld\t%s\n'); was Res_WriteReport. */

int __cdecl Res_Dump(char *filename,int type)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  Resource *res;
  int fh;
  char *pcVar2;
  int iVar3;
  int iVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  iVar4 = 0;
  fh = Res_FOpen(filename,&DAT_004dd478);
  res = g_pNewestResNode;
  if (fh != 0) {
    for (; res != (Resource *)0x0; res = res->pNext) {
      if ((type == 0) || (res->dwType == type)) {
        pcVar2 = s_REFERENCED_004e7a80;
        if (res->pRefs == (ResRef *)0x0) {
          pcVar2 = &DAT_004f5a98;
        }
        puVar1 = (undefined4 *)(g_dwResHS + 0x54);
        iVar3 = Res_GetSize(res);
        (*(code *)*puVar1)(fh,s_Resource___12s__size____7ld__s_004e7a5c,res->pName,iVar3,pcVar2);
        iVar3 = Res_GetSize(res);
        iVar4 = iVar4 + iVar3;
        local_4 = local_4 + 1;
      }
    }
    (**(code **)(g_dwResHS + 0x54))(fh,s_Total___d_items___d_bytes_004e7a40,local_4,iVar4);
    Res_FClose(fh);
    return 1;
  }
  return 0;
}
#undef local_4


/* ---- 0x00480740  Res_Log ---- */
/* Original name Res_Log (the remaster's GrimFandango (Linux): same body (open the log file for
   writing when a name is given, else close it)); was Res_OpenLog. */

int __cdecl Res_Log(char *filename)

{
  if (filename != (char *)0x0) {
    g_dwLogFile = (**(code **)(g_dwResHS + 0x30))(filename,&DAT_004dd478);
    return 1;
  }
  if (g_dwLogFile != 0) {
    (**(code **)(g_dwResHS + 0x34))(g_dwLogFile);
    g_dwLogFile = 0;
  }
  return 1;
}

/* ---- 0x00480790  Res_OverrideFileCalls ---- */
/* Temp/Res.c: keeps a copy of the raw file services in g_aLowLevelHS and replaces
   svc->fopen..fprintf with the ResFile_* versions so every open goes through the LAB archive system
   Original name Res_OverrideFileCalls (the remaster's GrimFandango (Linux): aligned call in
   sputResource_Startup); was Res_InstallFileServices. */

void __cdecl Res_OverrideFileCalls(GrimServices *svc)

{
  int iVar1;
  GrimServices *pGVar2;
  GrimServices *pGVar3;
  
  pGVar2 = svc;
  pGVar3 = &g_aLowLevelHS;
  for (iVar1 = 0x1c; iVar1 != 0; iVar1 = iVar1 + -1) {
    pGVar3->flVersion = pGVar2->flVersion;
    pGVar2 = (GrimServices *)&pGVar2->pPrintf;
    pGVar3 = (GrimServices *)&pGVar3->pPrintf;
  }
  g_dwLowLevelHS = (uint)&g_aLowLevelHS;
  svc->pFopen = Res_FOpen;
  svc->pFclose = Res_FClose;
  svc->pFread = Res_FRead;
  svc->pFgets = Res_FGets;
  svc->pFwrite = Res_FWrite;
  svc->pFeof = Res_FEOF;
  svc->pFtell = Res_FTell;
  svc->pFseek = Res_FSeek;
  svc->pFileSize = Res_FSize;
  svc->pFprintf = Res_FPrintf;
  return;
}

/* ---- 0x00480800  Res_RestoreFileCalls ---- */
/* Original name Res_RestoreFileCalls (the remaster's GrimFandango (Linux): same body (copies the
   ten file entries +0x30..+0x54 of the low-level services back, pLowLevelHS = pResHS); called by
   sputResource_Shutdown in both builds); was Res_RestoreFileServices. */

void __cdecl Res_RestoreFileCalls(GrimServices *svc)

{
  svc->pFopen = *(void **)(g_dwLowLevelHS + 0x30);
  svc->pFclose = *(void **)(g_dwLowLevelHS + 0x34);
  svc->pFread = *(void **)(g_dwLowLevelHS + 0x38);
  svc->pFgets = *(void **)(g_dwLowLevelHS + 0x3c);
  svc->pFwrite = *(void **)(g_dwLowLevelHS + 0x40);
  svc->pFeof = *(void **)(g_dwLowLevelHS + 0x44);
  svc->pFtell = *(void **)(g_dwLowLevelHS + 0x48);
  svc->pFseek = *(void **)(g_dwLowLevelHS + 0x4c);
  svc->pFileSize = *(void **)(g_dwLowLevelHS + 0x50);
  svc->pFprintf = *(void **)(g_dwLowLevelHS + 0x54);
  g_dwLowLevelHS = g_dwResHS;
  return;
}

/* ---- 0x004810e0  Res_FindByData ---- */
Resource * __cdecl Res_FindByData(void *data)

{
  Resource *pRVar1;
  
  pRVar1 = g_pNewestResNode;
  while( true ) {
    if (pRVar1 == (Resource *)0x0) {
      return (Resource *)0x0;
    }
    if (pRVar1->pData == data) break;
    pRVar1 = pRVar1->pNext;
  }
  return pRVar1;
}

/* ---- 0x00481100  Res_HandleFromSerialNumber ---- */
/* Original name Res_HandleFromSerialNumber (the remaster's GrimFandango (Linux): aligned call in
   sputLua_RestoreIndirector, sputRoom_Restore, sputText_Restore); was Res_DataFromHandle. */

void * __cdecl Res_HandleFromSerialNumber(void *handle)

{
  Resource *pRVar1;
  
  pRVar1 = Res_FindByHandle(handle);
  if (pRVar1 != (Resource *)0x0) {
    return pRVar1->pData;
  }
  return (void *)0x0;
}

/* ---- 0x00481120  Res_FindByHandle ---- */
Resource * __cdecl Res_FindByHandle(void *handle)

{
  Resource *pRVar1;
  
  pRVar1 = g_pNewestResNode;
  while( true ) {
    if (pRVar1 == (Resource *)0x0) {
      return (Resource *)0x0;
    }
    if ((void *)pRVar1->nHandle == handle) break;
    pRVar1 = pRVar1->pNext;
  }
  return pRVar1;
}

/* ---- 0x00481140  Res_Loaded ---- */
/* Original name Res_Loaded (the remaster's GrimFandango (Linux): aligned call in
   sputLua_GetCurrentSetupL, sputLua_PutActorInSetL); was Res_Find. */

void * __cdecl Res_Loaded(int type,char *name)

{
  void *pvVar1;
  
  pvVar1 = Res_FindByName(type,name);
  return pvVar1;
}

/* ---- 0x00481160  Res_FindByName ---- */
/* Hashes the name and scans the resource list for a record of the same type and hash (skipping
   records with flag 2) */

void * __cdecl Res_FindByName(int type,char *name)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  Resource **ppRVar2;
  uint uVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  Resource *pRVar7;
  bool bVar8;
  #define local_104 (*(byte (*)[260])(_frame + (0x120 - 0x104)))
  
  uVar3 = Res_HashName(name,(char *)local_104);
  pRVar7 = g_pNewestResNode;
  if (g_pNewestResNode == (Resource *)0x0) {
    return (void *)0x0;
  }
  do {
    if (((pRVar7->dwType == type) && (pRVar7->dwHash == uVar3)) && ((pRVar7->bFlags & 2) == 0)) {
      pbVar4 = (byte *)pRVar7->pName;
      pbVar6 = local_104;
      do {
        bVar1 = *pbVar4;
        bVar8 = bVar1 < *pbVar6;
        if (bVar1 != *pbVar6) {
LAB_004811d0:
          iVar5 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_004811d5;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar4[1];
        bVar8 = bVar1 < pbVar6[1];
        if (bVar1 != pbVar6[1]) goto LAB_004811d0;
        pbVar4 = pbVar4 + 2;
        pbVar6 = pbVar6 + 2;
      } while (bVar1 != 0);
      iVar5 = 0;
LAB_004811d5:
      if (iVar5 == 0) {
        return pRVar7;
      }
    }
    ppRVar2 = &pRVar7->pNext;
    pRVar7 = *ppRVar2;
    if (*ppRVar2 == (Resource *)0x0) {
      return (void *)0x0;
    }
  } while( true );
}
#undef local_104


/* ---- 0x00481210  res_Load ---- */
/* Asks the type handler to load {op=1, name, type}; on status 1 finds the new record and asks the
   handler for its size {op=3} Original name res_Load (the remaster's GrimFandango (Linux): aligned
   call in Res_Load, Res_SysLoad); was Res_LoadInternal. */

void * __cdecl res_Load(int type,char *name,int *status)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined uVar1;
  void *pvVar2;
  ResType *pRVar3;
  undefined3 extraout_var;
  int iVar4;
  undefined *puVar5;
  #define uStack_28 (*(undefined4 *)(_frame + (0x40 - 0x28)))
  #define uStack_24 (*(undefined4 *)(_frame + (0x40 - 0x24)))
  #define uStack_20 (*(undefined4 *)(_frame + (0x40 - 0x20)))
  #define uStack_1c (*(undefined4 *)(_frame + (0x40 - 0x1c)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  
  pvVar2 = Res_FindByName(type,name);
  if (pvVar2 != (void *)0x0) {
    *status = 4;
    return pvVar2;
  }
  pRVar3 = ResType_Find(type);
  local_14 = 1;
  local_10 = (uint)name;
  local_c = type;
  sputRender_DrawLoadingImage();
  if (pRVar3 == (ResType *)0x0) {
    iVar4 = (*(code *)PTR_res_DefaultHandler_004e79ac)(&local_14);
    *status = iVar4;
  }
  else {
    uVar1 = (*pRVar3->pfnHandler)(&local_14);
    *status = ((uint)(byte)(uVar1));
  }
  if (g_dwRes_pPeriodicCallback != 0) {
    (*(code *)g_dwRes_pPeriodicCallback)();
  }
  puVar5 = (undefined *)0x0;
  if (*status == 1) {
    puVar5 = res_LocateResByName(type,(uint)name);
    if (puVar5 != (undefined *)0x0) {
      uStack_24 = *(undefined4 *)(puVar5 + 8);
      uStack_20 = *(undefined4 *)(puVar5 + 0x10);
      uStack_1c = *(undefined4 *)(puVar5 + 0x14);
      uStack_28 = 3;
      uStack_18 = 0;
      (*pRVar3->pfnHandler)(&uStack_28);
      *(undefined4 *)(puVar5 + 0x28) = uStack_18;
    }
  }
  return puVar5;
}
#undef local_10
#undef local_14
#undef local_c
#undef uStack_18
#undef uStack_1c
#undef uStack_20
#undef uStack_24
#undef uStack_28


/* ---- 0x00481300  res_LocateResByName ---- */
/* Original name res_LocateResByName (the remaster's GrimFandango (Linux): the lookup res_Load makes
   after a successful load in both builds (hash the name, walk from pNewestResNode for type and
   hash); the remaster inlined Res_FindByNameInList into it); was Res_FindByNameFrom. */

undefined * __cdecl res_LocateResByName(uint param_1,uint param_2)

{
  int *piVar1;
  
  piVar1 = Res_FindByNameInList(param_1,(char *)param_2,(int *)g_pNewestResNode);
  return (undefined *)piVar1;
}

/* ---- 0x00481320  Res_FindByNameInList ---- */
int * __cdecl Res_FindByNameInList(int param_1,char *name,int *newestResNode)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  #define local_104 (*(byte (*)[260])(_frame + (0x120 - 0x104)))
  
  uVar2 = Res_HashName(name,(char *)local_104);
  if (newestResNode == (int *)0x0) {
    return (int *)0x0;
  }
  do {
    if ((newestResNode[4] == param_1) && (newestResNode[3] == uVar2)) {
      pbVar3 = (byte *)newestResNode[2];
      pbVar5 = local_104;
      do {
        bVar1 = *pbVar3;
        bVar6 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_00481387:
          iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
          goto LAB_0048138c;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar6 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_00481387;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_0048138c:
      if (iVar4 == 0) {
        return newestResNode;
      }
    }
    newestResNode = (int *)*newestResNode;
    if (newestResNode == (int *)0x0) {
      return (int *)0x0;
    }
  } while( true );
}
#undef local_104


/* ---- 0x00481400  Res_CreateRecord ---- */
/* Allocates a 0x2c-byte record {next, prev, name, hash, type, data, handle, flags, lab, refs, size}
   from g_pResPool; the name is shared with the LAB directory when the recent-lookup ring knows it
    */

void * __cdecl Res_CreateRecord(int type,char *name,void *data)

{
  char cVar1;
  uint *puVar2;
  Resource *res;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  
  res = (Resource *)Memory_AllocFixed((int *)g_dwResNodePool);
  if (res != (Resource *)0x0) {
    res->dwType = type;
    res->pData = data;
    res->nHandle = (int)data;
    *(undefined2 *)&res->bFlags = 0;
    res->pRefs = (ResRef *)0x0;
    res->pName = (char *)0x0;
    res->pLab = (void *)0x0;
    iVar6 = 1;
    do {
      puVar2 = *(uint **)(&g_aFoundFiles + (g_dwLastFound - iVar6 & 0xf) * 4);
      if ((puVar2 != (uint *)0x0) && (iVar3 = _stricmp((byte *)name,(byte *)puVar2[1]), iVar3 == 0))
      {
        res->pName = (char *)puVar2[1];
        res->pLab = *(void **)(&g_aFoundFileNodes + (g_dwLastFound - iVar6 & 0xf) * 4);
        res->dwHash = *puVar2;
        break;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < 0x11);
    if (res->pName == (char *)0x0) {
      uVar5 = 0xffffffff;
      pcVar4 = name;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      pcVar4 = (char *)(**(code **)(g_dwResHS + 0x20))
                                 (~uVar5,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xaed);
      res->pName = pcVar4;
      uVar5 = Res_HashName(name,pcVar4);
      res->bFlags = res->bFlags | 4;
      res->dwHash = uVar5;
    }
    res->pNext = g_pNewestResNode;
    if (g_pNewestResNode != (Resource *)0x0) {
      g_pNewestResNode->pPrev = res;
    }
    res->pPrev = (Resource *)0x0;
    if (g_dwOldestResNode == 0) {
      g_dwOldestResNode = (uint)res;
    }
    g_pNewestResNode = res;
    Res_MoveToFront(res);
  }
  return res;
}

/* ---- 0x00481510  Res_CallUnload ---- */
/* Invalidates all ResRefs of the record and sends {op=2, name, type, data} to the type handler */

void __cdecl Res_CallUnload(Resource *res)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  ResRef *pRVar1;
  undefined uVar2;
  ResType *pRVar3;
  undefined3 extraout_var;
  int iVar4;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  iVar4 = 0;
  pRVar3 = ResType_Find(res->dwType);
  for (pRVar1 = res->pRefs; pRVar1 != (ResRef *)0x0; pRVar1 = pRVar1->pNext) {
    iVar4 = iVar4 + 1;
    if (pRVar1->nValid == 0) {
      (**(code **)(g_dwResHS + 0x18))
                (s_ref__valid____0_004e7ae0,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xb19);
    }
    pRVar1->nValid = 0;
  }
  if (pRVar3 != (ResType *)0x0) {
    local_10 = (uint)res->pName;
    local_c = res->dwType;
    local_8 = (uint)res->pData;
    local_14 = 2;
    uVar2 = (*pRVar3->pfnHandler)(&local_14);
    if ((((uint)(byte)(uVar2)) == 1) && (g_dwLogFile != 0)) {
      (**(code **)(g_dwResHS + 0x54))
                (g_dwLogFile,s_Resource____12s__freed___d_refer_004e7ab8,res->pName,iVar4);
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_8
#undef local_c


/* ---- 0x004815c0  Res_Unlink ---- */
int __cdecl Res_Unlink(Resource *res)

{
  if (res->pPrev != (Resource *)0x0) {
    res->pPrev->pNext = res->pNext;
  }
  if (res->pNext != (Resource *)0x0) {
    res->pNext->pPrev = res->pPrev;
  }
  if (g_pNewestResNode == res) {
    g_pNewestResNode = res->pNext;
  }
  if ((Resource *)g_dwOldestResNode == res) {
    g_dwOldestResNode = (uint)res->pPrev;
  }
  if ((res->bFlags & 4) != 0) {
    (**(code **)(g_dwResHS + 0x24))(res->pName);
  }
  Pool_Free(res);
  return 1;
}

/* ---- 0x00481ef0  Res_GetSize ---- */
int __cdecl Res_GetSize(Resource *res)

{
  if (res != (Resource *)0x0) {
    return res->nSize;
  }
  return 0;
}

/* ---- 0x00481f00  Res_MoveToFront ---- */
/* LRU touch: moves the record to the head of the resource list */

void __cdecl Res_MoveToFront(void *res)

{
  if (g_pNewestResNode != res) {
    if (*(undefined4 **)((int)res + 4) != (undefined4 *)0x0) {
      **(undefined4 **)((int)res + 4) = *(undefined4 *)res;
    }
    if (*(int *)res != 0) {
      *(undefined4 *)(*(int *)res + 4) = *(undefined4 *)((int)res + 4);
    }
    if ((void *)g_dwOldestResNode == res) {
      g_dwOldestResNode = *(uint *)((int)res + 4);
    }
    *(Resource **)res = g_pNewestResNode;
    g_pNewestResNode->pPrev = res;
    *(undefined4 *)((int)res + 4) = 0;
    g_pNewestResNode = res;
  }
  return;
}

/* ---- 0x00481f60  Res_HashName ---- */
/* Rotate-left/xor hash over the lower-cased name (seeded with the length); also writes the
   lower-cased name to outLower */

uint __cdecl Res_HashName(char *name,char *outLower)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  
  uVar3 = 0xffffffff;
  pcVar4 = name;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3 - 1;
  uVar3 = uVar3 | ((uVar3 * 0x100 | uVar3) << 8 | uVar3) << 8;
  iVar2 = toupper((int)*name);
  cVar1 = (char)iVar2;
  *outLower = cVar1;
  while (cVar1 != '\0') {
    outLower = outLower + 1;
    name = name + 1;
    uVar3 = (uVar3 * 2 | uVar3 >> 0x1f) ^ (int)(char)iVar2;
    iVar2 = toupper((int)*name);
    cVar1 = (char)iVar2;
    *outLower = cVar1;
  }
  return uVar3;
}

/* ---- 0x00482170  Res_GetFirstType ---- */
/* Original name Res_GetFirstType (the remaster's GrimFandango (Linux): aligned call in
   sputRoom_Save); was Res_FindByHandleOrNull. */

void __cdecl Res_GetFirstType(int *param_1,int *param_2,int param_3)

{
  Resource *pRVar1;
  
  pRVar1 = g_pNewestResNode;
  while( true ) {
    if (pRVar1 == (Resource *)0x0) {
      *param_2 = 0;
      *param_1 = 0;
      return;
    }
    if (pRVar1->dwType == param_3) break;
    pRVar1 = pRVar1->pNext;
  }
  *param_1 = (int)pRVar1->pNext;
  *param_2 = (int)pRVar1->pData;
  return;
}

/* ---- 0x004821b0  Res_GetNextType ---- */
/* Original name Res_GetNextType (the remaster's GrimFandango (Linux): aligned call in
   sputRoom_Save); was Res_NextInList. */

void __cdecl Res_GetNextType(int *param_1,int *param_2,int param_3)

{
  int *piVar1;
  
  piVar1 = (int *)*param_1;
  if (piVar1 == (int *)0x0) {
    *param_2 = 0;
    *param_1 = 0;
    return;
  }
  do {
    if (piVar1[4] == param_3) {
      *param_1 = *piVar1;
      *param_2 = piVar1[5];
      return;
    }
    piVar1 = (int *)*piVar1;
  } while (piVar1 != (int *)0x0);
  *param_2 = 0;
  *param_1 = 0;
  return;
}

/* ---- 0x00482200  Res_Touch ---- */
/* Moves the record owning the data pointer to the front of the LRU list Original name Res_Touch
   (the remaster's GrimFandango (Linux): aligned call in sputRoom_GetSetupBackground,
   sputRoom_GetSetupZBackground, sputRoom_LoadResources); was Res_TouchByData. */

void __cdecl Res_Touch(void *data)

{
  Resource *res;
  
  res = Res_FindByData(data);
  if (res != (Resource *)0x0) {
    Res_MoveToFront(res);
  }
  return;
}

/* ---- 0x004824f0  Res_CountChildren ---- */
int __cdecl Res_CountChildren(uint param_1,uint param_2)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  
  iVar3 = 0;
  puVar2 = res_LocateResByName(param_1,param_2);
  if (puVar2 != (undefined *)0x0) {
    for (iVar1 = *(int *)(puVar2 + 0x24); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x30)) {
      iVar3 = iVar3 + 1;
    }
  }
  return iVar3;
}

/* ---- 0x00482520  grimlib_SetCacheMax ---- */
/* Cache limit in megabytes (shifted left by 20) Original name grimlib_SetCacheMax (the remaster's
   GrimFandango (Linux): max_ram = MB << 20); was Res_SetCacheSizeMB. */

void __cdecl grimlib_SetCacheMax(int param_1)

{
  g_dwMax_ram = param_1 << 0x14;
  return;
}

/* ---- 0x0048e230  sputResource_ReportAllocations ---- */
/* Original name sputResource_ReportAllocations (the remaster's GrimFandango (Linux): strings:
   'Grim.res'); was Res_PrintReport. */

void __cdecl sputResource_ReportAllocations(void)

{
  Res_Dump(s_Grim_res_004e9c74,0);
  return;
}
