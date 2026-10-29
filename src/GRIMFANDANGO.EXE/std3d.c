/* GRIMFANDANGO.EXE :: std3d.c
 * functions 0x00478230 .. 0x0047a930 (35 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00478230  D3D_Enumerate ---- */
/* Queries IDirect3D from DirectDraw and enumerates the 3D drivers into g_D3dDrivers (0x22c bytes
   each) */

undefined4 D3D_Enumerate(void)

{
  int iVar1;
  
  PTR_00806968 = (int *)DDraw_Get();
  if (PTR_00806968 == (int *)0x0) {
    return 0;
  }
  g_dwD3dRenderFlags = 0x19b3;
  DAT_004dee60 = 1;
  iVar1 = (**(code_std **)*PTR_00806968)(PTR_00806968,&DAT_004d8570,&g_pDirect3D);
  if (iVar1 != 0) {
    return 0;
  }
  g_dwD3dDriverCount = 0;
  iVar1 = (**(code_std **)(*(int *)g_pDirect3D + 0x10))(g_pDirect3D,FUN_0047a3b0,0);
  if (iVar1 != 0) {
    return 0;
  }
  if (g_dwD3dDriverCount == 0) {
    return 0;
  }
  DAT_0080696c = 1;
  return 1;
}

/* ---- 0x004782b0  D3D_Release ---- */
void D3D_Release(void)

{
  if (g_pDirect3D != (void *)0x0) {
    (**(code_std **)(*(int *)g_pDirect3D + 8))(g_pDirect3D);
  }
  DAT_0080696c = 0;
  return;
}

/* ---- 0x004782d0  D3D_IsAvailable ---- */
undefined4 D3D_IsAvailable(void)

{
  return DAT_0080696c;
}

/* ---- 0x004782e0  D3D_SelectDriver ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Creates the Direct3D device, z-buffer, viewport, execute buffer and picks the texture formats */

int __cdecl D3D_SelectDriver(uint driverIdx,int useZBuffer)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  #define pvStack_ac (*(void **)(_frame + (0xc0 - 0xac)))
  #define pcStack_a8 (*(code_std **)(_frame + (0xc0 - 0xa8)))
  #define uStack_a4 (*(undefined4 *)(_frame + (0xc0 - 0xa4)))
  #define piStack_a0 (*(int **)(_frame + (0xc0 - 0xa0)))
  #define iStack_9c (*(int *)(_frame + (0xc0 - 0x9c)))
  #define ppvStack_98 (*(void ***)(_frame + (0xc0 - 0x98)))
  #define uStack_74 (*(undefined4 *)(_frame + (0xc0 - 0x74)))
  #define uStack_70 (*(undefined4 *)(_frame + (0xc0 - 0x70)))
  #define auStack_60 (*(undefined4 (*)[24])(_frame + (0xc0 - 0x60)))
  
  if (DAT_00806970 != 0) {
    return 0;
  }
  if (g_dwD3dDriverCount <= driverIdx) {
    return 0;
  }
  DAT_00900530 = driverIdx;
  g_pD3dDriver = &DAT_00900b40 + driverIdx * 0x8b;
  if (((useZBuffer == 0) || (*(int *)(&DAT_00900b48 + driverIdx * 0x22c) == 0)) ||
     ((g_dwD3dRenderFlags & 0x1800) == 0)) {
    DAT_004dee60 = 0;
  }
  else {
    DAT_004dee60 = 1;
    ppvStack_98 = *(void ***)((int)g_pVideoMode + 0xc);
    iStack_9c = *(undefined4 *)((int)g_pVideoMode + 8);
    piStack_a0 = (int *)0x478388;
    iVar1 = ((code *)D3D_CreateZBuffer)();
    if (iVar1 == 0) {
      return 0;
    }
    DAT_00900534 = (-(uint)((*(uint *)((int)g_pD3dDriver + 0x2c) & 0x10) != 0) & 0xe) + 2;
  }
  iStack_9c = (int)g_pD3dDriver + 0x21c;
  ppvStack_98 = &g_pD3dDevice;
  piStack_a0 = PTR_00905644;
  uStack_a4 = 0x4783ca;
  iVar1 = (**(code_std **)*PTR_00905644)();
  if (iVar1 != 0) {
    return 0;
  }
  DAT_00806930 = 0;
  uStack_a4 = 0;
  pcStack_a8 = FUN_0047a590;
  pvStack_ac = g_pD3dDevice;
  iVar1 = (**(code_std **)(*(int *)g_pD3dDevice + 0x38))();
  if (iVar1 != 0) {
    return 0;
  }
  if (DAT_00806930 == 0) {
    return 0;
  }
  iVar1 = ((code *)D3D_CreateViewport)(*(undefined4 *)((int)g_pVideoMode + 8),
                             *(undefined4 *)((int)g_pVideoMode + 0xc));
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = D3D_InitRenderState();
  if (iVar1 == 0) {
    return 0;
  }
  _DAT_008063fc = *(int *)((int)g_pD3dDriver + 0x40);
  if (_DAT_008063fc == 0) {
    _DAT_008063fc = 0x10000;
  }
  _DAT_008063f0 = 0x14;
  _DAT_008063f4 = 1;
  _DAT_008063f8 = 0;
  DAT_00806400 = 0;
  DAT_00806940 = *(uint *)((int)g_pD3dDriver + 0x44);
  if ((DAT_00806940 == 0) || (0x1ff < DAT_00806940)) {
    DAT_00806940 = 0x200;
  }
  _DAT_00806958 = _DAT_008063fc;
  (**(code_std **)(*(int *)g_pD3dDevice + 0x18))(g_pD3dDevice,&DAT_008063f0,&g_pD3dExecuteBuffer,0);
  DAT_004dee58 = 1;
  DAT_00806944 = 0;
  D3D_SetTextureLimits
            (*(int *)((int)g_pD3dDriver + 0x30),*(int *)((int)g_pD3dDriver + 0x34),
             *(int *)((int)g_pD3dDriver + 0x38),*(int *)((int)g_pD3dDriver + 0x3c));
  g_pD3dTextureList = (void *)0x0;
  PTR_0080694c = (void *)0x0;
  _DAT_00900568 = D3D_FindTextureFormat((int)g_pVideoMode + 0x1c,&DAT_00900620,DAT_00806930);
  DAT_00806934 = &DAT_00900620 + _DAT_00900568 * 0xa4;
  if (*(int *)((int)g_pD3dDriver + 0x10) != 0) {
    pvStack_ac = (void *)0x2;
    pcStack_a8 = (code *)0x10;
    uStack_a4 = 5;
    piStack_a0 = (int *)0x5;
    iStack_9c = 5;
    _DAT_009014d8 = D3D_FindTextureFormat(&pvStack_ac,&DAT_00900620,DAT_00806930);
    DAT_00806938 = &DAT_00900620 + _DAT_009014d8 * 0xa4;
    if (*(int *)((int)g_pD3dDriver + 0x18) == 0) {
      pvStack_ac = (void *)0x2;
      pcStack_a8 = (code *)0x10;
      uStack_a4 = 4;
      piStack_a0 = (int *)0x4;
      iStack_9c = 4;
      _DAT_0090052c = D3D_FindTextureFormat(&pvStack_ac,&DAT_00900620,DAT_00806930);
      uStack_74 = 0x20;
      uStack_70 = 0x20;
      DAT_0080693c = (undefined4 *)(&DAT_00900620 + _DAT_0090052c * 0xa4);
      puVar2 = DAT_0080693c;
      puVar3 = auStack_60;
      for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      DAT_00806950 = Surface_Create(&uStack_74,1,0,0);
    }
  }
  ((code *)D3D_SetVertexLimit)((int)g_pD3dDriver + 0x148,(int)g_pD3dDriver + 0x14c);
  DAT_00806970 = 1;
  return 1;
}
#undef auStack_60
#undef iStack_9c
#undef pcStack_a8
#undef piStack_a0
#undef ppvStack_98
#undef pvStack_ac
#undef uStack_70
#undef uStack_74
#undef uStack_a4


/* ---- 0x00478660  D3D_ReleaseDriver ---- */
void D3D_ReleaseDriver(void)

{
  if (DAT_00806970 != 0) {
    if (DAT_00806950 != (void *)0x0) {
      Surface_Free(DAT_00806950);
      DAT_00806950 = (void *)0x0;
    }
    (**(code_std **)(*(int *)g_pD3dExecuteBuffer + 8))(g_pD3dExecuteBuffer);
    D3D_FreeAllTextures();
    if (PTR_0080660c != (int *)0x0) {
      (**(code_std **)(*PTR_0080660c + 8))(PTR_0080660c);
      PTR_0080660c = (int *)0x0;
    }
    if (PTR_00806614 != (int *)0x0) {
      (**(code_std **)(*PTR_00806614 + 8))(PTR_00806614);
      PTR_00806614 = (int *)0x0;
    }
    if (PTR_00901464 != (int *)0x0) {
      (**(code_std **)(*PTR_00901464 + 8))(PTR_00901464);
      PTR_00901464 = (int *)0x0;
    }
    if (g_pD3dDevice != (void *)0x0) {
      (**(code_std **)(*(int *)g_pD3dDevice + 8))(g_pD3dDevice);
      g_pD3dDevice = (void *)0x0;
    }
    g_pD3dDriver = (void *)0x0;
    DAT_00806970 = 0;
  }
  return;
}

/* ---- 0x00478700  D3D_SetTextureLimits ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl D3D_SetTextureLimits(int minW,int minH,int maxSize,int d)

{
  DAT_004dee48 = minW;
  DAT_004dee4c = minH;
  DAT_004dee50 = maxSize;
  _DAT_004dee54 = d;
  return;
}

/* ---- 0x00478730  D3D_BeginScene ---- */
void D3D_BeginScene(void)

