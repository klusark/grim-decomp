/* GRIMFANDANGO.EXE :: res.c
 * functions 0x00480000 .. 0x0048e230 (30 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00480000  Res_GetMemoryUsed ---- */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Total bytes held by loaded resources */

int Res_GetMemoryUsed(void)

{
  return UINT_00825e7c;
}

/* ---- 0x00480230  Res_Register ---- */
/* Called by type handlers after loading to create the resource record */

void * __cdecl Res_Register(int fourcc,char *name,void *data)

{
  undefined4 *puVar1;
  void *pvVar2;
  int iVar3;
  void *pvVar4;
  
  pvVar4 = (void *)0x0;
  pvVar2 = Res_FindByData(data);
  if (pvVar2 == (void *)0x0) {
    pvVar2 = Res_CreateRecord(fourcc,name,data);
    if (pvVar2 != (void *)0x0) {
      if (UINT_008a85e4 != 0) {
        puVar1 = (undefined4 *)(UINT_008a856c + 0x54);
        iVar3 = Res_GetSize(pvVar2);
        (*(code *)*puVar1)(UINT_008a85e4,s_Resource____12s__allocated___8ld_004e79f4,name,iVar3);
      }
      return (void *)0x1;
    }
  }
  else {
    pvVar4 = (void *)0x4;
  }
  return pvVar4;
}

/* ---- 0x004802b0  Res_GetFilePath ---- */
int __cdecl Res_GetFilePath(char *name,char *buf,int size)

{
  unsigned char _frame[0x330] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  #define local_31c (*(char (*)[260])(_frame + (0x330 - 0x31c)))
  #define local_218 (*(undefined1 (*)[277])(_frame + (0x330 - 0x218)))
  #define local_103 (*(undefined1 (*)[259])(_frame + (0x330 - 0x103)))
  
  iVar3 = 0;
  iVar4 = 0;
  uVar2 = Res_HashName(name,local_31c);
  for (piVar1 = PTR_008a85c4; piVar1 != (int *)0x0; piVar1 = (int *)*piVar1) {
    if (iVar4 != 0) goto LAB_0048030d;
    iVar4 = 0;
    if ((*(byte *)(piVar1 + 0x45) & 2) == 0) {
      iVar4 = LabDir_FindEntry(piVar1,0,local_31c,uVar2,local_218);
    }
  }
  if (iVar4 != 0) {
LAB_0048030d:
    pcVar5 = buf;
    for (uVar2 = (uint)size >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      pcVar5[0] = '\0';
      pcVar5[1] = '\0';
      pcVar5[2] = '\0';
      pcVar5[3] = '\0';
      pcVar5 = pcVar5 + 4;
    }
    for (uVar2 = size & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *pcVar5 = '\0';
      pcVar5 = pcVar5 + 1;
    }
    strncpy(buf,local_103,size + -1);
    iVar3 = 1;
  }
  return iVar3;
}
#undef local_103
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
  res = Res_LoadInternal(type,name,(int *)&name);
  if (res != (void *)0x0) {
    Res_MoveToFront(res);
    pvVar1 = *(void **)((int)res + 0x14);
  }
  return pvVar1;
}

/* ---- 0x00480560  Res_SetLocked ---- */
/* Locks (flag 8) a resource against Res_FreeUnreferenced; returns the previous unlocked state */

uint __cdecl Res_SetLocked(void *data,int unlock)

{
  ushort uVar1;
  void *pvVar2;
  uint uVar3;
  
  uVar3 = 0;
  pvVar2 = Res_FindByData(data);
  if (pvVar2 != (void *)0x0) {
    uVar1 = *(ushort *)((int)pvVar2 + 0x1c);
    uVar3 = ((byte)~(byte)uVar1 & 8) >> 3;
    if (unlock != 0) {
      *(ushort *)((int)pvVar2 + 0x1c) = uVar1 & 0xfff7;
      return uVar3;
    }
    *(ushort *)((int)pvVar2 + 0x1c) = uVar1 | 8;
  }
  return uVar3;
}

/* ---- 0x004805b0  Res_FreeUnreferenced ---- */
/* Walks the LRU list from the oldest end freeing unreferenced, unlocked resources until bytesWanted
   is reached; calls the yield hook every 5 items */

