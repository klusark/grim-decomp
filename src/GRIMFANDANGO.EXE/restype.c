/* GRIMFANDANGO.EXE :: restype.c
 * functions 0x004801a0 .. 0x0048dee0 (12 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x004801a0  ResType_Register ---- */
int __cdecl ResType_Register(int fourcc,void *handler)

{
  int *piVar1;
  uint *puVar2;
  
  if (fourcc == 0x44454648) {
    PTR_ResType_DefaultHandler_004e79ac = handler;
    return 1;
  }
  piVar1 = (int *)UINT_008a85cc;
  if (UINT_008a85cc != 0) {
    do {
      if (piVar1[2] == fourcc) break;
      piVar1 = (int *)*piVar1;
    } while (piVar1 != (int *)0x0);
    if (piVar1 != (int *)0x0) {
      return 2;
    }
  }
  puVar2 = (uint *)Pool_Alloc(UINT_008a85c8);
  if (puVar2 == (uint *)0x0) {
    return 3;
  }
  puVar2[2] = fourcc;
  puVar2[3] = (uint)handler;
  *puVar2 = UINT_008a85cc;
  if (UINT_008a85cc != 0) {
    *(uint **)(UINT_008a85cc + 4) = puVar2;
  }
  puVar2[1] = 0;
  UINT_008a85cc = (uint)puVar2;
  return 1;
}

/* ---- 0x00481050  ResType_Find ---- */
/* Finds the handler record {next, ?, fourcc, handlerFn} registered for a resource type */

void * __cdecl ResType_Find(int fourcc)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)UINT_008a85cc;
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return (void *)0x0;
    }
    if (puVar1[2] == fourcc) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}

/* ---- 0x00481e10  ResType_DefaultHandler ---- */
/* Handler for plain file resources: op 1 opens the file and reads it into a handle allocation
   (hAlloc/hLock), op 2 frees it */

int __cdecl ResType_DefaultHandler(void *msg)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int fh;
  uint n;
  void *data;
  void *buf;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  local_4 = 0;
  if (*(int *)msg == 1) {
    if (*(int *)((int)msg + 8) != 0x52455346) {
      fh = ResFile_Open(*(char **)((int)msg + 4),&DAT_004ddb18);
      if (fh != 0) {
        n = ResFile_Size(*(char **)((int)msg + 4));
        data = (void *)(**(code **)(UINT_008a856c + 0x5c))(n);
        if (data != (void *)0x0) {
          buf = (void *)(**(code **)(UINT_008a856c + 0x68))(data);
          ResFile_Read(fh,buf,n);
          (**(code **)(UINT_008a856c + 0x6c))(data);
          Res_Register(*(int *)((int)msg + 8),*(char **)((int)msg + 4),data);
        }
        local_4 = (uint)(data != (void *)0x0);
        ResFile_Close(fh);
        return local_4;
      }
      local_4 = 4;
    }
  }
  else if (*(int *)msg == 2) {
    (**(code **)(UINT_008a856c + 0x60))(*(undefined4 *)((int)msg + 0xc));
    return 0;
  }
  return local_4;
}
#undef local_4


/* ---- 0x0048d930  ResType_BitmapHandler ---- */
/* BKND handler: op 1 loads the .bm with stdBitmap and remaps 16-bit frames to the display, op 2
   frees it, op 3 reports its size */

int __cdecl ResType_BitmapHandler(void *msg)