{
  if (DAT_00806974 == 0) {
    (**(code_std **)(*(int *)g_pD3dDevice + 0x4c))(g_pD3dDevice);
    DAT_00806974 = 1;
  }
  return;
}

/* ---- 0x00478750  D3D_EndScene ---- */
void D3D_EndScene(void)

{
  if (DAT_00806974 != 0) {
    (**(code_std **)(*(int *)g_pD3dDevice + 0x50))(g_pD3dDevice);
    DAT_00806974 = 0;
  }
  return;
}

/* ---- 0x00478770  D3D_BeginExecuteBuffer ---- */
undefined4 D3D_BeginExecuteBuffer(void)

{
  int iVar1;
  
  DAT_0080695c = 0;
  DAT_004dee58 = DAT_004dee58 + 1;
  DAT_00806960 = 0;
  DAT_004dee5c = 1;
  iVar1 = (**(code_std **)(*(int *)g_pD3dExecuteBuffer + 0x10))(g_pD3dExecuteBuffer,&DAT_008063f0);
  if (iVar1 != 0) {
    return 0;
  }
  DAT_008063ec = DAT_00806400;
  PTR_00806918 = DAT_00806400;
  return 1;
}

/* ---- 0x004787d0  D3D_AddVertices ---- */
/* Copies 32-byte TLVERTEX records into the execute buffer */

int __cdecl D3D_AddVertices(void *verts,uint count)

{
  int iVar1;
  int *piVar2;
  
  if (DAT_00806940 < count + DAT_0080695c) {
    return 0;
  }
  if (PTR_00806918 != verts) {
    piVar2 = PTR_00806918;
    for (iVar1 = (count & 0x7ffffff) << 3; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar2 = *(int *)verts;
      verts = (int *)((int)verts + 4);
      piVar2 = piVar2 + 1;
    }
    for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
      *(char *)piVar2 = (char)*(int *)verts;
      verts = (int *)((int)verts + 1);
      piVar2 = (int *)((int)piVar2 + 1);
    }
  }
  PTR_00806918 = PTR_00806918 + count * 8;
  DAT_0080695c = DAT_0080695c + count;
  return 1;
}

/* ---- 0x00478840  D3D_BeginInstructions ---- */
/* Emits the PROCESSVERTICES instruction for everything added so far */

undefined4 D3D_BeginInstructions(void)

{
  DAT_0080691c = PTR_00806918;
  *(undefined1 *)PTR_00806918 = 9;
  *(undefined1 *)((int)PTR_00806918 + 1) = 0x10;
  *(undefined2 *)((int)PTR_00806918 + 2) = 1;
  PTR_00806918 = PTR_00806918 + 1;
  *PTR_00806918 = 2;
  *(undefined2 *)(PTR_00806918 + 1) = 0;
  *(undefined2 *)((int)PTR_00806918 + 6) = 0;
  PTR_00806918[2] = DAT_0080695c;
  PTR_00806918[3] = 0;
  PTR_00806918 = PTR_00806918 + 4;
  return 1;
}

/* ---- 0x004788c0  D3D_AddTriangles ---- */
/* Emits TRIANGLE instructions, grouped by texture handle, switching render state and texture as
   needed */

int __cdecl D3D_AddTriangles(void *tris,uint count)

{
  uint uVar1;
  uint flags;
  void *pvVar2;
  int iVar3;
  uint *puVar4;
  undefined2 *puVar5;
  int iVar6;
  
  puVar5 = tris;
  tris = (void *)0x0;
  if (count != 0) {
    do {
      uVar1 = *(uint *)(puVar5 + 8);
      flags = *(uint *)(puVar5 + 6);
      puVar4 = (uint *)(puVar5 + 6);
      iVar6 = 0;
      pvVar2 = tris;
      if (uVar1 == 0) {
        for (; ((pvVar2 < count && (puVar4[1] == 0)) && (*puVar4 == flags)); puVar4 = puVar4 + 5) {
          iVar6 = iVar6 + 1;
          pvVar2 = (void *)((int)pvVar2 + 1);
        }
        D3D_SetRenderFlags(flags);
        if (DAT_004dee5c != 0) {
          *(undefined1 *)PTR_00806918 = 8;
          *(undefined1 *)((int)PTR_00806918 + 1) = 8;
          *(undefined2 *)((int)PTR_00806918 + 2) = 1;
          PTR_00806918 = PTR_00806918 + 1;
          *PTR_00806918 = 1;
          PTR_00806918[1] = 0;
          PTR_00806918 = PTR_00806918 + 2;
          DAT_004dee5c = 0;
        }
        *(undefined1 *)PTR_00806918 = 3;
        *(undefined1 *)((int)PTR_00806918 + 1) = 8;
        *(short *)((int)PTR_00806918 + 2) = (short)iVar6;
        PTR_00806918 = PTR_00806918 + 1;
        for (iVar3 = iVar6; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined2 *)PTR_00806918 = *puVar5;
          *(undefined2 *)((int)PTR_00806918 + 2) = puVar5[2];
          *(undefined2 *)(PTR_00806918 + 1) = puVar5[4];
          *(undefined2 *)((int)PTR_00806918 + 6) = 0x700;
          PTR_00806918 = PTR_00806918 + 2;
          puVar5 = puVar5 + 10;
        }
      }
      else {
        for (; ((pvVar2 < count && (puVar4[1] == uVar1)) && (*puVar4 == flags)); puVar4 = puVar4 + 5
            ) {
          iVar6 = iVar6 + 1;
          pvVar2 = (void *)((int)pvVar2 + 1);
        }
        D3D_SetRenderFlags(flags);
        if (*(uint *)(puVar5 + 8) != DAT_004dee5c) {
          *(undefined1 *)PTR_00806918 = 8;
          *(undefined1 *)((int)PTR_00806918 + 1) = 8;
          *(undefined2 *)((int)PTR_00806918 + 2) = 1;
          PTR_00806918 = PTR_00806918 + 1;
          *PTR_00806918 = 1;
          PTR_00806918[1] = *(int *)(uVar1 + 0x74);
          PTR_00806918 = PTR_00806918 + 2;
          DAT_004dee5c = uVar1;
        }
        *(undefined1 *)PTR_00806918 = 3;
        *(undefined1 *)((int)PTR_00806918 + 1) = 8;
        *(short *)((int)PTR_00806918 + 2) = (short)iVar6;
        PTR_00806918 = PTR_00806918 + 1;
        for (iVar3 = iVar6; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined2 *)PTR_00806918 = *puVar5;
          *(undefined2 *)((int)PTR_00806918 + 2) = puVar5[2];
          *(undefined2 *)(PTR_00806918 + 1) = puVar5[4];
          *(undefined2 *)((int)PTR_00806918 + 6) = 0x700;
          PTR_00806918 = PTR_00806918 + 2;
          puVar5 = puVar5 + 10;
        }
      }
      tris = (void *)((int)tris + iVar6);
    } while (tris < count);
  }
  DAT_00806960 = DAT_00806960 + count;
  return 1;
}

/* ---- 0x00478b40  D3D_ExecuteBuffer ---- */
/* Terminates and executes the buffer on the device */

bool D3D_ExecuteBuffer(void)

{
  unsigned char _frame[0x50] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  void **ppvVar2;
  #define pvStack_38 (*(void **)(_frame + (0x50 - 0x38)))
  
  *(undefined1 *)PTR_00806918 = 0xb;
  *(undefined1 *)((int)PTR_00806918 + 1) = 0;
  *(undefined2 *)((int)PTR_00806918 + 2) = 0;
  PTR_00806918 = PTR_00806918 + 1;
  pvStack_38 = g_pD3dExecuteBuffer;
  ppvVar2 = &pvStack_38;
  iVar1 = (**(code_std **)(*(int *)g_pD3dExecuteBuffer + 0x14))();
  if (iVar1 != 0) {
    return false;
  }
  for (iVar1 = 0xc; ppvVar2 = ppvVar2 + 1, iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppvVar2 = (void *)0x0;
  }
  (**(code_std **)(*(int *)g_pD3dExecuteBuffer + 0x18))(g_pD3dExecuteBuffer,&STACK0X(0xffffffcc));
  iVar1 = (**(code_std **)(*(int *)g_pD3dDevice + 0x20))
                    (g_pD3dDevice,g_pD3dExecuteBuffer,PTR_0080660c,2);
  return iVar1 == 0;
}
#undef pvStack_38


/* ---- 0x00478c00  D3D_SetRenderFlags ---- */
/* Emits STATERENDER changes: 0x8000 z compare, 0x600 blending, 0x1800 filtering/perspective, 0x40
   fog */

void __cdecl D3D_SetRenderFlags(uint flags)