int __cdecl Res_FreeUnreferenced(uint bytesWanted,uint *bytesFreed)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  bool bVar2;
  void *res;
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
      pvVar1 = (void *)UINT_008a85d8;
      while (res = pvVar1, res != (void *)0x0) {
        if (bytesWanted <= *bytesFreed) goto LAB_0048065f;
        local_8 = local_8 + 1;
        if (((code *)UINT_008a85e8 != (code *)0x0) && ((int)local_8 % 5 == 0)) {
          (*(code *)UINT_008a85e8)();
        }
        pvVar1 = *(void **)((int)res + 4);
        if ((*(int *)((int)res + 0x24) == 0) && ((*(byte *)((int)res + 0x1c) & 8) == 0)) {
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


/* ---- 0x00480680  Res_WriteReport ---- */
/* Dumps 'Resource %12s size %7ld REFERENCED' lines for every loaded resource */

int __cdecl Res_WriteReport(char *filename,int type)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  undefined4 *puVar1;
  int *res;
  int fh;
  char *pcVar2;
  int iVar3;
  int iVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  iVar4 = 0;
  fh = ResFile_Open(filename,&DAT_004dd478);
  res = PTR_008a85d4;
  if (fh != 0) {
    for (; res != (int *)0x0; res = (int *)*res) {
      if ((type == 0) || (res[4] == type)) {
        pcVar2 = s_REFERENCED_004e7a80;
        if (res[9] == 0) {
          pcVar2 = &DAT_004f5a98;
        }
        puVar1 = (undefined4 *)(UINT_008a856c + 0x54);
        iVar3 = Res_GetSize(res);
        (*(code *)*puVar1)(fh,s_Resource___12s__size____7ld__s_004e7a5c,res[2],iVar3,pcVar2);
        iVar3 = Res_GetSize(res);
        iVar4 = iVar4 + iVar3;
        local_4 = local_4 + 1;
      }
    }
    (**(code **)(UINT_008a856c + 0x54))(fh,s_Total___d_items___d_bytes_004e7a40,local_4,iVar4);
    ResFile_Close(fh);
    return 1;
  }
  return 0;
}
#undef local_4


/* ---- 0x00480740  Res_OpenLog ---- */
int __cdecl Res_OpenLog(char *filename)

{
  if (filename != (char *)0x0) {
    UINT_008a85e4 = (**(code **)(UINT_008a856c + 0x30))(filename,&DAT_004dd478);
    return 1;
  }
  if (UINT_008a85e4 != 0) {
    (**(code **)(UINT_008a856c + 0x34))(UINT_008a85e4);
    UINT_008a85e4 = 0;
  }
  return 1;
}

/* ---- 0x00480790  Res_InstallFileServices ---- */
/* Temp/Res.c: keeps a copy of the raw file services in g_ResFileServices and replaces
   svc->fopen..fprintf with the ResFile_* versions so every open goes through the LAB archive system
    */

void __cdecl Res_InstallFileServices(GrimServices *svc)

{
  int iVar1;
  GrimServices *pGVar2;
  GrimServices *pGVar3;
  
  pGVar2 = svc;
  pGVar3 = &g_ResFileServices;
  for (iVar1 = 0x1c; iVar1 != 0; iVar1 = iVar1 + -1) {
    pGVar3->flVersion = pGVar2->flVersion;
    pGVar2 = (GrimServices *)&pGVar2->pPrintf;
    pGVar3 = (GrimServices *)&pGVar3->pPrintf;
  }
  UINT_008a8570 = (uint)&g_ResFileServices;
  svc->pFopen = ResFile_Open;
  svc->pFclose = ResFile_Close;
  svc->pFread = ResFile_Read;
  svc->pFgets = FUN_00480bb0;
  svc->pFwrite = FUN_00480ce0;
  svc->pFeof = FUN_00480d50;
  svc->pFtell = FUN_00480dc0;
  svc->pFseek = ResFile_Seek;
  svc->pFileSize = ResFile_Size;
  svc->pFprintf = ResFile_Printf;
  return;
}

/* ---- 0x00480800  Res_RestoreFileServices ---- */
void __cdecl Res_RestoreFileServices(GrimServices *svc)

{
  svc->pFopen = *(void **)(UINT_008a8570 + 0x30);
  svc->pFclose = *(void **)(UINT_008a8570 + 0x34);
  svc->pFread = *(void **)(UINT_008a8570 + 0x38);
  svc->pFgets = *(void **)(UINT_008a8570 + 0x3c);
  svc->pFwrite = *(void **)(UINT_008a8570 + 0x40);
  svc->pFeof = *(void **)(UINT_008a8570 + 0x44);
  svc->pFtell = *(void **)(UINT_008a8570 + 0x48);
  svc->pFseek = *(void **)(UINT_008a8570 + 0x4c);
  svc->pFileSize = *(void **)(UINT_008a8570 + 0x50);
  svc->pFprintf = *(void **)(UINT_008a8570 + 0x54);
  UINT_008a8570 = UINT_008a856c;
  return;
}

/* ---- 0x004810e0  Res_FindByData ---- */
void * __cdecl Res_FindByData(void *data)

{
  int *piVar1;
  
  piVar1 = PTR_008a85d4;
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return (void *)0x0;
    }
    if ((void *)piVar1[5] == data) break;
    piVar1 = (int *)*piVar1;
  }
  return piVar1;
}

