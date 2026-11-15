/* GRIMFANDANGO.EXE :: restype.c
 * functions 0x004801a0 .. 0x0048e1e0 (14 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004801a0  Res_SysRegisterHandler ---- */
/* Original name Res_SysRegisterHandler (the remaster's GrimFandango (Linux): the one-handler
   registration that sputResource_Startup loops over (inlined there), body similarity); was
   ResType_Register. */

int __cdecl Res_SysRegisterHandler(int fourcc,void *handler)

{
  ResType *pRVar1;
  
  if (fourcc == 0x44454648) {
    PTR_res_DefaultHandler_004e79ac = handler;
    return 1;
  }
  pRVar1 = g_dwResTypeList;
  if (g_dwResTypeList != (ResType *)0x0) {
    do {
      if (pRVar1->dwType == fourcc) break;
      pRVar1 = pRVar1->pNext;
    } while (pRVar1 != (ResType *)0x0);
    if (pRVar1 != (ResType *)0x0) {
      return 2;
    }
  }
  pRVar1 = (ResType *)Memory_AllocFixed((int *)g_dwResTypePool);
  if (pRVar1 == (ResType *)0x0) {
    return 3;
  }
  pRVar1->dwType = fourcc;
  pRVar1->pfnHandler = handler;
  pRVar1->pNext = g_dwResTypeList;
  if (g_dwResTypeList != (ResType *)0x0) {
    g_dwResTypeList->pPrev = pRVar1;
  }
  pRVar1->pPrev = (ResType *)0x0;
  g_dwResTypeList = pRVar1;
  return 1;
}

/* ---- 0x00481050  ResType_Find ---- */
/* Finds the handler record {next, ?, fourcc, handlerFn} registered for a resource type */

ResType * __cdecl ResType_Find(int fourcc)

{
  ResType *pRVar1;
  
  pRVar1 = g_dwResTypeList;
  while( true ) {
    if (pRVar1 == (ResType *)0x0) {
      return (ResType *)0x0;
    }
    if (pRVar1->dwType == fourcc) break;
    pRVar1 = pRVar1->pNext;
  }
  return pRVar1;
}

/* ---- 0x00481e10  res_DefaultHandler ---- */
/* Handler for plain file resources: op 1 opens the file and reads it into a handle allocation
   (hAlloc/hLock), op 2 frees it Original name res_DefaultHandler (the remaster's GrimFandango
   (Linux): same body (message 1: open, size, alloc, read and Res_SysAddHandle a non-'RESF' file;
   message 2: free the handle); res_Load's handler when no type matches in both builds); was
   ResType_DefaultHandler. */

int __cdecl res_DefaultHandler(ResMsg *msg)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int fh;
  uint n;
  void *data;
  void *buf;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  if (msg->nOp == 1) {
    if (msg->dwType != 0x52455346) {
      fh = Res_FOpen(msg->pName,&DAT_004ddb18);
      if (fh != 0) {
        n = Res_FSize(msg->pName);
        data = (void *)(**(code **)(g_dwResHS + 0x5c))(n);
        if (data != (void *)0x0) {
          buf = (void *)(**(code **)(g_dwResHS + 0x68))(data);
          Res_FRead(fh,buf,n);
          (**(code **)(g_dwResHS + 0x6c))(data);
          Res_SysAddHandle(msg->dwType,msg->pName,data);
        }
        local_4 = (uint)(data != (void *)0x0);
        Res_FClose(fh);
        return local_4;
      }
      local_4 = 4;
    }
  }
  else if (msg->nOp == 2) {
    (**(code **)(g_dwResHS + 0x60))(msg->pData);
    return 0;
  }
  return local_4;
}
#undef local_4


/* ---- 0x0048d8c0  sputResource_LipSyncHandler ---- */
/* Resource type handler for 'SYNC' (entry of g_ResTypeTable): op 1 loads, op 2 frees, op 3 reports
   the size. Load = grimSound_LipSyncLoad. Original name sputResource_LipSyncHandler (the remaster's
   GrimFandango (Linux): the 'SYNC' entry of the resource type table (g_ResTypeTable /
   TypesToRegister)); was ResType_LipSyncHandler. */