{
  int iVar1;
  
  if (DAT_00806924 != flags) {
    if (((flags ^ DAT_00806924) & 0x8000) != 0) {
      *(undefined1 *)PTR_00806918 = 8;
      *(undefined1 *)((int)PTR_00806918 + 1) = 8;
      *(undefined2 *)((int)PTR_00806918 + 2) = 1;
      PTR_00806918 = PTR_00806918 + 1;
      *PTR_00806918 = 0xb;
      if ((flags & 0x8000) == 0) {
        PTR_00806918[1] = 1;
        PTR_00806918 = PTR_00806918 + 2;
      }
      else {
        PTR_00806918[1] = 0;
        PTR_00806918 = PTR_00806918 + 2;
      }
    }
    if (((flags ^ DAT_00806924) & 0x600) != 0) {
      *(undefined1 *)PTR_00806918 = 8;
      *(undefined1 *)((int)PTR_00806918 + 1) = 8;
      *(undefined2 *)((int)PTR_00806918 + 2) = 4;
      if ((flags & 0x600) == 0) {
        PTR_00806918 = PTR_00806918 + 1;
        *PTR_00806918 = 0x13;
        PTR_00806918[1] = 2;
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x14;
        PTR_00806918[1] = 1;
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x15;
        if ((flags & 0x400) == 0) {
          PTR_00806918[1] = 2;
        }
        else {
          PTR_00806918[1] = 4;
        }
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x1b;
        PTR_00806918[1] = 0;
      }
      else {
        PTR_00806918 = PTR_00806918 + 1;
        *PTR_00806918 = 0x13;
        PTR_00806918[1] = 5;
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x14;
        PTR_00806918[1] = 6;
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x15;
        if ((flags & 0x400) == 0) {
          PTR_00806918[1] = 2;
        }
        else {
          PTR_00806918[1] = 4;
        }
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x1b;
        PTR_00806918[1] = 1;
      }
      PTR_00806918 = PTR_00806918 + 2;
    }
    if (((flags ^ DAT_00806924) & 0x1800) != 0) {
      *(undefined1 *)PTR_00806918 = 8;
      *(undefined1 *)((int)PTR_00806918 + 1) = 8;
      *(undefined2 *)((int)PTR_00806918 + 2) = 2;
      PTR_00806918 = PTR_00806918 + 1;
      *PTR_00806918 = 0x17;
      if ((flags & 0x800) == 0) {
        PTR_00806918[1] = 8;
      }
      else {
        iVar1 = D3D_FilterBitsToEnum(DAT_00900534);
        PTR_00806918[1] = iVar1;
      }
      PTR_00806918 = PTR_00806918 + 2;
      *PTR_00806918 = 0xe;
      if ((flags & 0x1000) == 0) {
        PTR_00806918[1] = 0;
        PTR_00806918 = PTR_00806918 + 2;
      }
      else {
        PTR_00806918[1] = 1;
        PTR_00806918 = PTR_00806918 + 2;
      }
    }
    if (((flags ^ DAT_00806924) & 0x40) != 0) {
      if ((flags & 0x40) == 0) {
        *(undefined1 *)PTR_00806918 = 8;
        *(undefined1 *)((int)PTR_00806918 + 1) = 8;
        *(undefined2 *)((int)PTR_00806918 + 2) = 1;
        PTR_00806918 = PTR_00806918 + 1;
        *PTR_00806918 = 0x1c;
        PTR_00806918[1] = 0;
      }
      else {
        *(undefined1 *)PTR_00806918 = 8;
        *(undefined1 *)((int)PTR_00806918 + 1) = 8;
        *(undefined2 *)((int)PTR_00806918 + 2) = 5;
        PTR_00806918 = PTR_00806918 + 1;
        *PTR_00806918 = 0x1c;
        PTR_00806918[1] = 1;
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x22;
        PTR_00806918[1] = (DAT_008063e8 << 8 | DAT_00806610) << 8 | DAT_008061dc;
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x23;
        PTR_00806918[1] = 3;
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x24;
        PTR_00806918[1] = DAT_008061e0;
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x25;
        PTR_00806918[1] = DAT_008061d8;
      }
      PTR_00806918 = PTR_00806918 + 2;
    }
    DAT_00806924 = flags;
  }
  return;
}

/* ---- 0x00479070  D3D_ClampTextureSize ---- */
void D3D_ClampTextureSize(uint param_1,uint param_2,uint *param_3,uint *param_4)

{
  if (param_1 == 0) {
    param_1 = 1;
  }
  else if (DAT_004dee50 < param_1) {
    param_1 = DAT_004dee50;
  }
  if (param_2 == 0) {
    param_2 = 1;
  }
  else if (DAT_004dee50 < param_2) {
    param_2 = DAT_004dee50;
  }
  if (((param_1 < DAT_004dee48) || (param_2 < DAT_004dee4c)) ||
     ((*(int *)((int)g_pD3dDriver + 0x1c) != 0 && (param_1 != param_2)))) {
    if ((*(int *)((int)g_pD3dDriver + 0x1c) != 0) && (param_1 != param_2)) {
      if (param_1 <= param_2) {
        param_1 = param_2;
      }
      *param_3 = param_1;
      *param_4 = param_1;
      return;
    }
    if (param_1 < DAT_004dee48) {
      param_1 = DAT_004dee48;
    }
    if (param_2 < DAT_004dee4c) {
      param_2 = DAT_004dee4c;
    }
  }
  *param_3 = param_1;
  *param_4 = param_2;
  return;
}

/* ---- 0x00479110  D3D_ResetTextures ---- */
/* Lua ResetTextures: frees every texture record */

void D3D_ResetTextures(void)

{
  while (g_pD3dTextureList != (void *)0x0) {
    (**(code_std **)(**(int **)((int)g_pD3dTextureList + 4) + 8))(*(int **)((int)g_pD3dTextureList + 4))
    ;
    (**(code_std **)(**(int **)g_pD3dTextureList + 8))(*(int **)g_pD3dTextureList);
    *(undefined4 *)((int)g_pD3dTextureList + 0x78) = 0;
    *(undefined4 *)((int)g_pD3dTextureList + 0x8c) = 0;
    D3D_UnlinkTexture(g_pD3dTextureList);
  }
  return;
}

/* ---- 0x00479170  D3D_CreateTexture ---- */
/* Builds a 0x98-byte texture record {sysSurface, vidSurface, ..., +0x74 handle, +0x78 valid, +0x80
   w, +0x88 h, +0x88 size, +0x8c frameStamp, +0x90 prev, +0x94 next}; scales to the driver's size
   limits and converts 8-bit sources to 16-bit */

int __cdecl D3D_CreateTexture(void *surface,void *texture,int usePalette,int colorKey)