/* ---- 0x00481100  Res_DataFromHandle ---- */
void * __cdecl Res_DataFromHandle(void *handle)

{
  void *pvVar1;
  
  pvVar1 = Res_FindByHandle(handle);
  if (pvVar1 != (void *)0x0) {
    return *(void **)((int)pvVar1 + 0x14);
  }
  return (void *)0x0;
}

/* ---- 0x00481120  Res_FindByHandle ---- */
void * __cdecl Res_FindByHandle(void *handle)

{
  int *piVar1;
  
  piVar1 = PTR_008a85d4;
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return (void *)0x0;
    }
    if ((void *)piVar1[6] == handle) break;
    piVar1 = (int *)*piVar1;
  }
  return piVar1;
}

/* ---- 0x00481140  Res_Find ---- */
void * __cdecl Res_Find(int type,char *name)

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
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  int *piVar6;
  bool bVar7;
  #define local_104 (*(byte (*)[260])(_frame + (0x120 - 0x104)))
  
  uVar2 = Res_HashName(name,(char *)local_104);
  piVar6 = PTR_008a85d4;
  if (PTR_008a85d4 == (int *)0x0) {
    return (void *)0x0;
  }
  do {
    if (((piVar6[4] == type) && (piVar6[3] == uVar2)) && ((*(byte *)(piVar6 + 7) & 2) == 0)) {
      pbVar3 = (byte *)piVar6[2];
      pbVar5 = local_104;
      do {
        bVar1 = *pbVar3;
        bVar7 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_004811d0:
          iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_004811d5;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar7 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_004811d0;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_004811d5:
      if (iVar4 == 0) {
        return piVar6;
      }
    }
    piVar6 = (int *)*piVar6;
    if (piVar6 == (int *)0x0) {
      return (void *)0x0;
    }
  } while( true );
}
#undef local_104


/* ---- 0x00481210  Res_LoadInternal ---- */
/* Asks the type handler to load {op=1, name, type}; on status 1 finds the new record and asks the
   handler for its size {op=3} */

void * __cdecl Res_LoadInternal(int type,char *name,int *status)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  void *pvVar1;
  int iVar2;
  undefined *puVar3;
  #define uStack_28 (*(undefined4 *)(_frame + (0x40 - 0x28)))
  #define uStack_24 (*(undefined4 *)(_frame + (0x40 - 0x24)))
  #define uStack_20 (*(undefined4 *)(_frame + (0x40 - 0x20)))
  #define uStack_1c (*(undefined4 *)(_frame + (0x40 - 0x1c)))
  #define uStack_18 (*(undefined4 *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  
  pvVar1 = Res_FindByName(type,name);
  if (pvVar1 != (void *)0x0) {
    *status = 4;
    return pvVar1;
  }
  pvVar1 = ResType_Find(type);
  local_14 = 1;
  local_10 = (uint)name;
  local_c = type;
  Render_UpdateWaitCursor();
  if (pvVar1 == (void *)0x0) {
    iVar2 = (*(code *)PTR_ResType_DefaultHandler_004e79ac)(&local_14);
    *status = iVar2;
  }
  else {
    iVar2 = (**(code **)((int)pvVar1 + 0xc))(&local_14);
    *status = iVar2;
  }
  if (UINT_008a85e8 != 0) {
    (*(code *)UINT_008a85e8)();
  }
  puVar3 = (undefined *)0x0;
  if (*status == 1) {
    puVar3 = Res_FindByNameFrom(type,(uint)name);
    if (puVar3 != (undefined *)0x0) {
      uStack_24 = *(undefined4 *)(puVar3 + 8);
      uStack_20 = *(undefined4 *)(puVar3 + 0x10);
      uStack_1c = *(undefined4 *)(puVar3 + 0x14);
      uStack_28 = 3;
      uStack_18 = 0;
      (**(code **)((int)pvVar1 + 0xc))(&uStack_28);
      *(undefined4 *)(puVar3 + 0x28) = uStack_18;
    }
  }
  return puVar3;
}
#undef local_10
#undef local_14
#undef local_c
#undef uStack_18
#undef uStack_1c
#undef uStack_20
#undef uStack_24
#undef uStack_28