void * __cdecl sputResource_LipSyncHandler(int *param_1)

{
  int iVar1;
  uint *data;
  void *pvVar2;
  
  if (param_1[2] == 0x53594e43) {
    iVar1 = *param_1;
    if (iVar1 == 1) {
      data = grimSound_LipSyncLoad((uint *)param_1[1]);
      if (data != (uint *)0x0) {
        pvVar2 = Res_SysAddHandle(param_1[2],(char *)param_1[1],data);
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

/* ---- 0x0048d930  sputResource_BackgroundHandler ---- */
/* BKND handler: op 1 loads the .bm with stdBitmap and remaps 16-bit frames to the display, op 2
   frees it, op 3 reports its size Original name sputResource_BackgroundHandler (the remaster's
   GrimFandango (Linux): the 'BKND' entry of the resource type table (g_ResTypeTable /
   TypesToRegister)); was ResType_BitmapHandler. */

int __cdecl sputResource_BackgroundHandler(ResMsg *msg)

{
  VBuffer *surface;
  int iVar1;
  stdBitmap *data;
  void *pvVar2;
  int iVar3;
  
  if (msg->dwType != 0x444e4b42) {
    return 0;
  }
  iVar1 = msg->nOp;
  if (iVar1 == 1) {
    data = stdLoadImageData(msg->pName,0,0);
    if (data != (stdBitmap *)0x0) {
      if ((((data->nType != 3) && (data->nType == 0)) && ((data->colorFormat).nColorMode == 1)) &&
         (iVar1 = 0, 0 < data->nFrames)) {
        do {
          surface = data->ppFrames[iVar1];
          stdDisplay_VBufferLock(surface);
          iVar3 = 0;
          if (0 < (surface->format).nHeight) {
            do {
              sputRender_ColorCorrect
                        ((ushort *)(iVar3 * (surface->format).nPitch + (int)surface->pPixels),
                         (surface->format).nWidth);
              iVar3 = iVar3 + 1;
            } while (iVar3 < (surface->format).nHeight);
          }
          stdDisplay_VBufferUnlock(surface);
          surface->dwColorKey = 0xf81f;
          sputRender_ColorCorrect((ushort *)&surface->dwColorKey,1);
          iVar1 = iVar1 + 1;
        } while (iVar1 < data->nFrames);
      }
      pvVar2 = Res_SysAddHandle(msg->dwType,msg->pName,data);
      return (int)pvVar2;
    }
  }
  else {
    if (iVar1 == 2) {
      stdBitmap_Free(msg->pData);
      return 1;
    }
    if (iVar1 == 3) {
      iVar1 = stdBitmap_MemUsage(msg->pData);
      msg->nSize = iVar1;
      return 1;
    }
  }
  return 0;
}

/* ---- 0x0048da40  sputResource_CostumeHandler ---- */
/* COST handler: Cos_Load / Cos_Free Original name sputResource_CostumeHandler (the remaster's
   GrimFandango (Linux): the 'COST' entry of the resource type table (g_ResTypeTable /
   TypesToRegister)); was ResType_CostumeHandler. */

int __cdecl sputResource_CostumeHandler(ResMsg *msg)

{
  int iVar1;
  void *pvVar2;
  
  pvVar2 = (void *)0x0;
  if (msg->dwType != 0x54534f43) {
    return (int)pvVar2;
  }
  iVar1 = msg->nOp;
  if (iVar1 == 1) {
    pvVar2 = (void *)Cos_Load((int)msg->pName);
    if (pvVar2 == (void *)0x0) {
      return 0;
    }
    pvVar2 = Res_SysAddHandle(msg->dwType,msg->pName,pvVar2);
  }
  else {
    if (iVar1 == 2) {
      Cos_Free((int)msg->pData);
      return 1;
    }
    if (iVar1 == 3) {
      msg->nSize = 1;
      return 1;
    }
  }
  return (int)pvVar2;
}

/* ---- 0x0048dab0  sputResource_ColormapHandler ---- */
/* Resource type handler for 'CMAP' (entry of g_ResTypeTable): op 1 loads, op 2 frees, op 3 reports
   the size. Load = rdColormap_Load + 16-bit tables + pixel remap. Original name
   sputResource_ColormapHandler (the remaster's GrimFandango (Linux): the only unmatched caller of
   rdColormap_Free; 2 matched neighbours agree, 0 disagree); was ResType_ColormapHandler. */

void * __cdecl sputResource_ColormapHandler(int *param_1)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  rdColormap *data;
  void *pvVar2;
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
  if (param_1[2] != 0x50414d43) {
    return (void *)0x0;
  }
  iVar1 = *param_1;
  if (iVar1 == 1) {
    data = rdColormap_Load((char *)param_1[1]);
    if (data != (rdColormap *)0x0) {
      rdColormap_BuildRGB16(data->pRGB16,(ushort *)data->aPalette,0,0,0,(int)&local_38);
      sputRender_ColorCorrect(data->pRGB16,0x4000);
      pvVar2 = Res_SysAddHandle(param_1[2],(char *)param_1[1],data);
      return pvVar2;
    }
  }
  else {
    if (iVar1 == 2) {
      rdColormap_Free(param_1[3]);
      return (void *)0x1;
    }
    if (iVar1 == 3) {
      iVar1 = rdColormap_Size(param_1[3]);
      param_1[4] = iVar1;
      return (void *)0x1;
    }
  }
  return (void *)0x0;
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
#undef local_4
#undef local_8
#undef local_c


/* ---- 0x0048dbd0  sputResource_FontHandler ---- */
/* Resource type handler for 'FONT' (entry of g_ResTypeTable): op 1 loads, op 2 frees, op 3 reports
   the size. Load = Font_LoadFile, kept locked. Original name sputResource_FontHandler (the
   remaster's GrimFandango (Linux): the 'FONT' entry of the resource type table (g_ResTypeTable /
   TypesToRegister)); was ResType_FontHandler. */

void * __cdecl sputResource_FontHandler(int *param_1)

{
  int *piVar1;
  int iVar2;
  void *pvVar3;
  
  piVar1 = param_1;
  if (param_1[2] != 0x544e4f46) {
    return (void *)0x0;
  }
  iVar2 = *param_1;
  if (iVar2 == 1) {
    iVar2 = Text_LoadNativeFont((char *)param_1[1],&param_1);
    if (iVar2 == 0) {
      pvVar3 = Res_SysAddHandle(piVar1[2],(char *)piVar1[1],param_1);
      Res_SetPurgable(param_1,0);
      return pvVar3;
    }
  }
  else {
    if (iVar2 == 2) {
      Text_FreeFont((void *)param_1[3]);
      return (void *)0x1;
    }
    if (iVar2 == 3) {
      param_1[4] = 1;
      return (void *)0x1;
    }
  }
  return (void *)0x0;
}

/* ---- 0x0048dc60  sputResource_KeyframeHandler ---- */
/* Resource type handler for 'KEYF' (entry of g_ResTypeTable): op 1 loads, op 2 frees, op 3 reports
   the size. Load = rdKeyframe_Load (default 15 fps). Original name sputResource_KeyframeHandler
   (the remaster's GrimFandango (Linux): the only unmatched caller of rdKeyframe_Free; the only
   unmatched caller of rdKeyframe_Load; 2 matched neighbours agree, 0 disagree); was
   ResType_KeyframeHandler. */

void * __cdecl sputResource_KeyframeHandler(ResMsg *msg)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  
  if (msg->dwType != 0x4659454b) {
    return (void *)0x0;
  }
  iVar3 = msg->nOp;
  if (iVar3 == 1) {
    pvVar2 = (void *)rdKeyframe_Load(msg->pName);
    if (pvVar2 == (void *)0x0) {
      return (void *)0x0;
    }
    *(undefined4 *)((int)pvVar2 + 0x30) = 0x41700000;
    pvVar2 = Res_SysAddHandle(msg->dwType,msg->pName,pvVar2);
    return pvVar2;
  }
  if (iVar3 == 2) {
    rdKeyframe_Free((int)msg->pData);
  }
  else {
    if (iVar3 != 3) {
      return (void *)0x0;
    }
    pvVar2 = msg->pData;
    msg->nSize = 0x84;
    iVar3 = 0;
    if (0 < *(int *)((int)pvVar2 + 0x38)) {
      iVar4 = 0;
      do {
        iVar4 = iVar4 + 0x2c;
        iVar1 = msg->nSize + 0x2c;
        msg->nSize = iVar1;
        iVar3 = iVar3 + 1;
        msg->nSize = iVar1 + *(int *)(*(int *)((int)pvVar2 + 0x3c) + -8 + iVar4) * 0x38;
      } while (iVar3 < *(int *)((int)pvVar2 + 0x38));
      return (void *)0x1;
    }
  }
  return (void *)0x1;
}

/* ---- 0x0048dd20  sputResource_MaterialHandler ---- */
/* Resource type handler for 'MAT ' (entry of g_ResTypeTable): op 1 loads, op 2 frees, op 3 reports
   the size. Load = rdMaterial_LoadFile, falls back to dflt.mat. Original name
   sputResource_MaterialHandler (the remaster's GrimFandango (Linux): strings: 'dflt.mat'); was
   ResType_MaterialHandler. */

void * __cdecl sputResource_MaterialHandler(int *param_1)

{
  rdMaterial *material;
  int iVar1;
  void *pvVar2;
  
  pvVar2 = (void *)0x0;
  if (param_1[2] != 0x2054414d) {
    return (void *)0x0;
  }
  iVar1 = *param_1;
  if (iVar1 == 1) {
    material = (rdMaterial *)
               (**(code **)(g_dwSputResHS + 0x20))
                         (0xb0,s_C__grimsrc_libs_grimlib_Main_spu_004e9c30,0x49f);
    iVar1 = rdMaterial_LoadEntry((char *)param_1[1],material,0,0);
    if (iVar1 == 0) {
      iVar1 = rdMaterial_LoadEntry(s_dflt_mat_004e9c68,material,0,0);
      if (iVar1 == 0) {
        rdMaterial_FreeEntry((int)material);
        (**(code **)(g_dwSputResHS + 0x24))(material);
        return (void *)0x0;
      }
    }
    pvVar2 = Res_SysAddHandle(param_1[2],(char *)param_1[1],material);
    Res_SetPurgable(material,0);
  }
  else {
    if (iVar1 == 2) {
      rdMaterial_FreeEntry(param_1[3]);
      (**(code **)(g_dwSputResHS + 0x24))(param_1[3]);
      return (void *)0x1;
    }
    if (iVar1 == 3) {
      param_1[4] = 0;
      return (void *)0x1;
    }
  }
  return pvVar2;
}

/* ---- 0x0048de10  sputResource_ModelHandler ---- */
/* Resource type handler for 'MODL' (entry of g_ResTypeTable): op 1 loads, op 2 frees, op 3 reports
   the size. Load = rdModel3_New (.3do). Original name sputResource_ModelHandler (the remaster's
   GrimFandango (Linux): the 'MODL' entry of the resource type table (g_ResTypeTable /
   TypesToRegister)); was ResType_ModelHandler. */

void * __cdecl sputResource_ModelHandler(int *param_1)

{
  int iVar1;
  undefined4 *data;
  void *pvVar2;
  
  if (param_1[2] == 0x4c444f4d) {
    iVar1 = *param_1;
    if (iVar1 == 1) {
      data = rdModel3_Load(param_1[1]);
      if (data != (undefined4 *)0x0) {
        pvVar2 = Res_SysAddHandle(param_1[2],(char *)param_1[1],data);
        return pvVar2;
      }
    }
    else {
      if (iVar1 == 2) {
        rdModel3_Free(param_1[3]);
        return (void *)0x1;
      }
      if (iVar1 == 3) {
        param_1[4] = 1;
        return (void *)0x1;
      }
    }
  }
  return (void *)0x0;
}

/* ---- 0x0048de70  sputResource_SetHandler ---- */
/* Resource type handler for 'SET ' (entry of g_ResTypeTable): op 1 loads, op 2 frees, op 3 reports
   the size. Load = Set_LoadFile. Original name sputResource_SetHandler (the remaster's GrimFandango
   (Linux): the 'SET ' entry of the resource type table (g_ResTypeTable / TypesToRegister)); was
   ResType_SetHandler. */

void * __cdecl sputResource_SetHandler(int *param_1)

{
  int iVar1;
  Set *data;
  void *pvVar2;
  
  if (param_1[2] == 0x20544553) {
    iVar1 = *param_1;
    if (iVar1 == 1) {
      data = sputRoom_LoadRoom((char *)param_1[1]);
      if (data != (Set *)0x0) {
        pvVar2 = Res_SysAddHandle(param_1[2],(char *)param_1[1],data);
        return pvVar2;
      }
    }
    else {
      if (iVar1 == 2) {
        sputRoom_FreeRoom(param_1[3]);
        return (void *)0x1;
      }
      if (iVar1 == 3) {
        param_1[4] = *(int *)(param_1[3] + 0x1af4);
        return (void *)0x1;
      }
    }
  }
  return (void *)0x0;
}

/* ---- 0x0048dee0  sputResource_ZBufferHandler ---- */
/* Resource type handler for 'ZBUF' (entry of g_ResTypeTable): op 1 loads, op 2 frees, op 3 reports
   the size. Load = ZBuffer_Load (z-buffer bitmap). Original name sputResource_ZBufferHandler (the
   remaster's GrimFandango (Linux): the 'ZBUF' entry of the resource type table (g_ResTypeTable /
   TypesToRegister)); was ResType_ZBufferHandler. */

void * __cdecl sputResource_ZBufferHandler(int *param_1)

{
  int iVar1;
  void *pvVar2;
  
  if (param_1[2] == 0x4655425a) {
    iVar1 = *param_1;
    if (iVar1 == 1) {
      pvVar2 = (void *)sputRoom_LoadZBuffer(param_1[1]);
      if (pvVar2 != (void *)0x0) {
        pvVar2 = Res_SysAddHandle(param_1[2],(char *)param_1[1],pvVar2);
        return pvVar2;
      }
    }
    else {
      if (iVar1 == 2) {
        sputRoom_FreeZBuffer(param_1[3]);
        return (void *)0x1;
      }
      if (iVar1 == 3) {
        param_1[4] = *(int *)(param_1[3] + 0x14);
        return (void *)0x1;
      }
    }
  }
  return (void *)0x0;
}

/* ---- 0x0048e1e0  sputResource_MemoryHandler ---- */
/* Resource type handler for 'MEM ' (entry of g_ResTypeTable): op 1 loads, op 2 frees, op 3 reports
   the size. Plain memory block: free releases the block and its data. Original name
   sputResource_MemoryHandler (the remaster's GrimFandango (Linux): the 'MEM ' entry of the resource
   type table (g_ResTypeTable / TypesToRegister)); was ResType_MemoryHandler. */

uint __cdecl sputResource_MemoryHandler(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = *param_1;
  if (iVar1 != 1) {
    if (iVar1 == 2) {
      puVar2 = (undefined4 *)param_1[3];
      (**(code **)(g_dwSputResHS + 0x24))(*puVar2);
      (**(code **)(g_dwSputResHS + 0x24))(puVar2);
    }
    else if (iVar1 == 3) {
      param_1[4] = *(int *)(param_1[3] + 4);
      return 1;
    }
  }
  return 1;
}
