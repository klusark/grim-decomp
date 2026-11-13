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
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Creates the Direct3D device, z-buffer, viewport, execute buffer and picks the texture formats */

int __cdecl D3D_SelectDriver(uint driverIdx,int useZBuffer)

{
  unsigned char _frame[0xc0] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  #define pvStack_ac (*(void **)(_frame + (0xc0 - 0xac)))
  #define pcStack_a8 (*(code_std **)(_frame + (0xc0 - 0xa8)))
  #define uStack_a4 (*(undefined4 *)(_frame + (0xc0 - 0xa4)))
  #define piStack_a0 (*(int **)(_frame + (0xc0 - 0xa0)))
  #define uStack_74 (*(undefined4 *)(_frame + (0xc0 - 0x74)))
  #define uStack_70 (*(undefined4 *)(_frame + (0xc0 - 0x70)))
  #define auStack_60 (*(undefined4 (*)[24])(_frame + (0xc0 - 0x60)))
  
  if (UINT_00806970 != 0) {
    return 0;
  }
  if (g_dwD3dDriverCount <= driverIdx) {
    return 0;
  }
  UINT_00900530 = driverIdx;
  g_pStd3D_CurDevice = &UINT_00900b40 + driverIdx * 0x8b;
  if (((useZBuffer == 0) || (*(int *)(&DAT_00900b48 + driverIdx * 0x22c) == 0)) ||
     ((g_dwD3dRenderFlags & 0x1800) == 0)) {
    UINT_004dee60 = 0;
  }
  else {
    UINT_004dee60 = 1;
    piStack_a0 = (int *)0x478388;
    uVar1 = D3D_CreateZBuffer(*(int *)((int)g_pVideoMode + 8),*(int *)((int)g_pVideoMode + 0xc));
    if (uVar1 == 0) {
      return 0;
    }
    UINT_00900534 = (-(uint)((*(uint *)((int)g_pStd3D_CurDevice + 0x2c) & 0x10) != 0) & 0xe) + 2;
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
  iVar2 = D3D_CreateViewport(*(uint *)((int)g_pVideoMode + 8),*(uint *)((int)g_pVideoMode + 0xc));
  if (iVar2 == 0) {
    return 0;
  }
  uVar1 = D3D_InitRenderState();
  if (uVar1 == 0) {
    return 0;
  }
  _DAT_008063fc = *(int *)((int)g_pStd3D_CurDevice + 0x40);
  if (_DAT_008063fc == 0) {
    _DAT_008063fc = 0x10000;
  }
  _DAT_008063f0 = 0x14;
  _DAT_008063f4 = 1;
  _DAT_008063f8 = 0;
  UINT_00806400 = 0;
  g_dwStd3D_maxVertices = *(uint *)((int)g_pStd3D_CurDevice + 0x44);
  if ((g_dwStd3D_maxVertices == 0) || (0x1ff < g_dwStd3D_maxVertices)) {
    g_dwStd3D_maxVertices = 0x200;
  }
  _DAT_00806958 = _DAT_008063fc;
  (**(code_std **)(*(int *)g_pD3dDevice + 0x18))(g_pD3dDevice,&DAT_008063f0,&g_pD3dExecuteBuffer,0);
  UINT_004dee58 = 1;
  UINT_00806944 = 0;
  D3D_SetTextureLimits
            (*(int *)((int)g_pStd3D_CurDevice + 0x30),*(int *)((int)g_pStd3D_CurDevice + 0x34),
             *(int *)((int)g_pStd3D_CurDevice + 0x38),*(int *)((int)g_pStd3D_CurDevice + 0x3c));
  g_pD3dTextureList = (void *)0x0;
  PTR_0080694c = (void *)0x0;
  _DAT_00900568 = D3D_FindTextureFormat((int *)((int)g_pVideoMode + 0x1c),((unsigned)(uintptr_t)&DAT_00900620),UINT_00806930);
  UINT_00806934 = (uint)(&DAT_00900620 + _DAT_00900568 * 0xa4);
  if (*(int *)((int)g_pStd3D_CurDevice + 0x10) != 0) {
    pvStack_ac = (void *)0x2;
    pcStack_a8 = (code *)0x10;
    uStack_a4 = 5;
    piStack_a0 = (int *)0x5;
    _DAT_009014d8 = D3D_FindTextureFormat((int *)&pvStack_ac,((unsigned)(uintptr_t)&DAT_00900620),UINT_00806930);
    UINT_00806938 = (uint)(&DAT_00900620 + _DAT_009014d8 * 0xa4);
    if (*(int *)((int)g_pStd3D_CurDevice + 0x18) == 0) {
      pvStack_ac = (void *)0x2;
      pcStack_a8 = (code *)0x10;
      uStack_a4 = 4;
      piStack_a0 = (int *)0x4;
      _DAT_0090052c = D3D_FindTextureFormat((int *)&pvStack_ac,((unsigned)(uintptr_t)&DAT_00900620),UINT_00806930);
      uStack_74 = 0x20;
      uStack_70 = 0x20;
      UINT_0080693c = (uint)(&DAT_00900620 + _DAT_0090052c * 0xa4);
      puVar3 = (undefined4 *)UINT_0080693c;
      puVar4 = auStack_60;
      for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      UINT_00806950 = (uint)stdDisplay_VBufferNew(&uStack_74,1,0,0);
    }
  }
  D3D_SetVertexLimit();
  UINT_00806970 = 1;
  return 1;
}
#undef auStack_60
#undef pcStack_a8
#undef piStack_a0
#undef pvStack_ac
#undef uStack_70
#undef uStack_74
#undef uStack_a4


/* ---- 0x00478660  D3D_ReleaseDriver ---- */
void __cdecl D3D_ReleaseDriver(void)

{
  if (UINT_00806970 != 0) {
    if (UINT_00806950 != 0) {
      stdDisplay_VBufferFree((void *)UINT_00806950);
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
    g_pStd3D_CurDevice = (void *)0x0;
    UINT_00806970 = 0;
  }
  return;
}

/* ---- 0x00478700  D3D_SetTextureLimits ---- */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl D3D_SetTextureLimits(int minW,int minH,int maxSize,int d)

{
  UINT_004dee48 = minW;
  UINT_004dee4c = minH;
  UINT_004dee50 = maxSize;
  _DAT_004dee54 = d;
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
    return 0;
  }
  for (iVar1 = 0xc; ppvVar2 = ppvVar2 + 1, iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppvVar2 = (void *)0x0;
  }
  (**(code_std **)(*(int *)g_pD3dExecuteBuffer + 0x18))(g_pD3dExecuteBuffer,(_frame + (0x50 - 0x34)));
  iVar1 = (**(code_std **)(*(int *)g_pD3dDevice + 0x20))
                    (g_pD3dDevice,g_pD3dExecuteBuffer,PTR_0080660c,2);
  return (uint)(iVar1 == 0);
}
#undef pvStack_38

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

void __cdecl std3D_GetValidDimensions(uint param_1,uint param_2,uint *param_3,uint *param_4)

{
  if (param_1 == 0) {
    param_1 = 1;
  }
  else if (UINT_004dee50 < param_1) {
    param_1 = UINT_004dee50;
  }
  if (param_2 == 0) {
    param_2 = 1;
  }
  else if (UINT_004dee50 < param_2) {
    param_2 = UINT_004dee50;
  }
  if (((param_1 < UINT_004dee48) || (param_2 < UINT_004dee4c)) ||
     ((*(int *)((int)g_pStd3D_CurDevice + 0x1c) != 0 && (param_1 != param_2)))) {
    if ((*(int *)((int)g_pStd3D_CurDevice + 0x1c) != 0) && (param_1 != param_2)) {
      if (param_1 <= param_2) {
        param_1 = param_2;
      }
      *param_3 = param_1;
      *param_4 = param_1;
      return;
    }
    if (param_1 < UINT_004dee48) {
      param_1 = UINT_004dee48;
    }
    if (param_2 < UINT_004dee4c) {
      param_2 = UINT_004dee4c;
    }
  }
  *param_3 = param_1;
  *param_4 = param_2;
  return;
}

/* ---- 0x00479110  std3D_PurgeTextureCache ---- */
/* Lua ResetTextures: frees every texture record Original name std3D_PurgeTextureCache (the
   remaster's GrimFandango (Linux): aligned call in rdCache_SendFaceListToHardware); was
   D3D_ResetTextures. */

void __cdecl std3D_PurgeTextureCache(void)

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

/* ---- 0x00479170  std3D_AddToTextureCache ---- */
/* Builds a 0x98-byte texture record {sysSurface, vidSurface, ..., +0x74 handle, +0x78 valid, +0x80
   w, +0x88 h, +0x88 size, +0x8c frameStamp, +0x90 prev, +0x94 next}; scales to the driver's size
   limits and converts 8-bit sources to 16-bit Original name std3D_AddToTextureCache (the remaster's
   GrimFandango (Linux): aligned call in rdMaterial_AddToTextureCache); was D3D_CreateTexture. */

int __cdecl std3D_AddToTextureCache(void *surface,void *texture,int usePalette,int colorKey)

{
  unsigned char _frame[0x170] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  byte bVar1;
  undefined2 *puVar2;
  void *pvVar3;
  int iVar4;
  byte *pbVar5;
  void *pvVar6;
  void *pvVar7;
  uint *puVar8;
  float fVar9;
  uint uVar10;
  uint uVar11;
  uint *puVar12;
  #define local_15c (*(uint *)(_frame + (0x170 - 0x15c)))
  #define local_14c (*(uint *)(_frame + (0x170 - 0x14c)))
  #define local_138 (*(uint *)(_frame + (0x170 - 0x138)))
  #define local_f0 (*(uint *)(_frame + (0x170 - 0xf0)))
  #define local_ec (*(uint *)(_frame + (0x170 - 0xec)))
  #define local_a4 (*(uint *)(_frame + (0x170 - 0xa4)))
  #define local_a0 (*(uint *)(_frame + (0x170 - 0xa0)))
  #define local_9c (*(uint *)(_frame + (0x170 - 0x9c)))
  #define local_98 (*(uint *)(_frame + (0x170 - 0x98)))
  #define local_3c (*(uint *)(_frame + (0x170 - 0x3c)))
  #define local_38 (*(float *)(_frame + (0x170 - 0x38)))
  #define local_34 (*(uint *)(_frame + (0x170 - 0x34)))
  #define local_30 (*(uint *)(_frame + (0x170 - 0x30)))
  #define local_2c (*(uint *)(_frame + (0x170 - 0x2c)))
  #define local_28 (*(uint *)(_frame + (0x170 - 0x28)))
  #define uStack_24 (*(uint *)(_frame + (0x170 - 0x24)))
  #define local_20 (*(void **)(_frame + (0x170 - 0x20)))
  #define fStack_1c (*(float *)(_frame + (0x170 - 0x1c)))
  #define local_18 (*(uint *)(_frame + (0x170 - 0x18)))
  #define local_14 (*(uint *)(_frame + (0x170 - 0x14)))
  #define local_10 (*(uint *)(_frame + (0x170 - 0x10)))
  #define local_c (*(uint *)(_frame + (0x170 - 0xc)))
  #define local_8 (*(uint *)(_frame + (0x170 - 0x8)))
  
  pvVar3 = *(void **)((int)surface + 0xc);
  local_8 = 0;
  local_18 = 0;
  local_10 = 0;
  local_14 = 0;
  local_30 = 0;
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
  local_c = (uint)pvVar3;
  if (((pvVar3 < UINT_004dee48) || (pvVar6 < UINT_004dee4c)) ||
     ((pvVar7 = surface, *(int *)((int)g_pStd3D_CurDevice + 0x1c) != 0 && (pvVar3 != pvVar6)))) {
    puVar8 = (uint *)((int)surface + 0xc);
    puVar12 = &local_f0;
    for (iVar4 = 0x13; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar12 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar12 = puVar12 + 1;
    }
    if ((*(int *)((int)g_pStd3D_CurDevice + 0x1c) == 0) || (pvVar3 == pvVar6)) {
      if (pvVar3 < UINT_004dee48) {
        pvVar3 = (void *)UINT_004dee48;
      }
      pvVar7 = pvVar6;
      if (pvVar6 < UINT_004dee4c) {
        pvVar7 = (void *)UINT_004dee4c;
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
    uStack_24 = 0;
    local_38 = (float)(int)ROUND(PUN(float,pvVar3) / (float)(int)local_c - -0.5);
    fStack_1c = PUN(float,pvVar7) / (float)(int)pvVar6 - -0.5;
    uVar10 = (uint)ROUND(fStack_1c);
    local_f0 = local_f0 * (int)local_38;
    local_ec = local_ec * uVar10;
    local_34 = uVar10;
    local_20 = pvVar6;
    local_30 = (uint)stdDisplay_VBufferNew(&local_f0,0,0,0);
    if (uVar10 != 0) {
      local_34 = 0;
      fStack_1c = (float)uVar10;
      do {
        if (local_38 != 0.0) {
          iVar4 = 0;
          fVar9 = local_38;
          do {
            Surface_Blit((void *)local_30,surface,iVar4,local_34,(int *)0x0,0);
            iVar4 = iVar4 + local_c;
            fVar9 = (float)((int)fVar9 + -1);
          } while (fVar9 != 0.0);
        }
        local_34 = local_34 + (int)pvVar6;
        fStack_1c = (float)((int)fStack_1c - 1);
      } while (fStack_1c != 0.0);
    }
    local_c = local_f0;
    surface = (void *)local_ec;
    pvVar7 = (void *)local_30;
    pvVar6 = surface;
  }
  surface = pvVar6;
  fStack_1c = (float)((int)surface * local_c);
  if ((usePalette == 0) || (*(int *)((int)g_pStd3D_CurDevice + 0x10) == 0)) {
    if (colorKey == 0) {
      *(undefined4 *)((int)texture + 0x7c) = 0;
      uVar10 = UINT_00806934;
    }
    else {
      *(undefined4 *)((int)texture + 0x7c) = 1;
      uVar10 = UINT_0080693c;
    }
  }
  else {
    *(undefined4 *)((int)texture + 0x7c) = 1;
    uVar10 = UINT_00806938;
    if (colorKey != 0) {
      uVar10 = UINT_0080693c;
    }
  }
  Mem_Copy(&local_a4,(void *)(uVar10 + 0x38),0x6c);
  uVar10 = local_c;
  local_9c = (uint)surface;
  local_a4 = 0x6c;
  local_a0 = 0x1007;
  local_3c = 0x1800;
  local_98 = local_c;
  iVar4 = (**(code_std **)(*PTR_00806968 + 0x18))(PTR_00806968,&local_a4,&local_8,0);
  if (iVar4 != 0) {
    local_8 = 0;
    goto LAB_0047940a;
  }
  puVar8 = &local_15c;
  for (iVar4 = 0x1b; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  local_15c = 0x6c;
  iVar4 = (**(code_std **)(*(int *)local_8 + 100))(local_8,0,&local_15c,1,0);
  if (iVar4 != 0) goto LAB_0047940a;
  iVar4 = *(int *)((int)pvVar7 + 0x20);
  if (iVar4 == 0) {
    stdDisplay_VBufferLock(pvVar7);
    if ((usePalette == 0) || (*(int *)((int)g_pStd3D_CurDevice + 0x10) == 0)) {
      if (colorKey == 0) {
        pvVar3 = (void *)0x0;
        if (surface != (void *)0x0) {
          do {
            pbVar5 = (byte *)((int)pvVar3 * *(int *)((int)pvVar7 + 0x18) +
                             *(int *)((int)pvVar7 + 0x5c));
            puVar2 = (undefined2 *)((int)pvVar3 * local_14c + local_138);
            uVar11 = uVar10;
            for (; uVar11 != 0; uVar11 = uVar11 - 1) {
              bVar1 = *pbVar5;
              pbVar5 = pbVar5 + 1;
              *puVar2 = *(undefined2 *)((int)&UINT_00806408 + (uint)bVar1 * 2);
              puVar2 = puVar2 + 1;
              uVar10 = local_c;
            }
            pvVar3 = (void *)((int)pvVar3 + 1);
          } while (pvVar3 < surface);
        }
      }
      else {
        pvVar3 = (void *)0x0;
        if (surface != (void *)0x0) {
          do {
            pbVar5 = (byte *)((int)pvVar3 * *(int *)((int)pvVar7 + 0x18) +
                             *(int *)((int)pvVar7 + 0x5c));
            puVar2 = (undefined2 *)((int)pvVar3 * local_14c + local_138);
            uVar11 = uVar10;
            for (; uVar11 != 0; uVar11 = uVar11 - 1) {
              bVar1 = *pbVar5;
              pbVar5 = pbVar5 + 1;
              *puVar2 = *(undefined2 *)(&DAT_00805fd8 + (uint)bVar1 * 2);
              puVar2 = puVar2 + 1;
              uVar10 = local_c;
            }
            pvVar3 = (void *)((int)pvVar3 + 1);
          } while (pvVar3 < surface);
        }
      }
    }
    else if (colorKey == 0) {
      pvVar3 = (void *)0x0;
      if (surface != (void *)0x0) {
        do {
          pbVar5 = (byte *)((int)pvVar3 * *(int *)((int)pvVar7 + 0x18) +
                           *(int *)((int)pvVar7 + 0x5c));
          puVar2 = (undefined2 *)((int)pvVar3 * local_14c + local_138);
          uVar11 = uVar10;
          for (; uVar11 != 0; uVar11 = uVar11 - 1) {
            bVar1 = *pbVar5;
            pbVar5 = pbVar5 + 1;
            *puVar2 = *(undefined2 *)(&DAT_008061e8 + (uint)bVar1 * 2);
            puVar2 = puVar2 + 1;
            uVar10 = local_c;
          }
          pvVar3 = (void *)((int)pvVar3 + 1);
        } while (pvVar3 < surface);
      }
    }
    else {
      pvVar3 = (void *)0x0;
      if (surface != (void *)0x0) {
        do {
          pbVar5 = (byte *)((int)pvVar3 * *(int *)((int)pvVar7 + 0x18) +
                           *(int *)((int)pvVar7 + 0x5c));
          puVar2 = (undefined2 *)((int)pvVar3 * local_14c + local_138);
          uVar11 = uVar10;
          for (; uVar11 != 0; uVar11 = uVar11 - 1) {
            bVar1 = *pbVar5;
            pbVar5 = pbVar5 + 1;
            *puVar2 = *(undefined2 *)(&DAT_00805fd8 + (uint)bVar1 * 2);
            puVar2 = puVar2 + 1;
            uVar10 = local_c;
          }
          pvVar3 = (void *)((int)pvVar3 + 1);
        } while (pvVar3 < surface);
      }
    }
LAB_00479709:
    stdDisplay_VBufferUnlock(pvVar7);
  }
  else if ((0 < iVar4) && (iVar4 < 3)) {
    stdDisplay_VBufferLock(pvVar7);
    pvVar3 = (void *)0x0;
    if (surface != (void *)0x0) {
      do {
        Mem_Copy((void *)((int)pvVar3 * local_14c + local_138),
                 (void *)((int)pvVar3 * *(int *)((int)pvVar7 + 0x18) + *(int *)((int)pvVar7 + 0x5c))
                 ,uVar10 * 2);
        pvVar3 = (void *)((int)pvVar3 + 1);
      } while (pvVar3 < surface);
    }
    goto LAB_00479709;
  }
  iVar4 = (**(code_std **)(*(int *)local_8 + 0x80))(local_8,0);
  if (iVar4 == 0) {
    if ((usePalette != 0) && (*(int *)((int)g_pStd3D_CurDevice + 0x10) == 0)) {
      if (*(int *)((int)pvVar7 + 0x20) == 0) {
        local_28 = UINT_00806408 & 0xffff;
        uStack_24 = local_28;
      }
      else if (*(int *)((int)pvVar7 + 0x20) == 1) {
        local_28 = *(uint *)((int)pvVar7 + 0x60);
        uStack_24 = *(uint *)((int)pvVar7 + 0x60);
      }
      (**(code_std **)(*(int *)local_8 + 0x74))(local_8,8,&local_28);
    }
    iVar4 = (*(code_std *)**(undefined4 **)local_8)(local_8,&DAT_004d85f0,&local_10);
    if (iVar4 == 0) {
      iVar4 = (**(code_std **)(*(int *)local_8 + 0x58))(local_8,&local_a4);
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
        iVar4 = (*(code_std *)**(undefined4 **)local_18)(local_18,&DAT_004d85f0,&local_14);
        if (iVar4 == 0) {
          iVar4 = (**(code_std **)(*(int *)local_14 + 0x18))(local_14,local_10);
          if (iVar4 == 0) {
            iVar4 = (**(code_std **)(*(int *)local_14 + 0x10))(local_14,g_pD3dDevice,&local_2c);
            if (iVar4 != 0) {
              local_2c = 0;
            }
            (**(code_std **)(*(int *)local_10 + 8))(local_10);
            local_10 = 0;
            (**(code_std **)(*(int *)local_8 + 8))(local_8);
            local_8 = 0;
            if (local_30 != 0) {
              stdDisplay_VBufferFree((void *)local_30);
            }
            *(uint *)texture = local_14;
            *(uint *)((int)texture + 4) = local_18;
            *(uint *)((int)texture + 0x74) = local_2c;
            *(uint *)((int)texture + 0x80) = uVar10;
            *(void **)((int)texture + 0x84) = surface;
            *(float *)((int)texture + 0x88) = fStack_1c;
            *(undefined4 *)((int)texture + 0x78) = 1;
            *(uint *)((int)texture + 0x8c) = UINT_004dee58;
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
    stdDisplay_VBufferFree((void *)local_30);
  }
  if (local_18 != 0) {
    (**(code_std **)(*(int *)local_18 + 8))(local_18);
  }
  if (local_14 != 0) {
    (**(code_std **)(*(int *)local_14 + 8))(local_14);
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
#undef local_ec
#undef local_f0
#undef uStack_24


/* ---- 0x00479860  D3D_FreeAllTextures ---- */
void __cdecl D3D_FreeAllTextures(void)

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
  UINT_00806944 = 0;
  *(undefined4 *)((int)g_pStd3D_CurDevice + 0x14c) =
       *(undefined4 *)((int)g_pStd3D_CurDevice + 0x148);
  UINT_004dee58 = 1;
  return;
}

/* ---- 0x004798e0  D3D_LinkTexture ---- */
void __cdecl D3D_LinkTexture(void *param_1)

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
  UINT_00806944 = UINT_00806944 + 1;
  *(int *)((int)g_pStd3D_CurDevice + 0x14c) =
       *(int *)((int)g_pStd3D_CurDevice + 0x14c) - *(int *)((int)param_1 + 0x88);
  return;
}

/* ---- 0x00479950  D3D_UnlinkTexture ---- */
void __cdecl D3D_UnlinkTexture(void *param_1)

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
  UINT_00806944 = UINT_00806944 - 1;
  *(int *)((int)g_pStd3D_CurDevice + 0x14c) =
       *(int *)((int)g_pStd3D_CurDevice + 0x14c) + *(int *)((int)param_1 + 0x88);
  return;
}

/* ---- 0x00479a00  D3D_SetVertexLimit ---- */
uint __cdecl D3D_SetVertexLimit(void)

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


/* ---- 0x00479a70  std3D_UpdateFrameCount ---- */
/* Original name std3D_UpdateFrameCount (the remaster's GrimFandango (Linux): aligned call in
   rdMaterial_AddToTextureCache); was D3D_TouchTexture. */

void __cdecl std3D_UpdateFrameCount(int param_1)

{
  *(uint *)(param_1 + 0x8c) = UINT_004dee58;
  D3D_UnlinkTexture((void *)param_1);
  D3D_LinkTexture((void *)param_1);
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
uint __cdecl D3D_FindClosestDriver(int *param_1,int param_2,uint param_3)

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
uint __cdecl D3D_FindTextureFormat(int *param_1,int param_2,uint param_3)

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

void __cdecl D3D_SetViewportRect(uint *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  
  UINT_00900600 = *param_1;
  uVar1 = param_1[1];
  UINT_00900580 = PUN(uint,(float)(float)(int)UINT_00900600);
  UINT_00900608 = param_1[2];
  iVar3 = UINT_00900600 + UINT_00900608;
  UINT_0090060c = param_1[3];
  puVar4 = &UINT_00900580;
  UINT_00900604 = uVar1;
  for (iVar2 = 0x20; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  UINT_00900584 = PUN(uint,(float)(float)(int)UINT_00900604);
  _DAT_00900540 = 0;
  _DAT_00900544 = 1;
  *(float *)&DAT_009005a0 = (float)iVar3;
  *(float *)&DAT_009005a4 = (float)(int)UINT_00900604;
  *(float *)&DAT_009005c4 = (float)(int)(uVar1 + UINT_0090060c);
  *(float *)&DAT_009005c0 = (float)iVar3;
  _DAT_00900550 = 0;
  *(float *)&DAT_009005e4 = *(float *)&DAT_009005c4;
  *(float *)&DAT_009005e0 = (float)UINT_00900580;
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
  iVar3 = *(int *)((int)g_pStd3D_CurDevice + 0x14);
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

uint __cdecl D3D_CreateZBuffer(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  
  _DAT_00901400 = 1;
  _DAT_00901408 = 0;
  Mem_Copy(&DAT_0090140c,(void *)((int)g_pVideoMode + 8),0x4c);
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
  PTR_00806964[5] = param_1;
  PTR_00806964[4] = param_2;
  if (*(int *)g_pStd3D_CurDevice == 0) {
    uVar2 = PTR_00806964[0x1c] | 0x800;
  }
  else {
    uVar2 = PTR_00806964[0x1c] | 0x4000;
  }
  PTR_00806964[0x1c] = uVar2;
  uVar2 = *(uint *)((int)g_pStd3D_CurDevice + 0x1f0);
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
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  
  if (g_dwD3dDriverCount < 4) {
    iVar1 = g_dwD3dDriverCount * 0x22c;
    iVar4 = g_dwD3dDriverCount * 0x8b;
    Mem_Copy((void *)(iVar1 + ((unsigned)(uintptr_t)&DAT_00900d5c)),(void *)a1,0x10);
    strncpy(iVar1 + 0x900c08,a2,0x7f);
    (&DAT_00900c87)[iVar1] = 0;
    strncpy(iVar1 + 0x900b88,a3,0x7f);
    (&DAT_00900c07)[iVar1] = 0;
    if (*(int *)(a4 + 8) == 0) {
      (&UINT_00900b40)[iVar4] = 0;
      a4 = a5;
    }
    else {
      (&UINT_00900b40)[iVar4] = 1;
    }
    Mem_Copy((void *)(iVar1 + ((unsigned)(uintptr_t)&DAT_00900c90)),(void *)a4,0xcc);
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
    uVar3 = D3D_CapsToFilterBits(*(uint *)(&DAT_00900d2c + iVar1));
    *(uint *)(&DAT_00900b68 + iVar1) = uVar3;
    uVar3 = D3D_FilterBitsToMask((byte)*(undefined4 *)(&DAT_00900d00 + iVar1));
    *(uint *)(&DAT_00900b6c + iVar1) = uVar3;
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
uint __cdecl D3D_CapsToFilterBits(uint param_1)

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
  return (uint)bVar1;
}

/* ---- 0x0047a890  D3D_FilterBitsToMask ---- */
uint __cdecl D3D_FilterBitsToMask(byte param_1)

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
  return (uint)bVar1;
}

/* ---- 0x0047a8e0  D3D_FilterBitsToEnum ---- */
uint __cdecl D3D_FilterBitsToEnum(byte param_1)

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
  return (uint)bVar1;
}

/* ---- 0x0047a930  D3D_EvictTexture ---- */
/* Frees a texture not used this frame (best size match) to make room, or all idle textures */

int __cdecl D3D_EvictTexture(uint size)

{
  unsigned char _frame[0x20] __attribute__((aligned(16)));  /* Ghidra stack frame, see tools/frame_locals.py */
  uint uVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  #define local_4 (*(uint *)(_frame + (0x20 - 0x4)))
  
  uVar3 = 0xffffffff;
  puVar4 = (undefined4 *)0x0;
  for (puVar2 = g_pD3dTextureList; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)puVar2[0x25])
  {
    if (puVar2[0x23] != UINT_004dee58) {
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
      if (puVar4[0x23] != UINT_004dee58) {
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
#undef local_4

