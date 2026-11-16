/* GRIMFANDANGO.EXE :: std3d.c
 * functions 0x00478230 .. 0x0047a930 (35 functions)
 * Decompiled from the shipped binaries with Ghidra; see ../../README.md */
#include "ghidra_types.h"
#include "globals.h"
#include "functions.h"

/* ---- 0x00478230  D3D_Enumerate ---- */
/* Queries IDirect3D from DirectDraw and enumerates the 3D drivers into g_D3dDrivers (0x22c bytes
   each) */

uint __cdecl D3D_Enumerate(void)

{
  int iVar1;
  
  PTR_00806968 = DDraw_Get();
  if (PTR_00806968 == (int *)0x0) {
    return 0;
  }
  g_dwD3dRenderFlags = 0x19b3;
  UINT_004dee60 = 1;
  iVar1 = (**(code_std **)*PTR_00806968)(PTR_00806968,&DAT_004d8570,&g_pDirect3D);
  if (iVar1 != 0) {
    return 0;
  }
  g_dwD3dDriverCount = 0;
  iVar1 = (**(code_std **)(*(int *)g_pDirect3D + 0x10))(g_pDirect3D,D3D_EnumDevicesCallback,0);
  if (iVar1 != 0) {
    return 0;
  }
  if (g_dwD3dDriverCount == 0) {
    return 0;
  }
  UINT_0080696c = 1;
  return 1;
}

/* ---- 0x004782b0  D3D_Release ---- */
void __cdecl D3D_Release(void)

{
  if (g_pDirect3D != (void *)0x0) {
    (**(code_std **)(*(int *)g_pDirect3D + 8))(g_pDirect3D);
  }
  UINT_0080696c = 0;
  return;
}

/* ---- 0x004782d0  D3D_IsAvailable ---- */
uint __cdecl D3D_IsAvailable(void)

{
  return UINT_0080696c;
}

/* ---- 0x004782e0  D3D_SelectDriver ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Creates the Direct3D device, z-buffer, viewport, execute buffer and picks the texture formats */

int __cdecl D3D_SelectDriver(uint driverIdx,int useZBuffer)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  int *piVar3;
  ColorFormat *pCVar4;
  #define pvStack_ac (*(void **)(_frame + (0xc0 - 0xac)))
  #define pcStack_a8 (*(code_std **)(_frame + (0xc0 - 0xa8)))
  #define uStack_a4 (*(undefined4 *)(_frame + (0xc0 - 0xa4)))
  #define piStack_a0 (*(int **)(_frame + (0xc0 - 0xa0)))
  #define VStack_74 (*(VBufferFormat *)(_frame + (0xc0 - 0x74)))
  
  if (UINT_00806970 != 0) {
    return 0;
  }
  if (g_dwD3dDriverCount <= driverIdx) {
    return 0;
  }
  UINT_00900530 = driverIdx;
  g_pStd3D_CurDevice = g_aStd3DDevices + driverIdx;
  if (((useZBuffer == 0) || (g_aStd3DDevices[driverIdx].nHasZBuffer == 0)) ||
     ((g_dwD3dRenderFlags & 0x1800) == 0)) {
    UINT_004dee60 = 0;
  }
  else {
    UINT_004dee60 = 1;
    piStack_a0 = (int *)0x478388;
    uVar1 = D3D_CreateZBuffer((g_pVideoMode->format).nWidth,(g_pVideoMode->format).nHeight);
    if (uVar1 == 0) {
      return 0;
    }
    UINT_00900534 = (-(uint)((g_pStd3D_CurDevice->dwCaps & 0x10) != 0) & 0xe) + 2;
  }
  piStack_a0 = PTR_00905644;
  uStack_a4 = 0x4783ca;
  iVar2 = (**(code_std **)*PTR_00905644)();
  if (iVar2 != 0) {
    return 0;
  }
  UINT_00806930 = 0;
  uStack_a4 = 0;
  pcStack_a8 = D3D_EnumTextureFormatsCallback;
  pvStack_ac = g_pD3dDevice;
  iVar2 = (**(code_std **)(*(int *)g_pD3dDevice + 0x38))();
  if (iVar2 != 0) {
    return 0;
  }
  if (UINT_00806930 == 0) {
    return 0;
  }
  iVar2 = D3D_CreateViewport((g_pVideoMode->format).nWidth,(g_pVideoMode->format).nHeight);
  if (iVar2 == 0) {
    return 0;
  }
  uVar1 = D3D_InitRenderState();
  if (uVar1 == 0) {
    return 0;
  }
  _DAT_008063fc = g_pStd3D_CurDevice->dwMaxBufferSize;
  if (_DAT_008063fc == 0) {
    _DAT_008063fc = 0x10000;
  }
  _DAT_008063f0 = 0x14;
  _DAT_008063f4 = 1;
  _DAT_008063f8 = 0;
  UINT_00806400 = 0;
  g_dwStd3D_maxVertices = g_pStd3D_CurDevice->dwMaxVertexCount;
  if ((g_dwStd3D_maxVertices == 0) || (0x1ff < g_dwStd3D_maxVertices)) {
    g_dwStd3D_maxVertices = 0x200;
  }
  _DAT_00806958 = _DAT_008063fc;
  (**(code_std **)(*(int *)g_pD3dDevice + 0x18))(g_pD3dDevice,&DAT_008063f0,&g_pD3dExecuteBuffer,0);
  UINT_004dee58 = 1;
  UINT_00806944 = 0;
  D3D_SetTextureLimits
            (g_pStd3D_CurDevice->nMinTexWidth,g_pStd3D_CurDevice->nMinTexHeight,
             g_pStd3D_CurDevice->nMaxTexWidth,g_pStd3D_CurDevice->nMaxTexHeight);
  g_pD3dTextureList = (Std3DTexture *)0x0;
  PTR_0080694c = (Std3DTexture *)0x0;
  _DAT_00900568 =
       D3D_FindTextureFormat(&(g_pVideoMode->format).colorFormat.nColorMode,((unsigned)(uintptr_t)&DAT_00900620),UINT_00806930);
  UINT_00806934 = (uint)(&DAT_00900620 + _DAT_00900568 * 0xa4);
  if (g_pStd3D_CurDevice->nPalettedTextures != 0) {
    pvStack_ac = (void *)0x2;
    pcStack_a8 = (code *)0x10;
    uStack_a4 = 5;
    piStack_a0 = (int *)0x5;
    _DAT_009014d8 = D3D_FindTextureFormat((int *)&pvStack_ac,((unsigned)(uintptr_t)&DAT_00900620),UINT_00806930);
    UINT_00806938 = (uint)(&DAT_00900620 + _DAT_009014d8 * 0xa4);
    if (g_pStd3D_CurDevice->nUnknown18 == 0) {
      pvStack_ac = (void *)0x2;
      pcStack_a8 = (code *)0x10;
      uStack_a4 = 4;
      piStack_a0 = (int *)0x4;
      _DAT_0090052c = D3D_FindTextureFormat((int *)&pvStack_ac,((unsigned)(uintptr_t)&DAT_00900620),UINT_00806930);
      VStack_74.nWidth = 0x20;
      VStack_74.nHeight = 0x20;
      UINT_0080693c = (uint)(&DAT_00900620 + _DAT_0090052c * 0xa4);
      piVar3 = (int *)UINT_0080693c;
      pCVar4 = &VStack_74.colorFormat;
      for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
        pCVar4->nColorMode = *piVar3;
        piVar3 = piVar3 + 1;
        pCVar4 = (ColorFormat *)&pCVar4->nBpp;
      }
      UINT_00806950 = (uint)stdDisplay_VBufferNew(&VStack_74,1,0,0);
    }
  }
  D3D_SetVertexLimit(&g_pStd3D_CurDevice->dwTextureMemTotal,&g_pStd3D_CurDevice->nTextureMemFree);
  UINT_00806970 = 1;
  return 1;
}
#undef VStack_74
#undef pcStack_a8
#undef piStack_a0
#undef pvStack_ac
#undef uStack_a4

#endif


/* ---- 0x00478660  D3D_ReleaseDriver ---- */
void __cdecl D3D_ReleaseDriver(void)