{
  unsigned char _frame[0x170] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  undefined2 *puVar2;
  void *pvVar3;
  int iVar4;
  byte *pbVar5;
  void *pvVar6;
  void *pvVar7;
  undefined4 *puVar8;
  void *pvVar9;
  void **ppvVar10;
  int x;
  #define local_15c (*(undefined4 (*)[4])(_frame + (0x170 - 0x15c)))
  #define local_14c (*(int *)(_frame + (0x170 - 0x14c)))
  #define local_138 (*(int *)(_frame + (0x170 - 0x138)))
  #define local_f0 (*(void *(*)[19])(_frame + (0x170 - 0xf0)))
  #define local_a4 (*(undefined4 *)(_frame + (0x170 - 0xa4)))
  #define local_a0 (*(undefined4 *)(_frame + (0x170 - 0xa0)))
  #define local_9c (*(void **)(_frame + (0x170 - 0x9c)))
  #define local_98 (*(void **)(_frame + (0x170 - 0x98)))
  #define local_3c (*(undefined4 *)(_frame + (0x170 - 0x3c)))
  #define local_38 (*(int *)(_frame + (0x170 - 0x38)))
  #define local_34 (*(int *)(_frame + (0x170 - 0x34)))
  #define local_30 (*(void **)(_frame + (0x170 - 0x30)))
  #define local_2c (*(undefined4 *)(_frame + (0x170 - 0x2c)))
  #define local_28 (*(void **)(_frame + (0x170 - 0x28)))
  #define pvStack_24 (*(void **)(_frame + (0x170 - 0x24)))
  #define local_20 (*(void **)(_frame + (0x170 - 0x20)))
  #define fStack_1c (*(float *)(_frame + (0x170 - 0x1c)))
  #define local_18 (*(int **)(_frame + (0x170 - 0x18)))
  #define local_14 (*(int **)(_frame + (0x170 - 0x14)))
  #define local_10 (*(int **)(_frame + (0x170 - 0x10)))
  #define local_c (*(void **)(_frame + (0x170 - 0xc)))
  #define local_8 (*(int **)(_frame + (0x170 - 0x8)))
  
  pvVar3 = *(void **)((int)surface + 0xc);
  local_8 = (int *)0x0;
  local_18 = (int *)0x0;
  local_10 = (int *)0x0;
  local_14 = (int *)0x0;
  local_30 = (void *)0x0;
  if (pvVar3 == (void *)0x0) {
    pvVar3 = (void *)0x1;
  }
  else if ((void *)0x100 < pvVar3) {
    pvVar3 = (void *)0x100;
  }
  pvVar6 = *(void **)((int)surface + 0x10);
  if (pvVar6 == (void *)0x0) {
    pvVar6 = (void *)0x1;
  }
  else if ((void *)0x100 < pvVar6) {
    pvVar6 = (void *)0x100;
  }
  local_c = pvVar3;
  if (((pvVar3 < DAT_004dee48) || (pvVar6 < DAT_004dee4c)) ||
     ((pvVar7 = surface, *(int *)((int)g_pD3dDriver + 0x1c) != 0 && (pvVar3 != pvVar6)))) {
    puVar8 = (undefined4 *)((int)surface + 0xc);
    ppvVar10 = local_f0;
    for (iVar4 = 0x13; iVar4 != 0; iVar4 = iVar4 + -1) {
      *ppvVar10 = (void *)*puVar8;
      puVar8 = puVar8 + 1;
      ppvVar10 = ppvVar10 + 1;
    }
    if ((*(int *)((int)g_pD3dDriver + 0x1c) == 0) || (pvVar3 == pvVar6)) {
      if (pvVar3 < DAT_004dee48) {
        pvVar3 = DAT_004dee48;
      }
      pvVar7 = pvVar6;
      if (pvVar6 < DAT_004dee4c) {
        pvVar7 = DAT_004dee4c;
      }
    }
    else {
      pvVar7 = pvVar3;
      if (pvVar3 <= pvVar6) {
        pvVar3 = pvVar6;
        pvVar7 = pvVar6;
      }
    }
    local_28 = local_c;
    pvStack_24 = (void *)0x0;
    local_38 = (int)ROUND(PUN(float,pvVar3) / (float)(int)local_c - -0.5);
    fStack_1c = PUN(float,pvVar7) / (float)(int)pvVar6 - -0.5;
    iVar4 = (int)ROUND(fStack_1c);
    local_f0[0] = (void *)((int)local_f0[0] * local_38);
    local_f0[1] = (void *)((int)local_f0[1] * iVar4);
    local_34 = iVar4;
    local_20 = pvVar6;
    local_30 = Surface_Create(local_f0,0,0,0);
    if (iVar4 != 0) {
      local_34 = 0;
      fStack_1c = (float)iVar4;
      do {
        if (local_38 != 0) {
          x = 0;
          iVar4 = local_38;
          do {
            Surface_Blit(local_30,surface,x,local_34,(int *)0x0,0);
            x = x + (int)local_c;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
        }
        local_34 = local_34 + (int)pvVar6;
        fStack_1c = (float)((int)fStack_1c + -1);
      } while (fStack_1c != 0.0);
    }
    local_c = local_f0[0];
    surface = local_f0[1];
    pvVar7 = local_30;
    pvVar6 = surface;
  }
  surface = pvVar6;
  fStack_1c = (float)((int)surface * (int)local_c);
  if ((usePalette == 0) || (*(int *)((int)g_pD3dDriver + 0x10) == 0)) {
    if (colorKey == 0) {
      *(undefined4 *)((int)texture + 0x7c) = 0;
      iVar4 = DAT_00806934;
    }
    else {
      *(undefined4 *)((int)texture + 0x7c) = 1;
      iVar4 = DAT_0080693c;
    }
  }
  else {
    *(undefined4 *)((int)texture + 0x7c) = 1;
    iVar4 = DAT_00806938;
    if (colorKey != 0) {
      iVar4 = DAT_0080693c;
    }
  }
  Mem_Copy(&local_a4,(void *)(iVar4 + 0x38),0x6c);
  pvVar3 = local_c;
  local_9c = surface;
  local_a4 = 0x6c;
  local_a0 = 0x1007;
  local_3c = 0x1800;
  local_98 = local_c;
  iVar4 = (**(code_std **)(*PTR_00806968 + 0x18))(PTR_00806968,&local_a4,&local_8,0);
  if (iVar4 != 0) {
    local_8 = (int *)0x0;
    goto LAB_0047940a;
  }
  puVar8 = local_15c;
  for (iVar4 = 0x1b; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  local_15c[0] = 0x6c;
  iVar4 = (**(code_std **)(*local_8 + 100))(local_8,0,local_15c,1,0);
  if (iVar4 != 0) goto LAB_0047940a;
  iVar4 = *(int *)((int)pvVar7 + 0x20);
  if (iVar4 == 0) {
    Surface_Lock(pvVar7);
    if ((usePalette == 0) || (*(int *)((int)g_pD3dDriver + 0x10) == 0)) {
      if (colorKey == 0) {
        pvVar6 = (void *)0x0;
        if (surface != (void *)0x0) {
          do {
            pbVar5 = (byte *)((int)pvVar6 * *(int *)((int)pvVar7 + 0x18) +
                             *(int *)((int)pvVar7 + 0x5c));
            puVar2 = (undefined2 *)((int)pvVar6 * local_14c + local_138);
            pvVar9 = pvVar3;
            for (; pvVar9 != (void *)0x0; pvVar9 = (void *)((int)pvVar9 - 1)) {
              bVar1 = *pbVar5;
              pbVar5 = pbVar5 + 1;
              *puVar2 = *(undefined2 *)((int)&DAT_00806408 + (uint)bVar1 * 2);
              puVar2 = puVar2 + 1;
              pvVar3 = local_c;
            }
            pvVar6 = (void *)((int)pvVar6 + 1);
          } while (pvVar6 < surface);
        }
      }
      else {
        pvVar6 = (void *)0x0;
        if (surface != (void *)0x0) {
          do {
            pbVar5 = (byte *)((int)pvVar6 * *(int *)((int)pvVar7 + 0x18) +
                             *(int *)((int)pvVar7 + 0x5c));
            puVar2 = (undefined2 *)((int)pvVar6 * local_14c + local_138);
            pvVar9 = pvVar3;
            for (; pvVar9 != (void *)0x0; pvVar9 = (void *)((int)pvVar9 - 1)) {
              bVar1 = *pbVar5;
              pbVar5 = pbVar5 + 1;
              *puVar2 = *(undefined2 *)(&DAT_00805fd8 + (uint)bVar1 * 2);
              puVar2 = puVar2 + 1;
              pvVar3 = local_c;
            }
            pvVar6 = (void *)((int)pvVar6 + 1);
          } while (pvVar6 < surface);
        }
      }
    }
    else if (colorKey == 0) {
      pvVar6 = (void *)0x0;
      if (surface != (void *)0x0) {
        do {
          pbVar5 = (byte *)((int)pvVar6 * *(int *)((int)pvVar7 + 0x18) +
                           *(int *)((int)pvVar7 + 0x5c));
          puVar2 = (undefined2 *)((int)pvVar6 * local_14c + local_138);
          pvVar9 = pvVar3;
          for (; pvVar9 != (void *)0x0; pvVar9 = (void *)((int)pvVar9 - 1)) {
            bVar1 = *pbVar5;
            pbVar5 = pbVar5 + 1;
            *puVar2 = *(undefined2 *)(&DAT_008061e8 + (uint)bVar1 * 2);
            puVar2 = puVar2 + 1;
            pvVar3 = local_c;
          }
          pvVar6 = (void *)((int)pvVar6 + 1);
        } while (pvVar6 < surface);
      }
    }
    else {
      pvVar6 = (void *)0x0;
      if (surface != (void *)0x0) {
        do {
          pbVar5 = (byte *)((int)pvVar6 * *(int *)((int)pvVar7 + 0x18) +
                           *(int *)((int)pvVar7 + 0x5c));
          puVar2 = (undefined2 *)((int)pvVar6 * local_14c + local_138);
          pvVar9 = pvVar3;
          for (; pvVar9 != (void *)0x0; pvVar9 = (void *)((int)pvVar9 - 1)) {
            bVar1 = *pbVar5;
            pbVar5 = pbVar5 + 1;
            *puVar2 = *(undefined2 *)(&DAT_00805fd8 + (uint)bVar1 * 2);
            puVar2 = puVar2 + 1;
            pvVar3 = local_c;
          }
          pvVar6 = (void *)((int)pvVar6 + 1);
        } while (pvVar6 < surface);
      }
    }
LAB_00479709:
    Surface_Unlock(pvVar7);
  }
  else if ((0 < iVar4) && (iVar4 < 3)) {
    Surface_Lock(pvVar7);
    pvVar6 = (void *)0x0;
    if (surface != (void *)0x0) {
      do {
        Mem_Copy((void *)((int)pvVar6 * local_14c + local_138),
                 (void *)((int)pvVar6 * *(int *)((int)pvVar7 + 0x18) + *(int *)((int)pvVar7 + 0x5c))
                 ,(int)pvVar3 * 2);
        pvVar6 = (void *)((int)pvVar6 + 1);
      } while (pvVar6 < surface);
    }
    goto LAB_00479709;
  }
  iVar4 = (**(code_std **)(*local_8 + 0x80))(local_8,0);
  if (iVar4 == 0) {
    if ((usePalette != 0) && (*(int *)((int)g_pD3dDriver + 0x10) == 0)) {
      if (*(int *)((int)pvVar7 + 0x20) == 0) {
        local_28 = (void *)(DAT_00806408 & 0xffff);
        pvStack_24 = local_28;
      }
      else if (*(int *)((int)pvVar7 + 0x20) == 1) {
        local_28 = *(void **)((int)pvVar7 + 0x60);
        pvStack_24 = *(void **)((int)pvVar7 + 0x60);
      }
      (**(code_std **)(*local_8 + 0x74))(local_8,8,&local_28);
    }
    iVar4 = (**(code_std **)*local_8)(local_8,&DAT_004d85f0,&local_10);
    if (iVar4 == 0) {
      iVar4 = (**(code_std **)(*local_8 + 0x58))(local_8,&local_a4);
      if (iVar4 == 0) {
        Mem_Copy((void *)((int)texture + 8),&local_a4,0x6c);
        local_a0 = 0x1007;
        local_3c = 0x4005000;
        iVar4 = (**(code_std **)(*PTR_00806968 + 0x18))(PTR_00806968,&local_a4,&local_18,0);
        if (iVar4 != 0) {
          if (iVar4 != -0x7789fe84) goto LAB_0047940a;
          D3D_EvictTexture((uint)fStack_1c);
          iVar4 = (**(code_std **)(*PTR_00806968 + 0x18))(PTR_00806968,&local_a4,&local_18,0);
          if (iVar4 != 0) goto LAB_0047940a;
        }
        iVar4 = (**(code_std **)*local_18)(local_18,&DAT_004d85f0,&local_14);
        if (iVar4 == 0) {
          iVar4 = (**(code_std **)(*local_14 + 0x18))(local_14,local_10);
          if (iVar4 == 0) {
            iVar4 = (**(code_std **)(*local_14 + 0x10))(local_14,g_pD3dDevice,&local_2c);
            if (iVar4 != 0) {
              local_2c = 0;
            }
            (**(code_std **)(*local_10 + 8))(local_10);
            local_10 = (int *)0x0;
            (**(code_std **)(*local_8 + 8))(local_8);
            local_8 = (int *)0x0;
            if (local_30 != (void *)0x0) {
              Surface_Free(local_30);
            }
            *(int **)texture = local_14;
            *(int **)((int)texture + 4) = local_18;
            *(undefined4 *)((int)texture + 0x74) = local_2c;
            *(void **)((int)texture + 0x80) = pvVar3;
            *(void **)((int)texture + 0x84) = surface;
            *(float *)((int)texture + 0x88) = fStack_1c;
            *(undefined4 *)((int)texture + 0x78) = 1;
            *(undefined4 *)((int)texture + 0x8c) = DAT_004dee58;
            D3D_LinkTexture(texture);
            return 1;
          }
        }
        else {
          local_14 = (int *)0x0;
        }
      }
      else {
        local_10 = (int *)0x0;
      }
    }
    else {
      local_10 = (int *)0x0;
    }
  }
LAB_0047940a:
  if (local_8 != (int *)0x0) {
    (**(code_std **)(*local_8 + 8))(local_8);
  }
  if (local_10 != (int *)0x0) {
    (**(code_std **)(*local_10 + 8))(local_10);
  }
  if (local_30 != (void *)0x0) {
    Surface_Free(local_30);
  }
  if (local_18 != (int *)0x0) {
    (**(code_std **)(*local_18 + 8))(local_18);
  }
  if (local_14 != (int *)0x0) {
    (**(code_std **)(*local_14 + 8))(local_14);
  }
  *(undefined4 *)texture = 0;
  *(undefined4 *)((int)texture + 4) = 0;
  *(undefined4 *)((int)texture + 0x74) = 0;
  *(undefined4 *)((int)texture + 0x78) = 0;
  *(undefined4 *)((int)texture + 0x8c) = 0;
  return 0;
}
#undef fStack_1c
#undef local_10
#undef local_138
#undef local_14
#undef local_14c
#undef local_15c
#undef local_18
#undef local_20
#undef local_28
#undef local_2c
#undef local_30
#undef local_34
#undef local_38
#undef local_3c
#undef local_8
#undef local_98
#undef local_9c
#undef local_a0
#undef local_a4
#undef local_c
#undef local_f0
#undef pvStack_24


/* ---- 0x00479860  D3D_FreeAllTextures ---- */
void D3D_FreeAllTextures(void)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = g_pD3dTextureList;
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)piVar2[1];
    if (piVar1 != (int *)0x0) {
      (**(code_std **)(*piVar1 + 8))(piVar1);
      piVar2[1] = 0;
    }
    piVar1 = (int *)*piVar2;
    if (piVar1 != (int *)0x0) {
      (**(code_std **)(*piVar1 + 8))(piVar1);
      *piVar2 = 0;
    }
    piVar2[0x1e] = 0;
    piVar2[0x23] = 0;
    piVar1 = (int *)piVar2[0x25];
    piVar2[0x25] = 0;
    piVar2[0x24] = 0;
    piVar2 = piVar1;
  }
  g_pD3dTextureList = (void *)0x0;
  PTR_0080694c = (void *)0x0;
  DAT_00806944 = 0;
  *(undefined4 *)((int)g_pD3dDriver + 0x14c) = *(undefined4 *)((int)g_pD3dDriver + 0x148);
  DAT_004dee58 = 1;
  return;
}