/* ---- 0x00481300  Res_FindByNameFrom ---- */
undefined * __cdecl Res_FindByNameFrom(uint param_1,uint param_2)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)Res_FindByNameInList(param_1,param_2,PTR_008a85d4);
  return puVar1;
}

/* ---- 0x00481320  Res_FindByNameInList ---- */
int * Res_FindByNameInList(int param_1,char *param_2,int *param_3)

{
  unsigned char _frame[0x120] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  #define local_104 (*(byte (*)[260])(_frame + (0x120 - 0x104)))
  
  uVar2 = Res_HashName(param_2,(char *)local_104);
  if (param_3 == (int *)0x0) {
    return (int *)0x0;
  }
  do {
    if ((param_3[4] == param_1) && (param_3[3] == uVar2)) {
      pbVar3 = (byte *)param_3[2];
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
        return param_3;
      }
    }
    param_3 = (int *)*param_3;
    if (param_3 == (int *)0x0) {
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
  int *piVar2;
  int *res;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  
  res = (int *)Pool_Alloc(UINT_008a85d0);
  if (res != (int *)0x0) {
    res[4] = type;
    res[5] = (int)data;
    res[6] = (int)data;
    *(undefined2 *)(res + 7) = 0;
    res[9] = 0;
    res[2] = 0;
    res[8] = 0;
    iVar6 = 1;
    do {
      piVar2 = *(int **)(&DAT_00825f00 + (UINT_008a85e0 - iVar6 & 0xf) * 4);
      if ((piVar2 != (int *)0x0) && (iVar3 = _stricmp(name,piVar2[1]), iVar3 == 0)) {
        res[2] = piVar2[1];
        res[8] = *(int *)(&DAT_008a8578 + (UINT_008a85e0 - iVar6 & 0xf) * 4);
        res[3] = *piVar2;
        break;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < 0x11);
    if (res[2] == 0) {
      uVar5 = 0xffffffff;
      pcVar4 = name;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      pcVar4 = (char *)(**(code **)(UINT_008a856c + 0x20))
                                 (~uVar5,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xaed);
      res[2] = (int)pcVar4;
      uVar5 = Res_HashName(name,pcVar4);
      *(byte *)(res + 7) = *(byte *)(res + 7) | 4;
      res[3] = uVar5;
    }
    *res = (int)PTR_008a85d4;
    if (PTR_008a85d4 != (int *)0x0) {
      PTR_008a85d4[1] = (int)res;
    }
    res[1] = 0;
    if (UINT_008a85d8 == 0) {
      UINT_008a85d8 = (uint)res;
    }
    PTR_008a85d4 = res;
    Res_MoveToFront(res);
  }
  return res;
}

/* ---- 0x00481510  Res_CallUnload ---- */
/* Invalidates all ResRefs of the record and sends {op=2, name, type, data} to the type handler */

void __cdecl Res_CallUnload(void *res)

{
  unsigned char _frame[0x30] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int *piVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  #define local_14 (*(uint *)(_frame + (0x30 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x30 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x30 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x30 - 0x8)))
  
  iVar4 = 0;
  pvVar2 = ResType_Find(*(int *)((int)res + 0x10));
  for (piVar1 = *(int **)((int)res + 0x24); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[0xc]) {
    iVar4 = iVar4 + 1;
    if (*piVar1 == 0) {
      (**(code **)(UINT_008a856c + 0x18))
                (s_ref__valid____0_004e7ae0,s_C__grimsrc_libs_grimlib_Temp_Res_004e7a1c,0xb19);
    }
    *piVar1 = 0;
  }
  if (pvVar2 != (void *)0x0) {
    local_10 = *(uint *)((int)res + 8);
    local_c = *(uint *)((int)res + 0x10);
    local_8 = *(uint *)((int)res + 0x14);
    local_14 = 2;
    iVar3 = (**(code **)((int)pvVar2 + 0xc))(&local_14);
    if ((iVar3 == 1) && (UINT_008a85e4 != 0)) {
      (**(code **)(UINT_008a856c + 0x54))
                (UINT_008a85e4,s_Resource____12s__freed___d_refer_004e7ab8,
                 *(undefined4 *)((int)res + 8),iVar4);
    }
  }
  return;
}
#undef local_10
#undef local_14
#undef local_8
#undef local_c


/* ---- 0x004815c0  Res_Unlink ---- */
int __cdecl Res_Unlink(void *res)

{
  if (*(undefined4 **)((int)res + 4) != (undefined4 *)0x0) {
    **(undefined4 **)((int)res + 4) = *(undefined4 *)res;
  }
  if (*(int *)res != 0) {
    *(undefined4 *)(*(int *)res + 4) = *(undefined4 *)((int)res + 4);
  }
  if (PTR_008a85d4 == res) {
    PTR_008a85d4 = *(int **)res;
  }
  if ((void *)UINT_008a85d8 == res) {
    UINT_008a85d8 = *(uint *)((int)res + 4);
  }
  if ((*(byte *)((int)res + 0x1c) & 4) != 0) {
    (**(code **)(UINT_008a856c + 0x24))(*(undefined4 *)((int)res + 8));
  }
  Pool_Free(res);
  return 1;
}

/* ---- 0x00481ef0  Res_GetSize ---- */
int __cdecl Res_GetSize(void *res)

{
  if (res != (void *)0x0) {
    return *(int *)((int)res + 0x28);
  }
  return 0;
}

/* ---- 0x00481f00  Res_MoveToFront ---- */
/* LRU touch: moves the record to the head of the resource list */

void __cdecl Res_MoveToFront(void *res)

{
  if (PTR_008a85d4 != res) {
    if (*(undefined4 **)((int)res + 4) != (undefined4 *)0x0) {
      **(undefined4 **)((int)res + 4) = *(undefined4 *)res;
    }
    if (*(int *)res != 0) {
      *(undefined4 *)(*(int *)res + 4) = *(undefined4 *)((int)res + 4);
    }
    if ((void *)UINT_008a85d8 == res) {
      UINT_008a85d8 = *(uint *)((int)res + 4);
    }
    *(int **)res = PTR_008a85d4;
    PTR_008a85d4[1] = (int)res;
    *(undefined4 *)((int)res + 4) = 0;
    PTR_008a85d4 = res;
  }
  return;
}

/* ---- 0x00481f60  Res_HashName ---- */
/* Rotate-left/xor hash over the lower-cased name (seeded with the length); also writes the
   lower-cased name to outLower */

uint __cdecl Res_HashName(char *name,char *outLower)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  uVar2 = 0xffffffff;
  pcVar3 = name;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2 - 1;
  uVar2 = uVar2 | ((uVar2 * 0x100 | uVar2) << 8 | uVar2) << 8;
  cVar1 = toupper((int)*name);
  *outLower = cVar1;
  while (cVar1 != '\0') {
    outLower = outLower + 1;
    name = name + 1;
    uVar2 = (uVar2 * 2 | uVar2 >> 0x1f) ^ (int)cVar1;
    cVar1 = toupper((int)*name);
    *outLower = cVar1;
  }
  return uVar2;
}

/* ---- 0x00482170  Res_FindByHandleOrNull ---- */
void Res_FindByHandleOrNull(int *param_1,int *param_2,int param_3)

{
  int *piVar1;
  
  piVar1 = PTR_008a85d4;
  while( true ) {
    if (piVar1 == (int *)0x0) {
      *param_2 = 0;
      *param_1 = 0;
      return;
    }
    if (piVar1[4] == param_3) break;
    piVar1 = (int *)*piVar1;
  }
  *param_1 = *piVar1;
  *param_2 = piVar1[5];
  return;
}

/* ---- 0x004821b0  Res_NextInList ---- */
void Res_NextInList(int *param_1,int *param_2,int param_3)

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

/* ---- 0x00482200  Res_TouchByData ---- */
/* Moves the record owning the data pointer to the front of the LRU list */

undefined * __cdecl Res_TouchByData(void *param_1)

{
  void *res;
  undefined *extraout_EAX;
  undefined *puVar1;
  
  res = Res_FindByData(param_1);
  puVar1 = (undefined *)0x0;
  if (res != (void *)0x0) {
    Res_MoveToFront(res);
    puVar1 = extraout_EAX;
  }
  return puVar1;
}

/* ---- 0x004824f0  Res_CountChildren ---- */
int Res_CountChildren(uint param_1,uint param_2)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  
  iVar3 = 0;
  puVar2 = Res_FindByNameFrom(param_1,param_2);
  if (puVar2 != (undefined *)0x0) {
    for (iVar1 = *(int *)(puVar2 + 0x24); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x30)) {
      iVar3 = iVar3 + 1;
    }
  }
  return iVar3;
}

/* ---- 0x00482520  Res_SetCacheSizeMB ---- */
/* Cache limit in megabytes (shifted left by 20) */

void Res_SetCacheSizeMB(int param_1)

{
  UINT_004e7b20 = param_1 << 0x14;
  return;
}

/* ---- 0x0048e230  Res_PrintReport ---- */
void Res_PrintReport(void)

{
  Res_WriteReport(s_Grim_res_004e9c74,0);
  return;
}