{
  ushort *pixels;
  void *surface;
  int iVar1;
  void *pvVar2;
  int iVar3;
  
  if (*(int *)((int)msg + 8) != 0x444e4b42) {
    return 0;
  }
  iVar1 = *(int *)msg;
  if (iVar1 == 1) {
    pvVar2 = stdBitmap_LoadFile(*(char **)((int)msg + 4),0,0);
    if (pvVar2 != (void *)0x0) {
      if ((((*(int *)((int)pvVar2 + 0x20) != 3) && (*(int *)((int)pvVar2 + 0x20) == 0)) &&
          (*(int *)((int)pvVar2 + 0x28) == 1)) && (iVar1 = 0, 0 < *(int *)((int)pvVar2 + 100))) {
        do {
          surface = *(void **)(*(int *)((int)pvVar2 + 0x78) + iVar1 * 4);
          Surface_Lock(surface);
          iVar3 = 0;
          if (0 < *(int *)((int)surface + 0x10)) {
            do {
              Render_RemapPixels((ushort *)
                                 (iVar3 * *(int *)((int)surface + 0x18) +
                                 *(int *)((int)surface + 0x5c)),*(uint *)((int)surface + 0xc));
              iVar3 = iVar3 + 1;
            } while (iVar3 < *(int *)((int)surface + 0x10));
          }
          Surface_Unlock(surface);
          pixels = (ushort *)((int)surface + 0x60);
          pixels[0] = 0xf81f;
          pixels[1] = 0;
          Render_RemapPixels(pixels,1);
          iVar1 = iVar1 + 1;
        } while (iVar1 < *(int *)((int)pvVar2 + 100));
      }
      pvVar2 = Res_Register(*(int *)((int)msg + 8),*(char **)((int)msg + 4),pvVar2);
      return (int)pvVar2;
    }
  }
  else {
    if (iVar1 == 2) {
      stdBitmap_Free(*(void **)((int)msg + 0xc));
      return 1;
    }
    if (iVar1 == 3) {
      iVar1 = stdBitmap_ConvertToDisplay(*(void **)((int)msg + 0xc));
      *(int *)((int)msg + 0x10) = iVar1;
      return 1;
    }
  }
  return 0;
}

/* ---- 0x0048da40  ResType_CostumeHandler ---- */
/* COST handler: Cos_Load / Cos_Free */

int __cdecl ResType_CostumeHandler(void *msg)

{
  int iVar1;
  void *pvVar2;
  
  pvVar2 = (void *)0x0;
  if (*(int *)((int)msg + 8) != 0x54534f43) {
    return (int)pvVar2;
  }
  iVar1 = *(int *)msg;
  if (iVar1 == 1) {
    pvVar2 = (void *)Cos_Load(*(undefined4 *)((int)msg + 4));
    if (pvVar2 == (void *)0x0) {
      return 0;
    }
    pvVar2 = Res_Register(*(int *)((int)msg + 8),*(char **)((int)msg + 4),pvVar2);
  }
  else {
    if (iVar1 == 2) {
      Cos_Free(*(undefined4 *)((int)msg + 0xc));
      return 1;
    }
    if (iVar1 == 3) {
      *(undefined4 *)((int)msg + 0x10) = 1;
      return 1;
    }
  }
  return (int)pvVar2;
}

/* ---- 0x0048dab0  FUN_0048dab0 ---- */
void * FUN_0048dab0(int *param_1)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
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
    pvVar2 = rdColormap_Load((char *)param_1[1]);
    if (pvVar2 != (void *)0x0) {
      ((code *)rdColormap_Build16bitTables)(*(undefined4 *)((int)pvVar2 + 0x348),(int)pvVar2 + 0x30,0,0,0,&local_38);
      Render_RemapPixels(*(ushort **)((int)pvVar2 + 0x348),0x4000);
      pvVar2 = Res_Register(param_1[2],(char *)param_1[1],pvVar2);
      return pvVar2;
    }
  }
  else {
    if (iVar1 == 2) {
      rdColormap_Free(param_1[3]);
      return (void *)0x1;
    }
    if (iVar1 == 3) {
      iVar1 = FUN_00404b30(param_1[3]);
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


/* ---- 0x0048dbd0  FUN_0048dbd0 ---- */
void * FUN_0048dbd0(int *param_1)

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
    iVar2 = Font_LoadFile((char *)param_1[1],&param_1);
    if (iVar2 == 0) {
      pvVar3 = Res_Register(piVar1[2],(char *)piVar1[1],param_1);
      Res_SetLocked(param_1,0);
      return pvVar3;
    }
  }
  else {
    if (iVar2 == 2) {
      Font_Free((void *)param_1[3]);
      return (void *)0x1;
    }
    if (iVar2 == 3) {
      param_1[4] = 1;
      return (void *)0x1;
    }
  }
  return (void *)0x0;
}