{
  if (UINT_00806970 != 0) {
    if (UINT_00806950 != 0) {
      stdDisplay_VBufferFree((VBuffer *)UINT_00806950);
      UINT_00806950 = 0;
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
    g_pStd3D_CurDevice = (Std3DDevice *)0x0;
    UINT_00806970 = 0;
  }
  return;
}

/* ---- 0x00478700  D3D_SetTextureLimits ---- */
void __cdecl D3D_SetTextureLimits(int minW,int minH,int maxSize,int d)

{
  UINT_004dee48 = minW;
  UINT_004dee4c = minH;
  UINT_004dee50 = maxSize;
  INT_004dee54 = d;
  return;
}

/* ---- 0x00478730  std3D_StartScene ---- */
/* Original name std3D_StartScene (the remaster's GrimFandango (Linux): the only call of
   rdCache_AdvanceFrame (hardware path); the remaster's is a stub); was D3D_BeginScene. */

void __cdecl std3D_StartScene(void)

{
  if (UINT_00806974 == 0) {
    (**(code_std **)(*(int *)g_pD3dDevice + 0x4c))(g_pD3dDevice);
    UINT_00806974 = 1;
  }
  return;
}

/* ---- 0x00478750  std3D_EndScene ---- */
/* Original name std3D_EndScene (the remaster's GrimFandango (Linux): the only call of
   rdCache_FinishFrame (with acceleration) in both builds; the remaster's is a stub of its platform
   layer, named by the slot as orig-4 did for std3D_StartScene); was D3D_EndScene. */

void __cdecl std3D_EndScene(void)

{
  if (UINT_00806974 != 0) {
    (**(code_std **)(*(int *)g_pD3dDevice + 0x50))(g_pD3dDevice);
    UINT_00806974 = 0;
  }
  return;
}

/* ---- 0x00478770  D3D_BeginExecuteBuffer ---- */
uint __cdecl D3D_BeginExecuteBuffer(void)

{
  int iVar1;
  
  UINT_0080695c = 0;
  UINT_004dee58 = UINT_004dee58 + 1;
  UINT_00806960 = 0;
  UINT_004dee5c = 1;
  iVar1 = (**(code_std **)(*(int *)g_pD3dExecuteBuffer + 0x10))(g_pD3dExecuteBuffer,&DAT_008063f0);
  if (iVar1 != 0) {
    return 0;
  }
  UINT_008063ec = UINT_00806400;
  PTR_00806918 = (int *)UINT_00806400;
  return 1;
}

/* ---- 0x004787d0  std3D_AddRenderListVertices ---- */
/* Copies 32-byte TLVERTEX records into the execute buffer Original name std3D_AddRenderListVertices
   (the remaster's GrimFandango (Linux): the (vertices, count) call of rdCache_DrawRenderList); was
   D3D_AddVertices. */

int __cdecl std3D_AddRenderListVertices(void *verts,uint count)

{
  int iVar1;
  int *piVar2;
  
  if (g_dwStd3D_maxVertices < count + UINT_0080695c) {
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
  UINT_0080695c = UINT_0080695c + count;
  return 1;
}

/* ---- 0x00478840  std3D_RenderListVerticesFinish ---- */
/* Emits the PROCESSVERTICES instruction for everything added so far Original name
   std3D_RenderListVerticesFinish (the remaster's GrimFandango (Linux): aligned call in
   rdCache_DrawRenderList); was D3D_BeginInstructions. */

uint __cdecl std3D_RenderListVerticesFinish(void)

{
  UINT_0080691c = (uint)PTR_00806918;
  *(undefined1 *)PTR_00806918 = 9;
  *(undefined1 *)((int)PTR_00806918 + 1) = 0x10;
  *(undefined2 *)((int)PTR_00806918 + 2) = 1;
  PTR_00806918 = PTR_00806918 + 1;
  *PTR_00806918 = 2;
  *(undefined2 *)(PTR_00806918 + 1) = 0;
  *(undefined2 *)((int)PTR_00806918 + 6) = 0;
  PTR_00806918[2] = UINT_0080695c;
  PTR_00806918[3] = 0;
  PTR_00806918 = PTR_00806918 + 4;
  return 1;
}

/* ---- 0x004788c0  std3D_AddRenderListTris ---- */
/* Emits TRIANGLE instructions, grouped by texture handle, switching render state and texture as
   needed Original name std3D_AddRenderListTris (the remaster's GrimFandango (Linux): aligned call
   in rdCache_DrawRenderList); was D3D_AddTriangles. */

int __cdecl std3D_AddRenderListTris(void *tris,uint count)

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
        if (UINT_004dee5c != 0) {
          *(undefined1 *)PTR_00806918 = 8;
          *(undefined1 *)((int)PTR_00806918 + 1) = 8;
          *(undefined2 *)((int)PTR_00806918 + 2) = 1;
          PTR_00806918 = PTR_00806918 + 1;
          *PTR_00806918 = 1;
          PTR_00806918[1] = 0;
          PTR_00806918 = PTR_00806918 + 2;
          UINT_004dee5c = 0;
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
        if (*(uint *)(puVar5 + 8) != UINT_004dee5c) {
          *(undefined1 *)PTR_00806918 = 8;
          *(undefined1 *)((int)PTR_00806918 + 1) = 8;
          *(undefined2 *)((int)PTR_00806918 + 2) = 1;
          PTR_00806918 = PTR_00806918 + 1;
          *PTR_00806918 = 1;
          PTR_00806918[1] = *(int *)(uVar1 + 0x74);
          PTR_00806918 = PTR_00806918 + 2;
          UINT_004dee5c = uVar1;
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
  UINT_00806960 = UINT_00806960 + count;
  return 1;
}

/* ---- 0x00478b40  std3D_DrawRenderList ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Terminates and executes the buffer on the device
   Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
   Original name std3D_DrawRenderList (the remaster's GrimFandango (Linux): the argument-less flush
   call of rdCache_DrawRenderList (the remaster stub shares its address with
   std3D_AddRenderListVertices)); was D3D_ExecuteBuffer. */

int __cdecl std3D_DrawRenderList(void)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  undefined4 unaff_EDI;
  uint *puVar2;
  #define auStack_2c (*(uint (*)[4])(_frame + (0x40 - 0x2c)))
  #define iStack_1c (*(int *)(_frame + (0x40 - 0x1c)))
  
  *(undefined1 *)PTR_00806918 = 0xb;
  *(undefined1 *)((int)PTR_00806918 + 1) = 0;
  *(undefined2 *)((int)PTR_00806918 + 2) = 0;
  PTR_00806918 = PTR_00806918 + 1;
  iVar1 = (**(code_std **)(*(int *)g_pD3dExecuteBuffer + 0x14))(g_pD3dExecuteBuffer,unaff_EDI);
  if (iVar1 != 0) {
    return 0;
  }
  puVar2 = auStack_2c;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  auStack_2c[2] = UINT_0080695c;
  auStack_2c[3] = UINT_0080691c - UINT_008063ec;
  iStack_1c = (int)PTR_00806918 - UINT_0080691c;
  auStack_2c[0] = 0x30;
  (**(code_std **)(*(int *)g_pD3dExecuteBuffer + 0x18))(g_pD3dExecuteBuffer,auStack_2c);
  iVar1 = (**(code_std **)(*(int *)g_pD3dDevice + 0x20))
                    (g_pD3dDevice,g_pD3dExecuteBuffer,PTR_0080660c,2);
  return (uint)(iVar1 == 0);
}
#undef auStack_2c
#undef iStack_1c

#endif


/* ---- 0x00478c00  D3D_SetRenderFlags ---- */
/* Emits STATERENDER changes: 0x8000 z compare, 0x600 blending, 0x1800 filtering/perspective, 0x40
   fog */

void __cdecl D3D_SetRenderFlags(uint flags)

{
  uint uVar1;
  
  if (UINT_00806924 != flags) {
    if (((flags ^ UINT_00806924) & 0x8000) != 0) {
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
    if (((flags ^ UINT_00806924) & 0x600) != 0) {
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
    if (((flags ^ UINT_00806924) & 0x1800) != 0) {
      *(undefined1 *)PTR_00806918 = 8;
      *(undefined1 *)((int)PTR_00806918 + 1) = 8;
      *(undefined2 *)((int)PTR_00806918 + 2) = 2;
      PTR_00806918 = PTR_00806918 + 1;
      *PTR_00806918 = 0x17;
      if ((flags & 0x800) == 0) {
        PTR_00806918[1] = 8;
      }
      else {
        uVar1 = D3D_FilterBitsToEnum((byte)UINT_00900534);
        PTR_00806918[1] = uVar1;
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
    if (((flags ^ UINT_00806924) & 0x40) != 0) {
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
        PTR_00806918[1] = (UINT_008063e8 << 8 | UINT_00806610) << 8 | UINT_008061dc;
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x23;
        PTR_00806918[1] = 3;
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x24;
        PTR_00806918[1] = UINT_008061e0;
        PTR_00806918 = PTR_00806918 + 2;
        *PTR_00806918 = 0x25;
        PTR_00806918[1] = UINT_008061d8;
      }
      PTR_00806918 = PTR_00806918 + 2;
    }
    UINT_00806924 = flags;
  }
  return;
}

/* ---- 0x00479070  std3D_GetValidDimensions ---- */
/* Original name std3D_GetValidDimensions (the remaster's GrimFandango (Linux): aligned call in
   rdCache_SendFaceListToHardware); was D3D_ClampTextureSize. */

void __cdecl std3D_GetValidDimensions(uint width,uint height,uint *outWidth,uint *outHeight)

{
  if (width == 0) {
    width = 1;
  }
  else if (UINT_004dee50 < width) {
    width = UINT_004dee50;
  }
  if (height == 0) {
    height = 1;
  }
  else if (UINT_004dee50 < height) {
    height = UINT_004dee50;
  }
  if (((width < UINT_004dee48) || (height < UINT_004dee4c)) ||
     ((g_pStd3D_CurDevice->nUnknown1c != 0 && (width != height)))) {
    if ((g_pStd3D_CurDevice->nUnknown1c != 0) && (width != height)) {
      if (width <= height) {
        width = height;
      }
      *outWidth = width;
      *outHeight = width;
      return;
    }
    if (width < UINT_004dee48) {
      width = UINT_004dee48;
    }
    if (height < UINT_004dee4c) {
      height = UINT_004dee4c;
    }
  }
  *outWidth = width;
  *outHeight = height;
  return;
}

/* ---- 0x00479110  std3D_PurgeTextureCache ---- */
/* Lua ResetTextures: frees every texture record Original name std3D_PurgeTextureCache (the
   remaster's GrimFandango (Linux): aligned call in rdCache_SendFaceListToHardware); was
   D3D_ResetTextures. */

void __cdecl std3D_PurgeTextureCache(void)

{
  while (g_pD3dTextureList != (Std3DTexture *)0x0) {
    (**(code_std **)(**(int **)&g_pD3dTextureList->field_0x4 + 8))
              (*(int **)&g_pD3dTextureList->field_0x4);
    (**(code_std **)(**(int **)g_pD3dTextureList + 8))(*(int **)g_pD3dTextureList);
    g_pD3dTextureList->nValid = 0;
    g_pD3dTextureList->dwFrameStamp = 0;
    D3D_UnlinkTexture(g_pD3dTextureList);
  }
  return;
}

/* ---- 0x00479170  std3D_AddToTextureCache ---- */
/* Builds a 0x98-byte texture record {sysSurface, vidSurface, ..., +0x74 handle, +0x78 valid, +0x80
   w, +0x88 h, +0x88 size, +0x8c frameStamp, +0x90 prev, +0x94 next}; scales to the driver's size
   limits and converts 8-bit sources to 16-bit Original name std3D_AddToTextureCache (the remaster's
   GrimFandango (Linux): aligned call in rdMaterial_AddToTextureCache); was D3D_CreateTexture. */

int __cdecl
std3D_AddToTextureCache(VBuffer *surface,Std3DTexture *texture,int usePalette,int colorKey)

{
  unsigned char _frame[0x40] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  ushort *puVar2;
  undefined2 *puVar3;
  VBuffer *pVVar4;
  VBuffer *pVVar5;
  int iVar6;
  byte *pbVar7;
  VBuffer *pVVar8;
  uint size;
  VBufferFormat *pVVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  VBufferFormat *pVVar13;
  int x;
  DDSurfaceDesc *pDVar14;
  DDSurfaceDesc lockDesc;
  VBufferFormat format;
  DDSurfaceDesc ddsd;
  float local_38;
  uint local_34;
  uint local_30;
  #define local_2c (*(uint *)(_frame + (0x40 - 0x2c)))
  uint aColorKey [2];
  #define iStack_1c (*(int *)(_frame + (0x40 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x40 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x40 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x40 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x40 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x40 - 0x8)))
  
  pVVar4 = (VBuffer *)(surface->format).nWidth;
  local_8 = 0;
  local_18 = 0;
  local_10 = 0;
  local_14 = 0;
  local_30 = 0;
  if (pVVar4 == (VBuffer *)0x0) {
    pVVar4 = (VBuffer *)0x1;
  }
  else if ((VBuffer *)0x100 < pVVar4) {
    pVVar4 = (VBuffer *)0x100;
  }
  pVVar8 = (VBuffer *)(surface->format).nHeight;
  if (pVVar8 == (VBuffer *)0x0) {
    pVVar8 = (VBuffer *)0x1;
  }
  else if ((VBuffer *)0x100 < pVVar8) {
    pVVar8 = (VBuffer *)0x100;
  }
  local_c = (uint)pVVar4;
  if (((pVVar4 < UINT_004dee48) || (pVVar8 < UINT_004dee4c)) ||
     ((pVVar5 = surface, g_pStd3D_CurDevice->nUnknown1c != 0 && (pVVar4 != pVVar8)))) {
    pVVar9 = &surface->format;
    pVVar13 = &format;
    for (iVar6 = 0x13; iVar6 != 0; iVar6 = iVar6 + -1) {
      pVVar13->nWidth = pVVar9->nWidth;
      pVVar9 = (VBufferFormat *)&pVVar9->nHeight;
      pVVar13 = (VBufferFormat *)&pVVar13->nHeight;
    }
    if ((g_pStd3D_CurDevice->nUnknown1c == 0) || (pVVar4 == pVVar8)) {
      if (pVVar4 < UINT_004dee48) {
        pVVar4 = (VBuffer *)UINT_004dee48;
      }
      pVVar5 = pVVar8;
      if (pVVar8 < UINT_004dee4c) {
        pVVar5 = (VBuffer *)UINT_004dee4c;
      }
    }
    else {
      pVVar5 = pVVar4;
      if (pVVar4 <= pVVar8) {
        pVVar4 = pVVar8;
        pVVar5 = pVVar8;
      }
    }
    aColorKey[0] = local_c;
    aColorKey[1] = 0;
    iVar6 = (int)ROUND_DOWN(PUN(float,pVVar4) / (float)(int)local_c - -0.5f);
    iStack_1c = (int)ROUND_DOWN(PUN(float,pVVar5) / (float)(int)pVVar8 - -0.5f);
    format.nWidth = format.nWidth * iVar6;
    format.nHeight = format.nHeight * iStack_1c;
    pVVar5 = stdDisplay_VBufferNew(&format,0,0,0);
    if (iStack_1c != 0) {
      local_34 = 0;
      do {
        if (iVar6 != 0) {
          x = 0;
          iVar10 = iVar6;
          do {
            Surface_Blit(pVVar5,surface,x,local_34,(int *)0x0,0);
            x = x + local_c;
            iVar10 = iVar10 + -1;
          } while (iVar10 != 0);
        }
        local_34 = (int)&pVVar8->nType + local_34;
        iStack_1c = iStack_1c + -1;
      } while (iStack_1c != 0);
    }
    local_c = format.nWidth;
    surface = (VBuffer *)format.nHeight;
    pVVar8 = surface;
    local_30 = (uint)pVVar5;
  }
  surface = pVVar8;
  size = (int)surface * local_c;
  if ((usePalette == 0) || (g_pStd3D_CurDevice->nPalettedTextures == 0)) {
    if (colorKey == 0) {
      *(undefined4 *)&texture->field_0x7c = 0;
      uVar11 = UINT_00806934;
    }
    else {
      *(undefined4 *)&texture->field_0x7c = 1;
      uVar11 = UINT_0080693c;
    }
  }
  else {
    *(undefined4 *)&texture->field_0x7c = 1;
    uVar11 = UINT_00806938;
    if (colorKey != 0) {
      uVar11 = UINT_0080693c;
    }
  }
  Mem_Copy(&ddsd,(void *)(uVar11 + 0x38),0x6c);
  uVar11 = local_c;
  ddsd.dwHeight = (uint)surface;
  ddsd.dwSize = 0x6c;
  ddsd.dwFlags = 0x1007;
  ddsd.dwCaps = 0x1800;
  ddsd.dwWidth = local_c;
  iVar6 = (**(code_std **)(*PTR_00806968 + 0x18))(PTR_00806968,&ddsd,&local_8,0);
  if (iVar6 != 0) {
    local_8 = 0;
    goto LAB_0047940a;
  }
  pDVar14 = &lockDesc;
  for (iVar6 = 0x1b; iVar6 != 0; iVar6 = iVar6 + -1) {
    pDVar14->dwSize = 0;
    pDVar14 = (DDSurfaceDesc *)&pDVar14->dwFlags;
  }
  lockDesc.dwSize = 0x6c;
  iVar6 = (**(code_std **)(*(int *)local_8 + 100))(local_8,0,&lockDesc,1,0);
  if (iVar6 != 0) goto LAB_0047940a;
  iVar6 = (pVVar5->format).colorFormat.nColorMode;
  if (iVar6 == 0) {
    stdDisplay_VBufferLock(pVVar5);
    if ((usePalette == 0) || (g_pStd3D_CurDevice->nPalettedTextures == 0)) {
      if (colorKey == 0) {
        pVVar4 = (VBuffer *)0x0;
        if (surface != (VBuffer *)0x0) {
          do {
            pbVar7 = (byte *)((int)pVVar4 * (pVVar5->format).nPitch + (int)pVVar5->pPixels);
            puVar2 = (ushort *)((int)pVVar4 * lockDesc.nPitch + (int)lockDesc.pSurface);
            uVar12 = uVar11;
            for (; uVar12 != 0; uVar12 = uVar12 - 1) {
              bVar1 = *pbVar7;
              pbVar7 = pbVar7 + 1;
              *puVar2 = g_awStd3D_Palette16[bVar1];
              puVar2 = puVar2 + 1;
              uVar11 = local_c;
            }
            pVVar4 = (VBuffer *)((int)&pVVar4->nType + 1);
          } while (pVVar4 < surface);
        }
      }
      else {
        pVVar4 = (VBuffer *)0x0;
        if (surface != (VBuffer *)0x0) {
          do {
            pbVar7 = (byte *)((int)pVVar4 * (pVVar5->format).nPitch + (int)pVVar5->pPixels);
            puVar3 = (undefined2 *)((int)pVVar4 * lockDesc.nPitch + (int)lockDesc.pSurface);
            uVar12 = uVar11;
            for (; uVar12 != 0; uVar12 = uVar12 - 1) {
              bVar1 = *pbVar7;
              pbVar7 = pbVar7 + 1;
              *puVar3 = *(undefined2 *)(&DAT_00805fd8 + (uint)bVar1 * 2);
              puVar3 = puVar3 + 1;
              uVar11 = local_c;
            }
            pVVar4 = (VBuffer *)((int)&pVVar4->nType + 1);
          } while (pVVar4 < surface);
        }
      }
    }
    else if (colorKey == 0) {
      pVVar4 = (VBuffer *)0x0;
      if (surface != (VBuffer *)0x0) {
        do {
          pbVar7 = (byte *)((int)pVVar4 * (pVVar5->format).nPitch + (int)pVVar5->pPixels);
          puVar3 = (undefined2 *)((int)pVVar4 * lockDesc.nPitch + (int)lockDesc.pSurface);
          uVar12 = uVar11;
          for (; uVar12 != 0; uVar12 = uVar12 - 1) {
            bVar1 = *pbVar7;
            pbVar7 = pbVar7 + 1;
            *puVar3 = *(undefined2 *)(&DAT_008061e8 + (uint)bVar1 * 2);
            puVar3 = puVar3 + 1;
            uVar11 = local_c;
          }
          pVVar4 = (VBuffer *)((int)&pVVar4->nType + 1);
        } while (pVVar4 < surface);
      }
    }
    else {
      pVVar4 = (VBuffer *)0x0;
      if (surface != (VBuffer *)0x0) {
        do {
          pbVar7 = (byte *)((int)pVVar4 * (pVVar5->format).nPitch + (int)pVVar5->pPixels);
          puVar3 = (undefined2 *)((int)pVVar4 * lockDesc.nPitch + (int)lockDesc.pSurface);
          uVar12 = uVar11;
          for (; uVar12 != 0; uVar12 = uVar12 - 1) {
            bVar1 = *pbVar7;
            pbVar7 = pbVar7 + 1;
            *puVar3 = *(undefined2 *)(&DAT_00805fd8 + (uint)bVar1 * 2);
            puVar3 = puVar3 + 1;
            uVar11 = local_c;
          }
          pVVar4 = (VBuffer *)((int)&pVVar4->nType + 1);
        } while (pVVar4 < surface);
      }
    }
LAB_00479709:
    stdDisplay_VBufferUnlock(pVVar5);
  }
  else if ((0 < iVar6) && (iVar6 < 3)) {
    stdDisplay_VBufferLock(pVVar5);
    pVVar4 = (VBuffer *)0x0;
    if (surface != (VBuffer *)0x0) {
      do {
        Mem_Copy((void *)((int)pVVar4 * lockDesc.nPitch + (int)lockDesc.pSurface),
                 (void *)((int)pVVar4 * (pVVar5->format).nPitch + (int)pVVar5->pPixels),uVar11 * 2);
        pVVar4 = (VBuffer *)((int)&pVVar4->nType + 1);
      } while (pVVar4 < surface);
    }
    goto LAB_00479709;
  }
  iVar6 = (**(code_std **)(*(int *)local_8 + 0x80))(local_8,0);
  if (iVar6 == 0) {
    if ((usePalette != 0) && (g_pStd3D_CurDevice->nPalettedTextures == 0)) {
      iVar6 = (pVVar5->format).colorFormat.nColorMode;
      if (iVar6 == 0) {
        aColorKey[0] = PIECE(g_awStd3D_Palette16,0,4) & 0xffff;
        aColorKey[1] = aColorKey[0];
      }
      else if (iVar6 == 1) {
        aColorKey[0] = pVVar5->dwColorKey;
        aColorKey[1] = pVVar5->dwColorKey;
      }
      (**(code_std **)(*(int *)local_8 + 0x74))(local_8,8,aColorKey);
    }
    iVar6 = (*(code_std *)**(undefined4 **)local_8)(local_8,&DAT_004d85f0,&local_10);
    if (iVar6 == 0) {
      iVar6 = (**(code_std **)(*(int *)local_8 + 0x58))(local_8,&ddsd);
      if (iVar6 == 0) {
        Mem_Copy(&texture->field_0x8,&ddsd,0x6c);
        ddsd.dwFlags = 0x1007;
        ddsd.dwCaps = 0x4005000;
        iVar6 = (**(code_std **)(*PTR_00806968 + 0x18))(PTR_00806968,&ddsd,&local_18,0);
        if (iVar6 != 0) {
          if (iVar6 != -0x7789fe84) goto LAB_0047940a;
          D3D_EvictTexture(size);
          iVar6 = (**(code_std **)(*PTR_00806968 + 0x18))(PTR_00806968,&ddsd,&local_18,0);
          if (iVar6 != 0) goto LAB_0047940a;
        }
        iVar6 = (*(code_std *)**(undefined4 **)local_18)(local_18,&DAT_004d85f0,&local_14);
        if (iVar6 == 0) {
          iVar6 = (**(code_std **)(*(int *)local_14 + 0x18))(local_14,local_10);
          if (iVar6 == 0) {
            iVar6 = (**(code_std **)(*(int *)local_14 + 0x10))(local_14,g_pD3dDevice,&local_2c);
            if (iVar6 != 0) {
              local_2c = 0;
            }
            (**(code_std **)(*(int *)local_10 + 8))(local_10);
            local_10 = 0;
            (**(code_std **)(*(int *)local_8 + 8))(local_8);
            local_8 = 0;
            if (local_30 != 0) {
              stdDisplay_VBufferFree((VBuffer *)local_30);
            }
            *(uint *)texture = local_14;
            *(uint *)&texture->field_0x4 = local_18;
            texture->dwHandle = local_2c;
            *(uint *)&texture->field_0x80 = uVar11;
            *(VBuffer **)&texture->field_0x84 = surface;
            texture->nSize = size;
            texture->nValid = 1;
            texture->dwFrameStamp = UINT_004dee58;
            D3D_LinkTexture(texture);
            return 1;
          }
        }
        else {
          local_14 = 0;
        }
      }
      else {
        local_10 = 0;
      }
    }
    else {
      local_10 = 0;
    }
  }
LAB_0047940a:
  if (local_8 != 0) {
    (**(code_std **)(*(int *)local_8 + 8))(local_8);
  }
  if (local_10 != 0) {
    (**(code_std **)(*(int *)local_10 + 8))(local_10);
  }
  if (local_30 != 0) {
    stdDisplay_VBufferFree((VBuffer *)local_30);
  }
  if (local_18 != 0) {
    (**(code_std **)(*(int *)local_18 + 8))(local_18);
  }
  if (local_14 != 0) {
    (**(code_std **)(*(int *)local_14 + 8))(local_14);
  }
  *(undefined4 *)texture = 0;
  *(undefined4 *)&texture->field_0x4 = 0;
  texture->dwHandle = 0;
  texture->nValid = 0;
  texture->dwFrameStamp = 0;
  return 0;
}
#undef iStack_1c
#undef local_10
#undef local_14
#undef local_18
#undef local_2c
#undef local_8
#undef local_c


/* ---- 0x00479860  D3D_FreeAllTextures ---- */
void __cdecl D3D_FreeAllTextures(void)

{
  int *piVar1;
  Std3DTexture *pSVar2;
  Std3DTexture *pSVar3;
  
  pSVar3 = g_pD3dTextureList;
  while (pSVar3 != (Std3DTexture *)0x0) {
    piVar1 = *(int **)&pSVar3->field_0x4;
    if (piVar1 != (int *)0x0) {
      (**(code_std **)(*piVar1 + 8))(piVar1);
      *(undefined4 *)&pSVar3->field_0x4 = 0;
    }
    piVar1 = *(int **)pSVar3;
    if (piVar1 != (int *)0x0) {
      (**(code_std **)(*piVar1 + 8))(piVar1);
      *(int *)pSVar3 = 0;
    }
    pSVar3->nValid = 0;
    pSVar3->dwFrameStamp = 0;
    pSVar2 = pSVar3->pNext;
    pSVar3->pNext = (Std3DTexture *)0x0;
    pSVar3->pPrev = (Std3DTexture *)0x0;
    pSVar3 = pSVar2;
  }
  g_pD3dTextureList = (Std3DTexture *)0x0;
  PTR_0080694c = (Std3DTexture *)0x0;
  UINT_00806944 = 0;
  g_pStd3D_CurDevice->nTextureMemFree = g_pStd3D_CurDevice->dwTextureMemTotal;
  UINT_004dee58 = 1;
  return;
}

/* ---- 0x004798e0  D3D_LinkTexture ---- */
void __cdecl D3D_LinkTexture(Std3DTexture *texture)

{
  if (g_pD3dTextureList == (Std3DTexture *)0x0) {
    PTR_0080694c = texture;
    g_pD3dTextureList = texture;
    texture->pPrev = (Std3DTexture *)0x0;
    texture->pNext = (Std3DTexture *)0x0;
  }
  else {
    PTR_0080694c->pNext = texture;
    texture->pPrev = PTR_0080694c;
    texture->pNext = (Std3DTexture *)0x0;
    PTR_0080694c = texture;
  }
  UINT_00806944 = UINT_00806944 + 1;
  g_pStd3D_CurDevice->nTextureMemFree = g_pStd3D_CurDevice->nTextureMemFree - texture->nSize;
  return;
}

/* ---- 0x00479950  D3D_UnlinkTexture ---- */
void __cdecl D3D_UnlinkTexture(Std3DTexture *texture)

{
  Std3DTexture *pSVar1;
  
  if (texture == g_pD3dTextureList) {
    g_pD3dTextureList = texture->pNext;
    if (g_pD3dTextureList == (Std3DTexture *)0x0) {
      PTR_0080694c = (Std3DTexture *)0x0;
    }
    else {
      g_pD3dTextureList->pPrev = (Std3DTexture *)0x0;
      if (g_pD3dTextureList->pNext == (Std3DTexture *)0x0) {
        PTR_0080694c = g_pD3dTextureList;
      }
    }
  }
  else {
    pSVar1 = texture->pPrev;
    if (texture == PTR_0080694c) {
      PTR_0080694c = pSVar1;
      pSVar1->pNext = (Std3DTexture *)0x0;
    }
    else {
      pSVar1->pNext = texture->pNext;
      texture->pNext->pPrev = texture->pPrev;
    }
  }
  UINT_00806944 = UINT_00806944 - 1;
  g_pStd3D_CurDevice->nTextureMemFree = g_pStd3D_CurDevice->nTextureMemFree + texture->nSize;
  return;
}

/* ---- 0x00479a00  D3D_SetVertexLimit ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
uint __cdecl D3D_SetVertexLimit(uint *total,int *free)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  int *piVar2;
  #define puStack_10 (*(undefined **)(_frame + (0x20 - 0x10)))
  #define puStack_c (*(undefined1 **)(_frame + (0x20 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x20 - 0x8)))
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

#endif


/* ---- 0x00479a70  std3D_UpdateFrameCount ---- */
/* Original name std3D_UpdateFrameCount (the remaster's GrimFandango (Linux): aligned call in
   rdMaterial_AddToTextureCache); was D3D_TouchTexture. */

void __cdecl std3D_UpdateFrameCount(Std3DTexture *texture)

{
  texture->dwFrameStamp = UINT_004dee58;
  D3D_UnlinkTexture(texture);
  D3D_LinkTexture(texture);
  return;
}

/* ---- 0x00479aa0  std3D_ClearZBuffer ---- */
/* Original name std3D_ClearZBuffer (the remaster's GrimFandango (Linux): the hardware call of
   rdCamera_AdvanceFrame; the remaster's is a stub); was D3D_ClearZBuffer. */

uint __cdecl std3D_ClearZBuffer(void)

{
  unsigned char _frame[0x90] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  int iVar1;
  uint *puVar2;
  #define local_74 (*(uint *)(_frame + (0x90 - 0x74)))
  #define local_70 (*(uint *)(_frame + (0x90 - 0x70)))
  #define local_6c (*(uint *)(_frame + (0x90 - 0x6c)))
  #define local_68 (*(uint *)(_frame + (0x90 - 0x68)))
  #define local_64 (*(uint *)(_frame + (0x90 - 0x64)))
  #define local_14 (*(uint *)(_frame + (0x90 - 0x14)))
  
  puVar2 = &local_64;
  for (iVar1 = 0x19; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  local_70 = UINT_00900604;
  local_14 = -(uint)(UINT_00900534 != 0x10) & 0xffff;
  local_64 = 100;
  local_74 = UINT_00900600;
  local_6c = UINT_00900600 + UINT_00900608;
  local_68 = UINT_00900604 + UINT_0090060c;
  do {
    iVar1 = (**(code_std **)(*PTR_00901464 + 0x14))(PTR_00901464,&local_74,0,0,0x3000000,&local_64);
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
uint __cdecl D3D_FindClosestDriver(int *drivers,int count,uint flags)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  uint local_4;
  
  uVar1 = 0;
  if (flags == 0) {
    return uVar1;
  }
  uVar3 = 0;
  local_4 = 0;
  if (flags != 0) {
    piVar4 = (int *)(count + 8);
    do {
      uVar2 = 0;
      if ((drivers[1] == 0) || (piVar4[-1] == drivers[1])) {
        uVar2 = 1;
        if (((drivers[2] == 0) || (*piVar4 == drivers[2])) &&
           ((uVar2 = 2, (piVar4[7] & drivers[9]) != 0 && (uVar2 = 3, piVar4[-2] == *drivers)))) {
          return uVar1;
        }
      }
      if (uVar3 < uVar2) {
        uVar3 = uVar2;
        local_4 = uVar1;
      }
      piVar4 = piVar4 + 0x8b;
      uVar1 = uVar1 + 1;
    } while (uVar1 < flags);
  }
  return local_4;
}

/* ---- 0x00479be0  D3D_FindTextureFormat ---- */
uint __cdecl D3D_FindTextureFormat(int *formats,int count,uint bpp)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  uint local_8;
  uint local_4;
  
  uVar2 = 0;
  if (bpp == 0) {
    return uVar2;
  }
  local_8 = 0;
  local_4 = 0;
  if (bpp != 0) {
    piVar3 = (int *)(count + 8);
    iVar1 = *formats;
    do {
      uVar4 = 0;
      if ((piVar3[-2] == iVar1) && (uVar4 = 1, piVar3[-1] == formats[1])) {
        uVar4 = 2;
        if (iVar1 == 1) {
          if (((*piVar3 == formats[2]) && (piVar3[1] == formats[3])) && (piVar3[2] == formats[4])) {
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
          if (((*piVar3 == formats[2]) && (piVar3[1] == formats[3])) &&
             ((piVar3[2] == formats[4] && (piVar3[9] == formats[0xb])))) {
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
    } while (uVar2 < bpp);
  }
  return local_4;
}

/* ---- 0x00479cc0  D3D_SetViewportRect ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl D3D_SetViewportRect(uint *srcRect)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  
  UINT_00900600 = *srcRect;
  uVar1 = srcRect[1];
  FLOAT_00900580 = (float)(int)UINT_00900600;
  UINT_00900608 = srcRect[2];
  iVar3 = UINT_00900600 + UINT_00900608;
  UINT_0090060c = srcRect[3];
  pfVar4 = &FLOAT_00900580;
  UINT_00900604 = uVar1;
  for (iVar2 = 0x20; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar4 = 0.0f;
    pfVar4 = pfVar4 + 1;
  }
  FLOAT_00900584 = (float)(int)UINT_00900604;
  _DAT_00900540 = 0;
  _DAT_00900544 = 1;
  FLOAT_009005a0 = (float)iVar3;
  FLOAT_009005a4 = (float)(int)UINT_00900604;
  FLOAT_009005c4 = (float)(int)(uVar1 + UINT_0090060c);
  FLOAT_009005c0 = (float)iVar3;
  _DAT_00900550 = 0;
  FLOAT_009005e4 = FLOAT_009005c4;
  _DAT_009005e0 = FLOAT_00900580;
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
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Fills an execute buffer with the initial STATERENDER list derived from the driver capability bits
    */

uint __cdecl D3D_InitRenderState(void)

{
  unsigned char _frame[0x60] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  unsigned char _stkneg[112] __attribute__((aligned(16)));  /* the original frame below the return address */
  uint uVar1;
  uint uVar2;
  int iVar3;
  int *unaff_EDI;
  undefined4 *puVar4;
  uint *puVar5;
  bool bVar6;
  uint *puVar7;
  uint *puVar8;
  #define local_4c (*(uint *)(_frame + (0x60 - 0x4c)))
  #define local_44 (*(uint *)(_frame + (0x60 - 0x44)))
  #define local_40 (*(uint *)(_frame + (0x60 - 0x40)))
  #define local_3c (*(uint *)(_frame + (0x60 - 0x3c)))
  #define local_38 (*(uint *)(_frame + (0x60 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x60 - 0x34)))
  
  local_3c = 0;
  puVar8 = &local_4c;
  local_34 = 0;
  puVar7 = &local_44;
  local_4c = 0;
  local_44 = 0x14;
  local_40 = 1;
  local_38 = 0x1000;
  (**(code_std **)(*(int *)g_pD3dDevice + 0x18))(g_pD3dDevice,puVar7,puVar8,0);
  (**(code_std **)(*unaff_EDI + 0x10))(unaff_EDI,(_stkneg + 28));
  uVar1 = local_4c;
  puVar4 = (undefined4 *)local_4c;
  for (iVar3 = 0x400; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined1 *)local_4c = 8;
  *(undefined1 *)(local_4c + 1) = 8;
  *(undefined2 *)(local_4c + 2) = 0x19;
  *(undefined4 *)(local_4c + 4) = 4;
  *(uint *)(local_4c + 8) = g_dwD3dRenderFlags & 1;
  *(undefined4 *)(local_4c + 0xc) = 0x11;
  *(uint *)(local_4c + 0x10) = ((g_dwD3dRenderFlags & 0x80) != 0) + 1;
  *(undefined4 *)(local_4c + 0x14) = 0x12;
  *(uint *)(local_4c + 0x18) = ((g_dwD3dRenderFlags & 0x100) != 0) + 1;
  *(undefined4 *)(local_4c + 0x1c) = 0x1f;
  *(uint *)(local_4c + 0x20) = g_dwD3dRenderFlags >> 4 & 1;
  *(undefined4 *)(local_4c + 0x24) = 0x20;
  *(uint *)(local_4c + 0x28) = g_dwD3dRenderFlags >> 5 & 1;
  *(undefined4 *)(local_4c + 0x2c) = 5;
  *(undefined4 *)(local_4c + 0x30) = 0;
  *(undefined4 *)(local_4c + 0x34) = 6;
  *(undefined4 *)(local_4c + 0x38) = 0;
  *(undefined4 *)(local_4c + 0x3c) = 0x1b;
  *(uint *)(local_4c + 0x40) = (uint)((g_dwD3dRenderFlags & 0x600) != 0);
  if ((g_dwD3dRenderFlags & 0x600) == 0) {
    *(undefined4 *)(local_4c + 0x44) = 0x15;
    *(undefined4 *)(local_4c + 0x48) = 2;
    *(undefined4 *)(local_4c + 0x4c) = 0x13;
    *(undefined4 *)(local_4c + 0x50) = 2;
    *(undefined4 *)(local_4c + 0x54) = 0x14;
    *(undefined4 *)(local_4c + 0x58) = 1;
  }
  else {
    uVar2 = g_dwD3dRenderFlags & 0x400;
    *(undefined4 *)(local_4c + 0x44) = 0x15;
    if (uVar2 == 0) {
      *(undefined4 *)(local_4c + 0x48) = 2;
    }
    else {
      *(undefined4 *)(local_4c + 0x48) = 4;
    }
    *(undefined4 *)(local_4c + 0x4c) = 0x13;
    *(undefined4 *)(local_4c + 0x50) = 5;
    *(undefined4 *)(local_4c + 0x54) = 0x14;
    *(undefined4 *)(local_4c + 0x58) = 6;
  }
  *(undefined4 *)(local_4c + 0x5c) = 0xf;
  *(undefined4 *)(local_4c + 0x60) = 1;
  *(undefined4 *)(local_4c + 100) = 0x19;
  uVar2 = D3D_FilterBitsToEnum((byte)UINT_00900534);
  *(uint *)(uVar1 + 0x68) = uVar2;
  iVar3 = g_pStd3D_CurDevice->nUnknown14;
  *(undefined4 *)(uVar1 + 0x6c) = 0x21;
  if (iVar3 == 0) {
    *(undefined4 *)(uVar1 + 0x70) = 0;
  }
  else {
    *(undefined4 *)(uVar1 + 0x70) = 1;
  }
  *(undefined4 *)(uVar1 + 0x74) = 9;
  *(undefined4 *)(uVar1 + 0x78) = 2;
  *(undefined4 *)(uVar1 + 0x7c) = 0xb;
  *(uint *)(uVar1 + 0x80) = ~g_dwD3dRenderFlags >> 0xf & 1;
  *(undefined4 *)(uVar1 + 0x84) = 0x1d;
  *(uint *)(uVar1 + 0x88) = g_dwD3dRenderFlags >> 2 & 1;
  *(undefined4 *)(uVar1 + 0x8c) = 0x1c;
  *(uint *)(uVar1 + 0x90) = g_dwD3dRenderFlags >> 6 & 1;
  *(undefined4 *)(uVar1 + 0x94) = 8;
  *(undefined4 *)(uVar1 + 0x98) = 3;
  *(undefined4 *)(uVar1 + 0x9c) = 0x1a;
  *(uint *)(uVar1 + 0xa0) = g_dwD3dRenderFlags >> 1 & 1;
  *(undefined4 *)(uVar1 + 0xa4) = 2;
  *(uint *)(uVar1 + 0xa8) = g_dwD3dRenderFlags >> 3 & 1;
  bVar6 = UINT_004dee60 == 0;
  *(undefined4 *)(uVar1 + 0xac) = 7;
  if (bVar6) {
    *(undefined4 *)(uVar1 + 0xb0) = 0;
    *(undefined4 *)(uVar1 + 0xb4) = 0xe;
    *(undefined4 *)(uVar1 + 0xb8) = 0;
    *(undefined4 *)(uVar1 + 0xbc) = 0x17;
  }
  else {
    *(undefined4 *)(uVar1 + 0xb0) = 1;
    *(undefined4 *)(uVar1 + 0xb4) = 0xe;
    *(undefined4 *)(uVar1 + 0xb8) = 1;
    *(undefined4 *)(uVar1 + 0xbc) = 0x17;
  }
  uVar2 = D3D_FilterBitsToEnum((byte)UINT_00900534);
  *(uint *)(uVar1 + 0xc0) = uVar2;
  *(undefined4 *)(uVar1 + 0xc4) = 0x16;
  *(undefined4 *)(uVar1 + 200) = 1;
  *(undefined1 *)(uVar1 + 0xcc) = 0xb;
  *(undefined1 *)(uVar1 + 0xcd) = 0;
  *(undefined2 *)(uVar1 + 0xce) = 0;
  (**(code_std **)(*puVar8 + 0x14))(puVar8);
  puVar5 = &local_4c;
  for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  local_3c = (uVar1 + 0xd0) - (int)puVar8;
  local_4c = 0x30;
  local_40 = 0;
  (**(code_std **)(*puVar7 + 0x18))(puVar7,&local_4c);
  (**(code_std **)(*(int *)g_pD3dDevice + 0x4c))(g_pD3dDevice);
  (**(code_std **)(*(int *)g_pD3dDevice + 0x20))(g_pD3dDevice,unaff_EDI,PTR_0080660c);
  (**(code_std **)(*(int *)g_pD3dDevice + 0x50))(g_pD3dDevice);
  (**(code_std **)((*(int *)0x00000002) + 8))(2);
  UINT_00806924 = g_dwD3dRenderFlags;
  return 1;
}
#undef local_34
#undef local_38
#undef local_3c
#undef local_40
#undef local_44
#undef local_4c

#endif


/* ---- 0x0047a130  D3D_CreateViewport ---- */
/* replaced by the hand-written version in build/overrides.c */
#if 0
/* Ported to C (build/overrides_asm_o2.c): differential test, 0 differences (docs/notes/asm_o2.md).
    */

undefined4 __cdecl D3D_CreateViewport(uint width,uint height)

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
  fStack_10 = (float)PUN(uint,(float)fStack_10);
  uStack_58 = uStack_c;
  fVar1 = fStack_10 * 0.5f;
  fVar2 = (float)uStack_c * 0.5f;
  puVar5 = auStack_40;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  fStack_24 = fStack_10 / (fVar1 + fVar1);
  auStack_40[0] = 0x2c;
  auStack_40[2] = 0;
  auStack_40[1] = 0;
  auStack_40[3] = PUN(uint,(float)fVar3);
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

#endif


/* ---- 0x0047a240  D3D_CreateZBuffer ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl D3D_CreateZBuffer(int width,int height)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  
  _DAT_00901400 = 1;
  _DAT_00901408 = 0;
  Mem_Copy(&DAT_0090140c,&g_pVideoMode->format,0x4c);
  _DAT_00901458 = 0;
  _DAT_0090145c = 0;
  PTR_00806964 = (int *)&PTR_00901464;
  puVar3 = &UINT_0090146c;
  for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  PTR_00806964[2] = 0x6c;
  PTR_00806964[3] = 0x47;
  PTR_00806964[0x1c] = 0x20000;
  PTR_00806964[5] = width;
  PTR_00806964[4] = height;
  if (g_pStd3D_CurDevice->nHardware == 0) {
    uVar2 = PTR_00806964[0x1c] | 0x800;
  }
  else {
    uVar2 = PTR_00806964[0x1c] | 0x4000;
  }
  PTR_00806964[0x1c] = uVar2;
  uVar2 = g_pStd3D_CurDevice->dwZBufferBitDepths;
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

/* ---- 0x0047a3b0  D3D_EnumDevicesCallback ---- */
/* IDirect3D::EnumDevices callback of D3D_Enumerate: stores GUID, name, description and caps of up
   to 4 3D drivers. */

undefined * __stdcall D3D_EnumDevicesCallback(int a1,int a2,int a3,int a4,int a5,int a6)

{
  Std3DDevice *pSVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar3 = g_dwD3dDriverCount;
  if (g_dwD3dDriverCount < 4) {
    pSVar1 = g_aStd3DDevices + g_dwD3dDriverCount;
    Mem_Copy(g_aStd3DDevices[g_dwD3dDriverCount].aGuid,(void *)a1,0x10);
    strncpy((uint *)&g_aStd3DDevices[uVar3].field_0xc8,(uint *)a2,0x7f);
    g_aStd3DDevices[uVar3].field_0x147 = 0;
    strncpy((uint *)&g_aStd3DDevices[uVar3].field_0x48,(uint *)a3,0x7f);
    g_aStd3DDevices[uVar3].field_0xc7 = 0;
    if (*(int *)(a4 + 8) == 0) {
      pSVar1->nHardware = 0;
      a4 = a5;
    }
    else {
      pSVar1->nHardware = 1;
    }
    Mem_Copy(&g_aStd3DDevices[uVar3].field_0x150,(void *)a4,0xcc);
    uVar4 = *(uint *)&g_aStd3DDevices[uVar3].field_0x158;
    *(undefined4 *)&g_aStd3DDevices[uVar3].field_0x24 = 0;
    if ((uVar4 & 2) != 0) {
      *(undefined4 *)&g_aStd3DDevices[uVar3].field_0x24 = 2;
    }
    if ((uVar4 & 1) != 0) {
      *(uint *)&g_aStd3DDevices[uVar3].field_0x24 = *(uint *)&g_aStd3DDevices[uVar3].field_0x24 | 1;
    }
    uVar4 = *(uint *)&g_aStd3DDevices[uVar3].field_0x1d4;
    *(uint *)&g_aStd3DDevices[uVar3].field_0x4 = uVar4 & 1;
    g_aStd3DDevices[uVar3].nHasZBuffer = (uint)(g_aStd3DDevices[uVar3].dwZBufferBitDepths != 0);
    g_aStd3DDevices[uVar3].nPalettedTextures = uVar4 >> 2 & 1;
    uVar2 = *(uint *)&g_aStd3DDevices[uVar3].field_0x1d0;
    g_aStd3DDevices[uVar3].nUnknown1c = uVar4 >> 5 & 1;
    if (((uVar2 & 0x1000) == 0) && ((uVar2 & 0x2000) != 0)) {
      g_aStd3DDevices[uVar3].nUnknown14 = 1;
    }
    else {
      g_aStd3DDevices[uVar3].nUnknown14 = 0;
    }
    if ((((g_aStd3DDevices[uVar3].field_0x1dc & 8) == 0) || ((uVar2 & 0x4000) == 0)) &&
       (g_aStd3DDevices[uVar3].nUnknown14 == 0)) {
      iVar5 = 0;
    }
    else {
      iVar5 = 1;
    }
    uVar2 = *(uint *)&g_aStd3DDevices[uVar3].field_0x1ec;
    g_aStd3DDevices[uVar3].nUnknown18 = iVar5;
    *(uint *)&g_aStd3DDevices[uVar3].field_0xc = uVar4 >> 3 & 1;
    uVar4 = D3D_CapsToFilterBits(uVar2);
    *(uint *)&g_aStd3DDevices[uVar3].field_0x28 = uVar4;
    uVar4 = D3D_FilterBitsToMask((byte)*(undefined4 *)&g_aStd3DDevices[uVar3].field_0x1c0);
    g_aStd3DDevices[uVar3].dwCaps = uVar4;
    uVar4 = *(uint *)&g_aStd3DDevices[uVar3].field_0x1fc;
    if (uVar4 < 5) {
      uVar4 = 4;
    }
    g_aStd3DDevices[uVar3].nMinTexWidth = uVar4;
    uVar4 = *(uint *)&g_aStd3DDevices[uVar3].field_0x200;
    if (uVar4 < 5) {
      uVar4 = 4;
    }
    g_aStd3DDevices[uVar3].nMinTexHeight = uVar4;
    iVar5 = *(int *)&g_aStd3DDevices[uVar3].field_0x204;
    if (iVar5 == 0) {
      iVar5 = 0x100;
    }
    g_aStd3DDevices[uVar3].nMaxTexWidth = iVar5;
    iVar5 = *(int *)&g_aStd3DDevices[uVar3].field_0x208;
    if (iVar5 == 0) {
      iVar5 = 0x100;
    }
    uVar4 = *(uint *)&g_aStd3DDevices[uVar3].field_0x1f4;
    uVar2 = *(uint *)&g_aStd3DDevices[uVar3].field_0x1f8;
    g_aStd3DDevices[uVar3].nMaxTexHeight = iVar5;
    g_aStd3DDevices[uVar3].dwMaxBufferSize = uVar4;
    g_aStd3DDevices[uVar3].dwMaxVertexCount = uVar2;
    g_dwD3dDriverCount = g_dwD3dDriverCount + 1;
    return (undefined *)0x1;
  }
  return (undefined *)0x0;
}

/* ---- 0x0047a590  D3D_EnumTextureFormatsCallback ---- */
/* EnumTextureFormats callback of D3D_SelectDriver: stores the RGB/palette texture formats with
   their shifts and bit counts (up to 8). */

undefined * __stdcall D3D_EnumTextureFormatsCallback(int a1,int a2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  
  if (7 < UINT_00806930) {
    return (undefined *)0x0;
  }
  iVar1 = UINT_00806930 * 0xa4;
  puVar2 = (undefined4 *)(&DAT_00900620 + iVar1);
  Mem_Copy((void *)(iVar1 + ((unsigned)(uintptr_t)&DAT_00900658)),(void *)a1,0x6c);
  uVar4 = *(uint *)(a1 + 0x4c);
  if ((uVar4 & 0x20) == 0) {
    if ((uVar4 & 8) != 0) {
      return (undefined *)0x1;
    }
    if ((uVar4 & 1) != 0) {
      *puVar2 = 2;
      *(undefined4 *)(&DAT_00900624 + iVar1) = *(undefined4 *)(a1 + 0x54);
      iVar3 = 0;
      for (uVar4 = *(uint *)(a1 + 0x58); (uVar4 & 1) == 0; uVar4 = uVar4 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *(int *)(&DAT_00900634 + iVar1) = iVar3;
      iVar3 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x58) >> ((byte)iVar3 & 0x1f))))
      ;
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
      iVar3 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x5c) >> ((byte)iVar3 & 0x1f))))
      ;
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
      iVar3 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x60) >> ((byte)iVar3 & 0x1f))))
      ;
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
      iVar3 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 100) >> ((byte)iVar3 & 0x1f))));
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
    iVar3 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x58) >> ((byte)iVar3 & 0x1f))));
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
    iVar3 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x5c) >> ((byte)iVar3 & 0x1f))));
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
    iVar3 = stdCalcBitPos((int)(0xff / (ulonglong)(*(uint *)(a1 + 0x60) >> ((byte)iVar3 & 0x1f))));
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
  UINT_00806930 = UINT_00806930 + 1;
  return (undefined *)0x1;
}