/* ---- 0x004798e0  D3D_LinkTexture ---- */
void D3D_LinkTexture(void *param_1)

{
  if (g_pD3dTextureList == (void *)0x0) {
    PTR_0080694c = param_1;
    g_pD3dTextureList = param_1;
    *(undefined4 *)((int)param_1 + 0x90) = 0;
    *(undefined4 *)((int)param_1 + 0x94) = 0;
  }
  else {
    *(void **)((int)PTR_0080694c + 0x94) = param_1;
    *(void **)((int)param_1 + 0x90) = PTR_0080694c;
    *(undefined4 *)((int)param_1 + 0x94) = 0;
    PTR_0080694c = param_1;
  }
  DAT_00806944 = DAT_00806944 + 1;
  *(int *)((int)g_pD3dDriver + 0x14c) =
       *(int *)((int)g_pD3dDriver + 0x14c) - *(int *)((int)param_1 + 0x88);
  return;
}

/* ---- 0x00479950  D3D_UnlinkTexture ---- */
void D3D_UnlinkTexture(void *param_1)

{
  void *pvVar1;
  
  if (param_1 == g_pD3dTextureList) {
    g_pD3dTextureList = *(void **)((int)param_1 + 0x94);
    if (g_pD3dTextureList == (void *)0x0) {
      PTR_0080694c = (void *)0x0;
    }
    else {
      *(undefined4 *)((int)g_pD3dTextureList + 0x90) = 0;
      if (*(int *)((int)g_pD3dTextureList + 0x94) == 0) {
        PTR_0080694c = g_pD3dTextureList;
      }
    }
  }
  else {
    pvVar1 = *(void **)((int)param_1 + 0x90);
    if (param_1 == PTR_0080694c) {
      PTR_0080694c = pvVar1;
      *(undefined4 *)((int)pvVar1 + 0x94) = 0;
    }
    else {
      *(undefined4 *)((int)pvVar1 + 0x94) = *(undefined4 *)((int)param_1 + 0x94);
      *(undefined4 *)(*(int *)((int)param_1 + 0x94) + 0x90) = *(undefined4 *)((int)param_1 + 0x90);
    }
  }
  DAT_00806944 = DAT_00806944 + -1;
  *(int *)((int)g_pD3dDriver + 0x14c) =
       *(int *)((int)g_pD3dDriver + 0x14c) + *(int *)((int)param_1 + 0x88);
  return;
}

/* ---- 0x00479a00  D3D_SetVertexLimit ---- */
undefined4 D3D_SetVertexLimit(void)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  #define puStack_10 (*(undefined **)(_frame + (0x20 - 0x10)))
  #define puStack_c (*(undefined1 **)(_frame + (0x20 - 0xc)))
  #define local_8 (*(undefined4 *)(_frame + (0x20 - 0x8)))
  #define uStack_4 (*(undefined4 *)(_frame + (0x20 - 0x4)))
  
  piVar2 = PTR_00806968;
  puStack_c = (undefined1 *)&local_8;
  local_8 = 0;
  puStack_10 = &DAT_004d8460;
  iVar1 = (**(code_std **)*PTR_00806968)();
  if (iVar1 != 0) {
    return 0;
  }
  puStack_10 = (undefined *)0x1000;
  iVar1 = (**(code_std **)(*piVar2 + 0x5c))(piVar2,&puStack_10,local_8,uStack_4);
  if (iVar1 != 0) {
    return 0;
  }
  (**(code_std **)(*piVar2 + 8))(piVar2);
  return 1;
}
#undef local_8
#undef puStack_10
#undef puStack_c
#undef uStack_4


/* ---- 0x00479a70  D3D_TouchTexture ---- */
void D3D_TouchTexture(int param_1)

{
  *(undefined4 *)(param_1 + 0x8c) = DAT_004dee58;
  D3D_UnlinkTexture(param_1);
  D3D_LinkTexture(param_1);
  return;
}

/* ---- 0x00479aa0  D3D_ClearZBuffer ---- */
undefined4 D3D_ClearZBuffer(void)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 *puVar2;
  #define local_74 (*(int *)(_frame + (0x90 - 0x74)))
  #define local_70 (*(int *)(_frame + (0x90 - 0x70)))
  #define local_6c (*(int *)(_frame + (0x90 - 0x6c)))
  #define local_68 (*(int *)(_frame + (0x90 - 0x68)))
  #define local_64 (*(undefined4 (*)[20])(_frame + (0x90 - 0x64)))
  #define local_14 (*(uint *)(_frame + (0x90 - 0x14)))
  
  puVar2 = local_64;
  for (iVar1 = 0x19; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  local_70 = DAT_00900604;
  local_14 = -(uint)(DAT_00900534 != 0x10) & 0xffff;
  local_64[0] = 100;
  local_74 = DAT_00900600;
  local_6c = DAT_00900600 + DAT_00900608;
  local_68 = DAT_00900604 + DAT_0090060c;
  do {
    iVar1 = (**(code_std **)(*PTR_00901464 + 0x14))(PTR_00901464,&local_74,0,0,0x3000000,local_64);
    if (iVar1 == 0) {
      return 1;
    }
    if (iVar1 == -0x7789fe3e) {
      iVar1 = (**(code_std **)(*PTR_00901464 + 0x6c))(PTR_00901464);
    }
  } while (iVar1 == 0);
  return 0;
}
#undef local_14
#undef local_64
#undef local_68
#undef local_6c
#undef local_70
#undef local_74


/* ---- 0x00479b50  D3D_FindClosestDriver ---- */
uint D3D_FindClosestDriver(int *param_1,int param_2,uint param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar1 = 0;
  if (param_3 == 0) {
    return uVar1;
  }
  uVar3 = 0;
  local_4 = 0;
  if (param_3 != 0) {
    piVar4 = (int *)(param_2 + 8);
    do {
      uVar2 = 0;
      if ((param_1[1] == 0) || (piVar4[-1] == param_1[1])) {
        uVar2 = 1;
        if (((param_1[2] == 0) || (*piVar4 == param_1[2])) &&
           ((uVar2 = 2, (piVar4[7] & param_1[9]) != 0 && (uVar2 = 3, piVar4[-2] == *param_1)))) {
          return uVar1;
        }
      }
      if (uVar3 < uVar2) {
        uVar3 = uVar2;
        local_4 = uVar1;
      }
      piVar4 = piVar4 + 0x8b;
      uVar1 = uVar1 + 1;
    } while (uVar1 < param_3);
  }
  return local_4;
}
#undef local_4