/* ---- 0x0048dc60  FUN_0048dc60 ---- */
void * FUN_0048dc60(int *param_1)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  
  if (param_1[2] != 0x4659454b) {
    return (void *)0x0;
  }
  iVar1 = *param_1;
  if (iVar1 == 1) {
    pvVar3 = (void *)FUN_004c0660(param_1[1]);
    if (pvVar3 == (void *)0x0) {
      return (void *)0x0;
    }
    *(undefined4 *)((int)pvVar3 + 0x30) = 0x41700000;
    pvVar3 = Res_Register(param_1[2],(char *)param_1[1],pvVar3);
    return pvVar3;
  }
  if (iVar1 == 2) {
    FUN_004c0e40(param_1[3]);
  }
  else {
    if (iVar1 != 3) {
      return (void *)0x0;
    }
    iVar1 = param_1[3];
    param_1[4] = 0x84;
    iVar4 = 0;
    if (0 < *(int *)(iVar1 + 0x38)) {
      iVar5 = 0;
      do {
        iVar2 = param_1[4];
        iVar5 = iVar5 + 0x2c;
        param_1[4] = iVar2 + 0x2c;
        iVar4 = iVar4 + 1;
        param_1[4] = iVar2 + 0x2c + *(int *)(*(int *)(iVar1 + 0x3c) + -8 + iVar5) * 0x38;
      } while (iVar4 < *(int *)(iVar1 + 0x38));
      return (void *)0x1;
    }
  }
  return (void *)0x1;
}

/* ---- 0x0048dd20  FUN_0048dd20 ---- */
void * FUN_0048dd20(int *param_1)

{
  void *material;
  int iVar1;
  void *pvVar2;
  
  pvVar2 = (void *)0x0;
  if (param_1[2] != 0x2054414d) {
    return (void *)0x0;
  }
  iVar1 = *param_1;
  if (iVar1 == 1) {
    material = (void *)(**(code **)(UINT_008ca1d0 + 0x20))
                                 (0xb0,s_C__grimsrc_libs_grimlib_Main_spu_004e9c30,0x49f);
    iVar1 = rdMaterial_LoadFile((char *)param_1[1],material,0,0);
    if (iVar1 == 0) {
      iVar1 = rdMaterial_LoadFile(s_dflt_mat_004e9c68,material,0,0);
      if (iVar1 == 0) {
        rdMaterial_FreeContents(material);
        (**(code **)(UINT_008ca1d0 + 0x24))(material);
        return (void *)0x0;
      }
    }
    pvVar2 = Res_Register(param_1[2],(char *)param_1[1],material);
    Res_SetLocked(material,0);
  }
  else {
    if (iVar1 == 2) {
      rdMaterial_FreeContents(param_1[3]);
      (**(code **)(UINT_008ca1d0 + 0x24))(param_1[3]);
      return (void *)0x1;
    }
    if (iVar1 == 3) {
      param_1[4] = 0;
      return (void *)0x1;
    }
  }
  return pvVar2;
}

/* ---- 0x0048de10  FUN_0048de10 ---- */
void * FUN_0048de10(int *param_1)

{
  int iVar1;
  void *pvVar2;
  
  if (param_1[2] == 0x4c444f4d) {
    iVar1 = *param_1;
    if (iVar1 == 1) {
      pvVar2 = (void *)FUN_0040a8f0(param_1[1]);
      if (pvVar2 != (void *)0x0) {
        pvVar2 = Res_Register(param_1[2],(char *)param_1[1],pvVar2);
        return pvVar2;
      }
    }
    else {
      if (iVar1 == 2) {
        FUN_0040c0d0(param_1[3]);
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

/* ---- 0x0048de70  FUN_0048de70 ---- */
void * FUN_0048de70(int *param_1)

{
  int iVar1;
  void *pvVar2;
  
  if (param_1[2] == 0x20544553) {
    iVar1 = *param_1;
    if (iVar1 == 1) {
      pvVar2 = (void *)FUN_004a49a0(param_1[1]);
      if (pvVar2 != (void *)0x0) {
        pvVar2 = Res_Register(param_1[2],(char *)param_1[1],pvVar2);
        return pvVar2;
      }
    }
    else {
      if (iVar1 == 2) {
        FUN_004a4c40(param_1[3]);
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

/* ---- 0x0048dee0  FUN_0048dee0 ---- */
void * FUN_0048dee0(int *param_1)

{
  int iVar1;
  void *pvVar2;
  
  if (param_1[2] == 0x4655425a) {
    iVar1 = *param_1;
    if (iVar1 == 1) {
      pvVar2 = (void *)((code *)FUN_004a4920)(param_1[1]);
      if (pvVar2 != (void *)0x0) {
        pvVar2 = Res_Register(param_1[2],(char *)param_1[1],pvVar2);
        return pvVar2;
      }
    }
    else {
      if (iVar1 == 2) {
        FUN_004a4980(param_1[3]);
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