/* ---- 0x0047a850  D3D_CapsToFilterBits ---- */
uint __cdecl D3D_CapsToFilterBits(uint caps)

{
  byte bVar1;
  
  bVar1 = (caps & 0x4000) != 0;
  if ((caps & 0x2000) != 0) {
    bVar1 = bVar1 | 2;
  }
  if ((caps & 0x1000) != 0) {
    bVar1 = bVar1 | 4;
  }
  if ((caps & 0x800) != 0) {
    bVar1 = bVar1 | 8;
  }
  if ((caps & 0x400) != 0) {
    bVar1 = bVar1 | 0x10;
  }
  if ((caps & 0x200) != 0) {
    bVar1 = bVar1 | 0x20;
  }
  if ((caps & 0x100) != 0) {
    bVar1 = bVar1 | 0x40;
  }
  return (uint)bVar1;
}

/* ---- 0x0047a890  D3D_FilterBitsToMask ---- */
uint __cdecl D3D_FilterBitsToMask(byte bits)

{
  byte bVar1;
  
  bVar1 = (bits & 1) != 0;
  if ((bits & 4) != 0) {
    bVar1 = bVar1 | 4;
  }
  if ((bits & 2) != 0) {
    bVar1 = bVar1 | 2;
  }
  if ((bits & 8) != 0) {
    bVar1 = bVar1 | 8;
  }
  if ((bits & 0x10) != 0) {
    bVar1 = bVar1 | 0x10;
  }
  if ((bits & 0x20) != 0) {
    bVar1 = bVar1 | 0x20;
  }
  if ((bits & 0x40) != 0) {
    bVar1 = bVar1 | 0x40;
  }
  if ((bits & 0x80) != 0) {
    bVar1 = bVar1 | 0x80;
  }
  return (uint)bVar1;
}