/* ---- 0x00479be0  D3D_FindTextureFormat ---- */
uint D3D_FindTextureFormat(int *param_1,int param_2,uint param_3)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar2 = 0;
  if (param_3 == 0) {
    return uVar2;
  }
  local_8 = 0;
  local_4 = 0;
  if (param_3 != 0) {
    piVar3 = (int *)(param_2 + 8);
    iVar1 = *param_1;
    do {
      uVar4 = 0;
      if ((piVar3[-2] == iVar1) && (uVar4 = 1, piVar3[-1] == param_1[1])) {
        uVar4 = 2;
        if (iVar1 == 1) {
          if (((*piVar3 == param_1[2]) && (piVar3[1] == param_1[3])) && (piVar3[2] == param_1[4])) {
            return uVar2;
          }
        }
        else {
          if (iVar1 != 2) {
            return uVar2;
          }
          if (piVar3[-2] == 2) {
            uVar4 = 3;
          }
          if (((*piVar3 == param_1[2]) && (piVar3[1] == param_1[3])) &&
             ((piVar3[2] == param_1[4] && (piVar3[9] == param_1[0xb])))) {
            return uVar2;
          }
        }
      }
      if (local_8 < uVar4) {
        local_8 = uVar4;
        local_4 = uVar2;
      }
      piVar3 = piVar3 + 0x29;
      uVar2 = uVar2 + 1;
    } while (uVar2 < param_3);
  }
  return local_4;
}
#undef local_4
#undef local_8


/* ---- 0x00479cc0  D3D_SetViewportRect ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void D3D_SetViewportRect(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  DAT_00900600 = *param_1;
  iVar1 = param_1[1];
  DAT_00900580 = (float)DAT_00900600;
  DAT_00900608 = param_1[2];
  iVar3 = DAT_00900600 + DAT_00900608;
  DAT_0090060c = param_1[3];
  puVar4 = &DAT_00900580;
  DAT_00900604 = iVar1;
  for (iVar2 = 0x20; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  DAT_00900584 = (float)DAT_00900604;
  _DAT_00900540 = 0;
  _DAT_00900544 = 1;
  _DAT_009005a0 = (float)iVar3;
  _DAT_009005a4 = (float)DAT_00900604;
  _DAT_009005c4 = (float)(iVar1 + DAT_0090060c);
  _DAT_009005c0 = (float)iVar3;
  _DAT_00900550 = 0;
  _DAT_009005e4 = _DAT_009005c4;
  _DAT_009005e0 = DAT_00900580;
  _DAT_00900548 = 2;
  _DAT_0090054c = 0x8200;
  _DAT_00900554 = 0;
  _DAT_00900558 = 2;
  _DAT_0090055c = 3;
  _DAT_00900564 = 0;
  _DAT_00900560 = 0x8200;
  return;
}

/* ---- 0x00479db0  D3D_InitRenderState ---- */
/* Fills an execute buffer with the initial STATERENDER list derived from the driver capability bits
    */

undefined4 D3D_InitRenderState(void)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int *unaff_EDI;
  undefined4 *puVar5;
  undefined4 **ppuVar6;
  bool bVar7;
  int *piVar8;
  undefined4 **ppuVar9;
  #define local_4c (*(undefined4 *(*)[2])(_frame + (0x60 - 0x4c)))
  #define local_44 (*(int (*)[17])(_frame + (0x60 - 0x44)))
  
  local_44[2] = 0;
  ppuVar9 = local_4c;
  local_44[4] = 0;
  piVar8 = local_44;
  local_4c[0] = (undefined4 *)0x0;
  local_44[0] = 0x14;
  local_44[1] = 1;
  local_44[3] = 0x1000;
  (**(code_std **)(*(int *)g_pD3dDevice + 0x18))(g_pD3dDevice,piVar8,ppuVar9,0);
  (**(code_std **)(*unaff_EDI + 0x10))(unaff_EDI,&STACK0X(0xffffffac));
  puVar2 = local_4c[0];
  puVar5 = local_4c[0];
  for (iVar4 = 0x400; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  *(undefined1 *)local_4c[0] = 8;
  *(undefined1 *)((int)local_4c[0] + 1) = 8;
  *(undefined2 *)((int)local_4c[0] + 2) = 0x19;
  local_4c[0][1] = 4;
  local_4c[0][2] = g_dwD3dRenderFlags & 1;
  local_4c[0][3] = 0x11;
  local_4c[0][4] = ((g_dwD3dRenderFlags & 0x80) != 0) + 1;
  local_4c[0][5] = 0x12;
  local_4c[0][6] = ((g_dwD3dRenderFlags & 0x100) != 0) + 1;
  local_4c[0][7] = 0x1f;
  local_4c[0][8] = g_dwD3dRenderFlags >> 4 & 1;
  local_4c[0][9] = 0x20;
  local_4c[0][10] = g_dwD3dRenderFlags >> 5 & 1;
  local_4c[0][0xb] = 5;
  local_4c[0][0xc] = 0;
  local_4c[0][0xd] = 6;
  local_4c[0][0xe] = 0;
  local_4c[0][0xf] = 0x1b;
  local_4c[0][0x10] = (uint)((g_dwD3dRenderFlags & 0x600) != 0);
  if ((g_dwD3dRenderFlags & 0x600) == 0) {
    local_4c[0][0x11] = 0x15;
    local_4c[0][0x12] = 2;
    local_4c[0][0x13] = 0x13;
    local_4c[0][0x14] = 2;
    local_4c[0][0x15] = 0x14;
    local_4c[0][0x16] = 1;
  }
  else {
    uVar1 = g_dwD3dRenderFlags & 0x400;
    local_4c[0][0x11] = 0x15;
    if (uVar1 == 0) {
      local_4c[0][0x12] = 2;
    }
    else {
      local_4c[0][0x12] = 4;
    }
    local_4c[0][0x13] = 0x13;
    local_4c[0][0x14] = 5;
    local_4c[0][0x15] = 0x14;
    local_4c[0][0x16] = 6;
  }
  local_4c[0][0x17] = 0xf;
  local_4c[0][0x18] = 1;
  local_4c[0][0x19] = 0x19;
  uVar3 = D3D_FilterBitsToEnum(DAT_00900534);
  puVar2[0x1a] = uVar3;
  iVar4 = *(int *)((int)g_pD3dDriver + 0x14);
  puVar2[0x1b] = 0x21;
  if (iVar4 == 0) {
    puVar2[0x1c] = 0;
  }
  else {
    puVar2[0x1c] = 1;
  }
  puVar2[0x1d] = 9;
  puVar2[0x1e] = 2;
  puVar2[0x1f] = 0xb;
  puVar2[0x20] = ~g_dwD3dRenderFlags >> 0xf & 1;
  puVar2[0x21] = 0x1d;
  puVar2[0x22] = g_dwD3dRenderFlags >> 2 & 1;
  puVar2[0x23] = 0x1c;
  puVar2[0x24] = g_dwD3dRenderFlags >> 6 & 1;
  puVar2[0x25] = 8;
  puVar2[0x26] = 3;
  puVar2[0x27] = 0x1a;
  puVar2[0x28] = g_dwD3dRenderFlags >> 1 & 1;
  puVar2[0x29] = 2;
  puVar2[0x2a] = g_dwD3dRenderFlags >> 3 & 1;
  bVar7 = DAT_004dee60 == 0;
  puVar2[0x2b] = 7;
  if (bVar7) {
    puVar2[0x2c] = 0;
    puVar2[0x2d] = 0xe;
    puVar2[0x2e] = 0;
    puVar2[0x2f] = 0x17;
  }
  else {
    puVar2[0x2c] = 1;
    puVar2[0x2d] = 0xe;
    puVar2[0x2e] = 1;
    puVar2[0x2f] = 0x17;
  }
  uVar3 = D3D_FilterBitsToEnum(DAT_00900534);
  puVar2[0x30] = uVar3;
  puVar2[0x31] = 0x16;
  puVar2[0x32] = 1;
  *(undefined1 *)(puVar2 + 0x33) = 0xb;
  *(undefined1 *)((int)puVar2 + 0xcd) = 0;
  *(undefined2 *)((int)puVar2 + 0xce) = 0;
  (*(code_std *)(*ppuVar9)[5])(ppuVar9);
  ppuVar6 = local_4c;
  for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
    *ppuVar6 = (undefined4 *)0x0;
    ppuVar6 = ppuVar6 + 1;
  }
  local_44[2] = (int)puVar2 + (0xd0 - (int)ppuVar9);
  local_4c[0] = (undefined4 *)0x30;
  local_44[1] = 0;
  (**(code_std **)(*piVar8 + 0x18))(piVar8,local_4c);
  (**(code_std **)(*(int *)g_pD3dDevice + 0x4c))(g_pD3dDevice);
  (**(code_std **)(*(int *)g_pD3dDevice + 0x20))(g_pD3dDevice,unaff_EDI,PTR_0080660c);
  (**(code_std **)(*(int *)g_pD3dDevice + 0x50))(g_pD3dDevice);
  (**(code_std **)((*(int *)0x00000002) + 8))(2);
  DAT_00806924 = g_dwD3dRenderFlags;
  return 1;
}
#undef local_44
#undef local_4c


/* ---- 0x0047a130  D3D_CreateViewport ---- */
undefined4 D3D_CreateViewport(void)