/* ---- 0x0047a8e0  D3D_FilterBitsToEnum ---- */
uint __cdecl D3D_FilterBitsToEnum(byte bits)

{
  byte bVar1;
  
  bVar1 = (bits & 1) != 0;
  if ((bits & 4) != 0) {
    bVar1 = 3;
  }
  if ((bits & 2) != 0) {
    bVar1 = bVar1 | 2;
  }
  if ((bits & 8) != 0) {
    bVar1 = bVar1 | 4;
  }
  if ((bits & 0x10) != 0) {
    bVar1 = bVar1 | 5;
  }
  if ((bits & 0x20) != 0) {
    bVar1 = bVar1 | 6;
  }
  if ((bits & 0x40) != 0) {
    bVar1 = 7;
  }
  if ((bits & 0x80) != 0) {
    bVar1 = bVar1 | 8;
  }
  return (uint)bVar1;
}

/* ---- 0x0047a930  D3D_EvictTexture ---- */
/* Frees a texture not used this frame (best size match) to make room, or all idle textures */

int __cdecl D3D_EvictTexture(uint size)

{
  uint uVar1;
  Std3DTexture *pSVar2;
  uint uVar3;
  Std3DTexture *pSVar4;
  uint local_4;
  
  uVar3 = 0xffffffff;
  pSVar4 = (Std3DTexture *)0x0;
  for (pSVar2 = g_pD3dTextureList; pSVar2 != (Std3DTexture *)0x0; pSVar2 = pSVar2->pNext) {
    if (pSVar2->dwFrameStamp != UINT_004dee58) {
      uVar1 = pSVar2->nSize;
      if (uVar1 == size) {
        (**(code_std **)(**(int **)&pSVar2->field_0x4 + 8))(*(int **)&pSVar2->field_0x4);
        (**(code_std **)(**(int **)pSVar2 + 8))(*(int **)pSVar2);
        pSVar2->nValid = 0;
        pSVar2->dwFrameStamp = 0;
        D3D_UnlinkTexture(pSVar2);
        return 1;
      }
      if ((size < uVar1) && (uVar1 - size < uVar3)) {
        uVar3 = uVar1 - size;
        pSVar4 = pSVar2;
      }
    }
  }
  pSVar2 = g_pD3dTextureList;
  if (pSVar4 == (Std3DTexture *)0x0) {
    while (pSVar4 = pSVar2, pSVar4 != (Std3DTexture *)0x0) {
      pSVar2 = pSVar4->pNext;
      if (pSVar4->dwFrameStamp != UINT_004dee58) {
        (**(code_std **)(**(int **)&pSVar4->field_0x4 + 8))(*(int **)&pSVar4->field_0x4);
        (**(code_std **)(**(int **)pSVar4 + 8))(*(int **)pSVar4);
        pSVar4->nValid = 0;
        pSVar4->dwFrameStamp = 0;
        D3D_UnlinkTexture(pSVar4);
      }
    }
    (**(code_std **)(*PTR_00806968 + 0xc))(PTR_00806968);
    return 1;
  }
  (**(code_std **)(**(int **)&pSVar4->field_0x4 + 8))(*(int **)&pSVar4->field_0x4);
  (**(code_std **)(**(int **)pSVar4 + 8))(*(int **)pSVar4);
  pSVar4->nValid = 0;
  pSVar4->dwFrameStamp = 0;
  D3D_UnlinkTexture(pSVar4);
  return 1;
}