{
  unsigned char _frame[0x70] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint *puVar5;
  #define uStack_58 (*(uint *)(_frame + (0x70 - 0x58)))
  #define auStack_40 (*(uint (*)[4])(_frame + (0x70 - 0x40)))
  #define uStack_30 (*(uint *)(_frame + (0x70 - 0x30)))
  #define fStack_2c (*(float *)(_frame + (0x70 - 0x2c)))
  #define fStack_28 (*(float *)(_frame + (0x70 - 0x28)))
  #define fStack_24 (*(float *)(_frame + (0x70 - 0x24)))
  #define fStack_20 (*(float *)(_frame + (0x70 - 0x20)))
  #define fStack_10 (*(float *)(_frame + (0x70 - 0x10)))
  #define uStack_c (*(uint *)(_frame + (0x70 - 0xc)))
  
  uStack_58 = 0;
  iVar4 = (**(code_std **)(*(int *)g_pDirect3D + 0x1c))(g_pDirect3D,&PTR_0080660c);
  if (iVar4 != 0) {
    return 0;
  }
  iVar4 = (**(code_std **)(*(int *)g_pD3dDevice + 0x24))(g_pD3dDevice,PTR_0080660c);
  fVar3 = fStack_10;
  if (iVar4 != 0) {
    return 0;
  }
  fStack_10 = (float)(uint)fStack_10;
  uStack_58 = uStack_c;
  fVar1 = fStack_10 * 0.5;
  fVar2 = (float)uStack_c * 0.5;
  puVar5 = auStack_40;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  fStack_24 = fStack_10 / (fVar1 + fVar1);
  auStack_40[0] = 0x2c;
  auStack_40[2] = 0;
  auStack_40[1] = 0;
  auStack_40[3] = (uint)fVar3;
  uStack_30 = uStack_c;
  fStack_20 = (float)uStack_c / (fVar2 + fVar2);
  fStack_2c = fVar1;
  fStack_28 = fVar2;
  iVar4 = (**(code_std **)(*PTR_0080660c + 0x14))(PTR_0080660c,auStack_40);
  if (iVar4 != 0) {
    return 0;
  }
  uStack_58 = 0;
  D3D_SetViewportRect(&uStack_58);
  return 1;
}
#undef auStack_40
#undef fStack_10
#undef fStack_20
#undef fStack_24
#undef fStack_28
#undef fStack_2c
#undef uStack_30
#undef uStack_58
#undef uStack_c


/* ---- 0x0047a240  D3D_CreateZBuffer ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 D3D_CreateZBuffer(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  _DAT_00901400 = 1;
  _DAT_00901408 = 0;
  Mem_Copy(&DAT_0090140c,(void *)((int)g_pVideoMode + 8),0x4c);
  _DAT_00901458 = 0;
  _DAT_0090145c = 0;
  PTR_00806964 = (int *)&PTR_00901464;
  puVar3 = &DAT_0090146c;
  for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  PTR_00806964[2] = 0x6c;
  PTR_00806964[3] = 0x47;
  PTR_00806964[0x1c] = 0x20000;
  PTR_00806964[5] = param_1;
  PTR_00806964[4] = param_2;
  if (*(int *)g_pD3dDriver == 0) {
    uVar2 = PTR_00806964[0x1c] | 0x800;
  }
  else {
    uVar2 = PTR_00806964[0x1c] | 0x4000;
  }
  PTR_00806964[0x1c] = uVar2;
  uVar2 = *(uint *)((int)g_pD3dDriver + 0x1f0);
  if ((uVar2 & 0x100) == 0) {
    if ((uVar2 & 0x400) == 0) {
      if ((uVar2 & 0x800) == 0) {
        return 0;
      }
      PTR_00806964[8] = 8;
    }
    else {
      PTR_00806964[8] = 0x10;
    }
  }
  else {
    PTR_00806964[8] = 0x20;
  }
  iVar1 = (**(code_std **)(*PTR_00806968 + 0x18))(PTR_00806968,PTR_00806964 + 2,PTR_00806964,0);
  if (((iVar1 == 0) &&
      (iVar1 = (**(code_std **)(*PTR_00905644 + 0xc))(PTR_00905644,*PTR_00806964), iVar1 == 0)) &&
     (iVar1 = (**(code_std **)(*(int *)*PTR_00806964 + 0x58))((int *)*PTR_00806964,PTR_00806964 + 2),
     iVar1 == 0)) {
    if ((PTR_00806964[0x1c] & 0x4000U) != 0) {
      _DAT_00901408 = 1;
    }
    return 1;
  }
  return 0;
}

/* ---- 0x0047a3b0  FUN_0047a3b0 ---- */
undefined4 __stdcall FUN_0047a3b0(int a1,int a2,int a3,int a4,int a5,int a6)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  
  if (g_dwD3dDriverCount < 4) {
    iVar1 = g_dwD3dDriverCount * 0x22c;
    iVar4 = g_dwD3dDriverCount * 0x8b;
    Mem_Copy((void *)(iVar1 + 0x900d5c),(void *)a1,0x10);
    strncpy(iVar1 + 0x900c08,a2,0x7f);
    (&DAT_00900c87)[iVar1] = 0;
    strncpy(iVar1 + 0x900b88,a3,0x7f);
    (&DAT_00900c07)[iVar1] = 0;
    if (*(int *)(a4 + 8) == 0) {
      (&DAT_00900b40)[iVar4] = 0;
      a4 = a5;
    }
    else {
      (&DAT_00900b40)[iVar4] = 1;
    }
    Mem_Copy((void *)(iVar1 + 0x900c90),(void *)a4,0xcc);
    *(undefined4 *)(&DAT_00900b64 + iVar1) = 0;
    if ((*(uint *)(&DAT_00900c98 + iVar1) & 2) != 0) {
      *(undefined4 *)(&DAT_00900b64 + iVar1) = 2;
    }
    if ((*(uint *)(&DAT_00900c98 + iVar1) & 1) != 0) {
      *(uint *)(&DAT_00900b64 + iVar1) = *(uint *)(&DAT_00900b64 + iVar1) | 1;
    }
    uVar3 = *(uint *)(&DAT_00900d14 + iVar1);
    *(uint *)(&DAT_00900b44 + iVar1) = uVar3 & 1;
    *(uint *)(&DAT_00900b48 + iVar1) = (uint)(*(int *)(&DAT_00900d30 + iVar1) != 0);
    *(uint *)(&DAT_00900b50 + iVar1) = uVar3 >> 2 & 1;
    uVar2 = *(uint *)(&DAT_00900d10 + iVar1);
    *(uint *)(&DAT_00900b5c + iVar1) = uVar3 >> 5 & 1;
    if (((uVar2 & 0x1000) == 0) && ((uVar2 & 0x2000) != 0)) {
      *(undefined4 *)(&DAT_00900b54 + iVar1) = 1;
    }
    else {
      *(undefined4 *)(&DAT_00900b54 + iVar1) = 0;
    }
    if (((((&DAT_00900d1c)[iVar1] & 8) == 0) || ((uVar2 & 0x4000) == 0)) &&
       (*(int *)(&DAT_00900b54 + iVar1) == 0)) {
      uVar5 = 0;
    }
    else {
      uVar5 = 1;
    }
    *(undefined4 *)(&DAT_00900b58 + iVar1) = uVar5;
    *(uint *)(&DAT_00900b4c + iVar1) = uVar3 >> 3 & 1;
    uVar5 = D3D_CapsToFilterBits(*(undefined4 *)(&DAT_00900d2c + iVar1));
    *(undefined4 *)(&DAT_00900b68 + iVar1) = uVar5;
    uVar5 = D3D_FilterBitsToMask(*(undefined4 *)(&DAT_00900d00 + iVar1));
    *(undefined4 *)(&DAT_00900b6c + iVar1) = uVar5;
    uVar3 = *(uint *)(&DAT_00900d3c + iVar1);
    if (uVar3 < 5) {
      uVar3 = 4;
    }
    *(uint *)(&DAT_00900b70 + iVar1) = uVar3;
    uVar3 = *(uint *)(&DAT_00900d40 + iVar1);
    if (uVar3 < 5) {
      uVar3 = 4;
    }
    *(uint *)(&DAT_00900b74 + iVar1) = uVar3;
    iVar4 = *(int *)(&DAT_00900d44 + iVar1);
    if (iVar4 == 0) {
      iVar4 = 0x100;
    }
    *(int *)(&DAT_00900b78 + iVar1) = iVar4;
    iVar4 = *(int *)(&DAT_00900d48 + iVar1);
    if (iVar4 == 0) {
      iVar4 = 0x100;
    }
    *(int *)(&DAT_00900b7c + iVar1) = iVar4;
    *(undefined4 *)(&DAT_00900b80 + iVar1) = *(undefined4 *)(&DAT_00900d34 + iVar1);
    *(undefined4 *)(&DAT_00900b84 + iVar1) = *(undefined4 *)(&DAT_00900d38 + iVar1);
    g_dwD3dDriverCount = g_dwD3dDriverCount + 1;
    return 1;
  }
  return 0;
}

/* ---- 0x0047a590  FUN_0047a590 ---- */
undefined4 __stdcall FUN_0047a590(int a1,int a2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  
  if (7 < DAT_00806930) {
    return 0;
  }
  iVar1 = DAT_00806930 * 0xa4;
  puVar2 = (undefined4 *)(&DAT_00900620 + iVar1);
  Mem_Copy((void *)(iVar1 + 0x900658),(void *)a1,0x6c);
  uVar4 = *(uint *)(a1 + 0x4c);
  if ((uVar4 & 0x20) == 0) {
    if ((uVar4 & 8) != 0) {
      return 1;
    }
    if ((uVar4 & 1) != 0) {
      *puVar2 = 2;
      *(undefined4 *)(&DAT_00900624 + iVar1) = *(undefined4 *)(a1 + 0x54);
      iVar3 = 0;
      for (uVar4 = *(uint *)(a1 + 0x58); (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_00900634 + iVar1) = iVar3;
      iVar3 = Math_Log2Int((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x58) >> ((byte)iVar3 & 0x1f))));
      *(int *)(&DAT_00900640 + iVar1) = iVar3;
      iVar3 = 0;
      for (; (uVar4 & 1) != 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_00900628 + iVar1) = iVar3;
      iVar3 = 0;
      for (uVar4 = *(uint *)(a1 + 0x5c); (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_00900638 + iVar1) = iVar3;
      iVar3 = Math_Log2Int((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x5c) >> ((byte)iVar3 & 0x1f))));
      *(int *)(&DAT_00900644 + iVar1) = iVar3;
      iVar3 = 0;
      for (; (uVar4 & 1) != 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_0090062c + iVar1) = iVar3;
      iVar3 = 0;
      for (uVar4 = *(uint *)(a1 + 0x60); (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_0090063c + iVar1) = iVar3;
      iVar3 = Math_Log2Int((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x60) >> ((byte)iVar3 & 0x1f))));
      *(int *)(&DAT_00900648 + iVar1) = iVar3;
      iVar3 = 0;
      for (; (uVar4 & 1) != 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_00900630 + iVar1) = iVar3;
      iVar3 = 0;
      for (uVar4 = *(uint *)(a1 + 100); (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_00900650 + iVar1) = iVar3;
      iVar3 = Math_Log2Int((int)(0xff / (ulonglong)(*(uint *)(a1 + 100) >> ((byte)iVar3 & 0x1f))));
      *(int *)(&DAT_00900654 + iVar1) = iVar3;
      iVar3 = 0;
      for (; (uVar4 & 1) != 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_0090064c + iVar1) = iVar3;
      goto LAB_0047a825;
    }
    *puVar2 = 1;
    *(undefined4 *)(&DAT_00900624 + iVar1) = *(undefined4 *)(a1 + 0x54);
    iVar3 = 0;
    for (uVar4 = *(uint *)(a1 + 0x58); (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
      iVar3 = iVar3 + 1;
    }
    *(int *)(&DAT_00900634 + iVar1) = iVar3;
    iVar3 = Math_Log2Int((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x58) >> ((byte)iVar3 & 0x1f))));
    *(int *)(&DAT_00900640 + iVar1) = iVar3;
    iVar3 = 0;
    for (; (uVar4 & 1) != 0; uVar4 = uVar4 >> 1) {
      iVar3 = iVar3 + 1;
    }
    *(int *)(&DAT_00900628 + iVar1) = iVar3;
    iVar3 = 0;
    for (uVar4 = *(uint *)(a1 + 0x5c); (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
      iVar3 = iVar3 + 1;
    }
    *(int *)(&DAT_00900638 + iVar1) = iVar3;
    iVar3 = Math_Log2Int((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x5c) >> ((byte)iVar3 & 0x1f))));
    *(int *)(&DAT_00900644 + iVar1) = iVar3;
    iVar3 = 0;
    for (; (uVar4 & 1) != 0; uVar4 = uVar4 >> 1) {
      iVar3 = iVar3 + 1;
    }
    *(int *)(&DAT_0090062c + iVar1) = iVar3;
    iVar3 = 0;
    for (uVar4 = *(uint *)(a1 + 0x60); (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
      iVar3 = iVar3 + 1;
    }
    *(int *)(&DAT_0090063c + iVar1) = iVar3;
    iVar3 = Math_Log2Int((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x60) >> ((byte)iVar3 & 0x1f))));
    *(int *)(&DAT_00900648 + iVar1) = iVar3;
    iVar3 = 0;
    for (; (uVar4 & 1) != 0; uVar4 = uVar4 >> 1) {
      iVar3 = iVar3 + 1;
    }
    *(int *)(&DAT_00900630 + iVar1) = iVar3;
  }
  else {
    *(undefined4 *)(&DAT_00900624 + iVar1) = 8;
    *puVar2 = 0;
    *(undefined4 *)(&DAT_00900634 + iVar1) = 0;
    *(undefined4 *)(&DAT_00900640 + iVar1) = 0;
    *(undefined4 *)(&DAT_00900628 + iVar1) = 0;
    *(undefined4 *)(&DAT_00900638 + iVar1) = 0;
    *(undefined4 *)(&DAT_00900644 + iVar1) = 0;
    *(undefined4 *)(&DAT_0090062c + iVar1) = 0;
    *(undefined4 *)(&DAT_0090063c + iVar1) = 0;
    *(undefined4 *)(&DAT_00900648 + iVar1) = 0;
    *(undefined4 *)(&DAT_00900630 + iVar1) = 0;
  }
  *(undefined4 *)(&DAT_00900650 + iVar1) = 0;
  *(undefined4 *)(&DAT_00900654 + iVar1) = 0;
  *(undefined4 *)(&DAT_0090064c + iVar1) = 0;
LAB_0047a825:
  DAT_00806930 = DAT_00806930 + 1;
  return 1;
}

/* ---- 0x0047a850  D3D_CapsToFilterBits ---- */
byte D3D_CapsToFilterBits(uint param_1)

{
  byte bVar1;
  
  bVar1 = (param_1 & 0x4000) != 0;
  if ((param_1 & 0x2000) != 0) {
    bVar1 = bVar1 | 2;
  }
  if ((param_1 & 0x1000) != 0) {
    bVar1 = bVar1 | 4;
  }
  if ((param_1 & 0x800) != 0) {
    bVar1 = bVar1 | 8;
  }
  if ((param_1 & 0x400) != 0) {
    bVar1 = bVar1 | 0x10;
  }
  if ((param_1 & 0x200) != 0) {
    bVar1 = bVar1 | 0x20;
  }
  if ((param_1 & 0x100) != 0) {
    bVar1 = bVar1 | 0x40;
  }
  return bVar1;
}

/* ---- 0x0047a890  D3D_FilterBitsToMask ---- */
byte D3D_FilterBitsToMask(byte param_1)

{
  byte bVar1;
  
  bVar1 = (param_1 & 1) != 0;
  if ((param_1 & 4) != 0) {
    bVar1 = bVar1 | 4;
  }
  if ((param_1 & 2) != 0) {
    bVar1 = bVar1 | 2;
  }
  if ((param_1 & 8) != 0) {
    bVar1 = bVar1 | 8;
  }
  if ((param_1 & 0x10) != 0) {
    bVar1 = bVar1 | 0x10;
  }
  if ((param_1 & 0x20) != 0) {
    bVar1 = bVar1 | 0x20;
  }
  if ((param_1 & 0x40) != 0) {
    bVar1 = bVar1 | 0x40;
  }
  if ((param_1 & 0x80) != 0) {
    bVar1 = bVar1 | 0x80;
  }
  return bVar1;
}

/* ---- 0x0047a8e0  D3D_FilterBitsToEnum ---- */
byte D3D_FilterBitsToEnum(byte param_1)

{
  byte bVar1;
  
  bVar1 = (param_1 & 1) != 0;
  if ((param_1 & 4) != 0) {
    bVar1 = 3;
  }
  if ((param_1 & 2) != 0) {
    bVar1 = bVar1 | 2;
  }
  if ((param_1 & 8) != 0) {
    bVar1 = bVar1 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    bVar1 = bVar1 | 5;
  }
  if ((param_1 & 0x20) != 0) {
    bVar1 = bVar1 | 6;
  }
  if ((param_1 & 0x40) != 0) {
    bVar1 = 7;
  }
  if ((param_1 & 0x80) != 0) {
    bVar1 = bVar1 | 8;
  }
  return bVar1;
}

/* ---- 0x0047a930  D3D_EvictTexture ---- */
/* Frees a texture not used this frame (best size match) to make room, or all idle textures */

int __cdecl D3D_EvictTexture(uint size)

{
  uint uVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  uVar3 = 0xffffffff;
  puVar4 = (undefined4 *)0x0;
  for (puVar2 = g_pD3dTextureList; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)puVar2[0x25])
  {
    if (puVar2[0x23] != DAT_004dee58) {
      uVar1 = puVar2[0x22];
      if (uVar1 == size) {
        (**(code_std **)(*(int *)puVar2[1] + 8))((int *)puVar2[1]);
        (**(code_std **)(*(int *)*puVar2 + 8))((int *)*puVar2);
        puVar2[0x1e] = 0;
        puVar2[0x23] = 0;
        D3D_UnlinkTexture(puVar2);
        return 1;
      }
      if ((size < uVar1) && (uVar1 - size < uVar3)) {
        uVar3 = uVar1 - size;
        puVar4 = puVar2;
      }
    }
  }
  puVar2 = g_pD3dTextureList;
  if (puVar4 == (undefined4 *)0x0) {
    while (puVar4 = puVar2, puVar4 != (undefined4 *)0x0) {
      puVar2 = (undefined4 *)puVar4[0x25];
      if (puVar4[0x23] != DAT_004dee58) {
        (**(code_std **)(*(int *)puVar4[1] + 8))((int *)puVar4[1]);
        (**(code_std **)(*(int *)*puVar4 + 8))((int *)*puVar4);
        puVar4[0x1e] = 0;
        puVar4[0x23] = 0;
        D3D_UnlinkTexture(puVar4);
      }
    }
    (**(code_std **)(*PTR_00806968 + 0xc))(PTR_00806968);
    return 1;
  }
  (**(code_std **)(*(int *)puVar4[1] + 8))((int *)puVar4[1]);
  (**(code_std **)(*(int *)*puVar4 + 8))((int *)*puVar4);
  puVar4[0x1e] = 0;
  puVar4[0x23] = 0;
  D3D_UnlinkTexture(puVar4);
  return 1;
}