/* ---- data only this file names (tools/datagen.py: place_in_modules) ---- */
#ifndef GRIM_DATA
#define GRIM_DATA(k) __attribute__((section(".data$grim_" k), aligned(1), no_reorder))
#endif
extern unsigned char grim_def_DAT_004d8460[176] __asm__("_DAT_004d8460");
extern unsigned char grim_def_DAT_004d8570[128] __asm__("_DAT_004d8570");
extern unsigned char grim_def_DAT_004d85f0[176] __asm__("_DAT_004d85f0");
extern unsigned char grim_def_DAT_008063f0[4] __asm__("_DAT_008063f0");
extern unsigned char grim_def_DAT_008063f4[4] __asm__("_DAT_008063f4");
extern unsigned char grim_def_DAT_008063f8[4] __asm__("_DAT_008063f8");
extern unsigned char grim_def_DAT_008063fc[4] __asm__("_DAT_008063fc");
extern unsigned char grim_def_DAT_00806958[4] __asm__("_DAT_00806958");
extern unsigned char grim_def_DAT_0090052c[4] __asm__("_DAT_0090052c");
extern unsigned char grim_def_DAT_00900540[4] __asm__("_DAT_00900540");
extern unsigned char grim_def_DAT_00900544[4] __asm__("_DAT_00900544");
extern unsigned char grim_def_DAT_00900548[4] __asm__("_DAT_00900548");
extern unsigned char grim_def_DAT_0090054c[4] __asm__("_DAT_0090054c");
extern unsigned char grim_def_DAT_00900550[4] __asm__("_DAT_00900550");
extern unsigned char grim_def_DAT_00900554[4] __asm__("_DAT_00900554");
extern unsigned char grim_def_DAT_00900558[4] __asm__("_DAT_00900558");
extern unsigned char grim_def_DAT_0090055c[4] __asm__("_DAT_0090055c");
extern unsigned char grim_def_DAT_00900560[4] __asm__("_DAT_00900560");
extern unsigned char grim_def_DAT_00900564[4] __asm__("_DAT_00900564");
extern unsigned char grim_def_DAT_00900568[24] __asm__("_DAT_00900568");
extern unsigned char grim_def_DAT_009005e0[4] __asm__("_DAT_009005e0");
extern unsigned char grim_def_DAT_00900620[4] __asm__("_DAT_00900620");
extern unsigned char grim_def_DAT_00900624[4] __asm__("_DAT_00900624");
extern unsigned char grim_def_DAT_00900628[4] __asm__("_DAT_00900628");
extern unsigned char grim_def_DAT_0090062c[4] __asm__("_DAT_0090062c");
extern unsigned char grim_def_DAT_00900630[4] __asm__("_DAT_00900630");
extern unsigned char grim_def_DAT_00900634[4] __asm__("_DAT_00900634");
extern unsigned char grim_def_DAT_00900638[4] __asm__("_DAT_00900638");
extern unsigned char grim_def_DAT_0090063c[4] __asm__("_DAT_0090063c");
extern unsigned char grim_def_DAT_00900640[4] __asm__("_DAT_00900640");
extern unsigned char grim_def_DAT_00900644[4] __asm__("_DAT_00900644");
extern unsigned char grim_def_DAT_00900648[4] __asm__("_DAT_00900648");
extern unsigned char grim_def_DAT_0090064c[4] __asm__("_DAT_0090064c");
extern unsigned char grim_def_DAT_00900650[4] __asm__("_DAT_00900650");
extern unsigned char grim_def_DAT_00900654[4] __asm__("_DAT_00900654");
extern unsigned char grim_def_DAT_00900658[1256] __asm__("_DAT_00900658");
extern unsigned char grim_def_DAT_00901408[4] __asm__("_DAT_00901408");
extern unsigned char grim_def_DAT_0090140c[76] __asm__("_DAT_0090140c");
extern unsigned char grim_def_DAT_00901458[4] __asm__("_DAT_00901458");
extern unsigned char grim_def_DAT_0090145c[8] __asm__("_DAT_0090145c");
extern unsigned char grim_def_DAT_009014d8[8] __asm__("_DAT_009014d8");
extern float grim_def_FLOAT_00900580 __asm__("_FLOAT_00900580");
extern float grim_def_FLOAT_00900584 __asm__("_FLOAT_00900584");
extern float grim_def_FLOAT_009005a0 __asm__("_FLOAT_009005a0");
extern float grim_def_FLOAT_009005a4 __asm__("_FLOAT_009005a4");
extern float grim_def_FLOAT_009005c0 __asm__("_FLOAT_009005c0");
extern float grim_def_FLOAT_009005c4 __asm__("_FLOAT_009005c4");
extern float grim_def_FLOAT_009005e4 __asm__("_FLOAT_009005e4");
extern int grim_def_INT_004dee54 __asm__("_INT_004dee54");
extern unsigned char grim_def_PTR_0080660c[4] __asm__("_PTR_0080660c");
extern unsigned char grim_def_PTR_00806614[4] __asm__("_PTR_00806614");
extern unsigned char grim_def_PTR_00806918[4] __asm__("_PTR_00806918");
extern unsigned char grim_def_PTR_0080694c[4] __asm__("_PTR_0080694c");
extern unsigned char grim_def_PTR_00806964[4] __asm__("_PTR_00806964");
extern unsigned char grim_def_PTR_00806968[4] __asm__("_PTR_00806968");
extern unsigned char grim_def_PTR_00901464[8] __asm__("_PTR_00901464");
extern int grim_def_UINT_004dee48 __asm__("_UINT_004dee48");
extern int grim_def_UINT_004dee4c __asm__("_UINT_004dee4c");
extern unsigned int grim_def_UINT_004dee50 __asm__("_UINT_004dee50");
extern unsigned int grim_def_UINT_004dee58 __asm__("_UINT_004dee58");
extern unsigned int grim_def_UINT_004dee5c __asm__("_UINT_004dee5c");
extern unsigned char grim_def_UINT_004dee60[8] __asm__("_UINT_004dee60");
extern unsigned int grim_def_UINT_008061d8 __asm__("_UINT_008061d8");
extern unsigned int grim_def_UINT_008061dc __asm__("_UINT_008061dc");
extern unsigned int grim_def_UINT_008061e0 __asm__("_UINT_008061e0");
extern unsigned int grim_def_UINT_008063e8 __asm__("_UINT_008063e8");
extern unsigned int grim_def_UINT_008063ec __asm__("_UINT_008063ec");
extern unsigned char grim_def_UINT_00806400[8] __asm__("_UINT_00806400");
extern unsigned int grim_def_UINT_00806610 __asm__("_UINT_00806610");
extern unsigned int grim_def_UINT_0080691c __asm__("_UINT_0080691c");
extern unsigned int grim_def_UINT_00806924 __asm__("_UINT_00806924");
extern unsigned int grim_def_UINT_00806930 __asm__("_UINT_00806930");
extern unsigned int grim_def_UINT_00806944 __asm__("_UINT_00806944");
extern unsigned int grim_def_UINT_00806950 __asm__("_UINT_00806950");
extern unsigned int grim_def_UINT_0080695c __asm__("_UINT_0080695c");
extern unsigned int grim_def_UINT_00806960 __asm__("_UINT_00806960");
extern unsigned int grim_def_UINT_0080696c __asm__("_UINT_0080696c");
extern unsigned int grim_def_UINT_00806970 __asm__("_UINT_00806970");
extern unsigned char grim_def_UINT_00806974[780] __asm__("_UINT_00806974");
extern unsigned int grim_def_UINT_00900600 __asm__("_UINT_00900600");
extern unsigned int grim_def_UINT_00900604 __asm__("_UINT_00900604");
extern unsigned int grim_def_UINT_00900608 __asm__("_UINT_00900608");
extern unsigned char grim_def_UINT_0090060c[20] __asm__("_UINT_0090060c");
extern unsigned char grim_def_UINT_0090146c[108] __asm__("_UINT_0090146c");
extern unsigned int grim_def_g_dwD3dRenderFlags __asm__("_g_dwD3dRenderFlags");
extern unsigned char grim_def_g_pD3dDevice[4] __asm__("_g_pD3dDevice");
extern unsigned char grim_def_g_pD3dExecuteBuffer[4] __asm__("_g_pD3dExecuteBuffer");
extern unsigned char grim_def_g_pD3dTextureList[4] __asm__("_g_pD3dTextureList");
extern unsigned char grim_def_g_pDirect3D[4] __asm__("_g_pDirect3D");
/* 0x004d8460, 176 bytes */ GRIM_DATA("004d8460") unsigned char grim_def_DAT_004d8460[176] __asm__("_DAT_004d8460") = {
    0xe0, 0xf3, 0xa6, 0xb3, 0x43, 0x2b, 0xcf, 0x11, 0xa2, 0xde, 0x00, 0xaa, 0x00, 0xb9, 0x33, 0x56,
    0x81, 0xdb, 0x14, 0x6c, 0x33, 0xa7, 0xce, 0x11, 0xa5, 0x21, 0x00, 0x20, 0xaf, 0x0b, 0xe5, 0x60,
    0x85, 0x58, 0x80, 0x57, 0xec, 0x6e, 0xcf, 0x11, 0x94, 0x41, 0xa8, 0x23, 0x03, 0xc1, 0x0e, 0x27,
    0x00, 0x4e, 0x04, 0xda, 0xb2, 0x69, 0xd0, 0x11, 0xa1, 0xd5, 0x00, 0xaa, 0x00, 0xb8, 0xdf, 0xbb,
    0x84, 0xdb, 0x14, 0x6c, 0x33, 0xa7, 0xce, 0x11, 0xa5, 0x21, 0x00, 0x20, 0xaf, 0x0b, 0xe5, 0x60,
    0x85, 0xdb, 0x14, 0x6c, 0x33, 0xa7, 0xce, 0x11, 0xa5, 0x21, 0x00, 0x20, 0xaf, 0x0b, 0xe5, 0x60,
    0xe0, 0x0e, 0x9f, 0x4b, 0x7e, 0x0d, 0xd0, 0x11, 0x9b, 0x06, 0x00, 0xa0, 0xc9, 0x03, 0xa3, 0xb8,
    0x46, 0xd9, 0xd4, 0x47, 0xe8, 0x62, 0xcf, 0x11, 0x93, 0xbc, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00,
    0x80, 0x07, 0x21, 0xb0, 0xcd, 0x89, 0xd0, 0x11, 0xaf, 0x08, 0x00, 0xa0, 0xc9, 0x25, 0xcd, 0x16,
    0x83, 0xfa, 0x9a, 0x27, 0x81, 0x49, 0xce, 0x11, 0xa5, 0x21, 0x00, 0x20, 0xaf, 0x0b, 0xe5, 0x60,
    0x85, 0xfa, 0x9a, 0x27, 0x81, 0x49, 0xce, 0x11, 0xa5, 0x21, 0x00, 0x20, 0xaf, 0x0b, 0xe5, 0x60
};
/* 0x004d8570, 128 bytes */ GRIM_DATA("004d8570") unsigned char grim_def_DAT_004d8570[128] __asm__("_DAT_004d8570") = {
    0x80, 0x00, 0xba, 0x3b, 0x21, 0x24, 0xcf, 0x11, 0xa3, 0x1a, 0x00, 0xaa, 0x00, 0xb9, 0x33, 0x56,
    0xc1, 0x1e, 0xae, 0x6a, 0x2a, 0x66, 0xd0, 0x11, 0x88, 0x9d, 0x00, 0xaa, 0x00, 0xbb, 0xb7, 0x6a,
    0x20, 0x6b, 0x08, 0xf2, 0x9f, 0x25, 0xcf, 0x11, 0xa3, 0x1a, 0x00, 0xaa, 0x00, 0xb9, 0x33, 0x56,
    0x60, 0x5c, 0x66, 0xa4, 0x73, 0x26, 0xcf, 0x11, 0xa3, 0x1a, 0x00, 0xaa, 0x00, 0xb9, 0x33, 0x56,
    0xe0, 0x3d, 0xe6, 0x84, 0xaa, 0x46, 0xcf, 0x11, 0x81, 0x6f, 0x00, 0x00, 0xc0, 0x20, 0x15, 0x6e,
    0xa1, 0x49, 0x19, 0x88, 0xf3, 0xd6, 0xd0, 0x11, 0x89, 0xab, 0x00, 0xa0, 0xc9, 0x05, 0x41, 0x29,
    0x00, 0x88, 0x10, 0x64, 0x7d, 0x95, 0xd0, 0x11, 0x89, 0xab, 0x00, 0xa0, 0xc9, 0x05, 0x41, 0x29,
    0x01, 0x15, 0x28, 0x93, 0xf8, 0x8c, 0xd0, 0x11, 0x89, 0xab, 0x00, 0xa0, 0xc9, 0x05, 0x41, 0x29
};
/* 0x004d85f0, 176 bytes */ GRIM_DATA("004d85f0") unsigned char grim_def_DAT_004d85f0[176] __asm__("_DAT_004d85f0") = {
    0xe0, 0xd9, 0xdc, 0x2c, 0xa0, 0x25, 0xcf, 0x11, 0xa3, 0x1a, 0x00, 0xaa, 0x00, 0xb9, 0x33, 0x56,
    0x02, 0x15, 0x28, 0x93, 0xf8, 0x8c, 0xd0, 0x11, 0x89, 0xab, 0x00, 0xa0, 0xc9, 0x05, 0x41, 0x29,
    0x42, 0xc1, 0x17, 0x44, 0xad, 0x33, 0xcf, 0x11, 0x81, 0x6f, 0x00, 0x00, 0xc0, 0x20, 0x15, 0x6e,
    0x44, 0xc1, 0x17, 0x44, 0xad, 0x33, 0xcf, 0x11, 0x81, 0x6f, 0x00, 0x00, 0xc0, 0x20, 0x15, 0x6e,
    0x03, 0x15, 0x28, 0x93, 0xf8, 0x8c, 0xd0, 0x11, 0x89, 0xab, 0x00, 0xa0, 0xc9, 0x05, 0x41, 0x29,
    0x45, 0xc1, 0x17, 0x44, 0xad, 0x33, 0xcf, 0x11, 0x81, 0x6f, 0x00, 0x00, 0xc0, 0x20, 0x15, 0x6e,
    0x46, 0xc1, 0x17, 0x44, 0xad, 0x33, 0xcf, 0x11, 0x81, 0x6f, 0x00, 0x00, 0xc0, 0x20, 0x15, 0x6e,
    0x00, 0x15, 0x28, 0x93, 0xf8, 0x8c, 0xd0, 0x11, 0x89, 0xab, 0x00, 0xa0, 0xc9, 0x05, 0x41, 0x29,
    0xe0, 0xee, 0xf1, 0xd8, 0x34, 0xf6, 0xcf, 0x11, 0x87, 0x00, 0x00, 0xa0, 0x24, 0x5d, 0x91, 0x8b,
    0xe1, 0xee, 0xf1, 0xd8, 0x34, 0xf6, 0xcf, 0x11, 0x87, 0x00, 0x00, 0xa0, 0x24, 0x5d, 0x91, 0x8b,
    0x00, 0x00, 0x00, 0xbf, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x40
};
/* 0x004dee48, 4 bytes */ GRIM_DATA("004dee48") int grim_def_UINT_004dee48 __asm__("_UINT_004dee48") = 4;
/* 0x004dee4c, 4 bytes */ GRIM_DATA("004dee4c") int grim_def_UINT_004dee4c __asm__("_UINT_004dee4c") = 4;
/* 0x004dee50, 4 bytes */ GRIM_DATA("004dee50") unsigned int grim_def_UINT_004dee50 __asm__("_UINT_004dee50") = 0x100;
/* 0x004dee54, 4 bytes */ GRIM_DATA("004dee54") int grim_def_INT_004dee54 __asm__("_INT_004dee54") = 256;
/* 0x004dee58, 4 bytes */ GRIM_DATA("004dee58") unsigned int grim_def_UINT_004dee58 __asm__("_UINT_004dee58") = 0x1;
/* 0x004dee5c, 4 bytes */ GRIM_DATA("004dee5c") unsigned int grim_def_UINT_004dee5c __asm__("_UINT_004dee5c") = 0x1;
/* 0x004dee60, 8 bytes */ GRIM_DATA("004dee60") unsigned char grim_def_UINT_004dee60[8] __asm__("_UINT_004dee60") = { 0x01 };
/* 0x008061d8, 4 bytes */ GRIM_DATA("008061d8") unsigned int grim_def_UINT_008061d8 __asm__("_UINT_008061d8") = 0x0;
/* 0x008061dc, 4 bytes */ GRIM_DATA("008061dc") unsigned int grim_def_UINT_008061dc __asm__("_UINT_008061dc") = 0x0;
/* 0x008061e0, 4 bytes */ GRIM_DATA("008061e0") unsigned int grim_def_UINT_008061e0 __asm__("_UINT_008061e0") = 0x0;
/* 0x008061e4, 4 bytes */ GRIM_DATA("008061e4") unsigned char grim_def_g_pD3dDevice[4] __asm__("_g_pD3dDevice") = {0};
/* 0x008063e8, 4 bytes */ GRIM_DATA("008063e8") unsigned int grim_def_UINT_008063e8 __asm__("_UINT_008063e8") = 0x0;
/* 0x008063ec, 4 bytes */ GRIM_DATA("008063ec") unsigned int grim_def_UINT_008063ec __asm__("_UINT_008063ec") = 0x0;
/* 0x008063f0, 4 bytes */ GRIM_DATA("008063f0") unsigned char grim_def_DAT_008063f0[4] __asm__("_DAT_008063f0") = {0};
/* 0x008063f4, 4 bytes */ GRIM_DATA("008063f4") unsigned char grim_def_DAT_008063f4[4] __asm__("_DAT_008063f4") = {0};
/* 0x008063f8, 4 bytes */ GRIM_DATA("008063f8") unsigned char grim_def_DAT_008063f8[4] __asm__("_DAT_008063f8") = {0};
/* 0x008063fc, 4 bytes */ GRIM_DATA("008063fc") unsigned char grim_def_DAT_008063fc[4] __asm__("_DAT_008063fc") = {0};
/* 0x00806400, 8 bytes */ GRIM_DATA("00806400") unsigned char grim_def_UINT_00806400[8] __asm__("_UINT_00806400") = {0};
/* 0x00806608, 4 bytes */ GRIM_DATA("00806608") unsigned char grim_def_g_pDirect3D[4] __asm__("_g_pDirect3D") = {0};
/* 0x0080660c, 4 bytes */ GRIM_DATA("0080660c") unsigned char grim_def_PTR_0080660c[4] __asm__("_PTR_0080660c") = {0};
/* 0x00806610, 4 bytes */ GRIM_DATA("00806610") unsigned int grim_def_UINT_00806610 __asm__("_UINT_00806610") = 0x0;
/* 0x00806614, 4 bytes */ GRIM_DATA("00806614") unsigned char grim_def_PTR_00806614[4] __asm__("_PTR_00806614") = {0};
/* 0x00806918, 4 bytes */ GRIM_DATA("00806918") unsigned char grim_def_PTR_00806918[4] __asm__("_PTR_00806918") = {0};
/* 0x0080691c, 4 bytes */ GRIM_DATA("0080691c") unsigned int grim_def_UINT_0080691c __asm__("_UINT_0080691c") = 0x0;
/* 0x00806920, 4 bytes */ GRIM_DATA("00806920") unsigned int grim_def_g_dwD3dRenderFlags __asm__("_g_dwD3dRenderFlags") = 0x0;
/* 0x00806924, 4 bytes */ GRIM_DATA("00806924") unsigned int grim_def_UINT_00806924 __asm__("_UINT_00806924") = 0x0;
/* 0x00806930, 4 bytes */ GRIM_DATA("00806930") unsigned int grim_def_UINT_00806930 __asm__("_UINT_00806930") = 0x0;
/* 0x00806944, 4 bytes */ GRIM_DATA("00806944") unsigned int grim_def_UINT_00806944 __asm__("_UINT_00806944") = 0x0;
/* 0x00806948, 4 bytes */ GRIM_DATA("00806948") unsigned char grim_def_g_pD3dTextureList[4] __asm__("_g_pD3dTextureList") = {0};
/* 0x0080694c, 4 bytes */ GRIM_DATA("0080694c") unsigned char grim_def_PTR_0080694c[4] __asm__("_PTR_0080694c") = {0};
/* 0x00806950, 4 bytes */ GRIM_DATA("00806950") unsigned int grim_def_UINT_00806950 __asm__("_UINT_00806950") = 0x0;
/* 0x00806954, 4 bytes */ GRIM_DATA("00806954") unsigned char grim_def_g_pD3dExecuteBuffer[4] __asm__("_g_pD3dExecuteBuffer") = {0};
/* 0x00806958, 4 bytes */ GRIM_DATA("00806958") unsigned char grim_def_DAT_00806958[4] __asm__("_DAT_00806958") = {0};
/* 0x0080695c, 4 bytes */ GRIM_DATA("0080695c") unsigned int grim_def_UINT_0080695c __asm__("_UINT_0080695c") = 0x0;
/* 0x00806960, 4 bytes */ GRIM_DATA("00806960") unsigned int grim_def_UINT_00806960 __asm__("_UINT_00806960") = 0x0;
/* 0x00806964, 4 bytes */ GRIM_DATA("00806964") unsigned char grim_def_PTR_00806964[4] __asm__("_PTR_00806964") = {0};
/* 0x00806968, 4 bytes */ GRIM_DATA("00806968") unsigned char grim_def_PTR_00806968[4] __asm__("_PTR_00806968") = {0};
/* 0x0080696c, 4 bytes */ GRIM_DATA("0080696c") unsigned int grim_def_UINT_0080696c __asm__("_UINT_0080696c") = 0x0;
/* 0x00806970, 4 bytes */ GRIM_DATA("00806970") unsigned int grim_def_UINT_00806970 __asm__("_UINT_00806970") = 0x0;
/* 0x00806974, 780 bytes */ GRIM_DATA("00806974") unsigned char grim_def_UINT_00806974[780] __asm__("_UINT_00806974") = {0};
/* 0x0090052c, 4 bytes */ /* loose */ unsigned char grim_def_DAT_0090052c[4] __asm__("_DAT_0090052c") = {0};
/* 0x00900540, 4 bytes */ /* loose */ unsigned char grim_def_DAT_00900540[4] __asm__("_DAT_00900540") = {0};
/* 0x00900544, 4 bytes */ /* loose */ unsigned char grim_def_DAT_00900544[4] __asm__("_DAT_00900544") = {0};
/* 0x00900548, 4 bytes */ /* loose */ unsigned char grim_def_DAT_00900548[4] __asm__("_DAT_00900548") = {0};
/* 0x0090054c, 4 bytes */ /* loose */ unsigned char grim_def_DAT_0090054c[4] __asm__("_DAT_0090054c") = {0};
/* 0x00900550, 4 bytes */ /* loose */ unsigned char grim_def_DAT_00900550[4] __asm__("_DAT_00900550") = {0};
/* 0x00900554, 4 bytes */ /* loose */ unsigned char grim_def_DAT_00900554[4] __asm__("_DAT_00900554") = {0};
/* 0x00900558, 4 bytes */ /* loose */ unsigned char grim_def_DAT_00900558[4] __asm__("_DAT_00900558") = {0};
/* 0x0090055c, 4 bytes */ /* loose */ unsigned char grim_def_DAT_0090055c[4] __asm__("_DAT_0090055c") = {0};
/* 0x00900560, 4 bytes */ /* loose */ unsigned char grim_def_DAT_00900560[4] __asm__("_DAT_00900560") = {0};
/* 0x00900564, 4 bytes */ /* loose */ unsigned char grim_def_DAT_00900564[4] __asm__("_DAT_00900564") = {0};
static unsigned char grim_anchor_00900568[0] __attribute__((section(".data$grim_00900568"), aligned(16), used));
static unsigned char grim_pad_00900568[8] __attribute__((section(".data$grim_00900568_"), aligned(4), used));
/* 0x00900568, 24 bytes */ GRIM_DATA("00900568z") unsigned char grim_def_DAT_00900568[24] __asm__("_DAT_00900568") = {0};
/* 0x00900580, 4 bytes */ GRIM_DATA("00900580") float grim_def_FLOAT_00900580 __asm__("_FLOAT_00900580") = 0.0f;
/* 0x00900584, 28 bytes */ GRIM_DATA("00900584") float grim_def_FLOAT_00900584 __asm__("_FLOAT_00900584") = 0.0f;
/* 0x00900588, 24 bytes: the rest of grim_def_FLOAT_00900584's span */ GRIM_DATA("00900584") static unsigned char FLOAT_00900584__tail[24] __attribute__((used)) = {0};
/* 0x009005a0, 4 bytes */ GRIM_DATA("009005a0") float grim_def_FLOAT_009005a0 __asm__("_FLOAT_009005a0") = 0.0f;
/* 0x009005a4, 28 bytes */ GRIM_DATA("009005a4") float grim_def_FLOAT_009005a4 __asm__("_FLOAT_009005a4") = 0.0f;
/* 0x009005a8, 24 bytes: the rest of grim_def_FLOAT_009005a4's span */ GRIM_DATA("009005a4") static unsigned char FLOAT_009005a4__tail[24] __attribute__((used)) = {0};
/* 0x009005c0, 4 bytes */ GRIM_DATA("009005c0") float grim_def_FLOAT_009005c0 __asm__("_FLOAT_009005c0") = 0.0f;
/* 0x009005c4, 28 bytes */ GRIM_DATA("009005c4") float grim_def_FLOAT_009005c4 __asm__("_FLOAT_009005c4") = 0.0f;
/* 0x009005c8, 24 bytes: the rest of grim_def_FLOAT_009005c4's span */ GRIM_DATA("009005c4") static unsigned char FLOAT_009005c4__tail[24] __attribute__((used)) = {0};
/* 0x009005e0, 4 bytes */ GRIM_DATA("009005e0") unsigned char grim_def_DAT_009005e0[4] __asm__("_DAT_009005e0") = {0};
/* 0x009005e4, 28 bytes */ GRIM_DATA("009005e4") float grim_def_FLOAT_009005e4 __asm__("_FLOAT_009005e4") = 0.0f;
/* 0x009005e8, 24 bytes: the rest of grim_def_FLOAT_009005e4's span */ GRIM_DATA("009005e4") static unsigned char FLOAT_009005e4__tail[24] __attribute__((used)) = {0};
/* 0x00900600, 4 bytes */ GRIM_DATA("00900600") unsigned int grim_def_UINT_00900600 __asm__("_UINT_00900600") = 0x0;
/* 0x00900604, 4 bytes */ GRIM_DATA("00900604") unsigned int grim_def_UINT_00900604 __asm__("_UINT_00900604") = 0x0;
/* 0x00900608, 4 bytes */ GRIM_DATA("00900608") unsigned int grim_def_UINT_00900608 __asm__("_UINT_00900608") = 0x0;
/* 0x0090060c, 20 bytes */ GRIM_DATA("0090060c") unsigned char grim_def_UINT_0090060c[20] __asm__("_UINT_0090060c") = {0};
/* 0x00900620, 4 bytes */ GRIM_DATA("00900620") unsigned char grim_def_DAT_00900620[4] __asm__("_DAT_00900620") = {0};
/* 0x00900624, 4 bytes */ GRIM_DATA("00900624") unsigned char grim_def_DAT_00900624[4] __asm__("_DAT_00900624") = {0};
/* 0x00900628, 4 bytes */ GRIM_DATA("00900628") unsigned char grim_def_DAT_00900628[4] __asm__("_DAT_00900628") = {0};
/* 0x0090062c, 4 bytes */ GRIM_DATA("0090062c") unsigned char grim_def_DAT_0090062c[4] __asm__("_DAT_0090062c") = {0};
/* 0x00900630, 4 bytes */ GRIM_DATA("00900630") unsigned char grim_def_DAT_00900630[4] __asm__("_DAT_00900630") = {0};
/* 0x00900634, 4 bytes */ GRIM_DATA("00900634") unsigned char grim_def_DAT_00900634[4] __asm__("_DAT_00900634") = {0};
/* 0x00900638, 4 bytes */ GRIM_DATA("00900638") unsigned char grim_def_DAT_00900638[4] __asm__("_DAT_00900638") = {0};
/* 0x0090063c, 4 bytes */ GRIM_DATA("0090063c") unsigned char grim_def_DAT_0090063c[4] __asm__("_DAT_0090063c") = {0};
/* 0x00900640, 4 bytes */ GRIM_DATA("00900640") unsigned char grim_def_DAT_00900640[4] __asm__("_DAT_00900640") = {0};
/* 0x00900644, 4 bytes */ GRIM_DATA("00900644") unsigned char grim_def_DAT_00900644[4] __asm__("_DAT_00900644") = {0};
/* 0x00900648, 4 bytes */ GRIM_DATA("00900648") unsigned char grim_def_DAT_00900648[4] __asm__("_DAT_00900648") = {0};
/* 0x0090064c, 4 bytes */ GRIM_DATA("0090064c") unsigned char grim_def_DAT_0090064c[4] __asm__("_DAT_0090064c") = {0};
/* 0x00900650, 4 bytes */ GRIM_DATA("00900650") unsigned char grim_def_DAT_00900650[4] __asm__("_DAT_00900650") = {0};
/* 0x00900654, 4 bytes */ GRIM_DATA("00900654") unsigned char grim_def_DAT_00900654[4] __asm__("_DAT_00900654") = {0};
/* 0x00900658, 1256 bytes */ GRIM_DATA("00900658") unsigned char grim_def_DAT_00900658[1256] __asm__("_DAT_00900658") = {0};
/* 0x00901408, 4 bytes */ GRIM_DATA("00901408") unsigned char grim_def_DAT_00901408[4] __asm__("_DAT_00901408") = {0};
/* 0x0090140c, 76 bytes */ GRIM_DATA("0090140c") unsigned char grim_def_DAT_0090140c[76] __asm__("_DAT_0090140c") = {0};
/* 0x00901458, 4 bytes */ GRIM_DATA("00901458") unsigned char grim_def_DAT_00901458[4] __asm__("_DAT_00901458") = {0};
/* 0x0090145c, 8 bytes */ GRIM_DATA("0090145c") unsigned char grim_def_DAT_0090145c[8] __asm__("_DAT_0090145c") = {0};
/* 0x00901464, 8 bytes */ GRIM_DATA("00901464") unsigned char grim_def_PTR_00901464[8] __asm__("_PTR_00901464") = {0};
/* 0x0090146c, 108 bytes */ GRIM_DATA("0090146c") unsigned char grim_def_UINT_0090146c[108] __asm__("_UINT_0090146c") = {0};
/* 0x009014d8, 8 bytes */ GRIM_DATA("009014d8") unsigned char grim_def_DAT_009014d8[8] __asm__("_DAT_009014d8") = {0};
